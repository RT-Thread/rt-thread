/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
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
 * o Neither the name of the copyright holder nor the names of its
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

#include "fsl_emc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Define macros for EMC driver. */
#define EMC_REFRESH_CLOCK_PARAM   (16U)
#define EMC_SDRAM_WAIT_CYCLES  (2000U)
#define EMC_DYNCTL_COLUMNBASE_OFFSET  (0U)
#define EMC_DYNCTL_COLUMNBASE_MASK    (0x3U)
#define EMC_DYNCTL_COLUMNPLUS_OFFSET  (3U)
#define EMC_DYNCTL_COLUMNPLUS_MASK    (0x18U)
#define EMC_DYNCTL_BUSWIDTH_MASK      (0x80U)
#define EMC_DYNCTL_BUSADDRMAP_MASK    (0x20U)
#define EMC_DYNCTL_DEVBANKS_BITS_MASK (0x1cU)
#define EMC_SDRAM_BANKCS_BA0_MASK   (uint32_t)(0x2000)
#define EMC_SDRAM_BANKCS_BA1_MASK   (uint32_t)(0x4000)
#define EMC_SDRAM_BANKCS_BA_MASK    (EMC_SDRAM_BANKCS_BA0_MASK|EMC_SDRAM_BANKCS_BA1_MASK)
#define EMC_DIV_ROUND_UP(n, m)   ((n + m -1)/m)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Get instance number for EMC module.
 *
 * @param base EMC peripheral base address
 */
static uint32_t EMC_GetInstance(EMC_Type *base);

/*!
 * @brief Get the clock cycles of EMC clock.
 * The function is used to calculate the multiple of the 
 * 16 EMCCLKs between the timer_Ns period.
 *
 * @param base EMC peripheral base address
 * @param timer_Ns The timer/period in unit of nanosecond
 * @param plus The plus added to the register settings to reach the calculated cycles.
 * @return The calculated cycles. 
 */
static uint32_t EMC_CalculateTimerCycles(EMC_Type *base, uint32_t timer_Ns, uint32_t plus);

/*!
 * @brief Get the shift value to shift the mode register content by.
 *
 * @param addrMap EMC address map for the dynamic memory configuration. 
 *                It is the bit 14 ~ bit 7 of the EMC_DYNAMICCONFIG.
 * @return The offset value to shift the mode register content by. 
 */
static uint32_t EMC_ModeOffset(uint32_t addrMap);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Pointers to EMC clocks for each instance. */
static const clock_ip_name_t s_EMCClock[FSL_FEATURE_SOC_EMC_COUNT] = EMC_CLOCKS;

/*! @brief Pointers to EMC bases for each instance. */
static EMC_Type *const s_EMCBases[] = EMC_BASE_PTRS;

/*! @brief Define the the start address for each chip controlled by EMC. */
static uint32_t s_EMCDYCSBases[] = EMC_DYCS_ADDRESS;
/*******************************************************************************
 * Code
 ******************************************************************************/

static uint32_t EMC_GetInstance(EMC_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_EMCBases); instance++)
    {
        if (s_EMCBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_EMCBases));

    return instance;
}

static uint32_t EMC_CalculateTimerCycles(EMC_Type *base, uint32_t timer_Ns, uint32_t plus)
{
    uint32_t cycles;

    cycles = CLOCK_GetFreq(kCLOCK_EMC) / EMC_HZ_ONEMHZ * timer_Ns;
    cycles = EMC_DIV_ROUND_UP(cycles, EMC_MILLISECS_ONESEC); /* Round up. */

    /* Decrese according to the plus. */
    if (cycles >= plus)
    {
        cycles = cycles - plus;
    }
    else
    {
        cycles = 0;
    }
    
    return cycles;
}

static uint32_t EMC_ModeOffset(uint32_t addrMap)
{
    uint8_t offset = 0;
    uint32_t columbase = addrMap & EMC_DYNCTL_COLUMNBASE_MASK;

    /* First calculate the column length. */
    if (columbase == 0x10)
    {
        offset = 8;
    }
    else
    {
        if (!columbase)
        {
            offset = 9;          
        }
        else
        {
            offset = 8;
        }
        /* Add column length increase check. */
        if (((addrMap & EMC_DYNCTL_COLUMNPLUS_MASK) >> EMC_DYNCTL_COLUMNPLUS_OFFSET) == 1)
        {
            offset += 1;   
        }
        else if (((addrMap & EMC_DYNCTL_COLUMNPLUS_MASK) >> EMC_DYNCTL_COLUMNPLUS_OFFSET) == 2)
        {
            offset += 2;
        }
        else
        {
            /* To avoid MISRA rule 14.10 error. */
        }        
    }

    /* Add Buswidth/16. */
    if (addrMap & EMC_DYNCTL_BUSWIDTH_MASK)
    {
        offset += 2;
    }
    else
    {
        offset += 1;
    }

    /* Add bank select bit if the sdram address map mode is RBC(row-bank-column) mode. */
    if (!(addrMap & EMC_DYNCTL_BUSADDRMAP_MASK))
    {
        if (!(addrMap & EMC_DYNCTL_DEVBANKS_BITS_MASK))
        {
          offset += 1; 
        }
        else
        {
          offset += 2;
        }
    }

    return offset;
}

void EMC_Init(EMC_Type *base, emc_basic_config_t *config)
{
    /* Enable EMC clock. */
    CLOCK_EnableClock((s_EMCClock[EMC_GetInstance(base)]));

    /* Reset the EMC. */
    SYSCON->PRESETCTRL[2] |= SYSCON_PRESETCTRL_EMC_RESET_MASK;
    SYSCON->PRESETCTRL[2] &= ~ SYSCON_PRESETCTRL_EMC_RESET_MASK;
    
    /* Set the EMC sytem configure. */
    SYSCON->EMCCLKDIV = SYSCON_EMCCLKDIV_DIV(config->emcClkDiv);

    SYSCON->EMCSYSCTRL = SYSCON_EMCSYSCTRL_EMCFBCLKINSEL(config->fbClkSrc);

    /* Set the endian mode. */
    base->CONFIG = config->endian;
    /* Enable the EMC module with normal memory map mode and normal work mode. */
    base->CONTROL = EMC_CONTROL_E_MASK;
}

void EMC_DynamicMemInit(EMC_Type *base, emc_dynamic_timing_config_t *timing, 
        emc_dynamic_chip_config_t *config, uint32_t totalChips)
{
    assert(config);
    assert(timing);
    assert(totalChips <= EMC_DYNAMIC_MEMDEV_NUM);

    uint32_t count;
    uint8_t casLatency;
    uint32_t addr;
    uint32_t offset;
    uint32_t data;
    emc_dynamic_chip_config_t *dynamicConfig = config;

    /* Setting for dynamic memory controller chip independent configuration. */
    for (count = 0; (count < totalChips) && (dynamicConfig != NULL); count ++)
    {
        base->DYNAMIC[dynamicConfig->chipIndex].DYNAMICCONFIG  = EMC_DYNAMIC_DYNAMICCONFIG_MD(dynamicConfig->dynamicDevice) |
            EMC_ADDRMAP(dynamicConfig->devAddrMap);
        /* Abstract CAS latency from the sdram mode reigster setting values. */
        casLatency = (dynamicConfig->sdramModeReg & EMC_SDRAM_MODE_CL_MASK) >> EMC_SDRAM_MODE_CL_SHIFT;
        base->DYNAMIC[dynamicConfig->chipIndex].DYNAMICRASCAS  =  EMC_DYNAMIC_DYNAMICRASCAS_RAS(dynamicConfig->rAS_Nclk) |
        EMC_DYNAMIC_DYNAMICRASCAS_CAS(casLatency);
        
        dynamicConfig ++;
    }

    /* Configure the Dynamic Memory controller timing/latency for all chips. */
    base->DYNAMICREADCONFIG = EMC_DYNAMICREADCONFIG_RD(timing->readConfig);
    base->DYNAMICRP = EMC_CalculateTimerCycles(base, timing->tRp_Ns, 1) & EMC_DYNAMICRP_TRP_MASK;
    base->DYNAMICRAS = EMC_CalculateTimerCycles(base, timing->tRas_Ns, 1) & EMC_DYNAMICRAS_TRAS_MASK;
    base->DYNAMICSREX = EMC_CalculateTimerCycles(base, timing->tSrex_Ns, 1) & EMC_DYNAMICSREX_TSREX_MASK;
    base->DYNAMICAPR = EMC_CalculateTimerCycles(base, timing->tApr_Ns, 1) & EMC_DYNAMICAPR_TAPR_MASK;
    base->DYNAMICDAL = EMC_CalculateTimerCycles(base, timing->tDal_Ns, 0) & EMC_DYNAMICDAL_TDAL_MASK;
    base->DYNAMICWR = EMC_CalculateTimerCycles(base, timing->tWr_Ns, 1) & EMC_DYNAMICWR_TWR_MASK;
    base->DYNAMICRC = EMC_CalculateTimerCycles(base, timing->tRc_Ns, 1) & EMC_DYNAMICRC_TRC_MASK;
    base->DYNAMICRFC = EMC_CalculateTimerCycles(base, timing->tRfc_Ns, 1) &EMC_DYNAMICRFC_TRFC_MASK;
    base->DYNAMICXSR = EMC_CalculateTimerCycles(base, timing->tXsr_Ns, 1) & EMC_DYNAMICXSR_TXSR_MASK;
    base->DYNAMICRRD = EMC_CalculateTimerCycles(base, timing->tRrd_Ns, 1) & EMC_DYNAMICRRD_TRRD_MASK;
    base->DYNAMICMRD = EMC_DYNAMICMRD_TMRD((timing->tMrd_Nclk > 0)?timing->tMrd_Nclk - 1:0);

    /* Initialize the SDRAM.*/ 
    for (count = 0; count < EMC_SDRAM_WAIT_CYCLES;  count ++)
    {
    }
    /* Step 2. issue nop command. */
    base->DYNAMICCONTROL  = 0x00000183;
    for (count = 0; count < EMC_SDRAM_WAIT_CYCLES;  count ++)
    {
    }
    /* Step 3. issue precharge all command. */
    base->DYNAMICCONTROL  = 0x00000103;

    /* Step 4. issue two auto-refresh command. */
    base->DYNAMICREFRESH = 2;
    for (count = 0; count < EMC_SDRAM_WAIT_CYCLES/2; count ++)
    {
    }

    base->DYNAMICREFRESH = EMC_CalculateTimerCycles(base, timing->refreshPeriod_Nanosec, 0)/EMC_REFRESH_CLOCK_PARAM;

    /* Step 5. issue a mode command and set the mode value. */
    base->DYNAMICCONTROL  = 0x00000083;

    /* Calculate the mode settings here and to reach the 8 auto-refresh time requirement. */
    dynamicConfig = config;
    for (count = 0; (count < totalChips) && (dynamicConfig != NULL); count ++)
    {
        /* Get the shift value first. */
        offset = EMC_ModeOffset(dynamicConfig->devAddrMap);
        addr = (s_EMCDYCSBases[dynamicConfig->chipIndex] | 
            ((uint32_t)(dynamicConfig->sdramModeReg & ~EMC_SDRAM_BANKCS_BA_MASK ) << offset));
        /* Set the right mode setting value. */
        data = *(volatile uint32_t *)addr;
        data = data;
        dynamicConfig ++;
    }

    if (config->dynamicDevice)
    {
        /* Add extended mode register if the low-power sdram is used. */
        base->DYNAMICCONTROL  = 0x00000083;
        /* Calculate the mode settings for extended mode register. */
        dynamicConfig = config;
        for (count = 0; (count < totalChips) && (dynamicConfig != NULL); count ++)
        {
            /* Get the shift value first. */
            offset = EMC_ModeOffset(dynamicConfig->devAddrMap);
            addr = (s_EMCDYCSBases[dynamicConfig->chipIndex] | (((uint32_t)(dynamicConfig->sdramExtModeReg & ~EMC_SDRAM_BANKCS_BA_MASK) |
                EMC_SDRAM_BANKCS_BA1_MASK) << offset));
            /* Set the right mode setting value. */
            data = *(volatile uint32_t *)addr;
            data = data;
            dynamicConfig ++;
        }        
    }

    /* Step 6. issue normal operation command. */
    base->DYNAMICCONTROL  = 0x00000000; /* Issue NORMAL command */

    /* The buffer shall be disabled when do the sdram initialization and
     * enabled after the initialization during normal opeation.
     */
    dynamicConfig = config;
    for (count = 0; (count < totalChips) && (dynamicConfig != NULL); count ++)
    {
        base->DYNAMIC[dynamicConfig->chipIndex].DYNAMICCONFIG |= EMC_DYNAMIC_DYNAMICCONFIG_B_MASK;        
        dynamicConfig ++;
    }
}

void EMC_StaticMemInit(EMC_Type *base, uint32_t *extWait_Ns, 
         emc_static_chip_config_t *config, uint32_t totalChips)
{
    assert(config);

    uint32_t count;
    emc_static_chip_config_t *staticConfig = config;

    /* Initialize extended wait. */
    if (extWait_Ns)
    {   
        for (count = 0; (count < totalChips) && (staticConfig != NULL); count ++)
        {
            assert(staticConfig->specailConfig & kEMC_AsynchronosPageEnable);
        }

        base->STATICEXTENDEDWAIT = EMC_CalculateTimerCycles(base, *extWait_Ns, 1);
        staticConfig ++;
    }

    /* Initialize the static memory chip specific configure. */
    staticConfig = config;
    for (count = 0; (count < totalChips) && (staticConfig != NULL); count ++)
    {

        base->STATIC[staticConfig->chipIndex].STATICCONFIG = 
            (staticConfig->specailConfig | staticConfig->memWidth);
        base->STATIC[staticConfig->chipIndex].STATICWAITWEN =
            EMC_CalculateTimerCycles(base, staticConfig->tWaitWriteEn_Ns, 1);
        base->STATIC[staticConfig->chipIndex].STATICWAITOEN = 
            EMC_CalculateTimerCycles(base, staticConfig->tWaitOutEn_Ns, 0);
        base->STATIC[staticConfig->chipIndex].STATICWAITRD = 
            EMC_CalculateTimerCycles(base, staticConfig->tWaitReadNoPage_Ns, 1);
        base->STATIC[staticConfig->chipIndex].STATICWAITPAGE = 
            EMC_CalculateTimerCycles(base, staticConfig->tWaitReadPage_Ns, 1);
        base->STATIC[staticConfig->chipIndex].STATICWAITWR = 
            EMC_CalculateTimerCycles(base, staticConfig->tWaitWrite_Ns, 2);
        base->STATIC[staticConfig->chipIndex].STATICWAITTURN = 
            EMC_CalculateTimerCycles(base, staticConfig->tWaitTurn_Ns, 1);
        
        staticConfig ++;
    }
}   

void EMC_Deinit(EMC_Type *base)
{
    /* Deinit the EMC. */
    base->CONTROL &= ~EMC_CONTROL_E_MASK;

    /* Disable EMC clock. */
    CLOCK_DisableClock(s_EMCClock[EMC_GetInstance(base)]);
}
