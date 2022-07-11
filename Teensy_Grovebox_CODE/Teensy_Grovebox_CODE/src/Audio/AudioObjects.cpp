#include "AudioObjects.h"

// GUItool: begin automatically generated code
AudioSynthWavetable      wavetable0;     //xy=433.54896545410156,583.4569816589355
AudioSynthWaveform       waveform0; //xy=434.00000762939453,621.4545478820801
AudioSynthWaveform       waveform4; //xy=434,1035.45458984375
AudioSynthWavetable      wavetable4; //xy=434.57151794433594,998.1689014434814
AudioSynthWaveform       waveform3; //xy=436.0000305175781,927.4545555114746
AudioSynthWaveform       waveform1;      //xy=437.0000305175781,721.4545478820801
AudioSynthWaveform       waveform2; //xy=437.00000762939453,833.454553604126
AudioSynthWavetable      wavetable2; //xy=437.5715675354004,797.1688632965088
AudioSynthWavetable      wavetable1; //xy=439.57154083251953,684.1689052581787
AudioSynthWavetable      wavetable3; //xy=439.5715637207031,893.1688661575317
AudioSynthWavetable      wavetable5; //xy=440.5715637207031,1096.8959617614746
AudioSynthWaveform       waveform5; //xy=441,1131.45458984375
AudioSynthWavetable      wavetable6; //xy=441.5715637207031,1198.8959655761719
AudioSynthWaveform       waveform6; //xy=442.00000762939453,1235.4545602798462
AudioSynthWavetable      wavetable7; //xy=442.5715675354004,1295.8959636688232
AudioSynthWaveform       waveform7; //xy=444.00001525878906,1333.2727994918823
AudioMixer4              voiceSwitch4; //xy=669.0000610351562,1001.1819458007812
AudioMixer4              voiceSwitch2; //xy=673.0000152587891,816.090950012207
AudioMixer4              voiceSwitch5; //xy=672.0000610351562,1105.1820373535156
AudioMixer4              voiceSwitch6; //xy=672.0000610351562,1211.182041168213
AudioMixer4              voiceSwitch7; //xy=673.0000610351562,1306.1820449829102
AudioMixer4              voiceSwitch3; //xy=676.0000610351562,913.1819438934326
AudioMixer4              voiceSwitch1; //xy=678.0000152587891,707.0909042358398
AudioMixer4              voiceSwitch0; //xy=680.0000152587891,601.0909004211426
AudioMixer4              voiceMixer0_0;         //xy=884.5716323852539,784.8958778381348
AudioMixer4              voiceMixer0_1; //xy=885.5714988708496,1138.8958854675293
AudioMixer4              voiceMixer1_0; //xy=1096.793716430664,944.0072288513184
AudioFilterBiquad        freeverbBiquadL;        //xy=1361.7662887573242,995.4155788421631
AudioFilterBiquad        freeverbBiquadR; //xy=1362.7662811279297,1030.4155797958374
AudioMixer4              freeverbMixerL; //xy=1376.9755249023438,1095.7851486206055
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
AudioAnalyzePeak         peakMixerInsL; //xy=1900.9774322509766,922.409252166748
AudioAnalyzePeak         peakMixerInsR; //xy=1912.1997375488281,964.6315307617188
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
AudioMixer4              mixerSWPeakI2sL;         //xy=2552.583526611328,378.1668167114258
AudioMixer4              mixerSWPeakI2sR; //xy=2559.67440032959,531.1668014526367
AudioMixer4              mixerSWPeakUsbR;  //xy=2565.674430847168,929.9851341247559
AudioMixer4              mixerSWPeakUsbL;  //xy=2574.674705505371,720.1669902801514
AudioOutputI2S           i2sOUT;           //xy=2597.5834884643555,456.1668128967285
AudioOutputUSB           usbOUT;           //xy=2613.583396911621,832.1668071746826
AudioAnalyzePeak         peakI2sL;          //xy=2725.492706298828,377.1668291091919
AudioAnalyzePeak         peakI2sR;          //xy=2734.4929809570312,532.1669578552246
AudioAnalyzePeak         peakUsbR; //xy=2747.4927940368652,930.1670408248901
AudioAnalyzePeak         peakUsbL; //xy=2765.4929809570312,721.1670360565186
AudioConnection          patchCord1(wavetable0, 0, voiceSwitch0, 0);
AudioConnection          patchCord2(waveform0, 0, voiceSwitch0, 1);
AudioConnection          patchCord3(waveform4, 0, voiceSwitch4, 1);
AudioConnection          patchCord4(wavetable4, 0, voiceSwitch4, 0);
AudioConnection          patchCord5(waveform3, 0, voiceSwitch3, 1);
AudioConnection          patchCord6(waveform1, 0, voiceSwitch1, 1);
AudioConnection          patchCord7(waveform2, 0, voiceSwitch2, 1);
AudioConnection          patchCord8(wavetable2, 0, voiceSwitch2, 0);
AudioConnection          patchCord9(wavetable1, 0, voiceSwitch1, 0);
AudioConnection          patchCord10(wavetable3, 0, voiceSwitch3, 0);
AudioConnection          patchCord11(wavetable5, 0, voiceSwitch5, 0);
AudioConnection          patchCord12(waveform5, 0, voiceSwitch5, 1);
AudioConnection          patchCord13(wavetable6, 0, voiceSwitch6, 0);
AudioConnection          patchCord14(waveform6, 0, voiceSwitch6, 1);
AudioConnection          patchCord15(wavetable7, 0, voiceSwitch7, 0);
AudioConnection          patchCord16(waveform7, 0, voiceSwitch7, 1);
AudioConnection          patchCord17(voiceSwitch4, 0, voiceMixer0_1, 0);
AudioConnection          patchCord18(voiceSwitch2, 0, voiceMixer0_0, 2);
AudioConnection          patchCord19(voiceSwitch5, 0, voiceMixer0_1, 1);
AudioConnection          patchCord20(voiceSwitch6, 0, voiceMixer0_1, 2);
AudioConnection          patchCord21(voiceSwitch7, 0, voiceMixer0_1, 3);
AudioConnection          patchCord22(voiceSwitch3, 0, voiceMixer0_0, 3);
AudioConnection          patchCord23(voiceSwitch1, 0, voiceMixer0_0, 1);
AudioConnection          patchCord24(voiceSwitch0, 0, voiceMixer0_0, 0);
AudioConnection          patchCord25(voiceMixer0_0, 0, voiceMixer1_0, 0);
AudioConnection          patchCord26(voiceMixer0_1, 0, voiceMixer1_0, 1);
AudioConnection          patchCord27(voiceMixer1_0, 0, freeverbMixerL, 0);
AudioConnection          patchCord28(voiceMixer1_0, 0, freeverbMixerR, 0);
AudioConnection          patchCord29(freeverbBiquadL, 0, freeverbMixerL, 1);
AudioConnection          patchCord30(freeverbBiquadR, 0, freeverbMixerR, 1);
AudioConnection          patchCord31(freeverbMixerL, ampInsOutL);
AudioConnection          patchCord32(freeverbMixerR, ampInsOutR);
AudioConnection          patchCord33(i2sIN, 0, ampI2sInL, 0);
AudioConnection          patchCord34(i2sIN, 0, mixerSWPeakLmInL, 1);
AudioConnection          patchCord35(i2sIN, 0, peakVelocity, 0);
AudioConnection          patchCord36(i2sIN, 1, ampI2sInR, 0);
AudioConnection          patchCord37(i2sIN, 1, mixerSWPeakLmInR, 1);
AudioConnection          patchCord38(usbIN, 0, ampUsbInL, 0);
AudioConnection          patchCord39(usbIN, 0, mixerSWPeakUsbInL, 1);
AudioConnection          patchCord40(usbIN, 1, ampUsbInR, 0);
AudioConnection          patchCord41(usbIN, 1, mixerSWPeakUsbInR, 1);
AudioConnection          patchCord42(ampI2sInR, 0, mixerSWPeakLmInR, 0);
AudioConnection          patchCord43(ampI2sInR, 0, mixerOutI2sR, 0);
AudioConnection          patchCord44(ampI2sInR, 0, mixerOutUsbR, 0);
AudioConnection          patchCord45(ampI2sInR, peakMixerLmR);
AudioConnection          patchCord46(ampI2sInL, 0, mixerSWPeakLmInL, 0);
AudioConnection          patchCord47(ampI2sInL, 0, mixerOutI2sL, 0);
AudioConnection          patchCord48(ampI2sInL, 0, mixerOutUsbL, 0);
AudioConnection          patchCord49(ampI2sInL, peakMixerLmL);
AudioConnection          patchCord50(ampUsbInR, 0, mixerSWPeakUsbInR, 0);
AudioConnection          patchCord51(ampUsbInR, 0, mixerOutI2sR, 1);
AudioConnection          patchCord52(ampUsbInR, 0, mixerOutUsbR, 1);
AudioConnection          patchCord53(ampUsbInR, peakMixerUsbR);
AudioConnection          patchCord54(ampUsbInL, 0, mixerSWPeakUsbInL, 0);
AudioConnection          patchCord55(ampUsbInL, 0, mixerOutI2sL, 1);
AudioConnection          patchCord56(ampUsbInL, 0, mixerOutUsbL, 1);
AudioConnection          patchCord57(ampUsbInL, peakMixerUsbL);
AudioConnection          patchCord58(ampInsOutL, peakMixerInsL);
AudioConnection          patchCord59(ampInsOutL, 0, mixerOutUsbL, 2);
AudioConnection          patchCord60(ampInsOutL, 0, mixerOutI2sL, 2);
AudioConnection          patchCord61(ampInsOutR, peakMixerInsR);
AudioConnection          patchCord62(ampInsOutR, 0, mixerOutUsbR, 2);
AudioConnection          patchCord63(ampInsOutR, 0, mixerOutI2sR, 2);
AudioConnection          patchCord64(mixerSWPeakUsbInL, peakUsbInL);
AudioConnection          patchCord65(mixerSWPeakUsbInR, peakUsbInR);
AudioConnection          patchCord66(mixerSWPeakLmInL, peakLmInL);
AudioConnection          patchCord67(mixerSWPeakLmInR, peakLmInR);
AudioConnection          patchCord68(mixerOutI2sL, ampMasterOutI2sL);
AudioConnection          patchCord69(mixerOutI2sL, 0, mixerSWPeakI2sL, 1);
AudioConnection          patchCord70(mixerOutI2sR, ampMasterOutI2sR);
AudioConnection          patchCord71(mixerOutI2sR, 0, mixerSWPeakI2sR, 1);
AudioConnection          patchCord72(mixerOutUsbR, ampMasterOutUsbR);
AudioConnection          patchCord73(mixerOutUsbR, 0, mixerSWPeakUsbR, 1);
AudioConnection          patchCord74(mixerOutUsbL, ampMasterOutUsbL);
AudioConnection          patchCord75(mixerOutUsbL, 0, mixerSWPeakUsbL, 1);
AudioConnection          patchCord76(ampMasterOutI2sL, 0, i2sOUT, 0);
AudioConnection          patchCord77(ampMasterOutI2sL, 0, mixerSWPeakI2sL, 0);
AudioConnection          patchCord78(ampMasterOutI2sR, 0, i2sOUT, 1);
AudioConnection          patchCord79(ampMasterOutI2sR, 0, mixerSWPeakI2sR, 0);
AudioConnection          patchCord80(ampMasterOutUsbL, 0, usbOUT, 0);
AudioConnection          patchCord81(ampMasterOutUsbL, 0, mixerSWPeakUsbL, 0);
AudioConnection          patchCord82(ampMasterOutUsbR, 0, usbOUT, 1);
AudioConnection          patchCord83(ampMasterOutUsbR, 0, mixerSWPeakUsbR, 0);
AudioConnection          patchCord84(mixerSWPeakI2sL, peakI2sL);
AudioConnection          patchCord85(mixerSWPeakI2sR, peakI2sR);
AudioConnection          patchCord86(mixerSWPeakUsbR, peakUsbR);
AudioConnection          patchCord87(mixerSWPeakUsbL, peakUsbL);
AudioControlSGTL5000     sgtl5000_1;     //xy=1499.5834312438965,339.1668577194214
// GUItool: end automatically generated code



