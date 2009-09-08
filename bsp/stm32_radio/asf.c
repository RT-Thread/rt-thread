#include <rtthread.h>
#include <dfs_posix.h>
#include "libwma/asf.h"

#define DEBUGF rt_kprintf

/* always little endian */
#define read_uint16le(fd,buf) read((fd), (buf), 2)
#define read_uint32le(fd,buf) read((fd), (buf), 4)
#define read_uint64le(fd,buf) read((fd), (buf), 8)

struct id3_tag
{
    rt_uint32_t bitrate;		/* bit rate */
    rt_uint32_t frequency;		/* sample frequency */

	rt_size_t first_frame_offset; /* Byte offset to first real MP3 frame.
                                     Used for skipping leading garbage to
                                     avoid gaps between tracks. */

	rt_size_t filesize; 		/* file size; in bytes */
	rt_uint32_t frame_count; 	/* number of frames in the file (if VBR) */
	rt_size_t offset;  			/* bytes played */

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

struct stream_buffer
{
	rt_uint32_t length;
	rt_uint32_t position; /* current position */

	rt_uint8_t *buffer;

	/* file descriptor of this stream buffer */
	int fd;
};

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
static void asf_readGUID(int fd, guid_t* guid)
{
    read_uint32le(fd, &guid->v1);
    read_uint16le(fd, &guid->v2);
    read_uint16le(fd, &guid->v3);
    read(fd, guid->v4, 8);
}

static void asf_read_object_header(asf_object_t *obj, int fd)
{
    asf_readGUID(fd, &obj->guid);
    read_uint64le(fd, &obj->size);
    obj->datalen = 0;
}

/* Parse an integer from the extended content object - we always
   convert to an int, regardless of native format.
*/
static int asf_intdecode(int fd, int type, int length)
{
    rt_uint16_t tmp16;
    rt_uint32_t tmp32;
    rt_uint64_t tmp64;

    if (type==3) {
        read_uint32le(fd, &tmp32);
        lseek(fd,length - 4,SEEK_CUR);
        return (int)tmp32;
    } else if (type==4) {
        read_uint64le(fd, &tmp64);
        lseek(fd,length - 8,SEEK_CUR);
        return (int)tmp64;
    } else if (type == 5) {
        read_uint16le(fd, &tmp16);
        lseek(fd,length - 2,SEEK_CUR);
        return (int)tmp16;
    }

    return 0;
}

/* Decode a LE utf16 string from a disk buffer into a fixed-sized
   utf8 buffer.
*/
static void asf_utf16LEdecode(int fd,
	rt_uint16_t utf16bytes,
	unsigned char **utf8,
	int* utf8bytes)
{
    unsigned long ucs;
    int n;
    unsigned char utf16buf[256];
    unsigned char* utf16 = utf16buf;
    unsigned char* newutf8;

    n = read(fd, utf16buf, MIN(sizeof(utf16buf), utf16bytes));
    utf16bytes -= n;

    while (n > 0) {
        /* Check for a surrogate pair */
        if (utf16[1] >= 0xD8 && utf16[1] < 0xE0) {
            if (n < 4) {
                /* Run out of utf16 bytes, read some more */
                utf16buf[0] = utf16[0];
                utf16buf[1] = utf16[1];

                n = read(fd, utf16buf + 2, MIN(sizeof(utf16buf)-2, utf16bytes));
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
            n = read(fd, utf16buf, MIN(sizeof(utf16buf), utf16bytes));
            utf16 = utf16buf;
            utf16bytes -= n;
        }
    }

    *utf8[0] = 0;
    --*utf8bytes;

    if (utf16bytes > 0) {
        /* Skip any remaining bytes */
        lseek(fd, utf16bytes, SEEK_CUR);
    }
    return;
}

static int asf_parse_header(int fd, struct id3_tag* id3,
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

    asf_read_object_header((asf_object_t *) &header, fd);

    //DEBUGF("header.size=%d\n",(int)header.size);
    if (header.size < 30) {
        /* invalid size for header object */
        return ASF_ERROR_OBJECT_SIZE;
    }

    read_uint32le(fd, &subobjects);

    /* Two reserved bytes - do we need to read them? */
    lseek(fd, 2, SEEK_CUR);

    //DEBUGF("Read header - size=%d, subobjects=%d\n",(int)header.size, (int)subobjects);

    if (subobjects > 0) {
        header.datalen = header.size - 30;

        /* TODO: Check that we have datalen bytes left in the file */
        datalen = header.datalen;

        for (i=0; i<(int)subobjects; i++) {
            //DEBUGF("Parsing header object %d - datalen=%d\n",i,(int)datalen);
            if (datalen < 24) {
                //DEBUGF("not enough data for reading object\n");
                break;
            }

            asf_read_object_header(&current, fd);

            if (current.size > datalen || current.size < 24) {
                //DEBUGF("invalid object size - current.size=%d, datalen=%d\n",(int)current.size,(int)datalen);
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
                    lseek(fd, 40, SEEK_CUR);

                    read_uint64le(fd, &play_duration);
                    id3->length = play_duration / 10000;

                    //DEBUGF("****** length = %lums\n", id3->length);

                    /* Read the packet size - uint32_t at offset 68 */
                    lseek(fd, 20, SEEK_CUR);
                    read_uint32le(fd, &wfx->packet_size);

                    /* Skip bytes remaining in object */
                    lseek(fd, current.size - 24 - 72, SEEK_CUR);
            } else if (asf_guid_match(&current.guid, &asf_guid_stream_properties)) {
                    guid_t guid;
                    rt_uint32_t propdatalen;

                    if (current.size < 78)
                        return ASF_ERROR_OBJECT_SIZE;

                    asf_readGUID(fd, &guid);

                    lseek(fd, 24, SEEK_CUR);
                    read_uint32le(fd, &propdatalen);
                    lseek(fd, 4, SEEK_CUR);
                    read_uint16le(fd, &flags);

                    if (!asf_guid_match(&guid, &asf_guid_stream_type_audio)) {
                        //DEBUGF("Found stream properties for non audio stream, skipping\n");
                        lseek(fd,current.size - 24 - 50,SEEK_CUR);
                    } else if (wfx->audiostream == -1) {
                        lseek(fd, 4, SEEK_CUR);
                        //DEBUGF("Found stream properties for audio stream %d\n",flags&0x7f);

                        if (propdatalen < 18) {
                            return ASF_ERROR_INVALID_LENGTH;
                        }

                        read_uint16le(fd, &wfx->codec_id);
                        read_uint16le(fd, &wfx->channels);
                        read_uint32le(fd, &wfx->rate);
                        read_uint32le(fd, &wfx->bitrate);
                        wfx->bitrate *= 8;
                        read_uint16le(fd, &wfx->blockalign);
                        read_uint16le(fd, &wfx->bitspersample);
                        read_uint16le(fd, &wfx->datalen);

                        /* Round bitrate to the nearest kbit */
                        id3->bitrate = (wfx->bitrate + 500) / 1000;
                        id3->frequency = wfx->rate;

                        if (wfx->codec_id == ASF_CODEC_ID_WMAV1) {
                            read(fd, wfx->data, 4);
                            lseek(fd,current.size - 24 - 72 - 4,SEEK_CUR);
                            wfx->audiostream = flags&0x7f;
                        } else if (wfx->codec_id == ASF_CODEC_ID_WMAV2) {
                            read(fd, wfx->data, 6);
                            lseek(fd,current.size - 24 - 72 - 6,SEEK_CUR);
                            wfx->audiostream = flags&0x7f;
                        } else {
                            DEBUGF("Unsupported WMA codec (Pro, Lossless, Voice, etc)\n");
                            lseek(fd,current.size - 24 - 72,SEEK_CUR);
                        }
                    }
            } else if (asf_guid_match(&current.guid, &asf_guid_content_description)) {
                    /* Object contains five 16-bit string lengths, followed by the five strings:
                       title, artist, copyright, description, rating
                     */
                    rt_uint16_t strlength[5];
                    int i;

                    //DEBUGF("Found GUID_CONTENT_DESCRIPTION - size=%d\n",(int)(current.size - 24));

                    /* Read the 5 string lengths - number of bytes included trailing zero */
                    for (i=0; i<5; i++) {
                        read_uint16le(fd, &strlength[i]);
                        //DEBUGF("strlength = %u\n",strlength[i]);
                    }

                    if (strlength[0] > 0) {  /* 0 - Title */
                        id3->title = id3buf;
                        asf_utf16LEdecode(fd, strlength[0], &id3buf, &id3buf_remaining);
                    }

                    if (strlength[1] > 0) {  /* 1 - Artist */
                        id3->artist = id3buf;
                        asf_utf16LEdecode(fd, strlength[1], &id3buf, &id3buf_remaining);
                    }

                    lseek(fd, strlength[2], SEEK_CUR); /* 2 - copyright */

                    if (strlength[3] > 0) {  /* 3 - description */
                        id3->comment = id3buf;
                        asf_utf16LEdecode(fd, strlength[3], &id3buf, &id3buf_remaining);
                    }

                    lseek(fd, strlength[4], SEEK_CUR); /* 4 - rating */
            } else if (asf_guid_match(&current.guid, &asf_guid_extended_content_description)) {
                    rt_uint16_t count;
                    int i;
                    int bytesleft = current.size - 24;
                    //DEBUGF("Found GUID_EXTENDED_CONTENT_DESCRIPTION\n");

                    read_uint16le(fd, &count);
                    bytesleft -= 2;
                    //DEBUGF("extended metadata count = %u\n",count);

                    for (i=0; i < count; i++) {
                        rt_uint16_t length, type;
                        unsigned char* utf8 = utf8buf;
                        int utf8length = 512;

                        read_uint16le(fd, &length);
                        asf_utf16LEdecode(fd, length, &utf8, &utf8length);
                        bytesleft -= 2 + length;

                        read_uint16le(fd, &type);
                        read_uint16le(fd, &length);

                        if (!strcmp("WM/TrackNumber",utf8buf)) {
                            if (type == 0) {
                                id3->track_string = id3buf;
                                asf_utf16LEdecode(fd, length, &id3buf, &id3buf_remaining);
                                id3->tracknum = atoi(id3->track_string);
                            } else if ((type >=2) && (type <= 5)) {
                                id3->tracknum = asf_intdecode(fd, type, length);
                            } else {
                                lseek(fd, length, SEEK_CUR);
                            }
                        } else if ((!strcmp("WM/Genre",utf8buf)) && (type == 0)) {
                            id3->genre_string = id3buf;
                            asf_utf16LEdecode(fd, length, &id3buf, &id3buf_remaining);
                        } else if ((!strcmp("WM/AlbumTitle",utf8buf)) && (type == 0)) {
                            id3->album = id3buf;
                            asf_utf16LEdecode(fd, length, &id3buf, &id3buf_remaining);
                        } else if ((!strcmp("WM/AlbumArtist",utf8buf)) && (type == 0)) {
                            id3->albumartist = id3buf;
                            asf_utf16LEdecode(fd, length, &id3buf, &id3buf_remaining);
                        } else if ((!strcmp("WM/Composer",utf8buf)) && (type == 0)) {
                            id3->composer = id3buf;
                            asf_utf16LEdecode(fd, length, &id3buf, &id3buf_remaining);
                        } else if (!strcmp("WM/Year",utf8buf)) {
                            if (type == 0) {
                                id3->year_string = id3buf;
                                asf_utf16LEdecode(fd, length, &id3buf, &id3buf_remaining);
                                id3->year = atoi(id3->year_string);
                            } else if ((type >=2) && (type <= 5)) {
                                id3->year = asf_intdecode(fd, type, length);
                            } else {
                                lseek(fd, length, SEEK_CUR);
                            }
                        } else if (!strncmp("replaygain_", utf8buf, 11)) {
                            char* value = id3buf;
                            int buf_len = id3buf_remaining;
                            int len;
                            asf_utf16LEdecode(fd, length, &id3buf, &id3buf_remaining);
                            len = parse_replaygain(utf8buf, value, id3, 
                                value, buf_len);
                            
                            if (len == 0) {
                                /* Don't need to keep the value */
                                id3buf = value;
                                id3buf_remaining = buf_len;
                            }
                        } else if (!strcmp("MusicBrainz/Track Id", utf8buf)) {
                            id3->mb_track_id = id3buf;
                            asf_utf16LEdecode(fd, length, &id3buf, &id3buf_remaining);
                        } else {
                            lseek(fd, length, SEEK_CUR);
                        }
                        bytesleft -= 4 + length;
                    }

                    lseek(fd, bytesleft, SEEK_CUR);
            } else if (asf_guid_match(&current.guid, &asf_guid_content_encryption)
                || asf_guid_match(&current.guid, &asf_guid_extended_content_encryption)) {
                //DEBUGF("File is encrypted\n");
                return ASF_ERROR_ENCRYPTED;
            } else {
                //DEBUGF("Skipping %d bytes of object\n",(int)(current.size - 24));
                lseek(fd,current.size - 24,SEEK_CUR);
            }

            //DEBUGF("Parsed object - size = %d\n",(int)current.size);
            datalen -= current.size;
        }

        if (i != (int)subobjects || datalen != 0) {
            //DEBUGF("header data doesn't match given subobject count\n");
            return ASF_ERROR_INVALID_VALUE;
        }

        //DEBUGF("%d subobjects read successfully\n", i);
    }

    //DEBUGF("header validated correctly\n");

    return 0;
}

static rt_off_t filesize(int fd)
{
    struct dfs_stat buf;

    stat(fd,&buf);
    return buf.st_size;
}

rt_bool_t get_asf_metadata(int fd, struct id3_tag* id3)
{
    int res;
    asf_object_t obj;
    asf_waveformatex_t* wfx;

	wfx = (asf_waveformatex_t*) rt_malloc(sizeof(asf_waveformatex_t));
	if (wfx == RT_NULL) return RT_FALSE;

    wfx->audiostream = -1;

    res = asf_parse_header(fd, id3, wfx);
    if (res < 0) {
        DEBUGF("ASF: parsing error - %d\n",res);
        return RT_FALSE;
    }

    if (wfx->audiostream == -1) {
        DEBUGF("ASF: No WMA streams found\n");
		rt_free(wfx);
        return RT_FALSE;
    }

    asf_read_object_header(&obj, fd);

    if (!asf_guid_match(&obj.guid, &asf_guid_data)) {
        DEBUGF("ASF: No data object found\n");
		rt_free(wfx);
        return RT_FALSE;
    }

    /* Store the current file position - no need to parse the header
       again in the codec.  The +26 skips the rest of the data object
       header.
     */
    id3->first_frame_offset = lseek(fd, 0, SEEK_CUR) + 26;
    id3->filesize = filesize(fd);
	/* set wfx to user data */
	id3->user_data = (rt_uint32_t)wfx;

    return RT_TRUE;
}

