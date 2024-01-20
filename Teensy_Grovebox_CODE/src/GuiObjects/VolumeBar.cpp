#include "VolumeBar.h"
#include "Colors.h"
#include "Audio/AudioUtility.h"

void VolumeBar::createBar(lv_obj_t *parent, int16_t w, int16_t h, uint8_t color)
{
    bar = lv_bar_create(parent);
    lv_obj_set_size(bar, w, h);
    lv_bar_set_range(bar, -50, 0);
    lv_bar_set_value(bar, 0, LV_ANIM_ON);
    lv_obj_set_style_anim_time(bar, 100, 0);
    lv_obj_add_flag(bar, LV_OBJ_FLAG_OVERFLOW_VISIBLE);
    lv_obj_clear_flag(bar, LV_OBJ_FLAG_SCROLLABLE);
    // set color
    switch (color)
    {
    case 1:
        lv_obj_set_style_bg_color(bar, color_RedDark, LV_PART_MAIN);
        lv_obj_set_style_bg_color(bar, color_Red, LV_PART_INDICATOR);
        break;
    default:
        lv_obj_set_style_bg_color(bar, color_LightGreenDark, LV_PART_MAIN);
        lv_obj_set_style_bg_color(bar, color_LightGreen, LV_PART_INDICATOR);
        break;
    }
}

void VolumeBar::createLed(lv_obj_t *parent, int16_t w, int16_t h)
{
    led = lv_obj_create(parent);
    lv_obj_remove_style_all(led);
    lv_obj_set_size(led, w, h);
    lv_obj_set_style_radius(led, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_bg_color(led, color_RedDark, 0);
    lv_obj_set_style_bg_opa(led, LV_OPA_COVER, 0);
}

VolumeBar::VolumeBar(lv_obj_t *parent, int16_t w, int16_t h, bool vertical, uint8_t color)
{
    if (vertical)
    {
        createBar(parent, w, h-w*1.5, color);
        createLed(bar, w, w);
        lv_obj_align(led, LV_ALIGN_TOP_MID, w*1.5, 0);
    }
    else
    {
        createBar(parent, w-h*1.5, h, color);
        createLed(bar, h, h);
        lv_obj_align(led, LV_ALIGN_RIGHT_MID, h*1.5, 0);
    }
    resetVolume();
}

VolumeBar::~VolumeBar()
{
    lv_obj_del(bar);
}


/**
 * @brief Sets the volume of the VolumeBar. The volume is smoothed with running average. This method is supposed to be called periodically.
 * 
 * @param volume The volume value to set. (0.0f - 1.0f)
 */
void VolumeBar::setVolume(float volume)
{
    if (volume > 1.0f)
        volume = 1.0f;
    else if (volume < 0.0f)
        volume = 0.0f;

    float dB = gaintodB(volume);
    float resultVolume;
    // smooth volume
    if (smoothing > 0)
    {
        avgVolume = (avgVolume * smoothing + dB) / (smoothing + 1);
        resultVolume = avgVolume;
    }
    else
    {
        resultVolume = dB;
    }
    // set volume
    lv_bar_set_value(bar, resultVolume, useAnimation ? LV_ANIM_ON : LV_ANIM_OFF);

    // peak indicator
    if (dB >= -0.1)
    {
        peakHold = peakHoldTime;
    }
    if (peakHold > 0)
    {
        lv_obj_set_style_bg_color(led, color_Red, 0);
        peakHold--;
    }
    else
    {
        lv_obj_set_style_bg_color(led, color_RedDark, 0);
    }
}


/**
 * @brief Sets the smoothing value for the volume bar. The volume is smoothed with running average of the "smoothing" last values.
 * 
 * @param smoothing The smoothing factor to set.
 */
void VolumeBar::setSmoothing(uint16_t smoothing)
{
    this->smoothing = smoothing;
}

void VolumeBar::setAnimation(bool useAnimation)
{
    this->useAnimation = useAnimation;
}

void VolumeBar::setRange(int mindB, int maxdB)
{
    lv_bar_set_range(bar, mindB, maxdB);
}

void VolumeBar::setPeakHoldTime(uint16_t peakHoldTime)
{
    this->peakHoldTime = peakHoldTime;
}

void VolumeBar::resetVolume()
{
    lv_bar_set_value(bar, 0, LV_ANIM_OFF);
    lv_obj_set_style_bg_color(led, color_RedDark, 0);
}
