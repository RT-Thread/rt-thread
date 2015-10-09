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

#ifndef __FSL_SMARTCARD_DIRECT_DRIVER_H__
#define __FSL_SMARTCARD_DIRECT_DRIVER_H__

#include <stdint.h>
#include <stdbool.h>
#include "fsl_os_abstraction.h"
#include "fsl_smartcard_driver.h"
#include "fsl_clock_manager.h"

/*!
 * @addtogroup smartcard_driver
 * @{
 */

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Definitions
 ******************************************************************************/ 
#define ATR_DURATION_ADJUSTMENT             (360)
#define INIT_DELAY_CLOCK_CYCLES_ADJUSTMENT  (4200)

/*! @brief SMARTCARD interface slot parameters, specific to interface IC */
typedef struct InterfaceSlotParams
{
  uint32_t clockToResetDelay;           /*!< Indicates clock to RST apply delay */
  smartcard_card_voltage_class_t vcc;   /*!< Indicates smart card voltage classes */
  bool present;                      /*!< Indicates if a smart card is present */
  bool active;                       /*!< Indicates if the smart card is activated */
} smartcard_interface_slot_t;

/*! @brief Defines interface IC control types */
typedef enum _smartcard_interface_control
{
    kSmartcardInterfaceSetVcc                  = 0x0U,
    kSmartcardInterfaceSetClockToResetDelay    = 0x01U,
    kSmartcardInterfaceReadStatus              = 0x02
}smartcard_interface_control_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializes an SMARTCARD interface instance for operation.
 *
 * @param interfaceInstance The SMARTCARD interface instance number.
 * @param smartcardStatePtr A pointer to the SMARTCARD driver state structure memory. The user is only
 *  responsible to pass in the memory for this run-time state structure where the SMARTCARD driver
 *  will take care of filling out the members.
 *
 * @param interfaceUserConfig The user configuration structure of type smartcard_interface_config_t. The user
 *  is responsible to fill out the members of this structure and to pass the pointer of this structure
 *  into this function.
 */
smartcard_status_t SMARTCARD_DRV_DirectInit(uint32_t interfaceInstance, 
                               smartcard_state_t * smartcardStatePtr,
                               const smartcard_interface_config_t * interfaceUserConfig);

/*!
 * @brief De-initializes an SMARTCARD interface instance for operation.
 *
 * @param instance smart card device instance number
 *
 */
void SMARTCARD_DRV_DirectDeInit(uint32_t instance);
  
/*!
 * @brief Installs a callback function for an SMARTCARD interface instance. The installed 
 * callback function should be called from the interrupt serive routine context of the interface
 * device.
 *
 * @param instance The SMARTCARD module instance number.
 * @param function Pointer to the interface callback function.
 * @param callbackParam Pointer to the interface callback function parameter.
 *
 * @retval Function pointer of the last installed callback function.
 */
smartcard_interface_callback_t SMARTCARD_DRV_DirectInstallCallback(uint32_t instance, 
                                              smartcard_interface_callback_t function, 
                                              void * callbackParam);

/*!
 * @brief Activates the SMARTCARD interface.
 *
 * @param instance The SMARTCARD module instance number.
 * @param resetType type of reset to be performed, possible values 
 *                       = kSmartcardColdReset, kSmartcardWarmReset
 *
 */
void SMARTCARD_DRV_DirectActivate(uint32_t instance, smartcard_reset_type_t resetType);

/*!
 * @brief De-activates the SMARTCARD interface.
 *
 * @param instance The SMARTCARD module instance number.
 * @param slot slot number.
 *
 */
void SMARTCARD_DRV_DirectDeactivate(uint32_t instance);

/*!
 * @brief Controls SMARTCARD interface IC.
 *
 * @param instance The SMARTCARD module instance number.
 * @param slot card slot numner.
 *
 */
void SMARTCARD_DRV_DirectControl(uint32_t instance, void *interfaceControl, void *param);
/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* __FSL_SMARTCARD_DIRECT_DRIVER_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

