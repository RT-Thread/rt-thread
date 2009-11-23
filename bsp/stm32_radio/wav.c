#include <finsh.h>
#include <dfs_posix.h>
#include "netbuffer.h"
#include "stm32f10x.h"

static rt_err_t wav_tx_done(rt_device_t dev, void *buffer)
{
	/* release memory block */
	sbuf_release(buffer);

	return RT_EOK;
}

void wav(char* filename)
{
    int fd;
	rt_size_t block_size;

	block_size = sbuf_get_size();
	block_size = (block_size / 512) * 512;

    fd = open(filename, O_RDONLY, 0);
    if (fd >= 0)
    {
		rt_uint8_t* buf;
		rt_size_t 	len;
		rt_device_t device;

		/* open audio device and set tx done call back */
		device = rt_device_find("snd");
		rt_device_set_tx_complete(device, wav_tx_done);
		rt_device_open(device, RT_DEVICE_OFLAG_WRONLY);

		do
		{
			buf = sbuf_alloc();
			len = read(fd, (char*)buf, block_size);
			if (len > 0) rt_device_write(device, 0, buf, len);
			else sbuf_release(buf);
		} while (len != 0);

		/* close device and file */
		rt_device_close(device);
		close(fd);
    }
}
FINSH_FUNCTION_EXPORT(wav, wav test)

