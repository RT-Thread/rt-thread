/**************************************************************************//**
 * @file     ccap.c
 * @version  V3.00
 * @brief    M460 Series CCAP Driver Source File
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/

#include "NuMicro.h"
/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup CCAP_Driver CCAP Driver
  @{
*/

int32_t g_CCAP_i32ErrCode = 0;       /*!< CCAP global error code */

/** @addtogroup CCAP_EXPORTED_FUNCTIONS CCAP Exported Functions
  @{
*/

/**
 * @brief      Open and set CCAP function
 *
 * @param[in]  u32InFormat  The bits corresponding VSP, HSP, PCLK, INFMT, SNRTYPE, OUTFMT and PDORD configurations.
 *             - VSP     Sensor Vsync Polarity. It should be either \ref CCAP_PAR_VSP_LOW or \ref CCAP_PAR_VSP_HIGH
 *             - HSP     Sensor Hsync Polarity. It should be either \ref CCAP_PAR_HSP_LOW or \ref CCAP_PAR_HSP_HIGH
 *             - PCLK    Sensor Pixel Clock Polarity. It should be either \ref CCAP_PAR_PCLKP_LOW or \ref CCAP_PAR_PCLKP_HIGH
 *             - INFMT   Sensor Input Data Format. It should be either \ref CCAP_PAR_INFMT_YUV422 or \ref CCAP_PAR_INFMT_RGB565
 *             - SNRTYPE Sensor Input Type. It should be either \ref CCAP_PAR_SENTYPE_CCIR601 or \ref CCAP_PAR_SENTYPE_CCIR656
 *             - PLNFMT  Planar Output YUV Format
 *                       - \ref 0 = YUV422
 *             - OUTFMT  Image Data Format Output to System Memory. It should be one of the following settings
 *                       - \ref CCAP_PAR_OUTFMT_YUV422
 *                       - \ref CCAP_PAR_OUTFMT_ONLY_Y
 *                       - \ref CCAP_PAR_OUTFMT_RGB555
 *                       - \ref CCAP_PAR_OUTFMT_RGB565
 *             - PDORD   Sensor Input Data Order. It should be one of the following settings
 *                       - \ref CCAP_PAR_INDATORD_YUYV
 *                       - \ref CCAP_PAR_INDATORD_YVYU
 *                       - \ref CCAP_PAR_INDATORD_UYVY
 *                       - \ref CCAP_PAR_INDATORD_VYUY
 *                       - \ref CCAP_PAR_INDATORD_RGGB
 *                       - \ref CCAP_PAR_INDATORD_BGGR
 *                       - \ref CCAP_PAR_INDATORD_GBRG
 *                       - \ref CCAP_PAR_INDATORD_GRBG
 * @param[in]  u32OutFormat Image Data Output Format. It should be
 *                       - \ref CCAP_CTL_PKTEN
 *
 * @return     None
 *
 * @details    Initialize the Camera Capture Interface.
 */
void CCAP_Open(CCAP_T *ccap, uint32_t u32InFormat, uint32_t u32OutFormat)
{
    ccap->PAR = (ccap->PAR & ~(0x000007BFUL)) | u32InFormat;
    ccap->CTL = (ccap->CTL & ~(0x00000060UL)) | u32OutFormat;
}

/**
 * @brief      Set Cropping Window Starting Address and Size
 *
 * @param[in]  u32VStart: Cropping Window Vertical Starting Address. It should be 0 ~ 0x7FF.
 * @param[in]  u32HStart: Cropping Window Horizontal Starting Address. It should be 0 ~ 0x7FF.
 * @param[in]  u32Height: Cropping Window Height. It should be 0 ~ 0x7FF.
 * @param[in]  u32Width:  Cropping Window Width. It should be 0 ~ 0x7FF.
 *
 * @return     None
 *
 * @details    This function is used to set cropping window starting address and size.
 */
void CCAP_SetCroppingWindow(CCAP_T *ccap, uint32_t u32VStart, uint32_t u32HStart, uint32_t u32Height, uint32_t u32Width)
{
    ccap->CWSP = (ccap->CWSP & ~(CCAP_CWSP_CWSADDRV_Msk | CCAP_CWSP_CWSADDRH_Msk))
                 | (((u32VStart << 16) | u32HStart));

    ccap->CWS = (ccap->CWS & ~(CCAP_CWS_CWH_Msk | CCAP_CWS_CWW_Msk))
                | ((u32Height << 16) | u32Width);
}

/**
 * @brief      Set System Memory Packet Base Address
 *
 * @param[in]  u32Address: Set CCAP_PKTBA0 register. It should be 0x0 ~ 0xFFFFFFFF.
 *
 * @return     None
 *
 * @details    This function is used to set System Memory Packet Base Address 0 Register.
 */
void CCAP_SetPacketBuf(CCAP_T *ccap, uint32_t u32Address)
{
    ccap->PKTBA0 = u32Address;
    ccap->CTL |= CCAP_CTL_UPDATE_Msk;
}

/**
 * @brief      Set System Memory Planar Y Base Address
 *
 * @param[in]  u32Address: Set CCAP_YBA register. It should be 0x0 ~ 0xFFFFFFFF.
 *
 * @return     None
 *
 * @details    This function is used to set System Memory Planar Y Base Address 0 Register.
 */
void CCAP_SetPlanarYBuf(CCAP_T *ccap, uint32_t u32Address)
{
    ccap->YBA = u32Address;
    ccap->CTL |= CCAP_CTL_UPDATE_Msk;
}

/**
 * @brief      Set System Memory Planar U Base Address
 *
 * @param[in]  u32Address: Set CCAP_UBA register. It should be 0x0 ~ 0xFFFFFFFF.
 *
 * @return     None
 *
 * @details    This function is used to set System Memory Planar U Base Address 0 Register.
 */
void CCAP_SetPlanarUBuf(CCAP_T *ccap, uint32_t u32Address)
{
    ccap->UBA = u32Address;
    ccap->CTL |= CCAP_CTL_UPDATE_Msk;
}

/**
 * @brief      Set System Memory Planar V Base Address
 *
 * @param[in]  u32Address: Set CCAP_VBA register. It should be 0x0 ~ 0xFFFFFFFF.
 *
 * @return     None
 *
 * @details    This function is used to set System Memory Planar V Base Address 0 Register.
 */
void CCAP_SetPlanarVBuf(CCAP_T *ccap, uint32_t u32Address)
{
    ccap->VBA = u32Address;
    ccap->CTL |= CCAP_CTL_UPDATE_Msk;
}

/**
 * @brief      Close Camera Capture Interface
 *
 * @param      None
 *
 * @return     None
 *
 * @details    This function is used to disable Camera Capture Interface.
 */
void CCAP_Close(CCAP_T *ccap)
{
    ccap->CTL &= ~CCAP_CTL_CCAPEN;
}

/**
 * @brief      Enable CCAP Interrupt
 *
 * @param[in]  u32IntMask  Interrupt settings. It could be
 *                         - \ref CCAP_INT_VIEN_Msk
 *                         - \ref CCAP_INT_MEIEN_Msk
 *                         - \ref CCAP_INT_ADDRMIEN_Msk
 *
 * @return     None
 *
 * @details    This function is used to enable Video Frame End Interrupt,
 *             Bus Master Transfer Error Interrupt and Memory Address Match Interrupt.
 */
void CCAP_EnableInt(CCAP_T *ccap, uint32_t u32IntMask)
{
    ccap->INT = (ccap->INT & ~(CCAP_INT_VIEN_Msk | CCAP_INT_MEIEN_Msk | CCAP_INT_ADDRMIEN_Msk))
                | u32IntMask;
}

/**
 * @brief      Disable CCAP Interrupt
 *
 * @param[in]  u32IntMask  Interrupt settings. It could be
 *                         - \ref CCAP_INT_VINTF_Msk
 *                         - \ref CCAP_INT_MEINTF_Msk
 *                         - \ref CCAP_INT_ADDRMINTF_Msk
 *
 * @return     None
 *
 * @details    This function is used to disable Video Frame End Interrupt,
 *             Bus Master Transfer Error Interrupt and Memory Address Match Interrupt.
 */
void CCAP_DisableInt(CCAP_T *ccap, uint32_t u32IntMask)
{
    ccap->INT = (ccap->INT & ~(u32IntMask));
}

/**
 * @brief      Enable Monochrome CMOS Sensor
 *
 * @param[in]  u32Interface  Data I/O interface setting. It could be
 *                           - \ref CCAP_CTL_MY8_MY4
 *                           - \ref CCAP_CTL_MY8_MY8
 * @return     None
 *
 * @details    This function is used to select monochrome CMOS sensor and set data width.
 */
void CCAP_EnableMono(CCAP_T *ccap, uint32_t u32Interface)
{
    ccap->CTL = (ccap->CTL & ~CCAP_CTL_MY8_MY4) | CCAP_CTL_MONO_Msk | u32Interface;
}

/**
 * @brief      Disable Monochrome CMOS Sensor
 *
 * @param      None
 *
 * @return     None
 *
 * @details    This function is used to disable monochrome CMOS sensor selection.
 */
void CCAP_DisableMono(CCAP_T *ccap)
{
    ccap->CTL &= ~CCAP_CTL_MONO_Msk;
}

/**
 * @brief      Enable Luminance 8-bit Y to 1-bit Y Conversion
 *
 * @param[in]  u32th   Luminance Y8 to Y1 Threshold Value. It should be 0 ~ 255.
 *
 * @return     None
 *
 * @details    This function is used to enable luminance Y8 to Y1 function and set its threshold value.
 */
void CCAP_EnableLumaYOne(CCAP_T *ccap, uint32_t u32th)
{
    ccap->CTL |= CCAP_CTL_Luma_Y_One_Msk;
    ccap->LUMA_Y1_THD = u32th & 0xff;
}

/**
 * @brief      Disable Luminance 8-bit Y to 1-bit Y Conversion
 *
 * @param      None
 *
 * @return     None
 *
 * @details    This function is used to disable luminance Y8 to Y1 function.
 *
 */
void CCAP_DisableLumaYOne(CCAP_T *ccap)
{
    ccap->CTL &= ~CCAP_CTL_Luma_Y_One_Msk;
}

/**
 * @brief      Start Camera Capture Interface
 *
 * @param      None
 *
 * @return     None
 *
 * @details    This function is used to start Camera Capture Interface function.
 */
void CCAP_Start(CCAP_T *ccap)
{
    ccap->CTL |= CCAP_CTL_CCAPEN;
}

/**
 * @brief      Stop Camera Capture Interface
 *
 * @param[in]  u32FrameComplete:
 *             - \ref TRUE:  Capture module disables the CCAP module automatically after a frame had been captured.
 *             - \ref FALSE: Stop Capture module now.
 *
 * @return     None
 *
 * @details    If u32FrameComplete is set to TRUE then get a new frame and disable CCAP module.
 *
 * @note       This function sets g_CCAP_i32ErrCode to CCAP_TIMEOUT_ERR if the CCAP_IS_STOPPED() longer than expected.
 */
void CCAP_Stop(CCAP_T *ccap, uint32_t u32FrameComplete)
{
    uint32_t u32TimeOutCount = SystemCoreClock;

    if (u32FrameComplete == FALSE)
        ccap->CTL &= ~CCAP_CTL_CCAPEN;
    else
    {
        ccap->CTL |= CCAP_CTL_SHUTTER_Msk;
        while (!CCAP_IS_STOPPED(ccap))
        {
            if (--u32TimeOutCount == 0)
            {
                g_CCAP_i32ErrCode = CCAP_TIMEOUT_ERR;
                break;
            }
        }
    }
}

/**
 * @brief      Set Packet Scaling Factor
 *
 * @param[in]  u32VNumerator:   Packet Scaling Vertical Factor N. It should be 0x0 ~ 0xFFFF.
 * @param[in]  u32VDenominator: Packet Scaling Vertical Factor M. It should be 0x0 ~ 0xFFFF.
 * @param[in]  u32HNumerator:   Packet Scaling Horizontal Factor N. It should be 0x0 ~ 0xFFFF.
 * @param[in]  u32HDenominator: Packet Scaling Horizontal Factor M. It should be 0x0 ~ 0xFFFF.
 *
 * @return     None
 *
 * @details    This function is used to set Packet Scaling Vertical and Horizontal Factor register.
 */
void CCAP_SetPacketScaling(CCAP_T *ccap, uint32_t u32VNumerator, uint32_t u32VDenominator, uint32_t u32HNumerator, uint32_t u32HDenominator)
{
    uint32_t u32NumeratorL, u32NumeratorH;
    uint32_t u32DenominatorL, u32DenominatorH;

    u32NumeratorL = u32VNumerator & 0xFF;
    u32NumeratorH = u32VNumerator >> 8;
    u32DenominatorL = u32VDenominator & 0xFF;
    u32DenominatorH = u32VDenominator >> 8;
    ccap->PKTSL = (ccap->PKTSL & ~(CCAP_PKTSL_PKTSVNL_Msk | CCAP_PKTSL_PKTSVML_Msk))
                  | ((u32NumeratorL << CCAP_PKTSL_PKTSVNL_Pos) | (u32DenominatorL << CCAP_PKTSL_PKTSVML_Pos));
    ccap->PKTSM = (ccap->PKTSM & ~(CCAP_PKTSM_PKTSVNH_Msk | CCAP_PKTSM_PKTSVMH_Msk))
                  | ((u32NumeratorH << CCAP_PKTSL_PKTSVNL_Pos) | (u32DenominatorH << CCAP_PKTSL_PKTSVML_Pos));

    u32NumeratorL = u32HNumerator & 0xFF;
    u32NumeratorH = u32HNumerator >> 8;
    u32DenominatorL = u32HDenominator & 0xFF;
    u32DenominatorH = u32HDenominator >> 8;
    ccap->PKTSL = (ccap->PKTSL & ~(CCAP_PKTSL_PKTSHNL_Msk | CCAP_PKTSL_PKTSHML_Msk))
                  | ((u32NumeratorL << CCAP_PKTSL_PKTSHNL_Pos) | (u32DenominatorL << CCAP_PKTSL_PKTSHML_Pos));
    ccap->PKTSM = (ccap->PKTSM & ~(CCAP_PKTSM_PKTSHNH_Msk | CCAP_PKTSM_PKTSHMH_Msk))
                  | ((u32NumeratorH << CCAP_PKTSL_PKTSHNL_Pos) | (u32DenominatorH << CCAP_PKTSL_PKTSHML_Pos));
}

/**
 * @brief      Set Planar Scaling Factor
 *
 * @param[in]  u32VNumerator:   Planar Scaling Vertical Factor N. It should be 0x0 ~ 0xFFFF.
 * @param[in]  u32VDenominator: Planar Scaling Vertical Factor M. It should be 0x0 ~ 0xFFFF.
 * @param[in]  u32HNumerator:   Planar Scaling Horizontal Factor N. It should be 0x0 ~ 0xFFFF.
 * @param[in]  u32HDenominator: Planar Scaling Horizontal Factor M. It should be 0x0 ~ 0xFFFF.
 *
 * @return     None
 *
 * @details    This function is used to set Planar Scaling Vertical and Horizontal Factor register.
 */
void CCAP_SetPlanarScaling(CCAP_T *ccap, uint32_t u32VNumerator, uint32_t u32VDenominator, uint32_t u32HNumerator, uint32_t u32HDenominator)
{
    uint32_t u32NumeratorL, u32NumeratorH;
    uint32_t u32DenominatorL, u32DenominatorH;

    u32NumeratorL = u32VNumerator & 0xFF;
    u32NumeratorH = u32VNumerator >> 8;
    u32DenominatorL = u32VDenominator & 0xFF;
    u32DenominatorH = u32VDenominator >> 8;
    ccap->PLNSL = (ccap->PLNSL & ~(CCAP_PLNSL_PLNSVNL_Msk | CCAP_PLNSL_PLNSVML_Msk))
                  | ((u32NumeratorL << CCAP_PLNSL_PLNSVNL_Pos) | (u32DenominatorL << CCAP_PLNSL_PLNSVML_Pos));
    ccap->PLNSM = (ccap->PLNSM & ~(CCAP_PLNSM_PLNSVNH_Msk | CCAP_PLNSM_PLNSVMH_Msk))
                  | ((u32NumeratorH << CCAP_PLNSL_PLNSVNL_Pos) | (u32DenominatorH << CCAP_PLNSL_PLNSVML_Pos));

    u32NumeratorL = u32HNumerator & 0xFF;
    u32NumeratorH = u32HNumerator >> 8;
    u32DenominatorL = u32HDenominator & 0xFF;
    u32DenominatorH = u32HDenominator >> 8;
    ccap->PLNSL = (ccap->PLNSL & ~(CCAP_PLNSL_PLNSHNL_Msk | CCAP_PLNSL_PLNSHML_Msk))
                  | ((u32NumeratorL << CCAP_PLNSL_PLNSHNL_Pos) | (u32DenominatorL << CCAP_PLNSL_PLNSHML_Pos));
    ccap->PLNSM = (ccap->PLNSM & ~(CCAP_PLNSM_PLNSHNH_Msk | CCAP_PLNSM_PLNSHMH_Msk))
                  | ((u32NumeratorH << CCAP_PLNSL_PLNSHNL_Pos) | (u32DenominatorH << CCAP_PLNSL_PLNSHML_Pos));
}

/**
 * @brief     Set Packet Frame Output Pixel Stride Width
 *
 * @param[in] u32Stride: Set CCAP_STRIDE register. It should be 0x0 ~ 0x3FFF.
 *
 * @return    None
 *
 * @details   This function is used to set Packet Frame Output Pixel Stride Width.
 */
void CCAP_SetPacketStride(CCAP_T *ccap, uint32_t u32Stride)
{
    ccap->STRIDE = (ccap->STRIDE & ~CCAP_STRIDE_PKTSTRIDE_Msk) | (u32Stride << CCAP_STRIDE_PKTSTRIDE_Pos);
}

/**
 * @brief     Set Planar Frame Output Pixel Stride Width
 *
 * @param[in] u32Stride: Set CCAP_STRIDE register. It should be 0x0 ~ 0x3FFF.
 *
 * @return    None
 *
 * @details   This function is used to set Planar Frame Output Pixel Stride Width.
 */
void CCAP_SetPlanarStride(CCAP_T *ccap, uint32_t u32Stride)
{
    ccap->STRIDE = (ccap->STRIDE & ~CCAP_STRIDE_PLNSTRIDE_Msk) | (u32Stride << CCAP_STRIDE_PLNSTRIDE_Pos);
}


/*@}*/ /* end of group CCAP_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group CCAP_Driver */

/*@}*/ /* end of group Standard_Driver */
