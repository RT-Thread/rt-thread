/**************************************************************************//**
 * @file     cap.c
 * @brief    CAP driver source file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include "nuc980.h"
#include "nu_cap.h"
/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup CAP_Driver CAP Driver
  @{
*/


/** @addtogroup CAP_EXPORTED_FUNCTIONS CAP Exported Functions
  @{
*/

/**
 * @brief      Open engine clock and sensor clock
 *
 * @param[in]   VCAP  The pointer of the specified CAP module
 *
 * @param[in]  u32InFormat  The bits corresponding VSP, HSP, PCLK, INFMT, SNRTYPE, OUTFMT, PDORD and PNFMT configurations.
 *             - VSP should be ether \ref CAP_PAR_VSP_LOW or \ref CAP_PAR_VSP_HIGH
 *             - HSP should be ether \ref CAP_PAR_HSP_LOW or \ref CAP_PAR_HSP_HIGH
 *             - PCLK should be ether \ref CAP_PAR_PCLKP_LOW or \ref CAP_PAR_PCLKP_HIGH
 *             - INFMT should be ether \ref CAP_PAR_INFMT_YUV422 or \ref CAP_PAR_INFMT_RGB565
 *             - SNRTYPE should be ether \ref CAP_PAR_SENTYPE_CCIR601 or \ref CAP_PAR_SENTYPE_CCIR656
 *             - OUTFMT should be one of the following setting
 *                      - \ref CAP_PAR_OUTFMT_YUV422
 *                      - \ref CAP_PAR_OUTFMT_ONLY_Y
 *                      - \ref CAP_PAR_OUTFMT_RGB555
 *                      - \ref CAP_PAR_OUTFMT_RGB565
 *             - PDORD should be one of the following setting
 *                      - \ref CAP_PAR_INDATORD_YUYV
 *                      - \ref CAP_PAR_INDATORD_YVYU
 *                      - \ref CAP_PAR_INDATORD_UYVY
 *                      - \ref CAP_PAR_INDATORD_VYUY
 *                      - \ref CAP_PAR_INDATORD_RGGB
 *                      - \ref CAP_PAR_INDATORD_BGGR
 *                      - \ref CAP_PAR_INDATORD_GBRG
 *                      - \ref CAP_PAR_INDATORD_GRBG
 *             - PNFMT should be one of the following setting
 *                      - \ref CAP_PAR_PLNFMT_YUV422
 *                      - \ref CAP_PAR_PLNFMT_YUV420
 *
 * @param[in]  u32OutFormet Capture output format, should be one of following setting
 *                      - \ref CAP_CTL_PKTEN
 *                      - \ref CAP_CTL_PLNEN
 *
 * @return     None
 *
 * @details    Initialize the Image Capture Interface. Register a call back for driver internal using
 */
void CAP_Open(CAP_T *VCAP, uint32_t u32InFormat, uint32_t u32OutFormet)
{
    VCAP->PAR = (VCAP->PAR & ~0x000007BF) | u32InFormat;
    VCAP->CTL = (VCAP->CTL & ~0x00000060) | u32OutFormet;
}

/**
 * @brief Set Cropping Window Starting Address and Size
 *
 * @param[in]  VCAP: The pointer of the specified CAP module
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
void CAP_SetCroppingWindow(CAP_T *VCAP, uint32_t u32VStart, uint32_t u32HStart, uint32_t u32Height, uint32_t u32Width)
{
    VCAP->CWSP = (VCAP->CWSP & ~(CAP_CWSP_CWSADDRV_Msk | CAP_CWSP_CWSADDRH_Msk))
                 | (((u32VStart << 16) | u32HStart));

    VCAP->CWS = (VCAP->CWS & ~(CAP_CWS_CWH_Msk | CAP_CWS_CWW_Msk))
                | ((u32Height << 16) | u32Width);
}


/**
 * @brief     Set System Memory Packet Base Address0 Register
 *
 * @param[in]  VCAP: The pointer of the specified CAP module
 *
 * @param[in]  u32Address : set PKTBA0 register, It should be 0x0 ~ 0xFFFFFFFF
 *
 * @return    None
 *
 * @details   Set System Memory Packet Base Address Register
 */
void CAP_SetPacketBuf(CAP_T *VCAP, uint32_t  u32Address)
{
    VCAP->PKTBA0 = u32Address;
    VCAP->CTL |= CAP_CTL_UPDATE_Msk;
}

/**
 * @brief     Set System Memory Planar Y, U and V Base Address Registers.
 *
 * @param[in]  VCAP: The pointer of the specified CAP module
 *
 * @param[in] u32YAddr : set YBA register, It should be 0x0 ~ 0xFFFFFFFF
 *
 * @param[in] u32UAddr : set UBA register, It should be 0x0 ~ 0xFFFFFFFF
 *
 * @param[in] u32VAddr : set VBA register, It should be 0x0 ~ 0xFFFFFFFF
 *
 * @return    None
 *
 * @details   Set System Memory Planar Y,U and V Base Address Registers
 */
void CAP_SetPlanarBuf(CAP_T *VCAP, uint32_t u32YAddr, uint32_t u32UAddr, uint32_t u32VAddr)
{
    VCAP->YBA = u32YAddr;
    VCAP->UBA = u32UAddr;
    VCAP->VBA = u32VAddr;
    VCAP->CTL |= CAP_CTL_UPDATE_Msk;
}


/**
 * @brief     Close Image Capture Interface
 *
 * @param[in]  VCAP: The pointer of the specified CAP module
 *
 * @return    None
 */
void CAP_Close(CAP_T *VCAP)
{
    VCAP->CTL &= ~CAP_CTL_CAPEN;
}


/**
 * @brief      Set CAP Interrupt
 *
 * @param[in]  VCAP: The pointer of the specified CAP module
 *
 * @param[in]  u32IntMask   Interrupt settings. It could be
 *                           - \ref CAP_INT_VIEN_Msk
 *                           - \ref CAP_INT_MEIEN_Msk
 *                           - \ref CAP_INT_ADDRMIEN_Msk
 *                           - \ref CAP_INT_MDIEN_Msk
 * @return     None
 *
 * @details    Set Video Frame End Interrupt Enable,
 *                  System Memory Error Interrupt Enable,
 *                  Address Match Interrupt Enable,
 *                  Motion Detection Output Finish Interrupt Enable.
 */
void CAP_EnableInt(CAP_T *VCAP, uint32_t u32IntMask)
{
    VCAP->INT = (VCAP->INT & ~(CAP_INT_VIEN_Msk | CAP_INT_MEIEN_Msk | CAP_INT_ADDRMIEN_Msk | CAP_INT_MDIEN_Msk))
                | u32IntMask;
}

/**
 * @brief      Disable CAP Interrupt
 *
 * @param[in]  VCAP: The pointer of the specified CAP module
 *
 * @param[in]  u32IntMask   Interrupt settings. It could be
 *                           - \ref CAP_INT_VINTF_Msk
 *                           - \ref CAP_INT_MEINTF_Msk
 *                           - \ref CAP_INT_ADDRMINTF_Msk
 *                           - \ref CAP_INT_MDINTF_Msk
 * @return     None
 *
 * @details    Disable Video Frame End Interrupt ,
 *                  System Memory Error Interrupt ,
 *                  Address Match Interrupt and
 *                  Motion Detection Output Finish Interrupt .
 */
void CAP_DisableInt(CAP_T *VCAP, uint32_t u32IntMask)
{
    VCAP->INT = (VCAP->INT & ~(u32IntMask)) ;
}

/**
 * @brief     Start Image Capture Interface
 *
 * @param[in]  VCAP: The pointer of the specified CAP module
 *
 * @return    None
 */
void CAP_Start(CAP_T *VCAP)
{
    VCAP->CTL |= CAP_CTL_CAPEN;
}

/**
 * @brief     Stop Image Capture Interface
 *
 * @param[in]  VCAP: The pointer of the specified CAP module
 *
 * @param[in]  u32FrameComplete :
 *             TRUE:  Capture module automatically disable the CAP module after a frame had been captured
 *             FALSE: Stop Capture module now
 * @return    None
 *
 * @details   if u32FrameComplete is set to TRUE then get a new frame and disable CAP module
 */
void CAP_Stop(CAP_T *VCAP, uint32_t u32FrameComplete)
{
    if (u32FrameComplete == FALSE)
        VCAP->CTL &= ~CAP_CTL_CAPEN;
    else
    {
        VCAP->CTL |= CAP_CTL_SHUTTER_Msk;
        while (CAP_IS_STOPPED(VCAP));
    }
}

/**
 * @brief     Set Packet Scaling Vertical and Horizontal Factor Register
 *
 * @param[in]  VCAP: The pointer of the specified CAP module
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
void CAP_SetPacketScaling(CAP_T *VCAP, uint32_t u32VNumerator, uint32_t u32VDenominator, uint32_t u32HNumerator, uint32_t u32HDenominator)
{
    uint32_t u32NumeratorL, u32NumeratorH;
    uint32_t u32DenominatorL, u32DenominatorH;

    u32NumeratorL = u32VNumerator & 0xFF;
    u32NumeratorH = u32VNumerator >> 8;
    u32DenominatorL = u32VDenominator & 0xFF;
    u32DenominatorH = u32VDenominator >> 8;
    VCAP->PKTSL = (VCAP->PKTSL & ~(CAP_PKTSL_PKTSVNL_Msk | CAP_PKTSL_PKTSVML_Msk))
                  | ((u32NumeratorL << 24) | (u32DenominatorL << 16));
    VCAP->PKTSM = (VCAP->PKTSM & ~(CAP_PKTSM_PKTSVNH_Msk | CAP_PKTSM_PKTSVMH_Msk))
                  | ((u32NumeratorH << 24) | (u32DenominatorH << 16));

    u32NumeratorL = u32HNumerator & 0xFF;
    u32NumeratorH = u32HNumerator >> 8;
    u32DenominatorL = u32HDenominator & 0xFF;
    u32DenominatorH = u32HDenominator >> 8;
    VCAP->PKTSL = (VCAP->PKTSL & ~(CAP_PKTSL_PKTSHNL_Msk | CAP_PKTSL_PKTSHML_Msk))
                  | ((u32NumeratorL << 8) | u32DenominatorL);
    VCAP->PKTSM = (VCAP->PKTSM & ~(CAP_PKTSM_PKTSHNH_Msk | CAP_PKTSM_PKTSHMH_Msk))
                  | ((u32NumeratorH << 8) | u32DenominatorH);
}

/**
 * @brief     Set Planar Scaling Vertical and Horizontal Factor Register
 *
 * @param[in]  VCAP: The pointer of the specified CAP module
 *
 * @param[in] u32VNumerator: Planar Scaling Vertical Factor N. It should be 0 ~ FFFF.
 *
 * @param[in] u32VDenominator: Planar Scaling Vertical Factor M. It should be 0 ~ FFFF.
 *
 * @param[in] u32HNumerator: Planar Scaling Vertical Factor N. It should be 0 ~ FFFF.
 *
 * @param[in] u32HDenominator: Planar Scaling Vertical Factor M. It should be 0 ~ FFFF.
 *
 * @return    None
 *
 */
void CAP_SetPlanarScaling(CAP_T *VCAP, uint32_t u32VNumerator, uint32_t u32VDenominator, uint32_t u32HNumerator, uint32_t u32HDenominator)
{
    uint32_t u32NumeratorL, u32NumeratorH;
    uint32_t u32DenominatorL, u32DenominatorH;

    u32NumeratorL = u32VNumerator & 0xFF;
    u32NumeratorH = u32VNumerator >> 8;
    u32DenominatorL = u32VDenominator & 0xFF;
    u32DenominatorH = u32VDenominator >> 8;
    VCAP->PLNSL = (VCAP->PLNSL & ~(CAP_PLNSL_PLNSVNL_Msk | CAP_PLNSL_PLNSVML_Msk))
                  | ((u32NumeratorL << 24) | (u32DenominatorL << 16));
    VCAP->PLNSM = (VCAP->PLNSM & ~(CAP_PLNSM_PLNSVNH_Msk | CAP_PLNSM_PLNSVMH_Msk))
                  | ((u32NumeratorH << 24) | (u32DenominatorH << 16));

    u32NumeratorL = u32HNumerator & 0xFF;
    u32NumeratorH = u32HNumerator >> 8;
    u32DenominatorL = u32HDenominator & 0xFF;
    u32DenominatorH = u32HDenominator >> 8;
    VCAP->PLNSL = (VCAP->PLNSL & ~(CAP_PLNSL_PLNSHNL_Msk | CAP_PLNSL_PLNSHML_Msk))
                  | ((u32NumeratorL << 8) | u32DenominatorL);
    VCAP->PLNSM = (VCAP->PLNSM & ~(CAP_PLNSM_PLNSHNH_Msk | CAP_PLNSM_PLNSHMH_Msk))
                  | ((u32NumeratorH << 8) | u32DenominatorH);
}

/**
 * @brief     Set Packet Frame Output Pixel Stride Width.
 *
 * @param[in]  VCAP: The pointer of the specified CAP module
 *
 * @param[in] u32Stride : set PKTSTRIDE register, It should be 0x0 ~ 0x3FFF
 *
 * @return    None
 *
 * @details   Set Packet Frame Output Pixel Stride Width
 */
void CAP_SetPacketStride(CAP_T *VCAP, uint32_t u32Stride)
{
    VCAP->STRIDE = (VCAP->STRIDE & ~CAP_STRIDE_PKTSTRIDE_Msk) | u32Stride;
}

/**
 * @brief     Set Planar Frame Output Pixel Stride Width.
 *
 * @param[in]  VCAP: The pointer of the specified CAP module
 *
 * @param[in] u32Stride : set PLNSTRIDE register, It should be 0x0 ~ 0x3FFF
 *
 * @return    None
 *
 * @details  Set Planar Frame Output Pixel Stride Width
 */
void CAP_SetPlanarStride(CAP_T *VCAP, uint32_t u32Stride)
{
    VCAP->STRIDE = (VCAP->STRIDE & ~CAP_STRIDE_PLNSTRIDE_Msk) | u32Stride << CAP_STRIDE_PLNSTRIDE_Pos;
}


/**
 * @brief     Enable Motion Detection Function
 *
 * @param[in]  VCAP: The pointer of the specified CAP module
 *
 * @param[in] u32Freq: Motion Detection Detect Frequency. It should be 0x0 ~ 0x3.
 *
 * @param[in] u32BlockSize: Motion Detection Block Size
 *                        FALSE : 16x16
 *                        TRUE  : 8x8
 *
 * @param[in] u32Format: Motion Detection Save Mode
 *                        FALSE : 1 bit DIFF + 7 Y Differential
 *                        TRUE :  1 bit DIFF only
 *
 * @param[in] u32Threshold: Motion Detection Detect Threshold. It should be 0x0 ~ 0x1F.
 *
 * @param[in] u32YDetAddr : Motion Detection Detect Temp Y Output Address
 *
 * @param[in] u32DetAddr: Motion Detection Detect Address
 *
 * @return    None
 *
 * @details  Set Planar Frame Output Pixel Stride Width
 */
void CAP_EnableMotionDet(CAP_T *VCAP, uint32_t u32Freq, uint32_t u32BlockSize, uint32_t u32Format, uint32_t u32Threshold,  uint32_t u32YDetAddr, uint32_t u32DetAddr)
{
    VCAP->MD = (VCAP->MD & ~(CAP_MD_MDSM_Msk | CAP_MD_MDBS_Msk | CAP_MD_MDEN_Msk)) |
               ((CAP_MD_MDEN_Msk | (u32BlockSize ? CAP_MD_MDBS_Msk : 0)) |
                (u32Format ? CAP_MD_MDSM_Msk : 0));

    VCAP->MD = (VCAP->MD & ~CAP_MD_MDDF_Msk) | (u32Freq << CAP_MD_MDDF_Pos);
    VCAP->MD = (VCAP->MD & ~CAP_MD_MDTHR_Msk) | (u32Threshold << CAP_MD_MDTHR_Pos);

    VCAP->MDYADDR = u32YDetAddr;
    VCAP->MDADDR = u32DetAddr;
}

/**
 * @brief     Enable Motion Detection Function
 *
 * @param[in]  VCAP: The pointer of the specified CAP module
 *
 * @return    None
 *
 * @details  Set Planar Frame Output Pixel Stride Width
 */
void CAP_DisableMotionDet(CAP_T *VCAP)
{
    VCAP->MD &= ~CAP_MD_MDEN_Msk;
}

/*@}*/ /* end of group CAP_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group CAP_Driver */

/*@}*/ /* end of group Standard_Driver */
