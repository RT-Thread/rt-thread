/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-10-21     Yunlk        the first version
 */

/**
 * Test Case Name: cromfs Directory Name Bound Test (components.dfs.v2.cromfs.dirent_name)
 *
 * Test Objectives:
 * - Verify that dfs_cromfs_getdents() refuses a directory entry whose name_size
 *   does not fit into struct dirent::d_name instead of copying it.
 * - Verify that a well formed image is still listed normally, so the check does
 *   not reject valid entries.
 *
 * Test Scenarios:
 * - A cromfs image is built in RAM and mounted through the data pointer of
 *   dfs_mount(), the way bsp/k230 and bsp/cvitek mount their root filesystem.
 * That keeps the test independent of any block device and of zlib, because
 * listing a directory never decompresses file data.
 * 1. **Control image:** one entry with name_size = 2 ("oo"). getdents must
 *    return a positive byte count and d_name must hold that name.
 * 2. **Oversized name:** one entry with name_size = 512, larger than
 *    DIRENT_NAME_MAX (256). getdents must return -EINVAL and must not write the
 *    name into the caller's buffer.
 *
 * Verification Metrics:
 * - Control: return value > 0, d_namlen == 2, d_name == "oo".
 * - Oversized: return value == -EINVAL, caller buffer left untouched.
 *
 * Dependencies:
 * - Software configuration
 * - `RT_USING_UTEST` and `RT_USING_UTESTCASES` must be enabled.
 * - `RT-Thread Utestcases` -> `Kernel Components` -> `DFS` -> `cromfs dirent
 *   name bound test` must be enabled (`RT_UTEST_DFS_CROMFS`).
 * - `RT_USING_DFS_V2` and `RT_USING_DFS_CROMFS` must be enabled, and a tmpfs is
 *   used as the parent filesystem of the mount point (`RT_USING_DFS_TMPFS`).
 * - Hardware requirements
 * - None (verified on bsp/qemu-vexpress-a9).
 * - Run the test case from the msh prompt:
 * `utest_run components.dfs.v2.cromfs.dirent_name`
 *
 * Expected Results:
 * - The console prints the return value of both listings.
 * - Final Output: `[ PASSED ] [ result ] testcase (components.dfs.v2.cromfs.dirent_name)`
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <dfs.h>
#include <dfs_fs.h>
#include <dfs_file.h>
#include <dirent.h>
#include "utest.h"

#ifdef RT_UTEST_DFS_CROMFS

#define TEST_MNT_ROOT "/"
#define TEST_MNT_OK   "/crom_ok"
#define TEST_MNT_EVIL "/crom_evil"

#define TEST_IMG_SIZE       1024
#define TEST_DIR_POS        256     /* CROMFS_PATITION_HEAD_SIZE */
#define TEST_DIRENT_HDR     16      /* sizeof of the on-image dirent header */
#define TEST_ALIGN          16
#define TEST_NAME_MAX_ENTRY 512     /* deliberately larger than DIRENT_NAME_MAX */
#define TEST_MOUNT_FAILED   (-0x7fffffff)

/* mirrors partition_head_data */
typedef struct
{
    rt_uint8_t magic[8];
    rt_uint32_t version;
    rt_uint32_t partition_attr;
    rt_uint32_t partition_size;
    rt_uint32_t root_dir_pos;
    rt_uint32_t root_dir_size;
} test_partition_head;

/* mirrors cromfs_dirent without the trailing name */
typedef struct
{
    rt_uint16_t attr;
    rt_uint16_t name_size;
    rt_uint32_t file_size;
    rt_uint32_t file_origin_size;
    rt_uint32_t partition_pos;
} test_dirent_head;

static rt_uint8_t _image[TEST_IMG_SIZE];
static rt_bool_t _root_ready;

#define TEST_ALIGN_UP(x) (((x) + TEST_ALIGN - 1) & ~(TEST_ALIGN - 1))

static void _build_image(rt_uint16_t name_size, char name_byte)
{
    test_partition_head *head;
    test_dirent_head *entry;

    rt_memset(_image, 0, sizeof(_image));

    head = (test_partition_head *)_image;
    rt_memcpy(head->magic, "CROMFSMG", 8);
    head->version = 0;
    head->partition_attr = 0;
    head->partition_size = sizeof(_image);
    head->root_dir_pos = TEST_DIR_POS;
    head->root_dir_size = TEST_DIRENT_HDR + TEST_ALIGN_UP(name_size);

    entry = (test_dirent_head *)(_image + TEST_DIR_POS);
    entry->attr = 0;     /* CROMFS_DIRENT_ATTR_FILE */
    entry->name_size = name_size;
    entry->file_size = 0;
    entry->partition_pos = 0;

    rt_memset(_image + TEST_DIR_POS + TEST_DIRENT_HDR, name_byte, name_size);
}

/* mount the image at the given mount point and list its root directory once */
static int _list_image(const char *mnt_point, struct dirent *dent, rt_size_t dent_size)
{
    struct dfs_file file;
    int ret;

    ret = dfs_mount(RT_NULL, mnt_point, "crom", 0, _image);
    if (ret != 0)
    {
        LOG_E("mount of %s failed: %d", mnt_point, ret);
        return TEST_MOUNT_FAILED;
    }

    rt_memset(&file, 0, sizeof(file));
    ret = dfs_file_open(&file, mnt_point, O_DIRECTORY, 0);
    if (ret == 0)
    {
        ret = dfs_file_getdents(&file, dent, dent_size);
        dfs_file_close(&file);
    }
    else
    {
        LOG_E("open of %s failed: %d", mnt_point, ret);
    }

    return ret;
}

static void cromfs_dirent_name(void)
{
    struct dirent dent;
    int ret;

    /* a well formed entry must still be listed */
    _build_image(2, 'o');
    rt_memset(&dent, 0, sizeof(dent));
    ret = _list_image(TEST_MNT_OK, &dent, sizeof(dent));
    LOG_I("control image  -> ret=%d, d_namlen=%d, name=\"%s\" (expect >0 / 2 / oo)",
          ret, (int)dent.d_namlen, dent.d_name);
    uassert_true(ret > 0);
    uassert_int_equal(dent.d_namlen, 2);

    /* a name larger than d_name must be rejected, not copied */
    _build_image(TEST_NAME_MAX_ENTRY, 'A');
    rt_memset(&dent, 0, sizeof(dent));
    ret = _list_image(TEST_MNT_EVIL, &dent, sizeof(dent));
    LOG_I("oversized name -> ret=%d, d_namlen=%d (expect %d / 0)",
          ret, (int)dent.d_namlen, -EINVAL);
    uassert_true(ret != TEST_MOUNT_FAILED);
    uassert_int_equal(ret, -EINVAL);
    uassert_int_equal(dent.d_namlen, 0);
}

static rt_err_t utest_tc_init(void)
{
    /* the mount point has to exist in some parent filesystem */
    if (!_root_ready)
    {
        if (dfs_mount(RT_NULL, TEST_MNT_ROOT, "tmp", 0, RT_NULL) == 0)
        {
            _root_ready = RT_TRUE;
        }
        else
        {
            /* someone else already provided a root filesystem */
            _root_ready = RT_TRUE;
        }
    }

    mkdir(TEST_MNT_OK, 0777);
    mkdir(TEST_MNT_EVIL, 0777);

    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    dfs_unmount(TEST_MNT_OK);
    dfs_unmount(TEST_MNT_EVIL);

    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(cromfs_dirent_name);
}
UTEST_TC_EXPORT(testcase, "components.dfs.v2.cromfs.dirent_name",
                utest_tc_init, utest_tc_cleanup, 10);

#endif /* RT_UTEST_DFS_CROMFS */
