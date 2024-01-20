#include "MidiPage.h"
#include "Controls.h"
#include "GuiObjects/Colors.h"

// Gui object callbacks
void MidiPage::onCcArcTurned(void *targetPointer, lv_obj_t *valueTextObj, int16_t value, int8_t encoderIndex)
{
    MidiPage *instance = (MidiPage *)targetPointer;
    // update CC
    if (instance->encConfigure[encoderIndex])
        return;
    instance->updateCC(instance->curCC[encoderIndex], value);
    // find other Arcs that are bound to the same CC and update them (without calling the setValue function, this will casuse infinite loop)
    for (uint8_t i = 0; i < 4; i++)
    {
        if (i != encoderIndex && instance->curCC[i] == instance->curCC[encoderIndex] && !instance->encConfigure[i] && instance->ccArc[i] != NULL)
        {
            lv_arc_set_value(instance->ccArc[i]->getLvglObject(), value);
            if (instance->ccArc[i]->getEncoderIndex() >= 0)
            {
                enc[instance->ccArc[i]->getEncoderIndex()]->setCurrentReading(value);
            }
        }
    }
}

void MidiPage::onTogglePitchbend(void *targetPointer, lv_obj_t *labelObj, bool isToggled)
{
    MidiPage *instance = (MidiPage *)targetPointer;
    instance->usePitchbend = isToggled;
}

void MidiPage::onToggleModwheel(void *targetPointer, lv_obj_t *labelObj, bool isToggled)
{
    MidiPage *instance = (MidiPage *)targetPointer;
    instance->useModwheel = isToggled;
}

void MidiPage::onOctaveSelect(void *targetPointer, lv_obj_t *valueTextObj, int16_t value)
{
    MidiPage *instance = (MidiPage *)targetPointer;
    instance->octave = value;
    lv_label_set_text_fmt(valueTextObj, "%d", value);
}

void MidiPage::onChannelSelect(void *targetPointer, lv_obj_t *valueTextObj, int16_t value)
{
    MidiPage *instance = (MidiPage *)targetPointer;
    instance->midiChannel = value;
    lv_label_set_text_fmt(valueTextObj, "%d", value);
}

void MidiPage::onBtnPressed(uint8_t pin)
{
    uint8_t keyNum = PinToKeyNum(pin);
    uint8_t noteNum;
    if (keyNum > 0)
    {
        noteNum = keyNum - 1 + 12 * octave;
#ifndef DEBUG 
        usbMIDI.sendNoteOn(noteNum, 120, midiChannel);
#endif
    }
    else
    {
        switch (pin)
        {
        case BTN_PWR:
            PageManager.switchPage(PG_AUDIO);
            break;
#ifndef DEBUG
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
#endif
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
#ifndef DEBUG
        usbMIDI.sendNoteOff(noteNum, 120, midiChannel);
#endif
    }
    else
    {
        switch (pin)
        {
#ifndef DEBUG
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
#endif
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
        lv_label_set_text_fmt(ccArc[id]->getValueTextObject(), "%d", curCC[id]);
    }
    else
    {
        paramArcBindingTable[id]->encoderCallback(value);
    }
}

void MidiPage::onJoyUpdate(int joy_x, int joy_y)
{
    // TODO: joystick centering
#ifndef DEBUG
    if (usePitchbend)
        usbMIDI.sendPitchBend(map(joy_x, 0, 1019, 8191, -8192), midiChannel);
    if (useModwheel)
        usbMIDI.sendControlChange(1, map(joy_y, 0, 1019, 0, 127), midiChannel);
#endif
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
    // lvgl object creation was moved to load() function
}

void MidiPage::load()
{
    // set encConfigure to false (exit the configure state when loading the page)
    for (uint8_t i = 0; i < 4; i++)
    {
        encConfigure[i] = false;
    }
    // create lvgl objects
    // 4 CC arcs and CC text
    arcGroup = lv_obj_create(screen);
    lv_obj_remove_style_all(arcGroup);
    lv_obj_set_size(arcGroup, 320, 80);
    lv_obj_set_pos(arcGroup, 0, 35);

    for (uint8_t i = 0; i < 4; i++)
    {
        ccArc[i] = new ParamArc(arcGroup, i + 1);
        ccArc[i]->setRangeMax(127);
        ccArc[i]->bindEncoder(i);
        ccArc[i]->setCallback(onCcArcTurned, this);
        lv_obj_set_x(ccArc[i]->getLvglObject(), lv_pct(25 * i));
        // set user data
        ccArc[i]->setValue(storeCC[curCC[i] - CC_MIN]);
        lv_label_set_text_fmt(ccArc[i]->getValueTextObject(), "%d", curCC[i]);
    }
    // button group
    btnGroup = lv_obj_create(screen);
    lv_obj_remove_style_all(btnGroup);
    lv_obj_set_style_pad_all(btnGroup, 10, 0);
    lv_obj_set_size(btnGroup, 320, 135);
    lv_obj_set_pos(btnGroup, 0, 105);
    lv_obj_clear_flag(btnGroup, LV_OBJ_FLAG_SCROLLABLE);
    // pitchbend button
    pitchBtn = new Button(btnGroup, 90, -1, "PitchBend", true);
    pitchBtn->setPressedCallback(onTogglePitchbend, this);
    pitchBtn->setToggle(usePitchbend);
    // mod button
    modBtn = new Button(btnGroup, 90, -1, "ModWheel", true);
    modBtn->setPressedCallback(onToggleModwheel, this);
    modBtn->setToggle(useModwheel);
    lv_obj_set_y(modBtn->getLvglObject(), 45);
    // octave select
    lv_obj_t *label = lv_label_create(btnGroup);
    lv_label_set_text(label, "Octave:");
    lv_obj_set_pos(label, 135, 7);

    octaveSpinbox = new Spinbox(btnGroup);
    octaveSpinbox->setRange(1, 8);
    octaveSpinbox->setValue(octave);
    octaveSpinbox->setCallback(onOctaveSelect, this);
    lv_obj_set_x(octaveSpinbox->getLvglObject(), 205);

    // channel select
    label = lv_label_create(btnGroup);
    lv_label_set_text(label, "Channel:");
    lv_obj_set_pos(label, 130, 52);

    channelSpinbox = new Spinbox(btnGroup);
    channelSpinbox->setRange(1, 16);
    channelSpinbox->setValue(midiChannel);
    channelSpinbox->setCallback(onChannelSelect, this);
    lv_obj_set_pos(channelSpinbox->getLvglObject(), 205, 45);
    channelSpinbox->setValue(midiChannel);

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

void MidiPage::unload()
{
    Serial.println("MidiPage unload");
    // delete GUI objects
    for (uint8_t i = 0; i < 4; i++)
    {
        delete ccArc[i];
    }
    delete pitchBtn;
    delete modBtn;
    delete octaveSpinbox;
    delete channelSpinbox;
    // remember to set pointers to NULL
    for (uint8_t i = 0; i < 4; i++)
    {
        ccArc[i] = NULL;
    }
    pitchBtn = NULL;
    modBtn = NULL;
    octaveSpinbox = NULL;
    channelSpinbox = NULL;
    // delete parent lvgl object
    lv_obj_del(arcGroup);
    lv_obj_del(btnGroup);
    arcGroup = NULL;
    btnGroup = NULL;
}

void MidiPage::updateCC(uint8_t control, uint8_t value)
{
    storeCC[control - CC_MIN] = value;
    // send the midi message
#ifndef DEBUG
    usbMIDI.sendControlChange(control, value, midiChannel);
#endif
}

void MidiPage::toggleEncConfigure(uint8_t id)
{
    if (!encConfigure[id])
    {
        // enter configure state
        encConfigure[id] = true;
        // set arc color to white and set knob size to 0
        lv_obj_set_style_arc_color(ccArc[id]->getLvglObject(), lv_color_white(), LV_PART_INDICATOR);
        lv_obj_set_style_bg_color(ccArc[id]->getLvglObject(), lv_color_white(), LV_PART_KNOB);
        lv_obj_set_style_pad_all(ccArc[id]->getLvglObject(), -1, LV_PART_KNOB);
        // fill the arc
        lv_arc_set_value(ccArc[id]->getLvglObject(), 127);
        // disable touch
        lv_obj_clear_flag(ccArc[id]->getLvglObject(), LV_OBJ_FLAG_CLICKABLE);
        switches.changeEncoderPrecision(id, CC_MAX - CC_MIN, curCC[id] - CC_MIN, false);
    }
    else
    {
        // exit configure state
        encConfigure[id] = false;
        // set arc color back to original color and set knob size to 2
        switch (id)
        {
        case 0:
            lv_obj_set_style_arc_color(ccArc[id]->getLvglObject(), color_Red, LV_PART_INDICATOR);
            lv_obj_set_style_bg_color(ccArc[id]->getLvglObject(), color_Red, LV_PART_KNOB);
            break;
        case 1:
            lv_obj_set_style_arc_color(ccArc[id]->getLvglObject(), color_Yellow, LV_PART_INDICATOR);
            lv_obj_set_style_bg_color(ccArc[id]->getLvglObject(), color_Yellow, LV_PART_KNOB);
            break;
        case 2:
            lv_obj_set_style_arc_color(ccArc[id]->getLvglObject(), color_Blue, LV_PART_INDICATOR);
            lv_obj_set_style_bg_color(ccArc[id]->getLvglObject(), color_Blue, LV_PART_KNOB);
            break;
        case 3:
            lv_obj_set_style_arc_color(ccArc[id]->getLvglObject(), color_Green, LV_PART_INDICATOR);
            lv_obj_set_style_bg_color(ccArc[id]->getLvglObject(), color_Green, LV_PART_KNOB);
            break;
        }
        lv_obj_set_style_pad_all(ccArc[id]->getLvglObject(), 2, LV_PART_KNOB);
        // set the arc value back to the stored value
        lv_arc_set_value(ccArc[id]->getLvglObject(), storeCC[curCC[id] - CC_MIN]);
        // enable touch
        lv_obj_add_flag(ccArc[id]->getLvglObject(), LV_OBJ_FLAG_CLICKABLE);
        switches.changeEncoderPrecision(id, 127, storeCC[curCC[id] - CC_MIN], true);
    }
}

void MidiPage::configurePage()
{
    
}

void MidiPage::setUserData()
{
    
}