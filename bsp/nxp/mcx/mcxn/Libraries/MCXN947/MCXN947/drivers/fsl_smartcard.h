/*
 * Copyright (c) 2015-2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_SMARTCARD_H_
#define _FSL_SMARTCARD_H_

#include "fsl_common.h"

/*!
 * @addtogroup smartcard
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief Smart card driver version 2.2.2.
 */
#define FSL_SMARTCARD_DRIVER_VERSION (MAKE_VERSION(2, 2, 2))
/*@}*/

/*! @brief Smart card global define which specify number of clock cycles until initial 'TS' character has to be received
 */
#define SMARTCARD_INIT_DELAY_CLOCK_CYCLES (42000u)

/*! @brief Smart card global define which specify number of clock cycles during which ATR string has to be received */
#define SMARTCARD_EMV_ATR_DURATION_ETU (20150u)

/*! @brief Smart card specification initial TS character definition of direct convention */
#define SMARTCARD_TS_DIRECT_CONVENTION (0x3Bu)

/*! @brief Smart card specification initial TS character definition of inverse convention */
#define SMARTCARD_TS_INVERSE_CONVENTION (0x3Fu)

/*! @brief Smart card Error codes. */
enum
{
    kStatus_SMARTCARD_Success              = MAKE_STATUS(kStatusGroup_SMARTCARD, 0), /*!< Transfer ends successfully */
    kStatus_SMARTCARD_TxBusy               = MAKE_STATUS(kStatusGroup_SMARTCARD, 1), /*!< Transmit in progress */
    kStatus_SMARTCARD_RxBusy               = MAKE_STATUS(kStatusGroup_SMARTCARD, 2), /*!< Receiving in progress */
    kStatus_SMARTCARD_NoTransferInProgress = MAKE_STATUS(kStatusGroup_SMARTCARD, 3), /*!< No transfer in progress */
    kStatus_SMARTCARD_Timeout              = MAKE_STATUS(kStatusGroup_SMARTCARD, 4), /*!< Transfer ends with time-out */
    kStatus_SMARTCARD_Initialized =
        MAKE_STATUS(kStatusGroup_SMARTCARD, 5), /*!< Smart card driver is already initialized */
    kStatus_SMARTCARD_PhyInitialized =
        MAKE_STATUS(kStatusGroup_SMARTCARD, 6), /*!< Smart card PHY drive is already  initialized */
    kStatus_SMARTCARD_CardNotActivated = MAKE_STATUS(kStatusGroup_SMARTCARD, 7), /*!< Smart card is not activated */
    kStatus_SMARTCARD_InvalidInput =
        MAKE_STATUS(kStatusGroup_SMARTCARD, 8), /*!< Function called with invalid input arguments */
    kStatus_SMARTCARD_OtherError = MAKE_STATUS(kStatusGroup_SMARTCARD, 9) /*!< Some other error occur */
};

/*! @brief Control codes for the Smart card protocol timers and misc. */
typedef enum _smartcard_control
{
    kSMARTCARD_EnableADT               = 0x0u,
    kSMARTCARD_DisableADT              = 0x1u,
    kSMARTCARD_EnableGTV               = 0x2u,
    kSMARTCARD_DisableGTV              = 0x3u,
    kSMARTCARD_ResetWWT                = 0x4u,
    kSMARTCARD_EnableWWT               = 0x5u,
    kSMARTCARD_DisableWWT              = 0x6u,
    kSMARTCARD_ResetCWT                = 0x7u,
    kSMARTCARD_EnableCWT               = 0x8u,
    kSMARTCARD_DisableCWT              = 0x9u,
    kSMARTCARD_ResetBWT                = 0xAu,
    kSMARTCARD_EnableBWT               = 0xBu,
    kSMARTCARD_DisableBWT              = 0xCu,
    kSMARTCARD_EnableInitDetect        = 0xDu,
    kSMARTCARD_EnableAnack             = 0xEu,
    kSMARTCARD_DisableAnack            = 0xFu,
    kSMARTCARD_ConfigureBaudrate       = 0x10u,
    kSMARTCARD_SetupATRMode            = 0x11u,
    kSMARTCARD_SetupT0Mode             = 0x12u,
    kSMARTCARD_SetupT1Mode             = 0x13u,
    kSMARTCARD_EnableReceiverMode      = 0x14u,
    kSMARTCARD_DisableReceiverMode     = 0x15u,
    kSMARTCARD_EnableTransmitterMode   = 0x16u,
    kSMARTCARD_DisableTransmitterMode  = 0x17u,
    kSMARTCARD_ResetWaitTimeMultiplier = 0x18u,
} smartcard_control_t;

/*! @brief Defines Smart card interface voltage class values */
typedef enum _smartcard_card_voltage_class
{
    kSMARTCARD_VoltageClassUnknown = 0x0u,
    kSMARTCARD_VoltageClassA5_0V   = 0x1u,
    kSMARTCARD_VoltageClassB3_3V   = 0x2u,
    kSMARTCARD_VoltageClassC1_8V   = 0x3u
} smartcard_card_voltage_class_t;

/*! @brief Defines Smart card I/O transfer states */
typedef enum _smartcard_transfer_state
{
    kSMARTCARD_IdleState               = 0x0u,
    kSMARTCARD_WaitingForTSState       = 0x1u,
    kSMARTCARD_InvalidTSDetecetedState = 0x2u,
    kSMARTCARD_ReceivingState          = 0x3u,
    kSMARTCARD_TransmittingState       = 0x4u,
} smartcard_transfer_state_t;

/*! @brief Defines Smart card reset types */
typedef enum _smartcard_reset_type
{
    kSMARTCARD_ColdReset   = 0x0u,
    kSMARTCARD_WarmReset   = 0x1u,
    kSMARTCARD_NoColdReset = 0x2u,
    kSMARTCARD_NoWarmReset = 0x3u,
} smartcard_reset_type_t;

/*! @brief Defines Smart card transport protocol types */
typedef enum _smartcard_transport_type
{
    kSMARTCARD_T0Transport = 0x0u,
    kSMARTCARD_T1Transport = 0x1u
} smartcard_transport_type_t;

/*! @brief Defines Smart card data parity types */
typedef enum _smartcard_parity_type
{
    kSMARTCARD_EvenParity = 0x0u,
    kSMARTCARD_OddParity  = 0x1u
} smartcard_parity_type_t;

/*! @brief Defines data Convention format */
typedef enum _smartcard_card_convention
{
    kSMARTCARD_DirectConvention  = 0x0u,
    kSMARTCARD_InverseConvention = 0x1u
} smartcard_card_convention_t;

/*! @brief Defines Smart card interface IC control types */
typedef enum _smartcard_interface_control
{
    kSMARTCARD_InterfaceSetVcc               = 0x00u,
    kSMARTCARD_InterfaceSetClockToResetDelay = 0x01u,
    kSMARTCARD_InterfaceReadStatus           = 0x02u
} smartcard_interface_control_t;

/*! @brief Defines transfer direction.*/
typedef enum _smartcard_direction
{
    kSMARTCARD_Receive  = 0u,
    kSMARTCARD_Transmit = 1u
} smartcard_direction_t;

/*! @brief Smart card interface interrupt callback function type */
typedef void (*smartcard_interface_callback_t)(void *smartcardContext, void *param);
/*! @brief Smart card transfer interrupt callback function type */
typedef void (*smartcard_transfer_callback_t)(void *smartcardContext, void *param);

/*! @brief Time Delay function used to passive waiting using RTOS [us] */
typedef void (*smartcard_time_delay_t)(uint32_t us);

/*! @brief Defines card-specific parameters for Smart card driver */
typedef struct _smartcard_card_params
{
    /* ISO7816/EMV4.3 specification variables */
    uint16_t Fi;            /*!< 4 bits Fi - clock rate conversion integer */
    uint8_t fMax;           /*!< Maximum Smart card frequency in MHz */
    uint8_t WI;             /*!< 8 bits WI - work wait time integer */
    uint8_t Di;             /*!< 4 bits DI - baud rate divisor */
    uint8_t BWI;            /*!< 4 bits BWI - block wait time integer */
    uint8_t CWI;            /*!< 4 bits CWI - character wait time integer */
    uint8_t BGI;            /*!< 4 bits BGI - block guard time integer */
    uint8_t GTN;            /*!< 8 bits GTN - extended guard time integer */
    uint8_t IFSC;           /*!< Indicates IFSC value of the card */
    uint8_t modeNegotiable; /*!< Indicates if the card acts in negotiable or a specific mode. */
    uint8_t currentD;       /*!< 4 bits DI - current baud rate divisor*/
    /* Driver-specific variables */
    uint8_t status;                         /*!< Indicates smart card status */
    bool t0Indicated;                       /*!< Indicates ff T=0 indicated in TD1 byte */
    bool t1Indicated;                       /*!< Indicates if T=1 indicated in TD2 byte */
    bool atrComplete;                       /*!< Indicates whether the ATR received from the card was complete or not */
    bool atrValid;                          /*!< Indicates whether the ATR received from the card was valid or not */
    bool present;                           /*!< Indicates if a smart card is present */
    bool active;                            /*!< Indicates if the smart card is activated */
    bool faulty;                            /*!< Indicates whether smart card/interface is faulty */
    smartcard_card_convention_t convention; /*!< Card convention, kSMARTCARD_DirectConvention for direct convention,
                                                 kSMARTCARD_InverseConvention for inverse convention */
} smartcard_card_params_t;

/*! @brief Smart card defines the state of the EMV timers in the Smart card driver */
typedef struct _smartcard_timers_state
{
    volatile bool adtExpired;           /*!< Indicates whether ADT timer expired */
    volatile bool wwtExpired;           /*!< Indicates whether WWT timer expired */
    volatile bool cwtExpired;           /*!< Indicates whether CWT timer expired */
    volatile bool bwtExpired;           /*!< Indicates whether BWT timer expired */
    volatile bool initCharTimerExpired; /*!< Indicates whether reception timer
                for initialization character (TS) after the RST has expired */
} smartcard_timers_state_t;

/*! @brief Defines user specified configuration of Smart card interface */
typedef struct _smartcard_interface_config
{
    uint32_t smartCardClock;            /*!< Smart card interface clock [Hz] */
    uint32_t clockToResetDelay;         /*!< Indicates clock to RST apply delay [smart card clock cycles] */
    uint8_t clockModule;                /*!< Smart card clock module number */
    uint8_t clockModuleChannel;         /*!< Smart card clock module channel number */
    uint8_t clockModuleSourceClock;     /*!< Smart card clock module source clock [e.g., BusClk] */
    smartcard_card_voltage_class_t vcc; /*!< Smart card voltage class */
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
    uint8_t dataPort;                   /*!< Smart card PHY data port instance */
    uint8_t dataPin;                    /*!< Smart card PHY data pin instance */
    uint8_t dataPinMux;                 /*!< Smart card PHY data pin mux option */
    uint8_t tsTimerId; /*!< Numerical identifier of the External HW timer for Initial character detection */
} smartcard_interface_config_t;

/*! @brief Defines user transfer structure used to initialize transfer */
typedef struct _smartcard_xfer
{
    smartcard_direction_t direction; /*!< Direction of communication. (RX/TX) */
    uint8_t *buff;                   /*!< The buffer of data. */
    size_t size;                     /*!< The number of transferred units. */
} smartcard_xfer_t;

/*!
 * @brief Runtime state of the Smart card driver.
 */
typedef struct _smartcard_context
{
    /* Xfer part */
    void *base;                      /*!< Smart card module base address */
    smartcard_direction_t direction; /*!< Direction of communication. (RX/TX) */
    uint8_t *xBuff;                  /*!< The buffer of data being transferred.*/
    volatile size_t xSize;           /*!< The number of bytes to be transferred. */
    volatile bool xIsBusy;           /*!< True if there is an active transfer. */
    uint8_t txFifoEntryCount;        /*!< Number of data word entries in transmit FIFO. */
    uint8_t rxFifoThreshold;         /*!< The max value of the receiver FIFO threshold. */
    /* Smart card Interface part */
    smartcard_interface_callback_t interfaceCallback; /*!< Callback to invoke after interface IC raised interrupt.*/
    smartcard_transfer_callback_t transferCallback;   /*!< Callback to invoke after transfer event occur.*/
    void *interfaceCallbackParam;                     /*!< Interface callback parameter pointer.*/
    void *transferCallbackParam;                      /*!< Transfer callback parameter pointer.*/
    smartcard_time_delay_t timeDelay;                 /*!< Function which handles time delay defined by user or RTOS. */
    smartcard_reset_type_t resetType; /*!< Indicates whether a Cold reset or Warm reset was requested. */
    smartcard_transport_type_t tType; /*!< Indicates current transfer protocol (T0 or T1) */
    /* Smart card State part */
    volatile smartcard_transfer_state_t transferState; /*!< Indicates the current transfer state */
    smartcard_timers_state_t timersState; /*!< Indicates the state of different protocol timers used in driver */
    smartcard_card_params_t
        cardParams; /*!< Smart card parameters(ATR and current) and interface slots states(ATR and current) */
    uint8_t IFSD;   /*!< Indicates the terminal IFSD */
    smartcard_parity_type_t parity; /*!< Indicates current parity even/odd */
    volatile bool rxtCrossed;       /*!< Indicates whether RXT thresholds has been crossed */
    volatile bool txtCrossed;       /*!< Indicates whether TXT thresholds has been crossed */
    volatile bool wtxRequested;     /*!< Indicates whether WTX has been requested or not*/
    volatile bool parityError;      /*!< Indicates whether a parity error has been detected */
    uint8_t statusBytes[2]; /*!< Used to store Status bytes SW1, SW2 of the last executed card command response */
    /* Configuration part */
    smartcard_interface_config_t interfaceConfig; /*!< Smart card interface configuration structure */
    bool abortTransfer;                           /*!< Used to abort transfer. */
} smartcard_context_t;

/*! @}*/
#endif /* _FSL_SMARTCARD_H_*/
