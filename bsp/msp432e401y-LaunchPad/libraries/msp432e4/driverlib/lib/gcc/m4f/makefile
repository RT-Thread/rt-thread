SDK_INSTALL_DIR ?= $(abspath ../../../../../../../..)

include $(SDK_INSTALL_DIR)/imports.mak

CC = "$(GCC_ARMCOMPILER)/bin/arm-none-eabi-gcc"
AR = "$(GCC_ARMCOMPILER)/bin/arm-none-eabi-ar"

NAME = msp432e4_driverlib

OBJ_DIR = ../../../obj/gcc/m4f/msp432e4_driverlib
SRC_DIR = ../../..

CFLAGS = -I$(GCC_ARMCOMPILER)/arm-none-eabi/include -I$(SDK_INSTALL_DIR)/source/third_party/CMSIS/Include -I$(SDK_INSTALL_DIR)/source -mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DMSP432E411Y -Wall -ffunction-sections -fdata-sections -std=c99 -c -g -gstrict-dwarf
AFLAGS = -cr --target=elf32-little
ASMFLAGS = -I$(GCC_ARMCOMPILER)/arm-none-eabi/include 

OBJECTS = $(OBJ_DIR)/adc.o $(OBJ_DIR)/aes.o $(OBJ_DIR)/can.o $(OBJ_DIR)/comp.o $(OBJ_DIR)/cpu.o $(OBJ_DIR)/crc.o $(OBJ_DIR)/des.o $(OBJ_DIR)/eeprom.o $(OBJ_DIR)/emac.o $(OBJ_DIR)/epi.o $(OBJ_DIR)/flash.o $(OBJ_DIR)/fpu.o $(OBJ_DIR)/gpio.o $(OBJ_DIR)/hibernate.o $(OBJ_DIR)/i2c.o $(OBJ_DIR)/interrupt.o $(OBJ_DIR)/lcd.o $(OBJ_DIR)/mpu.o $(OBJ_DIR)/onewire.o $(OBJ_DIR)/pwm.o $(OBJ_DIR)/qei.o $(OBJ_DIR)/shamd5.o $(OBJ_DIR)/ssi.o $(OBJ_DIR)/sw_crc.o $(OBJ_DIR)/sysctl.o $(OBJ_DIR)/sysexc.o $(OBJ_DIR)/systick.o $(OBJ_DIR)/timer.o $(OBJ_DIR)/uart.o $(OBJ_DIR)/udma.o $(OBJ_DIR)/usb.o $(OBJ_DIR)/watchdog.o

all: $(NAME).a

$(NAME).a: $(OBJECTS)
	@ echo Archiving $@
	@ $(AR) $(AFLAGS) $@ $^

$(OBJ_DIR)/adc.o: $(SRC_DIR)/adc.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/aes.o: $(SRC_DIR)/aes.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/can.o: $(SRC_DIR)/can.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/comp.o: $(SRC_DIR)/comp.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/cpu.o: $(SRC_DIR)/cpu.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/crc.o: $(SRC_DIR)/crc.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/des.o: $(SRC_DIR)/des.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/eeprom.o: $(SRC_DIR)/eeprom.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/emac.o: $(SRC_DIR)/emac.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/epi.o: $(SRC_DIR)/epi.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/flash.o: $(SRC_DIR)/flash.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/fpu.o: $(SRC_DIR)/fpu.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/gpio.o: $(SRC_DIR)/gpio.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/hibernate.o: $(SRC_DIR)/hibernate.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/i2c.o: $(SRC_DIR)/i2c.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/interrupt.o: $(SRC_DIR)/interrupt.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/lcd.o: $(SRC_DIR)/lcd.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/mpu.o: $(SRC_DIR)/mpu.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/onewire.o: $(SRC_DIR)/onewire.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/pwm.o: $(SRC_DIR)/pwm.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/qei.o: $(SRC_DIR)/qei.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/shamd5.o: $(SRC_DIR)/shamd5.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/ssi.o: $(SRC_DIR)/ssi.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/sw_crc.o: $(SRC_DIR)/sw_crc.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/sysctl.o: $(SRC_DIR)/sysctl.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/sysexc.o: $(SRC_DIR)/sysexc.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/systick.o: $(SRC_DIR)/systick.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/timer.o: $(SRC_DIR)/timer.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/uart.o: $(SRC_DIR)/uart.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/udma.o: $(SRC_DIR)/udma.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/usb.o: $(SRC_DIR)/usb.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/watchdog.o: $(SRC_DIR)/watchdog.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

clean:
	@ echo Cleaning...
	@ $(RM) $(OBJECTS) > $(DEVNULL) 2>&1
	@ $(RM) $(NAME).a > $(DEVNULL) 2>&1
