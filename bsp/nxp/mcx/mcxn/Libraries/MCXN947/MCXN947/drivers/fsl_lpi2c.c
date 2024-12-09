/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_lpi2c.h"
#include <stdlib.h>
#include <string.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.lpflexcomm_lpi2c"
#endif

/*! @brief Typedef for slave interrupt handler. */
typedef void (*lpi2c_slave_isr_t)(uint32_t instance, void *handle);

/*!
 * @brief Used for conversion from `lpflexcomm_irq_handler_t` to `lpi2c_master_isr_t`
 */
typedef union lpi2c_to_lpflexcomm
{
    lpi2c_master_isr_t lpi2c_master_handler;
    lpi2c_slave_isr_t lpi2c_slave_handler;
    lpflexcomm_irq_handler_t lpflexcomm_handler;
} lpi2c_to_lpflexcomm_t;

/* ! @brief LPI2C master fifo commands. */
enum
{
    kTxDataCmd = LPI2C_MTDR_CMD(0x0U), /*!< Transmit DATA[7:0] */
    kRxDataCmd = LPI2C_MTDR_CMD(0X1U), /*!< Receive (DATA[7:0] + 1) bytes */
    kStopCmd   = LPI2C_MTDR_CMD(0x2U), /*!< Generate STOP condition */
    kStartCmd  = LPI2C_MTDR_CMD(0x4U), /*!< Generate(repeated) START and transmit address in DATA[[7:0] */
};

/*!
 * @brief Default watermark values.
 *
 * The default watermarks are set to zero.
 */
enum
{
    kDefaultTxWatermark = 0,
    kDefaultRxWatermark = 0,
};

/*! @brief States for the state machine used by transactional APIs. */
enum
{
    kIdleState = 0,
    kSendCommandState,
    kIssueReadCommandState,
    kTransferDataState,
    kStopState,
    kWaitForCompletionState,
};

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static uint32_t LPI2C_GetCyclesForWidth(
    uint32_t sourceClock_Hz, uint32_t width_ns, uint32_t minCycles, uint32_t maxCycles, uint32_t prescaler);

static status_t LPI2C_MasterWaitForTxReady(LPI2C_Type *base);

static status_t LPI2C_RunTransferStateMachine(LPI2C_Type *base, lpi2c_master_handle_t *handle, bool *isDone);

static void LPI2C_InitTransferStateMachine(lpi2c_master_handle_t *handle);

static status_t LPI2C_SlaveCheckAndClearError(LPI2C_Type *base, uint32_t flags);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Array to map LPI2C instance number to base pointer. */
static LPI2C_Type *const kLpi2cBases[] = LPI2C_BASE_PTRS;

/*! @brief Array to map LPI2C instance number to IRQ number, used internally for LPI2C master interrupt and EDMA
transactional APIs. */
IRQn_Type const kLpi2cIrqs[] = LPI2C_IRQS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Array to map LPI2C instance number to clock gate enum. */
static clock_ip_name_t const kLpi2cClocks[] = LPI2C_CLOCKS;

#if defined(LPI2C_PERIPH_CLOCKS)
/*! @brief Array to map LPI2C instance number to pheripheral clock gate enum. */
static const clock_ip_name_t kLpi2cPeriphClocks[] = LPI2C_PERIPH_CLOCKS;
#endif

#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*! @brief Pointer to master IRQ handler for each instance, used internally for LPI2C master interrupt and EDMA
transactional APIs. */
lpi2c_master_isr_t s_lpi2cMasterIsr;

/*! @brief Pointer to slave IRQ handler for each instance. */
static lpi2c_slave_isr_t s_lpi2cSlaveIsr;

/*! @brief Pointers to master handles for each instance, used internally for LPI2C master interrupt and EDMA
transactional APIs. */
void *s_lpi2cMasterHandle[ARRAY_SIZE(kLpi2cBases)];

/*! @brief Pointers to slave handles for each instance. */
static lpi2c_slave_handle_t *s_lpi2cSlaveHandle[ARRAY_SIZE(kLpi2cBases)];

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * brief Returns an instance number given a base address.
 *
 * If an invalid base address is passed, debug builds will assert. Release builds will just return
 * instance number 0.
 *
 * param base The LPI2C peripheral base address.
 * return LPI2C instance number starting from 0.
 */
uint32_t LPI2C_GetInstance(LPI2C_Type *base)
{
    uint32_t instance;
    for (instance = 0U; instance < ARRAY_SIZE(kLpi2cBases); ++instance)
    {
        if (kLpi2cBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(kLpi2cBases));
    return instance;
}

/*!
 * @brief Computes a cycle count for a given time in nanoseconds.
 * @param sourceClock_Hz LPI2C functional clock frequency in Hertz.
 * @param width_ns Desired with in nanoseconds.
 * @param minCycles Minimum cycle count.
 * @param maxCycles Maximum cycle count.
 * @param prescaler LPI2C prescaler setting. If the cycle period is not affected by the prescaler value, set it to 0.
 */
static uint32_t LPI2C_GetCyclesForWidth(
    uint32_t sourceClock_Hz, uint32_t width_ns, uint32_t minCycles, uint32_t maxCycles, uint32_t prescaler)
{
    assert(sourceClock_Hz > 0U);

    uint32_t divider = 1U;

    while (prescaler != 0U)
    {
        divider *= 2U;
        prescaler--;
    }

    uint32_t busCycle_ns = 1000000U / (sourceClock_Hz / divider / 1000U);
    /* Calculate the cycle count, round up the calculated value. */
    uint32_t cycles = (width_ns * 10U / busCycle_ns + 5U) / 10U;

    /* If the calculated value is smaller than the minimum value, use the minimum value */
    if (cycles < minCycles)
    {
        cycles = minCycles;
    }
    /* If the calculated value is larger than the maximum value, use the maxmum value */
    if (cycles > maxCycles)
    {
        cycles = maxCycles;
    }

    return cycles;
}

/*!
 * @brief Convert provided flags to status code, and clear any errors if present.
 * @param base The LPI2C peripheral base address.
 * @param status Current status flags value that will be checked.
 * @retval #kStatus_Success
 * @retval #kStatus_LPI2C_PinLowTimeout
 * @retval #kStatus_LPI2C_ArbitrationLost
 * @retval #kStatus_LPI2C_Nak
 * @retval #kStatus_LPI2C_FifoError
 */
/* Not static so it can be used from fsl_lpi2c_edma.c. */
status_t LPI2C_MasterCheckAndClearError(LPI2C_Type *base, uint32_t status)
{
    status_t result = kStatus_Success;

    /* Check for error. These errors cause a stop to automatically be sent. We must */
    /* clear the errors before a new transfer can start. */
    status &= (uint32_t)kLPI2C_MasterErrorFlags;
    if (0U != status)
    {
        /* Select the correct error code. Ordered by severity, with bus issues first. */
        if (0U != (status & (uint32_t)kLPI2C_MasterPinLowTimeoutFlag))
        {
            result = kStatus_LPI2C_PinLowTimeout;
        }
        else if (0U != (status & (uint32_t)kLPI2C_MasterArbitrationLostFlag))
        {
            result = kStatus_LPI2C_ArbitrationLost;
        }
        else if (0U != (status & (uint32_t)kLPI2C_MasterNackDetectFlag))
        {
            result = kStatus_LPI2C_Nak;
        }
        else if (0U != (status & (uint32_t)kLPI2C_MasterFifoErrFlag))
        {
            result = kStatus_LPI2C_FifoError;
        }
        else
        {
            ; /* Intentional empty */
        }

        /* Clear the flags. */
        LPI2C_MasterClearStatusFlags(base, status);

        /* Reset fifos. These flags clear automatically. */
        base->MCR |= LPI2C_MCR_RRF_MASK | LPI2C_MCR_RTF_MASK;
    }
    else
    {
        ; /* Intentional empty */
    }

    return result;
}

/*!
 * @brief Wait until there is room in the tx fifo.
 * @param base The LPI2C peripheral base address.
 * @retval #kStatus_Success
 * @retval #kStatus_LPI2C_PinLowTimeout
 * @retval #kStatus_LPI2C_ArbitrationLost
 * @retval #kStatus_LPI2C_Nak
 * @retval #kStatus_LPI2C_FifoError
 */
static status_t LPI2C_MasterWaitForTxReady(LPI2C_Type *base)
{
    status_t result = kStatus_Success;
    uint32_t status;
    size_t txCount;
    size_t txFifoSize = (size_t)FSL_FEATURE_LPI2C_FIFO_SIZEn(base);

#if I2C_RETRY_TIMES != 0U
    uint32_t waitTimes = I2C_RETRY_TIMES;
#endif
    do
    {
        /* Get the number of words in the tx fifo and compute empty slots. */
        LPI2C_MasterGetFifoCounts(base, NULL, &txCount);
        txCount = txFifoSize - txCount;

        /* Check for error flags. */
        status = LPI2C_MasterGetStatusFlags(base);
        result = LPI2C_MasterCheckAndClearError(base, status);
        if (kStatus_Success != result)
        {
            break;
        }
#if I2C_RETRY_TIMES != 0U
        waitTimes--;
    } while ((0U == txCount) && (0U != waitTimes));

    if (0U == waitTimes)
    {
        result = kStatus_LPI2C_Timeout;
    }
#else
    } while (0U == txCount);
#endif

    return result;
}

/*!
 * @brief Make sure the bus isn't already busy.
 *
 * A busy bus is allowed if we are the one driving it.
 *
 * @param base The LPI2C peripheral base address.
 * @retval #kStatus_Success
 * @retval #kStatus_LPI2C_Busy
 */
/* Not static so it can be used from fsl_lpi2c_edma.c. */
status_t LPI2C_CheckForBusyBus(LPI2C_Type *base)
{
    status_t ret = kStatus_Success;

    uint32_t status = LPI2C_MasterGetStatusFlags(base);
    if ((0U != (status & (uint32_t)kLPI2C_MasterBusBusyFlag)) && (0U == (status & (uint32_t)kLPI2C_MasterBusyFlag)))
    {
        ret = kStatus_LPI2C_Busy;
    }

    return ret;
}

/*!
 * brief Provides a default configuration for the LPI2C master peripheral.
 *
 * This function provides the following default configuration for the LPI2C master peripheral:
 * code
 *  masterConfig->enableMaster            = true;
 *  masterConfig->debugEnable             = false;
 *  masterConfig->ignoreAck               = false;
 *  masterConfig->pinConfig               = kLPI2C_2PinOpenDrain;
 *  masterConfig->baudRate_Hz             = 100000U;
 *  masterConfig->busIdleTimeout_ns       = 0U;
 *  masterConfig->pinLowTimeout_ns        = 0U;
 *  masterConfig->sdaGlitchFilterWidth_ns = 0U;
 *  masterConfig->sclGlitchFilterWidth_ns = 0U;
 *  masterConfig->hostRequest.enable      = false;
 *  masterConfig->hostRequest.source      = kLPI2C_HostRequestExternalPin;
 *  masterConfig->hostRequest.polarity    = kLPI2C_HostRequestPinActiveHigh;
 * endcode
 *
 * After calling this function, you can override any settings in order to customize the configuration,
 * prior to initializing the master driver with LPI2C_MasterInit().
 *
 * param[out] masterConfig User provided configuration structure for default values. Refer to #lpi2c_master_config_t.
 */
void LPI2C_MasterGetDefaultConfig(lpi2c_master_config_t *masterConfig)
{
    /* Initializes the configure structure to zero. */
    (void)memset(masterConfig, 0, sizeof(*masterConfig));

    masterConfig->enableMaster            = true;
    masterConfig->debugEnable             = false;
    masterConfig->enableDoze              = true;
    masterConfig->ignoreAck               = false;
    masterConfig->pinConfig               = kLPI2C_2PinOpenDrain;
    masterConfig->baudRate_Hz             = 100000U;
    masterConfig->busIdleTimeout_ns       = 0U; /* Set to 0 to disable the function */
    masterConfig->pinLowTimeout_ns        = 0U; /* Set to 0 to disable the function */
    masterConfig->sdaGlitchFilterWidth_ns = 0U; /* Set to 0 to disable the function */
    masterConfig->sclGlitchFilterWidth_ns = 0U; /* Set to 0 to disable the function */
    masterConfig->hostRequest.enable      = false;
    masterConfig->hostRequest.source      = kLPI2C_HostRequestExternalPin;
    masterConfig->hostRequest.polarity    = kLPI2C_HostRequestPinActiveHigh;
}

/*!
 * brief Initializes the LPI2C master peripheral.
 *
 * This function enables the peripheral clock and initializes the LPI2C master peripheral as described by the user
 * provided configuration. A software reset is performed prior to configuration.
 *
 * param base The LPI2C peripheral base address.
 * param masterConfig User provided peripheral configuration. Use LPI2C_MasterGetDefaultConfig() to get a set of
 * defaults
 *      that you can override.
 * param sourceClock_Hz Frequency in Hertz of the LPI2C functional clock. Used to calculate the baud rate divisors,
 *      filter widths, and timeout periods.
 */
void LPI2C_MasterInit(LPI2C_Type *base, const lpi2c_master_config_t *masterConfig, uint32_t sourceClock_Hz)
{
    uint32_t prescaler;
    uint32_t cycles;
    uint32_t cfgr2;
    uint32_t value;
    uint32_t instance = LPI2C_GetInstance(base);
    
    if(LP_FLEXCOMM_GetBaseAddress(instance) != 0U)
    {
      
#if !(defined(LPFLEXCOMM_INIT_NOT_USED_IN_DRIVER) && LPFLEXCOMM_INIT_NOT_USED_IN_DRIVER)
        /* initialize flexcomm to LPI2C mode */
        status_t status = LP_FLEXCOMM_Init(instance, LP_FLEXCOMM_PERIPH_LPI2C);
        if (kStatus_Success != status)
        {
            assert(false);
        }
#endif /* LPFLEXCOMM_INIT_NOT_USED_IN_DRIVER */
        
    }
    else
    {
     
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
        /* Ungate the clock. */
        (void)CLOCK_EnableClock(kLpi2cClocks[instance]);
#if defined(LPI2C_PERIPH_CLOCKS)
        /* Ungate the functional clock in initialize function. */
        CLOCK_EnableClock(kLpi2cPeriphClocks[instance]);
#endif

#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
        
    }
    
    /* Reset peripheral before configuring it. */
    LPI2C_MasterReset(base);

    /* Doze bit: 0 is enable, 1 is disable */
    base->MCR = LPI2C_MCR_DBGEN(masterConfig->debugEnable) | LPI2C_MCR_DOZEN(!(masterConfig->enableDoze));

    /* host request */
    value = base->MCFGR0;
    value &= (~(LPI2C_MCFGR0_HREN_MASK | LPI2C_MCFGR0_HRPOL_MASK | LPI2C_MCFGR0_HRSEL_MASK));
    value |= LPI2C_MCFGR0_HREN(masterConfig->hostRequest.enable) |
             LPI2C_MCFGR0_HRPOL(masterConfig->hostRequest.polarity) |
             LPI2C_MCFGR0_HRSEL(masterConfig->hostRequest.source);
    base->MCFGR0 = value;

    /* pin config and ignore ack */
    value = base->MCFGR1;
    value &= ~(LPI2C_MCFGR1_PINCFG_MASK | LPI2C_MCFGR1_IGNACK_MASK);
    value |= LPI2C_MCFGR1_PINCFG(masterConfig->pinConfig);
    value |= LPI2C_MCFGR1_IGNACK(masterConfig->ignoreAck);
    base->MCFGR1 = value;

    LPI2C_MasterSetWatermarks(base, (size_t)kDefaultTxWatermark, (size_t)kDefaultRxWatermark);

    /* Configure glitch filters. */
    cfgr2 = base->MCFGR2;
    if (0U != (masterConfig->sdaGlitchFilterWidth_ns))
    {
        /* Calculate SDA filter width. The width is equal to FILTSDA cycles of functional clock.
           And set FILTSDA to 0 disables the fileter, so the min value is 1. */
        cycles = LPI2C_GetCyclesForWidth(sourceClock_Hz, masterConfig->sdaGlitchFilterWidth_ns, 1U,
                                         (LPI2C_MCFGR2_FILTSDA_MASK >> LPI2C_MCFGR2_FILTSDA_SHIFT), 0U);
        cfgr2 &= ~LPI2C_MCFGR2_FILTSDA_MASK;
        cfgr2 |= LPI2C_MCFGR2_FILTSDA(cycles);
    }
    if (0U != masterConfig->sclGlitchFilterWidth_ns)
    {
        /* Calculate SDL filter width. The width is equal to FILTSCL cycles of functional clock.
           And set FILTSCL to 0 disables the fileter, so the min value is 1. */
        cycles = LPI2C_GetCyclesForWidth(sourceClock_Hz, masterConfig->sclGlitchFilterWidth_ns, 1U,
                                         (LPI2C_MCFGR2_FILTSCL_MASK >> LPI2C_MCFGR2_FILTSCL_SHIFT), 0U);
        cfgr2 &= ~LPI2C_MCFGR2_FILTSCL_MASK;
        cfgr2 |= LPI2C_MCFGR2_FILTSCL(cycles);
    }
    base->MCFGR2 = cfgr2;

    /* Configure baudrate after the SDA/SCL glitch filter setting,
       since the baudrate calculation needs them as parameter. */
    LPI2C_MasterSetBaudRate(base, sourceClock_Hz, masterConfig->baudRate_Hz);

    /* Configure bus idle and pin low timeouts after baudrate setting,
       since the timeout calculation needs prescaler as parameter. */
    prescaler = (base->MCFGR1 & LPI2C_MCFGR1_PRESCALE_MASK) >> LPI2C_MCFGR1_PRESCALE_SHIFT;

    if (0U != (masterConfig->busIdleTimeout_ns))
    {
        /* Calculate bus idle timeout value. The value is equal to BUSIDLE cycles of functional clock divided by
           prescaler. And set BUSIDLE to 0 disables the fileter, so the min value is 1. */
        cycles = LPI2C_GetCyclesForWidth(sourceClock_Hz, masterConfig->busIdleTimeout_ns, 1U,
                                         (LPI2C_MCFGR2_BUSIDLE_MASK >> LPI2C_MCFGR2_BUSIDLE_SHIFT), prescaler);
        cfgr2 &= ~LPI2C_MCFGR2_BUSIDLE_MASK;
        cfgr2 |= LPI2C_MCFGR2_BUSIDLE(cycles);
    }
    base->MCFGR2 = cfgr2;
    if (0U != masterConfig->pinLowTimeout_ns)
    {
        /* Calculate bus pin low timeout value. The value is equal to PINLOW cycles of functional clock divided by
           prescaler. And set PINLOW to 0 disables the fileter, so the min value is 1. */
        cycles       = LPI2C_GetCyclesForWidth(sourceClock_Hz, masterConfig->pinLowTimeout_ns / 256U, 1U,
                                         (LPI2C_MCFGR2_BUSIDLE_MASK >> LPI2C_MCFGR2_BUSIDLE_SHIFT), prescaler);
        base->MCFGR3 = (base->MCFGR3 & ~LPI2C_MCFGR3_PINLOW_MASK) | LPI2C_MCFGR3_PINLOW(cycles);
    }

    LPI2C_MasterEnable(base, masterConfig->enableMaster);
}

/*!
 * brief Deinitializes the LPI2C master peripheral.
 *
 * This function disables the LPI2C master peripheral and gates the clock. It also performs a software
 * reset to restore the peripheral to reset conditions.
 *
 * param base The LPI2C peripheral base address.
 */
void LPI2C_MasterDeinit(LPI2C_Type *base)
{
    uint32_t instance = LPI2C_GetInstance(base); 
    
    /* Restore to reset state. */
    LPI2C_MasterReset(base);
    if(LP_FLEXCOMM_GetBaseAddress(instance) != 0U)
    {
#if !(defined(LPFLEXCOMM_INIT_NOT_USED_IN_DRIVER) && LPFLEXCOMM_INIT_NOT_USED_IN_DRIVER)
        LP_FLEXCOMM_Deinit(instance);
#endif
    }
    else
    {
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
        /* Gate clock. */
        (void)CLOCK_DisableClock(kLpi2cClocks[instance]);
#if defined(LPI2C_PERIPH_CLOCKS)
        /* Gate the functional clock. */
        CLOCK_DisableClock(kLpi2cPeriphClocks[instance]);
#endif

#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
    }
}

/*!
 * brief Configures LPI2C master data match feature.
 *
 * param base The LPI2C peripheral base address.
 * param matchConfig Settings for the data match feature.
 */
void LPI2C_MasterConfigureDataMatch(LPI2C_Type *base, const lpi2c_data_match_config_t *matchConfig)
{
    /* Disable master mode. */
    bool wasEnabled = (0U != ((base->MCR & LPI2C_MCR_MEN_MASK) >> LPI2C_MCR_MEN_SHIFT));
    LPI2C_MasterEnable(base, false);

    base->MCFGR1 = (base->MCFGR1 & ~LPI2C_MCFGR1_MATCFG_MASK) | LPI2C_MCFGR1_MATCFG(matchConfig->matchMode);
    base->MCFGR0 = (base->MCFGR0 & ~LPI2C_MCFGR0_RDMO_MASK) | LPI2C_MCFGR0_RDMO(matchConfig->rxDataMatchOnly);
    base->MDMR   = LPI2C_MDMR_MATCH0(matchConfig->match0) | LPI2C_MDMR_MATCH1(matchConfig->match1);

    /* Restore master mode. */
    if (wasEnabled)
    {
        LPI2C_MasterEnable(base, true);
    }
}

/*!
 * brief Sets the I2C bus frequency for master transactions.
 *
 * The LPI2C master is automatically disabled and re-enabled as necessary to configure the baud
 * rate. Do not call this function during a transfer, or the transfer is aborted.
 *
 * note Please note that the second parameter is the clock frequency of LPI2C module, the third
 * parameter means user configured bus baudrate, this implementation is different from other I2C drivers
 * which use baudrate configuration as second parameter and source clock frequency as third parameter.
 *
 * param base The LPI2C peripheral base address.
 * param sourceClock_Hz LPI2C functional clock frequency in Hertz.
 * param baudRate_Hz Requested bus frequency in Hertz.
 */
void LPI2C_MasterSetBaudRate(LPI2C_Type *base, uint32_t sourceClock_Hz, uint32_t baudRate_Hz)
{
    bool wasEnabled;
    uint8_t filtScl = (uint8_t)((base->MCFGR2 & LPI2C_MCFGR2_FILTSCL_MASK) >> LPI2C_MCFGR2_FILTSCL_SHIFT);

    uint8_t divider     = 1U;
    uint8_t bestDivider = 1U;
    uint8_t prescale    = 0U;
    uint8_t bestPre     = 0U;

    uint8_t clkCycle;
    uint8_t bestclkCycle = 0U;

    uint32_t absError  = 0U;
    uint32_t bestError = 0xffffffffu;
    uint32_t computedRate;

    uint32_t tmpReg = 0U;

    /* Disable master mode. */
    wasEnabled = (0U != ((base->MCR & LPI2C_MCR_MEN_MASK) >> LPI2C_MCR_MEN_SHIFT));
    LPI2C_MasterEnable(base, false);

    /* Baud rate = (sourceClock_Hz / 2 ^ prescale) / (CLKLO + 1 + CLKHI + 1 + SCL_LATENCY)
     * SCL_LATENCY = ROUNDDOWN((2 + FILTSCL) / (2 ^ prescale))
     */
    for (prescale = 0U; prescale <= 7U; prescale++)
    {
        /* Calculate the clkCycle, clkCycle = CLKLO + CLKHI, divider = 2 ^ prescale */
        clkCycle = (uint8_t)((10U * sourceClock_Hz / divider / baudRate_Hz + 5U) / 10U - (2U + filtScl) / divider - 2U);
        /* According to register description, The max value for CLKLO and CLKHI is 63.
           however to meet the I2C specification of tBUF, CLKHI should be less than
           clkCycle - 0.52 x sourceClock_Hz / baudRate_Hz / divider + 1U. Refer to the comment of the tmpHigh's
           calculation for details. So we have:
           CLKHI < clkCycle - 0.52 x sourceClock_Hz / baudRate_Hz / divider + 1U,
           clkCycle = CLKHI + CLKLO and
           sourceClock_Hz / baudRate_Hz / divider = clkCycle + 2 + ROUNDDOWN((2 + FILTSCL) / divider),
           we can come up with: CLKHI < 0.92 x CLKLO - ROUNDDOWN(2 + FILTSCL) / divider
           so the max boundary of CLKHI should be 0.92 x 63 - ROUNDDOWN(2 + FILTSCL) / divider,
           and the max boundary of clkCycle is 1.92 x 63 - ROUNDDOWN(2 + FILTSCL) / divider. */
        if (clkCycle > (120U - (2U + filtScl) / divider))
        {
            divider *= 2U;
            continue;
        }
        /* Calculate the computed baudrate and compare it with the desired baudrate */
        computedRate = (sourceClock_Hz / (uint32_t)divider) /
                       ((uint32_t)clkCycle + 2U + (2U + (uint32_t)filtScl) / (uint32_t)divider);
        absError = baudRate_Hz > computedRate ? baudRate_Hz - computedRate : computedRate - baudRate_Hz;
        if (absError < bestError)
        {
            bestPre      = prescale;
            bestDivider  = divider;
            bestclkCycle = clkCycle;
            bestError    = absError;

            /* If the error is 0, then we can stop searching because we won't find a better match. */
            if (absError == 0U)
            {
                break;
            }
        }
        divider *= 2U;
    }

    /* SCL low time tLO should be larger than or equal to SCL high time tHI:
       tLO = ((CLKLO + 1) x (2 ^ PRESCALE)) >= tHI = ((CLKHI + 1 + SCL_LATENCY) x (2 ^ PRESCALE)),
       which is CLKLO >= CLKHI + (2U + filtScl) / bestDivider.
       Also since bestclkCycle = CLKLO + CLKHI, bestDivider = 2 ^ PRESCALE
       which makes CLKHI <= (bestclkCycle - (2U + filtScl) / bestDivider) / 2U.

       The max tBUF should be at least 0.52 times of the SCL clock cycle:
       tBUF = ((CLKLO + 1) x (2 ^ PRESCALE) / sourceClock_Hz) > (0.52 / baudRate_Hz),
       plus bestDivider = 2 ^ PRESCALE, bestclkCycle = CLKLO + CLKHI we can come up with
       CLKHI <= (bestclkCycle - 0.52 x sourceClock_Hz / baudRate_Hz / bestDivider + 1U).
       In this case to get a safe CLKHI calculation, we can assume:
    */
    uint8_t tmpHigh = (bestclkCycle - (2U + filtScl) / bestDivider) / 2U;
    while (tmpHigh > (bestclkCycle - 52U * sourceClock_Hz / baudRate_Hz / bestDivider / 100U + 1U))
    {
        tmpHigh = tmpHigh - 1U;
    }

    /* Calculate DATAVD and SETHOLD.
       To meet the timing requirement of I2C spec for standard mode, fast mode and fast mode plus: */
    /* The min tHD:STA/tSU:STA/tSU:STO should be at least 0.4 times of the SCL clock cycle, use 0.5 to be safe:
       tHD:STA = ((SETHOLD + 1) x (2 ^ PRESCALE) / sourceClock_Hz) > (0.5 / baudRate_Hz), bestDivider = 2 ^ PRESCALE */
    uint8_t tmpHold = (uint8_t)(sourceClock_Hz / baudRate_Hz / bestDivider / 2U) - 1U;

    /* The max tVD:DAT/tVD:ACK/tHD:DAT should be at most 0.345 times of the SCL clock cycle, use 0.25 to be safe:
       tVD:DAT = ((DATAVD + 1) x (2 ^ PRESCALE) / sourceClock_Hz) < (0.25 / baudRate_Hz), bestDivider = 2 ^ PRESCALE */
    uint8_t tmpDataVd = (uint8_t)(sourceClock_Hz / baudRate_Hz / bestDivider / 4U) - 1U;

    /* The min tSU:DAT should be at least 0.05 times of the SCL clock cycle:
       tSU:DAT = ((2 + FILTSDA + 2 ^ PRESCALE) / sourceClock_Hz) >= (0.05 / baud),
       plus bestDivider = 2 ^ PRESCALE, we can come up with:
       FILTSDA >= (0.05 x sourceClock_Hz / baudRate_Hz - bestDivider - 2) */
    if ((sourceClock_Hz / baudRate_Hz / 20U) > (bestDivider + 2U))
    {
        /* Read out the FILTSDA configuration, if it is smaller than expected, change the setting. */
        uint8_t filtSda = (uint8_t)((base->MCFGR2 & LPI2C_MCFGR2_FILTSDA_MASK) >> LPI2C_MCFGR2_FILTSDA_SHIFT);
        if (filtSda < (sourceClock_Hz / baudRate_Hz / 20U - bestDivider - 2U))
        {
            filtSda = (uint8_t)(sourceClock_Hz / baudRate_Hz / 20U) - bestDivider - 2U;
        }
        base->MCFGR2 = (base->MCFGR2 & ~LPI2C_MCFGR2_FILTSDA_MASK) | LPI2C_MCFGR2_FILTSDA(filtSda);
    }

    /* Set CLKHI, CLKLO, SETHOLD, DATAVD value. */
    tmpReg = LPI2C_MCCR0_CLKHI((uint32_t)tmpHigh) |
             LPI2C_MCCR0_CLKLO((uint32_t)((uint32_t)bestclkCycle - (uint32_t)tmpHigh)) |
             LPI2C_MCCR0_SETHOLD((uint32_t)tmpHold) | LPI2C_MCCR0_DATAVD((uint32_t)tmpDataVd);
    base->MCCR0 = tmpReg;

    /* Set PRESCALE value. */
    base->MCFGR1 = (base->MCFGR1 & ~LPI2C_MCFGR1_PRESCALE_MASK) | LPI2C_MCFGR1_PRESCALE(bestPre);

    /* Restore master mode. */
    if (wasEnabled)
    {
        LPI2C_MasterEnable(base, true);
    }
}

/*!
 * brief Sends a START signal and slave address on the I2C bus.
 *
 * This function is used to initiate a new master mode transfer. First, the bus state is checked to ensure
 * that another master is not occupying the bus. Then a START signal is transmitted, followed by the
 * 7-bit address specified in the a address parameter. Note that this function does not actually wait
 * until the START and address are successfully sent on the bus before returning.
 *
 * param base The LPI2C peripheral base address.
 * param address 7-bit slave device address, in bits [6:0].
 * param dir Master transfer direction, either #kLPI2C_Read or #kLPI2C_Write. This parameter is used to set
 *      the R/w bit (bit 0) in the transmitted slave address.
 * retval #kStatus_Success START signal and address were successfully enqueued in the transmit FIFO.
 * retval #kStatus_LPI2C_Busy Another master is currently utilizing the bus.
 */
status_t LPI2C_MasterStart(LPI2C_Type *base, uint8_t address, lpi2c_direction_t dir)
{
    /* Return an error if the bus is already in use not by us. */
    status_t result = LPI2C_CheckForBusyBus(base);
    if (kStatus_Success == result)
    {
        /* Clear all flags. */
        LPI2C_MasterClearStatusFlags(base, (uint32_t)kLPI2C_MasterClearFlags);

        /* Turn off auto-stop option. */
        base->MCFGR1 &= ~LPI2C_MCFGR1_AUTOSTOP_MASK;

        /* Wait until there is room in the fifo. */
        result = LPI2C_MasterWaitForTxReady(base);
        if (kStatus_Success == result)
        {
            /* Issue start command. */
            base->MTDR = (uint32_t)kStartCmd | (((uint32_t)address << 1U) | (uint32_t)dir);
        }
    }

    return result;
}

/*!
 * brief Sends a STOP signal on the I2C bus.
 *
 * This function does not return until the STOP signal is seen on the bus, or an error occurs.
 *
 * param base The LPI2C peripheral base address.
 * retval #kStatus_Success The STOP signal was successfully sent on the bus and the transaction terminated.
 * retval #kStatus_LPI2C_Busy Another master is currently utilizing the bus.
 * retval #kStatus_LPI2C_Nak The slave device sent a NAK in response to a byte.
 * retval #kStatus_LPI2C_FifoError FIFO under run or overrun.
 * retval #kStatus_LPI2C_ArbitrationLost Arbitration lost error.
 * retval #kStatus_LPI2C_PinLowTimeout SCL or SDA were held low longer than the timeout.
 */
status_t LPI2C_MasterStop(LPI2C_Type *base)
{
    /* Wait until there is room in the fifo. */
    status_t result = LPI2C_MasterWaitForTxReady(base);
    if (kStatus_Success == result)
    {
        /* Send the STOP signal */
        base->MTDR = (uint32_t)kStopCmd;

        /* Wait for the stop detected flag to set, indicating the transfer has completed on the bus. */
        /* Also check for errors while waiting. */
#if I2C_RETRY_TIMES != 0U
        uint32_t waitTimes = I2C_RETRY_TIMES;
#endif

#if I2C_RETRY_TIMES != 0U
        while ((result == kStatus_Success) && (0U != waitTimes))
        {
            waitTimes--;
#else
        while (result == kStatus_Success)
        {
#endif
            uint32_t status = LPI2C_MasterGetStatusFlags(base);

            /* Check for error flags. */
            result = LPI2C_MasterCheckAndClearError(base, status);

            /* Check if the stop was sent successfully. */
            if ((0U != (status & (uint32_t)kLPI2C_MasterStopDetectFlag)) &&
                (0U != (status & (uint32_t)kLPI2C_MasterTxReadyFlag)))
            {
                LPI2C_MasterClearStatusFlags(base, (uint32_t)kLPI2C_MasterStopDetectFlag);
                break;
            }
        }

#if I2C_RETRY_TIMES != 0U
        if (0U == waitTimes)
        {
            result = kStatus_LPI2C_Timeout;
        }
#endif
    }

    return result;
}

/*!
 * brief Performs a polling receive transfer on the I2C bus.
 *
 * param base  The LPI2C peripheral base address.
 * param rxBuff The pointer to the data to be transferred.
 * param rxSize The length in bytes of the data to be transferred.
 * retval #kStatus_Success Data was received successfully.
 * retval #kStatus_LPI2C_Busy Another master is currently utilizing the bus.
 * retval #kStatus_LPI2C_Nak The slave device sent a NAK in response to a byte.
 * retval #kStatus_LPI2C_FifoError FIFO under run or overrun.
 * retval #kStatus_LPI2C_ArbitrationLost Arbitration lost error.
 * retval #kStatus_LPI2C_PinLowTimeout SCL or SDA were held low longer than the timeout.
 */
status_t LPI2C_MasterReceive(LPI2C_Type *base, void *rxBuff, size_t rxSize)
{
    assert(NULL != rxBuff);

    status_t result = kStatus_Success;
    uint8_t *buf;
    size_t tmpRxSize = rxSize;
#if I2C_RETRY_TIMES != 0U
    uint32_t waitTimes;
#endif

    /* Check transfer data size. */
    if (rxSize > (256UL * (uint32_t)FSL_FEATURE_LPI2C_FIFO_SIZEn(base)))
    {
        return kStatus_InvalidArgument;
    }

    /* Handle empty read. */
    if (rxSize != 0U)
    {
        /* Wait until there is room in the command fifo. */
        result = LPI2C_MasterWaitForTxReady(base);
        if (kStatus_Success == result)
        {
            /* Issue command to receive data. A single write to MTDR can issue read operation of 0xFFU + 1 byte of data
               at most, so when the rxSize is larger than 0x100U, push multiple read commands to MTDR until rxSize is
               reached. */
            while (tmpRxSize != 0U)
            {
                if (tmpRxSize > 256U)
                {
                    base->MTDR = (uint32_t)(kRxDataCmd) | (uint32_t)LPI2C_MTDR_DATA(0xFFU);
                    tmpRxSize -= 256U;
                }
                else
                {
                    base->MTDR = (uint32_t)(kRxDataCmd) | (uint32_t)LPI2C_MTDR_DATA(tmpRxSize - 1U);
                    tmpRxSize  = 0U;
                }
            }

            /* Receive data */
            buf = (uint8_t *)rxBuff;
            while (0U != (rxSize--))
            {
#if I2C_RETRY_TIMES != 0U
                waitTimes = I2C_RETRY_TIMES;
#endif
                /* Read LPI2C receive fifo register. The register includes a flag to indicate whether */
                /* the FIFO is empty, so we can both get the data and check if we need to keep reading */
                /* using a single register read. */
                uint32_t value = 0U;
                do
                {
                    /* Check for errors. */
                    result = LPI2C_MasterCheckAndClearError(base, LPI2C_MasterGetStatusFlags(base));
                    if (kStatus_Success != result)
                    {
                        break;
                    }

                    value = base->MRDR;
#if I2C_RETRY_TIMES != 0U
                    waitTimes--;
                } while ((0U != (value & LPI2C_MRDR_RXEMPTY_MASK)) && (0U != waitTimes));
                if (0U == waitTimes)
                {
                    result = kStatus_LPI2C_Timeout;
                }
#else
                } while (0U != (value & LPI2C_MRDR_RXEMPTY_MASK));
#endif
                if ((status_t)kStatus_Success != result)
                {
                    break;
                }

                *buf++ = (uint8_t)(value & LPI2C_MRDR_DATA_MASK);
            }
        }
    }

    return result;
}

/*!
 * brief Performs a polling send transfer on the I2C bus.
 *
 * Sends up to a txSize number of bytes to the previously addressed slave device. The slave may
 * reply with a NAK to any byte in order to terminate the transfer early. If this happens, this
 * function returns #kStatus_LPI2C_Nak.
 *
 * param base  The LPI2C peripheral base address.
 * param txBuff The pointer to the data to be transferred.
 * param txSize The length in bytes of the data to be transferred.
 * retval #kStatus_Success Data was sent successfully.
 * retval #kStatus_LPI2C_Busy Another master is currently utilizing the bus.
 * retval #kStatus_LPI2C_Nak The slave device sent a NAK in response to a byte.
 * retval #kStatus_LPI2C_FifoError FIFO under run or over run.
 * retval #kStatus_LPI2C_ArbitrationLost Arbitration lost error.
 * retval #kStatus_LPI2C_PinLowTimeout SCL or SDA were held low longer than the timeout.
 */
status_t LPI2C_MasterSend(LPI2C_Type *base, void *txBuff, size_t txSize)
{
    status_t result = kStatus_Success;
    uint8_t *buf    = (uint8_t *)txBuff;

    assert(NULL != txBuff);

    /* Send data buffer */
    while (0U != (txSize--))
    {
        /* Wait until there is room in the fifo. This also checks for errors. */
        result = LPI2C_MasterWaitForTxReady(base);
        if (kStatus_Success != result)
        {
            break;
        }

        /* Write byte into LPI2C master data register. */
        base->MTDR = *buf++;
    }

    return result;
}

/*!
 * brief Performs a master polling transfer on the I2C bus.
 *
 * note The API does not return until the transfer succeeds or fails due
 * to error happens during transfer.
 *
 * param base The LPI2C peripheral base address.
 * param transfer Pointer to the transfer structure.
 * retval #kStatus_Success Data was received successfully.
 * retval #kStatus_LPI2C_Busy Another master is currently utilizing the bus.
 * retval #kStatus_LPI2C_Nak The slave device sent a NAK in response to a byte.
 * retval #kStatus_LPI2C_FifoError FIFO under run or overrun.
 * retval #kStatus_LPI2C_ArbitrationLost Arbitration lost error.
 * retval #kStatus_LPI2C_PinLowTimeout SCL or SDA were held low longer than the timeout.
 */
status_t LPI2C_MasterTransferBlocking(LPI2C_Type *base, lpi2c_master_transfer_t *transfer)
{
    assert(NULL != transfer);
    assert(transfer->subaddressSize <= sizeof(transfer->subaddress));

    status_t result = kStatus_Success;
    uint16_t commandBuffer[7];
    uint32_t cmdCount = 0U;

    /* Check transfer data size in read operation. */
    if ((transfer->direction == kLPI2C_Read) &&
        (transfer->dataSize > (256UL * (uint32_t)FSL_FEATURE_LPI2C_FIFO_SIZEn(base))))
    {
        return kStatus_InvalidArgument;
    }

    /* Return an error if the bus is already in use not by us. */
    result = LPI2C_CheckForBusyBus(base);
    if (kStatus_Success == result)
    {
        /* Clear all flags. */
        LPI2C_MasterClearStatusFlags(base, (uint32_t)kLPI2C_MasterClearFlags);

        /* Turn off auto-stop option. */
        base->MCFGR1 &= ~LPI2C_MCFGR1_AUTOSTOP_MASK;

        lpi2c_direction_t direction = (0U != transfer->subaddressSize) ? kLPI2C_Write : transfer->direction;
        if (0U == (transfer->flags & (uint32_t)kLPI2C_TransferNoStartFlag))
        {
            commandBuffer[cmdCount++] =
                (uint16_t)kStartCmd |
                (uint16_t)((uint16_t)((uint16_t)transfer->slaveAddress << 1U) | (uint16_t)direction);
        }

        /* Subaddress, MSB first. */
        if (0U != transfer->subaddressSize)
        {
            uint32_t subaddressRemaining = transfer->subaddressSize;
            while (0U != subaddressRemaining--)
            {
                uint8_t subaddressByte    = (uint8_t)((transfer->subaddress >> (8U * subaddressRemaining)) & 0xffU);
                commandBuffer[cmdCount++] = subaddressByte;
            }
        }

        /* Reads need special handling. */
        if ((0U != transfer->dataSize) && (transfer->direction == kLPI2C_Read))
        {
            /* Need to send repeated start if switching directions to read. */
            if (direction == kLPI2C_Write)
            {
                commandBuffer[cmdCount++] =
                    (uint16_t)kStartCmd |
                    (uint16_t)((uint16_t)((uint16_t)transfer->slaveAddress << 1U) | (uint16_t)kLPI2C_Read);
            }
        }

        /* Send command buffer */
        uint32_t index = 0U;
        while (0U != cmdCount--)
        {
            /* Wait until there is room in the fifo. This also checks for errors. */
            result = LPI2C_MasterWaitForTxReady(base);
            if (kStatus_Success != result)
            {
                break;
            }

            /* Write byte into LPI2C master data register. */
            base->MTDR = commandBuffer[index];
            index++;
        }

        if (kStatus_Success == result)
        {
            /* Transmit data. */
            if ((transfer->direction == kLPI2C_Write) && (transfer->dataSize > 0U))
            {
                /* Send Data. */
                result = LPI2C_MasterSend(base, transfer->data, transfer->dataSize);
            }

            /* Receive Data. */
            if ((transfer->direction == kLPI2C_Read) && (transfer->dataSize > 0U))
            {
                result = LPI2C_MasterReceive(base, transfer->data, transfer->dataSize);
            }

            if (kStatus_Success == result)
            {
                if ((transfer->flags & (uint32_t)kLPI2C_TransferNoStopFlag) == 0U)
                {
                    result = LPI2C_MasterStop(base);
                }
            }
        }

        /* Transmit fail */
        if (kStatus_Success != result)
        {
            if ((transfer->flags & (uint32_t)kLPI2C_TransferNoStopFlag) == 0U)
            {
                (void)LPI2C_MasterStop(base);
            }
        }
    }

    return result;
}

/*!
 * brief Creates a new handle for the LPI2C master non-blocking APIs.
 *
 * The creation of a handle is for use with the non-blocking APIs. Once a handle
 * is created, there is not a corresponding destroy handle. If the user wants to
 * terminate a transfer, the LPI2C_MasterTransferAbort() API shall be called.
 *
 *
 * note The function also enables the NVIC IRQ for the input LPI2C. Need to notice
 * that on some SoCs the LPI2C IRQ is connected to INTMUX, in this case user needs to
 * enable the associated INTMUX IRQ in application.
 *
 * param base The LPI2C peripheral base address.
 * param[out] handle Pointer to the LPI2C master driver handle.
 * param callback User provided pointer to the asynchronous callback function.
 * param userData User provided pointer to the application callback data.
 */
void LPI2C_MasterTransferCreateHandle(LPI2C_Type *base,
                                      lpi2c_master_handle_t *handle,
                                      lpi2c_master_transfer_callback_t callback,
                                      void *userData)
{
    uint32_t instance;

    assert(NULL != handle);
    
    /* Clear out the handle. */
    (void)memset(handle, 0, sizeof(*handle));

    /* Look up instance number */
    instance = LPI2C_GetInstance(base);

    /* Save base and instance. */
    handle->completionCallback = callback;
    handle->userData           = userData;

    if(LP_FLEXCOMM_GetBaseAddress(instance) != 0U)
    {
        lpi2c_to_lpflexcomm_t handler;
        (void)memset(&handler, 0, sizeof(handler));

        /* Save the handle in global variables to support the double weak mechanism. */
        handler.lpi2c_master_handler = LPI2C_MasterTransferHandleIRQ;
        LP_FLEXCOMM_SetIRQHandler(LPI2C_GetInstance(base), handler.lpflexcomm_handler, handle, LP_FLEXCOMM_PERIPH_LPI2C);
    }
    else
    {
         /* Save this handle for IRQ use. */
        s_lpi2cMasterHandle[instance] = handle;

        /* Set irq handler. */
        s_lpi2cMasterIsr = LPI2C_MasterTransferHandleIRQ;
    }

    /* Clear internal IRQ enables and enable NVIC IRQ. */
    LPI2C_MasterDisableInterrupts(base, (uint32_t)kLPI2C_MasterIrqFlags);

    /* Enable NVIC IRQ, this only enables the IRQ directly connected to the NVIC.
     In some cases the LPI2C IRQ is configured through INTMUX, user needs to enable
     INTMUX IRQ in application code. */
    (void)EnableIRQ(kLpi2cIrqs[instance]);
}

/*!
 * @brief Execute states until FIFOs are exhausted.
 * @param handle Master nonblocking driver handle.
 * @param[out] isDone Set to true if the transfer has completed.
 * @retval #kStatus_Success
 * @retval #kStatus_LPI2C_PinLowTimeout
 * @retval #kStatus_LPI2C_ArbitrationLost
 * @retval #kStatus_LPI2C_Nak
 * @retval #kStatus_LPI2C_FifoError
 */
static status_t LPI2C_RunTransferStateMachine(LPI2C_Type *base, lpi2c_master_handle_t *handle, bool *isDone)
{
    uint32_t status;
    status_t result = kStatus_Success;
    lpi2c_master_transfer_t *xfer;
    size_t txCount;
    size_t rxCount;
    size_t txFifoSize   = (size_t)FSL_FEATURE_LPI2C_FIFO_SIZEn(base);
    bool state_complete = false;
    uint16_t sendval;

    /* Set default isDone return value. */
    *isDone = false;

    /* Check for errors. */
    status = LPI2C_MasterGetStatusFlags(base);

    /* Get fifo counts. */
    LPI2C_MasterGetFifoCounts(base, &rxCount, &txCount);

    /* Get pointer to private data. */
    xfer = &handle->transfer;

    /* For the last byte, nack flag is expected.
       Do not check and clear kLPI2C_MasterNackDetectFlag for the last byte,
       in case FIFO is emptied when stop command has not been sent. */
    if (handle->remainingBytes == 0U)
    {
        /* When data size is not zero which means it is not only one byte of address is sent, and */
        /* when the txfifo is empty, or have one byte which is the stop command, then the nack status can be ignored. */
        if ((xfer->dataSize != 0U) &&
            ((txCount == 0U) || ((txCount == 1U) && (handle->state == (uint8_t)kWaitForCompletionState) &&
                                 ((xfer->flags & (uint32_t)kLPI2C_TransferNoStopFlag) == 0U))))
        {
            status &= ~(uint32_t)kLPI2C_MasterNackDetectFlag;
        }
    }

    result = LPI2C_MasterCheckAndClearError(base, status);

    if (kStatus_Success == result)
    {
        /* Compute room in tx fifo */
        txCount = txFifoSize - txCount;

        while (!state_complete)
        {
            /* Execute the state. */
            switch (handle->state)
            {
                case (uint8_t)kSendCommandState:
                    /* Make sure there is room in the tx fifo for the next command. */
                    if (0U == txCount--)
                    {
                        state_complete = true;
                        break;
                    }

                    /* Issue command. buf is a uint8_t* pointing at the uint16 command array. */
                    sendval    = ((uint16_t)handle->buf[0]) | (((uint16_t)handle->buf[1]) << 8U);
                    base->MTDR = sendval;
                    handle->buf++;
                    handle->buf++;

                    /* Count down until all commands are sent. */
                    if (--handle->remainingBytes == 0U)
                    {
                        /* Choose next state and set up buffer pointer and count. */
                        if (0U != xfer->dataSize)
                        {
                            /* Either a send or receive transfer is next. */
                            handle->state          = (uint8_t)kTransferDataState;
                            handle->buf            = (uint8_t *)xfer->data;
                            handle->remainingBytes = (uint16_t)xfer->dataSize;
                            if (xfer->direction == kLPI2C_Read)
                            {
                                /* Disable TX interrupt */
                                LPI2C_MasterDisableInterrupts(base, (uint32_t)kLPI2C_MasterTxReadyFlag);
                                /* Issue command to receive data. A single write to MTDR can issue read operation of
                                   0xFFU + 1 byte of data at most, so when the dataSize is larger than 0x100U, push
                                   multiple read commands to MTDR until dataSize is reached. */
                                size_t tmpRxSize = xfer->dataSize;
                                while (tmpRxSize != 0U)
                                {
                                    LPI2C_MasterGetFifoCounts(base, NULL, &txCount);
                                    while (txFifoSize == txCount)
                                    {
                                        LPI2C_MasterGetFifoCounts(base, NULL, &txCount);
                                    }

                                    if (tmpRxSize > 256U)
                                    {
                                        base->MTDR = (uint32_t)(kRxDataCmd) | (uint32_t)LPI2C_MTDR_DATA(0xFFU);
                                        tmpRxSize -= 256U;
                                    }
                                    else
                                    {
                                        base->MTDR = (uint32_t)(kRxDataCmd) | (uint32_t)LPI2C_MTDR_DATA(tmpRxSize - 1U);
                                        tmpRxSize  = 0U;
                                    }
                                }
                            }
                        }
                        else
                        {
                            /* No transfer, so move to stop state. */
                            handle->state = (uint8_t)kStopState;
                        }
                    }
                    break;

                case (uint8_t)kIssueReadCommandState:
                    /* Make sure there is room in the tx fifo for the read command. */
                    if (0U == txCount--)
                    {
                        state_complete = true;
                        break;
                    }

                    base->MTDR = (uint32_t)kRxDataCmd | LPI2C_MTDR_DATA(xfer->dataSize - 1U);

                    /* Move to transfer state. */
                    handle->state = (uint8_t)kTransferDataState;
                    if (xfer->direction == kLPI2C_Read)
                    {
                        /* Disable TX interrupt */
                        LPI2C_MasterDisableInterrupts(base, (uint32_t)kLPI2C_MasterTxReadyFlag);
                    }
                    break;

                case (uint8_t)kTransferDataState:
                    if (xfer->direction == kLPI2C_Write)
                    {
                        /* Make sure there is room in the tx fifo. */
                        if (0U == txCount--)
                        {
                            state_complete = true;
                            break;
                        }

                        /* Put byte to send in fifo. */
                        base->MTDR = *(handle->buf)++;
                    }
                    else
                    {
                        /* XXX handle receive sizes > 256, use kIssueReadCommandState */
                        /* Make sure there is data in the rx fifo. */
                        if (0U == rxCount--)
                        {
                            state_complete = true;
                            break;
                        }

                        /* Read byte from fifo. */
                        *(handle->buf)++ = (uint8_t)(base->MRDR & LPI2C_MRDR_DATA_MASK);
                    }

                    /* Move to stop when the transfer is done. */
                    if (--handle->remainingBytes == 0U)
                    {
                        if (xfer->direction == kLPI2C_Write)
                        {
                            state_complete = true;
                        }
                        handle->state = (uint8_t)kStopState;
                    }
                    break;

                case (uint8_t)kStopState:
                    /* Only issue a stop transition if the caller requested it. */
                    if ((xfer->flags & (uint32_t)kLPI2C_TransferNoStopFlag) == 0U)
                    {
                        /* Make sure there is room in the tx fifo for the stop command. */
                        if (0U == txCount--)
                        {
                            state_complete = true;
                            break;
                        }

                        base->MTDR = (uint32_t)kStopCmd;
                    }
                    else
                    {
                        /* If all data is read and no stop flag is required to send, we are done. */
                        if (xfer->direction == kLPI2C_Read)
                        {
                            *isDone = true;
                        }
                        state_complete = true;
                    }
                    handle->state = (uint8_t)kWaitForCompletionState;
                    break;

                case (uint8_t)kWaitForCompletionState:
                    if ((xfer->flags & (uint32_t)kLPI2C_TransferNoStopFlag) == 0U)
                    {
                        /* We stay in this state until the stop state is detected. */
                        if (0U != (status & (uint32_t)kLPI2C_MasterStopDetectFlag))
                        {
                            *isDone = true;
                        }
                    }
                    else
                    {
                        /* If all data is pushed to FIFO and no stop flag is required to send, we need to make sure they
                           are all send out to bus. */
                        if ((xfer->direction == kLPI2C_Write) && ((base->MFSR & LPI2C_MFSR_TXCOUNT_MASK) == 0U))
                        {
                            /* We stay in this state until the data is sent out to bus. */
                            *isDone = true;
                        }
                    }
                    state_complete = true;
                    break;
                default:
                    assert(false);
                    break;
            }
        }
    }
    return result;
}

/*!
 * @brief Prepares the transfer state machine and fills in the command buffer.
 * @param handle Master nonblocking driver handle.
 */
static void LPI2C_InitTransferStateMachine(lpi2c_master_handle_t *handle)
{
    lpi2c_master_transfer_t *xfer = &handle->transfer;

    /* Handle no start option. */
    if (0U != (xfer->flags & (uint32_t)kLPI2C_TransferNoStartFlag))
    {
        if (xfer->direction == kLPI2C_Read)
        {
            /* Need to issue read command first. */
            handle->state = (uint8_t)kIssueReadCommandState;
        }
        else
        {
            /* Start immediately in the data transfer state. */
            handle->state = (uint8_t)kTransferDataState;
        }

        handle->buf            = (uint8_t *)xfer->data;
        handle->remainingBytes = (uint16_t)xfer->dataSize;
    }
    else
    {
        uint16_t *cmd     = (uint16_t *)&handle->commandBuffer;
        uint32_t cmdCount = 0U;

        /* Initial direction depends on whether a subaddress was provided, and of course the actual */
        /* data transfer direction. */
        lpi2c_direction_t direction = (0U != xfer->subaddressSize) ? kLPI2C_Write : xfer->direction;

        /* Start command. */
        cmd[cmdCount++] =
            (uint16_t)kStartCmd | (uint16_t)((uint16_t)((uint16_t)xfer->slaveAddress << 1U) | (uint16_t)direction);

        /* Subaddress, MSB first. */
        if (0U != xfer->subaddressSize)
        {
            uint32_t subaddressRemaining = xfer->subaddressSize;
            while (0U != (subaddressRemaining--))
            {
                uint8_t subaddressByte = (uint8_t)((xfer->subaddress >> (8U * subaddressRemaining)) & 0xffU);
                cmd[cmdCount++]        = subaddressByte;
            }
        }

        /* Reads need special handling. */
        if ((0U != xfer->dataSize) && (xfer->direction == kLPI2C_Read))
        {
            /* Need to send repeated start if switching directions to read. */
            if (direction == kLPI2C_Write)
            {
                cmd[cmdCount++] = (uint16_t)kStartCmd |
                                  (uint16_t)((uint16_t)((uint16_t)xfer->slaveAddress << 1U) | (uint16_t)kLPI2C_Read);
            }
        }

        /* Set up state machine for transferring the commands. */
        handle->state          = (uint8_t)kSendCommandState;
        handle->remainingBytes = (uint16_t)cmdCount;
        handle->buf            = (uint8_t *)&handle->commandBuffer;
    }
}

/*!
 * brief Performs a non-blocking transaction on the I2C bus.
 *
 * param base The LPI2C peripheral base address.
 * param handle Pointer to the LPI2C master driver handle.
 * param transfer The pointer to the transfer descriptor.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t LPI2C_MasterTransferNonBlocking(LPI2C_Type *base,
                                         lpi2c_master_handle_t *handle,
                                         lpi2c_master_transfer_t *transfer)
{
    assert(NULL != handle);
    assert(NULL != transfer);
    assert(transfer->subaddressSize <= sizeof(transfer->subaddress));

    status_t result;

    /* Check transfer data size in read operation. */
    if ((transfer->direction == kLPI2C_Read) &&
        (transfer->dataSize > (256U * (uint32_t)FSL_FEATURE_LPI2C_FIFO_SIZEn(base))))
    {
        return kStatus_InvalidArgument;
    }

    /* Return busy if another transaction is in progress. */
    if (handle->state != (uint8_t)kIdleState)
    {
        result = kStatus_LPI2C_Busy;
    }
    else
    {
        result = LPI2C_CheckForBusyBus(base);
    }

    if ((status_t)kStatus_Success == result)
    {
        /* Disable LPI2C IRQ sources while we configure stuff. */
        LPI2C_MasterDisableInterrupts(base, (uint32_t)kLPI2C_MasterIrqFlags);

        /* Reset FIFO in case there are data. */
        base->MCR |= LPI2C_MCR_RRF_MASK | LPI2C_MCR_RTF_MASK;

        /* Save transfer into handle. */
        handle->transfer = *transfer;

        /* Generate commands to send. */
        LPI2C_InitTransferStateMachine(handle);

        /* Clear all flags. */
        LPI2C_MasterClearStatusFlags(base, (uint32_t)kLPI2C_MasterClearFlags);

        /* Turn off auto-stop option. */
        base->MCFGR1 &= ~LPI2C_MCFGR1_AUTOSTOP_MASK;

        /* Enable LPI2C internal IRQ sources. NVIC IRQ was enabled in CreateHandle() */
        LPI2C_MasterEnableInterrupts(base, (uint32_t)kLPI2C_MasterIrqFlags);
    }

    return result;
}

/*!
 * brief Returns number of bytes transferred so far.
 * param base The LPI2C peripheral base address.
 * param handle Pointer to the LPI2C master driver handle.
 * param[out] count Number of bytes transferred so far by the non-blocking transaction.
 * retval #kStatus_Success
 * retval #kStatus_NoTransferInProgress There is not a non-blocking transaction currently in progress.
 */
status_t LPI2C_MasterTransferGetCount(LPI2C_Type *base, lpi2c_master_handle_t *handle, size_t *count)
{
    status_t result = kStatus_Success;

    assert(NULL != handle);

    if (NULL == count)
    {
        result = kStatus_InvalidArgument;
    }

    /* Catch when there is not an active transfer. */
    else if (handle->state == (uint8_t)kIdleState)
    {
        *count = 0;
        result = kStatus_NoTransferInProgress;
    }
    else
    {
        uint8_t state;
        uint16_t remainingBytes;
        uint32_t dataSize;

        /* Cache some fields with IRQs disabled. This ensures all field values */
        /* are synchronized with each other during an ongoing transfer. */
        uint32_t irqs = LPI2C_MasterGetEnabledInterrupts(base);
        LPI2C_MasterDisableInterrupts(base, irqs);
        state          = handle->state;
        remainingBytes = handle->remainingBytes;
        dataSize       = handle->transfer.dataSize;
        LPI2C_MasterEnableInterrupts(base, irqs);

        /* Get transfer count based on current transfer state. */
        switch (state)
        {
            case (uint8_t)kIdleState:
            case (uint8_t)kSendCommandState:
            case (uint8_t)
                kIssueReadCommandState: /* XXX return correct value for this state when >256 reads are supported */
                *count = 0;
                break;

            case (uint8_t)kTransferDataState:
                *count = dataSize - remainingBytes;
                break;

            case (uint8_t)kStopState:
            case (uint8_t)kWaitForCompletionState:
            default:
                *count = dataSize;
                break;
        }
    }

    return result;
}

/*!
 * brief Terminates a non-blocking LPI2C master transmission early.
 *
 * note It is not safe to call this function from an IRQ handler that has a higher priority than the
 *      LPI2C peripheral's IRQ priority.
 *
 * param base The LPI2C peripheral base address.
 * param handle Pointer to the LPI2C master driver handle.
 * retval #kStatus_Success A transaction was successfully aborted.
 * retval #kStatus_LPI2C_Idle There is not a non-blocking transaction currently in progress.
 */
void LPI2C_MasterTransferAbort(LPI2C_Type *base, lpi2c_master_handle_t *handle)
{
    if (handle->state != (uint8_t)kIdleState)
    {
        /* Disable internal IRQ enables. */
        LPI2C_MasterDisableInterrupts(base, (uint32_t)kLPI2C_MasterIrqFlags);

        /* Reset fifos. */
        base->MCR |= LPI2C_MCR_RRF_MASK | LPI2C_MCR_RTF_MASK;

        /* If master is still busy and has not send out stop signal yet. */
        if ((LPI2C_MasterGetStatusFlags(base) & ((uint32_t)kLPI2C_MasterStopDetectFlag |
                                                 (uint32_t)kLPI2C_MasterBusyFlag)) == (uint32_t)kLPI2C_MasterBusyFlag)
        {
            /* Send a stop command to finalize the transfer. */
            base->MTDR = (uint32_t)kStopCmd;
        }

        /* Reset handle. */
        handle->state = (uint8_t)kIdleState;
    }
}

/*!
 * brief Reusable routine to handle master interrupts.
 * note This function does not need to be called unless you are reimplementing the
 *  nonblocking API's interrupt handler routines to add special functionality.
 * param instance The LPI2C instance.
 * param lpi2cMasterHandle Pointer to the LPI2C master driver handle.
 */
void LPI2C_MasterTransferHandleIRQ(uint32_t instance, void *lpi2cMasterHandle)
{
    assert(lpi2cMasterHandle != NULL);
    assert(instance < ARRAY_SIZE(kLpi2cBases));
    LPI2C_Type *base              = kLpi2cBases[instance];
    lpi2c_master_handle_t *handle = (lpi2c_master_handle_t *)lpi2cMasterHandle;
    bool isDone                   = false;
    status_t result;

    /* Don't do anything if we don't have a valid handle. */
    if (NULL != handle)
    {
        if (handle->state != (uint8_t)kIdleState)
        {
            result = LPI2C_RunTransferStateMachine(base, handle, &isDone);

            if ((result != kStatus_Success) || isDone)
            {
                /* Handle error, terminate xfer */
                if (result != kStatus_Success)
                {
                    LPI2C_MasterTransferAbort(base, handle);
                }

                /* Disable internal IRQ enables. */
                LPI2C_MasterDisableInterrupts(base, (uint32_t)kLPI2C_MasterIrqFlags);

                /* Set handle to idle state. */
                handle->state = (uint8_t)kIdleState;

                /* Invoke callback. */
                if (NULL != handle->completionCallback)
                {
                    handle->completionCallback(base, handle, result, handle->userData);
                }
            }
        }
    }
}

/*!
 * brief Provides a default configuration for the LPI2C slave peripheral.
 *
 * This function provides the following default configuration for the LPI2C slave peripheral:
 * code
 *  slaveConfig->enableSlave               = true;
 *  slaveConfig->address0                  = 0U;
 *  slaveConfig->address1                  = 0U;
 *  slaveConfig->addressMatchMode          = kLPI2C_MatchAddress0;
 *  slaveConfig->filterDozeEnable          = true;
 *  slaveConfig->filterEnable              = true;
 *  slaveConfig->enableGeneralCall         = false;
 *  slaveConfig->sclStall.enableAck        = false;
 *  slaveConfig->sclStall.enableTx         = true;
 *  slaveConfig->sclStall.enableRx         = true;
 *  slaveConfig->sclStall.enableAddress    = true;
 *  slaveConfig->ignoreAck                 = false;
 *  slaveConfig->enableReceivedAddressRead = false;
 *  slaveConfig->sdaGlitchFilterWidth_ns   = 0;
 *  slaveConfig->sclGlitchFilterWidth_ns   = 0;
 *  slaveConfig->dataValidDelay_ns         = 0;
 *  slaveConfig->clockHoldTime_ns          = 0;
 * endcode
 *
 * After calling this function, override any settings  to customize the configuration,
 * prior to initializing the master driver with LPI2C_SlaveInit(). Be sure to override at least the a
 * address0 member of the configuration structure with the desired slave address.
 *
 * param[out] slaveConfig User provided configuration structure that is set to default values. Refer to
 *      #lpi2c_slave_config_t.
 */
void LPI2C_SlaveGetDefaultConfig(lpi2c_slave_config_t *slaveConfig)
{
    /* Initializes the configure structure to zero. */
    (void)memset(slaveConfig, 0, sizeof(*slaveConfig));

    slaveConfig->enableSlave               = true;
    slaveConfig->address0                  = 0U;
    slaveConfig->address1                  = 0U;
    slaveConfig->addressMatchMode          = kLPI2C_MatchAddress0;
    slaveConfig->filterDozeEnable          = true;
    slaveConfig->filterEnable              = true;
    slaveConfig->enableGeneralCall         = false;
    slaveConfig->sclStall.enableAck        = false;
    slaveConfig->sclStall.enableTx         = true;
    slaveConfig->sclStall.enableRx         = true;
    slaveConfig->sclStall.enableAddress    = false;
    slaveConfig->ignoreAck                 = false;
    slaveConfig->enableReceivedAddressRead = false;
    slaveConfig->sdaGlitchFilterWidth_ns   = 0U; /* Set to 0 to disable the function */
    slaveConfig->sclGlitchFilterWidth_ns   = 0U; /* Set to 0 to disable the function */
    slaveConfig->dataValidDelay_ns         = 0U;
    /* When enabling the slave tx SCL stall, set the default clock hold time to 250ns according
       to I2C spec for standard mode baudrate(100k). User can manually change it to 100ns or 50ns
       for fast-mode(400k) or fast-mode+(1m). */
    slaveConfig->clockHoldTime_ns = 250U;
}

/*!
 * brief Initializes the LPI2C slave peripheral.
 *
 * This function enables the peripheral clock and initializes the LPI2C slave peripheral as described by the user
 * provided configuration.
 *
 * param base The LPI2C peripheral base address.
 * param slaveConfig User provided peripheral configuration. Use LPI2C_SlaveGetDefaultConfig() to get a set of defaults
 *      that you can override.
 * param sourceClock_Hz Frequency in Hertz of the LPI2C functional clock. Used to calculate the filter widths,
 *      data valid delay, and clock hold time.
 */
void LPI2C_SlaveInit(LPI2C_Type *base, const lpi2c_slave_config_t *slaveConfig, uint32_t sourceClock_Hz)
{
    uint32_t tmpReg;
    uint32_t tmpCycle;
    uint32_t instance = LPI2C_GetInstance(base);

    if(LP_FLEXCOMM_GetBaseAddress(instance) != 0U)
    {
      
#if !(defined(LPFLEXCOMM_INIT_NOT_USED_IN_DRIVER) && LPFLEXCOMM_INIT_NOT_USED_IN_DRIVER)
        /* initialize flexcomm to LPI2C mode */
        status_t status = LP_FLEXCOMM_Init(instance, LP_FLEXCOMM_PERIPH_LPI2C);
        if (kStatus_Success != status)
        {
            assert(false);
        }
#endif /* LPFLEXCOMM_INIT_NOT_USED_IN_DRIVER */
        
    }
    else
    {
      
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
        /* Ungate the clock. */
        (void)CLOCK_EnableClock(kLpi2cClocks[instance]);
#if defined(LPI2C_PERIPH_CLOCKS)
        /* Ungate the functional clock in initialize function. */
        CLOCK_EnableClock(kLpi2cPeriphClocks[instance]);
#endif

#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
      
    }

    /* Restore to reset conditions. */
    LPI2C_SlaveReset(base);

    /* Configure peripheral. */
    base->SAMR = LPI2C_SAMR_ADDR0(slaveConfig->address0) | LPI2C_SAMR_ADDR1(slaveConfig->address1);

    base->SCFGR1 =
        LPI2C_SCFGR1_ADDRCFG(slaveConfig->addressMatchMode) | LPI2C_SCFGR1_IGNACK(slaveConfig->ignoreAck) |
        LPI2C_SCFGR1_RXCFG(slaveConfig->enableReceivedAddressRead) | LPI2C_SCFGR1_GCEN(slaveConfig->enableGeneralCall) |
        LPI2C_SCFGR1_ACKSTALL(slaveConfig->sclStall.enableAck) | LPI2C_SCFGR1_TXDSTALL(slaveConfig->sclStall.enableTx) |
        LPI2C_SCFGR1_RXSTALL(slaveConfig->sclStall.enableRx) |
        LPI2C_SCFGR1_ADRSTALL(slaveConfig->sclStall.enableAddress);

    /* Calculate SDA filter width. The width is equal to FILTSDA+3 cycles of functional clock.
       And set FILTSDA to 0 disables the fileter, so the min value is 4. */
    tmpReg = LPI2C_SCFGR2_FILTSDA(
        LPI2C_GetCyclesForWidth(sourceClock_Hz, slaveConfig->sdaGlitchFilterWidth_ns, 4U,
                                (LPI2C_SCFGR2_FILTSDA_MASK >> LPI2C_SCFGR2_FILTSDA_SHIFT) + 3U, 0U) -
        3U);

    /* Calculate SDL filter width. The width is equal to FILTSCL+3 cycles of functional clock.
       And set FILTSCL to 0 disables the fileter, so the min value is 4. */
    tmpCycle = LPI2C_GetCyclesForWidth(sourceClock_Hz, slaveConfig->sclGlitchFilterWidth_ns, 4U,
                                       (LPI2C_SCFGR2_FILTSCL_MASK >> LPI2C_SCFGR2_FILTSCL_SHIFT) + 3U, 0U);
    tmpReg |= LPI2C_SCFGR2_FILTSCL(tmpCycle - 3U);

    /* Calculate data valid time. The time is equal to FILTSCL+DATAVD+3 cycles of functional clock.
       So the min value is FILTSCL+3. */
    tmpReg |= LPI2C_SCFGR2_DATAVD(
        LPI2C_GetCyclesForWidth(sourceClock_Hz, slaveConfig->dataValidDelay_ns, tmpCycle,
                                tmpCycle + (LPI2C_SCFGR2_DATAVD_MASK >> LPI2C_SCFGR2_DATAVD_SHIFT), 0U) -
        tmpCycle);

    /* Calculate clock hold time. The time is equal to CLKHOLD+3 cycles of functional clock.
       So the min value is 3. */
    base->SCFGR2 =
        tmpReg | LPI2C_SCFGR2_CLKHOLD(
                     LPI2C_GetCyclesForWidth(sourceClock_Hz, slaveConfig->clockHoldTime_ns, 3U,
                                             (LPI2C_SCFGR2_CLKHOLD_MASK >> LPI2C_SCFGR2_CLKHOLD_SHIFT) + 3U, 0U) -
                     3U);

    /* Save SCR to last so we don't enable slave until it is configured */
    base->SCR = LPI2C_SCR_FILTDZ(!slaveConfig->filterDozeEnable) | LPI2C_SCR_FILTEN(slaveConfig->filterEnable) |
                LPI2C_SCR_SEN(slaveConfig->enableSlave);
}

/*!
 * brief Deinitializes the LPI2C slave peripheral.
 *
 * This function disables the LPI2C slave peripheral and gates the clock. It also performs a software
 * reset to restore the peripheral to reset conditions.
 *
 * param base The LPI2C peripheral base address.
 */
void LPI2C_SlaveDeinit(LPI2C_Type *base)
{
    uint32_t instance = LPI2C_GetInstance(base); 

    /* Restore to reset state. */
    LPI2C_SlaveReset(base);
    if(LP_FLEXCOMM_GetBaseAddress(instance) != 0U)
    {
#if !(defined(LPFLEXCOMM_INIT_NOT_USED_IN_DRIVER) && LPFLEXCOMM_INIT_NOT_USED_IN_DRIVER)
        LP_FLEXCOMM_Deinit(instance);
#endif
    }
    else
    {
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
        /* Gate clock. */
        (void)CLOCK_DisableClock(kLpi2cClocks[instance]);
#if defined(LPI2C_PERIPH_CLOCKS)
        /* Gate the functional clock. */
        CLOCK_DisableClock(kLpi2cPeriphClocks[instance]);
#endif

#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
    }
}

/*!
 * @brief Convert provided flags to status code, and clear any errors if present.
 * @param base The LPI2C peripheral base address.
 * @param status Current status flags value that will be checked.
 * @retval #kStatus_Success
 * @retval #kStatus_LPI2C_BitError
 * @retval #kStatus_LPI2C_FifoError
 */
static status_t LPI2C_SlaveCheckAndClearError(LPI2C_Type *base, uint32_t flags)
{
    status_t result = kStatus_Success;

    flags &= (uint32_t)kLPI2C_SlaveErrorFlags;
    if (0U != flags)
    {
        if (0U != (flags & (uint32_t)kLPI2C_SlaveBitErrFlag))
        {
            result = kStatus_LPI2C_BitError;
        }
        else if (0U != (flags & (uint32_t)kLPI2C_SlaveFifoErrFlag))
        {
            result = kStatus_LPI2C_FifoError;
        }
        else
        {
            ; /* Intentional empty */
        }

        /* Clear the errors. */
        LPI2C_SlaveClearStatusFlags(base, flags);
    }
    else
    {
        ; /* Intentional empty */
    }

    return result;
}

/*!
 * brief Performs a polling send transfer on the I2C bus.
 *
 * param base  The LPI2C peripheral base address.
 * param txBuff The pointer to the data to be transferred.
 * param txSize The length in bytes of the data to be transferred.
 * param[out] actualTxSize
 * return Error or success status returned by API.
 */
status_t LPI2C_SlaveSend(LPI2C_Type *base, void *txBuff, size_t txSize, size_t *actualTxSize)
{
    status_t result  = kStatus_Success;
    uint8_t *buf     = (uint8_t *)txBuff;
    size_t remaining = txSize;

    assert(NULL != txBuff);

#if I2C_RETRY_TIMES != 0U
    uint32_t waitTimes = I2C_RETRY_TIMES;
#endif

    /* Clear stop flag. */
    LPI2C_SlaveClearStatusFlags(base,
                                (uint32_t)kLPI2C_SlaveStopDetectFlag | (uint32_t)kLPI2C_SlaveRepeatedStartDetectFlag);

    while (0U != remaining)
    {
        uint32_t flags;

        /* Wait until we can transmit. */
        do
        {
            /* Check for errors */
            flags  = LPI2C_SlaveGetStatusFlags(base);
            result = LPI2C_SlaveCheckAndClearError(base, flags);
            if (kStatus_Success != result)
            {
                if (NULL != actualTxSize)
                {
                    *actualTxSize = txSize - remaining;
                }
                break;
            }
#if I2C_RETRY_TIMES != 0U
            waitTimes--;
        } while ((0U == (flags & ((uint32_t)kLPI2C_SlaveTxReadyFlag | (uint32_t)kLPI2C_SlaveStopDetectFlag |
                                  (uint32_t)kLPI2C_SlaveRepeatedStartDetectFlag))) &&
                 (0U != waitTimes));
        if (0U == waitTimes)
        {
            result = kStatus_LPI2C_Timeout;
        }
#else
        } while (0U == (flags & ((uint32_t)kLPI2C_SlaveTxReadyFlag | (uint32_t)kLPI2C_SlaveStopDetectFlag |
                                 (uint32_t)kLPI2C_SlaveRepeatedStartDetectFlag)));
#endif

        if (kStatus_Success != result)
        {
            break;
        }

        /* Send a byte. */
        if (0U != (flags & (uint32_t)kLPI2C_SlaveTxReadyFlag))
        {
            base->STDR = *buf++;
            --remaining;
        }

        /* Exit loop if we see a stop or restart in transfer*/
        if ((0U != (flags & ((uint32_t)kLPI2C_SlaveStopDetectFlag | (uint32_t)kLPI2C_SlaveRepeatedStartDetectFlag))) &&
            (remaining != 0U))
        {
            LPI2C_SlaveClearStatusFlags(
                base, (uint32_t)kLPI2C_SlaveStopDetectFlag | (uint32_t)kLPI2C_SlaveRepeatedStartDetectFlag);
            break;
        }
    }

    if (NULL != actualTxSize)
    {
        *actualTxSize = txSize - remaining;
    }

    return result;
}

/*!
 * brief Performs a polling receive transfer on the I2C bus.
 *
 * param base  The LPI2C peripheral base address.
 * param rxBuff The pointer to the data to be transferred.
 * param rxSize The length in bytes of the data to be transferred.
 * param[out] actualRxSize
 * return Error or success status returned by API.
 */
status_t LPI2C_SlaveReceive(LPI2C_Type *base, void *rxBuff, size_t rxSize, size_t *actualRxSize)
{
    status_t result  = kStatus_Success;
    uint8_t *buf     = (uint8_t *)rxBuff;
    size_t remaining = rxSize;

    assert(NULL != rxBuff);

#if I2C_RETRY_TIMES != 0U
    uint32_t waitTimes = I2C_RETRY_TIMES;
#endif

    /* Clear stop flag. */
    LPI2C_SlaveClearStatusFlags(base,
                                (uint32_t)kLPI2C_SlaveStopDetectFlag | (uint32_t)kLPI2C_SlaveRepeatedStartDetectFlag);

    while (0U != remaining)
    {
        uint32_t flags;

        /* Wait until we can receive. */
        do
        {
            /* Check for errors */
            flags  = LPI2C_SlaveGetStatusFlags(base);
            result = LPI2C_SlaveCheckAndClearError(base, flags);
            if (kStatus_Success != result)
            {
                if (NULL != actualRxSize)
                {
                    *actualRxSize = rxSize - remaining;
                }
                break;
            }
#if I2C_RETRY_TIMES != 0U
            waitTimes--;
        } while ((0U == (flags & ((uint32_t)kLPI2C_SlaveRxReadyFlag | (uint32_t)kLPI2C_SlaveStopDetectFlag |
                                  (uint32_t)kLPI2C_SlaveRepeatedStartDetectFlag))) &&
                 (0U != waitTimes));
        if (0U == waitTimes)
        {
            result = kStatus_LPI2C_Timeout;
        }
#else
        } while (0U == (flags & ((uint32_t)kLPI2C_SlaveRxReadyFlag | (uint32_t)kLPI2C_SlaveStopDetectFlag |
                                 (uint32_t)kLPI2C_SlaveRepeatedStartDetectFlag)));
#endif

        if ((status_t)kStatus_Success != result)
        {
            break;
        }

        /* Receive a byte. */
        if (0U != (flags & (uint32_t)kLPI2C_SlaveRxReadyFlag))
        {
            *buf++ = (uint8_t)(base->SRDR & LPI2C_SRDR_DATA_MASK);
            --remaining;
        }

        /* Exit loop if we see a stop or restart */
        if ((0U != (flags & ((uint32_t)kLPI2C_SlaveStopDetectFlag | (uint32_t)kLPI2C_SlaveRepeatedStartDetectFlag))) &&
            (remaining != 0U))
        {
            LPI2C_SlaveClearStatusFlags(
                base, (uint32_t)kLPI2C_SlaveStopDetectFlag | (uint32_t)kLPI2C_SlaveRepeatedStartDetectFlag);
            break;
        }
    }

    if (NULL != actualRxSize)
    {
        *actualRxSize = rxSize - remaining;
    }

    return result;
}

/*!
 * brief Creates a new handle for the LPI2C slave non-blocking APIs.
 *
 * The creation of a handle is for use with the non-blocking APIs. Once a handle
 * is created, there is not a corresponding destroy handle. If the user wants to
 * terminate a transfer, the LPI2C_SlaveTransferAbort() API shall be called.
 *
 * note The function also enables the NVIC IRQ for the input LPI2C. Need to notice
 * that on some SoCs the LPI2C IRQ is connected to INTMUX, in this case user needs to
 * enable the associated INTMUX IRQ in application.

 * param base The LPI2C peripheral base address.
 * param[out] handle Pointer to the LPI2C slave driver handle.
 * param callback User provided pointer to the asynchronous callback function.
 * param userData User provided pointer to the application callback data.
 */
void LPI2C_SlaveTransferCreateHandle(LPI2C_Type *base,
                                     lpi2c_slave_handle_t *handle,
                                     lpi2c_slave_transfer_callback_t callback,
                                     void *userData)
{
    uint32_t instance;

    assert(NULL != handle);
    
    /* Clear out the handle. */
    (void)memset(handle, 0, sizeof(*handle));

    /* Look up instance number */
    instance = LPI2C_GetInstance(base);

    /* Save base and instance. */
    handle->callback = callback;
    handle->userData = userData;

    if(LP_FLEXCOMM_GetBaseAddress(instance) != 0U)
    {
        lpi2c_to_lpflexcomm_t handler;
        (void)memset(&handler, 0, sizeof(handler));

        /* Save the handle in global variables to support the double weak mechanism. */
        handler.lpi2c_slave_handler = LPI2C_SlaveTransferHandleIRQ;
        LP_FLEXCOMM_SetIRQHandler(LPI2C_GetInstance(base), handler.lpflexcomm_handler, handle, LP_FLEXCOMM_PERIPH_LPI2C);
    }
    else
    {        
        /* Save this handle for IRQ use. */
        s_lpi2cSlaveHandle[instance] = handle;

        /* Set irq handler. */
        s_lpi2cSlaveIsr = LPI2C_SlaveTransferHandleIRQ;
    }

    /* Clear internal IRQ enables and enable NVIC IRQ. */
    LPI2C_SlaveDisableInterrupts(base, (uint32_t)kLPI2C_SlaveIrqFlags);
    (void)EnableIRQ(kLpi2cIrqs[instance]);

    /* Nack by default. */
    base->STAR = LPI2C_STAR_TXNACK_MASK;
}

/*!
 * brief Starts accepting slave transfers.
 *
 * Call this API after calling I2C_SlaveInit() and LPI2C_SlaveTransferCreateHandle() to start processing
 * transactions driven by an I2C master. The slave monitors the I2C bus and pass events to the
 * callback that was passed into the call to LPI2C_SlaveTransferCreateHandle(). The callback is always invoked
 * from the interrupt context.
 *
 * The set of events received by the callback is customizable. To do so, set the a eventMask parameter to
 * the OR'd combination of #lpi2c_slave_transfer_event_t enumerators for the events you wish to receive.
 * The #kLPI2C_SlaveTransmitEvent and #kLPI2C_SlaveReceiveEvent events are always enabled and do not need
 * to be included in the mask. Alternatively, you can pass 0 to get a default set of only the transmit and
 * receive events that are always enabled. In addition, the #kLPI2C_SlaveAllEvents constant is provided as
 * a convenient way to enable all events.
 *
 * param base The LPI2C peripheral base address.
 * param handle Pointer to #lpi2c_slave_handle_t structure which stores the transfer state.
 * param eventMask Bit mask formed by OR'ing together #lpi2c_slave_transfer_event_t enumerators to specify
 *      which events to send to the callback. Other accepted values are 0 to get a default set of
 *      only the transmit and receive events, and #kLPI2C_SlaveAllEvents to enable all events.
 *
 * retval #kStatus_Success Slave transfers were successfully started.
 * retval #kStatus_LPI2C_Busy Slave transfers have already been started on this handle.
 */
status_t LPI2C_SlaveTransferNonBlocking(LPI2C_Type *base, lpi2c_slave_handle_t *handle, uint32_t eventMask)
{
    status_t result = kStatus_Success;

    assert(NULL != handle);

    /* Return busy if another transaction is in progress. */
    if (handle->isBusy)
    {
        result = kStatus_LPI2C_Busy;
    }
    else
    {
        /* Return an error if the bus is already in use not by us. */
        uint32_t status = LPI2C_SlaveGetStatusFlags(base);
        if ((0U != (status & (uint32_t)kLPI2C_SlaveBusBusyFlag)) && (0U == (status & (uint32_t)kLPI2C_SlaveBusyFlag)))
        {
            result = kStatus_LPI2C_Busy;
        }
    }

    if ((status_t)kStatus_Success == result)
    {
        /* Disable LPI2C IRQ sources while we configure stuff. */
        LPI2C_SlaveDisableInterrupts(base, (uint32_t)kLPI2C_SlaveIrqFlags);

        /* Clear transfer in handle. */
        (void)memset(&handle->transfer, 0, sizeof(handle->transfer));

        /* Record that we're busy. */
        handle->isBusy = true;

        /* Set up event mask. tx and rx are always enabled. */
        handle->eventMask = eventMask | (uint32_t)kLPI2C_SlaveTransmitEvent | (uint32_t)kLPI2C_SlaveReceiveEvent;

        /* Ack by default. */
        base->STAR = 0U;

        /* Clear all flags. */
        LPI2C_SlaveClearStatusFlags(base, (uint32_t)kLPI2C_SlaveClearFlags);

        /* Enable LPI2C internal IRQ sources. NVIC IRQ was enabled in CreateHandle() */
        LPI2C_SlaveEnableInterrupts(base, (uint32_t)kLPI2C_SlaveIrqFlags);
    }

    return result;
}

/*!
 * brief Gets the slave transfer status during a non-blocking transfer.
 * param base The LPI2C peripheral base address.
 * param handle Pointer to i2c_slave_handle_t structure.
 * param[out] count Pointer to a value to hold the number of bytes transferred. May be NULL if the count is not
 *      required.
 * retval #kStatus_Success
 * retval #kStatus_NoTransferInProgress
 */
status_t LPI2C_SlaveTransferGetCount(LPI2C_Type *base, lpi2c_slave_handle_t *handle, size_t *count)
{
    status_t status = kStatus_Success;

    assert(NULL != handle);

    if (count == NULL)
    {
        status = kStatus_InvalidArgument;
    }

    /* Catch when there is not an active transfer. */
    else if (!handle->isBusy)
    {
        *count = 0;
        status = kStatus_NoTransferInProgress;
    }

    /* For an active transfer, just return the count from the handle. */
    else
    {
        *count = handle->transferredCount;
    }

    return status;
}

/*!
 * brief Aborts the slave non-blocking transfers.
 * note This API could be called at any time to stop slave for handling the bus events.
 * param base The LPI2C peripheral base address.
 * param handle Pointer to #lpi2c_slave_handle_t structure which stores the transfer state.
 * retval #kStatus_Success
 * retval #kStatus_LPI2C_Idle
 */
void LPI2C_SlaveTransferAbort(LPI2C_Type *base, lpi2c_slave_handle_t *handle)
{
    assert(NULL != handle);

    /* Return idle if no transaction is in progress. */
    if (handle->isBusy)
    {
        /* Disable LPI2C IRQ sources. */
        LPI2C_SlaveDisableInterrupts(base, (uint32_t)kLPI2C_SlaveIrqFlags);

        /* Nack by default. */
        base->STAR = LPI2C_STAR_TXNACK_MASK;

        /* Reset transfer info. */
        (void)memset(&handle->transfer, 0, sizeof(handle->transfer));

        /* We're no longer busy. */
        handle->isBusy = false;
    }
}

/*!
 * brief Reusable routine to handle slave interrupts.
 * note This function does not need to be called unless you are reimplementing the
 *  non blocking API's interrupt handler routines to add special functionality.
 * param instance The LPI2C instance.
 * param lpi2cSlaveHandle Pointer to #lpi2c_slave_handle_t structure which stores the transfer state.
 */
void LPI2C_SlaveTransferHandleIRQ(uint32_t instance, void *lpi2cSlaveHandle)
{
    assert(instance < ARRAY_SIZE(kLpi2cBases));
    uint32_t flags;
    lpi2c_slave_transfer_t *xfer;
    LPI2C_Type *base             = kLpi2cBases[instance];
    lpi2c_slave_handle_t *handle = (lpi2c_slave_handle_t *)lpi2cSlaveHandle;

    /* Check for a valid handle in case of a spurious interrupt. */
    if (NULL != handle)
    {
        xfer = &handle->transfer;

        /* Get status flags. */
        flags = LPI2C_SlaveGetStatusFlags(base);

        if (0U != (flags & ((uint32_t)kLPI2C_SlaveBitErrFlag | (uint32_t)kLPI2C_SlaveFifoErrFlag)))
        {
            xfer->event            = kLPI2C_SlaveCompletionEvent;
            xfer->completionStatus = LPI2C_SlaveCheckAndClearError(base, flags);

            if ((0U != (handle->eventMask & (uint32_t)kLPI2C_SlaveCompletionEvent)) && (NULL != handle->callback))
            {
                handle->callback(base, xfer, handle->userData);
            }
        }
        else
        {
            if (0U !=
                (flags & (((uint32_t)kLPI2C_SlaveRepeatedStartDetectFlag) | ((uint32_t)kLPI2C_SlaveStopDetectFlag))))
            {
                xfer->event = (0U != (flags & (uint32_t)kLPI2C_SlaveRepeatedStartDetectFlag)) ?
                                  kLPI2C_SlaveRepeatedStartEvent :
                                  kLPI2C_SlaveCompletionEvent;
                xfer->receivedAddress  = 0U;
                xfer->completionStatus = kStatus_Success;
                xfer->transferredCount = handle->transferredCount;

                if (xfer->event == kLPI2C_SlaveCompletionEvent)
                {
                    handle->isBusy = false;
                }

                if (handle->wasTransmit)
                {
                    /* Subtract one from the transmit count to offset the fact that LPI2C asserts the */
                    /* tx flag before it sees the nack from the master-receiver, thus causing one more */
                    /* count that the master actually receives. */
                    --xfer->transferredCount;
                    handle->wasTransmit = false;
                }

                /* Clear the flag. */
                LPI2C_SlaveClearStatusFlags(base, flags & ((uint32_t)kLPI2C_SlaveRepeatedStartDetectFlag |
                                                           (uint32_t)kLPI2C_SlaveStopDetectFlag));

                /* Revert to sending an Ack by default, in case we sent a Nack for receive. */
                base->STAR = 0U;

                if ((0U != (handle->eventMask & (uint32_t)xfer->event)) && (NULL != handle->callback))
                {
                    handle->callback(base, xfer, handle->userData);
                }

                if (0U != (flags & (uint32_t)kLPI2C_SlaveStopDetectFlag))
                {
                    /* Clean up transfer info on completion, after the callback has been invoked. */
                    (void)memset(&handle->transfer, 0, sizeof(handle->transfer));
                }
            }
            if (0U != (flags & (uint32_t)kLPI2C_SlaveAddressValidFlag))
            {
                xfer->event           = kLPI2C_SlaveAddressMatchEvent;
                xfer->receivedAddress = (uint8_t)(base->SASR & LPI2C_SASR_RADDR_MASK);

                /* Update handle status to busy because slave is addressed. */
                handle->isBusy = true;
                if ((0U != (handle->eventMask & (uint32_t)kLPI2C_SlaveAddressMatchEvent)) && (NULL != handle->callback))
                {
                    handle->callback(base, xfer, handle->userData);
                }
            }
            if (0U != (flags & (uint32_t)kLPI2C_SlaveTransmitAckFlag))
            {
                xfer->event = kLPI2C_SlaveTransmitAckEvent;

                if ((0U != (handle->eventMask & (uint32_t)kLPI2C_SlaveTransmitAckEvent)) && (NULL != handle->callback))
                {
                    handle->callback(base, xfer, handle->userData);
                }
                else
                {
                    LPI2C_SlaveTransmitAck(base, true);
                }
            }

            /* Handle transmit and receive. */
            if (0U != (flags & (uint32_t)kLPI2C_SlaveTxReadyFlag))
            {
                handle->wasTransmit = true;

                /* If we're out of data, invoke callback to get more. */
                if ((NULL == xfer->data) || (0U == xfer->dataSize))
                {
                    xfer->event = kLPI2C_SlaveTransmitEvent;
                    if (NULL != handle->callback)
                    {
                        handle->callback(base, xfer, handle->userData);
                    }

                    /* Clear the transferred count now that we have a new buffer. */
                    handle->transferredCount = 0U;
                }

                /* Transmit a byte. */
                if ((NULL != xfer->data) && (0U != xfer->dataSize))
                {
                    base->STDR = *xfer->data++;
                    --xfer->dataSize;
                    ++handle->transferredCount;
                }
            }
            if (0U != (flags & (uint32_t)kLPI2C_SlaveRxReadyFlag))
            {
                /* If we're out of room in the buffer, invoke callback to get another. */
                if ((NULL == xfer->data) || (0U == xfer->dataSize))
                {
                    xfer->event = kLPI2C_SlaveReceiveEvent;
                    if (NULL != handle->callback)
                    {
                        handle->callback(base, xfer, handle->userData);
                    }

                    /* Clear the transferred count now that we have a new buffer. */
                    handle->transferredCount = 0U;
                }

                /* Receive a byte. */
                if ((NULL != xfer->data) && (0U != xfer->dataSize))
                {
                    *xfer->data++ = (uint8_t)base->SRDR;
                    --xfer->dataSize;
                    ++handle->transferredCount;
					if (0U != (base->SCFGR1 & LPI2C_SCFGR1_ACKSTALL_MASK))
                    {
                        if (((0U == (handle->eventMask & (uint32_t)kLPI2C_SlaveTransmitAckEvent)) ||
                             (NULL == handle->callback)))
                        {
                            LPI2C_SlaveTransmitAck(base, true);
                        }
                    }
                }
                else
                {
                    /* We don't have any room to receive more data, so send a nack. */
                    if (0U != (base->SCFGR1 & LPI2C_SCFGR1_ACKSTALL_MASK))
                    {
                        if (((0U == (handle->eventMask & (uint32_t)kLPI2C_SlaveTransmitAckEvent)) ||
                             (NULL == handle->callback)))
                        {
                            LPI2C_SlaveTransmitAck(base, false);
                        }
                    }
                }
            }
        }
    }
}

#if !(defined(FSL_FEATURE_I2C_HAS_NO_IRQ) && FSL_FEATURE_I2C_HAS_NO_IRQ)
/*!
 * @brief Shared IRQ handler that can call both master and slave ISRs.
 *
 * The master and slave ISRs are called through function pointers in order to decouple
 * this code from the ISR functions. Without this, the linker would always pull in both
 * ISRs and every function they call, even if only the functional API was used.
 *
 * @param base The LPI2C peripheral base address.
 * @param instance The LPI2C peripheral instance number.
 */
void LPI2C_CommonIRQHandler(LPI2C_Type *base, uint32_t instance);
void LPI2C_CommonIRQHandler(LPI2C_Type *base, uint32_t instance)
{
    /* Check for master IRQ. */
    if ((0U != (base->MCR & LPI2C_MCR_MEN_MASK)) && (NULL != s_lpi2cMasterIsr))
    {
        /* Master mode. */
        s_lpi2cMasterIsr(instance, s_lpi2cMasterHandle[instance]);
    }

    /* Check for slave IRQ. */
    if ((0U != (base->SCR & LPI2C_SCR_SEN_MASK)) && (NULL != s_lpi2cSlaveIsr))
    {
        /* Slave mode. */
        s_lpi2cSlaveIsr(instance, s_lpi2cSlaveHandle[instance]);
    }
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if defined(LPI2C15)
/* Implementation of LPI2C15 handler named in startup code. */
void LPI2C15_DriverIRQHandler(void);
void LPI2C15_DriverIRQHandler(void)
{
    LPI2C_CommonIRQHandler(LPI2C15, 15U);
}
#endif
