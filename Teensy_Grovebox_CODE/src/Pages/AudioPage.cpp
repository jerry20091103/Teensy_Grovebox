#include "AudioPage.h"
#include "Hardware.h"
#include "Controls.h"
#include "Audio/AudioUtility.h"

// reconfigure encoders when switching tabs
void AudioPage::onTabSwitch(lv_event_t *e)
{
    AudioPage *instance = (AudioPage *)lv_event_get_user_data(e);
    instance->configurePage();
}

// toggle PFL and update all PFL buttons
void AudioPage::onPFLBtnPressed(lv_event_t *e)
{
    AudioPage *instance = (AudioPage *)lv_event_get_user_data(e);
    instance->usePFL = !instance->usePFL;
    if (instance->usePFL)
    {
        lv_obj_add_state(instance->InPflBtn, LV_STATE_CHECKED);
        lv_obj_add_state(instance->OutPflBtn, LV_STATE_CHECKED);
    }
    else
    {
        lv_obj_clear_state(instance->InPflBtn, LV_STATE_CHECKED);
        lv_obj_clear_state(instance->OutPflBtn, LV_STATE_CHECKED);
    }
    instance->setPFL(instance->usePFL);
}

// Switch input source when button is pressed
void AudioPage::onInputSwitch(lv_event_t *e)
{
    AudioPage *instance = (AudioPage *)lv_event_get_user_data(e);
    lv_obj_t *btn = lv_event_get_target(e);
    // USER_1 flag indicates which button is pressed.
    instance->inputSource = lv_obj_has_flag(btn, LV_OBJ_FLAG_USER_1);
    if (!instance->inputSource)
    {
        // line input
        lv_obj_add_state(instance->lineBtn, LV_STATE_CHECKED);
        lv_obj_clear_state(instance->micBtn, LV_STATE_CHECKED);
        sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
        enc[0]->changePrecision(LINE_GAIN_MAX, instance->gain[0]);
        lv_arc_set_range(instance->gainArc, 0, LINE_GAIN_MAX);
        lv_arc_set_value(instance->gainArc, instance->gain[0]);
    }
    else
    {
        // mic input
        lv_obj_add_state(instance->micBtn, LV_STATE_CHECKED);
        lv_obj_clear_state(instance->lineBtn, LV_STATE_CHECKED);
        sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
        enc[0]->changePrecision(MIC_GAIN_MAX, instance->gain[1]);
        lv_arc_set_range(instance->gainArc, 0, MIC_GAIN_MAX);
        lv_arc_set_value(instance->gainArc, instance->gain[1]);
    }
    instance->updateInputGain(instance->gain[instance->inputSource]);
}

// update encoder value and variables when arc is pressed
void AudioPage::onArcPressed(lv_event_t *e)
{
    AudioPage *instance = (AudioPage *)lv_event_get_user_data(e);
    lv_obj_t *arc = lv_event_get_target(e);
    // use user flags to determine which arc is pressed
    uint8_t id = Gui_getObjIdFlag(arc);
    uint8_t newVal = lv_arc_get_value(arc);
    switch (id)
    {
    case 0:
        // analog out
        enc[0]->setCurrentReading(newVal);
        instance->updateOutVol(MasterTracks::ANALOG_OUT, newVal);
        break;
    case 1:
        // USB out
        enc[1]->setCurrentReading(newVal);
        instance->updateOutVol(MasterTracks::USB_OUT, newVal);
        break;
    case 2:
        // HP volume
        enc[2]->setCurrentReading(newVal);
        instance->updateHpVol(newVal);
        break;
    case 3:
        // analog in
        enc[1]->setCurrentReading(newVal);
        instance->updateInVol(InputTracks::LINEMIC_IN, newVal);
        break;
    case 4:
        // USB in
        enc[2]->setCurrentReading(newVal);
        instance->updateInVol(InputTracks::USB_IN, newVal);
        break;
    case 5:
        // input gain
        enc[0]->setCurrentReading(newVal);
        instance->updateInputGain(newVal);
        break;
    case 6:
    case 7:
    case 8:
    case 9:
        // mixer track 0 ~ 4
        enc[id - 6]->setCurrentReading(newVal);
        instance->updateMixerVol((MixerTracks)(id - 6), newVal);
    }
}

// open mixer window and reconfigure encoders
void AudioPage::onMixerBtnPressed(lv_event_t *e)
{
    AudioPage *instance = (AudioPage *)lv_event_get_user_data(e);
    lv_obj_t *btn = lv_event_get_target(e);
    uint8_t id = lv_obj_has_flag(btn, LV_OBJ_FLAG_USER_1);
    instance->currentMasterForMixer = (MasterTracks)id;
    lv_obj_clear_flag(instance->mixerWindow, LV_OBJ_FLAG_HIDDEN);
    for (uint8_t i = 0; i < 4; i++)
    {
        instance->updateMixerVol((MixerTracks)i, instance->mixerVol[instance->currentMasterForMixer][i]);
        lv_arc_set_value(instance->mixerArc[i], instance->mixerVol[instance->currentMasterForMixer][i]);
    }
    lv_label_set_text(instance->mixerTitle, instance->currentMasterForMixer ? "USB Output Mixer" : "Analog Output Mixer");
    instance->configurePage();
}

// close mixer window
void AudioPage::onMixerClose(lv_event_t *e)
{
    AudioPage *instance = (AudioPage *)lv_event_get_user_data(e);
    lv_obj_add_flag(instance->mixerWindow, LV_OBJ_FLAG_HIDDEN);
    instance->configurePage();
}

void AudioPage::onBtnPressed(uint8_t pin)
{
    uint8_t keyNum = PinToKeyNum(pin);
    if (keyNum > 0)
    {
        PageManager.PageArr[PageManager.getPrevPage()]->onBtnPressed(pin);
    }
    else
    {
        switch (pin)
        {
        case BTN_PWR:
            PageManager.goBack();
            break;
        case BTN_JOY:
            PageManager.PageArr[PageManager.getPrevPage()]->onBtnPressed(pin);
            break;
        }
    }
}

void AudioPage::onBtnHold(uint8_t pin)
{
    switch (pin)
    {
    case BTN_PWR:
        PageManager.showPowerPopup();
        break;
    }
}

void AudioPage::onBtnReleased(uint8_t pin)
{
    uint8_t keyNum = PinToKeyNum(pin);
    if (keyNum > 0)
    {
        PageManager.PageArr[PageManager.getPrevPage()]->onBtnReleased(pin);
    }
    else
    {
        switch (pin)
        {
        case BTN_JOY:
            PageManager.PageArr[PageManager.getPrevPage()]->onBtnReleased(pin);
            break;
        }
    }
}

void AudioPage::onEncTurned(uint8_t id, int value)
{
    uint8_t curTab = lv_tabview_get_tab_act(tabView);
    switch (curTab)
    {
    case 0:
        // *OUTPUT TAB
        if (lv_obj_has_flag(mixerWindow, LV_OBJ_FLAG_HIDDEN))
        {
            switch (id)
            {
            case 0:
                // analog out volume
            case 1:
                // USB out volume
                lv_arc_set_value(OutArc[id], value);
                updateOutVol((MasterTracks)id, value);
                break;
            case 2:
                // hp voulme
                lv_arc_set_value(hpArc, value);
                updateHpVol(value);
                break;
            }
        }
        else // mixer window is open
        {
            lv_arc_set_value(mixerArc[id], value);
            updateMixerVol((MixerTracks)id, value);
        }
        break;
    case 1:
        // *INPUT TAB
        switch (id)
        {
        case 0:
            // input gain
            lv_arc_set_value(gainArc, value);
            updateInputGain(value);
            break;
        case 1:
            // analog in volume
        case 2:
            // USB in volume
            lv_arc_set_value(InArc[id - 1], value);
            updateInVol((InputTracks)(id - 1), value);
            break;
        }
        break;
    case 2:
        // *POST-DSP TAB
        break;
    }
}

void AudioPage::onJoyUpdate(int joy_x, int joy_y)
{
}

void AudioPage::onCCReceive(u_int8_t channel, u_int8_t control, u_int8_t value)
{
}

void AudioPage::configurePage()
{
    // input source, gain and volume may be changed by synth for velocity, need to change back.
    sgtl5000_1.inputSelect(inputSource);
    updateInputGain(gain[inputSource]);
    updateInVol(InputTracks::LINEMIC_IN, InVol[0]);
    // encoders need to be reconfigured when swtiching tabs
    uint8_t curTab = lv_tabview_get_tab_act(tabView);
    switch (curTab)
    {
    case 0:
        // *OUTPUT TAB
        if (lv_obj_has_flag(mixerWindow, LV_OBJ_FLAG_HIDDEN))
        {
            enc[0]->changePrecision(VOL_MAX, OutVol[0], false);
            enc[1]->changePrecision(VOL_MAX, OutVol[1], false);
            enc[2]->changePrecision(HP_VOL_MAX, hpVol, false);
        }
        else // mixer window is open
        {
            for (uint8_t i = 0; i < 4; i++)
            {
                enc[i]->changePrecision(VOL_MAX, mixerVol[currentMasterForMixer][i], false);
            }
        }
        break;
    case 1:
        // *INPUT TAB
        enc[0]->changePrecision(inputSource ? MIC_GAIN_MAX : LINE_GAIN_MAX, gain[inputSource], false);
        enc[1]->changePrecision(VOL_MAX, InVol[0], false);
        enc[2]->changePrecision(VOL_MAX, InVol[1], false);
        break;
    case 2:
        // *POST-DSP TAB
        break;
    }
}

void AudioPage::setUserData()
{
    // output tab
    for (uint8_t i = 0; i < 2; i++)
    {
        updateOutVol((MasterTracks)i, OutVol[i]);
        lv_arc_set_value(OutArc[i], OutVol[i]);
    }
    updateHpVol(hpVol);
    lv_arc_set_value(hpArc, hpVol);
    setPFL(usePFL);
    if (usePFL)
        lv_obj_add_state(OutPflBtn, LV_STATE_CHECKED);
    else
        lv_obj_clear_state(OutPflBtn, LV_STATE_CHECKED);
    // input tab
    for (uint8_t i = 0; i < 2; i++)
    {
        updateInVol((InputTracks)i, InVol[i]);
        lv_arc_set_value(InArc[i], InVol[i]);
    }
    updateInputGain(gain[inputSource]);
    if (inputSource == 0)
    {
        lv_arc_set_range(gainArc, 0, LINE_GAIN_MAX);
        lv_obj_add_state(lineBtn, LV_STATE_CHECKED);
        lv_obj_clear_state(micBtn, LV_STATE_CHECKED);
        sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
    }
    else
    {
        lv_arc_set_range(gainArc, 0, MIC_GAIN_MAX);
        lv_obj_add_state(micBtn, LV_STATE_CHECKED);
        lv_obj_clear_state(lineBtn, LV_STATE_CHECKED);
        sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
    }
    lv_arc_set_value(gainArc, gain[inputSource]);
    if (usePFL)
        lv_obj_add_state(InPflBtn, LV_STATE_CHECKED);
    else
        lv_obj_clear_state(InPflBtn, LV_STATE_CHECKED);
    // post-dsp tab

    // output mixer window
    for (uint8_t i = 0; i < 4; i++)
    {
        updateMixerVol((MixerTracks)i, mixerVol[MasterTracks::ANALOG_OUT][i]);
        updateMixerVol((MixerTracks)i, mixerVol[MasterTracks::USB_OUT][i]);
        lv_arc_set_value(mixerArc[i], mixerVol[currentMasterForMixer][i]);
    }
}

void AudioPage::update()
{
    floatStereo inFS, outFS, mixerFS;
    float in_peak[2];
    float out_peak[2];
    float mixer_peak[2];
    // input
    for (uint8_t i = 0; i < 2; i++)
    {
        inFS = AudioIO.getInputPeak((InputTracks)i);
        in_peak[0] = inFS.l;
        in_peak[1] = inFS.r;
        for (uint8_t j = 0; j < 2; j++)
        {
            // peak level meter
            if (in_peak[j] >= 0)
            {
                // convert to dB
                in_peak[j] = gaintodB(in_peak[j]);
                if (in_peak[j] >= -0.1)
                    InPeakHold[i][j] = PEAK_HOLD_TIME;
                lv_bar_set_value(InBar[i][j], in_peak[j], LV_ANIM_ON);
            }
            // peak indicator
            if (InPeakHold[i][j] > 0)
            {
                Gui_PeakLedOn(InPeakLed[i][j]);
                InPeakHold[i][j]--;
            }
            else
            {
                Gui_PeakLedOff(InPeakLed[i][j]);
            }
        }
    }
    // mixer
    if (!lv_obj_has_flag(mixerWindow, LV_OBJ_FLAG_HIDDEN))
    {
        for (uint8_t i = 0; i < 3; i++) // TODO: add more tracks
        {
            mixerFS = AudioIO.getMixerPeak((MasterTracks)currentMasterForMixer, (MixerTracks)i);
            mixer_peak[0] = mixerFS.l;
            mixer_peak[1] = mixerFS.r;
            for (uint8_t j = 0; j < 2; j++)
            {
                // peak level meter
                if (mixer_peak[j] >= 0)
                {
                    // convert to dB
                    mixer_peak[j] = gaintodB(mixer_peak[j]);
                    if (mixer_peak[j] >= -0.1)
                        mixerPeakHold[i][j] = PEAK_HOLD_TIME;
                    lv_bar_set_value(mixerBar[i][j], mixer_peak[j], LV_ANIM_ON);
                }
                // peak indicator
                if (mixerPeakHold[i][j] > 0)
                {
                    Gui_PeakLedOn(mixerPeakLed[i][j]);
                    mixerPeakHold[i][j]--;
                }
                else
                {
                    Gui_PeakLedOff(mixerPeakLed[i][j]);
                }
            }
        }
    }
    else
    // output
    {
        for (uint8_t i = 0; i < 2; i++)
        {
            outFS = AudioIO.getMasterPeak((MasterTracks)i);
            out_peak[0] = outFS.l;
            out_peak[1] = outFS.r;
            for (uint8_t j = 0; j < 2; j++)
            {
                // peak level meter
                if (out_peak >= 0)
                {
                    // convert to dB
                    out_peak[j] = gaintodB(out_peak[j]);
                    if (out_peak[j] >= -0.1)
                        OutPeakHold[i][j] = PEAK_HOLD_TIME;
                    lv_bar_set_value(OutBar[i][j], out_peak[j], LV_ANIM_ON);
                }
                // peak indicator
                if (OutPeakHold[i][j] > 0)
                {
                    Gui_PeakLedOn(OutPeakLed[i][j]);
                    OutPeakHold[i][j]--;
                }
                else
                {
                    Gui_PeakLedOff(OutPeakLed[i][j]);
                }
            }
        }
    }
}

void AudioPage::init()
{
    pageID = PG_AUDIO;
    strcpy(pageName, "Audio Settings");
    // create screen
    screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen, lv_color_black(), 0);
    // create lvgl objects
    // *tab view
    tabView = lv_tabview_create(screen, LV_DIR_TOP, 30);
    lv_obj_set_size(tabView, 320, 205);
    lv_obj_set_y(tabView, 35);
    lv_obj_set_style_bg_color(tabView, lv_color_black(), 0);
    lv_obj_add_event_cb(tabView, onTabSwitch, LV_EVENT_VALUE_CHANGED, this);

    lv_obj_t *label;
    lv_obj_t *btn;

    // *OUTPUT TAB------------------------------------------------------------------------------
    lv_obj_t *tab1 = lv_tabview_add_tab(tabView, "OUTPUT");
    lv_obj_clear_flag(tab1, LV_OBJ_FLAG_SCROLLABLE);

    // *analog out and USB out
    for (uint8_t i = 0; i < 2; i++)
    {
        createTrackGui(tab1,
                       OutArc[i],
                       OutVolText[i],
                       OutBar[i],
                       OutPeakLed[i],
                       i + 1, i == 0 ? "Analog" : "USB");
        // set arc position
        lv_obj_set_y(OutArc[i], i * 80);
        // set value
        Gui_setObjIdFlag(OutArc[i], i);
        // set callback
        lv_obj_add_event_cb(OutArc[i], onArcPressed, LV_EVENT_VALUE_CHANGED, this);
        // mixer button
        btn = Gui_CreateButton(OutArc[i]);
        lv_obj_align(btn, LV_ALIGN_TOP_MID, 160, -5);
        if (i)
            lv_obj_add_flag(btn, LV_OBJ_FLAG_USER_1);
        lv_obj_add_event_cb(btn, onMixerBtnPressed, LV_EVENT_CLICKED, this);
        label = lv_label_create(btn);
        lv_label_set_text(label, LV_SYMBOL_EDIT);
        lv_obj_set_style_text_font(label, font_small, 0);
        lv_obj_center(label);
    }

    // *hp volume
    hpArc = Gui_CreateParamArc(tab1, 3, NULL, "%", false);
    lv_obj_align(hpArc, LV_ALIGN_TOP_RIGHT, 0, 20);
    // headphone logo
    hpModeLabel = lv_label_create(hpArc);
    lv_obj_set_style_text_font(hpModeLabel, font_extraSymbol, LV_PART_MAIN);
    lv_label_set_text(hpModeLabel, MY_HEADPHONE_SYMBOL);
    lv_obj_align(hpModeLabel, LV_ALIGN_TOP_MID, 0, -20);
    // volume text
    hpVolText = lv_label_create(hpArc);
    lv_obj_center(hpVolText);
    // set value
    Gui_setObjIdFlag(hpArc, 2);
    lv_obj_add_event_cb(hpArc, onArcPressed, LV_EVENT_VALUE_CHANGED, this);

    // PFL button
    OutPflBtn = Gui_CreateButton(hpArc, "PFL", true);
    lv_obj_add_event_cb(OutPflBtn, onPFLBtnPressed, LV_EVENT_CLICKED, this);
    lv_obj_set_width(OutPflBtn, 60);
    lv_obj_align(OutPflBtn, LV_ALIGN_BOTTOM_MID, 0, 40);

    // *INPUT TAB-------------------------------------------------------------------------------
    lv_obj_t *tab2 = lv_tabview_add_tab(tabView, "INPUT");
    lv_obj_clear_flag(tab2, LV_OBJ_FLAG_SCROLLABLE);
    // *analog in and USB in
    for (uint8_t i = 0; i < 2; i++)
    {
        createTrackGui(tab2,
                       InArc[i],
                       InVolText[i],
                       InBar[i],
                       InPeakLed[i],
                       i + 2, i == 0 ? "Analog" : "USB");
        // set arc position
        lv_obj_set_pos(InArc[i], 90, i * 80);
        // set value
        Gui_setObjIdFlag(InArc[i], i + 3);
        // set callback
        lv_obj_add_event_cb(InArc[i], onArcPressed, LV_EVENT_VALUE_CHANGED, this);
    }

    // *input gain
    gainArc = Gui_CreateParamArc(tab2, 1, "Gain", "dB", false);
    lv_obj_set_y(gainArc, 15);
    // gain text
    gainText = lv_label_create(gainArc);
    lv_obj_align(gainText, LV_ALIGN_CENTER, 0, 0);
    // set value
    Gui_setObjIdFlag(gainArc, 5);
    lv_obj_add_event_cb(gainArc, onArcPressed, LV_EVENT_VALUE_CHANGED, this);

    // *input source
    // title
    label = lv_label_create(gainArc);
    lv_label_set_text(label, "Source");
    lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, 20);
    // line button
    lineBtn = Gui_CreateButton(tab2, "LINE", true);
    lv_obj_set_pos(lineBtn, 0, 100);
    lv_obj_set_size(lineBtn, 60, 25);
    lv_obj_clear_flag(lineBtn, LV_OBJ_FLAG_USER_1); // use USER_1 flag to indicate source
    lv_obj_add_event_cb(lineBtn, onInputSwitch, LV_EVENT_CLICKED, this);
    // mic button
    micBtn = Gui_CreateButton(tab2, "MIC", true);
    lv_obj_set_pos(micBtn, 0, 130);
    lv_obj_set_size(micBtn, 60, 25);
    lv_obj_add_flag(micBtn, LV_OBJ_FLAG_USER_1); // use USER_1 flag to indicate source
    lv_obj_add_event_cb(micBtn, onInputSwitch, LV_EVENT_CLICKED, this);

    // PFL button
    InPflBtn = Gui_CreateButton(tab2, "PFL", true);
    lv_obj_set_pos(InPflBtn, 250, 0);
    lv_obj_add_event_cb(InPflBtn, onPFLBtnPressed, LV_EVENT_CLICKED, this);
    lv_obj_set_height(InPflBtn, 25);

    // *POST-DSP TAB----------------------------------------------------------------------------
    lv_obj_t *tab3 = lv_tabview_add_tab(tabView, "POST-DSP");
    label = lv_label_create(tab3);
    lv_label_set_text(label, "TBD");

    // *OUTPUT MIXER WINDOW----------------------------------------------------------------
    mixerWindow = lv_win_create(tab1, 30);
    lv_obj_set_size(mixerWindow, 292, 160);
    lv_obj_t *windowContent = lv_win_get_content(mixerWindow);
    // back button
    btn = lv_win_add_btn(mixerWindow, LV_SYMBOL_CLOSE, 30);
    lv_obj_add_event_cb(btn, onMixerClose, LV_EVENT_CLICKED, this);
    // title
    mixerTitle = lv_win_add_title(mixerWindow, " ");
    // pan button
    btn = lv_win_add_btn(mixerWindow, NULL, 60);
    lv_obj_set_style_bg_color(btn, color_Grey, 0);
    lv_obj_set_style_bg_color(btn, lv_color_white(), LV_STATE_CHECKED);
    lv_obj_set_style_text_color(btn, lv_color_black(), LV_STATE_CHECKED);
    lv_obj_add_flag(btn, LV_OBJ_FLAG_CHECKABLE);
    label = lv_label_create(btn);
    lv_label_set_text(label, "PAN");
    lv_obj_center(label);

    // *analog, USB, instruments, recorder tracks
    const char *trackNames[] = {"Analog", "USB", "Instruments", "Recorder"};
    for (uint8_t i = 0; i < 4; i++)
    {
        createTrackGui(windowContent,
                       mixerArc[i],
                       mixerVolText[i],
                       mixerBar[i],
                       mixerPeakLed[i],
                       i + 1, trackNames[i]);
        // set arc position
        lv_obj_set_y(mixerArc[i], i * 75);
        // set value
        Gui_setObjIdFlag(mixerArc[i], 6 + i);
        // set callback
        lv_obj_add_event_cb(mixerArc[i], onArcPressed, LV_EVENT_VALUE_CHANGED, this);
    }

    // hide mixer window
    lv_obj_add_flag(mixerWindow, LV_OBJ_FLAG_HIDDEN);
}

void AudioPage::createTrackGui(lv_obj_t *&parent, lv_obj_t *&arcRef, lv_obj_t *&volTextRef, lv_obj_t **barArrRef, lv_obj_t **peakArrRef, uint8_t color, const char *name)
{
    lv_obj_t *label;
    // create arc
    arcRef = Gui_CreateParamArc(parent, color, NULL, "dB", false);
    lv_arc_set_range(arcRef, 0, VOL_MAX);
    // title
    label = lv_label_create(arcRef);
    lv_label_set_text(label, name);
    lv_obj_align(label, LV_ALIGN_TOP_LEFT, 80, 2);
    // volume text
    volTextRef = lv_label_create(arcRef);
    lv_obj_center(volTextRef);
    // volume meter and peak led
    for (uint8_t i = 0; i < 2; i++)
    {
        barArrRef[i] = Gui_CreateVolumeMeter(arcRef, 120, 10);
        lv_obj_align(barArrRef[i], LV_ALIGN_CENTER, 105, 5 + 15 * i);

        peakArrRef[i] = Gui_CreatePeakLed(barArrRef[i], 10, 10);
        lv_obj_align(peakArrRef[i], LV_ALIGN_RIGHT_MID, 15, 0);
    }
}

void AudioPage::updateHpVol(uint8_t newVal)
{
    // mute
    if (newVal == 0)
    {
        sgtl5000_1.volume(0);
    }
    else
    {
        // convert to gain
        float temp = newVal;
        sgtl5000_1.volume(map((float)temp, 0, HP_VOL_MAX, 0, 0.8));
    }
    lv_label_set_text(hpVolText, String(newVal).c_str());
    hpVol = newVal;
}

void AudioPage::updateOutVol(MasterTracks track, uint8_t newVal)
{
    OutVol[track] = newVal;
    // mute
    if (newVal == 0)
    {
        AudioIO.setMasterVolume((MasterTracks)track, 0);
        lv_label_set_text(OutVolText[track], "MUTE");
    }
    else
    {
        // convert to gain
        int db = newVal - VOL_MAX + 10;
        float gain = dBtoGain(db);
        AudioIO.setMasterVolume((MasterTracks)track, gain);
        lv_label_set_text(OutVolText[track], String(db).c_str());
    }
}

void AudioPage::setPFL(bool flag)
{
    usePFL = flag;
    if (usePFL)
    {
        AudioIO.setMasterLevelMode(LevelMeterMode::PRE_FADER);
        AudioIO.setInputLevelMode(LevelMeterMode::PRE_FADER);
    }
    else
    {
        AudioIO.setMasterLevelMode(LevelMeterMode::POST_FADER);
        AudioIO.setInputLevelMode(LevelMeterMode::POST_FADER);
    }
}

void AudioPage::updateInVol(InputTracks track, uint8_t newVal)
{
    InVol[track] = newVal;
    // mute
    if (newVal == 0)
    {
        AudioIO.setInputVolume((InputTracks)track, 0);
        lv_label_set_text(InVolText[track], "MUTE");
    }
    else
    {
        // convert to gain
        int db = newVal - VOL_MAX + 10;
        float gain = dBtoGain(db);
        AudioIO.setInputVolume((InputTracks)track, gain);
        lv_label_set_text(InVolText[track], String(db).c_str());
    }
}

void AudioPage::updateInputGain(uint8_t newVal)
{
    gain[inputSource] = newVal;
    sgtl5000_1.micGain(newVal);
    lv_label_set_text(gainText, String(newVal).c_str());
}

void AudioPage::updateMixerVol(MixerTracks track, uint8_t newVal)
{
    mixerVol[currentMasterForMixer][track] = newVal;
    // mute
    if (newVal == 0)
    {
        AudioIO.setMixerVolume((MasterTracks)currentMasterForMixer, track, 0);
        lv_label_set_text(mixerVolText[track], "MUTE");
    }
    else
    {
        // convert to gain
        int db = newVal - VOL_MAX + 10;
        float gain = dBtoGain(db);
        AudioIO.setMixerVolume((MasterTracks)currentMasterForMixer, track, gain);
        lv_label_set_text(mixerVolText[track], String(db).c_str());
    }
}
