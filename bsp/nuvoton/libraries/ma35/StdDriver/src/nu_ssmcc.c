/**************************************************************************//**
 * @file     ssmcc.c
 * @brief    SSMCC driver source file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "NuMicro.h"


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup SSMCC_Driver SSMCC Driver
  @{
*/

/** @addtogroup SSMCC_EXPORTED_FUNCTIONS SSMCC Exported Functions
  @{
*/

/**
  * @brief  Set TZC Region0.
  * @param[in] u32Attr is security attribute for all region 0.
  * @return none
  * @details
  * SSMCC::TZC0:Ch0   CA35, AXI-AP
  * SSMCC::TZC0:Ch1   GFX, VC8000
  * SSMCC::TZC0:Ch2   DCUltra
  * SSMCC::TZC0:Ch3   GMAC0, GMAC1
  * SSMCC::TZC2:Ch0   CCAP0, CCAP1
  * SSMCC::TZC2:Ch1   CM4
  *                   PDMA0, PDMA1, PDMA2, PDMA3
  *                   SDH0, SDH1
  *                   HSUSBH0, HSUSBH1, USBH0, USBH1, USBH2
  *                   HSUSBD, NFI
  * SSMCC::TZC2:Ch2   CRYPTO
  * \hideinitializer
  */
#define TZC0_CH_NUM 4
#define TZC2_CH_NUM 3

void SSMCC_SetRegion0(uint32_t u32Attr)
{
    /* Enable SSMCC clock */
    CLK->APBCLK2 |= CLK_APBCLK2_SSMCCEN_Msk;

    /* Enable IP clocks on channels. */
    CLK->CLKSEL0 |= CLK_CLKSEL0_SYSCK0SEL_SYSPLL;

    CLK->SYSCLK0 |= (CLK_SYSCLK0_CCAP1EN_Msk |
                     CLK_SYSCLK0_CCAP0EN_Msk |
                     CLK_SYSCLK0_GMAC1EN_Msk |
                     CLK_SYSCLK0_GMAC0EN_Msk |
                     CLK_SYSCLK0_DCUEN_Msk |
                     CLK_SYSCLK0_VDECEN_Msk |
                     CLK_SYSCLK0_GFXEN_Msk |
                     CLK_SYSCLK0_HUSBH1EN_Msk |
                     CLK_SYSCLK0_HUSBH0EN_Msk |
                     CLK_SYSCLK0_USBHEN_Msk |
                     CLK_SYSCLK0_USBDEN_Msk |
                     CLK_SYSCLK0_NANDEN_Msk |
                     CLK_SYSCLK0_SDH1EN_Msk |
                     CLK_SYSCLK0_SDH0EN_Msk);

    /* Set region 0 secure attribute */
    TZC0->REGION[SSMCC_REGION_0].ATTRIBUTES = u32Attr & (TZC_REGION_ATTRIBUTES_s_rd_en_Msk | TZC_REGION_ATTRIBUTES_s_wr_en_Msk);
    TZC0->GATE_KEEPER = (1 << TZC0_CH_NUM) - 1; /* CH[0, 1, 2, 3] used, filter mask is 0xF */
    TZC2->REGION[SSMCC_REGION_0].ATTRIBUTES = u32Attr & (TZC_REGION_ATTRIBUTES_s_rd_en_Msk | TZC_REGION_ATTRIBUTES_s_wr_en_Msk);
    TZC2->GATE_KEEPER = (1 << TZC2_CH_NUM) - 1; /* CH[0, 1, 2] used, filter mask is 0x7 */

    while (1)
    {
        if (((TZC0->GATE_KEEPER & TZC_GATE_KEEPER_open_status_Msk) == (((1 << TZC0_CH_NUM) - 1) << TZC_GATE_KEEPER_open_status_Pos))
                && ((TZC2->GATE_KEEPER & TZC_GATE_KEEPER_open_status_Msk) == (((1 << TZC2_CH_NUM) - 1) << TZC_GATE_KEEPER_open_status_Pos)))
        {
            break;
        }
    }

    /* set region 0 non-secure attribute */
    TZC0->REGION[SSMCC_REGION_0].ID_ACCESS = u32Attr & 0x00010001;
    TZC2->REGION[SSMCC_REGION_0].ID_ACCESS = u32Attr & 0x00030003;

    CLK->SYSCLK0 &= ~(CLK_SYSCLK0_CCAP1EN_Msk |
                      CLK_SYSCLK0_CCAP0EN_Msk |
                      CLK_SYSCLK0_GMAC1EN_Msk |
                      CLK_SYSCLK0_GMAC0EN_Msk |
                      CLK_SYSCLK0_DCUEN_Msk |
                      CLK_SYSCLK0_VDECEN_Msk |
                      CLK_SYSCLK0_GFXEN_Msk |
                      CLK_SYSCLK0_HUSBH1EN_Msk |
                      CLK_SYSCLK0_HUSBH0EN_Msk |
                      CLK_SYSCLK0_USBHEN_Msk |
                      CLK_SYSCLK0_USBDEN_Msk |
                      CLK_SYSCLK0_NANDEN_Msk |
                      CLK_SYSCLK0_SDH1EN_Msk |
                      CLK_SYSCLK0_SDH0EN_Msk);

    //CLK->CLKSEL0 &= ~CLK_CLKSEL0_SYSCK0SEL_Msk;
}

/**
  * @brief  Set TZC Regions.
  * @param[in] psParam is structure pointer of SSMCC parameter.
  * @return none
  * @details
  * \hideinitializer
  */
void SSMCC_SetRegion(SSMCC_PARAM_T *psParam)
{
    if (psParam &&
            psParam->region_no != SSMCC_REGION_0)
    {
        TZC0->REGION[psParam->region_no].BASE_LOW   = psParam->base_address;
        TZC0->REGION[psParam->region_no].TOP_LOW    = psParam->base_address + psParam->size - 1;
        TZC0->REGION[psParam->region_no].ATTRIBUTES = ((1 << TZC0_CH_NUM) - 1) | (psParam->attribute & (TZC_REGION_ATTRIBUTES_s_rd_en_Msk | TZC_REGION_ATTRIBUTES_s_wr_en_Msk));
        TZC0->REGION[psParam->region_no].ID_ACCESS  = psParam->attribute & 0x00010001;

        TZC2->REGION[psParam->region_no].BASE_LOW   = psParam->base_address;
        TZC2->REGION[psParam->region_no].TOP_LOW    = psParam->base_address + psParam->size - 1;
        TZC2->REGION[psParam->region_no].ATTRIBUTES = ((1 << TZC2_CH_NUM) - 1) | (psParam->attribute & (TZC_REGION_ATTRIBUTES_s_rd_en_Msk | TZC_REGION_ATTRIBUTES_s_wr_en_Msk));
        TZC2->REGION[psParam->region_no].ID_ACCESS  = psParam->attribute & 0x00030003;
    }
}

/*@}*/ /* end of group SSMCC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group SSMCC_Driver */

/*@}*/ /* end of group Standard_Driver */

