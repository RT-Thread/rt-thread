/**
  ******************************************************************************
  * @file    md_CMP.h
  * @brief   ES32F0271 CMP Head File.
  *
  * @version V1.00.01
  * @date    11/23/2018
  * @author  Eastsoft AE Team
  * @note
  * detailed description
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *******************************************************************************
  */
  
  /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MD_CMP_H__
#define __MD_CMP_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -------------------------------------------------------------------*/
#include "es32f0271.h"
#include "reg_cmp.h"

/** @addtogroup Micro_Driver
  * @{
  */

#if defined (CMP)
/** @defgroup CMP CMP
  * @brief CMP micro driver
  * @{
  */


/* Private types --------------------------------------------------------------*/
/* Private variables ----------------------------------------------------------*/
/* Private constants ----------------------------------------------------------*/
/* Private macros -------------------------------------------------------------*/
/* Public types ---------------------------------------------------------------*/
/* Public constants -----------------------------------------------------------*/

/** @defgroup MD_CMP_Public_Constants CMP Public Constants
  * @{
  */
  
/** @defgroup MD_CMP_PC_CARS CMP Reference voltage
  * @{
  */
#define MD_CMP_CARS_1_25V                 (0x00000000UL)       /*!< @brief Select CARS for 0.25*5V */
#define MD_CMP_CARS_2_50V                  (0x00000001UL)       /*!< @brief Select CARS for 0.5*5V */
#define MD_CMP_CARS_3_75V                 (0x00000002UL)       /*!< @brief Select CARS for 0.75*5V */
#define MD_CMP_CARS_5_00V                  (0x00000003UL)       /*!< @brief Select CARS for 5V */

/**  
  * @} MD_CMP_PC_CARS 
  */

  
/**  
  * @} MD_CMP_Public_Constants 
  */

/* Public macro ---------------------------------------------------------------*/
/** @defgroup MD_CMP_Public_Macros CMP Public Macros
  * @{
  */

/** @defgroup MD_CMP_PF_CON CMP Control Register
  * @{
  */
/**
  * @brief  Set CMP control register (CMP_CON)
  * @param  cmp CMP Instance 
  * @param  value The value write in CMP_CON
  * @retval None
  */
__STATIC_INLINE void md_cmp_set_con(CMP_TypeDef *cmp, uint32_t value)
{
  WRITE_REG(cmp->CON, value);
}

/**
  * @brief  Get CMP control register (CMP_CON)
  * @param  cmp CMP Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_cmp_get_con(CMP_TypeDef *cmp)
{
  return (uint32_t)(READ_REG(cmp->CON));
}

/**
  * @brief  Enable Comparator 1 enable set
  * @param  cmp CMP Instance
  * @retval None
  */
__STATIC_INLINE void md_cmp_enable_con_cmpon1(CMP_TypeDef *cmp)
{
  SET_BIT(cmp->CON, CMP_CON_CMPON1_MSK);
}
/**
  * @brief  Disable Comparator 1 enable set
  * @param  cmp CMP Instance
  * @retval None
  */
__STATIC_INLINE void md_cmp_disable_con_cmpon1(CMP_TypeDef *cmp)
{
  CLEAR_BIT(cmp->CON, CMP_CON_CMPON1_MSK);
}

/**
  * @brief  Check if Comparator 1 enable set is enable
  * @param  cmp CMP Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_cmp_is_enable_con_cmpon1(CMP_TypeDef *cmp)
{
  return (READ_BIT(cmp->CON, CMP_CON_CMPON1_MSK));
}

/**
  * @brief  Enable Comparator 2 enable set
  * @param  cmp CMP Instance
  * @retval None
  */
__STATIC_INLINE void md_cmp_enable_con_cmpon2(CMP_TypeDef *cmp)
{
  SET_BIT(cmp->CON, CMP_CON_CMPON2_MSK);
}
/**
  * @brief  Disable Comparator 2 enable set
  * @param  cmp CMP Instance
  * @retval None
  */
__STATIC_INLINE void md_cmp_disable_con_cmpon2(CMP_TypeDef *cmp)
{
  CLEAR_BIT(cmp->CON, CMP_CON_CMPON2_MSK);
}

/**
  * @brief  Check if Comparator 2 enable set is enable
  * @param  cmp CMP Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_cmp_is_enable_con_caon2(CMP_TypeDef *cmp)
{
  return (READ_BIT(cmp->CON, CMP_CON_CMPON2_MSK));
}

/**
  * @} MD_CMP_PF_CON
  */


/** @defgroup MD_CMP_PF_Configuration CMP Configuration Manangement
  * @{
  */


/**
  * @brief  Set CMP control register 1(CMP_CFG1)
  * @param  cmp CMP Instance 
  * @param  value The value write in CMP_CFG1
  * @retval None
  */
__STATIC_INLINE void md_cmp_set_cfg1(CMP_TypeDef *cmp, uint32_t value)
{
  WRITE_REG(cmp->CFG1, value);
}
/**
  * @brief  Get CMP control register 1(CMP_CFG1)
  * @param  cmp CMP Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_cmp_get_cfg1(CMP_TypeDef *cmp)
{
  return (uint32_t)(READ_REG(cmp->CFG1));
}


/**
  * @brief  Set Comparator 1 reference voltage selection.
  * @param  cmp CMP Instance
  * @param  RefVol This parameter can be one of the following values:
  *         @arg MD_CMP_CARS_1_25V
  *         @arg MD_CMP_CARS_2_50V
  *         @arg MD_CMP_CARS_3_75V
  *         @arg MD_CMP_CARS_5_00V
  * @retval None
  */
__STATIC_INLINE void md_cmp_set_cfg1_rs(CMP_TypeDef *cmp, uint32_t RefVol)
{
  MODIFY_REG(cmp->CFG1, CMP_CFG1_RS_MSK, RefVol<<CMP_CFG1_RS_POSS);
}

/**
  * @brief  Return Comparator 1 reference voltage
  * @param  cmp CMP Instance
  * @retval None
  *         @arg MD_CMP_CARS_1_25V
  *         @arg MD_CMP_CARS_2_50V
  *         @arg MD_CMP_CARS_3_75V
  *         @arg MD_CMP_CARS_5_00V
  */
__STATIC_INLINE uint32_t md_cmp_get_cfg1_rs(CMP_TypeDef *cmp)
{
  return (uint32_t)(READ_BIT(cmp->CFG1, CMP_CFG1_RS_MSK) >> CMP_CFG1_RS_POSS);
}


/**
  * @brief  Enable Comparator 1 Filter circuit 
  * @param  cmp CMP Instance
  * @retval None
  */
__STATIC_INLINE void md_cmp_enable_cfg1_fen(CMP_TypeDef *cmp)
{
  SET_BIT(cmp->CFG1, CMP_CFG1_FEN_MSK);
}
/**
  * @brief  Disable Comparator 1 Filter circuit 
  * @param  cmp CMP Instance
  * @retval None
  */
__STATIC_INLINE void md_cmp_disable_cfg1_fen(CMP_TypeDef *cmp)
{
  CLEAR_BIT(cmp->CFG1, CMP_CFG1_FEN_MSK);
}

/**
  * @brief  Check if Comparator 1 Filter circuit is enable 
  * @param  cmp CMP Instance
  * @retval None
  */
__STATIC_INLINE uint32_t md_cmp_is_enable_cfg1_fen(CMP_TypeDef *cmp)
{
  return (READ_BIT(cmp->CFG1, CMP_CFG1_FEN_MSK) == (CMP_CFG1_FEN_MSK));
}


/**
  * @brief  Enable comparator 1 reverse circuit enable
  * @param  cmp CMP Instance
  * @retval None
  */
__STATIC_INLINE void md_cmp_enable_cfg1_psen(CMP_TypeDef *cmp)
{
  SET_BIT(cmp->CFG1, CMP_CFG1_PSEN_MSK);
}
/**
  * @brief  Disable comparator 1 reverse circuit enable
  * @param  cmp CMP Instance
  * @retval None
  */
__STATIC_INLINE void md_cmp_disable_cfg1_psen(CMP_TypeDef *cmp)
{
  CLEAR_BIT(cmp->CFG1, CMP_CFG1_PSEN_MSK);
}

/**
  * @brief  Check if comparator 1 reverse circuit enable is enable 
  * @param  cmp CMP Instance
  * @retval None
  */
__STATIC_INLINE uint32_t md_cmp_is_enable_cfg1_capsen(CMP_TypeDef *cmp)
{
  return (READ_BIT(cmp->CFG1, CMP_CFG1_PSEN_MSK) == (CMP_CFG1_PSEN_MSK) );
}


/**
  * @brief  Enable Comparator 1 Negative input select 
  * @param  cmp CMP Instance
  * @retval None
  */
__STATIC_INLINE void md_cmp_enable_cfg1_insel(CMP_TypeDef *cmp)
{
  SET_BIT(cmp->CFG1, CMP_CFG1_INSEL_MSK);
}
/**
  * @brief  Disable Comparator 1 Negative input select 
  * @param  cmp CMP Instance
  * @retval None
  */
__STATIC_INLINE void md_cmp_disable_cfg1_insel(CMP_TypeDef *cmp)
{
   CLEAR_BIT(cmp->CFG1, CMP_CFG1_INSEL_MSK);
}

/**
  * @brief  Check if comparator 1 Negative input select is enable 
  * @param  cmp CMP Instance
  * @retval None
  */
__STATIC_INLINE uint32_t md_cmp_is_enable_cfg1_insel(CMP_TypeDef *cmp)
{
  return (READ_BIT(cmp->CFG1, CMP_CFG1_INSEL_MSK) == (CMP_CFG1_INSEL_MSK));
}


/**
  * @brief  Enable comparator 1 Positive input select
  * @param  cmp CMP Instance
  * @retval None
  */
__STATIC_INLINE void md_cmp_enable_cfg1_ipsel(CMP_TypeDef *cmp)
{
  SET_BIT(cmp->CFG1, CMP_CFG1_IPSEL_MSK);
}
/**
  * @brief  Disable comparator 1 Positive input select
  * @param  cmp CMP Instance
  * @retval None
  */
__STATIC_INLINE void md_cmp_disable_cfg1_ipsel(CMP_TypeDef *cmp)
{
  CLEAR_BIT(cmp->CFG1, CMP_CFG1_IPSEL_MSK);
}

/**
  * @brief  Check if comparator 1 Positive input select is enable 
  * @param  cmp CMP Instance
  * @retval None
  */
__STATIC_INLINE uint32_t md_cmp_is_enable_cfg1_ipsel(CMP_TypeDef *cmp)
{
  return (READ_BIT(cmp->CFG1, CMP_CFG1_IPSEL_MSK) == (CMP_CFG1_IPSEL_MSK));
}


/**
  * @brief  Set CMP control register 2(CMP_CFG2)
  * @param  cmp CMP Instance 
  * @param  value The value write in CMP_CFG2
  * @retval None
  */
__STATIC_INLINE void md_cmp_set_cfg2(CMP_TypeDef *cmp, uint32_t value)
{
  WRITE_REG(cmp->CFG2, value);
}
/**
  * @brief  Get CMP control register 2(CMP_CFG2)
  * @param  cmp CMP Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_cmp_get_cfg2(CMP_TypeDef *cmp)
{
  return (uint32_t)(READ_REG(cmp->CFG2));
}


/**
  * @brief  Set Comparator 2 reference voltage selection.
  * @param  cmp CMP Instance
  * @param  RefVol This parameter can be one of the following values:
  *         @arg MD_CMP_CARS_1_25V
  *         @arg MD_CMP_CARS_2_50V
  *         @arg MD_CMP_CARS_3_75V
  *         @arg MD_CMP_CARS_5_00V
  * @retval None
  */
__STATIC_INLINE void md_cmp_set_cfg2_rs(CMP_TypeDef *cmp, uint32_t RefVol)
{
  MODIFY_REG(cmp->CFG2, CMP_CFG2_RS_MSK, RefVol << CMP_CFG2_RS_POSS);
}

/**
  * @brief  Return Comparator 2 reference voltage
  * @param  cmp CMP Instance
  * @retval None
  *         @arg MD_CMP_CARS_1_25V
  *         @arg MD_CMP_CARS_2_50V
  *         @arg MD_CMP_CARS_3_75V
  *         @arg MD_CMP_CARS_5_00V
  */
__STATIC_INLINE uint32_t md_cmp_get_cfg2_rs(CMP_TypeDef *cmp)
{
  return (uint32_t)(READ_BIT(cmp->CFG2, CMP_CFG2_RS_MSK) >> CMP_CFG2_RS_POSS);
}


/**
  * @brief  Enable Comparator 2 Filter circuit 
  * @param  cmp CMP Instance
  * @retval None
  */
__STATIC_INLINE void md_cmp_enable_cfg2_fen(CMP_TypeDef *cmp)
{
  SET_BIT(cmp->CFG2, CMP_CFG2_FEN_MSK);
}
/**
  * @brief  Disable Comparator 2 Filter circuit 
  * @param  cmp CMP Instance
  * @retval None
  */
__STATIC_INLINE void md_cmp_disable_cfg2_fen(CMP_TypeDef *cmp)
{
  CLEAR_BIT(cmp->CFG2, CMP_CFG2_FEN_MSK);
}

/**
  * @brief  Check if Comparator 2 Filter circuit is enable 
  * @param  cmp CMP Instance
  * @retval None
  */
__STATIC_INLINE uint32_t md_cmp_is_enable_cfg2_fen(CMP_TypeDef *cmp)
{
  return (READ_BIT(cmp->CFG2, CMP_CFG2_FEN_MSK) == (CMP_CFG2_FEN_MSK)) ;
}


/**
  * @brief  Enable comparator 2 reverse circuit enable
  * @param  cmp CMP Instance
  * @retval None
  */
__STATIC_INLINE void md_cmp_enable_cfg2_psen(CMP_TypeDef *cmp)
{
  SET_BIT(cmp->CFG2, CMP_CFG2_PSEN_MSK);
}
/**
  * @brief  Disable comparator 2 reverse circuit enable
  * @param  cmp CMP Instance
  * @retval None
  */
__STATIC_INLINE void md_cmp_disable_cfg2_psen(CMP_TypeDef *cmp)
{
  CLEAR_BIT(cmp->CFG2, CMP_CFG2_PSEN_MSK);
}

/**
  * @brief  Check if comparator 2 reverse circuit enable is enable 
  * @param  cmp CMP Instance
  * @retval None
  */
__STATIC_INLINE uint32_t md_cmp_is_enable_cfg2_psen(CMP_TypeDef *cmp)
{
  return (READ_BIT(cmp->CFG2, CMP_CFG2_PSEN_MSK) == (CMP_CFG2_PSEN_MSK));
}


/**
  * @brief  Enable Comparator 2 Negative input select 
  * @param  cmp CMP Instance
  * @retval None
  */
__STATIC_INLINE void md_cmp_enable_cfg2_insel(CMP_TypeDef *cmp)
{
  SET_BIT(cmp->CFG2, CMP_CFG2_INSEL_MSK);
}
/**
  * @brief  Disable Comparator 2 Negative input select 
  * @param  cmp CMP Instance
  * @retval None
  */
__STATIC_INLINE void md_cmp_disable_cfg2_insel(CMP_TypeDef *cmp)
{
   CLEAR_BIT(cmp->CFG2, CMP_CFG2_INSEL_MSK);
}

/**
  * @brief  Check if comparator 2 Negative input select is enable 
  * @param  cmp CMP Instance
  * @retval None
  */
__STATIC_INLINE uint32_t md_cmp_is_enable_cfg2_insel(CMP_TypeDef *cmp)
{
  return (READ_BIT(cmp->CFG2, CMP_CFG2_INSEL_MSK) == (CMP_CFG2_INSEL_MSK));
}


/**
  * @brief  Enable comparator 2 Positive input select
  * @param  cmp CMP Instance
  * @retval None
  */
__STATIC_INLINE void md_cmp_enable_cfg2_ipsel(CMP_TypeDef *cmp)
{
  SET_BIT(cmp->CFG2, CMP_CFG2_IPSEL_MSK);
}
/**
  * @brief  Disable comparator 2 Positive input select
  * @param  cmp CMP Instance
  * @retval None
  */
__STATIC_INLINE void md_cmp_disable_cfg2_ipsel(CMP_TypeDef *cmp)
{
  CLEAR_BIT(cmp->CFG2, CMP_CFG2_IPSEL_MSK);
}

/**
  * @brief  Check if comparator 2 Positive input select is enable 
  * @param  cmp CMP Instance
  * @retval None
  */
__STATIC_INLINE uint32_t md_cmp_is_enable_cfg2_ipsel(CMP_TypeDef *cmp)
{
  return (READ_BIT(cmp->CFG2, CMP_CFG2_IPSEL_MSK) == (CMP_CFG2_IPSEL_MSK));
}


/**
  * @} MD_CMP_PF_Configuration
  */

/** @defgroup MD_CMP_PC_RULT CMP Comparator Output Register.
  * @{
  */

/**
  * @brief  Return Comparator output result(CMP_RULT)
  * @param  cmp CMP Instance
  * @retval The state of 1 or 0
  */
__STATIC_INLINE uint32_t md_cmp_get_rult(CMP_TypeDef *cmp)
{
  return (uint32_t)(READ_REG(cmp->RULT));
}

/**
  * @brief  Return Comparator 1 output result
  * @param  cmp CMP Instance
  * @retval The state of 1 or 0
  */
__STATIC_INLINE uint32_t md_cmp_get_rult_cmpo1(CMP_TypeDef *cmp)
{
  return (uint32_t)(READ_BIT(cmp->RULT, CMP_RULT_CMPO1_MSK));
}
/**
  * @brief  Return Comparator 2 output result
  * @param  cmp CMP Instance
  * @retval The state of 1 or 0
  */
__STATIC_INLINE uint32_t md_cmp_get_rult_cmpo2(CMP_TypeDef *cmp)
{
  return (uint32_t)(READ_BIT(cmp->RULT, CMP_RULT_CMPO2_MSK));
}


/**
  * @} MD_CMP_PC_RULT
  */


/**
  * @} MD_CMP_Public_Macros
  */

/* Public functions -----------------------------------------------------------*/

/**
  * @} CMP
  */

#endif


/**
  * @} Micro_Driver
  */

#endif

#ifdef __cplusplus
}
#endif


/******************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
