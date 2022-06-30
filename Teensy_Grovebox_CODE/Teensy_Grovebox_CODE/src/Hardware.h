#ifndef HARDWARE_H
#define HARDWARE_H

#include "SPI.h"
#include "ILI9341_T4.h"
#include "lvgl.h"
#include "IoAbstractionWire.h"
#include "TaskManagerIO.h"

// *Pins
// LCD
#define TFT_MOSI 11
#define TFT_MISO 12
#define TFT_SCK 13
#define TFT_DC 9
#define TFT_CS 10
#define TFT_RST 255
#define TFT_BACKLIGHT 6
#define TFT_X 320
#define TFT_Y 240
// Touch display
#define TFT_TOUCH_CS 5
#define TFT_TOUCH_IRQ 4
// SPI (used for lcd and touch)
#define SPI_SPEED 60000000
// Expanders
#define EXPANDER_PIN 100        // The expander pins starts at 100
#define EXPANDER2_PIN 116
#define E1GPA(a) (EXPANDER_PIN + a)         // These converts expander pin numbers to IO pin numbers
#define E1GPB(b) (EXPANDER_PIN + b + 8)     // for the IoAbstraction library
#define E2GPA(a) (EXPANDER2_PIN + a)
#define E2GPB(b) (EXPANDER2_PIN + b + 8)
// Rotray Encoders
#define ENC1A 26
#define ENC1B 25
#define BTN_ENC1 24
#define ENC2A 29
#define ENC2B 28
#define BTN_ENC2 27
#define ENC3A 32
#define ENC3B 31
#define BTN_ENC3 30
#define ENC4A 35
#define ENC4B 34
#define BTN_ENC4 33
// Joysitck
#define JOY_X 41
#define JOY_Y 40
#define BTN_JOY 22
// Misc.
#define AMP_SHDN 0
#define BAR1_OUT 2
#define BAR2_OUT 3
#define BAR_MODE 1
#define BATT_LVL 16
#define HP_DETECT E2GPA(5)
#define BTN_PWR E2GPA(6)
#define PWR_HOLD E2GPA(7)
// FN Keys
#define BTN_FN0 E2GPA(1)
#define BTN_FN1 E2GPA(2)
#define BTN_FN2 E2GPA(3)
#define BTN_FN3 E2GPA(4)
#define BTN_FN4 39
#define BTN_FN5 38
#define BTN_FN6 37
#define BTN_FN7 36
// Piano Keys
#define BTN_K1 E1GPB(0)
#define BTN_K2 E1GPB(1)
#define BTN_K3 E1GPB(2)
#define BTN_K4 E1GPB(3)
#define BTN_K5 E1GPB(4)
#define BTN_K6 E1GPB(5)
#define BTN_K7 E1GPB(6)
#define BTN_K8 E1GPB(7)

#define BTN_K9 E1GPA(0)
#define BTN_K10 E1GPA(1)
#define BTN_K11 E1GPA(2)
#define BTN_K12 E1GPA(3)
#define BTN_K13 E1GPA(4)
#define BTN_K14 E1GPA(5)
#define BTN_K15 E1GPA(6)
#define BTN_K16 E1GPA(7)

#define BTN_K17 E2GPB(0)
#define BTN_K18 E2GPB(1)
#define BTN_K19 E2GPB(2)
#define BTN_K20 E2GPB(3)
#define BTN_K21 E2GPB(4)
#define BTN_K22 E2GPB(5)
#define BTN_K23 E2GPB(6)
#define BTN_K24 E2GPB(7)

#define BTN_K25 E2GPA(0)

// Display driver object
extern ILI9341_T4::ILI9341Driver tft;

// lvgl draw buffer
#define TFT_Y_BUF 40

// IO abstraction object
extern MultiIoAbstractionRef multiIo;

// encoder objects
extern HardwareRotaryEncoder* enc[4];

void HardwareSetup();

#endif