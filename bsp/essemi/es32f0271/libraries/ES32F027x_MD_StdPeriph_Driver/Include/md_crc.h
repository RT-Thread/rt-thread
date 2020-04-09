/**
  ******************************************************************************
  * @file    md_crc.h
  * @brief   M601 CRC Head File.
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
#ifndef __MD_CRC_H__
#define __MD_CRC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -------------------------------------------------------------------*/ 
#include "es32f0271.h"
  
/** @addtogroup Micro_Driver
  * @{
  */

#if defined (CRC)

/** @defgroup CRC CRC
  * @brief CRC module driver
  * @{
  */

/* Private Types --------------------------------------------------------------*/
/* Private Variables ----------------------------------------------------------*/
/* Private Macros -------------------------------------------------------------*/
/* Public Types ---------------------------------------------------------------*/
/** @defgroup MD_CRC_INIT CRC public init structure
  * @brief
  * @{
  */
typedef struct
{
  uint32_t xorout;
  uint32_t refout;
  uint32_t refin;
  uint32_t byte;
  uint32_t mode;  
  uint32_t req;
  uint32_t ds;
  uint32_t rst;  
} md_crc_init_typedef; 
/**
  * @} MD_CRC_INIT
  */

/* Public Constants -----------------------------------------------------------*/
/** @defgroup MD_CRC_Public_Constants CRC Public Constants
  * @brief
  * @{
  */

/** @defgroup MD_CRC_CON_registers CRC Control Registers
  * @brief
  * @{
  */
#define MD_CRC_CON_DMA_ON       1         /*!<  This allow user to enable DMA function.                             */
#define MD_CRC_CON_DMA_OFF      0         /*!<  This allow user to disable DMA function.                            */
#define MD_CRC_CON_MSB_ON       1         /*!<  User can set this bit to change the 'byte' order of input data.     */
#define MD_CRC_CON_MSB_OFF      1         /*!<  User can set this bit to change the 'byte' order of input data.     */
#define MD_CRC_CON_REOUT        0         /*!<  This allow user to reverse the order of CRC output data.            */
#define MD_CRC_CON_REOUT_REV    1         /*!<  This allow user to reverse the order of CRC output data.            */
#define MD_CRC_CON_REIN         0         /*!<  This allow user to reverse the order of CRC input data.             */
#define MD_CRC_CON_REIN_REV     1         /*!<  This allow user to reverse the order of CRC input data.             */
#define MD_CRC_CON_SIZE_POLY32  0         /*!<  This allow user to select polynomial size.                          */
#define MD_CRC_CON_SIZE_POLY16  1         /*!<  This allow user to select polynomial size.                          */
#define MD_CRC_CON_SIZE_POLY8   2         /*!<  This allow user to select polynomial size.                          */
#define MD_CRC_CON_MODE_COMP_DISABLE   0  /*!<  This allow user to check CRC result.                                */
#define MD_CRC_CON_MODE_COMP_ZERO      1  /*!<  This allow user to check CRC result.                                */
#define MD_CRC_CON_MODE_COMP_ENABLE    2  /*!<  This allow user to check CRC result.                                */
#define MD_CRC_CON_RESET  1               /*!<  User can set this bit to reset CRC function.                        */
/**
  * @} MD_CRC_CON_registers
  */
  
/** @defgroup MD_CRC_STAT_registers CRC Status Registers
  * @brief
  * @{
  */
#define MD_CRC_STAT_FAIL        1         /*!<  This bit is set when CRC result is not correct.         */
#define MD_CRC_STAT_EMPTY       1         /*!<  This bit is cleaned after an CRC calculation.           */
#define MD_CRC_STAT_BUSY        1         /*!<  This bit is set when CRC module is calculating result.  */
#define MD_CRC_STAT_DONE        1         /*!<  This bit is set when CRC calculation is finish.         */
/**
  * @} MD_CRC_STAT_registers
  */
  
/**
  * @} MD_CRC_Public_Constants
  */

/* Public Macros --------------------------------------------------------------*/
/** @defgroup MD_CRC_Public_Macros CRC Public Macros
  * @brief
  * @{
  */

/**
  * @brief  This register is used to write the CRC initial data. 
  * @param  CRC Instance
  * @param  value This parameter can be one of the following values:
  *         @arg Minimum 0x00000000
  *         @arg Maximum 0xFFFFFFFF
  * @retval None.
  */
__STATIC_INLINE void md_crc_set_init(CRC_TypeDef *crc, uint32_t value)
{
  WRITE_REG(crc->INIT, value);
}

/**
  * @brief  This register is used to read the CRC initial data.
  * @param  CRC Instance
  * @retval value 0x00000000 ~ 0xffffffff.
  */
__STATIC_INLINE uint32_t md_crc_get_init(CRC_TypeDef *crc)
{
  return (READ_REG(crc->INIT));
}

/**
  * @brief  This register is used to write the coefficient of the CRC polynomial. Default coefficient is for CRC32.
  * @param  CRC Instance
  * @param  value This parameter can be one of the following values:
  *         @arg Minimum 0x00000000
  *         @arg Maximum 0xFFFFFFFF
  * @retval None.
  */
__STATIC_INLINE void md_crc_set_poly(CRC_TypeDef *crc, uint32_t value)
{
  WRITE_REG(crc->POLY, value);
}

/**
  * @brief  This register is used to read the coefficient of the CRC polynomial. Default coefficient is for CRC32.
  * @param  CRC Instance
  * @retval value 0x00000000 ~ 0xffffffff.
  */
__STATIC_INLINE uint32_t md_crc_get_poly(CRC_TypeDef *crc)
{
  return (READ_REG(crc->POLY));
}

/**
  * @brief  This register is used to write the CRC input data. CRC will start to calculate result after this register is written.
  * @param  CRC Instance
  * @param  value This parameter can be one of the following values:
  *         @arg Minimum 0x00000000
  *         @arg Maximum 0xFFFFFFFF
  * @retval None.
  */
__STATIC_INLINE void md_crc_set_data(CRC_TypeDef *crc, uint32_t value)
{
  WRITE_REG(crc->DATA, value);
}

/**
  * @brief  This register is used to read the CRC input data. CRC will start to calculate result after this register is written.
  * @param  CRC Instance
  * @retval value 0x00000000 ~ 0xffffffff.
  */
__STATIC_INLINE uint32_t md_crc_get_data(CRC_TypeDef *crc)
{
  return (READ_REG(crc->DATA));
}

/**
  * @brief  This register is used to compare with the CRC output data.
  * @param  CRC Instance
  * @param  value This parameter can be one of the following values:
  *         @arg Minimum 0x00000000
  *         @arg Maximum 0xFFFFFFFF
  * @retval None.
  */
__STATIC_INLINE void md_crc_set_comp(CRC_TypeDef *crc, uint32_t value)
{
  WRITE_REG(crc->COMP, value);
}

/**
  * @brief  This register is used to compare with the CRC output data.
  * @param  CRC Instance
  * @retval value 0x00000000 ~ 0xffffffff.
  */
__STATIC_INLINE uint32_t md_crc_get_comp(CRC_TypeDef *crc)
{
  return (READ_REG(crc->COMP));
}

/**
  * @brief  This register is used to set a parameter to do exclusive OR with CRC output data.
  * @param  CRC Instance
  * @param  value This parameter can be one of the following values:
  *         @arg Minimum 0x00000000
  *         @arg Maximum 0xFFFFFFFF
  * @retval None.
  */
__STATIC_INLINE void md_crc_set_rema(CRC_TypeDef *crc, uint32_t value)
{
  WRITE_REG(crc->REMA, value);
}

/**
  * @brief  This register is used to set a parameter to do exclusive OR with CRC output data.
  * @param  CRC Instance
  * @retval value 0x00000000 ~ 0xffffffff.
  */
__STATIC_INLINE uint32_t md_crc_get_rema(CRC_TypeDef *crc)
{
  return (READ_REG(crc->REMA));
}

/**
  * @brief  This register is used to set a parameter.
  * @param  CRC Instance
  * @param  value This parameter can be one of the following values:
  *         @arg @ref MD_CRC_CON_DMA_ON            1  
  *         @arg @ref MD_CRC_CON_DMA_OFF           0 
  *         @arg @ref MD_CRC_CON_MSB_ON            1 
  *         @arg @ref MD_CRC_CON_MSB_OFF           0  
  *         @arg @ref MD_CRC_CON_REOUT             0            
  *         @arg @ref MD_CRC_CON_REOUT_REV         1        
  *         @arg @ref MD_CRC_CON_REIN              0             
  *         @arg @ref MD_CRC_CON_REIN_REV          1         
  *         @arg @ref MD_CRC_CON_SIZE_POLY32       0      
  *         @arg @ref MD_CRC_CON_SIZE_POLY16       1      
  *         @arg @ref MD_CRC_CON_SIZE_POLY8        2       
  *         @arg @ref MD_CRC_CON_MODE_COMP_DISABLE 0 
  *         @arg @ref MD_CRC_CON_MODE_COMP_ZERO    1    
  *         @arg @ref MD_CRC_CON_MODE_COMP_ENABLE  2  
  *         @arg @ref MD_CRC_CON_RESET             1            
  * @retval None.
  */
__STATIC_INLINE void md_crc_set_con(CRC_TypeDef *crc, uint32_t value)
{
  WRITE_REG(crc->CON, value);
}

/**
  * @brief  This register is used to get a parameter.
  * @param  CRC Instance
  * @retval value 0x00000000 ~ 0xffffffff.
  */
__STATIC_INLINE uint32_t md_crc_get_con(CRC_TypeDef *crc)
{
  return (READ_REG(crc->CON));
}

/**
  * @brief  This function allow user to enable DMA function.
  * @param  CRC Instance
  * @param  value This parameter can be one of the following values:
  *         @arg @ref MD_CRC_CON_DMA_ON            1  
  *         @arg @ref MD_CRC_CON_DMA_OFF           0 
  * @retval None.
  */
__STATIC_INLINE void md_crc_set_con_dma(CRC_TypeDef *crc, uint32_t value)
{
  MODIFY_REG(crc->CON, CRC_CON_DMA_MSK, value << CRC_CON_DMA_POS);
}

/**
  * @brief  This function allow user to enable DMA function. 
  * @param  CRC Instance
  * @retval value 0: disable, 1: enable.
  */
__STATIC_INLINE uint32_t md_crc_get_con_dma(CRC_TypeDef *crc)
{
  return ((READ_BIT(crc->CON, CRC_CON_DMA_MSK) >> CRC_CON_DMA_POS) & 0x1);
}

/**
  * @brief  User can set this bit to change the 'byte' order of input data.
  * @param  CRC Instance
  * @param  value This parameter can be one of the following values:
  *         @arg @ref MD_CRC_CON_MSB_ON            1 
  *         @arg @ref MD_CRC_CON_MSB_OFF           0 
  * @retval None.
  */
__STATIC_INLINE void md_crc_set_con_msb(CRC_TypeDef *crc, uint32_t value)
{
  MODIFY_REG(crc->CON, CRC_CON_MSB_MSK, value << CRC_CON_MSB_POS);
}

/**
  * @brief  User can set this bit to change the 'byte' order of input data. 
  * @param  CRC Instance
  * @retval value 0: disable, 1: enable.
  */
__STATIC_INLINE uint32_t md_crc_get_con_msb(CRC_TypeDef *crc)
{
  return ((READ_BIT(crc->CON, CRC_CON_MSB_MSK) >> CRC_CON_MSB_POS) & 0x1);
}

/**
  * @brief  This function allow user to reverse the order of CRC output data.
  * @param  CRC Instance
  * @param  value This parameter can be one of the following values:
  *         @arg @reg MD_CRC_CON_REOUT        0         
  *         @arg @reg MD_CRC_CON_REOUT_REV    1         
  * @retval None.
  */
__STATIC_INLINE void md_crc_set_con_reout(CRC_TypeDef *crc, uint32_t value)
{
  MODIFY_REG(crc->CON, CRC_CON_REOUT_MSK, value << CRC_CON_REOUT_POS);
}

/**
  * @brief  This function allow user to reverse the order of CRC output data.
  * @param  CRC Instance
  * @retval value 0: Disable reverse operation, 1: Reverse output data.
  */
__STATIC_INLINE uint32_t md_crc_get_con_reout(CRC_TypeDef *crc)
{
  return ((READ_BIT(crc->CON, CRC_CON_REOUT_MSK) >> CRC_CON_REOUT_POS) & 0x1);
}

/**
  * @brief  This function allow user to reverse the order of CRC input data.
  * @param  CRC Instance
  * @param  value This parameter can be one of the following values:
  *         @arg @reg MD_CRC_CON_REIN        0         
  *         @arg @reg MD_CRC_CON_REIN_REV    1         
  * @retval None.
  */
__STATIC_INLINE void md_crc_set_con_rein(CRC_TypeDef *crc, uint32_t value)
{
  MODIFY_REG(crc->CON, CRC_CON_REIN_MSK, value << CRC_CON_REIN_POS);
}

/**
  * @brief  User can set this bit to change the 'byte' order of input data. 
  * @param  CRC Instance
  * @retval value 0: Disable reverse operation, 1: Bit reversal done by byte.
  */
__STATIC_INLINE uint32_t md_crc_get_con_rein(CRC_TypeDef *crc)
{
  return ((READ_BIT(crc->CON, CRC_CON_REIN_MSK) >> CRC_CON_REIN_POS) & 0x1);
}

/**
  * @brief  User can set this bit to change the 'byte' order of input data.
  * @param  CRC Instance
  * @param  value This parameter can be one of the following values:
  *         @arg @ref MD_CRC_CON_SIZE_POLY32       0      
  *         @arg @ref MD_CRC_CON_SIZE_POLY16       1      
  *         @arg @ref MD_CRC_CON_SIZE_POLY8        2         
  * @retval None.
  */
__STATIC_INLINE void md_crc_set_con_size(CRC_TypeDef *crc, uint32_t value)
{
  MODIFY_REG(crc->CON, CRC_CON_SIZE_MSK, value << CRC_CON_SIZE_POSS);
}

/**
  * @brief  User can set this bit to change the 'byte' order of input data. 
  * @param  CRC Instance
  * @retval value 00: 32 bit polynomial, 01: 16 bit polynomial, 10: 8 bit polynomial.
  */
__STATIC_INLINE uint32_t md_crc_get_con_size(CRC_TypeDef *crc)
{
  return ((READ_BIT(crc->CON, CRC_CON_SIZE_MSK) >> CRC_CON_SIZE_POSS) & 0x3);
}

/**
  * @brief  This function allow user to check CRC result. If CRC result is not correct, the status “FAIL” in CRC_STA will be set to 1.
  * @param  CRC Instance
  * @param  value This parameter can be one of the following values:
  *         @arg @ref MD_CRC_CON_MODE_COMP_DISABLE   0
  *         @arg @ref MD_CRC_CON_MODE_COMP_ZERO      1
  *         @arg @ref MD_CRC_CON_MODE_COMP_ENABLE    2     
  * @retval None.
  */
__STATIC_INLINE void md_crc_set_con_mode(CRC_TypeDef *crc, uint32_t value)
{
  MODIFY_REG(crc->CON, CRC_CON_MODE_MSK, value << CRC_CON_MODE_POSS);
}

/**
  * @brief  This function allow user to check CRC result. If CRC result is not correct, the status “FAIL” in CRC_STA will be set to 1. 
  * @param  CRC Instance
  * @retval value 00: Disable compare function, 01: Compare CRC result with 32’h0000_0000, 10: Compare CRC result with CRC_COMP.
  */
__STATIC_INLINE uint32_t md_crc_get_con_mode(CRC_TypeDef *crc)
{
  return ((READ_BIT(crc->CON, CRC_CON_MODE_MSK) >> CRC_CON_MODE_POSS) & 0x3);
}

/**
  * @brief  User can set this bit to reset CRC function. This bit will be cleared by itself.
  * @param  CRC Instance
  * @param  value This parameter can be one of the following values:
  *         @arg @ref MD_CRC_CON_RESET  1   
  * @retval None.
  */
__STATIC_INLINE void md_crc_set_con_reset(CRC_TypeDef *crc, uint32_t value)
{
  MODIFY_REG(crc->CON, CRC_CON_RESET_MSK, value << CRC_CON_RESET_POS);
}

/**
  * @brief  User can set this bit to reset CRC function. This bit will be cleared by itself.
  * @param  CRC Instance
  * @retval value 0.
  */
__STATIC_INLINE uint32_t md_crc_get_con_reset(CRC_TypeDef *crc)
{
  return ((READ_BIT(crc->CON, CRC_CON_RESET_MSK) >> CRC_CON_RESET_POS) & 0x1);
}

/**
  * @brief  This register is used to show the CRC calculation result.
  * @param  CRC Instance
  * @retval value: 0x00000000 ~ 0xffffffff.
  */
__STATIC_INLINE uint32_t md_crc_get_dout(CRC_TypeDef *crc)
{
  return (READ_REG(crc->DOUT));
}

/**
  * @brief  This register is used to show the CRC calculation exculsive OR result.
  * @param  CRC Instance
  * @retval value: 0x00000000 ~ 0xffffffff.
  */
__STATIC_INLINE uint32_t md_crc_get_dout_xor(CRC_TypeDef *crc)
{
  return (READ_REG(crc->DOUT_XOR));
}

/**
  * @brief  This register is used to show the CRC calculation exculsive OR result.
  * @param  CRC Instance
  * @retval value: 0x00000000 ~ 0xffffffff.
  */
__STATIC_INLINE uint32_t md_crc_get_stat(CRC_TypeDef *crc)
{
  return (READ_REG(crc->STAT));
}

/**
  * @brief  This bit is set when CRC result is not correct.
  * @param  CRC Instance
  * @retval value: 1 = FAIL, 0 = PASS.
            @arg @ref MD_CRC_STAT_FAIL 1
  */
__STATIC_INLINE uint32_t md_crc_get_stat_fail(CRC_TypeDef *crc)
{
  return ((READ_BIT(crc->STAT, CRC_STAT_FAIL_MSK) >> CRC_STAT_FAIL_POS) & 0x1);
}

/**
  * @brief  This bit is cleaned after an CRC calculation.
  * @param  CRC Instance
  * @retval value: 1 = FAIL, 0 = PASS.
            @arg @ref MD_CRC_STAT_EMPTY 1
  */
__STATIC_INLINE uint32_t md_crc_get_stat_empty(CRC_TypeDef *crc)
{
  return ((READ_BIT(crc->STAT, CRC_STAT_EMPTY_MSK) >> CRC_STAT_EMPTY_POS) & 0x1);
}

/**
  * @brief  This bit is set when CRC module is calculating result.
  * @param  CRC Instance
  * @retval value: 1 = FAIL, 0 = PASS.
            @arg @ref MD_CRC_STAT_BUSY 1
  */
__STATIC_INLINE uint32_t md_crc_get_stat_busy(CRC_TypeDef *crc)
{
  return ((READ_BIT(crc->STAT, CRC_STAT_BUSY_MSK) >> CRC_STAT_BUSY_POS) & 0x1);
}

/**
  * @brief  This bit is set when CRC module is calculating result.
  * @param  CRC Instance
  * @retval value: 1 = FAIL, 0 = PASS.
            @arg @ref MD_CRC_STAT_DONE 1
  */
__STATIC_INLINE uint32_t md_crc_get_stat_done(CRC_TypeDef *crc)
{
  return (READ_BIT(crc->STAT, CRC_STAT_DONE_MSK) >> CRC_STAT_DONE_POS);
}

/**
  * @} MD_CRC_Public_Macros
  */

/**
  * @} CRC
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
