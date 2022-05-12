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
#include "elem/XRingGauge.h"
#include "elem/XSeekbar.h"
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
#include "font_AwesomeF080.h"
#include "font_AwesomeF100.h"
#include "font_AwesomeF200.h"
//<Fonts !End!>

// ------------------------------------------------
// Defines for resources
// ------------------------------------------------
//<Resources !Start!>
#define IMG_FX_LOGO               "/fx_logo.bmp"
#define IMG_MIDI_LOGO             "/midi_logo.bmp"
#define IMG_SF2_LOGO              "/sf2_logo.bmp"
#define IMG_SYNTH_LOGO            "/synth_logo.bmp"
//<Resources !End!>

// ------------------------------------------------
// Enumerations for pages, elements, fonts, images
// ------------------------------------------------
//<Enum !Start!>
enum {E_PG_BASE,E_PG_MIDI,E_PG_POPUP_POWER,E_PG_AUDIOOUT
      ,E_PG_POPUP_OUT_MIXER,E_PG_AUDIOIN,E_PG_HOME};
enum {E_DRAW_LINE1,E_DRAW_LINE2,E_DRAW_LINE3,E_DRAW_LINE4,E_DRAW_LINE7
      ,E_ELEM_AUDIOIN_GAIN_RING,E_ELEM_AUDIOIN_LINE_IN_BTN
      ,E_ELEM_AUDIOIN_LM_L_BAR,E_ELEM_AUDIOIN_LM_PEAK_L_BOX
      ,E_ELEM_AUDIOIN_LM_PEAK_R_BOX,E_ELEM_AUDIOIN_LM_R_BAR
      ,E_ELEM_AUDIOIN_LM_VOL,E_ELEM_AUDIOIN_LM_VOL_TEXT
      ,E_ELEM_AUDIOIN_MIC_BTN,E_ELEM_AUDIOIN_PFL_BTN
      ,E_ELEM_AUDIOIN_USB_L_BAR,E_ELEM_AUDIOIN_USB_PEAK_L_BOX
      ,E_ELEM_AUDIOIN_USB_PEAK_R_BOX,E_ELEM_AUDIOIN_USB_R_BAR
      ,E_ELEM_AUDIOIN_USB_VOL,E_ELEM_AUDIOIN_USB_VOL_TEXT
      ,E_ELEM_AUDIOOUT_ANALOG_BTN,E_ELEM_AUDIOOUT_HP_VOL_RING
      ,E_ELEM_AUDIOOUT_LINE_L_BAR,E_ELEM_AUDIOOUT_LINE_PEAK_BAR
      ,E_ELEM_AUDIOOUT_LINE_PEAK_L_BOX,E_ELEM_AUDIOOUT_LINE_PEAK_R_BOX
      ,E_ELEM_AUDIOOUT_LINE_R_BAR,E_ELEM_AUDIOOUT_LINE_VOL
      ,E_ELEM_AUDIOOUT_LINE_VOL_TEXT,E_ELEM_AUDIOOUT_PP_BTN
      ,E_ELEM_AUDIOOUT_PREFADER_BTN,E_ELEM_AUDIOOUT_USB_BTN
      ,E_ELEM_AUDIOOUT_USB_L_BAR,E_ELEM_AUDIOOUT_USB_PEAK_BAR
      ,E_ELEM_AUDIOOUT_USB_PEAK_L_BOX,E_ELEM_AUDIOOUT_USB_PEAK_R_BOX
      ,E_ELEM_AUDIOOUT_USB_R_BAR,E_ELEM_AUDIOOUT_USB_VOL
      ,E_ELEM_AUDIOOUT_USB_VOL_TEXT,E_ELEM_BASE_BACK_BTN,E_ELEM_BOX10
      ,E_ELEM_BOX24,E_ELEM_BOX29,E_ELEM_BOX30,E_ELEM_BOX31,E_ELEM_BOX32
      ,E_ELEM_BOX33,E_ELEM_BOX34,E_ELEM_BOX35,E_ELEM_BOX36
      ,E_ELEM_IMAGE4,E_ELEM_IMAGE5,E_ELEM_IMAGE6,E_ELEM_IMAGE7
      ,E_ELEM_MIDI_BLUE_BOX5,E_ELEM_MIDI_BLUE_BOX6
      ,E_ELEM_MIDI_CHANNEL_DEC,E_ELEM_MIDI_CHANNEL_INC
      ,E_ELEM_MIDI_GREEN_BOX7,E_ELEM_MIDI_GREEN_BOX8
      ,E_ELEM_MIDI_MOD_BTN,E_ELEM_MIDI_OCTAVE_DEC
      ,E_ELEM_MIDI_OCTAVE_INC,E_ELEM_MIDI_PITCHBEND_BTN
      ,E_ELEM_MIDI_RED_BOX1,E_ELEM_MIDI_RED_BOX2,E_ELEM_MIDI_RING_BLUE
      ,E_ELEM_MIDI_RING_GREEN,E_ELEM_MIDI_RING_RED
      ,E_ELEM_MIDI_RING_YELLOW,E_ELEM_MIDI_TEXT12,E_ELEM_MIDI_TEXT13
      ,E_ELEM_MIDI_TEXT14,E_ELEM_MIDI_TEXT15,E_ELEM_MIDI_TEXT16
      ,E_ELEM_MIDI_TEXT23,E_ELEM_MIDI_TEXT24,E_ELEM_MIDI_TEXT25
      ,E_ELEM_MIDI_TEXT26,E_ELEM_MIDI_TEXT_1,E_ELEM_MIDI_TEXT_CHANNEL
      ,E_ELEM_MIDI_TEXT_FB_F049,E_ELEM_MIDI_TEXT_FF_F050
      ,E_ELEM_MIDI_TEXT_OCTAVE,E_ELEM_MIDI_TEXT_PLAY_F04B
      ,E_ELEM_MIDI_TEXT_STOP_F04D,E_ELEM_MIDI_YELLOW_BOX3
      ,E_ELEM_MIDI_YELLOW_BOX4,E_ELEM_OUT_MIXER_BACK_BTN
      ,E_ELEM_OUT_MIXER_INS_PAN,E_ELEM_OUT_MIXER_LM_L_BAR
      ,E_ELEM_OUT_MIXER_LM_PAN,E_ELEM_OUT_MIXER_LM_PEAK_L_BOX
      ,E_ELEM_OUT_MIXER_LM_PEAK_R_BOX,E_ELEM_OUT_MIXER_LM_R_BAR
      ,E_ELEM_OUT_MIXER_LM_VOL,E_ELEM_OUT_MIXER_LM_VOL_TEXT
      ,E_ELEM_OUT_MIXER_PAN_BTN,E_ELEM_OUT_MIXER_PFL_BTN
      ,E_ELEM_OUT_MIXER_REC_PAN,E_ELEM_OUT_MIXER_TITLE_TEXT
      ,E_ELEM_OUT_MIXER_USB_L_BAR,E_ELEM_OUT_MIXER_USB_PAN
      ,E_ELEM_OUT_MIXER_USB_PEAK_L_BOX,E_ELEM_OUT_MIXER_USB_PEAK_R_BOX
      ,E_ELEM_OUT_MIXER_USB_R_BAR,E_ELEM_OUT_MIXER_USB_VOL
      ,E_ELEM_OUT_MIXER_USB_VOL_TEXT,E_ELEM_POWER_BTN_CALCEL
      ,E_ELEM_POWER_BTN_YES,E_ELEM_TEXT101,E_ELEM_TEXT102
      ,E_ELEM_TEXT104,E_ELEM_TEXT105,E_ELEM_TEXT106,E_ELEM_TEXT107
      ,E_ELEM_TEXT108,E_ELEM_TEXT109,E_ELEM_TEXT110,E_ELEM_TEXT111
      ,E_ELEM_TEXT27,E_ELEM_TEXT28,E_ELEM_TEXT29,E_ELEM_TEXT30
      ,E_ELEM_TEXT31,E_ELEM_TEXT32,E_ELEM_TEXT33,E_ELEM_TEXT34
      ,E_ELEM_TEXT36,E_ELEM_TEXT37,E_ELEM_TEXT38,E_ELEM_TEXT40
      ,E_ELEM_TEXT41,E_ELEM_TEXT42,E_ELEM_TEXT43,E_ELEM_TEXT48
      ,E_ELEM_TEXT49,E_ELEM_TEXT50,E_ELEM_TEXT52,E_ELEM_TEXT54
      ,E_ELEM_TEXT55,E_ELEM_TEXT57,E_ELEM_TEXT59,E_ELEM_TEXT60
      ,E_ELEM_TEXT61,E_ELEM_TEXT62,E_ELEM_TEXT63,E_ELEM_TEXT64
      ,E_ELEM_TEXT65,E_ELEM_TEXT66,E_ELEM_TEXT67,E_ELEM_TEXT69
      ,E_ELEM_TEXT75,E_ELEM_TEXT76,E_ELEM_TEXT77,E_ELEM_TEXT78
      ,E_ELEM_TEXT79,E_ELEM_TEXT80,E_ELEM_TEXT81,E_ELEM_TEXT82
      ,E_ELEM_TEXT83,E_ELEM_TEXT84,E_ELEM_TEXT85,E_ELEM_TEXT86
      ,E_ELEM_TEXT89,E_ELEM_TEXT90,E_ELEM_TEXT91,E_ELEM_TEXT92
      ,E_ELEM_TEXT93,E_ELEM_TEXT94,E_ELEM_TEXT95,E_ELEM_TEXT96
      ,E_ELEM_TEXT99,E_ELEM_TEXT_BATT,E_ELEM_TEXT_TITLE};
// Must use separate enum for fonts with MAX_FONT at end to use gslc_FontSet.
enum {E_ARIAL_10,E_ARIAL_10_BOLD,E_ARIAL_12,E_ARIAL_12_BOLD,E_ARIAL_13
      ,E_ARIAL_14,E_ARIAL_14_BOLD,E_ARIAL_8,E_AWESOMEF000_10
      ,E_AWESOMEF000_12,E_AWESOMEF000_14,E_AWESOMEF000_16
      ,E_AWESOMEF000_9,E_AWESOMEF080_18,E_AWESOMEF100_18
      ,E_AWESOMEF200_14,E_BUILTIN5X8,MAX_FONT};
//<Enum !End!>

// ------------------------------------------------
// Instantiate the GUI
// ------------------------------------------------

// ------------------------------------------------
// Define the maximum number of elements and pages
// ------------------------------------------------
//<ElementDefines !Start!>
#define MAX_PAGE                7

#define MAX_ELEM_PG_BASE 4 // # Elems total on page
#define MAX_ELEM_PG_BASE_RAM MAX_ELEM_PG_BASE // # Elems in RAM

#define MAX_ELEM_PG_MIDI 34 // # Elems total on page
#define MAX_ELEM_PG_MIDI_RAM MAX_ELEM_PG_MIDI // # Elems in RAM

#define MAX_ELEM_PG_POPUP_POWER 7 // # Elems total on page
#define MAX_ELEM_PG_POPUP_POWER_RAM MAX_ELEM_PG_POPUP_POWER // # Elems in RAM

#define MAX_ELEM_PG_AUDIOOUT 36 // # Elems total on page
#define MAX_ELEM_PG_AUDIOOUT_RAM MAX_ELEM_PG_AUDIOOUT // # Elems in RAM

#define MAX_ELEM_PG_POPUP_OUT_MIXER 38 // # Elems total on page
#define MAX_ELEM_PG_POPUP_OUT_MIXER_RAM MAX_ELEM_PG_POPUP_OUT_MIXER // # Elems in RAM

#define MAX_ELEM_PG_AUDIOIN 34 // # Elems total on page
#define MAX_ELEM_PG_AUDIOIN_RAM MAX_ELEM_PG_AUDIOIN // # Elems in RAM

#define MAX_ELEM_PG_HOME 23 // # Elems total on page
#define MAX_ELEM_PG_HOME_RAM MAX_ELEM_PG_HOME // # Elems in RAM
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
extern gslc_tsElem                     m_asPopup1Elem[MAX_ELEM_PG_POPUP_POWER_RAM];
extern gslc_tsElemRef                  m_asPopup1ElemRef[MAX_ELEM_PG_POPUP_POWER];
extern gslc_tsElem                     m_asPage2Elem[MAX_ELEM_PG_AUDIOOUT_RAM];
extern gslc_tsElemRef                  m_asPage2ElemRef[MAX_ELEM_PG_AUDIOOUT];
extern gslc_tsElem                     m_asPopup2Elem[MAX_ELEM_PG_POPUP_OUT_MIXER_RAM];
extern gslc_tsElemRef                  m_asPopup2ElemRef[MAX_ELEM_PG_POPUP_OUT_MIXER];
extern gslc_tsElem                     m_asPage3Elem[MAX_ELEM_PG_AUDIOIN_RAM];
extern gslc_tsElemRef                  m_asPage3ElemRef[MAX_ELEM_PG_AUDIOIN];
extern gslc_tsElem                     m_asPage4Elem[MAX_ELEM_PG_HOME_RAM];
extern gslc_tsElemRef                  m_asPage4ElemRef[MAX_ELEM_PG_HOME];
extern gslc_tsXRingGauge               m_sXRingGauge1;
extern gslc_tsXRingGauge               m_sXRingGauge2;
extern gslc_tsXRingGauge               m_sXRingGauge3;
extern gslc_tsXRingGauge               m_sXRingGauge4;
extern gslc_tsXProgress                m_sXBarGauge7;
extern gslc_tsXProgress                m_sXBarGauge1;
extern gslc_tsXProgress                m_sXBarGauge2;
extern gslc_tsXSeekbar                 m_sXSeekbar1;
extern gslc_tsXProgress                m_sXBarGauge9;
extern gslc_tsXProgress                m_sXBarGauge10;
extern gslc_tsXProgress                m_sXBarGauge11;
extern gslc_tsXSeekbar                 m_sXSeekbar2;
extern gslc_tsXRingGauge               m_sXRingGauge5;
extern gslc_tsXProgress                m_sXBarGauge13;
extern gslc_tsXProgress                m_sXBarGauge14;
extern gslc_tsXSeekbar                 m_sXSeekbar3;
extern gslc_tsXSeekbar                 m_sXSeekbar4;
extern gslc_tsXProgress                m_sXBarGauge15;
extern gslc_tsXProgress                m_sXBarGauge16;
extern gslc_tsXSeekbar                 m_sXSeekbar8;
extern gslc_tsXSeekbar                 m_sXSeekbar5;
extern gslc_tsXSeekbar                 m_sXSeekbar6;
extern gslc_tsXSeekbar                 m_sXSeekbar7;
extern gslc_tsXProgress                m_sXBarGauge17;
extern gslc_tsXProgress                m_sXBarGauge18;
extern gslc_tsXRingGauge               m_sXRingGauge6;
extern gslc_tsXSeekbar                 m_sXSeekbar9;
extern gslc_tsXProgress                m_sXBarGauge19;
extern gslc_tsXProgress                m_sXBarGauge20;
extern gslc_tsXSeekbar                 m_sXSeekbar10;

#define MAX_STR                 100

//<GUI_Extra_Elements !End!>

// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Element References for direct access
//<Extern_References !Start!>
extern gslc_tsElemRef* m_pElemAudioinGainRing;
extern gslc_tsElemRef* m_pElemAudioinLineInBtn;
extern gslc_tsElemRef* m_pElemAudioinLmLBar;
extern gslc_tsElemRef* m_pElemAudioinLmRBar;
extern gslc_tsElemRef* m_pElemAudioinLmVol;
extern gslc_tsElemRef* m_pElemAudioinLmVolTxt;
extern gslc_tsElemRef* m_pElemAudioinMicBtn;
extern gslc_tsElemRef* m_pElemAudioinPflBtn;
extern gslc_tsElemRef* m_pElemAudioinUsbLBar;
extern gslc_tsElemRef* m_pElemAudioinUsbRBar;
extern gslc_tsElemRef* m_pElemAudioinUsbVol;
extern gslc_tsElemRef* m_pElemAudioinUsbVolTxt;
extern gslc_tsElemRef* m_pElemAudiooutHpVolRing;
extern gslc_tsElemRef* m_pElemAudiooutLineLBar;
extern gslc_tsElemRef* m_pElemAudiooutLinePeakBar;
extern gslc_tsElemRef* m_pElemAudiooutLineRBar;
extern gslc_tsElemRef* m_pElemAudiooutLineVol;
extern gslc_tsElemRef* m_pElemAudiooutLineVolTxt;
extern gslc_tsElemRef* m_pElemAudiooutPrefaderBtn;
extern gslc_tsElemRef* m_pElemAudiooutUsbLBar;
extern gslc_tsElemRef* m_pElemAudiooutUsbPeakBar;
extern gslc_tsElemRef* m_pElemAudiooutUsbRBar;
extern gslc_tsElemRef* m_pElemAudiooutUsbVol;
extern gslc_tsElemRef* m_pElemAudiooutUsbVolTxt;
extern gslc_tsElemRef* m_pElemMidiModBtn;
extern gslc_tsElemRef* m_pElemMidiPitchbendBtn;
extern gslc_tsElemRef* m_pElemMidiRingBlue;
extern gslc_tsElemRef* m_pElemMidiRingGreen;
extern gslc_tsElemRef* m_pElemMidiRingRed;
extern gslc_tsElemRef* m_pElemMidiRingYellow;
extern gslc_tsElemRef* m_pElemMidiTxtChannel;
extern gslc_tsElemRef* m_pElemMidiTxtOctave;
extern gslc_tsElemRef* m_pElemOutMixerInsPan;
extern gslc_tsElemRef* m_pElemOutMixerLmLBar;
extern gslc_tsElemRef* m_pElemOutMixerLmPan;
extern gslc_tsElemRef* m_pElemOutMixerLmRBar;
extern gslc_tsElemRef* m_pElemOutMixerLmVol;
extern gslc_tsElemRef* m_pElemOutMixerLmVolTxt;
extern gslc_tsElemRef* m_pElemOutMixerPanBtn;
extern gslc_tsElemRef* m_pElemOutMixerPflBtn;
extern gslc_tsElemRef* m_pElemOutMixerRecPan;
extern gslc_tsElemRef* m_pElemOutMixerTitleTxt;
extern gslc_tsElemRef* m_pElemOutMixerUsbLBar;
extern gslc_tsElemRef* m_pElemOutMixerUsbPan;
extern gslc_tsElemRef* m_pElemOutMixerUsbRBar;
extern gslc_tsElemRef* m_pElemOutMixerUsbVol;
extern gslc_tsElemRef* m_pElemOutMixerUsbVolTxt;
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
