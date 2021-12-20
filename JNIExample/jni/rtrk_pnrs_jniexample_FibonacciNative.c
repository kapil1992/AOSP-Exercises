#include "rtrk_pnrs_jniexample_FibonacciNative.h"
#include <cutils/log.h>

/*
 * Class:     rtrk_pnrs_jniexample_FibonacciNative
 * Method:    getFebonacci
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_rtrk_pnrs_jniexample_FibonacciNative_getFebonacci
  (JNIEnv *env, jclass class, jint num)
{
  ALOGD("JNI getFibonacci called\n");
  return fib(num);   
}


int fib(int n)
{
    if (n <= 1)
        return n;
    return fib(n-1) + fib(n-2);
}
