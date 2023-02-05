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

void MidiPage::onOctaveSelect(lv_event_t *e)
{
    MidiPage *instance = (MidiPage *)lv_event_get_user_data(e);
    lv_obj_t *btn = lv_event_get_target(e);
    if (Gui_getObjIdFlag(btn) == 1)
    {
        // increase
        instance->octave++;
        if (instance->octave > 8)
        {
            instance->octave = 8;
        }
    }
    else
    {
        // decrease
        instance->octave--;
        if (instance->octave < 1)
        {
            instance->octave = 1;
        }
    }
    Gui_SpinboxSetValue(instance->octaveSpinbox, instance->octave);
}

void MidiPage::onChannelSelect(lv_event_t *e)
{
    MidiPage *instance = (MidiPage *)lv_event_get_user_data(e);
    lv_obj_t *btn = lv_event_get_target(e);
    if (Gui_getObjIdFlag(btn) == 1)
    {
        // increase
        instance->midiChannel++;
        if (instance->midiChannel > 16)
            instance->midiChannel = 16;
    }
    else
    {
        // decrease
        instance->midiChannel--;
        if (instance->midiChannel < 1)
            instance->midiChannel = 1;
    }
    Gui_SpinboxSetValue(instance->channelSpinbox, instance->midiChannel);
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
    pitchBtn = Gui_CreateButton(btnGroup, 90, -1, "PitchBend", true);
    lv_obj_add_event_cb(pitchBtn, onTogglePitchbend, LV_EVENT_CLICKED, this);
    // mod button
    modBtn = Gui_CreateButton(btnGroup, 90, -1, "ModWheel", true);
    lv_obj_add_event_cb(modBtn, onToggleModwheel, LV_EVENT_CLICKED, this);
    lv_obj_set_y(modBtn, 45);
    // octave select
    lv_obj_t *label = lv_label_create(btnGroup);
    lv_label_set_text(label, "Octave:");
    lv_obj_set_pos(label, 135, 7);

    octaveSpinbox =  Gui_CreateSpinbox(btnGroup, onOctaveSelect, this);
    lv_obj_set_x(octaveSpinbox, 205);

    // channel select
    label = lv_label_create(btnGroup);
    lv_label_set_text(label, "Channel:");
    lv_obj_set_pos(label, 130, 52);

    channelSpinbox = Gui_CreateSpinbox(btnGroup, onChannelSelect, this);
    lv_obj_set_pos(channelSpinbox, 205, 45);

    // bottom buttons
    lv_obj_t *btn = Gui_CreateButton(btnGroup, 30, 30, LV_SYMBOL_PLAY, false, 1);
    lv_obj_set_pos(btn, 0, 90);
    lv_obj_clear_flag(btn, LV_OBJ_FLAG_CLICKABLE);

    btn = Gui_CreateButton(btnGroup, 30, 30, LV_SYMBOL_STOP, false, 1);
    lv_obj_set_pos(btn, 39, 90);
    lv_obj_clear_flag(btn, LV_OBJ_FLAG_CLICKABLE);

    btn = Gui_CreateButton(btnGroup, 30, 30, LV_SYMBOL_PREV, false, 2);
    lv_obj_set_pos(btn, 78, 90);
    lv_obj_clear_flag(btn, LV_OBJ_FLAG_CLICKABLE);

    btn = Gui_CreateButton(btnGroup, 30, 30, LV_SYMBOL_NEXT, false, 2);
    lv_obj_set_pos(btn, 117, 90);
    lv_obj_clear_flag(btn, LV_OBJ_FLAG_CLICKABLE);

    btn = Gui_CreateButton(btnGroup, 30, 30, "20", false, 3);
    lv_obj_set_pos(btn, 156, 90);
    lv_obj_clear_flag(btn, LV_OBJ_FLAG_CLICKABLE);

    btn = Gui_CreateButton(btnGroup, 30, 30, "21", false, 3);
    lv_obj_set_pos(btn, 195, 90);
    lv_obj_clear_flag(btn, LV_OBJ_FLAG_CLICKABLE);

    btn = Gui_CreateButton(btnGroup, 30, 30, "22", false, 4);
    lv_obj_set_pos(btn, 234, 90);
    lv_obj_clear_flag(btn, LV_OBJ_FLAG_CLICKABLE);

    btn = Gui_CreateButton(btnGroup, 30, 30, "23", false, 4);
    lv_obj_set_pos(btn, 273, 90);
    lv_obj_clear_flag(btn, LV_OBJ_FLAG_CLICKABLE);
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

    Gui_SpinboxSetValue(octaveSpinbox, octave);
    Gui_SpinboxSetValue(channelSpinbox, midiChannel);

    if (usePitchbend)
        lv_obj_add_state(pitchBtn, LV_STATE_CHECKED);
    else
        lv_obj_clear_state(pitchBtn, LV_STATE_CHECKED);

    if (useModwheel)
        lv_obj_add_state(modBtn, LV_STATE_CHECKED);
    else
        lv_obj_clear_state(modBtn, LV_STATE_CHECKED);
}