LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libbinderimageserver
LOCAL_MODULE_TAGS := optional

LOCAL_SHARED_LIBRARIES += libutils
LOCAL_SHARED_LIBRARIES += libcutils
LOCAL_SHARED_LIBRARIES += libbinder

LOCAL_SRC_FILES += IImageDataServer.cpp
LOCAL_SRC_FILES += BnImageDataServer.cpp
LOCAL_SRC_FILES += BpImageDataServer.cpp

include $(BUILD_SHARED_LIBRARY)

