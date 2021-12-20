LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS) 

LOCAL_MODULE := CallStackExample
LOCAL_SRC_FILES := callstack_example.cpp
LOCAL_CPPFLAGS := -O0 -fno-inline
LOCAL_MODULE_TAGS := optional

LOCAL_SHARED_LIBRARIES := libutils

include $(BUILD_EXECUTABLE) 
