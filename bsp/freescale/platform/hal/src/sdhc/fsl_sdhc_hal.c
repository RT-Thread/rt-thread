/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "fsl_sdhc_hal.h"
#include <string.h>
#if FSL_FEATURE_SOC_SDHC_COUNT

/*FUNCTION****************************************************************
 *
 * Function Name: SDHC_HAL_Init
 * Description: Initialize sdhc hal
 *
 *END*********************************************************************/
void SDHC_HAL_Init(SDHC_Type * base)
{
    sdhc_hal_sdclk_config_t sdClkConf;
    sdhc_hal_config_t config;
    sdClkConf.enable = false;
    SDHC_HAL_ConfigSdClock(base, &sdClkConf);
    /* Load default configuration */
    SDHC_HAL_Config(base, &config);
    SDHC_HAL_SetIntState(base, false, (uint32_t)-1);
    SDHC_HAL_SetIntSignal(base, false, (uint32_t)-1);
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDHC_HAL_SetIntSignal
 * Description: Enable specified interrupts
 *
 *END*********************************************************************/
void SDHC_HAL_SetIntSignal(SDHC_Type * base, bool enable, uint32_t mask)
{
    if (enable)
    {
        SDHC_SET_IRQSIGEN(base, mask);
    }
    else
    {
        SDHC_CLR_IRQSIGEN(base, mask);
    }
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDHC_HAL_SetIntState
 * Description: Enable specified interrupts' state
 *
 *END*********************************************************************/
void SDHC_HAL_SetIntState(SDHC_Type * base, bool enable, uint32_t mask)
{
    if (enable)
    {
        SDHC_SET_IRQSTATEN(base, mask);
    }
    else
    {
        SDHC_CLR_IRQSTATEN(base, mask);
    }
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDHC_HAL_GetResponse
 * Description: get command response
 *
 *END*********************************************************************/
uint32_t SDHC_HAL_GetResponse(SDHC_Type * base, uint32_t index)
{
    assert(index < 4);
    return SDHC_RD_CMDRSP(base, index);
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDHC_HAL_InitCard
 * Description: Initialize card by sending 80 clocks to card
 *
 *END*********************************************************************/
uint32_t SDHC_HAL_InitCard(SDHC_Type * base, uint32_t timeout)
{
    assert(timeout);
    SDHC_BWR_SYSCTL_INITA(base, 1);
    while((!SDHC_BRD_SYSCTL_INITA(base)))
    {
        if (!timeout)
        {
            break;
        }
        timeout--;
    }
    return (!timeout);
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDHC_HAL_Reset
 * Description: Perform different kinds of reset
 *
 *END*********************************************************************/
uint32_t SDHC_HAL_Reset(SDHC_Type * base, uint32_t type, uint32_t timeout)
{
    uint32_t mask;
    assert(timeout);
    mask = type & (SDHC_SYSCTL_RSTA_MASK
                 | SDHC_SYSCTL_RSTC_MASK
                 | SDHC_SYSCTL_RSTD_MASK);
    SDHC_SET_SYSCTL(base, mask);
    while ((SDHC_RD_SYSCTL(base) & mask))
    {
        if (!timeout)
        {
            break;
        }
        timeout--;
    }
    return (!timeout);
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDHC_HAL_GetCapability
 * Description: Get the capability of the SDHC 
 *
 *END*********************************************************************/
void SDHC_HAL_GetBasicInfo(SDHC_Type * base, sdhc_hal_basic_info_t* basicInfo)
{
    uint32_t capability;
    uint32_t htcapbltReg;
    uint32_t hostverReg;
    uint8_t mblBit;
    assert(base);
    assert(basicInfo);
    capability = 0;
    htcapbltReg = SDHC_RD_HTCAPBLT(base);
    
    if (htcapbltReg & SDHC_HTCAPBLT_VS33_MASK)
    {
        capability |= SDHC_HAL_SUPPORT_V330_FLAG;
    }
#if FSL_FEATURE_SDHC_HAS_V300_SUPPORT
    if (htcapbltReg & SDHC_HTCAPBLT_VS30_MASK)
    {
        capability |= SDHC_HAL_SUPPORT_V300_FLAG;
    }
#endif
    if (htcapbltReg & SDHC_HTCAPBLT_HSS_MASK)
    {
        capability |= SDHC_HAL_SUPPORT_HIGHSPEED_FLAG;
    }
    if (htcapbltReg & SDHC_HTCAPBLT_DMAS_MASK)
    {
        capability |= SDHC_HAL_SUPPORT_DMA_FLAG;
    }
    if (htcapbltReg & SDHC_HTCAPBLT_ADMAS_MASK)
    {
        capability |= SDHC_HAL_SUPPORT_ADMA_FLAG;
    }
    if (htcapbltReg & SDHC_HTCAPBLT_SRS_MASK)
    {
        capability |= SDHC_HAL_SUPPORT_SUSPEND_RESUME_FLAG;
    }
#if FSL_FEATURE_SDHC_HAS_V180_SUPPORT
    if (htcapbltReg & SDHC_HTCAPBLT_VS18_MASK)
    {
        capability |= SDHC_HAL_SUPPORT_V180_FLAG;
    }
#endif
#if FSL_FEATURE_SDHC_HAS_EXTERNAL_DMA_SUPPORT 
    capability |= SDHC_HAL_SUPPORT_EXDMA_FLAG;
#endif 
    basicInfo->capability          = capability;
    mblBit = ((htcapbltReg & SDHC_HTCAPBLT_MBL_MASK) >> SDHC_HTCAPBLT_MBL_SHIFT);
    switch (mblBit)
    {
    case SDHC_HAL_MAX_BLKLEN_512B:
      {
          basicInfo->maxBlkLen = 512;
          break;
      }
    case SDHC_HAL_MAX_BLKLEN_1024B:
      {
          basicInfo->maxBlkLen = 1024;
          break;
      }
    case SDHC_HAL_MAX_BLKLEN_2048B:
      {
          basicInfo->maxBlkLen = 2048;
          break;
      }
    case SDHC_HAL_MAX_BLKLEN_4096B:
      {
          basicInfo->maxBlkLen = 4096;
          break;
      }
    default:
      {
          break;
      }
    }
    hostverReg = SDHC_RD_HOSTVER(base);
    basicInfo->specVer = ((hostverReg & SDHC_HOSTVER_SVN_MASK) >> SDHC_HOSTVER_SVN_SHIFT);
    basicInfo->vendorVer = ((hostverReg & SDHC_HOSTVER_VVN_MASK) >> SDHC_HOSTVER_VVN_SHIFT);
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDHC_HAL_ConfigSdClock
 * Description: configure clock of host controller, it will set the most
 *      close clock frequency to the given clock
 *
 *END*********************************************************************/
void SDHC_HAL_ConfigSdClock(SDHC_Type * base, sdhc_hal_sdclk_config_t* clkConfItms)
{
    uint32_t divisor, freq, sysCtlReg;
    assert(base);
    assert(clkConfItms);
    divisor = SDHC_HAL_INITIAL_DVS;
    freq = SDHC_HAL_INITIAL_CLKFS;
    /* Enables the IPG clock and no automatic clock gating off. 
     Enables the system clock and no automatic clock gating off. 
     Enables the peripheral clock and no automatic clock gating off. 
     Enables the SD clock. It should be disabled before changing the SD clock */
    SDHC_CLR_SYSCTL(base, (SDHC_SYSCTL_IPGEN_MASK | SDHC_SYSCTL_HCKEN_MASK | \
      SDHC_SYSCTL_PEREN_MASK | SDHC_SYSCTL_SDCLKEN_MASK));
    /* If user want to disable the clock , directly return. */
    if(!(clkConfItms->enable))
    {
        return;
    }
    if (clkConfItms->destClk > 0)
    {
        while((clkConfItms->maxHostClk / freq / SDHC_HAL_MAX_DVS > clkConfItms->destClk) &&
                (freq < SDHC_HAL_MAX_CLKFS))
        {
            SDHC_HAL_NEXT_CLKFS(freq);
        }
        while((clkConfItms->maxHostClk / freq / divisor > clkConfItms->destClk) &&
                (divisor < SDHC_HAL_MAX_DVS))
        {
            SDHC_HAL_NEXT_DVS(divisor);
        }

        clkConfItms->destClk = clkConfItms->maxHostClk / freq / divisor;
        SDHC_HAL_PREV_CLKFS(freq);
        SDHC_HAL_PREV_DVS(divisor);
        sysCtlReg = SDHC_RD_SYSCTL(base);
        /* Sets the SD clock frequency divisor. */
        sysCtlReg &= (~SDHC_SYSCTL_DVS_MASK);
        sysCtlReg |= (SDHC_SYSCTL_DVS(divisor));
        /* Sets the SD clock frequency select. */
        sysCtlReg &= (~SDHC_SYSCTL_SDCLKFS_MASK);
        sysCtlReg |= (SDHC_SYSCTL_SDCLKFS(freq));
        /* Sets the data timeout counter value. */
        sysCtlReg &= (~SDHC_SYSCTL_DTOCV_MASK);
        sysCtlReg |= (SDHC_SYSCTL_DTOCV(0xE));
        /* Enables the IPG clock and no automatic clock gating off. 
         Enables the system clock and no automatic clock gating off. 
         Enables the peripheral clock and no automatic clock gating off. */
        sysCtlReg |= (SDHC_SYSCTL_IPGEN_MASK | SDHC_SYSCTL_HCKEN_MASK | SDHC_SYSCTL_PEREN_MASK);
        SDHC_WR_SYSCTL(base, sysCtlReg);
        /* Checks whether the SD clock is stable or not. */
        while(!SDHC_BRD_PRSSTAT_SDSTB(base)) {}
        /* nables the SD clock. It should be disabled before changing the SD clock frequency. */
        SDHC_SET_SYSCTL(base, SDHC_SYSCTL_SDCLKEN_MASK);
    }
}
        
/*FUNCTION****************************************************************
 *
 * Function Name: SDHC_HAL_GetCurState
 * Description: Get current sdhc state
 *
 *END*********************************************************************/
bool SDHC_HAL_GetCurState(SDHC_Type * base, sdhc_hal_curstat_type_t stateType)
{
    uint8_t dateLineLevel;
    bool status = false; 
    assert(base);
    
    switch(stateType)
    {
    case kSdhcHalIsCmdInhibit:
      {
          status = SDHC_BRD_PRSSTAT_CIHB(base);
          break;
      }
    case kSdhcHalIsDataInhibit:
      {
          status = SDHC_BRD_PRSSTAT_CDIHB(base);
          break;
      }
    case kSdhcHalIsDataLineActive:
      {
          status = SDHC_BRD_PRSSTAT_DLA(base);
          break;
      }
    case kSdhcHalIsSdClockStable:
      {
          status = SDHC_BRD_PRSSTAT_SDSTB(base);
          break;
      }
    case kSdhcHalIsIpgClockOff:
      {
          status = SDHC_BRD_PRSSTAT_IPGOFF(base);
          break;
      }
    case kSdhcHalIsSysClockOff:
      {
          status = SDHC_BRD_PRSSTAT_HCKOFF(base);
          break;
      }
    case kSdhcHalIsPeripheralClockOff:
      {
          status = SDHC_BRD_PRSSTAT_PEROFF(base);
          break;
      }
    case kSdhcHalIsSdClkOff:
      {
          status = SDHC_BRD_PRSSTAT_SDOFF(base);
          break;
      }
    case kSdhcHalIsWriteTransferActive:
      {
          status = SDHC_BRD_PRSSTAT_WTA(base);
          break;
      }
    case kSdhcHalIsReadTransferActive:
      {
          status = SDHC_BRD_PRSSTAT_RTA(base);
          break;
      }
    case kSdhcHalIsBuffWriteEnabled:
      {
          status = SDHC_BRD_PRSSTAT_BWEN(base);
          break;
      }
    case kSdhcHalIsBuffReadEnabled:
      {
          status = SDHC_BRD_PRSSTAT_BREN(base);
          break;
      }
    case kSdhcHalIsCardInserted:
      {
          status = SDHC_BRD_PRSSTAT_CINS(base);
          break;
      }
    case kSdhcHalIsCmdLineLevelHigh:
      {
          status = SDHC_BRD_PRSSTAT_CLSL(base);
          break;
      }
    case kSdhcHalGetDataLine0Level:
    case kSdhcHalGetDataLine1Level:
    case kSdhcHalGetDataLine2Level:
    case kSdhcHalGetDataLine3Level:
    case kSdhcHalGetDataLine4Level:
    case kSdhcHalGetDataLine5Level:
    case kSdhcHalGetDataLine6Level:
    case kSdhcHalGetDataLine7Level:
      {
          dateLineLevel = SDHC_BRD_PRSSTAT_DLSL(base);
          if((dateLineLevel)&(1U<<(stateType-kSdhcHalGetDataLine0Level)))
          {
              status = true;
          }
          else
          {
              status = false;
          }
          break;
      }
    case kSdhcHalGetCdTestLevel:
      {
          status = SDHC_BRD_PROCTL_CDTL(base);
          break;
      }
    default:break;
    }
    return status;
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDHC_HAL_ConfigBootParam
 * Description: Configuration the boot params in MMC mode
 *
 *END*********************************************************************/
static void SDHC_HAL_ConfigBootParam(SDHC_Type * base, const sdhc_mmcboot_param_t* params)
{
    uint32_t mmcBootReg = 0;
    assert(base);
    assert(params);
    /* Sets the timeout value for the boot ACK. */
    mmcBootReg |= SDHC_MMCBOOT_DTOCVACK(params->ackTimeout);
    /* Enables/disable the boot ACK. */
    mmcBootReg |= SDHC_MMCBOOT_BOOTACK(!!(params->enFlags & SDHC_HAL_EN_BOOT_ACK_FLAG));
    /* Configures the boot mode. */
    mmcBootReg |= SDHC_MMCBOOT_BOOTMODE(params->mode);
    /* Enables/disable the fast boot. */
    mmcBootReg |= SDHC_MMCBOOT_BOOTEN(!!(params->enFlags & SDHC_HAL_EN_FAST_BOOT_FLAG));
    /* Enables/disable the automatic stop at the block gap. */
    mmcBootReg |= SDHC_MMCBOOT_AUTOSABGEN(!!(params->enFlags & SDHC_HAL_EN_BOOT_STOP_AT_BLK_GAP_FLAG));
    /* Configures the the block count for the boot. */
    mmcBootReg |= SDHC_MMCBOOT_BOOTBLKCNT(params->blockCount);
    SDHC_WR_MMCBOOT(base, mmcBootReg);
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDHC_HAL_GetBootParam
 * Description: Configuration the boot params in MMC mode
 *
 *END*********************************************************************/
static void SDHC_HAL_GetBootParam(SDHC_Type * base, sdhc_mmcboot_param_t* params)
{
    uint32_t mmcBootReg;
    assert(base);
    assert(params);
    memset(params, 0, sizeof(sdhc_mmcboot_param_t));
    mmcBootReg = SDHC_RD_MMCBOOT(base);
    /* Read the timeout value for the boot ACK. */
    params->ackTimeout = ((mmcBootReg & SDHC_MMCBOOT_DTOCVACK_MASK) >> SDHC_MMCBOOT_DTOCVACK_SHIFT);
    /* Read the boot ACK. */
    if((mmcBootReg & SDHC_MMCBOOT_BOOTACK_MASK) >> SDHC_MMCBOOT_BOOTACK_SHIFT)
    {
        params->enFlags |= SDHC_HAL_EN_BOOT_ACK_FLAG;
    }
    /* Read the boot mode. */
    params->mode = (sdhc_hal_mmcboot_t)((mmcBootReg & SDHC_MMCBOOT_BOOTMODE_MASK) \
      >> SDHC_MMCBOOT_BOOTMODE_SHIFT);
    /* Read the fast boot. */
    if((mmcBootReg & SDHC_MMCBOOT_BOOTEN_MASK) >> SDHC_MMCBOOT_BOOTEN_SHIFT)
    {
        params->enFlags |= SDHC_HAL_EN_FAST_BOOT_FLAG;
    }
    /* Read the automatic stop at the block gap. */
    if((mmcBootReg & SDHC_MMCBOOT_AUTOSABGEN_MASK) >> SDHC_MMCBOOT_AUTOSABGEN_SHIFT)
    {
        params->enFlags |= SDHC_HAL_EN_BOOT_STOP_AT_BLK_GAP_FLAG;
    }
    /* Read the the block count for the boot. */
    params->blockCount = ((mmcBootReg & SDHC_MMCBOOT_BOOTBLKCNT_MASK) >> SDHC_MMCBOOT_BOOTBLKCNT_SHIFT);
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDHC_HAL_Config
 * Description: Configuration in the init phase
 *
 *END*********************************************************************/
void SDHC_HAL_Config(SDHC_Type * base, const sdhc_hal_config_t* initConfig)
{
    uint32_t proctlReg;
    assert(base);
    assert(initConfig);
    
    proctlReg = SDHC_RD_PROCTL(base);
    /* Sets the LED state. */
    proctlReg &= (~SDHC_PROCTL_LCTL_MASK);
    proctlReg |= SDHC_PROCTL_LCTL(initConfig->ledState);
    /* Configures the endian mode. */
    proctlReg &= (~SDHC_PROCTL_EMODE_MASK);
    proctlReg |= SDHC_PROCTL_EMODE(initConfig->endianMode);
    /* Sets the DMA mode. */
    proctlReg &= (~SDHC_PROCTL_DMAS_MASK);
    proctlReg |= SDHC_PROCTL_DMAS(initConfig->dmaMode);
    /* Enables/disable the DAT3 as a card detect pin. */
    proctlReg &= (~SDHC_PROCTL_D3CD_MASK);
    proctlReg |= SDHC_PROCTL_D3CD(!!(initConfig->enFlags & SDHC_HAL_EN_D3CD_FLAG));
    /* Enables/disable the card detect test. */
    proctlReg &= (~SDHC_PROCTL_CDSS_MASK);
    proctlReg |= SDHC_PROCTL_CDSS(!!(initConfig->enFlags & SDHC_HAL_EN_CD_SIG_SEL_FLAG));
    /* Enables/disable stop at the block gap. */
    proctlReg &= (~SDHC_PROCTL_SABGREQ_MASK);
    proctlReg |= SDHC_PROCTL_SABGREQ(!!(initConfig->enFlags & SDHC_HAL_EN_STOP_AT_BLK_GAP_FLAG));
    /* Enables/disable the read wait control for the SDIO cards. */
    proctlReg &= (~SDHC_PROCTL_RWCTL_MASK);
    proctlReg |= SDHC_PROCTL_RWCTL(!!(initConfig->enFlags & SDHC_HAL_EN_READ_WAIT_CTRL_FLAG));
    /* Enables/disable stop at the block gap requests */
    proctlReg &= (~SDHC_PROCTL_IABG_MASK);
    proctlReg |= SDHC_PROCTL_IABG(!!(initConfig->enFlags & SDHC_HAL_EN_INT_STOP_AT_BLK_GAP_FLAG));
    /* Enables/disable wakeup event on the card interrupt. */
    proctlReg &= (~SDHC_PROCTL_WECINT_MASK);
    proctlReg |= SDHC_PROCTL_WECINT(!!(initConfig->enFlags & SDHC_HAL_EN_WAKEUP_ON_CARD_INT_FLAG));
    /* Enables/disable wakeup event on the card insertion. */
    proctlReg &= (~SDHC_PROCTL_WECINS_MASK);
    proctlReg |= SDHC_PROCTL_WECINS(!!(initConfig->enFlags & SDHC_HAL_EN_WAKEUP_ON_CARD_INS_FLAG));
    /* Enables/disable  wakeup event on card removal. */
    proctlReg &= (~SDHC_PROCTL_WECRM_MASK);
    proctlReg |= SDHC_PROCTL_WECRM(!!(initConfig->enFlags & SDHC_HAL_EN_WAKEUP_ON_CARD_REM_FLAG));
    SDHC_WR_PROCTL(base, proctlReg);
    
    /* Sets the watermark for writing. */
    SDHC_BWR_WML_WRWML(base, initConfig->writeWatermarkLevel);
    /* Sets the watermark for reading. */
    SDHC_BWR_WML_RDWML(base, initConfig->readWatermarkLevel);
#if FSL_FEATURE_SDHC_HAS_EXTERNAL_DMA_SUPPORT
    /* Enables/disable the external DMA request. */
    SDHC_BWR_VENDOR_EXTDMAEN(base, (!!(initConfig->enFlags & SDHC_HAL_EN_EXT_DMA_REQ_FLAG)));
#endif
    /* Enables/disable the exact block number for the SDIO CMD53. */ 
    SDHC_BWR_VENDOR_EXBLKNU(base, (!!(initConfig->enFlags & SDHC_HAL_EN_EXACT_BLK_NUM_FLAG)));
    SDHC_HAL_ConfigBootParam(base, &(initConfig->bootParams));
}

/*!
* @brief Get current configuration.
*
* @param base SDHC base address
* @param initConfig The configuration structure 
*/
void SDHC_HAL_GetCurConfig(SDHC_Type * base, sdhc_hal_config_t* curConfig)
{
    uint32_t proctlReg;
    assert(base);
    assert(curConfig);
    memset(curConfig, 0, sizeof(sdhc_hal_config_t));
    proctlReg = SDHC_RD_PROCTL(base);
    /* Read the LED state. */
    curConfig->ledState = (sdhc_hal_led_t)((proctlReg & SDHC_PROCTL_LCTL_MASK) \
      >> SDHC_PROCTL_LCTL_SHIFT);
    /* Read the endian mode. */
    curConfig->endianMode = (sdhc_hal_endian_t)((proctlReg & SDHC_PROCTL_EMODE_MASK) \
      >> SDHC_PROCTL_EMODE_SHIFT);
    /* Read the DMA mode. */
    curConfig->dmaMode = (sdhc_hal_dma_mode_t)((proctlReg & SDHC_PROCTL_DMAS_MASK)\
      >> SDHC_PROCTL_DMAS_SHIFT);
    /* Read the DAT3 as a card detect pin. */
    if((proctlReg & SDHC_PROCTL_D3CD_MASK) >> SDHC_PROCTL_D3CD_SHIFT)
    {
        curConfig->enFlags |= SDHC_HAL_EN_D3CD_FLAG;
    }
    /* Read the card detect signal selection configuration. */
    if((proctlReg & SDHC_PROCTL_CDSS_MASK) >> SDHC_PROCTL_CDSS_SHIFT)
    {
        curConfig->enFlags |= SDHC_HAL_EN_CD_SIG_SEL_FLAG;
    }
    /* Read stop at the block gap. */
    if((proctlReg & SDHC_PROCTL_SABGREQ_MASK) >> SDHC_PROCTL_SABGREQ_SHIFT)
    {
        curConfig->enFlags |= SDHC_HAL_EN_STOP_AT_BLK_GAP_FLAG;
    }
    /* Read the read wait control for the SDIO cards. */
    if((proctlReg & SDHC_PROCTL_RWCTL_MASK) >> SDHC_PROCTL_RWCTL_SHIFT)
    {
        curConfig->enFlags |= SDHC_HAL_EN_READ_WAIT_CTRL_FLAG;
    }
    /* Read stop at the block gap requests */
    if((proctlReg & SDHC_PROCTL_IABG_MASK) >> SDHC_PROCTL_IABG_SHIFT)
    {
        curConfig->enFlags |= SDHC_HAL_EN_INT_STOP_AT_BLK_GAP_FLAG;
    }

    /* Read wakeup event on the card interrupt. */
    if((proctlReg & SDHC_PROCTL_WECINT_MASK) >> SDHC_PROCTL_WECINT_SHIFT)
    {
        curConfig->enFlags |= SDHC_HAL_EN_WAKEUP_ON_CARD_INT_FLAG;
    }
    /* Read wakeup event on the card insertion. */
    if((proctlReg & SDHC_PROCTL_WECINS_MASK) >> SDHC_PROCTL_WECINS_SHIFT)
    {
        curConfig->enFlags |= SDHC_HAL_EN_WAKEUP_ON_CARD_INS_FLAG;
    }
    /* Read  wakeup event on card removal. */
    if((proctlReg & SDHC_PROCTL_WECRM_MASK) >> SDHC_PROCTL_WECRM_SHIFT)
    {
        curConfig->enFlags |= SDHC_HAL_EN_WAKEUP_ON_CARD_REM_FLAG;
    }
    
    /* Read the watermark for writing. */
    curConfig->writeWatermarkLevel    = SDHC_BRD_WML_WRWML(base);
    /* Read the watermark for reading. */
    curConfig->readWatermarkLevel     = SDHC_BRD_WML_RDWML(base);
#if FSL_FEATURE_SDHC_HAS_EXTERNAL_DMA_SUPPORT
    /* Read the external DMA request. */
    if(SDHC_BRD_VENDOR_EXTDMAEN(base))
    {
        curConfig->enFlags |= SDHC_HAL_EN_EXT_DMA_REQ_FLAG;
    }
#endif
    /* Read the exact block number for the SDIO CMD53. */ 
    if(SDHC_BRD_VENDOR_EXBLKNU(base))
    {
        curConfig->enFlags |= SDHC_HAL_EN_EXACT_BLK_NUM_FLAG;
    }
    SDHC_HAL_GetBootParam(base, &(curConfig->bootParams));
}


/*FUNCTION****************************************************************
 *
 * Function Name: SDHC_HAL_SendCmd
 * Description: Send a command to the card using sdhc
 *
 *END*********************************************************************/
void SDHC_HAL_SendCmd(SDHC_Type * base, const sdhc_hal_cmd_req_t* cmdReq)
{
    assert(base);
    assert(cmdReq);
    SDHC_BWR_BLKATTR_BLKSIZE(base, cmdReq->dataBlkSize);
    SDHC_BWR_BLKATTR_BLKCNT(base, cmdReq->dataBlkCount);
    SDHC_WR_CMDARG(base, cmdReq->arg);
    SDHC_WR_XFERTYP(base, ((cmdReq->index << SDHC_XFERTYP_CMDINX_SHIFT) & SDHC_XFERTYP_CMDINX_MASK)
            | (cmdReq->flags & ( SDHC_XFERTYP_DMAEN_MASK | SDHC_XFERTYP_MSBSEL_MASK | SDHC_XFERTYP_DPSEL_MASK
                | SDHC_XFERTYP_CMDTYP_MASK | SDHC_XFERTYP_BCEN_MASK | SDHC_XFERTYP_CICEN_MASK
                | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP_MASK | SDHC_XFERTYP_DTDSEL_MASK
                | SDHC_XFERTYP_AC12EN_MASK)));
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDHC_HAL_GetAllErrStatus
 * Description: Get the sdhc error status
 *
 *END*********************************************************************/

void SDHC_HAL_GetAllErrStatus(SDHC_Type * base, sdhc_hal_err_type_t errType, uint32_t* errFlags)
{
    assert(base);
    assert(errFlags);
    switch(errType)
    {
    case kAc12Err:
      {
          *errFlags =  SDHC_RD_AC12ERR(base);
          break;
      }
    case kAdmaErr:
      {
          *errFlags =  SDHC_RD_ADMAES(base);
          break;
      }
    default:break;
    }
}

#endif
/*************************************************************************************************
 * EOF
 ************************************************************************************************/
