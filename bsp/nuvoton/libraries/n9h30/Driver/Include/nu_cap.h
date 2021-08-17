/**************************************************************************//**
* @file     cap.h
* @version  V1.00
* $Revision: 2 $
* $Date: 15/06/12 8:48a $
* @brief    N9H30 CAP driver header file
*
* @note
* SPDX-License-Identifier: Apache-2.0
* Copyright (C) 2015 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#ifndef __NU_CAP_H__
#define __NU_CAP_H__

// #include header file
#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup N9H30_Device_Driver N9H30 Device Driver
  @{
*/

/** @addtogroup N9H30_CAP_Driver CAP Driver
  @{
*/

/** @addtogroup N9H30_CAP_EXPORTED_CONSTANTS CAP Exported Constants
  @{
*/

/* Define data type (struct, union? */
// #define Constant
#include "N9H30.h"
#include "nu_sys.h"

/*---------------------------------------------------------------------------------------------------------*/
/* CAP_CTL constant definitions                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define CAPEN     BIT0          /*!< Interrupt enable for VPE operations */
#define ADDRSW    BIT3          /*!< Packet Buffer Address Switch */
#define PLNEN     BIT5          /*!< Planar Output Enable */
#define PKTEN     BIT6          /*!< Packet Output Enable */
#define SHUTTER   BIT16         /*!< Image Capture Interface Automatically Disable The Capture Inteface After A Frame Had Been Captured */
#define UPDATE    BIT20         /*!< Update Register At New Frame */
#define VPRST     BIT24         /*!< Capture Interface Reset */

/*---------------------------------------------------------------------------------------------------------*/
/* CAP_PAR constant definitions                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define INFMT     BIT0          /*!< Sensor Input Data Format */
#define SENTYPE   BIT1          /*!< Sensor Input Type */
#define INDATORD  (BIT2|BIT3)   /*!< Sensor Input Data Order */
#define OUTFMT    (BIT4|BIT5)   /*!< Image Data Format Output To System Memory */
#define RANGE     BIT6          /*!< Scale Input YUV CCIR601 Color Range To Full Range */
#define PLNFMT    BIT7          /*!< Planar Output YUV Format */
#define PCLKP     BIT8          /*!< Sensor Pixel Clock Polarity */
#define HSP       BIT9          /*!< Sensor Hsync Polarity */
#define VSP       BIT10         /*!< Sensor Vsync Polarity */
#define COLORCTL  (BIT11|BIT12) /*!< Special COLORCTL Processing */
#define FBB       BIT18         /*!< Field By Blank */

/*---------------------------------------------------------------------------------------------------------*/
/* CAP_INT constant definitions                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define MDIEN       BIT20         /*!< Motion Detection Output Finish Interrupt Enable */
#define ADDRMIEN    BIT19         /*!< Address Match Interrupt Enable */
#define MEIEN       BIT17         /*!< System Memory Error Interrupt Enable */
#define VIEN        BIT16         /*!< Video Frame End Interrupt Enable */
#define MDINTF      BIT4          /*!< Motion Detection Output Finish Interrupt */
#define ADDRMINTF   BIT3          /*!< Memory Address Match Interrupt */
#define MEINTF      BIT1          /*!< Bus Master Transfer Error Interrupt */
#define VINTF       BIT0          /*!< Video Frame End Interrupt */

/*---------------------------------------------------------------------------------------------------------*/
/* CAP_MD constant definitions                                                                             */
/*---------------------------------------------------------------------------------------------------------*/
#define MDEN        BIT0          /*!< Motion Detection Enable */
#define MDBS        BIT8          /*!< Motion Detection Block Size */
#define MDSM        BIT9          /*!< Motion Detection Save Mode */
#define MDDF        (BIT10|BIT11) /*!< Motion Detection Detect Frequency */
#define MDTHR       (BIT16|BIT17|BIT18|BIT19|BIT20) /*!< Motion Detection Differential Threshold */

/*---------------------------------------------------------------------------------------------------------*/
/* CAP_CWSP constant definitions                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CWSADDRH    (0xFFF<<0)    /*!<Cropping Window Horizontal Starting Address */
#define CWSADDRV    (0xFFF<<16)   /*!<Cropping Window Vertical Starting Address */

/*---------------------------------------------------------------------------------------------------------*/
/* CAP_CWS constant definitions                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define CWW   (0xFFF<<0)    /*!< Cropping Window Horizontal Starting Address */
#define CWH   (0xFFF<<16)   /*!< Cropping Window Vertical Starting Address */

/*---------------------------------------------------------------------------------------------------------*/
/* CAP_PKTSL constant definitions                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define PKTSHML   (0xFFul<< 0) /*!< Packet Scaling Horizontal Factor M (Lower 8-Bit) */
#define PKTSHNL   (0xFFul<< 8) /*!< Packet Scaling Horizontal Factor N (Lower 8-Bit) */
#define PKTSVML   (0xFFul<<16) /*!< Packet Scaling Vertical Factor M (Lower 8-Bit) */
#define PKTSVNL   (0xFFul<<24) /*!< Packet Scaling Vertical Factor N (Lower 8-Bit) */

/*---------------------------------------------------------------------------------------------------------*/
/* CAP_PLNSL constant definitions                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define PLNSHML   (0xFFul<< 0) /*!< Planar Scaling Horizontal Factor M (Lower 8-Bit) */
#define PLNSHNL   (0xFFul<< 8) /*!< Planar Scaling Horizontal Factor N (Lower 8-Bit) */
#define PLNSVML   (0xFFul<<16) /*!< Planar Scaling Vertical Factor M (Lower 8-Bit) */
#define PLNSVNL   (0xFFul<<24) /*!< Planar Scaling Vertical Factor N (Lower 8-Bit) */

/*---------------------------------------------------------------------------------------------------------*/
/* CAP_PKTSM constant definitions                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define PKTSHMH   (0xFFul<< 0) /*!< Packet Scaling Horizontal Factor M (Higher 8-Bit) */
#define PKTSHNH   (0xFFul<< 8) /*!< Packet Scaling Horizontal Factor N (Higher 8-Bit) */
#define PKTSVMH   (0xFFul<<16) /*!< Packet Scaling Vertical Factor M (Higher 8-Bit) */
#define PKTSVNH   (0xFFul<<24) /*!< Packet Scaling Vertical Factor N (Higher 8-Bit) */

/*---------------------------------------------------------------------------------------------------------*/
/* CAP_PLNSM constant definitions                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define PLNSHMH   (0xFFul<< 0) /*!< Planar Scaling Horizontal Factor M (Higher 8-Bit) */
#define PLNSHNH   (0xFFul<< 8) /*!< Planar Scaling Horizontal Factor N (Higher 8-Bit) */
#define PLNSVMH   (0xFFul<<16) /*!< Planar Scaling Vertical Factor M (Higher 8-Bit) */
#define PLNSVNH   (0xFFul<<24) /*!< Planar Scaling Vertical Factor N (Higher 8-Bit) */

/*---------------------------------------------------------------------------------------------------------*/
/* CAP_FRCTL constant definitions                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define FRM   (0x3Ful<<0)  /*!< Scaling Frame Rate Factor M */
#define FRN   (0x3Ful<<8)  /*!< Scaling Frame Rate Factor N */

/*---------------------------------------------------------------------------------------------------------*/
/* CAP_STRIDE constant definitions                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define PKTSTRIDE       (0x3FFFul<<0)   /*!< Packet Frame Output Pixel Stride Width */
#define PLNSTRIDE       (0x3FFFul<<16)  /*!< Planar Frame Output Pixel Stride Width */

#define VIN_ERR_ID      0xFFFF1000  /*!< CAP library ID */

//Error message
// E_CAP_INVALID_INT            Invalid interrupt
// E_CAP_INVALID_BUF            Invalid buffer
// E_CAP_INVALID_PIPE           Invalid pipe
// E_CAP_INVALID_COLOR_MODE     Invalid color mode

#define E_CAP_INVALID_INT             (VIN_ERR_ID | 0x01) /*!< CAP invalid interrupt */
#define E_CAP_INVALID_BUF             (VIN_ERR_ID | 0x02) /*!< CAP invalid buffer */
#define E_CAP_INVALID_PIPE            (VIN_ERR_ID | 0x03) /*!< CAP invalid pipe */
#define E_CAP_INVALID_COLOR_MODE      (VIN_ERR_ID | 0x04) /*!< CAP invalid color mode */
#define E_CAP_WRONG_COLOR_PARAMETER   (VIN_ERR_ID | 0x05) /*!< CAP worng color parameter */

/// @cond HIDDEN_SYMBOLS
typedef void (*PFN_CAP_CALLBACK)(UINT8 u8PacketBufID, UINT8 u8PlanarBufID, UINT8 u8FrameRate);
/// @endcond HIDDEN_SYMBOLS

/** \brief  Structure type of E_CAP_INT_TYPE
 */
typedef enum
{
    eCAP_MDINTF     = 0x100000,  /*!< Motion detection output finish interrupt */
    eCAP_ADDRMINTF  = 0x80000,   /*!< Memory address match interrupt */
    eCAP_MEINTF     = 0x20000,   /*!< Bus master transfer error interrupt */
    eCAP_VINTF      = 0x10000    /*!< Video frame end interrupt */
} E_CAP_INT_TYPE;


/** \brief  Structure type of E_CAP_PIPE
 */
typedef enum
{
    eCAP_BOTH_PIPE_DISABLE  = 0,  /*!< Planar output disable and planar output disable */
    eCAP_PLANAR             = 1,  /*!< Planar output enable */
    eCAP_PACKET             = 2,  /*!< Packet output enable */
    eCAP_BOTH_PIPE_ENABLE   = 3   /*!< Planar output enable and planar output enable */
} E_CAP_PIPE;

/** \brief  Structure type of E_CAP_BUFFER
 */
typedef enum
{
    eCAP_BUF0 = 0, /*!< System memory packet/planar base Address 0/Y */
    eCAP_BUF1,     /*!< System memory packet/planar base Address 1/U */
    eCAP_BUF2      /*!< System memory packet/planar base Address 2/V */
} E_CAP_BUFFER;


/** \brief  Structure type of E_CAP_ORDER
 */
typedef enum
{
    eCAP_IN_YUYV = 0, /*!< Sensor input data (Byte 0 1 2 3) is Y0 U0 Y1 V0 */
    eCAP_IN_YVYU,   /*!< Sensor input data (Byte 0 1 2 3) is Y0 V0 Y1 U0 */
    eCAP_IN_UYVY,   /*!< Sensor input data (Byte 0 1 2 3) is U0 Y0 V0 Y1 */
    eCAP_IN_VYUY,   /*!< Sensor input data (Byte 0 1 2 3) is V0 Y0 U0 Y1 */
} E_CAP_ORDER;

/** \brief  Structure type of E_CAP_IN_FORMAT
 */
typedef enum
{
    eCAP_IN_YUV422 = 0, /*!< Sensor input data format is YUV222 */
    eCAP_IN_RGB565      /*!< Sensor input data format is RGB565 */
} E_CAP_IN_FORMAT;

/** \brief  Structure type of E_CAP_OUT_FORMAT
 */
typedef enum
{
    eCAP_OUT_YUV422 = 0,  /*!< Image data format is YUV422 */
    eCAP_OUT_ONLY_Y,      /*!< Image data format is Only output Y */
    eCAP_OUT_RGB555,      /*!< Image data format is RGB555 */
    eCAP_OUT_RGB565       /*!< Image data format is RGB565 */
} E_CAP_OUT_FORMAT;

/** \brief  Structure type of E_CAP_PLANAR_FORMAT
 */
typedef enum
{
    eCAP_PLANAR_YUV422 = 0, /*!< Planar output YUV format is YUV422 */
    eCAP_PLANAR_YUV420,     /*!< Planar output YUV format is YUV420 */
} E_CAP_PLANAR_FORMAT;

/** \brief  Structure type of E_CAP_TYPE
 */
typedef enum
{
    eCAP_TYPE_CCIR601 = 0,  /*!< Sensor input type is CCIR601 */
    eCAP_TYPE_CCIR656       /*!< Sensor input type is CCIR656 */
} E_CAP_TYPE;

/** \brief  Structure type of E_CAP_SNR_SRC
 */
typedef enum
{
    eCAP_SNR_APLL = 2,   /*!< CAP clock source is APLL */
    eCAP_SNR_UPLL = 3    /*!< CAP clock source is UPLL */
} E_CAP_SNR_SRC;

/** \brief  Structure type of E_CAP_CEF
 */
typedef enum
{
    eCAP_CEF_NORMAL       = 0,  /*!< Image Processing is normal color */
    eCAP_CEF_SEPIA        = 1,  /*!< Image Processing is sepia effect */
    eCAP_CEF_NEGATIVE     = 2,  /*!< Image Processing is negative picture. */
    eCAP_CEF_POSTERIZE    = 3   /*!< Image Processing is posterize image */
} E_CAP_CEF;

/*@}*/ /* end of group N9H30_CAP_EXPORTED_CONSTANTS */

/** @addtogroup N9H30_CAP_EXPORTED_FUNCTIONS CAP Exported Functions
  @{
*/

/// @cond HIDDEN_SYMBOLS
typedef struct
{
    void (*Init)(BOOL bIsEnableSnrClock, E_CAP_SNR_SRC eSnrSrc, UINT32 u32SensorFreqKHz);
    INT32(*Open)(UINT32 u32SensorFreqKHz);
    void (*Close)(void);
    void (*SetPipeEnable)(BOOL bEngEnable, E_CAP_PIPE ePipeEnable);
    void (*SetPlanarFormat)(E_CAP_PLANAR_FORMAT ePlanarFmt);
    void (*SetCropWinSize)(UINT32 u32height, UINT32 u32width);
    void (*SetCropWinStartAddr)(UINT32 u32VerticalStart, UINT32 u32HorizontalStart);
    void (*SetStride)(UINT32 u16packetstride, UINT32 u32planarstride);
    void (*GetStride)(PUINT32 pu32PacketStride, PUINT32 pu32PlanarStride);
    INT32(*EnableInt)(E_CAP_INT_TYPE eIntType);
    INT32(*DisableInt)(E_CAP_INT_TYPE eIntType);
    INT32(*InstallCallback)(E_CAP_INT_TYPE eIntType, PFN_CAP_CALLBACK pfnCallback, PFN_CAP_CALLBACK *pfnOldCallback);
    INT32(*SetBaseStartAddress)(E_CAP_PIPE ePipe, E_CAP_BUFFER eBuf, UINT32 u32BaseStartAddr);
    void (*SetOperationMode)(BOOL bIsOneSutterMode);
    BOOL (*GetOperationMode)(void);
    void (*SetPacketFrameBufferControl)(BOOL bFrameSwitch);
    void (*SetSensorPolarity)(BOOL bVsync, BOOL bHsync, BOOL bPixelClk);
    INT32(*SetColorEffectParameter)(UINT8 u8YComp, UINT8 u8UComp, UINT8 u8VComp);
    void (*SetDataFormatAndOrder)(E_CAP_ORDER eInputOrder, E_CAP_IN_FORMAT eInputFormat, E_CAP_OUT_FORMAT eOutputFormat);
    void (*SetMotionDet)(BOOL bEnable, BOOL bBlockSize, BOOL bSaveMode);
    void (*SetMotionDetEx)(UINT32 u32DetFreq, UINT32 u32Threshold, UINT32 u32OutBuffer, UINT32 u32LumBuffer);
    void (*SetStandardCCIR656)(BOOL);
    void (*SetShadowRegister)(void);
} CAPDEV_T;
/// @endcond HIDDEN_SYMBOLS

/*@}*/ /* end of group N9H30_CAP_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group N9H30_CAP_Driver */

/*@}*/ /* end of group N9H30_Device_Driver */

#ifdef __cplusplus
}
#endif

#endif

















