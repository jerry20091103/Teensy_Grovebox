#include "Hardware.h"
#include "Test.h"
#include "Controls.h"

ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC);
MultiIoAbstractionRef multiIo = multiIoExpander(EXPANDER_PIN);

HardwareRotaryEncoder* enc0;
HardwareRotaryEncoder* enc1;
HardwareRotaryEncoder* enc2;
HardwareRotaryEncoder* enc3;

void HardwareSetup()
{
    // Setup LCD
    //tft.begin();
    // Note: you can now set the SPI speed to any value
    // the default value is 30Mhz, but most ILI9341 displays
    // can handle at least 60Mhz and as much as 100Mhz
    //tft.setClock(60000000);
    //tft.setRotation(3);

    // setup io expanders
    Wire.begin();
    Wire.setClock(400000);
    multiIoAddExpander(multiIo, ioFrom23017(0x20, ACTIVE_LOW_OPEN, 17), 16);
    multiIoAddExpander(multiIo, ioFrom23017(0x21, ACTIVE_LOW_OPEN, 17), 16);

    // setup buttons
    switches.initialiseInterrupt(multiIo, true);
    for (int i = 0; i <= 7; i++)
    {
        // expander 1
        switches.addSwitch(E1GPA(i), BtnPressCallback);
        switches.onRelease(E1GPA(i), BtnReleaseCallback);
        switches.addSwitch(E1GPB(i), BtnPressCallback);
        switches.onRelease(E1GPB(i), BtnReleaseCallback);
        // expander 2, some pins on port A are not buttons.
        switches.addSwitch(E2GPB(i), BtnPressCallback);
        switches.onRelease(E2GPB(i), BtnReleaseCallback);
    }
    switches.addSwitch(E2GPA(0), BtnPressCallback);
    switches.onRelease(E2GPA(0), BtnReleaseCallback);
    switches.addSwitch(E2GPA(1), BtnPressCallback);
    switches.onRelease(E2GPA(1), BtnReleaseCallback);
    switches.addSwitch(E2GPA(2), BtnPressCallback);
    switches.onRelease(E2GPA(2), BtnReleaseCallback);
    switches.addSwitch(E2GPA(3), BtnPressCallback);
    switches.onRelease(E2GPA(3), BtnReleaseCallback);
    switches.addSwitch(E2GPA(4), BtnPressCallback);
    switches.onRelease(E2GPA(4), BtnReleaseCallback);
    switches.addSwitch(E2GPA(5), BtnPressCallback);
    switches.onRelease(E2GPA(5), BtnReleaseCallback);
    // encoder push btn
    switches.addSwitch(BTN_ENC1, BtnPressCallback);
    switches.onRelease(BTN_ENC1, BtnReleaseCallback);
    switches.addSwitch(BTN_ENC2, BtnPressCallback);
    switches.onRelease(BTN_ENC2, BtnReleaseCallback);
    switches.addSwitch(BTN_ENC3, BtnPressCallback);
    switches.onRelease(BTN_ENC3, BtnReleaseCallback);
    switches.addSwitch(BTN_ENC4, BtnPressCallback);
    switches.onRelease(BTN_ENC4, BtnReleaseCallback);
    // FN btn on teensy pins
    switches.addSwitch(BTN_FN4, BtnPressCallback);
    switches.onRelease(BTN_FN4, BtnReleaseCallback);
    switches.addSwitch(BTN_FN5, BtnPressCallback);
    switches.onRelease(BTN_FN5, BtnReleaseCallback);
    switches.addSwitch(BTN_FN6, BtnPressCallback);
    switches.onRelease(BTN_FN6, BtnReleaseCallback);
    switches.addSwitch(BTN_FN7, BtnPressCallback);
    switches.onRelease(BTN_FN7, BtnReleaseCallback);
    // power btn
    switches.addSwitch(BTN_PWR, BtnPressCallback);
    switches.onRelease(BTN_PWR, BtnReleaseCallback);

    // setup rotray encoders
    enc0 = new HardwareRotaryEncoder(ENC1A, ENC1B, Enc0Callback, HWACCEL_SLOWER);
    enc1 = new HardwareRotaryEncoder(ENC2A, ENC2B, Enc1Callback, HWACCEL_SLOWER);
    enc2 = new HardwareRotaryEncoder(ENC3A, ENC3B, Enc2Callback, HWACCEL_SLOWER);
    enc3 = new HardwareRotaryEncoder(ENC4A, ENC4B, Enc3Callback, HWACCEL_SLOWER);
    switches.setEncoder(0, enc0);
    switches.setEncoder(1, enc1);
    switches.setEncoder(2, enc2);
    switches.setEncoder(3, enc3);
    switches.changeEncoderPrecision(0, 0, 0);
    switches.changeEncoderPrecision(1, 0, 0);
    switches.changeEncoderPrecision(2, 0, 0);
    switches.changeEncoderPrecision(3, 0, 0);

    // setup joystick
    pinMode(JOY_X, INPUT);
    pinMode(JOY_Y, INPUT);
    switches.addSwitch(BTN_JOY, BtnPressCallback);
    switches.onRelease(BTN_JOY, BtnReleaseCallback);

    // setup LED bars
    pinMode(BAR1_OUT, OUTPUT);
    pinMode(BAR2_OUT, OUTPUT);
    pinMode(BAR_MODE, OUTPUT);
    

    // LCD brightness control
    pinMode(LCD_PWM, OUTPUT);
    analogWrite(LCD_PWM, 200);

    // Battery level
    pinMode(BATT_LVL, INPUT);

    // hold power
    ioDevicePinMode(multiIo, PWR_HOLD, OUTPUT);
    ioDevicePinMode(multiIo, AMP_SHDN, OUTPUT);
    ioDeviceDigitalWriteS(multiIo, PWR_HOLD, HIGH);
    ioDeviceDigitalWriteS(multiIo, AMP_SHDN, LOW);

    // wait until power button released
    while (!ioDeviceDigitalReadS(multiIo, BTN_PWR)) {}

    // Setup midi callbacks
    usbMIDI.setHandleControlChange(onControlChange);

}

