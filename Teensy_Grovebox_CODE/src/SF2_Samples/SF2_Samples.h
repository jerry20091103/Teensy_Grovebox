#include "pianoelectrique_samples.h"
#include "JR_bells_samples.h"
#include "JR_vibraphone_samples.h"
#include "YDPiano_samples.h"
#include "AcoustDryKit_samples.h"

#define MAX_SF2_INSTRUMENTS 3

// displayed instrument names in lvgl dropdown menu
static const char* SF2_Instrument_Names =
{
    "Piano Electrique\n"
    //"JR Bells\n"
    "JR Vibraphone\n"
    "Drumkit"
    //"YDP Piano"
};

// array of pointers to SF2 instrument samples
static const AudioSynthWavetable::instrument_data *SF2_InstrumentRef[MAX_SF2_INSTRUMENTS] = 
{
    &pianoelectrique,
    //&JR_bells,
    &JR_vibraphone,
    &AcoustDryKit
    //&YDPiano
};