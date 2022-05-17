#include "WaveTablePage.h"
#include "Hardware.h"
#include "Controls.h"
#include "AudioSynth.h"
#include "AudioIO.h"

void WaveTablePage::onBtnPressed(uint8_t pin)
{
    int noteNum;
    uint8_t keyNum = PinToKeyNum(pin);
    if (keyNum > 0)
    {
        noteNum = keyNum - 1 + 12 * octave;
        AudioSynth.noteOn(noteNum, velocity);
        Serial.println(noteNum);
    }
    else
    {
        switch (pin)
        {
        case BTN_PWR:
            PageManager.switchPage(E_PG_AUDIOOUT);
            break;
        case BTN_JOY:
            AudioSynth.sustainOn();
            break;
        }
    }
}

void WaveTablePage::onBtnHold(uint8_t pin)
{
    switch (pin)
    {
    case BTN_PWR:
        PageManager.showPopup(E_PG_POPUP_POWER);
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
}

void WaveTablePage::onJoyUpdate(int joy_x, int joy_y)
{
}

void WaveTablePage::onTouch(int ref)
{
    switch (ref)
    {
    case E_ELEM_BASE_BACK_BTN:
        PageManager.switchPage(E_PG_HOME);
        break;

    default:
        break;
    }
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
}

void WaveTablePage::update()
{
    // get velocity from microphone
    velocity =  rmsVelocity.read();
}

void WaveTablePage::draw()
{
}

void WaveTablePage::init()
{
    pageID = E_PG_WAVE;
    strcpy(pageName, "Wave Table Synth");
}
