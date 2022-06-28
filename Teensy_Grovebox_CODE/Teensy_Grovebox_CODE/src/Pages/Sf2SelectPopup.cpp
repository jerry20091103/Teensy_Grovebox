#include "Sf2SelectPopup.h"
#include "Hardware.h"

void Sf2SelectPopup::onBtnPressed(uint8_t pin)
{
    switch (pin)
    {
    case BTN_FN7:
        // set soundfont

        // exit popup
        PageManager.hidePopup();
        break;
    
    default:
        break;
    }
}

void Sf2SelectPopup::onBtnHold(uint8_t pin)
{
    switch (pin)
    {
    case BTN_PWR:
        PageManager.hidePopup();
        PageManager.showPopup(E_PG_POPUP_POWER);
        break;
    }
}

void Sf2SelectPopup::onBtnReleased(uint8_t pin)
{

}

void Sf2SelectPopup::onEncTurned(uint8_t id, int value)
{
    switch (id)
    {
    case 3: // move selection
        curSelection += value;
        break;
    
    default:
        break;
    }
}

void Sf2SelectPopup::onJoyUpdate(int joy_x, int joy_y)
{

}

void Sf2SelectPopup::onTouch(int ref)
{
    switch (ref)
    {
    case E_ELEM_SF2_BACK_BTN:
        PageManager.hidePopup();
        break;
    case E_ELEM_SF2_LISTBOX:
        Serial.println(gslc_ElemXListboxGetSel(&m_gui, m_pElemSf2Listbox));
        curSelection = gslc_ElemXListboxGetSel(&m_gui, m_pElemSf2Listbox);
        break;
    }
}

void Sf2SelectPopup::onCCReceive(u_int8_t channel, u_int8_t control, u_int8_t value)
{

}

void Sf2SelectPopup::configurePage()
{
    // change to direction mode
    enc3->changePrecision(0, 0);
}

void Sf2SelectPopup::update()
{

}

void Sf2SelectPopup::draw()
{

}

void Sf2SelectPopup::init()
{
    pageID = E_PG_POPUP_SF2_SELECT;
}
