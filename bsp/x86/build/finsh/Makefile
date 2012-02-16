KERNEL_ROOT=..

include $(KERNEL_ROOT)/config.mk

SRC		= cmd.c shell.c symbol.c finsh_error.c finsh_node.c finsh_token.c \
	finsh_heap.c finsh_ops.c finsh_var.c finsh_compiler.c finsh_init.c\
	finsh_parser.c finsh_vm.c
OBJ		= $(SRC:.c=.o) 

CFLAGS  += -I.


all: $(LIBFINSH)

$(LIBFINSH): $(OBJ)
	$(AR) -r $@ $?
	$(RANLIB) $@

clean :
	$(RM) *.o *~ *.bak
	$(RM) $(LIBFINSH)
	$(RM) .depend

dep : .depend

include .depend

.depend: $(SRC)
	$(CC) $(CFLAGS) -M $^ > $@
