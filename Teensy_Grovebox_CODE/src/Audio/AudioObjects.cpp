#include "AudioObjects.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthNoiseWhite     noise4;         //xy=185.99999237060547,2046.4999923706055
AudioSynthWaveform       lfo4_1;         //xy=191.99999237060547,2148.4999923706055
AudioSynthWaveform       lfo4_0;         //xy=193.99999237060547,2099.4999923706055
AudioSynthNoiseWhite     noise7;         //xy=190.99999237060547,3073.4999923706055
AudioSynthNoiseWhite     noise2;         //xy=200.99999237060547,1371.4999923706055
AudioSynthNoiseWhite     noise3;         //xy=199.99999237060547,1700.4999923706055
AudioSynthNoiseWhite     noise6;         //xy=198.99999237060547,2731.4999923706055
AudioSynthWaveform       lfo6_1;         //xy=200.99999237060547,2835.4999923706055
AudioSynthWaveform       lfo6_0;         //xy=201.99999237060547,2786.4999923706055
AudioSynthWaveform       lfo7_1;         //xy=200.99999237060547,3176.4999923706055
AudioSynthWaveform       lfo7_0;         //xy=201.99999237060547,3127.4999923706055
AudioSynthWaveform       waveform4_1;    //xy=207.99999237060547,2009.4999923706055
AudioSynthNoiseWhite     noise1;         //xy=211.99999237060547,1026.4999923706055
AudioSynthNoiseWhite     noise5;         //xy=206.99999237060547,2404.4999923706055
AudioSynthWaveform       waveform4_0;    //xy=208.99999237060547,1971.4999923706055
AudioSynthWaveform       lfo5_1;         //xy=206.99999237060547,2515.4999923706055
AudioSynthWaveform       lfo5_0;         //xy=207.99999237060547,2466.4999923706055
AudioSynthWaveform       waveform7_1;    //xy=209.99999237060547,3035.4999923706055
AudioSynthWaveform       waveform7_0;    //xy=210.99999237060547,2997.4999923706055
AudioSynthNoiseWhite     noise0;         //xy=220.99999237060547,707.4999923706055
AudioSynthWaveform       waveform3_1;    //xy=217.99999237060547,1664.4999923706055
AudioSynthWaveform       waveform6_1;    //xy=213.99999237060547,2691.4999923706055
AudioSynthWaveform       lfo2_1;         //xy=218.99999237060547,1479.4999923706055
AudioSynthWaveform       lfo3_1;         //xy=217.99999237060547,1804.4999923706055
AudioSynthWaveform       waveform3_0;    //xy=218.99999237060547,1626.4999923706055
AudioSynthWaveform       waveform6_0;    //xy=214.99999237060547,2653.4999923706055
AudioSynthWaveform       lfo2_0;         //xy=219.99999237060547,1430.4999923706055
AudioSynthWaveform       lfo3_0;         //xy=219.99999237060547,1755.4999923706055
AudioSynthWaveform       lfo1_1;         //xy=222.99999237060547,1166.4999923706055
AudioSynthWaveform       waveform2_0;    //xy=222.99999237060547,1296.4999923706055
AudioSynthWaveform       waveform2_1;    //xy=222.99999237060547,1334.4999923706055
AudioSynthWaveform       lfo1_0;         //xy=224.99999237060547,1117.4999923706055
AudioSynthWaveform       lfo0_1;         //xy=228.99999237060547,834.4999923706055
AudioSynthWaveform       lfo0_0;         //xy=229.99999237060547,786.4999923706055
AudioSynthWaveform       waveform5_1;    //xy=224.99999237060547,2366.4999923706055
AudioSynthWaveform       waveform5_0;    //xy=225.99999237060547,2328.4999923706055
AudioSynthWaveform       waveform1_0;    //xy=233.99999237060547,950.4999923706055
AudioSynthWaveform       waveform1_1;    //xy=233.99999237060547,988.4999923706055
AudioSynthWaveform       waveform0_0;    //xy=237.99999237060547,635.4999923706055
AudioSynthWaveform       waveform0_1;    //xy=238.99999237060547,671.4999923706055
AudioRecordSample        lfoSample4_1; //xy=358,2151
AudioRecordSample        lfoSample4_0; //xy=359,2103
AudioMixer4              oscMixer4;      //xy=361.99999237060547,2028.4999923706055
AudioRecordSample        lfoSample7_1; //xy=365,3175
AudioRecordSample        lfoSample7_0; //xy=366,3127
AudioRecordSample        lfoSample6_1; //xy=368,2838
AudioRecordSample        lfoSample6_0; //xy=369,2790
AudioMixer4              oscMixer7;      //xy=370.99999237060547,3060.4999923706055
AudioRecordSample        lfoSample3_1; //xy=378,1805
AudioRecordSample        lfoSample3_0; //xy=379,1757
AudioMixer4              oscMixer3;      //xy=379.99999237060547,1688.4999923706055
AudioMixer4              oscMixer6;      //xy=375.99999237060547,2719.4999923706055
AudioRecordSample        lfoSample2_1; //xy=385,1483
AudioRecordSample        lfoSample5_1; //xy=381,2515
AudioMixer4              oscMixer2;      //xy=385.99999237060547,1357.4999923706055
AudioRecordSample        lfoSample2_0; //xy=386,1435
AudioRecordSample        lfoSample5_0; //xy=382,2467
AudioMixer4              oscMixer5;      //xy=383.99999237060547,2391.4999923706055
AudioRecordSample        lfoSample0_1; //xy=394.00000762939453,836.0000114440918
AudioMixer4              oscMixer1;      //xy=393.99999237060547,1004.4999923706055
AudioRecordSample        lfoSample0_0;        //xy=395.00000762939453,788.0000114440918
AudioMixer4              oscMixer0;      //xy=398.99999237060547,690.4999923706055
AudioRecordSample        lfoSample1_1; //xy=402,1163
AudioRecordSample        lfoSample1_0; //xy=403,1115
AudioSynthWaveformDc     envDc4;         //xy=528.9999923706055,2121.4999923706055
AudioSynthWaveformDc     envDc7;         //xy=537.9999923706055,3142.4999923706055
AudioSynthWaveformDc     envDc6;         //xy=539.9999923706055,2806.4999923706055
AudioSynthWaveformDc     envDc0;         //xy=548.9999923706055,804.4999923706055
AudioSynthWaveformDc     envDc5;         //xy=543.9999923706055,2480.4999923706055
AudioFilterLadder        ladder1;        //xy=552.9999923706055,1005.4999923706055
AudioSynthWaveformDc     envDc1;         //xy=552.9999923706055,1139.4999923706055
AudioFilterLadder        ladder4;        //xy=550.9999923706055,2016.4999923706055
AudioFilterLadder        ladder2;        //xy=553.9999923706055,1353.4999923706055
AudioSynthWaveformDc     envDc2;         //xy=553.9999923706055,1451.4999923706055
AudioSynthWaveformDc     envDc3;         //xy=555.9999923706055,1775.4999923706055
AudioFilterLadder        ladder6;        //xy=552.9999923706055,2702.4999923706055
AudioFilterLadder        ladder7;        //xy=551.9999923706055,3041.4999923706055
AudioFilterLadder        ladder3;        //xy=560.9999923706055,1684.4999923706055
AudioFilterLadder        ladder0;        //xy=568.9999923706055,677.4999923706055
AudioFilterLadder        ladder5;        //xy=569.9999923706055,2369.4999923706055
AudioEffectEnvelope      envelope4_0;    //xy=685.9999923706055,2097.4999923706055
AudioEffectEnvelope      envelope4_1;    //xy=685.9999923706055,2139.4999923706055
AudioEffectEnvelope      envelope6_0;    //xy=694.9999923706055,2784.4999923706055
AudioEffectEnvelope      envelope6_1;    //xy=694.9999923706055,2826.4999923706055
AudioEffectEnvelope      envelope7_0;    //xy=694.9999923706055,3125.4999923706055
AudioEffectEnvelope      envelope7_1;    //xy=694.9999923706055,3167.4999923706055
AudioEffectEnvelope      envelope5_0;    //xy=700.9999923706055,2464.4999923706055
AudioEffectEnvelope      envelope5_1;    //xy=700.9999923706055,2506.4999923706055
AudioEffectEnvelope      envelope2_0;    //xy=711.9999923706055,1427.4999923706055
AudioEffectEnvelope      envelope2_1;    //xy=711.9999923706055,1470.4999923706055
AudioEffectEnvelope      envelope3_0;    //xy=711.9999923706055,1753.4999923706055
AudioEffectEnvelope      envelope3_1;    //xy=711.9999923706055,1795.4999923706055
AudioEffectEnvelope      envelope1_0;    //xy=716.9999923706055,1114.4999923706055
AudioEffectEnvelope      envelope1_1;    //xy=716.9999923706055,1157.4999923706055
AudioEffectEnvelope      envelope0_0;    //xy=721.9999923706055,783.4999923706055
AudioEffectEnvelope      envelope0_1;    //xy=721.9999923706055,826.4999923706055
AudioEffectEnvelope      ampEnvelope6;   //xy=729.9999923706055,2667.4999923706055
AudioEffectEnvelope      ampEnvelope1;   //xy=749.9999923706055,988.4999923706055
AudioEffectEnvelope      ampEnvelope7;   //xy=741.9999923706055,2993.4999923706055
AudioEffectEnvelope      ampEnvelope4;   //xy=746.9999923706055,1992.4999923706055
AudioPlayClip            playClip1;      //xy=756.2000427246094,719.200023651123
AudioEffectEnvelope      ampEnvelope0;   //xy=760.9999923706055,677.4999923706055
AudioSynthWavetable      wavetable6;     //xy=757.9999923706055,2582.4999923706055
AudioEffectEnvelope      ampEnvelope2;   //xy=764.9999923706055,1320.4999923706055
AudioSynthWavetable      wavetable2;     //xy=765.9999923706055,1258.4999923706055
AudioEffectEnvelope      ampEnvelope3;   //xy=764.9999923706055,1653.4999923706055
AudioEffectEnvelope      ampEnvelope5;   //xy=762.9999923706055,2325.4999923706055
AudioSynthWavetable      wavetable7;     //xy=760.9999923706055,2931.4999923706055
AudioSynthWavetable      wavetable3;     //xy=766.9999923706055,1579.4999923706055
AudioSynthWavetable      wavetable4;     //xy=768.9999923706055,1916.4999923706055
AudioSynthWavetable      wavetable1;     //xy=781.9999923706055,936.4999923706055
AudioSynthWavetable      wavetable0;     //xy=783.9999923706055,611.4999923706055
AudioSynthWavetable      wavetable5;     //xy=791.9999923706055,2261.4999923706055
AudioRecordSample        envSample4_0; //xy=894,2099
AudioRecordSample        envSample4_1; //xy=894,2142.000000476837
AudioRecordSample        envSample5_0; //xy=899,2457
AudioRecordSample        envSample5_1; //xy=899,2500.000000476837
AudioRecordSample        envSample7_0; //xy=897,3119
AudioRecordSample        envSample7_1; //xy=897,3162.000000476837
AudioRecordSample        envSample6_0; //xy=906,2779
AudioRecordSample        envSample6_1; //xy=906,2822.000000476837
AudioRecordSample        envSample3_0; //xy=921,1752
AudioRecordSample        envSample3_1; //xy=921,1795.0000004768372
AudioRecordSample        envSample2_0; //xy=927,1428
AudioRecordSample        envSample2_1; //xy=927,1471.0000004768372
AudioRecordSample        envSample0_0;        //xy=931.0000152587891,781.0000114440918
AudioRecordSample        envSample0_1; //xy=931.0000152587891,824.000011920929
AudioRecordSample        envSample1_0; //xy=930,1112
AudioRecordSample        envSample1_1; //xy=930,1155.0000004768372
AudioMixer4              voiceSwitch6;   //xy=929.9999923706055,2638.4999923706055
AudioRecordSample        ampEnvSample4; //xy=933,2028
AudioRecordSample        ampEnvSample6; //xy=932,2702
AudioMixer4              voiceSwitch4;   //xy=938.9999923706055,1968.4999923706055
AudioMixer4              voiceSwitch7;   //xy=934.9999923706055,2969.4999923706055
AudioMixer4              voiceSwitch2;   //xy=941.9999923706055,1312.4999923706055
AudioRecordSample        ampEnvSample7; //xy=939,3027
AudioRecordSample        ampEnvSample2; //xy=947,1372
AudioRecordSample        ampEnvSample3; //xy=948,1699
AudioMixer4              voiceSwitch1;   //xy=951.9999923706055,994.4999923706055
AudioRecordSample        ampEnvSample5; //xy=947,2366
AudioMixer4              voiceSwitch3;   //xy=949.9999923706055,1641.4999923706055
AudioMixer4              voiceSwitch5;   //xy=947.9999923706055,2305.4999923706055
AudioRecordSample        ampEnvSample1; //xy=953,1059
AudioRecordSample        ampEnvSample0;        //xy=959.0000152587891,722.0000104904175
AudioMixer4              voiceSwitch0;   //xy=963.9999923706055,659.4999923706055
AudioMixer4              voiceMixer0_0;  //xy=1201.9999923706055,1119.4999923706055
AudioMixer4              voiceMixer0_1;  //xy=1203.9999923706055,2460.4999923706055
AudioMixer4              voiceMixer1_0;  //xy=1344.9999923706055,1822.4999923706055
AudioFilterBiquad        freeverbBiquadL; //xy=1669.9999923706055,1498.4999923706055
AudioFilterBiquad        freeverbBiquadR; //xy=1670.9999923706055,1533.4999923706055
AudioMixer4              freeverbMixerL; //xy=1684.9999923706055,1598.4999923706055
AudioMixer4              freeverbMixerR; //xy=1685.9999923706055,1665.4999923706055
AudioInputI2S            i2sIN;          //xy=1735.9999923706055,974.4999923706055
AudioInputUSB            usbIN;          //xy=1743.9999923706055,1232.4999923706055
AudioAmplifier           ampI2sInR;      //xy=1897.9999923706055,996.4999923706055
AudioAmplifier           ampI2sInL;      //xy=1900.9999923706055,956.4999923706055
AudioAmplifier           ampUsbInR;      //xy=1902.9999923706055,1252.4999923706055
AudioAmplifier           ampUsbInL;      //xy=1905.9999923706055,1212.4999923706055
AudioAnalyzePeak         peakVelocity;   //xy=1928.9999923706055,741.4999923706055
AudioAmplifier           ampInsOutL;     //xy=2048.9999923706055,1556.4999923706055
AudioAmplifier           ampInsOutR;     //xy=2048.9999923706055,1597.4999923706055
AudioMixer4              mixerSWPeakUsbInL; //xy=2072.9999923706055,1079.4999923706055
AudioMixer4              mixerSWPeakUsbInR; //xy=2074.9999923706055,1152.4999923706055
AudioMixer4              mixerSWPeakLmInL; //xy=2084.9999923706055,813.4999923706055
AudioMixer4              mixerSWPeakLmInR; //xy=2086.9999923706055,886.4999923706055
AudioAnalyzePeak         peakMixerInsL;  //xy=2208.9999923706055,1425.4999923706055
AudioAnalyzePeak         peakMixerInsR;  //xy=2220.9999923706055,1467.4999923706055
AudioAnalyzePeak         peakLmInL;      //xy=2267.9999923706055,810.4999923706055
AudioAnalyzePeak         peakLmInR;      //xy=2269.9999923706055,886.4999923706055
AudioAnalyzePeak         peakUsbInL;     //xy=2276.9999923706055,1080.4999923706055
AudioAnalyzePeak         peakUsbInR;     //xy=2276.9999923706055,1149.4999923706055
AudioAnalyzePeak         peakMixerLmR;   //xy=2440.9999923706055,833.4999923706055
AudioRecordClip          clip1;          //xy=2442.000026702881,643.2000885009766
AudioAnalyzePeak         peakMixerLmL;   //xy=2441.9999923706055,793.4999923706055
AudioMixer4              mixerOutI2sL;   //xy=2447.9999923706055,925.4999923706055
AudioMixer4              mixerOutI2sR;   //xy=2449.9999923706055,1006.4999923706055
AudioAnalyzePeak         peakMixerUsbL;  //xy=2449.9999923706055,1160.4999923706055
AudioAnalyzePeak         peakMixerUsbR;  //xy=2450.9999923706055,1202.4999923706055
AudioMixer4              mixerOutUsbR;   //xy=2453.9999923706055,1381.4999923706055
AudioMixer4              mixerOutUsbL;   //xy=2454.9999923706055,1292.4999923706055
AudioAmplifier           ampMasterOutI2sL; //xy=2639.9999923706055,932.4999923706055
AudioAmplifier           ampMasterOutI2sR; //xy=2643.9999923706055,1002.4999923706055
AudioAmplifier           ampMasterOutUsbL; //xy=2664.9999923706055,1304.4999923706055
AudioAmplifier           ampMasterOutUsbR; //xy=2668.9999923706055,1366.4999923706055
AudioMixer4              mixerSWPeakI2sL; //xy=2864.9999923706055,867.5000114440918
AudioMixer4              mixerSWPeakI2sR; //xy=2867.9999923706055,1051.500015258789
AudioMixer4              mixerSWPeakUsbR; //xy=2873.9999923706055,1432.4999923706055
AudioMixer4              mixerSWPeakUsbL; //xy=2882.9999923706055,1223.4999923706055
AudioOutputI2S           i2sOUT;         //xy=2908.9999923706055,928.5000133514404
AudioOutputUSB           usbOUT;         //xy=2921.9999923706055,1335.4999923706055
AudioAnalyzePeak         peakI2sL;       //xy=3037.9999961853027,867.5000133514404
AudioAnalyzePeak         peakI2sR;       //xy=3046.9999923706055,1050.500015258789
AudioAnalyzePeak         peakUsbR;       //xy=3055.9999923706055,1433.4999923706055
AudioAnalyzePeak         peakUsbL;       //xy=3073.9999923706055,1224.4999923706055
AudioConnection          patchCord1(noise4, 0, oscMixer4, 2);
AudioConnection          patchCord2(lfo4_1, lfoSample4_1);
AudioConnection          patchCord3(lfo4_0, lfoSample4_0);
AudioConnection          patchCord4(noise7, 0, oscMixer7, 2);
AudioConnection          patchCord5(noise2, 0, oscMixer2, 2);
AudioConnection          patchCord6(noise3, 0, oscMixer3, 2);
AudioConnection          patchCord7(noise6, 0, oscMixer6, 2);
AudioConnection          patchCord8(lfo6_1, lfoSample6_1);
AudioConnection          patchCord9(lfo6_0, lfoSample6_0);
AudioConnection          patchCord10(lfo7_1, lfoSample7_1);
AudioConnection          patchCord11(lfo7_0, lfoSample7_0);
AudioConnection          patchCord12(waveform4_1, 0, oscMixer4, 1);
AudioConnection          patchCord13(noise1, 0, oscMixer1, 2);
AudioConnection          patchCord14(noise5, 0, oscMixer5, 2);
AudioConnection          patchCord15(waveform4_0, 0, oscMixer4, 0);
AudioConnection          patchCord16(lfo5_1, lfoSample5_1);
AudioConnection          patchCord17(lfo5_0, lfoSample5_0);
AudioConnection          patchCord18(waveform7_1, 0, oscMixer7, 1);
AudioConnection          patchCord19(waveform7_0, 0, oscMixer7, 0);
AudioConnection          patchCord20(noise0, 0, oscMixer0, 2);
AudioConnection          patchCord21(waveform3_1, 0, oscMixer3, 1);
AudioConnection          patchCord22(waveform6_1, 0, oscMixer6, 1);
AudioConnection          patchCord23(lfo2_1, lfoSample2_1);
AudioConnection          patchCord24(lfo3_1, lfoSample3_1);
AudioConnection          patchCord25(waveform3_0, 0, oscMixer3, 0);
AudioConnection          patchCord26(waveform6_0, 0, oscMixer6, 0);
AudioConnection          patchCord27(lfo2_0, lfoSample2_0);
AudioConnection          patchCord28(lfo3_0, lfoSample3_0);
AudioConnection          patchCord29(lfo1_1, lfoSample1_1);
AudioConnection          patchCord30(waveform2_0, 0, oscMixer2, 0);
AudioConnection          patchCord31(waveform2_1, 0, oscMixer2, 1);
AudioConnection          patchCord32(lfo1_0, lfoSample1_0);
AudioConnection          patchCord33(lfo0_1, lfoSample0_1);
AudioConnection          patchCord34(lfo0_0, lfoSample0_0);
AudioConnection          patchCord35(waveform5_1, 0, oscMixer5, 1);
AudioConnection          patchCord36(waveform5_0, 0, oscMixer5, 0);
AudioConnection          patchCord37(waveform1_0, 0, oscMixer1, 0);
AudioConnection          patchCord38(waveform1_1, 0, oscMixer1, 1);
AudioConnection          patchCord39(waveform0_0, 0, oscMixer0, 0);
AudioConnection          patchCord40(waveform0_1, 0, oscMixer0, 1);
AudioConnection          patchCord41(oscMixer4, 0, ladder4, 0);
AudioConnection          patchCord42(oscMixer7, 0, ladder7, 0);
AudioConnection          patchCord43(oscMixer3, 0, ladder3, 0);
AudioConnection          patchCord44(oscMixer6, 0, ladder6, 0);
AudioConnection          patchCord45(oscMixer2, 0, ladder2, 0);
AudioConnection          patchCord46(oscMixer5, 0, ladder5, 0);
AudioConnection          patchCord47(oscMixer1, 0, ladder1, 0);
AudioConnection          patchCord48(oscMixer0, 0, ladder0, 0);
AudioConnection          patchCord49(envDc4, envelope4_0);
AudioConnection          patchCord50(envDc4, envelope4_1);
AudioConnection          patchCord51(envDc7, envelope7_0);
AudioConnection          patchCord52(envDc7, envelope7_1);
AudioConnection          patchCord53(envDc6, envelope6_0);
AudioConnection          patchCord54(envDc6, envelope6_1);
AudioConnection          patchCord55(envDc0, envelope0_0);
AudioConnection          patchCord56(envDc0, envelope0_1);
AudioConnection          patchCord57(envDc5, envelope5_0);
AudioConnection          patchCord58(envDc5, envelope5_1);
AudioConnection          patchCord59(ladder1, ampEnvelope1);
AudioConnection          patchCord60(envDc1, envelope1_0);
AudioConnection          patchCord61(envDc1, envelope1_1);
AudioConnection          patchCord62(ladder4, ampEnvelope4);
AudioConnection          patchCord63(ladder2, ampEnvelope2);
AudioConnection          patchCord64(envDc2, envelope2_0);
AudioConnection          patchCord65(envDc2, envelope2_1);
AudioConnection          patchCord66(envDc3, envelope3_0);
AudioConnection          patchCord67(envDc3, envelope3_1);
AudioConnection          patchCord68(ladder6, ampEnvelope6);
AudioConnection          patchCord69(ladder7, ampEnvelope7);
AudioConnection          patchCord70(ladder3, ampEnvelope3);
AudioConnection          patchCord71(ladder0, ampEnvelope0);
AudioConnection          patchCord72(ladder5, ampEnvelope5);
AudioConnection          patchCord73(envelope4_0, envSample4_0);
AudioConnection          patchCord74(envelope4_1, envSample4_1);
AudioConnection          patchCord75(envelope6_0, envSample6_0);
AudioConnection          patchCord76(envelope6_1, envSample6_1);
AudioConnection          patchCord77(envelope7_0, envSample7_0);
AudioConnection          patchCord78(envelope7_1, envSample7_1);
AudioConnection          patchCord79(envelope5_0, envSample5_0);
AudioConnection          patchCord80(envelope5_1, envSample5_1);
AudioConnection          patchCord81(envelope2_0, envSample2_0);
AudioConnection          patchCord82(envelope2_1, envSample2_1);
AudioConnection          patchCord83(envelope3_0, envSample3_0);
AudioConnection          patchCord84(envelope3_1, envSample3_1);
AudioConnection          patchCord85(envelope1_0, envSample1_0);
AudioConnection          patchCord86(envelope1_1, envSample1_1);
AudioConnection          patchCord87(envelope0_0, envSample0_0);
AudioConnection          patchCord88(envelope0_1, envSample0_1);
AudioConnection          patchCord89(ampEnvelope6, 0, voiceSwitch6, 1);
AudioConnection          patchCord90(ampEnvelope6, ampEnvSample6);
AudioConnection          patchCord91(ampEnvelope1, 0, voiceSwitch1, 1);
AudioConnection          patchCord92(ampEnvelope1, ampEnvSample1);
AudioConnection          patchCord93(ampEnvelope7, 0, voiceSwitch7, 1);
AudioConnection          patchCord94(ampEnvelope7, ampEnvSample7);
AudioConnection          patchCord95(ampEnvelope4, 0, voiceSwitch4, 1);
AudioConnection          patchCord96(ampEnvelope4, ampEnvSample4);
AudioConnection          patchCord97(playClip1, 0, voiceSwitch0, 2);
AudioConnection          patchCord98(ampEnvelope0, 0, voiceSwitch0, 1);
AudioConnection          patchCord99(ampEnvelope0, ampEnvSample0);
AudioConnection          patchCord100(wavetable6, 0, voiceSwitch6, 0);
AudioConnection          patchCord101(ampEnvelope2, 0, voiceSwitch2, 1);
AudioConnection          patchCord102(ampEnvelope2, ampEnvSample2);
AudioConnection          patchCord103(wavetable2, 0, voiceSwitch2, 0);
AudioConnection          patchCord104(ampEnvelope3, 0, voiceSwitch3, 1);
AudioConnection          patchCord105(ampEnvelope3, ampEnvSample3);
AudioConnection          patchCord106(ampEnvelope5, 0, voiceSwitch5, 1);
AudioConnection          patchCord107(ampEnvelope5, ampEnvSample5);
AudioConnection          patchCord108(wavetable7, 0, voiceSwitch7, 0);
AudioConnection          patchCord109(wavetable3, 0, voiceSwitch3, 0);
AudioConnection          patchCord110(wavetable4, 0, voiceSwitch4, 0);
AudioConnection          patchCord111(wavetable1, 0, voiceSwitch1, 0);
AudioConnection          patchCord112(wavetable0, 0, voiceSwitch0, 0);
AudioConnection          patchCord113(wavetable5, 0, voiceSwitch5, 0);
AudioConnection          patchCord114(voiceSwitch6, 0, voiceMixer0_1, 2);
AudioConnection          patchCord115(voiceSwitch4, 0, voiceMixer0_1, 0);
AudioConnection          patchCord116(voiceSwitch7, 0, voiceMixer0_1, 3);
AudioConnection          patchCord117(voiceSwitch2, 0, voiceMixer0_0, 2);
AudioConnection          patchCord118(voiceSwitch1, 0, voiceMixer0_0, 1);
AudioConnection          patchCord119(voiceSwitch3, 0, voiceMixer0_0, 3);
AudioConnection          patchCord120(voiceSwitch5, 0, voiceMixer0_1, 1);
AudioConnection          patchCord121(voiceSwitch0, 0, voiceMixer0_0, 0);
AudioConnection          patchCord122(voiceMixer0_0, 0, voiceMixer1_0, 0);
AudioConnection          patchCord123(voiceMixer0_1, 0, voiceMixer1_0, 1);
AudioConnection          patchCord124(voiceMixer1_0, 0, freeverbMixerL, 0);
AudioConnection          patchCord125(voiceMixer1_0, 0, freeverbMixerR, 0);
AudioConnection          patchCord126(freeverbBiquadL, 0, freeverbMixerL, 1);
AudioConnection          patchCord127(freeverbBiquadR, 0, freeverbMixerR, 1);
AudioConnection          patchCord128(freeverbMixerL, ampInsOutL);
AudioConnection          patchCord129(freeverbMixerR, ampInsOutR);
AudioConnection          patchCord130(i2sIN, 0, ampI2sInL, 0);
AudioConnection          patchCord131(i2sIN, 0, mixerSWPeakLmInL, 1);
AudioConnection          patchCord132(i2sIN, 0, peakVelocity, 0);
AudioConnection          patchCord133(i2sIN, 1, ampI2sInR, 0);
AudioConnection          patchCord134(i2sIN, 1, mixerSWPeakLmInR, 1);
AudioConnection          patchCord135(usbIN, 0, ampUsbInL, 0);
AudioConnection          patchCord136(usbIN, 0, mixerSWPeakUsbInL, 1);
AudioConnection          patchCord137(usbIN, 1, ampUsbInR, 0);
AudioConnection          patchCord138(usbIN, 1, mixerSWPeakUsbInR, 1);
AudioConnection          patchCord139(ampI2sInR, 0, mixerSWPeakLmInR, 0);
AudioConnection          patchCord140(ampI2sInR, 0, mixerOutI2sR, 0);
AudioConnection          patchCord141(ampI2sInR, 0, mixerOutUsbR, 0);
AudioConnection          patchCord142(ampI2sInR, peakMixerLmR);
AudioConnection          patchCord143(ampI2sInL, 0, mixerSWPeakLmInL, 0);
AudioConnection          patchCord144(ampI2sInL, 0, mixerOutI2sL, 0);
AudioConnection          patchCord145(ampI2sInL, 0, mixerOutUsbL, 0);
AudioConnection          patchCord146(ampI2sInL, peakMixerLmL);
AudioConnection          patchCord147(ampI2sInL, clip1);
AudioConnection          patchCord148(ampUsbInR, 0, mixerSWPeakUsbInR, 0);
AudioConnection          patchCord149(ampUsbInR, 0, mixerOutI2sR, 1);
AudioConnection          patchCord150(ampUsbInR, 0, mixerOutUsbR, 1);
AudioConnection          patchCord151(ampUsbInR, peakMixerUsbR);
AudioConnection          patchCord152(ampUsbInL, 0, mixerSWPeakUsbInL, 0);
AudioConnection          patchCord153(ampUsbInL, 0, mixerOutI2sL, 1);
AudioConnection          patchCord154(ampUsbInL, 0, mixerOutUsbL, 1);
AudioConnection          patchCord155(ampUsbInL, peakMixerUsbL);
AudioConnection          patchCord156(ampInsOutL, peakMixerInsL);
AudioConnection          patchCord157(ampInsOutL, 0, mixerOutUsbL, 2);
AudioConnection          patchCord158(ampInsOutL, 0, mixerOutI2sL, 2);
AudioConnection          patchCord159(ampInsOutR, peakMixerInsR);
AudioConnection          patchCord160(ampInsOutR, 0, mixerOutUsbR, 2);
AudioConnection          patchCord161(ampInsOutR, 0, mixerOutI2sR, 2);
AudioConnection          patchCord162(mixerSWPeakUsbInL, peakUsbInL);
AudioConnection          patchCord163(mixerSWPeakUsbInR, peakUsbInR);
AudioConnection          patchCord164(mixerSWPeakLmInL, peakLmInL);
AudioConnection          patchCord165(mixerSWPeakLmInR, peakLmInR);
AudioConnection          patchCord166(mixerOutI2sL, ampMasterOutI2sL);
AudioConnection          patchCord167(mixerOutI2sL, 0, mixerSWPeakI2sL, 1);
AudioConnection          patchCord168(mixerOutI2sR, ampMasterOutI2sR);
AudioConnection          patchCord169(mixerOutI2sR, 0, mixerSWPeakI2sR, 1);
AudioConnection          patchCord170(mixerOutUsbR, ampMasterOutUsbR);
AudioConnection          patchCord171(mixerOutUsbR, 0, mixerSWPeakUsbR, 1);
AudioConnection          patchCord172(mixerOutUsbL, ampMasterOutUsbL);
AudioConnection          patchCord173(mixerOutUsbL, 0, mixerSWPeakUsbL, 1);
AudioConnection          patchCord174(ampMasterOutI2sL, 0, i2sOUT, 0);
AudioConnection          patchCord175(ampMasterOutI2sL, 0, mixerSWPeakI2sL, 0);
AudioConnection          patchCord176(ampMasterOutI2sR, 0, i2sOUT, 1);
AudioConnection          patchCord177(ampMasterOutI2sR, 0, mixerSWPeakI2sR, 0);
AudioConnection          patchCord178(ampMasterOutUsbL, 0, usbOUT, 0);
AudioConnection          patchCord179(ampMasterOutUsbL, 0, mixerSWPeakUsbL, 0);
AudioConnection          patchCord180(ampMasterOutUsbR, 0, usbOUT, 1);
AudioConnection          patchCord181(ampMasterOutUsbR, 0, mixerSWPeakUsbR, 0);
AudioConnection          patchCord182(mixerSWPeakI2sL, peakI2sL);
AudioConnection          patchCord183(mixerSWPeakI2sR, peakI2sR);
AudioConnection          patchCord184(mixerSWPeakUsbR, peakUsbR);
AudioConnection          patchCord185(mixerSWPeakUsbL, peakUsbL);
AudioControlSGTL5000     sgtl5000_1;     //xy=1708.9999923706055,809.4999923706055
// GUItool: end automatically generated code
