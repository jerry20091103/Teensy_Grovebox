#include "SampleEditorPage.h"
#include "Controls.h"
#include "Audio/AudioSynth.h"
#include "Audio/AudioObjects.h"

#define CURSOR_INCREMENT 0.002f

// toggle the record button (for record full canceling)
void toggleRecordButton(SampleEditorPage *instance)
{
    // toggle record button
    lv_obj_has_state(instance->recordBtn, LV_STATE_CHECKED) ? lv_obj_clear_state(instance->recordBtn, LV_STATE_CHECKED) : lv_obj_add_state(instance->recordBtn, LV_STATE_CHECKED);
    lv_event_send(instance->recordBtn, LV_EVENT_CLICKED, NULL);
}

void SampleEditorPage::loadWaveformChart(int16_t *data, int length_samples)
{
    // downsample to 1000 points
    if (length_samples < 1000)
    {
        lv_chart_set_point_count(waveformChart, length_samples);
        lv_chart_set_ext_y_array(waveformChart, serMax, data);
        lv_chart_set_ext_y_array(waveformChart, serMin, data);
    }
    else
    {
        int hop = length_samples / 1000.0f;
        for (int i = 0; i < 1000; i++)
        {
            // find max
            int16_t max = 0;
            for (int j = 0; j < hop; j++)
            {
                if (data[i * hop + j] > max)
                {
                    max = data[i * hop + j];
                }
            }
            waveformPointsMax[i] = max;
            // find min
            int16_t min = 0;
            for (int j = 0; j < hop; j++)
            {
                if (data[i * hop + j] < min)
                {
                    min = data[i * hop + j];
                }
            }
            waveformPointsMin[i] = min;
        }
        lv_chart_set_point_count(waveformChart, 1000);
        lv_chart_set_ext_y_array(waveformChart, serMax, waveformPointsMax);
        lv_chart_set_ext_y_array(waveformChart, serMin, waveformPointsMin);
    }
}

lv_obj_t *SampleEditorPage::createCursor(lv_obj_t *parent, lv_color_t color, const char *text, bool reverse)
{
    lv_obj_t *cursor = lv_obj_create(parent);
    lv_obj_set_size(cursor, 3, 95);
    lv_obj_set_style_border_width(cursor, 3, 0);
    lv_obj_set_style_border_color(cursor, color, 0);
    lv_obj_add_flag(cursor, LV_OBJ_FLAG_OVERFLOW_VISIBLE);
    lv_obj_clear_flag(cursor, LV_OBJ_FLAG_SCROLLABLE);
    if (reverse)
        lv_obj_set_y(cursor, 30);
    else
        lv_obj_set_y(cursor, 25);

    lv_obj_t *handle = Gui_CreateButton(cursor, 25, 25, text);
    if (reverse)
        lv_obj_align(handle, LV_ALIGN_BOTTOM_MID, 0, 38);
    else
        lv_obj_align(handle, LV_ALIGN_TOP_MID, 0, -38);
    lv_obj_set_style_bg_color(handle, color, 0);
    // add drag event
    lv_obj_add_event_cb(handle, onCursorDragged, LV_EVENT_PRESSING, this);

    return cursor;
}

void SampleEditorPage::setCursorColor(lv_obj_t *cursor, lv_color_t color)
{
    lv_obj_t *handle = lv_obj_get_child(cursor, 0);
    lv_obj_set_style_border_color(cursor, color, 0);
    lv_obj_set_style_bg_color(handle, color, 0);
}

void SampleEditorPage::setCursorPos(uint8_t id, float pos)
{
    // get upper and lower bound
    float lowerBound = 0.0f;
    float upperBound = 1.0f;
    if (id - 1 >= 0)
    {
        lowerBound = cursorPos[id - 1].get();
    }
    if (id + 1 <= 3)
    {
        upperBound = cursorPos[id + 1].get();
    }
    // set cursor position
    pos = constrain(pos, lowerBound, upperBound);
    cursorPos[id].set(pos);
    // set cursor position in GUI
    lv_obj_t *cursor = lv_obj_get_child(cursorGroup, id);
    lv_obj_set_x(cursor, pos * 300 + 10);
    // update cursor handle
    lv_obj_invalidate(lv_obj_get_child(cursor, 0));
}
    
void SampleEditorPage::onRecordButtonPressed(lv_event_t *event)
{
    // get the button
    lv_obj_t *btn = lv_event_get_target(event);
    // get label
    lv_obj_t *label = lv_obj_get_child(btn, 0);
    // get instance
    SampleEditorPage *instance = (SampleEditorPage *)lv_event_get_user_data(event);

    if (lv_obj_has_state(btn, LV_STATE_CHECKED))
    {
        // start recording
        clip1.startRecording();
        lv_label_set_text(label, "STOP");
        // cancel recording after 6 seconds (memory full)
        auto cancelRecordTask = new ExecWithParameter<SampleEditorPage *>(toggleRecordButton, instance);
        instance->cancelRecordTaskId = taskManager.scheduleOnce(6000, cancelRecordTask, TIME_MILLIS, true);
    }
    else
    {
        // cancel the "cancel recording task"
        taskManager.cancelTask(instance->cancelRecordTaskId);
        // stop recording
        clip1.stopRecording();
        AudioSynth.setClip(clip1.getClip(), clip1.getClipLength());
        // load to chart display
        instance->loadWaveformChart((int16_t *)clip1.getClip(), clip1.getClipLength() * AUDIO_BLOCK_SAMPLES);
        lv_label_set_text(label, "RECORD");
    }
}
void SampleEditorPage::onPlayButtonPressed(lv_event_t *event)
{
    // get the button
    lv_obj_t *btn = lv_event_get_target(event);
    // get label
    lv_obj_t *label = lv_obj_get_child(btn, 0);

    if (lv_obj_has_state(btn, LV_STATE_CHECKED))
    {
        // start playing
        AudioSynth.playClip();
        lv_label_set_text(label, "STOP");
    }
    else
    {
        // stop playing
        AudioSynth.stopClip();
        lv_label_set_text(label, "PLAY");
    }
}
void SampleEditorPage::onLoopButtonPressed(lv_event_t *event)
{
    // get the button
    lv_obj_t *btn = lv_event_get_target(event);
    // get instance
    SampleEditorPage *instance = (SampleEditorPage *)lv_event_get_user_data(event);

    if (lv_obj_has_state(btn, LV_STATE_CHECKED))
    {
        // start playing
        AudioSynth.setClipLoop(true);
        // set loop cursors to bright color
        setCursorColor(lv_obj_get_child(instance->cursorGroup, 1), color_Yellow);
        setCursorColor(lv_obj_get_child(instance->cursorGroup, 2), color_Blue);
    }
    else
    {
        // stop playing
        AudioSynth.setClipLoop(false);
        // set loop cursors to dark color
        setCursorColor(lv_obj_get_child(instance->cursorGroup, 1), color_YellowDark);
        setCursorColor(lv_obj_get_child(instance->cursorGroup, 2), color_BlueDark);
    }
}

void SampleEditorPage::onNormailzeButtonPressed(lv_event_t *event)
{
    // get instance
    SampleEditorPage *instance = (SampleEditorPage *)lv_event_get_user_data(event);

    if (lv_obj_has_state(instance->recordBtn, LV_STATE_CHECKED) || lv_obj_has_state(instance->playBtn, LV_STATE_CHECKED))
        return;

    // find max in clip
    int16_t maxValue = 0;
    int16_t *clipPtr = (int16_t *)clip1.getClip();
    int length_samples = clip1.getClipLength() * AUDIO_BLOCK_SAMPLES;
    for (int i = 0; i < length_samples; i++)
    {
        if (abs(clipPtr[i]) > maxValue)
            maxValue = clipPtr[i];
    }
    // calculate normailze factor
    float factor = 32767.0f / (float)maxValue;
    // apply normailzation
    for (int i = 0; i < length_samples; i++)
    {
        clipPtr[i] = clipPtr[i] * factor;
    }
    instance->loadWaveformChart(clipPtr, length_samples);
}

void SampleEditorPage::onReverseButtonPressed(lv_event_t *event)
{
    // get instance
    SampleEditorPage *instance = (SampleEditorPage *)lv_event_get_user_data(event);

    if (lv_obj_has_state(instance->recordBtn, LV_STATE_CHECKED) || lv_obj_has_state(instance->playBtn, LV_STATE_CHECKED))
        return;
    // reverse the clip
    int16_t *clipPtr = (int16_t *)clip1.getClip();
    int length_samples = clip1.getClipLength() * AUDIO_BLOCK_SAMPLES;
    for (int i = 0; i < length_samples / 2; i++)
    {
        int16_t temp = clipPtr[i];
        clipPtr[i] = clipPtr[length_samples - i];
        clipPtr[length_samples - i] = temp;
    }
    instance->loadWaveformChart(clipPtr, length_samples);
}

void SampleEditorPage::onCursorDragged(lv_event_t *event)
{
    // get touch position
    lv_indev_t *indev = lv_indev_get_act();
    if (indev == NULL)
        return;
    lv_point_t point;
    lv_indev_get_point(indev, &point);
    // get instance
    SampleEditorPage *instance = (SampleEditorPage *)lv_event_get_user_data(event);
    // get cursor
    lv_obj_t *cursor = lv_obj_get_parent(lv_event_get_target(event));
    // get cursor index
    int cursorIndex = lv_obj_get_index(cursor);
    Serial.println(point.x);
    
    instance->setCursorPos(cursorIndex, (point.x - 10) / 300.0f);
}

void SampleEditorPage::onCrossFadeSliderPressed(lv_event_t *event)
{
    SampleEditorPage *instance = (SampleEditorPage *)lv_event_get_user_data(event);
    lv_obj_t *slider = lv_event_get_target(event);
    int amount = lv_slider_get_value(slider);
    instance->crossFade.set(amount * 0.01f);
}

void SampleEditorPage::onBtnPressed(uint8_t pin)
{
    switch (pin)
    {
    case BTN_PWR:
        PageManager.switchPage(PG_AUDIO);
        break;
    case BTN_FN0:
        toggleRecordButton(this);
        break;
    }
}

void SampleEditorPage::onBtnHold(uint8_t pin)
{
    switch (pin)
    {
    case BTN_PWR:
        PageManager.showPowerPopup();
        break;
    }
}
void SampleEditorPage::onBtnReleased(uint8_t pin)
{
}
void SampleEditorPage::onEncTurned(uint8_t id, int value)
{
    setCursorPos(id, cursorPos[id].get() + value * CURSOR_INCREMENT);
    // todo: crossfade between loop cursors, input level meter
}
void SampleEditorPage::onJoyUpdate(int joy_x, int joy_y)
{
}
void SampleEditorPage::onCCReceive(u_int8_t channel, u_int8_t control, u_int8_t value)
{
}
void SampleEditorPage::configurePage()
{
    AudioSynth.setVoiceMode(VOICE_MODE_SAMPLE_EDITER);
    // set encoders to direction mode
    enc[0]->changePrecision(0, 0);
    enc[1]->changePrecision(0, 0);
    enc[2]->changePrecision(0, 0);
    enc[3]->changePrecision(0, 0);
}
void SampleEditorPage::setUserData()
{
}

void SampleEditorPage::update()
{
    // check clip playing state
    if (lv_obj_has_state(playBtn, LV_STATE_CHECKED))
    {
        // check play state of clip
        if (playClip0.playing())
        {
            // get current position
            float pos = playClip0.getCurrentPosition();
            // update current position cursor
            lv_obj_set_x(currentPosCursor, pos * 300 + 10);
        }
        else
        {
            // stop playing
            lv_obj_clear_state(playBtn, LV_STATE_CHECKED);
            lv_event_send(playBtn, LV_EVENT_CLICKED, NULL);
        }
    }
    // update volume meter
    if (peakClip1.available())
    {
        float peak = peakClip1.read();
        // convert to dB
        float temp_dB = gaintodB(peak);
        if (temp_dB >= -0.1)
            peakHold = PEAK_HOLD_TIME;
        // calulate running average
        peak = (peak + peakAvg * 3) / (3 + 1);
        peakAvg = peak;
        lv_bar_set_value(volBar, temp_dB, LV_ANIM_ON);
    }
    // peak indicator
    if (peakHold > 0)
    {
        Gui_PeakLedOn(peakLed);
        peakHold--;
    }
    else
    {
        Gui_PeakLedOff(peakLed);
    }
}
void SampleEditorPage::init()
{
    pageID = PG_SAMPLEEDITOR;
    strcpy(pageName, "Sample Editor");
    screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen, lv_color_black(), 0);
    // waveform display
    waveformChart = lv_chart_create(screen);
    lv_obj_set_size(waveformChart, 320, 110);
    lv_obj_set_pos(waveformChart, 0, 55);
    lv_chart_set_range(waveformChart, LV_CHART_AXIS_PRIMARY_Y, -32768, 32767);
    lv_obj_set_style_bg_color(waveformChart, lv_color_black(), 0);

    /*Do not display points on the data*/
    lv_obj_set_style_size(waveformChart, 0, LV_PART_INDICATOR);
    lv_obj_set_style_line_width(waveformChart, 1, LV_PART_ITEMS);

    serMax = lv_chart_add_series(waveformChart, lv_color_white(), LV_CHART_AXIS_PRIMARY_Y);
    serMin = lv_chart_add_series(waveformChart, lv_color_white(), LV_CHART_AXIS_PRIMARY_Y);

    // cursorGroup for 4 cursors
    cursorGroup = lv_obj_create(screen);
    lv_obj_remove_style_all(cursorGroup);
    lv_obj_set_size(cursorGroup, 320, 205);
    lv_obj_set_pos(cursorGroup, 0, 35);

    createCursor(cursorGroup, color_Red, LV_SYMBOL_PLAY);
    createCursor(cursorGroup, color_Yellow, LV_SYMBOL_LOOP, true);
    createCursor(cursorGroup, color_Blue, LV_SYMBOL_LOOP, true);
    createCursor(cursorGroup, color_Green, LV_SYMBOL_STOP);

    // current position cursor
    currentPosCursor = lv_obj_create(cursorGroup);
    lv_obj_set_size(currentPosCursor, 1, 90);
    lv_obj_set_style_border_width(currentPosCursor, 1, 0);
    lv_obj_set_style_border_color(currentPosCursor, lv_color_white(), 0);
    lv_obj_set_pos(currentPosCursor, 10, 30);

    // create buttons
    recordBtn = Gui_CreateButton(screen, 76, -1, "RECORD", true, 1);
    lv_obj_align(recordBtn, LV_ALIGN_BOTTOM_MID, -120, -5);
    lv_obj_add_event_cb(recordBtn, onRecordButtonPressed, LV_EVENT_CLICKED, this);

    playBtn = Gui_CreateButton(screen, 76, -1, "PLAY", true);
    lv_obj_align(playBtn, LV_ALIGN_BOTTOM_MID, -40, -5);
    lv_obj_add_event_cb(playBtn, onPlayButtonPressed, LV_EVENT_CLICKED, this);

    loopBtn = Gui_CreateButton(screen, 76, -1, "LOOP", true);
    lv_obj_align(loopBtn, LV_ALIGN_BOTTOM_MID, 40, -5);
    lv_obj_add_event_cb(loopBtn, onLoopButtonPressed, LV_EVENT_CLICKED, this);

    normalizeBtn = Gui_CreateButton(screen, 76, 25, "Normalize");
    lv_obj_align(normalizeBtn, LV_ALIGN_BOTTOM_MID, 120, -30);
    lv_obj_add_event_cb(normalizeBtn, onNormailzeButtonPressed, LV_EVENT_CLICKED, this);
    lv_obj_set_style_text_font(lv_obj_get_child(normalizeBtn, 0), font_small, 0);

    reverseBtn = Gui_CreateButton(screen, 76, 25, "Reverse");
    lv_obj_align(reverseBtn, LV_ALIGN_BOTTOM_MID, 120, -2);
    lv_obj_add_event_cb(reverseBtn, onReverseButtonPressed, LV_EVENT_CLICKED, this);
    lv_obj_set_style_text_font(lv_obj_get_child(reverseBtn, 0), font_small, 0);

    // input volume bar
    volBar = Gui_CreateVolumeMeter(screen, 60, 10);
    lv_obj_align(volBar, LV_ALIGN_BOTTOM_MID, -126, -43);
    peakLed = Gui_CreatePeakLed(volBar, 10, 10);
    lv_obj_align(peakLed, LV_ALIGN_RIGHT_MID, 15, 0);

    // crossfade slider
    lv_obj_t *label = lv_label_create(screen);
    lv_label_set_text(label, LV_SYMBOL_CLOSE);
    lv_obj_align(label, LV_ALIGN_BOTTOM_MID, -60, -40);
    lv_obj_t *slider = lv_slider_create(screen);
    lv_obj_set_size(slider, 115, 10);
    lv_obj_align(slider, LV_ALIGN_BOTTOM_MID, 10, -43);
    lv_slider_set_range(slider, 0, 100);
    lv_obj_set_style_bg_color(slider, color_Grey, 0);
    lv_obj_set_style_bg_color(slider, lv_color_white(), LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(slider, lv_color_white(), LV_PART_KNOB);
    lv_obj_set_style_pad_all(slider, 2, LV_PART_KNOB);
    lv_obj_add_event_cb(slider, onCrossFadeSliderPressed, LV_EVENT_VALUE_CHANGED, this);
}
