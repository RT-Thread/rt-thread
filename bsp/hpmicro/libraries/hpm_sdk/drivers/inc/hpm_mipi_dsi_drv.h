/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_MIPI_DSI_DRV_H
#define HPM_MIPI_DSI_DRV_H

/**
 * @brief MIPI_DSI APIs
 * @defgroup mipi_dsi_interface MIPI_DSI driver APIs
 * @ingroup mipi_dsi_interfaces
 * @{
 */

#include "hpm_common.h"
#include "hpm_soc.h"
#include "hpm_mipi_dsi_regs.h"


/* MIPI DSI Processor-to-Peripheral transaction types */
typedef enum mipi_dsi_tx_cmd {
    MIPI_DSI_SHUTDOWN_PERIPHERAL = 0x22,
    MIPI_DSI_TURN_ON_PERIPHERAL = 0x32,
    MIPI_DSI_GENERIC_SHORT_WRITE_0_PARAM = 0x03,
    MIPI_DSI_GENERIC_SHORT_WRITE_1_PARAM = 0x13,
    MIPI_DSI_GENERIC_SHORT_WRITE_2_PARAM = 0x23,
    MIPI_DSI_GENERIC_READ_REQUEST_0_PARAM = 0x04,
    MIPI_DSI_GENERIC_READ_REQUEST_1_PARAM = 0x14,
    MIPI_DSI_GENERIC_READ_REQUEST_2_PARAM = 0x24,
    MIPI_DSI_DCS_SHORT_WRITE = 0x05,
    MIPI_DSI_DCS_SHORT_WRITE_PARAM = 0x15,
    MIPI_DSI_DCS_READ = 0x06,
    MIPI_DSI_SET_MAXIMUM_RETURN_PACKET_SIZE = 0x37,
    MIPI_DSI_GENERIC_LONG_WRITE = 0x29,
    MIPI_DSI_DCS_LONG_WRITE	= 0x39
} mipi_dsi_tx_cmd_t;

/* MIPI DCS commands */
typedef enum mipi_dcs_cmd {
    MIPI_DCS_NOP = 0x00,
    MIPI_DCS_SOFT_RESET = 0x01,
    MIPI_DCS_GET_DISPLAY_ID = 0x04,
    MIPI_DCS_GET_RED_CHANNEL = 0x06,
    MIPI_DCS_GET_GREEN_CHANNEL = 0x07,
    MIPI_DCS_GET_BLUE_CHANNEL = 0x08,
    MIPI_DCS_GET_DISPLAY_STATUS = 0x09,
    MIPI_DCS_GET_POWER_MODE = 0x0A,
    MIPI_DCS_GET_ADDRESS_MODE = 0x0B,
    MIPI_DCS_GET_PIXEL_FORMAT = 0x0C,
    MIPI_DCS_GET_DISPLAY_MODE = 0x0D,
    MIPI_DCS_GET_SIGNAL_MODE = 0x0E,
    MIPI_DCS_GET_DIAGNOSTIC_RESULT = 0x0F,
    MIPI_DCS_ENTER_SLEEP_MODE = 0x10,
    MIPI_DCS_EXIT_SLEEP_MODE = 0x11,
    MIPI_DCS_ENTER_PARTIAL_MODE = 0x12,
    MIPI_DCS_ENTER_NORMAL_MODE = 0x13,
    MIPI_DCS_EXIT_INVERT_MODE = 0x20,
    MIPI_DCS_ENTER_INVERT_MODE = 0x21,
    MIPI_DCS_SET_GAMMA_CURVE = 0x26,
    MIPI_DCS_SET_DISPLAY_OFF = 0x28,
    MIPI_DCS_SET_DISPLAY_ON = 0x29,
    MIPI_DCS_SET_COLUMN_ADDRESS = 0x2A,
    MIPI_DCS_SET_PAGE_ADDRESS = 0x2B,
    MIPI_DCS_WRITE_MEMORY_START = 0x2C,
    MIPI_DCS_WRITE_LUT = 0x2D,
    MIPI_DCS_READ_MEMORY_START = 0x2E,
    MIPI_DCS_SET_PARTIAL_AREA = 0x30,
    MIPI_DCS_SET_SCROLL_AREA = 0x33,
    MIPI_DCS_SET_TEAR_OFF = 0x34,
    MIPI_DCS_SET_TEAR_ON = 0x35,
    MIPI_DCS_SET_ADDRESS_MODE = 0x36,
    MIPI_DCS_SET_SCROLL_START = 0x37,
    MIPI_DCS_EXIT_IDLE_MODE = 0x38,
    MIPI_DCS_ENTER_IDLE_MODE = 0x39,
    MIPI_DCS_SET_PIXEL_FORMAT = 0x3A,
    MIPI_DCS_WRITE_MEMORY_CONTINUE = 0x3C,
    MIPI_DCS_READ_MEMORY_CONTINUE = 0x3E,
    MIPI_DCS_SET_TEAR_SCANLINE = 0x44,
    MIPI_DCS_GET_SCANLINE = 0x45,
    MIPI_DCS_SET_DISPLAY_BRIGHTNESS = 0x51,		/* MIPI DCS 1.3 */
    MIPI_DCS_GET_DISPLAY_BRIGHTNESS = 0x52,		/* MIPI DCS 1.3 */
    MIPI_DCS_WRITE_CONTROL_DISPLAY = 0x53,		/* MIPI DCS 1.3 */
    MIPI_DCS_GET_CONTROL_DISPLAY = 0x54,		/* MIPI DCS 1.3 */
    MIPI_DCS_WRITE_POWER_SAVE = 0x55,		/* MIPI DCS 1.3 */
    MIPI_DCS_GET_POWER_SAVE = 0x56,		/* MIPI DCS 1.3 */
    MIPI_DCS_SET_CABC_MIN_BRIGHTNESS = 0x5E,	/* MIPI DCS 1.3 */
    MIPI_DCS_GET_CABC_MIN_BRIGHTNESS = 0x5F,	/* MIPI DCS 1.3 */
    MIPI_DCS_READ_DDB_START = 0xA1,
    MIPI_DCS_READ_DDB_CONTINUE = 0xA8,
} mipi_dcs_cmd_t;

typedef enum mipi_dsi_pixel_format {
	MIPI_DSI_FMT_RGB888,
	MIPI_DSI_FMT_RGB666,
	MIPI_DSI_FMT_RGB666_PACKED,
	MIPI_DSI_FMT_RGB565,
} mipi_dsi_pixel_format_t;

typedef enum mipi_dsi_video_mode {
    MIPI_DSI_VIDEO_MODE_SYNC_PULSE = 0x00,
    MIPI_DSI_VIDEO_MODE_SYNC_EVENT = 0x01,
	MIPI_DSI_VIDEO_MODE_BURST = 0x02,
} mipi_dsi_video_mode_t;

/**
 * mipi_dsi_msg_t - read/write DSI buffer
 */
typedef struct mipi_dsi_msg {
    uint8_t channel; /*!< virtual channel id */
    uint8_t type; /*!< payload data type */
    uint16_t tx_len; /*!< length of tx_buf */
    const void *tx_buf; /*!< data to be written */
    uint16_t rx_len; /*!< length of rx_buf */
    void *rx_buf; /*!< data to be read, or NULL */
} mipi_dsi_msg_t;

typedef struct mipi_video_para {
    uint32_t pixel_clock_khz;
    uint32_t hactive;		/*!< hor. active video */
	uint32_t hfront_porch;	/*!< hor. front porch */
	uint32_t hback_porch;	/*!< hor. back porch */
	uint32_t hsync_len;		/*!< hor. sync len */

	uint32_t vactive;		/*!< ver. active video */
	uint32_t vfront_porch;	/*!< ver. front porch */
	uint32_t vback_porch;	/*!< ver. back porch */
	uint32_t vsync_len;		/*!< ver. sync len */
} mipi_video_para_t;

typedef struct mipi_dsi_config {
    uint32_t lane_mbps;
    uint8_t channel;
    uint8_t lanes;
    bool disable_eotp;
    mipi_dsi_pixel_format_t pixel_format;
    mipi_video_para_t video_para;
    mipi_dsi_video_mode_t video_mode;
} mipi_dsi_config_t;


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief get MIPI_DSI default config on video mode
 *
 * @param cfg: MIPI_DSI default config
 */
void mipi_dsi_get_defconfig_on_video(mipi_dsi_config_t *cfg);

/**
 * @brief MIPI_DSI init
 *
 * @param ptr MIPI_DSI base address
 * @param cfg config of MIPI_DSI
 */
void mipi_dsi_init(MIPI_DSI_Type *ptr, mipi_dsi_config_t *cfg);

/**
 * @brief MIPI_DSI phy interface power on
 *
 * @param ptr MIPI_DSI base address
 */
void mipi_dsi_phy_poweron(MIPI_DSI_Type *ptr);

/**
 * @brief MIPI_DSI phy interface power down
 *
 * @param ptr MIPI_DSI base address
 */
void mipi_dsi_phy_powerdown(MIPI_DSI_Type *ptr);

/**
 * @brief MIPI_DSI hs transfer start
 *
 * @param ptr MIPI_DSI base address
 */
void mipi_dsi_video_mode_hs_transfer_enable(MIPI_DSI_Type *ptr);

/**
 * @brief MIPI_DSI hs transfer stop
 *
 * @param ptr MIPI_DSI base address
 */
void mipi_dsi_video_mode_hs_transfer_disable(MIPI_DSI_Type *ptr);

/**
 * @brief transmit data using mipi dsi message in low power mode
 *
 * @param ptr MIPI_DSI base address
 * @param msg MPI_DSI message
 *
 * @return The number of bytes transmitted on success or a negative error code
 * on failure.
 */
int mipi_dsi_lp_cmd_transfer(MIPI_DSI_Type *ptr, const mipi_dsi_msg_t *msg);

/**
 * @brief specify the maximum size of the
 *	the payload in a long packet transmitted from the peripheral back to the
 *	host processor
 *
 * @param ptr: MIPI_DSI base address
 * @param channel: virtual channel
 * @param value: the maximum size of the payload
 *
 * @return: true on success or false on failure.
 */
int mipi_dsi_set_maximum_return_packet_size(MIPI_DSI_Type *ptr, uint8_t channel, uint16_t value);

/**
 * @brief transmit data using a generic write packet
 *
 * @param ptr: MIPI_DSI base address
 * @param channel: virtual channel
 * @param payload: buffer containing the payload
 * @param size: size of payload buffer
 *
 * This function will automatically choose the right data type depending on
 * the payload length.
 *
 * @return: The number of bytes transmitted on success or a negative error code
 * on failure.
 */
int mipi_dsi_generic_write(MIPI_DSI_Type *ptr, uint8_t channel, const void *payload,
			       uint16_t size);

/**
 * @brief receive data using a generic read packet
 *
 * @param ptr: MIPI_DSI base address
 * @param channel: virtual channel
 * @param params: buffer containing the request parameters
 * @param num_params: number of request parameters
 * @param data: buffer in which to return the received data
 * @param size: size of receive buffer
 *
 * This function will automatically choose the right data type depending on
 * the number of parameters passed in.
 *
 * @return: The number of bytes successfully read or a negative error code on
 * failure.
 */
int mipi_dsi_generic_read(MIPI_DSI_Type *ptr, uint8_t channel, const void *params,
			      uint16_t num_params, void *data, uint16_t size);

/**
 * @brief transmit a DCS command with payload
 *
 * @param ptr: MIPI_DSI base address
 * @param channel: virtual channel
 * @param data: buffer containing data to be transmitted
 * @param len: size of transmission buffer
 *
 * This function will automatically choose the right data type depending on
 * the command payload length.
 *
 * @return: The number of bytes successfully transmitted or a negative error
 * code on failure.
 */
int mipi_dsi_dcs_write_buffer(MIPI_DSI_Type *ptr, uint8_t channel,
				  const void *data, uint16_t len);

/**
 * @brief send DCS write command
 *
 * @param ptr: MIPI_DSI base address
 * @param channel: virtual channel
 * @param cmd: DCS command
 * @param data: buffer containing the command payload
 * @param len: command payload length
 *
 * This function will automatically choose the right data type depending on
 * the command payload length.
 *
 * @return: The number of bytes successfully transmitted or a negative error
 * code on failure.
 */
int mipi_dsi_dcs_write(MIPI_DSI_Type *ptr, uint8_t channel, uint8_t cmd,
			   const void *data, uint16_t len);

/**
 * @brief send DCS read request command
 *
 * @param ptr: MIPI_DSI base address
 * @param channel: virtual channel
 * @param cmd: DCS command
 * @param data: buffer in which to receive data
 * @param len: size of receive buffer
 *
 * @return: The number of bytes read or a negative error code on failure.
 */
int mipi_dsi_dcs_read(MIPI_DSI_Type *ptr, uint8_t channel, uint8_t cmd, void *data, uint16_t len);


#ifdef __cplusplus
}
#endif

/**
 * @}
 */
#endif /* HPM_MIPI_DSI_DRV_H */
