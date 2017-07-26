PREFIX 	= /home/zj/risc-v/riscv64-unknown-elf-gcc-20170612-x86_64-linux-centos6/bin/riscv64-unknown-elf-
CC 	= $(PREFIX)gcc
CPP	= $(PREFIX)g++
AS 	= $(PREFIX)gcc
AR 	= $(PREFIX)ar
LINK 	= $(PREFIX)gcc
SIZE 	= $(PREFIX)size
OBJDUMP = $(PREFIX)objdump
OBJCPY 	= $(PREFIX)objcopy
GDB 	= $(PREFIX)gdb
OPENOCD = /home/zj/risc-v/riscv-openocd-20170612-x86_64-linux-centos6/bin/openocd

LIBS    = 
DEVICE 	=  -mcpu=arm926ej-s  -ffunction-sections -fdata-sections
CFLAGS 	= $(DEVICE) $(patsubst %, -I"%", $(CPATH)) 
CXXFLAGS= $(CFLAGS)
AFLAGS 	= $(DEVICE)  -c -x assembler-with-cpp
LFLAGS 	= $(DEVICE)  -Wl,-Map=$(TARGET).map,-cref,-u,Reset_Handler \
	  -T "ld" -nostartfiles $(patsubst %, -l%, $(LIBS)) \
	  $(patsubst %, -L"%", $(LPATH))

CPATH 	= 
LPATH 	= 
################################################################
BUILD   = debug
#BUILD   = release
#BUILD_LIB = yes
BUILD_LIB = no
################################################################

ifeq '$(BUILD)'  'debug'
	CFLAGS +=  -O0 -gdwarf-2
	AFLAGS +=  -gdwarf-2
else
	CFLAGS +=  -O2
endif

ROOT_DIR = $(shell pwd)
SUB_DIR = ${shell ls -l "${ROOT_DIR}" | grep ^d | awk '{if($$9 != "build") print $$9 }'}
################################################################
BUILD_DIR = $(ROOT_DIR)/build/$(BUILD)
BUILD_LIB_DIR =$(LPATH)
################################################################
TARGET = rtthread
export CC CPP AS AR LINK SIZE OBJDUMP OBJCPY DEVICE CFLAGS CXXFLAGS ASFLAGS LFLAGS ROOT_DIR \
       	BUILD BUILD_DIR BUILD_LIB_DIR

SRC_FILE = ${wildcard *.c}
SRC_FILE += ${wildcard *.cpp}
SRC_FILE += ${wildcard *.s}
#SRC_FILE = ${shell ls *.c}
#OBJ_FILE = ${SRC_FILE:.c=.o}
TMP = ${patsubst %.c, %.o, ${SRC_FILE}}
TMP += ${patsubst %.cpp, %.o, ${SRC_FILE}}
TMP += ${patsubst %.s, %.o, ${SRC_FILE}}
OBJ_FILE = $(filter %.o, $(TMP))


# Attempt to create a output directory.
$(shell [ -d ${BUILD_DIR} ]  || mkdir -p ${BUILD_DIR})
# Verify if it was successful.
BUILD_DIR := $(shell cd $(BUILD_DIR) && /bin/pwd)
$(if $(BUILD_DIR),,$(error output directory "$(saved-output)" does not exist))

#all: $(TARGET)
all:
	scons -j4
	#${SIZE}  -d "$(TARGET).axf"
	${OBJDUMP}  -S -D "$(TARGET).axf" > "${TARGET}.s"


$(SUB_DIR):ECHO
	-make -C "${ROOT_DIR}/$@"

%.o:%.cpp
	${CPP} ${CXXFLAGS} -c "$^" -o "${BUILD_DIR}/$@"

%.o:%.c
	${CC} ${CFLAGS}    -c "$^" -o "${BUILD_DIR}/$@"

%.o:%.s
	${AS} ${ASFLAGS}   -c "$^" -o "${BUILD_DIR}/$@"

ifneq "$(BUILD_LIB)" "yes"

$(TARGET): $(SUB_DIR) $(OBJ_FILE)
	cd "${BUILD_DIR}"  && ${CC}  $(filter %.o, $(shell  ls "$(BUILD_DIR)")) ${LFLAGS} -o "$(ROOT_DIR)/$(TARGET)" 
	${OBJCPY} -I elf32-littlearm -O ihex $(TARGET) $(TARGET).hex
	${OBJCPY} -I elf32-littlearm -O binary $(TARGET) $(TARGET).bin
	${SIZE}  -d "$(TARGET)"
	
else

$(TARGET): $(SUB_DIR) $(OBJ_FILE)
	cd "${BUILD_DIR}"  && ${AR} -rc "$(BUILD_LIB_DIR)/lib${TARGET}.a" $(filter %.o, $(shell  ls "$(BUILD_DIR)"))

endif

ECHO:
	@echo ${SUB_DIR}


DEBUG_INTERFACE = jlink
#DEBUG_INTERFACE = stlink-v2
#DEBUG_INTERFACE = ftdi/openjtag

GDB_CMD = -ex "tar ext 127.0.0.1:3333" 
GDB_CMD += -ex "monitor reset halt" 
#GDB_CMD += -ex "monitor step 0x20400000" 
GDB_CMD += --command=.gdbinit

run:
	setsid ${OPENOCD}   > /dev/null 2>&1 &
#	(sleep 1 && echo -e "halt" && sleep 1) | telnet 127.0.0.1 4444
	${GDB} ${TARGET}.axf  ${GDB_CMD}
#	arm-none-eabi-gdb ${TARGET} -ex "tar ext 127.0.0.1:3333" -ex "b main" -ex "lay n" -ex "lay n" -ex "lay n"
	killall -9 openocd

programe:
	setsid ${OPENOCD}   > /dev/null 2>&1 &
	${GDB} ${TARGET}.axf -ex "tar ext 127.0.0.1:3333" -ex "load ${TARGET}.axf"
	killall -9 openocd

clean:
	-cd "${BUILD_DIR}" && rm *
	-rm stm32*

.PHONY: all
