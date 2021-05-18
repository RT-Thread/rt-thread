/**************************************************************************//**
 * @file     tamper.c
 * @version  V3.00
 * @brief    M2354 series TAMPER driver source file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include "NuMicro.h"

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup TAMPER_Driver Tamper Driver
  @{
*/

/** @addtogroup TAMPER_EXPORTED_FUNCTIONS Tamper Exported Functions
  @{
*/

/**
  * @brief      Enable Tamper Interrupt
  *
  * @param[in]  u32IntFlagMask      Specify the interrupt source. It consists of:
  *                                 - \ref TAMPER_INTEN_TAMP0IEN_Msk
  *                                 - \ref TAMPER_INTEN_TAMP1IEN_Msk
  *                                 - \ref TAMPER_INTEN_TAMP2IEN_Msk
  *                                 - \ref TAMPER_INTEN_TAMP3IEN_Msk
  *                                 - \ref TAMPER_INTEN_TAMP4IEN_Msk
  *                                 - \ref TAMPER_INTEN_TAMP5IEN_Msk
  *                                 - \ref TAMPER_INTEN_CLKFIEN_Msk
  *                                 - \ref TAMPER_INTEN_CLKSTOPIEN_Msk
  *                                 - \ref TAMPER_INTEN_OVPIEN_Msk
  *                                 - \ref TAMPER_INTEN_VGPIEN_Msk
  *                                 - \ref TAMPER_INTEN_VGNIEN_Msk
  *                                 - \ref TAMPER_INTEN_ACTSIEN_Msk
  *                                 - \ref TAMPER_INTEN_RTCLVRIEN_Msk
  *                                 - \ref TAMPER_INTEN_RTCIOIEN_Msk
  *                                 - \ref TAMPER_INTEN_RTCLKIEN_Msk
  *                                 - \ref TAMPER_INTEN_BODIEN_Msk
  *
  * @return     None
  *
  * @details    This API is used to enable the specify tamper interrupt function.
  */
void TAMPER_EnableInt(uint32_t u32IntFlagMask)
{
    TAMPER->INTEN |= u32IntFlagMask;
}

/**
  * @brief      Disable Tamper Interrupt
  *
  * @param[in]  u32IntFlagMask      Specify the interrupt source. It consists of:
  *                                 - \ref TAMPER_INTEN_TAMP0IEN_Msk
  *                                 - \ref TAMPER_INTEN_TAMP1IEN_Msk
  *                                 - \ref TAMPER_INTEN_TAMP2IEN_Msk
  *                                 - \ref TAMPER_INTEN_TAMP3IEN_Msk
  *                                 - \ref TAMPER_INTEN_TAMP4IEN_Msk
  *                                 - \ref TAMPER_INTEN_TAMP5IEN_Msk
  *                                 - \ref TAMPER_INTEN_CLKFIEN_Msk
  *                                 - \ref TAMPER_INTEN_CLKSTOPIEN_Msk
  *                                 - \ref TAMPER_INTEN_OVPIEN_Msk
  *                                 - \ref TAMPER_INTEN_VGPIEN_Msk
  *                                 - \ref TAMPER_INTEN_VGNIEN_Msk
  *                                 - \ref TAMPER_INTEN_ACTSIEN_Msk
  *                                 - \ref TAMPER_INTEN_RTCLVRIEN_Msk
  *                                 - \ref TAMPER_INTEN_RTCIOIEN_Msk
  *                                 - \ref TAMPER_INTEN_RTCLKIEN_Msk
  *                                 - \ref TAMPER_INTEN_BODIEN_Msk
  *
  * @return     None
  *
  * @details    This API is used to disable the specify tamper interrupt function.
  */
void TAMPER_DisableInt(uint32_t u32IntFlagMask)
{
    TAMPER->INTEN &= ~u32IntFlagMask;
}

/**
  * @brief      Static Tamper Detect
  *
  * @param[in]  u32TamperSelect     Tamper pin select. Possible options are
  *                                 - \ref TAMPER_TAMPER0_SELECT
  *                                 - \ref TAMPER_TAMPER1_SELECT
  *                                 - \ref TAMPER_TAMPER2_SELECT
  *                                 - \ref TAMPER_TAMPER3_SELECT
  *                                 - \ref TAMPER_TAMPER4_SELECT
  *                                 - \ref TAMPER_TAMPER5_SELECT
  *
  * @param[in]  u32DetecLevel       Tamper pin detection level select. Possible options are
  *                                 - \ref TAMPER_TAMPER_HIGH_LEVEL_DETECT
  *                                 - \ref TAMPER_TAMPER_LOW_LEVEL_DETECT
  *
  * @param[in]  u32DebounceEn       Tamper pin de-bounce enable
  *                                 - \ref TAMPER_TAMPER_DEBOUNCE_ENABLE
  *                                 - \ref TAMPER_TAMPER_DEBOUNCE_DISABLE
  *
  * @return     None
  *
  * @details    This API is used to enable the tamper pin detect function with specify trigger condition.
  *             User needs to disable dynamic tamper function before use this API.
  */
void TAMPER_StaticTamperEnable(uint32_t u32TamperSelect, uint32_t u32DetecLevel, uint32_t u32DebounceEn)
{
    uint32_t i;
    uint32_t u32Reg;
    uint32_t u32TmpReg;

    u32Reg = TAMPER->TIOCTL;

    u32TmpReg = (TAMPER_TIOCTL_TAMP0EN_Msk | (u32DetecLevel << TAMPER_TIOCTL_TAMP0LV_Pos) |
                 (u32DebounceEn << TAMPER_TIOCTL_TAMP0DBEN_Pos));

    for(i = 0UL; i < (uint32_t)TAMPER_MAX_TAMPER_PIN_NUM; i++)
    {
        if(u32TamperSelect & (0x1UL << i))
        {
            u32Reg &= ~((TAMPER_TIOCTL_TAMP0EN_Msk | TAMPER_TIOCTL_TAMP0LV_Msk | TAMPER_TIOCTL_TAMP0DBEN_Msk) << (i * 4UL));
            u32Reg |= (u32TmpReg << (i * 4UL));
        }
    }

    TAMPER->TIOCTL = u32Reg;
}

/**
  * @brief      Static Tamper Disable
  *
  * @param[in]  u32TamperSelect     Tamper pin select. Possible options are
  *                                 - \ref TAMPER_TAMPER0_SELECT
  *                                 - \ref TAMPER_TAMPER1_SELECT
  *                                 - \ref TAMPER_TAMPER2_SELECT
  *                                 - \ref TAMPER_TAMPER3_SELECT
  *                                 - \ref TAMPER_TAMPER4_SELECT
  *                                 - \ref TAMPER_TAMPER5_SELECT
  *
  * @return     None
  *
  * @details    This API is used to disable the static tamper pin detect.
  */
void TAMPER_StaticTamperDisable(uint32_t u32TamperSelect)
{
    uint32_t i;
    uint32_t u32Reg;
    uint32_t u32TmpReg;

    u32Reg = TAMPER->TIOCTL;

    u32TmpReg = TAMPER_TIOCTL_TAMP0EN_Msk;

    for(i = 0UL; i < (uint32_t)TAMPER_MAX_TAMPER_PIN_NUM; i++)
    {
        if(u32TamperSelect & (0x1UL << i))
        {
            u32Reg &= ~(u32TmpReg << (i * 4UL));
        }
    }

    TAMPER->TIOCTL = u32Reg;
}

/**
  * @brief      Dynamic Tamper Detect
  *
  * @param[in]  u32PairSel          Tamper pin detection enable. Possible options are
  *                                 - \ref TAMPER_PAIR0_SELECT
  *                                 - \ref TAMPER_PAIR1_SELECT
  *                                 - \ref TAMPER_PAIR2_SELECT
  *
  * @param[in]  u32DebounceEn       Tamper pin de-bounce enable
  *                                 - \ref TAMPER_TAMPER_DEBOUNCE_ENABLE
  *                                 - \ref TAMPER_TAMPER_DEBOUNCE_DISABLE
  *
  *  @param[in]  u32Pair1Source     Dynamic pair 1 input source select
  *                                 0: Pair 1 source select tamper 2
  *                                 1: Pair 1 source select tamper 0
  *
  *  @param[in]  u32Pair2Source     Dynamic pair 2 input source select
  *                                 0: Pair 2 source select tamper 4
  *                                 1: Pair 2 source select tamper 0
  *
  * @return     None
  *
  * @details    This API is used to enable the dynamic tamper.
  */
void TAMPER_DynamicTamperEnable(uint32_t u32PairSel, uint32_t u32DebounceEn, uint32_t u32Pair1Source, uint32_t u32Pair2Source)
{
    uint32_t i;
    uint32_t u32Reg;
    uint32_t u32TmpReg;
    uint32_t u32Tamper2Debounce, u32Tamper4Debounce;

    u32Reg = TAMPER->TIOCTL;
    u32Reg &= ~(TAMPER_TIOCTL_TAMP0EN_Msk | TAMPER_TIOCTL_TAMP1EN_Msk | TAMPER_TIOCTL_TAMP2EN_Msk |
                TAMPER_TIOCTL_TAMP3EN_Msk | TAMPER_TIOCTL_TAMP4EN_Msk | TAMPER_TIOCTL_TAMP5EN_Msk);

    u32Tamper2Debounce = u32Reg & TAMPER_TIOCTL_TAMP2DBEN_Msk;
    u32Tamper4Debounce = u32Reg & TAMPER_TIOCTL_TAMP4DBEN_Msk;

    u32Reg &= ~(TAMPER_TIOCTL_TAMP0EN_Msk | TAMPER_TIOCTL_TAMP1EN_Msk | TAMPER_TIOCTL_TAMP2EN_Msk |
                TAMPER_TIOCTL_TAMP3EN_Msk | TAMPER_TIOCTL_TAMP4EN_Msk | TAMPER_TIOCTL_TAMP5EN_Msk);
    u32Reg &= ~(TAMPER_TIOCTL_DYN1ISS_Msk | TAMPER_TIOCTL_DYN2ISS_Msk);
    u32Reg |= ((u32Pair1Source & 0x1UL) << TAMPER_TIOCTL_DYN1ISS_Pos) | ((u32Pair2Source & 0x1UL) << TAMPER_TIOCTL_DYN2ISS_Pos);

    if(u32DebounceEn)
    {
        u32TmpReg = (TAMPER_TIOCTL_TAMP0EN_Msk | TAMPER_TIOCTL_TAMP1EN_Msk |
                     TAMPER_TIOCTL_TAMP0DBEN_Msk | TAMPER_TIOCTL_TAMP1DBEN_Msk | TAMPER_TIOCTL_DYNPR0EN_Msk);
    }
    else
    {
        u32TmpReg = (TAMPER_TIOCTL_TAMP0EN_Msk | TAMPER_TIOCTL_TAMP1EN_Msk | TAMPER_TIOCTL_DYNPR0EN_Msk);
    }

    for(i = 0UL; i < (uint32_t)TAMPER_MAX_PAIR_NUM; i++)
    {
        if(u32PairSel & (0x1UL << i))
        {
            u32Reg &= ~((TAMPER_TIOCTL_TAMP0DBEN_Msk | TAMPER_TIOCTL_TAMP1DBEN_Msk) << (i * 8UL));
            u32Reg |= (u32TmpReg << (i * 8UL));
        }
    }

    if((u32Pair1Source) && (u32PairSel & (uint32_t)TAMPER_PAIR1_SELECT))
    {
        u32Reg &= ~TAMPER_TIOCTL_TAMP2EN_Msk;
        u32Reg |= u32Tamper2Debounce;
    }

    if((u32Pair2Source) && (u32PairSel & (uint32_t)TAMPER_PAIR2_SELECT))
    {
        u32Reg &= ~TAMPER_TIOCTL_TAMP4EN_Msk;
        u32Reg |= u32Tamper4Debounce;
    }

    TAMPER->TIOCTL = u32Reg;
}

/**
  * @brief      Dynamic Tamper Disable
  *
  * @param[in]  u32PairSel          Tamper pin detection disable. Possible options are
  *                                 - \ref TAMPER_PAIR0_SELECT
  *                                 - \ref TAMPER_PAIR1_SELECT
  *                                 - \ref TAMPER_PAIR2_SELECT
  *
  * @return     None
  *
  * @details    This API is used to disable the dynamic tamper.
  */
void TAMPER_DynamicTamperDisable(uint32_t u32PairSel)
{
    uint32_t i;
    uint32_t u32Reg;
    uint32_t u32TmpReg;
    uint32_t u32Tamper2En = 0UL, u32Tamper4En = 0UL;

    u32Reg = TAMPER->TIOCTL;

    if((u32Reg & (uint32_t)TAMPER_TIOCTL_DYN1ISS_Msk) && (u32PairSel & (uint32_t)TAMPER_PAIR1_SELECT))
    {
        u32Tamper2En = u32Reg & TAMPER_TIOCTL_TAMP2EN_Msk;
    }

    if((u32Reg & (uint32_t)TAMPER_TIOCTL_DYN2ISS_Msk) && (u32PairSel & (uint32_t)TAMPER_PAIR2_SELECT))
    {
        u32Tamper4En = u32Reg & TAMPER_TIOCTL_TAMP4EN_Msk;
    }

    u32TmpReg = (TAMPER_TIOCTL_TAMP0EN_Msk | TAMPER_TIOCTL_TAMP1EN_Msk | TAMPER_TIOCTL_DYNPR0EN_Msk);

    for(i = 0UL; i < (uint32_t)TAMPER_MAX_PAIR_NUM; i++)
    {
        if(u32PairSel & (0x1UL << i))
        {
            u32Reg &= ~(u32TmpReg << ((i * 8UL)));
        }
    }

    u32Reg |= (u32Tamper2En | u32Tamper4En);

    TAMPER->TIOCTL = u32Reg;
}

/**
  * @brief      Config Dynamic Tamper
  *
  * @param[in]  u32ChangeRate       The dynamic tamper output change rate
  *                                 - \ref TAMPER_2POW6_CLK
  *                                 - \ref TAMPER_2POW7_CLK
  *                                 - \ref TAMPER_2POW8_CLK
  *                                 - \ref TAMPER_2POW9_CLK
  *                                 - \ref TAMPER_2POW10_CLK
  *                                 - \ref TAMPER_2POW11_CLK
  *                                 - \ref TAMPER_2POW12_CLK
  *                                 - \ref TAMPER_2POW13_CLK
  *
  * @param[in]  u32SeedReload       Reload new seed or not
  *                                 0: not reload new seed
  *                                 1: reload new seed
  *
  * @param[in]  u32RefPattern       Reference pattern
  *                                 - \ref TAMPER_REF_RANDOM_PATTERN
  *                                 - \ref TAMPER_REF_SEED
  *
  * @param[in]  u32Seed             Seed Value (0x0 ~ 0xFFFFFFFF)
  *
  * @return     None
  *
  * @details    This API is used to config dynamic tamper setting.
  */
void TAMPER_DynamicTamperConfig(uint32_t u32ChangeRate, uint32_t u32SeedReload, uint32_t u32RefPattern, uint32_t u32Seed)
{
    uint32_t u32Reg;

    u32Reg = TAMPER->TIOCTL;

    u32Reg &= ~(TAMPER_TIOCTL_DYNSRC_Msk | TAMPER_TIOCTL_SEEDRLD_Msk | TAMPER_TIOCTL_DYNRATE_Msk);

    u32Reg |= (u32ChangeRate) | ((u32SeedReload & 0x1UL) << TAMPER_TIOCTL_SEEDRLD_Pos) |
              ((u32RefPattern & 0x1UL) << TAMPER_TIOCTL_DYNSRC_Pos);

    TAMPER->SEED = u32Seed; /* Need to set seed value before reloaded seed */
    TAMPER->TIOCTL = u32Reg;
}

/**
  * @brief      Active Shield Dynamic Tamper Detect
  *
  * @param[in]  u32PairSel1/2       Active shield 1/2 tamper pin detection enable. Possible options are
  *                                 - \ref TAMPER_PAIR0_SELECT
  *                                 - \ref TAMPER_PAIR1_SELECT
  *                                 - \ref TAMPER_PAIR2_SELECT
  *
  *  @param[in]  u32Pair1Source1/2  Active shield 1/2 dynamic pair 1 input source select
  *                                 0: Pair 1 source select tamper 2
  *                                 1: Pair 1 source select tamper 0
  *
  * @return     None
  *
  * @details    This API is used to enable the active shield dynamic tamper.
  */
void TAMPER_ActiveShieldDynamicTamperEnable(uint32_t u32PairSel1, uint32_t u32Pair1Source1, uint32_t u32PairSel2, uint32_t u32Pair1Source2)
{
    uint32_t i;
    uint32_t u32Reg1, u32Reg2;
    uint32_t u32TmpReg1, u32TmpReg2;

    u32Reg1 = TAMPER->ACTSTIOCTL1;
    u32Reg1 &= ~(TAMPER_ACTSTIOCTL1_ATAMP0EN_Msk | TAMPER_ACTSTIOCTL1_ATAMP1EN_Msk | TAMPER_ACTSTIOCTL1_ATAMP2EN_Msk |
                 TAMPER_ACTSTIOCTL1_ATAMP3EN_Msk | TAMPER_ACTSTIOCTL1_ATAMP4EN_Msk | TAMPER_ACTSTIOCTL1_ATAMP5EN_Msk);
    u32Reg2 = TAMPER->ACTSTIOCTL2;
    u32Reg2 &= ~(TAMPER_ACTSTIOCTL2_ATAMP0EN2_Msk | TAMPER_ACTSTIOCTL2_ATAMP1EN2_Msk | TAMPER_ACTSTIOCTL2_ATAMP2EN2_Msk |
                 TAMPER_ACTSTIOCTL2_ATAMP3EN2_Msk | TAMPER_ACTSTIOCTL2_ATAMP4EN2_Msk | TAMPER_ACTSTIOCTL2_ATAMP5EN2_Msk);

    u32Reg1 &= ~(TAMPER_ACTSTIOCTL1_ADYN1ISS_Msk);
    u32Reg1 |= ((u32Pair1Source1 & 0x1UL) << TAMPER_ACTSTIOCTL1_ADYN1ISS_Pos);
    u32Reg2 &= ~(TAMPER_ACTSTIOCTL2_ADYN1ISS2_Msk);
    u32Reg2 |= ((u32Pair1Source2 & 0x1UL) << TAMPER_ACTSTIOCTL2_ADYN1ISS2_Pos);

    u32TmpReg1 = (TAMPER_ACTSTIOCTL1_ATAMP0EN_Msk | TAMPER_ACTSTIOCTL1_ATAMP1EN_Msk | TAMPER_ACTSTIOCTL1_ADYNPR0EN_Msk);
    u32TmpReg2 = (TAMPER_ACTSTIOCTL2_ATAMP0EN2_Msk | TAMPER_ACTSTIOCTL2_ATAMP1EN2_Msk | TAMPER_ACTSTIOCTL2_ADYNPR0EN2_Msk);

    for(i = 0UL; i < (uint32_t)TAMPER_MAX_PAIR_NUM; i++)
    {
        if(u32PairSel1 & (0x1UL << i))
        {
            u32Reg1 |= (u32TmpReg1 << (i * 8UL));
        }

        if(u32PairSel2 & (0x1UL << i))
        {
            u32Reg2 |= (u32TmpReg2 << (i * 8UL));
        }
    }

    if((u32Pair1Source1) && (u32PairSel1 & (uint32_t)TAMPER_PAIR1_SELECT))
    {
        u32Reg1 &= ~TAMPER_ACTSTIOCTL1_ATAMP2EN_Msk;
    }

    if((u32Pair1Source2) && (u32PairSel2 & (uint32_t)TAMPER_PAIR1_SELECT))
    {
        u32Reg2 &= ~TAMPER_ACTSTIOCTL2_ATAMP2EN2_Msk;
    }

    TAMPER->ACTSTIOCTL1 = u32Reg1;
    TAMPER->ACTSTIOCTL2 = u32Reg2;
}

/**
  * @brief      Active Shield Dynamic Tamper Disable
  *
  * @param[in]  u32PairSel1/2       Active shield 1/2 tamper pin detection disable. Possible options are
  *                                 - \ref TAMPER_PAIR0_SELECT
  *                                 - \ref TAMPER_PAIR1_SELECT
  *                                 - \ref TAMPER_PAIR2_SELECT
  *
  * @return     None
  *
  * @details    This API is used to disable the active shield dynamic tamper.
  */
void TAMPER_ActiveShieldDynamicTamperDisable(uint32_t u32PairSel1, uint32_t u32PairSel2)
{
    uint32_t i;
    uint32_t u32Reg1, u32Reg2;
    uint32_t u32TmpReg1, u32TmpReg2;
    uint32_t u32Tamper2En1 = 0UL, u32Tamper2En2 = 0UL;

    u32Reg1 = TAMPER->ACTSTIOCTL1;
    u32Reg2 = TAMPER->ACTSTIOCTL2;

    if((u32Reg1 & (uint32_t)TAMPER_ACTSTIOCTL1_ADYN1ISS_Msk) && (u32PairSel1 & (uint32_t)TAMPER_PAIR1_SELECT))
    {
        u32Tamper2En1 = u32Reg1 & TAMPER_ACTSTIOCTL1_ATAMP2EN_Msk;
    }

    if((u32Reg2 & (uint32_t)TAMPER_ACTSTIOCTL2_ADYN1ISS2_Msk) && (u32PairSel2 & (uint32_t)TAMPER_PAIR1_SELECT))
    {
        u32Tamper2En2 = u32Reg2 & TAMPER_ACTSTIOCTL2_ATAMP2EN2_Msk;
    }

    u32TmpReg1 = (TAMPER_ACTSTIOCTL1_ATAMP0EN_Msk | TAMPER_ACTSTIOCTL1_ATAMP1EN_Msk | TAMPER_ACTSTIOCTL1_ADYNPR0EN_Msk);
    u32TmpReg2 = (TAMPER_ACTSTIOCTL2_ATAMP0EN2_Msk | TAMPER_ACTSTIOCTL2_ATAMP1EN2_Msk | TAMPER_ACTSTIOCTL2_ADYNPR0EN2_Msk);

    for(i = 0UL; i < (uint32_t)TAMPER_MAX_PAIR_NUM; i++)
    {
        if(u32PairSel1 & (0x1UL << i))
        {
            u32Reg1 &= ~(u32TmpReg1 << ((i * 8UL)));
        }

        if(u32PairSel2 & (0x1UL << i))
        {
            u32Reg2 &= ~(u32TmpReg2 << ((i * 8UL)));
        }
    }

    u32Reg1 |= u32Tamper2En1;
    u32Reg2 |= u32Tamper2En2;

    TAMPER->ACTSTIOCTL1 = u32Reg1;
    TAMPER->ACTSTIOCTL2 = u32Reg2;
}

/**
  * @brief      Config Active Shield Dynamic Tamper
  *
  * @param[in]  u32ChangeRate1/2    The dynamic tamper output change rate
  *                                 - \ref TAMPER_ACTS_2POW10_CLK
  *                                 - \ref TAMPER_ACTS_2POW11_CLK
  *                                 - \ref TAMPER_ACTS_2POW12_CLK
  *                                 - \ref TAMPER_ACTS_2POW13_CLK
  *                                 - \ref TAMPER_ACTS_2POW14_CLK
  *                                 - \ref TAMPER_ACTS_2POW15_CLK
  *                                 - \ref TAMPER_ACTS_2POW16_CLK
  *                                 - \ref TAMPER_ACTS_2POW17_CLK
  *
  * @param[in]  u32SeedReload1/2    Reload new seed or not
  *                                 0: not reload new seed
  *                                 1: reload new seed
  *
  * @param[in]  u32RefPattern1/2    Reference pattern
  *                                 - \ref TAMPER_REF_RANDOM_PATTERN
  *                                 - \ref TAMPER_REF_SEED
  *
  * @param[in]  u32Seed/2           Seed Value (0x0 ~ 0xFFFFFFFF)
  *
  * @return     None
  *
  * @details    This API is used to config active shield dynamic tamper setting.
  */
void TAMPER_ActiveShieldDynamicTamperConfig(uint32_t u32ChangeRate1, uint32_t u32SeedReload1, uint32_t u32RefPattern1, uint32_t u32Seed,
        uint32_t u32ChangeRate2, uint32_t u32SeedReload2, uint32_t u32RefPattern2, uint32_t u32Seed2)
{
    uint32_t u32Reg1, u32Reg2;

    u32Reg1 = TAMPER->ACTSTIOCTL1;
    u32Reg2 = TAMPER->ACTSTIOCTL2;

    u32Reg1 &= ~(TAMPER_ACTSTIOCTL1_ADYNSRC_Msk | TAMPER_ACTSTIOCTL1_ADYNRATE_Msk);
    u32Reg2 &= ~(TAMPER_ACTSTIOCTL2_ADYNSRC2_Msk | TAMPER_ACTSTIOCTL2_SEEDRLD2_Msk | TAMPER_ACTSTIOCTL2_ADYNRATE2_Msk);

    u32Reg1 |= (u32ChangeRate1) | ((u32RefPattern1 & 0x1UL) << TAMPER_ACTSTIOCTL1_ADYNSRC_Pos);
    u32Reg2 |= (u32ChangeRate2) | ((u32SeedReload2 & 0x1UL) << TAMPER_ACTSTIOCTL2_SEEDRLD2_Pos) |
               ((u32RefPattern2 & 0x1UL) << TAMPER_ACTSTIOCTL2_ADYNSRC2_Pos);

    TAMPER->SEED = u32Seed; /* Need to set seed value before reloaded seed */
    TAMPER->SEED2 = u32Seed2; /* Need to set seed value before reloaded seed */

    TAMPER->ACTSTIOCTL1 = u32Reg1;
    TAMPER->TIOCTL |= ((u32SeedReload1 & 0x1UL) << TAMPER_TIOCTL_SEEDRLD_Pos);
    TAMPER->ACTSTIOCTL2 = u32Reg2;
}

/**@}*/ /* end of group TAMPER_EXPORTED_FUNCTIONS */

/**@}*/ /* end of group TAMPER_Driver */

/**@}*/ /* end of group Standard_Driver */

