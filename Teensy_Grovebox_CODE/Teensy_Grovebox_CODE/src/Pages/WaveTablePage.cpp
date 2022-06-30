#include "WaveTablePage.h"
#include "Hardware.h"
#include "Controls.h"
#include "Audio/AudioSynth.h"
#include "Audio/AudioIO.h"
#include "Audio/AudioUtility.h"

void WaveTablePage::onBtnPressed(uint8_t pin)
{
    int noteNum;
    uint8_t keyNum = PinToKeyNum(pin);
    if (keyNum > 0)
    {
        noteNum = keyNum - 1 + 12 * octave;
        AudioSynth.noteOn(noteNum);
        Serial.println(noteNum);
    }
    else
    {
        switch (pin)
        {
        case BTN_PWR:
            //PageManager.switchPage(E_PG_AUDIOOUT);
            break;
        case BTN_JOY:
            AudioSynth.sustainOn();
            break;
        case BTN_FN0:
            //onTouch(E_ELEM_WAVE_OCTAVE_DEC_BTN);
            break;
        case BTN_FN1:
            //onTouch(E_ELEM_WAVE_OCTAVE_INC_BTN);
            break;
        }
    }
}

void WaveTablePage::onBtnHold(uint8_t pin)
{
    switch (pin)
    {
    case BTN_PWR:
        //PageManager.showPopup(E_PG_POPUP_POWER);
        break;
    }
}

void WaveTablePage::onBtnReleased(uint8_t pin)
{
    uint8_t noteNum;
    uint8_t keyNum = PinToKeyNum(pin);
    if (keyNum > 0)
    {
        noteNum = keyNum - 1 + 12 * octave;
        AudioSynth.noteOff(noteNum);
    }
    else
    {
        switch (pin)
        {
        case BTN_JOY:
            AudioSynth.sustainOff();
            break;
        }
    }
}

void WaveTablePage::onEncTurned(uint8_t id, int value)
{
    switch (id)
    {
    case 3: // master out volume
        setVolume(value - 15);

        break;
    }
}

void WaveTablePage::onJoyUpdate(int joy_x, int joy_y)
{
}

void WaveTablePage::onCCReceive(u_int8_t channel, u_int8_t control, u_int8_t value)
{
}

void WaveTablePage::configurePage()
{
    // setup micorphone for velocity sensing
    sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
    sgtl5000_1.micGain(40);
    AudioIO.setInputVolume(InputTracks::LINEMIC_IN, 0);
    // setup peak module for level meter
    AudioIO.setMixerLevelMode(LevelMeterMode::PRE_FADER);
    setVolume(volume);
    enc[3]->changePrecision(30, volume + 15, false);
    // set reverb FX
    AudioFX.reverb.setWithMem(&reverbMem);
}

void WaveTablePage::update()
{
    float temp_peak = AudioIO.getMixerPeak(MasterTracks::ANALOG_OUT, MixerTracks::INSTRUMENTS).l;
    if (temp_peak >= 0)
    {
        // convert to dB
        float temp_dB = gaintodB(temp_peak);
        if (temp_dB >= -0.1)
            peakHold = PEAK_HOLD_TIME;
        // calulate running average
        temp_peak = (temp_peak + peakAvg * PEAK_AVG_TIME) / (PEAK_AVG_TIME + 1);
        peakAvg = temp_peak;
        //gslc_ElemXProgressSetVal(&m_gui, m_pElemWaveVolBar, map(gaintodB(temp_peak), -30, 0, 0, 100));
    }
    // peak indicator
    if (peakHold > 0)
        peakHold--;
    //togglePeakBox(peakBox, (bool)peakHold);
}

void WaveTablePage::init()
{
    //pageID = E_PG_WAVE;
    strcpy(pageName, "Wave Table Synth");

    //gslc_ElemSetTxtStr(&m_gui, m_pElemWaveOctaveTxt, String(octave).c_str());

    //peakBox = gslc_PageFindElemById(&m_gui, E_PG_WAVE, E_ELEM_WAVE_PEAK_BOX);
}

void WaveTablePage::setVolume(int8_t value)
{
    volume = value;
    AudioSynth.setMasterVol(value);
    // gslc_ElemXRingGaugeSetVal(&m_gui, m_pElemWaveVolRing, value + 15);
    // gslc_ElemSetTxtStr(&m_gui, m_pElemWaveVolRing, String(value).c_str());
}