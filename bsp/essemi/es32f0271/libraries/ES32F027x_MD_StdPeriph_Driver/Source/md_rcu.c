/**
  ******************************************************************************
  * @file    md_rcu.c
  * @brief   ES32F0271 RCU Source File.
  *
  * @version V1.00.01
  * @data    6/12/2018
  * @author  Eastsoft AE Team
  * @note
  * detailed description
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *******************************************************************************
  */

/* Includes -------------------------------------------------------------------*/
#include "md_rcu.h"
#include "md_fc.h"
#include "system_es32f027x.h"

/** @addtogroup Micro_Driver
  * @{
  */


/** @defgroup RCU RCU
  * @brief RCU micro driver
  * @{
  */


/* Private types --------------------------------------------------------------*/
/* Private variables ----------------------------------------------------------*/
/* Private constants ----------------------------------------------------------*/
/* Private macros -------------------------------------------------------------*/
/** @defgroup MD_RCU_Private_Macros RCU Private Macros
  * @{
  */


/**
  * @} MD_RCU_Private_Macros
  */

/* Private function prototypes ------------------------------------------------*/

/* Public functions -----------------------------------------------------------*/
/** @addtogroup MD_RCU_Public_Functions RCU Public Functions
  * @{
  */

/** @addtogroup MD_RCU_PF_Init RCU Public Init Functions
  * @{
  */

/**
  * @brief
  * @param
  * @retval None
  */
void md_rcu_init(void)
{
  uint8_t  pllmux;

  md_fc_set_con_wait(3);

  md_rcu_set_cfg_mpre(RCU, 0UL);
  md_rcu_set_cfg_msw(RCU, MD_RCU_MCO_DISABLE);
  md_rcu_set_cfg_pllmul(RCU, 12 - 1);
  md_rcu_set_cfg_pllsrc(RCU, MD_RCU_PLL_SRC_HRC);
  md_rcu_set_cfg_hoscdiv(RCU, 2 - 1);
  md_rcu_set_cfg_ppre(RCU, MD_RCU_PPRE_HCLK_DIV_1);
  md_rcu_set_cfg_hpre(RCU, MD_RCU_HPRE_SYSCLK_DIV_1);
  md_rcu_set_cfg_sw(RCU, MD_RCU_SYSCLK_PLL0);

  md_rcu_disable_con_csson(RCU);
  md_rcu_disable_con_pll1on(RCU);
  md_rcu_enable_con_pll0on(RCU);
  md_rcu_disable_con_loscon(RCU);
  md_rcu_disable_con_lrcon(RCU);
  md_rcu_disable_con_hoscon(RCU);
  md_rcu_enable_con_hrcon(RCU);

  md_rcu_set_cfg_ckcfg(RCU);

  /*  while(md_rcu_get_con_hoscrdy(RCU)==0)  {} */

  /*  while(md_rcu_get_con_pll0rdy(RCU)==0)  {} */


  if (RCU->CON & RCU_CON_HRCON_MSK)                 /* if HRC enbale */
    while (md_rcu_get_con_hrcrdy(RCU) == 0);  /* Wait for HRCRDY = 1 (HRC is ready)*/


  if (RCU->CON & RCU_CON_HOSCON_MSK)                  /* if HOSC enbale */
    while (md_rcu_get_con_hoscrdy(RCU) == 0);  /* Wait for HOSCRDY = 1 (HOSC is ready)*/


  if (RCU->CON & RCU_CON_LRCON_MSK)                  /* if LRC enbale */
    while (md_rcu_get_con_lrcrdy(RCU) == 0);  /* Wait for LRCRDY = 1 (LRC is ready)*/


  if (RCU->CON & RCU_CON_LOSCON_MSK)                 /* if LOSC enbale */
    while (md_rcu_get_con_loscrdy(RCU) == 0);  /* Wait for LOSCRDY = 1 (LOSC is ready)*/

  if (RCU->CON & RCU_CON_PLL0ON_MSK)             /* if PLL enbale */
    while (md_rcu_get_con_pll0rdy(RCU) == 0); /* Wait for PLLRDY = 1 (PLL is ready)*/



  /* PLL Reference Clock Source*/
  if (md_rcu_get_cfg_pllsrc(RCU))
    PLL0Frequency = (uint32_t)(__HOSC / (md_rcu_get_cfg_pllsrc(RCU) + 1));
  else
    PLL0Frequency = (uint32_t)(__HRC);

  /* System Frequency */
  switch (md_rcu_get_cfg_sw(RCU)) /* System clock switch(SYSCLK) */
  {
    case 0: /*================= HRC selected as system clock*/
      SystemCoreClock = (uint32_t)(__HRC);
      break;

    case 1: /*================= HOSC selected as system clock*/
      SystemCoreClock = (uint32_t)(__HOSC);
      break;

    case 2: /*================= LRC selected as system clock*/
      SystemCoreClock = (uint32_t)(__LRC);
      break;

    case 3: /*================= LOSC selected as system clock*/
      SystemCoreClock = (uint32_t)(__LOSC);
      break;

    case 4: /*================= PLL selected as system clock*/
      pllmux = md_rcu_get_cfg_pllmul(RCU) + 1;

      if (pllmux >= 18)  pllmux = 18;

      SystemCoreClock = (uint32_t)(PLL0Frequency * pllmux);
      break;

    default:
      SystemCoreClock = (uint32_t)(__HRC);
      break;
  }

  /* Core Frequency */
  if (md_rcu_get_cfg_hpre(RCU))
    SystemFrequency_SysClk = SystemCoreClock >> ((md_rcu_get_cfg_hpre(RCU) & 0x07) + 1);
  else
    SystemFrequency_SysClk = SystemCoreClock;

  /* AHB Frequency */
  SystemFrequency_AHBClk = SystemFrequency_SysClk;

  /* APB Frequency */
  if (md_rcu_get_cfg_ppre(RCU))
    SystemFrequency_APBClk = SystemFrequency_SysClk >> ((md_rcu_get_cfg_ppre(RCU) & 0x03) + 1);
  else
    SystemFrequency_APBClk = SystemFrequency_SysClk;


  if (SystemFrequency_AHBClk / 1000000 > 72)
    md_fc_set_con_wait(3);
  else if (SystemFrequency_AHBClk / 1000000 > 48)
    md_fc_set_con_wait(2);
  else if (SystemFrequency_AHBClk / 1000000 > 24)
    md_fc_set_con_wait(1);
  else
    md_fc_set_con_wait(0);
}

void md_rcu_init_set(RCU_TypeDef *rcu, md_rcu_init_typedef *RCU_InitStruct)
{
  uint8_t  pllmux;

  md_fc_set_con_wait(3);

  md_rcu_set_cfg_mpre(rcu, RCU_InitStruct->Mpre);
  md_rcu_set_cfg_msw(rcu, RCU_InitStruct->Msw);
  md_rcu_set_cfg_pllmul(rcu, (RCU_InitStruct->PllMul) - 1);
  md_rcu_set_cfg_pllsrc(rcu, RCU_InitStruct->PllSrc);
  md_rcu_set_cfg_hoscdiv(rcu, (RCU_InitStruct->HoscDiv) - 1);
  md_rcu_set_cfg_ppre(rcu, RCU_InitStruct->Ppre);
  md_rcu_set_cfg_hpre(rcu, RCU_InitStruct->Hpre);
  md_rcu_set_cfg_sw(rcu, RCU_InitStruct->Sw);  
  
  if(RCU_InitStruct->SysClock & RCU_CON_CSSON_MSK)
    md_rcu_enable_con_csson(rcu);
  else
    md_rcu_disable_con_csson(rcu);  
  
  if(RCU_InitStruct->SysClock & RCU_CON_PLL1ON_MSK)
    md_rcu_enable_con_pll1on(rcu);
  else
    md_rcu_disable_con_pll1on(rcu);  
  
  if(RCU_InitStruct->SysClock & RCU_CON_PLL0ON_MSK)
    md_rcu_enable_con_pll0on(rcu);
  else
    md_rcu_disable_con_pll0on(rcu);  
  
  if(RCU_InitStruct->SysClock & RCU_CON_LOSCON_MSK)
    md_rcu_enable_con_loscon(rcu);
  else
    md_rcu_disable_con_loscon(rcu);  
  
  if(RCU_InitStruct->SysClock & RCU_CON_LRCON_MSK)
    md_rcu_enable_con_lrcon(rcu);
  else
    md_rcu_disable_con_lrcon(rcu);  
  
  if(RCU_InitStruct->SysClock & RCU_CON_HOSCON_MSK)
    md_rcu_enable_con_hoscon(rcu);
  else
    md_rcu_disable_con_hoscon(rcu);  
  
  if(RCU_InitStruct->SysClock & RCU_CON_HRCON_MSK)
    md_rcu_enable_con_hrcon(rcu);
  else
    md_rcu_disable_con_hrcon(rcu);  
  
  md_rcu_set_cfg_ckcfg(rcu);

  /*  while(md_rcu_get_con_hoscrdy(RCU)==0)  {} */

  /*  while(md_rcu_get_con_pll0rdy(RCU)==0)  {} */


  if (RCU->CON & RCU_CON_HRCON_MSK)                 /* if HRC enbale */
    while (md_rcu_get_con_hrcrdy(rcu) == 0);  /* Wait for HRCRDY = 1 (HRC is ready)*/


  if (RCU->CON & RCU_CON_HOSCON_MSK)                  /* if HOSC enbale */
    while (md_rcu_get_con_hoscrdy(rcu) == 0);  /* Wait for HOSCRDY = 1 (HOSC is ready)*/


  if (RCU->CON & RCU_CON_LRCON_MSK)                  /* if LRC enbale */
    while (md_rcu_get_con_lrcrdy(rcu) == 0);  /* Wait for LRCRDY = 1 (LRC is ready)*/


  if (RCU->CON & RCU_CON_LOSCON_MSK)                 /* if LOSC enbale */
    while (md_rcu_get_con_loscrdy(rcu) == 0);  /* Wait for LOSCRDY = 1 (LOSC is ready)*/

  if (RCU->CON & RCU_CON_PLL0ON_MSK)             /* if PLL enbale */
    while (md_rcu_get_con_pll0rdy(rcu) == 0); /* Wait for PLLRDY = 1 (PLL is ready)*/



  /* PLL Reference Clock Source*/
  if (md_rcu_get_cfg_pllsrc(rcu))
    PLL0Frequency = (uint32_t)(__HOSC / (md_rcu_get_cfg_pllsrc(rcu) + 1));
  else
    PLL0Frequency = (uint32_t)(__HRC);

  /* System Frequency */
  switch (md_rcu_get_cfg_sw(rcu)) /* System clock switch(SYSCLK) */
  {
    case 0: /*================= HRC selected as system clock*/
      SystemCoreClock = (uint32_t)(__HRC);
      break;

    case 1: /*================= HOSC selected as system clock*/
      SystemCoreClock = (uint32_t)(__HOSC);
      break;

    case 2: /*================= LRC selected as system clock*/
      SystemCoreClock = (uint32_t)(__LRC);
      break;

    case 3: /*================= LOSC selected as system clock*/
      SystemCoreClock = (uint32_t)(__LOSC);
      break;

    case 4: /*================= PLL selected as system clock*/
      pllmux = md_rcu_get_cfg_pllmul(rcu) + 1;

      if (pllmux >= 18)  pllmux = 18;

      SystemCoreClock = (uint32_t)(PLL0Frequency * pllmux);
      break;

    default:
      SystemCoreClock = (uint32_t)(__HRC);
      break;
  }

  /* Core Frequency */
  if (md_rcu_get_cfg_hpre(rcu))
    SystemFrequency_SysClk = SystemCoreClock >> ((md_rcu_get_cfg_hpre(rcu) & 0x07) + 1);
  else
    SystemFrequency_SysClk = SystemCoreClock;

  /* AHB Frequency */
  SystemFrequency_AHBClk = SystemFrequency_SysClk;

  /* APB Frequency */
  if (md_rcu_get_cfg_ppre(rcu))
    SystemFrequency_APBClk = SystemFrequency_SysClk >> ((md_rcu_get_cfg_ppre(rcu) & 0x03) + 1);
  else
    SystemFrequency_APBClk = SystemFrequency_SysClk;


  if (SystemFrequency_AHBClk / 1000000 > 72)
    md_fc_set_con_wait(3);
  else if (SystemFrequency_AHBClk / 1000000 > 48)
    md_fc_set_con_wait(2);
  else if (SystemFrequency_AHBClk / 1000000 > 24)
    md_fc_set_con_wait(1);
  else
    md_fc_set_con_wait(0);
}


/**
  * @brief
  * @param
  * @retval None
  */
void md_rcu_pllreinit(uint8_t pllmul)
{
  md_rcu_set_cfg_pllmul(RCU, pllmul);
  md_rcu_set_cfg_ckcfg(RCU);

  /* PLL Reference Clock Source */
  if (md_rcu_get_cfg_pllsrc(RCU))
    PLL0Frequency = (uint32_t)(__HOSC / (md_rcu_get_cfg_pllsrc(RCU) + 1));
  else
    PLL0Frequency = (uint32_t)(__HRC);

  SystemCoreClock = (uint32_t)(PLL0Frequency * (pllmul + 1));

  /* Core Frequency */
  if (md_rcu_get_cfg_hpre(RCU))
    SystemFrequency_SysClk = SystemCoreClock >> ((md_rcu_get_cfg_hpre(RCU) & 0x07) + 1);
  else
    SystemFrequency_SysClk = SystemCoreClock;

  /* AHB Frequency */
  SystemFrequency_AHBClk = SystemFrequency_SysClk;

  /* APB Frequency */
  if (md_rcu_get_cfg_ppre(RCU))
    SystemFrequency_APBClk = SystemFrequency_SysClk >> ((md_rcu_get_cfg_ppre(RCU) & 0x03) + 1);
  else
    SystemFrequency_APBClk = SystemFrequency_SysClk;

  md_fc_set_con_wait(3);

  if (SystemFrequency_AHBClk / 1000000 > 72)
    md_fc_set_con_wait(3);
  else if (SystemFrequency_AHBClk / 1000000 > 48)
    md_fc_set_con_wait(2);
  else if (SystemFrequency_AHBClk / 1000000 > 24)
    md_fc_set_con_wait(1);
  else
    md_fc_set_con_wait(0);
}

/**
  * @} MD_RCU_PF_Init
  */

/**
  * @} MD_RCU_Public_Functions
  */

/**
  * @} RCU
  */

/**
  * @} Micro_Driver
  */

/******************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
