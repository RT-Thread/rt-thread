/**
  ******************************************************************************
  * @file    ft32f4xx_spdif.h
  * @author  xcao
  * @brief   Header file of SPDIF module.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef FT32F4XX_SPDIF_H
#define FT32F4XX_SPDIF_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx.h"

/** @addtogroup SPDIF
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup SPDIF_Exported_Types SPDIF Exported Types
  * @{
  */

/**
  * @brief SPDIF Init structure definition
  */

typedef struct
{
    uint32_t StereoMode;               /*!< Specifies whether the peripheral is in stereo or mono mode.
                                          This parameter can be a value of @ref SPDIF_Stereo_Mode */

    uint32_t ValidityBitMask;          /*!< Specifies whether the frame is written or discarded.
                                          This parameter can be a value of @ref SPDIF_V_Mask */

    uint32_t ParityErrorMask;          /*!< Specifies whether the parity error is checked.
                                          This parameter can be a value of @ref SPDIF_PE_Mask */

    uint16_t FifoAfullThreshold;       /*!< Specifies read fifo almost full threshold.
                                          This parameter can be a value of @ref SPDIF_FifoAF_THLD */

    uint16_t FifoAemptyThreshold;      /*!< Specifies read fifo almost empty threshold
                                          This parameter can be a value of @ref SPDIF_FifoAE_THLD */
} SPDIFRX_InitTypeDef;


/**
  * @brief SPDIF handle Structure definition
  */
typedef struct
{
    SPDIF_TypeDef              *Instance;    /* SPDIFRX registers base address */

    uint32_t                   *pRxBuffPtr;  /* Pointer to SPDIF Rx transfer buffer */


    __IO uint16_t              RxXferSize;   /* SPDIF Rx transfer size */

    __IO uint16_t              RxXferCount;  /* SPDIF Rx transfer counter
                                              (This field is initialized at the
                                               same value as transfer size at the
                                               beginning of the transfer and
                                               decremented when a sample is received.
                                               NbSamplesReceived = RxBufferSize-RxBufferCount) */
} SPDIF_HandleTypeDef;




/* Exported constants --------------------------------------------------------*/
/** @defgroup SPDIF_Exported_Constants SPDIF Exported Constants
  * @{
  */

/** @defgroup SPDIF_Stereo_Mode SPDIF Stereo Mode
  * @{
  */
#define SPDIF_STEREOMODE_DISABLE    ((uint32_t)0x00000000U)
#define SPDIF_STEREOMODE_ENABLE     ((uint32_t)SPDIF_CTRL_CHANNEL_MODE)
/**
  * @}
  */

/** @defgroup SPDIF_V_Mask SPDIF VALID Mask
  * @{
  */
#define SPDIF_VALIDITYMASK_OFF  ((uint32_t)0x00000000U)
#define SPDIF_VALIDITYMASK_ON   ((uint32_t)SPDIF_CTRL_VALIDITYCHECK)
/**
  * @}
  */

/** @defgroup SPDIF_PE_Mask SPDIF PARITYERROR Mask
  * @{
  */
#define SPDIF_PARITYERRORMASK_OFF ((uint32_t)0x00000000U)
#define SPDIF_PARITYERRORMASK_ON  ((uint32_t)SPDIF_CTRL_PARITY_MASK)
/**
  * @}
  */



/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @defgroup SPDIF_Private_Macros SPDIF Private Macros
  * @{
  */

#define IS_STEREO_MODE(MODE)                (((MODE) == SPDIF_STEREOMODE_DISABLE) || \
                                             ((MODE) == SPDIF_STEREOMODE_ENABLE))

#define IS_VALIDITY_MASK(VAL)               (((VAL) == SPDIF_VALIDITYMASK_OFF) || \
                                             ((VAL) == SPDIF_VALIDITYMASK_ON))

#define IS_PARITY_ERROR_MASK(VAL)           (((VAL) == SPDIF_PARITYERRORMASK_OFF) || \
                                             ((VAL) == SPDIF_PARITYERRORMASK_ON))
/**
  * @}
  */


#ifdef __cplusplus
}
#endif

/* Exported functions ---------------------------------------------------------*/
/** @defgroup SPDIF_Exported_Functions SPDIF Exported Functions
  * @{
  */
void SPDIFRX_Init(SPDIF_HandleTypeDef *spdif, SPDIFRX_InitTypeDef *spdifrx_init);
void SPDIF_ReceiveDataFlow(SPDIF_HandleTypeDef *spdif, uint32_t *pData, uint16_t Size,
                           uint32_t Timeout);
void SPDIFRX_ReceiveDataFlow_IT(SPDIF_HandleTypeDef *spdif, uint32_t *pData, uint16_t Size,
                                uint32_t Timeout);
void SPDIF_MspInit(SPDIF_HandleTypeDef *spdif);
/**
  * @}
  */

#endif /* FT32F4XX_SPDIF_H */
