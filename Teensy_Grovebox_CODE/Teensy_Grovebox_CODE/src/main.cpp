#include "GUIslice/GUIslice_GSLC.h"
#include "Hardware.h"
#include "font_Arial.h"
#include "Controls.h"
#include "Pages/Pages.h"
#include "AudioObjects.h"
#include "AudioIO.h"

int bar_test;
int batt_level;
unsigned long lastBarUpdate;

void update_gslc()
{
    gslc_Update(&m_gui);
    PageManager.PageArr[PageManager.getCurPage()]->update();
    PageManager.PageArr[PageManager.getCurPage()]->draw();
}

void checkAudioUsage() 
{
    Serial.println("Memory:    " + String(AudioMemoryUsageMax()));
    Serial.println("Processor: " + String(AudioProcessorUsageMax()));
    AudioMemoryUsageMaxReset();
    AudioProcessorUsageMaxReset();
}

void setup()
{
    // mute amp
    pinMode(0, OUTPUT);
    digitalWrite(0, LOW); 

    Serial.begin(9600);
    while (!Serial)
        ; // wait for Arduino Serial Monitor
    Serial.println("Setup begin!");

    digitalWrite(BAR_MODE, HIGH);
    bar_test = 10;

    batt_level = analogRead(BATT_LVL);

    // Audio connections require memory to work.  For more
    // detailed information, see the MemoryAndCpuUsage example
    AudioMemory(200);
    
    // Enable the audio shield, select input, and enable output
    sgtl5000_1.enable();
    sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
    sgtl5000_1.unmuteLineout();

    //gslc_InitDebug(&DebugOut);
    // Initializes GUI (must call this before taskManager starts)
    InitGUIslice_gen();
    PageManager.Init();
    // Initialize hardware
    HardwareSetup();
    // Schedule regular tasks
    taskManager.scheduleFixedRate(20, update_gslc);
    taskManager.scheduleFixedRate(15, UpdateJoystick);
    // switch to the first page
    PageManager.switchPage(E_PG_MIDI);

    // unmute amp
    digitalWrite(0, HIGH);
    // Change BAR PWM frequencey
    analogWriteFrequency(BAR1_OUT, 10000);
    analogWriteFrequency(BAR2_OUT, 10000);

    // DEBUG
    taskManager.scheduleFixedRate(5000, checkAudioUsage);
}

void loop(void)
{
    unsigned long curTime = millis();
    if (curTime - lastBarUpdate > 1000)
    {
        batt_level = analogRead(BATT_LVL);
        bar_test += 20;
        if (bar_test > 210)
            bar_test = 10;
        analogWrite(BAR1_OUT, bar_test);
        analogWrite(BAR2_OUT, bar_test);
        lastBarUpdate = curTime;
    }
    taskManager.runLoop();
}