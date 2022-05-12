#ifndef AUDIO_OBJECTS_H
#define AUDIO_OBJECTS_H

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
extern AudioInputI2S            i2sIN;           //xy=188.00008392333984,332.00007247924805
extern AudioInputUSB            usbIN;           //xy=196.00000381469727,590.0000610351562
extern AudioAmplifier           ampI2sInR;           //xy=350.00000762939453,353.90910148620605
extern AudioAmplifier           ampI2sInL;           //xy=353.00000762939453,313.9090976715088
extern AudioAmplifier           ampUsbInR; //xy=355.00000762939453,610.0000200271606
extern AudioAmplifier           ampUsbInL; //xy=358.00000762939453,570.0000162124634
extern AudioMixer4              mixerSWPeakUsbInL;  //xy=525,436.9090881347656
extern AudioMixer4              mixerSWPeakUsbInR; //xy=526.5453643798828,509.9090576171875
extern AudioMixer4              mixerSWPeakLmInL; //xy=537.0000610351562,171.00001525878906
extern AudioMixer4              mixerSWPeakLmInR; //xy=538.5454254150391,243.99998474121094
extern AudioAnalyzePeak         peakLmInL; //xy=719.4546508789062,168.00004863739014
extern AudioAnalyzePeak         peakLmInR; //xy=722.0000190734863,244.0000286102295
extern AudioAnalyzePeak         peakUsbInL; //xy=729.0000152587891,438.00001335144043
extern AudioAnalyzePeak         peakUsbInR; //xy=729.0000381469727,507.00010108947754
extern AudioAnalyzePeak         peakMixerLmR; //xy=893.0000228881836,191.0000057220459
extern AudioAnalyzePeak         peakMixerLmL; //xy=894.0000228881836,151.00000381469727
extern AudioMixer4              mixerOutI2sL;         //xy=900,283.0000305175781
extern AudioMixer4              mixerOutI2sR;         //xy=902,364.00004386901855
extern AudioAnalyzePeak         peakMixerUsbL; //xy=902.1818466186523,518.1818380355835
extern AudioAnalyzePeak         peakMixerUsbR;  //xy=903.1818466186523,560.1818397045135
extern AudioMixer4              mixerOutUsbR; //xy=905.9999923706055,739.0000114440918
extern AudioMixer4              mixerOutUsbL; //xy=907,650.0000114440918
extern AudioAmplifier           ampMasterOutI2sL;           //xy=1091.9090957641602,290.0000190734863
extern AudioAmplifier           ampMasterOutI2sR; //xy=1095.9091567993164,360.00002670288086
extern AudioAmplifier           ampMasterOutUsbL; //xy=1116.9090957641602,662.0000114440918
extern AudioAmplifier           ampMasterOutUsbR; //xy=1120.9090957641602,724.0000133514404
extern AudioMixer4              mixerSWPeakI2sL;         //xy=1317.0001602172852,148.00000381469727
extern AudioMixer4              mixerSWRmsI2sL; //xy=1319.000156402588,217.00004959106445
extern AudioMixer4              mixerSWPeakUsbL;  //xy=1319.0909805297852,536.0000877380371
extern AudioMixer4              mixerSWPeakI2sR; //xy=1320.0909805297852,392.00000762939453
extern AudioMixer4              mixerSWPeakUsbR;  //xy=1320.0909805297852,810.8182277679443
extern AudioMixer4              mixerSWRmsUsbR; //xy=1320.0909805297852,878.818229675293
extern AudioMixer4              mixerSWRmsUsbL; //xy=1323.090976715088,607.0000839233398
extern AudioMixer4              mixerSWRmsI2sR; //xy=1324.0910186767578,460.0000228881836
extern AudioOutputI2S           i2sOUT;           //xy=1358.0000686645508,317.0000190734863
extern AudioOutputUSB           usbOUT;           //xy=1373.9999771118164,693.0000133514404
extern AudioAnalyzePeak         peakI2sL;          //xy=1489.9093399047852,147.00001621246338
extern AudioAnalyzeRMS          rmsI2sL;           //xy=1494.9093437194824,215.0000514984131
extern AudioAnalyzePeak         peakUsbR; //xy=1501.9093437194824,811.0001344680786
extern AudioAnalyzeRMS          rmsUsbR; //xy=1503.9092559814453,878.0000476837158
extern AudioAnalyzePeak         peakUsbL; //xy=1514.9092559814453,532.0000877380371
extern AudioAnalyzeRMS          rmsUsbL; //xy=1515.9092292785645,614.0000734329224
extern AudioAnalyzePeak         peakI2sR;          //xy=1534.909381866455,394.00010776519775
extern AudioAnalyzeRMS          rmsI2sR;           //xy=1537.9095611572266,451.0000686645508
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
extern AudioControlSGTL5000     sgtl5000_1;     //xy=260.0000114440918,200.0000638961792
// GUItool: end automatically generated code


#endif