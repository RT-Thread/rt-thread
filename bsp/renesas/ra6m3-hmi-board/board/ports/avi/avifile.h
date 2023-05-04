#ifndef __AVIFILE_H
#define __AVIFILE_H

#include "avi_def.h"

//#define DEBUGINFO //信息打印开关

/** big_endian */
// #define RIFF_ID      0x52494646
// #define AVI_ID       0x41564920
// #define LIST_ID      0x4c495354
// #define hdrl_ID      0x6864726c
// #define avih_ID      0x61766968
// #define strl_ID      0x7374726c
// #define strh_ID      0x73747268
// #define strf_ID      0x73747266
// #define movi_ID      0x6d6f7669
// #define mjpg_ID     0x4D4A5047
// #define vids_ID     0x76696473
// #define auds_ID     0x61756473

/** little_endian */
#define RIFF_ID     _REV(0x52494646)
#define AVI_ID      _REV(0x41564920)
#define LIST_ID     _REV(0x4c495354)
#define hdrl_ID     _REV(0x6864726c)
#define avih_ID     _REV(0x61766968)
#define strl_ID     _REV(0x7374726c)
#define strh_ID     _REV(0x73747268)
#define strf_ID     _REV(0x73747266)
#define movi_ID     _REV(0x6d6f7669)
#define mjpg_ID     _REV(0x4D4A5047)
#define vids_ID     _REV(0x76696473)
#define auds_ID     _REV(0x61756473)

typedef struct
{
    uint32_t  RIFFchunksize;
    uint32_t  LISTchunksize;
    uint32_t  avihsize;
    uint32_t  strlsize;
    uint32_t  strhsize;

    uint32_t movi_start; //数据块的起始位置
    uint32_t movi_size;

    uint16_t vids_fps;
    uint16_t vids_width;
    uint16_t vids_height;

    uint16_t auds_channels;
    uint16_t auds_sample_rate;
    uint16_t auds_bits;

    AVI_HDRL_LIST avi_hd;
} AVI_TypeDef;

#define  MAKEWORD(ptr)  (uint32_t)(((uint32_t)*((uint8_t*)(ptr))<<8)|(uint32_t)*(uint8_t*)((ptr)+1))
#define  MAKEuint32_t(ptr)  (uint32_t)(((uint32_t)*(uint8_t*)(ptr)|(((uint32_t)*(uint8_t*)(ptr+1))<<8)|\
                        (((uint32_t)*(uint8_t*)(ptr+2))<<16)|(((uint32_t)*(uint8_t*)(ptr+3))<<24)))


int AVI_Parser(const uint8_t *buffer, uint32_t length);
uint8_t AVIH_Parser(uint8_t *buffer);

#endif

