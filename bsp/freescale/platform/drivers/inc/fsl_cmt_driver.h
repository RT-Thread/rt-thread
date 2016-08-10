/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
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
#ifndef __FSL_CMT_DRIVER_H__
#define __FSL_CMT_DRIVER_H__
 
#include <stdint.h>
#include <stdbool.h>
#include "fsl_cmt_hal.h"
 
/*!
 * @addtogroup cmt_driver
 * @{
 */

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Table of base addresses for CMT instances. */
extern CMT_Type * const g_cmtBase[];

/*! @brief Table to save CMT IRQ enumeration numbers defined in the CMSIS header file */
extern const IRQn_Type g_cmtIrqId[];

/*! @brief Define the standard intermediate frequency (IF) */
#define CMT_INTERMEDIATEFREQUENCY_8MHZ    8000000U

/*! @brief Define the standard intermediate frequency (IF) */
#define CMT_MODULATEUNIT8BITS       8U    

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief CMT configuration structure
 *
 * Defines a basic configure structure CmtBaseConfig and uses the CMT_DRV_Init() function to make necessary
 * initializations.
 *
 * 
 */
typedef struct CmtBaseConfig {
    bool isInterruptEnabled;       /*!< Timer interrupt 0-disable/1-enable */
    bool isIroEnabled;             /*!< The IRO output 0-disabled/1-enabled*/
    cmt_iro_polarity_t iroPolarity;        /*!< The IRO polarity */
    cmt_second_clkdiv_t cmtDivider;        /*!< The CMT clock divide prescaler */
} cmt_base_config_t;


/*!
 * @brief CMT modulate data structure
 *
 * Defines a data structure for CMT data modulation.
 *
 * 
 */
typedef struct CmtModulateData {
    uint8_t *data;        /* The data for modulation*/
    uint32_t len;         /* The length of data bit for modulation*/
    uint32_t lenDone;     /* The length of data bit has been modulated*/
    /* The mark and space time for the data bit "1" */
    uint16_t markOne;
    uint16_t spaceOne;
    /* The mark and space time for the data bit "0" */
    uint16_t markZero;
    uint16_t spaceZero;    
} cmt_modulate_data_t;

/*!
 * @brief CMT modulate configure structure
 *
 * Defines a specific configuration structure CmtModulateConfig and uses the 
 * CMT_DRV_StartCarrierModulate() function to initialize and start carrier 
 * generator and modulator. Stores the transmitted data information to 
 * the global variable for data modulation.
 * 
 */
typedef struct CmtModulateConfig {
    /*!< Choose these mode for carrier and modulator enabled, kCMTDirectIROCtl should not used here*/
    cmt_mode_t mode; 
    /*!< The high and low time for the carrier signal */
    uint8_t highCount1;  
    uint8_t lowCount1;  
    /* The high and low time for the second frequency carrier signal in FSK mode*/
    uint8_t highCount2;  
    uint8_t lowCount2;
    /* The mark and space time for the modulator gate*/
    uint16_t markCount;
    uint16_t spaceCount;
} cmt_modulate_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization and Shutdown
 * @{
 */

/*!
 * @brief Initializes the CMT module.
 * 
 * This function must be called before calling all the other CMT driver functions.
 * This function ungates the CMT clock and sets the CMT clock, interrupt, 
 * and output signal for CMT module. Pass in its basic configuration structure.
 * 
 *
 * @param instance CMT module instance number.
 * @param config The CMT basic configuration structure.
 * @return Error or success status returned by API.
 */
cmt_status_t CMT_DRV_Init(uint32_t instance, const cmt_base_config_t * config);

/*!
 * @brief Disables the CMT module and gate control.
 *
 * This function disables all CMT interrupts and CMT clock. It, then, gates the
 * CMT clock control. CMT_DRV_Init must be called if you want to use CMT again.
 *
 * @param instance CMT module instance number.
 * @return Error or success status returned by API.
 */
cmt_status_t CMT_DRV_Deinit(uint32_t instance);

/*!
 * @brief Starts the CMT carrier generator and modulator.
 * 
 * This function un-gates the CMT carrier generator and modulator clock, initializes, and
 * starts the modulator and carrier generator. Pass in the modulation specific configuration structure.
 * CMT_DRV_Init should be called before using this function.
 * 
 *
 * @param instance CMT module instance number.
 * @param modulateConfig The CMT modulator specific configuration structure.
 * @param cmtData The data to be modulated.
 * @param isMsbMode The MSB or LSB mode for the byte transmit
 *                  - true, The MSB mode.
 *                  - false, The LSB mode.    
 */
void CMT_DRV_StartCarrierModulate(uint32_t instance, cmt_modulate_config_t *modulateConfig,
                         cmt_modulate_data_t *cmtData, bool isMsbMode);

/*!
 * @brief Stops the CMT carrier generator and modulator.
 * 
 * This function stops and disables the CMT carrier generator and modulator.
 * When the CMT carrier generator and modulator is disabled the IRO signal
 * can be controlled directly by calling the CMT_DRV_SetIroCtl.
 * 
 *
 * @param instance CMT module instance number.
 */
void CMT_DRV_StopCarrierModulate(uint32_t instance);

/*!
 * @brief Modulates the date by one bit.
 * 
 * This function can be called by the CMT ISR handler to handle data modulation by using ISR handler
 * to change the modulation mark and space time period according to 
 * the data bit "1" or bit "0" each time.
 * Note: the modulation updates the mark and space time period at the end of every modulation
 * cycle, irrespective of interrupt handling. To update the new mark and space time period in time, 
 * this function should be processed in one modulation cycle. 
 * When tested for Bare Metal, the function called by the ISR handler takes about 4 µs and the maximum
 * bit rate is about 250000.  
 *
 * @param instance CMT module instance number.
 * @param cmtData The data to be modulated.
 * @param isMsbMode The MSB or LSB mode for the byte transmit.
 *                  - true, The MSB mode.
 *                  - false, The LSB mode.   
 */
cmt_status_t CMT_DRV_ModulateDataByBit(uint32_t instance, cmt_modulate_data_t *cmtData, bool isMsbMode);

/*!
 * @brief Selects the mode for CMT.
 *
 * This function selects the mode for CMT.
 *
 * @param base Base address for current CMT instance.
 * @param mode Selection of CMT feature mode enumeration. See to "cmt_mode_t"
 */
void CMT_DRV_SetMode(uint32_t instance, cmt_mode_t mode);

/*!
 * @brief Gets the mode of CMT module.
 *
 * This function gets the mode of CMT module.
 *
 * @param base Base address for current CMT instance.
 * @return The mode of CMT module. See to "cmt_mode_t".
 */
cmt_mode_t CMT_DRV_GetMode(uint32_t instance);

/* @} */

/*! 
 * @name Clock divider
 * @{
 */

/*!
 * @brief Sets CMT clock divider.
 * 
 * This function sets the CMT clock divider.
 *
 *
 * @param instance CMT module instance number.
 * @param spsDiv The CMT clock divider prescaler. The CMT carrier generator resolution is
 *        8 Mhz/(2 ^ spsDiv)  . spsDiv should be a integer range between
 *        0 ~ 3 representing the divisor 1,2,4 and 8 (See "cmt_second_clkdiv_t").
 */
void CMT_DRV_SetClockDiv(uint32_t instance, cmt_second_clkdiv_t spsDiv);

/* @} */

/*! 
 * @name Interrupt
 * @{
 */

/*!
 * @brief Reads Reads the current end of cycle flag.
 *
 * This flag is set at the end of each cycle.
 *
 * @param instance CMT module instance number.
 * @param channel Timer channel number
 * @return The status of the end of cycle flag
 *         - true:  The end of cycle has occurred.
 *         - false: The end of cycle has not yet occurred.
 */
bool CMT_DRV_IsEndofCycle(uint32_t instance);


/*!
 * @brief Clears the end of cycle status flag.
 * 
 * Clears the end of cycle status flag by reading the MSC followed by
 * and access of the lower eight bit of the modulator mark or space counter.
 * Note that this is not for clearing the end of cycle status flag when the CMT DMA is enabled.   
 *
 * @param instance CMT module instance number.
 * @param markCount The number of clock period for CMT modulator signal mark period,
 *                   in the range of 0 ~ 0xFFFF. 
 */
void CMT_DRV_ClearEndofCycleFlag(uint32_t instance, uint32_t markCount);

/* @} */

/*! 
 * @name Counters
 * @{
 */

/*!
 * @brief Sets the modulation mark time period for the CMT modulator counter.
 *
 * This function sets the mark time period of the CMT modulator counter
 * to control the mark time of the output modulated signal from the carrier generator output signal. 
 * If the CMT clock frequency is Fcmt and the carrier out signal frequency is fcg: 
 *        - In Time and Baseband mode: The mark period of the generated signal equals (markCount + 1) / (Fcmt/8).
 *        - In FSK mode:The mark period of the generated signal equals (markCount + 1) / fcg.
 *
 * @param instance CMT module instance number.
 * @param markCount The number of clock period for CMT modulator signal mark period,
 *                   in the range of 0 ~ 0xFFFF. 
 */
void CMT_DRV_SetModulateMarkCount(uint32_t instance, uint32_t markCount);

/*!
 * @brief Sets the modulation space time period for the CMT modulator counter.
 *
 * This function sets the mark time period of the CMT modulator counter
 * to control the space time of the output modulated signal from the carrier generator output signal. 
 * If the CMT clock frequency is Fcmt and the carrier out signal frequency is fcg: 
 *      - In Time and Baseband mode: The space period of the generated signal equals spaceCount / (Fcmt/8).  
 *      - In FSK mode:The space period of the generated signal equals spaceCount / fcg.
 *
 * @param instance CMT module instance number.
 * @param spaceCount The number of clock period for CMT modulator signal space period,
 *                   in the range of 0 ~ 0xFFFF. 
 */
void CMT_DRV_SetModulateSpaceCount(uint32_t instance, uint32_t spaceCount);

/* @} */

/*!
 * @name Output signal Control
 * @{
 */

/*!
 * @brief IRO Latch Control.
 * 
 * Changes the states of the IRO signal when the kCMTDirectIROMode mode is set
 * and the IRO signal is enabled.
 *
 * @param base Base address for current CMT instance.
 * @param ctlVal The control of the IRO signal. See "_cmt_iro_ctl_t"
 */
void CMT_DRV_SetIroCtl(uint32_t instance, cmt_iro_ctl_t ctlVal);

/*!
 * @brief Read the states of IRO latch.
 * 
 *
 * @param base Base address for current CMT instance.
 * @return The states of the IRO latch
 */
bool CMT_DRV_GetIrolatchState(uint32_t instance);


/* @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/
 
#endif /* __FSL_CMT_DRIVER_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

