#include <AudioObjects.h>

// GUItool: begin automatically generated code
AudioSynthWavetable      wavetable4; //xy=207.00000762939453,1161.4546146392822
AudioSynthWavetable      wavetable0;     //xy=208.97747802734375,975.742753982544
AudioSynthWavetable      wavetable2; //xy=209.00000762939453,1065.4546127319336
AudioSynthWavetable      wavetable3; //xy=209.00000762939453,1112.454613685608
AudioSynthWavetable      wavetable6; //xy=209.00000762939453,1250.1817111968994
AudioSynthWavetable      wavetable1; //xy=210.00000762939453,1019.4546089172363
AudioSynthWavetable      wavetable7; //xy=210.00000762939453,1303.181713104248
AudioSynthWavetable      wavetable5; //xy=211.00000762939453,1206.1817092895508
AudioInputI2S            i2sIN;           //xy=409.2502212524414,554.5000600814819
AudioInputUSB            usbIN;           //xy=417.2501411437988,812.5000486373901
AudioMixer4              voiceMixer0_1; //xy=443.00001525878906,1213.1817741394043
AudioMixer4              voiceMixer0_0;         //xy=456.00001525878906,1043.181770324707
AudioAmplifier           ampI2sInR;           //xy=571.2501449584961,576.4090890884399
AudioAmplifier           ampI2sInL;           //xy=574.2501449584961,536.4090852737427
AudioAmplifier           ampUsbInR; //xy=576.2501449584961,832.5000076293945
AudioAmplifier           ampUsbInL; //xy=579.2501449584961,792.5000038146973
AudioAnalyzePeak         rmsVelocity;           //xy=622.0000152587891,338.2727279663086
AudioMixer4              voiceMixer1_0; //xy=652.0000190734863,1142.1817741394043
AudioMixer4              mixerSWPeakUsbInL;  //xy=746.2501373291016,659.4090757369995
AudioMixer4              mixerSWPeakUsbInR; //xy=747.7955017089844,732.4090452194214
AudioMixer4              mixerSWPeakLmInL; //xy=758.2501983642578,393.50000286102295
AudioMixer4              mixerSWPeakLmInR; //xy=759.7955627441406,466.4999723434448
AudioAnalyzePeak         peakMixerInsR; //xy=934.977424621582,1062.4091272354126
AudioAnalyzePeak         peakMixerInsL; //xy=935.977424621582,1022.409125328064
AudioAnalyzePeak         peakLmInL; //xy=940.7047882080078,390.500036239624
AudioAnalyzePeak         peakLmInR; //xy=943.2501564025879,466.5000162124634
AudioAnalyzePeak         peakUsbInL; //xy=950.2501525878906,660.5000009536743
AudioAnalyzePeak         peakUsbInR; //xy=950.2501754760742,729.5000886917114
AudioAnalyzePeak         peakMixerLmR; //xy=1114.2501602172852,413.4999933242798
AudioAnalyzePeak         peakMixerLmL; //xy=1115.2501602172852,373.49999141693115
AudioMixer4              mixerOutI2sL;         //xy=1121.2501373291016,505.500018119812
AudioMixer4              mixerOutI2sR;         //xy=1123.2501373291016,586.5000314712524
AudioAnalyzePeak         peakMixerUsbL; //xy=1123.431983947754,740.6818256378174
AudioAnalyzePeak         peakMixerUsbR;  //xy=1124.431983947754,782.6818273067474
AudioMixer4              mixerOutUsbR; //xy=1127.250129699707,961.4999990463257
AudioMixer4              mixerOutUsbL; //xy=1128.2501373291016,872.4999990463257
AudioAmplifier           ampMasterOutI2sL;           //xy=1313.1592330932617,512.5000066757202
AudioAmplifier           ampMasterOutI2sR; //xy=1317.159294128418,582.5000143051147
AudioAmplifier           ampMasterOutUsbL; //xy=1338.1592330932617,884.4999990463257
AudioAmplifier           ampMasterOutUsbR; //xy=1342.1592330932617,946.5000009536743
AudioMixer4              mixerSWPeakI2sL;         //xy=1538.2502975463867,370.49999141693115
AudioMixer4              mixerSWRmsI2sL; //xy=1540.2502937316895,439.50003719329834
AudioMixer4              mixerSWPeakUsbL;  //xy=1540.3411178588867,758.500075340271
AudioMixer4              mixerSWPeakI2sR; //xy=1541.3411178588867,614.4999952316284
AudioMixer4              mixerSWPeakUsbR;  //xy=1541.3411178588867,1033.3182153701782
AudioMixer4              mixerSWRmsUsbR; //xy=1541.3411178588867,1101.3182172775269
AudioMixer4              mixerSWRmsUsbL; //xy=1544.3411140441895,829.5000715255737
AudioMixer4              mixerSWRmsI2sR; //xy=1545.3411560058594,682.5000104904175
AudioOutputI2S           i2sOUT;           //xy=1579.2502059936523,539.5000066757202
AudioOutputUSB           usbOUT;           //xy=1595.250114440918,915.5000009536743
AudioAnalyzePeak         peakI2sL;          //xy=1711.1594772338867,369.50000381469727
AudioAnalyzeRMS          rmsI2sL;           //xy=1716.159481048584,437.500039100647
AudioAnalyzePeak         peakUsbR; //xy=1723.159481048584,1033.5001220703125
AudioAnalyzeRMS          rmsUsbR; //xy=1725.1593933105469,1100.5000352859497
AudioAnalyzePeak         peakUsbL; //xy=1736.1593933105469,754.500075340271
AudioAnalyzeRMS          rmsUsbL; //xy=1737.159366607666,836.5000610351562
AudioAnalyzePeak         peakI2sR;          //xy=1756.1595191955566,616.5000953674316
AudioAnalyzeRMS          rmsI2sR;           //xy=1759.1596984863281,673.5000562667847
AudioConnection          patchCord1(wavetable4, 0, voiceMixer0_1, 0);
AudioConnection          patchCord2(wavetable0, 0, voiceMixer0_0, 0);
AudioConnection          patchCord3(wavetable2, 0, voiceMixer0_0, 2);
AudioConnection          patchCord4(wavetable3, 0, voiceMixer0_0, 3);
AudioConnection          patchCord5(wavetable6, 0, voiceMixer0_1, 2);
AudioConnection          patchCord6(wavetable1, 0, voiceMixer0_0, 1);
AudioConnection          patchCord7(wavetable7, 0, voiceMixer0_1, 3);
AudioConnection          patchCord8(wavetable5, 0, voiceMixer0_1, 1);
AudioConnection          patchCord9(i2sIN, 0, ampI2sInL, 0);
AudioConnection          patchCord10(i2sIN, 0, mixerSWPeakLmInL, 1);
AudioConnection          patchCord11(i2sIN, 0, rmsVelocity, 0);
AudioConnection          patchCord12(i2sIN, 1, ampI2sInR, 0);
AudioConnection          patchCord13(i2sIN, 1, mixerSWPeakLmInR, 1);
AudioConnection          patchCord14(usbIN, 0, ampUsbInL, 0);
AudioConnection          patchCord15(usbIN, 0, mixerSWPeakUsbInL, 1);
AudioConnection          patchCord16(usbIN, 1, ampUsbInR, 0);
AudioConnection          patchCord17(usbIN, 1, mixerSWPeakUsbInR, 1);
AudioConnection          patchCord18(voiceMixer0_1, 0, voiceMixer1_0, 1);
AudioConnection          patchCord19(voiceMixer0_0, 0, voiceMixer1_0, 0);
AudioConnection          patchCord20(ampI2sInR, 0, mixerSWPeakLmInR, 0);
AudioConnection          patchCord21(ampI2sInR, 0, mixerOutI2sR, 0);
AudioConnection          patchCord22(ampI2sInR, 0, mixerOutUsbR, 0);
AudioConnection          patchCord23(ampI2sInR, peakMixerLmR);
AudioConnection          patchCord24(ampI2sInL, 0, mixerSWPeakLmInL, 0);
AudioConnection          patchCord25(ampI2sInL, 0, mixerOutI2sL, 0);
AudioConnection          patchCord26(ampI2sInL, 0, mixerOutUsbL, 0);
AudioConnection          patchCord27(ampI2sInL, peakMixerLmL);
AudioConnection          patchCord28(ampUsbInR, 0, mixerSWPeakUsbInR, 0);
AudioConnection          patchCord29(ampUsbInR, 0, mixerOutI2sR, 1);
AudioConnection          patchCord30(ampUsbInR, 0, mixerOutUsbR, 1);
AudioConnection          patchCord31(ampUsbInR, peakMixerUsbR);
AudioConnection          patchCord32(ampUsbInL, 0, mixerSWPeakUsbInL, 0);
AudioConnection          patchCord33(ampUsbInL, 0, mixerOutI2sL, 1);
AudioConnection          patchCord34(ampUsbInL, 0, mixerOutUsbL, 1);
AudioConnection          patchCord35(ampUsbInL, peakMixerUsbL);
AudioConnection          patchCord36(voiceMixer1_0, peakMixerInsL);
AudioConnection          patchCord37(voiceMixer1_0, peakMixerInsR);
AudioConnection          patchCord38(voiceMixer1_0, 0, mixerOutUsbR, 2);
AudioConnection          patchCord39(voiceMixer1_0, 0, mixerOutUsbL, 2);
AudioConnection          patchCord40(voiceMixer1_0, 0, mixerOutI2sR, 2);
AudioConnection          patchCord41(voiceMixer1_0, 0, mixerOutI2sL, 2);
AudioConnection          patchCord42(mixerSWPeakUsbInL, peakUsbInL);
AudioConnection          patchCord43(mixerSWPeakUsbInR, peakUsbInR);
AudioConnection          patchCord44(mixerSWPeakLmInL, peakLmInL);
AudioConnection          patchCord45(mixerSWPeakLmInR, peakLmInR);
AudioConnection          patchCord46(mixerOutI2sL, ampMasterOutI2sL);
AudioConnection          patchCord47(mixerOutI2sL, 0, mixerSWPeakI2sL, 1);
AudioConnection          patchCord48(mixerOutI2sL, 0, mixerSWRmsI2sL, 1);
AudioConnection          patchCord49(mixerOutI2sR, ampMasterOutI2sR);
AudioConnection          patchCord50(mixerOutI2sR, 0, mixerSWPeakI2sR, 1);
AudioConnection          patchCord51(mixerOutI2sR, 0, mixerSWRmsI2sR, 1);
AudioConnection          patchCord52(mixerOutUsbR, ampMasterOutUsbR);
AudioConnection          patchCord53(mixerOutUsbR, 0, mixerSWPeakUsbR, 1);
AudioConnection          patchCord54(mixerOutUsbR, 0, mixerSWRmsUsbR, 1);
AudioConnection          patchCord55(mixerOutUsbL, ampMasterOutUsbL);
AudioConnection          patchCord56(mixerOutUsbL, 0, mixerSWPeakUsbL, 1);
AudioConnection          patchCord57(mixerOutUsbL, 0, mixerSWRmsUsbL, 1);
AudioConnection          patchCord58(ampMasterOutI2sL, 0, i2sOUT, 0);
AudioConnection          patchCord59(ampMasterOutI2sL, 0, mixerSWRmsI2sL, 0);
AudioConnection          patchCord60(ampMasterOutI2sL, 0, mixerSWPeakI2sL, 0);
AudioConnection          patchCord61(ampMasterOutI2sR, 0, i2sOUT, 1);
AudioConnection          patchCord62(ampMasterOutI2sR, 0, mixerSWPeakI2sR, 0);
AudioConnection          patchCord63(ampMasterOutI2sR, 0, mixerSWRmsI2sR, 0);
AudioConnection          patchCord64(ampMasterOutUsbL, 0, usbOUT, 0);
AudioConnection          patchCord65(ampMasterOutUsbL, 0, mixerSWPeakUsbL, 0);
AudioConnection          patchCord66(ampMasterOutUsbL, 0, mixerSWRmsUsbL, 0);
AudioConnection          patchCord67(ampMasterOutUsbR, 0, usbOUT, 1);
AudioConnection          patchCord68(ampMasterOutUsbR, 0, mixerSWPeakUsbR, 0);
AudioConnection          patchCord69(ampMasterOutUsbR, 0, mixerSWRmsUsbR, 0);
AudioConnection          patchCord70(mixerSWPeakI2sL, peakI2sL);
AudioConnection          patchCord71(mixerSWRmsI2sL, rmsI2sL);
AudioConnection          patchCord72(mixerSWPeakUsbL, peakUsbL);
AudioConnection          patchCord73(mixerSWPeakI2sR, peakI2sR);
AudioConnection          patchCord74(mixerSWPeakUsbR, peakUsbR);
AudioConnection          patchCord75(mixerSWRmsUsbR, rmsUsbR);
AudioConnection          patchCord76(mixerSWRmsUsbL, rmsUsbL);
AudioConnection          patchCord77(mixerSWRmsI2sR, rmsI2sR);
AudioControlSGTL5000     sgtl5000_1;     //xy=481.25014877319336,422.5000514984131
// GUItool: end automatically generated code

