/*******************************************************************************
*
* Copyright [2014-]2014 Freescale Semiconductor, Inc.

*
* This software is owned or controlled by Freescale Semiconductor.
* Use of this software is governed by the Freescale License
* distributed with this Material.
* See the LICENSE file distributed for more details.
* 
*
*******************************************************************************/

#ifndef __FSL_ENC_DRIVER_H__
#define __FSL_ENC_DRIVER_H__

#include <stdint.h>
#include <stdbool.h>

#include "fsl_enc_hal.h"
#include "fsl_os_abstraction.h"
#if FSL_FEATURE_SOC_ENC_COUNT

/*!
 * @addtogroup enc_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
extern ENC_Type* const g_encBase[];
extern const IRQn_Type g_encCmpIrqId[ENC_INSTANCE_COUNT];
extern const IRQn_Type g_encHomeIrqId[ENC_INSTANCE_COUNT];
extern const IRQn_Type g_encWdtIrqId[ENC_INSTANCE_COUNT];
extern const IRQn_Type g_encIndexIrqId[ENC_INSTANCE_COUNT];
/*!
 * @brief User configuration structure for ENC driver.
 *
 * Use an instance of this structure with the ENC_DRV_Init()function. This enables configuration of the
 * most common settings of the ENC peripheral with a single function call.
 * @internal gui name="ENC configuration" id="encCfg"
 */
typedef struct EncUserConfig {
    uint32_t posCntInitValue;           /*!< Value to put in Initialization Register. @internal gui name="Initialization register" id="InitReg" */
    uint32_t posCmpValue;               /*!< Value to put in Position Compare Register. @internal gui name="Position compare register" id="PosCompReg" */
    uint32_t moduloValue;               /*!< Value to put in Modulus Register. @internal gui name="Modulus register" id="ModReg" */
    uint16_t watchdogTimeout;           /*!< Value to put in Watchdog Timeout Register. @internal gui name="Watchdog time-out register" id="WdogTimetReg" */
    uint8_t filterCount;                /*!< Value represents the number of consecutive samples that must agree prior to the input filter accepting an input transition. @internal gui name="Filter sample count" id="FilterCount" */
    uint8_t filterPeriod;               /*!< Value represents the sampling period (in IPBus clock cycles) of the decoder input signals. @internal gui name="Filter sample period" id="FilterPeriod" */
    enc_operation_mode_t operationMode; /*!< Operation mode: Normal mode, modulo counting mode or bypass (signal phase count) mode. @internal gui name="Operation mode" id="OpMode" */
    bool reverseCounting;               /*!< Counting direction: Normal (false) or reverse (true) counting direction. @internal gui name="Reverse counting" id="ReverseCnt" */
    bool indexInputNegativeEdge;        /*!< Type of transition edge of INDEX input signal: positive (false) or negative (true). @internal gui name="INDEX input signal" id="IdxNegEdge" */
    bool homeInputNegativeEdge;         /*!< Type of transition edge of HOME input signal: positive (false) or negative (true). @internal gui name="HOME input signal" id="HomeNegEdge" */
    bool indexPulsePosInit;             /*!< To use HOME (false) or INDEX (true) input to initialize position counter to value in Initialization Register. @internal gui name="Position counter init. type" id="IdxPulsePosInit" */
    bool triggerUpdateHoldRegEnable;    /*!< Enable/disable updating hold registers on TRIGGER input. @internal gui name="Update hold registers" id="UpdateHoldReg" */
    bool triggerClearPosRegEnable;      /*!< Enable/disable clear of position registers on TRIGGER input. @internal gui name="Clear position registers" id="ClearPosReg" */
    bool moduloRevolutionCounting;      /*!< Type of revolution counter - index pulse counting (on false) or modulo counting (on true). @internal gui name="Revolution counter" id="TypeRevCnt" */
    bool outputControlOnReading;        /*!< Used to control the behaviour of the POSMATCH output signal. True - output control on reading position register, false - OC on match position register. @internal gui name="POSMATCH output signal" id="PosMatchOut" */
} enc_user_config_t;

/*!
 * @brief User configuration structure for ENC driver - ENC test module configuration.
 *
 * Use an instance of this structure with the ENC_DRV_TestInit()function. 
 * This enables configuration of the Test module of the ENC peripheral
 * with a single function call.
 */
typedef struct EncTestConfig {
    uint8_t testCount;                  /*!< Test count - holds the number of quadrature advances to generate. */       
    uint8_t testPeriod;                 /*!< Test period - holds the period of quadrature phase in IPBus clock cycles. */
    bool testNegativeSignalEnable;      /*!< Test signal type, positive (false) or negative (true). */
} enc_test_config_t;

/*!
 * @brief Counter registers structure for ENC driver.
 *
 * Use an instance of this structure with the ENC_DRV_ReadHoldRegisters() or
 * ENC_DRV_ReadCounters() functions. This reads counters and hold registers of
 * Position, PositionDifference, Revolution Counter.
 */
typedef struct EncCounter {
    int32_t position;                  /*!< Position Counter/Hold Register. */
    int16_t posDiff;                   /*!< Position Difference Counter/Hold Register. */
    int16_t revolution;                /*!< Revolution Counter/Hold Register. */
} enc_counter_t;

/*!
 * @brief Input monitor structure for ENC driver.
 *
 * Use an instance of this structure with the ENC_DRV_ReadInputMonitorRegister(). 
 * This reads Input Monitor register that contains the values of the raw or filtered
 * PHASEA, PHASEB, INDEX and HOME input signals.
 */
typedef struct EncInputMonitor {
    bool phaseA;                        /*!< PHASEA input. */
    bool phaseB;                        /*!< PHASEB input. */
    bool index;                         /*!< INDEX input. */
    bool home;                          /*!< HOME input. */
} enc_input_monitor_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Configuration
 * @{
 */
  
/*!
 * @brief Fills the initial user configuration for the ENC module
 * without the interrupts enablement.
 *
 * This function  fills the initial user configuration. Calling the initialization
 * function with the filled parameter configures the ENC module to function as
 * a simple Quadrature Encoder. The settings are:
 *
  @code
    encUserConfig.operationMode = kEncNormalMode;
    encUserConfig.reverseCounting = false;
    encUserConfig.indexInputNegativeEdge = false;
    encUserConfig.homeInputNegativeEdge = false;
    encUserConfig.indexPulsePosInit = true;
    encUserConfig.posCntInitValue = 0U;
    encUserConfig.posCmpValue = 0xFFFFU;
    encUserConfig.moduloValue = 0U;
    encUserConfig.triggerUpdateHoldRegEnable = false;
    encUserConfig.triggerClearPosRegEnable = false;
    encUserConfig.moduloRevolutionCounting = false;
    encUserConfig.outputControlOnReading = false;
    encUserConfig.watchdogTimeout = 0U;
    encUserConfig.filterCount = 0U;
    encUserConfig.filterPeriod = 0U;
  @endcode
 *
 * @param userConfigPtr Pointer to the user configuration structure.
 * @return              Execution status.
 */
enc_status_t ENC_DRV_StructInitUserConfigNormal(enc_user_config_t * userConfigPtr);
  
/*!
 * @brief Initializes an ENC instance for operation.
 *
 * This function initializes the run-time state structure to un-gate the clock to the ENC module,
 * initializes the module to user-defined settings and default settings,
 * configures the IRQ state structure, and enables the module-level interrupt to the core.
 * This example shows how to set up the enc_state_t and the
 * enc_user_config_t parameters and how to call the ENC_DRV_Init function by passing
 * in these parameters:
   @code
    enc_user_config_t encUserConfig;
    encUserConfig.operationMode = kEncNormalMode;
    encUserConfig.reverseCounting = false;
    encUserConfig.indexInputNegativeEdge = false;
    encUserConfig.homeInputNegativeEdge = false;
    encUserConfig.indexPulsePosInit = true;
    encUserConfig.posCntInitValue = 0U;
    encUserConfig.posCmpValue = 0xFFFFU;
    encUserConfig.moduloValue = 0U;
    encUserConfig.triggerUpdateHoldRegEnable = false;
    encUserConfig.triggerClearPosRegEnable = false;
    encUserConfig.moduloRevolutionCounting = false;
    encUserConfig.outputControlOnReading = false;
    encUserConfig.watchdogTimeout = 0U;
    encUserConfig.filterCount = 0U;
    encUserConfig.filterPeriod = 0U;
    ENC_DRV_Init(&encUserConfig);
   @endcode
 *
 * @param instance      ENC instance ID.
 * @param userConfigPtr The user configuration structure of type enc_user_config_t. The user
 *  is responsible to fill out the members of this structure and to pass the pointer 
 *  of this structure into this function.
 * @return              Execution status.
 */
enc_status_t ENC_DRV_Init(uint32_t instance, const enc_user_config_t *userConfigPtr);  
  
/*!
 * @brief De-initializes the ENC peripheral.
 *
 * This function shuts down the ENC clock to reduce power consumption. 
 *
 * @param instance      ENC instance ID.
 */
void ENC_DRV_Deinit(uint32_t instance);

/*!
 * @brief Initializes an ENC test module.
 *
 * This function initializes the run-time state structure to enable the test module
 * and sets the test period and test count values.
 * This example shows how to set up the enc_test_config_t parameters and 
 * how to call the ENC_DRV_TestInit function by passing in these parameters:
   @code
    enc_test_config_t encTestConfig;
    encTestConfig.testNegativeSignalEnable = false;
    encTestConfig.testCount = 100;
    encTestConfig.testPeriod = 10;
    ENC_DRV_TestInit(&encTestConfig);
   @endcode
 * 
 * @param instance      ENC instance ID.
 * @param userConfigPtr The user configuration structure of type enc_test_config_t.
 * @return              Execution status.
 */
enc_status_t ENC_DRV_TestInit(uint32_t instance, const enc_test_config_t * userConfigPtr);

/*!
 * @brief Shuts down the ENC test module, disables test counter,
 * and clears the test period and test count values.
 *
 * @param instance      ENC instance ID.
 */
void ENC_DRV_TestDeinit(uint32_t instance);

/*!
 * @brief Enables/disables the selected ENC interrupt.
 *
 * The interrupt source is passing as argument of type enc_interrupt_source_t.
 *
 * @param instance      ENC instance ID.
 * @param intSrc        The type of interrupt to enable/disable.
 * @param enable        Bool parameter to enable/disable.
 * @return              Execution status.
 */
enc_status_t ENC_DRV_SetIntMode
  (uint32_t instance, enc_int_source_t intSrc, bool enable);

/*!
 * @brief Gets the configuration of the selected ENC interrupt.
 *
 * The interrupt type is passing as an argument of type enc_int_source_t.
 *
 * @param instance      ENC instance ID.
 * @param intSrc        The type of interrupt to get configuration.
 * @return              Configuration of selected interrupt source.
 */
bool ENC_DRV_GetIntMode(uint32_t instance, enc_int_source_t intSrc);

/*!
 * @brief Gets the interrupt status flag of the selected interrupt source. 
 *
 * @param instance      ENC instance ID.
 * @param flag          Selected type of status flag.
 * @return              State of selected flag.
 */
bool ENC_DRV_GetStatusFlag(uint32_t instance, enc_status_flag_t flag);

/*!
 * @brief Clears the status flag of the selected status source. 
 *
 * @param instance      ENC instance ID.
 * @param flag          Selected type of status flag.
 */
void ENC_DRV_ClearStatusFlag(uint32_t instance, enc_status_flag_t flag);
 
/*!
 * @brief Reads the actual values of the ENC counter registers.
 *
 * @param instance      ENC instance ID.
 * @param countRegPtr   The structure of ENC counter registers.
 * @return              Execution status.
 */
enc_status_t ENC_DRV_ReadCounters(uint32_t instance, enc_counter_t * countRegPtr);

/*!
 * @brief Reads the ENC hold registers.
 *
 * @param instance      ENC instance ID.
 * @param holdRegPtr    The structure of ENC hold registers.
 * @return              Execution status.
 */
enc_status_t ENC_DRV_ReadHoldReg(uint32_t instance, enc_counter_t * holdRegPtr);

/*!
 * @brief Resets the ENC counter registers.
 *
 * @param instance      ENC instance ID.
 */
void ENC_DRV_ResetCounters(uint32_t instance);

/*!
 * @brief Reads the ENC input monitor register.
 *
 * @param instance              ENC instance ID.
 * @param inputMonitorRaw       The type of input monitor - raw (true) / filtered (false).
 * @param inputMonitorPtr       The structure of ENC Monitor register variables.
 * @return                      Execution status.
 */
enc_status_t ENC_DRV_ReadInputMonitor
  (uint32_t instance, bool inputMonitorRaw, enc_input_monitor_t * inputMonitorPtr);

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif
#endif /* __FSL_ENC_DRIVER_H__*/

/*******************************************************************************
 * EOF
 ******************************************************************************/
