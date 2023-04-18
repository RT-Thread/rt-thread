/***************************************************************************//**
* \file cy_lin.h
* \version 1.1
*
* \brief
* Provides an API declaration of the LIN driver
*
********************************************************************************
* \copyright
* Copyright 2020-2021, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

/**
* \addtogroup group_lin
* \{
* The LIN driver provides a function API to manage Local Interconnect Network.
*
* The functions and other declarations used in this driver are in cy_lin.h.
* You can include cy_pdl.h to get access to all functions
* and declarations in the PDL.
*
* The Local Interconnect Network (LIN) bus was developed to create a standard for low-cost, low-end multiplexed communication. The use of a standard * bus protocol promotes the interoperability of network nodes.
* The LIN bus is a sub-bus system based on a serial communications protocol. The bus is a single master / multiple slave bus that uses a single wire * to transmit data.
* A LIN cluster exchanges messages with a pre-defined message frame format. The master node initiates a message exchange. Both the master node and   * the slave nodes can transmit (TX) and receive (RX).
* The LIN protocol is half-duplex: a LIN node is either transmitting or receiving, but it cannot transmit and receive at the same time. Messages are * exchanged when the LIN cluster is in operational mode.
* A LIN cluster also exchanges wake-up signals. Both the master node and the slave nodes can initiate a wake-up. Wake-up signals are exchanged when   * the LIN cluster is in sleep mode.
* The LIN bus can have a length of 10's of meters and has a bit-rate in the range of 1 kbps to 20 kbps. Most bus timing is expressed in bit periods  * (e.g. a 20 kbps LIN bus has a 50 us bit period).
* The LIN bus uses single wire communication using a "lin" line with an operating Voltage of 12 V. Most master and slave nodes use discrete           * transceiver devices.
*
* Features:
* * Single LIN hardware unit supporting multiple LIN channels.
* * Unified interrupt model.
* * Per LIN channel:
* * * Master and slave functionality.
* * * Master node autonomous header transmission. Master node autonomous response transmission and reception.
* * * Slave node autonomous header reception. Slave node autonomous response transmission and reception.
* * * Message buffer for PID, data and checksum fields.
* * * Break detection during message reception.
* * * Classic and enhanced checksum.
* * * Wakeup signaling.
* * * Timeout detection.
* * * Error detection.
*
* The LIN bus is an industry standard.
*
* \image html lin_network.png "LIN Network" width=400px
* \image latex lin_network.png
*
* Message Format:
*
* A LIN message have a pre-defined message frame format.

* A frame consists of a header, followed by a response.
* A frame header consists of a break field, followed by a synchronization field, followed by a protected identifier (PID) field.
* A frame response consists of 1, 2, ..., or 8 data fields, followed by a checksum field.
* The PID field, data fields and checksum fields are supported through a message buffer registers (MMIO PID_CHECKSUM, DATA0 and DATA1 registers).
*
* When transmitting, the message buffer registers provides the "to be transmitted" field values (with the exception of the checksum
* field, which is dynamically calculated).
* When receiving, the message buffer registers capture the received field values.
*
* \image html LIN_Message_Format.png "LIN Message Format" width=600px
* \image latex LIN_Message_Format.png
*
* The break field length and the break delimiter length.
*
* All other fields are 8-bit (1Byte) values that are transferred in a "UART format" with 1 START bit period and 1 STOP bit period.
*
* When receiving, the START and STOP bits are verified. In case of verification failure, a RX_HEADER_FRAME_ERROR or
* RX_RESPONSE_FRAME_ERROR is activated.
* Byte values are transmitted with least significant bit first format.
*
* Initialization:
*
* The LIN initialization is according to the Options setup in the passed Config Struct. \ref cy_stc_lin_config_t  Several validations are done before that and an error is returned if invalid Modes are requested.
*
* Lin Configuration:
*
* Break_Wakup_Length field is used for transmission/reception of BOTH break and wakeup signals.
* \note These functions are mutually exclusive:
* Break_Delimiter_length field specifies the break delimiter length: used in header transmission, not used in header reception.
* STOP bit periods:
* LIN mode.
*
* \snippet lin/snippet/main.c snippet_Cy_LIN_Init
*
* Command:
*
* There are 5 commands that user can set in combinations. to send the data.
*    - TX_HEADER
*    - RX_HEADER
*    - TX_RESPONSE
*    - RX_RESPONSE
*    - TX_WAKEUP
*
* The following restrictions apply when programming the commands:
*    - TX_HEADER and RX_HEADER are mutually exclusive; i.e. both cannot be set to '1'.
*    - TX_WAKEUP is mutually exclusive with all other commands.
*    - TX_RESPONSE and RX_RESPONSE are NOT mutually exclusive, but are evaluated in the following order (of decreasing priority): TX_RESPONSE, RX_RESPONSE.
*
* The break or wakeup detection is always enabled, regardless of CMD register setting.
*
* Following are the combination of commands that user can use. These commands can be provided as predefined commands in cy_lin.h.
*    - LIN_CMD_TX_HEADER
*    - LIN_CMD_TX_RESPONSE
*    - LIN_CMD_RX_RESPONSE
*    - LIN_CMD_TX_HEADER_TX_RESPONSE
*    - LIN_CMD_TX_HEADER_RX_RESPONSE
*    - LIN_CMD_RX_HEADER_RX_RESPONSE
*    - LIN_CMD_TX_WAKEUP
*
* \snippet lin/snippet/main.c snippet_Cy_LIN_Sequence
*
* Interrupt Handling :
*
* Lin channels have dedicated interrupts
*
* Driver does not handle interrupts and it is user's responsibility to clear interrupts.
* User registers for the list of interrupts given below and handle the interrupts in the interrupt handler.
* A code snippet is given below for registering to the interrupts and handling the interrupts in interrupt handler.
*
* There are 16 type of interrupts that the software can register for
*
*    - TX_HEADER_DONE                : When a frame header (break field, synchronization field and PID field) is transmitted.
*    - TX_RESPONSE_DONE              : When a frame response (data fields and checksum field) is transmitted.
*    - TX_WAKEUP_DONE                : When a wakeup signal is transmitted. This cause is activated on a transition from dominant/'0' state to recessive/'1' state; i.e. at the end of the wakeup signal.
*    - RX_HEADER_DONE                : When a frame header (break field, synchronization field and PID field) is received.
*    - RX_RESPONSE_DONE              : When a frame response (data fields and checksum field) is received
*    - RX_BREAK_WAKEUP_DONE          : When a break or wakeup signal is received (per CTL.BREAK_WAKEUP_LENGTH). This cause is activated on a transition from dominant/'0' state to recessive/'1' state; i.e. at the end of the wakeup signal.
*    - RX_HEADER_SYNC_DONE           : When a synchronization field is received (including trailing STOP bits).
*    - RX_NOISE_DETECT               : When  isolated '0' or '1' "in_rx_in" values are observed or when during sampling the last three "lin_rx_in" values do NOT all have the same value. This mismatch is an indication of noise on the LIN line.
*    - TIMEOUT                       : When a frame, frame header or frame response timeout is detected.
*    - TX_HEADER_BIT_ERROR           : When a transmitted "lin_tx_out" value does NOT match a received "lin_rx_in" value (during header transmission). This specific test allows for delay through the external transceiver. This mismatch is an indication of bus collisions on the LIN line.
*    - TX_RESPONSE_BIT_ERROR         : When a transmitted "lin_tx_out" value does NOT match a received "lin_rx_in" value (during response transmission).
*    - RX_HEADER_FRAME_ERROR         : When the received START or STOP bits have an unexpected value (during header reception).
*    - RX_HEADER_SYNC_ERROR          : When the received synchronization field is not received within the synchronization counter range [106, 152]
*    - RX_HEADER_PARITY_ERROR        : When the received PID field has a parity error.
*    - RX_RESPONSE_FRAME_ERROR       : When the received START or STOP bits have an unexpected value (during response reception)
*    - RX_RESPONSE_CHECKSUM_ERROR    : When the calculated checksum over the received PID and data fields is not the same as the received checksum.
*
* \snippet lin/snippet/main.c snippet_Cy_LIN_ISR
*
* \section group_lin_changelog Changelog
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td>1.1</td>
*     <td>Fixed MISRA 2012 violations.</td>
*     <td>MISRA 2012 compliance.</td>
*   </tr>
*   <tr>
*     <td>1.0</td>
*     <td>Initial version</td>
*     <td></td>
*   </tr>
* </table>
*
* \defgroup group_lin_macro Macros
*   \{
*       \defgroup group_lin_cmd_macro LIN Command Type Definition
*       \defgroup group_lin_intr_mask_macro LIN ALL Interrupt Mask Definition
*       \defgroup group_lin_common_macro LIN Common Macros
*   \}
* \defgroup group_lin_functions Functions
* \defgroup group_lin_data_structures Data Structures
* \defgroup group_lin_enums Enumerated Types
*/


#if !defined(CY_LIN_H)
#define CY_LIN_H
#include "cy_device.h"
#if defined (CY_IP_MXLIN)
/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "cy_syslib.h"

#if defined(__cplusplus)
extern "C" {
#endif

/**
* \addtogroup group_lin_macro
* \{
*/


/*****************************************************************************/
/* Global pre-processor symbols/macros ('#define')                           */
/*****************************************************************************/
/** Driver major version */
#define CY_LIN_DRV_VERSION_MAJOR    1

/** Driver minor version */
#define CY_LIN_DRV_VERSION_MINOR    1

/** LIN driver ID */
#define CY_LIN_ID CY_PDL_DRV_ID(0x37u)

/** \} group_lin_macro */

/**
* \addtogroup group_lin_common_macro LIN Common Macros
* \{
* LIN Specific common Macros
*/
/** Maximum ID */
#define LIN_ID_MAX                              (0x3Fu)
/** Maximum data length */
#define LIN_DATA_LENGTH_MAX                     (8u)
/** Minimum data length */
#define LIN_DATA_LENGTH_MIN                     (1u)
/** Maximum time out length */
#define LIN_TIMEOUT_LENGTH_MAX                  (255u)
/** Minimum wakeup period value = 250usec*/
#define LIN_WAKEUP_PERIOD_MIN                   (250u)
/** Maximum break_wakeup period bit length */
#define LIN_BREAK_WAKEUP_LENGTH_BITS_MAX        (31u)
/** LIN Master minimum break filed detection length */
#define LIN_MASTER_BREAK_FILED_LENGTH_MIN       (13u)

/** \} group_lin_common_macro */

/**
* \addtogroup group_lin_enums
* \{
*/
/** LIN API status definition */
typedef enum
{
    CY_LIN_SUCCESS   = 0x00u,                                     /**< Returned successful */
    CY_LIN_BAD_PARAM = CY_LIN_ID | CY_PDL_STATUS_ERROR | 0x01u,   /**< Bad parameter was passed */
    CY_LIN_BUSY      = CY_LIN_ID | CY_PDL_STATUS_ERROR | 0x02u,   /**< Change settings while tx/rx on-going */
    CY_LIN_FRAME_NOT_RECEIVED = CY_LIN_ID | CY_PDL_STATUS_ERROR | 0x03u,   /**< No frame received */
} cy_en_lin_status_t;
/** \} group_lin_enums */

/**
* \addtogroup group_lin_cmd_macro LIN Command Type Definition
* \{
* Specifies the parameter values passed to LIN command API
*/
/** LIN Command TX Header */
#define LIN_CMD_TX_HEADER                   (LIN_CH_CMD_TX_HEADER_Msk)
/** LIN Command TX Response */
#define LIN_CMD_TX_RESPONSE                 (LIN_CH_CMD_TX_RESPONSE_Msk)
/** LIN Command RX Response */
#define LIN_CMD_RX_RESPONSE                 (LIN_CH_CMD_RX_RESPONSE_Msk)
/** LIN Command TX Header and TX Response */
#define LIN_CMD_TX_HEADER_TX_RESPONSE       (LIN_CH_CMD_TX_HEADER_Msk | LIN_CH_CMD_TX_RESPONSE_Msk)
/** LIN Command TX Header and RX Response */
#define LIN_CMD_TX_HEADER_RX_RESPONSE       (LIN_CH_CMD_TX_HEADER_Msk | LIN_CH_CMD_RX_RESPONSE_Msk)
/** LIN Command RX Header and RX Response */
#define LIN_CMD_RX_HEADER_RX_RESPONSE       (LIN_CH_CMD_RX_HEADER_Msk | LIN_CH_CMD_RX_RESPONSE_Msk)
/** LIN Command TX Wake up */
#define LIN_CMD_TX_WAKEUP                   (LIN_CH_CMD_TX_WAKEUP_Msk)
/** \} group_lin_cmd_macro */

/**
* \addtogroup group_lin_intr_mask_macro LIN ALL Interrupt Mask Definition
* \{
* Specifies the mask value for interrupt status/mask
*/
/** Mask for TX Header DONE */
#define LIN_INTR_TX_HEADER_DONE             (LIN_CH_INTR_TX_HEADER_DONE_Msk)
/** Mask for TX Response DONE */
#define LIN_INTR_TX_RESPONSE_DONE           (LIN_CH_INTR_TX_RESPONSE_DONE_Msk)
/** Mask for TX Wake up DONE */
#define LIN_INTR_TX_WAKEUP_DONE             (LIN_CH_INTR_TX_WAKEUP_DONE_Msk)
/** Mask for RX Header DONE */
#define LIN_INTR_RX_HEADER_DONE             (LIN_CH_INTR_RX_HEADER_DONE_Msk)
/** Mask for RX Response DONE */
#define LIN_INTR_RX_RESPONSE_DONE           (LIN_CH_INTR_RX_RESPONSE_DONE_Msk)
/** Mask for RX Wake up DONE */
#define LIN_INTR_RX_BREAK_WAKEUP_DONE       (LIN_CH_INTR_MASK_RX_BREAK_WAKEUP_DONE_Msk)
/** Mask for RX Header Sync DONE */
#define LIN_INTR_RX_HEADER_SYNC_DONE        (LIN_CH_INTR_RX_HEADER_SYNC_DONE_Msk)
/** Mask for RX Noise Detect */
#define LIN_INTR_RX_NOISE_DETECT            (LIN_CH_INTR_RX_NOISE_DETECT_Msk)
/** Mask for timeout */
#define LIN_INTR_TIMEOUT                    (LIN_CH_INTR_TIMEOUT_Msk)
/** Mask for TX Header Bit error */
#define LIN_INTR_TX_HEADER_BIT_ERROR        (LIN_CH_INTR_TX_HEADER_BIT_ERROR_Msk)
/** Mask for TX Response Bit error */
#define LIN_INTR_TX_RESPONSE_BIT_ERROR      (LIN_CH_INTR_TX_RESPONSE_BIT_ERROR_Msk)
/** Mask for RX Header frame error */
#define LIN_INTR_RX_HEADER_FRAME_ERROR      (LIN_CH_INTR_RX_HEADER_FRAME_ERROR_Msk)
/** Mask for Rx header sync error */
#define LIN_INTR_RX_HEADER_SYNC_ERROR       (LIN_CH_INTR_RX_HEADER_SYNC_ERROR_Msk)
/** Mask for Rx header parity error */
#define LIN_INTR_RX_HEADER_PARITY_ERROR     (LIN_CH_INTR_RX_HEADER_PARITY_ERROR_Msk)
/** Mask for Rx Response frame error */
#define LIN_INTR_RX_RESPONSE_FRAME_ERROR    (LIN_CH_INTR_RX_RESPONSE_FRAME_ERROR_Msk)
/** Mask for Rx response checksum error */
#define LIN_INTR_RX_RESPONSE_CHECKSUM_ERROR (LIN_CH_INTR_RX_RESPONSE_CHECKSUM_ERROR_Msk)
/** Mask for all slave errors */
#define LIN_INTR_ALL_ERROR_MASK_SLAVE       (LIN_CH_INTR_RX_NOISE_DETECT_Msk           |\
                                             LIN_CH_INTR_TIMEOUT_Msk                   |\
                                             LIN_CH_INTR_TX_RESPONSE_BIT_ERROR_Msk     |\
                                             LIN_CH_INTR_RX_HEADER_FRAME_ERROR_Msk     |\
                                             LIN_CH_INTR_RX_HEADER_SYNC_ERROR_Msk      |\
                                             LIN_CH_INTR_RX_HEADER_PARITY_ERROR_Msk    |\
                                             LIN_CH_INTR_RX_RESPONSE_FRAME_ERROR_Msk   |\
                                             LIN_CH_INTR_RX_RESPONSE_CHECKSUM_ERROR_Msk)
/** Mask for all master errors */
#define LIN_INTR_ALL_ERROR_MASK_MASTER      (LIN_INTR_ALL_ERROR_MASK_SLAVE | LIN_CH_INTR_TX_HEADER_BIT_ERROR_Msk)


/** \} group_lin_intr_mask_macro */

/**
* \addtogroup group_lin_enums
* \{
*/
/*****************************************************************************/
/* Global type definitions ('typedef')                                       */
/*****************************************************************************/
/**
 *****************************************************************************
 ** \brief LIN break delimiter length
 **
 ** This configuration is effective only when corresponding channel = master mode.
 *****************************************************************************/
typedef enum cy_en_lin_break_delimiter_length{
    LIN_BREAK_DILIMITER_LENGTH_1BITS = 0,   /*!< 1-bit length */
    LIN_BREAK_DILIMITER_LENGTH_2BITS = 1,   /*!< 2-bit length */
    LIN_BREAK_DILIMITER_LENGTH_3BITS = 2,   /*!< 3-bit length */
    LIN_BREAK_DILIMITER_LENGTH_4BITS = 3    /*!< 4-bit length */
}cy_en_lin_break_delimiter_length_t;

/**
 *****************************************************************************
 ** \brief Stop bit selection.
 **
 *****************************************************************************/
typedef enum cy_en_lin_stopbit
{
    LIN_ONE_STOP_BIT           = 1,    /*!< 1 stop bit */
    LIN_TWO_STOP_BIT           = 3     /*!< 2 stop bits */
} cy_en_lin_stopbit_t;

/**
 *****************************************************************************
 ** \brief Checksum type selection.
 **
 *****************************************************************************/
typedef enum cy_en_lin_checksum_type
{
    LIN_CHECKSUM_TYPE_NORMAL = 0,      /*!< Normal (classic) checksum */
    LIN_CHECKSUM_TYPE_EXTENDED = 1     /*!< Extended (enhanced) checksum */
}cy_en_lin_checksum_type_t;

/**
 *****************************************************************************
 ** \brief Timeout type selection.
 **
 *****************************************************************************/
typedef enum cy_en_lin_timeout_sel_type
{
    LIN_TIMEOUT_NONE = 0,                     /*!< No timeout */
    LIN_TIMEOUT_FROM_BREAK_TO_CHECKSUM = 1,    /*!< Frame mode: from the start of break field to checksum field STOP bits */
    LIN_TIMEOUT_FROM_BREAK_TO_PID = 2,         /*!< Frame header mode: detects timeout from the start of break field to PID field STOP bits */
    LIN_TIMEOUT_FROM_RESPONSE_TO_CHECKSUM = 3 /*!< Frame response mode: detects timeout from the first data field START bit to checksum field STOP bits. */
}cy_en_lin_timeout_sel_type_t;
/** \} group_lin_enums */

/**
* \addtogroup group_lin_data_structures
* \{
*/

/**
 *****************************************************************************
 ** \brief LIN configuration
 **        These settings are per LIN instance.
 *****************************************************************************/
typedef struct cy_stc_lin_config
{

    bool masterMode;                    /**< If TRUE, corresponding channel = master mode, If FALSE, slave mode. */

    bool linTransceiverAutoEnable;     /**< If TRUE, corresponding LIN channel transceiver is enabled automatically,
                                         If FALSE, firmware has to handle the transceiver enable signal manually */

    uint8_t breakFieldLength;           /**< Break field length. */

    cy_en_lin_break_delimiter_length_t breakDelimiterLength; /**< Break delimiter length. See #cy_en_lin_break_delimiter_length_t */

    cy_en_lin_stopbit_t stopBit;        /**< Stop bit length. See #cy_en_lin_stopbit_t. */

    bool filterEnable;                  /**< If TRUE, lin_rx_in filter operates.
                                        Median 3 operates on the last three "lin_rx_in" values.
                                        The sequences '000', '001', '010' and '100' result in a filtered value '0'.
                                        The sequences '111', '110', '101' and '011' result in a filtered value '1'.
                                        */
}cy_stc_lin_config_t;

/**
 *****************************************************************************
 ** \brief LIN Test configuration
 **        This testing functionality simplifies SW development,
 **        but may also be used in the field to verify correct channel functionality.
 *****************************************************************************/
typedef struct cy_stc_lin_test_config
{
    uint8_t chidx;                        /**< Specifies the channel index of the channel to which the test applies.
                                             The test mode allows BOTH of the two connected channels to be tested. */
    bool mode;                            /**< When set FALSE, it is partial disconnect from IOSS. Used to observe messages outside of device.
                                             When Set TRUE, it is full disconnect from IOSS. Used for device test without effecting
                                             operational LIN cluster. */
}cy_stc_lin_test_config_t;

/**
 *****************************************************************************
 ** \brief LIN Error CTL configuration
 **        Used only for software testing.
 **        It enables HW injected channel transmitter errors.
 **        The receiver should detect these errors and report these errors through activation of corresponding interrupt causes.
 *****************************************************************************/
typedef struct cy_stc_lin_test_error_config
{
    uint8_t chidx;                /**< Specifies the channel index of the channel to which the test applies.
                                     The test mode allows BOTH of the two connected channels to be tested. */
    bool txsync_error;            /**< At the receiver, this should result in INTR.RX_HEADER_SYNC_ERROR activation. */
    bool txsyncStop_error;        /**< At the receiver, this should result in INTR.RX_HEADER_SYNC_ERROR or INTR.RX_HEADER_FRAME_ERROR activation. */
    bool txParity_error;        /**< At the receiver, this should result in INTR.RX_HEADER_PARITY_ERROR activation. */
    bool txPIDStop_error;        /**< At the receiver, this should result in INTR.RX_HEADER_FRAME_ERROR activation. */
    bool txDataStop_error;        /**< At the receiver, this should result in INTR.RX_RESPONSE_FRAME_ERROR activation. */
    bool txChecksum_error;        /**< At the receiver, this should result in INTR.RX_RESPONSE_CHECKSUM_ERROR activation. */
    bool txChecksumStop_error;    /**< At the receiver, this should result in INTR.RX_RESPONSE_FRAME_ERROR activation. */
}cy_stc_lin_test_error_config_t;

/** \} group_lin_data_structures */

/*****************************************************************************/
/* Global variable declarations ('extern', definition in C source)           */
/*****************************************************************************/
/** \cond Internal */
/*
* Default values for the CTL Register.
*/

/** Mask for Stop Bits */
#define LIN_CH_CTL0_STOP_BITS_DEFAULT                LIN_ONE_STOP_BIT
/** Mask for Auto Enable */
#define LIN_CH_CTL0_AUTO_EN_DEFAULT                  0U
/** Mask for break delimiter length */
#define LIN_CH_CTL0_BREAK_DELIMITER_LENGTH_DEFAULT   1U
/** Mask for break wake up length */
#define LIN_CH_CTL0_BREAK_WAKEUP_LENGTH_DEFAULT      12U
/** Mask for mode */
#define LIN_CH_CTL0_MODE_DEFAULT                     0U
/** Mask for error ignore */
#define LIN_CH_CTL0_BIT_ERROR_IGNORE_DEFAULT         0U
/** Mask for parity */
#define LIN_CH_CTL0_PARITY_DEFAULT                   0U
/** Mask for parity enable */
#define LIN_CH_CTL0_PARITY_EN_DEFAULT                0U
/** Mask for filter enable */
#define LIN_CH_CTL0_FILTER_EN_DEFAULT                1U
/** Mask for enabled */
#define LIN_CH_CTL0_ENABLED_DEFAULT                  0U
/** Mask for default */
#define LIN_CH_CTL0_DEFAULT (_VAL2FLD(LIN_CH_CTL0_STOP_BITS, LIN_CH_CTL0_STOP_BITS_DEFAULT) | \
                                _VAL2FLD(LIN_CH_CTL0_AUTO_EN, LIN_CH_CTL0_AUTO_EN_DEFAULT) | \
                                _VAL2FLD(LIN_CH_CTL0_BREAK_DELIMITER_LENGTH, LIN_CH_CTL0_BREAK_DELIMITER_LENGTH_DEFAULT) | \
                                _VAL2FLD(LIN_CH_CTL0_BREAK_WAKEUP_LENGTH, LIN_CH_CTL0_BREAK_WAKEUP_LENGTH_DEFAULT) | \
                                _VAL2FLD(LIN_CH_CTL0_MODE, LIN_CH_CTL0_MODE_DEFAULT) | \
                                _VAL2FLD(LIN_CH_CTL0_BIT_ERROR_IGNORE, LIN_CH_CTL0_BIT_ERROR_IGNORE_DEFAULT) | \
                                _VAL2FLD(LIN_CH_CTL0_PARITY, LIN_CH_CTL0_PARITY_DEFAULT) | \
                                _VAL2FLD(LIN_CH_CTL0_PARITY_EN, LIN_CH_CTL0_PARITY_EN_DEFAULT) | \
                                _VAL2FLD(LIN_CH_CTL0_FILTER_EN, LIN_CH_CTL0_FILTER_EN_DEFAULT) | \
                                _VAL2FLD(LIN_CH_CTL0_ENABLED, LIN_CH_CTL0_ENABLED_DEFAULT))

/* Macros for the conditions used by CY_ASSERT calls */
#define CY_LIN_TEST_CTL_CH_IDX_MIN          0U        /** LIN Test Ctl Channel index Minimum value */
#define CY_LIN_TEST_CTL_CH_IDX_MAX          31U       /** LIN Test Ctl Channel index Maximum value */

#define CY_LIN_IS_TEST_CTL_CH_IDX_VALID(chidx)       ((chidx) <= CY_LIN_TEST_CTL_CH_IDX_MAX)


/** \endcond */

/**
* \addtogroup group_lin_functions
* \{
*/

/*****************************************************************************/
/* Global function prototypes ('extern', definition in C source)             */
/*****************************************************************************/
/**
 *****************************************************************************
 ** \brief Deinitialization of a LIN module.
 ** This function deinitializes the selected LIN channel.
 **
 ** \param [in]  base       Pointer to LIN instance channel register
 **
 ** \retval Refer \ref cy_en_lin_status_t
 **
 ** \funcusage
 ** \snippet lin/snippet/main.c snippet_Cy_LIN_DeInit
 **
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_DeInit( LIN_CH_Type* base );

/**
 *****************************************************************************
 ** \brief Initializes the LIN module.
 ** This function initializes LIN according to the options setup in the
 ** passed Config Struct. Several checkings are done before that and an error
 ** is returned if invalid Modes are requested.
 **
 ** \pre The Application must configure corresponding LIN pins (SIN, SOT)
 **      according to requirements and settings of LIN instance.
 **      And must set baud rate using SysClk. LIN I/F has internal fixed
 **      oversampling value (16). Therefore, LIN clock / 16 is actual
 **      baud rate.
 **
 ** \param [in]  base        Pointer to LIN instance register area
 ** \param [in]  pstcConfig     LIN module configuration. See #cy_stc_lin_config_t.
 **
 ** \retval Refer \ref cy_en_lin_status_t
 **
 ** \funcusage
 ** \snippet lin/snippet/main.c snippet_Cy_LIN_Init
 **
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_Init( LIN_CH_Type* base, const cy_stc_lin_config_t *pstcConfig);

/**
 *****************************************************************************
 ** \brief Reads response data.
 **        Data is read in Bytes. Maximum data length is 8-bytes.
 **
 ** \pre Must be run after RX_RESPONSE_DONE.
 **
 ** \note This function returns last received data set.
 **
 ** \param  base     [in]        Pointer to LIN instance register area.
 ** \param  data     [out]       Pointer to received data.
 **                              Must have enough space for current Rx data.
 **
 ** \retval Refer \ref cy_en_lin_status_t
 **
 ** \funcusage
 ** \snippet lin/snippet/main.c snippet_Cy_LIN_ISR
 **
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_ReadData( LIN_CH_Type* base, uint8_t *data);

/**
 *****************************************************************************
 ** \brief Writes response data.
 **        Data is written in Bytes. Maximum data length is 8-bytes.
 ** \param  base         [in]        Pointer to LIN instance register area.
 ** \param  data         [in]        Pointer to response data.
 ** \param  dataLength   [in]        Data length in bytes.
 ** \retval Refer \ref cy_en_lin_status_t
 **
 ** \funcusage
 ** \snippet lin/snippet/main.c snippet_Cy_LIN_Sequence
 **
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_WriteData( LIN_CH_Type* base, const uint8_t *data, uint8_t dataLength );

/**
 *****************************************************************************
 ** \brief Enables LIN channel.
 **
 ** \param  base  [in]  Pointer to LIN instance register area.
 **
 ** \retval Refer \ref cy_en_lin_status_t
 **
 ** \funcusage
 ** \snippet lin/snippet/main.c snippet_Cy_LIN_Enable
 **
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_Enable(LIN_CH_Type* base);

/**
 *****************************************************************************
 ** \brief Disables LIN channel.
 **        Disabling LIN channel causes clearing of non retained registers.
 **        e.g) CMD register, INTR register, STATUS register.
 **        This behavior can be used for re-initialization, after error or
 **        abort RX operation.
 **
 ** \param  base  [in]  Pointer to LIN instance register area.
 **
 ** \retval Refer \ref cy_en_lin_status_t
 **
 ** \funcusage
 ** \snippet lin/snippet/main.c snippet_Cy_LIN_Disable
 **
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_Disable(LIN_CH_Type* base);

/**
 *****************************************************************************
 ** \brief Sets LIN break/wakeup field length.
 **        Normally this I/F is used for detection of the wakeup pulse.
 **
 ** \param  base  [in]  Pointer to LIN instance register area.
 ** \param  length   [in]  Bit length of the break/wakeup field.
 **
 ** \retval Refer \ref cy_en_lin_status_t
 **
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_SetBreakWakeupFieldLength(LIN_CH_Type* base, uint8_t length);

/**
 *****************************************************************************
 ** \brief Sets LIN response field data length.
 **        Data is in Bytes and maximum data length is 8-bytes.
 **
 ** \param  base     [in]  Pointer to LIN instance register area.
 ** \param  length   [in]  Data length in byte
 **
 ** \retval Refer \ref cy_en_lin_status_t
 **
 ** \funcusage
 ** \snippet lin/snippet/main.c snippet_Cy_LIN_SetDataLength
 **
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_SetDataLength(LIN_CH_Type* base, uint8_t length);

/**
 *****************************************************************************
 ** \brief Sets LIN checksum type setting.
 **
 ** \param  base     [in]  Pointer to LIN instance register area.
 ** \param  type     [in]  Checksum type. Refer \ref cy_en_lin_checksum_type_t
 **
 ** \retval Refer \ref cy_en_lin_status_t
 **
 ** \funcusage
 ** \snippet lin/snippet/main.c snippet_Cy_LIN_SetChecksumType
 **
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_SetChecksumType(LIN_CH_Type* base, cy_en_lin_checksum_type_t type);

/**
 *****************************************************************************
 ** \brief Sets LIN operation command.
 **
 ** \note As a normal usage, following combinations are used.
 **       - Master
 **         Header TX only          : LIN_CMD_TX_HEADER
 **         Header TX & TX response : LIN_CMD_TX_HEADER_TX_RESPONSE
 **         Header TX & RX response : LIN_CMD_TX_HEADER_RX_RESPONSE
 **       - Slave
 **         Header RX               : LIN_CMD_RX_HEADER_RX_RESPONSE
 **         TX response             : LIN_CMD_TX_RESPONSE
 **         RX response             : Already set when header RX
 **         As a typical usage, RX response is always set at header RX phase.
 **       - Wakeup frame            : LIN_CMD_TX_WAKEUP
 **       Instead of above macro, you can use raw definition LIN_CH_CMD_*_Msk defined in IO header file.
 **
 ** \param  base     [in]  Pointer to LIN instance register area.
 ** \param  command  [in]  Required operation command. Refer \ref group_lin_cmd_macro
 **
 ** \retval Refer \ref cy_en_lin_status_t
 **
 ** \funcusage
 ** \snippet lin/snippet/main.c snippet_Cy_LIN_SetCmd
 **
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_SetCmd(LIN_CH_Type* base, uint32_t command);

/**
 *****************************************************************************
 ** \brief Sets LIN header for master tx header operation.
 **
 ** \param  base    [in]  Pointer to LIN instance register area.
 ** \param  id      [in]  ID value
 **
 ** \retval Refer \ref cy_en_lin_status_t
 **
 ** \funcusage
 ** \snippet lin/snippet/main.c snippet_Cy_LIN_SetHeader
 **
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_SetHeader(LIN_CH_Type* base, uint8_t id);

/**
 *****************************************************************************
 ** \brief Returns received LIN header.
 **
 ** \param  base    [in]  Pointer to LIN instance register area.
 ** \param  id      [out] Received ID value.
 ** \param  parity  [out] Received parity value.
 **                       Note that parity check is always done by HW automatically.
 **
 ** \retval Refer \ref cy_en_lin_status_t
 **
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_GetHeader(LIN_CH_Type* base, uint8_t *id, uint8_t *parity);

/**
 *****************************************************************************
 ** \brief Sets interrupt source to be accepted.
 **
 ** \param  base    [in]  Pointer to LIN instance register area.
 ** \param  mask    [in]  The mask with the OR of the interrupt source to be accepted.
 **                       See \ref group_lin_intr_mask_macro for the set of constants.
 **
 ** \retval Refer \ref cy_en_lin_status_t
 **
 ** \funcusage
 ** \snippet lin/snippet/main.c snippet_Cy_LIN_Sequence
 **
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_SetInterruptMask(LIN_CH_Type* base, uint32_t mask);

/**
 *****************************************************************************
 ** \brief Returns interrupt mask setting.
 **
 ** \param  base [in]  Pointer to LIN instance register area.
 ** \param  mask  [out] The mask with the OR of the interrupt source which is masked.
 **                       See \ref group_lin_intr_mask_macro for the set of constants.
 **
 ** \retval Refer \ref cy_en_lin_status_t
 **
 ** \funcusage
 ** \snippet lin/snippet/main.c snippet_Cy_LIN_Sequence
 **
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_GetInterruptMask(LIN_CH_Type* base, uint32_t *mask);

/**
 *****************************************************************************
 ** \brief Returns interrupt masked status.
 **
 ** \param  base    [in]  Pointer to LIN instance register area.
 ** \param  status  [out] The mask with the OR of the interrupt source which occurs.
 **                       See \ref group_lin_intr_mask_macro for the set of constants.
 **
 ** \retval Refer \ref cy_en_lin_status_t
 **
 ** \funcusage
 ** \snippet lin/snippet/main.c snippet_Cy_LIN_ISR
 **
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_GetInterruptMaskedStatus(LIN_CH_Type* base, uint32_t *status);

/**
 *****************************************************************************
 ** \brief Returns interrupt raw status.
 **
 ** \param  base    [in]  Pointer to LIN instance register area.
 ** \param  status  [out] The mask with the OR of the interrupt source which occurs.
 **                       See \ref group_lin_intr_mask_macro for the set of constants.
 **
 ** \retval Refer \ref cy_en_lin_status_t
 **
 ** \funcusage
 ** \snippet lin/snippet/main.c snippet_Cy_LIN_ISR
 **
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_GetInterruptStatus(LIN_CH_Type* base, uint32_t *status);

/**
 *****************************************************************************
 ** \brief Clears interrupt status.
 **
 ** \param  base [in]  Pointer to LIN instance register area.
 ** \param  mask    [in]  The mask with the OR of the interrupt source to be cleared.
 **                       See \ref group_lin_intr_mask_macro for the set of constants.
 **
 ** \retval Refer \ref cy_en_lin_status_t
 **
 ** \funcusage
 ** \snippet lin/snippet/main.c snippet_Cy_LIN_ISR
 **
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_ClearInterrupt(LIN_CH_Type* base, uint32_t mask);

/**
 *****************************************************************************
 ** \brief Returns LIN module status.
 **
 ** \param  base [in]  Pointer to LIN instance register area.
 ** \param  status  [out] LIN module status.
 **
 ** \retval Refer \ref cy_en_lin_status_t
 **
 ** \funcusage
 ** \snippet lin/snippet/main.c snippet_Cy_LIN_ISR
 **
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_GetStatus(LIN_CH_Type* base, uint32_t *status);

/**
 *****************************************************************************
 ** \brief  Enables LIN channel 'en' out.
 **
 ** If linTransceiverAutoEnable in cy_stc_lin_config_t config structure is set to true
 ** then transceiver is set automatically and user need not call this function,
 ** else user has to call Cy_Status_EnOut_Enable() before sending a message and call
 ** Cy_Status_EnOut_Disable() after sending the message.
 **
 ** \param  base [in]  Pointer to LIN instance register area.
 **
 ** \retval Refer \ref cy_en_lin_status_t
 **
 ** \funcusage
 ** \snippet lin/snippet/main.c snippet_Cy_LIN_Init_Example
 **
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_EnOut_Enable(LIN_CH_Type* base);

/**
 *****************************************************************************
 ** \brief  Disables LIN channel 'en' out.
 **
 ** If linTransceiverAutoEnable in cy_stc_lin_config_t config structure is set to true
 ** then transceiver is set automatically and user need not call this function,
 ** else user has to call Cy_Status_EnOut_Enable() before sending a message and call
 ** Cy_Status_EnOut_Disable() after sending the message.
 **
 ** \param  base [in]  Pointer to LIN instance register area.
 **
 ** \retval Refer \ref cy_en_lin_status_t
 **
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_EnOut_Disable(LIN_CH_Type* base);

/**
 *****************************************************************************
 ** \brief  Enables LIN Testing mode.
 **
 ** This testing functionality simplifies SW development,
 ** but may also be used in the field to verify correct channel functionality.
 **
 ** \param  base [in]  Pointer to LIN instance register area.
 ** \param  lin_test_config [in] pointer to Test configuration structure.
 **
 ** \retval Refer \ref cy_en_lin_status_t
 **
 ** \funcusage
 ** \snippet lin/snippet/main.c snippet_Cy_LIN_Init_Example
 **
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_TestMode_Enable(LIN_Type* base, const cy_stc_lin_test_config_t* lin_test_config);

/**
 *****************************************************************************
 ** \brief  Disables LIN Testing mode.
 **
 ** This testing functionality simplifies SW development,
 ** but may also be used in the field to verify correct channel functionality.
 **
 ** \param  base [in]  Pointer to LIN instance register area.
 **
 ** \retval Refer \ref cy_en_lin_status_t
 **
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_TestMode_Disable(LIN_Type* base);

/**
 *****************************************************************************
 ** \brief  Enables LIN ERROR CTL.
 **
 ** Enables HW injected channel transmitter errors.
 ** The receiver should detect these errors and report these errors through activation of corresponding interrupt causes.
 **
 ** \param  base [in]  Pointer to LIN instance register area.
 ** \param  test_error_config [in] pointer to Test Error configuration structure.
 **
 ** \retval Refer \ref cy_en_lin_status_t
 **
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_ErrCtl_Enable(LIN_Type* base, cy_stc_lin_test_error_config_t* test_error_config);

/**
 *****************************************************************************
 ** \brief  Disables LIN ERROR CTL.
 **
 ** Disables HW injected channel transmitter errors.
 **
 ** \param  base [in]  Pointer to LIN instance register area.
 **
 ** \retval Refer \ref cy_en_lin_status_t
 **
 *****************************************************************************/
cy_en_lin_status_t Cy_LIN_ErrCtl_Disable(LIN_Type* base);


/** \} group_lin_functions */
/** @} */

#ifdef __cplusplus
}
#endif
#endif /*(CY_IP_MXLIN) */
#endif /* __CY_LIN_H__ */

/** \} group_lin */

/*****************************************************************************/
/* EOF (not truncated)                                                       */
/*****************************************************************************/
