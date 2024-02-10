#ifndef PARAM_ARC_H
#define PARAM_ARC_H

#include "lvgl.h"
#include "Hardware.h"
/* ParamArc GUI object
Wraps lvgl objects, target value and hardware binding.
*/

typedef void (*ParamArcCallback_t)(void *targetPointer, lv_obj_t *valueTextObj, int16_t value, int8_t encoderIndex);

class ParamArc
{
protected:
    // lvgl objects
    lv_obj_t *arc = NULL;
    lv_obj_t *valueText = NULL;
    lv_obj_t *titleText = NULL;
    lv_obj_t *unitText = NULL;
    // range offset to allow min value other than 0
    int16_t rangeOffset = 0;
    // target to control
    void *targetPointer = NULL;
    // hardware binding
    int8_t encoderIndex = -1;
    // generic callback function
    ParamArcCallback_t callback = NULL;
    // lvgl callback function
    static void lvglCallback(lv_event_t *event);
    // protected constructor for subclass
    ParamArc() {}
    // helper functions
    virtual void createArc(lv_obj_t *parent, uint8_t color, const char* title, const char* unit, bool padding);
    void setArcColor(uint8_t color);

public:
    // constructor
    ParamArc(lv_obj_t *parent, uint8_t color = 0, const char* title = NULL, const char* unit = NULL, bool padding = true);
    // destructor
    virtual ~ParamArc();
    // methods
    void setValue(int16_t value);
    void setRange(int16_t rangeMin, int16_t rangeMax);
    void setCallback(ParamArcCallback_t callback, void *targetPointer);
    void setSymmetric(bool symmetric);
    void bindEncoder(int8_t encoderIndex);

    // hardware binding callback function
    void encoderCallback(int16_t value);

    lv_obj_t* getLvglObject() { return arc; }
    lv_obj_t* getValueTextObject() { return valueText; }
    lv_obj_t* getTitleTextObject() { return titleText; }
    lv_obj_t* getUnitTextObject() { return unitText; }
    int8_t getEncoderIndex() { return encoderIndex; }

};

// A smaller version of the ParamArc
class ParamArcMini : public ParamArc
{
private:
    void createArc(lv_obj_t *parent, uint8_t color, const char* title, const char* unit, bool padding) override;
public:
    ParamArcMini(lv_obj_t *parent, uint8_t color = 0, const char* title = NULL, const char* unit = NULL, bool padding = true);
};

// shared variables
// binding table for ParamArc
extern ParamArc *paramArcBindingTable[4];
void encoderBindCallback(uint8_t encoderId, int value);
// TODO: add unbind function to remove encoderIndex of previously binded arc

#endif // PARAM_ARC_H