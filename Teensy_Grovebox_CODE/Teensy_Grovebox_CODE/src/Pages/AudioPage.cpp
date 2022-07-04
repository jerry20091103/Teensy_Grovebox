#include "AudioPage.h"
#include "Hardware.h"
#include "Audio/AudioIO.h"

void AudioPage::onBtnPressed(uint8_t pin)
{
    switch (pin)
    {
    case BTN_PWR:
        PageManager.goBack();
    default:
        break;
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
}

void AudioPage::onEncTurned(uint8_t id, int value)
{
}

void AudioPage::onJoyUpdate(int joy_x, int joy_y)
{
}

void AudioPage::onCCReceive(u_int8_t channel, u_int8_t control, u_int8_t value)
{
}

void AudioPage::configurePage()
{
}

void AudioPage::update()
{
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
    lv_obj_t *tabView = lv_tabview_create(screen, LV_DIR_TOP, 30);
    lv_obj_set_size(tabView, 320, 205);
    lv_obj_set_y(tabView, 35);
    lv_obj_set_style_bg_color(tabView, lv_color_black(), 0);

    lv_obj_t *label;
    lv_obj_t *btn;

    // *OUTPUT TAB------------------------------------------------------------------------------
    lv_obj_t *tab1 = lv_tabview_add_tab(tabView, "OUTPUT");
    lv_obj_clear_flag(tab1, LV_OBJ_FLAG_SCROLLABLE);
    // *analog out
    createTrackGui(tab1,
                   OutArc[MasterTracks::ANALOG_OUT],
                   OutVolText[MasterTracks::ANALOG_OUT],
                   OutBar[MasterTracks::ANALOG_OUT],
                   OutPeakLed[MasterTracks::ANALOG_OUT],
                   1, "Analog");
    // set arc position
    lv_obj_set_y(OutArc[MasterTracks::ANALOG_OUT], 0);
    // TODO: set value
    lv_label_set_text(OutVolText[MasterTracks::ANALOG_OUT], "-10");
    lv_bar_set_value(OutBar[MasterTracks::ANALOG_OUT][0], 10, LV_ANIM_ON);
    // mixer button
    btn = Gui_CreateButton(OutArc[MasterTracks::ANALOG_OUT]);
    lv_obj_align(btn, LV_ALIGN_TOP_MID, 160, -5);
    label = lv_label_create(btn);
    lv_label_set_text(label, LV_SYMBOL_EDIT);
    lv_obj_set_style_text_font(label, font_small, 0);
    lv_obj_center(label);
    
    // *usb out
    createTrackGui(tab1,
                   OutArc[MasterTracks::USB_OUT],
                   OutVolText[MasterTracks::USB_OUT],
                   OutBar[MasterTracks::USB_OUT],
                   OutPeakLed[MasterTracks::USB_OUT],
                   2, "USB");
    // set arc position
    lv_obj_set_y(OutArc[MasterTracks::USB_OUT], 80);
    // TODO: set value
    lv_label_set_text(OutVolText[MasterTracks::USB_OUT], "-10");
    lv_bar_set_value(OutBar[MasterTracks::USB_OUT][0], 10, LV_ANIM_ON);
    // mixer button
    btn = Gui_CreateButton(OutArc[MasterTracks::USB_OUT]);
    lv_obj_align(btn, LV_ALIGN_TOP_MID, 160, -5);
    label = lv_label_create(btn);
    lv_label_set_text(label, LV_SYMBOL_EDIT);
    lv_obj_set_style_text_font(label, font_small, 0);
    lv_obj_center(label);

    // *hp volume
    hpArc = Gui_CreateParamArc(tab1, 3, false);
    lv_obj_align(hpArc, LV_ALIGN_TOP_RIGHT, 0, 20);
    // headphone logo
    hpModeLabel = lv_label_create(hpArc);
    lv_obj_set_style_text_font(hpModeLabel, font_extraSymbol, LV_PART_MAIN);
    lv_label_set_text(hpModeLabel, MY_HEADPHONE_SYMBOL);
    lv_obj_align(hpModeLabel, LV_ALIGN_TOP_MID, 0, -20);
    // volume text
    hpVolText = lv_label_create(hpArc);
    lv_label_set_text(hpVolText, "50");
    lv_obj_center(hpVolText);
    // % text
    label = lv_label_create(hpArc);
    lv_obj_set_style_text_font(label, font_small, 0);
    lv_label_set_text(label, "%");
    lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, 0);

    // PFL button
    btn = Gui_CreateButton(hpArc, true);
    if (usePFL)
        lv_obj_add_state(btn, LV_STATE_CHECKED);
    // todo event callback
    lv_obj_set_width(btn, 60);
    lv_obj_align(btn, LV_ALIGN_BOTTOM_MID, 0, 40);
    label = lv_label_create(btn);
    lv_label_set_text(label, "PFL");
    lv_obj_center(label);

    // *INPUT TAB-------------------------------------------------------------------------------
    lv_obj_t *tab2 = lv_tabview_add_tab(tabView, "INPUT");
    lv_obj_clear_flag(tab2, LV_OBJ_FLAG_SCROLLABLE);
    // *analog in
    createTrackGui(tab2,
                   InArc[InputTracks::LINEMIC_IN],
                   InVolText[InputTracks::LINEMIC_IN],
                   InBar[InputTracks::LINEMIC_IN],
                   InPeakLed[InputTracks::LINEMIC_IN],
                   2, "Analog");
    // set arc position
    lv_obj_set_pos(InArc[InputTracks::LINEMIC_IN], 90, 0);
    // TODO: set value
    lv_label_set_text(InVolText[InputTracks::LINEMIC_IN], "-10");
    lv_bar_set_value(InBar[InputTracks::LINEMIC_IN][0], 10, LV_ANIM_ON);

    // *usb in
    createTrackGui(tab2,
                   InArc[InputTracks::USB_IN],
                   InVolText[InputTracks::USB_IN],
                   InBar[InputTracks::USB_IN],
                   InPeakLed[InputTracks::USB_IN],
                   3, "USB");
    // set arc position
    lv_obj_set_pos(InArc[InputTracks::USB_IN], 90, 80);
    // TODO: set value
    lv_label_set_text(InVolText[InputTracks::USB_IN], "-10");
    lv_bar_set_value(InBar[InputTracks::USB_IN][0], 10, LV_ANIM_ON);

    // *input gain
    gainArc = Gui_CreateParamArc(tab2, 1, false);
    lv_obj_set_y(gainArc, 15);
    // title
    label = lv_label_create(gainArc);
    lv_label_set_text(label, "Gain");
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, -20);
    // gain text
    gainText = lv_label_create(gainArc);
    lv_label_set_text(gainText, "0");
    lv_obj_align(gainText, LV_ALIGN_CENTER, 0, 0);
    // dB text
    label = lv_label_create(gainArc);
    lv_label_set_text(label, "dB");
    lv_obj_set_style_text_font(label, font_small, 0);
    lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, 0);

    // *input source
    // title
    label = lv_label_create(gainArc);
    lv_label_set_text(label, "Source");
    lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, 20);
    // line button
    lineBtn = Gui_CreateButton(tab2, true);
    lv_obj_set_pos(lineBtn, 0, 100);
    lv_obj_set_size(lineBtn, 60, 25);
    label = lv_label_create(lineBtn);
    lv_label_set_text(label, "LINE");
    lv_obj_center(label);
    // mic button
    micBtn = Gui_CreateButton(tab2, true);
    lv_obj_set_pos(micBtn, 0, 130);
    lv_obj_set_size(micBtn, 60, 25);
    label = lv_label_create(micBtn);
    lv_label_set_text(label, "MIC");
    lv_obj_center(label);

    // PFL button
    btn = Gui_CreateButton(tab2, true);
    lv_obj_set_pos(btn, 250, 0);
    lv_obj_set_height(btn, 25);
    label = lv_label_create(btn);
    lv_label_set_text(label, "PFL");
    lv_obj_center(label);

    // *POST-DSP TAB----------------------------------------------------------------------------
    lv_obj_t *tab3 = lv_tabview_add_tab(tabView, "POST-DSP");
    label = lv_label_create(tab3);
    lv_label_set_text(label, "TBD");

    // *OUTPUT MIXER WINDOW----------------------------------------------------------------
    lv_obj_t *mixerWindow = lv_win_create(tab1, 30);
    lv_obj_set_size(mixerWindow, 292, 160);
    lv_obj_t *windowContent = lv_win_get_content(mixerWindow);
    // back button
    btn = lv_win_add_btn(mixerWindow, LV_SYMBOL_LEFT, 30);
    // title
    lv_win_add_title(mixerWindow, " Analog Output Mixer");
    btn = lv_win_add_btn(mixerWindow, NULL, 60);
    label = lv_label_create(btn);
    lv_label_set_text(label, "PAN");
    lv_obj_center(label);

    // *analog
    createTrackGui(windowContent,
                   mixerArc[MixerTracks::I2S],
                   mixerVolText[MixerTracks::I2S],
                   mixerBar[MixerTracks::I2S],
                   mixerPeakLed[MixerTracks::I2S],
                   1, "Analog");
    // set arc position
    lv_obj_set_y(mixerArc[MixerTracks::I2S], 0);
    // TODO: set value
    lv_label_set_text(mixerVolText[MixerTracks::I2S], "-10");
    lv_bar_set_value(mixerBar[MixerTracks::I2S][0], 10, LV_ANIM_ON);

    // *usb
    createTrackGui(windowContent,
                   mixerArc[MixerTracks::USB],
                   mixerVolText[MixerTracks::USB],
                   mixerBar[MixerTracks::USB],
                   mixerPeakLed[MixerTracks::USB],
                   2, "USB");
    // set arc position
    lv_obj_set_y(mixerArc[MixerTracks::USB], 75);
    // TODO: set value
    lv_label_set_text(mixerVolText[MixerTracks::USB], "-10");
    lv_bar_set_value(mixerBar[MixerTracks::USB][0], 10, LV_ANIM_ON);

    // *instruments
    createTrackGui(windowContent,
                   mixerArc[MixerTracks::INSTRUMENTS],
                   mixerVolText[MixerTracks::INSTRUMENTS],
                   mixerBar[MixerTracks::INSTRUMENTS],
                   mixerPeakLed[MixerTracks::INSTRUMENTS],
                   3, "Instruments");
    // set arc position
    lv_obj_set_y(mixerArc[MixerTracks::INSTRUMENTS], 150);
    // TODO: set value
    lv_label_set_text(mixerVolText[MixerTracks::INSTRUMENTS], "-10");
    lv_bar_set_value(mixerBar[MixerTracks::INSTRUMENTS][0], 10, LV_ANIM_ON);

    // *Recorder
    createTrackGui(windowContent,
                   mixerArc[MixerTracks::RECORDER],
                   mixerVolText[MixerTracks::RECORDER],
                   mixerBar[MixerTracks::RECORDER],
                   mixerPeakLed[MixerTracks::RECORDER],
                   4, "Recorder");
    // set arc position
    lv_obj_set_y(mixerArc[MixerTracks::RECORDER], 225);
    // TODO: set value
    lv_label_set_text(mixerVolText[MixerTracks::RECORDER], "-10");
    lv_bar_set_value(mixerBar[MixerTracks::RECORDER][0], 10, LV_ANIM_ON);

    // hide mixer window
    //lv_obj_add_flag(mixerWindow, LV_OBJ_FLAG_HIDDEN);
}

void AudioPage::createTrackGui(lv_obj_t *&parent, lv_obj_t *&arcRef, lv_obj_t *&volTextRef, lv_obj_t **barArrRef, lv_obj_t **peakArrRef, uint8_t color, const char *name)
{
    lv_obj_t *label;
    // create arc
    arcRef = Gui_CreateParamArc(parent, color, false);
    // title
    label = lv_label_create(arcRef);
    lv_label_set_text(label, name);
    lv_obj_align(label, LV_ALIGN_TOP_LEFT, 80, 2);
    // volume text
    volTextRef = lv_label_create(arcRef);
    lv_obj_center(volTextRef);
    // dB text
    label = lv_label_create(arcRef);
    lv_label_set_text(label, "dB");
    lv_obj_set_style_text_font(label, font_small, 0);
    lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, 0);
    // volume meter and peak led
    for (uint8_t i = 0; i < 2; i++)
    {
        barArrRef[i] = Gui_CreateVolumeMeter(arcRef, 120, 10);
        lv_obj_align(barArrRef[i], LV_ALIGN_CENTER, 105, 5 + 15 * i);

        peakArrRef[i] = Gui_CreatePeakLed(barArrRef[i], 10, 10);
        lv_obj_align(peakArrRef[i], LV_ALIGN_RIGHT_MID, 15, 0);
    }
}