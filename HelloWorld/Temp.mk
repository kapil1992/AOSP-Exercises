LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS) 

LOCAL_MODULE := HelloWorld
LOCAL_SRC_FILES := HelloWorld.c
LOCAL_MODULE_TAGS := optional

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../HelloStatic \
                    $(LOCAL_PATH)/../HelloShared

LOCAL_STATIC_LIBRARIES := libhellostatic
LOCAL_SHARED_LIBRARIES := libhelloshared

include $(BUILD_EXECUTABLE) 
