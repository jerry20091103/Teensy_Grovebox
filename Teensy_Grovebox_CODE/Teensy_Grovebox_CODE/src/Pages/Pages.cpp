#include "Pages/Pages.h"
#include "MidiPage.h"

PageManager_ &PageManager_::getInstance()
{
    static PageManager_ instance;
    return instance;
}

PageManager_ &PageManager = PageManager.getInstance();

int PageManager_::getCurPage()
{
    return gslc_GetPageCur(&m_gui);
}

void PageManager_::Init()
{
    PageArr[E_PG_MIDI] = new MidiPage();

    for(auto i : PageArr)
    {
        if(i == NULL)
            continue;
        i->init();
    }
}