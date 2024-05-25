#include <SdFat.h>
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
    // preset dropdown
    presetDropdown = lv_dropdown_create(statusBar);
    lv_obj_set_height(presetDropdown, lv_pct(100));
    lv_obj_set_width(presetDropdown, 125);
    lv_obj_align(presetDropdown, LV_ALIGN_RIGHT_MID, -80, 0);
    lv_obj_set_style_pad_all(presetDropdown, 5, 0);
    lv_obj_add_flag(presetDropdown, LV_OBJ_FLAG_OVERFLOW_VISIBLE);
    lv_obj_set_style_bg_color(presetDropdown, lv_color_black(), 0);
    lv_obj_set_style_border_color(presetDropdown, color_Grey, 0);
    lv_obj_set_style_text_font(presetDropdown, font_small, 0);
    lv_obj_t *list = lv_dropdown_get_list(presetDropdown);
    lv_obj_set_style_bg_color(list, lv_color_black(), 0);
    lv_obj_set_style_text_font(list, font_small, 0);
    lv_obj_add_flag(presetDropdown, LV_OBJ_FLAG_HIDDEN);
    // show new, save and delete button when preset dropdown is open
    lv_obj_add_event_cb(presetDropdown, onPresetDropdownOpen, LV_EVENT_READY, this);
    lv_obj_add_event_cb(presetDropdown, onPresetDropdownClose, LV_EVENT_CANCEL, this);
    // on preset change
    lv_obj_add_event_cb(presetDropdown, PageWithPreset::onPresetDropdownSelected, LV_EVENT_VALUE_CHANGED, nullptr);

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
    // new preset button
    newBtn = Gui_CreateButton(statusBar, -1, -1, LV_SYMBOL_PLUS);
    lv_obj_set_height(newBtn, lv_pct(100));
    lv_obj_align(newBtn, LV_ALIGN_RIGHT_MID, -40, 0);
    lv_obj_add_flag(newBtn, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_event_cb(newBtn, PageWithPreset::onPresetNewBtnPressed, LV_EVENT_CLICKED, nullptr);
    // save preset button
    saveBtn = Gui_CreateButton(statusBar, -1, -1, LV_SYMBOL_SAVE);
    lv_obj_set_height(saveBtn, lv_pct(100));
    lv_obj_align(saveBtn, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_obj_add_flag(saveBtn, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_event_cb(saveBtn, PageWithPreset::onPresetSaveBtnPressed, LV_EVENT_CLICKED, nullptr);
    // delete preset button
    deleteBtn = Gui_CreateButton(statusBar, -1, -1, LV_SYMBOL_TRASH, false, 1);
    lv_obj_set_height(deleteBtn, lv_pct(100));
    lv_obj_align(deleteBtn, LV_ALIGN_RIGHT_MID, -207, 0);
    lv_obj_add_flag(deleteBtn, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_event_cb(deleteBtn, PageWithPreset::onPresetDeleteBtnPressed, LV_EVENT_CLICKED, nullptr);

    // the backdrop to block the screen when entering preset name
    backdrop = lv_obj_create(lv_layer_top());
    lv_obj_remove_style_all(backdrop);
    lv_obj_set_size(backdrop, 320, 240);
    lv_obj_set_style_bg_color(backdrop, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(backdrop, LV_OPA_50, 0);
    lv_obj_add_flag(backdrop, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(backdrop, LV_OBJ_FLAG_CLICK_FOCUSABLE);

    // text area for preset name
    textArea = lv_textarea_create(backdrop);
    lv_obj_set_height(textArea, 33);
    lv_obj_set_width(textArea, 125);
    lv_obj_set_pos(textArea, 112, 3);
    lv_obj_set_style_pad_all(textArea, 5, 0);
    lv_obj_set_style_bg_color(textArea, lv_color_black(), 0);
    lv_obj_set_style_border_color(textArea, color_Grey, 0);
    lv_obj_set_style_text_font(textArea, font_small, 0);
    lv_obj_add_flag(textArea, LV_OBJ_FLAG_HIDDEN);
    lv_textarea_set_max_length(textArea, MAX_PRESET_NAME);
    lv_textarea_set_one_line(textArea, true);

    // on screen keyboard
    keyboard = lv_keyboard_create(lv_layer_top());
    lv_obj_set_y(keyboard, -35);
    lv_keyboard_set_popovers(keyboard, true);
    lv_obj_add_flag(keyboard, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_event_cb(keyboard, PageWithPreset::onKeyboardOkBtnPressed, LV_EVENT_READY, nullptr);

    for(auto i : PageArr)
    {
        if(i == nullptr)
            continue;
        i->init();
        Serial.println("Page init" + String(i->pageID));
    }

    if (!SD.begin(BUILTIN_SDCARD))
    {
        Serial.println("SD card failed, or not present");
        PageManager.showMessageBox("SD Card Error", "SD card failed, or not present");
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

void PageManager_::loadDataFromSD()
{
    if (!SD.mediaPresent())
    {
        Serial.println("SD card failed");
        PageManager.showMessageBox("SD Card Error", "SD card not detected. default settings will be used.");
    }
    else
    {
        for(auto i : PageArr)
        {
            if(i == nullptr)
                continue;
            i->loadDataFromSD();
        }
    }
}

void PageManager_::saveDataToSD()
{
    if (!SD.mediaPresent())
    {
        Serial.println("SD card failed");
        PageManager.showMessageBox("SD Card Error", "SD card not detected. Cannot save user data.");
    }
    else
    {
        for(auto i : PageArr)
        {
            if(i == nullptr)
                continue;
            i->saveDataToSD();
        }
    }
}

void PageManager_::showMessageBox(const char *title, const char *message, const char *btns[])
{
    // TODO: the "btns" parameter cause a crash when it's not nullptr
    bool addCloseBtn = false;
    if (btns == nullptr)
    {
        addCloseBtn = true;
    }
    
    lv_obj_t *msgbox = lv_msgbox_create(NULL, title, message, btns, addCloseBtn);
    lv_obj_center(msgbox);
    lv_obj_set_style_bg_color(msgbox, lv_color_black(), 0);
    lv_obj_t *label = lv_msgbox_get_title(msgbox);
    lv_obj_set_style_text_font(label, font_large, 0);
    label = lv_msgbox_get_text(msgbox);
    lv_label_set_recolor(label, true);
    lv_obj_t *btn = lv_msgbox_get_close_btn(msgbox);
    lv_obj_set_style_bg_color(btn, color_RedDark, 0);
    lv_obj_set_style_bg_color(btn, color_Red, LV_STATE_CHECKED);
}

void PageManager_::setShowKeyboardAndPresetName(bool enable, String text)
{
    if (enable)
    {
        if (text == "")
        {
            text = "Preset " + String(lv_dropdown_get_option_cnt(presetDropdown));
        }
        // show on screen keyboard and text area to enter the preset name
        lv_obj_clear_flag(backdrop, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(textArea, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(keyboard, LV_OBJ_FLAG_HIDDEN);
        lv_textarea_set_text(textArea, text.c_str());
        lv_textarea_set_cursor_pos(textArea, LV_TEXTAREA_CURSOR_LAST);
        lv_keyboard_set_textarea(keyboard, textArea);
        lv_event_send(textArea, LV_EVENT_FOCUSED, NULL);
        // make the rest of the screen unclickable
        lv_obj_add_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
    }
    else
    {
        // reverse the above
        lv_obj_add_flag(backdrop, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(textArea, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(keyboard, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
    }
}

void PageManager_::switchPage(uint8_t pageID, bool isGoBack)
{
    // check if we are saving a preset
    if (!lv_obj_has_flag(textArea, LV_OBJ_FLAG_HIDDEN))
    {
        // do nothing
        return;
    }
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
    // show preset dropdown if the page has preset
    if(PageArr[pageID]->hasPresets)
    {
        lv_obj_clear_flag(presetDropdown, LV_OBJ_FLAG_HIDDEN);
        // load the preset data
        PageArr[pageID]->loadDataFromSD();
    }
    else
    {
        lv_obj_add_flag(presetDropdown, LV_OBJ_FLAG_HIDDEN);
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

    // save user data to SD card
    // TODO: this is a temporary solution, should be moved to a better place
    PageManager.saveDataToSD();
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

void PageManager_::onPresetDropdownOpen(lv_event_t *e)
{
    PageManager_ *pm = (PageManager_ *)lv_event_get_user_data(e);
    // show new, save and delete button
    lv_obj_clear_flag(pm->newBtn, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(pm->saveBtn, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(pm->deleteBtn, LV_OBJ_FLAG_HIDDEN);
    // hide back button and battery logo
    lv_obj_add_flag(pm->backBtn, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(pm->battLabel, LV_OBJ_FLAG_HIDDEN);
}

void PageManager_::onPresetDropdownClose(lv_event_t *e)
{
    PageManager_ *pm = (PageManager_ *)lv_event_get_user_data(e);
    // hide new, save and delete button
    lv_obj_add_flag(pm->newBtn, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(pm->saveBtn, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(pm->deleteBtn, LV_OBJ_FLAG_HIDDEN);
    // show back button and battery logo
    lv_obj_clear_flag(pm->backBtn, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(pm->battLabel, LV_OBJ_FLAG_HIDDEN);
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

void Pages::loadDataFromSD()
{
    ifstream sdin((USER_DATA_FILE_PREFIX + String(pageName) + ".txt").c_str(), ios::in);
    if(sdin.is_open())
    {
        int versionNumber = 0;
        sdin >> versionNumber;
        if(versionNumber != USER_DATA_VERSION)
        {
            PageManager.showMessageBox("SD Card Error", ("User data version mismatch: " + String(pageName) + ".txt").c_str());
            sdin.close();
            return;
        }
        deserialize(sdin);
        sdin.close();
    }
    else
    {
        PageManager.showMessageBox("SD Card Error", ("SD file not found: " + String(pageName) + ".txt").c_str());
    }
}

void Pages::saveDataToSD()
{
    ofstream sdout((USER_DATA_FILE_PREFIX + String(pageName) + ".txt").c_str(), ios::out);
    if(sdout.is_open())
    {
        sdout << USER_DATA_VERSION << endl;
        serialize(sdout);
        sdout.close();
    }
    else
    {
        PageManager.showMessageBox("SD Card Error", ("Cannot create SD file: " + String(pageName) + ".txt").c_str());
    }
}

void PageWithSubPage::switchSubPage(SubPage *subPage)
{
    if(subPage == nullptr)
    {
        Serial.println("subPage is null");
        return;
    }
    // get current prest modified status
    bool presetModified = false;
    if (curSubPage->getParentPage()->hasPresets)
    {
        // determine the current page type
        switch (curSubPage->getParentPage()->pageID)
        {
            case PG_SYNTH:
                presetModified = ((SynthPage *)curSubPage->getParentPage())->getPresetModified();
                break;
        }
    }
    curSubPage->unload();
    subPage->load();
    curSubPage = subPage;
    // set the prest modified status back if the preset was unmodified before
    if (curSubPage->getParentPage()->hasPresets && !presetModified)
    {
        // determine the current page type
        switch (curSubPage->getParentPage()->pageID)
        {
            case PG_SYNTH:
                ((SynthPage *)curSubPage->getParentPage())->setPresetModified(false);
                break;
        }
    }
}

void PageWithPreset::loadDataFromSD()
{
    // check page folder
    if (!SD.exists((USER_DATA_FILE_PREFIX + String(pageName)).c_str()))
    {
        Serial.println("Page folder does not exist, creating a new one");
        SD.mkdir((USER_DATA_FILE_PREFIX + String(pageName)).c_str());
    }
    // read currnet preset number
    loadCurPresetNum();
    // read preset list
    File presetDir = SD.open((USER_DATA_FILE_PREFIX + String(pageName) + "/presets").c_str());
    if (!presetDir)
    {
        Serial.println("Preset directory does not exist, creating a new one");
        SD.mkdir((USER_DATA_FILE_PREFIX + String(pageName) + "/presets").c_str());
        // save the default preset
        createDefaultPreset();
    }
    std::list<String> files;
    while (true)
    {
        File entry = presetDir.openNextFile();
        if (!entry)
        {
            break;
        }
        // store them to string
        files.push_back(entry.name());
        entry.close();
    }
    presetDir.close();
    if (files.size() == 0)
    {
        Serial.println("No preset files found, creating default preset");
        createDefaultPreset();
        files.push_back(".default");
    }
    files.sort();
    // convert to string for the dropdown
    String PresetListStr = "";
    for (auto &f : files)
    {
        // don't add \n to the last item
        if (f == files.back())
            PresetListStr += f;
        else
            PresetListStr += (f + "\n");
    }
    lv_dropdown_set_options(PageManager.getPresetDropdown(), PresetListStr.c_str());
    // load the current preset
    auto it = files.begin();
    std::advance(it, curPreset);
    loadPreset(*it);
}

void PageWithPreset::saveDataToSD()
{
    // save current preset number
    saveCurPresetNum();
    
    // get current preset name
    char temp[MAX_PRESET_NAME + 1];
    lv_dropdown_get_selected_str(PageManager.getPresetDropdown(), temp, MAX_PRESET_NAME + 1);
    Serial.println("Saving preset: " + String(temp));
    // save the current preset data
    ofstream presetFile((USER_DATA_FILE_PREFIX + String(pageName) + "/presets" + "/" + String(temp)).c_str(), ios::out);
    if(presetFile.is_open())
    {
        presetFile << USER_DATA_VERSION << endl;
        serialize(presetFile);
        presetFile.close();
    }
    else
    {
        Serial.println("Cannot create current preset file");
    }
}

void PageWithPreset::newPreset(String presetName)
{
    // create a new preset file
    ofstream presetFile((USER_DATA_FILE_PREFIX + String(pageName) + "/presets" + "/" + presetName).c_str(), ios::out);
    if(presetFile.is_open())
    {
        presetFile << USER_DATA_VERSION << endl;
        serialize(presetFile);
        presetFile.close();
        Serial.println("New preset created: " + presetName);
    }
    else
    {
        Serial.println("Cannot create new preset file");
        return;
    }
    // reload the preset list
    loadDataFromSD();
    // find the new preset by name
    for(int i = 0; i < lv_dropdown_get_option_cnt(PageManager.getPresetDropdown()); i++)
    {
        char temp[MAX_PRESET_NAME + 1];
        lv_dropdown_set_selected(PageManager.getPresetDropdown(), i);
        lv_dropdown_get_selected_str(PageManager.getPresetDropdown(), temp, MAX_PRESET_NAME + 1);
        if(strcmp(temp, presetName.c_str()) == 0)
        {
            curPreset = i;
            break;
        }
    }
    // save the current preset number
    saveCurPresetNum();
    // load the new preset
    loadPreset(presetName);
}

void PageWithPreset::deletePreset(String presetName)
{
    Serial.println("Deleting preset: " + presetName);
    // cannot delete the first preset (default)
    if(curPreset == 0)
    {
        Serial.println("Cannot delete the default preset");
        return;
    }
    // delete the preset file
    if(SD.remove((USER_DATA_FILE_PREFIX + String(pageName) + "/presets" + "/" + presetName).c_str()))
    {
        Serial.println("Preset deleted");
    }
    else
    {
        Serial.println("Cannot delete preset file");
        return;
    }
    // set the current preset to the previous one
    (curPreset > 0) ? curPreset-- : curPreset = 0;
    saveCurPresetNum();
    // reload the preset list
    loadDataFromSD();
}

void PageWithPreset::loadPreset(String presetName)
{
    // TODO: check if the currnet preset needs to be saved (modified)

    // load the preset file
    Serial.println("Loading preset: " + presetName);
    ifstream presetFile((USER_DATA_FILE_PREFIX + String(pageName) + "/presets" + "/" + presetName).c_str(), ios::in);
    if(presetFile.is_open())
    {
        // check version number
        int versionNumber = 0;
        presetFile >> versionNumber;
        if(versionNumber != USER_DATA_VERSION)
        {
            PageManager.showMessageBox("SD Card Error", ("User data version mismatch: " + presetName).c_str());
            presetFile.close();
            return;
        }
        deserialize(presetFile);
        presetFile.close();
        // save the current preset number
        saveCurPresetNum();
        // set the dropdown to the current preset
        lv_dropdown_set_selected(PageManager.getPresetDropdown(), curPreset);
        // reload the page
        this->unload();
        this->loadAll(); // need to make sure all user data are applied to subpages
        this->load();
        setPresetModified(false);
    }
    else
    {
        Serial.println("Cannot open preset file");
    }
}

PageWithPreset::PageWithPreset()
{
    hasPresets = true;
    address = this;
}

void PageWithPreset::setPresetModified(bool modified)
{
    // if (curPreset == 0)
    //     modified = false;
    presetModified = modified;
    if (modified)
    {
        // make the preset dropdown border red
        lv_obj_set_style_border_color(PageManager.getPresetDropdown(), color_RedDark, 0);
    }
    else
    {
        // make the preset dropdown border grey
        lv_obj_set_style_border_color(PageManager.getPresetDropdown(), color_Grey, 0);
    }
}

void PageWithPreset::onPresetDropdownSelected(lv_event_t *e)
{
    // TODO: Here we use the stored address to essentially downcast to get the derived PageWithPreset class, this is ugly.
    void *pageaddr = PageManager.PageArr[PageManager.getCurPage()]->address;
    PageWithPreset *instance = (PageWithPreset *)pageaddr;
    
    lv_obj_t * dropdown = lv_event_get_target(e);
    int id = lv_dropdown_get_selected(dropdown);
    char temp[MAX_PRESET_NAME + 1];
    lv_dropdown_get_selected_str(dropdown, temp, MAX_PRESET_NAME + 1);
    instance->curPreset = id;
    instance->loadPreset(String(temp));
}

void PageWithPreset::onPresetNewBtnPressed(lv_event_t *e)
{
    // show the on screen keyboard and text area to enter the preset name
    PageManager.setShowKeyboardAndPresetName(true);
}

void PageWithPreset::onPresetSaveBtnPressed(lv_event_t *e)
{
    // TODO: Here we use the stored address to essentially downcast to get the derived PageWithPreset class, this is ugly.
    void *pageaddr = PageManager.PageArr[PageManager.getCurPage()]->address;
    PageWithPreset *instance = (PageWithPreset *)pageaddr;
    lv_obj_t *dropdown = PageManager.getPresetDropdown();
    // check if the current preset is the default one
    if (lv_dropdown_get_selected(dropdown) == 0)
    {
        PageManager.showMessageBox("Error", "Cannot overwrite the default preset. Press \"+\" to create a new one.");
        return;
    }
    // delete the current preset
    char temp[MAX_PRESET_NAME + 1];
    lv_dropdown_get_selected_str(dropdown, temp, MAX_PRESET_NAME + 1);
    // delete the preset file
    if(SD.remove((USER_DATA_FILE_PREFIX + String(instance->pageName) + "/presets" + "/" + temp).c_str()))
    {
        Serial.println("Preset deleted");
    }
    else
    {
        Serial.println("Cannot delete preset file");
        return;
    }
    // show the on screen keyboard and text area to enter the preset name
    PageManager.setShowKeyboardAndPresetName(true, temp);
}

void PageWithPreset::onPresetDeleteBtnPressed(lv_event_t *e)
{
    // TODO: Here we use the stored address to essentially downcast to get the derived PageWithPreset class, this is ugly.
    void *pageaddr = PageManager.PageArr[PageManager.getCurPage()]->address;
    PageWithPreset *instance = (PageWithPreset *)pageaddr;
    lv_obj_t *dropdown = PageManager.getPresetDropdown();
    char temp[MAX_PRESET_NAME + 1];
    lv_dropdown_get_selected_str(dropdown, temp, MAX_PRESET_NAME + 1);
    instance->deletePreset(temp);
    // reopen the dropdown
    lv_dropdown_open(dropdown);
    instance->setPresetModified(false);
}

void PageWithPreset::onKeyboardOkBtnPressed(lv_event_t *e)
{
    // TODO: Here we use the stored address to essentially downcast to get the derived PageWithPreset class, this is ugly.
    void *pageaddr = PageManager.PageArr[PageManager.getCurPage()]->address;
    PageWithPreset *instance = (PageWithPreset *)pageaddr;
    lv_obj_t *textArea = PageManager.getTextArea();
    // check if the text is empty
    String text = lv_textarea_get_text(textArea);
    if (text == "")
    {
        return;
    }
    // remove all invalid characters
    const char* invalidChars = "/\\:*?\"<>|";
    for (int i = 0; i < strlen(invalidChars); i++)
    {
        text.replace(invalidChars[i], '_');
    }
    // create a new preset
    instance->newPreset(text);
    // hide the on screen keyboard and text area
    PageManager.setShowKeyboardAndPresetName(false);
}

void PageWithPreset::loadCurPresetNum()
{
    ifstream curPresetFile((USER_DATA_FILE_PREFIX + String(pageName) + "/cur.txt").c_str(), ios::in);
    if(curPresetFile.is_open())
    {
        curPresetFile >> curPreset;
        curPresetFile.close();
    }
    else
    {
        curPreset = 0;
        Serial.println("Current preset file does not exist, creating a new one");
        saveCurPresetNum();
    }
}

void PageWithPreset::saveCurPresetNum()
{
    ofstream curPresetFile((USER_DATA_FILE_PREFIX + String(pageName) + "/cur.txt").c_str(), ios::out);
    if(curPresetFile.is_open())
    {
        curPresetFile << curPreset;
        curPresetFile.close();
    }
    else
    {
        Serial.println("Cannot create current preset file");
    }
}

void PageWithPreset::createDefaultPreset()
{
    // save the default preset
    ofstream presetFile((USER_DATA_FILE_PREFIX + String(pageName) + "/presets" + "/.default").c_str(), ios::out);
    if(presetFile.is_open())
    {
        presetFile << USER_DATA_VERSION << endl;
        serialize(presetFile);
        presetFile.close();
    }
    else
    {
        Serial.println("Cannot create default preset file");
    }
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