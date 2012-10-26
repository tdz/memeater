
LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE      := memeater
LOCAL_MODULE_TAGS := optional eng
LOCAL_MODULE_PATH := $(TARGET_OUT_OPTIONAL_EXECUTABLES)
LOCAL_SRC_FILES   := memeater.c

include $(BUILD_EXECUTABLE)
