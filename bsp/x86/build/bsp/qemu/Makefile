KERNEL_ROOT=../..

include $(KERNEL_ROOT)/config.mk

SRC	= board.c startup.c keyboard.c console.c serial.c
APP	= application.o
OBJ	= $(SRC:.c=.o)
BIN	= rtthread-$(BOARD)
IMG	= $(KERNEL_ROOT)/lib/$(BIN).img

#LFALGS	= -nostdlib -Bstatic -T $(LDSCRIPT) -Ttext $(TEXTBASE)
LFALGS	= -nostdlib -Bstatic -T $(LDSCRIPT)
CFLAGS	+= -I$(KERNEL_ROOT)/libcpu/$(ARCH)/include 

all: $(BIN) $(LIBBSP)

$(IMG): $(BIN) $(KERNEL_ROOT)/lib/boot
	dd if=/dev/zero of=$(IMG)~ count=1000 2>/dev/null
	dd if=$(KERNEL_ROOT)/lib/boot of=$(IMG)~ conv=notrunc 2>/dev/null
	dd if=$(BIN) of=$(IMG)~ seek=1 conv=notrunc 2>/dev/null

$(LIBBSP): $(OBJ)
	$(AR) r $@ $?
	$(RANLIB) $@

$(BIN): $(OBJ) $(APP) $(LIBFINSH) $(LIBCPU) $(KERNEL) 
	$(LD) $(LFALGS) $(STARTOBJ) $(OBJ) $(APP) $(LIBFINSH) $(KERNEL) $(LIBCPU) -o $(BIN).elf
	$(SIZE) $(BIN).elf

clean :
	$(RM) $(BIN).elf *.o *~ *.bak *.bin $(LIBBSP)
	$(RM) .depend

dep : .depend

include .depend

.depend: $(SRC)
	$(CC) $(CFLAGS) -M $^ > $@
