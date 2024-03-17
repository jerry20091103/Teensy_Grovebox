#ifndef PAGE_H
#define PAGE_H

#include <sdios.h>
#include "Hardware.h"
#include "GuiUtility.h"
#include "Utility/SimpleStack.h"

#define MAX_PAGE_NAME 20

#define PEAK_HOLD_TIME 100

enum PageID : uint8_t{
    PG_HOME,
    PG_MIDI,
    PG_AUDIO,
    PG_WAVE,
    PG_SYNTH,
    PG_SAMPLEEDITOR,
    MAX_PAGE
};

// Pages class
// A virtual class for other pages to inherit from
class Pages
{
public:
    // Page button press callback function
    virtual void onBtnPressed(uint8_t pin) = 0;
    // Page button hold callback function, will appear after onBtnPressed callback
    virtual void onBtnHold(uint8_t pin) = 0;
    // Page button hold function
    virtual void onBtnReleased(uint8_t pin) = 0;
    // Page encoder callback function
    virtual void onEncTurned(uint8_t id, int value) = 0;
    // Page joystick callback function
    virtual void onJoyUpdate(int joy_x, int joy_y) = 0;
    // Page MIDI control change signal received callback
    virtual void onCCReceive(u_int8_t channel, u_int8_t control, u_int8_t value) = 0;
    // Configure a page before swithcing to it. Sets the audio system and other stuff This function should be called after HardwareSetup().
    virtual void configurePage() = 0;

    // this updates the page approximately every frame
    virtual void update() = 0;
    // Initialize a page at program startup
    virtual void init() = 0;
    // Load a page before switching to it
    virtual void load() = 0;
    // Unload a page before switching to another page
    virtual void unload() = 0;
    // Load all pages, including the subpages, to load user data to GUI elements. This function should be called after HardwareSetup().
    virtual void loadAll() {load(); unload();}

    // serialize the page data to output stream
    virtual void serialize(ofstream &stream) = 0;
    // deserialize the page data from input stream
    virtual void deserialize(ifstream &stream) = 0;

    uint8_t pageID;
    char pageName[MAX_PAGE_NAME];
    lv_obj_t *screen = nullptr;

protected:
};

// Forward declaration for SubPage class
class SubPage;

// PageWithSubPage class
// A virtual class for pages that have sub pages to inherit from
// This makes the page keeps a default implementation of the sub page's methods, which is used if the sub page does not override the methods
// The load() and unload() methods must be overriden by the sub page
// The init() method should not be overriden by the sub page
class PageWithSubPage : public Pages
{
    friend class SubPage;
protected:
    SubPage *curSubPage = nullptr;
public:
    // Page button press callback function
    void onBtnPressed(uint8_t pin) final;
    // Page button hold callback function, will appear after onBtnPressed callback
    void onBtnHold(uint8_t pin) final;
    // Page button hold function
    void onBtnReleased(uint8_t pin) final;
    // Page encoder callback function
    void onEncTurned(uint8_t id, int value) final;
    // Page joystick callback function
    void onJoyUpdate(int joy_x, int joy_y) final;
    // Page MIDI control change signal received callback
    void onCCReceive(u_int8_t channel, u_int8_t control, u_int8_t value) final;

    void update() final;
    void load() final;
    void unload() final;
    virtual void loadAll() = 0;

protected:
    // default implementation of the callback functions
    virtual void onBtnPressedDefault(uint8_t pin) = 0;
    virtual void onBtnHoldDefault(uint8_t pin) = 0;
    virtual void onBtnReleasedDefault(uint8_t pin) = 0;
    virtual void onEncTurnedDefault(uint8_t id, int value) = 0;
    virtual void onJoyUpdateDefault(int joy_x, int joy_y) = 0;
    virtual void onCCReceiveDefault(u_int8_t channel, u_int8_t control, u_int8_t value) = 0;
    virtual void updateDefault() = 0;

    // Additional methods for sub page management
    // switch to a sub page
    void switchSubPage(SubPage* subPage);
};

// SubPage class
// A virtual class for sub pages to inherit from (pages that are inside other pages)
// This ensures that the sub page has a pointer to access its parent page
// By default, the parentPage's default methods will be called when the sub page's methods are not overriden
// However, the load() and unload() methods must be overriden
class SubPage
{
protected:
    PageWithSubPage *parentPage = nullptr;
public:
    virtual void onBtnPressed(uint8_t pin) {parentPage->onBtnPressedDefault(pin);}
    virtual void onBtnHold(uint8_t pin) {parentPage->onBtnHoldDefault(pin);}
    virtual void onBtnReleased(uint8_t pin) {parentPage->onBtnReleasedDefault(pin);}
    virtual void onEncTurned(uint8_t id, int value) {parentPage->onEncTurnedDefault(id, value);}
    virtual void onJoyUpdate(int joy_x, int joy_y) {parentPage->onJoyUpdateDefault(joy_x, joy_y);}
    virtual void onCCReceive(u_int8_t channel, u_int8_t control, u_int8_t value) {parentPage->onCCReceiveDefault(channel, control, value);}
    virtual void update() {parentPage->updateDefault();}
    virtual void load() = 0;
    virtual void unload() = 0;
    virtual void serialize(ofstream &stream) = 0;
    virtual void deserialize(ifstream &stream) = 0;
    
    PageWithSubPage* getParentPage() {return parentPage;}
    SubPage(PageWithSubPage *parentPage) : parentPage(parentPage) {}
    // common functions for sub pages
    static lv_obj_t* createSubPageItemArea(lv_obj_t* parent);
};

// PagesManager class
// A Singleton class to store and manage all pages
class PageManager_
{
public:
    static PageManager_ &getInstance();
    Pages *PageArr[MAX_PAGE];
    
    // Get the current Page on screen.
    uint8_t getCurPage();
    // Get the previous Page.
    uint8_t getPrevPage();
    // Initial all pages at program start
    PROGMEM void Init();
    // Switch to a page, will auto hide popup when in a popup.
    void switchPage(uint8_t pageID, bool isGoBack = false);
    // Show power off popup
    void showPowerPopup();
    // Go back to previous page
    void goBack();
    // set user data to GUI elements in all pages. This function should be called after HardwareSetup().
    void loadAll();
    // load user data from SD cand to all pages.
    void loadDataFromSD();
    // save user data from all pages to SD card.
    void saveDataToSD();
    // a global pointer variable for parameter passing when switching pages
    void *pageParam;
    // show a message box with a title, a message, and a close button
    void showMessageBox(const char *title, const char *message);
private:
    bool inPopup = false;   // true if a popup is active
    int curPopupID;         // stores current acitve popup ID
    lv_obj_t *statusBar = nullptr;
    lv_obj_t *backBtn = nullptr;
    lv_obj_t *title = nullptr;
    lv_obj_t *battLabel = nullptr;
    int userDataVersion = 12;

    const char* powerBtns[3] = {"Yes", "No", NULL};

    // lvgl callback functions
    static void onPowerBtnPressed(lv_event_t *e);
    static void onBackBtnPressed(lv_event_t *e);

    // navigation stack
    SimpleStack<uint8_t, MAX_PAGE> navStack;

    PageManager_() {}
};

extern PageManager_ &PageManager;

// common data shared by all pages
DMAMEM extern int16_t samplerWaveformPointsMax[1000]; // todo: ugly?
DMAMEM extern int16_t samplerWaveformPointsMin[1000];

#endif