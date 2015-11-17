#pragma once
#if defined(PLATFORM_ANDROID)

#include "System\String\String.h"
#include "System\Container\Set.h"
#include "System\Container\Vector.h"
#include "System\Utilities\Function\Details\FunctionBase.h"
#include "..\Utility\ForEach.h"


namespace JniHelper
{
    using String;
    using Set;
    using Vector;

    // scoped gc.
    class JniNativeGc
    {
        JNIEnv* e;

    public:
        JniNativeGc(JNIEnv* e) { this->e = e; instanceStack().PushBack(this); }
        ~JniNativeGc()
        {
            releaseIntArray();
            releaseStrRes();
            releaseFuncRes();
            instanceStack().PopBack();
        }

        static Vector<JniNativeGc*>& instanceStack() { static Vector<JniNativeGc*> s; return s; }
        
        static JniNativeGc& instance() { assert(instanceStack().Size(), "no gc instance declared."); return *instanceStack().Back(); }

        // int array
        struct IntArrayRes
        {
            jintArray   m_jintArray;
            jint*       m_cArray;
            bool operator<(const IntArrayRes& r)const{ return m_cArray < r.m_cArray; }
        };
        Set<IntArrayRes> intArraryRes;
        void add(jintArray i, jint* c)
        {
            IntArrayRes r={i, c};
            intArraryRes.Insert(r);
        }
        void releaseIntArray()
        { 
            foreach(const IntArrayRes& i, intArraryRes) {
                e->ReleaseIntArrayElements(i.m_jintArray, i.m_cArray, 0);
            }
        }



        // string
        struct StringRes
        {
            jstring     jniStr;
            const char* cstr;
            bool operator<(const StringRes& r)const{ return cstr < r.cstr; }
        };
        Set<StringRes> stringRes;
        void add(jstring i, const char* c)
        {
            StringRes r={i,c};
            stringRes.Insert(r);
        }
        void releaseStrRes()
        {
            foreach(const StringRes& i, stringRes){
                e->ReleaseStringUTFChars(i.jniStr, i.cstr);
            }  
        }

        // functions
        typedef Details::FunctionBase FuncBase;
        Set<FuncBase*> funcs;
        void add(FuncBase* f) { funcs.Insert(f);}
        void releaseFuncRes()
        {
            foreach(FuncBase* f, funcs){
                delete(f);
            }  
        }
    };


}

#endif