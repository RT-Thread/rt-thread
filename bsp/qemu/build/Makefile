KERNEL_ROOT=.

include $(KERNEL_ROOT)/config.mk

SRC_DIR = src libcpu
MAKE_CMD=

ifeq ($(RT_USING_FINSH), 1)
SRC_DIR += finsh
MAKE_CMD+= RT_USING_FINSH=1
endif

ifeq ($(RT_USING_LWIP), 1)
SRC_DIR += net
MAKE_CMD+= RT_USING_LWIP=1
endif

ifeq ($(RT_USING_EFSL), 1)
SRC_DIR += filesystem
MAKE_CMD+= RT_USING_EFSL=1
endif

ifeq ($(RT_USING_RTGUI), 1)
SRC_DIR += rtgui
MAKE_CMD+= RT_USING_RTGUI=1
endif

ifeq ($(RT_USING_CPLUSPLUS), 1)
SRC_DIR += cplusplus
endif

ifeq ($(RT_USING_NEWLIB), 1)
SRC_DIR += libc
else
ifeq ($(RT_USING_MINILIBC), 1)
SRC_DIR += libc
endif
endif

SRC_DIR += bsp

all:
	for dir in $(SRC_DIR); do				\
		make -C $$dir $(MAKE_CMD);			\
	done

clean :
	for dir in $(SRC_DIR); do				\
		make -C $$dir clean $(MAKE_CMD);	\
	done

test:
	make -C testsuite

docs:
	$(DOXYGEN) Doxyfile

dist-clean: clean
	make -C testsuite clean
