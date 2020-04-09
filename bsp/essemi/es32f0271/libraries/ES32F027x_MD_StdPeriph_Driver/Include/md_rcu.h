/**
  ******************************************************************************
  * @file    md_RCU.h
  * @brief   ES32F0271 RCU HEAD File.
  *
  * @version V1.00.02
  * @date    30/11/2018
  * @author  Eastsoft AE Team
  * @note
  * detailed description
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MD_RCU_H__
#define __MD_RCU_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -------------------------------------------------------------------*/ 
#include <stdbool.h>
#include "es32f0271.h"
#include "reg_rcu.h"

/** @addtogroup Micro_Driver
  * @{
  */

#if defined (RCU)

/** @defgroup RCU RCU
  * @brief RCU micro driver
  * @{
  */
  
/* Private types --------------------------------------------------------------*/
/* Private variables ----------------------------------------------------------*/
/* Private constants ----------------------------------------------------------*/
/** @defgroup MD_RCU_Private_Constants RCU Private Constants
  * @{
  */

#define __HOSC      (8000000UL)
#define __HRC       (4000000UL)
#define __LOSC      (  32768UL)
#define __LRC       (  32000UL)
#define __PLL1      (48000000UL)

/**
  * @} MD_RCU_Private_Constants
  */
/* Private macros -------------------------------------------------------------*/
/* Public types ---------------------------------------------------------------*/
/* Public types ---------------------------------------------------------------*/
/** @defgroup MD_RCU_Public_Types RCU Public Init Type
  * @{
  */

typedef struct
{
  uint32_t  Mpre;    /*! MCO clock prescaler  */
  uint32_t  Msw;     /*! MCO clock output  */
  uint32_t  PllMul;  /*! PLL multiplication factor  */
  uint32_t  PllSrc;  /*! PLL clock source  */
  uint32_t  HoscDiv; /*! PLL base clock 4MHz HOSC clock prescale  */
  uint32_t  Ppre;    /*! APB clock prescaler  */
  uint32_t  Hpre;    /*! AHB clock prescaler  */
  uint32_t  Sw;      /*! system clock   */
  uint8_t   SysClock;/*! system clock enable  */  
} md_rcu_init_typedef;

/**
  * @} MD_RCU_Public_Types
  */
/* Public constants -----------------------------------------------------------*/
/** @defgroup MD_RCU_Public_Constants RCU Public Constants
  * @{
  */

/** @defgroup MD_RCU_SWRDY_FLAG System clock switch ready flag
  * @{
  */
#define MD_RCU_SWRDY_NOT_READY  (0x00000000UL)  /** @brief System clock not ready */
#define MD_RCU_SWRDY_READY      (0x00000001UL)  /** @brief System clock ready */
/**
  * @} MD_RCU_SWRDY_FLAG
  */

/** @defgroup MD_RCU_CSSFLG_FLAG Clock Security System flag
  * @{
  */
#define MD_RCU_CSSFLG_NO_FAIL   (0x00000000UL)  /** @brief No clock security event caused by HOSC clock failure */
#define MD_RCU_CSSFLG_FAIL      (0x00000001UL)  /** @brief Clock security event caused by HOSC clock failure */
/**
  * @} MD_RCU_CSSFLG_FLAG
  */

/** @defgroup MD_RCU_PLL1_FLAG PLL1 clock ready flag
  * @{
  */
#define MD_RCU_PLL1_NOT_READY   (0x00000000UL)  /** @brief PLL1 not ready */
#define MD_RCU_PLL1_READY       (0x00000001UL)  /** @brief PLL1 ready */
/**
  * @} MD_RCU_PLL1_FLAG
  */

/** @defgroup MD_RCU_PLL0_FLAG PLL0 clock ready flag
  * @{
  */
#define MD_RCU_PLL0_NOT_READY   (0x00000000UL)  /** @brief PLL0 not ready */
#define MD_RCU_PLL0_READY       (0x00000001UL)  /** @brief PLL0 ready */
/**
  * @} MD_RCU_PLL0_FLAG
  */

/** @defgroup MD_RCU_LOSCRDY_FLAG LOSC clock ready flag
  * @{
  */
#define MD_RCU_LOSCRDY_NOT_READY   (0x00000000UL)  /** @brief LOSC oscillator not ready */
#define MD_RCU_LOSCRDY_READY       (0x00000001UL)  /** @brief LOSC oscillator ready */
/**
  * @} MD_RCU_LOSCRDY_FLAG
  */

/** @defgroup MD_RCU_LRCRDY_FLAG LRC clock ready flag
  * @{
  */
#define MD_RCU_LRCRDY_NOT_READY   (0x00000000UL)  /** @brief LRC oscillator not ready */
#define MD_RCU_LRCRDY_READY       (0x00000001UL)  /** @brief LRC oscillator ready */
/**
  * @} MD_RCU_LRCRDY_FLAG
  */

/** @defgroup MD_RCU_HOSCRDY_FLAG HOSC clock ready flag
  * @{
  */
#define MD_RCU_HOSCRDY_NOT_READY   (0x00000000UL)  /** @brief HOSC oscillator not ready */
#define MD_RCU_HOSCRDY_READY       (0x00000001UL)  /** @brief HOSC oscillator ready */
/**
  * @} MD_RCU_HOSCRDY_FLAG
  */

/** @defgroup MD_RCU_HRCRDY_FLAG HRC clock ready flag
  * @{
  */
#define MD_RCU_HRCRDY_NOT_READY   (0x00000000UL)  /** @brief HRC oscillator not ready */
#define MD_RCU_HRCRDY_READY       (0x00000001UL)  /** @brief HRC oscillator ready */
/**
  * @} MD_RCU_HRCRDY_FLAG
  */

/** @defgroup MD_RCU_MCO_OUTPUT Microcontroller clock output select
  * @{
  */
#define MD_RCU_MCO_DISABLE      (0x00000000UL)  /** @brief MCO output disabled, no clock on MCO */
#define MD_RCU_MCO_LRC          (0x00000001UL)  /** @brief Internal low speed (LRC) oscillator clock selected */
#define MD_RCU_MCO_LOSC          (0x00000002UL)  /** @brief External low speed (LOSC) oscillator clock selected */
#define MD_RCU_MCO_HRC          (0x00000003UL)  /** @brief Internal high speed (HRC) oscillator clock selected */
#define MD_RCU_MCO_HOSC          (0x00000004UL)  /** @brief External high speed (HOSC) oscillator clock selected */
#define MD_RCU_MCO_PLL0         (0x00000005UL)  /** @brief PLL0 clock selected */
#define MD_RCU_MCO_PLL1         (0x00000006UL)  /** @brief PLL1 clock selected */
#define MD_RCU_MCO_SYSCLK       (0x00000007UL)  /** @brief System clock selected(SYSCLK) */
#define MD_RCU_MCO_HCLK         (0x00000008UL)  /** @brief AHB clock selected(HCLK) */
#define MD_RCU_MCO_PCLK         (0x00000009UL)  /** @brief APB clock selected(PCLK) */
/**
  * @} MD_RCU_MCO_OUTPUT
  */

/** @defgroup MD_RCU_PLL_SRC PLL0/1 reference clock source
  * @{
  */
#define MD_RCU_PLL_SRC_HRC      (0x00000000UL)  /** @brief HRC selected as PLL0/1 reference clock */
#define MD_RCU_PLL_SRC_HOSCDIV  (0x00000001UL)  /** @brief HOSC/HOSCDIV selected as PLL reference clock */
/**
  * @} MD_RCU_PLL_SRC
  */

/** @defgroup MD_RCU_APB_CLK_DIV APB clock prescaler(PCLK)
  * @{
  */
#define MD_RCU_PPRE_HCLK_DIV_1   (0x00000000UL)  /** @brief HCLK not divided */
#define MD_RCU_PPRE_HCLK_DIV_2   (0x00000004UL)  /** @brief HCLK divided by 2 */
#define MD_RCU_PPRE_HCLK_DIV_4   (0x00000005UL)  /** @brief HCLK divided by 4 */
#define MD_RCU_PPRE_HCLK_DIV_8   (0x00000006UL)  /** @brief HCLK divided by 8 */
#define MD_RCU_PPRE_HCLK_DIV_16  (0x00000007UL)  /** @brief HCLK divided by 16 */
/**
  * @} MD_RCU_APB_CLK_DIV
  */

/** @defgroup MD_RCU_AHB_CLK_DIV AHB clock prescaler(HCLK)
  * @{
  */
#define MD_RCU_HPRE_SYSCLK_DIV_1   (0x00000000UL)  /** @brief SYSCLK not divided */
#define MD_RCU_HPRE_SYSCLK_DIV_2   (0x00000008UL)  /** @brief SYSCLK divided by 2 */
#define MD_RCU_HPRE_SYSCLK_DIV_4   (0x00000009UL)  /** @brief SYSCLK divided by 4 */
#define MD_RCU_HPRE_SYSCLK_DIV_8   (0x0000000AUL)  /** @brief SYSCLK divided by 8 */
#define MD_RCU_HPRE_SYSCLK_DIV_16  (0x0000000BUL)  /** @brief SYSCLK divided by 16 */
/**
  * @} MD_RCU_AHB_CLK_DIV
  */

/** @defgroup MD_RCU_SYS_CLK_SW System clock switch(SYSCLK)
  * @{
  */
#define MD_RCU_SYSCLK_HRC   (0x00000000UL)  /** @brief HRC selected as system clock */
#define MD_RCU_SYSCLK_HOSC   (0x00000001UL)  /** @brief HOSC selected as system clock */
#define MD_RCU_SYSCLK_LRC   (0x00000002UL)  /** @brief LRC selected as system clock */
#define MD_RCU_SYSCLK_LOSC   (0x00000003UL)  /** @brief LOSC selected as system clock */
#define MD_RCU_SYSCLK_PLL0  (0x00000004UL)  /** @brief PLL0 selected as system clock */
/**
  * @} MD_RCU_SYS_CLK_SW
  */

/** @defgroup MD_RCU_PSCK_I2S2CKSL SPI2/I2S2 External Clock Source Select
  * @{
  */
#define MD_RCU_PSCK_I2S2CKSL_DISABLE   (0x00000000UL)  /** @brief Disable External Clock (default value) */
#define MD_RCU_PSCK_I2S2CKSL_I2SCLK1   (0x00000001UL)
#define MD_RCU_PSCK_I2S2CKSL_I2SCLK2   (0x00000002UL)
/**
  * @} MD_RCU_PSCK_I2S2CKSL
  */

/** @defgroup MD_RCU_PSCK_I2S1CKSL SPI1/I2S1 External Clock Source Select
  * @{
  */
#define MD_RCU_PSCK_I2S1CKSL_DISABLE   (0x00000000UL)  /** @brief Disable External Clock (default value) */
#define MD_RCU_PSCK_I2S1CKSL_I2SCLK1   (0x00000001UL)
#define MD_RCU_PSCK_I2S1CKSL_I2SCLK2   (0x00000002UL)
/**
  * @} MD_RCU_PSCK_I2S1CKSL
  */


/**
  * @} MD_RCU_Public_Constants
  */

/* Public macro ---------------------------------------------------------------*/
/** @defgroup MD_RCU_Public_Macros RCU Public Macros
  * @{
  */

/**
  * @brief  Get System clock switch ready flag
  * @note   This bit is set by hardware to indicate that the system clock change is stable.
  *         When the CKCFG bit was set and finish configuartion process.
  * @param  rcu RCU Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_RCU_SWRDY_NOT_READY
  *         @arg @ref MD_RCU_SWRDY_READY
  */
__STATIC_INLINE uint32_t md_rcu_get_con_swrdy(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->CON, RCU_CON_SWRDY_MSK)>>RCU_CON_SWRDY_POS);
}
/**
  * @brief  Get Clock Security System flag
  * @note   This bit is reset by software by writing the CSSON bit.
  *         It is set by hardware in case of HOSC clock failure.
  * @param  rcu RCU Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_RCU_CSSFLG_NO_FAIL
  *         @arg @ref MD_RCU_CSSFLG_FAIL
  */
__STATIC_INLINE uint32_t md_rcu_get_con_cssflg(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->CON, RCU_CON_CSSFLG_MSK)>>RCU_CON_CSSFLG_POS);
}
/**
  * @brief  Get PLL1 clock ready flag
  * @note   This bit is set by hardware to indicate that the PLL1 oscillator is stable.
  * @param  rcu RCU Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_RCU_PLL1_NOT_READY
  *         @arg @ref MD_RCU_PLL1_READY
  */
__STATIC_INLINE uint32_t md_rcu_get_con_pll1rdy(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->CON, RCU_CON_PLL1RDY_MSK)>>RCU_CON_PLL1RDY_POS);
}
/**
  * @brief  Get PLL0 clock ready flag
  * @note   This bit is set by hardware to indicate that the PLL0 oscillator is stable.
  * @param  rcu RCU Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_RCU_PLL0_NOT_READY
  *         @arg @ref MD_RCU_PLL0_READY
  */
__STATIC_INLINE uint32_t md_rcu_get_con_pll0rdy(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->CON, RCU_CON_PLL0RDY_MSK)>>RCU_CON_PLL0RDY_POS);
}
/**
  * @brief  Get LOSCRDY clock ready flag
  * @note   This bit is set by hardware to indicate that the LOSC oscillator is stable.
  * @param  rcu RCU Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_RCU_LOSCRDY_NOT_READY
  *         @arg @ref MD_RCU_LOSCRDY_READY
  */
__STATIC_INLINE uint32_t md_rcu_get_con_loscrdy(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->CON, RCU_CON_LOSCRDY_MSK)>>RCU_CON_LOSCRDY_POS);
}
/**
  * @brief  Get LRCRDY clock ready flag
  * @note   This bit is set by hardware to indicate that the LRC oscillator is stable.
  * @param  rcu RCU Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_RCU_LRCRDY_NOT_READY
  *         @arg @ref MD_RCU_LRCRDY_READY
  */
__STATIC_INLINE uint32_t md_rcu_get_con_lrcrdy(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->CON, RCU_CON_LRCRDY_MSK)>>RCU_CON_LRCRDY_POS);
}
/**
  * @brief  Get HOSCRDY clock ready flag
  * @note   This bit is set by hardware to indicate that the HOSC oscillator is stable.
  * @param  rcu RCU Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_RCU_HOSCRDY_NOT_READY
  *         @arg @ref MD_RCU_HOSCRDY_READY
  */
__STATIC_INLINE uint32_t md_rcu_get_con_hoscrdy(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->CON, RCU_CON_HOSCRDY_MSK)>>RCU_CON_HOSCRDY_POS);
}
/**
  * @brief  Get HRCRDY clock ready flag
  * @note   This bit is set by hardware to indicate that the HRC oscillator is stable.
  * @param  rcu RCU Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_RCU_HRCRDY_NOT_READY
  *         @arg @ref MD_RCU_HRCRDY_READY
  */
__STATIC_INLINE uint32_t md_rcu_get_con_hrcrdy(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->CON, RCU_CON_HRCRDY_MSK)>>RCU_CON_HRCRDY_POS);
}
/**
  * @brief  Clock security system enable(CSS)
  * @note   Set and cleared by software to enable the clock security system.
  *         When CSSON is set, the clock detector is enabled by hardware when the HOSC oscillator is ready,
  *         and disabled by hardware if a HOSC clock failure is detected.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_con_csson(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->CON, RCU_CON_CSSON_MSK);
}
/**
  * @brief  Clock security system disable(CSS)
  * @note   Set and cleared by software to enable the clock security system.
  *         When CSSON is set, the clock detector is enabled by hardware when the HOSC oscillator is ready,
  *         and disabled by hardware if a HOSC clock failure is detected.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_con_csson(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->CON, RCU_CON_CSSON_MSK);
}
/**
  * @brief  Get Clock security system (CSS)
  * @note   Set and cleared by software to enable the clock security system.
  *         When CSSON is set, the clock detector is enabled by hardware when the HOSC oscillator is ready,
  *         and disabled by hardware if a HOSC clock failure is detected.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_con_csson(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->CON, RCU_CON_CSSON_MSK)>>RCU_CON_CSSON_POS);
}
/**
  * @brief  PLL1 enable bit(for USB PHY)
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_con_pll1on(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->CON, RCU_CON_PLL1ON_MSK);
}
/**
  * @brief  PLL1 disable bit(for USB PHY)
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_con_pll1on(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->CON, RCU_CON_PLL1ON_MSK);
}
/**
  * @brief  Get PLL1 bit(for USB PHY)
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_con_pll1on(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->CON, RCU_CON_PLL1ON_MSK)>>RCU_CON_PLL1ON_POS);
}
/**
  * @brief  PLL0 enable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_con_pll0on(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->CON, RCU_CON_PLL0ON_MSK);
}
/**
  * @brief  PLL0 disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_con_pll0on(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->CON, RCU_CON_PLL0ON_MSK);
}
/**
  * @brief  Get PLL0 bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_con_pll0on(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->CON, RCU_CON_PLL0ON_MSK)>>RCU_CON_PLL0ON_POS);
}
/**
  * @brief  External low speed oscillator clock enbale bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_con_loscon(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->CON, RCU_CON_LOSCON_MSK);
}
/**
  * @brief  External low speed oscillator clock disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_con_loscon(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->CON, RCU_CON_LOSCON_MSK);
}
/**
  * @brief  Get External low speed oscillator clock bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_con_loscon(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->CON, RCU_CON_LOSCON_MSK)>>RCU_CON_LOSCON_POS);
}
/**
  * @brief  Internal low speed oscillator clock enbale bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_con_lrcon(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->CON, RCU_CON_LRCON_MSK);
}
/**
  * @brief  Internal low speed oscillator clock disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_con_lrcon(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->CON, RCU_CON_LRCON_MSK);
}
/**
  * @brief  Get Internal low speed oscillator clock bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_con_lrcon(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->CON, RCU_CON_LRCON_MSK)>>RCU_CON_LRCON_POS);
}
/**
  * @brief  External high speed oscillator clock enbale bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_con_hoscon(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->CON, RCU_CON_HOSCON_MSK);
}
/**
  * @brief  External high speed oscillator clock disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_con_hoscon(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->CON, RCU_CON_HOSCON_MSK);
}
/**
  * @brief  Get External high speed oscillator clock bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_con_hoscon(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->CON, RCU_CON_HOSCON_MSK)>>RCU_CON_HOSCON_POS);
}
/**
  * @brief  Internal high speed oscillator clock enbale bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_con_hrcon(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->CON, RCU_CON_HRCON_MSK);
}
/**
  * @brief  Internal high speed oscillator clock disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_con_hrcon(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->CON, RCU_CON_HRCON_MSK);
}
/**
  * @brief  Get Internal high speed oscillator clock bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_con_hrcon(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->CON, RCU_CON_HRCON_MSK)>>RCU_CON_HRCON_POS);
}

/** @defgroup MD_RCU_CON_CSSON CSSON
  * @brief  Set Clock security system bit for md_rcu_set_con() function used
  * @param  csson This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_con_csson_fun(csson)  (csson<<RCU_CON_CSSON_POS)
/**
  * @} MD_RCU_CON_CSSON
  */
/** @defgroup MD_RCU_CON_PLL1ON PLL1ON
  * @brief  Set PLL1 bit for md_rcu_set_con() function used
  * @param  pll1on This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_con_pll1on_fun(pll1on)  (pll1on<<RCU_CON_PLL1ON_POS)
/**
  * @} MD_RCU_CON_PLL1ON
  */
/** @defgroup MD_RCU_CON_PLL0ON PLL0ON
  * @brief  Set PLL0 bit for md_rcu_set_con() function used
  * @param  pll0on This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_con_pll0on_fun(pll0on)  (pll0on<<RCU_CON_PLL0ON_POS)
/**
  * @} MD_RCU_CON_PLL0ON
  */
/** @defgroup MD_RCU_CON_LOSCON LOSCON
  * @brief  Set External low speed oscillator clock bit for md_rcu_set_con() function used
  * @param  loscon This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_con_loscon_fun(loscon)  (loscon<<RCU_CON_LOSCON_POS)
/**
  * @} MD_RCU_CON_LOSCON
  */
/** @defgroup MD_RCU_CON_LRCON LRCON
  * @brief  Set Internal low speed oscillator clock bit for md_rcu_set_con() function used
  * @param  lrcon This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_con_lrcon_fun(lrcon)  (lrcon<<RCU_CON_LRCON_POS)
/**
  * @} MD_RCU_CON_LRCON
  */
/** @defgroup MD_RCU_CON_HOSCON HOSCON
  * @brief  Set External high speed oscillator clock bit for md_rcu_set_con() function used
  * @param  hoscon This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_con_hoscon_fun(hoscon)  (hoscon<<RCU_CON_HOSCON_POS)
/**
  * @} MD_RCU_CON_HOSCON
  */
/** @defgroup MD_RCU_CON_HRCON HRCON
  * @brief  Set Internal high speed oscillator clock bit for md_rcu_set_con() function used
  * @param  hrcon This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_con_hrcon_fun(hrcon)  (hrcon<<RCU_CON_HRCON_POS)
/**
  * @} MD_RCU_CON_HRCON
  */
/**
  * @brief  Set Clock Control Register
  * @param  rcu RCU Instance
  * @param  csson This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_con_csson_fun(csson)
  * @param  pll1on This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_con_pll1on_fun(pll1on)
  * @param  pll0on This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_con_pll0on_fun(pll0on)
  * @param  loscon This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_con_loscon_fun(loscon)
  * @param  lrcon This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_con_lrcon_fun(lrcon)
  * @param  hoscon This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_con_hoscon_fun(hoscon)
  * @param  hrcon This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_con_hrcon_fun(hrcon)
  * @retval None
  */
__STATIC_INLINE void md_rcu_set_con(RCU_TypeDef *rcu, uint32_t csson, uint32_t pll1on, uint32_t pll0on, uint32_t loscon,
                                                         uint32_t lrcon, uint32_t hoscon, uint32_t hrcon)
{
  WRITE_REG(rcu->CON, (csson|pll1on|pll0on|loscon|lrcon|hoscon|hrcon));
}

/**
  * @brief  Clock configuration set bit
  * @note   This bit is write-only. A read to this bit returns the value 0.
  *         If set is bit to high, start to configurate clock setting.
  *         When the clock configuration process was finished, this bit was clear to zero by self.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_set_cfg_ckcfg(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->CFG, RCU_CFG_CKCFG_MSK);
}
/**
  * @brief  Set Microcontroller clock output prescaler
  * @note   Output Frequency = MCO/(MPRE+1)
  * @param  rcu RCU Instance
  * @param  mpre This parameter can be one of the following values:
  *         @arg Max Value 7
  *         @arg Min Value 0
  * @retval None
  */
__STATIC_INLINE void md_rcu_set_cfg_mpre(RCU_TypeDef *rcu, uint32_t mpre)
{
  MODIFY_REG(rcu->CFG, RCU_CFG_MPRE_MSK, (mpre<<RCU_CFG_MPRE_POSS));
}
/**
  * @brief  Get Microcontroller clock output prescaler
  * @note   Output Frequency = MCO/(MPRE+1)
  * @param  rcu RCU Instance
  * @retval The retval can be one of the following values:
  *         @arg Max Value 7
  *         @arg Min Value 0
  */
__STATIC_INLINE uint32_t md_rcu_get_cfg_mpre(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->CFG, RCU_CFG_MPRE_MSK)>>RCU_CFG_MPRE_POSS);
}
/**
  * @brief  Set Microcontroller clock output (MCO)
  * @param  rcu RCU Instance
  * @param  msw This parameter can be one of the following values:
  *         @arg @ref MD_RCU_MCO_DISABLE
  *         @arg @ref MD_RCU_MCO_LRC
  *         @arg @ref MD_RCU_MCO_LOSC
  *         @arg @ref MD_RCU_MCO_HRC
  *         @arg @ref MD_RCU_MCO_HOSC
  *         @arg @ref MD_RCU_MCO_PLL0
  *         @arg @ref MD_RCU_MCO_PLL1
  *         @arg @ref MD_RCU_MCO_SYSCLK
  *         @arg @ref MD_RCU_MCO_HCLK
  *         @arg @ref MD_RCU_MCO_PCLK
  * @retval None
  */
__STATIC_INLINE void md_rcu_set_cfg_msw(RCU_TypeDef *rcu, uint32_t msw)
{
  MODIFY_REG(rcu->CFG, RCU_CFG_MSW_MSK, (msw<<RCU_CFG_MSW_POSS));
}
/**
  * @brief  Get Microcontroller clock output (MCO)
  * @param  rcu RCU Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_RCU_MCO_DISABLE
  *         @arg @ref MD_RCU_MCO_LRC
  *         @arg @ref MD_RCU_MCO_LOSC
  *         @arg @ref MD_RCU_MCO_HRC
  *         @arg @ref MD_RCU_MCO_HOSC
  *         @arg @ref MD_RCU_MCO_PLL0
  *         @arg @ref MD_RCU_MCO_PLL1
  *         @arg @ref MD_RCU_MCO_SYSCLK
  *         @arg @ref MD_RCU_MCO_HCLK
  *         @arg @ref MD_RCU_MCO_PCLK
  */
__STATIC_INLINE uint32_t md_rcu_get_cfg_msw(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->CFG, RCU_CFG_MSW_MSK)>>RCU_CFG_MSW_POSS);
}
/**
  * @brief  Set PLL0 multiplication factor
  * @note   PLL0 output clock frequency is 4*(PLL0MUL+1)MHz
  * @param  rcu RCU Instance
  * @param  pllmul can be one of the following values:
  *         @arg Max Value 31
  *         @arg Min Value 0
  * @retval None
  */
__STATIC_INLINE void md_rcu_set_cfg_pllmul(RCU_TypeDef *rcu, uint32_t pllmul)
{
  MODIFY_REG(rcu->CFG, RCU_CFG_PLLMUL_MSK, (pllmul<<RCU_CFG_PLLMUL_POSS));
}
/**
  * @brief  Get PLL0 multiplication factor
  * @note   PLL0 output clock frequency is 4*(PLL0MUL+1)MHz
  * @param  rcu RCU Instance
  * @retval The retval can be one of the following values:
  *         @arg Max Value 31
  *         @arg Min Value 0
  */
__STATIC_INLINE uint32_t md_rcu_get_cfg_pllmul(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->CFG, RCU_CFG_PLLMUL_MSK)>>RCU_CFG_PLLMUL_POSS);
}
/**
  * @brief  Set PLL0/1 reference clock source
  * @param  rcu RCU Instance
  * @param  pllsrc This parameter can be one of the following values:
  *         @arg @ref MD_RCU_PLL_SRC_HRC
  *         @arg @ref MD_RCU_PLL_SRC_HOSCDIV
  * @retval None
  */
__STATIC_INLINE void md_rcu_set_cfg_pllsrc(RCU_TypeDef *rcu, uint32_t pllsrc)
{
  MODIFY_REG(rcu->CFG, RCU_CFG_PLLSRC_MSK, (pllsrc<<RCU_CFG_PLLSRC_POS));
}
/**
  * @brief  Get PLL0/1 reference clock source
  * @param  rcu RCU Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_RCU_PLL_SRC_HRC
  *         @arg @ref MD_RCU_PLL_SRC_HOSCDIV
  */
__STATIC_INLINE uint32_t md_rcu_get_cfg_pllsrc(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->CFG, RCU_CFG_PLLSRC_MSK)>>RCU_CFG_PLLSRC_POS);
}
/**
  * @brief  Set HOSC clock division factor for PLL0/1 reference clock 4 MHz
  * @note   These bits are set and cleared by software to select HOSCDIV division factor.
  * @note   PLL_reference_clock (4 MHz) = HOSC / (HOSCDIV+1)
  * @param  rcu RCU Instance
  * @param  hoscdiv can be one of the following values:
  *         @arg Max Value 7
  *         @arg Min Value 0
  * @retval None
  */
__STATIC_INLINE void md_rcu_set_cfg_hoscdiv(RCU_TypeDef *rcu, uint32_t hoscdiv)
{
  MODIFY_REG(rcu->CFG, RCU_CFG_HOSCDIV_MSK, (hoscdiv<<RCU_CFG_HOSCDIV_POSS));
}
/**
  * @brief  Get HOSC clock division factor for PLL0/1 reference clock 4 MHz
  * @note   These bits are set and cleared by software to select HOSCDIV division factor.
  * @note   PLL_reference_clock (4 MHz) = HOSC / (HOSCDIV+1)
  * @param  rcu RCU Instance
  * @retval The retval can be one of the following values:
  *         @arg Max Value 7
  *         @arg Min Value 0
  */
__STATIC_INLINE uint32_t md_rcu_get_cfg_hoscdiv(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->CFG, RCU_CFG_HOSCDIV_MSK)>>RCU_CFG_HOSCDIV_POSS);
}
/**
  * @brief  Set APB clock prescaler(PCLK)
  * @param  rcu RCU Instance
  * @param  ppre The retval can be one of the following values:
  *         @arg @ref MD_RCU_PPRE_HCLK_DIV_1
  *         @arg @ref MD_RCU_PPRE_HCLK_DIV_2
  *         @arg @ref MD_RCU_PPRE_HCLK_DIV_4
  *         @arg @ref MD_RCU_PPRE_HCLK_DIV_8
  *         @arg @ref MD_RCU_PPRE_HCLK_DIV_16
  * @retval None
  */
__STATIC_INLINE void md_rcu_set_cfg_ppre(RCU_TypeDef *rcu, uint32_t ppre)
{
  MODIFY_REG(rcu->CFG, RCU_CFG_PPRE_MSK, (ppre<<RCU_CFG_PPRE_POSS));
}
/**
  * @brief  Get APB clock prescaler(PCLK)
  * @param  rcu RCU Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_RCU_PPRE_HCLK_DIV_1
  *         @arg @ref MD_RCU_PPRE_HCLK_DIV_2
  *         @arg @ref MD_RCU_PPRE_HCLK_DIV_4
  *         @arg @ref MD_RCU_PPRE_HCLK_DIV_8
  *         @arg @ref MD_RCU_PPRE_HCLK_DIV_16
  */
__STATIC_INLINE uint32_t md_rcu_get_cfg_ppre(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->CFG, RCU_CFG_PPRE_MSK)>>RCU_CFG_PPRE_POSS);
}
/**
  * @brief  Set AHB clock prescaler(HCLK)
  * @param  rcu RCU Instance
  * @param  hpre can be one of the following values:
  *         @arg @ref MD_RCU_HPRE_SYSCLK_DIV_1
  *         @arg @ref MD_RCU_HPRE_SYSCLK_DIV_2
  *         @arg @ref MD_RCU_HPRE_SYSCLK_DIV_4
  *         @arg @ref MD_RCU_HPRE_SYSCLK_DIV_8
  *         @arg @ref MD_RCU_HPRE_SYSCLK_DIV_16
  * @retval None
  */
__STATIC_INLINE void md_rcu_set_cfg_hpre(RCU_TypeDef *rcu, uint32_t hpre)
{
  MODIFY_REG(rcu->CFG, RCU_CFG_HPRE_MSK, (hpre<<RCU_CFG_HPRE_POSS));
}
/**
  * @brief  Get AHB clock prescaler(HCLK)
  * @param  rcu RCU Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_RCU_HPRE_SYSCLK_DIV_1
  *         @arg @ref MD_RCU_HPRE_SYSCLK_DIV_2
  *         @arg @ref MD_RCU_HPRE_SYSCLK_DIV_4
  *         @arg @ref MD_RCU_HPRE_SYSCLK_DIV_8
  *         @arg @ref MD_RCU_HPRE_SYSCLK_DIV_16
  */
__STATIC_INLINE uint32_t md_rcu_get_cfg_hpre(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->CFG, RCU_CFG_HPRE_MSK)>>RCU_CFG_HPRE_POSS);
}
/**
  * @brief  Set System clock switch(SYSCLK)
  * @param  rcu RCU Instance
  * @param  sw can be one of the following values:
  *         @arg @ref MD_RCU_SYSCLK_HRC
  *         @arg @ref MD_RCU_SYSCLK_HOSC
  *         @arg @ref MD_RCU_SYSCLK_LRC
  *         @arg @ref MD_RCU_SYSCLK_LOSC
  *         @arg @ref MD_RCU_SYSCLK_PLL0
  * @retval None
  */
__STATIC_INLINE void md_rcu_set_cfg_sw(RCU_TypeDef *rcu, uint32_t sw)
{
  MODIFY_REG(rcu->CFG, RCU_CFG_SW_MSK, (sw<<RCU_CFG_SW_POSS));
}
/**
  * @brief  Get System clock switch(SYSCLK)
  * @param  rcu RCU Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_RCU_SYSCLK_HRC
  *         @arg @ref MD_RCU_SYSCLK_HOSC
  *         @arg @ref MD_RCU_SYSCLK_LRC
  *         @arg @ref MD_RCU_SYSCLK_LOSC
  *         @arg @ref MD_RCU_SYSCLK_PLL0
  */
__STATIC_INLINE uint32_t md_rcu_get_cfg_sw(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->CFG, RCU_CFG_SW_MSK)>>RCU_CFG_SW_POSS);
}
/** @defgroup MD_RCU_CFG_MPRE MPRE
  * @brief  Set Microcontroller clock output prescaler bit for md_rcu_set_cfg() function used
  * @param  mpre This parameter can be one of the following values:
  *         @arg Max Value 7
  *         @arg Min Value 0
  * @{
  */
#define md_rcu_set_cfg_mpre_fun(mpre)  (mpre<<RCU_CFG_MPRE_POSS)
/**
  * @} MD_RCU_CFG_MPRE
  */
/** @defgroup MD_RCU_CFG_MSW MSW
  * @brief  Set Microcontroller clock output (MCO) bit for md_rcu_set_cfg() function used
  * @param  msw This parameter can be one of the following values:
  *         @arg @ref MD_RCU_MCO_DISABLE
  *         @arg @ref MD_RCU_MCO_LRC
  *         @arg @ref MD_RCU_MCO_LOSC
  *         @arg @ref MD_RCU_MCO_HRC
  *         @arg @ref MD_RCU_MCO_HOSC
  *         @arg @ref MD_RCU_MCO_PLL0
  *         @arg @ref MD_RCU_MCO_PLL1
  *         @arg @ref MD_RCU_MCO_SYSCLK
  *         @arg @ref MD_RCU_MCO_HCLK
  *         @arg @ref MD_RCU_MCO_PCLK
  * @{
  */
#define md_rcu_set_cfg_msw_fun(msw)  (msw<<RCU_CFG_MSW_POSS)
/**
  * @} MD_RCU_CFG_MSW
  */
/** @defgroup MD_RCU_CFG_PLLMUL PLLMUL
  * @brief  Set PLL0 multiplication factor bit for md_rcu_set_cfg() function used
  * @param  pllmul This parameter can be one of the following values:
  *         @arg Max Value 31
  *         @arg Min Value 0
  * @{
  */
#define md_rcu_set_cfg_pllmul_fun(pllmul)  (pllmul<<RCU_CFG_PLLMUL_POSS)
/**
  * @} MD_RCU_CFG_PLLMUL
  */
/** @defgroup MD_RCU_CFG_PLLSRC PLLSRC
  * @brief  Set PLL0/1 reference clock source bit for md_rcu_set_cfg() function used
  * @param  pllsrc This parameter can be one of the following values:
  *         @arg @ref MD_RCU_PLL_SRC_HRC
  *         @arg @ref MD_RCU_PLL_SRC_HOSCDIV
  * @{
  */
#define md_rcu_set_cfg_pllsrc_fun(pllsrc)  (pllsrc<<RCU_CFG_PLLSRC_POS)
/**
  * @} MD_RCU_CFG_PLLSRC
  */
/** @defgroup MD_RCU_CFG_HOSCDIV HOSCDIV
  * @brief  Set HOSC clock division factor for PLL0/1 reference clock 4 MHz bit for md_rcu_set_cfg() function used
  * @param  hoscdiv This parameter can be one of the following values:
  *         @arg Max Value 7
  *         @arg Min Value 0
  * @{
  */
#define md_rcu_set_cfg_hoscdiv_fun(hoscdiv)  (hoscdiv<<RCU_CFG_HOSCDIV_POSS)
/**
  * @} MD_RCU_CFG_HOSCDIV
  */
/** @defgroup MD_RCU_CFG_PPRE PPRE
  * @brief  Set APB clock prescaler(PCLK) bit for md_rcu_set_cfg() function used
  * @param  ppre This parameter can be one of the following values:
  *         @arg @ref MD_RCU_PPRE_HCLK_DIV_1
  *         @arg @ref MD_RCU_PPRE_HCLK_DIV_2
  *         @arg @ref MD_RCU_PPRE_HCLK_DIV_4
  *         @arg @ref MD_RCU_PPRE_HCLK_DIV_8
  *         @arg @ref MD_RCU_PPRE_HCLK_DIV_16
  * @{
  */
#define md_rcu_set_cfg_ppre_fun(ppre)  (ppre<<RCU_CFG_PPRE_POSS)
/**
  * @} MD_RCU_CFG_PPRE
  */
/** @defgroup MD_RCU_CFG_HPRE HPRE
  * @brief  Set AHB clock prescaler(HCLK) bit for md_rcu_set_cfg() function used
  * @param  hpre This parameter can be one of the following values:
  *         @arg @ref MD_RCU_HPRE_SYSCLK_DIV_1
  *         @arg @ref MD_RCU_HPRE_SYSCLK_DIV_2
  *         @arg @ref MD_RCU_HPRE_SYSCLK_DIV_4
  *         @arg @ref MD_RCU_HPRE_SYSCLK_DIV_8
  *         @arg @ref MD_RCU_HPRE_SYSCLK_DIV_16
  * @{
  */
#define md_rcu_set_cfg_hpre_fun(hpre)  (hpre<<RCU_CFG_HPRE_POSS)
/**
  * @} MD_RCU_CFG_HPRE
  */
/** @defgroup MD_RCU_CFG_SW SW
  * @brief  Set System clock switch(SYSCLK) bit for md_rcu_set_cfg() function used
  * @param  sw This parameter can be one of the following values:
  *         @arg @ref MD_RCU_SYSCLK_HRC
  *         @arg @ref MD_RCU_SYSCLK_HOSC
  *         @arg @ref MD_RCU_SYSCLK_LRC
  *         @arg @ref MD_RCU_SYSCLK_LOSC
  *         @arg @ref MD_RCU_SYSCLK_PLL0
  * @{
  */
#define md_rcu_set_cfg_sw_fun(sw)  (sw<<RCU_CFG_SW_POSS)
/**
  * @} MD_RCU_CFG_SW
  */
/**
  * @brief  Set Clock Configuration Register
  * @param  rcu RCU Instance
  * @param  mpre This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_cfg_mpre_fun(mpre)
  * @param  msw This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_cfg_msw_fun(msw)
  * @param  pllmul This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_cfg_pllmul_fun(pllmul)
  * @param  pllsrc This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_cfg_pllsrc_fun(pllsrc)
  * @param  hoscdiv This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_cfg_hoscdiv_fun(hoscdiv)
  * @param  ppre This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_cfg_ppre_fun(ppre)
  * @param  hpre This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_cfg_hpre_fun(hpre)
  * @param  sw This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_cfg_sw_fun(sw)
  * @retval None
  */
__STATIC_INLINE void md_rcu_set_cfg(RCU_TypeDef *rcu, uint32_t mpre,    uint32_t msw,  uint32_t pllmul, uint32_t pllsrc,
                                                      uint32_t hoscdiv, uint32_t ppre, uint32_t hpre,   uint32_t sw)
{
  WRITE_REG(rcu->CFG, (mpre|msw|pllmul|pllsrc|hoscdiv|ppre|hpre|sw));
}

/**
  * @brief  Set SPI2/I2S2 External Clock Source Select
  * @param  rcu RCU Instance
  * @param  i2s2ckdl This parameter can be one of the following values:
  *         @arg @ref MD_RCU_PSCK_I2S2CKSL_DISABLE
  *         @arg @ref MD_RCU_PSCK_I2S2CKSL_I2SCLK1
  *         @arg @ref MD_RCU_PSCK_I2S2CKSL_I2SCLK2
  * @retval None
  */
__STATIC_INLINE void md_rcu_set_psck_i2s2ckdl(RCU_TypeDef *rcu, uint32_t i2s2ckdl)
{
  MODIFY_REG(rcu->PSCK, RCU_PSCK_I2S2CKSL_MSK, (i2s2ckdl<<RCU_PSCK_I2S2CKSL_POSS));
}
/**
  * @brief  Get SPI2/I2S2 External Clock Source Select
  * @param  rcu RCU Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_RCU_PSCK_I2S2CKSL_DISABLE
  *         @arg @ref MD_RCU_PSCK_I2S2CKSL_I2SCLK1
  *         @arg @ref MD_RCU_PSCK_I2S2CKSL_I2SCLK2
  */
__STATIC_INLINE uint32_t md_rcu_get_psck_i2s2ckdl(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->PSCK, RCU_PSCK_I2S2CKSL_MSK)>>RCU_PSCK_I2S2CKSL_POSS);
}
/**
  * @brief  Set SPI1/I2S1 External Clock Source Select
  * @param  rcu RCU Instance
  * @param  i2s1ckdl This parameter can be one of the following values:
  *         @arg @ref MD_RCU_PSCK_I2S1CKSL_DISABLE
  *         @arg @ref MD_RCU_PSCK_I2S1CKSL_I2SCLK1
  *         @arg @ref MD_RCU_PSCK_I2S1CKSL_I2SCLK2
  * @retval None
  */
__STATIC_INLINE void md_rcu_set_psck_i2s1ckdl(RCU_TypeDef *rcu, uint32_t i2s1ckdl)
{
  MODIFY_REG(rcu->PSCK, RCU_PSCK_I2S1CKSL_MSK, (i2s1ckdl<<RCU_PSCK_I2S1CKSL_POSS));
}
/**
  * @brief  Get SPI1/I2S1 External Clock Source Select
  * @param  rcu RCU Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_RCU_PSCK_I2S1CKSL_DISABLE
  *         @arg @ref MD_RCU_PSCK_I2S1CKSL_I2SCLK1
  *         @arg @ref MD_RCU_PSCK_I2S1CKSL_I2SCLK2
  */
__STATIC_INLINE uint32_t md_rcu_get_psck_i2s1ckdl(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->PSCK, RCU_PSCK_I2S1CKSL_MSK)>>RCU_PSCK_I2S1CKSL_POSS);
}

/** @defgroup MD_RCU_PSCK_I2S2CKSL_ I2S2CKSL
  * @brief  Set SPI2/I2S2 External Clock Source Select bit for md_rcu_set_psck() function used
  * @param  i2s2ckdl This parameter can be one of the following values:
  *         @arg @ref MD_RCU_PSCK_I2S2CKSL_DISABLE
  *         @arg @ref MD_RCU_PSCK_I2S2CKSL_I2SCLK1
  *         @arg @ref MD_RCU_PSCK_I2S2CKSL_I2SCLK2
  * @{
  */
#define md_rcu_set_psck_i2s2ckdl_fun(i2s2ckdl)  (i2s2ckdl<<RCU_PSCK_I2S2CKSL_POSS)
/**
  * @} MD_RCU_PSCK_I2S2CKSL_
  */
/** @defgroup MD_RCU_PSCK_I2S1CKSL_ I2S1CKSL
  * @brief  Set SPI1/I2S1 External Clock Source Select bit for md_rcu_set_psck() function used
  * @param  i2s1ckdl This parameter can be one of the following values:
  *         @arg @ref MD_RCU_PSCK_I2S1CKSL_DISABLE
  *         @arg @ref MD_RCU_PSCK_I2S1CKSL_I2SCLK1
  *         @arg @ref MD_RCU_PSCK_I2S1CKSL_I2SCLK2
  * @{
  */
#define md_rcu_set_psck_i2s1ckdl_fun(i2s1ckdl)  (i2s1ckdl<<RCU_PSCK_I2S1CKSL_POSS)
/**
  * @} MD_RCU_PSCK_I2S1CKSL_
  */
/**
  * @brief  Set Peripheral Special Clock Control Register
  * @param  rcu RCU Instance
  * @param  i2s2ckdl This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_psck_i2s2ckdl_fun(i2s2ckdl)
  * @param  i2s1ckdl This parameter can be one of the following values:
  *         md_rcu_set_psck_i2s1ckdl_fun(i2s1ckdl)
  * @retval None
  */
__STATIC_INLINE void md_rcu_set_psck(RCU_TypeDef *rcu, uint32_t i2s2ckdl, uint32_t i2s1ckdl)
{
  WRITE_REG(rcu->PSCK, (i2s2ckdl|i2s1ckdl));
}

/**
  * @brief  GPIOD reset request enable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahbrst_gpden(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBRST, RCU_AHBRST_GPDEN_MSK);
}
/**
  * @brief  GPIOD reset request disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahbrst_gpden(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBRST, RCU_AHBRST_GPDEN_MSK);
}
/**
  * @brief  Get GPIOD reset request bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahbrst_gpden(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBRST, RCU_AHBRST_GPDEN_MSK)>>RCU_AHBRST_GPDEN_POS);
}
/**
  * @brief  GPIOC reset request enable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahbrst_gpcen(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBRST, RCU_AHBRST_GPCEN_MSK);
}
/**
  * @brief  GPIOC reset request disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahbrst_gpcen(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBRST, RCU_AHBRST_GPCEN_MSK);
}
/**
  * @brief  Get GPIOC reset request bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahbrst_gpcen(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBRST, RCU_AHBRST_GPCEN_MSK)>>RCU_AHBRST_GPCEN_POS);
}
/**
  * @brief  GPIOB reset request enable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahbrst_gpben(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBRST, RCU_AHBRST_GPBEN_MSK);
}
/**
  * @brief  GPIOB reset request disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahbrst_gpben(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBRST, RCU_AHBRST_GPBEN_MSK);
}
/**
  * @brief  Get GPIOB reset request bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahbrst_gpben(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBRST, RCU_AHBRST_GPBEN_MSK)>>RCU_AHBRST_GPBEN_POS);
}
/**
  * @brief  GPIOA reset request enable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahbrst_gpaen(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBRST, RCU_AHBRST_GPAEN_MSK);
}
/**
  * @brief  GPIOA reset request disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahbrst_gpaen(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBRST, RCU_AHBRST_GPAEN_MSK);
}
/**
  * @brief  Get GPIOA reset request bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahbrst_gpaen(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBRST, RCU_AHBRST_GPAEN_MSK)>>RCU_AHBRST_GPAEN_POS);
}
/**
  * @brief  HDIV reset request enable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahbrst_hdiven(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBRST, RCU_AHBRST_HDIVEN_MSK);
}
/**
  * @brief  HDIV reset request disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahbrst_hdiven(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBRST, RCU_AHBRST_HDIVEN_MSK);
}
/**
  * @brief  Get HDIV reset request bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahbrst_hdiven(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBRST, RCU_AHBRST_HDIVEN_MSK)>>RCU_AHBRST_HDIVEN_POS);
}
/**
  * @brief  USB reset request enable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahbrst_usben(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBRST, RCU_AHBRST_USBEN_MSK);
}
/**
  * @brief  USB reset request disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahbrst_usben(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBRST, RCU_AHBRST_USBEN_MSK);
}
/**
  * @brief  Get USB reset request bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahbrst_usben(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBRST, RCU_AHBRST_USBEN_MSK)>>RCU_AHBRST_USBEN_POS);
}
/**
  * @brief  AES reset request enable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahbrst_aesen(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBRST, RCU_AHBRST_AESEN_MSK);
}
/**
  * @brief  AES reset request disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahbrst_aesen(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBRST, RCU_AHBRST_AESEN_MSK);
}
/**
  * @brief  Get AES reset request bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahbrst_aesen(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBRST, RCU_AHBRST_AESEN_MSK)>>RCU_AHBRST_AESEN_POS);
}
/**
  * @brief  CRC reset request enable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahbrst_crcen(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBRST, RCU_AHBRST_CRCEN_MSK);
}
/**
  * @brief  CRC reset request disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahbrst_crcen(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBRST, RCU_AHBRST_CRCEN_MSK);
}
/**
  * @brief  Get CRC reset request bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahbrst_crcen(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBRST, RCU_AHBRST_CRCEN_MSK)>>RCU_AHBRST_CRCEN_POS);
}
/**
  * @brief  RTC reset request enable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahbrst_rtcen(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBRST, RCU_AHBRST_RTCEN_MSK);
}
/**
  * @brief  RTC reset request disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahbrst_rtcen(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBRST, RCU_AHBRST_RTCEN_MSK);
}
/**
  * @brief  Get RTC reset request bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahbrst_rtcen(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBRST, RCU_AHBRST_RTCEN_MSK)>>RCU_AHBRST_RTCEN_POS);
}
/**
  * @brief  DMA1 reset request enable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahbrst_dma1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBRST, RCU_AHBRST_DMA1EN_MSK);
}
/**
  * @brief  DMA1 reset request disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahbrst_dma1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBRST, RCU_AHBRST_DMA1EN_MSK);
}
/**
  * @brief  Get DMA1 reset request bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahbrst_dma1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBRST, RCU_AHBRST_DMA1EN_MSK)>>RCU_AHBRST_DMA1EN_POS);
}

/** @defgroup MD_RCU_AHBRST_GPDEN GPDEN
  * @brief  Set GPIOD reset request bit for md_rcu_set_ahbrst() function used
  * @param  gpden This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_ahbrst_gpden_fun(gpden)  (gpden<<RCU_AHBRST_GPDEN_POS)
/**
  * @} MD_RCU_AHBRST_GPDEN
  */
/** @defgroup MD_RCU_AHBRST_GPCEN GPCEN
  * @brief  Set GPIOC reset request bit for md_rcu_set_ahbrst() function used
  * @param  gpcen This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_ahbrst_gpcen_fun(gpcen)  (gpcen<<RCU_AHBRST_GPCEN_POS)
/**
  * @} MD_RCU_AHBRST_GPCEN
  */
/** @defgroup MD_RCU_AHBRST_GPBEN GPBEN
  * @brief  Set GPIOB reset request bit for md_rcu_set_ahbrst() function used
  * @param  gpben This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_ahbrst_gpben_fun(gpben)  (gpben<<RCU_AHBRST_GPBEN_POS)
/**
  * @} MD_RCU_AHBRST_GPBEN
  */
/** @defgroup MD_RCU_AHBRST_GPAEN GPAEN
  * @brief  Set GPIOA reset request bit for md_rcu_set_ahbrst() function used
  * @param  gpaen This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_ahbrst_gpaen_fun(gpaen)  (gpaen<<RCU_AHBRST_GPAEN_POS)
/**
  * @} MD_RCU_AHBRST_GPAEN
  */
/** @defgroup MD_RCU_AHBRST_HDIVEN HDIVEN
  * @brief  Set HDIV reset request bit for md_rcu_set_ahbrst() function used
  * @param  hdiven This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_ahbrst_hdiven_fun(hdiven)  (hdiven<<RCU_AHBRST_HDIVEN_POS)
/**
  * @} MD_RCU_AHBRST_HDIVEN
  */
/** @defgroup MD_RCU_AHBRST_USBEN USBEN
  * @brief  Set USB reset request bit for md_rcu_set_ahbrst() function used
  * @param  usben This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_ahbrst_usben_fun(usben)  (usben<<RCU_AHBRST_USBEN_POS)
/**
  * @} MD_RCU_AHBRST_USBEN
  */
/** @defgroup MD_RCU_AHBRST_AESEN AESEN
  * @brief  Set AES reset request bit for md_rcu_set_ahbrst() function used
  * @param  aesen This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_ahbrst_aesen_fun(aesen)  (aesen<<RCU_AHBRST_AESEN_POS)
/**
  * @} MD_RCU_AHBRST_AESEN
  */
/** @defgroup MD_RCU_AHBRST_CRCEN CRCEN
  * @brief  Set CRC reset request bit for md_rcu_set_ahbrst() function used
  * @param  crcen This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_ahbrst_crcen_fun(crcen)  (crcen<<RCU_AHBRST_CRCEN_POS)
/**
  * @} MD_RCU_AHBRST_CRCEN
  */
/** @defgroup MD_RCU_AHBRST_RTCEN RTCEN
  * @brief  Set RTC reset request bit for md_rcu_set_ahbrst() function used
  * @param  rtcen This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_ahbrst_rtcen_fun(rtcen)  (rtcen<<RCU_AHBRST_RTCEN_POS)
/**
  * @} MD_RCU_AHBRST_RTCEN
  */
/** @defgroup MD_RCU_AHBRST_DMA1EN DMA1EN
  * @brief  Set DMA1 reset request bit for md_rcu_set_ahbrst() function used
  * @param  dma1en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_ahbrst_dma1en_fun(dma1en)  (dma1en<<RCU_AHBRST_DMA1EN_POS)
/**
  * @} MD_RCU_AHBRST_DMA1EN
  */
/**
  * @brief  Set Peripheral Special Clock Control Register
  * @param  rcu RCU Instance
  * @param  gpden This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_ahbrst_gpden_fun(gpden)
  * @param  gpcen This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_ahbrst_gpcen_fun(gpcen)
  * @param  gpben This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_ahbrst_gpben_fun(gpben)
  * @param  gpaen This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_ahbrst_gpaen_fun(gpaen)
  * @param  hdiven This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_ahbrst_hdiven_fun(hdiven)
  * @param  usben This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_ahbrst_usben_fun(usben)
  * @param  aesen This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_ahbrst_aesen_fun(aesen)
  * @param  crcen This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_ahbrst_crcen_fun(crcen)
  * @param  rtcen This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_ahbrst_rtcen_fun(rtcen)
  * @param  dma1en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_ahbrst_dma1en_fun(dma1en)
  * @retval None
  */
__STATIC_INLINE void md_rcu_set_ahbrst(RCU_TypeDef *rcu, uint32_t gpden,  uint32_t gpcen,  uint32_t gpben,
                                                         uint32_t gpaen,  uint32_t hdiven, uint32_t usben,
                                                         uint32_t aesen,  uint32_t crcen,  uint32_t rtcen,
                                                         uint32_t dma1en)
{
  WRITE_REG(rcu->AHBRST, (gpden|gpcen|gpben|gpaen|hdiven|usben|aesen|crcen|rtcen|dma1en));
}

/**
  * @brief  DAC reset request enable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1rst_dacen(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1RST, RCU_APB1RST_DACEN_MSK);
}
/**
  * @brief  DAC reset request disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1rst_dacen(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1RST, RCU_APB1RST_DACEN_MSK);
}
/**
  * @brief  Get DAC reset request bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1rst_dacen(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1RST, RCU_APB1RST_DACEN_MSK)>>RCU_APB1RST_DACEN_POS);
}
/**
  * @brief  I2C2 reset request enable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1rst_i2c2en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1RST, RCU_APB1RST_I2C2EN_MSK);
}
/**
  * @brief  I2C2 reset request disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1rst_i2c2en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1RST, RCU_APB1RST_I2C2EN_MSK);
}
/**
  * @brief  Get I2C2 reset request bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1rst_i2c2en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1RST, RCU_APB1RST_I2C2EN_MSK)>>RCU_APB1RST_I2C2EN_POS);
}
/**
  * @brief  I2C1 reset request enable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1rst_i2c1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1RST, RCU_APB1RST_I2C1EN_MSK);
}
/**
  * @brief  I2C1 reset request disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1rst_i2c1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1RST, RCU_APB1RST_I2C1EN_MSK);
}
/**
  * @brief  Get I2C1 reset request bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1rst_i2c1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1RST, RCU_APB1RST_I2C1EN_MSK)>>RCU_APB1RST_I2C1EN_POS);
}
/**
  * @brief  SUART2 reset request enable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1rst_suart2en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1RST, RCU_APB1RST_SUART2EN_MSK);
}
/**
  * @brief  SUART2 reset request disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1rst_suart2en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1RST, RCU_APB1RST_SUART2EN_MSK);
}
/**
  * @brief  Get SUART2 reset request bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1rst_suart2en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1RST, RCU_APB1RST_SUART2EN_MSK)>>RCU_APB1RST_SUART2EN_POS);
}
/**
  * @brief  SUART1 reset request enable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1rst_suart1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1RST, RCU_APB1RST_SUART1EN_MSK);
}
/**
  * @brief  SUART1 reset request disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1rst_suart1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1RST, RCU_APB1RST_SUART1EN_MSK);
}
/**
  * @brief  Get SUART1 reset request bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1rst_suart1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1RST, RCU_APB1RST_SUART1EN_MSK)>>RCU_APB1RST_SUART1EN_POS);
}
/**
  * @brief  UART3 reset request enable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1rst_uart3en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1RST, RCU_APB1RST_UART3EN_MSK);
}
/**
  * @brief  UART3 reset request disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1rst_uart3en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1RST, RCU_APB1RST_UART3EN_MSK);
}
/**
  * @brief  Get UART3 reset request bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1rst_uart3en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1RST, RCU_APB1RST_UART3EN_MSK)>>RCU_APB1RST_UART3EN_POS);
}
/**
  * @brief  UART2 reset request enable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1rst_uart2en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1RST, RCU_APB1RST_UART2EN_MSK);
}
/**
  * @brief  UART2 reset request disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1rst_uart2en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1RST, RCU_APB1RST_UART2EN_MSK);
}
/**
  * @brief  Get UART2 reset request bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1rst_uart2en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1RST, RCU_APB1RST_UART2EN_MSK)>>RCU_APB1RST_UART2EN_POS);
}
/**
  * @brief  SPI2 reset request enable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1rst_spi2en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1RST, RCU_APB1RST_SPI2EN_MSK);
}
/**
  * @brief  SPI2 reset request disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1rst_spi2en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1RST, RCU_APB1RST_SPI2EN_MSK);
}
/**
  * @brief  Get SPI2 reset request bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1rst_spi2en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1RST, RCU_APB1RST_SPI2EN_MSK)>>RCU_APB1RST_SPI2EN_POS);
}
/**
  * @brief  IWDT reset request enable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1rst_iwdten(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1RST, RCU_APB1RST_IWDTEN_MSK);
}
/**
  * @brief  IWDT reset request disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1rst_iwdten(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1RST, RCU_APB1RST_IWDTEN_MSK);
}
/**
  * @brief  Get IWDT reset request bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1rst_iwdten(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1RST, RCU_APB1RST_IWDTEN_MSK)>>RCU_APB1RST_IWDTEN_POS);
}
/**
  * @brief  WWDT reset request enable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1rst_wwdten(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1RST, RCU_APB1RST_WWDTEN_MSK);
}
/**
  * @brief  WWDT reset request disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1rst_wwdten(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1RST, RCU_APB1RST_WWDTEN_MSK);
}
/**
  * @brief  Get WWDT reset request bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1rst_wwdten(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1RST, RCU_APB1RST_WWDTEN_MSK)>>RCU_APB1RST_WWDTEN_POS);
}
/**
  * @brief  BS16T1 reset request enable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1rst_bs16t1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1RST, RCU_APB1RST_BS16T1EN_MSK);
}
/**
  * @brief  BS16T1 reset request disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1rst_bs16t1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1RST, RCU_APB1RST_BS16T1EN_MSK);
}
/**
  * @brief  Get BS16T1 reset request bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1rst_bs16t1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1RST, RCU_APB1RST_BS16T1EN_MSK)>>RCU_APB1RST_BS16T1EN_POS);
}
/**
  * @brief  GP16C4T3 reset request enable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1rst_gp16c4t3en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1RST, RCU_APB1RST_GP16C4T3EN_MSK);
}
/**
  * @brief  GP16C4T3 reset request disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1rst_gp16c4t3en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1RST, RCU_APB1RST_GP16C4T3EN_MSK);
}
/**
  * @brief  Get GP16C4T3 reset request bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1rst_gp16c4t3en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1RST, RCU_APB1RST_GP16C4T3EN_MSK)>>RCU_APB1RST_GP16C4T3EN_POS);
}
/**
  * @brief  GP16C4T2 reset request enable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1rst_gp16c4t2en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1RST, RCU_APB1RST_GP16C4T2EN_MSK);
}
/**
  * @brief  GP16C4T2 reset request disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1rst_gp16c4t2en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1RST, RCU_APB1RST_GP16C4T2EN_MSK);
}
/**
  * @brief  Get GP16C4T2 reset request bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1rst_gp16c4t2en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1RST, RCU_APB1RST_GP16C4T2EN_MSK)>>RCU_APB1RST_GP16C4T2EN_POS);
}
/**
  * @brief  GP16C4T1 reset request enable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1rst_gp16c4t1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1RST, RCU_APB1RST_GP16C4T1EN_MSK);
}
/**
  * @brief  GP16C4T1 reset request disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1rst_gp16c4t1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1RST, RCU_APB1RST_GP16C4T1EN_MSK);
}
/**
  * @brief  Get GP16C4T1 reset request bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1rst_gp16c4t1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1RST, RCU_APB1RST_GP16C4T1EN_MSK)>>RCU_APB1RST_GP16C4T1EN_POS);
}
/**
  * @brief  GP32C4T1 reset request enable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1rst_gp32c4t1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1RST, RCU_APB1RST_GP32C4T1EN_MSK);
}
/**
  * @brief  GP32C4T1 reset request disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1rst_gp32c4t1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1RST, RCU_APB1RST_GP32C4T1EN_MSK);
}
/**
  * @brief  Get GP32C4T1 reset request bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1rst_gp32c4t1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1RST, RCU_APB1RST_GP32C4T1EN_MSK)>>RCU_APB1RST_GP32C4T1EN_POS);
}

/** @defgroup MD_RCU_APB1RST_DACEN DACEN
  * @brief  Set DAC reset request bit for md_rcu_set_apb1rst() function used
  * @param  dacen This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb1rst_dacen_fun(dacen)  (dacen<<RCU_APB1RST_DACEN_POS)
/**
  * @} MD_RCU_APB1RST_DACEN
  */
/** @defgroup MD_RCU_APB1RST_I2C2EN I2C2EN
  * @brief  Set I2C2 reset request bit for md_rcu_set_apb1rst() function used
  * @param  i2c2en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb1rst_i2c2en_fun(i2c2en)  (i2c2en<<RCU_APB1RST_I2C2EN_POS)
/**
  * @} MD_RCU_APB1RST_I2C2EN
  */
/** @defgroup MD_RCU_APB1RST_I2C1EN I2C1EN
  * @brief  Set I2C1 reset request bit for md_rcu_set_apb1rst() function used
  * @param  i2c1en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb1rst_i2c1en_fun(i2c1en)  (i2c1en<<RCU_APB1RST_I2C1EN_POS)
/**
  * @} MD_RCU_APB1RST_I2C1EN
  */
/** @defgroup MD_RCU_APB1RST_SUART2EN SUART2EN
  * @brief  Set SUART2 reset request bit for md_rcu_set_apb1rst() function used
  * @param  suart2en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb1rst_suart2en_fun(suart2en)  (suart2en<<RCU_APB1RST_SUART2EN_POS)
/**
  * @} MD_RCU_APB1RST_SUART2EN
  */
/** @defgroup MD_RCU_APB1RST_SUART1EN SUART1EN
  * @brief  Set SUART1 reset request bit for md_rcu_set_apb1rst() function used
  * @param  suart1en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb1rst_suart1en_fun(suart1en)  (suart1en<<RCU_APB1RST_SUART1EN_POS)
/**
  * @} MD_RCU_APB1RST_SUART1EN
  */
/** @defgroup MD_RCU_APB1RST_UART3EN UART3EN
  * @brief  Set UART3 reset request bit for md_rcu_set_apb1rst() function used
  * @param  uart3en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb1rst_uart3en_fun(uart3en)  (uart3en<<RCU_APB1RST_UART3EN_POS)
/**
  * @} MD_RCU_APB1RST_UART3EN
  */
/** @defgroup MD_RCU_APB1RST_UART2EN UART2EN
  * @brief  Set UART2 reset request bit for md_rcu_set_apb1rst() function used
  * @param  uart2en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb1rst_uart2en_fun(uart2en)  (uart2en<<RCU_APB1RST_UART2EN_POS)
/**
  * @} MD_RCU_APB1RST_UART2EN
  */
/** @defgroup MD_RCU_APB1RST_SPI2EN SPI2EN
  * @brief  Set SPI2 reset request bit for md_rcu_set_apb1rst() function used
  * @param  spi2en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb1rst_spi2en_fun(spi2en)  (spi2en<<RCU_APB1RST_SPI2EN_POS)
/**
  * @} MD_RCU_APB1RST_SPI2EN
  */
/** @defgroup MD_RCU_APB1RST_IWDTEN IWDTEN
  * @brief  Set IWDT reset request bit for md_rcu_set_apb1rst() function used
  * @param  iwdten This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb1rst_iwdten_fun(iwdten)  (iwdten<<RCU_APB1RST_IWDTEN_POS)
/**
  * @} MD_RCU_APB1RST_IWDTEN
  */
/** @defgroup MD_RCU_APB1RST_WWDTEN WWDTEN
  * @brief  Set WWDT reset request bit for md_rcu_set_apb1rst() function used
  * @param  wwdten This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb1rst_wwdten_fun(wwdten)  (wwdten<<RCU_APB1RST_WWDTEN_POS)
/**
  * @} MD_RCU_APB1RST_WWDTEN
  */
/** @defgroup MD_RCU_APB1RST_BS16T1EN BS16T1EN
  * @brief  Set BS16T1 reset request bit for md_rcu_set_apb1rst() function used
  * @param  bs16t1en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb1rst_bs16t1en_fun(bs16t1en)  (bs16t1en<<RCU_APB1RST_BS16T1EN_POS)
/**
  * @} MD_RCU_APB1RST_BS16T1EN
  */
/** @defgroup MD_RCU_APB1RST_GP16C4T3EN GP16C4T3EN
  * @brief  Set GP16C4T3 reset request bit for md_rcu_set_apb1rst() function used
  * @param  gp16c4t3en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb1rst_gp16c4t3en_fun(gp16c4t3en)  (gp16c4t3en<<RCU_APB1RST_GP16C4T3EN_POS)
/**
  * @} MD_RCU_APB1RST_GP16C4T3EN
  */
/** @defgroup MD_RCU_APB1RST_GP16C4T2EN GP16C4T2EN
  * @brief  Set GP16C4T2 reset request bit for md_rcu_set_apb1rst() function used
  * @param  gp16c4t2en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb1rst_gp16c4t2en_fun(gp16c4t2en)  (gp16c4t2en<<RCU_APB1RST_GP16C4T2EN_POS)
/**
  * @} MD_RCU_APB1RST_GP16C4T2EN
  */
/** @defgroup MD_RCU_APB1RST_GP16C4T1EN GP16C4T1EN
  * @brief  Set GP16C4T1 reset request bit for md_rcu_set_apb1rst() function used
  * @param  gp16c4t1en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb1rst_gp16c4t1en_fun(gp16c4t1en)  (gp16c4t1en<<RCU_APB1RST_GP16C4T1EN_POS)
/**
  * @} MD_RCU_APB1RST_GP16C4T1EN
  */
/** @defgroup MD_RCU_APB1RST_GP32C4T1EN GP32C4T1EN
  * @brief  Set GP32C4T1 reset request bit for md_rcu_set_apb1rst() function used
  * @param  gp32c4t1en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb1rst_gp32c4t1en_fun(gp32c4t1en)  (gp32c4t1en<<RCU_APB1RST_GP32C4T1EN_POS)
/**
  * @} MD_RCU_APB1RST_GP32C4T1EN
  */
/**
  * @brief  Set APB1 Peripheral Reset Register
  * @param  rcu RCU Instance
  * @param  dacen This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb1rst_dacen_fun(dacen)
  * @param  i2c2en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb1rst_i2c2en_fun(i2c2en)
  * @param  i2c1en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb1rst_i2c1en_fun(i2c1en)
  * @param  suart2en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb1rst_suart2en_fun(suart2en)
  * @param  suart1en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb1rst_suart1en_fun(suart1en)
  * @param  uart3en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb1rst_uart3en_fun(uart3en)
  * @param  uart2en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb1rst_uart2en_fun(uart2en)
  * @param  spi2en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb1rst_spi2en_fun(spi2en)
  * @param  iwdten This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb1rst_iwdten_fun(iwdten)
  * @param  wwdten This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb1rst_wwdten_fun(wwdten)
  * @param  bs16t1en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb1rst_bs16t1en_fun(bs16t1en)
  * @param  gp16c4t3en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb1rst_gp16c4t3en_fun(gp16c4t3en)
  * @param  gp16c4t2en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb1rst_gp16c4t2en_fun(gp16c4t2en)
  * @param  gp16c4t1en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb1rst_gp16c4t1en_fun(gp16c4t1en)
  * @param  gp32c4t1en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb1rst_gp32c4t1en_fun(gp32c4t1en)
  * @retval None
  */
__STATIC_INLINE void md_rcu_set_apb1rst(RCU_TypeDef *rcu, uint32_t dacen,      uint32_t i2c2en,     uint32_t i2c1en,
                                                          uint32_t suart2en,   uint32_t suart1en,   uint32_t uart3en,
                                                          uint32_t uart2en,    uint32_t spi2en,     uint32_t iwdten,
                                                          uint32_t wwdten,     uint32_t bs16t1en,   uint32_t gp16c4t3en,
                                                          uint32_t gp16c4t2en, uint32_t gp16c4t1en, uint32_t gp32c4t1en)
{
  WRITE_REG(rcu->APB1RST, (dacen|i2c2en|i2c1en|suart2en|suart1en|uart3en|uart2en|spi2en|iwdten|wwdten|
                           bs16t1en|gp16c4t3en|gp16c4t2en|gp16c4t1en|gp32c4t1en));
}

/**
  * @brief  CMP reset request enable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb2rst_cmpen(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB2RST, RCU_APB2RST_CMPEN_MSK);
}
/**
  * @brief  CMP reset request disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb2rst_cmpen(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB2RST, RCU_APB2RST_CMPEN_MSK);
}
/**
  * @brief  Get CMP reset request bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb2rst_cmpen(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB2RST, RCU_APB2RST_CMPEN_MSK)>>RCU_APB2RST_CMPEN_POS);
}
/**
  * @brief  GP16C2T4 reset request enable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb2rst_gp16c2t4en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB2RST, RCU_APB2RST_GP16C2T4EN_MSK);
}
/**
  * @brief  GP16C2T4 reset request disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb2rst_gp16c2t4en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB2RST, RCU_APB2RST_GP16C2T4EN_MSK);
}
/**
  * @brief  Get GP16C2T4 reset request bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb2rst_gp16c2t4en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB2RST, RCU_APB2RST_GP16C2T4EN_MSK)>>RCU_APB2RST_GP16C2T4EN_POS);
}
/**
  * @brief  GP16C2T3 reset request enable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb2rst_gp16c2t3en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB2RST, RCU_APB2RST_GP16C2T3EN_MSK);
}
/**
  * @brief  GP16C2T3 reset request disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb2rst_gp16c2t3en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB2RST, RCU_APB2RST_GP16C2T3EN_MSK);
}
/**
  * @brief  Get GP16C2T3 reset request bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb2rst_gp16c2t3en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB2RST, RCU_APB2RST_GP16C2T3EN_MSK)>>RCU_APB2RST_GP16C2T3EN_POS);
}
/**
  * @brief  GP16C2T2 reset request enable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb2rst_gp16c2t2en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB2RST, RCU_APB2RST_GP16C2T2EN_MSK);
}
/**
  * @brief  GP16C2T2 reset request disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb2rst_gp16c2t2en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB2RST, RCU_APB2RST_GP16C2T2EN_MSK);
}
/**
  * @brief  Get GP16C2T2 reset request bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb2rst_gp16c2t2en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB2RST, RCU_APB2RST_GP16C2T2EN_MSK)>>RCU_APB2RST_GP16C2T2EN_POS);
}
/**
  * @brief  GP16C2T1 reset request enable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb2rst_gp16c2t1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB2RST, RCU_APB2RST_GP16C2T1EN_MSK);
}
/**
  * @brief  GP16C2T1 reset request disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb2rst_gp16c2t1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB2RST, RCU_APB2RST_GP16C2T1EN_MSK);
}
/**
  * @brief  Get GP16C2T1 reset request bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb2rst_gp16c2t1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB2RST, RCU_APB2RST_GP16C2T1EN_MSK)>>RCU_APB2RST_GP16C2T1EN_POS);
}
/**
  * @brief  UART1 reset request enable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb2rst_uart1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB2RST, RCU_APB2RST_UART1EN_MSK);
}
/**
  * @brief  UART1 reset request disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb2rst_uart1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB2RST, RCU_APB2RST_UART1EN_MSK);
}
/**
  * @brief  Get UART1 reset request bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb2rst_uart1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB2RST, RCU_APB2RST_UART1EN_MSK)>>RCU_APB2RST_UART1EN_POS);
}
/**
  * @brief  SPI1 reset request enable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb2rst_spi1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB2RST, RCU_APB2RST_SPI1EN_MSK);
}
/**
  * @brief  SPI1 reset request disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb2rst_spi1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB2RST, RCU_APB2RST_SPI1EN_MSK);
}
/**
  * @brief  Get SPI1 reset request bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb2rst_spi1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB2RST, RCU_APB2RST_SPI1EN_MSK)>>RCU_APB2RST_SPI1EN_POS);
}
/**
  * @brief  AD16C4T1 reset request enable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb2rst_ad16c4t1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB2RST, RCU_APB2RST_AD16C4T1EN_MSK);
}
/**
  * @brief  AD16C4T1 reset request disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb2rst_ad16c4t1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB2RST, RCU_APB2RST_AD16C4T1EN_MSK);
}
/**
  * @brief  Get AD16C4T1 reset request bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb2rst_ad16c4t1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB2RST, RCU_APB2RST_AD16C4T1EN_MSK)>>RCU_APB2RST_AD16C4T1EN_POS);
}
/**
  * @brief  ADC reset request enable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb2rst_adcen(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB2RST, RCU_APB2RST_ADCEN_MSK);
}
/**
  * @brief  ADC reset request disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb2rst_adcen(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB2RST, RCU_APB2RST_ADCEN_MSK);
}
/**
  * @brief  Get ADC reset request bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb2rst_adcen(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB2RST, RCU_APB2RST_ADCEN_MSK)>>RCU_APB2RST_ADCEN_POS);
}

/** @defgroup MD_RCU_APB2RST_CMPEN CMPEN
  * @brief  Set CMP reset request bit for md_rcu_set_apb2rst() function used
  * @param  cmpen This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb2rst_cmpen_fun(cmpen)  (cmpen<<RCU_APB2RST_CMPEN_POS)
/**
  * @} MD_RCU_APB2RST_CMPEN
  */
/** @defgroup MD_RCU_APB2RST_GP16C2T4EN GP16C2T4EN
  * @brief  Set GP16C2T4 reset request bit for md_rcu_set_apb2rst() function used
  * @param  gp16c2t4en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb2rst_gp16c2t4en_fun(gp16c2t4en)  (gp16c2t4en<<RCU_APB2RST_GP16C2T4EN_POS)
/**
  * @} MD_RCU_APB2RST_GP16C2T4EN
  */
/** @defgroup MD_RCU_APB2RST_GP16C2T3EN GP16C2T3EN
  * @brief  Set GP16C2T3 reset request bit for md_rcu_set_apb2rst() function used
  * @param  gp16c2t3en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb2rst_gp16c2t3en_fun(gp16c2t3en)  (gp16c2t3en<<RCU_APB2RST_GP16C2T3EN_POS)
/**
  * @} MD_RCU_APB2RST_GP16C2T3EN
  */
/** @defgroup MD_RCU_APB2RST_GP16C2T2EN GP16C2T2EN
  * @brief  Set GP16C2T2 reset request bit for md_rcu_set_apb2rst() function used
  * @param  gp16c2t2en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb2rst_gp16c2t2en_fun(gp16c2t2en)  (gp16c2t2en<<RCU_APB2RST_GP16C2T2EN_POS)
/**
  * @} MD_RCU_APB2RST_GP16C2T2EN
  */
/** @defgroup MD_RCU_APB2RST_GP16C2T1EN GP16C2T1EN
  * @brief  Set GP16C2T1 reset request bit for md_rcu_set_apb2rst() function used
  * @param  gp16c2t1en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb2rst_gp16c2t1en_fun(gp16c2t1en)  (gp16c2t1en<<RCU_APB2RST_GP16C2T1EN_POS)
/**
  * @} MD_RCU_APB2RST_GP16C2T1EN
  */
/** @defgroup MD_RCU_APB2RST_UART1EN UART1EN
  * @brief  Set UART1 reset request bit for md_rcu_set_apb2rst() function used
  * @param  uart1en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb2rst_uart1en_fun(uart1en)  (uart1en<<RCU_APB2RST_UART1EN_POS)
/**
  * @} MD_RCU_APB2RST_UART1EN
  */
/** @defgroup MD_RCU_APB2RST_SPI1EN SPI1EN
  * @brief  Set SPI1 reset request bit for md_rcu_set_apb2rst() function used
  * @param  spi1en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb2rst_spi1en_fun(spi1en)  (spi1en<<RCU_APB2RST_SPI1EN_POS)
/**
  * @} MD_RCU_APB2RST_SPI1EN
  */
/** @defgroup MD_RCU_APB2RST_AD16C4T1EN AD16C4T1EN
  * @brief  Set AD16C4T1 reset request bit for md_rcu_set_apb2rst() function used
  * @param  ad16c4t1en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb2rst_ad16c4t1en_fun(ad16c4t1en)  (ad16c4t1en<<RCU_APB2RST_AD16C4T1EN_POS)
/**
  * @} MD_RCU_APB2RST_AD16C4T1EN
  */
/** @defgroup MD_RCU_APB2RST_ADCEN ADCEN
  * @brief  Set ADC reset request bit for md_rcu_set_apb2rst() function used
  * @param  adcen This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb2rst_adcen_fun(adcen)  (adcen<<RCU_APB2RST_ADCEN_POS)
/**
  * @} MD_RCU_APB2RST_ADCEN
  */
/**
  * @brief  Set APB1 Peripheral Reset Register
  * @param  rcu RCU Instance
  * @param  cmpen This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb2rst_cmpen_fun(cmpen)
  * @param  gp16c2t4en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb2rst_gp16c2t4en_fun(gp16c2t4en)
  * @param  gp16c2t3en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb2rst_gp16c2t3en_fun(gp16c2t3en)
  * @param  gp16c2t2en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb2rst_gp16c2t2en_fun(gp16c2t2en)
  * @param  gp16c2t1en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb2rst_gp16c2t1en_fun(gp16c2t1en)
  * @param  uart1en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb2rst_uart1en_fun(uart1en)
  * @param  spi1en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb2rst_spi1en_fun(spi1en)
  * @param  ad16c4t1en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb2rst_ad16c4t1en_fun(ad16c4t1en)
  * @param  adcen This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb2rst_adcen_fun(adcen)
  * @retval None
  */
__STATIC_INLINE void md_rcu_set_apb2rst(RCU_TypeDef *rcu, uint32_t cmpen,
                                                          uint32_t gp16c2t4en, uint32_t gp16c2t3en, uint32_t gp16c2t2en,
                                                          uint32_t gp16c2t1en, uint32_t uart1en,    uint32_t spi1en,
                                                          uint32_t ad16c4t1en, uint32_t adcen)
{
  WRITE_REG(rcu->APB2RST, (cmpen|gp16c2t4en|gp16c2t3en|gp16c2t2en|gp16c2t1en|uart1en|spi1en|ad16c4t1en|adcen));
}

/**
  * @brief  GPIOD clock enable bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahben_gpden(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBEN, RCU_AHBEN_GPDEN_MSK);
}
/**
  * @brief  GPIOD Clock disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahben_gpden(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBEN, RCU_AHBEN_GPDEN_MSK);
}
/**
  * @brief  Get GPIOD Clock bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahben_gpden(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBEN, RCU_AHBEN_GPDEN_MSK)>>RCU_AHBEN_GPDEN_POS);
}
/**
  * @brief  GPIOC clock enable bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahben_gpcen(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBEN, RCU_AHBEN_GPCEN_MSK);
}
/**
  * @brief  GPIOC Clock disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahben_gpcen(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBEN, RCU_AHBEN_GPCEN_MSK);
}
/**
  * @brief  Get GPIOC Clock bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahben_gpcen(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBEN, RCU_AHBEN_GPCEN_MSK)>>RCU_AHBEN_GPCEN_POS);
}
/**
  * @brief  GPIOB clock enable bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahben_gpben(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBEN, RCU_AHBEN_GPBEN_MSK);
}
/**
  * @brief  GPIOB Clock disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahben_gpben(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBEN, RCU_AHBEN_GPBEN_MSK);
}
/**
  * @brief  Get GPIOB Clock bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahben_gpben(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBEN, RCU_AHBEN_GPBEN_MSK)>>RCU_AHBEN_GPBEN_POS);
}
/**
  * @brief  GPIOA clock enable bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahben_gpaen(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBEN, RCU_AHBEN_GPAEN_MSK);
}
/**
  * @brief  GPIOA Clock disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahben_gpaen(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBEN, RCU_AHBEN_GPAEN_MSK);
}
/**
  * @brief  Get GPIOA Clock bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahben_gpaen(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBEN, RCU_AHBEN_GPAEN_MSK)>>RCU_AHBEN_GPAEN_POS);
}
/**
  * @brief  HDIV clock enable bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahben_hdiven(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBEN, RCU_AHBEN_HDIVEN_MSK);
}
/**
  * @brief  HDIV Clock disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahben_hdiven(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBEN, RCU_AHBEN_HDIVEN_MSK);
}
/**
  * @brief  Get HDIV Clock bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahben_hdiven(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBEN, RCU_AHBEN_HDIVEN_MSK)>>RCU_AHBEN_HDIVEN_POS);
}
/**
  * @brief  USB clock enable bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahben_usben(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBEN, RCU_AHBEN_USBEN_MSK);
}
/**
  * @brief  USB Clock disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahben_usben(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBEN, RCU_AHBEN_USBEN_MSK);
}
/**
  * @brief  Get USB Clock bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahben_usben(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBEN, RCU_AHBEN_USBEN_MSK)>>RCU_AHBEN_USBEN_POS);
}
/**
  * @brief  AES clock enable bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahben_aesen(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBEN, RCU_AHBEN_AESEN_MSK);
}
/**
  * @brief  AES Clock disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahben_aesen(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBEN, RCU_AHBEN_AESEN_MSK);
}
/**
  * @brief  Get AES Clock bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahben_aesen(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBEN, RCU_AHBEN_AESEN_MSK)>>RCU_AHBEN_AESEN_POS);
}
/**
  * @brief  CRC clock enable bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahben_crcen(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBEN, RCU_AHBEN_CRCEN_MSK);
}
/**
  * @brief  CRC Clock disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahben_crcen(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBEN, RCU_AHBEN_CRCEN_MSK);
}
/**
  * @brief  Get CRC Clock bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahben_crcen(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBEN, RCU_AHBEN_CRCEN_MSK)>>RCU_AHBEN_CRCEN_POS);
}
/**
  * @brief  RTC clock enable bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahben_rtcen(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBEN, RCU_AHBEN_RTCEN_MSK);
}
/**
  * @brief  RTC Clock disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahben_rtcen(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBEN, RCU_AHBEN_RTCEN_MSK);
}
/**
  * @brief  Get RTC Clock bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahben_rtcen(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBEN, RCU_AHBEN_RTCEN_MSK)>>RCU_AHBEN_RTCEN_POS);
}
/**
  * @brief  DMA1 clock enable bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahben_dma1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBEN, RCU_AHBEN_DMA1EN_MSK);
}
/**
  * @brief  DMA1 Clock disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahben_dma1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBEN, RCU_AHBEN_DMA1EN_MSK);
}
/**
  * @brief  Get DMA1 Clock bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahben_dma1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBEN, RCU_AHBEN_DMA1EN_MSK)>>RCU_AHBEN_DMA1EN_POS);
}

/** @defgroup MD_RCU_AHBEN_GPDEN GPDEN
  * @brief  Set GPIOD clock bit for md_rcu_set_ahben() function used
  * @param  gpden This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_ahben_gpden_fun(gpden)  (gpden<<RCU_AHBEN_GPDEN_POS)
/**
  * @} MD_RCU_AHBEN_GPDEN
  */
/** @defgroup MD_RCU_AHBEN_GPCEN GPCEN
  * @brief  Set GPIOC clock bit for md_rcu_set_ahben() function used
  * @param  gpcen This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_ahben_gpcen_fun(gpcen)  (gpcen<<RCU_AHBEN_GPCEN_POS)
/**
  * @} MD_RCU_AHBEN_GPCEN
  */
/** @defgroup MD_RCU_AHBEN_GPBEN GPBEN
  * @brief  Set GPIOB clock bit for md_rcu_set_ahben() function used
  * @param  gpben This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_ahben_gpben_fun(gpben)  (gpben<<RCU_AHBEN_GPBEN_POS)
/**
  * @} MD_RCU_AHBEN_GPBEN
  */
/** @defgroup MD_RCU_AHBEN_GPAEN GPAEN
  * @brief  Set GPIOA clock bit for md_rcu_set_ahben() function used
  * @param  gpaen This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_ahben_gpaen_fun(gpaen)  (gpaen<<RCU_AHBEN_GPAEN_POS)
/**
  * @} MD_RCU_AHBEN_GPAEN
  */
/** @defgroup MD_RCU_AHBEN_HDIVEN HDIVEN
  * @brief  Set HDIV clock bit for md_rcu_set_ahben() function used
  * @param  hdiven This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_ahben_hdiven_fun(hdiven)  (hdiven<<RCU_AHBEN_HDIVEN_POS)
/**
  * @} MD_RCU_AHBEN_HDIVEN
  */
/** @defgroup MD_RCU_AHBEN_USBEN USBEN
  * @brief  Set USB clock bit for md_rcu_set_ahben() function used
  * @param  usben This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_ahben_usben_fun(usben)  (usben<<RCU_AHBEN_USBEN_POS)
/**
  * @} MD_RCU_AHBEN_USBEN
  */
/** @defgroup MD_RCU_AHBEN_AESEN AESEN
  * @brief  Set AES clock bit for md_rcu_set_ahben() function used
  * @param  aesen This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_ahben_aesen_fun(aesen)  (aesen<<RCU_AHBEN_AESEN_POS)
/**
  * @} MD_RCU_AHBEN_AESEN
  */
/** @defgroup MD_RCU_AHBEN_CRCEN CRCEN
  * @brief  Set CRC clock bit for md_rcu_set_ahben() function used
  * @param  crcen This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_ahben_crcen_fun(crcen)  (crcen<<RCU_AHBEN_CRCEN_POS)
/**
  * @} MD_RCU_AHBEN_CRCEN
  */
/** @defgroup MD_RCU_AHBEN_RTCEN RTCEN
  * @brief  Set RTC clock bit for md_rcu_set_ahben() function used
  * @param  rtcen This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_ahben_rtcen_fun(rtcen)  (rtcen<<RCU_AHBEN_RTCEN_POS)
/**
  * @} MD_RCU_AHBEN_RTCEN
  */
/** @defgroup MD_RCU_AHBEN_DMA1EN DMA1EN
  * @brief  Set DMA1 clock bit for md_rcu_set_ahben() function used
  * @param  dma1en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_ahben_dma1en_fun(dma1en)  (dma1en<<RCU_AHBEN_DMA1EN_POS)
/**
  * @} MD_RCU_AHBEN_DMA1EN
  */
/**
  * @brief  Set APB1 Peripheral Reset Register
  * @param  rcu RCU Instance
  * @param  gpden This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_ahben_gpden_fun(gpden)
  * @param  gpcen This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_ahben_gpcen_fun(gpcen)
  * @param  gpben This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_ahben_gpben_fun(gpben)
  * @param  gpaen This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_ahben_gpaen_fun(gpaen)
  * @param  hdiven This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_ahben_hdiven_fun(hdiven)
  * @param  usben This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_ahben_usben_fun(usben)
  * @param  aesen This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_ahben_aesen_fun(aesen)
  * @param  crcen This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_ahben_crcen_fun(crcen)
  * @param  rtcen This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_ahben_rtcen_fun(rtcen)
  * @param  dma1en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_ahben_dma1en_fun(dma1en)
  * @retval None
  */
__STATIC_INLINE void md_rcu_set_ahben(RCU_TypeDef *rcu, uint32_t gpden, uint32_t gpcen,   uint32_t gpben,
                                                        uint32_t gpaen, uint32_t hdiven,  uint32_t usben,
                                                        uint32_t aesen, uint32_t crcen,   uint32_t rtcen,
                                                        uint32_t dma1en)
{
  WRITE_REG(rcu->AHBEN, (gpden|gpcen|gpben|gpaen|hdiven|usben|aesen|crcen|rtcen|dma1en));
}

/**
  * @brief  DAC clock enable bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1en_dacen(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1EN, RCU_APB1EN_DACEN_MSK);
}
/**
  * @brief  DAC Clock disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1en_dacen(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1EN, RCU_APB1EN_DACEN_MSK);
}
/**
  * @brief  Get DAC Clock bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1en_dacen(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1EN, RCU_APB1EN_DACEN_MSK)>>RCU_APB1EN_DACEN_POS);
}
/**
  * @brief  I2C2 clock enable bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1en_i2c2en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1EN, RCU_APB1EN_I2C2EN_MSK);
}
/**
  * @brief  I2C2 Clock disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1en_i2c2en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1EN, RCU_APB1EN_I2C2EN_MSK);
}
/**
  * @brief  Get I2C2 Clock bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1en_i2c2en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1EN, RCU_APB1EN_I2C2EN_MSK)>>RCU_APB1EN_I2C2EN_POS);
}
/**
  * @brief  I2C1 clock enable bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1en_i2c1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1EN, RCU_APB1EN_I2C1EN_MSK);
}
/**
  * @brief  I2C1 Clock disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1en_i2c1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1EN, RCU_APB1EN_I2C1EN_MSK);
}
/**
  * @brief  Get I2C1 Clock bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1en_i2c1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1EN, RCU_APB1EN_I2C1EN_MSK)>>RCU_APB1EN_I2C1EN_POS);
}
/**
  * @brief  SUART2 clock enable bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1en_suart2en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1EN, RCU_APB1EN_SUART2EN_MSK);
}
/**
  * @brief  SUART2 Clock disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1en_suart2en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1EN, RCU_APB1EN_SUART2EN_MSK);
}
/**
  * @brief  Get SUART2 Clock bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1en_suart2en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1EN, RCU_APB1EN_SUART2EN_MSK)>>RCU_APB1EN_SUART2EN_POS);
}
/**
  * @brief  SUART1 clock enable bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1en_suart1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1EN, RCU_APB1EN_SUART1EN_MSK);
}
/**
  * @brief  SUART1 Clock disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1en_suart1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1EN, RCU_APB1EN_SUART1EN_MSK);
}
/**
  * @brief  Get SUART1 Clock bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1en_suart1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1EN, RCU_APB1EN_SUART1EN_MSK)>>RCU_APB1EN_SUART1EN_POS);
}
/**
  * @brief  UART3 clock enable bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1en_uart3en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1EN, RCU_APB1EN_UART3EN_MSK);
}
/**
  * @brief  UART3 Clock disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1en_uart3en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1EN, RCU_APB1EN_UART3EN_MSK);
}
/**
  * @brief  Get UART3 Clock bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1en_uart3en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1EN, RCU_APB1EN_UART3EN_MSK)>>RCU_APB1EN_UART3EN_POS);
}
/**
  * @brief  UART2 clock enable bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1en_uart2en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1EN, RCU_APB1EN_UART2EN_MSK);
}
/**
  * @brief  UART2 Clock disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1en_uart2en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1EN, RCU_APB1EN_UART2EN_MSK);
}
/**
  * @brief  Get UART2 Clock bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1en_uart2en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1EN, RCU_APB1EN_UART2EN_MSK)>>RCU_APB1EN_UART2EN_POS);
}
/**
  * @brief  SPI2 clock enable bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1en_spi2en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1EN, RCU_APB1EN_SPI2EN_MSK);
}
/**
  * @brief  SPI2 Clock disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1en_spi2en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1EN, RCU_APB1EN_SPI2EN_MSK);
}
/**
  * @brief  Get SPI2 Clock bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1en_spi2en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1EN, RCU_APB1EN_SPI2EN_MSK)>>RCU_APB1EN_SPI2EN_POS);
}
/**
  * @brief  IWDT clock enable bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1en_iwdten(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1EN, RCU_APB1EN_IWDTEN_MSK);
}
/**
  * @brief  IWDT Clock disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1en_iwdten(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1EN, RCU_APB1EN_IWDTEN_MSK);
}
/**
  * @brief  Get IWDT Clock bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1en_iwdten(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1EN, RCU_APB1EN_IWDTEN_MSK)>>RCU_APB1EN_IWDTEN_POS);
}
/**
  * @brief  WWDT clock enable bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1en_wwdten(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1EN, RCU_APB1EN_WWDTEN_MSK);
}
/**
  * @brief  WWDT Clock disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1en_wwdten(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1EN, RCU_APB1EN_WWDTEN_MSK);
}
/**
  * @brief  Get WWDT Clock bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1en_wwdten(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1EN, RCU_APB1EN_WWDTEN_MSK)>>RCU_APB1EN_WWDTEN_POS);
}
/**
  * @brief  BS16T1 clock enable bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1en_bs16t1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1EN, RCU_APB1EN_BS16T1EN_MSK);
}
/**
  * @brief  BS16T1 Clock disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1en_bs16t1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1EN, RCU_APB1EN_BS16T1EN_MSK);
}
/**
  * @brief  Get BS16T1 Clock bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1en_bs16t1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1EN, RCU_APB1EN_BS16T1EN_MSK)>>RCU_APB1EN_BS16T1EN_POS);
}
/**
  * @brief  GP16C4T3 clock enable bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1en_gp16c4t3en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1EN, RCU_APB1EN_GP16C4T3EN_MSK);
}
/**
  * @brief  GP16C4T3 Clock disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1en_gp16c4t3en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1EN, RCU_APB1EN_GP16C4T3EN_MSK);
}
/**
  * @brief  Get GP16C4T3 Clock bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1en_gp16c4t3en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1EN, RCU_APB1EN_GP16C4T3EN_MSK)>>RCU_APB1EN_GP16C4T3EN_POS);
}
/**
  * @brief  GP16C4T2 clock enable bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1en_gp16c4t2en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1EN, RCU_APB1EN_GP16C4T2EN_MSK);
}
/**
  * @brief  GP16C4T2 Clock disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1en_gp16c4t2en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1EN, RCU_APB1EN_GP16C4T2EN_MSK);
}
/**
  * @brief  Get GP16C4T2 Clock bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1en_gp16c4t2en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1EN, RCU_APB1EN_GP16C4T2EN_MSK)>>RCU_APB1EN_GP16C4T2EN_POS);
}
/**
  * @brief  GP16C4T1 clock enable bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1en_gp16c4t1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1EN, RCU_APB1EN_GP16C4T1EN_MSK);
}
/**
  * @brief  GP16C4T1 Clock disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1en_gp16c4t1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1EN, RCU_APB1EN_GP16C4T1EN_MSK);
}
/**
  * @brief  Get GP16C4T1 Clock bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1en_gp16c4t1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1EN, RCU_APB1EN_GP16C4T1EN_MSK)>>RCU_APB1EN_GP16C4T1EN_POS);
}
/**
  * @brief  GP32C4T1 clock enable bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1en_gp32c4t1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1EN, RCU_APB1EN_GP32C4T1EN_MSK);
}
/**
  * @brief  GP32C4T1 Clock disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1en_gp32c4t1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1EN, RCU_APB1EN_GP32C4T1EN_MSK);
}
/**
  * @brief  Get GP32C4T1 Clock bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1en_gp32c4t1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1EN, RCU_APB1EN_GP32C4T1EN_MSK)>>RCU_APB1EN_GP32C4T1EN_POS);
}

/** @defgroup MD_RCU_APB1EN_DACEN DACEN
  * @brief  Set DAC clock bit for md_rcu_set_apb1en() function used
  * @param  dacen This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb1en_dacen_fun(dacen)  (dacen<<RCU_APB1EN_DACEN_POS)
/**
  * @} MD_RCU_APB1EN_DACEN
  */
/** @defgroup MD_RCU_APB1EN_I2C2EN I2C2EN
  * @brief  Set I2C2 clock bit for md_rcu_set_apb1en() function used
  * @param  i2c2en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb1en_i2c2en_fun(i2c2en)  (i2c2en<<RCU_APB1EN_I2C2EN_POS)
/**
  * @} MD_RCU_APB1EN_I2C2EN
  */
/** @defgroup MD_RCU_APB1EN_I2C1EN I2C1EN
  * @brief  Set I2C1 clock bit for md_rcu_set_apb1en() function used
  * @param  i2c1en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb1en_i2c1en_fun(i2c1en)  (i2c1en<<RCU_APB1EN_I2C1EN_POS)
/**
  * @} MD_RCU_APB1EN_I2C1EN
  */
/** @defgroup MD_RCU_APB1EN_SUART2EN SUART2EN
  * @brief  Set SUART2 clock bit for md_rcu_set_apb1en() function used
  * @param  suart2en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb1en_suart2en_fun(suart2en)  (suart2en<<RCU_APB1EN_SUART2EN_POS)
/**
  * @} MD_RCU_APB1EN_SUART2EN
  */
/** @defgroup MD_RCU_APB1EN_SUART1EN SUART1EN
  * @brief  Set SUART1 clock bit for md_rcu_set_apb1en() function used
  * @param  suart1en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb1en_suart1en_fun(suart1en)  (suart1en<<RCU_APB1EN_SUART1EN_POS)
/**
  * @} MD_RCU_APB1EN_SUART1EN
  */
/** @defgroup MD_RCU_APB1EN_UART3EN UART3EN
  * @brief  Set UART3 clock bit for md_rcu_set_apb1en() function used
  * @param  uart3en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb1en_uart3en_fun(uart3en)  (uart3en<<RCU_APB1EN_UART3EN_POS)
/**
  * @} MD_RCU_APB1EN_UART3EN
  */
/** @defgroup MD_RCU_APB1EN_UART2EN UART2EN
  * @brief  Set UART2 clock bit for md_rcu_set_apb1en() function used
  * @param  uart2en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb1en_uart2en_fun(uart2en)  (uart2en<<RCU_APB1EN_UART2EN_POS)
/**
  * @} MD_RCU_APB1EN_UART2EN
  */
/** @defgroup MD_RCU_APB1EN_SPI2EN SPI2EN
  * @brief  Set SPI2 clock bit for md_rcu_set_apb1en() function used
  * @param  spi2en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb1en_spi2en_fun(spi2en)  (spi2en<<RCU_APB1EN_SPI2EN_POS)
/**
  * @} MD_RCU_APB1EN_SPI2EN
  */
/** @defgroup MD_RCU_APB1EN_IWDTEN IWDTEN
  * @brief  Set IWDT clock bit for md_rcu_set_apb1en() function used
  * @param  iwdten This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb1en_iwdten_fun(iwdten)  (iwdten<<RCU_APB1EN_IWDTEN_POS)
/**
  * @} MD_RCU_APB1EN_IWDTEN
  */
/** @defgroup MD_RCU_APB1EN_WWDTEN WWDTEN
  * @brief  Set WWDT clock bit for md_rcu_set_apb1en() function used
  * @param  wwdten This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb1en_wwdten_fun(wwdten)  (wwdten<<RCU_APB1EN_WWDTEN_POS)
/**
  * @} MD_RCU_APB1EN_WWDTEN
  */
/** @defgroup MD_RCU_APB1EN_BS16T1EN BS16T1EN
  * @brief  Set BS16T1 clock bit for md_rcu_set_apb1en() function used
  * @param  bs16t1en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb1en_bs16t1en_fun(bs16t1en)  (bs16t1en<<RCU_APB1EN_BS16T1EN_POS)
/**
  * @} MD_RCU_APB1EN_BS16T1EN
  */
/** @defgroup MD_RCU_APB1EN_GP16C4T3EN GP16C4T3EN
  * @brief  Set GP16C4T3 clock bit for md_rcu_set_apb1en() function used
  * @param  gp16c4t3en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb1en_gp16c4t3en_fun(gp16c4t3en)  (gp16c4t3en<<RCU_APB1EN_GP16C4T3EN_POS)
/**
  * @} MD_RCU_APB1EN_GP16C4T3EN
  */
/** @defgroup MD_RCU_APB1EN_GP16C4T2EN GP16C4T2EN
  * @brief  Set GP16C4T2 clock bit for md_rcu_set_apb1en() function used
  * @param  gp16c4t2en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb1en_gp16c4t2en_fun(gp16c4t2en)  (gp16c4t2en<<RCU_APB1EN_GP16C4T2EN_POS)
/**
  * @} MD_RCU_APB1EN_GP16C4T2EN
  */
/** @defgroup MD_RCU_APB1EN_GP16C4T1EN GP16C4T1EN
  * @brief  Set GP16C4T1 clock bit for md_rcu_set_apb1en() function used
  * @param  gp16c4t1en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb1en_gp16c4t1en_fun(gp16c4t1en)  (gp16c4t1en<<RCU_APB1EN_GP16C4T1EN_POS)
/**
  * @} MD_RCU_APB1EN_GP16C4T1EN
  */
/** @defgroup MD_RCU_APB1EN_GP32C4T1EN GP32C4T1EN
  * @brief  Set GP32C4T1 clock bit for md_rcu_set_apb1en() function used
  * @param  gp32c4t1en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb1en_gp32c4t1en_fun(gp32c4t1en)  (gp32c4t1en<<RCU_APB1EN_GP32C4T1EN_POS)
/**
  * @} MD_RCU_APB1EN_GP32C4T1EN
  */
/**
  * @brief  Set APB1 Peripheral Reset Register
  * @param  rcu RCU Instance
  * @param  dacen This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb1en_dacen_fun(dacen)
  * @param  i2c2en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb1en_i2c2en_fun(i2c2en)
  * @param  i2c1en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb1en_i2c1en_fun(i2c1en)
  * @param  suart2en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb1en_suart2en_fun(suart2en)
  * @param  suart1en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb1en_suart1en_fun(suart1en)
  * @param  uart3en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb1en_uart3en_fun(uart3en)
  * @param  uart2en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb1en_uart2en_fun(uart2en)
  * @param  spi2en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb1en_spi2en_fun(spi2en)
  * @param  iwdten This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb1en_iwdten_fun(iwdten)
  * @param  wwdten This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb1en_wwdten_fun(wwdten)
  * @param  bs16t1en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb1en_bs16t1en_fun(bs16t1en)
  * @param  gp16c4t3en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb1en_gp16c4t3en_fun(gp16c4t3en)
  * @param  gp16c4t2en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb1en_gp16c4t2en_fun(gp16c4t2en)
  * @param  gp16c4t1en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb1en_gp16c4t1en_fun(gp16c4t1en)
  * @param  gp32c4t1en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb1en_gp32c4t1en_fun(gp32c4t1en)
  * @retval None
  */
__STATIC_INLINE void md_rcu_set_apb1en(RCU_TypeDef *rcu, uint32_t dacen,      uint32_t i2c2en,      uint32_t i2c1en,
                                                         uint32_t suart2en,   uint32_t suart1en,    uint32_t uart3en,
                                                         uint32_t uart2en,    uint32_t spi2en,      uint32_t iwdten,
                                                         uint32_t wwdten,     uint32_t bs16t1en,    uint32_t gp16c4t3en,
                                                         uint32_t gp16c4t2en, uint32_t gp16c4t1en,  uint32_t gp32c4t1en)
{
  WRITE_REG(rcu->APB1EN, (dacen|i2c2en|i2c1en|suart2en|suart1en|uart3en|uart2en|spi2en|iwdten|wwdten|
                          bs16t1en|gp16c4t3en|gp16c4t2en|gp16c4t1en|gp32c4t1en));
}

/**
  * @brief  CMP clock enable bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb2en_cmpen(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB2EN, RCU_APB2EN_CMPEN_MSK);
}
/**
  * @brief  CMP Clock disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb2en_cmpen(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB2EN, RCU_APB2EN_CMPEN_MSK);
}
/**
  * @brief  Get CMP Clock bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb2en_cmpen(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB2EN, RCU_APB2EN_CMPEN_MSK)>>RCU_APB2EN_CMPEN_POS);
}
/**
  * @brief  GP16C2T4EN clock enable bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb2en_gp16c2t4en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB2EN, RCU_APB2EN_GP16C2T4EN_MSK);
}
/**
  * @brief  GP16C2T4EN Clock disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb2en_gp16c2t4en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB2EN, RCU_APB2EN_GP16C2T4EN_MSK);
}
/**
  * @brief  Get GP16C2T4EN Clock bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb2en_gp16c2t4en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB2EN, RCU_APB2EN_GP16C2T4EN_MSK)>>RCU_APB2EN_GP16C2T4EN_POS);
}
/**
  * @brief  GP16C2T3EN clock enable bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb2en_gp16c2t3en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB2EN, RCU_APB2EN_GP16C2T3EN_MSK);
}
/**
  * @brief  GP16C2T3EN Clock disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb2en_gp16c2t3en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB2EN, RCU_APB2EN_GP16C2T3EN_MSK);
}
/**
  * @brief  Get GP16C2T3EN Clock bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb2en_gp16c2t3en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB2EN, RCU_APB2EN_GP16C2T3EN_MSK)>>RCU_APB2EN_GP16C2T3EN_POS);
}
/**
  * @brief  GP16C2T2EN clock enable bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb2en_gp16c2t2en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB2EN, RCU_APB2EN_GP16C2T2EN_MSK);
}
/**
  * @brief  GP16C2T2EN Clock disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb2en_gp16c2t2en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB2EN, RCU_APB2EN_GP16C2T2EN_MSK);
}
/**
  * @brief  Get GP16C2T2EN Clock bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb2en_gp16c2t2en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB2EN, RCU_APB2EN_GP16C2T2EN_MSK)>>RCU_APB2EN_GP16C2T2EN_POS);
}
/**
  * @brief  GP16C2T1EN clock enable bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb2en_gp16c2t1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB2EN, RCU_APB2EN_GP16C2T1EN_MSK);
}
/**
  * @brief  GP16C2T1EN Clock disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb2en_gp16c2t1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB2EN, RCU_APB2EN_GP16C2T1EN_MSK);
}
/**
  * @brief  Get GP16C2T1EN Clock bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb2en_gp16c2t1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB2EN, RCU_APB2EN_GP16C2T1EN_MSK)>>RCU_APB2EN_GP16C2T1EN_POS);
}
/**
  * @brief  UART1EN clock enable bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb2en_uart1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB2EN, RCU_APB2EN_UART1EN_MSK);
}
/**
  * @brief  UART1EN Clock disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb2en_uart1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB2EN, RCU_APB2EN_UART1EN_MSK);
}
/**
  * @brief  Get UART1EN Clock bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb2en_uart1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB2EN, RCU_APB2EN_UART1EN_MSK)>>RCU_APB2EN_UART1EN_POS);
}
/**
  * @brief  SPI1EN clock enable bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb2en_spi1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB2EN, RCU_APB2EN_SPI1EN_MSK);
}
/**
  * @brief  SPI1EN Clock disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb2en_spi1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB2EN, RCU_APB2EN_SPI1EN_MSK);
}
/**
  * @brief  Get SPI1EN Clock bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb2en_spi1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB2EN, RCU_APB2EN_SPI1EN_MSK)>>RCU_APB2EN_SPI1EN_POS);
}
/**
  * @brief  AD16C4T1EN clock enable bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb2en_ad16c4t1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB2EN, RCU_APB2EN_AD16C4T1EN_MSK);
}
/**
  * @brief  AD16C4T1EN Clock disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb2en_ad16c4t1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB2EN, RCU_APB2EN_AD16C4T1EN_MSK);
}
/**
  * @brief  Get AD16C4T1EN Clock bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb2en_ad16c4t1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB2EN, RCU_APB2EN_AD16C4T1EN_MSK)>>RCU_APB2EN_AD16C4T1EN_POS);
}
/**
  * @brief  ADCEN clock enable bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb2en_adcen(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB2EN, RCU_APB2EN_ADCEN_MSK);
}
/**
  * @brief  ADCEN Clock disable bit
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb2en_adcen(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB2EN, RCU_APB2EN_ADCEN_MSK);
}
/**
  * @brief  Get ADCEN Clock bit
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb2en_adcen(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB2EN, RCU_APB2EN_ADCEN_MSK)>>RCU_APB2EN_ADCEN_POS);
}

/** @defgroup MD_RCU_APB2EN_CMPEN CMPEN
  * @brief  Set CMP clock bit for md_rcu_set_apb2en() function used
  * @param  cmpen This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb2en_cmpen_fun(cmpen)  (cmpen<<RCU_APB2EN_CMPEN_POS)
/**
  * @} MD_RCU_APB2EN_CMPEN
  */
/** @defgroup MD_RCU_APB2EN_GP16C2T4EN GP16C2T4EN
  * @brief  Set GP16C2T4EN clock bit for md_rcu_set_apb2en() function used
  * @param  gp16c2t4en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb2en_gp16c2t4en_fun(gp16c2t4en)  (gp16c2t4en<<RCU_APB2EN_GP16C2T4EN_POS)
/**
  * @} MD_RCU_APB2EN_GP16C2T4EN
  */
/** @defgroup MD_RCU_APB2EN_GP16C2T3EN GP16C2T3EN
  * @brief  Set GP16C2T3EN clock bit for md_rcu_set_apb2en() function used
  * @param  gp16c2t3en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb2en_gp16c2t3en_fun(gp16c2t3en)  (gp16c2t3en<<RCU_APB2EN_GP16C2T3EN_POS)
/**
  * @} MD_RCU_APB2EN_GP16C2T3EN
  */
/** @defgroup MD_RCU_APB2EN_GP16C2T2EN GP16C2T2EN
  * @brief  Set GP16C2T2EN clock bit for md_rcu_set_apb2en() function used
  * @param  gp16c2t2en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb2en_gp16c2t2en_fun(gp16c2t2en)  (gp16c2t2en<<RCU_APB2EN_GP16C2T2EN_POS)
/**
  * @} MD_RCU_APB2EN_GP16C2T2EN
  */
/** @defgroup MD_RCU_APB2EN_GP16C2T1EN GP16C2T1EN
  * @brief  Set GP16C2T1EN clock bit for md_rcu_set_apb2en() function used
  * @param  gp16c2t1en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb2en_gp16c2t1en_fun(gp16c2t1en)  (gp16c2t1en<<RCU_APB2EN_GP16C2T1EN_POS)
/**
  * @} MD_RCU_APB2EN_GP16C2T1EN
  */
/** @defgroup MD_RCU_APB2EN_UART1EN UART1EN
  * @brief  Set UART1EN clock bit for md_rcu_set_apb2en() function used
  * @param  uart1en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb2en_uart1en_fun(uart1en)  (uart1en<<RCU_APB2EN_UART1EN_POS)
/**
  * @} MD_RCU_APB2EN_UART1EN
  */
/** @defgroup MD_RCU_APB2EN_SPI1EN SPI1EN
  * @brief  Set SPI1EN clock bit for md_rcu_set_apb2en() function used
  * @param  spi1en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb2en_spi1en_fun(spi1en)  (spi1en<<RCU_APB2EN_SPI1EN_POS)
/**
  * @} MD_RCU_APB2EN_SPI1EN
  */
/** @defgroup MD_RCU_APB2EN_AD16C4T1EN AD16C4T1EN
  * @brief  Set AD16C4T1EN clock bit for md_rcu_set_apb2en() function used
  * @param  ad16c4t1en This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb2en_ad16c4t1en_fun(ad16c4t1en)  (ad16c4t1en<<RCU_APB2EN_AD16C4T1EN_POS)
/**
  * @} MD_RCU_APB2EN_AD16C4T1EN
  */
/** @defgroup MD_RCU_APB2EN_ADCEN ADCEN
  * @brief  Set ADCEN clock bit for md_rcu_set_apb2en() function used
  * @param  adcen This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_rcu_set_apb2en_adcen_fun(adcen)  (adcen<<RCU_APB2EN_ADCEN_POS)
/**
  * @} MD_RCU_APB2EN_ADCEN
  */
/**
  * @brief  Set APB2 Peripheral Reset Register
  * @param  rcu RCU Instance
  * @param  cmpen This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb2en_cmpen_fun(cmpen)
  * @param  gp16c2t4en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb2en_gp16c2t4en_fun(gp16c2t4en)
  * @param  gp16c2t3en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb2en_gp16c2t3en_fun(gp16c2t3en)
  * @param  gp16c2t2en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb2en_gp16c2t2en_fun(gp16c2t2en)
  * @param  gp16c2t1en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb2en_gp16c2t1en_fun(gp16c2t1en)
  * @param  uart1en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb2en_uart1en_fun(uart1en)
  * @param  spi1en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb2en_spi1en_fun(spi1en)
  * @param  ad16c4t1en This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb2en_ad16c4t1en_fun(ad16c4t1en)
  * @param  adcen This parameter can be one of the following values:
  *         @arg @ref md_rcu_set_apb2en_adcen_fun(adcen)
  * @retval None
  */
__STATIC_INLINE void md_rcu_set_apb2en(RCU_TypeDef *rcu, uint32_t cmpen,      
                                                         uint32_t gp16c2t4en, uint32_t gp16c2t3en,  uint32_t gp16c2t2en,
                                                         uint32_t gp16c2t1en, uint32_t uart1en,     uint32_t spi1en,
                                                         uint32_t ad16c4t1en, uint32_t adcen)
{
  WRITE_REG(rcu->APB2EN, (cmpen|gp16c2t4en|gp16c2t3en|gp16c2t2en|gp16c2t1en|uart1en|spi1en|ad16c4t1en|adcen));
}










/**
  * @brief  GPDEN clock enable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahbsl_gpden(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBSL, RCU_AHBSL_GPDEN_MSK);
}
/**
  * @brief  GPDEN clock disable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahbsl_gpden(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBSL, RCU_AHBSL_GPDEN_MSK);
}
/**
  * @brief  Get GPDEN clock during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahbsl_gpden(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBSL, RCU_AHBSL_GPDEN_MSK)>>RCU_AHBSL_GPDEN_POS);
}
/**
  * @brief  GPCEN clock enable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahbsl_gpcen(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBSL, RCU_AHBSL_GPCEN_MSK);
}
/**
  * @brief  GPCEN clock disable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahbsl_gpcen(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBSL, RCU_AHBSL_GPCEN_MSK);
}
/**
  * @brief  Get GPCEN clock during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahbsl_gpcen(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBSL, RCU_AHBSL_GPCEN_MSK)>>RCU_AHBSL_GPCEN_POS);
}
/**
  * @brief  GPBEN clock enable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahbsl_gpben(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBSL, RCU_AHBSL_GPBEN_MSK);
}
/**
  * @brief  GPBEN clock disable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahbsl_gpben(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBSL, RCU_AHBSL_GPBEN_MSK);
}
/**
  * @brief  Get GPBEN clock during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahbsl_gpben(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBSL, RCU_AHBSL_GPBEN_MSK)>>RCU_AHBSL_GPBEN_POS);
}
/**
  * @brief  GPAEN clock enable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahbsl_gpaen(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBSL, RCU_AHBSL_GPAEN_MSK);
}
/**
  * @brief  GPAEN clock disable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahbsl_gpaen(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBSL, RCU_AHBSL_GPAEN_MSK);
}
/**
  * @brief  Get GPAEN clock during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahbsl_gpaen(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBSL, RCU_AHBSL_GPAEN_MSK)>>RCU_AHBSL_GPAEN_POS);
}
/**
  * @brief  HDIVEN clock enable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahbsl_hdiven(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBSL, RCU_AHBSL_HDIVEN_MSK);
}
/**
  * @brief  HDIVEN clock disable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahbsl_hdiven(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBSL, RCU_AHBSL_HDIVEN_MSK);
}
/**
  * @brief  Get HDIVEN clock during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahbsl_hdiven(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBSL, RCU_AHBSL_HDIVEN_MSK)>>RCU_AHBSL_HDIVEN_POS);
}
/**
  * @brief  USBEN clock enable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahbsl_usben(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBSL, RCU_AHBSL_USBEN_MSK);
}
/**
  * @brief  USBEN clock disable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahbsl_usben(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBSL, RCU_AHBSL_USBEN_MSK);
}
/**
  * @brief  Get USBEN clock during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahbsl_usben(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBSL, RCU_AHBSL_USBEN_MSK)>>RCU_AHBSL_USBEN_POS);
}
/**
  * @brief  AESEN clock enable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahbsl_aesen(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBSL, RCU_AHBSL_AESEN_MSK);
}
/**
  * @brief  AESEN clock disable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahbsl_aesen(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBSL, RCU_AHBSL_AESEN_MSK);
}
/**
  * @brief  Get AESEN clock during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahbsl_aesen(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBSL, RCU_AHBSL_AESEN_MSK)>>RCU_AHBSL_AESEN_POS);
}
/**
  * @brief  CRCEN clock enable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahbsl_crcen(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBSL, RCU_AHBSL_CRCEN_MSK);
}
/**
  * @brief  CRCEN clock disable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahbsl_crcen(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBSL, RCU_AHBSL_CRCEN_MSK);
}
/**
  * @brief  Get CRCEN clock during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahbsl_crcen(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBSL, RCU_AHBSL_CRCEN_MSK)>>RCU_AHBSL_CRCEN_POS);
}
/**
  * @brief  RTCEN clock enable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahbsl_rtcen(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBSL, RCU_AHBSL_RTCEN_MSK);
}
/**
  * @brief  RTCEN clock disable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahbsl_rtcen(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBSL, RCU_AHBSL_RTCEN_MSK);
}
/**
  * @brief  Get RTCEN clock during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahbsl_rtcen(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBSL, RCU_AHBSL_RTCEN_MSK)>>RCU_AHBSL_RTCEN_POS);
}
/**
  * @brief  DMA1EN clock enable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahbsl_dma1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBSL, RCU_AHBSL_DMA1EN_MSK);
}
/**
  * @brief  DMA1EN clock disable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahbsl_dma1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBSL, RCU_AHBSL_DMA1EN_MSK);
}
/**
  * @brief  Get DMA1EN clock during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahbsl_dma1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBSL, RCU_AHBSL_DMA1EN_MSK)>>RCU_AHBSL_DMA1EN_POS);
}

/**
  * @brief  DAC clock enable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1sl_dacen(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1SL, RCU_APB1SL_DACEN_MSK);
}
/**
  * @brief  DAC clock disable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1sl_dacen(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1SL, RCU_APB1SL_DACEN_MSK);
}
/**
  * @brief  Get DAC clock during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1sl_dacen(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1SL, RCU_APB1SL_DACEN_MSK)>>RCU_APB1SL_DACEN_POS);
}
/**
  * @brief  I2C2EN clock enable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1sl_i2c2en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1SL, RCU_APB1SL_I2C2EN_MSK);
}
/**
  * @brief  I2C2EN clock disable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1sl_i2c2en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1SL, RCU_APB1SL_I2C2EN_MSK);
}
/**
  * @brief  Get I2C2EN clock during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1sl_i2c2en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1SL, RCU_APB1SL_I2C2EN_MSK)>>RCU_APB1SL_I2C2EN_POS);
}
/**
  * @brief  I2C1EN clock enable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1sl_i2c1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1SL, RCU_APB1SL_I2C1EN_MSK);
}
/**
  * @brief  I2C1EN clock disable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1sl_i2c1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1SL, RCU_APB1SL_I2C1EN_MSK);
}
/**
  * @brief  Get I2C1EN clock during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1sl_i2c1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1SL, RCU_APB1SL_I2C1EN_MSK)>>RCU_APB1SL_I2C1EN_POS);
}
/**
  * @brief  SUART2EN clock enable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1sl_suart2en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1SL, RCU_APB1SL_SUART2EN_MSK);
}
/**
  * @brief  SUART2EN clock disable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1sl_suart2en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1SL, RCU_APB1SL_SUART2EN_MSK);
}
/**
  * @brief  Get SUART2EN clock during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1sl_suart2en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1SL, RCU_APB1SL_SUART2EN_MSK)>>RCU_APB1SL_SUART2EN_POS);
}
/**
  * @brief  SUART1EN clock enable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1sl_suart1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1SL, RCU_APB1SL_SUART1EN_MSK);
}
/**
  * @brief  SUART1EN clock disable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1sl_suart1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1SL, RCU_APB1SL_SUART1EN_MSK);
}
/**
  * @brief  Get SUART1EN clock during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1sl_suart1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1SL, RCU_APB1SL_SUART1EN_MSK)>>RCU_APB1SL_SUART1EN_POS);
}
/**
  * @brief  UART3EN clock enable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1sl_uart3en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1SL, RCU_APB1SL_UART3EN_MSK);
}
/**
  * @brief  UART3EN clock disable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1sl_uart3en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1SL, RCU_APB1SL_UART3EN_MSK);
}
/**
  * @brief  Get UART3EN clock during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1sl_uart3en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1SL, RCU_APB1SL_UART3EN_MSK)>>RCU_APB1SL_UART3EN_POS);
}
/**
  * @brief  UART2EN clock enable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1sl_uart2en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1SL, RCU_APB1SL_UART2EN_MSK);
}
/**
  * @brief  UART2EN clock disable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1sl_uart2en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1SL, RCU_APB1SL_UART2EN_MSK);
}
/**
  * @brief  Get UART2EN clock during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1sl_uart2en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1SL, RCU_APB1SL_UART2EN_MSK)>>RCU_APB1SL_UART2EN_POS);
}
/**
  * @brief  SPI2EN clock enable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1sl_spi2en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1SL, RCU_APB1SL_SPI2EN_MSK);
}
/**
  * @brief  SPI2EN clock disable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1sl_spi2en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1SL, RCU_APB1SL_SPI2EN_MSK);
}
/**
  * @brief  Get SPI2EN clock during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1sl_spi2en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1SL, RCU_APB1SL_SPI2EN_MSK)>>RCU_APB1SL_SPI2EN_POS);
}
/**
  * @brief  IWDTEN clock enable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1sl_iwdten(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1SL, RCU_APB1SL_IWDTEN_MSK);
}
/**
  * @brief IWDTEN clock disable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1sl_iwdgen(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1SL, RCU_APB1SL_IWDTEN_MSK);
}
/**
  * @brief  Get IWDTEN clock during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1sl_iwdten(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1SL, RCU_APB1SL_IWDTEN_MSK)>>RCU_APB1SL_IWDTEN_POS);
}
/**
  * @brief  WWDTEN clock enable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1sl_wwdten(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1SL, RCU_APB1SL_WWDTEN_MSK);
}
/**
  * @brief WWDTEN clock disable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1sl_wwdten(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1SL, RCU_APB1SL_WWDTEN_MSK);
}
/**
  * @brief  Get WWDTEN clock during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1sl_wwdten(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1SL, RCU_APB1SL_WWDTEN_MSK)>>RCU_APB1SL_WWDTEN_POS);
}
/**
  * @brief  BS16T1EN clock enable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1sl_bs16t1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1SL, RCU_APB1SL_BS16T1EN_MSK);
}
/**
  * @brief  BS16T1EN clock disable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1sl_bs16t1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1SL, RCU_APB1SL_BS16T1EN_MSK);
}
/**
  * @brief  Get BS16T1EN clock during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1sl_bs16t1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1SL, RCU_APB1SL_BS16T1EN_MSK)>>RCU_APB1SL_BS16T1EN_POS);
}
/**
  * @brief  GP16C4T3EN clock enable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1sl_gp16c4t3en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1SL, RCU_APB1SL_GP16C4T3EN_MSK);
}
/**
  * @brief  GP16C4T3EN clock disable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1sl_gp16c4t3en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1SL, RCU_APB1SL_GP16C4T3EN_MSK);
}
/**
  * @brief  Get GP16C4T3EN clock during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1sl_gp16c4t3en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1SL, RCU_APB1SL_GP16C4T3EN_MSK)>>RCU_APB1SL_GP16C4T3EN_POS);
}
/**
  * @brief  GP16C4T2EN clock enable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1sl_gp16c4t2en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1SL, RCU_APB1SL_GP16C4T2EN_MSK);
}
/**
  * @brief  GP16C4T2EN clock disable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1sl_gp16c4t2en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1SL, RCU_APB1SL_GP16C4T2EN_MSK);
}
/**
  * @brief  Get GP16C4T2EN clock during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
y */
__STATIC_INLINE uint32_t md_rcu_get_apb1sl_gp16c4t2en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1SL, RCU_APB1SL_GP16C4T2EN_MSK)>>RCU_APB1SL_GP16C4T2EN_POS);
}
/**
  * @brief  GP16C4T1EN clock enable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1sl_gp16c4t1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1SL, RCU_APB1SL_GP16C4T1EN_MSK);
}
/**
  * @brief  GP16C4T1EN clock disable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1sl_gp16c4t1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1SL, RCU_APB1SL_GP16C4T1EN_MSK);
}
/**
  * @brief  Get GP16C4T1EN clock during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1sl_gp16c4t1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1SL, RCU_APB1SL_GP16C4T1EN_MSK)>>RCU_APB1SL_GP16C4T1EN_POS);
}
/**
  * @brief  GP32C4T1EN clock enable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1sl_gp32c4t1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1SL, RCU_APB1SL_GP32C4T1EN_MSK);
}
/**
  * @brief  GP32C4T1EN clock disable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1sl_gp32c4t1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1SL, RCU_APB1SL_GP32C4T1EN_MSK);
}
/**
  * @brief  Get GP32C4T1EN clock during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1sl_gp32c4t1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1SL, RCU_APB1SL_GP32C4T1EN_MSK)>>RCU_APB1SL_GP32C4T1EN_POS);
}

/**
  * @brief  CMP clock enable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb2sl_cmpen(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB2SL, RCU_APB2SL_CMPEN_MSK);
}
/**
  * @brief  CMP clock disable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb2sl_cmpen(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB2SL, RCU_APB2SL_CMPEN_MSK);
}
/**
  * @brief  Get CMP clock during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb2sl_cmpen(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB2SL, RCU_APB2SL_CMPEN_MSK)>>RCU_APB2SL_CMPEN_POS);
}
/**
  * @brief  GP16C2T4EN clock enable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb2sl_gp16c2t4en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB2SL, RCU_APB2SL_GP16C2T4EN_MSK);
}
/**
  * @brief  GP16C2T4EN clock disable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb2sl_gp16c2t4en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB2SL, RCU_APB2SL_GP16C2T4EN_MSK);
}
/**
  * @brief  Get GP16C2T4EN clock during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb2sl_gp16c2t4en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB2SL, RCU_APB2SL_GP16C2T4EN_MSK)>>RCU_APB2SL_GP16C2T4EN_POS);
}
/**
  * @brief  GP16C2T3EN clock enable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb2sl_gp16c2t3en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB2SL, RCU_APB2SL_GP16C2T3EN_MSK);
}
/**
  * @brief  GP16C2T3EN clock disable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb2sl_gp16c2t3en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB2SL, RCU_APB2SL_GP16C2T3EN_MSK);
}
/**
  * @brief  Get GP16C2T3EN clock during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb2sl_gp16c2t3en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB2SL, RCU_APB2SL_GP16C2T3EN_MSK)>>RCU_APB2SL_GP16C2T3EN_POS);
}
/**
  * @brief  GP16C2T2EN clock enable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb2sl_gp16c2t2en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB2SL, RCU_APB2SL_GP16C2T2EN_MSK);
}
/**
  * @brief  GP16C2T2EN clock disable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb2sl_gp16c2t2en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB2SL, RCU_APB2SL_GP16C2T2EN_MSK);
}
/**
  * @brief  Get GP16C2T2EN clock during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb2sl_gp16c2t2en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB2SL, RCU_APB2SL_GP16C2T2EN_MSK)>>RCU_APB2SL_GP16C2T2EN_POS);
}
/**
  * @brief  GP16C2T1EN clock enable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb2sl_gp16c2t1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB2SL, RCU_APB2SL_GP16C2T1EN_MSK);
}
/**
  * @brief  GP16C2T1EN clock disable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb2sl_gp16c2t1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB2SL, RCU_APB2SL_GP16C2T1EN_MSK);
}
/**
  * @brief  Get GP16C2T1EN clock during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb2sl_gp16c2t1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB2SL, RCU_APB2SL_GP16C2T1EN_MSK)>>RCU_APB2SL_GP16C2T1EN_POS);
}
/**
  * @brief  UART1EN clock enable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb2sl_uart1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB2SL, RCU_APB2SL_UART1EN_MSK);
}
/**
  * @brief  UART1EN clock disable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb2sl_uart1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB2SL, RCU_APB2SL_UART1EN_MSK);
}
/**
  * @brief  Get UART1EN clock during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb2sl_uart1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB2SL, RCU_APB2SL_UART1EN_MSK)>>RCU_APB2SL_UART1EN_POS);
}
/**
  * @brief  SPI1EN clock enable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb2sl_spi1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB2SL, RCU_APB2SL_SPI1EN_MSK);
}
/**
  * @brief  SPI1EN clock disable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb2sl_spi1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB2SL, RCU_APB2SL_SPI1EN_MSK);
}
/**
  * @brief  Get SPI1EN clock during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb2sl_spi1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB2SL, RCU_APB2SL_SPI1EN_MSK)>>RCU_APB2SL_SPI1EN_POS);
}
/**
  * @brief  AD16C4T1EN clock enable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb2sl_ad16c4t1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB2SL, RCU_APB2SL_AD16C4T1EN_MSK);
}
/**
  * @brief  AD16C4T1EN clock disable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb2sl_ad16c4t1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB2SL, RCU_APB2SL_AD16C4T1EN_MSK);
}
/**
  * @brief  Get AD16C4T1EN clock during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb2sl_ad16c4t1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB2SL, RCU_APB2SL_AD16C4T1EN_MSK)>>RCU_APB2SL_AD16C4T1EN_POS);
}
/**
  * @brief  ADCEN clock enable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb2sl_adcen(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB2SL, RCU_APB2SL_ADCEN_MSK);
}
/**
  * @brief  ADCEN clock disable during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb2sl_adcen(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB2SL, RCU_APB2SL_ADCEN_MSK);
}
/**
  * @brief  Get ADCEN clock during Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb2sl_adcen(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB2SL, RCU_APB2SL_ADCEN_MSK)>>RCU_APB2SL_ADCEN_POS);
}

/**
  * @brief  GPIOD clock enable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahbdsl_gpden(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBDSL, RCU_AHBDSL_GPDEN_MSK);
}
/**
  * @brief  GPIOD clock disable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahbdsl_gpden(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBDSL, RCU_AHBDSL_GPDEN_MSK);
}
/**
  * @brief  Get GPIOD clock during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahbdsl_gpden(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBDSL, RCU_AHBDSL_GPDEN_MSK)>>RCU_AHBDSL_GPDEN_POS);
}
/**
  * @brief  GPIOC clock enable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahbdsl_gpcen(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBDSL, RCU_AHBDSL_GPCEN_MSK);
}
/**
  * @brief  GPIOC clock disable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahbdsl_gpcen(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBDSL, RCU_AHBDSL_GPCEN_MSK);
}
/**
  * @brief  Get GPIOC clock during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahbdsl_gpcen(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBDSL, RCU_AHBDSL_GPCEN_MSK)>>RCU_AHBDSL_GPCEN_POS);
}
/**
  * @brief  GPIOB clock enable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahbdsl_gpben(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBDSL, RCU_AHBDSL_GPBEN_MSK);
}
/**
  * @brief  GPIOB clock disable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahbdsl_gpben(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBDSL, RCU_AHBDSL_GPBEN_MSK);
}
/**
  * @brief  Get GPIOB clock during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahbdsl_gpben(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBDSL, RCU_AHBDSL_GPBEN_MSK)>>RCU_AHBDSL_GPBEN_POS);
}
/**
  * @brief  GPIOA clock enable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahbdsl_gpaen(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBDSL, RCU_AHBDSL_GPAEN_MSK);
}
/**
  * @brief  GPIOA clock disable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahbdsl_gpaen(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBDSL, RCU_AHBDSL_GPAEN_MSK);
}
/**
  * @brief  Get GPIOA clock during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahbdsl_gpaen(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBDSL, RCU_AHBDSL_GPAEN_MSK)>>RCU_AHBDSL_GPAEN_POS);
}
/**
  * @brief  HDIV clock enable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahbdsl_hdiven(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBDSL, RCU_AHBDSL_HDIVEN_MSK);
}
/**
  * @brief  HDIV clock disable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahbdsl_hdiven(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBDSL, RCU_AHBDSL_HDIVEN_MSK);
}
/**
  * @brief  Get HDIV clock during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahbdsl_hdiven(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBDSL, RCU_AHBDSL_HDIVEN_MSK)>>RCU_AHBDSL_HDIVEN_POS);
}
/**
  * @brief  USB clock enable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahbdsl_usben(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBDSL, RCU_AHBDSL_USBEN_MSK);
}
/**
  * @brief  USB clock disable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahbdsl_usben(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBDSL, RCU_AHBDSL_USBEN_MSK);
}
/**
  * @brief  Get USB clock during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahbdsl_usben(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBDSL, RCU_AHBDSL_USBEN_MSK)>>RCU_AHBDSL_USBEN_POS);
}
/**
  * @brief  AES clock enable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahbdsl_aesen(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBDSL, RCU_AHBDSL_AESEN_MSK);
}
/**
  * @brief  AES clock disable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahbdsl_aesen(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBDSL, RCU_AHBDSL_AESEN_MSK);
}
/**
  * @brief  Get AES clock during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahbdsl_aesen(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBDSL, RCU_AHBDSL_AESEN_MSK)>>RCU_AHBDSL_AESEN_POS);
}
/**
  * @brief  CRC clock enable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahbdsl_crcen(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBDSL, RCU_AHBDSL_CRCEN_MSK);
}
/**
  * @brief  CRC clock disable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahbdsl_crcen(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBDSL, RCU_AHBDSL_CRCEN_MSK);
}
/**
  * @brief  Get CRC clock during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahbdsl_crcen(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBDSL, RCU_AHBDSL_CRCEN_MSK)>>RCU_AHBDSL_CRCEN_POS);
}
/**
  * @brief  RTC clock enable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahbdsl_rtcen(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBDSL, RCU_AHBDSL_RTCEN_MSK);
}
/**
  * @brief  RTC clock disable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahbdsl_rtcen(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBDSL, RCU_AHBDSL_RTCEN_MSK);
}
/**
  * @brief  Get RTC clock during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahbdsl_rtcen(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBDSL, RCU_AHBDSL_RTCEN_MSK)>>RCU_AHBDSL_RTCEN_POS);
}
/**
  * @brief  DMA1 clock enable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_ahbdsl_dma1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->AHBDSL, RCU_AHBDSL_DMA1EN_MSK);
}
/**
  * @brief  DMA1 clock disable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_ahbdsl_dma1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->AHBDSL, RCU_AHBDSL_DMA1EN_MSK);
}
/**
  * @brief  Get DMA1 clock during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_ahbdsl_dma1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->AHBDSL, RCU_AHBDSL_DMA1EN_MSK)>>RCU_AHBDSL_DMA1EN_POS);
}

/**
  * @brief  DAC clock enable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1dsl_dacen(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1DSL, RCU_APB1DSL_DACEN_MSK);
}
/**
  * @brief  DAC clock disable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1dsl_dacen(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1DSL, RCU_APB1DSL_DACEN_MSK);
}
/**
  * @brief  Get DAC clock during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1dsl_dacen(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1DSL, RCU_APB1DSL_DACEN_MSK)>>RCU_APB1DSL_DACEN_POS);
}
/**
  * @brief  I2C2 clock enable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1dsl_apb1dslen(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1DSL, RCU_APB1DSL_I2C2EN_MSK);
}
/**
  * @brief  I2C2 clock disable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1dsl_apb1dslen(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1DSL, RCU_APB1DSL_I2C2EN_MSK);
}
/**
  * @brief  Get I2C2 clock during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1dsl_apb1dslen(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1DSL, RCU_APB1DSL_I2C2EN_MSK)>>RCU_APB1DSL_I2C2EN_POS);
}
/**
  * @brief  I2C1 clock enable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1dsl_i2c1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1DSL, RCU_APB1DSL_I2C1EN_MSK);
}
/**
  * @brief  I2C1 clock disable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1dsl_i2c1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1DSL, RCU_APB1DSL_I2C1EN_MSK);
}
/**
  * @brief  Get I2C1 clock during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1dsl_i2c1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1DSL, RCU_APB1DSL_I2C1EN_MSK)>>RCU_APB1DSL_I2C1EN_POS);
}
/**
  * @brief  SUART2 clock enable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1dsl_suart2en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1DSL, RCU_APB1DSL_SUART2EN_MSK);
}
/**
  * @brief  SUART2 clock disable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1dsl_suart2en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1DSL, RCU_APB1DSL_SUART2EN_MSK);
}
/**
  * @brief  Get SUART2 clock during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1dsl_suart2en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1DSL, RCU_APB1DSL_SUART2EN_MSK)>>RCU_APB1DSL_SUART2EN_POS);
}
/**
  * @brief  SUART1 clock enable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1dsl_suart1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1DSL, RCU_APB1DSL_SUART1EN_MSK);
}
/**
  * @brief  SUART1 clock disable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1dsl_suart1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1DSL, RCU_APB1DSL_SUART1EN_MSK);
}
/**
  * @brief  Get SUART1 clock during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1dsl_suart1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1DSL, RCU_APB1DSL_SUART1EN_MSK)>>RCU_APB1DSL_SUART1EN_POS);
}
/**
  * @brief  UART3 clock enable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1dsl_uart3en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1DSL, RCU_APB1DSL_UART3EN_MSK);
}
/**
  * @brief  UART3 clock disable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1dsl_uart3en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1DSL, RCU_APB1DSL_UART3EN_MSK);
}
/**
  * @brief  Get UART3 clock during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1dsl_uart3en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1DSL, RCU_APB1DSL_UART3EN_MSK)>>RCU_APB1DSL_UART3EN_POS);
}
/**
  * @brief  UART2 clock enable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1dsl_uart2en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1DSL, RCU_APB1DSL_UART2EN_MSK);
}
/**
  * @brief  UART2 clock disable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1dsl_uart2en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1DSL, RCU_APB1DSL_UART2EN_MSK);
}
/**
  * @brief  Get UART2 clock during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1dsl_uart2en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1DSL, RCU_APB1DSL_UART2EN_MSK)>>RCU_APB1DSL_UART2EN_POS);
}
/**
  * @brief  SPI2 clock enable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1dsl_spi2en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1DSL, RCU_APB1DSL_SPI2EN_MSK);
}
/**
  * @brief  SPI2 clock disable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1dsl_spi2en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1DSL, RCU_APB1DSL_SPI2EN_MSK);
}
/**
  * @brief  Get SPI2 clock during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1dsl_spi2en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1DSL, RCU_APB1DSL_SPI2EN_MSK)>>RCU_APB1DSL_SPI2EN_POS);
}
/**
  * @brief  IWDT clock enable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1dsl_iwdten(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1DSL, RCU_APB1DSL_IWDTEN_MSK);
}
/**
  * @brief  IWDT clock disable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1dsl_iwdten(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1DSL, RCU_APB1DSL_IWDTEN_MSK);
}
/**
  * @brief  Get IWDT clock during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1dsl_iwdten(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1DSL, RCU_APB1DSL_IWDTEN_MSK)>>RCU_APB1DSL_IWDTEN_POS);
}
/**
  * @brief  WWDT clock enable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1dsl_wwdten(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1DSL, RCU_APB1DSL_WWDTEN_MSK);
}
/**
  * @brief  WWDT clock disable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1dsl_wwdten(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1DSL, RCU_APB1DSL_WWDTEN_MSK);
}
/**
  * @brief  Get WWDT clock during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1dsl_wwdten(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1DSL, RCU_APB1DSL_WWDTEN_MSK)>>RCU_APB1DSL_WWDTEN_POS);
}
/**
  * @brief  BS16T1 clock enable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1dsl_bs16t1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1DSL, RCU_APB1DSL_BS16T1EN_MSK);
}
/**
  * @brief  BS16T1 clock disable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1dsl_bs16t1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1DSL, RCU_APB1DSL_BS16T1EN_MSK);
}
/**
  * @brief  Get BS16T1 clock during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1dsl_bs16t1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1DSL, RCU_APB1DSL_BS16T1EN_MSK)>>RCU_APB1DSL_BS16T1EN_POS);
}
/**
  * @brief  GP16C4T3 clock enable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1dsl_gp16c4t3en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1DSL, RCU_APB1DSL_GP16C4T3EN_MSK);
}
/**
  * @brief  GP16C4T3 clock disable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1dsl_gp16c4t3en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1DSL, RCU_APB1DSL_GP16C4T3EN_MSK);
}
/**
  * @brief  Get GP16C4T3 clock during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1dsl_gp16c4t3en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1DSL, RCU_APB1DSL_GP16C4T3EN_MSK)>>RCU_APB1DSL_GP16C4T3EN_POS);
}
/**
  * @brief  GP16C4T2 clock enable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1dsl_gp16c4t2en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1DSL, RCU_APB1DSL_GP16C4T2EN_MSK);
}
/**
  * @brief  GP16C4T2 clock disable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1dsl_gp16c4t2en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1DSL, RCU_APB1DSL_GP16C4T2EN_MSK);
}
/**
  * @brief  Get GP16C4T2 clock during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1dsl_gp16c4t2en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1DSL, RCU_APB1DSL_GP16C4T2EN_MSK)>>RCU_APB1DSL_GP16C4T2EN_POS);
}
/**
  * @brief  GP16C4T1 clock enable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1dsl_gp16c4t1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1DSL, RCU_APB1DSL_GP16C4T1EN_MSK);
}
/**
  * @brief  GP16C4T1 clock disable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1dsl_gp16c4t1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1DSL, RCU_APB1DSL_GP16C4T1EN_MSK);
}
/**
  * @brief  Get GP16C4T1 clock during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1dsl_gp16c4t1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1DSL, RCU_APB1DSL_GP16C4T1EN_MSK)>>RCU_APB1DSL_GP16C4T1EN_POS);
}
/**
  * @brief  GP32C4T1 clock enable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb1dsl_gp32c4t1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB1DSL, RCU_APB1DSL_GP32C4T1EN_MSK);
}
/**
  * @brief  GP32C4T1 clock disable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb1dsl_gp32c4t1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB1DSL, RCU_APB1DSL_GP32C4T1EN_MSK);
}
/**
  * @brief  Get GP32C4T1 clock during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb1dsl_gp32c4t1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB1DSL, RCU_APB1DSL_GP32C4T1EN_MSK)>>RCU_APB1DSL_GP32C4T1EN_POS);
}

/**
  * @brief  CMP clock enable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb2dsl_cmpen(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB2DSL, RCU_APB2DSL_CMPEN_MSK);
}
/**
  * @brief  CMP clock disable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb2dsl_cmpen(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB2DSL, RCU_APB2DSL_CMPEN_MSK);
}
/**
  * @brief  Get CMP clock during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb2dsl_cmpen(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB2DSL, RCU_APB2DSL_CMPEN_MSK)>>RCU_APB2DSL_CMPEN_POS);
}
/**
  * @brief  GP16C2T4 clock enable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb2dsl_gp16c2t4en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB2DSL, RCU_APB2DSL_GP16C2T4EN_MSK);
}
/**
  * @brief  GP16C2T4 clock disable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb2dsl_gp16c2t4en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB2DSL, RCU_APB2DSL_GP16C2T4EN_MSK);
}
/**
  * @brief  Get GP16C2T4 clock during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb2dsl_gp16c2t4en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB2DSL, RCU_APB2DSL_GP16C2T4EN_MSK)>>RCU_APB2DSL_GP16C2T4EN_POS);
}
/**
  * @brief  GP16C2T3 clock enable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb2dsl_gp16c2t3en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB2DSL, RCU_APB2DSL_GP16C2T3EN_MSK);
}
/**
  * @brief  GP16C2T3 clock disable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb2dsl_gp16c2t3en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB2DSL, RCU_APB2DSL_GP16C2T3EN_MSK);
}
/**
  * @brief  Get GP16C2T3 clock during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb2dsl_gp16c2t3en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB2DSL, RCU_APB2DSL_GP16C2T3EN_MSK)>>RCU_APB2DSL_GP16C2T3EN_POS);
}
/**
  * @brief  GP16C2T2 clock enable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb2dsl_gp16c2t2en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB2DSL, RCU_APB2DSL_GP16C2T2EN_MSK);
}
/**
  * @brief  GP16C2T2 clock disable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb2dsl_gp16c2t2en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB2DSL, RCU_APB2DSL_GP16C2T2EN_MSK);
}
/**
  * @brief  Get GP16C2T2 clock during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb2dsl_gp16c2t2en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB2DSL, RCU_APB2DSL_GP16C2T2EN_MSK)>>RCU_APB2DSL_GP16C2T2EN_POS);
}
/**
  * @brief  GP16C2T1 clock enable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb2dsl_gp16c2t1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB2DSL, RCU_APB2DSL_GP16C2T1EN_MSK);
}
/**
  * @brief  GP16C2T1 clock disable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb2dsl_gp16c2t1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB2DSL, RCU_APB2DSL_GP16C2T1EN_MSK);
}
/**
  * @brief  Get GP16C2T1 clock during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb2dsl_gp16c2t1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB2DSL, RCU_APB2DSL_GP16C2T1EN_MSK)>>RCU_APB2DSL_GP16C2T1EN_POS);
}
/**
  * @brief  UART1 clock enable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb2dsl_uart1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB2DSL, RCU_APB2DSL_UART1EN_MSK);
}
/**
  * @brief  UART1 clock disable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb2dsl_uart1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB2DSL, RCU_APB2DSL_UART1EN_MSK);
}
/**
  * @brief  Get UART1 clock during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb2dsl_uart1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB2DSL, RCU_APB2DSL_UART1EN_MSK)>>RCU_APB2DSL_UART1EN_POS);
}
/**
  * @brief  SPI1 clock enable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb2dsl_spi1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB2DSL, RCU_APB2DSL_SPI1EN_MSK);
}
/**
  * @brief  SPI1 clock disable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb2dsl_spi1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB2DSL, RCU_APB2DSL_SPI1EN_MSK);
}
/**
  * @brief  Get SPI1 clock during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb2dsl_spi1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB2DSL, RCU_APB2DSL_SPI1EN_MSK)>>RCU_APB2DSL_SPI1EN_POS);
}
/**
  * @brief  AD16C4T1 clock enable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb2dsl_ad16c4t1en(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB2DSL, RCU_APB2DSL_AD16C4T1EN_MSK);
}
/**
  * @brief  AD16C4T1 clock disable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb2dsl_ad16c4t1en(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB2DSL, RCU_APB2DSL_AD16C4T1EN_MSK);
}
/**
  * @brief  Get AD16C4T1 clock during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb2dsl_ad16c4t1en(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB2DSL, RCU_APB2DSL_AD16C4T1EN_MSK)>>RCU_APB2DSL_AD16C4T1EN_POS);
}
/**
  * @brief  ADC clock enable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_enable_apb2dsl_adcen(RCU_TypeDef *rcu)
{
  SET_BIT(rcu->APB2DSL, RCU_APB2DSL_ADCEN_MSK);
}
/**
  * @brief  ADC clock disable during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval None
  */
__STATIC_INLINE void md_rcu_disable_apb2dsl_adcen(RCU_TypeDef *rcu)
{
  CLEAR_BIT(rcu->APB2DSL, RCU_APB2DSL_ADCEN_MSK);
}
/**
  * @brief  Get ADC clock during Deep Sleep mode bit.
  * @param  rcu RCU Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rcu_get_apb2dsl_adcen(RCU_TypeDef *rcu)
{
  return (READ_BIT(rcu->APB2DSL, RCU_APB2DSL_ADCEN_MSK)>>RCU_APB2DSL_ADCEN_POS);
}

/**
  * @} MD_RCU_Public_Macros
  */

/* Public functions -----------------------------------------------------------*/
/** @defgroup MD_RCU_Public_Functions RCU Public Functions
  * @{
  */

/** @defgroup MD_RCU_PF_Basic_Configuration Basic Configuration
  * @{
  */
void md_rcu_init(void);
void md_rcu_init_set(RCU_TypeDef *, md_rcu_init_typedef *);
void md_rcu_pllreinit(uint8_t);
/**
  * @} MD_RCU_PF_Basic_Configuration
  */

/**
  * @} MD_RCU_Public_Functions
  */

#endif

/**
  * @} RCU
  */

/**
  * @} Micro_Driver
  */
#ifdef __cplusplus
}

#endif

#endif

/******************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
