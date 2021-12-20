LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS) 

LOCAL_MODULE := NativeService
LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := native_service.cpp
LOCAL_SRC_FILES += ImageDataServer.cpp

LOCAL_SHARED_LIBRARIES := libcutils libutils libbinder
LOCAL_SHARED_LIBRARIES += libbinderimageserver

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../libbinderexample

include $(BUILD_EXECUTABLE) 
