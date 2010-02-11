/*
 * File      : readwrite.c
 * This file is part of RT-TestCase in RT-Thread RTOS
 * COPYRIGHT (C) 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-02-10     Bernard      first version
 */
#include <rtthread.h>
#include <dfs_posix.h>

#define TEST_FN		"/test.dat"

static char test_data[120], buffer[120];

/* 文件读写测试 */
void readwrite(const char* filename)
{
	int fd;
	int index, length;

	/* 只写 & 创建 打开 */
	fd = open(TEST_FN, O_WRONLY | O_CREAT | O_TRUNC, 0);
	if (fd < 0)
	{
		rt_kprintf("open file for write failed\n");
		return;
	}

	/* 准备写入数据 */
	for (index = 0; index < sizeof(test_data); index ++)
	{
		test_data[index] = index + 27;
	}

	/* 写入数据 */
	length = write(fd, test_data, sizeof(test_data));
	if (length != sizeof(test_data))
	{
		rt_kprintf("write data failed\n");
		close(fd);
		return;
	}

	/* 关闭文件 */
	close(fd);

	/* 只写并在末尾添加打开 */
	fd = open(TEST_FN, O_WRONLY | O_CREAT | O_APPEND, 0);
	if (fd < 0)
	{
		rt_kprintf("open file for append write failed\n");
		return;
	}

	length = write(fd, test_data, sizeof(test_data));
	if (length != sizeof(test_data))
	{
		rt_kprintf("append write data failed\n");
		close(fd);
		return;
	}
	/* 关闭文件 */
	close(fd);

	/* 只读打开进行数据校验 */
	fd = open(TEST_FN, O_RDONLY, 0);
	if (fd < 0)
	{
		rt_kprintf("check: open file for read failed\n");
		return;
	}

	length = read(fd, buffer, sizeof(buffer));
	if (length != sizeof(buffer))
	{
		rt_kprintf("check: read file failed\n");
		close(fd);
		return;
	}
	for (index = 0; index < sizeof(test_data); index ++)
	{
		if (test_data[index] != buffer[index])
		{
			rt_kprintf("check: check data failed at %d\n", index);
			close(fd);
			return;
		}
	}

	length = read(fd, buffer, sizeof(buffer));
	if (length != sizeof(buffer))
	{
		rt_kprintf("check: read file failed\n");
		close(fd);
		return;
	}
	for (index = 0; index < sizeof(test_data); index ++)
	{
		if (test_data[index] != buffer[index])
		{
			rt_kprintf("check: check data failed at %d\n", index);
			close(fd);
			return;
		}
	}
	/* 检查数据完毕，关闭文件 */
	close(fd);
	/* 打印结果 */
	rt_kprintf("read/write done.\n");
}

#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(readwrite, perform file read and write test);
#endif
