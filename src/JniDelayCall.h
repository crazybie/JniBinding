#if defined(PLATFORM_ANDROID)

#pragma once
    
#include "JniHelper.h"
#include "thread/adaptivelock.h"
#include <tuple>


namespace JniHelper
{


    namespace Private
    {
        // based on http://stackoverflow.com/questions/7858817/unpacking-a-tuple-to-call-a-matching-function-pointer

        template<int ...>
        struct NumberPack { };

        // generate NumberPack<0, 1, .., N-1>

        template<int N, int ...S>
        struct GenNumberPack : GenNumberPack<N-1, N-1, S...> { };

        template<int ...S>
        struct GenNumberPack<0, S...> 
        {
            typedef NumberPack<S...> type;
        };


                
        template<typename R, template<typename...> class Params, typename... Args>
        R call(const Function<R(Args...)>& func, const Params<Args...>& params)
        { 
            return call_helper(func, params, typename GenNumberPack<sizeof...(Args)>::type()); 
        }

        template<typename R, template<typename...> class Params, typename... Args, int... S>
        R call_helper(const Function<R(Args...)>& func, const Params<Args...>& params, NumberPack<S...>)
        { 
            return func(std::get<S>(params)...); 
        }
    }



    struct DelayedNativeCallBase
    {
        const char* className;
        const char* methodName;

        virtual ~DelayedNativeCallBase() {}
        virtual void exe() = 0;
    };

    template<typename... Args> struct DelayedCallHelper;


    // invoke the delayed calls in a dependent thread.
    class DelayCallManager
    {        
        Vector<DelayedNativeCallBase*>    delayedNativeCalls;
        AdaptiveLock                      callQueueLock;

    public:

        static DelayCallManager& Get()
        {
            static DelayCallManager i;
            return i;
        }

        void DispatchDelayedCalls()
        {         
            Vector<DelayedNativeCallBase*> calls;
            {
                callQueueLock.Lock();
                calls.Swap(delayedNativeCalls);
                callQueueLock.Unlock();
            }
            
            for(unsigned i=0; i<calls.Size(); i++) {
                calls[i]->exe();
                delete(calls[i]);
            }
        }

        void AddDelayedCall(DelayedNativeCallBase* call)
        {
            callQueueLock.Lock();
            delayedNativeCalls.PushBack(call);
            callQueueLock.Unlock();
        }
        

        template<typename... Args>
        inline Function<void(Args...)>* GetHook(Function<void(Args...)>* userCallback, const char* className, const char* methodName)
        {
            // safe mem leak: we bind the method to jni only once.

            typedef DelayedCallHelper<Args...> Helper;

            Helper* h = new(Helper)(userCallback, className, methodName);
            return &h->nativeCall;
        } 

    };


    template<typename... Args>
    struct DelayedCallHelper
    {
        typedef Function<void(Args...)> Func;

        const char* className;
        const char* methodName;
        Func*       userCallback;
        Func        nativeCall;


        DelayedCallHelper(Func* userCallback, const char* className, const char* methodName)
        {
            this->userCallback  = userCallback;
            this->className     = className;
            this->methodName    = methodName;
            nativeCall          = Bind(*this, &DelayedCallHelper::OnCalled);
        }

        void OnCalled(Args... args)
        {
            struct DelayedCall : DelayedNativeCallBase
            {
                Func*               userCallback;
                std::tuple<Args...> params;

                void exe() 
                { 
                    if (*userCallback) {
                        Private::call(*userCallback, params);
                        TRACE(LogModule_Default, "Jni: delayed native func called: %s.%s", className, methodName);
                    }
                    else {
                        WARNING(LogModule_Default, false, "Jni: delayed calling unimplementated native method[%s].", methodName);
                    }
                }
            };

            DelayedCall* call   = new(DelayedCall);
            call->userCallback  = userCallback;
            call->className     = className;
            call->methodName    = methodName;
            call->params        = std::make_tuple(args...);

            DelayCallManager::Get().AddDelayedCall(call);
        }
    };
}

#endif