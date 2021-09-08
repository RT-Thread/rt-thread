/**
  ******************************************************************************
  * @file    tae32f53xx_ll_sysctrl.c
  * @author  MCD Application Team
  * @brief   SYSCTRL LL Module Driver.
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "tae32f53xx_ll.h"


#define DBG_TAG             "SYSCTRL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae32f53xx_dbg.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @defgroup SYSCTRL_LL SYSCTRL LL
  * @brief    SYSCTRL LL Module Driver
  * @{
  */


/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/** @defgroup SYSCTRL_LL_Private_Types SYSCTRL LL Private Types
  * @brief    SYSCTRL LL Private Types
  * @{
  */

/**
  * @brief SYSCTRL PLL0/1/2 Config Type Define
  * @note pll_out_freq is before PLL Post Div
  */
typedef struct __SYSCTRL_PLLCfgTypedef {
    uint32_t pll_in_freq;       /*!< PLL Input Freq    */
    uint32_t pll_out_freq;      /*!< PLL Output Freq    */
    uint8_t  pll_pre_div;       /*!< PLL Pre-Div       */
    uint16_t fpll_int;          /*!< FPLL Integer      */
    uint16_t fpll_frac;         /*!< FPLL Fraction     */
    uint32_t pll_vco_band;      /*!< PLL VCO Band      */
    uint32_t pll_vco_gain;      /*!< PLL VCO Gain      */
} SYSCTRL_PLLCfgTypedef;

/**
  * @}
  */


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/** @defgroup SYSCTRL_LL_Private_Variables SYSCTRL LL Private Variables
  * @brief    SYSCTRL LL Private Variables
  * @{
  */

/**
  * @brief SYSCLK PLL Config Const Array Definition
  * @note  VCO band&gain config are the same to PLL0/1/2
  */
static const SYSCTRL_PLLCfgTypedef sysctrl_pll_cfg[] = {
    {8000000,  100000000, 1, 6,  0x4000, SYSCTRL_PLL0_BAND_312M, SYSCTRL_PLL0_GVCO_2},  /*!<PLL0In->8M,PLL0Out->100M    */
    {8000000,  110000000, 1, 6,  0xe000, SYSCTRL_PLL0_BAND_312M, SYSCTRL_PLL0_GVCO_2},  /*!<PLL0In->8M,PLL0Out->110M    */
    {8000000,  120000000, 1, 7,  0x8000, SYSCTRL_PLL0_BAND_312M, SYSCTRL_PLL0_GVCO_2},  /*!<PLL0In->8M,PLL0Out->120M    */
    {8000000,  130000000, 1, 8,  0x2000, SYSCTRL_PLL0_BAND_312M, SYSCTRL_PLL0_GVCO_2},  /*!<PLL0In->8M,PLL0Out->130M    */

    {8000000,  140000000, 1, 8,  0xc000, SYSCTRL_PLL0_BAND_396M, SYSCTRL_PLL0_GVCO_2},  /*!<PLL0In->8M,PLL0Out->140M    */
    {8000000,  150000000, 1, 9,  0x6000, SYSCTRL_PLL0_BAND_396M, SYSCTRL_PLL0_GVCO_2},  /*!<PLL0In->8M,PLL0Out->150M    */
    {8000000,  160000000, 1, 10, 0,      SYSCTRL_PLL0_BAND_396M, SYSCTRL_PLL0_GVCO_2},  /*!<PLL0In->8M,PLL0Out->160M    */
    {8000000,  170000000, 1, 10, 0xa000, SYSCTRL_PLL0_BAND_396M, SYSCTRL_PLL0_GVCO_2},  /*!<PLL0In->8M,PLL0Out->170M    */

    {8000000,  180000000, 1, 11, 0x4000, SYSCTRL_PLL0_BAND_466M, SYSCTRL_PLL0_GVCO_2},  /*!<PLL0In->8M,PLL0Out->180M    */
    {8000000,  190000000, 1, 11, 0xe000, SYSCTRL_PLL0_BAND_466M, SYSCTRL_PLL0_GVCO_2},  /*!<PLL0In->8M,PLL0Out->190M    */
    {8000000,  200000000, 1, 12, 0x8000, SYSCTRL_PLL0_BAND_466M, SYSCTRL_PLL0_GVCO_2},  /*!<PLL0In->8M,PLL0Out->200M    */

    {8000000,  210000000, 1, 13, 0x2000, SYSCTRL_PLL0_BAND_520M, SYSCTRL_PLL0_GVCO_2},  /*!<PLL0In->8M,PLL0Out->210M    */
    {8000000,  220000000, 1, 13, 0xc000, SYSCTRL_PLL0_BAND_520M, SYSCTRL_PLL0_GVCO_2},  /*!<PLL0In->8M,PLL0Out->220M    */
    {8000000,  230000000, 1, 14, 0x6000, SYSCTRL_PLL0_BAND_520M, SYSCTRL_PLL0_GVCO_2},  /*!<PLL0In->8M,PLL0Out->230M    */
};

/**
  * @}
  */


/* Private function prototypes -----------------------------------------------*/
/** @defgroup SYSCTRL_LL_Private_Functions SYSCTRL LL Private Functions
  * @brief    SYSCTRL LL Private Functions
  * @{
  */
static void LL_SYSCTRL_XOSCCfg(SYSCTRL_TypeDef *Instance);
/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @defgroup SYSCTRL_LL_Exported_Functions SYSCTRL LL Exported Functions
  * @brief    SYSCTRL LL Exported Functions
  * @{
  */

/** @defgroup SYSCTRL_LL_Exported_Functions_Group1 SYSCTRL Clock Config Functions
  * @brief    SYSCTRL Clock Config Functions
  * @{
  */

/**
  * @brief  SYSCTRL LL SYSCLK Init
  * @param  Instance Specifies SYSCTRL peripheral
  * @param  sysclk_cfg SYSCLK Config Pointer
  * @return Status of the Initialization
  */
LL_StatusETypeDef LL_SYSCTRL_SysclkInit(SYSCTRL_TypeDef *Instance, SYSCTRL_SysclkUserCfgTypeDef *sysclk_cfg)
{
    uint16_t sysclk_div, remain;
    SYSCTRL_PLLUserCfgTypeDef pll0_cfg;
    LL_StatusETypeDef ret = LL_ERROR;

    //Check params to be valid
    if (Instance == NULL || sysclk_cfg == NULL) {
        LOG_E("SYSCLK init params error!\n");
        return LL_ERROR;
    }

    assert_param(sysclk_cfg->sysclk_freq);

    //Auto Freq Config
    if (sysclk_cfg->sysclk_src == SYSCLK_SRC_RC32K) {               //SYSCLK Source RC32K
        sysclk_cfg->sysclk_src_freq = LSI_VALUE;
    } else if (sysclk_cfg->sysclk_src == SYSCLK_SRC_RC8M) {         //SYSCLK Source RC8M
        sysclk_cfg->sysclk_src_freq = HSI_VALUE;
    } else if (sysclk_cfg->sysclk_src == SYSCLK_SRC_HOSC) {         //SYSCLK Source HOSC
        if (!sysclk_cfg->sysclk_src_freq) {     //Hardware can AutoSwitch
            sysclk_cfg->sysclk_src_freq = HSE_VALUE;
        }
    } else if (sysclk_cfg->sysclk_src == SYSCLK_SRC_PLL0DivClk) {   //SYSCLK Source PLL0DivClk
        if (sysclk_cfg->pll0clk_src == PLLCLK_SRC_XOSC) {           //PLL0 CLK Source HOSC
            if (!sysclk_cfg->pll0clk_src_freq) { //Hardware can AutoSwitch
                sysclk_cfg->pll0clk_src_freq = HSE_VALUE;
            }
        } else if (sysclk_cfg->pll0clk_src == PLLCLK_SRC_RC8M) {    //PLL0 CLK Source RC8M
            sysclk_cfg->pll0clk_src_freq = HSI_VALUE;
        }
    }

    //Check APB0/APB1 Clock Div to be valid
    if (sysclk_cfg->apb0_clk_div == SYSCTRL_CLK_DIV_IVD) {
        sysclk_cfg->apb0_clk_div = SYSCTRL_CLK_DIV_1;
    }

    if (sysclk_cfg->apb1_clk_div == SYSCTRL_CLK_DIV_IVD) {
        sysclk_cfg->apb1_clk_div = SYSCTRL_CLK_DIV_1;
    }

    //Calculate SYSCLK division
    if (sysclk_cfg->sysclk_src != SYSCLK_SRC_PLL0DivClk) {
        sysclk_div = sysclk_cfg->sysclk_src_freq / sysclk_cfg->sysclk_freq;
        remain = sysclk_cfg->sysclk_src_freq % sysclk_cfg->sysclk_freq;

        if (!sysclk_div || remain) {
            LOG_E("Can't division %d SYSCLK from %d Source CLK!\n", sysclk_cfg->sysclk_freq, sysclk_cfg->sysclk_src_freq);
            return LL_ERROR;
        }
    }

    //SYSCTRL CTRL Register Unlock
    __LL_SYSCTRL_CTRLReg_Unlock(Instance);

    //Config SYSCLK
    switch (sysclk_cfg->sysclk_src) {
        case SYSCLK_SRC_RC32K:
            LOG_I("SYSCLK-[%d] source select RC32K.\n", sysclk_cfg->sysclk_freq);
            __LL_SYSCTRL_SysClkSrc_Set(Instance, SYSCTRL_SYSCLK_SRC_RC32K);
            __LL_SYSCTRL_SysClkDiv_Set(Instance, sysclk_div);
            ret = LL_OK;
            break;

        case SYSCLK_SRC_RC8M:
            LOG_I("SYSCLK-[%d] source select RC8M.\n", sysclk_cfg->sysclk_freq);
            __LL_SYSCTRL_RC8M_En(Instance);
            __LL_SYSCTRL_SysClkSrc_Set(Instance, SYSCTRL_SYSCLK_SRC_RC8M);
            __LL_SYSCTRL_SysClkDiv_Set(Instance, sysclk_div);
            ret = LL_OK;
            break;

        case SYSCLK_SRC_PLL0DivClk:
            //SYSCLK PLL0 Config
            pll0_cfg.pll_clk_src = sysclk_cfg->pll0clk_src;
            pll0_cfg.pll_in_freq = sysclk_cfg->pll0clk_src_freq;
            pll0_cfg.pll_user_freq = sysclk_cfg->sysclk_freq;
            ret = LL_SYSCTRL_Pll0Cfg(Instance, &pll0_cfg);

            //SYCTRL CTRL Reg Unlock because Pll0Cfg function has lock before return
            __LL_SYSCTRL_CTRLReg_Unlock(Instance);

            //SYSCLK Source Select PLL0DivClk, and SYSCLK Div set to default 1
            if (ret == LL_OK) {
                LOG_I("SYSCLK-[%d] source select PLL0DivClk.\n", sysclk_cfg->sysclk_freq);
                __LL_SYSCTRL_SysClkSrc_Set(Instance, SYSCTRL_SYSCLK_SRC_PLLDivClk);
                __LL_SYSCTRL_SysClkDiv_Set(Instance, SYSCTRL_CLK_DIV_1);
            }

            break;

        case SYSCLK_SRC_HOSC:
            LOG_I("SYSCLK-[%d] source select HOSC-[%d].\n", sysclk_cfg->sysclk_freq, sysclk_cfg->sysclk_src_freq);
            LL_SYSCTRL_XOSCCfg(Instance);
            __LL_SYSCTRL_SysClkSrc_Set(Instance, SYSCTRL_SYSCLK_SRC_HOSC);
            __LL_SYSCTRL_SysClkDiv_Set(Instance, sysclk_div);
            ret = LL_OK;
            break;

        default:
            LOG_E("SYSCLK Source Select-[%d] Error!\n", sysclk_cfg->sysclk_src);
            ret = LL_ERROR;
            break;
    }

    if (ret == LL_OK) {
        //APB0/APB1 Clock Div Config
        __LL_SYSCTRL_APB0ClkDiv_Set(Instance, sysclk_cfg->apb0_clk_div);
        __LL_SYSCTRL_APB1ClkDiv_Set(Instance, sysclk_cfg->apb1_clk_div);

        //APB0/APB1/ABH0 Bus Clock Enable
        __LL_SYSCTRL_APB0Clk_En(Instance);
        __LL_SYSCTRL_APB1Clk_En(Instance);
        __LL_SYSCTRL_AHBClk_En(Instance);

        //APB0/APB1/ABH0 Soft Reset Release
        __LL_SYSCTRL_APB0BusSoftRst_Release(Instance);
        __LL_SYSCTRL_APB1BusSoftRst_Release(Instance);
        __LL_SYSCTRL_AHBBusSoftRst_Release(Instance);

        //RAM2/RAM1/RAM0 Bus Clock Enable
        __LL_SYSCTRL_RAM2BusClk_En(Instance);
        __LL_SYSCTRL_RAM1BusClk_En(Instance);
        __LL_SYSCTRL_RAM0BusClk_En(Instance);
    }

    //SYSCTRL Register Lock
    __LL_SYSCTRL_Reg_Lock(Instance);

    return ret;
}

/**
  * @brief  SYSCTRL LL GPIOA Debounce Clock Config
  * @param  src GPIOA Debounce Clock Source
  * @param  div GPIOA Debounce Clock Div
  * @return LL_StatusETypeDef
  */
LL_StatusETypeDef LL_SYSCTRL_GPIOA_DbcClkCfg(SYSCTRL_GPIOADbcClkSrcETypeDef src, SYSCTRL_ClkDivETypeDef div)
{
    if (div <= SYSCTRL_CLK_DIV_IVD || div > SYSCTRL_CLK_DIV_256) {
        LOG_E("GPIOA Debounce CLK div-[%d] config error!\n", div);
        return LL_ERROR;
    }

    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_GPIOADbcSrc_Set(SYSCTRL, src);
    __LL_SYSCTRL_GPIOADbcClkDiv_Set(SYSCTRL, div);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);

    return LL_OK;
}

/**
  * @brief  SYSCTRL LL GPIOB Debounce Clock Config
  * @param  src GPIOB Debounce Clock Source
  * @param  div GPIOB Debounce Clock Div
  * @return LL_StatusETypeDef
  */
LL_StatusETypeDef LL_SYSCTRL_GPIOB_DbcClkCfg(SYSCTRL_GPIOBDbcClkSrcETypeDef src, SYSCTRL_ClkDivETypeDef div)
{
    if (div <= SYSCTRL_CLK_DIV_IVD || div > SYSCTRL_CLK_DIV_256) {
        LOG_E("GPIOB Debounce CLK div-[%d] config error!\n", div);
        return LL_ERROR;
    }

    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_GPIOBDbcSrc_Set(SYSCTRL, src);
    __LL_SYSCTRL_GPIOBDbcClkDiv_Set(SYSCTRL, div);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);

    return LL_OK;
}

/**
  * @brief  SYSCTRL LL GPIOC Debounce Clock Config
  * @param  src GPIOC Debounce Clock Source
  * @param  div GPIOC Debounce Clock Div
  * @return LL_StatusETypeDef
  */
LL_StatusETypeDef LL_SYSCTRL_GPIOC_DbcClkCfg(SYSCTRL_GPIOCDbcClkSrcETypeDef src, SYSCTRL_ClkDivETypeDef div)
{
    if (div <= SYSCTRL_CLK_DIV_IVD || div > SYSCTRL_CLK_DIV_256) {
        LOG_E("GPIOC Debounce CLK div-[%d] config error!\n", div);
        return LL_ERROR;
    }

    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_GPIOCDbcSrc_Set(SYSCTRL, src);
    __LL_SYSCTRL_GPIOCDbcClkDiv_Set(SYSCTRL, div);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);

    return LL_OK;
}

/**
  * @brief  SYSCTRL LL GPIOD Debounce Clock Config
  * @param  src GPIOD Debounce Clock Source
  * @param  div GPIOD Debounce Clock Div
  * @return LL_StatusETypeDef
  */
LL_StatusETypeDef LL_SYSCTRL_GPIOD_DbcClkCfg(SYSCTRL_GPIODDbcClkSrcETypeDef src, SYSCTRL_ClkDivETypeDef div)
{
    if (div <= SYSCTRL_CLK_DIV_IVD || div > SYSCTRL_CLK_DIV_256) {
        LOG_E("GPIOD Debounce CLK div-[%d] config error!\n", div);
        return LL_ERROR;
    }

    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_GPIODDbcSrc_Set(SYSCTRL, src);
    __LL_SYSCTRL_GPIODDbcClkDiv_Set(SYSCTRL, div);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);

    return LL_OK;
}

/**
  * @brief  SYSCTRL LL DFLASH Clock Config
  * @param  src DFLASH Clock Source
  * @param  div DFLASH Clock Div
  * @return LL_StatusETypeDef
  */
LL_StatusETypeDef LL_SYSCTRL_DFLASH_ClkCfg(SYSCTRL_DflashClkSrcETypeDef src, SYSCTRL_ClkDivETypeDef div)
{
    if (div <= SYSCTRL_CLK_DIV_IVD || div > SYSCTRL_CLK_DIV_16) {
        LOG_E("DFLASH CLK div-[%d] config error!\n", div);
        return LL_ERROR;
    }

    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_DFLASHMemClkSrc_Set(SYSCTRL, src);
    __LL_SYSCTRL_DFLASHMemClkDiv_Set(SYSCTRL, div);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);

    return LL_OK;
}

/**
  * @brief  SYSCTRL LL EFLASH Clock Config
  * @param  src EFLASH Clock Source
  * @param  div EFLASH Clock Div
  * @return LL_StatusETypeDef
  */
LL_StatusETypeDef LL_SYSCTRL_EFLASH_ClkCfg(SYSCTRL_EflashClkSrcETypeDef src, SYSCTRL_ClkDivETypeDef div)
{
    if (div <= SYSCTRL_CLK_DIV_IVD || div > SYSCTRL_CLK_DIV_16) {
        LOG_E("EFLASH CLK div-[%d] config error!\n", div);
        return LL_ERROR;
    }

    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_EFLASHMemClkSrc_Set(SYSCTRL, src);
    __LL_SYSCTRL_EFLASHMemClkDiv_Set(SYSCTRL, div);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);

    return LL_OK;
}

/**
  * @brief  SYSCTRL LL ADC Function Clock Config
  * @param  src ADC Function Clock Source
  * @param  div ADC Function Clock Div
  * @return LL_StatusETypeDef
  */
LL_StatusETypeDef LL_SYSCTRL_ADC_FuncClkCfg(SYSCTRL_ADCFuncClkSrcETypeDef src, SYSCTRL_ClkDivETypeDef div)
{
    if (div <= SYSCTRL_CLK_DIV_IVD || div > SYSCTRL_CLK_DIV_4) {
        LOG_E("ADC Function CLK div-[%d] config error!\n", div);
        return LL_ERROR;
    }

    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_ADCFunClkSrc_Set(SYSCTRL, src);
    __LL_SYSCTRL_ADCFunClkDiv_Set(SYSCTRL, div);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);

    return LL_OK;
}

/**
  * @brief  SYSCTRL LL HRPWM Function Clock Config
  * @param  src HRPWM Function Clock Source
  * @param  div HRPWM Function Clock Div
  * @return LL_StatusETypeDef
  */
LL_StatusETypeDef LL_SYSCTRL_HRPWM_FuncClkCfg(SYSCTRL_HRPWMFuncClkSrcETypeDef src, SYSCTRL_ClkDivETypeDef div)
{
    if (div <= SYSCTRL_CLK_DIV_IVD || div > SYSCTRL_CLK_DIV_4) {
        LOG_E("HRPWM Function CLK div-[%d] config error!\n", div);
        return LL_ERROR;
    }

    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_HRPWMFunClkSrc_Set(SYSCTRL, src);
    __LL_SYSCTRL_HRPWMFunClkDiv_Set(SYSCTRL, div);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);

    return LL_OK;
}

/**
  * @brief  SYSCTRL LL SYSCLK freq get
  * @param  None
  * @return SYSCLK freq
  */
uint32_t LL_SYSCTRL_SysclkGet(void)
{
    return SystemCoreClock;
}

/**
  * @brief  SYSCTRL LL AHB Clock freq get
  * @note   AHB Clock is equal to SYSCLK
  * @param  None
  * @return AHB Clock freq
  */
uint32_t LL_SYSCTRL_AHBClkGet(void)
{
    return LL_SYSCTRL_SysclkGet();
}

/**
  * @brief  SYSCTRL LL APB0 Clock freq get
  * @note   APB0 Clock is Div from AHB
  * @param  None
  * @return APB0 Clock freq
  */
uint32_t LL_SYSCTRL_APB0ClkGet(void)
{
    return LL_SYSCTRL_AHBClkGet() / __LL_SYSCTRL_APB0ClkDiv_Get(SYSCTRL);
}

/**
  * @brief  SYSCTRL LL APB1 Clock freq get
  * @note   APB1 Clock is Div from AHB
  * @param  None
  * @return APB1 Clock freq
  */
uint32_t LL_SYSCTRL_APB1ClkGet(void)
{
    return LL_SYSCTRL_AHBClkGet() / __LL_SYSCTRL_APB1ClkDiv_Get(SYSCTRL);
}

/**
  * @}
  */


/** @defgroup SYSCTRL_LL_Exported_Functions_Group2 SYSCTRL PLL Config Functions
  * @brief    SYSCTRL PLL Config Functions
  * @{
  */

/**
  * @brief  SYSCTRL ll PLL0 Config
  * @param  Instance Specifies SYSCTRL peripheral
  * @param  pll0_cfg PLL0 Config Pointer
  * @return LL_StatusETypeDef Config Result
  */
LL_StatusETypeDef LL_SYSCTRL_Pll0Cfg(SYSCTRL_TypeDef *Instance, SYSCTRL_PLLUserCfgTypeDef *pll0_cfg)
{
    uint8_t i, j;
    SYSCTRL_ClkDivETypeDef post_div = SYSCTRL_CLK_DIV_IVD;

    if (Instance == NULL || pll0_cfg == NULL) {
        LOG_E("PLL0 config params error!\n");
        return LL_ERROR;
    }

    for (i = 0; i < ARRAY_SIZE(sysctrl_pll_cfg); i++) {
        if (sysctrl_pll_cfg[i].pll_in_freq  == pll0_cfg->pll_in_freq) {
            for (j = 2; j <= 16; j++) {
                if ((sysctrl_pll_cfg[i].pll_out_freq / j) == pll0_cfg->pll_user_freq && \
                    !(sysctrl_pll_cfg[i].pll_out_freq % j)) {
                    post_div = (SYSCTRL_ClkDivETypeDef)j;
                    break;
                }
            }

            if (post_div != SYSCTRL_CLK_DIV_IVD) {
                break;
            }
        }
    }

    if (i == ARRAY_SIZE(sysctrl_pll_cfg)) {
        LOG_E("Don't match pll0_in_freq-[%d] to generate pll0_out_freq-[%d], please add the config to sysctrl_pll_cfg array!\n", \
              pll0_cfg->pll_in_freq, pll0_cfg->pll_user_freq);
        return LL_ERROR;
    }

    //SYSCTRL CTRL Register Unlock
    __LL_SYSCTRL_CTRLReg_Unlock(Instance);

    switch (pll0_cfg->pll_clk_src) {
        case PLLCLK_SRC_XOSC:
            LL_SYSCTRL_XOSCCfg(Instance);

            LOG_I("PLL0 CLK Source Select XOSC.\n");
            __LL_SYSCTRL_PLL0_RefClk_Set(Instance, SYSCTRL_PLL0_REFCLK_XOSC);
            break;

        case PLLCLK_SRC_RC8M:
            __LL_SYSCTRL_RC8M_En(Instance);

            LOG_I("PLL0 CLK Source Select RC8M.\n");
            __LL_SYSCTRL_PLL0_RefClk_Set(Instance, SYSCTRL_PLL0_REFCLK_RC8M);
            break;

        case PLLCLK_SRC_DFT:
            LOG_I("PLL0 CLK Source Select DFT.\n");
            __LL_SYSCTRL_PLL0_RefClk_Set(Instance, SYSCTRL_PLL0_REFCLK_DFT);
            break;

        default:
            LOG_E("PLL0 CLK Source Select-[%d] Error!\n", pll0_cfg->pll_clk_src);
            return LL_ERROR;
    }

    //PLL0 Pre-Div Config
    if (sysctrl_pll_cfg[i].pll_pre_div == SYSCTRL_CLK_DIV_1) {
        __LL_SYSCTRL_PLL0_PreDiv_1(Instance);
    } else if (sysctrl_pll_cfg[i].pll_pre_div == SYSCTRL_CLK_DIV_2) {
        __LL_SYSCTRL_PLL0_PreDiv_2(Instance);
    } else {
        LOG_E("PLL0 Pre-Div Config-[%d] Error!\n", sysctrl_pll_cfg[i].pll_pre_div);
    }

    //PLL0 Div Config
    if (post_div >= SYSCTRL_CLK_DIV_2 && post_div <= SYSCTRL_CLK_DIV_16) {
        __LL_SYSCTRL_PLL0_DIV_Set(Instance, post_div);
    } else {
        LOG_E("PLL0 Post Div Config-[%d] Error!\n", post_div);
    }

    //FPLL0 integer/fraction Config & Enable & Start
    LL_FPLL_DivStart(FPLL0, sysctrl_pll_cfg[i].fpll_int, sysctrl_pll_cfg[i].fpll_frac);

    //PLL0 VCO Band and Gain Config and Enable
    __LL_SYSCTRL_PLL0_Band_Set(Instance, sysctrl_pll_cfg[i].pll_vco_band);
    __LL_SYSCTRL_PLL0_GVCO_Set(Instance, sysctrl_pll_cfg[i].pll_vco_gain);
    __LL_SYSCTRL_PLL0_En(Instance);

    //Wait for PLL0 Lock
    LOG_D("Wait for PLL0 lock output\n");

    while (!__LL_SYSCTRL_PLL0_IsLocked(Instance))
        ;

    LOG_D("PLL0 lock Success\n");

    //SYSCTRL Register Lock
    __LL_SYSCTRL_Reg_Lock(Instance);

    return LL_OK;
}

/**
  * @brief  SYSCTRL ll PLL1 Config
  * @note   PLL1 don't config post-div, which is used for ADC/HRPWM module generally
  * @param  Instance Specifies SYSCTRL peripheral
  * @param  pll1_cfg PLL1 Config Pointer
  * @return LL_StatusETypeDef Config Result
  */
LL_StatusETypeDef LL_SYSCTRL_Pll1Cfg(SYSCTRL_TypeDef *Instance, SYSCTRL_PLLUserCfgTypeDef *pll1_cfg)
{
    uint8_t i;

    if (Instance == NULL || pll1_cfg == NULL) {
        LOG_E("PLL1 config params error!\n");
        return LL_ERROR;
    }

    for (i = 0; i < ARRAY_SIZE(sysctrl_pll_cfg); i++) {
        if (sysctrl_pll_cfg[i].pll_in_freq  == pll1_cfg->pll_in_freq && \
            sysctrl_pll_cfg[i].pll_out_freq == pll1_cfg->pll_user_freq) {
            break;
        }
    }

    if (i == ARRAY_SIZE(sysctrl_pll_cfg)) {
        LOG_E("Don't match pll1_in_freq-[%d] to generate pll1_out_freq-[%d], please add the config to sysctrl_pll_cfg array!\n", \
              pll1_cfg->pll_in_freq, pll1_cfg->pll_user_freq);
        return LL_ERROR;
    }

    //SYSCTRL CTRL Register Unlock
    __LL_SYSCTRL_CTRLReg_Unlock(Instance);

    switch (pll1_cfg->pll_clk_src) {
        case PLLCLK_SRC_XOSC:
            LL_SYSCTRL_XOSCCfg(Instance);

            LOG_I("PLL1 CLK Source Select XOSC.\n");
            __LL_SYSCTRL_PLL1_RefClk_Set(Instance, SYSCTRL_PLL1_REFCLK_XOSC);
            break;

        case PLLCLK_SRC_RC8M:
            __LL_SYSCTRL_RC8M_En(Instance);

            LOG_I("PLL1 CLK Source Select RC8M.\n");
            __LL_SYSCTRL_PLL1_RefClk_Set(Instance, SYSCTRL_PLL1_REFCLK_RC8M);
            break;

        case PLLCLK_SRC_DFT:
            LOG_I("PLL1 CLK Source Select DFT.\n");
            __LL_SYSCTRL_PLL1_RefClk_Set(Instance, SYSCTRL_PLL1_REFCLK_DFT);
            break;

        default:
            LOG_E("PLL1 CLK Source Select-[%d] Error!\n", pll1_cfg->pll_clk_src);
            return LL_ERROR;
    }

    //PLL1 Pre-Div Config
    if (sysctrl_pll_cfg[i].pll_pre_div == SYSCTRL_CLK_DIV_1) {
        __LL_SYSCTRL_PLL1_PreDiv_1(Instance);
    } else if (sysctrl_pll_cfg[i].pll_pre_div == SYSCTRL_CLK_DIV_2) {
        __LL_SYSCTRL_PLL1_PreDiv_2(Instance);
    } else {
        LOG_E("PLL1 Pre-Div Config-[%d] Error!\n", sysctrl_pll_cfg[i].pll_pre_div);
    }

    //FPLL1 integer/fraction Config & Enable & Start
    LL_FPLL_DivStart(FPLL1, sysctrl_pll_cfg[i].fpll_int, sysctrl_pll_cfg[i].fpll_frac);

    //PLL1 VCO Band and Gain Config and Enable
    __LL_SYSCTRL_PLL1_Band_Set(Instance, sysctrl_pll_cfg[i].pll_vco_band);
    __LL_SYSCTRL_PLL1_GVCO_Set(Instance, sysctrl_pll_cfg[i].pll_vco_gain);
    __LL_SYSCTRL_PLL1_En(Instance);

    //Wait for PLL1 Lock
    LOG_D("Wait for PLL1 lock output\n");

    while (!__LL_SYSCTRL_PLL1_IsLocked(Instance))
        ;

    LOG_D("PLL1 lock Success\n");

    //SYSCTRL Register Lock
    __LL_SYSCTRL_Reg_Lock(Instance);

    return LL_OK;
}

/**
  * @brief  SYSCTRL ll PLL2 Config
  * @param  Instance Specifies SYSCTRL peripheral
  * @param  pll2_cfg PLL2 Config Pointer
  * @return LL_StatusETypeDef Config Result
  */
LL_StatusETypeDef LL_SYSCTRL_Pll2Cfg(SYSCTRL_TypeDef *Instance, SYSCTRL_PLLUserCfgTypeDef *pll2_cfg)
{
    uint8_t i, j;
    SYSCTRL_ClkDivETypeDef post_div = SYSCTRL_CLK_DIV_IVD;

    if (Instance == NULL || pll2_cfg == NULL) {
        LOG_E("PLL2 config params error!\n");
        return LL_ERROR;
    }

    for (i = 0; i < ARRAY_SIZE(sysctrl_pll_cfg); i++) {
        if (sysctrl_pll_cfg[i].pll_in_freq  == pll2_cfg->pll_in_freq) {
            for (j = 2; j <= 16; j++) {
                if ((sysctrl_pll_cfg[i].pll_out_freq / j) == pll2_cfg->pll_user_freq && !(sysctrl_pll_cfg[i].pll_out_freq % j)) {
                    post_div = (SYSCTRL_ClkDivETypeDef)j;
                    break;
                }
            }

            if (post_div != SYSCTRL_CLK_DIV_IVD) {
                break;
            }
        }
    }

    if (i == ARRAY_SIZE(sysctrl_pll_cfg)) {
        LOG_E("Don't match pll2_in_freq-[%d] to generate pll2_out_freq-[%d], please add the config to sysctrl_pll_cfg array!\n", \
              pll2_cfg->pll_in_freq, pll2_cfg->pll_user_freq);
        return LL_ERROR;
    }

    //SYSCTRL CTRL Register Unlock
    __LL_SYSCTRL_CTRLReg_Unlock(Instance);

    switch (pll2_cfg->pll_clk_src) {
        case PLLCLK_SRC_XOSC:
            LL_SYSCTRL_XOSCCfg(Instance);

            LOG_I("PLL2 CLK Source Select XOSC.\n");
            __LL_SYSCTRL_PLL2_RefClk_Set(Instance, SYSCTRL_PLL2_REFCLK_XOSC);
            break;

        case PLLCLK_SRC_RC8M:
            __LL_SYSCTRL_RC8M_En(Instance);

            LOG_I("PLL2 CLK Source Select RC8M.\n");
            __LL_SYSCTRL_PLL2_RefClk_Set(Instance, SYSCTRL_PLL2_REFCLK_RC8M);
            break;

        case PLLCLK_SRC_DFT:
            LOG_I("PLL2 CLK Source Select DFT.\n");
            __LL_SYSCTRL_PLL2_RefClk_Set(Instance, SYSCTRL_PLL2_REFCLK_DFT);
            break;

        default:
            LOG_E("PLL2 CLK Source Select-[%d] Error!\n", pll2_cfg->pll_clk_src);
            return LL_ERROR;
    }

    //PLL2 Pre-Div Config
    if (sysctrl_pll_cfg[i].pll_pre_div == SYSCTRL_CLK_DIV_1) {
        __LL_SYSCTRL_PLL2_PreDiv_1(Instance);
    } else if (sysctrl_pll_cfg[i].pll_pre_div == SYSCTRL_CLK_DIV_2) {
        __LL_SYSCTRL_PLL2_PreDiv_2(Instance);
    } else {
        LOG_E("PLL2 Pre-Div Config-[%d] Error!\n", sysctrl_pll_cfg[i].pll_pre_div);
    }

    //PLL2 Div Config
    if (post_div >= SYSCTRL_CLK_DIV_2 && post_div <= SYSCTRL_CLK_DIV_16) {
        __LL_SYSCTRL_PLL2_DIV_Set(Instance, post_div);
    } else {
        LOG_E("PLL2 Post Div Config-[%d] Error!\n", post_div);
    }

    //FPLL2 integer/fraction Config & Enable & Start
    LL_FPLL_DivStart(FPLL2, sysctrl_pll_cfg[i].fpll_int, sysctrl_pll_cfg[i].fpll_frac);

    //PLL2 VCO Band and Gain Config and Enable
    __LL_SYSCTRL_PLL2_Band_Set(Instance, sysctrl_pll_cfg[i].pll_vco_band);
    __LL_SYSCTRL_PLL2_GVCO_Set(Instance, sysctrl_pll_cfg[i].pll_vco_gain);
    __LL_SYSCTRL_PLL2_En(Instance);

    //Wait for PLL2 Lock
    LOG_D("Wait for PLL2 lock output\n");

    while (!__LL_SYSCTRL_PLL2_IsLocked(Instance))
        ;

    LOG_D("PLL2 lock Success\n");

    //SYSCTRL Register Lock
    __LL_SYSCTRL_Reg_Lock(Instance);

    return LL_OK;
}
/**
  * @}
  */

/** @defgroup SYSCTRL_LL_Exported_Functions_Group3 SYSCTRL Peripherals Clock and Reset control Functions
  * @brief    SYSCTRL Peripherals Clock and Reset control Functions
  * @{
  */

/**
  * @brief  SYSCTRL LSTIMER Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_SYSCTRL_LSTMR_ClkEnRstRelease(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_LSTIMERBusClk_En(SYSCTRL);
    __LL_SYSCTRL_LSTIMERSoftRst_Release(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL LSTIMER Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_SYSCTRL_LSTMR_ClkDisRstAssert(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_LSTIMERBusClk_Dis(SYSCTRL);
    __LL_SYSCTRL_LSTIMERSoftRst_Assert(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL Uart1 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_SYSCTRL_UART1_ClkEnRstRelease(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_UART1BusClk_En(SYSCTRL);
    __LL_SYSCTRL_UART1SoftRst_Release(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL Uart1 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_SYSCTRL_UART1_ClkDisRstAssert(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_UART1BusClk_Dis(SYSCTRL);
    __LL_SYSCTRL_UART1SoftRst_Assert(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL Uart0 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_SYSCTRL_UART0_ClkEnRstRelease(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_UART0BusClk_En(SYSCTRL);
    __LL_SYSCTRL_UART0SoftRst_Release(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL Uart0 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_SYSCTRL_UART0_ClkDisRstAssert(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_UART0BusClk_Dis(SYSCTRL);
    __LL_SYSCTRL_UART0SoftRst_Assert(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL I2C1 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_SYSCTRL_I2C1_ClkEnRstRelease(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_I2C1BusClk_En(SYSCTRL);
    __LL_SYSCTRL_I2C1SoftRst_Release(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL I2C1 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_SYSCTRL_I2C1_ClkDisRstAssert(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_I2C1BusClk_Dis(SYSCTRL);
    __LL_SYSCTRL_I2C1SoftRst_Assert(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL I2C0 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_SYSCTRL_I2C0_ClkEnRstRelease(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_I2C0BusClk_En(SYSCTRL);
    __LL_SYSCTRL_I2C0SoftRst_Release(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL I2C0 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_SYSCTRL_I2C0_ClkDisRstAssert(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_I2C0BusClk_Dis(SYSCTRL);
    __LL_SYSCTRL_I2C0SoftRst_Assert(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL ECU Bus&Function Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_SYSCTRL_ECU_ClkEnRstRelease(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_ECUBusClk_En(SYSCTRL);
    __LL_SYSCTRL_ECUFunClk_En(SYSCTRL);
    __LL_SYSCTRL_ECUSoftRst_Release(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL ECU Bus&Function Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_SYSCTRL_ECU_ClkDisRstAssert(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_ECUBusClk_Dis(SYSCTRL);
    __LL_SYSCTRL_ECUFunClk_Dis(SYSCTRL);
    __LL_SYSCTRL_ECUSoftRst_Assert(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL IIR4 Bus&Function Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_SYSCTRL_IIR4_ClkEnRstRelease(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_IIR4BusClk_En(SYSCTRL);
    __LL_SYSCTRL_IIR4FunClk_En(SYSCTRL);
    __LL_SYSCTRL_IIR4SoftRst_Release(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL IIR4 Bus&Function Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_SYSCTRL_IIR4_ClkDisRstAssert(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_IIR4BusClk_Dis(SYSCTRL);
    __LL_SYSCTRL_IIR4FunClk_Dis(SYSCTRL);
    __LL_SYSCTRL_IIR4SoftRst_Assert(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL IIR3 Bus&Function Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_SYSCTRL_IIR3_ClkEnRstRelease(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_IIR3BusClk_En(SYSCTRL);
    __LL_SYSCTRL_IIR3FunClk_En(SYSCTRL);
    __LL_SYSCTRL_IIR3SoftRst_Release(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL IIR3 Bus&Function Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_SYSCTRL_IIR3_ClkDisRstAssert(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_IIR3BusClk_Dis(SYSCTRL);
    __LL_SYSCTRL_IIR3FunClk_Dis(SYSCTRL);
    __LL_SYSCTRL_IIR3SoftRst_Assert(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL IIR2 Bus&Function Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_SYSCTRL_IIR2_ClkEnRstRelease(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_IIR2BusClk_En(SYSCTRL);
    __LL_SYSCTRL_IIR2FunClk_En(SYSCTRL);
    __LL_SYSCTRL_IIR2SoftRst_Release(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL IIR2 Bus&Function Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_SYSCTRL_IIR2_ClkDisRstAssert(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_IIR2BusClk_Dis(SYSCTRL);
    __LL_SYSCTRL_IIR2FunClk_Dis(SYSCTRL);
    __LL_SYSCTRL_IIR2SoftRst_Assert(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL IIR1 Bus&Function Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_SYSCTRL_IIR1_ClkEnRstRelease(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_IIR1BusClk_En(SYSCTRL);
    __LL_SYSCTRL_IIR1FunClk_En(SYSCTRL);
    __LL_SYSCTRL_IIR1SoftRst_Release(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL IIR1 Bus&Function Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_SYSCTRL_IIR1_ClkDisRstAssert(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_IIR1BusClk_Dis(SYSCTRL);
    __LL_SYSCTRL_IIR1FunClk_Dis(SYSCTRL);
    __LL_SYSCTRL_IIR1SoftRst_Assert(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL IIR0 Bus&Function Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_SYSCTRL_IIR0_ClkEnRstRelease(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_IIR0BusClk_En(SYSCTRL);
    __LL_SYSCTRL_IIR0FunClk_En(SYSCTRL);
    __LL_SYSCTRL_IIR0SoftRst_Release(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL IIR0 Bus&Function Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_SYSCTRL_IIR0_ClkDisRstAssert(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_IIR0BusClk_Dis(SYSCTRL);
    __LL_SYSCTRL_IIR0FunClk_Dis(SYSCTRL);
    __LL_SYSCTRL_IIR0SoftRst_Assert(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL DALI Bus&Function Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_SYSCTRL_DALI_ClkEnRstRelease(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_DALIBusClk_En(SYSCTRL);
    __LL_SYSCTRL_DALISoftRst_Release(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL DALI Bus&Function Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_SYSCTRL_DALI_ClkDisRstAssert(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_DALIBusClk_Dis(SYSCTRL);
    __LL_SYSCTRL_DALISoftRst_Assert(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL FPLL2 Reset Release
  * @param  None
  * @return None
  */
void LL_SYSCTRL_FPLL2_RstRelease(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_FPLL2SoftRst_Release(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL FPLL2 Reset Assert
  * @param  None
  * @return None
  */
void LL_SYSCTRL_FPLL2_RstAssert(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_FPLL2SoftRst_Assert(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL FPLL1 Reset Release
  * @param  None
  * @return None
  */
void LL_SYSCTRL_FPLL1_RstRelease(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_FPLL1SoftRst_Release(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL FPLL1 Reset Assert
  * @param  None
  * @return None
  */
void LL_SYSCTRL_FPLL1_RstAssert(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_FPLL1SoftRst_Assert(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL FPLL0 Reset Release
  * @param  None
  * @return None
  */
void LL_SYSCTRL_FPLL0_RstRelease(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_FPLL0SoftRst_Release(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL FPLL0 Reset Assert
  * @param  None
  * @return None
  */
void LL_SYSCTRL_FPLL0_RstAssert(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_FPLL0SoftRst_Assert(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL USB Bus&Function Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_SYSCTRL_USB_ClkEnRstRelease(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_USBBusClk_En(SYSCTRL);
    __LL_SYSCTRL_USBFunClk_En(SYSCTRL);
    __LL_SYSCTRL_USBSoftRst_Release(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL USB Bus&Function Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_SYSCTRL_USB_ClkDisRstAssert(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_USBBusClk_Dis(SYSCTRL);
    __LL_SYSCTRL_USBFunClk_Dis(SYSCTRL);
    __LL_SYSCTRL_USBSoftRst_Assert(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL DFLASH Bus&Memory Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_SYSCTRL_DFLASH_ClkEnRstRelease(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_DFLASHBusClk_En(SYSCTRL);
    __LL_SYSCTRL_DFLASHMemClk_En(SYSCTRL);
    __LL_SYSCTRL_DFLASHSoftRst_Release(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL DFLASH Bus&Memory Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_SYSCTRL_DFLASH_ClkDisRstAssert(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_DFLASHBusClk_Dis(SYSCTRL);
    __LL_SYSCTRL_DFLASHMemClk_Dis(SYSCTRL);
    __LL_SYSCTRL_DFLASHSoftRst_Assert(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL EFLASH Bus&Memory Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_SYSCTRL_EFLASH_ClkEnRstRelease(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_EFLASHBusClk_En(SYSCTRL);
    __LL_SYSCTRL_EFLASHMemClk_En(SYSCTRL);
    __LL_SYSCTRL_EFLASHSoftRst_Release(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL EFLASH Bus&Memory Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_SYSCTRL_EFLASH_ClkDisRstAssert(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_EFLASHBusClk_Dis(SYSCTRL);
    __LL_SYSCTRL_EFLASHMemClk_Dis(SYSCTRL);
    __LL_SYSCTRL_EFLASHSoftRst_Assert(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL HRPWM Bus&Function Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_SYSCTRL_HRPWM_ClkEnRstRelease(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_HRPWMBusClk_En(SYSCTRL);
    __LL_SYSCTRL_HRPWMFunClk_En(SYSCTRL);
    __LL_SYSCTRL_HRPWMSoftRst_Release(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL HRPWM Bus&Function Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_SYSCTRL_HRPWM_ClkDisRstAssert(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_HRPWMBusClk_Dis(SYSCTRL);
    __LL_SYSCTRL_HRPWMFunClk_Dis(SYSCTRL);
    __LL_SYSCTRL_HRPWMSoftRst_Assert(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL ADC Bus&Function Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_SYSCTRL_ADC_ClkEnRstRelease(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_ADCBusClk_En(SYSCTRL);
    __LL_SYSCTRL_ADCFunClk_En(SYSCTRL);
    __LL_SYSCTRL_ADCSoftRst_Release(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL ADC Bus&Function Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_SYSCTRL_ADC_ClkDisRstAssert(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_ADCBusClk_Dis(SYSCTRL);
    __LL_SYSCTRL_ADCFunClk_Dis(SYSCTRL);
    __LL_SYSCTRL_ADCSoftRst_Assert(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL DAC Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_SYSCTRL_DAC_ClkEnRstRelease(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_DACBusClk_En(SYSCTRL);
    __LL_SYSCTRL_DACSoftRst_Release(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL DAC Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_SYSCTRL_DAC_ClkDisRstAssert(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_DACBusClk_Dis(SYSCTRL);
    __LL_SYSCTRL_DACSoftRst_Assert(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL CMP Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_SYSCTRL_CMP_ClkEnRstRelease(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_CMPBusClk_En(SYSCTRL);
    __LL_SYSCTRL_CMPSoftRst_Release(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL CMP Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_SYSCTRL_CMP_ClkDisRstAssert(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_CMPBusClk_Dis(SYSCTRL);
    __LL_SYSCTRL_CMPSoftRst_Assert(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL GPIOD Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_SYSCTRL_GPIOD_ClkEnRstRelease(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_GPIODBusClk_En(SYSCTRL);
    __LL_SYSCTRL_GPIODSoftRst_Release(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL GPIOD Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_SYSCTRL_GPIOD_ClkDisRstAssert(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_GPIODBusClk_Dis(SYSCTRL);
    __LL_SYSCTRL_GPIODSoftRst_Assert(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL GPIOC Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_SYSCTRL_GPIOC_ClkEnRstRelease(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_GPIOCBusClk_En(SYSCTRL);
    __LL_SYSCTRL_GPIOCSoftRst_Release(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL GPIOC Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_SYSCTRL_GPIOC_ClkDisRstAssert(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_GPIOCBusClk_Dis(SYSCTRL);
    __LL_SYSCTRL_GPIOCSoftRst_Assert(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL GPIOB Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_SYSCTRL_GPIOB_ClkEnRstRelease(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_GPIOBBusClk_En(SYSCTRL);
    __LL_SYSCTRL_GPIOBSoftRst_Release(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL GPIOB Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_SYSCTRL_GPIOB_ClkDisRstAssert(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_GPIOBBusClk_Dis(SYSCTRL);
    __LL_SYSCTRL_GPIOBSoftRst_Assert(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL GPIOA Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_SYSCTRL_GPIOA_ClkEnRstRelease(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_GPIOABusClk_En(SYSCTRL);
    __LL_SYSCTRL_GPIOASoftRst_Release(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL GPIOA Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_SYSCTRL_GPIOA_ClkDisRstAssert(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_GPIOABusClk_Dis(SYSCTRL);
    __LL_SYSCTRL_GPIOASoftRst_Assert(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL HSTIMER Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_SYSCTRL_HSTMR_ClkEnRstRelease(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_HSTIMERBusClk_En(SYSCTRL);
    __LL_SYSCTRL_HSTIMERSoftRst_Release(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL HSTIMER Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_SYSCTRL_HSTMR_ClkDisRstAssert(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_HSTIMERBusClk_Dis(SYSCTRL);
    __LL_SYSCTRL_HSTIMERSoftRst_Assert(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL CAN Bus&Function Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_SYSCTRL_CAN_ClkEnRstRelease(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_CANBusClk_En(SYSCTRL);
    __LL_SYSCTRL_CANFunClk_En(SYSCTRL);
    __LL_SYSCTRL_CANSoftRst_Release(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL CAN Bus&Function Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_SYSCTRL_CAN_ClkDisRstAssert(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_CANBusClk_Dis(SYSCTRL);
    __LL_SYSCTRL_CANFunClk_Dis(SYSCTRL);
    __LL_SYSCTRL_CANSoftRst_Assert(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL DMA Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_SYSCTRL_DMA_ClkEnRstRelease(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_DMABusClk_En(SYSCTRL);
    __LL_SYSCTRL_DMASoftRst_Release(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL DMA Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_SYSCTRL_DMA_ClkDisRstAssert(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_DMABusClk_Dis(SYSCTRL);
    __LL_SYSCTRL_DMASoftRst_Assert(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}


/**
  * @brief  SYSCTRL LL all peripheral reset assert
  * @note   All peripheral include system bus(AHB/APB0/APB1)
  * @param  None
  * @return None
  */
void LL_SYSCTRL_AllPeriphRstAssert(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_SysSoftRstAll_Assert(SYSCTRL);
    __LL_SYSCTRL_APB0SoftRstAll_Assert(SYSCTRL);
    __LL_SYSCTRL_APB1SoftRstAll_Assert(SYSCTRL);
    __LL_SYSCTRL_AHBSoftRstAll_Assert(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @brief  SYSCTRL LL all peripheral reset release
  * @note   All peripheral include system bus(AHB/APB0/APB1)
  * @param  None
  * @return None
  */
void LL_SYSCTRL_AllPeriphRstRelease(void)
{
    __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_SysSoftRstAll_Release(SYSCTRL);
    __LL_SYSCTRL_APB0SoftRstAll_Release(SYSCTRL);
    __LL_SYSCTRL_APB1SoftRstAll_Release(SYSCTRL);
    __LL_SYSCTRL_AHBSoftRstAll_Release(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}
/**
  * @}
  */

/** @defgroup SYSCTRL_LL_Exported_Functions_Group4 SYSCTRL Misc Config Functions
  * @brief    SYSCTRL Misc Config Functions
  * @{
  */

/**
  * @brief  SYSCTRL LL PMU Config
  * @param  None
  * @return None
  */
void LL_SYSCTRL_PMUCfg(void)
{
    __LL_SYSCTRL_FLSReg_Unlock(SYSCTRL);
    __LL_SYSCTRL_CUR_RES_Set(SYSCTRL, 0);
    __LL_SYSCTRL_BGR_DRD_Dis(SYSCTRL);
    __LL_SYSCTRL_BGR_Filter_En(SYSCTRL);
    __LL_SYSCTRL_Reg_Lock(SYSCTRL);
}

/**
  * @}
  */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @addtogroup SYSCTRL_LL_Private_Functions
  * @{
  */

/**
  * @brief  SYSCTRL LL XOSC Config
  * @param  Instance Specifies SYSCTRL peripheral
  * @note   Must unlock SYSCTRL CTRL Reg before call this function
  * @return None
  */
static void LL_SYSCTRL_XOSCCfg(SYSCTRL_TypeDef *Instance)
{
    //Check SYSCTRL CTRL Reg unlock or not
    if (!__LL_SYSCTRL_IsCTRLRegUnlock(Instance)) {
        LOG_E("SYSCTRL CTRL Reg is Lock, please unlock it before call this function!\n");
        return;
    }

    __LL_SYSCTRL_XOSC_En(Instance);
}
/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

