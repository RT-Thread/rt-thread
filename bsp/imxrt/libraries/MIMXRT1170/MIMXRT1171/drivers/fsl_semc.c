/*
 * Copyright 2017-2023, 2025 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_semc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.semc"
#endif

/*! @brief Define macros for SEMC driver. */
#define SEMC_IPCOMMANDDATASIZEBYTEMAX (4U)
#define SEMC_IPCOMMANDMAGICKEY        (0xA55A)
#if defined(FSL_FEATURE_SEMC_SUPPORT_SRAM_COUNT) && (FSL_FEATURE_SEMC_SUPPORT_SRAM_COUNT > 0x01U)
#define SEMC_IOCR_PINMUXBITWIDTH (0x4UL)
#else
#define SEMC_IOCR_PINMUXBITWIDTH (0x3UL)
#endif /* FSL_FEATURE_SEMC_SUPPORT_SRAM_COUNT */
#define SEMC_IOCR_NAND_CE   (4UL)
#define SEMC_IOCR_NOR_CE    (5UL)
#define SEMC_IOCR_NOR_CE_A8 (2UL)
#define SEMC_IOCR_PSRAM_CE  (6UL)
#if defined(SEMC_IOCR_PINMUXBITWIDTH) && (SEMC_IOCR_PINMUXBITWIDTH == 0x4UL)
#define SEMC_IOCR_PSRAM_CE_A8 (6UL)
#else
#define SEMC_IOCR_PSRAM_CE_A8 (3UL)
#endif /* SEMC_IOCR_PINMUXBITWIDTH */
#define SEMC_IOCR_DBI_CSX                     (7UL)
#define SEMC_IOCR_DBI_CSX_A8                  (4UL)
#define SEMC_NORFLASH_SRAM_ADDR_PORTWIDTHBASE (24U)
#define SEMC_NORFLASH_SRAM_ADDR_PORTWIDTHMAX  (28U)
#define SEMC_BMCR0_TYPICAL_WQOS               (5U)
#define SEMC_BMCR0_TYPICAL_WAGE               (8U)
#define SEMC_BMCR0_TYPICAL_WSH                (0x40U)
#define SEMC_BMCR0_TYPICAL_WRWS               (0x10U)
#define SEMC_BMCR1_TYPICAL_WQOS               (5U)
#define SEMC_BMCR1_TYPICAL_WAGE               (8U)
#define SEMC_BMCR1_TYPICAL_WPH                (0x60U)
#define SEMC_BMCR1_TYPICAL_WBR                (0x40U)
#define SEMC_BMCR1_TYPICAL_WRWS               (0x24U)
#define SEMC_STARTADDRESS                     (0x80000000UL)
#define SEMC_ENDADDRESS                       (0xDFFFFFFFUL)
#define SEMC_BR_MEMSIZE_MIN                   (4U)
#define SEMC_BR_MEMSIZE_OFFSET                (2U)
#define SEMC_BR_MEMSIZE_MAX                   (4UL * 1024UL * 1024UL)
#define SEMC_SDRAM_MODESETCAL_OFFSET          (4U)
#define SEMC_BR_REG_NUM                       (9U)
#define SEMC_BYTE_NUMBIT                      (8U)

#ifdef SEMC_DBICR1_REH_MASK
#if ((SEMC_DBICR1_REH_MASK >> SEMC_DBICR1_REH_SHIFT) == 0x1U)
#define SEMC_DBICR1_REH_WIDTH 1U
#elif ((SEMC_DBICR1_REH_MASK >> SEMC_DBICR1_REH_SHIFT) == 0x3U)
#define SEMC_DBICR1_REH_WIDTH 2U
#elif ((SEMC_DBICR1_REH_MASK >> SEMC_DBICR1_REH_SHIFT) == 0x7U)
#define SEMC_DBICR1_REH_WIDTH 3U
#elif ((SEMC_DBICR1_REH_MASK >> SEMC_DBICR1_REH_SHIFT) == 0xFU)
#define SEMC_DBICR1_REH_WIDTH 4U
#elif ((SEMC_DBICR1_REH_MASK >> SEMC_DBICR1_REH_SHIFT) == 0x1FU)
#define SEMC_DBICR1_REH_WIDTH 5U
#elif ((SEMC_DBICR1_REH_MASK >> SEMC_DBICR1_REH_SHIFT) == 0x3FU)
#define SEMC_DBICR1_REH_WIDTH 6U
#elif ((SEMC_DBICR1_REH_MASK >> SEMC_DBICR1_REH_SHIFT) == 0x7FU)
#define SEMC_DBICR1_REH_WIDTH 7U
#elif ((SEMC_DBICR1_REH_MASK >> SEMC_DBICR1_REH_SHIFT) == 0xFFU)
#define SEMC_DBICR1_REH_WIDTH 8U
#else
#error SEMC_DBICR1_REH width not supported
#endif
#endif /* SEMC_DBICR1_REH_MASK */

#ifdef SEMC_DBICR1_REL_MASK
#if ((SEMC_DBICR1_REL_MASK >> SEMC_DBICR1_REL_SHIFT) == 0x1U)
#define SEMC_DBICR1_REL_WIDTH 1U
#elif ((SEMC_DBICR1_REL_MASK >> SEMC_DBICR1_REL_SHIFT) == 0x3U)
#define SEMC_DBICR1_REL_WIDTH 2U
#elif ((SEMC_DBICR1_REL_MASK >> SEMC_DBICR1_REL_SHIFT) == 0x7U)
#define SEMC_DBICR1_REL_WIDTH 3U
#elif ((SEMC_DBICR1_REL_MASK >> SEMC_DBICR1_REL_SHIFT) == 0xFU)
#define SEMC_DBICR1_REL_WIDTH 4U
#elif ((SEMC_DBICR1_REL_MASK >> SEMC_DBICR1_REL_SHIFT) == 0x1FU)
#define SEMC_DBICR1_REL_WIDTH 5U
#elif ((SEMC_DBICR1_REL_MASK >> SEMC_DBICR1_REL_SHIFT) == 0x3FU)
#define SEMC_DBICR1_REL_WIDTH 6U
#elif ((SEMC_DBICR1_REL_MASK >> SEMC_DBICR1_REL_SHIFT) == 0x7FU)
#define SEMC_DBICR1_REL_WIDTH 7U
#elif ((SEMC_DBICR1_REL_MASK >> SEMC_DBICR1_REL_SHIFT) == 0xFFU)
#define SEMC_DBICR1_REL_WIDTH 8U
#else
#error SEMC_DBICR1_REL width not supported
#endif
#endif /* SEMC_DBICR1_REL_MASK */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Get instance number for SEMC module.
 *
 * @param base SEMC peripheral base address
 */
static uint32_t SEMC_GetInstance(SEMC_Type *base);

/*!
 * @brief Covert the input memory size to internal register set value.
 *
 * @param size_kbytes SEMC memory size in unit of kbytes.
 * @param sizeConverted SEMC converted memory size to 0 ~ 0x1F.
 * @return Execution status.
 */
static status_t SEMC_CovertMemorySize(uint32_t size_kbytes, uint8_t *sizeConverted);

/*!
 * @brief Covert the external timing nanosecond to internal clock cycle.
 *
 * @param time_ns   SEMC external time interval in unit of nanosecond.
 * @param clkSrc_Hz SEMC clock source frequency.
 * @return The changed internal clock cycle.
 */
static uint8_t SEMC_ConvertTiming(uint32_t time_ns, uint32_t clkSrc_Hz);

/*!
 * @brief Configure IP command.
 *
 * @param base SEMC peripheral base address.
 * @param size_bytes SEMC IP command data size.
 * @return Execution status.
 */
static status_t SEMC_ConfigureIPCommand(SEMC_Type *base, uint8_t size_bytes);

/*!
 * @brief Check if the IP command has finished.
 *
 * @param base SEMC peripheral base address.
 * @return Execution status.
 */
static status_t SEMC_IsIPCommandDone(SEMC_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to SEMC clocks for each instance. */
static const clock_ip_name_t s_semcClock[FSL_FEATURE_SOC_SEMC_COUNT] = SEMC_CLOCKS;
#if (defined(SEMC_EXSC_CLOCKS))
static const clock_ip_name_t s_semcExtClock[FSL_FEATURE_SOC_SEMC_COUNT] = SEMC_EXSC_CLOCKS;
#endif /* SEMC_EXSC_CLOCKS */
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*! @brief Pointers to SEMC bases for each instance. */
static SEMC_Type *const s_semcBases[] = SEMC_BASE_PTRS;
/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t SEMC_GetInstance(SEMC_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0UL; instance < ARRAY_SIZE(s_semcBases); instance++)
    {
        if (MSDK_REG_SECURE_ADDR(s_semcBases[instance]) == MSDK_REG_SECURE_ADDR(base))
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_semcBases));

    return instance;
}

static status_t SEMC_CovertMemorySize(uint32_t size_kbytes, uint8_t *sizeConverted)
{
    assert(sizeConverted != NULL);
    uint32_t memsize;
    status_t status = kStatus_Success;

    if ((size_kbytes < SEMC_BR_MEMSIZE_MIN) || (size_kbytes > SEMC_BR_MEMSIZE_MAX))
    {
        status = kStatus_SEMC_InvalidMemorySize;
    }
    else
    {
        *sizeConverted = 0U;
        memsize        = size_kbytes / 8U;
        while (memsize != 0x00U)
        {
            memsize >>= 1U;
            (*sizeConverted)++;
        }
    }

    return status;
}

static uint8_t SEMC_ConvertTiming(uint32_t time_ns, uint32_t clkSrc_Hz)
{
    assert(clkSrc_Hz != 0x00U);

    uint8_t clockCycles = 0;
    uint32_t tClk_ps;

    clkSrc_Hz /= 1000000U;
    /* Using ps for high resolution */
    tClk_ps = 1000000U / clkSrc_Hz;

    while (tClk_ps * clockCycles < time_ns * 1000U)
    {
        clockCycles++;
    }

    return (clockCycles == 0x00U) ? clockCycles : (clockCycles - 0x01U);
}

static status_t SEMC_ConfigureIPCommand(SEMC_Type *base, uint8_t size_bytes)
{
    status_t status = kStatus_Success;

    if ((size_bytes > SEMC_IPCOMMANDDATASIZEBYTEMAX) || (size_bytes == 0x00U))
    {
        status = kStatus_SEMC_InvalidIpcmdDataSize;
    }
    else
    {
        /* Set data size. */
        /* Note: It is better to set data size as the device data port width when transferring
         *    device command data. But for device memory data transfer, it can be set freely.
         * Note: If the data size is greater than data port width, for example, datsz = 4, data port = 16bit,
         *    then the 4-byte data transfer will be split into two 2-byte transfers, the slave address
         *    will be switched automatically according to connected device type*/
        base->IPCR1 = SEMC_IPCR1_DATSZ(size_bytes);
        /* Clear data size. */
        base->IPCR2 = 0;
        /* Set data size. */
        if (size_bytes < 4U)
        {
            base->IPCR2 |= SEMC_IPCR2_BM3_MASK;
        }
        if (size_bytes < 3U)
        {
            base->IPCR2 |= SEMC_IPCR2_BM2_MASK;
        }
        if (size_bytes < 2U)
        {
            base->IPCR2 |= SEMC_IPCR2_BM1_MASK;
        }
    }

    return status;
}

static status_t SEMC_IsIPCommandDone(SEMC_Type *base)
{
    status_t status = kStatus_Success;

    /* Poll status bit till command is done*/
    while ((base->INTR & (uint32_t)SEMC_INTR_IPCMDDONE_MASK) == 0x00U)
    {
    };

    /* Check error status */
    if ((base->INTR & (uint32_t)SEMC_INTR_IPCMDERR_MASK) != 0x00U)
    {
        base->INTR = SEMC_INTR_IPCMDERR_MASK;
        status = kStatus_SEMC_IpCommandExecutionError;
    }

    /* Clear status bit */
    base->INTR = SEMC_INTR_IPCMDDONE_MASK;

    return status;
}

/*!
 * brief Gets the SEMC default basic configuration structure.
 *
 * The purpose of this API is to get the default SEMC
 * configure structure for SEMC_Init(). User may use the initialized
 * structure unchanged in SEMC_Init(), or modify some fields of the
 * structure before calling SEMC_Init().
 * Example:
   code
   semc_config_t config;
   SEMC_GetDefaultConfig(&config);
   endcode
 * param config The SEMC configuration structure pointer.
 */
void SEMC_GetDefaultConfig(semc_config_t *config)
{
    assert(config != NULL);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->queueWeight.queueaEnable          = true;
    semc_queuea_weight_struct_t *queueaWeight = &(config->queueWeight.queueaWeight.queueaConfig);
    config->queueWeight.queuebEnable          = true;
    semc_queueb_weight_struct_t *queuebWeight = &(config->queueWeight.queuebWeight.queuebConfig);

    /* Get default settings. */
    config->dqsMode          = kSEMC_Loopbackinternal;
    config->cmdTimeoutCycles = 0xFF;
    config->busTimeoutCycles = 0x1F;

    queueaWeight->qos              = SEMC_BMCR0_TYPICAL_WQOS;
    queueaWeight->aging            = SEMC_BMCR0_TYPICAL_WAGE;
    queueaWeight->slaveHitNoswitch = SEMC_BMCR0_TYPICAL_WSH;
    queueaWeight->slaveHitSwitch   = SEMC_BMCR0_TYPICAL_WRWS;
    queuebWeight->qos              = SEMC_BMCR1_TYPICAL_WQOS;
    queuebWeight->aging            = SEMC_BMCR1_TYPICAL_WAGE;
    queuebWeight->weightPagehit    = SEMC_BMCR1_TYPICAL_WPH;
    queuebWeight->slaveHitNoswitch = SEMC_BMCR1_TYPICAL_WRWS;
    queuebWeight->bankRotation     = SEMC_BMCR1_TYPICAL_WBR;
}

/*!
 * brief Initializes SEMC.
 * This function ungates the SEMC clock and initializes SEMC.
 * This function must be called before calling any other SEMC driver functions.
 *
 * param base SEMC peripheral base address.
 * param configure The SEMC configuration structure pointer.
 */
void SEMC_Init(SEMC_Type *base, semc_config_t *configure)
{
    assert(configure != NULL);

    uint8_t index = 0;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Un-gate sdram controller clock. */
    CLOCK_EnableClock(s_semcClock[SEMC_GetInstance(base)]);
#if (defined(SEMC_EXSC_CLOCKS))
    CLOCK_EnableClock(s_semcExtClock[SEMC_GetInstance(base)]);
#endif /* SEMC_EXSC_CLOCKS */
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Initialize all BR to zero due to the default base address set. */
    for (index = 0; index < SEMC_BR_REG_NUM; index++)
    {
        base->BR[index] = 0;
    }

    /* Software reset for SEMC internal logical . */
    base->MCR = SEMC_MCR_SWRST_MASK;
    while ((base->MCR & (uint32_t)SEMC_MCR_SWRST_MASK) != 0x00U)
    {
    }

    /* Configure, disable module first. */
    base->MCR |= SEMC_MCR_MDIS_MASK | SEMC_MCR_BTO(configure->busTimeoutCycles) |
                 SEMC_MCR_CTO(configure->cmdTimeoutCycles) | SEMC_MCR_DQSMD(configure->dqsMode);

    if (configure->queueWeight.queueaEnable == true)
    {
        /* Configure Queue A for AXI bus access to SDRAM, NAND, NOR, SRAM and DBI slaves.*/
        base->BMCR0 = (uint32_t)(configure->queueWeight.queueaWeight.queueaValue);
    }
    else
    {
        base->BMCR0 = 0x00U;
    }

    if (configure->queueWeight.queuebEnable == true)
    {
        /* Configure Queue B for AXI bus access to SDRAM slave. */
        base->BMCR1 = (uint32_t)(configure->queueWeight.queuebWeight.queuebValue);
    }
    else
    {
        base->BMCR1 = 0x00U;
    }

    /* Enable SEMC. */
    base->MCR &= ~SEMC_MCR_MDIS_MASK;
}

/*!
 * brief Deinitializes the SEMC module and gates the clock.
 * This function gates the SEMC clock. As a result, the SEMC
 * module doesn't work after calling this function.
 *
 * param base SEMC peripheral base address.
 */
void SEMC_Deinit(SEMC_Type *base)
{
    /* Disable module.  Check there is no pending command before disable module.  */
    while ((base->STS0 & (uint32_t)SEMC_STS0_IDLE_MASK) == 0x00U)
    {
        ;
    }

    base->MCR |= SEMC_MCR_MDIS_MASK | SEMC_MCR_SWRST_MASK;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable SDRAM clock. */
    CLOCK_DisableClock(s_semcClock[SEMC_GetInstance(base)]);
#if (defined(SEMC_EXSC_CLOCKS))
    CLOCK_DisableClock(s_semcExtClock[SEMC_GetInstance(base)]);
#endif /* SEMC_EXSC_CLOCKS */
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Configures SDRAM controller in SEMC.
 *
 * param base SEMC peripheral base address.
 * param cs The chip selection.
 * param config The sdram configuration.
 * param clkSrc_Hz The SEMC clock frequency.
 */
status_t SEMC_ConfigureSDRAM(SEMC_Type *base, semc_sdram_cs_t cs, semc_sdram_config_t *config, uint32_t clkSrc_Hz)
{
    assert(config != NULL);
    assert(clkSrc_Hz > 0x00U);
    assert(config->refreshBurstLen > 0x00U);

    uint8_t memsize;
    uint8_t times;
    status_t result   = kStatus_Success;
    uint16_t prescale = (uint16_t)(config->tPrescalePeriod_Ns / 16U / (1000000000U / clkSrc_Hz));
    uint32_t refresh;
    uint32_t urgentRef;
    uint32_t idle;
    uint32_t mode;
    uint32_t timing;

    if ((config->address < SEMC_STARTADDRESS) || (config->address > SEMC_ENDADDRESS))
    {
        return kStatus_SEMC_InvalidBaseAddress;
    }

    if (config->csxPinMux == kSEMC_MUXA8)
    {
        return kStatus_SEMC_InvalidSwPinmuxSelection;
    }

    if (prescale > 256U)
    {
        return kStatus_SEMC_InvalidTimerSetting;
    }

    refresh   = config->refreshPeriod_nsPerRow / config->tPrescalePeriod_Ns;
    urgentRef = config->refreshUrgThreshold / config->tPrescalePeriod_Ns;
    idle      = config->tIdleTimeout_Ns / config->tPrescalePeriod_Ns;

    uint32_t iocReg = base->IOCR & (~(SEMC_IOCR_PINMUXBITWIDTH << (uint32_t)config->csxPinMux));

    /* Base control. */
    result = SEMC_CovertMemorySize(config->memsize_kbytes, &memsize);
    if (result != kStatus_Success)
    {
        return result;
    }

    base->BR[cs] = (config->address & SEMC_BR_BA_MASK) | SEMC_BR_MS(memsize) | SEMC_BR_VLD_MASK;

#if defined(FSL_FEATURE_SEMC_SDRAM_SUPPORT_COLUMN_ADDRESS_8BIT) && (FSL_FEATURE_SEMC_SDRAM_SUPPORT_COLUMN_ADDRESS_8BIT)
    if (kSEMC_SdramColunm_8bit == config->columnAddrBitNum)
    {
        base->SDRAMCR0 = SEMC_SDRAMCR0_PS(config->portSize) | SEMC_SDRAMCR0_BL(config->burstLen) |
                         SEMC_SDRAMCR0_COL8(true) | SEMC_SDRAMCR0_CL(config->casLatency);
    }
    else
#endif /* FSL_FEATURE_SEMC_SDRAM_SUPPORT_COLUMN_ADDRESS_8BIT */
    {
        base->SDRAMCR0 = SEMC_SDRAMCR0_PS(config->portSize) | SEMC_SDRAMCR0_BL(config->burstLen) |
                         SEMC_SDRAMCR0_COL(config->columnAddrBitNum) | SEMC_SDRAMCR0_CL(config->casLatency);
    }

    /* IOMUX setting. */
    if (cs != kSEMC_SDRAM_CS0)
    {
        base->IOCR = iocReg | ((uint32_t)cs << (uint32_t)config->csxPinMux);
    }

    base->IOCR &= ~SEMC_IOCR_MUX_A8_MASK;

#if defined(FSL_FEATURE_SEMC_HAS_DELAY_CHAIN_CONTROL) && (FSL_FEATURE_SEMC_HAS_DELAY_CHAIN_CONTROL)
    uint32_t tempDelayChain = base->DCCR;

    tempDelayChain &= ~(SEMC_DCCR_SDRAMVAL_MASK | SEMC_DCCR_SDRAMEN_MASK);
    /* Configure delay chain. */
    base->DCCR = tempDelayChain | SEMC_DCCR_SDRAMVAL((uint32_t)config->delayChain - 0x01U) | SEMC_DCCR_SDRAMEN_MASK;
#endif /* FSL_FEATURE_SEMC_HAS_DELAY_CHAIN_CONTROL */

    timing = SEMC_SDRAMCR1_PRE2ACT(SEMC_ConvertTiming(config->tPrecharge2Act_Ns, clkSrc_Hz));
    timing |= SEMC_SDRAMCR1_ACT2RW(SEMC_ConvertTiming(config->tAct2ReadWrite_Ns, clkSrc_Hz));
    timing |= SEMC_SDRAMCR1_RFRC(SEMC_ConvertTiming(config->tRefreshRecovery_Ns, clkSrc_Hz));
    timing |= SEMC_SDRAMCR1_WRC(SEMC_ConvertTiming(config->tWriteRecovery_Ns, clkSrc_Hz));
    timing |= SEMC_SDRAMCR1_CKEOFF(SEMC_ConvertTiming(config->tCkeOff_Ns, clkSrc_Hz));
    timing |= SEMC_SDRAMCR1_ACT2PRE(SEMC_ConvertTiming(config->tAct2Prechage_Ns, clkSrc_Hz));
    /* SDRAMCR1 timing setting. */
    base->SDRAMCR1 = timing;

    timing = SEMC_SDRAMCR2_SRRC(SEMC_ConvertTiming(config->tSelfRefRecovery_Ns, clkSrc_Hz));
    timing |= SEMC_SDRAMCR2_REF2REF(SEMC_ConvertTiming(config->tRefresh2Refresh_Ns, clkSrc_Hz));
    timing |= SEMC_SDRAMCR2_ACT2ACT(SEMC_ConvertTiming(config->tAct2Act_Ns, clkSrc_Hz)) | SEMC_SDRAMCR2_ITO(idle);
    /* SDRAMCR2 timing setting. */
    base->SDRAMCR2 = timing;

    /* SDRAMCR3 timing setting. */
    base->SDRAMCR3 = SEMC_SDRAMCR3_REBL((uint32_t)config->refreshBurstLen - 1UL) |
                     /* N * 16 * 1s / clkSrc_Hz = config->tPrescalePeriod_Ns */
                     SEMC_SDRAMCR3_PRESCALE(prescale) | SEMC_SDRAMCR3_RT(refresh - 1UL) | SEMC_SDRAMCR3_UT(urgentRef);

    SEMC->IPCR1 = 0x2U;
    SEMC->IPCR2 = 0U;

    result =
        SEMC_SendIPCommand(base, kSEMC_MemType_SDRAM, config->address, (uint32_t)kSEMC_SDRAMCM_Prechargeall, 0, NULL);
    if (result != kStatus_Success)
    {
        return result;
    }

    /* Generally, SDRAM requires 2 refresh cycles before and after setting the mode register. If the SDRAM used has special requirements, 
    *  please add autofreshTimes configuration in the initialization block of SDRAM */
    times = ((config->autofreshTimes != 0U) ? config->autofreshTimes : 2U);
    for(uint8_t count = 0U; count < times; count++)
    {
        result =
            SEMC_SendIPCommand(base, kSEMC_MemType_SDRAM, config->address, (uint32_t)kSEMC_SDRAMCM_AutoRefresh, 0, NULL);
        if (result != kStatus_Success)
        {
            return result;
        }
    }

    /* Mode setting value. */
    mode = (uint32_t)config->burstLen | (((uint32_t)config->casLatency) << SEMC_SDRAM_MODESETCAL_OFFSET);
    result =
        SEMC_SendIPCommand(base, kSEMC_MemType_SDRAM, config->address, (uint32_t)kSEMC_SDRAMCM_Modeset, mode, NULL);
    if (result != kStatus_Success)
    {
        return result;
    }
    /* Enables refresh */
    base->SDRAMCR3 |= SEMC_SDRAMCR3_REN_MASK;

    return kStatus_Success;
}

/*!
 * brief Configures NAND controller in SEMC.
 *
 * param base SEMC peripheral base address.
 * param config The nand configuration.
 * param clkSrc_Hz The SEMC clock frequency.
 */
status_t SEMC_ConfigureNAND(SEMC_Type *base, semc_nand_config_t *config, uint32_t clkSrc_Hz)
{
    assert(config != NULL);
    assert(config->timingConfig != NULL);

    uint8_t memsize;
    status_t result;
    uint32_t timing;

    if ((config->axiAddress < SEMC_STARTADDRESS) || (config->axiAddress > SEMC_ENDADDRESS))
    {
        return kStatus_SEMC_InvalidBaseAddress;
    }

    if (config->cePinMux == kSEMC_MUXRDY)
    {
        return kStatus_SEMC_InvalidSwPinmuxSelection;
    }

    /* Disable SEMC module during configuring control registers. */
    base->MCR |= SEMC_MCR_MDIS_MASK;

    uint32_t iocReg =
        base->IOCR & (~((SEMC_IOCR_PINMUXBITWIDTH << (uint32_t)config->cePinMux) | SEMC_IOCR_MUX_RDY_MASK));

    /* Base control. */
    if (config->rdyactivePolarity == kSEMC_RdyActivehigh)
    {
        base->MCR |= SEMC_MCR_WPOL1_MASK;
    }
    else
    {
        base->MCR &= ~SEMC_MCR_WPOL1_MASK;
    }
    result = SEMC_CovertMemorySize(config->axiMemsize_kbytes, &memsize);
    if (result != kStatus_Success)
    {
        return result;
    }
    base->BR[4] = (config->axiAddress & SEMC_BR_BA_MASK) | SEMC_BR_MS(memsize) | SEMC_BR_VLD_MASK;

    result = SEMC_CovertMemorySize(config->ipgMemsize_kbytes, &memsize);
    if (result != kStatus_Success)
    {
        return result;
    }
    base->BR[8] = (config->ipgAddress & SEMC_BR_BA_MASK) | SEMC_BR_MS(memsize) | SEMC_BR_VLD_MASK;

    /* IOMUX setting. */
    if ((uint32_t)config->cePinMux != 0x00U)
    {
        base->IOCR = iocReg | (SEMC_IOCR_NAND_CE << (uint32_t)config->cePinMux);
    }
    else
    {
        base->IOCR = iocReg | (1UL << (uint32_t)config->cePinMux);
    }

    base->NANDCR0 = SEMC_NANDCR0_PS(config->portSize) | SEMC_NANDCR0_BL(config->burstLen) |
                    SEMC_NANDCR0_EDO(config->edoModeEnabled) | SEMC_NANDCR0_COL(config->columnAddrBitNum);

    timing = SEMC_NANDCR1_CES(SEMC_ConvertTiming(config->timingConfig->tCeSetup_Ns, clkSrc_Hz));
    timing |= SEMC_NANDCR1_CEH(SEMC_ConvertTiming(config->timingConfig->tCeHold_Ns, clkSrc_Hz));
    timing |= SEMC_NANDCR1_WEL(SEMC_ConvertTiming(config->timingConfig->tWeLow_Ns, clkSrc_Hz));
    timing |= SEMC_NANDCR1_WEH(SEMC_ConvertTiming(config->timingConfig->tWeHigh_Ns, clkSrc_Hz));
    timing |= SEMC_NANDCR1_REL(SEMC_ConvertTiming(config->timingConfig->tReLow_Ns, clkSrc_Hz));
    timing |= SEMC_NANDCR1_REH(SEMC_ConvertTiming(config->timingConfig->tReHigh_Ns, clkSrc_Hz));
    timing |= SEMC_NANDCR1_TA(SEMC_ConvertTiming(config->timingConfig->tTurnAround_Ns, clkSrc_Hz));
    timing |= SEMC_NANDCR1_CEITV(SEMC_ConvertTiming(config->timingConfig->tCeInterval_Ns, clkSrc_Hz));
    /* NANDCR1 timing setting. */
    base->NANDCR1 = timing;

    timing = SEMC_NANDCR2_TWHR(SEMC_ConvertTiming(config->timingConfig->tWehigh2Relow_Ns, clkSrc_Hz));
    timing |= SEMC_NANDCR2_TRHW(SEMC_ConvertTiming(config->timingConfig->tRehigh2Welow_Ns, clkSrc_Hz));
    timing |= SEMC_NANDCR2_TADL(SEMC_ConvertTiming(config->timingConfig->tAle2WriteStart_Ns, clkSrc_Hz));
    timing |= SEMC_NANDCR2_TRR(SEMC_ConvertTiming(config->timingConfig->tReady2Relow_Ns, clkSrc_Hz));
    timing |= SEMC_NANDCR2_TWB(SEMC_ConvertTiming(config->timingConfig->tWehigh2Busy_Ns, clkSrc_Hz));

    /* NANDCR2 timing setting. */
    base->NANDCR2 = timing;

    /* NANDCR3 timing setting. */
    base->NANDCR3 = (uint32_t)config->arrayAddrOption;

    /* Enables SEMC module after configuring control registers completely. */
    base->MCR &= ~SEMC_MCR_MDIS_MASK;

    return kStatus_Success;
}

/*!
 * brief Configures NOR controller in SEMC.
 *
 * param base SEMC peripheral base address.
 * param config The nor configuration.
 * param clkSrc_Hz The SEMC clock frequency.
 */
status_t SEMC_ConfigureNOR(SEMC_Type *base, semc_nor_config_t *config, uint32_t clkSrc_Hz)
{
    assert(config != NULL);

    uint8_t memsize;
    status_t result;
    uint32_t timing;

    if ((config->address < SEMC_STARTADDRESS) || (config->address > SEMC_ENDADDRESS))
    {
        return kStatus_SEMC_InvalidBaseAddress;
    }

    uint32_t iocReg = base->IOCR & (~(SEMC_IOCR_PINMUXBITWIDTH << (uint32_t)config->cePinMux));
    uint32_t muxCe  = (config->cePinMux == kSEMC_MUXRDY) ?
                         (SEMC_IOCR_NOR_CE - 1U) :
                         ((config->cePinMux == kSEMC_MUXA8) ? SEMC_IOCR_NOR_CE_A8 : SEMC_IOCR_NOR_CE);

    /* IOMUX setting. */
    base->IOCR = iocReg | (muxCe << (uint32_t)config->cePinMux);
    /* Address bit setting. */
    if (config->addrPortWidth > SEMC_NORFLASH_SRAM_ADDR_PORTWIDTHBASE)
    {
        /* Address bit 24 (A24) */
        base->IOCR &= ~(uint32_t)SEMC_IOCR_MUX_CSX0_MASK;
        if (config->cePinMux == kSEMC_MUXCSX0)
        {
            return kStatus_SEMC_InvalidSwPinmuxSelection;
        }

        if (config->addrPortWidth >= (SEMC_NORFLASH_SRAM_ADDR_PORTWIDTHBASE + 2U))
        {
            /* Address bit 25 (A25) */
            base->IOCR &= ~(uint32_t)SEMC_IOCR_MUX_CSX1_MASK;
            if (config->cePinMux == kSEMC_MUXCSX1)
            {
                return kStatus_SEMC_InvalidSwPinmuxSelection;
            }
        }
        if (config->addrPortWidth >= (SEMC_NORFLASH_SRAM_ADDR_PORTWIDTHBASE + 3U))
        {
            /* Address bit 26 (A26) */
            base->IOCR &= ~(uint32_t)SEMC_IOCR_MUX_CSX2_MASK;
            if (config->cePinMux == kSEMC_MUXCSX2)
            {
                return kStatus_SEMC_InvalidSwPinmuxSelection;
            }
        }
        if (config->addrPortWidth >= (SEMC_NORFLASH_SRAM_ADDR_PORTWIDTHBASE + 4U))
        {
            if (config->addr27 == kSEMC_NORA27_MUXCSX3)
            {
                /* Address bit 27 (A27) */
                base->IOCR &= ~(uint32_t)SEMC_IOCR_MUX_CSX3_MASK;
            }
            else if (config->addr27 == kSEMC_NORA27_MUXRDY)
            {
                base->IOCR |= SEMC_IOCR_MUX_RDY_MASK;
            }
            else
            {
                return kStatus_SEMC_InvalidSwPinmuxSelection;
            }
            if (config->cePinMux == kSEMC_MUXCSX3)
            {
                return kStatus_SEMC_InvalidSwPinmuxSelection;
            }
        }
        if (config->addrPortWidth > SEMC_NORFLASH_SRAM_ADDR_PORTWIDTHMAX)
        {
            return kStatus_SEMC_InvalidAddressPortWidth;
        }
    }

    /* Base control. */
    if (config->rdyactivePolarity == kSEMC_RdyActivehigh)
    {
        base->MCR |= SEMC_MCR_WPOL0_MASK;
    }
    else
    {
        base->MCR &= ~SEMC_MCR_WPOL0_MASK;
    }
    result = SEMC_CovertMemorySize(config->memsize_kbytes, &memsize);
    if (result != kStatus_Success)
    {
        return result;
    }
    base->BR[5]  = (config->address & SEMC_BR_BA_MASK) | SEMC_BR_MS(memsize) | SEMC_BR_VLD_MASK;
    base->NORCR0 = SEMC_NORCR0_PS(config->portSize) | SEMC_NORCR0_BL(config->burstLen) |
                   SEMC_NORCR0_AM(config->addrMode) | SEMC_NORCR0_ADVP(config->advActivePolarity) |
                   SEMC_NORCR0_COL(config->columnAddrBitNum);

#if defined(FSL_FEATURE_SEMC_HAS_DELAY_CHAIN_CONTROL) && (FSL_FEATURE_SEMC_HAS_DELAY_CHAIN_CONTROL)
    uint32_t tempDelayChain = base->DCCR;

    tempDelayChain &= ~(SEMC_DCCR_NORVAL_MASK | SEMC_DCCR_NOREN_MASK);
    /* Configure delay chain. */
    base->DCCR = tempDelayChain | SEMC_DCCR_NORVAL((uint32_t)config->delayChain - 0x01U) | SEMC_DCCR_NOREN_MASK;
#endif /* FSL_FEATURE_SEMC_HAS_DELAY_CHAIN_CONTROL */

    timing = SEMC_NORCR1_CES(SEMC_ConvertTiming(config->tCeSetup_Ns, clkSrc_Hz));
    timing |= SEMC_NORCR1_CEH(SEMC_ConvertTiming(config->tCeHold_Ns, clkSrc_Hz));
    timing |= SEMC_NORCR1_AS(SEMC_ConvertTiming(config->tAddrSetup_Ns, clkSrc_Hz));
    timing |= SEMC_NORCR1_AH(SEMC_ConvertTiming(config->tAddrHold_Ns, clkSrc_Hz));
    timing |= SEMC_NORCR1_WEL(SEMC_ConvertTiming(config->tWeLow_Ns, clkSrc_Hz));
    timing |= SEMC_NORCR1_WEH(SEMC_ConvertTiming(config->tWeHigh_Ns, clkSrc_Hz));
    timing |= SEMC_NORCR1_REL(SEMC_ConvertTiming(config->tReLow_Ns, clkSrc_Hz));
    timing |= SEMC_NORCR1_REH(SEMC_ConvertTiming(config->tReHigh_Ns, clkSrc_Hz));

    /* NORCR1 timing setting. */
    base->NORCR1 = timing;

    timing = SEMC_NORCR2_CEITV(SEMC_ConvertTiming(config->tCeInterval_Ns, clkSrc_Hz));
#if defined(FSL_FEATURE_SEMC_HAS_NOR_WDS_TIME) && (FSL_FEATURE_SEMC_HAS_NOR_WDS_TIME)
    timing |= SEMC_NORCR2_WDS(SEMC_ConvertTiming(config->tWriteSetup_Ns, clkSrc_Hz));
#endif /* FSL_FEATURE_SEMC_HAS_NOR_WDS_TIME */
#if defined(FSL_FEATURE_SEMC_HAS_NOR_WDH_TIME) && (FSL_FEATURE_SEMC_HAS_NOR_WDH_TIME)
    timing |= SEMC_NORCR2_WDH(SEMC_ConvertTiming(config->tWriteHold_Ns, clkSrc_Hz));
#endif /* FSL_FEATURE_SEMC_HAS_NOR_WDH_TIME */
    timing |= SEMC_NORCR2_TA(SEMC_ConvertTiming(config->tTurnAround_Ns, clkSrc_Hz));
    timing |= SEMC_NORCR2_AWDH((uint32_t)SEMC_ConvertTiming(config->tAddr2WriteHold_Ns, clkSrc_Hz) + 0x01UL);
#if defined(FSL_FEATURE_SEMC_HAS_NOR_LC_TIME) && (FSL_FEATURE_SEMC_HAS_NOR_LC_TIME)
    timing |= SEMC_NORCR2_LC(config->latencyCount);
#endif
#if defined(FSL_FEATURE_SEMC_HAS_NOR_RD_TIME) && (FSL_FEATURE_SEMC_HAS_NOR_RD_TIME)
    timing |= SEMC_NORCR2_RD((uint32_t)config->readCycle - 0x01UL);
#endif

    /* NORCR2 timing setting. */
    base->NORCR2 = timing;

    return SEMC_ConfigureIPCommand(base, ((uint8_t)config->portSize + 1U));
}

/*!
 * brief Configures SRAM controller in SEMC, which can be used only for specific chip selection CS0.
 *
 * param base SEMC peripheral base address.
 * param config The sram configuration.
 * param clkSrc_Hz The SEMC clock frequency.
 */
status_t SEMC_ConfigureSRAM(SEMC_Type *base, semc_sram_config_t *config, uint32_t clkSrc_Hz)
{
    return SEMC_ConfigureSRAMWithChipSelection(base, kSEMC_SRAM_CS0, config, clkSrc_Hz);
}

/*!
 * brief Configures SRAM controller in SEMC, which can be used up to four chip selections CS0/CS1/CS2/CS3..
 *
 * param base SEMC peripheral base address.
 * param cs The chip selection.
 * param config The sram configuration.
 * param clkSrc_Hz The SEMC clock frequency.
 */
status_t SEMC_ConfigureSRAMWithChipSelection(SEMC_Type *base,
                                             semc_sram_cs_t cs,
                                             semc_sram_config_t *config,
                                             uint32_t clkSrc_Hz)
{
    assert(config != NULL);

    uint32_t tempBRVal;
    uint32_t timing;
    uint8_t memsize;
    status_t result = kStatus_Success;

#if defined(FSL_FEATURE_SEMC_HAS_SRAM_WAITEN) && (FSL_FEATURE_SEMC_HAS_SRAM_WAITEN)
    bool waitEnable;
#endif
#if defined(FSL_FEATURE_SEMC_HAS_SRAM_WAITSP) && (FSL_FEATURE_SEMC_HAS_SRAM_WAITSP)
    uint8_t waitSample;
#endif

    if ((config->address < SEMC_STARTADDRESS) || (config->address > SEMC_ENDADDRESS))
    {
        return kStatus_SEMC_InvalidBaseAddress;
    }

    uint32_t iocReg = base->IOCR & (~(SEMC_IOCR_PINMUXBITWIDTH << (uint32_t)config->cePinMux));

    uint32_t muxCe = (config->cePinMux == kSEMC_MUXRDY) ?
                         (SEMC_IOCR_PSRAM_CE - 1U) :
                         ((config->cePinMux == kSEMC_MUXA8) ? SEMC_IOCR_PSRAM_CE_A8 : SEMC_IOCR_PSRAM_CE);

    /* IOMUX setting. */
    base->IOCR = iocReg | (muxCe << (uint32_t)config->cePinMux);
    /* Address bit setting. */
    if (config->addrPortWidth > SEMC_NORFLASH_SRAM_ADDR_PORTWIDTHBASE)
    {
        /* Address bit 24 (A24) */
        base->IOCR &= ~(uint32_t)SEMC_IOCR_MUX_CSX0_MASK;
        if (config->cePinMux == kSEMC_MUXCSX0)
        {
            return kStatus_SEMC_InvalidSwPinmuxSelection;
        }

        if (config->addrPortWidth >= (SEMC_NORFLASH_SRAM_ADDR_PORTWIDTHBASE + 2U))
        {
            /* Address bit 25 (A25) */
            base->IOCR &= ~(uint32_t)SEMC_IOCR_MUX_CSX1_MASK;
            if (config->cePinMux == kSEMC_MUXCSX1)
            {
                return kStatus_SEMC_InvalidSwPinmuxSelection;
            }
        }
        if (config->addrPortWidth >= (SEMC_NORFLASH_SRAM_ADDR_PORTWIDTHBASE + 3U))
        {
            /* Address bit 26 (A26) */
            base->IOCR &= ~(uint32_t)SEMC_IOCR_MUX_CSX2_MASK;
            if (config->cePinMux == kSEMC_MUXCSX2)
            {
                return kStatus_SEMC_InvalidSwPinmuxSelection;
            }
        }
        if (config->addrPortWidth >= (SEMC_NORFLASH_SRAM_ADDR_PORTWIDTHBASE + 4U))
        {
            if (config->addr27 == kSEMC_NORA27_MUXCSX3)
            {
                /* Address bit 27 (A27) */
                base->IOCR &= ~(uint32_t)SEMC_IOCR_MUX_CSX3_MASK;
            }
            else if (config->addr27 == kSEMC_NORA27_MUXRDY)
            {
                base->IOCR |= SEMC_IOCR_MUX_RDY_MASK;
            }
            else
            {
                return kStatus_SEMC_InvalidSwPinmuxSelection;
            }

            if (config->cePinMux == kSEMC_MUXCSX3)
            {
                return kStatus_SEMC_InvalidSwPinmuxSelection;
            }
        }
        if (config->addrPortWidth > SEMC_NORFLASH_SRAM_ADDR_PORTWIDTHMAX)
        {
            return kStatus_SEMC_InvalidAddressPortWidth;
        }
    }
    /* Base control. */
    result = SEMC_CovertMemorySize(config->memsize_kbytes, &memsize);
    if (result != kStatus_Success)
    {
        return result;
    }

    tempBRVal = (config->address & SEMC_BR_BA_MASK) | SEMC_BR_MS(memsize) | SEMC_BR_VLD_MASK;

    uint32_t tempCtrlVal;

    switch (cs)
    {
        case kSEMC_SRAM_CS0:
            base->BR[6] = tempBRVal;
            break;
#if defined(FSL_FEATURE_SEMC_SUPPORT_SRAM_COUNT) && (FSL_FEATURE_SEMC_SUPPORT_SRAM_COUNT > 0x01U)
        case kSEMC_SRAM_CS1:
            base->BR9 = tempBRVal;
            break;
        case kSEMC_SRAM_CS2:
            base->BR10 = tempBRVal;
            break;
        case kSEMC_SRAM_CS3:
            base->BR11 = tempBRVal;
            break;
#endif /* FSL_FEATURE_SEMC_SUPPORT_SRAM_COUNT */
        default:
            assert(NULL);
            break;
    }

#if defined(FSL_FEATURE_SEMC_HAS_SRAM_WAITEN) && (FSL_FEATURE_SEMC_HAS_SRAM_WAITEN)
    waitEnable = config->waitEnable;
#endif
#if defined(FSL_FEATURE_SEMC_HAS_SRAM_WAITSP) && (FSL_FEATURE_SEMC_HAS_SRAM_WAITSP)
    waitSample = config->waitSample;
#endif

#if defined(FSL_FEATURE_SEMC_HAS_SRAM_SYNCEN) && (FSL_FEATURE_SEMC_HAS_SRAM_SYNCEN)
    /* Ready/wait(WAITEN and WAITSP) feature is only for async mode. */
    if (kSEMC_AsyncMode != config->syncMode)
    {
        /* Set the waitEnable and waitSample to default value. */
#if defined(FSL_FEATURE_SEMC_HAS_SRAM_WAITEN) && (FSL_FEATURE_SEMC_HAS_SRAM_WAITEN)
        waitEnable = false;
#endif

#if defined(FSL_FEATURE_SEMC_HAS_SRAM_WAITSP) && (FSL_FEATURE_SEMC_HAS_SRAM_WAITSP)
        waitSample = 0U;
#endif
    }
#endif /* FSL_FEATURE_SEMC_HAS_SRAM_SYNCEN */

    /* PSRAM0 SRAMCRx timing setting. */
    if (kSEMC_SRAM_CS0 == cs)
    {
        tempCtrlVal = SEMC_SRAMCR0_PS(config->portSize) |
#if defined(FSL_FEATURE_SEMC_HAS_SRAM_SYNCEN) && (FSL_FEATURE_SEMC_HAS_SRAM_SYNCEN)
                      SEMC_SRAMCR0_SYNCEN(config->syncMode) |
#endif /* FSL_FEATURE_SEMC_HAS_SRAM_SYNCEN */
#if defined(FSL_FEATURE_SEMC_HAS_SRAM_WAITEN) && (FSL_FEATURE_SEMC_HAS_SRAM_WAITEN)
                      SEMC_SRAMCR0_WAITEN(waitEnable) |
#endif /* FSL_FEATURE_SEMC_HAS_SRAM_WAITEN */
#if defined(FSL_FEATURE_SEMC_HAS_SRAM_WAITSP) && (FSL_FEATURE_SEMC_HAS_SRAM_WAITSP)
                      SEMC_SRAMCR0_WAITSP(waitSample) |
#endif /* FSL_FEATURE_SEMC_HAS_SRAM_WAITSP */
                      SEMC_SRAMCR0_BL(config->burstLen) | SEMC_SRAMCR0_AM(config->addrMode) |
                      SEMC_SRAMCR0_ADVP(config->advActivePolarity) |
#if defined(FSL_FEATURE_SEMC_HAS_SRAM_ADVH) && (FSL_FEATURE_SEMC_HAS_SRAM_ADVH)
                      SEMC_SRAMCR0_ADVH(config->advLevelCtrl) |
#endif /* FSL_FEATURE_SEMC_HAS_SRAM_ADVH */
                      SEMC_SRAMCR0_COL_MASK;

        base->SRAMCR0 = tempCtrlVal;
    }
#if defined(FSL_FEATURE_SEMC_SUPPORT_SRAM_COUNT) && (FSL_FEATURE_SEMC_SUPPORT_SRAM_COUNT > 0x01U)
    /* PSRAM1~PSRAM3 SRAMCRx timing setting. */
    else
    {
        tempCtrlVal = SEMC_SRAMCR4_PS(config->portSize) |
#if defined(FSL_FEATURE_SEMC_HAS_SRAM_SYNCEN) && (FSL_FEATURE_SEMC_HAS_SRAM_SYNCEN)
                      SEMC_SRAMCR4_SYNCEN(config->syncMode) |
#endif /* FSL_FEATURE_SEMC_HAS_SRAM_SYNCEN */
#if defined(FSL_FEATURE_SEMC_HAS_SRAM_WAITEN) && (FSL_FEATURE_SEMC_HAS_SRAM_WAITEN)
                      SEMC_SRAMCR4_WAITEN(waitEnable) |
#endif /* FSL_FEATURE_SEMC_HAS_SRAM_WAITEN */
#if defined(FSL_FEATURE_SEMC_HAS_SRAM_WAITSP) && (FSL_FEATURE_SEMC_HAS_SRAM_WAITSP)
                      SEMC_SRAMCR4_WAITSP(waitSample) |
#endif /* FSL_FEATURE_SEMC_HAS_SRAM_WAITSP */
                      SEMC_SRAMCR4_BL(config->burstLen) | SEMC_SRAMCR4_AM(config->addrMode) |
                      SEMC_SRAMCR4_ADVP(config->advActivePolarity) |
#if defined(FSL_FEATURE_SEMC_HAS_SRAM_ADVH) && (FSL_FEATURE_SEMC_HAS_SRAM_ADVH)
                      SEMC_SRAMCR4_ADVH(config->advLevelCtrl) |
#endif /* FSL_FEATURE_SEMC_HAS_SRAM_ADVH */
                      SEMC_SRAMCR4_COL_MASK;

        base->SRAMCR4 = tempCtrlVal;
    }
#endif /* FSL_FEATURE_SEMC_SUPPORT_SRAM_COUNT */

#if defined(FSL_FEATURE_SEMC_HAS_DELAY_CHAIN_CONTROL) && (FSL_FEATURE_SEMC_HAS_DELAY_CHAIN_CONTROL)
    uint32_t tempDelayChain = base->DCCR;

    /* Configure delay chain. */
    switch (cs)
    {
        case kSEMC_SRAM_CS0:
            tempDelayChain &= ~(SEMC_DCCR_SRAM0VAL_MASK | SEMC_DCCR_SRAM0EN_MASK);
            base->DCCR =
                tempDelayChain | SEMC_DCCR_SRAM0VAL((uint32_t)config->delayChain - 0x01U) | SEMC_DCCR_SRAM0EN_MASK;
            break;
#if defined(FSL_FEATURE_SEMC_SUPPORT_SRAM_COUNT) && (FSL_FEATURE_SEMC_SUPPORT_SRAM_COUNT > 0x01U)
        case kSEMC_SRAM_CS1:
            SUPPRESS_FALL_THROUGH_WARNING();
        case kSEMC_SRAM_CS2:
            SUPPRESS_FALL_THROUGH_WARNING();
        case kSEMC_SRAM_CS3:
            tempDelayChain &= ~(SEMC_DCCR_SRAMXVAL_MASK | SEMC_DCCR_SRAMXEN_MASK);
            base->DCCR =
                tempDelayChain | SEMC_DCCR_SRAMXVAL((uint32_t)config->delayChain - 0x01U) | SEMC_DCCR_SRAMXEN_MASK;
            break;
#endif /* FSL_FEATURE_SEMC_SUPPORT_SRAM_COUNT */
        default:
            assert(NULL);
            break;
    }
#endif /* FSL_FEATURE_SEMC_HAS_DELAY_CHAIN_CONTROL */

    if (kSEMC_SRAM_CS0 == cs)
    {
        timing = SEMC_SRAMCR1_CES(SEMC_ConvertTiming(config->tCeSetup_Ns, clkSrc_Hz));
        timing |= SEMC_SRAMCR1_CEH(SEMC_ConvertTiming(config->tCeHold_Ns, clkSrc_Hz));
        timing |= SEMC_SRAMCR1_AS(SEMC_ConvertTiming(config->tAddrSetup_Ns, clkSrc_Hz));
        timing |= SEMC_SRAMCR1_AH(SEMC_ConvertTiming(config->tAddrHold_Ns, clkSrc_Hz));
        timing |= SEMC_SRAMCR1_WEL(SEMC_ConvertTiming(config->tWeLow_Ns, clkSrc_Hz));
        timing |= SEMC_SRAMCR1_WEH(SEMC_ConvertTiming(config->tWeHigh_Ns, clkSrc_Hz));
        timing |= SEMC_SRAMCR1_REL(SEMC_ConvertTiming(config->tReLow_Ns, clkSrc_Hz));
        timing |= SEMC_SRAMCR1_REH(SEMC_ConvertTiming(config->tReHigh_Ns, clkSrc_Hz));

        /* SRAMCR1 timing setting. */
        base->SRAMCR1 = timing;

        timing = 0x00U;
#if defined(FSL_FEATURE_SEMC_HAS_SRAM_WDS_TIME) && (FSL_FEATURE_SEMC_HAS_SRAM_WDS_TIME)
        timing |= SEMC_SRAMCR2_WDS(SEMC_ConvertTiming(config->tWriteSetup_Ns, clkSrc_Hz));
#endif
#if defined(FSL_FEATURE_SEMC_HAS_SRAM_WDH_TIME) && (FSL_FEATURE_SEMC_HAS_SRAM_WDH_TIME)
        timing |= SEMC_SRAMCR2_WDH((uint32_t)SEMC_ConvertTiming(config->tWriteHold_Ns, clkSrc_Hz) + 1UL);
#endif
        timing |= SEMC_SRAMCR2_TA(SEMC_ConvertTiming(config->tTurnAround_Ns, clkSrc_Hz));
        timing |= SEMC_SRAMCR2_AWDH(SEMC_ConvertTiming(config->tAddr2WriteHold_Ns, clkSrc_Hz));
#if defined(FSL_FEATURE_SEMC_HAS_SRAM_LC_TIME) && (FSL_FEATURE_SEMC_HAS_SRAM_LC_TIME)
        timing |= SEMC_SRAMCR2_LC(config->latencyCount);
#endif
#if defined(FSL_FEATURE_SEMC_HAS_SRAM_RD_TIME) && (FSL_FEATURE_SEMC_HAS_SRAM_RD_TIME)
        timing |= SEMC_SRAMCR2_RD((uint32_t)config->readCycle - 1UL);
#endif
        timing |= SEMC_SRAMCR2_CEITV(SEMC_ConvertTiming(config->tCeInterval_Ns, clkSrc_Hz));
#if defined(FSL_FEATURE_SEMC_HAS_SRAM_RDH_TIME) && (FSL_FEATURE_SEMC_HAS_SRAM_RDH_TIME)
        timing |= SEMC_SRAMCR2_RDH((uint32_t)SEMC_ConvertTiming(config->readHoldTime_Ns, clkSrc_Hz) + 0x01U);
#endif /* FSL_FEATURE_SEMC_HAS_SRAM_RDH_TIME */

        /* SRAMCR2 timing setting. */
        base->SRAMCR2 = timing;
    }
#if defined(FSL_FEATURE_SEMC_SUPPORT_SRAM_COUNT) && (FSL_FEATURE_SEMC_SUPPORT_SRAM_COUNT > 0x01U)
    else
    {
        timing = SEMC_SRAMCR5_CES(SEMC_ConvertTiming(config->tCeSetup_Ns, clkSrc_Hz));
        timing |= SEMC_SRAMCR5_CEH(SEMC_ConvertTiming(config->tCeHold_Ns, clkSrc_Hz));
        timing |= SEMC_SRAMCR5_AS(SEMC_ConvertTiming(config->tAddrSetup_Ns, clkSrc_Hz));
        timing |= SEMC_SRAMCR5_AH(SEMC_ConvertTiming(config->tAddrHold_Ns, clkSrc_Hz));
        timing |= SEMC_SRAMCR5_WEL(SEMC_ConvertTiming(config->tWeLow_Ns, clkSrc_Hz));
        timing |= SEMC_SRAMCR5_WEH(SEMC_ConvertTiming(config->tWeHigh_Ns, clkSrc_Hz));
        timing |= SEMC_SRAMCR5_REL(SEMC_ConvertTiming(config->tReLow_Ns, clkSrc_Hz));
        timing |= SEMC_SRAMCR5_REH(SEMC_ConvertTiming(config->tReHigh_Ns, clkSrc_Hz));

        /* SRAMCR5 timing setting. */
        base->SRAMCR5 = timing;

        timing = 0x00U;
#if defined(FSL_FEATURE_SEMC_HAS_SRAM_WDS_TIME) && (FSL_FEATURE_SEMC_HAS_SRAM_WDS_TIME)
        timing = SEMC_SRAMCR6_WDS(SEMC_ConvertTiming(config->tWriteSetup_Ns, clkSrc_Hz));
#endif
#if defined(FSL_FEATURE_SEMC_HAS_SRAM_WDH_TIME) && (FSL_FEATURE_SEMC_HAS_SRAM_WDH_TIME)
        timing |= SEMC_SRAMCR6_WDH((uint32_t)SEMC_ConvertTiming(config->tWriteHold_Ns, clkSrc_Hz) + 1UL);
#endif
        timing |= SEMC_SRAMCR6_TA(SEMC_ConvertTiming(config->tTurnAround_Ns, clkSrc_Hz));
        timing |= SEMC_SRAMCR6_AWDH(SEMC_ConvertTiming(config->tAddr2WriteHold_Ns, clkSrc_Hz));
#if defined(FSL_FEATURE_SEMC_HAS_SRAM_LC_TIME) && (FSL_FEATURE_SEMC_HAS_SRAM_LC_TIME)
        timing |= SEMC_SRAMCR6_LC(config->latencyCount);
#endif
#if defined(FSL_FEATURE_SEMC_HAS_SRAM_RD_TIME) && (FSL_FEATURE_SEMC_HAS_SRAM_RD_TIME)
        timing |= SEMC_SRAMCR6_RD((uint32_t)config->readCycle - 1UL);
#endif
        timing |= SEMC_SRAMCR6_CEITV(SEMC_ConvertTiming(config->tCeInterval_Ns, clkSrc_Hz));
#if defined(FSL_FEATURE_SEMC_HAS_SRAM_RDH_TIME) && (FSL_FEATURE_SEMC_HAS_SRAM_RDH_TIME)
        timing |= SEMC_SRAMCR6_RDH((uint32_t)SEMC_ConvertTiming(config->readHoldTime_Ns, clkSrc_Hz) + 0x01U);
#endif /* FSL_FEATURE_SEMC_HAS_SRAM_RDH_TIME */

        /* SRAMCR6 timing setting. */
        base->SRAMCR6 = timing;
    }
#endif /* FSL_FEATURE_SEMC_SUPPORT_SRAM_COUNT */

    return result;
}

/*!
 * brief Configures DBI controller in SEMC.
 *
 * param base SEMC peripheral base address.
 * param config The dbi configuration.
 * param clkSrc_Hz The SEMC clock frequency.
 */
status_t SEMC_ConfigureDBI(SEMC_Type *base, semc_dbi_config_t *config, uint32_t clkSrc_Hz)
{
    assert(config != NULL);

    uint8_t memsize;
    status_t result;
    uint32_t timing;
#if (defined(SEMC_DBICR1_REL2_MASK) || defined(SEMC_DBICR1_REH2_MASK))
    uint32_t cr1RE;
#endif

    if ((config->address < SEMC_STARTADDRESS) || (config->address > SEMC_ENDADDRESS))
    {
        return kStatus_SEMC_InvalidBaseAddress;
    }

    uint32_t iocReg = base->IOCR & (~(SEMC_IOCR_PINMUXBITWIDTH << (uint32_t)config->csxPinMux));
    uint32_t muxCsx = (config->csxPinMux == kSEMC_MUXRDY) ?
                          (SEMC_IOCR_DBI_CSX - 1U) :
                          ((config->csxPinMux == kSEMC_MUXA8) ? SEMC_IOCR_DBI_CSX_A8 : SEMC_IOCR_DBI_CSX);

    /* IOMUX setting. */
    base->IOCR = iocReg | (muxCsx << (uint32_t)config->csxPinMux);
    /* Base control. */
    result = SEMC_CovertMemorySize(config->memsize_kbytes, &memsize);
    if (result != kStatus_Success)
    {
        return result;
    }
    base->BR[7] = (config->address & SEMC_BR_BA_MASK) | SEMC_BR_MS(memsize) | SEMC_BR_VLD_MASK;

    /* DBICR0 timing setting. */
    base->DBICR0 =
        SEMC_DBICR0_PS(config->portSize) | SEMC_DBICR0_BL(config->burstLen) | SEMC_DBICR0_COL(config->columnAddrBitNum);

    timing = SEMC_DBICR1_CES(SEMC_ConvertTiming(config->tCsxSetup_Ns, clkSrc_Hz));
    timing |= SEMC_DBICR1_CEH(SEMC_ConvertTiming(config->tCsxHold_Ns, clkSrc_Hz));
    timing |= SEMC_DBICR1_WEL(SEMC_ConvertTiming(config->tWexLow_Ns, clkSrc_Hz));
    timing |= SEMC_DBICR1_WEH(SEMC_ConvertTiming(config->tWexHigh_Ns, clkSrc_Hz));

#if defined(SEMC_DBICR1_REL2_MASK)
    cr1RE = SEMC_ConvertTiming(config->tRdxLow_Ns, clkSrc_Hz);
    timing |= SEMC_DBICR1_REL(cr1RE);
    timing |= SEMC_DBICR1_REL2(cr1RE >> SEMC_DBICR1_REL_WIDTH);
#else
    timing |= SEMC_DBICR1_REL(SEMC_ConvertTiming(config->tRdxLow_Ns, clkSrc_Hz));
#endif

#if defined(SEMC_DBICR1_REH2_MASK)
    cr1RE = SEMC_ConvertTiming(config->tRdxHigh_Ns, clkSrc_Hz);
    timing |= SEMC_DBICR1_REH(cr1RE);
    timing |= SEMC_DBICR1_REH2(cr1RE >> SEMC_DBICR1_REH_WIDTH);
#else
    timing |= SEMC_DBICR1_REH(SEMC_ConvertTiming(config->tRdxHigh_Ns, clkSrc_Hz));
#endif

#if defined(SEMC_DBICR1_CEITV_MASK)
    timing |= SEMC_DBICR1_CEITV(SEMC_ConvertTiming(config->tCsxInterval_Ns, clkSrc_Hz));
#endif /* SEMC_DBICR1_CEITV_MASK */

    /* DBICR1 timing setting. */
    base->DBICR1 = timing;

#if defined(SEMC_DBICR2_CEITV_MASK)
    timing = SEMC_DBICR2_CEITV(SEMC_ConvertTiming(config->tCsxInterval_Ns, clkSrc_Hz));

    /* DBICR2 timing setting. */
    base->DBICR2 = timing;
#endif /* SEMC_DBICR2_CEITV_MASK */

    return SEMC_ConfigureIPCommand(base, ((uint8_t)config->portSize + 1U));
}

/*!
 * brief SEMC IP command access.
 *
 * param base  SEMC peripheral base address.
 * param memType  SEMC memory type. refer to "semc_mem_type_t"
 * param address  SEMC device address.
 * param command  SEMC IP command.
 * For NAND device, we should use the SEMC_BuildNandIPCommand to get the right nand command.
 * For NOR/DBI device, take refer to "semc_ipcmd_nor_dbi_t".
 * For SRAM device, take refer to "semc_ipcmd_sram_t".
 * For SDRAM device, take refer to "semc_ipcmd_sdram_t".
 * param write  Data for write access.
 * param read   Data pointer for read data out.
 */
status_t SEMC_SendIPCommand(
    SEMC_Type *base, semc_mem_type_t memType, uint32_t address, uint32_t command, uint32_t write, uint32_t *read)
{
    uint32_t cmdMode;
    bool readCmd  = false;
    bool writeCmd = false;
    status_t result;

    /* Clear status bit */
    base->INTR = SEMC_INTR_IPCMDDONE_MASK;
    /* Set address. */
    base->IPCR0 = address;

    /* Check command mode. */
    cmdMode = (uint32_t)command & 0x0FU;
    switch (memType)
    {
        case kSEMC_MemType_NAND:
            readCmd = (cmdMode == (uint32_t)kSEMC_NANDCM_CommandAddressRead) ||
                      (cmdMode == (uint32_t)kSEMC_NANDCM_CommandRead) || (cmdMode == (uint32_t)kSEMC_NANDCM_Read);
            writeCmd = (cmdMode == (uint32_t)kSEMC_NANDCM_CommandAddressWrite) ||
                       (cmdMode == (uint32_t)kSEMC_NANDCM_CommandWrite) || (cmdMode == (uint32_t)kSEMC_NANDCM_Write);
            break;
        case kSEMC_MemType_NOR:
        case kSEMC_MemType_8080:
            readCmd  = (cmdMode == (uint32_t)kSEMC_NORDBICM_Read);
            writeCmd = (cmdMode == (uint32_t)kSEMC_NORDBICM_Write);
            break;
        case kSEMC_MemType_SRAM:
            readCmd  = (cmdMode == (uint32_t)kSEMC_SRAMCM_ArrayRead) || (cmdMode == (uint32_t)kSEMC_SRAMCM_RegRead);
            writeCmd = (cmdMode == (uint32_t)kSEMC_SRAMCM_ArrayWrite) || (cmdMode == (uint32_t)kSEMC_SRAMCM_RegWrite);
            break;
        case kSEMC_MemType_SDRAM:
            readCmd  = (cmdMode == (uint32_t)kSEMC_SDRAMCM_Read);
            writeCmd = (cmdMode == (uint32_t)kSEMC_SDRAMCM_Write) || (cmdMode == (uint32_t)kSEMC_SDRAMCM_Modeset);
            break;
        default:
            assert(false);
            break;
    }

    if (writeCmd)
    {
        /* Set data. */
        base->IPTXDAT = write;
    }

    /* Set command code. */
    base->IPCMD = command | SEMC_IPCMD_KEY(SEMC_IPCOMMANDMAGICKEY);
    /* Wait for command done. */
    result = SEMC_IsIPCommandDone(base);
    if (result != kStatus_Success)
    {
        return result;
    }

    if (readCmd)
    {
        /* Get the read data */
        *read = base->IPRXDAT;
    }

    return kStatus_Success;
}

/*!
 * brief SEMC NAND device memory write through IP command.
 *
 * param base  SEMC peripheral base address.
 * param address  SEMC NAND device address.
 * param data  Data for write access.
 * param size_bytes   Data length.
 */
status_t SEMC_IPCommandNandWrite(SEMC_Type *base, uint32_t address, uint8_t *data, uint32_t size_bytes)
{
    assert(data != NULL);

    status_t result = kStatus_Success;
    uint16_t ipCmd;
    uint32_t tempData = 0UL;

    /* Write command built */
    ipCmd = SEMC_BuildNandIPCommand(0, kSEMC_NANDAM_ColumnRow, kSEMC_NANDCM_Write);
    while (size_bytes >= SEMC_IPCOMMANDDATASIZEBYTEMAX)
    {
        /* Configure IP command data size. */
        (void)SEMC_ConfigureIPCommand(base, SEMC_IPCOMMANDDATASIZEBYTEMAX);
        result = SEMC_SendIPCommand(base, kSEMC_MemType_NAND, address, ipCmd, *(uint32_t *)(void *)data, NULL);
        if (result != kStatus_Success)
        {
            break;
        }

        data += SEMC_IPCOMMANDDATASIZEBYTEMAX;
        size_bytes -= SEMC_IPCOMMANDDATASIZEBYTEMAX;
    }

    if ((result == kStatus_Success) && (size_bytes != 0x00UL))
    {
        (void)SEMC_ConfigureIPCommand(base, (uint8_t)size_bytes);

        while (size_bytes != 0x00UL)
        {
            size_bytes--;
            tempData <<= SEMC_BYTE_NUMBIT;
            tempData |= data[size_bytes];
        }

        result = SEMC_SendIPCommand(base, kSEMC_MemType_NAND, address, ipCmd, tempData, NULL);
    }

    return result;
}

/*!
 * brief SEMC NAND device memory read through IP command.
 *
 * param base  SEMC peripheral base address.
 * param address  SEMC NAND device address.
 * param data  Data pointer for data read out.
 * param size_bytes   Data length.
 */
status_t SEMC_IPCommandNandRead(SEMC_Type *base, uint32_t address, uint8_t *data, uint32_t size_bytes)
{
    assert(data != NULL);

    status_t result = kStatus_Success;
    uint16_t ipCmd;
    uint32_t tempData = 0;

    /* Configure IP command data size. */
    (void)SEMC_ConfigureIPCommand(base, SEMC_IPCOMMANDDATASIZEBYTEMAX);
    /* Read command built */
    ipCmd = SEMC_BuildNandIPCommand(0, kSEMC_NANDAM_ColumnRow, kSEMC_NANDCM_Read);

    while (size_bytes >= SEMC_IPCOMMANDDATASIZEBYTEMAX)
    {
        result = SEMC_SendIPCommand(base, kSEMC_MemType_NAND, address, ipCmd, 0, (uint32_t *)(void *)data);
        if (result != kStatus_Success)
        {
            break;
        }

        data += SEMC_IPCOMMANDDATASIZEBYTEMAX;
        size_bytes -= SEMC_IPCOMMANDDATASIZEBYTEMAX;
    }

    if ((result == kStatus_Success) && (size_bytes != 0x00U))
    {
        (void)SEMC_ConfigureIPCommand(base, (uint8_t)size_bytes);
        result = SEMC_SendIPCommand(base, kSEMC_MemType_NAND, address, ipCmd, 0, &tempData);

        while (size_bytes != 0x00U)
        {
            size_bytes--;
            *(data + size_bytes) = (uint8_t)((tempData >> (SEMC_BYTE_NUMBIT * size_bytes)) & 0xFFU);
        }
    }

    return result;
}

/*!
 * brief SEMC NOR device memory read through IP command.
 *
 * param base  SEMC peripheral base address.
 * param address  SEMC NOR device address.
 * param data  Data pointer for data read out.
 * param size_bytes   Data length.
 */
status_t SEMC_IPCommandNorRead(SEMC_Type *base, uint32_t address, uint8_t *data, uint32_t size_bytes)
{
    assert(data != NULL);

    uint32_t tempData = 0;
    status_t result   = kStatus_Success;
    uint8_t dataSize  = (uint8_t)base->NORCR0 & SEMC_NORCR0_PS_MASK;

    /* Configure IP command data size. */
    (void)SEMC_ConfigureIPCommand(base, SEMC_IPCOMMANDDATASIZEBYTEMAX);

    while (size_bytes >= SEMC_IPCOMMANDDATASIZEBYTEMAX)
    {
        result = SEMC_SendIPCommand(base, kSEMC_MemType_NOR, address, (uint32_t)kSEMC_NORDBICM_Read, 0,
                                    (uint32_t *)(void *)data);
        if (result != kStatus_Success)
        {
            break;
        }

        data += SEMC_IPCOMMANDDATASIZEBYTEMAX;
        size_bytes -= SEMC_IPCOMMANDDATASIZEBYTEMAX;
    }

    if ((result == kStatus_Success) && (size_bytes != 0x00U))
    {
        (void)SEMC_ConfigureIPCommand(base, (uint8_t)size_bytes);
        result = SEMC_SendIPCommand(base, kSEMC_MemType_NOR, address, (uint16_t)kSEMC_NORDBICM_Read, 0, &tempData);
        while (size_bytes != 0x00U)
        {
            size_bytes--;
            *(data + size_bytes) = (uint8_t)((tempData >> (SEMC_BYTE_NUMBIT * size_bytes)) & 0xFFU);
        }
    }

    (void)SEMC_ConfigureIPCommand(base, dataSize);
    return result;
}

/*!
 * brief SEMC NOR device memory write through IP command.
 *
 * param base  SEMC peripheral base address.
 * param address  SEMC NOR device address.
 * param data  Data for write access.
 * param size_bytes   Data length.
 */
status_t SEMC_IPCommandNorWrite(SEMC_Type *base, uint32_t address, uint8_t *data, uint32_t size_bytes)
{
    assert(data != NULL);

    uint32_t tempData = 0;
    status_t result   = kStatus_Success;
    uint8_t dataSize  = (uint8_t)base->NORCR0 & SEMC_NORCR0_PS_MASK;

    /* Write command built */
    while (size_bytes >= SEMC_IPCOMMANDDATASIZEBYTEMAX)
    {
        /* Configure IP command data size. */
        (void)SEMC_ConfigureIPCommand(base, SEMC_IPCOMMANDDATASIZEBYTEMAX);
        result = SEMC_SendIPCommand(base, kSEMC_MemType_NOR, address, (uint16_t)kSEMC_NORDBICM_Write,
                                    *(uint32_t *)(void *)data, NULL);
        if (result != kStatus_Success)
        {
            break;
        }
        size_bytes -= SEMC_IPCOMMANDDATASIZEBYTEMAX;
        data += SEMC_IPCOMMANDDATASIZEBYTEMAX;
    }

    if ((result == kStatus_Success) && (size_bytes != 0x00U))
    {
        (void)SEMC_ConfigureIPCommand(base, (uint8_t)size_bytes);

        while (size_bytes != 0x00U)
        {
            tempData |= ((uint32_t) * (data + size_bytes - 1U) << ((size_bytes - 1U) * SEMC_BYTE_NUMBIT));
            size_bytes--;
        }

        result = SEMC_SendIPCommand(base, kSEMC_MemType_NOR, address, (uint16_t)kSEMC_NORDBICM_Write, tempData, NULL);
    }
    (void)SEMC_ConfigureIPCommand(base, dataSize);

    return result;
}
