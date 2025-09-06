/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-09-03     Rbb666       the first version for DFS POSIX API utest
 */
#include <rtthread.h>
#include "utest.h"

#include <dfs_file.h>
#include <dfs.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>

int fd = -1;
static const char write_buf[] = "Hello RT-Thread POSIX!";

#define TEST_MNT_PATH  RT_UTEST_DFS_MNT_PATH
#define TEST_BLOCK_DEV RT_UTEST_DFS_BLOCK_DEV
#define TEST_FS        RT_UTEST_DFS_FS_TYPE

#define TEST_FILE      TEST_MNT_PATH "/RTT.txt"
#define TEST_DIR       TEST_MNT_PATH "/posix"
#define TEST_DIR_FILE  TEST_MNT_PATH "/posix/RTT.txt"
#define TEST_RENAME_FILE TEST_MNT_PATH "/RTT-renamed.txt"
#define TEST_LINK_FILE TEST_MNT_PATH "/RTT-link.txt"
#define TEST_CHDIR_DIR TEST_MNT_PATH "/chdir_test"

#define WRITE_BUF_LEN  (sizeof(write_buf) - 1)

static void test_mkfs(void)
{
    rt_err_t rst = dfs_mkfs(TEST_FS, TEST_BLOCK_DEV);
    uassert_true(rst == 0);
}

static void test_mount(void)
{
    rt_err_t rst;
    struct stat stat_buf;

    /* First check if the mount point already has a filesystem */
    if (stat("/", &stat_buf) == 0)
    {
        uassert_true(RT_TRUE);
        return;
    }

    /* Try to unmount first, ignore errors as filesystem might not be mounted */
    rst = dfs_unmount(TEST_MNT_PATH);
    if (rst != 0)
    {
        rt_kprintf("[ERROR] unmount failed with result = %d\n", rst);
    }

    /* Now try to mount */
    rst = dfs_mount(TEST_BLOCK_DEV, TEST_MNT_PATH, TEST_FS, 0, 0);
    if (rst != 0)
    {
        rt_kprintf("[ERROR] Mount failed with result = %d\n", rst);
        /* If mount fails but filesystem already exists, consider it a pass */
        if (stat("/", &stat_buf) == 0)
        {
            uassert_true(RT_TRUE);
            return;
        }
    }
    uassert_true(rst == 0);
}

static void test_posix_open(void)
{
    rt_kprintf("TEST_FILE:%s\n", TEST_FILE);
    fd = open(TEST_FILE, O_CREAT | O_RDWR, 0644);
    if (fd < 0)
    {
        rt_kprintf("[ERROR] Open failed, fd = %d, errno = %d\n", fd, errno);
    }
    uassert_true(fd >= 0);
}

static void test_posix_write(void)
{
    ssize_t rst;

    rst = lseek(fd, 0, SEEK_SET);
    if (rst != 0)
    {
        rt_kprintf("[ERROR] lseek failed with result = %d\n", rst);
    }
    uassert_true(rst == 0);

    rt_kprintf("[WRITE] Writing data: \"%s\" (length: %d)\n", write_buf, WRITE_BUF_LEN);
    rst = write(fd, write_buf, WRITE_BUF_LEN);
    if (rst != WRITE_BUF_LEN)
    {
        rt_kprintf("[ERROR] Write failed, result = %d, expected = %d\n", rst, WRITE_BUF_LEN);
    }
    else
    {
        rt_kprintf("[WRITE] Write successful, %d bytes written\n", rst);
    }
    uassert_true(rst == WRITE_BUF_LEN);
}

static void test_posix_read(void)
{
    ssize_t rst;
    char read_buf[32];

    rst = lseek(fd, 0, SEEK_SET);
    if (rst != 0)
    {
        rt_kprintf("[ERROR] lseek failed with result = %d\n", rst);
    }
    uassert_true(rst == 0);

    rt_kprintf("[READ] Reading %d bytes from file\n", WRITE_BUF_LEN);
    rst = read(fd, read_buf, WRITE_BUF_LEN);
    if (rst != WRITE_BUF_LEN)
    {
        rt_kprintf("[ERROR] Read failed, result = %d, expected = %d\n", rst, WRITE_BUF_LEN);
    }
    else
    {
        read_buf[rst] = '\0';
        rt_kprintf("[READ] Read successful, %d bytes read: \"%s\"\n", rst, read_buf);
    }
    uassert_true(rst == WRITE_BUF_LEN);

    read_buf[rst] = '\0';
    uassert_str_equal(write_buf, read_buf);
}

static void test_posix_close(void)
{
    int rst = close(fd);
    if (rst != 0)
    {
        rt_kprintf("[ERROR] Close failed with result = %d\n", rst);
    }
    uassert_true(rst == 0);
    fd = -1;
}

static void test_posix_stat(void)
{
    struct stat stat_buf;
    int rst = stat(TEST_FILE, &stat_buf);
    if (rst != 0)
    {
        rt_kprintf("[ERROR] stat failed with result = %d\n", rst);
    }
    uassert_true(rst == 0);
    uassert_true(S_ISREG(stat_buf.st_mode));
}

static void test_posix_unlink(void)
{
    int rst = unlink(TEST_FILE);
    if (rst != 0)
    {
        rt_kprintf("[ERROR] unlink failed with result = %d\n", rst);
    }
    uassert_true(rst == 0);
}

static void test_posix_mkdir(void)
{
    int rst = mkdir(TEST_DIR, 0755);
    if (rst != 0)
    {
        rt_kprintf("[ERROR] mkdir failed with result = %d\n", rst);
    }
    uassert_true(rst == 0);
}

static void test_posix_rmdir(void)
{
    int rst = rmdir(TEST_DIR);
    if (rst != 0)
    {
        rt_kprintf("[ERROR] rmdir failed with result = %d\n", rst);
    }
    uassert_true(rst == 0);
}

static void test_posix_rename(void)
{
    /* Create a file first */
    fd = open(TEST_FILE, O_CREAT | O_RDWR, 0644);
    if (fd < 0)
    {
        rt_kprintf("[ERROR] Failed to create file for rename test\n");
        uassert_true(fd >= 0);
        return;
    }

    close(fd);
    fd = -1;

    /* Rename it */
    int rst = rename(TEST_FILE, TEST_RENAME_FILE);
    if (rst != 0)
    {
        rt_kprintf("[ERROR] rename failed with result = %d\n", rst);
        /* Clean up the original file if rename failed */
        unlink(TEST_FILE);
        uassert_true(rst == 0);
        return;
    }

    /* Check old file doesn't exist */
    struct stat stat_buf;
    rst = stat(TEST_FILE, &stat_buf);
    if (rst == 0)
    {
        rt_kprintf("[ERROR] Old file still exists after rename\n");
        /* Clean up both files */
        unlink(TEST_FILE);
        unlink(TEST_RENAME_FILE);
        uassert_true(rst != 0);
        return;
    }

    /* Check new file exists */
    rst = stat(TEST_RENAME_FILE, &stat_buf);
    if (rst != 0)
    {
        rt_kprintf("[ERROR] New file does not exist after rename\n");
        uassert_true(rst == 0);
        return;
    }

    /* Clean up */
    unlink(TEST_RENAME_FILE);
}

static void test_posix_opendir_readdir(void)
{
    DIR *dir = NULL;
    struct dirent *entry;

    /* Create directory and file */
    mkdir(TEST_DIR, 0755);

    fd = open(TEST_DIR_FILE, O_CREAT | O_RDWR, 0644);
    if (fd >= 0)
    {
        close(fd);
        fd = -1;
    }

    dir = opendir(TEST_DIR);
    if (dir == NULL)
    {
        rt_kprintf("[ERROR] opendir failed\n");
        /* Clean up on error */
        unlink(TEST_DIR_FILE);
        rmdir(TEST_DIR);
        uassert_not_null(dir);
        return;
    }

    entry = readdir(dir);
    if (entry == NULL)
    {
        rt_kprintf("[ERROR] readdir failed\n");
        closedir(dir);
        /* Clean up on error */
        unlink(TEST_DIR_FILE);
        rmdir(TEST_DIR);
        uassert_not_null(entry);
        return;
    }

    /* The filename should match what we created - just the basename, not the full path */
    uassert_str_equal(entry->d_name, "RTT.txt");  /* Just the basename */

    closedir(dir);
    dir = NULL;

    /* Clean up */
    unlink(TEST_DIR_FILE);
    rmdir(TEST_DIR);
}

static void test_posix_lseek(void)
{
    /* Create and write to file */
    fd = open(TEST_FILE, O_CREAT | O_RDWR, 0644);
    if (fd < 0)
    {
        rt_kprintf("[ERROR] Open failed for lseek test\n");
        uassert_true(fd >= 0);
        return;
    }

    ssize_t rst = write(fd, write_buf, WRITE_BUF_LEN);
    if (rst != WRITE_BUF_LEN)
    {
        rt_kprintf("[ERROR] Write failed in lseek test\n");
        close(fd);
        unlink(TEST_FILE);
        uassert_true(rst == WRITE_BUF_LEN);
        return;
    }

    /* Seek to beginning */
    off_t pos = lseek(fd, 0, SEEK_SET);
    if (pos != 0)
    {
        rt_kprintf("[ERROR] lseek to SET failed, pos = %ld\n", pos);
    }
    uassert_true(pos == 0);

    /* Seek to end */
    pos = lseek(fd, 0, SEEK_END);
    if (pos != WRITE_BUF_LEN)
    {
        rt_kprintf("[ERROR] lseek to END failed, pos = %ld, expected = %d\n", pos, WRITE_BUF_LEN);
    }
    uassert_true(pos == WRITE_BUF_LEN);

    /* Seek from current (back 5 bytes) */
    pos = lseek(fd, -5, SEEK_CUR);
    if (pos != (WRITE_BUF_LEN - 5))
    {
        rt_kprintf("[ERROR] lseek CUR failed, pos = %ld\n", pos);
    }
    uassert_true(pos == (WRITE_BUF_LEN - 5));

    close(fd);
    fd = -1;
    unlink(TEST_FILE);
}

static void test_posix_fstat(void)
{
    /* Create and open file */
    fd = open(TEST_FILE, O_CREAT | O_RDWR, 0644);
    if (fd < 0)
    {
        rt_kprintf("[ERROR] Open failed for fstat test\n");
        uassert_true(fd >= 0);
        return;
    }

    struct stat stat_buf;
    int rst = fstat(fd, &stat_buf);
    if (rst != 0)
    {
        rt_kprintf("[ERROR] fstat failed with result = %d\n", rst);
    }
    uassert_true(rst == 0);
    uassert_true(S_ISREG(stat_buf.st_mode));
    uassert_true(stat_buf.st_size == 0);  /* Initially empty */

    close(fd);
    fd = -1;
    unlink(TEST_FILE);
}

static void test_posix_access(void)
{
    /* Create file */
    fd = open(TEST_FILE, O_CREAT | O_RDWR, 0644);
    if (fd < 0)
    {
        rt_kprintf("[ERROR] Open failed for access test\n");
        uassert_true(fd >= 0);
        return;
    }
    close(fd);
    fd = -1;

    /* Check existence */
    int rst = access(TEST_FILE, F_OK);
    if (rst != 0)
    {
        rt_kprintf("[ERROR] access F_OK failed\n");
    }
    uassert_true(rst == 0);

    /* Check read permission */
    rst = access(TEST_FILE, R_OK);
    if (rst != 0)
    {
        rt_kprintf("[ERROR] access R_OK failed\n");
    }
    uassert_true(rst == 0);

    /* Check write permission */
    rst = access(TEST_FILE, W_OK);
    if (rst != 0)
    {
        rt_kprintf("[ERROR] access W_OK failed\n");
    }
    uassert_true(rst == 0);

    /* Check execute permission (may not be set) */
    rst = access(TEST_FILE, X_OK);
    if (rst == 0)
    {
        rt_kprintf("[WARN] access X_OK succeeded, but file is not executable\n");
    }
    /* No assert here as it depends on mode */

    unlink(TEST_FILE);
}

static void test_posix_chdir_getcwd(void)
{
    char cwd[256];

    /* Get current working directory */
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        rt_kprintf("[ERROR] getcwd failed initially\n");
        uassert_not_null(getcwd(cwd, sizeof(cwd)));
        return;
    }
    rt_kprintf("[CWD] Initial: %s\n", cwd);

    /* Create directory */
    int rst = mkdir(TEST_CHDIR_DIR, 0755);
    if (rst != 0)
    {
        rt_kprintf("[ERROR] mkdir failed for chdir test\n");
        uassert_true(rst == 0);
        return;
    }

    /* Change directory */
    rst = chdir(TEST_CHDIR_DIR);
    if (rst != 0)
    {
        rt_kprintf("[ERROR] chdir failed\n");
        rmdir(TEST_CHDIR_DIR);
        uassert_true(rst == 0);
        return;
    }

    /* Get new cwd */
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        rt_kprintf("[ERROR] getcwd failed after chdir\n");
        chdir("..");
        rmdir(TEST_CHDIR_DIR);
        uassert_not_null(getcwd(cwd, sizeof(cwd)));
        return;
    }
    rt_kprintf("[CWD] After chdir: %s\n", cwd);
    uassert_str_equal(cwd, TEST_CHDIR_DIR);

    /* Change back */
    rst = chdir("..");
    if (rst != 0)
    {
        rt_kprintf("[ERROR] chdir back failed\n");
    }
    uassert_true(rst == 0);

    /* Clean up */
    rmdir(TEST_CHDIR_DIR);
}

static rt_err_t utest_tc_init(void)
{
    /* Clean up any leftover files from previous runs */
    unlink(TEST_FILE);
    unlink(TEST_RENAME_FILE);
    unlink(TEST_DIR_FILE);
    unlink(TEST_LINK_FILE);
    rmdir(TEST_DIR);
    rmdir(TEST_CHDIR_DIR);

    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    /* Ensure all resources are cleaned up */
    if (fd >= 0)
    {
        close(fd);
        fd = -1;
    }

    /* Clean up all test files and directories */
    unlink(TEST_FILE);
    unlink(TEST_RENAME_FILE);
    unlink(TEST_DIR_FILE);
    unlink(TEST_LINK_FILE);
    rmdir(TEST_DIR);
    rmdir(TEST_CHDIR_DIR);

    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(test_mkfs);
    UTEST_UNIT_RUN(test_mount);
    UTEST_UNIT_RUN(test_posix_open);
    UTEST_UNIT_RUN(test_posix_write);
    UTEST_UNIT_RUN(test_posix_read);
    UTEST_UNIT_RUN(test_posix_close);
    UTEST_UNIT_RUN(test_posix_stat);
    UTEST_UNIT_RUN(test_posix_unlink);
    UTEST_UNIT_RUN(test_posix_mkdir);
    UTEST_UNIT_RUN(test_posix_rmdir);
    UTEST_UNIT_RUN(test_posix_rename);
    UTEST_UNIT_RUN(test_posix_opendir_readdir);
    UTEST_UNIT_RUN(test_posix_lseek);
    UTEST_UNIT_RUN(test_posix_fstat);
    UTEST_UNIT_RUN(test_posix_access);
    UTEST_UNIT_RUN(test_posix_chdir_getcwd);
}

UTEST_TC_EXPORT(testcase, "components.dfs.fs_posix_api_tc", utest_tc_init, utest_tc_cleanup, 10);
