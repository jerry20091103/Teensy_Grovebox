#ifndef AUDIOIO_H
#define AUDIOIO_H

#include <Audio.h>
#include "Audio/AudioObjects.h"

enum MixerTracks : uint8_t
{
    I2S,
    USB,
    INSTRUMENTS,
    RECORDER
};
enum MasterTracks : uint8_t
{
    ANALOG_OUT,
    USB_OUT
};
enum InputTracks : uint8_t
{
    LINEMIC_IN,
    USB_IN
};
enum LevelMeterMode : uint8_t
{
    POST_FADER,
    PRE_FADER
};

struct floatStereo
{
    float l;
    float r;
};

class AudioIO_
{
private:
    // mixer prefader flag
    bool mixerInPreFader = false;
    // store current mixer gain for pan and post-fader level calculation
    float mixerGain[2][4];
    // store current mixer pan
    float mixerPan[2][4];
    // store calculate gain after panning
    float mixerFinalGain[2][4][2];
    
    AudioAmplifier *inputFader[2][2];
    AudioMixer4 *inputMeterSW[2][2];
    AudioAnalyzePeak *inputPeak[2][2];

    AudioMixer4 *outputMixer[2][2];
    AudioAmplifier *outputFader[2][2];
    AudioAnalyzePeak * mixerPeak[4][2];
    AudioMixer4 *outputMeterSWPeak[2][2];
    AudioMixer4 *outputMeterSWRms[2][2];
    AudioAnalyzePeak *outputPeak[2][2];
    AudioAnalyzeRMS *outputRms[2][2];

public:
    AudioIO_();
    // level meter functions
    floatStereo getMixerPeak(MasterTracks output, MixerTracks track);
    floatStereo getInputPeak(InputTracks track);
    floatStereo getMasterRMS(MasterTracks track);
    floatStereo getMasterPeak(MasterTracks track);
    void setMasterLevelMode(LevelMeterMode mode);
    void setMixerLevelMode(LevelMeterMode mode);
    void setInputLevelMode(LevelMeterMode mode);
    // Master output controls
    void setMasterVolume(MasterTracks track, float value);
    // Mixer output controls
    void setMixerVolume(MasterTracks output, MixerTracks track, float value);
    void setMixerPan(MasterTracks output, MixerTracks track, float value);
    // Input controls
    void setInputVolume(InputTracks track, float value);
};

extern AudioIO_ AudioIO;

#endif