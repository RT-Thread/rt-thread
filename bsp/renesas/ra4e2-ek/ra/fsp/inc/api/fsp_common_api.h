/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef FSP_COMMON_API_H
#define FSP_COMMON_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <assert.h>
#include <stdint.h>

/* Includes FSP version macros. */
#include "fsp_version.h"

/*******************************************************************************************************************//**
 * @ingroup RENESAS_COMMON
 * @defgroup RENESAS_ERROR_CODES Common Error Codes
 * All FSP modules share these common error codes.
 * @{
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** This macro is used to suppress compiler messages about a parameter not being used in a function. The nice thing
 * about using this implementation is that it does not take any extra RAM or ROM. */

#define FSP_PARAMETER_NOT_USED(p)    (void) ((p))

/** Determine if a C++ compiler is being used.
 * If so, ensure that standard C is used to process the API information.  */
#if defined(__cplusplus)
 #define FSP_CPP_HEADER    extern "C" {
 #define FSP_CPP_FOOTER    }
#else
 #define FSP_CPP_HEADER
 #define FSP_CPP_FOOTER
#endif

/** FSP Header and Footer definitions */
#define FSP_HEADER    FSP_CPP_HEADER
#define FSP_FOOTER    FSP_CPP_FOOTER

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/** Macro to be used when argument to function is ignored since function call is NSC and the parameter is statically
 *  defined on the Secure side. */
#define FSP_SECURE_ARGUMENT    (NULL)

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Common error codes */
typedef enum e_fsp_err
{
    FSP_SUCCESS = 0,

    FSP_ERR_ASSERTION             = 1,                      ///< A critical assertion has failed
    FSP_ERR_INVALID_POINTER       = 2,                      ///< Pointer points to invalid memory location
    FSP_ERR_INVALID_ARGUMENT      = 3,                      ///< Invalid input parameter
    FSP_ERR_INVALID_CHANNEL       = 4,                      ///< Selected channel does not exist
    FSP_ERR_INVALID_MODE          = 5,                      ///< Unsupported or incorrect mode
    FSP_ERR_UNSUPPORTED           = 6,                      ///< Selected mode not supported by this API
    FSP_ERR_NOT_OPEN              = 7,                      ///< Requested channel is not configured or API not open
    FSP_ERR_IN_USE                = 8,                      ///< Channel/peripheral is running/busy
    FSP_ERR_OUT_OF_MEMORY         = 9,                      ///< Allocate more memory in the driver's cfg.h
    FSP_ERR_HW_LOCKED             = 10,                     ///< Hardware is locked
    FSP_ERR_IRQ_BSP_DISABLED      = 11,                     ///< IRQ not enabled in BSP
    FSP_ERR_OVERFLOW              = 12,                     ///< Hardware overflow
    FSP_ERR_UNDERFLOW             = 13,                     ///< Hardware underflow
    FSP_ERR_ALREADY_OPEN          = 14,                     ///< Requested channel is already open in a different configuration
    FSP_ERR_APPROXIMATION         = 15,                     ///< Could not set value to exact result
    FSP_ERR_CLAMPED               = 16,                     ///< Value had to be limited for some reason
    FSP_ERR_INVALID_RATE          = 17,                     ///< Selected rate could not be met
    FSP_ERR_ABORTED               = 18,                     ///< An operation was aborted
    FSP_ERR_NOT_ENABLED           = 19,                     ///< Requested operation is not enabled
    FSP_ERR_TIMEOUT               = 20,                     ///< Timeout error
    FSP_ERR_INVALID_BLOCKS        = 21,                     ///< Invalid number of blocks supplied
    FSP_ERR_INVALID_ADDRESS       = 22,                     ///< Invalid address supplied
    FSP_ERR_INVALID_SIZE          = 23,                     ///< Invalid size/length supplied for operation
    FSP_ERR_WRITE_FAILED          = 24,                     ///< Write operation failed
    FSP_ERR_ERASE_FAILED          = 25,                     ///< Erase operation failed
    FSP_ERR_INVALID_CALL          = 26,                     ///< Invalid function call is made
    FSP_ERR_INVALID_HW_CONDITION  = 27,                     ///< Detected hardware is in invalid condition
    FSP_ERR_INVALID_FACTORY_FLASH = 28,                     ///< Factory flash is not available on this MCU
    FSP_ERR_INVALID_STATE         = 30,                     ///< API or command not valid in the current state
    FSP_ERR_NOT_ERASED            = 31,                     ///< Erase verification failed
    FSP_ERR_SECTOR_RELEASE_FAILED = 32,                     ///< Sector release failed
    FSP_ERR_NOT_INITIALIZED       = 33,                     ///< Required initialization not complete
    FSP_ERR_NOT_FOUND             = 34,                     ///< The requested item could not be found
    FSP_ERR_NO_CALLBACK_MEMORY    = 35,                     ///< Non-secure callback memory not provided for non-secure callback
    FSP_ERR_BUFFER_EMPTY          = 36,                     ///< No data available in buffer
    FSP_ERR_INVALID_DATA          = 37,                     ///< Accuracy of data is not guaranteed

    /* Start of RTOS only error codes */
    FSP_ERR_INTERNAL     = 100,                             ///< Internal error
    FSP_ERR_WAIT_ABORTED = 101,                             ///< Wait aborted

    /* Start of UART specific */
    FSP_ERR_FRAMING            = 200,                       ///< Framing error occurs
    FSP_ERR_BREAK_DETECT       = 201,                       ///< Break signal detects
    FSP_ERR_PARITY             = 202,                       ///< Parity error occurs
    FSP_ERR_RXBUF_OVERFLOW     = 203,                       ///< Receive queue overflow
    FSP_ERR_QUEUE_UNAVAILABLE  = 204,                       ///< Can't open s/w queue
    FSP_ERR_INSUFFICIENT_SPACE = 205,                       ///< Not enough space in transmission circular buffer
    FSP_ERR_INSUFFICIENT_DATA  = 206,                       ///< Not enough data in receive circular buffer

    /* Start of SPI specific */
    FSP_ERR_TRANSFER_ABORTED = 300,                         ///< The data transfer was aborted.
    FSP_ERR_MODE_FAULT       = 301,                         ///< Mode fault error.
    FSP_ERR_READ_OVERFLOW    = 302,                         ///< Read overflow.
    FSP_ERR_SPI_PARITY       = 303,                         ///< Parity error.
    FSP_ERR_OVERRUN          = 304,                         ///< Overrun error.

    /* Start of CGC Specific */
    FSP_ERR_CLOCK_INACTIVE        = 400,                    ///< Inactive clock specified as system clock.
    FSP_ERR_CLOCK_ACTIVE          = 401,                    ///< Active clock source cannot be modified without stopping first.
    FSP_ERR_NOT_STABILIZED        = 403,                    ///< Clock has not stabilized after its been turned on/off
    FSP_ERR_PLL_SRC_INACTIVE      = 404,                    ///< PLL initialization attempted when PLL source is turned off
    FSP_ERR_OSC_STOP_DET_ENABLED  = 405,                    ///< Illegal attempt to stop LOCO when Oscillation stop is enabled
    FSP_ERR_OSC_STOP_DETECTED     = 406,                    ///< The Oscillation stop detection status flag is set
    FSP_ERR_OSC_STOP_CLOCK_ACTIVE = 407,                    ///< Attempt to clear Oscillation Stop Detect Status with PLL/MAIN_OSC active
    FSP_ERR_CLKOUT_EXCEEDED       = 408,                    ///< Output on target output clock pin exceeds maximum supported limit
    FSP_ERR_USB_MODULE_ENABLED    = 409,                    ///< USB clock configure request with USB Module enabled
    FSP_ERR_HARDWARE_TIMEOUT      = 410,                    ///< A register read or write timed out
    FSP_ERR_LOW_VOLTAGE_MODE      = 411,                    ///< Invalid clock setting attempted in low voltage mode

    /* Start of FLASH Specific */
    FSP_ERR_PE_FAILURE             = 500,                   ///< Unable to enter Programming mode.
    FSP_ERR_CMD_LOCKED             = 501,                   ///< Peripheral in command locked state
    FSP_ERR_FCLK                   = 502,                   ///< FCLK must be >= 4 MHz
    FSP_ERR_INVALID_LINKED_ADDRESS = 503,                   ///< Function or data are linked at an invalid region of memory
    FSP_ERR_BLANK_CHECK_FAILED     = 504,                   ///< Blank check operation failed
    FSP_ERR_HUK_ZEROIZATION        = 505,                   ///< W-HUK zeroization is in progress

    /* Start of CAC Specific */
    FSP_ERR_INVALID_CAC_REF_CLOCK = 600,                    ///< Measured clock rate < reference clock rate

    /* Start of IIRFA Specific */
    FSP_ERR_INVALID_RESULT = 700,                           ///< The result of one or more calculations was +/- infinity.

    /* Start of GLCD Specific */
    FSP_ERR_CLOCK_GENERATION           = 1000,              ///< Clock cannot be specified as system clock
    FSP_ERR_INVALID_TIMING_SETTING     = 1001,              ///< Invalid timing parameter
    FSP_ERR_INVALID_LAYER_SETTING      = 1002,              ///< Invalid layer parameter
    FSP_ERR_INVALID_ALIGNMENT          = 1003,              ///< Invalid memory alignment found
    FSP_ERR_INVALID_GAMMA_SETTING      = 1004,              ///< Invalid gamma correction parameter
    FSP_ERR_INVALID_LAYER_FORMAT       = 1005,              ///< Invalid color format in layer
    FSP_ERR_INVALID_UPDATE_TIMING      = 1006,              ///< Invalid timing for register update
    FSP_ERR_INVALID_CLUT_ACCESS        = 1007,              ///< Invalid access to CLUT entry
    FSP_ERR_INVALID_FADE_SETTING       = 1008,              ///< Invalid fade-in/fade-out setting
    FSP_ERR_INVALID_BRIGHTNESS_SETTING = 1009,              ///< Invalid gamma correction parameter

    /* Start of JPEG Specific */
    FSP_ERR_JPEG_ERR                                = 1100, ///< JPEG error
    FSP_ERR_JPEG_SOI_NOT_DETECTED                   = 1101, ///< SOI not detected until EOI detected.
    FSP_ERR_JPEG_SOF1_TO_SOFF_DETECTED              = 1102, ///< SOF1 to SOFF detected.
    FSP_ERR_JPEG_UNSUPPORTED_PIXEL_FORMAT           = 1103, ///< Unprovided pixel format detected.
    FSP_ERR_JPEG_SOF_ACCURACY_ERROR                 = 1104, ///< SOF accuracy error: other than 8 detected.
    FSP_ERR_JPEG_DQT_ACCURACY_ERROR                 = 1105, ///< DQT accuracy error: other than 0 detected.
    FSP_ERR_JPEG_COMPONENT_ERROR1                   = 1106, ///< Component error 1: the number of SOF0 header components detected is other than 1, 3, or 4.
    FSP_ERR_JPEG_COMPONENT_ERROR2                   = 1107, ///< Component error 2: the number of components differs between SOF0 header and SOS.
    FSP_ERR_JPEG_SOF0_DQT_DHT_NOT_DETECTED          = 1108, ///< SOF0, DQT, and DHT not detected when SOS detected.
    FSP_ERR_JPEG_SOS_NOT_DETECTED                   = 1109, ///< SOS not detected: SOS not detected until EOI detected.
    FSP_ERR_JPEG_EOI_NOT_DETECTED                   = 1110, ///< EOI not detected (default)
    FSP_ERR_JPEG_RESTART_INTERVAL_DATA_NUMBER_ERROR = 1111, ///< Restart interval data number error detected.
    FSP_ERR_JPEG_IMAGE_SIZE_ERROR                   = 1112, ///< Image size error detected.
    FSP_ERR_JPEG_LAST_MCU_DATA_NUMBER_ERROR         = 1113, ///< Last MCU data number error detected.
    FSP_ERR_JPEG_BLOCK_DATA_NUMBER_ERROR            = 1114, ///< Block data number error detected.
    FSP_ERR_JPEG_BUFFERSIZE_NOT_ENOUGH              = 1115, ///< User provided buffer size not enough
    FSP_ERR_JPEG_UNSUPPORTED_IMAGE_SIZE             = 1116, ///< JPEG Image size is not aligned with MCU

    /* Start of touch panel framework specific */
    FSP_ERR_CALIBRATE_FAILED = 1200,                        ///< Calibration failed

    /* Start of IIRFA specific */
    FSP_ERR_IIRFA_ECC_1BIT = 1300,                          ///< 1-bit ECC error detected
    FSP_ERR_IIRFA_ECC_2BIT = 1301,                          ///< 2-bit ECC error detected

    /* Start of IP specific */
    FSP_ERR_IP_HARDWARE_NOT_PRESENT = 1400,                 ///< Requested IP does not exist on this device
    FSP_ERR_IP_UNIT_NOT_PRESENT     = 1401,                 ///< Requested unit does not exist on this device
    FSP_ERR_IP_CHANNEL_NOT_PRESENT  = 1402,                 ///< Requested channel does not exist on this device

    /* Start of USB specific */
    FSP_ERR_USB_FAILED      = 1500,
    FSP_ERR_USB_BUSY        = 1501,
    FSP_ERR_USB_SIZE_SHORT  = 1502,
    FSP_ERR_USB_SIZE_OVER   = 1503,
    FSP_ERR_USB_NOT_OPEN    = 1504,
    FSP_ERR_USB_NOT_SUSPEND = 1505,
    FSP_ERR_USB_PARAMETER   = 1506,

    /* Start of Message framework specific */
    FSP_ERR_NO_MORE_BUFFER           = 2000,         ///< No more buffer found in the memory block pool
    FSP_ERR_ILLEGAL_BUFFER_ADDRESS   = 2001,         ///< Buffer address is out of block memory pool
    FSP_ERR_INVALID_WORKBUFFER_SIZE  = 2002,         ///< Work buffer size is invalid
    FSP_ERR_INVALID_MSG_BUFFER_SIZE  = 2003,         ///< Message buffer size is invalid
    FSP_ERR_TOO_MANY_BUFFERS         = 2004,         ///< Number of buffer is too many
    FSP_ERR_NO_SUBSCRIBER_FOUND      = 2005,         ///< No message subscriber found
    FSP_ERR_MESSAGE_QUEUE_EMPTY      = 2006,         ///< No message found in the message queue
    FSP_ERR_MESSAGE_QUEUE_FULL       = 2007,         ///< No room for new message in the message queue
    FSP_ERR_ILLEGAL_SUBSCRIBER_LISTS = 2008,         ///< Message subscriber lists is illegal
    FSP_ERR_BUFFER_RELEASED          = 2009,         ///< Buffer has been released

    /* Start of 2DG Driver specific */
    FSP_ERR_D2D_ERROR_INIT      = 3000,              ///< D/AVE 2D has an error in the initialization
    FSP_ERR_D2D_ERROR_DEINIT    = 3001,              ///< D/AVE 2D has an error in the initialization
    FSP_ERR_D2D_ERROR_RENDERING = 3002,              ///< D/AVE 2D has an error in the rendering
    FSP_ERR_D2D_ERROR_SIZE      = 3003,              ///< D/AVE 2D has an error in the rendering

    /* Start of ETHER Driver specific */
    FSP_ERR_ETHER_ERROR_NO_DATA              = 4000, ///< No Data in Receive buffer.
    FSP_ERR_ETHER_ERROR_LINK                 = 4001, ///< ETHERC/EDMAC has an error in the Auto-negotiation
    FSP_ERR_ETHER_ERROR_MAGIC_PACKET_MODE    = 4002, ///< As a Magic Packet is being detected, and transmission/reception is not enabled
    FSP_ERR_ETHER_ERROR_TRANSMIT_BUFFER_FULL = 4003, ///< Transmit buffer is not empty
    FSP_ERR_ETHER_ERROR_FILTERING            = 4004, ///< Detect multicast frame when multicast frame filtering enable
    FSP_ERR_ETHER_ERROR_PHY_COMMUNICATION    = 4005, ///< ETHERC/EDMAC has an error in the phy communication
    FSP_ERR_ETHER_RECEIVE_BUFFER_ACTIVE      = 4006, ///< Receive buffer is active.

    /* Start of ETHER_PHY Driver specific */
    FSP_ERR_ETHER_PHY_ERROR_LINK = 5000,             ///< PHY is not link up.
    FSP_ERR_ETHER_PHY_NOT_READY  = 5001,             ///< PHY has an error in the Auto-negotiation

    /* Start of BYTEQ library specific */
    FSP_ERR_QUEUE_FULL  = 10000,                     ///< Queue is full, cannot queue another data
    FSP_ERR_QUEUE_EMPTY = 10001,                     ///< Queue is empty, no data to dequeue

    /* Start of CTSU Driver specific */
    FSP_ERR_CTSU_SCANNING              = 6000,       ///< Scanning.
    FSP_ERR_CTSU_NOT_GET_DATA          = 6001,       ///< Not processed previous scan data.
    FSP_ERR_CTSU_INCOMPLETE_TUNING     = 6002,       ///< Incomplete initial offset tuning.
    FSP_ERR_CTSU_DIAG_NOT_YET          = 6003,       ///< Diagnosis of data collected no yet.
    FSP_ERR_CTSU_DIAG_LDO_OVER_VOLTAGE = 6004,       ///< Diagnosis of LDO over voltage failed.
    FSP_ERR_CTSU_DIAG_CCO_HIGH         = 6005,       ///< Diagnosis of CCO into 19.2uA failed.
    FSP_ERR_CTSU_DIAG_CCO_LOW          = 6006,       ///< Diagnosis of CCO into 2.4uA failed.
    FSP_ERR_CTSU_DIAG_SSCG             = 6007,       ///< Diagnosis of SSCG frequency failed.
    FSP_ERR_CTSU_DIAG_DAC              = 6008,       ///< Diagnosis of non-touch count value failed.
    FSP_ERR_CTSU_DIAG_OUTPUT_VOLTAGE   = 6009,       ///< Diagnosis of LDO output voltage failed.
    FSP_ERR_CTSU_DIAG_OVER_VOLTAGE     = 6010,       ///< Diagnosis of over voltage detection circuit failed.
    FSP_ERR_CTSU_DIAG_OVER_CURRENT     = 6011,       ///< Diagnosis of over current detection circuit failed.
    FSP_ERR_CTSU_DIAG_LOAD_RESISTANCE  = 6012,       ///< Diagnosis of LDO internal resistance value failed.
    FSP_ERR_CTSU_DIAG_CURRENT_SOURCE   = 6013,       ///< Diagnosis of Current source value failed.
    FSP_ERR_CTSU_DIAG_SENSCLK_GAIN     = 6014,       ///< Diagnosis of SENSCLK frequency gain failed.
    FSP_ERR_CTSU_DIAG_SUCLK_GAIN       = 6015,       ///< Diagnosis of SUCLK frequency gain failed.
    FSP_ERR_CTSU_DIAG_CLOCK_RECOVERY   = 6016,       ///< Diagnosis of SUCLK clock recovery function failed.
    FSP_ERR_CTSU_DIAG_CFC_GAIN         = 6017,       ///< Diagnosis of CFC oscillator gain failed.

    /* Start of SDMMC specific */
    FSP_ERR_CARD_INIT_FAILED     = 40000,            ///< SD card or eMMC device failed to initialize.
    FSP_ERR_CARD_NOT_INSERTED    = 40001,            ///< SD card not installed.
    FSP_ERR_DEVICE_BUSY          = 40002,            ///< Device is holding DAT0 low or another operation is ongoing.
    FSP_ERR_CARD_NOT_INITIALIZED = 40004,            ///< SD card was removed.
    FSP_ERR_CARD_WRITE_PROTECTED = 40005,            ///< Media is write protected.
    FSP_ERR_TRANSFER_BUSY        = 40006,            ///< Transfer in progress.
    FSP_ERR_RESPONSE             = 40007,            ///< Card did not respond or responded with an error.

    /* Start of FX_IO specific */
    FSP_ERR_MEDIA_FORMAT_FAILED = 50000,             ///< Media format failed.
    FSP_ERR_MEDIA_OPEN_FAILED   = 50001,             ///< Media open failed.

    /* Start of CAN specific */
    FSP_ERR_CAN_DATA_UNAVAILABLE   = 60000,          ///< No data available.
    FSP_ERR_CAN_MODE_SWITCH_FAILED = 60001,          ///< Switching operation modes failed.
    FSP_ERR_CAN_INIT_FAILED        = 60002,          ///< Hardware initialization failed.
    FSP_ERR_CAN_TRANSMIT_NOT_READY = 60003,          ///< Transmit in progress.
    FSP_ERR_CAN_RECEIVE_MAILBOX    = 60004,          ///< Mailbox is setup as a receive mailbox.
    FSP_ERR_CAN_TRANSMIT_MAILBOX   = 60005,          ///< Mailbox is setup as a transmit mailbox.
    FSP_ERR_CAN_MESSAGE_LOST       = 60006,          ///< Receive message has been overwritten or overrun.
    FSP_ERR_CAN_TRANSMIT_FIFO_FULL = 60007,          ///< Transmit FIFO is full.

    /* Start of SF_WIFI Specific */
    FSP_ERR_WIFI_CONFIG_FAILED    = 70000,           ///< WiFi module Configuration failed.
    FSP_ERR_WIFI_INIT_FAILED      = 70001,           ///< WiFi module initialization failed.
    FSP_ERR_WIFI_TRANSMIT_FAILED  = 70002,           ///< Transmission failed
    FSP_ERR_WIFI_INVALID_MODE     = 70003,           ///< API called when provisioned in client mode
    FSP_ERR_WIFI_FAILED           = 70004,           ///< WiFi Failed.
    FSP_ERR_WIFI_SCAN_COMPLETE    = 70005,           ///< Wifi scan has completed.
    FSP_ERR_WIFI_AP_NOT_CONNECTED = 70006,           ///< WiFi module is not connected to access point
    FSP_ERR_WIFI_UNKNOWN_AT_CMD   = 70007,           ///< DA16XXX Unknown AT command Error
    FSP_ERR_WIFI_INSUF_PARAM      = 70008,           ///< DA16XXX Insufficient parameter
    FSP_ERR_WIFI_TOO_MANY_PARAMS  = 70009,           ///< DA16XXX Too many parameters
    FSP_ERR_WIFI_INV_PARAM_VAL    = 70010,           ///< DA16XXX Wrong parameter value
    FSP_ERR_WIFI_NO_RESULT        = 70011,           ///< DA16XXX No result
    FSP_ERR_WIFI_RSP_BUF_OVFLW    = 70012,           ///< DA16XXX Response buffer overflow
    FSP_ERR_WIFI_FUNC_NOT_CONFIG  = 70013,           ///< DA16XXX Function is not configured
    FSP_ERR_WIFI_NVRAM_WR_FAIL    = 70014,           ///< DA16XXX NVRAM write failure
    FSP_ERR_WIFI_RET_MEM_WR_FAIL  = 70015,           ///< DA16XXX Retention memory write failure
    FSP_ERR_WIFI_UNKNOWN_ERR      = 70016,           ///< DA16XXX unknown error

    /* Start of SF_CELLULAR Specific */
    FSP_ERR_CELLULAR_CONFIG_FAILED       = 80000,    ///< Cellular module Configuration failed.
    FSP_ERR_CELLULAR_INIT_FAILED         = 80001,    ///< Cellular module initialization failed.
    FSP_ERR_CELLULAR_TRANSMIT_FAILED     = 80002,    ///< Transmission failed
    FSP_ERR_CELLULAR_FW_UPTODATE         = 80003,    ///< Firmware is uptodate
    FSP_ERR_CELLULAR_FW_UPGRADE_FAILED   = 80004,    ///< Firmware upgrade failed
    FSP_ERR_CELLULAR_FAILED              = 80005,    ///< Cellular Failed.
    FSP_ERR_CELLULAR_INVALID_STATE       = 80006,    ///< API Called in invalid state.
    FSP_ERR_CELLULAR_REGISTRATION_FAILED = 80007,    ///< Cellular Network registration failed

    /* Start of SF_BLE specific */
    FSP_ERR_BLE_FAILED              = 90001,         ///< BLE operation failed
    FSP_ERR_BLE_INIT_FAILED         = 90002,         ///< BLE device initialization failed
    FSP_ERR_BLE_CONFIG_FAILED       = 90003,         ///< BLE device configuration failed
    FSP_ERR_BLE_PRF_ALREADY_ENABLED = 90004,         ///< BLE device Profile already enabled
    FSP_ERR_BLE_PRF_NOT_ENABLED     = 90005,         ///< BLE device not enabled

    /* Start of SF_BLE_ABS specific */
    FSP_ERR_BLE_ABS_INVALID_OPERATION = 91001,       ///< Invalid operation is executed.
    FSP_ERR_BLE_ABS_NOT_FOUND         = 91002,       ///< Valid data or free space is not found.

    /* Start of Crypto specific (0x10000) @note Refer to sf_cryoto_err.h for Crypto error code. */
    FSP_ERR_CRYPTO_CONTINUE              = 0x10000,  ///< Continue executing function
    FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT = 0x10001,  ///< Hardware resource busy
    FSP_ERR_CRYPTO_SCE_FAIL              = 0x10002,  ///< Internal I/O buffer is not empty
    FSP_ERR_CRYPTO_SCE_HRK_INVALID_INDEX = 0x10003,  ///< Invalid index
    FSP_ERR_CRYPTO_SCE_RETRY             = 0x10004,  ///< Retry
    FSP_ERR_CRYPTO_SCE_VERIFY_FAIL       = 0x10005,  ///< Verify is failed
    FSP_ERR_CRYPTO_SCE_ALREADY_OPEN      = 0x10006,  ///< HW SCE module is already opened
    FSP_ERR_CRYPTO_NOT_OPEN              = 0x10007,  ///< Hardware module is not initialized
    FSP_ERR_CRYPTO_UNKNOWN               = 0x10008,  ///< Some unknown error occurred
    FSP_ERR_CRYPTO_NULL_POINTER          = 0x10009,  ///< Null pointer input as a parameter
    FSP_ERR_CRYPTO_NOT_IMPLEMENTED       = 0x1000a,  ///< Algorithm/size not implemented
    FSP_ERR_CRYPTO_RNG_INVALID_PARAM     = 0x1000b,  ///< An invalid parameter is specified
    FSP_ERR_CRYPTO_RNG_FATAL_ERROR       = 0x1000c,  ///< A fatal error occurred
    FSP_ERR_CRYPTO_INVALID_SIZE          = 0x1000d,  ///< Size specified is invalid
    FSP_ERR_CRYPTO_INVALID_STATE         = 0x1000e,  ///< Function used in an valid state
    FSP_ERR_CRYPTO_ALREADY_OPEN          = 0x1000f,  ///< control block is already opened
    FSP_ERR_CRYPTO_INSTALL_KEY_FAILED    = 0x10010,  ///< Specified input key is invalid.
    FSP_ERR_CRYPTO_AUTHENTICATION_FAILED = 0x10011,  ///< Authentication failed
    FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      = 0x10012,  ///< Failure to Init Cipher
    FSP_ERR_CRYPTO_SCE_AUTHENTICATION    = 0x10013,  ///< Authentication failed
    FSP_ERR_CRYPTO_SCE_PARAMETER         = 0x10014,  ///< Input date is illegal.
    FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION = 0x10015,  ///< An invalid function call occurred.

    FSP_ERR_CRYPTO_SCE_LBIST_CHECK_BUSY  = 0x100ff,  ///< LBIST Check BUSY

    /* Start of Crypto RSIP specific (0x10100) */
    FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT = 0x10100, ///< Hardware resource is busy
    FSP_ERR_CRYPTO_RSIP_FATAL             = 0x10101, ///< Hardware fatal error or unexpected return
    FSP_ERR_CRYPTO_RSIP_FAIL              = 0x10102, ///< Internal error
    FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      = 0x10103, ///< Input key type is illegal
    FSP_ERR_CRYPTO_RSIP_AUTHENTICATION    = 0x10104, ///< Authentication failed

    FSP_ERR_CRYPTO_RSIP_LBIST_CHECK_BUSY  = 0x101ff, ///< LBIST Check BUSY

    /* Start of SF_CRYPTO specific */
    FSP_ERR_CRYPTO_COMMON_NOT_OPENED      = 0x20000, ///< Crypto Framework Common is not opened
    FSP_ERR_CRYPTO_HAL_ERROR              = 0x20001, ///< Cryoto HAL module returned an error
    FSP_ERR_CRYPTO_KEY_BUF_NOT_ENOUGH     = 0x20002, ///< Key buffer size is not enough to generate a key
    FSP_ERR_CRYPTO_BUF_OVERFLOW           = 0x20003, ///< Attempt to write data larger than what the buffer can hold
    FSP_ERR_CRYPTO_INVALID_OPERATION_MODE = 0x20004, ///< Invalid operation mode.
    FSP_ERR_MESSAGE_TOO_LONG              = 0x20005, ///< Message for RSA encryption is too long.
    FSP_ERR_RSA_DECRYPTION_ERROR          = 0x20006, ///< RSA Decryption error.

    /** @note SF_CRYPTO APIs may return an error code starting from 0x10000 which is of Crypto module.
     *        Refer to sf_cryoto_err.h for Crypto error codes.
     */

    /* Start of Sensor specific */
    FSP_ERR_SENSOR_INVALID_DATA             = 0x30000, ///< Data is invalid.
    FSP_ERR_SENSOR_IN_STABILIZATION         = 0x30001, ///< Sensor is stabilizing.
    FSP_ERR_SENSOR_MEASUREMENT_NOT_FINISHED = 0x30002, ///< Measurement is not finished.

    /* Start of COMMS specific */
    FSP_ERR_COMMS_BUS_NOT_OPEN = 0x40000,              ///< Bus is not open.
} fsp_err_t;

/** @} */

/***********************************************************************************************************************
 * Function prototypes
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
