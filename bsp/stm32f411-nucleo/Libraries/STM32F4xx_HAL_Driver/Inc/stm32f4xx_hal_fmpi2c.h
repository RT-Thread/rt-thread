/**
  ******************************************************************************
  * @file    stm32f4xx_hal_fmpi2c.h
  * @author  MCD Application Team
  * @version V1.4.3
  * @date    11-December-2015
  * @brief   Header file of FMPI2C HAL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
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
  *
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F4xx_HAL_FMPI2C_H
#define __STM32F4xx_HAL_FMPI2C_H

#ifdef __cplusplus
 extern "C" {
#endif

#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) || defined(STM32F446xx)  
   
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal_def.h"  

/** @addtogroup STM32F4xx_HAL_Driver
  * @{
  */

/** @addtogroup FMPI2C
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/ 
/** @defgroup FMPI2C_Exported_Types FMPI2C Exported Types
  * @{
  */
   
/** 
  * @brief  FMPI2C Configuration Structure definition  
  */
typedef struct
{
  uint32_t Timing;              /*!< Specifies the FMPI2C_TIMINGR_register value.
                                  This parameter calculated by referring to FMPI2C initialization 
                                         section in Reference manual */

  uint32_t OwnAddress1;         /*!< Specifies the first device own address.
                                  This parameter can be a 7-bit or 10-bit address. */

  uint32_t AddressingMode;      /*!< Specifies if 7-bit or 10-bit addressing mode is selected.
                                  This parameter can be a value of @ref FMPI2C_addressing_mode */

  uint32_t DualAddressMode;     /*!< Specifies if dual addressing mode is selected.
                                  This parameter can be a value of @ref FMPI2C_dual_addressing_mode */

  uint32_t OwnAddress2;         /*!< Specifies the second device own address if dual addressing mode is selected
                                  This parameter can be a 7-bit address. */

  uint32_t OwnAddress2Masks;    /*!< Specifies the acknoledge mask address second device own address if dual addressing mode is selected
                                  This parameter can be a value of @ref FMPI2C_own_address2_masks */

  uint32_t GeneralCallMode;     /*!< Specifies if general call mode is selected.
                                  This parameter can be a value of @ref FMPI2C_general_call_addressing_mode */

  uint32_t NoStretchMode;       /*!< Specifies if nostretch mode is selected.
                                  This parameter can be a value of @ref FMPI2C_nostretch_mode */

}FMPI2C_InitTypeDef;

/** 
  * @brief  HAL State structures definition  
  */ 
typedef enum
{
  HAL_FMPI2C_STATE_RESET           = 0x00,  /*!< FMPI2C not yet initialized or disabled         */
  HAL_FMPI2C_STATE_READY           = 0x01,  /*!< FMPI2C initialized and ready for use           */
  HAL_FMPI2C_STATE_BUSY            = 0x02,  /*!< FMPI2C internal process is ongoing             */
  HAL_FMPI2C_STATE_MASTER_BUSY_TX  = 0x12,  /*!< Master Data Transmission process is ongoing */
  HAL_FMPI2C_STATE_MASTER_BUSY_RX  = 0x22,  /*!< Master Data Reception process is ongoing    */
  HAL_FMPI2C_STATE_SLAVE_BUSY_TX   = 0x32,  /*!< Slave Data Transmission process is ongoing  */
  HAL_FMPI2C_STATE_SLAVE_BUSY_RX   = 0x42,  /*!< Slave Data Reception process is ongoing     */
  HAL_FMPI2C_STATE_MEM_BUSY_TX     = 0x52,  /*!< Memory Data Transmission process is ongoing */
  HAL_FMPI2C_STATE_MEM_BUSY_RX     = 0x62,  /*!< Memory Data Reception process is ongoing    */
  HAL_FMPI2C_STATE_TIMEOUT         = 0x03,  /*!< Timeout state                               */
  HAL_FMPI2C_STATE_ERROR           = 0x04   /*!< Reception process is ongoing                */
}HAL_FMPI2C_StateTypeDef;

/** 
  * @brief  HAL FMPI2C Error Code structure definition  
  */ 
typedef enum
{
  HAL_FMPI2C_ERROR_NONE      = 0x00,    /*!< No error              */
  HAL_FMPI2C_ERROR_BERR      = 0x01,    /*!< BERR error            */
  HAL_FMPI2C_ERROR_ARLO      = 0x02,    /*!< ARLO error            */
  HAL_FMPI2C_ERROR_AF        = 0x04,    /*!< ACKF error            */
  HAL_FMPI2C_ERROR_OVR       = 0x08,    /*!< OVR error             */
  HAL_FMPI2C_ERROR_DMA       = 0x10,    /*!< DMA transfer error    */
  HAL_FMPI2C_ERROR_TIMEOUT   = 0x20,    /*!< Timeout error         */
  HAL_FMPI2C_ERROR_SIZE      = 0x40     /*!< Size Management error */
}HAL_FMPI2C_ErrorTypeDef;

/** 
  * @brief  FMPI2C handle Structure definition  
  */
typedef struct
{
  FMPI2C_TypeDef                *Instance;  /*!< FMPI2C registers base address     */

  FMPI2C_InitTypeDef            Init;       /*!< FMPI2C communication parameters   */

  uint8_t                    *pBuffPtr;  /*!< Pointer to FMPI2C transfer buffer */

  uint16_t                   XferSize;   /*!< FMPI2C transfer size              */

  __IO uint16_t              XferCount;  /*!< FMPI2C transfer counter           */

  DMA_HandleTypeDef          *hdmatx;    /*!< FMPI2C Tx DMA handle parameters   */

  DMA_HandleTypeDef          *hdmarx;    /*!< FMPI2C Rx DMA handle parameters   */

  HAL_LockTypeDef            Lock;       /*!< FMPI2C locking object             */

  __IO HAL_FMPI2C_StateTypeDef  State;      /*!< FMPI2C communication state        */

  __IO HAL_FMPI2C_ErrorTypeDef  ErrorCode;  /* FMPI2C Error code                   */

}FMPI2C_HandleTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup FMPI2C_Exported_Constants FMPI2C Exported Constants
  * @{
  */

/** @defgroup FMPI2C_addressing_mode FMPI2C addressing mode
  * @{
  */
#define FMPI2C_ADDRESSINGMODE_7BIT          ((uint32_t)0x00000001)
#define FMPI2C_ADDRESSINGMODE_10BIT         ((uint32_t)0x00000002)

/**
  * @}
  */

/** @defgroup FMPI2C_dual_addressing_mode FMPI2C dual addressing mode
  * @{
  */

#define FMPI2C_DUALADDRESS_DISABLE        ((uint32_t)0x00000000)
#define FMPI2C_DUALADDRESS_ENABLE         FMPI2C_OAR2_OA2EN

/**
  * @}
  */

/** @defgroup FMPI2C_own_address2_masks FMPI2C own address2 masks
  * @{
  */

#define FMPI2C_OA2_NOMASK                  ((uint8_t)0x00)
#define FMPI2C_OA2_MASK01                  ((uint8_t)0x01)
#define FMPI2C_OA2_MASK02                  ((uint8_t)0x02)
#define FMPI2C_OA2_MASK03                  ((uint8_t)0x03)
#define FMPI2C_OA2_MASK04                  ((uint8_t)0x04)
#define FMPI2C_OA2_MASK05                  ((uint8_t)0x05)
#define FMPI2C_OA2_MASK06                  ((uint8_t)0x06)
#define FMPI2C_OA2_MASK07                  ((uint8_t)0x07)
 
/**
  * @}
  */

/** @defgroup FMPI2C_general_call_addressing_mode FMPI2C general call addressing mode
  * @{
  */
#define FMPI2C_GENERALCALL_DISABLE        ((uint32_t)0x00000000)
#define FMPI2C_GENERALCALL_ENABLE         FMPI2C_CR1_GCEN

/**
  * @}
  */

/** @defgroup FMPI2C_nostretch_mode FMPI2C nostretch mode
  * @{
  */
#define FMPI2C_NOSTRETCH_DISABLE          ((uint32_t)0x00000000)
#define FMPI2C_NOSTRETCH_ENABLE           FMPI2C_CR1_NOSTRETCH

/**
  * @}
  */

/** @defgroup FMPI2C_Memory_Address_Size FMPI2C Memory Address Size
  * @{
  */
#define FMPI2C_MEMADD_SIZE_8BIT            ((uint32_t)0x00000001)
#define FMPI2C_MEMADD_SIZE_16BIT           ((uint32_t)0x00000002)

/**
  * @}
  */  
  
/** @defgroup FMPI2C_ReloadEndMode_definition FMPI2C ReloadEndMode definition
  * @{
  */

#define  FMPI2C_RELOAD_MODE                FMPI2C_CR2_RELOAD
#define  FMPI2C_AUTOEND_MODE               FMPI2C_CR2_AUTOEND
#define  FMPI2C_SOFTEND_MODE               ((uint32_t)0x00000000)

/**
  * @}
  */

/** @defgroup FMPI2C_StartStopMode_definition FMPI2C StartStopMode definition
  * @{
  */

#define  FMPI2C_NO_STARTSTOP                 ((uint32_t)0x00000000)
#define  FMPI2C_GENERATE_STOP                FMPI2C_CR2_STOP
#define  FMPI2C_GENERATE_START_READ          (uint32_t)(FMPI2C_CR2_START | FMPI2C_CR2_RD_WRN)
#define  FMPI2C_GENERATE_START_WRITE         FMPI2C_CR2_START
                               
/**
  * @}
  */

/** @defgroup FMPI2C_Interrupt_configuration_definition FMPI2C Interrupt configuration definition
  * @brief FMPI2C Interrupt definition
  *        Elements values convention: 0xXXXXXXXX
  *           - XXXXXXXX  : Interrupt control mask
  * @{
  */
#define FMPI2C_IT_ERRI                       FMPI2C_CR1_ERRIE
#define FMPI2C_IT_TCI                        FMPI2C_CR1_TCIE
#define FMPI2C_IT_STOPI                      FMPI2C_CR1_STOPIE
#define FMPI2C_IT_NACKI                      FMPI2C_CR1_NACKIE
#define FMPI2C_IT_ADDRI                      FMPI2C_CR1_ADDRIE
#define FMPI2C_IT_RXI                        FMPI2C_CR1_RXIE
#define FMPI2C_IT_TXI                        FMPI2C_CR1_TXIE

/**
  * @}
  */


/** @defgroup FMPI2C_Flag_definition FMPI2C Flag definition
  * @{
  */ 

#define FMPI2C_FLAG_TXE                      FMPI2C_ISR_TXE
#define FMPI2C_FLAG_TXIS                     FMPI2C_ISR_TXIS
#define FMPI2C_FLAG_RXNE                     FMPI2C_ISR_RXNE
#define FMPI2C_FLAG_ADDR                     FMPI2C_ISR_ADDR
#define FMPI2C_FLAG_AF                       FMPI2C_ISR_NACKF
#define FMPI2C_FLAG_STOPF                    FMPI2C_ISR_STOPF
#define FMPI2C_FLAG_TC                       FMPI2C_ISR_TC
#define FMPI2C_FLAG_TCR                      FMPI2C_ISR_TCR
#define FMPI2C_FLAG_BERR                     FMPI2C_ISR_BERR
#define FMPI2C_FLAG_ARLO                     FMPI2C_ISR_ARLO
#define FMPI2C_FLAG_OVR                      FMPI2C_ISR_OVR
#define FMPI2C_FLAG_PECERR                   FMPI2C_ISR_PECERR
#define FMPI2C_FLAG_TIMEOUT                  FMPI2C_ISR_TIMEOUT
#define FMPI2C_FLAG_ALERT                    FMPI2C_ISR_ALERT
#define FMPI2C_FLAG_BUSY                     FMPI2C_ISR_BUSY
#define FMPI2C_FLAG_DIR                      FMPI2C_ISR_DIR

/**
  * @}
  */

/**
  * @}
  */ 
  
/* Exported macro ------------------------------------------------------------*/
/** @defgroup FMPI2C_Exported_Macros FMPI2C Exported Macros
  * @{
  */

/** @brief Reset FMPI2C handle state
  * @param  __HANDLE__: specifies the FMPI2C Handle.
  *         This parameter can be FMPI2C where x: 1 or 2 to select the FMPI2C peripheral.
  * @retval None
  */
#define __HAL_FMPI2C_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_FMPI2C_STATE_RESET)

/** @brief  Enables or disables the specified FMPI2C interrupts.
  * @param  __HANDLE__: specifies the FMPI2C Handle.
  *         This parameter can be FMPI2C where x: 1 or 2 to select the FMPI2C peripheral.
  * @param  __INTERRUPT__: specifies the interrupt source to enable or disable.
  *        This parameter can be one of the following values:
  *            @arg FMPI2C_IT_ERRI: Errors interrupt enable
  *            @arg FMPI2C_IT_TCI: Transfer complete interrupt enable
  *            @arg FMPI2C_IT_STOPI: STOP detection interrupt enable
  *            @arg FMPI2C_IT_NACKI: NACK received interrupt enable
  *            @arg FMPI2C_IT_ADDRI: Address match interrupt enable
  *            @arg FMPI2C_IT_RXI: RX interrupt enable
  *            @arg FMPI2C_IT_TXI: TX interrupt enable
  *   
  * @retval None
  */
  
#define __HAL_FMPI2C_ENABLE_IT(__HANDLE__, __INTERRUPT__)   ((__HANDLE__)->Instance->CR1 |= (__INTERRUPT__))
#define __HAL_FMPI2C_DISABLE_IT(__HANDLE__, __INTERRUPT__)  ((__HANDLE__)->Instance->CR1 &= (~(__INTERRUPT__)))
 
/** @brief  Checks if the specified FMPI2C interrupt source is enabled or disabled.
  * @param  __HANDLE__: specifies the FMPI2C Handle.
  *         This parameter can be FMPI2C where x: 1 or 2 to select the FMPI2C peripheral.
  * @param  __INTERRUPT__: specifies the FMPI2C interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg FMPI2C_IT_ERRI: Errors interrupt enable
  *            @arg FMPI2C_IT_TCI: Transfer complete interrupt enable
  *            @arg FMPI2C_IT_STOPI: STOP detection interrupt enable
  *            @arg FMPI2C_IT_NACKI: NACK received interrupt enable
  *            @arg FMPI2C_IT_ADDRI: Address match interrupt enable
  *            @arg FMPI2C_IT_RXI: RX interrupt enable
  *            @arg FMPI2C_IT_TXI: TX interrupt enable
  *   
  * @retval The new state of __IT__ (TRUE or FALSE).
  */
#define __HAL_FMPI2C_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) ((((__HANDLE__)->Instance->CR1 & (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)

/** @brief  Checks whether the specified FMPI2C flag is set or not.
  * @param  __HANDLE__: specifies the FMPI2C Handle.
  *         This parameter can be FMPI2C where x: 1 or 2 to select the FMPI2C peripheral.
  * @param  __FLAG__: specifies the flag to check.
  *        This parameter can be one of the following values:
  *            @arg FMPI2C_FLAG_TXE:      Transmit data register empty
  *            @arg FMPI2C_FLAG_TXIS:     Transmit interrupt status
  *            @arg FMPI2C_FLAG_RXNE:     Receive data register not empty
  *            @arg FMPI2C_FLAG_ADDR:     Address matched (slave mode)
  *            @arg FMPI2C_FLAG_AF:       Acknowledge failure received flag
  *            @arg FMPI2C_FLAG_STOPF:    STOP detection flag
  *            @arg FMPI2C_FLAG_TC:       Transfer complete (master mode)
  *            @arg FMPI2C_FLAG_TCR:      Transfer complete reload
  *            @arg FMPI2C_FLAG_BERR:     Bus error
  *            @arg FMPI2C_FLAG_ARLO:     Arbitration lost
  *            @arg FMPI2C_FLAG_OVR:      Overrun/Underrun
  *            @arg FMPI2C_FLAG_PECERR:   PEC error in reception
  *            @arg FMPI2C_FLAG_TIMEOUT:  Timeout or Tlow detection flag 
  *            @arg FMPI2C_FLAG_ALERT:    SMBus alert
  *            @arg FMPI2C_FLAG_BUSY:     Bus busy
  *            @arg FMPI2C_FLAG_DIR:      Transfer direction (slave mode)
  *
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_FMPI2C_GET_FLAG(__HANDLE__, __FLAG__) (((((__HANDLE__)->Instance->ISR) & ((__FLAG__) & FMPI2C_FLAG_MASK)) == ((__FLAG__) & FMPI2C_FLAG_MASK)))

/** @brief  Clears the FMPI2C pending flags which are cleared by writing 1 in a specific bit.
  * @param  __HANDLE__: specifies the FMPI2C Handle.
  *         This parameter can be FMPI2C where x: 1 or 2 to select the FMPI2C peripheral.
  * @param  __FLAG__: specifies the flag to clear.
  *          This parameter can be any combination of the following values:
  *            @arg FMPI2C_FLAG_ADDR:    Address matched (slave mode)
  *            @arg FMPI2C_FLAG_AF:      Acknowledge failure received flag
  *            @arg FMPI2C_FLAG_STOPF:   STOP detection flag
  *            @arg FMPI2C_FLAG_BERR:    Bus error
  *            @arg FMPI2C_FLAG_ARLO:    Arbitration lost
  *            @arg FMPI2C_FLAG_OVR:     Overrun/Underrun            
  *            @arg FMPI2C_FLAG_PECERR:  PEC error in reception
  *            @arg FMPI2C_FLAG_TIMEOUT: Timeout or Tlow detection flag 
  *            @arg FMPI2C_FLAG_ALERT:   SMBus alert
  *   
  * @retval None
  */
#define __HAL_FMPI2C_CLEAR_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->ICR = ((__FLAG__) & FMPI2C_FLAG_MASK))
 

#define __HAL_FMPI2C_ENABLE(__HANDLE__)                            ((__HANDLE__)->Instance->CR1 |=  FMPI2C_CR1_PE)
#define __HAL_FMPI2C_DISABLE(__HANDLE__)                           ((__HANDLE__)->Instance->CR1 &=  ~FMPI2C_CR1_PE)

#define __HAL_FMPI2C_RESET_CR2(__HANDLE__)				((__HANDLE__)->Instance->CR2 &= (uint32_t)~((uint32_t)(FMPI2C_CR2_SADD | FMPI2C_CR2_HEAD10R | FMPI2C_CR2_NBYTES | FMPI2C_CR2_RELOAD | FMPI2C_CR2_RD_WRN)))

#define __HAL_FMPI2C_MEM_ADD_MSB(__ADDRESS__)                       ((uint8_t)((uint16_t)(((uint16_t)((__ADDRESS__) & (uint16_t)(0xFF00))) >> 8)))
#define __HAL_FMPI2C_MEM_ADD_LSB(__ADDRESS__)                       ((uint8_t)((uint16_t)((__ADDRESS__) & (uint16_t)(0x00FF))))

#define __HAL_FMPI2C_GENERATE_START(__ADDMODE__,__ADDRESS__)       (((__ADDMODE__) == FMPI2C_ADDRESSINGMODE_7BIT) ? (uint32_t)((((uint32_t)(__ADDRESS__) & (FMPI2C_CR2_SADD)) | (FMPI2C_CR2_START) | (FMPI2C_CR2_AUTOEND)) & (~FMPI2C_CR2_RD_WRN)) : \
                                                                  (uint32_t)((((uint32_t)(__ADDRESS__) & (FMPI2C_CR2_SADD)) | (FMPI2C_CR2_ADD10) | (FMPI2C_CR2_START)) & (~FMPI2C_CR2_RD_WRN)))

#define IS_FMPI2C_OWN_ADDRESS1(ADDRESS1)   ((ADDRESS1) <= (uint32_t)0x000003FF)
#define IS_FMPI2C_OWN_ADDRESS2(ADDRESS2)   ((ADDRESS2) <= (uint16_t)0x00FF)

/**
  * @}
  */

/* Include FMPI2C HAL Extension module */
#include "stm32f4xx_hal_fmpi2c_ex.h"

/* Exported functions --------------------------------------------------------*/
/** @addtogroup FMPI2C_Exported_Functions
  * @{
  */

/** @addtogroup FMPI2C_Exported_Functions_Group1
  * @{
  */

/* Initialization/de-initialization functions**********************************/
HAL_StatusTypeDef HAL_FMPI2C_Init(FMPI2C_HandleTypeDef *hFMPI2C);
HAL_StatusTypeDef HAL_FMPI2C_DeInit (FMPI2C_HandleTypeDef *hFMPI2C);
void HAL_FMPI2C_MspInit(FMPI2C_HandleTypeDef *hFMPI2C);
void HAL_FMPI2C_MspDeInit(FMPI2C_HandleTypeDef *hFMPI2C);

/**
  * @}
  */

/** @addtogroup FMPI2C_Exported_Functions_Group2
  * @{
  */

/* I/O operation functions  ***************************************************/
 /******* Blocking mode: Polling */
HAL_StatusTypeDef HAL_FMPI2C_Master_Transmit(FMPI2C_HandleTypeDef *hFMPI2C, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_FMPI2C_Master_Receive(FMPI2C_HandleTypeDef *hFMPI2C, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_FMPI2C_Slave_Transmit(FMPI2C_HandleTypeDef *hFMPI2C, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_FMPI2C_Slave_Receive(FMPI2C_HandleTypeDef *hFMPI2C, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_FMPI2C_Mem_Write(FMPI2C_HandleTypeDef *hFMPI2C, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_FMPI2C_Mem_Read(FMPI2C_HandleTypeDef *hFMPI2C, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_FMPI2C_IsDeviceReady(FMPI2C_HandleTypeDef *hFMPI2C, uint16_t DevAddress, uint32_t Trials, uint32_t Timeout);

 /******* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_FMPI2C_Master_Transmit_IT(FMPI2C_HandleTypeDef *hFMPI2C, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_FMPI2C_Master_Receive_IT(FMPI2C_HandleTypeDef *hFMPI2C, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_FMPI2C_Slave_Transmit_IT(FMPI2C_HandleTypeDef *hFMPI2C, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_FMPI2C_Slave_Receive_IT(FMPI2C_HandleTypeDef *hFMPI2C, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_FMPI2C_Mem_Write_IT(FMPI2C_HandleTypeDef *hFMPI2C, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_FMPI2C_Mem_Read_IT(FMPI2C_HandleTypeDef *hFMPI2C, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);

 /******* Non-Blocking mode: DMA */
HAL_StatusTypeDef HAL_FMPI2C_Master_Transmit_DMA(FMPI2C_HandleTypeDef *hFMPI2C, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_FMPI2C_Master_Receive_DMA(FMPI2C_HandleTypeDef *hFMPI2C, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_FMPI2C_Slave_Transmit_DMA(FMPI2C_HandleTypeDef *hFMPI2C, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_FMPI2C_Slave_Receive_DMA(FMPI2C_HandleTypeDef *hFMPI2C, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_FMPI2C_Mem_Write_DMA(FMPI2C_HandleTypeDef *hFMPI2C, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_FMPI2C_Mem_Read_DMA(FMPI2C_HandleTypeDef *hFMPI2C, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);

 /******* FMPI2C IRQHandler and Callbacks used in non blocking modes (Interrupt and DMA) */
void HAL_FMPI2C_EV_IRQHandler(FMPI2C_HandleTypeDef *hFMPI2C);
void HAL_FMPI2C_ER_IRQHandler(FMPI2C_HandleTypeDef *hFMPI2C);
void HAL_FMPI2C_MasterTxCpltCallback(FMPI2C_HandleTypeDef *hFMPI2C);
void HAL_FMPI2C_MasterRxCpltCallback(FMPI2C_HandleTypeDef *hFMPI2C);
void HAL_FMPI2C_SlaveTxCpltCallback(FMPI2C_HandleTypeDef *hFMPI2C);
void HAL_FMPI2C_SlaveRxCpltCallback(FMPI2C_HandleTypeDef *hFMPI2C);
void HAL_FMPI2C_MemTxCpltCallback(FMPI2C_HandleTypeDef *hFMPI2C);
void HAL_FMPI2C_MemRxCpltCallback(FMPI2C_HandleTypeDef *hFMPI2C);
void HAL_FMPI2C_ErrorCallback(FMPI2C_HandleTypeDef *hFMPI2C);
/**
  * @}
  */

/** @addtogroup FMPI2C_Exported_Functions_Group3
  * @{
  */

/* Peripheral State functions  ************************************************/
HAL_FMPI2C_StateTypeDef HAL_FMPI2C_GetState(FMPI2C_HandleTypeDef *hFMPI2C);
uint32_t             HAL_FMPI2C_GetError(FMPI2C_HandleTypeDef *hFMPI2C);

/**
  * @}
  */

/**
  * @}
  */ 

/* Private types -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup FMPI2C_Private_Constants FMPI2C Private Constants
  * @{
  */
#define FMPI2C_FLAG_MASK  ((uint32_t)0x0001FFFF)
/**
  * @}
  */ 

/* Private macros ------------------------------------------------------------*/
/** @defgroup FMPI2C_Private_Macros FMPI2C Private Macros
  * @{
  */

#define IS_FMPI2C_ADDRESSING_MODE(MODE) (((MODE) == FMPI2C_ADDRESSINGMODE_7BIT) || \
                                         ((MODE) == FMPI2C_ADDRESSINGMODE_10BIT))

#define IS_FMPI2C_DUAL_ADDRESS(ADDRESS) (((ADDRESS) == FMPI2C_DUALADDRESS_DISABLE) || \
                                         ((ADDRESS) == FMPI2C_DUALADDRESS_ENABLE))

#define IS_FMPI2C_OWN_ADDRESS2_MASK(MASK)  (((MASK) == FMPI2C_OA2_NOMASK) || \
                                            ((MASK) == FMPI2C_OA2_MASK01) || \
                                            ((MASK) == FMPI2C_OA2_MASK02) || \
                                            ((MASK) == FMPI2C_OA2_MASK03) || \
                                            ((MASK) == FMPI2C_OA2_MASK04) || \
                                            ((MASK) == FMPI2C_OA2_MASK05) || \
                                            ((MASK) == FMPI2C_OA2_MASK06) || \
                                            ((MASK) == FMPI2C_OA2_MASK07)) 

#define IS_FMPI2C_GENERAL_CALL(CALL) (((CALL) == FMPI2C_GENERALCALL_DISABLE) || \
                                      ((CALL) == FMPI2C_GENERALCALL_ENABLE))

#define IS_FMPI2C_NO_STRETCH(STRETCH) (((STRETCH) == FMPI2C_NOSTRETCH_DISABLE) || \
                                       ((STRETCH) == FMPI2C_NOSTRETCH_ENABLE))

#define IS_FMPI2C_MEMADD_SIZE(SIZE) (((SIZE) == FMPI2C_MEMADD_SIZE_8BIT) || \
                                     ((SIZE) == FMPI2C_MEMADD_SIZE_16BIT))

#define IS_TRANSFER_MODE(MODE)        (((MODE) == FMPI2C_RELOAD_MODE)  || \
                                       ((MODE) == FMPI2C_AUTOEND_MODE) || \
                                       ((MODE) == FMPI2C_SOFTEND_MODE))

#define IS_TRANSFER_REQUEST(REQUEST)    (((REQUEST) == FMPI2C_GENERATE_STOP)        || \
                                         ((REQUEST) == FMPI2C_GENERATE_START_READ)  || \
                                         ((REQUEST) == FMPI2C_GENERATE_START_WRITE) || \
                                         ((REQUEST) == FMPI2C_NO_STARTSTOP))

/**
  * @}
  */ 
/* Private functions ---------------------------------------------------------*/
/** @defgroup FMPI2C_Private_Functions FMPI2C Private Functions
  * @brief    FMPI2C private  functions 
  * @{
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
#endif /* STM32F410xx || STM32F446xx */ 
#ifdef __cplusplus
}
#endif


#endif /* __STM32F4xx_HAL_FMPI2C_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
