/**
 *********************************************************************************
 *
 * @file    ald_i2c.h
 * @brief   Header file of I2C driver
 *
 * @version V1.0
 * @date    15 Nov 2019
 * @author  AE Team
 * @note
 *
 * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
 *
 ********************************************************************************
 */

#ifndef __ALD_I2C_H__
#define __ALD_I2C_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "utils.h"
#include "ald_dma.h"
#include "ald_cmu.h"
#include <string.h>

/** @addtogroup ES32FXXX_ALD
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
	I2C_ERROR_NONE    = 0x0,  /**< No error */
	I2C_ERROR_BERR    = 0x1,  /**< Berr error */
	I2C_ERROR_ARLO    = 0x2,  /**< Arlo error */
	I2C_ERROR_RUD     = 0x4,  /**< Rx underflow error */
	I2C_ERROR_AF      = 0x8,  /**< Af error */	
	I2C_ERROR_ROV     = 0x10,  /**< Rx overflow error */
	I2C_ERROR_RF      = 0x20,  /**< Rx full error */
	I2C_ERROR_TUD     = 0x40,  /**< Tx underflow error */
	I2C_ERROR_TOV     = 0x80,  /**< Tx overflow error */
	I2C_ERROR_TE      = 0x100,  /**< Tx empty error */
	I2C_ERROR_DMA     = 0x200, /**< Dma error */
	I2C_ERROR_TIMEOUT = 0x400  /**< Timeout error */
} i2c_error_t;

/**
  * @brief I2C state structure definition
  */
typedef enum {
	I2C_STATE_RESET   = 0x0,  /**< Peripheral is not yet Initialized */
	I2C_STATE_READY   = 0x20, /**< Peripheral Initialized and ready for use */
	I2C_STATE_BUSY    = 0x24, /**< An internal process is ongoing */
	I2C_STATE_BUSY_TX = 0x21, /**< Data Transmission process is ongoing */
	I2C_STATE_BUSY_RX = 0x22, /**< Data Reception process is ongoing */
	I2C_STATE_TIMEOUT = 0xA0, /**< timeout state */
	I2C_STATE_ERROR   = 0xE0  /**< Error */
} i2c_state_t;

/**
  * @brief I2C Addressing Mode
  */
typedef enum {
	I2C_ADDR_7BIT  = 0x0, /**< 7 bit address */
	I2C_ADDR_10BIT = 0x1, /**< 10 bit address */
} i2c_addr_t;

/**
  * @brief I2C Dual Addressing Mode
  */
typedef enum {
	I2C_DUALADDR_DISABLE = 0x0, /**< dual address is disable */
	I2C_DUALADDR_ENABLE  = 0x1  /**< dual address is enable */
} i2c_dual_addr_t;

/**
  * @brief I2C General Call Addressing mode
  */
typedef enum {
	I2C_GENERALCALL_DISABLE = 0x0, /**< general call address is disable */
	I2C_GENERALCALL_ENABLE  = 0x1 /**< general call address is enable */
} i2c_general_addr_t;

/**
  * @brief I2C Nostretch Mode
  */
typedef enum {
	I2C_NOSTRETCH_DISABLE = 0x0, /**< Nostretch disable */
	I2C_NOSTRETCH_ENABLE  = 0x1 /**< Nostretch enable */
} i2c_nostretch_t;

/**
  * @brief I2C Memory Address Size
  */
typedef enum {
	I2C_MEMADD_SIZE_8BIT  = 0x8, /**< 8 bit memory address size */
	I2C_MEMADD_SIZE_16BIT = 0x10 /**< 10 bit memory address size */
} i2c_addr_size_t;

/**
  * @brief I2C mode structure definition
  */
typedef enum
{
	I2C_MODE_NONE   = 0x0,  /**< No I2C communication on going */
	I2C_MODE_MASTER = 0x10, /**< I2C communication is in Master mode */
	I2C_MODE_SLAVE  = 0x20, /**< I2C communication is in Slave mode */
	I2C_MODE_MEM    = 0x40  /**< I2C communication is in Memory mode */
} i2c_mode_t;

/**
  * @brief I2C Clock
  */
typedef enum {
	I2C_STANDARD_MODE_MAX_CLK     = 100000,  /**< Standard mode clock */
	I2C_FAST_MODE_MAX_CLK         = 400000,  /**< Fast mode clock */
	I2C_EXTREME_FAST_MODE_MAX_CLK = 1000000, /**< Extreme mode clock */
} i2c_clock_t;

/**
  * @brief I2C OAR2 Register
  */
typedef enum {
	I2C_OAR2_ENDUAL = (1U << 0), /**< ENDUAL BIT */
	I2C_OAR2_ADD2   = (1U << 1)  /**< ADD2 BIT */
} i2c_oar2_t;

/**
  * @brief I2C CON1 Register
  */
typedef enum {
	I2C_CON1_PE        = (1U << 0),		/**< Peripheral enable BIT */
	I2C_CON1_TXDMA     = (1U << 14),	/**< Transmit DMA BIT */
	I2C_CON1_RXDMA     = (1U << 15),	/**< Receive DMA BIT */
	I2C_CON1_SBC       = (1U << 16),	/**< Receive DMA BIT */
	I2C_CON1_NOSTRETCH = (1U << 17),	/**< Slave bytes control BIT */
	I2C_CON1_GCEN      = (1U << 19),	/**< General call BIT */
	I2C_CON1_SMBHEN    = (1U << 20),	/**< SMBus slave device enable BIT */
	I2C_CON1_SMBDEN    = (1U << 21),	/**< SMBus master device enable BIT */
	I2C_CON1_ALERTEN   = (1U << 22),	/**< SMBus alert device enable BIT */
	I2C_CON1_PECEN     = (1U << 23),	/**< PEC enable BIT */
} i2c_con1_t;

/**
  * @brief I2C CON2 Register
  */
typedef enum {
	I2C_CON2_RD_WRN    = (1U << 10),	/**< Master R/W control BIT */
	I2C_CON2_ADD10     = (1U << 11),	/**< 10bit address control BIT */
	I2C_CON2_HEAD10R   = (1U << 12),	/**< 10bit address master Receive control BIT */
	I2C_CON2_START     = (1U << 13),	/**< Master start singal control BIT */
	I2C_CON2_STOP      = (1U << 14),	/**< Master stop singal control BIT */
	I2C_CON2_NACK      = (1U << 15),	/**< Master Nack control BIT */
	I2C_CON2_RELOAD    = (1U << 24),	/**< Master communication reload control BIT */
	I2C_CON2_AUTOEND   = (1U << 25),	/**< Master Autoend control BIT */
	I2C_CON2_PECBYTE   = (1U << 26),	/**< PEC control BIT */
	I2C_CON2_HOLDACK   = (1U << 28),	/**< Hold ack control BIT */
} i2c_con2_t;

/**
  * @brief I2C ADDR1 Register
  */
typedef enum {
	I2C_OA1MODE = (1U << 10),	/**< Addr1 bits choose BIT */
	I2C_OA1EN   = (1U << 15),	/**< Addr1 enable BIT */
} i2c_addr1_t;

/**
  * @brief I2C ADDR2 Register
  */
typedef enum {
	I2C_OA2EN = (1U << 15),		/**< Addr2 enable BIT */
} i2c_addr2_t;

/**
  * @brief I2C TIMEOUTR Register
  */
typedef enum {
	I2C_TIMEOUTR_TIDLE     = (1U << 12),	/**< SCL idle check enable BIT */
	I2C_TIMEOUTR_TIMEOUTEN = (1U << 15),	/**< Timeout enable BIT */
} i2c_timoutr_t;

/**
  * @brief I2C peripherals module
  */
typedef enum {
	I2C_MODULE_MASTER = (1U << 0),	/**< Master module */
	I2C_MODULE_SLAVE  = (1U << 1)	/**< Slave module */
} i2c_module_t;

/**
  * @brief I2C STAT Register 
  */
typedef enum {
	I2C_STAT_TXE  = (1U << 0),	/**< Transmit FIFO empty flag */
	I2C_STAT_TXF  = (1U << 1),	/**< Transmit FIFO full flag */
	I2C_STAT_TXOV = (1U << 2),	/**< Transmit FIFO overrun flag */
	I2C_STAT_TXUD = (1U << 3),	/**< Transmit FIFO underrun flag*/
	I2C_STAT_THTH = (1U << 4),	/**< Transmit FIFO threshold flag */
	I2C_STAT_RXE  = (1U << 5),	/**< Receive FIFO empty flag*/
	I2C_STAT_RXF  = (1U << 6),	/**< Receive FIFO full flag*/
	I2C_STAT_RXOV = (1U << 7),	/**< Receive FIFO overrun flag */
	I2C_STAT_RXUD = (1U << 8),	/**< Receive FIFO underrun flag */
	I2C_STAT_RXTH = (1U << 9),	/**< Receive FIFO threshold flag */
	I2C_STAT_TC   = (1U << 10),	/**< Transmit completed flag */
	I2C_STAT_TCR  = (1U << 11),	/**< Transmit and reload completed flag */
	I2C_STAT_BUSY = (1U << 15),	/**< Bus status busy flag */
	I2C_STAT_DIR  = (1U << 16),	/**< Slave R/W flag */
} i2c_stat_t;

/**
  * @brief Interrupt Configuration Definition
  */
typedef enum {
	I2C_IT_TXE   = (1U << 0), /**< Transmit FIFO empty interrupt */
	I2C_IT_TXOV  = (1U << 2), /**< Transmit FIFO overrun interrupt */
	I2C_IT_TXUD  = (1U << 3), /**< Transmit FIFO underrun interrupt*/
	I2C_IT_TXTH  = (1U << 4), /**< Transmit FIFO threshold interrupt */
	I2C_IT_RXF   = (1U << 6), /**< Receive FIFO full interrupt*/
	I2C_IT_RXOV  = (1U << 7), /**< Receive FIFO overrun interrupt */
	I2C_IT_RXUD  = (1U << 8), /**< Receive FIFO underrun interrupt */
	I2C_IT_RXTH  = (1U << 9), /**< Receive FIFO threshold interrupt */
	I2C_IT_TC    = (1U << 10), /**< Transmit completed interrupt */
	I2C_IT_TCR   = (1U << 11), /**< Transmit and reload completed interrupt */
	I2C_IT_ADDR  = (1U << 12), /**< Address matching interrupt */
	I2C_IT_NACK  = (1U << 13), /**< NACK interrupt */
	I2C_IT_STOP  = (1U << 14), /**< Stop detection interrupt */
	I2C_IT_BERR  = (1U << 16), /**< Bus error interrupt */
	I2C_IT_ARLO  = (1U << 17), /**< Arbitration loss interrupt */
	I2C_IT_PECE  = (1U << 18), /**< PEC error interrupt */
	I2C_IT_TOUT  = (1U << 19), /**< Timeout interrupt */
	I2C_IT_ALERT = (1U << 20), /**< SMBus Alert interrupt */
} i2c_interrupt_t;

/**
  * @brief I2C TRISE Register
  */
typedef enum {
	I2C_TRISE_TRISE = 0x3F, /**< TRISE BITS */
} i2c_trise_t;

/**
 * @brief I2C Configuration Structure definition
 */
typedef struct {
	i2c_module_t module;		/**< Specifies the communication module */
	uint32_t clk_speed;		/**< Specifies the clock frequency */
	uint32_t own_addr1;		/**< Specifies the first device own address */
	i2c_addr_t addr_mode;		/**< Specifies addressing mode */
	i2c_dual_addr_t dual_addr;	/**< Specifies if dual addressing mode is selected */
	uint32_t own_addr2;		/**< Specifies the second device own address */
	i2c_general_addr_t general_call;/**< Specifies if general call mode is selected */
	i2c_nostretch_t no_stretch;	/**< Specifies if nostretch mode is selected */
} i2c_init_t;

/**
  * @brief  I2C handle Structure definition
  */
typedef struct i2c_handle_s {
	I2C_TypeDef *perh;        /**< I2C registers base address */
	i2c_init_t init;          /**< I2C communication parameters */
	uint8_t *p_buff;          /**< Pointer to I2C transfer buffer */
	uint16_t xfer_size;       /**< I2C transfer size */
	__IO uint16_t xfer_count; /**< I2C transfer counter */
#ifdef ALD_DMA
	dma_handle_t hdmatx;      /**< I2C Tx DMA handle parameters */
	dma_handle_t hdmarx;      /**< I2C Rx DMA handle parameters */
#endif
	lock_state_t lock;        /**< I2C locking object */
	__IO i2c_state_t state;   /**< I2C communication state */
	__IO i2c_mode_t mode;     /**< I2C communication mode */
	__IO uint32_t error_code; /**< I2C Error code */

	void (*master_tx_cplt_cbk)(struct i2c_handle_s *arg); /**< Master Tx completed callback */
	void (*master_rx_cplt_cbk)(struct i2c_handle_s *arg); /**< Master Rx completed callback */
	void (*slave_tx_cplt_cbk)(struct i2c_handle_s *arg);  /**< Slave Tx completed callback */
	void (*slave_rx_cplt_cbk)(struct i2c_handle_s *arg);  /**< Slave Rx completed callback */
	void (*mem_tx_cplt_cbk)(struct i2c_handle_s *arg);    /**< Tx to Memory completed callback */
	void (*mem_rx_cplt_cbk)(struct i2c_handle_s *arg);    /**< Rx from Memory completed callback */
	void (*error_callback)(struct i2c_handle_s *arg);     /**< Error callback */
} i2c_handle_t;

/**
 * @}
 */

/** @defgroup I2C_Public_Macro I2C Public Macros
  * @{
  */
#define I2C_FLAG_MASK	(0xFFFFFFFF)
#define I2C_RESET_HANDLE_STATE(x) ((x)->state = I2C_STATE_RESET)
#define I2C_ENABLE_IT(x, y)   (SET_BIT((x)->perh->IER, (y)))
#define I2C_DISABLE_IT(x, y)  (SET_BIT((x)->perh->IDR, (y)))
#define I2C_CLEAR_IT(x, y)  (SET_BIT((x)->perh->ICR, (y)))
#define I2C_GET_IT_FLAG(x, y)  (READ_BIT((x)->perh->RIF, (y)))
#define I2C_GET_IT_SOURCE(x, y) ((((x)->perh->IFM & (y))  == (y)) ? SET : RESET)
#define I2C_GET_FLAG(x, y) ((((x)->perh->STAT) & ((y) & I2C_FLAG_MASK)) != RESET)
#define I2C_MASTER_GET_DIR(x) (READ_BIT(((x)->perh->CON2), I2C_CON2_RD_WRN_MSK))
#define I2C_SLAVE_GET_DIR(x) (READ_BIT(hperh->perh->STAT, I2C_STAT_DIR_MSK))
#define I2C_ENABLE(x)  (SET_BIT((x)->perh->CON1, I2C_CON1_PE_MSK))
#define I2C_DISABLE(x) (CLEAR_BIT((x)->perh->CON1, I2C_CON1_PE_MSK))
/**
  * @}
  */

/** @defgroup I2C_Private_Macro I2C Private Macros
  * @{
  */
#define IS_I2C_TYPE(x)						(((x) == I2C0) || ((x) == I2C1))
#define IS_I2C_MODULE(x)					(((x) == I2C_MODULE_MASTER) || ((x) == I2C_MODULE_SLAVE))
#define IS_I2C_ADDRESSING_MODE(ADDRESS)				(((ADDRESS) == I2C_ADDR_7BIT) || \
	((ADDRESS) == I2C_ADDR_10BIT))
#define IS_I2C_DUAL_ADDRESS(ADDRESS)				(((ADDRESS) == I2C_DUALADDR_DISABLE) || \
	((ADDRESS) == I2C_DUALADDR_ENABLE))
#define IS_I2C_GENERAL_CALL(CALL)				(((CALL)    == I2C_GENERALCALL_DISABLE) || \
	((CALL)    == I2C_GENERALCALL_ENABLE))
#define IS_I2C_MEMADD_size(size)				(((size)    == I2C_MEMADD_SIZE_8BIT) || \
	((size)    == I2C_MEMADD_SIZE_16BIT))
#define IS_I2C_NO_STRETCH(STRETCH)				(((STRETCH) == I2C_NOSTRETCH_DISABLE) || \
	((STRETCH) == I2C_NOSTRETCH_ENABLE))
#define IS_I2C_CLOCK_SPEED(SPEED)				(((SPEED) > 0) && ((SPEED) <= I2C_EXTREME_FAST_MODE_MAX_CLK) )
#define I2C_FREQ_RANGE(__PCLK__)				((__PCLK__) / 1000000)
#define I2C_MEM_ADD_MSB(__ADDRESS__)				((uint8_t)((uint16_t)(((uint16_t)((__ADDRESS__) &\
        (uint16_t)(0xFF00))) >> 8)))
#define I2C_MEM_ADD_LSB(__ADDRESS__)				((uint8_t)((uint16_t)((__ADDRESS__) & (uint16_t)(0x00FF))))
#define IS_I2C_IT(x)						(((x) == I2C_IT_TXE)	|| \
                                                                 ((x) == I2C_IT_TXOV)	|| \
                                                                 ((x) == I2C_IT_TXUD)	|| \
                                                                 ((x) == I2C_IT_TXTH)	|| \
                                                                 ((x) == I2C_IT_RXF)	|| \
                                                                 ((x) == I2C_IT_RXOV)	|| \
                                                                 ((x) == I2C_IT_RXUD)	|| \
                                                                 ((x) == I2C_IT_RXTH)	|| \
                                                                 ((x) == I2C_IT_TC)	|| \
                                                                 ((x) == I2C_IT_TCR)	|| \
                                                                 ((x) == I2C_IT_ADDR)	|| \
                                                                 ((x) == I2C_IT_NACK)	|| \
                                                                 ((x) == I2C_IT_STOP)	|| \
                                                                 ((x) == I2C_IT_BERR)	|| \
                                                                 ((x) == I2C_IT_ARLO)	|| \
                                                                 ((x) == I2C_IT_PECE)	|| \
								 ((x) == I2C_IT_TOUT)	|| \
								 ((x) == I2C_IT_ALERT))
/**
  * @}
  */

/** @addtogroup I2C_Public_Functions
  * @{
  */

/** @addtogroup I2C_Public_Functions_Group1 Initialization and de-initialization functions
  * @{
  */
ald_status_t ald_i2c_init(i2c_handle_t *hperh);
ald_status_t ald_i2c_reset(i2c_handle_t *hperh);

/**
 * @}
 */

/** @addtogroup I2C_Public_Functions_Group2 Input and Output operation functions
 * @{
 */
 /** Blocking mode: Polling */
ald_status_t ald_i2c_master_send(i2c_handle_t *hperh, uint16_t dev_addr,
                                 uint8_t *buf, uint32_t size, uint32_t timeout);
ald_status_t ald_i2c_master_recv(i2c_handle_t *hperh, uint16_t dev_addr,
                                uint8_t *buf, uint32_t size, uint32_t timeout);
ald_status_t ald_i2c_slave_send(i2c_handle_t *hperh, uint8_t *buf, uint32_t size, uint32_t timeout);
ald_status_t ald_i2c_slave_recv(i2c_handle_t *hperh, uint8_t *buf, uint32_t size, uint32_t timeout);
ald_status_t ald_i2c_mem_write(i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr,
                           i2c_addr_size_t add_size, uint8_t *buf, uint32_t size, uint32_t timeout);
ald_status_t ald_i2c_mem_read(i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr,
                          i2c_addr_size_t add_size, uint8_t *buf, uint32_t size, uint32_t timeout);

 /** Non-Blocking mode: Interrupt */
ald_status_t ald_i2c_master_send_by_it(i2c_handle_t *hperh, uint16_t dev_addr, uint8_t *buf, uint32_t size);
ald_status_t ald_i2c_master_recv_by_it(i2c_handle_t *hperh, uint16_t dev_addr, uint8_t *buf, uint32_t size);
ald_status_t ald_i2c_slave_send_by_it(i2c_handle_t *hperh, uint8_t *buf, uint32_t size);
ald_status_t ald_i2c_slave_recv_by_it(i2c_handle_t *hperh, uint8_t *buf, uint32_t size);
ald_status_t ald_i2c_mem_write_by_it(i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr,
                              i2c_addr_size_t add_size, uint8_t *buf, uint32_t size);
ald_status_t ald_i2c_mem_read_by_it(i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr,
                             i2c_addr_size_t add_size, uint8_t *buf, uint32_t size);

#ifdef ALD_DMA
 /** Non-Blocking mode: DMA */
ald_status_t ald_i2c_master_send_by_dma(i2c_handle_t *hperh, uint16_t dev_addr,
                                     uint8_t *buf, uint8_t size, uint8_t channel);
ald_status_t ald_i2c_master_recv_by_dma(i2c_handle_t *hperh, uint16_t dev_addr,
                                    uint8_t *buf, uint8_t size, uint8_t channel);
ald_status_t ald_i2c_slave_send_by_dma(i2c_handle_t *hperh, uint8_t *buf, uint8_t size, uint8_t channel);
ald_status_t ald_i2c_slave_recv_by_dma(i2c_handle_t *hperh, uint8_t *buf, uint8_t size, uint8_t channel);
ald_status_t ald_i2c_mem_write_by_dma(i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr, i2c_addr_size_t add_size,
                                 uint8_t *buf, uint8_t size, uint8_t channel);
ald_status_t ald_i2c_mem_read_by_dma(i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr,
                                i2c_addr_size_t add_size, uint8_t *buf, uint8_t size, uint8_t channel);
#endif
/**
 * @}
 */

/** @addtogroup I2C_Public_Functions_Group3 Peripheral state and Errors functions
  * @{
  */
i2c_state_t ald_i2c_get_state(i2c_handle_t *hperh);
uint32_t ald_i2c_get_error(i2c_handle_t *hperh);
void ald_i2c_clear_flag_status(i2c_handle_t *hperh, i2c_interrupt_t flag);
flag_status_t ald_i2c_get_mask_flag_status(i2c_handle_t *hperh, i2c_interrupt_t flag);
flag_status_t ald_i2c_get_flag_status(i2c_handle_t *hperh, i2c_interrupt_t flag);
it_status_t ald_i2c_get_it_status(i2c_handle_t *hperh, i2c_interrupt_t it);
/**
 * @}
 */

/** @addtogroup I2C_Public_Functions_Group4 IRQ Handler and Callbacks
 * @{
 */
void ald_i2c_ev_irq_handler(i2c_handle_t *hperh);
void ald_i2c_er_irq_handler(i2c_handle_t *hperh);
void ald_i2c_interrupt_config(i2c_handle_t *hperh, i2c_interrupt_t it, type_func_t state);
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
#endif

#endif /* __ALD_I2C_H__ */
