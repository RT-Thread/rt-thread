/**************************************************************************//**
* @file     jpegcodec.h
* @brief    N9H30 JPEG driver header file
*
* @note
* SPDX-License-Identifier: Apache-2.0
* Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#ifndef __NU_JPEGCODEC_H__
#define __NU_JPEGCODEC_H__

//Include header file
#include "N9H30.h"
#include "nu_sys.h"


/** @addtogroup N9H30_Device_Driver N9H30 Device Driver
  @{
*/

/** @addtogroup N9H30_JPEG_Driver JPEG Driver
  @{
*/


/** @addtogroup N9H30_JPEG_EXPORTED_CONSTANTS JPEG Exported Constants
  @{
*/

#define E_FAIL      0             /*!< JPEG function Error */
#define E_SUCCESS   1             /*!< JPEG function Success */
#define E_JPEG_INVALID_PARAM 2    /*!< Input invalid paramater */
#define E_JPEG_TIMEOUT  3         /*!< JPEG function Time-out */


#define JPEG_ENC_PRIMARY        0   /*!< JPEG encode Primary */
#define JPEG_ENC_THUMBNAIL  1       /*!< JPEG encode Thumbanil */

//Define for Encode input Format
#define JPEG_ENC_SOURCE_PLANAR  0   /*!< JPEG encode input formate is Planar */
#define JPEG_ENC_SOURCE_PACKET  1   /*!< JPEG encode input formate is Packet */

//Define for Decode Output Format

//(PLANAR_ON | PDHTAB | DHEND)
#define JPEG_DEC_PRIMARY_PLANAR_YUV     0x8021  /*!< JPEG decode output Primary Planar YUV */
//(PDHTAB | DHEND)
#define JPEG_DEC_PRIMARY_PACKET_YUV422  0x0021  /*!< JPEG decode output Primary Packet YUV422 */

//(PDHTAB | DHEND | ORDER)
#define JPEG_DEC_PRIMARY_PACKET_RGB555  0x04021  /*!< JPEG decode output Primary Packet RGB555 */
//(PDHTAB | DHEND | RGB555_565 | ORDER )
#define JPEG_DEC_PRIMARY_PACKET_RGB565  0x06021  /*!< JPEG decode output Primary Packet RGB565 */

//(PDHTAB | DHEND | ORDER)
#define JPEG_DEC_PRIMARY_PACKET_RGB555R1    0x404021  /*!< JPEG decode output Primary Packet RGB555R1 */
//(PDHTAB | DHEND | RGB555_565 | ORDER )
#define JPEG_DEC_PRIMARY_PACKET_RGB565R1    0x406021  /*!< JPEG decode output Primary Packet RGB565R1 */

#define JPEG_DEC_PRIMARY_PACKET_RGB565R2    0x806021  /*!< JPEG decode output Primary Packet RGB565R2 */
//(PDHTAB | DHEND | ORDER)
#define JPEG_DEC_PRIMARY_PACKET_RGB555R2    0x804021  /*!< JPEG decode output Primary Packet RGB555R2 */

//(PDHTAB | DHEND | RGB555_565 | ORDER )
#define JPEG_DEC_PRIMARY_PACKET_RGB888  0x14021  /*!< JPEG decode Primary Packet RGB888 */
//(PLANAR_ON | DTHB | PDHTAB)
#define JPEG_DEC_THUMBNAIL_PLANAR_YUV   0x8031  /*!< JPEG decode Thumbnail Planar YUV */
//(DTHB | PDHTAB | DHEND)
#define JPEG_DEC_THUMBNAIL_PACKET_YUV422    0x0031  /*!< JPEG decode Thumbnail Packet YUV422 */
//(DTHB | PDHTAB | DHEND | ORDER)
#define JPEG_DEC_THUMBNAIL_PACKET_RGB555    0x4031  /*!< JPEG decode Thumbnail Packet RGB555 */

//Define for Encode Image Format
#define JPEG_ENC_PRIMARY_YUV420     0xA0  /*!< JPEG encode Primary YUV420 */
#define JPEG_ENC_PRIMARY_YUV422     0xA8  /*!< JPEG encode Primary YUV422 */
#define JPEG_ENC_PRIMARY_GRAY       0xA1  /*!< JPEG encode Primary Gray */
#define JPEG_ENC_THUMBNAIL_YUV420   0x90  /*!< JPEG encode Thumbnail YUV420 */
#define JPEG_ENC_THUMBNAIL_YUV422   0x98  /*!< JPEG encode Thumbnail YUV422 */
#define JPEG_ENC_THUMBNAIL_GRAY     0x91  /*!< JPEG encode Thumbnail Gray */

//Define for Decode Image Format
#define JPEG_DEC_YUV420     0x000  /*!< JPEG decode image formatr is YUV420 */
#define JPEG_DEC_YUV422     0x100  /*!< JPEG decode image formatr is YUV422 */
#define JPEG_DEC_YUV444     0x200  /*!< JPEG decode image formatr is YUV444 */
#define JPEG_DEC_YUV411     0x300  /*!< JPEG decode image formatr is YUV411 */
#define JPEG_DEC_GRAY       0x400  /*!< JPEG decode image formatr is Gray */
#define JPEG_DEC_YUV422T    0x500  /*!< JPEG decode image formatr is YUV422T */

//Define for Encode Image Header
/*P_DRI*/
#define JPEG_ENC_PRIMARY_DRI    0x10  /*!< JPEG encode image header Primary DRI */
/*P_QTAB*/
#define JPEG_ENC_PRIMARY_QTAB   0x20  /*!< JPEG encode image header Primary Q Table */
/*P_HTAB*/
#define JPEG_ENC_PRIMARY_HTAB   0x40  /*!< JPEG encode image header Primary H Table */
/*P_JFIF*/
#define JPEG_ENC_PRIMARY_JFIF   0x80  /*!< JPEG encode image header Primary JFIF */
/*T_DRI*/
#define JPEG_ENC_THUMBNAIL_DRI  0x1  /*!< JPEG encode image header Thumbnail DRI */
/*T_QTAB*/
#define JPEG_ENC_THUMBNAIL_QTAB 0x2  /*!< JPEG encode image header Thumbnail Q Table */
/*T_HTAB*/
#define JPEG_ENC_THUMBNAIL_HTAB 0x4  /*!< JPEG encode image header Thumbnail H Table */
/*T_JFIF*/
#define JPEG_ENC_THUMBNAIL_JFIF 0x8  /*!< JPEG encode image header Thumbnail JFIF */


#define JPEG_IOCTL_SET_YADDR                                0    /*!< Set Y Component Frame Buffer-0 Starting Address Register  */
#define JPEG_IOCTL_SET_YSTRIDE                              1    /*!< Set Y Component Frame Buffer Stride Register  */
#define JPEG_IOCTL_SET_USTRIDE                              2    /*!< Set U Component Frame Buffer Stride Register  */
#define JPEG_IOCTL_SET_VSTRIDE                              3    /*!< Set V Component Frame Buffer Stride Register  */
#define JPEG_IOCTL_SET_BITSTREAM_ADDR                       4    /*!< Set Bit-stream Frame Buffer-0 Starting Address Register  */
#define JPEG_IOCTL_SET_SOURCE_IMAGE_HEIGHT                  5    /*!< Set JPEG Bit-stream FIFO Control Register */
#define JPEG_IOCTL_ENC_SET_HEADER_CONTROL                   6    /*!< Set JPEG Encode Header Control Register  */
#define JPEG_IOCTL_SET_DEFAULT_QTAB                         7    /*!< Set Default Q Table  */
#define JPEG_IOCTL_SET_DECODE_MODE                          8    /*!< Set Decode Mode  */
#define JPEG_IOCTL_SET_ENCODE_MODE                          9    /*!< Set Encode Mode  */
#define JPEG_IOCTL_SET_DIMENSION                            10   /*!< Set Encode Primary Width/Height  */
#define JPEG_IOCTL_ENCODE_TRIGGER                           11   /*!< Encode Trigger  */
#define JPEG_IOCTL_DECODE_TRIGGER                           12   /*!< Decode Trigger  */
#define JPEG_IOCTL_WINDOW_DECODE                            13   /*!< Window Decode Setting  */
#define JPEG_IOCTL_SET_DECODE_STRIDE                        14   /*!< Set Decode Stride  */
#define JPEG_IOCTL_SET_DECODE_DOWNSCALE                     15   /*!< Set Decode Downscale  */
#define JPEG_IOCTL_SET_ENCODE_UPSCALE                       16   /*!< Set Encode Upscale  */
#define JPEG_IOCTL_SET_HEADERDECODE_CALBACKFUN              17   /*!< Set Header decode call back function  */
#define JPEG_IOCTL_SET_DECINPUTWAIT_CALBACKFUN              18   /*!< Set Decode Input Wait call back function  */
#define JPEG_IOCTL_ADJUST_QTAB                              19   /*!< Set Primary or Thumbnail Q Table  */
#define JPEG_IOCTL_ENC_RESERVED_FOR_SOFTWARE                20   /*!< Set Encode Reserved Size  */
#define JPEG_IOCTL_SET_UADDR                                21   /*!< Set U Component Frame Buffer-0 Starting Address Register  */
#define JPEG_IOCTL_SET_VADDR                                22   /*!< Set V Component Frame Buffer-0 Starting Address Register  */
#define JPEG_IOCTL_SET_ENCODE_PRIMARY_RESTART_INTERVAL      23   /*!< Set Encode Primary restart interval  */
#define JPEG_IOCTL_SET_ENCODE_THUMBNAIL_RESTART_INTERVAL    24   /*!< Set Encode Thumbnail restart interval  */
#define JPEG_IOCTL_GET_ENCODE_PRIMARY_RESTART_INTERVAL      25   /*!< Get Encode Primary restart interval  */
#define JPEG_IOCTL_GET_ENCODE_THUMBNAIL_RESTART_INTERVAL    26   /*!< Get Encode Thumbnail restart interval  */
#define JPEG_IOCTL_SET_THUMBNAIL_DIMENSION                  27   /*!< Set Encode Thumbnail Width/Height  */
#define JPEG_IOCTL_SET_ENCODE_SW_OFFSET                     28   /*!< Set Offset Between Primary & Thumbnail Register  */
#define JPEG_IOCTL_GET_THUMBNAIL_DIMENSION                  29   /*!< Get Thumbnail Width/Height  */
#define JPEG_IOCTL_GET_ENCODE_SW_OFFSET                     30   /*!< Get Offset Between Primary & Thumbnail Register  */
#define JPEG_IOCTL_SET_ENCODE_PRIMARY_DOWNSCALE             31   /*!< Set Enciode Primary Downscale  */
#define JPEG_IOCTL_SET_ENCODE_THUMBNAIL_DOWNSCALE           32   /*!< Set Encode Thumbnail Downscale  */
#define JPEG_IOCTL_SET_ENCODE_PRIMARY_ROTATE_RIGHT          33   /*!< Set Encode Primary rotate right  */
#define JPEG_IOCTL_SET_ENCODE_PRIMARY_ROTATE_LEFT           34   /*!< Set Encode Primary rotate left  */
#define JPEG_IOCTL_SET_ENCODE_PRIMARY_ROTATE_NORMAL         35   /*!< Set Encode Primary rotate normal  */
#define JPEG_IOCTL_SET_DECOUTPUTWAIT_CALBACKFUN             36   /*!< Set Decode Output wait call back function  */
#define JPEG_IOCTL_SET_DECOUTPUTWAIT                        37   /*!< Set Decode Output wait  */
#define JPEG_IOCTL_GET_DECOUTPUTWAIT_ADDR                   38   /*!< Get Decode Output wait address  */
#define JPEG_IOCTL_GET_DECOUTPUTWAIT_SIZE                   39   /*!< Get Decode Output wait size  */
#define JPEG_IOCTL_SET_DECODE_COMPLETE_CALBACKFUN           40   /*!< Set Decode complete call back function  */
#define JPEG_IOCTL_SET_ENCODE_COMPLETE_CALBACKFUN           41   /*!< Set Encode complete call back function  */
#define JPEG_IOCTL_SET_DECODE_ERROR_CALBACKFUN              42   /*!< Set Decode Error call back function  */

typedef BOOL (*PFN_JPEG_HEADERDECODE_CALLBACK)(void);   /*!< JPEG Header decode call back function */
typedef BOOL (*PFN_JPEG_CALLBACK)(void);  /*!< JPEG call back function */
typedef BOOL (*PFN_JPEG_DECWAIT_CALLBACK)(UINT32 u32Address, UINT32 u32Size); /*!< JPEG decode wait call back function */

/** \brief  Structure type of JPEG encode/decode information
 */
typedef struct
{
    /*decode information*/
    UINT32  yuvformat;      /*!< JPEG YUV Format for decode*/
    UINT32  width;          /*!< Image Width */
    UINT32  height;         /*!< Image High */
    UINT32  jpeg_width;     /*!< JPEG decode width*/
    UINT32  jpeg_height;    /*!< JPEG decode high*/
    UINT32  stride;         /*!< Stride for decode*/
    /*encode information*/
    UINT32  bufferend;     /*!< Encode buffer */
    UINT32  image_size[2]; /*!< Image size after encoded*/
} JPEG_INFO_T;

/** \brief  Structure type of JPEG Window Decode information
 */
typedef struct
{
    UINT16  u16StartMCUX;   /*!< Start X MCU  */
    UINT16  u16StartMCUY;   /*!< Horizontal Scaling Factor */
    UINT16  u16EndMCUX;     /*!< Vertical Scaling Factor */
    UINT16  u16EndMCUY;     /*!< Horizontal Scaling Factor  */
    UINT32  u32Stride;      /*!< Decode Output Stride */
} JPEG_WINDOW_DECODE_T;

struct nu_jpeg_ioctl
{
    UINT32 arg0;
    UINT32 arg1;
};
typedef struct nu_jpeg_ioctl *nu_jpeg_ioctl_t;

struct nu_jpeg_qtab
{
    PUINT8 puQTable0;
    PUINT8 puQTable1;
    PUINT8 puQTable2;
    UINT8 u8num;
};
typedef struct nu_jpeg_qtab *nu_jpeg_qtab_t;

/*@}*/ /* end of group N9H30_JPEG_EXPORTED_CONSTANTS */


/** @addtogroup N9H30_JPEG_EXPORTED_FUNCTIONS JPEG Exported Functions
  @{
*/
#define JPEG_IOCTL_SET_QTAB               64   /*!< Set User-defined Q Table  */
#define JPEG_IOCTL_INITIAL_CODEC          65   /*!< Reset Initial internal variables */
#define JPEG_IOCTL_GET_INFO               66   /*!< Set Decode Error call back function */
#define JPEG_IOCTL_IS_READY               67   /*!< Check JPEG codec is ready or not */
#define JPEG_IOCTL_WAITDONE               68   /*!< Wait JPEG action done. */

INT jpegSetQTAB(PUINT8 puQTable0, PUINT8 puQTable1, PUINT8 puQTable2, UINT8 u8num);
INT jpegOpen(void);
VOID jpegClose(void);
VOID jpegInit(void);
VOID jpegGetInfo(JPEG_INFO_T *info);
BOOL jpegIsReady(void);
INT jpegWait(void);
VOID jpegIoctl(UINT32 cmd, UINT32 arg0, UINT32 arg1);

/*@}*/ /* end of group N9H30_JPEG_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group N9H30_JPEG_Driver */

/*@}*/ /* end of group N9H30_Device_Driver */

#endif
