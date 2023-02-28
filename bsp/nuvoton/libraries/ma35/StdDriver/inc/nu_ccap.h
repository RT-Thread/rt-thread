/**************************************************************************//**
 * @file     nu_ccap.h
 * @version  V3.00
 * @brief    M460 Series CCAP Driver Header File
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef __NU_CCAP_H__
#define __NU_CCAP_H__

#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup CCAP_Driver CCAP Driver
  @{
*/

/** @addtogroup CCAP_EXPORTED_CONSTANTS CCAP Exported Constants
  @{
*/

/*---------------------------------------------------------------------------------------------------------*/
/* CTL constant definitions                                                                                */
/*---------------------------------------------------------------------------------------------------------*/
#define CCAP_CTL_CCAPEN     (1ul<<CCAP_CTL_CCAPEN_Pos)    /*!< CCAP CTL setting for enabling Camera Capture Interface  \hideinitializer */
#define CCAP_CTL_PKTEN      (1ul<<CCAP_CTL_PKTEN_Pos)     /*!< CCAP CTL setting for enabling packet output mode  \hideinitializer */
#define CCAP_CTL_PLNEN      (1ul<<CCAP_CTL_PLNEN_Pos)     /*!< CCAP CTL setting for enabling planar output mode  \hideinitializer */
#define CCAP_CTL_SHUTTER    (1ul<<CCAP_CTL_SHUTTER_Pos)   /*!< CCAP CTL setting for enabling shutter mode  \hideinitializer */
#define CCAP_CTL_UPDATE     (1ul<<CCAP_CTL_UPDATE_Pos)    /*!< CCAP CTL setting for enabling update register at new frame  \hideinitializer */
#define CCAP_CTL_RESET      (1ul<<CCAP_CTL_VPRST_Pos)     /*!< CCAP CTL setting for capture reset  \hideinitializer */
#define CCAP_CTL_MY8_MY4    (0ul<<CCAP_CTL_MY8_MY4_Pos)   /*!< CCAP CTL setting for 4-bit data I/O interface with Mono \hideinitializer */
#define CCAP_CTL_MY8_MY8    (1ul<<CCAP_CTL_MY8_MY4_Pos)   /*!< CCAP CTL setting for 8-bit data I/O interface with Mono  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/* PAR constant definitions                                                                                */
/*---------------------------------------------------------------------------------------------------------*/
#define CCAP_PAR_INFMT_YUV422 (0ul<<CCAP_PAR_INFMT_Pos)         /*!< CCAP PAR setting for Sensor Input Data YUV422 Format   \hideinitializer */
#define CCAP_PAR_INFMT_RGB565 (1ul<<CCAP_PAR_INFMT_Pos)         /*!< CCAP PAR setting for Sensor Input Data RGB565 Format   \hideinitializer */

#define CCAP_PAR_SENTYPE_CCIR601  (0ul<<CCAP_PAR_SENTYPE_Pos)   /*!< CCAP PAR setting for Sensor Input CCIR601 Type   \hideinitializer */
#define CCAP_PAR_SENTYPE_CCIR656  (1ul<<CCAP_PAR_SENTYPE_Pos)   /*!< CCAP PAR setting for Sensor Input CCIR656 Type   \hideinitializer */

#define CCAP_PAR_INDATORD_YUYV   (0x0ul<<CCAP_PAR_INDATORD_Pos)       /*!< CCAP PAR setting for Sensor Input Data Order, YUYV  \hideinitializer */
#define CCAP_PAR_INDATORD_YVYU   (0x1ul<<CCAP_PAR_INDATORD_Pos)       /*!< CCAP PAR setting for Sensor Input Data Order, YVYU  \hideinitializer */
#define CCAP_PAR_INDATORD_UYVY   (0x2ul<<CCAP_PAR_INDATORD_Pos)       /*!< CCAP PAR setting for Sensor Input Data Order, UYVY  \hideinitializer */
#define CCAP_PAR_INDATORD_VYUY   (0x3ul<<CCAP_PAR_INDATORD_Pos)       /*!< CCAP PAR setting for Sensor Input Data Order, VYUY  \hideinitializer */

#define CCAP_PAR_INDATORD_RGGB   (0x0ul<<CCAP_PAR_INDATORD_Pos)       /*!< CCAP PAR setting for Sensor Input Data Order, 0byte: R[0:4] G[5:8], 1byte G[0:2] R[3:8]  \hideinitializer */
#define CCAP_PAR_INDATORD_BGGR   (0x1ul<<CCAP_PAR_INDATORD_Pos)       /*!< CCAP PAR setting for Sensor Input Data Order, 0byte: b[0:4] G[5:8], 1byte G[0:2] R[3:8]  \hideinitializer */
#define CCAP_PAR_INDATORD_GBRG   (0x2ul<<CCAP_PAR_INDATORD_Pos)       /*!< CCAP PAR setting for Sensor Input Data Order, 0byte: G[0:3] G[4:8], 1byte G[0:4] G[5:8]  \hideinitializer */
#define CCAP_PAR_INDATORD_GRBG   (0x3ul<<CCAP_PAR_INDATORD_Pos)       /*!< CCAP PAR setting for Sensor Input Data Order, 0byte: G[0:3] G[4:8], 1byte G[0:4] G[5:8]  \hideinitializer */

#define CCAP_PAR_PLNFMT_YUV422 (0x0ul<<CCAP_PAR_PLNFMT_Pos)     /*!< CCAP PAR setting for Image Data YUV422P Format Output to System Memory  \hideinitializer */
#define CCAP_PAR_PLNFMT_YUV420 (0x1ul<<CCAP_PAR_PLNFMT_Pos)     /*!< CCAP PAR setting for Image Data YUV420P Format Output to System Memory  \hideinitializer */

#define CCAP_PAR_OUTFMT_YUV422 (0x0ul<<CCAP_PAR_OUTFMT_Pos)     /*!< CCAP PAR setting for Image Data YUV422 Format Output to System Memory  \hideinitializer */
#define CCAP_PAR_OUTFMT_ONLY_Y (0x1ul<<CCAP_PAR_OUTFMT_Pos)     /*!< CCAP PAR setting for Image Data ONLY_Y Format Output to System Memory  \hideinitializer */
#define CCAP_PAR_OUTFMT_RGB555 (0x2ul<<CCAP_PAR_OUTFMT_Pos)     /*!< CCAP PAR setting for Image Data RGB555 Format Output to System Memory  \hideinitializer */
#define CCAP_PAR_OUTFMT_RGB565 (0x3ul<<CCAP_PAR_OUTFMT_Pos)     /*!< CCAP PAR setting for Image Data RGB565 Format Output to System Memory  \hideinitializer */

#define CCAP_PAR_VSP_LOW      (0x0ul<<CCAP_PAR_VSP_Pos)         /*!< CCAP PAR setting for Sensor Vsync Polarity  \hideinitializer */
#define CCAP_PAR_VSP_HIGH     (0x1ul<<CCAP_PAR_VSP_Pos)         /*!< CCAP PAR setting for Sensor Vsync Polarity  \hideinitializer */
#define CCAP_PAR_HSP_LOW      (0x0ul<<CCAP_PAR_HSP_Pos)         /*!< CCAP PAR setting for Sensor Hsync Polarity  \hideinitializer */
#define CCAP_PAR_HSP_HIGH     (0x1ul<<CCAP_PAR_HSP_Pos)         /*!< CCAP PAR setting for Sensor Hsync Polarity  \hideinitializer */
#define CCAP_PAR_PCLKP_LOW    (0x0ul<<CCAP_PAR_PCLKP_Pos)       /*!< CCAP PAR setting for Sensor Pixel Clock Polarity  \hideinitializer */
#define CCAP_PAR_PCLKP_HIGH   (0x1ul<<CCAP_PAR_PCLKP_Pos)       /*!< CCAP PAR setting for Sensor Pixel Clock Polarity  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/* INT constant definitions                                                                                */
/*---------------------------------------------------------------------------------------------------------*/
#define CCAP_INT_VIEN_ENABLE        (0x1ul<<CCAP_INT_VIEN_Pos)        /*!< VININT setting for Video Frame End Interrupt enable  \hideinitializer */
#define CCAP_INT_MEIEN_ENABLE       (0x1ul<<CCAP_INT_MEIEN_Pos)       /*!< VININT setting for Bus Master Transfer Error Interrupt enable  \hideinitializer */
#define CCAP_INT_ADDRMIEN_ENABLE    (0x1ul<<CCAP_INT_ADDRMIEN_Pos)    /*!< VININT setting for Memory Address Match Interrupt enable  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/* Define Error Code                                                                                       */
/*---------------------------------------------------------------------------------------------------------*/
#define CCAP_INVALID_INT               ((int32_t)(0xFFFFFFFF-1))
#define CCAP_INVALID_BUF               ((int32_t)(0xFFFFFFFF-2))
#define CCAP_INVALID_PIPE              ((int32_t)(0xFFFFFFFF-3))

#define CCAP_TIMEOUT_ERR    (-1)    /*!< CCAP operation abort due to timeout error \hideinitializer */

/*@}*/ /* end of group CCAP_EXPORTED_CONSTANTS */

extern int32_t g_CCAP_i32ErrCode;

/** @addtogroup CCAP_EXPORTED_FUNCTIONS CCAP Exported Functions
  @{
*/

/**
 * @brief     Is CCAP module stopped
 *
 * @param     None
 *
 * @retval    0   CCAP module is enabled
 * @retval    1   CCAP module is disabled(stopped)
 *
 * @details   Check Camera Capture Interface module Enable or Disable(stopped)
 *  \hideinitializer
 */
#define CCAP_IS_STOPPED(ccap)  ((ccap->CTL & CCAP_CTL_CCAPEN_Msk)?0:1)

/**
 * @brief     Clear CCAP flag
 *
 * @param[in] u32IntMask interrupt flags settings. It could be
 *                   - \ref CCAP_INT_VINTF_Msk
 *                   - \ref CCAP_INT_MEINTF_Msk
 *                   - \ref CCAP_INT_ADDRMINTF_Msk
 *                   - \ref CCAP_INT_MDINTF_Msk
 *
 * @return    None
 *
 * @details   Clear Camera Capture Interface interrupt flag
 *  \hideinitializer
 */
#define CCAP_CLR_INT_FLAG(ccap, u32IntMask) (ccap->INT |= (u32IntMask))

/**
 * @brief     Get CCAP Interrupt status
 *
 * @param     None
 *
 * @return    CCAP Interrupt Register
 *
 * @details   Get Camera Capture Interface interrupt status.
 * \hideinitializer
 */
#define CCAP_GET_INT_STS(ccap) (ccap->INT)

#define CCAP_SET_CTL(ccap, u32IntMask) (ccap->CTL |= u32IntMask)
#define CCAP_CLR_CTL(ccap, u32IntMask) (ccap->CTL &= ~u32IntMask)

void CCAP_Open(CCAP_T *ccap, uint32_t u32InFormat, uint32_t u32OutFormat);
void CCAP_SetCroppingWindow(CCAP_T *ccap, uint32_t u32VStart, uint32_t u32HStart, uint32_t u32Height, uint32_t u32Width);
void CCAP_SetPacketBuf(CCAP_T *ccap, uint32_t u32Address);
void CCAP_Close(CCAP_T *ccap);
void CCAP_EnableInt(CCAP_T *ccap, uint32_t u32IntMask);
void CCAP_DisableInt(CCAP_T *ccap, uint32_t u32IntMask);
void CCAP_Start(CCAP_T *ccap);
void CCAP_Stop(CCAP_T *ccap, uint32_t u32FrameComplete);
void CCAP_SetPacketScaling(CCAP_T *ccap, uint32_t u32VNumerator, uint32_t u32VDenominator, uint32_t u32HNumerator, uint32_t u32HDenominator);
void CCAP_SetPacketStride(CCAP_T *ccap, uint32_t u32Stride);
void CCAP_EnableMono(CCAP_T *ccap, uint32_t u32Interface);
void CCAP_DisableMono(CCAP_T *ccap);
void CCAP_EnableLumaYOne(CCAP_T *ccap, uint32_t u32th);
void CCAP_DisableLumaYOne(CCAP_T *ccap);

void CCAP_SetPlanarYBuf(CCAP_T *ccap, uint32_t u32Address);
void CCAP_SetPlanarUBuf(CCAP_T *ccap, uint32_t u32Address);
void CCAP_SetPlanarVBuf(CCAP_T *ccap, uint32_t u32Address);
void CCAP_SetPlanarScaling(CCAP_T *ccap, uint32_t u32VNumerator, uint32_t u32VDenominator, uint32_t u32HNumerator, uint32_t u32HDenominator);
void CCAP_SetPlanarStride(CCAP_T *ccap, uint32_t u32Stride);


/*@}*/ /* end of group CCAP_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group CCAP_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif //__NU_CCAP_H__
