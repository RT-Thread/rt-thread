/**
 * @file hal_dsi.c
 * @brief
 *
 * Copyright (c) 2021 Bouffalolab team
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 */
#include "hal_dsi.h"
#include "hal_clock.h"
#include "mipi_display.h"
#include "bl808_dsi.h"

#define ENOSYS  123
#define EINVAL  124
#define ENOMEM  125
#define ENODATA 126

/**
 * mipi_dsi_packet_format_is_short - check if a packet is of the short format
 * @type: MIPI DSI data type of the packet
 *
 * Return: true if the packet for the given data type is a short packet, false
 * otherwise.
 */
bool mipi_dsi_packet_format_is_short(u8 type)
{
    switch (type) {
        case MIPI_DSI_V_SYNC_START:
        case MIPI_DSI_V_SYNC_END:
        case MIPI_DSI_H_SYNC_START:
        case MIPI_DSI_H_SYNC_END:
        case MIPI_DSI_COMPRESSION_MODE:
        case MIPI_DSI_END_OF_TRANSMISSION:
        case MIPI_DSI_COLOR_MODE_OFF:
        case MIPI_DSI_COLOR_MODE_ON:
        case MIPI_DSI_SHUTDOWN_PERIPHERAL:
        case MIPI_DSI_TURN_ON_PERIPHERAL:
        case MIPI_DSI_GENERIC_SHORT_WRITE_0_PARAM:
        case MIPI_DSI_GENERIC_SHORT_WRITE_1_PARAM:
        case MIPI_DSI_GENERIC_SHORT_WRITE_2_PARAM:
        case MIPI_DSI_GENERIC_READ_REQUEST_0_PARAM:
        case MIPI_DSI_GENERIC_READ_REQUEST_1_PARAM:
        case MIPI_DSI_GENERIC_READ_REQUEST_2_PARAM:
        case MIPI_DSI_DCS_SHORT_WRITE:
        case MIPI_DSI_DCS_SHORT_WRITE_PARAM:
        case MIPI_DSI_DCS_READ:
        case MIPI_DSI_EXECUTE_QUEUE:
        case MIPI_DSI_SET_MAXIMUM_RETURN_PACKET_SIZE:
            return true;
    }

    return false;
}

/**
 * mipi_dsi_packet_format_is_long - check if a packet is of the long format
 * @type: MIPI DSI data type of the packet
 *
 * Return: true if the packet for the given data type is a long packet, false
 * otherwise.
 */
bool mipi_dsi_packet_format_is_long(u8 type)
{
    switch (type) {
        case MIPI_DSI_NULL_PACKET:
        case MIPI_DSI_BLANKING_PACKET:
        case MIPI_DSI_GENERIC_LONG_WRITE:
        case MIPI_DSI_DCS_LONG_WRITE:
        case MIPI_DSI_PICTURE_PARAMETER_SET:
        case MIPI_DSI_COMPRESSED_PIXEL_STREAM:
        case MIPI_DSI_LOOSELY_PACKED_PIXEL_STREAM_YCBCR20:
        case MIPI_DSI_PACKED_PIXEL_STREAM_YCBCR24:
        case MIPI_DSI_PACKED_PIXEL_STREAM_YCBCR16:
        case MIPI_DSI_PACKED_PIXEL_STREAM_30:
        case MIPI_DSI_PACKED_PIXEL_STREAM_36:
        case MIPI_DSI_PACKED_PIXEL_STREAM_YCBCR12:
        case MIPI_DSI_PACKED_PIXEL_STREAM_16:
        case MIPI_DSI_PACKED_PIXEL_STREAM_18:
        case MIPI_DSI_PIXEL_STREAM_3BYTE_18:
        case MIPI_DSI_PACKED_PIXEL_STREAM_24:
            return true;
    }

    return false;
}

/**
 * mipi_dsi_controller_init() - Init DSI controller
 * @dsi: DSI peripheral device
 *
 * Return: 0 on success or a negative error code on failure.
 */
int mipi_dsi_controller_init(const struct mipi_dsi_device *dsi)
{
    DSI_CFG_Type dsiCfg = {
        .virtualChan = 0,                   /*!< DSI virtual channels */
        .laneNum = DSI_LANE_NUMBER_4,       /*!< DSI lane numbers */
        .laneOrder = DSI_LANE_ORDER_3210,   /*!< DSI lane order */
        .dataType = DSI_DATA_RGB888,        /*!< DSI data type */
        .syncType = DSI_HS_SYNC_EVENT_MODE, /*!< HS sync event mode */
        .vsa = 10,                          /*!< HS vertical sync active width */
        .vfp = 10,                          /*!< HS vertical front porch width */
    };
    DSI_DPhy_CFG_Type dphyCfg = {
        .time_clk_exit = 5,
        .time_clk_trail = 3,
        .time_clk_zero = 15,
        .time_data_exit = 5,
        .time_data_prepare = 2,
        .time_data_trail = 3,
        .time_data_zero = 15,
        .time_lpx = 3,
        .time_req_ready = 1,
        .time_ta_get = 15,
        .time_ta_go = 12,
        .time_wakeup = 40001,
    };
    DSI_Lane_Type usedLanes = DSI_LANE_CLOCK;

    dsiCfg.virtualChan = dsi->channel;
    if (dsi->lanes == 1) {
        dsiCfg.laneNum = DSI_LANE_NUMBER_1;
    } else if(dsi->lanes == 2) {
        dsiCfg.laneNum = DSI_LANE_NUMBER_2;
    } else {
        dsiCfg.laneNum = DSI_LANE_NUMBER_4;
    }
    dsiCfg.dataType = dsi->format;

    if (dsiCfg.laneNum == DSI_LANE_NUMBER_1) {
        usedLanes |= DSI_LANE_DATA0;
    } else if (dsiCfg.laneNum == DSI_LANE_NUMBER_2) {
        usedLanes |= DSI_LANE_DATA0;
        usedLanes |= DSI_LANE_DATA1;
    } else if (dsiCfg.laneNum == DSI_LANE_NUMBER_4) {
        usedLanes |= DSI_LANE_DATA0;
        usedLanes |= DSI_LANE_DATA1;
        usedLanes |= DSI_LANE_DATA2;
        usedLanes |= DSI_LANE_DATA3;
    }

    DSI_Init(DSI0_ID, &dsiCfg);
    DSI_PHY_Reset(DSI0_ID);
    DSI_PHY_Config(DSI0_ID, &dphyCfg);
    DSI_PHY_Enable_Lanes(DSI0_ID, usedLanes);
    return 0;
}

static int mipi_dsi_device_transfer(const struct mipi_dsi_device *dsi,
                                       struct mipi_dsi_msg *msg)
{
    DSI_LPDT_MSG_Type drvMsg = {
        .dataType = msg->type,
        .flag = msg->flags, /* MIPI_DSI_MSG_REQ_ACK or MIPI_DSI_MSG_USE_LPM*/
        .virtualChan = msg->channel,
        .tx_buf = msg->tx_buf,
        .tx_len = msg->tx_len,
        .rx_buf = msg->rx_buf,
        .rx_len = 0,
    };
#if 0
    const struct mipi_dsi_host_ops *ops = dsi->host->ops;

    if(!ops || !ops->transfer)
    {
        return -ENOSYS;
    }

    if(dsi->mode_flags & MIPI_DSI_MODE_LPM)
    {
        msg->flags |= MIPI_DSI_MSG_USE_LPM;
    }

    return ops->transfer(dsi->host, msg);
#endif

    if (mipi_dsi_packet_format_is_short(msg->type)) {
        /* short packet */
        if (dsi->mode_flags & MIPI_DSI_MODE_LPM) {
            /* use LPDT mode tx */
            if (SUCCESS != DSI_LPDT_Send_Short_Packet(DSI0_ID, &drvMsg)) {
                return 0;
            }
        } else {
            return 0;
        }
    } else {
        /* long packet */
        if (dsi->mode_flags & MIPI_DSI_MODE_LPM) {
            /* use LPDT mode tx */
            if (SUCCESS != DSI_LPDT_Send_Long_Packet(DSI0_ID, &drvMsg)) {
                return 0;
            }
        } else {
            return 0;
        }
    }

    /* get response */
    if (msg->flags & MIPI_DSI_MSG_REQ_ACK) {
        if (dsi->mode_flags & MIPI_DSI_MODE_LPM) {
            if (SUCCESS == DSI_LPDT_Recv_Packet(DSI0_ID, &drvMsg)) {
                msg->rx_len = drvMsg.rx_len;
                return msg->rx_len;
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    }

    return msg->tx_len;
}

/**
 * mipi_dsi_create_packet - create a packet from a message according to the
 *     DSI protocol
 * @packet: pointer to a DSI packet structure
 * @msg: message to translate into a packet
 *
 * Return: 0 on success or a negative error code on failure.
 */
int mipi_dsi_create_packet(struct mipi_dsi_packet *packet,
                           const struct mipi_dsi_msg *msg)
{
    if (!packet || !msg) {
        return -EINVAL;
    }

    /* do some minimum sanity checking */
    if (!mipi_dsi_packet_format_is_short(msg->type) &&
        !mipi_dsi_packet_format_is_long(msg->type)) {
        return -EINVAL;
    }

    if (msg->channel > 3) {
        return -EINVAL;
    }

    memset(packet, 0, sizeof(*packet));
    packet->header[0] = ((msg->channel & 0x3) << 6) | (msg->type & 0x3f);

    /* TODO: compute ECC if hardware support is not available */

    /*
     * Long write packets contain the word count in header bytes 1 and 2.
     * The payload follows the header and is word count bytes long.
     *
     * Short write packets encode up to two parameters in header bytes 1
     * and 2.
     */
    if (mipi_dsi_packet_format_is_long(msg->type)) {
        packet->header[1] = (msg->tx_len >> 0) & 0xff;
        packet->header[2] = (msg->tx_len >> 8) & 0xff;

        packet->payload_length = msg->tx_len;
        packet->payload = msg->tx_buf;
    } else {
        const u8 *tx = msg->tx_buf;

        packet->header[1] = (msg->tx_len > 0) ? tx[0] : 0;
        packet->header[2] = (msg->tx_len > 1) ? tx[1] : 0;
    }

    packet->size = sizeof(packet->header) + packet->payload_length;

    return 0;
}

/**
 * mipi_dsi_shutdown_peripheral() - sends a Shutdown Peripheral command
 * @dsi: DSI peripheral device
 *
 * Return: 0 on success or a negative error code on failure.
 */
int mipi_dsi_shutdown_peripheral(const struct mipi_dsi_device *dsi)
{
    struct mipi_dsi_msg msg = {
        .channel = dsi->channel,
        .type = MIPI_DSI_SHUTDOWN_PERIPHERAL,
        .tx_buf = (u8[2]){ 0, 0 },
        .tx_len = 2,
    };
    int ret = mipi_dsi_device_transfer(dsi, &msg);

    return (ret < 0) ? ret : 0;
}

/*
 * mipi_dsi_set_maximum_return_packet_size() - specify the maximum size of the
 *    the payload in a long packet transmitted from the peripheral back to the
 *    host processor
 * @dsi: DSI peripheral device
 * @value: the maximum size of the payload
 *
 * Return: 0 on success or a negative error code on failure.
 */
int mipi_dsi_set_maximum_return_packet_size(const struct mipi_dsi_device *dsi,
                                            u16 value)
{
    u8 tx[2] = { value & 0xff, value >> 8 };
    struct mipi_dsi_msg msg = {
        .channel = dsi->channel,
        .type = MIPI_DSI_SET_MAXIMUM_RETURN_PACKET_SIZE,
        .tx_len = sizeof(tx),
        .tx_buf = tx,
    };
    int ret = mipi_dsi_device_transfer(dsi, &msg);

    return (ret < 0) ? ret : 0;
}

/**
 * mipi_dsi_compression_mode() - enable/disable DSC on the peripheral
 * @dsi: DSI peripheral device
 * @enable: Whether to enable or disable the DSC
 *
 * Enable or disable Display Stream Compression on the peripheral using the
 * default Picture Parameter Set and VESA DSC 1.1 algorithm.
 *
 * Return: 0 on success or a negative error code on failure.
 */
int mipi_dsi_compression_mode(const struct mipi_dsi_device *dsi, bool enable)
{
    /* Note: Needs updating for non-default PPS or algorithm */
    u8 tx[2] = { enable << 0, 0 };
    struct mipi_dsi_msg msg = {
        .channel = dsi->channel,
        .type = MIPI_DSI_COMPRESSION_MODE,
        .tx_len = sizeof(tx),
        .tx_buf = tx,
    };
    int ret = mipi_dsi_device_transfer(dsi, &msg);

    return (ret < 0) ? ret : 0;
}

/**
 * mipi_dsi_picture_parameter_set() - transmit the DSC PPS to the peripheral
 * @dsi: DSI peripheral device
 * @pps: VESA DSC 1.1 Picture Parameter Set
 *
 * Transmit the VESA DSC 1.1 Picture Parameter Set to the peripheral.
 *
 * Return: 0 on success or a negative error code on failure.
 */
int mipi_dsi_picture_parameter_set(const struct mipi_dsi_device *dsi,
                                      const struct drm_dsc_picture_parameter_set *pps)
{
    struct mipi_dsi_msg msg = {
        .channel = dsi->channel,
        .type = MIPI_DSI_PICTURE_PARAMETER_SET,
        .tx_len = sizeof(*pps),
        .tx_buf = pps,
    };
    int ret = mipi_dsi_device_transfer(dsi, &msg);

    return (ret < 0) ? ret : 0;
}

/**
 * mipi_dsi_generic_write() - transmit data using a generic write packet
 * @dsi: DSI peripheral device
 * @payload: buffer containing the payload
 * @size: size of payload buffer
 *
 * This function will automatically choose the right data type depending on
 * the payload length.
 *
 * Return: The number of bytes transmitted on success or a negative error code
 * on failure.
 */
int mipi_dsi_generic_write(const struct mipi_dsi_device *dsi, const void *payload,
                              size_t size)
{
    struct mipi_dsi_msg msg = {
        .channel = dsi->channel,
        .tx_buf = payload,
        .tx_len = size
    };

    switch (size) {
        case 0:
            msg.type = MIPI_DSI_GENERIC_SHORT_WRITE_0_PARAM;
            break;

        case 1:
            msg.type = MIPI_DSI_GENERIC_SHORT_WRITE_1_PARAM;
            break;

        case 2:
            msg.type = MIPI_DSI_GENERIC_SHORT_WRITE_2_PARAM;
            break;

        default:
            msg.type = MIPI_DSI_GENERIC_LONG_WRITE;
            break;
    }

    return mipi_dsi_device_transfer(dsi, &msg);
}

/**
 * mipi_dsi_generic_read() - receive data using a generic read packet
 * @dsi: DSI peripheral device
 * @params: buffer containing the request parameters
 * @num_params: number of request parameters
 * @data: buffer in which to return the received data
 * @size: size of receive buffer
 *
 * This function will automatically choose the right data type depending on
 * the number of parameters passed in.
 *
 * Return: The number of bytes successfully read or a negative error code on
 * failure.
 */
int mipi_dsi_generic_read(const struct mipi_dsi_device *dsi, const void *params,
                             size_t num_params, void *data, size_t size)
{
    struct mipi_dsi_msg msg = {
        .channel = dsi->channel,
        .tx_len = num_params,
        .tx_buf = params,
        .rx_len = size,
        .rx_buf = data
    };

    switch (num_params) {
        case 0:
            msg.type = MIPI_DSI_GENERIC_READ_REQUEST_0_PARAM;
            break;

        case 1:
            msg.type = MIPI_DSI_GENERIC_READ_REQUEST_1_PARAM;
            break;

        case 2:
            msg.type = MIPI_DSI_GENERIC_READ_REQUEST_2_PARAM;
            break;

        default:
            return -EINVAL;
    }

    return mipi_dsi_device_transfer(dsi, &msg);
}

/**
 * mipi_dsi_dcs_write_buffer() - transmit a DCS command with payload
 * @dsi: DSI peripheral device
 * @data: buffer containing data to be transmitted
 * @len: size of transmission buffer
 *
 * This function will automatically choose the right data type depending on
 * the command payload length.
 *
 * Return: The number of bytes successfully transmitted or a negative error
 * code on failure.
 */
int mipi_dsi_dcs_write_buffer(const struct mipi_dsi_device *dsi,
                                 const void *data, size_t len)
{
    struct mipi_dsi_msg msg = {
        .channel = dsi->channel,
        .tx_buf = data,
        .tx_len = len
    };

    switch (len) {
        case 0:
            return -EINVAL;

        case 1:
            msg.type = MIPI_DSI_DCS_SHORT_WRITE;
            break;

        case 2:
            msg.type = MIPI_DSI_DCS_SHORT_WRITE_PARAM;
            break;

        default:
            msg.type = MIPI_DSI_DCS_LONG_WRITE;
            break;
    }

    return mipi_dsi_device_transfer(dsi, &msg);
}

/**
 * mipi_dsi_dcs_write() - send DCS write command
 * @dsi: DSI peripheral device
 * @cmd: DCS command
 * @data: buffer containing the command payload
 * @len: command payload length
 *
 * This function will automatically choose the right data type depending on
 * the command payload length.
 *
 * Return: The number of bytes successfully transmitted or a negative error
 * code on failure.
 */
int mipi_dsi_dcs_write(const struct mipi_dsi_device *dsi, u8 cmd,
                          const void *data, size_t len)
{
    int err;
    size_t size;
    u8 stack_tx[64];
    u8 *tx;

    size = 1 + len;

    if (len > sizeof(stack_tx) - 1) {
        return -ENOMEM;
    } else {
        tx = stack_tx;
    }

    /* concatenate the DCS command byte and the payload */
    tx[0] = cmd;

    if (data) {
        memcpy(&tx[1], data, len);
    }

    err = mipi_dsi_dcs_write_buffer(dsi, tx, size);

    return err;
}

/**
 * mipi_dsi_dcs_read() - send DCS read request command
 * @dsi: DSI peripheral device
 * @cmd: DCS command
 * @data: buffer in which to receive data
 * @len: size of receive buffer
 *
 * Return: The number of bytes read or a negative error code on failure.
 */
int mipi_dsi_dcs_read(const struct mipi_dsi_device *dsi, u8 cmd, void *data,
                         size_t len)
{
    u8 wData[2] = {0};
    struct mipi_dsi_msg msg = {
        .channel = dsi->channel,
        .type = MIPI_DSI_DCS_READ,
        .flags = MIPI_DSI_MSG_REQ_ACK,
        .tx_buf = wData,
        .tx_len = 1,
        .rx_buf = data,
        .rx_len = len
    };

    wData[0] = cmd;

    return mipi_dsi_device_transfer(dsi, &msg);
}

/**
 * mipi_dsi_dcs_nop() - send DCS nop packet
 * @dsi: DSI peripheral device
 *
 * Return: 0 on success or a negative error code on failure.
 */
int mipi_dsi_dcs_nop(const struct mipi_dsi_device *dsi)
{
    int err;

    err = mipi_dsi_dcs_write(dsi, MIPI_DCS_NOP, NULL, 0);

    if (err < 0) {
        return err;
    }

    return 0;
}

/**
 * mipi_dsi_dcs_soft_reset() - perform a software reset of the display module
 * @dsi: DSI peripheral device
 *
 * Return: 0 on success or a negative error code on failure.
 */
int mipi_dsi_dcs_soft_reset(const struct mipi_dsi_device *dsi)
{
    int err;

    err = mipi_dsi_dcs_write(dsi, MIPI_DCS_SOFT_RESET, NULL, 0);

    if (err < 0) {
        return err;
    }

    return 0;
}

/**
 * mipi_dsi_dcs_get_power_mode() - query the display module's current power
 *    mode
 * @dsi: DSI peripheral device
 * @mode: return location for the current power mode
 *
 * Return: 0 on success or a negative error code on failure.
 */
int mipi_dsi_dcs_get_power_mode(const struct mipi_dsi_device *dsi, u8 *mode)
{
    int err;

    err = mipi_dsi_dcs_read(dsi, MIPI_DCS_GET_POWER_MODE, mode,
                            sizeof(*mode));

    if (err <= 0) {
        if (err == 0) {
            err = -ENODATA;
        }

        return err;
    }

    return 0;
}

/**
 * mipi_dsi_dcs_get_pixel_format() - gets the pixel format for the RGB image
 *    data used by the interface
 * @dsi: DSI peripheral device
 * @format: return location for the pixel format
 *
 * Return: 0 on success or a negative error code on failure.
 */
int mipi_dsi_dcs_get_pixel_format(const struct mipi_dsi_device *dsi, u8 *format)
{
    int err;

    err = mipi_dsi_dcs_read(dsi, MIPI_DCS_GET_PIXEL_FORMAT, format,
                            sizeof(*format));

    if (err <= 0) {
        if (err == 0) {
            err = -ENODATA;
        }

        return err;
    }

    return 0;
}

/**
 * mipi_dsi_dcs_enter_sleep_mode() - disable all unnecessary blocks inside the
 *    display module except interface communication
 * @dsi: DSI peripheral device
 *
 * Return: 0 on success or a negative error code on failure.
 */
int mipi_dsi_dcs_enter_sleep_mode(const struct mipi_dsi_device *dsi)
{
    int err;

    err = mipi_dsi_dcs_write(dsi, MIPI_DCS_ENTER_SLEEP_MODE, NULL, 0);

    if (err < 0) {
        return err;
    }

    return 0;
}

/**
 * mipi_dsi_dcs_exit_sleep_mode() - enable all blocks inside the display
 *    module
 * @dsi: DSI peripheral device
 *
 * Return: 0 on success or a negative error code on failure.
 */
int mipi_dsi_dcs_exit_sleep_mode(const struct mipi_dsi_device *dsi)
{
    int err;

    err = mipi_dsi_dcs_write(dsi, MIPI_DCS_EXIT_SLEEP_MODE, NULL, 0);

    if (err < 0) {
        return err;
    }

    return 0;
}

/**
 * mipi_dsi_dcs_set_display_off() - stop displaying the image data on the
 *    display device
 * @dsi: DSI peripheral device
 *
 * Return: 0 on success or a negative error code on failure.
 */
int mipi_dsi_dcs_set_display_off(const struct mipi_dsi_device *dsi)
{
    int err;

    err = mipi_dsi_dcs_write(dsi, MIPI_DCS_SET_DISPLAY_OFF, NULL, 0);

    if (err < 0) {
        return err;
    }

    return 0;
}

/**
 * mipi_dsi_dcs_set_display_on() - start displaying the image data on the
 *    display device
 * @dsi: DSI peripheral device
 *
 * Return: 0 on success or a negative error code on failure
 */
int mipi_dsi_dcs_set_display_on(const struct mipi_dsi_device *dsi)
{
    int err;

    err = mipi_dsi_dcs_write(dsi, MIPI_DCS_SET_DISPLAY_ON, NULL, 0);

    if (err < 0) {
        return err;
    }

    return 0;
}

/**
 * mipi_dsi_dcs_set_column_address() - define the column extent of the frame
 *    memory accessed by the host processor
 * @dsi: DSI peripheral device
 * @start: first column of frame memory
 * @end: last column of frame memory
 *
 * Return: 0 on success or a negative error code on failure.
 */
int mipi_dsi_dcs_set_column_address(const struct mipi_dsi_device *dsi, u16 start,
                                    u16 end)
{
    u8 payload[4] = { start >> 8, start & 0xff, end >> 8, end & 0xff };
    int err;

    err = mipi_dsi_dcs_write(dsi, MIPI_DCS_SET_COLUMN_ADDRESS, payload,
                             sizeof(payload));

    if (err < 0) {
        return err;
    }

    return 0;
}

/**
 * mipi_dsi_dcs_set_page_address() - define the page extent of the frame
 *    memory accessed by the host processor
 * @dsi: DSI peripheral device
 * @start: first page of frame memory
 * @end: last page of frame memory
 *
 * Return: 0 on success or a negative error code on failure.
 */
int mipi_dsi_dcs_set_page_address(const struct mipi_dsi_device *dsi, u16 start,
                                  u16 end)
{
    u8 payload[4] = { start >> 8, start & 0xff, end >> 8, end & 0xff };
    int err;

    err = mipi_dsi_dcs_write(dsi, MIPI_DCS_SET_PAGE_ADDRESS, payload,
                             sizeof(payload));

    if (err < 0) {
        return err;
    }

    return 0;
}

/**
 * mipi_dsi_dcs_set_tear_off() - turn off the display module's Tearing Effect
 *    output signal on the TE signal line
 * @dsi: DSI peripheral device
 *
 * Return: 0 on success or a negative error code on failure
 */
int mipi_dsi_dcs_set_tear_off(const struct mipi_dsi_device *dsi)
{
    int err;

    err = mipi_dsi_dcs_write(dsi, MIPI_DCS_SET_TEAR_OFF, NULL, 0);

    if (err < 0) {
        return err;
    }

    return 0;
}

/**
 * mipi_dsi_dcs_set_tear_on() - turn on the display module's Tearing Effect
 *    output signal on the TE signal line.
 * @dsi: DSI peripheral device
 * @mode: the Tearing Effect Output Line mode
 *
 * Return: 0 on success or a negative error code on failure
 */
int mipi_dsi_dcs_set_tear_on(const struct mipi_dsi_device *dsi,
                             enum mipi_dsi_dcs_tear_mode mode)
{
    u8 value = mode;
    int err;

    err = mipi_dsi_dcs_write(dsi, MIPI_DCS_SET_TEAR_ON, &value,
                             sizeof(value));

    if (err < 0) {
        return err;
    }

    return 0;
}

/**
 * mipi_dsi_dcs_set_pixel_format() - sets the pixel format for the RGB image
 *    data used by the interface
 * @dsi: DSI peripheral device
 * @format: pixel format
 *
 * Return: 0 on success or a negative error code on failure.
 */
int mipi_dsi_dcs_set_pixel_format(const struct mipi_dsi_device *dsi, u8 format)
{
    int err;

    err = mipi_dsi_dcs_write(dsi, MIPI_DCS_SET_PIXEL_FORMAT, &format,
                             sizeof(format));

    if (err < 0) {
        return err;
    }

    return 0;
}

/**
 * mipi_dsi_dcs_set_tear_scanline() - set the scanline to use as trigger for
 *    the Tearing Effect output signal of the display module
 * @dsi: DSI peripheral device
 * @scanline: scanline to use as trigger
 *
 * Return: 0 on success or a negative error code on failure
 */
int mipi_dsi_dcs_set_tear_scanline(const struct mipi_dsi_device *dsi, u16 scanline)
{
    u8 payload[2] = { scanline >> 8, scanline & 0xff };
    int err;

    err = mipi_dsi_dcs_write(dsi, MIPI_DCS_SET_TEAR_SCANLINE, payload,
                             sizeof(payload));

    if (err < 0) {
        return err;
    }

    return 0;
}

/**
 * mipi_dsi_dcs_set_display_brightness() - sets the brightness value of the
 *    display
 * @dsi: DSI peripheral device
 * @brightness: brightness value
 *
 * Return: 0 on success or a negative error code on failure.
 */
int mipi_dsi_dcs_set_display_brightness(const struct mipi_dsi_device *dsi,
                                        u16 brightness)
{
    u8 payload[2] = { brightness & 0xff, brightness >> 8 };
    int err;

    err = mipi_dsi_dcs_write(dsi, MIPI_DCS_SET_DISPLAY_BRIGHTNESS,
                             payload, sizeof(payload));

    if (err < 0) {
        return err;
    }

    return 0;
}

/**
 * mipi_dsi_dcs_get_display_brightness() - gets the current brightness value
 *    of the display
 * @dsi: DSI peripheral device
 * @brightness: brightness value
 *
 * Return: 0 on success or a negative error code on failure.
 */
int mipi_dsi_dcs_get_display_brightness(const struct mipi_dsi_device *dsi,
                                        u16 *brightness)
{
    int err;

    err = mipi_dsi_dcs_read(dsi, MIPI_DCS_GET_DISPLAY_BRIGHTNESS,
                            brightness, sizeof(*brightness));

    if (err <= 0) {
        if (err == 0) {
            err = -ENODATA;
        }

        return err;
    }

    return 0;
}