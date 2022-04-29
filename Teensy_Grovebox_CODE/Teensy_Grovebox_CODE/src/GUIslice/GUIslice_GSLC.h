//<File !Start!>
// FILE: [GUIslice_GSLC.h]
// Created by GUIslice Builder version: [0.17.b11]
//
// GUIslice Builder Generated GUI Framework File
//
// For the latest guides, updates and support view:
// https://github.com/ImpulseAdventure/GUIslice
//
//<File !End!>

#ifndef _GUISLICE_GEN_H
#define _GUISLICE_GEN_H

// ------------------------------------------------
// Headers to include
// ------------------------------------------------
#include "GUIslice.h"
#include "GUIslice_drv.h"

// Include any extended elements
//<Includes !Start!>
// Include extended elements
#include "elem/XRingGauge.h"
//<Includes !End!>

// ------------------------------------------------
// Headers and Defines for fonts
// Note that font files are located within the Adafruit-GFX library folder:
// ------------------------------------------------
//<Fonts !Start!>
#include <SPI.h>
#include "font_Arial.h"
#include "font_ArialBold.h"
#include "font_AwesomeF000.h"
#include "font_AwesomeF200.h"
//<Fonts !End!>

// ------------------------------------------------
// Defines for resources
// ------------------------------------------------
//<Resources !Start!>
//<Resources !End!>

// ------------------------------------------------
// Enumerations for pages, elements, fonts, images
// ------------------------------------------------
//<Enum !Start!>
enum {E_PG_BASE,E_PG_MIDI};
enum {E_DRAW_LINE1,E_ELEM_BTN5,E_ELEM_MIDI_BLUE_BOX5
      ,E_ELEM_MIDI_BLUE_BOX6,E_ELEM_MIDI_CHANNEL_DEC
      ,E_ELEM_MIDI_CHANNEL_INC,E_ELEM_MIDI_GREEN_BOX7
      ,E_ELEM_MIDI_GREEN_BOX8,E_ELEM_MIDI_OCTAVE_DEC
      ,E_ELEM_MIDI_OCTAVE_INC,E_ELEM_MIDI_RED_BOX1,E_ELEM_MIDI_RED_BOX2
      ,E_ELEM_MIDI_RING_BLUE,E_ELEM_MIDI_RING_GREEN
      ,E_ELEM_MIDI_RING_RED,E_ELEM_MIDI_RING_YELLOW,E_ELEM_MIDI_TEXT12
      ,E_ELEM_MIDI_TEXT13,E_ELEM_MIDI_TEXT14,E_ELEM_MIDI_TEXT15
      ,E_ELEM_MIDI_TEXT16,E_ELEM_MIDI_TEXT23,E_ELEM_MIDI_TEXT24
      ,E_ELEM_MIDI_TEXT25,E_ELEM_MIDI_TEXT26,E_ELEM_MIDI_TEXT_1
      ,E_ELEM_MIDI_TEXT_CHANNEL,E_ELEM_MIDI_TEXT_FB_F049
      ,E_ELEM_MIDI_TEXT_FF_F050,E_ELEM_MIDI_TEXT_OCTAVE
      ,E_ELEM_MIDI_TEXT_PLAY_F04B,E_ELEM_MIDI_TEXT_STOP_F04D
      ,E_ELEM_MIDI_YELLOW_BOX3,E_ELEM_MIDI_YELLOW_BOX4,E_ELEM_TEXT_BATT
      ,E_ELEM_TEXT_TITLE};
// Must use separate enum for fonts with MAX_FONT at end to use gslc_FontSet.
enum {E_ARIAL_12,E_ARIAL_12_BOLD,E_ARIAL_13,E_ARIAL_14,E_AWESOMEF000_10
      ,E_AWESOMEF200_12,MAX_FONT};
//<Enum !End!>

// ------------------------------------------------
// Instantiate the GUI
// ------------------------------------------------

// ------------------------------------------------
// Define the maximum number of elements and pages
// ------------------------------------------------
//<ElementDefines !Start!>
#define MAX_PAGE                2

#define MAX_ELEM_PG_BASE 4 // # Elems total on page
#define MAX_ELEM_PG_BASE_RAM MAX_ELEM_PG_BASE // # Elems in RAM

#define MAX_ELEM_PG_MIDI 32 // # Elems total on page
#define MAX_ELEM_PG_MIDI_RAM MAX_ELEM_PG_MIDI // # Elems in RAM
//<ElementDefines !End!>

// ------------------------------------------------
// Create element storage
// ------------------------------------------------
extern gslc_tsGui                      m_gui;
extern gslc_tsDriver                   m_drv;
extern gslc_tsFont                     m_asFont[MAX_FONT];
extern gslc_tsPage                     m_asPage[MAX_PAGE];

//<GUI_Extra_Elements !Start!>
extern gslc_tsElem                     m_asBasePage1Elem[MAX_ELEM_PG_BASE_RAM];
extern gslc_tsElemRef                  m_asBasePage1ElemRef[MAX_ELEM_PG_BASE];
extern gslc_tsElem                     m_asPage1Elem[MAX_ELEM_PG_MIDI_RAM];
extern gslc_tsElemRef                  m_asPage1ElemRef[MAX_ELEM_PG_MIDI];
extern gslc_tsXRingGauge               m_sXRingGauge1;
extern gslc_tsXRingGauge               m_sXRingGauge2;
extern gslc_tsXRingGauge               m_sXRingGauge3;
extern gslc_tsXRingGauge               m_sXRingGauge4;

#define MAX_STR                 100

//<GUI_Extra_Elements !End!>

// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Element References for direct access
//<Extern_References !Start!>
extern gslc_tsElemRef* m_pElemMidiRingBlue;
extern gslc_tsElemRef* m_pElemMidiRingGreen;
extern gslc_tsElemRef* m_pElemMidiRingRed;
extern gslc_tsElemRef* m_pElemMidiRingYellow;
extern gslc_tsElemRef* m_pElemMidiTxtChannel;
extern gslc_tsElemRef* m_pElemMidiTxtOctave;
extern gslc_tsElemRef* m_pElemTxtBatt;
extern gslc_tsElemRef* m_pElemTxtTitle;
//<Extern_References !End!>

// Define debug message function
static int16_t DebugOut(char ch);

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
bool CbBtnCommon(void* pvGui,void *pvElemRef,gslc_teTouch eTouch,int16_t nX,int16_t nY);
bool CbCheckbox(void* pvGui, void* pvElemRef, int16_t nSelId, bool bState);
bool CbDrawScanner(void* pvGui,void* pvElemRef,gslc_teRedrawType eRedraw);
bool CbKeypad(void* pvGui, void *pvElemRef, int16_t nState, void* pvData);
bool CbListbox(void* pvGui, void* pvElemRef, int16_t nSelId);
bool CbSlidePos(void* pvGui,void* pvElemRef,int16_t nPos);
bool CbSpinner(void* pvGui, void *pvElemRef, int16_t nState, void* pvData);
bool CbTickScanner(void* pvGui,void* pvScope);

// ------------------------------------------------
void InitGUIslice_gen();
#endif // end _GUISLICE_GEN_H
