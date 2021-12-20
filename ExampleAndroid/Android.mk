LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS) 

LOCAL_MODULE := ExampleAndroid
LOCAL_SRC_FILES := example_android.c
LOCAL_MODULE_TAGS := optional

ifeq ($(USE_EXAMPLE_ANDROID),YES)
LOCAL_CFLAGS := -DEXAMPLE_ANDROID
endif

include $(BUILD_EXECUTABLE) 
