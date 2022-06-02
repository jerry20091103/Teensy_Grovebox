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
gslc_tsElem                     m_asPopup1Elem[MAX_ELEM_PG_POPUP_POWER_RAM];
gslc_tsElemRef                  m_asPopup1ElemRef[MAX_ELEM_PG_POPUP_POWER];
gslc_tsElem                     m_asPage2Elem[MAX_ELEM_PG_AUDIOOUT_RAM];
gslc_tsElemRef                  m_asPage2ElemRef[MAX_ELEM_PG_AUDIOOUT];
gslc_tsElem                     m_asPopup2Elem[MAX_ELEM_PG_POPUP_OUT_MIXER_RAM];
gslc_tsElemRef                  m_asPopup2ElemRef[MAX_ELEM_PG_POPUP_OUT_MIXER];
gslc_tsElem                     m_asPage3Elem[MAX_ELEM_PG_AUDIOIN_RAM];
gslc_tsElemRef                  m_asPage3ElemRef[MAX_ELEM_PG_AUDIOIN];
gslc_tsElem                     m_asPage4Elem[MAX_ELEM_PG_HOME_RAM];
gslc_tsElemRef                  m_asPage4ElemRef[MAX_ELEM_PG_HOME];
gslc_tsElem                     m_asPage5Elem[MAX_ELEM_PG_WAVE_RAM];
gslc_tsElemRef                  m_asPage5ElemRef[MAX_ELEM_PG_WAVE];
gslc_tsXRingGauge               m_sXRingGauge1;
gslc_tsXRingGauge               m_sXRingGauge2;
gslc_tsXRingGauge               m_sXRingGauge3;
gslc_tsXRingGauge               m_sXRingGauge4;
gslc_tsXProgress                m_sXBarGauge7;
gslc_tsXProgress                m_sXBarGauge1;
gslc_tsXProgress                m_sXBarGauge2;
gslc_tsXSeekbar                 m_sXSeekbar1;
gslc_tsXProgress                m_sXBarGauge9;
gslc_tsXProgress                m_sXBarGauge10;
gslc_tsXProgress                m_sXBarGauge11;
gslc_tsXSeekbar                 m_sXSeekbar2;
gslc_tsXRingGauge               m_sXRingGauge5;
gslc_tsXProgress                m_sXBarGauge13;
gslc_tsXProgress                m_sXBarGauge14;
gslc_tsXSeekbar                 m_sXSeekbar3;
gslc_tsXSeekbar                 m_sXSeekbar4;
gslc_tsXProgress                m_sXBarGauge15;
gslc_tsXProgress                m_sXBarGauge16;
gslc_tsXSeekbar                 m_sXSeekbar8;
gslc_tsXSeekbar                 m_sXSeekbar5;
gslc_tsXProgress                m_sXBarGauge22;
gslc_tsXProgress                m_sXBarGauge21;
gslc_tsXSeekbar                 m_sXSeekbar11;
gslc_tsXSeekbar                 m_sXSeekbar6;
gslc_tsXSeekbar                 m_sXSeekbar7;
gslc_tsXProgress                m_sXBarGauge17;
gslc_tsXProgress                m_sXBarGauge18;
gslc_tsXRingGauge               m_sXRingGauge6;
gslc_tsXSeekbar                 m_sXSeekbar9;
gslc_tsXProgress                m_sXBarGauge19;
gslc_tsXProgress                m_sXBarGauge20;
gslc_tsXSeekbar                 m_sXSeekbar10;
gslc_tsXProgress                m_sXBarGauge23;
gslc_tsXRingGauge               m_sXRingGauge10;


// Save some element references for direct access
//<Save_References !Start!>
gslc_tsElemRef* m_pElemAudioinGainRing= NULL;
gslc_tsElemRef* m_pElemAudioinLineInBtn= NULL;
gslc_tsElemRef* m_pElemAudioinLmLBar= NULL;
gslc_tsElemRef* m_pElemAudioinLmRBar= NULL;
gslc_tsElemRef* m_pElemAudioinLmVol= NULL;
gslc_tsElemRef* m_pElemAudioinLmVolTxt= NULL;
gslc_tsElemRef* m_pElemAudioinMicBtn= NULL;
gslc_tsElemRef* m_pElemAudioinPflBtn= NULL;
gslc_tsElemRef* m_pElemAudioinUsbLBar= NULL;
gslc_tsElemRef* m_pElemAudioinUsbRBar= NULL;
gslc_tsElemRef* m_pElemAudioinUsbVol= NULL;
gslc_tsElemRef* m_pElemAudioinUsbVolTxt= NULL;
gslc_tsElemRef* m_pElemAudiooutHpVolRing= NULL;
gslc_tsElemRef* m_pElemAudiooutLineLBar= NULL;
gslc_tsElemRef* m_pElemAudiooutLinePeakBar= NULL;
gslc_tsElemRef* m_pElemAudiooutLineRBar= NULL;
gslc_tsElemRef* m_pElemAudiooutLineVol= NULL;
gslc_tsElemRef* m_pElemAudiooutLineVolTxt= NULL;
gslc_tsElemRef* m_pElemAudiooutPrefaderBtn= NULL;
gslc_tsElemRef* m_pElemAudiooutUsbLBar= NULL;
gslc_tsElemRef* m_pElemAudiooutUsbPeakBar= NULL;
gslc_tsElemRef* m_pElemAudiooutUsbRBar= NULL;
gslc_tsElemRef* m_pElemAudiooutUsbVol= NULL;
gslc_tsElemRef* m_pElemAudiooutUsbVolTxt= NULL;
gslc_tsElemRef* m_pElemMidiModBtn = NULL;
gslc_tsElemRef* m_pElemMidiPitchbendBtn= NULL;
gslc_tsElemRef* m_pElemMidiRingBlue= NULL;
gslc_tsElemRef* m_pElemMidiRingGreen= NULL;
gslc_tsElemRef* m_pElemMidiRingRed= NULL;
gslc_tsElemRef* m_pElemMidiRingYellow= NULL;
gslc_tsElemRef* m_pElemMidiTxtChannel= NULL;
gslc_tsElemRef* m_pElemMidiTxtOctave= NULL;
gslc_tsElemRef* m_pElemOutMixerInsLBar= NULL;
gslc_tsElemRef* m_pElemOutMixerInsPan= NULL;
gslc_tsElemRef* m_pElemOutMixerInsRBar= NULL;
gslc_tsElemRef* m_pElemOutMixerInsVol= NULL;
gslc_tsElemRef* m_pElemOutMixerInsVolTxt= NULL;
gslc_tsElemRef* m_pElemOutMixerLmLBar= NULL;
gslc_tsElemRef* m_pElemOutMixerLmPan= NULL;
gslc_tsElemRef* m_pElemOutMixerLmRBar= NULL;
gslc_tsElemRef* m_pElemOutMixerLmVol= NULL;
gslc_tsElemRef* m_pElemOutMixerLmVolTxt= NULL;
gslc_tsElemRef* m_pElemOutMixerPanBtn= NULL;
gslc_tsElemRef* m_pElemOutMixerPflBtn= NULL;
gslc_tsElemRef* m_pElemOutMixerRecPan= NULL;
gslc_tsElemRef* m_pElemOutMixerTitleTxt= NULL;
gslc_tsElemRef* m_pElemOutMixerUsbLBar= NULL;
gslc_tsElemRef* m_pElemOutMixerUsbPan= NULL;
gslc_tsElemRef* m_pElemOutMixerUsbRBar= NULL;
gslc_tsElemRef* m_pElemOutMixerUsbVol= NULL;
gslc_tsElemRef* m_pElemOutMixerUsbVolTxt= NULL;
gslc_tsElemRef* m_pElemTxtBatt    = NULL;
gslc_tsElemRef* m_pElemTxtTitle   = NULL;
gslc_tsElemRef* m_pElemWaveOctaveDecBtn= NULL;
gslc_tsElemRef* m_pElemWaveOctaveIncBtn= NULL;
gslc_tsElemRef* m_pElemWaveOctaveTxt= NULL;
gslc_tsElemRef* m_pElemWaveSoundBtn= NULL;
gslc_tsElemRef* m_pElemWaveVelocityBtn= NULL;
gslc_tsElemRef* m_pElemWaveVelocityBtn39= NULL;
gslc_tsElemRef* m_pElemWaveVelocityBtn39_40= NULL;
gslc_tsElemRef* m_pElemWaveVelocityBtn39_40_42= NULL;
gslc_tsElemRef* m_pElemWaveVelocityBtn39_40_42_43= NULL;
gslc_tsElemRef* m_pElemWaveVolBar = NULL;
gslc_tsElemRef* m_pElemWaveVolRing= NULL;
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

// Callback function for when a slider's position has been updated
bool CbSlidePos(void* pvGui,void* pvElemRef,int16_t nPos)
{
  gslc_tsGui*     pGui     = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem*    pElem    = gslc_GetElemFromRef(pGui,pElemRef);
  int16_t         nVal;

  // From the element's ID we can determine which slider was updated.
    PageManager.PageArr[PageManager.getCurPage()]->onTouch(pElem->nId);

  return true;
}
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
    if (!gslc_FontSet(&m_gui,E_ARIAL_10,GSLC_FONTREF_PTR,&Arial_10,1)) { return; }
    gslc_FontSetMode(&m_gui, E_ARIAL_10, GSLC_FONTREF_MODE_1);	
    if (!gslc_FontSet(&m_gui,E_ARIAL_10_BOLD,GSLC_FONTREF_PTR,&Arial_10_Bold,1)) { return; }
    gslc_FontSetMode(&m_gui, E_ARIAL_10_BOLD, GSLC_FONTREF_MODE_1);	
    if (!gslc_FontSet(&m_gui,E_ARIAL_12,GSLC_FONTREF_PTR,&Arial_12,1)) { return; }
    gslc_FontSetMode(&m_gui, E_ARIAL_12, GSLC_FONTREF_MODE_1);	
    if (!gslc_FontSet(&m_gui,E_ARIAL_12_BOLD,GSLC_FONTREF_PTR,&Arial_12_Bold,1)) { return; }
    gslc_FontSetMode(&m_gui, E_ARIAL_12_BOLD, GSLC_FONTREF_MODE_1);	
    if (!gslc_FontSet(&m_gui,E_ARIAL_13,GSLC_FONTREF_PTR,&Arial_13,1)) { return; }
    gslc_FontSetMode(&m_gui, E_ARIAL_13, GSLC_FONTREF_MODE_1);	
    if (!gslc_FontSet(&m_gui,E_ARIAL_14,GSLC_FONTREF_PTR,&Arial_14,1)) { return; }
    gslc_FontSetMode(&m_gui, E_ARIAL_14, GSLC_FONTREF_MODE_1);	
    if (!gslc_FontSet(&m_gui,E_ARIAL_14_BOLD,GSLC_FONTREF_PTR,&Arial_14_Bold,1)) { return; }
    gslc_FontSetMode(&m_gui, E_ARIAL_14_BOLD, GSLC_FONTREF_MODE_1);	
    if (!gslc_FontSet(&m_gui,E_ARIAL_8,GSLC_FONTREF_PTR,&Arial_8,1)) { return; }
    gslc_FontSetMode(&m_gui, E_ARIAL_8, GSLC_FONTREF_MODE_1);	
    if (!gslc_FontSet(&m_gui,E_AWESOMEF000_10,GSLC_FONTREF_PTR,&AwesomeF000_10,1)) { return; }
    gslc_FontSetMode(&m_gui, E_AWESOMEF000_10, GSLC_FONTREF_MODE_1);	
    if (!gslc_FontSet(&m_gui,E_AWESOMEF000_12,GSLC_FONTREF_PTR,&AwesomeF000_12,1)) { return; }
    gslc_FontSetMode(&m_gui, E_AWESOMEF000_12, GSLC_FONTREF_MODE_1);	
    if (!gslc_FontSet(&m_gui,E_AWESOMEF000_14,GSLC_FONTREF_PTR,&AwesomeF000_14,1)) { return; }
    gslc_FontSetMode(&m_gui, E_AWESOMEF000_14, GSLC_FONTREF_MODE_1);	
    if (!gslc_FontSet(&m_gui,E_AWESOMEF000_16,GSLC_FONTREF_PTR,&AwesomeF000_16,1)) { return; }
    gslc_FontSetMode(&m_gui, E_AWESOMEF000_16, GSLC_FONTREF_MODE_1);	
    if (!gslc_FontSet(&m_gui,E_AWESOMEF000_9,GSLC_FONTREF_PTR,&AwesomeF000_9,1)) { return; }
    gslc_FontSetMode(&m_gui, E_AWESOMEF000_9, GSLC_FONTREF_MODE_1);	
    if (!gslc_FontSet(&m_gui,E_AWESOMEF080_18,GSLC_FONTREF_PTR,&AwesomeF080_18,1)) { return; }
    gslc_FontSetMode(&m_gui, E_AWESOMEF080_18, GSLC_FONTREF_MODE_1);	
    if (!gslc_FontSet(&m_gui,E_AWESOMEF100_18,GSLC_FONTREF_PTR,&AwesomeF100_18,1)) { return; }
    gslc_FontSetMode(&m_gui, E_AWESOMEF100_18, GSLC_FONTREF_MODE_1);	
    if (!gslc_FontSet(&m_gui,E_AWESOMEF200_14,GSLC_FONTREF_PTR,&AwesomeF200_14,1)) { return; }
    gslc_FontSetMode(&m_gui, E_AWESOMEF200_14, GSLC_FONTREF_MODE_1);	
    if (!gslc_FontSet(&m_gui,E_BUILTIN5X8,GSLC_FONTREF_PTR,NULL,1)) { return; }
//<Load_Fonts !End!>

//<InitGUI !Start!>
  gslc_PageAdd(&m_gui,E_PG_BASE,m_asBasePage1Elem,MAX_ELEM_PG_BASE_RAM,m_asBasePage1ElemRef,MAX_ELEM_PG_BASE);
  gslc_PageAdd(&m_gui,E_PG_MIDI,m_asPage1Elem,MAX_ELEM_PG_MIDI_RAM,m_asPage1ElemRef,MAX_ELEM_PG_MIDI);
  gslc_PageAdd(&m_gui,E_PG_POPUP_POWER,m_asPopup1Elem,MAX_ELEM_PG_POPUP_POWER_RAM,m_asPopup1ElemRef,MAX_ELEM_PG_POPUP_POWER);
  gslc_PageAdd(&m_gui,E_PG_AUDIOOUT,m_asPage2Elem,MAX_ELEM_PG_AUDIOOUT_RAM,m_asPage2ElemRef,MAX_ELEM_PG_AUDIOOUT);
  gslc_PageAdd(&m_gui,E_PG_POPUP_OUT_MIXER,m_asPopup2Elem,MAX_ELEM_PG_POPUP_OUT_MIXER_RAM,m_asPopup2ElemRef,MAX_ELEM_PG_POPUP_OUT_MIXER);
  gslc_PageAdd(&m_gui,E_PG_AUDIOIN,m_asPage3Elem,MAX_ELEM_PG_AUDIOIN_RAM,m_asPage3ElemRef,MAX_ELEM_PG_AUDIOIN);
  gslc_PageAdd(&m_gui,E_PG_HOME,m_asPage4Elem,MAX_ELEM_PG_HOME_RAM,m_asPage4ElemRef,MAX_ELEM_PG_HOME);
  gslc_PageAdd(&m_gui,E_PG_WAVE,m_asPage5Elem,MAX_ELEM_PG_WAVE_RAM,m_asPage5ElemRef,MAX_ELEM_PG_WAVE);

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
  static char m_sDisplayText5[21] = "AUDIO";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT_TITLE,E_PG_BASE,(gslc_tsRect){35,10,200,13},
    (char*)m_sDisplayText5,21,E_ARIAL_12_BOLD);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  m_pElemTxtTitle = pElemRef;
  
  // Create E_ELEM_TEXT_BATT runtime modifiable text
  static char m_sDisplayText6[3] = "@";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT_BATT,E_PG_BASE,(gslc_tsRect){285,4,26,20},
    (char*)m_sDisplayText6,3,E_AWESOMEF200_14);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GRAY_LT3);
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);
  m_pElemTxtBatt = pElemRef;
  
  // create E_ELEM_BASE_BACK_BTN button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BASE_BACK_BTN,E_PG_BASE,
    (gslc_tsRect){0,0,30,29},(char*)"<",0,E_ARIAL_14,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_BLACK,GSLC_COL_GRAY);

  // Create E_DRAW_LINE1 line 
  pElemRef = gslc_ElemCreateLine(&m_gui,E_DRAW_LINE1,E_PG_BASE,0,30,320,30);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_GRAY_LT2,GSLC_COL_GRAY_LT2);

  // -----------------------------------
  // PAGE: E_PG_MIDI
  
  
  // create E_ELEM_MIDI_OCTAVE_INC button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_MIDI_OCTAVE_INC,E_PG_MIDI,
    (gslc_tsRect){275,130,35,30},(char*)"g",0,E_AWESOMEF000_12,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_GRAY);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create E_ELEM_MIDI_OCTAVE_DEC button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_MIDI_OCTAVE_DEC,E_PG_MIDI,
    (gslc_tsRect){230,130,35,30},(char*)"h",0,E_AWESOMEF000_9,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_GRAY);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create E_ELEM_MIDI_CHANNEL_INC button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_MIDI_CHANNEL_INC,E_PG_MIDI,
    (gslc_tsRect){275,170,35,30},(char*)"g",0,E_AWESOMEF000_12,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_GRAY);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create E_ELEM_MIDI_CHANNEL_DEC button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_MIDI_CHANNEL_DEC,E_PG_MIDI,
    (gslc_tsRect){230,170,35,30},(char*)"h",0,E_AWESOMEF000_9,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_GRAY);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // Create E_ELEM_MIDI_TEXT_1 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_MIDI_TEXT_1,E_PG_MIDI,(gslc_tsRect){125,140,60,14},
    (char*)"Octave: ",0,E_ARIAL_12);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_MIDI_TEXT16 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_MIDI_TEXT16,E_PG_MIDI,(gslc_tsRect){125,180,65,13},
    (char*)"Channel:",0,E_ARIAL_12);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_MIDI_TEXT_OCTAVE runtime modifiable text
  static char m_sDisplayText11[3] = "0";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_MIDI_TEXT_OCTAVE,E_PG_MIDI,(gslc_tsRect){200,140,20,14},
    (char*)m_sDisplayText11,3,E_ARIAL_13);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  m_pElemMidiTxtOctave = pElemRef;
  
  // Create E_ELEM_MIDI_TEXT_CHANNEL runtime modifiable text
  static char m_sDisplayText17[3] = "0";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_MIDI_TEXT_CHANNEL,E_PG_MIDI,(gslc_tsRect){200,180,20,14},
    (char*)m_sDisplayText17,3,E_ARIAL_13);
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
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_MIDI_TEXT12,E_PG_MIDI,(gslc_tsRect){27,40,20,11},
    (char*)"CC",0,E_ARIAL_10);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_MIDI_TEXT13 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_MIDI_TEXT13,E_PG_MIDI,(gslc_tsRect){110,40,20,11},
    (char*)"CC",0,E_ARIAL_10);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_MIDI_TEXT14 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_MIDI_TEXT14,E_PG_MIDI,(gslc_tsRect){190,40,20,11},
    (char*)"CC",0,E_ARIAL_10);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_MIDI_TEXT15 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_MIDI_TEXT15,E_PG_MIDI,(gslc_tsRect){270,40,20,11},
    (char*)"CC",0,E_ARIAL_10);
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
  
  // create E_ELEM_MIDI_PITCHBEND_BTN button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_MIDI_PITCHBEND_BTN,E_PG_MIDI,
    (gslc_tsRect){10,130,80,30},(char*)"Pitch Bend",0,E_ARIAL_10,&CbBtnCommon);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_WHITE,GSLC_COL_GRAY);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemMidiPitchbendBtn = pElemRef;
  
  // create E_ELEM_MIDI_MOD_BTN button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_MIDI_MOD_BTN,E_PG_MIDI,
    (gslc_tsRect){10,170,80,30},(char*)"MOD",0,E_ARIAL_10,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_GRAY);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemMidiModBtn = pElemRef;

  // -----------------------------------
  // PAGE: E_PG_POPUP_POWER
  
   
  // Create E_ELEM_BOX10 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX10,E_PG_POPUP_POWER,(gslc_tsRect){25,25,270,190});
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_BLACK);
  
  // Create E_ELEM_TEXT27 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT27,E_PG_POPUP_POWER,(gslc_tsRect){55,35,102,16},
    (char*)"Power Off ?",0,E_ARIAL_14);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT28 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT28,E_PG_POPUP_POWER,(gslc_tsRect){70,80,169,14},
    (char*)"Changes will not be saved.",0,E_ARIAL_10);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);

  // Create E_DRAW_LINE2 line 
  pElemRef = gslc_ElemCreateLine(&m_gui,E_DRAW_LINE2,E_PG_POPUP_POWER,30,60,290,60);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_WHITE,GSLC_COL_WHITE);
  
  // create E_ELEM_POWER_BTN_YES button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_POWER_BTN_YES,E_PG_POPUP_POWER,
    (gslc_tsRect){45,160,85,35},(char*)"Yes",0,E_ARIAL_14,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_RED_DK1,GSLC_COL_RED_DK1,GSLC_COL_RED_DK4);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create E_ELEM_POWER_BTN_CALCEL button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_POWER_BTN_CALCEL,E_PG_POPUP_POWER,
    (gslc_tsRect){190,160,85,35},(char*)"Cancel",0,E_ARIAL_14,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_RED_DK1,GSLC_COL_BLACK,GSLC_COL_RED_DK4);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // Create E_ELEM_TEXT96 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT96,E_PG_POPUP_POWER,(gslc_tsRect){30,30,19,22},
    (char*)"j",0,E_AWESOMEF000_16);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_RED);

  // -----------------------------------
  // PAGE: E_PG_AUDIOOUT
  

  // Create progress bar E_ELEM_AUDIOOUT_USB_PEAK_BAR 
  pElemRef = gslc_ElemXProgressCreate(&m_gui,E_ELEM_AUDIOOUT_USB_PEAK_BAR,E_PG_AUDIOOUT,&m_sXBarGauge7,
    (gslc_tsRect){175,100,12,130},0,100,0,((gslc_tsColor){255,100,0}),true);
  m_pElemAudiooutUsbPeakBar = pElemRef;

  // Create progress bar E_ELEM_AUDIOOUT_USB_R_BAR 
  pElemRef = gslc_ElemXProgressCreate(&m_gui,E_ELEM_AUDIOOUT_USB_R_BAR,E_PG_AUDIOOUT,&m_sXBarGauge1,
    (gslc_tsRect){185,100,12,130},0,100,0,GSLC_COL_GREEN_LT3,true);
  m_pElemAudiooutUsbRBar = pElemRef;

  // Create progress bar E_ELEM_AUDIOOUT_USB_L_BAR 
  pElemRef = gslc_ElemXProgressCreate(&m_gui,E_ELEM_AUDIOOUT_USB_L_BAR,E_PG_AUDIOOUT,&m_sXBarGauge2,
    (gslc_tsRect){165,100,12,130},0,100,0,GSLC_COL_GREEN_LT3,true);
  m_pElemAudiooutUsbLBar = pElemRef;

  // Create seekbar E_ELEM_AUDIOOUT_USB_VOL 
  pElemRef = gslc_ElemXSeekbarCreate(&m_gui,E_ELEM_AUDIOOUT_USB_VOL,E_PG_AUDIOOUT,&m_sXSeekbar1,
    (gslc_tsRect){110,70,20,170},0,63,30,
    2,4,6,GSLC_COL_GRAY,((gslc_tsColor){250,230,0}),((gslc_tsColor){250,230,0}),true);
  gslc_ElemXSeekbarSetPosFunc(&m_gui,pElemRef,&CbSlidePos);
  gslc_ElemXSeekbarSetStyle(&m_gui,pElemRef,true,GSLC_COL_WHITE,false,GSLC_COL_GRAY,
    0,100,GSLC_COL_GRAY);
  m_pElemAudiooutUsbVol = pElemRef;
   
  // Create E_ELEM_AUDIOOUT_USB_PEAK_R_BOX box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_AUDIOOUT_USB_PEAK_R_BOX,E_PG_AUDIOOUT,(gslc_tsRect){185,85,12,10});
   
  // Create E_ELEM_AUDIOOUT_USB_PEAK_L_BOX box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_AUDIOOUT_USB_PEAK_L_BOX,E_PG_AUDIOOUT,(gslc_tsRect){165,85,12,10});
  
  // create E_ELEM_AUDIOOUT_ANALOG_BTN button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_AUDIOOUT_ANALOG_BTN,E_PG_AUDIOOUT,
    (gslc_tsRect){15,35,80,25},(char*)"Analog",0,E_ARIAL_12,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_GRAY);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // Create E_ELEM_AUDIOOUT_USB_VOL_TEXT runtime modifiable text
  static char m_sDisplayText44[5] = "-20";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_AUDIOOUT_USB_VOL_TEXT,E_PG_AUDIOOUT,(gslc_tsRect){165,65,40,13},
    (char*)m_sDisplayText44,5,E_ARIAL_12_BOLD);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);
  m_pElemAudiooutUsbVolTxt = pElemRef;

  // Create progress bar E_ELEM_AUDIOOUT_LINE_PEAK_BAR 
  pElemRef = gslc_ElemXProgressCreate(&m_gui,E_ELEM_AUDIOOUT_LINE_PEAK_BAR,E_PG_AUDIOOUT,&m_sXBarGauge9,
    (gslc_tsRect){65,100,12,130},0,100,0,((gslc_tsColor){255,100,0}),true);
  m_pElemAudiooutLinePeakBar = pElemRef;

  // Create progress bar E_ELEM_AUDIOOUT_LINE_R_BAR 
  pElemRef = gslc_ElemXProgressCreate(&m_gui,E_ELEM_AUDIOOUT_LINE_R_BAR,E_PG_AUDIOOUT,&m_sXBarGauge10,
    (gslc_tsRect){75,100,12,130},0,100,0,GSLC_COL_GREEN_LT3,true);
  m_pElemAudiooutLineRBar = pElemRef;

  // Create progress bar E_ELEM_AUDIOOUT_LINE_L_BAR 
  pElemRef = gslc_ElemXProgressCreate(&m_gui,E_ELEM_AUDIOOUT_LINE_L_BAR,E_PG_AUDIOOUT,&m_sXBarGauge11,
    (gslc_tsRect){55,100,12,130},0,100,0,GSLC_COL_GREEN_LT3,true);
  m_pElemAudiooutLineLBar = pElemRef;

  // Create seekbar E_ELEM_AUDIOOUT_LINE_VOL 
  pElemRef = gslc_ElemXSeekbarCreate(&m_gui,E_ELEM_AUDIOOUT_LINE_VOL,E_PG_AUDIOOUT,&m_sXSeekbar2,
    (gslc_tsRect){5,70,20,170},0,63,22,
    2,4,6,GSLC_COL_GRAY,GSLC_COL_RED_DK1,GSLC_COL_RED,true);
  gslc_ElemXSeekbarSetPosFunc(&m_gui,pElemRef,&CbSlidePos);
  gslc_ElemXSeekbarSetStyle(&m_gui,pElemRef,true,GSLC_COL_WHITE,false,GSLC_COL_GRAY,
    0,100,GSLC_COL_GRAY);
  m_pElemAudiooutLineVol = pElemRef;
   
  // Create E_ELEM_AUDIOOUT_LINE_PEAK_R_BOX box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_AUDIOOUT_LINE_PEAK_R_BOX,E_PG_AUDIOOUT,(gslc_tsRect){75,85,12,10});
   
  // Create E_ELEM_AUDIOOUT_LINE_PEAK_L_BOX box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_AUDIOOUT_LINE_PEAK_L_BOX,E_PG_AUDIOOUT,(gslc_tsRect){55,85,12,10});
  
  // create E_ELEM_AUDIOOUT_USB_BTN button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_AUDIOOUT_USB_BTN,E_PG_AUDIOOUT,
    (gslc_tsRect){125,35,80,25},(char*)"USB",0,E_ARIAL_12,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_GRAY);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // Create E_ELEM_AUDIOOUT_LINE_VOL_TEXT runtime modifiable text
  static char m_sDisplayText45[5] = "-20";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_AUDIOOUT_LINE_VOL_TEXT,E_PG_AUDIOOUT,(gslc_tsRect){55,65,40,13},
    (char*)m_sDisplayText45,5,E_ARIAL_12_BOLD);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);
  m_pElemAudiooutLineVolTxt = pElemRef;

  // Create ring gauge E_ELEM_AUDIOOUT_HP_VOL_RING 
  static char m_sRingText5[4] = "";
  pElemRef = gslc_ElemXRingGaugeCreate(&m_gui,E_ELEM_AUDIOOUT_HP_VOL_RING,E_PG_AUDIOOUT,&m_sXRingGauge5,
          (gslc_tsRect){237,60,60,55},
          (char*)m_sRingText5,4,E_ARIAL_12_BOLD);
  gslc_ElemXRingGaugeSetValRange(&m_gui, pElemRef, 0, 100);
  gslc_ElemXRingGaugeSetVal(&m_gui, pElemRef, 30); // Set initial value
  gslc_ElemXRingGaugeSetThickness(&m_gui,pElemRef, 6);
  gslc_ElemXRingGaugeSetAngleRange(&m_gui,pElemRef, 225, 270, true);
  gslc_ElemXRingGaugeSetColorActiveFlat(&m_gui,pElemRef, ((gslc_tsColor){20,20,255}));
  gslc_ElemXRingGaugeSetColorInactive(&m_gui,pElemRef, ((gslc_tsColor){0,0,58}));
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  m_pElemAudiooutHpVolRing = pElemRef;
  
  // create E_ELEM_AUDIOOUT_PREFADER_BTN button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_AUDIOOUT_PREFADER_BTN,E_PG_AUDIOOUT,
    (gslc_tsRect){227,190,85,30},(char*)"PFL",0,E_ARIAL_12,&CbBtnCommon);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_WHITE,GSLC_COL_GRAY);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemAudiooutPrefaderBtn = pElemRef;
  
  // create E_ELEM_AUDIOOUT_PP_BTN button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_AUDIOOUT_PP_BTN,E_PG_AUDIOOUT,
    (gslc_tsRect){227,140,85,30},(char*)"Post Processing",0,E_ARIAL_8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_GRAY);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // Create E_ELEM_TEXT29 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT29,E_PG_AUDIOOUT,(gslc_tsRect){245,35,18,18},
    (char*)"%",0,E_AWESOMEF000_14);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT30 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT30,E_PG_AUDIOOUT,(gslc_tsRect){275,33,10,20},
    (char*)"&",0,E_AWESOMEF000_16);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT31 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT31,E_PG_AUDIOOUT,(gslc_tsRect){265,40,5,15},
    (char*)"/",0,E_ARIAL_14);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT32 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT32,E_PG_AUDIOOUT,(gslc_tsRect){40,95,7,10},
    (char*)"0",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT33 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT33,E_PG_AUDIOOUT,(gslc_tsRect){150,95,7,10},
    (char*)"0",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT34 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT34,E_PG_AUDIOOUT,(gslc_tsRect){140,120,19,10},
    (char*)"-10",0,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_RIGHT);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);
  
  // Create E_ELEM_TEXT36 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT36,E_PG_AUDIOOUT,(gslc_tsRect){140,70,19,10},
    (char*)"+10",0,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_RIGHT);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);
  
  // Create E_ELEM_TEXT37 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT37,E_PG_AUDIOOUT,(gslc_tsRect){30,70,19,10},
    (char*)"+10",0,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_RIGHT);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);
  
  // Create E_ELEM_TEXT38 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT38,E_PG_AUDIOOUT,(gslc_tsRect){140,170,19,10},
    (char*)"-30",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT40 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT40,E_PG_AUDIOOUT,(gslc_tsRect){140,225,19,10},
    (char*)"-52",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT41 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT41,E_PG_AUDIOOUT,(gslc_tsRect){30,225,19,10},
    (char*)"-52",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT42 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT42,E_PG_AUDIOOUT,(gslc_tsRect){30,170,19,10},
    (char*)"-30",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT43 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT43,E_PG_AUDIOOUT,(gslc_tsRect){30,120,19,10},
    (char*)"-10",0,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_RIGHT);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);
  
  // Create E_ELEM_TEXT69 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT69,E_PG_AUDIOOUT,(gslc_tsRect){265,105,10,9},
    (char*)"%",0,E_ARIAL_8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_RIGHT);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);

  // Create E_DRAW_LINE4 line 
  pElemRef = gslc_ElemCreateLine(&m_gui,E_DRAW_LINE4,E_PG_AUDIOOUT,220,35,220,235);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_GRAY,GSLC_COL_GRAY);
  
  // Create E_ELEM_TEXT75 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT75,E_PG_AUDIOOUT,(gslc_tsRect){200,225,13,10},
    (char*)"dB",0,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_RIGHT);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);
  
  // Create E_ELEM_TEXT76 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT76,E_PG_AUDIOOUT,(gslc_tsRect){90,225,13,10},
    (char*)"dB",0,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_RIGHT);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);

  // -----------------------------------
  // PAGE: E_PG_POPUP_OUT_MIXER
  
   
  // Create E_ELEM_BOX24 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX24,E_PG_POPUP_OUT_MIXER,(gslc_tsRect){5,10,310,222});
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_BLACK);
  
  // create E_ELEM_OUT_MIXER_BACK_BTN button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_OUT_MIXER_BACK_BTN,E_PG_POPUP_OUT_MIXER,
    (gslc_tsRect){7,12,26,26},(char*)"<",0,E_ARIAL_14,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_BLACK,GSLC_COL_GRAY);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);

  // Create E_DRAW_LINE3 line 
  pElemRef = gslc_ElemCreateLine(&m_gui,E_DRAW_LINE3,E_PG_POPUP_OUT_MIXER,10,40,310,40);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_WHITE,GSLC_COL_WHITE);
  
  // Create E_ELEM_OUT_MIXER_TITLE_TEXT runtime modifiable text
  static char m_sDisplayText47[17] = "Analog out mixer";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_OUT_MIXER_TITLE_TEXT,E_PG_POPUP_OUT_MIXER,(gslc_tsRect){35,20,160,13},
    (char*)m_sDisplayText47,17,E_ARIAL_12_BOLD);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  m_pElemOutMixerTitleTxt = pElemRef;

  // Create progress bar E_ELEM_OUT_MIXER_LM_R_BAR 
  pElemRef = gslc_ElemXProgressCreate(&m_gui,E_ELEM_OUT_MIXER_LM_R_BAR,E_PG_POPUP_OUT_MIXER,&m_sXBarGauge13,
    (gslc_tsRect){65,120,12,100},0,100,0,GSLC_COL_GREEN_LT3,true);
  m_pElemOutMixerLmRBar = pElemRef;

  // Create progress bar E_ELEM_OUT_MIXER_LM_L_BAR 
  pElemRef = gslc_ElemXProgressCreate(&m_gui,E_ELEM_OUT_MIXER_LM_L_BAR,E_PG_POPUP_OUT_MIXER,&m_sXBarGauge14,
    (gslc_tsRect){50,120,12,100},0,100,0,GSLC_COL_GREEN_LT3,true);
  m_pElemOutMixerLmLBar = pElemRef;

  // Create seekbar E_ELEM_OUT_MIXER_LM_VOL 
  pElemRef = gslc_ElemXSeekbarCreate(&m_gui,E_ELEM_OUT_MIXER_LM_VOL,E_PG_POPUP_OUT_MIXER,&m_sXSeekbar3,
    (gslc_tsRect){10,95,15,133},0,61,20,
    2,4,6,GSLC_COL_GRAY,GSLC_COL_RED_DK1,GSLC_COL_RED,true);
  gslc_ElemXSeekbarSetPosFunc(&m_gui,pElemRef,&CbSlidePos);
  gslc_ElemXSeekbarSetStyle(&m_gui,pElemRef,true,GSLC_COL_WHITE,false,GSLC_COL_GRAY,
    0,100,GSLC_COL_GRAY);
  m_pElemOutMixerLmVol = pElemRef;
   
  // Create E_ELEM_OUT_MIXER_LM_PEAK_R_BOX box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_OUT_MIXER_LM_PEAK_R_BOX,E_PG_POPUP_OUT_MIXER,(gslc_tsRect){65,105,12,10});
   
  // Create E_ELEM_OUT_MIXER_LM_PEAK_L_BOX box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_OUT_MIXER_LM_PEAK_L_BOX,E_PG_POPUP_OUT_MIXER,(gslc_tsRect){50,105,12,10});

  // Create seekbar E_ELEM_OUT_MIXER_LM_PAN 
  pElemRef = gslc_ElemXSeekbarCreate(&m_gui,E_ELEM_OUT_MIXER_LM_PAN,E_PG_POPUP_OUT_MIXER,&m_sXSeekbar4,
    (gslc_tsRect){15,65,65,20},0,60,30,
    2,2,6,GSLC_COL_GRAY,GSLC_COL_GRAY,GSLC_COL_WHITE,false);
  gslc_ElemXSeekbarSetPosFunc(&m_gui,pElemRef,&CbSlidePos);
  gslc_ElemXSeekbarSetStyle(&m_gui,pElemRef,true,GSLC_COL_RED,false,GSLC_COL_GRAY,
    0,100,GSLC_COL_GRAY);
  m_pElemOutMixerLmPan = pElemRef;
  
  // Create E_ELEM_OUT_MIXER_LM_VOL_TEXT runtime modifiable text
  static char m_sDisplayText56[5] = "-20";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_OUT_MIXER_LM_VOL_TEXT,E_PG_POPUP_OUT_MIXER,(gslc_tsRect){45,85,36,11},
    (char*)m_sDisplayText56,5,E_ARIAL_10_BOLD);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  m_pElemOutMixerLmVolTxt = pElemRef;

  // Create progress bar E_ELEM_OUT_MIXER_USB_R_BAR 
  pElemRef = gslc_ElemXProgressCreate(&m_gui,E_ELEM_OUT_MIXER_USB_R_BAR,E_PG_POPUP_OUT_MIXER,&m_sXBarGauge15,
    (gslc_tsRect){140,120,12,100},0,100,0,GSLC_COL_GREEN_LT3,true);
  m_pElemOutMixerUsbRBar = pElemRef;

  // Create progress bar E_ELEM_OUT_MIXER_USB_L_BAR 
  pElemRef = gslc_ElemXProgressCreate(&m_gui,E_ELEM_OUT_MIXER_USB_L_BAR,E_PG_POPUP_OUT_MIXER,&m_sXBarGauge16,
    (gslc_tsRect){125,120,12,100},0,100,0,GSLC_COL_GREEN_LT3,true);
  m_pElemOutMixerUsbLBar = pElemRef;

  // Create seekbar E_ELEM_OUT_MIXER_USB_VOL 
  pElemRef = gslc_ElemXSeekbarCreate(&m_gui,E_ELEM_OUT_MIXER_USB_VOL,E_PG_POPUP_OUT_MIXER,&m_sXSeekbar8,
    (gslc_tsRect){85,95,15,133},0,61,20,
    2,4,6,GSLC_COL_GRAY,((gslc_tsColor){250,230,0}),((gslc_tsColor){250,230,0}),true);
  gslc_ElemXSeekbarSetPosFunc(&m_gui,pElemRef,&CbSlidePos);
  gslc_ElemXSeekbarSetStyle(&m_gui,pElemRef,true,GSLC_COL_WHITE,false,GSLC_COL_GRAY,
    0,100,GSLC_COL_GRAY);
  m_pElemOutMixerUsbVol = pElemRef;
   
  // Create E_ELEM_OUT_MIXER_USB_PEAK_R_BOX box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_OUT_MIXER_USB_PEAK_R_BOX,E_PG_POPUP_OUT_MIXER,(gslc_tsRect){140,105,12,10});
   
  // Create E_ELEM_OUT_MIXER_USB_PEAK_L_BOX box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_OUT_MIXER_USB_PEAK_L_BOX,E_PG_POPUP_OUT_MIXER,(gslc_tsRect){125,105,12,10});

  // Create seekbar E_ELEM_OUT_MIXER_USB_PAN 
  pElemRef = gslc_ElemXSeekbarCreate(&m_gui,E_ELEM_OUT_MIXER_USB_PAN,E_PG_POPUP_OUT_MIXER,&m_sXSeekbar5,
    (gslc_tsRect){90,65,65,20},0,60,30,
    2,2,6,GSLC_COL_GRAY,GSLC_COL_GRAY,GSLC_COL_WHITE,false);
  gslc_ElemXSeekbarSetPosFunc(&m_gui,pElemRef,&CbSlidePos);
  gslc_ElemXSeekbarSetStyle(&m_gui,pElemRef,true,((gslc_tsColor){250,230,0}),false,GSLC_COL_GRAY,
    0,100,GSLC_COL_GRAY);
  m_pElemOutMixerUsbPan = pElemRef;
  
  // Create E_ELEM_OUT_MIXER_USB_VOL_TEXT runtime modifiable text
  static char m_sDisplayText58[5] = "-20";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_OUT_MIXER_USB_VOL_TEXT,E_PG_POPUP_OUT_MIXER,(gslc_tsRect){120,85,36,11},
    (char*)m_sDisplayText58,5,E_ARIAL_10_BOLD);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  m_pElemOutMixerUsbVolTxt = pElemRef;

  // Create progress bar E_ELEM_OUT_MIXER_INS_R_BAR 
  pElemRef = gslc_ElemXProgressCreate(&m_gui,E_ELEM_OUT_MIXER_INS_R_BAR,E_PG_POPUP_OUT_MIXER,&m_sXBarGauge22,
    (gslc_tsRect){215,120,12,100},0,100,0,GSLC_COL_GREEN_LT3,true);
  m_pElemOutMixerInsRBar = pElemRef;

  // Create progress bar E_ELEM_OUT_MIXER_INS_L_BAR 
  pElemRef = gslc_ElemXProgressCreate(&m_gui,E_ELEM_OUT_MIXER_INS_L_BAR,E_PG_POPUP_OUT_MIXER,&m_sXBarGauge21,
    (gslc_tsRect){200,120,12,100},0,100,0,GSLC_COL_GREEN_LT3,true);
  m_pElemOutMixerInsLBar = pElemRef;

  // Create seekbar E_ELEM_OUT_MIXER_INS_VOL 
  pElemRef = gslc_ElemXSeekbarCreate(&m_gui,E_ELEM_OUT_MIXER_INS_VOL,E_PG_POPUP_OUT_MIXER,&m_sXSeekbar11,
    (gslc_tsRect){160,95,15,133},0,61,20,
    2,4,6,GSLC_COL_GRAY,((gslc_tsColor){20,20,255}),((gslc_tsColor){20,20,255}),true);
  gslc_ElemXSeekbarSetPosFunc(&m_gui,pElemRef,&CbSlidePos);
  gslc_ElemXSeekbarSetStyle(&m_gui,pElemRef,true,GSLC_COL_WHITE,false,GSLC_COL_GRAY,
    0,100,GSLC_COL_GRAY);
  m_pElemOutMixerInsVol = pElemRef;
   
  // Create E_ELEM_OUT_MIXER_INS_PEAK_R_BOX box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_OUT_MIXER_INS_PEAK_R_BOX,E_PG_POPUP_OUT_MIXER,(gslc_tsRect){215,105,12,10});
   
  // Create E_ELEM_OUT_MIXER_INS_PEAK_L_BOX box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_OUT_MIXER_INS_PEAK_L_BOX,E_PG_POPUP_OUT_MIXER,(gslc_tsRect){200,105,12,10});

  // Create seekbar E_ELEM_OUT_MIXER_INS_PAN 
  pElemRef = gslc_ElemXSeekbarCreate(&m_gui,E_ELEM_OUT_MIXER_INS_PAN,E_PG_POPUP_OUT_MIXER,&m_sXSeekbar6,
    (gslc_tsRect){165,65,65,20},0,60,30,
    2,2,6,GSLC_COL_GRAY,GSLC_COL_GRAY,GSLC_COL_WHITE,false);
  gslc_ElemXSeekbarSetPosFunc(&m_gui,pElemRef,&CbSlidePos);
  gslc_ElemXSeekbarSetStyle(&m_gui,pElemRef,true,((gslc_tsColor){20,20,255}),false,GSLC_COL_GRAY,
    0,100,GSLC_COL_GRAY);
  m_pElemOutMixerInsPan = pElemRef;
  
  // Create E_ELEM_OUT_MIXER_INS_VOL_TEXT runtime modifiable text
  static char m_sDisplayText118[5] = "-20";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_OUT_MIXER_INS_VOL_TEXT,E_PG_POPUP_OUT_MIXER,(gslc_tsRect){195,85,36,11},
    (char*)m_sDisplayText118,5,E_ARIAL_10_BOLD);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  m_pElemOutMixerInsVolTxt = pElemRef;

  // Create seekbar E_ELEM_OUT_MIXER_REC_PAN 
  pElemRef = gslc_ElemXSeekbarCreate(&m_gui,E_ELEM_OUT_MIXER_REC_PAN,E_PG_POPUP_OUT_MIXER,&m_sXSeekbar7,
    (gslc_tsRect){240,65,65,20},0,60,30,
    2,2,6,GSLC_COL_GRAY,GSLC_COL_GRAY,GSLC_COL_WHITE,false);
  gslc_ElemXSeekbarSetPosFunc(&m_gui,pElemRef,&CbSlidePos);
  gslc_ElemXSeekbarSetStyle(&m_gui,pElemRef,true,GSLC_COL_GREEN_DK2,false,GSLC_COL_GRAY,
    0,100,GSLC_COL_GRAY);
  m_pElemOutMixerRecPan = pElemRef;
  
  // create E_ELEM_OUT_MIXER_PFL_BTN button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_OUT_MIXER_PFL_BTN,E_PG_POPUP_OUT_MIXER,
    (gslc_tsRect){250,15,60,20},(char*)"PFL",0,E_ARIAL_12,&CbBtnCommon);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_WHITE,GSLC_COL_GRAY);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemOutMixerPflBtn = pElemRef;
  
  // create E_ELEM_OUT_MIXER_PAN_BTN button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_OUT_MIXER_PAN_BTN,E_PG_POPUP_OUT_MIXER,
    (gslc_tsRect){185,15,60,20},(char*)"PAN",0,E_ARIAL_12,&CbBtnCommon);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_RED_LT2,GSLC_COL_RED_LT2,GSLC_COL_GRAY);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemOutMixerPanBtn = pElemRef;
  
  // Create E_ELEM_TEXT48 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT48,E_PG_POPUP_OUT_MIXER,(gslc_tsRect){35,115,7,10},
    (char*)"0",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT49 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT49,E_PG_POPUP_OUT_MIXER,(gslc_tsRect){25,95,19,10},
    (char*)"+10",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT50 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT50,E_PG_POPUP_OUT_MIXER,(gslc_tsRect){25,135,19,10},
    (char*)"-10",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT52 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT52,E_PG_POPUP_OUT_MIXER,(gslc_tsRect){25,175,19,10},
    (char*)"-30",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT54 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT54,E_PG_POPUP_OUT_MIXER,(gslc_tsRect){25,215,19,10},
    (char*)"-50",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT55 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT55,E_PG_POPUP_OUT_MIXER,(gslc_tsRect){20,50,52,11},
    (char*)"Line/Mic",0,E_ARIAL_10);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT57 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT57,E_PG_POPUP_OUT_MIXER,(gslc_tsRect){107,50,27,11},
    (char*)"USB",0,E_ARIAL_10);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT59 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT59,E_PG_POPUP_OUT_MIXER,(gslc_tsRect){100,95,19,10},
    (char*)"+10",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT60 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT60,E_PG_POPUP_OUT_MIXER,(gslc_tsRect){110,115,7,10},
    (char*)"0",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT61 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT61,E_PG_POPUP_OUT_MIXER,(gslc_tsRect){100,135,19,10},
    (char*)"-10",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT62 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT62,E_PG_POPUP_OUT_MIXER,(gslc_tsRect){100,175,19,10},
    (char*)"-30",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT63 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT63,E_PG_POPUP_OUT_MIXER,(gslc_tsRect){100,215,19,10},
    (char*)"-50",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT64 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT64,E_PG_POPUP_OUT_MIXER,(gslc_tsRect){160,50,73,11},
    (char*)"Instruments",0,E_ARIAL_10);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT65 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT65,E_PG_POPUP_OUT_MIXER,(gslc_tsRect){245,50,54,11},
    (char*)"Recoder",0,E_ARIAL_10);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT67 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT67,E_PG_POPUP_OUT_MIXER,(gslc_tsRect){255,150,28,11},
    (char*)"TBD",0,E_ARIAL_10);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT113 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT113,E_PG_POPUP_OUT_MIXER,(gslc_tsRect){175,95,19,10},
    (char*)"+10",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT114 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT114,E_PG_POPUP_OUT_MIXER,(gslc_tsRect){185,115,7,10},
    (char*)"0",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT115 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT115,E_PG_POPUP_OUT_MIXER,(gslc_tsRect){175,135,19,10},
    (char*)"-10",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT116 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT116,E_PG_POPUP_OUT_MIXER,(gslc_tsRect){175,175,19,10},
    (char*)"-30",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT117 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT117,E_PG_POPUP_OUT_MIXER,(gslc_tsRect){175,215,19,10},
    (char*)"-50",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);

  // -----------------------------------
  // PAGE: E_PG_AUDIOIN
  

  // Create progress bar E_ELEM_AUDIOIN_LM_L_BAR 
  pElemRef = gslc_ElemXProgressCreate(&m_gui,E_ELEM_AUDIOIN_LM_L_BAR,E_PG_AUDIOIN,&m_sXBarGauge17,
    (gslc_tsRect){150,105,12,125},0,100,0,GSLC_COL_GREEN_LT3,true);
  m_pElemAudioinLmLBar = pElemRef;

  // Create progress bar E_ELEM_AUDIOIN_LM_R_BAR 
  pElemRef = gslc_ElemXProgressCreate(&m_gui,E_ELEM_AUDIOIN_LM_R_BAR,E_PG_AUDIOIN,&m_sXBarGauge18,
    (gslc_tsRect){170,105,12,125},0,100,0,GSLC_COL_GREEN_LT3,true);
  m_pElemAudioinLmRBar = pElemRef;
   
  // Create E_ELEM_AUDIOIN_LM_PEAK_L_BOX box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_AUDIOIN_LM_PEAK_L_BOX,E_PG_AUDIOIN,(gslc_tsRect){150,90,12,10});
   
  // Create E_ELEM_AUDIOIN_LM_PEAK_R_BOX box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_AUDIOIN_LM_PEAK_R_BOX,E_PG_AUDIOIN,(gslc_tsRect){170,90,12,10});
  
  // Create E_ELEM_AUDIOIN_LM_VOL_TEXT runtime modifiable text
  static char m_sDisplayText87[5] = "-20";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_AUDIOIN_LM_VOL_TEXT,E_PG_AUDIOIN,(gslc_tsRect){150,60,48,15},
    (char*)m_sDisplayText87,5,E_ARIAL_14_BOLD);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);
  m_pElemAudioinLmVolTxt = pElemRef;
  
  // create E_ELEM_AUDIOIN_LINE_IN_BTN button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_AUDIOIN_LINE_IN_BTN,E_PG_AUDIOIN,
    (gslc_tsRect){15,55,75,25},(char*)"LINE IN",0,E_ARIAL_12,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_GRAY);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemAudioinLineInBtn = pElemRef;
  
  // create E_ELEM_AUDIOIN_MIC_BTN button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_AUDIOIN_MIC_BTN,E_PG_AUDIOIN,
    (gslc_tsRect){15,85,75,25},(char*)"MIC",0,E_ARIAL_12,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_GRAY);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemAudioinMicBtn = pElemRef;

  // Create ring gauge E_ELEM_AUDIOIN_GAIN_RING 
  static char m_sRingText6[4] = "";
  pElemRef = gslc_ElemXRingGaugeCreate(&m_gui,E_ELEM_AUDIOIN_GAIN_RING,E_PG_AUDIOIN,&m_sXRingGauge6,
          (gslc_tsRect){20,140,60,55},
          (char*)m_sRingText6,4,E_ARIAL_12_BOLD);
  gslc_ElemXRingGaugeSetValRange(&m_gui, pElemRef, 0, 63);
  gslc_ElemXRingGaugeSetVal(&m_gui, pElemRef, 20); // Set initial value
  gslc_ElemXRingGaugeSetThickness(&m_gui,pElemRef, 6);
  gslc_ElemXRingGaugeSetAngleRange(&m_gui,pElemRef, 225, 270, true);
  gslc_ElemXRingGaugeSetColorActiveFlat(&m_gui,pElemRef, GSLC_COL_RED);
  gslc_ElemXRingGaugeSetColorInactive(&m_gui,pElemRef, ((gslc_tsColor){79,0,0}));
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  m_pElemAudioinGainRing = pElemRef;
  
  // create E_ELEM_AUDIOIN_PFL_BTN button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_AUDIOIN_PFL_BTN,E_PG_AUDIOIN,
    (gslc_tsRect){15,205,75,25},(char*)"PFL",0,E_ARIAL_12,&CbBtnCommon);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_WHITE,GSLC_COL_GRAY);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemAudioinPflBtn = pElemRef;

  // Create seekbar E_ELEM_AUDIOIN_LM_VOL 
  pElemRef = gslc_ElemXSeekbarCreate(&m_gui,E_ELEM_AUDIOIN_LM_VOL,E_PG_AUDIOIN,&m_sXSeekbar9,
    (gslc_tsRect){105,75,20,163},0,61,20,
    2,4,6,GSLC_COL_GRAY,((gslc_tsColor){250,230,0}),((gslc_tsColor){250,230,0}),true);
  gslc_ElemXSeekbarSetPosFunc(&m_gui,pElemRef,&CbSlidePos);
  gslc_ElemXSeekbarSetStyle(&m_gui,pElemRef,true,GSLC_COL_WHITE,false,GSLC_COL_GRAY,
    0,100,GSLC_COL_GRAY);
  m_pElemAudioinLmVol = pElemRef;

  // Create progress bar E_ELEM_AUDIOIN_USB_L_BAR 
  pElemRef = gslc_ElemXProgressCreate(&m_gui,E_ELEM_AUDIOIN_USB_L_BAR,E_PG_AUDIOIN,&m_sXBarGauge19,
    (gslc_tsRect){265,105,12,125},0,100,0,GSLC_COL_GREEN_LT3,true);
  m_pElemAudioinUsbLBar = pElemRef;

  // Create progress bar E_ELEM_AUDIOIN_USB_R_BAR 
  pElemRef = gslc_ElemXProgressCreate(&m_gui,E_ELEM_AUDIOIN_USB_R_BAR,E_PG_AUDIOIN,&m_sXBarGauge20,
    (gslc_tsRect){285,105,12,125},0,100,0,GSLC_COL_GREEN_LT3,true);
  m_pElemAudioinUsbRBar = pElemRef;
   
  // Create E_ELEM_AUDIOIN_USB_PEAK_L_BOX box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_AUDIOIN_USB_PEAK_L_BOX,E_PG_AUDIOIN,(gslc_tsRect){265,90,12,10});
   
  // Create E_ELEM_AUDIOIN_USB_PEAK_R_BOX box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_AUDIOIN_USB_PEAK_R_BOX,E_PG_AUDIOIN,(gslc_tsRect){285,90,12,10});

  // Create seekbar E_ELEM_AUDIOIN_USB_VOL 
  pElemRef = gslc_ElemXSeekbarCreate(&m_gui,E_ELEM_AUDIOIN_USB_VOL,E_PG_AUDIOIN,&m_sXSeekbar10,
    (gslc_tsRect){220,75,20,163},0,61,20,
    2,4,6,GSLC_COL_GRAY,((gslc_tsColor){20,20,255}),((gslc_tsColor){20,20,255}),true);
  gslc_ElemXSeekbarSetPosFunc(&m_gui,pElemRef,&CbSlidePos);
  gslc_ElemXSeekbarSetStyle(&m_gui,pElemRef,true,GSLC_COL_WHITE,false,GSLC_COL_GRAY,
    0,100,GSLC_COL_GRAY);
  m_pElemAudioinUsbVol = pElemRef;
  
  // Create E_ELEM_AUDIOIN_USB_VOL_TEXT runtime modifiable text
  static char m_sDisplayText88[5] = "-20";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_AUDIOIN_USB_VOL_TEXT,E_PG_AUDIOIN,(gslc_tsRect){265,60,48,15},
    (char*)m_sDisplayText88,5,E_ARIAL_14_BOLD);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);
  m_pElemAudioinUsbVolTxt = pElemRef;
  
  // Create E_ELEM_TEXT77 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT77,E_PG_AUDIOIN,(gslc_tsRect){15,35,80,14},
    (char*)"Input Source",0,E_ARIAL_10);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GRAY);
  
  // Create E_ELEM_TEXT78 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT78,E_PG_AUDIOIN,(gslc_tsRect){20,120,65,14},
    (char*)"Input Gain",0,E_ARIAL_10);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GRAY);
  
  // Create E_ELEM_TEXT79 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT79,E_PG_AUDIOIN,(gslc_tsRect){40,185,17,11},
    (char*)"dB",0,E_ARIAL_10);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT80 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT80,E_PG_AUDIOIN,(gslc_tsRect){125,35,50,16},
    (char*)"Analog",0,E_ARIAL_12);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_BLACK);
  
  // Create E_ELEM_TEXT81 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT81,E_PG_AUDIOIN,(gslc_tsRect){245,35,33,13},
    (char*)"USB",0,E_ARIAL_12);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT82 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT82,E_PG_AUDIOIN,(gslc_tsRect){125,75,19,10},
    (char*)"+10",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT83 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT83,E_PG_AUDIOIN,(gslc_tsRect){135,100,7,10},
    (char*)"0",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT84 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT84,E_PG_AUDIOIN,(gslc_tsRect){125,125,19,10},
    (char*)"-10",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT85 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT85,E_PG_AUDIOIN,(gslc_tsRect){125,225,19,10},
    (char*)"-50",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT86 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT86,E_PG_AUDIOIN,(gslc_tsRect){125,175,19,10},
    (char*)"-30",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT89 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT89,E_PG_AUDIOIN,(gslc_tsRect){240,75,19,10},
    (char*)"+10",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT90 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT90,E_PG_AUDIOIN,(gslc_tsRect){250,100,7,10},
    (char*)"0",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT91 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT91,E_PG_AUDIOIN,(gslc_tsRect){240,125,19,10},
    (char*)"-10",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT92 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT92,E_PG_AUDIOIN,(gslc_tsRect){240,175,19,10},
    (char*)"-30",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT93 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT93,E_PG_AUDIOIN,(gslc_tsRect){240,225,19,10},
    (char*)"-50",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);

  // Create E_DRAW_LINE7 line 
  pElemRef = gslc_ElemCreateLine(&m_gui,E_DRAW_LINE7,E_PG_AUDIOIN,205,35,205,235);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_GRAY,GSLC_COL_GRAY);
  
  // Create E_ELEM_TEXT94 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT94,E_PG_AUDIOIN,(gslc_tsRect){185,225,13,10},
    (char*)"dB",0,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_RIGHT);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);
  
  // Create E_ELEM_TEXT95 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT95,E_PG_AUDIOIN,(gslc_tsRect){300,225,13,10},
    (char*)"dB",0,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_RIGHT);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);

  // -----------------------------------
  // PAGE: E_PG_HOME
  
  
  // create E_ELEM_HOME_SYNTH_BTN button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_HOME_SYNTH_BTN,E_PG_HOME,
    (gslc_tsRect){10,40,140,40},(char*)"        Synth",0,E_ARIAL_14,&CbBtnCommon);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_LEFT);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_GRAY);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create E_ELEM_HOME_MIDI_BTN button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_HOME_MIDI_BTN,E_PG_HOME,
    (gslc_tsRect){10,90,140,40},(char*)"        MIDI",0,E_ARIAL_14,&CbBtnCommon);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_LEFT);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_GRAY);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create E_ELEM_HOME_RECODER_BTN button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_HOME_RECODER_BTN,E_PG_HOME,
    (gslc_tsRect){10,140,140,40},(char*)"        Recoder",0,E_ARIAL_14,&CbBtnCommon);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_LEFT);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_GRAY);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create E_ELEM_HOME_FX_BTN button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_HOME_FX_BTN,E_PG_HOME,
    (gslc_tsRect){10,190,140,40},(char*)"        FX",0,E_ARIAL_14,&CbBtnCommon);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_LEFT);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_GRAY);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create E_ELEM_HOME_WAVE_BTN button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_HOME_WAVE_BTN,E_PG_HOME,
    (gslc_tsRect){170,40,140,40},(char*)"        WaveTable",0,E_ARIAL_13,&CbBtnCommon);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_LEFT);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_GRAY);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create E_ELEM_HOME_DRUM_BTN button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_HOME_DRUM_BTN,E_PG_HOME,
    (gslc_tsRect){170,90,140,40},(char*)"        Drum",0,E_ARIAL_14,&CbBtnCommon);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_LEFT);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_GRAY);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create E_ELEM_HOME_KEYBOARD_BTN button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_HOME_KEYBOARD_BTN,E_PG_HOME,
    (gslc_tsRect){170,140,140,40},(char*)"        Keyboard",0,E_ARIAL_14,&CbBtnCommon);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_LEFT);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_GRAY);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create E_ELEM_HOME_SETTINGS_BTN button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_HOME_SETTINGS_BTN,E_PG_HOME,
    (gslc_tsRect){170,190,140,40},(char*)"        Settings",0,E_ARIAL_14,&CbBtnCommon);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_LEFT);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_GRAY);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // Create E_ELEM_TEXT105 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT105,E_PG_HOME,(gslc_tsRect){20,150,16,24},
    (char*)"0",0,E_AWESOMEF100_18);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT107 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT107,E_PG_HOME,(gslc_tsRect){175,200,23,25},
    (char*)"-",0,E_AWESOMEF080_18);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT109 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT109,E_PG_HOME,(gslc_tsRect){175,150,23,25},
    (char*)"-",0,E_AWESOMEF080_18);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
 
  // Create E_ELEM_IMAGE13 using Image 
  pElemRef = gslc_ElemCreateImg(&m_gui,E_ELEM_IMAGE13,E_PG_HOME,(gslc_tsRect){15,95,30,30},
    gslc_GetImageFromProg((const unsigned char*)midi_logo,GSLC_IMGREF_FMT_BMP24));
 
  // Create E_ELEM_IMAGE16 using Image 
  pElemRef = gslc_ElemCreateImg(&m_gui,E_ELEM_IMAGE16,E_PG_HOME,(gslc_tsRect){15,45,30,30},
    gslc_GetImageFromProg((const unsigned char*)synth_logo,GSLC_IMGREF_FMT_BMP24));
 
  // Create E_ELEM_IMAGE17 using Image 
  pElemRef = gslc_ElemCreateImg(&m_gui,E_ELEM_IMAGE17,E_PG_HOME,(gslc_tsRect){175,45,30,30},
    gslc_GetImageFromProg((const unsigned char*)sf2_logo,GSLC_IMGREF_FMT_BMP24));
 
  // Create E_ELEM_IMAGE18 using Image 
  pElemRef = gslc_ElemCreateImg(&m_gui,E_ELEM_IMAGE18,E_PG_HOME,(gslc_tsRect){15,195,30,30},
    gslc_GetImageFromProg((const unsigned char*)fx_logo,GSLC_IMGREF_FMT_BMP24));

  // -----------------------------------
  // PAGE: E_PG_WAVE
  
   
  // Create E_ELEM_WAVE_PEAK_BOX box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_WAVE_PEAK_BOX,E_PG_WAVE,(gslc_tsRect){300,90,15,10});

  // Create progress bar E_ELEM_WAVE_VOL_BAR 
  pElemRef = gslc_ElemXProgressCreate(&m_gui,E_ELEM_WAVE_VOL_BAR,E_PG_WAVE,&m_sXBarGauge23,
    (gslc_tsRect){300,105,15,125},0,100,0,GSLC_COL_GREEN_LT3,true);
  m_pElemWaveVolBar = pElemRef;
  
  // create E_ELEM_WAVE_VELOCTIY_BTN button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_WAVE_VELOCTIY_BTN,E_PG_WAVE,
    (gslc_tsRect){10,200,80,30},(char*)"Velocity",0,E_ARIAL_10,&CbBtnCommon);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_WHITE,GSLC_COL_GRAY);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemWaveVelocityBtn = pElemRef;
  
  // create E_ELEM_WAVE_OCTAVE_INC_BTN button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_WAVE_OCTAVE_INC_BTN,E_PG_WAVE,
    (gslc_tsRect){235,200,30,30},(char*)"g",0,E_AWESOMEF000_12,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_RED,GSLC_COL_BLACK,GSLC_COL_GRAY);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemWaveOctaveIncBtn = pElemRef;
  
  // create E_ELEM_WAVE_OCTAVE_DEC_BTN button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_WAVE_OCTAVE_DEC_BTN,E_PG_WAVE,
    (gslc_tsRect){195,200,30,30},(char*)"h",0,E_AWESOMEF000_9,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_RED,GSLC_COL_BLACK,GSLC_COL_GRAY);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemWaveOctaveDecBtn = pElemRef;
  
  // Create E_ELEM_WAVE_OCTAVE_TEXT runtime modifiable text
  static char m_sDisplayText120[3] = "0";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_WAVE_OCTAVE_TEXT,E_PG_WAVE,(gslc_tsRect){165,210,20,14},
    (char*)m_sDisplayText120,3,E_ARIAL_13);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  m_pElemWaveOctaveTxt = pElemRef;

  // Create ring gauge E_ELEM_WAVE_VOL_RING 
  static char m_sRingText10[4] = "";
  pElemRef = gslc_ElemXRingGaugeCreate(&m_gui,E_ELEM_WAVE_VOL_RING,E_PG_WAVE,&m_sXRingGauge10,
          (gslc_tsRect){210,120,50,50},
          (char*)m_sRingText10,4,E_ARIAL_12_BOLD);
  gslc_ElemXRingGaugeSetValRange(&m_gui, pElemRef, 0, 30);
  gslc_ElemXRingGaugeSetVal(&m_gui, pElemRef, 15); // Set initial value
  gslc_ElemXRingGaugeSetThickness(&m_gui,pElemRef, 6);
  gslc_ElemXRingGaugeSetAngleRange(&m_gui,pElemRef, 225, 270, true);
  gslc_ElemXRingGaugeSetColorActiveFlat(&m_gui,pElemRef, GSLC_COL_GREEN_DK2);
  gslc_ElemXRingGaugeSetColorInactive(&m_gui,pElemRef, ((gslc_tsColor){0,61,0}));
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  m_pElemWaveVolRing = pElemRef;
  
  // create E_ELEM_WAVE_SOUND_BTN button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_WAVE_SOUND_BTN,E_PG_WAVE,
    (gslc_tsRect){75,40,230,30},(char*)"Electric Piano",0,E_ARIAL_12_BOLD,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_GRAY);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemWaveSoundBtn = pElemRef;
  
  // Create E_ELEM_TEXT119 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT119,E_PG_WAVE,(gslc_tsRect){100,210,60,14},
    (char*)"Octave: ",0,E_ARIAL_12);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT121 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT121,E_PG_WAVE,(gslc_tsRect){280,120,13,10},
    (char*)"-5",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT122 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT122,E_PG_WAVE,(gslc_tsRect){280,85,13,10},
    (char*)"dB",0,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_RIGHT);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);
  
  // Create E_ELEM_TEXT123 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT123,E_PG_WAVE,(gslc_tsRect){285,100,7,10},
    (char*)"0",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT126 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT126,E_PG_WAVE,(gslc_tsRect){275,160,19,10},
    (char*)"-15",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT129 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT129,E_PG_WAVE,(gslc_tsRect){275,220,19,10},
    (char*)"-30",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT130 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT130,E_PG_WAVE,(gslc_tsRect){10,50,52,13},
    (char*)"Sound:",0,E_ARIAL_12);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT134 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT134,E_PG_WAVE,(gslc_tsRect){210,100,47,11},
    (char*)"Volume",0,E_ARIAL_10);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);

  // Create E_DRAW_LINE8 line 
  pElemRef = gslc_ElemCreateLine(&m_gui,E_DRAW_LINE8,E_PG_WAVE,5,80,315,80);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_GRAY,GSLC_COL_GRAY);
  
  // Create E_ELEM_TEXT138 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT138,E_PG_WAVE,(gslc_tsRect){228,160,13,9},
    (char*)"dB",0,E_ARIAL_8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // create E_ELEM_BTN39 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN39,E_PG_WAVE,
    (gslc_tsRect){10,95,85,30},(char*)"Compressor",0,E_ARIAL_10,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_GRAY);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemWaveVelocityBtn39 = pElemRef;
  
  // create E_ELEM_BTN40 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN40,E_PG_WAVE,
    (gslc_tsRect){110,95,85,30},(char*)"Modulation",0,E_ARIAL_10,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_GRAY);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemWaveVelocityBtn39_40 = pElemRef;
  
  // create E_ELEM_BTN42 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN42,E_PG_WAVE,
    (gslc_tsRect){110,140,85,30},(char*)"Reverb",0,E_ARIAL_10,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_GRAY);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemWaveVelocityBtn39_40_42 = pElemRef;
  
  // create E_ELEM_BTN43 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN43,E_PG_WAVE,
    (gslc_tsRect){10,140,85,30},(char*)"Delay",0,E_ARIAL_10,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_GRAY);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemWaveVelocityBtn39_40_42_43 = pElemRef;
//<InitGUI !End!>

//<Startup !Start!>
  gslc_GuiRotate(&m_gui, 3);
//<Startup !End!>

}

