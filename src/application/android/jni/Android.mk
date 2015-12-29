LOCAL_PATH := $(call my-dir)

GONA_BUILD_DEMO := true
GONA_BUILD_FREETYPE := false

# build gona demo
ifeq ($(GONA_BUILD_DEMO), true)
include $(CLEAR_VARS)

FD_SRC_PATH := ../../foundation

LOCAL_MODULE    := Gona
LOCAL_SRC_FILES := \
	Gona.cpp \
	../$(FD_SRC_PATH)/graphics/gl/GnGLRendererES.cpp \
	../$(FD_SRC_PATH)/graphics/gl/GnGLFontManager.cpp \
	../$(FD_SRC_PATH)/graphics/GnImage.cpp \

LOCAL_C_INCLUDES := \
	$(FD_SRC_PATH) \
	$(FD_SRC_PATH)/graphics \
	$(FD_SRC_PATH)/graphics/gl \
	$(FD_SRC_PATH)/third_party/freetype/include

LOCAL_CPPFLAGS	+= -D GONA_FOR_ANDROID
LOCAL_CFLAGS	+= -D GONA_FOR_ANDROID
LOCAL_LDLIBS    := -llog -lGLESv2 -lz

LOCAL_STATIC_LIBRARIES := libfreetype
LOCAL_LDFLAGS	:= obj/local/armeabi/libfreetype.a

include $(BUILD_SHARED_LIBRARY)
endif

# build freetype
ifeq ($(GONA_BUILD_FREETYPE), true)
include $(CLEAR_VARS)

FT_SRC_PATH := ../../../foundation/third_party/freetype
FT_INC_PATH := ../../foundation/third_party/freetype

LOCAL_MODULE := freetype
LOCAL_SRC_FILES := \
	$(FT_SRC_PATH)/src/autofit/autofit.c		\
	$(FT_SRC_PATH)/src/base/ftbase.c			\
	$(FT_SRC_PATH)/src/base/ftbbox.c			\
	$(FT_SRC_PATH)/src/base/ftbdf.c				\
	$(FT_SRC_PATH)/src/base/ftbitmap.c			\
	$(FT_SRC_PATH)/src/base/ftglyph.c			\
	$(FT_SRC_PATH)/src/base/ftinit.c			\
	$(FT_SRC_PATH)/src/base/ftmm.c				\
	$(FT_SRC_PATH)/src/base/ftpfr.c				\
	$(FT_SRC_PATH)/src/base/ftstroke.c			\
	$(FT_SRC_PATH)/src/base/ftsynth.c			\
	$(FT_SRC_PATH)/src/base/ftsystem.c			\
	$(FT_SRC_PATH)/src/base/fttype1.c			\
	$(FT_SRC_PATH)/src/base/ftwinfnt.c			\
	$(FT_SRC_PATH)/src/bdf/bdf.c				\
	$(FT_SRC_PATH)/src/cache/ftcache.c			\
	$(FT_SRC_PATH)/src/cff/cff.c				\
	$(FT_SRC_PATH)/src/cid/type1cid.c			\
	$(FT_SRC_PATH)/src/gzip/ftgzip.c			\
	$(FT_SRC_PATH)/src/lzw/ftlzw.c				\
	$(FT_SRC_PATH)/src/pcf/pcf.c				\
	$(FT_SRC_PATH)/src/pfr/pfr.c				\
	$(FT_SRC_PATH)/src/psaux/psaux.c			\
	$(FT_SRC_PATH)/src/pshinter/pshinter.c		\
	$(FT_SRC_PATH)/src/psnames/psmodule.c		\
	$(FT_SRC_PATH)/src/raster/raster.c			\
	$(FT_SRC_PATH)/src/sfnt/sfnt.c				\
	$(FT_SRC_PATH)/src/smooth/smooth.c			\
	$(FT_SRC_PATH)/src/truetype/truetype.c		\
	$(FT_SRC_PATH)/src/type1/type1.c			\
	$(FT_SRC_PATH)/src/type42/type42.c			\
	$(FT_SRC_PATH)/src/winfonts/winfnt.c	

LOCAL_C_INCLUDES := \
	$(FT_INC_PATH)/src/base \
	$(FT_INC_PATH)/src/pcf \
	$(FT_INC_PATH)/src/psaux \
	$(FT_INC_PATH)/src/pshinter \
	$(FT_INC_PATH)/src/psnames \
	$(FT_INC_PATH)/src/sfnt \
	$(FT_INC_PATH)/src/truetype \
	$(FT_INC_PATH)/src/type1  \
	$(FT_INC_PATH)/src/winfonts \
	$(FT_INC_PATH)/include/freetype \
	$(FT_INC_PATH)/include \
	$(FT_INC_PATH)/include/freetype/internal
	
LOCAL_CPPFLAGS += -DFT2_BUILD_LIBRARY
LOCAL_CFLAGS += -DFT2_BUILD_LIBRARY

include $(BUILD_STATIC_LIBRARY) 
endif
