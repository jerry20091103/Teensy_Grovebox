#include "pianoelectrique_samples.h"
#include "JR_bells_samples.h"
#include "JR_vibraphone_samples.h"
#include "SalL1_samples.h"

#define MAX_SF2_INSTRUMENTS 4

// displayed instrument names in lvgl dropdown menu
static const char* SF2_Instrument_Names =
{
    "Piano Electrique\n"
    "JR Bells\n"
    "JR Vibraphone\n"
    "Sal L1"
};

// array of pointers to SF2 instrument samples
static const AudioSynthWavetable::instrument_data *SF2_InstrumentRef[MAX_SF2_INSTRUMENTS] = 
{
    &pianoelectrique,
    &JR_bells,
    &JR_vibraphone,
    &SalL1
};