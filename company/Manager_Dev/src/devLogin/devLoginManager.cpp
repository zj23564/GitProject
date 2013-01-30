#include "../../include/devLogin/devLoginManager.h"


DEVMANAGER::DEVMANAGER()
{
    hk = NULL;
    Open_HK_Dev();
}

void DEVMANAGER::Open_HK_Dev()
{
    hk = new HK_DEVICE;
}

void DEVMANAGER::Open_HB_Dev()
{
    delete hk;
}
