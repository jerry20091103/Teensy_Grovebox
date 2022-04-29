#ifndef PAGE_H
#define PAGE_H

#include "GUIslice/GUIslice_GSLC.h"

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
    // Page GUI touch control callback function
    virtual void onTouch(int ref) = 0;
    // Page MIDI control change signal received callback
    virtual void onCCReceive(u_int8_t channel, u_int8_t control, u_int8_t value) = 0;
    // Sets encoder for a Page. Since precision and value is handled by library, need to update encoders when entering the page
    virtual void configureEncoders() = 0;

    // this handles custom graphics that are not built with GUIslice builder
    virtual void update() = 0;
    virtual void draw() = 0;
    // Initialize a page at program startup
    virtual void init() = 0;

    int pageID;
};

// PagesManager class
// A Singleton class to store and manage all pages
class PageManager_
{
public:
    static PageManager_ &getInstance();
    Pages *PageArr[MAX_PAGE];
    
    // Gets the current Page on screen. Returns the info from GUIslice library
    int getCurPage();
    // Initial all pages at program start
    void Init();
private:
    PageManager_() {}
};

extern PageManager_ &PageManager;

#endif