#include "PowerPopup.h"
#include "Hardware.h"

void PowerPopup::onBtnPressed(uint8_t pin)
{
    switch (pin)
    {
    case BTN_PWR:
        onTouch(E_ELEM_POWER_BTN_CALCEL);
        break;
    
    default:
        break;
    }
}

void PowerPopup::onBtnHold(uint8_t pin)
{

}

void PowerPopup::onBtnReleased(uint8_t pin)
{

}

void PowerPopup::onEncTurned(uint8_t id, int value)
{

}

void PowerPopup::onJoyUpdate(int joy_x, int joy_y)
{

}

void PowerPopup::onTouch(int ref)
{
    switch (ref)
    {
    case E_ELEM_POWER_BTN_YES:
        // power off!
        ioDeviceDigitalWriteS(multiIo, PWR_HOLD, LOW);
        break;
    case E_ELEM_POWER_BTN_CALCEL:
        PageManager.hidePopup();
        break;
    
    default:
        break;
    }
    
}

void PowerPopup::onCCReceive(u_int8_t channel, u_int8_t control, u_int8_t value)
{

}

void PowerPopup::configureEncoders()
{

}

void PowerPopup::update()
{

}

void PowerPopup::draw()
{

}

void PowerPopup::init()
{
    pageID = E_PG_POPUP_POWER;
}
