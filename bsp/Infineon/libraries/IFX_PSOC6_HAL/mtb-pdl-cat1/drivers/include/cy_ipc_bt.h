/***************************************************************************//**
* \file cy_ipc_bt.h
* \version 1.80
*
* \brief
* Provides an API declaration for the BT IPC driver.
*
********************************************************************************
* \copyright
* Copyright (c) (2020-2022), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#ifndef CY_IPC_BT_H
#define CY_IPC_BT_H

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/

#include "cy_device.h"

#if defined (CY_IP_MXIPC)

#include "cy_ipc_drv.h"
#include "cy_syslib.h"
#include "cy_sysint.h"

/**
* \addtogroup group_ipc_bt IPC Bluetooth sub-system layer (IPC_BTSS)
* \{
* All the HCI APIs are intended to be called by the stack interface layer, and
* not meant to be called by the application developers.
*
* The BT IPC functions provide a method to transfer Host Controller Interface (HCI)
* and High Priority Controller (HPC) messages between the MCU and BT SS.
*
* Include cy_ipc_bt.h. Alternatively include cy_pdl.h
* to get access to all functions and declarations in the PDL.
*
* The data needs to be provided in an array along with the payload type indicator.
* Depending on the payload length, the message gets formatted in to short or long
* message. If the payload length is less than 7 bytes, then it is considered as a short
* message. Short messages are packed and sent using IPC channel DATA0 and DATA1
* registers. Any payload length greater than 7 bytes will be sent using the buffers in
* the shared memory.
*
* It supports callback function for notification on receiving the HCI messages from the BT SS
* HCI notification callback function is registered during the initialization of the driver.
* It also supports multiple callback registration for notification on receiving the
* HPC messages.
*
*     \defgroup group_ipc_bt_macros Macros
*       Macro definitions are used in the driver
*
*     \defgroup group_ipc_bt_functions Functions
*       Functions are used in the driver
*
*     \defgroup group_ipc_bt_data_structures Data Structures
*       Data structures are used in the driver
*
*     \defgroup group_ipc_bt_enums Enumerated Types
*       Enumerations are used in the driver
* \}
*
*/

//#define BT_OLD_INIT
/* Enable below macro to get BT IPC statistics */
#define CY_BTIPC_STATS

/**
* \addtogroup group_ipc_bt_macros
* \{
*/

/** Software PDL driver ID for IPC BT  functions */
#define CY_BT_IPC_ID CY_IPC_ID

/** Return prefix for BT IPC driver function status codes */
#define CY_BT_IPC_ID_INFO    (uint32_t)( CY_BT_IPC_ID | CY_PDL_STATUS_INFO )

/** Return prefix for BT IPC driver function warning return values */
#define CY_BT_IPC_ID_WARNING (uint32_t)( CY_BT_IPC_ID | CY_PDL_STATUS_WARNING)

/** Return prefix for BT IPC driver function error return values */
#define CY_BT_IPC_ID_ERROR   (uint32_t)( CY_BT_IPC_ID | CY_PDL_STATUS_ERROR)

/** Maximum HPC callback supported */
#define MAX_BT_IPC_HPC_CB 10

/** Maximum number of buffers in the pool */
#define MAX_BUF_COUNT 4

/** Maximum number of buffers to be released */
#define MAX_TO_FREE_BUF_COUNT 5

/** Maximum size of IPC FIFO */
#define MAX_IPC_FIFO_SIZE 5

/** \} group_ipc_bt_macros */


/** Maximum length of short message */
#define MAX_SHORT_MESG_LENGTH 7

/** Buffer descriptor length in init message */
#define BUFFER_DESCRIPTION_LEN 7

/** size of cy_stc_ipc_msg_subheader_t structure */
#define SUB_HEADER_SIZE 4

/**
* \addtogroup group_ipc_bt_enums
* \{
*/
/**
* This is a list of ENUMs used for function return status.
*/
typedef enum
{
    CY_BT_IPC_DRV_SUCCESS            =(uint32_t)(0x00u),                     /**<  BT IPC API return for no error */
    CY_BT_IPC_DRV_ERROR              =(uint32_t)(CY_BT_IPC_ID_ERROR | 1UL),  /**<  BT IPC API return for general error */
    CY_BT_IPC_DRV_ERROR_BAD_HANDLE   =(uint32_t)(CY_BT_IPC_ID_ERROR | 2UL),  /**<  BT IPC API return for bad handle */
    CY_BT_IPC_DRV_ERROR_CH_BUSY      =(uint32_t)(CY_BT_IPC_ID_ERROR | 3UL),  /**<  BT IPC API return for channel busy */
    CY_BT_IPC_DRV_ERROR_LOCK_REL     =(uint32_t)(CY_BT_IPC_ID_ERROR | 4UL),  /**<  BT IPCAPI return for channel release error */
    CY_BT_IPC_DRV_ERROR_LOCK_ACQUIRE =(uint32_t)(CY_BT_IPC_ID_ERROR | 5UL),  /**<  BT IPC API return for channel release error */
    CY_BT_IPC_DRV_ERROR_BUF_GET      =(uint32_t)(CY_BT_IPC_ID_ERROR | 6UL),  /**<  BT IPC API return for get buffer error */
    CY_BT_IPC_DRV_ERROR_BUF_FULL     =(uint32_t)(CY_BT_IPC_ID_ERROR | 7UL),  /**<  BT IPC API return for buffer full error */
    CY_BT_IPC_DRV_ERROR_BUF_EMPTY    =(uint32_t)(CY_BT_IPC_ID_ERROR | 8UL),  /**<  BT IPC API return for buffer empty error */
    CY_BT_IPC_DRV_ERROR_BUF_PRESENT  =(uint32_t)(CY_BT_IPC_ID_ERROR | 9UL),  /**<  BT IPC API return for buffer already present error */
    CY_BT_IPC_DRV_ERROR_BUF_SIZE     =(uint32_t)(CY_BT_IPC_ID_ERROR | 10UL), /**<  BT IPC API return for buffer of size not available error */
    CY_BT_IPC_DRV_ERROR_PARAM        =(uint32_t)(CY_BT_IPC_ID_ERROR | 11UL), /**<  BT IPC API return for bad parameter error */
} cy_en_btipcdrv_status_t;

/**
* This is a list of ENUMs used for buffer types.
*/
typedef enum
{
    CY_BT_IPC_CTRL_BUF           = (0x00u),                /**<  Control buffer type */
    CY_BT_IPC_HCI_CMD_BUF        = (0x01u),                /**<  Command buffer type */
    CY_BT_IPC_HCI_BREDR_BUF      = (0x02u),                /**<  BR/EDR buffer type */
    CY_BT_IPC_HCI_BLE_BUF        = (0x03u),                /**<  BLE buffer type */
    CY_BT_IPC_HCI_ISOC_BUF       = (0x04u),                /**<  ISOC buffer type */
    CY_BT_IPC_HCI_INVALID_BUF    = (0xFFu),                /**<  Invalid buffer type */
} cy_en_btipc_buftype_t;

/**
* This is a list of ENUMs used for HCI packet type.
*/
typedef enum
{
    CY_BT_IPC_HCI_IGNORE         = (0x00u),                /**<  HCI payload type ignore */
    CY_BT_IPC_HCI_CMD            = (0x01u),                /**<  HCI payload type command */
    CY_BT_IPC_HCI_ACL            = (0x02u),                /**<  HCI payload type ACL */
    CY_BT_IPC_HCI_SCO            = (0x03u),                /**<  HCI payload type SCO */
    CY_BT_IPC_HCI_EVT            = (0x04u),                /**<  HCI payload type Event */
    CY_BT_IPC_HCI_ISO            = (0x05u),                /**<  HCI payload type ISO */
    CY_BT_IPC_HCI_DIAG           = (0x07u),                /**<  HCI payload type Diagnostics */
    CY_BT_IPC_HCI_MPAF           = (0x0Au),                /**<  HCI payload type MPAF */
    CY_BT_IPC_HCI_SLIPH5         = (0xC0u),                /**<  HCI payload type SLIPH5 */
    CY_BT_IPC_HCI_LONG           = (0xFFu),                /**<  HCI payload type long message */
} cy_en_btipc_hcipti_t;

/**
* This is a list of ENUMs used for HPC packet type.
*/
typedef enum
{
    CY_BT_IPC_HPC_RESERVED       = (0x00u),                /**<..Reserved (not used) */
    CY_BT_IPC_HPC_BUFRELEASE     = (0x01u),                /**<  HPC payload type buffer release, sent from MCU only */
    CY_BT_IPC_HPC_REQTRNG        = (0x02u),                /**<  HPC payload type request TRNG */
    CY_BT_IPC_HPC_BUFPROVIDE     = (0x03u),                /**<  HPC payload type provide buffer, sent from BT only */
    CY_BT_IPC_HPC_PM             = (0x04u),                /**<  HPC payload type PM control */
    CY_BT_IPC_HPC_RESACCESS      = (0x05u),                /**<  HPC payload type Resource Access */
    CY_BT_IPC_HPC_LPO_SWITCH     = (0x06u),                /**<  HPC payload type LPO Clk switch */
    CY_BT_IPC_HPC_LONG           = (0xFFu),                /**<  HPC payload type long message */
} cy_en_btipc_hpcpti_t;

/**
* This is a list of ENUMs used for HPC long message type.
*/
typedef enum
{
    CY_BT_IPC_HPC_INIT           = (0x01u),                /**<..Init message */
    CY_BT_IPC_HPC_HADM           = (0x02u),                /**<  HADM data message from BTSS to MCU */
    CY_BT_IPC_HPC_DUMMY          = (0x10u),                /**<  DUMMY data message from MCU to BTSS */
} cy_en_btipc_hpcmsgid_t;

/**
* This is a list of ENUMs used for bt boot type.
*/
typedef enum
{
#ifdef BT_OLD_INIT
    CY_BT_IPC_COLD_BOOT                     = (0x00u),     /**<  BTSS was reset and is in colds boot */
#endif
    CY_BT_IPC_BOOT_CONFIG_WAIT              = (0x00u),     /**<  BTSS is reset and is in boot waiting for a config from the MCU. If certificate error indicates any error processing certificates */
    CY_BT_IPC_BOOT_FULLY_UP                 = (0x01u),     /**<  BTSS is fully up. It either processed a config from the MCU, or the MCU did not send a config. If the certificate error value is non-zero, there was an error processing certificates after getting the config, but the boot continued anyway. */
} cy_en_btipc_boottype_t;

/**
* This is a list of ENUMs used in PM command from MCU to BTSS
*/
typedef enum
{
    CY_BT_IPC_PM_HIBERNATE_CMD   = (0x01u),                /**< Command for Hibernate state */
} cy_en_btipc_pm_cmd_t;

/**
* This is a list of ENUMs used in PM response from BTSS to MCU
*/
typedef enum
{
    CY_BT_IPC_PM_ACCEPTED        = (0x00u),                /**< PM command accepted */
    CY_BT_IPC_PM_REJECTED        = (0x01u),                /**< PM command rejected */
} cy_en_btipc_pm_resp_t;

/**
*  This is a list of ENUMs used in resource access request from BTSS to MCU
*/
typedef enum
{
    CY_BT_IPC_RESACC_DI          = (0x00u),                /**< Resource access disable request */
    CY_BT_IPC_RESACC_EN          = (0x01u),                /**< Resource access enable request */
} cy_en_btipc_recacc_req_t;

/**
*  This is a list of ENUMs used as response from MCCU to BTSS for resource access request
*/
typedef enum
{
    CY_BT_IPC_RESACC_ACCEPTED    = (0x00u),                /**< Resource access request accepted */
    CY_BT_IPC_RESACC_REJECTED    = (0x01u),                /**< Resource access request rejected */
}cy_en_btipc_recacc_resp_t;

/**
*  This is a list of ENUMs used for LPO change indication from MCUSS to BTSS
*/
typedef enum
{
    CY_BT_IPC_LPO_PILO          = (0x00u),                /**< LPO clk type PILO */
    CY_BT_IPC_LPO_WCO           = (0x01u),                /**< LPO clk type WCO */
}cy_en_btipc_lpo_cmd_t;

/**
* This is a list of ENUMs used for HCI DAIG packet type.
*/
typedef enum
{
    CY_BT_IPC_HCI_DIAG_IN_PKT_ID_NOP                       = (0x00U),
    CY_BT_IPC_HCI_DIAG_IN_PKT_ID_ALIVE_IND                 = (0x02U),
    CY_BT_IPC_HCI_DIAG_IN_PKT_ID_CPU_LOAD                  = (0x10U),
    CY_BT_IPC_HCI_DIAG_IN_PKT_ID_RESET_STATS               = (0xB9U),
    CY_BT_IPC_HCI_DIAG_IN_PKT_ID_LMP_LOG                   = (0xF0U),
    CY_BT_IPC_HCI_DIAG_IN_PKT_ID_MEM_PEEK                  = (0xF1U),
    CY_BT_IPC_HCI_DIAG_IN_PKT_ID_MEM_POKE                  = (0xF2U),
    CY_BT_IPC_HCI_DIAG_IN_PKT_ID_MEM_HEXDUMP               = (0xF3U),
    CY_BT_IPC_HCI_DIAG_IN_PKT_ID_SEND_STATS                = (0xF4U),
    CY_BT_IPC_HCI_DIAG_IN_PKT_ID_BB_PKT_TEST               = (0xF6U),
    CY_BT_IPC_HCI_DIAG_IN_PKT_ID_PICO_TEST                 = (0xF7U),
    CY_BT_IPC_HCI_DIAG_IN_PKT_ID_HCI_LOG                   = (0xF8U),
    CY_BT_IPC_HCI_DIAG_IN_PKT_ID_PICO_STATS                = (0xF9U),
    CY_BT_IPC_HCI_DIAG_IN_PKT_ID_AUX_STATS                 = (0xFAU),
    CY_BT_IPC_HCI_DIAG_IN_PKT_ID_SEND_RSSI                 = (0xFBU),
    CY_BT_IPC_HCI_DIAG_IN_PKT_ID_BAD_EVENT_LOG             = (0xFCU),
    CY_BT_IPC_HCI_DIAG_IN_PKT_ID_READ_2040_GPIO            = (0xFDU),
    CY_BT_IPC_HCI_DIAG_IN_PKT_ID_SEND_BASIC_RATE_ACL_STATS = (0xC1U),
    CY_BT_IPC_HCI_DIAG_IN_PKT_ID_SEND_EDR_ACL_STATS        = (0xC2U),
    CY_BT_IPC_HCI_DIAG_IN_PKT_ID_2045_AUX_STATS            = (0xC3U),
    CY_BT_IPC_HCI_DIAG_IN_PKT_ID_SEND_BASIC_RATE_SCO_STATS = (0xC5U),
    CY_BT_IPC_HCI_DIAG_IN_PKT_ID_SEND_EDR_SCO_STATS        = (0xC6U),
    CY_BT_IPC_HCI_DIAG_IN_PKT_ID_BLE_CONN_STATS            = (0xCFU),
}cy_en_btipc_hci_diag_msg_type_t;


/** \} group_ipc_bt_enums */

/*
 * This section defines the system level constants required to define
 * callback arrays for the Cypress pipe and the user pipe.  These defines
 * are used for both the max callback count and maximum clients.
*/

/** Typedef for bt ipc  callback function pointer */
typedef void (* cy_ipc_bt_callback_ptr_t)(uint32_t * msgPtr);

/** Typedef for bt ipc channel release callback function pointer */
typedef void (* cy_ipc_bt_relcallback_ptr_t)(void);

/** Typedef for bt ipc buffer available callback function pointer */
typedef void (* cy_ipc_bt_bufcallback_ptr_t)(cy_en_btipc_buftype_t bufType);

/** Typedef for bt ipc irq function pointer */
typedef void (* cy_ipc_bt_irq_handler_t)(void);

/**
* \addtogroup group_ipc_bt_data_structures
* \{
*/

/**
* This is the definition of an allocation msg structure.
*/
typedef struct cy_stc_ipc_msg_alloc_t
{
    uint8_t pti;                                    /**< Payload type indicator */
    uint8_t bufType;                                /**< Buffer type indicator */
    uint16_t bufSize;                               /**< Buffer size */
    uint8_t *bufAddr;                               /**< Pointer to the buffer */
} cy_stc_ipc_msg_alloc_t;

/**
* This is the definition of a long message structure.
*/
typedef struct cy_stc_ipc_msg_buff_t
{
    uint8_t pti;                                    /**< Payload type indicator */
    uint8_t actualPti;                              /**< Actual PTI for the long messages */
    uint16_t bufSize;                               /**< Buffer size */
    uint8_t *bufAddr;                               /**< Pointer to the buffer */
} cy_stc_ipc_msg_buff_t;

/**
* This is the definition of a short msg structure.
*/
typedef struct cy_stc_ipc_msg_short_t
{
    uint8_t pti;                                    /**< Payload type indicator */
    uint8_t db0;                                    /**< Payload byte 0 for short message */
    uint8_t db1;                                    /**< Payload byte 1 for short message */
    uint8_t db2;                                    /**< Payload byte 2 for short message */
    uint8_t db3;                                    /**< Payload byte 3 for short message */
    uint8_t db4;                                    /**< Payload byte 4 for short message */
    uint8_t db5;                                    /**< Payload byte 5 for short message */
    uint8_t db6;                                    /**< Payload byte 6 for short message */
} cy_stc_ipc_msg_short_t;

/** \} group_ipc_bt_data_structures */

/**
* This is the definition of an init msg structure.
*/
#ifdef BT_OLD_INIT
typedef struct cy_stc_ipc_msg_init_t
#else
typedef __PACKED_STRUCT cy_stc_ipc_msg_init_t
#endif
{
    uint8_t msgId;                                  /**< Message ID for HPC Long message */
    uint8_t payLoadLen;                             /**< Payload length in bytes */
    uint8_t bootType;                               /**< BT boot type indicator */
#ifndef BT_OLD_INIT
    uint32_t certError;                             /**< Certificate error value */
#endif
} cy_stc_ipc_msg_init_t;

/**
* This is the definition of a sub header msg structure.
*/
typedef __PACKED_STRUCT cy_stc_ipc_msg_subheader_t
{
    uint8_t msgId;                                  /**< Message ID for HPC message */
    uint8_t dummy;                                  /**< Dummy byte to be ignored */
    uint16_t payLoadLen;                            /**< Payload length in bytes */
} cy_stc_ipc_msg_subheader_t;

/**
* This is the definition of buffer descriptor structure.
*/
typedef struct cy_stc_ipc_bt_buf_t
{
    cy_en_btipc_buftype_t bufType;                  /**< Buffer type indicator */
    uint16_t bufLen;                                /**< Buffer length */
    uint8_t *bufPtr;                                /**< Pointer to the buffer */
} cy_stc_ipc_bt_buf_t;

/**
* This is the definition of buffer descriptor optimized for context store/restore.
*/
typedef struct cy_stc_ipc_bt_ctxbuf_t
{
    uint16_t bufType;                               /**< Buffer type indicator */
    uint16_t bufLen;                                /**< Buffer length */
    uint8_t *bufPtr;                                /**< Pointer to the buffer */
} cy_stc_ipc_bt_ctxbuf_t;


/* Following are the HCI packet header typedefs */
/**
* This is the definition of CMD header structure.
*/
typedef __PACKED_STRUCT BTHCI_CMD_HDR_t
{
    uint16_t opcode;
    uint8_t params_len;
} BTHCI_CMD_HDR_t;

/**
* This is the definition of event header structure.
*/
typedef struct BTHCI_EVENT_HDR_t
{
    uint8_t   code; /**< code */
    uint8_t   params_len; /**< params_len */
} BTHCI_EVENT_HDR_t;

/**
* This is the definition of ACL header structure.
*/
typedef __PACKED_STRUCT BTHCI_ACL_HDR_t
{
    uint16_t  conn_handle_and_flags;
    uint16_t  data_len;
} BTHCI_ACL_HDR_t;

/**
* This is the definition of ISO header structure.
*/
typedef __PACKED_STRUCT BTHCI_ISO_HDR_t
{
    uint16_t  conn_handle_and_flags;
    uint16_t  data_len;
} BTHCI_ISO_HDR_t;

/**
* This is the definition of SCO header structure.
*/
typedef struct BTHCI_SCO_HDR_t
{
    __PACKED_UNION
    {
        uint16_t  audioChannel; /**< audioChannel */
        uint16_t  connectionHandle; /**< connectionHandle*/
    }   u; /**< u */
    uint8_t  data_len; /**< data_len */
} BTHCI_SCO_HDR_t;

/** Typedef for internal ipc callback function pointer */
typedef void (* cy_ipc_bt_int_cb_ptr_t)(void *btIpcContext, uint32_t * msgPtr);

/**
* This is the definition of IPC message.
*/
typedef struct cy_stc_ipc_msg_t
{
    uint32_t msg[2];                                /**< IPC message */
} cy_stc_ipc_msg_t;

/**
* This is the definition of fifo for IPC messages.
*/
typedef struct cy_stc_ipc_msg_fifo_t
{
    cy_stc_ipc_msg_t fifo[MAX_IPC_FIFO_SIZE];       /**< FIFO for IPC messages */
    uint8_t rdIdx;                                  /**< FIFO read index */
    uint8_t wrIdx;                                  /**< FIFO write index */
    uint8_t bufLen;                                 /**< Number of FIFO entries */
} cy_stc_ipc_msg_fifo_t;

/**
* \addtogroup group_ipc_bt_data_structures
* \{
*/

/**
* This is the definition of HPC callback structure.
*/
typedef struct cy_stc_ipc_hcp_cb_t
{
    cy_en_btipc_hpcpti_t msgType;                    /**< HPC Message Type */
    cy_ipc_bt_callback_ptr_t hpcNotifyCallbackPtr;   /**< HPC Callback pointer for control channel notification */
} cy_stc_ipc_hcp_cb_t;


/**
* This is the definition of BT IPC context structure.
*/
typedef struct cy_stc_ipc_bt_context_t
{
    uint32_t ulChannelHCI;                                    /**< HCI Channel used to send to BLE */
    uint32_t dlChannelHCI;                                    /**< HCI Channel used to receive from BLE */

    uint32_t ulChannelHPC;                                    /**< HPC Channel used to send to BLE */
    uint32_t dlChannelHPC;                                    /**< HPC Channel used to receive from BLE */

    uint32_t intStuctureSelf;                                 /**< Interrupt structure for the MCU */
    uint32_t intStucturePeer;                                 /**< Interrupt structure for the BLE */

    uint32_t intPeerMask;                                     /**< Interrupt mask for the peer */

    uint32_t dlNotifyMask;                                    /**< Down link notify mask */
    uint32_t ulReleaseMask;                                   /**< Up link release mask */

    cy_stc_sysint_t ipcIntConfig;                             /**< IPC Interrupt configuration structure */

    cy_ipc_bt_irq_handler_t irqHandlerPtr;                    /**< This handler will be removed later once simulations are done */

    cy_ipc_bt_int_cb_ptr_t internal_hpc_notify_cb;            /**< This callback will be removed later once simulations are done */

    cy_ipc_bt_callback_ptr_t dlNotifyCallbackPtr;             /**< Callback function called when the DL message is received */

    cy_ipc_bt_relcallback_ptr_t ulReleaseCallbackPtr;         /**< Callback function called when the UL channel is released */

    cy_ipc_bt_bufcallback_ptr_t bufCallbackPtr;               /**< Callback function called when there is a free buffer available */

    cy_stc_ipc_hcp_cb_t hpcNotifyCallbackParam[MAX_BT_IPC_HPC_CB]; /**< Array of callback pointers registered for control channel notification */

    cy_stc_ipc_bt_buf_t buffPool[MAX_BUF_COUNT];              /**< Storage for pool of buffers sent by BLE for communication */

    cy_stc_ipc_msg_fifo_t IpcFifo;                            /**< FIFO for HCI IPC messages sent by BLE for communication */

    cy_stc_ipc_bt_buf_t toFreeBuf[MAX_TO_FREE_BUF_COUNT];     /**< Array of buffer descriptor of HCI long buffer to be released is stored */

    uint32_t droppedHCI;                                      /**< Count of dropped HCI messages */
    uint8_t bootType;                                         /**< Boot type */
    uint32_t certError;                                       /**< Certificate processing error description */

#ifdef CY_BTIPC_STATS
    /* Following data is used for analyses */
    uint32_t ipc_int_count;                                   /**< Total number of IPC interrupts received */

    uint32_t ipc_hci_cmd_count;                               /**< Total number of HCI cmds received */
    uint32_t ipc_hci_release_count;                           /**< Total number of HCI release received */

    uint32_t ipc_hci_notify_count;                            /**< Total number of HCI notifications received */
    uint32_t ipc_hci_peer_release_count;                      /**< Total number of releases done to peer HCI channel */

    uint32_t ipc_hpc_cmd_count;                               /**< Total number of HPC cmds received */
    uint32_t ipc_hpc_release_count;                           /**< Total number of HPC notifications received */

    uint32_t ipc_hpc_notify_count;                            /**< Total number of HPC notifications received */
    uint32_t ipc_hpc_peer_release_count;                      /**< Total number of releases done to peer HPC channel */

    uint32_t ipc_hci_peer_inbuf_count;                        /**< Total number of HCI buffers received */
    uint32_t ipc_hci_peer_outbuf_count;                       /**< Total number of HCI buffers returned */

    uint32_t ipc_hpc_peer_inbuf_count;                        /**< Total number of HPC buffers received */
    uint32_t ipc_hpc_peer_outbuf_count;                       /**< Total number of HPC buffers returned */

    uint32_t ipc_hci_cmd_self_outbuf_count;                   /**< Total number of HCI cmd buffers pulled form pool */
    uint32_t ipc_hci_cmd_self_outbuf_success;                 /**< Total number of HCI cmd buffers sent to peer */
    uint32_t ipc_hci_cmd_self_inbuf_count;                    /**< Total number of HCI cmd buffers received back from peer */

    uint32_t ipc_hci_fifo_full;                               /**< Total FIFO full condition count */
    uint32_t ipc_hci_notify_in_fifo_full;                     /**< HCI Notify received during FIFO full condition */
#endif
} cy_stc_ipc_bt_context_t;

/**
* This is the definition of BT IPC context structure used to restore and retrieve during RAM off state.
*/
typedef struct cy_stc_ipc_bt_save_ctxt_t
{
    cy_stc_ipc_bt_ctxbuf_t buffPool[MAX_BUF_COUNT];              /**< Storage for pool of buffers sent by BLE for communication */
} cy_stc_ipc_bt_save_ctxt_t;

/**
* This is the definition of BT IPC configuration structure.
*/
typedef struct cy_stc_ipc_bt_config_t
{
    uint32_t ulChannelHCI;                                    /**< HCI Channel used to send to BLE */
    uint32_t dlChannelHCI;                                    /**< HCI Channel used to receive from BLE */

    uint32_t ulChannelHPC;                                    /**< HPC Channel used to send to BLE */
    uint32_t dlChannelHPC;                                    /**< HPC Channel used to receive from BLE */

    uint32_t intStuctureSelf;                                 /**< Interrupt structure for the MCU */
    uint32_t intStucturePeer;                                 /**< Interrupt structure for the BLE */

    cy_stc_sysint_t ipcIntConfig;                             /**< IPC Interrupt configuration structure */

    cy_ipc_bt_irq_handler_t irqHandlerPtr;                    /**< This handler will be removed later once simulations are done */

    cy_ipc_bt_int_cb_ptr_t internal_hpc_notify_cb;            /**< This callback will be removed later once simulations are done */

    cy_ipc_bt_relcallback_ptr_t ulReleaseCallbackPtr;         /**< Callback function called when the UL channel is released */

    cy_ipc_bt_bufcallback_ptr_t bufCallbackPtr;               /**< Callback function called when there is a free buffer available */
} cy_stc_ipc_bt_config_t;

/**
* This is the definition of HPC IOSS config msg structure.
*/
typedef __PACKED_STRUCT cy_stc_ipc_msg_iocfg_t
{
    uint8_t msgId;                                  /**< Message ID for HPC message */
    uint8_t dummy1;                                 /**< Dummy byte to be ignored */
    uint16_t mode;                                  /**< IO config mode */
    uint32_t dummy2;                                /**< Dummy word to be ignored */
} cy_stc_ipc_msg_iocfg_t;

/**
* This is the definition of HPC TRNG msg structure.
*/
typedef __PACKED_STRUCT cy_stc_ipc_msg_trng_t
{
    uint8_t msgId;                                  /**< Message ID for HPC message */
    uint8_t dummy1;                                 /**< Dummy byte to be ignored */
    uint8_t dummy2;                                 /**< Dummy byte to be ignored */
    uint8_t dummy3;                                 /**< Dummy byte to be ignored */
    uint32_t trng;                                  /**< Dummy when sent to BTSS. TRNG when received from BTSS */
} cy_stc_ipc_msg_trng_t;

/**
* This is the definition of HPC PM request structure.
*/
typedef __PACKED_STRUCT cy_stc_ipc_msg_pmcmd_t
{
    uint8_t msgId;                                  /**< Message ID for HPC message */
    uint8_t dummy1;                                 /**< Not used */
    uint16_t dummy2;                                /**< Not used */
    uint32_t pm_op;                                 /**< Power management operation */
} cy_stc_ipc_msg_pmcmd_t;

/**
* This is the definition of HPC PM response structure.
*/
typedef __PACKED_STRUCT cy_stc_ipc_msg_pmresp_t
{
    uint8_t msgId;                                  /**< Message ID for HPC message */
    uint8_t dummy1;                                 /**< Not used */
    uint16_t dummy2;                                /**< Not used */
    uint32_t pm_resp;                               /**< Response form BT for power management command */
} cy_stc_ipc_msg_pmresp_t;

/**
* This is the definition of HPC resource access request structure from BTSS to MCU
*/
typedef __PACKED_STRUCT cy_stc_ipc_msg_res_access_req_t
{
    uint8_t msgId;                                  /**< Message ID for HPC message */
    uint8_t dummy1;                                 /**< Not used */
    uint16_t dummy2;                                /**< Not used */
    uint32_t access_ctrl;                           /**< Access enable/disable control */
} cy_stc_ipc_msg_res_access_req_t;

/**
* This is the definition of HPC resource access response structure from MCU to BTSS
*/
typedef __PACKED_STRUCT cy_stc_ipc_msg_res_access_resp_t
{
    uint8_t msgId;                                  /**< Message ID for HPC response */
    uint8_t dummy1;                                 /**< Not used */
    uint16_t dummy2;                                /**< Not used */
    uint32_t result;                                /**< result of access request */
} cy_stc_ipc_msg_res_access_resp_t;

/**
* This is the definition of HPC structure to indicate LPO change from MCU to BTSS
*/
typedef __PACKED_STRUCT cy_stc_ipc_msg_clklf_switch_t
{
    uint8_t msgId;                                  /**< Message ID for HPC message */
    uint8_t mode;                                   /**< LPO source 0 = PILO, 1 = WCO */
    uint8_t dummy1;                                 /**< Not used */
    uint8_t dummy2;                                 /**< Not used */
    uint32_t param;                                /**< WCO calibration offset in ppm */
} cy_stc_ipc_msg_clklf_switch_t;
/** \} group_ipc_bt_data_structures */


/**
* \addtogroup group_ipc_bt_functions
* \{
*/
/*******************************************************************************
* Function Name: Cy_BTIPC_Init
****************************************************************************//**
*
* This function initializes the Bluetooth IPC. The IPC channels used for HCI and HPC packet exchange
* between MCU and BT SS are initialized.
*
* \note In general, this function is called during application initialization.
*
* \param btIpcConfig
* This is the pointer to the bt ipc configuration structure.
*
* \param btIpcContext
* This is the pointer to the bt ipc context structure.
*
* \return
*    CY_BT_IPC_DRV_SUCCESS:          BT IPC API return for no error
*    CY_BT_IPC_DRV_ERROR:            BT IPC API return for general error
*    CY_BT_IPC_DRV_ERROR_BAD_HANDLE: BT IPC API return for bad handle
*
*******************************************************************************/
cy_en_btipcdrv_status_t Cy_BTIPC_Init(cy_stc_ipc_bt_context_t *btIpcContext, cy_stc_ipc_bt_config_t * btIpcConfig);


/*******************************************************************************
* Function Name: Cy_BTIPC_WarmInit
****************************************************************************//**
*
* This function performs the warm initialization of the Bluetooth IPC.
*
* \note In general, this function is called during application warm boot initialization.
*
* \param btIpcConfig
* This is the pointer to the bt ipc configuration structure.
*
* \param btIpcContext
* This is the pointer to the bt ipc context structure.
*
* \return
*    CY_BT_IPC_DRV_SUCCESS:          BT IPC API return for no error
*    CY_BT_IPC_DRV_ERROR:            BT IPC API return for general error
*    CY_BT_IPC_DRV_ERROR_BAD_HANDLE: BT IPC API return for bad handle
*
*******************************************************************************/
cy_en_btipcdrv_status_t Cy_BTIPC_WarmInit(cy_stc_ipc_bt_context_t *btIpcContext, cy_stc_ipc_bt_config_t * btIpcConfig);


/*******************************************************************************
* Function Name: Cy_BTIPC_Deinit
****************************************************************************//**
*
* This function de-initializes the Bluetooth IPC. All the registered callbacks are deleted.
*
* \note In general, this function is called when the application does not need BT IPC service
* anymore.
*
* \param btIpcContext
* This is the pointer to the bt ipc context structure.
*
* \return
*    CY_BT_IPC_DRV_SUCCESS:          BT IPC API return for no error
*    CY_BT_IPC_DRV_ERROR_BAD_HANDLE: BT IPC API return for bad handle
*
*******************************************************************************/
cy_en_btipcdrv_status_t Cy_BTIPC_Deinit(cy_stc_ipc_bt_context_t *btIpcContext);


/*******************************************************************************
* Function Name: Cy_BTIPC_HCI_getPTI
****************************************************************************//**
*
* This function gets the payload type indicator and the length of the HCI packet received
* from BTSS. This function can be called to find out the type of HCI packet and allocate
* buffer of appropriate size to copy the packet data.
*
* \note In general, this function is called before reading the packet to allocate memory
* of required size.
*
* \param pti
* This is the pointer to payload type indicator which is returned by the function.
*
* \param p_length
* This is the pointer to the length of the payload filled by the function.
*
* \param msgPtr
* This is the pointer to buffer which contains the IPC data received in DATA0 and DATA1
* registers.
*
* \return
*    CY_BT_IPC_DRV_SUCCESS:          BT IPC API return for no error
*    CY_BT_IPC_DRV_ERROR_BAD_HANDLE: BT IPC API return for bad handle
*
*******************************************************************************/
cy_en_btipcdrv_status_t Cy_BTIPC_HCI_getPTI (cy_en_btipc_hcipti_t *pti, uint32_t *p_length, uint32_t *msgPtr);


/*******************************************************************************
* Function Name: Cy_BTIPC_HCI_Write
****************************************************************************//**
*
* This function sends the HCI packet form the BT stack to the BTSS.
*
* \param pti
* This is the HCI payload type indicator.
*
* \param data
* This is the pointer to the buffer holding the HCI payload.
*
* \param length
* This is the length of the HCI payload in number of bytes.
*
* \param btIpcContext
* This is the pointer to the bt ipc context structure
*
* \return
*    CY_BT_IPC_DRV_SUCCESS:            BT IPC API return for no error
*    CY_BT_IPC_DRV_ERROR_BAD_HANDLE:   BT IPC API return for bad handle
*    CY_BT_IPC_DRV_ERROR_LOCK_ACQUIRE: BT IPC API return for buffer pool full error
*
*******************************************************************************/
cy_en_btipcdrv_status_t Cy_BTIPC_HCI_Write(cy_stc_ipc_bt_context_t *btIpcContext, cy_en_btipc_hcipti_t pti, void *data, size_t length);


/*******************************************************************************
* Function Name: Cy_BTIPC_HPC_Write
****************************************************************************//**
*
* This function sends the HPC packet form the MCU to the BTSS.
*
* \param data
* This is the pointer to the buffer holding the HPC payload.
*
* \param length
* This is the length of the HPC payload in number of bytes.
*
* \param btIpcContext
* This is the pointer to the bt ipc context structure
*
* \return
*    CY_BT_IPC_DRV_SUCCESS:            BT IPC API return for no error
*    CY_BT_IPC_DRV_ERROR_BAD_HANDLE:   BT IPC API return for bad handle
*    CY_BT_IPC_DRV_ERROR_LOCK_ACQUIRE: BT IPC API return for buffer pool full error
*
*******************************************************************************/
cy_en_btipcdrv_status_t Cy_BTIPC_HPC_Write(cy_stc_ipc_bt_context_t *btIpcContext, void *data, size_t length);


/*******************************************************************************
* Function Name: Cy_BTIPC_HCI_GetReadBufPtr
****************************************************************************//**
*
* This function gets the pointer to the received HCI packet by MCU from BTSS.
*
* \param ppData
* This is the pointer to the pointer of received HCI payload buffer
*
* \param pLength
* This is the pointer to the size of the payload received in number of bytes
*
* \param btIpcContext
* This is the pointer to the bt ipc context structure
*
* \return
*    CY_BT_IPC_DRV_SUCCESS:             BT IPC API return for no error
*    CY_BT_IPC_DRV_ERROR_BAD_HANDLE:    BT IPC API return for bad handle
*    CY_BT_IPC_DRV_ERROR_LOCK_ACQUIRE:  BT IPC API return for buffer pool full error
*    CY_BT_IPC_DRV_ERROR_LOCK_REL:      BT IPCAPI return for channel release error
*
*******************************************************************************/
cy_en_btipcdrv_status_t Cy_BTIPC_HCI_GetReadBufPtr (cy_stc_ipc_bt_context_t *btIpcContext, void **ppData, size_t* pLength);


/*******************************************************************************
* Function Name: Cy_BTIPC_HCI_GetWriteBufPtr
****************************************************************************//**
*
* This function gets the pointer to the buffer to write HCI packet to send to BTSS.
*
* \param pti
* This is the HCI payload type indicator.
*
* \param ppData
* This is the pointer to the pointer of buffer to write HCI payload buffer
*
* \param length
* This is the length of the HCI payload in number of bytes.
*
* \param btIpcContext
* This is the pointer to the bt ipc context structure
*
* \return
*    CY_BT_IPC_DRV_SUCCESS:             BT IPC API return for no error
*    CY_BT_IPC_DRV_ERROR_BAD_HANDLE:    BT IPC API return for bad handle
*    CY_BT_IPC_DRV_ERROR_LOCK_ACQUIRE:  BT IPC API return for buffer pool full error
*    CY_BT_IPC_DRV_ERROR_LOCK_REL:      BT IPCAPI return for channel release error
*
*******************************************************************************/
cy_en_btipcdrv_status_t Cy_BTIPC_HCI_GetWriteBufPtr(cy_stc_ipc_bt_context_t *btIpcContext, cy_en_btipc_hcipti_t pti, void **ppData, size_t length);


/*******************************************************************************
* Function Name: Cy_BTIPC_HPC_GetWriteBufPtr
****************************************************************************//**
*
* This function gets the pointer to the buffer to write HPC long message packet to
* send to BTSS.
*
* \param ppData
* This is the pointer to the pointer of buffer to write HPC long message payload buffer
*
* \param length
* This is the length of the HPC payload in number of bytes.
*
* \param btIpcContext
* This is the pointer to the bt ipc context structure
*
* \return
*    CY_BT_IPC_DRV_SUCCESS:             BT IPC API return for no error
*    CY_BT_IPC_DRV_ERROR_BAD_HANDLE:    BT IPC API return for bad handle
*    CY_BT_IPC_DRV_ERROR_LOCK_ACQUIRE:  BT IPC API return for buffer pool full error
*    CY_BT_IPC_DRV_ERROR_LOCK_REL:      BT IPCAPI return for channel release error
*
*******************************************************************************/
cy_en_btipcdrv_status_t Cy_BTIPC_HPC_GetWriteBufPtr(cy_stc_ipc_bt_context_t *btIpcContext, void **ppData, size_t length);


/*******************************************************************************
* Function Name: Cy_BTIPC_HCI_RelChannel
****************************************************************************//**
*
* This function releases the HCI channel after handling the notification from the
* BT SS
*
* \param btIpcContext
* This is the pointer to the bt ipc context structure
*
* \return
*    CY_BT_IPC_DRV_SUCCESS:             BT IPC API return for no error
*    CY_BT_IPC_DRV_ERROR_BAD_HANDLE:    BT IPC API return for bad handle
*    CY_BT_IPC_DRV_ERROR_LOCK_REL:      BT IPCAPI return for channel release error
*
*******************************************************************************/
cy_en_btipcdrv_status_t Cy_BTIPC_HCI_RelChannel(cy_stc_ipc_bt_context_t *btIpcContext);


/*******************************************************************************
* Function Name: Cy_BTIPC_HCI_RelBuffer
****************************************************************************//**
*
* This function releases the HCI buffer after copying the data received from BTSS
*
* \param btIpcContext
* This is the pointer to the bt ipc context structure
*
* \param msgPtr
* This is the pointer to the IPC message received form BTSS
*
* \return
*    CY_BT_IPC_DRV_SUCCESS:             BT IPC API return for no error
*    CY_BT_IPC_DRV_ERROR_BAD_HANDLE:    BT IPC API return for bad handle
*    CY_BT_IPC_DRV_ERROR_LOCK_REL:      BT IPCAPI return for channel release error
*
*******************************************************************************/
cy_en_btipcdrv_status_t Cy_BTIPC_HCI_RelBuffer(cy_stc_ipc_bt_context_t *btIpcContext, uint32_t* msgPtr);


/*******************************************************************************
* Function Name: Cy_BTIPC_HPC_RelChannel
****************************************************************************//**
*
* This function releases the HPC channel after handling the notification from the
* BT SS
*
* \param buf
* This is the pointer to the buffer received from BT SS in DATA0 and DATA1 channel
* registers.
*
* \param btIpcContext
* This is the pointer to the bt ipc context structure
*
* \return
*    CY_BT_IPC_DRV_SUCCESS:             BT IPC API return for no error
*    CY_BT_IPC_DRV_ERROR_BAD_HANDLE:    BT IPC API return for bad handle
*    CY_BT_IPC_DRV_ERROR_LOCK_REL:      BT IPCAPI return for channel release error
*
*******************************************************************************/
cy_en_btipcdrv_status_t Cy_BTIPC_HPC_RelChannel(cy_stc_ipc_bt_context_t *btIpcContext, void * buf);


/*******************************************************************************
* Function Name: Cy_BTIPC_HCI_RegisterCb
****************************************************************************//**
*
* This function registers the callback for HCI message notifications from BT SS
*
* \param hciNotifyCallbackPtr
* This is the pointer to the function to be called for HCI notifications.
*
* \param btIpcContext
* This is the pointer to the bt ipc context structure
*
* \return
*    CY_BT_IPC_DRV_SUCCESS:             BT IPC API return for no error
*    CY_BT_IPC_DRV_ERROR_BAD_HANDLE:    BT IPC API return for bad handle
*
*******************************************************************************/
cy_en_btipcdrv_status_t Cy_BTIPC_HCI_RegisterCb(cy_stc_ipc_bt_context_t *btIpcContext, cy_ipc_bt_callback_ptr_t hciNotifyCallbackPtr);


/*******************************************************************************
* Function Name: Cy_BTIPC_HCI_UnregisterCb
****************************************************************************//**
*
* This function un-registers the callback function registered for HCI message
* notifications from BT SS
*
* \param btIpcContext
* This is the pointer to the bt ipc context structure
*
* \return
*    CY_BT_IPC_DRV_SUCCESS:             BT IPC API return for no error
*    CY_BT_IPC_DRV_ERROR_BAD_HANDLE:    BT IPC API return for bad handle
*
*******************************************************************************/
cy_en_btipcdrv_status_t Cy_BTIPC_HCI_UnregisterCb(cy_stc_ipc_bt_context_t *btIpcContext);


/*******************************************************************************
* Function Name: Cy_BTIPC_HPC_RegisterCb
****************************************************************************//**
*
* This function registers the callback for HPC message notifications from BT SS
*
* \param pHpcNotifyCallbackParam
* This is the pointer to the function to be called for HPC notifications.
*
* \param btIpcContext
* This is the pointer to the bt ipc context structure
*
* \return
*    CY_BT_IPC_DRV_SUCCESS:             BT IPC API return for no error
*    CY_BT_IPC_DRV_ERROR_BAD_HANDLE:    BT IPC API return for bad handle
*    CY_BT_IPC_DRV_ERROR:               BT IPC API return for general error
*
*******************************************************************************/
cy_en_btipcdrv_status_t Cy_BTIPC_HPC_RegisterCb(cy_stc_ipc_bt_context_t *btIpcContext, cy_stc_ipc_hcp_cb_t *pHpcNotifyCallbackParam);


/*******************************************************************************
* Function Name: Cy_BTIPC_HPC_UnregisterCb
****************************************************************************//**
*
* This function un-registers the callback function registered for HPC message
* notifications from BT SS
*
* \param pHpcNotifyCallbackParam
* This is the pointer to the callback function to be un-registered.
*
* \param btIpcContext
* This is the pointer to the bt ipc context structure
*
* \return
*    CY_BT_IPC_DRV_SUCCESS:             BT IPC API return for no error
*    CY_BT_IPC_DRV_ERROR_BAD_HANDLE:    BT IPC API return for bad handle
*    CY_BT_IPC_DRV_ERROR:               BT IPC API return for general error
*
*******************************************************************************/
cy_en_btipcdrv_status_t Cy_BTIPC_HPC_UnregisterCb(cy_stc_ipc_bt_context_t *btIpcContext, cy_stc_ipc_hcp_cb_t *pHpcNotifyCallbackParam);


/*******************************************************************************
* Function Name: Cy_BTIPC_Buffer_RegisterCb
****************************************************************************//**
*
* This function registers the callback for buffer available notification
*
* \param bufCallbackPtr
* This is the pointer to the function to be called for buffer available notification.
*
* \param btIpcContext
* This is the pointer to the bt ipc context structure
*
* \return
*    CY_BT_IPC_DRV_SUCCESS:             BT IPC API return for no error
*    CY_BT_IPC_DRV_ERROR_BAD_HANDLE:    BT IPC API return for bad handle
*    CY_BT_IPC_DRV_ERROR:               BT IPC API return for general error
*
*******************************************************************************/
cy_en_btipcdrv_status_t Cy_BTIPC_Buffer_RegisterCb(cy_stc_ipc_bt_context_t *btIpcContext, cy_ipc_bt_bufcallback_ptr_t bufCallbackPtr);


/*******************************************************************************
* Function Name: Cy_BTIPC_HCI_FIFOGet
****************************************************************************//**
*
* This function is called to pull the IPC message from FIFO.
*
* \param ppMsg
* This is the pointer to pointer the location in FIFO where the retrieved message is stored.
*
* \param delete
* When set to 1, the entry from the FIFO is deleted after pulling it.
*
* \param btIpcContext
* This is the pointer to the bt ipc context structure
*
* \return
*    CY_BT_IPC_DRV_SUCCESS:             BT IPC API return for no error
*    CY_BT_IPC_DRV_ERROR_BUF_FULL  :    BT IPC API return for FIFO full
*
*******************************************************************************/
cy_en_btipcdrv_status_t Cy_BTIPC_HCI_FIFOGet(cy_stc_ipc_bt_context_t *btIpcContext, uint32_t **ppMsg, uint8_t delete);


/*******************************************************************************
* Function Name: Cy_BTIPC_HCI_FIFOCount
****************************************************************************//**
*
* This function is called to get the number of messages in the IPC FIFO.
*
* \param btIpcContext
* This is the pointer to the bt ipc context structure
*
* \return
*    number of messages in the IPC FIFO
*
*******************************************************************************/
uint16_t Cy_BTIPC_HCI_FIFOCount(cy_stc_ipc_bt_context_t *btIpcContext);


/*******************************************************************************
* Function Name: Cy_BTIPC_RetrieveContext
****************************************************************************//**
*
* This function is called to retrieve the context to be saved during RAM off
* state.
*
* \param pContextRet
* Pointer to the context to be retrieved. This will be updated by this function.
*
* \param btIpcContext
* This is the pointer to the bt ipc context structure
*
* \return
*    CY_BT_IPC_DRV_SUCCESS:             BT IPC API return for no error
*    CY_BT_IPC_DRV_ERROR_BAD_HANDLE:    BT IPC API return for bad handle
*
*******************************************************************************/
cy_en_btipcdrv_status_t Cy_BTIPC_RetrieveContext(cy_stc_ipc_bt_context_t *btIpcContext, cy_stc_ipc_bt_save_ctxt_t *pContextRet);


/*******************************************************************************
* Function Name: Cy_BTIPC_RestoreContext
****************************************************************************//**
*
* This function is called to restore the saved context during RAM off state.
*
* \param pContextRet
* Pointer to the saved context structure to be restored
*
* \param btIpcContext
* This is the pointer to the bt ipc context structure
*
* \return
*    CY_BT_IPC_DRV_SUCCESS:             BT IPC API return for no error
*    CY_BT_IPC_DRV_ERROR_BAD_HANDLE:    BT IPC API return for bad handle
*
*******************************************************************************/
cy_en_btipcdrv_status_t Cy_BTIPC_RestoreContext(cy_stc_ipc_bt_context_t *btIpcContext, cy_stc_ipc_bt_save_ctxt_t *pContextRet);


/** \} group_ipc_bt_functions */

void Cy_BTIPC_IRQ_Handler(cy_stc_ipc_bt_context_t *btIpcContext);

/* This function prototype will be removed once the simulations are done */
void Cy_BTIPC_HPC_Notify(void *btIpcContext, uint32_t * msgPtr);
/* This function will print the BT IPC driver status */
#ifdef BTIPC_STATUS
cy_en_btipcdrv_status_t Cy_bt_PrintStatus (cy_stc_ipc_bt_context_t *btIpcContext);
#endif
/** \} group_ipc_bt */

#ifdef __cplusplus
}
#endif

#endif /* CY_IP_MXIPC */

#endif /* !defined (CY_IPC_BT_H) */

/* [] END OF FILE */
