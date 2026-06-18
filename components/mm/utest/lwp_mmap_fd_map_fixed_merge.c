/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-08-17     Shell        test case for aspace_map(MAP_FIXED)
 */
#include "common.h"
#include "lwp_user_mm.h"
#include "utest_assert.h"
#include <mm_private.h>

#include <rtthread.h>

#define PAGE_SZ     (1 << MM_PAGE_SHIFT)
#define PAGE_COUNT  ('z' - 'a' + 1)
#define FILE_PATH   "/test_mmap"
#define FILE_SZ     (PAGE_COUNT * PAGE_SZ)

static struct rt_lwp *lwp;
static size_t former_vsz;
static size_t former_vcount;
static char page_sz_buf[PAGE_SZ];

static void *ex_start = (void *)0x100000000;
static size_t ex_size = 0x5000;
static long pgoffset = 0;
static size_t ex_prot = PROT_NONE;
static size_t ex_flags = MAP_PRIVATE | MAP_ANONYMOUS;

static char *private0 = (char *)0x100000000;
static char *private1 = (char *)0x100000000 + 0x1000;
static char *private2 = (char *)0x100000000 + 0x2000;
static char *private3 = (char *)0x100000000 + 0x3000;
static char *private4 = (char *)0x100000000 + 0x4000;
static size_t or_size = 0x1000;
static size_t or_prot = PROT_READ | PROT_WRITE;
static size_t or_flags = MAP_ANON | MAP_FIXED;

static long anon_fd = -1;

static int _count_vsz(rt_varea_t varea, void *arg)
{
    rt_base_t *pvsz = arg;
    *pvsz += 1;
    return 0;
}

static rt_base_t count_vcount(rt_aspace_t aspace)
{
    rt_base_t vcount = 0;
    rt_aspace_traversal(aspace, _count_vsz, &vcount);
    return vcount;
}

static rt_err_t _lwp_get_user(struct rt_lwp *lwp, char *vaddr, char *buffer)
{
    rt_varea_t varea = _aspace_bst_search(lwp->aspace, vaddr);
    if (varea && varea->mem_obj && varea->mem_obj->page_read)
    {
        struct rt_aspace_io_msg io_msg;
        rt_mm_io_msg_init(&io_msg, MM_PA_TO_OFF(vaddr), vaddr, buffer);
        varea->mem_obj->page_read(varea, &io_msg);
    }
    return RT_EOK;
}

static void _verify_file_content(struct rt_lwp *lwp, const char *mmap_buf, int ch)
{
    _lwp_get_user(lwp, (char *)mmap_buf, page_sz_buf);
    utest_int_equal(RT_EOK, memtest(page_sz_buf, ch, PAGE_SZ));
}

static void test_mmap_fd_fixed(void)
{
    former_vsz = rt_aspace_count_vsz(lwp->aspace);
    former_vcount = count_vcount(lwp->aspace);

    /* create an existed mapping */
    long temp_fd;
    temp_fd = open(FILE_PATH, O_RDONLY);
    LOG_D("New fd=%ld path=%s", temp_fd, FILE_PATH);
    uassert_true(temp_fd >= 0);
    utest_int_equal(
        lwp_mmap2(lwp, ex_start, ex_size, ex_prot, ex_flags, anon_fd, pgoffset),
        ex_start);
    utest_int_equal(former_vsz + ex_size, rt_aspace_count_vsz(lwp->aspace));
    utest_int_equal(former_vcount + 1, count_vcount(lwp->aspace));
    former_vsz += ex_size;
    former_vcount += 1;
    _verify_file_content(lwp, private0, 0);
    _verify_file_content(lwp, private1, 0);
    _verify_file_content(lwp, private2, 0);
    _verify_file_content(lwp, private3, 0);
    _verify_file_content(lwp, private4, 0);

    /* create an override mapping */
    utest_int_equal(
        lwp_mmap2(lwp, private2, or_size, or_prot, or_flags, temp_fd, 2),
        private2);
    utest_int_equal(former_vsz, rt_aspace_count_vsz(lwp->aspace));
    utest_int_equal(former_vcount + 2, count_vcount(lwp->aspace));
    former_vcount += 2;
    _verify_file_content(lwp, private0, 0);
    _verify_file_content(lwp, private1, 0);
    _verify_file_content(lwp, private2, 'c');
    _verify_file_content(lwp, private3, 0);
    _verify_file_content(lwp, private4, 0);

    /* fix private from left most */
    utest_int_equal(
        lwp_mmap2(lwp, private0, or_size, or_prot, or_flags, temp_fd, 0),
        private0);
    utest_int_equal(former_vsz, rt_aspace_count_vsz(lwp->aspace));
    utest_int_equal(former_vcount + 1, count_vcount(lwp->aspace));
    former_vcount += 1;
    _verify_file_content(lwp, private0, 'a');
    _verify_file_content(lwp, private1, 0);
    _verify_file_content(lwp, private2, 'c');
    _verify_file_content(lwp, private3, 0);
    _verify_file_content(lwp, private4, 0);

    /* fix private from right most */
    utest_int_equal(
        lwp_mmap2(lwp, private4, or_size, or_prot, or_flags, temp_fd, 4),
        private4);
    utest_int_equal(former_vsz, rt_aspace_count_vsz(lwp->aspace));
    utest_int_equal(former_vcount + 1, count_vcount(lwp->aspace));
    former_vcount += 1;
    _verify_file_content(lwp, private0, 'a');
    _verify_file_content(lwp, private1, 0);
    _verify_file_content(lwp, private2, 'c');
    _verify_file_content(lwp, private3, 0);
    _verify_file_content(lwp, private4, 'e');

    /* fix private from left-middle */
    utest_int_equal(
        lwp_mmap2(lwp, private1, or_size, or_prot, or_flags, temp_fd, 1),
        private1);
    rt_aspace_print_all(lwp->aspace);
    utest_int_equal(former_vsz, rt_aspace_count_vsz(lwp->aspace));
    utest_int_equal(former_vcount - 1, count_vcount(lwp->aspace));
    former_vcount -= 1;
    _verify_file_content(lwp, private0, 'a');
    _verify_file_content(lwp, private1, 'b');
    _verify_file_content(lwp, private2, 'c');
    _verify_file_content(lwp, private3, 0);
    _verify_file_content(lwp, private4, 'e');

    /* fix private from right-middle */
    utest_int_equal(
        lwp_mmap2(lwp, private3, or_size, or_prot, or_flags, temp_fd, 3),
        private3);
    utest_int_equal(former_vsz, rt_aspace_count_vsz(lwp->aspace));
    utest_int_equal(former_vcount - 1, count_vcount(lwp->aspace));
    former_vcount -= 1;
    _verify_file_content(lwp, private0, 'a');
    _verify_file_content(lwp, private1, 'b');
    _verify_file_content(lwp, private2, 'c');
    _verify_file_content(lwp, private3, 'd');
    _verify_file_content(lwp, private4, 'e');

    /* close */
    close(temp_fd);
    utest_int_equal(RT_EOK, rt_aspace_unmap_range(lwp->aspace, ex_start, FILE_SZ));
}

static void testcase_main(void)
{
    test_mmap_fd_fixed();
}

static void _setup_file_content(long fd)
{
    char ch = 'a';
    for (size_t i = 0; i < PAGE_COUNT; i++, ch++)
    {
        memset(page_sz_buf, ch, PAGE_SZ);
        write(fd, page_sz_buf, PAGE_SZ);
    }
}

static rt_err_t utest_tc_init(void)
{
    /* setup file */
    long temp_file_des;
    temp_file_des = open(FILE_PATH, O_RDWR | O_CREAT, 0777);
    LOG_D("New fd=%ld path=%s", temp_file_des, FILE_PATH);
    if (temp_file_des < 0)
        return -RT_ERROR;
    _setup_file_content(temp_file_des);
    close(temp_file_des);

    lwp = lwp_create(0);
    if (lwp)
        lwp_user_space_init(lwp, 1);
    else
        return -RT_ENOMEM;
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    lwp_ref_dec(lwp);
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(testcase_main);
}
UTEST_TC_EXPORT(testcase, "testcases.lwp.mman.mmap_fd.map_fixed_merge", utest_tc_init, utest_tc_cleanup, 10);
