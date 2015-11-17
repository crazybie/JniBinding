#if 0

// MyJavaClass.java
class MyJavaClass
{
    public static native void cppFunction(int value);

    public static String javaFunction()
    {
        return "string from java";
    }
};

//////////////////////////////////////////////////////////////////////////

#include "JniClass.h"

JniHelper::JniClass         activity("com.engine.MyJavaClass");

Function<String()>    javaFunction;
Function<void(int)>   cppFunction;


void init()
{
    activity.BindNativeMethod       ("cppFunction",     &cppFunction);
    activity.BindStaticJavaMethod   ("javaFunction",    &javaFunction);

    activity.RegisterAll();
}

void CalledByJava(int valueFromJava)
{
    // c++ function called by java code!
}

void test()
{
    // call the java function
    String stringFromJava = javaFunction();

    // or redirect the function call from java to our function.
    cppFunction = Bind(CalledByJava);
};

#endif