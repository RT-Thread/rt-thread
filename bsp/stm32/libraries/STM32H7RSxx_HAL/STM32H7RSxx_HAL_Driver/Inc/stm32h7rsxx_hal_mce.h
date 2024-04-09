/**
  ******************************************************************************
  * @file    stm32h7rsxx_hal_mce.h
  * @author  MCD Application Team
  * @brief   Header file of MCE HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H7RSxx_HAL_MCE_H
#define STM32H7RSxx_HAL_MCE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7rsxx_hal_def.h"

/** @addtogroup STM32H7RSxx_HAL_Driver
  * @{
  */

#if defined(MCE1)
/** @addtogroup MCE
  * @{
  */
typedef struct
{
  uint32_t         ContextID;              /*!< MCE region context ID (can be null) */
  /*!< This parameter is a value of @ref MCE_Context_Index. */

  uint32_t         StartAddress;           /*!< MCE region start address */

  uint32_t         EndAddress;             /*!< MCE region end address */

  uint32_t         Mode;                   /*!< Indicates the chaining mode used for encryption. */
  /*!< This parameter is a value of @defgroup MCE_Ciphering_Algorithm */
  uint32_t         AccessMode;             /*!< MCE region writes enabled or not */
  /*!< This parameter is a value of @ref MCE_Region_Privilege. */

  uint32_t         PrivilegedAccess;       /*!< MCE region privileged access or not */
  /*!< This parameter is a value of @ref MCE_Region_Privilege. */

} MCE_RegionConfigTypeDef;

typedef struct
{
  uint32_t         Nonce[2];              /*!< MCE context nonce */

  uint32_t         Version;               /*!< 16-bit long MCE context version */

  uint32_t         *pKey;                  /*!< Pointer at the key used for encryption/decryption */

} MCE_AESConfigTypeDef;

typedef struct
{
  uint32_t          KeyType;             /*!< This parameter is a value of @ref MCE_KeyType. */

  uint32_t          *pKey;                   /*!< Pointer at the key used for encryption/decryption .*/

} MCE_NoekeonConfigTypeDef;


/**
  * @brief MCE states structure definition
  */
typedef enum
{
  HAL_MCE_STATE_RESET             = 0x00U,  /*!< MCE not yet initialized or disabled */
  HAL_MCE_STATE_READY             = 0x01U,  /*!< MCE initialized and ready for use   */
  HAL_MCE_STATE_BUSY              = 0x02U,  /*!< MCE internal processing is ongoing  */
} HAL_MCE_StateTypeDef;

#if (USE_HAL_MCE_REGISTER_CALLBACKS == 1)
typedef struct __MCE_HandleTypeDef
#else
typedef struct
#endif /* USE_HAL_MCE_REGISTER_CALLBACKS */
{
  MCE_TypeDef             *Instance;        /*!< MCE registers base address */

  HAL_MCE_StateTypeDef    State;            /*!< MCE state */

  HAL_LockTypeDef         Lock;             /*!< MCE Locking object */

  __IO uint32_t           ErrorCode;        /*!< MCE error code */

#if (USE_HAL_MCE_REGISTER_CALLBACKS == 1)
  void (* ErrorCallback)(struct __MCE_HandleTypeDef *hmce);     /*!< MCE error callback */

  void (* MspInitCallback)(struct __MCE_HandleTypeDef *hmce);   /*!< MCE Msp Init callback */

  void (* MspDeInitCallback)(struct __MCE_HandleTypeDef *hmce); /*!< MCE Msp DeInit callback */
#endif /* USE_HAL_MCE_REGISTER_CALLBACKS */

} MCE_HandleTypeDef;

#if (USE_HAL_MCE_REGISTER_CALLBACKS == 1)
/**
  * @brief  HAL MCE Callback ID enumeration definition
  */
typedef enum
{
  HAL_MCE_ERROR_CB_ID       = 0x00U,  /*!< MCE error callback ID      */
  HAL_MCE_MSPINIT_CB_ID     = 0x01U,  /*!< MCE Msp DeInit callback ID */
  HAL_MCE_MSPDEINIT_CB_ID   = 0x02U   /*!< MCE Msp DeInit callback ID */
} HAL_MCE_CallbackIDTypeDef;

/**
  * @brief  HAL MCE Callback pointer definition
  */
typedef  void (*pMCE_CallbackTypeDef)(MCE_HandleTypeDef *hmce); /*!< pointer to a MCE callback function */

#endif /* USE_HAL_MCE_REGISTER_CALLBACKS */

/* Exported constants --------------------------------------------------------*/
/** @defgroup MCE_Exported_Constants MCE Exported Constants
  * @{
  */

/** @defgroup MCE_Error_Definition   MCE Error Definition
  * @{
  */
#define  HAL_MCE_ERROR_NONE                       ((uint32_t)0x00000000U)    /*!< No error                                                         */
#define  HAL_MCE_CONFIGURATION_ACCESS_ERROR       ((uint32_t)0x00000001U)    /*!< Configuration access error                                       */
#define  HAL_MCE_ILLEGAL_ACCESS_READ_PRIV_ERROR   ((uint32_t)0x00000002U)    /*!< Illegal privileged data read or instruction fetch access error   */
#define  HAL_MCE_ILLEGAL_ACCESS_READ_NPRIV_ERROR  ((uint32_t)0x00000004U)    /*!< Illegal unprivileged data read or instruction fetch access error */
#define  HAL_MCE_ILLEGAL_ACCESS_WRITE_PRIV_ERROR  ((uint32_t)0x00000008U)    /*!< Illegal privileged data write access error                       */
#define  HAL_MCE_ILLEGAL_ACCESS_WRITE_NPRIV_ERROR ((uint32_t)0x00000010U)    /*!< Illegal un privileged data write access error                    */
#define  HAL_MCE_MASTER_KEY_ERROR                 ((uint32_t)0x00000020U)    /*!< Master key error                                                 */
#define  HAL_MCE_FASTMASTER_KEY_ERROR             ((uint32_t)0x00000040U)    /*!< Fast master key error                                            */
#define  HAL_MCE_CONTEXT_KEY_ERROR                ((uint32_t)0x00000080U)    /*!< Context key error                                                */
#if (USE_HAL_MCE_REGISTER_CALLBACKS == 1)
#define HAL_MCE_ERROR_INVALID_CALLBACK            ((uint32_t)0x00000100U)    /*!< Invalid Callback error                                           */
#endif /* USE_HAL_MCE_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup MCE_Interrupts    MCE Interrupts
  * @{
  */
#define MCE_IT_ILLEGAL_ACCESS_ERROR        MCE_IAIER_IAEIE                   /*!< Illegal access error interrupt       */
#define MCE_IT_CONFIGURATION_ACCESS_ERROR  MCE_IAIER_CAEIE                   /*!< Configuration access error interrupt */
#define MCE_IT_ALL                        (MCE_IAIER_IAEIE|MCE_IAIER_CAEIE)  /*!< All interrupts                       */
/**
  * @}
  */

/** @defgroup MCE_Illegal_Access_Flags    MCE Illegal Access Flags
  * @{
  */
#define MCE_CONFIGURATION_ACCESS_ERROR     MCE_IASR_CAEF                      /*!< Configuration access error                                    */
#define MCE_ILLEGAL_ACCESS_READ_NPRIV      MCE_IASR_IAEF                      /*!< Illegal unprivileged data read/instruction fetch access flag   */
#define MCE_ILLEGAL_ACCESS_READ_PRIV       (MCE_IASR_IAEF | MCE_IAESR_IAPRIV) /*!< Illegal privileged data read/instruction fetch access flag     */
#define MCE_ILLEGAL_ACCESS_WRITE_NPRIV     (MCE_IASR_IAEF | MCE_IAESR_IANRW)  /*!< Illegal unprivileged write access access flag                 */
#define MCE_ILLEGAL_ACCESS_WRITE_PRIV      (MCE_IASR_IAEF | MCE_IAESR_IANRW | MCE_IAESR_IAPRIV) /*!< Illegal privileged write access access flag */
/**
  * @}
  */


/** @defgroup MCE_Regions_Index   MCE Regions Index
  * @{
  */
#define MCE_REGION1                       0U    /*!< MCE region 1 */
#define MCE_REGION2                       1U    /*!< MCE region 2 */
#define MCE_REGION3                       2U    /*!< MCE region 3 */
#define MCE_REGION4                       3U    /*!< MCE region 4 */
/**
  * @}
  */

/** @defgroup MCE_Context_Index   MCE Context Index
  * @{
  */
#define MCE_NO_CONTEXT                    0U                /*!< MCE no context */
#define MCE_CONTEXT1                      MCE_REGCR_CTXID_0 /*!< MCE context 1  */
#define MCE_CONTEXT2                      MCE_REGCR_CTXID_1 /*!< MCE context 2  */
/**
  * @}
  */

/** @defgroup MCE_Ciphering_Algorithm   MCE Ciphering Algorithm
  * @{
  */
#define MCE_NO_CIPHER                     0U               /*!< MCE no cipher         */
#define MCE_STREAM_CIPHER                 MCE_REGCR_ENC_0  /*!< MCE stream cipher     */
#define MCE_BLOCK_CIPHER                  MCE_REGCR_ENC_1  /*!< MCE block cipher      */
#define MCE_FASTBLOCK_CIPHER              MCE_REGCR_ENC    /*!< MCE fast block cipher */
/**
  * @}
  */


/** @defgroup MCE_Region_Privilege   MCE Region Privilege
  * @{
  */
#define MCE_REGION_NPRIV                  0U               /*!< Region non-privileged and privileged access */
#define MCE_REGION_PRIV                   MCE_REGCR_PRIV   /*!< Region privileged access only               */
/**
  * @}
  */


/** @defgroup MCE_Region_Privilege   MCE Region Privilege
  * @{
  */
#define MCE_REGION_READONLY               0U               /*!< Writes to region are ignored, reads are allowed */
#define MCE_REGION_READWRITE              MCE_ATTR_WREN    /*!< Region can be read and written                  */
/**
  * @}
  */

/** @defgroup MCE_Configuration_Attributes   MCE Configuration Attributes
  * @{
  */
#define MCE_ATTRIBUTE_NPRIV               0U                /*!< Non-privileged access protection */
#define MCE_ATTRIBUTE_PRIV                MCE_PRIVCFGR_PRIV /*!< Privileged access protection     */
/**
  * @}
  */

/** @defgroup MCE_Lock MCE Lock values
  * @{
  */
#define MCE_LOCK_OFF                      0U            /*!< No global lock set */
#define MCE_LOCK_ON                       MCE_CR_GLOCK  /*!< Global lock set    */
/**
  * @}
  */

/** @defgroup MCE_Lock MCE Lock values
  * @{
  */
#define MCE_MASTERKEYS_LOCK_OFF           0U             /*!< No master keys lock set */
#define MCE_MASTERKEYS_LOCK_ON            MCE_CR_MKLOCK  /*!< Master keys lock set    */
/**
  * @}
  */

/** @defgroup MCE_KeyType key type used for encryption, Master key or Fast Master key
  * @{
  */
#define MCE_USE_MASTERKEYS              0U             /*!< Master keys used for encryption         */
#define MCE_USE_FASTMASTERKEYS          1U             /*!< Fast Master keys used for encryption    */
/**
  * @}
  */



/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup MCE_Exported_Macros MCE Exported Macros
  * @{
  */

/** @brief  Reset MCE handle state.
  * @param  __HANDLE__ pointer to an MCE_HandleTypeDef structure that contains
  *         the configuration information for MCE module
  * @retval None
  */
#if (USE_HAL_MCE_REGISTER_CALLBACKS == 1)
#define __HAL_MCE_RESET_HANDLE_STATE(__HANDLE__)                            \
  do{                                                                       \
    (__HANDLE__)->State = HAL_MCE_STATE_RESET;                              \
    (__HANDLE__)->MspInitCallback = NULL;                                   \
    (__HANDLE__)->MspDeInitCallback = NULL;                                 \
  } while(0)
#else
#define __HAL_MCE_RESET_HANDLE_STATE(__HANDLE__)                            \
  ((__HANDLE__)->State = HAL_MCE_STATE_RESET)
#endif /* USE_HAL_MCE_REGISTER_CALLBACKS */

/**
  * @brief  Enable MCE peripheral interrupts combination
  * @param  __HANDLE__ pointer to an MCE_HandleTypeDef structure that contains
  *         the configuration information for MCE module
  * @param  __INTERRUPT__ mask on enabled interrupts
  *          This parameter can be one of the following values:
  *            @arg @ref MCE_IT_ILLEGAL_ACCESS_ERROR        MCE illegal access error interrupt
  *            @arg @ref MCE_IT_CONFIGURATION_ACCESS_ERROR  MCE configuration access error interrupt
  *            @arg @ref MCE_IT_ALL                         MCE all interrupts
  * @retval None
  */
#define __HAL_MCE_ENABLE_IT(__HANDLE__, __INTERRUPT__)  SET_BIT(((__HANDLE__)->Instance->IAIER), (__INTERRUPT__))

/**
  * @brief  Disable MCE peripheral interrupts combination
  * @param  __HANDLE__ pointer to an MCE_HandleTypeDef structure that contains
  *         the configuration information for MCE module
  * @param  __INTERRUPT__ mask on disabled interrupts
  *          This parameter can be one of the following values:
  *            @arg @ref MCE_IT_ILLEGAL_ACCESS_ERROR        MCE illegal access error interrupt
  *            @arg @ref MCE_IT_CONFIGURATION_ACCESS_ERROR  MCE configuration access error interrupt
  *            @arg @ref MCE_IT_ALL                         MCE all interrupts
  * @retval None
  */
#define __HAL_MCE_DISABLE_IT(__HANDLE__, __INTERRUPT__)  CLEAR_BIT(((__HANDLE__)->Instance->IAIER), (__INTERRUPT__))


/**
  * @brief  Get MCE peripheral access error flag
  * @param  __HANDLE__ pointer to an MCE_HandleTypeDef structure that contains
  *         the configuration information for MCE module
  * @param  __FLAG__ access error flag to check
  *          This parameter can be one of the following values:
  *          @arg @ref MCE_CONFIGURATION_ACCESS_ERROR  MCE configuration access error flag
  *          @arg @ref MCE_ILLEGAL_ACCESS_READ_NPRIV   MCE illegal unprivileged data read/instruction fetch access flag
  *          @arg @ref MCE_ILLEGAL_ACCESS_READ_PRIV    MCE illegal privileged data read/instruction fetch access flag
  *          @arg @ref MCE_ILLEGAL_ACCESS_WRITE_NPRIV  MCE illegal unprivileged write access access flag
  *          @arg @ref MCE_ILLEGAL_ACCESS_WRITE_PRIV   MCE illegal privileged write access access flag
  * @retval 0 (not set) or 1 (set)
  */
#define __HAL_MCE_GET_FLAG(__HANDLE__, __FLAG__)  \
  (((__FLAG__) == MCE_CONFIGURATION_ACCESS_ERROR) ? \
   (READ_BIT((__HANDLE__)->Instance->IASR, MCE_IASR_CAEF) == MCE_IASR_CAEF) : \
   ((READ_BIT((__HANDLE__)->Instance->IASR, MCE_IASR_IAEF) == MCE_IASR_IAEF) && \
    (READ_BIT((__HANDLE__)->Instance->IAESR, ((__FLAG__) & ~MCE_IASR_IAEF)) == ((__FLAG__) & ~MCE_IASR_IAEF))))



/**
  * @brief  Clear MCE peripheral illegal/configuration access flag
  * @param  __HANDLE__ pointer to an MCE_HandleTypeDef structure that contains
  *         the configuration information for MCE module
  * @param  __FLAG__ illegal access flag to check
  *        This parameter can be one of the following values:
  *          @arg @ref MCE_CONFIGURATION_ACCESS_ERROR  MCE configuration access error flag
  *          @arg @ref MCE_ILLEGAL_ACCESS_READ_NPRIV   MCE illegal unprivileged data read/instruction fetch access flag
  *          @arg @ref MCE_ILLEGAL_ACCESS_READ_PRIV    MCE illegal privileged data read/instruction fetch access flag
  *          @arg @ref MCE_ILLEGAL_ACCESS_WRITE_NPRIV  MCE illegal unprivileged write access access flag
  *          @arg @ref MCE_ILLEGAL_ACCESS_WRITE_PRIV   MCE illegal privileged write access access flag
  * @retval 0 (not set) or 1 (set)
  */
#define __HAL_MCE_CLEAR_FLAG(__HANDLE__, __FLAG__)  \
  (((__FLAG__) == MCE_CONFIGURATION_ACCESS_ERROR) ? WRITE_REG(((__HANDLE__)->Instance->IACR), MCE_IACR_CAEF) : \
   WRITE_REG(((__HANDLE__)->Instance->IACR), MCE_IACR_IAEF))


/**
  * @}
  */




/* Exported functions ---------------------------------------------------------*/


HAL_StatusTypeDef HAL_MCE_Init(MCE_HandleTypeDef *hmce);
HAL_StatusTypeDef HAL_MCE_DeInit(MCE_HandleTypeDef *hmce);
void HAL_MCE_MspInit(MCE_HandleTypeDef *hmce);
void HAL_MCE_MspDeInit(MCE_HandleTypeDef *hmce);


HAL_StatusTypeDef HAL_MCE_ConfigNoekeon(MCE_HandleTypeDef *hmce, const MCE_NoekeonConfigTypeDef *pConfig);
HAL_StatusTypeDef HAL_MCE_ConfigAESContext(MCE_HandleTypeDef *hmce, const MCE_AESConfigTypeDef  *AESConfig,
                                           uint32_t ContextIndex);
HAL_StatusTypeDef HAL_MCE_ConfigRegion(MCE_HandleTypeDef *hmce, uint32_t RegionIndex,
                                       const MCE_RegionConfigTypeDef *pConfig);
HAL_StatusTypeDef HAL_MCE_SetRegionAESContext(MCE_HandleTypeDef *hmce, uint32_t ContextIndex, uint32_t RegionIndex);
HAL_StatusTypeDef HAL_MCE_EnableAESContext(MCE_HandleTypeDef *hmce, uint32_t ContextIndex);
HAL_StatusTypeDef HAL_MCE_DisableAESContext(MCE_HandleTypeDef *hmce, uint32_t ContextIndex);
HAL_StatusTypeDef HAL_MCE_EnableRegion(MCE_HandleTypeDef *hmce, uint32_t RegionIndex);
HAL_StatusTypeDef HAL_MCE_DisableRegion(MCE_HandleTypeDef *hmce, uint32_t RegionIndex);
HAL_StatusTypeDef HAL_MCE_LockGlobalConfig(MCE_HandleTypeDef *hmce);
HAL_StatusTypeDef HAL_MCE_LockAESContextConfig(MCE_HandleTypeDef *hmce, uint32_t ContextIndex);
HAL_StatusTypeDef HAL_MCE_LockAESContextKey(MCE_HandleTypeDef *hmce, uint32_t ContextIndex);
HAL_StatusTypeDef HAL_MCE_LockNoekeonMasterKeys(MCE_HandleTypeDef *hmce);
HAL_StatusTypeDef HAL_MCE_LockNoekeonFastKeys(MCE_HandleTypeDef *hmce);
HAL_StatusTypeDef HAL_MCE_GetAESContextCRCKey(const MCE_HandleTypeDef *hmce, uint32_t *pCRCKey, uint32_t ContextIndex);


void HAL_MCE_IRQHandler(MCE_HandleTypeDef *hmce);
void HAL_MCE_ErrorCallback(MCE_HandleTypeDef *hmce);

HAL_MCE_StateTypeDef HAL_MCE_GetState(MCE_HandleTypeDef const *hmce);
uint32_t HAL_MCE_GetError(MCE_HandleTypeDef const *hmce);
uint32_t HAL_MCE_KeyCRCComputation(const uint32_t *pKey);

#define IS_MCE_INTERRUPT(__INTERRUPT__) (((__INTERRUPT__) == MCE_IT_ILLEGAL_ACCESS_ERROR)       || \
                                         ((__INTERRUPT__) == MCE_IT_CONFIGURATION_ACCESS_ERROR) || \
                                         ((__INTERRUPT__) == MCE_IT_ALL)  )

/**
  * @brief Verify the MCE region index.
  * @param __INDEX__ MCE region index
  * @retval SET (__INDEX__ is valid) or RESET (__INDEX__ is invalid)
  */
#define IS_MCE_REGIONINDEX(__INDEX__) (((__INDEX__) == MCE_REGION1)     || \
                                       ((__INDEX__) == MCE_REGION2)     || \
                                       ((__INDEX__) == MCE_REGION3)     || \
                                       ((__INDEX__) == MCE_REGION4))

/**
  * @brief Verify the MCE configuration attributes.
  * @param __ATTRIBUTE__ MCE region index
  * @retval SET (__ATTRIBUTE__ is valid) or RESET (__ATTRIBUTE__ is invalid)
  */
#define IS_MCE_ATTRIBUTE(__ATTRIBUTE__) (((__ATTRIBUTE__) == MCE_ATTRIBUTE_PRIV)   || \
                                         ((__ATTRIBUTE__) == MCE_ATTRIBUTE_NPRIV))

/**
  * @brief Verify the MCE region privilege attribute.
  * @param __PRIVILEGED__ MCE region privilege attribute
  * @retval SET (__PRIVILEGED__ is valid) or RESET (__PRIVILEGED__ is invalid)
  */
#define IS_MCE_REGIONPRIVILEGED(__PRIVILEGED__) (((__PRIVILEGED__) == MCE_REGION_NPRIV)   || \
                                                 ((__PRIVILEGED__) == MCE_REGION_PRIV))

/**
  * @brief Verify the MCE region write enable attribute.
  * @param __WRITE__ MCE region write enable attribute
  * @retval SET (__WRITE__ is valid) or RESET (__WRITE__ is invalid)
  */
#define IS_MCE_WRITE(__WRITE__) (((__WRITE__) == MCE_REGION_READONLY)   || \
                                 ((__WRITE__) == MCE_REGION_READWRITE))

/**
  * @brief Verify the MCE region context.
  * @param __INSTANCE__ MCE instance
  * @param __CONTEXT__ MCE region context
  * @retval SET (__CONTEXT__ is valid) or RESET (__CONTEXT__ is invalid)
  */
#define IS_MCE_CONTEXT(__INSTANCE__, __CONTEXT__) (((__INSTANCE__) == (MCE1)) ?           \
                                                   (((__CONTEXT__) == MCE_NO_CONTEXT)   || \
                                                    ((__CONTEXT__) == MCE_CONTEXT1)     || \
                                                    ((__CONTEXT__) == MCE_CONTEXT2))     : \
                                                   ((__CONTEXT__) == MCE_NO_CONTEXT))

/**
  * @brief Verify the MCE region algorithm.
  * @param __INSTANCE__ MCE instance
  * @param __ALGO__ MCE region context
  * @retval SET (__ALGO__ is valid) or RESET (__ALGO__ is invalid)
  */
#define IS_MCE_ALGORITHM(__INSTANCE__, __ALGO__) (((__INSTANCE__) == (MCE1)) ?             \
                                                  (((__ALGO__) == MCE_NO_CIPHER)         || \
                                                   ((__ALGO__) == MCE_STREAM_CIPHER)     || \
                                                   ((__ALGO__) == MCE_BLOCK_CIPHER)      || \
                                                   ((__ALGO__) == MCE_FASTBLOCK_CIPHER))  : \
                                                  (((__ALGO__) == MCE_NO_CIPHER)         || \
                                                   ((__ALGO__) == MCE_BLOCK_CIPHER)      || \
                                                   ((__ALGO__) == MCE_FASTBLOCK_CIPHER)))



#endif /* MCE1 */

/**
  * @}
  */

/**
  * @}
  */
#ifdef __cplusplus
}
#endif

#endif /* STM32H7RSxx_HAL_MCE_H */

