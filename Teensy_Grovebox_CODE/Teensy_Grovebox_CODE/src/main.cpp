#include "Hardware.h"
#include "font_Arial.h"
#include "Controls.h"
#include "Pages/Pages.h"
#include "Audio/AudioObjects.h"
#include "Audio/AudioIO.h"
#include "Audio/AudioSynth.h"

int bar_test;
int batt_level;
unsigned long lastBarUpdate;

// update GUI
void updateGui()
{
    lv_timer_handler();
}

void updatePage()
{
    PageManager.PageArr[PageManager.getCurPage()]->update();
}

extern float tempmonGetTemp(void);

void checkAudioUsage()
{
    Serial.println("Memory:    " + String(AudioMemoryUsageMax()));
    Serial.println("Processor: " + String(AudioProcessorUsageMax()));
    Serial.print(tempmonGetTemp());
    Serial.println("  C");
    AudioMemoryUsageMaxReset();
    AudioProcessorUsageMaxReset();
}

void readKeyVeloctiy()
{
    // get velocity from microphone
    AudioSynth.velocity = peakVelocity.read();
}

PROGMEM
void setup()
{
    // mute amp
    pinMode(0, OUTPUT);
    digitalWrite(0, LOW);

    Serial.begin(9600);
#if LV_USE_LOG != 0
    while (!Serial)
         ; // wait for Arduino Serial Monitor
#endif
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

    // Initialize hardware
    HardwareSetup();
    // Schedule regular tasks
    taskManager.scheduleFixedRate(5, updateGui);
    taskManager.scheduleFixedRate(25, updatePage);
    taskManager.scheduleFixedRate(15, UpdateJoystick);
    taskManager.scheduleFixedRate(15, readKeyVeloctiy);

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