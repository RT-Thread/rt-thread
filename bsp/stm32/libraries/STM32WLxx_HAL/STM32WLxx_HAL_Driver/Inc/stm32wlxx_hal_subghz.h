/**
  ******************************************************************************
  * @file    stm32wlxx_hal_subghz.h
  * @author  MCD Application Team
  * @brief   Header file of SUBGHZ HAL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32WLxx_HAL_SUBGHZ_H
#define STM32WLxx_HAL_SUBGHZ_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wlxx_hal_def.h"

/* Include low level driver */
#include "stm32wlxx_ll_spi.h"

/** @addtogroup STM32WLxx_HAL_Driver
  * @{
  */

/** @addtogroup SUBGHZ
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup SUBGHZ_Exported_Types SUBGHZ Exported Types
  * @{
  */

/**
  * @brief  SPI Configuration Structure definition
  */
typedef struct
{
  uint32_t BaudratePrescaler;   /*!< Specifies the Baud Rate prescaler value which will be
                                     used to configure SUBGHZSPI clock.
                                     This parameter can be a value of @ref SUBGHZSPI_BAUDRATE_Prescaler  */
} SUBGHZ_InitTypeDef;

/**
  * @brief  HAL SUBGHZ State structure definition
  */
typedef enum
{
  HAL_SUBGHZ_STATE_RESET                    = 0x00U,    /*!< Peripheral not Initialized                  */
  HAL_SUBGHZ_STATE_READY                    = 0x01U,    /*!< Peripheral Initialized and ready for use    */
  HAL_SUBGHZ_STATE_BUSY                     = 0x02U,    /*!< an internal process is ongoing              */
} HAL_SUBGHZ_StateTypeDef;

/**
  * @brief  HAL SUBGHZ CAD Status structure definition
  */
typedef enum
{
  HAL_SUBGHZ_CAD_CLEAR                      = 0x00U,    /*!< Channel activity cleared                    */
  HAL_SUBGHZ_CAD_DETECTED                   = 0x01U,    /*!< Channel activity detected                   */
} HAL_SUBGHZ_CadStatusTypeDef;

/**
  * @brief  SUBGHZ handle Structure definition
  */
#if (USE_HAL_SUBGHZ_REGISTER_CALLBACKS == 1)
typedef struct __SUBGHZ_HandleTypeDef
#else
typedef struct
#endif /* USE_HAL_SUBGHZ_REGISTER_CALLBACKS */
{
  SUBGHZ_InitTypeDef                        Init;       /*!< SUBGHZ communication parameters             */

  uint8_t                                   DeepSleep;  /*!< SUBGHZ deep sleep state                     */

  HAL_LockTypeDef                           Lock;       /*!< Locking object                              */

  __IO HAL_SUBGHZ_StateTypeDef              State;      /*!< SUBGHZ communication state                  */

  __IO uint32_t                             ErrorCode;  /*!< SUBGHZ Error code                           */

#if (USE_HAL_SUBGHZ_REGISTER_CALLBACKS == 1)
  void (* TxCpltCallback)(struct __SUBGHZ_HandleTypeDef *hsubghz);                /*!< SUBGHZ Tx Completed callback          */
  void (* RxCpltCallback)(struct __SUBGHZ_HandleTypeDef *hsubghz);                /*!< SUBGHZ Rx Completed callback          */
  void (* PreambleDetectedCallback)(struct __SUBGHZ_HandleTypeDef *hsubghz);      /*!< SUBGHZ Preamble detected callback     */
  void (* SyncWordValidCallback)(struct __SUBGHZ_HandleTypeDef *hsubghz);         /*!< SUBGHZ Synchro word valid callback    */
  void (* HeaderValidCallback)(struct __SUBGHZ_HandleTypeDef *hsubghz);           /*!< SUBGHZ Header valid callback          */
  void (* HeaderErrorCallback)(struct __SUBGHZ_HandleTypeDef *hsubghz);           /*!< SUBGHZ Header error callback          */
  void (* CRCErrorCallback)(struct __SUBGHZ_HandleTypeDef *hsubghz);              /*!< SUBGHZ CRC Error callback             */
  void (* CADStatusCallback)(struct __SUBGHZ_HandleTypeDef *hsubghz, HAL_SUBGHZ_CadStatusTypeDef cadstatus); /*!< SUBGHZ CAD Status callback            */
  void (* RxTxTimeoutCallback)(struct __SUBGHZ_HandleTypeDef *hsubghz);           /*!< SUBGHZ Rx Tx Timeout callback         */
  void (* MspInitCallback)(struct __SUBGHZ_HandleTypeDef *hsubghz);               /*!< SUBGHZ Msp Init callback              */
  void (* MspDeInitCallback)(struct __SUBGHZ_HandleTypeDef *hsubghz);             /*!< SUBGHZ Msp DeInit callback            */
#endif  /* USE_HAL_SUBGHZ_REGISTER_CALLBACKS */
} SUBGHZ_HandleTypeDef;

#if (USE_HAL_SUBGHZ_REGISTER_CALLBACKS == 1)
/**
  * @brief  HAL SUBGHZ Callback ID enumeration definition
  */
typedef enum
{
  HAL_SUBGHZ_TX_COMPLETE_CB_ID              = 0x00U,    /*!< SUBGHZ Tx Completed callback ID             */
  HAL_SUBGHZ_RX_COMPLETE_CB_ID              = 0x01U,    /*!< SUBGHZ Rx Completed callback ID             */
  HAL_SUBGHZ_PREAMBLE_DETECTED_CB_ID        = 0x02U,    /*!< SUBGHZ Preamble detected callback ID        */
  HAL_SUBGHZ_SYNCWORD_VALID_CB_ID           = 0x03U,    /*!< SUBGHZ Synchro word valid callback ID       */
  HAL_SUBGHZ_HEADER_VALID_CB_ID             = 0x04U,    /*!< SUBGHZ Header valid callback ID             */
  HAL_SUBGHZ_HEADER_ERROR_CB_ID             = 0x05U,    /*!< SUBGHZ Header error callback ID             */
  HAL_SUBGHZ_CRC_ERROR_CB_ID                = 0x06U,    /*!< SUBGHZ CRC error callback ID                */
  HAL_SUBGHZ_RX_TX_TIMEOUT_CB_ID            = 0x07U,    /*!< SUBGHZ Rx Tx timeout callback ID            */
  HAL_SUBGHZ_MSPINIT_CB_ID                  = 0x08U,    /*!< SUBGHZ Msp Init callback ID                 */
  HAL_SUBGHZ_MSPDEINIT_CB_ID                = 0x09U     /*!< SUBGHZ Msp DeInit callback ID               */

} HAL_SUBGHZ_CallbackIDTypeDef;

/**
  * @brief  HAL SUBGHZ Callback pointer definition
  */
typedef  void (*pSUBGHZ_CallbackTypeDef)(SUBGHZ_HandleTypeDef *hsubghz); /*!< pointer to an SUBGHZ callback function */
typedef  void (*pSUBGHZ_CadStatusCallbackTypeDef)(SUBGHZ_HandleTypeDef *hsubghz, HAL_SUBGHZ_CadStatusTypeDef cadstatus); /*!< pointer to an CAD Status callback function */
#endif /* USE_HAL_SUBGHZ_REGISTER_CALLBACKS */

/*
 * @brief  HAL SUBGHZ Radio Set Command enumeration definition
 */
typedef enum
{
  RADIO_SET_SLEEP                           = 0x84U,
  RADIO_SET_STANDBY                         = 0x80U,
  RADIO_SET_FS                              = 0xC1U,
  RADIO_SET_TX                              = 0x83U,
  RADIO_SET_RX                              = 0x82U,
  RADIO_SET_RXDUTYCYCLE                     = 0x94U,
  RADIO_SET_CAD                             = 0xC5U,
  RADIO_SET_TXCONTINUOUSWAVE                = 0xD1U,
  RADIO_SET_TXCONTINUOUSPREAMBLE            = 0xD2U,
  RADIO_SET_PACKETTYPE                      = 0x8AU,
  RADIO_SET_RFFREQUENCY                     = 0x86U,
  RADIO_SET_TXPARAMS                        = 0x8EU,
  RADIO_SET_PACONFIG                        = 0x95U,
  RADIO_SET_CADPARAMS                       = 0x88U,
  RADIO_SET_BUFFERBASEADDRESS               = 0x8FU,
  RADIO_SET_MODULATIONPARAMS                = 0x8BU,
  RADIO_SET_PACKETPARAMS                    = 0x8CU,
  RADIO_RESET_STATS                         = 0x00U,
  RADIO_CFG_DIOIRQ                          = 0x08U,
  RADIO_CLR_IRQSTATUS                       = 0x02U,
  RADIO_CALIBRATE                           = 0x89U,
  RADIO_CALIBRATEIMAGE                      = 0x98U,
  RADIO_SET_REGULATORMODE                   = 0x96U,
  RADIO_SET_TCXOMODE                        = 0x97U,
  RADIO_SET_TXFALLBACKMODE                  = 0x93U,
  RADIO_SET_RFSWITCHMODE                    = 0x9DU,
  RADIO_SET_STOPRXTIMERONPREAMBLE           = 0x9FU,
  RADIO_SET_LORASYMBTIMEOUT                 = 0xA0U,
  RADIO_CLR_ERROR                           = 0x07U
} SUBGHZ_RadioSetCmd_t;


/**
  * @brief  HAL SUBGHZ Radio Get Command enumeration definition
  */
typedef enum
{
  RADIO_GET_STATUS                          = 0xC0U,
  RADIO_GET_PACKETTYPE                      = 0x11U,
  RADIO_GET_RXBUFFERSTATUS                  = 0x13U,
  RADIO_GET_PACKETSTATUS                    = 0x14U,
  RADIO_GET_RSSIINST                        = 0x15U,
  RADIO_GET_STATS                           = 0x10U,
  RADIO_GET_IRQSTATUS                       = 0x12U,
  RADIO_GET_ERROR                           = 0x17U
} SUBGHZ_RadioGetCmd_t;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup SUBGHZ_Exported_Constants SUBGHZ Exported Constants
  * @{
  */

/** @defgroup SUBGHZ_Error_Code SUBGHZ Error Code definition
  * @brief  SUBGHZ Error Code definition
  * @{
  */
#define HAL_SUBGHZ_ERROR_NONE               (0x00000000U)   /*!< No error                         */
#define HAL_SUBGHZ_ERROR_TIMEOUT            (0x00000001U)   /*!< Timeout Error                    */
#define HAL_SUBGHZ_ERROR_RF_BUSY            (0x00000002U)   /*!< RF Busy Error                    */
#if (USE_HAL_SUBGHZ_REGISTER_CALLBACKS == 1)
#define HAL_SUBGHZ_ERROR_INVALID_CALLBACK   (0x00000080U)   /*!< Invalid Callback error           */
#endif /* USE_HAL_SUBGHZ_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup SUBGHZSPI_BAUDRATE_Prescaler SUBGHZ BaudRate Prescaler
  * @{
  */
#define SUBGHZSPI_BAUDRATEPRESCALER_2       (0x00000000U)
#define SUBGHZSPI_BAUDRATEPRESCALER_4       (SPI_CR1_BR_0)
#define SUBGHZSPI_BAUDRATEPRESCALER_8       (SPI_CR1_BR_1)
#define SUBGHZSPI_BAUDRATEPRESCALER_16      (SPI_CR1_BR_1 | SPI_CR1_BR_0)
#define SUBGHZSPI_BAUDRATEPRESCALER_32      (SPI_CR1_BR_2)
#define SUBGHZSPI_BAUDRATEPRESCALER_64      (SPI_CR1_BR_2 | SPI_CR1_BR_0)
#define SUBGHZSPI_BAUDRATEPRESCALER_128     (SPI_CR1_BR_2 | SPI_CR1_BR_1)
#define SUBGHZSPI_BAUDRATEPRESCALER_256     (SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0)
/**
  * @}
  */

/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/** @defgroup SUBGHZ_Private_Constants SUBGHZ Private Constants
  * @{
  */

/**
  * @brief SUBGHZSPI_Interrupts SUBGHZSPI Interrupts
  */
#define SUBGHZ_IT_TX_CPLT                   0x0001U
#define SUBGHZ_IT_RX_CPLT                   0x0002U
#define SUBGHZ_IT_PREAMBLE_DETECTED         0x0004U
#define SUBGHZ_IT_SYNCWORD_VALID            0x0008U
#define SUBGHZ_IT_HEADER_VALID              0x0010U
#define SUBGHZ_IT_HEADER_ERROR              0x0020U
#define SUBGHZ_IT_CRC_ERROR                 0x0040U
#define SUBGHZ_IT_CAD_DONE                  0x0080U
#define SUBGHZ_IT_CAD_ACTIVITY_DETECTED     0x0100U
#define SUBGHZ_IT_RX_TX_TIMEOUT             0x0200U

/**
  * @brief SUBGHZ Radio Read/Write Command definition
  */
#define SUBGHZ_RADIO_WRITE_REGISTER         0x0DU
#define SUBGHZ_RADIO_READ_REGISTER          0x1DU
#define SUBGHZ_RADIO_WRITE_BUFFER           0x0EU
#define SUBGHZ_RADIO_READ_BUFFER            0x1EU
/**
  * @}
  */


/* Exported macros -----------------------------------------------------------*/
/** @defgroup SUBGHZ_Exported_Macros SUBGHZ Exported Macros
  * @{
  */

/** @brief  Reset SUBGHZ handle state.
  * @param  __HANDLE__ specifies the SUBGHZ Handle.
  * @retval None
  */
#if (USE_HAL_SUBGHZ_REGISTER_CALLBACKS == 1)
#define __HAL_SUBGHZ_RESET_HANDLE_STATE(__HANDLE__)             do{                                                  \
                                                                    (__HANDLE__)->State = HAL_SUBGHZ_STATE_RESET;    \
                                                                    (__HANDLE__)->MspInitCallback = NULL;            \
                                                                    (__HANDLE__)->MspDeInitCallback = NULL;          \
                                                                  } while(0U)
#else
#define __HAL_SUBGHZ_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_SUBGHZ_STATE_RESET)
#endif /* USE_HAL_SUBGHZ_REGISTER_CALLBACKS */
/**
  * @}
  */

/* Private macros -----------------------------------------------------------*/
/** @defgroup SUBGHZ_Private_Macros SUBGHZ Private Macros
  * @{
  */

/** @brief  Check whether the specified SPI Interrupt is set or not.
  * @param  __SUBGHZ_IRQ__  copy of SUBGHZ IRQ Register.
  * @param  __INTERRUPT__ specifies the SUBGHZ interrupt source to check.
  *         This parameter can be one of the following values:
  *            @arg SUBGHZ_IT_TX_DONE
  *            @arg SUBGHZ_IT_RX_DONE
  *            @arg SUBGHZ_IT_PREAMBLE_DETECTED
  *            @arg SUBGHZ_IT_SYNCWORD_VALID
  *            @arg SUBGHZ_IT_HEADER_VALID
  *            @arg SUBGHZ_IT_HEADER_ERROR
  *            @arg SUBGHZ_IT_CRC_ERROR
  *            @arg SUBGHZ_IT_CAD_DONE
  *            @arg SUBGHZ_IT_CAD_ACTIVITY_DETECTED
  *            @arg SUBGHZ_IT_RX_TX_TIMEOUT
  * @retval SET or RESET.
  */
#define SUBGHZ_CHECK_IT_SOURCE(__SUBGHZ_IRQ__, __INTERRUPT__)       \
  ((((__SUBGHZ_IRQ__) & (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)

/** @brief  Checks if SUBGHZSPI Baudrate prescaler parameter is in allowed range.
  * @param  __PRESCALER__ specifies the SUBGHZSPI Baudrate prescaler.
  *         This parameter can be a value of @ref SUBGHZSPI_BAUDRATE_Prescaler
  * @retval None
  */
#define IS_SUBGHZSPI_BAUDRATE_PRESCALER(__PRESCALER__) (((__PRESCALER__) == SUBGHZSPI_BAUDRATEPRESCALER_2)    || \
                                                        ((__PRESCALER__) == SUBGHZSPI_BAUDRATEPRESCALER_4)    || \
                                                        ((__PRESCALER__) == SUBGHZSPI_BAUDRATEPRESCALER_8)    || \
                                                        ((__PRESCALER__) == SUBGHZSPI_BAUDRATEPRESCALER_16)   || \
                                                        ((__PRESCALER__) == SUBGHZSPI_BAUDRATEPRESCALER_32)   || \
                                                        ((__PRESCALER__) == SUBGHZSPI_BAUDRATEPRESCALER_64)   || \
                                                        ((__PRESCALER__) == SUBGHZSPI_BAUDRATEPRESCALER_128)  || \
                                                        ((__PRESCALER__) == SUBGHZSPI_BAUDRATEPRESCALER_256))
/**
  * @}
  */

/* Exported functions ------------------------------------------------------- */
/** @addtogroup SUBGHZ_Exported_Functions
  * @{
  */

/** @addtogroup SUBGHZ_Exported_Functions_Group1
  * @{
  */
/* Initialization/de-initialization functions  ********************************/
HAL_StatusTypeDef HAL_SUBGHZ_Init(SUBGHZ_HandleTypeDef *hsubghz);
HAL_StatusTypeDef HAL_SUBGHZ_DeInit(SUBGHZ_HandleTypeDef *hsubghz);
void              HAL_SUBGHZ_MspInit(SUBGHZ_HandleTypeDef *hsubghz);
void              HAL_SUBGHZ_MspDeInit(SUBGHZ_HandleTypeDef *hsubghz);

/* Callbacks Register/UnRegister functions  ***********************************/
#if (USE_HAL_SUBGHZ_REGISTER_CALLBACKS == 1)
HAL_StatusTypeDef HAL_SUBGHZ_RegisterCallback(SUBGHZ_HandleTypeDef *hsubghz,
                                              HAL_SUBGHZ_CallbackIDTypeDef CallbackID,
                                              pSUBGHZ_CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_SUBGHZ_UnRegisterCallback(SUBGHZ_HandleTypeDef *hsubghz,
                                                HAL_SUBGHZ_CallbackIDTypeDef CallbackID);
HAL_StatusTypeDef HAL_SUBGHZ_RegisterCadStatusCallback(SUBGHZ_HandleTypeDef *hsubghz,
                                                       pSUBGHZ_CadStatusCallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_SUBGHZ_UnRegisterCadStatusCallback(SUBGHZ_HandleTypeDef *hsubghz);
#endif /* USE_HAL_SUBGHZ_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @addtogroup SUBGHZ_Exported_Functions_Group2
  * @{
  */
/* I/O operation functions  ***************************************************/
HAL_StatusTypeDef HAL_SUBGHZ_ExecSetCmd(SUBGHZ_HandleTypeDef *hsubghz, SUBGHZ_RadioSetCmd_t Command, uint8_t *pBuffer,
                                        uint16_t Size);
HAL_StatusTypeDef HAL_SUBGHZ_ExecGetCmd(SUBGHZ_HandleTypeDef *hsubghz, SUBGHZ_RadioGetCmd_t Command, uint8_t *pBuffer,
                                        uint16_t Size);
HAL_StatusTypeDef HAL_SUBGHZ_WriteBuffer(SUBGHZ_HandleTypeDef *hsubghz, uint8_t Offset, uint8_t *pBuffer,
                                         uint16_t Size);
HAL_StatusTypeDef HAL_SUBGHZ_ReadBuffer(SUBGHZ_HandleTypeDef *hsubghz, uint8_t Offset, uint8_t *pBuffer,
                                        uint16_t Size);
HAL_StatusTypeDef HAL_SUBGHZ_WriteRegisters(SUBGHZ_HandleTypeDef *hsubghz, uint16_t Address, uint8_t *pBuffer,
                                            uint16_t Size);
HAL_StatusTypeDef HAL_SUBGHZ_ReadRegisters(SUBGHZ_HandleTypeDef *hsubghz, uint16_t Address, uint8_t *pBuffer,
                                           uint16_t Size);

HAL_StatusTypeDef HAL_SUBGHZ_WriteRegister(SUBGHZ_HandleTypeDef *hsubghz, uint16_t Address, uint8_t Value);
HAL_StatusTypeDef HAL_SUBGHZ_ReadRegister(SUBGHZ_HandleTypeDef *hsubghz, uint16_t Address, uint8_t *pValue);

void HAL_SUBGHZ_IRQHandler(SUBGHZ_HandleTypeDef *hsubghz);
void HAL_SUBGHZ_TxCpltCallback(SUBGHZ_HandleTypeDef *hsubghz);
void HAL_SUBGHZ_RxCpltCallback(SUBGHZ_HandleTypeDef *hsubghz);
void HAL_SUBGHZ_PreambleDetectedCallback(SUBGHZ_HandleTypeDef *hsubghz);
void HAL_SUBGHZ_SyncWordValidCallback(SUBGHZ_HandleTypeDef *hsubghz);
void HAL_SUBGHZ_HeaderValidCallback(SUBGHZ_HandleTypeDef *hsubghz);
void HAL_SUBGHZ_HeaderErrorCallback(SUBGHZ_HandleTypeDef *hsubghz);
void HAL_SUBGHZ_CRCErrorCallback(SUBGHZ_HandleTypeDef *hsubghz);
void HAL_SUBGHZ_CADStatusCallback(SUBGHZ_HandleTypeDef *hsubghz, HAL_SUBGHZ_CadStatusTypeDef cadstatus);
void HAL_SUBGHZ_RxTxTimeoutCallback(SUBGHZ_HandleTypeDef *hsubghz);
/**
  * @}
  */

/** @addtogroup SUBGHZ_Exported_Functions_Group3
  * @{
  */
/* Peripheral State and Error functions ***************************************/
HAL_SUBGHZ_StateTypeDef HAL_SUBGHZ_GetState(SUBGHZ_HandleTypeDef *hsubghz);
uint32_t                HAL_SUBGHZ_GetError(SUBGHZ_HandleTypeDef *hsubghz);
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

#endif /* STM32WLxx_HAL_SUBGHZ_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
