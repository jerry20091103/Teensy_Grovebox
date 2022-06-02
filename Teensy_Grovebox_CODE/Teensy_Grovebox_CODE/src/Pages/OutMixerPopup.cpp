#include "OutMixerPopup.h"
#include "Hardware.h"
#include "Controls.h"
#include "Audio/AudioUtility.h"

void OutMixerPopup::onBtnPressed(uint8_t pin)
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
        case BTN_FN0:
            onTouch(E_ELEM_OUT_MIXER_PAN_BTN);
            break;
        case BTN_JOY:
            PageManager.PageArr[PageManager.lastPage]->onBtnPressed(pin);
        break;;
        }
    }
}

void OutMixerPopup::onBtnHold(uint8_t pin)
{
}

void OutMixerPopup::onBtnReleased(uint8_t pin)
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

void OutMixerPopup::onEncTurned(uint8_t id, int value)
{
    switch (id)
    {
    case 0:
        if (adjustingPan)
        {
            gslc_ElemXSeekbarSetPos(&m_gui, m_pElemOutMixerLmPan, value);
            updateTrackPan(MixerTracks::I2S, value);
        }
        else
        {
            gslc_ElemXSeekbarSetPos(&m_gui, m_pElemOutMixerLmVol, TRACK_VOL_MAX - value);
            updateTrackVol(MixerTracks::I2S, value);
        }
        break;
    case 1:
        if (adjustingPan)
        {
            gslc_ElemXSeekbarSetPos(&m_gui, m_pElemOutMixerUsbPan, value);
            updateTrackPan(MixerTracks::USB, value);
        }
        else
        {
            gslc_ElemXSeekbarSetPos(&m_gui, m_pElemOutMixerUsbVol, TRACK_VOL_MAX - value);
            updateTrackVol(MixerTracks::USB, value);
        }
        break;
    case 2:
        if (adjustingPan)
        {
            gslc_ElemXSeekbarSetPos(&m_gui, m_pElemOutMixerInsPan, value);
            updateTrackPan(MixerTracks::INSTRUMENTS, value);
        }
        else
        {
            gslc_ElemXSeekbarSetPos(&m_gui, m_pElemOutMixerInsVol, TRACK_VOL_MAX - value);
            updateTrackVol(MixerTracks::INSTRUMENTS, value);
        }
        break;
        // TODO: Other tracks
    }
}

void OutMixerPopup::onJoyUpdate(int joy_x, int joy_y)
{
}

void OutMixerPopup::onTouch(int ref)
{
    int temp;
    switch (ref)
    {
    case E_ELEM_OUT_MIXER_BACK_BTN:
        PageManager.hidePopup();
        break;
    case E_ELEM_OUT_MIXER_PFL_BTN:
        usePFL = !usePFL;
        setPFL(usePFL);
        break;
    case E_ELEM_OUT_MIXER_PAN_BTN:
        adjustingPan = !adjustingPan;
        changeEncState(adjustingPan);
        break;
    case E_ELEM_OUT_MIXER_LM_VOL:
        temp = gslc_ElemXSeekbarGetPos(&m_gui, m_pElemOutMixerLmVol);
        updateTrackVol(MixerTracks::I2S, TRACK_VOL_MAX - temp);
        if (!adjustingPan)
            enc0->setCurrentReading(TRACK_VOL_MAX - temp);
        break;
    case E_ELEM_OUT_MIXER_USB_VOL:
        temp = gslc_ElemXSeekbarGetPos(&m_gui, m_pElemOutMixerUsbVol);
        updateTrackVol(MixerTracks::USB, TRACK_VOL_MAX - temp);
        if (!adjustingPan)
            enc1->setCurrentReading(TRACK_VOL_MAX - temp);
        break;
    case E_ELEM_OUT_MIXER_INS_VOL:
        temp = gslc_ElemXSeekbarGetPos(&m_gui, m_pElemOutMixerInsVol);
        updateTrackVol(MixerTracks::INSTRUMENTS, TRACK_VOL_MAX - temp);
        if (!adjustingPan)
            enc2->setCurrentReading(TRACK_VOL_MAX - temp);
        break;
        // TODO: volume for Other tracks

    case E_ELEM_OUT_MIXER_LM_PAN:
        temp = gslc_ElemXSeekbarGetPos(&m_gui, m_pElemOutMixerLmPan);
        updateTrackPan(MixerTracks::I2S, temp);
        if (adjustingPan)
            enc0->setCurrentReading(temp);
        break;
    case E_ELEM_OUT_MIXER_USB_PAN:
        temp = gslc_ElemXSeekbarGetPos(&m_gui, m_pElemOutMixerUsbPan);
        updateTrackPan(MixerTracks::USB, temp);
        if (adjustingPan)
            enc1->setCurrentReading(temp);
        break;
    case E_ELEM_OUT_MIXER_INS_PAN:
        temp = gslc_ElemXSeekbarGetPos(&m_gui, m_pElemOutMixerInsPan);
        updateTrackPan(MixerTracks::INSTRUMENTS, temp);
        if (adjustingPan)
            enc2->setCurrentReading(temp);
        break;
        // TODO: pan for Other tracks
    }
}

void OutMixerPopup::onCCReceive(u_int8_t channel, u_int8_t control, u_int8_t value)
{
}

void OutMixerPopup::configurePage()
{
    // set title
    if (PageManager.pageParam == 0)
    {
        strcpy(pageName, "Analog Out Mixer");
        currentMasterTrack = MasterTracks::ANALOG_OUT;
    }
    else if (PageManager.pageParam == 1)
    {
        strcpy(pageName, "USB Out Mixer");
        currentMasterTrack = MasterTracks::USB_OUT;
    }
    gslc_ElemSetTxtStr(&m_gui, m_pElemOutMixerTitleTxt, pageName);
    setPFL(usePFL);
    // set pan state
    changeEncState(adjustingPan);
    // set current volume and pan level
    // TODO: add more tracks
    gslc_ElemXSeekbarSetPos(&m_gui, m_pElemOutMixerLmVol, TRACK_VOL_MAX - trackVol[currentMasterTrack][0]);
    gslc_ElemXSeekbarSetPos(&m_gui, m_pElemOutMixerUsbVol, TRACK_VOL_MAX - trackVol[currentMasterTrack][1]);
    gslc_ElemXSeekbarSetPos(&m_gui, m_pElemOutMixerInsVol, TRACK_VOL_MAX - trackVol[currentMasterTrack][2]);

    gslc_ElemXSeekbarSetPos(&m_gui, m_pElemOutMixerLmPan, trackPan[currentMasterTrack][0]);
    gslc_ElemXSeekbarSetPos(&m_gui, m_pElemOutMixerUsbPan, trackPan[currentMasterTrack][1]);
    gslc_ElemXSeekbarSetPos(&m_gui, m_pElemOutMixerInsPan, trackPan[currentMasterTrack][2]);
}

void OutMixerPopup::update()
{
    floatStereo temp;
    float temp_peak[2];
    // TODO: add more tracks
    for (uint8_t i = 0; i < 3; i++)
    {
        temp = AudioIO.getMixerPeak(currentMasterTrack, (MixerTracks)i);
        temp_peak[0] = temp.l;
        temp_peak[1] = temp.r;
        for (uint8_t j = 0; j < 2; j++)
        {
            // peak level meter
            if (temp_peak[j] >= 0)
            {
                // convert to dB
                temp_peak[j] = gaintodB(temp_peak[j]);
                if (temp_peak[j] >= -0.1)
                    peakHold[i][j] = PEAK_HOLD_TIME;
                gslc_ElemXProgressSetVal(&m_gui, peakBar[i][j], map(temp_peak[j], -50, 0, 0, 100));
            }
            // peak indicator
            if (peakHold[i][j] > 0)
            {
                peakHold[i][j]--;
            }
            togglePeakBox(peakBox[i][j], (bool)peakHold[i][j]);
        }
    }
}

void OutMixerPopup::draw()
{
}

void OutMixerPopup::init()
{
    pageID = E_PG_POPUP_OUT_MIXER;
    strcpy(pageName, "Analog Out Mixer");
    gslc_ElemSetTxtStr(&m_gui, m_pElemOutMixerTitleTxt, pageName);
    for (uint8_t i = 0; i < 4; i++)
    {
        currentMasterTrack = MasterTracks::USB_OUT;
        updateTrackVol((MixerTracks)i, trackVol[currentMasterTrack][i]);
        updateTrackPan((MixerTracks)i, trackPan[currentMasterTrack][i]);
        currentMasterTrack = MasterTracks::ANALOG_OUT;
        updateTrackVol((MixerTracks)i, trackVol[currentMasterTrack][i]);
        updateTrackPan((MixerTracks)i, trackPan[currentMasterTrack][i]);
    }
    setPFL(usePFL);

    gslc_ElemXSeekbarSetPos(&m_gui, m_pElemOutMixerLmVol, TRACK_VOL_MAX - trackVol[currentMasterTrack][0]);
    gslc_ElemXSeekbarSetPos(&m_gui, m_pElemOutMixerUsbVol, TRACK_VOL_MAX - trackVol[currentMasterTrack][1]);

    gslc_ElemXSeekbarSetPos(&m_gui, m_pElemOutMixerLmPan, trackPan[currentMasterTrack][0]);
    gslc_ElemXSeekbarSetPos(&m_gui, m_pElemOutMixerUsbPan, trackPan[currentMasterTrack][1]);

    // TODO: add more tracks
    peakBox[MixerTracks::I2S][0] = gslc_PageFindElemById(&m_gui, E_PG_POPUP_OUT_MIXER, E_ELEM_OUT_MIXER_LM_PEAK_L_BOX);
    peakBox[MixerTracks::I2S][1] = gslc_PageFindElemById(&m_gui, E_PG_POPUP_OUT_MIXER, E_ELEM_OUT_MIXER_LM_PEAK_R_BOX);
    peakBox[MixerTracks::USB][0] = gslc_PageFindElemById(&m_gui, E_PG_POPUP_OUT_MIXER, E_ELEM_OUT_MIXER_USB_PEAK_L_BOX);
    peakBox[MixerTracks::USB][1] = gslc_PageFindElemById(&m_gui, E_PG_POPUP_OUT_MIXER, E_ELEM_OUT_MIXER_USB_PEAK_L_BOX);
    peakBox[MixerTracks::INSTRUMENTS][0] = gslc_PageFindElemById(&m_gui, E_PG_POPUP_OUT_MIXER, E_ELEM_OUT_MIXER_INS_PEAK_L_BOX);
    peakBox[MixerTracks::INSTRUMENTS][1] = gslc_PageFindElemById(&m_gui, E_PG_POPUP_OUT_MIXER, E_ELEM_OUT_MIXER_INS_PEAK_L_BOX);

    peakBar[MixerTracks::I2S][0] = m_pElemOutMixerLmLBar;
    peakBar[MixerTracks::I2S][1] = m_pElemOutMixerLmRBar;
    peakBar[MixerTracks::USB][0] = m_pElemOutMixerUsbLBar;
    peakBar[MixerTracks::USB][1] = m_pElemOutMixerUsbRBar;
    peakBar[MixerTracks::INSTRUMENTS][0] = m_pElemOutMixerInsLBar;
    peakBar[MixerTracks::INSTRUMENTS][1] = m_pElemOutMixerInsRBar;
}

void OutMixerPopup::setPFL(bool flag)
{
    usePFL = flag;
    toggleButton(m_pElemOutMixerPflBtn, flag);
    if (usePFL)
    {
        AudioIO.setMixerLevelMode(LevelMeterMode::PRE_FADER);
    }
    else
    {
        AudioIO.setMixerLevelMode(LevelMeterMode::POST_FADER);
    }
}

void OutMixerPopup::updateTrackVol(MixerTracks track, uint8_t value)
{
    trackVol[currentMasterTrack][track] = value;
    gslc_tsElemRef *txtRef = NULL;

    switch (track)
    {
    case MixerTracks::I2S:
        txtRef = m_pElemOutMixerLmVolTxt;
        break;
    case MixerTracks::USB:
        txtRef = m_pElemOutMixerUsbVolTxt;
        break;
    case MixerTracks::INSTRUMENTS:
        txtRef = m_pElemOutMixerInsVolTxt;
        break;
    case MixerTracks::RECORDER:
        // TODO
        break;
    }
    // mute
    if (txtRef != NULL)
    {
        if (value == 0)
        {
            AudioIO.setMixerVolume(currentMasterTrack, track, 0);
            gslc_ElemSetTxtStr(&m_gui, txtRef, "Mute");
        }
        else
        {
            // convert to gain
            int db = value - TRACK_VOL_MAX + 10; // slider ranges from -52 dB to +10 dB
            float temp = dBtoGain(db);
            AudioIO.setMixerVolume(currentMasterTrack, track, temp);
            gslc_ElemSetTxtStr(&m_gui, txtRef, String(db).c_str());
        }
    }
}

void OutMixerPopup::updateTrackPan(MixerTracks track, uint8_t value)
{
    trackPan[currentMasterTrack][track] = value;
    AudioIO.setMixerPan(currentMasterTrack, track, map((float)value, 0, TRACK_PAN_MAX, -1, 1));
}

void OutMixerPopup::changeEncState(bool pan)
{
    if (pan)
    {
        for (uint8_t i = 0; i < 4; i++)
        {
            switches.changeEncoderPrecision(i, TRACK_PAN_MAX, trackPan[currentMasterTrack][i], false);
        }
        gslc_ElemSetCol(&m_gui, m_pElemOutMixerPanBtn, GSLC_COL_RED_LT2, GSLC_COL_RED_LT2, GSLC_COL_GRAY);
        gslc_ElemSetTxtCol(&m_gui, m_pElemOutMixerPanBtn, GSLC_COL_BLACK);
    }
    else
    {
        for (uint8_t i = 0; i < 4; i++)
        {
            switches.changeEncoderPrecision(i, TRACK_VOL_MAX, trackVol[currentMasterTrack][i], false);
        }
        gslc_ElemSetCol(&m_gui, m_pElemOutMixerPanBtn, GSLC_COL_WHITE, GSLC_COL_BLACK, GSLC_COL_GRAY);
        gslc_ElemSetTxtCol(&m_gui, m_pElemOutMixerPanBtn, GSLC_COL_WHITE);
    }
}