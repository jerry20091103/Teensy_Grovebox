#include "Pages/Pages.h"
#include "HomePage.h"
#include "MidiPage.h"
// #include "AudiooutPage.h"
// #include "OutMixerPopup.h"
// #include "AudioinPage.h"
// #include "WaveTablePage.h"
// #include "ReverbPopup.h"
// #include "Sf2SelectPopup.h"

PageManager_ &PageManager_::getInstance()
{
    static PageManager_ instance;
    return instance;
}

PageManager_ &PageManager = PageManager.getInstance();

int PageManager_::getCurPage()
{ 
    return curPage;
}

void PageManager_::Init()
{
    Gui_InitStyles();
    PageArr[PG_HOME] = new HomePage();
    PageArr[PG_MIDI] = new MidiPage();
    // PageArr[E_PG_AUDIOOUT] = new AudiooutPage();
    // PageArr[E_PG_POPUP_OUT_MIXER] = new OutMixerPopup();
    // PageArr[E_PG_AUDIOIN] = new AudioinPage();
    // PageArr[E_PG_HOME] = new HomePage();
    // PageArr[E_PG_WAVE] = new WaveTablePage();
    // PageArr[E_PG_POPUP_REVERB] = new ReverbPopup();
    // PageArr[E_PG_POPUP_SF2_SELECT] = new Sf2SelectPopup();

    Serial.println("Page constructor");

    // setup top layer (status bar)
    statusBar = lv_obj_create(lv_layer_top());
    lv_obj_set_size(statusBar, 320, 35);
    lv_obj_set_style_pad_all(statusBar, 1, 0);
    lv_obj_set_style_bg_color(statusBar, color_GreyDark, 0);
    // back button 
    backBtn = Gui_CreateButton(statusBar);
    lv_obj_set_height(backBtn, lv_pct(100));
    lv_obj_t *label = lv_label_create(backBtn);
    lv_label_set_text(label, LV_SYMBOL_LEFT);
    lv_obj_center(label);
    lv_obj_add_event_cb(backBtn, onBackBtnPressed, LV_EVENT_CLICKED, this);
    // title
    title = lv_label_create(statusBar);
    lv_label_set_text(title, "Tiltle");
    lv_obj_set_style_text_font(title, font_large, 0);
    lv_obj_align(title, LV_ALIGN_LEFT_MID, 45, 0);
    // battery logo
    battLabel = lv_label_create(statusBar);
    lv_label_set_text(battLabel, LV_SYMBOL_BATTERY_1);
    lv_obj_set_style_text_font(battLabel, font_large, 0);
    lv_obj_align(battLabel, LV_ALIGN_RIGHT_MID, -5, 0);

    for(auto i : PageArr)
    {
        if(i == nullptr)
            continue;
        i->init();
        Serial.println("Page init" + String(i->pageID));
    }
}

void PageManager_::switchPage(int pageID)
{
    lastPage = getCurPage();
    curPage = pageID;
    // set title text
    lv_label_set_text(title, PageArr[pageID]->pageName);
    PageArr[getCurPage()]->configurePage();
    lv_scr_load_anim(PageArr[pageID]->screen, LV_SCR_LOAD_ANIM_FADE_IN, 150, 0, false);
}

void PageManager_::showPowerPopup()
{
    lv_obj_t *msgbox = lv_msgbox_create(NULL, "Power Off", "Are you sure you want to power off?", powerBtns, false);
    lv_obj_center(msgbox);
    lv_obj_set_style_bg_color(msgbox, lv_color_black(), 0);
    lv_obj_add_event_cb(msgbox, onPowerBtnPressed, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_t *temp = lv_msgbox_get_title(msgbox);
    lv_obj_set_style_text_font(temp, font_large, 0);
    lv_label_set_recolor(temp, true);
    temp = lv_msgbox_get_btns(msgbox);
    lv_obj_set_style_text_font(temp, font_large, 0);
}

void PageManager_::onPowerBtnPressed(lv_event_t *e)
{
    lv_obj_t *msgbox = lv_event_get_current_target(e);
    if(strcmp(lv_msgbox_get_active_btn_text(msgbox), "Yes") == 0)
    {
        // power off!
        ioDeviceDigitalWriteS(multiIo, PWR_HOLD, LOW);
    }
    else
    {
        lv_msgbox_close(msgbox);
    }
}

void PageManager_::onBackBtnPressed(lv_event_t *e)
{
    if(PageManager.lastPage < 0)
        return;
    PageManager.switchPage(PageManager.lastPage);
}
