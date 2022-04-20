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
#include "elem/XProgress.h"
//<Includes !End!>

// ------------------------------------------------
// Headers and Defines for fonts
// Note that font files are located within the Adafruit-GFX library folder:
// ------------------------------------------------
//<Fonts !Start!>
#include <SPI.h>
#include "font_Arial.h"
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
enum {E_PG_MAIN};
enum {E_COUNTER,E_ELEM_BTN_DEC,E_ELEM_BTN_INC,E_ELEM_PROGRESS1
      ,E_ELEM_TEXT2,E_ELEM_TEXT3};
// Must use separate enum for fonts with MAX_FONT at end to use gslc_FontSet.
enum {E_ARIAL_10,E_ARIAL_12,E_ARIAL_13,MAX_FONT};
//<Enum !End!>

// ------------------------------------------------
// Instantiate the GUI
// ------------------------------------------------

// ------------------------------------------------
// Define the maximum number of elements and pages
// ------------------------------------------------
//<ElementDefines !Start!>
#define MAX_PAGE                1

#define MAX_ELEM_PG_MAIN 6 // # Elems total on page
#define MAX_ELEM_PG_MAIN_RAM MAX_ELEM_PG_MAIN // # Elems in RAM
//<ElementDefines !End!>

// ------------------------------------------------
// Create element storage
// ------------------------------------------------
gslc_tsGui                      m_gui;
gslc_tsDriver                   m_drv;
gslc_tsFont                     m_asFont[MAX_FONT];
gslc_tsPage                     m_asPage[MAX_PAGE];

//<GUI_Extra_Elements !Start!>
gslc_tsElem                     m_asPage1Elem[MAX_ELEM_PG_MAIN_RAM];
gslc_tsElemRef                  m_asPage1ElemRef[MAX_ELEM_PG_MAIN];
gslc_tsXProgress                m_sXBarGauge1;

#define MAX_STR                 100

//<GUI_Extra_Elements !End!>

// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Element References for direct access
//<Extern_References !Start!>
extern gslc_tsElemRef* m_pElemCount;
extern gslc_tsElemRef* m_pElemProgress1;
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
// Create page elements
// ------------------------------------------------
void InitGUIslice_gen()
{
  gslc_tsElemRef* pElemRef = NULL;

  if (!gslc_Init(&m_gui,&m_drv,m_asPage,MAX_PAGE,m_asFont,MAX_FONT)) { return; }

  // ------------------------------------------------
  // Load Fonts
  // ------------------------------------------------
//<Load_Fonts !Start!>
    if (!gslc_FontSet(&m_gui,E_ARIAL_10,GSLC_FONTREF_PTR,&Arial_10,1)) { return; }
    gslc_FontSetMode(&m_gui, E_ARIAL_10, GSLC_FONTREF_MODE_1);	
    if (!gslc_FontSet(&m_gui,E_ARIAL_12,GSLC_FONTREF_PTR,&Arial_12,1)) { return; }
    gslc_FontSetMode(&m_gui, E_ARIAL_12, GSLC_FONTREF_MODE_1);	
    if (!gslc_FontSet(&m_gui,E_ARIAL_13,GSLC_FONTREF_PTR,&Arial_13,1)) { return; }
    gslc_FontSetMode(&m_gui, E_ARIAL_13, GSLC_FONTREF_MODE_1);	
//<Load_Fonts !End!>

//<InitGUI !Start!>
  gslc_PageAdd(&m_gui,E_PG_MAIN,m_asPage1Elem,MAX_ELEM_PG_MAIN_RAM,m_asPage1ElemRef,MAX_ELEM_PG_MAIN);

  // NOTE: The current page defaults to the first page added. Here we explicitly
  //       ensure that the main page is the correct page no matter the add order.
  gslc_SetPageCur(&m_gui,E_PG_MAIN);
  
  // Set Background to a flat color
  gslc_SetBkgndColor(&m_gui,GSLC_COL_BLACK);

  // -----------------------------------
  // PAGE: E_PG_MAIN
  
  
  // Create E_ELEM_TEXT2 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT2,E_PG_MAIN,(gslc_tsRect){110,30,84,15},
    (char*)"GUI TEST",0,E_ARIAL_13);
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);
  
  // Create E_ELEM_TEXT3 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT3,E_PG_MAIN,(gslc_tsRect){20,70,46,12},
    (char*)"Count: ",0,E_ARIAL_10);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_RED_DK1);
  
  // Create E_COUNTER runtime modifiable text
  static char m_sDisplayText4[13] = "0";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_COUNTER,E_PG_MAIN,(gslc_tsRect){80,70,96,11},
    (char*)m_sDisplayText4,13,E_ARIAL_10);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK1);
  m_pElemCount = pElemRef;
  
  // create E_ELEM_BTN_INC button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_INC,E_PG_MAIN,
    (gslc_tsRect){60,120,80,30},(char*)"INC",0,E_ARIAL_12,&CbBtnCommon);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create E_ELEM_BTN_DEC button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_DEC,E_PG_MAIN,
    (gslc_tsRect){160,100,80,30},(char*)"DEC",0,E_ARIAL_12,&CbBtnCommon);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);

  // Create progress bar E_ELEM_PROGRESS1 
  pElemRef = gslc_ElemXProgressCreate(&m_gui,E_ELEM_PROGRESS1,E_PG_MAIN,&m_sXBarGauge1,
    (gslc_tsRect){200,170,50,12},0,100,0,GSLC_COL_GREEN,false);
  m_pElemProgress1 = pElemRef;
//<InitGUI !End!>

//<Startup !Start!>
  gslc_GuiRotate(&m_gui, 3);
//<Startup !End!>

}

// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Save some element references for direct access
//<Save_References !Start!>
gslc_tsElemRef* m_pElemCount      = NULL;
gslc_tsElemRef* m_pElemProgress1  = NULL;
//<Save_References !End!>

// Define debug message function
static int16_t DebugOut(char ch) { if (ch == (char)'\n') Serial.println(""); else Serial.write(ch); return 0; }

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
// Common Button callback
bool CbBtnCommon(void* pvGui,void *pvElemRef,gslc_teTouch eTouch,int16_t nX,int16_t nY)
{
  // Typecast the parameters to match the GUI and element types
  gslc_tsGui*     pGui     = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem*    pElem    = gslc_GetElemFromRef(pGui,pElemRef);

  if ( eTouch == GSLC_TOUCH_UP_IN ) {
    // From the element's ID we can determine which button was pressed.
    switch (pElem->nId) {
//<Button Enums !Start!>
      case E_ELEM_BTN_INC:
        break;
      case E_ELEM_BTN_DEC:
        break;

//<Button Enums !End!>
      default:
        break;
    }
  }
  return true;
}

#endif // end _GUISLICE_GEN_H
