#include "HomePage.h"
#include "Hardware.h"
#include "GuiObjects/Colors.h"

void HomePage::onBtnPressed(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);
    uint32_t id = lv_btnmatrix_get_selected_btn(obj);
    switch (id)
    {
    case 0:
        PageManager.switchPage(PG_SYNTH);
        break;
    case 1:
        PageManager.switchPage(PG_WAVE);
        break;
    case 2:
        PageManager.switchPage(PG_MIDI);
        break;
    case 3:
        //PageManager.switchPage(PG_DRUM);
        break;
    case 4:
        PageManager.switchPage(PG_SAMPLEEDITOR);
        break;
    case 5:
        //PageManager.switchPage(PG_KEYBOARD);
        break;
    case 6:
        //PageManager.switchPage(PG_FX);
        break;
    case 7:
        //PageManager.switchPage(PG_SETTINGS);
        break;
    }
}

void HomePage::onBtnPressed(uint8_t pin)
{
    switch (pin)
    {
    case BTN_PWR:
        PageManager.switchPage(PG_AUDIO);
        break;
    }
}

void HomePage::onBtnHold(uint8_t pin)
{
    switch (pin)
    {
    case BTN_PWR:
        PageManager.showPowerPopup();
        break;
    }
}

void HomePage::onBtnReleased(uint8_t pin)
{

}

void HomePage::onEncTurned(uint8_t id, int value)
{

}

void HomePage::onJoyUpdate(int joy_x, int joy_y)
{

}

void HomePage::onCCReceive(u_int8_t channel, u_int8_t control, u_int8_t value)
{

}

void HomePage::configurePage()
{

}

void HomePage::update()
{

}

void HomePage::init()
{
    pageID = PG_HOME;
    strcpy(pageName, "Home");
    // create screen
    screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen, lv_color_black(), 0);
    // create lvgl objects
    btnMatrix = lv_btnmatrix_create(screen);
    lv_obj_set_style_bg_color(btnMatrix, lv_color_black(), 0);
    lv_obj_set_style_border_width(btnMatrix, 0, 0);
    lv_obj_set_style_text_font(btnMatrix, font_large, LV_PART_ITEMS);
    lv_obj_set_style_bg_color(btnMatrix, color_Grey, LV_PART_ITEMS);
    lv_obj_set_size(btnMatrix, 320, 205);
    lv_obj_set_y(btnMatrix, 35);
    lv_btnmatrix_set_map(btnMatrix, btnMap);
    lv_obj_add_event_cb(btnMatrix, onBtnPressed, LV_EVENT_VALUE_CHANGED, this);
}

void HomePage::load()
{
}

void HomePage::unload()
{
}

void HomePage::serialize(ofstream &stream)
{
    // nothing to save
}

void HomePage::deserialize(ifstream &stream)
{
    // nothing to load
}
