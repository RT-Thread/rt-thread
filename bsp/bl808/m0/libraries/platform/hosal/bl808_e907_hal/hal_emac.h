/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __HAL_EMAC_H__
#define __HAL_EMAC_H__

#include "hal_common.h"
#include "drv_device.h"
// #include "bl808_config.h"
#include "bl808_emac.h"

#define CTX_TYPE 1

#define MSG(a,...)              printf(a,##__VA_ARGS__)
// #define MSG_DBG(a,...)          printf(a,##__VA_ARGS__)
// #define MSG_WAR(a,...)          printf(a,##__VA_ARGS__)
// #define MSG_ERR(a,...)          printf(a,##__VA_ARGS__)
#define BL_CASE_FAIL            {MSG(" Case Fail\r\n");while(1){}}
#define BL_CASE_SUCCESS         {MSG(" Case Success\r\n");while(1){}}

typedef struct emac_device {
    struct device parent;
    uint8_t mac_addr[6]; /*!< mac address */
} emac_device_t;

/**
 *  @brief EMAC PHY configuration type definition
 */
typedef struct
{
    uint8_t auto_negotiation; /*!< Speed and mode auto negotiation */
    uint8_t full_duplex;      /*!< Duplex mode */
#define PHY_STATE_DOWN    (0) /* PHY is not usable */
#define PHY_STATE_READY   (1) /* PHY is OK, wait for controller */
#define PHY_STATE_UP      (2) /* Network is ready for TX/RX */
#define PHY_STATE_RUNNING (3) /* working */
#define PHY_STATE_NOLINK  (4) /* no cable connected */
#define PHY_STATE_STOPPED (5) /* PHY has been stopped */
#define PHY_STATE_TESTING (6) /* in test mode */
    uint8_t phy_state;        /*!< down,ready,up,running,nolink,halted */
    uint8_t use_irq;          /*!< 0: no IRQ used */
    uint16_t speed;           /*!< Speed mode */
    uint16_t phy_address;     /*!< PHY address */
    uint32_t phy_id;          /*!< PHY OUI */
} emac_phy_cfg_t;

#define EMAC_NORMAL_PACKET    (uint32_t)(0)
#define EMAC_FRAGMENT_PACKET  (uint32_t)(0x01)
#define EMAC_NOCOPY_PACKET    (uint32_t)(0x02)

#ifndef ETH_TX_BUFFER_SIZE
#define ETH_TX_BUFFER_SIZE (ETH_MAX_PACKET_SIZE)
#endif

#ifndef ETH_RX_BUFFER_SIZE
#define ETH_RX_BUFFER_SIZE (ETH_MAX_PACKET_SIZE)
#endif

#define EMAC_TX_COMMON_FLAGS (EMAC_BD_FIELD_MSK(TX_RD) |  \
                              EMAC_BD_FIELD_MSK(TX_IRQ) | \
                              EMAC_BD_FIELD_MSK(TX_PAD) | \
                              EMAC_BD_FIELD_MSK(TX_CRC) | \
                              EMAC_BD_FIELD_MSK(TX_EOF))

#define EMAC_RX_COMMON_FLAGS    (ETH_MAX_PACKET_SIZE << 16) | \
    EMAC_BD_FIELD_MSK(RX_IRQ) )

typedef enum _BD_TYPE_ {
    EMAC_BD_TYPE_INVLAID,
    EMAC_BD_TYPE_TX,
    EMAC_BD_TYPE_RX,
    EMAC_BD_TYPE_NONE,
    EMAC_BD_TYPE_MAX = 0x7FFFFFFF
} EMAC_BD_TYPE_e;

int emac_init(emac_device_t *emac_cfg);
int emac_bd_init(uint8_t *ethTxBuff, uint8_t txBufCount, uint8_t *ethRxBuff, uint8_t rxBufCount);
int emac_bd_fragment_support(void);
int emac_bd_tx_enqueue(uint32_t flags, uint32_t len, const uint8_t *data_in);
int emac_bd_rx_dequeue(uint32_t flags, uint32_t *len, uint8_t *data_out);
__WEAK void emac_rx_done_callback_app(void);
__WEAK void emac_rx_error_callback_app(void);
__WEAK void emac_rx_busy_callback_app(void);
__WEAK void emac_tx_error_callback_app(void);
__WEAK void emac_tx_done_callback_app(void);
int emac_phy_set_address(uint16_t phyAddress);
int emac_phy_config_full_duplex(uint8_t fullDuplex);
int emac_phy_reg_read(uint16_t phyReg, uint16_t *regValue);
int emac_phy_reg_write(uint16_t phyReg, uint16_t regValue);
int emac_stop(void);
int emac_start(void);
int emac_start_tx(void);
int emac_stop_tx(void);
int emac_start_rx(void);
int emac_stop_rx(void);
int emac_intmask(EMAC_INT_Type intType, BL_Mask_Type intMask);
int emac_get_fram_len(uint16_t *max, uint16_t *min);
BL_Err_Type EMAC_GetFramLen(EMAC_ID_Type emacId, uint16_t * max, uint16_t *min);
BL_Err_Type EMAC_GetBD(EMAC_ID_Type emacId, uint32_t *bd);
#endif
