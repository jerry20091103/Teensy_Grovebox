#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s2;           //xy=590.0000610351562,234.0000286102295
AudioOutputI2S           i2s1;           //xy=804.0000267028809,237.0000057220459
AudioConnection          patchCord1(i2s2, 0, i2s1, 0);
AudioConnection          patchCord2(i2s2, 1, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=710.0000038146973,365.00000381469727
// GUItool: end automatically generated code
