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

    // *OUTPUT TAB
    lv_obj_t *tab1 = lv_tabview_add_tab(tabView, "OUTPUT");
    // *analog out
    OutArc[MasterTracks::ANALOG_OUT] = Gui_CreateParamArc(tab1, 1, false);
    // title
    label = lv_label_create(OutArc[MasterTracks::ANALOG_OUT]);
    lv_label_set_text(label, "Analog");
    lv_obj_align(label, LV_ALIGN_TOP_LEFT, 80, 2);
    // volume text
    OutVolText[MasterTracks::ANALOG_OUT] = lv_label_create(OutArc[MasterTracks::ANALOG_OUT]);
    lv_label_set_text(OutVolText[MasterTracks::ANALOG_OUT], "-10");
    lv_obj_align(OutVolText[MasterTracks::ANALOG_OUT], LV_ALIGN_CENTER, 0, 0);
    // dB text
    label = lv_label_create(OutArc[MasterTracks::ANALOG_OUT]);
    lv_label_set_text(label, "dB");
    lv_obj_set_style_text_font(label, font_small, 0);
    lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, 0);
    // mixer button
    btn = Gui_CreateButton(OutArc[MasterTracks::ANALOG_OUT]);
    lv_obj_align(btn, LV_ALIGN_TOP_MID, 160, -5);
    label = lv_label_create(btn);
    lv_label_set_text(label, LV_SYMBOL_EDIT);
    lv_obj_set_style_text_font(label, font_small, 0);
    lv_obj_center(label);

    // volume meter and peak led
    OutBar[MasterTracks::ANALOG_OUT][0] = Gui_CreateVolumeMeter(OutArc[MasterTracks::ANALOG_OUT], 120, 10);
    lv_obj_align(OutBar[MasterTracks::ANALOG_OUT][0], LV_ALIGN_CENTER, 105, 5);

    OutPeakLed[MasterTracks::ANALOG_OUT][0] = Gui_CreatePeakLed(OutBar[MasterTracks::ANALOG_OUT][0], 10, 10);
    lv_obj_align(OutPeakLed[MasterTracks::ANALOG_OUT][0], LV_ALIGN_RIGHT_MID, 15, 0);

    OutBar[MasterTracks::ANALOG_OUT][1] = Gui_CreateVolumeMeter(OutArc[MasterTracks::ANALOG_OUT], 120, 10);
    lv_obj_align(OutBar[MasterTracks::ANALOG_OUT][1], LV_ALIGN_CENTER, 105, 20);

    OutPeakLed[MasterTracks::ANALOG_OUT][1] = Gui_CreatePeakLed(OutBar[MasterTracks::ANALOG_OUT][1], 10, 10);
    lv_obj_align(OutPeakLed[MasterTracks::ANALOG_OUT][1], LV_ALIGN_RIGHT_MID, 15, 0);

    // *usb out
    OutArc[MasterTracks::USB_OUT] = Gui_CreateParamArc(tab1, 2, false);
    lv_obj_set_y(OutArc[MasterTracks::USB_OUT], 80);
    // title
    label = lv_label_create(OutArc[MasterTracks::USB_OUT]);
    lv_label_set_text(label, "USB");
    lv_obj_align(label, LV_ALIGN_TOP_LEFT, 80, 2);
    // volume text
    OutVolText[MasterTracks::USB_OUT] = lv_label_create(OutArc[MasterTracks::USB_OUT]);
    lv_label_set_text(OutVolText[MasterTracks::USB_OUT], "-10");
    lv_obj_align(OutVolText[MasterTracks::USB_OUT], LV_ALIGN_CENTER, 0, 0);
    // dB text
    label = lv_label_create(OutArc[MasterTracks::USB_OUT]);
    lv_label_set_text(label, "dB");
    lv_obj_set_style_text_font(label, font_small, 0);
    lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, 0);
    // mixer button
    btn = Gui_CreateButton(OutArc[MasterTracks::USB_OUT]);
    lv_obj_align(btn, LV_ALIGN_TOP_MID, 160, -5);
    label = lv_label_create(btn);
    lv_label_set_text(label, LV_SYMBOL_EDIT);
    lv_obj_set_style_text_font(label, font_small, 0);
    lv_obj_center(label);

    // volume meter and peak led
    OutBar[MasterTracks::USB_OUT][0] = Gui_CreateVolumeMeter(OutArc[MasterTracks::USB_OUT], 120, 10);
    lv_obj_align(OutBar[MasterTracks::USB_OUT][0], LV_ALIGN_CENTER, 105, 5);

    OutPeakLed[MasterTracks::USB_OUT][0] = Gui_CreatePeakLed(OutBar[MasterTracks::USB_OUT][0], 10, 10);
    lv_obj_align(OutPeakLed[MasterTracks::USB_OUT][0], LV_ALIGN_RIGHT_MID, 15, 0);

    OutBar[MasterTracks::USB_OUT][1] = Gui_CreateVolumeMeter(OutArc[MasterTracks::USB_OUT], 120, 10);
    lv_obj_align(OutBar[MasterTracks::USB_OUT][1], LV_ALIGN_CENTER, 105, 20);

    OutPeakLed[MasterTracks::USB_OUT][1] = Gui_CreatePeakLed(OutBar[MasterTracks::USB_OUT][1], 10, 10);
    lv_obj_align(OutPeakLed[MasterTracks::USB_OUT][1], LV_ALIGN_RIGHT_MID, 15, 0);

    // *hp volume
    hpArc  = Gui_CreateParamArc(tab1, 3, false);
    lv_obj_align(hpArc, LV_ALIGN_TOP_RIGHT, 0, 20);
    // headphone logo
    hpModeLabel = lv_label_create(hpArc);
    lv_obj_set_style_text_font(hpModeLabel, font_extraSymbol, LV_PART_MAIN);
    lv_label_set_text(hpModeLabel, MY_HEADPHONE_SYMBOL);
    lv_obj_align(hpModeLabel, LV_ALIGN_TOP_MID, 0, -20);
    // volume text
    hpVolText = lv_label_create(hpArc);
    lv_label_set_text(hpVolText, "-10");
    lv_obj_center(hpVolText);
    // % text
    label = lv_label_create(hpArc);
    lv_obj_set_style_text_font(label, font_small, 0);
    lv_label_set_text(label, "%");
    lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, 0);
    
    // PFL button
    btn = Gui_CreateButton(hpArc, true);
    if(usePFL)
        lv_obj_add_state(btn, LV_STATE_CHECKED);
    // todo event callback
    lv_obj_set_width(btn, 60);
    lv_obj_align(btn, LV_ALIGN_BOTTOM_MID, 0, 40);
    label = lv_label_create(btn);
    lv_label_set_text(label, "PFL");
    lv_obj_center(label);

    // *INPUT TAB
    lv_obj_t *tab2 = lv_tabview_add_tab(tabView, "INPUT");
    label = lv_label_create(tab2);
    lv_label_set_text(label, "tab2");
    // *POST-DSP TAB
    lv_obj_t *tab3 = lv_tabview_add_tab(tabView, "POST-DSP");
    label = lv_label_create(tab3);
    lv_label_set_text(label, "tab3");
}
