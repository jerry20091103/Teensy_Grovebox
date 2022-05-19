#include "AudiooutPage.h"
#include "Hardware.h"
#include "Controls.h"

void AudiooutPage::onBtnPressed(uint8_t pin)
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
            PageManager.switchPage(E_PG_AUDIOIN);
            break;
        case BTN_JOY:
            PageManager.PageArr[PageManager.lastPage]->onBtnPressed(pin);
            break;
        }
    }
}

void AudiooutPage::onBtnHold(uint8_t pin)
{
    switch (pin)
    {
    case BTN_PWR:
        PageManager.showPopup(E_PG_POPUP_POWER);
        break;
    }
}

void AudiooutPage::onBtnReleased(uint8_t pin)
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

void AudiooutPage::onEncTurned(uint8_t id, int value)
{
    switch (id)
    {
    case 0:
        // analog out volume
        gslc_ElemXSeekbarSetPos(&m_gui, m_pElemAudiooutLineVol, MASTER_VOL_MAX - value); // the seek bar has reverse value (64 ~ 0)
        updateOutVolume(MasterTracks::ANALOG_OUT, value);
        break;
    case 1:
        // USB out volume
        gslc_ElemXSeekbarSetPos(&m_gui, m_pElemAudiooutUsbVol, MASTER_VOL_MAX - value);
        updateOutVolume(MasterTracks::USB_OUT, value);
        break;
    case 2:
        // hp voulme
        updateHpVol(value);
        break;
    case 3:
        break;
    }
}

void AudiooutPage::onJoyUpdate(int joy_x, int joy_y)
{
}

void AudiooutPage::onTouch(int ref)
{
    int temp;
    switch (ref)
    {
    case E_ELEM_BASE_BACK_BTN:
        PageManager.switchPage(PageManager.lastPage);
        break;
    case E_ELEM_AUDIOOUT_LINE_VOL:
        temp = gslc_ElemXSeekbarGetPos(&m_gui, m_pElemAudiooutLineVol);
        updateOutVolume(MasterTracks::ANALOG_OUT, MASTER_VOL_MAX - temp);
        enc0->setCurrentReading(MASTER_VOL_MAX - temp);
        break;
    case E_ELEM_AUDIOOUT_USB_VOL:
        temp = gslc_ElemXSeekbarGetPos(&m_gui, m_pElemAudiooutUsbVol);
        updateOutVolume(MasterTracks::USB_OUT, MASTER_VOL_MAX - temp);
        enc1->setCurrentReading(MASTER_VOL_MAX - temp);
        break;
    case E_ELEM_AUDIOOUT_PREFADER_BTN:
        usePFL = !usePFL;
        setPFL(usePFL);
        break;
    case E_ELEM_AUDIOOUT_PP_BTN:
        // TODO go to post processing popup
        break;
    case E_ELEM_AUDIOOUT_ANALOG_BTN:
        PageManager.pageParam = 0;
        PageManager.showPopup(E_PG_POPUP_OUT_MIXER);
        break;
    case E_ELEM_AUDIOOUT_USB_BTN:
        PageManager.pageParam = 1;
        PageManager.showPopup(E_PG_POPUP_OUT_MIXER);
        break;
    }
}

void AudiooutPage::onCCReceive(u_int8_t channel, u_int8_t control, u_int8_t value)
{
}

void AudiooutPage::configurePage()
{
    switches.changeEncoderPrecision(0, MASTER_VOL_MAX, analogOutVol, false);
    switches.changeEncoderPrecision(1, MASTER_VOL_MAX, usbOutVol, false);
    switches.changeEncoderPrecision(2, 50, hpVol, false);
}

void AudiooutPage::update()
{
    // read peak and rms data
    float temp_rms;
    float temp_peak[2];
    floatStereo temp;
    for (uint8_t i = 0; i < 2; i++)
    {
        temp = AudioIO.getMasterPeak((MasterTracks)i);
        temp_peak[0] = temp.l;
        temp_peak[1] = temp.r;
        temp = AudioIO.getMasterRMS((MasterTracks)i);
        temp_rms = max(temp.l, temp.r);
        // peak for left and right channel
        for (uint8_t j = 0; j < 2; j++)
        {
            if (temp_peak[j] >= 0)
            {
                // convert to dB
                temp_peak[j] = 20 * log10f(temp_peak[j]);
                if (temp_peak[j] >= 0.1)
                    peakHold[i][j] = PEAK_HOLD_TIME;
                gslc_ElemXProgressSetVal(&m_gui, peakBar[i][j], map(temp_peak[j], -52, 0, 0, 100));
            }
            // peak indicator
            if (peakHold[i][j] > 0)
                peakHold[i][j]--;
            togglePeakBox(peakBox[i][j], (bool)peakHold[i][j]);
        }
        // one rms value that takes max of two channels
        if (temp_rms >= 0)
        {
            // calculate running average
            temp_rms = (temp_rms + rmsAvg[i] * RMS_AVG_TIME) / (RMS_AVG_TIME + 1);
            rmsAvg[i] = temp_rms;
            // convert to dB
            temp_rms  = 20 * log10f(temp_rms);
            gslc_ElemXProgressSetVal(&m_gui, rmsBar[i], map(temp_rms, -52, 0, 0, 100));
        }
    }
}

void AudiooutPage::draw()
{
}

void AudiooutPage::init()
{
    pageID = E_PG_AUDIOOUT;
    strcpy(pageName, "Audio Output");

    updateHpVol(hpVol);

    updateOutVolume(MasterTracks::ANALOG_OUT, analogOutVol);
    updateOutVolume(MasterTracks::USB_OUT, usbOutVol);
    gslc_ElemXSeekbarSetPos(&m_gui, m_pElemAudiooutLineVol, MASTER_VOL_MAX - analogOutVol);
    gslc_ElemXSeekbarSetPos(&m_gui, m_pElemAudiooutUsbVol, MASTER_VOL_MAX - usbOutVol);
    setPFL(usePFL);

    peakBox[MasterTracks::ANALOG_OUT][0] = gslc_PageFindElemById(&m_gui, E_PG_AUDIOOUT, E_ELEM_AUDIOOUT_LINE_PEAK_L_BOX);
    peakBox[MasterTracks::ANALOG_OUT][1] = gslc_PageFindElemById(&m_gui, E_PG_AUDIOOUT, E_ELEM_AUDIOOUT_LINE_PEAK_R_BOX);
    peakBox[MasterTracks::USB_OUT][0] = gslc_PageFindElemById(&m_gui, E_PG_AUDIOOUT, E_ELEM_AUDIOOUT_USB_PEAK_L_BOX);
    peakBox[MasterTracks::USB_OUT][1] = gslc_PageFindElemById(&m_gui, E_PG_AUDIOOUT, E_ELEM_AUDIOOUT_USB_PEAK_R_BOX);

    peakBar[MasterTracks::ANALOG_OUT][0] = m_pElemAudiooutLineLBar;
    peakBar[MasterTracks::ANALOG_OUT][1] = m_pElemAudiooutLineRBar;
    peakBar[MasterTracks::USB_OUT][0] = m_pElemAudiooutUsbLBar;
    peakBar[MasterTracks::USB_OUT][1] = m_pElemAudiooutUsbRBar;

    rmsBar[MasterTracks::ANALOG_OUT] = m_pElemAudiooutLinePeakBar;
    rmsBar[MasterTracks::USB_OUT] = m_pElemAudiooutUsbPeakBar;
}

void AudiooutPage::updateHpVol(uint8_t newVal)
{
    // mute
    if (newVal == 0)
    {
        sgtl5000_1.volume(0);
    }
    else
    {
        // convert to gain
        float temp = newVal;
        sgtl5000_1.volume(map((float)temp, 0, 50, 0, 0.8));
    }
    gslc_ElemXRingGaugeSetVal(&m_gui, m_pElemAudiooutHpVolRing, newVal * 2); // x2 here to show '%'
    gslc_ElemSetTxtStr(&m_gui, m_pElemAudiooutHpVolRing, String(newVal * 2).c_str());
    hpVol = newVal;
}

void AudiooutPage::updateOutVolume(MasterTracks track, uint8_t newVal)
{
    switch (track)
    {
    case MasterTracks::ANALOG_OUT:
        analogOutVol = newVal;
        // mute
        if (newVal == 0)
        {
            AudioIO.setMasterVolume(MasterTracks::ANALOG_OUT, 0);
            gslc_ElemSetTxtStr(&m_gui, m_pElemAudiooutLineVolTxt, "Mute");
        }
        else
        {
            // convert to gain
            int db = newVal - MASTER_VOL_MAX + 10; // slider ranges from -52 dB to +10 dB
            float temp = pow10f(db * 0.05);
            AudioIO.setMasterVolume(MasterTracks::ANALOG_OUT, temp);
            gslc_ElemSetTxtStr(&m_gui, m_pElemAudiooutLineVolTxt, String(db).c_str());
        }
        break;
    case MasterTracks::USB_OUT:
        usbOutVol = newVal;
        // mute
        if (newVal == 0)
        {
            AudioIO.setMasterVolume(MasterTracks::USB_OUT, 0);
            gslc_ElemSetTxtStr(&m_gui, m_pElemAudiooutUsbVolTxt, "Mute");
        }
        else
        {
            // convert to gain
            int db = newVal - MASTER_VOL_MAX + 10; // slider ranges from -52 dB to +10 dB
            float temp = pow10f(db * 0.05);
            AudioIO.setMasterVolume(MasterTracks::USB_OUT, temp);
            gslc_ElemSetTxtStr(&m_gui, m_pElemAudiooutUsbVolTxt, String(db).c_str());
        }
        break;
    }
}

void AudiooutPage::setPFL(bool flag)
{
    usePFL = flag;
    toggleButton(m_pElemAudiooutPrefaderBtn, flag);
    if (usePFL)
    {
        AudioIO.setMasterLevelMode(LevelMeterMode::PRE_FADER);
    }
    else
    {
        AudioIO.setMasterLevelMode(LevelMeterMode::POST_FADER);
    }
}
