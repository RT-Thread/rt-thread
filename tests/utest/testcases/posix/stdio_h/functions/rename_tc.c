#include <stdio.h>

static int rename_entry(void)
{
    FILE *stream;
    stream = fopen("fopen_file.txt","r");
    if(stream == NULL)
    {
        stream = fopen("fopen_file.txt","w");
        if(stream == NULL)
        {
            return -1;
        }
    }
    fclose(stream);

    rename("fopen_file.txt", "rename_test.txt");
    stream = fopen("rename_test.txt","r");
    if(stream == NULL)
    {
        return -1;
    }
    fclose(stream);
    return 0;
}

#include <utest.h>
static void test_rename(void)
{
    uassert_int_equal(rename_entry(), 0);
}
static void testcase(void)
{
    UTEST_UNIT_RUN(test_rename);
}
UTEST_TC_EXPORT(testcase, "posix.stdio_h.rename.c", RT_NULL, RT_NULL, 10);

