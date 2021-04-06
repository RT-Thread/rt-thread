#ifndef __CI_TESTS_H__
#define __CI_TESTS_H__

#include "board_mock.h"

// board mock tests
void test_stdoutSpy();

// memorry tests
void test_memory_setup(void);
void test_memory_malloc_right(void);
void test_memory_malloc_too_big(void);
void test_memory_malloc_zero(void);
void test_memory_malloc_not_a_size(void);

#endif