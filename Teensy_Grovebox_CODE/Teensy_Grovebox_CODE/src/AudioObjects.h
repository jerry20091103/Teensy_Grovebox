#ifndef AUDIO_OBJECTS_H
#define AUDIO_OBJECTS_H

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
extern AudioSynthWavetable      wavetable4; //xy=207.00000762939453,1161.4546146392822
extern AudioSynthWavetable      wavetable0;     //xy=208.97747802734375,975.742753982544
extern AudioSynthWavetable      wavetable2; //xy=209.00000762939453,1065.4546127319336
extern AudioSynthWavetable      wavetable3; //xy=209.00000762939453,1112.454613685608
extern AudioSynthWavetable      wavetable6; //xy=209.00000762939453,1250.1817111968994
extern AudioSynthWavetable      wavetable1; //xy=210.00000762939453,1019.4546089172363
extern AudioSynthWavetable      wavetable7; //xy=210.00000762939453,1303.181713104248
extern AudioSynthWavetable      wavetable5; //xy=211.00000762939453,1206.1817092895508
extern AudioInputI2S            i2sIN;           //xy=409.2502212524414,554.5000600814819
extern AudioInputUSB            usbIN;           //xy=417.2501411437988,812.5000486373901
extern AudioMixer4              voiceMixer0_1; //xy=443.00001525878906,1213.1817741394043
extern AudioMixer4              voiceMixer0_0;         //xy=456.00001525878906,1043.181770324707
extern AudioAmplifier           ampI2sInR;           //xy=571.2501449584961,576.4090890884399
extern AudioAmplifier           ampI2sInL;           //xy=574.2501449584961,536.4090852737427
extern AudioAmplifier           ampUsbInR; //xy=576.2501449584961,832.5000076293945
extern AudioAmplifier           ampUsbInL; //xy=579.2501449584961,792.5000038146973
extern AudioAnalyzePeak         peakVelocity;           //xy=622.0000152587891,338.2727279663086
extern AudioMixer4              voiceMixer1_0; //xy=652.0000190734863,1142.1817741394043
extern AudioMixer4              mixerSWPeakUsbInL;  //xy=746.2501373291016,659.4090757369995
extern AudioMixer4              mixerSWPeakUsbInR; //xy=747.7955017089844,732.4090452194214
extern AudioMixer4              mixerSWPeakLmInL; //xy=758.2501983642578,393.50000286102295
extern AudioMixer4              mixerSWPeakLmInR; //xy=759.7955627441406,466.4999723434448
extern AudioAnalyzePeak         peakMixerInsR; //xy=934.977424621582,1062.4091272354126
extern AudioAnalyzePeak         peakMixerInsL; //xy=935.977424621582,1022.409125328064
extern AudioAnalyzePeak         peakLmInL; //xy=940.7047882080078,390.500036239624
extern AudioAnalyzePeak         peakLmInR; //xy=943.2501564025879,466.5000162124634
extern AudioAnalyzePeak         peakUsbInL; //xy=950.2501525878906,660.5000009536743
extern AudioAnalyzePeak         peakUsbInR; //xy=950.2501754760742,729.5000886917114
extern AudioAnalyzePeak         peakMixerLmR; //xy=1114.2501602172852,413.4999933242798
extern AudioAnalyzePeak         peakMixerLmL; //xy=1115.2501602172852,373.49999141693115
extern AudioMixer4              mixerOutI2sL;         //xy=1121.2501373291016,505.500018119812
extern AudioMixer4              mixerOutI2sR;         //xy=1123.2501373291016,586.5000314712524
extern AudioAnalyzePeak         peakMixerUsbL; //xy=1123.431983947754,740.6818256378174
extern AudioAnalyzePeak         peakMixerUsbR;  //xy=1124.431983947754,782.6818273067474
extern AudioMixer4              mixerOutUsbR; //xy=1127.250129699707,961.4999990463257
extern AudioMixer4              mixerOutUsbL; //xy=1128.2501373291016,872.4999990463257
extern AudioAmplifier           ampMasterOutI2sL;           //xy=1313.1592330932617,512.5000066757202
extern AudioAmplifier           ampMasterOutI2sR; //xy=1317.159294128418,582.5000143051147
extern AudioAmplifier           ampMasterOutUsbL; //xy=1338.1592330932617,884.4999990463257
extern AudioAmplifier           ampMasterOutUsbR; //xy=1342.1592330932617,946.5000009536743
extern AudioMixer4              mixerSWPeakI2sL;         //xy=1538.2502975463867,370.49999141693115
extern AudioMixer4              mixerSWRmsI2sL; //xy=1540.2502937316895,439.50003719329834
extern AudioMixer4              mixerSWPeakUsbL;  //xy=1540.3411178588867,758.500075340271
extern AudioMixer4              mixerSWPeakI2sR; //xy=1541.3411178588867,614.4999952316284
extern AudioMixer4              mixerSWPeakUsbR;  //xy=1541.3411178588867,1033.3182153701782
extern AudioMixer4              mixerSWRmsUsbR; //xy=1541.3411178588867,1101.3182172775269
extern AudioMixer4              mixerSWRmsUsbL; //xy=1544.3411140441895,829.5000715255737
extern AudioMixer4              mixerSWRmsI2sR; //xy=1545.3411560058594,682.5000104904175
extern AudioOutputI2S           i2sOUT;           //xy=1579.2502059936523,539.5000066757202
extern AudioOutputUSB           usbOUT;           //xy=1595.250114440918,915.5000009536743
extern AudioAnalyzePeak         peakI2sL;          //xy=1711.1594772338867,369.50000381469727
extern AudioAnalyzeRMS          rmsI2sL;           //xy=1716.159481048584,437.500039100647
extern AudioAnalyzePeak         peakUsbR; //xy=1723.159481048584,1033.5001220703125
extern AudioAnalyzeRMS          rmsUsbR; //xy=1725.1593933105469,1100.5000352859497
extern AudioAnalyzePeak         peakUsbL; //xy=1736.1593933105469,754.500075340271
extern AudioAnalyzeRMS          rmsUsbL; //xy=1737.159366607666,836.5000610351562
extern AudioAnalyzePeak         peakI2sR;          //xy=1756.1595191955566,616.5000953674316
extern AudioAnalyzeRMS          rmsI2sR;           //xy=1759.1596984863281,673.5000562667847
extern AudioConnection          patchCord1;
extern AudioConnection          patchCord2;
extern AudioConnection          patchCord3;
extern AudioConnection          patchCord4;
extern AudioConnection          patchCord5;
extern AudioConnection          patchCord6;
extern AudioConnection          patchCord7;
extern AudioConnection          patchCord8;
extern AudioConnection          patchCord9;
extern AudioConnection          patchCord10;
extern AudioConnection          patchCord11;
extern AudioConnection          patchCord12;
extern AudioConnection          patchCord13;
extern AudioConnection          patchCord14;
extern AudioConnection          patchCord15;
extern AudioConnection          patchCord16;
extern AudioConnection          patchCord17;
extern AudioConnection          patchCord18;
extern AudioConnection          patchCord19;
extern AudioConnection          patchCord20;
extern AudioConnection          patchCord21;
extern AudioConnection          patchCord22;
extern AudioConnection          patchCord23;
extern AudioConnection          patchCord24;
extern AudioConnection          patchCord25;
extern AudioConnection          patchCord26;
extern AudioConnection          patchCord27;
extern AudioConnection          patchCord28;
extern AudioConnection          patchCord29;
extern AudioConnection          patchCord30;
extern AudioConnection          patchCord31;
extern AudioConnection          patchCord32;
extern AudioConnection          patchCord33;
extern AudioConnection          patchCord34;
extern AudioConnection          patchCord35;
extern AudioConnection          patchCord36;
extern AudioConnection          patchCord37;
extern AudioConnection          patchCord38;
extern AudioConnection          patchCord39;
extern AudioConnection          patchCord40;
extern AudioConnection          patchCord41;
extern AudioConnection          patchCord42;
extern AudioConnection          patchCord43;
extern AudioConnection          patchCord44;
extern AudioConnection          patchCord45;
extern AudioConnection          patchCord46;
extern AudioConnection          patchCord47;
extern AudioConnection          patchCord48;
extern AudioConnection          patchCord49;
extern AudioConnection          patchCord50;
extern AudioConnection          patchCord51;
extern AudioConnection          patchCord52;
extern AudioConnection          patchCord53;
extern AudioConnection          patchCord54;
extern AudioConnection          patchCord55;
extern AudioConnection          patchCord56;
extern AudioConnection          patchCord57;
extern AudioConnection          patchCord58;
extern AudioConnection          patchCord59;
extern AudioConnection          patchCord60;
extern AudioConnection          patchCord61;
extern AudioConnection          patchCord62;
extern AudioConnection          patchCord63;
extern AudioConnection          patchCord64;
extern AudioConnection          patchCord65;
extern AudioConnection          patchCord66;
extern AudioConnection          patchCord67;
extern AudioConnection          patchCord68;
extern AudioConnection          patchCord69;
extern AudioConnection          patchCord70;
extern AudioConnection          patchCord71;
extern AudioConnection          patchCord72;
extern AudioConnection          patchCord73;
extern AudioConnection          patchCord74;
extern AudioConnection          patchCord75;
extern AudioConnection          patchCord76;
extern AudioConnection          patchCord77;
extern AudioControlSGTL5000     sgtl5000_1;     //xy=481.25014877319336,422.5000514984131
// GUItool: end automatically generated code


#endif