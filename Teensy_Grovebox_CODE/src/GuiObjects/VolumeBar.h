#ifndef VOLUME_BAR_H
#define VOLUME_BAR_H

#include "lvgl.h"
/* Volume Bar GUI object
    Wraps the lvgl bar and led to form a volume bar with peak indicator.
*/

class VolumeBar
{
private:
    // lvgl objects
    lv_obj_t *bar = NULL;
    lv_obj_t *led = NULL;
    // other private methods
    void createBar(lv_obj_t *parent, int16_t w, int16_t h, uint8_t color);
    void createLed(lv_obj_t *parent, int16_t w, int16_t h);
    // other variables
    float avgVolume = 0.0f;
    uint16_t smoothing = 0;
    uint16_t peakHold = 0;
    uint16_t peakHoldTime = 100;
    bool useAnimation = true;
public:
    // constructor
    VolumeBar(lv_obj_t *parent, int16_t w, int16_t h, bool vertical = false, uint8_t color = 0);
    // destructor
    ~VolumeBar();
    // methods
    void setVolume(float volume);
    void setSmoothing(uint16_t smoothing);
    void setAnimation(bool useAnimation);
    void setRange(int mindB, int maxdB);
    void setPeakHoldTime(uint16_t peakHoldTime);
    void resetVolume();

    lv_obj_t* getBarObject() { return bar; }
    lv_obj_t* getLedObject() { return led; }
};


#endif // BUTTONS_H