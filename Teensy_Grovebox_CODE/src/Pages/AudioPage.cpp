#include "AudioPage.h"
#include "Hardware.h"
#include "Controls.h"
#include "Audio/AudioUtility.h"
#include "GuiObjects/Colors.h"

void AudioPage::onBtnPressedDefault(uint8_t pin)
{
    uint8_t keyNum = PinToKeyNum(pin);
    if (keyNum > 0)
    {
        PageManager.PageArr[PageManager.getPrevPage()]->onBtnPressed(pin);
    }
    else
    {
        switch (pin)
        {
        case BTN_PWR:
            PageManager.goBack();
            break;
        case BTN_JOY:
            PageManager.PageArr[PageManager.getPrevPage()]->onBtnPressed(pin);
            break;
        }
    }
}

void AudioPage::onBtnHoldDefault(uint8_t pin)
{
    switch (pin)
    {
    case BTN_PWR:
        PageManager.showPowerPopup();
        break;
    }
}

void AudioPage::onBtnReleasedDefault(uint8_t pin)
{
    uint8_t keyNum = PinToKeyNum(pin);
    if (keyNum > 0)
    {
        PageManager.PageArr[PageManager.getPrevPage()]->onBtnReleased(pin);
    }
    else
    {
        switch (pin)
        {
        case BTN_JOY:
            PageManager.PageArr[PageManager.getPrevPage()]->onBtnReleased(pin);
            break;
        }
    }
}

void AudioPage::onEncTurnedDefault(uint8_t id, int value)
{
    encoderBindCallback(id, value);
}

void AudioPage::onJoyUpdateDefault(int joy_x, int joy_y)
{
    PageManager.PageArr[PageManager.getPrevPage()]->onJoyUpdate(joy_x, joy_y);
}

void AudioPage::onCCReceiveDefault(u_int8_t channel, u_int8_t control, u_int8_t value)
{
}

void AudioPage::configurePage()
{
    // input source, gain and volume may be changed by synth for velocity, need to change back.
    sgtl5000_1.inputSelect(mainPage->inputSource);
    sgtl5000_1.micGain(mainPage->gain[mainPage->inputSource]);
    if (mainPage->InVol[0] == 0) // mute
        AudioIO.setInputVolume(InputTracks::LINEMIC_IN, 0);
    else
    {
        float gain = dBtoGain(mainPage->InVol[0] - VOL_MAX + 10);
        AudioIO.setInputVolume(InputTracks::LINEMIC_IN, gain);
    }
    AudioIO.setMixerLevelMode(LevelMeterMode::POST_FADER);
}

void AudioPage::updateDefault()
{
}

void AudioPage::init()
{
    pageID = PG_AUDIO;
    strcpy(pageName, "Audio Settings");
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

    // create subpages
    mainPage = new MainPage(this);
    mixerPage[0] = new MixerPage(this, MasterTracks::ANALOG_OUT);
    mixerPage[1] = new MixerPage(this, MasterTracks::USB_OUT);

    curSubPage = mainPage;
}

void AudioPage::loadAll()
{
    mainPage->load();
    mainPage->unload();
    mixerPage[0]->load();
    mixerPage[0]->unload();
    mixerPage[1]->load();
    mixerPage[1]->unload();
}

void AudioPage::createTrackGui(lv_obj_t *parent, ParamArc *&arcRef, VolumeBar **barArrRef, uint8_t color, const char *name)
{
    lv_obj_t *label;
    // create arc
    arcRef = new ParamArc(parent, color, NULL, "dB", false);
    arcRef->setRange(0, VOL_MAX);
    // title
    label = lv_label_create(arcRef->getLvglObject());
    lv_label_set_text(label, name);
    lv_obj_align(label, LV_ALIGN_TOP_LEFT, 80, 2);
    // volume meter and peak led
    for (uint8_t i = 0; i < 2; i++)
    {
        barArrRef[i] = new VolumeBar(arcRef->getLvglObject(), 135, 10);
        lv_obj_align(barArrRef[i]->getBarObject(), LV_ALIGN_CENTER, 105, 5 + 15 * i);
    }
}

void AudioPage::createMixerTrackGui(lv_obj_t *parent, ParamArcMini *&volArcRef, ParamArcMini *&panArcRef, VolumeBar **barArrRef, uint8_t color, const char *name)
{
    // volume arc
    volArcRef = new ParamArcMini(parent, color, NULL, "dB", true);
    volArcRef->setRange(0, VOL_MAX);
    // track title
    lv_obj_t *label = lv_label_create(volArcRef->getLvglObject());
    lv_label_set_text(label, name);
    lv_obj_align(label, LV_ALIGN_CENTER, -50, 0);
    lv_obj_set_style_text_font(label, font_medium, 0);
    // pan arc
    panArcRef = new ParamArcMini(volArcRef->getLvglObject(), 0, NULL, "%", true);
    lv_obj_align(panArcRef->getLvglObject(), LV_ALIGN_CENTER, 45, 0);
    panArcRef->setRange(PAN_MIN, PAN_MAX);
    panArcRef->setSymmetric(true);
    // volume bar
    for (uint8_t i=0; i<2; i++)
    {
        barArrRef[i] = new VolumeBar(volArcRef->getLvglObject(), 135, 8);
        lv_obj_align(barArrRef[i]->getBarObject(), LV_ALIGN_LEFT_MID, 88, -7 + i * 14);
    }
}

lv_obj_t *AudioPage::createTopBar(lv_obj_t *parent, const char *title)
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
        AudioPage *audioPage = (AudioPage *)lv_event_get_user_data(e);
        audioPage->switchSubPage(audioPage->mainPage);
    }, LV_EVENT_PRESSED, this);
    // title label
    lv_obj_t *label = lv_label_create(topBar);
    lv_label_set_text(label, title);
    lv_obj_align(label, LV_ALIGN_LEFT_MID, 80, 0);

    return topBar;
}

void AudioPage::MainPage::load()
{
    // get AudioPage instance
    AudioPage *audioPage = (AudioPage *)parentPage;
    // *tab view
    tabView = lv_tabview_create(audioPage->subpageGroup, LV_DIR_TOP, 30);
    lv_obj_set_size(tabView, 320, 205);
    lv_obj_set_style_bg_color(tabView, lv_color_black(), 0);
    lv_obj_add_event_cb(tabView, onTabSwitch, LV_EVENT_VALUE_CHANGED, this);

    lv_obj_t *label;
    lv_obj_t *btn;

    // *OUTPUT TAB
    lv_obj_t *tab = lv_tabview_add_tab(tabView, "OUTPUT");
    lv_obj_clear_flag(tab, LV_OBJ_FLAG_SCROLLABLE);

    // *analog out and USB out track
    for (uint8_t i = 0; i < 2; i++)
    {
        createTrackGui(tab,
                       OutArc[i],
                       OutBar[i],
                       i + 1, i == 0 ? "Analog" : "USB");
        lv_obj_set_y(OutArc[i]->getLvglObject(), i * 80);
        OutArc[i]->bindEncoder(i);
        OutArc[i]->setRange(0, VOL_MAX);
        OutArc[i]->setCallback(onOutputArcPressed, this);
        OutArc[i]->setValue(OutVol[i]);
        // mixer button
        btn = Gui_CreateButton(OutArc[i]->getLvglObject(),-1 ,-1);
        lv_obj_align(btn, LV_ALIGN_TOP_MID, 160, -5);
        if (i == 0)
        {
            lv_obj_add_event_cb(btn, [](lv_event_t *e) {
                AudioPage *instance = (AudioPage *)lv_event_get_user_data(e);
                instance->switchSubPage(instance->mixerPage[0]);
            }, LV_EVENT_CLICKED, audioPage);
        }
        else 
        {
            lv_obj_add_event_cb(btn, [](lv_event_t *e) {
                AudioPage *instance = (AudioPage *)lv_event_get_user_data(e);
                instance->switchSubPage(instance->mixerPage[1]);
            }, LV_EVENT_CLICKED, audioPage);
        }
        label = lv_label_create(btn);
        lv_label_set_text(label, LV_SYMBOL_EDIT);
        lv_obj_set_style_text_font(label, font_small, 0);
        lv_obj_center(label);
    }

    // *hp volume arc
    hpArc = new ParamArc(tab, 3, MY_HEADPHONE_SYMBOL, "%", false);
    lv_obj_align(hpArc->getLvglObject(), LV_ALIGN_TOP_RIGHT, 0, 20);
    hpArc->bindEncoder(2);
    hpArc->setRange(0, HP_VOL_MAX);
    hpArc->setCallback(onHpArcPressed, this);
    hpArc->setValue(hpVol);
    // headphone logo
    lv_obj_set_style_text_font(hpArc->getTitleTextObject(), font_extraSymbol, LV_PART_MAIN);
    // TODO: Change icons when headphone is plugged in / unplugged

    // *PFL button
    OutPflBtn = new Button(hpArc->getLvglObject(), 60, 25, "PFL", true);
    lv_obj_align(OutPflBtn->getLvglObject(), LV_ALIGN_BOTTOM_MID, 0, 40);
    OutPflBtn->setPressedCallback(onMainPFLBtnPressed, this);
    OutPflBtn->setToggle(usePFL);
    
    // *INPUT TAB
    tab = lv_tabview_add_tab(tabView, "INPUT");
    lv_obj_clear_flag(tab, LV_OBJ_FLAG_SCROLLABLE);

    // *analog in and USB in track
    for (uint8_t i = 0; i < 2; i++)
    {
        createTrackGui(tab,
                       InArc[i],
                       InBar[i],
                       i + 2, i == 0 ? "Analog" : "USB");
        lv_obj_set_pos(InArc[i]->getLvglObject(), 90, i * 80);
        InArc[i]->bindEncoder(i + 1);
        InArc[i]->setRange(0, VOL_MAX);
        InArc[i]->setCallback(onInputArcPressed, this);
        InArc[i]->setValue(InVol[i]);
    }

    // *input gain arc
    gainArc = new ParamArc(tab, 1, "Gain", "dB", false);
    lv_obj_set_y(gainArc->getLvglObject(), 15);
    gainArc->bindEncoder(0);
    gainArc->setRange(0, inputSource ? MIC_GAIN_MAX : LINE_GAIN_MAX);
    gainArc->setCallback(onGainArcPressed, this);
    gainArc->setValue(gain[inputSource]);

    // *input source buttons
    // title
    label = lv_label_create(gainArc->getLvglObject());
    lv_label_set_text(label, "Source");
    lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, 20);
    // line button
    lineBtn = new Button(tab, 60, 25, "LINE", true);
    lv_obj_set_pos(lineBtn->getLvglObject(), 0, 100);
    lineBtn->setPressedCallback(onLineSourceSelect, this);
    lineBtn->setToggle(!inputSource);
    // mic button
    micBtn = new Button(tab, 60, 25, "MIC", true);
    lv_obj_set_pos(micBtn->getLvglObject(), 0, 130);
    micBtn->setPressedCallback(onMicSourceSelect, this);
    micBtn->setToggle(inputSource);

    // *PFL button
    InPflBtn = new Button(tab, -1, 25, "PFL", true);
    lv_obj_set_pos(InPflBtn->getLvglObject(), 250, 0);
    InPflBtn->setPressedCallback(onMainPFLBtnPressed, this);
    InPflBtn->setToggle(usePFL);

    // *POST-DSP TAB
    tab = lv_tabview_add_tab(tabView, "POST-DSP");
    label = lv_label_create(tab);
    lv_label_set_text(label, "TBD");

    // switch to current tab
    lv_tabview_set_act(tabView, curTab, LV_ANIM_OFF);
    lv_event_send(tabView, LV_EVENT_VALUE_CHANGED, NULL);
}

void AudioPage::MainPage::unload()
{
    // the order here is important! Some objects are childs of others
    for (uint8_t i = 0; i < 2; i++)
    {
        delete OutBar[i][0];
        delete OutBar[i][1];
        delete OutArc[i];
        delete InBar[i][0];
        delete InBar[i][1];
        delete InArc[i];
        OutBar[i][0] = nullptr;
        OutBar[i][1] = nullptr;
        OutArc[i] = nullptr;
        InBar[i][0] = nullptr;
        InBar[i][1] = nullptr;
        InArc[i] = nullptr;
    }
    delete OutPflBtn;
    delete hpArc;
    delete InPflBtn;
    delete gainArc;
    delete lineBtn;
    delete micBtn;
    OutPflBtn = nullptr;
    hpArc = nullptr;
    InPflBtn = nullptr;
    gainArc = nullptr;
    lineBtn = nullptr;
    micBtn = nullptr;

    lv_obj_clean(((AudioPage *)parentPage)->subpageGroup);
}

void AudioPage::MainPage::update()
{
    // update volume meters
    floatStereo value;
    // input
    for (uint8_t i = 0; i < 2; i++)
    {
        value = AudioIO.getInputPeak((InputTracks)i);
        if (value.l >= 0)
        {
            InBar[i][0]->setVolume(value.l);
        }
        if (value.r >= 0)
        {
            InBar[i][1]->setVolume(value.r);
        }
    }
    // output
    for (uint8_t i = 0; i < 2; i++)
    {
        value = AudioIO.getMasterPeak((MasterTracks)i);
        if (value.l >= 0)
        {
            OutBar[i][0]->setVolume(value.l);
        }
        if (value.r >= 0)
        {
            OutBar[i][1]->setVolume(value.r);
        }
    }
}

void AudioPage::MainPage::onOutputArcPressed(void *targetPointer, lv_obj_t *valueTextObj, int16_t value, int8_t encoderIndex)
{
    MainPage *instance = (MainPage *)targetPointer;
    instance->OutVol[encoderIndex] = value;
    if (value == 0) // mute
    {
        AudioIO.setMasterVolume((MasterTracks)encoderIndex, 0);
        lv_label_set_text(valueTextObj, "MUTE");
    }
    else
    {
        // convert to gain
        int db = value - VOL_MAX + 10;
        float gain = dBtoGain(db);
        AudioIO.setMasterVolume((MasterTracks)encoderIndex, gain);
        lv_label_set_text_fmt(valueTextObj, "%d", db);
    }
}

void AudioPage::MainPage::onHpArcPressed(void *targetPointer, lv_obj_t *valueTextObj, int16_t value, int8_t encoderIndex)
{
    MainPage *instance = (MainPage *)targetPointer;
    instance->hpVol = value;
    lv_label_set_text_fmt(valueTextObj, "%d", value);
    sgtl5000_1.volume(map((float)value, 0, HP_VOL_MAX, 0, 0.8));
}

void AudioPage::MainPage::onMainPFLBtnPressed(void *targetPointer, lv_obj_t *labelObj, bool isToggled)
{
    MainPage *instance = (MainPage *)targetPointer;
    instance->usePFL = isToggled;
    // set checked state for all PFL buttons on MainPage
    if (isToggled)
    {
        if (instance->InPflBtn != nullptr) // need to check if input tab is loaded because outPFL button is loaded earlier than inputPFL button
            lv_obj_add_state(instance->InPflBtn->getLvglObject(), LV_STATE_CHECKED);
        lv_obj_add_state(instance->OutPflBtn->getLvglObject(), LV_STATE_CHECKED);
        AudioIO.setMasterLevelMode(LevelMeterMode::PRE_FADER);
        AudioIO.setInputLevelMode(LevelMeterMode::PRE_FADER);
    }
    else
    {
        if (instance->InPflBtn != nullptr)
            lv_obj_clear_state(instance->InPflBtn->getLvglObject(), LV_STATE_CHECKED);
        lv_obj_clear_state(instance->OutPflBtn->getLvglObject(), LV_STATE_CHECKED);
        AudioIO.setMasterLevelMode(LevelMeterMode::POST_FADER);
        AudioIO.setInputLevelMode(LevelMeterMode::POST_FADER);
    }
}

void AudioPage::MainPage::onInputArcPressed(void *targetPointer, lv_obj_t *valueTextObj, int16_t value, int8_t encoderIndex)
{
    MainPage *instance = (MainPage *)targetPointer;
    instance->InVol[encoderIndex - 1] = value;
    if (value == 0) // mute
    {
        AudioIO.setInputVolume((InputTracks)(encoderIndex - 1), 0);
        lv_label_set_text(valueTextObj, "MUTE");
    }
    else
    {
        // convert to gain
        int db = value - VOL_MAX + 10;
        float gain = dBtoGain(db);
        AudioIO.setInputVolume((InputTracks)(encoderIndex - 1), gain);
        lv_label_set_text_fmt(valueTextObj, "%d", db);
    }
}

void AudioPage::MainPage::onGainArcPressed(void *targetPointer, lv_obj_t *valueTextObj, int16_t value, int8_t encoderIndex)
{
    MainPage *instance = (MainPage *)targetPointer;
    instance->gain[instance->inputSource] = value;
    lv_label_set_text_fmt(valueTextObj, "%d", value);
    sgtl5000_1.micGain(value);
}

void AudioPage::MainPage::onLineSourceSelect(void *targetPointer, lv_obj_t *labelObj, bool isToggled)
{
    if (isToggled)
    {
        MainPage *instance = (MainPage *)targetPointer;
        instance->inputSource = 0;
        if (instance->micBtn != nullptr)
            lv_obj_clear_state(instance->micBtn->getLvglObject(), LV_STATE_CHECKED);
        sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
        instance->gainArc->setRange(0, LINE_GAIN_MAX);
        instance->gainArc->setValue(instance->gain[0]);
    }
}

void AudioPage::MainPage::onMicSourceSelect(void *targetPointer, lv_obj_t *labelObj, bool isToggled)
{
    if (isToggled)
    {
        MainPage *instance = (MainPage *)targetPointer;
        instance->inputSource = 1;
        if (instance->lineBtn != nullptr)
            lv_obj_clear_state(instance->lineBtn->getLvglObject(), LV_STATE_CHECKED);
        sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
        instance->gainArc->setRange(0, MIC_GAIN_MAX);
        instance->gainArc->setValue(instance->gain[1]);
    }
}

void AudioPage::MainPage::onTabSwitch(lv_event_t *e)
{
    MainPage *instance = (MainPage *)lv_event_get_user_data(e);
    instance->curTab = lv_tabview_get_tab_act(instance->tabView);
    switch (instance->curTab)
    {
    case 0: // output tab
        instance->OutArc[0]->bindEncoder(0);
        instance->OutArc[1]->bindEncoder(1);
        instance->hpArc->bindEncoder(2);
        break;
    case 1: // input tab
        instance->InArc[0]->bindEncoder(1);
        instance->InArc[1]->bindEncoder(2);
        instance->gainArc->bindEncoder(0);
        break;
    case 2: // post-dsp tab
        // TODO
        break;
    }
}

void AudioPage::MixerPage::load()
{
    // get parent AudioPage instance
    AudioPage *audioPage = (AudioPage *)parentPage;
    // create top bar
    if (id == MasterTracks::ANALOG_OUT)
        audioPage->createTopBar(audioPage->subpageGroup, "Analog Output Mixer");
    else
        audioPage->createTopBar(audioPage->subpageGroup, "USB Output Mixer");
    // create itemArea
    lv_obj_t *itemArea = createSubPageItemArea(audioPage->subpageGroup);

    // create mixer tracks
    createMixerTrackGui(itemArea, mixerVolArc[0], mixerPanArc[0], mixerBar[0], 1, "Analog");
    lv_obj_set_pos(mixerVolArc[0]->getLvglObject(), 65, 0);
    createMixerTrackGui(itemArea, mixerVolArc[1], mixerPanArc[1], mixerBar[1], 2, "USB");
    lv_obj_set_pos(mixerVolArc[1]->getLvglObject(), 65, 43);
    createMixerTrackGui(itemArea, mixerVolArc[2], mixerPanArc[2], mixerBar[2], 3, "Inst.");
    lv_obj_set_pos(mixerVolArc[2]->getLvglObject(), 65, 86);

    for (uint8_t i=0; i<3; i++)
    {
        mixerVolArc[i]->bindEncoder(i);
        Gui_setObjIdFlag(mixerVolArc[i]->getValueTextObject(), i);
        Gui_setObjIdFlag(mixerPanArc[i]->getValueTextObject(), i);
        mixerVolArc[i]->setCallback(onMixerVolArcPressed, this);
        mixerPanArc[i]->setCallback(onMixerPanArcPressed, this);
        mixerVolArc[i]->setValue(mixerVol[i]);
        mixerPanArc[i]->setValue(mixerPan[i]);
    }

    
}

void AudioPage::MixerPage::unload()
{
    for (uint8_t i=0; i<3; i++)
    {
        delete mixerBar[i][0];
        delete mixerBar[i][1];
        delete mixerPanArc[i];
        delete mixerVolArc[i];
        mixerBar[i][0] = nullptr;
        mixerBar[i][1] = nullptr;
        mixerPanArc[i] = nullptr;
        mixerVolArc[i] = nullptr;
    }
    lv_obj_clean(((AudioPage *)parentPage)->subpageGroup);
}

void AudioPage::MixerPage::update()
{
    // update volume meters
    floatStereo value;
    for (uint8_t i = 0; i < 3; i++)
    {
        value = AudioIO.getMixerPeak((MasterTracks)id, (MixerTracks)i);
        if (value.l >= 0)
        {
            mixerBar[i][0]->setVolume(value.l);
        }
        if (value.r >= 0)
        {
            mixerBar[i][1]->setVolume(value.r);
        }
    }
}

void AudioPage::MixerPage::onMixerVolArcPressed(void *targetPointer, lv_obj_t *valueTextObj, int16_t value, int8_t encoderIndex)
{
    MixerPage *instance = (MixerPage *)targetPointer;
    // the valueTextObject is used to pass user id flag to the callback function
    uint8_t arcId = Gui_getObjIdFlag(valueTextObj);
    instance->mixerVol[arcId] = value;
    if (value == 0) // mute
    {
        AudioIO.setMixerVolume((MasterTracks)instance->id, (MixerTracks)arcId, 0);
        lv_label_set_text(valueTextObj, "X");
    }
    else
    {
        // convert to gain
        int db = value - VOL_MAX + 10;
        float gain = dBtoGain(db);
        AudioIO.setMixerVolume((MasterTracks)instance->id, (MixerTracks)arcId, gain);
        lv_label_set_text_fmt(valueTextObj, "%d", db);
    }
}

void AudioPage::MixerPage::onMixerPanArcPressed(void *targetPointer, lv_obj_t *valueTextObj, int16_t value, int8_t encoderIndex)
{
    MixerPage *instance = (MixerPage *)targetPointer;
    // the valueTextObject is used to pass user id flag to the callback function
    uint8_t arcId = Gui_getObjIdFlag(valueTextObj);
    instance->mixerPan[arcId] = value;
    // set pan to AudioIO
    AudioIO.setMixerPan((MasterTracks)instance->id, (MixerTracks)arcId, map((float)value, PAN_MIN, PAN_MAX, -1, 1));
    // update text
    if (value == 0)
        lv_label_set_text(valueTextObj, "C");
    else if (value == PAN_MIN)
        lv_label_set_text(valueTextObj, "L");
    else if (value == PAN_MAX)
        lv_label_set_text(valueTextObj, "R");
    else
        lv_label_set_text_fmt(valueTextObj, "%s%d", value > 0 ? "R" : "L", abs(value));
}
