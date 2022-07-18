#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define FILE_TEST_NAME "./rw_file_test.txt"
#define FILE_TEST_LENGTH(x)  sizeof(x)


/* close read write fsync*/
static int open_read_write_fsync_close_entry(void)
{
    __attribute__((unused)) int res = 0;
    int size = 0;
    int fd = 0;
    char s[] = "RT-Thread Programmer!";
    char buffer[30];

    printf("the data is: %s\n", s);

    fd = open(FILE_TEST_NAME, O_RDWR | O_CREAT | O_APPEND);
    if (fd < 0)
    {
        printf("rw_entry open error\n");
        return -1;
    }
    write(fd, s, FILE_TEST_LENGTH(s));

    /* write -> read */
    read(fd,buffer,FILE_TEST_LENGTH(s));
    printf("the read content is %s\n ",buffer);

    /* write -> fsync -> read */
    if(fsync(fd)!=0)
    {
        printf("fync failed\n ");
        return -1;
    }

    read(fd,buffer,FILE_TEST_LENGTH(s));
    printf("the fync read content is %s\n ",buffer);

    close(fd);

    /* close -> open -> read */
    fd = open(FILE_TEST_NAME, O_RDONLY);
    if (fd>= 0)
    {
        size = read(fd, buffer, sizeof(buffer));
        close(fd);
        printf("Read from file test.txt : %s \n", buffer);
        if (size < 0)
            return -1;
    }
    return 0;
}

#include <utest.h>
static void test_open_read_write_fsync_close(void)
{
    uassert_int_equal(open_read_write_fsync_close_entry(), 0);
}
static void testcase(void)
{
    UTEST_UNIT_RUN(test_open_read_write_fsync_close);
}
UTEST_TC_EXPORT(testcase, "posix.unistd_h.open_read_write_fsync_close_tc.c", RT_NULL, RT_NULL, 10);

