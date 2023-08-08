﻿//
// Copyright (c) 2019-2022 yanggaofeng
//

#include <yangcapture/YangCaptureFactory.h>

#ifdef _WIN32
#include <yangaudiodev/win/YangWinAudioCapture.h>
#include <yangaudiodev/win/YangWinAudioApiDevice.h>
#include <yangaudiodev/win/YangAudioCaptureWindows.h>
#include "win/YangVideoCaptureWindows.h"
#else
#ifdef __ANDROID__
#include <yangaudiodev/android/YangAudioCaptureAndroid.h>
#include <yangcapture/android/YangVideoCaptureAndroid.h>
#else
#include <yangaudiodev/linux/YangAudioAecLinux.h>
#include <yangaudiodev/linux/YangAudioCaptureLinux.h>
#include <yangcapture/linux/YangVideoCaptureLinux.h>
#endif
#endif
#if defined(__APPLE__)
#include <yangaudiodev/mac/YangAudioCaptureMac.h>
#include <yangcapture/mac/YangVideoCaptureMac.h>
#endif
YangCaptureFactory::YangCaptureFactory() {


}

YangCaptureFactory::~YangCaptureFactory() {

}

YangAudioCapture* YangCaptureFactory::createAudioCapture(YangContext *pcontext){
#ifdef _WIN32
	return new YangWinAudioApiDevice(pcontext,0,true);
	// return new YangWinAudioCapture(pcontext);
#else

#ifdef __ANDROID__
	return NULL;
#else
    #if defined(__APPLE__)
        return NULL;
    #else
        return new YangAudioAecLinux(&pcontext->avinfo,&pcontext->synMgr);//new YangAlsaHandle(pcontext);//YangAudioCaptureImpl(pcontext);
    #endif
#endif
#endif

}
YangAudioCapture* YangCaptureFactory::createRecordAudioCapture(YangAVInfo *avinfo){
#ifdef _WIN32
	 return new YangAudioCaptureWindows(avinfo);
	 //return new YangWinAudioApiDevice(pcontext,1);
#else
#ifdef __ANDROID__
	 return new YangAudioCaptureAndroid(avinfo);
#else
    #if defined(__APPLE__)
        return new YangAudioCaptureMac(avinfo);
    #else
         return new YangAudioCaptureLinux(avinfo);//new YangAlsaHandle(pcontext);//YangAudioCaptureImpl(pcontext);
    #endif
#endif
#endif
}



YangMultiVideoCapture* YangCaptureFactory::createVideoCapture(YangVideoInfo *pcontext){
#ifdef _WIN32
	return new YangVideoCaptureWindows(pcontext);

#else
#ifdef __ANDROID__
	return NULL;
#else
    #if defined(__APPLE__)
        return NULL;
    #else
        return new YangVideoCaptureLinux(pcontext);
    #endif
#endif
#endif
}
YangMultiVideoCapture* YangCaptureFactory::createRecordVideoCapture(YangVideoInfo *pcontext){
#if defined(_WIN32)
	return new YangVideoCaptureWindows(pcontext);
#else
#ifdef __ANDROID__
	return NULL;
#else
    #if defined(__APPLE__)
        return new YangVideoCaptureMac(pcontext);
    #else
        return new YangVideoCaptureLinux(pcontext);
    #endif
#endif
#endif
}
YangMultiVideoCapture* YangCaptureFactory::createRecordVideoCaptureAndroid(YangVideoInfo *pcontext,void* pwindow){
#ifdef __ANDROID__
	return new YangVideoCaptureAndroid(pcontext,pwindow);
#else
	return NULL;
#endif
}

