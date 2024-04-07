#include <unistd.h>
#include <fcntl.h>

#define TRUN_SIZE 3
#define TRUNCATE_TEST_NAME "./ftruncate_to3"

static int ftruncate_entry(void)
{
    int res = 0;
    int fd = 0;

    fd = open(TRUNCATE_TEST_NAME, O_RDWR | O_CREAT | O_APPEND);
    if (fd < 0)
    {
        return -1;
    }

    write(fd, "hello", 6);
    /* TODO */
    res = ftruncate(fd, TRUN_SIZE);
    close(fd);
    return res;
}

#include <utest.h>

static void test_ftruncate(void)
{
    uassert_int_equal(ftruncate_entry(), 0);
}
static void testcase(void)
{
    UTEST_UNIT_RUN(test_ftruncate);
}
UTEST_TC_EXPORT(testcase, "posix.unistd_h.ftruncate_tc.c", RT_NULL, RT_NULL, 10);

