LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS) 

LOCAL_MODULE := HelloLog
LOCAL_SRC_FILES := helloLog.c
LOCAL_MODULE_TAGS := optional

LOCAL_SHARED_LIBRARIES := libcutils

include $(BUILD_EXECUTABLE) 
