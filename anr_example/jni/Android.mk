LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libanrjni
LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES := anr-jni.c
LOCAL_CPPFLAGS := -O0 -fno-inline 

include $(BUILD_SHARED_LIBRARY)
