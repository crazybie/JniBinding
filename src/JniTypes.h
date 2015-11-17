#if defined(PLATFORM_ANDROID)

#pragma once

#include "System\String\String.h"
#include "System\Container\Vector.h"
#include "System\String\StringUtilities.h"
#include "System/Utilities/Function/Function.h"
#include "System/Utilities/Function/Bind.h"

#include <jni.h>


namespace JniHelper
{
    using String;
    using Vector;
    using Function;


    template<typename T>struct JniType;

    // we always receive the param by const reference, see toJni.
    // so use the same processing way with value type.
    template<typename T>struct JniType<T&>          : JniType<T> {};
    template<typename T>struct JniType<const T&>    : JniType<T> {};
    
    
    // we only support common types here to make things simpler.

    template<> struct JniType<void>                
    { 
        typedef void            JniT;     
        static String           jniTypeStr(){ return "V";}  
    };

    //
    // WARNING: the java side must use `Object` to map to the `jobject` type in c++.
    //
    template<> struct JniType<jobject>                
    { 
        typedef jobject         JniT;     
        typedef jobject         (*staticJobject)        (JNIEnv*,jclass,jmethodID,...);  

        static jobject          toJni(JNIEnv* e, jobject i)                 { return (jobject)i; }
        static jobject          fromJni(JNIEnv* e, jobject i)               { return i; } 
        static String           toStr(jobject i)                            { return Str::Format("%x", i);}
        static String           jniTypeStr()                                { return "Ljava/lang/Object;";}    
        static staticJobject    getStaticMethodByRet(JNIEnv* e)             { return e->functions->CallStaticObjectMethod;     } 
    };

    template<> struct JniType<unsigned int>        
    { 
        typedef jint            JniT;     
        typedef jint            (*staticInt)        (JNIEnv*,jclass,jmethodID,...);  

        static jint             toJni(JNIEnv* e, unsigned int i)            { return (jint)i; }
        static unsigned int     fromJni(JNIEnv* e, jint i)                  { return (unsigned int)i; }    
        static String           toStr(jint i)                               { return Str::Format("%u", i);}
        static String           jniTypeStr()                                { return "I";}          
        static staticInt        getStaticMethodByRet(JNIEnv* e)             { return e->functions->CallStaticIntMethod;     }    
    };


    template<> struct JniType<long long>           
    { 
        typedef jlong           JniT;
        typedef jlong           (*staticLong)       (JNIEnv*,jclass,jmethodID,...);        

        static staticLong       getStaticMethodByRet(JNIEnv* e)             { return e->functions->CallStaticLongMethod;    }    
        static long long        fromJni(JNIEnv* e, jlong i)                 { return i; }
        static jlong            toJni(JNIEnv* e, long long i)               { return i;}
        static String           toStr(jlong i)                              { return Str::Format("%llu", i);}
        static String           jniTypeStr()                                { return "J";}  
    };

    template<> struct JniType<int>                 
    {
        typedef jint            JniT;             
        typedef jint            (*staticInt)        (JNIEnv*,jclass,jmethodID,...);     

        static jint             toJni(JNIEnv* e, int i)                     { return i;}
        static int              fromJni(JNIEnv* e, jint i)                  { return i; }        
        static String           jniTypeStr()                                { return "I";}  
        static String           toStr(jint i)                               { return Str::Format("%d", i);}
        static staticInt        getStaticMethodByRet(JNIEnv* e)             { return e->functions->CallStaticIntMethod;     }    
    };


    template<> struct JniType<bool>                
    { 
        typedef jboolean        JniT;     
        typedef jboolean        (*staticBool)       (JNIEnv*,jclass,jmethodID,...);

        static jboolean         toJni(JNIEnv* e, bool i)                    { return i; }  
        static bool             fromJni(JNIEnv* e, jboolean i)              { return i; }    
        static String           jniTypeStr()                                { return "Z";}  
        static String           toStr(jboolean i)                           { return i?"true":"false";}
        static staticBool       getStaticMethodByRet(JNIEnv* e)             { return e->functions->CallStaticBooleanMethod; }
    };


    template<>struct JniType<float>               
    { 
        typedef jfloat          JniT;     
        typedef jfloat          (*staticFloat)      (JNIEnv*,jclass,jmethodID,...);        

        static jfloat           toJni(JNIEnv* e, float i)                   { return i; }
        static String           jniTypeStr()                                { return "F";}  
        static float            fromJni(JNIEnv* e, jfloat i)                { return i; }
        static String           toStr(float i)                              { return Str::Format("%f", i); }
        static staticFloat      getStaticMethodByRet(JNIEnv* e)             { return e->functions->CallStaticFloatMethod;   }  
    };


    template<>struct JniType<String>              
    { 
        typedef jstring         JniT;     
        typedef jstring         (*staticStr)      (JNIEnv*,jclass,jmethodID,...);        

        static String           jniTypeStr()                                { return "Ljava/lang/String;";} 
        static String           fromJni(JNIEnv* e, jstring i)               { const char* s=e->GetStringUTFChars(i, 0); JniNativeGc::instance().add(i, s); return s;} 
        static jstring          toJni(JNIEnv* e, const String& i)           { jstring r=e->NewStringUTF(i.CStr()); return r; }
        static String           toStr(const String& i)                      { return i; }
        static staticStr        getStaticMethodByRet(JNIEnv* e)             { return (staticStr) e->functions->CallStaticObjectMethod;   }  
    };


    template<>struct JniType< Vector<int> >
    {
        typedef jintArray       JniT;
        typedef JniT            (*staticIntA)(JNIEnv*,jclass,jmethodID,...);

        static String           jniTypeStr()                                { return "[I"; }
        static staticIntA       getStaticMethodByRet(JNIEnv* e)             { return (staticIntA) e->functions->CallStaticObjectMethod;   }  
        static String           toStr(const Vector<int>& i)                 { return Str::Format("vector[size=%d]", i.Size()); }

        static JniT             toJni(JNIEnv* e, const Vector<int>& i)      {
            jintArray buf = e->NewIntArray(i.Size());
            e->SetIntArrayRegion(buf, 0, i.Size(), (jint*)&i[0]);
            JniNativeGc::instance().add(buf, (jint*)&i[0]);
            return buf;
        }

        static Vector<int>      fromJni(JNIEnv* e, jintArray i)             { 
            jint* start = e->GetIntArrayElements(i, 0);
            jsize len = e->GetArrayLength(i);
            Vector<int> r(len);
            MemoryCopy(&r[0], start, len/sizeof(jint));
            JniNativeGc::instance().add(i, start);
            return r;
        }
    };


    // we can pass function object to java(and vice versa) as a long type.
    template<typename RET, typename... Args> 
    struct JniType< Function<RET(Args...)> >
    { 
        typedef Function<RET(Args...)> Func;

        typedef jlong      JniT;     
        typedef jlong      (*staticLong)       (JNIEnv*,jclass,jmethodID,...);

        static jlong        toJni(JNIEnv* e, const Func& i)                 { return (jlong) new(Func)(i); }  
        static Func         fromJni(JNIEnv* e, jlong i)                     { Func* f = (Func*)i; Func r=*f; JniNativeGc::instance().add(f); return r; } 
        static String       toStr(const Func& i)                            { return Str::Format("function[%x]", i.GetCallHook()); }
        static String       jniTypeStr()                                    { return "J";}  
        static staticLong   getStaticMethodByRet(JNIEnv* e)                 { return e->functions->CallStaticLongMethod; }
    };


}


#endif