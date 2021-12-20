#include <jni.h>
#include <unistd.h>


void
Java_rtrk_pnrs_anr_ANRExample_anrSleep( JNIEnv* env, jobject thiz )
{
    sleep(4);
}

unsigned
Java_rtrk_pnrs_anr_ANRExample_anrCrash( JNIEnv* env, jobject thiz )
{
    unsigned* x = 0x12345678;
    *x = 10;
    return *x;
}
