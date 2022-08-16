#include "AudioVoice.h"
#include "AudioUtility.h"
#include "AudioSynth.h"

AudioVoice::AudioVoice()
{
}

void AudioVoice::setOscFreq(uint8_t id, float freq)
{
    if (oscOctave[id] || oscSemi[id] || oscDetune[id])
        freq *= (powf(2, oscOctave[id] + (((float)oscSemi[id] + oscDetune[id]) / 12.0f)));

    waveform[id]->frequency(freq);
}

void AudioVoice::noteOn(uint8_t note, float amp)
{
    frequency = noteToFreq(note);
    curNote = note;
    curAmp = amp;
    switch (curVoiceMode)
    {
    case VOICE_MODE_SYNTH:
        setOscFreq(0, frequency);
        setOscFreq(1, frequency);
        ampEnv->noteOn();
        env[0]->noteOn();
        env[1]->noteOn();
        break;

    case VOICE_MODE_WAVETABLE:
        waveTable->playFrequency(frequency);
        waveTable->amplitude(amp);
        break;
    }
}

void AudioVoice::noteOff()
{
    switch (curVoiceMode)
    {
    case VOICE_MODE_SYNTH:
        ampEnv->noteOff();
        env[0]->noteOff();
        env[1]->noteOff();
        break;

    case VOICE_MODE_WAVETABLE:
        waveTable->stop();
        break;
    }
}

// set the amount of pitch bend in semitones
void AudioVoice::setPitchbend(float semitone, float amount)
{
    curPitchbend = amount;
    switch (curVoiceMode)
    {
    case VOICE_MODE_SYNTH:
        setOscFreq(0, frequency * powf(2.0f, semitone / 12.0f));
        setOscFreq(1, frequency * powf(2.0f, semitone / 12.0f));
        break;

    case VOICE_MODE_WAVETABLE:
        waveTable->setFrequency(frequency * powf(2.0f, semitone / 12.0f));
        break;
    }
}

void AudioVoice::setModwheel(float amount)
{
    curModwheel = amount;
}

// use the audio mixer to select voice mode (soucre of voice)
void AudioVoice::setVoiceMode(uint8_t mode)
{
    curVoiceMode = mode;
    for (uint8_t i = 0; i < 4; i++)
    {
        if (i == mode)
        {
            voiceSwitch->gain(1.0f, i);
        }
        else
        {
            voiceSwitch->gain(0.0f, i);
        }
    }
}

// set the output waveform of the synth voice
void AudioVoice::setOscWaveform(uint8_t id, uint8_t wave)
{
    switch (wave)
    {
    case WAVE_OSC_SINE:
        waveform[id]->begin(WAVEFORM_SINE);
        break;
    case WAVE_OSC_TRIANGLE:
        waveform[id]->begin(WAVEFORM_TRIANGLE);
        break;
    case WAVE_OSC_SAW:
        waveform[id]->begin(WAVEFORM_BANDLIMIT_SAWTOOTH);
        break;
    case WAVE_OSC_SQUARE:
        waveform[id]->begin(WAVEFORM_BANDLIMIT_PULSE);
        break;
    }
}

void AudioVoice::setOscOctave(uint8_t id, int8_t value)
{
    oscOctave[id] = value;
    setOscFreq(id, frequency);
}

void AudioVoice::setOscSemi(uint8_t id, int8_t value)
{
    oscSemi[id] = value;
    setOscFreq(id, frequency);
}

void AudioVoice::setOscDetune(uint8_t id, float amount)
{
    oscDetune[id] = amount;
    setOscFreq(id, frequency);
}

void AudioVoice::setAmpEnvelope(float delay, float attack, float decay, float sustain, float release)
{
    ampEnv->delay(delay);
    ampEnv->attack(attack);
    ampEnv->hold(0);
    ampEnv->decay(decay);
    ampEnv->sustain(sustain);
    ampEnv->release(release);
}

void AudioVoice::setLfoWaveform(uint8_t id, uint8_t wave)
{
    switch (wave)
    {
    case WAVE_LFO_SINE:
        lfo[id]->begin(WAVEFORM_SINE);
        break;
    case WAVE_LFO_TRIANGLE:
        lfo[id]->begin(WAVEFORM_TRIANGLE);
        break;
    case WAVE_LFO_SAW:
        lfo[id]->begin(WAVEFORM_BANDLIMIT_SAWTOOTH);
        break;
    case WAVE_LFO_SAW_REV:
        lfo[id]->begin(WAVEFORM_BANDLIMIT_SAWTOOTH_REVERSE);
        break;
    case WAVE_LFO_SQUARE:
        lfo[id]->begin(WAVEFORM_BANDLIMIT_PULSE);
        break;
    case WAVE_LFO_SAMPLE_HOLD:
        lfo[id]->begin(WAVEFORM_SAMPLE_HOLD);
        break;
    }
}

void AudioVoice::setEnvelope(uint8_t id, float delay, float attack, float decay, float sustain, float release)
{
    env[id]->delay(delay);
    env[id]->attack(attack);
    env[id]->hold(0);
    env[id]->decay(decay);
    env[id]->sustain(sustain);
    env[id]->release(release);
}

void AudioVoice::updateModulation()
{
    if (curVoiceMode != VOICE_MODE_SYNTH)
        return;

    float modSrcValue[MOD_SRC_MAX] = {0.0f};
    float modTgtValue[MOD_TGT_MAX] = {0.0f};
    bool dirty[MOD_TGT_MAX] = {false};
    // get all modulation source value and store it
    for (uint8_t i = 0; i < MOD_SRC_MAX; i++)
    {
        switch (i)
        {
        case MOD_SRC_LFO1:
            modSrcValue[i] = lfoSample[0]->readSample() / 32768.0f;
            break;
        case MOD_SRC_LFO2:
            modSrcValue[i] = lfoSample[1]->readSample() / 32768.0f;
            break;
        case MOD_SRC_AMPENV:
            modSrcValue[i] = ampEnvSample->readSample() / 32768.0f;
            break;
        case MOD_SRC_ENV1:
            modSrcValue[i] = envSample[0]->readSample() / 32768.0f;
            break;
        case MOD_SRC_ENV2:
            modSrcValue[i] = envSample[1]->readSample() / 32768.0f;
            break;
        case MOD_SRC_PITCHBEND:
            modSrcValue[i] = curPitchbend;
            break;
        case MOD_SRC_MODWHEEL:
            modSrcValue[i] = curModwheel;
            break;
        case MOD_SRC_PITCH:
            modSrcValue[i] = (curNote - 64) / 64.0f;
            break;
        case MOD_SRC_VELOCITY:
            modSrcValue[i] = curAmp;
            break;
        }
    }

    // process all the modulations in modList, store the result value in modTgtValue
    for (std::list<ModulationEntry>::iterator it = modList->begin(); it != modList->end(); it++)
    {
        float value = modSrcValue[it->source];
        // calculate amount
        value *= it->amount;
        // add to the target value storege (using +=, so one target and be affected by multiple sources)
        modTgtValue[it->target] += value;
        // mark dirty
        dirty[it->target] = true;
    }
    // set the final modulation value to the targets
    // get the current value from AudioSynth
    for (uint8_t i = 0; i < MOD_TGT_MAX; i++)
    {
        if (dirty[i])
        {
            switch (i)
            {
            case MOD_TGT_OSC1_FREQ:
                // the modulation range is 4 octaves
                setOscFreq(0, frequency * powf(2, modTgtValue[i] * 4.0f));
                break;
            case MOD_TGT_OSC1_LEVEL:
                setOscLevel(0, AudioSynth.curSynthParam.oscLevel[0] + modTgtValue[i]);
                break;
            case MOD_TGT_OSC1_PWM:
                setOscPwm(0, AudioSynth.curSynthParam.oscPwm[0] + modTgtValue[i]);
                break;
            case MOD_TGT_OSC2_FREQ:
                setOscFreq(1, frequency * powf(2, modTgtValue[i] * 4.0f));
                break;
            case MOD_TGT_OSC2_LEVEL:
                setOscLevel(1, AudioSynth.curSynthParam.oscLevel[1] + modTgtValue[i]);
                break;
            case MOD_TGT_OSC2_PWM:
                setOscPwm(1, AudioSynth.curSynthParam.oscPwm[1] + modTgtValue[i]);
                break;
            case MOD_TGT_NOISE_LEVEL:
                setNoiseLevel(AudioSynth.curSynthParam.noiseLevel + modTgtValue[i]);
                break;
            case MOD_TGT_FILTER_CUTOFF:
                setLadderFreq(AudioSynth.curSynthParam.ladderFreq * powf(10, modTgtValue[i] * 3.0f));
                break;
            case MOD_TGT_FILTER_RESONANCE:
                setLadderResonance(AudioSynth.curSynthParam.ladderResonance + modTgtValue[i]);
                break;
            case MOD_TGT_LFO1_FREQ:
                setLfoFreq(0, AudioSynth.curSynthParam.lfoFreq[0] * powf(2, modTgtValue[i] * 7.0f));
                break;
            case MOD_TGT_LFO1_LEVEL:
                setLfoLevel(0, AudioSynth.curSynthParam.lfoLevel[0] + modTgtValue[i]);
                break;
            case MOD_TGT_LFO2_FREQ:
                setLfoFreq(1, AudioSynth.curSynthParam.lfoFreq[1] * powf(2, modTgtValue[i] * 7.0f));
                break;
            case MOD_TGT_LFO2_LEVEL:
                setLfoLevel(1, AudioSynth.curSynthParam.lfoLevel[1] + modTgtValue[i]);
                break;
            case MOD_TGT_AMPENV_DELAY:
                setAmpEnvelope(AudioSynth.curSynthParam.ampEnvVal[0] * powf(1.05f, modTgtValue[i] * 100.0f),
                               AudioSynth.curSynthParam.ampEnvVal[1],
                               AudioSynth.curSynthParam.ampEnvVal[2],
                               AudioSynth.curSynthParam.ampEnvVal[3],
                               AudioSynth.curSynthParam.ampEnvVal[4]);
                break;
            case MOD_TGT_AMPENV_ATTACK:
                setAmpEnvelope(AudioSynth.curSynthParam.ampEnvVal[0],
                               AudioSynth.curSynthParam.ampEnvVal[1] * powf(1.05f, modTgtValue[i] * 100.0f),
                               AudioSynth.curSynthParam.ampEnvVal[2],
                               AudioSynth.curSynthParam.ampEnvVal[3],
                               AudioSynth.curSynthParam.ampEnvVal[4]);
                break;
            case MOD_TGT_AMPENV_DECAY:
                setAmpEnvelope(AudioSynth.curSynthParam.ampEnvVal[0],
                               AudioSynth.curSynthParam.ampEnvVal[1],
                               AudioSynth.curSynthParam.ampEnvVal[2] * powf(1.05f, modTgtValue[i] * 100.0f),
                               AudioSynth.curSynthParam.ampEnvVal[3],
                               AudioSynth.curSynthParam.ampEnvVal[4]);
                break;
            case MOD_TGT_AMPENV_SUSTAIN:
                setAmpEnvelope(AudioSynth.curSynthParam.ampEnvVal[0],
                               AudioSynth.curSynthParam.ampEnvVal[1],
                               AudioSynth.curSynthParam.ampEnvVal[2],
                               AudioSynth.curSynthParam.ampEnvVal[3] + modTgtValue[i],
                               AudioSynth.curSynthParam.ampEnvVal[4]);
                break;
            case MOD_TGT_AMPENV_RELEASE:
                setAmpEnvelope(AudioSynth.curSynthParam.ampEnvVal[0],
                               AudioSynth.curSynthParam.ampEnvVal[1],
                               AudioSynth.curSynthParam.ampEnvVal[2],
                               AudioSynth.curSynthParam.ampEnvVal[3],
                               AudioSynth.curSynthParam.ampEnvVal[4] * powf(1.05f, modTgtValue[i] * 100.0f));
                break;
            case MOD_TGT_ENV1_DELAY:
                setEnvelope(0, AudioSynth.curSynthParam.envVal[0][0] * powf(1.05f, modTgtValue[i] * 100.0f),
                            AudioSynth.curSynthParam.envVal[0][1],
                            AudioSynth.curSynthParam.envVal[0][2],
                            AudioSynth.curSynthParam.envVal[0][3],
                            AudioSynth.curSynthParam.envVal[0][4]);
                break;
            case MOD_TGT_ENV1_ATTACK:
                setEnvelope(0, AudioSynth.curSynthParam.envVal[0][0],
                            AudioSynth.curSynthParam.envVal[0][1] * powf(1.05f, modTgtValue[i] * 100.0f),
                            AudioSynth.curSynthParam.envVal[0][2],
                            AudioSynth.curSynthParam.envVal[0][3],
                            AudioSynth.curSynthParam.envVal[0][4]);
                break;
            case MOD_TGT_ENV1_DECAY:
                setEnvelope(0, AudioSynth.curSynthParam.envVal[0][0],
                            AudioSynth.curSynthParam.envVal[0][1],
                            AudioSynth.curSynthParam.envVal[0][2] * powf(1.05f, modTgtValue[i] * 100.0f),
                            AudioSynth.curSynthParam.envVal[0][3],
                            AudioSynth.curSynthParam.envVal[0][4]);
                break;
            case MOD_TGT_ENV1_SUSTAIN:
                setEnvelope(0, AudioSynth.curSynthParam.envVal[0][0],
                            AudioSynth.curSynthParam.envVal[0][1],
                            AudioSynth.curSynthParam.envVal[0][2],
                            AudioSynth.curSynthParam.envVal[0][3] + modTgtValue[i],
                            AudioSynth.curSynthParam.envVal[0][4]);
                break;
            case MOD_TGT_ENV1_RELEASE:
                setEnvelope(0, AudioSynth.curSynthParam.envVal[0][0],
                            AudioSynth.curSynthParam.envVal[0][1],
                            AudioSynth.curSynthParam.envVal[0][2],
                            AudioSynth.curSynthParam.envVal[0][3],
                            AudioSynth.curSynthParam.envVal[0][4] * powf(1.05f, modTgtValue[i] * 100.0f));
                break;
            case MOD_TGT_ENV2_DELAY:
                setEnvelope(1, AudioSynth.curSynthParam.envVal[1][0] * powf(1.05f, modTgtValue[i] * 100.0f),
                            AudioSynth.curSynthParam.envVal[1][1],
                            AudioSynth.curSynthParam.envVal[1][2],
                            AudioSynth.curSynthParam.envVal[1][3],
                            AudioSynth.curSynthParam.envVal[1][4]);
                break;
            case MOD_TGT_ENV2_ATTACK:
                setEnvelope(1, AudioSynth.curSynthParam.envVal[1][0],
                            AudioSynth.curSynthParam.envVal[1][1] * powf(1.05f, modTgtValue[i] * 100.0f),
                            AudioSynth.curSynthParam.envVal[1][2],
                            AudioSynth.curSynthParam.envVal[1][3],
                            AudioSynth.curSynthParam.envVal[1][4]);
                break;
            case MOD_TGT_ENV2_DECAY:
                setEnvelope(1, AudioSynth.curSynthParam.envVal[1][0],
                            AudioSynth.curSynthParam.envVal[1][1],
                            AudioSynth.curSynthParam.envVal[1][2] * powf(1.05f, modTgtValue[i] * 100.0f),
                            AudioSynth.curSynthParam.envVal[1][3],
                            AudioSynth.curSynthParam.envVal[1][4]);
                break;
            case MOD_TGT_ENV2_SUSTAIN:
                setEnvelope(1, AudioSynth.curSynthParam.envVal[1][0],
                            AudioSynth.curSynthParam.envVal[1][1],
                            AudioSynth.curSynthParam.envVal[1][2],
                            AudioSynth.curSynthParam.envVal[1][3] + modTgtValue[i],
                            AudioSynth.curSynthParam.envVal[1][4]);
                break;
            case MOD_TGT_ENV2_RELEASE:
                setEnvelope(1, AudioSynth.curSynthParam.envVal[1][0],
                            AudioSynth.curSynthParam.envVal[1][1],
                            AudioSynth.curSynthParam.envVal[1][2],
                            AudioSynth.curSynthParam.envVal[1][3],
                            AudioSynth.curSynthParam.envVal[1][4] * powf(1.05f, modTgtValue[i] * 100.0f));
                break;
            }
        }
    }
}

// reset the modulated target's value when removing a modulation entry
// TODO: There might be a more elegant way to do this
void AudioVoice::resetModulaltion(modTarget target)
{
    switch (target)
    {
    case MOD_TGT_OSC1_FREQ:
        setOscFreq(0, frequency);
        break;
    case MOD_TGT_OSC1_LEVEL:
        setOscLevel(0, AudioSynth.curSynthParam.oscLevel[0]);
        break;
    case MOD_TGT_OSC1_PWM:
        setOscPwm(0, AudioSynth.curSynthParam.oscPwm[0]);
        break;
    case MOD_TGT_OSC2_FREQ:
        setOscFreq(1, frequency);
        break;
    case MOD_TGT_OSC2_LEVEL:
        setOscLevel(1, AudioSynth.curSynthParam.oscLevel[1]);
        break;
    case MOD_TGT_OSC2_PWM:
        setOscPwm(1, AudioSynth.curSynthParam.oscPwm[1]);
        break;
    case MOD_TGT_NOISE_LEVEL:
        setNoiseLevel(AudioSynth.curSynthParam.noiseLevel);
        break;
    case MOD_TGT_FILTER_CUTOFF:
        setLadderFreq(AudioSynth.curSynthParam.ladderFreq);
        break;
    case MOD_TGT_FILTER_RESONANCE:
        setLadderResonance(AudioSynth.curSynthParam.ladderResonance);
        break;
    case MOD_TGT_LFO1_FREQ:
        setLfoFreq(0, AudioSynth.curSynthParam.lfoFreq[0]);
        break;
    case MOD_TGT_LFO1_LEVEL:
        setLfoLevel(0, AudioSynth.curSynthParam.lfoLevel[0]);
        break;
    case MOD_TGT_LFO2_FREQ:
        setLfoFreq(1, AudioSynth.curSynthParam.lfoFreq[1]);
        break;
    case MOD_TGT_LFO2_LEVEL:
        setLfoLevel(1, AudioSynth.curSynthParam.lfoLevel[1]);
        break;
    case MOD_TGT_AMPENV_DELAY:
    case MOD_TGT_AMPENV_ATTACK:
    case MOD_TGT_AMPENV_DECAY:
    case MOD_TGT_AMPENV_SUSTAIN:
    case MOD_TGT_AMPENV_RELEASE:
        setAmpEnvelope(AudioSynth.curSynthParam.ampEnvVal[0],
                       AudioSynth.curSynthParam.ampEnvVal[1],
                       AudioSynth.curSynthParam.ampEnvVal[2],
                       AudioSynth.curSynthParam.ampEnvVal[3],
                       AudioSynth.curSynthParam.ampEnvVal[4]);
        break;
    case MOD_TGT_ENV1_DELAY:
    case MOD_TGT_ENV1_ATTACK:
    case MOD_TGT_ENV1_DECAY:
    case MOD_TGT_ENV1_SUSTAIN:
    case MOD_TGT_ENV1_RELEASE:
        setEnvelope(0, AudioSynth.curSynthParam.envVal[0][0],
                    AudioSynth.curSynthParam.envVal[0][1],
                    AudioSynth.curSynthParam.envVal[0][2],
                    AudioSynth.curSynthParam.envVal[0][3],
                    AudioSynth.curSynthParam.envVal[0][4]);
        break;
    case MOD_TGT_ENV2_DELAY:
    case MOD_TGT_ENV2_ATTACK:
    case MOD_TGT_ENV2_DECAY:
    case MOD_TGT_ENV2_SUSTAIN:
    case MOD_TGT_ENV2_RELEASE:
        setEnvelope(1, AudioSynth.curSynthParam.envVal[1][0],
                    AudioSynth.curSynthParam.envVal[1][1],
                    AudioSynth.curSynthParam.envVal[1][2],
                    AudioSynth.curSynthParam.envVal[1][3],
                    AudioSynth.curSynthParam.envVal[1][4]);
        break;
    }
}