/**
  ******************************************************************************
  * @file    md_i2c.h
  * @brief   ES32F0271 I2C HEAD File.
  *
  * @version V0.01
  * @date    4/12/2018
  * @author  Eastsoft AE Team
  * @note
  * detailed description
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MD_I2C_H__
#define __MD_I2C_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -------------------------------------------------------------------*/ 
#include "es32f0271.h"
#include "reg_i2c.h"

/** @addtogroup Micro_Driver
  * @{
  */

#if defined (I2C1) | defined (I2C2)

/** @defgroup I2C I2C
  * @brief I2C micro driver
  * @{
  */
  
/* Private types --------------------------------------------------------------*/
/* Private variables ----------------------------------------------------------*/
/* Private constants ----------------------------------------------------------*/
/* Private macros -------------------------------------------------------------*/


/* Public Init Structure ------------------------------------------------------*/
/** @defgroup MD_I2C_PT_INIT I2C Public Init structure
  * @brief   I2C Init structure.
  * @{
  */
typedef struct
{
  uint32_t Timing;              /*!< Specifies the I2C_TIMINGR_register value.
                                     This parameter calculated by referring to I2C initialization section in Reference manual */

  uint32_t Address1;            /*!< Specifies the first device address.
                                     This parameter can be a 7-bit or 10-bit address. */

  uint32_t AddrSize;            /*!< Specifies the device address 1 size (7-bit or 10-bit).
                                     This parameter can be a value of @ref I2C_LL_EC_OWNADDRESS1

                                     This feature can be modified afterwards using unitary function @ref LL_I2C_SetOwnAddress1(). */
  
  uint32_t DualAddressMode;     /*!< Specifies if dual addressing mode is selected.
                                  This parameter can be a value of @ref I2C_DUAL_ADDRESSING_MODE */

  uint32_t Address2;         /*!< Specifies the second device own address if dual addressing mode is selected
                                  This parameter can be a 7-bit address. */

  uint32_t Address2Masks;    /*!< Specifies the acknowledge mask address second device own address if dual addressing mode is selected
                                  This parameter can be a value of @ref I2C_OWN_ADDRESS2_MASKS */
} md_i2c_inittypedef;
/**
  * @} MD_I2C_PT_INIT
  */

/* Public constants -----------------------------------------------------------*/
/** @defgroup MD_I2C_Public_Constants I2C Public Constants
  * @{
  */

/** @defgroup MD_I2C_ADDRESSING_MODE I2C Addressing Mode
  * @{
  */
#define MD_I2C_ADDRESSINGMODE_7BIT         (0x00000000U)                    /*!< DISABLE */
#define MD_I2C_ADDRESSINGMODE_10BIT        (I2C_CON2_ADD10_MSK)             /*!< I2C_CON2_ADD10_MSK = 1<<11 */
/**
  * @} MD_I2C_ADDRESSING_MODE
  */

/** @defgroup MD_I2C_DUAL_ADDRESSING_MODE I2C Dual Addressing Mode
  * @{
  */
#define MD_I2C_DUALADDRESS_DISABLE         (0x00000000U)                     /*!< DISABLE */
#define MD_I2C_DUALADDRESS_ENABLE          (I2C_ADDR2_OA2EN_MSK)             /*!< I2C_ADDR2_OA2EN_MSK = 1<<15 */
/**
  * @} MD_I2C_DUAL_ADDRESSING_MODE
  */

/** @defgroup MD_I2C_TIMING_CONFIG I2C Timing Config
  * @note   pllmul<<28|presc<<24|scll<<16|sclh<<8|sdadel<<4|scldel
  * @{
  */
/*                       pllmul    presc     scll       sclh     sdadel  scldel        */
#define CLK10kHz8M      (1<<28)  |(1<<24)  |(0xC7<<16)|(0xC3<<8)|(2<<4)|(4)            /*!< APB = 8MHz; CLK = 10kHz */
#define CLK100kHz8M     (1<<28)  |(1<<24)  |(0x13<<16)|(0xF<<8) |(2<<4)|(4)            /*!< APB = 8MHz; CLK = 100kHz */
#define CLK400kHz8M     (1<<28)  |(0<<24)  |(9<<16)   |(3<<8)   |(1<<4)|(3)            /*!< APB = 8MHz; CLK = 400kHz */
#define CLK500kHz8M     (1<<28)  |(0<<24)  |(6<<16)   |(3<<8)   |(0<<4)|(1)            /*!< APB = 8MHz; CLK = 500kHz */
#define CLK10kHz16M     (3<<28)  |(3<<24)  |(0xC7<<16)|(0xC3<<8)|(2<<4)|(4)            /*!< APB = 16MHz; CLK = 10kHz */
#define CLK100kHz16M    (3<<28)  |(3<<24)  |(0x13<<16)|(0xF<<8) |(2<<4)|(4)            /*!< APB = 16MHz; CLK = 100kHz */
#define CLK400kHz16M    (3<<28)  |(1<<24)  |(9<<16)   |(3<<8)   |(2<<4)|(3)            /*!< APB = 16MHz; CLK = 400kHz */
#define CLK1000kHz16M   (3<<28)  |(0<<24)  |(4<<16)   |(2<<8)   |(0<<4)|(2)            /*!< APB = 16MHz; CLK = 1000kHz */
#define CLK10kHz48M     (11U<<28)|(0xB<<24)|(0xC7<<16)|(0xC3<<8)|(2<<4)|(4)            /*!< APB = 48MHz; CLK = 10kHz */
#define CLK100kHz48M    (11U<<28)|(0xB<<24)|(0x13<<16)|(0xF<<8) |(2<<4)|(4)            /*!< APB = 48MHz; CLK = 100kHz */
#define CLK400kHz48M    (11U<<28)|(5<<24)  |(9<<16)   |(3<<8)   |(3<<4)|(3)            /*!< APB = 48MHz; CLK = 400kHz */
#define CLK1000kHz48M   (11U<<28)|(5<<24)  |(3<<16)   |(1<<8)   |(0<<4)|(1)            /*!< APB = 48MHz; CLK = 1000kHz */
/**
  * @} MD_I2C_TIMING_CONFIG
  */

/** @defgroup MD_I2C_ADDRESS2_MASKS I2C Address2 Masks
  * @{
  */
#define MD_I2C_ADDR2_NOMASK                  (0x0000U)              /*!< NOMASK */
#define MD_I2C_ADDR2_MASK01                  (0x0100U)              /*!< MASK01 */
#define MD_I2C_ADDR2_MASK02                  (0x0200U)              /*!< MASK02 */
#define MD_I2C_ADDR2_MASK03                  (0x0300U)              /*!< MASK03 */
#define MD_I2C_ADDR2_MASK04                  (0x0400U)              /*!< MASK04 */
#define MD_I2C_ADDR2_MASK05                  (0x0500U)              /*!< MASK05 */
#define MD_I2C_ADDR2_MASK06                  (0x0600U)              /*!< MASK06 */
#define MD_I2C_ADDR2_MASK07                  (0x0700U)              /*!< MASK07 */
/**
  * @} MD_I2C_ADDRESS2_MASKS
  */

/** @defgroup MD_I2C_GENERAL_CALL_ADDRESSING_MODE I2C General Call Addressing Mode
  * @{
  */
#define MD_I2C_GENERALCALL_DISABLE         (0x00000000U)              /*!< DISABLE */
#define MD_I2C_GENERALCALL_ENABLE          (I2C_CON1_GCEN_MSK)        /*!< I2C_CON1_GCEN_MSK = 1<<19 */
/**
  * @} MD_I2C_GENERAL_CALL_ADDRESSING_MODE
  */

/** @defgroup MD_I2C_NOSTRETCH_MODE I2C No-Stretch Mode
  * @{
  */
#define MD_I2C_NOSTRETCH_DISABLE           (0x00000000U)             /*!< DISABLE */
#define MD_I2C_NOSTRETCH_ENABLE            (I2C_CON1_NOSTRETCH_MSK)  /*!< I2C_CON1_NOSTRETCH_MSK = 1<<17 */
/**
  * @} MD_I2C_NOSTRETCH_MODE
  */

/** @defgroup MD_I2C_MODE I2C Mode
  * @{
  */
#define MD_I2C_MODE_NONE                ((uint8_t)0x00U              /*!< None */
#define MD_I2C_MODE_MASTER              ((uint8_t)0x10U)             /*!< Master */
#define MD_I2C_MODE_SLAVE               ((uint8_t)0x20U)             /*!< Slave */
#define MD_I2C_MODE_MEM                 ((uint8_t)0x40U)             /*!< Mem */
/**
  * @} MD_I2C_MODE
  */

/** @defgroup MD_I2C_PECBYTE_ENABLE Pecbyte Enable
  * @{
  */
#define MD_I2C_PECBYTE_ENABLE            I2C_CON2_PECBYTE_MSK        /*!< I2C_CON2_PECBYTE_MSK = 1<<26 */
/**
  * @} MD_I2C_PECBYTE_ENABLE
  */
  
/** @defgroup MD_I2C_AUTOEND_ENABLE I2C Autoend Enable
  * @{
  */
#define MD_I2C_SOFTEND_MODE            (0x00000000U)              /*!< DISABLE */
#define MD_I2C_AUTOEND_MODE            (I2C_CON2_AUTOEND_MSK)     /*!< I2C_CON2_AUTOEND_MSK = 1<<25 */
/**
  * @} MD_I2C_AUTOEND_ENABLE
  */
  
/** @defgroup MD_I2C_RELOAD_MODE I2C Reload Mode
  * @{
  */
#define MD_I2C_NORELOAD_MODE           (0x00000000U)              /*!< DISABLE */
#define MD_I2C_RELOAD_MODE             (I2C_CON2_RELOAD_MSK)      /*!< I2C_CON2_RELOAD_MSK = 1<<24 */
/**
  * @} MD_I2C_RELOAD_MODE
  */

/** @defgroup MD_I2C_NACKNOWLEDGE Acknowledge Generation
  * @{
  */
#define MD_I2C_ACK                          0x00000000U              /*!< ACK is sent after current received byte. */
#define MD_I2C_NACK                         I2C_CON2_NACK_MSK        /*!< NACK is sent after current received byte, I2C_CON2_NACK_MSK = 1<<15 */
/**
  * @} MD_I2C_NACKNOWLEDGE
  */
  
/** @defgroup MD_I2C_STOP_GENERATION Stop Generation
  * @{
  */
#define MD_I2C_STOP_GENERATION            I2C_CON2_STOP_MSK        /*!< I2C_CON2_STOP_MSK = 1<<14 */
/**
  * @} MD_I2C_STOP_GENERATION
  */
  
/** @defgroup MD_I2C_START_GENERATION Start Generation
  * @{
  */
#define MD_I2C_START_GENERATION           I2C_CON2_START_MSK       /*!< I2C_CON2_PECBYTE_MSK = 1<<13 */
/**
  * @} MD_I2C_START_GENERATION
  */

/** @defgroup MD_I2C_HEAD10R Acknowledge Generation
  * @{
  */
#define MD_I2C_GENERAL_10BIT_READ                        0x00000000U                 /*!< DISABLE */
#define MD_I2C_SIMPLIFIED_10BIT_READ                     I2C_CON2_HEAD10R_MSK        /*!< I2C_CON2_HEAD10R_MSK = 1<<12 */
/**
  * @} MD_I2C_HEAD10R
  */

/** @defgroup MD_I2C_TRANSFER_DIRECTION Transfer direction (master mode) 
  * @{
  */
#define MD_I2C_MASTER_WRITE                    0x00000000U                           /*!< Master Write */
#define MD_I2C_MASTER_READ                     I2C_CON2_RD_WRN_MSK                   /*!< I2C_CON2_RD_WRN_MSK = 1<<10 */
/**
  * @} MD_I2C_TRANSFER_DIRECTION
  */
  
/** @defgroup MD_I2C_OA1_MODE Own Address 1 mode 
  * @{
  */
#define MD_I2C_OA1_7BIT                      0x00000000U                           /*!< OA1 7-bit mode */
#define MD_I2C_OA1_10BIT                     I2C_ADDR1_OA1MODE_MSK                 /*!< I2C_ADDR1_OA1MODE_MSK = 1<<10 */
/**
  * @} MD_I2C_OA1_MODE
  */

/** @defgroup MD_I2C_TIDLE_MODE Tidle  mode 
  * @{
  */
#define MD_I2C_LOW_TIMEOUTA                      0x00000000U                           /*!< TIMEOUTA is used to detect SCL low timeout */
#define MD_I2C_IDLE_TIMEOUTA                     I2C_TIMEOUTR_TIDLE_MSK                /*!< TIMEOUTA is used to detectbus idle condition, I2C_TIMEOUTR_TIDLE_MSK = 1<<12 */
/**
  * @} MD_I2C_TIDLE_MODE
  */

/** @defgroup MD_I2C_RXFIFO_THRESHOLD FIFO Threshold 
  * @{
  */
#define MD_I2C_RXFIFO_THRESHOLD_RX1                      0U<<I2C_FCON_RXFTH_POSS                /*!< 1 character in the FIFO, I2C_FCON_RXFTH_POSS = 1<<14 */
#define MD_I2C_RXFIFO_THRESHOLD_RX4                      1U<<I2C_FCON_RXFTH_POSS                /*!< 4 characters in the FIFO, I2C_FCON_RXFTH_POSS = 1<<14 */
#define MD_I2C_RXFIFO_THRESHOLD_RX8                      2U<<I2C_FCON_RXFTH_POSS                /*!< 8 characters in the FIFO, I2C_FCON_RXFTH_POSS = 1<<14 */
#define MD_I2C_RXFIFO_THRESHOLD_RX14                     3U<<I2C_FCON_RXFTH_POSS                /*!< 14 characters in the FIFO, I2C_FCON_RXFTH_POSS = 1<<14 */
/**
  * @} MD_I2C_RXFIFO_THRESHOLD
  */
  
/** @defgroup MD_I2C_RXFIFO_RESET Rx FIFO Reset
  * @{
  */
#define MD_I2C_RXFIFO_RESET           I2C_FCON_RXFRST_MSK       /*!< I2C_FCON_RXFRST_MSK = 1<<13 */
/**
  * @} MD_I2C_RXFIFO_RESET
  */
  
/** @defgroup MD_I2C_TXFIFO_THRESHOLD FIFO Threshold 
  * @{
  */
#define MD_I2C_TXFIFO_THRESHOLD_TX0                      0U<<I2C_FCON_TXFTH_POSS                /*!< 0 character in the FIFO, I2C_FCON_TXFTH_POSS = 1<<6 */
#define MD_I2C_TXFIFO_THRESHOLD_TX2                      1U<<I2C_FCON_TXFTH_POSS                /*!< 2 characters in the FIFO, I2C_FCON_TXFTH_POSS = 1<<6 */
#define MD_I2C_TXFIFO_THRESHOLD_TX4                      2U<<I2C_FCON_TXFTH_POSS                /*!< 4 characters in the FIFO, I2C_FCON_TXFTH_POSS = 1<<6 */
#define MD_I2C_TXFIFO_THRESHOLD_TX8                      3U<<I2C_FCON_TXFTH_POSS                /*!< 8 characters in the FIFO, I2C_FCON_TXFTH_POSS = 1<<6 */
/**
  * @} MD_I2C_TXFIFO_THRESHOLD
  */

/** @defgroup MD_I2C_TXFIFO_RESET Tx FIFO Reset
  * @{
  */
#define MD_I2C_TXFIFO_RESET           I2C_FCON_TXFRST_MSK       /*!< I2C_FCON_TXFRST_MSK = 1<<5 */
/**
  * @} MD_I2C_TXFIFO_RESET
  */

/**
  * @} MD_I2C_Public_Constants
  */

/* Public macro ---------------------------------------------------------------*/
/** @defgroup MD_I2C_Public_Macros I2C Public Macros
  * @{
  */

/**
  * @brief  I2C Set CON1
  * @note   These bits must be configured when the I2C is disabled (PE = 0) except TXDMAEN and RXDMAEN.
  * @param  I2Cx I2C Instance
  * @param  Reg_Value is a 32-bit value
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_con1(I2C_TypeDef *I2Cx, uint32_t Reg_Value)
{
  WRITE_REG(I2Cx->CON1, Reg_Value);
}

/**
  * @brief  I2C Get CON1
  * @note   None
  * @param  I2Cx I2C Instance
  * @retval a 32-bit value
  */
__STATIC_INLINE uint32_t md_i2c_get_con1(I2C_TypeDef *I2Cx)
{
  return (uint32_t) (READ_REG(I2Cx->CON1));
}

/**
  * @brief  I2C PEC Enable
  * @note   If the SMBus feature is not supported,this bit is reserved and forced by hardware to 0.
  *         This register must be configured when the I2C is disabled (PE = 0). 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_con1_pecen(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->CON1, I2C_CON1_PECEN_MSK);
}

/**
  * @brief  I2C PEC Disable
  * @note   If the SMBus feature is not supported,this bit is reserved and forced by hardware to 0.
  *         This register must be configured when the I2C is disabled (PE = 0).
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_con1_pecen(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->CON1, I2C_CON1_PECEN_MSK);
}

/**
  * @brief  Indicate if I2C PEC is enabled
  * @note   If the SMBus feature is not supported,this bit is reserved and forced by hardware to '0'
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_con1_pecen(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->CON1, I2C_CON1_PECEN_MSK) == (I2C_CON1_PECEN_MSK));
}

/**
  * @brief  I2C Alert Enable
  * @note   When ALERTEN = 0, the SMBA pin can be used as a standard GPIO.If the SMBus feature is not supported, this bit is reserved and forced by hardware to 0.
  *         This register must be configured when the I2C is disabled (PE = 0).
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_con1_alerten(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->CON1, I2C_CON1_ALERTEN_MSK);
}

/**
  * @brief  I2C Alert Disable
  * @note   When ALERTEN = 0, the SMBA pin can be used as a standard GPIO.If the SMBus feature is not supported, this bit is reserved and forced by hardware to 0.
  *         This register must be configured when the I2C is disabled (PE = 0).
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_con1_alerten(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->CON1, I2C_CON1_ALERTEN_MSK);
}

/**
  * @brief  Indicate if I2C PEC is enabled
  * @note   When ALERTEN = 0, the SMBA pin can be used as a standard GPIO.If the SMBus feature is not supported, this bit is reserved and forced by hardware to 0.
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_con1_alerten(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->CON1, I2C_CON1_ALERTEN_MSK) == (I2C_CON1_ALERTEN_MSK));
}

/**
  * @brief  I2C SMBus Device Default address Enable
  * @note   If the SMBus feature is not supported,this bit is reserved and forced by hardware to 0. Device default address 0b1100 001.
  *         This register must be configured when the I2C is disabled (PE = 0).
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_con1_smbden(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->CON1, I2C_CON1_SMBDEN_MSK);
}

/**
  * @brief  I2C SMBus Device Default address Disable
  * @note   If the SMBus feature is not supported,this bit is reserved and forced by hardware to 0. Device default address 0b1100 001.
  *         This register must be configured when the I2C is disabled (PE = 0).
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_con1_smbden(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->CON1, I2C_CON1_SMBDEN_MSK);
}

/**
  * @brief  Indicate if I2C SMBus Device Default address is enabled
  * @note   If the SMBus feature is not supported,this bit is reserved and forced by hardware to 0. Device default address 0b1100 001.
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_con1_smbden(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->CON1, I2C_CON1_SMBDEN_MSK) == (I2C_CON1_SMBDEN_MSK));
}

/**
  * @brief  I2C SMBus Host address Enable
  * @note   If the SMBus feature is not supported,this bit is reserved and forced by hardware to 0. Host default address 0b0001 000.
  *         This register must be configured when the I2C is disabled (PE = 0).
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_con1_smbhen(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->CON1, I2C_CON1_SMBHEN_MSK);
}

/**
  * @brief  I2C SMBus Host address Disable
  * @note   If the SMBus feature is not supported,this bit is reserved and forced by hardware to 0. Host default address 0b0001 000.
  *         This register must be configured when the I2C is disabled (PE = 0).
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_con1_smbhen(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->CON1, I2C_CON1_SMBHEN_MSK);
}

/**
  * @brief  Indicate if I2C SMBus Host address is enabled
  * @note   If the SMBus feature is not supported,this bit is reserved and forced by hardware to 0. Host default address 0b0001 000.
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_con1_smbhen(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->CON1, I2C_CON1_SMBHEN_MSK) == (I2C_CON1_SMBHEN_MSK));
}

/**
  * @brief  I2C general call Enable
  * @note   This register must be configured when the I2C is disabled (PE = 0).
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_con1_gcen(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->CON1, I2C_CON1_GCEN_MSK);
}

/**
  * @brief  I2C general call Disable
  * @note   This register must be configured when the I2C is disabled (PE = 0).
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_con1_gcen(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->CON1, I2C_CON1_GCEN_MSK);
}

/**
  * @brief  Indicate if I2C general call is enabled
  * @note   None
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_con1_gcen(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->CON1, I2C_CON1_GCEN_MSK) == (I2C_CON1_GCEN_MSK));
}

/**
  * @brief  I2C clock stretching Disable
  * @note   Clock stretching disables. This bit can only be programmed when the I2C is disabled(PE = 0)
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_con1_nostretch(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->CON1, I2C_CON1_NOSTRETCH_MSK);
}

/**
  * @brief  I2C clock stretching Enable
  * @note   Clock stretching enables.This bit can only be programmed when the I2C is disabled(PE = 0)
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_con1_nostretch(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->CON1, I2C_CON1_NOSTRETCH_MSK);
}

/**
  * @brief  Indicate if I2C clock nostretching is enabled
  * @note   This bit can only be programmed when the I2C is disabled(PE = 0)
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_con1_nostretch(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->CON1, I2C_CON1_NOSTRETCH_MSK) == (I2C_CON1_NOSTRETCH_MSK));
}

/**
  * @brief  I2C slave byte control Enable
  * @note   This bit can only be programmed when the I2C is disabled(PE = 0)
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_con1_sbc(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->CON1, I2C_CON1_SBC_MSK);
}

/**
  * @brief  I2C slave byte control Disable
  * @note   This bit can only be programmed when the I2C is disabled(PE = 0)
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_con1_sbc(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->CON1, I2C_CON1_SBC_MSK);
}

/**
  * @brief  Indicate if I2C slave byte control is enabled
  * @note   None
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_con1_sbc(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->CON1, I2C_CON1_SBC_MSK) == (I2C_CON1_SBC_MSK));
}

/**
  * @brief  I2C DMA reception requests Enable
  * @note   None
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_con1_rxdmaen(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->CON1, I2C_CON1_RXDMAEN_MSK);
}

/**
  * @brief  I2C DMA reception requests Disable
  * @note   None
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_con1_rxdmaen(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->CON1, I2C_CON1_RXDMAEN_MSK);
}

/**
  * @brief  Indicate if I2C DMA reception requests is enabled
  * @note   None
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_con1_rxdmaen(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->CON1, I2C_CON1_RXDMAEN_MSK) == (I2C_CON1_RXDMAEN_MSK));
}

/**
  * @brief  I2C DMA transmission requests Enable
  * @note   None
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_con1_txdmaen(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->CON1, I2C_CON1_TXDMAEN_MSK);
}

/**
  * @brief  I2C DMA transmission requests Disable
  * @note   None
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_con1_txdmaen(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->CON1, I2C_CON1_TXDMAEN_MSK);
}

/**
  * @brief  Indicate if I2C DMA transmission requests is enabled
  * @note   None
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_con1_txdmaen(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->CON1, I2C_CON1_TXDMAEN_MSK) == (I2C_CON1_TXDMAEN_MSK));
}

/**
  * @brief  Set I2C digital noise filter
  * @note   If the analog filter is also enabled,the digital filter is added to the analog filter.
  *         This filter can only be programmed when the I2C is disabled(PE = 0)
  * @param  I2Cx I2C Instance
  * @param  filter_capability digital noise filter capability
  *         @arg Max Value 0xFF
  *         @arg Min Value 0
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_con1_dnf(I2C_TypeDef *I2Cx, uint32_t filter_capability)
{
  MODIFY_REG(I2Cx->CON1, I2C_CON1_DNF_MSK, filter_capability<<I2C_CON1_DNF_POSS);
}

/**
  * @brief  Get I2C digital noise filter
  * @note   If the analog filter is also enabled,the digital filter is added to the analog filter.
  *         This filter can only be programmed when the I2C is disabled(PE = 0)
  * @param  I2Cx I2C Instance
  * @retval filter_capability digital noise filter capability
  */
__STATIC_INLINE uint32_t md_i2c_get_con1_dnf(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->CON1, I2C_CON1_DNF_MSK)>>I2C_CON1_DNF_POSS);
}

/**
  * @brief  I2C Peripheral Enable
  * @note   When PE = 0, the I2C SCL and SDA lines are released.
  *         Internal state machines and status bits are put back to their reset value.
  *         When cleared, PE must be kept low for at least 3 APB clock cycles.
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_con1_pe(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->CON1, I2C_CON1_PE_MSK);
}

/**
  * @brief  I2C Peripheral Disable
  * @note   When PE = 0, the I2C SCL and SDA lines are released.Internal state machines and status bits are put back to their reset value.When cleared,PE must be kept low for at least 3 APB clock cycles
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_con1_pe(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->CON1, I2C_CON1_PE_MSK);
}

/**
  * @brief  Indicate if Peripheral is enabled
  * @note   When PE = 0, the I2C SCL and SDA lines are released.Internal state machines and status bits are put back to their reset value.When cleared,PE must be kept low for at least 3 APB clock cycles
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_con1_pe(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->CON1, I2C_CON1_PE_MSK) == (I2C_CON1_PE_MSK));
}

/**
  * @brief  I2C Set CON2
  * @note   None
  * @param  I2Cx I2C Instance
  * @param  Reg_Value is a 32-bit value
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_con2(I2C_TypeDef *I2Cx, uint32_t Reg_Value)
{
  WRITE_REG(I2Cx->CON2, Reg_Value);
}

/**
  * @brief  I2C Get CON2
  * @note   None
  * @param  I2Cx I2C Instance
  * @retval a 32-bit value
  */
__STATIC_INLINE uint32_t md_i2c_get_con2(I2C_TypeDef *I2Cx)
{
  return (uint32_t) (READ_REG(I2Cx->CON2));
}

/**
  * @brief  I2C Set ACK Update
  * @note   None
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_con2_ack_upd(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->CON2, I2C_CON2_ACK_UPD_MSK);
}

/**
  * @brief  I2C Hold Ack Enable
  * @note   None
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_con2_holdack(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->CON2, I2C_CON2_HOLDACK_MSK);
}

/**
  * @brief  I2C Hold Ack Disable
  * @note   None
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_con2_holdack(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->CON2, I2C_CON2_HOLDACK_MSK);
}

/**
  * @brief  Indicate if I2C Hold Ack is enabled
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_con2_holdack(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->CON2, I2C_CON2_HOLDACK_MSK) == (I2C_CON2_HOLDACK_MSK));
}

/**
  * @brief  Set I2C Packet error checking byte
  * @note   This bit is set by software, and cleared by hardware when the PEC is transferred,
  *         or when a STOP condition or an Address matched is received, also when PE=0. 
  *         Writing 0 to this bit has no effet. This bit has no effect when RELOAD is set,
  *         and when SBC is 0 in the slave mode.
  *         If the SMBus feature is not supported, this bit is reserved and forced by hardware to 0.
  * @param  I2Cx I2C Instance
  * @param  setbit 
  *         @arg @ref MD_I2C_PECBYTE_ENABLE
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_con2_pecbyte(I2C_TypeDef *I2Cx, uint32_t setbit)
{
  MODIFY_REG(I2Cx->CON2, I2C_CON2_PECBYTE_MSK, setbit);
}

/**
  * @brief  Get I2C Packet error checking byte
  * @note   This bit is set by software, and cleared by hardware when the PEC is transferred,
  *         or when a STOP condition or an Address matched is received, also when PE=0. 
  *         Writing 0 to this bit has no effet. This bit has no effect when RELOAD is set,
  *         and when SBC is 0 in the slave mode.
  *         If the SMBus feature is not supported, this bit is reserved and forced by hardware to 0.
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_get_con2_pecbyte(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->CON2, I2C_CON2_PECBYTE_MSK)>>I2C_CON2_PECBYTE_POS);
}

/**
  * @brief  Set I2C automatic end mode or software end mode(master mode) 
  * @note   This bit has no effect in slave mode or when the RELOAD bit is set.
  *         Software end mode: TC flag is set when NBYTES data are transferred, stretching SCL low.
  *         Automatic end mode: a STOP condition is automatically sent when NBYTES data are transferred. 
  * @param  I2Cx I2C Instance
  * @param  setbit 
  *         @arg @ref MD_I2C_SOFTEND_MODE 
  *         @arg @ref MD_I2C_AUTOEND_MODE 
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_con2_autoend(I2C_TypeDef *I2Cx, uint32_t setbit)
{
  MODIFY_REG(I2Cx->CON2, I2C_CON2_AUTOEND_MSK, setbit);
}

/**
  * @brief  Get I2C automatic or software end mode(master mode) 
  * @note   This bit has no effect in slave mode or when the RELOAD bit is set.
  *         Software end mode: TC flag is set when NBYTES data are transferred, stretching SCL low.
  *         Automatic end mode: a STOP condition is automatically sent when NBYTES data are transferred. 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_get_con2_autoend(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->CON2, I2C_CON2_AUTOEND_MSK)>>I2C_CON2_AUTOEND_POS);
}

/**
  * @brief  Set I2C NBYTES reload mode or not
  * @note   RELOAD = 0: The transfer is completed after the NBYTES data transfer (STOP or RESTART will follow).
  *         RELOAD = 1: The transfer is not completed after the NBYTES data transfer (NBYTES will be reloaded).
  *                     TCR flag is set when NBYTES data are transferred, stretching SCL low.
  * @param  I2Cx I2C Instance
  * @param  setbit 
  *         @arg @ref MD_I2C_NORELOAD_MODE
  *         @arg @ref MD_I2C_RELOAD_MODE 
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_con2_reload(I2C_TypeDef *I2Cx, uint32_t setbit)
{
  MODIFY_REG(I2Cx->CON2, I2C_CON2_RELOAD_MSK, setbit);
}

/**
  * @brief  Get I2C RELOAD value
  * @note   RELOAD = 0: The transfer is completed after the NBYTES data transfer (STOP or RESTART will follow).
  *         RELOAD = 1: The transfer is not completed after the NBYTES data transfer (NBYTES will be reloaded).
  *                     TCR flag is set when NBYTES data are transferred, stretching SCL low.
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_get_con2_reload(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->CON2, I2C_CON2_RELOAD_MSK)>>I2C_CON2_RELOAD_POS);
}

/**
  * @brief  Set I2C number of bytes
  * @note   The number of bytes to be transmitted/received is programmed there. 
  *         This field is don¡¯t care in slave mode with SBC=0.
  *         Changing these bits when the START bit is set is not allowed.
  * @param  I2Cx I2C Instance
  * @param  nbytes number of bytes
  *         @arg Max Value 0xFF
  *         @arg Min Value 0x0
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_con2_nbytes(I2C_TypeDef *I2Cx, uint32_t nbytes)
{
  MODIFY_REG(I2Cx->CON2, I2C_CON2_NBYTES_MSK, nbytes<<I2C_CON2_NBYTES_POSS);
}

/**
  * @brief  Get I2C number of bytes
  * @note   The number of bytes to be transmitted/received is programmed there. 
  *         This field is don¡¯t care in slave mode with SBC=0.
  *         Changing these bits when the START bit is set is not allowed.
  * @param  I2Cx I2C Instance
  * @retval The retval can be a value of the area:
  *         @arg Max Value 0xFF
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint32_t md_i2c_get_con2_nbytes(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->CON2, I2C_CON2_NBYTES_MSK)>>I2C_CON2_NBYTES_POSS);
}

/**
  * @brief  Set I2C NACK generation(slave mode)
  * @note   Writing 0 to this bit has no effect. This bit is used in slave mode only.
  *         When an overrun occurs in slave receiver NOSTRETCH mode,a NACK is automatically generated whatever the NACK bit value.
  *         When hardware PEC checking is enabled(PECBYTE = 1),the PEC acknowledge value does not depend on the NACK value.
  * @param  I2Cx I2C Instance
  * @param  nack nack generation
  *         @arg @ref MD_I2C_NACK
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_con2_nack(I2C_TypeDef *I2Cx, uint32_t nack)
{
  MODIFY_REG(I2Cx->CON2, I2C_CON2_NACK_MSK, nack);
}

/**
  * @brief  Get I2C NACK bit state(slave mode)
  * @note   NACK=1: will generate NACK
  *         NACK=0: will generate ACK
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_get_con2_nack(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->CON2, I2C_CON2_NACK_MSK)>>I2C_CON2_NACK_POS);
}

/**
  * @brief  Set I2C Stop generation(master mode)
  * @note   Writing 0 to this bit has no effect.
  * @param  I2Cx I2C Instance
  * @param  stop_generate stop generate
  *         @arg MD_I2C_STOP_GENERATION 
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_con2_stop(I2C_TypeDef *I2Cx, uint32_t stop_generate)
{
  MODIFY_REG(I2Cx->CON2, I2C_CON2_STOP_MSK, stop_generate);
}

/**
  * @brief  Get I2C state of STOP bit(master mode)
  * @note   Writing 0 to this bit has no effect.
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_get_con2_stop(I2C_TypeDef *I2Cx)
{
   return (READ_BIT(I2Cx->CON2, I2C_CON2_STOP_MSK)>>I2C_CON2_STOP_POS);
}

/**
  * @brief  Set I2C Start generation
  * @note   Writing 0 to this bit has no effect.The START bit can be set even if the bus is BUSY or I2C is in slave mode.
  *         In 10-bit addressing mode, if a NACK is received on the first part of the address, 
  *         the START bit is not cleared by hardware and the master will resend the address sequence.
  * @param  I2Cx I2C Instance
  * @param  start_generate stop generate
  *         @arg MD_I2C_START_GENERATION
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_con2_start(I2C_TypeDef *I2Cx, uint32_t start_generate)
{
  MODIFY_REG(I2Cx->CON2, I2C_CON2_START_MSK, start_generate);
}

/**
  * @brief  Get I2C state of START bit
  * @note   None
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_get_con2_start(I2C_TypeDef *I2Cx)
{
   return (READ_BIT(I2Cx->CON2, I2C_CON2_START_MSK)>>I2C_CON2_START_POS);
}

/**
  * @brief  Set the master operates in 10-bit addressing mode(master receiver mode)
  * @note   Changing this bit when the START bit is set is not allowed. 
  *         It can be used when the 10-bit transmission was done before.
  * @param  I2Cx I2C Instance
  * @param  read_header format of read header
  *         @arg @ref MD_I2C_GENERAL_10BIT_READ 
  *         @arg @ref MD_I2C_SIMPLIFIED_10BIT_READ
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_con2_head10r(I2C_TypeDef *I2Cx, uint32_t read_header)
{
  MODIFY_REG(I2Cx->CON2, I2C_CON2_HEAD10R_MSK, read_header);
}

/**
  * @brief  Indicate if I2C 10-bit address header only read direction is enabled(master receiver mode)
  * @note   None
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_get_con2_head10r(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->CON2, I2C_CON2_HEAD10R_MSK)>>I2C_CON2_HEAD10R_POS);
}

/**
  * @brief  I2C 10-bit addressing mode Enable(master mode)
  * @note   Changing this bit when the START bit is set is not allowed.
  * @param  I2Cx I2C Instance
  * @param  addrmode
            @arg @ref MD_I2C_ADDRESSINGMODE_7BIT
            @arg @ref MD_I2C_ADDRESSINGMODE_10BIT
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_con2_add10(I2C_TypeDef *I2Cx, uint32_t addrmode)
{
  MODIFY_REG(I2Cx->CON2, I2C_CON2_ADD10_MSK, addrmode);
}

/**
  * @brief  Get I2C addressing mode is 10-bit or 7-bit mode(master mode)
  * @note   ADD10=1: 10-bit mode
  *         ADD10=0: 7-bit mode
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_get_con2_add10(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->CON2, I2C_CON2_ADD10_MSK)>>I2C_CON2_ADD10_POS);
}

/**
  * @brief  Set Master transfer direction(master mode)
  * @note   Changing this bit when the START bit is set is not allowed.
  * @param  I2Cx I2C Instance
  * @param  direction
  *         @arg @ref MD_I2C_MASTER_WRITE
  *         @arg @ref MD_I2C_MASTER_READ
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_con2_rd_wrn(I2C_TypeDef *I2Cx, uint32_t direction)
{
  MODIFY_REG(I2Cx->CON2, I2C_CON2_RD_WRN_MSK, direction);
}

/**
  * @brief  Get Master transfer direction(master mode)
  * @note   None
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_get_con2_rd_wrn(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->CON2, I2C_CON2_RD_WRN_MSK)>>I2C_CON2_RD_WRN_POS);
}

/**
  * @brief  Set I2C slave address(master mode)
  * @note   Changing these bits when the START bit is set is not allowed
  *         For 7-bit mode, bit 7 to 1 are valid; for 10-bit mode, all 10 bits are valid.
  * @param  I2Cx I2C Instance
  * @param  slave_addr I2C slave address
  *         @arg Max Value 7-bit: 0xFF / 10-bit: 0x3FF
  *         @arg Min Value 7-bit: 0x2 / 10-bit: 0x1
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_con2_sadd(I2C_TypeDef *I2Cx, uint32_t slave_addr)
{
  MODIFY_REG(I2Cx->CON2, I2C_CON2_SADD_MSK, slave_addr);
}

/**
  * @brief  Get I2C slave address(master mode)
  * @note   Changing these bits when the START bit is set is not allowed
  *         For 7-bit mode, bit 7 to 1 are valid; for 10-bit mode, all 10 bits are valid.
  * @param  I2Cx I2C Instance
  * @retval I2C slave address
  *         @arg Max Value 7-bit: 0xFF / 10-bit: 0x3FF
  *         @arg Min Value 7-bit: 0x2 / 10-bit: 0x1
  */
__STATIC_INLINE uint32_t md_i2c_get_sadd_7bit(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->CON2, I2C_CON2_SADD_MSK));
}

/**
  * @brief  Set I2C ADDR1
  * @note   These bits can be written only when OA1EN=0 except OA1EN.
  * @param  I2Cx I2C Instance
  * @param  Reg_Value is a 32-bit value
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_addr1(I2C_TypeDef *I2Cx, uint32_t Reg_Value)
{
  WRITE_REG(I2Cx->ADDR1, Reg_Value);
}

/**
  * @brief  Get I2C ADDR1
  * @note   None
  * @param  I2Cx I2C Instance
  * @retval a 32-bit value
  */
__STATIC_INLINE uint32_t md_i2c_get_addr1(I2C_TypeDef *I2Cx)
{
  return (uint32_t) (READ_REG(I2Cx->ADDR1));
}

/**
  * @brief  I2C address register 1 Enable
  * @note   None
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_addr1_oa1en(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->ADDR1, I2C_ADDR1_OA1EN_MSK);
}

/**
  * @brief  I2C address register 1 Disable
  * @note   None
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_addr1_oa1en(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->ADDR1, I2C_ADDR1_OA1EN_MSK);
}

/**
  * @brief  Indicate if address register 1 is enabled
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_addr1_oa1en(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->ADDR1, I2C_ADDR1_OA1EN_MSK) == (I2C_ADDR1_OA1EN_MSK));
}

/**
  * @brief  Set I2C OA1 bit mode
  * @param  I2Cx I2C Instance
  * @param  oa1mode
  *         @arg @ref MD_I2C_OA1_7BIT
  *         @arg @ref MD_I2C_OA1_10BIT
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_addr1_oa1mode(I2C_TypeDef *I2Cx, uint32_t oa1mode)
{
  MODIFY_REG(I2Cx->ADDR1, I2C_ADDR1_OA1MODE_MSK, oa1mode);
}

/**
  * @brief  Get I2C own address 1 mode
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_get_addr1_oa1mode(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->ADDR1, I2C_ADDR1_OA1MODE_MSK)>>I2C_ADDR1_OA1MODE_POS);
}

/**
  * @brief  Set I2C address1
  * @note   For 7-bit mode, bit 7 to 1 are valid; for 10-bit mode, all 10 bits are valid.
  * @param  I2Cx I2C Instance
  * @param  own_addr I2C own address1
  *         @arg Max Value 7-bit: 0xFF / 10-bit: 0x3FF
  *         @arg Min Value 7-bit: 0x2 / 10-bit: 0x1
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_addr1_oa1(I2C_TypeDef *I2Cx, uint32_t own_addr)
{
  MODIFY_REG(I2Cx->ADDR1, I2C_ADDR1_OA1_MSK, own_addr);
}

/**
  * @brief  Get I2C address1
  * @note   For 7-bit mode, bit 7 to 1 are valid; for 10-bit mode, all 10 bits are valid.
  * @param  I2Cx I2C Instance
  * @retval I2C own address1
  *         @arg Max Value 7-bit: 0xFF / 10-bit: 0x3FF
  *         @arg Min Value 7-bit: 0x2 / 10-bit: 0x1
  */
__STATIC_INLINE uint32_t md_i2c_get_addr1_oa1(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->ADDR1, I2C_ADDR1_OA1_MSK));
}

/**
  * @brief  Set I2C ADDR2
  * @note   These bits can be written only when OA2EN=0 except OA2EN.
  * @param  I2Cx I2C Instance
  * @param  Reg_Value is a 32-bit value
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_addr2(I2C_TypeDef *I2Cx, uint32_t Reg_Value)
{
  WRITE_REG(I2Cx->ADDR2, Reg_Value);
}

/**
  * @brief  Get I2C ADDR2
  * @note   None
  * @param  I2Cx I2C Instance
  * @retval a 32-bit value
  */
__STATIC_INLINE uint32_t md_i2c_get_addr2(I2C_TypeDef *I2Cx)
{
  return (uint32_t) (READ_REG(I2Cx->ADDR2));
}

/**
  * @brief  I2C own address register 2 Enable
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_addr2_oa2en(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->ADDR2, I2C_ADDR2_OA2EN_MSK);
}

/**
  * @brief  I2C own address register 2 Disable
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_addr2_oa2en(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->ADDR2, I2C_ADDR2_OA2EN_MSK);
}

/**
  * @brief  Indicate if address register 2 is enabled
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_addr2_oa2en(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->ADDR2, I2C_ADDR2_OA2EN_MSK) == (I2C_ADDR2_OA2EN_MSK));
}

/**
  * @brief  Set I2C own address2 mask
  * @note   These bits can be written only when OA2EN=0.
  *         As soon as OA2MSK is not equal to 0,the reserved I2C addresses(0b0000xxx and 0b1111xxx) are not acknowledged even if the comparison matches.
  * @param  I2Cx I2C Instance
  * @param  oa2_mask I2C own address2 mask
  *         @arg @ref MD_I2C_ADDR2_NOMASK
  *         @arg @ref MD_I2C_ADDR2_MASK01
  *         @arg @ref MD_I2C_ADDR2_MASK02
  *         @arg @ref MD_I2C_ADDR2_MASK03
  *         @arg @ref MD_I2C_ADDR2_MASK04
  *         @arg @ref MD_I2C_ADDR2_MASK05
  *         @arg @ref MD_I2C_ADDR2_MASK06
  *         @arg @ref MD_I2C_ADDR2_MASK07
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_addr2_oa2mask(I2C_TypeDef *I2Cx, uint32_t oa2_mask)
{
  MODIFY_REG(I2Cx->ADDR2, I2C_ADDR2_OA2MSK_MSK, oa2_mask);
}

/**
  * @brief  Get I2C address2 mask
  * @note   None
  *         As soon as OA2MSK is not equal to 0,the reserved I2C addresses(0b0000xxx and 0b1111xxx) are not acknowledged even if the comparison matches.
  * @param  I2Cx I2C Instance
  * @retval I2C own address2 mask(value 0 to 7)
  */
__STATIC_INLINE uint32_t md_i2c_get_addr2_oa2mask(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->ADDR2, I2C_ADDR2_OA2MSK_MSK)>>I2C_ADDR2_OA2MSK_POSS);
}

/**
  * @brief  Set I2C own address2
  * @note   These bits can be written only when OA2EN=0.
  * @param  I2Cx I2C Instance
  * @param  own_addr I2C own address2
  *         @arg Max Value 0x7F
  *         @arg Min Value 0x1
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_addr2_oa2(I2C_TypeDef *I2Cx, uint32_t own_addr)
{
  MODIFY_REG(I2Cx->ADDR2, I2C_ADDR2_OA2_MSK, own_addr <<I2C_ADDR2_OA2_POSS);
}

/**
  * @brief  Get I2C own address2
  * @note   None
  * @param  I2Cx I2C Instance
  * @retval I2C own address2
  *         @arg Max Value 0x7F
  *         @arg Min Value 0x1
  */
__STATIC_INLINE uint32_t md_i2c_get_oa2(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->ADDR2, I2C_ADDR2_OA2_MSK)>>I2C_ADDR2_OA2_POSS);
}

/**
  * @brief  Set I2C TIMINGR
  * @note   These bits must be configured when the I2C is disabled (PE = 0). 
  * @param  I2Cx I2C Instance
  * @param  Reg_Value is a 32-bit value
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_timingr(I2C_TypeDef *I2Cx, uint32_t Reg_Value)
{
  WRITE_REG(I2Cx->TIMINGR, Reg_Value);
}

/**
  * @brief  Get I2C TIMINGR
  * @note   None
  * @param  I2Cx I2C Instance
  * @retval a 32-bit value
  */
__STATIC_INLINE uint32_t md_i2c_get_timingr(I2C_TypeDef *I2Cx)
{
  return (uint32_t) (READ_REG(I2Cx->TIMINGR));
}

/**
  * @brief  Set I2C Timing prescaler
  * @note   This register must be configured when the I2C is disabled(PE = 0)
  * @param  I2Cx I2C Instance
  * @param  timing_prescaler 
  *         @arg Max Value 0xF
  *         @arg Min Value 0x0
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_timingr_presc(I2C_TypeDef *I2Cx, uint32_t timing_prescaler)
{
  MODIFY_REG(I2Cx->TIMINGR, I2C_TIMINGR_PRESC_MSK, timing_prescaler << I2C_TIMINGR_PRESC_POSS);
}

/**
  * @brief  Get I2C Timing prescaler
  * @note   This register must be configured when the I2C is disabled(PE = 0)
  * @param  I2Cx I2C Instance
  * @retval timing_prescaler
  *         @arg Max Value 0xF
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint32_t md_i2c_get_timingr_presc(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->TIMINGR, I2C_TIMINGR_PRESC_MSK)>>I2C_TIMINGR_PRESC_POSS);
}

/**
  * @brief  Set I2C date setup time
  * @note   This register must be configured when the I2C is disabled(PE = 0)
  * @param  I2Cx I2C Instance
  * @param  data_setup_time
  *         @arg Max Value 0xF
  *         @arg Min Value 0x0
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_timingr_scldel(I2C_TypeDef *I2Cx, uint32_t data_setup_time)
{
  MODIFY_REG(I2Cx->TIMINGR, I2C_TIMINGR_SCLDEL_MSK, data_setup_time <<I2C_TIMINGR_SCLDEL_POSS);
}

/**
  * @brief  Get I2C date setup time
  * @note   This register must be configured when the I2C is disabled(PE = 0)
  * @param  I2Cx I2C Instance
  * @retval data_setup_time
  *         @arg Max Value 0xF
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint32_t md_i2c_get_timingr_scldel(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->TIMINGR, I2C_TIMINGR_SCLDEL_MSK)>>I2C_TIMINGR_SCLDEL_POSS);
}

/**
  * @brief  Set I2C date hold time
  * @note   This register must be configured when the I2C is disabled(PE = 0)
  * @param  I2Cx I2C Instance
  * @param  data_hold_time 
  *         @arg Max Value 0xF
  *         @arg Min Value 0x0
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_timingr_sdadel(I2C_TypeDef *I2Cx, uint32_t data_hold_time)
{
  MODIFY_REG(I2Cx->TIMINGR, I2C_TIMINGR_SDADEL_MSK, data_hold_time << I2C_TIMINGR_SDADEL_POSS);
}

/**
  * @brief  Get I2C date hold time
  * @note   This register must be configured when the I2C is disabled(PE = 0)
  * @param  I2Cx I2C Instance
  * @retval data_hold_time
  *         @arg Max Value 0xF
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint32_t md_i2c_get_timingr_sdadel(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->TIMINGR, I2C_TIMINGR_SDADEL_MSK)>>I2C_TIMINGR_SDADEL_POSS);
}

/**
  * @brief  Set I2C SCL high period(master mode)
  * @note   This register must be configured when the I2C is disabled(PE = 0)
  * @param  I2Cx I2C Instance
  * @param  SCL_hperiod 
  *         @arg Max Value 0xFF
  *         @arg Min Value 0x0
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_timingr_sclh(I2C_TypeDef *I2Cx, uint32_t SCL_hperiod)
{
  MODIFY_REG(I2Cx->TIMINGR, I2C_TIMINGR_SCLH_MSK, SCL_hperiod << I2C_TIMINGR_SCLH_POSS);
}

/**
  * @brief  Get I2C SCL high period(master mode)
  * @note   This register must be configured when the I2C is disabled(PE = 0)
  * @param  I2Cx I2C Instance
  * @retval SCL_hperiod
  *         @arg Max Value 0xFF
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint32_t md_i2c_get_timingr_sclh(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->TIMINGR, I2C_TIMINGR_SCLH_MSK)>>I2C_TIMINGR_SCLH_POSS);
}

/**
  * @brief  Set I2C SCL low period(master mode)
  * @note   This register must be configured when the I2C is disabled(PE = 0)
  * @param  I2Cx I2C Instance
  * @param  SCL_lperiod 
  *         @arg Max Value 0xFF
  *         @arg Min Value 0x0
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_timingr_scll(I2C_TypeDef *I2Cx, uint32_t SCL_lperiod)
{
  MODIFY_REG(I2Cx->TIMINGR, I2C_TIMINGR_SCLL_MSK, SCL_lperiod << I2C_TIMINGR_SCLL_POSS);
}

/**
  * @brief  Get I2C SCL low period(master mode)
  * @note   This register must be configured when the I2C is disabled(PE = 0)
  * @param  I2Cx I2C Instance
  * @retval SCL_lperiod
  *         @arg Max Value 0xFF
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint32_t md_i2c_get_timingr_scll(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->TIMINGR, I2C_TIMINGR_SCLL_MSK));
}

/**
  * @brief  Set I2C TIMEOUTR
  * @note   These bits can be written only when TEXTEN=0 and TIMEOUTEN=0 except TEXTEN and TIMEOUTEN.
  * @param  I2Cx I2C Instance
  * @param  Reg_Value is a 32-bit value
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_timeoutr(I2C_TypeDef *I2Cx, uint32_t Reg_Value)
{
  WRITE_REG(I2Cx->TIMEOUTR, Reg_Value);
}

/**
  * @brief  Get I2C TIMEOUTR
  * @note   None
  * @param  I2Cx I2C Instance
  * @retval a 32-bit value
  */
__STATIC_INLINE uint32_t md_i2c_get_timeoutr(I2C_TypeDef *I2Cx)
{
  return (uint32_t) (READ_REG(I2Cx->TIMEOUTR));
}

/**
  * @brief  I2C Extended clock timeout Enable
  * @note   None
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_timeoutr_texten(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->TIMEOUTR, I2C_TIMEOUTR_TEXTEN_MSK);
}

/**
  * @brief  I2C Extended clock timeout Disable
  * @note   None
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_timeoutr_texten(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->TIMEOUTR, I2C_TIMEOUTR_TEXTEN_MSK);
}

/**
  * @brief  Indicate if I2C Extended clock timeout is enabled
  * @note   None
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_timeoutr_texten(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->TIMEOUTR, I2C_TIMEOUTR_TEXTEN_MSK) == (I2C_TIMEOUTR_TEXTEN_MSK));
}

/**
  * @brief  Set I2C Bus timeout B
  * @note   These bits can be written only when TEXTEN = 0
  * @param  I2Cx I2C Instance
  * @param  timeoutb Bus timeout B
  *         @arg Max Value 0xFFFFFF
  *         @arg Min Value 0x0
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_timeoutr_timeoutb(I2C_TypeDef *I2Cx, uint32_t timeoutb)
{
  MODIFY_REG(I2Cx->TIMEOUTR, I2C_TIMEOUTR_TIMEOUTB_MSK, timeoutb << I2C_TIMEOUTR_TIMEOUTB_POSS);
}

/**
  * @brief  Get I2C Bus timeout B
  * @note   These bits can be written only when TEXTEN = 0
  * @param  I2Cx I2C Instance
  * @retval Bus timeout B
  *         @arg Max Value 0xFFFFFF
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint32_t md_i2c_get_timeoutr_timeoutb(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->TIMEOUTR, I2C_TIMEOUTR_TIMEOUTB_MSK)>>I2C_TIMEOUTR_TIMEOUTB_POSS);
}

/**
  * @brief  I2C clock timeout Enable
  * @note   None
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_timeoutr_timeouten(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->TIMEOUTR, I2C_TIMEOUTR_TIMEOUTEN_MSK);
}

/**
  * @brief  I2C clock timeout Disable
  * @note   None
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_timeoutr_timeouten(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->TIMEOUTR, I2C_TIMEOUTR_TIMEOUTEN_MSK);
}

/**
  * @brief  Indicate if I2C clock timeout is enabled
  * @note   None
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_timeoutr_timeouten(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->TIMEOUTR, I2C_TIMEOUTR_TIMEOUTEN_MSK) == (I2C_TIMEOUTR_TIMEOUTEN_MSK));
}

/**
  * @brief  Set I2C Tidle to decide a timeouta mode
  * @note   This bit can be written only when TIMOUTEN = 0
  * @param  I2Cx I2C Instance
  * @param  tidle_mode
  *         @arg @ref MD_I2C_LOW_TIMEOUTA
  *         @arg @ref MD_I2C_IDLE_TIMEOUTA
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_timeoutr_tidle(I2C_TypeDef *I2Cx, uint32_t tidle_mode)
{
  MODIFY_REG(I2Cx->TIMEOUTR, I2C_TIMEOUTR_TIDLE_MSK, tidle_mode);
}

/**
  * @brief  Get I2C Tidle to know a timeouta mode
  * @note   None
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_get_timeoutr_tidle(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->TIMEOUTR, I2C_TIMEOUTR_TIDLE_MSK)>>I2C_TIMEOUTR_TIDLE_POS);
}

/**
  * @brief  Set I2C Bus timeout A
  * @note   These bits can be written only when TIMOUTEN = 0
  * @param  I2Cx I2C Instance
  * @param  timeouta Bus timeout A
  *         @arg Max Value 0xFFFFFF
  *         @arg Min Value 0x0
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_timeoutr_timeouta(I2C_TypeDef *I2Cx, uint32_t timeouta)
{
  MODIFY_REG(I2Cx->TIMEOUTR, I2C_TIMEOUTR_TIMEOUTA_MSK, timeouta << I2C_TIMEOUTR_TIMEOUTA_POSS);
}

/**
  * @brief  Get I2C Bus timeout A
  * @note   These bits can be written only when TIMOUTEN = 0
  * @param  I2Cx I2C Instance
  * @retval Bus timeout A
  *         @arg Max Value 0xFFFFFF
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint32_t md_i2c_get_timeoutr_timeouta(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->TIMEOUTR, I2C_TIMEOUTR_TIMEOUTA_MSK));
}

/**
  * @brief  Get I2C STAT
  * @note   All bits are read-only
  * @param  I2Cx I2C Instance
  * @retval a 32-bit value
  */
__STATIC_INLINE uint32_t md_i2c_get_stat(I2C_TypeDef *I2Cx)
{
  return (uint32_t) (READ_REG(I2Cx->STAT));
}

/**
  * @brief  Get address match code(slave mode)
  * @note   These bits are updated with the received address when an address match event occurs(ADDR=1).
  * @param  I2Cx I2C Instance
  * @retval 7-bit received address value
  */
__STATIC_INLINE uint32_t md_i2c_get_stat_addcode(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->STAT, I2C_STAT_ADDCODE_MSK)>>I2C_STAT_ADDCODE_POSS);
}

/**
  * @brief  Get transfer direction(slave mode)
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_get_stat_dir(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->STAT, I2C_STAT_DIR_MSK)>>I2C_STAT_DIR_POS);
}

/**
  * @brief  Indicate if I2C busy flag is active
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_stat_busy(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->STAT, I2C_STAT_BUSY_MSK) == (I2C_STAT_BUSY_MSK));
}

/**
  * @brief  Indicate if I2C transfer complete reload flag (TCR) is active
  * @note   This bit is cleared by hardware when PE = 0.
  *         This flag is only for master mode,or for slave mode when the SBC bit is set
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_stat_tcr(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->STAT, I2C_STAT_TCR_MSK) == (I2C_STAT_TCR_MSK));
}

/**
  * @brief  Indicate if I2C transfer complete flag (TC) is active
  * @note   This bit is cleared by hardware when PE = 0.
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_stat_tc(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->STAT, I2C_STAT_TC_MSK) == (I2C_STAT_TC_MSK));
}

/**
  * @brief  Indicate if I2C Rx FIFO level over threshold flag (RXTH) is active
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_stat_rxth(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->STAT, I2C_STAT_RXTH_MSK) == (I2C_STAT_RXTH_MSK));
}

/**
  * @brief  Indicate if I2C Rx buffer underflow flag (RXUD) is active
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_stat_rxud(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->STAT, I2C_STAT_RXUD_MSK) == (I2C_STAT_RXUD_MSK));
}

/**
  * @brief  Indicate if I2C Rx buffer overflow flag (RXOV) is active
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_stat_rxov(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->STAT, I2C_STAT_RXOV_MSK) == (I2C_STAT_RXOV_MSK));
}

/**
  * @brief  Indicate if I2C Rx buffer full flag (RXF) is active
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_stat_rxf(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->STAT, I2C_STAT_RXF_MSK) == (I2C_STAT_RXF_MSK));
}

/**
  * @brief  Indicate if I2C Rx buffer empty flag (RXE) is active
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_stat_rxe(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->STAT, I2C_STAT_RXE_MSK) == (I2C_STAT_RXE_MSK));
}

/**
  * @brief  Indicate if I2C Tx FIFO level over threshold flag (TXTH) is active
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_stat_txth(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->STAT, I2C_STAT_TXTH_MSK) == (I2C_STAT_TXTH_MSK));
}

/**
  * @brief  Indicate if I2C Tx buffer underflow flag (TXUD) is active
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_is_active_stat_txud(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->STAT, I2C_STAT_TXUD_MSK) == (I2C_STAT_TXUD_MSK));
}

/**
  * @brief  Indicate if I2C Tx buffer overflow flag (TXOV) is active
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_stat_txov(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->STAT, I2C_STAT_TXOV_MSK) == (I2C_STAT_TXOV_MSK));
}

/**
  * @brief  Indicate if I2C Tx buffer full flag (TXF) is active
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_stat_txf(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->STAT, I2C_STAT_TXF_MSK) == (I2C_STAT_TXF_MSK));
}

/**
  * @brief  Indicate if I2C Tx buffer empty flag (TXE) is active
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_stat_txe(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->STAT, I2C_STAT_TXE_MSK) == (I2C_STAT_TXE_MSK));
}

/**
  * @brief  Set I2C FCON
  * @note   FIFO trigger threshold must be configured when the I2C is disabled (PE = 0).
  * @param  I2Cx I2C Instance
  * @param  Reg_Value is a 32-bit value
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_fcon(I2C_TypeDef *I2Cx, uint32_t Reg_Value)
{
  WRITE_REG(I2Cx->FCON, Reg_Value);
}

/**
  * @brief  Get I2C FCON
  * @note   None
  * @param  I2Cx I2C Instance
  * @retval a 32-bit value
  */
__STATIC_INLINE uint32_t md_i2c_get_fcon(I2C_TypeDef *I2Cx)
{
  return (uint32_t) (READ_REG(I2Cx->FCON));
}

/**
  * @brief  Set RXFIFO trigger threshold
  * @note   Receive FIFO trigger threshold must be configured when the I2C is disabled (PE = 0).
  * @param  I2Cx I2C Instance
  * @param  rxfifo_trigger_threshold This parameter can be one of the following values:
  *         @arg @ref MD_I2C_RXFIFO_THRESHOLD_RX1
  *         @arg @ref MD_I2C_RXFIFO_THRESHOLD_RX4
  *         @arg @ref MD_I2C_RXFIFO_THRESHOLD_RX8
  *         @arg @ref MD_I2C_RXFIFO_THRESHOLD_RX14
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_fcon_rxfth(I2C_TypeDef *I2Cx, uint32_t rxfifo_trigger_threshold)
{
  MODIFY_REG(I2Cx->FCON, I2C_FCON_RXFTH_MSK, rxfifo_trigger_threshold);
}

/**
  * @brief  Get RXFIFO trigger threshold
  * @note   None
  * @param  I2Cx I2C Instance
  * @retval The retval can be 0 to 3
  */
__STATIC_INLINE uint32_t md_i2c_get_fcon_rxfth(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->FCON, I2C_FCON_RXFTH_MSK)>>I2C_FCON_RXFTH_POSS);
}

/**
  * @brief  Set I2C RXFIFO reset
  * @note   None
  * @param  I2Cx I2C Instance
  *         @arg @ref MD_I2C_RXFIFO_RESET
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_fcon_rxfrst(I2C_TypeDef *I2Cx, uint32_t reset)
{
  MODIFY_REG(I2Cx->FCON, I2C_FCON_RXFRST_MSK, reset);
}

/**
  * @brief  Get I2C RXFIFO level
  * @note   None
  * @param  I2Cx I2C Instance
  * @retval It's from 0 to 16
  */
__STATIC_INLINE uint32_t md_i2c_get_rxfifo_level(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->FCON, I2C_FCON_RXFLV_MSK)>>I2C_FCON_RXFLV_POSS);
}

/**
  * @brief  Set TXFIFO trigger threshold
  * @param  I2Cx I2C Instance
  * @param  txfifo_trigger_threshold This parameter can be one of the following values:
  *         @arg @ref MD_I2C_TXFIFO_THRESHOLD_TX0
  *         @arg @ref MD_I2C_TXFIFO_THRESHOLD_TX2
  *         @arg @ref MD_I2C_TXFIFO_THRESHOLD_TX4
  *         @arg @ref MD_I2C_TXFIFO_THRESHOLD_TX8
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_fcon_txfth(I2C_TypeDef *I2Cx, uint32_t txfifo_trigger_threshold)
{
  MODIFY_REG(I2Cx->FCON, I2C_FCON_TXFTH_MSK, txfifo_trigger_threshold);
}

/**
  * @brief  Get TXFIFO trigger threshold
  * @param  I2Cx I2C Instance
  * @retval It's from 0 to 3
  */
__STATIC_INLINE uint32_t md_i2c_get_txfifo_trigger_threshold(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->FCON, I2C_FCON_TXFTH_MSK)>>I2C_FCON_TXFTH_POSS);
}

/**
  * @brief  I2C TXFIFO reset
  * @note   None
  * @param  I2Cx I2C Instance
  *         @arg @ref MD_I2C_TXFIFO_RESET
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_fcon_txfrst(I2C_TypeDef *I2Cx, uint32_t reset)
{
  MODIFY_REG(I2Cx->FCON, I2C_FCON_TXFRST_MSK, reset);
}

/**
  * @brief  Get TXFIFO level
  * @note   None
  * @param  I2Cx I2C Instance
  * @retval It's from 0 to 16
  */
__STATIC_INLINE uint32_t md_i2c_get_txfifo_level(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->FCON, I2C_FCON_TXFLV_MSK));
}

/**
  * @brief  Get packet error checking register
  * @note   None
  * @param  I2Cx I2C Instance
  * @retval 8-bit pec value
  */
__STATIC_INLINE uint32_t md_i2c_get_pecr_pec(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->PECR, I2C_PECR_PEC_MSK));
}

/**
  * @brief  8-bit receive data
  * @note   None
  * @param  I2Cx I2C Instance
  * @retval 8-bit receive data
  */
__STATIC_INLINE uint32_t md_i2c_recv(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->RXDATA, I2C_RXDATA_RXDATA_MSK));
}

/**
  * @brief  8-bit transmit data
  * @note   These bits can be written only when TXE = 1.
  * @param  I2Cx I2C Instance
  * @param  txdata Transmit Data
  *         @arg Max value 0xFF
  *         @arg Min value 0
  * @retval None
  */
__STATIC_INLINE void md_i2c_send(I2C_TypeDef *I2Cx, uint32_t txdata)
{
  MODIFY_REG(I2Cx->TXDATA, I2C_TXDATA_TXDATA_MSK, txdata);
}

/**
  * @brief  Set I2C IER
  * @note   None 
  * @param  I2Cx I2C Instance
  * @param  ier
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_ier(I2C_TypeDef *I2Cx, uint32_t ier)
{
  WRITE_REG(I2Cx->IER, ier);
}

/**
  * @brief  Enable SMBus alert interrupt
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_ier_alertie(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->IER, I2C_IER_ALERTIE_MSK);
}

/**
  * @brief  Enable timeout interrupt
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_ier_toutie(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->IER, I2C_IER_TOUTIE_MSK);
}

/**
  * @brief  Enable PEC error interrupt
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_ier_peceie(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->IER, I2C_IER_PECEIE_MSK);
}

/**
  * @brief  Enable arbitration loss interrupt
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_ier_arloie(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->IER, I2C_IER_ARLOIE_MSK);
}

/**
  * @brief  Enable bus error interrupt
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_ier_berrie(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->IER, I2C_IER_BERRIE_MSK);
}

/**
  * @brief  Enable stop detection interrupt
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_ier_stopie(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->IER, I2C_IER_STOPIE_MSK);
}

/**
  * @brief  Enable NACK reception interrupt
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_ier_nackie(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->IER, I2C_IER_NACKIE_MSK);
}

/**
  * @brief  Enable address matched interrupt
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_ier_addrie(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->IER, I2C_IER_ADDRIE_MSK);
}

/**
  * @brief  Enable transfer complete and reload interrupt
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_ier_tcrie(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->IER, I2C_IER_TCRIE_MSK);
}

/**
  * @brief  Enable transfer complete interrupt
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_ier_tcie(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->IER, I2C_IER_TCIE_MSK);
}

/**
  * @brief  Enable receive buffer over threshold interrupt
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_ier_rxthie(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->IER, I2C_IER_RXTHIE_MSK);
}

/**
  * @brief  Enable receive buffer underrun interrupt
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_ier_rxudie(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->IER, I2C_IER_RXUDIE_MSK);
}

/**
  * @brief  Enable receive buffer ovrun interrupt
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_ier_rxovie(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->IER, I2C_IER_RXOVIE_MSK);
}

/**
  * @brief  Enable receive buffer full interrupt
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_ier_rxfie(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->IER, I2C_IER_RXFIE_MSK);
}

/**
  * @brief  Enable transmit buffer under threshold interrupt
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_ier_txthie(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->IER, I2C_IER_TXTHIE_MSK);
}

/**
  * @brief  Enable transmit buffer underrun interrupt
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_ier_txudie(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->IER, I2C_IER_TXUDIE_MSK);
}

/**
  * @brief  Enable transmit buffer ovrun interrupt
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_ier_txovie(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->IER, I2C_IER_TXOVIE_MSK);
}

/**
  * @brief  Enable transmit buffer empty interrupt 
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_ier_txeie(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->IER, I2C_IER_TXEIE_MSK);
}

/**
  * @brief  Set I2C IDR
  * @note   None 
  * @param  I2Cx I2C Instance
  * @param  ier
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_idr(I2C_TypeDef *I2Cx, uint32_t idr)
{
  WRITE_REG(I2Cx->IDR, idr);
}

/**
  * @brief  Disable SMBus alert interrupt
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_idr_alertid(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->IDR, I2C_IDR_ALERTID_MSK);
}

/**
  * @brief  Disable timeout interrupt 
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_idr_toutid(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->IDR, I2C_IDR_TOUTID_MSK);
}

/**
  * @brief  Disable PEC error interrupt
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_idr_peceid(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->IDR, I2C_IDR_PECEID_MSK);
}

/**
  * @brief  Disable arbitration loss interrupt
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_idr_arloid(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->IDR, I2C_IDR_ARLOID_MSK);
}

/**
  * @brief  Disable bus error interrupt.
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_idr_berrid(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->IDR, I2C_IDR_BERRID_MSK);
}

/**
  * @brief  Disable stop detection interrupt
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_idr_stopid(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->IDR, I2C_IDR_STOPID_MSK);
}

/**
  * @brief  Disable NACK reception interrupt
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_idr_nackid(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->IDR, I2C_IDR_NACKID_MSK);
}

/**
  * @brief  Disable address matched interrupt
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_idr_addrid(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->IDR, I2C_IDR_ADDRID_MSK);
}

/**
  * @brief  Disable transfer complete and reload interrupt
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_idr_tcrid(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->IDR, I2C_IDR_TCRID_MSK);
}

/**
  * @brief  Disable transfer complete interrupt
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_idr_tcid(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->IDR, I2C_IDR_TCID_MSK);
}

/**
  * @brief  Disable receive buffer over threshold interrupt
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_idr_rxthid(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->IDR, I2C_IDR_RXTHID_MSK);
}

/**
  * @brief  Disable receive buffer underrun interrupt
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_idr_rxudid(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->IDR, I2C_IDR_RXUDID_MSK);
}

/**
  * @brief  Disable receive buffer ovrun interrupt
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_idr_rxovid(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->IDR, I2C_IDR_RXOVID_MSK);
}

/**
  * @brief  Disable receive buffer full interrupt
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_idr_rxfid(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->IDR, I2C_IDR_RXFID_MSK);
}

/**
  * @brief  Disable transmit buffer under threshold interrupt
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_idr_txthid(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->IDR, I2C_IDR_TXTHID_MSK);
}

/**
  * @brief  Disable transmit buffer underrun interrupt
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_idr_txudid(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->IDR, I2C_IDR_TXUDID_MSK);
}

/**
  * @brief  Disable transmit buffer ovrun interrupt
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_idr_txovid(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->IDR, I2C_IDR_TXOVID_MSK);
}

/**
  * @brief  Disable transmit buffer empty interrupt
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_idr_txeid(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->IDR, I2C_IDR_TXEID_MSK);
}

/**
  * @brief  Get I2C IVS
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval a 32-bit value
  */
__STATIC_INLINE uint32_t md_i2c_get_ivs(I2C_TypeDef *I2Cx)
{
  return (uint32_t)  (READ_REG(I2Cx->IVS));
}

/**
  * @brief  Check if SMBus alert interrupt is enabled
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_ivs_alertiv(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->IVS, I2C_IVS_ALERTIV_MSK) == (I2C_IVS_ALERTIV_MSK));
}

/**
  * @brief  Check if timeout interrupt is enabled 
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_ivs_toutiv(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->IVS, I2C_IVS_TOUTIV_MSK) == (I2C_IVS_TOUTIV_MSK));
}

/**
  * @brief  Check if PEC error interrupt is enabled
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_ivs_peceiv(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->IVS, I2C_IVS_PECEIV_MSK) == (I2C_IVS_PECEIV_MSK));
}

/**
  * @brief  Check if arbitration loss interrupt is enabled
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_ivs_arloiv(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->IVS, I2C_IVS_ARLOIV_MSK) == (I2C_IVS_ARLOIV_MSK));
}

/**
  * @brief  Check if bus error interrupt is enabled
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_ivs_berriv(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->IVS, I2C_IVS_BERRIV_MSK) == (I2C_IVS_BERRIV_MSK));
}

/**
  * @brief  Check if stop detection interrupt is enabled
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_ivs_stopiv(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->IVS, I2C_IVS_STOPIV_MSK) == (I2C_IVS_STOPIV_MSK));
}

/**
  * @brief  Check if NACK reception interrupt is enabled
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_ivs_nackiv(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->IVS, I2C_IVS_NACKIV_MSK) == (I2C_IVS_NACKIV_MSK));
}

/**
  * @brief  Check if address matched interrupt is enabled
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_ivs_addriv(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->IVS, I2C_IVS_ADDRIV_MSK) == (I2C_IVS_ADDRIV_MSK));
}

/**
  * @brief  Check if transfer complete and reload interrupt is enabled
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_ivs_tcriv(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->IVS, I2C_IVS_TCRIV_MSK) == (I2C_IVS_TCRIV_MSK));
}

/**
  * @brief  Check if transfer complete interrupt is enabled
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_ivs_tciv(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->IVS, I2C_IVS_TCIV_MSK) == (I2C_IVS_TCIV_MSK));
}

/**
  * @brief  Check if receive buffer over threshold interrupt is enabled
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_ivs_rxthiv(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->IVS, I2C_IVS_RXTHIV_MSK) == (I2C_IVS_RXTHIV_MSK));
}

/**
  * @brief  Check if receive buffer underrun interrupt is enabled
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_ivs_rxudiv(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->IVS, I2C_IVS_RXUDIV_MSK) == (I2C_IVS_RXUDIV_MSK));
}

/**
  * @brief  Check if receive buffer ovrun interrupt is enabled
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_ivs_rxoviv(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->IVS, I2C_IVS_RXOVIV_MSK) == (I2C_IVS_RXOVIV_MSK));
}

/**
  * @brief  Check if receive buffer full interrupt is enabled
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_ivs_rxfiv(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->IVS, I2C_IVS_RXFIV_MSK) == (I2C_IVS_RXFIV_MSK));
}

/**
  * @brief  Check if transmit buffer under threshold interrupt is enabled
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_ivs_txthiv(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->IVS, I2C_IVS_TXTHIV_MSK) == (I2C_IVS_TXTHIV_MSK));
}

/**
  * @brief  Check if transmit buffer underrun interrupt is enabled
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_ivs_txudiv(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->IVS, I2C_IVS_TXUDIV_MSK) == (I2C_IVS_TXUDIV_MSK));
}

/**
  * @brief  Check if transmit buffer ovrun interrupt is enabled
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_ivs_txoviv(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->IVS, I2C_IVS_TXOVIV_MSK) == (I2C_IVS_TXOVIV_MSK));
}

/**
  * @brief  Check if transmit buffer empty interrupt is enabled
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_ivs_txeiv(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->IVS, I2C_IVS_TXEIV_MSK) == (I2C_IVS_TXEIV_MSK));
}

/**
  * @brief  Get I2C RIF
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval a 32-bit value
  */
__STATIC_INLINE uint32_t md_i2c_get_rif(I2C_TypeDef *I2Cx)
{
  return (uint32_t)  (READ_REG(I2Cx->RIF));
}

/**
  * @brief  Get SMBus alert raw interrupt flag
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_rif_alertri(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->RIF, I2C_RIF_ALERTRI_MSK) == (I2C_RIF_ALERTRI_MSK));
}

/**
  * @brief  Get timeout raw interrupt flag 
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_rif_toutri(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->RIF, I2C_RIF_TOUTRI_MSK) == (I2C_RIF_TOUTRI_MSK));
}

/**
  * @brief  Get PEC error raw interrupt flag
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_rif_peceri(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->RIF, I2C_RIF_PECERI_MSK) == (I2C_RIF_PECERI_MSK));
}

/**
  * @brief  Get arbitration loss raw interrupt flag
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_rif_arlori(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->RIF, I2C_RIF_ARLORI_MSK) == (I2C_RIF_ARLORI_MSK));
}

/**
  * @brief  Get bus error raw interrupt flag
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_rif_berrri(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->RIF, I2C_RIF_BERRRI_MSK) == (I2C_RIF_BERRRI_MSK));
}

/**
  * @brief  Get stop detection raw interrupt flag
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_rif_stopri(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->RIF, I2C_RIF_STOPRI_MSK) == (I2C_RIF_STOPRI_MSK));
}

/**
  * @brief  Get NACK reception raw interrupt flag
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_rif_nackri(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->RIF, I2C_RIF_NACKRI_MSK) == (I2C_RIF_NACKRI_MSK));
}

/**
  * @brief  Get address matched raw interrupt flag
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_rif_addrri(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->RIF, I2C_RIF_ADDRRI_MSK) == (I2C_RIF_ADDRRI_MSK));
}

/**
  * @brief  Get transfer complete and reload raw interrupt flag
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_rif_tcrri(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->RIF, I2C_RIF_TCRRI_MSK) == (I2C_RIF_TCRRI_MSK));
}

/**
  * @brief  Get transfer complete raw interrupt flag
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_rif_tcri(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->RIF, I2C_RIF_TCRI_MSK) == (I2C_RIF_TCRI_MSK));
}

/**
  * @brief  Get receive buffer over threshold raw interrupt flag
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_rif_rxthri(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->RIF, I2C_RIF_RXTHRI_MSK) == (I2C_RIF_RXTHRI_MSK));
}

/**
  * @brief  Get receive buffer underrun raw interrupt flag
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_rif_rxudri(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->RIF, I2C_RIF_RXUDRI_MSK) == (I2C_RIF_RXUDRI_MSK));
}

/**
  * @brief  Get receive buffer ovrun raw interrupt flag
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_rif_rxovri(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->RIF, I2C_RIF_RXOVRI_MSK) == (I2C_RIF_RXOVRI_MSK));
}

/**
  * @brief  Get receive buffer full raw interrupt flag
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_rif_rxfri(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->RIF, I2C_RIF_RXFRI_MSK) == (I2C_RIF_RXFRI_MSK));
}

/**
  * @brief  Get transmit buffer under threshold raw interrupt flag
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_rif_txthri(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->RIF, I2C_RIF_TXTHRI_MSK) == (I2C_RIF_TXTHRI_MSK));
}

/**
  * @brief  Get transmit buffer underrun raw interrupt flag
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_rif_txudri(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->RIF, I2C_RIF_TXUDRI_MSK) == (I2C_RIF_TXUDRI_MSK));
}

/**
  * @brief  Get transmit buffer ovrun raw interrupt flag
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_rif_txovri(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->RIF, I2C_RIF_TXOVRI_MSK) == (I2C_RIF_TXOVRI_MSK));
}

/**
  * @brief  Get transmit buffer empty raw interrupt flag
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_rif_txeri(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->RIF, I2C_RIF_TXERI_MSK) == (I2C_RIF_TXERI_MSK));
}

/**
  * @brief  Set I2C ICR
  * @note   None 
  * @param  I2Cx I2C Instance
  * @param  icr
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_icr(I2C_TypeDef *I2Cx, uint32_t icr)
{
  WRITE_REG(I2Cx->ICR, icr);
}

/**
  * @brief  Clear SMBus alert raw interrupt flag
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_clear_icr_alertic(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->ICR, I2C_ICR_ALERTIC_MSK);
}

/**
  * @brief  Clear timeout raw interrupt flag
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_clear_icr_toutic(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->ICR, I2C_ICR_TOUTIC_MSK);
}

/**
  * @brief  Clear PEC error raw interrupt flag
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_clear_icr_peceic(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->ICR, I2C_ICR_PECEIC_MSK);
}

/**
  * @brief  Clear arbitration loss raw interrupt flag
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_clear_icr_arloic(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->ICR, I2C_ICR_ARLOIC_MSK);
}

/**
  * @brief  Clear bus error raw interrupt flag
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_clear_icr_berric(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->ICR, I2C_ICR_BERRIC_MSK);
}

/**
  * @brief  Clear stop detection raw interrupt flag
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_clear_icr_stopic(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->ICR, I2C_ICR_STOPIC_MSK);
}

/**
  * @brief  Clear NACK reception raw interrupt flag
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_clear_icr_nackic(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->ICR, I2C_ICR_NACKIC_MSK);
}

/**
  * @brief  Clear address matched raw interrupt flag
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_clear_icr_addric(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->ICR, I2C_ICR_ADDRIC_MSK);
}

/**
  * @brief  Clear transfer complete and reload raw interrupt flag
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_clear_icr_tcric(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->ICR, I2C_ICR_TCRIC_MSK);
}

/**
  * @brief  Clear transfer complete raw interrupt flag
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_clear_icr_tcic(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->ICR, I2C_ICR_TCIC_MSK);
}

/**
  * @brief  Clear receive buffer over threshold raw interrupt flag
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_clear_icr_rxthic(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->ICR, I2C_ICR_RXTHIC_MSK);
}

/**
  * @brief  Clear receive buffer underrun raw interrupt flag
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_clear_icr_rxudic(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->ICR, I2C_ICR_RXUDIC_MSK);
}

/**
  * @brief  Clear receive buffer ovrun raw interrupt flag
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_clear_icr_rxovic(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->ICR, I2C_ICR_RXOVIC_MSK);
}

/**
  * @brief  Clear receive buffer full raw interrupt flag
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_clear_icr_rxfic(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->ICR, I2C_ICR_RXFIC_MSK);
}

/**
  * @brief  Clear transmit buffer under threshold raw interrupt flag
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_clear_icr_txthic(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->ICR, I2C_ICR_TXTHIC_MSK);
}

/**
  * @brief  Clear transmit buffer underrun raw interrupt flag
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_clear_icr_txudic(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->ICR, I2C_ICR_TXUDIC_MSK);
}

/**
  * @brief  Clear transmit buffer ovrun raw interrupt flag
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_clear_icr_txovic(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->ICR, I2C_ICR_TXOVIC_MSK);
}

/**
  * @brief  Clear transmit buffer empty raw interrupt flag 
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval None
  */
__STATIC_INLINE void md_i2c_clear_icr_txeic(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->ICR, I2C_ICR_TXEIC_MSK);
}

/**
  * @brief  Get I2C IFM
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval a 32-bit value
  */
__STATIC_INLINE uint32_t md_i2c_get_ifm(I2C_TypeDef *I2Cx)
{
  return (uint32_t)  (READ_REG(I2Cx->IFM));
}

/**
  * @brief  Get SMBus alert interrupt flag massked status
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_ifm_alertfm(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->IFM, I2C_IFM_ALERTFM_MSK) == (I2C_IFM_ALERTFM_MSK));
}

/**
  * @brief  Get timeout interrupt flag masked status 
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_ifm_toutfm(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->IFM, I2C_IFM_TOUTFM_MSK) == (I2C_IFM_TOUTFM_MSK));
}

/**
  * @brief  Get PEC error interrupt flag masked status
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_ifm_pecefm(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->IFM, I2C_IFM_PECEFM_MSK) == (I2C_IFM_PECEFM_MSK));
}

/**
  * @brief  Get arbitration loss interrupt flag masked status
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_ifm_arlofm(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->IFM, I2C_IFM_ARLOFM_MSK) == (I2C_IFM_ARLOFM_MSK));
}

/**
  * @brief  Get bus error interrupt flag masked status
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_ifm_berrfm(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->IFM, I2C_IFM_BERRFM_MSK) == (I2C_IFM_BERRFM_MSK));
}

/**
  * @brief  Get stop detection interrupt flag masked status
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_ifm_stopfm(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->IFM, I2C_IFM_STOPFM_MSK) == (I2C_IFM_STOPFM_MSK));
}

/**
  * @brief  Get NACK reception interrupt flag masked status
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_ifm_nackfm(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->IFM, I2C_IFM_NACKFM_MSK) == (I2C_IFM_NACKFM_MSK));
}

/**
  * @brief  Get address matched interrupt flag masked status
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_ifm_addrfm(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->IFM, I2C_IFM_ADDRFM_MSK) == (I2C_IFM_ADDRFM_MSK));
}

/**
  * @brief  Get transfer complete and reload interrupt flag masked status
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_ifm_tcrfm(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->IFM, I2C_IFM_TCRFM_MSK) == (I2C_IFM_TCRFM_MSK));
}

/**
  * @brief  Get transfer complete interrupt flag masked status
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_ifm_tcfm(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->IFM, I2C_IFM_TCFM_MSK) == (I2C_IFM_TCFM_MSK));
}

/**
  * @brief  Get receive buffer over threshold interrupt flag masked status
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_ifm_rxthfm(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->IFM, I2C_IFM_RXTHFM_MSK) == (I2C_IFM_RXTHFM_MSK));
}

/**
  * @brief  Get receive buffer underrun interrupt flag masked status
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_ifm_rxudfm(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->IFM, I2C_IFM_RXUDFM_MSK) == (I2C_IFM_RXUDFM_MSK));
}

/**
  * @brief  Get receive buffer ovrun interrupt flag masked status
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_ifm_rxovfm(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->IFM, I2C_IFM_RXOVFM_MSK) == (I2C_IFM_RXOVFM_MSK));
}

/**
  * @brief  Get receive buffer full interrupt flag masked status
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_ifm_rxffm(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->IFM, I2C_IFM_RXFFM_MSK) == (I2C_IFM_RXFFM_MSK));
}

/**
  * @brief  Get transmit buffer under threshold interrupt flag masked status
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_ifm_txthfm(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->IFM, I2C_IFM_TXTHFM_MSK) == (I2C_IFM_TXTHFM_MSK));
}

/**
  * @brief  Get transmit buffer underrun interrupt flag masked status
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_ifm_txudfm(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->IFM, I2C_IFM_TXUDFM_MSK) == (I2C_IFM_TXUDFM_MSK));
}

/**
  * @brief  Get transmit buffer ovrun interrupt flag masked status
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_ifm_txovfm(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->IFM, I2C_IFM_TXOVFM_MSK) == (I2C_IFM_TXOVFM_MSK));
}

/**
  * @brief  Get transmit buffer empty interrupt flag masked status
  * @note   None 
  * @param  I2Cx I2C Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_ifm_txefm(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->IFM, I2C_IFM_TXEFM_MSK) == (I2C_IFM_TXEFM_MSK));
}

/**
  * @} MD_I2C_Public_Macros
  */






/* Public functions -----------------------------------------------------------*/
/** @defgroup MD_I2C_Public_Functions I2C Public Functions
  * @{
  */

/** @defgroup MD_I2C_PF_Basic_Configuration I2C Configuration
  * @{
  */

//ErrorStatus md_i2c_deinit(I2C_TypeDef *I2Cx);
ErrorStatus md_i2c_init(I2C_TypeDef *I2Cx, md_i2c_inittypedef *I2C_InitStruct);
void        md_i2c_struct_init(md_i2c_inittypedef *I2C_InitStruct);
void        md_i2c_master_send(I2C_TypeDef *I2Cx, uint8_t Nbyte, uint32_t addr10, uint16_t DevAddr, uint8_t *txbuf);
void        md_i2c_master_rece(I2C_TypeDef *I2Cx, uint8_t Nbyte, uint32_t addr10, uint16_t DevAddr, uint8_t *rxbuf);
void        md_i2c_slave_send(I2C_TypeDef *I2Cx, uint8_t Num, uint8_t *txbuf);
void        md_i2c_slave_rece(I2C_TypeDef *I2Cx, uint8_t Num, uint8_t *rxbuf);

/**
  * @} MD_I2C_PF_Init
  */

/**
  * @} MD_I2C_Public_Functions
  */

#endif

/* Private macros ------------------------------------------------------------*/
/** @defgroup MD_I2C_Private_Macro I2C Private Macros
  * @{
  */
#define IS_MD_I2C_ALL_INSTANCE(__INSTANCE__) ((__INSTANCE__ == I2C1)  \
                                           || (__INSTANCE__ == I2C2)  \
                                           || (__INSTANCE__ == I2C3))

#define IS_MD_I2C_TIMING(__VALUE__) ((__VALUE__ == CLK10kHz8M)  \
                                  || (__VALUE__ == CLK100kHz8M)) \
                                  || (__VALUE__ == CLK400kHz8M)) \
                                  || (__VALUE__ == CLK500kHz8M)) \
                                  || (__VALUE__ == CLK10kHz16M)) \
                                  || (__VALUE__ == CLK100kHz16M)) \
                                  || (__VALUE__ == CLK400kHz16M)) \
                                  || (__VALUE__ == CLK1000kHz16M)) \
                                  || (__VALUE__ == CLK10kHz48M)) \
                                  || (__VALUE__ == CLK100kHz48M)) \
                                  || (__VALUE__ == CLK400kHz48M)) \
                                  || (__VALUE__ == CLK1000kHz48M))

#define IS_MD_I2C_ADDRSIZE(__VALUE__) ((__VALUE__ == MD_I2C_ADDRESSINGMODE_7BIT)  \
                                    || (__VALUE__ == MD_I2C_ADDRESSINGMODE_10BIT))
      
#define IS_MD_I2C_ADDRESS1(__VALUE__) (__VALUE__ <= 0x000003FFU)
#define IS_MD_I2C_ADDRESS2(__VALUE__) (__VALUE__ <= (uint16_t)0x00FFU)  

#define IS_MD_I2C_DUALADDRESSMODE(__VALUE__)   ((__VALUE__ == MD_I2C_DUALADDRESS_DISABLE)  \
                                             || (__VALUE__ == MD_I2C_DUALADDRESS_ENABLE))
#define IS_MD_I2C_ADDRESS2MASKS(__VALUE__)  ((__VALUE__ == MD_I2C_ADDR2_NOMASK)  \
                                          || (__VALUE__ == MD_I2C_ADDR2_MASK01)  \
                                          || (__VALUE__ == MD_I2C_ADDR2_MASK02)  \
                                          || (__VALUE__ == MD_I2C_ADDR2_MASK03)  \
                                          || (__VALUE__ == MD_I2C_ADDR2_MASK04)  \
                                          || (__VALUE__ == MD_I2C_ADDR2_MASK05)  \
                                          || (__VALUE__ == MD_I2C_ADDR2_MASK06)  \
                                          || (__VALUE__ == MD_I2C_ADDR2_MASK07))

/**
  * @} MD_I2C_Private_Macro
  */  

/**
  * @} I2C
  */  
  
/**
  * @} Micro_Driver
  */

#ifdef __cplusplus
}
#endif

#endif

/******************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
