
include .config.mk

ifndef NDKROOT
  $(error "path to Android not defined, set NDKROOT in .config.mk")
endif

AGCC=$(NDKROOT)/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86/bin/arm-linux-androideabi-gcc

ACPPFLAGS := -DANDROID -DOS_ANDROID
ACFLAGS := --sysroot $(NDKROOT)/platforms/android-9/arch-arm -mandroid
ALDFLAGS := --sysroot $(NDKROOT)/platforms/android-9/arch-arm -mandroid

PROGRAMS := memeater

memeater_OBJECTS := memeater.o

.PHONY: all clean

.DEFAULT: all

.SECONDEXPANSION:

all : $(PROGRAMS)

clean :
	$(RM) $(PROGRAMS)
	$(RM) $(sort $(foreach prog,$(PROGRAMS),$($(prog)_OBJECTS)))

%.o : %.c
	$(AGCC) -c $($@_CPPFLAGS) $(ACPPFLAGS) $(CPPFLAGS) $($@_CFLAGS) $(ACFLAGS) $(CFLAGS) $< -o $@

$(PROGRAMS) : $$($$(@)_OBJECTS)
	$(AGCC) $($@_LDFLAGS) $(ALDFLAGS) $(LDFLAGS) $^ -o $@
