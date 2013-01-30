#ifndef __PLAYSDKPU_H__
#define __PLAYSDKPU_H__

#ifdef __linux__

#ifdef __cplusplus
    extern "C"{
#endif

#define PLAYM4_API

// max channel numbers
#ifndef PLAYM4_MAX_SUPPORTS
#define PLAYM4_MAX_SUPPORTS 500
#endif

// buffer type
#define BUF_VIDEO_SRC       1
#define BUF_AUDIO_SRC       2
#define BUF_VIDEO_RENDER    3
#define BUF_AUDIO_RENDER    4

#define M4PErr_NoError              0x00000000
#define M4PErr_SDLInitFail          0x00000001
#define M4PErr_SDLSetVideoFail      0x00000002
#define M4PErr_CreateYUVOverlayFail 0x00000003
#define M4PErr_SDLAddTimerFail      0x00000004
#define M4PErr_CreateMutexFail      0x00000005
#define M4PErr_InvalidFuction       0x00010000
#define M4PErr_InvalidParam         0x00010001
#define M4PErr_M4SDKUnInit          0x00010002
#define M4PErr_OpenFileFail         0x00010003
#define M4PErr_OrderFail            0x00010004
#define M4PErr_AllocMemFail         0x00010005
#define M4PErr_ThreadCreateFail     0x00010006
#define M4PErr_BadFileFormat        0x00010007
#define M4PErr_InitVideoDecoderFail 0x00010008
#define M4PErr_InitAudioDecoderFail 0x00010009

#define M4PErr_DecoderVideoFail     0x0001000a
#define M4PErr_DecoderAudioFail     0x0001000b
#define M4PErr_AudioCreateFail      0x0001000c
#define M4PErr_SurportFileOnly      0x0001000d
#define M4PErr_SurportStreamOnly    0x0001000e
#define M4PErr_BadFileHead          0x0001000f
#define M4PErr_VersionIncorrect     0x00010010
#define M4PErr_BufOverflow          0x00010011
#define M4PErr_JpegCompressFail     0x00010012
#define M4PErr_OpenSDLFailed        0x00010013


#define M4PErr_UnknownFail          0x000fffff

// max display regions.
#define MAX_DISPLAY_WND     4

// display buffers
#define MAX_DIS_FRAMES      50
#define MIN_DIS_FRAMES      1

// locate by
#define BY_FRAMENUM         1
#define BY_FRAMETIME        2

#define SOURCE_BUF_MAX	(1024*50000)	//最大流缓冲
#define SOURCE_BUF_MIN	(1024*50)		//最小流缓冲


#define DECODE_NORMAIL      0
#define DECODE_KEY_FRAME    1
#define DECODE_NONE         2

// stream type
#define STREAM_REALTIME     0
#define STREAME_REALTIME    STREAM_REALTIME
#define STREAM_FILE         1
#define STREAME_FILE        STREAM_FILE

// frame type
#define T_AUDIO16           101
#define T_AUDIO8            100
#define T_UYVY              1
#define T_YV12              3
#define T_RGB32             7


// 系统封装格式
#define SYSTEM_NULL         0x0             // 没有系统层, 纯音频流或视频流
#define SYSTEM_PRIVT          0x1             // 私有文件层
#define SYSTEM_MPEG2_PS     0x2             // PS封装
#define SYSTEM_MPEG2_TS     0x3             // TS封装
#define SYSTEM_RTP          0x4             // rtp封装

// 视频编码类型
#define VIDEO_NULL          0x0             // 没有视频
#define VIDEO_H264          0x1             // 标准H.264和私有H.264都可以用这个定义
#define VIDEO_MPEG4         0x3             // 标准MPEG4

// 音频编码类型
#define AUDIO_NULL          0x0000          // 没有音频
#define AUDIO_ADPCM         0x1000          // ADPCM
#define AUDIO_MPEG          0x2000          // MPEG 系列音频, 解码器能自适应各种MPEG音频

// G系列音频
#define AUDIO_G711_U        0x7110
#define AUDIO_G711_A        0x7111
#define AUDIO_G722_1        0x7221
#define AUDIO_G723_1        0x7231
#define AUDIO_G726          0x7260
#define AUDIO_G729          0x7290
/*
#ifndef __INITINFO_defined
#define __INITINFO_defined
typedef struct __INITINFO
{
    int uWidth;                             // 整个窗口的宽度
    int uHeight;                            // 整个窗口的高度
}INITINFO;
#endif
*/
#ifndef __PLAYRECT_defined
#define __PLAYRECT_defined
typedef struct __PLAYRECT
{
    int x;                                  // 显示窗口在整个窗口中的左顶点X轴坐标
    int y;                                  // 显示窗口在整个窗口中的左顶点Y轴坐标
    int uWidth;                             // 显示窗口的宽度,显然必须小于INITINFO.uWidth
    int uHeight;                            // 显示窗口的高度,显然必须小于INITINFO.uHeight
}PLAYRECT;
#endif

#ifndef __HWND_defined
#define __HWND_defined
typedef PLAYRECT HWND;
#endif

#ifndef __HDC_defined
#define __HDC_defined
typedef struct __DC
{
    void*   surface;                        // SDL窗口的Surface
    HWND    hwnd;                           // HDC所在的窗口句柄
}DC;

typedef DC* HDC;
#endif


#ifndef __RECT_defined
#define __RECT_defined
typedef struct __RECT                       // 定义矩形框
{
    long left;                              // 矩形框的左边
    long top;                               // 矩形框的顶部
    long right;                             // 矩形框的右边
    long bottom;                            // 矩形框的底部
}RECT;
#endif

// SYSTEMTIME
typedef struct _SYSTEMTIME
{
    unsigned short wYear;
    unsigned short wMonth;
    unsigned short wDayOfWeek;
    unsigned short wDay;
    unsigned short wHour;
    unsigned short wMinute;
    unsigned short wSecond;
    unsigned short wMilliseconds;
}SYSTEMTIME;

// frame position
typedef struct
{
    long        nFilePos;
    long        nFrameNum;
    long        nFrameTime;
    long        nErrorFrameNum;
    SYSTEMTIME* pErrorTime;
    long        nErrorLostFrameNum;
    long        nErrorFrameSize;
}FRAME_POS, *PFRAME_POS;

// frame Info
typedef struct
{
    long        nWidth;
    long        nHeight;
    long        nStamp;
    long        nType;
    long        nFrameRate;
    unsigned int dwFrameNum;
}FRAME_INFO;

// frame type
typedef struct
{
    char*       pDataBuf;
    long        nSize;
    long        nFrameNum;
    int         bIsAudio;
    long        nReserved;
}FRAME_TYPE;

// watermark Info
typedef struct
{
    char*       pDataBuf;
    long        nSize;
    long        nFrameNum;
    int         bRsaRight;
    long        nReserved;
}WATERMARK_INFO;


//////////////////////////////////////////////////////////////////////////////
// PlayM4 API                                                               //
//////////////////////////////////////////////////////////////////////////////

PLAYM4_API int PlayM4_Init(INITINFO InitInfo, int using_SDL);   /*  Should be done First */
PLAYM4_API int PlayM4_DeInit(void);                             /*  Should be done at Last */
PLAYM4_API int PlayM4_SetDisplay(int width, int height);

PLAYM4_API int PlayM4_GetPort(int* nPort);
PLAYM4_API int PlayM4_FreePort(int nPort);

PLAYM4_API int PlayM4_OpenFile(int nPort, const char * sFileName);
PLAYM4_API int PlayM4_CloseFile(int nPort);
PLAYM4_API int PlayM4_Play(int nPort, PLAYRECT rect);
PLAYM4_API int PlayM4_Stop(int nPort);
PLAYM4_API int PlayM4_Pause(int nPort, int nPause);
PLAYM4_API int PlayM4_Fast(int nPort);
PLAYM4_API int PlayM4_Slow(int nPort);

PLAYM4_API int PlayM4_OneByOne(int nPort);

PLAYM4_API int   PlayM4_SetPlayPos(int nPort, float percent);
PLAYM4_API float PlayM4_GetPlayPos(int nPort);

PLAYM4_API int PlayM4_SetFileEndCallBack(int nPort, void (*funFileEndCallBack)(int nPort));
PLAYM4_API int PlayM4_SetFileEndCallBackEx(int nPort, void (*funFileEndCallBack)(int nPort, void* pUser), void* pUser);
PLAYM4_API int PlayM4_SetDecCallBack(int nPort,
		void (*funDecCallBack)(int nPort, char *pBuf, int size, FRAME_INFO* pFrameInfo, long reservd1, long reserved2));
PLAYM4_API int PlayM4_SetDecCallBackMend(int nPort,
		void (*funDecCallBack)(int nPort, char*pBuf, int size, FRAME_INFO* pFrameInfo, long nUser, long reserved2), long nUser);
PLAYM4_API int PlayM4_SetDisplayCallBack(int nPort,
		void (*funDisplayCallBack)(int nPort, char *pBuf, long size,long width, long height, long stamp, long type,long reserved));

PLAYM4_API int PlayM4_PlaySound(int nPort);
PLAYM4_API int PlayM4_StopSound();
PLAYM4_API int PlayM4_PlaySoundShare(int nPort);
PLAYM4_API int PlayM4_StopSoundShare(int nPort);
PLAYM4_API int PlayM4_BeginMixSound();
PLAYM4_API int PlayM4_OpenSound(int nPort);
PLAYM4_API int PlayM4_CloseSound(int nPort);
PLAYM4_API int PlayM4_StopMixSound();

PLAYM4_API int PlayM4_SetVolume(int nPort, int volume);
PLAYM4_API int PlayM4_GetVolume(int nPort);

PLAYM4_API int PlayM4_GetFileTime(int nPort);
PLAYM4_API int PlayM4_GetFileTotalFrames(int nPort);
PLAYM4_API int PlayM4_GetPlayedTime(int nPort);
PLAYM4_API int PlayM4_GetFileFrames(int nPort);
PLAYM4_API int PlayM4_GetPlayedFrames(int nPort);
PLAYM4_API int PlayM4_GetCurrentFrameNum(int nPort);
PLAYM4_API int PlayM4_GetCurrentFrameRate(int nPort);
PLAYM4_API int PlayM4_GetPictureSize(int nPort, int *pwidth, int *pheight);

PLAYM4_API int PlayM4_OpenStream(int nPort, char* pfileheadbuf, int size, int streambufsize);
PLAYM4_API int PlayM4_InputData(int nPort, char *pBuf, int nSize);
PLAYM4_API int PlayM4_CloseStream(int nPort);

PLAYM4_API int PlayM4_ConvertToBmpFile( char *pBuf, long size,long width, long height, long type,char *filename);
PLAYM4_API int PlayM4_GetFileHeadLength();

PLAYM4_API int PlayM4_GetLastErrorCode();
PLAYM4_API int PlayM4_GetSdkVersion();

PLAYM4_API int PlayM4_SetPlayRect(int nPort, PLAYRECT rect);

PLAYM4_API int PlayM4_GetSourceBufferRemain(int nPort);
PLAYM4_API int PlayM4_ResetSourceBuffer(int nPort);

PLAYM4_API int PlayM4_ThrowBFrameNum(int nPort, unsigned int num);
PLAYM4_API int PlayM4_SetPicQuality(int nPort, unsigned int hightquality);
PLAYM4_API int PlayM4_GetPicQuality(int nPort, unsigned int *hightquality);
PLAYM4_API int PlayM4_SetColor(int nPort, unsigned int nRegionNum, int nBrightness, int nContrast, int nSaturation, int nHue);


PLAYM4_API int PlayM4_SetFileRefCallBack(int nPort, void (*FileRefCallBack)(int nPort));
PLAYM4_API int PlayM4_OneByOneBack(int nPort);
PLAYM4_API int PlayM4_SetCurrentFrameNum(int nPort, unsigned int framenum);
PLAYM4_API int PlayM4_GetKeyFramePos(int nPort,unsigned int nValue, unsigned int nType, PFRAME_POS pframePos);
PLAYM4_API int PlayM4_GetNextKeyFramePos(int nPort,unsigned int nValue, unsigned int nType, PFRAME_POS pframePos);

PLAYM4_API int PlayM4_OpenStreamEx(int  nPort, char *pfileheadbuf, int size, int streambufsize);
PLAYM4_API int PlayM4_InputVideoData(int nPort, char *pBuf, int nSize);
PLAYM4_API int PlayM4_InputAudioData(int nPort, char *pBuf, int nSize);
PLAYM4_API int PlayM4_CloseStreamEx(int nPort);

PLAYM4_API int PlayM4_SetOpenStreamMode(int nPort, int mode);
PLAYM4_API int PlayM4_GetStreamMode(int nPort);

PLAYM4_API int PlayM4_SetIndexFile(int nPort,char* sIndexName);
PLAYM4_API int PlayM4_GetSpecialData(int nPort);
PLAYM4_API int PlayM4_InputFileHead(int nPort, char* pFileHeadBuf, int size);
PLAYM4_API int PlayM4_SetDecodeIOnly(int nPort, int enable);
PLAYM4_API int PlayM4_RegisterBCallBack(int nPort, void(*BThrownCallBack)(int nPort));
PLAYM4_API int PlayM4_GetAbsFrameNum(int nPort);
PLAYM4_API int PlayM4_SetDeflash(int nPort, int enable);
PLAYM4_API int PlayM4_CheckDiscontinuousFrameNum(int nPort, unsigned int nEnable);
PLAYM4_API int PlayM4_ResetBuffer(int nPort,unsigned int nBufType);

PLAYM4_API int PlayM4_SetJpegQuality(long nQuality);
PLAYM4_API int PlayM4_ConvertToJpegFile(char *pBuf, long nSize, long nWidth, long nHeight, long nType, char* sFileName);

// add new functions for PlayM4
PLAYM4_API int PlayM4_GetPlayedTimeEx(int nPort);
PLAYM4_API int PlayM4_SetPlayedTimeEx(int nPort, unsigned int nTime);

PLAYM4_API int PLayM4_ConvertToBmpFile(char* pBuf, long nSize, long nWidth, long nHeight, long nType, char* sFileName);
PLAYM4_API int PlayM4_GetBMP(int nPort,unsigned char* pBitmap,unsigned int nBufSize,unsigned int* pBmpSize);
PLAYM4_API int PlayM4_GetJPEG(int nPort,unsigned char* pJpeg,unsigned int nBufSize,unsigned int* pJpegSize);
PLAYM4_API int PlayM4_SetDecCallBackEx(int nPort,
           void (*funDecCallBack)(int nPort, char* pBuf, int nSize, FRAME_INFO * pFrameInfo, long nReserved1, long nReserved2),
           char* pDest, long nDestSize);

PLAYM4_API int PlayM4_SetPlayMode(int nPort,int bNormal);

PLAYM4_API int PlayM4_RefreshPlay(int nPort);

PLAYM4_API int PlayM4_GetPictureSize(int nPort,int *pWidth,int *pHeight);
PLAYM4_API int PlayM4_GetPictureQuality(int nPort,int *bHighQuality);

PLAYM4_API int PlayM4_ResetSourceBuffer(int nPort);
PLAYM4_API int PlayM4_SetSourceBufCallBack(int nPort,unsigned int nThreShold,
           void (*funSourceBufCallBack)(int nPort, unsigned int nBufSize, unsigned int dwUser, void* pResvered),
           unsigned int dwUser,void* pReserved);
PLAYM4_API int PlayM4_ResetSourceBufFlag(int nPort);
PLAYM4_API int PlayM4_SetDisplayBuf(int nPort,unsigned int nNum);
PLAYM4_API int PlayM4_SetDisplayFrames(int nPort, unsigned int nNum);
PLAYM4_API int PlayM4_GetDisplayBuf(int nPort);

PLAYM4_API int PlayM4_SyncToAudio(int nPort, int bSyncToAudio);

PLAYM4_API int PlayM4_RegisterDrawFun(int nPort, void (*funDrawCBFun)(int nPort, HDC hDc, long nUser), long nUser);

PLAYM4_API int PlayM4_SetDecCBStream(int nPort,unsigned int nStream);
PLAYM4_API int PlayM4_SetDisplayRegion(int nPort,unsigned int nRegionNum, RECT *pSrcRect, HWND hDestWnd, int bEnable);
PLAYM4_API int PlayM4_RefreshPlayEx(int nPort,unsigned int nRegionNum);

PLAYM4_API int PlayM4_GetRefValue(int nPort,unsigned char *pBuffer, unsigned int *pSize);
PLAYM4_API int PlayM4_SetRefValue(int nPort,unsigned char *pBuffer, unsigned int nSize);

PLAYM4_API int PlayM4_RigisterDrawFun(int nPort, void (*DrawFun)(long nPort, HDC hDc, long nUser), long nUser);
PLAYM4_API int PlayM4_RegisterDrawFunEx(int nPort, unsigned int nRegionNum,
        void (*funDrawCBFun)(int nPort, HDC hDc, long nUser),
        long nUser);

PLAYM4_API int PlayM4_ResetBuffer(int nPort,unsigned int nBufType);
PLAYM4_API int PlayM4_GetBufferValue(int nPort,unsigned int nBufType);

PLAYM4_API int PlayM4_AdjustWaveAudio(int nPort,int nCoefficient);
PLAYM4_API int PlayM4_SetVerifyCallBack(int nPort, unsigned int nBeginTime, unsigned int nEndTime,
        void (*funVerify)(int nPort, FRAME_POS* pFilePos, unsigned int bIsVideo, unsigned int nUser),
        unsigned int  nUser);

PLAYM4_API int PlayM4_SetEncTypeChangeCallBack(int nPort,void(*funEncChange)(int nPort, long nUser),long nUser);

PLAYM4_API int PlayM4_GetFileSpecialAttr(int nPort, unsigned int *pTimeStamp,unsigned int *pFileNum ,unsigned int *pReserved);

PLAYM4_API int PlayM4_SetCheckWatermarkCallBack(int nPort,
        void(*funCheckWatermark)(int nPort, WATERMARK_INFO* pWatermarkInfo, unsigned int nUser),
        unsigned int nUser);

PLAYM4_API int PlayM4_SetImageSharpen(int nPort,unsigned int nLevel);

PLAYM4_API int PlayM4_GetThrowBFrameCallBack(int nPort,
        void(*funThrowBFrame)(int nPort, unsigned int nBFrame, unsigned int nUser),
        unsigned int nUser);

PLAYM4_API int PlayM4_SetDecodeFrameType(int nPort, unsigned int nFrameType);

PLAYM4_API int PlayM4_SetSecretKey(int nPort, int lKeyType, char *pSecretKey, int lKeyLen);

#ifdef __cplusplus
    }
#endif

#endif

#endif


