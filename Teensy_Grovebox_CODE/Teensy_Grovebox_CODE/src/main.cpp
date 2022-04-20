#include "GUIslice/GUIslice_GSLC.h"
#include "Hardware.h"
#include "font_Arial.h"
#include "Test.h"
#include "Controls.h"



void setup()
{
    HardwareSetup();

    //tft.fillScreen(ILI9341_BLACK);
    //tft.setTextColor(ILI9341_YELLOW);
    //tft.setCursor(0, 0);
    //tft.setTextSize(2);
    //tft.println("Waiting for Arduino Serial Monitor...");

    Serial.begin(9600);
    while (!Serial)
        ; // wait for Arduino Serial Monitor
    Serial.println("ILI9341 Test!");

    digitalWrite(BAR_MODE, HIGH);
    bar_test = 10;

    batt_level = analogRead(BATT_LVL);

    gslc_InitDebug(&DebugOut);
    InitGUIslice_gen();
}

void loop(void)
{
    unsigned long curTime = millis();
    if(curTime - lastScreenUpdate > 50)
    {
        int joyX, joyY;
        joyX = analogRead(40);
        joyY = analogRead(41);
        //tft.fillRect(0, 150, 160, 14, ILI9341_BLACK);
        //tft.setCursor(0, 150);
        //tft.println(String(joyX) + ", " + String(joyY));
        lastScreenUpdate = curTime;
    }
    if(curTime - lastBarUpdate > 1000)
    {
        batt_level = analogRead(BATT_LVL);
        bar_test += 20;
        if(bar_test > 210)
            bar_test = 10;
        analogWrite(BAR1_OUT, bar_test);
        analogWrite(BAR2_OUT, bar_test);
        lastBarUpdate = curTime;
    }
    taskManager.runLoop();
    gslc_Update(&m_gui);
}