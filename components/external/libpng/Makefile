RTGUI_ROOT=../..

include $(RTGUI_ROOT)/config.mk

SRC	= png.c pngerror.c pnggccrd.c pngget.c pngmem.c pngpread.c pngread.c \
	pngrio.c pngrtran.c pngrutil.c pngset.c pngtrans.c pngvcrd.c pngwio.c \
	pngwrite.c pngwtran.c pngwutil.c
CFLAGS	+= -I../libz

OBJ	= $(SRC:.c=.o) 
LIB	= libpng.a

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
