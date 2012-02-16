KERNEL_ROOT=..

include $(KERNEL_ROOT)/config.mk

SRC	= kservice.c clock.c object.c ipc.c timer.c irq.c scheduler.c \
	thread.c idle.c mempool.c mem.c slab.c device.c
OBJ	= $(SRC:.c=.o)

all: $(KERNEL)

$(KERNEL): $(OBJ)
	$(AR) r $@ $?
	$(RANLIB) $@

clean :
	$(RM) *.o *~ *.bak
	$(RM) $(KERNEL)
	$(RM) .depend

dep : .depend

include .depend

.depend: $(SRC)
	$(CC) $(CFLAGS) -M $^ > $@
