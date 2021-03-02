/******************************************************************************
* Copyright (c) 2002 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xstatus.h
*
* @addtogroup common_status_codes Xilinx&reg; software status codes
*
* The xstatus.h file contains the Xilinx&reg; software status codes.These codes are
* used throughout the Xilinx device drivers.
*
* @{
******************************************************************************/

#ifndef XSTATUS_H        /* prevent circular inclusions */
#define XSTATUS_H        /* by using protection macros */

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/

#include "xil_types.h"
#include "xil_assert.h"

/************************** Constant Definitions *****************************/

/*********************** Common statuses 0 - 500 *****************************/
/**
@name Common Status Codes for All Device Drivers
@{
*/
#define XST_SUCCESS                     0L
#define XST_FAILURE                     1L
#define XST_DEVICE_NOT_FOUND            2L
#define XST_DEVICE_BLOCK_NOT_FOUND      3L
#define XST_INVALID_VERSION             4L
#define XST_DEVICE_IS_STARTED           5L
#define XST_DEVICE_IS_STOPPED           6L
#define XST_FIFO_ERROR                  7L    /*!< An error occurred during an
                           operation with a FIFO such as
                           an underrun or overrun, this
                           error requires the device to
                           be reset */
#define XST_RESET_ERROR                 8L    /*!< An error occurred which requires
                           the device to be reset */
#define XST_DMA_ERROR                   9L    /*!< A DMA error occurred, this error
                           typically requires the device
                           using the DMA to be reset */
#define XST_NOT_POLLED                  10L    /*!< The device is not configured for
                           polled mode operation */
#define XST_FIFO_NO_ROOM                11L    /*!< A FIFO did not have room to put
                           the specified data into */
#define XST_BUFFER_TOO_SMALL            12L    /*!< The buffer is not large enough
                           to hold the expected data */
#define XST_NO_DATA                     13L    /*!< There was no data available */
#define XST_REGISTER_ERROR              14L    /*!< A register did not contain the
                           expected value */
#define XST_INVALID_PARAM               15L    /*!< An invalid parameter was passed
                           into the function */
#define XST_NOT_SGDMA                   16L    /*!< The device is not configured for
                           scatter-gather DMA operation */
#define XST_LOOPBACK_ERROR              17L    /*!< A loopback test failed */
#define XST_NO_CALLBACK                 18L    /*!< A callback has not yet been
                           registered */
#define XST_NO_FEATURE                  19L    /*!< Device is not configured with
                           the requested feature */
#define XST_NOT_INTERRUPT               20L    /*!< Device is not configured for
                           interrupt mode operation */
#define XST_DEVICE_BUSY                 21L    /*!< Device is busy */
#define XST_ERROR_COUNT_MAX             22L    /*!< The error counters of a device
                           have maxed out */
#define XST_IS_STARTED                  23L    /*!< Used when part of device is
                           already started i.e.
                           sub channel */
#define XST_IS_STOPPED                  24L    /*!< Used when part of device is
                           already stopped i.e.
                           sub channel */
#define XST_DATA_LOST                   26L    /*!< Driver defined error */
#define XST_RECV_ERROR                  27L    /*!< Generic receive error */
#define XST_SEND_ERROR                  28L    /*!< Generic transmit error */
#define XST_NOT_ENABLED                 29L    /*!< A requested service is not
                           available because it has not
                           been enabled */
#define XST_NO_ACCESS            30L    /* Generic access error */
#define XST_TIMEOUT                     31L    /*!< Event timeout occurred */

/** @} */
/***************** Utility Component statuses 401 - 500  *********************/
/**
@name Utility Component Status Codes 401 - 500
@{
*/
#define XST_MEMTEST_FAILED              401L    /*!< Memory test failed */

/** @} */
/***************** Common Components statuses 501 - 1000 *********************/
/**
@name Packet Fifo Status Codes 501 - 510
@{
*/
/********************* Packet Fifo statuses 501 - 510 ************************/

#define XST_PFIFO_LACK_OF_DATA          501L    /*!< Not enough data in FIFO   */
#define XST_PFIFO_NO_ROOM               502L    /*!< Not enough room in FIFO   */
#define XST_PFIFO_BAD_REG_VALUE         503L    /*!< Self test, a register value
                           was invalid after reset */
#define XST_PFIFO_ERROR                 504L    /*!< Generic packet FIFO error */
#define XST_PFIFO_DEADLOCK              505L    /*!< Packet FIFO is reporting
                         * empty and full simultaneously
                         */
/** @} */
/**
@name DMA Status Codes 511 - 530
@{
*/
/************************** DMA statuses 511 - 530 ***************************/

#define XST_DMA_TRANSFER_ERROR          511L    /*!< Self test, DMA transfer
                           failed */
#define XST_DMA_RESET_REGISTER_ERROR    512L    /*!< Self test, a register value
                           was invalid after reset */
#define XST_DMA_SG_LIST_EMPTY           513L    /*!< Scatter gather list contains
                           no buffer descriptors ready
                           to be processed */
#define XST_DMA_SG_IS_STARTED           514L    /*!< Scatter gather not stopped */
#define XST_DMA_SG_IS_STOPPED           515L    /*!< Scatter gather not running */
#define XST_DMA_SG_LIST_FULL            517L    /*!< All the buffer descriptors of
                           the scatter gather list are
                           being used */
#define XST_DMA_SG_BD_LOCKED            518L    /*!< The scatter gather buffer
                           descriptor which is to be
                           copied over in the scatter
                           list is locked */
#define XST_DMA_SG_NOTHING_TO_COMMIT    519L    /*!< No buffer descriptors have been
                           put into the scatter gather
                           list to be committed */
#define XST_DMA_SG_COUNT_EXCEEDED       521L    /*!< The packet count threshold
                           specified was larger than the
                           total # of buffer descriptors
                           in the scatter gather list */
#define XST_DMA_SG_LIST_EXISTS          522L    /*!< The scatter gather list has
                           already been created */
#define XST_DMA_SG_NO_LIST              523L    /*!< No scatter gather list has
                           been created */
#define XST_DMA_SG_BD_NOT_COMMITTED     524L    /*!< The buffer descriptor which was
                           being started was not committed
                           to the list */
#define XST_DMA_SG_NO_DATA              525L    /*!< The buffer descriptor to start
                           has already been used by the
                           hardware so it can't be reused
                         */
#define XST_DMA_SG_LIST_ERROR           526L    /*!< General purpose list access
                           error */
#define XST_DMA_BD_ERROR                527L    /*!< General buffer descriptor
                           error */
/** @} */
/**
@name IPIF Status Codes Codes 531 - 550
@{
*/
/************************** IPIF statuses 531 - 550 ***************************/

#define XST_IPIF_REG_WIDTH_ERROR        531L    /*!< An invalid register width
                           was passed into the function */
#define XST_IPIF_RESET_REGISTER_ERROR   532L    /*!< The value of a register at
                           reset was not valid */
#define XST_IPIF_DEVICE_STATUS_ERROR    533L    /*!< A write to the device interrupt
                           status register did not read
                           back correctly */
#define XST_IPIF_DEVICE_ACK_ERROR       534L    /*!< The device interrupt status
                           register did not reset when
                           acked */
#define XST_IPIF_DEVICE_ENABLE_ERROR    535L    /*!< The device interrupt enable
                           register was not updated when
                           other registers changed */
#define XST_IPIF_IP_STATUS_ERROR        536L    /*!< A write to the IP interrupt
                           status register did not read
                           back correctly */
#define XST_IPIF_IP_ACK_ERROR           537L    /*!< The IP interrupt status register
                           did not reset when acked */
#define XST_IPIF_IP_ENABLE_ERROR        538L    /*!< IP interrupt enable register was
                           not updated correctly when other
                           registers changed */
#define XST_IPIF_DEVICE_PENDING_ERROR   539L    /*!< The device interrupt pending
                           register did not indicate the
                           expected value */
#define XST_IPIF_DEVICE_ID_ERROR        540L    /*!< The device interrupt ID register
                           did not indicate the expected
                           value */
#define XST_IPIF_ERROR                  541L    /*!< Generic ipif error */
/** @} */

/****************** Device specific statuses 1001 - 4095 *********************/
/**
@name Ethernet Status Codes 1001 - 1050
@{
*/
/********************* Ethernet statuses 1001 - 1050 *************************/

#define XST_EMAC_MEMORY_SIZE_ERROR  1001L    /*!< Memory space is not big enough
                         * to hold the minimum number of
                         * buffers or descriptors */
#define XST_EMAC_MEMORY_ALLOC_ERROR 1002L    /*!< Memory allocation failed */
#define XST_EMAC_MII_READ_ERROR     1003L    /*!< MII read error */
#define XST_EMAC_MII_BUSY           1004L    /*!< An MII operation is in progress */
#define XST_EMAC_OUT_OF_BUFFERS     1005L    /*!< Driver is out of buffers */
#define XST_EMAC_PARSE_ERROR        1006L    /*!< Invalid driver init string */
#define XST_EMAC_COLLISION_ERROR    1007L    /*!< Excess deferral or late
                         * collision on polled send */
/** @} */
/**
@name UART Status Codes 1051 - 1075
@{
*/
/*********************** UART statuses 1051 - 1075 ***************************/
#define XST_UART

#define XST_UART_INIT_ERROR         1051L
#define XST_UART_START_ERROR        1052L
#define XST_UART_CONFIG_ERROR       1053L
#define XST_UART_TEST_FAIL          1054L
#define XST_UART_BAUD_ERROR         1055L
#define XST_UART_BAUD_RANGE         1056L

/** @} */
/**
@name IIC Status Codes 1076 - 1100
@{
*/
/************************ IIC statuses 1076 - 1100 ***************************/

#define XST_IIC_SELFTEST_FAILED         1076    /*!< self test failed            */
#define XST_IIC_BUS_BUSY                1077    /*!< bus found busy              */
#define XST_IIC_GENERAL_CALL_ADDRESS    1078    /*!< mastersend attempted with   */
                         /* general call address        */
#define XST_IIC_STAND_REG_RESET_ERROR   1079    /*!< A non parameterizable reg   */
                         /* value after reset not valid */
#define XST_IIC_TX_FIFO_REG_RESET_ERROR 1080    /*!< Tx fifo included in design  */
                         /* value after reset not valid */
#define XST_IIC_RX_FIFO_REG_RESET_ERROR 1081    /*!< Rx fifo included in design  */
                         /* value after reset not valid */
#define XST_IIC_TBA_REG_RESET_ERROR     1082    /*!< 10 bit addr incl in design  */
                         /* value after reset not valid */
#define XST_IIC_CR_READBACK_ERROR       1083    /*!< Read of the control register */
                         /* didn't return value written */
#define XST_IIC_DTR_READBACK_ERROR      1084    /*!< Read of the data Tx reg     */
                         /* didn't return value written */
#define XST_IIC_DRR_READBACK_ERROR      1085    /*!< Read of the data Receive reg */
                         /* didn't return value written */
#define XST_IIC_ADR_READBACK_ERROR      1086    /*!< Read of the data Tx reg     */
                         /* didn't return value written */
#define XST_IIC_TBA_READBACK_ERROR      1087    /*!< Read of the 10 bit addr reg */
                         /* didn't return written value */
#define XST_IIC_NOT_SLAVE               1088    /*!< The device isn't a slave    */
#define XST_IIC_ARB_LOST                 1089     /*!< Arbitration lost for master    */
/** @} */
/**
@name ATMC Status Codes 1101 - 1125
@{
*/
/*********************** ATMC statuses 1101 - 1125 ***************************/

#define XST_ATMC_ERROR_COUNT_MAX    1101L    /*!< the error counters in the ATM
                           controller hit the max value
                           which requires the statistics
                           to be cleared */
/** @} */
/**
@name Flash Status Codes 1126 - 1150
@{
*/
/*********************** Flash statuses 1126 - 1150 **************************/

#define XST_FLASH_BUSY                1126L    /*!< Flash is erasing or programming
                         */
#define XST_FLASH_READY               1127L    /*!< Flash is ready for commands */
#define XST_FLASH_ERROR               1128L    /*!< Flash had detected an internal
                           error. Use XFlash_DeviceControl
                           to retrieve device specific codes
                         */
#define XST_FLASH_ERASE_SUSPENDED     1129L    /*!< Flash is in suspended erase state
                         */
#define XST_FLASH_WRITE_SUSPENDED     1130L    /*!< Flash is in suspended write state
                         */
#define XST_FLASH_PART_NOT_SUPPORTED  1131L    /*!< Flash type not supported by
                           driver */
#define XST_FLASH_NOT_SUPPORTED       1132L    /*!< Operation not supported */
#define XST_FLASH_TOO_MANY_REGIONS    1133L    /*!< Too many erase regions */
#define XST_FLASH_TIMEOUT_ERROR       1134L    /*!< Programming or erase operation
                           aborted due to a timeout */
#define XST_FLASH_ADDRESS_ERROR       1135L    /*!< Accessed flash outside its
                           addressible range */
#define XST_FLASH_ALIGNMENT_ERROR     1136L    /*!< Write alignment error */
#define XST_FLASH_BLOCKING_CALL_ERROR 1137L    /*!< Couldn't return immediately from
                           write/erase function with
                           XFL_NON_BLOCKING_WRITE/ERASE
                           option cleared */
#define XST_FLASH_CFI_QUERY_ERROR     1138L    /*!< Failed to query the device */
/** @} */
/**
@name SPI Status Codes 1151 - 1175
@{
*/
/*********************** SPI statuses 1151 - 1175 ****************************/

#define XST_SPI_MODE_FAULT          1151    /*!< master was selected as slave */
#define XST_SPI_TRANSFER_DONE       1152    /*!< data transfer is complete */
#define XST_SPI_TRANSMIT_UNDERRUN   1153    /*!< slave underruns transmit register */
#define XST_SPI_RECEIVE_OVERRUN     1154    /*!< device overruns receive register */
#define XST_SPI_NO_SLAVE            1155    /*!< no slave has been selected yet */
#define XST_SPI_TOO_MANY_SLAVES     1156    /*!< more than one slave is being
                         * selected */
#define XST_SPI_NOT_MASTER          1157    /*!< operation is valid only as master */
#define XST_SPI_SLAVE_ONLY          1158    /*!< device is configured as slave-only
                         */
#define XST_SPI_SLAVE_MODE_FAULT    1159    /*!< slave was selected while disabled */
#define XST_SPI_SLAVE_MODE          1160    /*!< device has been addressed as slave */
#define XST_SPI_RECEIVE_NOT_EMPTY   1161    /*!< device received data in slave mode */

#define XST_SPI_COMMAND_ERROR       1162    /*!< unrecognised command - qspi only */
#define XST_SPI_POLL_DONE           1163        /*!< controller completed polling the
                           device for status */
/** @} */
/**
@name OPB Arbiter Status Codes 1176 - 1200
@{
*/
/********************** OPB Arbiter statuses 1176 - 1200 *********************/

#define XST_OPBARB_INVALID_PRIORITY  1176    /*!< the priority registers have either
                         * one master assigned to two or more
                         * priorities, or one master not
                         * assigned to any priority
                         */
#define XST_OPBARB_NOT_SUSPENDED     1177    /*!< an attempt was made to modify the
                         * priority levels without first
                         * suspending the use of priority
                         * levels
                         */
#define XST_OPBARB_PARK_NOT_ENABLED  1178    /*!< bus parking by id was enabled but
                         * bus parking was not enabled
                         */
#define XST_OPBARB_NOT_FIXED_PRIORITY 1179    /*!< the arbiter must be in fixed
                         * priority mode to allow the
                         * priorities to be changed
                         */
/** @} */
/**
@name INTC Status Codes 1201 - 1225
@{
*/
/************************ Intc statuses 1201 - 1225 **************************/

#define XST_INTC_FAIL_SELFTEST      1201    /*!< self test failed */
#define XST_INTC_CONNECT_ERROR      1202    /*!< interrupt already in use */
/** @} */
/**
@name TmrCtr Status Codes 1226 - 1250
@{
*/
/********************** TmrCtr statuses 1226 - 1250 **************************/

#define XST_TMRCTR_TIMER_FAILED     1226    /*!< self test failed */
/** @} */
/**
@name WdtTb Status Codes 1251 - 1275
@{
*/
/********************** WdtTb statuses 1251 - 1275 ***************************/

#define XST_WDTTB_TIMER_FAILED      1251L
/** @} */
/**
@name PlbArb status Codes 1276 - 1300
@{
*/
/********************** PlbArb statuses 1276 - 1300 **************************/

#define XST_PLBARB_FAIL_SELFTEST    1276L
/** @} */
/**
@name Plb2Opb Status Codes 1301 - 1325
@{
*/
/********************** Plb2Opb statuses 1301 - 1325 *************************/

#define XST_PLB2OPB_FAIL_SELFTEST   1301L
/** @} */
/**
@name Opb2Plb Status 1326 - 1350
@{
*/
/********************** Opb2Plb statuses 1326 - 1350 *************************/

#define XST_OPB2PLB_FAIL_SELFTEST   1326L
/** @} */
/**
@name SysAce Status Codes 1351 - 1360
@{
*/
/********************** SysAce statuses 1351 - 1360 **************************/

#define XST_SYSACE_NO_LOCK          1351L    /*!< No MPU lock has been granted */
/** @} */
/**
@name PCI Bridge Status Codes 1361 - 1375
@{
*/
/********************** PCI Bridge statuses 1361 - 1375 **********************/

#define XST_PCI_INVALID_ADDRESS     1361L
/** @} */
/**
@name FlexRay Constants 1400 - 1409
@{
*/
/********************** FlexRay constants 1400 - 1409 *************************/

#define XST_FR_TX_ERROR            1400
#define XST_FR_TX_BUSY            1401
#define XST_FR_BUF_LOCKED        1402
#define XST_FR_NO_BUF            1403
/** @} */
/**
@name USB constants 1410 - 1420
@{
*/
/****************** USB constants 1410 - 1420  *******************************/

#define XST_USB_ALREADY_CONFIGURED    1410
#define XST_USB_BUF_ALIGN_ERROR        1411
#define XST_USB_NO_DESC_AVAILABLE    1412
#define XST_USB_BUF_TOO_BIG        1413
#define XST_USB_NO_BUF            1414
/** @} */
/**
@name HWICAP constants 1421 - 1429
@{
*/
/****************** HWICAP constants 1421 - 1429  *****************************/

#define XST_HWICAP_WRITE_DONE        1421

/** @} */
/**
@name AXI VDMA constants 1430 - 1440
@{
*/
/****************** AXI VDMA constants 1430 - 1440  *****************************/

#define XST_VDMA_MISMATCH_ERROR        1430
/** @} */
/**
@name NAND Flash Status Codes 1441 - 1459
@{
*/
/*********************** NAND Flash statuses 1441 - 1459  *********************/

#define XST_NAND_BUSY            1441L    /*!< Flash is erasing or
                         * programming
                         */
#define XST_NAND_READY            1442L    /*!< Flash is ready for commands
                         */
#define XST_NAND_ERROR            1443L    /*!< Flash had detected an
                         * internal error.
                         */
#define XST_NAND_PART_NOT_SUPPORTED    1444L    /*!< Flash type not supported by
                         * driver
                         */
#define XST_NAND_OPT_NOT_SUPPORTED    1445L    /*!< Operation not supported
                         */
#define XST_NAND_TIMEOUT_ERROR        1446L    /*!< Programming or erase
                         * operation aborted due to a
                         * timeout
                         */
#define XST_NAND_ADDRESS_ERROR        1447L    /*!< Accessed flash outside its
                         * addressible range
                         */
#define XST_NAND_ALIGNMENT_ERROR    1448L    /*!< Write alignment error
                         */
#define XST_NAND_PARAM_PAGE_ERROR    1449L    /*!< Failed to read parameter
                         * page of the device
                         */
#define XST_NAND_CACHE_ERROR        1450L    /*!< Flash page buffer error
                         */

#define XST_NAND_WRITE_PROTECTED    1451L    /*!< Flash is write protected
                         */
/** @} */

/**************************** Type Definitions *******************************/

typedef s32 XStatus;

/***************** Macros (Inline Functions) Definitions *********************/


/************************** Function Prototypes ******************************/

#ifdef __cplusplus
}
#endif

#endif /* end of protection macro */
/**
* @} End of "addtogroup common_status_codes".
*/
