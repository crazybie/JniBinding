#if defined(PLATFORM_ANDROID)

#pragma once

#include <utility>
#include "JniHelper.h"
#include "JniDelayCall.h"


namespace JniHelper
{
    // return a functor which can automatically invoke the last callback param,
    // with the other params as the context of that callback.
    //
    // this is very handy when you want to pass a callback across the jni and  
    // automatically be invoked to your callback implementaion.
    //
    // ex:
    // give : foo(int a, int b, function<void(int,int)> callback)
    // do   : callback(a, b)

    template<typename T>
    struct CallbackInvoker;


    template<typename Ret, typename... Args>
    struct CallbackInvoker< Function<Ret(Args...)> >
    {
        typedef Function<Ret(Args...)> Callback;

        static Ret Call(Args... args, Callback& callback)
        { 
            if (callback) return callback(std::forward<Args>(args)...); 
        }

        static Function<Ret(Args..., Callback)>& Get()
        {
            static Function<Ret(Args..., Callback) > f = Bind(Call);
            return f;
        };
    };   




    class JniClass
    {
        const char*                         className;
        Vector<JNINativeMethod>*      nativeMethods;
        bool                                delayedInit;        

    public:        
        JniClass(const char* className_) : className(className_)    
        { 
            nativeMethods = NULL;
            delayedInit = false;
        }
        
        void DelayedInit()
        {
            if (!delayedInit) {
                delayedInit = true;                
                nativeMethods = new(Vector<JNINativeMethod>)();
            }
        }        
        
        void RegisterAll()
        {
            if (delayedInit) {
                Android::AndroidEnvironment::Singleton().RegisterNativeMethods(className, &(*nativeMethods)[0], nativeMethods->Size()); 
            }
        }

        void UnregisterAll()
        {
            if (delayedInit) {
                Android::AndroidEnvironment::Singleton().UnRegisterNativeMethods(className);                
                delete(nativeMethods);
            }
        }

        // auto generate the method id.

#define BindDelayedNativeVoidMethod(name, f)    BindDelayedNativeVoidMethod_<__LINE__>(name, f)
#define BindNativeMethod(name, f)               BindNativeMethod_<__LINE__>(name, f)
        

        //
        // delayed calls are thread safe: 
        //  calls will be dispatched in the thread which calls the DelayCallManager::DispatchDelayedCalls.
        // NOTE: delayed method can't return value to jni.
        //
        template<int kMethodId, typename... Args>
        void BindDelayedNativeVoidMethod_(const char* methodName, Function<void(Args...)>* userCallback)
        {
            typedef NativeMethodWrapper<kMethodId, void(Args...)> NativeMethod;

            assert(userCallback, "must provide a callback");

            DelayedInit();        

            JNINativeMethod sig;
            sig.name        = methodName;
            sig.signature   = NativeMethod::Get().GetSignature();
            sig.fnPtr       = (void*) NativeMethod::Get().GetSlotFunc(className, methodName, DelayCallManager::Get().GetHook(userCallback, className, methodName));

            nativeMethods->PushBack(sig); 
        } 


        // thread unsafe: your callback may be invoked in the java ui thread.
        template<int kMethodId, typename Ret, typename... Args>
        void BindNativeMethod_(const char* methodName, Function<Ret(Args...)>* userCallback)              
        {        
            typedef NativeMethodWrapper<kMethodId, Ret(Args...)> NativeMethod;

            assert(userCallback, "must provide a callback");

            DelayedInit();

            JNINativeMethod sig;
            sig.name        = methodName;
            sig.signature   = NativeMethod::Get().GetSignature();
            sig.fnPtr       = (void*) NativeMethod::Get().GetSlotFunc(className, methodName, userCallback);

            nativeMethods->PushBack(sig); 
        }    


        template<typename Ret, typename... Args>
        inline void BindStaticJavaMethod(const char* methodName, Function<Ret(Args...)>* fn)
        {
            typedef JavaMethodInvoker<Ret(Args...)> JavaMethod;

            assert(fn, "must provide a function to call the script implementation.");

            DelayedInit();

            SharedPtr<JavaMethod> javaMethod( new(JavaMethod)(className, methodName) );
            *fn = Bind(javaMethod, &JavaMethod::Call);
        }

    };
}


#endif