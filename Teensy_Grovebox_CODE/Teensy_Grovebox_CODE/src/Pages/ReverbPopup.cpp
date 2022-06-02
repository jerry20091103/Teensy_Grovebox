#include "ReverbPopup.h"
#include "Hardware.h"
#include "Controls.h"

void ReverbPopup::onBtnPressed(uint8_t pin)
{
    uint8_t keyNum = PinToKeyNum(pin);
    if (keyNum > 0)
    {
        PageManager.PageArr[PageManager.getCurPage(false)]->onBtnPressed(pin);
    }
    else
    {
    }
}

void ReverbPopup::onBtnHold(uint8_t pin)
{
}

void ReverbPopup::onBtnReleased(uint8_t pin)
{
    uint8_t keyNum = PinToKeyNum(pin);
    if (keyNum > 0)
    {
        PageManager.PageArr[PageManager.getCurPage(false)]->onBtnReleased(pin);
    }
    else
    {
    }
}

void ReverbPopup::onEncTurned(uint8_t id, int value)
{
    switch (id)
    {
    case 0:
        updateRoomSize(value);
        break;
    case 1:
        updateDamping(value);
        break;
    case 2:
        updateLpf(value);
        break;
    case 3:
        updateMix(value);
        break;
    }
}

void ReverbPopup::onJoyUpdate(int joy_x, int joy_y)
{
}

void ReverbPopup::onTouch(int ref)
{
    switch (ref)
    {
    case E_ELEM_REVERB_BACK_BTN:
        PageManager.hidePopup();
        break;
    }
}

void ReverbPopup::onCCReceive(u_int8_t channel, u_int8_t control, u_int8_t value)
{
}

void ReverbPopup::configurePage()
{
    mem = (FXFreeverb_Mem *)PageManager.pageParam;
    int value;
    // room size
    value = mem->roomSize * 100;
    gslc_ElemXRingGaugeSetVal(&m_gui, m_pElemReverbRSRing, value);
    gslc_ElemSetTxtStr(&m_gui, m_pElemReverbRSRing, String(value).c_str());
    enc0->changePrecision(100, value, false);
    // damping
    value = mem->damping * 100;
    gslc_ElemXRingGaugeSetVal(&m_gui, m_pElemReverbDampingRing, value);
    gslc_ElemSetTxtStr(&m_gui, m_pElemReverbDampingRing, String(value).c_str());
    enc1->changePrecision(100, value, false);
    // filter
    value = mem->lpf;
    gslc_ElemXRingGaugeSetVal(&m_gui, m_pElemReverbFilterRing, map(value, 1000, 20000, 0, 200));
    gslc_ElemSetTxtStr(&m_gui, m_pElemReverbFilterRing, String(value).c_str());
    enc2->changePrecision(200, map(value, 1000, 20000, 0, 200), false);
    // mix
    value = mem->mix * 100;
    gslc_ElemXRingGaugeSetVal(&m_gui, m_pElemReverbMixRing, value);
    gslc_ElemSetTxtStr(&m_gui, m_pElemReverbMixRing, String(value).c_str());
    enc3->changePrecision(100, value, false);
}

void ReverbPopup::update()
{
}

void ReverbPopup::draw()
{
}

void ReverbPopup::init()
{
    pageID = E_PG_POPUP_REVERB;
}

void ReverbPopup::updateRoomSize(uint8_t value)
{
    float newVal = value * 0.01f;
    AudioFX.reverb.setRoomSize(newVal);
    mem->roomSize = newVal;

    gslc_ElemXRingGaugeSetVal(&m_gui, m_pElemReverbRSRing, value);
    gslc_ElemSetTxtStr(&m_gui, m_pElemReverbRSRing, String(value).c_str());
}
void ReverbPopup::updateDamping(uint8_t value)
{
    float newVal = value * 0.01f;
    AudioFX.reverb.setDamping(newVal);
    mem->damping = newVal;

    gslc_ElemXRingGaugeSetVal(&m_gui, m_pElemReverbDampingRing, value);
    gslc_ElemSetTxtStr(&m_gui, m_pElemReverbDampingRing, String(value).c_str());
}
void ReverbPopup::updateLpf(uint8_t value)
{
    int newVal = map((int)value, 0, 200, 1000, 20000);
    AudioFX.reverb.setLpf(newVal);
    mem->lpf = newVal;

    gslc_ElemXRingGaugeSetVal(&m_gui, m_pElemReverbFilterRing, value);
    gslc_ElemSetTxtStr(&m_gui, m_pElemReverbFilterRing, String(newVal).c_str());
}
void ReverbPopup::updateMix(uint8_t value)
{
    float newVal = value * 0.01f;
    AudioFX.reverb.setMix(newVal);
    mem->mix = newVal;

    gslc_ElemXRingGaugeSetVal(&m_gui, m_pElemReverbMixRing, value);
    gslc_ElemSetTxtStr(&m_gui, m_pElemReverbMixRing, String(value).c_str());
}
