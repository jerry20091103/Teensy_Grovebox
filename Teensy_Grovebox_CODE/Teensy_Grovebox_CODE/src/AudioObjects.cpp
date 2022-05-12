#include <AudioObjects.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2sIN;           //xy=188.00008392333984,332.00007247924805
AudioInputUSB            usbIN;           //xy=196.00000381469727,590.0000610351562
AudioAmplifier           ampI2sInR;           //xy=350.00000762939453,353.90910148620605
AudioAmplifier           ampI2sInL;           //xy=353.00000762939453,313.9090976715088
AudioAmplifier           ampUsbInR; //xy=355.00000762939453,610.0000200271606
AudioAmplifier           ampUsbInL; //xy=358.00000762939453,570.0000162124634
AudioMixer4              mixerSWPeakUsbInL;  //xy=525,436.9090881347656
AudioMixer4              mixerSWPeakUsbInR; //xy=526.5453643798828,509.9090576171875
AudioMixer4              mixerSWPeakLmInL; //xy=537.0000610351562,171.00001525878906
AudioMixer4              mixerSWPeakLmInR; //xy=538.5454254150391,243.99998474121094
AudioAnalyzePeak         peakLmInL; //xy=719.4546508789062,168.00004863739014
AudioAnalyzePeak         peakLmInR; //xy=722.0000190734863,244.0000286102295
AudioAnalyzePeak         peakUsbInL; //xy=729.0000152587891,438.00001335144043
AudioAnalyzePeak         peakUsbInR; //xy=729.0000381469727,507.00010108947754
AudioAnalyzePeak         peakMixerLmR; //xy=893.0000228881836,191.0000057220459
AudioAnalyzePeak         peakMixerLmL; //xy=894.0000228881836,151.00000381469727
AudioMixer4              mixerOutI2sL;         //xy=900,283.0000305175781
AudioMixer4              mixerOutI2sR;         //xy=902,364.00004386901855
AudioAnalyzePeak         peakMixerUsbL; //xy=902.1818466186523,518.1818380355835
AudioAnalyzePeak         peakMixerUsbR;  //xy=903.1818466186523,560.1818397045135
AudioMixer4              mixerOutUsbR; //xy=905.9999923706055,739.0000114440918
AudioMixer4              mixerOutUsbL; //xy=907,650.0000114440918
AudioAmplifier           ampMasterOutI2sL;           //xy=1091.9090957641602,290.0000190734863
AudioAmplifier           ampMasterOutI2sR; //xy=1095.9091567993164,360.00002670288086
AudioAmplifier           ampMasterOutUsbL; //xy=1116.9090957641602,662.0000114440918
AudioAmplifier           ampMasterOutUsbR; //xy=1120.9090957641602,724.0000133514404
AudioMixer4              mixerSWPeakI2sL;         //xy=1317.0001602172852,148.00000381469727
AudioMixer4              mixerSWRmsI2sL; //xy=1319.000156402588,217.00004959106445
AudioMixer4              mixerSWPeakUsbL;  //xy=1319.0909805297852,536.0000877380371
AudioMixer4              mixerSWPeakI2sR; //xy=1320.0909805297852,392.00000762939453
AudioMixer4              mixerSWPeakUsbR;  //xy=1320.0909805297852,810.8182277679443
AudioMixer4              mixerSWRmsUsbR; //xy=1320.0909805297852,878.818229675293
AudioMixer4              mixerSWRmsUsbL; //xy=1323.090976715088,607.0000839233398
AudioMixer4              mixerSWRmsI2sR; //xy=1324.0910186767578,460.0000228881836
AudioOutputI2S           i2sOUT;           //xy=1358.0000686645508,317.0000190734863
AudioOutputUSB           usbOUT;           //xy=1373.9999771118164,693.0000133514404
AudioAnalyzePeak         peakI2sL;          //xy=1489.9093399047852,147.00001621246338
AudioAnalyzeRMS          rmsI2sL;           //xy=1494.9093437194824,215.0000514984131
AudioAnalyzePeak         peakUsbR; //xy=1501.9093437194824,811.0001344680786
AudioAnalyzeRMS          rmsUsbR; //xy=1503.9092559814453,878.0000476837158
AudioAnalyzePeak         peakUsbL; //xy=1514.9092559814453,532.0000877380371
AudioAnalyzeRMS          rmsUsbL; //xy=1515.9092292785645,614.0000734329224
AudioAnalyzePeak         peakI2sR;          //xy=1534.909381866455,394.00010776519775
AudioAnalyzeRMS          rmsI2sR;           //xy=1537.9095611572266,451.0000686645508
AudioConnection          patchCord1(i2sIN, 0, ampI2sInL, 0);
AudioConnection          patchCord2(i2sIN, 0, mixerSWPeakLmInL, 1);
AudioConnection          patchCord3(i2sIN, 1, ampI2sInR, 0);
AudioConnection          patchCord4(i2sIN, 1, mixerSWPeakLmInR, 1);
AudioConnection          patchCord5(usbIN, 0, ampUsbInL, 0);
AudioConnection          patchCord6(usbIN, 0, mixerSWPeakUsbInL, 1);
AudioConnection          patchCord7(usbIN, 1, ampUsbInR, 0);
AudioConnection          patchCord8(usbIN, 1, mixerSWPeakUsbInR, 1);
AudioConnection          patchCord9(ampI2sInR, 0, mixerSWPeakLmInR, 0);
AudioConnection          patchCord10(ampI2sInR, 0, mixerOutI2sR, 0);
AudioConnection          patchCord11(ampI2sInR, 0, mixerOutUsbR, 0);
AudioConnection          patchCord12(ampI2sInR, peakMixerLmR);
AudioConnection          patchCord13(ampI2sInL, 0, mixerSWPeakLmInL, 0);
AudioConnection          patchCord14(ampI2sInL, 0, mixerOutI2sL, 0);
AudioConnection          patchCord15(ampI2sInL, 0, mixerOutUsbL, 0);
AudioConnection          patchCord16(ampI2sInL, peakMixerLmL);
AudioConnection          patchCord17(ampUsbInR, 0, mixerSWPeakUsbInR, 0);
AudioConnection          patchCord18(ampUsbInR, 0, mixerOutI2sR, 1);
AudioConnection          patchCord19(ampUsbInR, 0, mixerOutUsbR, 1);
AudioConnection          patchCord20(ampUsbInR, peakMixerUsbR);
AudioConnection          patchCord21(ampUsbInL, 0, mixerSWPeakUsbInL, 0);
AudioConnection          patchCord22(ampUsbInL, 0, mixerOutI2sL, 1);
AudioConnection          patchCord23(ampUsbInL, 0, mixerOutUsbL, 1);
AudioConnection          patchCord24(ampUsbInL, peakMixerUsbL);
AudioConnection          patchCord25(mixerSWPeakUsbInL, peakUsbInL);
AudioConnection          patchCord26(mixerSWPeakUsbInR, peakUsbInR);
AudioConnection          patchCord27(mixerSWPeakLmInL, peakLmInL);
AudioConnection          patchCord28(mixerSWPeakLmInR, peakLmInR);
AudioConnection          patchCord29(mixerOutI2sL, ampMasterOutI2sL);
AudioConnection          patchCord30(mixerOutI2sL, 0, mixerSWPeakI2sL, 1);
AudioConnection          patchCord31(mixerOutI2sL, 0, mixerSWRmsI2sL, 1);
AudioConnection          patchCord32(mixerOutI2sR, ampMasterOutI2sR);
AudioConnection          patchCord33(mixerOutI2sR, 0, mixerSWPeakI2sR, 1);
AudioConnection          patchCord34(mixerOutI2sR, 0, mixerSWRmsI2sR, 1);
AudioConnection          patchCord35(mixerOutUsbR, ampMasterOutUsbR);
AudioConnection          patchCord36(mixerOutUsbR, 0, mixerSWPeakUsbR, 1);
AudioConnection          patchCord37(mixerOutUsbR, 0, mixerSWRmsUsbR, 1);
AudioConnection          patchCord38(mixerOutUsbL, ampMasterOutUsbL);
AudioConnection          patchCord39(mixerOutUsbL, 0, mixerSWPeakUsbL, 1);
AudioConnection          patchCord40(mixerOutUsbL, 0, mixerSWRmsUsbL, 1);
AudioConnection          patchCord41(ampMasterOutI2sL, 0, i2sOUT, 0);
AudioConnection          patchCord42(ampMasterOutI2sL, 0, mixerSWRmsI2sL, 0);
AudioConnection          patchCord43(ampMasterOutI2sL, 0, mixerSWPeakI2sL, 0);
AudioConnection          patchCord44(ampMasterOutI2sR, 0, i2sOUT, 1);
AudioConnection          patchCord45(ampMasterOutI2sR, 0, mixerSWPeakI2sR, 0);
AudioConnection          patchCord46(ampMasterOutI2sR, 0, mixerSWRmsI2sR, 0);
AudioConnection          patchCord47(ampMasterOutUsbL, 0, usbOUT, 0);
AudioConnection          patchCord48(ampMasterOutUsbL, 0, mixerSWPeakUsbL, 0);
AudioConnection          patchCord49(ampMasterOutUsbL, 0, mixerSWRmsUsbL, 0);
AudioConnection          patchCord50(ampMasterOutUsbR, 0, usbOUT, 1);
AudioConnection          patchCord51(ampMasterOutUsbR, 0, mixerSWPeakUsbR, 0);
AudioConnection          patchCord52(ampMasterOutUsbR, 0, mixerSWRmsUsbR, 0);
AudioConnection          patchCord53(mixerSWPeakI2sL, peakI2sL);
AudioConnection          patchCord54(mixerSWRmsI2sL, rmsI2sL);
AudioConnection          patchCord55(mixerSWPeakUsbL, peakUsbL);
AudioConnection          patchCord56(mixerSWPeakI2sR, peakI2sR);
AudioConnection          patchCord57(mixerSWPeakUsbR, peakUsbR);
AudioConnection          patchCord58(mixerSWRmsUsbR, rmsUsbR);
AudioConnection          patchCord59(mixerSWRmsUsbL, rmsUsbL);
AudioConnection          patchCord60(mixerSWRmsI2sR, rmsI2sR);
AudioControlSGTL5000     sgtl5000_1;     //xy=260.0000114440918,200.0000638961792
// GUItool: end automatically generated code
