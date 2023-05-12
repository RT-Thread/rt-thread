/**
 *********************************************************************************
 *
 * @file    ald_i2c.h
 * @brief   Header file of I2C driver
 *
 * @version V1.0
 * @date    24 Feb. 2023
 * @author  AE Team
 * @note
 *          Change Logs:
 *          Date            Author          Notes
 *          24 Feb. 2023    Lisq            The first version
 *
 * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 **********************************************************************************
 */

#ifndef __ALD_I2C_H__
#define __ALD_I2C_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <string.h>
#include "ald_cmu.h"
#include "ald_dma.h"

/** @addtogroup ES32VF2264_ALD
  * @{
  */

/** @addtogroup I2C
  * @{
  */

/** @defgroup I2C_Public_Types I2C Public Types
  * @{
  */
/**
  * @brief I2C Error Code
  */
typedef enum {
    ALD_I2C_ERROR_NONE    = 0x0U,   /**< No error */
    ALD_I2C_ERROR_BERR    = 0x1U,   /**< Berr error */
    ALD_I2C_ERROR_ARLO    = 0x2U,   /**< Arlo error */
    ALD_I2C_ERROR_RUD     = 0x4U,   /**< Rx underflow error */
    ALD_I2C_ERROR_AF      = 0x8U,   /**< Af error */
    ALD_I2C_ERROR_ROV     = 0x10U,  /**< Rx overflow error */
    ALD_I2C_ERROR_RF      = 0x20U,  /**< Rx full error */
    ALD_I2C_ERROR_TUD     = 0x40U,  /**< Tx underflow error */
    ALD_I2C_ERROR_TOV     = 0x80U,  /**< Tx overflow error */
    ALD_I2C_ERROR_TE      = 0x100U, /**< Tx empty error */
    ALD_I2C_ERROR_DMA     = 0x200U, /**< Dma error */
    ALD_I2C_ERROR_TIMEOUT = 0x400U, /**< Timeout error */
} ald_i2c_error_t;

/**
  * @brief I2C state structure definition
  */
typedef enum {
    ALD_I2C_STATE_RESET   = 0x0U,   /**< Peripheral is not yet Initialized */
    ALD_I2C_STATE_READY   = 0x20U,  /**< Peripheral Initialized and ready for use */
    ALD_I2C_STATE_BUSY    = 0x24U,  /**< An internal process is ongoing */
    ALD_I2C_STATE_BUSY_TX = 0x21U,  /**< Data Transmission process is ongoing */
    ALD_I2C_STATE_BUSY_RX = 0x22U,  /**< Data Reception process is ongoing */

    ALD_I2C_STATE_LISTEN          = 0x28U,  /**< Address Listen */
    ALD_I2C_STATE_BUSY_TX_LISTEN  = 0x29U,  /**< Address Listen and Data Transmission */
    ALD_I2C_STATE_BUSY_RX_LISTEN  = 0x2AU,  /**< Address Listen and Data Receive */

    ALD_I2C_STATE_ABORT   = 0x60U,  /**< Abort user request */
    ALD_I2C_STATE_TIMEOUT = 0xA0U,  /**< timeout state */
    ALD_I2C_STATE_ERROR   = 0xE0U,  /**< Error */
} ald_i2c_state_t;

/**
  * @brief I2C Addressing Mode
  */
typedef enum {
    ALD_I2C_ADDR_7BIT  = 0x0U,  /**< 7 bit address */
    ALD_I2C_ADDR_10BIT = 0x1U,  /**< 10 bit address */
} ald_i2c_addr_t;

/**
  * @brief I2C Dual Addressing Mode
  */
typedef enum {
    ALD_I2C_DUALADDR_DISABLE = 0x0U,    /**< dual address is disable */
    ALD_I2C_DUALADDR_ENABLE  = 0x1U,    /**< dual address is enable */
} ald_i2c_dual_addr_t;

/**
  * @brief I2C General Call Addressing mode
  */
typedef enum {
    ALD_I2C_GENERALCALL_DISABLE = 0x0U, /**< general call address is disable */
    ALD_I2C_GENERALCALL_ENABLE  = 0x1U, /**< general call address is enable */
} ald_i2c_general_addr_t;

/**
  * @brief I2C Nostretch Mode
  */
typedef enum {
    ALD_I2C_NOSTRETCH_DISABLE = 0x0U,   /**< Nostretch disable */
    ALD_I2C_NOSTRETCH_ENABLE  = 0x1U,   /**< Nostretch enable */
} ald_i2c_nostretch_t;

/**
  * @brief I2C Memory Address Size
  */
typedef enum {
    ALD_I2C_MEMADD_SIZE_8BIT  = 0x8U,   /**< 8 bit memory address size */
    ALD_I2C_MEMADD_SIZE_16BIT = 0x10U,  /**< 10 bit memory address size */
} ald_i2c_addr_size_t;

/**
  * @brief I2C mode structure definition
  */
typedef enum {
    ALD_I2C_MODE_NONE   = 0x0U,     /**< No I2C communication on going */
    ALD_I2C_MODE_MASTER = 0x10U,    /**< I2C communication is in Master mode */
    ALD_I2C_MODE_SLAVE  = 0x20U,    /**< I2C communication is in Slave mode */
    ALD_I2C_MODE_MEM    = 0x40U,    /**< I2C communication is in Memory mode */
} ald_i2c_mode_t;

/**
  * @brief I2C Clock
  */
typedef enum {
    ALD_I2C_STANDARD_MODE_MAX_CLK     = 100000U,    /**< Standard mode clock */
    ALD_I2C_FAST_MODE_MAX_CLK         = 400000U,    /**< Fast mode clock */
    ALD_I2C_EXTREME_FAST_MODE_MAX_CLK = 1000000U,   /**< Extreme mode clock */
} ald_i2c_clock_t;

/**
  * @brief I2C OAR2 Register
  */
typedef enum {
    ALD_I2C_OAR2_ENDUAL = (1U << 0), /**< ENDUAL BIT */
    ALD_I2C_OAR2_ADD2   = (1U << 1)  /**< ADD2 BIT */
} ald_i2c_oar2_t;

/**
  * @brief I2C CON1 Register
  */
typedef enum {
    ALD_I2C_CON1_PE        = (1U << 0),     /**< Peripheral enable BIT */
    ALD_I2C_CON1_TXDMA     = (1U << 14),    /**< Transmit DMA BIT */
    ALD_I2C_CON1_RXDMA     = (1U << 15),    /**< Receive DMA BIT */
    ALD_I2C_CON1_SBC       = (1U << 16),    /**< Receive DMA BIT */
    ALD_I2C_CON1_NOSTRETCH = (1U << 17),    /**< Slave bytes control BIT */
    ALD_I2C_CON1_GCEN      = (1U << 19),    /**< General call BIT */
    ALD_I2C_CON1_SMBHEN    = (1U << 20),    /**< SMBus slave device enable BIT */
    ALD_I2C_CON1_SMBDEN    = (1U << 21),    /**< SMBus master device enable BIT */
    ALD_I2C_CON1_ALERTEN   = (1U << 22),    /**< SMBus alert device enable BIT */
    ALD_I2C_CON1_PECEN     = (1U << 23),    /**< PEC enable BIT */
} ald_i2c_con1_t;

/**
  * @brief I2C CON2 Register
  */
typedef enum {
    ALD_I2C_CON2_RD_WRN    = (1U << 10),    /**< Master R/W control BIT */
    ALD_I2C_CON2_ADD10     = (1U << 11),    /**< 10bit address control BIT */
    ALD_I2C_CON2_HEAD10R   = (1U << 12),    /**< 10bit address master Receive control BIT */
    ALD_I2C_CON2_START     = (1U << 13),    /**< Master start singal control BIT */
    ALD_I2C_CON2_STOP      = (1U << 14),    /**< Master stop singal control BIT */
    ALD_I2C_CON2_NACK      = (1U << 15),    /**< Master Nack control BIT */
    ALD_I2C_CON2_RELOAD    = (1U << 24),    /**< Master communication reload control BIT */
    ALD_I2C_CON2_AUTOEND   = (1U << 25),    /**< Master Autoend control BIT */
    ALD_I2C_CON2_PECBYTE   = (1U << 26),    /**< PEC control BIT */
    ALD_I2C_CON2_HOLDACK   = (1U << 28),    /**< Hold ack control BIT */
} ald_i2c_con2_t;

/**
  * @brief I2C ADDR1 Register
  */
typedef enum {
    ALD_I2C_OA1MODE = (1U << 10),   /**< Addr1 bits choose BIT */
    ALD_I2C_OA1EN   = (1U << 15),   /**< Addr1 enable BIT */
} ald_i2c_addr1_t;

/**
  * @brief I2C ADDR2 Register
  */
typedef enum {
    ALD_I2C_OA2EN = (1U << 15),     /**< Addr2 enable BIT */
} ald_i2c_addr2_t;

/**
  * @brief I2C TIMEOUTR Register
  */
typedef enum {
    ALD_I2C_TIMEOUTR_TIDLE     = (1U << 12),    /**< SCL idle check enable BIT */
    ALD_I2C_TIMEOUTR_TIMEOUTEN = (1U << 15),    /**< Timeout enable BIT */
} ald_i2c_timoutr_t;

/**
  * @brief I2C peripherals module
  */
typedef enum {
    ALD_I2C_MODULE_MASTER = (1U << 0),  /**< Master module */
    ALD_I2C_MODULE_SLAVE  = (1U << 1)   /**< Slave module */
} ald_i2c_module_t;

/**
  * @brief I2C STAT Register
  */
typedef enum {
    ALD_I2C_STAT_TXE  = (1U << 0),  /**< Transmit empty flag */
    ALD_I2C_STAT_TXOV = (1U << 2),  /**< Transmit overrun flag */
    ALD_I2C_STAT_TXUD = (1U << 3),  /**< Transmit underrun flag */
    ALD_I2C_STAT_RXNE = (1U << 5),  /**< Receive not empty flag */
    ALD_I2C_STAT_RXOV = (1U << 7),  /**< Receive overrun flag */
    ALD_I2C_STAT_RXUD = (1U << 8),  /**< Receive underrun flag */
    ALD_I2C_STAT_TC   = (1U << 10), /**< Transmit completed flag */
    ALD_I2C_STAT_TCR  = (1U << 11), /**< Transmit and reload completed flag */
    ALD_I2C_STAT_BUSY = (1U << 15), /**< Bus status busy flag */
    ALD_I2C_STAT_DIR  = (1U << 16), /**< Slave R/W flag */
} ald_i2c_stat_t;

/**
  * @brief Interrupt Configuration Definition
  */
typedef enum {
    ALD_I2C_IT_TXE   = (1U << 0), /**< Transmit empty interrupt */
    ALD_I2C_IT_TXOV  = (1U << 2), /**< Transmit overrun interrupt */
    ALD_I2C_IT_TXUD  = (1U << 3), /**< Transmit underrun interrupt */
    ALD_I2C_IT_RXNE  = (1U << 5), /**< Receive not empty interrupt */
    ALD_I2C_IT_RXOV  = (1U << 7), /**< Receive overrun interrupt */
    ALD_I2C_IT_RXUD  = (1U << 8), /**< Receive underrun interrupt */
    ALD_I2C_IT_TC    = (1U << 10), /**< Transmit completed interrupt */
    ALD_I2C_IT_TCR   = (1U << 11), /**< Transmit and reload completed interrupt */
    ALD_I2C_IT_ADDR  = (1U << 12), /**< Address matching interrupt */
    ALD_I2C_IT_NACK  = (1U << 13), /**< NACK interrupt */
    ALD_I2C_IT_STOP  = (1U << 14), /**< Stop detection interrupt */
    ALD_I2C_IT_BERR  = (1U << 16), /**< Bus error interrupt */
    ALD_I2C_IT_ARLO  = (1U << 17), /**< Arbitration loss interrupt */
    ALD_I2C_IT_PECE  = (1U << 18), /**< PEC error interrupt */
    ALD_I2C_IT_TOUT  = (1U << 19), /**< Timeout interrupt */
    ALD_I2C_IT_ALERT = (1U << 20), /**< SMBus Alert interrupt */
} ald_i2c_interrupt_t;

/**
  * @brief I2C TRISE Register
  */
typedef enum {
    ALD_I2C_TRISE_TRISE = 0x3FU, /**< TRISE BITS */
} ald_i2c_trise_t;

/**
 * @brief I2C Configuration Structure definition
 */
typedef struct {
    ald_i2c_module_t module;        /**< Specifies the communication module */
    uint32_t clk_speed;     /**< Specifies the clock frequency */
    uint32_t own_addr1;     /**< Specifies the first device own address */
    ald_i2c_addr_t addr_mode;       /**< Specifies addressing mode */
    ald_i2c_dual_addr_t dual_addr;  /**< Specifies if dual addressing mode is selected */
    uint32_t own_addr2;     /**< Specifies the second device own address */
    ald_i2c_general_addr_t general_call;/**< Specifies if general call mode is selected */
    ald_i2c_nostretch_t no_stretch; /**< Specifies if nostretch mode is selected */
} ald_i2c_init_t;

/**
  * @brief  I2C handle Structure definition
  */
typedef struct ald_i2c_handle_s {
    I2C_TypeDef *perh;        /**< I2C registers base address */
    ald_i2c_init_t init;      /**< I2C communication parameters */
    uint8_t *p_buff;          /**< Pointer to I2C transfer buffer */
    uint16_t xfer_size;       /**< I2C transfer size */
    __IO uint16_t xfer_count; /**< I2C transfer counter */

    __IO uint32_t xfer_opt;   /**< I2C transfer options */
    __IO uint32_t pre_state;  /**< I2C previous communication state */

    ald_dma_handle_t hdmatx;      /**< I2C Tx DMA handle parameters */
    ald_dma_handle_t hdmarx;      /**< I2C Rx DMA handle parameters */

    lock_state_t lock;            /**< I2C locking object */
    __IO ald_i2c_state_t state;   /**< I2C communication state */
    __IO ald_i2c_mode_t mode;     /**< I2C communication mode */
    __IO uint32_t error_code;     /**< I2C Error code */

    void (*addr_cplt_cbk)(struct ald_i2c_handle_s *arg); /**< Call Slave Addr callback */
    void (*listen_cplt_cbk)(struct ald_i2c_handle_s *arg); /**< Listen callback */

    void (*master_tx_cplt_cbk)(struct ald_i2c_handle_s *arg); /**< Master Tx completed callback */
    void (*master_rx_cplt_cbk)(struct ald_i2c_handle_s *arg); /**< Master Rx completed callback */
    void (*slave_tx_cplt_cbk)(struct ald_i2c_handle_s *arg);  /**< Slave Tx completed callback */
    void (*slave_rx_cplt_cbk)(struct ald_i2c_handle_s *arg);  /**< Slave Rx completed callback */
    void (*mem_tx_cplt_cbk)(struct ald_i2c_handle_s *arg);    /**< Tx to Memory completed callback */
    void (*mem_rx_cplt_cbk)(struct ald_i2c_handle_s *arg);    /**< Rx from Memory completed callback */
    void (*error_callback)(struct ald_i2c_handle_s *arg);     /**< Error callback */
} ald_i2c_handle_t;

/**
 * @}
 */

/** @defgroup I2C_Public_Macro I2C Public Macros
  * @{
  */

/**
  * @brief I2C Direction Definition
  */
#define ALD_I2C_DIRECTION_RECEIVE   (0x00000000U)
#define ALD_I2C_DIRECTION_TRANSMIT  (0x00000001U)
/**
  * @brief I2C Transfer Definition
  */
#define ALD_I2C_NO_OPTION_FRAME     (0xFFFF0000U)

#define ALD_I2C_FIRST_FRAME         (0x00000001U)
#define ALD_I2C_FIRST_AND_NEXT_FRAME    (0x00000002U)
#define ALD_I2C_NEXT_FRAME          (0x00000004U)
#define ALD_I2C_FIRST_AND_LAST_FRAME    (0x00000008U)
#define ALD_I2C_LAST_FRAME_NO_STOP      (0x00000010U)
#define ALD_I2C_LAST_FRAME          (0x00000020U)

#define ALD_I2C_OTHER_FRAME         (0x00550000U)
#define ALD_I2C_OTHER_AND_LAST_FRAME    (0x55000000U)

#define ALD_I2C_FLAG_MASK   (0xFFFFFFFFU)
#define ALD_I2C_RESET_HANDLE_STATE(x) ((x)->state = ALD_I2C_STATE_RESET)
#define ALD_I2C_ENABLE_IT(x, y)   (SET_BIT((x)->perh->IER, (y)))
#define ALD_I2C_DISABLE_IT(x, y)  (SET_BIT((x)->perh->IDR, (y)))
#define ALD_I2C_CLEAR_IT(x, y)  (SET_BIT((x)->perh->ICR, (y)))
#define ALD_I2C_GET_IT_FLAG(x, y)  (READ_BIT((x)->perh->RIF, (y)))
#define ALD_I2C_GET_IT_SOURCE(x, y) ((((x)->perh->IFM & (y))  == (y)) ? SET : RESET)
#define ALD_I2C_GET_FLAG(x, y) ((((x)->perh->STAT) & ((y) & ALD_I2C_FLAG_MASK)) != RESET)
#define ALD_I2C_MASTER_GET_DIR(x) (READ_BIT(((x)->perh->CON2), I2C_CON2_RD_WRN_MSK))
#define ALD_I2C_SLAVE_GET_DIR(x) (READ_BIT(((x)->perh->STAT), I2C_STAT_DIR_MSK))
#define ALD_I2C_ENABLE(x)  (SET_BIT((x)->perh->CON1, I2C_CON1_PE_MSK))
#define ALD_I2C_DISABLE(x) (CLEAR_BIT((x)->perh->CON1, I2C_CON1_PE_MSK))
/**
  * @}
  */

/** @defgroup I2C_Private_Macro I2C Private Macros
  * @{
  */
#define IS_I2C_TYPE(x)                      (((x) == I2C0) || ((x) == I2C1))
#define IS_I2C_MODULE(x)                    (((x) == ALD_I2C_MODULE_MASTER) || ((x) == ALD_I2C_MODULE_SLAVE))
#define IS_I2C_ADDRESSING_MODE(ADDRESS)             (((ADDRESS) == ALD_I2C_ADDR_7BIT) || \
    ((ADDRESS) == ALD_I2C_ADDR_10BIT))
#define IS_I2C_DUAL_ADDRESS(ADDRESS)                (((ADDRESS) == ALD_I2C_DUALADDR_DISABLE) || \
    ((ADDRESS) == ALD_I2C_DUALADDR_ENABLE))
#define IS_I2C_GENERAL_CALL(CALL)               (((CALL)    == ALD_I2C_GENERALCALL_DISABLE) || \
    ((CALL)    == ALD_I2C_GENERALCALL_ENABLE))
#define IS_I2C_MEMADD_size(size)                (((size)    == ALD_I2C_MEMADD_SIZE_8BIT) || \
    ((size)    == ALD_I2C_MEMADD_SIZE_16BIT))
#define IS_I2C_NO_STRETCH(STRETCH)              (((STRETCH) == ALD_I2C_NOSTRETCH_DISABLE) || \
    ((STRETCH) == ALD_I2C_NOSTRETCH_ENABLE))
#define IS_I2C_CLOCK_SPEED(SPEED)               (((SPEED) > 0) && ((SPEED) <= ALD_I2C_EXTREME_FAST_MODE_MAX_CLK) )
#define I2C_FREQ_RANGE(__PCLK__)                ((__PCLK__) / 1000000)
#define I2C_MEM_ADD_MSB(__ADDRESS__)                ((uint8_t)((uint16_t)(((uint16_t)((__ADDRESS__) &\
        (uint16_t)(0xFF00))) >> 8)))
#define I2C_MEM_ADD_LSB(__ADDRESS__)                ((uint8_t)((uint16_t)((__ADDRESS__) & (uint16_t)(0x00FF))))
#define IS_I2C_IT(x)                        (((x) == ALD_I2C_IT_TXE)    || \
                                                                 ((x) == ALD_I2C_IT_TXOV)   || \
                                                                 ((x) == ALD_I2C_IT_TXUD)   || \
                                                                 ((x) == ALD_I2C_IT_RXNE)   || \
                                                                 ((x) == ALD_I2C_IT_RXOV)   || \
                                                                 ((x) == ALD_I2C_IT_RXUD)   || \
                                                                 ((x) == ALD_I2C_IT_TC) || \
                                                                 ((x) == ALD_I2C_IT_TCR)    || \
                                                                 ((x) == ALD_I2C_IT_ADDR)   || \
                                                                 ((x) == ALD_I2C_IT_NACK)   || \
                                                                 ((x) == ALD_I2C_IT_STOP)   || \
                                                                 ((x) == ALD_I2C_IT_BERR)   || \
                                                                 ((x) == ALD_I2C_IT_ARLO)   || \
                                                                 ((x) == ALD_I2C_IT_PECE)   || \
                                 ((x) == ALD_I2C_IT_TOUT)   || \
                                 ((x) == ALD_I2C_IT_ALERT))

#define IS_I2C_TRANSFER_OTHER_OPTIONS(OPTION)           (((OPTION) == ALD_I2C_OTHER_FRAME)      || \
                                                                 ((OPTION) == ALD_I2C_OTHER_AND_LAST_FRAME))

#define IS_I2C_TRANSFER_OPTIONS(OPTION)             (((OPTION) == ALD_I2C_FIRST_FRAME)      || \
                                                                 ((OPTION) == ALD_I2C_FIRST_AND_NEXT_FRAME) || \
                                                                 ((OPTION) == ALD_I2C_NEXT_FRAME)       || \
                                                                 ((OPTION) == ALD_I2C_FIRST_AND_LAST_FRAME) || \
                                                                 ((OPTION) == ALD_I2C_LAST_FRAME)       || \
                                                                 ((OPTION) == ALD_I2C_LAST_FRAME_NO_STOP)   || \
                                                                 IS_I2C_TRANSFER_OTHER_OPTIONS(OPTION))

#define ALD_I2C_STATE_MSK                       ((ALD_I2C_STATE_BUSY_TX | ALD_I2C_STATE_BUSY_RX) & (~(ALD_I2C_STATE_READY)))
#define ALD_I2C_STATE_NONE                      (ALD_I2C_MODE_NONE)
#define ALD_I2C_STATE_MASTER_BUSY_TX                ((ALD_I2C_STATE_BUSY_TX | ALD_I2C_STATE_MSK) | (ALD_I2C_MODE_MASTER))
#define ALD_I2C_STATE_MASTER_BUSY_RX                ((ALD_I2C_STATE_BUSY_RX | ALD_I2C_STATE_MSK) | (ALD_I2C_MODE_MASTER))
#define ALD_I2C_STATE_SLAVE_BUSY_TX                 ((ALD_I2C_STATE_BUSY_TX | ALD_I2C_STATE_MSK) | (ALD_I2C_MODE_SLAVE))
#define ALD_I2C_STATE_SLAVE_BUSY_RX                 ((ALD_I2C_STATE_BUSY_RX | ALD_I2C_STATE_MSK) | (ALD_I2C_MODE_SLAVE))

/**
  * @}
  */

/** @addtogroup I2C_Public_Functions
  * @{
  */

/** @addtogroup I2C_Public_Functions_Group1 Initialization and de-initialization functions
  * @{
  */
ald_status_t ald_i2c_init(ald_i2c_handle_t *hperh);
ald_status_t ald_i2c_reset(ald_i2c_handle_t *hperh);

/**
 * @}
 */

/** @addtogroup I2C_Public_Functions_Group2 Input and Output operation functions
 * @{
 */
/** Blocking mode: Polling */
ald_status_t ald_i2c_master_send(ald_i2c_handle_t *hperh, uint16_t dev_addr,
                                 uint8_t *buf, uint32_t size, uint32_t timeout);
ald_status_t ald_i2c_master_recv(ald_i2c_handle_t *hperh, uint16_t dev_addr,
                                uint8_t *buf, uint32_t size, uint32_t timeout);
ald_status_t ald_i2c_slave_send(ald_i2c_handle_t *hperh, uint8_t *buf, uint32_t size, uint32_t timeout);
ald_status_t ald_i2c_slave_recv(ald_i2c_handle_t *hperh, uint8_t *buf, uint32_t size, uint32_t timeout);
ald_status_t ald_i2c_mem_write(ald_i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr,
                           ald_i2c_addr_size_t add_size, uint8_t *buf, uint32_t size, uint32_t timeout);
ald_status_t ald_i2c_mem_read(ald_i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr,
                          ald_i2c_addr_size_t add_size, uint8_t *buf, uint32_t size, uint32_t timeout);

/** Non-Blocking mode: Interrupt */
ald_status_t ald_i2c_master_send_by_it(ald_i2c_handle_t *hperh, uint16_t dev_addr, uint8_t *buf, uint32_t size);
ald_status_t ald_i2c_master_recv_by_it(ald_i2c_handle_t *hperh, uint16_t dev_addr, uint8_t *buf, uint32_t size);
ald_status_t ald_i2c_slave_send_by_it(ald_i2c_handle_t *hperh, uint8_t *buf, uint32_t size);
ald_status_t ald_i2c_slave_recv_by_it(ald_i2c_handle_t *hperh, uint8_t *buf, uint32_t size);
ald_status_t ald_i2c_mem_write_by_it(ald_i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr,
                              ald_i2c_addr_size_t add_size, uint8_t *buf, uint32_t size);
ald_status_t ald_i2c_mem_read_by_it(ald_i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr,
                             ald_i2c_addr_size_t add_size, uint8_t *buf, uint32_t size);


/** Non-Blocking mode: DMA */
ald_status_t ald_i2c_master_send_by_dma(ald_i2c_handle_t *hperh, uint16_t dev_addr,
                                     uint8_t *buf, uint16_t size, uint8_t channel);
ald_status_t ald_i2c_master_recv_by_dma(ald_i2c_handle_t *hperh, uint16_t dev_addr,
                                    uint8_t *buf, uint16_t size, uint8_t channel);
ald_status_t ald_i2c_slave_send_by_dma(ald_i2c_handle_t *hperh, uint8_t *buf, uint16_t size, uint8_t channel);
ald_status_t ald_i2c_slave_recv_by_dma(ald_i2c_handle_t *hperh, uint8_t *buf, uint16_t size, uint8_t channel);
ald_status_t ald_i2c_mem_write_by_dma(ald_i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr, ald_i2c_addr_size_t add_size,
                                 uint8_t *buf, uint16_t size, uint8_t channel);
ald_status_t ald_i2c_mem_read_by_dma(ald_i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr,
                                ald_i2c_addr_size_t add_size, uint8_t *buf, uint16_t size, uint8_t channel);

/** Non-Blocking Sequence transmit mode */

ald_status_t ald_i2c_master_seq_send_by_it(ald_i2c_handle_t *hperh, uint16_t dev_addr, uint8_t *buf, uint32_t size, uint32_t option);
ald_status_t ald_i2c_master_seq_recv_by_it(ald_i2c_handle_t *hperh, uint16_t dev_addr, uint8_t *buf, uint32_t size, uint32_t option);
ald_status_t ald_i2c_slave_seq_send_by_it(ald_i2c_handle_t *hperh, uint8_t *buf, uint32_t size, uint32_t option);
ald_status_t ald_i2c_slave_seq_recv_by_it(ald_i2c_handle_t *hperh, uint8_t *buf, uint32_t size, uint32_t option);
ald_status_t ald_i2c_master_abort_it(ald_i2c_handle_t *hperh, uint16_t addr);
ald_status_t ald_i2c_enablelisten_it(ald_i2c_handle_t *hperh);
ald_status_t ald_i2c_disablelisten_it(ald_i2c_handle_t *hperh);

void ald_i2c_seq_ev_irq_handler(ald_i2c_handle_t *hperh);
void ald_i2c_seq_er_irq_handler(ald_i2c_handle_t *hperh);

/**
 * @}
 */

/** @addtogroup I2C_Public_Functions_Group3 Peripheral state and Errors functions
  * @{
  */
ald_i2c_state_t ald_i2c_get_state(ald_i2c_handle_t *hperh);
uint32_t ald_i2c_get_error(ald_i2c_handle_t *hperh);
void ald_i2c_clear_flag_status(ald_i2c_handle_t *hperh, ald_i2c_interrupt_t flag);
flag_status_t ald_i2c_get_mask_flag_status(ald_i2c_handle_t *hperh, ald_i2c_interrupt_t flag);
flag_status_t ald_i2c_get_flag_status(ald_i2c_handle_t *hperh, ald_i2c_interrupt_t flag);
it_status_t ald_i2c_get_it_status(ald_i2c_handle_t *hperh, ald_i2c_interrupt_t it);
/**
 * @}
 */

/** @addtogroup I2C_Public_Functions_Group4 IRQ Handler and Callbacks
 * @{
 */
void ald_i2c_ev_irq_handler(ald_i2c_handle_t *hperh);
void ald_i2c_er_irq_handler(ald_i2c_handle_t *hperh);
void ald_i2c_interrupt_config(ald_i2c_handle_t *hperh, ald_i2c_interrupt_t it, type_func_t state);
/**
 * @}
 */

/**
 * @}
 */

/**
  * @}
  */

/**
 * @}
 */
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ALD_I2C_H__ */
