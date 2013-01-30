#ifndef DEVLOGINMANAGER_H_INCLUDED
#define DEVLOGINMANAGER_H_INCLUDED

#include "HKSDK/hk_device.h"

class DEVMANAGER{

    public:
        DEVMANAGER();
        ~DEVMANAGER(){}
        void Open_HK_Dev();
        void Open_HB_Dev();

    private:

        HK_DEVICE* hk;



};



#endif // DEVLOGINMANAGER_H_INCLUDED
