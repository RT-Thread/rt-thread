#ifndef _ASF_H
#define _ASF_H

#include <inttypes.h>

/* ASF codec IDs */
#define ASF_CODEC_ID_WMAV1 0x160
#define ASF_CODEC_ID_WMAV2 0x161

struct asf_waveformatex_s {
        uint32_t packet_size;
        int audiostream;
	uint16_t codec_id;
	uint16_t channels;
	uint32_t rate;
	uint32_t bitrate;
	uint16_t blockalign;
	uint16_t bitspersample;
	uint16_t datalen;
	uint8_t data[6];
};
typedef struct asf_waveformatex_s asf_waveformatex_t;

#endif
