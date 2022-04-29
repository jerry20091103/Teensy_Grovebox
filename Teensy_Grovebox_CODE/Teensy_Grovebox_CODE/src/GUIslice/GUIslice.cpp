//<App !Start!>
// FILE: [GUIslice.ino]
// Created by GUIslice Builder version: [0.17.b11]
//
// GUIslice Builder Generated File
//
// For the latest guides, updates and support view:
// https://github.com/ImpulseAdventure/GUIslice
//
//<App !End!>

// ------------------------------------------------
// Headers to include
// ------------------------------------------------
#include "Pages/Pages.h"
#include "GUIslice_GSLC.h"


// ------------------------------------------------
// Program Globals
// ------------------------------------------------
// Create element storage
// ------------------------------------------------
gslc_tsGui                      m_gui;
gslc_tsDriver                   m_drv;
gslc_tsFont                     m_asFont[MAX_FONT];
gslc_tsPage                     m_asPage[MAX_PAGE];

//<GUI_Extra_Elements !Start!>
gslc_tsElem                     m_asBasePage1Elem[MAX_ELEM_PG_BASE_RAM];
gslc_tsElemRef                  m_asBasePage1ElemRef[MAX_ELEM_PG_BASE];
gslc_tsElem                     m_asPage1Elem[MAX_ELEM_PG_MIDI_RAM];
gslc_tsElemRef                  m_asPage1ElemRef[MAX_ELEM_PG_MIDI];
gslc_tsXRingGauge               m_sXRingGauge1;
gslc_tsXRingGauge               m_sXRingGauge2;
gslc_tsXRingGauge               m_sXRingGauge3;
gslc_tsXRingGauge               m_sXRingGauge4;


// Save some element references for direct access
//<Save_References !Start!>
gslc_tsElemRef* m_pElemMidiRingBlue= NULL;
gslc_tsElemRef* m_pElemMidiRingGreen= NULL;
gslc_tsElemRef* m_pElemMidiRingRed= NULL;
gslc_tsElemRef* m_pElemMidiRingYellow= NULL;
gslc_tsElemRef* m_pElemMidiTxtChannel= NULL;
gslc_tsElemRef* m_pElemMidiTxtOctave= NULL;
gslc_tsElemRef* m_pElemTxtBatt    = NULL;
gslc_tsElemRef* m_pElemTxtTitle   = NULL;
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
    PageManager.PageArr[PageManager.getCurPage()]->onTouch(pElem->nId);
  }
  return true;
}
//<Checkbox Callback !Start!>
//<Checkbox Callback !End!>
//<Keypad Callback !Start!>
//<Keypad Callback !End!>
//<Spinner Callback !Start!>
//<Spinner Callback !End!>
//<Listbox Callback !Start!>
//<Listbox Callback !End!>
//<Draw Callback !Start!>
//<Draw Callback !End!>
//<Slider Callback !Start!>
//<Slider Callback !End!>
//<Tick Callback !Start!>

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
    if (!gslc_FontSet(&m_gui,E_ARIAL_12,GSLC_FONTREF_PTR,&Arial_12,1)) { return; }
    gslc_FontSetMode(&m_gui, E_ARIAL_12, GSLC_FONTREF_MODE_1);	
    if (!gslc_FontSet(&m_gui,E_ARIAL_12_BOLD,GSLC_FONTREF_PTR,&Arial_12_Bold,1)) { return; }
    gslc_FontSetMode(&m_gui, E_ARIAL_12_BOLD, GSLC_FONTREF_MODE_1);	
    if (!gslc_FontSet(&m_gui,E_ARIAL_13,GSLC_FONTREF_PTR,&Arial_13,1)) { return; }
    gslc_FontSetMode(&m_gui, E_ARIAL_13, GSLC_FONTREF_MODE_1);	
    if (!gslc_FontSet(&m_gui,E_ARIAL_14,GSLC_FONTREF_PTR,&Arial_14,1)) { return; }
    gslc_FontSetMode(&m_gui, E_ARIAL_14, GSLC_FONTREF_MODE_1);	
    if (!gslc_FontSet(&m_gui,E_AWESOMEF000_10,GSLC_FONTREF_PTR,&AwesomeF000_10,1)) { return; }
    gslc_FontSetMode(&m_gui, E_AWESOMEF000_10, GSLC_FONTREF_MODE_1);	
    if (!gslc_FontSet(&m_gui,E_AWESOMEF200_12,GSLC_FONTREF_PTR,&AwesomeF200_12,1)) { return; }
    gslc_FontSetMode(&m_gui, E_AWESOMEF200_12, GSLC_FONTREF_MODE_1);	
//<Load_Fonts !End!>

//<InitGUI !Start!>
  gslc_PageAdd(&m_gui,E_PG_BASE,m_asBasePage1Elem,MAX_ELEM_PG_BASE_RAM,m_asBasePage1ElemRef,MAX_ELEM_PG_BASE);
  gslc_PageAdd(&m_gui,E_PG_MIDI,m_asPage1Elem,MAX_ELEM_PG_MIDI_RAM,m_asPage1ElemRef,MAX_ELEM_PG_MIDI);

  // Now mark E_PG_BASE as a "base" page which means that it's elements
  // are always visible. This is useful for common page elements.
  gslc_SetPageBase(&m_gui, E_PG_BASE);


  // NOTE: The current page defaults to the first page added. Here we explicitly
  //       ensure that the main page is the correct page no matter the add order.
  gslc_SetPageCur(&m_gui,E_PG_MIDI);
  
  // Set Background to a flat color
  gslc_SetBkgndColor(&m_gui,GSLC_COL_BLACK);

  // -----------------------------------
  // PAGE: E_PG_BASE
  
  
  // Create E_ELEM_TEXT_TITLE runtime modifiable text
  static char m_sDisplayText5[16] = "MIDI";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT_TITLE,E_PG_BASE,(gslc_tsRect){35,10,150,13},
    (char*)m_sDisplayText5,16,E_ARIAL_12_BOLD);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  m_pElemTxtTitle = pElemRef;
  
  // Create E_ELEM_TEXT_BATT runtime modifiable text
  static char m_sDisplayText6[3] = "@";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT_BATT,E_PG_BASE,(gslc_tsRect){280,10,20,11},
    (char*)m_sDisplayText6,3,E_AWESOMEF200_12);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GRAY_LT3);
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);
  m_pElemTxtBatt = pElemRef;
  
  // create E_ELEM_BTN5 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN5,E_PG_BASE,
    (gslc_tsRect){0,0,30,30},(char*)"<",0,E_ARIAL_14,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_BLACK,GSLC_COL_GRAY);

  // Create E_DRAW_LINE1 line 
  pElemRef = gslc_ElemCreateLine(&m_gui,E_DRAW_LINE1,E_PG_BASE,0,30,320,30);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_GRAY_LT2,GSLC_COL_GRAY_LT2);

  // -----------------------------------
  // PAGE: E_PG_MIDI
  
  
  // create E_ELEM_MIDI_OCTAVE_INC button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_MIDI_OCTAVE_INC,E_PG_MIDI,
    (gslc_tsRect){195,125,35,35},(char*)"+",0,E_ARIAL_12_BOLD,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_GRAY);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create E_ELEM_MIDI_OCTAVE_DEC button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_MIDI_OCTAVE_DEC,E_PG_MIDI,
    (gslc_tsRect){255,125,35,35},(char*)"-",0,E_ARIAL_12_BOLD,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_GRAY);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create E_ELEM_MIDI_CHANNEL_INC button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_MIDI_CHANNEL_INC,E_PG_MIDI,
    (gslc_tsRect){195,170,35,35},(char*)"+",0,E_ARIAL_12_BOLD,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_GRAY);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create E_ELEM_MIDI_CHANNEL_DEC button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_MIDI_CHANNEL_DEC,E_PG_MIDI,
    (gslc_tsRect){255,170,35,35},(char*)"-",0,E_ARIAL_12_BOLD,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_GRAY);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // Create E_ELEM_MIDI_TEXT_1 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_MIDI_TEXT_1,E_PG_MIDI,(gslc_tsRect){30,135,67,15},
    (char*)"Octave: ",0,E_ARIAL_13);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_MIDI_TEXT16 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_MIDI_TEXT16,E_PG_MIDI,(gslc_tsRect){30,180,72,14},
    (char*)"Channel:",0,E_ARIAL_13);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_MIDI_TEXT_OCTAVE runtime modifiable text
  static char m_sDisplayText11[4] = "0";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_MIDI_TEXT_OCTAVE,E_PG_MIDI,(gslc_tsRect){125,135,30,14},
    (char*)m_sDisplayText11,4,E_ARIAL_13);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  m_pElemMidiTxtOctave = pElemRef;
  
  // Create E_ELEM_MIDI_TEXT_CHANNEL runtime modifiable text
  static char m_sDisplayText17[4] = "0";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_MIDI_TEXT_CHANNEL,E_PG_MIDI,(gslc_tsRect){125,180,30,14},
    (char*)m_sDisplayText17,4,E_ARIAL_13);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  m_pElemMidiTxtChannel = pElemRef;

  // Create ring gauge E_ELEM_MIDI_RING_RED 
  static char m_sRingText1[4] = "";
  pElemRef = gslc_ElemXRingGaugeCreate(&m_gui,E_ELEM_MIDI_RING_RED,E_PG_MIDI,&m_sXRingGauge1,
          (gslc_tsRect){9,56,60,60},
          (char*)m_sRingText1,4,E_ARIAL_12_BOLD);
  gslc_ElemXRingGaugeSetValRange(&m_gui, pElemRef, 0, 127);
  gslc_ElemXRingGaugeSetVal(&m_gui, pElemRef, 0); // Set initial value
  gslc_ElemXRingGaugeSetThickness(&m_gui,pElemRef, 6);
  gslc_ElemXRingGaugeSetAngleRange(&m_gui,pElemRef, 225, 270, true);
  gslc_ElemXRingGaugeSetColorActiveFlat(&m_gui,pElemRef, GSLC_COL_RED);
  gslc_ElemXRingGaugeSetColorInactive(&m_gui,pElemRef, ((gslc_tsColor){79,0,0}));
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  m_pElemMidiRingRed = pElemRef;

  // Create ring gauge E_ELEM_MIDI_RING_YELLOW 
  static char m_sRingText2[4] = "";
  pElemRef = gslc_ElemXRingGaugeCreate(&m_gui,E_ELEM_MIDI_RING_YELLOW,E_PG_MIDI,&m_sXRingGauge2,
          (gslc_tsRect){91,56,60,60},
          (char*)m_sRingText2,4,E_ARIAL_12_BOLD);
  gslc_ElemXRingGaugeSetValRange(&m_gui, pElemRef, 0, 127);
  gslc_ElemXRingGaugeSetVal(&m_gui, pElemRef, 0); // Set initial value
  gslc_ElemXRingGaugeSetThickness(&m_gui,pElemRef, 6);
  gslc_ElemXRingGaugeSetAngleRange(&m_gui,pElemRef, 225, 270, true);
  gslc_ElemXRingGaugeSetColorActiveFlat(&m_gui,pElemRef, ((gslc_tsColor){250,230,0}));
  gslc_ElemXRingGaugeSetColorInactive(&m_gui,pElemRef, ((gslc_tsColor){75,68,0}));
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  m_pElemMidiRingYellow = pElemRef;

  // Create ring gauge E_ELEM_MIDI_RING_BLUE 
  static char m_sRingText3[4] = "";
  pElemRef = gslc_ElemXRingGaugeCreate(&m_gui,E_ELEM_MIDI_RING_BLUE,E_PG_MIDI,&m_sXRingGauge3,
          (gslc_tsRect){171,55,60,60},
          (char*)m_sRingText3,4,E_ARIAL_12_BOLD);
  gslc_ElemXRingGaugeSetValRange(&m_gui, pElemRef, 0, 127);
  gslc_ElemXRingGaugeSetVal(&m_gui, pElemRef, 0); // Set initial value
  gslc_ElemXRingGaugeSetThickness(&m_gui,pElemRef, 6);
  gslc_ElemXRingGaugeSetAngleRange(&m_gui,pElemRef, 225, 270, true);
  gslc_ElemXRingGaugeSetColorActiveFlat(&m_gui,pElemRef, ((gslc_tsColor){20,20,255}));
  gslc_ElemXRingGaugeSetColorInactive(&m_gui,pElemRef, ((gslc_tsColor){0,0,58}));
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  m_pElemMidiRingBlue = pElemRef;

  // Create ring gauge E_ELEM_MIDI_RING_GREEN 
  static char m_sRingText4[4] = "";
  pElemRef = gslc_ElemXRingGaugeCreate(&m_gui,E_ELEM_MIDI_RING_GREEN,E_PG_MIDI,&m_sXRingGauge4,
          (gslc_tsRect){251,56,60,60},
          (char*)m_sRingText4,4,E_ARIAL_12_BOLD);
  gslc_ElemXRingGaugeSetValRange(&m_gui, pElemRef, 0, 127);
  gslc_ElemXRingGaugeSetVal(&m_gui, pElemRef, 0); // Set initial value
  gslc_ElemXRingGaugeSetThickness(&m_gui,pElemRef, 6);
  gslc_ElemXRingGaugeSetAngleRange(&m_gui,pElemRef, 225, 270, true);
  gslc_ElemXRingGaugeSetColorActiveFlat(&m_gui,pElemRef, GSLC_COL_GREEN_DK2);
  gslc_ElemXRingGaugeSetColorInactive(&m_gui,pElemRef, ((gslc_tsColor){0,61,0}));
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  m_pElemMidiRingGreen = pElemRef;
  
  // Create E_ELEM_MIDI_TEXT12 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_MIDI_TEXT12,E_PG_MIDI,(gslc_tsRect){24,36,24,13},
    (char*)"CC",0,E_ARIAL_12);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_MIDI_TEXT13 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_MIDI_TEXT13,E_PG_MIDI,(gslc_tsRect){106,36,26,14},
    (char*)"CC",0,E_ARIAL_13);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_MIDI_TEXT14 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_MIDI_TEXT14,E_PG_MIDI,(gslc_tsRect){186,36,26,14},
    (char*)"CC",0,E_ARIAL_13);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_MIDI_TEXT15 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_MIDI_TEXT15,E_PG_MIDI,(gslc_tsRect){266,36,26,14},
    (char*)"CC",0,E_ARIAL_13);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
   
  // Create E_ELEM_MIDI_RED_BOX1 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_MIDI_RED_BOX1,E_PG_MIDI,(gslc_tsRect){5,215,30,20});
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_RED_DK1,GSLC_COL_BLACK,GSLC_COL_BLACK);
   
  // Create E_ELEM_MIDI_RED_BOX2 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_MIDI_RED_BOX2,E_PG_MIDI,(gslc_tsRect){45,215,30,20});
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_RED_DK1,GSLC_COL_BLACK,GSLC_COL_BLACK);
   
  // Create E_ELEM_MIDI_YELLOW_BOX3 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_MIDI_YELLOW_BOX3,E_PG_MIDI,(gslc_tsRect){85,215,30,20});
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetCol(&m_gui,pElemRef,((gslc_tsColor){250,230,0}),GSLC_COL_BLACK,GSLC_COL_BLACK);
   
  // Create E_ELEM_MIDI_YELLOW_BOX4 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_MIDI_YELLOW_BOX4,E_PG_MIDI,(gslc_tsRect){125,215,30,20});
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetCol(&m_gui,pElemRef,((gslc_tsColor){250,230,0}),GSLC_COL_BLACK,GSLC_COL_BLACK);
   
  // Create E_ELEM_MIDI_BLUE_BOX5 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_MIDI_BLUE_BOX5,E_PG_MIDI,(gslc_tsRect){205,215,30,20});
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetCol(&m_gui,pElemRef,((gslc_tsColor){30,30,255}),GSLC_COL_BLACK,GSLC_COL_BLACK);
   
  // Create E_ELEM_MIDI_BLUE_BOX6 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_MIDI_BLUE_BOX6,E_PG_MIDI,(gslc_tsRect){165,215,30,20});
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetCol(&m_gui,pElemRef,((gslc_tsColor){30,30,255}),GSLC_COL_BLACK,GSLC_COL_BLACK);
   
  // Create E_ELEM_MIDI_GREEN_BOX7 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_MIDI_GREEN_BOX7,E_PG_MIDI,(gslc_tsRect){285,215,30,20});
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GREEN_DK2,GSLC_COL_BLACK,GSLC_COL_BLACK);
   
  // Create E_ELEM_MIDI_GREEN_BOX8 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_MIDI_GREEN_BOX8,E_PG_MIDI,(gslc_tsRect){245,215,30,20});
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GREEN_DK2,GSLC_COL_BLACK,GSLC_COL_BLACK);
  
  // Create E_ELEM_MIDI_TEXT_PLAY_F04B text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_MIDI_TEXT_PLAY_F04B,E_PG_MIDI,(gslc_tsRect){15,218,11,13},
    (char*)"K",0,E_AWESOMEF000_10);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_MIDI_TEXT_STOP_F04D text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_MIDI_TEXT_STOP_F04D,E_PG_MIDI,(gslc_tsRect){53,217,12,14},
    (char*)"M",0,E_AWESOMEF000_10);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_MIDI_TEXT_FF_F050 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_MIDI_TEXT_FF_F050,E_PG_MIDI,(gslc_tsRect){133,217,14,14},
    (char*)"P",0,E_AWESOMEF000_10);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_MIDI_TEXT_FB_F049 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_MIDI_TEXT_FB_F049,E_PG_MIDI,(gslc_tsRect){92,217,14,14},
    (char*)"I",0,E_AWESOMEF000_10);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_MIDI_TEXT23 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_MIDI_TEXT23,E_PG_MIDI,(gslc_tsRect){171,219,18,13},
    (char*)"20",0,E_ARIAL_12);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_MIDI_TEXT24 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_MIDI_TEXT24,E_PG_MIDI,(gslc_tsRect){211,219,18,13},
    (char*)"21",0,E_ARIAL_12);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_MIDI_TEXT25 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_MIDI_TEXT25,E_PG_MIDI,(gslc_tsRect){251,219,18,13},
    (char*)"22",0,E_ARIAL_12);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_MIDI_TEXT26 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_MIDI_TEXT26,E_PG_MIDI,(gslc_tsRect){291,219,18,13},
    (char*)"23",0,E_ARIAL_12);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
//<InitGUI !End!>

//<Startup !Start!>
  gslc_GuiRotate(&m_gui, 3);
//<Startup !End!>

}

