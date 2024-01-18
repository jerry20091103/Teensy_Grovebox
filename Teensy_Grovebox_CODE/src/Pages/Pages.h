#ifndef PAGE_H
#define PAGE_H

#include "Hardware.h"
#include "GuiUtility.h"
#include "Utility/SimpleStack.h"
#include "Utility/GuiUserData.h"

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
    // Configure a page before swithcing to it. Sets encoders and prepare variables. This function should be called after HardwareSetup().
    virtual void configurePage() = 0;
    // set user data to GUI elements. This function should be called after HardwareSetup().
    // todo: also ensure that user data is set into audio objects?
    virtual void setUserData() = 0;

    // this updates the page approximately every frame
    virtual void update() = 0;
    // Initialize a page at program startup
    virtual void init() = 0;
    // Load a page before switching to it
    virtual void load() = 0;
    // Unload a page before switching to another page
    virtual void unload() = 0;

    int pageID;
    char pageName[MAX_PAGE_NAME];
    lv_obj_t *screen;

protected:
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
    void setUserData();
    // a global pointer variable for parameter passing when switching pages
    void *pageParam;
private:
    bool inPopup = false;   // true if a popup is active
    int curPopupID;         // stores current acitve popup ID
    lv_obj_t *statusBar;
    lv_obj_t *backBtn;
    lv_obj_t *title;
    lv_obj_t *battLabel;

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
extern int16_t samplerWaveformPointsMax[1000]; // todo: ugly?
extern int16_t samplerWaveformPointsMin[1000];

#endif