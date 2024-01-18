#include "Arduino.h"
#include "SerialPrint.h"
#include "TeensyDebug.h"

void serialPrintln(const String &str)
{
#ifndef DEBUG
    Serial.println(str);
#endif
}

void serialPrint(const String &str)
{
#ifndef DEBUG
    Serial.print(str);
#endif
}