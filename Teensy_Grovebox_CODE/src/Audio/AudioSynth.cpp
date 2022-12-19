#include "AudioSynth.h"
#include "AudioIO.h"
#include "SF2_Samples/SF2_Samples.h"
#include "AudioUtility.h"

AudioSynth_ AudioSynth;

AudioSynth_::AudioSynth_()
{
    // set up voice mixers
    voiceMixer[0] = &voiceMixer0_0;
    voiceMixer[1] = &voiceMixer0_1;

    for (auto i : voiceMixer)
    {
        i->gain(0, 0.25);
        i->gain(1, 0.25);
        i->gain(2, 0.25);
        i->gain(3, 0.25);
    }

    voiceFinalMixer = &voiceMixer1_0;

    voiceFinalMixer->gain(0, 0.5);
    voiceFinalMixer->gain(1, 0.5);

    // setup master volume
    mainVolume[0] = &ampInsOutL;
    mainVolume[1] = &ampInsOutR;

    // *initiailze all voices
    // wavetable synth
    voiceArr[0].waveTable = &wavetable0;
    voiceArr[1].waveTable = &wavetable1;
    voiceArr[2].waveTable = &wavetable2;
    voiceArr[3].waveTable = &wavetable3;
    voiceArr[4].waveTable = &wavetable4;
    voiceArr[5].waveTable = &wavetable5;
    voiceArr[6].waveTable = &wavetable6;
    voiceArr[7].waveTable = &wavetable7;
    // 2 waveforms
    voiceArr[0].waveform[0] = &waveform0_0;
    voiceArr[0].waveform[1] = &waveform0_1;
    voiceArr[1].waveform[0] = &waveform1_0;
    voiceArr[1].waveform[1] = &waveform1_1;
    voiceArr[2].waveform[0] = &waveform2_0;
    voiceArr[2].waveform[1] = &waveform2_1;
    voiceArr[3].waveform[0] = &waveform3_0;
    voiceArr[3].waveform[1] = &waveform3_1;
    voiceArr[4].waveform[0] = &waveform4_0;
    voiceArr[4].waveform[1] = &waveform4_1;
    voiceArr[5].waveform[0] = &waveform5_0;
    voiceArr[5].waveform[1] = &waveform5_1;
    voiceArr[6].waveform[0] = &waveform6_0;
    voiceArr[6].waveform[1] = &waveform6_1;
    voiceArr[7].waveform[0] = &waveform7_0;
    voiceArr[7].waveform[1] = &waveform7_1;
    // noise generator
    voiceArr[0].noise = &noise0;
    voiceArr[1].noise = &noise1;
    voiceArr[2].noise = &noise2;
    voiceArr[3].noise = &noise3;
    voiceArr[4].noise = &noise4;
    voiceArr[5].noise = &noise5;
    voiceArr[6].noise = &noise6;
    voiceArr[7].noise = &noise7;
    // voice mode switch
    voiceArr[0].voiceSwitch = &voiceSwitch0;
    voiceArr[1].voiceSwitch = &voiceSwitch1;
    voiceArr[2].voiceSwitch = &voiceSwitch2;
    voiceArr[3].voiceSwitch = &voiceSwitch3;
    voiceArr[4].voiceSwitch = &voiceSwitch4;
    voiceArr[5].voiceSwitch = &voiceSwitch5;
    voiceArr[6].voiceSwitch = &voiceSwitch6;
    voiceArr[7].voiceSwitch = &voiceSwitch7;
    // amp envelope
    voiceArr[0].ampEnv = &ampEnvelope0;
    voiceArr[1].ampEnv = &ampEnvelope1;
    voiceArr[2].ampEnv = &ampEnvelope2;
    voiceArr[3].ampEnv = &ampEnvelope3;
    voiceArr[4].ampEnv = &ampEnvelope4;
    voiceArr[5].ampEnv = &ampEnvelope5;
    voiceArr[6].ampEnv = &ampEnvelope6;
    voiceArr[7].ampEnv = &ampEnvelope7;
    // ladder filter
    voiceArr[0].ladderFilter = &ladder0;
    voiceArr[1].ladderFilter = &ladder1;
    voiceArr[2].ladderFilter = &ladder2;
    voiceArr[3].ladderFilter = &ladder3;
    voiceArr[4].ladderFilter = &ladder4;
    voiceArr[5].ladderFilter = &ladder5;
    voiceArr[6].ladderFilter = &ladder6;
    voiceArr[7].ladderFilter = &ladder7;
    // lfo1
    voiceArr[0].lfo[0] = &lfo0_0;
    voiceArr[1].lfo[0] = &lfo1_0;
    voiceArr[2].lfo[0] = &lfo2_0;
    voiceArr[3].lfo[0] = &lfo3_0;
    voiceArr[4].lfo[0] = &lfo4_0;
    voiceArr[5].lfo[0] = &lfo5_0;
    voiceArr[6].lfo[0] = &lfo6_0;
    voiceArr[7].lfo[0] = &lfo7_0;
    // lfo2
    voiceArr[0].lfo[1] = &lfo0_1;
    voiceArr[1].lfo[1] = &lfo1_1;
    voiceArr[2].lfo[1] = &lfo2_1;
    voiceArr[3].lfo[1] = &lfo3_1;
    voiceArr[4].lfo[1] = &lfo4_1;
    voiceArr[5].lfo[1] = &lfo5_1;
    voiceArr[6].lfo[1] = &lfo6_1;
    voiceArr[7].lfo[1] = &lfo7_1;
    // env1
    voiceArr[0].env[0] = &envelope0_0;
    voiceArr[1].env[0] = &envelope1_0;
    voiceArr[2].env[0] = &envelope2_0;
    voiceArr[3].env[0] = &envelope3_0;
    voiceArr[4].env[0] = &envelope4_0;
    voiceArr[5].env[0] = &envelope5_0;
    voiceArr[6].env[0] = &envelope6_0;
    voiceArr[7].env[0] = &envelope7_0;
    // env2
    voiceArr[0].env[1] = &envelope0_1;
    voiceArr[1].env[1] = &envelope1_1;
    voiceArr[2].env[1] = &envelope2_1;
    voiceArr[3].env[1] = &envelope3_1;
    voiceArr[4].env[1] = &envelope4_1;
    voiceArr[5].env[1] = &envelope5_1;
    voiceArr[6].env[1] = &envelope6_1;
    voiceArr[7].env[1] = &envelope7_1;
    // lfoSample[0]
    voiceArr[0].lfoSample[0] = &lfoSample0_0;
    voiceArr[1].lfoSample[0] = &lfoSample1_0;
    voiceArr[2].lfoSample[0] = &lfoSample2_0;
    voiceArr[3].lfoSample[0] = &lfoSample3_0;
    voiceArr[4].lfoSample[0] = &lfoSample4_0;
    voiceArr[5].lfoSample[0] = &lfoSample5_0;
    voiceArr[6].lfoSample[0] = &lfoSample6_0;
    voiceArr[7].lfoSample[0] = &lfoSample7_0;
    // lfoSample[1]
    voiceArr[0].lfoSample[1] = &lfoSample0_1;
    voiceArr[1].lfoSample[1] = &lfoSample1_1;
    voiceArr[2].lfoSample[1] = &lfoSample2_1;
    voiceArr[3].lfoSample[1] = &lfoSample3_1;
    voiceArr[4].lfoSample[1] = &lfoSample4_1;
    voiceArr[5].lfoSample[1] = &lfoSample5_1;
    voiceArr[6].lfoSample[1] = &lfoSample6_1;
    voiceArr[7].lfoSample[1] = &lfoSample7_1;
    // envSample[0]
    voiceArr[0].envSample[0] = &envSample0_0;
    voiceArr[1].envSample[0] = &envSample1_0;
    voiceArr[2].envSample[0] = &envSample2_0;
    voiceArr[3].envSample[0] = &envSample3_0;
    voiceArr[4].envSample[0] = &envSample4_0;
    voiceArr[5].envSample[0] = &envSample5_0;
    voiceArr[6].envSample[0] = &envSample6_0;
    voiceArr[7].envSample[0] = &envSample7_0;
    // envSample[1]
    voiceArr[0].envSample[1] = &envSample0_1;
    voiceArr[1].envSample[1] = &envSample1_1;
    voiceArr[2].envSample[1] = &envSample2_1;
    voiceArr[3].envSample[1] = &envSample3_1;
    voiceArr[4].envSample[1] = &envSample4_1;
    voiceArr[5].envSample[1] = &envSample5_1;
    voiceArr[6].envSample[1] = &envSample6_1;
    voiceArr[7].envSample[1] = &envSample7_1;
    // ampEnvSample
    voiceArr[0].ampEnvSample = &ampEnvSample0;
    voiceArr[1].ampEnvSample = &ampEnvSample1;
    voiceArr[2].ampEnvSample = &ampEnvSample2;
    voiceArr[3].ampEnvSample = &ampEnvSample3;
    voiceArr[4].ampEnvSample = &ampEnvSample4;
    voiceArr[5].ampEnvSample = &ampEnvSample5;
    voiceArr[6].ampEnvSample = &ampEnvSample6;
    voiceArr[7].ampEnvSample = &ampEnvSample7;

    // set env1 and env2 DC generator
    envDc0.amplitude(1);
    envDc1.amplitude(1);
    envDc2.amplitude(1);
    envDc3.amplitude(1);
    envDc4.amplitude(1);
    envDc5.amplitude(1);
    envDc6.amplitude(1);
    envDc7.amplitude(1);
    // set osc mixer
    oscMixer0.gain(0, 1);
    oscMixer0.gain(1, 1);
    oscMixer0.gain(2, 1);
    oscMixer1.gain(0, 1);
    oscMixer1.gain(1, 1);
    oscMixer1.gain(2, 1);
    oscMixer2.gain(0, 1);
    oscMixer2.gain(1, 1);
    oscMixer2.gain(2, 1);
    oscMixer3.gain(0, 1);
    oscMixer3.gain(1, 1);
    oscMixer3.gain(2, 1);
    oscMixer4.gain(0, 1);
    oscMixer4.gain(1, 1);
    oscMixer4.gain(2, 1);
    oscMixer5.gain(0, 1);
    oscMixer5.gain(1, 1);
    oscMixer5.gain(2, 1);
    oscMixer6.gain(0, 1);
    oscMixer6.gain(1, 1);
    oscMixer6.gain(2, 1);
    oscMixer7.gain(0, 1);
    oscMixer7.gain(1, 1);
    oscMixer7.gain(2, 1);

    setSF2Instrument(0);
    setOscWaveform(0, WAVE_OSC_SINE);
    setOscWaveform(1, WAVE_OSC_SINE);
    setVoiceMode(VOICE_MODE_SYNTH);

    for (int i = 0; i < MAX_VOICE; i++)
    {
        // put voice in idle list
        idleNote.push_front(noteEntry(0, i));
        //  set modList
        voiceArr[i].setModulationList(&modList);
    }
}

void AudioSynth_::noteOn(uint8_t note)
{
    int16_t voiceFound = -1;
    // check if the note is already playing
    for (std::list<noteEntry>::iterator it = playingNote.begin(); it != playingNote.end(); it++)
    {
        if (it->note == note)
        {
            voiceFound = it->voiceIndex;
            Serial.println("DEBUG: voice found in playingNote, note = " + String(note) + " voice index = " + String(voiceFound));
            playingNote.erase(it);
            voiceArr[voiceFound].noteOff();

            break;
        }
    }
    if (voiceFound == -1)
    {
        // If the note is not playig, take the last note from idleNote list.
        if (!idleNote.empty())
        {
            voiceFound = idleNote.back().voiceIndex;
            idleNote.pop_back();
            Serial.println("DEBUG: voice found in idleNote, voice index = " + String(voiceFound));
        }
        // If the all voices are occupied, grab the last voice from playing list.
        else if (!playingNote.empty())
        {
            voiceFound = playingNote.back().voiceIndex;
            playingNote.pop_back();
            Serial.println("DEBUG: voice stole from playingNote, voice index = " + String(voiceFound));
            voiceArr[voiceFound].noteOff();
        }
        // this is not supposed to happen.
        else
        {
            Serial.println("DEBUG: voice allocation failed");
        }
    }
    // DEBUG
    if (voiceFound == -1)
        return;

    playingNote.push_front(noteEntry(note, voiceFound));
    voiceArr[voiceFound].isNoteOn = true;
    if (useVelocity)
        voiceArr[voiceFound].noteOn(note, map(velocity, 0, 1, 0.2, 1));
    else
        voiceArr[voiceFound].noteOn(note, 0.8);
    Serial.println("DEBUG: playingNote size: " + String(playingNote.size()) + " idleNote size: " + String(idleNote.size()));
}

void AudioSynth_::noteOff(uint8_t note)
{
    // Check if the note is already playing.
    for (std::list<noteEntry>::iterator it = playingNote.begin(); it != playingNote.end(); it++)
    {
        if (it->note == note)
        {
            uint8_t voiceInd = it->voiceIndex;
            voiceArr[voiceInd].isNoteOn = false;
            // If sustaining, set isNoteOn = false, and let it play in playingNote (don't stop it)
            if (isSustain)
                Serial.println("DEBUG: sustain voice in playingNote, voice index = " + String(voiceInd));
            if (!isSustain)
            {
                Serial.println("DEBUG: remove voice in playingNote, voice index = " + String(voiceInd));
                playingNote.erase(it);
                idleNote.push_front(noteEntry(note, voiceInd));
                voiceArr[voiceInd].noteOff();

                Serial.println("DEBUG: playingNote size: " + String(playingNote.size()) + " idleNote size: " + String(idleNote.size()));
            }
            break;
        }
    }
    // If not, then it may be stolen by other notes. Nothing to do here.
}

void AudioSynth_::sustainOn()
{
    isSustain = true;
}

void AudioSynth_::sustainOff()
{
    isSustain = false;
    // Find all notes in playingNotes that are noteOff (the key was released but is sustaining).
    for (std::list<noteEntry>::iterator it = playingNote.begin(); it != playingNote.end();)
    {
        uint8_t voiceInd = it->voiceIndex;
        if (!voiceArr[voiceInd].isNoteOn)
        {
            // remove the note from playingNote list and stop it.
            Serial.println("DEBUG: remove voice in playingNote, voice index = " + String(voiceInd));
            playingNote.erase(it++);
            idleNote.push_front(noteEntry(0, voiceInd));
            voiceArr[voiceInd].noteOff();
            Serial.println("DEBUG: playingNote size: " + String(playingNote.size()) + " idleNote size: " + String(idleNote.size()));

            if (playingNote.empty())
                break;
        }
        else
        {
            it++; // the iterator increment is moved here because after erase(), "it" becomes invalid.
        }
    }
}

// find all playing notes and set their pitch bend
void AudioSynth_::pitchbend(float semitone, float amount)
{
    for (uint8_t i = 0; i < MAX_VOICE; i++)
    {
        voiceArr[i].setPitchbend(semitone, amount);
    }
}

void AudioSynth_::modwheel(float amount)
{
    for (uint8_t i = 0; i < MAX_VOICE; i++)
    {
        voiceArr[i].setModwheel(amount);
    }
}

void AudioSynth_::setMasterVol(int8_t vol)
{
    float gain = dBtoGain(vol);
    mainVolume[0]->gain(gain);
    mainVolume[1]->gain(gain);
}

void AudioSynth_::setUseVelocity(bool value)
{
    useVelocity = value;
}

void AudioSynth_::setSF2Instrument(uint8_t id)
{
    if (id < MAX_SF2_INSTRUMENTS)
    {
        for (int i = 0; i < MAX_VOICE; i++)
        {
            voiceArr[i].setInstrument(*SF2_InstrumentRef[id]);
        }
    }
}

void AudioSynth_::setVoiceMode(uint8_t mode)
{
    for (int i = 0; i < MAX_VOICE; i++)
    {
        voiceArr[i].setVoiceMode(mode);
    }
}

void AudioSynth_::setOscWaveform(uint8_t id, uint8_t wave)
{
    for (int i = 0; i < MAX_VOICE; i++)
    {
        voiceArr[i].setOscWaveform(id, wave);
    }
}

void AudioSynth_::setOscOctave(uint8_t id, int8_t value)
{
    for (int i = 0; i < MAX_VOICE; i++)
    {
        voiceArr[i].setOscOctave(id, value);
    }
}

void AudioSynth_::setOscSemi(uint8_t id, int8_t value)
{
    for (int i = 0; i < MAX_VOICE; i++)
    {
        voiceArr[i].setOscSemi(id, value);
    }
}

void AudioSynth_::setOscPwm(uint8_t id, uint8_t duty)
{
    float duty_f = duty * 0.01f;
    curSynthParam.oscPwm[id] = duty_f;
    for (int i = 0; i < MAX_VOICE; i++)
    {
        voiceArr[i].setOscPwm(id, duty_f);
    }
}

void AudioSynth_::setOscDetune(uint8_t id, float amount)
{
    for (int i = 0; i < MAX_VOICE; i++)
    {
        voiceArr[i].setOscDetune(id, amount);
    }
}

void AudioSynth_::setOscLevel(uint8_t id, uint8_t amount)
{
    float gain;
    if (amount > 0)
        gain = dBtoGain(amount * 0.5f - 60); // the max level is -10 dB, to prevent clipping.
    else
        gain = 0;
    for (int i = 0; i < MAX_VOICE; i++)
    {
        voiceArr[i].setOscLevel(id, gain);
    }
    curSynthParam.oscLevel[id] = gain;
}

// set the amplitude envelope of the voice in ms (max 10000). Sustain is 0~1.
void AudioSynth_::setAmpEnvelope(float delay, float attack, float decay, float sustain, float release)
{
    for (int i = 0; i < MAX_VOICE; i++)
    {
        voiceArr[i].setAmpEnvelope(delay, attack, decay, sustain, release);
    }
    curSynthParam.ampEnvVal[0] = delay;
    curSynthParam.ampEnvVal[1] = attack;
    curSynthParam.ampEnvVal[2] = decay;
    curSynthParam.ampEnvVal[3] = sustain;
    curSynthParam.ampEnvVal[4] = release;
}

void AudioSynth_::setNoiseLevel(float amount)
{
    float gain;
    if (amount > 0)
        gain = dBtoGain(amount * 0.5f - 60); // the max level is -10 dB, to prevent clipping.
    else
        gain = 0;
    for (int i = 0; i < MAX_VOICE; i++)
    {
        voiceArr[i].setNoiseLevel(gain);
    }
    curSynthParam.noiseLevel = gain;
}

void AudioSynth_::setLadderFreq(float freq)
{
    for (int i = 0; i < MAX_VOICE; i++)
    {
        voiceArr[i].setLadderFreq(freq);
    }
    curSynthParam.ladderFreq = freq;
}

// set the ladder filter resonance. range 0~1.
void AudioSynth_::setLadderResonance(float amount)
{
    float res = map(amount, 0, 1, 0, 1.8);
    for (int i = 0; i < MAX_VOICE; i++)
    {
        voiceArr[i].setLadderResonance(res);
    }
    curSynthParam.ladderResonance = res;
}

// set the ladder filter drive. range 0~1.
void AudioSynth_::setLadderDrive(float amount)
{
    float drive = map(amount, 0, 1, 1, 4);
    for (int i = 0; i < MAX_VOICE; i++)
    {
        voiceArr[i].setLadderDrive(drive);
    }
}

// set the ladder filter passband gain. range 0~1.
void AudioSynth_::setLadderPassbandGain(float amount)
{
    float gain = map(amount, 0, 1, 0, 0.5);
    for (int i = 0; i < MAX_VOICE; i++)
    {
        voiceArr[i].setLadderPassbandGain(gain);
    }
}

void AudioSynth_::setLfoWaveform(uint8_t id, uint8_t wave)
{
    for (int i = 0; i < MAX_VOICE; i++)
    {
        voiceArr[i].setLfoWaveform(id, wave);
    }
}

void AudioSynth_::setLfoFreq(uint8_t id, float freq)
{
    for (int i = 0; i < MAX_VOICE; i++)
    {
        voiceArr[i].setLfoFreq(id, freq);
    }
    curSynthParam.lfoFreq[id] = freq;
}

void AudioSynth_::setLfoLevel(uint8_t id, float level)
{
    for (int i = 0; i < MAX_VOICE; i++)
    {
        voiceArr[i].setLfoLevel(id, level);
    }
    curSynthParam.lfoLevel[id] = level;
}

void AudioSynth_::setEnvelope(uint8_t id, float delay, float attack, float decay, float sustain, float release)
{
    for (int i = 0; i < MAX_VOICE; i++)
    {
        voiceArr[i].setEnvelope(id, delay, attack, decay, sustain, release);
    }
    curSynthParam.envVal[id][0] = delay;
    curSynthParam.envVal[id][1] = attack;
    curSynthParam.envVal[id][2] = decay;
    curSynthParam.envVal[id][3] = sustain;
    curSynthParam.envVal[id][4] = release;
}

// add a modulation to the modList and returns id. Returns -1 if not valid.
int8_t AudioSynth_::addModulation(uint8_t source, uint8_t dest)
{
    if (source < MOD_SRC_MAX && dest < MOD_TGT_MAX && modList.size() < MAX_MODULATION_COUNT)
    {
        modList.push_back(ModulationEntry((modSource)source, (modTarget)dest, 0));
        return modList.size() - 1;
    }
    return -1;
}

// set the id-th modulation amount of the modList
void AudioSynth_::setModulationAmount(uint8_t id, float amount)
{
    if (id < modList.size())
    {
        // get the modulation entry in list
        std::list<ModulationEntry>::iterator it = modList.begin();
        for (int i = 0; i < id; i++)
        {
            it++;
        }
        // set the amount
        it->amount = amount;
    }
}

// set the id-th modulation source of the modList
void AudioSynth_::setModulationSource(uint8_t id, uint8_t source)
{
    if (id < modList.size())
    {
        // get the modulation entry in list
        std::list<ModulationEntry>::iterator it = modList.begin();
        for (int i = 0; i < id; i++)
        {
            it++;
        }
        // set the source
        it->source = (modSource)source;
    }
}

// set the id-th modulation target of the modList
void AudioSynth_::setModulationTarget(uint8_t id, uint8_t target)
{
    if (id < modList.size())
    {
        // get the modulation entry in list
        std::list<ModulationEntry>::iterator it = modList.begin();
        for (int i = 0; i < id; i++)
        {
            it++;
        }
        // reset the previous target
        for (uint8_t i = 0; i < MAX_VOICE; i++)
        {
            voiceArr[i].resetModulaltion(it->target);
        }
        // set the target
        it->target = (modTarget)target;
    }
}

// remove the id-th modulation of the modList
void AudioSynth_::removeModulation(uint8_t id)
{
    if (id < modList.size())
    {
        // get the modulation entry in list
        std::list<ModulationEntry>::iterator it = modList.begin();
        for (int i = 0; i < id; i++)
        {
            it++;
        }
        // reset the modulated target value
        for (uint8_t i = 0; i < MAX_VOICE; i++)
        {
            voiceArr[i].resetModulaltion(it->target);
        }
        // remove the entry
        modList.erase(it);
    }
}

void AudioSynth_::updateModulation()
{
    for (uint8_t i = 0; i < MAX_VOICE; i++)
    {
        voiceArr[i].updateModulation();
    }
}