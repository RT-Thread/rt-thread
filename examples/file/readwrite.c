/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-02-10     Bernard      first version
 * 2020-04-12     Jianjia Ma   add msh cmd
 */

#include <rtthread.h>
#include <dfs_posix.h>

#define TEST_DATA_LEN     120

/* file read write test */
void readwrite(const char* filename)
{
	int fd;
	int index, length;
	char* test_data;
	char* buffer;
	int block_size = TEST_DATA_LEN;

	/* open with write only & create */
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0);
	if (fd < 0)
	{
		rt_kprintf("open file for write failed\n");
		return;
	}

	test_data = rt_malloc(block_size);
    if (test_data == RT_NULL)
    {
        rt_kprintf("no memory\n");
        close(fd);
        return;
    }

    buffer = rt_malloc(block_size);
    if (buffer == RT_NULL)
    {
        rt_kprintf("no memory\n");
        close(fd);
        rt_free(test_data);
        return;
    }

	/* prepare some data */
	for (index = 0; index < block_size; index ++)
	{
		test_data[index] = index + 27;
	}

	/* write to file */
	length = write(fd, test_data, block_size);
	if (length != block_size)
	{
		rt_kprintf("write data failed\n");
		close(fd);
		goto __exit;
	}

	/* close file */
	close(fd);

	/* reopen the file with append to the end */
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0);
	if (fd < 0)
	{
		rt_kprintf("open file for append write failed\n");
		goto __exit;;
	}

	length = write(fd, test_data, block_size);
	if (length != block_size)
	{
		rt_kprintf("append write data failed\n");
		close(fd);
		goto __exit;
	}
	/* close the file */
	close(fd);

	/* open the file for data validation. */
	fd = open(filename, O_RDONLY, 0);
	if (fd < 0)
	{
		rt_kprintf("check: open file for read failed\n");
		goto __exit;
	}

	/* read the data (should be the data written by the first time ) */
	length = read(fd, buffer, block_size);
	if (length != block_size)
	{
		rt_kprintf("check: read file failed\n");
		close(fd);
		goto __exit;
	}

	/* validate */
	for (index = 0; index < block_size; index ++)
	{
		if (test_data[index] != buffer[index])
		{
			rt_kprintf("check: check data failed at %d\n", index);
			close(fd);
			goto __exit;
		}
	}

	/* read the data (should be the second time data) */
	length = read(fd, buffer, block_size);
	if (length != block_size)
	{
		rt_kprintf("check: read file failed\n");
		close(fd);
		goto __exit;
	}

	/* validate */
	for (index = 0; index < block_size; index ++)
	{
		if (test_data[index] != buffer[index])
		{
			rt_kprintf("check: check data failed at %d\n", index);
			close(fd);
			goto __exit;
		}
	}

	/* close the file */
	close(fd);
	/* print result */
	rt_kprintf("read/write test successful!\n");

__exit:
    rt_free(test_data);
    rt_free(buffer);
}

#ifdef RT_USING_FINSH
#include <finsh.h>
/* export to finsh */
FINSH_FUNCTION_EXPORT(readwrite, perform file read and write test);

#ifdef FINSH_USING_MSH
static void cmd_readwrite(int argc, char *argv[])
{
    char* filename;

    if(argc == 2)
    {
        filename = argv[1];
    }
    else
    {
        rt_kprintf("Usage: readwrite [file_path]\n");
        return;
    }
    readwrite(filename);
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_readwrite, __cmd_readwrite, perform file read and write test);
#endif /* FINSH_USING_MSH */
#endif /* RT_USING_FINSH */
