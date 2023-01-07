/**
 * @file hal_dsi.h
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
#ifndef __HAL_DSI__H__
#define __HAL_DSI__H__

#include "hal_common.h"
#include "drv_device.h"
#include "bl808_config.h"

#define DSI_DEV_NAME_SIZE 20
#define u8                uint8_t
#define u16               uint16_t
#define u32               uint32_t
#define __be16            uint16_t
/* VESA Display Stream Compression DSC 1.2 constants */
#define DSC_NUM_BUF_RANGES 15

enum mipi_dsi_index_type {
    DSI0_INDEX,
    DSI_MAX_INDEX
};

struct mipi_dsi_host;
struct mipi_dsi_device;
struct drm_dsc_picture_parameter_set;

/**
 * struct drm_dsc_picture_parameter_set - Represents 128 bytes of
 *  Picture Parameter Set
 *
 * The VESA DSC standard defines picture parameter set (PPS) which display
 * stream compression encoders must communicate to decoders.
 * The PPS is encapsulated in 128 bytes (PPS 0 through PPS 127). The fields in
 * this structure are as per Table 4.1 in Vesa DSC specification v1.1/v1.2.
 * The PPS fields that span over more than a byte should be stored in Big Endian
 * format.
 */
struct drm_dsc_picture_parameter_set {
    /**
	 * @dsc_version:
	 * PPS0[3:0] - dsc_version_minor: Contains Minor version of DSC
	 * PPS0[7:4] - dsc_version_major: Contains major version of DSC
	 */
    u8 dsc_version;
    /**
	 * @pps_identifier:
	 * PPS1[7:0] - Application specific identifier that can be
	 * used to differentiate between different PPS tables.
	 */
    u8 pps_identifier;
    /**
	 * @pps_reserved:
	 * PPS2[7:0]- RESERVED Byte
	 */
    u8 pps_reserved;
    /**
	 * @pps_3:
	 * PPS3[3:0] - linebuf_depth: Contains linebuffer bit depth used to
	 * generate the bitstream. (0x0 - 16 bits for DSC 1.2, 0x8 - 8 bits,
	 * 0xA - 10 bits, 0xB - 11 bits, 0xC - 12 bits, 0xD - 13 bits,
	 * 0xE - 14 bits for DSC1.2, 0xF - 14 bits for DSC 1.2.
	 * PPS3[7:4] - bits_per_component: Bits per component for the original
	 * pixels of the encoded picture.
	 * 0x0 = 16bpc (allowed only when dsc_version_minor = 0x2)
	 * 0x8 = 8bpc, 0xA = 10bpc, 0xC = 12bpc, 0xE = 14bpc (also
	 * allowed only when dsc_minor_version = 0x2)
	 */
    u8 pps_3;
    /**
	 * @pps_4:
	 * PPS4[1:0] -These are the most significant 2 bits of
	 * compressed BPP bits_per_pixel[9:0] syntax element.
	 * PPS4[2] - vbr_enable: 0 = VBR disabled, 1 = VBR enabled
	 * PPS4[3] - simple_422: Indicates if decoder drops samples to
	 * reconstruct the 4:2:2 picture.
	 * PPS4[4] - Convert_rgb: Indicates if DSC color space conversion is
	 * active.
	 * PPS4[5] - blobk_pred_enable: Indicates if BP is used to code any
	 * groups in picture
	 * PPS4[7:6] - Reseved bits
	 */
    u8 pps_4;
    /**
	 * @bits_per_pixel_low:
	 * PPS5[7:0] - This indicates the lower significant 8 bits of
	 * the compressed BPP bits_per_pixel[9:0] element.
	 */
    u8 bits_per_pixel_low;
    /**
	 * @pic_height:
	 * PPS6[7:0], PPS7[7:0] -pic_height: Specifies the number of pixel rows
	 * within the raster.
	 */
    __be16 pic_height;
    /**
	 * @pic_width:
	 * PPS8[7:0], PPS9[7:0] - pic_width: Number of pixel columns within
	 * the raster.
	 */
    __be16 pic_width;
    /**
	 * @slice_height:
	 * PPS10[7:0], PPS11[7:0] - Slice height in units of pixels.
	 */
    __be16 slice_height;
    /**
	 * @slice_width:
	 * PPS12[7:0], PPS13[7:0] - Slice width in terms of pixels.
	 */
    __be16 slice_width;
    /**
	 * @chunk_size:
	 * PPS14[7:0], PPS15[7:0] - Size in units of bytes of the chunks
	 * that are used for slice multiplexing.
	 */
    __be16 chunk_size;
    /**
	 * @initial_xmit_delay_high:
	 * PPS16[1:0] - Most Significant two bits of initial transmission delay.
	 * It specifies the number of pixel times that the encoder waits before
	 * transmitting data from its rate buffer.
	 * PPS16[7:2] - Reserved
	 */
    u8 initial_xmit_delay_high;
    /**
	 * @initial_xmit_delay_low:
	 * PPS17[7:0] - Least significant 8 bits of initial transmission delay.
	 */
    u8 initial_xmit_delay_low;
    /**
	 * @initial_dec_delay:
	 *
	 * PPS18[7:0], PPS19[7:0] - Initial decoding delay which is the number
	 * of pixel times that the decoder accumulates data in its rate buffer
	 * before starting to decode and output pixels.
	 */
    __be16 initial_dec_delay;
    /**
	 * @pps20_reserved:
	 *
	 * PPS20[7:0] - Reserved
	 */
    u8 pps20_reserved;
    /**
	 * @initial_scale_value:
	 * PPS21[5:0] - Initial rcXformScale factor used at beginning
	 * of a slice.
	 * PPS21[7:6] - Reserved
	 */
    u8 initial_scale_value;
    /**
	 * @scale_increment_interval:
	 * PPS22[7:0], PPS23[7:0] - Number of group times between incrementing
	 * the rcXformScale factor at end of a slice.
	 */
    __be16 scale_increment_interval;
    /**
	 * @scale_decrement_interval_high:
	 * PPS24[3:0] - Higher 4 bits indicating number of group times between
	 * decrementing the rcXformScale factor at beginning of a slice.
	 * PPS24[7:4] - Reserved
	 */
    u8 scale_decrement_interval_high;
    /**
	 * @scale_decrement_interval_low:
	 * PPS25[7:0] - Lower 8 bits of scale decrement interval
	 */
    u8 scale_decrement_interval_low;
    /**
	 * @pps26_reserved:
	 * PPS26[7:0]
	 */
    u8 pps26_reserved;
    /**
	 * @first_line_bpg_offset:
	 * PPS27[4:0] - Number of additional bits that are allocated
	 * for each group on first line of a slice.
	 * PPS27[7:5] - Reserved
	 */
    u8 first_line_bpg_offset;
    /**
	 * @nfl_bpg_offset:
	 * PPS28[7:0], PPS29[7:0] - Number of bits including frac bits
	 * deallocated for each group for groups after the first line of slice.
	 */
    __be16 nfl_bpg_offset;
    /**
	 * @slice_bpg_offset:
	 * PPS30, PPS31[7:0] - Number of bits that are deallocated for each
	 * group to enforce the slice constraint.
	 */
    __be16 slice_bpg_offset;
    /**
	 * @initial_offset:
	 * PPS32,33[7:0] - Initial value for rcXformOffset
	 */
    __be16 initial_offset;
    /**
	 * @final_offset:
	 * PPS34,35[7:0] - Maximum end-of-slice value for rcXformOffset
	 */
    __be16 final_offset;
    /**
	 * @flatness_min_qp:
	 * PPS36[4:0] - Minimum QP at which flatness is signaled and
	 * flatness QP adjustment is made.
	 * PPS36[7:5] - Reserved
	 */
    u8 flatness_min_qp;
    /**
	 * @flatness_max_qp:
	 * PPS37[4:0] - Max QP at which flatness is signalled and
	 * the flatness adjustment is made.
	 * PPS37[7:5] - Reserved
	 */
    u8 flatness_max_qp;
    /**
	 * @rc_model_size:
	 * PPS38,39[7:0] - Number of bits within RC Model.
	 */
    __be16 rc_model_size;
    /**
	 * @rc_edge_factor:
	 * PPS40[3:0] - Ratio of current activity vs, previous
	 * activity to determine presence of edge.
	 * PPS40[7:4] - Reserved
	 */
    u8 rc_edge_factor;
    /**
	 * @rc_quant_incr_limit0:
	 * PPS41[4:0] - QP threshold used in short term RC
	 * PPS41[7:5] - Reserved
	 */
    u8 rc_quant_incr_limit0;
    /**
	 * @rc_quant_incr_limit1:
	 * PPS42[4:0] - QP threshold used in short term RC
	 * PPS42[7:5] - Reserved
	 */
    u8 rc_quant_incr_limit1;
    /**
	 * @rc_tgt_offset:
	 * PPS43[3:0] - Lower end of the variability range around the target
	 * bits per group that is allowed by short term RC.
	 * PPS43[7:4]- Upper end of the variability range around the target
	 * bits per group that i allowed by short term rc.
	 */
    u8 rc_tgt_offset;
    /**
	 * @rc_buf_thresh:
	 * PPS44[7:0] - PPS57[7:0] - Specifies the thresholds in RC model for
	 * the 15 ranges defined by 14 thresholds.
	 */
    u8 rc_buf_thresh[DSC_NUM_BUF_RANGES - 1];
    /**
	 * @rc_range_parameters:
	 * PPS58[7:0] - PPS87[7:0]
	 * Parameters that correspond to each of the 15 ranges.
	 */
    __be16 rc_range_parameters[DSC_NUM_BUF_RANGES];
    /**
	 * @native_422_420:
	 * PPS88[0] - 0 = Native 4:2:2 not used
	 * 1 = Native 4:2:2 used
	 * PPS88[1] - 0 = Native 4:2:0 not use
	 * 1 = Native 4:2:0 used
	 * PPS88[7:2] - Reserved 6 bits
	 */
    u8 native_422_420;
    /**
	 * @second_line_bpg_offset:
	 * PPS89[4:0] - Additional bits/group budget for the
	 * second line of a slice in Native 4:2:0 mode.
	 * Set to 0 if DSC minor version is 1 or native420 is 0.
	 * PPS89[7:5] - Reserved
	 */
    u8 second_line_bpg_offset;
    /**
	 * @nsl_bpg_offset:
	 * PPS90[7:0], PPS91[7:0] - Number of bits that are deallocated
	 * for each group that is not in the second line of a slice.
	 */
    __be16 nsl_bpg_offset;
    /**
	 * @second_line_offset_adj:
	 * PPS92[7:0], PPS93[7:0] - Used as offset adjustment for the second
	 * line in Native 4:2:0 mode.
	 */
    __be16 second_line_offset_adj;
    /**
	 * @pps_long_94_reserved:
	 * PPS 94, 95, 96, 97 - Reserved
	 */
    u32 pps_long_94_reserved;
    /**
	 * @pps_long_98_reserved:
	 * PPS 98, 99, 100, 101 - Reserved
	 */
    u32 pps_long_98_reserved;
    /**
	 * @pps_long_102_reserved:
	 * PPS 102, 103, 104, 105 - Reserved
	 */
    u32 pps_long_102_reserved;
    /**
	 * @pps_long_106_reserved:
	 * PPS 106, 107, 108, 109 - reserved
	 */
    u32 pps_long_106_reserved;
    /**
	 * @pps_long_110_reserved:
	 * PPS 110, 111, 112, 113 - reserved
	 */
    u32 pps_long_110_reserved;
    /**
	 * @pps_long_114_reserved:
	 * PPS 114 - 117 - reserved
	 */
    u32 pps_long_114_reserved;
    /**
	 * @pps_long_118_reserved:
	 * PPS 118 - 121 - reserved
	 */
    u32 pps_long_118_reserved;
    /**
	 * @pps_long_122_reserved:
	 * PPS 122- 125 - reserved
	 */
    u32 pps_long_122_reserved;
    /**
	 * @pps_short_126_reserved:
	 * PPS 126, 127 - reserved
	 */
    __be16 pps_short_126_reserved;
} __attribute__((packed));

/* request ACK from peripheral */
#define MIPI_DSI_MSG_REQ_ACK BIT(0)
/* use Low Power Mode to transmit message */
#define MIPI_DSI_MSG_USE_LPM BIT(1)

/**
 * struct mipi_dsi_msg - read/write DSI buffer
 * @channel: virtual channel id
 * @type: payload data type
 * @flags: flags controlling this message transmission
 * @tx_len: length of @tx_buf
 * @tx_buf: data to be written
 * @rx_len: length of @rx_buf
 * @rx_buf: data to be read, or NULL
 */
struct mipi_dsi_msg {
    u8 channel;
    u8 type;
    u16 flags;

    size_t tx_len;
    const void *tx_buf;

    size_t rx_len;
    void *rx_buf;
};

bool mipi_dsi_packet_format_is_short(u8 type);
bool mipi_dsi_packet_format_is_long(u8 type);

/**
 * struct mipi_dsi_packet - represents a MIPI DSI packet in protocol format
 * @size: size (in bytes) of the packet
 * @header: the four bytes that make up the header (Data ID, Word Count or
 *     Packet Data, and ECC)
 * @payload_length: number of bytes in the payload
 * @payload: a pointer to a buffer containing the payload, if any
 */
struct mipi_dsi_packet {
    size_t size;
    u8 header[4];
    size_t payload_length;
    const u8 *payload;
};

int mipi_dsi_create_packet(struct mipi_dsi_packet *packet,
                           const struct mipi_dsi_msg *msg);
/**
 * struct mipi_dsi_host_ops - DSI bus operations
 * @attach: attach DSI device to DSI host
 * @detach: detach DSI device from DSI host
 * @transfer: transmit a DSI packet
 *
 * DSI packets transmitted by .transfer() are passed in as mipi_dsi_msg
 * structures. This structure contains information about the type of packet
 * being transmitted as well as the transmit and receive buffers. When an
 * error is encountered during transmission, this function will return a
 * negative error code. On success it shall return the number of bytes
 * transmitted for write packets or the number of bytes received for read
 * packets.
 *
 * Note that typically DSI packet transmission is atomic, so the .transfer()
 * function will seldomly return anything other than the number of bytes
 * contained in the transmit buffer on success.
 */
struct mipi_dsi_host_ops {
    int (*attach)(struct mipi_dsi_host *host,
                  const struct mipi_dsi_device *dsi);
    int (*detach)(struct mipi_dsi_host *host,
                  const struct mipi_dsi_device *dsi);
    size_t (*transfer)(struct mipi_dsi_host *host,
                       const struct mipi_dsi_msg *msg);
};

/**
 * struct mipi_dsi_host - DSI host device
 * @dev: driver model device node for this DSI host
 * @ops: DSI host operations
 * @list: list management
 */
struct mipi_dsi_host {
    //struct device *dev;
    const struct mipi_dsi_host_ops *ops;
    //struct list_head list;
};

/* DSI mode flags */

/* video mode */
#define MIPI_DSI_MODE_VIDEO BIT(0)
/* video burst mode */
#define MIPI_DSI_MODE_VIDEO_BURST BIT(1)
/* video pulse mode */
#define MIPI_DSI_MODE_VIDEO_SYNC_PULSE BIT(2)
/* enable auto vertical count mode */
#define MIPI_DSI_MODE_VIDEO_AUTO_VERT BIT(3)
/* enable hsync-end packets in vsync-pulse and v-porch area */
#define MIPI_DSI_MODE_VIDEO_HSE BIT(4)
/* disable hfront-porch area */
#define MIPI_DSI_MODE_VIDEO_HFP BIT(5)
/* disable hback-porch area */
#define MIPI_DSI_MODE_VIDEO_HBP BIT(6)
/* disable hsync-active area */
#define MIPI_DSI_MODE_VIDEO_HSA BIT(7)
/* flush display FIFO on vsync pulse */
#define MIPI_DSI_MODE_VSYNC_FLUSH BIT(8)
/* disable EoT packets in HS mode */
#define MIPI_DSI_MODE_EOT_PACKET BIT(9)
/* device supports non-continuous clock behavior (DSI spec 5.6.1) */
#define MIPI_DSI_CLOCK_NON_CONTINUOUS BIT(10)
/* transmit data in low power */
#define MIPI_DSI_MODE_LPM BIT(11)

enum mipi_dsi_pixel_format {
    MIPI_DSI_DATA_FMT_YUV422 = 0x2C, /*!< DSI data format:YUV 422 8bits */
    MIPI_DSI_DATA_FMT_RGB565 = 0x0E, /*!< DSI data format:RGB565 */
    MIPI_DSI_DATA_FMT_RGB666 = 0x2E, /*!< DSI data format:RGB666 */
    MIPI_DSI_DATA_FMT_RGB888 = 0x3E, /*!< DSI data format:RGB888 */
};

/**
 * struct mipi_dsi_device_info - template for creating a mipi_dsi_device
 * @type: DSI peripheral chip type
 * @channel: DSI virtual channel assigned to peripheral
 * @node: pointer to OF device node or NULL
 *
 * This is populated and passed to mipi_dsi_device_new to create a new
 * DSI device
 */
struct mipi_dsi_device_info {
    char type[DSI_DEV_NAME_SIZE];
    u32 channel;
    struct device_node *node;
};

/**
 * struct mipi_dsi_device - DSI peripheral device
 * @host: DSI host for this peripheral
 * @dev: driver model device node for this peripheral
 * @name: DSI peripheral chip type
 * @channel: virtual channel assigned to the peripheral
 * @format: pixel format for video mode
 * @lanes: number of active data lanes
 * @mode_flags: DSI operation mode related flags
 * @hs_rate: maximum lane frequency for high speed mode in hertz, this should
 * be set to the real limits of the hardware, zero is only accepted for
 * legacy drivers
 * @lp_rate: maximum lane frequency for low power mode in hertz, this should
 * be set to the real limits of the hardware, zero is only accepted for
 * legacy drivers
 */
typedef struct mipi_dsi_device {
    struct device dev;
    struct mipi_dsi_host *host;

    char name[DSI_DEV_NAME_SIZE];
    unsigned int channel;
    unsigned int lanes;
    enum mipi_dsi_pixel_format format;
    unsigned long mode_flags;
    unsigned long hs_rate;
    unsigned long lp_rate;
} mipi_dsi_device_t;

/**
 * enum mipi_dsi_dcs_tear_mode - Tearing Effect Output Line mode
 * @MIPI_DSI_DCS_TEAR_MODE_VBLANK: the TE output line consists of V-Blanking
 *    information only
 * @MIPI_DSI_DCS_TEAR_MODE_VHBLANK : the TE output line consists of both
 *    V-Blanking and H-Blanking information
 */
enum mipi_dsi_dcs_tear_mode {
    MIPI_DSI_DCS_TEAR_MODE_VBLANK,
    MIPI_DSI_DCS_TEAR_MODE_VHBLANK,
};

int mipi_dsi_controller_init(const struct mipi_dsi_device *dsi);
int mipi_dsi_shutdown_peripheral(const struct mipi_dsi_device *dsi);
int mipi_dsi_turn_on_peripheral(const struct mipi_dsi_device *dsi);
int mipi_dsi_set_maximum_return_packet_size(const struct mipi_dsi_device *dsi,
                                            u16 value);
int mipi_dsi_compression_mode(const struct mipi_dsi_device *dsi, bool enable);
int mipi_dsi_picture_parameter_set(const struct mipi_dsi_device *dsi,
                                      const struct drm_dsc_picture_parameter_set *pps);

int mipi_dsi_generic_write(const struct mipi_dsi_device *dsi, const void *payload,
                              size_t size);
int mipi_dsi_generic_read(const struct mipi_dsi_device *dsi, const void *params,
                             size_t num_params, void *data, size_t size);
int mipi_dsi_dcs_write_buffer(const struct mipi_dsi_device *dsi,
                                 const void *data, size_t len);
int mipi_dsi_dcs_write(const struct mipi_dsi_device *dsi, u8 cmd,
                          const void *data, size_t len);
int mipi_dsi_dcs_read(const struct mipi_dsi_device *dsi, u8 cmd, void *data,
                         size_t len);
int mipi_dsi_dcs_nop(const struct mipi_dsi_device *dsi);
int mipi_dsi_dcs_soft_reset(const struct mipi_dsi_device *dsi);
int mipi_dsi_dcs_get_power_mode(const struct mipi_dsi_device *dsi, u8 *mode);
int mipi_dsi_dcs_get_pixel_format(const struct mipi_dsi_device *dsi, u8 *format);
int mipi_dsi_dcs_enter_sleep_mode(const struct mipi_dsi_device *dsi);
int mipi_dsi_dcs_exit_sleep_mode(const struct mipi_dsi_device *dsi);
int mipi_dsi_dcs_set_display_off(const struct mipi_dsi_device *dsi);
int mipi_dsi_dcs_set_display_on(const struct mipi_dsi_device *dsi);
int mipi_dsi_dcs_set_column_address(const struct mipi_dsi_device *dsi, u16 start,
                                    u16 end);
int mipi_dsi_dcs_set_page_address(const struct mipi_dsi_device *dsi, u16 start,
                                  u16 end);
int mipi_dsi_dcs_set_tear_off(const struct mipi_dsi_device *dsi);
int mipi_dsi_dcs_set_tear_on(const struct mipi_dsi_device *dsi,
                             enum mipi_dsi_dcs_tear_mode mode);
int mipi_dsi_dcs_set_pixel_format(const struct mipi_dsi_device *dsi, u8 format);
int mipi_dsi_dcs_set_tear_scanline(const struct mipi_dsi_device *dsi, u16 scanline);
int mipi_dsi_dcs_set_display_brightness(const struct mipi_dsi_device *dsi,
                                        u16 brightness);
int mipi_dsi_dcs_get_display_brightness(const struct mipi_dsi_device *dsi,
                                        u16 *brightness);

#endif