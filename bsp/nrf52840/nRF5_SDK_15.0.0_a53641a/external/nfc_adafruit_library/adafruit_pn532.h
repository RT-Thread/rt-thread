/*
 * Adafruit PN532 library adapted to use in nRF51 and nRF52
 *
 * Software License Agreement (BSD License)
 *
 * Copyright (c) 2012, Adafruit Industries
 * All rights reserved.

 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holders nor the
 * names of its contributors may be used to endorse or promote products
 * derived from this software without specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef ADAFRUIT_PN532__
#define ADAFRUIT_PN532__

#include <stdint.h>
#include <stdbool.h>
#include "sdk_errors.h"

/** @file
 *  @brief Adafruit PN532 NFC Shield library for reading and writing tags.
 *
 *  @defgroup adafruit_pn532 Adafruit PN532 NFC Shield library
 *  @{
 *  @ingroup app_common
 *  @brief Adafruit PN532 NFC Shield library for reading and writing tags.
 *
 *  This library is an nRF51 and nRF52 port of the Adafruit PN532 library,
 *  which is available on <a href="https://github.com/adafruit/Adafruit-PN532" target="_blank">GitHub</a>,
 *  with some improvements and bugfixes. The library is responsible for
 *  communicating with the Adafruit PN532 NFC Shield and using its main
 *  functions.
 *
 *  This library can be used with an <a href="https://www.adafruit.com/products/789" target="_blank">Adafruit PN532 NFC/RFID Controller Shield</a>.
 */

/**
 * @defgroup nrf_external_adafruit_pn532_frame_header Frame header
 * @brief Macros related to the frame header and checksum parts.
 *
 *
 * Sizes of the header and checksum parts of the frame.
 * @{
 */
#define HEADER_SEQUENCE_LENGTH   6
#define CHECKSUM_SEQUENCE_LENGTH 2
#define PN532_FRAME_OVERHEAD     (HEADER_SEQUENCE_LENGTH + CHECKSUM_SEQUENCE_LENGTH)
/** @} */

/**
 * @defgroup nrf_external_adafruit_pn532_frame_tokens Frame tokens and offsets
 * @brief Macros related to frame tokens and offsets.
 *
 * @{
 *
 * @name Tokens
 * @brief Start and end location of frame token identifiers.
 * @{
 */
#define PN532_PREAMBLE          (0x00)
#define PN532_STARTCODE1        (0x00)
#define PN532_STARTCODE2        (0xFF)
#define PN532_POSTAMBLE         (0x00)
/**
 * @}
 *
 * @name Offsets
 * @{
 */
#define PN532_PREAMBLE_OFFSET   0
#define PN532_STARTCODE1_OFFSET 1
#define PN532_STARTCODE2_OFFSET 2
#define PN532_LENGTH_OFFSET     3
#define PN532_LENGTH_CS_OFFSET  4
#define PN532_TFI_OFFSET        5
#define PN532_DATA_OFFSET       6
/**
 * @}
 * @}
 */

/**
 * @defgroup nrf_external_adafruit_pn532_frame_direction_identifiers Frame direction identifiers
 * @brief Macro codes identifying the communication direction.
 *
 * Each frame contains one of these codes to identify whether this frame
 * was sent to or received from the Adafruit PN532 Shield.
 * @{
 */
#define PN532_HOSTTOPN532 (0xD4)
#define PN532_PN532TOHOST (0xD5)
/** @} */

/**
 * @defgroup nrf_external_adafruit_pn532_command_codes Command codes
 * @brief Macros for the available command codes.
 *
 * The following command codes are available in the Adafruit PN532 Shield.
 * @{
 */
#define PN532_COMMAND_DIAGNOSE              (0x00)
#define PN532_COMMAND_GETFIRMWAREVERSION    (0x02)
#define PN532_COMMAND_GETGENERALSTATUS      (0x04)
#define PN532_COMMAND_READREGISTER          (0x06)
#define PN532_COMMAND_WRITEREGISTER         (0x08)
#define PN532_COMMAND_READGPIO              (0x0C)
#define PN532_COMMAND_WRITEGPIO             (0x0E)
#define PN532_COMMAND_SETSERIALBAUDRATE     (0x10)
#define PN532_COMMAND_SETPARAMETERS         (0x12)
#define PN532_COMMAND_SAMCONFIGURATION      (0x14)
#define PN532_COMMAND_POWERDOWN             (0x16)
#define PN532_COMMAND_RFCONFIGURATION       (0x32)
#define PN532_COMMAND_RFREGULATIONTEST      (0x58)
#define PN532_COMMAND_INJUMPFORDEP          (0x56)
#define PN532_COMMAND_INJUMPFORPSL          (0x46)
#define PN532_COMMAND_INLISTPASSIVETARGET   (0x4A)
#define PN532_COMMAND_INATR                 (0x50)
#define PN532_COMMAND_INPSL                 (0x4E)
#define PN532_COMMAND_INDATAEXCHANGE        (0x40)
#define PN532_COMMAND_INCOMMUNICATETHRU     (0x42)
#define PN532_COMMAND_INDESELECT            (0x44)
#define PN532_COMMAND_INRELEASE             (0x52)
#define PN532_COMMAND_INSELECT              (0x54)
#define PN532_COMMAND_INAUTOPOLL            (0x60)
#define PN532_COMMAND_TGINITASTARGET        (0x8C)
#define PN532_COMMAND_TGSETGENERALBYTES     (0x92)
#define PN532_COMMAND_TGGETDATA             (0x86)
#define PN532_COMMAND_TGSETDATA             (0x8E)
#define PN532_COMMAND_TGSETMETADATA         (0x94)
#define PN532_COMMAND_TGGETINITIATORCOMMAND (0x88)
#define PN532_COMMAND_TGRESPONSETOINITIATOR (0x90)
#define PN532_COMMAND_TGGETTARGETSTATUS     (0x8A)
/** @} */

/**
 * @defgroup nrf_external_adafruit_pn532_mifare_command_codes Mifare command codes
 * @brief Macros for the available Mifare command codes.
 *
 * The following Mifare command codes are available in the Adafruit PN532 Shield.
 * @{
 */
#define MIFARE_CMD_AUTH_A           (0x60)
#define MIFARE_CMD_AUTH_B           (0x61)
#define MIFARE_CMD_READ             (0x30)
#define MIFARE_CMD_WRITE            (0xA0)
#define MIFARE_CMD_TRANSFER         (0xB0)
#define MIFARE_CMD_DECREMENT        (0xC0)
#define MIFARE_CMD_INCREMENT        (0xC1)
#define MIFARE_CMD_STORE            (0xC2)
#define MIFARE_ULTRALIGHT_CMD_WRITE (0xA2)
/** @} */

/**
 * @defgroup nrf_external_adafruit_pn532_t2t Type 2 Tag specific parameters
 * @brief Macros for Type 2 Tag specific parameters.
 * @{
 */
#define T2T_MAX_DATA_EXCHANGE            16 ///< Type 2 Tag maximal command data size (in bytes).
#define T2T_PAGE_SIZE                    4  ///< Type 2 Tag page/block size (in bytes).
#define T2T_END_PAGE_OFFSET              3  ///< Offset of the last page/block in Type 2 Tag response payload.
/** @} */

/**
 * @defgroup nrf_external_adafruit_pn532_nfc_a NFC-A initialisation response parameters.
 * @brief Macros for NFC-A initialisation response parameters.
 * @{
 */
#define SENS_RES_ANTICOLLISION_INFO_BYTE 0
#define SENS_RES_PLATFORM_INFO_BYTE      1
#define SENS_RES_SIZE                    2
#define MAX_NFC_A_ID_LEN                 10
/** @} */

#define PN532_MIFARE_ISO14443A_BAUD      (0x00)      ///< Code identifying the baud rate for the ISO14443A (NFC-A) card type.

#define PN532_I2C_ADDRESS                (0x48 >> 1) ///< Address of the I2C peripheral of the Adafruit PN532 Shield.

#ifndef PN532_PACKBUFF_SIZE
    #define PN532_PACKBUFF_SIZE 64
#endif

/**
 * @brief Basic information about detected NFC-A tag.
 */
typedef struct
{
    uint8_t sens_res[SENS_RES_SIZE];  ///< SENS_RES response bytes.
    uint8_t sel_res;                  ///< SEL_RES response byte.
    uint8_t nfc_id_len;               ///< UID length.
    uint8_t nfc_id[MAX_NFC_A_ID_LEN]; ///< NFC-A UID.
} nfc_a_tag_info;

/**
 * @name Functions used for initialization
 *
 * @{ */

/**  @brief Function for initializing the communication with the Adafruit PN532 Shield.
 *
 *   @note This library is not thread-safe, because it uses static buffers.
 *
 *   @param[in] force           If true, reinitialization of the library will be forced.
 *
 *   @retval    NRF_SUCCESS     If the communication was initialized successfully. Otherwise,
 *                              an error code is returned.
 */
ret_code_t adafruit_pn532_init(bool force);

/**  @brief Function for creating a new PN532 object using I2C.
 *
 *   Before calling this function, PN532_IRQ and PN532_RESET must be configured.
 *
 *   @retval    NRF_SUCCESS     If the object was created successfully. Otherwise,
 *                              an error code is returned.
 */
ret_code_t adafruit_pn532_i2c_create(void);
/** @} */

/**
 * @name Generic functions for the Adafruit PN532 Shield
 *
 * @{ */

/**  @brief Function for configuring the Secure Access Module (SAM).
 *
 *   This function configures the SAM to work in a mode specified in the mode parameter. For a reader
 *   operation, use SAMCONFIGURATION_MODE_NORMAL.
 *
 *   @param[in] mode            Mode in which the PN532 Shield should work.
 *
 *   @retval    NRF_SUCCESS     If the SAM was configured successfully. Otherwise,
 *                              an error code is returned.
 */
ret_code_t adafruit_pn532_sam_config(uint8_t mode);

/**  @brief Function for entering power-down mode with I2C as wake-up source.
 *
 *   @retval    NRF_SUCCESS     If power-down mode was entered successfully. Otherwise,
 *                              an error code is returned.
 */
ret_code_t adafruit_pn532_power_down(void);

/**  @brief Function for waking up the PN532 Shield from power-down mode.
 *
 *   @retval    NRF_SUCCESS     If the PN532 Shield woke up successfully. Otherwise,
 *                              an error code is returned.
 */
ret_code_t adafruit_pn532_wake_up(void);

/**  @brief Function for checking the firmware version of the PN532 chip.
 *
 *   @param[out]    p_response      The chip's firmware version and ID.
 *
 *   @retval        NRF_SUCCESS     If the function completed successfully. Otherwise,
 *                                  an error code is returned.
 */
ret_code_t adafruit_pn532_firmware_version_get(uint32_t * p_response);

/**  @brief Function for sending a command and waiting a specified period for the ACK.
 *
 *   @param[in] p_cmd                  Pointer to the command buffer.
 *   @param[in] cmd_len                The length of the command (in bytes).
 *   @param[in] timeout                Time-out (in ms) before giving up.
 *
 *   @retval    NRF_SUCCESS            If the command was sent successfully. Otherwise,
 *                                     an error code is returned.
 */
ret_code_t adafruit_pn532_cmd_send(uint8_t * p_cmd, uint8_t cmd_len, uint16_t timeout);

/**  @brief Function for enabling the PN532 RF field.
 *
 *   @retval    NRF_SUCCESS     If the RF field was enabled successfully. Otherwise,
 *                              an error code is returned.
 */
ret_code_t adafruit_pn532_field_on(void);

/**  @brief Function for disabling the PN532 RF field.
 *
 *   @retval    NRF_SUCCESS     If the RF field was disabled successfully. Otherwise,
 *                              an error code is returned.
 */
ret_code_t adafruit_pn532_field_off(void);
/** @} */

/**
 * @name Functions for ISO14443A tags
 *
 * @{ */

/**  @brief Function for detecting an ISO14443A (NFC-A) target presence in the RF field.
 *
 *   This function enables the RF field and scans for ISO14443A (NFC-A) targets present
 *   in the field. The number of scan retries is set by the @ref adafruit_pn532_passive_activation_retries_set
 *   function. By default, the maximum number of retries is set to unlimited, which means
 *   that the PN532 Shield scans for targets until it finds one or the scan is
 *   canceled. The @p timeout parameter specifies the time-out of the scan. If it is
 *   set to a value greater than 0, the function exits with a failure if either the maximum number
 *   of retries or the time-out has been reached. If the @p timeout parameter is set to 0,
 *   a single scan is performed. When the ISO14443A (NFC-A) target is detected, the
 *   PN532 module initializes communication and reads the basic initialization information 
 *   about NFC-A tag including SENS_RES, SEL_RES and UID. This information is retrieved by
 *   NFC reader during Technology Detection and Collision Resolution Activities.
 *
 *   @param[in,out] p_tag_info            Pointer to the structure where NFC-A Tag
 *                                        basic initialization information will be stored.
 *   @param[in]     timeout               Time-out (in ms). 0 means that only a single
 *                                        scan is performed.
 *                                        If no tag is presented before the time-out,
 *                                        the function returns NRF_ERROR_INTERNAL.
 *
 *   @retval        NRF_SUCCESS           If the function completed successfully. Otherwise,
 *                                        an error code is returned.
 */
ret_code_t adafruit_pn532_nfc_a_target_init(nfc_a_tag_info * p_tag_info,
                                            uint16_t         timeout);

/** @brief Function for exchanging an Application Protocol Data Unit (APDU) with the currently enlisted peer.
 *
 *   @param[in]     p_send                 Pointer to the data to send.
 *   @param[in]     send_len               Length of the data to send.
 *   @param[out]    p_response             Pointer to the buffer for response data.
 *   @param[in,out] p_response_len         Pointer to the variable that stores
 *                                         the length of the p_response buffer (as
 *                                         input) and the length of the response data
 *                                         (as output).
 *
 *   @retval        NRF_SUCCESS            If the function completed successfully. Otherwise,
 *                                         an error code is returned.
 */
ret_code_t adafruit_pn532_in_data_exchange(uint8_t * p_send,
                                           uint8_t   send_len,
                                           uint8_t * p_response,
                                           uint8_t * p_response_len);

/**  @brief Function for setting the MxRtyPassiveActivation parameter of the RFConfiguration register.
 *
 *   This function sets the maximum number of retries when scanning for a tag.
 *   The default is an unlimited number of retries.
 *
 *   @param[in]     max_retries         0xFF to wait forever. 0x00..0xFE to time out
 *                                      after the specified number of retries.
 *
 *   @retval        NRF_SUCCESS         If MxRtyPassiveActivation was set successfully. Otherwise,
 *                                      an error code is returned.
 */
ret_code_t adafruit_pn532_passive_activation_retries_set(uint8_t max_retries);

/** @} */

/**
 * @name Type 2 Tag related functions
 *
 * @{ */

/**  @brief Function for reading 4 pages/blocks within Type 2 Tag, starting with
 *          the specified page/block number.
 *
 *   This function reads 4 pages/blocks within Type 2 Tag at the specified page/block
 *   number, using Type 2 Tag READ command.
 *
 *   @param[in]     start_page            The page/block number (0..63 in most cases).
 *   @param[out]    p_buffer              Pointer to the uint8_t array that will
 *                                        hold the retrieved data (if any).
 *
 *   @retval        NRF_SUCCESS           If the data was read successfully. Otherwise,
 *                                        an error code is returned.
 */
ret_code_t adafruit_pn532_tag2_read(uint8_t start_page, uint8_t * p_buffer);

/**  @brief Function for writing an entire 4-byte page/block to the Type 2 Tag at the specified 
 *          page/block address.
 *
 *   This function writes a 4-byte sequence to the Type 2 Tag at the specified page/block, using
 *   Type 2 Tag WRITE command.
 *
 *   @param[in]     page                The page/block number to write (0..63 in most cases).
 *   @param[in]     p_data              The uint8_t array that contains the data to write.
 *                                      The data should be exactly 4 bytes long.
 *
 *   @retval        NRF_SUCCESS         If the data was written successfully. Otherwise,
 *                                      an error code is returned.
 */
ret_code_t adafruit_pn532_tag2_page_write(uint8_t page, uint8_t * p_data);

/**  @brief Function for writing an NDEF URI record to Type 2 Tag at the specified page (4..nn).
 *
 *   This function writes an NDEF URI record to Type 2 Tag at the specified page (4..nn). It uses
 *   @ref adafruit_pn532_tag2_page_write to perform atomic writes.
 *
 *   @param[in]     uri_id             The URI identifier code (0 = none, 0x01 =
 *                                     "http://www.", and so on).
 *   @param[in]     p_url              The URI text to write (null-terminated string).
 *   @param[in]     data_len           The maximum number of bytes that can be stored in the
 *                                     target device.
 *
 *   @retval        NRF_SUCCESS        If the record was written successfully. Otherwise,
 *                                     an error code is returned.
 */
ret_code_t adafruit_pn532_ndef_uri_tag2_write(uint8_t uri_id, char * p_url, uint8_t data_len);

/** @} */

/**
 * @name Printing functions.
 *
 * @{ */

/**  @brief Function for printing NFC-A Tag Info descriptor.
 *
 *   This function prints NFC-A Tag Info descriptor.
 *
 *   @param[in] p_tag_info Pointer to the NFC-A Tag Info descriptor.
 */
void adafruit_pn532_tag_info_printout(nfc_a_tag_info const * const p_tag_info);

/** @} */

/**
 * @name Low-level communication functions that utilize I2C and GPIO
 *
 * @{ */

/**  @brief Function for checking PN532 Shield readiness.
 *
 *    @retval True        If the PN532 Shield is ready with a response.
 *    @retval False       Otherwise.
 */
bool adafruit_pn532_is_ready(void);

/**  @brief Function for waiting until the PN532 Shield is ready.
 *
 *   @param[in]  timeout     Time-out (in ms) before giving up.
 *
 *   @retval  True        If the PN532 Shield is ready.
 *   @retval  False       Otherwise.
 */
bool adafruit_pn532_waitready_ms(uint16_t timeout);

/**  @brief Function for reading the ACK frame.
 *
 *   @retval  NRF_SUCCESS       If the ACK frame was read. Otherwise, an error code is returned.
 */
ret_code_t adafruit_pn532_ack_read(void);

/** @brief Function for reading n bytes of data from the PN532 Shield via I2C.
 *
 *   @param[out]    p_buff                 Pointer to the buffer where the data will be written.
 *   @param[in]     n                      Number of bytes to read.
 *
 *   @retval        NRF_SUCCESS            If the data was read successfully. Otherwise,
 *                                         an error code is returned.
 */
ret_code_t adafruit_pn532_data_read(uint8_t * p_buff, uint8_t n);

/**  @brief Function for writing a command to the PN532 Shield.
 *
 *   This function writes a command to the PN532 Shield and automatically inserts
 *   the preamble and required frame details (such as checksum, length, ...)
 *
 *   @param[in]  p_cmd              Pointer to the command buffer.
 *   @param[in]  cmd_len            Command length in bytes.
 *
 *   @retval     NRF_SUCCESS        If the command was written successfully. Otherwise,
 *                                  an error code is returned.
 */
ret_code_t adafruit_pn532_command_write(uint8_t * p_cmd, uint8_t cmd_len);
/** @} */

/**
 *@}
 **/

#endif
