#include "AudioIO.h"

AudioIO_ AudioIO;

// constructor
AudioIO_::AudioIO_()
{
    inputFader[InputTracks::LINEMIC_IN][0] = &ampI2sInL;
    inputFader[InputTracks::LINEMIC_IN][1] = &ampI2sInR;
    inputFader[InputTracks::USB_IN][0] = &ampUsbInL;
    inputFader[InputTracks::USB_IN][1] = &ampUsbInR;
    
    inputMeterSW[InputTracks::LINEMIC_IN][0] = &mixerSWPeakLmInL;
    inputMeterSW[InputTracks::LINEMIC_IN][1] = &mixerSWPeakLmInR;
    inputMeterSW[InputTracks::USB_IN][0] = &mixerSWPeakUsbInL;
    inputMeterSW[InputTracks::USB_IN][1] = &mixerSWPeakUsbInR;

    inputPeak[InputTracks::LINEMIC_IN][0] = &peakLmInL;
    inputPeak[InputTracks::LINEMIC_IN][1] = &peakLmInR;
    inputPeak[InputTracks::USB_IN][0] = &peakUsbInL;
    inputPeak[InputTracks::USB_IN][1] = &peakUsbInR;

    outputMixer[MasterTracks::ANALOG_OUT][0] = &mixerOutI2sL;
    outputMixer[MasterTracks::ANALOG_OUT][1] = &mixerOutI2sR;
    outputMixer[MasterTracks::USB_OUT][0] = &mixerOutUsbL;
    outputMixer[MasterTracks::USB_OUT][1] = &mixerOutUsbR;

    outputFader[MasterTracks::ANALOG_OUT][0] = &ampMasterOutI2sL;
    outputFader[MasterTracks::ANALOG_OUT][1] = &ampMasterOutI2sR;
    outputFader[MasterTracks::USB_OUT][0] = &ampMasterOutUsbL;
    outputFader[MasterTracks::USB_OUT][1] = &ampMasterOutUsbR;

    // todo: add more tracks
    mixerPeak[MixerTracks::I2S][0] = &peakMixerLmL;
    mixerPeak[MixerTracks::I2S][1] = &peakMixerLmR;
    mixerPeak[MixerTracks::USB][0] = &peakMixerUsbL;
    mixerPeak[MixerTracks::USB][1] = &peakMixerUsbR;
    mixerPeak[MixerTracks::INSTRUMENTS][0] = &peakMixerInsL;
    mixerPeak[MixerTracks::INSTRUMENTS][1] = &peakMixerInsR;

    outputMeterSWPeak[MasterTracks::ANALOG_OUT][0] = &mixerSWPeakI2sL;
    outputMeterSWPeak[MasterTracks::ANALOG_OUT][1] = &mixerSWPeakI2sR;
    outputMeterSWPeak[MasterTracks::USB_OUT][0] = &mixerSWPeakUsbL;
    outputMeterSWPeak[MasterTracks::USB_OUT][1] = &mixerSWPeakUsbR;

    outputPeak[MasterTracks::ANALOG_OUT][0] = &peakI2sL;
    outputPeak[MasterTracks::ANALOG_OUT][1] = &peakI2sR;
    outputPeak[MasterTracks::USB_OUT][0] = &peakUsbL;
    outputPeak[MasterTracks::USB_OUT][1] = &peakUsbR;

}

// level meter functions
floatStereo AudioIO_::getMixerPeak(MasterTracks output, MixerTracks track)
{
    floatStereo temp;
    if (mixerPeak[track][0]->available() && mixerPeak[track][1]->available())
    {
        temp.l = mixerPeak[track][0]->read();
        temp.r = mixerPeak[track][1]->read();
        if (!mixerInPreFader)
        {
            temp.l *= mixerFinalGain[output][track][0];
            temp.r *= mixerFinalGain[output][track][1];
        }
    }
    else
    {
        temp.l = temp.r = -1;
    }
    return temp;
}
floatStereo AudioIO_::getInputPeak(InputTracks track)
{
    floatStereo temp;
    if (inputPeak[track][0]->available() && inputPeak[track][1]->available())
    {
        temp.l = inputPeak[track][0]->read();
        temp.r = inputPeak[track][1]->read();
    }
    else
    {
        temp.l = temp.r = -1;
    }
    return temp;
}
floatStereo AudioIO_::getMasterRMS(MasterTracks track)
{
    floatStereo temp;
    if (outputRms[track][0]->available() && outputRms[track][1]->available())
    {
        temp.l = outputRms[track][0]->read();
        temp.r = outputRms[track][1]->read();
    }
    else
    {
        temp.l = temp.r = -1;
    }
    return temp;
}
floatStereo AudioIO_::getMasterPeak(MasterTracks track)
{
    floatStereo temp;
    if (outputPeak[track][0]->available() && outputPeak[track][1]->available())
    {
        temp.l = outputPeak[track][0]->read();
        temp.r = outputPeak[track][1]->read();
    }
    else
    {
        temp.l = temp.r = -1;
    }
    return temp;
}
void AudioIO_::setMasterLevelMode(LevelMeterMode mode)
{
    for (uint8_t i = 0; i < 2; i++)
    {
        for(uint8_t j = 0; j < 2; j++)
        {
            outputMeterSWPeak[i][j]->gain(mode, 1);
            outputMeterSWPeak[i][j]->gain(1-mode, 0);
            outputMeterSWRms[i][j]->gain(mode, 1);
            outputMeterSWRms[i][j]->gain(1-mode, 0);
        }
    }
}
void AudioIO_::setMixerLevelMode(LevelMeterMode mode)
{
    // for post-fader, get gain value from mixer and calculate level
    // for pre-fader, read peak directly
    mixerInPreFader = mode;
}
void AudioIO_::setInputLevelMode(LevelMeterMode mode)
{
    for (uint8_t i = 0; i < 2; i++)
    {
        for(uint8_t j = 0; j < 2; j++)
        {
            inputMeterSW[i][j]->gain(mode, 1);
            inputMeterSW[i][j]->gain(1-mode, 0);
        }
    }
}

// Master output controls
void AudioIO_::setMasterVolume(MasterTracks track, float value)
{
    outputFader[track][0]->gain(value);
    outputFader[track][1]->gain(value);
}

// Mixer output controls
// Sets the mixer volume for the fader, also re-calculate the pan
void AudioIO_::setMixerVolume(MasterTracks output, MixerTracks track, float value)
{
    mixerGain[output][track] = value;
    mixerFinalGain[output][track][0] = (mixerPan[output][track] > 0) ? value * (1 - mixerPan[output][track]) : value;
    mixerFinalGain[output][track][1] = (mixerPan[output][track] < 0) ? value * (1 + mixerPan[output][track]) : value;
    
    outputMixer[output][0]->gain(track, mixerFinalGain[output][track][0]);
    outputMixer[output][1]->gain(track, mixerFinalGain[output][track][1]);
}
// Set the mixer pan.
void AudioIO_::setMixerPan(MasterTracks output, MixerTracks track, float value)
{
    mixerPan[output][track] = value;
    setMixerVolume(output, track, mixerGain[output][track]);
}

// Input controls
void AudioIO_::setInputVolume(InputTracks track, float value)
{
    inputFader[track][0]->gain(value);
    inputFader[track][1]->gain(value);
}