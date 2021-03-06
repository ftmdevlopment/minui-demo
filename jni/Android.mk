# Copyright (C) 2007 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

LOCAL_PATH := $(call my-dir)

C_ROOT := $(LOCAL_PATH)

TARGET_USE_ADF := false
TARGET_USE_DOUBLE_BUFFER := false
TARGET_RECOVERY_PIXEL_FORMAT := BGRA_8888

include $(CLEAR_VARS)

LOCAL_MODULE := mint
LOCAL_FORCE_STATIC_EXECUTABLE := true
LOCAL_MODULE_TAGS := tests
LOCAL_CFLAGS += -Wno-unused-parameter
LOCAL_SRC_FILES := \
    main.c \

LOCAL_STATIC_LIBRARIES := \
    libminui \
    libpng \
    libz \
    libstdc++ \
    libc

include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)

LOCAL_MODULE := clockui
LOCAL_FORCE_STATIC_EXECUTABLE := true
LOCAL_MODULE_TAGS := tests
LOCAL_CFLAGS += -Wno-unused-parameter
LOCAL_SRC_FILES := \
    clock_ui.c \

LOCAL_STATIC_LIBRARIES := \
    libminui \
    libpng \
    libz \
    libstdc++ \
    libc

include $(BUILD_EXECUTABLE)


include $(LOCAL_PATH)/minui/Android.mk \
    $(LOCAL_PATH)/libpng/Android.mk \
    $(LOCAL_PATH)/zlib/Android.mk \

ifeq ($(TARGET_USE_ADF),true)
    $(LOCAL_PATH)/adf/Android.mk
endif
