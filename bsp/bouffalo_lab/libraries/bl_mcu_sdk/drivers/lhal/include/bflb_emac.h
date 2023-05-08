#ifndef _BFLB_EMAC_H
#define _BFLB_EMAC_H

#include "bflb_core.h"

/** @addtogroup LHAL
  * @{
  */

/** @addtogroup EMAC
  * @{
  */

#define EMAC_DO_FLUSH_DATA (1)

/* EMAC clock use external or use internal; 0: used external 1: used internal */
#define EMAC_CLK_USE_EXTERNAL (0)
#define EMAC_CLK_USE_INTERNAL (1)

/** @defgroup EMAC_CMD emac feature control cmd definition
  * @{
  */
#define EMAC_CMD_NO_PREAMBLE_MODE (0x01)
#define EMAC_CMD_EN_PROMISCUOUS   (0x02)
#define EMAC_CMD_FRAME_GAP_CHECK  (0x03)
#define EMAC_CMD_FULL_DUPLEX      (0x04)
#define EMAC_CMD_EN_TX_CRC_FIELD  (0x05)
#define EMAC_CMD_RECV_HUGE_FRAMES (0x06)
#define EMAC_CMD_EN_AUTO_PADDING  (0x07)
#define EMAC_CMD_RECV_SMALL_FRAME (0x08)
#define EMAC_CMD_SET_PHY_ADDRESS  (0x09)
#define EMAC_CMD_SET_MAC_ADDRESS  (0x0A)
#define EMAC_CMD_SET_PACKET_GAP   (0x0B)
#define EMAC_CMD_SET_MIN_FRAME    (0x0C)
#define EMAC_CMD_SET_MAX_FRAME    (0x0D)
#define EMAC_CMD_SET_MAXRET       (0x0E)
#define EMAC_CMD_SET_COLLVALID    (0x0F)
/**
  * @}
  */

/** @defgroup PHY_STATE phy state definition
  * @{
  */
#define PHY_STATE_DOWN    (0) /* PHY is not usable */
#define PHY_STATE_READY   (1) /* PHY is OK, wait for controller */
#define PHY_STATE_UP      (2) /* Network is ready for TX/RX */
#define PHY_STATE_RUNNING (3) /* working */
#define PHY_STATE_NOLINK  (4) /* no cable connected */
#define PHY_STATE_STOPPED (5) /* PHY has been stopped */
#define PHY_STATE_TESTING (6) /* in test mode */
/**
  * @}
  */

/* EMAC PACKET */
#define EMAC_NORMAL_PACKET   (uint32_t)(0)
#define EMAC_FRAGMENT_PACKET (uint32_t)(0x01)
#define EMAC_NOCOPY_PACKET   (uint32_t)(0x02)

/* ETH packet size */
/* ETH     | Header | Extra | VLAN tag | Payload   | CRC | */
/* Size    | 14     | 2     | 4        | 46 ~ 1500 | 4   | */
#define ETH_MAX_PACKET_SIZE          ((uint32_t)1524U) /*!< ETH_HEADER + ETH_EXTRA + ETH_VLAN_TAG + ETH_MAX_ETH_PAYLOAD + ETH_CRC */
#define ETH_HEADER_SZIE              ((uint32_t)14U)   /*!< 6 byte Dest addr, 6 byte Src addr, 2 byte length/type */
#define ETH_CRC_SIZE                 ((uint32_t)4U)    /*!< Ethernet CRC */
#define ETH_EXTRA_SIZE               ((uint32_t)2U)    /*!< Extra bytes in some cases */
#define ETH_VLAN_TAG_SIZE            ((uint32_t)4U)    /*!< optional 802.1q VLAN Tag */
#define ETH_MIN_ETH_PAYLOAD_SIZE     ((uint32_t)46U)   /*!< Minimum Ethernet payload size */
#define ETH_MAX_ETH_PAYLOAD_SIZE     ((uint32_t)1500U) /*!< Maximum Ethernet payload size */
#define ETH_JUMBO_FRAME_PAYLOAD_SIZE ((uint32_t)9000U) /*!< Jumbo frame payload size */

/* ETH tx & rx buffer size */
#ifndef ETH_TX_BUFFER_SIZE
#define ETH_TX_BUFFER_SIZE (ETH_MAX_PACKET_SIZE)
#endif
#ifndef ETH_RX_BUFFER_SIZE
#define ETH_RX_BUFFER_SIZE (ETH_MAX_PACKET_SIZE)
#endif

/* emac interrupt UNMASK/MASK define */
#define EMAC_INT_EN_TX_DONE  (1 << 0)
#define EMAC_INT_EN_TX_ERROR (1 << 1)
#define EMAC_INT_EN_RX_DONE  (1 << 2)
#define EMAC_INT_EN_RX_ERROR (1 << 3)
#define EMAC_INT_EN_RX_BUSY  (1 << 4)
#define EMAC_INT_EN_TX_CTRL  (1 << 5)
#define EMAC_INT_EN_RX_CTRL  (1 << 6)
#define EMAC_INT_EN_ALL      (0x7f << 0)

/* emac interrupt status define */
#define EMAC_INT_STS_TX_DONE  (1 << 0)
#define EMAC_INT_STS_TX_ERROR (1 << 1)
#define EMAC_INT_STS_RX_DONE  (1 << 2)
#define EMAC_INT_STS_RX_ERROR (1 << 3)
#define EMAC_INT_STS_RX_BUSY  (1 << 4)
#define EMAC_INT_STS_TX_CTRL  (1 << 5)
#define EMAC_INT_STS_RX_CTRL  (1 << 6)
#define EMAC_INT_STS_ALL      (0x7f << 0)

/* emac buffer descriptors type define */
#define EMAC_BD_TYPE_INVLAID (0)
#define EMAC_BD_TYPE_TX      (1)
#define EMAC_BD_TYPE_RX      (2)
#define EMAC_BD_TYPE_NONE    (3)
#define EMAC_BD_TYPE_MAX     (0x7FFFFFFF)

/**
 * @brief EMAC configuration structure
 *
 * @param mac_addr  EMAC mac addr
 * @param inside_clk EMAC select inside or external @ref EMAC_CLK_USE_EXTERNAL or EMAC_CLK_USE_INTERNAL
 * @param mii_clk_div mii clock div
 * @param min_frame_len min frame len
 * @param max_frame_len max frame len
 *
 */
struct bflb_emac_config_s {
    uint8_t mac_addr[6];
    uint8_t inside_clk;
    uint8_t mii_clk_div;
    uint16_t min_frame_len;
    uint16_t max_frame_len;
};

/**
 * @brief EMAC phy configuration structure
 *
 * @param auto_negotiation EMAC phy speed and mode auto negotiation
 * @param full_duplex      EMAC phy duplex mode
 * @param phy_state        EMAC phy down,ready,up,running,nolink,halted, @ref PHY_STATE
 * @param use_irq          EMAC phy interrupt enable 0: no IRQ used
 * @param speed            EMAC phy speed mode
 * @param phy_address      EMAC phy address
 * @param phy_id           EMAC phy read phy id
 */
struct bflb_emac_phy_cfg_s {
    uint8_t auto_negotiation;
    uint8_t full_duplex;
    uint8_t phy_state;
    uint8_t use_irq;
    uint16_t speed;
    uint16_t phy_address;
    uint32_t phy_id;
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief
 *
 * @param [in] dev
 * @param [in] config
 */
void bflb_emac_init(struct bflb_device_s *dev, const struct bflb_emac_config_s *config);

/**
 * @brief
 *
 * @param [in] dev
 */
void bflb_emac_stop(struct bflb_device_s *dev);

/**
 * @brief
 *
 * @param [in] dev
 */
void bflb_emac_start(struct bflb_device_s *dev);

/**
 * @brief
 *
 * @param [in] dev
 */
void bflb_emac_start_tx(struct bflb_device_s *dev);

/**
 * @brief
 *
 * @param [in] dev
 */
void bflb_emac_stop_tx(struct bflb_device_s *dev);

/**
 * @brief
 *
 * @param [in] dev
 */
void bflb_emac_start_rx(struct bflb_device_s *dev);

/**
 * @brief
 *
 * @param [in] dev
 */
void bflb_emac_stop_rx(struct bflb_device_s *dev);

/**
 * @brief
 *
 * @param [in] dev
 * @param [in] eth_tx_buff
 * @param [in] tx_buf_count
 * @param [in] eth_rx_buff
 * @param [in] rx_buf_count
 */
void bflb_emac_bd_init(struct bflb_device_s *dev, uint8_t *eth_tx_buff, uint8_t tx_buf_count, uint8_t *eth_rx_buff, uint8_t rx_buf_count);

/**
 * @brief
 *
 * @param [in] dev
 * @param [in] bdt
 * @return uint32_t
 */
uint32_t bflb_emac_bd_get_cur_active(struct bflb_device_s *dev, uint8_t bdt);

/**
 * @brief
 *
 * @param [in] index
 */
void bflb_emac_bd_rx_enqueue(uint32_t index);

/**
 * @brief
 *
 * @param [in] index
 */
void bflb_emac_bd_rx_on_err(uint32_t index);

/**
 * @brief
 *
 * @param [in] index
 */
void bflb_emac_bd_tx_dequeue(uint32_t index);

/**
 * @brief
 *
 * @param [in] index
 */
void bflb_emac_bd_tx_on_err(uint32_t index);

/**
 * @brief
 *
 * @param [in] flags
 * @param [in] len
 * @param [in] data_in
 * @return int
 */
int bflb_emac_bd_tx_enqueue(uint32_t flags, uint32_t len, const uint8_t *data_in);

/**
 * @brief
 *
 * @param [in] flags
 * @param [in] len
 * @param [in] data_out
 * @return int
 */
int bflb_emac_bd_rx_dequeue(uint32_t flags, uint32_t *len, uint8_t *data_out);

/**
 * @brief
 *
 * @return int
 */
int emac_bd_fragment_support(void);

/**
 * @brief
 *
 * @param [in] dev
 * @param [in] flag
 * @param [in] enable
 */
void bflb_emac_int_enable(struct bflb_device_s *dev, uint32_t flag, bool enable);

/**
 * @brief
 *
 * @param [in] dev
 * @param [in] flag
 */
void bflb_emac_int_clear(struct bflb_device_s *dev, uint32_t flag);

/**
 * @brief
 *
 * @param [in] dev
 * @return uint32_t
 */
uint32_t bflb_emac_get_int_status(struct bflb_device_s *dev);

/**
 * @brief
 *
 * @param [in] dev
 * @param [in] cmd
 * @param [in] arg
 * @return int
 */
int bflb_emac_feature_control(struct bflb_device_s *dev, int cmd, size_t arg);

/**
 * @brief
 *
 * @param [in] dev
 * @param [in] phy_reg
 * @param [in] phy_reg_val
 * @return int
 */
int bflb_emac_phy_reg_read(struct bflb_device_s *dev, uint16_t phy_reg, uint16_t *phy_reg_val);

/**
 * @brief
 *
 * @param [in] dev
 * @param [in] phy_reg
 * @param [in] phy_reg_val
 * @return int
 */
int bflb_emac_phy_reg_write(struct bflb_device_s *dev, uint16_t phy_reg, uint16_t phy_reg_val);

#ifdef __cplusplus
}
#endif

/**
  * @}
  */

/**
  * @}
  */

#endif