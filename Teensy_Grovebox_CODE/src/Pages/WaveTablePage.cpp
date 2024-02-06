#include "WaveTablePage.h"
#include "Hardware.h"
#include "Controls.h"
#include "Audio/AudioSynth.h"
#include "Audio/AudioIO.h"
#include "Audio/AudioUtility.h"
#include "SF2_Samples/SF2_Samples.h"

void WaveTablePage::onVelocityBtnPressed(void *targetPointer, lv_obj_t *labelObj, bool isToggled)
{
    WaveTablePage *instance = (WaveTablePage *)targetPointer;
    instance->useVelocity = isToggled;
    AudioSynth.setUseVelocity(instance->useVelocity);
}

void WaveTablePage::onPitchBtnPressed(void *targetPointer, lv_obj_t *labelObj, bool isToggled)
{
    WaveTablePage *instance = (WaveTablePage *)targetPointer;
    instance->usePitchbend = isToggled;
    if(!instance->usePitchbend)
        AudioSynth.pitchbend(0, 0);
}

void WaveTablePage::onPitchBtnHolded(void *targetPointer, lv_obj_t *labelObj)
{
    WaveTablePage *instance = (WaveTablePage *)targetPointer;
    lv_dropdown_open(instance->pitchDropdown);
}

void WaveTablePage::onPitchDropdownSelect(lv_event_t *e)
{
    WaveTablePage *instance = (WaveTablePage *)lv_event_get_user_data(e);
    lv_obj_t * dropdown = lv_event_get_target(e);
    uint8_t id = lv_dropdown_get_selected(dropdown);
    instance->pitchbendRange = id + 1;
    lv_label_set_text_fmt(instance->pitchBtn->getLabelObject(), "Pitch: %d", instance->pitchbendRange);
}

void WaveTablePage::onOctaveSelect(void *targetPointer, lv_obj_t *valueTextObj, int16_t value)
{
    WaveTablePage *instance = (WaveTablePage *)targetPointer;
    lv_label_set_text_fmt(valueTextObj, "%d", value);
    instance->octave = value;
}

void WaveTablePage::onSF2DropdownSelect(lv_event_t *e)
{
    WaveTablePage *instance = (WaveTablePage *)lv_event_get_user_data(e);
    lv_obj_t * dropdown = lv_event_get_target(e);
    uint8_t id = lv_dropdown_get_selected(dropdown);
    AudioSynth.setSF2Instrument(id);
    instance->curInstrument = id;
}

void WaveTablePage::onVolArcTurned(void *targetPointer, lv_obj_t *valueTextObj, int16_t value, int8_t encoderIndex)
{
    WaveTablePage *instance = (WaveTablePage *)targetPointer;
    lv_label_set_text_fmt(valueTextObj, "%d", value);
    instance->setVolume(value);
}

void WaveTablePage::onBtnPressed(uint8_t pin)
{
    int noteNum;
    uint8_t keyNum = PinToKeyNum(pin);
    if (keyNum > 0)
    {
        noteNum = keyNum - 1 + 12 * octave;
        AudioSynth.noteOn(noteNum);
    }
    else
    {
        switch (pin)
        {
        case BTN_PWR:
            PageManager.switchPage(PG_AUDIO);
            break;
        case BTN_JOY:
            AudioSynth.sustainOn();
            break;
        case BTN_FN0:
            octaveSpinbox->pressButtonMinus();
            break;
        case BTN_FN1:
            octaveSpinbox->pressButtonPlus();
            break;
        }
    }
}

void WaveTablePage::onBtnHold(uint8_t pin)
{
    switch (pin)
    {
    case BTN_PWR:
        PageManager.showPowerPopup();
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
    encoderBindCallback(id, value);
}

void WaveTablePage::onJoyUpdate(int joy_x, int joy_y)
{
    if (usePitchbend)
    {
        AudioSynth.pitchbend(map((float)joy_x, 0, 1019, pitchbendRange, -pitchbendRange), joy_x);
    }
}

void WaveTablePage::onCCReceive(u_int8_t channel, u_int8_t control, u_int8_t value)
{
}

void WaveTablePage::configurePage()
{
    // todo: maybe move this to load()?
    // setup micorphone for velocity sensing
    sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
    sgtl5000_1.micGain(40);
    AudioIO.setInputVolume(InputTracks::LINEMIC_IN, 0);
    // setup peak module for level meter
    AudioIO.setMixerLevelMode(LevelMeterMode::PRE_FADER);
    setVolume(volume);
    // update current velocity settings
    AudioSynth.setUseVelocity(useVelocity);
    // set reverb FX
    AudioFX.reverb.setWithMem(&reverbMem);
    // set voice mode for AudioSynth
    AudioSynth.setVoiceMode(VOICE_MODE_WAVETABLE);
}

void WaveTablePage::setUserData()
{

}

void WaveTablePage::update()
{
    float temp_peak = AudioIO.getMixerPeak(MasterTracks::ANALOG_OUT, MixerTracks::INSTRUMENTS).l;
    if (temp_peak >= 0)
        volBar->setVolume(temp_peak);
}

void WaveTablePage::init()
{
    pageID = PG_WAVE;
    strcpy(pageName, "Wave Table Synth");
    // create screen
    screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen, lv_color_black(), 0);
}

void WaveTablePage::load()
{
    // Group the objects in the select area
    selectGroup = lv_obj_create(screen);
    lv_obj_set_style_bg_color(selectGroup, lv_color_black(), 0);
    lv_obj_set_style_pad_all(selectGroup, 5, 0);
    lv_obj_set_size(selectGroup, 320, 100);
    lv_obj_set_y(selectGroup, 35);

    lv_obj_t *label;

    // *drop down menu for sound selection
    sf2SelectDropdown = lv_dropdown_create(selectGroup);
    lv_obj_set_x(sf2SelectDropdown, 60);
    lv_obj_set_width(sf2SelectDropdown, 170);
    lv_obj_add_flag(sf2SelectDropdown, LV_OBJ_FLAG_OVERFLOW_VISIBLE);
    lv_dropdown_set_options_static(sf2SelectDropdown, SF2_Instrument_Names);
    lv_obj_add_event_cb(sf2SelectDropdown, onSF2DropdownSelect, LV_EVENT_VALUE_CHANGED, this);
    label = lv_label_create(sf2SelectDropdown);
    lv_label_set_text(label, "Sound:");
    lv_obj_align(label, LV_ALIGN_LEFT_MID, -70, 0);
    // set dropdown value
    lv_dropdown_set_selected(sf2SelectDropdown, curInstrument);
    lv_event_send(sf2SelectDropdown, LV_EVENT_VALUE_CHANGED, NULL);

    // *volume arc
    volArc = new ParamArc(selectGroup, 4, "Gain", "dB", false);
    volArc->setRange(-15, 15);
    volArc->bindEncoder(3);
    volArc->setCallback(onVolArcTurned, this);
    volArc->setValue(volume);
    lv_obj_align(volArc->getLvglObject(), LV_ALIGN_TOP_RIGHT, -5, 20);

    // *octave select
    label = lv_label_create(selectGroup);
    lv_label_set_text(label, "Octave");
    lv_obj_set_style_text_font(label, font_small, 0);
    lv_obj_set_pos(label, 23, 38);
    octaveSpinbox = new Spinbox(selectGroup, 1);
    octaveSpinbox->setRange(1, 8);
    octaveSpinbox->setCallback(onOctaveSelect, this);
    octaveSpinbox->setValue(octave);
    lv_obj_align(octaveSpinbox->getLvglObject(), LV_ALIGN_BOTTOM_LEFT, 0, 0);

    // *velocity button
    velocityBtn = new Button(selectGroup, 60, 30, "Velocity", true);
    velocityBtn->setPressedCallback(onVelocityBtnPressed, this);
    velocityBtn->setToggle(useVelocity);
    lv_obj_align(velocityBtn->getLvglObject(), LV_ALIGN_BOTTOM_LEFT, 100, 0);
    lv_obj_set_style_text_font(velocityBtn->getLabelObject(), font_small, 0);

    // *pitch bend button
    // add a dropdown right under it
    pitchDropdown = lv_dropdown_create(selectGroup);
    lv_obj_set_size(pitchDropdown, 60, 30);
    lv_obj_align(pitchDropdown, LV_ALIGN_BOTTOM_LEFT, 170, 0);
    lv_dropdown_set_options(pitchDropdown, "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12");
    lv_obj_add_event_cb(pitchDropdown, onPitchDropdownSelect, LV_EVENT_VALUE_CHANGED, this);
    pitchBtn = new Button(selectGroup, 60, 30, "Pitch", true);
    pitchBtn->setPressedCallback(onPitchBtnPressed, this);
    pitchBtn->setHoldCallback(onPitchBtnHolded, this);
    pitchBtn->setToggle(usePitchbend);
    lv_obj_align(pitchBtn->getLvglObject(), LV_ALIGN_BOTTOM_LEFT, 170, 0);
    lv_obj_set_style_text_font(pitchBtn->getLabelObject(), font_small, 0);
    // set dropdown value
    lv_dropdown_set_selected(pitchDropdown, pitchbendRange - 1);
    lv_event_send(pitchDropdown, LV_EVENT_VALUE_CHANGED, NULL);

    // *volume bar
    volBar = new VolumeBar(selectGroup, 130, 10);
    volBar->setRange(-50, 0);
    volBar->setSmoothing(2);
    lv_obj_align(volBar->getBarObject(), LV_ALIGN_BOTTOM_LEFT, 100, -35);
}

void WaveTablePage::unload()
{
    delete volArc;
    delete octaveSpinbox;
    delete velocityBtn;
    delete pitchBtn;
    delete volBar;
    lv_obj_clean(screen);
    volArc = NULL;
    octaveSpinbox = NULL;
    velocityBtn = NULL;
    pitchBtn = NULL;
    volBar = NULL;
    selectGroup = NULL;
}

void WaveTablePage::setVolume(int8_t value)
{
    volume = value;
    AudioSynth.setMasterVol(value);
}