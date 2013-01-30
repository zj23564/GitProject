#include "../../include/devLogin/HKSDK/hk_device.h"
#include <stdio.h>
#include "../../include/init/ObjectFactoy.h"

extern ObjectFactoy *m_fator;
HK_DEVICE::HK_DEVICE()
{
    Source_Init();
}

HK_DEVICE::~HK_DEVICE()
{
    NET_DVR_StopServer(serverHandle);
    NET_DVR_Cleanup();
}

void HK_DEVICE::Source_Init()
{
    if(false ==NET_DVR_Init()){
        switch(NET_DVR_GetLastError()){
            case 0:printf("HKDEV INIT DONE\n");break;
            case 41:printf("SDK资源分配错误\n");return;break;
            case 53:printf("获得本地PC的IP地址或物理地址失败\n");return;break;
            default:
                break;
        }
    }

   if(NET_DVR_SetRegisterCallBack(hkCallBack,(void*)this)){
        printf("CallBack Set Done\n");
   }
   else{
        return;
   }

  serverHandle = NET_DVR_StartServer(NULL,3100);
  if(serverHandle < 0 ){
        printf("NET_DVR_StartServer error\n");
        return;
  }

//login device
    NET_DVR_DEVICEINFO_V30* devinfo = new NET_DVR_DEVICEINFO_V30;
    int lUserID = NET_DVR_Login_V30("192.168.1.159",8000,"admin","12345",devinfo);
    int ret = NET_DVR_GetLastError();
    printf("error number is %d\n",ret);


    int iRet;
    //set params
    DWORD uiReturnLen;
    NET_DVR_COMPRESSIONCFG struParams = {0};
    iRet = NET_DVR_GetDVRConfig(lUserID, NET_DVR_GET_COMPRESSCFG, devinfo->byStartChan, &struParams, sizeof(NET_DVR_COMPRESSIONCFG), &uiReturnLen);
    if (!iRet)
    {
        printf("pyd---NET_DVR_GetDVRConfig NET_DVR_GET_COMPRESSCFG_V30 error.\n");
        NET_DVR_Logout_V30(lUserID);
        NET_DVR_Cleanup();
    }
    else{
        printf("NET_DVR_GetDVRConfig done\n");
    }

}

LONG CALLBACK hkCallBack(LONG userID,LPNET_DVR_REGCALLBACKPARAM   pRegCallbackParam,void* pUser)
{
    printf("HK device event\n");
}
