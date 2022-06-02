#include "AudioSynth.h"
#include "AudioIO.h"
#include "SF2_Samples/pianoelectrique_samples.h"
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

    // initiailze all voices
    voiceArr[0].waveTable = &wavetable0;
    voiceArr[1].waveTable = &wavetable1;
    voiceArr[2].waveTable = &wavetable2;
    voiceArr[3].waveTable = &wavetable3;
    voiceArr[4].waveTable = &wavetable4;
    voiceArr[5].waveTable = &wavetable5;
    voiceArr[6].waveTable = &wavetable6;
    voiceArr[7].waveTable = &wavetable7;

    // set initial instrument
    for (int i = 0; i < MAX_VOICE; i++)
    {
        voiceArr[i].setInstrument(pianoelectrique);
    }

    // put all voices in idle list
    for (int i = 0; i < MAX_VOICE; i++)
    {
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
    voiceArr[voiceFound].noteOn(noteToFreq(note), map(velocity, 0, 1, 0.2, 1));
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
            if(isSustain)
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

            if(playingNote.empty())
                break;
        }
        else
        {
            it++; // the iterator increment is moved here because after erase(), "it" becomes invalid.
        }
    }
}

void AudioSynth_::setMasterVol(int8_t vol)
{
    float gain = dBtoGain(vol);
    mainVolume[0]->gain(gain);
    mainVolume[1]->gain(gain);
}