/* -----------------------------------------------------------------------------
 * Copyright (c) 2013-2014 ARM Ltd.
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from
 * the use of this software. Permission is granted to anyone to use this
 * software for any purpose, including commercial applications, and to alter
 * it and redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software in
 *    a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 *
 *
 * $Date:        17. Apr 2014
 * $Revision:    V2.01
 *
 * Project:      SPI (Serial Peripheral Interface) Driver definitions
 * -------------------------------------------------------------------------- */

/* History:
 *  Version 2.01
 *    Renamed status flag "tx_rx_busy" to "busy"
 *  Version 2.00
 *    New simplified driver:
 *      complexity moved to upper layer (especially data handling)
 *      more unified API for different communication interfaces
 *    Added:
 *      Slave Mode
 *      Half-duplex Modes
 *      Configurable number of data bits
 *      Support for TI Mode and Microwire
 *    Changed prefix ARM_DRV -> ARM_DRIVER
 *  Version 1.10
 *    Namespace prefix ARM_ added
 *  Version 1.01
 *    Added "send_done_event" to Capabilities
 *  Version 1.00
 *    Initial release
 */

#ifndef __DRIVER_SPI_H
#define __DRIVER_SPI_H

#include "Driver_Common.h"

#define ARM_SPI_API_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(2,00)  /* API version */


/****** SPI Control Codes *****/

#define ARM_SPI_CONTROL_Pos              0
#define ARM_SPI_CONTROL_Msk             (0xFFUL << ARM_SPI_CONTROL_Pos)

/*----- SPI Control Codes: Mode -----*/
#define ARM_SPI_MODE_INACTIVE           (0x00UL << ARM_SPI_CONTROL_Pos)     ///< SPI Inactive
#define ARM_SPI_MODE_MASTER             (0x01UL << ARM_SPI_CONTROL_Pos)     ///< SPI Master (Output on MOSI, Input on MISO); arg = Bus Speed in bps
#define ARM_SPI_MODE_SLAVE              (0x02UL << ARM_SPI_CONTROL_Pos)     ///< SPI Slave  (Output on MISO, Input on MOSI)
#define ARM_SPI_MODE_MASTER_SIMPLEX     (0x03UL << ARM_SPI_CONTROL_Pos)     ///< SPI Master (Output/Input on MOSI); arg = Bus Speed in bps
#define ARM_SPI_MODE_SLAVE_SIMPLEX      (0x04UL << ARM_SPI_CONTROL_Pos)     ///< SPI Slave  (Output/Input on MISO)

/*----- SPI Control Codes: Mode Parameters: Frame Format -----*/
#define ARM_SPI_FRAME_FORMAT_Pos         8
#define ARM_SPI_FRAME_FORMAT_Msk        (7UL << ARM_SPI_FRAME_FORMAT_Pos)
#define ARM_SPI_CPOL0_CPHA0             (0UL << ARM_SPI_FRAME_FORMAT_Pos)   ///< Clock Polarity 0, Clock Phase 0 (default)
#define ARM_SPI_CPOL0_CPHA1             (1UL << ARM_SPI_FRAME_FORMAT_Pos)   ///< Clock Polarity 0, Clock Phase 1
#define ARM_SPI_CPOL1_CPHA0             (2UL << ARM_SPI_FRAME_FORMAT_Pos)   ///< Clock Polarity 1, Clock Phase 0
#define ARM_SPI_CPOL1_CPHA1             (3UL << ARM_SPI_FRAME_FORMAT_Pos)   ///< Clock Polarity 1, Clock Phase 1
#define ARM_SPI_TI_SSI                  (4UL << ARM_SPI_FRAME_FORMAT_Pos)   ///< Texas Instruments Frame Format
#define ARM_SPI_MICROWIRE               (5UL << ARM_SPI_FRAME_FORMAT_Pos)   ///< National Microwire Frame Format

/*----- SPI Control Codes: Mode Parameters: Data Bits -----*/
#define ARM_SPI_DATA_BITS_Pos            12
#define ARM_SPI_DATA_BITS_Msk           (0x3FUL << ARM_SPI_DATA_BITS_Pos)
#define ARM_SPI_DATA_BITS(n)            (((n) & 0x3F) << ARM_SPI_DATA_BITS_Pos) ///< Number of Data bits

/*----- SPI Control Codes: Mode Parameters: Bit Order -----*/
#define ARM_SPI_BIT_ORDER_Pos            18
#define ARM_SPI_BIT_ORDER_Msk           (1UL << ARM_SPI_BIT_ORDER_Pos)
#define ARM_SPI_MSB_LSB                 (0UL << ARM_SPI_BIT_ORDER_Pos)      ///< SPI Bit order from MSB to LSB (default)
#define ARM_SPI_LSB_MSB                 (1UL << ARM_SPI_BIT_ORDER_Pos)      ///< SPI Bit order from LSB to MSB

/*----- SPI Control Codes: Mode Parameters: Slave Select Mode -----*/
#define ARM_SPI_SS_MASTER_MODE_Pos       19
#define ARM_SPI_SS_MASTER_MODE_Msk      (3UL << ARM_SPI_SS_MASTER_MODE_Pos)
#define ARM_SPI_SS_MASTER_UNUSED        (0UL << ARM_SPI_SS_MASTER_MODE_Pos) ///< SPI Slave Select when Master: Not used (default)
#define ARM_SPI_SS_MASTER_SW            (1UL << ARM_SPI_SS_MASTER_MODE_Pos) ///< SPI Slave Select when Master: Software controlled
#define ARM_SPI_SS_MASTER_HW_OUTPUT     (2UL << ARM_SPI_SS_MASTER_MODE_Pos) ///< SPI Slave Select when Master: Hardware controlled Output
#define ARM_SPI_SS_MASTER_HW_INPUT      (3UL << ARM_SPI_SS_MASTER_MODE_Pos) ///< SPI Slave Select when Master: Hardware monitored Input
#define ARM_SPI_SS_SLAVE_MODE_Pos        21
#define ARM_SPI_SS_SLAVE_MODE_Msk       (1UL << ARM_SPI_SS_SLAVE_MODE_Pos)
#define ARM_SPI_SS_SLAVE_HW             (0UL << ARM_SPI_SS_SLAVE_MODE_Pos)  ///< SPI Slave Select when Slave: Hardware monitored (default)
#define ARM_SPI_SS_SLAVE_SW             (1UL << ARM_SPI_SS_SLAVE_MODE_Pos)  ///< SPI Slave Select when Slave: Software controlled


/*----- SPI Control Codes: Miscellaneous Controls  -----*/
#define ARM_SPI_SET_BUS_SPEED           (0x10UL << ARM_SPI_CONTROL_Pos)     ///< Set Bus Speed in bps; arg = value
#define ARM_SPI_GET_BUS_SPEED           (0x11UL << ARM_SPI_CONTROL_Pos)     ///< Get Bus Speed in bps
#define ARM_SPI_SET_DEFAULT_TX_VALUE    (0x12UL << ARM_SPI_CONTROL_Pos)     ///< Set default Transmit value; arg = value
#define ARM_SPI_CONTROL_SS              (0x13UL << ARM_SPI_CONTROL_Pos)     ///< Control Slave Select; arg: 0=inactive, 1=active 
#define ARM_SPI_ABORT_TRANSFER          (0x14UL << ARM_SPI_CONTROL_Pos)     ///< Abort current data transfer


/****** SPI Slave Select Signal definitions *****/
#define ARM_SPI_SS_INACTIVE              0                                  ///< SPI Slave Select Signal Inactive
#define ARM_SPI_SS_ACTIVE                1                                  ///< SPI Slave Select Signal Active


/****** SPI specific error codes *****/
#define ARM_SPI_ERROR_MODE              (ARM_DRIVER_ERROR_SPECIFIC - 1)     ///< Specified Mode not supported
#define ARM_SPI_ERROR_FRAME_FORMAT      (ARM_DRIVER_ERROR_SPECIFIC - 2)     ///< Specified Frame Format not supported
#define ARM_SPI_ERROR_DATA_BITS         (ARM_DRIVER_ERROR_SPECIFIC - 3)     ///< Specified number of Data bits not supported
#define ARM_SPI_ERROR_BIT_ORDER         (ARM_DRIVER_ERROR_SPECIFIC - 4)     ///< Specified Bit order not supported
#define ARM_SPI_ERROR_SS_MODE           (ARM_DRIVER_ERROR_SPECIFIC - 5)     ///< Specified Slave Select Mode not supported


/**
\brief SPI Status
*/
typedef struct _ARM_SPI_STATUS {
  uint32_t busy       : 1;              ///< Transmitter/Receiver busy flag
  uint32_t data_lost  : 1;              ///< Data lost: Receive overflow / Transmit underflow (cleared on start of transfer operation)
  uint32_t mode_fault : 1;              ///< Mode fault detected; optional (cleared on start of transfer operation)
} ARM_SPI_STATUS;


/****** SPI Event *****/
#define ARM_SPI_EVENT_TRANSFER_COMPLETE (1UL << 0)  ///< Data Transfer completed
#define ARM_SPI_EVENT_DATA_LOST         (1UL << 1)  ///< Data lost: Receive overflow / Transmit underflow
#define ARM_SPI_EVENT_MODE_FAULT        (1UL << 2)  ///< Master Mode Fault (SS deactivated when Master)


// Function documentation
/**
  \fn          ARM_DRIVER_VERSION ARM_SPI_GetVersion (void)
  \brief       Get driver version.
  \return      \ref ARM_DRIVER_VERSION

  \fn          ARM_SPI_CAPABILITIES ARM_SPI_GetCapabilities (void)
  \brief       Get driver capabilities.
  \return      \ref ARM_SPI_CAPABILITIES

  \fn          int32_t ARM_SPI_Initialize (ARM_SPI_SignalEvent_t cb_event)
  \brief       Initialize SPI Interface.
  \param[in]   cb_event  Pointer to \ref ARM_SPI_SignalEvent
  \return      \ref execution_status

  \fn          int32_t ARM_SPI_Uninitialize (void)
  \brief       De-initialize SPI Interface.
  \return      \ref execution_status

  \fn          int32_t ARM_SPI_PowerControl (ARM_POWER_STATE state)
  \brief       Control SPI Interface Power.
  \param[in]   state  Power state
  \return      \ref execution_status

  \fn          int32_t ARM_SPI_Send (const void *data, uint32_t num)
  \brief       Start sending data to SPI transmitter.
  \param[in]   data  Pointer to buffer with data to send to SPI transmitter
  \param[in]   num   Number of data items to send
  \return      \ref execution_status

  \fn          int32_t ARM_SPI_Receive (void *data, uint32_t num)
  \brief       Start receiving data from SPI receiver.
  \param[out]  data  Pointer to buffer for data to receive from SPI receiver
  \param[in]   num   Number of data items to receive
  \return      \ref execution_status

  \fn          int32_t ARM_SPI_Transfer (const void *data_out,
                                               void *data_in,
                                         uint32_t    num)
  \brief       Start sending/receiving data to/from SPI transmitter/receiver.
  \param[in]   data_out  Pointer to buffer with data to send to SPI transmitter
  \param[out]  data_in   Pointer to buffer for data to receive from SPI receiver
  \param[in]   num       Number of data items to transfer
  \return      \ref execution_status

  \fn          uint32_t ARM_SPI_GetDataCount (void)
  \brief       Get transferred data count.
  \return      number of data items transferred

  \fn          int32_t ARM_SPI_Control (uint32_t control, uint32_t arg)
  \brief       Control SPI Interface.
  \param[in]   control  Operation
  \param[in]   arg      Argument of operation (optional)
  \return      common \ref execution_status and driver specific \ref spi_execution_status

  \fn          ARM_SPI_STATUS ARM_SPI_GetStatus (void)
  \brief       Get SPI status.
  \return      SPI status \ref ARM_SPI_STATUS

  \fn          void ARM_SPI_SignalEvent (uint32_t event)
  \brief       Signal SPI Events.
  \param[in]   event \ref SPI_events notification mask
  \return      none
*/

typedef void (*ARM_SPI_SignalEvent_t) (uint32_t event);  ///< Pointer to \ref ARM_SPI_SignalEvent : Signal SPI Event.


/**
\brief SPI Driver Capabilities.
*/
typedef struct _ARM_SPI_CAPABILITIES {
  uint32_t simplex          : 1;        ///< supports Simplex Mode (Master and Slave)
  uint32_t ti_ssi           : 1;        ///< supports TI Synchronous Serial Interface
  uint32_t microwire        : 1;        ///< supports Microwire Interface
  uint32_t event_mode_fault : 1;        ///< Signal Mode Fault event: \ref ARM_SPI_EVENT_MODE_FAULT
} ARM_SPI_CAPABILITIES;


/**
\brief Access structure of the SPI Driver.
*/
typedef struct _ARM_DRIVER_SPI {
  ARM_DRIVER_VERSION   (*GetVersion)      (void);                             ///< Pointer to \ref ARM_SPI_GetVersion : Get driver version.
  ARM_SPI_CAPABILITIES (*GetCapabilities) (void);                             ///< Pointer to \ref ARM_SPI_GetCapabilities : Get driver capabilities.
  int32_t              (*Initialize)      (ARM_SPI_SignalEvent_t cb_event);   ///< Pointer to \ref ARM_SPI_Initialize : Initialize SPI Interface.
  int32_t              (*Uninitialize)    (void);                             ///< Pointer to \ref ARM_SPI_Uninitialize : De-initialize SPI Interface.
  int32_t              (*PowerControl)    (ARM_POWER_STATE state);            ///< Pointer to \ref ARM_SPI_PowerControl : Control SPI Interface Power.
  int32_t              (*Send)            (const void *data, uint32_t num);   ///< Pointer to \ref ARM_SPI_Send : Start sending data to SPI Interface.
  int32_t              (*Receive)         (      void *data, uint32_t num);   ///< Pointer to \ref ARM_SPI_Receive : Start receiving data from SPI Interface.
  int32_t              (*Transfer)        (const void *data_out,
                                                 void *data_in,
                                           uint32_t    num);                  ///< Pointer to \ref ARM_SPI_Transfer : Start sending/receiving data to/from SPI.
  uint32_t             (*GetDataCount)    (void);                             ///< Pointer to \ref ARM_SPI_GetDataCount : Get transferred data count.
  int32_t              (*Control)         (uint32_t control, uint32_t arg);   ///< Pointer to \ref ARM_SPI_Control : Control SPI Interface.
  ARM_SPI_STATUS       (*GetStatus)       (void);                             ///< Pointer to \ref ARM_SPI_GetStatus : Get SPI status.
} const ARM_DRIVER_SPI;

#endif /* __DRIVER_SPI_H */
