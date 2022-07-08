#include "WaveTablePage.h"
#include "Hardware.h"
#include "Controls.h"
#include "Audio/AudioSynth.h"
#include "Audio/AudioIO.h"
#include "Audio/AudioUtility.h"
#include "SF2_Samples/SF2_Samples.h"

void WaveTablePage::onVelocityBtnPressed(lv_event_t *e)
{
    WaveTablePage *instance = (WaveTablePage *)lv_event_get_user_data(e);
    instance->useVelocity = !instance->useVelocity;
    AudioSynth.setUseVelocity(instance->useVelocity);
}

void WaveTablePage::onPitchBtnPressed(lv_event_t *e)
{
    WaveTablePage *instance = (WaveTablePage *)lv_event_get_user_data(e);
    instance->usePitchbend = !instance->usePitchbend;
    AudioSynth.setUsePitchbend(instance->usePitchbend);
}

void WaveTablePage::onPitchBtnHolded(lv_event_t *e)
{
    WaveTablePage *instance = (WaveTablePage *)lv_event_get_user_data(e);
    lv_dropdown_open(instance->pitchDropdown);
}

void WaveTablePage::onPitchDropdownSelect(lv_event_t *e)
{
    WaveTablePage *instance = (WaveTablePage *)lv_event_get_user_data(e);
    lv_obj_t * dropdown = lv_event_get_target(e);
    uint8_t id = lv_dropdown_get_selected(dropdown);
    instance->pitchbendRange = id + 1;
    lv_label_set_text_fmt(instance->pitchText, "Pitch: %d", instance->pitchbendRange);
}

void WaveTablePage::onOctaveSelect(lv_event_t *e)
{
    WaveTablePage *instance = (WaveTablePage *)lv_event_get_user_data(e);
    lv_obj_t *btn = lv_event_get_target(e);
    if (lv_obj_has_flag(btn, LV_OBJ_FLAG_USER_1))
    {
        // increase
        instance->onBtnPressed(BTN_FN1);
    }
    else
    {
        // decrease
        instance->onBtnPressed(BTN_FN0);
    }
}

void WaveTablePage::onSF2DropdownSelect(lv_event_t *e)
{
    lv_obj_t * dropdown = lv_event_get_target(e);
    uint8_t id = lv_dropdown_get_selected(dropdown);
    AudioSynth.setSF2Instrument(id);
}

void WaveTablePage::onVolArcPressed(lv_event_t *e)
{
    WaveTablePage *instance = (WaveTablePage *)lv_event_get_user_data(e);
    lv_obj_t *arc = lv_event_get_target(e);
    uint8_t value = lv_arc_get_value(arc);
    enc[3]->setCurrentReading(value);
    instance->setVolume(value - VOL_OFFSET);
}

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
            PageManager.switchPage(PG_AUDIO);
            break;
        case BTN_JOY:
            AudioSynth.sustainOn();
            break;
        case BTN_FN0:
            octave--;
            if (octave < 1)
            {
                octave = 1;
            }
            lv_label_set_text_fmt(octaveText, "%d", octave);
            break;
        case BTN_FN1:
            octave++;
            if (octave > 8)
            {
                octave = 8;
            }
            lv_label_set_text_fmt(octaveText, "%d", octave);
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
    switch (id)
    {
    case 3: // master out volume
        setVolume(value - VOL_OFFSET);
        lv_arc_set_value(volArc, value);
        break;
    }
}

void WaveTablePage::onJoyUpdate(int joy_x, int joy_y)
{
    if (usePitchbend)
    {
        AudioSynth.pitchbend(map((float)joy_x, 0, 1019, pitchbendRange, -pitchbendRange));
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
    // setup peak module for level meter
    AudioIO.setMixerLevelMode(LevelMeterMode::PRE_FADER);
    setVolume(volume);
    enc[3]->changePrecision(30, volume + VOL_OFFSET, false);
    // update current velocity settings
    AudioSynth.setUseVelocity(useVelocity);
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
        lv_bar_set_value(volBar, temp_dB, LV_ANIM_ON);
    }
    // peak indicator
    if (peakHold > 0)
    {
        // !the leds are buggy now, so use set color to toggle on/off
        lv_obj_set_style_bg_color(peakLed, color_Red, 0);
        peakHold--;
    }
    else
    {
        lv_obj_set_style_bg_color(peakLed, color_RedDark, 0);
    }
}

void WaveTablePage::init()
{
    pageID = PG_WAVE;
    strcpy(pageName, "Wave Table Synth");
    // create screen
    screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen, lv_color_black(), 0);
    // create lvgl objects
    // *SELECT AREA-----------------------------------------------------------------
    lv_obj_t *selectArea = lv_obj_create(screen);
    // lv_obj_remove_style_all(selectArea);
    lv_obj_set_style_bg_color(selectArea, lv_color_black(), 0);
    lv_obj_set_style_pad_all(selectArea, 5, 0);
    lv_obj_set_size(selectArea, 320, 100);
    lv_obj_set_y(selectArea, 35);
    lv_obj_t *label;
    lv_obj_t *btn;
    // *drop down menu for sound selection
    sf2SelectDropdown = lv_dropdown_create(selectArea);
    lv_obj_set_x(sf2SelectDropdown, 60);
    lv_obj_set_width(sf2SelectDropdown, 170);
    lv_obj_add_flag(sf2SelectDropdown, LV_OBJ_FLAG_OVERFLOW_VISIBLE);
    lv_dropdown_set_options_static(sf2SelectDropdown, SF2_Instrument_Names);
    lv_obj_add_event_cb(sf2SelectDropdown, onSF2DropdownSelect, LV_EVENT_VALUE_CHANGED, this);
    label = lv_label_create(sf2SelectDropdown);
    lv_label_set_text(label, "Sound:");
    lv_obj_align(label, LV_ALIGN_LEFT_MID, -70, 0);

    // *volume arc
    volArc = Gui_CreateParamArc(selectArea, 4, false);
    lv_obj_align(volArc, LV_ALIGN_TOP_RIGHT, -5, 20);
    label = lv_label_create(volArc);
    lv_label_set_text(label, "Gain");
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, -20);
    // gain text
    volText = lv_label_create(volArc);
    lv_label_set_text(volText, "0");
    lv_obj_center(volText);
    // dB text
    label = lv_label_create(volArc);
    lv_obj_set_style_text_font(label, font_small, 0);
    lv_label_set_text(label, "dB");
    lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, 0);
    // set value
    setVolume(volume);
    lv_arc_set_range(volArc, 0, 30);
    lv_arc_set_value(volArc, volume + VOL_OFFSET);
    lv_obj_add_event_cb(volArc, onVolArcPressed, LV_EVENT_VALUE_CHANGED, this);

    // *octave select
    label = lv_label_create(selectArea);
    lv_label_set_text(label, "Octave");
    lv_obj_set_style_text_font(label, font_small, 0);
    lv_obj_set_pos(label, 23, 38);
    btn = Gui_CreateButton(selectArea, false, 1);
    lv_obj_set_size(btn, 30, 30);
    lv_obj_align(btn, LV_ALIGN_BOTTOM_LEFT, 0, 0);
    lv_obj_add_event_cb(btn, onOctaveSelect, LV_EVENT_CLICKED, this);
    label = lv_label_create(btn);
    lv_label_set_text(label, LV_SYMBOL_MINUS);
    lv_obj_center(label);

    octaveText = lv_label_create(selectArea);
    lv_obj_set_style_text_font(octaveText, font_large, 0);
    lv_label_set_text_fmt(octaveText, "%d", octave);
    lv_obj_align(octaveText, LV_ALIGN_BOTTOM_LEFT, 40, -3);

    btn = Gui_CreateButton(selectArea, false, 1);
    lv_obj_set_size(btn, 30, 30);
    lv_obj_align(btn, LV_ALIGN_BOTTOM_LEFT, 60, 0);
    lv_obj_add_flag(btn, LV_OBJ_FLAG_USER_1);
    lv_obj_add_event_cb(btn, onOctaveSelect, LV_EVENT_CLICKED, this);
    label = lv_label_create(btn);
    lv_label_set_text(label, LV_SYMBOL_PLUS);
    lv_obj_center(label);

    // *velocity button
    btn = Gui_CreateButton(selectArea, true);
    lv_obj_set_size(btn, 60, 30);
    lv_obj_align(btn, LV_ALIGN_BOTTOM_LEFT, 100, 0);
    lv_obj_add_event_cb(btn, onVelocityBtnPressed, LV_EVENT_CLICKED, this);
    if (useVelocity)
        lv_obj_add_state(btn, LV_STATE_CHECKED);
    else
        lv_obj_clear_state(btn, LV_STATE_CHECKED);
    label = lv_label_create(btn);
    lv_label_set_text(label, "Velocity");
    lv_obj_set_style_text_font(label, font_small, 0);
    lv_obj_center(label);
    // *pitch bend button
    // add a dropdown right under it
    pitchDropdown = lv_dropdown_create(selectArea);
    lv_obj_set_size(pitchDropdown, 60, 30);
    lv_obj_align(pitchDropdown, LV_ALIGN_BOTTOM_LEFT, 170, 0);
    lv_dropdown_set_options(pitchDropdown, "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12");
    lv_dropdown_set_selected(pitchDropdown, pitchbendRange - 1);
    lv_obj_add_event_cb(pitchDropdown, onPitchDropdownSelect, LV_EVENT_VALUE_CHANGED, this);
    btn = Gui_CreateButton(selectArea, true);
    lv_obj_set_size(btn, 60, 30);
    lv_obj_align(btn, LV_ALIGN_BOTTOM_LEFT, 170, 0);
    lv_obj_add_event_cb(btn, onPitchBtnPressed, LV_EVENT_CLICKED, this);
    lv_obj_add_event_cb(btn, onPitchBtnHolded, LV_EVENT_LONG_PRESSED, this);
    if (usePitchbend)
        lv_obj_add_state(btn, LV_STATE_CHECKED);
    else
        lv_obj_clear_state(btn, LV_STATE_CHECKED);
    pitchText = lv_label_create(btn);
    lv_label_set_text_fmt(pitchText, "Pitch: %d", pitchbendRange);
    lv_obj_set_style_text_font(pitchText, font_small, 0);
    lv_obj_center(pitchText);

    //  *volume bar
    volBar = Gui_CreateVolumeMeter(selectArea, 115, 10);
    lv_obj_align(volBar, LV_ALIGN_BOTTOM_LEFT, 100, -35);
    peakLed = Gui_CreatePeakLed(volBar, 10, 10);
    lv_obj_align(peakLed, LV_ALIGN_RIGHT_MID, 15, 0);
}

void WaveTablePage::setVolume(int8_t value)
{
    volume = value;
    AudioSynth.setMasterVol(value);
    lv_label_set_text_fmt(volText, "%d", value);
}