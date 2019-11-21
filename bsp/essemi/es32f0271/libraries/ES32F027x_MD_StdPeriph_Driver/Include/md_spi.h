/**
  ******************************************************************************
  * @file    md_spi.h
  * @brief   ES32F0271 SPI Head File.
  *
  * @version V1.00.01
  * @date    06/11/2018
  * @author  Eastsoft AE Team
  * @note
  * detailed description
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MD_SPI_H__
#define __MD_SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -------------------------------------------------------------------*/ 
#include "es32f0271.h"
#include "reg_spi.h"
  
/** @addtogroup Micro_Driver
  * @{
  */

#if defined (SPI1) || defined (SPI2)

/** @defgroup SPI SPI
  * @brief SPI micro driver
  * @{
  */
  
/* Private types --------------------------------------------------------------*/
/* Private variables ----------------------------------------------------------*/
/* Private macros -------------------------------------------------------------*/

/* Public types ---------------------------------------------------------------*/
/** @defgroup MD_SPI_Public_Types SPI Public Types
  * @{
  */

/** @defgroup MD_SPI_PT_INIT SPI Public Init structure
  * @{
  */

/**
  * @brief   SPI Init structure.
  */
typedef struct
{
  uint32_t Mode;                    /*!< Specifies the SPI mode (Master/Slave).
                                         This parameter can be a value of @ref MD_SPI_PC_MODE.

                                         This feature can be modified afterwards using unitary function @ref md_spi_set_con1_mstren().*/

  uint32_t ClockPhase;              /*!< Specifies the clock active edge for the bit capture.
                                         This parameter can be a value of @ref MD_SPI_PC_PHASE.

                                         This feature can be modified afterwards using unitary function @ref md_spi_set_con1_cpha().*/

  uint32_t ClockPolarity;           /*!< Specifies the serial clock steady state. 
                                         This parameter can be a value of @ref MD_SPI_PC_POLARITY.

                                         This feature can be modified afterwards using unitary function @ref md_spi_get_con1_cpol().*/

  uint32_t BaudRate;                /*!< Specifies the BaudRate prescaler value which will be used to configure the transmit and receive SCK clock.
                                         This parameter can be a value of @ref MD_SPI_PC_BAUDRATEPRESCALER.
                                         @note The communication clock is derived from the master clock. The slave clock does not need to be set.

                                         This feature can be modified afterwards using unitary function @ref md_spi_set_con1_baud().*/

  uint32_t BitOrder;                /*!< Specifies whether data transfers start from MSB or LSB bit.
                                         This parameter can be a value of @ref MD_SPI_PC_BIT_ORDER.

                                         This feature can be modified afterwards using unitary function @ref md_spi_set_con1_lsbfirst().*/

  uint32_t TransferDirection;       /*!< Specifies the SPI unidirectional or bidirectional data mode.
                                         This parameter can be a value of @ref MD_SPI_PC_TRANSFER_DIRECTION.

                                         This feature can be modified afterwards using unitary function @ref md_spi_set_con1_bidimode().*/

  uint32_t DataWidth;               /*!< Specifies the SPI data width.
                                         This parameter can be a value of @ref MD_SPI_PC_FRAME_FORMAT.

                                         This feature can be modified afterwards using unitary function @ref md_spi_set_con1_dlen().*/

  uint32_t NSS;                     /*!< Specifies whether the NSS signal is managed by hardware (NSS pin) or by software using the SSI bit.
                                         This parameter can be a value of @ref MD_SPI_PC_NSS_MODE.

                                         This feature can be modified afterwards using unitary function @ref md_spi_set_con1_ssout().*/

  uint32_t CRCCalculation;          /*!< Specifies if the CRC calculation is enabled or not.
                                         This parameter can be a value of @ref MD_SPI_EC_CRC_CALCULATION.

                                         This feature can be modified afterwards using unitary functions @ref md_spi_enable_con1_crcen() and @ref md_spi_disable_con1_crcen().*/

  uint32_t CRCPoly;                 /*!< Specifies the polynomial used for the CRC calculation.
                                         This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFFFF.

                                         This feature can be modified afterwards using unitary function.*/

} md_spi_inittypedef;




/**
  * @} MD_SPI_PT_INIT
  */

/**
  * @} MD_SPI_Public_Types
  */

/* Public constants -----------------------------------------------------------*/
/** @defgroup MD_SPI_Public_Constants SPI Public Constants
  * @{
  */

/** @defgroup MD_SPI_PC_MODE SPI Operation Mode
  * @{
  */
#define MD_SPI_MODE_SLAVE           0x00000000U               /*!< Slave configuration   */
#define MD_SPI_MODE_MASTER          (SPI_CON1_MSTREN_MSK)               /*!< Master configuration  */
/**
  * @} MD_SPI_PC_MODE
  */

/** @defgroup MD_SPI_PC_PROTOCOL SPI Serial Protocol
  * @{
  */
#define MD_SPI_PROTOCOL_MOTOROLA           0x00000000U                /*!< Motorola mode. Used as default value */
#define MD_SPI_PROTOCOL_TI                 (SPI_CON2_FRF_MSK)         /*!< TI mode                              */
/**
  * @} MD_SPI_PC_PROTOCOL
  */

/** @defgroup MD_SPI_PC_PHASE SPI Clock Phase
  * @{
  */
#define MD_SPI_PHASE_1EDGE                 0x00000000U                /*!< First clock transition is the first data capture edge  */
#define MD_SPI_PHASE_2EDGE                 (SPI_CON1_CPHA_MSK)        /*!< Second clock transition is the first data capture edge */
/**
  * @} MD_SPI_PC_PHASE
  */

/** @defgroup MD_SPI_PC_POLARITY SPI Clock Polarity
  * @{
  */
#define MD_SPI_POLARITY_LOW                0x00000000U                /*!< Clock to 0 when idle */
#define MD_SPI_POLARITY_HIGH               (SPI_CON1_CPOL_MSK)        /*!< Clock to 1 when idle */
/**
  * @} MD_SPI_PC_POLARITY
  */

/** @defgroup MD_SPI_PC_BAUDRATEPRESCALER SPI Baud Rate Prescaler
  * @{
  */
#define MD_SPI_BAUDRATEPRESCALER_DIV2      0x00000000U                        /*!< BaudRate control equal to fPCLK/2   */
#define MD_SPI_BAUDRATEPRESCALER_DIV4      (0x1U<<SPI_CON1_BAUD_POSS)         /*!< BaudRate control equal to fPCLK/4   */
#define MD_SPI_BAUDRATEPRESCALER_DIV8      (0x2U<<SPI_CON1_BAUD_POSS)         /*!< BaudRate control equal to fPCLK/8   */
#define MD_SPI_BAUDRATEPRESCALER_DIV16     (0x3U<<SPI_CON1_BAUD_POSS)         /*!< BaudRate control equal to fPCLK/16   */
#define MD_SPI_BAUDRATEPRESCALER_DIV32     (0x4U<<SPI_CON1_BAUD_POSS)          /*!< BaudRate control equal to fPCLK/32  */
#define MD_SPI_BAUDRATEPRESCALER_DIV64     (0x5U<<SPI_CON1_BAUD_POSS)         /*!< BaudRate control equal to fPCLK/64  */
#define MD_SPI_BAUDRATEPRESCALER_DIV128    (0x6U<<SPI_CON1_BAUD_POSS)         /*!< BaudRate control equal to fPCLK/128 */
#define MD_SPI_BAUDRATEPRESCALER_DIV256    (0x7U<<SPI_CON1_BAUD_POSS)         /*!< BaudRate control equal to fPCLK/256 */
/**
  * @} MD_SPI_PC_BAUDRATEPRESCALER
  */

/** @defgroup MD_SPI_PC_BIT_ORDER SPI Transmission Bit Order
  * @{
  */
#define MD_SPI_LSB_FIRST                   (SPI_CON1_LSBFST_MSK)      /*!< Data is transmitted/received with the LSB first */
#define MD_SPI_MSB_FIRST                   0x00000000U                /*!< Data is transmitted/received with the MSB first */
/**
  * @} MD_SPI_PC_BIT_ORDER
  */

/** @defgroup MD_SPI_PC_TRANSFER_DIRECTION SPI Transfer Direction
  * @{
  */
#define MD_SPI_FULL_DUPLEX                0x00000000U                                 /*!< Full-Duplex mode. Rx and Tx transfer on 2 lines */
#define MD_SPI_HALF_DUPLEX                (SPI_CON1_BIDEN_MSK)                        /*!< Half-Duplex Rx mode. Rx transfer on 1 line      */
/**
  * @} MD_SPI_PC_TRANSFER_DIRECTION
  */

/** @defgroup MD_SPI_PC_FRAME_FORMAT SPI Transfer Mode
  * @{
  */
#define MD_SPI_FRAME_FORMAT_8BIT                0x00000000U                              /*!< 8 bits data format */
#define MD_SPI_FRAME_FORMAT_16BIT               (SPI_CON1_DLEN_MSK)                      /*!< 16 bits data format    */
/**
  * @} MD_SPI_PC_FRAME_FORMAT
  */

/** @defgroup MD_SPI_PC_RX_FIFO_TH SPI RX FIFO Threshold
  * @{
  */
#define MD_SPI_RX_FIFO_TH_1BIT          0x0U              /*!< RXTHIE event is generated if FIFO level is greater than or equel to 1 bit */
#define MD_SPI_RX_FIFO_TH_4BIT          0x1U              /*!< RXTHIE event is generated if FIFO level is greater than or equel to 4 bit  */
#define MD_SPI_RX_FIFO_TH_8BIT          0x2U              /*!< RXTHIE event is generated if FIFO level is greater than or equel to 8 bit  */
#define MD_SPI_RX_FIFO_TH_14BIT         0x3U              /*!< RXTHIE event is generated if FIFO level is greater than or equel to 14 bit  */
/**
  * @} MD_SPI_PC_RX_FIFO_TH
  */

/** @defgroup MD_SPI_PC_TX_FIFO_TH SPI TX FIFO Threshold
  * @{
  */
#define MD_SPI_TX_FIFO_TH_0BIT          0x0U             /*!< TXTHIE event is generated if FIFO level is below or equel to 0 bit */
#define MD_SPI_TX_FIFO_TH_2BIT          0x1U             /*!< TXTHIE event is generated if FIFO level is below than or equel to 2 bit  */
#define MD_SPI_TX_FIFO_TH_4BIT          0x2U             /*!< TXTHIE event is generated if FIFO level is below than or equel to 4 bit  */
#define MD_SPI_TX_FIFO_TH_8BIT          0x3U             /*!< TXTHIE event is generated if FIFO level is below than or equel to 8 bit  */
/**
  * @} MD_SPI_PC_TX_FIFO_TH
  */

/** @defgroup MD_SPI_PC_NSS_MODE SPI Slave Select Pin Mode
  * @{
  */

#define MD_SPI_NSS_SOFT                    (SPI_CON1_SSEN_MSK)           /*!< NSS managed internally  */
#define MD_SPI_NSS_HARD                    (0x00000000U)                 /*!< NSS pin is controled by hardware */
/**
  * @} MD_SPI_PC_NSS_MODE
  */
  

/** @defgroup MD_SPI_EC_CRC_CALCULATION SPI CRC Calculation
  * @{
  */
#define MD_SPI_CRCCALCULATION_DISABLE      0x00000000U                /*!< CRC calculation disabled */
#define MD_SPI_CRCCALCULATION_ENABLE       (SPI_CON1_CRCEN_MSK)       /*!< CRC calculation enabled  */
/**
  * @} MD_SPI_EC_CRC_CALCULATION
  */


/** @defgroup MD_SPI_PC_I2S_CHANNEL_LENGTH I2S Channel length
  * @{
  */
#define MD_I2S_CHANNEL_LENGTH_16BIT                0x00000000U                  /*!< 16 bits wide */
#define MD_I2S_CHANNEL_LENGTH_32BIT                (SPI_I2SCFG_CHLEN_MSK)       /*!< 32 bits wide */
/**
  * @} MD_SPI_PC_CHANNEL_LENGTH
  */
  
/** @defgroup MD_SPI_PC_I2S_CLOCK_POLARITY I2S Clock polarity
  * @{
  */
#define MD_I2S_POLARITY_LOW                0x00000000U                  /*!< Clock to 0 when idle */
#define MD_I2S_POLARITY_HIGH               (SPI_I2SCFG_CKPOL_MSK)       /*!< Clock to 1 when idle */
/**
  * @} MD_SPI_PC_I2S_CLOCK_POLARITY
  */


/** @defgroup MD_SPI_PC_I2S_DATA_LENGTH I2S Data Length
  * @{
  */
#define MD_I2S_DATA_LENGTH_16BIT          0x00000000U                       /*!< I2S data length to be transferred 16-bit data length */
#define MD_I2S_DATA_LENGTH_24BIT          (0x1U<<SPI_I2SCFG_DATLEN_POSS)    /*!< I2S data length to be transferred  24-bit data length  */
#define MD_I2S_DATA_LENGTH_32BIT          (0x2U<<SPI_I2SCFG_DATLEN_POSS)    /*!< I2S data length to be transferred  32-bit data length  */
#define MD_I2S_DATA_LENGTH_NOT_ALLOWED    (0x3U<<SPI_I2SCFG_DATLEN_POSS)    /*!< I2S data length to be transferred  Not allowed  */
/**
  * @} MD_SPI_PC_I2S_DATA_LENGTH
  */
  

/** @defgroup MD_SPI_PC_I2S_STANDARD_SELECTION I2S standard selection
  * @{
  */
#define MD_I2S_PHILIPS_STANDARD           0x00000000U                       /*!< I2S standard selection philips  */
#define MD_I2S_MSB_STANDARD               (0x1U<<SPI_I2SCFG_I2SSTD_POSS)    /*!< I2S standard selection MSB  */
#define MD_I2S_LSB_STANDARD               (0x2U<<SPI_I2SCFG_I2SSTD_POSS)    /*!< I2S standard selection LSB  */
#define MD_I2S_PCM_STANDARD               (0x3U<<SPI_I2SCFG_I2SSTD_POSS)    /*!< I2S standard selection PCM  */
/**
  * @} MD_SPI_PC_I2S_standard_selection
  */
  
/** @defgroup MD_SPI_PC_I2S_FRAME_SYNCHRONIZATION I2S Frame Synchronization
  * @{
  */
#define MD_I2S_FRAME_SYN_SHORT                0x00000000U                    /*!< Short frame synchronization */
#define MD_I2S_FRAME_SYN_LONG                 (SPI_I2SCFG_PCMSYNC_MSK)       /*!< Long frame synchronization */
/**
  * @} MD_SPI_PC_I2S_FRAME_SYNCHRONIZATION
  */
  
/** @defgroup MD_SPI_PC_I2S_MODE_SELECTION I2S Mode Selection
  * @{
  */
#define MD_I2S_MODE_SPI                 0x00000000U                   /*!< SPI mode is selection */
#define MD_I2S_MODE_I2S                 (SPI_I2SCFG_I2SMOD_MSK)       /*!< I2S mode is seleciton */
/**
  * @} MD_SPI_PC_I2S_FRAME_SYNCHRONIZATION
  */

/** @defgroup MD_SPI_PC_I2S_CFG_MODE I2S Configuration Mode
  * @{
  */
#define MD_I2S_SLAVE_TX                0x00000000U  /*!< I2S configuartion mode slave transmit  */
#define MD_I2S_SLAVE_RX                (0x1U<<SPI_I2SCFG_I2SCFG_POSS)  /*!< I2S configuartion mode slave receive  */
#define MD_I2S_MASTER_TX               (0x2U<<SPI_I2SCFG_I2SCFG_POSS)  /*!< I2S configuartion mode master transmit  */
#define MD_I2S_MASTER_RX               (0x3U<<SPI_I2SCFG_I2SCFG_POSS)  /*!< I2S configuartion mode master receive  */
/**
  * @} MD_SPI_PC_I2S_CFG_MODE
  */ 

/** @defgroup MD_SPI_PC_I2S_EXTERN_CLOCK I2S Extern Clock 
  * @{
  */
#define MD_I2S_EVEN                 0x00000000U               /*!< Real divider value is = (I2SDIV * 2) */
#define MD_I2S_ODD                  (SPI_I2SPR_ODD_MSK)       /*!< Real divider value is = (I2SDIV * 2)+1 */
/**
  * @} MD_SPI_PC_I2S_EXTERN_CLOCK
  */

/** @defgroup MD_SPI_PC_I2S_EXTERN_CLOCK I2S Extern Clock 
  * @{
  */
#define MD_I2S_APB_CLOCK                0x00000000U                   /*!< APB clock is selection */
#define MD_I2S_EXTERNAL_CLOCK           (SPI_I2SPR_EXTCKEN_MSK)       /*!< External clock is seleciton */
/**
  * @} MD_SPI_PC_I2S_EXTERN_CLOCK
  */


typedef struct ald_spi_handle_s
{
  SPI_TypeDef *SPI;
  md_spi_inittypedef init;
  uint8_t tx_size;
  uint8_t rx_size;
  uint8_t tx_count;
  uint8_t rx_count;
  uint8_t *tx_buf;
  uint8_t *rx_buf;
  uint32_t ifm_buf; 
} md_spi_handle_t;

/**
  * @} MD_SPI_Public_Constants
  */

/* Public macro ---------------------------------------------------------------*/
/** @defgroup MD_SPI_Public_Macros SPI Public Macros
  * @{
  */
/** @defgroup MD_SPI_CON1 SPI Control Register 1
  * @{
  */

/**
  * @brief  Set SPI control register (SPIx_CON1)
  * @param  SPIx SPI Instance 
  * @param  value The value write in SPIx_CON1
  * @retval None
  */
__STATIC_INLINE void md_spi_set_con1(SPI_TypeDef *SPIx, uint32_t value)
{
  WRITE_REG(SPIx->CON1, value);
}

/**
  * @brief  Get SPI control register (SPIx_CON1)
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_get_con1(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_REG(SPIx->CON1));
}

/**

  * @brief  Set SPI clock phase
  * @note   This bit should not be changed when communication is ongoing. \n
            This bit is not used in SPI TI mode.
  * @param  SPIx SPI Instance
  * @param  ClockPhase This parameter can be one of the following values:
  *         @arg @ref MD_SPI_PHASE_1EDGE
  *         @arg @ref MD_SPI_PHASE_2EDGE
  * @retval None

  */
__STATIC_INLINE void md_spi_set_con1_cpha(SPI_TypeDef *SPIx, uint32_t ClockPhase)
{
  MODIFY_REG(SPIx->CON1, SPI_CON1_CPHA_MSK, ClockPhase);
}

/**
  * @brief  Get SPI clock phase
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_SPI_PHASE_1EDGE
  *         @arg @ref MD_SPI_PHASE_2EDGE
  */
__STATIC_INLINE uint32_t md_spi_get_con1_cpha(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CON1, SPI_CON1_CPHA_MSK)>>SPI_CON1_CPHA_POS);
}

/**
  * @brief  Set SPI clock polarity
  * @note   This bit should not be changed when communication is ongoing.
  *         This bit is not used in SPI TI mode.
  * @param  SPIx SPI Instance
  * @param  ClockPolarity This parameter can be one of the following values:
  *         @arg @ref MD_SPI_POLARITY_LOW
  *         @arg @ref MD_SPI_POLARITY_HIGH
  * @retval None
  */
__STATIC_INLINE void md_spi_set_con1_cpol(SPI_TypeDef *SPIx, uint32_t ClockPolarity)
{
  MODIFY_REG(SPIx->CON1, SPI_CON1_CPOL_MSK, ClockPolarity);
}

/**
  * @brief  Get SPI clock polarity
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_SPI_POLARITY_LOW
  *         @arg @ref MD_SPI_POLARITY_HIGH
  */
__STATIC_INLINE uint32_t md_spi_get_con1_cpol(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CON1, SPI_CON1_CPOL_MSK)>>SPI_CON1_CPOL_POS);
}

/**
  * @brief  Set SPI master selection
  * @note   This bit should not be changed when communication is ongoing.
  * @param  SPIx SPI Instance
  * @param  Mode This parameter can be one of the following values:
  *         @arg @ref MD_SPI_MODE_MASTER
  *         @arg @ref MD_SPI_MODE_SLAVE
  * @retval None
  */
__STATIC_INLINE void md_spi_set_con1_mstren(SPI_TypeDef *SPIx, uint32_t Mode)
{
  MODIFY_REG(SPIx->CON1, SPI_CON1_MSTREN_MSK, Mode);
}

/**
  * @brief  Get SPI SPI operation mode (Master or Slave)
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_SPI_MODE_MASTER
  *         @arg @ref MD_SPI_MODE_SLAVE
  */
__STATIC_INLINE uint32_t md_spi_get_con1_mstren(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CON1, SPI_CON1_MSTREN_MSK )>>SPI_CON1_MSTREN_POS);
}

/**
  * @brief  Set SPI baud rate control
  * @note   These bits should not be changed when communication is ongoing. SPI BaudRate = fPCLK/Prescaler.
  * @param  SPIx SPI Instance
  * @param  BaudRate This parameter can be one of the following values:
  *         @arg @ref MD_SPI_BAUDRATEPRESCALER_DIV2
  *         @arg @ref MD_SPI_BAUDRATEPRESCALER_DIV4
  *         @arg @ref MD_SPI_BAUDRATEPRESCALER_DIV8
  *         @arg @ref MD_SPI_BAUDRATEPRESCALER_DIV16
  *         @arg @ref MD_SPI_BAUDRATEPRESCALER_DIV32
  *         @arg @ref MD_SPI_BAUDRATEPRESCALER_DIV64
  *         @arg @ref MD_SPI_BAUDRATEPRESCALER_DIV128
  *         @arg @ref MD_SPI_BAUDRATEPRESCALER_DIV256
  * @retval None
  */
__STATIC_INLINE void md_spi_set_con1_baud(SPI_TypeDef *SPIx, uint32_t BaudRate)
{
  MODIFY_REG(SPIx->CON1, SPI_CON1_BAUD_MSK, BaudRate);
}

/**
  * @brief  Get SPI baud rate prescaler
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_SPI_BAUDRATEPRESCALER_DIV2
  *         @arg @ref MD_SPI_BAUDRATEPRESCALER_DIV4
  *         @arg @ref MD_SPI_BAUDRATEPRESCALER_DIV8
  *         @arg @ref MD_SPI_BAUDRATEPRESCALER_DIV16
  *         @arg @ref MD_SPI_BAUDRATEPRESCALER_DIV32
  *         @arg @ref MD_SPI_BAUDRATEPRESCALER_DIV64
  *         @arg @ref MD_SPI_BAUDRATEPRESCALER_DIV128
  *         @arg @ref MD_SPI_BAUDRATEPRESCALER_DIV256
  */
__STATIC_INLINE uint32_t md_spi_get_con1_baud(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CON1, SPI_CON1_BAUD_MSK)>>SPI_CON1_BAUD_POSS);
}

/**
  * @brief  Enable SPI peripheral
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_enable_con1_spien(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->CON1, SPI_CON1_SPIEN_MSK);
}

/**
  * @brief  Disable SPI peripheral
  * @note   When disabling the SPI, follow the procedure described in the Reference Manual.
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_disable_con1_spien(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->CON1, SPI_CON1_SPIEN_MSK);
}

/**
  * @brief  Check if SPI peripheral is enabled
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_enable_con1_spien(SPI_TypeDef *SPIx)
{
  return (READ_BIT(SPIx->CON1, SPI_CON1_SPIEN_MSK) == (SPI_CON1_SPIEN_MSK));
}

/**
  * @brief  Set SPI frame format
  * @note   This bit should not be changed when communication is ongoing. This bit is not used in SPI TI mode.
  * @param  SPIx SPI Instance
  * @param  BitOrder This parameter can be one of the following values:
  *         @arg @ref MD_SPI_LSB_FIRST
  *         @arg @ref MD_SPI_MSB_FIRST
  * @retval None
  */
__STATIC_INLINE void md_spi_set_con1_lsbfirst(SPI_TypeDef *SPIx, uint32_t BitOrder)
{
  MODIFY_REG(SPIx->CON1, SPI_CON1_LSBFST_MSK, BitOrder);
}

/**
  * @brief  Get SPI transfer bit order
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_SPI_LSB_FIRST
  *         @arg @ref MD_SPI_MSB_FIRST
  */
__STATIC_INLINE uint32_t md_spi_get_con1_lsbfirst(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CON1, SPI_CON1_LSBFST_MSK)>>SPI_CON1_LSBFST_POS);
}

/**
  * @brief  Set SPI Internal slave select
  * @note   This bit has an effect only when the SSEN bit is set. The value of this bit is forced onto the NSS pin.
  * @param  SPIx SPI Instance
  * @param  value This bit can be set to:   
  *         @arg BIT_SET
  *         @arg BIT_RESET
  * @retval None
  */
__STATIC_INLINE void md_spi_set_con1_ssout(SPI_TypeDef *SPIx, uint32_t value)
{
  MODIFY_REG(SPIx->CON1, SPI_CON1_SSOUT_MSK , value);
}

/**
  * @brief  Get SPI Internal slave select
  * @param  SPIx SPI Instance
  * @retval State of 1 or 0
  */
__STATIC_INLINE uint32_t md_spi_get_con1_ssout(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CON1, SPI_CON1_SSOUT_MSK)>>SPI_CON1_SSOUT_POS);
}

/**
  * @brief  Enable SPI software slave management
  * @note   When the SSEN bit is set, the NSS pin input is replaced with the value from the SSOUT bit.
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_enable_con1_ssen(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->CON1, SPI_CON1_SSEN_MSK);
}

/**
  * @brief  Disable SPI software slave management
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_disable_con1_ssen(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->CON1, SPI_CON1_SSEN_MSK);
}

/**
  * @brief  Check if SPI peripheral is software slave management
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_enable_con1_ssen(SPI_TypeDef *SPIx)
{
  return (READ_BIT(SPIx->CON1, SPI_CON1_SSEN_MSK) == (SPI_CON1_SSEN_MSK));
}

/**
  * @brief  Set SPI receive only mode enable
  * @note   This bit enables simplex communication using a single unidirectional line to receive data exclusively. \n
            Keep BIDEN bit clear when receive only mode is active.This bit is also useful in a multislave system \n
            in which this particular slave is not accessed, the output from the accessed slave is not corrupted.
  * @param  SPIx SPI Instance
  * @param  value This bit can be set to:   
  *         @arg  BIT_SET
  *         @arg  BIT_RESET
  * @retval None
  */
__STATIC_INLINE void md_spi_set_con1_rxo(SPI_TypeDef *SPIx, uint32_t value)
{
  MODIFY_REG(SPIx->CON1, SPI_CON1_RXO_MSK , value);
}

/**
  * @brief  Set SPI receive only mode enable
  * @param  SPIx SPI Instance
  * @retval State of 1 or 0
  */
__STATIC_INLINE uint32_t md_spi_get_con1_rxo(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CON1, SPI_CON1_RXO_MSK)>>SPI_CON1_RXO_POS);
}

/**
  * @brief  Set data frame format
  * @param  SPIx SPI Instance
  * @param  DataWidth This parameter can be one of the following values:
  *         @arg @ref MD_SPI_FRAME_FORMAT_8BIT
  *         @arg @ref MD_SPI_FRAME_FORMAT_16BIT
  * @retval None
  */
__STATIC_INLINE void md_spi_set_con1_flen(SPI_TypeDef *SPIx, uint32_t DataWidth)
{
  MODIFY_REG(SPIx->CON1, SPI_CON1_FLEN_MSK, DataWidth);
}

/**
  * @brief  Get data frame format
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_SPI_FRAME_FORMAT_8BIT
  *         @arg @ref MD_SPI_FRAME_FORMAT_16BIT
  */
__STATIC_INLINE uint32_t md_spi_get_con1_flen(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CON1, SPI_CON1_FLEN_MSK)>>SPI_CON1_FLEN_POS);
}

/**
  * @brief  Set CRCNext to transfer CRC on the line
  * @note   This bit has to be written as soon as the last data is written in the SPIx_DATA register.
  * @param  SPIx SPI Instance
  * @param  value This bit can be set to:   
  *         @arg  BIT_SET
  *         @arg  BIT_RESET
  * @retval None
  */
__STATIC_INLINE void md_spi_set_con1_crcnext(SPI_TypeDef *SPIx, uint32_t value)
{
  MODIFY_REG(SPIx->CON1, SPI_CON1_NXTCRC_MSK, value);
}

/**
  * @brief  Get CRCNext to transfer CRC on the line
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  * @retval State of 1 or 0
  */
__STATIC_INLINE uint32_t md_spi_get_con1_crcnext(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CON1, SPI_CON1_NXTCRC_MSK)>>SPI_CON1_NXTCRC_POS);
}

/**
  * @brief  Enable SPI hardware CRC calculation
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_enable_con1_crcen(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->CON1, SPI_CON1_CRCEN_MSK);
}

/**
  * @brief  Disable SPI hardware CRC calculation
  * @note   When disabling the SPI, follow the procedure described in the Reference Manual.
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_disable_con1_crcen(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->CON1, SPI_CON1_CRCEN_MSK);
}

/**
  * @brief  Check if hardware CRC calculation is enabled
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_enable_con1_crcen(SPI_TypeDef *SPIx)
{
  return (READ_BIT(SPIx->CON1, SPI_CON1_CRCEN_MSK) == (SPI_CON1_CRCEN_MSK));
}

/**
  * @brief  Enable SPI Output enable in bidirectional mode
  * @note   Output enable in bidirectional mode. This bit combined with the BIDEN bit selects the direction of \n
            transfer in bidirectional mode
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_enable_con1_bidoen(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->CON1, SPI_CON1_BIDOEN_MSK);
}

/**
  * @brief  Disable Output enable in bidirectional mode
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_disable_con1_bidoen(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->CON1, SPI_CON1_BIDOEN_MSK);
}

/**
  * @brief  Check if Output enable in bidirectional mode is enabled
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_enable_con1_bidoen(SPI_TypeDef *SPIx)
{
  return (READ_BIT(SPIx->CON1, SPI_CON1_BIDOEN_MSK) == (SPI_CON1_BIDOEN_MSK));
}

/**
  * @brief  Set Bidirectional data mode enable
  * @note   Bidirectional data mode enable. This bit enables  half-duplex communication using common single bidirectional \n
            data line. Keep RXO bit clear when bidirectional mode is active.
  * @param  SPIx SPI Instance
  * @param  value This bit can be set to:   
  * @arg @ref MD_SPI_FULL_DUPLEX
  * @arg @ref MD_SPI_HALF_DUPLEX
  * @retval None
  */
__STATIC_INLINE void md_spi_set_con1_bidimode(SPI_TypeDef *SPIx, uint32_t value)
{
  MODIFY_REG(SPIx->CON1, SPI_CON1_BIDEN_MSK, value);
}

/**
  * @brief  Get Bidirectional data mode enable
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  * @retval Return follow:
  * @arg @ref MD_SPI_FULL_DUPLEX
  * @arg @ref MD_SPI_HALF_DUPLEX
  */
__STATIC_INLINE uint32_t md_spi_get_con1_bidimode(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CON1, SPI_CON1_BIDEN_MSK)>>SPI_CON1_BIDEN_POS);
}


/**
  * @} MD_SPI_CON1
  */



/** @defgroup MD_SPI_CON2 SPI Control Register 2
  * @{
  */

/**
  * @brief  Set SPI control register 2 (SPIx_CON2)
  * @param  SPIx SPI Instance 
  * @param  value The value write in SPIx_CON2
  * @retval None
  */
__STATIC_INLINE void md_spi_set_con2(SPI_TypeDef *SPIx, uint32_t value)
{
  WRITE_REG(SPIx->CON2, value);
}

/**
  * @brief  Get SPI control register 2(SPIx_CON2)
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_get_con2(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_REG(SPIx->CON2));
}


/**
  * @brief  Enable Rx buffer DMA 
  * @note   When this bit is set, a DMA request is generated whenever the RXTH flag is set.
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_enable_con2_rxdmaen(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->CON2, SPI_CON2_RXDMA_MSK);
}

/**
  * @brief  Disable Rx buffer DMA 
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_disable_con2_rxdmaen(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->CON2, SPI_CON2_RXDMA_MSK);
}

/**
  * @brief  Check if Rx buffer DMA  is enabled
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_enabled_con2_rxdmaen(SPI_TypeDef *SPIx)
{
  return (READ_BIT(SPIx->CON2, SPI_CON2_RXDMA_MSK) == (SPI_CON2_RXDMA_MSK));
}

/**
  * @brief  Enable Tx buffer DMA enable
  * @note   When this bit is set, a DMA request is generated whenever the TXTH flag is set. 
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_enable_con2_txdmaen(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->CON2, SPI_CON2_TXDMA_MSK);
}

/**
  * @brief  Disable Tx buffer DMA enable
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_disable_con2_txdmaen(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->CON2, SPI_CON2_TXDMA_MSK);
}

/**
  * @brief  Check if Tx buffer DMA enable is enabled
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_enabled_con2_txdmaen(SPI_TypeDef *SPIx)
{
  return (READ_BIT(SPIx->CON2, SPI_CON2_TXDMA_MSK) == (SPI_CON2_TXDMA_MSK));
}

/**
  * @brief  Enable SS output enable
  * @note   SS output is enabled in master mode and when the SPI interface is enabled. The SPI interface cannot \n
            work in a multimaster environment.
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_enable_con2_ssoe(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->CON2, SPI_CON2_NSSOE_MSK);
}

/**
  * @brief  Disable SS output enable
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_disable_con2_ssoe(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->CON2, SPI_CON2_NSSOE_MSK);
}

/**
  * @brief  Check if SS output enable is enabled
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_enabled_con2_ssoe(SPI_TypeDef *SPIx)
{
  return (READ_BIT(SPIx->CON2, SPI_CON2_NSSOE_MSK) == (SPI_CON2_NSSOE_MSK));
}

/**
  * @brief  Enable NSS pulse management
  * @note   This bit is used in master mode only. It allow the SPI to generate an NSS pulse between two consecutive \n
            data when doing continuous transfers. In the case of a single data transfer, it forces the NSS pin high \n
            level after the transfer. It has no meaning if CPHA = ’1’, or FRF = ’1’.This bit should not be changed \n
            when communication is ongoing. This bit is not used in SPI TI mode.
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_enable_con2_nssp(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->CON2, SPI_CON2_NSSP_MSK);
}

/**
  * @brief  Disable NSS pulse management
  * @note   This bit should not be changed when communication is ongoing. This bit is not used in SPI TI mode.
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_disable_con2_nssp(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->CON2, SPI_CON2_NSSP_MSK);
}

/**
  * @brief  Check if NSS pulse is enabled
  * @note   This bit should not be changed when communication is ongoing. This bit is not used in SPI TI mode.
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_enabled_con2_nssp(SPI_TypeDef *SPIx)
{
  return (READ_BIT(SPIx->CON2, SPI_CON2_NSSP_MSK) == (SPI_CON2_NSSP_MSK));
}

/**
  * @brief  Set frame format
  * @note   This bit should be written only when SPI is disabled (SPE = 0) for correct operation.
  * @param  SPIx SPI Instance
  * @param  Standard This parameter can be one of the following values:
  *         @arg @ref MD_SPI_PROTOCOL_MOTOROLA
  *         @arg @ref MD_SPI_PROTOCOL_TI
  * @retval None
  */
__STATIC_INLINE void md_spi_set_con2_frf(SPI_TypeDef *SPIx, uint32_t Standard)
{
  MODIFY_REG(SPIx->CON2, SPI_CON2_FRF_MSK, Standard);
}

/**
  * @brief  Get frame format
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_SPI_PROTOCOL_MOTOROLA
  *         @arg @ref MD_SPI_PROTOCOL_TI
  */
__STATIC_INLINE uint32_t md_spi_get_con2_frf(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CON2, SPI_CON2_FRF_MSK)>>SPI_CON2_FRF_POS);
}


/**
  * @brief  Set transmit FIFO trigger threshold
  * @note   This is used to select the threshold level in the transmit FIFO at which the Transmit FIFO \n
            trigger threshold flag is generated.
  * @param  SPIx SPI Instance
  * @param  Threshold This parameter can be one of the following values:
  *         @arg @ref MD_SPI_TX_FIFO_TH_0BIT
  *         @arg @ref MD_SPI_TX_FIFO_TH_2BIT
  *         @arg @ref MD_SPI_TX_FIFO_TH_4BIT
  *         @arg @ref MD_SPI_TX_FIFO_TH_8BIT
  * @retval None
  */
__STATIC_INLINE void md_spi_set_con2_txfth(SPI_TypeDef *SPIx, uint32_t Threshold)
{
  MODIFY_REG(SPIx->CON2, SPI_CON2_TXFTH_MSK, Threshold<<SPI_CON2_TXFTH_POSS);
}

/**
  * @brief  Get transmit FIFO trigger threshold
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_SPI_TX_FIFO_TH_0BIT
  *         @arg @ref MD_SPI_TX_FIFO_TH_2BIT
  *         @arg @ref MD_SPI_TX_FIFO_TH_4BIT
  *         @arg @ref MD_SPI_TX_FIFO_TH_8BIT
  */
__STATIC_INLINE uint32_t md_spi_get_con2_txfth(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CON2, SPI_CON2_TXFTH_MSK)>>SPI_CON2_TXFTH_POSS);
}

/**
  * @brief  Set receive FIFO trigger threshold
  * @note   This is used to select the threshold level in the receiver FIFO at which the Receive FIFO \n
            trigger threshold flag is generated. 
  * @param  SPIx SPI Instance
  * @param  Threshold This parameter can be one of the following values:
  *         @arg @ref MD_SPI_RX_FIFO_TH_1BIT
  *         @arg @ref MD_SPI_RX_FIFO_TH_4BIT
  *         @arg @ref MD_SPI_RX_FIFO_TH_8BIT
  *         @arg @ref MD_SPI_RX_FIFO_TH_14BIT
  * @retval None
  */
__STATIC_INLINE void md_spi_set_con2_rxfth(SPI_TypeDef *SPIx, uint32_t Threshold)
{
  MODIFY_REG(SPIx->CON2, SPI_CON2_RXFTH_MSK, Threshold<<SPI_CON2_RXFTH_POSS);
}

/**
  * @brief  Get receive FIFO trigger threshold
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_SPI_RX_FIFO_TH_1BIT
  *         @arg @ref MD_SPI_RX_FIFO_TH_4BIT
  *         @arg @ref MD_SPI_RX_FIFO_TH_8BIT
  *         @arg @ref MD_SPI_RX_FIFO_TH_14BIT
  */
__STATIC_INLINE uint32_t md_spi_get_con2_rxfth(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CON2, SPI_CON2_RXFTH_MSK)>>SPI_CON2_RXFTH_POSS);
}


/**
  * @} MD_SPI_CON2
  */

/**
  * @defgroup MD_SPI_STAT SPI Status Register
  * @{ 
  */


/**
  * @brief  Get SPI status register(SPIx_STAT)
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_get_stat(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_REG(SPIx->STAT));
}

/**
  * @brief  Check if SPI transmit buffer empty is actived
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_stat_txe(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->STAT, SPI_STAT_TXE_MSK)== (SPI_STAT_TXE_MSK));
}

/**
  * @brief  Check if SPI transmit buffer full is actived
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_stat_txf(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->STAT, SPI_STAT_TXF_MSK)== (SPI_STAT_TXF_MSK));
}

/**
  * @brief  Check if SPI transmit buffer overflow is actived
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_stat_txov(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->STAT, SPI_STAT_TXOV_MSK)== (SPI_STAT_TXOV_MSK));
}

/**
  * @brief  Check if SPI transmit buffer underflow is actived
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_stat_txud(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->STAT, SPI_STAT_TXUD_MSK) == (SPI_STAT_TXUD_MSK));
}

/**
  * @brief  Check if SPI Tx FIFO level under threshold is actived
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_stat_txth(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->STAT, SPI_STAT_TXTH_MSK) == (SPI_STAT_TXTH_MSK));
}

/**
  * @brief  Check if SPI receive buffer empty is actived
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_stat_rxe(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->STAT, SPI_STAT_RXE_MSK) == (SPI_STAT_RXE_MSK));
}

/**
  * @brief  Check if SPI receive buffer full is actived
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_stat_rxf(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->STAT, SPI_STAT_RXF_MSK)== (SPI_STAT_RXF_MSK));
}

/**
  * @brief  Get SPI receive buffer overflow
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_stat_rxov(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CON2, SPI_STAT_RXOV_MSK)== (SPI_STAT_RXOV_MSK));
}

/**
  * @brief  Check if SPI receive buffer underflow is actived
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_stat_rxud(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->STAT, SPI_STAT_RXUD_MSK)== (SPI_STAT_RXUD_MSK));
}

/**
  * @brief  Check if SPI Rx FIFO level over threshold is actived
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_stat_rxth(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->STAT, SPI_STAT_RXTH_MSK)== (SPI_STAT_RXTH_MSK));
}

/**
  * @brief  Check if SPI channel side is actived
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_stat_chside(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->STAT, SPI_STAT_CHSIDE_MSK)== (SPI_STAT_CHSIDE_MSK));
}

/**
  * @brief  Check if SPI busy flag is actived
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_stat_busy(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->STAT, SPI_STAT_BUSY_MSK)== (SPI_STAT_BUSY_MSK));
}

/**
  * @brief  Get SPI Tx FIFO level
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_get_stat_txflv(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->STAT, SPI_STAT_TXFLV_MSK) >> SPI_STAT_TXFLV_POSS);
}

/**
  * @brief  Get SPI Rx FIFO level
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_get_stat_rxflv(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->STAT, SPI_STAT_RXFLV_MSK) >> SPI_STAT_RXFLV_POSS);
}

/**
  * @} MD_SPI_STAT
  */


/** @defgroup MD_SPI_DATA SPI Data Register
  * @{
  */

/**
  * @brief  Read 8-Bits in the data register
  * @param  SPIx SPI Instance
  * @retval RxData Value between Min_Data=0x00 and Max_Data=0xFF
  */
__STATIC_INLINE uint8_t md_spi_recv_data8(SPI_TypeDef *SPIx)
{
  return (uint8_t)(READ_REG(SPIx->DATA));
}

/**
  * @brief  Read 16-Bits in the data register
  * @param  SPIx SPI Instance
  * @retval RxData Value between Min_Data=0x00 and Max_Data=0xFFFF
  */
__STATIC_INLINE uint16_t md_spi_recv_data16(SPI_TypeDef *SPIx)
{
  return (uint16_t)(READ_REG(SPIx->DATA));
}

/**
  * @brief  Write 8-Bits in the data register
  * @param  SPIx SPI Instance
  * @param  TxData Value between Min_Data=0x00 and Max_Data=0xFF
  * @retval None
  */
__STATIC_INLINE void md_spi_send_data8(SPI_TypeDef *SPIx, uint8_t TxData)
{
  SPIx->DATA = (uint8_t)TxData;
}

/**
  * @brief  Write 16-Bits in the data register
  * @param  SPIx SPI Instance
  * @param  TxData Value between Min_Data=0x0000 and Max_Data=0xFFFF
  * @retval None
  */
__STATIC_INLINE void md_spi_send_data16(SPI_TypeDef *SPIx, uint16_t TxData)
{
  SPIx->DATA = (uint16_t)TxData;
}

/** 
  * @} MD_SPI_DATA
  */

/** @defgroup MD_SPI_CRC SPI CRC Manangement
  * @{ MD_SPI_CRC
  */

/**
  * @brief  Set CRC polynmomial register (SPIx_CRCPLOY)
  * @note   When CRC calculation is enabled, the RxCRC[15:0] bits contain the computed CRC value of the subsequently \n
            received bytes. This register is reset when the CRCEN bit in SPIx_CR1 register is written to 1. The CRC is \n
            calculated serially using the polynomial  programmed in the SPIx_CRCPLOY register. Only the 8 LSB bits are \n
            considered when the CRC frame format is set to be 8-bit length (CRCL bit in the SPIx_CON1 is cleared). CRC \n
            calculation is done based on any CRC8 standard. The entire 16-bits of this register are considered when a \n
            16-bit CRC frame format is selected (CRCL bit in the SPIx_CR1 register is set). CRC calculation is done based \n 
            on any CRC16 standard.
            Note: A read to this register when the BSY Flag is set could return an incorrect value. These bits are not \n
            used in I2S mode.
  * @param  SPIx SPI Instance
  * @param  CRCPoly This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFFFF
  * @retval None
  */
__STATIC_INLINE void md_spi_set_crcploy(SPI_TypeDef *SPIx, uint32_t CRCPoly)
{
  WRITE_REG(SPIx->CRCPOLY, (uint16_t)CRCPoly);
}

/**
  * @brief  Get CRC polynmomial register (SPIx_CRCPLOY)
  * @param  SPIx SPI Instance
  * @retval Returned value is a number between Min_Data = 0x00 and Max_Data = 0xFFFF
  */
__STATIC_INLINE uint32_t md_spi_get_crcploy(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_REG(SPIx->CRCPOLY));
}

/**
  * @brief  Get Rx CRC register
  * @note   When CRC calculation is enabled, the RxCRC[7:0] bits contain the computed CRC value of the subsequently \n
            transmitted bytes. This register is reset when the CRCEN bit of SPIx_CON1 is written to 1. The CRC is calculated \n
            serially using the polynomial programmed in the SPIx_CRCPLOY register. Only the 8 LSB bits are considered \n
            when the CRC frame format is set to be 8-bit length (FLEN bit in the SPIx_CON1 is cleared). CRC calculation is \n
            done based on any CRC8 standard. The entire 16-bits of this register are considered when a 16-bit CRC frame \n
            format is selected (CRCL bit in the SPIx_CR1 register is set). CRC calculation is done based on any CRC16 standard. \n
            Note: A read to this register when the BSY flag is set could return an incorrect value. These bits are not used \n
            in I2S mode.
  * @param  SPIx SPI Instance
  * @retval Returned value is a number between Min_Data = 0x00 and Max_Data = 0xFFFF
  */
__STATIC_INLINE uint32_t md_spi_get_rxcrc(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_REG(SPIx->RXCRC));
}

/**
  * @brief  Get Tx CRC register
  * @note   When CRC calculation is enabled, the TxCRC[7:0] bits contain the computed CRC value of the subsequently \n
            transmitted bytes. This register is reset when the CRCEN bit of SPIx_CON1 is written to 1. The CRC is calculated \n
            serially using the polynomial programmed in the SPIx_CRCPLOY register. Only the 8 LSB bits are considered \n
            when the CRC frame format is set to be 8-bit length (FLEN bit in the SPIx_CR1 is cleared). CRC calculation is \n
            done based on any CRC8 standard. The entire 16-bits of this register are considered when a 16-bit CRC frame \n
            format is selected (CRCL bit in the SPIx_CR1 register is set). CRC calculation is done based on any CRC16 standard. \n
            Note: A read to this register when the BSY flag is set could return an incorrect value. These bits are not used \n
            in I2S mode.
  * @param  SPIx SPI Instance
  * @retval Returned value is a number between Min_Data = 0x00 and Max_Data = 0xFFFF
  */
__STATIC_INLINE uint32_t md_spi_get_txcrc(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_REG(SPIx->TXCRC));
}

/**
  * @} MD_SPI_CRC
  */



/** @defgroup MD_SPI_I2S I2S Configuration Management
  * @{
  */


/** @defgroup MD_SPI_I2SCFG I2S Configuration register
  * @{
  */

/**
  * @brief  Set SPI I2S configuration register(SPIx_I2SCFG)
  * @param  SPIx SPI Instance 
  * @param  value The value write in SPIx_I2SCFG
  * @retval None
  */
__STATIC_INLINE void md_spi_set_I2SCFG(SPI_TypeDef *SPIx, uint32_t value)
{
  WRITE_REG(SPIx->I2SCFG, value);
}

/**
  * @brief  Get SPI I2S configuration register (SPIx_I2SCFG)
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_get_I2SCFG(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_REG(SPIx->I2SCFG));
}

/**
  * @brief  Set channel legth(number of bits per audio channel)
  * @note   The bit write operation has a meaning only if DATLEN = 00 otherwise the channel length is fixed to 32-bit by \n
            hardware whatever the value filled in.
            Note: For correct operation, this bit should be configured when the I2S is disabled. It is not used in SPI mode.
  * @param  SPIx SPI Instance
  * @param  value This bit can be set to:   
  *         @arg @ref MD_I2S_CHANNEL_LENGTH_16BIT
  *         @arg @ref MD_I2S_CHANNEL_LENGTH_32BIT
  * @retval None
  */
__STATIC_INLINE void md_spi_set_i2scfg_chlen(SPI_TypeDef *SPIx, uint32_t value)
{
  MODIFY_REG(SPIx->I2SCFG, SPI_I2SCFG_CHLEN_MSK, value);
}

/**
  * @brief  Get channel legth(number of bits per audio channel)
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  * @retval Return:
  *         @arg @ref MD_I2S_CHANNEL_LENGTH_16BIT
  *         @arg @ref MD_I2S_CHANNEL_LENGTH_32BIT
  */
__STATIC_INLINE uint32_t md_spi_get_i2scfg_chlen(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->I2SCFG, SPI_I2SCFG_CHLEN_MSK));
}

/**
  * @brief  Set Data length to be transferred
  * @param  SPIx SPI Instance
  * @param  value This bit can be set to:   
  *         @arg @ref MD_I2S_DATA_LENGTH_16BIT
  *         @arg @ref MD_I2S_DATA_LENGTH_24BIT
  *         @arg @ref MD_I2S_DATA_LENGTH_32BIT
  *         @arg @ref MD_I2S_DATA_LENGTH_NOT_ALLOWED
  * @retval None
  */
__STATIC_INLINE void md_spi_set_i2scfg_datlen(SPI_TypeDef *SPIx, uint32_t value)
{
  MODIFY_REG(SPIx->I2SCFG, SPI_I2SCFG_DATLEN_MSK, value);
}

/**
  * @brief  Get Data length to be transferred
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_I2S_DATA_LENGTH_16BIT
  *         @arg @ref MD_I2S_DATA_LENGTH_24BIT
  *         @arg @ref MD_I2S_DATA_LENGTH_32BIT
  *         @arg @ref MD_I2S_DATA_LENGTH_NOT_ALLOWED
  */
__STATIC_INLINE uint32_t md_spi_get_i2scfg_datlen(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->I2SCFG, SPI_I2SCFG_DATLEN_MSK)>>SPI_I2SCFG_DATLEN_POSS);
}

/**
  * @brief  Set Inactive state clock polarity
  * @note   Note: For correct operation, this bit should be configured when the I2S is disabled. It is not used \n
            in SPI mode. The bit CKPOL does not affect the CK edge sensitivity used to receive or transmit the SD \n
            and WS signals.
  * @param  SPIx SPI Instance
  * @param  value This bit can be set to:   
  *         @arg @ref MD_I2S_POLARITY_LOW
  *         @arg @ref MD_I2S_POLARITY_HIGH
  * @retval None
  */
__STATIC_INLINE void md_spi_set_i2scfg_ckpol(SPI_TypeDef *SPIx, uint32_t value)
{
  MODIFY_REG(SPIx->I2SCFG, SPI_I2SCFG_CKPOL_MSK, value);
}

/**
  * @brief  Get Inactive state clock polarity
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  * @retval Return follow :
  *         @arg @ref MD_I2S_POLARITY_LOW
  *         @arg @ref MD_I2S_POLARITY_HIGH
  */
__STATIC_INLINE uint32_t md_spi_get_i2scfg_ckpol(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->I2SCFG, SPI_I2SCFG_CKPOL_MSK)>>SPI_I2SCFG_CKPOL_POS);
}

/**
  * @brief  Set I2S standard selection
  * @param  SPIx SPI Instance
  * @param  value This bit can be set to:   
  *         @arg @ref MD_I2S_PHILIPS_STANDARD
  *         @arg @ref MD_I2S_MSB_STANDARD
  *         @arg @ref MD_I2S_LSB_STANDARD
  *         @arg @ref MD_I2S_PCM_STANDARD
  * @retval None
  */
__STATIC_INLINE void md_spi_set_i2scfg_i2sstd(SPI_TypeDef *SPIx, uint32_t value)
{
  MODIFY_REG(SPIx->I2SCFG, SPI_I2SCFG_I2SSTD_MSK, value);
}

/**
  * @brief  Get I2S standard selection
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  * @retval Return follow :
  *         @arg @ref MD_I2S_PHILIPS_STANDARD
  *         @arg @ref MD_I2S_MSB_STANDARD
  *         @arg @ref MD_I2S_LSB_STANDARD
  *         @arg @ref MD_I2S_PCM_STANDARD
  */
__STATIC_INLINE uint32_t md_spi_get_i2scfg_i2sstd(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->I2SCFG, SPI_I2SCFG_I2SSTD_MSK)>>SPI_I2SCFG_I2SSTD_POSS);
}

/**
  * @brief  Set PCM frame synchronization
  * @param  SPIx SPI Instance
  * @param  value This bit can be set to:   
  *         @arg @ref MD_I2S_FRAME_SYN_SHORT
  *         @arg @ref MD_I2S_FRAME_SYN_LONG
  * @retval None
  */
__STATIC_INLINE void md_spi_set_i2scfg_pcmsync(SPI_TypeDef *SPIx, uint32_t value)
{
  MODIFY_REG(SPIx->I2SCFG, SPI_I2SCFG_PCMSYNC_MSK, value);
}

/**
  * @brief  Get PCM frame synchronization
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  * @retval Return follow :
  *         @arg @ref MD_I2S_FRAME_SYN_SHORT
  *         @arg @ref MD_I2S_FRAME_SYN_LONG
  */
__STATIC_INLINE uint32_t md_spi_get_i2scfg_pcmsync(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->I2SCFG, SPI_I2SCFG_PCMSYNC_MSK)>>SPI_I2SCFG_PCMSYNC_POS);
}

/**
  * @brief  Set I2S configuration mode
  * @param  SPIx SPI Instance
  * @param  value This bit can be set to:   
  *         @arg @ref MD_I2S_SLAVE_TX
  *         @arg @ref MD_I2S_SLAVE_RX
  *         @arg @ref MD_I2S_MASTER_TX
  *         @arg @ref MD_I2S_MASTER_RX
  * @retval None
  */
__STATIC_INLINE void md_spi_set_i2scfg_i2scfg(SPI_TypeDef *SPIx, uint32_t value)
{
  MODIFY_REG(SPIx->I2SCFG, SPI_I2SCFG_I2SCFG_MSK, value);
}

/**
  * @brief  Get I2S configuration mode
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  * @retval Return follow :
  *         @arg @ref MD_I2S_SLAVE_TX
  *         @arg @ref MD_I2S_SLAVE_RX
  *         @arg @ref MD_I2S_MASTER_TX
  *         @arg @ref MD_I2S_MASTER_RX
  */
__STATIC_INLINE uint32_t md_spi_get_i2scfg_i2scfg(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->I2SCFG, SPI_I2SCFG_I2SCFG_MSK)>>SPI_I2SCFG_I2SCFG_POSS);
}

/**
  * @brief  Enable I2S enable
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_enable_i2scfg_i2se(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->I2SCFG, SPI_I2SCFG_I2SE_MSK);
}

/**
  * @brief  Disable I2S enable
  * @note   When disabling the I2S, follow the procedure described in the Reference Manual.
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_disable_i2scfg_i2se(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->I2SCFG, SPI_I2SCFG_I2SE_MSK);
}

/**
  * @brief  Check if I2S enable is enabled
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_enable_i2scfg_i2se(SPI_TypeDef *SPIx)
{
  return (READ_BIT(SPIx->I2SCFG, SPI_I2SCFG_I2SE_MSK) == (SPI_I2SCFG_I2SE_MSK));
}

/**
  * @brief  Set I2S mode selection
  * @param  SPIx SPI Instance
  * @param  value This bit can be set to:   
  *         @arg @ref MD_I2S_MODE_SPI
  *         @arg @ref MD_I2S_MODE_I2S
  * @retval None
  */
__STATIC_INLINE void md_spi_set_i2scfg_i2smod(SPI_TypeDef *SPIx, uint32_t value)
{
  MODIFY_REG(SPIx->I2SCFG, SPI_I2SCFG_I2SMOD_MSK, value);
}

/**
  * @brief  Get I2S mode selection
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  * @retval Return follow :
  *         @arg @ref MD_I2S_MODE_SPI
  *         @arg @ref MD_I2S_MODE_I2S
  */
__STATIC_INLINE uint32_t md_spi_get_i2scfg_i2smod(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->I2SCFG, SPI_I2SCFG_I2SMOD_MSK)>>SPI_I2SCFG_I2SMOD_POS);
}


/**
  * @} MD_SPI_I2SCFG
  */

/**@defgroup MD_SPI_I2SPR I2S Prescaler register
  * @{ 
  */



/**
  * @brief  Set SPI I2S configuration register(SPIx_I2SPR)
  * @param  SPIx SPI Instance 
  * @param  value The value write in SPIx_I2SPR
  * @retval None
  */
__STATIC_INLINE void md_spi_set_I2SPR(SPI_TypeDef *SPIx, uint32_t value)
{
  WRITE_REG(SPIx->I2SPR, value);
}

/**
  * @brief  Get SPI I2S configuration register (SPIx_I2SPR)
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_get_I2SPR(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_REG(SPIx->I2SPR));
}

/**
  * @brief  Set I2S linear prescaler
  * @note   I2SDIV [7:0] = 0 or I2SDIV [7:0] = 1 are forbidden values.  \n
            Note: These bits should be configured when the I2S is disabled. \n
            They are used only when the I2S is in master mode. They are not used in SPI mode.
  * @param  SPIx SPI Instance
  * @param  value This bit can be set to:   
  *         @arg Max:255
  *         @arg Min:2
  * @retval None
  */
__STATIC_INLINE void md_spi_set_i2spr_i2sdiv(SPI_TypeDef *SPIx, uint32_t value)
{
  MODIFY_REG(SPIx->I2SPR, SPI_I2SPR_I2SDIV_MSK, value);
}

/**
  * @brief  Get I2S linear prescaler
  * @note   0 or 1 are forbidden values
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  * @retval Return follow :
  *         @arg Max:255
  *         @arg Min:2
  */
__STATIC_INLINE uint32_t md_spi_get_i2spr_i2sdiv(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->I2SPR, SPI_I2SPR_I2SDIV_MSK)>>SPI_I2SPR_I2SDIV_POSS);
}

/**
  * @brief  Set Odd factor for the prescaler
  * @note   0 or 1 are forbidden values
  * @param  SPIx SPI Instance
  * @param  value This bit can be set to:   
  *         @arg MD_I2S_EVEN
  *         @arg MD_I2S_ODD
  * @retval None
  */
__STATIC_INLINE void md_spi_set_i2spr_odd(SPI_TypeDef *SPIx, uint32_t value)
{
  MODIFY_REG(SPIx->I2SPR, SPI_I2SPR_ODD_MSK, value);
}

/**
  * @brief  Get Odd factor for the prescaler
  * @note   0 or 1 are forbidden values
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  * @retval Return follow :
  *         @arg MD_I2S_EVEN
  *         @arg MD_I2S_ODD
  */
__STATIC_INLINE uint32_t md_spi_get_i2spr_odd(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->I2SPR, SPI_I2SPR_ODD_MSK)>>SPI_I2SPR_ODD_POS);
}

/**
  * @brief  Master clock output enable
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_enable_i2spr_mckoe(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->I2SPR, SPI_I2SPR_MCKOE_MSK);
}

/**
  * @brief  Master clock output disable
  * @note   When disabling the I2S, follow the procedure described in the Reference Manual.
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_disable_i2spr_mckoe(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->I2SCFG, SPI_I2SPR_MCKOE_MSK);
}

/**
  * @brief  Check if Master clock output enable is enabled
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_enable_i2spr_mckoe(SPI_TypeDef *SPIx)
{
  return (READ_BIT(SPIx->I2SPR, SPI_I2SPR_MCKOE_MSK) == (SPI_I2SPR_MCKOE_MSK));
}

/**
  * @brief  Set External I2S Clock Enable
  * @note   0 or 1 are forbidden values
  * @param  SPIx SPI Instance
  * @param  value This bit can be set to:   
  *         @arg MD_I2S_APB_CLOCK
  *         @arg MD_I2S_EXTERNAL_CLOCK
  * @retval None
  */
__STATIC_INLINE void md_spi_set_i2spr_extcken(SPI_TypeDef *SPIx, uint32_t value)
{
  MODIFY_REG(SPIx->I2SPR, SPI_I2SPR_EXTCKEN_MSK, value);
}

/**
  * @brief  Get External I2S Clock Enable
  * @note   0 or 1 are forbidden values
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  * @retval Return follow :
  *         @arg MD_I2S_APB_CLOCK
  *         @arg MD_I2S_EXTERNAL_CLOCK
  */
__STATIC_INLINE uint32_t md_spi_get_i2spr_extcken(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->I2SPR, SPI_I2SPR_EXTCKEN_MSK)>>SPI_I2SPR_EXTCKEN_POS);
}






/**
  * @} MD_SPI_I2SPR
  */



/**
  * @} MD_SPI_I2S
  */


/** @defgroup MD_SPI_PF_Interrupt_Management SPI Interrupt Management
  * @{
  */
  
/** @defgroup MD_SPI_IER SPI Interrupt Enable Register
  * @{
  */
  
  
/**
  * @brief  Frame format error interrupt enable
  * @note   This bit controls the generation of an interrupt when an error condition occurs (CRCERR, OVR, MODF in SPI mode, FRE at TI mode).
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_enable_ier_freie(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IER, SPI_IER_FREIE_MSK);
}

/**
  * @brief  Mode fault interrupt enable
  * @note   This bit controls the generation of an interrupt when an error condition occurs (CRCERR, OVR, MODF in SPI mode, FRE at TI mode).
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_enable_ier_modfie(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IER, SPI_IER_MODFIE_MSK);
}

/**
  * @brief  CRC error interrupt enable
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_enable_ier_crcerrie(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IER, SPI_IER_CRCERRIE_MSK);
}

/**
  * @brief  Receive buffer over threshold interrupt enable
  * @note   This bit controls the generation of an interrupt when an error condition occurs (CRCERR, OVR, MODF in SPI mode, FRE at TI mode).
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_enable_ier_rxthie(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IER, SPI_IER_RXTHIE_MSK);
}

/**
  * @brief  Transmit buffer over threshold interrupt enable
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_enable_ier_txthie(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IER, SPI_IER_TXTHIE_MSK);
}

/**
  * @brief  Receive buffer underrun interrupt enable
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_enable_ier_rxudie(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IER, SPI_IER_RXUDIE_MSK);
}

/**
  * @brief  Transmit buffer underrun interrupt enable
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_enable_ier_txudie(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IER, SPI_IER_TXUDIE_MSK);
}

/**
  * @brief  Receive buffer overrun interrupt enable
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_enable_ier_rxovie(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IER, SPI_IER_RXOVIE_MSK);
}

/**
  * @brief  Transmit buffer overrun interrupt enable
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_enable_ier_txovie(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IER, SPI_IER_TXOVIE_MSK);
}

/**
  * @brief  Receive buffer full interrupt enable
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_enable_ier_rxfie(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IER, SPI_IER_RXFIE_MSK);
}

/**
  * @brief Transmit buffer empty interrupt enable
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_enable_ier_txeie(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IER, SPI_IER_TXEIE_MSK);
}

/**
  * @} MD_SPI_IER
  */


/** @defgroup MD_SPI_IDR SPI Interrupt Disable Register
  * @{
  */

/**
  * @brief  Frame format error interrupt disable
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_disable_idr_freid(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IDR, SPI_IDR_FREID_MSK);
}

/**
  * @brief  Mode fault interrupt disable
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_disable_idr_modfid(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IDR, SPI_IDR_MODFID_MSK);
}

/**
  * @brief  CRC error interrupt disable
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_disable_idr_crcerrid(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IDR, SPI_IDR_CRCERRID_MSK);
}

/**
  * @brief  Receive buffer under threshold interrupt disable
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_disable_idr_rxthid(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IDR, SPI_IDR_RXTHID_MSK);
}

/**
  * @brief  Transmit buffer under threshold interrupt disable
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_disable_idr_txthid(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IDR, SPI_IDR_TXTHID_MSK);
}

/**
  * @brief  Receive buffer underrun interrupt disable
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_disable_idr_rxudid(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IDR, SPI_IDR_RXUDID_MSK);
}

/**
  * @brief  Transmit buffer underrun interrupt disable
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_disable_idr_txudid(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IDR, SPI_IDR_TXUDID_MSK);
}

/**
  * @brief  Receive buffer overrun interrupt disable
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_disable_idr_rxovid(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IDR, SPI_IDR_RXOVID_MSK);
}

/**
  * @brief  Transmit buffer overrun interrupt disable
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_disable_idr_txovid(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IDR, SPI_IDR_TXOVID_MSK);
}

/**
  * @brief  Receive buffer full interrupt disable
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_disable_idr_rxfid(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IDR, SPI_IDR_RXFID_MSK);
}

/**
  * @brief  Transmit buffer empty interrupt disable
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void md_spi_disable_idr_txeid(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IDR, SPI_IDR_TXEID_MSK);
}

/**
  * @} MD_SPI_IDR
  */

/** @defgroup MD_SPI_ICR SPI Interrupt Clear Status Register
  * @{
  */

/**
  * @brief  Frame format error interrupt clear
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_spi_clear_icr_freic(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->ICR, SPI_ICR_FREIC_MSK);
}

/**
  * @brief  Mode fault interrupt clear
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_spi_clear_icr_modfic(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->ICR, SPI_ICR_MODFIC_MSK);
}

/**
  * @brief  CRC error interrupt clear
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_spi_clear_icr_crcerric(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->ICR, SPI_ICR_CRCERRIC_MSK);
}

/**
  * @brief  Receive buffer over threshold interrupt clear
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_spi_clear_icr_rxthic(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->ICR, SPI_ICR_RXTHIC_MSK);
}

/**
  * @brief  Transmit buffer over threshold interrupt clear
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_spi_clear_icr_txthic(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->ICR, SPI_ICR_TXTHIC_MSK);
}

/**
  * @brief  Receive buffer underrun interrupt clear
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_spi_clear_icr_rxudic(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->ICR, SPI_ICR_RXUDIC_MSK);
}

/**
  * @brief  Transmit buffer underrun interrupt clear
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_spi_clear_icr_txudic(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->ICR, SPI_ICR_TXUDIC_MSK);
}

/**
  * @brief  Receive buffer overrun interrupt clear
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_spi_clear_icr_rxovic(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->ICR, SPI_ICR_RXOVIC_MSK);
}

/**
  * @brief  Transmit buffer overrun interrupt clear
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_spi_clear_icr_txovic(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->ICR, SPI_ICR_TXOVIC_MSK);
}

/**
  * @brief  Receive buffer full interrupt clear
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_spi_clear_icr_rxfic(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->ICR, SPI_ICR_RXFIC_MSK);
}

/**
  * @brief  Transmit buffer empty interrupt clear
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_spi_clear_icr_txeic(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->ICR, SPI_ICR_TXEIC_MSK);
}

/**
  * @} MD_SPI_ICR
  */

/** @defgroup MD_SPI_IVS SPI Interrupt Valid Status Register
  * @{
  */


/**
  * @brief  Check if Frame format error interrupt valid is enabled
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_enabled_ivs_freiv(SPI_TypeDef *SPIx)
{
  return (READ_BIT(SPIx->IVS, SPI_IVS_FREIV_MSK) == (SPI_IVS_FREIV_MSK));
}

/**
  * @brief  Check if Mode fault interrupt valid is enabled
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_enabled_ivs_modfiv(SPI_TypeDef *SPIx)
{
  return (READ_BIT(SPIx->IVS, SPI_IVS_MODFIV_MSK) == (SPI_IVS_MODFIV_MSK));
}

/**
  * @brief  Check if CRC error interrupt valid is enabled
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_enabled_ivs_crcerriv(SPI_TypeDef *SPIx)
{
  return (READ_BIT(SPIx->IVS, SPI_IVS_CRCERRIV_MSK) == (SPI_IVS_CRCERRIV_MSK));
}

/**
  * @brief  Check if Receive buffer under threshold interrupt valid is enabled
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_enabled_ivs_rxthiv(SPI_TypeDef *SPIx)
{
  return (READ_BIT(SPIx->IVS, SPI_IVS_RXTHIV_MSK) == (SPI_IVS_RXTHIV_MSK));
}

/**
  * @brief  Check if Transmit buffer under threshold interrupt valid is enabled
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_enabled_it_txthiv(SPI_TypeDef *SPIx)
{
  return (READ_BIT(SPIx->IVS, SPI_IVS_TXTHIV_MSK) == (SPI_IVS_TXTHIV_MSK));
}

/**
  * @brief  Check if Receive buffer under underrun interrupt valid is enabled
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_enabled_ivs_rxudiv(SPI_TypeDef *SPIx)
{
  return (READ_BIT(SPIx->IVS, SPI_IVS_RXUDIV_MSK) == (SPI_IVS_RXUDIV_MSK));
}

/**
  * @brief  Check if Transmit buffer underrun interrupt valid is enabled
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_enabled_it_txudiv(SPI_TypeDef *SPIx)
{
  return (READ_BIT(SPIx->IVS, SPI_IVS_TXUDIV_MSK) == (SPI_IVS_TXUDIV_MSK));
}

/**
  * @brief  Check if Receive buffer overrun interrupt valid is enabled
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_enabled_ivs_rxoviv(SPI_TypeDef *SPIx)
{
  return (READ_BIT(SPIx->IVS, SPI_IVS_RXOVIV_MSK) == (SPI_IVS_RXOVIV_MSK));
}

/**
  * @brief  Check if Transmit buffer overrun interrupt valid is enabled
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_enabled_ivs_txoviv(SPI_TypeDef *SPIx)
{
  return (READ_BIT(SPIx->IVS, SPI_IVS_TXOVIV_MSK) == (SPI_IVS_TXOVIV_MSK));
}

/**
  * @brief  Check if Receive buffer full interrupt valid is enabled
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_enabled_ivs_rxfiv(SPI_TypeDef *SPIx)
{
  return (READ_BIT(SPIx->IVS, SPI_IVS_RXFIV_MSK) == (SPI_IVS_RXFIV_MSK));
}

/**
  * @brief  Check if Transmit buffer empty interrupt valid is enabled
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_enabled_ivs_txeiv(SPI_TypeDef *SPIx)
{
  return (READ_BIT(SPIx->IVS, SPI_IVS_TXEIV_MSK) == (SPI_IVS_TXEIV_MSK));
}


/**
  * @} MD_SPI_IVS
  */


/** @defgroup MD_SPI_RIF SPI Raw Interrupt Flag Status Register
  * @{
  */

/**
  * @brief  Check if Transmit buffer empty interrupt flag status is actived
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_rif_txeri(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->RIF, SPI_RIF_TXERI_MSK)==(SPI_RIF_TXERI_MSK));
}

/**
  * @brief  Check if Transmit buffer overrun interrupt flag status is actived
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_rif_txovri(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->RIF, SPI_RIF_TXOVRI_MSK)==(SPI_RIF_TXOVRI_MSK));
}

/**
  * @brief  Check if Transmit buffer underrun interrupt flag status is actived
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_rif_txudri(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->RIF, SPI_RIF_TXUDRI_MSK)==(SPI_RIF_TXUDRI_MSK));
}

/**
  * @brief  Check if Transmit buffer under threshold interrupt flag status is actived
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_rif_txthri(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->RIF, SPI_RIF_TXTHRI_MSK)==(SPI_RIF_TXTHRI_MSK));
}

/**
  * @brief  Check if Receive buffer full interrupt flag status is actived
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_rif_rxfri(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->RIF, SPI_RIF_RXFRI_MSK)==(SPI_RIF_RXFRI_MSK));
}

/**
  * @brief  Check if Receive buffer overrun interrupt flag status is actived
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_rif_rxovri(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->RIF, SPI_RIF_RXOVRI_MSK)==(SPI_RIF_RXOVRI_MSK));
}

/**
  * @brief  Check if Receive buffer underrun interrupt flag status is actived
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_rif_rxudri(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->RIF, SPI_RIF_RXUDRI_MSK)==(SPI_RIF_RXUDRI_MSK));
}

/**
  * @brief  Check if Receive buffer over threshold interrupt flag status is actived
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_rif_rxthri(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->RIF, SPI_RIF_RXTHRI_MSK)==(SPI_RIF_RXTHRI_MSK));
}

/**
  * @brief  Check if CRC error interrupt flag status is actived
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_rif_crcerrri(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->RIF, SPI_RIF_CRCERRRI_MSK)==(SPI_RIF_CRCERRRI_MSK));
}

/**
  * @brief  Check if Mode fault interrupt flag status is actived
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_rif_modfri(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->RIF, SPI_RIF_MODFRI_MSK)==(SPI_RIF_MODFRI_MSK));
}

/**
  * @brief  Check if Frame format error interrupt flag status is actived
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_rif_freri(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->RIF, SPI_RIF_FRERI_MSK)==(SPI_RIF_FRERI_MSK));
}

/**
  * @} MD_SPI_RIF
  */

/** @defgroup MD_SPI_IFM SPI Interrupt Masked Flag Status Register
  * @{
  */

/**
  * @brief  Check if Transmit buffer empty interrupt flag status is actived
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_ifm_txefm(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->IFM, SPI_IFM_TXEFM_MSK)==(SPI_IFM_TXEFM_MSK));
}

/**
  * @brief  Check if Transmit buffer overrun interrupt flag status is actived
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_ifm_txovfm(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->IFM, SPI_IFM_TXOVFM_MSK)==(SPI_IFM_TXOVFM_MSK));
}

/**
  * @brief  Check if Transmit buffer underrun interrupt flag status is actived
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_ifm_txudfm(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->IFM, SPI_IFM_TXUDFM_MSK)==(SPI_IFM_TXUDFM_MSK));
}

/**
  * @brief  Check if Transmit buffer under threshold interrupt flag status is actived
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_ifm_txthfm(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->IFM, SPI_IFM_TXTHFM_MSK)==(SPI_IFM_TXTHFM_MSK));
}

/**
  * @brief  Check if Receive buffer full interrupt flag status is actived
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_ifm_rxffm(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->IFM, SPI_IFM_RXFFM_MSK)==(SPI_IFM_RXFFM_MSK));
}

/**
  * @brief  Check if Receive buffer overrun interrupt flag status is actived
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_ifm_rxovfm(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->IFM, SPI_IFM_RXOVFM_MSK)==(SPI_IFM_RXOVFM_MSK));
}

/**
  * @brief  Check if Receive buffer underrun interrupt flag status is actived
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_ifm_rxudfm(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->IFM, SPI_IFM_RXUDFM_MSK)==(SPI_IFM_RXUDFM_MSK));
}

/**
  * @brief  Check if Receive buffer over threshold interrupt flag status is actived
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_ifm_rxthfm(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->IFM, SPI_IFM_RXTHFM_MSK)==(SPI_IFM_RXTHFM_MSK));
}

/**
  * @brief  Check if CRC error interrupt flag status is actived
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_ifm_crcerrfm(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->IFM, SPI_IFM_CRCERRFM_MSK)==(SPI_IFM_CRCERRFM_MSK));
}

/**
  * @brief  Check if Mode fault interrupt flag status is actived
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_ifm_modffm(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->IFM, SPI_IFM_MODFFM_MSK)==(SPI_IFM_MODFFM_MSK));
}

/**
  * @brief  Check if Frame format error interrupt flag status is actived
  * @param  SPIx SPI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_ifm_frefm(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->IFM, SPI_IFM_FREFM_MSK)==(SPI_IFM_FREFM_MSK));
}

/**
  * @} MD_SPI_IFM
  */



/**
  * @} MD_SPI_PF_Interrupt_Management
  */



/**
  * @} MD_SPI_Public_Macros
  */

/* Public functions -----------------------------------------------------------*/
/** @defgroup MD_SPI_Public_Functions SPI Public Functions
  * @{
  */




/** @defgroup MD_SPI_PF_Init SPI Initialization and De-Initialization functions
  * @{
  */

ErrorStatus md_spi_init(SPI_TypeDef *SPIx, md_spi_inittypedef *SPI_InitStruct);
void md_spi_struct_init(md_spi_inittypedef *SPI_InitStruct);
void SPISingleWr(SPI_TypeDef *SPIx, uint8_t data);
uint8_t SPISSingleRd(SPI_TypeDef *SPIx);
/**
  * @} MD_SPI_PF_Init
  */

/**
  * @} MD_SPI_Public_Functions
  */

/**
  * @} SPI
  */

#endif

/**
  * @} Micro_Driver
  */

#ifdef __cplusplus
}
#endif

#endif

/******************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
