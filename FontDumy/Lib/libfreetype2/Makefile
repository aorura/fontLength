SHELL = /bin/sh

TOP_DIR = $(shell pwd)

PREFIX = /opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain/bin/arm-fsl-linux-gnueabi-
CC = $(PREFIX)g++
AR = $(PREFIX)ar

CFLAGS += -fPIC
CFLAGS += -O2 -g
CFLAGS += -march=armv6 -mno-thumb-interwork -mfpu=vfp -rdynamic
CFLAGS += -DIMX35_3STACK
CFLAGS += -DARCH_ARM
CFLAGS += -DBUILD_VERSION_2
CFLAGS += -DMLINK_ENABLE
CFLAGS += -DCARPLAY_ENABLE
CFLAGS += -DX86=0
CFLAGS += -D_LINUX
CFLAGS += -D_UNICODE
CFLAGS += -D_IS_TARGET
CFLAGS += -Wno-deprecated
CFLAGS += -DFT_DEBUG_LEVEL_ERROR
CFLAGS += -DFT_DEBUG_LEVEL_TRACE
CFLAGS += -DFT2_BUILD_LIBRARY

INC += -I../../Inc/freetype2/

OBJS += ./src/autofit/autofit.o
OBJS += ./src/bdf/bdf.o
OBJS += ./src/cff/cff.o
OBJS += ./src/base/ftbase.o
OBJS += ./src/base/ftbitmap.o
OBJS += ./src/cache/ftcache.o
OBJS += ./src/base/ftfstype.o
OBJS += ./src/base/ftgasp.o
OBJS += ./src/base/ftglyph.o
OBJS += ./src/gzip/ftgzip.o
OBJS += ./src/base/ftinit.o
OBJS += ./src/lzw/ftlzw.o
OBJS += ./src/base/ftstroke.o
OBJS += ./src/base/ftsystem.o
OBJS += ./src/smooth/ftsmooth.o

OBJS += ./src/base/ftbbox.o
OBJS += ./src/base/ftgxval.o
OBJS += ./src/base/ftlcdfil.o
OBJS += ./src/base/ftmm.o
OBJS += ./src/base/ftotval.o
OBJS += ./src/base/ftpatent.o
OBJS += ./src/base/ftpfr.o
OBJS += ./src/base/ftsynth.o
OBJS += ./src/base/fttype1.o
OBJS += ./src/base/ftwinfnt.o
OBJS += ./src/base/ftxf86.o
OBJS += ./src/pcf/pcf.o
OBJS += ./src/pfr/pfr.o
OBJS += ./src/psaux/psaux.o
OBJS += ./src/pshinter/pshinter.o
OBJS += ./src/psnames/psmodule.o
OBJS += ./src/raster/raster.o
OBJS += ./src/sfnt/sfnt.o
OBJS += ./src/truetype/truetype.o
OBJS += ./src/type1/type1.o
OBJS += ./src/cid/type1cid.o
OBJS += ./src/type42/type42.o
OBJS += ./src/winfonts/winfnt.o

OBJS += ./platform/nsf/ftdebug.o

STATIC_LIB = libfreetype2.a
SHARED_LIB = libfreetype2.so

all: target

target: $(SHARED_LIB) $(STATIC_LIB)

$(SHARED_LIB): $(OBJS)
	$(CC) -shared $^ -Wl,-rpath,/lib -o $@

$(STATIC_LIB): $(OBJS)
	$(AR) rcs $@ $^

.c.o:
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	rm -f $(STATIC_LIB)$(SHARED_LIB) $(OBJS)

