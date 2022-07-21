#include "MidiPage.h"
#include "Controls.h"

// lvgl event callbacks
void MidiPage::onArcValueChanged(lv_event_t *e)
{
    MidiPage *instance = (MidiPage *)lv_event_get_user_data(e);
    lv_obj_t *arc = lv_event_get_target(e);
    for (uint8_t i = 0; i < 4; i++)
    {
        if (arc == instance->ccArc[i])
        {
            instance->updateCC(instance->curCC[i], lv_arc_get_value(arc));
            break;
        }
    }
}

void MidiPage::onTogglePitchbend(lv_event_t *e)
{
    MidiPage *instance = (MidiPage *)lv_event_get_user_data(e);
    instance->usePitchbend = !instance->usePitchbend;
}

void MidiPage::onToggleModwheel(lv_event_t *e)
{
    MidiPage *instance = (MidiPage *)lv_event_get_user_data(e);
    instance->useModwheel = !instance->useModwheel;
}

void MidiPage::onOctaveInc(lv_event_t *e)
{
    MidiPage *instance = (MidiPage *)lv_event_get_user_data(e);
    instance->octave++;
    if (instance->octave > 8)
    {
        instance->octave = 8;
    }
    lv_label_set_text_fmt(instance->octaveText, "%d", instance->octave);
}

void MidiPage::onOctaveDec(lv_event_t *e)
{
    MidiPage *instance = (MidiPage *)lv_event_get_user_data(e);
    instance->octave--;
    if (instance->octave < 1)
    {
        instance->octave = 1;
    }
    lv_label_set_text_fmt(instance->octaveText, "%d", instance->octave);
}

void MidiPage::onChannelInc(lv_event_t *e)
{
    MidiPage *instance = (MidiPage *)lv_event_get_user_data(e);
    instance->midiChannel++;
    if (instance->midiChannel > 16)
        instance->midiChannel = 16;
    lv_label_set_text_fmt(instance->channelText, "%d", instance->midiChannel);
}

void MidiPage::onChannelDec(lv_event_t *e)
{
    MidiPage *instance = (MidiPage *)lv_event_get_user_data(e);
    instance->midiChannel--;
    if (instance->midiChannel < 1)
        instance->midiChannel = 1;
    lv_label_set_text_fmt(instance->channelText, "%d", instance->midiChannel);
}

void MidiPage::onBtnPressed(uint8_t pin)
{
    uint8_t keyNum = PinToKeyNum(pin);
    uint8_t noteNum;
    if (keyNum > 0)
    {
        noteNum = keyNum - 1 + 12 * octave;
        usbMIDI.sendNoteOn(noteNum, 120, midiChannel);
    }
    else
    {
        switch (pin)
        {
        case BTN_PWR:
            PageManager.switchPage(PG_AUDIO);
            break;
        case BTN_JOY:
            usbMIDI.sendControlChange(64, 127, midiChannel); // sustain
            break;
        // FN btns
        case BTN_FN0:
            usbMIDI.sendSysEx(4, playMsg);
            break;
        case BTN_FN1:
            usbMIDI.sendSysEx(4, stopMsg);
            break;
        case BTN_FN2:
            usbMIDI.sendSysEx(4, rewindMsg);
            break;
        case BTN_FN3:
            usbMIDI.sendSysEx(4, forwardMsg);
            break;
        case BTN_FN4:
            usbMIDI.sendControlChange(20, 127, midiChannel);
            break;
        case BTN_FN5:
            usbMIDI.sendControlChange(21, 127, midiChannel);
            break;
        case BTN_FN6:
            usbMIDI.sendControlChange(22, 127, midiChannel);
            break;
        case BTN_FN7:
            usbMIDI.sendControlChange(23, 127, midiChannel);
            break;
        // ENC btns
        case BTN_ENC1:
            toggleEncConfigure(0);
            break;
        case BTN_ENC2:
            toggleEncConfigure(1);
            break;
        case BTN_ENC3:
            toggleEncConfigure(2);
            break;
        case BTN_ENC4:
            toggleEncConfigure(3);
            break;
        default:
            break;
        }
    }
}

void MidiPage::onBtnHold(uint8_t pin)
{
    switch (pin)
    {
    case BTN_PWR:
        PageManager.showPowerPopup();
        break;

    default:
        break;
    }
}

void MidiPage::onBtnReleased(uint8_t pin)
{
    uint8_t keyNum = PinToKeyNum(pin);
    uint8_t noteNum;
    if (keyNum > 0)
    {
        noteNum = keyNum - 1 + 12 * octave;
        usbMIDI.sendNoteOff(noteNum, 120, midiChannel);
    }
    else
    {
        switch (pin)
        {
        case BTN_JOY:
            usbMIDI.sendControlChange(64, 0, midiChannel);
            break;
        case BTN_FN2:
            usbMIDI.sendSysEx(4, stopMsg);
            break;
        case BTN_FN3:
            usbMIDI.sendSysEx(4, stopMsg);
            break;
        case BTN_FN4:
            usbMIDI.sendControlChange(20, 0, midiChannel);
            break;
        case BTN_FN5:
            usbMIDI.sendControlChange(21, 0, midiChannel);
            break;
        case BTN_FN6:
            usbMIDI.sendControlChange(22, 0, midiChannel);
            break;
        case BTN_FN7:
            usbMIDI.sendControlChange(23, 0, midiChannel);
            break;

        default:
            break;
        }
    }
}

void MidiPage::onEncTurned(uint8_t id, int value)
{
    if (encConfigure[id])
    {
        curCC[id] = value + CC_MIN;
        lv_label_set_text_fmt(ccText[id], "%d", curCC[id]);
    }
    else
    {
        usbMIDI.sendControlChange(curCC[id], value, midiChannel);
        updateCC(curCC[id], value);
    }
}

void MidiPage::onJoyUpdate(int joy_x, int joy_y)
{
    // TODO: joystick centering
    if (usePitchbend)
        usbMIDI.sendPitchBend(map(joy_x, 0, 1019, 8191, -8192), midiChannel);
    if (useModwheel)
        usbMIDI.sendControlChange(1, map(joy_y, 0, 1019, 0, 127), midiChannel);
}

void MidiPage::onCCReceive(u_int8_t channel, u_int8_t control, u_int8_t value)
{
    if (channel != midiChannel || control < CC_MIN || control > CC_MAX)
    {
        return;
    }
    else
    {
        updateCC(control, value);
    }
}

void MidiPage::update()
{
}

void MidiPage::init()
{
    pageID = PG_MIDI;
    strcpy(pageName, "MIDI");
    // create screen
    screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen, lv_color_black(), 0);
    // create lvgl objects
    // 4 CC arcs and CC text
    lv_obj_t *arcGroup = lv_obj_create(screen);
    lv_obj_remove_style_all(arcGroup);
    lv_obj_set_size(arcGroup, 320, 80);
    lv_obj_set_pos(arcGroup, 0, 35);

    for (uint8_t i = 0; i < 4; i++)
    {
        ccArc[i] = Gui_CreateParamArc(arcGroup, i + 1, NULL, NULL);
        lv_arc_set_range(ccArc[i], 0, 127);
        lv_obj_set_x(ccArc[i], lv_pct(25 * i));
        lv_obj_add_event_cb(ccArc[i], onArcValueChanged, LV_EVENT_VALUE_CHANGED, this);
        ccText[i] = lv_label_create(ccArc[i]);
        lv_obj_center(ccText[i]);
    }
    // button group
    lv_obj_t *btnGroup = lv_obj_create(screen);
    lv_obj_remove_style_all(btnGroup);
    lv_obj_set_style_pad_all(btnGroup, 10, 0);
    lv_obj_set_size(btnGroup, 320, 135);
    lv_obj_set_pos(btnGroup, 0, 105);
    lv_obj_clear_flag(btnGroup, LV_OBJ_FLAG_SCROLLABLE);
    // pitchbend button
    pitchBtn = Gui_CreateButton(btnGroup, true);
    lv_obj_add_event_cb(pitchBtn, onTogglePitchbend, LV_EVENT_CLICKED, this);
    lv_obj_set_width(pitchBtn, 90);
    lv_obj_t *label = lv_label_create(pitchBtn);
    lv_label_set_text(label, "PitchBend");
    lv_obj_center(label);
    // mod button
    modBtn = Gui_CreateButton(btnGroup, true);
    lv_obj_add_event_cb(modBtn, onToggleModwheel, LV_EVENT_CLICKED, this);
    lv_obj_set_width(modBtn, 90);
    lv_obj_set_y(modBtn, 45);
    label = lv_label_create(modBtn);
    lv_label_set_text(label, "ModWheel");
    lv_obj_center(label);
    // octave select
    label = lv_label_create(btnGroup);
    lv_label_set_text(label, "Octave:");
    lv_obj_set_pos(label, 110, 7);

    lv_obj_t *btn = Gui_CreateButton(btnGroup);
    lv_obj_set_x(btn, 180);
    lv_obj_add_event_cb(btn, onOctaveDec, LV_EVENT_CLICKED, this);
    label = lv_label_create(btn);
    lv_label_set_text(label, LV_SYMBOL_MINUS);

    octaveText = lv_label_create(btnGroup);
    lv_obj_set_style_text_font(octaveText, font_large, 0);
    lv_obj_set_pos(octaveText, 232, 7);

    btn = Gui_CreateButton(btnGroup);
    lv_obj_set_x(btn, 260);
    lv_obj_add_event_cb(btn, onOctaveInc, LV_EVENT_CLICKED, this);
    label = lv_label_create(btn);
    lv_label_set_text(label, LV_SYMBOL_PLUS);

    // channel select
    label = lv_label_create(btnGroup);
    lv_label_set_text(label, "Channel:");
    lv_obj_set_pos(label, 105, 7 + 45);

    btn = Gui_CreateButton(btnGroup);
    lv_obj_set_pos(btn, 180, 45);
    lv_obj_add_event_cb(btn, onChannelDec, LV_EVENT_CLICKED, this);
    label = lv_label_create(btn);
    lv_label_set_text(label, LV_SYMBOL_MINUS);

    channelText = lv_label_create(btnGroup);
    lv_obj_set_style_text_font(channelText, font_large, 0);
    lv_obj_set_pos(channelText, 232, 7 + 45);

    btn = Gui_CreateButton(btnGroup);
    lv_obj_set_pos(btn, 260, 45);
    lv_obj_add_event_cb(btn, onChannelInc, LV_EVENT_CLICKED, this);
    label = lv_label_create(btn);
    lv_label_set_text(label, LV_SYMBOL_PLUS);

    // bottom buttons
    btn = Gui_CreateButton(btnGroup, false, 1);
    lv_obj_set_size(btn, 30, 30);
    lv_obj_set_pos(btn, 0, 90);
    lv_obj_clear_flag(btn, LV_OBJ_FLAG_CLICKABLE);
    label = lv_label_create(btn);
    lv_obj_center(label);
    lv_label_set_text(label, LV_SYMBOL_PLAY);

    btn = Gui_CreateButton(btnGroup, false, 1);
    lv_obj_set_size(btn, 30, 30);
    lv_obj_set_pos(btn, 39, 90);
    lv_obj_clear_flag(btn, LV_OBJ_FLAG_CLICKABLE);
    label = lv_label_create(btn);
    lv_obj_center(label);
    lv_label_set_text(label, LV_SYMBOL_STOP);

    btn = Gui_CreateButton(btnGroup, false, 2);
    lv_obj_set_size(btn, 30, 30);
    lv_obj_set_pos(btn, 78, 90);
    lv_obj_clear_flag(btn, LV_OBJ_FLAG_CLICKABLE);
    label = lv_label_create(btn);
    lv_obj_center(label);
    lv_label_set_text(label, LV_SYMBOL_PREV);

    btn = Gui_CreateButton(btnGroup, false, 2);
    lv_obj_set_size(btn, 30, 30);
    lv_obj_set_pos(btn, 117, 90);
    lv_obj_clear_flag(btn, LV_OBJ_FLAG_CLICKABLE);
    label = lv_label_create(btn);
    lv_obj_center(label);
    lv_label_set_text(label, LV_SYMBOL_NEXT);

    btn = Gui_CreateButton(btnGroup, false, 3);
    lv_obj_set_size(btn, 30, 30);
    lv_obj_set_pos(btn, 156, 90);
    lv_obj_clear_flag(btn, LV_OBJ_FLAG_CLICKABLE);
    label = lv_label_create(btn);
    lv_obj_center(label);
    lv_label_set_text(label, "20");

    btn = Gui_CreateButton(btnGroup, false, 3);
    lv_obj_set_size(btn, 30, 30);
    lv_obj_set_pos(btn, 195, 90);
    lv_obj_clear_flag(btn, LV_OBJ_FLAG_CLICKABLE);
    label = lv_label_create(btn);
    lv_obj_center(label);
    lv_label_set_text(label, "21");

    btn = Gui_CreateButton(btnGroup, false, 4);
    lv_obj_set_size(btn, 30, 30);
    lv_obj_set_pos(btn, 234, 90);
    lv_obj_clear_flag(btn, LV_OBJ_FLAG_CLICKABLE);
    label = lv_label_create(btn);
    lv_obj_center(label);
    lv_label_set_text(label, "22");

    btn = Gui_CreateButton(btnGroup, false, 4);
    lv_obj_set_size(btn, 30, 30);
    lv_obj_set_pos(btn, 273, 90);
    lv_obj_clear_flag(btn, LV_OBJ_FLAG_CLICKABLE);
    label = lv_label_create(btn);
    lv_obj_center(label);
    lv_label_set_text(label, "23");
}

void MidiPage::updateCC(uint8_t control, uint8_t value)
{
    storeCC[control - CC_MIN] = value;
    // did not use else if because two encoders may be mapped to the same CC
    for (uint8_t i = 0; i < 4; i++)
    {
        if (control == curCC[i])
        {
            lv_arc_set_value(ccArc[i], value);
            enc[i]->setCurrentReading(value);
        }
    }
}

void MidiPage::toggleEncConfigure(uint8_t id)
{
    if (!encConfigure[id])
    {
        // enter configure state
        encConfigure[id] = true;
        lv_obj_set_style_arc_color(ccArc[id], lv_color_white(), LV_PART_INDICATOR);
        lv_arc_set_value(ccArc[id], 127);
        switches.changeEncoderPrecision(0, CC_MAX - CC_MIN, curCC[id] - CC_MIN, true);
    }
    else
    {
        // exit configure state
        encConfigure[id] = false;
        switch (id)
        {
        case 0:
            lv_obj_set_style_arc_color(ccArc[id], color_Red, LV_PART_INDICATOR);
            break;
        case 1:
            lv_obj_set_style_arc_color(ccArc[id], color_Yellow, LV_PART_INDICATOR);
            break;
        case 2:
            lv_obj_set_style_arc_color(ccArc[id], color_Blue, LV_PART_INDICATOR);
            break;
        case 3:
            lv_obj_set_style_arc_color(ccArc[id], color_Green, LV_PART_INDICATOR);
            break;
        }
        lv_arc_set_value(ccArc[id], storeCC[curCC[id] - CC_MIN]);
        switches.changeEncoderPrecision(0, 127, storeCC[curCC[id] - CC_MIN], false);
    }
}

void MidiPage::configurePage()
{
    for (int i = 0; i < MAX_ROTARY_ENCODERS; i++)
    {
        if (encConfigure[i])
        {
            switches.changeEncoderPrecision(i, CC_MAX - CC_MIN, curCC[i] - CC_MIN, false);
        }
        else
        {
            switches.changeEncoderPrecision(i, 127, storeCC[curCC[i] - CC_MIN], false);
        }
    }
}

void MidiPage::setUserData()
{
    for (uint8_t i = 0; i < 4; i++)
    {
        lv_arc_set_value(ccArc[i], storeCC[curCC[i] - CC_MIN]);
        lv_label_set_text_fmt(ccText[i], "%d", curCC[i]);
    }

    lv_label_set_text_fmt(octaveText, "%d", octave);
    lv_label_set_text_fmt(channelText, "%d", midiChannel);

    if (usePitchbend)
        lv_obj_add_state(pitchBtn, LV_STATE_CHECKED);
    else
        lv_obj_clear_state(pitchBtn, LV_STATE_CHECKED);
    
    if (useModwheel)
        lv_obj_add_state(modBtn, LV_STATE_CHECKED);
    else
        lv_obj_clear_state(modBtn, LV_STATE_CHECKED);
}