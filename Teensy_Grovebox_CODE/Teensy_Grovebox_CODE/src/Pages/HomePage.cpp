#include "HomePage.h"
#include "Hardware.h"

void HomePage::onBtnPressed(uint8_t pin)
{
    switch (pin)
    {
    
    default:
        break;
    }
}

void HomePage::onBtnHold(uint8_t pin)
{
    switch (pin)
    {
    case BTN_PWR:
        PageManager.showPopup(E_PG_POPUP_POWER);
        break;
    }
}

void HomePage::onBtnReleased(uint8_t pin)
{

}

void HomePage::onEncTurned(uint8_t id, int value)
{

}

void HomePage::onJoyUpdate(int joy_x, int joy_y)
{

}

void HomePage::onTouch(int ref)
{
    switch (ref)
    {
    case E_ELEM_HOME_MIDI_BTN:
        PageManager.switchPage(E_PG_MIDI);
        break;
    case E_ELEM_HOME_WAVE_BTN:
        PageManager.switchPage(E_PG_WAVE);
        break;
    default:
        break;
    }
    
}

void HomePage::onCCReceive(u_int8_t channel, u_int8_t control, u_int8_t value)
{

}

void HomePage::configurePage()
{

}

void HomePage::update()
{

}

void HomePage::draw()
{

}

void HomePage::init()
{
    pageID = E_PG_HOME;
    strcpy(pageName, "Home");
}
