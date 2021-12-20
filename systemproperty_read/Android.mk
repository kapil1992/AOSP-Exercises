LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS) 

LOCAL_MODULE := SystemPropertyReader
LOCAL_SRC_FILES := read_systemprop.c
LOCAL_MODULE_TAGS := optional

LOCAL_SHARED_LIBRARIES := libcutils

include $(BUILD_EXECUTABLE) 
