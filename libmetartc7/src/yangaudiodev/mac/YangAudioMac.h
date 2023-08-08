﻿#ifndef YANGAUDIOMAC_H
#define YANGAUDIOMAC_H
#include <yangutil/yangtype.h>
#include <yangutil/yangavctype.h>
#if defined(__APPLE__)
#include <AudioUnit/AudioUnit.h>
#include <CoreAudio/CoreAudio.h>

typedef struct{
    void* user;
    void (*on_audio)(uint8_t* data,uint32_t nb,void* user);
    int32_t (*getRenderData)(YangFrame* audioFrame,void* user);
}YangMacAudioCallback;



class YangAudioMac
{
public:
    YangAudioMac(bool isInput);
    ~YangAudioMac();
    int32_t init();
    int32_t start();
    int32_t stop();
    void setInputCallback(YangMacAudioCallback* callback);
    void on_audio(uint8_t* data,uint32_t nb);
    uint32_t getSample();
    uint32_t getChannel();
public:
    AudioUnit           m_unit;

    AudioDeviceID       m_deviceId;

    AudioBufferList*    m_bufferList;
    YangMacAudioCallback* m_callback;
    bool m_isInput;
    bool m_isStart;
    bool m_inited;
    YangFrame m_audioFrame;
private:
    uint32_t m_sample;
    uint32_t m_channel;

};
#endif
#endif // YANGAUDIOMAC_H
