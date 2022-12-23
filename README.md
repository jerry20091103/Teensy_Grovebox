# Teensy Grovebox
<img src=./images/front_photo.jpg width = 800/>

- An all-in-one music multi-tool in a 25-key MIDI keyboard form factor.
- Made with Teensy 4.1 and Teensy Audio Board.
## Hardware Features
- 25-key MIDI keyboard with mechanical key switches.
- 4 encoder knobs and a joystick.
- 3.5 inch TFT touch screen.
- Built-in audio interface with stereo line input/output, and headphone output.
- Onboard speaker and microphone.
- 10+ hours of battery life.
- USB-C charging and data transfer.
- Supports sustain pedal.
- Exposed I2C and S/PDIF headers.
- ...

## Software Features
- USB MIDI keyboard with pitchbend, mod wheel, and 4 assignable knobs.
- Wavetable synth mode to play SF2 soundfonts. (with Teensy SoundFont Decoder ...link)
- Polyphonic synth engine with 8 voices, each with 2 oscillators, 2 LFOs, 3 envelopes, and 1 filter.
- Sampler mode (under development).
- Effects like delay, chorus, reverb... (under development).

## Folders in this repo
> There's a readme file in each folder with more details.
- `Teensy_Grovebox_Hardware`
    - Kicad files for schematic and PCB. 
    - 3D files for the case.
- `Teensy_Grovebox_CODE`
    - Arduino code for the Teensy 4.1.
    - Uses PlatformIO.
- `Joystick_Board`
    - Kicad schematic and PCB files for the joystick board used in the Teensy Grovebox.

<img src=./images/front_hardware_photo.jpg width=800>