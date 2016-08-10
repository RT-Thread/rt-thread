/*
 * Copyright (c) 2014 - 2015, Freescale Semiconductor, Inc.
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

#ifndef __FSL_SMARTCARD_DRIVER_H__
#define __FSL_SMARTCARD_DRIVER_H__

#include <stdint.h>
#include <stdbool.h>
#include "fsl_os_abstraction.h"
#include "fsl_device_registers.h"
#if defined(FSL_FEATURE_DMA_DMAMUX_CHANNELS)
#include "fsl_dma_driver.h"
#endif
#if defined(FSL_FEATURE_EDMA_MODULE_CHANNEL)
#include "fsl_edma_driver.h"
#endif

/*!
 * @addtogroup smartcard_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define HW_SMARTCARD_INTERFACE_COUNT            (1)
#define HW_SMARTCARD_INTERFACE_SLOT_COUNT       (1)

#if defined(FSL_FEATURE_UART_HAS_SMART_CARD_SUPPORT)
#if (FSL_FEATURE_UART_HAS_SMART_CARD_SUPPORT == 1)
#define HW_SMARTCARD_INSTANCE_COUNT  UART_INSTANCE_COUNT
#endif
#elif defined(FSL_FEATURE_SOC_EMVSIM_COUNT)
#define HW_SMARTCARD_INSTANCE_COUNT  FSL_FEATURE_SOC_EMVSIM_COUNT
#else
    #error "No valid Smart Card Module defined!"
#endif

#define INIT_DELAY_CLOCK_CYCLES         (42000)
#define EMV_ATR_DURATION_ETU            (20160 - 10)   

/*! @brief Error codes for the Smart card driver. */
typedef enum _smartcard_status
{
    kStatus_SMARTCARD_Success                  = 0x0U, 
    kStatus_SMARTCARD_TxBusy                   = 0x1U, 
    kStatus_SMARTCARD_RxBusy                   = 0x2U,  
    kStatus_SMARTCARD_NoTransmitInProgress     = 0x3U,
    kStatus_SMARTCARD_NoReceiveInProgress      = 0x4U, 
    kStatus_SMARTCARD_Timeout                  = 0x5U,
    kStatus_SMARTCARD_Initialized              = 0x6U,
    kStatus_SMARTCARD_PhyInitialized           = 0x7U,
    kStatus_SMARTCARD_DmaNotInitialized        = 0x8U,
    kStatus_SMARTCARD_OtherError               = 0x9U
} smartcard_status_t;

/*! @brief Control codes for the Smart card protocol timers and misc. */
typedef enum _smartcard_control
{
    kSmartcardEnableADT                      = 0x0U,
    kSmartcardDisableADT                     = 0x1U,
    kSmartcardEnableGTV                      = 0x2U,
    kSmartcardDisableGTV                     = 0x3U,
    kSmartcardResetWWT                       = 0x4U,
    kSmartcardEnableWWT                      = 0x5U,
    kSmartcardDisableWWT                     = 0x6U,
    kSmartcardResetCWT                       = 0x7U,
    kSmartcardEnableCWT                      = 0x8U,
    kSmartcardDisableCWT                     = 0x9U,
    kSmartcardResetBWT                       = 0xAU,
    kSmartcardEnableBWT                      = 0xBU,
    kSmartcardDisableBWT                     = 0xCU,
    kSmartcardEnableInitDetect               = 0xDU,
    kSmartcardEnableAnack                    = 0xEU,
    kSmartcardDisableAnack                   = 0xFU,
    kSmartcardConfigureBaudrate              = 0x10U,
    kSmartcardSetupATRMode                   = 0x11U,
    kSmartcardSetupT0Mode                    = 0x12U,
    kSmartcardSetupT1Mode                    = 0x13U,
    kSmartcardEnableReceiverMode             = 0x14U,
    kSmartcardDisableReceiverMode            = 0x15U,
    kSmartcardEnableTransmitterMode          = 0x16U,
    kSmartcardDisableTransmitterMode         = 0x17U,
    kSmartcardResetWaitTimeMultiplier        = 0x18U,
} smartcard_control_t;

/*! @brief Smart card interface interrupt callback function type */
typedef void (* smartcard_interface_callback_t)(uint32_t instance, void * smartcardState);

/*! @brief Defines Smart card interface voltage class values */
typedef enum _smartcard_card_voltage_class
{
    kSmartcardVoltageClassUnknown              = 0x0U,
    kSmartcardVoltageClassA5_0V                = 0x1U,
    kSmartcardVoltageClassB3_3V                = 0x2U,
    kSmartcardVoltageClassC1_8V                = 0x3U
}smartcard_card_voltage_class_t;

/*! @brief Defines Smart card I/O transfer states */
typedef enum _smartcard_transfer_state
{
    kSmartcardIdleState                 = 0x0U,
    kSmartcardWaitingForTSState         = 0x1U, 
    kSmartcardInvalidTSDetecetedState   = 0x2U,  
    kSmartcardReceivingState            = 0x3U,
    kSmartcardTransmittingState         = 0x4U,
}smartcard_transfer_state_t;

/*! @brief Defines Smart card reset types */
typedef enum _smartcard_reset_type
{
    kSmartcardColdReset                      = 0x0U,
    kSmartcardWarmReset                      = 0x1U,
    kSmartcardNoColdReset                    = 0x2U,
    kSmartcardNoWarmReset                    = 0x3U,
}smartcard_reset_type_t;

/*! @brief Defines Smart card transport protocol types */
typedef enum _smartcard_transport_type
{
    kSmartcardT0Transport                    = 0x0U,
    kSmartcardT1Transport                    = 0x1U
}smartcard_transport_type_t;

/*! @brief Defines Smart card data parity types */
typedef enum _smartcard_parity_type
{
    kSmartcardEvenParity                       = 0x0U,
    kSmartcardOddParity                        = 0x1U
}smartcard_parity_type_t;

/*! @brief Defines data transfer mode: CPU or DMA */
typedef enum _smartcard_xfer_mode
{
    kSmartcardCPUXferMode                      = 0x0U,
    kSmartcardDMAXferMode                      = 0x1U
}smartcard_xfer_mode_t;

/*! @brief Defines data convention format */
typedef enum _smartcard_card_convention
{
    kSmartcardDirectConvention                 = 0x0U,
    kSmartcardInverseConvention
}smartcard_card_convention_t;

/*! @brief Defines card-specific parameters for Smart card driver */
typedef struct CardParams {
    smartcard_card_voltage_class_t vcc;     /*!< Indicates current voltage class of the operation */
    bool atrComplete;                       /*!< Indicates whether the ATR received from the card was complete or not */
    bool atrValid;                          /*!< Indicates whether the ATR received from the card was valid or not */
    uint16_t Fi;                            /*!< 4 bits Fi */
    uint8_t fMax;                           /*!< Maximum Smart card frequency in MHz */
    uint8_t WI;                             /*!< 8 bits WI - work wait time integer */
    uint8_t Di;                             /*!< 4 bits DI - baud rate divisor */
    uint8_t BWI;                            /*!< 4 bits BWI - block wait time integer */
    uint8_t CWI;                            /*!< 4 bits CWI - character wait time integer */
    uint8_t BGI;                            /*!< 4 bits BGI - block guard time integer */
    uint8_t GTN;                            /*!< 8 bits GTN - extended guard time integer */
    bool t0Indicated;                       /*!< Indicates ff T=0 indicated in TD1 byte */
    bool t1Indicated;                       /*!< Indicates if T=1 indicated in TD2 byte */
    uint8_t IFSC;                           /*!< Indicates IFSC value of the card */
    uint8_t modeNegotiable;                 /*!< Indicates if the card acts in a negotiable or specific mode. */
    uint8_t currentD;                       /*!< 4 bits DI - current baud rate divisor*/
    smartcard_card_convention_t convention; /*!< Card convention, kSmartcardDirectConvention for direct convention, 
                                                 kSmartcardInverseConvention for inverse convention */
}smartcard_card_params_t;

/*! @brief Defines the state of the EMV timers in the Smart card driver */
typedef struct TimersState
{
    volatile bool adtExpired;   /*!< Indicates whether ADT timer expired */
    volatile bool wwtExpired;   /*!< Indicates whether WWT timer expired */
    volatile bool cwtExpired;   /*!< Indicates whether CWT timer expired */
    volatile bool bwtExpired;   /*!< Indicates whether BWT timer expired */
    volatile bool initCharTimerExpired;/*!< Indicates whether reception timer for initialization character (TS) after the RST has expired */
}smartcard_timers_state_t;

/*! @brief Defines state of user specified configuration of Smart card interface */
typedef struct SmartcardExtTimerConfig
{
    uint32_t tsTimerId;        /*!< Numerical identifier of the hardware timer for initial character detection */
}smartcard_ext_timer_config_t;

/*! @brief Defines state of user specified configuration of Smart card interface */
typedef struct InterfaceConfig
{
    uint32_t interfaceInstance;        /*!< Smart card interface IC no w.r.t. the board */
    uint32_t cardSoltNo;                /*!< Smart card slot number w.r.t. the interface IC */
    uint32_t sCClock;                   /*!< Smart card interface clock */
    uint8_t clockModuleInstance;        /*!< Smart card clock module instance number */
    uint8_t clockModuleChannel;         /*!< Smart card clock module channel number */
    uint8_t controlPort;                /*!< Smart card PHY control port instance */
    uint8_t controlPin;                 /*!< Smart card PHY control pin instance */
    uint8_t irqPort;                    /*!< Smart card PHY Interrupt port instance */
    uint8_t irqPin;                     /*!< Smart card PHY Interrupt pin instance */
    uint8_t resetPort;                  /*!< Smart card reset port instance */
    uint8_t resetPin;                   /*!< Smart card reset pin instance */
    uint8_t vsel0Port;                  /*!< Smart card PHY Vsel0 control port instance */
    uint8_t vsel0Pin;                   /*!< Smart card PHY Vsel0 control pin instance */
    uint8_t vsel1Port;                  /*!< Smart card PHY Vsel1 control port instance */
    uint8_t vsel1Pin;                   /*!< Smart card PHY Vsel1 control pin instance */
}smartcard_interface_config_t;

/*! @brief Defines state of Smart card interface slots */
typedef struct InterfaceState
{
    void *state;                                        /*!< Smart card interface state pointer */     
    void *slot[HW_SMARTCARD_INTERFACE_SLOT_COUNT];      /*!< Smart card interface card slots state pointers */
} smartcard_interface_state_t;

/*!
 * @brief Runtime state of the Smart card driver.
 *
 */
typedef struct SmartcardState {
    uint8_t txFifoEntryCount;      /*!< Number of data word entries in transmit FIFO. */
    const uint8_t * txBuff;        /*!< The buffer of data being sent.*/
    uint8_t * rxBuff;              /*!< The buffer of received data. */
    volatile size_t txSize;        /*!< The remaining number of bytes to be transmitted. */
    volatile size_t rxSize;        /*!< The remaining number of bytes to be received. */
    volatile bool isTxBusy;        /*!< True if there is an active transmit. */
    volatile bool isRxBusy;        /*!< True if there is an active receive. */
    volatile bool isTxBlocking;    /*!< True if transmit is blocking transaction. */
    volatile bool isRxBlocking;    /*!< True if receive is blocking transaction. */
    volatile bool bwtActive;       /*!< True if Global Counter 1 is set to wait for min. time before sending data (BWT) */
    semaphore_t txIrqSync;         /*!< Used to wait for ISR to complete its transmit. */
    semaphore_t rxIrqSync;         /*!< Used to wait for ISR to complete its receive. */
#if defined(FSL_FEATURE_EDMA_MODULE_CHANNEL)
    edma_chn_state_t txDmaState; /*!< Structure definition for the eDMA channel */
    edma_chn_state_t rxDmaState; /*!< Structure definition for the eDMA channel */
#endif
#if defined(FSL_FEATURE_DMA_DMAMUX_CHANNELS)
    dma_channel_t txDmaState; /*!< Structure definition for the DMA channel */
    dma_channel_t rxDmaState; /*!< Structure definition for the DMA channel */
#endif    
    smartcard_interface_callback_t interfaceCallback; /*!< Callback to invoke after interface IC raised interrupt.*/
    void * interfaceCallbackParam;        /*!< Interface callback parameter pointer.*/
    uint32_t sCClock;              /*!< Smart card clock set in Hz */    
    smartcard_transport_type_t tType;        /*!< Transfer type */
    bool useDMA;       /*!< Indicates whether to use DMA mode */
    smartcard_reset_type_t resetType;    /*!< Indicates whether a Cold reset or Warm reset was requested. */
    smartcard_transfer_state_t transState;   /*!< Indicates the current transfer state */
    uint8_t IFSD;         /*!< Indicates IFSD value of the terminal */ 
    smartcard_parity_type_t parity;       /*!< Indicates current parity even/odd */ 
    volatile bool rxtCrossed;     /*!< Indicates whether RXT thresholds has been crossed */
    volatile bool txtCrossed;     /*!< Indicates whether TXT thresholds has been crossed */
    volatile bool wtxRequested;   /*!< Indicates whether WTX has been requested or not*/
    volatile bool parityError;     /*!< Indicates whether a parity error has been detected */
    uint8_t statusBytes[2]; /*!< Used to store Status bytes SW1, SW2 of the last executed card command response */
    smartcard_interface_state_t *interfaceState;    /*!< Holds a pointer to the working state of the Interface IC */ 
    smartcard_interface_config_t interfaceConfig ;     /*!< Indicates the card slot number of the interface IC */
    smartcard_ext_timer_config_t extTimerConfig; /*!< Indicates the id of TS detection and ATR timers */
    smartcard_timers_state_t timersState; /*!< Indicates the state of different protocol timers used in driver */
    smartcard_card_params_t cardParams;    /*!< Indicates the card parameters (ATR and current) */
} smartcard_state_t;

/*!
 * @brief User configuration structure for the Smart card driver.
 *
 * Use an instance of this structure with the SMARTCARD_DRV_Init()function. This enables configuration of the
 * most common settings of the UART peripheral with a single function call. Settings include:
 * Smart card clock, Smart card interface configuration: interface instance no, slot no; 
 * Smart card operating voltage request: 1.8V, 3.3V, 5V.
 */
typedef struct SmartcardUserConfig {
    uint32_t sCClock;                   /*!< Smart card Clock set in Hz */
    smartcard_xfer_mode_t xferMode;     /*!< Smart card driver transfer mode */
    smartcard_interface_config_t interfaceConfig;       /*!< Smart card interface configuration */
    smartcard_ext_timer_config_t extTimerConfig; /*!< Indicates the id of TS detection and ATR timers */
    smartcard_card_voltage_class_t vcc;  /*!< Smart card requested operating voltage */
} smartcard_user_config_t;

/*!
 * @brief Smart card driver interface, which holds function pointers for implementation-specific functions.
 *
 * Use an instance of this structure initialized with implementation specific driver functions.
 * 
 */
typedef struct SmartcardDriverInterface {
    smartcard_status_t (* smartcardDrvInit)(uint32_t instance, 
                                smartcard_state_t * smartcardStatePtr,
                                const smartcard_user_config_t * smartcardUserConfig); /*!< Function pointer to 
                                Smart card implementation-specific initialization function */
    void (* smartcardDrvDeinit) (uint32_t instance);             /*!< Function pointer to 
                                Smart card implementation-specific de-initialization function */
    smartcard_status_t (* smartcardDrvSendDataBlocking) (uint32_t instance, 
                                        const uint8_t * txBuff,
                                        uint32_t txSize, 
                                        uint32_t timeout);      /*!< Function pointer to 
                                Smart card implementation-specific function to send data bytes 
                                in a blocking operation */
    smartcard_status_t (* smartcardDrvSendData) (uint32_t instance, 
                                     const uint8_t * txBuff, 
                                     uint32_t txSize);          /*!< Function pointer to 
                                Smart card implementation-specific function to send data bytes 
                                in a non-blocking operation */
    smartcard_status_t (* smartcardDrvGetTransmitStatus) (uint32_t instance, 
                                              uint32_t * bytesRemaining); /*!< Function pointer to 
                                Smart card implementation-specific function to get 
                                transmission status */
    smartcard_status_t (* smartcardDrvAbortSendingData) (uint32_t instance); /*!< Function pointer to 
                                Smart card implementation-specific function to abort
                                current transmission  */
    smartcard_status_t (* smartcardDrvReceiveDataBlocking) (uint32_t instance,
                                           uint8_t * rxBuff,
                                           uint32_t rxSize,
                                           uint32_t * rcvdSize,
                                           uint32_t timeout);           /*!< Function pointer to 
                                Smart card implementation-specific function to receive data in 
                                blocking operation */
    smartcard_status_t (* smartcardDrvReceiveData) (uint32_t instance, 
                                        uint8_t * rxBuff, 
                                        uint32_t rxSize);               /*!< Function pointer to 
                                Smart card implementation-specific function to receive data in 
                                non-blocking operation */
    smartcard_status_t (* smartcardDrvGetReceiveStatus) (uint32_t instance, 
                                             uint32_t * bytesRemaining);/*!< Function pointer to 
                                Smart card implementation specific function to get status of 
                                ongoing reception  */
    smartcard_status_t (* smartcardDrvAbortReceivingData) (uint32_t instance);  /*!< Function pointer to 
                                Smart card implementation specific function to abort 
                                ongoing reception */
    smartcard_status_t (* smartcardDrvControl)(uint32_t instance, 
                                         smartcard_control_t control, 
                                         void *controlBuff);            /*!< Function pointer to 
                                Smart card implementation-specific function to control different 
                                protocol parameters, and so on  */
    smartcard_status_t (* smartcardDrvInterfaceInit)(uint32_t interfaceInstance, 
                               smartcard_state_t * smartcardStatePtr,
                               const smartcard_interface_config_t * interfaceUserConfig);       /*!< Function pointer to 
                                Smart card implementation-specific physical interface initialization 
                                function */
    void (* smartcardDrvInterfaceDeInit)(uint32_t cardSoltNo);          /*!< Function pointer to 
                                Smart card implementation-specific physical interface de-initialization 
                                function */
    smartcard_interface_callback_t (* smartcardDrvInstallInterfaceCallback)(uint32_t interfaceInstance, 
                                        smartcard_interface_callback_t function, 
                                        void * callbackParam);          /*!< Function pointer to 
                                Smart card implementation-specific function to register a callback 
                                function to be called after physical interface device ISR is invoked */
    void (* smartcardDrvInterfaceActivate) (uint32_t interfaceInstance, 
                                      smartcard_reset_type_t resetType);               /*!< Function pointer to 
                                Smart card implementation-specific physical interface activation
                                function */
    void (* smartcardDrvInterfaceDeactivate) (uint32_t interfaceInstance);       /*!< Function pointer to 
                                Smart card implementation-specific physical interface deactivation
                                function */
    void (* smartcardDrvInterfaceControl) (uint32_t interfaceInstance,
                                           void * interfaceControlPtr,
                                           void * param);            /*!< Function pointer to 
                                Smart card implementation-specific function to read status information */
} smartcard_driver_interface_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Pointer to the UART runtime state structure.*/
extern void * g_smartcardStatePtr[HW_SMARTCARD_INSTANCE_COUNT];
extern void * g_smartcardInterfaceStatePtr[HW_SMARTCARD_INTERFACE_COUNT];
extern smartcard_driver_interface_t smartcardDrvInterface;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Installs the Smart card peripheral driver functions.
 *
 * @param smartcardDrvInterfacePtr Pointer to the Smart card composite driver structure of function pointers
 */
void SMARTCARD_DRV_InstallDriverFunctions(smartcard_driver_interface_t *smartcardDrvInterfacePtr);

/*!
 * @brief Installs the Smart card PHY/interface driver functions.
 *
 * @param smartcardDrvInterfacePtr Pointer to the Smart card composite driver structure of function pointers
 */
void SMARTCARD_DRV_InstallInterfaceFunctions(smartcard_driver_interface_t *smartcardDrvInterfacePtr);

/*!
 * @brief Initializes a Smart card instance for operation.
 *
 * This function initializes the run-time state structure to keep track of the on-going
 * transfers, un-gates the clock to the Smart card module, initializes the module
 * to user-defined settings and default settings, configures the IRQ state structure, and enables
 * the module-level interrupt to the core, and the Smart card module transmitter and receiver.
 *
 * @param instance The Smart card instance number.
 * @param smartcardStatePtr A pointer to the Smart card driver state structure memory. The user is only
 *  responsible to pass in the memory for this run-time state structure and the Smart card driver
 *  fills out the members. This run-time state structure keeps track of the
 *  current transfer in progress.
 * @param smartcardUserConfig The user configuration structure of type smartcard_user_config_t. The user
 *  is responsible to fill out the members of this structure and to pass the pointer of this structure
 *  into this function.
 * @return An error code or kStatus_SMARTCARD_Success.
 */
smartcard_status_t SMARTCARD_DRV_Init(uint32_t instance, 
                                      smartcard_state_t * smartcardStatePtr,
                                      const smartcard_user_config_t * smartcardUserConfig);

/*!
 * @brief Shuts down the Smart card by disabling interrupts and the transmitter/receiver.
 *
 * This function disables the Smart card interrupts, the transmitter and receiver, and
 * flushes the FIFOs (for modules that support FIFOs).
 *
 * @param instance The Smart card instance number.
 */
void SMARTCARD_DRV_Deinit(uint32_t instance);

/*!
 * @brief Sends (transmits) data out through the Smart card module using a blocking method.
 *
 * A blocking (also known as synchronous) function means that the function does not return until
 * the transmit is complete. This blocking function is used to send data through the Smart card port.
 *
 * @param instance The Smart card instance number.
 * @param txBuff A pointer to the source buffer containing 8-bit data chars to send.
 * @param txSize The number of bytes to send.
 * @param timeout A timeout value for RTOS abstraction sync control in milliseconds (ms).
 * @return An error code or kStatus_SMARTCARD_Success.
 */
smartcard_status_t SMARTCARD_DRV_SendDataBlocking(uint32_t instance,
                                      const uint8_t * txBuff,
                                      uint32_t txSize,
                                      uint32_t timeout);

/*!
 * @brief Sends (transmits) data through the Smart card module using a non-blocking method.
 *
 * A non-blocking (also known as synchronous) function means that the function returns
 * immediately after initiating the transmit function. The application has to get the
 * transmit status to see when the transmit is complete. In other words, after calling non-blocking
 * (asynchronous) send function, the application must get the transmit status to check if transmit
 * is complete.
 * The asynchronous method of transmitting and receiving allows the Smart card to perform a full duplex
 * operation (simultaneously transmit and receive).
 *
 * @param instance The Smart card module instance number.
 * @param txBuff A pointer to the source buffer containing 8-bit data chars to send.
 * @param txSize The number of bytes to send.
 * @return An error code or kStatus_SMARTCARD_Success.
 */
smartcard_status_t SMARTCARD_DRV_SendData(uint32_t instance,
                                      const uint8_t * txBuff,
                                      uint32_t txSize);

/*!
 * @brief Returns whether the previous Smart card transmit has finished.
 *
 * When performing an a-sync transmit, call this function to ascertain the state of the
 * current transmission: in progress (or busy) or complete (success). If the
 * transmission is still in progress, the user can obtain the number of words that have been
 * transferred.
 *
 * @param instance The Smart card module instance number.
 * @param bytesRemaining A pointer to a value that is filled in with the number of bytes that
 *                       are remaining in the active transfer.
 * @retval kStatus_SMARTCARD_Success The transmit has completed successfully.
 * @retval kStatus_SMARTCARD_TxBusy The transmit is still in progress. bytesTransmitted is
 *     filled with the number of bytes which are transmitted up to that point.
 */
smartcard_status_t SMARTCARD_DRV_GetTransmitStatus(uint32_t instance, 
                                      uint32_t * bytesRemaining);

/*!
 * @brief Terminates an asynchronous Smart card transmission early.
 *
 * During an a-sync Smart card transmission, the user can terminate the transmission early
 * if the transmission is still in progress.
 *
 * @param instance The Smart card module instance number.
 * @retval kStatus_SMARTCARD_Success The transmit was successful.
 * @retval kStatus_SMARTCARD_NoTransmitInProgress No transmission is currently in progress.
 */
smartcard_status_t SMARTCARD_DRV_AbortSendingData(uint32_t instance);

/*!
 * @brief Gets (receives) data from the Smart card module using a blocking method.
 *
 * A blocking (also known as synchronous) function means that the function does not return until
 * the receive is complete. This blocking function sends data through the UART port.
 *
 * @param instance The Smart card module instance number.
 * @param rxBuff A pointer to the buffer containing 8-bit read data chars received.
 * @param rxSize The number of bytes to receive.
 * @param rcvdSize The number of bytes actually received.
 * @param timeout A timeout value for RTOS abstraction sync control in milliseconds (ms).
 * @return An error code or kStatus_SMARTCARD_Success.
 */
smartcard_status_t SMARTCARD_DRV_ReceiveDataBlocking(uint32_t instance, 
                                      uint8_t * rxBuff,
                                      uint32_t rxSize, 
                                      uint32_t *rcvdSize,
                                      uint32_t timeout);

/*!
 * @brief Gets (receives) data from the Smart card module using a non-blocking method.
 *
 * A non-blocking (also known as synchronous) function means that the function returns
 * immediately after initiating the receive function. The application has to get the
 * receive status to see when the receive is complete. In other words, after calling non-blocking
 * (asynchronous) get function, the application must get the receive status to check if receive
 * is completed or not.
 * The asynchronous method of transmitting and receiving allows the UART to perform a full duplex
 * operation (simultaneously transmit and receive).
 *
 * @param instance The Smart card module instance number.
 * @param rxBuff  A pointer to the buffer containing 8-bit read data chars received.
 * @param rxSize The number of bytes to receive.
 * @return An error code or kStatus_SMARTCARD_Success.
 */
smartcard_status_t SMARTCARD_DRV_ReceiveData(uint32_t instance,
                                    uint8_t * rxBuff,
                                    uint32_t rxSize);

/*!
 * @brief Returns whether the previous Smart card receive is complete.
 *
 * When performing an a-sync receive, the user can call this function to ascertain the state of the
 * current receive progress: in progress (or busy) or complete (success). In addition, if the
 * receive is still in progress, the user can obtain the number of words that have been
 * currently received.
 *
 * @param instance The Smart card module instance number.
 * @param bytesRemaining A pointer to a value that is filled in with the number of bytes which
 *                       still need to be received in the active transfer.
 *
 * @retval kStatus_SMARTCARD_Success The receive has completed successfully.
 * @retval kStatus_SMARTCARD_RxBusy The receive is still in progress. @a bytesReceived is
 *     filled with the number of bytes which are received up to that point.
 */
smartcard_status_t SMARTCARD_DRV_GetReceiveStatus(uint32_t instance,
                                    uint32_t * bytesRemaining);

/*!
 * @brief Terminates an asynchronous Smart card receive early.
 *
 * During an a-sync UART receive, the user can terminate the receive early
 * if the receive is still in progress.
 *
 * @param instance The Smart card module instance number.
 *
 * @retval kStatus_SMARTCARD_Success Aborting the receive process was successful.
 * @retval kStatus_SMARTCARD_NoTransmitInProgress No receive is currently in progress.
 */
smartcard_status_t SMARTCARD_DRV_AbortReceivingData(uint32_t instance);

/*!
 * @brief Controls the Smart card modules per different user requests.
 *
 * @param instance The Smart card module instance number.
 * @param control control parameter.
 * @parma controlBuff A buffer pointer to be used along with control parameter
 *
 * @retval An error code as per operation execution.
 */
smartcard_status_t SMARTCARD_DRV_Control(uint32_t instance, 
                                    smartcard_control_t control, 
                                    void *controlBuff);

/*!
 * @brief Installs a user callback function to be called after any interface interrupt 
 * is serviced.
 *
 * @param instance The Smart card module instance number.
 * @param function Pointer to interface callback function.
 * @param callbackParam Pointer to interface callback function parameter.
 *
 * @retval Function pointer of the last installed callback function.
 */
smartcard_interface_callback_t SMARTCARD_DRV_InstallInterfaceCallback(uint32_t instance, 
                                    smartcard_interface_callback_t function, 
                                    void * callbackParam);

/*!
 * @brief Resets the Smart card interface/card slot for the given reset type.
 *
 * @param instance The Smart card module instance number.
 * @param resetType type of reset to be performed, possible values 
 *                       = kSmartcardColdReset, kSmartcardWarmReset
 *
 */
void SMARTCARD_DRV_Reset(uint32_t instance, smartcard_reset_type_t resetType);

/*!
 * @brief Deactivates the Smart card interface/card slot.
 *
 * @param instance The Smart card module instance number.
 *
 */
void SMARTCARD_DRV_Deactivate(uint32_t instance);

/*!
 * @brief Reads the status of card presence from the Smart card interface/card slot.
 *
 * @param instance The Smart card module instance number.
 * @param interfaceControl interface control type
 * @param param interface control parameter if any
 *
 */
void SMARTCARD_DRV_InterfaceControl(uint32_t instance, void *interfaceControl, void *param);
#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* __FSL_SMARTCARD_DRIVER_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

