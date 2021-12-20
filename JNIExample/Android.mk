LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libfibonacci
LOCAL_SRC_FILES := jni/rtrk_pnrs_jniexample_FibonacciNative.c
LOCAL_MODULE_TAGS := optional
LOCAL_SHARED_LIBRARIES := libcutils

include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_PACKAGE_NAME := JNIExample
LOCAL_MODULE_TAGS := optional
LOCAL_DEX_PREOPT := false

LOCAL_SRC_FILES += src/rtrk/pnrs/jniexample/FibonacciNative.java
LOCAL_SRC_FILES += src/rtrk/pnrs/jniexample/MainActivity.java

include $(BUILD_PACKAGE)

include $(call all-makefiles-under,$(LOCAL_PATH))
