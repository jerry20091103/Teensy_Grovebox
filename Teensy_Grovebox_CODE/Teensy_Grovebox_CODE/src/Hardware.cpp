#include "Hardware.h"
#include "Controls.h"

// 2 diff buffers for the LCD
ILI9341_T4::DiffBuffStatic<8000> tft_diff1;
ILI9341_T4::DiffBuffStatic<8000> tft_diff2;

// Display driver object
ILI9341_T4::ILI9341Driver tft(TFT_CS, TFT_DC, TFT_SCK, TFT_MOSI, TFT_MISO, TFT_RST, TFT_TOUCH_CS, TFT_TOUCH_IRQ);

IntervalTimer guiTimer;

// lvgl draw buffer
extern lv_color_t lvgl_buf[TFT_X * 40];

extern lv_disp_draw_buf_t draw_buf; // lvgl 'draw buffer' object
extern lv_disp_drv_t disp_drv;      // lvgl 'display driver'
extern lv_indev_drv_t indev_drv;    // lvgl 'input device driver'

MultiIoAbstractionRef multiIo = multiIoExpander(EXPANDER_PIN);

HardwareRotaryEncoder *enc0;
HardwareRotaryEncoder *enc1;
HardwareRotaryEncoder *enc2;
HardwareRotaryEncoder *enc3;

#if LV_USE_LOG != 0
/* LVGL Serial debugging */
void my_print(const char * buf)
{
    Serial.printf(buf);
    Serial.flush();
}
#endif

/** Callback to draw on the screen */
void myDispFlush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    const bool redraw_now = lv_disp_flush_is_last(disp);                                       // check if when should update the screen (or just buffer the changes).
    tft.updateRegion(redraw_now, (uint16_t *)color_p, area->x1, area->x2, area->y1, area->y2); // update the interval framebuffer and then redraw the screen if requested
    lv_disp_flush_ready(disp);                                                                 // tell lvgl that we are done and that the lvgl draw buffer can be reused immediately
}

/** Call back to read the touchpad */
void myTouchRead(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
    int touchX, touchY, touchZ;
    bool touched = tft.readTouch(touchX, touchY, touchZ); // read the touchpad
    if (!touched)
    { // nothing
        data->state = LV_INDEV_STATE_REL;
    }
    else
    { // pressed
        data->state = LV_INDEV_STATE_PR;
        data->point.x = touchX;
        data->point.y = touchY;
    }
}

// callback to update lvgl's tick every ms.
void guiInc()
{
    lv_tick_inc(1);
}

void HardwareSetup()
{
    // Setup LCD
    tft.begin(SPI_SPEED);
    tft.setFramebuffer(tft_fb);
    tft.setDiffBuffers(&tft_diff1, &tft_diff2);
    tft.setRotation(3);
    tft.setDiffGap(4);
    tft.setVSyncSpacing(1);
    tft.setRefreshRate(40);

    // LCD touch calibration
    int touchCalib[4] = {400, 3775, 3901, 483};
    tft.setTouchCalibration(touchCalib);

    // Setup LVGL
    lv_init();
#if LV_USE_LOG != 0
    lv_log_register_print_cb(my_print); /* register print function for debugging */
#endif
    lv_disp_draw_buf_init(&draw_buf, lvgl_buf, NULL, TFT_X * TFT_Y_BUF);
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = TFT_X;
    disp_drv.ver_res = TFT_Y;
    disp_drv.flush_cb = myDispFlush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    // Setup LVGL input device driver
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = myTouchRead;
    lv_indev_drv_register(&indev_drv);

    // setup io expanders
    Wire.begin();
    Wire.setClock(400000);
    multiIoAddExpander(multiIo, ioFrom23017(0x20, ACTIVE_LOW_OPEN, 17), 16);
    multiIoAddExpander(multiIo, ioFrom23017(0x21, ACTIVE_LOW_OPEN, 17), 16);

    // setup buttons
    switches.initialiseInterrupt(multiIo, true);
    for (int i = 0; i <= 7; i++)
    {
        // expander 1
        switches.addSwitch(E1GPA(i), BtnPressCallback);
        switches.onRelease(E1GPA(i), BtnReleaseCallback);
        switches.addSwitch(E1GPB(i), BtnPressCallback);
        switches.onRelease(E1GPB(i), BtnReleaseCallback);
        // expander 2, some pins on port A are not buttons.
        switches.addSwitch(E2GPB(i), BtnPressCallback);
        switches.onRelease(E2GPB(i), BtnReleaseCallback);
    }
    switches.addSwitch(E2GPA(0), BtnPressCallback);
    switches.onRelease(E2GPA(0), BtnReleaseCallback);
    switches.addSwitch(E2GPA(1), BtnPressCallback);
    switches.onRelease(E2GPA(1), BtnReleaseCallback);
    switches.addSwitch(E2GPA(2), BtnPressCallback);
    switches.onRelease(E2GPA(2), BtnReleaseCallback);
    switches.addSwitch(E2GPA(3), BtnPressCallback);
    switches.onRelease(E2GPA(3), BtnReleaseCallback);
    switches.addSwitch(E2GPA(4), BtnPressCallback);
    switches.onRelease(E2GPA(4), BtnReleaseCallback);
    switches.addSwitch(E2GPA(5), BtnPressCallback);
    switches.onRelease(E2GPA(5), BtnReleaseCallback);
    // encoder push btn
    switches.addSwitch(BTN_ENC1, BtnPressCallback);
    switches.onRelease(BTN_ENC1, BtnReleaseCallback);
    switches.addSwitch(BTN_ENC2, BtnPressCallback);
    switches.onRelease(BTN_ENC2, BtnReleaseCallback);
    switches.addSwitch(BTN_ENC3, BtnPressCallback);
    switches.onRelease(BTN_ENC3, BtnReleaseCallback);
    switches.addSwitch(BTN_ENC4, BtnPressCallback);
    switches.onRelease(BTN_ENC4, BtnReleaseCallback);
    // FN btn on teensy pins
    switches.addSwitch(BTN_FN4, BtnPressCallback);
    switches.onRelease(BTN_FN4, BtnReleaseCallback);
    switches.addSwitch(BTN_FN5, BtnPressCallback);
    switches.onRelease(BTN_FN5, BtnReleaseCallback);
    switches.addSwitch(BTN_FN6, BtnPressCallback);
    switches.onRelease(BTN_FN6, BtnReleaseCallback);
    switches.addSwitch(BTN_FN7, BtnPressCallback);
    switches.onRelease(BTN_FN7, BtnReleaseCallback);
    // power btn
    switches.addSwitch(BTN_PWR, BtnPressCallback);
    switches.onRelease(BTN_PWR, BtnReleaseCallback);

    // setup rotray encoders
    enc0 = new HardwareRotaryEncoder(ENC1A, ENC1B, Enc0Callback, HWACCEL_SLOWER);
    enc1 = new HardwareRotaryEncoder(ENC2A, ENC2B, Enc1Callback, HWACCEL_SLOWER);
    enc2 = new HardwareRotaryEncoder(ENC3A, ENC3B, Enc2Callback, HWACCEL_SLOWER);
    enc3 = new HardwareRotaryEncoder(ENC4A, ENC4B, Enc3Callback, HWACCEL_SLOWER);
    switches.setEncoder(0, enc0);
    switches.setEncoder(1, enc1);
    switches.setEncoder(2, enc2);
    switches.setEncoder(3, enc3);
    switches.changeEncoderPrecision(0, 0, 0);
    switches.changeEncoderPrecision(1, 0, 0);
    switches.changeEncoderPrecision(2, 0, 0);
    switches.changeEncoderPrecision(3, 0, 0);

    // setup joystick
    pinMode(JOY_X, INPUT);
    pinMode(JOY_Y, INPUT);
    switches.addSwitch(BTN_JOY, BtnPressCallback);
    switches.onRelease(BTN_JOY, BtnReleaseCallback);

    // setup LED bars
    pinMode(BAR1_OUT, OUTPUT);
    pinMode(BAR2_OUT, OUTPUT);
    pinMode(BAR_MODE, OUTPUT);

    // LCD brightness control
    pinMode(TFT_BACKLIGHT, OUTPUT);
    analogWrite(TFT_BACKLIGHT, 200);

    // Battery level
    pinMode(BATT_LVL, INPUT);

    // hold power
    ioDevicePinMode(multiIo, PWR_HOLD, OUTPUT);
    ioDevicePinMode(multiIo, AMP_SHDN, OUTPUT);
    ioDeviceDigitalWriteS(multiIo, PWR_HOLD, HIGH);
    ioDeviceDigitalWriteS(multiIo, AMP_SHDN, LOW);

    // set the interval timer that given lvgl ticks.
    guiTimer.begin(guiInc, 1000);

    // wait until power button released
    while (!ioDeviceDigitalReadS(multiIo, BTN_PWR))
    {
    }

    // Setup midi callbacks
    usbMIDI.setHandleControlChange(onControlChange);
}
