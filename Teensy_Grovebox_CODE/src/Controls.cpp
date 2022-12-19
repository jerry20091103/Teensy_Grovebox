#include "Controls.h"
#include "Pages/Pages.h"

void UpdateJoystick()
{
    // TODO: joystick deadzone tuning
    int joyX, joyY;
    joyX = analogRead(40);
    joyY = analogRead(41);
    if (joyX > 500 && joyX < 520 && joyY > 500 && joyY < 520)
    {
        joyX = 510;
        joyY = 510;
    }
    PageManager.PageArr[PageManager.getCurPage()]->onJoyUpdate(joyX, joyY);
    usbMIDI.read();
}

void BtnPressCallback(pinid_t pin, bool isHeld)
{
    if(isHeld)
        PageManager.PageArr[PageManager.getCurPage()]->onBtnHold(pin);
    else
        PageManager.PageArr[PageManager.getCurPage()]->onBtnPressed(pin);
}

void BtnReleaseCallback(pinid_t pin, bool isHeld)
{
    PageManager.PageArr[PageManager.getCurPage()]->onBtnReleased(pin);
}

void Enc0Callback(int value)
{
    PageManager.PageArr[PageManager.getCurPage()]->onEncTurned(0, value);
}
void Enc1Callback(int value)
{
    PageManager.PageArr[PageManager.getCurPage()]->onEncTurned(1, value);
}
void Enc2Callback(int value)
{
    PageManager.PageArr[PageManager.getCurPage()]->onEncTurned(2, value);
}
void Enc3Callback(int value)
{
    PageManager.PageArr[PageManager.getCurPage()]->onEncTurned(3, value);
}

void onControlChange(byte channel, byte control, byte value)
{
    PageManager.PageArr[PageManager.getCurPage()]->onCCReceive(channel, control, value);
}

// Converts hardware pin numbers to piano key number.
// returns 1~25 (key number), or 0 if the hardware pin is not a piano key.
uint8_t PinToKeyNum(uint8_t pin)
{
    switch (pin)
    {
    case BTN_K1: return 1; break;
    case BTN_K2: return 2; break;
    case BTN_K3: return 3; break;
    case BTN_K4: return 4; break;
    case BTN_K5: return 5; break;
    case BTN_K6: return 6; break;
    case BTN_K7: return 7; break;
    case BTN_K8: return 8; break;
    case BTN_K9: return 9; break;
    case BTN_K10: return 10; break;
    case BTN_K11: return 11; break;
    case BTN_K12: return 12; break;
    case BTN_K13: return 13; break;
    case BTN_K14: return 14; break;
    case BTN_K15: return 15; break;
    case BTN_K16: return 16; break;
    case BTN_K17: return 17; break;
    case BTN_K18: return 18; break;
    case BTN_K19: return 19; break;
    case BTN_K20: return 20; break;
    case BTN_K21: return 21; break;
    case BTN_K22: return 22; break;
    case BTN_K23: return 23; break;
    case BTN_K24: return 24; break;
    case BTN_K25: return 25; break;

    default:
        return 0;
        break;
    }
}