#include "SampleEditorPage.h"
#include "Controls.h"
#include "Audio/AudioSynth.h"
#include "Audio/AudioObjects.h"
#include "GuiObjects/Colors.h"

#define CURSOR_INCREMENT 0.002f

// toggle the record button (for record full canceling)
void toggleRecordButton(SampleEditorPage *instance)
{
    // toggle record button
    instance->recordBtn->pressButton();
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
        lowerBound = cursorPos[id - 1];
    }
    if (id + 1 <= 3)
    {
        upperBound = cursorPos[id + 1];
    }
    // set cursor position
    pos = constrain(pos, lowerBound, upperBound);
    cursorPos[id] = pos;
    // set parameters in AudioSynth
    switch (id)
    {
    case 0:
        AudioSynth.setClipStartPoint(pos);
        break;
    case 1:
        AudioSynth.setClipLoopStartPoint(pos);
        break;
    case 2:
        AudioSynth.setClipLoopEndPoint(pos);
        break;
    case 3:
        AudioSynth.setClipEndPoint(pos);
        break;
    }
    // set cursor position in GUI
    lv_obj_t *cursor = lv_obj_get_child(cursorGroup, id);
    lv_obj_set_x(cursor, pos * 300 + 10);
    // update cursor handle
    lv_obj_invalidate(lv_obj_get_child(cursor, 0));
}
    
void SampleEditorPage::onRecordButtonPressed(void *targetPointer, lv_obj_t *labelObj, bool isToggled)
{
    // get instance
    SampleEditorPage *instance = (SampleEditorPage *)targetPointer;

    if (isToggled)
    {
        // start recording
        clip1.startRecording();
        lv_label_set_text(labelObj, "STOP");
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
        // re calculate new cursor positions
        for (int i = 0; i < 4; i++)
        {
            instance->setCursorPos(i, instance->cursorPos[i]);
        }
        // load to chart display
        Gui_WaveFormChartSetPoints(instance->waveformChart, instance->serMax, instance->serMin, (int16_t *)clip1.getClip(), clip1.getClipLength() * AUDIO_BLOCK_SAMPLES);
        lv_label_set_text(labelObj, "RECORD");
    }
}
void SampleEditorPage::onPlayButtonPressed(void *targetPointer, lv_obj_t *labelObj, bool isToggled)
{
    if (isToggled)
    {
        // start playing
        AudioSynth.playClip();
        lv_label_set_text(labelObj, "STOP");
    }
    else
    {
        // stop playing
        AudioSynth.stopClip();
        lv_label_set_text(labelObj, "PLAY");
    }
}
void SampleEditorPage::onLoopButtonPressed(void *targetPointer, lv_obj_t *labelObj, bool isToggled)
{
    // get instance
    SampleEditorPage *instance = (SampleEditorPage *)targetPointer;
    instance->isLooping = isToggled;
    if (isToggled)
    {
        AudioSynth.setClipLoop(true);
        // set loop cursors to bright color
        setCursorColor(lv_obj_get_child(instance->cursorGroup, 1), color_Yellow);
        setCursorColor(lv_obj_get_child(instance->cursorGroup, 2), color_Blue);
    }
    else
    {
        AudioSynth.setClipLoop(false);
        // set loop cursors to dark color
        setCursorColor(lv_obj_get_child(instance->cursorGroup, 1), color_YellowDark);
        setCursorColor(lv_obj_get_child(instance->cursorGroup, 2), color_BlueDark);
    }
}

void SampleEditorPage::onNormailzeButtonPressed(void *targetPointer, lv_obj_t *labelObj, bool isToggled)
{
    // get instance
    SampleEditorPage *instance = (SampleEditorPage *)targetPointer;
    
    // check if recording or playing
    if (instance->recordBtn->getIsToggled() || instance->playBtn->getIsToggled())
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
    Gui_WaveFormChartSetPoints(instance->waveformChart, instance->serMax, instance->serMin, clipPtr, length_samples);
}

void SampleEditorPage::onReverseButtonPressed(void *targetPointer, lv_obj_t *labelObj, bool isToggled)
{
    // get instance
    SampleEditorPage *instance = (SampleEditorPage *)targetPointer;

    // check if recording or playing
    if (instance->recordBtn->getIsToggled() || instance->playBtn->getIsToggled())
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
    Gui_WaveFormChartSetPoints(instance->waveformChart, instance->serMax, instance->serMin, clipPtr, length_samples);
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

void SampleEditorPage::onCrossFadeSliderPressed(void *targetPointer, int value)
{
    SampleEditorPage *instance = (SampleEditorPage *)targetPointer;
    int amount = value;
    instance->crossFade = amount * 0.01f;
    AudioSynth.setClipLoopCrossfade(instance->crossFade);
}

void SampleEditorPage::onBtnPressed(uint8_t pin)
{
    switch (pin)
    {
    case BTN_PWR:
        PageManager.switchPage(PG_AUDIO);
        break;
    case BTN_FN0:
        recordBtn->pressButton();
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
    setCursorPos(id, cursorPos[id] + value * CURSOR_INCREMENT);
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
    
}
void SampleEditorPage::setUserData()
{
}

void SampleEditorPage::update()
{
    // check clip playing state
    if (playBtn->getIsToggled())
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
            playBtn->setToggle(false);
        }
    }
    // update volume meter
    if (peakClip1.available())
    {
        volBar->setVolume(peakClip1.read());
    }
}
void SampleEditorPage::init()
{
    pageID = PG_SAMPLEEDITOR;
    strcpy(pageName, "Sample Editor");
    screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen, lv_color_black(), 0);
}

void SampleEditorPage::load()
{
    // waveform display
    waveformChart = Gui_CreateWaveformChart(screen, 320, 110, &serMax, &serMin, samplerWaveformPointsMax, samplerWaveformPointsMin);
    lv_obj_set_pos(waveformChart, 0, 55);
    if (clip1.getClip() != NULL)
        Gui_WaveFormChartSetPoints(waveformChart, serMax, serMin, (int16_t *)clip1.getClip(), clip1.getClipLength() * AUDIO_BLOCK_SAMPLES);

    // cursorGroup for 4 cursors
    cursorGroup = lv_obj_create(screen);
    lv_obj_remove_style_all(cursorGroup);
    lv_obj_set_size(cursorGroup, 320, 205);
    lv_obj_set_pos(cursorGroup, 0, 35);

    createCursor(cursorGroup, color_Red, LV_SYMBOL_PLAY);
    createCursor(cursorGroup, color_Yellow, LV_SYMBOL_LOOP, true);
    createCursor(cursorGroup, color_Blue, LV_SYMBOL_LOOP, true);
    createCursor(cursorGroup, color_Green, LV_SYMBOL_STOP);

    for (int i = 0; i < 4; i++)
    {
        setCursorPos(i, cursorPos[i]);
    }

    // current position cursor
    currentPosCursor = lv_obj_create(cursorGroup);
    lv_obj_set_size(currentPosCursor, 1, 90);
    lv_obj_set_style_border_width(currentPosCursor, 1, 0);
    lv_obj_set_style_border_color(currentPosCursor, lv_color_white(), 0);
    lv_obj_set_pos(currentPosCursor, 10, 30);

    // create buttons
    recordBtn = new Button(screen, 76, -1, "RECORD", true, 1);
    lv_obj_align(recordBtn->getLvglObject(), LV_ALIGN_BOTTOM_MID, -120, -5);
    recordBtn->setPressedCallback(onRecordButtonPressed, this);

    playBtn = new Button(screen, 76, -1, "PLAY", true);
    lv_obj_align(playBtn->getLvglObject(), LV_ALIGN_BOTTOM_MID, -40, -5);
    playBtn->setPressedCallback(onPlayButtonPressed, this);

    loopBtn = new Button(screen, 76, -1, "LOOP", true);
    lv_obj_align(loopBtn->getLvglObject(), LV_ALIGN_BOTTOM_MID, 40, -5);
    loopBtn->setPressedCallback(onLoopButtonPressed, this);
    loopBtn->setToggle(isLooping);

    normalizeBtn = new Button(screen, 76, 25, "Normalize");
    lv_obj_align(normalizeBtn->getLvglObject(), LV_ALIGN_BOTTOM_MID, 120, -30);
    lv_obj_set_style_text_font(normalizeBtn->getLabelObject(), font_small, 0);
    normalizeBtn->setPressedCallback(onNormailzeButtonPressed, this);

    reverseBtn = new Button(screen, 76, 25, "Reverse");
    lv_obj_align(reverseBtn->getLvglObject(), LV_ALIGN_BOTTOM_MID, 120, -2);
    lv_obj_set_style_text_font(reverseBtn->getLabelObject(), font_small, 0);
    reverseBtn->setPressedCallback(onReverseButtonPressed, this);

    // input volume bar
    volBar = new VolumeBar(screen, 75, 10);
    lv_obj_align(volBar->getBarObject(), LV_ALIGN_BOTTOM_MID, -126, -43);
    volBar->setSmoothing(1);
    volBar->setRange(-50, 0);

    // crossfade slider
    crossFadeSlider = new Slider(screen, 115, 10);
    lv_obj_align(crossFadeSlider->getLvglObject(), LV_ALIGN_BOTTOM_MID, 10, -43);
    crossFadeSlider->setRange(0, 100);
    crossFadeSlider->setCallback(onCrossFadeSliderPressed, this);
    crossFadeSlider->setValue(crossFade);
    lv_obj_t *label = lv_label_create(crossFadeSlider->getLvglObject());
    lv_label_set_text(label, LV_SYMBOL_CLOSE);
    lv_obj_align(label, LV_ALIGN_BOTTOM_MID, -70, 3);

    // set audio synth mode
    AudioSynth.setVoiceMode(VOICE_MODE_SAMPLE_EDITER);

    // set encoders to direction mode
    enc[0]->changePrecision(0, 0);
    enc[1]->changePrecision(0, 0);
    enc[2]->changePrecision(0, 0);
    enc[3]->changePrecision(0, 0);
}

void SampleEditorPage::unload()
{
    delete recordBtn;
    delete playBtn;
    delete loopBtn;
    delete normalizeBtn;
    delete reverseBtn;
    delete volBar;
    delete crossFadeSlider;
    lv_obj_del(waveformChart);
    lv_obj_del(cursorGroup);
    recordBtn = NULL;
    playBtn = NULL;
    loopBtn = NULL;
    normalizeBtn = NULL;
    reverseBtn = NULL;
    volBar = NULL;
    crossFadeSlider = NULL;
    waveformChart = NULL;
    cursorGroup = NULL;
    currentPosCursor = NULL;
}
