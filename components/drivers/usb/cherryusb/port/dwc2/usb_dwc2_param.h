/*
 * Copyright (c) 2025, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __USB_DWC2_PARAM_H__
#define __USB_DWC2_PARAM_H__

/* Maximum number of Endpoints/HostChannels */
#define MAX_EPS_CHANNELS 16

#define HSOTG_REG(x) (x)

#define dwc2_readl(addr) \
    (*(volatile uint32_t *)(addr))

#define GUID_OFFSET HSOTG_REG(0x003C)

#define GSNPSID_OFFSET  HSOTG_REG(0x0040)
#define GSNPSID_ID_MASK (0xFFFF0000UL)

#define GHWCFG1_OFFSET HSOTG_REG(0x0044)

#define GHWCFG2_OFFSET                        HSOTG_REG(0x0048)
#define GHWCFG2_OTG_ENABLE_IC_USB             (0x01UL << 31U)
#define GHWCFG2_DEV_TOKEN_Q_DEPTH_MASK        (0x1FUL << 26U)
#define GHWCFG2_DEV_TOKEN_Q_DEPTH_SHIFT       (26U)
#define GHWCFG2_HOST_PERIO_TX_Q_DEPTH_MASK    (0x03UL << 24U)
#define GHWCFG2_HOST_PERIO_TX_Q_DEPTH_SHIFT   (24U)
#define GHWCFG2_NONPERIO_TX_Q_DEPTH_MASK      (0x03UL << 22U)
#define GHWCFG2_NONPERIO_TX_Q_DEPTH_SHIFT     (22U)
#define GHWCFG2_MULTI_PROC_INT                (0x01UL << 20U)
#define GHWCFG2_DYNAMIC_FIFO                  (0x01UL << 19U)
#define GHWCFG2_PERIO_EP_SUPPORTED            (0x01UL << 18U)
#define GHWCFG2_NUM_HOST_CHAN_MASK            (0x0FUL << 14U)
#define GHWCFG2_NUM_HOST_CHAN_SHIFT           (14U)
#define GHWCFG2_NUM_DEV_EP_MASK               (0x0FUL << 10U)
#define GHWCFG2_NUM_DEV_EP_SHIFT              (10U)
#define GHWCFG2_FS_PHY_TYPE_MASK              (0x03UL << 8U)
#define GHWCFG2_FS_PHY_TYPE_SHIFT             (8U)
#define GHWCFG2_FS_PHY_TYPE_NOT_SUPPORTED     (0x00UL)
#define GHWCFG2_FS_PHY_TYPE_DEDICATED         (0x01UL)
#define GHWCFG2_FS_PHY_TYPE_SHARED_UTMI       (0x02UL)
#define GHWCFG2_FS_PHY_TYPE_SHARED_ULPI       (0x03UL)
#define GHWCFG2_HS_PHY_TYPE_MASK              (0x03UL << 6U)
#define GHWCFG2_HS_PHY_TYPE_SHIFT             (6U)
#define GHWCFG2_HS_PHY_TYPE_NOT_SUPPORTED     (0x00UL)
#define GHWCFG2_HS_PHY_TYPE_UTMI              (0x01UL)
#define GHWCFG2_HS_PHY_TYPE_ULPI              (0x02UL)
#define GHWCFG2_HS_PHY_TYPE_UTMI_ULPI         (0x03UL)
#define GHWCFG2_POINT2POINT                   (0x01UL << 5U)
#define GHWCFG2_ARCHITECTURE_MASK             (0x03UL << 3U)
#define GHWCFG2_ARCHITECTURE_SHIFT            (3U)
#define GHWCFG2_SLAVE_ONLY_ARCH               (0x00UL)
#define GHWCFG2_EXT_DMA_ARCH                  (0x01UL)
#define GHWCFG2_INT_DMA_ARCH                  (0x02UL)
#define GHWCFG2_OP_MODE_MASK                  (0x07UL << 0U)
#define GHWCFG2_OP_MODE_SHIFT                 (0U)
#define GHWCFG2_OP_MODE_HNP_SRP_CAPABLE       (0x00UL)
#define GHWCFG2_OP_MODE_SRP_ONLY_CAPABLE      (0x01UL)
#define GHWCFG2_OP_MODE_NO_HNP_SRP_CAPABLE    (0x02UL)
#define GHWCFG2_OP_MODE_SRP_CAPABLE_DEVICE    (0x03UL)
#define GHWCFG2_OP_MODE_NO_SRP_CAPABLE_DEVICE (0x04UL)
#define GHWCFG2_OP_MODE_SRP_CAPABLE_HOST      (0x05UL)
#define GHWCFG2_OP_MODE_NO_SRP_CAPABLE_HOST   (0x06UL)
#define GHWCFG2_OP_MODE_UNDEFINED             (0x07UL)

#define GHWCFG3_OFFSET                       HSOTG_REG(0x004C)
#define GHWCFG3_DFIFO_DEPTH_MASK             (0xFFFFUL << 16U)
#define GHWCFG3_DFIFO_DEPTH_SHIFT            (16U)
#define GHWCFG3_OTG_LPM_EN                   (0x0001UL << 15U)
#define GHWCFG3_BC_SUPPORT                   (0x0001UL << 14U)
#define GHWCFG3_OTG_ENABLE_HSIC              (0x0001UL << 13U)
#define GHWCFG3_ADP_SUPP                     (0x0001UL << 12U)
#define GHWCFG3_SYNCH_RESET_TYPE             (0x0001UL << 11U)
#define GHWCFG3_OPTIONAL_FEATURES            (0x0001UL << 10U)
#define GHWCFG3_VENDOR_CTRL_IF               (0x0001UL << 9U)
#define GHWCFG3_I2C                          (0x0001UL << 8U)
#define GHWCFG3_OTG_FUNC                     (0x0001UL << 7U)
#define GHWCFG3_PACKET_SIZE_CNTR_WIDTH_MASK  (0x0007UL << 4U)
#define GHWCFG3_PACKET_SIZE_CNTR_WIDTH_SHIFT (4U)
#define GHWCFG3_XFER_SIZE_CNTR_WIDTH_MASK    (0x000FUL << 0U)
#define GHWCFG3_XFER_SIZE_CNTR_WIDTH_SHIFT   (0U)

#define GHWCFG4_OFFSET                      HSOTG_REG(0x0050)
#define GHWCFG4_DESC_DMA_DYN                (0x1UL << 31U)
#define GHWCFG4_DESC_DMA                    (0x1UL << 30U)
#define GHWCFG4_NUM_IN_EPS_MASK             (0xFUL << 26U)
#define GHWCFG4_NUM_IN_EPS_SHIFT            (26U)
#define GHWCFG4_DED_FIFO_EN                 (0x1UL << 25U)
#define GHWCFG4_DED_FIFO_SHIFT              (25U)
#define GHWCFG4_SESSION_END_FILT_EN         (0x1UL << 24U)
#define GHWCFG4_B_VALID_FILT_EN             (0x1UL << 23U)
#define GHWCFG4_A_VALID_FILT_EN             (0x1UL << 22U)
#define GHWCFG4_VBUS_VALID_FILT_EN          (0x1UL << 21U)
#define GHWCFG4_IDDIG_FILT_EN               (0x1UL << 20U)
#define GHWCFG4_NUM_DEV_MODE_CTRL_EP_MASK   (0xFUL << 16U)
#define GHWCFG4_NUM_DEV_MODE_CTRL_EP_SHIFT  (16U)
#define GHWCFG4_UTMI_PHY_DATA_WIDTH_MASK    (0x3UL << 14U)
#define GHWCFG4_UTMI_PHY_DATA_WIDTH_SHIFT   (14U)
#define GHWCFG4_UTMI_PHY_DATA_WIDTH_8       (0x0UL)
#define GHWCFG4_UTMI_PHY_DATA_WIDTH_16      (0x1UL)
#define GHWCFG4_UTMI_PHY_DATA_WIDTH_8_OR_16 (0x2UL)
#define GHWCFG4_ACG_SUPPORTED               (0x1UL << 12U)
#define GHWCFG4_IPG_ISOC_SUPPORTED          (0x1UL << 11U)
#define GHWCFG4_SERVICE_INTERVAL_SUPPORTED  (0x1UL << 10U)
#define GHWCFG4_XHIBER                      (0x1UL << 7U)
#define GHWCFG4_HIBER                       (0x1UL << 6U)
#define GHWCFG4_MIN_AHB_FREQ                (0x1UL << 5U)
#define GHWCFG4_POWER_OPTIMIZ               (0x1UL << 4U)
#define GHWCFG4_NUM_DEV_PERIO_IN_EP_MASK    (0xFUL << 0U)
#define GHWCFG4_NUM_DEV_PERIO_IN_EP_SHIFT   (0U)

/**
 * struct dwc2_hw_params - Autodetected parameters.
 *
 * These parameters are the various parameters read from hardware
 * registers during initialization. They typically contain the best
 * supported or maximum value that can be configured in the
 * corresponding dwc2_core_params value.
 *
 * The values that are not in dwc2_core_params are documented below.
 *
 * @snpsid:             Value from SNPSID register
 * @dev_ep_dirs:        Direction of device endpoints (GHWCFG1)
 *
 * @op_mode:             Mode of Operation
 *                       0 - HNP- and SRP-Capable OTG (Host & Device)
 *                       1 - SRP-Capable OTG (Host & Device)
 *                       2 - Non-HNP and Non-SRP Capable OTG (Host & Device)
 *                       3 - SRP-Capable Device
 *                       4 - Non-OTG Device
 *                       5 - SRP-Capable Host
 *                       6 - Non-OTG Host
 * @arch:                Architecture
 *                       0 - Slave only
 *                       1 - External DMA
 *                       2 - Internal DMA
 * @enable_dynamic_fifo: 0 - Use coreConsultant-specified FIFO size parameters
 *                       1 - Allow dynamic FIFO sizing (default, if available)
 * @host_channels:      The number of host channel registers to use
 *                       1 to 16
 * @hs_phy_type:         High-speed PHY interface type
 *                       0 - High-speed interface not supported
 *                       1 - UTMI+
 *                       2 - ULPI
 *                       3 - UTMI+ and ULPI
 * @fs_phy_type:         Full-speed PHY interface type
 *                       0 - Full speed interface not supported
 *                       1 - Dedicated full speed interface
 *                       2 - FS pins shared with UTMI+ pins
 *                       3 - FS pins shared with ULPI pins
 * @num_dev_ep:         Number of device endpoints available
 * @nperio_tx_q_depth:
 *                      Non-Periodic Request Queue Depth
 *                       2, 4 or 8
 * @dev_token_q_depth:  Device Mode IN Token Sequence Learning Queue
 *                      Depth
 *                       0 to 30
 * @host_perio_tx_q_depth:
 *                      Host Mode Periodic Request Queue Depth
 *                       2, 4 or 8
 *
 * @max_transfer_size:  The maximum transfer size supported, in bytes
 *                       2047 to 65,535
 *                      Actual maximum value is autodetected and also
 *                      the default.
 * @max_packet_count:   The maximum number of packets in a transfer
 *                       15 to 511
 *                      Actual maximum value is autodetected and also
 *                      the default.
 * @i2c_enable:         Specifies whether to use the I2Cinterface for a full
 *                      speed PHY. This parameter is only applicable if phy_type
 *                      is FS.
 *                       0 - No (default)
 *                       1 - Yes
 * @total_fifo_size:    Total internal RAM for FIFOs (bytes)
 * @lpm_mode:		For enabling Link Power Management in the controller
 *                       0 - Disable
 *                       1 - Enable
 *
 * @en_multiple_tx_fifo: Specifies whether dedicated per-endpoint transmit FIFOs
 *                      are enabled for non-periodic IN endpoints in device
 *                      mode.
 * @num_dev_in_eps:     Number of device IN endpoints available
 * @num_dev_perio_in_ep: Number of device periodic IN endpoints
 *                       available
 * @dma_desc_enable:    When DMA mode is enabled, specifies whether to use
 *                      address DMA mode or descriptor DMA mode for accessing
 *                      the data FIFOs. The driver will automatically detect the
 *                      value for this if none is specified.
 *                       0 - Address DMA
 *                       1 - Descriptor DMA (default, if available)

 * @power_optimized:    Are power optimizations enabled?
 * @hibernation:	Is hibernation enabled?
 * @utmi_phy_data_width: UTMI+ PHY data width
 *                       0 - 8 bits
 *                       1 - 16 bits
 *                       2 - 8 or 16 bits

 * @acg_enable:		For enabling Active Clock Gating in the controller
 *                       0 - Disable
 *                       1 - Enable
 * @ipg_isoc_en:        This feature indicates that the controller supports
 *                      the worst-case scenario of Rx followed by Rx
 *                      Interpacket Gap (IPG) (32 bitTimes) as per the utmi
 *                      specification for any token following ISOC OUT token.
 *                       0 - Don't support
 *                       1 - Support
 * @service_interval_mode: For enabling service interval based scheduling in the
 *                         controller.
 *                           0 - Disable
 *                           1 - Enable
 */
struct dwc2_hw_params {
    uint32_t snpsid;
    uint32_t dev_ep_dirs;

    unsigned op_mode                  : 3;
    unsigned arch                     : 2;
    unsigned enable_dynamic_fifo      : 1;
    unsigned host_channels            : 5;
    unsigned hs_phy_type              : 2;
    unsigned fs_phy_type              : 2;
    unsigned num_dev_ep               : 4;
    unsigned nperio_tx_q_depth        : 3;
    unsigned host_perio_tx_q_depth    : 3;
    unsigned dev_token_q_depth        : 5;

    unsigned max_transfer_size        : 26;
    unsigned max_packet_count         : 11;
    unsigned i2c_enable               : 1;
    unsigned total_fifo_size          : 16;
    unsigned lpm_mode                 : 1;

    unsigned en_multiple_tx_fifo      : 1;
    unsigned num_dev_in_eps           : 4;
    unsigned num_dev_perio_in_ep      : 4;
    unsigned dma_desc_enable          : 1;
    unsigned power_optimized          : 1;
    unsigned hibernation              : 1;
    unsigned utmi_phy_data_width      : 2;
    unsigned acg_enable               : 1;
    unsigned ipg_isoc_en              : 1;
    unsigned service_interval_mode    : 1;
};

#define DWC2_PHY_TYPE_PARAM_FS		0
#define DWC2_PHY_TYPE_PARAM_UTMI	1
#define DWC2_PHY_TYPE_PARAM_ULPI	2

struct dwc2_user_params {
	uint8_t phy_type;
    uint8_t phy_utmi_width;

    bool device_dma_enable;
    bool device_dma_desc_enable;
    /* (5 * number of control endpoints + 8) + ((largest USB packet used / 4) + 1 for
    * status information) + (2 * number of OUT endpoints) + 1 for Global NAK
    */
    uint16_t device_rx_fifo_size;
    /* IN Endpoints Max packet Size / 4 */
	uint16_t device_tx_fifo_size[MAX_EPS_CHANNELS];

    bool host_dma_desc_enable;
    /*
    * (largest USB packet used / 4) + 1 for status information + 1 transfer complete +
    * 1 location each for Bulk/Control endpoint for handling NAK/NYET scenario
    */
	uint16_t host_rx_fifo_size;
    /* largest non-periodic USB packet used / 4 */
	uint16_t host_nperio_tx_fifo_size;
    /* largest periodic USB packet used / 4 */
	uint16_t host_perio_tx_fifo_size;

    uint32_t device_gccfg;
    uint32_t host_gccfg;

    bool b_session_valid_override;
    uint32_t total_fifo_size;
};

struct usb_dwc2_user_fifo_config {
     /* (5 * number of control endpoints + 8) + ((largest USB packet used / 4) + 1 for
    * status information) + (2 * number of OUT endpoints) + 1 for Global NAK
    */
    uint16_t device_rx_fifo_size;
    /* IN Endpoints Max packet Size / 4 */
    uint16_t device_tx_fifo_size[MAX_EPS_CHANNELS];
};

static inline void dwc2_get_hwparams(uint32_t reg_base, struct dwc2_hw_params *hw)
{
    unsigned int width;
    uint32_t snpsid, hwcfg1, hwcfg2, hwcfg3, hwcfg4;

    snpsid = dwc2_readl(reg_base + GSNPSID_OFFSET);

    hwcfg1 = dwc2_readl(reg_base + GHWCFG1_OFFSET);
    hwcfg2 = dwc2_readl(reg_base + GHWCFG2_OFFSET);
    hwcfg3 = dwc2_readl(reg_base + GHWCFG3_OFFSET);
    hwcfg4 = dwc2_readl(reg_base + GHWCFG4_OFFSET);

    /* snpsid */
    hw->snpsid = snpsid;

    /* hwcfg1 */
    hw->dev_ep_dirs = hwcfg1;

    /* hwcfg2 */
    hw->op_mode = (hwcfg2 & GHWCFG2_OP_MODE_MASK) >>
                  GHWCFG2_OP_MODE_SHIFT;
    hw->arch = (hwcfg2 & GHWCFG2_ARCHITECTURE_MASK) >>
               GHWCFG2_ARCHITECTURE_SHIFT;
    hw->enable_dynamic_fifo = !!(hwcfg2 & GHWCFG2_DYNAMIC_FIFO);
    hw->host_channels = 1 + ((hwcfg2 & GHWCFG2_NUM_HOST_CHAN_MASK) >>
                             GHWCFG2_NUM_HOST_CHAN_SHIFT);
    hw->hs_phy_type = (hwcfg2 & GHWCFG2_HS_PHY_TYPE_MASK) >>
                      GHWCFG2_HS_PHY_TYPE_SHIFT;
    hw->fs_phy_type = (hwcfg2 & GHWCFG2_FS_PHY_TYPE_MASK) >>
                      GHWCFG2_FS_PHY_TYPE_SHIFT;
    hw->num_dev_ep = (hwcfg2 & GHWCFG2_NUM_DEV_EP_MASK) >>
                     GHWCFG2_NUM_DEV_EP_SHIFT;
    hw->nperio_tx_q_depth =
        (hwcfg2 & GHWCFG2_NONPERIO_TX_Q_DEPTH_MASK) >>
        GHWCFG2_NONPERIO_TX_Q_DEPTH_SHIFT << 1;
    hw->host_perio_tx_q_depth =
        (hwcfg2 & GHWCFG2_HOST_PERIO_TX_Q_DEPTH_MASK) >>
        GHWCFG2_HOST_PERIO_TX_Q_DEPTH_SHIFT << 1;
    hw->dev_token_q_depth =
        (hwcfg2 & GHWCFG2_DEV_TOKEN_Q_DEPTH_MASK) >>
        GHWCFG2_DEV_TOKEN_Q_DEPTH_SHIFT;

    /* hwcfg3 */
    width = (hwcfg3 & GHWCFG3_XFER_SIZE_CNTR_WIDTH_MASK) >>
            GHWCFG3_XFER_SIZE_CNTR_WIDTH_SHIFT;
    hw->max_transfer_size = (1 << (width + 11)) - 1;
    width = (hwcfg3 & GHWCFG3_PACKET_SIZE_CNTR_WIDTH_MASK) >>
            GHWCFG3_PACKET_SIZE_CNTR_WIDTH_SHIFT;
    hw->max_packet_count = (1 << (width + 4)) - 1;
    hw->i2c_enable = !!(hwcfg3 & GHWCFG3_I2C);
    hw->total_fifo_size = (hwcfg3 & GHWCFG3_DFIFO_DEPTH_MASK) >>
                          GHWCFG3_DFIFO_DEPTH_SHIFT;
    hw->lpm_mode = !!(hwcfg3 & GHWCFG3_OTG_LPM_EN);

    /* hwcfg4 */
    hw->en_multiple_tx_fifo = !!(hwcfg4 & GHWCFG4_DED_FIFO_EN);
    hw->num_dev_perio_in_ep = (hwcfg4 & GHWCFG4_NUM_DEV_PERIO_IN_EP_MASK) >>
                              GHWCFG4_NUM_DEV_PERIO_IN_EP_SHIFT;
    hw->num_dev_in_eps = (hwcfg4 & GHWCFG4_NUM_IN_EPS_MASK) >>
                         GHWCFG4_NUM_IN_EPS_SHIFT;
    hw->dma_desc_enable = !!(hwcfg4 & GHWCFG4_DESC_DMA);
    hw->power_optimized = !!(hwcfg4 & GHWCFG4_POWER_OPTIMIZ);
    hw->hibernation = !!(hwcfg4 & GHWCFG4_HIBER);
    hw->utmi_phy_data_width = (hwcfg4 & GHWCFG4_UTMI_PHY_DATA_WIDTH_MASK) >>
                              GHWCFG4_UTMI_PHY_DATA_WIDTH_SHIFT;
    hw->acg_enable = !!(hwcfg4 & GHWCFG4_ACG_SUPPORTED);
    hw->ipg_isoc_en = !!(hwcfg4 & GHWCFG4_IPG_ISOC_SUPPORTED);
    hw->service_interval_mode = !!(hwcfg4 &
                                   GHWCFG4_SERVICE_INTERVAL_SUPPORTED);
}

void dwc2_get_user_params(uint32_t reg_base, struct dwc2_user_params *params);
void dwc2_get_user_fifo_config(uint32_t reg_base, struct usb_dwc2_user_fifo_config *config);

#endif