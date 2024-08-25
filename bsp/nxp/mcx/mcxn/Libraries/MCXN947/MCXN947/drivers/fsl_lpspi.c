/*
 * Copyright 2022-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_lpspi.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.lpflexcomm_lpspi"
#endif

/*!
 * @brief Default watermark values.
 *
 * The default watermarks are set to zero.
 */
enum _lpspi_default_watermarks
{
    kLpspiDefaultTxWatermark = 0,
    kLpspiDefaultRxWatermark = 0,
};

/*! @brief Typedef for master interrupt handler. */
typedef void (*lpspi_master_isr_t)(uint32_t instance, lpspi_master_handle_t *handle);

/*! @brief Typedef for slave interrupt handler. */
typedef void (*lpspi_slave_isr_t)(uint32_t instance, lpspi_slave_handle_t *handle);

/*!
 * @brief Used for conversion from `lpflexcomm_irq_handler_t` to `lpuart_irq_handler_t`
 */
typedef union lpspi_to_lpflexcomm
{
    lpspi_master_isr_t lpspi_master_handler;
    lpspi_slave_isr_t lpspi_slave_handler;
    lpflexcomm_irq_handler_t lpflexcomm_handler;
} lpspi_to_lpflexcomm_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Configures the LPSPI peripheral chip select polarity.
 *
 * This function  takes in the desired peripheral chip select (Pcs) and it's corresponding desired polarity and
 * configures the Pcs signal to operate with the desired characteristic.
 *
 * @param base LPSPI peripheral address.
 * @param pcs The particular peripheral chip select (parameter value is of type lpspi_which_pcs_t) for which we wish to
 *            apply the active high or active low characteristic.
 * @param activeLowOrHigh The setting for either "active high, inactive low (0)"  or "active low, inactive high(1)" of
 *                        type lpspi_pcs_polarity_config_t.
 */
static void LPSPI_SetOnePcsPolarity(LPSPI_Type *base,
                                    lpspi_which_pcs_t pcs,
                                    lpspi_pcs_polarity_config_t activeLowOrHigh);

/*!
 * @brief Combine the write data for 1 byte to 4 bytes.
 * This is not a public API.
 */
static uint32_t LPSPI_CombineWriteData(const uint8_t *txData, uint8_t bytesEachWrite, bool isByteSwap);

/*!
 * @brief Separate the read data for 1 byte to 4 bytes.
 * This is not a public API.
 */
static void LPSPI_SeparateReadData(uint8_t *rxData, uint32_t readData, uint8_t bytesEachRead, bool isByteSwap);

/*!
 * @brief Wait for tx FIFO to be empty.
 * This is not a public API.
 * @param base LPSPI peripheral address.
 * @return true for the tx FIFO is ready, false is not.
 */
static bool LPSPI_TxFifoReady(LPSPI_Type *base);

/*!
 * @brief Master fill up the TX FIFO with data.
 * This is not a public API.
 */
static void LPSPI_MasterTransferFillUpTxFifo(LPSPI_Type *base, lpspi_master_handle_t *handle);

/*!
 * @brief Master finish up a transfer.
 * It would call back if there is callback function and set the state to idle.
 * This is not a public API.
 */
static void LPSPI_MasterTransferComplete(LPSPI_Type *base, lpspi_master_handle_t *handle);

/*!
 * @brief Slave fill up the TX FIFO with data.
 * This is not a public API.
 */
static void LPSPI_SlaveTransferFillUpTxFifo(LPSPI_Type *base, lpspi_slave_handle_t *handle);

/*!
 * @brief Slave finish up a transfer.
 * It would call back if there is callback function and set the state to idle.
 * This is not a public API.
 */
static void LPSPI_SlaveTransferComplete(LPSPI_Type *base, lpspi_slave_handle_t *handle);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Defines constant value arrays for the baud rate pre-scalar and scalar divider values.*/
static const uint8_t s_baudratePrescaler[] = {1, 2, 4, 8, 16, 32, 64, 128};

/*! @brief Pointers to lpspi bases for each instance. */
static LPSPI_Type *const s_lpspiBases[] = LPSPI_BASE_PTRS;

/*! @brief Pointers to lpspi IRQ number for each instance. */
static const IRQn_Type s_lpspiIRQ[] = LPSPI_IRQS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to lpspi clocks for each instance. */
static const clock_ip_name_t s_lpspiClocks[] = LPSPI_CLOCKS;

#if defined(LPSPI_PERIPH_CLOCKS)
static const clock_ip_name_t s_LpspiPeriphClocks[] = LPSPI_PERIPH_CLOCKS;
#endif

#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*! @brief Pointers to lpspi handles for each instance. */
static void *s_lpspiHandle[ARRAY_SIZE(s_lpspiBases)];

/* @brief Dummy data for each instance. This data is used when user's tx buffer is NULL*/
volatile uint8_t g_lpspiDummyData[ARRAY_SIZE(s_lpspiBases)] = {0};

/*! @brief Pointer to master IRQ handler for each instance. */
static lpspi_master_isr_t s_lpspiMasterIsr;
/*! @brief Pointer to slave IRQ handler for each instance. */
static lpspi_slave_isr_t s_lpspiSlaveIsr;

/**********************************************************************************************************************
 * Code
 *********************************************************************************************************************/

/*!
 * brief Get the LPSPI instance from peripheral base address.
 *
 * param base LPSPI peripheral base address.
 * return LPSPI instance.
 */
uint32_t LPSPI_GetInstance(LPSPI_Type *base)
{
    uint8_t instance = 0;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_lpspiBases); instance++)
    {
        if (s_lpspiBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_lpspiBases));

    return instance;
}

/*!
 * brief Set up the dummy data.
 *
 * param base LPSPI peripheral address.
 * param dummyData Data to be transferred when tx buffer is NULL.
 * Note:
 *      This API has no effect when LPSPI in slave interrupt mode, because driver
 *      will set the TXMSK bit to 1 if txData is NULL, no data is loaded from transmit
 *      FIFO and output pin is tristated.
 */
void LPSPI_SetDummyData(LPSPI_Type *base, uint8_t dummyData)
{
    uint32_t instance          = LPSPI_GetInstance(base);
    g_lpspiDummyData[instance] = dummyData;
}

/*!
 * brief Initializes the LPSPI master.
 *
 * param base LPSPI peripheral address.
 * param masterConfig Pointer to structure lpspi_master_config_t.
 * param srcClock_Hz Module source input clock in Hertz
 */
void LPSPI_MasterInit(LPSPI_Type *base, const lpspi_master_config_t *masterConfig, uint32_t srcClock_Hz)
{
    assert(masterConfig != NULL);
    
    uint32_t tcrPrescaleValue = 0;
    uint32_t instance = LPSPI_GetInstance(base);    

    if(LP_FLEXCOMM_GetBaseAddress(instance) != 0U)
    {
#if !(defined(LPFLEXCOMM_INIT_NOT_USED_IN_DRIVER) && LPFLEXCOMM_INIT_NOT_USED_IN_DRIVER)
    /* initialize flexcomm to LPSPI mode */
        status_t status = LP_FLEXCOMM_Init(LPSPI_GetInstance(base), LP_FLEXCOMM_PERIPH_LPSPI);
        if (kStatus_Success != status)
        {
            assert(false);
        }
#endif /* LPFLEXCOMM_INIT_NOT_USED_IN_DRIVER */
    }
    else
    {
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)

        /* Enable LPSPI clock */
        (void)CLOCK_EnableClock(s_lpspiClocks[instance]);

#if defined(LPSPI_PERIPH_CLOCKS)
        (void)CLOCK_EnableClock(s_LpspiPeriphClocks[instance]);
#endif

#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
    }

    /* Disable LPSPI first */
    LPSPI_Enable(base, false);

    /* Set LPSPI to master */
    LPSPI_SetMasterSlaveMode(base, kLPSPI_Master);

    /* Set specific PCS to active high or low */
    LPSPI_SetOnePcsPolarity(base, masterConfig->whichPcs, masterConfig->pcsActiveHighOrLow);

    /* Set Configuration Register 1 related setting.*/
    base->CFGR1 = (base->CFGR1 & ~(LPSPI_CFGR1_OUTCFG_MASK | LPSPI_CFGR1_PINCFG_MASK | LPSPI_CFGR1_NOSTALL_MASK |
                                   LPSPI_CFGR1_SAMPLE_MASK | LPSPI_CFGR1_PCSCFG_MASK )) |
                  LPSPI_CFGR1_OUTCFG(masterConfig->dataOutConfig) | LPSPI_CFGR1_PINCFG(masterConfig->pinCfg) |
                  LPSPI_CFGR1_NOSTALL(0) | LPSPI_CFGR1_SAMPLE((uint32_t)masterConfig->enableInputDelay )|
                  LPSPI_CFGR1_PCSCFG(masterConfig->pcsFunc);

    /* Set baudrate and delay times*/
    (void)LPSPI_MasterSetBaudRate(base, masterConfig->baudRate, srcClock_Hz, &tcrPrescaleValue);

    /* Set default watermarks */
    LPSPI_SetFifoWatermarks(base, (uint32_t)kLpspiDefaultTxWatermark, (uint32_t)kLpspiDefaultRxWatermark);

    /* Set Transmit Command Register*/
    base->TCR = LPSPI_TCR_CPOL(masterConfig->cpol) | LPSPI_TCR_CPHA(masterConfig->cpha) |
                LPSPI_TCR_LSBF(masterConfig->direction) | LPSPI_TCR_FRAMESZ(masterConfig->bitsPerFrame - 1U) |
                LPSPI_TCR_PRESCALE(tcrPrescaleValue) | LPSPI_TCR_PCS(masterConfig->whichPcs);

    LPSPI_Enable(base, true);

    (void)LPSPI_MasterSetDelayTimes(base, masterConfig->pcsToSckDelayInNanoSec, kLPSPI_PcsToSck, srcClock_Hz);
    (void)LPSPI_MasterSetDelayTimes(base, masterConfig->lastSckToPcsDelayInNanoSec, kLPSPI_LastSckToPcs, srcClock_Hz);
    (void)LPSPI_MasterSetDelayTimes(base, masterConfig->betweenTransferDelayInNanoSec, kLPSPI_BetweenTransfer,
                                    srcClock_Hz);

    LPSPI_SetDummyData(base, LPSPI_DUMMY_DATA);
}

/*!
 * brief Sets the lpspi_master_config_t structure to default values.
 *
 * This API initializes the configuration structure  for LPSPI_MasterInit().
 * The initialized structure can remain unchanged in LPSPI_MasterInit(), or can be modified
 * before calling the LPSPI_MasterInit().
 * Example:
 * code
 *  lpspi_master_config_t  masterConfig;
 *  LPSPI_MasterGetDefaultConfig(&masterConfig);
 * endcode
 * param masterConfig pointer to lpspi_master_config_t structure
 */
void LPSPI_MasterGetDefaultConfig(lpspi_master_config_t *masterConfig)
{
    assert(masterConfig != NULL);

    /* Initializes the configure structure to zero. */
    (void)memset(masterConfig, 0, sizeof(*masterConfig));

    masterConfig->baudRate     = 500000;
    masterConfig->bitsPerFrame = 8;
    masterConfig->cpol         = kLPSPI_ClockPolarityActiveHigh;
    masterConfig->cpha         = kLPSPI_ClockPhaseFirstEdge;
    masterConfig->direction    = kLPSPI_MsbFirst;

    masterConfig->pcsToSckDelayInNanoSec        = (1000000000U / masterConfig->baudRate) / 2U;
    masterConfig->lastSckToPcsDelayInNanoSec    = (1000000000U / masterConfig->baudRate) / 2U;
    masterConfig->betweenTransferDelayInNanoSec = (1000000000U / masterConfig->baudRate) / 2U;

    masterConfig->whichPcs           = kLPSPI_Pcs0;
    masterConfig->pcsActiveHighOrLow = kLPSPI_PcsActiveLow;
    masterConfig->pcsFunc            = kLPSPI_PcsAsCs; 

    masterConfig->pinCfg        = kLPSPI_SdiInSdoOut;
    masterConfig->dataOutConfig = kLpspiDataOutRetained;

    masterConfig->enableInputDelay = false;
}

/*!
 * brief LPSPI slave configuration.
 *
 * param base LPSPI peripheral address.
 * param slaveConfig Pointer to a structure lpspi_slave_config_t.
 */
void LPSPI_SlaveInit(LPSPI_Type *base, const lpspi_slave_config_t *slaveConfig)
{
    assert(slaveConfig != NULL);
    
    uint32_t instance = LPSPI_GetInstance(base);

    if(LP_FLEXCOMM_GetBaseAddress(instance) != 0U)
    {
#if !(defined(LPFLEXCOMM_INIT_NOT_USED_IN_DRIVER) && LPFLEXCOMM_INIT_NOT_USED_IN_DRIVER)
    /* initialize flexcomm to LPSPI mode */
        status_t status = LP_FLEXCOMM_Init(LPSPI_GetInstance(base), LP_FLEXCOMM_PERIPH_LPSPI);
        if (kStatus_Success != status)
        {
            assert(false);
        }
#endif /* LPFLEXCOMM_INIT_NOT_USED_IN_DRIVER */
    }
    else
    {
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)

        /* Enable LPSPI clock */
        (void)CLOCK_EnableClock(s_lpspiClocks[instance]);

#if defined(LPSPI_PERIPH_CLOCKS)
        (void)CLOCK_EnableClock(s_LpspiPeriphClocks[instance]);
#endif

#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
    }
    
    LPSPI_SetMasterSlaveMode(base, kLPSPI_Slave);

    LPSPI_SetOnePcsPolarity(base, slaveConfig->whichPcs, slaveConfig->pcsActiveHighOrLow);

    base->CFGR1 = (base->CFGR1 & ~(LPSPI_CFGR1_OUTCFG_MASK | LPSPI_CFGR1_PINCFG_MASK)) |
                  LPSPI_CFGR1_OUTCFG(slaveConfig->dataOutConfig) | LPSPI_CFGR1_PINCFG(slaveConfig->pinCfg);

    LPSPI_SetFifoWatermarks(base, (uint32_t)kLpspiDefaultTxWatermark, (uint32_t)kLpspiDefaultRxWatermark);

    base->TCR = LPSPI_TCR_CPOL(slaveConfig->cpol) | LPSPI_TCR_CPHA(slaveConfig->cpha) |
                LPSPI_TCR_LSBF(slaveConfig->direction) | LPSPI_TCR_FRAMESZ(slaveConfig->bitsPerFrame - 1U);

    /* This operation will set the dummy data for edma transfer, no effect in interrupt way. */
    LPSPI_SetDummyData(base, LPSPI_DUMMY_DATA);

    LPSPI_Enable(base, true);
}

/*!
 * brief Sets the lpspi_slave_config_t structure to default values.
 *
 * This API initializes the configuration structure for LPSPI_SlaveInit().
 * The initialized structure can remain unchanged in LPSPI_SlaveInit() or can be modified
 * before calling the LPSPI_SlaveInit().
 * Example:
 * code
 *  lpspi_slave_config_t  slaveConfig;
 *  LPSPI_SlaveGetDefaultConfig(&slaveConfig);
 * endcode
 * param slaveConfig pointer to lpspi_slave_config_t structure.
 */
void LPSPI_SlaveGetDefaultConfig(lpspi_slave_config_t *slaveConfig)
{
    assert(slaveConfig != NULL);

    /* Initializes the configure structure to zero. */
    (void)memset(slaveConfig, 0, sizeof(*slaveConfig));

    slaveConfig->bitsPerFrame = 8;                              /*!< Bits per frame, minimum 8, maximum 4096.*/
    slaveConfig->cpol         = kLPSPI_ClockPolarityActiveHigh; /*!< Clock polarity. */
    slaveConfig->cpha         = kLPSPI_ClockPhaseFirstEdge;     /*!< Clock phase. */
    slaveConfig->direction    = kLPSPI_MsbFirst;                /*!< MSB or LSB data shift direction. */

    slaveConfig->whichPcs           = kLPSPI_Pcs0;         /*!< Desired Peripheral Chip Select (pcs) */
    slaveConfig->pcsActiveHighOrLow = kLPSPI_PcsActiveLow; /*!< Desired PCS active high or low */

    slaveConfig->pinCfg        = kLPSPI_SdiInSdoOut;
    slaveConfig->dataOutConfig = kLpspiDataOutRetained;
}

/*!
 * brief Restores the LPSPI peripheral to reset state. Note that this function
 * sets all registers to reset state. As a result, the LPSPI module can't work after calling
 * this API.
 * param base LPSPI peripheral address.
 */
void LPSPI_Reset(LPSPI_Type *base)
{
    /* Reset all internal logic and registers, except the Control Register. Remains set until cleared by software.*/
    base->CR |= LPSPI_CR_RST_MASK;

    /* Software reset doesn't reset the CR, so manual reset the FIFOs */
    base->CR |= LPSPI_CR_RRF_MASK | LPSPI_CR_RTF_MASK;

    /* Master logic is not reset and module is disabled.*/
    base->CR = 0x00U;
}

/*!
 * brief De-initializes the LPSPI peripheral. Call this API to disable the LPSPI clock.
 * param base LPSPI peripheral address.
 */
void LPSPI_Deinit(LPSPI_Type *base)
{
    uint32_t instance = LPSPI_GetInstance(base);

    /* Reset to default value */
    LPSPI_Reset(base);
    if(LP_FLEXCOMM_GetBaseAddress(instance) != 0U)
    {
#if !(defined(LPFLEXCOMM_INIT_NOT_USED_IN_DRIVER) && LPFLEXCOMM_INIT_NOT_USED_IN_DRIVER)
        LP_FLEXCOMM_Deinit(instance);
#endif
    }
    else
    {        
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
        /* Disable LPSPI clock */
        (void)CLOCK_DisableClock(s_lpspiClocks[instance]);

#if defined(LPSPI_PERIPH_CLOCKS)
        (void)CLOCK_DisableClock(s_LpspiPeriphClocks[instance]);
#endif

#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
    }
}

static void LPSPI_SetOnePcsPolarity(LPSPI_Type *base,
                                    lpspi_which_pcs_t pcs,
                                    lpspi_pcs_polarity_config_t activeLowOrHigh)
{
    uint32_t cfgr1Value = 0;
    /* Clear the PCS polarity bit */
    cfgr1Value = base->CFGR1 & ~(1UL << (LPSPI_CFGR1_PCSPOL_SHIFT + (uint32_t)pcs));

    /* Configure the PCS polarity bit according to the activeLowOrHigh setting */
    base->CFGR1 = cfgr1Value | ((uint32_t)activeLowOrHigh << (LPSPI_CFGR1_PCSPOL_SHIFT + (uint32_t)pcs));
}

/*!
 * brief Sets the LPSPI baud rate in bits per second.
 *
 * This function takes in the desired bitsPerSec (baud rate) and calculates the nearest
 * possible baud rate without exceeding the desired baud rate and returns the
 * calculated baud rate in bits-per-second. It requires the caller to provide
 * the frequency of the module source clock (in Hertz). Note that the baud rate
 * does not go into effect until the Transmit Control Register (TCR) is programmed
 * with the prescale value. Hence, this function returns the prescale tcrPrescaleValue
 * parameter for later programming in the TCR.  The higher level
 * peripheral driver should alert the user of an out of range baud rate input.
 *
 * Note that the LPSPI module must first be disabled before configuring this.
 * Note that the LPSPI module must be configured for master mode before configuring this.
 *
 * param base LPSPI peripheral address.
 * param baudRate_Bps The desired baud rate in bits per second.
 * param srcClock_Hz Module source input clock in Hertz.
 * param tcrPrescaleValue The TCR prescale value needed to program the TCR.
 * return  The actual calculated baud rate. This function may also return a "0" if the
 *          LPSPI is not configured for master mode or if the LPSPI module is not disabled.
 */

uint32_t LPSPI_MasterSetBaudRate(LPSPI_Type *base,
                                 uint32_t baudRate_Bps,
                                 uint32_t srcClock_Hz,
                                 uint32_t *tcrPrescaleValue)
{
    assert(tcrPrescaleValue != NULL);

    /* For master mode configuration only, if slave mode detected, return 0.
     * Also, the LPSPI module needs to be disabled first, if enabled, return 0
     */
    if ((!LPSPI_IsMaster(base)) || ((base->CR & LPSPI_CR_MEN_MASK) != 0U))
    {
        return 0U;
    }

    uint32_t prescaler, bestPrescaler;
    uint32_t scaler, bestScaler;
    uint32_t realBaudrate, bestBaudrate;
    uint32_t diff, min_diff;
    uint32_t desiredBaudrate = baudRate_Bps;

    /* find combination of prescaler and scaler resulting in baudrate closest to the
     * requested value
     */
    min_diff = 0xFFFFFFFFU;

    /* Set to maximum divisor value bit settings so that if baud rate passed in is less
     * than the minimum possible baud rate, then the SPI will be configured to the lowest
     * possible baud rate
     */
    bestPrescaler = 7;
    bestScaler    = 255;

    bestBaudrate = 0; /* required to avoid compilation warning */

    /* In all for loops, if min_diff = 0, the exit for loop*/
    for (prescaler = 0U; prescaler < 8U; prescaler++)
    {
        if (min_diff == 0U)
        {
            break;
        }
        for (scaler = 0U; scaler < 256U; scaler++)
        {
            if (min_diff == 0U)
            {
                break;
            }
            realBaudrate = (srcClock_Hz / (s_baudratePrescaler[prescaler] * (scaler + 2U)));

            /* calculate the baud rate difference based on the conditional statement
             * that states that the calculated baud rate must not exceed the desired baud rate
             */
            if (desiredBaudrate >= realBaudrate)
            {
                diff = desiredBaudrate - realBaudrate;
                if (min_diff > diff)
                {
                    /* a better match found */
                    min_diff      = diff;
                    bestPrescaler = prescaler;
                    bestScaler    = scaler;
                    bestBaudrate  = realBaudrate;
                }
            }
        }
    }

    /* Write the best baud rate scalar to the CCR.
     * Note, no need to check for error since we've already checked to make sure the module is
     * disabled and in master mode. Also, there is a limit on the maximum divider so we will not
     * exceed this.
     */
#if defined(FSL_FEATURE_LPSPI_HAS_CCR1) && FSL_FEATURE_LPSPI_HAS_CCR1
    /* When CCR1 is present, the CCR[DBT] and CCR[SCKDIV] is write only, all read will return 0
       The real DBT and SCKDIV can be obtained in CCR1, CCR[DBT]=CCR1[SCKSCK] and CCR[SCKDIV]=CCR1[SCKHLD]+CCR1[SCKSET]
       So when changing either CCR[DBT] or CCR[SCKDIV] make sure the other value is not overwritten by 0 */
    base->CCR = base->CCR | LPSPI_CCR_DBT((base->CCR1 & LPSPI_CCR1_SCKSCK_MASK) >> LPSPI_CCR1_SCKSCK_SHIFT) |
                LPSPI_CCR_SCKDIV(bestScaler);
#else
    base->CCR = (base->CCR & ~LPSPI_CCR_SCKDIV_MASK) | LPSPI_CCR_SCKDIV(bestScaler);
#endif /* FSL_FEATURE_LPSPI_HAS_CCR1 */

    /* return the best prescaler value for user to use later */
    *tcrPrescaleValue = bestPrescaler;

    /* return the actual calculated baud rate */
    return bestBaudrate;
}

/*!
 * brief Manually configures a specific LPSPI delay parameter (module must be disabled to
 *        change the delay values).
 *
 * This function configures the following:
 * SCK to PCS delay, or
 * PCS to SCK delay, or
 * The configurations must occur between the transfer delay.
 *
 * The delay names are available in type lpspi_delay_type_t.
 *
 * The user passes the desired delay along with the delay value.
 * This allows the user to directly set the delay values if they have
 * pre-calculated them or if they simply wish to manually increment the value.
 *
 * Note that the LPSPI module must first be disabled before configuring this.
 * Note that the LPSPI module must be configured for master mode before configuring this.
 *
 * param base LPSPI peripheral address.
 * param scaler The 8-bit delay value 0x00 to 0xFF (255).
 * param whichDelay The desired delay to configure, must be of type lpspi_delay_type_t.
 */
void LPSPI_MasterSetDelayScaler(LPSPI_Type *base, uint32_t scaler, lpspi_delay_type_t whichDelay)
{
    /*These settings are only relevant in master mode */
#if defined(FSL_FEATURE_LPSPI_HAS_CCR1) && FSL_FEATURE_LPSPI_HAS_CCR1
    /* When CCR1 is present, the CCR[DBT] and CCR[SCKDIV] is write only, all read will return 0
       The real DBT and SCKDIV can be obtained in CCR1, CCR[DBT]=CCR1[SCKSCK] and CCR[SCKDIV]=CCR1[SCKHLD]+CCR1[SCKSET]
       So when changing either CCR[DBT] or CCR[SCKDIV] make sure the other value is not overwritten by 0 */
    uint32_t dbt    = (base->CCR1 & LPSPI_CCR1_SCKSCK_MASK) >> LPSPI_CCR1_SCKSCK_SHIFT;
    uint32_t sckdiv = (base->CCR1 & LPSPI_CCR1_SCKHLD_MASK) >> LPSPI_CCR1_SCKHLD_SHIFT;
    sckdiv += (base->CCR1 & LPSPI_CCR1_SCKSET_MASK) >> LPSPI_CCR1_SCKSET_SHIFT;
    switch (whichDelay)
    {
        case kLPSPI_PcsToSck:
            base->CCR = (base->CCR & (~LPSPI_CCR_PCSSCK_MASK)) | LPSPI_CCR_PCSSCK(scaler) | LPSPI_CCR_DBT(dbt) |
                        LPSPI_CCR_SCKDIV(sckdiv);

            break;
        case kLPSPI_LastSckToPcs:
            base->CCR = (base->CCR & (~LPSPI_CCR_SCKPCS_MASK)) | LPSPI_CCR_SCKPCS(scaler) | LPSPI_CCR_DBT(dbt) |
                        LPSPI_CCR_SCKDIV(sckdiv);

            break;
        case kLPSPI_BetweenTransfer:
            base->CCR = base->CCR | LPSPI_CCR_DBT(scaler) | LPSPI_CCR_SCKDIV(sckdiv);
#else
    switch (whichDelay)
    {
        case kLPSPI_PcsToSck:
            base->CCR = (base->CCR & (~LPSPI_CCR_PCSSCK_MASK)) | LPSPI_CCR_PCSSCK(scaler);

            break;
        case kLPSPI_LastSckToPcs:
            base->CCR = (base->CCR & (~LPSPI_CCR_SCKPCS_MASK)) | LPSPI_CCR_SCKPCS(scaler);

            break;
        case kLPSPI_BetweenTransfer:
            base->CCR = (base->CCR & (~LPSPI_CCR_DBT_MASK)) | LPSPI_CCR_DBT(scaler);
#endif /* FSL_FEATURE_LPSPI_HAS_CCR1 */
            break;
        default:
            assert(false);
            break;
    }
}

/*!
 * brief Calculates the delay based on the desired delay input in nanoseconds (module must be
 *        disabled to change the delay values).
 *
 * This function calculates the values for the following:
 * SCK to PCS delay, or
 * PCS to SCK delay, or
 * The configurations must occur between the transfer delay.
 *
 * The delay names are available in type lpspi_delay_type_t.
 *
 * The user passes the desired delay and the desired delay value in
 * nano-seconds.  The function calculates the value needed for the desired delay parameter
 * and returns the actual calculated delay because an exact delay match may not be possible. In this
 * case, the closest match is calculated without going below the desired delay value input.
 * It is possible to input a very large delay value that exceeds the capability of the part, in
 * which case the maximum supported delay is returned. It is up to the higher level
 * peripheral driver to alert the user of an out of range delay input.
 *
 * Note that the LPSPI module must be configured for master mode before configuring this. And note that
 * the delayTime = LPSPI_clockSource / (PRESCALE * Delay_scaler).
 *
 * param base LPSPI peripheral address.
 * param delayTimeInNanoSec The desired delay value in nano-seconds.
 * param whichDelay The desired delay to configuration, which must be of type lpspi_delay_type_t.
 * param srcClock_Hz  Module source input clock in Hertz.
 * return actual Calculated delay value in nano-seconds.
 */
uint32_t LPSPI_MasterSetDelayTimes(LPSPI_Type *base,
                                   uint32_t delayTimeInNanoSec,
                                   lpspi_delay_type_t whichDelay,
                                   uint32_t srcClock_Hz)
{
    uint64_t realDelay, bestDelay;
    uint32_t scaler, bestScaler;
    uint32_t diff, min_diff;
    uint64_t initialDelayNanoSec;
    uint32_t clockDividedPrescaler;

    /* For delay between transfer, an additional scaler value is needed */
    uint32_t additionalScaler = 0;

    /*As the RM note, the LPSPI baud rate clock is itself divided by the PRESCALE setting, which can vary between
     * transfers.*/
    clockDividedPrescaler =
        srcClock_Hz / s_baudratePrescaler[(base->TCR & LPSPI_TCR_PRESCALE_MASK) >> LPSPI_TCR_PRESCALE_SHIFT];

    /* Find combination of prescaler and scaler resulting in the delay closest to the requested value.*/
    min_diff = 0xFFFFFFFFU;

    /* Initialize scaler to max value to generate the max delay */
    bestScaler = 0xFFU;

    /* Calculate the initial (min) delay and maximum possible delay based on the specific delay as
     * the delay divisors are slightly different based on which delay we are configuring.
     */
    if (whichDelay == kLPSPI_BetweenTransfer)
    {
        /* First calculate the initial, default delay, note min delay is 2 clock cycles. Due to large size of
         calculated values (uint64_t), we need to break up the calculation into several steps to ensure
         accurate calculated results
         */
        initialDelayNanoSec = 1000000000U;
        initialDelayNanoSec *= 2U;
        initialDelayNanoSec /= clockDividedPrescaler;

        /* Calculate the maximum delay */
        bestDelay = 1000000000U;
        bestDelay *= 257U; /* based on DBT+2, or 255 + 2 */
        bestDelay /= clockDividedPrescaler;

        additionalScaler = 1U;
    }
    else
    {
        /* First calculate the initial, default delay, min delay is 1 clock cycle. Due to large size of calculated
        values (uint64_t), we need to break up the calculation into several steps to ensure accurate calculated
        results.
        */
        initialDelayNanoSec = 1000000000U;
        initialDelayNanoSec /= clockDividedPrescaler;

        /* Calculate the maximum delay */
        bestDelay = 1000000000U;
        bestDelay *= 256U; /* based on SCKPCS+1 or PCSSCK+1, or 255 + 1 */
        bestDelay /= clockDividedPrescaler;

        additionalScaler = 0U;
    }

    /* If the initial, default delay is already greater than the desired delay, then
     * set the delay to their initial value (0) and return the delay. In other words,
     * there is no way to decrease the delay value further.
     */
    if (initialDelayNanoSec >= delayTimeInNanoSec)
    {
        LPSPI_MasterSetDelayScaler(base, 0, whichDelay);
        return (uint32_t)initialDelayNanoSec;
    }

    /* If min_diff = 0, the exit for loop */
    for (scaler = 0U; scaler < 256U; scaler++)
    {
        if (min_diff == 0U)
        {
            break;
        }
        /* Calculate the real delay value as we cycle through the scaler values.
        Due to large size of calculated values (uint64_t), we need to break up the
        calculation into several steps to ensure accurate calculated results
        */
        realDelay = 1000000000U;
        realDelay *= ((uint64_t)scaler + 1UL + (uint64_t)additionalScaler);
        realDelay /= clockDividedPrescaler;

        /* calculate the delay difference based on the conditional statement
         * that states that the calculated delay must not be less then the desired delay
         */
        if (realDelay >= delayTimeInNanoSec)
        {
            diff = (uint32_t)(realDelay - (uint64_t)delayTimeInNanoSec);
            if (min_diff > diff)
            {
                /* a better match found */
                min_diff   = diff;
                bestScaler = scaler;
                bestDelay  = realDelay;
            }
        }
    }

    /* write the best scaler value for the delay */
    LPSPI_MasterSetDelayScaler(base, bestScaler, whichDelay);

    /* return the actual calculated delay value (in ns) */
    return (uint32_t)bestDelay;
}

/*Transactional APIs -- Master*/

/*!
 * brief Initializes the LPSPI master handle.
 *
 * This function initializes the LPSPI handle, which can be used for other LPSPI transactional APIs.  Usually, for a
 * specified LPSPI instance, call this API once to get the initialized handle.

 * param base LPSPI peripheral address.
 * param handle LPSPI handle pointer to lpspi_master_handle_t.
 * param callback DSPI callback.
 * param userData callback function parameter.
 */
void LPSPI_MasterTransferCreateHandle(LPSPI_Type *base,
                                      lpspi_master_handle_t *handle,
                                      lpspi_master_transfer_callback_t callback,
                                      void *userData)
{
    assert(handle != NULL);
    
    uint32_t instance = LPSPI_GetInstance(base);

    /* Zero the handle. */
    (void)memset(handle, 0, sizeof(*handle));

    handle->callback = callback;
    handle->userData = userData;

    if(LP_FLEXCOMM_GetBaseAddress(instance) != 0U)
    {
        lpspi_to_lpflexcomm_t handler;
        handler.lpspi_master_handler = LPSPI_MasterTransferHandleIRQ;

        /* Save the handle in global variables to support the double weak mechanism. */
        LP_FLEXCOMM_SetIRQHandler(instance, handler.lpflexcomm_handler, handle, LP_FLEXCOMM_PERIPH_LPSPI);
    }
    else
    {        
        s_lpspiHandle[instance] = handle;

        /* Set irq handler. */
        s_lpspiMasterIsr = LPSPI_MasterTransferHandleIRQ;
    }
}

/*!
 * brief Check the argument for transfer .
 *
 * param base LPSPI peripheral address.
 * param transfer the transfer struct to be used.
 * param isEdma True to check for EDMA transfer, false to check interrupt non-blocking transfer
 * return Return true for right and false for wrong.
 */
bool LPSPI_CheckTransferArgument(LPSPI_Type *base, lpspi_transfer_t *transfer, bool isEdma)
{
    assert(transfer != NULL);
    uint32_t bitsPerFrame  = ((base->TCR & LPSPI_TCR_FRAMESZ_MASK) >> LPSPI_TCR_FRAMESZ_SHIFT) + 1U;
    uint32_t bytesPerFrame = (bitsPerFrame + 7U) / 8U;
    uint32_t temp          = (base->CFGR1 & LPSPI_CFGR1_PINCFG_MASK);
    /* If the transfer count is zero, then return immediately.*/
    if (transfer->dataSize == 0U)
    {
        return false;
    }

    /* If both send buffer and receive buffer is null */
    if ((NULL == (transfer->txData)) && (NULL == (transfer->rxData)))
    {
        return false;
    }

    /*The transfer data size should be integer multiples of bytesPerFrame if bytesPerFrame is less than or equal to 4 .
     *For bytesPerFrame greater than 4 situation:
     *the transfer data size should be equal to bytesPerFrame if the bytesPerFrame is not integer multiples of 4 ,
     *otherwise , the transfer data size can be integer multiples of bytesPerFrame.
     */
    if (bytesPerFrame <= 4U)
    {
        if ((transfer->dataSize % bytesPerFrame) != 0U)
        {
            return false;
        }
    }
    else
    {
        if ((bytesPerFrame % 4U) != 0U)
        {
            if (transfer->dataSize != bytesPerFrame)
            {
                return false;
            }
        }
        else
        {
            if ((transfer->dataSize % bytesPerFrame) != 0U)
            {
                return false;
            }
        }
    }

    /* Check if using 3-wire mode and the txData is NULL, set the output pin to tristated. */
    if ((temp == LPSPI_CFGR1_PINCFG(kLPSPI_SdiInSdiOut)) || (temp == LPSPI_CFGR1_PINCFG(kLPSPI_SdoInSdoOut)))
    {
        /* The 3-wire mode can't send and receive data at the same time. */
        if ((transfer->txData != NULL) && (transfer->rxData != NULL))
        {
            return false;
        }
        if (NULL == transfer->txData)
        {
            base->CFGR1 |= LPSPI_CFGR1_OUTCFG_MASK;
        }
    }

    if (isEdma && ((bytesPerFrame % 4U) == 3U))
    {
        return false;
    }

    return true;
}

/*!
 * brief LPSPI master transfer data using a polling method.
 *
 * This function transfers data using a  polling method. This is a blocking function, which does not return until all
 * transfers have been completed.
 *
 * Note:
 * The transfer data size should be integer multiples of bytesPerFrame if bytesPerFrame is less than or equal to 4.
 * For bytesPerFrame greater than 4:
 * The transfer data size should be equal to bytesPerFrame if the bytesPerFrame is not integer multiples of 4.
 * Otherwise, the transfer data size can be an integer multiple of bytesPerFrame.
 *
 * param base LPSPI peripheral address.
 * param transfer pointer to lpspi_transfer_t structure.
 * return status of status_t.
 */
status_t LPSPI_MasterTransferBlocking(LPSPI_Type *base, lpspi_transfer_t *transfer)
{
    assert(transfer != NULL);

    /* Check that LPSPI is not busy.*/
    if ((LPSPI_GetStatusFlags(base) & (uint32_t)kLPSPI_ModuleBusyFlag) != 0U)
    {
        return kStatus_LPSPI_Busy;
    }
    LPSPI_Enable(base, false);
    /* Check arguements */
    if (!LPSPI_CheckTransferArgument(base, transfer, false))
    {
        return kStatus_InvalidArgument;
    }

    LPSPI_FlushFifo(base, true, true);
    LPSPI_ClearStatusFlags(base, (uint32_t)kLPSPI_AllStatusFlag);

    /* Variables */
    bool isTxMask   = false;
    bool isByteSwap = ((transfer->configFlags & (uint32_t)kLPSPI_MasterByteSwap) != 0U);
    uint8_t bytesEachWrite;
    uint8_t bytesEachRead;
    const uint8_t *txData         = transfer->txData;
    uint8_t *rxData               = transfer->rxData;
    uint8_t dummyData             = g_lpspiDummyData[LPSPI_GetInstance(base)];
    uint32_t readData             = 0U;
    uint32_t txRemainingByteCount = transfer->dataSize;
    uint32_t rxRemainingByteCount = transfer->dataSize;
    uint32_t wordToSend =
        ((uint32_t)dummyData) | ((uint32_t)dummyData << 8) | ((uint32_t)dummyData << 16) | ((uint32_t)dummyData << 24);
    /*The TX and RX FIFO sizes are always the same*/
    uint32_t fifoSize      = LPSPI_GetRxFifoSize(base);
    uint32_t bytesPerFrame = ((base->TCR & LPSPI_TCR_FRAMESZ_MASK) >> LPSPI_TCR_FRAMESZ_SHIFT) / 8U + 1U;
    /* No need to configure PCS continous if the transfer byte count is smaller than frame size */
    bool isPcsContinuous    = (((transfer->configFlags & (uint32_t)kLPSPI_MasterPcsContinuous) != 0U) &&
                            (bytesPerFrame < transfer->dataSize));
    uint32_t rxFifoMaxBytes = MIN(bytesPerFrame, 4U) * fifoSize;
    uint32_t whichPcs       = (transfer->configFlags & LPSPI_MASTER_PCS_MASK) >> LPSPI_MASTER_PCS_SHIFT;
    uint32_t width          = (transfer->configFlags & LPSPI_MASTER_WIDTH_MASK) >> LPSPI_MASTER_WIDTH_SHIFT;
    uint32_t temp           = (base->CFGR1 & LPSPI_CFGR1_PINCFG_MASK);

#if SPI_RETRY_TIMES
    uint32_t waitTimes;
#endif

    /* Mask tx data in half duplex mode */
    if (((temp == LPSPI_CFGR1_PINCFG(kLPSPI_SdiInSdiOut)) || (temp == LPSPI_CFGR1_PINCFG(kLPSPI_SdoInSdoOut))) &&
        (txData == NULL))
    {
        isTxMask = true;
    }

    base->CFGR1 &= (~LPSPI_CFGR1_NOSTALL_MASK);
    LPSPI_Enable(base, true);

    /* Configure transfer control register. */
    base->TCR = (base->TCR & ~(LPSPI_TCR_CONT_MASK | LPSPI_TCR_CONTC_MASK | LPSPI_TCR_RXMSK_MASK |
                               LPSPI_TCR_TXMSK_MASK | LPSPI_TCR_PCS_MASK)) |
                LPSPI_TCR_PCS(whichPcs) | LPSPI_TCR_WIDTH(width);

    /*TCR is also shared the FIFO, so wait for TCR written.*/
    if (!LPSPI_TxFifoReady(base))
    {
        return kStatus_LPSPI_Timeout;
    }

    /* PCS should be configured separately from the other bits, otherwise it will not take effect. */
    base->TCR |= LPSPI_TCR_CONT(isPcsContinuous) | LPSPI_TCR_CONTC(isPcsContinuous) | LPSPI_TCR_RXMSK(NULL == rxData);

    /*TCR is also shared the FIFO, so wait for TCR written.*/
    if (!LPSPI_TxFifoReady(base))
    {
        return kStatus_LPSPI_Timeout;
    }

    if (bytesPerFrame <= 4U)
    {
        bytesEachWrite = (uint8_t)bytesPerFrame;
        bytesEachRead  = (uint8_t)bytesPerFrame;
    }
    else
    {
        bytesEachWrite = 4U;
        bytesEachRead  = 4U;
    }

    /*Write the TX data until txRemainingByteCount is equal to 0 */
    while (txRemainingByteCount > 0U)
    {
        if (txRemainingByteCount < bytesEachWrite)
        {
            bytesEachWrite = (uint8_t)txRemainingByteCount;
        }

        /*Wait until TX FIFO is not full*/
#if SPI_RETRY_TIMES
        waitTimes = SPI_RETRY_TIMES;
        while ((LPSPI_GetTxFifoCount(base) == fifoSize) && (--waitTimes != 0U))
#else
        while (LPSPI_GetTxFifoCount(base) == fifoSize)
#endif
        {
        }
#if SPI_RETRY_TIMES
        if (waitTimes == 0U)
        {
            return kStatus_LPSPI_Timeout;
        }
#endif

        /* To prevent rxfifo overflow, ensure transmitting and receiving are executed in parallel */
        if (((NULL == rxData) || (rxRemainingByteCount - txRemainingByteCount) < rxFifoMaxBytes))
        {
            if (isTxMask)
            {
                /* When TCR[TXMSK]=1, transfer is initiate by writting a new command word to TCR. TCR[TXMSK] is cleared
                   by hardware every time when TCR[FRAMESZ] bit of data is transfered.
                   In this case TCR[TXMSK] should be set to initiate each transfer. */
                base->TCR |= LPSPI_TCR_TXMSK_MASK;
                if (isPcsContinuous && (txRemainingByteCount == bytesPerFrame))
                {
                    /* For the last piece of frame size of data, if is PCS continous mode(TCR[CONT]), TCR[CONTC] should
                     * be cleared to de-assert the PCS. Be sure to clear the TXMSK as well otherwise another FRAMESZ
                     * of data will be received. */
                    base->TCR &= ~(LPSPI_TCR_CONTC_MASK | LPSPI_TCR_CONT_MASK | LPSPI_TCR_TXMSK_MASK);
                }
                txRemainingByteCount -= bytesPerFrame;
            }
            else
            {
                if (txData != NULL)
                {
                    wordToSend = LPSPI_CombineWriteData(txData, bytesEachWrite, isByteSwap);
                    txData += bytesEachWrite;
                }
                /* Otherwise push data to tx FIFO to initiate transfer */
                LPSPI_WriteData(base, wordToSend);
                txRemainingByteCount -= bytesEachWrite;
            }
        }

        /* Check whether there is RX data in RX FIFO . Read out the RX data so that the RX FIFO would not overrun. */
        if ((rxData != NULL) && (rxRemainingByteCount != 0U))
        {
            /* To ensure parallel execution in 3-wire mode, after writting 1 to TXMSK to generate clock of
               bytesPerFrame's data wait until bytesPerFrame's data is received. */
            while (isTxMask && (LPSPI_GetRxFifoCount(base) == 0U))
            {
            }
#if SPI_RETRY_TIMES
            waitTimes = SPI_RETRY_TIMES;
            while ((LPSPI_GetRxFifoCount(base) != 0U) && (--waitTimes != 0U))
#else
            while (LPSPI_GetRxFifoCount(base) != 0U)
#endif
            {
                readData = LPSPI_ReadData(base);
                if (rxRemainingByteCount < bytesEachRead)
                {
                    bytesEachRead = (uint8_t)rxRemainingByteCount;
                }

                LPSPI_SeparateReadData(rxData, readData, bytesEachRead, isByteSwap);
                rxData += bytesEachRead;

                rxRemainingByteCount -= bytesEachRead;
            }
#if SPI_RETRY_TIMES
            if (waitTimes == 0U)
            {
                return kStatus_LPSPI_Timeout;
            }
#endif
        }
    }

    if (isPcsContinuous && !isTxMask)
    {
        /* In PCS continous mode(TCR[CONT]), after write all the data in TX FIFO, TCR[CONTC] and TCR[CONT] should be
           cleared to de-assert the PCS. Note that TCR register also use the TX FIFO. Also CONTC should be cleared when
           tx is not masked, otherwise written to TCR register with TXMSK bit wet will initiate a new transfer. */
#if SPI_RETRY_TIMES
        waitTimes = SPI_RETRY_TIMES;
        while ((LPSPI_GetTxFifoCount(base) == fifoSize) && (--waitTimes != 0U))
#else
        while (LPSPI_GetTxFifoCount(base) == fifoSize)
#endif
        {
        }
#if SPI_RETRY_TIMES
        if (waitTimes == 0U)
        {
            return kStatus_LPSPI_Timeout;
        }
#endif
        base->TCR = (base->TCR & ~(LPSPI_TCR_CONTC_MASK | LPSPI_TCR_CONT_MASK));
    }

    /*Read out the RX data in FIFO*/
    if (rxData != NULL)
    {
        while (rxRemainingByteCount > 0U)
        {
#if SPI_RETRY_TIMES
            waitTimes = SPI_RETRY_TIMES;
            while ((LPSPI_GetRxFifoCount(base) != 0U) && (--waitTimes != 0U))
#else
            while (LPSPI_GetRxFifoCount(base) != 0U)
#endif
            {
                readData = LPSPI_ReadData(base);

                if (rxRemainingByteCount < bytesEachRead)
                {
                    bytesEachRead = (uint8_t)rxRemainingByteCount;
                }

                LPSPI_SeparateReadData(rxData, readData, bytesEachRead, isByteSwap);
                rxData += bytesEachRead;

                rxRemainingByteCount -= bytesEachRead;
            }
#if SPI_RETRY_TIMES
            if (waitTimes == 0U)
            {
                return kStatus_LPSPI_Timeout;
            }
#endif
        }
    }

    /* Wait for transfer complete flag, that is the PCS is re-asserted. */
#if SPI_RETRY_TIMES
    waitTimes = SPI_RETRY_TIMES;
    while (((LPSPI_GetStatusFlags(base) & (uint32_t)kLPSPI_TransferCompleteFlag) == 0U) && (--waitTimes != 0U))
#else
    while ((LPSPI_GetStatusFlags(base) & (uint32_t)kLPSPI_TransferCompleteFlag) == 0U)
#endif
    {
    }
#if SPI_RETRY_TIMES
    if (waitTimes == 0U)
    {
        return kStatus_LPSPI_Timeout;
    }
#endif

    return kStatus_Success;
}

/*!
 * brief LPSPI master transfer data using an interrupt method.
 *
 * This function transfers data using an interrupt method. This is a non-blocking function, which returns right away.
 * When all data is transferred, the callback function is called.
 *
 * Note:
 * The transfer data size should be integer multiples of bytesPerFrame if bytesPerFrame is less than or equal to 4.
 * For bytesPerFrame greater than 4:
 * The transfer data size should be equal to bytesPerFrame if the bytesPerFrame is not integer multiples of 4.
 * Otherwise, the transfer data size can be an integer multiple of bytesPerFrame.
 *
 * param base LPSPI peripheral address.
 * param handle pointer to lpspi_master_handle_t structure which stores the transfer state.
 * param transfer pointer to lpspi_transfer_t structure.
 * return status of status_t.
 */
status_t LPSPI_MasterTransferNonBlocking(LPSPI_Type *base, lpspi_master_handle_t *handle, lpspi_transfer_t *transfer)
{
    assert(handle != NULL);
    assert(transfer != NULL);

    /* Check that we're not busy.*/
    if (handle->state == (uint8_t)kLPSPI_Busy)
    {
        return kStatus_LPSPI_Busy;
    }

    LPSPI_Enable(base, false);
    /* Check arguements */
    if (!LPSPI_CheckTransferArgument(base, transfer, false))
    {
        return kStatus_InvalidArgument;
    }

    /* Flush FIFO, clear status, disable all the interrupts. */
    LPSPI_FlushFifo(base, true, true);
    LPSPI_ClearStatusFlags(base, (uint32_t)kLPSPI_AllStatusFlag);
    LPSPI_DisableInterrupts(base, (uint32_t)kLPSPI_AllInterruptEnable);

    /* Variables */
    bool isRxMask = false;
    handle->isTxMask = false;
    uint8_t txWatermark;
    uint8_t dummyData = g_lpspiDummyData[LPSPI_GetInstance(base)];
    uint32_t tmpTimes;
    uint32_t whichPcs = (transfer->configFlags & LPSPI_MASTER_PCS_MASK) >> LPSPI_MASTER_PCS_SHIFT;
    uint32_t temp     = (base->CFGR1 & LPSPI_CFGR1_PINCFG_MASK);

    /* Assign the original value for members of transfer handle. */
    handle->state                = (uint8_t)kLPSPI_Busy;
    handle->txData               = transfer->txData;
    handle->rxData               = transfer->rxData;
    handle->txRemainingByteCount = transfer->dataSize;
    handle->rxRemainingByteCount = transfer->dataSize;
    handle->totalByteCount       = transfer->dataSize;
    handle->writeTcrInIsr        = false;
    handle->bytesPerFrame = (uint16_t)((base->TCR & LPSPI_TCR_FRAMESZ_MASK) >> LPSPI_TCR_FRAMESZ_SHIFT) / 8U + 1U;
    /* No need to configure PCS continous if the transfer byte count is smaller than frame size */
    bool isPcsContinuous = (((transfer->configFlags & (uint32_t)kLPSPI_MasterPcsContinuous) != 0U) &&
                            (transfer->dataSize > handle->bytesPerFrame));
    handle->writeRegRemainingTimes =
        (transfer->dataSize / (uint32_t)handle->bytesPerFrame) * (((uint32_t)handle->bytesPerFrame + 3U) / 4U);
    handle->readRegRemainingTimes = handle->writeRegRemainingTimes;
    handle->txBuffIfNull =
        ((uint32_t)dummyData) | ((uint32_t)dummyData << 8) | ((uint32_t)dummyData << 16) | ((uint32_t)dummyData << 24);
    /*The TX and RX FIFO sizes are always the same*/
    handle->fifoSize        = LPSPI_GetRxFifoSize(base);
    handle->isPcsContinuous = isPcsContinuous;
    handle->isByteSwap      = ((transfer->configFlags & (uint32_t)kLPSPI_MasterByteSwap) != 0U);
    /*Calculate the bytes for write/read the TX/RX register each time*/
    if (handle->bytesPerFrame <= 4U)
    {
        handle->bytesEachWrite = (uint8_t)handle->bytesPerFrame;
        handle->bytesEachRead  = (uint8_t)handle->bytesPerFrame;
    }
    else
    {
        handle->bytesEachWrite = 4U;
        handle->bytesEachRead  = 4U;
    }

    /*Set the RX and TX watermarks to reduce the ISR times.*/
    if (handle->fifoSize > 1U)
    {
        txWatermark         = 1U;
        handle->rxWatermark = handle->fifoSize - 2U;
    }
    else
    {
        txWatermark         = 0U;
        handle->rxWatermark = 0U;
    }
    LPSPI_SetFifoWatermarks(base, txWatermark, handle->rxWatermark);

    /* If there is no rxData, mask the receive data so that receive data is not stored in receive FIFO. */
    if (handle->rxData == NULL)
    {
        isRxMask                     = true;
        handle->rxRemainingByteCount = 0;
    }

    /* Mask tx data in half duplex mode since the tx/rx share the same pin, so that the data received from slave is not
     * interfered. */
    if (((temp == LPSPI_CFGR1_PINCFG(kLPSPI_SdiInSdiOut)) || (temp == LPSPI_CFGR1_PINCFG(kLPSPI_SdoInSdoOut))) &&
        (handle->txData == NULL))
    {
        handle->isTxMask = true;
    }

    /*Transfers will stall when transmit FIFO is empty or receive FIFO is full. */
    base->CFGR1 &= (~LPSPI_CFGR1_NOSTALL_MASK);

    /* Enable module for following configuration of TCR to take effect. */
    LPSPI_Enable(base, true);

    /* Configure transfer control register. */
    base->TCR = (base->TCR & ~(LPSPI_TCR_CONT_MASK | LPSPI_TCR_CONTC_MASK | LPSPI_TCR_RXMSK_MASK |
                               LPSPI_TCR_TXMSK_MASK | LPSPI_TCR_PCS_MASK)) |
                LPSPI_TCR_PCS(whichPcs);

    /*TCR is also shared the FIFO , so wait for TCR written.*/
    if (!LPSPI_TxFifoReady(base))
    {
        return kStatus_LPSPI_Timeout;
    }

    /* PCS should be configured separately from the other bits, otherwise it will not take effect. */
    base->TCR |= LPSPI_TCR_CONT(isPcsContinuous) | LPSPI_TCR_CONTC(isPcsContinuous) | LPSPI_TCR_RXMSK(isRxMask);

    /* Enable the NVIC for LPSPI peripheral. Note that below code is useless if the LPSPI interrupt is in INTMUX ,
     * and you should also enable the INTMUX interupt in your application.
     */
    (void)EnableIRQ(s_lpspiIRQ[LPSPI_GetInstance(base)]);

    /*TCR is also shared the FIFO , so wait for TCR written.*/
    if (!LPSPI_TxFifoReady(base))
    {
        return kStatus_LPSPI_Timeout;
    }

    if (handle->isTxMask)
    {
        /* When TCR[TXMSK]=1, transfer is initiate by writting a new command word to TCR. TCR[TXMSK] is cleared by
           hardware every time when TCR[FRAMESZ] bit of data is transfered. In this case TCR[TXMSK] should be set to
           initiate each transfer. */

        base->TCR |= LPSPI_TCR_TXMSK_MASK;
        handle->txRemainingByteCount -= (uint32_t)handle->bytesPerFrame;
    }
    else
    {
        /* Fill up the TX data in FIFO to initiate transfer */
        LPSPI_MasterTransferFillUpTxFifo(base, handle);
    }

    /* Since SPI is a synchronous interface, we only need to enable the RX interrupt if there is RX data.
     * The IRQ handler will get the status of RX and TX interrupt flags.
     */
    if (handle->rxData != NULL)
    {
        if (handle->isTxMask)
        {
            /* if tx data is masked, transfer is initiated by writing 1 to TCR[TXMSK] and TCR[FRMESZ] bits of data is
               read. If rx water mark is set larger than TCR[FRMESZ], rx interrupt will not be generated. Lower the rx
               water mark setting */
            if ((handle->bytesPerFrame / 4U) < (uint16_t)handle->rxWatermark)
            {
                handle->rxWatermark =
                    (uint8_t)(handle->bytesPerFrame / 4U) > 0U ? (uint8_t)(handle->bytesPerFrame / 4U - 1U) : 0U;
                base->FCR = (base->FCR & (~LPSPI_FCR_RXWATER_MASK)) | LPSPI_FCR_RXWATER(handle->rxWatermark);
            }
        }
        else
        {
            /*Set rxWatermark to (readRegRemainingTimes-1) if readRegRemainingTimes less than rxWatermark. Otherwise
             *there is not RX interrupt for the last datas because the RX count is not greater than rxWatermark.
             */
            tmpTimes = handle->readRegRemainingTimes;
            if (tmpTimes <= handle->rxWatermark)
            {
                base->FCR = (base->FCR & (~LPSPI_FCR_RXWATER_MASK)) | LPSPI_FCR_RXWATER(tmpTimes - 1U);
            }
        }

        LPSPI_EnableInterrupts(base, (uint32_t)kLPSPI_RxInterruptEnable);
    }
    else
    {
        LPSPI_EnableInterrupts(base, (uint32_t)kLPSPI_TxInterruptEnable);
    }

    return kStatus_Success;
}

static void LPSPI_MasterTransferFillUpTxFifo(LPSPI_Type *base, lpspi_master_handle_t *handle)
{
    assert(handle != NULL);

    uint32_t wordToSend             = 0;
    uint8_t fifoSize                = handle->fifoSize;
    uint32_t writeRegRemainingTimes = handle->writeRegRemainingTimes;
    uint32_t readRegRemainingTimes  = handle->readRegRemainingTimes;
    size_t txRemainingByteCount     = handle->txRemainingByteCount;
    uint8_t bytesEachWrite          = handle->bytesEachWrite;
    bool isByteSwap                 = handle->isByteSwap;

    /* Make sure the difference in remaining TX and RX byte counts does not exceed FIFO depth
     * and that the number of TX FIFO entries does not exceed the FIFO depth.
     * But no need to make the protection if there is no rxData.
     */
    while ((LPSPI_GetTxFifoCount(base) < fifoSize) &&
           (((readRegRemainingTimes - writeRegRemainingTimes) < (uint32_t)fifoSize) || (handle->rxData == NULL)))
    {
        if (txRemainingByteCount < (size_t)bytesEachWrite)
        {
            handle->bytesEachWrite = (uint8_t)txRemainingByteCount;
            bytesEachWrite         = handle->bytesEachWrite;
        }

        if (handle->txData != NULL)
        {
            wordToSend = LPSPI_CombineWriteData(handle->txData, bytesEachWrite, isByteSwap);
            handle->txData += bytesEachWrite;
        }
        else
        {
            wordToSend = handle->txBuffIfNull;
        }

        /*Write the word to TX register*/
        LPSPI_WriteData(base, wordToSend);

        /*Decrease the write TX register times.*/
        --handle->writeRegRemainingTimes;
        writeRegRemainingTimes = handle->writeRegRemainingTimes;

        /*Decrease the remaining TX byte count.*/
        handle->txRemainingByteCount -= (size_t)bytesEachWrite;
        txRemainingByteCount = handle->txRemainingByteCount;

        if (handle->txRemainingByteCount == 0U)
        {
            /* If PCS is continuous, update TCR to de-assert PCS */
            if (handle->isPcsContinuous)
            {
                /* Only write to the TCR if the FIFO has room */
                if (LPSPI_GetTxFifoCount(base) < fifoSize)
                {
                    base->TCR             = (base->TCR & ~(LPSPI_TCR_CONTC_MASK));
                    handle->writeTcrInIsr = false;
                }
                /* Else, set a global flag to tell the ISR to do write to the TCR */
                else
                {
                    handle->writeTcrInIsr = true;
                }
            }
            break;
        }
    }
}

static void LPSPI_MasterTransferComplete(LPSPI_Type *base, lpspi_master_handle_t *handle)
{
    assert(handle != NULL);

    /* Disable interrupt requests*/
    LPSPI_DisableInterrupts(base, (uint32_t)kLPSPI_AllInterruptEnable);

    handle->state = (uint8_t)kLPSPI_Idle;

    if (handle->callback != NULL)
    {
        handle->callback(base, handle, kStatus_Success, handle->userData);
    }
}

/*!
 * brief Gets the master transfer remaining bytes.
 *
 * This function gets the master transfer remaining bytes.
 *
 * param base LPSPI peripheral address.
 * param handle pointer to lpspi_master_handle_t structure which stores the transfer state.
 * param count Number of bytes transferred so far by the non-blocking transaction.
 * return status of status_t.
 */
status_t LPSPI_MasterTransferGetCount(LPSPI_Type *base, lpspi_master_handle_t *handle, size_t *count)
{
    assert(handle != NULL);

    if (NULL == count)
    {
        return kStatus_InvalidArgument;
    }

    /* Catch when there is not an active transfer. */
    if (handle->state != (uint8_t)kLPSPI_Busy)
    {
        *count = 0;
        return kStatus_NoTransferInProgress;
    }

    size_t remainingByte;

    if (handle->rxData != NULL)
    {
        remainingByte = handle->rxRemainingByteCount;
    }
    else
    {
        remainingByte = handle->txRemainingByteCount;
    }

    *count = handle->totalByteCount - remainingByte;

    return kStatus_Success;
}

/*!
 * brief LPSPI master abort transfer which uses an interrupt method.
 *
 * This function aborts a transfer which uses an interrupt method.
 *
 * param base LPSPI peripheral address.
 * param handle pointer to lpspi_master_handle_t structure which stores the transfer state.
 */
void LPSPI_MasterTransferAbort(LPSPI_Type *base, lpspi_master_handle_t *handle)
{
    assert(handle != NULL);

    /* Disable interrupt requests*/
    LPSPI_DisableInterrupts(base, (uint32_t)kLPSPI_AllInterruptEnable);

    LPSPI_Reset(base);

    handle->state                = (uint8_t)kLPSPI_Idle;
    handle->txRemainingByteCount = 0;
    handle->rxRemainingByteCount = 0;
}

/*!
 * brief LPSPI Master IRQ handler function.
 *
 * This function processes the LPSPI transmit and receive IRQ.
 *
 * param instance LPSPI instance.
 * param handle pointer to lpspi_master_handle_t structure which stores the transfer state.
 */
void LPSPI_MasterTransferHandleIRQ(uint32_t instance, lpspi_master_handle_t *handle)
{
    assert(handle != NULL);
    assert(instance < ARRAY_SIZE(s_lpspiBases));
    LPSPI_Type *base = s_lpspiBases[instance];
    uint32_t readData;
    uint8_t bytesEachRead          = handle->bytesEachRead;
    bool isByteSwap                = handle->isByteSwap;
    uint32_t readRegRemainingTimes = handle->readRegRemainingTimes;

    if (handle->rxData != NULL)
    {
        if (handle->rxRemainingByteCount != 0U)
        {
            /* First, disable the interrupts to avoid potentially triggering another interrupt
             * while reading out the RX FIFO as more data may be coming into the RX FIFO. We'll
             * re-enable the interrupts based on the LPSPI state after reading out the FIFO.
             */
            LPSPI_DisableInterrupts(base, (uint32_t)kLPSPI_RxInterruptEnable);

            while ((LPSPI_GetRxFifoCount(base) != 0U) && (handle->rxRemainingByteCount != 0U))
            {
                /*Read out the data*/
                readData = LPSPI_ReadData(base);

                /*Decrease the read RX register times.*/
                --handle->readRegRemainingTimes;
                readRegRemainingTimes = handle->readRegRemainingTimes;

                if (handle->rxRemainingByteCount < (size_t)bytesEachRead)
                {
                    handle->bytesEachRead = (uint8_t)(handle->rxRemainingByteCount);
                    bytesEachRead         = handle->bytesEachRead;
                }

                LPSPI_SeparateReadData(handle->rxData, readData, bytesEachRead, isByteSwap);
                handle->rxData += bytesEachRead;

                /*Decrease the remaining RX byte count.*/
                handle->rxRemainingByteCount -= (size_t)bytesEachRead;
            }

            /* Re-enable the interrupts only if rxCount indicates there is more data to receive,
             * else we may get a spurious interrupt.
             * */
            if (handle->rxRemainingByteCount != 0U)
            {
                /* Set the TDF and RDF interrupt enables simultaneously to avoid race conditions */
                LPSPI_EnableInterrupts(base, (uint32_t)kLPSPI_RxInterruptEnable);
            }
        }

        /*Set rxWatermark to (readRegRemainingTimes-1) if readRegRemainingTimes less than rxWatermark. Otherwise there
         *is not RX interrupt for the last datas because the RX count is not greater than rxWatermark.
         */
        if (readRegRemainingTimes <= (uint32_t)handle->rxWatermark)
        {
            base->FCR = (base->FCR & (~LPSPI_FCR_RXWATER_MASK)) |
                        LPSPI_FCR_RXWATER((readRegRemainingTimes > 1U) ? (readRegRemainingTimes - 1U) : (0U));
        }
    }

    if (handle->txRemainingByteCount != 0U)
    {
        if (handle->isTxMask)
        {
            /* When TCR[TXMSK]=1, transfer is initiate by writting a new command word to TCR. TCR[TXMSK] is cleared by
               hardware every time when TCR[FRAMESZ] bit of data is transfered.
               In this case TCR[TXMSK] should be set to initiate each transfer. */
            base->TCR |= LPSPI_TCR_TXMSK_MASK;
            if ((handle->txRemainingByteCount == (uint32_t)handle->bytesPerFrame) && (handle->isPcsContinuous))
            {
                /* For the last piece of frame size of data, if is PCS continous mode(TCR[CONT]), TCR[CONTC] should
                 * be cleared to de-assert the PCS. Be sure to clear the TXMSK as well otherwise another FRAMESZ
                 * of data will be received. */
                base->TCR &= ~(LPSPI_TCR_CONTC_MASK | LPSPI_TCR_CONT_MASK | LPSPI_TCR_TXMSK_MASK);
            }
            handle->txRemainingByteCount -= (uint32_t)handle->bytesPerFrame;
        }
        else
        {
            LPSPI_MasterTransferFillUpTxFifo(base, handle);
        }
    }
    else
    {
        if ((LPSPI_GetTxFifoCount(base) < (handle->fifoSize)))
        {
            if ((handle->isPcsContinuous) && (handle->writeTcrInIsr) && (!handle->isTxMask))
            {
                base->TCR             = (base->TCR & ~(LPSPI_TCR_CONTC_MASK));
                handle->writeTcrInIsr = false;
            }
        }
    }

    if ((handle->txRemainingByteCount == 0U) && (handle->rxRemainingByteCount == 0U) && (!handle->writeTcrInIsr))
    {
        /* If no RX buffer, then transfer is not complete until transfer complete flag sets */
        if (handle->rxData == NULL)
        {
            if ((LPSPI_GetStatusFlags(base) & (uint32_t)kLPSPI_TransferCompleteFlag) != 0U)
            {
                LPSPI_ClearStatusFlags(base, (uint32_t)kLPSPI_TransferCompleteFlag);
                /* Complete the transfer and disable the interrupts */
                LPSPI_MasterTransferComplete(base, handle);
            }
            else
            {
                LPSPI_EnableInterrupts(base, (uint32_t)kLPSPI_TransferCompleteInterruptEnable);
                LPSPI_DisableInterrupts(base, (uint32_t)kLPSPI_TxInterruptEnable | (uint32_t)kLPSPI_RxInterruptEnable);
            }
        }
        else
        {
            /* Complete the transfer and disable the interrupts */
            LPSPI_MasterTransferComplete(base, handle);
        }
    }
}

/*Transactional APIs -- Slave*/
/*!
 * brief Initializes the LPSPI slave handle.
 *
 * This function initializes the LPSPI handle, which can be used for other LPSPI transactional APIs.  Usually, for a
 * specified LPSPI instance, call this API once to get the initialized handle.
 *
 * param base LPSPI peripheral address.
 * param handle LPSPI handle pointer to lpspi_slave_handle_t.
 * param callback DSPI callback.
 * param userData callback function parameter.
 */
void LPSPI_SlaveTransferCreateHandle(LPSPI_Type *base,
                                     lpspi_slave_handle_t *handle,
                                     lpspi_slave_transfer_callback_t callback,
                                     void *userData)
{
    assert(handle != NULL);

    /* Get instance from peripheral base address. */
    uint32_t instance = LPSPI_GetInstance(base);

    /* Zero the handle. */
    (void)memset(handle, 0, sizeof(*handle));

    handle->callback = callback;
    handle->userData = userData;

    if(LP_FLEXCOMM_GetBaseAddress(instance) != 0U)
    {      
        lpspi_to_lpflexcomm_t handler;
        handler.lpspi_slave_handler = LPSPI_SlaveTransferHandleIRQ;
        
        /* Save the handle in global variables to support the double weak mechanism. */
        LP_FLEXCOMM_SetIRQHandler(instance, handler.lpflexcomm_handler, handle, LP_FLEXCOMM_PERIPH_LPSPI);
    }
    else
    {
        s_lpspiHandle[instance] = handle;

        /* Set irq handler. */
        s_lpspiSlaveIsr = LPSPI_SlaveTransferHandleIRQ;
    }
}

/*!
 * brief LPSPI slave transfer data using an interrupt method.
 *
 * This function transfer data using an interrupt method. This is a non-blocking function, which returns right away.
 * When all data is transferred, the callback function is called.
 *
 * Note:
 * The transfer data size should be integer multiples of bytesPerFrame if bytesPerFrame is less than or equal to 4.
 * For bytesPerFrame greater than 4:
 * The transfer data size should be equal to bytesPerFrame if the bytesPerFrame is not an integer multiple of 4.
 * Otherwise, the transfer data size can be an integer multiple of bytesPerFrame.
 *
 * param base LPSPI peripheral address.
 * param handle pointer to lpspi_slave_handle_t structure which stores the transfer state.
 * param transfer pointer to lpspi_transfer_t structure.
 * return status of status_t.
 */
status_t LPSPI_SlaveTransferNonBlocking(LPSPI_Type *base, lpspi_slave_handle_t *handle, lpspi_transfer_t *transfer)
{
    assert(handle != NULL);
    assert(transfer != NULL);

    /* Check that we're not busy.*/
    if (handle->state == (uint8_t)kLPSPI_Busy)
    {
        return kStatus_LPSPI_Busy;
    }
    LPSPI_Enable(base, false);
    /* Check arguements */
    if (!LPSPI_CheckTransferArgument(base, transfer, false))
    {
        return kStatus_InvalidArgument;
    }

    /* Flush FIFO, clear status, disable all the inerrupts. */
    LPSPI_FlushFifo(base, true, true);
    LPSPI_ClearStatusFlags(base, (uint32_t)kLPSPI_AllStatusFlag);
    LPSPI_DisableInterrupts(base, (uint32_t)kLPSPI_AllInterruptEnable);

    /* Variables */
    bool isRxMask = false;
    bool isTxMask = false;
    uint8_t txWatermark;
    uint32_t readRegRemainingTimes;
    uint32_t whichPcs      = (transfer->configFlags & LPSPI_SLAVE_PCS_MASK) >> LPSPI_SLAVE_PCS_SHIFT;
    uint32_t bytesPerFrame = ((base->TCR & LPSPI_TCR_FRAMESZ_MASK) >> LPSPI_TCR_FRAMESZ_SHIFT) / 8U + 1U;

    /* Assign the original value for members of transfer handle. */
    handle->state                  = (uint8_t)kLPSPI_Busy;
    handle->txData                 = transfer->txData;
    handle->rxData                 = transfer->rxData;
    handle->txRemainingByteCount   = transfer->dataSize;
    handle->rxRemainingByteCount   = transfer->dataSize;
    handle->totalByteCount         = transfer->dataSize;
    handle->writeRegRemainingTimes = (transfer->dataSize / bytesPerFrame) * ((bytesPerFrame + 3U) / 4U);
    handle->readRegRemainingTimes  = handle->writeRegRemainingTimes;
    /*The TX and RX FIFO sizes are always the same*/
    handle->fifoSize   = LPSPI_GetRxFifoSize(base);
    handle->isByteSwap = ((transfer->configFlags & (uint32_t)kLPSPI_SlaveByteSwap) != 0U);
    /*Calculate the bytes for write/read the TX/RX register each time*/
    if (bytesPerFrame <= 4U)
    {
        handle->bytesEachWrite = (uint8_t)bytesPerFrame;
        handle->bytesEachRead  = (uint8_t)bytesPerFrame;
    }
    else
    {
        handle->bytesEachWrite = 4U;
        handle->bytesEachRead  = 4U;
    }
    /* Set proper RX and TX watermarks to reduce the ISR response times. */
    if (handle->fifoSize > 1U)
    {
        txWatermark         = 1U;
        handle->rxWatermark = handle->fifoSize - 2U;
    }
    else
    {
        txWatermark         = 0U;
        handle->rxWatermark = 0U;
    }
    LPSPI_SetFifoWatermarks(base, txWatermark, handle->rxWatermark);

    /* If there is no rxData, mask the receive data so that receive data is not stored in receive FIFO. */
    if (handle->rxData == NULL)
    {
        isRxMask                     = true;
        handle->rxRemainingByteCount = 0U;
    }
    /* If there is no txData, mask the transmit data so that no data is loaded from transmit FIFO and output pin
     * is tristated. */
    if (handle->txData == NULL)
    {
        isTxMask                     = true;
        handle->txRemainingByteCount = 0U;
    }

    /* Enable module for following configuration of TCR to take effect. */
    LPSPI_Enable(base, true);

    base->TCR = (base->TCR & ~(LPSPI_TCR_CONT_MASK | LPSPI_TCR_CONTC_MASK | LPSPI_TCR_RXMSK_MASK |
                               LPSPI_TCR_TXMSK_MASK | LPSPI_TCR_PCS_MASK)) |
                LPSPI_TCR_RXMSK(isRxMask) | LPSPI_TCR_TXMSK(isTxMask) | LPSPI_TCR_PCS(whichPcs);

    /* Enable the NVIC for LPSPI peripheral. Note that below code is useless if the LPSPI interrupt is in INTMUX ,
     * and you should also enable the INTMUX interupt in your application.
     */
    (void)EnableIRQ(s_lpspiIRQ[LPSPI_GetInstance(base)]);

    /*TCR is also shared the FIFO, so wait for TCR written.*/
    if (!LPSPI_TxFifoReady(base))
    {
        return kStatus_LPSPI_Timeout;
    }

    /* Fill up the TX data in FIFO */
    if (handle->txData != NULL)
    {
        LPSPI_SlaveTransferFillUpTxFifo(base, handle);
    }

    /* Since SPI is a synchronous interface, we only need to enable the RX interrupt if there is RX data.
     * The IRQ handler will get the status of RX and TX interrupt flags.
     */
    if (handle->rxData != NULL)
    {
        /*Set rxWatermark to (readRegRemainingTimes-1) if readRegRemainingTimes less than rxWatermark. Otherwise there
         *is not RX interrupt for the last datas because the RX count is not greater than rxWatermark.
         */
        readRegRemainingTimes = handle->readRegRemainingTimes;
        if (readRegRemainingTimes <= (uint32_t)handle->rxWatermark)
        {
            base->FCR = (base->FCR & (~LPSPI_FCR_RXWATER_MASK)) | LPSPI_FCR_RXWATER(readRegRemainingTimes - 1U);
        }

        /* RX request and FIFO overflow request enable */
        LPSPI_EnableInterrupts(base, (uint32_t)kLPSPI_RxInterruptEnable | (uint32_t)kLPSPI_ReceiveErrorInterruptEnable);
    }
    else
    {
        LPSPI_EnableInterrupts(base, (uint32_t)kLPSPI_TxInterruptEnable);
    }

    if (handle->txData != NULL)
    {
        /* TX FIFO underflow request enable */
        LPSPI_EnableInterrupts(base, (uint32_t)kLPSPI_TransmitErrorInterruptEnable);
    }

    return kStatus_Success;
}

static void LPSPI_SlaveTransferFillUpTxFifo(LPSPI_Type *base, lpspi_slave_handle_t *handle)
{
    assert(handle != NULL);

    uint32_t wordToSend    = 0U;
    uint8_t bytesEachWrite = handle->bytesEachWrite;
    bool isByteSwap        = handle->isByteSwap;

    while (LPSPI_GetTxFifoCount(base) < (handle->fifoSize))
    {
        if (handle->txRemainingByteCount < (size_t)bytesEachWrite)
        {
            handle->bytesEachWrite = (uint8_t)handle->txRemainingByteCount;
            bytesEachWrite         = handle->bytesEachWrite;
        }

        wordToSend = LPSPI_CombineWriteData(handle->txData, bytesEachWrite, isByteSwap);
        handle->txData += bytesEachWrite;

        /*Decrease the remaining TX byte count.*/
        handle->txRemainingByteCount -= (size_t)bytesEachWrite;

        /*Write the word to TX register*/
        LPSPI_WriteData(base, wordToSend);

        if (handle->txRemainingByteCount == 0U)
        {
            break;
        }
    }
}

static void LPSPI_SlaveTransferComplete(LPSPI_Type *base, lpspi_slave_handle_t *handle)
{
    assert(handle != NULL);

    status_t status = kStatus_Success;

    /* Disable interrupt requests*/
    LPSPI_DisableInterrupts(base, (uint32_t)kLPSPI_AllInterruptEnable);

    if (handle->state == (uint8_t)kLPSPI_Error)
    {
        status = kStatus_LPSPI_Error;
    }
    else
    {
        status = kStatus_Success;
    }

    handle->state = (uint8_t)kLPSPI_Idle;

    if (handle->callback != NULL)
    {
        handle->callback(base, handle, status, handle->userData);
    }
}

/*!
 * brief Gets the slave transfer remaining bytes.
 *
 * This function gets the slave transfer remaining bytes.
 *
 * param base LPSPI peripheral address.
 * param handle pointer to lpspi_slave_handle_t structure which stores the transfer state.
 * param count Number of bytes transferred so far by the non-blocking transaction.
 * return status of status_t.
 */
status_t LPSPI_SlaveTransferGetCount(LPSPI_Type *base, lpspi_slave_handle_t *handle, size_t *count)
{
    assert(handle != NULL);

    if (NULL == count)
    {
        return kStatus_InvalidArgument;
    }

    /* Catch when there is not an active transfer. */
    if (handle->state != (uint8_t)kLPSPI_Busy)
    {
        *count = 0;
        return kStatus_NoTransferInProgress;
    }

    size_t remainingByte;

    if (handle->rxData != NULL)
    {
        remainingByte = handle->rxRemainingByteCount;
    }
    else
    {
        remainingByte = handle->txRemainingByteCount;
    }

    *count = handle->totalByteCount - remainingByte;

    return kStatus_Success;
}

/*!
 * brief LPSPI slave aborts a transfer which uses an interrupt method.
 *
 * This function aborts a transfer which uses an interrupt method.
 *
 * param base LPSPI peripheral address.
 * param handle pointer to lpspi_slave_handle_t structure which stores the transfer state.
 */
void LPSPI_SlaveTransferAbort(LPSPI_Type *base, lpspi_slave_handle_t *handle)
{
    assert(handle != NULL);

    /* Disable interrupt requests*/
    LPSPI_DisableInterrupts(base, (uint32_t)kLPSPI_TxInterruptEnable | (uint32_t)kLPSPI_RxInterruptEnable);

    LPSPI_Reset(base);

    handle->state                = (uint8_t)kLPSPI_Idle;
    handle->txRemainingByteCount = 0U;
    handle->rxRemainingByteCount = 0U;
}

/*!
 * brief LPSPI Slave IRQ handler function.
 *
 * This function processes the LPSPI transmit and receives an IRQ.
 *
 * param instance LPSPI instance index.
 * param handle pointer to lpspi_slave_handle_t structure which stores the transfer state.
 */
void LPSPI_SlaveTransferHandleIRQ(uint32_t instance, lpspi_slave_handle_t *handle)
{
    assert(handle != NULL);
    assert(instance < ARRAY_SIZE(s_lpspiBases));
    LPSPI_Type *base = s_lpspiBases[instance];
    uint32_t readData; /* variable to store word read from RX FIFO */
    uint8_t bytesEachRead = handle->bytesEachRead;
    bool isByteSwap       = handle->isByteSwap;
    uint32_t readRegRemainingTimes;

    if (handle->rxData != NULL)
    {
        if (handle->rxRemainingByteCount > 0U)
        {
            while (LPSPI_GetRxFifoCount(base) != 0U)
            {
                /*Read out the data*/
                readData = LPSPI_ReadData(base);

                /*Decrease the read RX register times.*/
                --handle->readRegRemainingTimes;

                if (handle->rxRemainingByteCount < (size_t)bytesEachRead)
                {
                    handle->bytesEachRead = (uint8_t)handle->rxRemainingByteCount;
                    bytesEachRead         = handle->bytesEachRead;
                }

                LPSPI_SeparateReadData(handle->rxData, readData, bytesEachRead, isByteSwap);
                handle->rxData += bytesEachRead;

                /*Decrease the remaining RX byte count.*/
                handle->rxRemainingByteCount -= (size_t)bytesEachRead;

                if ((handle->txRemainingByteCount > 0U) && (handle->txData != NULL))
                {
                    LPSPI_SlaveTransferFillUpTxFifo(base, handle);
                }

                if (handle->rxRemainingByteCount == 0U)
                {
                    break;
                }
            }
        }

        /*Set rxWatermark to (readRegRemainingTimes-1) if readRegRemainingTimes less than rxWatermark. Otherwise there
         *is not RX interrupt for the last datas because the RX count is not greater than rxWatermark.
         */
        readRegRemainingTimes = handle->readRegRemainingTimes;
        if (readRegRemainingTimes <= (uint32_t)handle->rxWatermark)
        {
            base->FCR = (base->FCR & (~LPSPI_FCR_RXWATER_MASK)) |
                        LPSPI_FCR_RXWATER((readRegRemainingTimes > 1U) ? (readRegRemainingTimes - 1U) : (0U));
        }
    }
    if ((handle->rxData == NULL) && (handle->txRemainingByteCount != 0U) && (handle->txData != NULL))
    {
        LPSPI_SlaveTransferFillUpTxFifo(base, handle);
    }

    if ((handle->txRemainingByteCount == 0U) && (handle->rxRemainingByteCount == 0U))
    {
        /* If no RX buffer, then transfer is not complete until transfer complete flag sets and the TX FIFO empty*/
        if (handle->rxData == NULL)
        {
            if (((LPSPI_GetStatusFlags(base) & (uint32_t)kLPSPI_FrameCompleteFlag) != 0U) &&
                (LPSPI_GetTxFifoCount(base) == 0U))
            {
                LPSPI_ClearStatusFlags(base, (uint32_t)kLPSPI_FrameCompleteFlag);
                /* Complete the transfer and disable the interrupts */
                LPSPI_SlaveTransferComplete(base, handle);
            }
            else
            {
                LPSPI_ClearStatusFlags(base, (uint32_t)kLPSPI_FrameCompleteFlag);
                LPSPI_EnableInterrupts(base, (uint32_t)kLPSPI_FrameCompleteInterruptEnable);
                LPSPI_DisableInterrupts(base, (uint32_t)kLPSPI_TxInterruptEnable | (uint32_t)kLPSPI_RxInterruptEnable);
            }
        }
        else
        {
            /* Complete the transfer and disable the interrupts */
            LPSPI_SlaveTransferComplete(base, handle);
        }
    }

    /* Catch tx fifo underflow conditions, service only if tx under flow interrupt enabled */
    if (((LPSPI_GetStatusFlags(base) & (uint32_t)kLPSPI_TransmitErrorFlag) != 0U) &&
        ((base->IER & LPSPI_IER_TEIE_MASK) != 0U))
    {
        LPSPI_ClearStatusFlags(base, (uint32_t)kLPSPI_TransmitErrorFlag);
        /* Change state to error and clear flag */
        if (handle->txData != NULL)
        {
            handle->state = (uint8_t)kLPSPI_Error;
        }
        handle->errorCount++;     
        /* ERR051588: Clear FIFO after underrun occurs */   
        LPSPI_FlushFifo(base, true, false);
    }
    /* Catch rx fifo overflow conditions, service only if rx over flow interrupt enabled */
    if (((LPSPI_GetStatusFlags(base) & (uint32_t)kLPSPI_ReceiveErrorFlag) != 0U) &&
        ((base->IER & LPSPI_IER_REIE_MASK) != 0U))
    {
        LPSPI_ClearStatusFlags(base, (uint32_t)kLPSPI_ReceiveErrorFlag);
        /* Change state to error and clear flag */
        if (handle->txData != NULL)
        {
            handle->state = (uint8_t)kLPSPI_Error;
        }
        handle->errorCount++;
    }
}

static uint32_t LPSPI_CombineWriteData(const uint8_t *txData, uint8_t bytesEachWrite, bool isByteSwap)
{
    assert(txData != NULL);

    uint32_t wordToSend = 0U;

    switch (bytesEachWrite)
    {
        case 1:
            wordToSend = *txData;
            ++txData;
            break;

        case 2:
            if (!isByteSwap)
            {
                wordToSend = *txData;
                ++txData;
                wordToSend |= (unsigned)(*txData) << 8U;
                ++txData;
            }
            else
            {
                wordToSend = (unsigned)(*txData) << 8U;
                ++txData;
                wordToSend |= *txData;
                ++txData;
            }

            break;

        case 3:
            if (!isByteSwap)
            {
                wordToSend = *txData;
                ++txData;
                wordToSend |= (unsigned)(*txData) << 8U;
                ++txData;
                wordToSend |= (unsigned)(*txData) << 16U;
                ++txData;
            }
            else
            {
                wordToSend = (unsigned)(*txData) << 16U;
                ++txData;
                wordToSend |= (unsigned)(*txData) << 8U;
                ++txData;
                wordToSend |= *txData;
                ++txData;
            }
            break;

        case 4:
            if (!isByteSwap)
            {
                wordToSend = *txData;
                ++txData;
                wordToSend |= (unsigned)(*txData) << 8U;
                ++txData;
                wordToSend |= (unsigned)(*txData) << 16U;
                ++txData;
                wordToSend |= (unsigned)(*txData) << 24U;
                ++txData;
            }
            else
            {
                wordToSend = (unsigned)(*txData) << 24U;
                ++txData;
                wordToSend |= (unsigned)(*txData) << 16U;
                ++txData;
                wordToSend |= (unsigned)(*txData) << 8U;
                ++txData;
                wordToSend |= *txData;
                ++txData;
            }
            break;

        default:
            assert(false);
            break;
    }
    return wordToSend;
}

static void LPSPI_SeparateReadData(uint8_t *rxData, uint32_t readData, uint8_t bytesEachRead, bool isByteSwap)
{
    assert(rxData != NULL);

    switch (bytesEachRead)
    {
        case 1:
            *rxData = (uint8_t)readData;
            ++rxData;
            break;

        case 2:
            if (!isByteSwap)
            {
                *rxData = (uint8_t)readData;
                ++rxData;
                *rxData = (uint8_t)(readData >> 8);
                ++rxData;
            }
            else
            {
                *rxData = (uint8_t)(readData >> 8);
                ++rxData;
                *rxData = (uint8_t)readData;
                ++rxData;
            }
            break;

        case 3:
            if (!isByteSwap)
            {
                *rxData = (uint8_t)readData;
                ++rxData;
                *rxData = (uint8_t)(readData >> 8);
                ++rxData;
                *rxData = (uint8_t)(readData >> 16);
                ++rxData;
            }
            else
            {
                *rxData = (uint8_t)(readData >> 16);
                ++rxData;
                *rxData = (uint8_t)(readData >> 8);
                ++rxData;
                *rxData = (uint8_t)readData;
                ++rxData;
            }
            break;

        case 4:
            if (!isByteSwap)
            {
                *rxData = (uint8_t)readData;
                ++rxData;
                *rxData = (uint8_t)(readData >> 8);
                ++rxData;
                *rxData = (uint8_t)(readData >> 16);
                ++rxData;
                *rxData = (uint8_t)(readData >> 24);
                ++rxData;
            }
            else
            {
                *rxData = (uint8_t)(readData >> 24);
                ++rxData;
                *rxData = (uint8_t)(readData >> 16);
                ++rxData;
                *rxData = (uint8_t)(readData >> 8);
                ++rxData;
                *rxData = (uint8_t)readData;
                ++rxData;
            }
            break;

        default:
            assert(false);
            break;
    }
}

static bool LPSPI_TxFifoReady(LPSPI_Type *base)
{
#if SPI_RETRY_TIMES
    uint32_t waitTimes = SPI_RETRY_TIMES;
    while (((uint8_t)LPSPI_GetTxFifoCount(base) != 0U) && (--waitTimes != 0U))
#else
    while ((uint8_t)LPSPI_GetTxFifoCount(base) != 0U)
#endif
    {
    }
#if SPI_RETRY_TIMES
    if (waitTimes == 0U)
    {
        return false;
    }
#endif
    return true;
}

void LPSPI_CommonIRQHandler(LPSPI_Type *base, uint32_t instance);
void LPSPI_CommonIRQHandler(LPSPI_Type *base, uint32_t instance)
{
    assert(s_lpspiHandle[instance] != NULL);
    if (LPSPI_IsMaster(base))
    {
        s_lpspiMasterIsr(instance, (lpspi_master_handle_t *)s_lpspiHandle[instance]);
    }
    else
    {
        s_lpspiSlaveIsr(instance, (lpspi_slave_handle_t *)s_lpspiHandle[instance]);
    }
    SDK_ISR_EXIT_BARRIER;
}

#if defined(LPSPI14)
void LPSPI14_DriverIRQHandler(void);
void LPSPI14_DriverIRQHandler(void)
{
    LPSPI_CommonIRQHandler(LPSPI14, 14);
}
#endif

#if defined(LPSPI16)
void LPSPI16_DriverIRQHandler(void);
void LPSPI16_DriverIRQHandler(void)
{
    LPSPI_CommonIRQHandler(LPSPI16, 16);
}
#endif
