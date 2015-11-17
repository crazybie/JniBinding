#if defined(PLATFORM_ANDROID)

#ifndef JNIHELPER_H
#define JNIHELPER_H

#ifdef ENABLE_WARNING
#define DEBUG_JNI_HELPER 1
#else
#define DEBUG_JNI_HELPER 0
#endif


#include "JniNativeGc.h"
#include "JniTypes.h"
#include "System/Utilities/Function/Function.h"
#include "System/Utilities/Function/Bind.h"


#include "System/Utilities/_Android/AndroidEnvironment.h"
#include "System/Utilities/_Android/JNIEnvHandler.h"


namespace JniHelper
{
    using Function;
    using Bind;

    class ExceptionHelper
    {
        jmethodID mid_throwable_getCause;
        jmethodID mid_throwable_getStackTrace;
        jmethodID mid_throwable_toString;
        jmethodID mid_frame_toString;

        void LoadMethods(JNIEnv* pEnv);
        void AppendExceptionTraceMessages(JNIEnv& a_jni_env, String& a_error_msg, jthrowable a_exception);

    public:        

        String GetExceptionString(JNIEnv* pEnv);
    };


    const char* _GetClassName(JNIEnv* e, jclass cls);

}

// generating 

#define NUMARGS         0
#define TEMPARGS        
#define ARGS    
#define ARGTYPES
#define ARGNAMES
#define ARGFMT          
#define ARGFMT2 
#define ARGJNITYPES     
#define ARGTOSTR
#define ARGJNIVALUES    
#define ARGSJNITYPES2
#define ARGSNATIVEVALUE
#include __FILE__

#define NUMARGS         1
#define TEMPARGS        typename A0
#define ARGS            A0 a0
#define ARGTYPES        A0 
#define ARGNAMES        a0
#define ARGFMT          "%s"
#define ARGFMT2         "%s"
#define ARGTOSTR        JniType<A0>::toStr(a0).CStr()
#define ARGJNITYPES     JniType<A0>::jniTypeStr().CStr()
#define ARGJNIVALUES    JniType<A0>::toJni(e,a0)
#define ARGSJNITYPES2   typename JniType<A0>::JniT a0
#define ARGSNATIVEVALUE JniType<A0>::fromJni(e,a0)
#include __FILE__

#define NUMARGS         2
#define TEMPARGS        typename A0, typename A1
#define ARGS            A0 a0, A1 a1
#define ARGTYPES        A0, A1
#define ARGNAMES        a0, a1
#define ARGFMT          "%s%s"
#define ARGFMT2         "%s,%s"
#define ARGTOSTR        JniType<A0>::toStr(a0).CStr(), JniType<A1>::toStr(a1).CStr()
#define ARGJNITYPES     JniType<A0>::jniTypeStr().CStr(), JniType<A1>::jniTypeStr().CStr()
#define ARGJNIVALUES    JniType<A0>::toJni(e,a0), JniType<A1>::toJni(e,a1)
#define ARGSJNITYPES2   typename JniType<A0>::JniT a0, typename JniType<A1>::JniT a1
#define ARGSNATIVEVALUE JniType<A0>::fromJni(e,a0), JniType<A1>::fromJni(e,a1)
#include __FILE__

#define NUMARGS         3
#define TEMPARGS        typename A0, typename A1, typename A2
#define ARGS            A0 a0, A1 a1, A2 a2
#define ARGTYPES        A0, A1, A2
#define ARGNAMES        a0, a1, a2
#define ARGFMT          "%s%s%s"
#define ARGFMT2         "%s,%s,%s"
#define ARGTOSTR        JniType<A0>::toStr(a0).CStr(), JniType<A1>::toStr(a1).CStr(), JniType<A2>::toStr(a2).CStr()
#define ARGJNITYPES     JniType<A0>::jniTypeStr().CStr(), JniType<A1>::jniTypeStr().CStr(), JniType<A2>::jniTypeStr().CStr()
#define ARGJNIVALUES    JniType<A0>::toJni(e,a0), JniType<A1>::toJni(e,a1), JniType<A2>::toJni(e,a2)
#define ARGSJNITYPES2   typename JniType<A0>::JniT a0, typename JniType<A1>::JniT a1, typename JniType<A2>::JniT a2
#define ARGSNATIVEVALUE JniType<A0>::fromJni(e,a0), JniType<A1>::fromJni(e,a1), JniType<A2>::fromJni(e,a2)
#include __FILE__

#define NUMARGS         4
#define TEMPARGS        typename A0, typename A1, typename A2, typename A3
#define ARGS            A0 a0, A1 a1, A2 a2, A3 a3
#define ARGTYPES        A0, A1, A2, A3
#define ARGNAMES        a0, a1, a2, a3
#define ARGFMT          "%s%s%s%s"
#define ARGFMT2         "%s,%s,%s,%s"
#define ARGTOSTR        JniType<A0>::toStr(a0).CStr(), JniType<A1>::toStr(a1).CStr(), JniType<A2>::toStr(a2).CStr(), JniType<A3>::toStr(a3).CStr()
#define ARGJNITYPES     JniType<A0>::jniTypeStr().CStr(), JniType<A1>::jniTypeStr().CStr(), JniType<A2>::jniTypeStr().CStr(), JniType<A3>::jniTypeStr().CStr()
#define ARGJNIVALUES    JniType<A0>::toJni(e,a0), JniType<A1>::toJni(e,a1), JniType<A2>::toJni(e,a2), JniType<A3>::toJni(e,a3)
#define ARGSJNITYPES2   typename JniType<A0>::JniT a0, typename JniType<A1>::JniT a1, typename JniType<A2>::JniT a2, typename JniType<A3>::JniT a3
#define ARGSNATIVEVALUE JniType<A0>::fromJni(e,a0), JniType<A1>::fromJni(e,a1), JniType<A2>::fromJni(e,a2), JniType<A3>::fromJni(e,a3)
#include __FILE__

#define NUMARGS         5
#define TEMPARGS        typename A0, typename A1, typename A2, typename A3, typename A4
#define ARGS            A0 a0, A1 a1, A2 a2, A3 a3, A4 a4
#define ARGTYPES        A0, A1, A2, A3, A4
#define ARGNAMES        a0, a1, a2, a3, a4
#define ARGFMT          "%s%s%s%s%s"
#define ARGFMT2         "%s,%s,%s,%s,%s"
#define ARGTOSTR        JniType<A0>::toStr(a0).CStr(), JniType<A1>::toStr(a1).CStr(), JniType<A2>::toStr(a2).CStr(), JniType<A3>::toStr(a3).CStr(), JniType<A4>::toStr(a4).CStr()
#define ARGJNITYPES     JniType<A0>::jniTypeStr().CStr(), JniType<A1>::jniTypeStr().CStr(), JniType<A2>::jniTypeStr().CStr(), JniType<A3>::jniTypeStr().CStr(), JniType<A4>::jniTypeStr().CStr()
#define ARGJNIVALUES    JniType<A0>::toJni(e,a0), JniType<A1>::toJni(e,a1), JniType<A2>::toJni(e,a2), JniType<A3>::toJni(e,a3), JniType<A4>::toJni(e,a4)
#define ARGSJNITYPES2   typename JniType<A0>::JniT a0, typename JniType<A1>::JniT a1, typename JniType<A2>::JniT a2, typename JniType<A3>::JniT a3, typename JniType<A4>::JniT a4
#define ARGSNATIVEVALUE JniType<A0>::fromJni(e,a0), JniType<A1>::fromJni(e,a1), JniType<A2>::fromJni(e,a2), JniType<A3>::fromJni(e,a3), JniType<A4>::fromJni(e,a4)
#include __FILE__


#define NUMARGS         6
#define TEMPARGS        typename A0, typename A1, typename A2, typename A3, typename A4, typename A5
#define ARGS            A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5
#define ARGTYPES        A0, A1, A2, A3, A4, A5
#define ARGNAMES        a0, a1, a2, a3, a4, a5
#define ARGFMT          "%s%s%s%s%s%s"
#define ARGFMT2         "%s,%s,%s,%s,%s,%s"
#define ARGTOSTR        JniType<A0>::toStr(a0).CStr(), JniType<A1>::toStr(a1).CStr(), JniType<A2>::toStr(a2).CStr(), JniType<A3>::toStr(a3).CStr(), JniType<A4>::toStr(a4).CStr(), JniType<A5>::toStr(a5).CStr()
#define ARGJNITYPES     JniType<A0>::jniTypeStr().CStr(), JniType<A1>::jniTypeStr().CStr(), JniType<A2>::jniTypeStr().CStr(), JniType<A3>::jniTypeStr().CStr(), JniType<A4>::jniTypeStr().CStr(), JniType<A5>::jniTypeStr().CStr()
#define ARGJNIVALUES    JniType<A0>::toJni(e,a0), JniType<A1>::toJni(e,a1), JniType<A2>::toJni(e,a2), JniType<A3>::toJni(e,a3), JniType<A4>::toJni(e,a4), JniType<A5>::toJni(e,a5)
#define ARGSJNITYPES2   typename JniType<A0>::JniT a0, typename JniType<A1>::JniT a1, typename JniType<A2>::JniT a2, typename JniType<A3>::JniT a3, typename JniType<A4>::JniT a4, typename JniType<A5>::JniT a5
#define ARGSNATIVEVALUE JniType<A0>::fromJni(e,a0), JniType<A1>::fromJni(e,a1), JniType<A2>::fromJni(e,a2), JniType<A3>::fromJni(e,a3), JniType<A4>::fromJni(e,a4), JniType<A5>::fromJni(e,a5)
#include __FILE__

#define NUMARGS         7
#define TEMPARGS        typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6
#define ARGS            A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6
#define ARGTYPES        A0, A1, A2, A3, A4, A5, A6
#define ARGNAMES        a0, a1, a2, a3, a4, a5, a6
#define ARGFMT          "%s%s%s%s%s%s%s"
#define ARGFMT2         "%s,%s,%s,%s,%s,%s,%s"
#define ARGTOSTR        JniType<A0>::toStr(a0).CStr(), JniType<A1>::toStr(a1).CStr(), JniType<A2>::toStr(a2).CStr(), JniType<A3>::toStr(a3).CStr(), JniType<A4>::toStr(a4).CStr(), JniType<A5>::toStr(a5).CStr(), JniType<A6>::toStr(a6).CStr()
#define ARGJNITYPES     JniType<A0>::jniTypeStr().CStr(), JniType<A1>::jniTypeStr().CStr(), JniType<A2>::jniTypeStr().CStr(), JniType<A3>::jniTypeStr().CStr(), JniType<A4>::jniTypeStr().CStr(), JniType<A5>::jniTypeStr().CStr(), JniType<A6>::jniTypeStr().CStr()
#define ARGJNIVALUES    JniType<A0>::toJni(e,a0), JniType<A1>::toJni(e,a1), JniType<A2>::toJni(e,a2), JniType<A3>::toJni(e,a3), JniType<A4>::toJni(e,a4), JniType<A5>::toJni(e,a5), JniType<A6>::toJni(e,a6)
#define ARGSJNITYPES2   typename JniType<A0>::JniT a0, typename JniType<A1>::JniT a1, typename JniType<A2>::JniT a2, typename JniType<A3>::JniT a3, typename JniType<A4>::JniT a4, typename JniType<A5>::JniT a5, typename JniType<A6>::JniT a6
#define ARGSNATIVEVALUE JniType<A0>::fromJni(e,a0), JniType<A1>::fromJni(e,a1), JniType<A2>::fromJni(e,a2), JniType<A3>::fromJni(e,a3), JniType<A4>::fromJni(e,a4), JniType<A5>::fromJni(e,a5), JniType<A6>::fromJni(e,a6)
#include __FILE__



#pragma once


#else



#if NUMARGS > 0
#define ARGS_COMMA ,
#else
#define ARGS_COMMA
#endif

namespace JniHelper
{
    

    //========================================================================
    //
    // call java static function
    //
    //========================================================================

    //
    // we only support static java functions:
    // this can make java object lifetime management eaiser.
    //


    // version to call void function

#if NUMARGS > 0
    template<TEMPARGS>
#endif
    inline bool CallJavaStaticVoidMethod(const char* className, const char* methodName ARGS_COMMA ARGS)
    {
        Android::JNIEnvHandler    envHandler;
        JNIEnv*                         e = envHandler.Get();        
        JniNativeGc                     gc(e);

        
        Android::JNIClassAutoPtr targetClass = Android::AndroidEnvironment::Singleton().FindClass(className);
        assert(targetClass.Get() != NULL, "Can not find jclass %s", className);
        if (targetClass.Get() == NULL) return false;


        char signatureStr[1024];
        sprintf(signatureStr, "(" ARGFMT ")V" ARGS_COMMA ARGJNITYPES);


        jmethodID targetMethod = e->GetStaticMethodID(targetClass.Get(), methodName, signatureStr);
        assert(targetMethod != NULL, "Can not find jmethod %s", methodName);
        if (targetMethod == NULL) return false;


        e->CallStaticVoidMethod(targetClass.Get(), targetMethod ARGS_COMMA ARGJNIVALUES);        
        

#if DEBUG_JNI_HELPER        
        TRACE(LogModule_Default, "Jni: call script: %s.%s:(" ARGFMT2 ")", className, methodName ARGS_COMMA ARGTOSTR);
        if (e->ExceptionCheck())
        {
            ExceptionHelper excHelper;
            String msg = excHelper.GetExceptionString(e);
            TRACE(LogModule_Default, "JniException %s: %s \n", methodName, msg.CStr());
            return false;
        }
        return true;

#else        
        // always clear the pending exceptions.
        // see http://developer.android.com/training/articles/perf-jni.html, Exceptions section.
        if (e->ExceptionCheck())
        {
            e->ExceptionClear();
            return false;
        }
        return true;
#endif
    }


    
    // non void version

    template<typename Ret ARGS_COMMA TEMPARGS>
    inline bool CallJavaStaticMethod(const char* className, const char* methodName, Ret* ret ARGS_COMMA ARGS)
    {
        Android::JNIEnvHandler    envHandler;
        JNIEnv*                         e = envHandler.Get();        
        JniNativeGc                     gc(e);

        Android::JNIClassAutoPtr targetClass = Android::AndroidEnvironment::Singleton().FindClass(className);
        assert(targetClass.Get() != NULL, "Can not find jclass %s", className);
        if (targetClass.Get() == NULL) return false;


        char signatureStr[1024];
        sprintf(signatureStr, "(" ARGFMT ")%s" ARGS_COMMA ARGJNITYPES, JniType<Ret>::jniTypeStr().CStr());


        jmethodID targetMethod = e->GetStaticMethodID(targetClass.Get(), methodName, signatureStr);
        assert(targetMethod != NULL, "Can not find jmethod %s", methodName);
        if (targetMethod == NULL) return false;


        *ret = JniType<Ret>::fromJni(e, 
            JniType<Ret>::getStaticMethodByRet(e)(e, targetClass.Get(), targetMethod ARGS_COMMA ARGJNIVALUES)
            );

#if DEBUG_JNI_HELPER        
        TRACE(LogModule_Default, "Jni: call script: %s.%s:(" ARGFMT2 ")%s", className, methodName, ARGTOSTR ARGS_COMMA JniType<Ret>::toStr(*ret).CStr());
        if (e->ExceptionCheck())
        {
            ExceptionHelper excHelper;
            String msg = excHelper.GetExceptionString(e);
            TRACE(LogModule_Default, "JniException %s: %s \n", methodName, msg.CStr());
            return false;
        }
        return true;
#else
        // always clear the pending exceptions.
        // see http://developer.android.com/training/articles/perf-jni.html, Exceptions section.
        if (e->ExceptionCheck())
        {
            e->ExceptionClear();
            return false;
        }
        return true;
#endif
    }

    //========================================================================
    //
    // java function invoker
    //
    //========================================================================


    template<typename T>
    struct JavaMethodInvoker;


    // void version

    template<TEMPARGS>
    struct JavaMethodInvoker<void(ARGS)>
    {
        const char* className;
        const char* methodName;

        JavaMethodInvoker(const char* c, const char* m) : className(c), methodName(m) 
        { 
            ValidateMethod(); 
        }

        void Call(ARGS)
        {
            // TODO: save the error flag if failed.
#if NUMARGS
            CallJavaStaticVoidMethod<ARGTYPES>(className, methodName ARGS_COMMA ARGNAMES); 
#else
            CallJavaStaticVoidMethod(className, methodName ARGS_COMMA ARGNAMES); 
#endif
        }

        void ValidateMethod()
        {
#if DEBUG_JNI_HELPER
            Android::JNIEnvHandler    envHandler;
            JNIEnv*                         e = envHandler.Get();

            Android::JNIClassAutoPtr targetClass = Android::AndroidEnvironment::Singleton().FindClass(className);
            assert(targetClass.Get() != NULL, "Can not find jclass %s", className);
            if (targetClass.Get() == NULL) return;

            char signatureStr[1024];
            sprintf(signatureStr, "(" ARGFMT ")V" ARGS_COMMA ARGJNITYPES);

            jmethodID targetMethod = e->GetStaticMethodID(targetClass.Get(), methodName, signatureStr);
            assert(targetMethod != NULL, "Can not find jmethod %s", methodName);
            if (!targetMethod) return;
#endif
        }
    };



    // non void version

    template<typename Ret ARGS_COMMA TEMPARGS>
    struct JavaMethodInvoker<Ret(ARGS)>
    {
        const char* className;
        const char* methodName;

        JavaMethodInvoker(const char* c, const char* m) : className(c), methodName(m) 
        { 
            ValidateMethod(); 
        }

        Ret Call(ARGS)
        {
            // TODO: save the error flag if failed.
            Ret r; 
            CallJavaStaticMethod<Ret ARGS_COMMA ARGTYPES>(className, methodName, &r ARGS_COMMA ARGNAMES); 
            return r;
        }

        void ValidateMethod()
        {
#if DEBUG_JNI_HELPER
            Android::JNIEnvHandler    envHandler;
            JNIEnv*                         e = envHandler.Get();

            Android::JNIClassAutoPtr targetClass = Android::AndroidEnvironment::Singleton().FindClass(className);
            assert(targetClass.Get() != NULL, "Can not find jclass %s", className);
            if (targetClass.Get() == NULL) return;

            char signatureStr[1024];
            sprintf(signatureStr, "(" ARGFMT ")%s" ARGS_COMMA ARGJNITYPES, JniType<Ret>::jniTypeStr().CStr());

            jmethodID targetMethod = e->GetStaticMethodID(targetClass.Get(), methodName, signatureStr);
            assert(targetMethod != NULL, "Can not find jmethod %s", methodName);      
            if (!targetMethod) return;
#endif
        }
    };

    
    //========================================================================
    //
    // register native method to jni
    //
    //========================================================================


    // kMethodId is used to generate different static function for the methods with same signature.
    // it will be auto generated from __LINE__.
    template<int kMethodId, typename T>
    struct NativeMethodWrapper;



    // non void version

    template<int kMethodId, typename Ret ARGS_COMMA TEMPARGS>
    struct NativeMethodWrapper<kMethodId, Ret(ARGS)>
    {
        typedef Function<Ret(ARGS)>   NativeFunc;
        typedef typename JniType<Ret>::JniT JniRet;
        typedef JniRet JNICALL (*JniNativeFuncPtr)(JNIEnv* env, jclass ARGS_COMMA ARGSJNITYPES2) ;

        
        void*       f; 
        const char* methodName; 
        char        signatureStr[256];


        NativeMethodWrapper() : f(0),methodName(0) {}        
        static NativeMethodWrapper& Get() { static NativeMethodWrapper i; return i; }

        JniNativeFuncPtr GetSlotFunc(const char* className, const char* methodName, NativeFunc* f) 
        { 
            assert(!f && !methodName, "function[%s.%s] already bound before.", className, methodName);
            this->f = f;
            this->methodName = methodName;
            return JniNativeFunc; 
        }

        const char* GetSignature()
        {
            sprintf(signatureStr, "(" ARGFMT ")%s" ARGS_COMMA ARGJNITYPES, JniType<Ret>::jniTypeStr().CStr());
            return signatureStr;
        }

        static JniRet JniNativeFunc(JNIEnv* e, jclass cls ARGS_COMMA ARGSJNITYPES2)
        {
            JniNativeGc gc(e);            
            NativeMethodWrapper& methodWrapper = Get();
            NativeFunc* rawf = (NativeFunc*)methodWrapper.f;            

            if (!*rawf) 
            {
                WARNING(LogModule_Default, false, 
                    "Jni: calling unimplementation native: %s.%s:%s", _GetClassName(e, cls), methodWrapper.methodName, methodWrapper.GetSignature());
                return JniRet();
            }

            Ret r = (*rawf)(ARGSNATIVEVALUE);

#if DEBUG_JNI_HELPER
            char buffer[1024*2] = "";
            auto ArgsToStr = [](char* buffer, int buflen, const Ret& r ARGS_COMMA ARGS) {
                snprintf(buffer, buflen, "(" ARGFMT2 ")%s", ARGTOSTR ARGS_COMMA JniType<Ret>::toStr(r).CStr() );
            };
            ArgsToStr(buffer, sizeof(buffer), r ARGS_COMMA ARGSNATIVEVALUE);
            TRACE(LogModule_Default, "Jni: call native: %s.%s:%s", _GetClassName(e, cls), methodWrapper.methodName, buffer);
#endif
            return JniType<Ret>::toJni(e, r);
        }
    };



    // version for void function 

    template<int kMethodId ARGS_COMMA TEMPARGS>
    struct NativeMethodWrapper<kMethodId, void(ARGS)>
    {
        typedef Function<void(ARGS)> NativeFunc;
        typedef typename JniType<void>::JniT JNICALL (*JniNativeFuncPtr)(JNIEnv* env, jclass ARGS_COMMA ARGSJNITYPES2) ;

        
        void*       f; 
        const char* methodName; 
        char        signatureStr[128];


        NativeMethodWrapper() : f(0), methodName(0) {}
        static NativeMethodWrapper& Get() { static NativeMethodWrapper i; return i; }

        JniNativeFuncPtr GetSlotFunc(const char* className, const char* methodName, NativeFunc* f) 
        { 
            assert(!f && !methodName, "function[%s.%s] already bound before.", className, methodName);
            this->f = f;
            this->methodName = methodName;
            return JniNativeFunc; 
        }

        const char* GetSignature()
        {
            sprintf(signatureStr, "(" ARGFMT ")%s" ARGS_COMMA ARGJNITYPES, JniType<void>::jniTypeStr().CStr());
            return signatureStr;
        }

        static void JniNativeFunc(JNIEnv* e, jclass cls ARGS_COMMA ARGSJNITYPES2)
        {
            JniNativeGc gc(e);
            NativeMethodWrapper& methodWrapper = Get();
            NativeFunc* rawf = (NativeFunc*)methodWrapper.f;

            if (!*rawf) 
            {
                WARNING(LogModule_Default, false, 
                    "Jni: calling unimplementation native: %s.%s:%s", _GetClassName(e, cls), methodWrapper.methodName, methodWrapper.GetSignature());
                return;
            }

            (*rawf)(ARGSNATIVEVALUE);

#if DEBUG_JNI_HELPER
            char buffer[1024*2] = "";            
            auto ArgsToStr = [](char* buffer, int buflen ARGS_COMMA ARGS) {
                snprintf(buffer, sizeof(buffer), "(" ARGFMT2 ")" ARGS_COMMA ARGTOSTR );
            };
            ArgsToStr(buffer, sizeof(buffer) ARGS_COMMA ARGSNATIVEVALUE);
            TRACE(LogModule_Default, "Jni: call native: %s.%s:%s", _GetClassName(e, cls), methodWrapper.methodName, buffer);
#endif
        }
    };
}




#undef NUMARGS
#undef TEMPARGS
#undef ARGS
#undef ARGTOSTR
#undef ARGTYPES
#undef ARGNAMES
#undef ARGJNITYPES
#undef ARGFMT
#undef ARGFMT2
#undef ARGJNIVALUES
#undef ARGSJNITYPES2
#undef ARGSNATIVEVALUE


#undef ARGS_COMMA

#endif


#endif