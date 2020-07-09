/**
  ******************************************************************************
  * @file    md_aes.h
  * @brief   M601 AES Head File.
  *
  * @version V0.01
  * @date    28/11/2018
  * @author  Eastsoft AE Team
  * @note
  * detailed description
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MD_AES_H__
#define __MD_AES_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -------------------------------------------------------------------*/ 
#include "es32f0271.h"
  
/** @addtogroup Micro_Driver
  * @{
  */

#if defined (AES)

/** @defgroup AES AES
  * @brief AES micro driver
  * @{
  */
  
/* Private Types --------------------------------------------------------------*/
/* Private Variables ----------------------------------------------------------*/
/* Private Macros -------------------------------------------------------------*/
/* Public Types ---------------------------------------------------------------*/
/** @defgroup MD_AES_INIT AES public init structure
  * @brief
  * @{
  */
typedef struct
{
  volatile uint8_t aes_con_bl;
  volatile uint8_t aes_con_mode;    
  volatile uint32_t aes_key[4];
  volatile uint32_t aes_iv[4];
  volatile uint32_t aes_din[4];
  volatile uint32_t aes_dout[4];
} md_aes_init_typedef; 
/**
  * @} MD_AES_INIT
  */

/* Public constants -----------------------------------------------------------*/
/** @defgroup MD_AES_Public_Constants AES Public Constants
  * @brief
  * @{
  */

/** @defgroup MD_AES_CON_registers AES Control Registers
  * @brief
  * @{
  */
#define MD_AES_CON_READY_BUSY   0                     /*!<  This allow user to read AES Encryption/Decryption Ready Status.       */
#define MD_AES_CON_READY_READY  1                     /*!<  This allow user to read AES Encryption/Decryption Ready Status.       */
#define MD_AES_CON_OT_DMA_ST_PASS 1                   /*!<  This allow user to read AES DMA Output Status.                        */
#define MD_AES_CON_OT_DMA_ST_FAIL 0                   /*!<  This allow user to read AES DMA Output Status.                        */
#define MD_AES_CON_IT_DMA_ST_PASS 1                   /*!<  This allow user to read AES DMA Input Status.                         */
#define MD_AES_CON_IT_DMA_ST_FAIL 0                   /*!<  This allow user to read AES DMA Input Status.                         */
#define MD_AES_CON_OT_DEPTH_0  0                      /*!<  This allow user to read AES DIO data depth status (X=0).              */
#define MD_AES_CON_OT_DEPTH_1  1                      /*!<  This allow user to read AES DIO data depth status (X=1).              */
#define MD_AES_CON_OT_DEPTH_2  2                      /*!<  This allow user to read AES DIO data depth status (X=2).              */
#define MD_AES_CON_OT_DEPTH_3  3                      /*!<  This allow user to read AES DIO data depth status (X=3).              */
#define MD_AES_CON_IT_DEPTH_0  0                      /*!<  This allow user to read AES DIO data depth status (X=0).              */
#define MD_AES_CON_IT_DEPTH_1  1                      /*!<  This allow user to read AES DIO data depth status (X=1).              */
#define MD_AES_CON_IT_DEPTH_2  2                      /*!<  This allow user to read AES DIO data depth status (X=2).              */
#define MD_AES_CON_IT_DEPTH_3  3                      /*!<  This allow user to read AES DIO data depth status (X=3).              */
#define MD_AES_CON_RE_INIT_SET    1                   /*!<  This allow user to set AES Re-initial.      */
#define MD_AES_CON_RE_INIT_UNSET  0                   /*!<  This allow user to set AES Re-initial.      */
#define MD_AES_CON_DMA_EN_INPUT_ENABLE    (1 << 0)    /*!<  This allow user to set AES DMA Function Enable. 0:AES input DMA disable     */
#define MD_AES_CON_DMA_EN_INPUT_DISABLE   (0 << 0)    /*!<  This allow user to set AES DMA Function Enable. 1:AES input DMA enable      */
#define MD_AES_CON_DMA_EN_OUTPUT_ENABLE   (1 << 1     /*!<  This allow user to set AES DMA Function Enable. 0:AES output DMA disable    */
#define MD_AES_CON_DMA_EN_OUTPUT_DISABLE  (0 << 1)    /*!<  This allow user to set AES DMA Function Enable. 1:AES outut DMA enable      */
#define MD_AES_CON_BL_CBC 0                           /*!<  This allow user to set Block Cipher Encryption / Decryption Mode. 000:CBC      */
#define MD_AES_CON_BL_CFB 1                           /*!<  This allow user to set Block Cipher Encryption / Decryption Mode. 001:CFB      */
#define MD_AES_CON_BL_OFB 2                           /*!<  This allow user to set Block Cipher Encryption / Decryption Mode. 010:OFB      */
#define MD_AES_CON_BL_CTR 3                           /*!<  This allow user to set Block Cipher Encryption / Decryption Mode. 011:CTR      */
#define MD_AES_CON_BL_ECB 4                           /*!<  This allow user to set Block Cipher Encryption / Decryption Mode. 100:ECB      */
#define MD_AES_CON_BL_GCM 5                           /*!<  This allow user to set Block Cipher Encryption / Decryption Mode. 101:GCM      */
#define MD_AES_CON_REV_NORMAL   0                     /*!<  This allow user to set AES Input Reverse. 0:Normal Mode      */
#define MD_AES_CON_REV_REVERSE  1                     /*!<  This allow user to set AES Input Reverse. 1:KEY, IV, DI, DO Byte Reverse Mode      */
#define MD_AES_CON_MODE_ENCRYPT 0                     /*!<  This allow user to set AES Mode Control. 0:Encryption Mode      */
#define MD_AES_CON_MODE_DECRYPT 1                     /*!<  This allow user to set AES Mode Control. 1:Decryption Mode      */
#define MD_AES_CON_START 1                            /*!<  This allow user to set AES Start. AES function will start after this bit is set to 1.      */
/**
  * @} MD_AES_CON_registers
  */
  
/** @defgroup MD_AES_IER_registers AES Interrupt Enable Registers
  * @brief
  * @{
  */
#define MD_AES_IER_DECIE  1   /*!<  This allow user to set AES Decryption Interrupt Enable.      */
#define MD_AES_IER_ENCIE  1   /*!<  This allow user to set AES Encryption Interrupt Enable.      */
/**
  * @} MD_AES_IER_registers
  */

/** @defgroup MD_AES_IDR_registers AES Interrupt Disable Registers
  * @brief
  * @{
  */
#define MD_AES_IDR_DECID  1   /*!<  This allow user to set AES Decryption Interrupt Disable.      */
#define MD_AES_IDR_ENCID  1   /*!<  This allow user to set AES Encryption Interrupt Disable.      */
/**
  * @} MD_AES_IDR_registers
  */

/** @defgroup MD_AES_IVS_registers AES Interrupt Valid Status Registers
  * @brief
  * @{
  */
#define MD_AES_IVS_DECIVS_DISABLE  0   /*!<  This allow user to set AES Decryption Interrupt Valid Status. 0:AES Decryption interrupt is disabled.      */
#define MD_AES_IVS_DECIVS_ENABLE   1   /*!<  This allow user to set AES Decryption Interrupt Valid Status. 1:AES Decryption interrupt is enabled.       */
#define MD_AES_IVS_ENCIVS_DISABLE  0   /*!<  This allow user to set AES Encryption Interrupt Valid Status. 0:AES Encryption interrupt is disabled.      */
#define MD_AES_IVS_ENCIVS_ENABLE   1   /*!<  This allow user to set AES Encryption Interrupt Valid Status. 1:AES Encryption interrupt is enabled.       */
/**
  * @} MD_AES_IVS_registers
  */
  
/** @defgroup MD_AES_RIF_registers AES Raw Interrupt Flag Registers
  * @brief
  * @{
  */
#define MD_AES_RIF_DECRIF_NO_INTERRUPT  0   /*!<  This allow user to set AES Decryption Raw Interrupt Flag Status. 0: No interrupt.                               */
#define MD_AES_RIF_DECRIF_INTERRUPT     1   /*!<  This allow user to set AES Decryption Raw Interrupt Flag Status. 1: AES Decryption interrupt is asserting.      */
#define MD_AES_RIF_ENCRIF_NO_INTERRUPT  0   /*!<  This allow user to set AES Encryption Raw Interrupt Flag Status. 0: No interrupt.                               */
#define MD_AES_RIF_ENCRIF_INTERRUPT     1   /*!<  This allow user to set AES Encryption Raw Interrupt Flag Status. 1: AES Encryption interrupt is asserting.      */
/**
  * @} MD_AES_RIF_registers
  */
  
/** @defgroup MD_AES_IFM_registers AES Interrupt Flag Mask Registers
  * @brief
  * @{
  */
#define MD_AES_IFM_DECRIF_MASK    0   /*!<  This allow user to set AES Decryption Interrupt Flag Masked Status. 0: No interrupt or the interrupt has been masked.     */
#define MD_AES_IFM_DECRIF_SIGNAL  1   /*!<  This allow user to set AES Decryption Interrupt Flag Masked Status. 1: AES Decryption interrupt has been signalled.       */
#define MD_AES_IFM_ENCRIF_MASK    0   /*!<  This allow user to set AES Encryption Interrupt Flag Masked Status. 0: No interrupt or the interrupt has been masked.     */
#define MD_AES_IFM_ENCRIF_SIGNAL  1   /*!<  This allow user to set AES Encryption Interrupt Flag Masked Status. 1: AES Encryption interrupt has been signalled.       */
/**
  * @} MD_AES_IFM_registers
  */
  
/** @defgroup MD_AES_ICR_registers AES Interrupt Clear Registers
  * @brief
  * @{
  */
#define MD_AES_ICR_DECICR    1   /*!<  This allow user to set AES Decryption Interrupt Clear. User can set this bit to clear AES Decryption interrupt status.      */
#define MD_AES_ICR_ENCICR    1   /*!<  This allow user to set AES Decryption Interrupt Clear. User can set this bit to clear AES Encryption interrupt status.      */
/**
  * @} MD_AES_ICR_registers
  */

/**
  * @} MD_AES_Public_Constants
  */

/* Public macro ---------------------------------------------------------------*/
/** @defgroup MD_AES_Public_Macros AES Public Macros
  * @brief
  * @{
  */
  
/**
  * @brief  AES Control Register
  * @param  AES Instance
  * @param  value This parameter can be one of the following values:
  *         @arg @ref MD_AES_CON_READY_BUSY   0
  *         @arg @ref MD_AES_CON_READY_READY  1
  *         @arg @ref MD_AES_CON_OT_DMA_ST_PASS 1
  *         @arg @ref MD_AES_CON_OT_DMA_ST_FAIL 0
  *         @arg @ref MD_AES_CON_IT_DMA_ST_PASS 1
  *         @arg @ref MD_AES_CON_IT_DMA_ST_FAIL 0
  *         @arg @ref MD_AES_CON_OT_DEPTH_0  0
  *         @arg @ref MD_AES_CON_OT_DEPTH_1  1
  *         @arg @ref MD_AES_CON_OT_DEPTH_2  2
  *         @arg @ref MD_AES_CON_OT_DEPTH_3  3
  *         @arg @ref MD_AES_CON_IT_DEPTH_0  0
  *         @arg @ref MD_AES_CON_IT_DEPTH_1  1
  *         @arg @ref MD_AES_CON_IT_DEPTH_2  2
  *         @arg @ref MD_AES_CON_IT_DEPTH_3  3
  *         @arg @ref MD_AES_CON_RE_INIT_SET    1
  *         @arg @ref MD_AES_CON_RE_INIT_UNSET  0
  *         @arg @ref MD_AES_CON_DMA_EN_INPUT_ENABLE    (1 << 0)
  *         @arg @ref MD_AES_CON_DMA_EN_INPUT_DISABLE   (0 << 0)
  *         @arg @ref MD_AES_CON_DMA_EN_OUTPUT_ENABLE   (1 << 1)
  *         @arg @ref MD_AES_CON_DMA_EN_OUTPUT_DISABLE  (0 << 1)
  *         @arg @ref MD_AES_CON_BL_CBC 0
  *         @arg @ref MD_AES_CON_BL_CFB 1
  *         @arg @ref MD_AES_CON_BL_OFB 2
  *         @arg @ref MD_AES_CON_BL_CTR 3
  *         @arg @ref MD_AES_CON_BL_ECB 4
  *         @arg @ref MD_AES_CON_BL_GCM 5
  *         @arg @ref MD_AES_CON_REV_NORMAL   0
  *         @arg @ref MD_AES_CON_REV_REVERSE  1
  *         @arg @ref MD_AES_CON_MODE_ENCRYPT 0
  *         @arg @ref MD_AES_CON_MODE_DECRYPT 1
  *         @arg @ref MD_AES_CON_START 1
  * @retval None.
  */
__STATIC_INLINE void md_aes_set_con(AES_TypeDef *aes, uint32_t value)
{
  WRITE_REG(aes->CON, value);
}

/**
  * @brief  AES Control Register
  * @param  AES Instance
  * @retval value This parameter can be one of the following values:
  *         @arg @ref MD_AES_CON_READY_BUSY   0
  *         @arg @ref MD_AES_CON_READY_READY  1
  *         @arg @ref MD_AES_CON_OT_DMA_ST_PASS 1
  *         @arg @ref MD_AES_CON_OT_DMA_ST_FAIL 0
  *         @arg @ref MD_AES_CON_IT_DMA_ST_PASS 1
  *         @arg @ref MD_AES_CON_IT_DMA_ST_FAIL 0
  *         @arg @ref MD_AES_CON_OT_DEPTH_0  0
  *         @arg @ref MD_AES_CON_OT_DEPTH_1  1
  *         @arg @ref MD_AES_CON_OT_DEPTH_2  2
  *         @arg @ref MD_AES_CON_OT_DEPTH_3  3
  *         @arg @ref MD_AES_CON_IT_DEPTH_0  0
  *         @arg @ref MD_AES_CON_IT_DEPTH_1  1
  *         @arg @ref MD_AES_CON_IT_DEPTH_2  2
  *         @arg @ref MD_AES_CON_IT_DEPTH_3  3
  *         @arg @ref MD_AES_CON_RE_INIT_SET    1
  *         @arg @ref MD_AES_CON_RE_INIT_UNSET  0
  *         @arg @ref MD_AES_CON_DMA_EN_INPUT_ENABLE    (1 << 0)
  *         @arg @ref MD_AES_CON_DMA_EN_INPUT_DISABLE   (0 << 0)
  *         @arg @ref MD_AES_CON_DMA_EN_OUTPUT_ENABLE   (1 << 1)
  *         @arg @ref MD_AES_CON_DMA_EN_OUTPUT_DISABLE  (0 << 1)
  *         @arg @ref MD_AES_CON_BL_CBC 0
  *         @arg @ref MD_AES_CON_BL_CFB 1
  *         @arg @ref MD_AES_CON_BL_OFB 2
  *         @arg @ref MD_AES_CON_BL_CTR 3
  *         @arg @ref MD_AES_CON_BL_ECB 4
  *         @arg @ref MD_AES_CON_BL_GCM 5
  *         @arg @ref MD_AES_CON_REV_NORMAL   0
  *         @arg @ref MD_AES_CON_REV_REVERSE  1
  *         @arg @ref MD_AES_CON_MODE_ENCRYPT 0
  *         @arg @ref MD_AES_CON_MODE_DECRYPT 1
  *         @arg @ref MD_AES_CON_START 1
  */
__STATIC_INLINE uint32_t md_aes_get_con(AES_TypeDef *aes)
{
  return (READ_REG(aes->CON));
}

/**
  * @brief  AES Encryption / Decryption Ready Status
  * @param  AES Instance
  * @retval value This parameter can be one of the following values:
  *         @arg @ref MD_AES_CON_READY_BUSY   0
  *         @arg @ref MD_AES_CON_READY_READY  1
  */
__STATIC_INLINE uint32_t md_aes_get_con_ready(AES_TypeDef *aes)
{
  return ((READ_BIT(aes->CON, AES_CON_READY_MSK) >> AES_CON_READY_POS) & 0x1);
}

/**
  * @brief  AES DMA Output Status
  * @param  AES Instance
  * @retval value This parameter can be one of the following values:
  *         @arg @ref MD_AES_CON_OT_DMA_ST_PASS   0
  *         @arg @ref MD_AES_CON_OT_DMA_ST_FAIL   1
  */
__STATIC_INLINE uint32_t md_aes_get_con_ot_dma_st(AES_TypeDef *aes)
{
  return ((READ_BIT(aes->CON, AES_CON_OT_DMA_ST_MSK) >> AES_CON_OT_DMA_ST_POS) & 0x1);
}

/**
  * @brief  AES DMA Intput Status
  * @param  AES Instance
  * @retval value This parameter can be one of the following values:
  *         @arg @ref MD_AES_CON_IT_DMA_ST_PASS   0
  *         @arg @ref MD_AES_CON_IT_DMA_ST_FAIL   1
  */
__STATIC_INLINE uint32_t md_aes_get_con_it_dma_st(AES_TypeDef *aes, uint32_t value)
{
  return ((READ_BIT(aes->CON, AES_CON_IT_DMA_ST_MSK) >> AES_CON_IT_DMA_ST_POS) & 0x1);
}

/**
  * @brief  AES DIO data depth status (X=0,1,2,3)
  * @param  AES Instance
  * @retval value This parameter can be one of the following values:
  *         @arg @ref MD_AES_CON_OT_DEPTH_0  0
  *         @arg @ref MD_AES_CON_OT_DEPTH_1  1
  *         @arg @ref MD_AES_CON_OT_DEPTH_2  2
  *         @arg @ref MD_AES_CON_OT_DEPTH_3  3
  */
__STATIC_INLINE uint32_t md_aes_get_con_ot_depth(AES_TypeDef *aes)
{
  return ((READ_BIT(aes->CON, AES_CON_OT_DEPTH_MSK) >> AES_CON_OT_DEPTH_POSS) & 0x3);
}

/**
  * @brief  AES DIO data depth status (X=0,1,2,3)
  * @param  AES Instance
  * @retval value This parameter can be one of the following values:
  *         @arg @ref MD_AES_CON_IT_DEPTH_0  0
  *         @arg @ref MD_AES_CON_IT_DEPTH_1  1
  *         @arg @ref MD_AES_CON_IT_DEPTH_2  2
  *         @arg @ref MD_AES_CON_IT_DEPTH_3  3
  */
__STATIC_INLINE uint32_t md_aes_get_con_it_depth(AES_TypeDef *aes)
{
  return ((READ_BIT(aes->CON, AES_CON_IT_DEPTH_MSK) >> AES_CON_IT_DEPTH_POSS) & 0x3);
}

/**
  * @brief  AES Re-initial
  * @param  AES Instance
  * @param  value This parameter can be one of the following values:
  *         @arg @ref MD_AES_CON_RE_INIT_SET    1
  *         @arg @ref MD_AES_CON_RE_INIT_UNSET  0
  * @retval None.
  */
__STATIC_INLINE void md_aes_set_con_re_init(AES_TypeDef *aes, uint32_t value)
{
  MODIFY_REG(aes->CON, AES_CON_RE_INIT_MSK, (value << AES_CON_RE_INIT_POS));
}

/**
  * @brief  AES Re-initial
  * @param  AES Instance
  * @retval value This parameter can be one of the following values:
  *         @arg @ref MD_AES_CON_RE_INIT_SET    1
  *         @arg @ref MD_AES_CON_RE_INIT_UNSET  0
  */
__STATIC_INLINE uint32_t md_aes_get_con_re_init(AES_TypeDef *aes)
{
  
  return ((READ_BIT(aes->CON, AES_CON_RE_INIT_MSK) >> AES_CON_RE_INIT_POS) & 0x1);
}

/**
  * @brief  AES DMA Function Enable
  * @param  AES Instance
  * @param  value This parameter can be one of the following values:
  *         @arg @ref MD_AES_CON_DMA_EN_INPUT_ENABLE    (1 << 0)
  *         @arg @ref MD_AES_CON_DMA_EN_INPUT_DISABLE   (0 << 0)
  *         @arg @ref MD_AES_CON_DMA_EN_OUTPUT_ENABLE   (1 << 1)
  *         @arg @ref MD_AES_CON_DMA_EN_OUTPUT_DISABLE  (0 << 1)
  * @retval None.
  */
__STATIC_INLINE void md_aes_set_con_dma_en(AES_TypeDef *aes, uint32_t value)
{
  MODIFY_REG(aes->CON, AES_CON_DMA_EN_MSK, (value << AES_CON_DMA_EN_POSS));
}

/**
  * @brief  AES DMA Function Enable
  * @param  AES Instance
  * @retval value This parameter can be one of the following values:
  *         @arg @ref MD_AES_CON_DMA_EN_INPUT_ENABLE    (1 << 0)
  *         @arg @ref MD_AES_CON_DMA_EN_INPUT_DISABLE   (0 << 0)
  *         @arg @ref MD_AES_CON_DMA_EN_OUTPUT_ENABLE   (1 << 1)
  *         @arg @ref MD_AES_CON_DMA_EN_OUTPUT_DISABLE  (0 << 1)
  */
__STATIC_INLINE uint32_t md_aes_get_con_dma_en(AES_TypeDef *aes)
{
  return ((READ_BIT(aes->CON, AES_CON_DMA_EN_MSK) >> AES_CON_DMA_EN_POSS) & 0x3);
}

/**
  * @brief  Block Cipher Encryption / Decryption Mode
  * @param  AES Instance
  * @param  value This parameter can be one of the following values:
  *         @arg @ref MD_AES_CON_BL_CBC 0
  *         @arg @ref MD_AES_CON_BL_CFB 1
  *         @arg @ref MD_AES_CON_BL_OFB 2
  *         @arg @ref MD_AES_CON_BL_CTR 3
  *         @arg @ref MD_AES_CON_BL_ECB 4
  *         @arg @ref MD_AES_CON_BL_GCM 5
  * @retval None.
  */
__STATIC_INLINE void md_aes_set_con_bl(AES_TypeDef *aes, uint32_t value)
{
  MODIFY_REG(aes->CON, AES_CON_BL_MSK, (value << AES_CON_BL_POSS));
}

/**
  * @brief  Block Cipher Encryption / Decryption Mode
  * @param  AES Instance
  * @retval value This parameter can be one of the following values:
  *         @arg @ref MD_AES_CON_BL_CBC 0
  *         @arg @ref MD_AES_CON_BL_CFB 1
  *         @arg @ref MD_AES_CON_BL_OFB 2
  *         @arg @ref MD_AES_CON_BL_CTR 3
  *         @arg @ref MD_AES_CON_BL_ECB 4
  *         @arg @ref MD_AES_CON_BL_GCM 5
  */
__STATIC_INLINE uint32_t md_aes_get_con_bl(AES_TypeDef *aes)
{
  return ((READ_BIT(aes->CON, AES_CON_BL_MSK) >> AES_CON_BL_POSS) & 0x7);
}

/**
  * @brief  AES Input Reverse
  * @param  AES Instance
  * @param  value This parameter can be one of the following values:
  *         @arg @ref MD_AES_CON_REV_NORMAL   0
  *         @arg @ref MD_AES_CON_REV_REVERSE  1
  * @retval None.
  */
__STATIC_INLINE void md_aes_set_con_rev(AES_TypeDef *aes, uint32_t value)
{
  MODIFY_REG(aes->CON, AES_CON_REV_MSK, (value << AES_CON_REV_POS));
}

/**
  * @brief  AES Input Reverse
  * @param  AES Instance
  * @retval value This parameter can be one of the following values:
  *         @arg @ref MD_AES_CON_REV_NORMAL   0
  *         @arg @ref MD_AES_CON_REV_REVERSE  1
  */
__STATIC_INLINE uint32_t md_aes_get_con_rev(AES_TypeDef *aes)
{
  return ((READ_BIT(aes->CON, AES_CON_REV_MSK) >> AES_CON_REV_POS) & 0x1);
}

/**
  * @brief  AES Mode Control
  * @param  AES Instance
  * @param  value This parameter can be one of the following values:
  *         @arg @ref MD_AES_CON_MODE_ENCRYPT 0
  *         @arg @ref MD_AES_CON_MODE_DECRYPT 1
  * @retval None.
  */
__STATIC_INLINE void md_aes_set_con_mode(AES_TypeDef *aes, uint32_t value)
{
  MODIFY_REG(aes->CON, AES_CON_MODE_MSK, (value << AES_CON_MODE_POS));
}

/**
  * @brief  AES Mode Control
  * @param  AES Instance
  * @retval value This parameter can be one of the following values:
  *         @arg @ref MD_AES_CON_MODE_ENCRYPT 0
  *         @arg @ref MD_AES_CON_MODE_DECRYPT 1
  */
__STATIC_INLINE uint32_t md_aes_get_con_mode(AES_TypeDef *aes)
{
  return ((READ_BIT(aes->CON, AES_CON_MODE_MSK) >> AES_CON_MODE_POS) & 0x1);
}

/**
  * @brief  AES Start
  * @param  AES Instance
  * @param  value This parameter can be one of the following values:
  *         @arg @ref MD_AES_CON_START 1
  * @retval None.
  */
__STATIC_INLINE void md_aes_set_con_start(AES_TypeDef *aes, uint32_t value)
{
  MODIFY_REG(aes->CON, AES_CON_START_MSK, (value << AES_CON_START_POS));
}

/**
  * @brief  AES Start
  * @param  AES Instance
  * @retval value This parameter can be one of the following values:
  *         @arg @ref MD_AES_CON_START 1
  */
__STATIC_INLINE uint32_t md_aes_get_con_start(AES_TypeDef *aes)
{
  return ((READ_BIT(aes->CON, AES_CON_START_MSK) >> AES_CON_START_POS) & 0x1);
}

/**
  * @brief  AES Interrupt Enable Register
  * @param  AES Instance
  * @param  value This parameter can be one of the following values:
  *         @arg @ref MD_AES_IER_DECIE  1
  *         @arg @ref MD_AES_IER_ENCIE  1
  * @retval None.
  */
__STATIC_INLINE void md_aes_set_ier(AES_TypeDef *aes, uint32_t value)
{
  WRITE_REG(aes->IER, value);
}

/**
  * @brief  AES Decryption Interrupt Enable
  * @param  AES Instance
  * @retval None.
  */
__STATIC_INLINE void md_aes_enable_ier_decie(AES_TypeDef *aes)
{
  MODIFY_REG(aes->IER, AES_IER_DECIE_MSK, (1 << AES_IER_DECIE_POS));
}

/**
  * @brief  AES Encryption Interrupt Enable
  * @param  AES Instance
  * @retval None.
  */
__STATIC_INLINE void md_aes_enable_ier_encie(AES_TypeDef *aes)
{
  MODIFY_REG(aes->IER, AES_IER_ENCIE_MSK, (1 << AES_IER_ENCIE_POS));
}

/**
  * @brief  AES Interrupt Disable Register
  * @param  AES Instance
  * @param  value This parameter can be one of the following values:
  *         @arg @ref MD_AES_IDR_DECID  1
  *         @arg @ref MD_AES_IDR_ENCID  1
  * @retval None.
  */
__STATIC_INLINE void md_aes_set_idr(AES_TypeDef *aes, uint32_t value)
{
  WRITE_REG(aes->IDR, value);
}

/**
  * @brief  AES Decryption Interrupt Disable
  * @param  AES Instance
  * @retval None.
  */
__STATIC_INLINE void md_aes_disable_idr_decid(AES_TypeDef *aes)
{
  MODIFY_REG(aes->IDR, AES_IDR_DECID_MSK, (1 << AES_IDR_DECID_POS));
}

/**
  * @brief  AES Encryption Interrupt Disable
  * @param  AES Instance
  * @retval None.
  */
__STATIC_INLINE void md_aes_disable_idr_encid(AES_TypeDef *aes)
{
  MODIFY_REG(aes->IDR, AES_IDR_DECID_MSK, (1 << AES_IDR_DECID_POS));
}

/**
  * @brief  AES Interrupt Valid Status Register
  * @param  AES Instance
  * @retval value This parameter can be one of the following values:
  *         @arg @ref MD_AES_IVS_DECIVS_DISABLE  0
  *         @arg @ref MD_AES_IVS_DECIVS_ENABLE   1
  *         @arg @ref MD_AES_IVS_ENCIVS_DISABLE  0
  *         @arg @ref MD_AES_IVS_ENCIVS_ENABLE   1
  */
__STATIC_INLINE uint32_t md_aes_get_ivs(AES_TypeDef *aes)
{
  return (READ_REG(aes->IVS));
}

/**
  * @brief  AES Decryption Interrupt Valid Status
  * @param  AES Instance
  * @retval value This parameter can be one of the following values:
  *         @arg value true, false
  */
__STATIC_INLINE bool md_aes_is_enabled_ivs_decivs(AES_TypeDef *aes)
{
  return ((READ_BIT(aes->IVS, AES_IVS_DECIVS_MSK) >> AES_IVS_DECIVS_POS) & 0x1) ? true : false;
}

/**
  * @brief  AES Encryption Interrupt Valid Status
  * @param  AES Instance
  * @retval value This parameter can be one of the following values:
  *         @arg value true, false
  */
__STATIC_INLINE bool md_aes_is_enabled_ivs_encivs(AES_TypeDef *aes)
{
  return ((READ_BIT(aes->IVS, AES_IVS_ENCIVS_MSK) >> AES_IVS_ENCIVS_POS) & 0x1) ? true : false;
}

/**
  * @brief  AES Raw Interrupt Flag Status
  * @param  AES Instance
  * @retval value This parameter can be one of the following values:
  *         @arg @reg MD_AES_RIF_DECRIF_NO_INTERRUPT  0
  *         @arg @reg MD_AES_RIF_DECRIF_INTERRUPT     1
  */
__STATIC_INLINE uint32_t md_aes_get_rif(AES_TypeDef *aes)
{
  return (READ_REG(aes->RIF));
}

/**
  * @brief  AES Encryption Raw Interrupt Flag Status
  * @param  AES Instance
  * @retval value This parameter can be one of the following values:
  *         @arg value true, false
  */
__STATIC_INLINE bool md_aes_is_active_rif_decrif(AES_TypeDef *aes)
{
  return ((READ_BIT(aes->RIF, AES_RIF_DECRIF_MSK) >> AES_RIF_DECRIF_POS) & 0x1) ? true : false;
}

/**
  * @brief  AES Encryption Raw Interrupt Flag Status
  * @param  Mode This parameter can be one of the following values:
  *         @arg value true, false
  * @retval None.
  */
__STATIC_INLINE bool md_aes_is_active_rif_encrif(AES_TypeDef *aes)
{
  return ((READ_BIT(aes->RIF, AES_RIF_ENCRIF_MSK) >> AES_RIF_ENCRIF_POS) & 0x1) ? true : false;
}

/**
  * @brief  AES Interrupt Flag Mask Status Register
  * @param  AES Instance
  * @retval value This parameter can be one of the following values:
  *         @arg @reg MD_AES_IFM_DECRIF_MASK    0
  *         @arg @reg MD_AES_IFM_DECRIF_SIGNAL  1
  *         @arg @reg MD_AES_IFM_ENCRIF_MASK    0
  *         @arg @reg MD_AES_IFM_ENCRIF_SIGNAL  1
  */
__STATIC_INLINE uint32_t md_aes_get_ifm(AES_TypeDef *aes)
{
  return (READ_REG(aes->IFM));
}

/**
  * @brief  AES Interrupt Flag Mask Status Register
  * @param  AES Instance
  * @retval value This parameter can be one of the following values:
  *         @arg value true, false
  */
__STATIC_INLINE bool md_aes_is_active_ifm_decifm(AES_TypeDef *aes)
{
  return ((READ_BIT(aes->IFM, AES_IFM_DECIFM_MSK) >> AES_IFM_DECIFM_POS) & 0x1) ? true : false;
}

/**
  * @brief  AES Interrupt Flag Mask Status Register
  * @param  AES Instance
  * @retval value This parameter can be one of the following values:
  *         @arg value true, false
  */
__STATIC_INLINE bool md_aes_is_active_ifm_encifm(AES_TypeDef *aes)
{
  return ((READ_BIT(aes->IFM, AES_IFM_ENCIFM_MSK) >> AES_IFM_ENCIFM_POS) & 0x1) ? true : false;
}

/**
  * @brief  AES Interrupt Clear Register
  * @param  AES Instance
  * @param  value This parameter can be one of the following values:
  *         @arg @reg MD_AES_ICR_DECICR    1
  *         @arg @reg MD_AES_ICR_ENCICR    1
  * @retval None.
  */
__STATIC_INLINE void md_aes_set_icr(AES_TypeDef *aes, uint32_t value)
{
  WRITE_REG(aes->ICR, value);
}

/**
  * @brief  AES Decryption Interrupt Clear
  * @param  AES Instance
  * @retval None.
  */
__STATIC_INLINE void md_aes_clear_icr_decicr(AES_TypeDef *aes)
{
  MODIFY_REG(aes->ICR, AES_ICR_DECICR_MSK, (1 << AES_ICR_DECICR_POS));
}

/**
  * @brief  AES Encryption Interrupt Clear
  * @param  AES Instance
  * @retval None.
  */
__STATIC_INLINE void md_aes_clear_icr_encicr(AES_TypeDef *aes)
{
  MODIFY_REG(aes->ICR, AES_ICR_ENCICR_MSK, (1 << AES_ICR_ENCICR_POS));
}

/**
  * @brief  AES 128-bit Input / Ouput Data Register
  * @param  AES Instance
  * @param  value This parameter can be one of the following values:
  *         @arg Minimum 0x0000000
  *         @arg Maximum 0xFFFFFFF
  * @retval None.
  */
__STATIC_INLINE void md_aes_set_dio(AES_TypeDef *aes, uint32_t value)
{
  WRITE_REG(aes->DIO, value);
}

/**
  * @brief  AES 128-bit Input / Ouput Data Register
  * @param  AES Instance
  * @retval value
  *         @arg Minimum 0x0000000
  *         @arg Maximum 0xFFFFFFF
  */
//#pragma push
//#pragma O0
__STATIC_INLINE uint32_t md_aes_get_dio(AES_TypeDef *aes)
{
  return (READ_REG(aes->DIO));
}
//#pragma pop

/**
  * @brief  AES 128-bit Keyword Register 0
  * @param  AES Instance
  * @param  value This parameter can be one of the following values:
  *         @arg Minimum 0x0000000
  *         @arg Maximum 0xFFFFFFF
  * @retval None.
  */
__STATIC_INLINE void md_aes_set_key0(AES_TypeDef *aes, uint32_t value)
{
  WRITE_REG(aes->KEY0, value);
}

/**
  * @brief  AES 128-bit Keyword Register 0
  * @param  AES Instance
  * @retval value
  *         @arg Minimum 0x0000000
  *         @arg Maximum 0xFFFFFFF
  */
__STATIC_INLINE uint32_t md_aes_get_key0(AES_TypeDef *aes)
{
  return (READ_REG(aes->KEY0));
}

/**
  * @brief  AES 128-bit Keyword Register 1
  * @param  AES Instance
  * @param  value This parameter can be one of the following values:
  *         @arg Minimum 0x0000000
  *         @arg Maximum 0xFFFFFFF
  * @retval None.
  */
__STATIC_INLINE void md_aes_set_key1(AES_TypeDef *aes, uint32_t value)
{
  WRITE_REG(aes->KEY1, value);
}

/**
  * @brief  AES 128-bit Keyword Register 1
  * @param  AES Instance
  * @retval value
  *         @arg Minimum 0x0000000
  *         @arg Maximum 0xFFFFFFF
  */
__STATIC_INLINE uint32_t md_aes_get_key1(AES_TypeDef *aes)
{
  return (READ_REG(aes->KEY1));
}

/**
  * @brief  AES 128-bit Keyword Register 2
  * @param  AES Instance
  * @param  value This parameter can be one of the following values:
  *         @arg Minimum 0x0000000
  *         @arg Maximum 0xFFFFFFF
  * @retval None.
  */
__STATIC_INLINE void md_aes_set_key2(AES_TypeDef *aes, uint32_t value)
{
  WRITE_REG(aes->KEY2, value);
}

/**
  * @brief  AES 128-bit Keyword Register 2
  * @param  AES Instance
  * @retval value
  *         @arg Minimum 0x0000000
  *         @arg Maximum 0xFFFFFFF
  */
__STATIC_INLINE uint32_t md_aes_get_key2(AES_TypeDef *aes)
{
  return (READ_REG(aes->KEY2));
}

/**
  * @brief  AES 128-bit Keyword Register 3
  * @param  AES Instance
  * @param  value This parameter can be one of the following values:
  *         @arg Minimum 0x0000000
  *         @arg Maximum 0xFFFFFFF
  * @retval None.
  */
__STATIC_INLINE void md_aes_set_key3(AES_TypeDef *aes, uint32_t value)
{
  WRITE_REG(aes->KEY3, value);
}

/**
  * @brief  AES 128-bit Keyword Register 3
  * @param  AES Instance
  * @retval value
  *         @arg Minimum 0x0000000
  *         @arg Maximum 0xFFFFFFF
  */
__STATIC_INLINE uint32_t md_aes_get_key3(AES_TypeDef *aes)
{
  return (READ_REG(aes->KEY3));
}

/**
  * @brief  AES 128-bit Initial Vector Register 0
  * @param  AES Instance
  * @param  value This parameter can be one of the following values:
  *         @arg Minimum 0x0000000
  *         @arg Maximum 0xFFFFFFF
  * @retval None.
  */
__STATIC_INLINE void md_aes_set_iv0(AES_TypeDef *aes, uint32_t value)
{
  WRITE_REG(aes->IV0, value);
}

/**
  * @brief  AES 128-bit Initial Vector Register 0
  * @param  AES Instance
  * @retval value
  *         @arg Minimum 0x0000000
  *         @arg Maximum 0xFFFFFFF
  */
__STATIC_INLINE uint32_t md_aes_get_iv0(AES_TypeDef *aes)
{
  return (READ_REG(aes->IV0));
}

/**
  * @brief  AES 128-bit Initial Vector Register 1
  * @param  AES Instance
  * @param  value This parameter can be one of the following values:
  *         @arg Minimum 0x0000000
  *         @arg Maximum 0xFFFFFFF
  * @retval None.
  */
__STATIC_INLINE void md_aes_set_iv1(AES_TypeDef *aes, uint32_t value)
{
  WRITE_REG(aes->IV1, value);
}

/**
  * @brief  AES 128-bit Initial Vector Register 1
  * @param  AES Instance
  * @retval value
  *         @arg Minimum 0x0000000
  *         @arg Maximum 0xFFFFFFF
  */
__STATIC_INLINE uint32_t md_aes_get_iv1(AES_TypeDef *aes)
{
  return (READ_REG(aes->IV1));
}

/**
  * @brief  AES 128-bit Initial Vector Register 2
  * @param  AES Instance
  * @param  value This parameter can be one of the following values:
  *         @arg Minimum 0x0000000
  *         @arg Maximum 0xFFFFFFF
  * @retval None.
  */
__STATIC_INLINE void md_aes_set_iv2(AES_TypeDef *aes, uint32_t value)
{
  WRITE_REG(aes->IV2, value);
}

/**
  * @brief  AES 128-bit Initial Vector Register 2
  * @param  AES Instance
  * @retval value
  *         @arg Minimum 0x0000000
  *         @arg Maximum 0xFFFFFFF
  */
__STATIC_INLINE uint32_t md_aes_get_iv2(AES_TypeDef *aes)
{
  return (READ_REG(aes->IV2));
}

/**
  * @brief  AES 128-bit Initial Vector Register 3
  * @param  AES Instance
  * @param  value This parameter can be one of the following values:
  *         @arg Minimum 0x0000000
  *         @arg Maximum 0xFFFFFFF
  * @retval None.
  */
__STATIC_INLINE void md_aes_set_iv3(AES_TypeDef *aes, uint32_t value)
{
  WRITE_REG(aes->IV3, value);
}

/**
  * @brief  AES 128-bit Initial Vector Register 3
  * @param  AES Instance
  * @retval value
  *         @arg Minimum 0x0000000
  *         @arg Maximum 0xFFFFFFF
  */
__STATIC_INLINE uint32_t md_aes_get_iv3(AES_TypeDef *aes)
{
  return (READ_REG(aes->IV3));
}

/**
  * @} MD_AES_Public_Macros
  */

/**
  * @} AES
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
