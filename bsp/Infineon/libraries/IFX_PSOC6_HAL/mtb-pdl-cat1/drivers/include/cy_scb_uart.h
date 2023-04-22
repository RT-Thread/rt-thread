/***************************************************************************//**
* \file cy_scb_uart.h
* \version 3.0
*
* Provides UART API declarations of the SCB driver.
*
********************************************************************************
* \copyright
* Copyright 2016-2021 Cypress Semiconductor Corporation
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

/**
* \addtogroup group_scb_uart
* \{
* Driver API for UART
*
* The functions and other declarations used in this part of the driver are in
* cy_scb_uart.h. You can also include cy_pdl.h to get access
* to all functions and declarations in the PDL.
*
* The Universal Asynchronous Receiver/Transmitter (UART) protocol is an
* asynchronous serial interface protocol. UART communication is typically
* point-to-point. The UART interface consists of two signals:
* * TX: Transmitter output
* * RX: Receiver input
*
* Additionally, two side-band signals are used to implement flow control in
* UART. Note that the flow control applies only to TX functionality.
* * Clear to Send (CTS): This is an input signal to the transmitter.
*   When active, it indicates that the slave is ready for the master to
*   transmit data.
* * Ready to Send (RTS): This is an output signal from the receiver. When
*   active, it indicates that the receiver is ready to receive data
*
* Features:
* * Supports UART protocol
*   * Standard UART
*   * Multi-processor mode
* * SmartCard (ISO7816) reader
* * IrDA
* * Data frame size programmable from 4 to 16 bits
* * Programmable number of STOP bits, which can be set in terms of half bit
*   periods between 1 and 4
* * Parity support (odd and even parity)
* * Median filter on Rx input
* * Programmable oversampling
* * Start skipping
*
********************************************************************************
* \section group_scb_uart_configuration Configuration Considerations
********************************************************************************
* The UART driver configuration can be divided to number of sequential
* steps listed below:
* * \ref group_scb_uart_config
* * \ref group_scb_uart_pins
* * \ref group_scb_uart_clock
* * \ref group_scb_uart_data_rate
* * \ref group_scb_uart_intr
* * \ref group_scb_uart_enable
*
* \note
* UART driver is built on top of the SCB hardware block. The SCB5 instance is
* used as an example for all code snippets. Modify the code to match your
* design.
*
********************************************************************************
* \subsection group_scb_uart_config Configure UART
********************************************************************************
* To set up the UART driver, provide the configuration parameters in the
* \ref cy_stc_scb_uart_config_t structure. For example: provide uartMode,
* oversample, dataWidth, enableMsbFirst, parity, and stopBits. The other
* parameters are optional. To initialize the driver, call \ref Cy_SCB_UART_Init
* function providing a pointer to the populated \ref cy_stc_scb_uart_config_t
* structure and the allocated \ref cy_stc_scb_uart_context_t structure.
*
* \snippet scb/uart_snippet/main.c UART_CFG
*
********************************************************************************
* \subsection group_scb_uart_pins Assign and Configure Pins
********************************************************************************
* Only dedicated SCB pins can be used for UART operation. The HSIOM
* register must be configured to connect dedicated SCB UART pins to the
* SCB block. Also, the UART output pins must be configured in Strong Drive
* Input Off mode and UART input pins in Digital High-Z:
*
* \snippet scb/uart_snippet/main.c UART_CFG_PINS
*
********************************************************************************
* \subsection group_scb_uart_clock Assign Clock Divider
********************************************************************************
* A clock source must be connected to the SCB block to oversample input and
* output signals, in this document this clock will be referred as clk_scb.
* You must use one of available integer or fractional dividers. Use the
* \ref group_sysclk driver API to do this.
*
* \snippet scb/uart_snippet/main.c UART_CFG_ASSIGN_CLOCK
*
********************************************************************************
* \subsection group_scb_uart_data_rate Configure Baud Rate
********************************************************************************
* To get the UART to operate with the desired baud rate, the clk_scb frequency
* and the oversample must be configured. Use the \ref group_sysclk driver API
* to configure clk_scb frequency. Set the <em><b>oversample parameter
* in configuration structure</b></em> to define the number of the SCB clocks
* within one UART bit-time.
*
* \snippet scb/uart_snippet/main.c UART_CFG_DATA_RATE
*
* <b>Refer to the technical reference manual (TRM) section UART sub-section
* Clocking and Oversampling to get information about how to configure the UART to run with
* desired baud rate.</b>
*
********************************************************************************
* \subsection group_scb_uart_intr Configure Interrupt
********************************************************************************
* The interrupt is optional for the UART operation. To configure interrupt
* the \ref Cy_SCB_UART_Interrupt function must be called in the interrupt
* handler for the selected SCB instance. Also, this interrupt must be enabled
* in the NVIC.
* The interrupt must be configured when \ref group_scb_uart_hl will be used.
*
* \snippet scb/uart_snippet/main.c UART_INTR_A
* \snippet scb/uart_snippet/main.c UART_INTR_B
*
********************************************************************************
* \subsection group_scb_uart_enable Enable UART
********************************************************************************
* Finally, enable the UART operation by calling \ref Cy_SCB_UART_Enable.
*
* \snippet scb/uart_snippet/main.c UART_ENABLE
*
********************************************************************************
* \section group_scb_uart_use_cases Common Use Cases
********************************************************************************
* The UART API is divided into two categories: \ref group_scb_uart_low_level_functions
* and \ref group_scb_uart_high_level_functions. \n
* <em>Do not mix <b>High-Level</b> and <b>Low-Level</b> API because a Low-Level
* API can adversely affect the operation of a High-Level API.</em>
*
********************************************************************************
* \subsection group_scb_uart_ll Low-Level API
********************************************************************************
* The \ref group_scb_uart_low_level_functions functions allow
* interacting directly with the hardware and do not use \ref Cy_SCB_UART_Interrupt.
* These functions do not require context for operation. Thus, NULL can be
* passed for context parameter in \ref Cy_SCB_UART_Init and \ref Cy_SCB_UART_Disable
* instead of a pointer to the context structure.
*
* * To write data into the TX FIFO, use one of the provided functions:
*   \ref Cy_SCB_UART_Put, \ref Cy_SCB_UART_PutArray,
*   \ref Cy_SCB_UART_PutArrayBlocking or \ref Cy_SCB_UART_PutString.
*   Note that putting data into the TX FIFO starts data transfer.
*
* * To read data from the RX FIFO, use one of the provided functions:
*   \ref Cy_SCB_UART_Get, \ref Cy_SCB_UART_GetArray or
*   \ref Cy_SCB_UART_GetArrayBlocking.
*
* * The statuses can be polled using: \ref Cy_SCB_UART_GetRxFifoStatus and
*   \ref Cy_SCB_UART_GetTxFifoStatus.
*   <em>The statuses are <b>W1C (Write 1 to Clear)</b> and after a status
*   is set, it must be cleared.</em> Note that there are statuses evaluated as level.
*   These statuses remain set until an event is true. Therefore, after the clear
*   operation, the status is cleared but then it is restored (if event is still
*   true).
*   Also, the following functions can be used for polling as well
*   \ref Cy_SCB_UART_IsTxComplete, \ref Cy_SCB_UART_GetNumInRxFifo and
*   \ref Cy_SCB_UART_GetNumInTxFifo.
*
* \snippet scb/uart_snippet/main.c UART_TRANSMIT_DATA_LL
*
********************************************************************************
* \subsection group_scb_uart_hl High-Level API
********************************************************************************
* The \ref group_scb_uart_high_level_functions API use \ref Cy_SCB_UART_Interrupt
* to execute the transfer. Call \ref Cy_SCB_UART_Transmit to start transmission.
* Call \ref Cy_SCB_UART_Receive to start receive operation. After the
* operation is started the \ref Cy_SCB_UART_Interrupt handles the data
* transfer until its completion.
* Therefore \ref Cy_SCB_UART_Interrupt must be called inside the user
* interrupt handler to make the High-Level API work. To monitor status
* of transmit operation, use \ref Cy_SCB_UART_GetTransmitStatus and
* \ref Cy_SCB_UART_GetReceiveStatus to monitor receive status appropriately.
* Alternatively use \ref Cy_SCB_UART_RegisterCallback to register callback
* function to be notified about \ref group_scb_uart_macros_callback_events.
*
* <b>Receive Operation</b>
* \snippet scb/uart_snippet/main.c UART_RECEIVE_DATA_HL
*
* <b>Transmit Operation</b>
* \snippet scb/uart_snippet/main.c UART_TRANSMIT_DATA_HL
*
* There is also capability to insert a receive ring buffer that operates between
* the RX FIFO and the user buffer. The received data is copied into the ring
* buffer from the RX FIFO. This process runs in the background after the ring
* buffer operation is started by \ref Cy_SCB_UART_StartRingBuffer.
* When \ref Cy_SCB_UART_Receive is called, it first reads data from the ring
* buffer and then sets up an interrupt to receive more data if the required
* amount has not yet been read.
*
********************************************************************************
* \section group_scb_uart_dma_trig DMA Trigger
********************************************************************************
* The SCB provides TX and RX output trigger signals that can be routed to the
* DMA controller inputs. These signals are assigned based on the data availability
* in the TX and RX FIFOs appropriately.
*
* * The RX trigger signal is active while the number of data
*   elements in the RX FIFO is greater than the value of RX FIFO level. Use
*   function \ref Cy_SCB_SetRxFifoLevel or set configuration structure
*   rxFifoTriggerLevel parameter to configure RX FIFO level value. \n
*   <em>For example, the RX FIFO has 8 data elements and the RX FIFO level is 0.
*   The RX trigger signal is active until DMA reads all data from
*   the RX FIFO.</em>
*
* * The TX trigger signal is active while the number of data elements
*   in the TX FIFO is less than the value of TX FIFO level. Use function
*   \ref Cy_SCB_SetTxFifoLevel or set configuration structure txFifoTriggerLevel
*   parameter to configure TX FIFO level value. \n
*   <em>For example, the TX FIFO has 0 data elements (empty) and the TX FIFO level
*   is 7. The TX trigger signal is active until DMA loads TX FIFO
*   with 8 data elements (note that after the first TX load operation, the data
*   element goes to the shift register and TX FIFO is empty).</em>
*
* To route SCB TX or RX trigger signals to DMA controller use \ref group_trigmux
* driver API.
*
* \note
* To properly handle DMA level request signal activation and de-activation from the SCB
* peripheral block the DMA Descriptor typically must be configured to re-trigger
* after 16 Clk_Slow cycles.
*
********************************************************************************
* \section group_scb_uart_lp Low Power Support
********************************************************************************
* The UART driver provides callback functions to handle power mode
* transition. The callback \ref Cy_SCB_UART_DeepSleepCallback must be called
* during execution of \ref Cy_SysPm_CpuEnterDeepSleep \ref Cy_SCB_UART_HibernateCallback
* must be called during execution of \ref Cy_SysPm_SystemEnterHibernate. To trigger the
* callback execution, the callback must be registered before calling the
* power mode transition function. Refer to \ref group_syspm driver for more
* information about power mode transitions and callback registration.
*
* The UART is disabled during Deep Sleep and Hibernate and stops driving
* the output pins. The state of the UART output pins TX and RTS is High-Z,
* which can cause unexpected behavior of the UART receiver due to possible
* glitches on these lines. These pins must be set to the inactive state before
* entering Deep Sleep or Hibernate mode.
* These pins must keep the inactive level (the same state
* when UART TX is enabled and does not transfer data) before entering Deep
* Sleep or Hibernate mode. To do that, write the GPIO data register of each pin
* to the inactive level for each output pin. Then configure High-Speed Input
* Output Multiplexer (HSIOM) of each pin to be controlled by the GPIO (use
* \ref group_gpio driver API). After exiting Deep Sleep mode the UART
* must be enabled and the pins configuration restored to return the
* UART control of the pins (after exiting Hibernate mode, the
* system initialization code does the same). Copy either or
* both \ref Cy_SCB_UART_DeepSleepCallback and \ref Cy_SCB_UART_HibernateCallback
* as appropriate, and make the changes described above inside the function.
* Alternately, external pull-up or pull-down resistors can be connected
* to the appropriate UART lines to keep them inactive during Deep-Sleep or
* Hibernate.
*
* \defgroup group_scb_uart_macros Macros
* \defgroup group_scb_uart_functions Functions
* \{
* \defgroup group_scb_uart_general_functions General
* \defgroup group_scb_uart_high_level_functions High-Level
* \defgroup group_scb_uart_low_level_functions Low-Level
* \defgroup group_scb_uart_interrupt_functions Interrupt
* \defgroup group_scb_uart_low_power_functions Low Power Callbacks
* \}
* \defgroup group_scb_uart_data_structures Data Structures
* \defgroup group_scb_uart_enums Enumerated Types
*/

#if !defined(CY_SCB_UART_H)
#define CY_SCB_UART_H

#include "cy_device.h"

#if (defined (CY_IP_MXSCB) || defined (CY_IP_MXS22SCB))

#include "cy_scb_common.h"

#if defined(__cplusplus)
extern "C" {
#endif

/***************************************
*          Enumerated Types
***************************************/

/**
* \addtogroup group_scb_uart_enums
* \{
*/

/** UART status codes */
typedef enum
{
    /** Operation completed successfully */
    CY_SCB_UART_SUCCESS = 0U,

    /** One or more of input parameters are invalid */
    CY_SCB_UART_BAD_PARAM = (CY_SCB_ID | CY_PDL_STATUS_ERROR | CY_SCB_UART_ID | 1U),

    /**
    * The UART is busy processing a receive operation.
    */
    CY_SCB_UART_RECEIVE_BUSY = (CY_SCB_ID | CY_PDL_STATUS_ERROR | CY_SCB_UART_ID | 2U),

    /**
    * The UART is busy processing a transmit operation.
    */
    CY_SCB_UART_TRANSMIT_BUSY = (CY_SCB_ID | CY_PDL_STATUS_ERROR | CY_SCB_UART_ID | 3U)
} cy_en_scb_uart_status_t;

/** UART Mode */
typedef enum
{
    CY_SCB_UART_STANDARD  = 0U, /**< Configures the SCB for Standard UART operation */
    CY_SCB_UART_SMARTCARD = 1U, /**< Configures the SCB for SmartCard operation */
    CY_SCB_UART_IRDA      = 2U, /**< Configures the SCB for IrDA operation */
} cy_en_scb_uart_mode_t;

/** UART Stop Bits */
typedef enum
{
    CY_SCB_UART_STOP_BITS_1   = 2U,  /**< UART looks for 1 Stop Bit    */
    CY_SCB_UART_STOP_BITS_1_5 = 3U,  /**< UART looks for 1.5 Stop Bits */
    CY_SCB_UART_STOP_BITS_2   = 4U,  /**< UART looks for 2 Stop Bits   */
    CY_SCB_UART_STOP_BITS_2_5 = 5U,  /**< UART looks for 2.5 Stop Bits */
    CY_SCB_UART_STOP_BITS_3   = 6U,  /**< UART looks for 3 Stop Bits   */
    CY_SCB_UART_STOP_BITS_3_5 = 7U,  /**< UART looks for 3.5 Stop Bits */
    CY_SCB_UART_STOP_BITS_4   = 8U,  /**< UART looks for 4 Stop Bits   */
} cy_en_scb_uart_stop_bits_t;

/** UART Parity */
typedef enum
{
    CY_SCB_UART_PARITY_NONE = 0U,    /**< UART has no parity check   */
    CY_SCB_UART_PARITY_EVEN = 2U,    /**< UART has even parity check */
    CY_SCB_UART_PARITY_ODD  = 3U,    /**< UART has odd parity check  */
} cy_en_scb_uart_parity_t;

/** UART Polarity */
typedef enum
{
    CY_SCB_UART_ACTIVE_LOW  = 0U,   /**< Signal is active low */
    CY_SCB_UART_ACTIVE_HIGH = 1U,   /**< Signal is active high */
} cy_en_scb_uart_polarity_t;
/** \} group_scb_uart_enums */


/*******************************************************************************
*                           Type Definitions
*******************************************************************************/

/**
* \addtogroup group_scb_uart_data_structures
* \{
*/

/**
* Provides the typedef for the callback function called in the
* \ref Cy_SCB_UART_Interrupt to notify the user about occurrences of
* \ref group_scb_uart_macros_callback_events.
*/
typedef void (* cy_cb_scb_uart_handle_events_t)(uint32_t event);

/** UART configuration structure */
typedef struct stc_scb_uart_config
{
    /** Specifies the UART's mode of operation */
    cy_en_scb_uart_mode_t    uartMode;

    /**
    * Oversample factor for UART.
    * * The UART baud rate is the SCB Clock frequency / oversample
    *  (valid range is 8-16).
    * * For IrDA, the oversample is always 16, unless
    * \ref irdaEnableLowPowerReceiver is enabled. Then the oversample is
    * reduced to the \ref group_scb_uart_macros_irda_lp_ovs set.
    */
    uint32_t    oversample;

    /** The width of UART data (valid range is 5 to 9) */
    uint32_t    dataWidth;

    /**
    * Enables the hardware to shift out data element MSB first; otherwise,
    * LSB first
    */
    bool        enableMsbFirst;

    /**
    * Specifies the number of stop bits in the UART transaction, in half-bit
    * increments
    */
    cy_en_scb_uart_stop_bits_t    stopBits;

    /** Configures the UART parity */
    cy_en_scb_uart_parity_t    parity;

    /**
    * Enables a digital 3-tap median filter (2 out of 3 voting) to be applied
    * to the input of the RX FIFO to filter glitches on the line (for IrDA,
    * this parameter is ignored)
    *
    */
    bool        enableInputFilter;

    /**
    * Enables the hardware to drop data in the RX FIFO when a parity error is
    * detected
    */
    bool        dropOnParityError;

    /**
    * Enables the hardware to drop data in the RX FIFO when a frame error is
    * detected
    */
    bool        dropOnFrameError;

    /**
    * Enables the UART operation in Multi-Processor mode which requires
    * dataWidth to be 9 bits (the 9th bit is used to indicate address byte)
    */
    bool        enableMutliProcessorMode;

    /**
    * If Multi Processor mode is enabled, this is the address of the RX
    * FIFO. If the address matches, data is accepted into the FIFO. If
    * it does not match, the data is ignored.
    */
    uint32_t    receiverAddress;

    /**
    * This is the address mask for the Multi Processor address. 1 indicates
    * that the incoming address must match the corresponding bit in the slave
    * address. A 0 in the mask indicates that the incoming address does
    * not need to match.
    */
    uint32_t    receiverAddressMask;

    /**
    * Enables the hardware to accept the matching address in the RX FIFO.
    * This is useful when the device supports more than one address.
    */
    bool        acceptAddrInFifo;

    /** Inverts the IrDA RX input */
    bool        irdaInvertRx;

    /**
    * Enables the low-power receive for IrDA mode.
    * Note that the transmission must be disabled if this mode is enabled.
    */
    bool        irdaEnableLowPowerReceiver;

    /**
    * Enables retransmission of the frame placed in the TX FIFO when
    * NACK is received in SmartCard mode (for Standard and IrDA , this parameter
    * is ignored)
    */
    bool        smartCardRetryOnNack;

    /**
    * Enables the usage of the CTS input signal for the transmitter. The
    * transmitter waits for CTS to be active before sending data
    */
    bool        enableCts;

    /** Sets the CTS Polarity */
    cy_en_scb_uart_polarity_t    ctsPolarity;

    /**
    * When the RX FIFO has fewer entries than rtsRxFifoLevel, the
    * RTS signal is active (note to disable RTS, set this field to zero)
    */
    uint32_t    rtsRxFifoLevel;

    /** Sets the RTS Polarity */
    cy_en_scb_uart_polarity_t    rtsPolarity;

    /** Specifies the number of bits to detect a break condition */
    uint32_t    breakWidth;
#if(((CY_IP_MXSCB_VERSION>=2) || defined (CY_IP_MXS22SCB)) || defined (CY_DOXYGEN))
    /** Specifies the low or high level pulse detection for break condition */
    /**
    * \note
    * This parameter is available for CAT1B and CAT1C devices.
    **/
    bool        breaklevel;
#endif /* (((CY_IP_MXSCB_VERSION>=2) || defined (CY_IP_MXS22SCB)) || defined (CY_DOXYGEN)) */
    /**
    * When there are more entries in the RX FIFO than this level
    * the RX trigger output goes high. This output can be connected
    * to a DMA channel through a trigger mux.
    * Also, it controls the \ref CY_SCB_UART_RX_TRIGGER interrupt source.
    */
    uint32_t    rxFifoTriggerLevel;

    /**
    * The bits set in this mask allow the event to cause an interrupt
    * (See \ref group_scb_uart_macros_rx_fifo_status for the set of constants)
    */
    uint32_t    rxFifoIntEnableMask;

    /**
    * When there are fewer entries in the TX FIFO then this level
    * the TX trigger output goes high. This output can be connected
    * to a DMA channel through a trigger mux.
    * Also, it controls \ref CY_SCB_UART_TX_TRIGGER interrupt source.
    */
    uint32_t    txFifoTriggerLevel;

    /**
    * Bits set in this mask allows the event to cause an interrupt
    * (See \ref group_scb_uart_macros_tx_fifo_status for the set of constants)
    */
    uint32_t    txFifoIntEnableMask;
} cy_stc_scb_uart_config_t;

/** UART context structure.
* All fields for the context structure are internal. Firmware never reads or
* writes these values. Firmware allocates the structure and provides the
* address of the structure to the driver in function calls. Firmware must
* ensure that the defined instance of this structure remains in scope
* while the drive is in use.
*/
typedef struct cy_stc_scb_uart_context
{
    /** \cond INTERNAL */
    uint32_t volatile txStatus;         /**< The transmit status */
    uint32_t volatile rxStatus;         /**< The receive status */

    void     *rxRingBuf;                /**< The pointer to the ring buffer */
    uint32_t  rxRingBufSize;            /**< The ring buffer size */
    uint32_t volatile rxRingBufHead;    /**< The ring buffer head index */
    uint32_t volatile rxRingBufTail;    /**< The ring buffer tail index */

    void     *rxBuf;                    /**< The pointer to the receive buffer */
    uint32_t  rxBufSize;                /**< The receive buffer size */
    uint32_t volatile rxBufIdx;         /**< The current location in the receive buffer */

    void     *txBuf;                    /**< The pointer to the transmit buffer */
    uint32_t  txBufSize;                /**< The transmit buffer size */
    uint32_t volatile txLeftToTransmit; /**< The number of data elements left to be transmitted */

    /**
    * Enables the low-power receive for IrDA mode.
    * Note that the transmission must be disabled if this mode is enabled.
    */
    bool irdaEnableLowPowerReceiver;

    /** The pointer to an event callback that is called when any of
    * \ref group_scb_uart_macros_callback_events occurs
    */
    cy_cb_scb_uart_handle_events_t cbEvents;

#if !defined(NDEBUG)
    uint32_t initKey;               /**< Tracks the context initialization */
#endif /* !(NDEBUG) */
    /** \endcond */
} cy_stc_scb_uart_context_t;
/** \} group_scb_uart_data_structures */


/*******************************************************************************
*                           Function Prototypes
*******************************************************************************/

/**
* \addtogroup group_scb_uart_general_functions
* \{
*/
cy_en_scb_uart_status_t Cy_SCB_UART_Init(CySCB_Type *base, cy_stc_scb_uart_config_t const *config,
                                         cy_stc_scb_uart_context_t *context);
void Cy_SCB_UART_DeInit (CySCB_Type *base);
__STATIC_INLINE void Cy_SCB_UART_Enable(CySCB_Type *base);
void Cy_SCB_UART_Disable(CySCB_Type *base, cy_stc_scb_uart_context_t *context);

__STATIC_INLINE void     Cy_SCB_UART_EnableCts      (CySCB_Type *base);
__STATIC_INLINE void     Cy_SCB_UART_DisableCts     (CySCB_Type *base);
__STATIC_INLINE void     Cy_SCB_UART_SetRtsFifoLevel(CySCB_Type *base, uint32_t level);
__STATIC_INLINE uint32_t Cy_SCB_UART_GetRtsFifoLevel(CySCB_Type const *base);

__STATIC_INLINE void Cy_SCB_UART_EnableSkipStart (CySCB_Type *base);
__STATIC_INLINE void Cy_SCB_UART_DisableSkipStart(CySCB_Type *base);
/** \} group_scb_uart_general_functions */

/**
* \addtogroup group_scb_uart_high_level_functions
* \{
*/
void     Cy_SCB_UART_StartRingBuffer   (CySCB_Type *base, void *buffer, uint32_t size,
                                        cy_stc_scb_uart_context_t *context);
void     Cy_SCB_UART_StopRingBuffer    (CySCB_Type *base, cy_stc_scb_uart_context_t *context);
uint32_t Cy_SCB_UART_GetNumInRingBuffer(CySCB_Type const *base, cy_stc_scb_uart_context_t const *context);
void     Cy_SCB_UART_ClearRingBuffer   (CySCB_Type const *base, cy_stc_scb_uart_context_t *context);

cy_en_scb_uart_status_t Cy_SCB_UART_Receive(CySCB_Type *base, void *buffer, uint32_t size,
                                            cy_stc_scb_uart_context_t *context);
void     Cy_SCB_UART_AbortReceive    (CySCB_Type *base, cy_stc_scb_uart_context_t *context);
uint32_t Cy_SCB_UART_GetReceiveStatus(CySCB_Type const *base, cy_stc_scb_uart_context_t const *context);
uint32_t Cy_SCB_UART_GetNumReceived  (CySCB_Type const *base, cy_stc_scb_uart_context_t const *context);

cy_en_scb_uart_status_t Cy_SCB_UART_Transmit(CySCB_Type *base, void *buffer, uint32_t size,
                                             cy_stc_scb_uart_context_t *context);
void     Cy_SCB_UART_AbortTransmit       (CySCB_Type *base, cy_stc_scb_uart_context_t *context);
uint32_t Cy_SCB_UART_GetTransmitStatus   (CySCB_Type const *base, cy_stc_scb_uart_context_t const *context);
uint32_t Cy_SCB_UART_GetNumLeftToTransmit(CySCB_Type const *base, cy_stc_scb_uart_context_t const *context);
/** \} group_scb_uart_high_level_functions */

/**
* \addtogroup group_scb_uart_low_level_functions
* \{
*/
__STATIC_INLINE uint32_t Cy_SCB_UART_Put             (CySCB_Type *base, uint32_t data);
__STATIC_INLINE uint32_t Cy_SCB_UART_PutArray        (CySCB_Type *base, void *buffer, uint32_t size);
__STATIC_INLINE void     Cy_SCB_UART_PutArrayBlocking(CySCB_Type *base, void *buffer, uint32_t size);
__STATIC_INLINE void     Cy_SCB_UART_PutString       (CySCB_Type *base, char_t const string[]);
void Cy_SCB_UART_SendBreakBlocking(CySCB_Type *base, uint32_t breakWidth);

__STATIC_INLINE uint32_t Cy_SCB_UART_Get             (CySCB_Type const *base);
__STATIC_INLINE uint32_t Cy_SCB_UART_GetArray        (CySCB_Type const *base, void *buffer, uint32_t size);
__STATIC_INLINE void     Cy_SCB_UART_GetArrayBlocking(CySCB_Type const *base, void *buffer, uint32_t size);

__STATIC_INLINE uint32_t Cy_SCB_UART_GetTxFifoStatus  (CySCB_Type const *base);
__STATIC_INLINE void     Cy_SCB_UART_ClearTxFifoStatus(CySCB_Type *base, uint32_t clearMask);

__STATIC_INLINE uint32_t Cy_SCB_UART_GetRxFifoStatus  (CySCB_Type const *base);
__STATIC_INLINE void     Cy_SCB_UART_ClearRxFifoStatus(CySCB_Type *base, uint32_t clearMask);

__STATIC_INLINE uint32_t Cy_SCB_UART_GetNumInTxFifo   (CySCB_Type const *base);
__STATIC_INLINE bool     Cy_SCB_UART_IsTxComplete     (CySCB_Type const *base);

__STATIC_INLINE uint32_t Cy_SCB_UART_GetNumInRxFifo   (CySCB_Type const *base);

__STATIC_INLINE void     Cy_SCB_UART_ClearRxFifo      (CySCB_Type *base);
__STATIC_INLINE void     Cy_SCB_UART_ClearTxFifo      (CySCB_Type *base);

__STATIC_INLINE uint32_t Cy_SCB_UART_GetOverSample(CySCB_Type const *base);
cy_en_scb_uart_status_t Cy_SCB_UART_SetOverSample(CySCB_Type *base, uint32_t overSample, cy_stc_scb_uart_context_t *context);

__STATIC_INLINE uint32_t Cy_SCB_UART_GetDataWidth(CySCB_Type const *base);
void Cy_SCB_UART_SetDataWidth(CySCB_Type *base, uint32_t dataWidth);

__STATIC_INLINE uint32_t Cy_SCB_UART_GetParity(CySCB_Type const *base);
void Cy_SCB_UART_SetParity(CySCB_Type *base, cy_en_scb_uart_parity_t parity);

__STATIC_INLINE uint32_t Cy_SCB_UART_GetStopBits(CySCB_Type const *base);
void Cy_SCB_UART_SetStopBits(CySCB_Type *base, cy_en_scb_uart_stop_bits_t stopBits);

__STATIC_INLINE bool Cy_SCB_UART_GetDropOnParityError(CySCB_Type const *base);
void Cy_SCB_UART_SetDropOnParityError(CySCB_Type *base, bool dropOnParityError);

__STATIC_INLINE bool Cy_SCB_UART_GetEnableMsbFirst(CySCB_Type const *base);
void Cy_SCB_UART_SetEnableMsbFirst(CySCB_Type *base, bool enableMsbFirst);
/** \} group_scb_uart_low_level_functions */

/**
* \addtogroup group_scb_uart_interrupt_functions
* \{
*/
void Cy_SCB_UART_Interrupt(CySCB_Type *base, cy_stc_scb_uart_context_t *context);

__STATIC_INLINE void Cy_SCB_UART_RegisterCallback(CySCB_Type const *base, cy_cb_scb_uart_handle_events_t callback,
                                                  cy_stc_scb_uart_context_t *context);
/** \} group_scb_uart_interrupt_functions */

/**
* \addtogroup group_scb_uart_low_power_functions
* \{
*/
cy_en_syspm_status_t Cy_SCB_UART_DeepSleepCallback(cy_stc_syspm_callback_params_t *callbackParams, cy_en_syspm_callback_mode_t mode);
cy_en_syspm_status_t Cy_SCB_UART_HibernateCallback(cy_stc_syspm_callback_params_t *callbackParams, cy_en_syspm_callback_mode_t mode);
/** \} group_scb_uart_low_power_functions */


/*******************************************************************************
*                               API Constants
*******************************************************************************/

/**
* \addtogroup group_scb_uart_macros
* \{
*/

/**
* \defgroup group_scb_uart_macros_irda_lp_ovs UART IRDA Low Power Oversample factors
* \{
*/
#define CY_SCB_UART_IRDA_LP_OVS16      (1UL)   /**< IrDA in low-power mode oversampled by 16   */
#define CY_SCB_UART_IRDA_LP_OVS32      (2UL)   /**< IrDA in low-power mode oversampled by 32   */
#define CY_SCB_UART_IRDA_LP_OVS48      (3UL)   /**< IrDA in low-power mode oversampled by 48   */
#define CY_SCB_UART_IRDA_LP_OVS96      (4UL)   /**< IrDA in low-power mode oversampled by 96   */
#define CY_SCB_UART_IRDA_LP_OVS192     (5UL)   /**< IrDA in low-power mode oversampled by 192  */
#define CY_SCB_UART_IRDA_LP_OVS768     (6UL)   /**< IrDA in low-power mode oversampled by 768  */
#define CY_SCB_UART_IRDA_LP_OVS1536    (7UL)   /**< IrDA in low-power mode oversampled by 1536 */
/** \} group_scb_uart_macros_irda_lp_ovs */

/**
* \defgroup group_scb_uart_macros_rx_fifo_status UART RX FIFO status.
* \{
* Macros to check UART RX FIFO status returned by \ref Cy_SCB_UART_GetRxFifoStatus
* function or assign mask for \ref Cy_SCB_UART_ClearRxFifoStatus function.
* Each UART RX FIFO status is encoded in a separate bit, therefore multiple
* bits may be set to indicate the current status.
*/

/** The number of entries in the RX FIFO is more than the RX FIFO trigger level
* value
*/
#define CY_SCB_UART_RX_TRIGGER         (SCB_INTR_RX_TRIGGER_Msk)

/** The RX FIFO is not empty, there is data to read */
#define CY_SCB_UART_RX_NOT_EMPTY       (SCB_INTR_RX_NOT_EMPTY_Msk)

/**
* The RX FIFO is full, there is no more space for additional data, and
* any additional data will be dropped
*/
#define CY_SCB_UART_RX_FULL            (SCB_INTR_RX_FULL_Msk)

/**
* The RX FIFO was full and there was an attempt to write to it.
* That additional data was dropped.
*/
#define CY_SCB_UART_RX_OVERFLOW        (SCB_INTR_RX_OVERFLOW_Msk)

/** An attempt to read from an empty RX FIFO */
#define CY_SCB_UART_RX_UNDERFLOW       (SCB_INTR_RX_UNDERFLOW_Msk)

/** The RX FIFO detected a frame error, either a stop or stop-bit error */
#define CY_SCB_UART_RX_ERR_FRAME       (SCB_INTR_RX_FRAME_ERROR_Msk)

/** The RX FIFO detected a parity error */
#define CY_SCB_UART_RX_ERR_PARITY      (SCB_INTR_RX_PARITY_ERROR_Msk)

/** The RX FIFO detected a break transmission from the transmitter */
#define CY_SCB_UART_RX_BREAK_DETECT    (SCB_INTR_RX_BREAK_DETECT_Msk)
/** \} group_scb_uart_macros_rx_fifo_status */

/**
* \defgroup group_scb_uart_macros_tx_fifo_status UART TX FIFO Statuses
* \{
* Macros to check UART TX FIFO status returned by \ref Cy_SCB_UART_GetTxFifoStatus
* function or assign mask for \ref Cy_SCB_UART_ClearTxFifoStatus function.
* Each UART TX FIFO status is encoded in a separate bit, therefore multiple bits
* may be set to indicate the current status.
*/

/** The number of entries in the TX FIFO is less than the TX FIFO trigger level
* value
*/
#define CY_SCB_UART_TX_TRIGGER     (SCB_INTR_TX_TRIGGER_Msk)

/** The TX FIFO is not full, there is a space for more data */
#define CY_SCB_UART_TX_NOT_FULL    (SCB_INTR_TX_NOT_FULL_Msk)

/** The TX FIFO is empty, note there may still be data in the shift register.*/
#define CY_SCB_UART_TX_EMPTY       (SCB_INTR_TX_EMPTY_Msk)

/** An attempt to write to the full TX FIFO */
#define CY_SCB_UART_TX_OVERFLOW    (SCB_INTR_TX_OVERFLOW_Msk)

/** An attempt to read from an empty transmitter FIFO (hardware reads). */
#define CY_SCB_UART_TX_UNDERFLOW (SCB_INTR_TX_UNDERFLOW_Msk)

/** All data has been transmitted out of the FIFO, including shifter */
#define CY_SCB_UART_TX_DONE        (SCB_INTR_TX_UART_DONE_Msk)

/** SmartCard only: the transmitter received a NACK */
#define CY_SCB_UART_TX_NACK        (SCB_INTR_TX_UART_NACK_Msk)

/** SmartCard only: the transmitter lost arbitration */
#define CY_SCB_UART_TX_ARB_LOST    (SCB_INTR_TX_UART_ARB_LOST_Msk)
/** \} group_scb_uart_macros_tx_fifo_status */

/**
* \defgroup group_scb_uart_macros_receive_status UART Receive Statuses
* \{
* Macros to check current UART receive status returned by
* \ref Cy_SCB_UART_GetReceiveStatus function.
* Each UART receive status is encoded in a separate bit, therefore multiple bits
* may be set to indicate the current status.
*/
/** The receive operation started by \ref Cy_SCB_UART_Receive is in progress */
#define CY_SCB_UART_RECEIVE_ACTIVE         (0x01UL)

/**
* The hardware RX FIFO was full and there was an attempt to write to it.
* That additional data was dropped.
*/
#define CY_SCB_UART_RECEIVE_OVERFLOW       (SCB_INTR_RX_OVERFLOW_Msk)

/** The receive hardware detected a frame error, either a start or
* stop bit error
*/
#define CY_SCB_UART_RECEIVE_ERR_FRAME      (SCB_INTR_RX_FRAME_ERROR_Msk)

/** The receive hardware detected a parity error */
#define CY_SCB_UART_RECEIVE_ERR_PARITY     (SCB_INTR_RX_PARITY_ERROR_Msk)

/** The receive hardware detected a break transmission from transmitter */
#define CY_SCB_UART_RECEIVE_BREAK_DETECT   (SCB_INTR_RX_BREAK_DETECT_Msk)
/** \} group_scb_uart_macros_receive_status */

/**
* \defgroup group_scb_uart_macros_transmit_status UART Transmit Status
* \{
* Macros to check current UART transmit status returned by
* \ref Cy_SCB_UART_GetTransmitStatus function.
* Each UART transmit status is encoded in a separate bit, therefore multiple bits
* may be set to indicate the current status.
*/

/** The transmit operation started by \ref Cy_SCB_UART_Transmit is in progress */
#define CY_SCB_UART_TRANSMIT_ACTIVE    (0x01UL)

/**
* All data elements specified by \ref Cy_SCB_UART_Transmit have been loaded
* into the TX FIFO
*/
#define CY_SCB_UART_TRANSMIT_IN_FIFO   (0x02UL)

/** SmartCard only: the transmitter received a NACK */
#define CY_SCB_UART_TRANSMIT_NACK      (SCB_INTR_TX_UART_NACK_Msk)

/** SmartCard only: the transmitter lost arbitration */
#define CY_SCB_UART_TRANSMIT_ARB_LOST  (SCB_INTR_TX_UART_ARB_LOST_Msk)
/** \} group_scb_uart_macros_transmit_status */

/**
* \defgroup group_scb_uart_macros_callback_events UART Callback Events
* \{
* Macros to check UART events passed by \ref cy_cb_scb_uart_handle_events_t callback.
* Note that only single event is notified by the callback when it is called.
*/

/**
* All data elements specified by \ref Cy_SCB_UART_Transmit have been loaded
* into the TX FIFO
*/
#define CY_SCB_UART_TRANSMIT_IN_FIFO_EVENT (0x01UL)

/** The transmit operation started by \ref Cy_SCB_UART_Transmit is complete */
#define CY_SCB_UART_TRANSMIT_DONE_EVENT    (0x02UL)

/** The receive operation started by \ref Cy_SCB_UART_Receive is complete */
#define CY_SCB_UART_RECEIVE_DONE_EVENT     (0x04UL)

/**
* The ring buffer is full, there is no more space for additional data.
* Additional data is stored in the RX FIFO until it becomes full, at which
* point data is dropped.
*/
#define CY_SCB_UART_RB_FULL_EVENT          (0x08UL)

/**
* An error was detected during the receive operation. This includes overflow,
* frame error, or parity error. Check \ref Cy_SCB_UART_GetReceiveStatus to
* determine the source of the error.
*/
#define CY_SCB_UART_RECEIVE_ERR_EVENT      (0x10UL)

/**
* An error was detected during the transmit operation. This includes a NACK
* or lost arbitration. Check \ref Cy_SCB_UART_GetTransmitStatus to determine
* the source of the error
*/
#define CY_SCB_UART_TRANSMIT_ERR_EVENT     (0x20UL)

/** The receive fifo is not empty. To use this event the \ref CY_SCB_RX_INTR_NOT_EMPTY interrupt must be enabled by the user. */
#define CY_SCB_UART_RECEIVE_NOT_EMTPY       (0x40UL)

/** The transmit fifo is empty. To use this event the \ref CY_SCB_UART_TX_EMPTY interrupt must be enabled by the user. */
#define CY_SCB_UART_TRANSMIT_EMTPY          (0x80UL)
/** \} group_scb_uart_macros_callback_events */


/** Data returned by the hardware when an empty RX FIFO is read */
#define CY_SCB_UART_RX_NO_DATA         (0xFFFFFFFFUL)


/*******************************************************************************
*                            Internal Constants
*******************************************************************************/

/** \cond INTERNAL */
#define CY_SCB_UART_TX_INTR_MASK    (CY_SCB_UART_TX_TRIGGER  | CY_SCB_UART_TX_NOT_FULL  | CY_SCB_UART_TX_EMPTY | \
                                     CY_SCB_UART_TX_OVERFLOW | CY_SCB_UART_TX_UNDERFLOW | CY_SCB_UART_TX_DONE  | \
                                     CY_SCB_UART_TX_NACK     | CY_SCB_UART_TX_ARB_LOST)

#define CY_SCB_UART_RX_INTR_MASK    (CY_SCB_UART_RX_TRIGGER    | CY_SCB_UART_RX_NOT_EMPTY | CY_SCB_UART_RX_FULL      | \
                                     CY_SCB_UART_RX_OVERFLOW   | CY_SCB_UART_RX_UNDERFLOW | CY_SCB_UART_RX_ERR_FRAME | \
                                     CY_SCB_UART_RX_ERR_PARITY | CY_SCB_UART_RX_BREAK_DETECT)

#define CY_SCB_UART_TX_INTR        (CY_SCB_TX_INTR_LEVEL | CY_SCB_TX_INTR_UART_NACK | CY_SCB_TX_INTR_UART_ARB_LOST)

#define CY_SCB_UART_RX_INTR        (CY_SCB_RX_INTR_LEVEL | CY_SCB_RX_INTR_OVERFLOW | CY_SCB_RX_INTR_UART_FRAME_ERROR | \
                                    CY_SCB_RX_INTR_UART_PARITY_ERROR | CY_SCB_RX_INTR_UART_BREAK_DETECT)

#define CY_SCB_UART_RECEIVE_ERR    (CY_SCB_RX_INTR_OVERFLOW | CY_SCB_RX_INTR_UART_FRAME_ERROR | \
                                    CY_SCB_RX_INTR_UART_PARITY_ERROR)

#define CY_SCB_UART_TRANSMIT_ERR   (CY_SCB_TX_INTR_UART_NACK | CY_SCB_TX_INTR_UART_ARB_LOST)

#define CY_SCB_UART_INIT_KEY       (0x00ABCDEFUL)

#define CY_SCB_UART_IS_MODE_VALID(mode)     ( (CY_SCB_UART_STANDARD  == (mode)) || \
                                              (CY_SCB_UART_SMARTCARD == (mode)) || \
                                              (CY_SCB_UART_IRDA      == (mode)) )

#define CY_SCB_UART_IS_STOP_BITS_VALID(stopBits)    ( (CY_SCB_UART_STOP_BITS_1   == (stopBits)) || \
                                                      (CY_SCB_UART_STOP_BITS_1_5 == (stopBits)) || \
                                                      (CY_SCB_UART_STOP_BITS_2   == (stopBits)) || \
                                                      (CY_SCB_UART_STOP_BITS_2_5 == (stopBits)) || \
                                                      (CY_SCB_UART_STOP_BITS_3   == (stopBits)) || \
                                                      (CY_SCB_UART_STOP_BITS_3_5 == (stopBits)) || \
                                                      (CY_SCB_UART_STOP_BITS_4   == (stopBits)) )

#define CY_SCB_UART_IS_PARITY_VALID(parity)         ( (CY_SCB_UART_PARITY_NONE == (parity)) || \
                                                      (CY_SCB_UART_PARITY_EVEN == (parity)) || \
                                                      (CY_SCB_UART_PARITY_ODD  == (parity)) )

#define CY_SCB_UART_IS_POLARITY_VALID(polarity)     ( (CY_SCB_UART_ACTIVE_LOW  == (polarity)) || \
                                                      (CY_SCB_UART_ACTIVE_HIGH == (polarity)) )

#define CY_SCB_UART_IS_IRDA_LP_OVS_VALID(ovs)       ( (CY_SCB_UART_IRDA_LP_OVS16   == (ovs)) || \
                                                      (CY_SCB_UART_IRDA_LP_OVS32   == (ovs)) || \
                                                      (CY_SCB_UART_IRDA_LP_OVS48   == (ovs)) || \
                                                      (CY_SCB_UART_IRDA_LP_OVS96   == (ovs)) || \
                                                      (CY_SCB_UART_IRDA_LP_OVS192  == (ovs)) || \
                                                      (CY_SCB_UART_IRDA_LP_OVS768  == (ovs)) || \
                                                      (CY_SCB_UART_IRDA_LP_OVS1536 == (ovs)) )

#define CY_SCB_UART_IS_ADDRESS_VALID(addr)          ((addr) <= 0xFFUL)
#define CY_SCB_UART_IS_ADDRESS_MASK_VALID(mask)     ((mask) <= 0xFFUL)
#define CY_SCB_UART_IS_DATA_WIDTH_VALID(width)      ( ((width) >= 5UL) && ((width) <= 9UL) )
#define CY_SCB_UART_IS_OVERSAMPLE_VALID(ovs, mode, lpRx)    ( ((CY_SCB_UART_STANDARD  == (mode)) || (CY_SCB_UART_SMARTCARD == (mode))) ? \
                                                              (((ovs) >= 8UL) && ((ovs) <= 16UL)) :                                      \
                                                              (bool) ((lpRx) ? CY_SCB_UART_IS_IRDA_LP_OVS_VALID(ovs) : true) )

#define CY_SCB_UART_IS_RX_BREAK_WIDTH_VALID(base, width)    ( ((width) >= (_FLD2VAL(SCB_RX_CTRL_DATA_WIDTH, (base)->RX_CTRL) + 3UL)) && \
                                                              ((width) <= 16UL) )
#define CY_SCB_UART_IS_TX_BREAK_WIDTH_VALID(width)          ( ((width) >= 4UL) && ((width) <= 16UL) )

#define CY_SCB_UART_IS_MUTLI_PROC_VALID(mp, mode, width, parity)    ( (mp) ? ((CY_SCB_UART_STANDARD  == (mode)) && ((width) == 9UL) && \
                                                                              (CY_SCB_UART_PARITY_NONE == (parity))) : true)
/** \endcond */

/** \} group_scb_uart_macros */


/*******************************************************************************
*                    In-line Function Implementation
*******************************************************************************/

/**
* \addtogroup group_scb_uart_general_functions
* \{
*/

/*******************************************************************************
* Function Name: Cy_SCB_UART_Enable
****************************************************************************//**
*
* Enables the SCB block for the UART operation.
*
* \param base
* The pointer to the UART SCB instance.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_UART_Enable(CySCB_Type *base)
{
    SCB_CTRL(base) |= SCB_CTRL_ENABLED_Msk;
}


/*******************************************************************************
* Function Name: Cy_SCB_UART_EnableCts
****************************************************************************//**
*
* Enables the Clear to Send (CTS) input for the UART. The UART will not transmit
* data while this signal is inactive.
*
* \param base
* The pointer to the UART SCB instance.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_UART_EnableCts(CySCB_Type *base)
{
    SCB_UART_FLOW_CTRL(base) |= SCB_UART_FLOW_CTRL_CTS_ENABLED_Msk;
}


/*******************************************************************************
* Function Name: Cy_SCB_UART_DisableCts
****************************************************************************//**
*
* Disables the Clear to Send (CTS) input for the UART.
* See \ref Cy_SCB_UART_EnableCts for the details.
*
* \param base
* The pointer to the UART SCB instance.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_UART_DisableCts(CySCB_Type *base)
{
    SCB_UART_FLOW_CTRL(base) &= (uint32_t) ~SCB_UART_FLOW_CTRL_CTS_ENABLED_Msk;
}


/*******************************************************************************
* Function Name: Cy_SCB_UART_SetRtsFifoLevel
****************************************************************************//**
*
* Sets a level for the Ready To Send (RTS) signal activation.
* When the number of data elements in the receive FIFO is below this level,
* then the RTS output is active. Otherwise, the RTS signal is inactive.
* To disable the RTS signal generation, set this level to zero.
*
* \param base
* The pointer to the UART SCB instance.
*
* \param level
* The level in the RX FIFO for RTS signal activation.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_UART_SetRtsFifoLevel(CySCB_Type *base, uint32_t level)
{
    CY_ASSERT_L2(CY_SCB_IS_TRIGGER_LEVEL_VALID(base, level));

    CY_REG32_CLR_SET(SCB_UART_FLOW_CTRL(base), SCB_UART_FLOW_CTRL_TRIGGER_LEVEL, level);
}


/*******************************************************************************
* Function Name: Cy_SCB_UART_GetRtsFifoLevel
****************************************************************************//**
*
* Returns the level in the RX FIFO for the RTS signal activation.
*
* \param base
* The pointer to the UART SCB instance.
*
* \return
* The level in the RX FIFO for RTS signal activation.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_UART_GetRtsFifoLevel(CySCB_Type const *base)
{
    return _FLD2VAL(SCB_UART_FLOW_CTRL_TRIGGER_LEVEL, SCB_UART_FLOW_CTRL(base));
}


/*******************************************************************************
* Function Name: Cy_SCB_UART_EnableSkipStart
****************************************************************************//**
*
* Enables the skip start-bit functionality.
* When skip start is enabled the UART hardware does not synchronize to a
* start bit but synchronizes to the first rising edge. To create a rising edge,
* the first data bit must be a 1. This feature is useful when the start bit
* falling edge is used to wake the device through a GPIO interrupt.
*
* \param base
* The pointer to the UART SCB instance.
*
* \note
* When skip start-bit feature is enabled, it is applied (UART synchronizes
* to the first rising edge after start bit) whenever the SCB is enabled.
* This can cause incorrect UART synchronization and data reception when
* the first data bit is not a 1. Therefore, disable the skip start-bit
* when it should not be applied.
* Note that SCB is disabled before enter Deep Sleep mode or after calling
* \ref Cy_SCB_UART_Disable.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_UART_EnableSkipStart(CySCB_Type *base)
{
    SCB_UART_RX_CTRL(base) |= SCB_UART_RX_CTRL_SKIP_START_Msk;
}


/*******************************************************************************
* Function Name: Cy_SCB_UART_DisableSkipStart
****************************************************************************//**
*
* Disable the skip start-bit functionality.
* See \ref Cy_SCB_UART_EnableSkipStart for the details.
*
* \param base
* The pointer to the UART SCB instance.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_UART_DisableSkipStart(CySCB_Type *base)
{
    SCB_UART_RX_CTRL(base) &= (uint32_t) ~SCB_UART_RX_CTRL_SKIP_START_Msk;
}
/** \} group_scb_uart_general_functions */


/**
* \addtogroup group_scb_uart_low_level_functions
* \{
*/


/*******************************************************************************
* Function Name: Cy_SCB_UART_GetOverSample
****************************************************************************//**
*
* Returns the value of oversample.
*
* \param base
* The pointer to the UART SCB instance.
*
* \return
* The value of oversample.
*
* \snippet scb/uart_snippet/main.c UART_GET_OVS
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_UART_GetOverSample(CySCB_Type const *base)
{
    return (_FLD2VAL(SCB_CTRL_OVS, SCB_CTRL(base))+1UL);
}


/*******************************************************************************
* Function Name: Cy_SCB_UART_GetDataWidth
****************************************************************************//**
*
* Returns the value of datawidth.
*
* \param base
* The pointer to the UART SCB instance.
*
* \return
* The value of datawidth.
*
* \note
* Values of Tx and Rx datawidth are same.
*
* \snippet scb/uart_snippet/main.c UART_GET_DATA_WIDTH
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_UART_GetDataWidth(CySCB_Type const *base)
{
    return (_FLD2VAL(SCB_TX_CTRL_DATA_WIDTH, SCB_TX_CTRL(base))+1UL);
}


/*******************************************************************************
* Function Name: Cy_SCB_UART_GetParity
****************************************************************************//**
*
* Returns the value of parity.
*
* \param base
* The pointer to the UART SCB instance.
*
* \return
* The value of parity.
*
* \note
* Values of Tx and Rx parity are same.
*
* \snippet scb/uart_snippet/main.c UART_GET_PARITY
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_UART_GetParity(CySCB_Type const *base)
{
    return _FLD2VAL(CY_SCB_UART_TX_CTRL_SET_PARITY, SCB_UART_TX_CTRL(base));
}


/*******************************************************************************
* Function Name: Cy_SCB_UART_GetStopBits
****************************************************************************//**
*
* Returns the value of stop bits.
*
* \param base
* The pointer to the UART SCB instance.
*
* \return
* The value of stop bits.
*
* \note
* Values of Tx and Rx stop bits are same.
*
* \snippet scb/uart_snippet/main.c UART_GET_STOP_BITS
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_UART_GetStopBits(CySCB_Type const *base)
{
    return (_FLD2VAL(SCB_UART_TX_CTRL_STOP_BITS, SCB_UART_TX_CTRL(base))+1UL);
}


/*******************************************************************************
* Function Name: Cy_SCB_UART_GetDropOnParityError
****************************************************************************//**
*
* Returns the value of SetDropOnParityError.
*
* \param base
* The pointer to the UART SCB instance.
*
* \return
* The value of SetDropOnParityError.
*
* \snippet scb/uart_snippet/main.c UART_GET_DROP_ON_PARITY_ERROR
*
*******************************************************************************/
__STATIC_INLINE bool Cy_SCB_UART_GetDropOnParityError(CySCB_Type const *base)
{
    return _FLD2BOOL(SCB_UART_RX_CTRL_DROP_ON_PARITY_ERROR, SCB_UART_RX_CTRL(base));
}


/*******************************************************************************
* Function Name: Cy_SCB_UART_GetEnableMsbFirst
****************************************************************************//**
*
* Returns the value of enableMsbFirst.
*
* \param base
* The pointer to the UART SCB instance.
*
* \return
* The value of enableMsbFirst.
*
* \note
* Values of Tx and Rx enableMsbFirst are same.
*
* \snippet scb/uart_snippet/main.c UART_GET_ENABLE_MSB_FIRST
*
*******************************************************************************/
__STATIC_INLINE bool Cy_SCB_UART_GetEnableMsbFirst(CySCB_Type const *base)
{
    return _FLD2BOOL(SCB_TX_CTRL_MSB_FIRST, SCB_TX_CTRL(base));
}


/*******************************************************************************
* Function Name: Cy_SCB_UART_Get
****************************************************************************//**
*
* Reads a single data element from the UART RX FIFO.
* This function does not check whether the RX FIFO has data before reading it.
* If the RX FIFO is empty, the function returns \ref CY_SCB_UART_RX_NO_DATA.
*
* \param base
* The pointer to the UART SCB instance.
*
* \return
* Data from the RX FIFO.
* The data element size is defined by the configured data width.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_UART_Get(CySCB_Type const *base)
{
    return Cy_SCB_ReadRxFifo(base);
}


/*******************************************************************************
* Function Name: Cy_SCB_UART_GetArray
****************************************************************************//**
*
* Reads an array of data out of the UART RX FIFO.
* This function does not block. It returns how many data elements were read
* from the RX FIFO.
*
* \param base
* The pointer to the UART SCB instance.
*
* \param buffer
* The pointer to the location to place the data read from the RX FIFO.
* The element size is defined by the data type, which depends on the configured
* data width.
*
* \param size
* The number of data elements to read from the RX FIFO.
*
* \return
* The number of data elements read from the RX FIFO.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_UART_GetArray(CySCB_Type const *base, void *buffer, uint32_t size)
{
    CY_ASSERT_L1(CY_SCB_IS_BUFFER_VALID(buffer, size));

    return Cy_SCB_ReadArray(base, buffer, size);
}


/*******************************************************************************
* Function Name: Cy_SCB_UART_GetArrayBlocking
****************************************************************************//**
*
* Reads an array of data out of the UART RX FIFO.
* This function blocks until the number of data elements specified by the
* size has been read from the RX FIFO.
*
* \param base
* The pointer to the UART SCB instance.
*
* \param buffer
* The pointer to the location to place the data read from the RX FIFO.
* The element size is defined by the data type, which depends on the configured
* data width.
*
* \param size
* The number of data elements to read from the RX FIFO.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_UART_GetArrayBlocking(CySCB_Type const *base, void *buffer, uint32_t size)
{
    CY_ASSERT_L1(CY_SCB_IS_BUFFER_VALID(buffer, size));

    Cy_SCB_ReadArrayBlocking(base, buffer, size);
}


/*******************************************************************************
* Function Name: Cy_SCB_UART_GetRxFifoStatus
****************************************************************************//**
*
* Returns the current status of the RX FIFO.
*
* \param base
* The pointer to the UART SCB instance.
*
* \return
* \ref group_scb_uart_macros_rx_fifo_status
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_UART_GetRxFifoStatus(CySCB_Type const *base)
{
    return (Cy_SCB_GetRxInterruptStatus(base) & CY_SCB_UART_RX_INTR_MASK);
}


/*******************************************************************************
* Function Name: Cy_SCB_UART_ClearRxFifoStatus
****************************************************************************//**
*
* Clears the selected statuses of the RX FIFO.
*
* \param base
* The pointer to the UART SCB instance.
*
* \param clearMask
* The mask whose statuses to clear.
* See \ref group_scb_uart_macros_rx_fifo_status for the set of constants.
*
* \note
* * This status is also used for interrupt generation, so clearing it also
*   clears the interrupt sources.
* * Level-sensitive statuses such as \ref CY_SCB_UART_RX_TRIGGER,
*   \ref CY_SCB_UART_RX_NOT_EMPTY and \ref CY_SCB_UART_RX_FULL are set high again after
*   being cleared if the condition remains true.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_UART_ClearRxFifoStatus(CySCB_Type *base, uint32_t clearMask)
{
    CY_ASSERT_L2(CY_SCB_IS_INTR_VALID(clearMask, CY_SCB_UART_RX_INTR_MASK));

    Cy_SCB_ClearRxInterrupt(base, clearMask);
}


/*******************************************************************************
* Function Name: Cy_SCB_UART_GetNumInRxFifo
****************************************************************************//**
*
* Returns the number of data elements in the UART RX FIFO.
*
* \param base
* The pointer to the UART SCB instance.
*
* \return
* The number of data elements in the RX FIFO.
* The size of date element defined by the configured data width.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_UART_GetNumInRxFifo(CySCB_Type const *base)
{
    return Cy_SCB_GetNumInRxFifo(base);
}

/*******************************************************************************
* Function Name: Cy_SCB_UART_ClearRxFifo
****************************************************************************//**
*
* Clears all data out of the UART RX FIFO.
*
* \param base
* The pointer to the UART SCB instance.
*
* \sideeffect
* Any data currently in the shifter is cleared and lost.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_UART_ClearRxFifo(CySCB_Type *base)
{
    Cy_SCB_ClearRxFifo(base);
}


/*******************************************************************************
* Function Name: Cy_SCB_UART_Put
****************************************************************************//**
*
* Places a single data element in the UART TX FIFO.
* This function does not block and returns how many data elements were placed
* in the TX FIFO.
*
* \param base
* The pointer to the UART SCB instance.
*
* \param data
* Data to put in the TX FIFO.
* The element size is defined by the data type, which depends on the configured
* data width.
*
* \return
* The number of data elements placed in the TX FIFO: 0 or 1.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_UART_Put(CySCB_Type *base, uint32_t data)
{
    return Cy_SCB_Write(base, data);
}


/*******************************************************************************
* Function Name: Cy_SCB_UART_PutArray
****************************************************************************//**
*
* Places an array of data in the UART TX FIFO.
* This function does not block. It returns how many data elements were
* placed in the TX FIFO.
*
* \param base
* The pointer to the UART SCB instance.
*
* \param buffer
* The pointer to data to place in the TX FIFO.
* The element size is defined by the data type, which depends on the configured
* TX data width.
*
* \param size
* The number of data elements to TX.
*
* \return
* The number of data elements placed in the TX FIFO.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_UART_PutArray(CySCB_Type *base, void *buffer, uint32_t size)
{
    CY_ASSERT_L1(CY_SCB_IS_BUFFER_VALID(buffer, size));

    return Cy_SCB_WriteArray(base, buffer, size);
}


/*******************************************************************************
* Function Name: Cy_SCB_UART_PutArrayBlocking
****************************************************************************//**
*
* Places an array of data in the UART TX FIFO.
* This function blocks until the number of data elements specified by the size
* is placed in the TX FIFO.
*
* \param base
* The pointer to the UART SCB instance.
*
* \param buffer
* The pointer to data to place in the TX FIFO.
* The element size is defined by the data type, which depends on the configured
* data width.
*
* \param size
* The number of data elements to write into the TX FIFO.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_UART_PutArrayBlocking(CySCB_Type *base, void *buffer, uint32_t size)
{
    CY_ASSERT_L1(CY_SCB_IS_BUFFER_VALID(buffer, size));

    Cy_SCB_WriteArrayBlocking(base, buffer, size);
}


/*******************************************************************************
* Function Name: Cy_SCB_UART_PutString
****************************************************************************//**
*
* Places a NULL terminated string in the UART TX FIFO.
* This function blocks until the entire string is placed in the TX FIFO.
*
* \param base
* The pointer to the UART SCB instance.
*
* \param string
* The pointer to the null terminated string array.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_UART_PutString(CySCB_Type *base, char_t const string[])
{
    CY_ASSERT_L1(CY_SCB_IS_BUFFER_VALID(string, 1UL));

    Cy_SCB_WriteString(base, string);
}


/*******************************************************************************
* Function Name: Cy_SCB_UART_GetTxFifoStatus
****************************************************************************//**
*
* Returns the current status of the TX FIFO.
*
* \param base
* The pointer to the UART SCB instance.
*
* \return
* \ref group_scb_uart_macros_tx_fifo_status
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_UART_GetTxFifoStatus(CySCB_Type const *base)
{
    return (Cy_SCB_GetTxInterruptStatus(base) & CY_SCB_UART_TX_INTR_MASK);
}


/*******************************************************************************
* Function Name: Cy_SCB_UART_ClearTxFifoStatus
****************************************************************************//**
*
* Clears the selected statuses of the TX FIFO.
*
* \param base
* The pointer to the UART SCB instance.
*
* \param clearMask
* The mask whose statuses to clear.
* See \ref group_scb_uart_macros_tx_fifo_status for the set of constants.
*
* \note
* * The status is also used for interrupt generation, so clearing it also
*   clears the interrupt sources.
* * Level-sensitive statuses such as \ref CY_SCB_UART_TX_TRIGGER,
*   \ref CY_SCB_UART_TX_EMPTY and \ref CY_SCB_UART_TX_NOT_FULL are set high again after
*   being cleared if the condition remains true.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_UART_ClearTxFifoStatus(CySCB_Type *base, uint32_t clearMask)
{
    CY_ASSERT_L2(CY_SCB_IS_INTR_VALID(clearMask, CY_SCB_UART_TX_INTR_MASK));

    Cy_SCB_ClearTxInterrupt(base, clearMask);
}


/*******************************************************************************
* Function Name: Cy_SCB_UART_GetNumInTxFifo
****************************************************************************//**
*
* Returns the number of data elements in the UART TX FIFO.
*
* \param base
* The pointer to the UART SCB instance.
*
* \return
* The number of data elements in the TX FIFO.
* The size of date element defined by the configured data width.
*
* \note
* This number does not include any data currently in the TX shifter.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_UART_GetNumInTxFifo(CySCB_Type const *base)
{
    return Cy_SCB_GetNumInTxFifo(base);
}


/*******************************************************************************
* Function Name: Cy_SCB_UART_IsTxComplete
****************************************************************************//**
*
* Checks whether the TX FIFO and Shifter are empty and there is no more data to send
*
* \param base
* Pointer to the UART SCB instance.
*
* \return
* If true, transmission complete. If false, transmission is not complete.
*
*******************************************************************************/
__STATIC_INLINE bool Cy_SCB_UART_IsTxComplete(CySCB_Type const *base)
{
    return Cy_SCB_IsTxComplete(base);
}


/*******************************************************************************
* Function Name: Cy_SCB_UART_ClearTxFifo
****************************************************************************//**
*
* Clears all data out of the UART TX FIFO.
*
* \param base
* The pointer to the UART SCB instance.
*
* \sideeffect
* The TX FIFO clear operation also clears the shift register, so that
* the shifter could be cleared in the middle of a data element transfer,
* corrupting it. The data element corruption means that all bits that have
* not been transmitted are transmitted as 1s on the bus.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_UART_ClearTxFifo(CySCB_Type *base)
{
    Cy_SCB_ClearTxFifo(base);
}
/** \} group_scb_uart_low_level_functions */

/**
* \addtogroup group_scb_uart_interrupt_functions
* \{
*/
/*******************************************************************************
* Function Name: Cy_SCB_UART_RegisterCallback
****************************************************************************//**
*
* Registers a callback function that notifies that
* \ref group_scb_uart_macros_callback_events occurred in the
* \ref Cy_SCB_UART_Interrupt.
*
* \param base
* The pointer to the UART SCB instance.
*
* \param callback
* The pointer to the callback function.
* See \ref cy_cb_scb_uart_handle_events_t for the function prototype.
*
* \param context
* The pointer to the context structure \ref cy_stc_scb_uart_context_t allocated
* by the user. The structure is used during the UART operation for internal
* configuration and data retention. The user should not modify anything
* in this structure.
*
* \note
* To remove the callback, pass NULL as the pointer to the callback function.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_UART_RegisterCallback(CySCB_Type const *base,
          cy_cb_scb_uart_handle_events_t callback, cy_stc_scb_uart_context_t *context)
{
    /* Suppress a compiler warning about unused variables */
    (void) base;

    context->cbEvents = callback;
}
/** \} group_scb_uart_interrupt_functions */

#if defined(__cplusplus)
}
#endif

/** \} group_scb_uart */

#endif /* (defined (CY_IP_MXSCB) || defined (CY_IP_MXS22SCB)) */

#endif /* (CY_SCB_UART_H) */
/* [] END OF FILE */
