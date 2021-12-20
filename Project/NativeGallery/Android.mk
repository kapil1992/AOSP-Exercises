LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := libNativeAshmemBinder
LOCAL_SRC_FILES := jni/native_binder_ashmem.cpp
LOCAL_MODULE_TAGS := optional
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../libbinderexample
LOCAL_SHARED_LIBRARIES += libutils libcutils libbinder
LOCAL_SHARED_LIBRARIES += libbinderimageserver

include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_PACKAGE_NAME := NativeGallary
LOCAL_MODULE_TAG := optional
LOCAL_DEX_PREOPT := false

LOCAL_SRC_FILES := $(call all-java-files-under, src)
LOCAL_SRC_FILES += $(call all-Iaidl-files-under, src)

include $(BUILD_PACKAGE)
