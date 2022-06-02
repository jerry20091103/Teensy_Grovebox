#include "Pages/Pages.h"
#include "MidiPage.h"
#include "PowerPopup.h"
#include "AudiooutPage.h"
#include "OutMixerPopup.h"
#include "AudioinPage.h"
#include "HomePage.h"
#include "WaveTablePage.h"
#include "ReverbPopup.h"

PageManager_ &PageManager_::getInstance()
{
    static PageManager_ instance;
    return instance;
}

PageManager_ &PageManager = PageManager.getInstance();

int PageManager_::getCurPage()
{
    if(inPopup)
        return curPopupID;
    else
        return gslc_GetPageCur(&m_gui);
}

void PageManager_::Init()
{
    PageArr[E_PG_MIDI] = new MidiPage();
    PageArr[E_PG_POPUP_POWER] = new PowerPopup();
    PageArr[E_PG_AUDIOOUT] = new AudiooutPage();
    PageArr[E_PG_POPUP_OUT_MIXER] = new OutMixerPopup();
    PageArr[E_PG_AUDIOIN] = new AudioinPage();
    PageArr[E_PG_HOME] = new HomePage();
    PageArr[E_PG_WAVE] = new WaveTablePage();
    PageArr[E_PG_POPUP_REVERB] = new ReverbPopup();

    Serial.println("Page constructor");

    for(auto i : PageArr)
    {
        if(i == nullptr)
            continue;
        i->init();
        Serial.println("Page init" + String(i->pageID));
    }
}

void PageManager_::switchPage(int pageID)
{
    if(inPopup)
        hidePopup();
    lastPage = getCurPage();
    gslc_SetPageCur(&m_gui, pageID);
    gslc_ElemSetTxtStr(&m_gui, m_pElemTxtTitle, PageArr[getCurPage()]->pageName);
    PageArr[getCurPage()]->configurePage();
}

void PageManager_::showPopup(int pageID)
{
    if(inPopup)
        return;

    gslc_PopupShow(&m_gui, pageID, true);
    curPopupID = pageID;
    inPopup = true;
    PageArr[getCurPage()]->configurePage();
}

void PageManager_::hidePopup()
{
    if(!inPopup)
        return;

    gslc_PopupHide(&m_gui);
    inPopup = false;
    PageArr[getCurPage()]->configurePage();
}

void Pages::toggleButton(gslc_tsElemRef *ref, bool state)
{
    if(state)
    {
        gslc_ElemSetCol(&m_gui, ref, GSLC_COL_WHITE, GSLC_COL_WHITE, GSLC_COL_GRAY);
        gslc_ElemSetTxtCol(&m_gui, ref, GSLC_COL_BLACK);
    }
    else
    {
        gslc_ElemSetCol(&m_gui, ref, GSLC_COL_WHITE, GSLC_COL_BLACK, GSLC_COL_GRAY);
        gslc_ElemSetTxtCol(&m_gui, ref, GSLC_COL_WHITE);
    }
}

void Pages::togglePeakBox(gslc_tsElemRef *ref, bool state)
{
    if(state)
        gslc_ElemSetCol(&m_gui, ref, GSLC_COL_GRAY, GSLC_COL_RED, GSLC_COL_RED);
    else
        gslc_ElemSetCol(&m_gui, ref, GSLC_COL_GRAY, GSLC_COL_BLACK, GSLC_COL_BLACK);
}