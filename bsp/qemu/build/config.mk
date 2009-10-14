#
# RT-Thread Makefile
# CFLAGS 	for C compiler flags
# CPPFLAGS	for C++ compiler flags
# LDFLAGS 	for ld link flags
# LDLIBS	for libraries should be linked
# AFLAGS	for assemble flags
#

include $(KERNEL_ROOT)/config.local
include $(KERNEL_ROOT)/config.target

#
# toolchain variables
#
CC		= $(PREFIX)gcc
CXX		= $(PREFIX)g++
LD		= $(PREFIX)ld
AR		= $(PREFIX)ar
AS		= $(PREFIX)as
RANLIB	= $(PREFIX)ranlib
NM		= $(PREFIX)nm
OBJCOPY	= $(PREFIX)objcopy
OBJDUMP	= $(PREFIX)objdump
STRIP	= $(PREFIX)strip
SIZE	= $(PREFIX)size
RM		= rm -rf
MKDIR	= mkdir -p

#
# start object and library
#
STARTOBJ	=	$(KERNEL_ROOT)/lib/start_$(CPU).o
LIBCPU		= 	$(KERNEL_ROOT)/lib/libcpu_$(CPU).a
KERNEL		= 	$(KERNEL_ROOT)/lib/libkernel_$(ARCH).a
LIBBSP  	= 	$(KERNEL_ROOT)/lib/libbsp_$(BOARD).a
LIBFINSH	= 	$(KERNEL_ROOT)/lib/libfinsh_$(ARCH).a
LIBEFSL		= 	$(KERNEL_ROOT)/lib/libefsl-fs-vfat.a	\
				$(KERNEL_ROOT)/lib/libefsl-base.a
LIBRTGUI 	=	$(KERNEL_ROOT)/lib/librtgui_widgets.a	\
				$(KERNEL_ROOT)/lib/librtgui_server.a 	\
				$(KERNEL_ROOT)/lib/librtgui_common.a	\
				$(KERNEL_ROOT)/lib/librtgui_app.a
LIBLWIP		=	$(KERNEL_ROOT)/lib/liblwip_$(ARCH).a
LIBCPP		= 	$(KERNEL_ROOT)/lib/librtt++_$(ARCH).a
LIBMINIC	= 	$(KERNEL_ROOT)/lib/libminilibc_$(ARCH).a

LDLIBS		=	-lcpu_$(CPU) -lkernel_$(ARCH) -lbsp_$(BOARD)

#
# ld script, according to build type, RAM or ROM
#
ifeq ($(BUILDTYPE), RAM)
LDSCRIPT= $(KERNEL_ROOT)/bsp/$(BOARD)/$(BOARD)_ram.lds
else
LDSCRIPT= $(KERNEL_ROOT)/bsp/$(BOARD)/$(BOARD)_rom.lds
endif

#
# RT-Thread component
#
ifeq ($(RT_USING_FINSH), 1)
CFLAGS  += -I$(KERNEL_ROOT)/finsh
LDLIBS	+= -lfinsh_$(ARCH)
endif

ifeq ($(RT_USING_RTGUI), 1)
CFLAGS	+= -I$(KERNEL_ROOT)/rtgui/include 
LDLIBS	+= -lrtgui_server -lrtgui_common -lrtgui_widgets -lrtgui_app
endif

ifeq ($(RT_USING_LWIP), 1)
CFLAGS 	+= -I$(KERNEL_ROOT)/net/lwip/src \
			-I$(KERNEL_ROOT)/net/lwip/src/include \
			-I$(KERNEL_ROOT)/net/lwip/src/include/ipv4 \
			-I$(KERNEL_ROOT)/net/lwip/src/arch/include
LDLIBS	+= -llwip_$(ARCH)
endif

ifeq ($(RT_USING_EFSL), 1)
CFLAGS	+= -I$(KERNEL_ROOT)/filesystem/efsl/src/fs/vfat/include \
			-I$(KERNEL_ROOT)/filesystem/efsl/src/base/include \
			-I$(KERNEL_ROOT)/filesystem/efsl/src/include \
			-I$(KERNEL_ROOT)/filesystem/efsl/conf
LDLIBS	+= -lefsl-base -lefsl-fs-vfat
endif

ifeq ($(RT_USING_CPLUSPLUS), 1)
CFLAGS	+= 
LDLIBS	+= -lrtt++_$(ARCH)
endif

ifeq ($(RT_USING_NEWLIB), 1)
CFLAGS	+= -I$(KERNEL_ROOT)/newlib/libc/include
LDLIBS	+= -lnewlib_$(ARCH)
else
ifeq ($(RT_USING_MINILIBC), 1)
CFLAGS 	+= -I$(KERNEL_ROOT)/libc/minilibc
LDLIBS	+= -lminilibc_$(ARCH)
endif
endif

#
# compiler, assemble and ld link flag
#
CFLAGS += -I$(KERNEL_ROOT)/include -I$(KERNEL_ROOT)/bsp/$(BOARD) -Wall -nostdinc -fno-builtin

ifeq ($(RELEASETYPE), DEBUG)
CFLAGS += -ggdb
AFLAGS += -ggdb
else
CFLAGS += -O2
CFLAGS += 
AFLAGS +=
endif

ifeq ($(BUILDTYPE), RAM)
#AFLAGS	+=  
#AFLAGS	+= -x assembler-with-cpp -DTEXT_BASE=$(TEXTBASE)
#AFLAGS	+= -x assembler-with-cpp 
else
#AFLAGS	+= 
#AFLAGS	+= -x assembler-with-cpp -DTEXT_BASE=$(TEXTBASE) -D__FLASH_BUILD__
endif

LDFLAGS	+= -L$(KERNEL_ROOT)/lib --start-group $(LDLIBS) --end-group

CPPFLAGS = $(CFLAGS) -fno-rtti

#
# Common rules
#
.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<

.cpp.o:
	$(CXX) -c $(CPPFLAGS) -o $@ $<

.S.o:
	$(CC) -c $(AFLAGS) -o $@ $<
