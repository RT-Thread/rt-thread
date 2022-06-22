/**
 *********************************************************************************
 *
 * @file    ald_i2c.h
 * @brief   Header file of I2C driver
 *
 * @version V1.0
 * @date    15 Nov 2017
 * @author  AE Team
 * @note
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
	I2C_ERROR_NONE    = 0x0U, 	/**< No error */
	I2C_ERROR_BERR    = 0x1U, 	/**< Berr error */
	I2C_ERROR_ARLO    = 0x2U, 	/**< Arlo error */
	I2C_ERROR_AF      = 0x4U, 	/**< Af error */
	I2C_ERROR_OVR     = 0x8U, 	/**< Ovr error */
	I2C_ERROR_DMA     = 0x10U,	/**< Dma error */
	I2C_ERROR_TIMEOUT = 0x20U,	/**< Timeout error */
} i2c_error_t;

/**
  * @brief I2C state structure definition
  */
typedef enum {
	I2C_STATE_RESET   = 0x0U, 	/**< Peripheral is not yet Initialized */
	I2C_STATE_READY   = 0x1U,	/**< Peripheral Initialized and ready for use */
	I2C_STATE_BUSY    = 0x2U,	/**< An internal process is ongoing */
	I2C_STATE_BUSY_TX = 0x3U,	/**< Data Transmission process is ongoing */
	I2C_STATE_BUSY_RX = 0x4U,	/**< Data Reception process is ongoing */
	I2C_STATE_TIMEOUT = 0x5U,	/**< timeout state */
	I2C_STATE_ERROR   = 0x6U,	/**< Error */
} i2c_state_t;

/**
  * @brief I2C Duty Cycle
  */
typedef enum {
	I2C_DUTYCYCLE_2    = 0x0U,   	/**< duty cycle is 2 */
	I2C_DUTYCYCLE_16_9 = 0x4000U,	/**< duty cycle is 16/9 */
} i2c_duty_t;

/**
  * @brief I2C Addressing Mode
  */
typedef enum {
	I2C_ADDR_7BIT  = 0x1U,	/**< 7 bit address */
	I2C_ADDR_10BIT = 0x2U,	/**< 10 bit address */
} i2c_addr_t;

/**
  * @brief I2C Dual Addressing Mode
  */
typedef enum {
	I2C_DUALADDR_DISABLE = 0x0U,	/**< dual address is disable */
	I2C_DUALADDR_ENABLE  = 0x1U,	/**< dual address is enable */
} i2c_dual_addr_t;

/**
  * @brief I2C General Call Addressing mode
  */
typedef enum {
	I2C_GENERALCALL_DISABLE = 0x0U, 	/**< feneral call address is disable */
	I2C_GENERALCALL_ENABLE  = 0x40U,	/**< feneral call address is enable */
} i2c_general_addr_t;

/**
  * @brief I2C Nostretch Mode
  */
typedef enum {
	I2C_NOSTRETCH_DISABLE = 0x0U, 	/**< Nostretch disable */
	I2C_NOSTRETCH_ENABLE  = 0x80U,	/**< Nostretch enable */
} i2c_nostretch_t;

/**
  * @brief I2C Memory Address Size
  */
typedef enum {
	I2C_MEMADD_SIZE_8BIT  = 0x1U,	/**< 8 bit memory address size */
	I2C_MEMADD_SIZE_16BIT = 0x10U,	/**< 10 bit memory address size */
} i2c_addr_size_t;

/**
  * @brief I2C Flag Definition
  */
typedef enum {
	I2C_FLAG_SB         = (1U << 0),
	I2C_FLAG_ADDR       = (1U << 1),
	I2C_FLAG_BTF        = (1U << 2),
	I2C_FLAG_ADD10      = (1U << 3),
	I2C_FLAG_STOPF      = (1U << 4),
	I2C_FLAG_RXNE       = (1U << 6),
	I2C_FLAG_TXE        = (1U << 7),
	I2C_FLAG_BERR       = (1U << 8),
	I2C_FLAG_ARLO       = (1U << 9),
	I2C_FLAG_AF         = (1U << 10),
	I2C_FLAG_OVR        = (1U << 11),
	I2C_FLAG_PECERR     = (1U << 12),
	I2C_FLAG_TIMEOUT    = (1U << 14),
	I2C_FLAG_SMBALERT   = (1U << 15),
	I2C_FLAG_MSL        = (1U << 16),
	I2C_FLAG_BUSY       = (1U << 17),
	I2C_FLAG_TRA        = (1U << 18),
	I2C_FLAG_GENCALL    = (1U << 20),
	I2C_FLAG_SMBDEFAULT = (1U << 21),
	I2C_FLAG_SMBHOST    = (1U << 22),
	I2C_FLAG_DUALF      = (1U << 23),
} i2c_flag_t;

/**
  * @brief I2C mode structure definition
  */
typedef enum
{
	I2C_MODE_NONE   = 0x0U, 	/**< No I2C communication on going */
	I2C_MODE_MASTER = 0x10U,	/**< I2C communication is in Master mode */
	I2C_MODE_SLAVE  = 0x20U,	/**< I2C communication is in Slave mode */
	I2C_MODE_MEM    = 0x40U,	/**< I2C communication is in Memory mode */
} i2c_mode_t;

/**
  * @brief I2C Clock
  */
typedef enum {
	I2C_STANDARD_MODE_MAX_CLK = 100000U,	/**< Standard mode clock */
	I2C_FAST_MODE_MAX_CLK     = 400000U,	/**< Fast mode clock */
} i2c_clock_t;

/**
  * @brief Interrupt Configuration Definition
  */
typedef enum {
	I2C_IT_BUF = (1U << 10),	/**< Buffer interrupt */
	I2C_IT_EVT = (1U << 9), 	/**< Event interrupt */
	I2C_IT_ERR = (1U << 8), 	/**< Error interrupt */
} i2c_interrupt_t;

/**
  * @brief I2C CON1 Register
  */
typedef enum {
	I2C_CON1_PEN    = (1U << 0), 	/**< PEN BIT */
	I2C_CON1_PMOD   = (1U << 1), 	/**< PMOD BIT */
	I2C_CON1_SMBMOD = (1U << 3), 	/**< SMBMOD  BIT */
	I2C_CON1_ARPEN  = (1U << 4), 	/**< ARPEN BIT */
	I2C_CON1_PECEN  = (1U << 5), 	/**< PECEN BIT */
	I2C_CON1_GCEN   = (1U << 6), 	/**< GCEN  BIT */
	I2C_CON1_DISCS  = (1U << 7), 	/**< DISCS BIT */
	I2C_CON1_START  = (1U << 8), 	/**< START BIT */
	I2C_CON1_STOP   = (1U << 9), 	/**< STOP BIT */
	I2C_CON1_ACKEN  = (1U << 10),	/**< ACKEN  BIT */
	I2C_CON1_POSAP  = (1U << 11),	/**< POSAP BIT */
	I2C_CON1_TRPEC  = (1U << 12),	/**< TRPEC  BIT */
	I2C_CON1_ALARM  = (1U << 13),	/**< ALARM BIT */
	I2C_CON1_SRST   = (1U << 15),	/**< SRST BIT */
} i2c_con1_t;

/**
  * @brief I2C CON2 Register
  */
typedef enum {
	I2C_CON2_CLKF    =  0x3FU,     	/**< CLKF BITS */
	I2C_CON2_CLKF_0  = (1U << 0), 	/**< CLKF_0 BIT */
	I2C_CON2_CLKF_1  = (1U << 1), 	/**< CLKF_1 BIT */
	I2C_CON2_CLKF_2  = (1U << 2), 	/**< CLKF_2 BIT */
	I2C_CON2_CLKF_3  = (1U << 3), 	/**< CLKF_3 BIT */
	I2C_CON2_CLKF_4  = (1U << 4), 	/**< CLKF_4 BIT */
	I2C_CON2_CLKF_5  = (1U << 5), 	/**< CLKF_5 BIT */
	I2C_CON2_ERRIE   = (1U << 8), 	/**< ERRIE BIT */
	I2C_CON2_EVTIE   = (1U << 9), 	/**< EVTIE BIT */
	I2C_CON2_BUFIE   = (1U << 10),	/**< BUFIE BIT */
	I2C_CON2_DMAEN   = (1U << 11),	/**< DMAEN BIT */
	I2C_CON2_LDMA    = (1U << 12),	/**< LDMA BIT */
} i2c_con2_t;

/**
  * @brief I2C ADDR1 Register
  */
typedef enum {
	I2C_ADDR1_ADDH0   = (1U << 0), 	/**< ADDH0 BIT */
	I2C_ADDR1_ADDH1   = (1U << 1), 	/**< ADDH1 BIT */
	I2C_ADDR1_ADDH2   = (1U << 2), 	/**< ADDH2 BIT */
	I2C_ADDR1_ADDH3   = (1U << 3), 	/**< ADDH3 BIT */
	I2C_ADDR1_ADDH4   = (1U << 4), 	/**< ADDH4 BIT */
	I2C_ADDR1_ADDH5   = (1U << 5), 	/**< ADDH5 BIT */
	I2C_ADDR1_ADDH6   = (1U << 6), 	/**< ADDH6 BIT */
	I2C_ADDR1_ADDH7   = (1U << 7), 	/**< ADDH7 BIT */
	I2C_ADDR1_ADDH8   = (1U << 8), /**< ADDH8 BIT */
	I2C_ADDR1_ADDH9   = (1U << 9),	/**< ADDH9 BIT */
	I2C_ADDR1_ADDTYPE = (1U << 15),	/**< ADDTYPE BIT */
} i2c_addr1_t;

/**
  * @brief I2C ADDR2 Register
  */
typedef enum {
	I2C_ADDR2_DUALEN = (1U << 0),	/**< DUALEN BIT */
	I2C_ADDR2_ADD    = (1U << 1),	/**< ADD BIT */
} i2c_addr2_t;

/**
  * @brief I2C STAT1 Register
  */
typedef enum {
	I2C_STAT1_SB        = (1U << 0), 	/**< SB BIT */
	I2C_STAT1_ADDR      = (1U << 1), 	/**< ADDR  BIT */
	I2C_STAT1_BTC       = (1U << 2), 	/**< BTC BIT */
	I2C_STAT1_SENDADD10 = (1U << 3), 	/**< SENDADD10 BIT */
	I2C_STAT1_DETSTP    = (1U << 4), 	/**< DETSTP BIT */
	I2C_STAT1_RXBNE     = (1U << 6), 	/**< RXBNE BIT */
	I2C_STAT1_TXBE      = (1U << 7), 	/**< TXBE BIT */
	I2C_STAT1_BUSERR    = (1U << 8), 	/**< BUSERR BIT */
	I2C_STAT1_LARB      = (1U << 9), 	/**< LARB BIT */
	I2C_STAT1_ACKERR    = (1U << 10),	/**< ACKERR BIT */
	I2C_STAT1_ROUERR    = (1U << 11),	/**< ROUERR BIT */
	I2C_STAT1_PECERR    = (1U << 12),	/**< PECERR BIT */
	I2C_STAT1_SMBTO     = (1U << 14),	/**< SMBTO BIT */
	I2C_STAT1_SMBALARM  = (1U << 15),	/**< SMBALARM BIT */
} i2c_stat1_t;

/**
  * @brief I2C STAT2 Register
  */
typedef enum {
	I2C_STAT2_MASTER = (1U << 0),	/**< MASTER BIT */
	I2C_STAT2_BSYF   = (1U << 1),	/**< BSYF  BIT */
	I2C_STAT2_TRF    = (1U << 2),	/**< TRF BIT */
	I2C_STAT2_RXGCF  = (1U << 4),	/**< RXGCF BIT */
	I2C_STAT2_SMBDEF = (1U << 5),	/**< SMBDEF BIT */
	I2C_STAT2_SMBHH  = (1U << 6),	/**< SMBHH BIT */
	I2C_STAT2_DUALF  = (1U << 7),	/**< DMF BIT */
	I2C_STAT2_PECV   = (1U << 8),	/**< PECV BIT */
} i2c_stat2_t;

/**
  * @brief I2C CKCFG Register
  */
typedef enum {
	I2C_CKCFG_CLKSET =  0xFFFU,    	/**< CLKSET BITS */
	I2C_CKCFG_DUTY   = (1U << 14),	/**< DUTY BIT */
	I2C_CKCFG_CLKMOD = (1U << 15),	/**< CLKMOD BIT */
} i2c_ckcfg_t;

/**
  * @brief I2C RT Register
  */
typedef enum {
	I2C_RT_RISET = 0x3FU,	/**< RISET BITS */
} i2c_trise_t;

/**
 * @brief I2C Configuration Structure definition
 */
typedef struct {
	uint32_t clk_speed;                	/**< Specifies the clock frequency */
	i2c_duty_t duty;			/**< Specifies the I2C fast mode duty cycle */
	uint32_t own_addr1;               	/**< Specifies the first device own address */
	i2c_addr_t addr_mode;			/**< Specifies addressing mode */
	i2c_dual_addr_t dual_addr;		/**< Specifies if dual addressing mode is selected */
	uint32_t own_addr2;               	/**< Specifies the second device own address */
	i2c_general_addr_t general_call;	/**< Specifies if general call mode is selected */
	i2c_nostretch_t no_stretch;     	/**< Specifies if nostretch mode is selected */
} i2c_init_t;

/**
  * @brief  I2C handle Structure definition
  */
typedef struct i2c_handle_s {
	I2C_TypeDef *perh;       	/**< I2C registers base address */
	i2c_init_t init;         	/**< I2C communication parameters */
	uint8_t *p_buff;         	/**< Pointer to I2C transfer buffer */
	uint16_t xfer_size;      	/**< I2C transfer size */
	__IO uint16_t xfer_count;	/**< I2C transfer counter */
#ifdef ALD_DMA
	dma_handle_t hdmatx;		/**< I2C Tx DMA handle parameters */
	dma_handle_t hdmarx;		/**< I2C Rx DMA handle parameters */
#endif
	lock_state_t lock;       	/**< I2C locking object */
	__IO i2c_state_t state;  	/**< I2C communication state */
	__IO i2c_mode_t mode;    	/**< I2C communication mode */
	__IO uint32_t error_code;	/**< I2C Error code */

	void (*master_tx_cplt_cbk)(struct i2c_handle_s *arg);	/**< Master Tx completed callback */
	void (*master_rx_cplt_cbk)(struct i2c_handle_s *arg);	/**< Master Rx completed callback */
	void (*slave_tx_cplt_cbk)(struct i2c_handle_s *arg); 	/**< Slave Tx completed callback */
	void (*slave_rx_cplt_cbk)(struct i2c_handle_s *arg); 	/**< Slave Rx completed callback */
	void (*mem_tx_cplt_cbk)(struct i2c_handle_s *arg);   	/**< Tx to Memory completed callback */
	void (*mem_rx_cplt_cbk)(struct i2c_handle_s *arg);   	/**< Rx from Memory completed callback */
	void (*error_callback)(struct i2c_handle_s *arg);    	/**< Error callback */
} i2c_handle_t;

/**
 * @}
 */

/** @defgroup I2C_Public_Macro I2C Public Macros
  * @{
  */
#define I2C_RESET_HANDLE_STATE(x) ((x)->state = I2C_STATE_RESET)
#define I2C_CLEAR_ADDRFLAG(x)		\
do {					\
	__IO uint32_t tmpreg;		\
	tmpreg = (x)->perh->STAT1;	\
	tmpreg = (x)->perh->STAT2;	\
	UNUSED(tmpreg);			\
} while (0)
#define __I2C_CLEAR_STOPFLAG(x)					\
do {								\
	__IO uint32_t tmpreg;					\
	tmpreg = (x)->perh->STAT1;				\
	tmpreg = SET_BIT((x)->perh->CON1, I2C_CON1_PEN);	\
	UNUSED(tmpreg);						\
} while (0)
#define I2C_ENABLE(x)  (SET_BIT((x)->perh->CON1, I2C_CON1_PEN_MSK))
#define I2C_DISABLE(x) (CLEAR_BIT((x)->perh->CON1, I2C_CON1_PEN_MSK))
/**
  * @}
  */

/** @defgroup I2C_Private_Macro I2C Private Macros
  * @{
  */
#define IS_I2C_TYPE(x)						(((x) == I2C0) || \
								 ((x) == I2C1))
#define IS_I2C_ADDRESSING_MODE(x)				(((x) == I2C_ADDR_7BIT) || \
								 ((x) == I2C_ADDR_10BIT))
#define IS_I2C_DUAL_ADDRESS(x)					(((x) == I2C_DUALADDR_DISABLE) || \
								 ((x) == I2C_DUALADDR_ENABLE))
#define IS_I2C_GENERAL_CALL(x)					(((x) == I2C_GENERALCALL_DISABLE) || \
								 ((x) == I2C_GENERALCALL_ENABLE))
#define IS_I2C_MEMADD_size(x)					(((x) == I2C_MEMADD_SIZE_8BIT) || \
								 ((x) == I2C_MEMADD_SIZE_16BIT))
#define IS_I2C_NO_STRETCH(x)					(((x) == I2C_NOSTRETCH_DISABLE) || \
								 ((x) == I2C_NOSTRETCH_ENABLE))
#define IS_I2C_OWN_ADDRESS1(x)					(((x) & (uint32_t)(0xFFFFFC00)) == 0)
#define IS_I2C_OWN_ADDRESS2(x)					(((x) & (uint32_t)(0xFFFFFF01)) == 0)
#define IS_I2C_CLOCK_SPEED(x)					(((x) > 0) && ((x) <= I2C_FAST_MODE_MAX_CLK))
#define IS_I2C_DUTY_CYCLE(x)					(((x) == I2C_DUTYCYCLE_2) || \
								 ((x) == I2C_DUTYCYCLE_16_9))
#define IS_I2C_IT_TYPE(x)					(((x) == I2C_IT_BUF) || \
								 ((x) == I2C_IT_EVT) || \
								 ((x) == I2C_IT_ERR))
#define IS_I2C_FLAG(x)						(((x) == I2C_FLAG_SB)         || \
								 ((x) == I2C_FLAG_ADDR)       || \
								 ((x) == I2C_FLAG_BTF)        || \
								 ((x) == I2C_FLAG_ADD10)      || \
								 ((x) == I2C_FLAG_STOPF)      || \
								 ((x) == I2C_FLAG_RXNE)       || \
								 ((x) == I2C_FLAG_TXE)        || \
								 ((x) == I2C_FLAG_BERR)       || \
								 ((x) == I2C_FLAG_ARLO)       || \
								 ((x) == I2C_FLAG_AF)         || \
								 ((x) == I2C_FLAG_OVR)        || \
								 ((x) == I2C_FLAG_PECERR)     || \
								 ((x) == I2C_FLAG_TIMEOUT)    || \
								 ((x) == I2C_FLAG_SMBALERT)   || \
								 ((x) == I2C_FLAG_MSL)        || \
								 ((x) == I2C_FLAG_BUSY)       || \
								 ((x) == I2C_FLAG_TRA)        || \
								 ((x) == I2C_FLAG_GENCALL)    || \
								 ((x) == I2C_FLAG_SMBDEFAULT) || \
								 ((x) == I2C_FLAG_SMBHOST)    || \
								 ((x) == I2C_FLAG_DUALF))

#define I2C_FREQ_RANGE(x)					((x) / 1000000)
#define I2C_RISE_TIME(x, u)					(((u) <= I2C_STANDARD_MODE_MAX_CLK) ? ((x) + 1) :\
        ((((x) * 300) / 1000) + 1))
#define I2C_SPEED_STANDARD(x, y)				(((((x) / ((y) << 1)) & I2C_CKCFG_CLKSET) < 4) ? 4:\
	((x) / ((y) << 1)))
#define I2C_SPEED_FAST(x, y, z)					(((z) == I2C_DUTYCYCLE_2) ? ((x) / ((y) * 3)) :\
        (((x) / ((y) * 25)) | I2C_DUTYCYCLE_16_9))
#define I2C_SPEED(x, y, z)					(((y) <= 100000) ? (I2C_SPEED_STANDARD((x), (y))) :\
	((I2C_SPEED_FAST((x), (y), (z)) & I2C_CKCFG_CLKSET) == 0) ? 1 : \
        ((I2C_SPEED_FAST((x), (y), (z))) | I2C_CKCFG_CLKMOD))
#define I2C_MEM_ADD_MSB(x)					((uint8_t)((uint16_t)(((uint16_t)((x) &\
        (uint16_t)(0xFF00))) >> 8)))
#define I2C_MEM_ADD_LSB(x)					((uint8_t)((uint16_t)((x) & (uint16_t)(0x00FF))))
#define I2C_7BIT_ADD_WRITE(x)					((uint8_t)((x) & (~I2C_ADDR1_ADDH0)))
#define I2C_7BIT_ADD_READ(x)					((uint8_t)((x) | I2C_ADDR1_ADDH0))
#define I2C_10BIT_ADDRESS(x)					((uint8_t)((uint16_t)((x) & (uint16_t)(0x00FF))))
#define I2C_10BIT_HEADER_WRITE(x)				((uint8_t)((uint16_t)((uint16_t)(((uint16_t)((x) &\
        (uint16_t)(0x0300))) >> 7) | (uint16_t)(0xF0))))
#define I2C_10BIT_HEADER_READ(x)				((uint8_t)((uint16_t)((uint16_t)(((uint16_t)((x) &\
       (uint16_t)(0x0300))) >> 7) | (uint16_t)(0xF1))))
/**
  * @}
  */

/** @addtogroup I2C_Public_Functions
  * @{
  */

/** @addtogroup I2C_Public_Functions_Group1
  * @{
  */
ald_status_t ald_i2c_init(i2c_handle_t *hperh);
ald_status_t ald_i2c_reset(i2c_handle_t *hperh);

/**
 * @}
 */

/** @addtogroup I2C_Public_Functions_Group2
 * @{
 */
 /** Blocking mode: Polling */
ald_status_t ald_i2c_master_send(i2c_handle_t *hperh, uint16_t dev_addr,
                                 uint8_t *buf, uint16_t size, uint32_t timeout);
ald_status_t ald_i2c_master_recv(i2c_handle_t *hperh, uint16_t dev_addr,
                                uint8_t *buf, uint16_t size, uint32_t timeout);
ald_status_t ald_i2c_slave_send(i2c_handle_t *hperh, uint8_t *buf, uint16_t size, uint32_t timeout);
ald_status_t ald_i2c_slave_recv(i2c_handle_t *hperh, uint8_t *buf, uint16_t size, uint32_t timeout);
ald_status_t ald_i2c_mem_write(i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr,
                           i2c_addr_size_t add_size, uint8_t *buf, uint16_t size, uint32_t timeout);
ald_status_t ald_i2c_mem_read(i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr,
                          i2c_addr_size_t add_size, uint8_t *buf, uint16_t size, uint32_t timeout);
ald_status_t ald_i2c_is_device_ready(i2c_handle_t *hperh, uint16_t dev_addr, uint32_t trials, uint32_t timeout);

 /** Non-Blocking mode: Interrupt */
ald_status_t ald_i2c_master_send_by_it(i2c_handle_t *hperh, uint16_t dev_addr, uint8_t *buf, uint16_t size);
ald_status_t ald_i2c_master_recv_by_it(i2c_handle_t *hperh, uint16_t dev_addr, uint8_t *buf, uint16_t size);
ald_status_t ald_i2c_slave_send_by_it(i2c_handle_t *hperh, uint8_t *buf, uint16_t size);
ald_status_t ald_i2c_slave_recv_by_it(i2c_handle_t *hperh, uint8_t *buf, uint16_t size);
ald_status_t ald_i2c_mem_write_by_it(i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr,
                              i2c_addr_size_t add_size, uint8_t *buf, uint16_t size);
ald_status_t ald_i2c_mem_read_by_it(i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr,
                             i2c_addr_size_t add_size, uint8_t *buf, uint16_t size);

#ifdef ALD_DMA
 /** Non-Blocking mode: DMA */
ald_status_t ald_i2c_master_send_by_dma(i2c_handle_t *hperh, uint16_t dev_addr,
                                     uint8_t *buf, uint16_t size, uint8_t channel);
ald_status_t ald_i2c_master_recv_by_dma(i2c_handle_t *hperh, uint16_t dev_addr,
                                    uint8_t *buf, uint16_t size, uint8_t channel);
ald_status_t ald_i2c_slave_send_by_dma(i2c_handle_t *hperh, uint8_t *buf, uint16_t size, uint8_t channel);
ald_status_t ald_i2c_slave_recv_by_dma(i2c_handle_t *hperh, uint8_t *buf, uint16_t size, uint8_t channel);
ald_status_t ald_i2c_mem_write_by_dma(i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr, i2c_addr_size_t add_size,
                                 uint8_t *buf, uint16_t size, uint8_t channel);
ald_status_t ald_i2c_mem_read_by_dma(i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr,
                                i2c_addr_size_t add_size, uint8_t *buf, uint16_t size, uint8_t channel);
#endif
/**
 * @}
 */

/** @addtogroup I2C_Public_Functions_Group3
  * @{
  */
i2c_state_t ald_i2c_get_state(i2c_handle_t *hperh);
uint32_t ald_i2c_get_error(i2c_handle_t *hperh);
flag_status_t ald_i2c_get_flag_status(i2c_handle_t *hperh, i2c_flag_t flag);
flag_status_t ald_i2c_get_it_status(i2c_handle_t *hperh, i2c_interrupt_t it);
void ald_i2c_clear_flag_status(i2c_handle_t *hperh, i2c_flag_t flag);
/**
 * @}
 */

/** @addtogroup I2C_Public_Functions_Group4
 * @{
 */
void ald_i2c_interrupt_config(i2c_handle_t *hperh, i2c_interrupt_t it, type_func_t state);
void ald_i2c_ev_irq_handler(i2c_handle_t *hperh);
void ald_i2c_er_irq_handler(i2c_handle_t *hperh);
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
