#include "AudioSynth.h"
#include "AudioIO.h"
#include "SF2_Samples/SF2_Samples.h"
#include "AudioUtility.h"

float noteToFreq(uint8_t note)
{
    return powf(2, (float)(note - 69) / 12.0f) * 440.0f;
}

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
    // osc mixer
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

    for (int i = 0; i < MAX_VOICE; i++)
    {
        // set initial instrument
        voiceArr[i].setInstrument(*SF2_InstrumentRef[0]);
        // set initial synth waveform
        voiceArr[i].setOscWaveform(0, WAVE_SINE);
        voiceArr[i].setOscWaveform(1, WAVE_SINE);
        // switch to initial voice mode
        voiceArr[i].setVoiceMode(VOICE_MODE_SYNTH);
        // put voice in idle list
        idleNote.push_front(noteEntry(0, i));
    }
}

void AudioSynth_::noteOn(uint8_t note)
{
    int16_t voiceFound = -1;
    // check if the note is already playing
    for (std::list<noteEntry>::iterator it = playingNote.begin(); it != playingNote.end(); it++)
    {
        if ((*it).note == note)
        {
            voiceFound = (*it).voiceIndex;
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
        voiceArr[voiceFound].noteOn(noteToFreq(note), map(velocity, 0, 1, 0.2, 1));
    else
        voiceArr[voiceFound].noteOn(noteToFreq(note), 0.8);
    if (usePitchbend)
        voiceArr[voiceFound].setPitchbend(curPitchbend);
    Serial.println("DEBUG: playingNote size: " + String(playingNote.size()) + " idleNote size: " + String(idleNote.size()));
}

void AudioSynth_::noteOff(uint8_t note)
{
    // Check if the note is already playing.
    for (std::list<noteEntry>::iterator it = playingNote.begin(); it != playingNote.end(); it++)
    {
        if ((*it).note == note)
        {
            uint8_t voiceInd = (*it).voiceIndex;
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
        uint8_t voiceInd = (*it).voiceIndex;
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
void AudioSynth_::pitchbend(float semitone)
{
    curPitchbend = semitone;
    for (std::list<noteEntry>::iterator it = playingNote.begin(); it != playingNote.end(); it++)
    {
        voiceArr[(*it).voiceIndex].setPitchbend(semitone);
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

void AudioSynth_::setUsePitchbend(bool value)
{
    usePitchbend = value;
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
    for (int i = 0; i < MAX_VOICE; i++)
    {
        voiceArr[i].setOscPwm(id, duty);
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
    if(amount > 0)
        gain = dBtoGain(amount * 0.5f - 50);
    else
        gain = 0;
    for (int i = 0; i < MAX_VOICE; i++)
    {
        voiceArr[i].setOscLevel(id, gain);
    }
}

// set the amplitude envelope of the voice in ms (max 10000). Sustain is 0~1.
void AudioSynth_::setAmpEnvelope(float delay, float attack, float decay, float sustain, float release)
{
    for (int i = 0; i < MAX_VOICE; i++)
    {
        voiceArr[i].setAmpEnvelope(delay, attack, decay, sustain, release);
    }
}

void AudioSynth_::setNoiseLevel(float amount)
{
    float gain;
    if(amount > 0)
        gain = dBtoGain(amount * 0.5f - 50);
    else
        gain = 0;
    for (int i = 0; i < MAX_VOICE; i++)
    {
        voiceArr[i].setNoiseLevel(gain);
    }
}