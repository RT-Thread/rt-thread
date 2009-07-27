#include <rtthread.h>
#include <dfs_posix.h>
#include <mp3/pub/mp3dec.h>
#include "dac.h"

static HMP3Decoder hMP3Decoder;
static MP3FrameInfo mp3FrameInfo;
static unsigned char *read_ptr;
static int bytes_left=0, bytes_leftBeforeDecoding=0, err, offset;
static int nFrames = 0;
static unsigned char *mp3buf;
static unsigned int mp3buf_size;
static unsigned char allocated = 0;

static void mp3_reset()
{
	read_ptr = RT_NULL;
	bytes_leftBeforeDecoding = bytes_left = 0;
	nFrames = 0;
}

void mp3_init(rt_uint8_t *buffer, rt_uint32_t buffer_size)
{
	mp3buf = buffer;
	mp3buf_size = buffer_size;
	mp3_reset();
}

void mp3_alloc()
{
	if (!allocated) hMP3Decoder = MP3InitDecoder();
	allocated = 1;
}

void mp3_free()
{
	if (allocated) MP3FreeDecoder(hMP3Decoder);
	allocated = 0;
}

int mp3_refill_inbuffer(int fd)
{
  rt_uint16_t bytes_read;
  int bytes_to_read;
  
  // rt_kprintf("left: %d. refilling inbuffer...\n", bytes_left);
  if (bytes_left > 0)
  {
    	// after fseeking backwards the FAT has to be read from the beginning -> S L O W
		// assert(f_lseek(mp3file, mp3file->fptr - bytes_leftBeforeDecoding) == FR_OK);
		// better: move unused rest of buffer to the start
		// no overlap as long as (1024 <= mp3buf_size/2), so no need to use memove
		rt_memcpy(mp3buf, read_ptr, bytes_left);
  }
  
  bytes_to_read = mp3buf_size - bytes_left;
  
	bytes_read = read(fd, (char *)mp3buf + bytes_left, bytes_to_read);
	
	if (bytes_read == bytes_to_read)
	{
		read_ptr = mp3buf;
		offset = 0;
		bytes_left = mp3buf_size;
		// rt_kprintf("ok. read: %d. left: %d\n", bytes_read, bytes_left);
		return 0;
	}
	else
	{
		rt_kprintf("can't read more data");
		return -1;
	}
}

int mp3_process(int fd)
{
	int writeable_buffer;
	
	if (read_ptr == RT_NULL)
	{
		if(mp3_refill_inbuffer(fd) != 0)
		  return -1;
	}

	offset = MP3FindSyncWord(read_ptr, bytes_left);
	if (offset < 0)
	{
		rt_kprintf("Error: MP3FindSyncWord returned <0");
		
		if(mp3_refill_inbuffer(fd) != 0)
		  return -1;
	}

	read_ptr += offset;
	bytes_left -= offset;
	bytes_leftBeforeDecoding = bytes_left;

	// check if this is really a valid frame
	// (the decoder does not seem to calculate CRC, so make some plausibility checks)
	if (MP3GetNextFrameInfo(hMP3Decoder, &mp3FrameInfo, read_ptr) == 0 &&
		mp3FrameInfo.nChans == 2 &&
		mp3FrameInfo.version == 0)
	{
		// rt_kprintf("Found a frame at offset %x\n", offset + read_ptr - mp3buf + mp3file->fptr);
	}
	else
	{
		rt_kprintf("this is no valid frame\n");
		// advance data pointer
		// TODO: handle bytes_left == 0
		RT_ASSERT(bytes_left > 0);
		bytes_left -= 1;
		read_ptr += 1;
		return 0;
	}

	if (bytes_left < 1024) {
		if(mp3_refill_inbuffer(fd) != 0)
		  return -1;
	}

	// rt_kprintf("bytes_leftBeforeDecoding: %i\n", bytes_leftBeforeDecoding);

	writeable_buffer = dac_get_writeable_buffer();
	if (writeable_buffer == -1) {
		return 0;
	}

	// rt_kprintf("wb %i\n", writeable_buffer);

	err = MP3Decode(hMP3Decoder, &read_ptr, &bytes_left, dac_buffer[writeable_buffer], 0);

	nFrames++;
	
	if (err)
	{
 		switch (err)
		{
		case ERR_MP3_INDATA_UNDERFLOW:
			rt_kprintf("ERR_MP3_INDATA_UNDERFLOW");
      		bytes_left = 0;
			if(mp3_refill_inbuffer(fd) != 0)
  		  return -1;
			break;

 		case ERR_MP3_MAINDATA_UNDERFLOW:
 			/* do nothing - next call to decode will provide more mainData */
 			rt_kprintf("ERR_MP3_MAINDATA_UNDERFLOW");
 			break;

 		default:
 			rt_kprintf("unknown error: %i\n", err);
 			// skip this frame
 			if (bytes_left > 0)
			{
 				bytes_left --;
 				read_ptr ++;
 			}
			else
			{
 				// TODO
 				RT_ASSERT(0);
 			}
 			break;
 		}

		dac_buffer_size[writeable_buffer] = 0;
	}
	else
	{
		/* no error */
		MP3GetLastFrameInfo(hMP3Decoder, &mp3FrameInfo);
		// rt_kprintf("Bitrate: %i\r\n", mp3FrameInfo.bitrate);
		// rt_kprintf("%i samples\n", mp3FrameInfo.outputSamps);

		dac_buffer_size[writeable_buffer] = mp3FrameInfo.outputSamps;

		// rt_kprintf("%lu Hz, %i kbps\n", mp3FrameInfo.samprate, mp3FrameInfo.bitrate/1000);

		if (dac_set_srate(mp3FrameInfo.samprate) != 0) {
			rt_kprintf("unsupported sample rate: %lu\n", mp3FrameInfo.samprate);
			return -1;
		}
	}

	return 0;
}

#include <finsh.h>
void mp3(char* filename)
{
	int fd;
	rt_uint8_t *mp3_buffer;
	
	list_date();
	
	dac_init();
	
	mp3_buffer = rt_malloc(2048);
	mp3_init(mp3_buffer, 2048);
	mp3_alloc();
	
	fd = open(filename, O_RDONLY, 0);
	if (fd >= 0)
	{
		while (mp3_process(fd) == 0);
		
		close(fd);
	}
	
	list_date();
}
FINSH_FUNCTION_EXPORT(mp3, mp3 decode test)
