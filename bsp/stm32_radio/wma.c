#include <rtthread.h>
#include <dfs_posix.h>

#include "libwma/asf.h"
#include "libwma/wmadec.h"

int packet_count=0;

/* The output buffer containing the decoded samples (channels 0 and 1)
   BLOCK_MAX_SIZE is 2048 (samples) and MAX_CHANNELS is 2.
 */

static rt_uint32_t decoded[BLOCK_MAX_SIZE * MAX_CHANNELS];

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
    ASF_ERROR_SEEK           = -10, /* file is seekable but seeking failed */
    ASF_ERROR_ENCRYPTED      = -11  /* file is encrypted */
};

// #define DEBUGF rt_kprintf

#ifndef MIN
#define MIN(a,b)	((a) < (b) ? (a) : (b))
#endif

/* always little endian */
#define read_uint16le(stream,buf) stream_buffer_read((stream), (rt_uint8_t*)(buf), 2)
#define read_uint32le(stream,buf) stream_buffer_read((stream), (rt_uint8_t*)(buf), 4)
#define read_uint64le(stream,buf) stream_buffer_read((stream), (rt_uint8_t*)(buf), 8)

#define ID3V2_BUF_SIZE 300

struct id3_tag
{
    char* title;
    char* artist;
    char* album;
    char* year_string;
    char* comment;
    char* genre_string;
    char* track_string;
    char* albumartist;
    char* composer;

    /* Musicbrainz Track ID */
    char* mb_track_id;

    int year;
    int tracknum;

    rt_uint32_t bitrate;		/* bit rate */
    rt_uint32_t frequency;		/* sample frequency */
	rt_uint32_t length;			/* length */

	rt_size_t first_frame_offset; /* Byte offset to first real MP3 frame.
                                     Used for skipping leading garbage to
                                     avoid gaps between tracks. */

	rt_uint32_t frame_count; 	/* number of frames in the file (if VBR) */
	rt_size_t offset;  			/* bytes played */

    /* these following two fields are used for local buffering */
    char id3v2buf[ID3V2_BUF_SIZE];
    char id3v1buf[4][92];

	rt_uint32_t user_data;		/* user data */
};

/* TODO: Just read the GUIDs into a 16-byte array, and use memcmp to compare */
struct guid_s {
    rt_uint32_t v1;
    rt_uint16_t v2;
    rt_uint16_t v3;
    rt_uint8_t  v4[8];
};
typedef struct guid_s guid_t;
typedef long long rt_uint64_t;

struct asf_object_s {
    guid_t       	guid;
    rt_uint64_t     size;
    rt_uint64_t     datalen;
};
typedef struct asf_object_s asf_object_t;

static const guid_t asf_guid_null =
{0x00000000, 0x0000, 0x0000, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

/* top level object guids */

static const guid_t asf_guid_header =
{0x75B22630, 0x668E, 0x11CF, {0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C}};

static const guid_t asf_guid_data =
{0x75B22636, 0x668E, 0x11CF, {0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C}};

static const guid_t asf_guid_index =
{0x33000890, 0xE5B1, 0x11CF, {0x89, 0xF4, 0x00, 0xA0, 0xC9, 0x03, 0x49, 0xCB}};

/* header level object guids */

static const guid_t asf_guid_file_properties =
{0x8cabdca1, 0xa947, 0x11cf, {0x8E, 0xe4, 0x00, 0xC0, 0x0C, 0x20, 0x53, 0x65}};

static const guid_t asf_guid_stream_properties =
{0xB7DC0791, 0xA9B7, 0x11CF, {0x8E, 0xE6, 0x00, 0xC0, 0x0C, 0x20, 0x53, 0x65}};

static const guid_t asf_guid_content_description =
{0x75B22633, 0x668E, 0x11CF, {0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C}};

static const guid_t asf_guid_extended_content_description =
{0xD2D0A440, 0xE307, 0x11D2, {0x97, 0xF0, 0x00, 0xA0, 0xC9, 0x5E, 0xA8, 0x50}};

static const guid_t asf_guid_content_encryption =
{0x2211b3fb, 0xbd23, 0x11d2, {0xb4, 0xb7, 0x00, 0xa0, 0xc9, 0x55, 0xfc, 0x6e}};

static const guid_t asf_guid_extended_content_encryption =
{0x298ae614, 0x2622, 0x4c17, {0xb9, 0x35, 0xda, 0xe0, 0x7e, 0xe9, 0x28, 0x9c}};

/* stream type guids */

static const guid_t asf_guid_stream_type_audio =
{0xF8699E40, 0x5B4D, 0x11CF, {0xA8, 0xFD, 0x00, 0x80, 0x5F, 0x5C, 0x44, 0x2B}};

#define STREAM_BUFFER_SIZE		1024
struct stream_buffer
{
	rt_uint32_t length;
	rt_uint32_t position; /* current position in the buffer */

	rt_uint8_t *buffer;
	rt_size_t buffer_size;

	/* file descriptor of this stream buffer */
	int fd;
	rt_bool_t eof;
};

struct stream_buffer* stream;
struct id3_tag _id3;
struct id3_tag* id3;

rt_size_t stream_buffer_read(struct stream_buffer* stream, rt_uint8_t* ptr, rt_size_t len)
{
	rt_size_t rest_bytes;
	
	if (stream->position + len > stream->length)
	{
		rest_bytes = stream->length - stream->position;
		memcpy(ptr, &stream->buffer[stream->position], rest_bytes);
		ptr += rest_bytes;

		/* read more buffer */
		stream->length = read(stream->fd, &stream->buffer[0], stream->buffer_size);

		if (stream->length < len - rest_bytes)
		{
			stream->position = stream->length;
			stream->eof = RT_TRUE;
		}
		else 
			stream->position = len - rest_bytes;

		memcpy(ptr, &stream->buffer[0], stream->position);
		return rest_bytes + stream->position;
	}

	memcpy(ptr, &stream->buffer[stream->position], len);
	stream->position += len;

	return len;
}

void stream_buffer_advance(struct stream_buffer* stream, rt_size_t size)
{
	if (stream->position + size < stream->length)
	{
		stream->position += size;
		return;
	}

	stream->position = size - (stream->length - stream->position);
	stream->length = read(stream->fd, stream->buffer, stream->buffer_size);
	if (stream->length < stream->position) stream->eof = RT_TRUE;
};

rt_uint8_t *stream_buffer_request(struct stream_buffer* stream, rt_size_t *r_size, rt_size_t size)
{
	rt_size_t rest_bytes, read_bytes, read_result;

	if (size > stream->buffer_size) return RT_NULL; /* request size more than the buffer size */

	if (stream->position + size < stream->length)
	{
		*r_size = size;
		return &stream->buffer[stream->position];
	}

	/* read more data */
	rest_bytes = stream->length - stream->position;
	memmove(&stream->buffer[0], &stream->buffer[stream->position], rest_bytes);

	read_bytes = stream->buffer_size - rest_bytes;
	read_bytes = (read_bytes / 512) * 512; /* align to 512 */

	read_result = read(stream->fd, &stream->buffer[rest_bytes], read_bytes);
	stream->position = 0;
	stream->length = read_result + rest_bytes;
	*r_size = size;

	return &stream->buffer[0];
}

struct stream_buffer* stream_buffer_create(int fd)
{
	struct stream_buffer* buffer = (struct stream_buffer*) rt_malloc(sizeof(struct stream_buffer));
	if (buffer != RT_NULL)
	{
		buffer->fd = fd;
		buffer->eof = RT_FALSE;

		buffer->length = 0;
		buffer->position = 0;

		buffer->buffer_size = STREAM_BUFFER_SIZE;
		buffer->buffer = rt_malloc(buffer->buffer_size);
	}

	return buffer;
}

void stream_buffer_close(struct stream_buffer* stream)
{
	rt_free(stream->buffer);
	close(stream->fd);
}

static int asf_guid_match(const guid_t *guid1, const guid_t *guid2)
{
    if((guid1->v1 != guid2->v1) ||
       (guid1->v2 != guid2->v2) ||
       (guid1->v3 != guid2->v3) ||
       (rt_memcmp(guid1->v4, guid2->v4, 8)))
	{
        return 0;
    }

    return 1;
}

/* Read the 16 byte GUID from a file */
static void asf_readGUID(struct stream_buffer* stream, guid_t* guid)
{
    read_uint32le(stream, &guid->v1);
    read_uint16le(stream, &guid->v2);
    read_uint16le(stream, &guid->v3);
    stream_buffer_read(stream, guid->v4, 8);
}

static void asf_read_object_header(asf_object_t *obj, struct stream_buffer* stream)
{
    asf_readGUID(stream, &obj->guid);
    read_uint64le(stream, &obj->size);
    obj->datalen = 0;
}

/* Parse an integer from the extended content object - we always
   convert to an int, regardless of native format.
*/
static int asf_intdecode(struct stream_buffer* stream, int type, int length)
{
    rt_uint16_t tmp16;
    rt_uint32_t tmp32;
    rt_uint64_t tmp64;

    if (type==3) {
        read_uint32le(stream, &tmp32);
        stream_buffer_advance(stream,length - 4);
        return (int)tmp32;
    } else if (type==4) {
        read_uint64le(stream, &tmp64);
        stream_buffer_advance(stream,length - 8);
        return (int)tmp64;
    } else if (type == 5) {
        read_uint16le(stream, &tmp16);
        stream_buffer_advance(stream,length - 2);
        return (int)tmp16;
    }

    return 0;
}

#define MASK   0xC0 /* 11000000 */
#define COMP   0x80 /* 10x      */
static const unsigned char utf8comp[6] =
{
    0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC
};
/* Encode a UCS value as UTF-8 and return a pointer after this UTF-8 char. */
unsigned char* utf8encode(unsigned long ucs, unsigned char *utf8)
{
    int tail = 0;

    if (ucs > 0x7F)
        while (ucs >> (5*tail + 6))
            tail++;

    *utf8++ = (ucs >> (6*tail)) | utf8comp[tail];
    while (tail--)
        *utf8++ = ((ucs >> (6*tail)) & (MASK ^ 0xFF)) | COMP;

    return utf8;
}

/* Decode a LE utf16 string from a disk buffer into a fixed-sized
   utf8 buffer.
*/
static void asf_utf16LEdecode(struct stream_buffer* stream,
	rt_uint16_t utf16bytes,
	unsigned char **utf8,
	int* utf8bytes)
{
    unsigned long ucs;
    int n;
    unsigned char utf16buf[256];
    unsigned char* utf16 = utf16buf;
    unsigned char* newutf8;

    n = stream_buffer_read(stream, utf16buf, MIN(sizeof(utf16buf), utf16bytes));
    utf16bytes -= n;

    while (n > 0) {
        /* Check for a surrogate pair */
        if (utf16[1] >= 0xD8 && utf16[1] < 0xE0) {
            if (n < 4) {
                /* Run out of utf16 bytes, read some more */
                utf16buf[0] = utf16[0];
                utf16buf[1] = utf16[1];

                n = stream_buffer_read(stream, utf16buf + 2, MIN(sizeof(utf16buf)-2, utf16bytes));
                utf16 = utf16buf;
                utf16bytes -= n;
                n += 2;
            }

            if (n < 4) {
                /* Truncated utf16 string, abort */
                break;
            }
            ucs = 0x10000 + ((utf16[0] << 10) | ((utf16[1] - 0xD8) << 18)
                             | utf16[2] | ((utf16[3] - 0xDC) << 8));
            utf16 += 4;
            n -= 4;
        } else {
            ucs = (utf16[0] | (utf16[1] << 8));
            utf16 += 2;
            n -= 2;
        }

        if (*utf8bytes > 6) {
            newutf8 = utf8encode(ucs, *utf8);
            *utf8bytes -= (newutf8 - *utf8);
            *utf8 += (newutf8 - *utf8);
        }

        /* We have run out of utf16 bytes, read more if available */
        if ((n == 0) && (utf16bytes > 0)) {
            n = stream_buffer_read(stream, utf16buf, MIN(sizeof(utf16buf), utf16bytes));
            utf16 = utf16buf;
            utf16bytes -= n;
        }
    }

    *utf8[0] = 0;
    --*utf8bytes;

    if (utf16bytes > 0) {
        /* Skip any remaining bytes */
        stream_buffer_advance(stream, utf16bytes);
    }
    return;
}

static int asf_parse_header(struct stream_buffer* stream, struct id3_tag* id3,
                                    asf_waveformatex_t* wfx)
{
    asf_object_t current;
    asf_object_t header;
    rt_uint64_t datalen;
    int i;
    int fileprop = 0;
    rt_uint64_t play_duration;
    rt_uint16_t flags;
    rt_uint32_t subobjects;
    rt_uint8_t utf8buf[512];
    int id3buf_remaining = sizeof(id3->id3v2buf) + sizeof(id3->id3v1buf);
    unsigned char* id3buf = (unsigned char*)id3->id3v2buf;

    asf_read_object_header((asf_object_t *) &header, stream);

    DEBUGF("header.size=%d\n",(int)header.size);
    if (header.size < 30) {
        /* invalid size for header object */
        return ASF_ERROR_OBJECT_SIZE;
    }

    read_uint32le(stream, &subobjects);

    /* Two reserved bytes - do we need to read them? */
    stream_buffer_advance(stream, 2);

    DEBUGF("Read header - size=%d, subobjects=%d\n",(int)header.size, (int)subobjects);

    if (subobjects > 0) {
        header.datalen = header.size - 30;

        /* TODO: Check that we have datalen bytes left in the file */
        datalen = header.datalen;

        for (i=0; i<(int)subobjects; i++) {
            DEBUGF("Parsing header object %d - datalen=%d\n",i,(int)datalen);
            if (datalen < 24) {
                DEBUGF("not enough data for reading object\n");
                break;
            }

            asf_read_object_header(&current, stream);

            if (current.size > datalen || current.size < 24) {
                DEBUGF("invalid object size - current.size=%d, datalen=%d\n",(int)current.size,(int)datalen);
                break;
            }

            if (asf_guid_match(&current.guid, &asf_guid_file_properties)) {
                    if (current.size < 104)
                        return ASF_ERROR_OBJECT_SIZE;

                    if (fileprop) {
                        /* multiple file properties objects not allowed */
                        return ASF_ERROR_INVALID_OBJECT;
                    }

                    fileprop = 1;
                    /* All we want is the play duration - uint64_t at offset 40 */
                    stream_buffer_advance(stream, 40);

                    read_uint64le(stream, &play_duration);
                    id3->length = play_duration / 10000;

                    DEBUGF("****** length = %lums\n", id3->length);

                    /* Read the packet size - uint32_t at offset 68 */
                    stream_buffer_advance(stream, 20);
                    read_uint32le(stream, &wfx->packet_size);

                    /* Skip bytes remaining in object */
                    stream_buffer_advance(stream, current.size - 24 - 72);
            } else if (asf_guid_match(&current.guid, &asf_guid_stream_properties)) {
                    guid_t guid;
                    rt_uint32_t propdatalen;

                    if (current.size < 78)
                        return ASF_ERROR_OBJECT_SIZE;

                    asf_readGUID(stream, &guid);

                    stream_buffer_advance(stream, 24);
                    read_uint32le(stream, &propdatalen);
                    stream_buffer_advance(stream, 4);
                    read_uint16le(stream, &flags);

                    if (!asf_guid_match(&guid, &asf_guid_stream_type_audio)) {
                        DEBUGF("Found stream properties for non audio stream, skipping\n");
                        stream_buffer_advance(stream,current.size - 24 - 50);
                    } else if (wfx->audiostream == -1) {
                        stream_buffer_advance(stream, 4);
                        DEBUGF("Found stream properties for audio stream %d\n",flags&0x7f);

                        if (propdatalen < 18) {
                            return ASF_ERROR_INVALID_LENGTH;
                        }

                        read_uint16le(stream, &wfx->codec_id);
                        read_uint16le(stream, &wfx->channels);
                        read_uint32le(stream, &wfx->rate);
                        read_uint32le(stream, &wfx->bitrate);
                        wfx->bitrate *= 8;
                        read_uint16le(stream, &wfx->blockalign);
                        read_uint16le(stream, &wfx->bitspersample);
                        read_uint16le(stream, &wfx->datalen);

                        /* Round bitrate to the nearest kbit */
                        id3->bitrate = (wfx->bitrate + 500) / 1000;
                        id3->frequency = wfx->rate;

                        if (wfx->codec_id == ASF_CODEC_ID_WMAV1) {
                            stream_buffer_read(stream, wfx->data, 4);
                            stream_buffer_advance(stream, current.size - 24 - 72 - 4);
                            wfx->audiostream = flags&0x7f;
                        } else if (wfx->codec_id == ASF_CODEC_ID_WMAV2) {
                            stream_buffer_read(stream, wfx->data, 6);
                            stream_buffer_advance(stream,current.size - 24 - 72 - 6);
                            wfx->audiostream = flags&0x7f;
                        } else {
                            DEBUGF("Unsupported WMA codec (Pro, Lossless, Voice, etc)\n");
                            stream_buffer_advance(stream,current.size - 24 - 72);
                        }
                    }
            } else if (asf_guid_match(&current.guid, &asf_guid_content_description)) {
                    /* Object contains five 16-bit string lengths, followed by the five strings:
                       title, artist, copyright, description, rating
                     */
                    rt_uint16_t strlength[5];
                    int i;

                    DEBUGF("Found GUID_CONTENT_DESCRIPTION - size=%d\n",(int)(current.size - 24));

                    /* Read the 5 string lengths - number of bytes included trailing zero */
                    for (i=0; i<5; i++) {
                        read_uint16le(stream, &strlength[i]);
                        DEBUGF("strlength = %u\n",strlength[i]);
                    }

                    if (strlength[0] > 0) {  /* 0 - Title */
                        id3->title = id3buf;
                        asf_utf16LEdecode(stream, strlength[0], &id3buf, &id3buf_remaining);
                    }

                    if (strlength[1] > 0) {  /* 1 - Artist */
                        id3->artist = id3buf;
                        asf_utf16LEdecode(stream, strlength[1], &id3buf, &id3buf_remaining);
                    }

                    stream_buffer_advance(stream, strlength[2]); /* 2 - copyright */

                    if (strlength[3] > 0) {  /* 3 - description */
                        id3->comment = id3buf;
                        asf_utf16LEdecode(stream, strlength[3], &id3buf, &id3buf_remaining);
                    }

                    stream_buffer_advance(stream, strlength[4]); /* 4 - rating */
            } else if (asf_guid_match(&current.guid, &asf_guid_extended_content_description)) {
                    rt_uint16_t count;
                    int i;
                    int bytesleft = current.size - 24;
                    DEBUGF("Found GUID_EXTENDED_CONTENT_DESCRIPTION\n");

                    read_uint16le(stream, &count);
                    bytesleft -= 2;
                    DEBUGF("extended metadata count = %u\n",count);

                    for (i=0; i < count; i++) {
                        rt_uint16_t length, type;
                        unsigned char* utf8 = utf8buf;
                        int utf8length = 512;

                        read_uint16le(stream, &length);
                        asf_utf16LEdecode(stream, length, &utf8, &utf8length);
                        bytesleft -= 2 + length;

                        read_uint16le(stream, &type);
                        read_uint16le(stream, &length);

                        if (!strcmp("WM/TrackNumber",utf8buf)) {
                            if (type == 0) {
                                id3->track_string = id3buf;
                                asf_utf16LEdecode(stream, length, &id3buf, &id3buf_remaining);
                                id3->tracknum = atoi(id3->track_string);
                            } else if ((type >=2) && (type <= 5)) {
                                id3->tracknum = asf_intdecode(stream, type, length);
                            } else {
                                stream_buffer_advance(stream, length);
                            }
                        } else if ((!strcmp("WM/Genre",utf8buf)) && (type == 0)) {
                            id3->genre_string = id3buf;
                            asf_utf16LEdecode(stream, length, &id3buf, &id3buf_remaining);
                        } else if ((!strcmp("WM/AlbumTitle",utf8buf)) && (type == 0)) {
                            id3->album = id3buf;
                            asf_utf16LEdecode(stream, length, &id3buf, &id3buf_remaining);
                        } else if ((!strcmp("WM/AlbumArtist",utf8buf)) && (type == 0)) {
                            id3->albumartist = id3buf;
                            asf_utf16LEdecode(stream, length, &id3buf, &id3buf_remaining);
                        } else if ((!strcmp("WM/Composer",utf8buf)) && (type == 0)) {
                            id3->composer = id3buf;
                            asf_utf16LEdecode(stream, length, &id3buf, &id3buf_remaining);
                        } else if (!strcmp("WM/Year",utf8buf)) {
                            if (type == 0) {
                                id3->year_string = id3buf;
                                asf_utf16LEdecode(stream, length, &id3buf, &id3buf_remaining);
                                id3->year = atoi(id3->year_string);
                            } else if ((type >=2) && (type <= 5)) {
                                id3->year = asf_intdecode(stream, type, length);
                            } else {
                                stream_buffer_advance(stream, length);
                            }
                        } else if (!strncmp("replaygain_", utf8buf, 11)) {
                            char* value = id3buf;
                            int buf_len = id3buf_remaining;
                            int len;
                            asf_utf16LEdecode(stream, length, &id3buf, &id3buf_remaining);
                            len = 0; // parse_replaygain(utf8buf, value, id3, value, buf_len);
                            
                            if (len == 0) {
                                /* Don't need to keep the value */
                                id3buf = value;
                                id3buf_remaining = buf_len;
                            }
                        } else if (!strcmp("MusicBrainz/Track Id", utf8buf)) {
                            id3->mb_track_id = id3buf;
                            asf_utf16LEdecode(stream, length, &id3buf, &id3buf_remaining);
                        } else {
                            stream_buffer_advance(stream, length);
                        }
                        bytesleft -= 4 + length;
                    }

                    stream_buffer_advance(stream, bytesleft);
            } else if (asf_guid_match(&current.guid, &asf_guid_content_encryption)
                || asf_guid_match(&current.guid, &asf_guid_extended_content_encryption)) {
                DEBUGF("File is encrypted\n");
                return ASF_ERROR_ENCRYPTED;
            } else {
                DEBUGF("Skipping %d bytes of object\n",(int)(current.size - 24));
                stream_buffer_advance(stream,current.size - 24);
            }

            DEBUGF("Parsed object - size = %d\n",(int)current.size);
            datalen -= current.size;
        }

        if (i != (int)subobjects || datalen != 0) {
            DEBUGF("header data doesn't match given subobject count\n");
            return ASF_ERROR_INVALID_VALUE;
        }

        DEBUGF("%d subobjects read successfully\n", i);
    }

    DEBUGF("header validated correctly\n");

    return 0;
}

rt_bool_t get_asf_metadata(struct stream_buffer* stream, struct id3_tag* id3)
{
    int res;
    asf_object_t obj;
    asf_waveformatex_t* wfx;

	wfx = (asf_waveformatex_t*) rt_malloc(sizeof(asf_waveformatex_t));
	if (wfx == RT_NULL) return RT_FALSE;

    wfx->audiostream = -1;

    res = asf_parse_header(stream, id3, wfx);
    if (res < 0) {
        DEBUGF("ASF: parsing error - %d\n",res);
        return RT_FALSE;
    }

    if (wfx->audiostream == -1) {
        DEBUGF("ASF: No WMA streams found\n");
		rt_free(wfx);
        return RT_FALSE;
    }

    asf_read_object_header(&obj, stream);

    if (!asf_guid_match(&obj.guid, &asf_guid_data)) {
        DEBUGF("ASF: No data object found\n");
		rt_free(wfx);
        return RT_FALSE;
    }

    /* Store the current file position - no need to parse the header
       again in the codec.  The +26 skips the rest of the data object
       header.
     */
    id3->first_frame_offset = 26;
	/* set wfx to user data */
	id3->user_data = (rt_uint32_t)wfx;

    return RT_TRUE;
}


/* Read an unaligned 32-bit little endian long from buffer. */
static unsigned long get_long_le(void* buf)
{
    unsigned char* p = (unsigned char*) buf;

    return p[0] | (p[1] << 8) | (p[2] << 16) | (p[3] << 24);
}

/* Read an unaligned 16-bit little endian short from buffer. */
static unsigned short get_short_le(void* buf)
{
    unsigned char* p = (unsigned char*) buf;

    return p[0] | (p[1] << 8);
}

#define GETLEN2b(bits) (((bits) == 0x03) ? 4 : bits)

#define GETVALUE2b(bits, data) \
        (((bits) != 0x03) ? ((bits) != 0x02) ? ((bits) != 0x01) ? \
         0 : *(data) : get_short_le(data) : get_long_le(data))

static int asf_read_packet(rt_uint8_t** audiobuf, int* audiobufsize, int* packetlength, asf_waveformatex_t* wfx)
{
    rt_uint8_t tmp8, packet_flags, packet_property;
    int stream_id;
    int ec_length, opaque_data, ec_length_type;
    int datalen;
    rt_uint8_t data[18];
    rt_uint8_t* datap;
    rt_uint32_t length;
    rt_uint32_t padding_length;
    rt_uint32_t send_time;
    rt_uint16_t duration;
    rt_uint16_t payload_count;
    int payload_length_type;
    rt_uint32_t payload_hdrlen;
    int payload_datalen;
    int multiple;
    rt_uint32_t replicated_length;
    rt_uint32_t media_object_number;
    rt_uint32_t media_object_offset;
    rt_uint32_t bytesread = 0;
    rt_uint8_t* buf;
    size_t bufsize;
    int i;
    /*DEBUGF("Reading new packet at %d bytes ", (int)ci->curpos);*/

    if (stream_buffer_read(stream, &tmp8, 1) == 0) {
        return ASF_ERROR_EOF;
    }
    bytesread++;

    /* TODO: We need a better way to detect endofstream */
    if (tmp8 != 0x82) {
    DEBUGF("Read failed:  packet did not sync\n");
    return -1;
    }


    if (tmp8 & 0x80) {
       ec_length = tmp8 & 0x0f;
       opaque_data = (tmp8 >> 4) & 0x01;
       ec_length_type = (tmp8 >> 5) & 0x03;

       if (ec_length_type != 0x00 || opaque_data != 0 || ec_length != 0x02) {
            DEBUGF("incorrect error correction flags\n");
            return ASF_ERROR_INVALID_VALUE;
       }

       /* Skip ec_data */
       stream_buffer_advance(stream, ec_length);
       bytesread += ec_length;
    } else {
        ec_length = 0;
    }

    if (stream_buffer_read(stream, &packet_flags, 1) == 0) { return ASF_ERROR_EOF; }
    if (stream_buffer_read(stream, &packet_property, 1) == 0) { return ASF_ERROR_EOF; }
    bytesread += 2;

    datalen = GETLEN2b((packet_flags >> 1) & 0x03) +
              GETLEN2b((packet_flags >> 3) & 0x03) +
              GETLEN2b((packet_flags >> 5) & 0x03) + 6;

    if (stream_buffer_read(stream, data, datalen) == 0) {
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
    /*DEBUGF("and duration %d ms\n", duration);*/

    /* this is really idiotic, packet length can (and often will) be
     * undefined and we just have to use the header packet size as the size
     * value */
    if (!((packet_flags >> 5) & 0x03)) {
         length = wfx->packet_size;
    }

    /* this is also really idiotic, if packet length is smaller than packet
     * size, we need to manually add the additional bytes into padding length
     */
    if (length < wfx->packet_size) {
        padding_length += wfx->packet_size - length;
        length = wfx->packet_size;
    }

    if (length > wfx->packet_size) {
        DEBUGF("packet with too big length value\n");
        return ASF_ERROR_INVALID_LENGTH;
    }

    /* check if we have multiple payloads */
    if (packet_flags & 0x01) {
        if (stream_buffer_read(stream, &tmp8, 1) == 0) {
            return ASF_ERROR_EOF;
        }
        payload_count = tmp8 & 0x3f;
        payload_length_type = (tmp8 >> 6) & 0x03;
        bytesread++;
    } else {
        payload_count = 1;
        payload_length_type = 0x02; /* not used */
    }

    if (length < bytesread) {
        DEBUGF("header exceeded packet size, invalid file - length=%d, bytesread=%d\n",(int)length,(int)bytesread);
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

    buf = stream_buffer_request(stream, &bufsize, length);
    datap = buf;

    if (bufsize != length) {
        /* This should only happen with packets larger than 32KB (the
           guard buffer size).  All the streams I've seen have
           relatively small packets less than about 8KB), but I don't
           know what is expected.
        */
        DEBUGF("Could not read packet (requested %d bytes, received %d), aborting\n",
               (int)length,(int)bufsize);
        return -1;
    }

    for (i=0; i<payload_count; i++) {
        stream_id = datap[0]&0x7f;
        datap++;
        bytesread++;

        payload_hdrlen = GETLEN2b(packet_property & 0x03) +
                         GETLEN2b((packet_property >> 2) & 0x03) +
                         GETLEN2b((packet_property >> 4) & 0x03);

        //DEBUGF("payload_hdrlen = %d\n",payload_hdrlen);
        if (payload_hdrlen > sizeof(data)) {
            DEBUGF("Unexpectedly long datalen in data - %d\n",datalen);
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


        if (multiple) {
            int x;

            x = GETLEN2b(payload_length_type);

            if (x != 2) {
                /* in multiple payloads datalen should be a word */
                return ASF_ERROR_INVALID_VALUE;
            }

            payload_datalen = GETVALUE2b(payload_length_type, datap);
            datap += x;
            bytesread += x;
        } else {
            payload_datalen = length - bytesread - padding_length;
        }

        if (replicated_length==1)
            datap++;

        if (stream_id == wfx->audiostream)
        {
            if (*audiobuf == NULL) {
                /* The first payload can stay where it is */
                *audiobuf = datap;
                *audiobufsize = payload_datalen;
            } else {
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

#include <finsh.h>
/* this is the codec entry point */
void wma(const char* filename)
{
    rt_uint32_t elapsedtime;
    asf_waveformatex_t* wfx;
    int i;
    int wmares, res;
    rt_uint8_t* audiobuf;
    int audiobufsize;
    int packetlength = 0;
    int errcount = 0;
	rt_device_t snd = RT_NULL;

	int fd;

	snd = rt_device_find("snd");
	if (snd == RT_NULL)
	{
		rt_kprintf("open audio device failed\n");
		return;
	}

	rt_device_open(snd, RT_DEVICE_OFLAG_RDONLY);

	fd = open(filename, O_RDONLY, 0);
	if (fd < 0)
	{
		rt_kprintf("open file: %s failed\n", filename);
		return ;
	}

	/* create stream */
	stream = stream_buffer_create(fd);
	id3 = &_id3;
	/* get meta information */
	get_asf_metadata(stream, id3);

	wfx = (asf_waveformatex_t*)id3->user_data;

    if (wma_decode_init(&wmadec, wfx) < 0) {
        DEBUGF("WMA: Unsupported or corrupt file\n");
        goto exit;
    }

    DEBUGF("**************** IN WMA.C ******************\n");

    /* The main decoding loop */

    res = 1;
    while (res >= 0)
    {
        errcount = 0;
new_packet:
        res = asf_read_packet(&audiobuf, &audiobufsize, &packetlength, wfx);

        if (res < 0) {
            /* We'll try to recover from a parse error a certain number of
             * times. If we succeed, the error counter will be reset.
             */
            errcount++;
            DEBUGF("read_packet error %d, errcount %d\n",wmares, errcount);
            if (errcount > 5) {
                goto done;
            } else {
       	 		stream_buffer_advance(stream, packetlength);
                goto new_packet;
            }
        } else if (res > 0) {
            wma_decode_superframe_init(&wmadec, audiobuf, audiobufsize);

            for (i=0; i < wmadec.nb_frames; i++)
            {
                wmares = wma_decode_superframe_frame(&wmadec,
                                                     decoded,
                                                     audiobuf, audiobufsize);

                if (wmares < 0) {
                    /* Do the above, but for errors in decode. */
                    errcount++;
                    DEBUGF("WMA decode error %d, errcount %d\n",wmares, errcount);
                    if (errcount > 5) {
                        goto done;
                    } else {
                        stream_buffer_advance(stream, packetlength);
                        goto new_packet;
                    }
                } else if (wmares > 0) {
                	/* write to audio device */
                    elapsedtime += (wmares*10)/(wfx->rate/100);
                    // ci->set_elapsed(elapsedtime);
                }
            }
        }

        stream_buffer_advance(stream, packetlength);
    }

done:
exit:
	stream_buffer_close(stream);
	stream = RT_NULL;

    return ;
}
FINSH_FUNCTION_EXPORT(wma, wma decode test)

