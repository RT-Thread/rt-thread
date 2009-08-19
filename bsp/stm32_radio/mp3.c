#include <rtthread.h>
#include <dfs_posix.h>
#include <mp3/pub/mp3dec.h>

#define MP3_AUDIO_BUF_SZ    4096
#define MP3_DECODE_MP_CNT   2
#define MP3_DECODE_MP_SZ    2560

#define STATIC_MEMORY_POOL
#ifdef STATIC_MEMORY_POOL
static rt_uint8_t mempool[(MP3_DECODE_MP_SZ * 2 + 4)* 2]; // 5k x 2
static struct rt_mempool _mp;
#endif

struct mp3_decoder
{
    /* mp3 information */
    HMP3Decoder decoder;
    MP3FrameInfo frame_info;
    rt_uint32_t frames;

    /* mp3 file descriptor */
    int fd;

    /* mp3 read session */
    rt_uint8_t *read_buffer;
    rt_uint8_t* read_ptr;
    rt_int32_t read_offset;
    rt_uint32_t bytes_left, bytes_left_before_decoding;

    /* mp3 decode memory pool */
    rt_mp_t mp;

	/* audio device */
	rt_device_t snd_device;
};

static rt_err_t mp3_decoder_tx_done(rt_device_t dev, void *buffer)
{
	/* release memory block to memory pool */
	rt_mp_free(buffer);

	return RT_EOK;
}

rt_uint8_t mp3_fd_buffer[MP3_AUDIO_BUF_SZ];
void mp3_decoder_init(struct mp3_decoder* decoder)
{
    RT_ASSERT(decoder != RT_NULL);

	/* init read session */
	decoder->read_ptr = RT_NULL;
	decoder->bytes_left_before_decoding = decoder->bytes_left = 0;
	decoder->frames = 0;

    // decoder->read_buffer = rt_malloc(MP3_AUDIO_BUF_SZ);
    decoder->read_buffer = &mp3_fd_buffer[0];
	if (decoder->read_buffer == RT_NULL) return;

	/* create memory pool for decoding */
#ifdef STATIC_MEMORY_POOL
	rt_mp_init(&_mp, "mp3", &mempool[0], sizeof(mempool), MP3_DECODE_MP_SZ * 2);
	decoder->mp = &_mp;
#else
	decoder->mp = rt_mp_create("mp3dec", MP3_DECODE_MP_CNT, MP3_DECODE_MP_SZ * 2);
#endif

    decoder->decoder = MP3InitDecoder();

	/* open audio device */
	decoder->snd_device = rt_device_find("snd");
	if (decoder->snd_device != RT_NULL)
	{
		/* set tx complete call back function */
		rt_device_set_tx_complete(decoder->snd_device, mp3_decoder_tx_done);
		rt_device_open(decoder->snd_device, RT_DEVICE_OFLAG_WRONLY);
	}
}

void mp3_decoder_detach(struct mp3_decoder* decoder)
{
    RT_ASSERT(decoder != RT_NULL);

	/* close audio device */
	if (decoder->snd_device != RT_NULL)
		rt_device_close(decoder->snd_device);
	
	/* release mp3 decoder */
    MP3FreeDecoder(decoder->decoder);

#ifdef STATIC_MEMORY_POOL
	rt_mp_detach(decoder->mp);
#else
	/* delete memory pool for decoding */
	rt_mp_delete(decoder->mp);
#endif
}

struct mp3_decoder* mp3_decoder_create()
{
    struct mp3_decoder* decoder;

	/* allocate object */
    decoder = (struct mp3_decoder*) rt_malloc (sizeof(struct mp3_decoder));
    if (decoder != RT_NULL)
    {
        mp3_decoder_init(decoder);
    }

    return decoder;
}

void mp3_decoder_delete(struct mp3_decoder* decoder)
{
    RT_ASSERT(decoder != RT_NULL);

	/* de-init mp3 decoder object */
	mp3_decoder_detach(decoder);
	/* release this object */
    rt_free(decoder);
}

rt_uint16_t is_first = 1;
rt_uint32_t current_offset = 0;
static rt_int32_t mp3_decoder_fill_buffer(struct mp3_decoder* decoder)
{
	rt_size_t bytes_read;
	rt_size_t bytes_to_read;

	// rt_kprintf("left: %d. refilling inbuffer...\n", decoder->bytes_left);
	if (decoder->bytes_left > 0)
	{
		// better: move unused rest of buffer to the start
		rt_memmove(decoder->read_buffer, decoder->read_ptr, decoder->bytes_left);
	}

	bytes_to_read = (MP3_AUDIO_BUF_SZ - decoder->bytes_left) & ~(512 - 1);
	// rt_kprintf("read bytes: %d\n", bytes_to_read);
	
	if (is_first) is_first = 0;
	else current_offset += MP3_AUDIO_BUF_SZ - decoder->bytes_left;

	bytes_read = read(decoder->fd, (char *)(decoder->read_buffer + decoder->bytes_left),
        bytes_to_read);

	if (bytes_read == bytes_to_read)
	{
		decoder->read_ptr = decoder->read_buffer;
		decoder->read_offset = 0;
		decoder->bytes_left = decoder->bytes_left + bytes_to_read;
		return 0;
	}
	else
	{
		rt_kprintf("can't read more data");
		return -1;
	}
}

int mp3_decoder_run(struct mp3_decoder* decoder)
{
	int err;
	rt_uint16_t* buffer;

    RT_ASSERT(decoder != RT_NULL);

	if ((decoder->read_ptr == RT_NULL) || decoder->bytes_left < 2*MAINBUF_SIZE)
	{
		if(mp3_decoder_fill_buffer(decoder) != 0)
			return -1;
	}

	// rt_kprintf("read offset: 0x%08x\n", decoder->read_ptr - decoder->read_buffer);
	decoder->read_offset = MP3FindSyncWord(decoder->read_ptr, decoder->bytes_left);
	if (decoder->read_offset < 0)
	{
		rt_kprintf("Error: MP3FindSyncWord returned <0");

		if(mp3_decoder_fill_buffer(decoder) != 0)
			return -1;
	}
	// rt_kprintf("sync position: %x\n", decoder->read_offset);

	decoder->read_ptr += decoder->read_offset;
	decoder->bytes_left -= decoder->read_offset;
	decoder->bytes_left_before_decoding = decoder->bytes_left;

#if 0
	// check if this is really a valid frame
	// (the decoder does not seem to calculate CRC, so make some plausibility checks)
	if (!(MP3GetNextFrameInfo(decoder->decoder, &decoder->frame_info, decoder->read_ptr) == 0 &&
			decoder->frame_info.nChans == 2 &&
			decoder->frame_info.version == 0))
	{
		rt_kprintf("this is an invalid frame\n");
		// advance data pointer
		// TODO: handle bytes_left == 0
		RT_ASSERT(decoder->bytes_left > 0);

		decoder->bytes_left --;
		decoder->read_ptr ++;
		return 0;
	}

	if (decoder->bytes_left < 1024)
	{
		if(mp3_decoder_fill_buffer(decoder) != 0)
			return -1;
	}
#endif

    /* get a decoder buffer */
    buffer = (rt_uint16_t*)rt_mp_alloc(decoder->mp, RT_WAITING_FOREVER);

	// rt_kprintf("bytes left before decode: %d\n", decoder->bytes_left);

	err = MP3Decode(decoder->decoder, &decoder->read_ptr,
        (int*)&decoder->bytes_left, (short*)buffer, 0);

	// rt_kprintf("bytes left after decode: %d\n", decoder->bytes_left);
	
	decoder->frames++;

	if (err != ERR_MP3_NONE)
	{
		switch (err)
		{
		case ERR_MP3_INDATA_UNDERFLOW:
			rt_kprintf("ERR_MP3_INDATA_UNDERFLOW\n");
			decoder->bytes_left = 0;
			if(mp3_decoder_fill_buffer(decoder) != 0)
				return -1;
			break;

		case ERR_MP3_MAINDATA_UNDERFLOW:
			/* do nothing - next call to decode will provide more mainData */
			rt_kprintf("ERR_MP3_MAINDATA_UNDERFLOW\n");
			break;

		case ERR_MP3_INVALID_FRAMEHEADER:
			rt_kprintf("ERR_MP3_INVALID_FRAMEHEADER\n");
			rt_kprintf("current offset: 0x%08x, frames: %d\n", current_offset, decoder->frames);
			/* dump sector */
			{
				rt_uint8_t *ptr;
				rt_size_t   size = 0, col = 0;

				ptr = decoder->read_buffer;
				rt_kprintf("   00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f\n");
				rt_kprintf("00 ");
				while (size ++ < 512)
				{
					rt_kprintf("%02x ", *ptr ++);
					if (size % 16 == 0) rt_kprintf("\n%02x ", ++col);
				}
			}
			RT_ASSERT(0);
			// break;

		case ERR_MP3_INVALID_HUFFCODES:
			rt_kprintf("ERR_MP3_INVALID_HUFFCODES\n");
			break;

		default:
			rt_kprintf("unknown error: %i\n", err);
			// skip this frame
			if (decoder->bytes_left > 0)
			{
				decoder->bytes_left --;
				decoder->read_ptr ++;
			}
			else
			{
				// TODO
				RT_ASSERT(0);
			}
			break;
		}

		/* release this memory block */
		rt_mp_free(buffer);
	}
	else
	{
		/* no error */
		MP3GetLastFrameInfo(decoder->decoder, &decoder->frame_info);

// #ifdef MP3_DECODER_TRACE
		rt_kprintf("Bitrate: %i\n", decoder->frame_info.bitrate);
		rt_kprintf("%i samples\n", decoder->frame_info.outputSamps);

		rt_kprintf("%lu Hz, %i kbps\n", decoder->frame_info.samprate,
            decoder->frame_info.bitrate/1000);
// #endif

        /* set sample rate */

		/* write to sound device */
		rt_device_write(decoder->snd_device, 0, buffer, decoder->frame_info.outputSamps * 2);
		// rt_mp_free(buffer);
	}

	return 0;
}

#include <finsh.h>
void mp3(char* filename)
{
	int fd;
	struct mp3_decoder* decoder;
	
	fd = open(filename, O_RDONLY, 0);
	if (fd >= 0)
	{
		decoder = mp3_decoder_create();
		if (decoder != RT_NULL)
		{
			decoder->fd = fd;
			while (mp3_decoder_run(decoder) != -1);
			close(fd);
			
			/* delete decoder object */
			mp3_decoder_delete(decoder);
		}
	}
}
FINSH_FUNCTION_EXPORT(mp3, mp3 decode test)
