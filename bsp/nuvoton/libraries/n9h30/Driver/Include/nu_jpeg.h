/**************************************************************************//**
* @file     jpeg.h
* @brief    N9H30 JPEG driver header file
*
* @note
* SPDX-License-Identifier: Apache-2.0
* Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#ifndef __NU_JPEG_H__
#define __NU_JPEG_H__

#include "nu_jpegcodec.h"

/** @addtogroup N9H30_Device_Driver N9H30 Device Driver
  @{
*/

/** @addtogroup N9H30_JPEG_Driver JPEG Driver
  @{
*/

/** @addtogroup N9H30_JPEG_EXPORTED_CONSTANTS JPEG Exported Constants
  @{
*/


/// @cond HIDDEN_SYMBOLS
// Define bits mask
#define NVTBIT(start,end) ((0xFFFFFFFFUL >> (31 - start)) & (0xFFFFFFFFUL >>end  << end))
/// @endcond HIDDEN_SYMBOLS


//JMCR
#define RESUMEI     BIT9                /*!< Resume JPEG Operation for Input On-the-Fly Mode          */
#define RESUMEO     BIT8                /*!< Resume JPEG Operation for Output On-the-Fly Mode   */
#define ENC_DEC     BIT7                /*!< JPEG Encode/Decode Mode   */
#define WIN_DEC     BIT6                /*!< JPEG Window Decode Mode   */
#define PRI         BIT5                /*!< Encode Primary Image   */
#define THB         BIT4                /*!< Encode Thumbnail Image   */
#define EY422       BIT3                /*!< Encode Image Format   */
#define QT_BUSY     BIT2                /*!< Quantization-Table Busy Status (Read-Only)   */
#define ENG_RST     BIT1                /*!< Soft Reset JPEG Engine (Except JPEG Control Registers)   */
#define JPG_EN      BIT0                /*!< JPEG Engine Operation Control  */

//JHEADER
#define P_JFIF      BIT7                /*!< Primary JPEG Bit-stream Include JFIF Header           */
#define P_HTAB      BIT6                /*!< Primary JPEG Bit-stream Include Huffman-Table  */
#define P_QTAB      BIT5                /*!< Primary JPEG Bit-stream Include Quantization-Table  */
#define P_DRI       BIT4                /*!< Primary JPEG Bit-stream Include Restart Interval  */
#define T_JFIF      BIT3                /*!< Thumbnail JPEG Bit-stream Include JFIF Header  */
#define T_HTAB      BIT2                /*!< Thumbnail JPEG Bit-stream Include Huffman-Table  */
#define T_QTAB      BIT1                /*!< Thumbnail JPEG Bit-stream Include Quantization-Table  */
#define T_DRI       BIT0                /*!< Thumbnail JPEG Bit-stream Include Restart Interval  */

//JITCR
#define Dec_Scatter_Gather  BIT18
#define DEC_OTF             BIT17               /*!< Decoder on the fly with VPE                                        */
#define ARGB8888            BIT16               /*!< ARGB8888  */
#define PLANAR_ON           BIT15               /*!< Packet On  */
#define ORDER               BIT14               /*!< Decode Packet Data Order  */
#define RGB_555_565         BIT13               /*!< RGB555 & RGB565  */
#define ROTATE              NVTBIT(12,11)       /*!< Encode Image Rotate  */
#define DYUV_MODE           NVTBIT(10,8)        /*!< Decoded Image YUV Color Format (Read-Only)  */
#define EXIF                BIT7                /*!< Encode Quantization-Table & Huffman-Table Header Format Selection  */
#define EY_ONLY             BIT6                /*!< Encode Gray-level (Y-component Only) Image                     */
#define DHEND               BIT5                /*!< Header Decode Complete Stop Enable  */
#define DTHB                BIT4                /*!< Decode Thumbnail Image Only  */
#define E3QTAB              BIT3                /*!< Numbers of Quantization-Table are Used For Encode  */
#define D3QTAB              BIT2                /*!< Numbers of Quantization-Table are Used For Decode (Read-Only)  */
#define ERR_DIS             BIT1                /*!< Decode Error Engine Abort  */
#define PDHTAB              BIT0                /*!< Programmable Huffman-Table Function For Decode  */

//JPRIQC
#define P_QADJUST   NVTBIT(7,4)         /*!< Primary Quantization-Table Adjustment       */
#define P_QVS       NVTBIT(3,0)         /*!< Primary Quantization-Table Scaling Control  */

//JTHBQC
#define T_QADJUST   NVTBIT(7,4)         /*!< Thumbnail Quantization-Table Adjustment       */
#define T_QVS       NVTBIT(3,0)         /*!< Thumbnail Quantization-Table Scaling Control  */

//JPRIWH
#define P_HEIGHT    NVTBIT(27,16)           /*!< Primary Encode Image Height   */
#define P_WIDTH     NVTBIT(11,0)            /*!< Primary Encode Image Width    */

//JTHBWH
#define T_HEIGHT    NVTBIT(27,16)           /*!< Thumbnail Encode Image Height  */
#define T_WIDTH     NVTBIT(11,0)            /*!< Thumbnail Encode Image Width   */

//JPRST
#define P_RST       NVTBIT(7,0)             /*!< Primary Encode Restart Interval Value  */

//JTRST
#define T_RST       NVTBIT(7,0)             /*!< Thumbnail Encode Restart Interval Value  */

//JDECWH
#define DEC_HEIGHT  NVTBIT(31,16)           /*!< 13-bit Bit Stream Buffer threshold  */
#define DEC_WIDTH   NVTBIT(15,0)            /*!< 13-bit Header Offset Address        */

//JINTCR
#define JPG_DOW_INTE    BIT28               /*!< Decoding Output Wait Interrupt Enable  */
#define JPG_DOW_INTS    BIT24               /*!< Status of Decoding Output Wait  */
#define JPG_WAITI       BIT23               /*!< JPEG Input Wait Status (Read-Only)  */
#define JPG_WAITO       BIT22               /*!< JPEG Output Wait Status (Read-Only)  */
#define BAbort          BIT16               /*!< JPEG Memory Access Error Status (Read-Only)  */
#define CER_INTE        BIT15               /*!< Un-complete Capture On-The-Fly Frame Occur Interrupt Enable  */
#define DHE_INTE        BIT14               /*!< JPEG Header Decode End Wait Interrupt Enable  */
#define IPW_INTE        BIT13               /*!< Input Wait Interrupt Enable  */
#define OPW_INTE        BIT12               /*!< Output Wait Interrupt Enable  */
#define ENC_INTE        BIT11               /*!< Encode Complete Interrupt Enable  */
#define DEC_INTE        BIT10               /*!< Decode Complete Interrupt Enable  */
#define DER_INTE        BIT9                /*!< Decode Error Interrupt Enable  */
#define EER_INTE        BIT8                /*!< Encode (On-The-Fly) Error Interrupt Enable  */
#define CER_INTS        BIT7                /*!< Un-complete Capture On-The-Fly Frame Occur Interrupt Status  */
#define DHE_INTS        BIT6                /*!< JPEG  Header Decode End Wait Interrupt Status  */
#define IPW_INTS        BIT5                /*!< Input Wait Interrupt Status  */
#define OPW_INTS        BIT4                /*!< Output Wait Interrupt Status  */
#define ENC_INTS        BIT3                /*!< Encode Complete Interrupt Status  */
#define DEC_INTS        BIT2                /*!< Decode Complete Interrupt Status  */
#define DER_INTS        BIT1                /*!< Decode Error Interrupt Status  */
#define EER_INTS        BIT0                /*!< Encode (On-The-Fly) Error Interrupt Status  */

//JPEG_BSBAD
#define BIST_ST         NVTBIT(23,16)       /*!< Internal SRAM BIST Status (Read-Only)  */
#define TEST_DOUT       NVTBIT(15,8)        /*!< Test Data Output (Read-Only)  */
#define TEST_ON         BIT7                /*!< Test Enable  */
#define BIST_ON         BIT6                /*!< Internal SRAM BIST Mode Enable  */
#define BIST_FINI       BIT5                /*!< Internal SRAM BIST Mode Finish (Read-Only)  */
#define BSBAD_BIST_FAIL BIT4                /*!< Internal SRAM BIST Mode Fail (Read-Only)  */
#define TEST_SEL        NVTBIT(3,0)         /*!< Test Data Selection  */

//JWINDEC0
#define MCU_S_Y     NVTBIT(24,16)           /*!< MCU Start Position Y For Window Decode Mode  */
#define MCU_S_X     NVTBIT(8,0)             /*!< MCU Start Position X For Window Decode Mode  */

//JWINDEC1
#define MCU_E_Y     NVTBIT(24,16)           /*!< MCU End Position Y For Window Decode Mode  */
#define MCU_E_X     NVTBIT(8,0)             /*!< MCU End Position X For Window Decode Mode  */

//JWINDEC2
#define WD_WIDTH    NVTBIT(11,0))           /*!< Image Width (Y-Stride) For Window Decode Mode  */

//JMACR
#define FLY_SEL     NVTBIT(29,24)       /*!< Hardware Memory On-the-Fly Access Image Buffer-Size Selection for Encode  */
#define FLY_TYPE    NVTBIT(23,22)       /*!< Dual/Single buffer on-the fly   */
#define BSF_SEL     NVTBIT(17,8)        /*!< Memory On-the-Fly Access Bitstream Buffer-Size Selection  */
#define FLY_ON      BIT7                /*!< Hardware Memory On-the-Fly Access Mode  */
#define IP_SF_ON    BIT3                /*!< Software Memory On-the-Fly Access Mode for Data Input  */
#define OP_SF_ON    BIT2                /*!< Software Memory On-the-Fly Access Mode for Data Output  */
#define ENC_MODE    NVTBIT(1,0)         /*!< JPEG Memory Address Mode Control  */

//JPSCALU
#define JPSCALU_8X  BIT6                /*!< Primary Image Up-Scaling For Encode  */
#define A_JUMP      BIT2                /*!< Reserve Buffer Size In JPEG Bit-stream For Software Application  */

//JPSCALD
#define PSX_ON      BIT15               /*!< Primary Image Horizontal Down-Scaling For Encode/Decode  */
#define PS_LPF_ON   BIT14               /*!< Primary Image Down-Scaling Low Pass Filter For Decode  */
#define PSCALX_F    NVTBIT(12,8)        /*!< Primary Image Horizontal Down-Scaling Factor  */
#define PSCALY_F    NVTBIT(5,0)         /*!< Primary Image Vertical Down-Scaling Factor  */

//JTSCALD
#define TSX_ON      BIT15               /*!< Thumbnail Image Horizontal Down-Scaling For Encode/Decode  */
#define TSCALX_F    NVTBIT(14,8)        /*!< Thumbnail Image Horizontal Down-Scaling Factor  */
#define TSCALY_F    NVTBIT(7,0)         /*!< Thumbnail Image Vertical Down-Scaling Factor  */

//JDBCR
#define DBF_EN      BIT7                /*!< Dual Buffering Control  */
#define IP_BUF      BIT4                /*!< Input Dual Buffer Control  */

//JRESERVE
#define RES_SIZE    NVTBIT(15,0)        /*!< Primary Encode Bit-stream Reserved Size  */

//JOFFSET
#define OFFSET_SIZE NVTBIT(23,0)        /*!< Primary/Thumbnail Starting Address Offset Size  */

//JFSTRIDE
#define F_STRIDE    NVTBIT(23,0)        /*!< JPEG Encode Bit-stream Frame Stride  */

//JYADDR0
#define Y_IADDR0    NVTBIT(31,0)        /*!< JPEG Y Component Frame Buffer-0 Starting Address  */

//JUADDR0
#define U_IADDR0    NVTBIT(31,0)        /*!< JPEG U Component Frame Buffer-0 Starting Address  */

//JVADDR0
#define V_IADDR0    NVTBIT(31,0)        /*!< JPEG V Component Frame Buffer-0 Starting Address  */

//JYADDR1
#define Y_IADDR1    NVTBIT(31,0)        /*!< JPEG Y Component Frame Buffer-1 Starting Address  */

//JUADDR1
#define U_IADDR1    NVTBIT(31,0)        /*!< JPEG U Component Frame Buffer-1 Starting Address  */

//JVADDR1
#define V_IADDR1    NVTBIT(31,0)        /*!< JPEG V Component Frame Buffer-1 Starting Address  */

//JYSTRIDE
#define Y_STRIDE    NVTBIT(11,0)        /*!< JPEG Y Component Frame Buffer Stride  */

//JUSTRIDE
#define U_STRIDE    NVTBIT(11,0)        /*!< JPEG U Component Frame Buffer Stride  */

//JVSTRIDE
#define V_STRIDE    NVTBIT(11,0)        /*!< JPEG V Component Frame Buffer Stride  */

//JIOADDR0
#define IO_IADDR0   NVTBIT(31,0)        /*!< JPEG Bit-stream Frame Buffer-0 Starting Address  */

//JIOADDR1
#define IO_IADDR1   NVTBIT(31,0)        /*!< JPEG Bit-stream Frame Buffer-1 Starting Address  */

//JPRI_SIZE
#define PRI_SIZE    NVTBIT(23,0)        /*!< JPEG Primary Image Encode Bit-stream Size  */

//JTHB_SIZE
#define THB_SIZE    NVTBIT(15,0)        /*!< JPEG Thumbnail Image Encode Bit-stream Size  */

//JUPRAT
#define S_HEIGHT    NVTBIT(29,16)       /*!< JPEG Image Height Up-Scale Ratio  */
#define S_WIDTH     NVTBIT(13,0)        /*!< JPEG Image Width Up-Scale Ratio  */

//JBSFIFO
#define BSFIFO_HT   NVTBIT(6,4)         /*!< Bit-stream FIFO High-Threshold Control  */
#define BSFIFO_LT   NVTBIT(2,0)         /*!< Bit-stream FIFO Low-Threshold Control  */

//JSRCH
#define JSRCH_JSRCH NVTBIT(11,0)        /*!< JPEG Encode Source Image Height  */

/*@}*/ /* end of group N9H30_JPEG_EXPORTED_CONSTANTS */

/// @cond HIDDEN_SYMBOLS

//Define for Interrupt Status
#define JPEG_EER_INTS   EER_INTS
#define JPEG_DER_INTS   DER_INTS
#define JPEG_DEC_INTS   DEC_INTS
#define JPEG_ENC_INTS   ENC_INTS
#define JPEG_DHE_INTS   DHE_INTS
#define JPEG_IPW_INTS   IPW_INTS

//Define for Scaling
#define JPEG_ENC_UPSCALE_MODE               0
#define JPEG_DEC_PACKET_DOWNSCALE_MODE      1
#define JPEG_DEC_PLANAR_DOWNSCALE_MODE              2
#define JPEG_ENC_PLANAR_PRIMARY_DOWNSCALE_MODE       3
#define JPEG_ENC_PLANAR_THUMBNAIL_DOWNSCALE_MODE  4

//Define for Interrupt Enable
#define JPEG_EER_INTE   ERR_INTE
#define JPEG_DER_INTE   DER_INTE
#define JPEG_DEC_INTE   DEC_INTE
#define JPEG_ENC_INTE   ENC_INTE
#define JPEG_DHE_INTE   DHE_INTE
#define JPEG_IPW_INTE   IPW_INTE

//Register
#define     REG_JMCR        JMCR             /*!< JPEG Mode Control Register  */
#define     REG_JHEADER     JHEADER          /*!< JPEG Encode Header Control Register  */
#define     REG_JITCR       JITCR            /*!< JPEG Image Type Control Register  */
#define     REG_JPRIQC      JPRIQC           /*!< JPEG Primary Q-Table Control Register  */
#define     REG_JTHBQC      JTHBQC           /*!< JPEG Thumbnail Q-Table Control Register  */
#define     REG_JPRIWH      JPRIWH           /*!< JPEG Encode Primary Width/Height Register  */
#define     REG_JTHBWH      JTHBWH           /*!< JPEG Encode Thumbnail Width/Height Register  */
#define     REG_JPRST       JPRST            /*!< JPEG Encode Primary Restart Interval Register  */
#define     REG_JTRST       JTRST            /*!< JPEG Encode Thumbnail Restart Interval  */
#define     REG_JDECWH      JDECWH           /*!< JPEG Decode Image Width/Height Register  */
#define     REG_JINTCR      JINTCR           /*!< JPEG Interrupt Control and Status Register  */
#define     REG_JTEST       JTEST            /*!< JPEG Test Control Register  */
#define     REG_JWINDEC0    JWINDEC0         /*!< JPEG Window Decode Mode Control Register 0  */
#define     REG_JWINDEC1    JWINDEC1         /*!< JPEG Window Decode Mode Control Register 1  */
#define     REG_JWINDEC2    JWINDEC2         /*!< JPEG Window Decode Mode Control Register 2  */
#define     REG_JMACR       JMACR            /*!< JPEG Memory Address Mode Control Register  */
#define     REG_JPSCALU     JPSCALU          /*!< JPEG Primary Scaling-Up Control Register  */
#define     REG_JPSCALD     JPSCALD          /*!< JPEG Primary Scaling-Down Control Register  */
#define     REG_JTSCALD     JTSCALD          /*!< JPEG Thumbnail  Scaling-Down Control Register  */
#define     REG_JDBCR       JDBCR            /*!< JPEG Dual-Buffer Control Register  */
#define     REG_JRESERVE    JRESERVE         /*!< JPEG Encode Primary Bit-stream Reserved Size Register  */
#define     REG_JOFFSET     JOFFSET          /*!< JPEG Offset Between Primary & Thumbnail Register  */
#define     REG_JFSTRIDE    JFSTRIDE         /*!< JPEG Encode Bit-stream Frame Stride Register  */
#define     REG_JYADDR0     JYADDR0          /*!< JPEG Y Component Frame Buffer-0 Starting Address Register  */
#define     REG_JUADDR0     JUADDR0          /*!< JPEG U Component Frame Buffer-0 Starting Address Register  */
#define     REG_JVADDR0     JVADDR0          /*!< JPEG V Component Frame Buffer-0 Starting Address Register  */
#define     REG_JYADDR1     JYADDR1          /*!< JPEG Y Component Frame Buffer-1 Starting Address Register  */
#define     REG_JUADDR1     JUADDR1          /*!< JPEG U Component Frame Buffer-1 Starting Address Register  */
#define     REG_JVADDR1     JVADDR1          /*!< JPEG V Component Frame Buffer-1 Starting Address Register  */
#define     REG_JYSTRIDE    JYSTRIDE         /*!< JPEG Y Component Frame Buffer Stride Register  */
#define     REG_JUSTRIDE    JUSTRIDE         /*!< JPEG U Component Frame Buffer Stride Register  */
#define     REG_JVSTRIDE    JVSTRIDE         /*!< JPEG V Component Frame Buffer Stride Register  */
#define     REG_JIOADDR0    JIOADDR0         /*!< JPEG Bit-stream Frame Buffer-0 Starting Address Register  */
#define     REG_JIOADDR1    JIOADDR1         /*!< JPEG Bit-stream Frame Buffer-1 Starting Address Register  */
#define     REG_JPRI_SIZE   JPRI_SIZE        /*!< JPEG Encode Primary Image Bit-stream Size Register  */
#define     REG_JTHB_SIZE   JTHB_SIZE        /*!< JPEG Encode Thumbnail Image Bit-stream Size Register  */
#define     REG_JUPRAT      JUPRAT           /*!< JPEG Encode Up-Scale Ratio Register  */
#define     REG_JBSFIFO     JBSFIFO          /*!< JPEG Bit-stream FIFO Control Register  */
#define     REG_JSRCH       JSRCH            /*!< JPEG Encode Source Image Height  */
#define     REG_JQTAB0      JQTAB0           /*!< JPEG Quantization-Table 0 Register  */
#define     REG_JQTAB1      JQTAB1           /*!< JPEG Quantization-Table 1 Register  */
#define     REG_JQTAB2      JQTAB2           /*!< JPEG Quantization-Table 2 Register  */

//Export functions
#define JPEG_SET_YADDR(u32Address)              outp32(REG_JYADDR0, u32Address)
#define JPEG_SET_UADDR(u32Address)              outp32(REG_JUADDR0, u32Address)
#define JPEG_SET_VADDR(u32Address)              outp32(REG_JVADDR0, u32Address)
#define JPEG_GET_YADDR()                        inp32(REG_JYADDR0)
#define JPEG_GET_UADDR()                        inp32(REG_JUADDR0)
#define JPEG_GET_VADDR()                        inp32(REG_JVADDR0)
#define JPEG_SET_YSTRIDE(u32Stride)             outp32(REG_JYSTRIDE, u32Stride)
#define JPEG_SET_USTRIDE(u32Stride)             outp32(REG_JUSTRIDE, u32Stride)
#define JPEG_SET_VSTRIDE(u32Stride)             outp32(REG_JVSTRIDE, u32Stride)
#define JPEG_GET_YSTRIDE()                      inp32(REG_JYSTRIDE)
#define JPEG_GET_USTRIDE()                      inp32(REG_JUSTRIDE)
#define JPEG_GET_VSTRIDE()                      inp32(REG_JVSTRIDE)
#define JPEG_SET_BITSTREAM_ADDR(u32Address)     outp32(REG_JIOADDR0,u32Address)
#define JPEG_GET_BITSTREAM_ADDR()               inp32(REG_JIOADDR0)
#define JPEG_SET_ENC_DEC(u8Mode)                outp32(REG_JMCR, (inp32(REG_JMCR) & ~ENC_DEC) | (u8Mode << 7));

//Encode
#define JPEG_GET_ENC_PRIMARY_BITSTREAM_SIZE()   inp32(REG_JPRI_SIZE)
#define JPEG_GET_ENC_THUMBNAIL_BITSTREAM_SIZE() inp32(REG_JTHB_SIZE)
#define JPEG_SET_SOURCE_IMAGE_HEIGHT(u16Size)   outp32(REG_JSRCH,u16Size)
#define JPEG_GET_SOURCE_IMAGE_HEIGHT()          inp32(REG_JSRCH)
#define JPEG_ENC_ENABLE_UPSCALING()             outp32(REG_JPSCALU,inp32(REG_JPSCALU) | JPSCALU_8X)
#define JPEG_ENC_DISABLE_UPSCALING()            outp32(REG_JPSCALU,inp32(REG_JPSCALU) & ~JPSCALU_8X)
#define JPEG_ENC_ISENABLE_UPSCALING()           ((inp32(REG_JPSCALU) & JPSCALU_8X) >> 6)
#define JPEG_ENC_SET_HEADER_CONTROL(u8Control)  outp32(REG_JHEADER, u8Control)
#define JPEG_ENC_GET_HEADER_CONTROL()           inp32(REG_JHEADER)
#define JPEG_ENC_SET_RDI_VALUE(u8Value)         outp32(REG_JPRST,u8Value)
#define JPEG_ENC_GET_RDI_VALUE()                inp32(REG_JPRST)

//Decode
#define JPEG_DEC_ENABLE_DOWNSCALING()           outp32(REG_JPSCALD, PSX_ON)
#define JPEG_DEC_ISENABLE_DOWNSCALING()         ((inp32(REG_JPSCALD) & PSX_ON) >> 15)
#define JPEG_DEC_DISABLE_DOWNSCALING()          outp32(REG_JPSCALD,~PSX_ON)
#define JPEG_DEC_GET_DECODED_IMAGE_FORMAT()     (inp32(REG_JITCR) & DYUV_MODE)
#define JPEG_DEC_ENABLE_LOW_PASS_FILTER()       outp32(REG_JPSCALD,inp32(REG_JPSCALD) | PS_LPF_ON)
#define JPEG_DEC_DISABLE_LOW_PASS_FILTER()      outp32(REG_JPSCALD,inp32(REG_JPSCALD) & ~PS_LPF_ON)
#define JPEG_DEC_ISENABLE_LOW_PASS_FILTER()     ((inp32(REG_JPSCALD) & PS_LPF_ON) >> 14)
#define JPEG_DEC_SET_INPUT_WAIT(u16Size)        outp32(REG_JMACR, 0x00400008 | ((u16Size & 0x3FF)<< 8) );
#define JPEG_DEC_RESUME_INPUT_WAIT()            outp32(REG_JMCR,inp32(REG_JMCR) | RESUMEI);
#define JPEG_DEC_DISABLE_WINDOWDECODE()         outp32(REG_JMCR, inp32(REG_JMCR) & ~(WIN_DEC));

//Interrupt
#define JPEG_INT_ENABLE(u32Intflag)             outp32(REG_JINTCR, u32Intflag)
#define JPEG_INT_DISABLE(u32Intflag)            outp32(REG_JINTCR, inp32 (REG_JINTCR) & ~(u32Intflag))
#define JPEG_GET_INT_STATUS()                   (inp32(REG_JINTCR) & 0x010000FF)
#define JPEG_CLEAR_INT(u32Intflag)              outp32(REG_JINTCR, (inp32 (REG_JINTCR) & ~0xFF) | u32Intflag)

static INT jpegSetEncodeMode(UINT8 u8SourceFormat, UINT16 u16JpegFormat);
static INT jpegSetDecodeMode(UINT32 u8OutputFormat);
static BOOL jpegPollInt(UINT32 u32Intflag);
static VOID jpegEncodeTrigger(void);
static VOID jpegDecodeTrigger(void);
static VOID jpegGetDecodedDimension(
    PUINT16 pu16Height,         //Decode/Encode Height
    PUINT16 pu16Width           //Decode/Encode Width
);
static VOID jpegSetDimension(
    UINT16 u16Height,           //Decode/Encode Height
    UINT16 u16Width             //Decode/Encode Width
);
static VOID jpegGetDimension(
    PUINT16 pu16Height,         //Decoded Height from bit stream
    PUINT16 pu16Width           //Decoded Width  from bit stream
);
static INT jpegSetWindowDecode(
    UINT16  u16StartMCUX,   //Start X MCU
    UINT16  u16StartMCUY,   //Horizontal Scaling Factor
    UINT16  u16EndMCUX,     //Vertical Scaling Factor
    UINT16  u16EndMCUY,     //Horizontal Scaling Factor
    UINT32  u32Stride       //Decode Output Stride
);
static INT jpegCalScalingFactor(
    UINT8   u8Mode,                     //Up / Down Scaling
    UINT16  u16Height,                  //Original Height
    UINT16  u16Width,                   //Original Width
    UINT16  u16ScalingHeight,           //Scaled Height
    UINT16  u16ScalingWidth,            //Scaled Width
    PUINT16 pu16RatioH,                 //Horizontal Ratio
    PUINT16 pu16RatioW                  //Vertical Ratio
);
static INT jpegSetScalingFactor(
    UINT8   u8Mode,                 //Up / Down Scaling
    UINT16  u16FactorH,             //Vertical Scaling Factor
    UINT16  u16FactorW              //Horizontal Scaling Factor
);
static VOID jpegGetScalingFactor(
    UINT8   u8Mode,             //Up / Down Scaling
    PUINT16 pu16FactorH,        //Vertical Scaling Factor
    PUINT16 pu16FactorW         //Horizontal Scaling Factor
);
/// @endcond HIDDEN_SYMBOLS

/*@}*/ /* end of group N9H30_JPEG_Driver */

/*@}*/ /* end of group N9H30_Device_Driver */

#endif
