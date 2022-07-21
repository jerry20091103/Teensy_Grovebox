#include "AudioObjects.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthNoiseWhite     noise4; //xy=116,1124.272705078125
AudioSynthNoiseWhite     noise1;  //xy=123,574.9091186523438
AudioSynthNoiseWhite     noise2; //xy=123,754.727294921875
AudioSynthNoiseWhite     noise3; //xy=124,934.5454711914062
AudioSynthNoiseWhite     noise5; //xy=123,1338.0909423828125
AudioSynthNoiseWhite     noise0;         //xy=127,382.72759532928467
AudioSynthNoiseWhite     noise6; //xy=123,1511.8182373046875
AudioSynthNoiseWhite     noise7; //xy=124.00000381469727,1697.8182878494263
AudioSynthWaveform       waveform4_1;  //xy=137.99996948242188,1086.4545230865479
AudioSynthWaveform       waveform4_0; //xy=139.00000762939453,1048.363618850708
AudioSynthWaveform       waveform6_1; //xy=137.99996948242188,1471.9091911315918
AudioSynthWaveform       waveform6_0; //xy=139.00000762939453,1433.818286895752
AudioSynthWaveform       waveform0_0; //xy=144.0000457763672,310.4546604156494
AudioSynthWaveform       waveform3_1; //xy=141.9999771118164,898.5454940795898
AudioSynthWaveform       waveform5_1; //xy=140.99996948242188,1299.2727661132812
AudioSynthWaveform       waveform0_1; //xy=145.0000228881836,346.5454807281494
AudioSynthWaveform       waveform3_0; //xy=143.00001525878906,860.45458984375
AudioSynthWaveform       waveform1_0; //xy=145.00001907348633,499.54541969299316
AudioSynthWaveform       waveform5_0; //xy=142.00000762939453,1261.1818618774414
AudioSynthWaveform       waveform1_1; //xy=144.99998474121094,537.6362419128418
AudioSynthWaveform       waveform2_0; //xy=145.00000381469727,679.5454654693604
AudioSynthWaveform       waveform2_1; //xy=144.9999771118164,717.6362857818604
AudioSynthWaveform       waveform7_1; //xy=142.99996948242188,1659.9091300964355
AudioSynthWaveform       waveform7_0; //xy=144.00000762939453,1621.8182258605957
AudioMixer4              oscMixer4; //xy=291.99998474121094,1105.454433441162
AudioMixer4              oscMixer5; //xy=299.99998474121094,1324.2725887298584
AudioMixer4              oscMixer6; //xy=299.9999694824219,1499.9091567993164
AudioMixer4              oscMixer0;         //xy=305.00000762939453,365.54548263549805
AudioMixer4              oscMixer1; //xy=304.99998474121094,553.6362838745117
AudioMixer4              oscMixer3; //xy=303.9999694824219,922.5454635620117
AudioMixer4              oscMixer7; //xy=303.9999694824219,1684.9091606140137
AudioMixer4              oscMixer2; //xy=308.0000114440918,740.6362838745117
AudioSynthWavetable      wavetable5; //xy=417.5715637207031,1258.8959884643555
AudioSynthWavetable      wavetable6; //xy=423.5715637207031,1442.8961715698242
AudioSynthWavetable      wavetable7; //xy=432.5715675354004,1627.8961925506592
AudioSynthWavetable      wavetable3; //xy=440.5715637207031,870.1688995361328
AudioSynthWavetable      wavetable4; //xy=447.5715637207031,1047.1689567565918
AudioEffectEnvelope      ampEnvelope5; //xy=463,1315
AudioSynthWavetable      wavetable1; //xy=468.5715675354004,497.168909072876
AudioEffectEnvelope      ampEnvelope4; //xy=467,1105.1817626953125
AudioSynthWavetable      wavetable2; //xy=473.5715637207031,682.1688213348389
AudioEffectEnvelope      ampEnvelope0;      //xy=475.00001525878906,357.81818771362305
AudioEffectEnvelope      ampEnvelope3; //xy=474,921.4545288085938
AudioEffectEnvelope      ampEnvelope6; //xy=472,1489.9090576171875
AudioEffectEnvelope      ampEnvelope7; //xy=474.000057220459,1680.7273445129395
AudioEffectEnvelope      ampEnvelope2; //xy=478,739.6363525390625
AudioEffectEnvelope      ampEnvelope1; //xy=479.00001525878906,549.818193435669
AudioSynthWavetable      wavetable0;     //xy=487.5489692687988,301.4570827484131
AudioMixer4              voiceSwitch5; //xy=649.0000610351562,1267.1820640563965
AudioMixer4              voiceSwitch6; //xy=654.0000610351562,1455.1822471618652
AudioMixer4              voiceSwitch1; //xy=661.0000190734863,546.0908737182617
AudioMixer4              voiceSwitch2; //xy=661.0000190734863,712.0909233093262
AudioMixer4              voiceSwitch3; //xy=664.0000610351562,901.1819496154785
AudioMixer4              voiceSwitch4; //xy=665.0000610351562,1098.1819190979004
AudioMixer4              voiceSwitch0; //xy=668.0000152587891,349.0908718109131
AudioMixer4              voiceSwitch7; //xy=663.0000610351562,1638.182273864746
AudioMixer4              voiceMixer0_1; //xy=890.5714912414551,1349.895839691162
AudioMixer4              voiceMixer0_0;         //xy=893.5716705322266,616.8958797454834
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
AudioConnection          patchCord1(noise4, 0, oscMixer4, 2);
AudioConnection          patchCord2(noise1, 0, oscMixer1, 2);
AudioConnection          patchCord3(noise2, 0, oscMixer2, 2);
AudioConnection          patchCord4(noise3, 0, oscMixer3, 2);
AudioConnection          patchCord5(noise5, 0, oscMixer5, 2);
AudioConnection          patchCord6(noise0, 0, oscMixer0, 2);
AudioConnection          patchCord7(noise6, 0, oscMixer6, 2);
AudioConnection          patchCord8(noise7, 0, oscMixer7, 2);
AudioConnection          patchCord9(waveform4_1, 0, oscMixer4, 1);
AudioConnection          patchCord10(waveform4_0, 0, oscMixer4, 0);
AudioConnection          patchCord11(waveform6_1, 0, oscMixer6, 1);
AudioConnection          patchCord12(waveform6_0, 0, oscMixer6, 0);
AudioConnection          patchCord13(waveform0_0, 0, oscMixer0, 0);
AudioConnection          patchCord14(waveform3_1, 0, oscMixer3, 1);
AudioConnection          patchCord15(waveform5_1, 0, oscMixer5, 1);
AudioConnection          patchCord16(waveform0_1, 0, oscMixer0, 1);
AudioConnection          patchCord17(waveform3_0, 0, oscMixer3, 0);
AudioConnection          patchCord18(waveform1_0, 0, oscMixer1, 0);
AudioConnection          patchCord19(waveform5_0, 0, oscMixer5, 0);
AudioConnection          patchCord20(waveform1_1, 0, oscMixer1, 1);
AudioConnection          patchCord21(waveform2_0, 0, oscMixer2, 0);
AudioConnection          patchCord22(waveform2_1, 0, oscMixer2, 1);
AudioConnection          patchCord23(waveform7_1, 0, oscMixer7, 1);
AudioConnection          patchCord24(waveform7_0, 0, oscMixer7, 0);
AudioConnection          patchCord25(oscMixer4, ampEnvelope4);
AudioConnection          patchCord26(oscMixer5, ampEnvelope5);
AudioConnection          patchCord27(oscMixer6, ampEnvelope6);
AudioConnection          patchCord28(oscMixer0, ampEnvelope0);
AudioConnection          patchCord29(oscMixer1, ampEnvelope1);
AudioConnection          patchCord30(oscMixer3, ampEnvelope3);
AudioConnection          patchCord31(oscMixer7, ampEnvelope7);
AudioConnection          patchCord32(oscMixer2, ampEnvelope2);
AudioConnection          patchCord33(wavetable5, 0, voiceSwitch5, 0);
AudioConnection          patchCord34(wavetable6, 0, voiceSwitch6, 0);
AudioConnection          patchCord35(wavetable7, 0, voiceSwitch7, 0);
AudioConnection          patchCord36(wavetable3, 0, voiceSwitch3, 0);
AudioConnection          patchCord37(wavetable4, 0, voiceSwitch4, 0);
AudioConnection          patchCord38(ampEnvelope5, 0, voiceSwitch5, 1);
AudioConnection          patchCord39(wavetable1, 0, voiceSwitch1, 0);
AudioConnection          patchCord40(ampEnvelope4, 0, voiceSwitch4, 1);
AudioConnection          patchCord41(wavetable2, 0, voiceSwitch2, 0);
AudioConnection          patchCord42(ampEnvelope0, 0, voiceSwitch0, 1);
AudioConnection          patchCord43(ampEnvelope3, 0, voiceSwitch3, 1);
AudioConnection          patchCord44(ampEnvelope6, 0, voiceSwitch6, 1);
AudioConnection          patchCord45(ampEnvelope7, 0, voiceSwitch7, 1);
AudioConnection          patchCord46(ampEnvelope2, 0, voiceSwitch2, 1);
AudioConnection          patchCord47(ampEnvelope1, 0, voiceSwitch1, 1);
AudioConnection          patchCord48(wavetable0, 0, voiceSwitch0, 0);
AudioConnection          patchCord49(voiceSwitch5, 0, voiceMixer0_1, 1);
AudioConnection          patchCord50(voiceSwitch6, 0, voiceMixer0_1, 2);
AudioConnection          patchCord51(voiceSwitch1, 0, voiceMixer0_0, 1);
AudioConnection          patchCord52(voiceSwitch2, 0, voiceMixer0_0, 2);
AudioConnection          patchCord53(voiceSwitch3, 0, voiceMixer0_0, 3);
AudioConnection          patchCord54(voiceSwitch4, 0, voiceMixer0_1, 0);
AudioConnection          patchCord55(voiceSwitch0, 0, voiceMixer0_0, 0);
AudioConnection          patchCord56(voiceSwitch7, 0, voiceMixer0_1, 3);
AudioConnection          patchCord57(voiceMixer0_1, 0, voiceMixer1_0, 1);
AudioConnection          patchCord58(voiceMixer0_0, 0, voiceMixer1_0, 0);
AudioConnection          patchCord59(voiceMixer1_0, 0, freeverbMixerL, 0);
AudioConnection          patchCord60(voiceMixer1_0, 0, freeverbMixerR, 0);
AudioConnection          patchCord61(freeverbBiquadL, 0, freeverbMixerL, 1);
AudioConnection          patchCord62(freeverbBiquadR, 0, freeverbMixerR, 1);
AudioConnection          patchCord63(freeverbMixerL, ampInsOutL);
AudioConnection          patchCord64(freeverbMixerR, ampInsOutR);
AudioConnection          patchCord65(i2sIN, 0, ampI2sInL, 0);
AudioConnection          patchCord66(i2sIN, 0, mixerSWPeakLmInL, 1);
AudioConnection          patchCord67(i2sIN, 0, peakVelocity, 0);
AudioConnection          patchCord68(i2sIN, 1, ampI2sInR, 0);
AudioConnection          patchCord69(i2sIN, 1, mixerSWPeakLmInR, 1);
AudioConnection          patchCord70(usbIN, 0, ampUsbInL, 0);
AudioConnection          patchCord71(usbIN, 0, mixerSWPeakUsbInL, 1);
AudioConnection          patchCord72(usbIN, 1, ampUsbInR, 0);
AudioConnection          patchCord73(usbIN, 1, mixerSWPeakUsbInR, 1);
AudioConnection          patchCord74(ampI2sInR, 0, mixerSWPeakLmInR, 0);
AudioConnection          patchCord75(ampI2sInR, 0, mixerOutI2sR, 0);
AudioConnection          patchCord76(ampI2sInR, 0, mixerOutUsbR, 0);
AudioConnection          patchCord77(ampI2sInR, peakMixerLmR);
AudioConnection          patchCord78(ampI2sInL, 0, mixerSWPeakLmInL, 0);
AudioConnection          patchCord79(ampI2sInL, 0, mixerOutI2sL, 0);
AudioConnection          patchCord80(ampI2sInL, 0, mixerOutUsbL, 0);
AudioConnection          patchCord81(ampI2sInL, peakMixerLmL);
AudioConnection          patchCord82(ampUsbInR, 0, mixerSWPeakUsbInR, 0);
AudioConnection          patchCord83(ampUsbInR, 0, mixerOutI2sR, 1);
AudioConnection          patchCord84(ampUsbInR, 0, mixerOutUsbR, 1);
AudioConnection          patchCord85(ampUsbInR, peakMixerUsbR);
AudioConnection          patchCord86(ampUsbInL, 0, mixerSWPeakUsbInL, 0);
AudioConnection          patchCord87(ampUsbInL, 0, mixerOutI2sL, 1);
AudioConnection          patchCord88(ampUsbInL, 0, mixerOutUsbL, 1);
AudioConnection          patchCord89(ampUsbInL, peakMixerUsbL);
AudioConnection          patchCord90(ampInsOutL, peakMixerInsL);
AudioConnection          patchCord91(ampInsOutL, 0, mixerOutUsbL, 2);
AudioConnection          patchCord92(ampInsOutL, 0, mixerOutI2sL, 2);
AudioConnection          patchCord93(ampInsOutR, peakMixerInsR);
AudioConnection          patchCord94(ampInsOutR, 0, mixerOutUsbR, 2);
AudioConnection          patchCord95(ampInsOutR, 0, mixerOutI2sR, 2);
AudioConnection          patchCord96(mixerSWPeakUsbInL, peakUsbInL);
AudioConnection          patchCord97(mixerSWPeakUsbInR, peakUsbInR);
AudioConnection          patchCord98(mixerSWPeakLmInL, peakLmInL);
AudioConnection          patchCord99(mixerSWPeakLmInR, peakLmInR);
AudioConnection          patchCord100(mixerOutI2sL, ampMasterOutI2sL);
AudioConnection          patchCord101(mixerOutI2sL, 0, mixerSWPeakI2sL, 1);
AudioConnection          patchCord102(mixerOutI2sR, ampMasterOutI2sR);
AudioConnection          patchCord103(mixerOutI2sR, 0, mixerSWPeakI2sR, 1);
AudioConnection          patchCord104(mixerOutUsbR, ampMasterOutUsbR);
AudioConnection          patchCord105(mixerOutUsbR, 0, mixerSWPeakUsbR, 1);
AudioConnection          patchCord106(mixerOutUsbL, ampMasterOutUsbL);
AudioConnection          patchCord107(mixerOutUsbL, 0, mixerSWPeakUsbL, 1);
AudioConnection          patchCord108(ampMasterOutI2sL, 0, i2sOUT, 0);
AudioConnection          patchCord109(ampMasterOutI2sL, 0, mixerSWPeakI2sL, 0);
AudioConnection          patchCord110(ampMasterOutI2sR, 0, i2sOUT, 1);
AudioConnection          patchCord111(ampMasterOutI2sR, 0, mixerSWPeakI2sR, 0);
AudioConnection          patchCord112(ampMasterOutUsbL, 0, usbOUT, 0);
AudioConnection          patchCord113(ampMasterOutUsbL, 0, mixerSWPeakUsbL, 0);
AudioConnection          patchCord114(ampMasterOutUsbR, 0, usbOUT, 1);
AudioConnection          patchCord115(ampMasterOutUsbR, 0, mixerSWPeakUsbR, 0);
AudioConnection          patchCord116(mixerSWPeakI2sL, peakI2sL);
AudioConnection          patchCord117(mixerSWPeakI2sR, peakI2sR);
AudioConnection          patchCord118(mixerSWPeakUsbR, peakUsbR);
AudioConnection          patchCord119(mixerSWPeakUsbL, peakUsbL);
AudioControlSGTL5000     sgtl5000_1;     //xy=1400.583396911621,306.16686820983887
// GUItool: end automatically generated code





