#ifndef AUDIO_OBJECTS_H
#define AUDIO_OBJECTS_H

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
extern AudioSynthNoiseWhite     noise5; //xy=544.5557022094727,1354.9799671173096
extern AudioSynthNoiseWhite     noise4; //xy=548.6668395996094,1164.4950256347656
extern AudioSynthNoiseWhite     noise3; //xy=550.0001525878906,948.1010875701904
extern AudioSynthNoiseWhite     noise6; //xy=547.889030456543,1542.0406131744385
extern AudioSynthNoiseWhite     noise7; //xy=548.8889617919922,1739.1517248153687
extern AudioSynthNoiseWhite     noise2; //xy=555.6668281555176,759.3940696716309
extern AudioSynthNoiseWhite     noise1;  //xy=556.7779159545898,566.2425804138184
extern AudioSynthNoiseWhite     noise0;         //xy=560.7778930664062,385.1721200942993
extern AudioSynthWaveform       waveform5_1; //xy=562.5556716918945,1316.1617908477783
extern AudioSynthWaveform       waveform5_0; //xy=563.5557098388672,1278.0708866119385
extern AudioSynthWaveform       waveform6_1; //xy=562.8889999389648,1502.1315670013428
extern AudioSynthWaveform       waveform6_0; //xy=563.8890380859375,1464.040662765503
extern AudioSynthWaveform       waveform3_1; //xy=568.000129699707,912.101110458374
extern AudioSynthWaveform       waveform3_0; //xy=569.0001678466797,874.0102062225342
extern AudioSynthWaveform       waveform7_1; //xy=567.8889274597168,1701.242567062378
extern AudioSynthWaveform       waveform4_1;  //xy=570.6668090820312,1126.6768436431885
extern AudioSynthWaveform       waveform7_0; //xy=568.8889656066895,1663.151662826538
extern AudioSynthWaveform       waveform4_0; //xy=571.6668472290039,1088.5859394073486
extern AudioSynthWaveform       waveform0_0; //xy=577.7779388427734,312.89918518066406
extern AudioSynthWaveform       waveform0_1; //xy=578.7779159545898,348.99000549316406
extern AudioSynthWaveform       waveform2_0; //xy=577.6668319702148,684.2122402191162
extern AudioSynthWaveform       waveform2_1; //xy=577.666805267334,722.3030605316162
extern AudioSynthWaveform       waveform1_0; //xy=578.7779350280762,490.8788814544678
extern AudioSynthWaveform       waveform1_1; //xy=578.7779006958008,528.9697036743164
extern AudioMixer4              oscMixer5; //xy=721.5556869506836,1341.1616134643555
extern AudioMixer4              oscMixer4; //xy=724.6668243408203,1145.6767539978027
extern AudioMixer4              oscMixer6; //xy=724.8889999389648,1530.1315326690674
extern AudioMixer4              oscMixer3; //xy=730.0001220703125,936.1010799407959
extern AudioMixer4              oscMixer7; //xy=728.8889274597168,1726.242597579956
extern AudioMixer4              oscMixer0;         //xy=738.7779006958008,367.9900074005127
extern AudioMixer4              oscMixer1; //xy=738.7779006958008,544.9697456359863
extern AudioMixer4              oscMixer2; //xy=740.6668395996094,745.3030586242676
extern AudioFilterLadder        ladder1; //xy=897.8284072875977,545.3535995483398
extern AudioFilterLadder        ladder6; //xy=901.6061058044434,1513.2019805908203
extern AudioFilterLadder        ladder0;        //xy=909.1615867614746,355.24245834350586
extern AudioFilterLadder        ladder2; //xy=909.3838863372803,741.373722076416
extern AudioFilterLadder        ladder5; //xy=907.4948616027832,1319.7373447418213
extern AudioFilterLadder        ladder3; //xy=911.3837966918945,931.5757389068604
extern AudioFilterLadder        ladder7; //xy=909.4948616027832,1706.989917755127
extern AudioFilterLadder        ladder4; //xy=913.4948654174805,1133.605978012085
extern AudioEffectEnvelope      ampEnvelope6; //xy=1089.8890991210938,1472.1315803527832
extern AudioEffectEnvelope      ampEnvelope1; //xy=1094.778034210205,528.1517162322998
extern AudioEffectEnvelope      ampEnvelope0;      //xy=1100.7780418395996,355.26272201538086
extern AudioEffectEnvelope      ampEnvelope5; //xy=1100.5558242797852,1275.8890647888184
extern AudioEffectEnvelope      ampEnvelope7; //xy=1099.8890991210938,1651.0607643127441
extern AudioEffectEnvelope      ampEnvelope4; //xy=1109.6670684814453,1110.4040069580078
extern AudioEffectEnvelope      ampEnvelope3; //xy=1115.000244140625,901.0101318359375
extern AudioSynthWavetable      wavetable3; //xy=1116.5717544555664,827.0579061508179
extern AudioEffectEnvelope      ampEnvelope2; //xy=1119.6668853759766,708.3031005859375
extern AudioSynthWavetable      wavetable2; //xy=1120.6828842163086,645.7244892120361
extern AudioSynthWavetable      wavetable6; //xy=1118.4606018066406,1387.5630340576172
extern AudioSynthWavetable      wavetable0;     //xy=1123.5490760803223,289.4571723937988
extern AudioSynthWavetable      wavetable7; //xy=1118.5715713500977,1589.2296047210693
extern AudioSynthWavetable      wavetable1; //xy=1126.7940063476562,476.2801914215088
extern AudioSynthWavetable      wavetable5; //xy=1129.1272010803223,1211.340612411499
extern AudioSynthWavetable      wavetable4; //xy=1131.3494491577148,1034.0579090118408
extern AudioMixer4              voiceSwitch5; //xy=1285.0001678466797,1255.1821537017822
extern AudioMixer4              voiceSwitch6; //xy=1290.0001678466797,1443.182336807251
extern AudioMixer4              voiceSwitch7; //xy=1292.3334999084473,1627.2935428619385
extern AudioMixer4              voiceSwitch1; //xy=1297.0001258850098,534.0909633636475
extern AudioMixer4              voiceSwitch2; //xy=1297.0001258850098,700.0910129547119
extern AudioMixer4              voiceSwitch3; //xy=1300.0001678466797,889.1820392608643
extern AudioMixer4              voiceSwitch4; //xy=1301.0001678466797,1086.1820087432861
extern AudioMixer4              voiceSwitch0; //xy=1304.0001220703125,337.0909614562988
extern AudioMixer4              voiceMixer0_1; //xy=1526.5715980529785,1337.8959293365479
extern AudioMixer4              voiceMixer0_0;         //xy=1529.57177734375,604.8959693908691
extern AudioMixer4              voiceMixer1_0; //xy=1732.7938232421875,932.0073184967041
extern AudioFilterBiquad        freeverbBiquadL;        //xy=1997.7663955688477,983.4156684875488
extern AudioFilterBiquad        freeverbBiquadR; //xy=1998.7663879394531,1018.4156694412231
extern AudioMixer4              freeverbMixerL; //xy=2012.9756317138672,1083.7852382659912
extern AudioMixer4              freeverbMixerR; //xy=2013.610496520996,1150.7015399932861
extern AudioInputI2S            i2sIN;           //xy=2063.583610534668,459.166955947876
extern AudioInputUSB            usbIN;           //xy=2071.5835304260254,717.1669445037842
extern AudioAmplifier           ampI2sInR;           //xy=2225.5835342407227,481.075984954834
extern AudioAmplifier           ampI2sInL;           //xy=2228.5835342407227,441.0759811401367
extern AudioAmplifier           ampUsbInR; //xy=2230.5835342407227,737.1669034957886
extern AudioAmplifier           ampUsbInL; //xy=2233.5835342407227,697.1668996810913
extern AudioAnalyzePeak         peakVelocity;          //xy=2256.3334045410156,226.48508167266846
extern AudioAmplifier           ampInsOutL;           //xy=2376.2944412231445,1041.6020164489746
extern AudioAmplifier           ampInsOutR; //xy=2376.476261138916,1082.4201107025146
extern AudioMixer4              mixerSWPeakUsbInL;  //xy=2400.583526611328,564.0759716033936
extern AudioMixer4              mixerSWPeakUsbInR; //xy=2402.128890991211,637.0759410858154
extern AudioMixer4              mixerSWPeakLmInL; //xy=2412.5835876464844,298.166898727417
extern AudioMixer4              mixerSWPeakLmInR; //xy=2414.128952026367,371.16686820983887
extern AudioAnalyzePeak         peakMixerInsL; //xy=2536.9775390625,910.4093418121338
extern AudioAnalyzePeak         peakMixerInsR; //xy=2548.1998443603516,952.6316204071045
extern AudioAnalyzePeak         peakLmInL; //xy=2595.0381774902344,295.16693210601807
extern AudioAnalyzePeak         peakLmInR; //xy=2597.5835456848145,371.1669120788574
extern AudioAnalyzePeak         peakUsbInL; //xy=2604.583541870117,565.1668968200684
extern AudioAnalyzePeak         peakUsbInR; //xy=2604.583564758301,634.1669845581055
extern AudioAnalyzePeak         peakMixerLmR; //xy=2768.5835494995117,318.1668891906738
extern AudioAnalyzePeak         peakMixerLmL; //xy=2769.5835494995117,278.1668872833252
extern AudioMixer4              mixerOutI2sL;         //xy=2775.583526611328,410.16691398620605
extern AudioMixer4              mixerOutI2sR;         //xy=2777.583526611328,491.1669273376465
extern AudioAnalyzePeak         peakMixerUsbL; //xy=2777.7653732299805,645.3487215042114
extern AudioAnalyzePeak         peakMixerUsbR;  //xy=2778.7653732299805,687.3487231731415
extern AudioMixer4              mixerOutUsbR; //xy=2781.5835189819336,866.1668949127197
extern AudioMixer4              mixerOutUsbL; //xy=2782.583526611328,777.1668949127197
extern AudioAmplifier           ampMasterOutI2sL;           //xy=2967.4926223754883,417.16690254211426
extern AudioAmplifier           ampMasterOutI2sR; //xy=2971.4926834106445,487.1669101715088
extern AudioAmplifier           ampMasterOutUsbL; //xy=2992.4926223754883,789.1668949127197
extern AudioAmplifier           ampMasterOutUsbR; //xy=2996.4926223754883,851.1668968200684
extern AudioMixer4              mixerSWPeakI2sL;         //xy=3188.5836334228516,366.1669063568115
extern AudioMixer4              mixerSWPeakI2sR; //xy=3195.6745071411133,519.1668910980225
extern AudioMixer4              mixerSWPeakUsbR;  //xy=3201.6745376586914,917.9852237701416
extern AudioMixer4              mixerSWPeakUsbL;  //xy=3210.6748123168945,708.1670799255371
extern AudioOutputI2S           i2sOUT;           //xy=3233.583595275879,444.16690254211426
extern AudioOutputUSB           usbOUT;           //xy=3249.5835037231445,820.1668968200684
extern AudioAnalyzePeak         peakI2sL;          //xy=3361.4928131103516,365.16691875457764
extern AudioAnalyzePeak         peakI2sR;          //xy=3370.4930877685547,520.1670475006104
extern AudioAnalyzePeak         peakUsbR; //xy=3383.4929008483887,918.1671304702759
extern AudioAnalyzePeak         peakUsbL; //xy=3401.4930877685547,709.1671257019043
extern AudioControlSGTL5000     sgtl5000_1;     //xy=2036.5835037231445,294.1669578552246
// GUItool: end automatically generated code
#endif