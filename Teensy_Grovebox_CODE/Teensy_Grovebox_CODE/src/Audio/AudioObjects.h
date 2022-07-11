#ifndef AUDIO_OBJECTS_H
#define AUDIO_OBJECTS_H

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
extern AudioSynthWavetable      wavetable0;     //xy=433.54896545410156,583.4569816589355
extern AudioSynthWaveform       waveform0; //xy=434.00000762939453,621.4545478820801
extern AudioSynthWaveform       waveform4; //xy=434,1035.45458984375
extern AudioSynthWavetable      wavetable4; //xy=434.57151794433594,998.1689014434814
extern AudioSynthWaveform       waveform3; //xy=436.0000305175781,927.4545555114746
extern AudioSynthWaveform       waveform1;      //xy=437.0000305175781,721.4545478820801
extern AudioSynthWaveform       waveform2; //xy=437.00000762939453,833.454553604126
extern AudioSynthWavetable      wavetable2; //xy=437.5715675354004,797.1688632965088
extern AudioSynthWavetable      wavetable1; //xy=439.57154083251953,684.1689052581787
extern AudioSynthWavetable      wavetable3; //xy=439.5715637207031,893.1688661575317
extern AudioSynthWavetable      wavetable5; //xy=440.5715637207031,1096.8959617614746
extern AudioSynthWaveform       waveform5; //xy=441,1131.45458984375
extern AudioSynthWavetable      wavetable6; //xy=441.5715637207031,1198.8959655761719
extern AudioSynthWaveform       waveform6; //xy=442.00000762939453,1235.4545602798462
extern AudioSynthWavetable      wavetable7; //xy=442.5715675354004,1295.8959636688232
extern AudioSynthWaveform       waveform7; //xy=444.00001525878906,1333.2727994918823
extern AudioMixer4              voiceSwitch4; //xy=669.0000610351562,1001.1819458007812
extern AudioMixer4              voiceSwitch2; //xy=673.0000152587891,816.090950012207
extern AudioMixer4              voiceSwitch5; //xy=672.0000610351562,1105.1820373535156
extern AudioMixer4              voiceSwitch6; //xy=672.0000610351562,1211.182041168213
extern AudioMixer4              voiceSwitch7; //xy=673.0000610351562,1306.1820449829102
extern AudioMixer4              voiceSwitch3; //xy=676.0000610351562,913.1819438934326
extern AudioMixer4              voiceSwitch1; //xy=678.0000152587891,707.0909042358398
extern AudioMixer4              voiceSwitch0; //xy=680.0000152587891,601.0909004211426
extern AudioMixer4              voiceMixer0_0;         //xy=884.5716323852539,784.8958778381348
extern AudioMixer4              voiceMixer0_1; //xy=885.5714988708496,1138.8958854675293
extern AudioMixer4              voiceMixer1_0; //xy=1096.793716430664,944.0072288513184
extern AudioFilterBiquad        freeverbBiquadL;        //xy=1361.7662887573242,995.4155788421631
extern AudioFilterBiquad        freeverbBiquadR; //xy=1362.7662811279297,1030.4155797958374
extern AudioMixer4              freeverbMixerL; //xy=1376.9755249023438,1095.7851486206055
extern AudioMixer4              freeverbMixerR; //xy=1377.6103897094727,1162.7014503479004
extern AudioInputI2S            i2sIN;           //xy=1427.5835037231445,471.16686630249023
extern AudioInputUSB            usbIN;           //xy=1435.583423614502,729.1668548583984
extern AudioAmplifier           ampI2sInR;           //xy=1589.5834274291992,493.07589530944824
extern AudioAmplifier           ampI2sInL;           //xy=1592.5834274291992,453.075891494751
extern AudioAmplifier           ampUsbInR; //xy=1594.5834274291992,749.1668138504028
extern AudioAmplifier           ampUsbInL; //xy=1597.5834274291992,709.1668100357056
extern AudioAnalyzePeak         peakVelocity;          //xy=1620.3332977294922,238.48499202728271
extern AudioAmplifier           ampInsOutL;           //xy=1740.294334411621,1053.6019268035889
extern AudioAmplifier           ampInsOutR; //xy=1740.4761543273926,1094.420021057129
extern AudioMixer4              mixerSWPeakUsbInL;  //xy=1764.5834197998047,576.0758819580078
extern AudioMixer4              mixerSWPeakUsbInR; //xy=1766.1287841796875,649.0758514404297
extern AudioMixer4              mixerSWPeakLmInL; //xy=1776.583480834961,310.16680908203125
extern AudioMixer4              mixerSWPeakLmInR; //xy=1778.1288452148438,383.1667785644531
extern AudioAnalyzePeak         peakMixerInsL; //xy=1900.9774322509766,922.409252166748
extern AudioAnalyzePeak         peakMixerInsR; //xy=1912.1997375488281,964.6315307617188
extern AudioAnalyzePeak         peakLmInL; //xy=1959.038070678711,307.1668424606323
extern AudioAnalyzePeak         peakLmInR; //xy=1961.583438873291,383.1668224334717
extern AudioAnalyzePeak         peakUsbInL; //xy=1968.5834350585938,577.1668071746826
extern AudioAnalyzePeak         peakUsbInR; //xy=1968.5834579467773,646.1668949127197
extern AudioAnalyzePeak         peakMixerLmR; //xy=2132.5834426879883,330.1667995452881
extern AudioAnalyzePeak         peakMixerLmL; //xy=2133.5834426879883,290.16679763793945
extern AudioMixer4              mixerOutI2sL;         //xy=2139.5834197998047,422.1668243408203
extern AudioMixer4              mixerOutI2sR;         //xy=2141.5834197998047,503.16683769226074
extern AudioAnalyzePeak         peakMixerUsbL; //xy=2141.765266418457,657.3486318588257
extern AudioAnalyzePeak         peakMixerUsbR;  //xy=2142.765266418457,699.3486335277557
extern AudioMixer4              mixerOutUsbR; //xy=2145.58341217041,878.166805267334
extern AudioMixer4              mixerOutUsbL; //xy=2146.5834197998047,789.166805267334
extern AudioAmplifier           ampMasterOutI2sL;           //xy=2331.492515563965,429.1668128967285
extern AudioAmplifier           ampMasterOutI2sR; //xy=2335.492576599121,499.16682052612305
extern AudioAmplifier           ampMasterOutUsbL; //xy=2356.492515563965,801.166805267334
extern AudioAmplifier           ampMasterOutUsbR; //xy=2360.492515563965,863.1668071746826
extern AudioMixer4              mixerSWPeakI2sL;         //xy=2552.583526611328,378.1668167114258
extern AudioMixer4              mixerSWPeakI2sR; //xy=2559.67440032959,531.1668014526367
extern AudioMixer4              mixerSWPeakUsbR;  //xy=2565.674430847168,929.9851341247559
extern AudioMixer4              mixerSWPeakUsbL;  //xy=2574.674705505371,720.1669902801514
extern AudioOutputI2S           i2sOUT;           //xy=2597.5834884643555,456.1668128967285
extern AudioOutputUSB           usbOUT;           //xy=2613.583396911621,832.1668071746826
extern AudioAnalyzePeak         peakI2sL;          //xy=2725.492706298828,377.1668291091919
extern AudioAnalyzePeak         peakI2sR;          //xy=2734.4929809570312,532.1669578552246
extern AudioAnalyzePeak         peakUsbR; //xy=2747.4927940368652,930.1670408248901
extern AudioAnalyzePeak         peakUsbL; //xy=2765.4929809570312,721.1670360565186
extern AudioControlSGTL5000     sgtl5000_1;     //xy=1499.5834312438965,339.1668577194214
// GUItool: end automatically generated code

#endif