#include <finsh.h>
#include <dfs_posix.h>
#include "stm32f10x_lib.h"

rt_uint32_t wav_length;
rt_uint8_t* wav_buffer;

#define WAV_MP_NUM		2
#define WAV_MP_BUFSZ	(1024 * 1)
#define STATIC_MEMPOOL
#ifdef STATIC_MEMPOOL
static rt_uint8_t mempool[(WAV_MP_BUFSZ + 4)* WAV_MP_NUM]; // 5k x 2
static struct rt_mempool _mp;
#endif
static rt_mp_t mp;

static rt_err_t wav_tx_done(rt_device_t dev, void *buffer)
{
	/* release memory block to memory pool */
	rt_mp_free(buffer);

	return RT_EOK;
}

void wav(char* filename)
{
    int fd;

#ifdef STATIC_MEMPOOL
	rt_mp_init(&_mp, "wav", &mempool[0], sizeof(mempool), WAV_MP_BUFSZ);
	mp = &_mp;
#else
	mp = rt_mp_create("wav", WAV_MP_NUM, WAV_MP_BUFSZ);
#endif

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

		// buf = rt_mp_alloc(mp, RT_WAITING_FOREVER);
		// len = read(fd, (char*)buf, WAV_MP_BUFSZ);

		do {
			buf = rt_mp_alloc(mp, RT_WAITING_FOREVER);
			rt_kprintf("read file");
			len = read(fd, (char*)buf, WAV_MP_BUFSZ);
			rt_kprintf("...done!\n");
			if (len > 0) rt_device_write(device, 0, buf, len);
		} while (len != 0);
		
		/* close device and file */
		rt_device_close(device);
		close(fd);
		
		/* delete memory pool */
#ifdef STATIC_MEMPOOL
		rt_mp_detach(mp);
#else
		rt_mp_delete(mp);
#endif
    }
}
FINSH_FUNCTION_EXPORT(wav, wav test)

/* DMA Test */
#define BufferSize         32
u8 SPI2_Buffer_Tx[BufferSize] = {0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,
                                 0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,0x60,0x61,0x62,
                                 0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,
                                 0x6C,0x6D,0x6E,0x6F,0x70};

void wm(int cnt)
{
	rt_device_t device;
	rt_uint8_t *buf;

	mp = rt_mp_create("wav", WAV_MP_NUM, WAV_MP_BUFSZ);

	device = rt_device_find("snd");
	rt_device_set_tx_complete(device, wav_tx_done);
	rt_device_open(device, RT_DEVICE_OFLAG_WRONLY);

	while(cnt)
	{
		buf = rt_mp_alloc(mp, RT_WAITING_FOREVER);
		rt_memcpy(buf, SPI2_Buffer_Tx, BufferSize);

		rt_device_write(device, 0, buf, BufferSize);
		
		cnt --;
	}

	rt_device_close(device);
	rt_mp_delete(mp);
}
FINSH_FUNCTION_EXPORT(wm, wm test)

