#include "Precompiled.h"
#if defined(PLATFORM_ANDROID)
#include "JniHelper.h"

// please refer to http://stackoverflow.com/questions/10408972/how-to-obtain-a-description-of-a-java-exception-in-c-when-using-jni

void JniHelper::ExceptionHelper::LoadMethods( JNIEnv* pEnv )
{
    jclass throwable_class = pEnv->FindClass("java/lang/Throwable");
    mid_throwable_getCause = pEnv->GetMethodID(throwable_class, "getCause", "()Ljava/lang/Throwable;");
    mid_throwable_getStackTrace = pEnv->GetMethodID(throwable_class, "getStackTrace", "()[Ljava/lang/StackTraceElement;");
    mid_throwable_toString = pEnv->GetMethodID(throwable_class, "toString", "()Ljava/lang/String;");

    jclass frame_class = pEnv->FindClass("java/lang/StackTraceElement");
    mid_frame_toString = pEnv->GetMethodID(frame_class, "toString", "()Ljava/lang/String;");
}

void JniHelper::ExceptionHelper::AppendExceptionTraceMessages( JNIEnv& a_jni_env, String& a_error_msg, jthrowable a_exception )
{
    // Get the array of StackTraceElements.
    jobjectArray frames = (jobjectArray) a_jni_env.CallObjectMethod(a_exception, mid_throwable_getStackTrace);
    jsize frames_length = a_jni_env.GetArrayLength(frames);

    // Add Throwable.toString() before descending
    // stack trace messages.
    if (0 != frames)
    {
        jstring msg_obj = (jstring) a_jni_env.CallObjectMethod(a_exception, mid_throwable_toString);
        const char* msg_str = a_jni_env.GetStringUTFChars(msg_obj, 0);

        // If this is not the top-of-the-trace then
        // this is a cause.
        if (!a_error_msg.Empty())
        {
            a_error_msg += "\nCaused by: ";
            a_error_msg += msg_str;
        }
        else
        {
            a_error_msg = msg_str;
        }

        a_jni_env.ReleaseStringUTFChars(msg_obj, msg_str);
        a_jni_env.DeleteLocalRef(msg_obj);
    }

    // Append stack trace messages if there are any.
    if (frames_length > 0)
    {
        jsize i = 0;
        for (i = 0; i < frames_length; i++)
        {
            // Get the string returned from the 'toString()'
            // method of the next frame and append it to
            // the error message.
            jobject frame = a_jni_env.GetObjectArrayElement(frames, i);
            jstring msg_obj = (jstring) a_jni_env.CallObjectMethod(frame, mid_frame_toString);

            const char* msg_str = a_jni_env.GetStringUTFChars(msg_obj, 0);

            a_error_msg += "\n    ";
            a_error_msg += msg_str;

            a_jni_env.ReleaseStringUTFChars(msg_obj, msg_str);
            a_jni_env.DeleteLocalRef(msg_obj);
            a_jni_env.DeleteLocalRef(frame);
        }
    }

    // If 'a_exception' has a cause then append the
    // stack trace messages from the cause.
    if (0 != frames)
    {
        jthrowable cause = (jthrowable) a_jni_env.CallObjectMethod(a_exception, mid_throwable_getCause);
        if (0 != cause)
        {
            AppendExceptionTraceMessages(a_jni_env, a_error_msg, cause);
        }
    }
}

JniHelper::String JniHelper::ExceptionHelper::GetExceptionString( JNIEnv* pEnv )
{
    String error_msg; // Could use ostringstream instead.

    LoadMethods(pEnv);

    // Get the exception and clear as no
    // JNI calls can be made while an exception exists.
    jthrowable exception = pEnv->ExceptionOccurred();
    pEnv->ExceptionClear();

    AppendExceptionTraceMessages(*pEnv, error_msg, exception);

    return error_msg;
}


const char* JniHelper::_GetClassName( JNIEnv* e, jclass cls )
{    
    // all methods will be looked up from the callee's class.
    // so cls.getName() =>
    // 1. get class C from `cls`
    // 2. get method M from C
    // 3. call M on `cls`

    jclass      classObj    = e->GetObjectClass(cls);
    jmethodID   getName     = e->GetMethodID(classObj, "getName", "()Ljava/lang/String;");
    jstring     jname       = (jstring) e->CallObjectMethod(cls, getName);    
    const char* cname       = e->GetStringUTFChars(jname, NULL);

    JniNativeGc::instance().add(jname, cname);
    return cname;
}


#endif
