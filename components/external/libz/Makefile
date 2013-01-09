RTGUI_ROOT=../..

include $(RTGUI_ROOT)/config.mk

SRC	= adler32.c compress.c crc32.c deflate.c gzio.c infback.c inffast.c \
	inflate.c inftrees.c trees.c uncompr.c zutil.c

OBJ	= $(SRC:.c=.o) 
LIB	= libz.a

all: $(LIB)

$(LIB): $(OBJ)
	$(AR) r $@ $?
	$(RANLIB) $@

clean :
	$(RM) *.o *~ *.bak
	$(RM) $(LIB)
	$(RM) .depend

dep : .depend

include .depend

.depend: $(SRC)
	$(CC) $(CFLAGS) -M $^ > $@
