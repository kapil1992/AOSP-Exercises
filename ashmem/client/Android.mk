LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := binder_ashmem_client_example
LOCAL_MODULE_TAGS := optional

LOCAL_SHARED_LIBRARIES += libutils libcutils libbinder
LOCAL_SHARED_LIBRARIES += libbinderexample

LOCAL_SRC_FILES += client.cpp

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../libbinderexample

include $(BUILD_EXECUTABLE)

