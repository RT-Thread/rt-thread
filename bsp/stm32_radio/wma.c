/* wma player test */
#include "libwma/asf.h"
#include "libwma/wmadec.h"

/* The output buffer containing the decoded samples (channels 0 and 1)
   BLOCK_MAX_SIZE is 2048 (samples) and MAX_CHANNELS is 2.
 */

static uint32_t decoded[BLOCK_MAX_SIZE * MAX_CHANNELS];

/* NOTE: WMADecodeContext is 120152 bytes (on x86) */
static WMADecodeContext wmadec;

enum asf_error_e {
	ASF_ERROR_INTERNAL       = -1,  /* incorrect input to API calls */
	ASF_ERROR_OUTOFMEM       = -2,  /* some malloc inside program failed */
	ASF_ERROR_EOF            = -3,  /* unexpected end of file */
	ASF_ERROR_IO             = -4,  /* error reading or writing to file */
	ASF_ERROR_INVALID_LENGTH = -5,  /* length value conflict in input data */
	ASF_ERROR_INVALID_VALUE  = -6,  /* other value conflict in input data */
	ASF_ERROR_INVALID_OBJECT = -7,  /* ASF object missing or in wrong place */
	ASF_ERROR_OBJECT_SIZE    = -8,  /* invalid ASF object size (too small) */
	ASF_ERROR_SEEKABLE       = -9,  /* file not seekable */
	ASF_ERROR_SEEK           = -10  /* file is seekable but seeking failed */
};


static int asf_read_packet(uint8_t** audiobuf, int* audiobufsize, int* packetlength, asf_waveformatex_t* wfx)
{
	uint8_t tmp8, packet_flags, packet_property;
	int stream_id;
	int ec_length, opaque_data, ec_length_type;
	int datalen;
	uint8_t data[18];
	uint8_t* datap;
	uint32_t length;
	uint32_t padding_length;
	uint32_t send_time;
	uint16_t duration;
	uint16_t payload_count;
	int payload_length_type;
	uint32_t payload_hdrlen;
	int payload_datalen;
	int multiple;
	uint32_t replicated_length;
	uint32_t media_object_number;
	uint32_t media_object_offset;
	uint32_t bytesread = 0;
	uint8_t* buf;
	size_t bufsize;
	int i;

	/* rt_kprintf("Reading new packet at %d bytes ", (int)ci->curpos); */

	if (ci->read_filebuf(&tmp8, 1) == 0)
	{
		return ASF_ERROR_EOF;
	}
	bytesread++;

	/* TODO: We need a better way to detect endofstream */
	if (tmp8 != 0x82)
	{
		rt_kprintf("Read failed:  packet did not sync\n");
		return -1;
	}

	if (tmp8 & 0x80)
	{
		ec_length = tmp8 & 0x0f;
		opaque_data = (tmp8 >> 4) & 0x01;
		ec_length_type = (tmp8 >> 5) & 0x03;

		if (ec_length_type != 0x00 || opaque_data != 0 || ec_length != 0x02)
		{
			rt_kprintf("incorrect error correction flags\n");
			return ASF_ERROR_INVALID_VALUE;
		}

		/* Skip ec_data */
		ci->advance_buffer(ec_length);
		bytesread += ec_length;
	}
	else
	{
		ec_length = 0;
	}

	if (ci->read_filebuf(&packet_flags, 1) == 0)
	{
		return ASF_ERROR_EOF;
	}
	if (ci->read_filebuf(&packet_property, 1) == 0)
	{
		return ASF_ERROR_EOF;
	}
	bytesread += 2;

	datalen = GETLEN2b((packet_flags >> 1) & 0x03) +
			  GETLEN2b((packet_flags >> 3) & 0x03) +
			  GETLEN2b((packet_flags >> 5) & 0x03) + 6;

	if (ci->read_filebuf(data, datalen) == 0)
	{
		return ASF_ERROR_EOF;
	}

	bytesread += datalen;

	datap = data;
	length = GETVALUE2b((packet_flags >> 5) & 0x03, datap);
	datap += GETLEN2b((packet_flags >> 5) & 0x03);
	/* sequence value is not used */
	GETVALUE2b((packet_flags >> 1) & 0x03, datap);
	datap += GETLEN2b((packet_flags >> 1) & 0x03);
	padding_length = GETVALUE2b((packet_flags >> 3) & 0x03, datap);
	datap += GETLEN2b((packet_flags >> 3) & 0x03);
	send_time = get_long_le(datap);
	datap += 4;
	duration = get_short_le(datap);
	datap += 2;
	/* rt_kprintf("and duration %d ms\n", duration); */

	/* this is really idiotic, packet length can (and often will) be
	 * undefined and we just have to use the header packet size as the size
	 * value */
	if (!((packet_flags >> 5) & 0x03))
	{
		length = wfx->packet_size;
	}

	/* this is also really idiotic, if packet length is smaller than packet
	 * size, we need to manually add the additional bytes into padding length
	 */
	if (length < wfx->packet_size)
	{
		padding_length += wfx->packet_size - length;
		length = wfx->packet_size;
	}

	if (length > wfx->packet_size)
	{
		rt_kprintf("packet with too big length value\n");
		return ASF_ERROR_INVALID_LENGTH;
	}

	/* check if we have multiple payloads */
	if (packet_flags & 0x01)
	{
		if (ci->read_filebuf(&tmp8, 1) == 0)
		{
			return ASF_ERROR_EOF;
		}
		payload_count = tmp8 & 0x3f;
		payload_length_type = (tmp8 >> 6) & 0x03;
		bytesread++;
	}
	else
	{
		payload_count = 1;
		payload_length_type = 0x02; /* not used */
	}

	if (length < bytesread)
	{
		rt_kprintf("header exceeded packet size, invalid file - length=%d, bytesread=%d\n",(int)length,(int)bytesread);
		/* FIXME: should this be checked earlier? */
		return ASF_ERROR_INVALID_LENGTH;
	}

	/* We now parse the individual payloads, and move all payloads
	   belonging to our audio stream to a contiguous block, starting at
	   the location of the first payload.
	*/
	*audiobuf = NULL;
	*audiobufsize = 0;
	*packetlength = length - bytesread;

	buf = ci->request_buffer(&bufsize, length);
	datap = buf;

	if (bufsize != length)
	{
		/* This should only happen with packets larger than 32KB (the
		   guard buffer size).  All the streams I've seen have
		   relatively small packets less than about 8KB), but I don't
		   know what is expected.
		*/
		rt_kprintf("Could not read packet (requested %d bytes, received %d), curpos=%d, aborting\n",
				   (int)length,(int)bufsize,(int)ci->curpos);
		return -1;
	}

	for (i=0; i<payload_count; i++)
	{
		stream_id = datap[0]&0x7f;
		datap++;
		bytesread++;

		payload_hdrlen = GETLEN2b(packet_property & 0x03) +
						 GETLEN2b((packet_property >> 2) & 0x03) +
						 GETLEN2b((packet_property >> 4) & 0x03);

		// rt_kprintf("payload_hdrlen = %d\n",payload_hdrlen);
		if (payload_hdrlen > sizeof(data))
		{
			rt_kprintf("Unexpectedly long datalen in data - %d\n",datalen);
			return ASF_ERROR_OUTOFMEM;
		}

		bytesread += payload_hdrlen;
		media_object_number = GETVALUE2b((packet_property >> 4) & 0x03, datap);
		datap += GETLEN2b((packet_property >> 4) & 0x03);
		media_object_offset = GETVALUE2b((packet_property >> 2) & 0x03, datap);
		datap += GETLEN2b((packet_property >> 2) & 0x03);
		replicated_length = GETVALUE2b(packet_property & 0x03, datap);
		datap += GETLEN2b(packet_property & 0x03);

		/* TODO: Validate replicated_length */
		/* TODO: Is the content of this important for us? */
		datap += replicated_length;
		bytesread += replicated_length;

		multiple = packet_flags & 0x01;


		if (multiple)
		{
			int x;

			x = GETLEN2b(payload_length_type);

			if (x != 2)
			{
				/* in multiple payloads datalen should be a word */
				return ASF_ERROR_INVALID_VALUE;
			}

			payload_datalen = GETVALUE2b(payload_length_type, datap);
			datap += x;
			bytesread += x;
		}
		else
		{
			payload_datalen = length - bytesread - padding_length;
		}

		if (replicated_length==1)
			datap++;

		if (stream_id == wfx->audiostream)
		{
			if (*audiobuf == NULL)
			{
				/* The first payload can stay where it is */
				*audiobuf = datap;
				*audiobufsize = payload_datalen;
			}
			else
			{
				/* The second and subsequent payloads in this packet
				   that belong to the audio stream need to be moved to be
				   contiguous with the first payload.
				*/
				memmove(*audiobuf + *audiobufsize, datap, payload_datalen);
				*audiobufsize += payload_datalen;
			}
		}
		datap += payload_datalen;
		bytesread += payload_datalen;
	}

	if (*audiobuf != NULL)
		return 1;
	else
		return 0;
}

/* this is the codec entry point */
void wma_run(void)
{
	uint32_t elapsedtime;
	int retval;
	asf_waveformatex_t wfx;
	size_t resume_offset;
	int i;
	int wmares, res;
	uint8_t* audiobuf;
	int audiobufsize;
	int packetlength = 0;
	int errcount = 0;

	/* Generic codec initialisation */
next_track:

	retval = CODEC_OK;

	/* Remember the resume position - when the codec is opened, the
	   playback engine will reset it. */
	resume_offset = ci->id3->offset;

restart_track:
	if (codec_init())
	{
		LOGF("WMA: Error initialising codec\n");
		retval = CODEC_ERROR;
		goto exit;
	}

	/* Copy the format metadata we've stored in the id3 TOC field.  This
	   saves us from parsing it again here. */
	memcpy(&wfx, ci->id3->toc, sizeof(wfx));

	if (wma_decode_init(&wmadec,&wfx) < 0)
	{
		LOGF("WMA: Unsupported or corrupt file\n");
		retval = CODEC_ERROR;
		goto exit;
	}

	if (resume_offset > ci->id3->first_frame_offset)
	{
		/* Get start of current packet */
		int packet_offset = (resume_offset - ci->id3->first_frame_offset)
							% wfx.packet_size;
		ci->seek_buffer(resume_offset - packet_offset);
		elapsedtime = get_timestamp(&i);
		ci->set_elapsed(elapsedtime);
	}
	else
	{
		/* Now advance the file position to the first frame */
		ci->seek_buffer(ci->id3->first_frame_offset);
		elapsedtime = 0;
	}

	resume_offset = 0;

	/* The main decoding loop */

	res = 1;
	while (res >= 0)
	{
		/* Deal with any pending seek requests */
		errcount = 0;

new_packet:
		res = asf_read_packet(&audiobuf, &audiobufsize, &packetlength, &wfx);

		if (res < 0)
		{
			/* We'll try to recover from a parse error a certain number of
			 * times. If we succeed, the error counter will be reset.
			 */

			errcount++;
			rt_kprintf("read_packet error %d, errcount %d\n",wmares, errcount);
			if (errcount > 5)
			{
				goto done;
			}
			else
			{
				ci->advance_buffer(packetlength);
				goto new_packet;
			}
		}
		else if (res > 0)
		{
			wma_decode_superframe_init(&wmadec, audiobuf, audiobufsize);

			for (i=0; i < wmadec.nb_frames; i++)
			{
				wmares = wma_decode_superframe_frame(&wmadec,
													 decoded,
													 audiobuf, audiobufsize);

				if (wmares < 0)
				{
					/* Do the above, but for errors in decode. */
					errcount++;
					rt_kprintf("WMA decode error %d, errcount %d\n",wmares, errcount);
					if (errcount > 5)
					{
						goto done;
					}
					else
					{
						ci->advance_buffer(packetlength);
						goto new_packet;
					}
				}
				else if (wmares > 0)
				{
					ci->pcmbuf_insert(decoded, NULL, wmares);
				}
			}
		}
	}
	retval = CODEC_OK;

done:
	/*LOGF("WMA: Decoded %ld samples\n",elapsedtime*wfx.rate/1000);*/
	return retval;
}

void wma()
{}
FINSH_FUNCTION_EXPORT(wma, wma test)
