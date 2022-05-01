#include "Pages/Pages.h"
#include "MidiPage.h"
#include "PowerPopup.h"

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

    for(auto i : PageArr)
    {
        if(i == NULL)
            continue;
        i->init();
    }
}

void PageManager_::switchPage(int pageID)
{
    if(inPopup)
        hidePopup();

    gslc_SetPageCur(&m_gui, pageID);
    gslc_ElemSetTxtStr(&m_gui, m_pElemTxtTitle, PageArr[getCurPage()]->pageName);
    PageArr[getCurPage()]->configureEncoders();
}

void PageManager_::showPopup(int pageID)
{
    if(inPopup)
        return;

    gslc_PopupShow(&m_gui, pageID, true);
    curPopupID = pageID;
    inPopup = true;
    PageArr[getCurPage()]->configureEncoders();
}

void PageManager_::hidePopup()
{
    if(!inPopup)
        return;

    gslc_PopupHide(&m_gui);
    inPopup = false;
    PageArr[getCurPage()]->configureEncoders();
}