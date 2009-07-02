#include <rtthread.h>

#include <stdio.h>
#include <string.h>

/* 
 * Only need when RealView MDK is used.
 */
void *rt_memset(void * s, int c, rt_ubase_t count)
{
	return memset(s, c, count);
}

void *rt_memcpy(void * dst, const void *src, rt_ubase_t count)
{
	return memcpy(dst, src, count);
}

rt_ubase_t rt_strncmp(const char * cs, const char * ct, rt_ubase_t count)
{
	return strncmp(cs, ct, count);
}

/**
 * This function will show the version of rt-thread rtos
 */
void rt_show_version()
{
	rt_kprintf(" \\ | /\n");
	rt_kprintf("- RT - Thread Operating System\n");
	rt_kprintf(" / | \\ 0.%d.%d build %s\n", RT_VERSION, RT_SUBVERSION, __DATE__);
	rt_kprintf(" 2006 - 2009 Copyright by rt-thread team\n");
}

void rt_kprintf(const char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
}
