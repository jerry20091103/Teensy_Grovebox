#include "SynthPage.h"
#include "Hardware.h"
#include "Controls.h"
#include "Audio/AudioSynth.h"
#include "Audio/AudioIO.h"
#include "Audio/AudioUtility.h"
#include "GuiObjects/Colors.h"


void SynthPage::onVelocityBtnPressed(void *targetPointer, lv_obj_t *labelObj, bool isToggled)
{
    SynthPage *instance = (SynthPage *)targetPointer;
    instance->useVelocity = isToggled;
    AudioSynth.setUseVelocity(isToggled);
}

void SynthPage::onPitchBtnPressed(void *targetPointer, lv_obj_t *labelObj, bool isToggled)
{
    SynthPage *instance = (SynthPage *)targetPointer;
    instance->usePitchbend = isToggled;
    if (!isToggled)
        AudioSynth.pitchbend(0, 0);
}

void SynthPage::onPitchBtnHolded(void *targetPointer, lv_obj_t *labelObj)
{
    SynthPage *instance = (SynthPage *)targetPointer;
    lv_dropdown_open(instance->pitchDropdown);
}

void SynthPage::onOscPwmArcPressed(void * targetPointer, lv_obj_t *valueTextObj, int16_t value, int8_t encoderIndex)
{
    SynthPage *instance = (SynthPage *)targetPointer;
    instance->oscPwm[0] = value;
    AudioSynth.setOscPwm(0, value);
    lv_label_set_text_fmt(valueTextObj, "%d", value);
}

void SynthPage::onOctaveSelect(void *targetPointer, lv_obj_t *valueTextObj, int16_t value)
{
    SynthPage *instance = (SynthPage *)targetPointer;
    // set value text
    lv_label_set_text_fmt(valueTextObj, "%d", value);
    // set octave
    instance->octave = value;
}

void SynthPage::onVelocityBtnPressed(lv_event_t *e)
{
    SynthPage *instance = (SynthPage *)lv_event_get_user_data(e);
    instance->useVelocity = !instance->useVelocity;
    AudioSynth.setUseVelocity(instance->useVelocity);
}

void SynthPage::onPitchBtnPressed(lv_event_t *e)
{
    SynthPage *instance = (SynthPage *)lv_event_get_user_data(e);
    instance->usePitchbend = !instance->usePitchbend;
    if (!instance->usePitchbend)
        AudioSynth.pitchbend(0, 0);
}

void SynthPage::onPitchBtnHolded(lv_event_t *e)
{
    SynthPage *instance = (SynthPage *)lv_event_get_user_data(e);
    lv_dropdown_open(instance->pitchDropdown);
}

void SynthPage::onPitchDropdownSelect(lv_event_t *e)
{
    SynthPage *instance = (SynthPage *)lv_event_get_user_data(e);
    lv_obj_t *dropdown = lv_event_get_target(e);
    uint8_t id = lv_dropdown_get_selected(dropdown);
    instance->pitchbendRange = id + 1;
    lv_label_set_text_fmt(instance->pitchBtnNew->getLabelObject(), "Pitch: %d", instance->pitchbendRange);
}

void SynthPage::onOctaveSelect(lv_event_t *e)
{
    SynthPage *instance = (SynthPage *)lv_event_get_user_data(e);
    lv_obj_t *btn = lv_event_get_target(e);
    if (Gui_getObjIdFlag(btn) == 1)
    {
        // increase
        instance->onBtnPressed(BTN_FN1);
    }
    else
    {
        // decrease
        instance->onBtnPressed(BTN_FN0);
    }
}

void SynthPage::onVolArcPressed(lv_event_t *e)
{
    SynthPage *instance = (SynthPage *)lv_event_get_user_data(e);
    lv_obj_t *arc = lv_event_get_target(e);
    int8_t value = lv_arc_get_value(arc);
    if (enc[3] != NULL)
        enc[3]->setCurrentReading(value + VOL_OFFSET);
    instance->volume = value;
    AudioSynth.setMasterVol(value);
    lv_label_set_text_fmt(Gui_ParamArcGetValueText(arc), "%d", value);
}

// re-configure encoders when menu page has changed
void SynthPage::onMenuPageChange(lv_event_t *e)
{
    // todo: between configreEncoders(), lv_event... lots of arc+encoder stuff is repeated...
    SynthPage *instance = (SynthPage *)lv_event_get_user_data(e);
    instance->configureEncoders();
    lv_obj_t *curMenu = lv_menu_get_cur_main_page(instance->menu);
    // load values into shared GUI objects and move them to new parent
    // * ENVs
    if (curMenu == instance->menu_ampenv || curMenu == instance->menu_env[0] || curMenu == instance->menu_env[1])
    {
        uint8_t *curVal;
        if (curMenu == instance->menu_env[0])
            curVal = instance->envVal[0];
        else if (curMenu == instance->menu_env[1])
            curVal = instance->envVal[1];
        else
            curVal = instance->ampEnvVal;

        for (uint8_t arcId = 0; arcId < 5; arcId++)
        {
            lv_arc_set_value(instance->envArc[arcId], curVal[arcId]);
            lv_event_send(instance->envArc[arcId], LV_EVENT_VALUE_CHANGED, NULL);
        }
        lv_obj_set_parent(instance->envMenuArea, curMenu);
    }
    // *OSCs
    if (curMenu == instance->menu_osc[0] || curMenu == instance->menu_osc[1])
    {
        uint8_t id;
        if (curMenu == instance->menu_osc[0])
            id = 0;
        else
            id = 1;

        lv_dropdown_set_selected(instance->oscWaveDropdown, instance->oscWaveform[id]);
        lv_event_send(instance->oscWaveDropdown, LV_EVENT_VALUE_CHANGED, NULL);

        Gui_SpinboxSetValue(instance->oscOctaveSpinbox, instance->oscOctave[id]);
        AudioSynth.setOscOctave(id, instance->oscOctave[id]);

        Gui_SpinboxSetValue(instance->oscSemiSpinbox, instance->oscSemi[id]);
        AudioSynth.setOscSemi(id, instance->oscSemi[id]);

        // lv_arc_set_value(instance->oscArc[0], instance->oscPwm[id]);
        // lv_event_send(instance->oscArc[0], LV_EVENT_VALUE_CHANGED, NULL);

        lv_arc_set_value(instance->oscArc[1], instance->oscDetune[id]);
        lv_event_send(instance->oscArc[1], LV_EVENT_VALUE_CHANGED, NULL);

        lv_arc_set_value(instance->oscArc[2], instance->oscLevel[id]);
        lv_event_send(instance->oscArc[2], LV_EVENT_VALUE_CHANGED, NULL);

        lv_obj_set_parent(instance->oscMenuArea, curMenu);
    }
}

void SynthPage::onOscWaveSelect(lv_event_t *e)
{
    SynthPage *instance = (SynthPage *)lv_event_get_user_data(e);
    lv_obj_t *dropdown = lv_event_get_target(e);
    uint8_t wave = lv_dropdown_get_selected(dropdown);
    // get which menu we're in
    lv_obj_t *curMenu = lv_menu_get_cur_main_page(instance->menu);
    uint8_t menuId = 0;
    if (curMenu == instance->menu_osc[0])
        menuId = 0;
    else if (curMenu == instance->menu_osc[1])
        menuId = 1;
    else
        return;

    AudioSynth.setOscWaveform(menuId, wave);
    instance->oscWaveform[menuId] = wave;
    const lv_img_dsc_t *img = instance->getOscWaveImg(wave);
    lv_img_set_src(instance->oscWaveImg, img);
    lv_img_set_src(instance->oscWaveItemImg[menuId], img);
}

void SynthPage::onOscArcPressed(lv_event_t *e)
{
    SynthPage *instance = (SynthPage *)lv_event_get_user_data(e);
    lv_obj_t *arc = lv_event_get_target(e);
    int8_t value = lv_arc_get_value(arc);
    uint8_t arcId = Gui_getObjIdFlag(arc);
    // get which menu we're in
    lv_obj_t *curMenu = lv_menu_get_cur_main_page(instance->menu);
    uint8_t menuId = 0;
    if (curMenu == instance->menu_osc[0])
        menuId = 0;
    else if (curMenu == instance->menu_osc[1])
        menuId = 1;
    else
        return;

    switch (arcId)
    {
    case 0:
        // pwm
        // if (enc[0] != NULL)
        //     enc[0]->setCurrentReading(value);
        // instance->oscPwm[menuId] = value;
        // AudioSynth.setOscPwm(menuId, value);
        // lv_label_set_text_fmt(Gui_ParamArcGetValueText(arc), "%d", value);
        break;
    case 1:
        // detune
        if (enc[1] != NULL)
            enc[1]->setCurrentReading(value + 100);
        instance->oscDetune[menuId] = value;
        AudioSynth.setOscDetune(menuId, value * 0.01f);
        lv_label_set_text_fmt(Gui_ParamArcGetValueText(arc), "%d", value);
        break;
    case 2:
        // level
        if (enc[2] != NULL)
            enc[2]->setCurrentReading(value);
        instance->oscLevel[menuId] = value;
        AudioSynth.setOscLevel(menuId, value);
        lv_label_set_text_fmt(Gui_ParamArcGetValueText(arc), "%d", value);
        break;
    }
}

void SynthPage::onOscOctaveSelect(lv_event_t *e)
{
    SynthPage *instance = (SynthPage *)lv_event_get_user_data(e);
    lv_obj_t *btn = lv_event_get_target(e);
    lv_obj_t *curMenu = lv_menu_get_cur_main_page(instance->menu);
    uint8_t id = 0;
    if (curMenu == instance->menu_osc[0])
        id = 0;
    else if (curMenu == instance->menu_osc[1])
        id = 1;

    if (Gui_getObjIdFlag(btn) == 1)
    {
        // increase
        instance->oscOctave[id]++;
        if (instance->oscOctave[id] > 2)
            instance->oscOctave[id] = 2;
    }
    else
    {
        // decrease
        instance->oscOctave[id]--;
        if (instance->oscOctave[id] < -2)
            instance->oscOctave[id] = -2;
    }
    AudioSynth.setOscOctave(id, instance->oscOctave[id]);
    Gui_SpinboxSetValue(instance->oscOctaveSpinbox, instance->oscOctave[id]);
}

void SynthPage::onOscSemiSelect(lv_event_t *e)
{
    SynthPage *instance = (SynthPage *)lv_event_get_user_data(e);
    lv_obj_t *btn = lv_event_get_target(e);
    lv_obj_t *curMenu = lv_menu_get_cur_main_page(instance->menu);
    uint8_t id = 0;
    if (curMenu == instance->menu_osc[0])
        id = 0;
    else if (curMenu == instance->menu_osc[1])
        id = 1;

    if (Gui_getObjIdFlag(btn) == 1)
    {
        // increase
        instance->oscSemi[id]++;
        if (instance->oscSemi[id] > 12)
            instance->oscSemi[id] = 12;
    }
    else
    {
        // decrease
        instance->oscSemi[id]--;
        if (instance->oscSemi[id] < -12)
            instance->oscSemi[id] = -12;
    }
    AudioSynth.setOscSemi(id, instance->oscSemi[id]);
    Gui_SpinboxSetValue(instance->oscSemiSpinbox, instance->oscSemi[id]);
}

void SynthPage::onNoiseArcPressed(lv_event_t *e)
{
    SynthPage *instance = (SynthPage *)lv_event_get_user_data(e);
    lv_obj_t *arc = lv_event_get_target(e);
    int16_t value = lv_arc_get_value(arc);

    enc[0]->setCurrentReading(value);
    instance->noiseLevel = value;
    AudioSynth.setNoiseLevel(value);
    lv_label_set_text_fmt(Gui_ParamArcGetValueText(arc), "%d", value);
}

void SynthPage::onEnvArcPressed(lv_event_t *e)
{
    SynthPage *instance = (SynthPage *)lv_event_get_user_data(e);
    lv_obj_t *arc = lv_event_get_target(e);
    int16_t value = lv_arc_get_value(arc);
    uint8_t arcId = Gui_getObjIdFlag(arc);
    // get which menu we're in
    lv_obj_t *curMenu = lv_menu_get_cur_main_page(instance->menu);
    uint8_t menuId = 0;
    uint8_t *curVal;
    if (curMenu == instance->menu_env[0])
    {
        menuId = 1;
        curVal = instance->envVal[0];
    }
    else if (curMenu == instance->menu_env[1])
    {
        menuId = 2;
        curVal = instance->envVal[1];
    }
    else
    {
        menuId = 0;
        curVal = instance->ampEnvVal;
    }
    // set values
    float envParam = powf(ENV_VAL_INCREMENT, value) - 1; // sustain is a special case, handled below.
    switch (arcId)
    {
    case 0:
        // delay
        curVal[arcId] = value;
        AudioSynth.setEnvDelay(menuId, envParam);
        break;
    case 1:
        // attack
        enc[0]->setCurrentReading(value);
        curVal[arcId] = value;
        AudioSynth.setEnvAttack(menuId, envParam);
        break;
    case 2:
        // decay
        enc[1]->setCurrentReading(value);
        curVal[arcId] = value;
        AudioSynth.setEnvDecay(menuId, envParam);
        break;
    case 3:
        // sustain
        enc[2]->setCurrentReading(value);
        curVal[arcId] = value;
        envParam = value * 0.01f;
        AudioSynth.setEnvSustain(menuId, envParam);
        break;
    case 4:
        // release
        enc[3]->setCurrentReading(value);
        curVal[arcId] = value;
        AudioSynth.setEnvRelease(menuId, envParam);
        break;
    }
    // envelope graph needs all envelope values...
    instance->envGraphNew->setEnvelope(
                         powf(ENV_VAL_INCREMENT, curVal[0]) - 1,
                         powf(ENV_VAL_INCREMENT, curVal[1]) - 1,
                         powf(ENV_VAL_INCREMENT, curVal[2]) - 1,
                         curVal[3] * 0.01f,
                         powf(ENV_VAL_INCREMENT, curVal[4]) - 1);

    // set displayed value for GUI
    int decimal;
    if (arcId != 3)
    {
        // units (S of ms)
        if (envParam >= 1000)
        {
            envParam /= 1000.0f;
            lv_label_set_text(Gui_ParamArcGetUnitText(instance->envArc[arcId]), "S");
        }
        else
        {
            lv_label_set_text(Gui_ParamArcGetUnitText(instance->envArc[arcId]), "ms");
        }
        // decimal count
        if (envParam < 10)
            decimal = 2;
        else if (envParam < 100)
            decimal = 1;
        else
            decimal = 0;
        lv_label_set_text_fmt(Gui_ParamArcGetValueText(arc), "%.*f", decimal, envParam);
    }
    else // sustain
    {
        lv_label_set_text_fmt(Gui_ParamArcGetValueText(arc), "%d", curVal[arcId]);
    }
}

void SynthPage::onFilterArcPressed(lv_event_t *e)
{
    SynthPage *instance = (SynthPage *)lv_event_get_user_data(e);
    lv_obj_t *arc = lv_event_get_target(e);
    int16_t value = lv_arc_get_value(arc);
    uint8_t flag = Gui_getObjIdFlag(arc);
    enc[flag]->setCurrentReading(value);
    instance->filterVal[flag] = value;
    float freq;
    int decimal;
    switch (flag)
    {
    case 0: // cut off
        freq = pow10f(value / 100.0f) * 20.0f;
        AudioSynth.setLadderFreq(freq);
        if (freq >= 1000)
        {
            freq /= 1000.0f;
            lv_label_set_text(Gui_ParamArcGetUnitText(arc), "kHz");
        }
        else
        {
            lv_label_set_text(Gui_ParamArcGetUnitText(arc), "Hz");
        }
        if (freq < 100)
            decimal = 2;
        else
            decimal = 1;
        lv_label_set_text_fmt(Gui_ParamArcGetValueText(arc), "%.*f", decimal, freq);
        break;
    case 1: // resonance
        AudioSynth.setLadderResonance(value / 100.0f);
        lv_label_set_text_fmt(Gui_ParamArcGetValueText(arc), "%d", value);
        break;
    case 2: // drive
        AudioSynth.setLadderDrive(value / 100.0f);
        lv_label_set_text_fmt(Gui_ParamArcGetValueText(arc), "%d", value);
        break;
    case 3: // passband gain
        AudioSynth.setLadderPassbandGain(value / 100.0f);
        lv_label_set_text_fmt(Gui_ParamArcGetValueText(arc), "%d", value);
        break;
    }
}

void SynthPage::onLfoWaveSelect(lv_event_t *e)
{
    SynthPage *instance = (SynthPage *)lv_event_get_user_data(e);
    lv_obj_t *dropdown = lv_event_get_target(e);
    uint8_t wave = lv_dropdown_get_selected(dropdown);
    uint8_t id = Gui_getObjIdFlag(dropdown);

    AudioSynth.setLfoWaveform(id, wave);
    instance->lfoWaveform[id] = id;
    const lv_img_dsc_t *img = instance->getLfoWaveImg(wave);
    lv_img_set_src(instance->lfoWaveImg[id], img);
    lv_img_set_src(instance->lfoWaveItemImg[id], img);
}

void SynthPage::onLfoArcPressed(lv_event_t *e)
{
    SynthPage *instance = (SynthPage *)lv_event_get_user_data(e);
    lv_obj_t *arc = lv_event_get_target(e);
    int16_t value = lv_arc_get_value(arc);
    uint8_t flag = Gui_getObjIdFlag(arc);
    lv_obj_t *curMenu;
    if (lv_event_get_param(e) == NULL)
        curMenu = lv_menu_get_cur_main_page(instance->menu);
    else
        curMenu = (lv_obj_t *)lv_event_get_param(e);

    uint8_t id = 0;
    if (curMenu == instance->menu_lfo[0])
        id = 0;
    else if (curMenu == instance->menu_lfo[1])
        id = 1;
    enc[flag]->setCurrentReading(value);
    instance->lfoVal[id][flag] = value;
    float freq;
    int decimal;
    switch (flag)
    {
    case 0: // frequency
        freq = powf(2, value / 50.0f) - 1;
        AudioSynth.setLfoFreq(id, freq);
        if (freq < 10)
            decimal = 3;
        else if (freq < 100)
            decimal = 2;
        else
            decimal = 1;
        lv_label_set_text_fmt(Gui_ParamArcGetValueText(arc), "%.*f", decimal, freq);
        break;
    case 1: // level
        AudioSynth.setLfoLevel(id, value / 100.0f);
        lv_label_set_text_fmt(Gui_ParamArcGetValueText(arc), "%d", value);
        break;
    }
}

void SynthPage::onNewModBtnPressed(lv_event_t *e)
{
    SynthPage *instance = (SynthPage *)lv_event_get_user_data(e);
    // add modulation
    int8_t id = AudioSynth.addModulation(MOD_SRC_NONE, MOD_TGT_NONE);
    if (id != -1)
    {
        // create a new mod entry
        instance->createModEntry(instance->modMenuArea, id);
        // scroll down
        lv_obj_scroll_by_bounded(instance->modMenuArea, 0, -55, LV_ANIM_ON);
    }
}

void SynthPage::onDelModBtnPressed(lv_event_t *e)
{
    SynthPage *instance = (SynthPage *)lv_event_get_user_data(e);
    // get the to be deleted entry
    lv_obj_t *entry = lv_obj_get_parent(lv_event_get_target(e));
    if (entry == NULL)
        return;
    // remove modulation
    AudioSynth.removeModulation(lv_obj_get_child_id(entry));
    // remove the entry
    lv_obj_del_async(entry); // use async because we are still in a callback
}

void SynthPage::onModSourceChange(lv_event_t *e)
{
    SynthPage *instance = (SynthPage *)lv_event_get_user_data(e);
    lv_obj_t *dropdown = lv_event_get_target(e);
    uint8_t src = lv_dropdown_get_selected(dropdown);
    uint8_t id = lv_obj_get_child_id(lv_obj_get_parent(dropdown));
    AudioSynth.setModulationSource(id, src);
    // todo: memory?
}

void SynthPage::onModTargetChange(lv_event_t *e)
{
    SynthPage *instance = (SynthPage *)lv_event_get_user_data(e);
    lv_obj_t *dropdown = lv_event_get_target(e);
    uint8_t tgt = lv_dropdown_get_selected(dropdown);
    uint8_t id = lv_obj_get_child_id(lv_obj_get_parent(dropdown));
    AudioSynth.setModulationTarget(id, tgt);
}

void SynthPage::onModAmountChange(lv_event_t *e)
{
    SynthPage *instance = (SynthPage *)lv_event_get_user_data(e);
    lv_obj_t *slider = lv_event_get_target(e);
    int8_t amount = lv_slider_get_value(slider);
    uint8_t id = lv_obj_get_child_id(lv_obj_get_parent(slider));
    AudioSynth.setModulationAmount(id, float(amount) / 100.0f);
}

void SynthPage::onSamplerWaveformChartPressed(lv_event_t *e)
{
    PageManager.switchPage(PG_SAMPLEEDITOR);
}

void SynthPage::onSamplerArcPressed(lv_event_t *e)
{
    SynthPage *instance = (SynthPage *)lv_event_get_user_data(e);
    lv_obj_t *arc = lv_event_get_target(e);
    int16_t value = lv_arc_get_value(arc);
    uint8_t arcId = Gui_getObjIdFlag(arc);

    switch (arcId)
    {
    case 0: // tune
        enc[arcId]->setCurrentReading(value + 100);
        instance->samplerTune = value;
        // todo: not implemented
        // AudioSynth.setClipTune();
        lv_label_set_text_fmt(Gui_ParamArcGetValueText(arc), "%d", value);
        break;
    case 1: // level
        enc[arcId]->setCurrentReading(value);
        instance->samplerLevel = value;
        AudioSynth.setClipLevel(value);
        lv_label_set_text_fmt(Gui_ParamArcGetValueText(arc), "%d", value);
        break;
    }
}

void SynthPage::onSamplerRootKeyBtnPressed(lv_event_t *e)
{
    SynthPage *instance = (SynthPage *)lv_event_get_user_data(e);
    if (instance->seletctingRootKey)
        return;
    instance->seletctingRootKey = true;
    // show message box
    lv_obj_t *msgbox = lv_msgbox_create(NULL, "Root Key: ", "Press a piano key to select root key.", instance->setRootKeyBtns, false);
    lv_obj_center(msgbox);
    lv_obj_set_style_bg_color(msgbox, lv_color_black(), 0);
    lv_obj_add_event_cb(msgbox, onSamplerRootKeySelectSetPressed, LV_EVENT_VALUE_CHANGED, instance);
    instance->rootKeySelectTitleText = lv_msgbox_get_title(msgbox);
    lv_label_set_text_fmt(instance->rootKeySelectTitleText, "Root Key: %s", noteNumToNoteName(instance->samplerRootKey).c_str());
    lv_obj_set_style_text_font(lv_msgbox_get_title(msgbox), font_large, 0);
}

void SynthPage::onSamplerRootKeySelectSetPressed(lv_event_t *e)
{
    SynthPage *instance = (SynthPage *)lv_event_get_user_data(e);
    lv_obj_t *msgbox = lv_event_get_current_target(e);
    if (lv_msgbox_get_active_btn(msgbox) == 0)
    {
        // set
        instance->seletctingRootKey = false;
        // close msgbox
        lv_msgbox_close(msgbox);
    }
}

void SynthPage::onBtnPressed(uint8_t pin)
{
    int noteNum;
    uint8_t keyNum = PinToKeyNum(pin);
    if (keyNum > 0)
    {
        noteNum = keyNum - 1 + 12 * octave;
        if (seletctingRootKey)
        {
            samplerRootKey = noteNum;
            AudioSynth.setClipBaseNote(noteNum);
            // change button label
            lv_obj_t *label = lv_obj_get_child(rootKeyBtn, 0);
            lv_label_set_text(label, noteNumToNoteName(samplerRootKey).c_str());
            // change msgbox title
            lv_label_set_text_fmt(rootKeySelectTitleText, "Root Key: %s", noteNumToNoteName(noteNum).c_str());
        }
        AudioSynth.noteOn(noteNum);
    }
    else
    {
        switch (pin)
        {
        case BTN_PWR:
            PageManager.switchPage(PG_AUDIO);
            break;
        case BTN_JOY:
            AudioSynth.sustainOn();
            break;
        case BTN_FN0:
            octaveSpinboxNew->pressButtonMinus();
            break;
        case BTN_FN1:
            octaveSpinboxNew->pressButtonPlus();
            break;
        }
    }
}

void SynthPage::onBtnHold(uint8_t pin)
{
    switch (pin)
    {
    case BTN_PWR:
        PageManager.showPowerPopup();
        break;
    }
}

void SynthPage::onBtnReleased(uint8_t pin)
{
    uint8_t noteNum;
    uint8_t keyNum = PinToKeyNum(pin);
    if (keyNum > 0)
    {
        noteNum = keyNum - 1 + 12 * octave;
        AudioSynth.noteOff(noteNum);
    }
    else
    {
        switch (pin)
        {
        case BTN_JOY:
            AudioSynth.sustainOff();
            break;
        }
    }
}

void SynthPage::onEncTurned(uint8_t id, int value)
{

    lv_obj_t *curMenu = lv_menu_get_cur_main_page(menu);
    if (curMenu == menu_main)
    {
        switch (id)
        {
        case 3: // master out volume
            lv_arc_set_value(volArc, value - VOL_OFFSET);
            lv_event_send(volArc, LV_EVENT_VALUE_CHANGED, NULL);
            break;
        }
    }
    else if (curMenu == menu_osc[0] || curMenu == menu_osc[1])
    {
        switch (id)
        {
        case 0: // pwm
            // lv_arc_set_value(oscArc[id], value);
            paramArcBindingTable[0]->encoderCallback(value);
            break;
        case 1: // detune
            lv_arc_set_value(oscArc[id], value - 100);
            break;
        case 2: // level
            lv_arc_set_value(oscArc[id], value);
            break;
        }
        if (id != 0)
            lv_event_send(oscArc[id], LV_EVENT_VALUE_CHANGED, NULL);
    }
    else if (curMenu == menu_noise)
    {
        switch (id)
        {
        case 0: // level
            lv_arc_set_value(noiseArc, value);
            break;
        }
        lv_event_send(noiseArc, LV_EVENT_VALUE_CHANGED, NULL);
    }
    else if (curMenu == menu_ampenv || curMenu == menu_env[0] || curMenu == menu_env[1])
    {
        lv_arc_set_value(envArc[id + 1], value);
        lv_event_send(envArc[id + 1], LV_EVENT_VALUE_CHANGED, NULL);
    }
    else if (curMenu == menu_filter)
    {
        lv_arc_set_value(filterArc[id], value);
        lv_event_send(filterArc[id], LV_EVENT_VALUE_CHANGED, NULL);
    }
    else if (curMenu == menu_lfo[0] || curMenu == menu_lfo[1])
    {
        uint8_t i = curMenu == menu_lfo[0] ? 0 : 1;
        lv_arc_set_value(lfoArc[i][id], value);
        lv_event_send(lfoArc[i][id], LV_EVENT_VALUE_CHANGED, NULL);
    }
    else if (curMenu == menu_sampler)
    {
        switch (id)
        {
        case 0: // tune
            lv_arc_set_value(samplerArc[id], value - 100);
            break;
        default:
            lv_arc_set_value(samplerArc[id], value);
            break;
        }
        lv_event_send(samplerArc[id], LV_EVENT_VALUE_CHANGED, NULL);
    }
}

void SynthPage::onJoyUpdate(int joy_x, int joy_y)
{
    if (usePitchbend)
    {
        AudioSynth.pitchbend(map((float)joy_x, 0, 1019, pitchbendRange, -pitchbendRange), map((float)joy_x, 0, 1019, 1, -1));
    }
    if (useModwheel)
    {
        AudioSynth.modwheel(map((float)joy_y, 0, 1019, -1, 1));
    }
}

void SynthPage::onCCReceive(u_int8_t channel, u_int8_t control, u_int8_t value)
{
}

void SynthPage::configurePage()
{
    // configure encoders
    configureEncoders();
    // setup micorphone for velocity sensing
    sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
    sgtl5000_1.micGain(40);
    AudioIO.setInputVolume(InputTracks::LINEMIC_IN, 0);
    // setup peak module for level meter
    AudioIO.setMixerLevelMode(LevelMeterMode::PRE_FADER);
    lv_arc_set_value(volArc, volume);
    lv_event_send(volArc, LV_EVENT_VALUE_CHANGED, NULL);
    // update current velocity settings
    AudioSynth.setUseVelocity(useVelocity);
    // set reverb FX
    AudioFX.reverb.setWithMem(&reverbMem);
    // set voice mode for AudioSynth
    AudioSynth.setVoiceMode(VOICE_MODE_SYNTH);
    // refresh waveformChart for sampler
    lv_chart_refresh(waveformChart);
}

// configure enocders for according to current menu page
void SynthPage::configureEncoders()
{
    lv_obj_t *curMenu = lv_menu_get_cur_main_page(menu);
    if (curMenu == menu_main)
    {
        enc[3]->changePrecision(30, volume + VOL_OFFSET, false);
    }
    else if (curMenu == menu_osc[0])
    {
        // pwm
        // enc[0]->changePrecision(100, oscPwm[0], false);
        oscArcNew->bindEncoder(0);
        oscArcNew->setValue(oscPwm[0]);
        // detune
        enc[1]->changePrecision(200, oscDetune[0] + 100, false);
        // level
        enc[2]->changePrecision(100, oscLevel[0], false);
    }
    else if (curMenu == menu_osc[1])
    {
        // pwm
        enc[0]->changePrecision(100, oscPwm[1], false);
        // detune
        enc[1]->changePrecision(200, oscDetune[1] + 100, false);
        // level
        enc[2]->changePrecision(100, oscLevel[1], false);
    }
    else if (curMenu == menu_noise)
    {
        // level
        enc[0]->changePrecision(100, noiseLevel, false);
    }
    else if (curMenu == menu_ampenv)
    {
        // attack
        enc[0]->changePrecision(ENV_VAL_MAX, ampEnvVal[1], false);
        // decay
        enc[1]->changePrecision(ENV_VAL_MAX, ampEnvVal[2], false);
        // sustain
        enc[2]->changePrecision(100, ampEnvVal[3], false);
        // release
        enc[3]->changePrecision(ENV_VAL_MAX, ampEnvVal[4], false);
    }
    else if (curMenu == menu_env[0] || curMenu == menu_env[1])
    {
        uint8_t id = curMenu == menu_env[0] ? 0 : 1;
        // attack
        enc[0]->changePrecision(ENV_VAL_MAX, envVal[id][1], false);
        // decay
        enc[1]->changePrecision(ENV_VAL_MAX, envVal[id][2], false);
        // sustain
        enc[2]->changePrecision(100, envVal[id][3], false);
        // release
        enc[3]->changePrecision(ENV_VAL_MAX, envVal[id][4], false);
    }
    else if (curMenu == menu_filter)
    {
        // cut off
        enc[0]->changePrecision(300, filterVal[0], false);
        // resonance
        enc[1]->changePrecision(100, filterVal[1], false);
        // drive
        enc[2]->changePrecision(100, filterVal[2], false);
        // passband gain
        enc[3]->changePrecision(100, filterVal[3], false);
    }
    else if (curMenu == menu_lfo[0] || curMenu == menu_lfo[1])
    {
        uint8_t id = curMenu == menu_lfo[0] ? 0 : 1;
        // freq
        enc[0]->changePrecision(350, lfoVal[id][0], false);
        // level
        enc[1]->changePrecision(100, lfoVal[id][1], false);
    }
    else if (curMenu == menu_sampler)
    {
        // tune
        enc[0]->changePrecision(200, samplerTune + 100, false);
        // level
        enc[1]->changePrecision(100, samplerLevel, false);
    }
}

void SynthPage::setUserData()
{
    // main menu
    octaveSpinboxNew->setValue(octave);
    lv_arc_set_value(volArc, volume);
    lv_event_send(volArc, LV_EVENT_VALUE_CHANGED, NULL);
    AudioSynth.setUseVelocity(useVelocity);
    velocityBtnNew->setToggle(useVelocity);
    lv_dropdown_set_selected(pitchDropdown, pitchbendRange - 1);
    lv_label_set_text_fmt(pitchBtnNew->getLabelObject(), "Pitch: %d", pitchbendRange);
    pitchBtnNew->setToggle(usePitchbend);
    lv_img_set_src(oscWaveItemImg[0], getOscWaveImg(oscWaveform[0]));
    lv_img_set_src(oscWaveItemImg[1], getOscWaveImg(oscWaveform[1]));

    // noise menu
    lv_arc_set_value(noiseArc, noiseLevel);
    AudioSynth.setNoiseLevel(noiseLevel);
    lv_label_set_text_fmt(Gui_ParamArcGetValueText(noiseArc), "%d", noiseLevel);

    // filter menu
    for (uint8_t id = 0; id < 4; id++)
    {
        lv_arc_set_value(filterArc[id], filterVal[id]);
        lv_event_send(filterArc[id], LV_EVENT_VALUE_CHANGED, NULL);
    }
    // lfo1 and lfo2
    for (uint8_t id = 0; id < 2; id++)
    {
        lv_dropdown_set_selected(lfoWaveDropdown[id], lfoWaveform[id]);
        lv_event_send(lfoWaveDropdown[id], LV_EVENT_VALUE_CHANGED, NULL);
        for (uint8_t j = 0; j < 2; j++)
        {
            lv_arc_set_value(lfoArc[id][j], lfoVal[id][j]);
            lv_event_send(lfoArc[id][j], LV_EVENT_VALUE_CHANGED, menu_lfo[id]);
        }
    }
    // todo: set user data of shared GUI objects into audio systems.
}

void SynthPage::update()
{
    float temp_peak = AudioIO.getMixerPeak(MasterTracks::ANALOG_OUT, MixerTracks::INSTRUMENTS).l;
    if (temp_peak >= 0)
    {
        // convert to dB
        float temp_dB = gaintodB(temp_peak);
        if (temp_dB >= -0.1)
            peakHold = PEAK_HOLD_TIME;
        // calulate running average
        temp_peak = (temp_peak + peakAvg * PEAK_AVG_TIME) / (PEAK_AVG_TIME + 1);
        peakAvg = temp_peak;
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

void SynthPage::init()
{
    pageID = PG_SYNTH;
    strcpy(pageName, "Synthesizer");
    // create screen
    screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen, lv_color_black(), 0);
    // create lvgl objects
    lv_obj_t *label;
    lv_obj_t *btn;
    // **MENU OBJECT
    menu = lv_menu_create(screen);
    lv_obj_set_style_bg_color(menu, lv_color_black(), 0);
    lv_obj_set_style_pad_all(menu, 0, 0);
    lv_obj_set_style_border_width(menu, 0, 0);
    lv_obj_set_size(menu, 320, 205);
    lv_obj_set_y(menu, 35);
    btn = lv_menu_get_main_header_back_btn(menu);
    lv_obj_set_style_bg_opa(btn, LV_OPA_100, 0);
    lv_obj_set_style_bg_color(btn, color_Grey, 0);
    label = lv_label_create(btn);
    lv_label_set_text(label, " Back ");
    // *MENU OSC1 and 2-------------------------------------------------------------------
    for (uint8_t menuId = 0; menuId < 2; menuId++)
    {
        char oscName[14];
        strcpy(oscName, (String("Oscillator ") + String(menuId + 1)).c_str());
        menu_osc[menuId] = lv_menu_page_create(menu, oscName);
    }
    // create a menu area to be shared by 2 OSCs
    oscMenuArea = createItemMenuArea(menu_osc[0]);
    lv_obj_clear_flag(oscMenuArea, LV_OBJ_FLAG_SCROLLABLE);
    // *waveform selector
    label = lv_label_create(oscMenuArea);
    lv_label_set_text(label, "Waveform: ");
    lv_obj_align(label, LV_ALIGN_TOP_LEFT, 0, 10);
    oscWaveDropdown = lv_dropdown_create(oscMenuArea);
    lv_dropdown_set_options(oscWaveDropdown, "Sine\nTriangle\nSawtooth\nSquare");
    lv_obj_set_size(oscWaveDropdown, 150, 35);
    lv_obj_align(oscWaveDropdown, LV_ALIGN_TOP_LEFT, 90, 0);
    lv_obj_add_flag(oscWaveDropdown, LV_OBJ_FLAG_OVERFLOW_VISIBLE);
    lv_obj_add_event_cb(oscWaveDropdown, onOscWaveSelect, LV_EVENT_VALUE_CHANGED, this);
    oscWaveImg = lv_img_create(oscMenuArea);
    lv_img_set_src(oscWaveImg, &sin_wave);
    lv_obj_align(oscWaveImg, LV_ALIGN_TOP_LEFT, 250, 5);
    // *octave selector
    label = lv_label_create(oscMenuArea);
    lv_label_set_text(label, "Octave: ");
    lv_obj_align(label, LV_ALIGN_TOP_LEFT, 0, 50);
    oscOctaveSpinbox = Gui_CreateSpinbox(oscMenuArea, onOscOctaveSelect, this);
    lv_obj_align(oscOctaveSpinbox, LV_ALIGN_TOP_LEFT, 65, 43);
    // *semitone selector
    label = lv_label_create(oscMenuArea);
    lv_label_set_text(label, "Semi: ");
    lv_obj_align(label, LV_ALIGN_TOP_LEFT, 165, 50);
    oscSemiSpinbox = Gui_CreateSpinbox(oscMenuArea, onOscSemiSelect, this);
    lv_obj_align(oscSemiSpinbox, LV_ALIGN_TOP_LEFT, 210, 43);
    // *pwm arc
    oscArcNew =  new ParamArc(oscMenuArea, 1, "PWM", "%", false);
    lv_obj_align(oscArcNew->getLvglObject(), LV_ALIGN_TOP_LEFT, 0, 100);
    // set value
    oscArcNew->setRangeMax(100);
    oscArcNew->setCallback(onOscPwmArcPressed, this);
    // oscArcNew->bindEncoder(0);

    // oscArc[0] = Gui_CreateParamArc(oscMenuArea, 1, "PWM", "%", false);
    // Gui_setObjIdFlag(oscArc[0], 0);
    // lv_obj_align(oscArc[0], LV_ALIGN_TOP_LEFT, 0, 100);
    // // set value
    // lv_arc_set_range(oscArc[0], 0, 100);
    // lv_obj_add_event_cb(oscArc[0], onOscArcPressed, LV_EVENT_VALUE_CHANGED, this);
    // *detune arc
    oscArc[1] = Gui_CreateParamArc(oscMenuArea, 2, "Detune", "cent", false);
    Gui_setObjIdFlag(oscArc[1], 1);
    lv_obj_align(oscArc[1], LV_ALIGN_TOP_LEFT, 80, 100);
    // set value
    lv_arc_set_range(oscArc[1], -100, 100);
    lv_obj_add_event_cb(oscArc[1], onOscArcPressed, LV_EVENT_VALUE_CHANGED, this);
    // *level arc
    oscArc[2] = Gui_CreateParamArc(oscMenuArea, 3, "Level", "%", false);
    Gui_setObjIdFlag(oscArc[2], 2);
    lv_obj_align(oscArc[2], LV_ALIGN_TOP_LEFT, 160, 100);
    // set value
    lv_arc_set_range(oscArc[2], 0, 100);
    lv_obj_add_event_cb(oscArc[2], onOscArcPressed, LV_EVENT_VALUE_CHANGED, this);

    // *MENU NOISE------------------------------------------------------------------
    menu_noise = lv_menu_page_create(menu, "Noise Generator");
    lv_obj_t *menu_area = createItemMenuArea(menu_noise);
    // *level arc
    noiseArc = Gui_CreateParamArc(menu_area, 1, "Level", "%", false);
    lv_obj_align(noiseArc, LV_ALIGN_TOP_LEFT, 5, 20);
    // set value
    lv_arc_set_range(noiseArc, 0, 100);
    lv_obj_add_event_cb(noiseArc, onNoiseArcPressed, LV_EVENT_VALUE_CHANGED, this);

    // *MENU AMPENV-----------------------------------------------------------------
    menu_ampenv = lv_menu_page_create(menu, "Amp Envelope");

    // *MENU ENV1 AND ENV2------------------------------------------------------------
    for (uint8_t i = 0; i < 2; i++)
    {
        char title[11];
        strcpy(title, (String("Envelope ") + String(i + 1)).c_str());
        menu_env[i] = lv_menu_page_create(menu, title);
    }
    // *create a menu area to be shared by all envelopes
    envMenuArea = createItemMenuArea(menu_ampenv); // set parent to amp env menu for now
    lv_obj_clear_flag(envMenuArea, LV_OBJ_FLAG_SCROLLABLE);
    // *envelope graph
    envGraphNew = new EnvelopeGraph(envMenuArea, 320, 90);
    // *5 envelope arcs
    const char *envTitle[] = {"Delay", "Attack", "Decay", "Sustain", "Release"};
    for (uint8_t arcId = 0; arcId < 5; arcId++)
    {
        envArc[arcId] = Gui_CreateParamArc(envMenuArea, arcId, envTitle[arcId], arcId == 3 ? "%" : "ms", false);
        lv_obj_set_size(envArc[arcId], 55, 55);
        lv_obj_align(envArc[arcId], LV_ALIGN_BOTTOM_MID, -126 + 63 * arcId, 0);
        Gui_setObjIdFlag(envArc[arcId], arcId);
        if (arcId == 3) // sustain arc
            lv_arc_set_range(envArc[arcId], 0, 100);
        else // everything else
            lv_arc_set_range(envArc[arcId], 0, ENV_VAL_MAX);
        lv_obj_add_event_cb(envArc[arcId], onEnvArcPressed, LV_EVENT_VALUE_CHANGED, this);
    }

    // *MENU FILTER-----------------------------------------------------------------
    menu_filter = lv_menu_page_create(menu, "Low Pass Filter");
    menu_area = createItemMenuArea(menu_filter);
    // * 4 filter arcs
    const char *filterTitle[] = {"Cutoff", "Resonance", "Drive", "Passband\nGain"};
    for (uint8_t i = 0; i < 4; i++)
    {
        switch (i)
        {
        case 0: // cut off
            filterArc[i] = Gui_CreateParamArc(menu_area, i + 1, filterTitle[i], "Hz", false);
            lv_arc_set_range(filterArc[i], 0, 300);
            break;
        case 1: // resonance
        case 2: // drive
        case 3: // passband gain
            filterArc[i] = Gui_CreateParamArc(menu_area, i + 1, filterTitle[i], "%", false);
            lv_arc_set_range(filterArc[i], 0, 100);
            break;
        }
        lv_obj_align(filterArc[i], LV_ALIGN_BOTTOM_MID, -120 + 80 * i, -80);
        Gui_setObjIdFlag(filterArc[i], i);
        lv_obj_add_event_cb(filterArc[i], onFilterArcPressed, LV_EVENT_VALUE_CHANGED, this);
    }

    // *MENU LFO1 AND LFO2-----------------------------------------------------------------
    for (uint8_t id = 0; id < 2; id++)
    {
        char title[28];
        strcpy(title, (String("Low Frequency Oscillator ") + String(id + 1)).c_str());
        menu_lfo[id] = lv_menu_page_create(menu, title);
        menu_area = createItemMenuArea(menu_lfo[id]);
        lv_obj_clear_flag(menu_area, LV_OBJ_FLAG_SCROLLABLE);
        // *waveform selector
        label = lv_label_create(menu_area);
        lv_label_set_text(label, "Waveform: ");
        lv_obj_align(label, LV_ALIGN_TOP_LEFT, 0, 10);
        lfoWaveDropdown[id] = lv_dropdown_create(menu_area);
        lv_dropdown_set_options(lfoWaveDropdown[id], "Sine\nTriangle\nSawtooth\nRev-Sawtooth\nSquare\nSample&Hold");
        lv_obj_set_size(lfoWaveDropdown[id], 150, 35);
        lv_obj_align(lfoWaveDropdown[id], LV_ALIGN_TOP_LEFT, 90, 0);
        lv_obj_add_flag(lfoWaveDropdown[id], LV_OBJ_FLAG_OVERFLOW_VISIBLE);
        Gui_setObjIdFlag(lfoWaveDropdown[id], id);
        lv_obj_add_event_cb(lfoWaveDropdown[id], onLfoWaveSelect, LV_EVENT_VALUE_CHANGED, this);
        lfoWaveImg[id] = lv_img_create(menu_area);
        lv_img_set_src(lfoWaveImg[id], &sin_wave);
        lv_obj_align(lfoWaveImg[id], LV_ALIGN_TOP_LEFT, 250, 5);
        // *frequency arc
        lfoArc[id][0] = Gui_CreateParamArc(menu_area, 1, "Frequency", "Hz", false);
        lv_arc_set_range(lfoArc[id][0], 0, 350);
        lv_obj_align(lfoArc[id][0], LV_ALIGN_BOTTOM_MID, -120, -40);
        Gui_setObjIdFlag(lfoArc[id][0], 0);
        lv_obj_add_event_cb(lfoArc[id][0], onLfoArcPressed, LV_EVENT_VALUE_CHANGED, this);
        // *level arc
        lfoArc[id][1] = Gui_CreateParamArc(menu_area, 2, "Level", "%", false);
        lv_arc_set_range(lfoArc[id][1], 0, 100);
        lv_obj_align(lfoArc[id][1], LV_ALIGN_BOTTOM_MID, -40, -40);
        Gui_setObjIdFlag(lfoArc[id][1], 1);
        lv_obj_add_event_cb(lfoArc[id][1], onLfoArcPressed, LV_EVENT_VALUE_CHANGED, this);
    }

    // *MENU MODULATION-----------------------------------------------------------------
    menu_mod = lv_menu_page_create(menu, "Modulation");
    modMenuArea = createItemMenuArea(menu_mod);
    // column flex layout
    lv_obj_set_flex_flow(modMenuArea, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_scroll_dir(modMenuArea, LV_DIR_VER);
    // "new modulation" btn
    createNewModBtn(modMenuArea);

    // * MENU SAMPLER-------------------------------------------------------------------
    menu_sampler = lv_menu_page_create(menu, "Sampler");
    menu_area = createItemMenuArea(menu_sampler);
    // *sample waveform viewer
    waveformChart = Gui_CreateWaveformChart(menu_area, 305, 60, &serMax, &serMin, samplerWaveformPointsMax, samplerWaveformPointsMin);
    lv_chart_set_point_count(waveformChart, 1000);
    lv_obj_set_style_pad_all(waveformChart, 3, 0);
    lv_obj_add_event_cb(waveformChart, onSamplerWaveformChartPressed, LV_EVENT_PRESSED, this);
    // root key selector
    label = lv_label_create(menu_area);
    lv_label_set_text(label, "Root Key: ");
    lv_obj_align(label, LV_ALIGN_LEFT_MID, 5, -10);
    rootKeyBtn = Gui_CreateButton(menu_area, -1, 25, "C4");
    lv_obj_align(rootKeyBtn, LV_ALIGN_LEFT_MID, 80, -10);
    lv_obj_add_event_cb(rootKeyBtn, onSamplerRootKeyBtnPressed, LV_EVENT_PRESSED, this);
    // tune arc
    samplerArc[0] = Gui_CreateParamArc(menu_area, 1, "Tune", "cent", false);
    lv_arc_set_range(samplerArc[0], -100, 100);
    lv_obj_align(samplerArc[0], LV_ALIGN_BOTTOM_MID, -120, 0);
    Gui_setObjIdFlag(samplerArc[0], 0);
    lv_obj_add_event_cb(samplerArc[0], onSamplerArcPressed, LV_EVENT_VALUE_CHANGED, this);
    // level arc
    samplerArc[1] = Gui_CreateParamArc(menu_area, 2, "Level", "%", false);
    lv_arc_set_range(samplerArc[1], 0, 100);
    lv_obj_align(samplerArc[1], LV_ALIGN_BOTTOM_MID, -40, 0);
    Gui_setObjIdFlag(samplerArc[1], 1);
    lv_obj_add_event_cb(samplerArc[1], onSamplerArcPressed, LV_EVENT_VALUE_CHANGED, this);

    // *MENU MAIN-------------------------------------------------------------------
    menu_main = lv_menu_page_create(menu, NULL);
    lv_menu_set_page(menu, menu_main);
    // *SELECT AREA
    lv_obj_t *selectArea = lv_obj_create(menu_main);
    // lv_obj_remove_style_all(selectArea);
    lv_obj_set_style_bg_color(selectArea, lv_color_black(), 0);
    lv_obj_set_style_pad_all(selectArea, 5, 0);
    lv_obj_set_size(selectArea, 320, 100);

    // *Quick parameters
    label = lv_label_create(selectArea);
    lv_label_set_text(label, "Quick Parameters:\nIn Development");
    lv_obj_set_style_text_color(label, color_Grey, 0);

    // *volume arc
    volArc = Gui_CreateParamArc(selectArea, 4, "Gain", "dB", false);
    lv_obj_align(volArc, LV_ALIGN_TOP_RIGHT, -5, 20);
    // set value
    lv_arc_set_range(volArc, -15, 15);
    lv_obj_add_event_cb(volArc, onVolArcPressed, LV_EVENT_VALUE_CHANGED, this);

    // *octave select
    label = lv_label_create(selectArea);
    lv_label_set_text(label, "Octave");
    lv_obj_set_style_text_font(label, font_small, 0);
    lv_obj_set_pos(label, 23, 38);
    octaveSpinboxNew = new Spinbox(selectArea, 1);
    octaveSpinboxNew->setRange(1, 8);
    octaveSpinboxNew->setCallback(onOctaveSelect, this);
    lv_obj_align(octaveSpinboxNew->getLvglObject(), LV_ALIGN_BOTTOM_LEFT, 0, 0);

    // *velocity button
    velocityBtnNew = new Button(selectArea, 60, 30, "Velocity", true);
    lv_obj_align(velocityBtnNew->getLvglObject(), LV_ALIGN_BOTTOM_LEFT, 100, 0);
    velocityBtnNew->setPressedCallback(onVelocityBtnPressed, this);
    lv_obj_set_style_text_font(velocityBtnNew->getLabelObject(), font_small, 0);

    // *pitch bend button
    // add a dropdown right under it
    pitchDropdown = lv_dropdown_create(selectArea);
    lv_obj_set_size(pitchDropdown, 60, 30);
    lv_obj_align(pitchDropdown, LV_ALIGN_BOTTOM_LEFT, 170, 0);
    lv_dropdown_set_options(pitchDropdown, "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12");
    lv_obj_add_event_cb(pitchDropdown, onPitchDropdownSelect, LV_EVENT_VALUE_CHANGED, this);

    pitchBtnNew = new Button(selectArea, 60, 30, "Pitch", true);
    lv_obj_align(pitchBtnNew->getLvglObject(), LV_ALIGN_BOTTOM_LEFT, 170, 0);
    pitchBtnNew->setPressedCallback(onPitchBtnPressed, this);
    pitchBtnNew->setHoldCallback(onPitchBtnHolded, this);
    lv_obj_set_style_text_font(pitchBtnNew->getLabelObject(), font_small, 0);

    //  *volume bar
    volBar = Gui_CreateVolumeMeter(selectArea, 115, 10);
    lv_obj_align(volBar, LV_ALIGN_BOTTOM_LEFT, 100, -35);
    peakLed = Gui_CreatePeakLed(volBar, 10, 10);
    lv_obj_align(peakLed, LV_ALIGN_RIGHT_MID, 15, 0);

    // *ITEM AREA
    /*
        osc1  | noise  | ampenv | lfo1
        osc2  | filter | env1   | lfo2
      sampler |  mod   | env2   |
    */
    lv_obj_t *itemArea = lv_obj_create(menu_main);
    lv_obj_remove_style_all(itemArea);
    lv_obj_set_size(itemArea, 320, 105);
    lv_obj_set_y(itemArea, 135);

    // *column 1
    lv_obj_t *col = lv_obj_create(itemArea);
    lv_obj_remove_style_all(col);
    lv_obj_set_size(col, 80, 105);
    lv_obj_set_style_pad_all(col, 2, 0);
    // osc1 button
    btn = createItemBtn(col, "OSC 1");
    oscWaveItemImg[0] = lv_img_create(btn);
    lv_obj_set_align(oscWaveItemImg[0], LV_ALIGN_LEFT_MID);
    lv_menu_set_load_page_event(menu, btn, menu_osc[0]);
    // osc2 button
    btn = createItemBtn(col, "OSC2");
    lv_obj_set_y(btn, 35);
    oscWaveItemImg[1] = lv_img_create(btn);
    lv_obj_set_align(oscWaveItemImg[1], LV_ALIGN_LEFT_MID);
    lv_menu_set_load_page_event(menu, btn, menu_osc[1]);
    // sampler button
    btn = createItemBtn(col, "Sampler");
    lv_obj_set_y(btn, 70);
    lv_obj_center(lv_obj_get_child(btn, 0));
    lv_menu_set_load_page_event(menu, btn, menu_sampler);

    // *column 2
    col = lv_obj_create(itemArea);
    lv_obj_remove_style_all(col);
    lv_obj_set_size(col, 80, 105);
    lv_obj_set_style_pad_all(col, 2, 0);
    lv_obj_set_x(col, 80);
    // noise button
    btn = createItemBtn(col, "Noise");
    lv_obj_center(lv_obj_get_child(btn, 0));
    lv_menu_set_load_page_event(menu, btn, menu_noise);
    // filter button
    btn = createItemBtn(col, "Filter");
    lv_obj_set_y(btn, 35);
    lv_obj_center(lv_obj_get_child(btn, 0));
    lv_menu_set_load_page_event(menu, btn, menu_filter);
    // mod button
    btn = createItemBtn(col, "MOD");
    lv_obj_set_y(btn, 70);
    lv_obj_center(lv_obj_get_child(btn, 0));
    lv_menu_set_load_page_event(menu, btn, menu_mod);

    // *column 3
    col = lv_obj_create(itemArea);
    lv_obj_remove_style_all(col);
    lv_obj_set_size(col, 80, 105);
    lv_obj_set_style_pad_all(col, 2, 0);
    lv_obj_set_x(col, 160);
    // ampenv button
    btn = createItemBtn(col, "AMPENV");
    lv_obj_center(lv_obj_get_child(btn, 0));
    lv_menu_set_load_page_event(menu, btn, menu_ampenv);
    // env1 button
    btn = createItemBtn(col, "ENV1");
    lv_obj_set_y(btn, 35);
    lv_obj_center(lv_obj_get_child(btn, 0));
    lv_menu_set_load_page_event(menu, btn, menu_env[0]);
    // env2 button
    btn = createItemBtn(col, "ENV2");
    lv_obj_set_y(btn, 70);
    lv_obj_center(lv_obj_get_child(btn, 0));
    lv_menu_set_load_page_event(menu, btn, menu_env[1]);

    // *column 4
    col = lv_obj_create(itemArea);
    lv_obj_remove_style_all(col);
    lv_obj_set_size(col, 80, 105);
    lv_obj_set_style_pad_all(col, 2, 0);
    lv_obj_set_x(col, 240);
    // lfo1 button
    btn = createItemBtn(col, "LFO 1");
    lv_obj_set_y(btn, 0);
    lfoWaveItemImg[0] = lv_img_create(btn);
    lv_obj_set_align(lfoWaveItemImg[0], LV_ALIGN_LEFT_MID);
    lv_menu_set_load_page_event(menu, btn, menu_lfo[0]);
    // lfo2 button
    btn = createItemBtn(col, "LFO2");
    lv_obj_set_y(btn, 35);
    lfoWaveItemImg[1] = lv_img_create(btn);
    lv_obj_set_align(lfoWaveItemImg[1], LV_ALIGN_LEFT_MID);
    lv_menu_set_load_page_event(menu, btn, menu_lfo[1]);

    // *At last, add menu change callback
    lv_obj_add_event_cb(menu, onMenuPageChange, LV_EVENT_VALUE_CHANGED, this);
}

void SynthPage::load()
{
}

void SynthPage::unload()
{
}

lv_obj_t *SynthPage::createItemBtn(lv_obj_t *parent, const char *text)
{
    lv_obj_t *btn = Gui_CreateButton(parent, 76, 30);
    lv_obj_set_style_pad_all(btn, 4, 0);
    lv_obj_t *label = lv_label_create(btn);
    lv_label_set_text(label, text);
    lv_obj_set_align(label, LV_ALIGN_RIGHT_MID);

    return btn;
}

lv_obj_t *SynthPage::createItemMenuArea(lv_obj_t *menu)
{
    lv_obj_t *menu_area = lv_obj_create(menu);
    lv_obj_remove_style_all(menu_area);
    lv_obj_set_style_pad_all(menu_area, 5, 0);
    lv_obj_set_size(menu_area, 320, 178);

    return menu_area;
}

const lv_img_dsc_t *SynthPage::getOscWaveImg(uint8_t id)
{
    const lv_img_dsc_t *img;
    switch (id)
    {
    default:
        img = &sin_wave;
        break;
    case 1:
        img = &tri_wave;
        break;
    case 2:
        img = &saw_wave;
        break;
    case 3:
        img = &sqr_wave;
        break;
    }
    return img;
}

const lv_img_dsc_t *SynthPage::getLfoWaveImg(uint8_t id)
{
    const lv_img_dsc_t *img;
    switch (id)
    {
    default:
        img = &sin_wave;
        break;
    case 1:
        img = &tri_wave;
        break;
    case 2:
        img = &saw_wave;
        break;
    case 3:
        img = &rev_saw_wave;
        break;
    case 4:
        img = &sqr_wave;
        break;
    case 5:
        img = &s_r_wave;
        break;
    }
    return img;
}

lv_obj_t *SynthPage::createModEntry(lv_obj_t *parent, int8_t id)
{
    // delete "new modulation" button
    lv_obj_del(lv_obj_get_child(parent, -1));

    lv_obj_t *entry = lv_obj_create(parent);
    lv_obj_remove_style_all(entry);
    lv_obj_set_size(entry, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_style_pad_all(entry, 5, 0);
    lv_obj_clear_flag(entry, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(entry, LV_OBJ_FLAG_SCROLL_CHAIN_VER);
    // source dropdown
    lv_obj_t *dropdown = lv_dropdown_create(entry);
    lv_obj_set_style_text_font(dropdown, font_small, 0);
    lv_dropdown_set_options_static(dropdown, modSourceStr);
    lv_obj_set_size(dropdown, 105, 32);
    lv_obj_set_pos(dropdown, 0, 0);
    lv_obj_add_event_cb(dropdown, onModSourceChange, LV_EVENT_VALUE_CHANGED, this);
    lv_obj_t *list = lv_dropdown_get_list(dropdown);
    lv_obj_set_style_text_font(list, font_small, 0);
    // arrow symbol
    lv_obj_t *arrow = lv_label_create(entry);
    lv_label_set_text(arrow, LV_SYMBOL_PLAY);
    lv_obj_set_style_text_color(arrow, color_Grey, 0);
    lv_obj_set_pos(arrow, 108, 9);
    // target dropdown
    dropdown = lv_dropdown_create(entry);
    lv_obj_set_style_text_font(dropdown, font_small, 0);
    lv_dropdown_set_options_static(dropdown, modTargetStr);
    lv_obj_set_size(dropdown, 140, 32);
    lv_obj_set_pos(dropdown, 125, 0);
    lv_obj_add_event_cb(dropdown, onModTargetChange, LV_EVENT_VALUE_CHANGED, this);
    list = lv_dropdown_get_list(dropdown);
    lv_obj_set_style_text_font(list, font_small, 0);
    // delete button
    lv_obj_t *btn = Gui_CreateButton(entry, 32, 32, LV_SYMBOL_TRASH, false, 1);
    lv_obj_set_pos(btn, 270, 0);
    lv_obj_add_event_cb(btn, onDelModBtnPressed, LV_EVENT_CLICKED, this);
    // amount slider
    lv_obj_t *slider = lv_slider_create(entry);
    lv_obj_set_size(slider, 265, 10);
    lv_obj_set_pos(slider, 0, 40);
    lv_slider_set_mode(slider, LV_SLIDER_MODE_SYMMETRICAL);
    lv_slider_set_range(slider, -100, 100);
    lv_obj_set_style_bg_color(slider, color_Grey, 0);
    lv_obj_set_style_bg_color(slider, lv_color_white(), LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(slider, lv_color_white(), LV_PART_KNOB);
    lv_obj_set_style_pad_all(slider, 2, LV_PART_KNOB);
    lv_obj_add_event_cb(slider, onModAmountChange, LV_EVENT_VALUE_CHANGED, this);
    // id text
    lv_obj_t *label = lv_label_create(entry);
    lv_obj_set_style_text_font(label, font_small, 0);
    lv_obj_set_pos(label, 270, 35);
    lv_label_set_text_fmt(label, "%d", id);

    createNewModBtn(parent);

    return entry;
}

lv_obj_t *SynthPage::createNewModBtn(lv_obj_t *parent)
{
    // "new modulation" btn
    lv_obj_t *Btn = lv_btn_create(modMenuArea);
    lv_obj_set_size(Btn, 300, 35);
    lv_obj_set_style_bg_color(Btn, lv_color_black(), 0);
    lv_obj_set_style_border_color(Btn, color_Grey, 0);
    lv_obj_set_style_border_width(Btn, 2, 0);
    lv_obj_t *label = lv_label_create(Btn);
    lv_label_set_text(label, "+ New Modulation");
    lv_obj_center(label);

    lv_obj_add_event_cb(Btn, onNewModBtnPressed, LV_EVENT_CLICKED, this);

    return Btn;
}

// convert midi note number to note name
String SynthPage::noteNumToNoteName(uint8_t keyNum)
{
    String noteName;
    uint8_t octave = keyNum / 12 - 1;
    uint8_t note = keyNum % 12;
    switch (note)
    {
    case 0:
        noteName = "C";
        break;
    case 1:
        noteName = "C#";
        break;
    case 2:
        noteName = "D";
        break;
    case 3:
        noteName = "D#";
        break;
    case 4:
        noteName = "E";
        break;
    case 5:
        noteName = "F";
        break;
    case 6:
        noteName = "F#";
        break;
    case 7:
        noteName = "G";
        break;
    case 8:
        noteName = "G#";
        break;
    case 9:
        noteName = "A";
        break;
    case 10:
        noteName = "A#";
        break;
    case 11:
        noteName = "B";
        break;
    }
    noteName += octave;
    return noteName;
}