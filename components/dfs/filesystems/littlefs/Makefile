TARGET = lfs.a
ifneq ($(wildcard test.c main.c),)
override TARGET = lfs
endif

CC ?= gcc
AR ?= ar
SIZE ?= size

SRC += $(wildcard *.c emubd/*.c)
OBJ := $(SRC:.c=.o)
DEP := $(SRC:.c=.d)
ASM := $(SRC:.c=.s)

TEST := $(patsubst tests/%.sh,%,$(wildcard tests/test_*))

SHELL = /bin/bash -o pipefail

ifdef DEBUG
override CFLAGS += -O0 -g3
else
override CFLAGS += -Os
endif
ifdef WORD
override CFLAGS += -m$(WORD)
endif
override CFLAGS += -I.
override CFLAGS += -std=c99 -Wall -pedantic -Wshadow -Wunused-parameter


all: $(TARGET)

asm: $(ASM)

size: $(OBJ)
	$(SIZE) -t $^

.SUFFIXES:
test: test_format test_dirs test_files test_seek test_truncate \
	test_interspersed test_alloc test_paths test_orphan test_move test_corrupt
	@rm test.c
test_%: tests/test_%.sh

ifdef QUIET
	@./$< | sed -n '/^[-=]/p'
else
	./$<
endif

-include $(DEP)

lfs: $(OBJ)
	$(CC) $(CFLAGS) $^ $(LFLAGS) -o $@

%.a: $(OBJ)
	$(AR) rcs $@ $^

%.o: %.c
	$(CC) -c -MMD $(CFLAGS) $< -o $@

%.s: %.c
	$(CC) -S $(CFLAGS) $< -o $@

clean:
	rm -f $(TARGET)
	rm -f $(OBJ)
	rm -f $(DEP)
	rm -f $(ASM)
