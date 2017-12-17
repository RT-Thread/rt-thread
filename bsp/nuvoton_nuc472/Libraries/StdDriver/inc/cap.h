/**************************************************************************//**
 * @file     cap.h
 * @version  V0.10
 * $Revision: 17 $
 * $Date: 15/10/22 10:00a $
 * @brief    NUC470 series Image Capture Driver Header File
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#ifndef __CAP_H__
#define __CAP_H__

#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup NUC472_442_Device_Driver NUC472/NUC442 Device Driver
  @{
*/

/** @addtogroup NUC472_442_CAP_Driver CAP Driver
  @{
*/

/** @addtogroup NUC472_442_CAP_EXPORTED_CONSTANTS CAP Exported Constants
  @{
*/

/*---------------------------------------------------------------------------------------------------------*/
/* VINCTRL constant definitions                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define CAP_CTL_CAPEN      (1ul<<CAP_CTL_CAPEN_Pos)     /*!< CAP CTL setting for enabling capture engine mode  \hideinitializer */
#define CAP_CTL_ADDRSW     (1ul<<CAP_CTL_ADDRSW_Pos)    /*!< CAP CTL setting for packet buffer address switch  \hideinitializer */
#define CAP_CTL_PKTEN      (1ul<<CAP_CTL_PKTEN_Pos)     /*!< CAP CTL setting for enabling packet output mode  \hideinitializer */
#define CAP_CTL_PLNEN      (1ul<<CAP_CTL_PLNEN_Pos)     /*!< CAP CTL setting for enabling planar output mode  \hideinitializer */
#define CAP_CTL_SHUTTER    (1ul<<CAP_CTL_SHUTTER_Pos)   /*!< CAP CTL setting for enabling shutter mode  \hideinitializer */
#define CAP_CTL_UPDATE     (1ul<<CAP_CTL_UPDATE_Pos)    /*!< CAP CTL setting for enabling update register at new frame  \hideinitializer */
#define CAP_CTL_RESET      (1ul<<CAP_CTL_VPRST_Pos)     /*!< CAP CTL setting for capture reset  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/* CAPPAR constant definitions                                                                             */
/*---------------------------------------------------------------------------------------------------------*/
#define CAP_PAR_INFMT_YUV422 (0ul<<CAP_PAR_INFMT_Pos)         /*!< CAP PAR setting for Sensor Input Data YUV422 Format   \hideinitializer */
#define CAP_PAR_INFMT_RGB565 (1ul<<CAP_PAR_INFMT_Pos)         /*!< CAP PAR setting for Sensor Input Data RGB565 Format   \hideinitializer */
                                                                       
#define CAP_PAR_SENTYPE_CCIR601  (0ul<<CAP_PAR_SENTYPE_Pos)   /*!< CAP PAR setting for Sensor Input CCIR601 Type   \hideinitializer */
#define CAP_PAR_SENTYPE_CCIR656  (1ul<<CAP_PAR_SENTYPE_Pos)   /*!< CAP PAR setting for Sensor Input CCIR656 Type   \hideinitializer */

#define CAP_PAR_INDATORD_YUYV   (0x0ul<<CAP_PAR_INDATORD_Pos)       /*!< CAP PAR setting for Sensor Input Data Order, YUYV  \hideinitializer */
#define CAP_PAR_INDATORD_YVYU   (0x1ul<<CAP_PAR_INDATORD_Pos)       /*!< CAP PAR setting for Sensor Input Data Order, YVYU  \hideinitializer */
#define CAP_PAR_INDATORD_UYVY   (0x2ul<<CAP_PAR_INDATORD_Pos)       /*!< CAP PAR setting for Sensor Input Data Order, UYVY  \hideinitializer */
#define CAP_PAR_INDATORD_VYUY   (0x3ul<<CAP_PAR_INDATORD_Pos)       /*!< CAP PAR setting for Sensor Input Data Order, VYUY  \hideinitializer */

#define CAP_PAR_INDATORD_RGGB   (0x0ul<<CAP_PAR_INDATORD_Pos)       /*!< CAP PAR setting for Sensor Input Data Order, 0byte: R[0:4] G[5:8], 1byte G[0:2] R[3:8]  \hideinitializer */
#define CAP_PAR_INDATORD_BGGR   (0x1ul<<CAP_PAR_INDATORD_Pos)       /*!< CAP PAR setting for Sensor Input Data Order, 0byte: b[0:4] G[5:8], 1byte G[0:2] R[3:8]  \hideinitializer */
#define CAP_PAR_INDATORD_GBRG   (0x2ul<<CAP_PAR_INDATORD_Pos)       /*!< CAP PAR setting for Sensor Input Data Order, 0byte: G[0:3] G[4:8], 1byte G[0:4] G[5:8]  \hideinitializer */
#define CAP_PAR_INDATORD_GRBG   (0x3ul<<CAP_PAR_INDATORD_Pos)       /*!< CAP PAR setting for Sensor Input Data Order, 0byte: G[0:3] G[4:8], 1byte G[0:4] G[5:8]  \hideinitializer */

#define CAP_PAR_OUTFMT_YUV422 (0x0ul<<CAP_PAR_OUTFMT_Pos)     /*!< CAP PAR setting for Image Data YUV422 Format Output to System Memory  \hideinitializer */
#define CAP_PAR_OUTFMT_ONLY_Y (0x1ul<<CAP_PAR_OUTFMT_Pos)     /*!< CAP PAR setting for Image Data ONLY_Y Format Output to System Memory  \hideinitializer */
#define CAP_PAR_OUTFMT_RGB555 (0x2ul<<CAP_PAR_OUTFMT_Pos)     /*!< CAP PAR setting for Image Data RGB555 Format Output to System Memory  \hideinitializer */
#define CAP_PAR_OUTFMT_RGB565 (0x3ul<<CAP_PAR_OUTFMT_Pos)     /*!< CAP PAR setting for Image Data RGB565 Format Output to System Memory  \hideinitializer */

#define CAP_PAR_PLNFMT_YUV422 (0x0ul<<CAP_PAR_PLNFMT_Pos)       /*!< CAP PAR setting for Planar Output YUV422 Format  \hideinitializer */
#define CAP_PAR_PLNFMT_YUV420 (0x1ul<<CAP_PAR_PLNFMT_Pos)       /*!< CAP PAR setting for Planar Output YUV420 Format  \hideinitializer */

#define CAP_PAR_VSP_LOW      (0x0ul<<CAP_PAR_VSP_Pos)         /*!< CAP PAR setting for Sensor Vsync Polarity  \hideinitializer */
#define CAP_PAR_VSP_HIGH     (0x1ul<<CAP_PAR_VSP_Pos)         /*!< CAP PAR setting for Sensor Vsync Polarity  \hideinitializer */
#define CAP_PAR_HSP_LOW      (0x0ul<<CAP_PAR_HSP_Pos)         /*!< CAP PAR setting for Sensor Hsync Polarity  \hideinitializer */
#define CAP_PAR_HSP_HIGH     (0x1ul<<CAP_PAR_HSP_Pos)         /*!< CAP PAR setting for Sensor Hsync Polarity  \hideinitializer */
#define CAP_PAR_PCLKP_LOW    (0x0ul<<CAP_PAR_PCLKP_Pos)       /*!< CAP PAR setting for Sensor Pixel Clock Polarity  \hideinitializer */
#define CAP_PAR_PCLKP_HIGH   (0x1ul<<CAP_PAR_PCLKP_Pos)       /*!< CAP PAR setting for Sensor Pixel Clock Polarity  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/* VININT constant definitions                                                                             */
/*---------------------------------------------------------------------------------------------------------*/
#define CAP_INT_VIEN_ENABLE        (0x1ul<<CAP_INT_VIEN_Pos)        /*!< VININT setting for Frame End Interrupt enable  \hideinitializer */
#define CAP_INT_MEIEN_ENABLE       (0x1ul<<CAP_INT_MEIEN_Pos)       /*!< VININT setting for Bus Master Transfer Error Interrupt enable  \hideinitializer */
#define CAP_INT_ADDRMIEN_ENABLE    (0x1ul<<CAP_INT_ADDRMIEN_Pos)    /*!< VININT setting for Memory Address Match Interrupt enable  \hideinitializer */
#define CAP_INT_MDIEN_ENABLE       (0x1ul<<CAP_INT_MDIEN_Pos)       /*!< VININT setting for Motion Detection Output Finish Interrupt Enable enable  \hideinitializer */


static uint32_t u32EscapeFrame = 0;
/*---------------------------------------------------------------------------------------------------------*/
/*  Define Error Code                                                                                      */
/*---------------------------------------------------------------------------------------------------------*/
#define CAP_INVALID_INT               ((int32_t)(0xFFFFFFFF-1))
#define CAP_INVALID_BUF               ((int32_t)(0xFFFFFFFF-2))
#define CAP_INVALID_PIPE              ((int32_t)(0xFFFFFFFF-3))


/*@}*/ /* end of group NUC472_442_CAP_EXPORTED_CONSTANTS */



/** @addtogroup NUC472_442_CAP_EXPORTED_FUNCTIONS CAP Exported Functions
  @{
*/

/**
 * @brief     Is CAP module Enable
 *
 * @return   FALSE(Enable) or TRUE(Disable)
 *
 * @details   Check Image Capture Interface module Enable or Disable
 *  \hideinitializer 
 */
#define CAP_IS_STOPPED()  ((ICAP->CTL & CAP_CTL_CAPEN_Msk)?0:1)

/**
 * @brief     Clear CAP flag
 *
 * @param[in] u32IntMask interrupt flags settings. It could be
 *                   - \ref CAP_INT_VINTF_Msk
 *                   - \ref CAP_INT_MEINTF_Msk
 *                   - \ref CAP_INT_ADDRMINTF_Msk
 *                   - \ref CAP_INT_MDINTF_Msk
 *
 * @return    TRUE(Enable) or FALSE(Disable)
 *
 * @details   Clear Image Capture Interface interrupt flag
 *  \hideinitializer 
 */
#define CAP_CLR_INT_FLAG(u32IntMask) (ICAP->INT |=u32IntMask)

/**
 * @brief     Get CAP Interrupt status
 *
 * @return    TRUE(Enable) or FALSE(Disable)
 *
 * @details   Get Image Capture Interface interrupt status.
 * \hideinitializer 
 */
#define CAP_GET_INT_STS() (ICAP->INT)

void CAP_Open(uint32_t u32InFormat, uint32_t u32OutFormet);
void CAP_SetCroppingWindow(uint32_t u32VStart,uint32_t u32HStart, uint32_t u32Height, uint32_t u32Width);
void CAP_SetPacketBuf(uint32_t  u32Address );
void CAP_SetPlanarBuf(uint32_t u32YAddr, uint32_t u32UAddr, uint32_t u32VAddr);
void CAP_Close(void);
void CAP_EnableInt(uint32_t u32IntMask);
void CAP_DisableInt(uint32_t u32IntMask);
void CAP_Start(void);
void CAP_Stop(uint32_t u32FrameComplete);
void CAP_SetPacketScaling(uint32_t u32VNumerator, uint32_t u32VDenominator, uint32_t u32HNumerator, uint32_t u32HDenominator);
void CAP_SetPlanarScaling(uint32_t u32VNumerator, uint32_t u32VDenominator, uint32_t u32HNumerator, uint32_t u32HDenominator);
void CAP_SetPacketStride(uint32_t u32Stride );
void CAP_SetPlanarStride(uint32_t u32Stride );
void CAP_EnableMotionDet(uint32_t u32Freq, uint32_t u32BlockSize, uint32_t u32Format, uint32_t u32Threshold,  uint32_t u32YDetAddr, uint32_t u32DetAddr);
void CAP_DisableMotionDet(void);

/*@}*/ /* end of group NUC472_442_CAP_EXPORTED_FUNCTIONS */



/*@}*/ /* end of group NUC472_442_CAP_Driver */

/*@}*/ /* end of group NUC472_442_Device_Driver */

#ifdef __cplusplus
}
#endif

#endif //__CAP_H__

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
