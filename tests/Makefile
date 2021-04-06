# make file for ci test

ifeq ($(OS), Windows_NT)
	EXECUTABLE ?= unit-tests.exe
else
	EXECUTABLE ?= unit-tests
endif

# add rtt source code
FILES = $(wildcard ../src/*.c)

# add Unity as test frame
FILES += $(wildcard Unity-2.5.2/src/*.c)

# add test codes
FILES += $(wildcard *.c)

# include paths
INCLUDES := -I ../include -I ./Unity-2.5.2/src -I .

OBJS := $(patsubst %.c, %.o, $(FILES))

JCOVS := ../src/*.gcov
JCOVS += ../src/*.gcda
JCOVS += ../src/*.gcno

JCOVS += Unity-2.5.2/src/*.gcov
JCOVS += Unity-2.5.2/src/*.gcda
JCOVS += Unity-2.5.2/src/*.gcno

JCOVS += *.gcov
JCOVS += *.gcda
JCOVS += *.gcno
JCOVS += *.html

.PHONY: build
build: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	@echo "build target"
	@gcc $^ -o $@ -Wl,-Map=$@.map -lgcov

%.o:%.c
	@echo 'compile $<'
	@gcc -c $< -o $@ $(INCLUDES) -fprofile-arcs -ftest-coverage

.PHONY: clean
clean:
	rm -f $(OBJS) $(EXECUTABLE) $(JCOVS)

.PHONY: gcov
gcov:
	@echo "generating base coverage ..."
	gcov -f ../src/*.c

.PHONY: gcovr
gcovr:
	gcovr -r ../src --html --html-details -o coverage.html

.PHONY: test
test: build
	./$(EXECUTABLE)
