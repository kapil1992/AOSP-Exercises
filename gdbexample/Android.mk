LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_C_INCLUDES += \
	$(LOCAL_PATH)/include

LOCAL_SRC_FILES:= source/gdbexample_lib_1.cpp
LOCAL_MODULE:= libgdbexample_lib_1
LOCAL_SHARED_LIBRARIES:= libgdbexample_lib_2
LOCAL_MODULE_TAGS:= optional

include $(BUILD_SHARED_LIBRARY)


include $(CLEAR_VARS)

LOCAL_C_INCLUDES += \
	$(LOCAL_PATH)/include

LOCAL_SRC_FILES:= source/gdbexample_lib_2.cpp
LOCAL_MODULE:= libgdbexample_lib_2
LOCAL_SHARED_LIBRARIES:= libgdbexample_lib_3
LOCAL_MODULE_TAGS:= optional

include $(BUILD_SHARED_LIBRARY)


include $(CLEAR_VARS)

LOCAL_C_INCLUDES += \
	$(LOCAL_PATH)/include

LOCAL_SRC_FILES:= source/gdbexample_lib_3.cpp
LOCAL_MODULE:= libgdbexample_lib_3
LOCAL_MODULE_TAGS:= optional

include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_C_INCLUDES += \
	$(LOCAL_PATH)/include

LOCAL_SRC_FILES:= source/gdbexample_exe.cpp
LOCAL_SHARED_LIBRARIES:= liblog libgdbexample_lib_1
LOCAL_MODULE:= gdbexample
LOCAL_C_FLAGS += -g -O0 -fno-inline
LOCAL_CPP_FLAGS += -g -O0 -fno-inline
LOCAL_MODULE_TAGS:= optional

include $(BUILD_EXECUTABLE)

