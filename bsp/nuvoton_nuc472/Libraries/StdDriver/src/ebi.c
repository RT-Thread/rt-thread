/****************************************************************************//**
 * @file     ebi.c
 * @version  V0.10
 * $Revision: 8 $
 * $Date: 15/06/23 5:40p $
 * @brief    NUC472/NUC442 EBI driver source file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "NUC472_442.h"
#include "ebi.h"

/** @addtogroup NUC472_442_Device_Driver NUC472/NUC442 Device Driver
  @{
*/

/** @addtogroup NUC472_442_EBI_Driver EBI Driver
  @{
*/


/** @addtogroup NUC472_442_EBI_EXPORTED_FUNCTIONS EBI Exported Functions
  @{
*/

/**
  * @brief  Initialize EBI for Bank 0~3
  * @param[in]  u32Bank Bank number for EBI. Valid values are:
  *                      - \ref EBI_BANK0
  *                      - \ref EBI_BANK1
  *                      - \ref EBI_BANK2
  *                      - \ref EBI_BANK3
  * @param[in]  u32DataWidth Data bus width. Valid values are:
  *                      - \ref EBI_BUSWIDTH_8BIT
  *                      - \ref EBI_BUSWIDTH_16BIT
  * @param[in]  u32TimingClass Default timing configuration. Valid values are:
  *                      - \ref EBI_TIMING_FASTEST
  *                      - \ref EBI_TIMING_VERYFAST
  *                      - \ref EBI_TIMING_FAST
  *                      - \ref EBI_TIMING_NORMAL
  *                      - \ref EBI_TIMING_SLOW
  *                      - \ref EBI_TIMING_VERYSLOW
  *                      - \ref EBI_TIMING_SLOWEST
  * @param[in]  u32BusMode Enable EBI separate mode. Valid values are:
  *                      - \ref EBI_SEPARATEMODE_ENABLE
  *                      - \ref EBI_SEPARATEMODE_DISABLE
  * @param[in]  u32CSActiveLevel CS is active High/Low. Valid values are:
  *                      - \ref EBI_CS_ACTIVE_HIGH
  *                      - \ref EBI_CS_ACTIVE_LOW
  * @return none
  */
void EBI_Open(uint32_t u32Bank, uint32_t u32DataWidth, uint32_t u32TimingClass, uint32_t u32BusMode, uint32_t u32CSActiveLevel)
{
    /* Enable EBI channel */
    EBI->TCTL[u32Bank] |= EBI_TCTL_CSEN_Msk;

    /* Configure data bus to 8 or 16bit */
    if(u32DataWidth == EBI_BUSWIDTH_8BIT)
        EBI->TCTL[u32Bank] &= ~EBI_TCTL_DW16_Msk;
    else
        EBI->TCTL[u32Bank] |= EBI_TCTL_DW16_Msk;

    /* Enable separate mode */
    if(u32BusMode)
        EBI->TCTL[u32Bank] |= EBI_TCTL_SEPEN_Msk;
    else
        EBI->TCTL[u32Bank] &= ~EBI_TCTL_SEPEN_Msk;

    /* Setup active level of chip select */
    switch(u32Bank) {
    case EBI_BANK0:
        if(u32CSActiveLevel)
            EBI->CTL |= (0x1ul << EBI_CTL_CSPOLINV_Pos);
        else
            EBI->CTL &= ~(0x1ul << EBI_CTL_CSPOLINV_Pos);
        break;

    case EBI_BANK1:
        if(u32CSActiveLevel)
            EBI->CTL |= (0x2ul << EBI_CTL_CSPOLINV_Pos);
        else
            EBI->CTL &= ~(0x2ul << EBI_CTL_CSPOLINV_Pos);
        break;

    case EBI_BANK2:
        if(u32CSActiveLevel)
            EBI->CTL |= (0x4ul << EBI_CTL_CSPOLINV_Pos);
        else
            EBI->CTL &= ~(0x4ul << EBI_CTL_CSPOLINV_Pos);
        break;

    case EBI_BANK3:
        if(u32CSActiveLevel)
            EBI->CTL |= (0x8ul << EBI_CTL_CSPOLINV_Pos);
        else
            EBI->CTL &= ~(0x8ul << EBI_CTL_CSPOLINV_Pos);
        break;
    }

    /* Clear R2R/R2W/R2X/TAHD/TACC/TALE entries for safety */
    EBI->TCTL[u32Bank] &= ~0x0F0FF7FF;

    /* Setup EBI timing */
    switch(u32TimingClass) {
    case EBI_TIMING_FASTEST:
        EBI->CTL = (EBI->CTL & ~EBI_CTL_MCLKDIV_Msk) | (  EBI_MCLKDIV_1 << 8);
        break;

    case EBI_TIMING_VERYFAST:
        EBI->CTL = (EBI->CTL & ~EBI_CTL_MCLKDIV_Msk) | (  EBI_MCLKDIV_1 << 8);
        EBI->TCTL[u32Bank] |= 0x0303331B;
        break;

    case EBI_TIMING_FAST:
        EBI->CTL = (EBI->CTL & ~EBI_CTL_MCLKDIV_Msk) | (  EBI_MCLKDIV_2 << 8);
        break;

    case EBI_TIMING_NORMAL:
        EBI->CTL = (EBI->CTL & ~EBI_CTL_MCLKDIV_Msk) | (  EBI_MCLKDIV_2 << 8);
        EBI->TCTL[u32Bank] |= 0x0303331B;
        break;

    case EBI_TIMING_SLOW:
        EBI->CTL = (EBI->CTL & ~EBI_CTL_MCLKDIV_Msk) | (  EBI_MCLKDIV_2 << 8);
        EBI->TCTL[u32Bank] |= 0x0707773F;
        break;

    case EBI_TIMING_VERYSLOW:
        EBI->CTL = (EBI->CTL & ~EBI_CTL_MCLKDIV_Msk) | (  EBI_MCLKDIV_4 << 8);
        EBI->TCTL[u32Bank] |= 0x0707773F;
        break;

    case EBI_TIMING_SLOWEST:
        EBI->CTL = (EBI->CTL & ~EBI_CTL_MCLKDIV_Msk) | (  EBI_MCLKDIV_8 << 8);
        EBI->TCTL[u32Bank] |= 0x0707773F;
        break;
    }
}

/**
  * @brief  Disable EBI for bank 0~3.
  * @param[in]  u32Bank Bank number for EBI. Valid values are:
  *                      - \ref EBI_BANK0
  *                      - \ref EBI_BANK1
  *                      - \ref EBI_BANK2
  *                      - \ref EBI_BANK3
  * @return none
  */
void EBI_Close(uint32_t u32Bank)
{
    EBI->TCTL[u32Bank] &= ~EBI_TCTL_CSEN_Msk;
}

/**
  * @brief  Set EBI bus timings
  * @param[in]  u32Bank Bank number for EBI. Valid values are:
  *                      - \ref EBI_BANK0
  *                      - \ref EBI_BANK1
  *                      - \ref EBI_BANK2
  *                      - \ref EBI_BANK3
  * @param[in]  u32TimingConfig The new EBI timing settings.
  * @param[in]  u32MclkDiv Divider for MCLK. Valid values are:
  *                      - \ref EBI_MCLKDIV_1
  *                      - \ref EBI_MCLKDIV_2
  *                      - \ref EBI_MCLKDIV_4
  *                      - \ref EBI_MCLKDIV_8
  *                      - \ref EBI_MCLKDIV_16
  *                      - \ref EBI_MCLKDIV_32
  * @return none
  */
void EBI_SetBusTiming(uint32_t u32Bank, uint32_t u32TimingConfig, uint32_t u32MclkDiv)
{
    EBI->CTL = (EBI->CTL & ~EBI_CTL_MCLKDIV_Msk) | (u32MclkDiv << EBI_CTL_MCLKDIV_Pos);
    EBI->TCTL[u32Bank] |= (u32TimingConfig & 0x0F0FF7FF);
}

/**
  * @brief  Enable encrypt/decrypt function and set key for EBI bank 0~3.
  * @param[in]  u32Bank Bank number for EBI. Valid values are:
  *                      - \ref EBI_BANK0
  *                      - \ref EBI_BANK1
  *                      - \ref EBI_BANK2
  *                      - \ref EBI_BANK3
  * @param[in]  *u32Key 128-bits encrypt/decrypt key array.
  * @return none
  */
void EBI_EnableCrypto(uint32_t u32Bank, uint32_t *u32Key)
{
    switch(u32Bank) {
    case EBI_BANK0:
        EBI->CTL |= (0x1ul << EBI_CTL_CRYPTOEN_Pos);
        break;
    case EBI_BANK1:
        EBI->CTL |= (0x2ul << EBI_CTL_CRYPTOEN_Pos);
        break;
    case EBI_BANK2:
        EBI->CTL |= (0x4ul << EBI_CTL_CRYPTOEN_Pos);
        break;
    case EBI_BANK3:
        EBI->CTL |= (0x8ul << EBI_CTL_CRYPTOEN_Pos);
        break;
    }

    /* Setup 128-bits key */
    EBI->KEY0 = u32Key[0];
    EBI->KEY1 = u32Key[1];
    EBI->KEY2 = u32Key[2];
    EBI->KEY3 = u32Key[3];
}

/**
  * @brief  Disable encrypt/decrypt function for EBI bank 0~3.
  * @param[in]  u32Bank Bank number for EBI. Valid values are:
  *                      - \ref EBI_BANK0
  *                      - \ref EBI_BANK1
  *                      - \ref EBI_BANK2
  *                      - \ref EBI_BANK3
  * @return none
  */
void EBI_DisbleCrypto(uint32_t u32Bank)
{
    switch(u32Bank) {
    case EBI_BANK0:
        EBI->CTL &= ~(0x1ul << EBI_CTL_CRYPTOEN_Pos);
        break;
    case EBI_BANK1:
        EBI->CTL &= ~(0x2ul << EBI_CTL_CRYPTOEN_Pos);
        break;
    case EBI_BANK2:
        EBI->CTL &= ~(0x4ul << EBI_CTL_CRYPTOEN_Pos);
        break;
    case EBI_BANK3:
        EBI->CTL &= ~(0x8ul << EBI_CTL_CRYPTOEN_Pos);
        break;
    }
}

/*@}*/ /* end of group NUC472_442_EBI_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC472_442_EBI_Driver */

/*@}*/ /* end of group NUC472_442_Device_Driver */

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
