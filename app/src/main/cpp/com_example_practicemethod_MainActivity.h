/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_example_practicemethod_MainActivity */

#include <fmod.hpp>  // 引入fmod头文件
#include <string>
#include <android/log.h>

#ifndef _Included_com_example_practicemethod_MainActivity
#define _Included_com_example_practicemethod_MainActivity
#ifdef __cplusplus
extern "C" {
#endif
#undef com_example_practicemethod_MainActivity_MODE_NORMAL
#define com_example_practicemethod_MainActivity_MODE_NORMAL 0L
#undef com_example_practicemethod_MainActivity_MODE_GIRL
#define com_example_practicemethod_MainActivity_MODE_GIRL 1L
#undef com_example_practicemethod_MainActivity_MODE_UNCLE
#define com_example_practicemethod_MainActivity_MODE_UNCLE 2L
#undef com_example_practicemethod_MainActivity_MODE_HORROR
#define com_example_practicemethod_MainActivity_MODE_HORROR 3L
#undef com_example_practicemethod_MainActivity_MODE_FUN
#define com_example_practicemethod_MainActivity_MODE_FUN 4L
#undef com_example_practicemethod_MainActivity_MODE_ETHEREAL
#define com_example_practicemethod_MainActivity_MODE_ETHEREAL 5L
/*
 * Class:     com_example_practicemethod_MainActivity
 * Method:    stringFromJNI
 * Signature: ()Ljava/lang/String;
 */
extern "C" JNIEXPORT jstring JNICALL Java_com_example_practicemethod_MainActivity_stringFromJNI
  (JNIEnv *, jobject);

/*
 * Class:     com_example_practicemethod_MainActivity
 * Method:    changeVoiceNative
 * Signature: (ILjava/lang/String;)V
 */
extern "C" JNIEXPORT void JNICALL Java_com_example_practicemethod_MainActivity_changeVoiceNative
  (JNIEnv *, jobject, jint, jstring);

#ifdef __cplusplus
}
#endif
#endif