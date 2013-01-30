#ifndef HK_DEVICE_H_INCLUDED
#define HK_DEVICE_H_INCLUDED

#include "HCNetSDK.h"


LONG CALLBACK hkCallBack(LONG userID,LPNET_DVR_REGCALLBACKPARAM    pRegCallbackParam,void* pUser);

class HK_DEVICE{

    public:
        HK_DEVICE();
        ~HK_DEVICE();
        void Source_Init();
    private:
        long serverHandle;
};


#endif // HK_DEVICE_H_INCLUDED
