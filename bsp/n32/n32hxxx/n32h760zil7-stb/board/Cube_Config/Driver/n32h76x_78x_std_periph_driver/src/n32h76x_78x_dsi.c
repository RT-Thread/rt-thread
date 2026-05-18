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
 * @file n32h76x_78x_dsi.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */ 
#include "n32h76x_78x_dsi.h"
#include "stdio.h"


static DSI_StateTypeDef DSI_ShortWrite(DSI_HandleTypeDef *hdsi, DSI_PKTCtrlTypeDef PacketCtrl);

/**
*\*\name    DSI_EnableWrapper.
*\*\fun     Enable DSI Wrapper.
*\*\param   hdsi: dsi host instance.
*\*\param  cmd : 
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  None.
**/
void DSI_EnableWrapper(DSI_HandleTypeDef *hdsi, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        hdsi->InstanceWrap->DSI_WRPCTRL  &= ~DSI_WRPCTRL_TRIGREQ;
    }
    else
    {
        hdsi->InstanceWrap->DSI_WRPCTRL  |= DSI_WRPCTRL_TRIGREQ;
    }
}

/**
*\*\name    DSI_Disable.
*\*\fun     Disable DSI.
*\*\param   hdsi: dsi host instance.
*\*\return  None.
**/
void DSI_Disable(DSI_HandleTypeDef *hdsi)
{
    hdsi->Instance->DSI_NUMLANES  = DSI_REGISTER_MASK;
}

/**
*\*\name    DSI_EnableClockLane.
*\*\fun     Enable or Disable DSI clock lane.
*\*\param   hdsi: dsi host instance.
*\*\param   Cmd : 
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  None.
**/
void DSI_EnableClockLane(DSI_HandleTypeDef *hdsi, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        hdsi->Instance->DSI_CLKLANEN  = DSI_CLKLANEN_CLKLANEN;
    }
    else
    {
        hdsi->Instance->DSI_CLKLANEN  &= ~DSI_CLKLANEN_CLKLANEN;
    }
}

/**
*\*\name    DSI_EnableDataLane.
*\*\fun     Configure DSI data lane number.
*\*\param   hdsi: dsi host instance.
*\*\param   datalinenum : 
*\*\          - DSI_ONE_DATALANE_ENABLE
*\*\          - DSI_TWO_DATALANES_ENABLE
*\*\          - DSI_THREE_DATALANES_ENABLE
*\*\          - DSI_FOUR_DATALANES_ENABLE
*\*\return  None.
**/
void DSI_ConfigDataLaneNum(DSI_HandleTypeDef *hdsi, uint32_t datalinenum)
{
    hdsi->Instance->DSI_DATLANEN  = datalinenum;
}

/**
*\*\name    DSI_SetVCID.
*\*\fun     Configure DSI virtual channel ID.
*\*\param   hdsi: dsi host instance.
*\*\param   channel : 
*\*\return  None.
**/
void DSI_SetVCID(DSI_HandleTypeDef *hdsi, uint32_t channel)
{
    hdsi->Instance->VID_VC  = channel;
}

/**
*\*\name    DSI_CofigWrapULPSDL.
*\*\fun     Configure DSI wrapper data lane number.
*\*\param   hdsi: dsi host instance.
*\*\param   datalinenum : 
*\*\          - DSI_ULPS_ONE_DATA_LANE
*\*\          - DSI_ULPS_TWO_DATA_LANES
*\*\          - DSI_ULPS_THREE_DATA_LANES
*\*\          - DSI_ULPS_FOUR_DATA_LANES
*\*\param   Cmd : 
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  None.
**/
void DSI_CofigWrapULPSDL(DSI_HandleTypeDef *hdsi, uint32_t datalinenum, FunctionalState Cmd)
{
    uint32_t temp;
    temp = hdsi->InstanceWrap->DSI_WRPCTRL;
    temp &= ~DSI_WRPCTRL_ULPSDLEN;
    if(Cmd != DISABLE)
    {
        temp |= datalinenum << DSI_WRPCTRL_ULPSDLEN_POS;
        hdsi->InstanceWrap->DSI_WRPCTRL = temp;
    }
    else
    {
        hdsi->InstanceWrap->DSI_WRPCTRL = temp;
    }
}

/**
*\*\name    DSI_EnableWrapULPSDL.
*\*\fun     Configure DSI wrapper data lane number.
*\*\param   hdsi: dsi host instance.
*\*\param   Cmd : 
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  None.
**/
void DSI_EnableWrapULPSCL(DSI_HandleTypeDef *hdsi, FunctionalState Cmd)
{
    uint32_t temp;
    
    temp = hdsi->InstanceWrap->DSI_WRPCTRL;
    temp &= ~DSI_WRPCTRL_ULPSCLEN;
    if(Cmd != DISABLE)
    {
        temp |= DSI_WRPCTRL_ULPSCLEN;
        hdsi->InstanceWrap->DSI_WRPCTRL = temp;
    }
    else
    {
        hdsi->InstanceWrap->DSI_WRPCTRL = temp;
    }
}

/**
*\*\name    DSI_DisableSkewCal.
*\*\fun     Disable DSI skew calibration .
*\*\param   hdsi: dsi host instance.
*\*\return  None.
**/
void DSI_DisableSkewCal(DSI_HandleTypeDef *hdsi)
{
    hdsi->Instance->DSI_SKEWCALINE  = DSI_REGISTER_MASK;
}

/**
*\*\name    DSI_DeInit.
*\*\fun     De-initializes the DSI peripheral registers to their default reset
*\*\param   hdsi: dsi host instance.
*\*\return  None.
**/
DSI_StateTypeDef DSI_DeInit(DSI_HandleTypeDef *hdsi)
{
    /* Check the DSI handle allocation */
    if (hdsi == NULL)
    {
        return DSI_ERROR;
    }

    /* Change DSI peripheral state */
    hdsi->State = DSI_BUSY;

    /* Disable the DSI wrapper: write bit9 = 0 NEED TBD */
    DSI_EnableWrapper(hdsi, ENABLE);

    /* Disable the DSI host */
    DSI_Disable(hdsi);

    /* D-PHY clock lane and data lane disable */
    DSI_EnableClockLane(hdsi, DISABLE);

    /* Disable the skewcal*/
    DSI_DisableSkewCal(hdsi);

    /* Initialize the error code */
    hdsi->ErrorCode = DSI_NO_ERRORS;

    /* Initialize the DSI state*/
    hdsi->State = DSI_RESET;

    /* Release Lock */
    hdsi->Lock = DSI_UNLOCKED;

  return DSI_OK;
}

/**
*\*\name    DSI_InitHostWrap.
*\*\fun     Initialize DSI host and wrapper .
*\*\param   hdsi: dsi host instance.
*\*\return  None.
**/
void DSI_InitHostWrap(DSI_HandleTypeDef *hdsi)
{
   /* Base address of DSI Host/Wrapper registers to be set before calling De-Init */
    hdsi->Instance     = DSI_HOST;
    hdsi->InstanceWrap = DSI_HOST_WRAPPER;
}

/**
*\*\name    DSI_GetPHYStatus.
*\*\fun     Get DSI PHY status.
*\*\param   hdsi: dsi host instance.
*\*\return  SET or RESET.
**/
FlagStatus DSI_GetPHYStatus(DSI_HandleTypeDef *hdsi)
{
    FlagStatus bitstatus = RESET;

    hdsi->InstanceWrap->DSIPHY_PLLSTS = 1;

    if ((hdsi->InstanceWrap->DSIPHY_PLLSTS & DSIPHY_PLLSTS_PHYREADY) != DSIPHY_PLLSTS_PHYREADY)
    {
        bitstatus = RESET;
    }
    else
    {
        bitstatus = SET;
    }
    /* Return the flag status */
    return bitstatus;
}

/**
*\*\name    DSI_InitHostWrap.
*\*\fun     Initialize DSI PHY .
*\*\param   hdsi: dsi host instance.
*\*\return  DSI_StateTypeDef.
**/
void DSI_InitPHY(DSI_HandleTypeDef *hdsi, DSI_PHY_InitTypeDef *PHY_InitParams)
{
    uint32_t tmp1 = 0;
    uint32_t tmp2 = 0;
    uint32_t tmp3 = 0;
    uint32_t tmp4 = 0;
    uint32_t tmp5 = 0;
    uint32_t tmp6 = 0;
    uint32_t tmp7 = 0;
    
    // config wrap register 0x08: CFG_LN_SWAP_SEL 
    hdsi->InstanceWrap->DSIPHY_CTRL1 &= ~(DSIPHY_CTRL1_REFCKSEL | DSIPHY_CTRL1_EXTDCYCEL | DSIPHY_CTRL1_L4SEL | DSIPHY_CTRL1_L3SEL | DSIPHY_CTRL1_L2SEL | DSIPHY_CTRL1_L1SEL | DSIPHY_CTRL1_L0SEL);
    tmp1 = ( PHY_InitParams->L4_Swap_Sel_Value << DSIPHY_CTRL1_L4SEL_POS);
    tmp2 = ( PHY_InitParams->L3_Swap_Sel_Value << DSIPHY_CTRL1_L3SEL_POS);
    tmp3 = ( PHY_InitParams->L2_Swap_Sel_Value << DSIPHY_CTRL1_L2SEL_POS);
    tmp4 = ( PHY_InitParams->L1_Swap_Sel_Value << DSIPHY_CTRL1_L1SEL_POS);
    tmp5 = ( PHY_InitParams->L0_Swap_Sel_Value << DSIPHY_CTRL1_L0SEL_POS);
    
    // config wrap register 0x08 
    tmp6 = ( PHY_InitParams->RefCLK_In_Sel << DSIPHY_CTRL1_REFCKSEL_POS);
    tmp7 = ( PHY_InitParams->EXTD_CYCLE_SEL << DSIPHY_CTRL1_EXTDCYCEL_POS);
    hdsi->InstanceWrap->DSIPHY_CTRL1 |= (tmp1 | tmp2 | tmp3 | tmp4 | tmp5 | tmp6 | tmp7);
    
    // config wrap register 0x0c 
    tmp1 = ( PHY_InitParams->DLANE_HS_PER_TIME << DSIPHY_CTRL2_DLPRET_POS);
    tmp2 = ( PHY_InitParams->DLANE_HS_ZERO_TIME << DSIPHY_CTRL2_DLZEROT_POS);
    tmp3 = ( PHY_InitParams->DLANE_HS_TRAIL_TIME << DSIPHY_CTRL2_DLTRAT_POS);
    tmp4 = ( PHY_InitParams->CLANE_HS_PER_TIME << DSIPHY_CTRL2_CLPRET_POS);
    hdsi->InstanceWrap->DSIPHY_CTRL2 = (tmp1 | tmp2 | tmp3 | tmp4);
    
    // config wrap register 0x10 
    tmp1 = ( PHY_InitParams->CLANE_HS_ZERO_TIME << DSIPHY_CTRL3_CLZEROT_POS);
    tmp2 = ( PHY_InitParams->CLANE_HS_TRAIL_TIME << DSIPHY_CTRL3_CLTRLT_POS);
    tmp3 = ( PHY_InitParams->CLANE_HS_CLK_PRE_TIME << DSIPHY_CTRL3_CLCLKPRET_POS);
    tmp4 = ( PHY_InitParams->CLANE_HS_CLK_POST_TIME << DSIPHY_CTRL3_CLCLKPOST_POS);
    hdsi->InstanceWrap->DSIPHY_CTRL3 = (tmp1 | tmp2 | tmp3 | tmp4);
    
    // config wrap register 0x64
    tmp1 = ( PHY_InitParams->PLL_FBK_FRA7_0 << 0);
    tmp2 = ( PHY_InitParams->PLL_FBK_FRA15_8 << 8);
    tmp3 = ( PHY_InitParams->PLL_FBK_FRA23_16 << 16);
    hdsi->InstanceWrap->DSIPHY_PLLCTRL1 = (tmp1 | tmp2 | tmp3 );

    // config wrap register 0x68 
    tmp1 = ( PHY_InitParams->PLL_SSC_DELTA7_0 << DSIPHY_PLLCTRL2_SSCAMPOP_POS );
    tmp2 = ( PHY_InitParams->PLL_SSC_DELTA15_8 << 20 );
    tmp3 = ( PHY_InitParams->PLL_SSC_DELTA17_16 << 28 );
    hdsi->InstanceWrap->DSIPHY_PLLCTRL2 = (tmp1 | tmp2 | tmp3 |(PHY_InitParams->PLL_PRE_DIV << DSIPHY_PLLCTRL2_PREDIV_POS) | (PHY_InitParams->PLL_FBK_INT << DSIPHY_PLLCTRL2_FBKINT_POS));
    
    // config wrap register 0x6c 
    tmp1 = ( PHY_InitParams->PLL_SSC_DELTA_INIT7_0 << 0 );
    tmp2 = ( PHY_InitParams->PLL_SSC_DELTA_INIT15_8 << 8 );
    tmp3 = ( PHY_InitParams->PLL_SSC_DELTA_INIT17_16 << 16 );
    tmp4 = ( PHY_InitParams->PLL_SSC_PRD7_0 << DSIPHY_PLLCTRL3_SSCPRD_POS );
    tmp5 = ( PHY_InitParams->PLL_SSC_PRD9_8 << 26 );
    hdsi->InstanceWrap->DSIPHY_PLLCTRL3 = (tmp5 | tmp4 | tmp3 | tmp2 | tmp1 );

    // config wrap register 0x70 and 0x74, added default lane impedance, only for high speed TX, LPDT does not use HS TX
    hdsi->InstanceWrap->DSIPHY_PLLCTRL4 |= 0x21084210;
    hdsi->InstanceWrap->DSIPHY_PLLCTRL5 |= 0x84210;
}

/**
*\*\name    DSI_Start.
*\*\fun     Initialize DSI PHY .
*\*\param   hdsi: dsi host instance.
*\*\return  DSI_StateTypeDef.
**/
DSI_StateTypeDef DSI_Start(DSI_HandleTypeDef *hdsi)
{
    uint32_t temp;
    /* Process locked */
    hdsi->Lock = DSI_LOCKED;
    /* Enable the DSI host */
    // enable clock lane
    DSI_EnableClockLane(hdsi, ENABLE);
    
    /* Request on Data Lanes */
    if(hdsi->HostInit.NumOfLanes == DSI_ONE_DATA_LANE)
    {
        temp = DSI_ONE_DATALANE_ENABLE;
    }
    else if(hdsi->HostInit.NumOfLanes == DSI_TWO_DATA_LANES)
    {
        temp = DSI_TWO_DATALANES_ENABLE;
    }
    else if(hdsi->HostInit.NumOfLanes == DSI_THREE_DATA_LANES)
    {
        temp = DSI_THREE_DATALANES_ENABLE;
    }
    else if(hdsi->HostInit.NumOfLanes == DSI_FOUR_DATA_LANES)
    {
        temp = DSI_FOUR_DATALANES_ENABLE;
    }
    // enable data lane
    DSI_ConfigDataLaneNum(hdsi, temp);
    /* Process unlocked */
    hdsi->Lock = DSI_UNLOCKED;
    return DSI_OK;
}

/**
*\*\name    DSI_EnterULPSData.
*\*\fun     Enter the ULPM (Ultra Low Power Mode) with the D-PHY PLL running(only data lanes are in ULPM)
*\*\param   hdsi: dsi host instance.
*\*\param   Cmd : 
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  DSI_StateTypeDef.
**/
DSI_StateTypeDef DSI_EnterULPSData(DSI_HandleTypeDef *hdsi, FunctionalState Cmd)
{
    uint32_t temp;
    uint32_t timeout = DSI_TIME_OUT_VALUE;
    /* Process locked */
    hdsi->Lock = DSI_LOCKED;

    /* ULPS Request on Data Lanes */
    if(hdsi->HostInit.NumOfLanes == DSI_ONE_DATA_LANE)
    {
        temp = DSI_ULPS_ONE_DATA_LANE;
    }
    else if(hdsi->HostInit.NumOfLanes == DSI_TWO_DATA_LANES)
    {
        temp = DSI_ULPS_TWO_DATA_LANE;
    }
    else if(hdsi->HostInit.NumOfLanes == DSI_THREE_DATA_LANES)
    {
        temp = DSI_ULPS_THREE_DATA_LANE;
    }
    else if(hdsi->HostInit.NumOfLanes == DSI_FOUR_DATA_LANES)
    {
        temp = DSI_ULPS_FOUR_DATA_LANE;
    }
    DSI_CofigWrapULPSDL(hdsi, temp, ENABLE);
    // wait data lane enter ULPS
    while(((hdsi->InstanceWrap->DSI_WRPSTS & DSI_WRPCTRL_ULPSDLEN) != temp) && timeout--)
    {
    }
    /* Process unlocked */
    hdsi->Lock = DSI_UNLOCKED;
    
    if(timeout == 0xFFFFFFFF)
    {
        return DSI_TIMEOUT;
    }
    return DSI_OK;
}

/**
*\*\name    DSI_EnterULPSClock.
*\*\fun     Enter the ULPM (Ultra Low Power Mode) with the C-PHY PLL running (only clock lanes are in ULPM)
*\*\param   hdsi: dsi host instance.
*\*\return  DSI_StateTypeDef.
**/
DSI_StateTypeDef DSI_EnterULPSClock(DSI_HandleTypeDef *hdsi)
{
    uint32_t timeout = DSI_TIME_OUT_VALUE;
    /* Process locked */
    hdsi->Lock = DSI_LOCKED;

    /* ULPS Request on Clock Lanes */
    DSI_EnableWrapULPSCL(hdsi, ENABLE);
    
    // wait clock lane enter ULPS
    while(((hdsi->InstanceWrap->DSI_WRPSTS & DSI_WRPCTRL_ULPSCLEN) != DSI_WRPCTRL_ULPSCLEN) && timeout--)
    {
    }

    /* Process unlocked */
    hdsi->Lock = DSI_UNLOCKED;
    
    if(timeout == 0xFFFFFFFF)
    {
        return DSI_TIMEOUT;
    }
    return DSI_OK;
}

/**
*\*\name    DSI_ExitULPSClock.
*\*\fun     Exit the ULPM (Ultra Low Power Mode) with the C-PHY PLL running (only clock lanes are in ULPM)
*\*\param   hdsi: dsi host instance.
*\*\return  DSI_StateTypeDef.
**/
DSI_StateTypeDef DSI_ExitULPSClock(DSI_HandleTypeDef *hdsi)
{
    uint32_t timeout = DSI_TIME_OUT_VALUE;
    /* Process locked */
    hdsi->Lock = DSI_LOCKED;

    /* Exit ULPS on Clock Lanes */
    DSI_EnableWrapULPSCL(hdsi, DISABLE);

    // wait clock lane enter ULPS
    while(((hdsi->InstanceWrap->DSI_WRPSTS & DSI_WRPCTRL_ULPSCLEN) != 0) && timeout--)
    {
    }
    /* Process unlocked */
    hdsi->Lock = DSI_UNLOCKED;

    if(timeout == 0xFFFFFFFF)
    {
        return DSI_TIMEOUT;
    }
    return DSI_OK;
}

/**
*\*\name    DSI_EnterULPS.
*\*\fun      Enter the ULPM (Ultra Low Power Mode)(both data and clock lanes are in ULPM)
*\*\param   hdsi: dsi host instance.
*\*\return  DSI_StateTypeDef.
**/
DSI_StateTypeDef DSI_EnterULPS(DSI_HandleTypeDef *hdsi)
{
    DSI_StateTypeDef result;
    /* Process locked */
    hdsi->Lock = DSI_LOCKED;

    /* ULPS Request on Clock Lanes */
    result = DSI_EnterULPSClock(hdsi);
    
    if(result != DSI_OK)
    {
        /* Process unlocked */
        hdsi->Lock = DSI_UNLOCKED;
        return result;
    }

    /* ULPS Request on Data Lanes */
    result = DSI_EnterULPSData(hdsi, ENABLE);

    /* Process unlocked */
    hdsi->Lock = DSI_UNLOCKED;

    return result;
}

/**
*\*\name    DSI_ExitULPS.
*\*\fun     Exit the ULPM (Ultra Low Power Mode)(both data and clock lanes are in ULPM)
*\*\param   hdsi: dsi host instance.
*\*\return  DSI_StateTypeDef.
**/
DSI_StateTypeDef DSI_ExitULPS(DSI_HandleTypeDef *hdsi)
{
    DSI_StateTypeDef result;
    /* Process locked */
    hdsi->Lock = DSI_LOCKED;

    /* Exit ULPS on Data Lanes */
    result = DSI_EnterULPSData(hdsi, DISABLE);
    if(result != DSI_OK)
    {
        /* Process unlocked */
        hdsi->Lock = DSI_UNLOCKED;
        return result;
    }

    /* Exit ULPS on Clock Lanes */
    result = DSI_ExitULPSClock(hdsi);

    /* Process unlocked */
    hdsi->Lock = DSI_UNLOCKED;

    return DSI_OK;
}

/**
*\*\name    DSI_EnableWrapperISkewCal.
*\*\fun     Enable or disable Wrapper Initial skew calibration.
*\*\param   hdsi: dsi host instance.
*\*\param   Cmd : 
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  None.
**/
void DSI_EnableWrapperISkewCal(DSI_HandleTypeDef *hdsi, FunctionalState Cmd)
{
    uint32_t temp;
    temp = hdsi->InstanceWrap->DSI_WRPCTRL;
    if(Cmd != DISABLE)
    {
        temp |= DSI_WRPCTRL_ISKEWCAL;
        hdsi->InstanceWrap->DSI_WRPCTRL = temp;
    }
    else
    {
        temp &= ~DSI_WRPCTRL_ISKEWCAL;
        hdsi->InstanceWrap->DSI_WRPCTRL = temp;
    }
}

/**
*\*\name    DSI_EnableWrapperPSkewCal.
*\*\fun     Enable or disable Wrapper Period skew calibration.
*\*\param   hdsi: dsi host instance.
*\*\param   Cmd : 
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  None.
**/
void DSI_EnableWrapperPSkewCal(DSI_HandleTypeDef *hdsi, FunctionalState Cmd)
{
    uint32_t temp;
    temp = hdsi->InstanceWrap->DSI_WRPCTRL;
    if(Cmd != DISABLE)
    {
        temp |= DSI_WRPCTRL_PSKEWCAL;
        hdsi->InstanceWrap->DSI_WRPCTRL = temp;
    }
    else
    {
        temp &= ~DSI_WRPCTRL_PSKEWCAL;
        hdsi->InstanceWrap->DSI_WRPCTRL = temp;
    }
}

/**
*\*\name    DSI_EnableInitialSkewCali.
*\*\fun     Enable Wrapper Initialize skew calibration.
*\*\param   hdsi: dsi host instance.
*\*\return  None.
**/
DSI_StateTypeDef DSI_EnableInitialSkewCalib(DSI_HandleTypeDef *hdsi)
{
    uint32_t timeout = DSI_TIME_OUT_VALUE;
    /* Process locked */
    hdsi->Lock = DSI_LOCKED;

    // enable initial skew 
    DSI_EnableWrapperISkewCal(hdsi, ENABLE);

    // wait for status 
    while((((hdsi->InstanceWrap->DSI_WRPSTS) & DSI_WRPCTRL_ISKEWCAL) == 0) && timeout--)
    {
    }
    // clear status : write 1
    hdsi->InstanceWrap->DSI_WRPSTS |= (DSI_WRPSTS_ISKEWCALDN);

    /* Process unlocked */
    hdsi->Lock = DSI_UNLOCKED;
    
    if(timeout == 0xFFFFFFFF)
    {
        return DSI_TIMEOUT;
    }

    return DSI_OK;
}

/**
*\*\name    DSI_EnableInitialSkewCali.
*\*\fun     Enable Wrapper Period skew calibration.
*\*\param   hdsi: dsi host instance.
*\*\return  None.
**/
DSI_StateTypeDef DSI_EnablePeriodSkewCali(DSI_HandleTypeDef *hdsi)
{
    uint32_t timeout = DSI_TIME_OUT_VALUE;
    /* Process locked */
    hdsi->Lock = DSI_LOCKED;

    // enable period skew 
    DSI_EnableWrapperPSkewCal(hdsi, ENABLE);

    // wait for status 
    while((((hdsi->InstanceWrap->DSI_WRPSTS) & DSI_WRPSTS_PSKEWCALDN) == 0) && timeout--)
    {
    }

     // clear status: write 1
    hdsi->InstanceWrap->DSI_WRPSTS |= (DSI_WRPSTS_PSKEWCALDN);

    /* Process unlocked */
    hdsi->Lock = DSI_UNLOCKED;
    
    if(timeout == 0xFFFFFFFF)
    {
        return DSI_TIMEOUT;
    }

    return DSI_OK;

}

/**
*\*\name    DSI_EnableInitialSkewCali.
*\*\fun     Enable Wrapper reset trigger.
*\*\param   hdsi: dsi host instance.
*\*\return  None.
**/
DSI_StateTypeDef DSI_EnableResetTrigger(DSI_HandleTypeDef *hdsi)
{
    uint32_t timeout = DSI_TIME_OUT_VALUE;
    /* Process locked */
    hdsi->Lock = DSI_LOCKED;

    // set reset trigger and enable reset trigger send
    hdsi->InstanceWrap->DSI_WRPCTRL &= ~DSI_WRPCTRL_TRIGSEND;
    hdsi->InstanceWrap->DSI_WRPCTRL |= DSI_WRPCTRL_TRIGREQ;

    // wait for status 
    while((((hdsi->InstanceWrap->DSI_WRPSTS) & DSI_WRPSTS_TRIGACK) == 0) && timeout--)
    {
    }
    // clear status: write 1
    hdsi->InstanceWrap->DSI_WRPSTS |= (DSI_WRPSTS_TRIGACK);

    /* Process unlocked */
    hdsi->Lock = DSI_UNLOCKED;
    
    if(timeout == 0xFFFFFFFF)
    {
        return DSI_TIMEOUT;
    }

    return DSI_OK;
}

/**
*\*\name    DSI_Wrapper_ConfigInt
*\*\fun     Enables or disables the specified DSI Wrapper's interrupts.
*\*\param   hdsi: dsi host instance.
*\*\param   DSI_IT
*\*\          - DSI_WRAPPER_INT_BLKERRIEN
*\*\          - DSI_WRAPPER_INT_SPERRIEN
*\*\          - DSI_WRAPPER_INT_OVERRIEN
*\*\          - DSI_WRAPPER_INT_UNDERRIEN
*\*\param   Cmd
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void DSI_Wrapper_ConfigInt(DSI_HandleTypeDef *hdsi, uint32_t DSI_IT, FunctionalState Cmd)
{
	/* Process locked */
    hdsi->Lock = DSI_LOCKED;
	
    if (Cmd != DISABLE)
    {
        /* Enable the Interrupt sources */
        hdsi->InstanceWrap->DSI_WRPCTRL |= (uint32_t)DSI_IT;
    }
    else
    {
        /* Disable the Interrupt sources */
        hdsi->InstanceWrap->DSI_WRPCTRL &= (uint32_t)(~DSI_IT);
    }
	
	/* Process unlocked */
    hdsi->Lock = DSI_UNLOCKED;
}


/**
*\*\name    DSI_Wrapper_GetFlagStatus
*\*\fun     Checks whether the specified LCDC flag is set or not.
*\*\param   hdsi: dsi host instance.
*\*\param   DSI_FLAG
*\*\          - DSI_WRAPPER_FLAG_ISKEWCALDN
*\*\          - DSI_WRAPPER_FLAG_PSKEWCALDN
*\*\          - DSI_WRAPPER_FLAG_TRIGACK
*\*\          - DSI_WRAPPER_FLAG_BLKERRIEN
*\*\          - DSI_WRAPPER_FLAG_SPERRIEN
*\*\          - DSI_WRAPPER_FLAG_OVERRIEN
*\*\          - DSI_WRAPPER_FLAG_UNDERRIEN
*\*\return  The new state of DSI Wrapper FLAG (SET or RESET).
**/
FlagStatus DSI_Wrapper_GetFlagStatus(DSI_HandleTypeDef *hdsi, uint32_t DSI_FLAG)
{
    FlagStatus bitstatus;
	
	/* Process locked */
    hdsi->Lock = DSI_LOCKED;

    if ((hdsi->InstanceWrap->DSI_WRPSTS & DSI_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
	
	/* Process unlocked */
    hdsi->Lock = DSI_UNLOCKED;

    return bitstatus;
}

/**
*\*\name    DSI_Wrapper_ClearFlag
*\*\fun     Clears the DSI Wrapper's pending flags.
*\*\param   hdsi: dsi host instance.
*\*\param   DSI_FLAG
*\*\          - DSI_WRAPPER_FLAG_ISKEWCALDN
*\*\          - DSI_WRAPPER_FLAG_PSKEWCALDN
*\*\          - DSI_WRAPPER_FLAG_TRIGACK
*\*\          - DSI_WRAPPER_FLAG_BLKERRIEN
*\*\          - DSI_WRAPPER_FLAG_SPERRIEN
*\*\          - DSI_WRAPPER_FLAG_OVERRIEN
*\*\          - DSI_WRAPPER_FLAG_UNDERRIEN
*\*\return  none.
**/
void DSI_Wrapper_ClearFlag(DSI_HandleTypeDef *hdsi, uint32_t DSI_FLAG)
{
	/* Process locked */
    hdsi->Lock = DSI_LOCKED;
	
    /* Clear the flags */
    hdsi->InstanceWrap->DSI_WRPSTS |= (uint32_t)(DSI_FLAG);
	
	/* Process unlocked */
    hdsi->Lock = DSI_UNLOCKED;
}

/**
*\*\name    DSI_Wrapper_GetIntStatus
*\*\fun     Checks whether the specified DSI Wrapper's interrupt has occurred or not.
*\*\param   hdsi: dsi host instance.
*\*\param   DSI_IT
*\*\          - DSI_WRAPPER_INT_BLKERRIEN
*\*\          - DSI_WRAPPER_INT_SPERRIEN
*\*\          - DSI_WRAPPER_INT_OVERRIEN
*\*\          - DSI_WRAPPER_INT_UNDERRIEN
*\*\return  The new state of DSI_IT (SET or RESET).
**/
INTStatus DSI_Wrapper_GetIntStatus(DSI_HandleTypeDef *hdsi, uint32_t DSI_IT)
{
    INTStatus bitstatus;
	
	/* Process locked */
    hdsi->Lock = DSI_LOCKED;

    if ((hdsi->InstanceWrap->DSI_WRPCTRL & DSI_IT) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    if ((bitstatus != (uint32_t)RESET) && ((hdsi->InstanceWrap->DSI_WRPSTS & (DSI_IT >> 2)) != (uint32_t)RESET))
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
	
	/* Process unlocked */
    hdsi->Lock = DSI_UNLOCKED;

    return bitstatus;
}


/**
*\*\name    DSI_Init.
*\*\fun     Initialize the dsi host according to the specified parameters in the DSI_HandleTypeDef.
*\*\param   hdsi: dsi host instance.
*\*\return  DSI_OK or DSI_ERROR.
**/
DSI_StateTypeDef DSI_Init(DSI_HandleTypeDef *hdsi)
{
    uint32_t temp;
    /* Check the LCDC peripheral state */
    if(hdsi == NULL)
    {
        return DSI_ERROR;
    }

    /* Change CDC peripheral state */
    hdsi->State = DSI_BUSY;

    /************************ Set the DSI HOST BASE parameter ************************/
    temp = hdsi->Instance->DSI_DISBST;
    temp &= ~(DSI_DISBST_DISBST);
    temp |= hdsi->HostInit.BurstSel;
    hdsi->Instance->DSI_DISBST = temp;

    temp = hdsi->Instance->DSI_AUTOINSERT_EOTP;
    temp &= ~(DSI_AUTOINSERT_EOTP_AUTOINSEOTP);
    temp |= hdsi->HostInit.AutoInsertEOTP;
    hdsi->Instance->DSI_AUTOINSERT_EOTP = temp;
    
    temp = hdsi->Instance->DSI_DISRXCRCCHK;
    temp &= ~(DSI_DISRXCRCCHK_DISRXCRCCHK);
    temp |= hdsi->HostInit.DisRXCRC;
    hdsi->Instance->DSI_DISRXCRCCHK = temp;
    
    temp = hdsi->Instance->DSI_TPRE;
    temp &= ~(DSI_TPRE_TPRE<<DSI_TPRE_TPRE_POS);
    temp |= (hdsi->ClockInit.ClockBeforeHS << DSI_TPRE_TPRE_POS);
    hdsi->Instance->DSI_TPRE = temp;

    temp = hdsi->Instance->DSI_TPOST;
    temp &= ~(DSI_TPOST_TPOST<<DSI_TPOST_TPOST_POS);
    temp |= (hdsi->ClockInit.ClockHS2LP << DSI_TPOST_TPOST_POS);
    hdsi->Instance->DSI_TPOST = temp;

    temp = hdsi->Instance->DSI_TXGAP;
    temp &= ~(DSI_TXGAP_TXGAP<<DSI_TXGAP_TXGAP_POS);
    temp |= (hdsi->ClockInit.ClockLP2HS << DSI_TXGAP_TXGAP_POS);
    hdsi->Instance->DSI_TXGAP = temp;
    
    temp = hdsi->Instance->DSI_TWAKEUP;
    temp &= ~(DSI_TWAKEUP_TWAKEUP<<DSI_TWAKEUP_TWAKEUP_POS);
    temp |= (hdsi->ClockInit.ClockExitULPS << DSI_TWAKEUP_TWAKEUP_POS);
    hdsi->Instance->DSI_TWAKEUP = temp;

    temp = hdsi->Instance->DSI_CONTHSCLK;
    temp &= ~(DSI_CONTHSCLK_CONTHSCLK << DSI_CONTHSCLK_CONTHSCLK_POS);
    temp |= (hdsi->ClockInit.ContinuousHSCLK << DSI_CONTHSCLK_CONTHSCLK_POS);
    hdsi->Instance->DSI_CONTHSCLK = temp;

    /************************ Set DSI HOST SKEWCAL Parameter ************************/
    temp = hdsi->Instance->DSI_SKEWCALTIMI;
    temp &= ~(DSI_SKEWCALTIMI_SKEWVALTIMI << DSI_SKEWCALTIMI_SKEWVALTIMI_POS);
    temp |= (hdsi->SkewcalInit.ClockInitialSkewcal << DSI_SKEWCALTIMI_SKEWVALTIMI_POS);
    hdsi->Instance->DSI_SKEWCALTIMI = temp;
    
    temp = hdsi->Instance->DSI_SKEWCALTIMP;
    temp &= ~(DSI_SKEWCALTIMP_SKEWVALTIMP << DSI_SKEWCALTIMP_SKEWVALTIMP_POS);
    temp |= (hdsi->SkewcalInit.ClockPeriodicSkewcal << DSI_SKEWCALTIMP_SKEWVALTIMP_POS);
    hdsi->Instance->DSI_SKEWCALTIMP = temp;
    
    temp = hdsi->Instance->DSI_ALTCALTIM;
    temp &= ~(DSI_ALTCALTIM_ALTCALTIM << DSI_ALTCALTIM_ALTCALTIM_POS);
    temp |= (hdsi->SkewcalInit.ClockAlternateCal << DSI_ALTCALTIM_ALTCALTIM_POS);
    hdsi->Instance->DSI_ALTCALTIM = temp;
    
    temp = hdsi->Instance->DSI_SKEWCALINE;
    temp &= ~(DSI_SKEWCALINE_SKEWCALINE << DSI_SKEWCALINE_SKEWCALINE_POS);
    temp |= (hdsi->SkewcalInit.LinePeriodicSkewcal << DSI_SKEWCALINE_SKEWCALINE_POS);
    hdsi->Instance->DSI_SKEWCALINE = temp;
    
    /* Config the num_lanes to enable the host controller */
    temp = hdsi->Instance->DSI_NUMLANES;
    temp &= ~(DSI_NUMLANES_NUMLANES << DSI_NUMLANES_NUMLANES_POS);
    temp |= (hdsi->HostInit.NumOfLanes << DSI_NUMLANES_NUMLANES_POS);
    hdsi->Instance->DSI_NUMLANES = temp;

    /* Initialize the error code */
    hdsi->ErrorCode = DSI_NO_ERRORS;  

    /* Initialize the LCDC state*/
    hdsi->State = DSI_READY;

    return DSI_OK;
}

/**
*\*\name    DSI_ConfigVideoMode.
*\*\fun     Select video mode and configure the corresponding parameters
*\*\param   hdsi: dsi host instance.
*\*\param   VidCfg: pointer to a DSI_VidCfgTypeDef structure that contains the DSI video mode configuration parameters
*\*\return  DSI_OK or DSI_ERROR.
**/
DSI_StateTypeDef DSI_ConfigVideoMode(DSI_HandleTypeDef *hdsi, DSI_VidCfgTypeDef *VidCfg)
{
    uint32_t temp;
    
    /* Check the LCDC peripheral state */
    if(hdsi == NULL || VidCfg == NULL)
    {
        return DSI_ERROR;
    }
    /* Process locked */
    hdsi->Lock = DSI_LOCKED;

    /************************ Set DSI HOST VID IF ************************/
    temp = hdsi->Instance->VID_PIXPERPKT;
    temp &= ~(VID_PIXPERPKT_PIXPERPKT << VID_PIXPERPKT_PIXPERPKT_POS);
    temp |= (VidCfg->PixelsPerPacket << VID_PIXPERPKT_PIXPERPKT_POS);
    hdsi->Instance->VID_PIXPERPKT = temp;
    
    temp = hdsi->Instance->VID_PIXPLDSIZ;
    temp &= ~(VID_PIXPLDSIZ_PIXPLDSIZ << VID_PIXPLDSIZ_PIXPLDSIZ_POS);
    temp |= (VidCfg->PixelPayloadSize << VID_PIXPLDSIZ_PIXPLDSIZ_POS);
    hdsi->Instance->VID_PIXPLDSIZ = temp;

    temp = hdsi->Instance->VID_PIXALIGN;
    temp &= ~(VID_PIXALIGN_PIXALIGN << VID_PIXALIGN_PIXALIGN_POS);
    temp |= (VidCfg->PixelAlignment << VID_PIXALIGN_PIXALIGN_POS);
    hdsi->Instance->VID_PIXALIGN = temp;
    
    temp = hdsi->Instance->VID_PIXFMT;
    temp &= ~(VID_PIXFMT_PIXFMT << VID_PIXFMT_PIXFMT_POS);
    temp |= (VidCfg->PixelFormat << VID_PIXFMT_PIXFMT_POS);
    hdsi->Instance->VID_PIXFMT = temp;
    
    temp = hdsi->Instance->VID_VSYNCPOL;
    temp &= ~(VID_VSYNCPOL_VSYNCPOL << VID_VSYNCPOL_VSYNCPOL_POS);
    temp |= (VidCfg->VSPolarity << VID_VSYNCPOL_VSYNCPOL_POS);
    hdsi->Instance->VID_VSYNCPOL = temp;
    
    temp = hdsi->Instance->VID_HSYNCPOL;
    temp &= ~(VID_HSYNCPOL_HSYNCPOL << VID_HSYNCPOL_HSYNCPOL_POS);
    temp |= (VidCfg->HSPolarity << VID_HSYNCPOL_HSYNCPOL_POS);
    hdsi->Instance->VID_HSYNCPOL = temp;
    
    temp = hdsi->Instance->VID_VIDEOMOD;
    temp &= ~(VID_VIDEOMOD_VIDEOMOD << VID_VIDEOMOD_VIDEOMOD_POS);
    temp |= (VidCfg->Mode << VID_VIDEOMOD_VIDEOMOD_POS);
    hdsi->Instance->VID_VIDEOMOD = temp;
    
    temp = hdsi->Instance->VID_OVERIDE;
    temp &= ~(VID_OVERIDE_OVERIDE << VID_OVERIDE_OVERIDE_POS);
    temp |= (VidCfg->Override << VID_OVERIDE_OVERIDE_POS);
    hdsi->Instance->VID_OVERIDE = temp;
	
	/* Only Override = 1 need to program timing register, Otherwise, the reset value is maintained */
	if (VidCfg->Override == VID_OVERIDE_OVERIDE)
	{
		temp = hdsi->Instance->VID_HSA;
		temp &= ~(VID_HSA_HSA << VID_HSA_HSA_POS);
		temp |= (VidCfg->HorizontalSyncActive << VID_HSA_HSA_POS);
		hdsi->Instance->VID_HSA = temp;
		
		temp = hdsi->Instance->VID_HBP;
		temp &= ~(VID_HBP_HBP << VID_HBP_HBP_POS);
		temp |= (VidCfg->HorizontalBackPorch << VID_HBP_HBP_POS);
		hdsi->Instance->VID_HBP = temp;
		
		temp = hdsi->Instance->VID_HFP;
		temp &= ~(VID_HFP_HFP << VID_HFP_HFP_POS);
		temp |= (VidCfg->HorizontalFrontPorch << VID_HFP_HFP_POS);
		hdsi->Instance->VID_HFP = temp;
		
		temp = hdsi->Instance->VID_VBP;
		temp &= ~(VID_VBP_VBP << VID_VBP_VBP_POS);
		temp |= (VidCfg->VerticalBackPorch << VID_VBP_VBP_POS);
		hdsi->Instance->VID_VBP = temp;
		
		temp = hdsi->Instance->VID_VFP;
		temp &= ~(VID_VFP_VFP << VID_VFP_VFP_POS);
		temp |= (VidCfg->VerticalFrontPorch << VID_VFP_VFP_POS);
		hdsi->Instance->VID_VFP = temp;
		
		temp = hdsi->Instance->VID_VACT;
		temp &= ~(VID_VACT_VACT << VID_VACT_VACT_POS);
		temp |= (VidCfg->VerticalActive << VID_VACT_VACT_POS);
		hdsi->Instance->VID_VACT = temp;
	}

    temp = hdsi->Instance->VID_STD;
    temp &= ~(VID_STD_STD << VID_STD_STD_POS);
    temp |= (VidCfg->DelayFromStart << VID_STD_STD_POS);
    hdsi->Instance->VID_STD = temp;

    temp = hdsi->Instance->VID_PKTPERLINE;
    temp &= ~(VID_PKTPERLINE_PKTPERLINE << VID_PKTPERLINE_PKTPERLINE_POS);
    temp |= (VidCfg->PacketsPerLine << VID_PKTPERLINE_PKTPERLINE_POS);
    hdsi->Instance->VID_PKTPERLINE = temp;

    temp = hdsi->Instance->VID_BLLPMOD;
    temp &= ~(VID_BLLPMOD_BLLPMOD << VID_BLLPMOD_BLLPMOD_POS);
    temp |= (VidCfg->BLLPMode << VID_BLLPMOD_BLLPMOD_POS);
    hdsi->Instance->VID_BLLPMOD = temp;
    
    temp = hdsi->Instance->VID_NULLPKTBLLP;
    temp &= ~(VID_NULLPKTBLLP_NULLPKTBLLP << VID_NULLPKTBLLP_NULLPKTBLLP_POS);
    temp |= (VidCfg->NULLPacketInBLLP << VID_NULLPKTBLLP_NULLPKTBLLP_POS);
    hdsi->Instance->VID_NULLPKTBLLP = temp;

    temp = hdsi->Instance->VID_VC;
    temp &= ~(VID_VC_VC << VID_VC_VC_POS);
    temp |= (VidCfg->VirtualChannel << VID_VC_VC_POS);
    hdsi->Instance->VID_VC = temp;

    temp = hdsi->Instance->VID_EXTPKTEN;
    temp &= ~(VID_EXTPKTEN_EXTPKTEN << VID_EXTPKTEN_EXTPKTEN_POS);
    temp |= (VidCfg->ExternalPacket << VID_EXTPKTEN_EXTPKTEN_POS);
    hdsi->Instance->VID_EXTPKTEN = temp;

    temp = hdsi->Instance->VID_VSSPLD;
    temp &= ~(VID_VSSPLD_VSSPLD << VID_VSSPLD_VSSPLD_POS);
    temp |= (VidCfg->VerticalSyncStartPayload << VID_VSSPLD_VSSPLD_POS);
    hdsi->Instance->VID_VSSPLD = temp;

    temp = hdsi->Instance->VID_PLDPERPKT;
    temp &= ~(VID_PLDPERPKT_PLLPERPKT << VID_PLDPERPKT_PLLPERPKT_POS);
    temp |= (VidCfg->PayloadPerPacket << VID_PLDPERPKT_PLLPERPKT_POS);
    hdsi->Instance->VID_PLDPERPKT = temp;

    hdsi->Instance->VID_EN |= VID_EN_EN;

    /* Process unlocked */
    hdsi->Lock = DSI_UNLOCKED;

    return DSI_OK;
}

/**
*\*\name    DSI_ConfigTimeout.
*\*\fun     Configure DSI host timeout parameters.
*\*\param   hdsi: dsi host instance.
*\*\param   hstxcnt: 0~0xFFFFFF, Hight speed TX timeout count.
*\*\param   lprxcnt: 0~0xFFFFFF, Low power RX timeout count.
*\*\param   btacnt:  0~0xFFFFFF, Bus turn around timeout count.
*\*\return  DSI_OK.
**/
DSI_StateTypeDef DSI_ConfigTimeout(DSI_HandleTypeDef *hdsi, uint32_t hstxcnt, uint32_t lprxcnt, uint32_t btacnt)
{
    /* Process locked */
    hdsi->Lock = DSI_LOCKED;

    hdsi->Instance->DSI_HSTXTOCNT = hstxcnt;
    hdsi->Instance->DSI_LRXTOCNT = lprxcnt;
    hdsi->Instance->DSI_BTATOCNT = btacnt;
    
    /* Process unlocked */
    hdsi->Lock = DSI_UNLOCKED;

    return DSI_OK;
}

/**
*\*\name    DSI_APBPKT_ShortWrite.
*\*\fun     write short DCS or short Generic command.
*\*\param   hdsi: dsi host instance.
*\*\param   ChannelID: Virtual channel ID.
*\*\param   Mode: DSI short packet data type.
*\*\              - DSI_DCS_SHORT_PKT_WRITE_P0
*\*\              - DSI_DCS_SHORT_PKT_WRITE_P1
*\*\              - DSI_GEN_SHORT_PKT_WRITE_P0
*\*\              - DSI_GEN_SHORT_PKT_WRITE_P1
*\*\              - DSI_GEN_SHORT_PKT_WRITE_P2
*\*\param   Speed: DSI short packet speed.
*\*\              - DSI_MODE_LPDT
*\*\              - DSI_MODE_HSDT
*\*\param   Param1: DSC command or first generic parameter.
*\*\param   Param2: DSC parameter or second generic parameter.
*\*\return  none
**/
DSI_StateTypeDef DSI_APBPKT_ShortWrite(DSI_HandleTypeDef *hdsi, uint32_t ChannelID, uint32_t Mode, uint32_t Speed, uint32_t Param1, uint32_t Param2)
{
    DSI_StateTypeDef status;
    DSI_PKTCtrlTypeDef PacketCtrl;

    /* Process locked */
    hdsi->Lock = DSI_LOCKED;

    PacketCtrl.IsBTAEnable = 0;
    PacketCtrl.IsBTAOnly = 0;
    PacketCtrl.CmdType = Speed;
    PacketCtrl.Header.ChannelID = ChannelID;
    PacketCtrl.Header.DataType = Mode;
    PacketCtrl.Header.WordCount = (Param2 << 8U | (Param1 & 0xff));

    status = DSI_ShortWrite(hdsi, PacketCtrl);
    
    /* Process unlocked */
    hdsi->Lock = DSI_UNLOCKED;

    return status;
}

/**
*\*\name    DSI_ShortWrite.
*\*\fun     write short DCS or short Generic command.
*\*\param   hdsi: dsi host instance.
*\*\param   PacketCtrl: Pointer to parameter DSI_PKTCtrlType struct.
*\*\return  DSI_State
**/
static DSI_StateTypeDef DSI_ShortWrite(DSI_HandleTypeDef *hdsi, DSI_PKTCtrlTypeDef PacketCtrl)
{
    uint32_t timeout = DSI_TIME_OUT_VALUE;
    // wait for DPHY direction is tx
    while(((hdsi->Instance->DSI_PKTSTS & DSI_PKTSTS_DPHYDIR) == DSI_PKTSTS_DPHYDIR) && timeout--);
     
    if(timeout == 0xFFFFFFFF)
    {
        return DSI_TIMEOUT;
    }
    /* Configure the packet to send a short DCS command with 0 or 1 parameter */
    /* Update the DSI packet header with new information */
    // write the TX packet header values into the register
    hdsi->Instance->DSI_PKTCTRL = ((PacketCtrl.IsBTAOnly << 26U) | (PacketCtrl.IsBTAEnable << 25U) | (PacketCtrl.CmdType << 24U) | \
                                       (PacketCtrl.Header.DataType << 18U) | (PacketCtrl.Header.ChannelID << 16U) | (PacketCtrl.Header.WordCount));
         
    // set TX send enable
    hdsi->Instance->DSI_SENDPKT = DSI_SENDPKT_SENDPKT;

    timeout = DSI_TIME_OUT_VALUE;
    // wait until tx done
    if(PacketCtrl.IsBTAEnable == 0)  
    {
        // write wait for not idle
        while(((hdsi->Instance->DSI_PKTSTS & DSI_PKTSTS_NIDLE) == DSI_PKTSTS_NIDLE) && timeout--)
        {
        }
        if(timeout == 0xFFFFFFFF)
        {
            return DSI_TIMEOUT;
        }
    }
    return DSI_OK;
}

/**
*\*\name    DSI_APBPKT_LongWrite.
*\*\fun     write long DCS or long Generic command
*\*\param   hdsi: dsi host instance.
*\*\param   ChannelID: Virtual channel ID.
*\*\param   Mode: DSI short packet data type.
*\*\              - DSI_DCS_LONG_PKT_WRITE
*\*\              - DSI_GEN_LONG_PKT_WRITE
*\*\param   Speed: DSI short packet speed.
*\*\              - DSI_MODE_LPDT
*\*\              - DSI_MODE_HSDT
*\*\param   ParametersTable: Pointer to parameter values table.
*\*\param   NbParams: Number of parameters.
*\*\return  DSI_State
**/
DSI_StateTypeDef DSI_APBPKT_LongWrite(DSI_HandleTypeDef *hdsi, uint32_t ChannelID, uint32_t Mode, uint32_t Speed, uint8_t *ParametersTable, uint32_t NbParams)
{
    DSI_StateTypeDef status;
    DSI_PKTCtrlTypeDef PacketCtrl;

    /* Process locked */
    hdsi->Lock = DSI_LOCKED;

    PacketCtrl.IsBTAEnable = 0;
    PacketCtrl.IsBTAOnly   = 0;
    PacketCtrl.CmdType     = Speed; 
        
    PacketCtrl.Header.ChannelID = ChannelID;
    PacketCtrl.Header.DataType  = Mode;
    PacketCtrl.Header.WordCount = NbParams;

    status = DSI_LongWrite(hdsi, PacketCtrl, ParametersTable);

    /* Process unlocked */
    hdsi->Lock = DSI_UNLOCKED;

    return status;
}

/**
*\*\name    DSI_LongWrite.
*\*\fun     write long DCS or long Generic command
*\*\param   hdsi: dsi host instance.
*\*\param   PacketCtrl: Pointer to parameter DSI_PKTCtrlType struct.
*\*\param   ParametersTable: Pointer to parameter values table.
*\*\return  DSI_State
**/
DSI_StateTypeDef DSI_LongWrite(DSI_HandleTypeDef *hdsi, DSI_PKTCtrlTypeDef PacketCtrl, uint8_t *ParametersTable)
{
    uint32_t uicounter;
    uint32_t indexBytes;
    uint32_t count;
    uint32_t fifoword;
    uint8_t *pparams = ParametersTable;
    uint32_t timeout = DSI_TIME_OUT_VALUE;
    uint8_t longpacket_byte[100] = {0};
    uint32_t longpacket_fifo[100] = {0};

    // wait for DPHY direction is tx
    while(((hdsi->Instance->DSI_PKTSTS & DSI_PKTSTS_DPHYDIR) == DSI_PKTSTS_DPHYDIR) && timeout--);

    if(timeout == 0xFFFFFFFF)
    {
        return DSI_TIMEOUT;
    }
    /* Configure the packet to send a long DCS command */
    // write the TX packet header values into the register
    hdsi->Instance->DSI_PKTCTRL = ((PacketCtrl.IsBTAOnly << 26U) | (PacketCtrl.IsBTAEnable << 25U) | (PacketCtrl.CmdType << 24U) | \
                       (PacketCtrl.Header.DataType << 18U) | (PacketCtrl.Header.ChannelID << 16U) | (PacketCtrl.Header.WordCount));

    for(uint16_t i = 0; i < PacketCtrl.Header.WordCount; i++ )
    {
        longpacket_byte[i] = *pparams;
        pparams += 4;
    }
    // write the payload data
    uicounter = (PacketCtrl.Header.WordCount + 3) / 4;
    for (count = 0U; count < uicounter ; ++count)
    {
        indexBytes = count * 4;
        fifoword = 0;
        if(indexBytes < PacketCtrl.Header.WordCount)
        {
            fifoword |= (uint32_t)(longpacket_byte[indexBytes]) << 0;
        }
        if((indexBytes + 1) < PacketCtrl.Header.WordCount)
        {
            fifoword |= ((uint32_t)(longpacket_byte[indexBytes + 1]) << 8);
        }
        if((indexBytes + 2) < PacketCtrl.Header.WordCount)
        {
            fifoword |= ((uint32_t)(longpacket_byte[indexBytes + 2]) << 16);
        }
        if((indexBytes + 3) < PacketCtrl.Header.WordCount)
        {
            fifoword |= ((uint32_t)(longpacket_byte[indexBytes + 3]) << 24);
        }

        longpacket_fifo[count] = fifoword;
    }
    for(uint16_t i = 0; i < uicounter; i++)
    {
        hdsi->Instance->DSI_TXPLD = longpacket_fifo[i];
    }
    // set TX send enable
    hdsi->Instance->DSI_SENDPKT = DSI_SENDPKT_SENDPKT;
    
    timeout = DSI_TIME_OUT_VALUE;
    // wait until tx done
    while(((hdsi->Instance->DSI_PKTSTS & DSI_PKTSTS_TXD) == DSI_PKTSTS_TXD) && timeout--)
    {
    }
    if(timeout == 0xFFFFFFFF)
    {
        return DSI_TIMEOUT;
    }
    return DSI_OK;
}

/**
*\*\name    DSI_APBPKT_Read.
*\*\fun     Read command (DCS or generic)
*\*\param   hdsi: dsi host instance.
*\*\param   ChannelNbr: Virtual channel ID.
*\*\param   Array: Array pointer to a buffer to store the payload of a read back operation.
*\*\param   Size: Data size to be read (in byte).
*\*\param   Mode: DSI short packet data type.
*\*\              - DSI_DCS_SHORT_PKT_READ
*\*\              - DSI_GEN_SHORT_PKT_READ_P0
*\*\              - DSI_GEN_SHORT_PKT_READ_P1
*\*\              - DSI_GEN_SHORT_PKT_READ_P2
*\*\param   DCSCmd: DCS get/read command.
*\*\param   ParametersTable: Pointer to parameter values table.
*\*\return  DSI_State
**/
DSI_StateTypeDef DSI_APBPKT_Read(DSI_HandleTypeDef *hdsi, uint32_t ChannelNbr, uint8_t *Array, uint32_t Size, uint32_t Mode, uint32_t DCSCmd, uint8_t *ParametersTable)
{
    uint32_t datasize = Size;

    DSI_PKTCtrlTypeDef PacketCtrl;
    DSI_StateTypeDef status;

    /* Process locked */
    hdsi->Lock = DSI_LOCKED;

    /* Check the parameters */
    assert_param(IS_DSI_READ_PACKET_TYPE(Mode));

    if (datasize > 2U)
    {
        /* step1: set max return packet size */
        if (DSI_APBPKT_ShortWrite(hdsi, ChannelNbr, DSI_MAX_RETURN_PKT_SIZE, DSI_MODE_LPDT, ((datasize) & 0xFFU), (((datasize) >> 8U) & 0xFFU)) != DSI_OK)
        {
            /* Process Unlocked */
            hdsi->Lock = DSI_UNLOCKED;
            return DSI_ERROR;
        }
    }

    /* step2: send read cmd */
    PacketCtrl.IsBTAEnable = 1;    
    PacketCtrl.IsBTAOnly = 0;
    PacketCtrl.CmdType = DSI_MODE_LPDT;

    PacketCtrl.Header.ChannelID = ChannelNbr;
    PacketCtrl.Header.DataType = Mode;

    /* step3: dsi rx secondly*/
    if (Mode == DSI_DCS_SHORT_PKT_READ)
    {
        //levan, cmd need to be in the data 0
        PacketCtrl.Header.WordCount = (0x0 << 8U | (DCSCmd & 0xff));
        status = DSI_ShortWrite(hdsi, PacketCtrl);
    }
    else if (Mode == DSI_GEN_SHORT_PKT_READ_P0)
    {
        PacketCtrl.Header.WordCount = 0;
        status = DSI_ShortWrite(hdsi, PacketCtrl);
    }
    else if (Mode == DSI_GEN_SHORT_PKT_READ_P1)
    {
        PacketCtrl.Header.WordCount = DCSCmd << 8U;
        status = DSI_ShortWrite(hdsi, PacketCtrl);
        PacketCtrl.Header.DataType = DSI_EOTP;
        PacketCtrl.Header.WordCount = (0x0f << 8U | 0x0f);
        PacketCtrl.IsBTAEnable = 1;    
        status = DSI_ShortWrite(hdsi, PacketCtrl);
    }
    else if (Mode == DSI_GEN_SHORT_PKT_READ_P2)
    {
        PacketCtrl.Header.WordCount = (DCSCmd << 8U | ParametersTable[0U]);
        status = DSI_ShortWrite(hdsi, PacketCtrl);
    }
    else
    {
        /* Process Unlocked */
        hdsi->Lock = DSI_UNLOCKED;
        return DSI_ERROR;
    }
    /* step4: dsi rx */
    status = DSI_Read(hdsi, (uint8_t *)Array, Size);
    /* Process unlocked */
    hdsi->Lock = DSI_UNLOCKED;
    
    return status;
}

/**
*\*\name    DSI_APBPKT_Read_BTA.
*\*\fun     Read command (DCS or generic)
*\*\param   hdsi: dsi host instance.
*\*\param   ChannelNbr: Virtual channel ID.
*\*\param   Array: Array pointer to a buffer to store the payload of a read back operation.
*\*\param   Size: Data size to be read (in byte).
*\*\param   Mode: DSI short packet data type.
*\*\              - DSI_DCS_SHORT_PKT_READ
*\*\              - DSI_GEN_SHORT_PKT_READ_P0
*\*\              - DSI_GEN_SHORT_PKT_READ_P1
*\*\              - DSI_GEN_SHORT_PKT_READ_P2
*\*\return  DSI_State
**/
DSI_StateTypeDef DSI_APBPKT_Read_BTA(DSI_HandleTypeDef *hdsi, uint32_t ChannelNbr, uint8_t *Array, uint32_t Size, uint32_t Mode)
{
    uint32_t datasize = Size;

    DSI_PKTCtrlTypeDef PacketCtrl;
    DSI_StateTypeDef status;

    /* Process locked */
    hdsi->Lock = DSI_LOCKED;

    if (datasize > 2U)
    {
        /* step1: set max return packet size */
        if (DSI_APBPKT_ShortWrite(hdsi, ChannelNbr, DSI_MAX_RETURN_PKT_SIZE, DSI_MODE_LPDT, ((datasize) & 0xFFU), (((datasize) >> 8U) & 0xFFU)) != DSI_OK)
        {
            /* Process Unlocked */
            hdsi->Lock = DSI_UNLOCKED;
            return DSI_ERROR;
        }
    }

    /* step2: send read cmd */
    PacketCtrl.IsBTAEnable = 0;
    PacketCtrl.IsBTAOnly = 1;
    PacketCtrl.CmdType = DSI_MODE_LPDT;

    PacketCtrl.Header.ChannelID = ChannelNbr;
    PacketCtrl.Header.DataType = Mode;

    /* step3: dsi rx secondly*/
    PacketCtrl.Header.WordCount = 0;
    status = DSI_ShortWrite(hdsi, PacketCtrl);

    /* step4: dsi rx */
    status = DSI_Read(hdsi, (uint8_t *)Array, Size);
    /* Process unlocked */
    hdsi->Lock = DSI_UNLOCKED;
    
    return status;
}

/**
*\*\name    DSI_Read.
*\*\fun     DSI Read data
*\*\param   hdsi: dsi host instance.
*\*\param   RxArray: Array pointer to a buffer to store the payload of a read back operation.
*\*\param   RxSize: Data size to be read (in byte).
*\*\return  DSI_State
**/
DSI_StateTypeDef DSI_Read(DSI_HandleTypeDef *hdsi, uint8_t *RxArray, uint32_t RxSize)
{
    uint8_t *pdata = RxArray;
    uint32_t timeout = DSI_TIME_OUT_VALUE;
    DSI_PKTHeaderTypeDef RxPKTHeader;

    //levan, wait until packet header has been received
    while(((hdsi->Instance->DSI_PKTSTS & DSI_PKTSTS_RXPKTD) != DSI_PKTSTS_RXPKTD) && timeout--)
    {}
    if(timeout == 0xFFFFFFFF)
    {
        return DSI_TIMEOUT;
    }
    //then proceed with
    // read rx packet header
    RxPKTHeader.WordCount = hdsi->Instance->DSI_PKTRXHDR & 0x0000ffff;
    RxPKTHeader.DataType  = (hdsi->Instance->DSI_PKTRXHDR >> 16) & 0x3f;
    RxPKTHeader.ChannelID = (hdsi->Instance->DSI_PKTRXHDR >> 22) & 0x03;
    //levan added, for short packet, TODO for long packet
    *pdata = (uint8_t) RxPKTHeader.WordCount & 0x00ff;
    pdata++;
    *pdata = (uint8_t) RxPKTHeader.WordCount>>8 & 0x00ff;
    return DSI_OK;
}



/**
*\*\name    DSI_GetSTS
*\*\fun     Get DSI flag status.
*\*\param   hdsi: dsi host instance.
*\*\param   DSI_FLAG (The input parameters must be the following values):
*\*\          - DSI_FLAG_SOT_ERROR
*\*\          - DSI_FLAG_SOTSYNC_ERROR
*\*\          - DSI_FLAG_EOTSYNC_ERROR
*\*\          - DSI_FLAG_ESCMOD_ERROR
*\*\          - DSI_FLAG_LPTXSYNC_ERROR
*\*\          - DSI_FLAG_TO_ERROR
*\*\          - DSI_FLAG_FCTRL_ERROR
*\*\          - DSI_FLAG_COTDET_ERROR
*\*\          - DSI_FLAG_ECCSB_ERROR
*\*\          - DSI_FLAG_ECCML_ERROR
*\*\          - DSI_FLAG_CRC_ERROR
*\*\          - DSI_FLAG_DATATYPE_ERROR
*\*\          - DSI_FLAG_VCIDINVLID_ERROR
*\*\          - DSI_FLAG_INVLID_TXLEN_ERROR
*\*\          - DSI_FLAG_PROVILT_ERROR
*\*\          - DSI_FLAG_BIT0_ERROR
*\*\          - DSI_FLAG_BIT1_ERROR
*\*\          - DSI_FLAG_BIT2_ERROR
*\*\          - DSI_FLAG_BIT3_ERROR
*\*\return  bitstatus
*\*\          - SET   
*\*\          - RESET 
**/
FlagStatus DSI_GetSTS(DSI_HandleTypeDef *hdsi, uint32_t DSI_FLAG)
{
    FlagStatus bitstatus;
    
    /* Process locked */
    hdsi->Lock = DSI_LOCKED;

    if ((hdsi->Instance->DSI_STS & DSI_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    /* Process unlocked */
    hdsi->Lock = DSI_UNLOCKED;
    
    return bitstatus;
}

/**
*\*\name    DSI_GetERRSTS
*\*\fun     Get DSI error flag status.
*\*\param   hdsi: dsi host instance.
*\*\param   DSI_FLAG (The input parameters must be the following values):
*\*\          - DSI_ERROR_FLAG_ECCSB
*\*\          - DSI_ERROR_FLAG_ECCML
*\*\          - DSI_ERROR_FLAG_CRC  
*\*\          - DSI_ERROR_FLAG_HTXTO
*\*\          - DSI_ERROR_FLAG_LRXTO
*\*\          - DSI_ERROR_FLAG_BATTO
*\*\return  bitstatus
*\*\          - SET   
*\*\          - RESET 
**/
FlagStatus DSI_GetERRSTS(DSI_HandleTypeDef *hdsi, uint32_t DSI_FLAG)
{
    FlagStatus bitstatus;
    
    /* Process locked */
    hdsi->Lock = DSI_LOCKED;

    if ((hdsi->Instance->DSI_ERRSTS & DSI_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    /* Process unlocked */
    hdsi->Lock = DSI_UNLOCKED;
    
    return bitstatus;
}

/**
*\*\name    DSI_GetPKTSTS
*\*\fun     Get DSI packet flag status.
*\*\param   hdsi: dsi host instance.
*\*\param   DSI_FLAG (The input parameters must be the following values):
*\*\          - DSI_PKT_FLAG_NIDLE    
*\*\          - DSI_PKT_FLAG_TXD      
*\*\          - DSI_PKT_FLAG_DPHYDIR  
*\*\          - DSI_PKT_FLAG_TXFOVER  
*\*\          - DSI_PKT_FLAG_TXFUNDER 
*\*\          - DSI_PKT_FLAG_RXFOVER  
*\*\          - DSI_PKT_FLAG_RXFUNDER 
*\*\          - DSI_PKT_FLAG_RXPKTD   
*\*\          - DSI_PKT_FLAG_ALLRXPKTD
*\*\return  bitstatus
*\*\          - SET   
*\*\          - RESET 
**/
FlagStatus DSI_GetPKTSTS(DSI_HandleTypeDef *hdsi, uint32_t DSI_FLAG)
{
    FlagStatus bitstatus;
    
    /* Process locked */
    hdsi->Lock = DSI_LOCKED;

    if ((hdsi->Instance->DSI_STS & DSI_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    /* Process unlocked */
    hdsi->Lock = DSI_UNLOCKED;
    
    return bitstatus;
}
