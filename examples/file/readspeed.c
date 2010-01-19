#include <rtthread.h>
#include <dfs_posix.h>

void readspeed(const char* filename, int block_size)
{
    int fd;
    char *buff_ptr;
    rt_size_t total_length;
    rt_tick_t tick;

    fd = open(filename, 0, DFS_O_RDONLY);
    if (fd < 0)
    {
        rt_kprintf("open file:%s failed\n", filename);
        return;
    }

    buff_ptr = rt_malloc(block_size);
    if (buff_ptr == RT_NULL)
    {
        rt_kprintf("no memory\n");
        close(fd);

        return;
    }

    tick = rt_tick_get();
    total_length = 0;
    while (1)
    {
        int length;
        length = read(fd, buff_ptr, block_size);

        if (length == 0) break;
        total_length += length;
    }
    tick = rt_tick_get() - tick;

	/* close file and release memory */
    close(fd);
	rt_free(buff_ptr);

    /* calculate read speed */
    rt_kprintf("File read speed: %d byte/s\n", total_length/ (tick/RT_TICK_PER_SECOND));
}

#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(readspeed, perform file read test);
#endif
