#include "SynthPage.h"
#include "Hardware.h"
#include "Controls.h"
#include "Audio/AudioSynth.h"
#include "Audio/AudioIO.h"
#include "Audio/AudioUtility.h"
#include "GuiObjects/Colors.h"

void SynthPage::onBtnPressedDefault(uint8_t pin)
{
    int noteNum;
    uint8_t keyNum = PinToKeyNum(pin);
    if (keyNum > 0)
    {
        noteNum = keyNum - 1 + 12 * mainPage->octave;
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
        }
    }
}

void SynthPage::onBtnHoldDefault(uint8_t pin)
{
    switch (pin)
    {
    case BTN_PWR:
        PageManager.showPowerPopup();
        break;
    }
}

void SynthPage::onBtnReleasedDefault(uint8_t pin)
{
    uint8_t noteNum;
    uint8_t keyNum = PinToKeyNum(pin);
    if (keyNum > 0)
    {
        noteNum = keyNum - 1 + 12 * mainPage->octave;
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

void SynthPage::onEncTurnedDefault(uint8_t id, int value)
{
    encoderBindCallback(id, value);
}

void SynthPage::onJoyUpdateDefault(int joy_x, int joy_y)
{
    if (mainPage->usePitchbend)
    {
        AudioSynth.pitchbend(map((float)joy_x, 0, 1019, mainPage->pitchbendRange, -mainPage->pitchbendRange), map((float)joy_x, 0, 1019, 1, -1));
    }
    if (mainPage->useModwheel)
    {
        AudioSynth.modwheel(map((float)joy_y, 0, 1019, -1, 1));
    }
}

void SynthPage::onCCReceiveDefault(u_int8_t channel, u_int8_t control, u_int8_t value)
{
}

void SynthPage::configurePage()
{
    // setup micorphone for velocity sensing
    sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
    sgtl5000_1.micGain(40);
    AudioIO.setInputVolume(InputTracks::LINEMIC_IN, 0);
    // setup peak module for level meter
    AudioIO.setMixerLevelMode(LevelMeterMode::PRE_FADER);
    // set reverb FX
    AudioFX.reverb.setWithMem(&reverbMem);
    // set voice mode for AudioSynth
    AudioSynth.setVoiceMode(VOICE_MODE_SYNTH);
}

void SynthPage::updateDefault()
{
    
}

void SynthPage::init()
{
    pageID = PG_SYNTH;
    strcpy(pageName, "Synthesizer");
    // create screen
    screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen, lv_color_black(), 0);
    // create subpage group object for all subpages to use
    subpageGroup = lv_obj_create(screen);
    lv_obj_set_style_bg_color(subpageGroup, lv_color_black(), 0);
    lv_obj_set_style_pad_all(subpageGroup, 0, 0);
    lv_obj_set_style_border_width(subpageGroup, 0, 0);
    lv_obj_set_size(subpageGroup, 320, 205);
    lv_obj_set_y(subpageGroup, 35);

    // Create subpage objects
    mainPage = new MainPage(this);
    oscPage[0] = new OscPage(this, 0);
    oscPage[1] = new OscPage(this, 1);
    samplerPage = new SamplerPage(this);
    noisePage = new NoisePage(this);
    filterPage = new FilterPage(this);
    modPage = new ModPage(this);
    envPage[0] = new EnvPage(this, 0);
    envPage[1] = new EnvPage(this, 1);
    envPage[2] = new EnvPage(this, 2);
    lfoPage[0] = new LfoPage(this, 0);
    lfoPage[1] = new LfoPage(this, 1);
    // set default subpage
    // TODO: maybe store curSubPage into user data?
    curSubPage = mainPage;

    // set modulation list pointer
    AudioSynth.setModulationListPtr(&modPage->modList);
}

void SynthPage::loadAll()
{
    // load all subpages one by one to set user data or apply presets
    mainPage->load();
    mainPage->unload();
    for (uint8_t i=0; i<2; i++)
    {
        oscPage[i]->load();
        oscPage[i]->unload();
    }
    samplerPage->load();
    samplerPage->unload();
    noisePage->load();
    noisePage->unload();
    filterPage->load();
    filterPage->unload();
    modPage->load();
    modPage->unload();
    for (uint8_t i=0; i<3; i++)
    {
        envPage[i]->load();
        envPage[i]->unload();
    }
    for (uint8_t i=0; i<2; i++)
    {
        lfoPage[i]->load();
        lfoPage[i]->unload();
    }
}

void SynthPage::serialize(ofstream &stream)
{
    // serialize all subpages
    mainPage->serialize(stream);
    for (uint8_t i=0; i<2; i++)
    {
        oscPage[i]->serialize(stream);
    }
    samplerPage->serialize(stream);
    noisePage->serialize(stream);
    filterPage->serialize(stream);
    modPage->serialize(stream);
    for (uint8_t i=0; i<3; i++)
    {
        envPage[i]->serialize(stream);
    }
    for (uint8_t i=0; i<2; i++)
    {
        lfoPage[i]->serialize(stream);
    }
}

void SynthPage::deserialize(ifstream &stream)
{
    // deserialize all subpages
    mainPage->deserialize(stream);
    for (uint8_t i=0; i<2; i++)
    {
        oscPage[i]->deserialize(stream);
    }
    samplerPage->deserialize(stream);
    noisePage->deserialize(stream);
    filterPage->deserialize(stream);
    modPage->deserialize(stream);
    for (uint8_t i=0; i<3; i++)
    {
        envPage[i]->deserialize(stream);
    }
    for (uint8_t i=0; i<2; i++)
    {
        lfoPage[i]->deserialize(stream);
    }
}

lv_obj_t *SynthPage::createTopBar(lv_obj_t *parent, const char *title)
{
    lv_obj_t *topBar = lv_obj_create(parent);
    lv_obj_set_style_bg_color(topBar, lv_color_black(), 0);
    lv_obj_set_style_pad_all(topBar, 2, 0);
    lv_obj_set_style_border_width(topBar, 0, 0);
    lv_obj_set_size(topBar, 320, 27);
    lv_obj_clear_flag(topBar, LV_OBJ_FLAG_SCROLLABLE);
    // back button
    lv_obj_t *btn = Gui_CreateButton(topBar, -1, 25, " Back ");
    lv_obj_add_event_cb(btn, [](lv_event_t *e) {
        SynthPage *synthPage = (SynthPage *)lv_event_get_user_data(e);
        synthPage->switchSubPage(synthPage->mainPage);
    }, LV_EVENT_PRESSED, this);
    // title label
    lv_obj_t *label = lv_label_create(topBar);
    lv_label_set_text(label, title);
    lv_obj_align(label, LV_ALIGN_LEFT_MID, 80, 0);

    return topBar;
}

// convert midi note number to note name
String SynthPage::noteNumToNoteName(uint8_t keyNum)
{
    String noteName;
    uint8_t octave = keyNum / 12 - 1;
    uint8_t note = keyNum % 12;
    switch (note)
    {
    case 0:
        noteName = "C";
        break;
    case 1:
        noteName = "C#";
        break;
    case 2:
        noteName = "D";
        break;
    case 3:
        noteName = "D#";
        break;
    case 4:
        noteName = "E";
        break;
    case 5:
        noteName = "F";
        break;
    case 6:
        noteName = "F#";
        break;
    case 7:
        noteName = "G";
        break;
    case 8:
        noteName = "G#";
        break;
    case 9:
        noteName = "A";
        break;
    case 10:
        noteName = "A#";
        break;
    case 11:
        noteName = "B";
        break;
    }
    noteName += octave;
    return noteName;
}

void SynthPage::MainPage::load()
{
    // get parent page reference
    SynthPage *synthPage = (SynthPage*) parentPage;
    // *SELECT AREA
    lv_obj_t *selectArea = lv_obj_create(synthPage->subpageGroup);
    lv_obj_set_style_bg_color(selectArea, lv_color_black(), 0);
    lv_obj_set_style_pad_all(selectArea, 5, 0);
    lv_obj_set_size(selectArea, 320, 100);

    // *Quick parameters
    lv_obj_t *label = lv_label_create(selectArea);
    lv_label_set_text(label, "Quick Parameters:\nIn Development");
    lv_obj_set_style_text_color(label, color_Grey, 0);
    // TODO: quick parameters use the other 3 arcs as new modulation source.

    // *volume arc
    volArc = new ParamArc(selectArea, 4, "Gain", "dB", false);
    volArc->bindEncoder(3);
    volArc->setRange(-15, 15);
    lv_obj_align(volArc->getLvglObject(), LV_ALIGN_TOP_RIGHT, -5, 20);
    volArc->setCallback(onVolArcPressed, this);
    volArc->setValue(volume);

    // *octave select
    label = lv_label_create(selectArea);
    lv_label_set_text(label, "Octave");
    lv_obj_set_style_text_font(label, font_small, 0);
    lv_obj_set_pos(label, 23, 38);
    octaveSpinbox = new Spinbox(selectArea, 1);
    octaveSpinbox->setRange(1, 8);
    octaveSpinbox->setCallback(onOctaveSelect, this);
    octaveSpinbox->setValue(octave);
    lv_obj_align(octaveSpinbox->getLvglObject(), LV_ALIGN_BOTTOM_LEFT, 0, 0);
    
    // *velocity button
    velocityBtn = new Button(selectArea, 60, 30, "Velocity", true);
    lv_obj_align(velocityBtn->getLvglObject(), LV_ALIGN_BOTTOM_LEFT, 100, 0);
    lv_obj_set_style_text_font(velocityBtn->getLabelObject(), font_small, 0);
    velocityBtn->setPressedCallback(onVelocityBtnPressed, this);
    velocityBtn->setToggle(useVelocity);

    // *pitch bend button
    // add a dropdown right under it
    pitchDropdown = lv_dropdown_create(selectArea);
    lv_obj_set_size(pitchDropdown, 60, 30);
    lv_obj_align(pitchDropdown, LV_ALIGN_BOTTOM_LEFT, 170, 0);
    lv_dropdown_set_options(pitchDropdown, "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12");
    lv_obj_add_event_cb(pitchDropdown, onPitchDropdownSelect, LV_EVENT_VALUE_CHANGED, this);

    pitchBtn = new Button(selectArea, 60, 30, "Pitch", true);
    lv_obj_align(pitchBtn->getLvglObject(), LV_ALIGN_BOTTOM_LEFT, 170, 0);
    pitchBtn->setPressedCallback(onPitchBtnPressed, this);
    pitchBtn->setHoldCallback(onPitchBtnHolded, this);
    pitchBtn->setToggle(usePitchbend);
    lv_obj_set_style_text_font(pitchBtn->getLabelObject(), font_small, 0);
    // set dropdown value
    lv_dropdown_set_selected(pitchDropdown, pitchbendRange - 1);
    lv_event_send(pitchDropdown, LV_EVENT_VALUE_CHANGED, NULL);

    //  *volume meter
    volBar = new VolumeBar(selectArea, 130, 10);
    volBar->setRange(-50, 0);
    volBar->setSmoothing(2);
    lv_obj_align(volBar->getBarObject(), LV_ALIGN_BOTTOM_LEFT, 100, -35);

    // *ITEM AREA
    /*
        osc1  | noise  | ampenv | lfo1
        osc2  | filter | env1   | lfo2
      sampler |  mod   | env2   |
    */
    lv_obj_t *itemArea = lv_obj_create(synthPage->subpageGroup);
    lv_obj_remove_style_all(itemArea);
    lv_obj_set_size(itemArea, 320, 105);
    lv_obj_set_y(itemArea, 100);

    // *column 1
    lv_obj_t *col = createItemMenuColumn(itemArea);
    // osc1 button
    lv_obj_t *btn = createItemBtn(col, "OSC 1");
    oscWaveItemImg[0] = lv_img_create(btn);
    lv_img_set_src(oscWaveItemImg[0], synthPage->oscPage[0]->getOscWaveImg());
    lv_obj_set_align(oscWaveItemImg[0], LV_ALIGN_LEFT_MID);
    lv_obj_add_event_cb(btn, [](lv_event_t *e) {
        SynthPage *synthPage = (SynthPage *)lv_event_get_user_data(e);
        synthPage->switchSubPage((SubPage *)synthPage->oscPage[0]);
    }, LV_EVENT_PRESSED, synthPage);
    // osc2 button
    btn = createItemBtn(col, "OSC2");
    lv_obj_set_y(btn, 35);
    oscWaveItemImg[1] = lv_img_create(btn);
    lv_img_set_src(oscWaveItemImg[1], synthPage->oscPage[1]->getOscWaveImg());
    lv_obj_set_align(oscWaveItemImg[1], LV_ALIGN_LEFT_MID);
    lv_obj_add_event_cb(btn, [](lv_event_t *e) {
        SynthPage *synthPage = (SynthPage *)lv_event_get_user_data(e);
        synthPage->switchSubPage((SubPage *)synthPage->oscPage[1]);
    }, LV_EVENT_PRESSED, synthPage);
    // sampler button
    btn = createItemBtn(col, "Sampler");
    lv_obj_set_y(btn, 70);
    lv_obj_center(lv_obj_get_child(btn, 0));
    lv_obj_add_event_cb(btn, [](lv_event_t *e) {
        SynthPage *synthPage = (SynthPage *)lv_event_get_user_data(e);
        synthPage->switchSubPage((SubPage *)synthPage->samplerPage);
    }, LV_EVENT_PRESSED, synthPage);

    // *column 2
    col = createItemMenuColumn(itemArea);
    lv_obj_set_x(col, 80);
    // noise button
    btn = createItemBtn(col, "Noise");
    lv_obj_center(lv_obj_get_child(btn, 0));
    lv_obj_add_event_cb(btn, [](lv_event_t *e) {
        SynthPage *synthPage = (SynthPage *)lv_event_get_user_data(e);
        synthPage->switchSubPage((SubPage *)synthPage->noisePage);
    }, LV_EVENT_PRESSED, synthPage);
    // filter button
    btn = createItemBtn(col, "Filter");
    lv_obj_set_y(btn, 35);
    lv_obj_center(lv_obj_get_child(btn, 0));
    lv_obj_add_event_cb(btn, [](lv_event_t *e) {
        SynthPage *synthPage = (SynthPage *)lv_event_get_user_data(e);
        synthPage->switchSubPage((SubPage *)synthPage->filterPage);
    }, LV_EVENT_PRESSED, synthPage);
    // mod button
    btn = createItemBtn(col, "MOD");
    lv_obj_set_y(btn, 70);
    lv_obj_center(lv_obj_get_child(btn, 0));
    lv_obj_add_event_cb(btn, [](lv_event_t *e) {
        SynthPage *synthPage = (SynthPage *)lv_event_get_user_data(e);
        synthPage->switchSubPage((SubPage *)synthPage->modPage);
    }, LV_EVENT_PRESSED, synthPage);

    // *column 3
    col = createItemMenuColumn(itemArea);
    lv_obj_set_x(col, 160);
    // ampenv button
    btn = createItemBtn(col, "AMPENV");
    lv_obj_center(lv_obj_get_child(btn, 0));
    lv_obj_add_event_cb(btn, [](lv_event_t *e) {
        SynthPage *synthPage = (SynthPage *)lv_event_get_user_data(e);
        synthPage->switchSubPage((SubPage *)synthPage->envPage[0]);
    }, LV_EVENT_PRESSED, synthPage);
    // env1 button
    btn = createItemBtn(col, "ENV1");
    lv_obj_set_y(btn, 35);
    lv_obj_center(lv_obj_get_child(btn, 0));
    lv_obj_add_event_cb(btn, [](lv_event_t *e) {
        SynthPage *synthPage = (SynthPage *)lv_event_get_user_data(e);
        synthPage->switchSubPage((SubPage *)synthPage->envPage[1]);
    }, LV_EVENT_PRESSED, synthPage);
    // env2 button
    btn = createItemBtn(col, "ENV2");
    lv_obj_set_y(btn, 70);
    lv_obj_center(lv_obj_get_child(btn, 0));
    lv_obj_add_event_cb(btn, [](lv_event_t *e) {
        SynthPage *synthPage = (SynthPage *)lv_event_get_user_data(e);
        synthPage->switchSubPage((SubPage *)synthPage->envPage[2]);
    }, LV_EVENT_PRESSED, synthPage);

    // *column 4
    col = createItemMenuColumn(itemArea);
    lv_obj_set_x(col, 240);
    // lfo1 button
    btn = createItemBtn(col, "LFO 1");
    lv_obj_set_y(btn, 0);
    lfoWaveItemImg[0] = lv_img_create(btn);
    lv_img_set_src(lfoWaveItemImg[0], synthPage->lfoPage[0]->getLfoWaveImg());
    lv_obj_set_align(lfoWaveItemImg[0], LV_ALIGN_LEFT_MID);
    lv_obj_add_event_cb(btn, [](lv_event_t *e) {
        SynthPage *synthPage = (SynthPage *)lv_event_get_user_data(e);
        synthPage->switchSubPage((SubPage *)synthPage->lfoPage[0]);
    }, LV_EVENT_PRESSED, synthPage);
    // lfo2 button
    btn = createItemBtn(col, "LFO2");
    lv_obj_set_y(btn, 35);
    lfoWaveItemImg[1] = lv_img_create(btn);
    lv_img_set_src(lfoWaveItemImg[1], synthPage->lfoPage[1]->getLfoWaveImg());
    lv_obj_set_align(lfoWaveItemImg[1], LV_ALIGN_LEFT_MID);
    lv_obj_add_event_cb(btn, [](lv_event_t *e) {
        SynthPage *synthPage = (SynthPage *)lv_event_get_user_data(e);
        synthPage->switchSubPage((SubPage *)synthPage->lfoPage[1]);
    }, LV_EVENT_PRESSED, synthPage);
}

void SynthPage::MainPage::unload()
{
    delete volArc;
    delete octaveSpinbox;
    delete velocityBtn;
    delete pitchBtn;
    delete volBar;
    volArc = nullptr;
    octaveSpinbox = nullptr;
    velocityBtn = nullptr;
    pitchBtn = nullptr;
    volBar = nullptr;
    lv_obj_clean(((SynthPage *)parentPage)->subpageGroup);
}

void SynthPage::MainPage::update()
{
    float temp_peak = AudioIO.getMixerPeak(MasterTracks::ANALOG_OUT, MixerTracks::INSTRUMENTS).l;
    if (temp_peak >= 0)
        volBar->setVolume(temp_peak);
}

void SynthPage::MainPage::onBtnPressed(uint8_t pin)
{
    SynthPage *synthPage = (SynthPage *)parentPage;
    switch (pin)
    {
    case BTN_FN0: // TODO: Maybe move these to the mainPage?
        octaveSpinbox->pressButtonMinus();
        break;
    case BTN_FN1:
        octaveSpinbox->pressButtonPlus();
        break;
    }

    synthPage->onBtnPressedDefault(pin);
}

void SynthPage::MainPage::serialize(ofstream &stream)
{
    stream << octave << " " << volume << " " << pitchbendRange << " " << useVelocity << " " << usePitchbend << " " << useModwheel << " ";
}

void SynthPage::MainPage::deserialize(ifstream &stream)
{
    stream >> octave >> volume >> pitchbendRange >> useVelocity >> usePitchbend >> useModwheel;
}

void SynthPage::MainPage::onVolArcPressed(void *targetPointer, lv_obj_t *valueTextObj, int16_t value, int8_t encoderIndex)
{
    MainPage *instance = (MainPage *)targetPointer;
    instance->volume = value;
    AudioSynth.setMasterVol(value);
    lv_label_set_text_fmt(valueTextObj, "%d", value);
}

void SynthPage::MainPage::onVelocityBtnPressed(void *targetPointer, lv_obj_t *labelObj, bool isToggled)
{
    MainPage *instance = (MainPage *)targetPointer;
    instance->useVelocity = isToggled;
    AudioSynth.setUseVelocity(isToggled);
}

void SynthPage::MainPage::onPitchBtnPressed(void *targetPointer, lv_obj_t *labelObj, bool isToggled)
{
    MainPage *instance = (MainPage *)targetPointer;
    instance->usePitchbend = isToggled;
    if (!isToggled)
        AudioSynth.pitchbend(0, 0);
}

void SynthPage::MainPage::onPitchBtnHolded(void *targetPointer, lv_obj_t *labelObj)
{
    MainPage *instance = (MainPage *)targetPointer;
    lv_dropdown_open(instance->pitchDropdown);
}

void SynthPage::MainPage::onOctaveSelect(void *targetPointer, lv_obj_t *valueTextObj, int16_t value)
{
    MainPage *instance = (MainPage *)targetPointer;
    // set value text
    lv_label_set_text_fmt(valueTextObj, "%d", value);
    // set octave
    instance->octave = value;
}

void SynthPage::MainPage::onPitchDropdownSelect(lv_event_t *e)
{
    MainPage *instance = (MainPage *)lv_event_get_user_data(e);
    lv_obj_t *dropdown = lv_event_get_target(e);
    uint8_t id = lv_dropdown_get_selected(dropdown);
    instance->pitchbendRange = id + 1;
    lv_label_set_text_fmt(instance->pitchBtn->getLabelObject(), "Pitch: %d", instance->pitchbendRange);
}

lv_obj_t *SynthPage::MainPage::createItemBtn(lv_obj_t *parent, const char *text)
{
    lv_obj_t *btn = Gui_CreateButton(parent, 76, 30);
    lv_obj_set_style_pad_all(btn, 4, 0);
    lv_obj_t *label = lv_label_create(btn);
    lv_label_set_text(label, text);
    lv_obj_set_align(label, LV_ALIGN_RIGHT_MID);

    return btn;
}

lv_obj_t *SynthPage::MainPage::createItemMenuColumn(lv_obj_t *parent)
{
    lv_obj_t *col = lv_obj_create(parent);
    lv_obj_remove_style_all(col);
    lv_obj_set_size(col, 80, 105);
    lv_obj_set_style_pad_all(col, 2, 0);

    return col;
}

void SynthPage::OscPage::load()
{
    // get parent page reference
    SynthPage *synthPage = (SynthPage*) parentPage;
    // create top bar
    synthPage->createTopBar(synthPage->subpageGroup, (String("Oscillator ") + String(id + 1)).c_str());
    // create itemMenuArea
    lv_obj_t *menuArea = createSubPageItemArea(synthPage->subpageGroup);

    // *waveform selector
    lv_obj_t *label = lv_label_create(menuArea);
    lv_label_set_text(label, "Waveform: ");
    lv_obj_align(label, LV_ALIGN_TOP_LEFT, 0, 10);
    oscWaveDropdown = lv_dropdown_create(menuArea);
    lv_dropdown_set_options(oscWaveDropdown, "Sine\nTriangle\nSawtooth\nSquare");
    lv_obj_set_size(oscWaveDropdown, 150, 35);
    lv_obj_align(oscWaveDropdown, LV_ALIGN_TOP_LEFT, 90, 0);
    lv_obj_add_flag(oscWaveDropdown, LV_OBJ_FLAG_OVERFLOW_VISIBLE);
    lv_obj_add_event_cb(oscWaveDropdown, onOscWaveSelect, LV_EVENT_VALUE_CHANGED, this);
    oscWaveImg = lv_img_create(menuArea);
    lv_obj_align(oscWaveImg, LV_ALIGN_TOP_LEFT, 250, 5);
    // set dropdown value
    lv_dropdown_set_selected(oscWaveDropdown, oscWaveform);
    lv_event_send(oscWaveDropdown, LV_EVENT_VALUE_CHANGED, NULL);

    // *octave selector
    label = lv_label_create(menuArea);
    lv_label_set_text(label, "Octave: ");
    lv_obj_align(label, LV_ALIGN_TOP_LEFT, 0, 50);
    oscOctaveSpinbox = new Spinbox(menuArea);
    lv_obj_align(oscOctaveSpinbox->getLvglObject(), LV_ALIGN_TOP_LEFT, 65, 43);
    oscOctaveSpinbox->setRange(-2, 2);
    oscOctaveSpinbox->setCallback(onOscOctaveSelect, this);
    oscOctaveSpinbox->setValue(oscOctave);

    // *semitone selector
    label = lv_label_create(menuArea);
    lv_label_set_text(label, "Semi: ");
    lv_obj_align(label, LV_ALIGN_TOP_LEFT, 165, 50);
    oscSemiSpinbox = new Spinbox(menuArea);
    lv_obj_align(oscSemiSpinbox->getLvglObject(), LV_ALIGN_TOP_LEFT, 210, 43);
    oscSemiSpinbox->setRange(-12, 12);
    oscSemiSpinbox->setCallback(onOscSemiSelect, this);
    oscSemiSpinbox->setValue(oscSemi);

    // *pwm arc
    oscArc[0] = new ParamArc(menuArea, 1, "PWM", "%", false);
    lv_obj_align(oscArc[0]->getLvglObject(), LV_ALIGN_TOP_LEFT, 0, 100);
    oscArc[0]->bindEncoder(0);
    oscArc[0]->setRange(0, 100);
    oscArc[0]->setCallback(onOscArcPressed, this);
    oscArc[0]->setValue(oscPwm);

    // *detune arc
    oscArc[1] = new ParamArc(menuArea, 2, "Detune", "cent", false);
    lv_obj_align(oscArc[1]->getLvglObject(), LV_ALIGN_TOP_LEFT, 80, 100);
    oscArc[1]->bindEncoder(1);
    oscArc[1]->setRange(-100, 100);
    oscArc[1]->setCallback(onOscArcPressed, this);
    oscArc[1]->setValue(oscDetune);

    // *level arc
    oscArc[2] = new ParamArc(menuArea, 3, "Level", "%", false);
    lv_obj_align(oscArc[2]->getLvglObject(), LV_ALIGN_TOP_LEFT, 160, 100);
    oscArc[2]->bindEncoder(2);
    oscArc[2]->setRange(0, 100);
    oscArc[2]->setCallback(onOscArcPressed, this);
    oscArc[2]->setValue(oscLevel);
}

void SynthPage::OscPage::unload()
{
    delete oscOctaveSpinbox;
    delete oscSemiSpinbox;
    delete oscArc[0];
    delete oscArc[1];
    delete oscArc[2];
    oscOctaveSpinbox = nullptr;
    oscSemiSpinbox = nullptr;
    oscArc[0] = nullptr;
    oscArc[1] = nullptr;
    oscArc[2] = nullptr;
    lv_obj_clean(((SynthPage *)parentPage)->subpageGroup);
}

void SynthPage::OscPage::serialize(ofstream &stream)
{
    stream << oscWaveform << " " << oscOctave << " " << oscSemi << " " << oscPwm << " " << oscDetune << " " << oscLevel << " ";
}

void SynthPage::OscPage::deserialize(ifstream &stream)
{
    stream >> oscWaveform >> oscOctave >> oscSemi >> oscPwm >> oscDetune >> oscLevel;
}

void SynthPage::OscPage::onOscOctaveSelect(void *targetPointer, lv_obj_t *valueTextObj, int16_t value)
{
    OscPage *instance = (OscPage *)targetPointer;
    // set value text
    lv_label_set_text_fmt(valueTextObj, "%d", value);
    // set octave
    instance->oscOctave = value;
    AudioSynth.setOscOctave(instance->id, value);
}

void SynthPage::OscPage::onOscSemiSelect(void *targetPointer, lv_obj_t *valueTextObj, int16_t value)
{
    OscPage *instance = (OscPage *)targetPointer;
    // set value text
    lv_label_set_text_fmt(valueTextObj, "%d", value);
    // set semi
    instance->oscSemi = value;
    AudioSynth.setOscSemi(instance->id, value);
}

void SynthPage::OscPage::onOscArcPressed(void *targetPointer, lv_obj_t *valueTextObj, int16_t value, int8_t encoderIndex)
{
    OscPage *instance = (OscPage *)targetPointer;
    switch (encoderIndex)
    {
    case 0:
        // pwm
        instance->oscPwm = value;
        AudioSynth.setOscPwm(instance->id, value);
        break;
    case 1:
        // detune
        instance->oscDetune = value;
        AudioSynth.setOscDetune(instance->id, value * 0.01f);
        break;
    case 2:
        // level
        instance->oscLevel = value;
        AudioSynth.setOscLevel(instance->id, value);
        break;
    }
    lv_label_set_text_fmt(valueTextObj, "%d", value);
}

void SynthPage::OscPage::onOscWaveSelect(lv_event_t *e)
{
    OscPage *instance = (OscPage *)lv_event_get_user_data(e);
    lv_obj_t *dropdown = lv_event_get_target(e);
    uint8_t wave = lv_dropdown_get_selected(dropdown);
    // set waveform
    instance->oscWaveform = wave;
    AudioSynth.setOscWaveform(instance->id, wave);
    // set waveform image
    const lv_img_dsc_t *img = instance->getOscWaveImg();
    lv_img_set_src(instance->oscWaveImg, img);
}

const lv_img_dsc_t *SynthPage::OscPage::getOscWaveImg()
{
    const lv_img_dsc_t *img;
    switch (this->oscWaveform)
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

void SynthPage::SamplerPage::load()
{
    // get parent page reference
    SynthPage *synthPage = (SynthPage*) parentPage;
    // create top bar
    synthPage->createTopBar(synthPage->subpageGroup, "Sampler");
    // create itemMenuArea
    lv_obj_t *menuArea = createSubPageItemArea(synthPage->subpageGroup);

    // *sample waveform viewer
    waveformChart = Gui_CreateWaveformChart(menuArea, 305, 60, &serMax, &serMin, samplerWaveformPointsMax, samplerWaveformPointsMin);
    lv_chart_set_point_count(waveformChart, 1000);
    lv_obj_set_style_pad_all(waveformChart, 3, 0);
    lv_obj_add_event_cb(waveformChart, onSamplerWaveformChartPressed, LV_EVENT_PRESSED, this);
    if (clip1.getClip() != NULL)
        Gui_WaveFormChartSetPoints(waveformChart, serMax, serMin, (int16_t *)clip1.getClip(), clip1.getClipLength() * AUDIO_BLOCK_SAMPLES);
    
    // *root key selector
    lv_obj_t *label = lv_label_create(menuArea);
    lv_label_set_text(label, "Root Key: ");
    lv_obj_align(label, LV_ALIGN_LEFT_MID, 5, -10);
    rootKeyBtn = new Button(menuArea, -1, 25, "C4");
    lv_obj_align(rootKeyBtn->getLvglObject(), LV_ALIGN_LEFT_MID, 80, -10);
    rootKeyBtn->setPressedCallback(onSamplerRootKeyBtnPressed, this);
    lv_label_set_text(rootKeyBtn->getLabelObject(), noteNumToNoteName(samplerRootKey).c_str());

    // *tune arc
    samplerArc[0] = new ParamArc(menuArea, 1, "Tune", "cent", false);
    lv_obj_align(samplerArc[0]->getLvglObject(), LV_ALIGN_BOTTOM_MID, -120, 0);
    samplerArc[0]->bindEncoder(0);
    samplerArc[0]->setRange(-100, 100);
    samplerArc[0]->setCallback(onSamplerArcPressed, this);
    samplerArc[0]->setValue(samplerTune);

    // *level arc
    samplerArc[1] = new ParamArc(menuArea, 2, "Level", "%", false);
    lv_obj_align(samplerArc[1]->getLvglObject(), LV_ALIGN_BOTTOM_MID, -40, 0);
    samplerArc[1]->bindEncoder(1);
    samplerArc[1]->setRange(0, 100);
    samplerArc[1]->setCallback(onSamplerArcPressed, this);
    samplerArc[1]->setValue(samplerLevel);
}

void SynthPage::SamplerPage::unload()
{
    delete rootKeyBtn;
    delete samplerArc[0];
    delete samplerArc[1];
    rootKeyBtn = nullptr;
    samplerArc[0] = nullptr;
    samplerArc[1] = nullptr;
    lv_obj_clean(((SynthPage *)parentPage)->subpageGroup);
}

void SynthPage::SamplerPage::onBtnPressed(uint8_t pin)
{
    SynthPage *synthPage = (SynthPage *)parentPage;
    int noteNum;
    uint8_t keyNum = PinToKeyNum(pin);
    if (keyNum > 0 && seletctingRootKey)
    {
        noteNum = keyNum - 1 + 12 * synthPage->mainPage->octave;
        samplerRootKey = noteNum;
        AudioSynth.setClipBaseNote(noteNum);
        // change button label
        lv_label_set_text(rootKeyBtn->getLabelObject(), noteNumToNoteName(samplerRootKey).c_str());
        // change msgbox title
        lv_label_set_text_fmt(rootKeySelectTitleText, "Root Key: %s", noteNumToNoteName(noteNum).c_str());
    }
    // still need to call the parent's onBtnPressed
    synthPage->onBtnPressedDefault(pin);
}

void SynthPage::SamplerPage::serialize(ofstream &stream)
{
    stream << samplerTune << " " << samplerLevel << " " << samplerRootKey << " ";
}

void SynthPage::SamplerPage::deserialize(ifstream &stream)
{
    stream >> samplerTune >> samplerLevel >> samplerRootKey;
}

void SynthPage::SamplerPage::onSamplerArcPressed(void *targetPointer, lv_obj_t *valueTextObj, int16_t value, int8_t encoderIndex)
{
    SamplerPage *instance = (SamplerPage *)targetPointer;
    switch (encoderIndex)
    {
    case 0:
        // tune
        instance->samplerTune = value;
        // TODO: Not implemented
        // AudioSynth.setClipTune(value);
        break;
    case 1:
        // level
        instance->samplerLevel = value;
        AudioSynth.setClipLevel(value);
        break;
    }
    lv_label_set_text_fmt(valueTextObj, "%d", value);
}

void SynthPage::SamplerPage::onSamplerRootKeyBtnPressed(void *targetPointer, lv_obj_t *labelObj, bool isToggled)
{
    SamplerPage *instance = (SamplerPage *)targetPointer;
    if (instance->seletctingRootKey)
        return;
    instance->seletctingRootKey = true;
    // show message box
    lv_obj_t *msgbox = lv_msgbox_create(NULL, "Root Key: ", "Press a piano key to select root key.", instance->setRootKeyBtns, false);
    lv_obj_center(msgbox);
    lv_obj_set_style_bg_color(msgbox, lv_color_black(), 0);
    lv_obj_add_event_cb(msgbox, onSamplerRootKeySelectSetPressed, LV_EVENT_VALUE_CHANGED, instance);
    lv_obj_set_style_text_font(lv_msgbox_get_title(msgbox), font_large, 0);
    instance->rootKeySelectTitleText = lv_msgbox_get_title(msgbox);
    lv_label_set_text_fmt(instance->rootKeySelectTitleText, "Root Key: %s", noteNumToNoteName(instance->samplerRootKey).c_str());
}

void SynthPage::SamplerPage::onSamplerWaveformChartPressed(lv_event_t *e)
{
    PageManager.switchPage(PG_SAMPLEEDITOR);
}

void SynthPage::SamplerPage::onSamplerRootKeySelectSetPressed(lv_event_t *e)
{
    SamplerPage *instance = (SamplerPage *)lv_event_get_user_data(e);
    lv_obj_t *msgbox = lv_event_get_current_target(e);
    if (lv_msgbox_get_active_btn(msgbox) == 0)
    {
        // set
        instance->seletctingRootKey = false;
        // close msgbox
        lv_msgbox_close(msgbox);
    }
}

void SynthPage::NoisePage::load()
{
    // get parent page reference
    SynthPage *synthPage = (SynthPage*) parentPage;
    // create top bar
    synthPage->createTopBar(synthPage->subpageGroup, "Noise Generator");
    // create itemMenuArea
    lv_obj_t *menuArea = createSubPageItemArea(synthPage->subpageGroup);

    // *level arc
    noiseArc = new ParamArc(menuArea, 1, "Level", "%");
    lv_obj_align(noiseArc->getLvglObject(), LV_ALIGN_TOP_LEFT, 0, 10);
    noiseArc->bindEncoder(0);
    noiseArc->setRange(0, 100);
    noiseArc->setCallback(onNoiseArcPressed, this);
    noiseArc->setValue(noiseLevel);
}

void SynthPage::NoisePage::unload()
{
    delete noiseArc;
    noiseArc = nullptr;
    lv_obj_clean(((SynthPage *)parentPage)->subpageGroup);
}

void SynthPage::NoisePage::serialize(ofstream &stream)
{
    stream << noiseLevel << " ";
}

void SynthPage::NoisePage::deserialize(ifstream &stream)
{
    stream >> noiseLevel;
}

void SynthPage::NoisePage::onNoiseArcPressed(void *targetPointer, lv_obj_t *valueTextObj, int16_t value, int8_t encoderIndex)
{
    NoisePage *instance = (NoisePage *)targetPointer;
    instance->noiseLevel = value;
    AudioSynth.setNoiseLevel(value);
    lv_label_set_text_fmt(valueTextObj, "%d", value);
}

void SynthPage::FilterPage::load()
{
    // get parent page reference
    SynthPage *synthPage = (SynthPage*) parentPage;
    // create top bar
    synthPage->createTopBar(synthPage->subpageGroup, "Ladder Filter");
    // create itemMenuArea
    lv_obj_t *menuArea = createSubPageItemArea(synthPage->subpageGroup);
    
    // *cutoff arc
    filterArc[0] = new ParamArc(menuArea, 1, "Cutoff", "Hz", false);
    lv_obj_align(filterArc[0]->getLvglObject(), LV_ALIGN_BOTTOM_MID, -120, -80);
    filterArc[0]->bindEncoder(0);
    filterArc[0]->setRange(0, 300);
    filterArc[0]->setCallback(onFilterArcPressed, this);
    filterArc[0]->setValue(filterVal[0]);

    // *resonance arc
    filterArc[1] = new ParamArc(menuArea, 2, "Resonance", "%", false);
    lv_obj_align(filterArc[1]->getLvglObject(), LV_ALIGN_BOTTOM_MID, -40, -80);
    filterArc[1]->bindEncoder(1);
    filterArc[1]->setRange(0, 100);
    filterArc[1]->setCallback(onFilterArcPressed, this);
    filterArc[1]->setValue(filterVal[1]);

    // *drive arc
    filterArc[2] = new ParamArc(menuArea, 3, "Drive", "%", false);
    lv_obj_align(filterArc[2]->getLvglObject(), LV_ALIGN_BOTTOM_MID, 40, -80);
    filterArc[2]->bindEncoder(2);
    filterArc[2]->setRange(0, 100);
    filterArc[2]->setCallback(onFilterArcPressed, this);
    filterArc[2]->setValue(filterVal[2]);

    // *passband gain arc
    filterArc[3] = new ParamArc(menuArea, 4, "Passband\nGain", "dB", false);
    lv_obj_align(filterArc[3]->getLvglObject(), LV_ALIGN_BOTTOM_MID, 120, -80);
    filterArc[3]->bindEncoder(3);
    filterArc[3]->setRange(0, 100);
    filterArc[3]->setCallback(onFilterArcPressed, this);
    filterArc[3]->setValue(filterVal[3]);
}

void SynthPage::FilterPage::unload()
{
    for (uint8_t i = 0; i < 4; i++)
    {
        delete filterArc[i];
        filterArc[i] = nullptr;
    }
    lv_obj_clean(((SynthPage *)parentPage)->subpageGroup);
}

void SynthPage::FilterPage::serialize(ofstream &stream)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        stream << filterVal[i] << " ";
    }
}

void SynthPage::FilterPage::deserialize(ifstream &stream)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        stream >> filterVal[i];
    }
}

void SynthPage::FilterPage::onFilterArcPressed(void *targetPointer, lv_obj_t *valueTextObj, int16_t value, int8_t encoderIndex)
{
    FilterPage *instance = (FilterPage *)targetPointer;
    ParamArc * arc = instance->filterArc[encoderIndex];
    instance->filterVal[encoderIndex] = value;
    float freq;
    int decimal;
    switch (encoderIndex)
    {
    case 0:
        // cutoff
        freq = pow10f(value * 0.01f) * 20.0f;
        AudioSynth.setLadderFreq(freq);
        // set unit text
        if (freq >= 1000)
        {
            freq /= 1000.0f;
            lv_label_set_text(arc->getUnitTextObject(), "kHz");
        }
        else
        {
            lv_label_set_text(arc->getUnitTextObject(), "Hz");
        }
        // set value text
        if (freq < 10)
            decimal = 1;
        else
            decimal = 0;
        lv_label_set_text_fmt(valueTextObj, "%.*f", decimal, freq);
        break;
    case 1: 
        // resonance
        AudioSynth.setLadderResonance(value * 0.01f);
        lv_label_set_text_fmt(valueTextObj, "%d", value);
        break;
    case 2:
        // drive
        AudioSynth.setLadderDrive(value * 0.01f);
        lv_label_set_text_fmt(valueTextObj, "%d", value);
        break;
    case 3:
        // passband gain
        AudioSynth.setLadderPassbandGain(value * 0.01f);
        lv_label_set_text_fmt(valueTextObj, "%d", value);
        break;
    }
}

void SynthPage::ModPage::load()
{
    // get parent page reference
    SynthPage *synthPage = (SynthPage*) parentPage;
    // create top bar
    synthPage->createTopBar(synthPage->subpageGroup, "Modulation");
    // create itemMenuArea
    modMenuArea = createSubPageItemArea(synthPage->subpageGroup);
    lv_obj_add_flag(modMenuArea, LV_OBJ_FLAG_SCROLLABLE);
    
    // column flex layout
    lv_obj_set_flex_flow(modMenuArea, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_scroll_dir(modMenuArea, LV_DIR_VER);
    
    // *"new modulation" button
    createNewModBtn(modMenuArea);

    // load mod entries
    loadModList();
}

void SynthPage::ModPage::unload()
{
    lv_obj_clean(((SynthPage *)parentPage)->subpageGroup);
}

void SynthPage::ModPage::serialize(ofstream &stream)
{
    int modListSize = modList.size();
    stream << modListSize << " ";

    auto it = modList.begin();
    while (it != modList.end())
    {
        stream << it->source << " " << it->target << " " << it->amount << " ";
        it++;
    }
}

void SynthPage::ModPage::deserialize(ifstream &stream)
{
    modList.clear();
    int modListSize;
    stream >> modListSize;
    for (int i = 0; i < modListSize; i++)
    {
        int source;
        int target;
        float amount;
        stream >> source >> target >> amount;
        modList.push_back(ModulationEntry((modSource)source, (modTarget)target, amount));
    }
}

void SynthPage::ModPage::onNewModBtnPressed(lv_event_t *e)
{
    ModPage *instance = (ModPage *)lv_event_get_user_data(e);
    // add modulation
    int8_t id = AudioSynth.addModulation(MOD_SRC_NONE, MOD_TGT_NONE);
    if (id != -1)
    {
        // create a new mod entry
        instance->createModEntry(instance->modMenuArea, id, MOD_SRC_NONE, MOD_TGT_NONE, 0.0f);
        // scroll down
        lv_obj_scroll_by_bounded(instance->modMenuArea, 0, -55, LV_ANIM_ON);
    }
}

void SynthPage::ModPage::onDelModBtnPressed(lv_event_t *e)
{
    ModPage *instance = (ModPage *)lv_event_get_user_data(e);
    // get the to be deleted entry
    lv_obj_t *entry = lv_obj_get_parent(lv_event_get_target(e));
    if (entry == NULL)
        return;
    // remove modulation
    AudioSynth.removeModulation(lv_obj_get_child_id(entry));
    // remove the entry
    lv_obj_del_async(entry); // use async because we are still in a callback
    // schedule a callback to update the id of all mod entries
    auto updateModIdTask = new ExecWithParameter<lv_obj_t *>([](lv_obj_t * data) {
        lv_obj_t *modMenuArea = (lv_obj_t *)data;
        for (uint8_t i = 0; i < lv_obj_get_child_cnt(modMenuArea) - 1; i++) // -1 to exclude the "new modulation" button
        {
            lv_obj_t *entry = lv_obj_get_child(modMenuArea, i);
            lv_obj_t *label = lv_obj_get_child(entry, 5);
            if (label != nullptr)
                lv_label_set_text_fmt(label, "%d", i);
        }
    }, instance->modMenuArea);
    taskManager.scheduleOnce(10, updateModIdTask, TIME_MILLIS, true);
}

void SynthPage::ModPage::onModSourceChange(lv_event_t *e)
{
    lv_obj_t *dropdown = lv_event_get_target(e);
    uint8_t src = lv_dropdown_get_selected(dropdown);
    uint8_t id = lv_obj_get_child_id(lv_obj_get_parent(dropdown));
    AudioSynth.setModulationSource(id, src);
    // todo: memory?
}

void SynthPage::ModPage::onModTargetChange(lv_event_t *e)
{
    lv_obj_t *dropdown = lv_event_get_target(e);
    uint8_t tgt = lv_dropdown_get_selected(dropdown);
    uint8_t id = lv_obj_get_child_id(lv_obj_get_parent(dropdown));
    AudioSynth.setModulationTarget(id, tgt);
}

void SynthPage::ModPage::onModAmountChange(lv_event_t *e)
{
    lv_obj_t *slider = lv_event_get_target(e);
    int8_t amount = lv_slider_get_value(slider);
    uint8_t id = lv_obj_get_child_id(lv_obj_get_parent(slider));
    AudioSynth.setModulationAmount(id, float(amount) / 100.0f);
}

lv_obj_t *SynthPage::ModPage::createModEntry(lv_obj_t* parent, int8_t id, modSource source, modTarget target, float amount)
{
    // delete "new modulation" button
    lv_obj_del(lv_obj_get_child(parent, -1));

    lv_obj_t *entry = lv_obj_create(parent);
    lv_obj_remove_style_all(entry);
    lv_obj_set_size(entry, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_style_pad_all(entry, 5, 0);
    lv_obj_clear_flag(entry, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(entry, LV_OBJ_FLAG_SCROLL_CHAIN_VER);
    // source dropdown
    lv_obj_t *dropdown = lv_dropdown_create(entry);
    lv_obj_set_style_text_font(dropdown, font_small, 0);
    lv_dropdown_set_options_static(dropdown, modSourceStr);
    lv_dropdown_set_selected(dropdown, source);
    lv_obj_set_size(dropdown, 105, 32);
    lv_obj_set_pos(dropdown, 0, 0);
    lv_obj_add_event_cb(dropdown, onModSourceChange, LV_EVENT_VALUE_CHANGED, this);
    lv_obj_t *list = lv_dropdown_get_list(dropdown);
    lv_obj_set_style_text_font(list, font_small, 0);
    // arrow symbol
    lv_obj_t *arrow = lv_label_create(entry);
    lv_label_set_text(arrow, LV_SYMBOL_PLAY);
    lv_obj_set_style_text_color(arrow, color_Grey, 0);
    lv_obj_set_pos(arrow, 108, 9);
    // target dropdown
    dropdown = lv_dropdown_create(entry);
    lv_obj_set_style_text_font(dropdown, font_small, 0);
    lv_dropdown_set_options_static(dropdown, modTargetStr);
    lv_dropdown_set_selected(dropdown, target);
    lv_obj_set_size(dropdown, 140, 32);
    lv_obj_set_pos(dropdown, 125, 0);
    lv_obj_add_event_cb(dropdown, onModTargetChange, LV_EVENT_VALUE_CHANGED, this);
    list = lv_dropdown_get_list(dropdown);
    lv_obj_set_style_text_font(list, font_small, 0);
    // delete button
    lv_obj_t *btn = Gui_CreateButton(entry, 32, 32, LV_SYMBOL_TRASH, false, 1);
    lv_obj_set_pos(btn, 270, 0);
    lv_obj_add_event_cb(btn, onDelModBtnPressed, LV_EVENT_CLICKED, this);
    // amount slider
    lv_obj_t *slider = lv_slider_create(entry);
    lv_obj_set_size(slider, 265, 10);
    lv_obj_set_pos(slider, 0, 40);
    lv_slider_set_mode(slider, LV_SLIDER_MODE_SYMMETRICAL);
    lv_slider_set_range(slider, -100, 100);
    lv_slider_set_value(slider, map(amount, -1.0f, 1.0f, -100, 100), LV_ANIM_OFF);
    lv_obj_set_style_bg_color(slider, color_Grey, 0);
    lv_obj_set_style_bg_color(slider, lv_color_white(), LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(slider, lv_color_white(), LV_PART_KNOB);
    lv_obj_set_style_pad_all(slider, 2, LV_PART_KNOB);
    lv_obj_add_event_cb(slider, onModAmountChange, LV_EVENT_VALUE_CHANGED, this);
    // id text
    lv_obj_t *label = lv_label_create(entry);
    lv_obj_set_style_text_font(label, font_small, 0);
    lv_obj_set_pos(label, 270, 35);
    lv_label_set_text_fmt(label, "%d", id);

    createNewModBtn(parent);

    return entry;
}

lv_obj_t *SynthPage::ModPage::createNewModBtn(lv_obj_t *parent)
{
    // "new modulation" btn
    lv_obj_t *Btn = lv_btn_create(parent);
    lv_obj_set_size(Btn, 300, 35);
    lv_obj_set_style_bg_color(Btn, lv_color_black(), 0);
    lv_obj_set_style_border_color(Btn, color_Grey, 0);
    lv_obj_set_style_border_width(Btn, 2, 0);
    lv_obj_t *label = lv_label_create(Btn);
    lv_label_set_text(label, "+ New Modulation");
    lv_obj_center(label);

    lv_obj_add_event_cb(Btn, onNewModBtnPressed, LV_EVENT_CLICKED, this);

    return Btn;
}

void SynthPage::ModPage::loadModList()
{
    // iterate through the modList and create entries
    std::list<ModulationEntry>::iterator it = modList.begin();
    uint8_t id = 0;
    while (it != modList.end())
    {
        ModulationEntry entry = *it;
        createModEntry(modMenuArea, id, entry.source, entry.target, entry.amount);
        it++;
        id++;
    }
}

void SynthPage::EnvPage::load()
{
    // get parent page reference
    SynthPage *synthPage = (SynthPage*) parentPage;
    // create top bar
    if (id == 0)
        synthPage->createTopBar(synthPage->subpageGroup, "Amplitude Envelope");
    else
        synthPage->createTopBar(synthPage->subpageGroup, (String("Envelope ") + String(id)).c_str());
    // create itemMenuArea
    lv_obj_t *menuArea = createSubPageItemArea(synthPage->subpageGroup);

    // *envelope graph
    envGraph = new EnvelopeGraph(menuArea, 320, 90);

    // *delay arc
    envArc[0] = new ParamArc(menuArea, 0, "Delay", "ms", false);
    lv_obj_align(envArc[0]->getLvglObject(), LV_ALIGN_BOTTOM_MID, -126, 0);
    envArc[0]->setRange(0, ENV_VAL_MAX);
    envArc[0]->setCallback(onEnvArcPressed, this);
    envArc[0]->setValue(envVal[0]);

    // *attack arc
    envArc[1] = new ParamArc(menuArea, 1, "Attack", "ms", false);
    lv_obj_align(envArc[1]->getLvglObject(), LV_ALIGN_BOTTOM_MID, -63, 0);
    envArc[1]->bindEncoder(0);
    envArc[1]->setRange(0, ENV_VAL_MAX);
    envArc[1]->setCallback(onEnvArcPressed, this);
    envArc[1]->setValue(envVal[1]);

    // *Decay arc
    envArc[2] = new ParamArc(menuArea, 2, "Decay", "ms", false);
    lv_obj_align(envArc[2]->getLvglObject(), LV_ALIGN_BOTTOM_MID, 0, 0);
    envArc[2]->bindEncoder(1);
    envArc[2]->setRange(0, ENV_VAL_MAX);
    envArc[2]->setCallback(onEnvArcPressed, this);
    envArc[2]->setValue(envVal[2]);

    // *Sustain arc
    envArc[3] = new ParamArc(menuArea, 3, "Sustain", "%", false);
    lv_obj_align(envArc[3]->getLvglObject(), LV_ALIGN_BOTTOM_MID, 63, 0);
    envArc[3]->bindEncoder(2);
    envArc[3]->setRange(0, 100);
    envArc[3]->setCallback(onEnvArcPressed, this);
    envArc[3]->setValue(envVal[3]);

    // *Release arc
    envArc[4] = new ParamArc(menuArea, 4, "Release", "ms", false);
    lv_obj_align(envArc[4]->getLvglObject(), LV_ALIGN_BOTTOM_MID, 126, 0);
    envArc[4]->bindEncoder(3);
    envArc[4]->setRange(0, ENV_VAL_MAX);
    envArc[4]->setCallback(onEnvArcPressed, this);
    envArc[4]->setValue(envVal[4]);
}

void SynthPage::EnvPage::unload()
{
    delete envGraph;
    envGraph = nullptr;
    for (uint8_t i = 0; i < 5; i++)
    {
        delete envArc[i];
        envArc[i] = nullptr;
    }
    lv_obj_clean(((SynthPage *)parentPage)->subpageGroup);
}

void SynthPage::EnvPage::serialize(ofstream &stream)
{
    for (uint8_t i = 0; i < 5; i++)
    {
        stream << envVal[i] << " ";
    }
}

void SynthPage::EnvPage::deserialize(ifstream &stream)
{
    for (uint8_t i = 0; i < 5; i++)
    {
        stream >> envVal[i];
    }
}

void SynthPage::EnvPage::onEnvArcPressed(void *targetPointer, lv_obj_t *valueTextObj, int16_t value, int8_t encoderIndex)
{
    EnvPage *instance = (EnvPage *)targetPointer;
    // store value
    instance->envVal[encoderIndex + 1] = value;
    // set to AudioSynth
    float valueMs = powf(ENV_VAL_INCREMENT, value) - 1; // sustain is a special case, handled below.
    switch (encoderIndex)
    {
    case -1:
        // delay
        AudioSynth.setEnvDelay(instance->id, valueMs);
        break;
    case 0:
        // attack
        AudioSynth.setEnvAttack(instance->id, valueMs);
        break;
    case 1:
        // decay
        AudioSynth.setEnvDecay(instance->id, valueMs);
        break;
    case 2:
        // sustain
        AudioSynth.setEnvSustain(instance->id, value * 0.01f);
        break;
    case 3:
        // release
        AudioSynth.setEnvRelease(instance->id, valueMs);
        break;
    }
    // update envelope graph
    instance->envGraph->setEnvelope(
                        powf(ENV_VAL_INCREMENT, instance->envVal[0]) - 1,
                        powf(ENV_VAL_INCREMENT, instance->envVal[1]) - 1,
                        powf(ENV_VAL_INCREMENT, instance->envVal[2]) - 1,
                        instance->envVal[3] * 0.01f,
                        powf(ENV_VAL_INCREMENT, instance->envVal[4]) - 1);
    // update value text
    int decimal = 0;
    if (encoderIndex != 2) // not sustain
    {
        // update unit (S or ms)
        if (valueMs >= 1000)
        {
            valueMs *= 0.001f;
            lv_label_set_text(instance->envArc[encoderIndex + 1]->getUnitTextObject(), "S");
        }
        else
        {
            lv_label_set_text(instance->envArc[encoderIndex + 1]->getUnitTextObject(), "ms");
        }
        // decimal count
        if (valueMs < 10)
            decimal = 2;
        else if (valueMs < 100)
            decimal = 1;
        else
            decimal = 0;
        lv_label_set_text_fmt(valueTextObj, "%.*f", decimal, valueMs);
    }
    else // sustain
    {
        lv_label_set_text_fmt(valueTextObj, "%d", value);
    }
}

void SynthPage::LfoPage::load()
{
    // get parent page reference
    SynthPage *synthPage = (SynthPage*) parentPage;
    // create top bar
    synthPage->createTopBar(synthPage->subpageGroup, (String("Low Frequency Oscillator ") + String(id + 1)).c_str());
    // create itemMenuArea
    lv_obj_t *menuArea = createSubPageItemArea  (synthPage->subpageGroup);

    // *lfo waveform selector
    lv_obj_t *label = lv_label_create(menuArea);
    lv_label_set_text(label, "Waveform: ");
    lv_obj_align(label, LV_ALIGN_TOP_LEFT, 0, 10);
    lfoWaveDropdown = lv_dropdown_create(menuArea);
    lv_dropdown_set_options(lfoWaveDropdown, "Sine\nTriangle\nSawtooth\nRev-Sawtooth\nSquare\nSample&Hold");
    lv_obj_set_size(lfoWaveDropdown, 150, 35);
    lv_obj_align(lfoWaveDropdown, LV_ALIGN_TOP_LEFT, 90, 0);
    lv_obj_add_flag(lfoWaveDropdown, LV_OBJ_FLAG_OVERFLOW_VISIBLE);
    lv_obj_add_event_cb(lfoWaveDropdown, onLfoWaveSelect, LV_EVENT_VALUE_CHANGED, this);
    lfoWaveImg = lv_img_create(menuArea);
    lv_obj_align(lfoWaveImg, LV_ALIGN_TOP_LEFT, 250, 5);
    // set dropdown value
    lv_dropdown_set_selected(lfoWaveDropdown, lfoWaveform);
    lv_event_send(lfoWaveDropdown, LV_EVENT_VALUE_CHANGED, NULL);

    // *frequency arc
    lfoArc[0] = new ParamArc(menuArea, 1, "Frequency", "Hz", false);
    lv_obj_align(lfoArc[0]->getLvglObject(), LV_ALIGN_BOTTOM_MID, -120, -40);
    lfoArc[0]->bindEncoder(0);
    lfoArc[0]->setRange(0, 350);
    lfoArc[0]->setCallback(onLfoArcPressed, this);
    lfoArc[0]->setValue(lfoVal[0]);

    // *level arc
    lfoArc[1] = new ParamArc(menuArea, 2, "Level", "%", false);
    lv_obj_align(lfoArc[1]->getLvglObject(), LV_ALIGN_BOTTOM_MID, -40, -40);
    lfoArc[1]->bindEncoder(1);
    lfoArc[1]->setRange(0, 100);
    lfoArc[1]->setCallback(onLfoArcPressed, this);
    lfoArc[1]->setValue(lfoVal[1]);
}

void SynthPage::LfoPage::unload()
{
    delete lfoArc[0];
    delete lfoArc[1];
    lfoArc[0] = nullptr;
    lfoArc[1] = nullptr;
    lv_obj_clean(((SynthPage *)parentPage)->subpageGroup);
}

void SynthPage::LfoPage::serialize(ofstream &stream)
{
    stream << lfoWaveform << " ";
    for (uint8_t i = 0; i < 2; i++)
    {
        stream << lfoVal[i] << " ";
    }
}

void SynthPage::LfoPage::deserialize(ifstream &stream)
{
    stream >> lfoWaveform;
    for (uint8_t i = 0; i < 2; i++)
    {
        stream >> lfoVal[i];
    }
}

void SynthPage::LfoPage::onLfoArcPressed(void *targetPointer, lv_obj_t *valueTextObj, int16_t value, int8_t encoderIndex)
{
    LfoPage *instance = (LfoPage *)targetPointer;
    // store value
    instance->lfoVal[encoderIndex] = value;
    // set to AudioSynth
    float freq;
    int decimal;
    switch (encoderIndex)
    {
    case 0:
        // frequency
        freq = powf(2, value * 0.02f) - 1;
        AudioSynth.setLfoFreq(instance->id, freq);
        if (freq < 10)
            decimal = 3;
        else if (freq < 100)
            decimal = 2;
        else
            decimal = 1;
        lv_label_set_text_fmt(valueTextObj, "%.*f", decimal, freq);
        break;
    case 1:
        // level
        AudioSynth.setLfoLevel(instance->id, value * 0.01f);
        lv_label_set_text_fmt(valueTextObj, "%d", value);
        break;
    }
}

void SynthPage::LfoPage::onLfoWaveSelect(lv_event_t *e)
{
    LfoPage *instance = (LfoPage *)lv_event_get_user_data(e);
    lv_obj_t *dropdown = lv_event_get_target(e);
    uint8_t wave = lv_dropdown_get_selected(dropdown);
    uint8_t id = instance->id;

    AudioSynth.setLfoWaveform(id, wave);
    instance->lfoWaveform = wave;
    const lv_img_dsc_t *img = instance->getLfoWaveImg();
    lv_img_set_src(instance->lfoWaveImg, img);
}

const lv_img_dsc_t *SynthPage::LfoPage::getLfoWaveImg()
{
    const lv_img_dsc_t *img;
    switch (lfoWaveform)
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
        img = &rev_saw_wave;
        break;
    case 4:
        img = &sqr_wave;
        break;
    case 5:
        img = &s_r_wave;
        break;
    }
    return img;
}