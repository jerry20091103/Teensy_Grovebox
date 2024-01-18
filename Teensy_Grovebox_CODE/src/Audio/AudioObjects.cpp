#include "AudioObjects.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlayClip            playClip6; //xy=401.2000541687012,2821.2003049850464
AudioPlayClip            playClip1; //xy=410.20009994506836,1123.200029373169
AudioPlayClip            playClip4; //xy=406.20006561279297,2142.199864387512
AudioPlayClip            playClip2; //xy=409.2000617980957,1461.2001008987427
AudioPlayClip            playClip5; //xy=412.20006942749023,2496.200406074524
AudioPlayClip            playClip3; //xy=418.20006561279297,1806.2003631591797
AudioPlayClip            playClip7; //xy=414.2000541687012,3173.2003240585327
AudioPlayClip            playClip0;      //xy=428.2001190185547,805.2001457214355
AudioAmplifier           clipAmp4; //xy=541.4286117553711,2121.2857990264893
AudioSynthNoiseWhite     noise4;         //xy=542.9999885559082,2084.4999465942383
AudioAmplifier           clipAmp6; //xy=542.428581237793,2809.428508758545
AudioAmplifier           clipAmp3; //xy=551.5714645385742,1781.4286155700684
AudioSynthWaveform       lfo4_1;         //xy=549.9999885559082,2209.4999465942383
AudioAmplifier           clipAmp2; //xy=553.285758972168,1451.571494102478
AudioSynthNoiseWhite     noise7;         //xy=547.9999885559082,3113.50008392334
AudioSynthWaveform       lfo4_0;         //xy=551.9999885559082,2160.4999465942383
AudioAmplifier           clipAmp5; //xy=552.428581237793,2483.285803794861
AudioAmplifier           clipAmp7; //xy=550.428581237793,3148.571336746216
AudioAmplifier           clipAmp1; //xy=559.4286117553711,1115.285966873169
AudioSynthNoiseWhite     noise3;         //xy=556.9999885559082,1742.5000629425049
AudioSynthNoiseWhite     noise6;         //xy=553.9999885559082,2772.500078678131
AudioSynthNoiseWhite     noise2;         //xy=559.9999885559082,1415.4999961853027
AudioSynthWaveform       waveform4_1;    //xy=558.9999885559082,2048.500068664551
AudioSynthWaveform       lfo6_1;         //xy=555.9999885559082,2898.5000801086426
AudioSynthWaveform       lfo6_0;         //xy=556.9999885559082,2849.5000801086426
AudioSynthWaveform       lfo7_1;         //xy=555.9999885559082,3238.50008392334
AudioSynthWaveform       lfo7_0;         //xy=556.9999885559082,3189.50008392334
AudioSynthNoiseWhite     noise1;         //xy=566.9999771118164,1076.5000305175781
AudioSynthNoiseWhite     noise5;         //xy=561.9999885559082,2444.499952316284
AudioSynthWaveform       waveform4_0;    //xy=563.9999771118164,2012.5000305175781
AudioSynthWaveform       lfo5_0;         //xy=561.9999885559082,2525.4999532699585
AudioSynthWaveform       lfo2_1;         //xy=565.9999885559082,1548.4999980926514
AudioSynthWaveform       lfo5_1;         //xy=561.9999771118164,2568.5000314712524
AudioSynthWaveform       lfo2_0;         //xy=566.9999885559082,1499.4999980926514
AudioSynthWaveform       lfo3_0;         //xy=568.9999885559082,1831.5000648498535
AudioAmplifier           clipAmp0;           //xy=573.4286117553711,796.5717277526855
AudioSynthWaveform       lfo3_1;         //xy=569.9999771118164,1869.5000305175781
AudioSynthNoiseWhite     noise0;         //xy=575.9999771118164,757.5000305175781
AudioSynthWaveform       waveform7_1;    //xy=566.9999885559082,3075.50008392334
AudioSynthWaveform       waveform6_1;    //xy=568.9999885559082,2732.500078678131
AudioSynthWaveform       waveform7_0;    //xy=567.9999885559082,3037.50008392334
AudioSynthWaveform       waveform6_0;    //xy=569.9999885559082,2694.500078678131
AudioSynthWaveform       waveform3_1;    //xy=574.9999885559082,1706.5000629425049
AudioSynthWaveform       waveform3_0;    //xy=575.9999885559082,1668.5000629425049
AudioSynthWaveform       lfo1_1;         //xy=577.9999771118164,1216.5000305175781
AudioSynthWaveform       lfo1_0;         //xy=579.9999771118164,1167.5000305175781
AudioSynthWaveform       waveform2_0;    //xy=581.9999885559082,1340.4999961853027
AudioSynthWaveform       waveform2_1;    //xy=581.9999885559082,1378.4999961853027
AudioSynthWaveform       lfo0_1;         //xy=583.9999771118164,884.5000305175781
AudioSynthWaveform       lfo0_0;         //xy=584.9999771118164,836.5000305175781
AudioSynthWaveform       waveform5_1;    //xy=579.9999885559082,2406.499952316284
AudioSynthWaveform       waveform5_0;    //xy=580.9999885559082,2368.499952316284
AudioSynthWaveform       waveform1_0;    //xy=588.9999771118164,1000.5000305175781
AudioSynthWaveform       waveform1_1;    //xy=588.9999771118164,1038.5000305175781
AudioSynthWaveform       waveform0_0;    //xy=592.9999771118164,685.5000305175781
AudioSynthWaveform       waveform0_1;    //xy=593.9999771118164,721.5000305175781
AudioRecordSample        lfoSample4_1; //xy=712.9999847412109,2201.0000381469727
AudioRecordSample        lfoSample4_0; //xy=713.9999847412109,2153.0000381469727
AudioMixer4              oscMixer4;      //xy=718.9999847412109,2071.499969482422
AudioRecordSample        lfoSample7_1; //xy=719.9999847412109,3225.0000381469727
AudioRecordSample        lfoSample7_0; //xy=720.9999847412109,3177.0000381469727
AudioRecordSample        lfoSample6_1; //xy=722.9999847412109,2888.0000381469727
AudioRecordSample        lfoSample6_0; //xy=723.9999847412109,2840.0000381469727
AudioRecordSample        lfoSample3_1; //xy=732.9999847412109,1855.0000381469727
AudioRecordSample        lfoSample3_0; //xy=733.9999847412109,1807.0000381469727
AudioMixer4              oscMixer3;      //xy=734.9999771118164,1738.5000305175781
AudioMixer4              oscMixer7;      //xy=731.9999885559082,3093.500141143799
AudioRecordSample        lfoSample2_1; //xy=739.9999847412109,1533.0000381469727
AudioRecordSample        lfoSample5_1; //xy=735.9999847412109,2565.0000381469727
AudioRecordSample        lfoSample2_0; //xy=740.9999847412109,1485.0000381469727
AudioRecordSample        lfoSample5_0; //xy=736.9999847412109,2517.0000381469727
AudioMixer4              oscMixer6;      //xy=736.9999923706055,2758.500123977661
AudioMixer4              oscMixer2;      //xy=743.0000152587891,1399.5000648498535
AudioRecordSample        lfoSample0_1; //xy=748.9999923706055,886.0000495910645
AudioMixer4              oscMixer1;      //xy=748.9999771118164,1054.5000305175781
AudioRecordSample        lfoSample0_0;        //xy=749.9999923706055,838.0000495910645
AudioMixer4              oscMixer5;      //xy=745.0000495910645,2419.500108718872
AudioMixer4              oscMixer0;      //xy=753.9999771118164,740.5000305175781
AudioRecordSample        lfoSample1_1; //xy=756.9999847412109,1213.0000381469727
AudioRecordSample        lfoSample1_0; //xy=757.9999847412109,1165.0000381469727
AudioSynthWaveformDc     envDc4;         //xy=883.9999771118164,2171.500030517578
AudioSynthWaveformDc     envDc7;         //xy=892.9999771118164,3192.500030517578
AudioSynthWaveformDc     envDc6;         //xy=894.9999771118164,2856.500030517578
AudioSynthWaveformDc     envDc0;         //xy=903.9999771118164,854.5000305175781
AudioSynthWaveformDc     envDc5;         //xy=898.9999771118164,2530.500030517578
AudioFilterLadder        ladder1;        //xy=907.9999771118164,1055.5000305175781
AudioSynthWaveformDc     envDc1;         //xy=907.9999771118164,1189.5000305175781
AudioFilterLadder        ladder4;        //xy=905.9999771118164,2066.500030517578
AudioFilterLadder        ladder2;        //xy=908.9999771118164,1403.5000305175781
AudioSynthWaveformDc     envDc2;         //xy=908.9999771118164,1501.5000305175781
AudioSynthWaveformDc     envDc3;         //xy=910.9999771118164,1825.5000305175781
AudioFilterLadder        ladder6;        //xy=907.9999771118164,2752.500030517578
AudioFilterLadder        ladder7;        //xy=906.9999771118164,3091.500030517578
AudioFilterLadder        ladder3;        //xy=915.9999771118164,1734.5000305175781
AudioFilterLadder        ladder0;        //xy=923.9999771118164,727.5000305175781
AudioFilterLadder        ladder5;        //xy=924.9999771118164,2419.500030517578
AudioEffectEnvelope      envelope4_0;    //xy=1040.9999771118164,2147.500030517578
AudioEffectEnvelope      envelope4_1;    //xy=1040.9999771118164,2189.500030517578
AudioEffectEnvelope      envelope6_0;    //xy=1049.9999771118164,2834.500030517578
AudioEffectEnvelope      envelope6_1;    //xy=1049.9999771118164,2876.500030517578
AudioEffectEnvelope      envelope7_0;    //xy=1049.9999771118164,3175.500030517578
AudioEffectEnvelope      envelope7_1;    //xy=1049.9999771118164,3217.500030517578
AudioEffectEnvelope      envelope5_0;    //xy=1055.9999771118164,2514.500030517578
AudioEffectEnvelope      envelope5_1;    //xy=1055.9999771118164,2556.500030517578
AudioEffectEnvelope      envelope2_0;    //xy=1066.9999771118164,1477.5000305175781
AudioEffectEnvelope      envelope2_1;    //xy=1066.9999771118164,1520.5000305175781
AudioEffectEnvelope      envelope3_0;    //xy=1066.9999771118164,1803.5000305175781
AudioEffectEnvelope      envelope3_1;    //xy=1066.9999771118164,1845.5000305175781
AudioEffectEnvelope      envelope1_0;    //xy=1071.9999771118164,1164.5000305175781
AudioEffectEnvelope      envelope1_1;    //xy=1071.9999771118164,1207.5000305175781
AudioEffectEnvelope      envelope0_0;    //xy=1076.9999771118164,833.5000305175781
AudioEffectEnvelope      envelope0_1;    //xy=1076.9999771118164,876.5000305175781
AudioEffectEnvelope      ampEnvelope6;   //xy=1084.9999771118164,2717.500030517578
AudioEffectEnvelope      ampEnvelope1;   //xy=1104.9999771118164,1038.5000305175781
AudioEffectEnvelope      ampEnvelope7;   //xy=1096.9999771118164,3043.500030517578
AudioEffectEnvelope      ampEnvelope4;   //xy=1101.9999771118164,2042.5000305175781
AudioEffectEnvelope      ampEnvelope0;   //xy=1115.9999771118164,727.5000305175781
AudioSynthWavetable      wavetable6;     //xy=1112.9999771118164,2632.500030517578
AudioEffectEnvelope      ampEnvelope2;   //xy=1119.9999771118164,1370.5000305175781
AudioSynthWavetable      wavetable2;     //xy=1120.9999771118164,1308.5000305175781
AudioEffectEnvelope      ampEnvelope3;   //xy=1119.9999771118164,1703.5000305175781
AudioEffectEnvelope      ampEnvelope5;   //xy=1117.9999771118164,2375.500030517578
AudioSynthWavetable      wavetable7;     //xy=1115.9999771118164,2981.500030517578
AudioSynthWavetable      wavetable3;     //xy=1121.9999771118164,1629.5000305175781
AudioSynthWavetable      wavetable4;     //xy=1123.9999771118164,1966.5000305175781
AudioSynthWavetable      wavetable1;     //xy=1136.9999771118164,986.5000305175781
AudioSynthWavetable      wavetable0;     //xy=1138.9999771118164,661.5000305175781
AudioSynthWavetable      wavetable5;     //xy=1146.9999771118164,2311.500030517578
AudioRecordSample        envSample4_0; //xy=1248.999984741211,2149.0000381469727
AudioRecordSample        envSample4_1; //xy=1248.999984741211,2192.00003862381
AudioRecordSample        envSample5_0; //xy=1253.999984741211,2507.0000381469727
AudioRecordSample        envSample5_1; //xy=1253.999984741211,2550.00003862381
AudioRecordSample        envSample7_0; //xy=1251.999984741211,3169.0000381469727
AudioRecordSample        envSample7_1; //xy=1251.999984741211,3212.00003862381
AudioRecordSample        envSample6_0; //xy=1260.999984741211,2829.0000381469727
AudioRecordSample        envSample6_1; //xy=1260.999984741211,2872.00003862381
AudioRecordSample        envSample3_0; //xy=1275.999984741211,1802.0000381469727
AudioRecordSample        envSample3_1; //xy=1275.999984741211,1845.0000386238098
AudioRecordSample        envSample2_0; //xy=1281.999984741211,1478.0000381469727
AudioRecordSample        envSample2_1; //xy=1281.999984741211,1521.0000386238098
AudioRecordSample        envSample0_0;        //xy=1286,831.0000495910645
AudioRecordSample        envSample0_1; //xy=1286,874.0000500679016
AudioRecordSample        envSample1_0; //xy=1284.999984741211,1162.0000381469727
AudioRecordSample        envSample1_1; //xy=1284.999984741211,1205.0000386238098
AudioMixer4              voiceSwitch6;   //xy=1284.9999771118164,2688.500030517578
AudioRecordSample        ampEnvSample4; //xy=1287.999984741211,2078.0000381469727
AudioRecordSample        ampEnvSample6; //xy=1286.999984741211,2752.0000381469727
AudioMixer4              voiceSwitch4;   //xy=1293.9999771118164,2018.5000305175781
AudioMixer4              voiceSwitch7;   //xy=1289.9999771118164,3019.500030517578
AudioMixer4              voiceSwitch2;   //xy=1296.9999771118164,1362.5000305175781
AudioRecordSample        ampEnvSample7; //xy=1293.999984741211,3077.0000381469727
AudioRecordSample        ampEnvSample2; //xy=1301.999984741211,1422.0000381469727
AudioRecordSample        ampEnvSample3; //xy=1302.999984741211,1749.0000381469727
AudioMixer4              voiceSwitch1;   //xy=1306.9999771118164,1044.5000305175781
AudioRecordSample        ampEnvSample5; //xy=1301.999984741211,2416.0000381469727
AudioMixer4              voiceSwitch3;   //xy=1304.9999771118164,1691.5000305175781
AudioMixer4              voiceSwitch5;   //xy=1302.9999771118164,2355.500030517578
AudioRecordSample        ampEnvSample1; //xy=1307.999984741211,1109.0000381469727
AudioRecordSample        ampEnvSample0;        //xy=1314,772.0000486373901
AudioMixer4              voiceSwitch0;   //xy=1318.9999771118164,709.5000305175781
AudioMixer4              voiceMixer0_0;  //xy=1556.9999771118164,1169.5000305175781
AudioMixer4              voiceMixer0_1;  //xy=1558.9999771118164,2510.500030517578
AudioMixer4              voiceMixer1_0;  //xy=1699.9999771118164,1872.5000305175781
AudioFilterBiquad        freeverbBiquadL; //xy=2024.9999771118164,1548.5000305175781
AudioFilterBiquad        freeverbBiquadR; //xy=2025.9999771118164,1583.5000305175781
AudioMixer4              freeverbMixerL; //xy=2039.9999771118164,1648.5000305175781
AudioMixer4              freeverbMixerR; //xy=2040.9999771118164,1715.5000305175781
AudioInputI2S            i2sIN;          //xy=2090.9999771118164,1024.5000305175781
#ifndef DEBUG
AudioInputUSB            usbIN;          //xy=2098.9999771118164,1282.5000305175781
#else
AudioInputSPDIF3    usbIN;
#endif
AudioAmplifier           ampI2sInR;      //xy=2252.9999771118164,1046.5000305175781
AudioAmplifier           ampI2sInL;      //xy=2255.9999771118164,1006.5000305175781
AudioAmplifier           ampUsbInR;      //xy=2257.9999771118164,1302.5000305175781
AudioAmplifier           ampUsbInL;      //xy=2260.9999771118164,1262.5000305175781
AudioAnalyzePeak         peakVelocity;   //xy=2283.9999771118164,791.5000305175781
AudioAmplifier           ampInsOutL;     //xy=2403.9999771118164,1606.5000305175781
AudioAmplifier           ampInsOutR;     //xy=2403.9999771118164,1647.5000305175781
AudioMixer4              mixerSWPeakUsbInL; //xy=2427.9999771118164,1129.5000305175781
AudioMixer4              mixerSWPeakUsbInR; //xy=2429.9999771118164,1202.5000305175781
AudioMixer4              mixerSWPeakLmInL; //xy=2439.9999771118164,863.5000305175781
AudioMixer4              mixerSWPeakLmInR; //xy=2441.9999771118164,936.5000305175781
AudioAnalyzePeak         peakMixerInsL;  //xy=2563.9999771118164,1475.5000305175781
AudioAnalyzePeak         peakMixerInsR;  //xy=2575.9999771118164,1517.5000305175781
AudioAnalyzePeak         peakLmInL;      //xy=2622.9999771118164,860.5000305175781
AudioAnalyzePeak         peakLmInR;      //xy=2624.9999771118164,936.5000305175781
AudioAnalyzePeak         peakUsbInL;     //xy=2631.9999771118164,1130.5000305175781
AudioAnalyzePeak         peakUsbInR;     //xy=2631.9999771118164,1199.5000305175781
AudioMixer4              mixerClip1;         //xy=2700.0000190734863,716.2000617980957
AudioAnalyzePeak         peakMixerLmR;   //xy=2795.9999771118164,883.5000305175781
AudioAnalyzePeak         peakMixerLmL;   //xy=2796.9999771118164,843.5000305175781
AudioMixer4              mixerOutI2sL;   //xy=2802.9999771118164,975.5000305175781
AudioMixer4              mixerOutI2sR;   //xy=2804.9999771118164,1056.5000305175781
AudioAnalyzePeak         peakMixerUsbL;  //xy=2804.9999771118164,1210.5000305175781
AudioAnalyzePeak         peakMixerUsbR;  //xy=2805.9999771118164,1252.5000305175781
AudioMixer4              mixerOutUsbR;   //xy=2808.9999771118164,1431.5000305175781
AudioMixer4              mixerOutUsbL;   //xy=2809.9999771118164,1342.5000305175781
AudioRecordClip          clip1;          //xy=2849.0000228881836,716.2001819610596
AudioAnalyzePeak         peakClip1;          //xy=2865.000030517578,665.2000350952148
AudioAmplifier           ampMasterOutI2sL; //xy=2994.9999771118164,982.5000305175781
AudioAmplifier           ampMasterOutI2sR; //xy=2998.9999771118164,1052.5000305175781
AudioAmplifier           ampMasterOutUsbL; //xy=3019.9999771118164,1354.5000305175781
AudioAmplifier           ampMasterOutUsbR; //xy=3023.9999771118164,1416.5000305175781
AudioMixer4              mixerSWPeakI2sL; //xy=3219.9999771118164,917.5000495910645
AudioMixer4              mixerSWPeakI2sR; //xy=3222.9999771118164,1101.5000534057617
AudioMixer4              mixerSWPeakUsbR; //xy=3228.9999771118164,1482.5000305175781
AudioMixer4              mixerSWPeakUsbL; //xy=3237.9999771118164,1273.5000305175781
AudioOutputI2S           i2sOUT;         //xy=3263.9999771118164,978.5000514984131
#ifndef DEBUG
AudioOutputUSB           usbOUT;         //xy=3276.9999771118164,1385.5000305175781
#else
AudioOutputSPDIF3        usbOUT;
#endif
AudioAnalyzePeak         peakI2sL;       //xy=3392.9999809265137,917.5000514984131
AudioAnalyzePeak         peakI2sR;       //xy=3401.9999771118164,1100.5000534057617
AudioAnalyzePeak         peakUsbR;       //xy=3410.9999771118164,1483.5000305175781
AudioAnalyzePeak         peakUsbL;       //xy=3428.9999771118164,1274.5000305175781
AudioConnection          patchCord1(playClip6, 0, voiceSwitch6, 2);
AudioConnection          patchCord2(playClip6, clipAmp6);
AudioConnection          patchCord3(playClip1, 0, voiceSwitch1, 2);
AudioConnection          patchCord4(playClip1, clipAmp1);
AudioConnection          patchCord5(playClip4, 0, voiceSwitch4, 2);
AudioConnection          patchCord6(playClip4, clipAmp4);
AudioConnection          patchCord7(playClip2, 0, voiceSwitch2, 2);
AudioConnection          patchCord8(playClip2, clipAmp2);
AudioConnection          patchCord9(playClip5, 0, voiceSwitch5, 2);
AudioConnection          patchCord10(playClip5, clipAmp5);
AudioConnection          patchCord11(playClip3, 0, voiceSwitch3, 2);
AudioConnection          patchCord12(playClip3, clipAmp3);
AudioConnection          patchCord13(playClip7, 0, voiceSwitch7, 2);
AudioConnection          patchCord14(playClip7, clipAmp7);
AudioConnection          patchCord15(playClip0, 0, voiceSwitch0, 2);
AudioConnection          patchCord16(playClip0, clipAmp0);
AudioConnection          patchCord17(clipAmp4, 0, oscMixer4, 3);
AudioConnection          patchCord18(noise4, 0, oscMixer4, 2);
AudioConnection          patchCord19(clipAmp6, 0, oscMixer6, 3);
AudioConnection          patchCord20(clipAmp3, 0, oscMixer3, 3);
AudioConnection          patchCord21(lfo4_1, lfoSample4_1);
AudioConnection          patchCord22(clipAmp2, 0, oscMixer2, 3);
AudioConnection          patchCord23(noise7, 0, oscMixer7, 2);
AudioConnection          patchCord24(lfo4_0, lfoSample4_0);
AudioConnection          patchCord25(clipAmp5, 0, oscMixer5, 3);
AudioConnection          patchCord26(clipAmp7, 0, oscMixer7, 3);
AudioConnection          patchCord27(clipAmp1, 0, oscMixer1, 3);
AudioConnection          patchCord28(noise3, 0, oscMixer3, 2);
AudioConnection          patchCord29(noise6, 0, oscMixer6, 2);
AudioConnection          patchCord30(noise2, 0, oscMixer2, 2);
AudioConnection          patchCord31(waveform4_1, 0, oscMixer4, 1);
AudioConnection          patchCord32(lfo6_1, lfoSample6_1);
AudioConnection          patchCord33(lfo6_0, lfoSample6_0);
AudioConnection          patchCord34(lfo7_1, lfoSample7_1);
AudioConnection          patchCord35(lfo7_0, lfoSample7_0);
AudioConnection          patchCord36(noise1, 0, oscMixer1, 2);
AudioConnection          patchCord37(noise5, 0, oscMixer5, 2);
AudioConnection          patchCord38(waveform4_0, 0, oscMixer4, 0);
AudioConnection          patchCord39(lfo5_0, lfoSample5_0);
AudioConnection          patchCord40(lfo2_1, lfoSample2_1);
AudioConnection          patchCord41(lfo5_1, lfoSample5_1);
AudioConnection          patchCord42(lfo2_0, lfoSample2_0);
AudioConnection          patchCord43(lfo3_0, lfoSample3_0);
AudioConnection          patchCord44(clipAmp0, 0, oscMixer0, 3);
AudioConnection          patchCord45(lfo3_1, lfoSample3_1);
AudioConnection          patchCord46(noise0, 0, oscMixer0, 2);
AudioConnection          patchCord47(waveform7_1, 0, oscMixer7, 1);
AudioConnection          patchCord48(waveform6_1, 0, oscMixer6, 1);
AudioConnection          patchCord49(waveform7_0, 0, oscMixer7, 0);
AudioConnection          patchCord50(waveform6_0, 0, oscMixer6, 0);
AudioConnection          patchCord51(waveform3_1, 0, oscMixer3, 1);
AudioConnection          patchCord52(waveform3_0, 0, oscMixer3, 0);
AudioConnection          patchCord53(lfo1_1, lfoSample1_1);
AudioConnection          patchCord54(lfo1_0, lfoSample1_0);
AudioConnection          patchCord55(waveform2_0, 0, oscMixer2, 0);
AudioConnection          patchCord56(waveform2_1, 0, oscMixer2, 1);
AudioConnection          patchCord57(lfo0_1, lfoSample0_1);
AudioConnection          patchCord58(lfo0_0, lfoSample0_0);
AudioConnection          patchCord59(waveform5_1, 0, oscMixer5, 1);
AudioConnection          patchCord60(waveform5_0, 0, oscMixer5, 0);
AudioConnection          patchCord61(waveform1_0, 0, oscMixer1, 0);
AudioConnection          patchCord62(waveform1_1, 0, oscMixer1, 1);
AudioConnection          patchCord63(waveform0_0, 0, oscMixer0, 0);
AudioConnection          patchCord64(waveform0_1, 0, oscMixer0, 1);
AudioConnection          patchCord65(oscMixer4, 0, ladder4, 0);
AudioConnection          patchCord66(oscMixer3, 0, ladder3, 0);
AudioConnection          patchCord67(oscMixer7, 0, ladder7, 0);
AudioConnection          patchCord68(oscMixer6, 0, ladder6, 0);
AudioConnection          patchCord69(oscMixer2, 0, ladder2, 0);
AudioConnection          patchCord70(oscMixer1, 0, ladder1, 0);
AudioConnection          patchCord71(oscMixer5, 0, ladder5, 0);
AudioConnection          patchCord72(oscMixer0, 0, ladder0, 0);
AudioConnection          patchCord73(envDc4, envelope4_0);
AudioConnection          patchCord74(envDc4, envelope4_1);
AudioConnection          patchCord75(envDc7, envelope7_0);
AudioConnection          patchCord76(envDc7, envelope7_1);
AudioConnection          patchCord77(envDc6, envelope6_0);
AudioConnection          patchCord78(envDc6, envelope6_1);
AudioConnection          patchCord79(envDc0, envelope0_0);
AudioConnection          patchCord80(envDc0, envelope0_1);
AudioConnection          patchCord81(envDc5, envelope5_0);
AudioConnection          patchCord82(envDc5, envelope5_1);
AudioConnection          patchCord83(ladder1, ampEnvelope1);
AudioConnection          patchCord84(envDc1, envelope1_0);
AudioConnection          patchCord85(envDc1, envelope1_1);
AudioConnection          patchCord86(ladder4, ampEnvelope4);
AudioConnection          patchCord87(ladder2, ampEnvelope2);
AudioConnection          patchCord88(envDc2, envelope2_0);
AudioConnection          patchCord89(envDc2, envelope2_1);
AudioConnection          patchCord90(envDc3, envelope3_0);
AudioConnection          patchCord91(envDc3, envelope3_1);
AudioConnection          patchCord92(ladder6, ampEnvelope6);
AudioConnection          patchCord93(ladder7, ampEnvelope7);
AudioConnection          patchCord94(ladder3, ampEnvelope3);
AudioConnection          patchCord95(ladder0, ampEnvelope0);
AudioConnection          patchCord96(ladder5, ampEnvelope5);
AudioConnection          patchCord97(envelope4_0, envSample4_0);
AudioConnection          patchCord98(envelope4_1, envSample4_1);
AudioConnection          patchCord99(envelope6_0, envSample6_0);
AudioConnection          patchCord100(envelope6_1, envSample6_1);
AudioConnection          patchCord101(envelope7_0, envSample7_0);
AudioConnection          patchCord102(envelope7_1, envSample7_1);
AudioConnection          patchCord103(envelope5_0, envSample5_0);
AudioConnection          patchCord104(envelope5_1, envSample5_1);
AudioConnection          patchCord105(envelope2_0, envSample2_0);
AudioConnection          patchCord106(envelope2_1, envSample2_1);
AudioConnection          patchCord107(envelope3_0, envSample3_0);
AudioConnection          patchCord108(envelope3_1, envSample3_1);
AudioConnection          patchCord109(envelope1_0, envSample1_0);
AudioConnection          patchCord110(envelope1_1, envSample1_1);
AudioConnection          patchCord111(envelope0_0, envSample0_0);
AudioConnection          patchCord112(envelope0_1, envSample0_1);
AudioConnection          patchCord113(ampEnvelope6, 0, voiceSwitch6, 1);
AudioConnection          patchCord114(ampEnvelope6, ampEnvSample6);
AudioConnection          patchCord115(ampEnvelope1, 0, voiceSwitch1, 1);
AudioConnection          patchCord116(ampEnvelope1, ampEnvSample1);
AudioConnection          patchCord117(ampEnvelope7, 0, voiceSwitch7, 1);
AudioConnection          patchCord118(ampEnvelope7, ampEnvSample7);
AudioConnection          patchCord119(ampEnvelope4, 0, voiceSwitch4, 1);
AudioConnection          patchCord120(ampEnvelope4, ampEnvSample4);
AudioConnection          patchCord121(ampEnvelope0, 0, voiceSwitch0, 1);
AudioConnection          patchCord122(ampEnvelope0, ampEnvSample0);
AudioConnection          patchCord123(wavetable6, 0, voiceSwitch6, 0);
AudioConnection          patchCord124(ampEnvelope2, 0, voiceSwitch2, 1);
AudioConnection          patchCord125(ampEnvelope2, ampEnvSample2);
AudioConnection          patchCord126(wavetable2, 0, voiceSwitch2, 0);
AudioConnection          patchCord127(ampEnvelope3, 0, voiceSwitch3, 1);
AudioConnection          patchCord128(ampEnvelope3, ampEnvSample3);
AudioConnection          patchCord129(ampEnvelope5, 0, voiceSwitch5, 1);
AudioConnection          patchCord130(ampEnvelope5, ampEnvSample5);
AudioConnection          patchCord131(wavetable7, 0, voiceSwitch7, 0);
AudioConnection          patchCord132(wavetable3, 0, voiceSwitch3, 0);
AudioConnection          patchCord133(wavetable4, 0, voiceSwitch4, 0);
AudioConnection          patchCord134(wavetable1, 0, voiceSwitch1, 0);
AudioConnection          patchCord135(wavetable0, 0, voiceSwitch0, 0);
AudioConnection          patchCord136(wavetable5, 0, voiceSwitch5, 0);
AudioConnection          patchCord137(voiceSwitch6, 0, voiceMixer0_1, 2);
AudioConnection          patchCord138(voiceSwitch4, 0, voiceMixer0_1, 0);
AudioConnection          patchCord139(voiceSwitch7, 0, voiceMixer0_1, 3);
AudioConnection          patchCord140(voiceSwitch2, 0, voiceMixer0_0, 2);
AudioConnection          patchCord141(voiceSwitch1, 0, voiceMixer0_0, 1);
AudioConnection          patchCord142(voiceSwitch3, 0, voiceMixer0_0, 3);
AudioConnection          patchCord143(voiceSwitch5, 0, voiceMixer0_1, 1);
AudioConnection          patchCord144(voiceSwitch0, 0, voiceMixer0_0, 0);
AudioConnection          patchCord145(voiceMixer0_0, 0, voiceMixer1_0, 0);
AudioConnection          patchCord146(voiceMixer0_1, 0, voiceMixer1_0, 1);
AudioConnection          patchCord147(voiceMixer1_0, 0, freeverbMixerL, 0);
AudioConnection          patchCord148(voiceMixer1_0, 0, freeverbMixerR, 0);
AudioConnection          patchCord149(freeverbBiquadL, 0, freeverbMixerL, 1);
AudioConnection          patchCord150(freeverbBiquadR, 0, freeverbMixerR, 1);
AudioConnection          patchCord151(freeverbMixerL, ampInsOutL);
AudioConnection          patchCord152(freeverbMixerR, ampInsOutR);
AudioConnection          patchCord153(i2sIN, 0, ampI2sInL, 0);
AudioConnection          patchCord154(i2sIN, 0, mixerSWPeakLmInL, 1);
AudioConnection          patchCord155(i2sIN, 0, peakVelocity, 0);
AudioConnection          patchCord156(i2sIN, 1, ampI2sInR, 0);
AudioConnection          patchCord157(i2sIN, 1, mixerSWPeakLmInR, 1);
AudioConnection          patchCord158(usbIN, 0, ampUsbInL, 0);
AudioConnection          patchCord159(usbIN, 0, mixerSWPeakUsbInL, 1);
AudioConnection          patchCord160(usbIN, 1, ampUsbInR, 0);
AudioConnection          patchCord161(usbIN, 1, mixerSWPeakUsbInR, 1);
AudioConnection          patchCord162(ampI2sInR, 0, mixerSWPeakLmInR, 0);
AudioConnection          patchCord163(ampI2sInR, 0, mixerOutI2sR, 0);
AudioConnection          patchCord164(ampI2sInR, 0, mixerOutUsbR, 0);
AudioConnection          patchCord165(ampI2sInR, peakMixerLmR);
AudioConnection          patchCord166(ampI2sInR, 0, mixerClip1, 1);
AudioConnection          patchCord167(ampI2sInL, 0, mixerSWPeakLmInL, 0);
AudioConnection          patchCord168(ampI2sInL, 0, mixerOutI2sL, 0);
AudioConnection          patchCord169(ampI2sInL, 0, mixerOutUsbL, 0);
AudioConnection          patchCord170(ampI2sInL, peakMixerLmL);
AudioConnection          patchCord171(ampI2sInL, 0, mixerClip1, 0);
AudioConnection          patchCord172(ampUsbInR, 0, mixerSWPeakUsbInR, 0);
AudioConnection          patchCord173(ampUsbInR, 0, mixerOutI2sR, 1);
AudioConnection          patchCord174(ampUsbInR, 0, mixerOutUsbR, 1);
AudioConnection          patchCord175(ampUsbInR, peakMixerUsbR);
AudioConnection          patchCord176(ampUsbInR, 0, mixerClip1, 3);
AudioConnection          patchCord177(ampUsbInL, 0, mixerSWPeakUsbInL, 0);
AudioConnection          patchCord178(ampUsbInL, 0, mixerOutI2sL, 1);
AudioConnection          patchCord179(ampUsbInL, 0, mixerOutUsbL, 1);
AudioConnection          patchCord180(ampUsbInL, peakMixerUsbL);
AudioConnection          patchCord181(ampUsbInL, 0, mixerClip1, 2);
AudioConnection          patchCord182(ampInsOutL, peakMixerInsL);
AudioConnection          patchCord183(ampInsOutL, 0, mixerOutUsbL, 2);
AudioConnection          patchCord184(ampInsOutL, 0, mixerOutI2sL, 2);
AudioConnection          patchCord185(ampInsOutR, peakMixerInsR);
AudioConnection          patchCord186(ampInsOutR, 0, mixerOutUsbR, 2);
AudioConnection          patchCord187(ampInsOutR, 0, mixerOutI2sR, 2);
AudioConnection          patchCord188(mixerSWPeakUsbInL, peakUsbInL);
AudioConnection          patchCord189(mixerSWPeakUsbInR, peakUsbInR);
AudioConnection          patchCord190(mixerSWPeakLmInL, peakLmInL);
AudioConnection          patchCord191(mixerSWPeakLmInR, peakLmInR);
AudioConnection          patchCord192(mixerClip1, clip1);
AudioConnection          patchCord193(mixerClip1, peakClip1);
AudioConnection          patchCord194(mixerOutI2sL, ampMasterOutI2sL);
AudioConnection          patchCord195(mixerOutI2sL, 0, mixerSWPeakI2sL, 1);
AudioConnection          patchCord196(mixerOutI2sR, ampMasterOutI2sR);
AudioConnection          patchCord197(mixerOutI2sR, 0, mixerSWPeakI2sR, 1);
AudioConnection          patchCord198(mixerOutUsbR, ampMasterOutUsbR);
AudioConnection          patchCord199(mixerOutUsbR, 0, mixerSWPeakUsbR, 1);
AudioConnection          patchCord200(mixerOutUsbL, ampMasterOutUsbL);
AudioConnection          patchCord201(mixerOutUsbL, 0, mixerSWPeakUsbL, 1);
AudioConnection          patchCord202(ampMasterOutI2sL, 0, i2sOUT, 0);
AudioConnection          patchCord203(ampMasterOutI2sL, 0, mixerSWPeakI2sL, 0);
AudioConnection          patchCord204(ampMasterOutI2sR, 0, i2sOUT, 1);
AudioConnection          patchCord205(ampMasterOutI2sR, 0, mixerSWPeakI2sR, 0);
AudioConnection          patchCord206(ampMasterOutUsbL, 0, usbOUT, 0);
AudioConnection          patchCord207(ampMasterOutUsbL, 0, mixerSWPeakUsbL, 0);
AudioConnection          patchCord208(ampMasterOutUsbR, 0, usbOUT, 1);
AudioConnection          patchCord209(ampMasterOutUsbR, 0, mixerSWPeakUsbR, 0);
AudioConnection          patchCord210(mixerSWPeakI2sL, peakI2sL);
AudioConnection          patchCord211(mixerSWPeakI2sR, peakI2sR);
AudioConnection          patchCord212(mixerSWPeakUsbR, peakUsbR);
AudioConnection          patchCord213(mixerSWPeakUsbL, peakUsbL);
AudioControlSGTL5000     sgtl5000_1;     //xy=2063.9999771118164,859.5000305175781
// GUItool: end automatically generated code
