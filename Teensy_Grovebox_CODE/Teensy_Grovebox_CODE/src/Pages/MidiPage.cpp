#include "MidiPage.h"
#include "Controls.h"

void MidiPage::onBtnPressed(uint8_t pin)
{
    uint8_t keyNum = PinToKeyNum(pin);
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
            PageManager.switchPage(E_PG_AUDIOOUT);
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
            if(!encConfigure[0])
            {
                // enter configure state
                encConfigure[0] = true;
                gslc_ElemXRingGaugeSetColorInactive(&m_gui, m_pElemMidiRingRed, GSLC_COL_GRAY);
                gslc_ElemXRingGaugeSetColorActiveFlat(&m_gui, m_pElemMidiRingRed, GSLC_COL_WHITE);
                gslc_ElemXRingGaugeSetVal(&m_gui, m_pElemMidiRingRed, 127);
                switches.changeEncoderPrecision(0, CC_MAX - CC_MIN, curCC[0]-CC_MIN, true);
            }
            else
            {
                // exit configure state
                encConfigure[0] = false;
                gslc_ElemXRingGaugeSetColorInactive(&m_gui, m_pElemMidiRingRed, gslc_tsColor{79, 0, 0});
                gslc_ElemXRingGaugeSetColorActiveFlat(&m_gui, m_pElemMidiRingRed, GSLC_COL_RED);
                gslc_ElemXRingGaugeSetVal(&m_gui, m_pElemMidiRingRed, storeCC[curCC[0]-CC_MIN]);
                switches.changeEncoderPrecision(0, 127, storeCC[curCC[0]-CC_MIN], false);
            }
            break;
        case BTN_ENC2:
            if(!encConfigure[1])
            {
                // enter configure state
                encConfigure[1] = true;
                gslc_ElemXRingGaugeSetColorInactive(&m_gui, m_pElemMidiRingYellow, GSLC_COL_GRAY);
                gslc_ElemXRingGaugeSetColorActiveFlat(&m_gui, m_pElemMidiRingYellow, GSLC_COL_WHITE);
                gslc_ElemXRingGaugeSetVal(&m_gui, m_pElemMidiRingYellow, 127);
                switches.changeEncoderPrecision(1, CC_MAX - CC_MIN, curCC[1]-CC_MIN, true);
            }
            else
            {
                // exit configure state
                encConfigure[1] = false;
                gslc_ElemXRingGaugeSetColorInactive(&m_gui, m_pElemMidiRingYellow, gslc_tsColor{75, 68, 0});
                gslc_ElemXRingGaugeSetColorActiveFlat(&m_gui, m_pElemMidiRingYellow, gslc_tsColor{250, 230, 0});
                gslc_ElemXRingGaugeSetVal(&m_gui, m_pElemMidiRingYellow, storeCC[curCC[1]-CC_MIN]);
                switches.changeEncoderPrecision(1, 127, storeCC[curCC[1]-CC_MIN], false);
            }
            break;
        case BTN_ENC3:
            if(!encConfigure[2])
            {
                // enter configure state
                encConfigure[2] = true;
                gslc_ElemXRingGaugeSetColorInactive(&m_gui, m_pElemMidiRingBlue, GSLC_COL_GRAY);
                gslc_ElemXRingGaugeSetColorActiveFlat(&m_gui, m_pElemMidiRingBlue, GSLC_COL_WHITE);
                gslc_ElemXRingGaugeSetVal(&m_gui, m_pElemMidiRingBlue, 127);
                switches.changeEncoderPrecision(2, CC_MAX - CC_MIN, curCC[2]-CC_MIN, true);
            }
            else
            {
                // exit configure state
                encConfigure[2] = false;
                gslc_ElemXRingGaugeSetColorInactive(&m_gui, m_pElemMidiRingBlue, gslc_tsColor{0, 0, 58});
                gslc_ElemXRingGaugeSetColorActiveFlat(&m_gui, m_pElemMidiRingBlue, gslc_tsColor{20, 20, 255});
                gslc_ElemXRingGaugeSetVal(&m_gui, m_pElemMidiRingBlue, storeCC[curCC[2]-CC_MIN]);
                switches.changeEncoderPrecision(2, 127, storeCC[curCC[2]-CC_MIN], false);
            }
            break;
        case BTN_ENC4:
            if(!encConfigure[3])
            {
                // enter configure state
                encConfigure[3] = true;
                gslc_ElemXRingGaugeSetColorInactive(&m_gui, m_pElemMidiRingGreen, GSLC_COL_GRAY);
                gslc_ElemXRingGaugeSetColorActiveFlat(&m_gui, m_pElemMidiRingGreen, GSLC_COL_WHITE);
                gslc_ElemXRingGaugeSetVal(&m_gui, m_pElemMidiRingGreen, 127);
                switches.changeEncoderPrecision(3, CC_MAX - CC_MIN, curCC[3]-CC_MIN, true);
            }
            else
            {
                // exit configure state
                encConfigure[3] = false;
                gslc_ElemXRingGaugeSetColorInactive(&m_gui, m_pElemMidiRingGreen, gslc_tsColor{0, 61, 0});
                gslc_ElemXRingGaugeSetColorActiveFlat(&m_gui, m_pElemMidiRingGreen, GSLC_COL_GREEN_DK2);
                gslc_ElemXRingGaugeSetVal(&m_gui, m_pElemMidiRingGreen, storeCC[curCC[3]-CC_MIN]);
                switches.changeEncoderPrecision(3, 127, storeCC[curCC[3]-CC_MIN], false);
            }
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
        PageManager.showPopup(E_PG_POPUP_POWER);
        break;
    
    default:
        break;
    }
}

void MidiPage::onBtnReleased(uint8_t pin)
{
    uint8_t keyNum = PinToKeyNum(pin);
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
    if(encConfigure[id])
    {
        curCC[id] = value + CC_MIN;
        
        gslc_tsElemRef *ringRef = NULL;
        switch (id)
        {
        case 0: ringRef = m_pElemMidiRingRed;       break;
        case 1: ringRef = m_pElemMidiRingYellow;    break;
        case 2: ringRef = m_pElemMidiRingBlue;      break;
        case 3: ringRef = m_pElemMidiRingGreen;     break;
        }
        gslc_ElemSetTxtStr(&m_gui, ringRef, String(curCC[id]).c_str());
    }
    else
    {   
        usbMIDI.sendControlChange(curCC[id], value, midiChannel);
        updateCC(curCC[id], value);
    }
}

void MidiPage::onJoyUpdate(int joy_x, int joy_y)
{
    if(usePitchbend)
        usbMIDI.sendPitchBend(map(joy_x, 0, 1019, 8191, -8192), midiChannel);
    if(useModwheel)
        usbMIDI.sendControlChange(1, map(joy_y, 0, 1019, 0, 127), midiChannel);
}

void MidiPage::onTouch(int ref)
{
    switch (ref)
    {
    case E_ELEM_MIDI_OCTAVE_INC:
        octave++;
        if (octave > 8)
            octave = 8;
        gslc_ElemSetTxtStr(&m_gui, m_pElemMidiTxtOctave, String(octave).c_str());
        break;
    case E_ELEM_MIDI_OCTAVE_DEC:
        octave--;
        if (octave < 1)
            octave = 1;
        gslc_ElemSetTxtStr(&m_gui, m_pElemMidiTxtOctave, String(octave).c_str());
        break;
    case E_ELEM_MIDI_CHANNEL_INC:
        midiChannel++;
        if (midiChannel > 16)
            midiChannel = 16;
        gslc_ElemSetTxtStr(&m_gui, m_pElemMidiTxtChannel, String(midiChannel).c_str());
        break;
    case E_ELEM_MIDI_CHANNEL_DEC:
        midiChannel--;
        if (midiChannel < 1)
            midiChannel = 1;
        gslc_ElemSetTxtStr(&m_gui, m_pElemMidiTxtChannel, String(midiChannel).c_str());
        break;
    case E_ELEM_MIDI_PITCHBEND_BTN:
        usePitchbend = !usePitchbend;
        toggleButton(m_pElemMidiPitchbendBtn, usePitchbend);
        break;
    case E_ELEM_MIDI_MOD_BTN:
        useModwheel = !useModwheel;
        toggleButton(m_pElemMidiModBtn, useModwheel);
        break;
    }
}

void MidiPage::onCCReceive(u_int8_t channel, u_int8_t control, u_int8_t value)
{
    if(channel != midiChannel || control < CC_MIN || control > CC_MAX)
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
    gslc_ElemSetTxtStr(&m_gui, m_pElemTxtBatt, "\x40");
}

void MidiPage::draw()
{
}

void MidiPage::init()
{
    pageID = E_PG_MIDI;
    strcpy(pageName, "MIDI");
    gslc_ElemSetTxtStr(&m_gui, m_pElemMidiTxtChannel, String(midiChannel).c_str());
    gslc_ElemSetTxtStr(&m_gui, m_pElemMidiTxtOctave, String(octave).c_str());
    toggleButton(m_pElemMidiPitchbendBtn, usePitchbend);
    toggleButton(m_pElemMidiModBtn, useModwheel);

    gslc_tsElemRef *ringRef;
    for(u_int8_t i=0; i<4; i++)
    {
        switch (i)
        {
        case 0: ringRef = m_pElemMidiRingRed;       break;
        case 1: ringRef = m_pElemMidiRingYellow;    break;
        case 2: ringRef = m_pElemMidiRingBlue;      break;
        case 3: ringRef = m_pElemMidiRingGreen;     break;
        }
        gslc_ElemSetTxtStr(&m_gui, ringRef, String(curCC[i]).c_str());
    }
}

void MidiPage::updateCC(uint8_t control, uint8_t value)
{
    storeCC[control-CC_MIN] = value;
    // did not use else if because two encoders may be mapped to the same CC
    if(control == curCC[0])
    {
        gslc_ElemXRingGaugeSetVal(&m_gui, m_pElemMidiRingRed, value);
        enc0->setCurrentReading(value);
    }
    if(control == curCC[1])
    {
        gslc_ElemXRingGaugeSetVal(&m_gui, m_pElemMidiRingYellow, value);
        enc1->setCurrentReading(value);
    }
    if(control == curCC[2])
    {
        gslc_ElemXRingGaugeSetVal(&m_gui, m_pElemMidiRingBlue, value);
        enc2->setCurrentReading(value);
    }
    if(control == curCC[3])
    {
        gslc_ElemXRingGaugeSetVal(&m_gui, m_pElemMidiRingGreen, value);
        enc3->setCurrentReading(value);
    }
}

void MidiPage::configurePage()
{
    for(int i=0; i<MAX_ROTARY_ENCODERS; i++)
    {
        if(encConfigure[i])
        {
            switches.changeEncoderPrecision(i, CC_MAX - CC_MIN, curCC[i]-CC_MIN, false);
        }
        else
        {
            switches.changeEncoderPrecision(i, 127, storeCC[curCC[i]-CC_MIN], false);
        }
    }
}