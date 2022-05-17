#include "AudioinPage.h"
#include "Hardware.h"
#include "Controls.h"

void AudioinPage::onBtnPressed(uint8_t pin)
{
    uint8_t keyNum = PinToKeyNum(pin);
    if (keyNum > 0)
    {
        PageManager.PageArr[PageManager.lastPage]->onBtnPressed(pin);
    }
    else
    {
        switch (pin)
        {
        case BTN_PWR:
            // switch to previous page and then immediately switch back to Audioin page
            PageManager.switchPage(PageManager.lastPage);
            break;
        case BTN_JOY:
            PageManager.PageArr[PageManager.lastPage]->onBtnPressed(pin);
            break;
        }
    }
}

void AudioinPage::onBtnHold(uint8_t pin)
{
    switch (pin)
    {
    case BTN_PWR:
        PageManager.showPopup(E_PG_POPUP_POWER);
        break;
    }
}

void AudioinPage::onBtnReleased(uint8_t pin)
{
    uint8_t keyNum = PinToKeyNum(pin);
    if (keyNum > 0)
    {
        PageManager.PageArr[PageManager.lastPage]->onBtnReleased(pin);
    }
    else
    {
        switch (pin)
        {
        case BTN_JOY:
            PageManager.PageArr[PageManager.lastPage]->onBtnReleased(pin);
            break;
        }
    }
}

void AudioinPage::onEncTurned(uint8_t id, int value)
{
    switch (id)
    {
    case 0:
        // input gain
        setInputGain(value);
        break;
    case 1:
        // Analog in volume
        gslc_ElemXSeekbarSetPos(&m_gui, m_pElemAudioinLmVol, INPUT_VOL_MAX - value);
        updateInputVol(InputTracks::LINEMIC_IN, value);
        break;
    case 2:
        // USB in volume
        gslc_ElemXSeekbarSetPos(&m_gui, m_pElemAudioinUsbVol, INPUT_VOL_MAX - value);
        updateInputVol(InputTracks::USB_IN, value);
        break;
    }
}

void AudioinPage::onJoyUpdate(int joy_x, int joy_y)
{
}

void AudioinPage::onTouch(int ref)
{
    int temp;
    switch (ref)
    {
    case E_ELEM_BASE_BACK_BTN:
        PageManager.switchPage(PageManager.lastPage);
        break;
    case E_ELEM_AUDIOIN_PFL_BTN:
        usePFL = !usePFL;
        setPFL(usePFL);
        break;
    case E_ELEM_AUDIOIN_LINE_IN_BTN:
        inputSource = 0;
        enc0->changePrecision(LINE_GAIN_MAX, inputGain[inputSource], false);
        toggleButton(m_pElemAudioinLineInBtn, true);
        toggleButton(m_pElemAudioinMicBtn, false);
        sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
        setInputGain(inputGain[0]);
        break;
    case E_ELEM_AUDIOIN_MIC_BTN:
        inputSource = 1;
        enc0->changePrecision(MIC_GAIN_MAX, inputGain[inputSource], false);
        toggleButton(m_pElemAudioinLineInBtn, false);
        toggleButton(m_pElemAudioinMicBtn, true);
        sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
        setInputGain(inputGain[1]);
        break;
    case E_ELEM_AUDIOIN_LM_VOL:
        temp = gslc_ElemXSeekbarGetPos(&m_gui, m_pElemAudioinLmVol);
        updateInputVol(InputTracks::LINEMIC_IN, INPUT_VOL_MAX - temp);
        enc1->setCurrentReading(INPUT_VOL_MAX - temp);
        break;
    case E_ELEM_AUDIOIN_USB_VOL:
        temp = gslc_ElemXSeekbarGetPos(&m_gui, m_pElemAudioinUsbVol);
        updateInputVol(InputTracks::USB_IN, INPUT_VOL_MAX - temp);
        enc2->setCurrentReading(INPUT_VOL_MAX - temp);
        break;
    }
}

void AudioinPage::onCCReceive(u_int8_t channel, u_int8_t control, u_int8_t value)
{
}

void AudioinPage::configurePage()
{
    // input source, gain and volume may be changed by synth for velocity, need to change back.
    sgtl5000_1.inputSelect(inputSource);
    setInputGain(inputGain[inputSource]);
    updateInputVol(InputTracks::LINEMIC_IN, inputVol[0]);

    switches.changeEncoderPrecision(0, inputSource ? MIC_GAIN_MAX : LINE_GAIN_MAX, inputGain[inputSource], false);
    switches.changeEncoderPrecision(1, INPUT_VOL_MAX, inputVol[0], false);
    switches.changeEncoderPrecision(2, INPUT_VOL_MAX, inputVol[1], false);
}

void AudioinPage::update()
{
    floatStereo temp;
    float temp_peak[2];
    for (uint8_t i = 0; i < 2; i++)
    {
        temp = AudioIO.getInputPeak((InputTracks)i);
        temp_peak[0] = temp.l;
        temp_peak[1] = temp.r;
        for (uint8_t j = 0; j < 2; j++)
        {
            // peak level meter
            if (temp_peak[j] >= 0)
            {
                // convert to dB
                temp_peak[j] = 20 * log10f(temp_peak[j]);
                if (temp_peak[j] >= -0.1)
                    peakHold[i][j] = PEAK_HOLD_TIME;
                gslc_ElemXProgressSetVal(&m_gui, peakBar[i][j], map(temp_peak[j], -50, 0, 0, 100));
            }
            // peak indicator
            if (peakHold[i][j] > 0)
            {
                peakHold[i][j]--;
                gslc_ElemSetCol(&m_gui, peakBox[i][j], GSLC_COL_GRAY, GSLC_COL_RED, GSLC_COL_RED);
            }
            else
            {
                gslc_ElemSetCol(&m_gui, peakBox[i][j], GSLC_COL_GRAY, GSLC_COL_BLACK, GSLC_COL_BLACK);
            }
        }
    }
}

void AudioinPage::draw()
{
}

void AudioinPage::init()
{
    pageID = E_PG_AUDIOIN;
    strcpy(pageName, "Audio Input");

    inputSource = 0;
    toggleButton(m_pElemAudioinLineInBtn, true);
    toggleButton(m_pElemAudioinMicBtn, false);
    sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
    setInputGain(inputGain[0]);

    updateInputVol(InputTracks::LINEMIC_IN, inputVol[0]);
    updateInputVol(InputTracks::USB_IN, inputVol[1]);
    gslc_ElemXSeekbarSetPos(&m_gui, m_pElemAudioinLmVol, INPUT_VOL_MAX - inputVol[0]);
    gslc_ElemXSeekbarSetPos(&m_gui, m_pElemAudioinUsbVol, INPUT_VOL_MAX - inputVol[1]);
    setPFL(usePFL);

    peakBox[InputTracks::LINEMIC_IN][0] = gslc_PageFindElemById(&m_gui, E_PG_AUDIOIN, E_ELEM_AUDIOIN_LM_PEAK_L_BOX);
    peakBox[InputTracks::LINEMIC_IN][1] = gslc_PageFindElemById(&m_gui, E_PG_AUDIOIN, E_ELEM_AUDIOIN_LM_PEAK_R_BOX);
    peakBox[InputTracks::USB_IN][0] = gslc_PageFindElemById(&m_gui, E_PG_AUDIOIN, E_ELEM_AUDIOIN_USB_PEAK_L_BOX);
    peakBox[InputTracks::USB_IN][1] = gslc_PageFindElemById(&m_gui, E_PG_AUDIOIN, E_ELEM_AUDIOIN_USB_PEAK_R_BOX);

    peakBar[InputTracks::LINEMIC_IN][0] = m_pElemAudioinLmLBar;
    peakBar[InputTracks::LINEMIC_IN][1] = m_pElemAudioinLmRBar;
    peakBar[InputTracks::USB_IN][0] = m_pElemAudioinUsbLBar;
    peakBar[InputTracks::USB_IN][1] = m_pElemAudioinUsbRBar;
}

void AudioinPage::setInputGain(uint8_t value)
{
    inputGain[inputSource] = value;
    sgtl5000_1.micGain(value);
    uint8_t temp;
    if (inputSource == 0)
        temp = map(value, 0, 15, 0, 63); // the range of GUI ring is 0~63, need to map when displaying line gain (0~15)
    else
        temp = value;
    gslc_ElemXRingGaugeSetVal(&m_gui, m_pElemAudioinGainRing, temp);
    gslc_ElemSetTxtStr(&m_gui, m_pElemAudioinGainRing, String(value).c_str());
}

void AudioinPage::setPFL(bool flag)
{
    usePFL = flag;
    toggleButton(m_pElemAudioinPflBtn, flag);
    if (usePFL)
    {
        AudioIO.setInputLevelMode(LevelMeterMode::PRE_FADER);
    }
    else
    {
        AudioIO.setInputLevelMode(LevelMeterMode::POST_FADER);
    }
}

void AudioinPage::updateInputVol(InputTracks track, uint8_t value)
{
    gslc_tsElemRef *txtRef = nullptr;
    switch (track)
    {
    case InputTracks::LINEMIC_IN:
        txtRef = m_pElemAudioinLmVolTxt;
        break;
    case InputTracks::USB_IN:
        txtRef = m_pElemAudioinUsbVolTxt;
        break;
    }

    inputVol[track] = value;
    // mute
    if (value == 0)
    {
        AudioIO.setInputVolume(track, 0);
        gslc_ElemSetTxtStr(&m_gui, txtRef, "Mute");
    }
    else
    {
        // convert to gain
        int db = value - INPUT_VOL_MAX + 10; // slider ranges from -50 dB to +10 dB
        float temp = pow10f(db * 0.05);
        AudioIO.setInputVolume(track, temp);
        gslc_ElemSetTxtStr(&m_gui, txtRef, String(db).c_str());
    }
}
