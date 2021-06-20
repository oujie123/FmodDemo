#include <unistd.h>
#import "com_example_practicemethod_MainActivity.h"

using namespace FMOD;

#define TAG "Jack_Ou"
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_practicemethod_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_practicemethod_MainActivity_changeVoiceNative
        (JNIEnv *env, jobject thiz, jint mode, jstring path) {
    const char *content_ = "播放完毕";

    // 获取C能识别的path
    const char *path_ = env->GetStringUTFChars(path, NULL);

    // 音效引擎系统
    System *system = 0;

    // 声音
    Sound *sound = 0;

    // 声道，音轨
    Channel *channel = 0;

    // DSP
    DSP *dsp = 0;

    // 创建系统
    System_Create(&system);

    // 系统初始化
    // 参数1：最大声道数；
    // 参数2：初始化标记
    system->init(32, FMOD_INIT_NORMAL, 0);

    // 创建声音
    // 参数1：音频文件路基
    // 参数2：初始化音频标记
    // 参数3：额外参数
    // 参数4：声音
    system->createSound(path_, FMOD_DEFAULT, 0, &sound);

    // 播放
    // 参数1：声音
    // 参数2：通道分组
    // 参数3：是否暂停
    // 参数4：声道
    system->playSound(sound, 0, false, &channel);

    // 切换音效
    switch (mode) {
        case com_example_practicemethod_MainActivity_MODE_NORMAL:
            content_ = "原生 播放完毕";
            break;
        case com_example_practicemethod_MainActivity_MODE_GIRL:
            // 音调调高
            // 创建DPS
            system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
            // 设置pitch
            dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 2.0f);
            // 添加dsp
            // 参数1：通道编号
            channel->addDSP(0, dsp);
            content_ = "女声 播放完毕";
            LOGE("%s", content_);
            break;
        case com_example_practicemethod_MainActivity_MODE_UNCLE:
            system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
            dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 0.7f);
            channel->addDSP(0, dsp);
            content_ = "大叔 播放完毕";
            break;
        case com_example_practicemethod_MainActivity_MODE_HORROR:
            // 音量调低
            system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
            dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 0.7f);
            channel->addDSP(0, dsp); // 配置第一个音轨

            // 添加回声
            system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);
            dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 200); // 回音延时
            dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK, 10);  // 回音衰减度
            channel->addDSP(1, dsp);  // 配置第二个音轨

            // 添加颤抖
            system->createDSPByType(FMOD_DSP_TYPE_TREMOLO, &dsp);
            dsp->setParameterFloat(FMOD_DSP_TREMOLO_FREQUENCY, 20);  // 颤抖
            dsp->setParameterFloat(FMOD_DSP_TREMOLO_SKEW, 0.8f);  // 颤抖停顿
            channel->addDSP(2, dsp);
            content_ = "惊悚 播放完毕";
            break;
        case com_example_practicemethod_MainActivity_MODE_FUN:
            float freq;
            channel->getFrequency(&freq);

            channel->setFrequency(freq * 1.5f);
            content_ = "搞怪 播放完毕";
            break;
        case com_example_practicemethod_MainActivity_MODE_ETHEREAL:
            system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);
            dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 200); // 回音延时
            dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK, 0);  // 回音衰减度
            channel->addDSP(0, dsp);
            content_ = "空灵 播放完毕";
            break;
    }

    // 等待播放完毕
    bool isPlay = true;
    while (isPlay) {
        channel->isPlaying(&isPlay);  // 声道知道是否播放完毕
        LOGE("%s", content_);
        usleep(1000 * 1000);
    }

    // 回调结果
    jclass clazz = env->GetObjectClass(thiz);
    jmethodID endMethod = env->GetMethodID(clazz, "playEnd", "(Ljava/lang/String;)V");
    jstring value = env->NewStringUTF(content_);
    env->CallVoidMethod(thiz, endMethod, value);

    // 回收资源
    sound->release();
    system->close();
    system->release();
    env->ReleaseStringUTFChars(path, path_);
}
