LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := binder_server_example
LOCAL_MODULE_TAGS := optional

LOCAL_SHARED_LIBRARIES += libutils libcutils libbinder
LOCAL_SHARED_LIBRARIES += libbinderexample

LOCAL_SRC_FILES += server.cpp
LOCAL_SRC_FILES += Example.cpp

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../libbinderexample

include $(BUILD_EXECUTABLE)

