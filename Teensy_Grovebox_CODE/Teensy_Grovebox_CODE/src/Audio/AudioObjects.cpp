#include "AudioObjects.h"

// GUItool: begin automatically generated code
AudioSynthWavetable      wavetable4; //xy=85.57147216796875,1324.1688346862793
AudioSynthWavetable      wavetable0;     //xy=87.54894256591797,1138.456974029541
AudioSynthWavetable      wavetable2; //xy=87.57147216796875,1228.1688327789307
AudioSynthWavetable      wavetable3; //xy=87.57147216796875,1275.168833732605
AudioSynthWavetable      wavetable6; //xy=87.57147216796875,1412.8959312438965
AudioSynthWavetable      wavetable1; //xy=88.57147216796875,1182.1688289642334
AudioSynthWavetable      wavetable7; //xy=88.57147216796875,1465.8959331512451
AudioSynthWavetable      wavetable5; //xy=89.57147216796875,1368.8959293365479
AudioMixer4              voiceMixer0_1; //xy=321.5714797973633,1375.8959941864014
AudioMixer4              voiceMixer0_0;         //xy=334.5714797973633,1205.895990371704
AudioMixer4              voiceMixer1_0; //xy=520.5714797973633,1292.8959941864014
AudioEffectFlange        flange1;        //xy=790.3333015441895,1028.0178527832031
AudioMixer4              flangeMixer;         //xy=799.1903686523438,1096.549903869629
AudioEffectDelay         delay1;         //xy=954.333309173584,1001.0176696777344
AudioMixer4              delayMixer; //xy=977.6190147399902,1108.6928062438965
AudioEffectFreeverbStereo freeverbs1;     //xy=1172.476146697998,1012.8749980926514
AudioFilterBiquad        freeverbBiquadL;        //xy=1361.7662887573242,995.4155788421631
AudioFilterBiquad        freeverbBiquadR; //xy=1362.7662811279297,1030.4155797958374
AudioMixer4              freeverbMixerL; //xy=1374.7532806396484,1096.8961791992188
AudioMixer4              freeverbMixerR; //xy=1377.6103897094727,1162.7014503479004
AudioInputI2S            i2sIN;           //xy=1427.5835037231445,471.16686630249023
AudioInputUSB            usbIN;           //xy=1435.583423614502,729.1668548583984
AudioAmplifier           ampI2sInR;           //xy=1589.5834274291992,493.07589530944824
AudioAmplifier           ampI2sInL;           //xy=1592.5834274291992,453.075891494751
AudioAmplifier           ampUsbInR; //xy=1594.5834274291992,749.1668138504028
AudioAmplifier           ampUsbInL; //xy=1597.5834274291992,709.1668100357056
AudioAnalyzePeak         peakVelocity;          //xy=1620.3332977294922,238.48499202728271
AudioAmplifier           ampInsOutL;           //xy=1740.294334411621,1053.6019268035889
AudioAmplifier           ampInsOutR; //xy=1740.4761543273926,1094.420021057129
AudioMixer4              mixerSWPeakUsbInL;  //xy=1764.5834197998047,576.0758819580078
AudioMixer4              mixerSWPeakUsbInR; //xy=1766.1287841796875,649.0758514404297
AudioMixer4              mixerSWPeakLmInL; //xy=1776.583480834961,310.16680908203125
AudioMixer4              mixerSWPeakLmInR; //xy=1778.1288452148438,383.1667785644531
AudioAnalyzePeak         peakMixerInsR; //xy=1953.3107070922852,979.0759334564209
AudioAnalyzePeak         peakMixerInsL; //xy=1954.3107070922852,939.0759315490723
AudioAnalyzePeak         peakLmInL; //xy=1959.038070678711,307.1668424606323
AudioAnalyzePeak         peakLmInR; //xy=1961.583438873291,383.1668224334717
AudioAnalyzePeak         peakUsbInL; //xy=1968.5834350585938,577.1668071746826
AudioAnalyzePeak         peakUsbInR; //xy=1968.5834579467773,646.1668949127197
AudioAnalyzePeak         peakMixerLmR; //xy=2132.5834426879883,330.1667995452881
AudioAnalyzePeak         peakMixerLmL; //xy=2133.5834426879883,290.16679763793945
AudioMixer4              mixerOutI2sL;         //xy=2139.5834197998047,422.1668243408203
AudioMixer4              mixerOutI2sR;         //xy=2141.5834197998047,503.16683769226074
AudioAnalyzePeak         peakMixerUsbL; //xy=2141.765266418457,657.3486318588257
AudioAnalyzePeak         peakMixerUsbR;  //xy=2142.765266418457,699.3486335277557
AudioMixer4              mixerOutUsbR; //xy=2145.58341217041,878.166805267334
AudioMixer4              mixerOutUsbL; //xy=2146.5834197998047,789.166805267334
AudioAmplifier           ampMasterOutI2sL;           //xy=2331.492515563965,429.1668128967285
AudioAmplifier           ampMasterOutI2sR; //xy=2335.492576599121,499.16682052612305
AudioAmplifier           ampMasterOutUsbL; //xy=2356.492515563965,801.166805267334
AudioAmplifier           ampMasterOutUsbR; //xy=2360.492515563965,863.1668071746826
AudioMixer4              mixerSWPeakI2sL;         //xy=2556.58358001709,287.16679763793945
AudioMixer4              mixerSWRmsI2sL; //xy=2558.5835762023926,356.16684341430664
AudioMixer4              mixerSWPeakUsbL;  //xy=2558.67440032959,675.1668815612793
AudioMixer4              mixerSWPeakI2sR; //xy=2559.67440032959,531.1668014526367
AudioMixer4              mixerSWPeakUsbR;  //xy=2559.67440032959,949.9850215911865
AudioMixer4              mixerSWRmsUsbR; //xy=2559.67440032959,1017.9850234985352
AudioMixer4              mixerSWRmsUsbL; //xy=2562.6743965148926,746.166877746582
AudioMixer4              mixerSWRmsI2sR; //xy=2563.6744384765625,599.1668167114258
AudioOutputI2S           i2sOUT;           //xy=2597.5834884643555,456.1668128967285
AudioOutputUSB           usbOUT;           //xy=2613.583396911621,832.1668071746826
AudioAnalyzePeak         peakI2sL;          //xy=2729.49275970459,286.16681003570557
AudioAnalyzeRMS          rmsI2sL;           //xy=2734.492763519287,354.1668453216553
AudioAnalyzePeak         peakUsbR; //xy=2741.492763519287,950.1669282913208
AudioAnalyzeRMS          rmsUsbR; //xy=2743.49267578125,1017.166841506958
AudioAnalyzePeak         peakUsbL; //xy=2754.49267578125,671.1668815612793
AudioAnalyzeRMS          rmsUsbL; //xy=2755.492649078369,753.1668672561646
AudioAnalyzePeak         peakI2sR;          //xy=2774.4928016662598,533.1669015884399
AudioAnalyzeRMS          rmsI2sR;           //xy=2777.4929809570312,590.166862487793
AudioConnection          patchCord1(wavetable4, 0, voiceMixer0_1, 0);
AudioConnection          patchCord2(wavetable0, 0, voiceMixer0_0, 0);
AudioConnection          patchCord3(wavetable2, 0, voiceMixer0_0, 2);
AudioConnection          patchCord4(wavetable3, 0, voiceMixer0_0, 3);
AudioConnection          patchCord5(wavetable6, 0, voiceMixer0_1, 2);
AudioConnection          patchCord6(wavetable1, 0, voiceMixer0_0, 1);
AudioConnection          patchCord7(wavetable7, 0, voiceMixer0_1, 3);
AudioConnection          patchCord8(wavetable5, 0, voiceMixer0_1, 1);
AudioConnection          patchCord9(voiceMixer0_1, 0, voiceMixer1_0, 1);
AudioConnection          patchCord10(voiceMixer0_0, 0, voiceMixer1_0, 0);
AudioConnection          patchCord11(voiceMixer1_0, flange1);
AudioConnection          patchCord12(voiceMixer1_0, 0, flangeMixer, 0);
AudioConnection          patchCord13(voiceMixer1_0, ampInsOutL);
AudioConnection          patchCord14(voiceMixer1_0, ampInsOutR);
AudioConnection          patchCord15(flange1, 0, flangeMixer, 1);
AudioConnection          patchCord16(flangeMixer, delay1);
AudioConnection          patchCord17(flangeMixer, 0, delayMixer, 0);
AudioConnection          patchCord18(delay1, 0, delayMixer, 1);
AudioConnection          patchCord19(delayMixer, freeverbs1);
AudioConnection          patchCord20(delayMixer, 0, freeverbMixerL, 0);
AudioConnection          patchCord21(delayMixer, 0, freeverbMixerR, 0);
AudioConnection          patchCord22(freeverbs1, 0, freeverbBiquadL, 0);
AudioConnection          patchCord23(freeverbs1, 1, freeverbBiquadR, 0);
AudioConnection          patchCord24(freeverbBiquadL, 0, freeverbMixerL, 1);
AudioConnection          patchCord25(freeverbBiquadR, 0, freeverbMixerR, 1);
AudioConnection          patchCord26(i2sIN, 0, ampI2sInL, 0);
AudioConnection          patchCord27(i2sIN, 0, mixerSWPeakLmInL, 1);
AudioConnection          patchCord28(i2sIN, 0, peakVelocity, 0);
AudioConnection          patchCord29(i2sIN, 1, ampI2sInR, 0);
AudioConnection          patchCord30(i2sIN, 1, mixerSWPeakLmInR, 1);
AudioConnection          patchCord31(usbIN, 0, ampUsbInL, 0);
AudioConnection          patchCord32(usbIN, 0, mixerSWPeakUsbInL, 1);
AudioConnection          patchCord33(usbIN, 1, ampUsbInR, 0);
AudioConnection          patchCord34(usbIN, 1, mixerSWPeakUsbInR, 1);
AudioConnection          patchCord35(ampI2sInR, 0, mixerSWPeakLmInR, 0);
AudioConnection          patchCord36(ampI2sInR, 0, mixerOutI2sR, 0);
AudioConnection          patchCord37(ampI2sInR, 0, mixerOutUsbR, 0);
AudioConnection          patchCord38(ampI2sInR, peakMixerLmR);
AudioConnection          patchCord39(ampI2sInL, 0, mixerSWPeakLmInL, 0);
AudioConnection          patchCord40(ampI2sInL, 0, mixerOutI2sL, 0);
AudioConnection          patchCord41(ampI2sInL, 0, mixerOutUsbL, 0);
AudioConnection          patchCord42(ampI2sInL, peakMixerLmL);
AudioConnection          patchCord43(ampUsbInR, 0, mixerSWPeakUsbInR, 0);
AudioConnection          patchCord44(ampUsbInR, 0, mixerOutI2sR, 1);
AudioConnection          patchCord45(ampUsbInR, 0, mixerOutUsbR, 1);
AudioConnection          patchCord46(ampUsbInR, peakMixerUsbR);
AudioConnection          patchCord47(ampUsbInL, 0, mixerSWPeakUsbInL, 0);
AudioConnection          patchCord48(ampUsbInL, 0, mixerOutI2sL, 1);
AudioConnection          patchCord49(ampUsbInL, 0, mixerOutUsbL, 1);
AudioConnection          patchCord50(ampUsbInL, peakMixerUsbL);
AudioConnection          patchCord51(ampInsOutL, peakMixerInsL);
AudioConnection          patchCord52(ampInsOutL, 0, mixerOutUsbL, 2);
AudioConnection          patchCord53(ampInsOutL, 0, mixerOutI2sL, 2);
AudioConnection          patchCord54(ampInsOutR, peakMixerInsR);
AudioConnection          patchCord55(ampInsOutR, 0, mixerOutUsbR, 2);
AudioConnection          patchCord56(ampInsOutR, 0, mixerOutI2sR, 2);
AudioConnection          patchCord57(mixerSWPeakUsbInL, peakUsbInL);
AudioConnection          patchCord58(mixerSWPeakUsbInR, peakUsbInR);
AudioConnection          patchCord59(mixerSWPeakLmInL, peakLmInL);
AudioConnection          patchCord60(mixerSWPeakLmInR, peakLmInR);
AudioConnection          patchCord61(mixerOutI2sL, ampMasterOutI2sL);
AudioConnection          patchCord62(mixerOutI2sL, 0, mixerSWPeakI2sL, 1);
AudioConnection          patchCord63(mixerOutI2sL, 0, mixerSWRmsI2sL, 1);
AudioConnection          patchCord64(mixerOutI2sR, ampMasterOutI2sR);
AudioConnection          patchCord65(mixerOutI2sR, 0, mixerSWPeakI2sR, 1);
AudioConnection          patchCord66(mixerOutI2sR, 0, mixerSWRmsI2sR, 1);
AudioConnection          patchCord67(mixerOutUsbR, ampMasterOutUsbR);
AudioConnection          patchCord68(mixerOutUsbR, 0, mixerSWPeakUsbR, 1);
AudioConnection          patchCord69(mixerOutUsbR, 0, mixerSWRmsUsbR, 1);
AudioConnection          patchCord70(mixerOutUsbL, ampMasterOutUsbL);
AudioConnection          patchCord71(mixerOutUsbL, 0, mixerSWPeakUsbL, 1);
AudioConnection          patchCord72(mixerOutUsbL, 0, mixerSWRmsUsbL, 1);
AudioConnection          patchCord73(ampMasterOutI2sL, 0, i2sOUT, 0);
AudioConnection          patchCord74(ampMasterOutI2sL, 0, mixerSWRmsI2sL, 0);
AudioConnection          patchCord75(ampMasterOutI2sL, 0, mixerSWPeakI2sL, 0);
AudioConnection          patchCord76(ampMasterOutI2sR, 0, i2sOUT, 1);
AudioConnection          patchCord77(ampMasterOutI2sR, 0, mixerSWPeakI2sR, 0);
AudioConnection          patchCord78(ampMasterOutI2sR, 0, mixerSWRmsI2sR, 0);
AudioConnection          patchCord79(ampMasterOutUsbL, 0, usbOUT, 0);
AudioConnection          patchCord80(ampMasterOutUsbL, 0, mixerSWPeakUsbL, 0);
AudioConnection          patchCord81(ampMasterOutUsbL, 0, mixerSWRmsUsbL, 0);
AudioConnection          patchCord82(ampMasterOutUsbR, 0, usbOUT, 1);
AudioConnection          patchCord83(ampMasterOutUsbR, 0, mixerSWPeakUsbR, 0);
AudioConnection          patchCord84(ampMasterOutUsbR, 0, mixerSWRmsUsbR, 0);
AudioConnection          patchCord85(mixerSWPeakI2sL, peakI2sL);
AudioConnection          patchCord86(mixerSWRmsI2sL, rmsI2sL);
AudioConnection          patchCord87(mixerSWPeakUsbL, peakUsbL);
AudioConnection          patchCord88(mixerSWPeakI2sR, peakI2sR);
AudioConnection          patchCord89(mixerSWPeakUsbR, peakUsbR);
AudioConnection          patchCord90(mixerSWRmsUsbR, rmsUsbR);
AudioConnection          patchCord91(mixerSWRmsUsbL, rmsUsbL);
AudioConnection          patchCord92(mixerSWRmsI2sR, rmsI2sR);
AudioControlSGTL5000     sgtl5000_1;     //xy=1499.5834312438965,339.1668577194214
// GUItool: end automatically generated code



