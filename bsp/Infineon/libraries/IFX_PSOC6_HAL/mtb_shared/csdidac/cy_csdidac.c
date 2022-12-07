/***************************************************************************//**
* \file cy_csdidac.c
* \version 2.10
*
* \brief
* This file provides the CSD HW block IDAC functionality implementation.
*
********************************************************************************
* \copyright
* Copyright 2019-2020, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#include "cy_device_headers.h"
#include "cy_syslib.h"
#include "cy_syspm.h"
#include "cy_csdidac.h"
#include "cy_gpio.h"
#include "cy_csd.h"

#if (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2))


/*******************************************************************************
* Function Prototypes - Internal Functions
*******************************************************************************/
/**
* \cond SECTION_CSDIDAC_INTERNAL
* \addtogroup group_csdidac_internal
* \{
*/
static void Cy_CSDIDAC_ConnectChannelA(cy_stc_csdidac_context_t * context);
static void Cy_CSDIDAC_ConnectChannelB(cy_stc_csdidac_context_t * context);
static void Cy_CSDIDAC_DisconnectChannelA(cy_stc_csdidac_context_t * context);
static void Cy_CSDIDAC_DisconnectChannelB(cy_stc_csdidac_context_t * context);
/** \}
* \endcond */


/*******************************************************************************
* Local Definition
*******************************************************************************/
#define CY_CSDIDAC_FSM_ABORT                        (0x08u)

/* IDAC configuration register */
/* +--------+---------------+-------------------------------------------------------------------+
 * |  BITS  |   FIELD       |             DEFAULT MODE                                          |
 * |--------|---------------|-------------------------------------------------------------------|
 * | 6:0    | VAL           | 0x00(Sets the IDAC value to "0")                                  |
 * | 7      | POL_STATIC    | 0x00(Sets the static IDAC polarity)                               |
 * | 9:8    | POLARITY      | 0x00(IDAC polarity SOURCE)                                        |
 * | 11:10  | BAL_MODE      | 0x00(IDAC is enabled in PHI2 and disabled at the end of balancing)|
 * | 17:16  | LEG1_MODE     | 0x00(Configures LEG1 to GP_static mode)                           |
 * | 19:18  | LEG2_MODE     | 0x00(Configures LEG1 to GP_static mode)                           |
 * | 21     | DSI_CTRL_EN   | 0x00(The IDAC DSI control is disabled)                            |
 * | 23:22  | RANGE         | 0x00(Sets the range parameter value to low: 1LSB = 37.5 nA)       |
 * | 24     | LEG1_EN       | 0x00(The output for LEG1 is disabled)                             |
 * | 25     | LEG2_EN       | 0x00(The output for LEG2 is disabled)                             |
 * +--------+---------------+-------------------------------------------------------------------+*/
#define CY_CSDIDAC_DEFAULT_CFG                      (0x01800000uL)
#define CY_CSDIDAC_POLARITY_POS                     (8uL)
#define CY_CSDIDAC_POLARITY_MASK                    (3uL << CY_CSDIDAC_POLARITY_POS)
#define CY_CSDIDAC_LSB_POS                          (22uL)
#define CY_CSDIDAC_LSB_MASK                         (3uL << CY_CSDIDAC_LSB_POS)
#define CY_CSDIDAC_LEG1_EN_POS                      (24uL)
#define CY_CSDIDAC_LEG1_EN_MASK                     (1uL << CY_CSDIDAC_LEG1_EN_POS)
#define CY_CSDIDAC_LEG2_EN_POS                      (25uL)
#define CY_CSDIDAC_LEG2_EN_MASK                     (1uL << CY_CSDIDAC_LEG2_EN_POS)
#define CY_CSDIDAC_RANGE_MASK                       (CY_CSDIDAC_LSB_MASK | CY_CSDIDAC_LEG1_EN_MASK | CY_CSDIDAC_LEG2_EN_MASK)

/*
* All the defines below correspond to IDAC LSB in pA
*/
#define CY_CSDIDAC_LSB_37                           (  37500u)
#define CY_CSDIDAC_LSB_75                           (  75000u)
#define CY_CSDIDAC_LSB_300                          ( 300000u)
#define CY_CSDIDAC_LSB_600                          ( 600000u)
#define CY_CSDIDAC_LSB_2400                         (2400000u)
#define CY_CSDIDAC_LSB_4800                         (4800000u)

#define CY_CSDIDAC_LSB_37_MAX_CURRENT             (  4762500u)
#define CY_CSDIDAC_LSB_75_MAX_CURRENT             (  9525000u)
#define CY_CSDIDAC_LSB_300_MAX_CURRENT            ( 38100000u)
#define CY_CSDIDAC_LSB_600_MAX_CURRENT            ( 76200000u)
#define CY_CSDIDAC_LSB_2400_MAX_CURRENT           (304800000u)
#define CY_CSDIDAC_LSB_4800_MAX_CURRENT           (609600000u)

#define CY_CSDIDAC_CODE_MASK                        (127u)
#define CY_CSDIDAC_CONST_2                          (2u)
#define CY_CSDIDAC_CONST_10                         (10u)
#define CY_CSDIDAC_CONST_1000                       (1000u)
#define CY_CSDIDAC_CONST_1000000                    (1000000u)

/* CSD HW block CONFIG register definitions */
#define CY_CSDIDAC_CSD_REG_CONFIG_INIT              (0x80001000uL)
#define CY_CSDIDAC_CSD_REG_CONFIG_DEFAULT           (CY_CSDIDAC_CSD_REG_CONFIG_INIT)

/* CSD_INTR register masks */
#define CY_CSDIDAC_CSD_INTR_SAMPLE_MSK              (0x00000001uL)
#define CY_CSDIDAC_CSD_INTR_INIT_MSK                (0x00000002uL)
#define CY_CSDIDAC_CSD_INTR_ADC_RES_MSK             (0x00000100uL)
#define CY_CSDIDAC_CSD_INTR_ALL_MSK                 (CY_CSDIDAC_CSD_INTR_SAMPLE_MSK | \
                                                     CY_CSDIDAC_CSD_INTR_INIT_MSK | \
                                                     CY_CSDIDAC_CSD_INTR_ADC_RES_MSK)
/* CSD_INTR_MASK register masks */
#define CY_CSDIDAC_CSD_INTR_MASK_SAMPLE_MSK         (0x00000001uL)
#define CY_CSDIDAC_CSD_INTR_MASK_INIT_MSK           (0x00000002uL)
#define CY_CSDIDAC_CSD_INTR_MASK_ADC_RES_MSK        (0x00000100uL)
#define CY_CSDIDAC_CSD_INTR_MASK_CLEAR_MSK          (0x00000000uL)

/* Switch definitions */
#define CY_CSDIDAC_SW_BYPA_ENABLE                   (0x00001000uL)
#define CY_CSDIDAC_SW_BYPB_ENABLE                   (0x00010000uL)
#define CY_CSDIDAC_SW_REFGEN_SEL_IBCB_ON            (0x00000010uL)
#define CY_CSDIDAC_SW_REFGEN_SEL_IAIB_ON            (0x00000001uL)

#define CY_CSDIDAC_CSD_CONFIG_DEFAULT  {\
    .config         = 0x80001000uL,\
    .spare          = 0x00000000uL,\
    .status         = 0x00000000uL,\
    .statSeq        = 0x00000000uL,\
    .statCnts       = 0x00000000uL,\
    .statHcnt       = 0x00000000uL,\
    .resultVal1     = 0x00000000uL,\
    .resultVal2     = 0x00000000uL,\
    .adcRes         = 0x00000000uL,\
    .intr           = 0x00000000uL,\
    .intrSet        = 0x00000000uL,\
    .intrMask       = 0x00000000uL,\
    .intrMasked     = 0x00000000uL,\
    .hscmp          = 0x00000000uL,\
    .ambuf          = 0x00000000uL,\
    .refgen         = 0x00000000uL,\
    .csdCmp         = 0x00000000uL,\
    .swRes          = 0x00000000uL,\
    .sensePeriod    = 0x00000000uL,\
    .senseDuty      = 0x00000000uL,\
    .swHsPosSel     = 0x00000000uL,\
    .swHsNegSel     = 0x00000000uL,\
    .swShieldSel    = 0x00000000uL,\
    .swAmuxbufSel   = 0x00000000uL,\
    .swBypSel       = 0x00000000uL,\
    .swCmpPosSel    = 0x00000000uL,\
    .swCmpNegSel    = 0x00000000uL,\
    .swRefgenSel    = CY_CSDIDAC_SW_REFGEN_SEL_IBCB_ON,\
    .swFwModSel     = 0x00000000uL,\
    .swFwTankSel    = 0x00000000uL,\
    .swDsiSel       = 0x00000000uL,\
    .ioSel          = 0x00000000uL,\
    .seqTime        = 0x00000000uL,\
    .seqInitCnt     = 0x00000000uL,\
    .seqNormCnt     = 0x00000000uL,\
    .adcCtl         = 0x00000000uL,\
    .seqStart       = 0x00000000uL,\
    .idacA          = 0x00000000uL,\
    .idacB          = 0x00000000uL,\
    }


/*******************************************************************************
* Function Name: Cy_CSDIDAC_Init
****************************************************************************//**
*
* Captures the CSD HW block and configures it to the default state.
* This function is called by the application program prior to calling
* any other middleware function.
*
* Initializes the CSDIDAC middleware. Acquires, locks, and initializes
* the CSD HW block by using the low-level CSD driver.
* The function performs the following tasks:
* * Verifies the input parameters. The CY_CSDIDAC_BAD_PARAM is returned if
*   verification fails.
* * Acquires and locks the CSD HW block for use of the CSDIDAC, if the CSD HW
*   block is in a free state.
* * If the CSD HW block is acquired, it is initialized with
*   the CSDIDAC middleware by the default configuration.
*   The output pins are not connected to the CSD HW block.
*   The outputs are disabled and CY_CSDIDAC_SUCCESS is returned.
*
* To connect an output pin and enable an output current, the
* Cy_CSDIDAC_OutputEnable() or Cy_CSDIDAC_OutputEnableExt() functions
* are used.
* If there is no CSD HW block, the CY_CSDIDAC_HW_BUSY status is returned,
* and the CSDIDAC middleware waits for the CSD HW block to be in the idle
* state to initialize.
*
* \param config
* The pointer to the configuration structure \ref cy_stc_csdidac_config_t that
* contains the CSDIDAC middleware initial configuration data generated
* by the CSD personality of the ModusToolbox Device Configurator tool.
*
* \param context
* The pointer to the CSDIDAC context structure \ref cy_stc_csdidac_context_t
* passed by the user. After the initialization, this structure contains
* both CSDIDAC configuration and internal data. It is used during the whole
* CSDIDAC operation.
*
* \return
* The function returns the status of its operation.
* * CY_CSDIDAC_SUCCESS           - The operation is performed successfully.
* * CY_CSDIDAC_BAD_PARAM         - The input pointer is NULL or an invalid
*                                  parameter is passed.
* * CY_CSDIDAC_HW_LOCKED         - The CSD HW block is already in use by other
*                                  middleware.
* * CY_CSDIDAC_HW_FAILURE        - The CSD HW block failure.
* * CY_CSDIDAC_BAD_CONFIGURATION - The CSDIDAC configuration structure
*                                  initialization issue.
*
*******************************************************************************/
cy_en_csdidac_status_t Cy_CSDIDAC_Init(
                const cy_stc_csdidac_config_t * config,
                cy_stc_csdidac_context_t * context)
{
    cy_en_csdidac_status_t result = CY_CSDIDAC_BAD_PARAM;

    if ((NULL != config) && (NULL != context))
    {
        if(true == Cy_CSDIDAC_IsIdacConfigValid(config))
        {
            /* Copies the configuration structure to the context. */
            context->cfgCopy = *config;
            /* Captures the CSD HW block for the IDAC functionality. */
            result = Cy_CSDIDAC_Restore(context);
            if (CY_CSDIDAC_SUCCESS == result)
            {
                /* Disconnects all CSDIDAC channels. */
                Cy_CSDIDAC_DisconnectChannelA(context);
                Cy_CSDIDAC_DisconnectChannelB(context);
                /* Wakes up the CSD HW block. */
                (void)Cy_CSDIDAC_Wakeup(context);
            }
        }
        else
        {
            result = CY_CSDIDAC_BAD_CONFIGURATION;
        }
    }

    return (result);
}


/*******************************************************************************
* Function Name: Cy_CSDIDAC_DeInit
****************************************************************************//**
*
* Stops the middleware operation and releases the CSD HW block.
*
* If any output channel is enabled, it will be disabled and disconnected.
*
* After the CSDIDAC middleware is stopped, the CSD HW block may be
* reconfigured by the application program or other middleware for any
* other usage.
*
* When the middleware operation is stopped by the Cy_CSDIDAC_DeInit()
* function, a subsequent call of the Cy_CSDIDAC_Init() function repeats the
* initialization process. However, to implement Time-multiplexed mode
* (sharing the CSD HW Block between multiple middleware),
* the Cy_CSDIDAC_Save() and Cy_CSDIDAC_Restore() functions are used
* instead of the Cy_CSDIDAC_DeInit() and Cy_CSDIDAC_Init() functions.
*
* \param context
* The pointer to the CSDIDAC context structure \ref cy_stc_csdidac_context_t.
*
* \return
* The function returns the status of its operation.
* * CY_CSDIDAC_SUCCESS           - The operation is performed successfully.
* * CY_CSDIDAC_BAD_PARAM         - The input pointer is NULL or an invalid
*                                  parameter is passed.
* * CY_CSDIDAC_HW_LOCKED         - The CSD HW block is already in use by other
*                                  middleware.
* * CY_CSDIDAC_HW_FAILURE        - A CSD HW block failure.
*
*******************************************************************************/
cy_en_csdidac_status_t Cy_CSDIDAC_DeInit(cy_stc_csdidac_context_t * context)
{
    return (Cy_CSDIDAC_Save(context));
}


/*******************************************************************************
* Function Name: Cy_CSDIDAC_WriteConfig
****************************************************************************//**
*
* Updates the CSDIDAC middleware with the desired configuration.
*
* This function sets the desired CSDIDAC middleware configuration.
* The function performs the following:
* * Verifies the input parameters
* * Verifies whether the CSD HW block is captured by the CSDIDAC middleware
*   and that there are no active IDAC outputs.
* * Initializes the CSD HW block registers with data passed through the
*   config parameter of this function if the above verifications are
*   successful.
* * Returns the status code regarding the function execution result.
*
* \param config
* The pointer to the CSDIDAC configuration structure to be updated.
*
* \param context
* The pointer to the CSDIDAC context structure \ref cy_stc_csdidac_context_t.
*
* \return
* The function returns the status of its operation.
* * CY_CSDIDAC_SUCCESS           - The operation is performed successfully.
* * CY_CSDIDAC_BAD_PARAM         - The input pointer is NULL or an invalid
*                                  parameter is passed.
* * CY_CSDIDAC_HW_BUSY           - Any IDAC output is enabled. The operation
*                                  cannot be completed.
* * CY_CSDIDAC_HW_LOCKED         - The CSD HW block is already in use by other
*                                  middleware.
* * CY_CSDIDAC_BAD_CONFIGURATION - The CSDIDAC configuration structure
*                                  initialization issue.
*
*******************************************************************************/
cy_en_csdidac_status_t Cy_CSDIDAC_WriteConfig(
                const cy_stc_csdidac_config_t * config,
                cy_stc_csdidac_context_t * context)
{
    cy_en_csdidac_status_t result = CY_CSDIDAC_BAD_PARAM;
    uint32_t tmpRegValue = CY_CSDIDAC_SW_REFGEN_SEL_IBCB_ON;

    if ((NULL != config) && (NULL != context))
    {
        if(true == Cy_CSDIDAC_IsIdacConfigValid(config))
        {
            if (CY_CSD_IDAC_KEY == Cy_CSD_GetLockStatus(context->cfgCopy.base, context->cfgCopy.csdCxtPtr))
            {
                if ((CY_CSDIDAC_DISABLE == context->channelStateA) && (CY_CSDIDAC_DISABLE == context->channelStateB))
                {
                    /* Copies the configuration structure to the context. */
                    context->cfgCopy = *config;

                    /* Disconnects the IDACs from AMUX buses. */
                    Cy_CSD_WriteReg(context->cfgCopy.base, CY_CSD_REG_OFFSET_SW_BYP_SEL, 0u);

                    /* Closes the IAIB switch if IDACs joined. */
                    if ((CY_CSDIDAC_JOIN == context->cfgCopy.configA) || (CY_CSDIDAC_JOIN == context->cfgCopy.configB))
                    {
                        tmpRegValue |= CY_CSDIDAC_SW_REFGEN_SEL_IAIB_ON;
                    }
                    Cy_CSD_WriteReg(context->cfgCopy.base, CY_CSD_REG_OFFSET_SW_REFGEN_SEL, tmpRegValue);
                    result = CY_CSDIDAC_SUCCESS;
                }
                else
                {
                    result = CY_CSDIDAC_HW_BUSY;
                }
            }
            else
            {
                result = CY_CSDIDAC_HW_LOCKED;
            }
        }
        else
        {
            result = CY_CSDIDAC_BAD_CONFIGURATION;
        }
    }

    return (result);
}


/*******************************************************************************
* Function Name: Cy_CSDIDAC_Wakeup
****************************************************************************//**
*
* Provides a delay required for the CSD HW block to settle after a wakeup
* from CPU / System Deep Sleep.
*
* This function provides a delay after exiting CPU / System Deep Sleep.
* After the CSD HW block has been powered off, an extra delay is required
* to establish the CSD HW block correct operation.
*
* \param context
* The pointer to the CSDIDAC context structure \ref cy_stc_csdidac_context_t.
*
* \return
* The function returns the status of its operation.
* * CY_CSDIDAC_SUCCESS   - The operation is performed successfully.
* * CY_CSDIDAC_BAD_PARAM - The input pointer is NULL.
*
*******************************************************************************/
cy_en_csdidac_status_t Cy_CSDIDAC_Wakeup(const cy_stc_csdidac_context_t * context)
{
    cy_en_csdidac_status_t result = CY_CSDIDAC_BAD_PARAM;

    if (NULL != context)
    {
        Cy_SysLib_DelayUs((uint16_t)context->cfgCopy.csdInitTime);
        result = CY_CSDIDAC_SUCCESS;
    }

    return (result);
}


/*******************************************************************************
* Function Name: Cy_CSDIDAC_DeepSleepCallback
****************************************************************************//**
*
* The callback function to prepare the CSDIDAC before entering CPU / System Deep Sleep.
*
* This function handles CPU active to CPU / System Deep Sleep power mode transition
* for the CSDIDAC middleware.
* Calling this function directly from the application program is not
* recommended. Instead, Cy_SysPm_CpuEnterDeepSleep() is used for CPU active to
* CPU / System Deep Sleep power mode transition of the device.
* \note
* After the CPU Deep Sleep transition, the device automatically goes
* to System Deep Sleep if all conditions are fulfilled: another core is
* in CPU Deep Sleep, all the peripherals are ready to System Deep Sleep, etc.
* (see details in the device TRM).
*
* For the CSDIDAC middleware correct operation during CPU active to
* CPU / System Deep Sleep mode transition, a callback to this API is registered
* using the Cy_SysPm_RegisterCallback() function with CY_SYSPM_DEEPSLEEP
* type. After the callback is registered, this function is called by the
* Cy_SysPm_CpuEnterDeepSleep() function to prepare the middleware for the device
* power mode transition.
*
* When this function is called with CY_SYSPM_CHECK_READY as an input, this
* function returns CY_SYSPM_SUCCESS if no output is enabled. Otherwise,
* CY_SYSPM_FAIL is returned. If CY_SYSPM_FAIL status is returned, a device
* cannot change power mode. To provide such a transition, the application
* program disables all the enabled IDAC outputs.
*
* \param callbackParams
* Refer to the description of the cy_stc_syspm_callback_params_t type in the
* Peripheral Driver Library documentation.
*
* \param mode
* Refer to the description of the cy_en_syspm_callback_mode_t type in the
* Peripheral Driver Library documentation.
*
* \return
* Returns the status of the operation requested by the mode parameter:
* * CY_SYSPM_SUCCESS  - CPU / System Deep Sleep power mode can be entered.
* * CY_SYSPM_FAIL     - CPU / System Deep Sleep power mode cannot be entered.
*
*******************************************************************************/
cy_en_syspm_status_t Cy_CSDIDAC_DeepSleepCallback(
                cy_stc_syspm_callback_params_t * callbackParams,
                cy_en_syspm_callback_mode_t mode)
{
    cy_en_syspm_status_t retVal = CY_SYSPM_SUCCESS;
    cy_stc_csdidac_context_t * csdIdacCxt = (cy_stc_csdidac_context_t *) callbackParams->context;

    if (CY_SYSPM_CHECK_READY == mode)
    { /* Actions before entering CPU / System Deep Sleep */
        if ((CY_CSD_IDAC_KEY == Cy_CSD_GetLockStatus(csdIdacCxt->cfgCopy.base, csdIdacCxt->cfgCopy.csdCxtPtr)) &&
           ((CY_CSDIDAC_ENABLE == csdIdacCxt->channelStateA) || (CY_CSDIDAC_ENABLE == csdIdacCxt->channelStateB)))
        {
            retVal = CY_SYSPM_FAIL;
        }
    }

    return (retVal);
}


/*******************************************************************************
* Function Name: Cy_CSDIDAC_Save
****************************************************************************//**
*
* Saves the state of the CSDIDAC middleware so the functionality can be
* restored later.
*
* This function, along with Cy_CSDIDAC_Restore(), is specifically designed
* to support time multiplexing of the CSD HW block between multiple
* middleware. When the CSD HW block is shared by more than one middleware,
* this function can be used to save the current state of the CSDIDAC middleware
* and the CSD HW block prior to releasing the CSD HW block for use by other
* middleware.
*
* This function performs the following operations:
* * Saves the current configuration of the CSD HW block and CSDIDAC middleware.
* * Configures the output pins to the default state and disconnects them from
* the CSD HW block. Releases the CSD HW block.
*
* \param context
* The pointer to the CSDIDAC context structure \ref cy_stc_csdidac_context_t.
*
* \return
* The function returns the status of its operation.
* * CY_CSDIDAC_SUCCESS      - The operation is performed successfully.
* * CY_CSDIDAC_BAD_PARAM    - The input pointer is NULL or an invalid parameter
*                             is passed. The operation is not completed.
* * CY_CSDIDAC_HW_LOCKED    - The CSD HW block is already in use by other middleware.
*                             The CSDIDAC middleware cannot save the state
*                             without the initialization or restore operation.
* * CY_CSDIDAC_HW_FAILURE   - A CSD HW block failure.
*
*******************************************************************************/
cy_en_csdidac_status_t Cy_CSDIDAC_Save(cy_stc_csdidac_context_t * context)
{
    cy_en_csdidac_status_t result = CY_CSDIDAC_BAD_PARAM;
    cy_en_csd_status_t initStatus = CY_CSD_LOCKED;

    if (NULL != context)
    {
        if (CY_CSD_IDAC_KEY == Cy_CSD_GetLockStatus(context->cfgCopy.base, context->cfgCopy.csdCxtPtr))
        {
            /* Disconnects the output channels pins from analog buses. */
            Cy_CSDIDAC_DisconnectChannelA(context);
            Cy_CSDIDAC_DisconnectChannelB(context);

            /* Releases the HW CSD block. */
            initStatus = Cy_CSD_DeInit(context->cfgCopy.base, CY_CSD_IDAC_KEY, context->cfgCopy.csdCxtPtr);

            if (CY_CSD_SUCCESS == initStatus)
            {
                result = CY_CSDIDAC_SUCCESS;
            }
            else
            {
                result = CY_CSDIDAC_HW_FAILURE;
            }
        }
        else
        {
            result = CY_CSDIDAC_HW_LOCKED;
        }
    }

    return (result);
}


/*******************************************************************************
* Function Name: Cy_CSDIDAC_Restore
****************************************************************************//**
*
* Resumes the middleware operation if the Cy_CSDIDAC_Save() function was
* called previously.
*
* This function, along with the Cy_CSDIDAC_Save() function, is specifically
* designed to support the CSD HW block time-multiplexing
* among multiple middleware. When the CSD HW block is shared by more than one
* middleware, this function can be used to restore the CSD HW block previous
* state and the CSDIDAC middleware saved using the Cy_CSDIDAC_Save() function.
*
* This function performs the Cy_CSDIDAC_Init() function, part tasks
* namely captures the CSD HW block. Use the Cy_CSDIDAC_Save() and
* Cy_CSDIDAC_Restore() functions to implement Time-multiplexed mode
* instead of using the Cy_CSDIDAC_DeInit() and Cy_CSDIDAC_Init() functions.
*
* \param context
* The pointer to the CSDIDAC middleware context
* structure \ref cy_stc_csdidac_context_t.
*
* \return
* The function returns the status of its operation.
* * CY_CSDIDAC_SUCCESS           - The operation is performed successfully.
* * CY_CSDIDAC_BAD_PARAM         - The input pointer is NULL or an invalid
*                                  parameter is passed.
* * CY_CSDIDAC_HW_LOCKED         - The CSD HW block is already in use by
*                                  another middleware.
* * CY_CSDIDAC_HW_FAILURE        - The CSD HW block failure.
*
*******************************************************************************/
cy_en_csdidac_status_t Cy_CSDIDAC_Restore(cy_stc_csdidac_context_t * context)
{
    uint32_t watchdogCounter;

    cy_en_csdidac_status_t result = CY_CSDIDAC_HW_FAILURE;
    cy_en_csd_key_t mvKey;
    cy_en_csd_status_t initStatus = CY_CSD_LOCKED;
    CSD_Type * ptrCsdBaseAdd = context->cfgCopy.base;
    cy_stc_csd_context_t * ptrCsdCxt = context->cfgCopy.csdCxtPtr;
    cy_stc_csd_config_t csdCfg = CY_CSDIDAC_CSD_CONFIG_DEFAULT;

    /* The number of cycles of one for() loop. */
    const uint32_t cyclesPerLoop = 5u;
    /* The timeout in microseconds */
    const uint32_t watchdogTimeoutUs = 10000u;

    if (NULL != context)
    {
        /* Closes the IAIB switch if IDACs joined */
        if ((CY_CSDIDAC_JOIN == context->cfgCopy.configA) || (CY_CSDIDAC_JOIN == context->cfgCopy.configB))
        {
            csdCfg.swRefgenSel |= CY_CSDIDAC_SW_REFGEN_SEL_IAIB_ON;
        }

        /* Gets the CSD HW block status. */
        mvKey = Cy_CSD_GetLockStatus(ptrCsdBaseAdd, ptrCsdCxt);
        if(CY_CSD_NONE_KEY == mvKey)
        {
            Cy_CSD_WriteReg(ptrCsdBaseAdd, CY_CSD_REG_OFFSET_INTR_MASK, CY_CSDIDAC_CSD_INTR_MASK_CLEAR_MSK);
            Cy_CSD_WriteReg(ptrCsdBaseAdd, CY_CSD_REG_OFFSET_SEQ_START, CY_CSDIDAC_FSM_ABORT);

            /* Initializes the Watchdog Counter to prevent a hang. */
            watchdogCounter = (watchdogTimeoutUs * (context->cfgCopy.cpuClk / CY_CSDIDAC_CONST_1000000)) / cyclesPerLoop;
            do
            {
                initStatus = Cy_CSD_GetConversionStatus(ptrCsdBaseAdd, ptrCsdCxt);
                watchdogCounter--;
            }
            while((CY_CSD_BUSY == initStatus) && (0u != watchdogCounter));

            if (CY_CSD_SUCCESS == initStatus)
            {
                /* Captures the CSD HW block for the IDAC functionality. */
                initStatus = Cy_CSD_Init(ptrCsdBaseAdd, &csdCfg, CY_CSD_IDAC_KEY, ptrCsdCxt);

                if(CY_CSD_SUCCESS == initStatus)
                {
                    result = CY_CSDIDAC_SUCCESS;
                }
            }
        }
        else
        {
            result = CY_CSDIDAC_HW_LOCKED;
        }
    }
    else
    {
        result = CY_CSDIDAC_BAD_PARAM;
    }
    return (result);
}


/*******************************************************************************
* Function Name: Cy_CSDIDAC_OutputEnable
****************************************************************************//**
*
* Enables an IDAC output with a specified current.
*
* This function performs the following:
* * Verifies the input parameters.
* * Identifies LSB and IDAC code required to generate the specified
*   output current and configures the CSD HW block accordingly.
* * Configures and enables the CSDIDAC specified output and returns
*   the status code.
*
* \param ch
* The CSDIDAC supports two outputs (A and B), this parameter
* specifies the output to be enabled.
*
* \param current
* A current value for an IDAC output in nA with a sign. If the parameter is
* positive, a sourcing current is generated. If the parameter is
* negative, the sinking current is generated. The middleware
* identifies LSB and code values required to achieve the specified output
* current. The middleware chooses the minimum possible LSB to generate the
* current to minimize a quantization error. NOTE! the quantization
* error in the output current based on the LSB size (37.5/
* 75/300/600/2400/4800 nA). For instance, if this function
* is called to set 123456 nA, the actual output current is rounded
* to the nearest value of multiple to 2400 nA, i.e 122400 nA. The absolute
* value of this parameter is in the range from 0x00u
* to \ref CY_CSDIDAC_MAX_CURRENT_NA.
*
* \param context
* The pointer to the CSDIDAC middleware context
* structure \ref cy_stc_csdidac_context_t.
*
* \return
* The function returns the status of its operation.
* * CY_CSDIDAC_SUCCESS    - The operation is performed successfully.
* * CY_CSDIDAC_BAD_PARAM  - The input pointer is NULL or an invalid parameter
*                           is passed.
*
*******************************************************************************/
cy_en_csdidac_status_t Cy_CSDIDAC_OutputEnable(
                cy_en_csdidac_choice_t ch,
                int32_t current,
                cy_stc_csdidac_context_t * context)
{
    cy_en_csdidac_status_t retVal = CY_CSDIDAC_BAD_PARAM;
    cy_en_csdidac_polarity_t polarity= CY_CSDIDAC_SOURCE;
    cy_en_csdidac_lsb_t lsbIndex;
    uint32_t absCurrent = (0 > current) ? (uint32_t)(-current) : (uint32_t)current;
    uint32_t code;

    if((NULL != context) && (CY_CSDIDAC_MAX_CURRENT_NA >= absCurrent))
    {
        if(true == Cy_CSDIDAC_IsIdacChoiceValid(ch, context->cfgCopy.configA, context->cfgCopy.configB))
        {
            /* Chooses the desired current polarity */
            if (0 > current)
            {
                polarity = CY_CSDIDAC_SINK;
            }
            /* Converts absCurrent to pA */
            absCurrent *= CY_CSDIDAC_CONST_1000;
            /* Chooses IDAC LSB and calculates the IDAC code */
            if (absCurrent < CY_CSDIDAC_LSB_37_MAX_CURRENT)
            {
                lsbIndex = CY_CSDIDAC_LSB_37_IDX;
                code = absCurrent / CY_CSDIDAC_LSB_37;
            }
            else if (absCurrent < CY_CSDIDAC_LSB_75_MAX_CURRENT)
            {
                lsbIndex = CY_CSDIDAC_LSB_75_IDX;
                code = absCurrent / CY_CSDIDAC_LSB_75;
            }
            else if (absCurrent < CY_CSDIDAC_LSB_300_MAX_CURRENT)
            {
                lsbIndex = CY_CSDIDAC_LSB_300_IDX;
                code = absCurrent / CY_CSDIDAC_LSB_300;
            }
            else if (absCurrent < CY_CSDIDAC_LSB_600_MAX_CURRENT)
            {
                lsbIndex = CY_CSDIDAC_LSB_600_IDX;
                code = absCurrent / CY_CSDIDAC_LSB_600;
            }
            else if(absCurrent < CY_CSDIDAC_LSB_2400_MAX_CURRENT)
            {
                lsbIndex = CY_CSDIDAC_LSB_2400_IDX;
                code = absCurrent / CY_CSDIDAC_LSB_2400;
            }
            else
            {
                lsbIndex = CY_CSDIDAC_LSB_4800_IDX;
                code = absCurrent / CY_CSDIDAC_LSB_4800;
            }
            if (code > CY_CSDIDAC_MAX_CODE)
            {
                code = CY_CSDIDAC_MAX_CODE;
            }

            /* Sets the desired IDAC(s) polarity, LSB and code in the CSD block and connects output(s). */
            retVal = Cy_CSDIDAC_OutputEnableExt(ch, polarity, lsbIndex, code, context);
        }
    }

    return (retVal);
}


/*******************************************************************************
* Function Name: Cy_CSDIDAC_OutputEnableExt
****************************************************************************//**
*
* Enables an IDAC output with the specified polarity, LSB, and IDAC code.
*
* This function performs the following:
* * Verifies the input parameters.
* * Configures and enables the specified output of CSDIDAC and returns the
*   status code.
*
* \param outputCh
* CSDIDAC supports two outputs, this parameter specifies the output to
* be enabled.
*
* \param polarity
* The polarity to be set for the specified IDAC.
*
* \param lsbIndex
* The LSB to be set for the specified IDAC.
*
* \param idacCode
* The code value for the specified IDAC in the range from 0 u
* to \ref CY_CSDIDAC_MAX_CODE.
*
* \param context
* The pointer to the CSDIDAC middleware context
* structure \ref cy_stc_csdidac_context_t.
*
* \return
* The function returns the status of its operation.
* * CY_CSDIDAC_SUCCESS    - The operation is performed successfully.
* * CY_CSDIDAC_BAD_PARAM  - The input pointer is NULL or an invalid parameter
*                           is passed.
*
*******************************************************************************/
cy_en_csdidac_status_t Cy_CSDIDAC_OutputEnableExt(
                cy_en_csdidac_choice_t outputCh,
                cy_en_csdidac_polarity_t polarity,
                cy_en_csdidac_lsb_t lsbIndex,
                uint32_t idacCode,
                cy_stc_csdidac_context_t * context)
{
    CSD_Type * ptrCsdBaseAdd = context->cfgCopy.base;
    uint32_t idacRegValue;
    uint32_t  interruptState;
    cy_en_csdidac_status_t retVal = CY_CSDIDAC_BAD_PARAM;

    if((NULL != context) && (CY_CSDIDAC_MAX_CODE >= idacCode))
    {
        if((true == Cy_CSDIDAC_IsIdacChoiceValid(outputCh, context->cfgCopy.configA, context->cfgCopy.configB)) &&
           (true == Cy_CSDIDAC_IsIdacPolarityValid(polarity)) &&
           (true == Cy_CSDIDAC_IsIdacLsbValid(lsbIndex)))
         {
            idacRegValue = idacCode | (((uint32_t)polarity) << CY_CSDIDAC_POLARITY_POS);
            /* Sets IDAC LSB. The LSB value equals lsbIndex divided by 2 */
            idacRegValue |= ((((uint32_t)lsbIndex) >> 1uL) << CY_CSDIDAC_LSB_POS);
            /* Sets the IDAC leg1 enabling bit */
            idacRegValue |= ((uint32_t)CY_CSDIDAC_LEG1_EN_MASK);
            /* Sets the IDAC leg2 enabling bit if the lsbIndex is even. */
            if (0u != (lsbIndex % CY_CSDIDAC_CONST_2))
            {
                idacRegValue |= ((uint32_t)CY_CSDIDAC_LEG2_EN_MASK);
            }

            interruptState = Cy_SysLib_EnterCriticalSection();
            if (((CY_CSDIDAC_A == outputCh) || (CY_CSDIDAC_AB == outputCh)) &&
                (CY_CSDIDAC_DISABLED != context->cfgCopy.configA))
            {
                /* Sets the IDAC A polarity, LSB and code in the context structure. */
                context->polarityA = polarity;
                context->lsbA = lsbIndex;
                context->codeA = (uint8_t)idacCode;
                context->channelStateA = CY_CSDIDAC_ENABLE;
                /* Connects the IDAC A output. */
                Cy_CSDIDAC_ConnectChannelA(context);
                /* A connected IDAC B output must be available if the IDAC A output is joined to it. */
                if (CY_CSDIDAC_JOIN == context->cfgCopy.configA)
                {
                    Cy_CSDIDAC_ConnectChannelB(context);
                }
                Cy_CSD_WriteReg(ptrCsdBaseAdd, CY_CSD_REG_OFFSET_IDACA, idacRegValue);

                retVal = CY_CSDIDAC_SUCCESS;
            }

            if (((CY_CSDIDAC_B == outputCh) || (CY_CSDIDAC_AB == outputCh)) &&
                (CY_CSDIDAC_DISABLED != context->cfgCopy.configB))
            {
                /* Sets the IDAC B polarity, LSB and code in the context structure. */
                context->polarityB = polarity;
                context->lsbB = lsbIndex;
                context->codeB = (uint8_t)idacCode;
                context->channelStateB = CY_CSDIDAC_ENABLE;
                /* Connects the IDAC B output. */
                Cy_CSDIDAC_ConnectChannelB(context);
                /* A connected IDAC A output must be available if the IDAC B output is joined to it */
                if (CY_CSDIDAC_JOIN == context->cfgCopy.configB)
                {
                    Cy_CSDIDAC_ConnectChannelA(context);
                }
                Cy_CSD_WriteReg(ptrCsdBaseAdd, CY_CSD_REG_OFFSET_IDACB, idacRegValue);

                retVal = CY_CSDIDAC_SUCCESS;
            }
            Cy_SysLib_ExitCriticalSection(interruptState);
        }
    }

    return (retVal);
}


/*******************************************************************************
* Function Name: Cy_CSDIDAC_ConnectChannelA
****************************************************************************//**
*
* Connects an IDAC A output as specified by the configuration.
*
* \param context
* The pointer to the CSDIDAC middleware context
* structure \ref cy_stc_csdidac_context_t.
*
*******************************************************************************/
static void Cy_CSDIDAC_ConnectChannelA(
                cy_stc_csdidac_context_t * context)
{
    /* Closes the bypass A switch to feed output current to AMuxBusA. */
    if ((CY_CSDIDAC_GPIO == context->cfgCopy.configA) ||  (CY_CSDIDAC_AMUX == context->cfgCopy.configA))
    {
        Cy_CSD_SetBits(context->cfgCopy.base, CY_CSD_REG_OFFSET_SW_BYP_SEL, CY_CSDIDAC_SW_BYPA_ENABLE);
    }
    /* Configures port pin, if it is enabled. */
    if ((CY_CSDIDAC_GPIO == context->cfgCopy.configA) && (NULL != context->cfgCopy.ptrPinA))
    {
        /* Update port configuration register (drive mode) to High-Z Analog */
        Cy_GPIO_SetDrivemode(context->cfgCopy.ptrPinA->ioPcPtr, (uint32_t)context->cfgCopy.ptrPinA->pin, CY_GPIO_DM_ANALOG);
        /* Connect the selected port to AMuxBusA */
        Cy_GPIO_SetHSIOM(context->cfgCopy.ptrPinA->ioPcPtr, (uint32_t)context->cfgCopy.ptrPinA->pin, HSIOM_SEL_AMUXA);
    }
}


/*******************************************************************************
* Function Name: Cy_CSDIDAC_ConnectChannelB
****************************************************************************//**
*
* Connects an IDAC B output as specified by the configuration.
*
* \param context
* The pointer to the CSDIDAC middleware context
* structure \ref cy_stc_csdidac_context_t.
*
*******************************************************************************/
static void Cy_CSDIDAC_ConnectChannelB(
                cy_stc_csdidac_context_t * context)
{
    /* Closes the bypass B switch to feed an output current to AMuxBusB. */
    if ((CY_CSDIDAC_GPIO == context->cfgCopy.configB) ||  (CY_CSDIDAC_AMUX == context->cfgCopy.configB))
    {
        Cy_CSD_SetBits(context->cfgCopy.base, CY_CSD_REG_OFFSET_SW_BYP_SEL, CY_CSDIDAC_SW_BYPB_ENABLE);
    }
    /* Configures port pin, if it is enabled. */
    if (CY_CSDIDAC_GPIO == context->cfgCopy.configB)
    {
        /* Update port configuration register (drive mode) to High-Z Analog */
        Cy_GPIO_SetDrivemode(context->cfgCopy.ptrPinB->ioPcPtr, (uint32_t)context->cfgCopy.ptrPinB->pin, CY_GPIO_DM_ANALOG);
        /* Connect the selected port to AMuxBusB */
        Cy_GPIO_SetHSIOM(context->cfgCopy.ptrPinB->ioPcPtr, (uint32_t)context->cfgCopy.ptrPinB->pin, HSIOM_SEL_AMUXB);
    }
}


/*******************************************************************************
* Function Name: Cy_CSDIDAC_DisconnectChannelA
****************************************************************************//**
*
* Disconnects the output channel A pin, if it is configured.
*
* \param context
* The pointer to the CSDIDAC middleware context
* structure \ref cy_stc_csdidac_context_t.
*
*******************************************************************************/
static void Cy_CSDIDAC_DisconnectChannelA(cy_stc_csdidac_context_t * context)
{
    /* Disables the desired IDAC. */
    context->channelStateA = CY_CSDIDAC_DISABLE;
    Cy_CSD_WriteReg(context->cfgCopy.base, CY_CSD_REG_OFFSET_IDACA, 0uL);
    /* Opens the bypass A switch to disconnect an output current from AMuxBusA. */
    if ((CY_CSDIDAC_GPIO == context->cfgCopy.configA) ||  (CY_CSDIDAC_AMUX == context->cfgCopy.configA))
    {
        Cy_CSD_ClrBits(context->cfgCopy.base, CY_CSD_REG_OFFSET_SW_BYP_SEL, CY_CSDIDAC_SW_BYPA_ENABLE);
    }
    /* Disconnects AMuxBusA from the selected pin, if it is configured. */
    if ((CY_CSDIDAC_GPIO == context->cfgCopy.configA) && (NULL != context->cfgCopy.ptrPinA))
    {
        Cy_GPIO_SetHSIOM(context->cfgCopy.ptrPinA->ioPcPtr, (uint32_t)context->cfgCopy.ptrPinA->pin, HSIOM_SEL_GPIO);
    }
}


/*******************************************************************************
* Function Name: Cy_CSDIDAC_DisconnectChannelB
****************************************************************************//**
*
* Disconnects the output channel B pin, if it is configured.
*
* \param context
* The pointer to the CSDIDAC middleware context
* structure \ref cy_stc_csdidac_context_t.
*
*******************************************************************************/
static void Cy_CSDIDAC_DisconnectChannelB(cy_stc_csdidac_context_t * context)
{
    /* Disables the desired IDAC. */
    context->channelStateB = CY_CSDIDAC_DISABLE;
    Cy_CSD_WriteReg(context->cfgCopy.base, CY_CSD_REG_OFFSET_IDACB, 0uL);
    /* Opens the bypass B switch to disconnect an output current from AMuxBusB. */
    if ((CY_CSDIDAC_GPIO == context->cfgCopy.configB) ||  (CY_CSDIDAC_AMUX == context->cfgCopy.configB))
    {
        Cy_CSD_ClrBits(context->cfgCopy.base, CY_CSD_REG_OFFSET_SW_BYP_SEL, CY_CSDIDAC_SW_BYPB_ENABLE);
    }
    /* Disconnects AMuxBusB from the selected pin, if it is configured. */
    if ((CY_CSDIDAC_GPIO == context->cfgCopy.configB) && (NULL != context->cfgCopy.ptrPinB))
    {
        Cy_GPIO_SetHSIOM(context->cfgCopy.ptrPinB->ioPcPtr, (uint32_t)context->cfgCopy.ptrPinB->pin, HSIOM_SEL_GPIO);
    }
}


/*******************************************************************************
* Function Name: Cy_CSDIDAC_OutputDisable
****************************************************************************//**
*
* Disables a specified IDAC output.
*
* The function performs the following:
* * Verifies the input parameters.
* * Disables the specified output of CSDIDAC and returns the status code.
*
* \param ch
* The channel to disconnect.
*
* \param context
* The pointer to the CSDIDAC middleware context
* structure \ref cy_stc_csdidac_context_t.
*
* \return
* The function returns the status of its operation.
* * CY_CSDIDAC_SUCCESS    - The operation is performed successfully.
* * CY_CSDIDAC_BAD_PARAM  - The input pointer is NULL or an invalid parameter
*                           is passed.
*
*******************************************************************************/
cy_en_csdidac_status_t Cy_CSDIDAC_OutputDisable(
                cy_en_csdidac_choice_t ch,
                cy_stc_csdidac_context_t * context)
{
    cy_en_csdidac_status_t retVal = CY_CSDIDAC_BAD_PARAM;

    if(NULL != context)
    {
        if ((CY_CSDIDAC_A == ch) || (CY_CSDIDAC_AB == ch))
        {
            Cy_CSDIDAC_DisconnectChannelA(context);
            retVal = CY_CSDIDAC_SUCCESS;
        }
        if ((CY_CSDIDAC_B == ch) || (CY_CSDIDAC_AB == ch))
        {
            Cy_CSDIDAC_DisconnectChannelB(context);
            retVal = CY_CSDIDAC_SUCCESS;
        }
    }

    return (retVal);
}

#endif /* (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2)) */


/* [] END OF FILE */
