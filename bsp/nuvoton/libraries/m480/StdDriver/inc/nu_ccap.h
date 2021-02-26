/**************************************************************************//**
 * @file     nu_ccap.h
 * @version  V1.00
 * @brief    M480 Series CCAP Driver Header File
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2016-2020 Nuvoton Technology Corp. All rights reserved.
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
/* CTL constant definitions                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define CCAP_CTL_CCAPEN     (1ul<<CCAP_CTL_CCAPEN_Pos)    /*!< CCAP CTL setting for enabling capture engine mode  \hideinitializer */
#define CCAP_CTL_ADDRSW     (1ul<<CCAP_CTL_ADDRSW_Pos)    /*!< CCAP CTL setting for packet buffer address switch  \hideinitializer */
#define CCAP_CTL_PKTEN      (1ul<<CCAP_CTL_PKTEN_Pos)     /*!< CCAP CTL setting for enabling packet output mode  \hideinitializer */
#define CCAP_CTL_PLNEN      (1ul<<CCAP_CTL_PLNEN_Pos)     /*!< CCAP CTL setting for enabling planar output mode  \hideinitializer */
#define CCAP_CTL_SHUTTER    (1ul<<CCAP_CTL_SHUTTER_Pos)   /*!< CCAP CTL setting for enabling shutter mode  \hideinitializer */
#define CCAP_CTL_UPDATE     (1ul<<CCAP_CTL_UPDATE_Pos)    /*!< CCAP CTL setting for enabling update register at new frame  \hideinitializer */
#define CCAP_CTL_RESET      (1ul<<CCAP_CTL_VPRST_Pos)     /*!< CCAP CTL setting for capture reset  \hideinitializer */
#define CCAP_CTL_MY8_MY4    (0ul<<CCAP_CTL_MY8_MY4_Pos)   /*!< CCAP CTL setting for 4-bit data I/O interface with Mono \hideinitializer */
#define CCAP_CTL_MY8_MY8    (1ul<<CCAP_CTL_MY8_MY4_Pos)   /*!< CCAP CTL setting for 8-bit data I/O interface with Mono  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/* PAR constant definitions                                                                            */
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

#define CCAP_PAR_OUTFMT_YUV422 (0x0ul<<CCAP_PAR_OUTFMT_Pos)     /*!< CCAP PAR setting for Image Data YUV422 Format Output to System Memory  \hideinitializer */
#define CCAP_PAR_OUTFMT_ONLY_Y (0x1ul<<CCAP_PAR_OUTFMT_Pos)     /*!< CCAP PAR setting for Image Data ONLY_Y Format Output to System Memory  \hideinitializer */
#define CCAP_PAR_OUTFMT_RGB555 (0x2ul<<CCAP_PAR_OUTFMT_Pos)     /*!< CCAP PAR setting for Image Data RGB555 Format Output to System Memory  \hideinitializer */
#define CCAP_PAR_OUTFMT_RGB565 (0x3ul<<CCAP_PAR_OUTFMT_Pos)     /*!< CCAP PAR setting for Image Data RGB565 Format Output to System Memory  \hideinitializer */

#define CCAP_PAR_PLNFMT_YUV422 (0x0ul<<CCAP_PAR_PLNFMT_Pos)       /*!< CCAP PAR setting for Planar Output YUV422 Format  \hideinitializer */
#define CCAP_PAR_PLNFMT_YUV420 (0x1ul<<CCAP_PAR_PLNFMT_Pos)       /*!< CCAP PAR setting for Planar Output YUV420 Format  \hideinitializer */

#define CCAP_PAR_VSP_LOW      (0x0ul<<CCAP_PAR_VSP_Pos)         /*!< CCAP PAR setting for Sensor Vsync Polarity  \hideinitializer */
#define CCAP_PAR_VSP_HIGH     (0x1ul<<CCAP_PAR_VSP_Pos)         /*!< CCAP PAR setting for Sensor Vsync Polarity  \hideinitializer */
#define CCAP_PAR_HSP_LOW      (0x0ul<<CCAP_PAR_HSP_Pos)         /*!< CCAP PAR setting for Sensor Hsync Polarity  \hideinitializer */
#define CCAP_PAR_HSP_HIGH     (0x1ul<<CCAP_PAR_HSP_Pos)         /*!< CCAP PAR setting for Sensor Hsync Polarity  \hideinitializer */
#define CCAP_PAR_PCLKP_LOW    (0x0ul<<CCAP_PAR_PCLKP_Pos)       /*!< CCAP PAR setting for Sensor Pixel Clock Polarity  \hideinitializer */
#define CCAP_PAR_PCLKP_HIGH   (0x1ul<<CCAP_PAR_PCLKP_Pos)       /*!< CCAP PAR setting for Sensor Pixel Clock Polarity  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/* INT constant definitions                                                                             */
/*---------------------------------------------------------------------------------------------------------*/
#define CCAP_INT_VIEN_ENABLE        (0x1ul<<CCAP_INT_VIEN_Pos)        /*!< VININT setting for Frame End Interrupt enable  \hideinitializer */
#define CCAP_INT_MEIEN_ENABLE       (0x1ul<<CCAP_INT_MEIEN_Pos)       /*!< VININT setting for Bus Master Transfer Error Interrupt enable  \hideinitializer */
#define CCAP_INT_ADDRMIEN_ENABLE    (0x1ul<<CCAP_INT_ADDRMIEN_Pos)    /*!< VININT setting for Memory Address Match Interrupt enable  \hideinitializer */
#define CCAP_INT_MDIEN_ENABLE       (0x1ul<<CCAP_INT_MDIEN_Pos)       /*!< VININT setting for Motion Detection Output Finish Interrupt Enable enable  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Define Error Code                                                                                      */
/*---------------------------------------------------------------------------------------------------------*/
#define CCAP_INVALID_INT               ((int32_t)(0xFFFFFFFF-1))
#define CCAP_INVALID_BUF               ((int32_t)(0xFFFFFFFF-2))
#define CCAP_INVALID_PIPE              ((int32_t)(0xFFFFFFFF-3))


/*@}*/ /* end of group NUC472_442_CCAP_EXPORTED_CONSTANTS */



/** @addtogroup CCAP_EXPORTED_FUNCTIONS CCAP Exported Functions
  @{
*/

/**
 * @brief     Is CCAP module Enable
 *
 * @return   FALSE(Enable) or TRUE(Disable)
 *
 * @details   Check Camera Capture Interface module Enable or Disable
 *  \hideinitializer
 */
#define CCAP_IS_STOPPED()  ((CCAP->CTL & CCAP_CTL_CCAPEN_Msk)?0:1)

/**
 * @brief     Clear CCAP flag
 *
 * @param[in] u32IntMask interrupt flags settings. It could be
 *                   - \ref CCAP_INT_VINTF_Msk
 *                   - \ref CCAP_INT_MEINTF_Msk
 *                   - \ref CCAP_INT_ADDRMINTF_Msk
 *                   - \ref CCAP_INT_MDINTF_Msk
 *
 * @return    TRUE(Enable) or FALSE(Disable)
 *
 * @details   Clear Image Capture Interface interrupt flag
 *  \hideinitializer
 */
#define CCAP_CLR_INT_FLAG(u32IntMask) (CCAP->INT |=u32IntMask)

/**
 * @brief     Get CCAP Interrupt status
 *
 * @return    TRUE(Enable) or FALSE(Disable)
 *
 * @details   Get Image Capture Interface interrupt status.
 * \hideinitializer
 */
#define CCAP_GET_INT_STS() (CCAP->INT)

void CCAP_Open(uint32_t u32InFormat, uint32_t u32OutFormet);
void CCAP_SetCroppingWindow(uint32_t u32VStart,uint32_t u32HStart, uint32_t u32Height, uint32_t u32Width);
void CCAP_SetPacketBuf(uint32_t  u32Address );
void CCAP_Close(void);
void CCAP_EnableInt(uint32_t u32IntMask);
void CCAP_DisableInt(uint32_t u32IntMask);
void CCAP_Start(void);
void CCAP_Stop(uint32_t u32FrameComplete);
void CCAP_SetPacketScaling(uint32_t u32VNumerator, uint32_t u32VDenominator, uint32_t u32HNumerator, uint32_t u32HDenominator);
void CCAP_SetPacketStride(uint32_t u32Stride );
void CCAP_EnableMono(uint32_t u32Interface);
void CCAP_DisableMono(void);
void CCAP_EnableLumaYOne(uint32_t u32th);
void CCAP_DisableLumaYOne(void);

/*@}*/ /* end of group CCAP_EXPORTED_FUNCTIONS */



/*@}*/ /* end of group CCAP_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif //__NU_CCAP_H__

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
