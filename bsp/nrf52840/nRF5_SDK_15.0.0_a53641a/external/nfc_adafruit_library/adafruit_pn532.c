/*
 * Adafruit PN532 library adapted to use in NRF51 and NRF52
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
#include "sdk_config.h"
#if ADAFRUIT_PN532_ENABLED
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include "adafruit_pn532.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "nrf_drv_twi.h"
#include "app_error.h"
#include "app_util.h"
#include "nordic_common.h"

#define NRF_LOG_MODULE_NAME adafruit_pn532
#if ADAFRUIT_PN532_LOG_ENABLED
#define NRF_LOG_LEVEL       ADAFRUIT_PN532_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  ADAFRUIT_PN532_INFO_COLOR
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();
#else // ADAFRUIT_PN532_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#include "nrf_log.h"
#endif // ADAFRUIT_PN532_LOG_ENABLED

// Type 2 Tag page/block read/write restrictions.
#define T2T_MAX_READ_PAGE_NUMBER                          255
#define T2T_MIN_WRITE_PAGE_NUMBER                         4
#define T2T_MAX_WRITE_PAGE_NUMBER                         255

// Lengths and offsets for specific commands and responses.
#define COMMAND_GETFIRMWAREVERSION_LENGTH                     1
#define REPLY_GETFIRMWAREVERSION_LENGTH                       (5 + PN532_FRAME_OVERHEAD)

#define COMMAND_SAMCONFIGURATION_LENGTH                       4
#define REPLY_SAMCONFIGURATION_LENGTH                         (1 + PN532_FRAME_OVERHEAD)

#define COMMAND_POWERDOWN_BASE_LENGTH                         2  // No GenerateIRQ parameter.
#define REPLY_POWERDOWN_LENGTH                                (2 + PN532_FRAME_OVERHEAD)

#define COMMAND_RFCONFIGURATION_MAXRETRIES_LENGTH             5
#define COMMAND_RFCONFIGURATION_RFFIELD_LENGTH                3
#define REPLY_RFCONFIGURATION_LENGTH                          (1 + PN532_FRAME_OVERHEAD)

#define COMMAND_INLISTPASSIVETARGET_BASE_LENGTH               3
#define REPLY_INLISTPASSIVETARGET_106A_TARGET_LENGTH          (17 + PN532_FRAME_OVERHEAD)
#define REPLY_INLISTPASSIVETARGET_106A_NBTG_OFFSET            7
#define REPLY_INLISTPASSIVETARGET_106A_TG_OFFSET              8
#define REPLY_INLISTPASSIVETARGET_106A_SENS_RES_BYTE_1_OFFSET 10
#define REPLY_INLISTPASSIVETARGET_106A_SENS_RES_BYTE_2_OFFSET 9
#define REPLY_INLISTPASSIVETARGET_106A_SEL_RES_OFFSET         11
#define REPLY_INLISTPASSIVETARGET_106A_UID_LEN_OFFSET         12
#define REPLY_INLISTPASSIVETARGET_106A_UID_OFFSET             13

#define COMMAND_INDATAEXCHANGE_BASE_LENGTH                    2
#define REPLY_INDATAEXCHANGE_BASE_LENGTH                      (2 + PN532_FRAME_OVERHEAD)

// Configuration parameters for SAMCONFIGURATION command.
#define SAMCONFIGURATION_MODE_NORMAL                          0x01
#define SAMCONFIGURATION_MODE_VIRTUAL_CARD                    0x02
#define SAMCONFIGURATION_MODE_WIRED_CARD                      0x03
#define SAMCONFIGURATION_MODE_DUAL_CARD                       0x04

#define SAMCONFIGURATION_IRQ_ENABLED                          0x01
#define SAMCONFIGURATION_IRQ_DISABLED                         0x00

// Configuration parameters for POWERDOWN command.
#define POWERDOWN_WAKEUP_IRQ                                  0x80
#define POWERDOWN_WAKEUP_SPI                                  0x20

// Configuration parameters for RFCONFIGURATION command.
#define RFCONFIGURATION_CFGITEM_RFFIELD                       0x01
#define RFCONFIGURATION_CFGITEM_MAXRETRIES                    0x05
#define RFCONFIGURATION_RFFIELD_ON                            0x01
#define RFCONFIGURATION_RFFIELD_OFF                           0x00

// Error mask for the status mask in INDATAEXCHANGE frame.
#define PN532_STATUS_ERROR_MASK                               0x3F

// Size of the PN532 size packet.
#define PN532_ACK_PACKET_SIZE                                 6

// Default time-out for read_passive_target_id (time required for field scan).
#define PN532_DEFAULT_WAIT_FOR_READY_TIMEOUT                  100

/**
 * @brief Information about the communication between the host and the Adafruit PN532 Shield.
 */
typedef struct
{
    uint8_t ss;            // !< Slave select signal for SPI.
    uint8_t clk;           // !< Clock signal for SPI.
    uint8_t mosi;          // !< Master output, slave input signal for SPI.
    uint8_t miso;          // !< Master input, slave output signal for SPI.
    uint8_t irq;           // !< Interrupt pin for Adafruit.
    uint8_t reset;         // !< Reset pin for Adafruit.
    uint8_t in_listed_tag; // !< Tag number of in listed tags.
    bool    using_spi;     // !< True if using SPI, false if using I2C.
    bool    hardware_spi;  // !< True if using hardware SPI, false if using software SPI.
} adafruit_pn532;


// ACK frame format.
static const uint8_t m_pn532_ack[] = {0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00};
// Firmware version reply frame format (preamble to command byte).
static const uint8_t m_pn532_rsp_firmware_ver[] = {0x00, 0xFF, 0x06, 0xFA, 0xD5, 0x03};

static adafruit_pn532 m_pn532_object = {
    .clk          = 0,
    .miso         = 0,
    .mosi         = 0,
    .ss           = 0,
    .irq          = PN532_IRQ,
    .reset        = PN532_RESET,
    .using_spi    = false,
    .hardware_spi = false
};

static const nrf_drv_twi_t m_twi_master = NRF_DRV_TWI_INSTANCE(PN532_CONFIG_TWI_INSTANCE);

static uint8_t m_pn532_packet_buf[PN532_PACKBUFF_SIZE];

static uint8_t m_pn532_rxtx_buffer[PN532_PACKBUFF_SIZE]; /// Buffer for low level communication.

static bool m_lib_initialized = false;


/**
 * @brief Function to configure pins in host chip.
 *
 * This function configures specific pins to interact with the PN532 module.
 */
static void adafruit_pn532_pin_setup(void)
{
    nrf_gpio_cfg_input(m_pn532_object.irq, NRF_GPIO_PIN_NOPULL);
    // The reset pin in the AdaFruit NFC Shield is actually the PN532 reset indicator pin (RSTOUT_N)
    // and cannot be used to perform reset of the chip. (RSTPD_N pin, see AdaFruit NFC Shield
    // schematics).
    nrf_gpio_cfg_input(m_pn532_object.reset, NRF_GPIO_PIN_NOPULL);
}


/**
 * @brief Function to calculate the checksum byte.
 *
 * This function calculates the checksum byte, so that the sum of all verified bytes
 * and the checksum byte is equal to 0.
 *
 * @param  current_sum[in]  Sum of all bytes used to calculate checksum.
 *
 * @retval Value of the checksum byte.
 */
static uint8_t adafruit_pn532_cs_complement_calc(uint8_t current_sum)
{
    return ~current_sum + 1;
}


/**
 * @brief Function to check correctness of PN532 Normal information frame header.
 *
 * @param  p_buffer[in]  Pointer to the buffer containing frame header.
 * @param  p_length[out] Pointer to the variable where the data length will be stored.
 *
 * @retval NRF_SUCCESS             If the header was correct.
 * @retval NRF_ERROR_INVALID_DATA  Otherwise.
 */
static ret_code_t adafruit_pn532_header_check(uint8_t const * p_buffer, uint8_t * p_length)
{
    // Preamble
    if ( (p_buffer[PN532_PREAMBLE_OFFSET] != PN532_PREAMBLE) ||
         (p_buffer[PN532_STARTCODE1_OFFSET] != PN532_STARTCODE1) ||
         (p_buffer[PN532_STARTCODE2_OFFSET] != PN532_STARTCODE2) )
    {
        NRF_LOG_INFO("Preamble missing");
        return NRF_ERROR_INVALID_DATA;
    }
    // Data length
    if (p_buffer[PN532_LENGTH_CS_OFFSET] !=
        adafruit_pn532_cs_complement_calc(p_buffer[PN532_LENGTH_OFFSET]))
    {
        NRF_LOG_INFO("Length check invalid: len: 0x%02x, cs: 02%02x",
                     p_buffer[PN532_LENGTH_OFFSET], p_buffer[PN532_LENGTH_CS_OFFSET]);
        return NRF_ERROR_INVALID_DATA;
    }
    // Direction byte
    if ( (p_buffer[PN532_TFI_OFFSET] != PN532_PN532TOHOST) &&
         (p_buffer[PN532_TFI_OFFSET] != PN532_HOSTTOPN532) )
    {
        NRF_LOG_INFO("Invalid direction byte: %02x", p_buffer[PN532_TFI_OFFSET]);
        return NRF_ERROR_INVALID_DATA;
    }

    *p_length = p_buffer[PN532_LENGTH_OFFSET];

    return NRF_SUCCESS;
}


ret_code_t adafruit_pn532_init(bool force)
{
    uint32_t ver_data; // Variable to store firmware version read from PN532.

    if (m_lib_initialized && !(force))
    {
        NRF_LOG_INFO("Library is already initialized");
        return NRF_SUCCESS;
    }

    if (force)
    {
        NRF_LOG_INFO("Forcing library reinitialization");
    }

    if (m_pn532_object.using_spi)
    {
        NRF_LOG_INFO("Communication over SPI is currently not supported!");
        return NRF_ERROR_INTERNAL;
    }

    ret_code_t err_code = adafruit_pn532_i2c_create();
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_INFO("Failed to create I2C, err_code = %d", err_code);
        return err_code;
    }

    adafruit_pn532_pin_setup();

    // Delay for PN532 to catch up with NRF.
    nrf_delay_ms(100);

    NRF_LOG_INFO("Looking for PN532");

    err_code = adafruit_pn532_firmware_version_get(&ver_data);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_INFO("Didn't find PN53x board, err_code = %d", err_code);
        return err_code;
    }

    NRF_LOG_INFO("Found chip PN5%02x", (ver_data >> 24) & 0xFF);
    NRF_LOG_INFO("Firmware version %d.%d", (ver_data >> 16) & 0xFF,
                                               (ver_data >> 8)  & 0xFF);

    err_code = adafruit_pn532_sam_config(SAMCONFIGURATION_MODE_NORMAL);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_INFO("Failed to configure SAM, err_code = %d", err_code);
        return err_code;
    }

    err_code = adafruit_pn532_passive_activation_retries_set(0xFF);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_INFO("Failed to set passive activation retries, err_code = %d", err_code);
        return err_code;
    }

    NRF_LOG_INFO("Waiting for an ISO14443A card");

    m_lib_initialized = true;

    return NRF_SUCCESS;
}


ret_code_t adafruit_pn532_i2c_create(void)
{
    NRF_LOG_INFO("Creating I2C");

    nrf_drv_twi_config_t twi_config = NRF_DRV_TWI_DEFAULT_CONFIG;
    twi_config.scl = PN532_CONFIG_SCL;
    twi_config.sda = PN532_CONFIG_SDA;

    ret_code_t ret = nrf_drv_twi_init(&m_twi_master, &twi_config, NULL, NULL);
    if (ret != NRF_SUCCESS)
    {
        NRF_LOG_INFO("Failed to initialize TWI, err_code = %d", ret);
        return ret;
    }

    nrf_drv_twi_enable(&m_twi_master);

    return NRF_SUCCESS;
}


void adafruit_pn532_tag_info_printout(nfc_a_tag_info const * const p_tag_info)
{
    NRF_LOG_INFO("Basic NFC-A Tag information");
    NRF_LOG_INFO("Anticollision information byte of SENS_RES: 0x%02X",
                 p_tag_info->sens_res[SENS_RES_ANTICOLLISION_INFO_BYTE]);
    NRF_LOG_INFO("Platform information byte of SENS_RES: 0x%02X",
                 p_tag_info->sens_res[SENS_RES_PLATFORM_INFO_BYTE]);
    NRF_LOG_INFO("SEL_RES: 0x%02X", p_tag_info->sel_res);
    NRF_LOG_INFO("%d-byte NFC ID:", p_tag_info->nfc_id_len);
    NRF_LOG_HEXDUMP_INFO(p_tag_info->nfc_id, p_tag_info->nfc_id_len);
    NRF_LOG_RAW_INFO("\r\n");
}


ret_code_t adafruit_pn532_firmware_version_get(uint32_t * p_response)
{
    NRF_LOG_INFO("Trying to get the firmware version");

    m_pn532_packet_buf[0] = PN532_COMMAND_GETFIRMWAREVERSION;

    ret_code_t err_code = adafruit_pn532_cmd_send(m_pn532_packet_buf,
                                                  COMMAND_GETFIRMWAREVERSION_LENGTH,
                                                  1000);

    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_INFO("Failed to send GetFirmwareVersion command, err_code = %d", err_code);
        return err_code;
    }

    // Read data packet.
    err_code = adafruit_pn532_data_read(m_pn532_packet_buf, REPLY_GETFIRMWAREVERSION_LENGTH);

    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_INFO("Failed to read data, err_code = %d", err_code);
        return err_code;
    }

    if (memcmp(m_pn532_packet_buf + 1, m_pn532_rsp_firmware_ver, sizeof(m_pn532_rsp_firmware_ver)))
    {
        NRF_LOG_INFO("Firmware frame doesn't match!");
        return NRF_ERROR_NOT_FOUND;
    }

    // Extract firmware version from the frame.
    *p_response = uint32_big_decode(m_pn532_packet_buf + PN532_DATA_OFFSET + 1);

    return NRF_SUCCESS;
}


ret_code_t adafruit_pn532_cmd_send(uint8_t * p_cmd, uint8_t cmd_len, uint16_t timeout)
{
    NRF_LOG_INFO("Trying to send command");
    NRF_LOG_HEXDUMP_INFO(p_cmd, cmd_len);

    ret_code_t err_code = adafruit_pn532_command_write(p_cmd, cmd_len);

    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_INFO("Failed to write command, err_code = %d", err_code);
        return err_code;
    }

    // Wait for ACK
    if (!adafruit_pn532_waitready_ms(timeout))
    {
        NRF_LOG_INFO("Failed while waiting");
        return NRF_ERROR_INTERNAL;
    }

    return adafruit_pn532_ack_read();
}


ret_code_t adafruit_pn532_sam_config(uint8_t mode)
{
    NRF_LOG_INFO("Attempting to configure SAM");

    ret_code_t err_code;

    if ( (mode != SAMCONFIGURATION_MODE_NORMAL) &&
         (mode != SAMCONFIGURATION_MODE_VIRTUAL_CARD) &&
         (mode != SAMCONFIGURATION_MODE_WIRED_CARD) &&
         (mode != SAMCONFIGURATION_MODE_DUAL_CARD) )
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    m_pn532_packet_buf[0] = PN532_COMMAND_SAMCONFIGURATION;
    m_pn532_packet_buf[1] = mode;
    m_pn532_packet_buf[2] = 0x14; // Time-out value
    m_pn532_packet_buf[3] = SAMCONFIGURATION_IRQ_ENABLED;

    err_code = adafruit_pn532_cmd_send(m_pn532_packet_buf, COMMAND_SAMCONFIGURATION_LENGTH, 1000);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_INFO("Failed while checking ACK! err_code = %d", err_code);
        return err_code;
    }

    err_code = adafruit_pn532_data_read(m_pn532_packet_buf, REPLY_SAMCONFIGURATION_LENGTH);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_INFO("Failed while reading data! err_code = %d", err_code);
        return err_code;
    }

    if (!(m_pn532_packet_buf[PN532_DATA_OFFSET] == PN532_COMMAND_SAMCONFIGURATION + 1))
    {
        NRF_LOG_INFO("Failed while checking SAMCONFIGURATION response, expected 0x%02x, got 0x%02x",
                     PN532_COMMAND_SAMCONFIGURATION + 1,
                     m_pn532_packet_buf[PN532_DATA_OFFSET]);
        return NRF_ERROR_NOT_FOUND;
    }

    return NRF_SUCCESS;
}


ret_code_t adafruit_pn532_power_down(void)
{
    NRF_LOG_INFO("Powering down the PN532");

    m_pn532_packet_buf[0] = PN532_COMMAND_POWERDOWN;
    m_pn532_packet_buf[1] = POWERDOWN_WAKEUP_IRQ;

    ret_code_t err_code = adafruit_pn532_cmd_send(m_pn532_packet_buf,
                                                  COMMAND_POWERDOWN_BASE_LENGTH,
                                                  1000);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_INFO("Failed while checking ACK! err_code = %d", err_code);
        return err_code;
    }

    err_code = adafruit_pn532_data_read(m_pn532_packet_buf, REPLY_POWERDOWN_LENGTH);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_INFO("Failed while reading data! err_code = %d", err_code);
        return err_code;
    }

    if (!(m_pn532_packet_buf[PN532_DATA_OFFSET] == PN532_COMMAND_POWERDOWN + 1))
    {
        NRF_LOG_INFO("Failed while checking POWERDOWN response, expected 0x%02x, got 0x%02x",
                     PN532_COMMAND_POWERDOWN + 1,
                     m_pn532_packet_buf[PN532_DATA_OFFSET]);
        return NRF_ERROR_NOT_FOUND;
    }

    // From PN532 user manual: "The PN532 needs approximately 1 ms to get into Power Down mode,
    // after the command response." (Rev. 02, p. 7.2.11, page 98)
    nrf_delay_ms(1);

    return NRF_SUCCESS;
}


ret_code_t adafruit_pn532_wake_up(void)
{
    ret_code_t err_code;

    if (m_pn532_object.using_spi)
    {
        NRF_LOG_INFO("Communication over SPI is currently not supported!");
        return NRF_ERROR_INTERNAL;
    }

    // Wakeup procedure as specified in PN532 User Manual Rev. 02, p. 7.2.11, page 99.
    uint8_t dummy_byte = 0x55;
    err_code = nrf_drv_twi_tx(&m_twi_master, PN532_I2C_ADDRESS, &dummy_byte, 1, false);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_INFO("Failed while calling twi tx, err_code = %d", err_code);
        return err_code;
    }
    // Wait specified time to ensure that the PN532 shield is fully operational
    // (PN532 data sheet, Rev. 3.2, page 209).
    nrf_delay_ms(2);

    return NRF_SUCCESS;
}


ret_code_t adafruit_pn532_passive_activation_retries_set(uint8_t max_retries)
{
    ret_code_t err_code;

    m_pn532_packet_buf[0] = PN532_COMMAND_RFCONFIGURATION;
    m_pn532_packet_buf[1] = RFCONFIGURATION_CFGITEM_MAXRETRIES;
    m_pn532_packet_buf[2] = 0xFF;        // MxRtyATR retries (default value)
    m_pn532_packet_buf[3] = 0x01;        // MxRtyPSL retries (default value)
    m_pn532_packet_buf[4] = max_retries; // MxRtyPassiveActivation retries (user value)

    NRF_LOG_INFO("Setting MxRtyPassiveActivation to %i", max_retries);

    err_code = adafruit_pn532_cmd_send(m_pn532_packet_buf,
                                       COMMAND_RFCONFIGURATION_MAXRETRIES_LENGTH,
                                       1000);

    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_INFO("Failed while checking ACK! err_code = %d", err_code);
        return err_code;
    }

    return NRF_SUCCESS;
}


ret_code_t adafruit_pn532_nfc_a_target_init(nfc_a_tag_info * p_tag_info,
                                            uint16_t         timeout)
{
    NRF_LOG_INFO("Trying to read passive target ID");

    if (p_tag_info == NULL)
    {
        NRF_LOG_INFO("NULL pointers passed as arguments to adafruit_pn532_passive_target_init.");
        return NRF_ERROR_INVALID_PARAM;
    }

    m_pn532_packet_buf[0] = PN532_COMMAND_INLISTPASSIVETARGET;
    m_pn532_packet_buf[1] = 1; // Maximum number of targets.
    m_pn532_packet_buf[2] = PN532_MIFARE_ISO14443A_BAUD;

    ret_code_t err_code = adafruit_pn532_cmd_send(m_pn532_packet_buf,
                                                  COMMAND_INLISTPASSIVETARGET_BASE_LENGTH,
                                                  PN532_DEFAULT_WAIT_FOR_READY_TIMEOUT);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_INFO("No card(s) read, err_code = %d", err_code);
        return err_code;
    }

    NRF_LOG_INFO("Waiting for IRQ (indicates card presence)");

    // Give PN532 a little time to scan in case time-out is very small.
    if (timeout < PN532_DEFAULT_WAIT_FOR_READY_TIMEOUT)
    {
        timeout = PN532_DEFAULT_WAIT_FOR_READY_TIMEOUT;
    }

    if (!adafruit_pn532_waitready_ms(timeout))
    {
        NRF_LOG_INFO("IRQ time-out");
        return NRF_ERROR_INTERNAL;
    }

    err_code = adafruit_pn532_data_read(m_pn532_packet_buf,
                                        REPLY_INLISTPASSIVETARGET_106A_TARGET_LENGTH);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_INFO("Failed while reading data! err_code = %d", err_code);
        return err_code;
    }

    if (m_pn532_packet_buf[REPLY_INLISTPASSIVETARGET_106A_NBTG_OFFSET] != 1)
    {
        NRF_LOG_INFO("Failed while checking number of targets, expected 1, got %02x",
                     m_pn532_packet_buf[REPLY_INLISTPASSIVETARGET_106A_NBTG_OFFSET]);
        return NRF_ERROR_INVALID_DATA;
    }

    if (MAX_NFC_A_ID_LEN < m_pn532_packet_buf[REPLY_INLISTPASSIVETARGET_106A_UID_LEN_OFFSET])
    {
        NRF_LOG_INFO("UID length is invalid.");
        return NRF_ERROR_INVALID_LENGTH;
    }

    p_tag_info->sens_res[SENS_RES_ANTICOLLISION_INFO_BYTE] =
        m_pn532_packet_buf[REPLY_INLISTPASSIVETARGET_106A_SENS_RES_BYTE_1_OFFSET];
    p_tag_info->sens_res[SENS_RES_PLATFORM_INFO_BYTE] =
        m_pn532_packet_buf[REPLY_INLISTPASSIVETARGET_106A_SENS_RES_BYTE_2_OFFSET];

    p_tag_info->sel_res    = m_pn532_packet_buf[REPLY_INLISTPASSIVETARGET_106A_SEL_RES_OFFSET];
    p_tag_info->nfc_id_len = m_pn532_packet_buf[REPLY_INLISTPASSIVETARGET_106A_UID_LEN_OFFSET];
    memcpy(p_tag_info->nfc_id,
           m_pn532_packet_buf + REPLY_INLISTPASSIVETARGET_106A_UID_OFFSET,
           p_tag_info->nfc_id_len);

    m_pn532_object.in_listed_tag = m_pn532_packet_buf[REPLY_INLISTPASSIVETARGET_106A_TG_OFFSET];

    return NRF_SUCCESS;
}


ret_code_t adafruit_pn532_in_data_exchange(uint8_t * p_send,
                                           uint8_t   send_len,
                                           uint8_t * p_response,
                                           uint8_t * p_response_len)
{
    NRF_LOG_INFO("Trying in data exchange");

    if ((uint16_t) send_len + 2 > PN532_PACKBUFF_SIZE)
    {
        NRF_LOG_INFO("APDU length (%d) too long for packet buffer (%d)",
                     send_len,
                     PN532_PACKBUFF_SIZE - 2);
        return NRF_ERROR_INTERNAL;
    }

    if ((uint16_t) (*p_response_len) + REPLY_INDATAEXCHANGE_BASE_LENGTH > PN532_PACKBUFF_SIZE)
    {
        NRF_LOG_INFO("Desired response length (%d) too long for packet buffer (%d)",
                     *p_response_len,
                     PN532_PACKBUFF_SIZE);
        return NRF_ERROR_INTERNAL;
    }

    // Prepare command.
    m_pn532_packet_buf[0] = PN532_COMMAND_INDATAEXCHANGE;
    m_pn532_packet_buf[1] = m_pn532_object.in_listed_tag;
    memcpy(m_pn532_packet_buf + 2, p_send, send_len);

    ret_code_t err_code = adafruit_pn532_cmd_send(m_pn532_packet_buf,
                                                  send_len + 2,
                                                  1000);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_INFO("Could not send ADPU, err_code = %d", err_code);
        return err_code;
    }

    if (!adafruit_pn532_waitready_ms(1000))
    {
        NRF_LOG_INFO("Response never received for ADPU");
        return NRF_ERROR_INTERNAL;
    }

    err_code = adafruit_pn532_data_read(m_pn532_packet_buf,
                                        *p_response_len + REPLY_INDATAEXCHANGE_BASE_LENGTH);
                                                        // + 2 for command and status byte
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_INFO("Could not read data, err_code = %d", err_code);
        return err_code;
    }

    uint8_t length = 0;
    err_code = adafruit_pn532_header_check(m_pn532_packet_buf, &length);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_INFO("Invalid frame header");
        return err_code;
    }

    if ( (m_pn532_packet_buf[PN532_TFI_OFFSET] != PN532_PN532TOHOST) ||
         (m_pn532_packet_buf[PN532_DATA_OFFSET] != PN532_COMMAND_INDATAEXCHANGE + 1) )
    {
        NRF_LOG_INFO("Don't know how to handle this command: %02x",
                     m_pn532_packet_buf[PN532_DATA_OFFSET]);
        return NRF_ERROR_INTERNAL;
    }

    // Check InDataExchange Status byte.
    if ((m_pn532_packet_buf[PN532_DATA_OFFSET + 1] & PN532_STATUS_ERROR_MASK) != 0x00)
    {
        NRF_LOG_INFO("Status code indicates an error, %02x",
                     m_pn532_packet_buf[PN532_DATA_OFFSET + 1]);
        return NRF_ERROR_INTERNAL;
    }

    length -= 3; // Calculate the actual data length

    // Silently truncate response to fit into reply desired data size.
    if (length > *p_response_len)
    {
        length = *p_response_len;
    }

    memcpy(p_response, m_pn532_packet_buf + PN532_DATA_OFFSET + 2, length);
    *p_response_len = length;

    return NRF_SUCCESS;
}


ret_code_t adafruit_pn532_tag2_read(uint8_t start_page, uint8_t * p_buffer)
{
    NRF_LOG_INFO("Trying to read pages: %d-%d", start_page, start_page + T2T_END_PAGE_OFFSET);

    ret_code_t err_code;

    uint8_t cmd_buf[2];
    uint8_t response_len = T2T_MAX_DATA_EXCHANGE;

    cmd_buf[0] = MIFARE_CMD_READ;
    cmd_buf[1] = start_page;

    err_code = adafruit_pn532_in_data_exchange(cmd_buf, 2, p_buffer, &response_len);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_INFO("Failed to read pages: %d-%d",
                     start_page,
                     start_page + T2T_END_PAGE_OFFSET);
        return err_code;
    }

    NRF_LOG_INFO("Pages %d-%d", start_page, start_page + T2T_END_PAGE_OFFSET);
    NRF_LOG_HEXDUMP_INFO(p_buffer, response_len);

    return NRF_SUCCESS;
}


ret_code_t adafruit_pn532_tag2_page_write(uint8_t page, uint8_t * p_data)
{
    if (page < T2T_MIN_WRITE_PAGE_NUMBER)
    {
        NRF_LOG_INFO("Page value out of range, page = %d", page);
        return NRF_ERROR_INVALID_PARAM;
    }

    NRF_LOG_INFO("Trying to write 4-byte page %u", page);

    uint8_t write_buf[T2T_MAX_DATA_EXCHANGE];
    uint8_t response_len = T2T_MAX_DATA_EXCHANGE;

    write_buf[0] = MIFARE_ULTRALIGHT_CMD_WRITE;
    write_buf[1] = page;
    memcpy(write_buf + 2, p_data, T2T_PAGE_SIZE);

    ret_code_t err_code = adafruit_pn532_in_data_exchange(write_buf,
                                                          2 + T2T_PAGE_SIZE,
                                                          write_buf,
                                                          &response_len);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_INFO("Failed to write page %d", page);
        return err_code;
    }

    return NRF_SUCCESS;
}


ret_code_t adafruit_pn532_ndef_uri_tag2_write(uint8_t uri_id, char * p_url, uint8_t data_len)
{
    NRF_LOG_INFO("Trying to write URI %d", uri_id);

    uint8_t page_buf[4]   = {0};
    uint8_t uri_len       = strlen(p_url);
    uint8_t page_header[] =
    {
        0x00, 0x03, uri_len + 5, 0xD1,
        0x01, uri_len + 1, 0x55, uri_id
    };
    uint8_t page_header_len = sizeof(page_header);

    if ( (uri_len < 1) || (uri_len + 1 > (data_len - page_header_len)))
    {
        NRF_LOG_INFO("URL is too long for provided data length");
        return NRF_ERROR_INVALID_PARAM;
    }

    ret_code_t err_code;
    int32_t    i;
    uint8_t    current_page = 4;

    for (i = 0; i < 2; i++)
    {
        memcpy(page_buf, page_header + 4 * i, T2T_PAGE_SIZE);
        err_code = adafruit_pn532_tag2_page_write(current_page, page_buf);
        if (err_code != NRF_SUCCESS)
        {
            NRF_LOG_INFO("Failed to write URI page %d, err_code = %d", current_page, err_code);
            return err_code;
        }
        current_page++;
    }

    char  * url_ptr    = p_url;
    uint8_t len_to_cpy = 0;

    while (uri_len > 0)
    {
        // Prepare length of the chunk to copy.
        if (uri_len < T2T_PAGE_SIZE)
        {
            len_to_cpy = uri_len;
            // If do not copy a full page, prepare the buffer.
            memset(page_buf, 0x00, T2T_PAGE_SIZE);
            page_buf[len_to_cpy] = 0xFE; // Terminator block.
        }
        else
        {
            len_to_cpy = T2T_PAGE_SIZE;
        }

        memcpy(page_buf, url_ptr, len_to_cpy);

        err_code = adafruit_pn532_tag2_page_write(current_page, page_buf);
        if (err_code != NRF_SUCCESS)
        {
            NRF_LOG_INFO("Failed to write page %d, err_code = %d", current_page, err_code);
            return err_code;
        }

        current_page++;

        // If the last page was sent, and there was no chance to insert TLV Terminator block,
        // send another page with Terminator block in it.
        if (uri_len == T2T_PAGE_SIZE)
        {
            memset(page_buf, 0x00, T2T_PAGE_SIZE);
            page_buf[0] = 0xFE;
            err_code    = adafruit_pn532_tag2_page_write(current_page, page_buf);
            if (err_code != NRF_SUCCESS)
            {
                NRF_LOG_INFO("Failed to write page %d, err_code = %d", current_page, err_code);
                return err_code;
            }
            current_page++;
        }

        uri_len -= len_to_cpy;
        url_ptr += len_to_cpy;
    }

    return NRF_SUCCESS;
}


ret_code_t adafruit_pn532_ack_read(void)
{
    NRF_LOG_INFO("Reading ACK");

    uint8_t    ack_buf[PN532_ACK_PACKET_SIZE];
    ret_code_t err_code;

    err_code = adafruit_pn532_data_read(ack_buf, PN532_ACK_PACKET_SIZE);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_INFO("ACK read failed");
        return err_code;
    }

    // Wait for irq to be taken off.
    for (uint16_t i = 0; i < 1000; i++)
    {
        if (!adafruit_pn532_is_ready())
        {
            break;
        }
    }

    if (memcmp(ack_buf, m_pn532_ack, PN532_ACK_PACKET_SIZE) != 0)
    {
        NRF_LOG_INFO("Failed while comparing ACK packet");
        return NRF_ERROR_INTERNAL;
    }

    return NRF_SUCCESS;
}


bool adafruit_pn532_is_ready(void)
{
    return nrf_gpio_pin_read(m_pn532_object.irq) == 0;
}


bool adafruit_pn532_waitready_ms(uint16_t timeout)
{
    uint16_t timer  = 0;
    bool     result = false;

    result = adafruit_pn532_is_ready();
    while ((!result) && (timer < timeout))
    {
        timer += 1;
        nrf_delay_ms(1);
        result = adafruit_pn532_is_ready();
    }

    return result;
}


ret_code_t adafruit_pn532_data_read(uint8_t * p_buff, uint8_t n)
{
    if (!adafruit_pn532_waitready_ms(PN532_DEFAULT_WAIT_FOR_READY_TIMEOUT))
    {
        return NRF_ERROR_INTERNAL;
    }

    if (m_pn532_object.using_spi)
    {
        NRF_LOG_INFO("Communication over SPI is currently not supported!");
        return NRF_ERROR_INTERNAL;
    }

    if ((uint16_t) n + 1 > PN532_PACKBUFF_SIZE)
    {
        NRF_LOG_INFO("Rx buffer is too short!");
        return NRF_ERROR_INVALID_PARAM;
    }

    if (n == UINT8_MAX)
    {
        NRF_LOG_INFO("Read command exceeds uint8_t !");
        return NRF_ERROR_NOT_SUPPORTED;
    }

    ret_code_t err_code;
    // In case of I2C, read the additional status byte.

    NRF_LOG_INFO("Reading (%d bytes): ", n+1);
    err_code = nrf_drv_twi_rx(&m_twi_master, PN532_I2C_ADDRESS, m_pn532_rxtx_buffer, n + 1);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_INFO("Failed while calling TWI rx, err_code = %d", err_code);
        return err_code;
    }
    memcpy(p_buff, m_pn532_rxtx_buffer + 1, n);

    NRF_LOG_HEXDUMP_INFO(p_buff, n);

    return NRF_SUCCESS;
}


ret_code_t adafruit_pn532_command_write(uint8_t * p_cmd, uint8_t cmd_len)
{
    ret_code_t err_code;
    uint8_t    checksum;

    if (m_pn532_object.using_spi)
    {
        NRF_LOG_INFO("Communication over SPI is currently not supported!");
        return NRF_ERROR_INTERNAL;
    }

    if ((uint16_t) cmd_len + PN532_FRAME_OVERHEAD > PN532_PACKBUFF_SIZE)
    {
        NRF_LOG_INFO("Tx buffer is too short!");
        return NRF_ERROR_INVALID_PARAM;
    }

    // Compose header part of the command frame.
    m_pn532_rxtx_buffer[0] = PN532_PREAMBLE;
    m_pn532_rxtx_buffer[1] = PN532_STARTCODE1;
    m_pn532_rxtx_buffer[2] = PN532_STARTCODE2;
    m_pn532_rxtx_buffer[3] = cmd_len + 1; // Data length + TFI byte.
    m_pn532_rxtx_buffer[4] = adafruit_pn532_cs_complement_calc(cmd_len + 1);
    m_pn532_rxtx_buffer[5] = PN532_HOSTTOPN532;

    // Copy the payload data.
    memcpy(m_pn532_rxtx_buffer + HEADER_SEQUENCE_LENGTH, p_cmd, cmd_len);

    // Calculate checksum.
    checksum = PN532_HOSTTOPN532;
    for (uint8_t i = 0; i < cmd_len; i++)
    {
        checksum += p_cmd[i];
    }
    checksum = adafruit_pn532_cs_complement_calc(checksum);

    // Compose checksum part of the command frame.
    m_pn532_rxtx_buffer[HEADER_SEQUENCE_LENGTH + cmd_len]     = checksum;
    m_pn532_rxtx_buffer[HEADER_SEQUENCE_LENGTH + cmd_len + 1] = PN532_POSTAMBLE;

    NRF_LOG_INFO("Sending command");
    NRF_LOG_HEXDUMP_INFO(m_pn532_rxtx_buffer, cmd_len + PN532_FRAME_OVERHEAD);

    err_code = nrf_drv_twi_tx(&m_twi_master,
                              PN532_I2C_ADDRESS,
                              m_pn532_rxtx_buffer,
                              cmd_len + PN532_FRAME_OVERHEAD,
                              false);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_INFO("Failed while calling TWI tx 1, err_code = %d", err_code);
        return err_code;
    }

    return NRF_SUCCESS;
}


/** Function for enabling or disabling the PN532 RF field.
 *
 *  This function sends a configuration command to the PN532, which enables or disables the RF field.
 *
 *  @param     field_conf   A value indicating whether the RF field should be turned on or off.
 *                          Valid values are 1 (field on) and 0 (field off).
 *
 *  @retval    NRF_SUCCESS              If the RF field was enabled successfully.
 *  @retval    NRF_ERROR_INVALID_PARAM  If the value in field_conf was invalid.
 *  @retval    Other                    Otherwise.
 */
static ret_code_t adafruit_pn532_field_switch(uint8_t field_conf)
{
    ret_code_t err_code;

    if ( (field_conf != RFCONFIGURATION_RFFIELD_ON) && (field_conf != RFCONFIGURATION_RFFIELD_OFF) )
    {
        NRF_LOG_INFO("Invalid field configuration: 0x%02x", field_conf);
        return NRF_ERROR_INVALID_PARAM;
    }

    m_pn532_packet_buf[0] = PN532_COMMAND_RFCONFIGURATION;
    m_pn532_packet_buf[1] = RFCONFIGURATION_CFGITEM_RFFIELD;
    m_pn532_packet_buf[2] = field_conf;

    err_code = adafruit_pn532_cmd_send(m_pn532_packet_buf,
                                       COMMAND_RFCONFIGURATION_RFFIELD_LENGTH,
                                       1000);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_INFO("Failed while checking ACK! err_code = %d", err_code);
        return err_code;
    }

    if (!adafruit_pn532_waitready_ms(PN532_DEFAULT_WAIT_FOR_READY_TIMEOUT))
    {
        return NRF_ERROR_INTERNAL;
    }

    return NRF_SUCCESS;
}


ret_code_t adafruit_pn532_field_on(void)
{
    return adafruit_pn532_field_switch(RFCONFIGURATION_RFFIELD_ON);
}


ret_code_t adafruit_pn532_field_off(void)
{
    return adafruit_pn532_field_switch(RFCONFIGURATION_RFFIELD_OFF);
}


#endif // ADAFRUIT_PN532_ENABLED
