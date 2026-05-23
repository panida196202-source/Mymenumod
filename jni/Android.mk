LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := ModMenu
LOCAL_CFLAGS    := -w -s -Wno-error=format-security -Wno-error=pointer-arith
LOCAL_CPPFLAGS  := -w -s -Wno-error=format-security -Wno-error=pointer-arith
LOCAL_CPPFLAGS  += -std=c++17 -Wno-error=c++11-narrowing
LOCAL_LDFLAGS   += -Wl,--gc-sections,--strip-all
LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv2 -lz
LOCAL_ARM_MODE  := arm

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/Includes \
                    $(LOCAL_PATH)/KittyMemory \
                    $(LOCAL_PATH)/Menu \
                    $(LOCAL_PATH)/And64InlineHook \
                    $(LOCAL_PATH)/Substrate

LOCAL_SRC_FILES := Main.cpp \
                   Substrate/hde64.c \
                   Substrate/SubstrateDebug.cpp \
                   Substrate/SubstrateHook.cpp \
                   Substrate/SubstratePosixMemory.cpp \
                   Substrate/SymbolFinder.cpp \
                   KittyMemory/KittyMemory.cpp \
                   KittyMemory/MemoryPatch.cpp \
                   KittyMemory/MemoryBackup.cpp

include $(BUILD_SHARED_LIBRARY)
