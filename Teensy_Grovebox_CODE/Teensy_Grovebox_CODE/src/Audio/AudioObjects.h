#ifndef AUDIO_OBJECTS_H
#define AUDIO_OBJECTS_H

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
extern AudioSynthNoiseWhite     noise4; //xy=116,1124.272705078125
extern AudioSynthNoiseWhite     noise1;  //xy=123,574.9091186523438
extern AudioSynthNoiseWhite     noise2; //xy=123,754.727294921875
extern AudioSynthNoiseWhite     noise3; //xy=124,934.5454711914062
extern AudioSynthNoiseWhite     noise5; //xy=123,1338.0909423828125
extern AudioSynthNoiseWhite     noise0;         //xy=127,382.72759532928467
extern AudioSynthNoiseWhite     noise6; //xy=123,1511.8182373046875
extern AudioSynthNoiseWhite     noise7; //xy=124.00000381469727,1697.8182878494263
extern AudioSynthWaveform       waveform4_1;  //xy=137.99996948242188,1086.4545230865479
extern AudioSynthWaveform       waveform4_0; //xy=139.00000762939453,1048.363618850708
extern AudioSynthWaveform       waveform6_1; //xy=137.99996948242188,1471.9091911315918
extern AudioSynthWaveform       waveform6_0; //xy=139.00000762939453,1433.818286895752
extern AudioSynthWaveform       waveform0_0; //xy=144.0000457763672,310.4546604156494
extern AudioSynthWaveform       waveform3_1; //xy=141.9999771118164,898.5454940795898
extern AudioSynthWaveform       waveform5_1; //xy=140.99996948242188,1299.2727661132812
extern AudioSynthWaveform       waveform0_1; //xy=145.0000228881836,346.5454807281494
extern AudioSynthWaveform       waveform3_0; //xy=143.00001525878906,860.45458984375
extern AudioSynthWaveform       waveform1_0; //xy=145.00001907348633,499.54541969299316
extern AudioSynthWaveform       waveform5_0; //xy=142.00000762939453,1261.1818618774414
extern AudioSynthWaveform       waveform1_1; //xy=144.99998474121094,537.6362419128418
extern AudioSynthWaveform       waveform2_0; //xy=145.00000381469727,679.5454654693604
extern AudioSynthWaveform       waveform2_1; //xy=144.9999771118164,717.6362857818604
extern AudioSynthWaveform       waveform7_1; //xy=142.99996948242188,1659.9091300964355
extern AudioSynthWaveform       waveform7_0; //xy=144.00000762939453,1621.8182258605957
extern AudioMixer4              oscMixer4; //xy=291.99998474121094,1105.454433441162
extern AudioMixer4              oscMixer5; //xy=299.99998474121094,1324.2725887298584
extern AudioMixer4              oscMixer6; //xy=299.9999694824219,1499.9091567993164
extern AudioMixer4              oscMixer0;         //xy=305.00000762939453,365.54548263549805
extern AudioMixer4              oscMixer1; //xy=304.99998474121094,553.6362838745117
extern AudioMixer4              oscMixer3; //xy=303.9999694824219,922.5454635620117
extern AudioMixer4              oscMixer7; //xy=303.9999694824219,1684.9091606140137
extern AudioMixer4              oscMixer2; //xy=308.0000114440918,740.6362838745117
extern AudioSynthWavetable      wavetable5; //xy=417.5715637207031,1258.8959884643555
extern AudioSynthWavetable      wavetable6; //xy=423.5715637207031,1442.8961715698242
extern AudioSynthWavetable      wavetable7; //xy=432.5715675354004,1627.8961925506592
extern AudioSynthWavetable      wavetable3; //xy=440.5715637207031,870.1688995361328
extern AudioSynthWavetable      wavetable4; //xy=447.5715637207031,1047.1689567565918
extern AudioEffectEnvelope      ampEnvelope5; //xy=463,1315
extern AudioSynthWavetable      wavetable1; //xy=468.5715675354004,497.168909072876
extern AudioEffectEnvelope      ampEnvelope4; //xy=467,1105.1817626953125
extern AudioSynthWavetable      wavetable2; //xy=473.5715637207031,682.1688213348389
extern AudioEffectEnvelope      ampEnvelope0;      //xy=475.00001525878906,357.81818771362305
extern AudioEffectEnvelope      ampEnvelope3; //xy=474,921.4545288085938
extern AudioEffectEnvelope      ampEnvelope6; //xy=472,1489.9090576171875
extern AudioEffectEnvelope      ampEnvelope7; //xy=474.000057220459,1680.7273445129395
extern AudioEffectEnvelope      ampEnvelope2; //xy=478,739.6363525390625
extern AudioEffectEnvelope      ampEnvelope1; //xy=479.00001525878906,549.818193435669
extern AudioSynthWavetable      wavetable0;     //xy=487.5489692687988,301.4570827484131
extern AudioMixer4              voiceSwitch5; //xy=649.0000610351562,1267.1820640563965
extern AudioMixer4              voiceSwitch6; //xy=654.0000610351562,1455.1822471618652
extern AudioMixer4              voiceSwitch1; //xy=661.0000190734863,546.0908737182617
extern AudioMixer4              voiceSwitch2; //xy=661.0000190734863,712.0909233093262
extern AudioMixer4              voiceSwitch3; //xy=664.0000610351562,901.1819496154785
extern AudioMixer4              voiceSwitch4; //xy=665.0000610351562,1098.1819190979004
extern AudioMixer4              voiceSwitch0; //xy=668.0000152587891,349.0908718109131
extern AudioMixer4              voiceSwitch7; //xy=663.0000610351562,1638.182273864746
extern AudioMixer4              voiceMixer0_1; //xy=890.5714912414551,1349.895839691162
extern AudioMixer4              voiceMixer0_0;         //xy=893.5716705322266,616.8958797454834
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
extern AudioControlSGTL5000     sgtl5000_1;     //xy=1400.583396911621,306.16686820983887
// GUItool: end automatically generated code
#endif