#ifndef AUDIO_OBJECTS_H
#define AUDIO_OBJECTS_H

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
extern AudioSynthWavetable      wavetable4; //xy=85.57147216796875,1324.1688346862793
extern AudioSynthWavetable      wavetable0;     //xy=87.54894256591797,1138.456974029541
extern AudioSynthWavetable      wavetable2; //xy=87.57147216796875,1228.1688327789307
extern AudioSynthWavetable      wavetable3; //xy=87.57147216796875,1275.168833732605
extern AudioSynthWavetable      wavetable6; //xy=87.57147216796875,1412.8959312438965
extern AudioSynthWavetable      wavetable1; //xy=88.57147216796875,1182.1688289642334
extern AudioSynthWavetable      wavetable7; //xy=88.57147216796875,1465.8959331512451
extern AudioSynthWavetable      wavetable5; //xy=89.57147216796875,1368.8959293365479
extern AudioMixer4              voiceMixer0_1; //xy=321.5714797973633,1375.8959941864014
extern AudioMixer4              voiceMixer0_0;         //xy=334.5714797973633,1205.895990371704
extern AudioMixer4              voiceMixer1_0; //xy=520.5714797973633,1292.8959941864014
extern AudioEffectDelay         delay1;         //xy=954.333309173584,1001.0176696777344
extern AudioMixer4              delayMixer; //xy=977.6190147399902,1108.6928062438965
extern AudioEffectFreeverbStereo freeverbs1;     //xy=1172.476146697998,1012.8749980926514
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
extern AudioAnalyzePeak         peakMixerInsR; //xy=1953.3107070922852,979.0759334564209
extern AudioAnalyzePeak         peakMixerInsL; //xy=1954.3107070922852,939.0759315490723
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
extern AudioMixer4              mixerSWPeakI2sL;         //xy=2556.58358001709,287.16679763793945
extern AudioMixer4              mixerSWRmsI2sL; //xy=2558.5835762023926,356.16684341430664
extern AudioMixer4              mixerSWPeakUsbL;  //xy=2558.67440032959,675.1668815612793
extern AudioMixer4              mixerSWPeakI2sR; //xy=2559.67440032959,531.1668014526367
extern AudioMixer4              mixerSWPeakUsbR;  //xy=2559.67440032959,949.9850215911865
extern AudioMixer4              mixerSWRmsUsbR; //xy=2559.67440032959,1017.9850234985352
extern AudioMixer4              mixerSWRmsUsbL; //xy=2562.6743965148926,746.166877746582
extern AudioMixer4              mixerSWRmsI2sR; //xy=2563.6744384765625,599.1668167114258
extern AudioOutputI2S           i2sOUT;           //xy=2597.5834884643555,456.1668128967285
extern AudioOutputUSB           usbOUT;           //xy=2613.583396911621,832.1668071746826
extern AudioAnalyzePeak         peakI2sL;          //xy=2729.49275970459,286.16681003570557
extern AudioAnalyzeRMS          rmsI2sL;           //xy=2734.492763519287,354.1668453216553
extern AudioAnalyzePeak         peakUsbR; //xy=2741.492763519287,950.1669282913208
extern AudioAnalyzeRMS          rmsUsbR; //xy=2743.49267578125,1017.166841506958
extern AudioAnalyzePeak         peakUsbL; //xy=2754.49267578125,671.1668815612793
extern AudioAnalyzeRMS          rmsUsbL; //xy=2755.492649078369,753.1668672561646
extern AudioAnalyzePeak         peakI2sR;          //xy=2774.4928016662598,533.1669015884399
extern AudioAnalyzeRMS          rmsI2sR;           //xy=2777.4929809570312,590.166862487793
extern AudioConnection          patchCord1;
extern AudioConnection          patchCord2;
extern AudioConnection          patchCord3;
extern AudioConnection          patchCord4;
extern AudioConnection          patchCord5;
extern AudioConnection          patchCord6;
extern AudioConnection          patchCord7;
extern AudioConnection          patchCord8;
extern AudioConnection          patchCord9;
extern AudioConnection          patchCord10;
extern AudioConnection          patchCord11;
extern AudioConnection          patchCord12;
extern AudioConnection          patchCord13;
extern AudioConnection          patchCord14;
extern AudioConnection          patchCord15;
extern AudioConnection          patchCord16;
extern AudioConnection          patchCord17;
extern AudioConnection          patchCord18;
extern AudioConnection          patchCord19;
extern AudioConnection          patchCord20;
extern AudioConnection          patchCord21;
extern AudioConnection          patchCord22;
extern AudioConnection          patchCord23;
extern AudioConnection          patchCord24;
extern AudioConnection          patchCord25;
extern AudioConnection          patchCord26;
extern AudioConnection          patchCord27;
extern AudioConnection          patchCord28;
extern AudioConnection          patchCord29;
extern AudioConnection          patchCord30;
extern AudioConnection          patchCord31;
extern AudioConnection          patchCord32;
extern AudioConnection          patchCord33;
extern AudioConnection          patchCord34;
extern AudioConnection          patchCord35;
extern AudioConnection          patchCord36;
extern AudioConnection          patchCord37;
extern AudioConnection          patchCord38;
extern AudioConnection          patchCord39;
extern AudioConnection          patchCord40;
extern AudioConnection          patchCord41;
extern AudioConnection          patchCord42;
extern AudioConnection          patchCord43;
extern AudioConnection          patchCord44;
extern AudioConnection          patchCord45;
extern AudioConnection          patchCord46;
extern AudioConnection          patchCord47;
extern AudioConnection          patchCord48;
extern AudioConnection          patchCord49;
extern AudioConnection          patchCord50;
extern AudioConnection          patchCord51;
extern AudioConnection          patchCord52;
extern AudioConnection          patchCord53;
extern AudioConnection          patchCord54;
extern AudioConnection          patchCord55;
extern AudioConnection          patchCord56;
extern AudioConnection          patchCord57;
extern AudioConnection          patchCord58;
extern AudioConnection          patchCord59;
extern AudioConnection          patchCord60;
extern AudioConnection          patchCord61;
extern AudioConnection          patchCord62;
extern AudioConnection          patchCord63;
extern AudioConnection          patchCord64;
extern AudioConnection          patchCord65;
extern AudioConnection          patchCord66;
extern AudioConnection          patchCord67;
extern AudioConnection          patchCord68;
extern AudioConnection          patchCord69;
extern AudioConnection          patchCord70;
extern AudioConnection          patchCord71;
extern AudioConnection          patchCord72;
extern AudioConnection          patchCord73;
extern AudioConnection          patchCord74;
extern AudioConnection          patchCord75;
extern AudioConnection          patchCord76;
extern AudioConnection          patchCord77;
extern AudioConnection          patchCord78;
extern AudioConnection          patchCord79;
extern AudioConnection          patchCord80;
extern AudioConnection          patchCord81;
extern AudioConnection          patchCord82;
extern AudioConnection          patchCord83;
extern AudioConnection          patchCord84;
extern AudioConnection          patchCord85;
extern AudioConnection          patchCord86;
extern AudioConnection          patchCord87;
extern AudioConnection          patchCord88;
extern AudioConnection          patchCord89;
extern AudioControlSGTL5000     sgtl5000_1;     //xy=1499.5834312438965,339.1668577194214
// GUItool: end automatically generated code

#endif