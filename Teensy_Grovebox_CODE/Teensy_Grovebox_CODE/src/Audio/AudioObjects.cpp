#include "AudioObjects.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthNoiseWhite     noise5; //xy=544.5557022094727,1354.9799671173096
AudioSynthNoiseWhite     noise4; //xy=548.6668395996094,1164.4950256347656
AudioSynthNoiseWhite     noise3; //xy=550.0001525878906,948.1010875701904
AudioSynthNoiseWhite     noise6; //xy=547.889030456543,1542.0406131744385
AudioSynthNoiseWhite     noise7; //xy=548.8889617919922,1739.1517248153687
AudioSynthNoiseWhite     noise2; //xy=555.6668281555176,759.3940696716309
AudioSynthNoiseWhite     noise1;  //xy=556.7779159545898,566.2425804138184
AudioSynthNoiseWhite     noise0;         //xy=560.7778930664062,385.1721200942993
AudioSynthWaveform       waveform5_1; //xy=562.5556716918945,1316.1617908477783
AudioSynthWaveform       waveform5_0; //xy=563.5557098388672,1278.0708866119385
AudioSynthWaveform       waveform6_1; //xy=562.8889999389648,1502.1315670013428
AudioSynthWaveform       waveform6_0; //xy=563.8890380859375,1464.040662765503
AudioSynthWaveform       waveform3_1; //xy=568.000129699707,912.101110458374
AudioSynthWaveform       waveform3_0; //xy=569.0001678466797,874.0102062225342
AudioSynthWaveform       waveform7_1; //xy=567.8889274597168,1701.242567062378
AudioSynthWaveform       waveform4_1;  //xy=570.6668090820312,1126.6768436431885
AudioSynthWaveform       waveform7_0; //xy=568.8889656066895,1663.151662826538
AudioSynthWaveform       waveform4_0; //xy=571.6668472290039,1088.5859394073486
AudioSynthWaveform       waveform0_0; //xy=577.7779388427734,312.89918518066406
AudioSynthWaveform       waveform0_1; //xy=578.7779159545898,348.99000549316406
AudioSynthWaveform       waveform2_0; //xy=577.6668319702148,684.2122402191162
AudioSynthWaveform       waveform2_1; //xy=577.666805267334,722.3030605316162
AudioSynthWaveform       waveform1_0; //xy=578.7779350280762,490.8788814544678
AudioSynthWaveform       waveform1_1; //xy=578.7779006958008,528.9697036743164
AudioMixer4              oscMixer5; //xy=721.5556869506836,1341.1616134643555
AudioMixer4              oscMixer4; //xy=724.6668243408203,1145.6767539978027
AudioMixer4              oscMixer6; //xy=724.8889999389648,1530.1315326690674
AudioMixer4              oscMixer3; //xy=730.0001220703125,936.1010799407959
AudioMixer4              oscMixer7; //xy=728.8889274597168,1726.242597579956
AudioMixer4              oscMixer0;         //xy=738.7779006958008,367.9900074005127
AudioMixer4              oscMixer1; //xy=738.7779006958008,544.9697456359863
AudioMixer4              oscMixer2; //xy=740.6668395996094,745.3030586242676
AudioFilterLadder        ladder1; //xy=897.8284072875977,545.3535995483398
AudioFilterLadder        ladder6; //xy=901.6061058044434,1513.2019805908203
AudioFilterLadder        ladder0;        //xy=909.1615867614746,355.24245834350586
AudioFilterLadder        ladder2; //xy=909.3838863372803,741.373722076416
AudioFilterLadder        ladder5; //xy=907.4948616027832,1319.7373447418213
AudioFilterLadder        ladder3; //xy=911.3837966918945,931.5757389068604
AudioFilterLadder        ladder7; //xy=909.4948616027832,1706.989917755127
AudioFilterLadder        ladder4; //xy=913.4948654174805,1133.605978012085
AudioEffectEnvelope      ampEnvelope6; //xy=1089.8890991210938,1472.1315803527832
AudioEffectEnvelope      ampEnvelope1; //xy=1094.778034210205,528.1517162322998
AudioEffectEnvelope      ampEnvelope0;      //xy=1100.7780418395996,355.26272201538086
AudioEffectEnvelope      ampEnvelope5; //xy=1100.5558242797852,1275.8890647888184
AudioEffectEnvelope      ampEnvelope7; //xy=1099.8890991210938,1651.0607643127441
AudioEffectEnvelope      ampEnvelope4; //xy=1109.6670684814453,1110.4040069580078
AudioEffectEnvelope      ampEnvelope3; //xy=1115.000244140625,901.0101318359375
AudioSynthWavetable      wavetable3; //xy=1116.5717544555664,827.0579061508179
AudioEffectEnvelope      ampEnvelope2; //xy=1119.6668853759766,708.3031005859375
AudioSynthWavetable      wavetable2; //xy=1120.6828842163086,645.7244892120361
AudioSynthWavetable      wavetable6; //xy=1118.4606018066406,1387.5630340576172
AudioSynthWavetable      wavetable0;     //xy=1123.5490760803223,289.4571723937988
AudioSynthWavetable      wavetable7; //xy=1118.5715713500977,1589.2296047210693
AudioSynthWavetable      wavetable1; //xy=1126.7940063476562,476.2801914215088
AudioSynthWavetable      wavetable5; //xy=1129.1272010803223,1211.340612411499
AudioSynthWavetable      wavetable4; //xy=1131.3494491577148,1034.0579090118408
AudioMixer4              voiceSwitch5; //xy=1285.0001678466797,1255.1821537017822
AudioMixer4              voiceSwitch6; //xy=1290.0001678466797,1443.182336807251
AudioMixer4              voiceSwitch7; //xy=1292.3334999084473,1627.2935428619385
AudioMixer4              voiceSwitch1; //xy=1297.0001258850098,534.0909633636475
AudioMixer4              voiceSwitch2; //xy=1297.0001258850098,700.0910129547119
AudioMixer4              voiceSwitch3; //xy=1300.0001678466797,889.1820392608643
AudioMixer4              voiceSwitch4; //xy=1301.0001678466797,1086.1820087432861
AudioMixer4              voiceSwitch0; //xy=1304.0001220703125,337.0909614562988
AudioMixer4              voiceMixer0_1; //xy=1526.5715980529785,1337.8959293365479
AudioMixer4              voiceMixer0_0;         //xy=1529.57177734375,604.8959693908691
AudioMixer4              voiceMixer1_0; //xy=1732.7938232421875,932.0073184967041
AudioFilterBiquad        freeverbBiquadL;        //xy=1997.7663955688477,983.4156684875488
AudioFilterBiquad        freeverbBiquadR; //xy=1998.7663879394531,1018.4156694412231
AudioMixer4              freeverbMixerL; //xy=2012.9756317138672,1083.7852382659912
AudioMixer4              freeverbMixerR; //xy=2013.610496520996,1150.7015399932861
AudioInputI2S            i2sIN;           //xy=2063.583610534668,459.166955947876
AudioInputUSB            usbIN;           //xy=2071.5835304260254,717.1669445037842
AudioAmplifier           ampI2sInR;           //xy=2225.5835342407227,481.075984954834
AudioAmplifier           ampI2sInL;           //xy=2228.5835342407227,441.0759811401367
AudioAmplifier           ampUsbInR; //xy=2230.5835342407227,737.1669034957886
AudioAmplifier           ampUsbInL; //xy=2233.5835342407227,697.1668996810913
AudioAnalyzePeak         peakVelocity;          //xy=2256.3334045410156,226.48508167266846
AudioAmplifier           ampInsOutL;           //xy=2376.2944412231445,1041.6020164489746
AudioAmplifier           ampInsOutR; //xy=2376.476261138916,1082.4201107025146
AudioMixer4              mixerSWPeakUsbInL;  //xy=2400.583526611328,564.0759716033936
AudioMixer4              mixerSWPeakUsbInR; //xy=2402.128890991211,637.0759410858154
AudioMixer4              mixerSWPeakLmInL; //xy=2412.5835876464844,298.166898727417
AudioMixer4              mixerSWPeakLmInR; //xy=2414.128952026367,371.16686820983887
AudioAnalyzePeak         peakMixerInsL; //xy=2536.9775390625,910.4093418121338
AudioAnalyzePeak         peakMixerInsR; //xy=2548.1998443603516,952.6316204071045
AudioAnalyzePeak         peakLmInL; //xy=2595.0381774902344,295.16693210601807
AudioAnalyzePeak         peakLmInR; //xy=2597.5835456848145,371.1669120788574
AudioAnalyzePeak         peakUsbInL; //xy=2604.583541870117,565.1668968200684
AudioAnalyzePeak         peakUsbInR; //xy=2604.583564758301,634.1669845581055
AudioAnalyzePeak         peakMixerLmR; //xy=2768.5835494995117,318.1668891906738
AudioAnalyzePeak         peakMixerLmL; //xy=2769.5835494995117,278.1668872833252
AudioMixer4              mixerOutI2sL;         //xy=2775.583526611328,410.16691398620605
AudioMixer4              mixerOutI2sR;         //xy=2777.583526611328,491.1669273376465
AudioAnalyzePeak         peakMixerUsbL; //xy=2777.7653732299805,645.3487215042114
AudioAnalyzePeak         peakMixerUsbR;  //xy=2778.7653732299805,687.3487231731415
AudioMixer4              mixerOutUsbR; //xy=2781.5835189819336,866.1668949127197
AudioMixer4              mixerOutUsbL; //xy=2782.583526611328,777.1668949127197
AudioAmplifier           ampMasterOutI2sL;           //xy=2967.4926223754883,417.16690254211426
AudioAmplifier           ampMasterOutI2sR; //xy=2971.4926834106445,487.1669101715088
AudioAmplifier           ampMasterOutUsbL; //xy=2992.4926223754883,789.1668949127197
AudioAmplifier           ampMasterOutUsbR; //xy=2996.4926223754883,851.1668968200684
AudioMixer4              mixerSWPeakI2sL;         //xy=3188.5836334228516,366.1669063568115
AudioMixer4              mixerSWPeakI2sR; //xy=3195.6745071411133,519.1668910980225
AudioMixer4              mixerSWPeakUsbR;  //xy=3201.6745376586914,917.9852237701416
AudioMixer4              mixerSWPeakUsbL;  //xy=3210.6748123168945,708.1670799255371
AudioOutputI2S           i2sOUT;           //xy=3233.583595275879,444.16690254211426
AudioOutputUSB           usbOUT;           //xy=3249.5835037231445,820.1668968200684
AudioAnalyzePeak         peakI2sL;          //xy=3361.4928131103516,365.16691875457764
AudioAnalyzePeak         peakI2sR;          //xy=3370.4930877685547,520.1670475006104
AudioAnalyzePeak         peakUsbR; //xy=3383.4929008483887,918.1671304702759
AudioAnalyzePeak         peakUsbL; //xy=3401.4930877685547,709.1671257019043
AudioConnection          patchCord1(noise5, 0, oscMixer5, 2);
AudioConnection          patchCord2(noise4, 0, oscMixer4, 2);
AudioConnection          patchCord3(noise3, 0, oscMixer3, 2);
AudioConnection          patchCord4(noise6, 0, oscMixer6, 2);
AudioConnection          patchCord5(noise7, 0, oscMixer7, 2);
AudioConnection          patchCord6(noise2, 0, oscMixer2, 2);
AudioConnection          patchCord7(noise1, 0, oscMixer1, 2);
AudioConnection          patchCord8(noise0, 0, oscMixer0, 2);
AudioConnection          patchCord9(waveform5_1, 0, oscMixer5, 1);
AudioConnection          patchCord10(waveform5_0, 0, oscMixer5, 0);
AudioConnection          patchCord11(waveform6_1, 0, oscMixer6, 1);
AudioConnection          patchCord12(waveform6_0, 0, oscMixer6, 0);
AudioConnection          patchCord13(waveform3_1, 0, oscMixer3, 1);
AudioConnection          patchCord14(waveform3_0, 0, oscMixer3, 0);
AudioConnection          patchCord15(waveform7_1, 0, oscMixer7, 1);
AudioConnection          patchCord16(waveform4_1, 0, oscMixer4, 1);
AudioConnection          patchCord17(waveform7_0, 0, oscMixer7, 0);
AudioConnection          patchCord18(waveform4_0, 0, oscMixer4, 0);
AudioConnection          patchCord19(waveform0_0, 0, oscMixer0, 0);
AudioConnection          patchCord20(waveform0_1, 0, oscMixer0, 1);
AudioConnection          patchCord21(waveform2_0, 0, oscMixer2, 0);
AudioConnection          patchCord22(waveform2_1, 0, oscMixer2, 1);
AudioConnection          patchCord23(waveform1_0, 0, oscMixer1, 0);
AudioConnection          patchCord24(waveform1_1, 0, oscMixer1, 1);
AudioConnection          patchCord25(oscMixer5, 0, ladder5, 0);
AudioConnection          patchCord26(oscMixer4, 0, ladder4, 0);
AudioConnection          patchCord27(oscMixer6, 0, ladder6, 0);
AudioConnection          patchCord28(oscMixer3, 0, ladder3, 0);
AudioConnection          patchCord29(oscMixer7, 0, ladder7, 0);
AudioConnection          patchCord30(oscMixer0, 0, ladder0, 0);
AudioConnection          patchCord31(oscMixer1, 0, ladder1, 0);
AudioConnection          patchCord32(oscMixer2, 0, ladder2, 0);
AudioConnection          patchCord33(ladder1, ampEnvelope1);
AudioConnection          patchCord34(ladder6, ampEnvelope6);
AudioConnection          patchCord35(ladder0, ampEnvelope0);
AudioConnection          patchCord36(ladder2, ampEnvelope2);
AudioConnection          patchCord37(ladder5, ampEnvelope5);
AudioConnection          patchCord38(ladder3, ampEnvelope3);
AudioConnection          patchCord39(ladder7, ampEnvelope7);
AudioConnection          patchCord40(ladder4, ampEnvelope4);
AudioConnection          patchCord41(ampEnvelope6, 0, voiceSwitch6, 1);
AudioConnection          patchCord42(ampEnvelope1, 0, voiceSwitch1, 1);
AudioConnection          patchCord43(ampEnvelope0, 0, voiceSwitch0, 1);
AudioConnection          patchCord44(ampEnvelope5, 0, voiceSwitch5, 1);
AudioConnection          patchCord45(ampEnvelope7, 0, voiceSwitch7, 1);
AudioConnection          patchCord46(ampEnvelope4, 0, voiceSwitch4, 1);
AudioConnection          patchCord47(ampEnvelope3, 0, voiceSwitch3, 1);
AudioConnection          patchCord48(wavetable3, 0, voiceSwitch3, 0);
AudioConnection          patchCord49(ampEnvelope2, 0, voiceSwitch2, 1);
AudioConnection          patchCord50(wavetable2, 0, voiceSwitch2, 0);
AudioConnection          patchCord51(wavetable6, 0, voiceSwitch6, 0);
AudioConnection          patchCord52(wavetable0, 0, voiceSwitch0, 0);
AudioConnection          patchCord53(wavetable7, 0, voiceSwitch7, 0);
AudioConnection          patchCord54(wavetable1, 0, voiceSwitch1, 0);
AudioConnection          patchCord55(wavetable5, 0, voiceSwitch5, 0);
AudioConnection          patchCord56(wavetable4, 0, voiceSwitch4, 0);
AudioConnection          patchCord57(voiceSwitch5, 0, voiceMixer0_1, 1);
AudioConnection          patchCord58(voiceSwitch6, 0, voiceMixer0_1, 2);
AudioConnection          patchCord59(voiceSwitch7, 0, voiceMixer0_1, 3);
AudioConnection          patchCord60(voiceSwitch1, 0, voiceMixer0_0, 1);
AudioConnection          patchCord61(voiceSwitch2, 0, voiceMixer0_0, 2);
AudioConnection          patchCord62(voiceSwitch3, 0, voiceMixer0_0, 3);
AudioConnection          patchCord63(voiceSwitch4, 0, voiceMixer0_1, 0);
AudioConnection          patchCord64(voiceSwitch0, 0, voiceMixer0_0, 0);
AudioConnection          patchCord65(voiceMixer0_1, 0, voiceMixer1_0, 1);
AudioConnection          patchCord66(voiceMixer0_0, 0, voiceMixer1_0, 0);
AudioConnection          patchCord67(voiceMixer1_0, 0, freeverbMixerL, 0);
AudioConnection          patchCord68(voiceMixer1_0, 0, freeverbMixerR, 0);
AudioConnection          patchCord69(freeverbBiquadL, 0, freeverbMixerL, 1);
AudioConnection          patchCord70(freeverbBiquadR, 0, freeverbMixerR, 1);
AudioConnection          patchCord71(freeverbMixerL, ampInsOutL);
AudioConnection          patchCord72(freeverbMixerR, ampInsOutR);
AudioConnection          patchCord73(i2sIN, 0, ampI2sInL, 0);
AudioConnection          patchCord74(i2sIN, 0, mixerSWPeakLmInL, 1);
AudioConnection          patchCord75(i2sIN, 0, peakVelocity, 0);
AudioConnection          patchCord76(i2sIN, 1, ampI2sInR, 0);
AudioConnection          patchCord77(i2sIN, 1, mixerSWPeakLmInR, 1);
AudioConnection          patchCord78(usbIN, 0, ampUsbInL, 0);
AudioConnection          patchCord79(usbIN, 0, mixerSWPeakUsbInL, 1);
AudioConnection          patchCord80(usbIN, 1, ampUsbInR, 0);
AudioConnection          patchCord81(usbIN, 1, mixerSWPeakUsbInR, 1);
AudioConnection          patchCord82(ampI2sInR, 0, mixerSWPeakLmInR, 0);
AudioConnection          patchCord83(ampI2sInR, 0, mixerOutI2sR, 0);
AudioConnection          patchCord84(ampI2sInR, 0, mixerOutUsbR, 0);
AudioConnection          patchCord85(ampI2sInR, peakMixerLmR);
AudioConnection          patchCord86(ampI2sInL, 0, mixerSWPeakLmInL, 0);
AudioConnection          patchCord87(ampI2sInL, 0, mixerOutI2sL, 0);
AudioConnection          patchCord88(ampI2sInL, 0, mixerOutUsbL, 0);
AudioConnection          patchCord89(ampI2sInL, peakMixerLmL);
AudioConnection          patchCord90(ampUsbInR, 0, mixerSWPeakUsbInR, 0);
AudioConnection          patchCord91(ampUsbInR, 0, mixerOutI2sR, 1);
AudioConnection          patchCord92(ampUsbInR, 0, mixerOutUsbR, 1);
AudioConnection          patchCord93(ampUsbInR, peakMixerUsbR);
AudioConnection          patchCord94(ampUsbInL, 0, mixerSWPeakUsbInL, 0);
AudioConnection          patchCord95(ampUsbInL, 0, mixerOutI2sL, 1);
AudioConnection          patchCord96(ampUsbInL, 0, mixerOutUsbL, 1);
AudioConnection          patchCord97(ampUsbInL, peakMixerUsbL);
AudioConnection          patchCord98(ampInsOutL, peakMixerInsL);
AudioConnection          patchCord99(ampInsOutL, 0, mixerOutUsbL, 2);
AudioConnection          patchCord100(ampInsOutL, 0, mixerOutI2sL, 2);
AudioConnection          patchCord101(ampInsOutR, peakMixerInsR);
AudioConnection          patchCord102(ampInsOutR, 0, mixerOutUsbR, 2);
AudioConnection          patchCord103(ampInsOutR, 0, mixerOutI2sR, 2);
AudioConnection          patchCord104(mixerSWPeakUsbInL, peakUsbInL);
AudioConnection          patchCord105(mixerSWPeakUsbInR, peakUsbInR);
AudioConnection          patchCord106(mixerSWPeakLmInL, peakLmInL);
AudioConnection          patchCord107(mixerSWPeakLmInR, peakLmInR);
AudioConnection          patchCord108(mixerOutI2sL, ampMasterOutI2sL);
AudioConnection          patchCord109(mixerOutI2sL, 0, mixerSWPeakI2sL, 1);
AudioConnection          patchCord110(mixerOutI2sR, ampMasterOutI2sR);
AudioConnection          patchCord111(mixerOutI2sR, 0, mixerSWPeakI2sR, 1);
AudioConnection          patchCord112(mixerOutUsbR, ampMasterOutUsbR);
AudioConnection          patchCord113(mixerOutUsbR, 0, mixerSWPeakUsbR, 1);
AudioConnection          patchCord114(mixerOutUsbL, ampMasterOutUsbL);
AudioConnection          patchCord115(mixerOutUsbL, 0, mixerSWPeakUsbL, 1);
AudioConnection          patchCord116(ampMasterOutI2sL, 0, i2sOUT, 0);
AudioConnection          patchCord117(ampMasterOutI2sL, 0, mixerSWPeakI2sL, 0);
AudioConnection          patchCord118(ampMasterOutI2sR, 0, i2sOUT, 1);
AudioConnection          patchCord119(ampMasterOutI2sR, 0, mixerSWPeakI2sR, 0);
AudioConnection          patchCord120(ampMasterOutUsbL, 0, usbOUT, 0);
AudioConnection          patchCord121(ampMasterOutUsbL, 0, mixerSWPeakUsbL, 0);
AudioConnection          patchCord122(ampMasterOutUsbR, 0, usbOUT, 1);
AudioConnection          patchCord123(ampMasterOutUsbR, 0, mixerSWPeakUsbR, 0);
AudioConnection          patchCord124(mixerSWPeakI2sL, peakI2sL);
AudioConnection          patchCord125(mixerSWPeakI2sR, peakI2sR);
AudioConnection          patchCord126(mixerSWPeakUsbR, peakUsbR);
AudioConnection          patchCord127(mixerSWPeakUsbL, peakUsbL);
AudioControlSGTL5000     sgtl5000_1;     //xy=2036.5835037231445,294.1669578552246
// GUItool: end automatically generated code
