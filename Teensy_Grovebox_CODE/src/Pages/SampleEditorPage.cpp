#include "SampleEditorPage.h"
#include "Controls.h"
#include "Audio/AudioSynth.h"
#include "Audio/AudioObjects.h"

void SampleEditorPage::loadWaveformChart(int16_t *data, int length)
{
    // down sample to 1000 points
    if (length < 1000)
    {
        lv_chart_set_point_count(waveformChart, length);
        lv_chart_set_ext_y_array(waveformChart, serMax, data);
        lv_chart_set_ext_y_array(waveformChart, serMin, data);
    }
    else
    {
        int hop = length / 1000.0f;
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

lv_obj_t* SampleEditorPage::createCursor(lv_obj_t *parent, lv_color_t color, const char *text, bool reverse = false)
{
    lv_obj_t *cursor = lv_obj_create(parent);
    lv_obj_set_size(cursor, 3, 110);
    lv_obj_set_style_border_width(cursor, 3, 0);
    lv_obj_set_style_border_color(cursor, color, 0);
    lv_obj_add_flag(cursor, LV_OBJ_FLAG_OVERFLOW_VISIBLE);
    if (reverse)
        lv_obj_set_y(cursor, 30);
    else
        lv_obj_set_y(cursor, 20);

    lv_obj_t *label = lv_label_create(cursor);
    if (reverse)
        lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, 33);
    else
        lv_obj_align(label, LV_ALIGN_TOP_MID, 0, -33);
    lv_label_set_text(label, text);
    lv_obj_set_style_pad_all(label, 3, 0);
    lv_obj_set_style_bg_opa(label, LV_OPA_COVER, 0);
    lv_obj_set_style_bg_color(label, color, 0);
    lv_obj_set_style_radius(label, 5, 0);

    return cursor;
}

void SampleEditorPage::onBtnPressed(uint8_t pin)
{
    switch (pin)
    {
    case BTN_PWR:
        PageManager.switchPage(PG_AUDIO);
        break;
    case BTN_FN0:
        clip1.startRecording();
        break;
    case BTN_FN1:
        clip1.stopRecording();
        playClip1.setClip(clip1.getClip(), clip1.getClipLength());
        // load to chart display
        loadWaveformChart((int16_t *)clip1.getClip(), clip1.getClipLength() * AUDIO_BLOCK_SAMPLES);
        break;
    case BTN_FN2:
        playClip1.play();
        break;
    case BTN_FN3:
        playClip1.stop();
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
}
void SampleEditorPage::onJoyUpdate(int joy_x, int joy_y)
{
}
void SampleEditorPage::onCCReceive(u_int8_t channel, u_int8_t control, u_int8_t value)
{
}
void SampleEditorPage::configurePage()
{
    AudioSynth.setVoiceMode(2);
}
void SampleEditorPage::setUserData()
{
}

void SampleEditorPage::update()
{
}
void SampleEditorPage::init()
{
    pageID = PG_SAMPLEEDITOR;
    strcpy(pageName, "Sample Editor");
    screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen, lv_color_black(), 0);
    // waveform display
    waveformChart = lv_chart_create(screen);
    lv_obj_set_size(waveformChart, 320, 120);
    lv_obj_set_pos(waveformChart, 0, 55);
    lv_chart_set_range(waveformChart, LV_CHART_AXIS_PRIMARY_Y, -32768, 32767);
    lv_obj_set_style_bg_color(waveformChart, lv_color_black(), 0);

    /*Do not display points on the data*/
    lv_obj_set_style_size(waveformChart, 0, LV_PART_INDICATOR);
    lv_obj_set_style_line_width(waveformChart, 1, LV_PART_ITEMS);

    serMax = lv_chart_add_series(waveformChart, lv_color_white(), LV_CHART_AXIS_PRIMARY_Y);
    serMin = lv_chart_add_series(waveformChart, lv_color_white(), LV_CHART_AXIS_PRIMARY_Y);

    // Draw lines cursors on the chart
    cursorGroup = lv_obj_create(screen);
    lv_obj_remove_style_all(cursorGroup);
    lv_obj_set_size(cursorGroup, 320, 205);
    lv_obj_set_pos(cursorGroup, 0, 35);

    createCursor(cursorGroup, color_Red, LV_SYMBOL_PLAY);
    createCursor(cursorGroup, color_Green, LV_SYMBOL_STOP);
    createCursor(cursorGroup, color_Yellow, LV_SYMBOL_LOOP, true);
    createCursor(cursorGroup, color_Blue, LV_SYMBOL_LOOP, true);

    lv_obj_set_x(lv_obj_get_child(cursorGroup, 0), 10);
    lv_obj_set_x(lv_obj_get_child(cursorGroup, 1), 310);
    lv_obj_set_x(lv_obj_get_child(cursorGroup, 2), 20);
    lv_obj_set_x(lv_obj_get_child(cursorGroup, 3), 300);

    // create buttons
    recordBtn = Gui_CreateButton(screen, "RECORD", false, 1);
    lv_obj_set_width(recordBtn, 70);
    lv_obj_align(recordBtn, LV_ALIGN_BOTTOM_MID, -120, -5);

    playBtn = Gui_CreateButton(screen, "PLAY");
    lv_obj_set_width(playBtn, 70);
    lv_obj_align(playBtn, LV_ALIGN_BOTTOM_MID, -40, -5);

    stopBtn = Gui_CreateButton(screen, "STOP");
    lv_obj_set_width(stopBtn, 70);
    lv_obj_align(stopBtn, LV_ALIGN_BOTTOM_MID, 40, -5);

    loopBtn = Gui_CreateButton(screen, "LOOP", true);
    lv_obj_set_width(loopBtn, 70);
    lv_obj_align(loopBtn, LV_ALIGN_BOTTOM_MID, 120, -5);


}

