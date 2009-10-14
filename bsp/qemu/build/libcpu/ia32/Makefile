KERNEL_ROOT=../..

include $(KERNEL_ROOT)/config.mk

SRC		= interrupt.c trap.c stack.c backtrace.c showmem.c __udivsi3.c __umodsi3.c
CPU_OBJ	= $(SRC:.c=.o) context.o trapisr.o hdisr.o

#AFLAGS	+= -DTEXT_BASE=$(TEXTBASE) -I$(KERNEL_ROOT)/libcpu/$(ARCH)/include
AFLAGS	+= -I$(KERNEL_ROOT)/libcpu/$(ARCH)/include
CFLAGS	+= -I$(KERNEL_ROOT)/libcpu/$(ARCH)/include

all: $(LIBCPU) $(STARTOBJ)

$(STARTOBJ): start.S
#	$(CC) $(AFLAGS) -c start.S -ggdb -o $(STARTOBJ)
	$(CC) $(AFLAGS) -c start.S -o $(STARTOBJ)

$(LIBCPU): $(CPU_OBJ)
	$(AR) r $(LIBCPU) $?
	$(RANLIB) $(LIBCPU)

clean :
	$(RM) *.o *~ *.bak
	$(RM) $(LIBCPU)
	$(RM) $(STARTOBJ)
	$(RM) .depend

dep : .depend

include .depend

.depend: $(SRC)
	$(CC) $(CFLAGS) -M $^ > $@
