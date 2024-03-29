#include "Pages/Pages.h"
#include "HomePage.h"
#include "MidiPage.h"
#include "AudioPage.h"
#include "WaveTablePage.h"
#include "SynthPage.h"
#include "SampleEditorPage.h"
// #include "ReverbPopup.h"
#include "GuiObjects/Colors.h"
#include "Pages.h"

PageManager_ &PageManager_::getInstance()
{
    static PageManager_ instance;
    return instance;
}

PageManager_ &PageManager = PageManager.getInstance();

uint8_t PageManager_::getCurPage()
{ 
    return navStack.top();
}

uint8_t PageManager_::getPrevPage()
{
    uint8_t curPage = navStack.top();
    navStack.pop();
    uint8_t lastPage = navStack.top();
    navStack.push(curPage);
    return lastPage;
}

void PageManager_::Init()
{
    PageArr[PG_HOME] = new HomePage();
    PageArr[PG_MIDI] = new MidiPage();
    PageArr[PG_AUDIO] = new AudioPage();
    PageArr[PG_WAVE] = new WaveTablePage();
    PageArr[PG_SYNTH] = new SynthPage();
    PageArr[PG_SAMPLEEDITOR] = new SampleEditorPage();
    // PageArr[E_PG_POPUP_REVERB] = new ReverbPopup();
    // PageArr[E_PG_POPUP_SF2_SELECT] = new Sf2SelectPopup();

    Serial.println("Page constructor");

    // setup top layer (status bar)
    statusBar = lv_obj_create(lv_layer_top());
    lv_obj_set_size(statusBar, 320, 35);
    lv_obj_set_style_pad_all(statusBar, 1, 0);
    lv_obj_set_style_bg_color(statusBar, color_GreyDark, 0);
    // title
    title = lv_label_create(statusBar);
    lv_label_set_text(title, "Tiltle");
    lv_obj_set_style_text_font(title, font_large, 0);
    lv_obj_align(title, LV_ALIGN_LEFT_MID, 10, 0);
    // battery logo
    battLabel = lv_label_create(statusBar);
    lv_label_set_text(battLabel, LV_SYMBOL_BATTERY_1);
    lv_obj_set_style_text_font(battLabel, font_large, 0);
    lv_obj_align(battLabel, LV_ALIGN_RIGHT_MID, -50, 0);
    // back button 
    backBtn = Gui_CreateButton(statusBar, -1, -1, LV_SYMBOL_HOME);
    lv_obj_set_height(backBtn, lv_pct(100));
    lv_obj_align(backBtn, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_obj_add_event_cb(backBtn, onBackBtnPressed, LV_EVENT_CLICKED, this);

    for(auto i : PageArr)
    {
        if(i == nullptr)
            continue;
        i->init();
        Serial.println("Page init" + String(i->pageID));
    }
}

void PageManager_::loadAll()
{
    for(auto i : PageArr)
    {
        if(i == nullptr)
            continue;
        i->loadAll();
        Serial.println("Page loadAll(): " + String(i->pageID));
    }
}

void PageManager_::switchPage(uint8_t pageID, bool isGoBack)
{
    PageArr[getCurPage()]->unload();
    if (isGoBack)
        navStack.pop();
    else
        navStack.push(pageID);
    // set title text
    lv_label_set_text(title, PageArr[pageID]->pageName);
    PageArr[pageID]->load();
    PageArr[pageID]->configurePage();
    // change back button icon if previous page is home page
    lv_obj_t *label = lv_obj_get_child(backBtn, 0);
    if(getPrevPage() == PG_HOME)
    {
        lv_label_set_text(label, LV_SYMBOL_HOME);
    }
    else
    {
        lv_label_set_text(label, LV_SYMBOL_LEFT);
    }
    // load screen in lvgl
    lv_scr_load(PageArr[pageID]->screen);
}

void PageManager_::goBack()
{
    PageManager.onBackBtnPressed(NULL);
}

void PageManager_::showPowerPopup()
{
    lv_obj_t *msgbox = lv_msgbox_create(NULL, "Power Off", "Are you sure you want to power off ?\n#f44336 ALL CHANGES WILL BE LOST.#", powerBtns, false);
    lv_obj_center(msgbox);
    lv_obj_set_style_bg_color(msgbox, lv_color_black(), 0);
    lv_obj_add_event_cb(msgbox, onPowerBtnPressed, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_t *temp = lv_msgbox_get_title(msgbox);
    lv_obj_set_style_text_font(temp, font_large, 0);
    temp = lv_msgbox_get_text(msgbox);
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
    if(PageManager.navStack.size() > 1)
    {
        // go back to previous page
        PageManager.switchPage(PageManager.getPrevPage(), true);
    }
}

// common data shared by all pages
int16_t samplerWaveformPointsMax[1000]; // todo: ugly?
int16_t samplerWaveformPointsMin[1000];

void PageWithSubPage::onBtnPressed(uint8_t pin)
{
    curSubPage->onBtnPressed(pin);
}

void PageWithSubPage::onBtnHold(uint8_t pin)
{
    curSubPage->onBtnHold(pin);
}

void PageWithSubPage::onBtnReleased(uint8_t pin)
{
    curSubPage->onBtnReleased(pin);
}

void PageWithSubPage::onEncTurned(uint8_t id, int value)
{
    curSubPage->onEncTurned(id, value);
}

void PageWithSubPage::onJoyUpdate(int joy_x, int joy_y)
{
    curSubPage->onJoyUpdate(joy_x, joy_y);
}

void PageWithSubPage::onCCReceive(u_int8_t channel, u_int8_t control, u_int8_t value)
{
    curSubPage->onCCReceive(channel, control, value);
}

void PageWithSubPage::update()
{
    curSubPage->update();
}

void PageWithSubPage::load()
{
    curSubPage->load();
}

void PageWithSubPage::unload()
{
    curSubPage->unload();
}

void PageWithSubPage::switchSubPage(SubPage *subPage)
{
    if(subPage == nullptr)
    {
        Serial.println("subPage is null");
        return;
    }
    curSubPage->unload();
    subPage->load();
    curSubPage = subPage;
}

lv_obj_t *SubPage::createSubPageItemArea(lv_obj_t *parent)
{
    lv_obj_t *itemArea = lv_obj_create(parent);
    lv_obj_remove_style_all(itemArea);
    lv_obj_set_style_pad_all(itemArea, 5, 0);
    lv_obj_set_size(itemArea, 320, 178);
    lv_obj_clear_flag(itemArea, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_y(itemArea, 27);

    return itemArea;
}