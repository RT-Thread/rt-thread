/**
******************************************************************************
* @file    HAL_spi.h
* @author  AE Team
* @version V1.0.0
* @date    28/05/2015
* @brief   This file contains all the functions prototypes for the SPI firmware 
*          library.
******************************************************************************
* @copy
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, MindMotion SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <h2><center>&copy; COPYRIGHT 2015 MindMotion</center></h2>
*/ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_SPI_H
#define __HAL_SPI_H

/* Includes ------------------------------------------------------------------*/
#include "HAL_device.h"

/** @addtogroup StdPeriph_Driver
* @{
*/

/** @addtogroup SPI
* @{
*/ 

/** @defgroup SPI_Exported_Types
* @{
*/

/** 
* @brief  SPI Init structure definition  
*/

typedef struct
{
  uint16_t SPI_Mode;
  uint16_t SPI_DataSize;
  uint16_t SPI_DataWidth;
  uint16_t SPI_CPOL;
  uint16_t SPI_CPHA;
  uint16_t SPI_NSS;
  uint16_t SPI_BaudRatePrescaler;
  uint16_t SPI_FirstBit; 
}SPI_InitTypeDef;


/**
* @}
*/

/** @defgroup SPI_Exported_Constants
* @{
*/

#define IS_SPI_ALL_PERIPH(PERIPH) (((*(uint32_t*)&(PERIPH)) == SPI0_BASE) || \
((*(uint32_t*)&(PERIPH)) == SPI1_BASE))

#define IS_SPI_2_PERIPH(PERIPH) ((*(uint32_t*)&(PERIPH)) == SPI1_BASE)


/**
* @}
*/

/** @defgroup SPI_master_slave_mode 
* @{
*/

#define SPI_Mode_Master                 ((uint16_t)0x0004)
#define SPI_Mode_Slave                  ((uint16_t)0x0000)
#define IS_SPI_MODE(MODE) (((MODE) == SPI_Mode_Master) || \
((MODE) == SPI_Mode_Slave))
/**
* @}
*/

/** @defgroup SPI_data_size 
* @{
*/

#define SPI_DataSize_32b                ((uint16_t)0x0800)
#define SPI_DataSize_8b                 ((uint16_t)0x0000)
#define IS_SPI_DATASIZE(DATASIZE) (((DATASIZE) == SPI_DataSize_32b) || \
((DATASIZE) == SPI_DataSize_8b))

/**
* @}
*/


/** @defgroup SPI_7bit_8bit data width 
* @{
*/

#define SPI_DataWidth_1b                  ((uint16_t)0x0001)
#define SPI_DataWidth_2b                  ((uint16_t)0x0002)
#define SPI_DataWidth_3b                  ((uint16_t)0x0003)
#define SPI_DataWidth_4b                  ((uint16_t)0x0004)
#define SPI_DataWidth_5b                  ((uint16_t)0x0005)
#define SPI_DataWidth_6b                  ((uint16_t)0x0006)
#define SPI_DataWidth_7b                  ((uint16_t)0x0007)
#define SPI_DataWidth_8b                  ((uint16_t)0x0008)
#define SPI_DataWidth_9b                  ((uint16_t)0x0009)
#define SPI_DataWidth_10b                 ((uint16_t)0x000a)
#define SPI_DataWidth_11b                 ((uint16_t)0x000b)
#define SPI_DataWidth_12b                 ((uint16_t)0x000c)
#define SPI_DataWidth_13b                 ((uint16_t)0x000d)
#define SPI_DataWidth_14b                 ((uint16_t)0x000e)
#define SPI_DataWidth_15b                 ((uint16_t)0x000f)
#define SPI_DataWidth_16b                 ((uint16_t)0x0010)
#define SPI_DataWidth_17b                 ((uint16_t)0x0011)
#define SPI_DataWidth_18b                 ((uint16_t)0x0012)
#define SPI_DataWidth_19b                 ((uint16_t)0x0013)
#define SPI_DataWidth_20b                 ((uint16_t)0x0014)
#define SPI_DataWidth_21b                 ((uint16_t)0x0015)
#define SPI_DataWidth_22b                 ((uint16_t)0x0016)
#define SPI_DataWidth_23b                 ((uint16_t)0x0017)
#define SPI_DataWidth_24b                 ((uint16_t)0x0018)
#define SPI_DataWidth_25b                 ((uint16_t)0x0019)
#define SPI_DataWidth_26b                 ((uint16_t)0x001a)
#define SPI_DataWidth_27b                 ((uint16_t)0x001b)
#define SPI_DataWidth_28b                 ((uint16_t)0x001c)
#define SPI_DataWidth_29b                 ((uint16_t)0x001d)
#define SPI_DataWidth_30b                 ((uint16_t)0x001e)
#define SPI_DataWidth_31b                 ((uint16_t)0x001f)
#define SPI_DataWidth_32b                 ((uint16_t)0x0000)
#define IS_SPI_DATAWIDRH(WIDTH) (((WIDTH) == SPI_DataWidth_1b) || ((WIDTH) == SPI_DataWidth_2b)||\
((WIDTH) == SPI_DataWidth_3b)||((WIDTH) == SPI_DataWidth_4b)||\
  ((WIDTH) == SPI_DataWidth_5b)||((WIDTH) == SPI_DataWidth_6b)||\
    ((WIDTH) == SPI_DataWidth_7b)||((WIDTH) == SPI_DataWidth_8b)||\
      ((WIDTH) == SPI_DataWidth_9b)||((WIDTH) == SPI_DataWidth_10b)||\
        ((WIDTH) == SPI_DataWidth_11b)||((WIDTH) == SPI_DataWidth_12b)||\
          ((WIDTH) == SPI_DataWidth_13b)||((WIDTH) == SPI_DataWidth_14b)||\
            ((WIDTH) == SPI_DataWidth_15b)||((WIDTH) == SPI_DataWidth_16b)||\
              ((WIDTH) == SPI_DataWidth_17b)||((WIDTH) == SPI_DataWidth_18b)||\
                ((WIDTH) == SPI_DataWidth_19b)||((WIDTH) == SPI_DataWidth_20b)||\
                  ((WIDTH) == SPI_DataWidth_21b)||((WIDTH) == SPI_DataWidth_22b)||\
                    ((WIDTH) == SPI_DataWidth_23b)||((WIDTH) == SPI_DataWidth_24b)||\
                      ((WIDTH) == SPI_DataWidth_25b)||((WIDTH) == SPI_DataWidth_26b)||\
                        ((WIDTH) == SPI_DataWidth_27b)||((WIDTH) == SPI_DataWidth_28b)||\
                          ((WIDTH) == SPI_DataWidth_29b)||((WIDTH) == SPI_DataWidth_30b)||\
                            ((WIDTH) == SPI_DataWidth_31b)||((WIDTH) == SPI_DataWidth_32b)||)
/**
* @}
*/


/** @defgroup SPI_Clock_Polarity 
* @{
*/

#define SPI_CPOL_Low                    ((uint16_t)0x0000)
#define SPI_CPOL_High                   ((uint16_t)0x0002)
#define IS_SPI_CPOL(CPOL) (((CPOL) == SPI_CPOL_Low) || \
((CPOL) == SPI_CPOL_High))
/**
* @}
*/

/** @defgroup SPI_Clock_Phase 
* @{
*/

#define SPI_CPHA_1Edge                  ((uint16_t)0x0001)
#define SPI_CPHA_2Edge                  ((uint16_t)0x0000)
#define IS_SPI_CPHA(CPHA) (((CPHA) == SPI_CPHA_1Edge) || \
((CPHA) == SPI_CPHA_2Edge))
/**
* @}
*/

/** @defgroup SPI_Slave_Select_management 
* @{
*/

#define SPI_NSS_Soft                    ((uint16_t)0x0000)
#define SPI_NSS_Hard                    ((uint16_t)0x0400)
#define IS_SPI_NSS(NSS) (((NSS) == SPI_NSS_Soft) || \
((NSS) == SPI_NSS_Hard))


/**
* @}
*/

/** @defgroup SPI_NSS_internal_software_mangement 
* @{
*/

#define SPI_NSSInternalSoft_Set         ((uint16_t)0x0001)
#define SPI_NSSInternalSoft_Reset       ((uint16_t)0xFFFE)
#define IS_SPI_NSS_INTERNAL(INTERNAL) (((INTERNAL) == SPI_NSSInternalSoft_Set) || \
((INTERNAL) == SPI_NSSInternalSoft_Reset))
/**
* @}
*/

/**
* @}
*/ 

/** @defgroup SPI_BaudRate_Prescaler_ 
* @{
*/


#define SPI_BaudRatePrescaler_2         ((uint16_t)0x0002)
#define SPI_BaudRatePrescaler_4         ((uint16_t)0x0004)
#define SPI_BaudRatePrescaler_8         ((uint16_t)0x0008)
#define SPI_BaudRatePrescaler_16        ((uint16_t)0x0010)
#define SPI_BaudRatePrescaler_32        ((uint16_t)0x0020)
#define SPI_BaudRatePrescaler_64        ((uint16_t)0x0040)
#define SPI_BaudRatePrescaler_128       ((uint16_t)0x0080)
#define SPI_BaudRatePrescaler_256       ((uint16_t)0x0100)
#define IS_SPI_BAUDRATE_PRESCALER(PRESCALER) (((PRESCALER) == SPI_BaudRatePrescaler_2) || \
((PRESCALER) == SPI_BaudRatePrescaler_4) || \
  ((PRESCALER) == SPI_BaudRatePrescaler_8) || \
    ((PRESCALER) == SPI_BaudRatePrescaler_16) || \
      ((PRESCALER) == SPI_BaudRatePrescaler_32) || \
        ((PRESCALER) == SPI_BaudRatePrescaler_64) || \
          ((PRESCALER) == SPI_BaudRatePrescaler_128) || \
            ((PRESCALER) == SPI_BaudRatePrescaler_256))
/**
* @}
*/ 

/** @defgroup SPI_MSB_LSB_transmission 
* @{
*/

#define SPI_FirstBit_MSB                ((uint16_t)0x0000)
#define SPI_FirstBit_LSB                ((uint16_t)0x0004)
#define IS_SPI_FIRST_BIT(BIT) (((BIT) == SPI_FirstBit_MSB) || \
((BIT) == SPI_FirstBit_LSB))


/**
* @}
*/

/** @defgroup SPI_DMA_transfer_requests 
* @{
*/

#define SPI_DMAReq_EN               		((uint16_t)0x0200)
#define IS_SPI_DMAREQ(DMAREQ) ((DMAREQ)  == SPI_DMAReq_EN)


/**
* @}
*/

/** @defgroup SPI TX Fifo and RX Fifo trigger level 
* @{
*/
#define SPI_TXTLF               		    ((uint16_t)0x0080)
#define SPI_RXTLF               		    ((uint16_t)0x0020)
#define IS_SPI_FIFOTRIGGER(TRIGGER) (((TRIGGER)  == SPI_TXTLF) && ((TRIGGER) == SPI_RXTLF))







/**
* @}
*/

/** @defgroup SPI_NSS_internal_software_mangement 
* @{
*/

#define SPI_CS_BIT0                   ((uint16_t)0xfffe)
#define SPI_CS_BIT1                   ((uint16_t)0xfffd)
#define SPI_CS_BIT2                   ((uint16_t)0xfffb)
#define SPI_CS_BIT3                   ((uint16_t)0xfff7)
#define SPI_CS_BIT4                   ((uint16_t)0xffef)
#define SPI_CS_BIT5                   ((uint16_t)0xffdf)
#define SPI_CS_BIT6                   ((uint16_t)0xffbf)
#define SPI_CS_BIT7                   ((uint16_t)0xff7f)
#define IS_SPI_CS(CS)        (((CS) == SPI_CS_BIT0) || ((CS) == SPI_CS_BIT1)||\
((CS) == SPI_CS_BIT2) || ((CS) == SPI_CS_BIT3)||\
  ((CS) == SPI_CS_BIT4) || ((CS) == SPI_CS_BIT5)||\
    ((CS) == SPI_CS_BIT6) || ((CS) == SPI_CS_BIT7))
/**
* @}
*/


/** @defgroup SPI_direction_transmit_receive 
* @{
*/

#define SPI_Direction_Rx                ((uint16_t)0x0010)
#define SPI_Direction_Tx                ((uint16_t)0x0008)
#define SPI_Disable_Tx                	((uint16_t)0xfff7)
#define SPI_Disable_Rx                	((uint16_t)0xffef)
#define IS_SPI_DIRECTION(DIRECTION) (((DIRECTION) == SPI_Direction_Rx) || \
((DIRECTION) == SPI_Direction_Tx) || \
  ((DIRECTION) == SPI_Disable_Tx) || \
    ((DIRECTION) == SPI_Disable_Rx))
/**
* @}
*/

/** @defgroup SPI_interrupts_definition 
* @{
*/
#define SPI_INT_EN                    ((uint16_t)0x0002)

#define SPI_IT_TX                     ((uint8_t)0x01)
#define SPI_IT_RX                     ((uint8_t)0x02)

#define IS_SPI_CONFIG_IT(IT) (((IT) == SPI_IT_TX) || \
((IT) == SPI_IT_RX))

#define SPI_IT_UNDERRUN                ((uint8_t)0x04)
#define SPI_IT_RXOVER                  ((uint8_t)0x08)
#define SPI_IT_RXMATCH                 ((uint8_t)0x10)
#define SPI_IT_RXFULL                  ((uint8_t)0x20)
#define SPI_IT_TXEPT                   ((uint8_t)0x40)

#define IS_SPI_GET_IT(IT) (((IT) == SPI_IT_TX) || ((IT) == SPI_IT_RX) || \
((IT) == SPI_IT_UNDERRUN) || ((IT) == SPI_IT_RXOVER) || \
  ((IT) == SPI_IT_RXMATCH) || ((IT) == SPI_IT_RXFULL) || \
    ((IT) == SPI_IT_TXEPT))
/**
* @}
*/

/** @defgroup SPI_flags_definition 
* @{
*/


#define SPI_FLAG_RXAVL                ((uint16_t)0x0002)
#define SPI_FLAG_TXEPT                ((uint16_t)0x0001)

#define IS_SPI_GET_FLAG(FLAG) (((FLAG) == SPI_FLAG_RXAVL) || \
((FLAG) == SPI_FLAG_TXEPT))

/**
* @}
*/

/** @defgroup SPI mode tx data transmit phase adjust set 
*in slave mode according to txedge bit of CCTL register
* @{
*/


#define SPI_SlaveAdjust_FAST          ((uint16_t)0x0020)
#define SPI_SlaveAdjust_LOW           ((uint16_t)0xffdf)

#define IS_SPI_SlaveAdjust(ADJUST) (((ADJUST) == SPI_SlaveAdjust_FAST) || \
((ADJUST) == SPI_SlaveAdjust_LOW))


/**
* @}
*/

/** @defgroup SPI_Exported_Macros
* @{
*/

/**
* @}
*/

/** @defgroup SPI_Exported_Functions
* @{
*/

void SPI_DeInit(SPI_TypeDef* SPIx);
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct);
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct);
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void SPI_ITConfig(SPI_TypeDef* SPIx, uint8_t SPI_IT, FunctionalState NewState);
void SPI_DMACmd(SPI_TypeDef* SPIx, uint16_t SPI_DMAReq, FunctionalState NewState);
void SPI_FifoTrigger(SPI_TypeDef* SPIx, uint16_t SPI_FifoTriggerValue, FunctionalState NewState);
void SPI_SendData(SPI_TypeDef* SPIx, uint32_t Data);
uint32_t SPI_ReceiveData(SPI_TypeDef* SPIx);
void SPI_CSInternalSelected(SPI_TypeDef* SPIx, uint16_t SPI_CSInternalSelected,FunctionalState NewState);
void SPI_NSSInternalSoftwareConfig(SPI_TypeDef* SPIx, uint16_t SPI_NSSInternalSoft);
void SPI_DataSizeConfig(SPI_TypeDef* SPIx, uint16_t SPI_DataSize);
void SPI_BiDirectionalLineConfig(SPI_TypeDef* SPIx, uint16_t SPI_Direction);
FlagStatus SPI_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_FLAG);
ITStatus SPI_GetITStatus(SPI_TypeDef* SPIx, uint8_t SPI_IT);
void SPI_ClearITPendingBit(SPI_TypeDef* SPIx, uint8_t SPI_IT);
void SPI_RxBytes(SPI_TypeDef* SPIx, uint16_t Number);
void SPI_SlaveAdjust(SPI_TypeDef* SPIx, uint16_t AdjustValue);
#endif /*__HAL_SPI_H */
/**
* @}
*/

/**
* @}
*/

/**
* @}
*/

/*-------------------------(C) COPYRIGHT 2015 MindMotion ----------------------*/
