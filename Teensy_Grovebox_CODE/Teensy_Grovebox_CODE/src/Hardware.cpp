#include "Hardware.h"
#include "Test.h"

ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC);
MultiIoAbstractionRef multiIo = multiIoExpander(EXPANDER_PIN);

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
    delay(1000);

    // setup buttons
    switches.initialise(multiIo, true);
    for (int i = 0; i <= 7; i++)
    {
        // expander 1
        switches.addSwitch(E1GPA(i), onBtnPressed);
        switches.addSwitch(E1GPB(i), onBtnPressed);
        // expander 2, some pins on port A are not buttons.
        switches.addSwitch(E2GPB(i), onBtnPressed);
    }
    switches.addSwitch(E2GPA(0), onBtnPressed);
    switches.addSwitch(E2GPA(1), onBtnPressed);
    switches.addSwitch(E2GPA(2), onBtnPressed);
    switches.addSwitch(E2GPA(3), onBtnPressed);
    switches.addSwitch(E2GPA(4), onBtnPressed);
    switches.addSwitch(E2GPA(5), onBtnPressed);
    // encoder push btn
    switches.addSwitch(BTN_ENC1, onBtnPressed);
    switches.addSwitch(BTN_ENC2, onBtnPressed);
    switches.addSwitch(BTN_ENC3, onBtnPressed);
    switches.addSwitch(BTN_ENC4, onBtnPressed);
    // FN btn on teensy pins
    switches.addSwitch(BTN_FN4, onBtnPressed);
    switches.addSwitch(BTN_FN5, onBtnPressed);
    switches.addSwitch(BTN_FN6, onBtnPressed);
    switches.addSwitch(BTN_FN7, onBtnPressed);
    // power btn
    switches.addSwitch(BTN_PWR, onBtnPressed);

    // setup rotray encoders
    HardwareRotaryEncoder* enc0 = new HardwareRotaryEncoder(ENC1A, ENC1B, onEnc0Turned);
    HardwareRotaryEncoder* enc1 = new HardwareRotaryEncoder(ENC2A, ENC2B, onEnc1Turned);
    HardwareRotaryEncoder* enc2 = new HardwareRotaryEncoder(ENC3A, ENC3B, onEnc2Turned);
    HardwareRotaryEncoder* enc3 = new HardwareRotaryEncoder(ENC4A, ENC4B, onEnc3Turned);
    switches.setEncoder(0, enc0);
    switches.setEncoder(1, enc1);
    switches.setEncoder(2, enc2);
    switches.setEncoder(3, enc3);
    switches.changeEncoderPrecision(0, 0, 0);
    switches.changeEncoderPrecision(1, 1024, 512);
    switches.changeEncoderPrecision(2, 1024, 512);
    switches.changeEncoderPrecision(3, 1024, 512);

    // setup joystick
    pinMode(JOY_X, INPUT);
    pinMode(JOY_Y, INPUT);
    switches.addSwitch(BTN_JOY, onBtnPressed);

    // setup LED bars
    pinMode(BAR1_OUT, OUTPUT);
    pinMode(BAR2_OUT, OUTPUT);
    pinMode(BAR_MODE, OUTPUT);
    

    // LCD brightness control
    pinMode(LCD_PWM, OUTPUT);
    analogWrite(LCD_PWM, 250);

    // Battery level
    pinMode(BATT_LVL, INPUT);

    // hold power
    ioDevicePinMode(multiIo, PWR_HOLD, OUTPUT);
    ioDevicePinMode(multiIo, AMP_SHDN, OUTPUT);
    ioDeviceDigitalWriteS(multiIo, PWR_HOLD, HIGH);
    ioDeviceDigitalWriteS(multiIo, AMP_SHDN, HIGH);

}

