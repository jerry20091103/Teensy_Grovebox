#include "Test.h"

String debugString = "empty";
unsigned long lastScreenUpdate = 0;
unsigned long lastBarUpdate = 0;
uint8_t bar_test;
uint8_t batt_level;

unsigned long testText(int brightness)
{
    //tft.fillScreen(ILI9341_BLACK);
    unsigned long start = micros();
    //tft.setCursor(0, 0);
    //tft.setTextColor(ILI9341_WHITE);
    //tft.setTextSize(2);
    //tft.println("Hello World!");
    //tft.setTextColor(ILI9341_YELLOW);
    //tft.setTextSize(2);
    //tft.print("Brightness: ");
    //tft.println(brightness);
    //tft.setTextColor(ILI9341_RED);
    //tft.println(debugString);
    //tft.setTextColor(ILI9341_CYAN);
    //tft.print("Bar pwm: ");
    //tft.println(bar_test);
    //tft.print("Battery : ");
    //tft.println(batt_level);


    return micros() - start;
}

void onBtnPressed(pinid_t pin, bool isHeld)
{
    if(!isHeld)
    {
        //usbMIDI.sendNoteOn(60, 255, 1);
        Keyboard.print(pin);
    }
    else
    {
        // power off btn
        if(pin == E2GPA(6))
        {
            ioDeviceDigitalWrite(multiIo, E2GPA(7), LOW);
            ioDeviceSync(multiIo);
        }
        // bar mode FN0, FN1
        else if(pin == E2GPA(1))
        {
            digitalWrite(BAR_MODE, LOW);
        }
        else if(pin == E2GPA(2))
        {
            digitalWrite(BAR_MODE, HIGH);
        }
        // LCD brightness FN2, FN3
        else if(pin == E2GPA(3))
        {
            analogWrite(LCD_PWM, 250);
        }
        else if(pin == E2GPA(4))
        {
            analogWrite(LCD_PWM, 100);
        }
    }

    debugString = "BtnPress: " + String(pin) + ", hold: " + String(isHeld);
    Serial.println(debugString);
    testText(255);
}

void onEnc0Turned(int value)
{
    debugString = "Button: Enc0, value: " + String(value);
    Serial.println(debugString);
    testText(255);
}

void onEnc1Turned(int value)
{
    debugString = "Button: Enc1, value: " + String(value);
    Serial.println(debugString);
    testText(255);
}

void onEnc2Turned(int value)
{
    debugString = "Button: Enc2, value: " + String(value);
    Serial.println(debugString);
    testText(255);
}

void onEnc3Turned(int value)
{
    debugString = "Button: Enc3, value: " + String(value);
    Serial.println(debugString);
    testText(255);
}