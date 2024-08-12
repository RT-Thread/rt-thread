/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_mipi_dsi_drv.h"

#define MIPI_WAIT_COND(cond, timeout_us)	\
({ \
    volatile uint32_t timeout_cycle = 1000UL * (timeout_us); \
    for (;;) { \
        if (cond) \
            break; \
        if (timeout_us && timeout_cycle == 0) { \
            break; \
        } \
        timeout_cycle--; \
    } \
    (cond) ? true : false; \
})

typedef struct mipi_dsi_packet {
    uint8_t header[4]; /*!< the four bytes that make up the header (Data ID, Word Count or Packet Data, and ECC) */
    uint16_t payload_length; /*!< number of bytes in the payload */
    const uint8_t *payload; /*!< a pointer to a buffer containing the payload, if any */
} mipi_dsi_packet_t;

/**
 * mipi_dsi_packet_format_is_short - check if a packet is of the short format
 * @param type: MIPI DSI data type of the packet
 *
 * @return: true if the packet for the given data type is a short packet, false
 * otherwise.
 */
static bool mipi_dsi_packet_format_is_short(uint8_t type)
{
    switch (type) {
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
    case MIPI_DSI_SET_MAXIMUM_RETURN_PACKET_SIZE:
        return true;
    }

    return false;
}

/**
 * mipi_dsi_packet_format_is_long - check if a packet is of the long format
 * @param type: MIPI DSI data type of the packet
 *
 * @return: true if the packet for the given data type is a long packet, false
 * otherwise.
 */
static bool mipi_dsi_packet_format_is_long(uint8_t type)
{
    switch (type) {
    case MIPI_DSI_GENERIC_LONG_WRITE:
    case MIPI_DSI_DCS_LONG_WRITE:
        return true;
    }

    return false;
}

/**
 * mipi_dsi_create_packet - create a packet from a message according to the
 *	DSI protocol
 * @param packet: pointer to a DSI packet structure
 * @param msg: message to translate into a packet
 *
 * @return: true on success or false on failure.
 */
static bool mipi_dsi_create_packet(mipi_dsi_packet_t *packet, const mipi_dsi_msg_t *msg)
{
    if (!packet || !msg)
        return false;

    /* do some minimum sanity checking */
    if (!mipi_dsi_packet_format_is_short(msg->type) &&
        !mipi_dsi_packet_format_is_long(msg->type))
        return false;

    if (msg->channel > 3)
        return false;

    memset(packet, 0, sizeof(*packet));
    packet->header[0] = ((msg->channel & 0x3) << 6) | (msg->type & 0x3f);
    if (mipi_dsi_packet_format_is_long(msg->type)) {
        packet->header[1] = (msg->tx_len >> 0) & 0xff;
        packet->header[2] = (msg->tx_len >> 8) & 0xff;

        packet->payload_length = msg->tx_len;
        packet->payload = (const uint8_t *)msg->tx_buf;
    } else {
        const uint8_t *tx = (const uint8_t *)msg->tx_buf;

        packet->header[1] = (msg->tx_len > 0) ? tx[0] : 0;
        packet->header[2] = (msg->tx_len > 1) ? tx[1] : 0;
    }

    return true;
}

static void mipi_dsi_config_format(MIPI_DSI_Type *ptr, mipi_dsi_pixel_format_t format)
{
    uint32_t val = 0;

    switch ((uint8_t)format) {
    case MIPI_DSI_FMT_RGB888:
        val = MIPI_DSI_DPI_COLOR_CODING_DPI_COLOR_CODING_SET(0x05);
        break;
    case MIPI_DSI_FMT_RGB666:
        val = MIPI_DSI_DPI_COLOR_CODING_DPI_COLOR_CODING_SET(0x04) |
                MIPI_DSI_DPI_COLOR_CODING_LOOSELY18_EN_MASK;
        break;
    case MIPI_DSI_FMT_RGB666_PACKED:
        val = MIPI_DSI_DPI_COLOR_CODING_DPI_COLOR_CODING_SET(0x04);
        break;
    case MIPI_DSI_FMT_RGB565:
        val = MIPI_DSI_DPI_COLOR_CODING_DPI_COLOR_CODING_SET(0x00);
        break;
    }

    ptr->DPI_COLOR_CODING = val;
}

/* Get lane byte clock cycles. */
static int mipi_dsi_get_hcomponent_lbcc(uint32_t lane_mbps, uint32_t pixel_clock_khz, uint32_t hcomponent)
{
	uint32_t lbcc = hcomponent * lane_mbps * 1000 / 8;

	if (!pixel_clock_khz)
		return 0;

	return HPM_DIV_ROUND_CLOSEST(lbcc, pixel_clock_khz);
}

static void mipi_dsi_video_para_config(MIPI_DSI_Type *ptr, mipi_dsi_config_t *cfg)
{
    mipi_video_para_t *video_para = &cfg->video_para;
    int htotal, lbcc;

    /* VID_HXXXX_TIME uint is lbcc(lane byte clock = lane_mbps / 8) */
    htotal = video_para->hactive + video_para->hsync_len +
                video_para->hback_porch + video_para->hfront_porch;
    lbcc = mipi_dsi_get_hcomponent_lbcc(cfg->lane_mbps, video_para->pixel_clock_khz, htotal);
    ptr->VID_HLINE_TIME = lbcc;
    lbcc = mipi_dsi_get_hcomponent_lbcc(cfg->lane_mbps, video_para->pixel_clock_khz, video_para->hsync_len);
    ptr->VID_HSA_TIME = lbcc;
    lbcc = mipi_dsi_get_hcomponent_lbcc(cfg->lane_mbps, video_para->pixel_clock_khz, video_para->hback_porch);
    ptr->VID_HBP_TIME = lbcc;

    ptr->VID_VACTIVE_LINES = video_para->vactive;
    ptr->VID_VSA_LINES = video_para->vsync_len;
    ptr->VID_VBP_LINES = video_para->vback_porch;
    ptr->VID_VFP_LINES = video_para->vfront_porch;
}

static bool mipi_dsi_genif_wait_w_pld_fifo_not_full(MIPI_DSI_Type *ptr)
{
    uint32_t mask = MIPI_DSI_CMD_PKT_STATUS_GEN_PLD_W_FULL_MASK;
    return MIPI_WAIT_COND(!(ptr->CMD_PKT_STATUS & mask), 10000);
}

static bool mipi_dsi_genif_wait_cmd_fifo_not_full(MIPI_DSI_Type *ptr)
{
    uint32_t mask = MIPI_DSI_CMD_PKT_STATUS_GEN_CMD_FULL_MASK;
    return MIPI_WAIT_COND(!(ptr->CMD_PKT_STATUS & mask), 10000);
}

static bool mipi_dsi_genif_wait_write_fifo_empty(MIPI_DSI_Type *ptr)
{
    uint32_t mask = MIPI_DSI_CMD_PKT_STATUS_GEN_CMD_EMPTY_MASK |
                    MIPI_DSI_CMD_PKT_STATUS_GEN_PLD_W_EMPTY_MASK;

    return MIPI_WAIT_COND((ptr->CMD_PKT_STATUS & mask) == mask, 10000);
}

static bool dw_mipi_dsi_read_from_fifo(MIPI_DSI_Type *ptr,
				      const struct mipi_dsi_msg *msg)
{
    uint8_t *payload = (uint8_t *)msg->rx_buf;
    uint16_t length;
    uint32_t val;
    uint32_t mask;
    bool ret = true;

    mask = MIPI_DSI_CMD_PKT_STATUS_GEN_RD_CMD_BUSY_MASK;
    ret = MIPI_WAIT_COND(!(ptr->CMD_PKT_STATUS & mask), 10000);
    if (ret == false) {
        return ret;
    }

    /* Receive payload */
    for (length = msg->rx_len; length; length -= 4) {
        mask = MIPI_DSI_CMD_PKT_STATUS_GEN_PLD_R_EMPTY_MASK;
        ret = MIPI_WAIT_COND(!(ptr->CMD_PKT_STATUS & mask), 10000);
        if (ret == false) {
            return ret;
        }

        val = ptr->GEN_PLD_DATA;

        switch (length) {
        case 3:
            payload[2] = (val >> 16) & 0xff;
        /* Fall through */
        case 2:
            payload[1] = (val >> 8) & 0xff;
        /* Fall through */
        case 1:
            payload[0] = val & 0xff;
            return ret;
        }

        payload[0] = (val >>  0) & 0xff;
        payload[1] = (val >>  8) & 0xff;
        payload[2] = (val >> 16) & 0xff;
        payload[3] = (val >> 24) & 0xff;
        payload += 4;
    }

    return ret;
}

static uint32_t get_le32(const uint8_t *p)
{
    return p[0] | p[1] << 8 | p[2] << 16 | p[3] << 24;
}

void mipi_dsi_get_defconfig_on_video(mipi_dsi_config_t *cfg)
{
    mipi_video_para_t video_para = {
        .pixel_clock_khz = 59400,
        .hactive = 800,
        .hsync_len = 8,
        .hback_porch = 48,
        .hfront_porch = 52,
        .vsync_len = 6,
        .vactive = 1280,
        .vback_porch = 16,
        .vfront_porch = 15
    };

    cfg->lanes = 4;
    cfg->channel = 0;
    cfg->lane_mbps = 500;
    cfg->disable_eotp = false;
    cfg->pixel_format = MIPI_DSI_FMT_RGB888;
    cfg->video_mode = MIPI_DSI_VIDEO_MODE_BURST;
    cfg->video_para = video_para;
}

void mipi_dsi_init(MIPI_DSI_Type *ptr, mipi_dsi_config_t *cfg)
{
    uint32_t val;

    /* PWR need reset when config register */
    ptr->PWR_UP &= ~MIPI_DSI_PWR_UP_SHUTDOWNZ_MASK;

    /* escclk config about 20MHz and esc_clk_div > 1*/
    uint32_t esc_clk_div = HPM_DIV_ROUND_UP(cfg->lane_mbps / 8, 20);
    esc_clk_div = esc_clk_div <= 1 ? 2 : esc_clk_div;

    ptr->CLKMGR_CFG = MIPI_DSI_CLKMGR_CFG_TO_CLK_DIVISION_SET(10) |
        MIPI_DSI_CLKMGR_CFG_TX_ESC_CLK_DIVISION_SET(esc_clk_div);

    mipi_dsi_config_format(ptr, cfg->pixel_format);
    ptr->DPI_VCID = MIPI_DSI_DPI_VCID_DPI_VCID_SET(cfg->channel);
    ptr->DPI_LP_CMD_TIM = MIPI_DSI_DPI_LP_CMD_TIM_OUTVACT_LPCMD_TIME_SET(4) |
                            MIPI_DSI_DPI_LP_CMD_TIM_OUTVACT_LPCMD_TIME_SET(4);

    val = MIPI_DSI_PCKHDL_CFG_BTA_EN_MASK |
            MIPI_DSI_PCKHDL_CFG_EOTP_TX_EN_MASK |
            MIPI_DSI_PCKHDL_CFG_ECC_RX_EN_MASK |
            MIPI_DSI_PCKHDL_CFG_CRC_RX_EN_MASK;
    if (cfg->disable_eotp)
        val &= ~MIPI_DSI_PCKHDL_CFG_EOTP_TX_EN_MASK;
    ptr->PCKHDL_CFG = val;

    val = MIPI_DSI_VID_MODE_CFG_LP_HFP_EN_MASK |
            MIPI_DSI_VID_MODE_CFG_LP_HBP_EN_MASK |
            MIPI_DSI_VID_MODE_CFG_LP_VACT_EN_MASK |
            MIPI_DSI_VID_MODE_CFG_LP_VFP_EN_MASK |
            MIPI_DSI_VID_MODE_CFG_LP_VBP_EN_MASK |
            MIPI_DSI_VID_MODE_CFG_LP_VSA_EN_MASK |
            MIPI_DSI_VID_MODE_CFG_VID_MODE_TYPE_SET(cfg->video_mode);
    ptr->VID_MODE_CFG = val;

    ptr->VID_PKT_SIZE = cfg->video_para.hactive;

    ptr->TO_CNT_CFG = MIPI_DSI_TO_CNT_CFG_HSTX_TO_CNT_SET(1000) |
                        MIPI_DSI_TO_CNT_CFG_LPRX_TO_CNT_SET(1000);

    ptr->BTA_TO_CNT = MIPI_DSI_BTA_TO_CNT_BTA_TO_CNT_SET(0xd00);

    mipi_dsi_video_para_config(ptr, cfg);

    ptr->PHY_TMR_CFG = MIPI_DSI_PHY_TMR_CFG_PHY_HS2LP_TIME_SET(0x40) |
                        MIPI_DSI_PHY_TMR_CFG_PHY_LP2HS_TIME_SET(0x40);
    ptr->PHY_TMR_RD = 10000;
    ptr->PHY_TMR_LPCLK_CFG = MIPI_DSI_PHY_TMR_LPCLK_CFG_PHY_CLKHS2LP_TIME_SET(0x40) |
                                MIPI_DSI_PHY_TMR_LPCLK_CFG_PHY_CLKLP2HS_TIME_SET(0x40);
    ptr->PHY_IF_CFG = MIPI_DSI_PHY_IF_CFG_PHY_STOP_WAIT_TIME_SET(0x20) |
                        MIPI_DSI_PHY_IF_CFG_N_LANES_SET(cfg->lanes - 1);
    ptr->PWR_UP |= MIPI_DSI_PWR_UP_SHUTDOWNZ_MASK;
}

void mipi_dsi_phy_poweron(MIPI_DSI_Type *ptr)
{
    ptr->PHY_RSTZ |= MIPI_DSI_PHY_RSTZ_PHY_SHUTDOWNZ_MASK;
    ptr->PHY_RSTZ |= MIPI_DSI_PHY_RSTZ_PHY_RSTZ_MASK;
}

void mipi_dsi_phy_powerdown(MIPI_DSI_Type *ptr)
{
    ptr->PHY_RSTZ &= ~(MIPI_DSI_PHY_RSTZ_PHY_SHUTDOWNZ_MASK |
                        MIPI_DSI_PHY_RSTZ_PHY_RSTZ_MASK);
}

void mipi_dsi_video_mode_hs_transfer_enable(MIPI_DSI_Type *ptr)
{
    ptr->PWR_UP &= ~MIPI_DSI_PWR_UP_SHUTDOWNZ_MASK;
    ptr->LPCLK_CTRL |= MIPI_DSI_LPCLK_CTRL_PHY_TXREQUESTCLKHS_MASK;
    ptr->MODE_CFG = MIPI_DSI_MODE_CFG_CMD_VIDEO_MODE_SET(0);
    ptr->PWR_UP |= MIPI_DSI_PWR_UP_SHUTDOWNZ_MASK;
}

void mipi_dsi_video_mode_hs_transfer_disable(MIPI_DSI_Type *ptr)
{
    ptr->PWR_UP &= ~MIPI_DSI_PWR_UP_SHUTDOWNZ_MASK;
    ptr->LPCLK_CTRL &= ~MIPI_DSI_LPCLK_CTRL_PHY_TXREQUESTCLKHS_MASK;
}

int mipi_dsi_lp_cmd_transfer(MIPI_DSI_Type *ptr, const mipi_dsi_msg_t *msg)
{
    struct mipi_dsi_packet packet;
    int ret = -1;
    int val;

    /* do some minimum sanity checking */
    if (!mipi_dsi_packet_format_is_short(msg->type) &&
        !mipi_dsi_packet_format_is_long(msg->type))
        return ret;

    ptr->VID_MODE_CFG |= MIPI_DSI_VID_MODE_CFG_LP_CMD_EN_MASK;
    ptr->LPCLK_CTRL &= ~MIPI_DSI_LPCLK_CTRL_PHY_TXREQUESTCLKHS_MASK;

    /* create a packet to the DSI protocol */
    if (mipi_dsi_create_packet(&packet, msg) == false) {
        return ret;
    }

    ptr->CMD_MODE_CFG = 1u<<24 | 1u<<19 | 1u<<18 | 1u<<17 |
                        1u<<16 | 1u<<14 | 1u<<13 | 1u<<12 |
                        1u<<11 | 1u<<10 | 1u<<9 | 1u<<8;

    /* config to cmd mode */
    ptr->MODE_CFG = MIPI_DSI_MODE_CFG_CMD_VIDEO_MODE_SET(1);

    /* Send payload */
    while (packet.payload_length > 0) {
        /*
         * Alternatively, you can always keep the FIFO
         * nearly full by monitoring the FIFO state until
         * it is not full, and then writea single word of data.
         * This solution is more resource consuming
         * but it simultaneously avoids FIFO starvation,
         * making it possible to use FIFO sizes smaller than
         * the amount of data of the longest packet to be written.
         */
        if (mipi_dsi_genif_wait_w_pld_fifo_not_full(ptr) == false)
            return ret;

        if (packet.payload_length < 4) {
            /* send residu payload */
            val = 0;
            memcpy(&val, packet.payload, packet.payload_length);
            packet.payload_length = 0;
        } else {
            val = get_le32(packet.payload);
            packet.payload += 4;
            packet.payload_length -= 4;
        }
        ptr->GEN_PLD_DATA = val;
    }

    if (mipi_dsi_genif_wait_cmd_fifo_not_full(ptr) == false)
        return ret;

    /* Send packet header */
    val = get_le32(packet.header);
    ptr->GEN_HDR = val;

    if (mipi_dsi_genif_wait_write_fifo_empty(ptr) == false)
        return ret;

    if (msg->rx_len) {
        if (dw_mipi_dsi_read_from_fifo(ptr, msg) == false)
            return ret;
    }

    return msg->rx_len ? msg->rx_len : msg->tx_len;
}

int mipi_dsi_set_maximum_return_packet_size(MIPI_DSI_Type *ptr, uint8_t channel, uint16_t value)
{
    uint8_t tx[2] = {value & 0xff, value >> 8};
    struct mipi_dsi_msg msg = {
        .channel = channel,
        .type = MIPI_DSI_SET_MAXIMUM_RETURN_PACKET_SIZE,
        .tx_len = sizeof(tx),
        .tx_buf = tx,
    };

    int ret = mipi_dsi_lp_cmd_transfer(ptr, &msg);

    return (ret < 0) ? false : true;
}

int mipi_dsi_generic_write(MIPI_DSI_Type *ptr, uint8_t channel, const void *payload,
			       uint16_t size)
{
    struct mipi_dsi_msg msg = {
        .channel = channel,
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

    return mipi_dsi_lp_cmd_transfer(ptr, &msg);
}


int mipi_dsi_generic_read(MIPI_DSI_Type *ptr, uint8_t channel, const void *params,
			      uint16_t num_params, void *data, uint16_t size)
{
    struct mipi_dsi_msg msg = {
        .channel = channel,
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
        return -1;
    }

    return mipi_dsi_lp_cmd_transfer(ptr, &msg);
}


int mipi_dsi_dcs_write_buffer(MIPI_DSI_Type *ptr, uint8_t channel,
				  const void *data, uint16_t len)
{
    struct mipi_dsi_msg msg = {
        .channel = channel,
        .tx_buf = data,
        .tx_len = len
    };

    switch (len) {
    case 0:
        return -1;
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

    return mipi_dsi_lp_cmd_transfer(ptr, &msg);
}

int mipi_dsi_dcs_write(MIPI_DSI_Type *ptr, uint8_t channel, uint8_t cmd,
			   const void *data, uint16_t len)
{
    int err;
    uint16_t size;
    uint8_t tx[128];

    if (len < sizeof(tx)) {
        size = 1 + len;
        tx[0] = cmd;
        if (len > 0)
            memcpy(&tx[1], data, len);
    } else {
        return -1;
    }

    err = mipi_dsi_dcs_write_buffer(ptr, channel, tx, size);

    return err;
}

int mipi_dsi_dcs_read(MIPI_DSI_Type *ptr, uint8_t channel, uint8_t cmd, void *data, uint16_t len)
{
	struct mipi_dsi_msg msg = {
		.channel = channel,
		.type = MIPI_DSI_DCS_READ,
		.tx_buf = &cmd,
		.tx_len = 1,
		.rx_buf = data,
		.rx_len = len
	};

	return mipi_dsi_lp_cmd_transfer(ptr, &msg);
}