/*
 * ===========================================================================================
 *
 *       Filename:  hal_sem.c
 *
 *    Description:  memory allocator impl for hal driver.
 *
 *        Version:  Melis3.0
 *         Create:  2019-11-27 14:20:53
 *       Revision:  none
 *       Compiler:  GCC:version 7.2.1 20170904 (release),ARM/embedded-7-branch revision 255204
 *
 *         Author:  caozilong@allwinnertech.com
 *   Organization:  BU1-PSW
 *  Last Modified:  2020-07-28 08:49:06
 *
 * ===========================================================================================
 */

#include <hal_mem.h>
#include <rtdef.h>
#include <log.h>

#include <rtthread.h>

void *hal_malloc(uint32_t size)
{
    return rt_malloc(size);
}

void hal_free(void *p)
{
    rt_free(p);
}

void *hal_malloc_align(uint32_t size, int align)
{
    return rt_malloc_align(size, align);
}

void hal_free_align(void *p)
{
    rt_free_align(p);
}

