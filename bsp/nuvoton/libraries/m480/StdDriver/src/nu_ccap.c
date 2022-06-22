/**************************************************************************//**
 * @file     ccap.c
 * @version  V1.00
 * @brief    M480 Series CCAP Driver Source File
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2016-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/

#include "NuMicro.h"
/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup CCAP_Driver CCAP Driver
  @{
*/


/** @addtogroup CCAP_EXPORTED_FUNCTIONS CCAP Exported Functions
  @{
*/

/**
 * @brief      Open engine clock and sensor clock
 *
 * @param[in]  u32InFormat  The bits corresponding VSP, HSP, PCLK, INFMT, SNRTYPE, OUTFMT, PDORD and PNFMT configurations.
 *             - VSP should be ether \ref CCAP_PAR_VSP_LOW or \ref CCAP_PAR_VSP_HIGH
 *             - HSP should be ether \ref CCAP_PAR_HSP_LOW or \ref CCAP_PAR_HSP_HIGH
 *             - PCLK should be ether \ref CCAP_PAR_PCLKP_LOW or \ref CCAP_PAR_PCLKP_HIGH
 *             - INFMT should be ether \ref CCAP_PAR_INFMT_YUV422 or \ref CCAP_PAR_INFMT_RGB565
 *             - SNRTYPE should be ether \ref CCAP_PAR_SENTYPE_CCIR601 or \ref CCAP_PAR_SENTYPE_CCIR656
 *             - OUTFMT should be one of the following setting
 *                      - \ref CCAP_PAR_OUTFMT_YUV422
 *                      - \ref CCAP_PAR_OUTFMT_ONLY_Y
 *                      - \ref CCAP_PAR_OUTFMT_RGB555
 *                      - \ref CCAP_PAR_OUTFMT_RGB565
 *             - PDORD should be one of the following setting
 *                      - \ref CCAP_PAR_INDATORD_YUYV
 *                      - \ref CCAP_PAR_INDATORD_YVYU
 *                      - \ref CCAP_PAR_INDATORD_UYVY
 *                      - \ref CCAP_PAR_INDATORD_VYUY
 *                      - \ref CCAP_PAR_INDATORD_RGGB
 *                      - \ref CCAP_PAR_INDATORD_BGGR
 *                      - \ref CCAP_PAR_INDATORD_GBRG
 *                      - \ref CCAP_PAR_INDATORD_GRBG
 *             - PNFMT should be one of the following setting
 *                      - \ref CCAP_PAR_PLNFMT_YUV422
 *                      - \ref CCAP_PAR_PLNFMT_YUV420
 *
 * @param[in]  u32OutFormet Capture output format, should be one of following setting
 *                      - \ref CCAP_CTL_PKTEN
 *
 * @return     None
 *
 * @details    Initialize the Image Capture Interface. Register a call back for driver internal using
 */
void CCAP_Open(uint32_t u32InFormat, uint32_t u32OutFormet)
{
    CCAP->PAR = (CCAP->PAR & ~(0x000007BFUL)) | u32InFormat;
    CCAP->CTL = (CCAP->CTL & ~(0x00000040UL)) | u32OutFormet;
}

/**
 * @brief Set Cropping Window Starting Address and Size
 *
 * @param[in] u32VStart: Cropping Window Vertical Starting Address. It should be 0 ~ 0x7FF.
 *
 * @param[in] u32HStart: Cropping Window Horizontal Starting Address. It should be 0 ~ 0x7FF.
 *
 * @param[in] u32Height: Cropping Window Height . It should be 0 ~ 0x7FF.
 *
 * @param[in] u32Width: Cropping Window Width. It should be 0 ~ 0x7FF.
 *
 * @return    None
 *
 * @details   Set Cropping Window Starting Address Register
 */
void CCAP_SetCroppingWindow(uint32_t u32VStart,uint32_t u32HStart, uint32_t u32Height, uint32_t u32Width)
{
    CCAP->CWSP = (CCAP->CWSP & ~(CCAP_CWSP_CWSADDRV_Msk | CCAP_CWSP_CWSADDRH_Msk))
                 | (((u32VStart << 16) | u32HStart));

    CCAP->CWS = (CCAP->CWS & ~(CCAP_CWS_CWH_Msk | CCAP_CWS_CWW_Msk))
                | ((u32Height << 16)| u32Width);
}


/**
 * @brief     Set System Memory Packet Base Address0 Register
 *
 * @param[in]  u32Address : set PKTBA0 register, It should be 0x0 ~ 0xFFFFFFFF
 *
 * @return    None
 *
 * @details   Set System Memory Packet Base Address Register
 */
void CCAP_SetPacketBuf(uint32_t  u32Address )
{
    CCAP->PKTBA0 = u32Address;
    CCAP->CTL |= CCAP_CTL_UPDATE_Msk;
}

/**
 * @brief     Close Camera Capture Interface
 *
 * @return    None
 */
void CCAP_Close(void)
{
    CCAP->CTL &= ~CCAP_CTL_CCAPEN;
}


/**
 * @brief      Set CCAP Interrupt
 *
 * @param[in]  u32IntMask   Interrupt settings. It could be
 *                           - \ref CCAP_INT_VIEN_Msk
 *                           - \ref CCAP_INT_MEIEN_Msk
 *                           - \ref CCAP_INT_ADDRMIEN_Msk
 * @return     None
 *
 * @details    Set Video Frame End Interrupt Enable,
 *                  System Memory Error Interrupt Enable,
 *                  Address Match Interrupt Enable,
 *                  Motion Detection Output Finish Interrupt Enable.
 */
void CCAP_EnableInt(uint32_t u32IntMask)
{
    CCAP->INT = (CCAP->INT & ~(CCAP_INT_VIEN_Msk | CCAP_INT_MEIEN_Msk | CCAP_INT_ADDRMIEN_Msk ) )
                | u32IntMask;
}

/**
 * @brief      Disable CCAP Interrupt
 *
 * @param[in]  u32IntMask   Interrupt settings. It could be
 *                           - \ref CCAP_INT_VINTF_Msk
 *                           - \ref CCAP_INT_MEINTF_Msk
 *                           - \ref CCAP_INT_ADDRMINTF_Msk

 * @return     None
 *
 * @details    Disable Video Frame End Interrupt ,
 *                  System Memory Error Interrupt ,
 *                  Address Match Interrupt and
 *                  Motion Detection Output Finish Interrupt .
 */
void CCAP_DisableInt(uint32_t u32IntMask)
{
    CCAP->INT = (CCAP->INT & ~(u32IntMask) ) ;
}


/**
 * @brief      Enable Monochrome CMOS Sensor
 *
 * @param[in]  u32Interface   I/O interface settings. It could be
 *                           - \ref CCAP_CTL_MY8_MY4
 *                           - \ref CCAP_CTL_MY8_MY8
 * @return     None
 *
 */
void CCAP_EnableMono(uint32_t u32Interface)
{
    CCAP->CTL = (CCAP->CTL & ~CCAP_CTL_MY8_MY4) | CCAP_CTL_MONO_Msk |u32Interface;
}

/**
 * @brief      Disable Monochrome CMOS Sensor
 *
 * @return     None
 *
 */
void CCAP_DisableMono(void)
{
    CCAP->CTL |= CCAP_CTL_MONO_Msk;
}

/**
 * @brief      Enable Luminance 8-bit Y to 1-bit Y Conversion
 *
 * @param[in]  u32th   Luminance Y8 to Y1 Threshold Value, It should be 0 ~ 255.
 *
 * @return     None
 *
 */
void CCAP_EnableLumaYOne(uint32_t u32th)
{
    CCAP->CTL |= CCAP_CTL_Luma_Y_One_Msk;
    CCAP->LUMA_Y1_THD = u32th & 0xff;
}

/**
 * @brief      Disable Luminance 8-bit Y to 1-bit Y Conversion
 *
 * @return     None
 *
 */
void CCAP_DisableLumaYOne(void)
{
    CCAP->CTL &= ~CCAP_CTL_Luma_Y_One_Msk;
}

/**
 * @brief     Start Camera Capture Interface
 *
 * @return    None
 */
void CCAP_Start(void)
{
    CCAP->CTL |= CCAP_CTL_CCAPEN;
}

/**
 * @brief     Stop Camera Capture Interface
 *
 * @param[in]  u32FrameComplete :
 *             TRUE:  Capture module automatically disable the CCAP module after a frame had been captured
 *             FALSE: Stop Capture module now
 * @return    None
 *
 * @details   if u32FrameComplete is set to TRUE then get a new frame and disable CCAP module
 */
void CCAP_Stop(uint32_t u32FrameComplete)
{
    if(u32FrameComplete==FALSE)
        CCAP->CTL &= ~CCAP_CTL_CCAPEN;
    else
    {
        CCAP->CTL |= CCAP_CTL_SHUTTER_Msk;
        while(CCAP_IS_STOPPED());
    }
}

/**
 * @brief     Set Packet Scaling Vertical and Horizontal Factor Register
 *
 * @param[in] u32VNumerator: Packet Scaling Vertical Factor N. It should be 0 ~ FFFF.
 *
 * @param[in] u32VDenominator: Packet Scaling Vertical Factor M. It should be 0 ~ FFFF.
 *
 * @param[in] u32HNumerator: Packet Scaling Vertical Factor N. It should be 0 ~ FFFF.
 *
 * @param[in] u32HDenominator: Packet Scaling Vertical Factor M. It should be 0 ~ FFFF.
 *
 * @return    None
 *
 */
void CCAP_SetPacketScaling(uint32_t u32VNumerator, uint32_t u32VDenominator, uint32_t u32HNumerator, uint32_t u32HDenominator)
{
    uint32_t u32NumeratorL, u32NumeratorH;
    uint32_t u32DenominatorL, u32DenominatorH;

    u32NumeratorL = u32VNumerator&0xFF;
    u32NumeratorH=u32VNumerator>>8;
    u32DenominatorL = u32VDenominator&0xFF;
    u32DenominatorH = u32VDenominator>>8;
    CCAP->PKTSL = (CCAP->PKTSL & ~(CCAP_PKTSL_PKTSVNL_Msk | CCAP_PKTSL_PKTSVML_Msk))
                  | ((u32NumeratorL << 24)| (u32DenominatorL << 16));
    CCAP->PKTSM = (CCAP->PKTSM & ~(CCAP_PKTSM_PKTSVNH_Msk | CCAP_PKTSM_PKTSVMH_Msk))
                  | ((u32NumeratorH << 24) | (u32DenominatorH << 16));

    u32NumeratorL = u32HNumerator&0xFF;
    u32NumeratorH=u32HNumerator>>8;
    u32DenominatorL = u32HDenominator&0xFF;
    u32DenominatorH = u32HDenominator>>8;
    CCAP->PKTSL = (CCAP->PKTSL & ~(CCAP_PKTSL_PKTSHNL_Msk | CCAP_PKTSL_PKTSHML_Msk))
                  | ((u32NumeratorL << 8)| u32DenominatorL);
    CCAP->PKTSM = (CCAP->PKTSM & ~(CCAP_PKTSM_PKTSHNH_Msk | CCAP_PKTSM_PKTSHMH_Msk))
                  | ((u32NumeratorH << 8) | u32DenominatorH);
}

/**
 * @brief     Set Packet Frame Output Pixel Stride Width.
 *
 * @param[in] u32Stride : set PKTSTRIDE register, It should be 0x0 ~ 0x3FFF
 *
 * @return    None
 *
 * @details   Set Packet Frame Output Pixel Stride Width
 */
void CCAP_SetPacketStride(uint32_t u32Stride )
{
    CCAP->STRIDE = (CCAP->STRIDE & ~CCAP_STRIDE_PKTSTRIDE_Msk) | u32Stride;
}


/*@}*/ /* end of group CCAP_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group CCAP_Driver */

/*@}*/ /* end of group Standard_Driver */

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
