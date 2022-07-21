#include "SynthPage.h"
#include "Hardware.h"
#include "Controls.h"
#include "Audio/AudioSynth.h"
#include "Audio/AudioIO.h"
#include "Audio/AudioUtility.h"

void SynthPage::onVelocityBtnPressed(lv_event_t *e)
{
    SynthPage *instance = (SynthPage *)lv_event_get_user_data(e);
    instance->useVelocity = !instance->useVelocity;
    AudioSynth.setUseVelocity(instance->useVelocity);
}

void SynthPage::onPitchBtnPressed(lv_event_t *e)
{
    SynthPage *instance = (SynthPage *)lv_event_get_user_data(e);
    instance->usePitchbend = !instance->usePitchbend;
    AudioSynth.setUsePitchbend(instance->usePitchbend);
}

void SynthPage::onPitchBtnHolded(lv_event_t *e)
{
    SynthPage *instance = (SynthPage *)lv_event_get_user_data(e);
    lv_dropdown_open(instance->pitchDropdown);
}

void SynthPage::onPitchDropdownSelect(lv_event_t *e)
{
    SynthPage *instance = (SynthPage *)lv_event_get_user_data(e);
    lv_obj_t *dropdown = lv_event_get_target(e);
    uint8_t id = lv_dropdown_get_selected(dropdown);
    instance->pitchbendRange = id + 1;
    lv_label_set_text_fmt(instance->pitchText, "Pitch: %d", instance->pitchbendRange);
}

void SynthPage::onOctaveSelect(lv_event_t *e)
{
    SynthPage *instance = (SynthPage *)lv_event_get_user_data(e);
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

void SynthPage::onVolArcPressed(lv_event_t *e)
{
    SynthPage *instance = (SynthPage *)lv_event_get_user_data(e);
    lv_obj_t *arc = lv_event_get_target(e);
    int8_t value = lv_arc_get_value(arc);
    if (enc[3] != NULL)
        enc[3]->setCurrentReading(value + VOL_OFFSET);
    instance->volume = value;
    AudioSynth.setMasterVol(value);
    lv_label_set_text_fmt(instance->volText, "%d", value);
}

// re-configure encoders when menu page has changed
void SynthPage::onMenuPageChange(lv_event_t *e)
{
    SynthPage *instance = (SynthPage *)lv_event_get_user_data(e);
    instance->configureEncoders();
}

void SynthPage::onOscWaveSelect(lv_event_t *e)
{
    SynthPage *instance = (SynthPage *)lv_event_get_user_data(e);
    lv_obj_t *dropdown = lv_event_get_target(e);
    uint8_t wave = lv_dropdown_get_selected(dropdown);
    lv_obj_t *curMenu = lv_menu_get_cur_main_page(instance->menu);
    uint8_t id = 0;
    if (curMenu == instance->menu_osc[0])
        id = 0;
    else if (curMenu == instance->menu_osc[1])
        id = 1;

    AudioSynth.setOscWaveform(id, wave);
    instance->oscWaveform[id] = id;
    const lv_img_dsc_t *img = instance->getWaveImg(wave);
    lv_img_set_src(instance->oscWaveImg[id], img);
    lv_img_set_src(instance->oscWaveItemImg[id], img);
}

void SynthPage::onOscArcPressed(lv_event_t *e)
{
    SynthPage *instance = (SynthPage *)lv_event_get_user_data(e);
    lv_obj_t *arc = lv_event_get_target(e);
    int8_t value = lv_arc_get_value(arc);
    uint8_t flag = Gui_getArcIdFlag(arc);
    uint8_t id = 0;
    lv_obj_t *curMenu = lv_menu_get_cur_main_page(instance->menu);
    if (curMenu == instance->menu_osc[0])
        id = 0;
    else if (curMenu == instance->menu_osc[1])
        id = 1;

    switch (flag)
    {
    case 0:
        // pwm
        if (enc[0] != NULL)
            enc[0]->setCurrentReading(value);
        instance->oscPwm[id] = value;
        AudioSynth.setOscPwm(id, value);
        lv_label_set_text_fmt(instance->oscPwmText[id], "%d", value);
        break;
    case 1:
        // detune
        if (enc[1] != NULL)
            enc[1]->setCurrentReading(value + 100);
        instance->oscDetune[id] = value;
        AudioSynth.setOscDetune(id, value * 0.01f);
        lv_label_set_text_fmt(instance->oscDetuneText[id], "%d", value);
        break;
    case 2:
        // level
        if (enc[2] != NULL)
            enc[2]->setCurrentReading(value);
        instance->oscLevel[id] = value;
        AudioSynth.setOscLevel(id, value);
        lv_label_set_text_fmt(instance->oscLevelText[id], "%d", value);
        break;
    }
}

void SynthPage::onOscOctaveSelect(lv_event_t *e)
{
    SynthPage *instance = (SynthPage *)lv_event_get_user_data(e);
    lv_obj_t *btn = lv_event_get_target(e);
    lv_obj_t *curMenu = lv_menu_get_cur_main_page(instance->menu);
    uint8_t id = 0;
    if (curMenu == instance->menu_osc[0])
        id = 0;
    else if (curMenu == instance->menu_osc[1])
        id = 1;

    if (lv_obj_has_flag(btn, LV_OBJ_FLAG_USER_1))
    {
        // increase
        instance->oscOctave[id]++;
        if (instance->oscOctave[id] > 2)
            instance->oscOctave[id] = 2;
    }
    else
    {
        // decrease
        instance->oscOctave[id]--;
        if (instance->oscOctave[id] < -2)
            instance->oscOctave[id] = -2;
    }
    AudioSynth.setOscOctave(id, instance->oscOctave[id]);
    lv_label_set_text_fmt(instance->oscOctaveText[id], "%d", instance->oscOctave[id]);
}

void SynthPage::onOscSemiSelect(lv_event_t *e)
{
    SynthPage *instance = (SynthPage *)lv_event_get_user_data(e);
    lv_obj_t *btn = lv_event_get_target(e);
    lv_obj_t *curMenu = lv_menu_get_cur_main_page(instance->menu);
    uint8_t id = 0;
    if (curMenu == instance->menu_osc[0])
        id = 0;
    else if (curMenu == instance->menu_osc[1])
        id = 1;

    if (lv_obj_has_flag(btn, LV_OBJ_FLAG_USER_1))
    {
        // increase
        instance->oscSemi[id]++;
        if (instance->oscSemi[id] > 12)
            instance->oscSemi[id] = 12;
    }
    else
    {
        // decrease
        instance->oscSemi[id]--;
        if (instance->oscSemi[id] < -12)
            instance->oscSemi[id] = -12;
    }
    AudioSynth.setOscSemi(id, instance->oscSemi[id]);
    lv_label_set_text_fmt(instance->oscSemiText[id], "%d", instance->oscSemi[id]);
}

void SynthPage::onNoiseArcPressed(lv_event_t *e)
{
    SynthPage *instance = (SynthPage *)lv_event_get_user_data(e);
    lv_obj_t *arc = lv_event_get_target(e);
    int16_t value = lv_arc_get_value(arc);

    enc[0]->setCurrentReading(value);
    instance->noiseLevel = value;
    AudioSynth.setNoiseLevel(value);
    lv_label_set_text_fmt(instance->noiseLevelText, "%d", value);
}

void SynthPage::onAmpEnvArcPressed(lv_event_t *e)
{
    SynthPage *instance = (SynthPage *)lv_event_get_user_data(e);
    lv_obj_t *arc = lv_event_get_target(e);
    int16_t value = lv_arc_get_value(arc);
    uint8_t flag = Gui_getArcIdFlag(arc);
    switch (flag)
    {
    case 0:
        // delay
        instance->ampEnvVal[flag] = value;
        break;
    case 1:
        // attack
        if (enc[0] != NULL)
            enc[0]->setCurrentReading(value);
        instance->ampEnvVal[flag] = value;
        break;
    case 2:
        // decay
        if (enc[1] != NULL)
            enc[1]->setCurrentReading(value);
        instance->ampEnvVal[flag] = value;
        break;
    case 3:
        // sustain
        if (enc[2] != NULL)
            enc[2]->setCurrentReading(value);
        instance->ampEnvVal[flag] = value;
        break;
    case 4:
        // release
        if (enc[3] != NULL)
            enc[3]->setCurrentReading(value);
        instance->ampEnvVal[flag] = value;
        break;
    }
    float envParam[5];
    envParam[0] = powf(ENV_VAL_INCREMENT, instance->ampEnvVal[0]) - 1; // delay
    envParam[1] = powf(ENV_VAL_INCREMENT, instance->ampEnvVal[1]) - 1; // attack
    envParam[2] = powf(ENV_VAL_INCREMENT, instance->ampEnvVal[2]) - 1; // decay
    envParam[3] = instance->ampEnvVal[3] * 0.01f;                      // sustain
    envParam[4] = powf(ENV_VAL_INCREMENT, instance->ampEnvVal[4]) - 1; // release

    AudioSynth.setAmpEnvelope(envParam[0], envParam[1], envParam[2], envParam[3], envParam[4]);
    Gui_SetEnvelopeGraph(instance->ampEnvGraph, instance->ampEnvPoints, envParam[0], envParam[1], envParam[2], envParam[3], envParam[4]);

    int decimal;
    for (uint8_t i = 0; i < 5; i++)
    {
        if (i != 3)
        {
            if (envParam[i] >= 1000)
            {
                envParam[i] /= 1000.0f;
                lv_label_set_text(lv_obj_get_child(instance->ampEnvArc[i], 1), "S");
            }
            else
            {
                lv_label_set_text(lv_obj_get_child(instance->ampEnvArc[i], 1), "ms");
            }

            if (envParam[i] < 10)
                decimal = 2;
            else if (envParam[i] < 100)
                decimal = 1;
            else
                decimal = 0;
            lv_label_set_text_fmt(instance->ampEnvText[i], "%.*f", decimal, envParam[i]);
        }
        else // sustain
        {
            lv_label_set_text_fmt(instance->ampEnvText[i], "%d", instance->ampEnvVal[i]);
        }
    }
}

void SynthPage::onBtnPressed(uint8_t pin)
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

void SynthPage::onBtnHold(uint8_t pin)
{
    switch (pin)
    {
    case BTN_PWR:
        PageManager.showPowerPopup();
        break;
    }
}

void SynthPage::onBtnReleased(uint8_t pin)
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

void SynthPage::onEncTurned(uint8_t id, int value)
{

    lv_obj_t *curMenu = lv_menu_get_cur_main_page(menu);
    if (curMenu == menu_main)
    {
        switch (id)
        {
        case 3: // master out volume
            lv_arc_set_value(volArc, value - VOL_OFFSET);
            lv_event_send(volArc, LV_EVENT_VALUE_CHANGED, NULL);
            break;
        }
    }
    else if (curMenu == menu_osc[0])
    {
        switch (id)
        {
        case 0: // pwm
            lv_arc_set_value(oscArc[0][id], value);
            break;
        case 1: // detune
            lv_arc_set_value(oscArc[0][id], value - 100);
            break;
        case 2: // level
            lv_arc_set_value(oscArc[0][id], value);
            break;
        }
        lv_event_send(oscArc[0][id], LV_EVENT_VALUE_CHANGED, NULL);
    }
    else if (curMenu == menu_osc[1])
    {
        switch (id)
        {
        case 0: // pwm
            lv_arc_set_value(oscArc[1][id], value);
            break;
        case 1: // detune
            lv_arc_set_value(oscArc[1][id], value - 100);
            break;
        case 2: // level
            lv_arc_set_value(oscArc[1][id], value);
            break;
        }
        lv_event_send(oscArc[1][id], LV_EVENT_VALUE_CHANGED, NULL);
    }
    else if (curMenu == menu_noise)
    {
        switch (id)
        {
        case 0: // level
            lv_arc_set_value(noiseArc, value);
            break;
        }
        lv_event_send(noiseArc, LV_EVENT_VALUE_CHANGED, NULL);
    }
    else if (curMenu == menu_ampenv)
    {
        lv_arc_set_value(ampEnvArc[id + 1], value);
        lv_event_send(ampEnvArc[id + 1], LV_EVENT_VALUE_CHANGED, NULL);
    }
}

void SynthPage::onJoyUpdate(int joy_x, int joy_y)
{
    if (usePitchbend)
    {
        AudioSynth.pitchbend(map((float)joy_x, 0, 1019, pitchbendRange, -pitchbendRange));
    }
}

void SynthPage::onCCReceive(u_int8_t channel, u_int8_t control, u_int8_t value)
{
}

void SynthPage::configurePage()
{
    // configure encoders
    configureEncoders();
    // setup micorphone for velocity sensing
    sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
    sgtl5000_1.micGain(40);
    AudioIO.setInputVolume(InputTracks::LINEMIC_IN, 0);
    // setup peak module for level meter
    AudioIO.setMixerLevelMode(LevelMeterMode::PRE_FADER);
    lv_arc_set_value(volArc, volume);
    lv_event_send(volArc, LV_EVENT_VALUE_CHANGED, NULL);
    // update current velocity settings
    AudioSynth.setUseVelocity(useVelocity);
    // set reverb FX
    AudioFX.reverb.setWithMem(&reverbMem);
    // set voice mode for AudioSynth
    AudioSynth.setVoiceMode(VOICE_MODE_SYNTH);
}

// configure enocders for according to current menu page
void SynthPage::configureEncoders()
{
    lv_obj_t *curMenu = lv_menu_get_cur_main_page(menu);
    if (curMenu == menu_main)
    {
        enc[3]->changePrecision(30, volume + VOL_OFFSET, false);
    }
    else if (curMenu == menu_osc[0])
    {
        // pwm
        enc[0]->changePrecision(100, oscPwm[0], false);
        // detune
        enc[1]->changePrecision(200, oscDetune[0] + 100, false);
        // level
        enc[2]->changePrecision(100, oscLevel[0], false);
    }
    else if (curMenu == menu_osc[1])
    {
        // pwm
        enc[0]->changePrecision(100, oscPwm[1], false);
        // detune
        enc[1]->changePrecision(200, oscDetune[1] + 100, false);
        // level
        enc[2]->changePrecision(100, oscLevel[1], false);
    }
    else if (curMenu == menu_noise)
    {
        // level
        enc[0]->changePrecision(100, noiseLevel, false);
    }
    else if (curMenu == menu_ampenv)
    {
        // attack
        enc[0]->changePrecision(ENV_VAL_MAX, ampEnvVal[1], false);
        // decay
        enc[1]->changePrecision(ENV_VAL_MAX, ampEnvVal[2], false);
        // sustain
        enc[2]->changePrecision(100, ampEnvVal[3], false);
        // release
        enc[3]->changePrecision(ENV_VAL_MAX, ampEnvVal[4], false);
    }
}

void SynthPage::setUserData()
{
    // main menu
    lv_label_set_text_fmt(octaveText, "%d", octave);
    lv_arc_set_value(volArc, volume);
    lv_event_send(volArc, LV_EVENT_VALUE_CHANGED, NULL);
    AudioSynth.setUseVelocity(useVelocity);
    if (useVelocity)
        lv_obj_add_state(velocityBtn, LV_STATE_CHECKED);
    else
        lv_obj_clear_state(velocityBtn, LV_STATE_CHECKED);
    lv_dropdown_set_selected(pitchDropdown, pitchbendRange - 1);
    lv_label_set_text_fmt(pitchText, "Pitch: %d", pitchbendRange);
    AudioSynth.setUsePitchbend(usePitchbend);
    if (usePitchbend)
        lv_obj_add_state(pitchBtn, LV_STATE_CHECKED);
    else
        lv_obj_clear_state(pitchBtn, LV_STATE_CHECKED);
    lv_img_set_src(oscWaveItemImg[0], getWaveImg(oscWaveform[0]));
    lv_img_set_src(oscWaveItemImg[1], getWaveImg(oscWaveform[1]));

    // osc1 and osc2 menu
    for (uint8_t id=0; id<2; id++)
    {
        lv_dropdown_set_selected(oscWaveDropdown[id], oscWaveform[id]);
        lv_event_send(oscWaveDropdown[id], LV_EVENT_VALUE_CHANGED, NULL);

        lv_label_set_text_fmt(oscOctaveText[id], "%d", oscOctave[id]);
        AudioSynth.setOscOctave(id, oscOctave[id]);

        lv_label_set_text_fmt(oscSemiText[id], "%d", oscSemi[id]);
        AudioSynth.setOscSemi(id, oscSemi[id]);

        lv_arc_set_value(oscArc[id][0], oscPwm[id]);
        AudioSynth.setOscPwm(id, oscPwm[id]);
        lv_label_set_text_fmt(oscPwmText[id], "%d", oscPwm[id]);

        lv_arc_set_value(oscArc[id][1], oscDetune[id]);
        AudioSynth.setOscDetune(id, oscDetune[id] * 0.01f);
        lv_label_set_text_fmt(oscDetuneText[id], "%d", oscDetune[id]);

        lv_arc_set_value(oscArc[id][2], oscLevel[id]);
        AudioSynth.setOscLevel(id, oscLevel[id]);
        lv_label_set_text_fmt(oscLevelText[id], "%d", oscLevel[id]);
    }

    // noise menu
    lv_arc_set_value(noiseArc, noiseLevel);
    AudioSynth.setNoiseLevel(noiseLevel);
    lv_label_set_text_fmt(noiseLevelText, "%d", noiseLevel);

    // amp env menu
    for (uint8_t id=0; id<5; id++)
    {
        lv_arc_set_value(ampEnvArc[id], ampEnvVal[id]);
        lv_event_send(ampEnvArc[id], LV_EVENT_VALUE_CHANGED, NULL);
    }
    
}

void SynthPage::update()
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

void SynthPage::init()
{
    pageID = PG_SYNTH;
    strcpy(pageName, "Synthesizer");
    // create screen
    screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen, lv_color_black(), 0);
    // create lvgl objects
    lv_obj_t *label;
    lv_obj_t *btn;
    lv_obj_t *img;
    // **MENU OBJECT
    menu = lv_menu_create(screen);
    lv_obj_set_style_bg_color(menu, lv_color_black(), 0);
    lv_obj_set_style_pad_all(menu, 0, 0);
    lv_obj_set_style_border_width(menu, 0, 0);
    lv_obj_set_size(menu, 320, 205);
    lv_obj_set_y(menu, 35);
    btn = lv_menu_get_main_header_back_btn(menu);
    lv_obj_set_size(btn, 25, 20);
    // *MENU OSC1 and 2-------------------------------------------------------------------
    for (uint8_t id = 0; id < 2; id++)
    {
        char oscName[14];
        strcpy(oscName, (String("Oscillator ") + String(id + 1)).c_str());
        menu_osc[id] = lv_menu_page_create(menu, oscName);
        lv_obj_t *menu_area = createItemMenuArea(menu_osc[id]);
        // *waveform selector
        label = lv_label_create(menu_area);
        lv_label_set_text(label, "Waveform: ");
        lv_obj_align(label, LV_ALIGN_TOP_LEFT, 0, 10);
        oscWaveDropdown[id] = lv_dropdown_create(menu_area);
        lv_dropdown_set_options(oscWaveDropdown[id], "Sine\nTriangle\nSawtooth\nSquare");
        lv_obj_set_size(oscWaveDropdown[id], 150, 35);
        lv_obj_align(oscWaveDropdown[id], LV_ALIGN_TOP_LEFT, 90, 0);
        lv_obj_add_flag(oscWaveDropdown[id], LV_OBJ_FLAG_OVERFLOW_VISIBLE);
        lv_obj_add_event_cb(oscWaveDropdown[id], onOscWaveSelect, LV_EVENT_VALUE_CHANGED, this);
        oscWaveImg[id] = lv_img_create(menu_area);
        lv_img_set_src(oscWaveImg[id], &sin_wave);
        lv_obj_align(oscWaveImg[id], LV_ALIGN_TOP_LEFT, 250, 5);
        // *octave selector
        label = lv_label_create(menu_area);
        lv_label_set_text(label, "Octave: ");
        lv_obj_align(label, LV_ALIGN_TOP_LEFT, 0, 50);
        // minus btn
        btn = Gui_CreateButton(menu_area);
        lv_obj_set_size(btn, 30, 30);
        lv_obj_align(btn, LV_ALIGN_TOP_LEFT, 65, 40);
        lv_obj_add_event_cb(btn, onOscOctaveSelect, LV_EVENT_CLICKED, this);
        label = lv_label_create(btn);
        lv_label_set_text(label, LV_SYMBOL_MINUS);
        lv_obj_center(label);
        // octave text
        oscOctaveText[id] = lv_label_create(menu_area);
        lv_obj_set_style_text_font(oscOctaveText[id], font_large, 0);
        lv_obj_align(oscOctaveText[id], LV_ALIGN_TOP_LEFT, 105, 45);
        // plus btn
        btn = Gui_CreateButton(menu_area);
        lv_obj_set_size(btn, 30, 30);
        lv_obj_align(btn, LV_ALIGN_TOP_LEFT, 130, 40);
        lv_obj_add_flag(btn, LV_OBJ_FLAG_USER_1);
        lv_obj_add_event_cb(btn, onOscOctaveSelect, LV_EVENT_CLICKED, this);
        label = lv_label_create(btn);
        lv_label_set_text(label, LV_SYMBOL_PLUS);
        lv_obj_center(label);
        // *semitone selector
        label = lv_label_create(menu_area);
        lv_label_set_text(label, "Semi: ");
        lv_obj_align(label, LV_ALIGN_TOP_LEFT, 165, 50);
        // minus btn
        btn = Gui_CreateButton(menu_area);
        lv_obj_set_size(btn, 30, 30);
        lv_obj_align(btn, LV_ALIGN_TOP_LEFT, 210, 40);
        lv_obj_add_event_cb(btn, onOscSemiSelect, LV_EVENT_CLICKED, this);
        label = lv_label_create(btn);
        lv_label_set_text(label, LV_SYMBOL_MINUS);
        lv_obj_center(label);
        // semitone text
        oscSemiText[id] = lv_label_create(menu_area);
        lv_obj_set_style_text_font(oscSemiText[id], font_large, 0);
        lv_obj_align(oscSemiText[id], LV_ALIGN_TOP_LEFT, 250, 45);
        // plus btn
        btn = Gui_CreateButton(menu_area);
        lv_obj_set_size(btn, 30, 30);
        lv_obj_align(btn, LV_ALIGN_TOP_LEFT, 275, 40);
        lv_obj_add_flag(btn, LV_OBJ_FLAG_USER_1);
        lv_obj_add_event_cb(btn, onOscSemiSelect, LV_EVENT_CLICKED, this);
        label = lv_label_create(btn);
        lv_label_set_text(label, LV_SYMBOL_PLUS);
        lv_obj_center(label);
        // *pwm arc
        oscArc[id][0] = Gui_CreateParamArc(menu_area, 1, "PWM", "%", false);
        Gui_setArcIdFlag(oscArc[id][0], 0);
        lv_obj_align(oscArc[id][0], LV_ALIGN_TOP_LEFT, 0, 100);
        // pwm text
        oscPwmText[id] = lv_label_create(oscArc[id][0]);
        lv_obj_center(oscPwmText[id]);
        // set value
        lv_arc_set_range(oscArc[id][0], 0, 100);
        lv_obj_add_event_cb(oscArc[id][0], onOscArcPressed, LV_EVENT_VALUE_CHANGED, this);
        // *detune arc
        oscArc[id][1] = Gui_CreateParamArc(menu_area, 2, "Detune", "cent", false);
        Gui_setArcIdFlag(oscArc[id][1], 1);
        lv_obj_align(oscArc[id][1], LV_ALIGN_TOP_LEFT, 80, 100);
        // detune text
        oscDetuneText[id] = lv_label_create(oscArc[id][1]);
        lv_obj_center(oscDetuneText[id]);
        // set value
        lv_arc_set_range(oscArc[id][1], -100, 100);
        lv_obj_add_event_cb(oscArc[id][1], onOscArcPressed, LV_EVENT_VALUE_CHANGED, this);
        // *level arc
        oscArc[id][2] = Gui_CreateParamArc(menu_area, 3, "Level", "%", false);
        Gui_setArcIdFlag(oscArc[id][2], 2);
        lv_obj_align(oscArc[id][2], LV_ALIGN_TOP_LEFT, 160, 100);
        // level text
        oscLevelText[id] = lv_label_create(oscArc[id][2]);
        lv_obj_center(oscLevelText[id]);
        // set value
        lv_arc_set_range(oscArc[id][2], 0, 100);
        lv_obj_add_event_cb(oscArc[id][2], onOscArcPressed, LV_EVENT_VALUE_CHANGED, this);
    }
    // *MENU NOISE------------------------------------------------------------------
    menu_noise = lv_menu_page_create(menu, "Noise Generator");
    lv_obj_t *menu_area = createItemMenuArea(menu_noise);
    // *level arc
    noiseArc = Gui_CreateParamArc(menu_area, 1, "Level", "%", false);
    lv_obj_align(noiseArc, LV_ALIGN_TOP_LEFT, 0, 100);
    // level text
    noiseLevelText = lv_label_create(noiseArc);
    lv_obj_center(noiseLevelText);
    // set value
    lv_arc_set_range(noiseArc, 0, 100);
    lv_obj_add_event_cb(noiseArc, onNoiseArcPressed, LV_EVENT_VALUE_CHANGED, this);
    // *MENU AMPENV-----------------------------------------------------------------
    menu_ampenv = lv_menu_page_create(menu, "Amp Envelope");
    menu_area = createItemMenuArea(menu_ampenv);
    lv_obj_clear_flag(menu_area, LV_OBJ_FLAG_SCROLLABLE);
    // *envelope graph
    ampEnvGraph = Gui_CreateEnvelopeGraph(menu_area, 320, 90);
    // *5 envelope arcs
    const char *envTitle[] = {"Delay", "Attack", "Decay", "Sustain", "Release"};
    for (uint8_t i = 0; i < 5; i++)
    {
        ampEnvArc[i] = Gui_CreateParamArc(menu_area, i, envTitle[i], i == 3 ? "%" : "ms", false);
        lv_obj_set_size(ampEnvArc[i], 55, 55);
        lv_obj_align(ampEnvArc[i], LV_ALIGN_BOTTOM_MID, -126 + 63 * i, 0);
        Gui_setArcIdFlag(ampEnvArc[i], i);
        if (i == 3) // sustain arc
            lv_arc_set_range(ampEnvArc[i], 0, 100);
        else // everything else
            lv_arc_set_range(ampEnvArc[i], 0, ENV_VAL_MAX);
        lv_obj_add_event_cb(ampEnvArc[i], onAmpEnvArcPressed, LV_EVENT_VALUE_CHANGED, this);
        ampEnvText[i] = lv_label_create(ampEnvArc[i]);
        lv_obj_center(ampEnvText[i]);
    }

    // *MENU MAIN-------------------------------------------------------------------
    menu_main = lv_menu_page_create(menu, NULL);
    lv_menu_set_page(menu, menu_main);
    // *SELECT AREA
    lv_obj_t *selectArea = lv_obj_create(menu_main);
    // lv_obj_remove_style_all(selectArea);
    lv_obj_set_style_bg_color(selectArea, lv_color_black(), 0);
    lv_obj_set_style_pad_all(selectArea, 5, 0);
    lv_obj_set_size(selectArea, 320, 100);

    // *Quick parameters
    label = lv_label_create(selectArea);
    lv_label_set_text(label, "Quick Parameters:\nIn Development");
    lv_obj_set_style_text_color(label, color_Grey, 0);

    // *volume arc
    volArc = Gui_CreateParamArc(selectArea, 4, "Gain", "dB", false);
    lv_obj_align(volArc, LV_ALIGN_TOP_RIGHT, -5, 20);
    // gain text
    volText = lv_label_create(volArc);
    lv_obj_center(volText);
    // set value
    lv_arc_set_range(volArc, -15, 15);
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
    velocityBtn = Gui_CreateButton(selectArea, true);
    lv_obj_set_size(velocityBtn, 60, 30);
    lv_obj_align(velocityBtn, LV_ALIGN_BOTTOM_LEFT, 100, 0);
    lv_obj_add_event_cb(velocityBtn, onVelocityBtnPressed, LV_EVENT_CLICKED, this);
    label = lv_label_create(velocityBtn);
    lv_label_set_text(label, "Velocity");
    lv_obj_set_style_text_font(label, font_small, 0);
    lv_obj_center(label);
    // *pitch bend button
    // add a dropdown right under it
    pitchDropdown = lv_dropdown_create(selectArea);
    lv_obj_set_size(pitchDropdown, 60, 30);
    lv_obj_align(pitchDropdown, LV_ALIGN_BOTTOM_LEFT, 170, 0);
    lv_dropdown_set_options(pitchDropdown, "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12");
    lv_obj_add_event_cb(pitchDropdown, onPitchDropdownSelect, LV_EVENT_VALUE_CHANGED, this);
    pitchBtn = Gui_CreateButton(selectArea, true);
    lv_obj_set_size(pitchBtn, 60, 30);
    lv_obj_align(pitchBtn, LV_ALIGN_BOTTOM_LEFT, 170, 0);
    lv_obj_add_event_cb(pitchBtn, onPitchBtnPressed, LV_EVENT_CLICKED, this);
    lv_obj_add_event_cb(pitchBtn, onPitchBtnHolded, LV_EVENT_LONG_PRESSED, this);
    pitchText = lv_label_create(pitchBtn);
    lv_obj_set_style_text_font(pitchText, font_small, 0);
    lv_obj_center(pitchText);

    //  *volume bar
    volBar = Gui_CreateVolumeMeter(selectArea, 115, 10);
    lv_obj_align(volBar, LV_ALIGN_BOTTOM_LEFT, 100, -35);
    peakLed = Gui_CreatePeakLed(volBar, 10, 10);
    lv_obj_align(peakLed, LV_ALIGN_RIGHT_MID, 15, 0);

    // *ITEM AREA
    lv_obj_t *itemArea = lv_obj_create(menu_main);
    lv_obj_remove_style_all(itemArea);
    lv_obj_set_size(itemArea, 320, 105);
    lv_obj_set_y(itemArea, 135);

    // *column 1
    lv_obj_t *col = lv_obj_create(itemArea);
    lv_obj_remove_style_all(col);
    lv_obj_set_size(col, 80, 105);
    lv_obj_set_style_pad_all(col, 2, 0);
    // osc1 button
    btn = createItemBtn(col, "OSC 1");
    oscWaveItemImg[0] = lv_img_create(btn);
    lv_obj_set_align(oscWaveItemImg[0], LV_ALIGN_LEFT_MID);
    lv_menu_set_load_page_event(menu, btn, menu_osc[0]);
    // osc2 button
    btn = createItemBtn(col, "OSC2");
    lv_obj_set_y(btn, 35);
    oscWaveItemImg[1] = lv_img_create(btn);
    lv_obj_set_align(oscWaveItemImg[1], LV_ALIGN_LEFT_MID);
    lv_menu_set_load_page_event(menu, btn, menu_osc[1]);
    // noise button
    btn = createItemBtn(col, "Noise");
    lv_obj_set_y(btn, 70);
    lv_obj_center(lv_obj_get_child(btn, 0));
    lv_menu_set_load_page_event(menu, btn, menu_noise);

    // *column 2
    col = lv_obj_create(itemArea);
    lv_obj_remove_style_all(col);
    lv_obj_set_size(col, 80, 105);
    lv_obj_set_style_pad_all(col, 2, 0);
    lv_obj_set_x(col, 80);
    // ampenv button
    btn = createItemBtn(col, "AMPENV");
    lv_obj_center(lv_obj_get_child(btn, 0));
    lv_menu_set_load_page_event(menu, btn, menu_ampenv);

    // *column 3
    col = lv_obj_create(itemArea);
    lv_obj_set_size(col, 80, 105);
    lv_obj_set_style_bg_color(col, lv_color_black(), 0);
    lv_obj_set_style_pad_all(col, 2, 0);
    lv_obj_set_x(col, 160);

    // *column 4
    col = lv_obj_create(itemArea);
    lv_obj_set_size(col, 80, 105);
    lv_obj_set_style_bg_color(col, lv_color_black(), 0);
    lv_obj_set_style_pad_all(col, 2, 0);
    lv_obj_set_x(col, 240);

    // *At last, add menu change callback
    lv_obj_add_event_cb(menu, onMenuPageChange, LV_EVENT_VALUE_CHANGED, this);
}

lv_obj_t *SynthPage::createItemBtn(lv_obj_t *parent, const char *text)
{
    lv_obj_t *btn = Gui_CreateButton(parent);
    lv_obj_set_size(btn, 76, 30);
    lv_obj_set_style_pad_all(btn, 4, 0);
    lv_obj_t *label = lv_label_create(btn);
    lv_label_set_text(label, text);
    lv_obj_set_align(label, LV_ALIGN_RIGHT_MID);

    return btn;
}

lv_obj_t *SynthPage::createItemMenuArea(lv_obj_t *menu)
{
    lv_obj_t *menu_area = lv_obj_create(menu);
    lv_obj_remove_style_all(menu_area);
    lv_obj_set_style_pad_all(menu_area, 5, 0);
    lv_obj_set_size(menu_area, 320, 180);

    return menu_area;
}

const lv_img_dsc_t *SynthPage::getWaveImg(uint8_t id)
{
    const lv_img_dsc_t *img;
    switch (id)
    {
    default:
        img = &sin_wave;
        break;
    case 1:
        img = &tri_wave;
        break;
    case 2:
        img = &saw_wave;
        break;
    case 3:
        img = &sqr_wave;
        break;
    }
    return img;
}