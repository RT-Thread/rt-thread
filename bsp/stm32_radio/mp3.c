#include <rtthread.h>
#include <dfs_posix.h>
#include <mp3/pub/mp3dec.h>
#include <string.h>

#include "board.h"
#include "netbuffer.h"
#include "player_ui.h"
#include "player_bg.h"

#define MP3_AUDIO_BUF_SZ    4096
#ifndef MIN
#define MIN(x, y)			((x) < (y)? (x) : (y))
#endif

rt_uint8_t mp3_fd_buffer[MP3_AUDIO_BUF_SZ];

struct mp3_decoder
{
    /* mp3 information */
    HMP3Decoder decoder;
    MP3FrameInfo frame_info;
    rt_uint32_t frames;

    /* mp3 file descriptor */
	rt_size_t (*fetch_data)(void* parameter, rt_uint8_t *buffer, rt_size_t length);
	void* fetch_parameter;

    /* mp3 read session */
    rt_uint8_t *read_buffer, *read_ptr;
    rt_int32_t  read_offset;
    rt_uint32_t bytes_left, bytes_left_before_decoding;

	/* audio device */
	rt_device_t snd_device;
};

static rt_err_t mp3_decoder_tx_done(rt_device_t dev, void *buffer)
{
	/* release memory block */
	sbuf_release(buffer);

	return RT_EOK;
}

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

	bytes_read = decoder->fetch_data(decoder->fetch_parameter,
		(rt_uint8_t *)(decoder->read_buffer + decoder->bytes_left),
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
	rt_uint32_t  delta;

    RT_ASSERT(decoder != RT_NULL);

	if (player_is_playing() != RT_TRUE) return -1;

	if ((decoder->read_ptr == RT_NULL) || decoder->bytes_left < 2*MAINBUF_SIZE)
	{
		if(mp3_decoder_fill_buffer(decoder) != 0)
			return -1;
	}

	// rt_kprintf("read offset: 0x%08x\n", decoder->read_ptr - decoder->read_buffer);
	decoder->read_offset = MP3FindSyncWord(decoder->read_ptr, decoder->bytes_left);
	if (decoder->read_offset < 0)
	{
		/* discard this data */
		rt_kprintf("outof sync\n");

		decoder->bytes_left = 0;
		return 0;
	}

	decoder->read_ptr += decoder->read_offset;
	delta = decoder->read_offset;
	decoder->bytes_left -= decoder->read_offset;
	if (decoder->bytes_left < 1024)
	{
		/* fill more data */
		if(mp3_decoder_fill_buffer(decoder) != 0)
			return -1;
	}

    /* get a decoder buffer */
    buffer = (rt_uint16_t*)sbuf_alloc();
	decoder->bytes_left_before_decoding = decoder->bytes_left;

	err = MP3Decode(decoder->decoder, &decoder->read_ptr,
        (int*)&decoder->bytes_left, (short*)buffer, 0);
	delta += (decoder->bytes_left_before_decoding - decoder->bytes_left);

	current_offset += delta;
	player_set_position(current_offset);

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
			{
				/* release this memory block */
				sbuf_release(buffer);
				return -1;
			}
			break;

		case ERR_MP3_MAINDATA_UNDERFLOW:
			/* do nothing - next call to decode will provide more mainData */
			rt_kprintf("ERR_MP3_MAINDATA_UNDERFLOW\n");
			break;

		default:
			rt_kprintf("unknown error: %d, left: %d\n", err, decoder->bytes_left);

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
		sbuf_release(buffer);
	}
	else
	{
		/* no error */
		MP3GetLastFrameInfo(decoder->decoder, &decoder->frame_info);

        /* set sample rate */

		/* write to sound device */
		if (decoder->frame_info.outputSamps > 0)
		{
			rt_device_write(decoder->snd_device, 0, buffer, decoder->frame_info.outputSamps * 2);
		}
		else
		{
			/* no output */
			sbuf_release(buffer);
		}
	}

	return 0;
}

/* get mp3 information */
void mp3_get_info(const char* filename, struct tag_info* info)
{
	int fd;
	char* id3buffer;
	rt_size_t   bytes_read;
	int sync_word;
    HMP3Decoder decoder;
    MP3FrameInfo frame_info;

	id3buffer = (char*)&mp3_fd_buffer[0];
	if (filename == RT_NULL || info == RT_NULL) return;

	fd = open(filename, O_RDONLY, 0);
	if (fd < 0) return; /* can't read file */

	/* init decoder */
	decoder = MP3InitDecoder();

	/* read data */
	bytes_read = read(fd, id3buffer, sizeof(mp3_fd_buffer));

	/* get frame information */
	sync_word = MP3FindSyncWord(id3buffer, bytes_read);
	if (sync_word < 0)
	{
		/* can't get sync word */
		close(fd);
		mp3_decoder_detach(decoder);
	}
	/* get frame information */
	MP3GetNextFrameInfo(decoder, &frame_info, &id3buffer[sync_word]);
	info->bit_rate = frame_info.bitrate;
	info->sampling = frame_info.samprate;
	info->duration = lseek(fd, 0, SEEK_END)/ (info->bit_rate / 8); /* second */

	if (strncmp("ID3", id3buffer, 4) == 0)
	{
		rt_uint32_t tag_size, frame_size, i;
		rt_uint8_t version_major;
		int frame_header_size;

		tag_size = ((rt_uint32_t)id3buffer[6] << 21)|((rt_uint32_t)id3buffer[7] << 14)|((rt_uint16_t)id3buffer[8] << 7)|id3buffer[9];
		info->data_start = tag_size;
		version_major = id3buffer[3];
		if (version_major >= 3)
		{
			frame_header_size = 10;
		}
		else
		{
			frame_header_size = 6;
		}
		i = 10;

		// iterate through frames
		while (i < MIN(tag_size, sizeof(id3buffer)))
		{
			if (version_major >= 3)
			{
				frame_size = ((rt_uint32_t)id3buffer[i + 4] << 24)|((rt_uint32_t)id3buffer[i + 5] << 16)|((rt_uint16_t)id3buffer[i + 6] << 8)|id3buffer[i + 7];
			}
			else
			{
				frame_size = ((rt_uint32_t)id3buffer[i + 3] << 14)|((rt_uint16_t)id3buffer[i + 4] << 7)|id3buffer[i + 5];
			}

			if (strncmp("TT2", id3buffer + i, 3) == 0 || strncmp("TIT2", id3buffer + i, 4) == 0)
			{
				strncpy(info->title, id3buffer + i + frame_header_size + 1, MIN(frame_size - 1, sizeof(info->title) - 1));
			}
			else if (strncmp("TP1", id3buffer + i, 3) == 0 || strncmp("TPE1", id3buffer + i, 4) == 0)
			{
				strncpy(info->artist, id3buffer + i + frame_header_size + 1, MIN(frame_size - 1, sizeof(info->artist) - 1));
			}

			i += frame_size + frame_header_size;
		}
	}
	else
	{
		lseek(fd, -128, SEEK_END);
		bytes_read = read(fd, id3buffer, 128);

		/* ID3v1 */
		if (strncmp("TAG", id3buffer, 3) == 0)
		{
			strncpy(info->title, id3buffer + 3, MIN(30, sizeof(info->title) - 1));
			strncpy(info->artist, id3buffer + 3 + 30, MIN(30, sizeof(info->artist) - 1));
		}

		/* set data start position */
		info->data_start = 0;
	}

    /* set current position */
    info->position = 0;

	/* release mp3 decoder */
    MP3FreeDecoder(decoder);

	/* close file */
	close(fd);
}

#include <finsh.h>
rt_size_t fd_fetch(void* parameter, rt_uint8_t *buffer, rt_size_t length)
{
	int fd = (int)parameter;
	return read(fd, (char*)buffer, length);
}
void mp3(char* filename)
{
	int fd;
	struct mp3_decoder* decoder;
	extern rt_bool_t is_playing;
	
	is_playing = RT_TRUE;
	fd = open(filename, O_RDONLY, 0);
	if (fd >= 0)
	{
		decoder = mp3_decoder_create();
		if (decoder != RT_NULL)
		{
			decoder->fetch_data = fd_fetch;
			decoder->fetch_parameter = (void*)fd;

			current_offset = 0;
			while (mp3_decoder_run(decoder) != -1);
			close(fd);

			/* delete decoder object */
			mp3_decoder_delete(decoder);
		}
	}
	is_playing = RT_FALSE;
}
FINSH_FUNCTION_EXPORT(mp3, mp3 decode test);

#if STM32_EXT_SRAM
/* http mp3 */
#include "http.h"
static rt_size_t http_fetch(rt_uint8_t* ptr, rt_size_t len, void* parameter)
{
	struct http_session* session = (struct http_session*)parameter;
	RT_ASSERT(session != RT_NULL);

	return http_session_read(session, ptr, len);
}

static void http_close(void* parameter)
{
	struct http_session* session = (struct http_session*)parameter;
	RT_ASSERT(session != RT_NULL);

	http_session_close(session);
}

rt_size_t http_data_fetch(void* parameter, rt_uint8_t *buffer, rt_size_t length)
{
	return net_buf_read(buffer, length);
}
void http_mp3(char* url)
{
    struct http_session* session;
	struct mp3_decoder* decoder;
	extern rt_bool_t is_playing;
	
	is_playing = RT_TRUE;

	session = http_session_open(url);
	if (session != RT_NULL)
	{
		/* add a job to netbuf worker */
		net_buf_add_job(http_fetch, http_close, (void*)session);

		decoder = mp3_decoder_create();
		if (decoder != RT_NULL)
		{
			decoder->fetch_data = http_data_fetch;
			decoder->fetch_parameter = RT_NULL;

			current_offset = 0;
			while (mp3_decoder_run(decoder) != -1);

			/* delete decoder object */
			mp3_decoder_delete(decoder);
		}
		session = RT_NULL;
	}
}
FINSH_FUNCTION_EXPORT(http_mp3, http mp3 decode test);

/* http mp3 */
#include "http.h"
static rt_size_t ice_fetch(rt_uint8_t* ptr, rt_size_t len, void* parameter)
{
	struct shoutcast_session* session = (struct shoutcast_session*)parameter;
	RT_ASSERT(session != RT_NULL);

	return shoutcast_session_read(session, ptr, len);
}

static void ice_close(void* parameter)
{
	struct shoutcast_session* session = (struct shoutcast_session*)parameter;
	RT_ASSERT(session != RT_NULL);

	shoutcast_session_close(session);
}

rt_size_t ice_data_fetch(void* parameter, rt_uint8_t *buffer, rt_size_t length)
{
	return net_buf_read(buffer, length);
}

void ice_mp3(char* url)
{
    struct shoutcast_session* session;
	struct mp3_decoder* decoder;
	extern rt_bool_t is_playing;

	is_playing = RT_TRUE;

	session = shoutcast_session_open(url);
	if (session != RT_NULL)
	{
		/* add a job to netbuf worker */
		net_buf_add_job(ice_fetch, ice_close, (void*)session);

		decoder = mp3_decoder_create();
		if (decoder != RT_NULL)
		{
			decoder->fetch_data = ice_data_fetch;
			decoder->fetch_parameter = RT_NULL;

			current_offset = 0;
			while (mp3_decoder_run(decoder) != -1);

			/* delete decoder object */
			mp3_decoder_delete(decoder);
		}
		session = RT_NULL;
	}
}
FINSH_FUNCTION_EXPORT(ice_mp3, shoutcast mp3 decode test);

char ice_url[] = "http://192.168.1.5:8000/stream";
void ice()
{
	rt_thread_t tid;
	
	tid = rt_thread_create("ice", ice_mp3, (void*)ice_url,
		4096, 0x08, 5);
	if (tid != RT_NULL) rt_thread_startup(tid);
}
FINSH_FUNCTION_EXPORT(ice, shoutcast thread test);

#endif
