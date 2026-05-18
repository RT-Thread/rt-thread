/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file n32h76x_78x_lcdc.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */

#include "n32h76x_78x_lcdc.h"
#include "n32h76x_78x_rcc.h"

/**
*\*\name    LCDC_DeInit
*\*\fun     Deinitializes the LCDC registers.
*\*\param   none
*\*\return  none
**/
void LCDC_DeInit(void)
{
    RCC_EnableAXIPeriphReset2(RCC_AXI_PERIPHRST_LCDC);
}

/**
*\*\name    LCDC_Init
*\*\fun     Initializes the LCDC.
*\*\param   LCDC_InitStruct: refer to the definition of LCDC_InitType
*\*\          - LCDC_HSPolarity
*\*\            * LCDC_HSPolarity_LOW
*\*\            * LCDC_HSPolarity_HIGH
*\*\          - LCDC_VSPolarity
*\*\            * LCDC_VSPolarity_LOW
*\*\            * LCDC_VSPolarity_HIGH
*\*\          - LCDC_DEPolarity
*\*\            * LCDC_DEPolarity_LOW
*\*\            * LCDC_DEPolarity_HIGH
*\*\          - LCDC_PCPolarity
*\*\            * LCDC_PCPolarity_IPC
*\*\            * LCDC_PCPolarity_IIPC
*\*\          - LCDC_HorizontalSync
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - LCDC_VerticalSync
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - LCDC_AccumulatedHBP
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - LCDC_AccumulatedVBP
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - LCDC_AccumulatedActiveW
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - LCDC_AccumulatedActiveH
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - LCDC_TotalWidth
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - LCDC_TotalHeight
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - LCDC_BackgroundRedValue
*\*\            * 0x00 ~ 0xFF
*\*\          - LCDC_BackgroundGreenValue
*\*\            * 0x00 ~ 0xFF
*\*\          - LCDC_BackgroundBlueValue
*\*\            * 0x00 ~ 0xFF
*\*\return  none
**/
void LCDC_Init(LCDC_InitType* LCDC_InitStruct)
{
    uint32_t tmpgctrl;
    uint32_t tmpbgcctrl;

    /* Configure the HS, VS, DE and PC polarity */
    /* Get the LCDC_GCTRL register value */
    tmpgctrl = LCDC->GCTRL;
    /* Clear PCLKPOL/DEPOL/VSPOL/HSPOL bits */
    tmpgctrl &= ~(LCDC_GCTRL_HSPOL | LCDC_GCTRL_VSPOL | LCDC_GCTRL_DEPOL | LCDC_GCTRL_PCLKPOL);
    /* Set PCLKPOL/DEPOL/VSPOL/HSPOL bits */
    tmpgctrl |= (uint32_t)(LCDC_InitStruct->LCDC_HSPolarity | LCDC_InitStruct->LCDC_VSPolarity | LCDC_InitStruct->LCDC_DEPolarity | LCDC_InitStruct->LCDC_PCPolarity);
    /* Write to LCDC_GCTRL */
    LCDC->GCTRL = (uint32_t)tmpgctrl;

    /* Set Synchronization size */
    LCDC->SYNCCTRL = (uint32_t)((LCDC_InitStruct->LCDC_HorizontalSync << 16) | LCDC_InitStruct->LCDC_VerticalSync);

    /* Set Accumulated Back porch */
    LCDC->BPCTRL = (uint32_t)((LCDC_InitStruct->LCDC_AccumulatedHBP << 16) | LCDC_InitStruct->LCDC_AccumulatedVBP);

    /* Set Accumulated Active Width */
    LCDC->AWCTRL = (uint32_t)((LCDC_InitStruct->LCDC_AccumulatedActiveW << 16) | LCDC_InitStruct->LCDC_AccumulatedActiveH);

    /* Set Total Width */
    LCDC->TWCTRL = (uint32_t)((LCDC_InitStruct->LCDC_TotalWidth << 16) | LCDC_InitStruct->LCDC_TotalHeight);

    /* Configure the background color value */
    /* Get the LCDC_BGCCTRL register value */
    tmpbgcctrl = LCDC->BGCCTRL;
    /* Clear BCR/BCG/BCB bits */
    tmpbgcctrl &= ~(LCDC_BGCCTRL_BCR | LCDC_BGCCTRL_BCG | LCDC_BGCCTRL_BCB);
    /* Set BCR/BCG/BCB bits */
    tmpbgcctrl |= (uint32_t)((LCDC_InitStruct->LCDC_BackgroundRedValue << 16) | (LCDC_InitStruct->LCDC_BackgroundGreenValue << 8) | LCDC_InitStruct->LCDC_BackgroundBlueValue);
    /* Write to LCDC_BGCCTRL */
    LCDC->BGCCTRL = (uint32_t)tmpbgcctrl;
}

/**
*\*\name    LCDC_StructInit
*\*\fun     Fills each LCDC_InitStruct member with its default value.
*\*\param   LCDC_InitStruct: refer to the definition of LCDC_InitType
*\*\          - LCDC_HSPolarity
*\*\            * LCDC_HSPolarity_LOW
*\*\            * LCDC_HSPolarity_HIGH
*\*\          - LCDC_VSPolarity
*\*\            * LCDC_VSPolarity_LOW
*\*\            * LCDC_VSPolarity_HIGH
*\*\          - LCDC_DEPolarity
*\*\            * LCDC_DEPolarity_LOW
*\*\            * LCDC_DEPolarity_HIGH
*\*\          - LCDC_PCPolarity
*\*\            * LCDC_PCPolarity_LOW
*\*\            * LCDC_PCPolarity_HIGH
*\*\          - LCDC_HorizontalSync
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - LCDC_VerticalSync
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - LCDC_AccumulatedHBP
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - LCDC_AccumulatedVBP
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - LCDC_AccumulatedActiveW
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - LCDC_AccumulatedActiveH
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - LCDC_TotalWidth
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - LCDC_TotalHeight
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - LCDC_BackgroundRedValue
*\*\            * 0x00 ~ 0xFF
*\*\          - LCDC_BackgroundGreenValue
*\*\            * 0x00 ~ 0xFF
*\*\          - LCDC_BackgroundBlueValue
*\*\            * 0x00 ~ 0xFF
*\*\return  none
**/
void LCDC_StructInit(LCDC_InitType* LCDC_InitStruct)
{
    /* Set the default configuration */
    LCDC_InitStruct->LCDC_HSPolarity            = LCDC_HSPolarity_LOW;
    LCDC_InitStruct->LCDC_VSPolarity            = LCDC_VSPolarity_LOW;
    LCDC_InitStruct->LCDC_DEPolarity            = LCDC_DEPolarity_LOW;
    LCDC_InitStruct->LCDC_PCPolarity            = LCDC_PCPolarity_IPC;
    LCDC_InitStruct->LCDC_HorizontalSync        = 0x00;
    LCDC_InitStruct->LCDC_VerticalSync          = 0x00;
    LCDC_InitStruct->LCDC_AccumulatedHBP        = 0x00;
    LCDC_InitStruct->LCDC_AccumulatedVBP        = 0x00;
    LCDC_InitStruct->LCDC_AccumulatedActiveW    = 0x00;
    LCDC_InitStruct->LCDC_AccumulatedActiveH    = 0x00;
    LCDC_InitStruct->LCDC_TotalWidth            = 0x00;
    LCDC_InitStruct->LCDC_TotalHeight           = 0x00;
    LCDC_InitStruct->LCDC_BackgroundRedValue    = 0x00;
    LCDC_InitStruct->LCDC_BackgroundGreenValue  = 0x00;
    LCDC_InitStruct->LCDC_BackgroundBlueValue   = 0x00;
}

/**
*\*\name    LCDC_Enable
*\*\fun     Enables or disables the specified LCDC peripheral.
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void LCDC_Enable(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the LCDC */
        LCDC->GCTRL |= (uint32_t)LCDC_GCTRL_EN;
    }
    else
    {
        /* Disable the LCDC */
        LCDC->GCTRL &= (uint32_t)(~LCDC_GCTRL_EN);
    }
}

/**
*\*\name    LCDC_DitherEnable
*\*\fun     Enables or disables the dither.
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void LCDC_DitherEnable(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the dither */
        LCDC->GCTRL |= (uint32_t)LCDC_GCTRL_DEN;
    }
    else
    {
        /* Disable the dither */
        LCDC->GCTRL &= (uint32_t)(~LCDC_GCTRL_DEN);
    }

}

/**
*\*\name    LCDC_GetDitherWidth
*\*\fun     Get the dither RGB width.
*\*\param   none
*\*\return  LCDC_RGBType:
*\*\          - LCDC_Blue      Dither blue width
*\*\          - LCDC_Green     Dither green width
*\*\          - LCDC_Red       Dither red width
**/
LCDC_RGBType LCDC_GetDitherWidth(void)
{
    LCDC_RGBType LCDC_RGB_DitherStruct;

    LCDC->GCTRL &= ~(LCDC_GCTRL_DBW | LCDC_GCTRL_DGW | LCDC_GCTRL_DRW);

    LCDC_RGB_DitherStruct.LCDC_Blue = (uint32_t)((LCDC->GCTRL >> 4) & 0x7);
    LCDC_RGB_DitherStruct.LCDC_Green = (uint32_t)((LCDC->GCTRL >> 8) & 0x7);
    LCDC_RGB_DitherStruct.LCDC_Red = (uint32_t)((LCDC->GCTRL >> 12) & 0x7);

    return LCDC_RGB_DitherStruct;
}

/**
*\*\name    LCDC_DitherStructInit
*\*\fun     Fills each LCDC_RGB_DitherStruct member with its default value.
*\*\param   LCDC_RGB_DitherStruct
*\*\          - LCDC_Blue      Dither blue width
*\*\          - LCDC_Green     Dither green width
*\*\          - LCDC_Red       Dither red width
*\*\return  none
**/
void LCDC_DitherStructInit(LCDC_RGBType* LCDC_RGB_DitherStruct)
{
    LCDC_RGB_DitherStruct->LCDC_Blue  = 0x02;
    LCDC_RGB_DitherStruct->LCDC_Green = 0x02;
    LCDC_RGB_DitherStruct->LCDC_Red   = 0x02;
}

/**
*\*\name    LCDC_LINTPConfig
*\*\fun     Define the position of the line interrupt.
*\*\param   LCDC_LINTPosition
*\*\          - 0x0000 ~ 0xFFFF
*\*\return  none
**/
void LCDC_LINTPConfig(uint32_t LCDC_LINTPosition)
{
    /* Sets the Line Interrupt position */
    LCDC->LINTPCTRL = LCDC_LINTPosition;
}

/**
*\*\name    LCDC_ReloadConfig
*\*\fun     Reload registers with new parameters.
*\*\param   LCDC_Reload
*\*\          - LCDC_IMReload
*\*\          - LCDC_VBReload
*\*\return  none
**/
void LCDC_ReloadConfig(uint32_t LCDC_Reload)
{
    /* Sets the Reload type */
    LCDC->SRCTRL = (uint32_t)LCDC_Reload;
}

/**
*\*\name    LCDC_LayerReloadConfig
*\*\fun     Reload layers registers with new parameters.
*\*\param   LCDC_Reload
*\*\          - LCDC_LayerIMReload
*\*\          - LCDC_LayerVBReload
*\*\          - LCDC_LayerMGReload
*\*\return  none
**/
void LCDC_LayerReloadConfig(LCDC_Layer_Module* LCDC_Layerx, uint32_t LCDC_LayerReload)
{
    /* Sets the reload type */
    LCDC_Layerx->LSRCTRL = (uint32_t)LCDC_LayerReload;
}

/**
*\*\name    LCDC_LayerInit
*\*\fun     Initializes the LCDC Layer according to the specified parameters in the LCDC_Layer_InitStruct.
*\*\param   LCDC_Layerx: refer to the definition of LCDC_Layer_Module
*\*\          - LCDC_Layer1
*\*\          - LCDC_Layer2
*\*\          - LCDC_Layer3
*\*\          - LCDC_Layer4
*\*\param   LCDC_Layer_InitStruct: refer to the definition of LCDC_Layer_InitType
*\*\          - LCDC_HorizontalStart
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - LCDC_HorizontalStop
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - LCDC_HorizontalScalerStop

*\*\          - LCDC_VerticalStart
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - LCDC_VerticalStop
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - LCDC_VerticalScalerStop

*\*\          - LCDC_PixelFormat
*\*\            * LCDC_Pixel_Format_ARGB8888
*\*\            * LCDC_Pixel_Format_ABGR8888
*\*\            * LCDC_Pixel_Format_RGBA8888
*\*\            * LCDC_Pixel_Format_BGRA8888
*\*\            * LCDC_Pixel_Format_RGB565
*\*\            * LCDC_Pixel_Format_BGR565
*\*\            * LCDC_Pixel_Format_RGB888
*\*\            * LCDC_Pixel_Format_Custom
*\*\          - LCDC_ConstantAlpha
*\*\            * 0x00 ~ 0xFF
*\*\          - LCDC_DefaultAlpha
*\*\            * 0x00 ~ 0xFF
*\*\          - LCDC_BlendingFactor1
*\*\            * LCDC_BlendingFactor1_CA
*\*\            * LCDC_BlendingFactor1_PAxCA
*\*\          - LCDC_BlendingFactor2
*\*\            * LCDC_BlendingFactor2_CA
*\*\            * LCDC_BlendingFactor2_PAxCA
*\*\          - LCDC_CFBStartAdress
*\*\            * 0x00000000 ~ 0xFFFFFFFF
*\*\          - LCDC_AFB0StartAdress

*\*\          - LCDC_AFB1StartAdress

*\*\          - LCDC_CFBLineLength
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - LCDC_CFBPitch
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - LCDC_CFBLineNumber
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - LCDC_DefaultColorBlue
*\*\            * 0x00 ~ 0xFF
*\*\          - LCDC_DefaultColorGreen
*\*\            * 0x00 ~ 0xFF
*\*\          - LCDC_DefaultColorRed
*\*\            * 0x00 ~ 0xFF
*\*\return  none
**/
void LCDC_LayerInit(LCDC_Layer_Module* LCDC_Layerx, LCDC_Layer_InitType* LCDC_Layer_InitStruct)
{
    uint32_t tmpwhpctrl;
    uint32_t tmpwvpctrl;
    uint32_t tmppfctrl;
    uint32_t tmpdcctrl;
    uint32_t tmpcactrl;
    uint32_t tmpbfctrl;
    uint32_t tmpcfbaddr;
    uint32_t tmpcfblen;
    uint32_t tmpcfblnum;
    /* Configures the horizontal start and stop position */
    /* Get the LCDC_WHPCTRL register value */
    tmpwhpctrl = LCDC_Layerx->WHPCTRL;
    /* Clear WHSTPOS/WHSPPOS bits */
    tmpwhpctrl &= ~(LCDC_WHPCTRL_WHSTPOS | LCDC_WHPCTRL_WHSPPOS);
    /* Set WHSTPOS/WHSPPOS bits */
    tmpwhpctrl |= (uint32_t)((LCDC_Layer_InitStruct->LCDC_HorizontalStop << 16) | (LCDC_Layer_InitStruct->LCDC_HorizontalStart));
    /* Write to LCDC_WHPCTRL */
    LCDC_Layerx->WHPCTRL = (uint32_t)tmpwhpctrl;

    /* Configures the vertical start and stop position */
    /* Get the LCDC_WVPCTRL register value */
    tmpwvpctrl = LCDC_Layerx->WVPCTRL;
    /* Clear WVSTPOS/WVSPPOS bits */
    tmpwvpctrl &= ~(LCDC_WVPCTRL_WVSTPOS | LCDC_WVPCTRL_WVSPPOS);
    /* Set WVSTPOS/WVSPPOS bits */
    tmpwvpctrl |= (uint32_t)((LCDC_Layer_InitStruct->LCDC_VerticalStop << 16) | (LCDC_Layer_InitStruct->LCDC_VerticalStart));
    /* Write to LCDC_WVPCTRL */
    LCDC_Layerx->WVPCTRL = (uint32_t)tmpwvpctrl;

    /* Specifies the pixel format */
    /* Get the LCDC_PFCTRL register value */
    tmppfctrl = LCDC_Layerx->PFCTRL;
    /* Clear PF bits */
    tmppfctrl &= ~LCDC_PFCTRL_PF;
    /* Set PF bits */
    tmppfctrl |= (uint32_t)(LCDC_Layer_InitStruct->LCDC_PixelFormat);
    /* Write to LCDC_PFCTRL */
    LCDC_Layerx->PFCTRL = (uint32_t)tmppfctrl;
    
    /* Configures the default color values */    
    /* Get the LCDC_DCCTRL register value */
    tmpdcctrl = LCDC_Layerx->DCCTRL;
    /* Clear DCA/DCR/DCG/DCB bits */
    tmpdcctrl &= ~(LCDC_DCCTRL_DCA | LCDC_DCCTRL_DCR | LCDC_DCCTRL_DCG | LCDC_DCCTRL_DCB);
    /* Set DCA/DCR/DCG/DCB bits */
    tmpdcctrl |= (uint32_t)((LCDC_Layer_InitStruct->LCDC_DefaultAlpha << 24) | (LCDC_Layer_InitStruct->LCDC_DefaultColorRed << 16) | \
                            (LCDC_Layer_InitStruct->LCDC_DefaultColorGreen << 8) | (LCDC_Layer_InitStruct->LCDC_DefaultColorBlue));
    /* Write to LCDC_DCCTRL */
    LCDC_Layerx->DCCTRL = (uint32_t)tmpdcctrl;

    /* Specifies the constant alpha value */
    /* Get the LCDC_CACTRL register value */
    tmpcactrl = LCDC_Layerx->CACTRL;
    /* Clear CA bits */
    tmpcactrl &= ~LCDC_CACTRL_CA;
    /* Set CA bits */
    tmpcactrl |= (uint32_t)(LCDC_Layer_InitStruct->LCDC_ConstantAlpha);
    /* Write to LCDC_CACTRL */
    LCDC_Layerx->CACTRL = (uint32_t)tmpcactrl;

    /* Specifies the blending factors */
    /* Get the LCDC_BFCTRL register value */
    tmpbfctrl = LCDC_Layerx->BFCTRL;
    /* Clear BF1/BF2 bits */
    tmpbfctrl &= ~(LCDC_BFCTRL_BF1 | LCDC_BFCTRL_BF2);
    /* Set BF1/BF2 bits */
    tmpbfctrl |= (uint32_t)((LCDC_Layer_InitStruct->LCDC_BlendingFactor1) | (LCDC_Layer_InitStruct->LCDC_BlendingFactor2));
    /* Write to LCDC_BFCTRL */
    LCDC_Layerx->BFCTRL = (uint32_t)tmpbfctrl;

    /* Configures the color frame buffer start address */
    /* Get the LCDC_CFBADDR register value */
    tmpcfbaddr = LCDC_Layerx->CFBADDR;
    /* Clear CFBADDR bits */
    tmpcfbaddr &= ~(LCDC_CFBADDR_CFBADDR);
    /* Set CFBADDR bits */
    tmpcfbaddr |= (uint32_t)(LCDC_Layer_InitStruct->LCDC_CFBStartAdress);
    /* Write to LCDC_CFBADDR */
    LCDC_Layerx->CFBADDR = (uint32_t)tmpcfbaddr;

    /* Configures the color frame buffer pitch in byte */
    /* Get the LCDC_CFBLEN register value */
    tmpcfblen = LCDC_Layerx->CFBLEN;
    /* Clear CFBLLEN/CFBP bits */
    tmpcfblen &= ~(LCDC_CFBLEN_CFBLLEN | LCDC_CFBLEN_CFBP);
    /* Set CFBLLEN/CFBP bits */
    tmpcfblen |= (uint32_t)((LCDC_Layer_InitStruct->LCDC_CFBPitch << 16) | (LCDC_Layer_InitStruct->LCDC_CFBLineLength));
    /* Write to LCDC_CFBLEN */
    LCDC_Layerx->CFBLEN = (uint32_t)tmpcfblen;

    /* Configures the frame buffer line number */
    /* Get the LCDC_CFBLNUM register value */
    tmpcfblnum = LCDC_Layerx->CFBLNUM;
    /* Clear CFBLNUM bits */
    tmpcfblnum &= ~(LCDC_CFBLNUM_CFBLNUM);
    /* Set CFBLNUM bits */
    tmpcfblnum |= (uint32_t)(LCDC_Layer_InitStruct->LCDC_CFBLineNumber);
    /* Write to LCDC_CFBLNUM */
    LCDC_Layerx->CFBLNUM = (uint32_t)tmpcfblnum;

}

/**
*\*\name    LCDC_LayerStructInit
*\*\fun     Fills each LCDC_Layer_InitStruct member with its default value.
*\*\param   LCDC_Layer_InitStruct: refer to the definition of LCDC_Layer_InitType
*\*\          - LCDC_HorizontalStart
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - LCDC_HorizontalStop
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - LCDC_HorizontalScalerStop

*\*\          - LCDC_VerticalStart
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - LCDC_VerticalStop
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - LCDC_VerticalScalerStop

*\*\          - LCDC_PixelFormat
*\*\            * LCDC_Pixel_Format_ARGB8888
*\*\            * LCDC_Pixel_Format_ABGR8888
*\*\            * LCDC_Pixel_Format_RGBA8888
*\*\            * LCDC_Pixel_Format_BGRA8888
*\*\            * LCDC_Pixel_Format_RGB565
*\*\            * LCDC_Pixel_Format_BGR565
*\*\            * LCDC_Pixel_Format_RGB888
*\*\            * LCDC_Pixel_Format_Custom
*\*\          - LCDC_ConstantAlpha
*\*\            * 0x00 ~ 0xFF
*\*\          - LCDC_DefaultAlpha
*\*\            * 0x00 ~ 0xFF
*\*\          - LCDC_BlendingFactor1
*\*\            * LCDC_BlendingFactor1_CA
*\*\            * LCDC_BlendingFactor1_PAxCA
*\*\          - LCDC_BlendingFactor2
*\*\            * LCDC_BlendingFactor2_CA
*\*\            * LCDC_BlendingFactor2_PAxCA
*\*\          - LCDC_CFBStartAdress
*\*\            * 0x00000000 ~ 0xFFFFFFFF
*\*\          - LCDC_AFB0StartAdress

*\*\          - LCDC_AFB1StartAdress

*\*\          - LCDC_CFBLineLength
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - LCDC_CFBPitch
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - LCDC_CFBLineNumber
*\*\            * 0x0000 ~ 0xFFFF
*\*\          - LCDC_DefaultColorBlue
*\*\            * 0x00 ~ 0xFF
*\*\          - LCDC_DefaultColorGreen
*\*\            * 0x00 ~ 0xFF
*\*\          - LCDC_DefaultColorRed
*\*\            * 0x00 ~ 0xFF
*\*\return  none
**/
void LCDC_LayerStructInit(LCDC_Layer_InitType* LCDC_Layer_InitStruct)
{
    /* Set the default configuration */
    LCDC_Layer_InitStruct->LCDC_HorizontalStart      = 0x00;
    LCDC_Layer_InitStruct->LCDC_HorizontalStop       = 0x00;
    LCDC_Layer_InitStruct->LCDC_HorizontalScalerStop = 0x00;
    LCDC_Layer_InitStruct->LCDC_VerticalStart        = 0x00;
    LCDC_Layer_InitStruct->LCDC_VerticalStop         = 0x00;
    LCDC_Layer_InitStruct->LCDC_VerticalScalerStop   = 0x00;
    LCDC_Layer_InitStruct->LCDC_PixelFormat          = LCDC_Pixel_Format_ARGB8888;
    LCDC_Layer_InitStruct->LCDC_ConstantAlpha        = 0xFF;
    LCDC_Layer_InitStruct->LCDC_DefaultAlpha         = 0x00;
    LCDC_Layer_InitStruct->LCDC_BlendingFactor1      = LCDC_BlendingFactor1_PAxCA;
    LCDC_Layer_InitStruct->LCDC_BlendingFactor2      = LCDC_BlendingFactor2_PAxCA;
    LCDC_Layer_InitStruct->LCDC_CFBStartAdress       = 0x00;
    LCDC_Layer_InitStruct->LCDC_AFB0StartAdress      = 0x00;
    LCDC_Layer_InitStruct->LCDC_AFB1StartAdress      = 0x00;
    LCDC_Layer_InitStruct->LCDC_CFBLineLength        = 0x00;
    LCDC_Layer_InitStruct->LCDC_CFBLineNumber        = 0x00;
    LCDC_Layer_InitStruct->LCDC_CFBPitch             = 0x00;
    LCDC_Layer_InitStruct->LCDC_DefaultColorBlue     = 0x00;
    LCDC_Layer_InitStruct->LCDC_DefaultColorGreen    = 0x00;
    LCDC_Layer_InitStruct->LCDC_DefaultColorRed      = 0x00;
}

void LCDC_LayerEnable(LCDC_Layer_Module* LCDC_Layerx , FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the LCDC layer */
        LCDC_Layerx->LCTRL |= (uint32_t)LCDC_LCTRL_LEN;
    }
    else
    {
        /* Disable the LCDC layer */
        LCDC_Layerx->LCTRL &= (uint32_t)(~LCDC_LCTRL_LEN);
    }
}

LCDC_PosType LCDC_GetPosStatus(void)
{
    LCDC_PosType LCDC_Pos_InitStruct;

    LCDC->CPSTS &= ~(LCDC_CPSTS_CYPOS | LCDC_CPSTS_CXPOS);

    LCDC_Pos_InitStruct.LCDC_POSX = (uint32_t)(LCDC->CPSTS >> 16);
    LCDC_Pos_InitStruct.LCDC_POSY = (uint32_t)(LCDC->CPSTS & 0xFFFF);

    return LCDC_Pos_InitStruct;
}

void LCDC_PosStructInit(LCDC_PosType* LCDC_Pos_InitStruct)
{
    LCDC_Pos_InitStruct->LCDC_POSX = 0x00;
    LCDC_Pos_InitStruct->LCDC_POSY = 0x00;
}

FlagStatus LCDC_GetCDStatus(uint32_t LCDC_CD)
{
    FlagStatus bitstatus;

    if ((LCDC->CDSTS & LCDC_CD) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
*\*\name    LCDC_ColorKeyingConfig
*\*\fun     Set and configure the color keying.
*\*\param   LCDC_Layerx: refer to the definition of LCDC_Layer_Module
*\*\          - LCDC_Layer1
*\*\          - LCDC_Layer2
*\*\          - LCDC_Layer3
*\*\          - LCDC_Layer4
*\*\param   LCDC_ColorKeying_InitStruct: refer to the definition of LCDC_ColorKeying_InitType
*\*\          - LCDC_ColorKeyBlue
*\*\            * 0x00 ~ 0xFF
*\*\          - LCDC_ColorKeyGreen
*\*\            * 0x00 ~ 0xFF
*\*\          - LCDC_ColorKeyRed
*\*\            * 0x00 ~ 0xFF
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void LCDC_ColorKeyingConfig(LCDC_Layer_Module* LCDC_Layerx, LCDC_ColorKeying_InitType* LCDC_ColorKeying_InitStruct, FunctionalState Cmd)
{
    uint32_t tmpckctrl;

    if (Cmd != DISABLE)
    {
        /* Enable LCDC color keying by setting COLKEN bit */
        LCDC_Layerx->LCTRL |= (uint32_t)LCDC_LCTRL_CKEN;

        /* Sets the color keying values */
        tmpckctrl = LCDC_Layerx ->CKCTRL;
        tmpckctrl &= (LCDC_CKCTRL_CKR | LCDC_CKCTRL_CKG | LCDC_CKCTRL_CKB);
        tmpckctrl |= ((LCDC_ColorKeying_InitStruct->LCDC_ColorKeyRed << 16) | (LCDC_ColorKeying_InitStruct->LCDC_ColorKeyGreen << 8) | (LCDC_ColorKeying_InitStruct->LCDC_ColorKeyBlue));
        LCDC_Layerx->LCTRL = (uint32_t)tmpckctrl;
    }
    else
    {
        /* Disable LCDC color keying by clearing COLKEN bit */
        LCDC_Layerx->LCTRL &= (uint32_t)(~LCDC_LCTRL_CKEN);
    }

    /* Reload shadow register */
    LCDC->SRCTRL = (uint32_t)LCDC_IMReload;
}

/**
*\*\name    LCDC_ColorKeyingStructInit
*\*\fun     Fills each LCDC_ColorKeying_InitStruct member with its default value.
*\*\param   LCDC_ColorKeying_InitStruct: refer to the definition of LCDC_ColorKeying_InitType
*\*\          - LCDC_ColorKeyBlue
*\*\            * 0x00 ~ 0xFF
*\*\          - LCDC_ColorKeyGreen
*\*\            * 0x00 ~ 0xFF
*\*\          - LCDC_ColorKeyRed
*\*\            * 0x00 ~ 0xFF
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void LCDC_ColorKeyingStructInit(LCDC_ColorKeying_InitType* LCDC_ColorKeying_InitStruct)
{
    /* Initialize the color keying values */
    LCDC_ColorKeying_InitStruct->LCDC_ColorKeyBlue = 0x00;
    LCDC_ColorKeying_InitStruct->LCDC_ColorKeyGreen = 0x00;
    LCDC_ColorKeying_InitStruct->LCDC_ColorKeyRed = 0x00;
}

/**
*\*\name    LCDC_CLUTEnable
*\*\fun     Enables or disables CLUT.
*\*\param   LCDC_Layerx: refer to the definition of LCDC_Layer_Module
*\*\          - LCDC_Layer1
*\*\          - LCDC_Layer2
*\*\          - LCDC_Layer3
*\*\          - LCDC_Layer4
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void LCDC_CLUTEnable(LCDC_Layer_Module* LCDC_Layerx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable CLUT by setting CLUTEN bit  */
        LCDC_Layerx->LCTRL |= (uint32_t)LCDC_LCTRL_CLUTEN;
    }
    else
    {
        /* Disable CLUT by clearing CLUTEN bit */
        LCDC_Layerx->LCTRL &= (uint32_t)(~LCDC_LCTRL_CLUTEN);
    }

    /* Reload shadow register */
    LCDC->SRCTRL = (uint32_t)LCDC_IMReload;
}

/**
*\*\name    LCDC_CLUTInit
*\*\fun     Configure the CLUT.
*\*\param   LCDC_Layerx: refer to the definition of LCDC_Layer_Module
*\*\          - LCDC_Layer1
*\*\          - LCDC_Layer2
*\*\          - LCDC_Layer3
*\*\          - LCDC_Layer4
*\*\param   LCDC_CLUT_InitStruct: refer to the definition of LCDC_CLUT_InitType
*\*\          - LCDC_CLUTAdress
*\*\            * 0x00 ~ 0xFF
*\*\          - LCDC_RedValue
*\*\            * 0x00 ~ 0xFF
*\*\          - LCDC_GreenValue
*\*\            * 0x00 ~ 0xFF
*\*\          - LCDC_BlueValue
*\*\            * 0x00 ~ 0xFF
*\*\return  none
**/
void LCDC_CLUTInit(LCDC_Layer_Module* LCDC_Layerx, LCDC_CLUT_InitType* LCDC_CLUT_InitStruct)
{
    uint32_t tmpclutwr;

    /* Set the CLUT address and RGB value */
    tmpclutwr = LCDC_Layerx ->CLUTWR;
    tmpclutwr &= (LCDC_CLUTWR_CLUTADDR | LCDC_CLUTWR_CLUTR | LCDC_CLUTWR_CLUTG | LCDC_CLUTWR_CLUTB);
    tmpclutwr |= ((LCDC_CLUT_InitStruct->LCDC_CLUTAdress << 24) | (LCDC_CLUT_InitStruct->LCDC_RedValue << 16) | \
                  (LCDC_CLUT_InitStruct->LCDC_GreenValue << 8) | (LCDC_CLUT_InitStruct->LCDC_BlueValue));

    LCDC_Layerx->CLUTWR = (uint32_t)tmpclutwr;
}

/**
*\*\name    LCDC_CLUTStructInit
*\*\fun     Fills each LCDC_CLUT_InitStruct member with its default value.
*\*\param   LCDC_CLUT_InitStruct: refer to the definition of LCDC_CLUT_InitType
*\*\          - LCDC_CLUTAdress
*\*\            * 0x00 ~ 0xFF
*\*\          - LCDC_RedValue
*\*\            * 0x00 ~ 0xFF
*\*\          - LCDC_GreenValue
*\*\            * 0x00 ~ 0xFF
*\*\          - LCDC_BlueValue
*\*\            * 0x00 ~ 0xFF
*\*\return  none
**/
void LCDC_CLUTStructInit(LCDC_CLUT_InitType* LCDC_CLUT_InitStruct)
{
    /* Initialize the CLUT address and RGB values */
    LCDC_CLUT_InitStruct->LCDC_CLUTAdress = 0x00;
    LCDC_CLUT_InitStruct->LCDC_RedValue   = 0x00;
    LCDC_CLUT_InitStruct->LCDC_GreenValue = 0x00;
    LCDC_CLUT_InitStruct->LCDC_BlueValue  = 0x00;
}


/**
*\*\name    LCDC_LayerPosition
*\*\fun     Reconfigure the layer position.
*\*\param   LCDC_Layerx: refer to the definition of LCDC_Layer_Module
*\*\          - LCDC_Layer1
*\*\          - LCDC_Layer2
*\*\          - LCDC_Layer3
*\*\          - LCDC_Layer4
*\*\param   OffsetX
*\*\          - 0x0000 ~ 0xFFFF
*\*\param   OffsetY
*\*\          - 0x0000 ~ 0xFFFF
*\*\return  none
**/
void LCDC_LayerPosition(LCDC_Layer_Module* LCDC_Layerx, uint16_t OffsetX, uint16_t OffsetY)
{
    uint32_t tmpbpctrl;
    uint32_t tmppfctrl;
    uint32_t tmpcfblen;
    uint32_t tmpcfblnum;
    uint32_t horizontal_start;
    uint32_t horizontal_stop;
    uint32_t vertical_start;
    uint32_t vertical_stop;
    uint8_t tmp;

    LCDC_Layerx->WHPCTRL &= ~(LCDC_WHPCTRL_WHSTPOS | LCDC_WHPCTRL_WHSPPOS);
    LCDC_Layerx->WVPCTRL &= ~(LCDC_WVPCTRL_WVSTPOS | LCDC_WVPCTRL_WVSPPOS);

    /* Reconfigures the horizontal and vertical start position */
    tmpbpctrl = LCDC->BPCTRL;
    horizontal_start = (tmpbpctrl >> 16) + 1 + OffsetX;
    vertical_start = (tmpbpctrl & 0xFFFF) + 1 + OffsetY;

    tmppfctrl = LCDC_Layerx ->PFCTRL;

    if((tmppfctrl == LCDC_Pixel_Format_ARGB8888) | (tmppfctrl == LCDC_Pixel_Format_ABGR8888) | (tmppfctrl == LCDC_Pixel_Format_RGBA8888) | (tmppfctrl == LCDC_Pixel_Format_BGRA8888))
    {
        tmp = 4;
    }
    else if(tmppfctrl == LCDC_Pixel_Format_RGB888)
    {
        tmp = 3;
    }
    else if((tmppfctrl == LCDC_Pixel_Format_RGB565) | (tmppfctrl == LCDC_Pixel_Format_BGR565))
    {
        tmp = 2;
    }
    else
    {

    }

    tmpcfblen = LCDC_Layerx->CFBLEN;
    horizontal_stop = (((tmpcfblen & 0xFFFF) - 3) / tmp) + horizontal_start - 1;

    tmpcfblnum = LCDC_Layerx->CFBLNUM;
    vertical_stop = (tmpcfblnum & 0xFFFF) + vertical_start - 1;

    LCDC_Layerx->WHPCTRL = horizontal_start | (horizontal_stop << 16);
    LCDC_Layerx->WVPCTRL = vertical_start | (vertical_stop << 16);
}

/**
*\*\name    LCDC_LayerAlpha
*\*\fun     Reconfigure constant alpha.
*\*\param   LCDC_Layerx: refer to the definition of LCDC_Layer_Module
*\*\          - LCDC_Layer1
*\*\          - LCDC_Layer2
*\*\          - LCDC_Layer3
*\*\          - LCDC_Layer4
*\*\param   ConstantAlpha
*\*\          - 0x00 ~ 0xFF
*\*\return  none
**/
void LCDC_LayerAlpha(LCDC_Layer_Module* LCDC_Layerx, uint8_t ConstantAlpha)
{
    LCDC_Layerx -> CACTRL = ConstantAlpha;
}

/**
*\*\name    LCDC_LayerAddress
*\*\fun     Reconfigure layer address.
*\*\param   LCDC_Layerx: refer to the definition of LCDC_Layer_Module
*\*\          - LCDC_Layer1
*\*\          - LCDC_Layer2
*\*\          - LCDC_Layer3
*\*\          - LCDC_Layer4
*\*\param   Address
*\*\          - 0x00000000 ~ 0xFFFFFFFF
*\*\return  none
**/
void LCDC_LayerAddress(LCDC_Layer_Module* LCDC_Layerx, uint32_t Address)
{
    LCDC_Layerx -> CFBADDR = Address;
}

/**
*\*\name    LCDC_LayerSize
*\*\fun     Reconfigure layer size.
*\*\param   LCDC_Layerx: refer to the definition of LCDC_Layer_Module
*\*\          - LCDC_Layer1
*\*\          - LCDC_Layer2
*\*\          - LCDC_Layer3
*\*\          - LCDC_Layer4
*\*\param   Width
*\*\          - layer window width
*\*\param   Height
*\*\          - layer window height
*\*\return  none
**/
void LCDC_LayerSize(LCDC_Layer_Module* LCDC_Layerx, uint32_t Width, uint32_t Height)
{
    uint8_t tmp;
    uint32_t tmppfctrl;
    uint32_t tmpwhpctrl;
    uint32_t tmpwvpctrl;
    uint32_t horizontal_start;
    uint32_t horizontal_stop;
    uint32_t vertical_start;
    uint32_t vertical_stop;

    tmppfctrl = LCDC_Layerx ->PFCTRL;

    if((tmppfctrl == LCDC_Pixel_Format_ARGB8888) | (tmppfctrl == LCDC_Pixel_Format_ABGR8888) | (tmppfctrl == LCDC_Pixel_Format_RGBA8888) | (tmppfctrl == LCDC_Pixel_Format_BGRA8888))
    {
        tmp = 4;
    }
    else if(tmppfctrl == LCDC_Pixel_Format_RGB888)
    {
        tmp = 3;
    }
    else if((tmppfctrl == LCDC_Pixel_Format_RGB565) | (tmppfctrl == LCDC_Pixel_Format_BGR565))
    {
        tmp = 2;
    }
    else
    {

    }

    /* update horizontal and vertical stop */
    tmpwhpctrl = LCDC_Layerx->WHPCTRL;
    horizontal_start = (tmpwhpctrl & 0xFFFF);
    horizontal_stop = Width + horizontal_start - 1;

    tmpwvpctrl = LCDC_Layerx->WVPCTRL;
    vertical_start = (tmpwvpctrl & 0xFFFF);
    vertical_stop = Height + vertical_start - 1;

    LCDC_Layerx->WHPCTRL = horizontal_start | (horizontal_stop << 16);
    LCDC_Layerx->WVPCTRL = vertical_start | (vertical_stop << 16);

    /* Reconfigures the color frame buffer pitch in byte */
    LCDC_Layerx->CFBLEN  = ((Width * tmp) << 16) | ((Width * tmp) + 3);

    /* Reconfigures the frame buffer line number */
    LCDC_Layerx->CFBLNUM  = Height;
}

/**
*\*\name    LCDC_LayerPixelFormat
*\*\fun     Reconfigure layer pixel format.
*\*\param   LCDC_Layerx: refer to the definition of LCDC_Layer_Module
*\*\          - LCDC_Layer1
*\*\          - LCDC_Layer2
*\*\          - LCDC_Layer3
*\*\          - LCDC_Layer4
*\*\param   PixelFormat
*\*\          - LCDC_Pixel_Format_ARGB8888
*\*\          - LCDC_Pixel_Format_ABGR8888
*\*\          - LCDC_Pixel_Format_RGBA8888
*\*\          - LCDC_Pixel_Format_BGRA8888
*\*\          - LCDC_Pixel_Format_RGB565
*\*\          - LCDC_Pixel_Format_BGR565
*\*\          - LCDC_Pixel_Format_RGB888
*\*\return  none
**/
void LCDC_LayerPixelFormat(LCDC_Layer_Module* LCDC_Layerx, uint32_t PixelFormat)
{
    uint8_t tmp;
    uint32_t tmppfctrl;
    uint32_t tmpcfblen;

    tmppfctrl = LCDC_Layerx ->PFCTRL;

    if((tmppfctrl == LCDC_Pixel_Format_ARGB8888) | (tmppfctrl == LCDC_Pixel_Format_ABGR8888) | (tmppfctrl == LCDC_Pixel_Format_RGBA8888) | (tmppfctrl == LCDC_Pixel_Format_BGRA8888))
    {
        tmp = 4;
    }
    else if(tmppfctrl == LCDC_Pixel_Format_RGB888)
    {
        tmp = 3;
    }
    else if((tmppfctrl == LCDC_Pixel_Format_RGB565) | (tmppfctrl == LCDC_Pixel_Format_BGR565))
    {
        tmp = 2;
    }
    else
    {

    }

    tmpcfblen = (LCDC_Layerx->CFBLEN >> 16);
    tmpcfblen = (tmpcfblen / tmp);

    if((PixelFormat == LCDC_Pixel_Format_ARGB8888) | (PixelFormat == LCDC_Pixel_Format_ABGR8888) | (PixelFormat == LCDC_Pixel_Format_RGBA8888) | (PixelFormat == LCDC_Pixel_Format_BGRA8888))
    {
        tmp = 4;
    }
    else if(PixelFormat == LCDC_Pixel_Format_RGB888)
    {
        tmp = 3;
    }
    else if((PixelFormat == LCDC_Pixel_Format_RGB565) | (PixelFormat == LCDC_Pixel_Format_BGR565))
    {
        tmp = 2;
    }
    else
    {

    }

    /* Reconfigures the color frame buffer pitch in byte */
    LCDC_Layerx->CFBLEN  = ((tmpcfblen * tmp) << 16) | ((tmpcfblen * tmp) + 3);

    /* Reconfigures the color frame buffer start address */
    LCDC_Layerx->PFCTRL = PixelFormat;
}

/**
*\*\name    LCDC_ConfigInt
*\*\fun     Enables or disables the specified LCDC's interrupts.
*\*\param   LCDC_IT
*\*\          - LCDC_INT_LIEN
*\*\          - LCDC_INT_FUIEN
*\*\          - LCDC_INT_BEIEN
*\*\          - LCDC_INT_RRIEN
*\*\          - LCDC_INT_STNSIGIEN
*\*\          - LCDC_INT_STNSYNCIEN
*\*\          - LCDC_INT_FUKIEN
*\*\          - LCDC_INT_CRCIEN
*\*\          - LCDC_INT_RFEIEN
*\*\param   Cmd
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void LCDC_ConfigInt(uint32_t LCDC_IT, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the Interrupt sources */
        LCDC->INTEN |= (uint32_t)LCDC_IT;
    }
    else
    {
        /* Disable the Interrupt sources */
        LCDC->INTEN &= (uint32_t)(~LCDC_IT);
    }
}

/**
*\*\name    LCDC_GetFlagStatus
*\*\fun     Checks whether the specified LCDC flag is set or not.
*\*\param   LCDC_FLAG
*\*\          - LCDC_FLAG_L
*\*\          - LCDC_FLAG_FU
*\*\          - LCDC_FLAG_BE
*\*\          - LCDC_FLAG_RR
*\*\          - LCDC_FLAG_STNSIG
*\*\          - LCDC_FLAG_STNSYNC
*\*\          - LCDC_FLAG_CRC
*\*\          - LCDC_FLAG_RFE
*\*\return  The new state of LCDC_FLAG (SET or RESET).
**/
FlagStatus LCDC_GetFlagStatus(uint32_t LCDC_FLAG)
{
    FlagStatus bitstatus;

    if ((LCDC->INTSTS & LCDC_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
*\*\name    LCDC_ClearFlag
*\*\fun     Clears the LCDC's pending flags.
*\*\param   LCDC_FLAG
*\*\          - LCDC_FLAG_L
*\*\          - LCDC_FLAG_FU
*\*\          - LCDC_FLAG_BE
*\*\          - LCDC_FLAG_RR
*\*\          - LCDC_FLAG_STNSIG
*\*\          - LCDC_FLAG_STNSYNC
*\*\          - LCDC_FLAG_CRC
*\*\          - LCDC_FLAG_RFE
*\*\return  none.
**/
void LCDC_ClearFlag(uint32_t LCDC_FLAG)
{
    /* Clear the flags */
    LCDC->INTCLR = LCDC_FLAG;
}

/**
*\*\name    LCDC_GetIntStatus
*\*\fun     Checks whether the specified LCDC's interrupt has occurred or not.
*\*\param   LCDC_IT
*\*\          - LCDC_INT_LIEN
*\*\          - LCDC_INT_FUIEN
*\*\          - LCDC_INT_BEIEN
*\*\          - LCDC_INT_RRIEN
*\*\          - LCDC_INT_STNSIGIEN
*\*\          - LCDC_INT_STNSYNCIEN
*\*\          - LCDC_INT_FUKIEN
*\*\          - LCDC_INT_CRCIEN
*\*\          - LCDC_INT_RFEIEN
*\*\return  The new state of LCDC_IT (SET or RESET).
**/
INTStatus LCDC_GetIntStatus(uint32_t LCDC_IT)
{
    INTStatus bitstatus;

    if ((LCDC->INTSTS & LCDC_IT) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    if (((LCDC->INTEN & LCDC_IT) != (uint32_t)RESET) && (bitstatus != (uint32_t)RESET))
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
*\*\name    LCDC_ClrIntPendingBit
*\*\fun     Clears the LCDC's interrupt pending bits.
*\*\param   LCDC_IT
*\*\          - LCDC_INT_LIEN
*\*\          - LCDC_INT_FUIEN
*\*\          - LCDC_INT_BEIEN
*\*\          - LCDC_INT_RRIEN
*\*\          - LCDC_INT_STNSIGIEN
*\*\          - LCDC_INT_STNSYNCIEN
*\*\          - LCDC_INT_FUKIEN
*\*\          - LCDC_INT_CRCIEN
*\*\          - LCDC_INT_RFEIEN
*\*\return  none.
**/
void LCDC_ClrIntPendingBit(uint32_t LCDC_IT)
{
    /* Clear the IT pending Bit */
    LCDC->INTCLR = LCDC_IT;
}










