# JniBinding
bind cpp function to java via jni.


easy way to bind cpp functions to android java side via jni, no tedious wrapper code any more.

NODE:
most of the code was written at my free time, but now the code here may not pass the compiling 
since it is be using in production projects and I only grab a latest copy out here and removed the company specific part.
the main purpose is just to give a solution for reference. 
you can use the code to do whatever you want without any licence restriction, but I would like you
to just let me know its useful to you.
One day I may make it compiles if there is any request for it.


Features:
- export cpp function to java
- export java function to cpp
- auto manage cpp object lifetime 
- thread issue of java calls from android UI thread.
- pass cpp functions to java and back to cpp.

Limitations: 
- only support static java method to simplify the java object lifetime issue.
- no support for struct binding.

please check the TODO list for more details.


