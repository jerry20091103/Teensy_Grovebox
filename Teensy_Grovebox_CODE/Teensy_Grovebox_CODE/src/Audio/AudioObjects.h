#ifndef AUDIO_OBJECTS_H
#define AUDIO_OBJECTS_H

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
extern AudioSynthWaveform       waveform5_1; //xy=197.99996185302734,1340.2726669311523
extern AudioSynthWaveform       waveform5_0; //xy=199,1302.1817626953125
extern AudioSynthWaveform       waveform6_1; //xy=207.99996185302734,1517.9091415405273
extern AudioSynthWaveform       waveform6_0; //xy=209,1479.8182373046875
extern AudioSynthWaveform       waveform7_1; //xy=211.99996185302734,1705.9091415405273
extern AudioSynthWaveform       waveform7_0; //xy=213,1667.8182373046875
extern AudioSynthWaveform       waveform3_1; //xy=219.99996948242188,952.5454940795898
extern AudioSynthWaveform       waveform3_0; //xy=221.00000762939453,914.45458984375
extern AudioSynthWaveform       waveform4_1;  //xy=222.99996185302734,1123.4545516967773
extern AudioSynthWaveform       waveform2_0; //xy=224.99999618530273,714.5454654693604
extern AudioSynthWaveform       waveform2_1; //xy=224.99996948242188,752.6362857818604
extern AudioSynthWaveform       waveform4_0; //xy=224,1085.3636474609375
extern AudioSynthWaveform       waveform1_0; //xy=239,534.5454425811768
extern AudioSynthWaveform       waveform1_1; //xy=238.99997329711914,572.6362628936768
extern AudioSynthWaveform       waveform0_0; //xy=262.00004959106445,340.4546432495117
extern AudioSynthWaveform       waveform0_1; //xy=262.0000228881836,378.5454635620117
extern AudioSynthWavetable      wavetable5; //xy=417.5715637207031,1258.8959884643555
extern AudioMixer4              oscMixer2; //xy=420.00000762939453,755.6362838745117
extern AudioSynthWavetable      wavetable2; //xy=425.57157135009766,693.1688365936279
extern AudioMixer4              oscMixer5; //xy=423.99996185302734,1318.2725830078125
extern AudioSynthWavetable      wavetable6; //xy=423.5715637207031,1442.8961715698242
extern AudioSynthWavetable      wavetable7; //xy=432.5715675354004,1627.8961925506592
extern AudioMixer4              oscMixer6; //xy=433.99996185302734,1495.9090576171875
extern AudioSynthWavetable      wavetable3; //xy=440.5715637207031,870.1688995361328
extern AudioMixer4              oscMixer7; //xy=437.99996185302734,1683.9090576171875
extern AudioMixer4              oscMixer3; //xy=445.9999694824219,930.54541015625
extern AudioSynthWavetable      wavetable4; //xy=447.5715637207031,1047.1689567565918
extern AudioMixer4              oscMixer4; //xy=448.99996185302734,1101.4544677734375
extern AudioMixer4              oscMixer1; //xy=464.9999580383301,555.6362648010254
extern AudioSynthWavetable      wavetable1; //xy=468.5715675354004,497.168909072876
extern AudioSynthWavetable      wavetable0;     //xy=487.5489692687988,301.4570827484131
extern AudioMixer4              oscMixer0;         //xy=488.00000762939453,361.54546546936035
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
extern AudioControlSGTL5000     sgtl5000_1;     //xy=1499.5834312438965,339.1668577194214
// GUItool: end automatically generated code

#endif