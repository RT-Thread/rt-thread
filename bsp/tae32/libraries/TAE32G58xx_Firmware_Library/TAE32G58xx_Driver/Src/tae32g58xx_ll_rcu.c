/**
  ******************************************************************************
  * @file    tae32g58xx_ll_rcu.c
  * @author  MCD Application Team
  * @brief   RCU LL module driver
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
#include "tae32g58xx_ll.h"
#include "stdlib.h"


#define DBG_TAG             "RCU LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae_dbg.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @defgroup RCU_LL RCU LL
  * @brief    RCU LL Module Driver
  * @{
  */


/* Private Constants ---------------------------------------------------------*/
/** @defgroup RCU_LL_Private_Functions RCU LL Private Functions
  * @brief    RCU LL Private Functions
  * @{
  */
static void LL_RCU_PLL0Cali_ADC0ClkCfgRst(RCU_TypeDef *Instance, RCU_ClkSrcETypeDef src, RCU_ClkDivETypeDef div);
static void LL_RCU_PLL0Cali_ADC0ClkRstDis(RCU_TypeDef *Instance);
static uint8_t LL_RCU_PLL0Cali(RCU_TypeDef *Instance);
/**
  * @}
  */


/* Private Macros ------------------------------------------------------------*/
/** @defgroup RCU_LL_Private_Macros RCU LL Private Macros
  * @brief    RCU LL Private Macros
  * @{
  */

/** 
  * @brief  Default System Clock
  */
#define LL_RCU_SYS_CLK_DEFAULT                      (180000000UL) //360000000/2

/** 
  * @brief  Max System Clock
  */
#define LL_RCU_SYS_CLK_MAX                          (200000000UL) //400000000/2

/**
  * @}
  */


/* Private Types -------------------------------------------------------------*/
/** @defgroup RCU_LL_Private_Types RCU LL Private Types
  * @brief    RCU LL Private Types
  * @{
  */

/**
  * @brief RCU PLL0/1 Config Type Define
  * @note pll_out_freq is before PLL Post Div
  */
typedef struct __RCU_PLLCfgTypeDef {
    uint32_t pll_in_freq;       /*!< PLL Input Freq     */
    uint32_t pll_out_freq;      /*!< PLL Output Freq    */
    uint8_t  pll_pre_div;       /*!< PLL Pre-Div        */
    uint16_t pll_int;           /*!< PLL Integer        */
    uint16_t pll_frac;          /*!< PLL Fraction       */
    uint32_t pll_vco_band;      /*!< PLL VCO Band       */
    uint32_t pll_vco_gain;      /*!< PLL VCO Gain       */
} RCU_PLLCfgTypeDef;

/**
  * @}
  */


/* Private Variables ---------------------------------------------------------*/
/** @defgroup RCU_LL_Private_Variables RCU LL Private Variables
  * @brief    RCU LL Private Variables
  * @{
  */

/**
  * @brief SYSCLK PLL Config Const Array Definition
  */
static const RCU_PLLCfgTypeDef rcu_pll_cfg[] = {
    {8000000,  360000000, 1, 22, 0x8000, PLL_BAND_3, PLL_GVCO_2},   /*!<PLLIn->8M,PLLOut->360M  */
    {8000000,  380000000, 1, 23, 0xC000, PLL_BAND_3, PLL_GVCO_2},   /*!<PLLIn->8M,PLLOut->380M  */
    {8000000,  400000000, 1, 25, 0,      PLL_BAND_3, PLL_GVCO_2},   /*!<PLLIn->8M,PLLOut->400M  */
    {8000000,  420000000, 1, 26, 0x4000, PLL_BAND_3, PLL_GVCO_2},   /*!<PLLIn->8M,PLLOut->420M  */
    {8000000,  440000000, 1, 27, 0x8000, PLL_BAND_3, PLL_GVCO_2},   /*!<PLLIn->8M,PLLOut->440M  */
    {8000000,  460000000, 1, 28, 0xC000, PLL_BAND_3, PLL_GVCO_2},   /*!<PLLIn->8M,PLLOut->460M  */
    {8000000,  480000000, 1, 30, 0,      PLL_BAND_3, PLL_GVCO_2},   /*!<PLLIn->8M,PLLOut->480M  */

    {12000000, 360000000, 1, 15, 0,      PLL_BAND_3, PLL_GVCO_2},   /*!<PLLIn->12M,PLLOut->360M */
    {12000000, 380000000, 1, 15, 0xD555, PLL_BAND_3, PLL_GVCO_2},   /*!<PLLIn->12M,PLLOut->380M */
    {12000000, 400000000, 1, 16, 0xAAAA, PLL_BAND_3, PLL_GVCO_2},   /*!<PLLIn->12M,PLLOut->400M */
    {12000000, 420000000, 1, 17, 0x8000, PLL_BAND_3, PLL_GVCO_2},   /*!<PLLIn->12M,PLLOut->420M */
    {12000000, 440000000, 1, 18, 0x5555, PLL_BAND_3, PLL_GVCO_2},   /*!<PLLIn->12M,PLLOut->440M */
    {12000000, 460000000, 1, 19, 0x2AAA, PLL_BAND_3, PLL_GVCO_2},   /*!<PLLIn->12M,PLLOut->460M */
    {12000000, 480000000, 1, 20, 0,      PLL_BAND_3, PLL_GVCO_2},   /*!<PLLIn->12M,PLLOut->480M */

    {8000000,  100000000, 1, 6,  0x4000, PLL_BAND_0, PLL_GVCO_2},   /*!<PLLIn->8M,PLLOut->100M  */
    {8000000,  110000000, 1, 6,  0xe000, PLL_BAND_0, PLL_GVCO_2},   /*!<PLLIn->8M,PLLOut->110M  */
    {8000000,  120000000, 1, 7,  0x8000, PLL_BAND_0, PLL_GVCO_2},   /*!<PLLIn->8M,PLLOut->120M  */
    {8000000,  130000000, 1, 8,  0x2000, PLL_BAND_0, PLL_GVCO_2},   /*!<PLLIn->8M,PLLOut->130M  */

    {8000000,  140000000, 1, 8,  0xc000, PLL_BAND_0, PLL_GVCO_2},   /*!<PLLIn->8M,PLLOut->140M  */
    {8000000,  150000000, 1, 9,  0x6000, PLL_BAND_0, PLL_GVCO_2},   /*!<PLLIn->8M,PLLOut->150M  */
    {8000000,  160000000, 1, 10, 0,      PLL_BAND_0, PLL_GVCO_2},   /*!<PLLIn->8M,PLLOut->160M  */
    {8000000,  170000000, 1, 10, 0xa000, PLL_BAND_0, PLL_GVCO_2},   /*!<PLLIn->8M,PLLOut->170M  */

    {8000000,  180000000, 1, 11, 0x4000, PLL_BAND_0, PLL_GVCO_2},   /*!<PLLIn->8M,PLLOut->180M  */
    {8000000,  190000000, 1, 11, 0xe000, PLL_BAND_0, PLL_GVCO_2},   /*!<PLLIn->8M,PLLOut->190M  */
    {8000000,  200000000, 1, 12, 0x8000, PLL_BAND_0, PLL_GVCO_2},   /*!<PLLIn->8M,PLLOut->200M  */

    {8000000,  210000000, 1, 13, 0x2000, PLL_BAND_1, PLL_GVCO_2},   /*!<PLLIn->8M,PLLOut->210M  */
    {8000000,  220000000, 1, 13, 0xc000, PLL_BAND_1, PLL_GVCO_2},   /*!<PLLIn->8M,PLLOut->220M  */
    {8000000,  230000000, 1, 14, 0x6000, PLL_BAND_1, PLL_GVCO_2},   /*!<PLLIn->8M,PLLOut->230M  */
};

/**
  * @}
  */


/* Private Function Prototypes -----------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup RCU_LL_Exported_Functions RCU LL Exported Functions
  * @brief    RCU LL Exported Functions
  * @{
  */

/** @defgroup RCU_LL_Exported_Functions_Group1 RCU Clock Config Functions
  * @brief    RCU Clock Config Functions
  * @{
  */

/**
  * @brief  RCU LL SYSCLK Init
  * @param  Instance Specifies RCU peripheral
  * @param  sysclk_cfg SYSCLK Config Pointer
  * @return Status of the Initialization
  */
LL_StatusETypeDef LL_RCU_SysclkInit(RCU_TypeDef *Instance, RCU_SysclkUserCfgTypeDef *sysclk_cfg)
{
    RCU_PLLUserCfgTypeDef pll0_cfg;
    LL_StatusETypeDef ret = LL_ERROR;

    //Assert param
    assert_param(IS_RCU_ALL_INSTANCE(Instance));
    assert_param(sysclk_cfg != NULL);
    assert_param(sysclk_cfg->sysclk_freq);

    if (!IS_RCU_ALL_INSTANCE(Instance) || sysclk_cfg == NULL || !sysclk_cfg->sysclk_freq) {
        return LL_INVALID;
    }

    //Auto Freq Config
    if (sysclk_cfg->sysclk_src == SYSCLK_SRC_PLL0DivClk) {
        if (sysclk_cfg->pll0clk_src == PLLCLK_SRC_HSE) {            //PLL0 CLK Source HSE
            sysclk_cfg->pll0clk_src_freq = HSE_VALUE;
        } else if (sysclk_cfg->pll0clk_src == PLLCLK_SRC_HSI) {     //PLL0 CLK Source HSI
            sysclk_cfg->pll0clk_src_freq = HSI_VALUE;
        }
    } else if (sysclk_cfg->sysclk_src == SYSCLK_SRC_RC32K) {
        sysclk_cfg->sysclk_freq = LSI_VALUE;
    } else if (sysclk_cfg->sysclk_src == SYSCLK_SRC_RC8M) {
        sysclk_cfg->sysclk_freq = HSI_VALUE;
    } else if (sysclk_cfg->sysclk_src == SYSCLK_SRC_XOSC) {
        sysclk_cfg->sysclk_freq = HSE_VALUE;
    }

    //Check APB0/APB1/AHB Clock Div to be valid
    if (sysclk_cfg->apb0_clk_div == RCU_CLK_DIV_IVD || sysclk_cfg->apb0_clk_div < RCU_CLK_DIV_2 ||
        sysclk_cfg->apb0_clk_div > RCU_CLK_DIV_16) {
        sysclk_cfg->apb0_clk_div = RCU_CLK_DIV_2;
    }

    if (sysclk_cfg->apb1_clk_div == RCU_CLK_DIV_IVD || sysclk_cfg->apb1_clk_div < RCU_CLK_DIV_2 ||
        sysclk_cfg->apb1_clk_div > RCU_CLK_DIV_16) {
        sysclk_cfg->apb1_clk_div = RCU_CLK_DIV_2;
    }

    if (sysclk_cfg->ahb_clk_div == RCU_CLK_DIV_IVD || sysclk_cfg->ahb_clk_div > RCU_CLK_DIV_64) {
        sysclk_cfg->ahb_clk_div = RCU_CLK_DIV_1;
    }

    //RCU Register Write Unlock
    __LL_RCU_RegWrite_Unlock(Instance);

    //Config SYSCLK
    switch (sysclk_cfg->sysclk_src) {
        case SYSCLK_SRC_RC32K:
            LOG_I("SYSCLK-[%d] source select RC32K.\n", sysclk_cfg->sysclk_freq);
            __LL_RCU_SysClkSrc_Set(Instance, SYSCLK_SRC_RC32K);
            ret = LL_OK;
            break;

        case SYSCLK_SRC_RC8M:
            LOG_I("SYSCLK-[%d] source select RC8M.\n", sysclk_cfg->sysclk_freq);
            __LL_RCU_HSI_En(Instance);
            __LL_RCU_SysClkSrc_Set(Instance, SYSCLK_SRC_RC8M);
            ret = LL_OK;
            break;

        case SYSCLK_SRC_PLL0DivClk:

            //SYSCLK Select RC8M Temporary if current SYSCLK select PLL0
            if ((RCU_SysclkSrcETypeDef)__LL_RCU_SysClkSrc_Get(Instance) == SYSCLK_SRC_PLL0DivClk) {
                __LL_RCU_HSI_En(Instance);
                __LL_RCU_SysClkSrc_Set(Instance, SYSCLK_SRC_RC8M);
            }

            //SYSCLK PLL0 Config
            pll0_cfg.pll_clk_src = sysclk_cfg->pll0clk_src;
            pll0_cfg.pll_in_freq = sysclk_cfg->pll0clk_src_freq;
            pll0_cfg.pll_user_freq = sysclk_cfg->sysclk_freq;
            ret = LL_RCU_Pll0Cfg(Instance, &pll0_cfg);

            //SYCTRL CTRL Reg Unlock because Pll0Cfg function has lock before return
            __LL_RCU_RegWrite_Unlock(Instance);

            //SYSCLK Source Select PLL0DivClk
            if (ret == LL_OK) {
                LOG_I("SYSCLK-[%d] source select PLL0DivClk.\n", sysclk_cfg->sysclk_freq);
                __LL_RCU_SysClkSrc_Set(Instance, SYSCLK_SRC_PLL0DivClk);
            }

            break;

        case SYSCLK_SRC_XOSC:
            LOG_I("SYSCLK-[%d] source select XOSC.\n", sysclk_cfg->sysclk_freq);
            __LL_RCU_HSE_En(Instance);
            __LL_RCU_SysClkSrc_Set(Instance, SYSCLK_SRC_XOSC);
            ret = LL_OK;
            break;

        default:
            LOG_E("SYSCLK Source Select-[%d] Error!\n", sysclk_cfg->sysclk_src);
            ret = LL_ERROR;
            break;
    }

    if (ret == LL_OK) {
        //APB0/APB1/AHB Clock Div Config
        __LL_RCU_APB0ClkDiv_Set(Instance, sysclk_cfg->apb0_clk_div);
        __LL_RCU_APB1ClkDiv_Set(Instance, sysclk_cfg->apb1_clk_div);
        __LL_RCU_AHBClkDiv_Set(Instance, sysclk_cfg->ahb_clk_div);

        //APB0/APB1/AHB0/AHB1 Bus Clock Enable
        __LL_RCU_APB0Clk_En(Instance);
        __LL_RCU_APB1Clk_En(Instance);
        __LL_RCU_AHB0Clk_En(Instance);
        __LL_RCU_AHB1Clk_En(Instance);
    }

    //RCU Register Lock
    __LL_RCU_RegWrite_Lock(Instance);

    return ret;
}

/**
  * @brief  RCU LL ADC Clock Config
  * @param  src ADC Clock Source
  * @param  div ADC Clock Div
  * @return LL Status
  */
LL_StatusETypeDef LL_RCU_ADC_ClkCfg(RCU_ClkSrcETypeDef src, RCU_ClkDivETypeDef div)
{
    //Assert param
    assert_param(div > RCU_CLK_DIV_IVD && div <= RCU_CLK_DIV_16);

    if (div <= RCU_CLK_DIV_IVD || div > RCU_CLK_DIV_16) {
        return LL_INVALID;
    }

    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_ADCClkSrc_Set(RCU, src);
    __LL_RCU_ADCClkDiv_Set(RCU, div);
    __LL_RCU_RegWrite_Lock(RCU);

    return LL_OK;
}

/**
  * @brief  RCU LL HRPWM Clock Config
  * @param  src HRPWM Clock Source
  * @param  div HRPWM Clock Div
  * @return LL Status
  */
LL_StatusETypeDef LL_RCU_HRPWM_ClkCfg(RCU_ClkSrcETypeDef src, RCU_ClkDivETypeDef div)
{
    //Assert param
    assert_param(div > RCU_CLK_DIV_IVD && div <= RCU_CLK_DIV_16);

    if (div <= RCU_CLK_DIV_IVD || div > RCU_CLK_DIV_16) {
        return LL_INVALID;
    }

    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_HRPWMClkSrc_Set(RCU, src);
    __LL_RCU_HRPWMClkDiv_Set(RCU, div);
    __LL_RCU_RegWrite_Lock(RCU);

    return LL_OK;
}

/**
  * @brief  RCU LL CAN Clock Config
  * @param  src CAN Clock Source
  * @param  div CAN Clock Div
  * @return LL Status
  */
LL_StatusETypeDef LL_RCU_CAN_ClkCfg(RCU_ClkSrcETypeDef src, RCU_ClkDivETypeDef div)
{
    //Assert param
    assert_param(div > RCU_CLK_DIV_IVD && div <= RCU_CLK_DIV_16);

    if (div <= RCU_CLK_DIV_IVD || div > RCU_CLK_DIV_16) {
        return LL_INVALID;
    }

    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_CANClkSrc_Set(RCU, src);
    __LL_RCU_CANClkDiv_Set(RCU, div);
    __LL_RCU_RegWrite_Lock(RCU);

    return LL_OK;
}

/**
  * @brief  RCU LL USB Clock Config
  * @param  src USB Clock Source
  * @param  div USB Clock Div
  * @return LL Status
  */
LL_StatusETypeDef LL_RCU_USB_ClkCfg(RCU_ClkSrcETypeDef src, RCU_ClkDivETypeDef div)
{
    //Assert param
    assert_param(div > RCU_CLK_DIV_IVD && div <= RCU_CLK_DIV_16);

    if (div <= RCU_CLK_DIV_IVD || div > RCU_CLK_DIV_16) {
        return LL_INVALID;
    }

    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_USBClkSrc_Set(RCU, src);
    __LL_RCU_USBClkDiv_Set(RCU, div);
    __LL_RCU_RegWrite_Lock(RCU);

    return LL_OK;
}

/**
  * @brief  RCU LL LPTMR Clock Config
  * @param  src LPTMR Clock Source
  * @return LL Status
  */
LL_StatusETypeDef LL_RCU_LPTMR_ClkCfg(RCU_ClkSrcExETypeDef src)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_LPTMRClkSrc_Set(RCU, src);
    __LL_RCU_RegWrite_Lock(RCU);

    return LL_OK;
}

/**
  * @brief  RCU LL SYSCLK freq get
  * @param  None
  * @return SYSCLK freq
  */
uint32_t LL_RCU_SysclkGet(void)
{
    return SystemCoreClock;
}

/**
  * @brief  RCU LL AHB Clock freq get
  * @note   AHB Clock is Div from SYSCLK
  * @param  None
  * @return AHB Clock freq
  */
uint32_t LL_RCU_AHBClkGet(void)
{
    return LL_RCU_SysclkGet() / __LL_RCU_AHBClkDiv_Get(RCU);
}

/**
  * @brief  RCU LL APB0 Clock freq get
  * @note   APB0 Clock is Div from SYSCLK
  * @param  None
  * @return APB0 Clock freq
  */
uint32_t LL_RCU_APB0ClkGet(void)
{
    return LL_RCU_SysclkGet() / __LL_RCU_APB0ClkDiv_Get(RCU);
}

/**
  * @brief  RCU LL APB1 Clock freq get
  * @note   APB1 Clock is Div from SYSCLK
  * @param  None
  * @return APB1 Clock freq
  */
uint32_t LL_RCU_APB1ClkGet(void)
{
    return LL_RCU_SysclkGet() / __LL_RCU_APB1ClkDiv_Get(RCU);
}

/**
  * @}
  */


/** @defgroup RCU_LL_Exported_Functions_Group2 RCU PLL Config Functions
  * @brief    RCU PLL Config Functions
  * @{
  */

/**
  * @brief  RCU LL PLL0 Config
  * @param  Instance Specifies RCU peripheral
  * @param  pll0_cfg PLL0 Config Pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_RCU_Pll0Cfg(RCU_TypeDef *Instance, RCU_PLLUserCfgTypeDef *pll0_cfg)
{
    uint8_t i;
    uint16_t pll_int = 0, pll_frac = 0;
    uint32_t pll_vco_band = 0, pll_vco_gain = 0;
    RCU_ClkDivETypeDef pre_div = RCU_CLK_DIV_IVD;
    volatile uint8_t pll0_adc0_set = 0;

    //Assert param
    assert_param(IS_RCU_ALL_INSTANCE(Instance));
    assert_param(pll0_cfg != NULL);

    if (!IS_RCU_ALL_INSTANCE(Instance) || pll0_cfg == NULL) {
        return LL_INVALID;
    }

    for (i = 0; i < ARRAY_SIZE(rcu_pll_cfg); i++) {
        if (rcu_pll_cfg[i].pll_in_freq  == pll0_cfg->pll_in_freq && rcu_pll_cfg[i].pll_out_freq / 2 == pll0_cfg->pll_user_freq) {
            pre_div = (RCU_ClkDivETypeDef)rcu_pll_cfg[i].pll_pre_div;
            pll_int = rcu_pll_cfg[i].pll_int;
            pll_frac = rcu_pll_cfg[i].pll_frac;
            pll_vco_band = rcu_pll_cfg[i].pll_vco_band;
            pll_vco_gain = rcu_pll_cfg[i].pll_vco_gain;
            break;
        }
    }

    if (i == ARRAY_SIZE(rcu_pll_cfg)) {
        if (pll0_cfg->pll_clk_src == PLLCLK_SRC_HSI) {
            pll0_cfg->pll_in_freq = HSI_VALUE;
        }

        if (pll0_cfg->pll_in_freq) {
            double pll_coef = (double)pll0_cfg->pll_user_freq / pll0_cfg->pll_in_freq;
            pll_int = pll_coef;
            pll_frac = (pll_coef - pll_int) * 65536;

            pre_div = RCU_CLK_DIV_1;
            pll_vco_band = PLL_BAND_1;
            pll_vco_gain = PLL_GVCO_2;
        } else {
            LOG_E("Don't match pll0_in_freq-[%" PRIu32 "] to generate pll0_out_freq-[%" PRIu32 "], please add the config to rcu_pll_cfg array!\n", \
                  pll0_cfg->pll_in_freq, pll0_cfg->pll_user_freq);
            return LL_ERROR;
        }
    }

    //RCU CTRL Register Unlock
    __LL_RCU_RegWrite_Unlock(Instance);

    //ADC0 for PLL0 Band value calibration
    if (pll0_cfg->pll_user_freq == LL_RCU_SYS_CLK_MAX) {
        if (pll0_cfg->pll_clk_src == PLLCLK_SRC_HSE && pll0_cfg->pll_in_freq == 8000000) {
            pll0_adc0_set = 0;
        } else if (pll0_cfg->pll_clk_src == PLLCLK_SRC_HSI) {
            pll0_adc0_set = 0;
        } else {
            LL_RCU_PLL0Cali_ADC0ClkCfgRst(RCU, RCU_CLK_SRC_RC8M, RCU_CLK_DIV_1);
            pll0_adc0_set = 1;
        } 
    } else {
        LL_RCU_PLL0Cali_ADC0ClkCfgRst(RCU, RCU_CLK_SRC_RC8M, RCU_CLK_DIV_1);
        pll0_adc0_set = 1;
    }

    //PLL0 Disable before config
    __LL_RCU_PLL0_Dis(Instance);

    switch (pll0_cfg->pll_clk_src) {
        case PLLCLK_SRC_HSE:
            __LL_RCU_HSE_En(Instance);

            LOG_I("PLL0 CLK Source Select HSE.\n");
            __LL_RCU_PLL0_RefClk_Set(Instance, PLLCLK_SRC_HSE);
            break;

        case PLLCLK_SRC_HSI:
            __LL_RCU_HSI_En(Instance);

            LOG_I("PLL0 CLK Source Select HSI.\n");
            __LL_RCU_PLL0_RefClk_Set(Instance, PLLCLK_SRC_HSI);
            break;

        case PLLCLK_SRC_EXT:
            LOG_I("PLL0 CLK Source Select EXT.\n");
            __LL_RCU_PLL0_RefClk_Set(Instance, PLLCLK_SRC_EXT);
            break;

        default:
            LOG_E("PLL0 CLK Source Select-[%d] Error!\n", pll0_cfg->pll_clk_src);
            return LL_ERROR;
    }

    //PLL0 Pre-Div Config
    if (pre_div == RCU_CLK_DIV_1) {
        __LL_RCU_PLL0_PreDiv_1(Instance);
    } else if (pre_div == RCU_CLK_DIV_2) {
        __LL_RCU_PLL0_PreDiv_2(Instance);
    } else {
        LOG_E("PLL0 Pre-Div Config-[%d] Error, set to default 1 division!\n", pre_div);
        pre_div = RCU_CLK_DIV_1;
        __LL_RCU_PLL0_PreDiv_1(Instance);
    }

    //PLL0 LPF Config
    if (pll0_cfg->pll_in_freq / pre_div > 12000000) {
        __LL_RCU_PLL0_12MHigh_Set(Instance);
    } else {
        __LL_RCU_PLL0_12MLow_Set(Instance);
    }

    //PLL0 integer/fraction and Gain Config
    __LL_RCU_PLL0_DivInt_Set(Instance, pll_int);
    __LL_RCU_PLL0_DivFrac_Set(Instance, pll_frac);
    __LL_RCU_PLL0_GVCO_Set(Instance, pll_vco_gain);

    //PLL0 Band value calibration
    if (pll0_cfg->pll_user_freq == LL_RCU_SYS_CLK_MAX) { //400000000/2
        if (pll0_cfg->pll_clk_src == PLLCLK_SRC_HSE && pll0_cfg->pll_in_freq == 8000000) {
            pll_vco_band = __LL_SYSCTRL_XOSC_PLL0BandValue_Get(SYSCTRL);
        } else if (pll0_cfg->pll_clk_src == PLLCLK_SRC_HSI) {
            pll_vco_band = __LL_SYSCTRL_RC8M_PLL0BandValue_Get(SYSCTRL);
        } else {
            pll_vco_band = LL_RCU_PLL0Cali(RCU);
            __LL_RCU_RegWrite_Unlock(Instance); //SYCTRL CTRL Reg Unlock because PLL0Cali function has lock before return
        }
    } else {
        pll_vco_band = LL_RCU_PLL0Cali(RCU);
        __LL_RCU_RegWrite_Unlock(Instance);     //SYCTRL CTRL Reg Unlock because PLL0Cali function has lock before return
    }

    if (pll0_adc0_set) {
        LL_RCU_PLL0Cali_ADC0ClkRstDis(RCU);
    }

    //PLL0 VCO Band Config and Enable
    __LL_RCU_PLL0_Band_Set(Instance, pll_vco_band);
    __LL_RCU_PLL0_En(Instance);

    //Wait for PLL0 Lock
    LOG_D("Wait for PLL0 lock output\n");

    while (!__LL_RCU_PLL0_IsLocked(Instance))
        ;

    LOG_D("PLL0 lock Success\n");

    //RCU Register Lock
    __LL_RCU_RegWrite_Lock(Instance);

    return LL_OK;
}

/**
  * @}
  */


/** @defgroup RCU_LL_Exported_Functions_Group3 RCU Peripherals Clock and Reset control Functions
  * @brief    RCU Peripherals Clock and Reset control Functions
  * @{
  */

/**
  * @brief  RCU EFLASH Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_EFLASH_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_EFLASHClk_En(RCU);
    __LL_RCU_EFLASHSoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU EFLASH Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_EFLASH_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_EFLASHClk_Dis(RCU);
    __LL_RCU_EFLASHSoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU DMA Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_DMA_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_DMAClk_En(RCU);
    __LL_RCU_DMASoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU DMA Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_DMA_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_DMAClk_Dis(RCU);
    __LL_RCU_DMASoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU CORDIC Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_CORDIC_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_CORDICClk_En(RCU);
    __LL_RCU_CORDICSoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU CORDIC Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_CORDIC_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_CORDICClk_Dis(RCU);
    __LL_RCU_CORDICSoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU TMR0 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_TMR0_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_TMR0Clk_En(RCU);
    __LL_RCU_TMR0SoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU TMR0 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_TMR0_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_TMR0Clk_Dis(RCU);
    __LL_RCU_TMR0SoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU TMR1 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_TMR1_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_TMR1Clk_En(RCU);
    __LL_RCU_TMR1SoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU TMR1 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_TMR1_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_TMR1Clk_Dis(RCU);
    __LL_RCU_TMR1SoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU TMR2 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_TMR2_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_TMR2Clk_En(RCU);
    __LL_RCU_TMR2SoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU TMR2 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_TMR2_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_TMR2Clk_Dis(RCU);
    __LL_RCU_TMR2SoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU TMR3 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_TMR3_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_TMR3Clk_En(RCU);
    __LL_RCU_TMR3SoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU TMR3 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_TMR3_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_TMR3Clk_Dis(RCU);
    __LL_RCU_TMR3SoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU TMR4 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_TMR4_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_TMR4Clk_En(RCU);
    __LL_RCU_TMR4SoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU TMR4 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_TMR4_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_TMR4Clk_Dis(RCU);
    __LL_RCU_TMR4SoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU TMR7 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_TMR7_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_TMR7Clk_En(RCU);
    __LL_RCU_TMR7SoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU TMR7 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_TMR7_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_TMR7Clk_Dis(RCU);
    __LL_RCU_TMR7SoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU TMR8 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_TMR8_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_TMR8Clk_En(RCU);
    __LL_RCU_TMR8SoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU TMR8 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_TMR8_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_TMR8Clk_Dis(RCU);
    __LL_RCU_TMR8SoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU TMR9 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_TMR9_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_TMR9Clk_En(RCU);
    __LL_RCU_TMR9SoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU TMR9 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_TMR9_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_TMR9Clk_Dis(RCU);
    __LL_RCU_TMR9SoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU TMR10 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_TMR10_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_TMR10Clk_En(RCU);
    __LL_RCU_TMR10SoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU TMR10 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_TMR10_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_TMR10Clk_Dis(RCU);
    __LL_RCU_TMR10SoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU TMR6 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_TMR6_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_TMR6Clk_En(RCU);
    __LL_RCU_TMR6FunClk_En(RCU);
    __LL_RCU_TMR6SoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU TMR6 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_TMR6_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_TMR6Clk_Dis(RCU);
    __LL_RCU_TMR6FunClk_Dis(RCU);
    __LL_RCU_TMR6SoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU QEI0 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_QEI0_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_QEI0Clk_En(RCU);
    __LL_RCU_QEI0SoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU QEI0 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_QEI0_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_QEI0Clk_Dis(RCU);
    __LL_RCU_QEI0SoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU QEI1 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_QEI1_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_QEI1Clk_En(RCU);
    __LL_RCU_QEI1SoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU QEI1 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_QEI1_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_QEI1Clk_Dis(RCU);
    __LL_RCU_QEI1SoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU QEI2 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_QEI2_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_QEI2Clk_En(RCU);
    __LL_RCU_QEI2SoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU QEI2 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_QEI2_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_QEI2Clk_Dis(RCU);
    __LL_RCU_QEI2SoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU IIR0 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_IIR0_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_IIR0Clk_En(RCU);
    __LL_RCU_IIR0SoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU IIR0 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_IIR0_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_IIR0Clk_Dis(RCU);
    __LL_RCU_IIR0SoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU IIR1 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_IIR1_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_IIR1Clk_En(RCU);
    __LL_RCU_IIR1SoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU IIR1 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_IIR1_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_IIR1Clk_Dis(RCU);
    __LL_RCU_IIR1SoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU IIR2 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_IIR2_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_IIR2Clk_En(RCU);
    __LL_RCU_IIR2SoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU IIR2 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_IIR2_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_IIR2Clk_Dis(RCU);
    __LL_RCU_IIR2SoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU IIR3 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_IIR3_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_IIR3Clk_En(RCU);
    __LL_RCU_IIR3SoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU IIR3 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_IIR3_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_IIR3Clk_Dis(RCU);
    __LL_RCU_IIR3SoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU IIR4 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_IIR4_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_IIR4Clk_En(RCU);
    __LL_RCU_IIR4SoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU IIR4 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_IIR4_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_IIR4Clk_Dis(RCU);
    __LL_RCU_IIR4SoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU IIR5 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_IIR5_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_IIR5Clk_En(RCU);
    __LL_RCU_IIR5SoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU IIR5 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_IIR5_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_IIR5Clk_Dis(RCU);
    __LL_RCU_IIR5SoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}


/**
  * @brief  RCU GPIOA Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_GPIOA_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_GPIOAClk_En(RCU);
    __LL_RCU_GPIOASoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU GPIOA Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_GPIOA_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_GPIOAClk_Dis(RCU);
    __LL_RCU_GPIOASoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU GPIOB Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_GPIOB_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_GPIOBClk_En(RCU);
    __LL_RCU_GPIOBSoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU GPIOB Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_GPIOB_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_GPIOBClk_Dis(RCU);
    __LL_RCU_GPIOBSoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU GPIOC Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_GPIOC_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_GPIOCClk_En(RCU);
    __LL_RCU_GPIOCSoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU GPIOC Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_GPIOC_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_GPIOCClk_Dis(RCU);
    __LL_RCU_GPIOCSoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU GPIOD Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_GPIOD_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_GPIODClk_En(RCU);
    __LL_RCU_GPIODSoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU GPIOD Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_GPIOD_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_GPIODClk_Dis(RCU);
    __LL_RCU_GPIODSoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU GPIOE Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_GPIOE_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_GPIOEClk_En(RCU);
    __LL_RCU_GPIOESoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU GPIOE Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_GPIOE_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_GPIOEClk_Dis(RCU);
    __LL_RCU_GPIOESoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU GPIOF Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_GPIOF_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_GPIOFClk_En(RCU);
    __LL_RCU_GPIOFSoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU GPIOF Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_GPIOF_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_GPIOFClk_Dis(RCU);
    __LL_RCU_GPIOFSoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU I2C0 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_I2C0_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_I2C0Clk_En(RCU);
    __LL_RCU_I2C0SoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU I2C0 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_I2C0_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_I2C0Clk_Dis(RCU);
    __LL_RCU_I2C0SoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU I2C1 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_I2C1_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_I2C1Clk_En(RCU);
    __LL_RCU_I2C1SoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU I2C1 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_I2C1_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_I2C1Clk_Dis(RCU);
    __LL_RCU_I2C1SoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU I2C2 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_I2C2_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_I2C2Clk_En(RCU);
    __LL_RCU_I2C2SoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU I2C2 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_I2C2_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_I2C2Clk_Dis(RCU);
    __LL_RCU_I2C2SoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU UART0 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_UART0_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_UART0Clk_En(RCU);
    __LL_RCU_UART0SoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU UART0 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_UART0_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_UART0Clk_Dis(RCU);
    __LL_RCU_UART0SoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU UART1 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_UART1_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_UART1Clk_En(RCU);
    __LL_RCU_UART1SoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU UART1 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_UART1_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_UART1Clk_Dis(RCU);
    __LL_RCU_UART1SoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU UART2 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_UART2_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_UART2Clk_En(RCU);
    __LL_RCU_UART2SoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU UART2 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_UART2_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_UART2Clk_Dis(RCU);
    __LL_RCU_UART2SoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU UART3 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_UART3_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_UART3Clk_En(RCU);
    __LL_RCU_UART3SoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU UART3 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_UART3_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_UART3Clk_Dis(RCU);
    __LL_RCU_UART3SoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU UART4 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_UART4_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_UART4Clk_En(RCU);
    __LL_RCU_UART4SoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU UART4 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_UART4_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_UART4Clk_Dis(RCU);
    __LL_RCU_UART4SoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU SPI0 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_SPI0_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_SPI0Clk_En(RCU);
    __LL_RCU_SPI0SoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU SPI0 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_SPI0_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_SPI0Clk_Dis(RCU);
    __LL_RCU_SPI0SoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU SPI1 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_SPI1_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_SPI1Clk_En(RCU);
    __LL_RCU_SPI1SoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU SPI1 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_SPI1_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_SPI1Clk_Dis(RCU);
    __LL_RCU_SPI1SoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU CAN0 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_CAN0_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_CAN0Clk_En(RCU);
    __LL_RCU_CAN0FunClk_En(RCU);
    __LL_RCU_CAN0SoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU CAN0 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_CAN0_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_CAN0Clk_Dis(RCU);
    __LL_RCU_CAN0FunClk_Dis(RCU);
    __LL_RCU_CAN0SoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU CAN1 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_CAN1_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_CAN1Clk_En(RCU);
    __LL_RCU_CAN1FunClk_En(RCU);
    __LL_RCU_CAN1SoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU CAN1 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_CAN1_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_CAN1Clk_Dis(RCU);
    __LL_RCU_CAN1FunClk_Dis(RCU);
    __LL_RCU_CAN1SoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU USB Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_USB_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_USBClk_En(RCU);
    __LL_RCU_USBFunClk_En(RCU);
    __LL_RCU_USBSoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU USB Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_USB_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_USBClk_Dis(RCU);
    __LL_RCU_USBFunClk_Dis(RCU);
    __LL_RCU_USBSoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU XIF Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_XIF_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_XIFClk_En(RCU);
    __LL_RCU_XIFSoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU XIF Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_XIF_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_XIFClk_Dis(RCU);
    __LL_RCU_XIFSoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}


/**
  * @brief  RCU ADC0 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_ADC0_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_ADC0Clk_En(RCU);
    __LL_RCU_ADC0FunClk_En(RCU);
    __LL_RCU_ADCSoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU ADC0 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_ADC0_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_ADC0Clk_Dis(RCU);
    __LL_RCU_ADC0FunClk_Dis(RCU);

    if (!__LL_RCU_IsADCClkEn(RCU)) {
        __LL_RCU_ADCSoftRst_Assert(RCU);
    }

    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU ADC1 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_ADC1_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_ADC1Clk_En(RCU);
    __LL_RCU_ADC1FunClk_En(RCU);
    __LL_RCU_ADCSoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU ADC1 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_ADC1_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_ADC1Clk_Dis(RCU);
    __LL_RCU_ADC1FunClk_Dis(RCU);

    if (!__LL_RCU_IsADCClkEn(RCU)) {
        __LL_RCU_ADCSoftRst_Assert(RCU);
    }

    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU ADC2 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_ADC2_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_ADC2Clk_En(RCU);
    __LL_RCU_ADC2FunClk_En(RCU);
    __LL_RCU_ADCSoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU ADC2 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_ADC2_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_ADC2Clk_Dis(RCU);
    __LL_RCU_ADC2FunClk_Dis(RCU);

    if (!__LL_RCU_IsADCClkEn(RCU)) {
        __LL_RCU_ADCSoftRst_Assert(RCU);
    }

    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU ADC3 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_ADC3_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_ADC3Clk_En(RCU);
    __LL_RCU_ADC3FunClk_En(RCU);
    __LL_RCU_ADCSoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU ADC3 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_ADC3_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_ADC3Clk_Dis(RCU);
    __LL_RCU_ADC3FunClk_Dis(RCU);

    if (!__LL_RCU_IsADCClkEn(RCU)) {
        __LL_RCU_ADCSoftRst_Assert(RCU);
    }

    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU DAC Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_DAC_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_DACClk_En(RCU);
    __LL_RCU_DACSoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU DAC Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_DAC_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_DACClk_Dis(RCU);
    __LL_RCU_DACSoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU CMP Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_CMP_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_CMPClk_En(RCU);
    __LL_RCU_CMPSoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU CMP Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_CMP_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_CMPClk_Dis(RCU);
    __LL_RCU_CMPSoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU HRPWM Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_HRPWM_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_HRPWM0Clk_En(RCU);
    __LL_RCU_HRPWM1Clk_En(RCU);
    __LL_RCU_HRPWM2Clk_En(RCU);
    __LL_RCU_HRPWM3Clk_En(RCU);
    __LL_RCU_HRPWM4Clk_En(RCU);
    __LL_RCU_HRPWM5Clk_En(RCU);
    __LL_RCU_HRPWM6Clk_En(RCU);
    __LL_RCU_HRPWM7Clk_En(RCU);
    __LL_RCU_HRPWM0FunClk_En(RCU);
    __LL_RCU_HRPWM1FunClk_En(RCU);
    __LL_RCU_HRPWM2FunClk_En(RCU);
    __LL_RCU_HRPWM3FunClk_En(RCU);
    __LL_RCU_HRPWM4FunClk_En(RCU);
    __LL_RCU_HRPWM5FunClk_En(RCU);
    __LL_RCU_HRPWM6FunClk_En(RCU);
    __LL_RCU_HRPWM7FunClk_En(RCU);
    __LL_RCU_HRPWMSoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU HRPWM Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_HRPWM_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_HRPWM0Clk_Dis(RCU);
    __LL_RCU_HRPWM1Clk_Dis(RCU);
    __LL_RCU_HRPWM2Clk_Dis(RCU);
    __LL_RCU_HRPWM3Clk_Dis(RCU);
    __LL_RCU_HRPWM4Clk_Dis(RCU);
    __LL_RCU_HRPWM5Clk_Dis(RCU);
    __LL_RCU_HRPWM6Clk_Dis(RCU);
    __LL_RCU_HRPWM7Clk_Dis(RCU);
    __LL_RCU_HRPWM0FunClk_Dis(RCU);
    __LL_RCU_HRPWM1FunClk_Dis(RCU);
    __LL_RCU_HRPWM2FunClk_Dis(RCU);
    __LL_RCU_HRPWM3FunClk_Dis(RCU);
    __LL_RCU_HRPWM4FunClk_Dis(RCU);
    __LL_RCU_HRPWM5FunClk_Dis(RCU);
    __LL_RCU_HRPWM6FunClk_Dis(RCU);
    __LL_RCU_HRPWM7FunClk_Dis(RCU);
    __LL_RCU_HRPWMSoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU HRPWM0 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_HRPWM0_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_HRPWM0Clk_En(RCU);
    __LL_RCU_HRPWM0FunClk_En(RCU);
    __LL_RCU_HRPWMSoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU HRPWM0 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_HRPWM0_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_HRPWM0Clk_Dis(RCU);
    __LL_RCU_HRPWM0FunClk_Dis(RCU);

    if (!__LL_RCU_IsHRPWMClkEn(RCU)) {
        __LL_RCU_HRPWMSoftRst_Assert(RCU);
    }

    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU HRPWM1 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_HRPWM1_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_HRPWM1Clk_En(RCU);
    __LL_RCU_HRPWM1FunClk_En(RCU);
    __LL_RCU_HRPWMSoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU HRPWM1 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_HRPWM1_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_HRPWM1Clk_Dis(RCU);
    __LL_RCU_HRPWM1FunClk_Dis(RCU);

    if (!__LL_RCU_IsHRPWMClkEn(RCU)) {
        __LL_RCU_HRPWMSoftRst_Assert(RCU);
    }

    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU HRPWM2 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_HRPWM2_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_HRPWM2Clk_En(RCU);
    __LL_RCU_HRPWM2FunClk_En(RCU);
    __LL_RCU_HRPWMSoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU HRPWM2 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_HRPWM2_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_HRPWM2Clk_Dis(RCU);
    __LL_RCU_HRPWM2FunClk_Dis(RCU);

    if (!__LL_RCU_IsHRPWMClkEn(RCU)) {
        __LL_RCU_HRPWMSoftRst_Assert(RCU);
    }

    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU HRPWM3 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_HRPWM3_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_HRPWM3Clk_En(RCU);
    __LL_RCU_HRPWM3FunClk_En(RCU);
    __LL_RCU_HRPWMSoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU HRPWM3 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_HRPWM3_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_HRPWM3Clk_Dis(RCU);
    __LL_RCU_HRPWM3FunClk_Dis(RCU);

    if (!__LL_RCU_IsHRPWMClkEn(RCU)) {
        __LL_RCU_HRPWMSoftRst_Assert(RCU);
    }

    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU HRPWM4 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_HRPWM4_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_HRPWM4Clk_En(RCU);
    __LL_RCU_HRPWM4FunClk_En(RCU);
    __LL_RCU_HRPWMSoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU HRPWM4 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_HRPWM4_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_HRPWM4Clk_Dis(RCU);
    __LL_RCU_HRPWM4FunClk_Dis(RCU);

    if (!__LL_RCU_IsHRPWMClkEn(RCU)) {
        __LL_RCU_HRPWMSoftRst_Assert(RCU);
    }

    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU HRPWM5 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_HRPWM5_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_HRPWM5Clk_En(RCU);
    __LL_RCU_HRPWM5FunClk_En(RCU);
    __LL_RCU_HRPWMSoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU HRPWM5 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_HRPWM5_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_HRPWM5Clk_Dis(RCU);
    __LL_RCU_HRPWM5FunClk_Dis(RCU);

    if (!__LL_RCU_IsHRPWMClkEn(RCU)) {
        __LL_RCU_HRPWMSoftRst_Assert(RCU);
    }

    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU HRPWM6 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_HRPWM6_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_HRPWM6Clk_En(RCU);
    __LL_RCU_HRPWM6FunClk_En(RCU);
    __LL_RCU_HRPWMSoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU HRPWM6 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_HRPWM6_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_HRPWM6Clk_Dis(RCU);
    __LL_RCU_HRPWM6FunClk_Dis(RCU);

    if (!__LL_RCU_IsHRPWMClkEn(RCU)) {
        __LL_RCU_HRPWMSoftRst_Assert(RCU);
    }

    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU HRPWM7 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_HRPWM7_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_HRPWM7Clk_En(RCU);
    __LL_RCU_HRPWM7FunClk_En(RCU);
    __LL_RCU_HRPWMSoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU HRPWM7 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_HRPWM7_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_HRPWM7Clk_Dis(RCU);
    __LL_RCU_HRPWM7FunClk_Dis(RCU);

    if (!__LL_RCU_IsHRPWMClkEn(RCU)) {
        __LL_RCU_HRPWMSoftRst_Assert(RCU);
    }

    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU PDM0 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_PDM0_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_PDM0Clk_En(RCU);
    __LL_RCU_PDM0SoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU PDM0 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_PDM0_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_PDM0Clk_Dis(RCU);
    __LL_RCU_PDM0SoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU PDM1 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_PDM1_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_PDM1Clk_En(RCU);
    __LL_RCU_PDM1SoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU PDM1 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_PDM1_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_PDM1Clk_Dis(RCU);
    __LL_RCU_PDM1SoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU PDM2 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_PDM2_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_PDM2Clk_En(RCU);
    __LL_RCU_PDM2SoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU PDM2 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_PDM2_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_PDM2Clk_Dis(RCU);
    __LL_RCU_PDM2SoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU PDM3 Bus Clock Enable and Reset Release
  * @param  None
  * @return None
  */
void LL_RCU_PDM3_ClkEnRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_PDM3Clk_En(RCU);
    __LL_RCU_PDM3SoftRst_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU PDM3 Bus Clock Disable and Reset Assert
  * @param  None
  * @return None
  */
void LL_RCU_PDM3_ClkDisRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_PDM3Clk_Dis(RCU);
    __LL_RCU_PDM3SoftRst_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}


/**
  * @brief  RCU LL all peripheral reset assert
  * @note   All peripheral include system bus(AHB0/AHB1/APB0/APB1)
  * @param  None
  * @return None
  */
void LL_RCU_AllPeriphRstAssert(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_APB0SoftRstAll_Assert(RCU);
    __LL_RCU_APB1SoftRstAll_Assert(RCU);
    __LL_RCU_AHB0SoftRstAll_Assert(RCU);
    __LL_RCU_AHB1SoftRstAll_Assert(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @brief  RCU LL all peripheral reset release
  * @note   All peripheral include system bus(AHB0/AHB1/APB0/APB1)
  * @param  None
  * @return None
  */
void LL_RCU_AllPeriphRstRelease(void)
{
    __LL_RCU_RegWrite_Unlock(RCU);
    __LL_RCU_APB0SoftRstAll_Release(RCU);
    __LL_RCU_APB1SoftRstAll_Release(RCU);
    __LL_RCU_AHB0SoftRstAll_Release(RCU);
    __LL_RCU_AHB1SoftRstAll_Release(RCU);
    __LL_RCU_RegWrite_Lock(RCU);
}

/**
  * @}
  */

/**
  * @}
  */


/* Private Functions ---------------------------------------------------------*/
/** @addtogroup RCU_LL_Private_Functions
  * @{
  */

/**
  * @brief  ADC0 Clock Config and Soft Reset Release for PLL Calibrate 
  * @note   Unlock the RCU register before use
  * @param  Instance Specifies RCU peripheral
  * @param  src ADC Clock Source
  * @param  div ADC Clock Div
  * @return None
  */
static void LL_RCU_PLL0Cali_ADC0ClkCfgRst(RCU_TypeDef *Instance, RCU_ClkSrcETypeDef src, RCU_ClkDivETypeDef div)
{
    //Clock Disable
    __LL_RCU_ADC0Clk_Dis(Instance);
    __LL_RCU_ADC0FunClk_Dis(Instance);
    
    //Clock Config
    __LL_RCU_ADCClkSrc_Set(Instance, src);
    __LL_RCU_ADCClkDiv_Set(Instance, div);
    
    //Clock Enable
    __LL_RCU_ADC0Clk_En(Instance);
    __LL_RCU_ADC0FunClk_En(Instance);
    
    //ADC Reset
    __LL_RCU_ADCSoftRst_Assert(Instance);
    __LL_RCU_ADCSoftRst_Release(Instance);
}

/**
  * @brief  ADC0 Clock Disable and Soft Reset Release for PLL Calibrate 
  * @note   Unlock the RCU register before use
  * @param  Instance Specifies RCU peripheral
  * @return None
  */
static void LL_RCU_PLL0Cali_ADC0ClkRstDis(RCU_TypeDef *Instance)
{
    //ADC Reset
    __LL_RCU_ADCSoftRst_Assert(Instance);
    __LL_RCU_ADCSoftRst_Release(Instance);

    //Clock Disable
    __LL_RCU_ADC0Clk_Dis(Instance);
    __LL_RCU_ADC0FunClk_Dis(Instance);
}

/**
  * @brief  RCU LL PLL0 calibrate
  * @param  Instance Specifies RCU peripheral
  * @return Fitband
  */
static uint8_t LL_RCU_PLL0Cali(RCU_TypeDef *Instance)
{
    uint32_t CPOUT_Vout[4];
    uint8_t  FitBand = 0;
    uint32_t atcr = READ_REG(SYSCTRL->ATCR);
    uint32_t sysatr = READ_REG(SYSCTRL->SYSATR);
    uint8_t  pll0_status = READ_BIT(RCU->PLL0CR, RCU_PLL0CR_EN_Msk);
    int32_t  Trim_Value;
    uint32_t cr_store = 0;

    //Assert param
    assert_param(IS_RCU_ALL_INSTANCE(Instance));

    if (!IS_RCU_ALL_INSTANCE(Instance)) {
        return 0;
    }

    //RCU/SYSCTRL Reg Unlock
    __LL_RCU_RegWrite_Unlock(Instance);
    __LL_SYSCTRL_SysRegWrite_Unlock(SYSCTRL);
    __LL_SYSCTRL_SpRegWrite_Unlock(SYSCTRL);

    //Vref Buf output 2.5V
    __LL_SYSCTRL_VREFBUFOutputVol_Set(SYSCTRL, SYSCTRL_VREFBUF_VOL_2V5);
    __LL_SYSCTRL_VREFBUF_En(SYSCTRL);

    //ADC BUF select VRIP2
    __LL_SYSCTRL_ADCBuf_En(SYSCTRL);
    __LL_SYSCTRL_ADCBufSrc_Sel(SYSCTRL, 0x3);

    //Enable DWT
    cr_store = CoreDebug->DEMCR & CoreDebug_DEMCR_TRCENA_Msk;	
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;	

    //delay 1.2ms
    DWT->CYCCNT = (uint32_t)0U;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

    while (DWT->CYCCNT < (uint32_t)(((float)HSI_VALUE / 1000000) * 1200));

    //ADC0 Config
    WRITE_REG(ADC0->CFGR0,  0x00808321);
    WRITE_REG(ADC0->CFGR1,  0x0000002B);
    WRITE_REG(ADC0->SIGSEL, 0);
    WRITE_REG(ADC0->SMPR2,  0x20);
    WRITE_REG(ADC0->SQR0,   0x00000011);

    ADC0->CR |= BIT(0);

    while (((ADC0->ISR & BIT(8)) >> 8U) != 1);

    ADC0->CR |= BIT(2);

    //ADC REG Start Conversion
    SET_BIT(ADC0->DISR, BIT(17));

    while (((ADC0->DISR & BIT(17)) >> 17U) != 1);

    Trim_Value = ADC0->DR;
    SET_BIT(ADC0->DISR, BIT(17));

    //ADC BUF select PLL0 CPOUT
    __LL_SYSCTRL_ADCBufSrc_Sel(SYSCTRL, 0x12);

    //PLL0 VCODET Enable
    SET_BIT(Instance->PLL0CR, BIT(17));

    for (uint8_t pll_band_index = 0; pll_band_index < 4; pll_band_index++) {
        __LL_RCU_PLL0_Dis(Instance);
        __LL_RCU_PLL0_Band_Set(Instance, pll_band_index);
        __LL_RCU_PLL0_En(Instance);

        //delay 1.5ms
        DWT->CYCCNT = (uint32_t)0U;
        DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

        while (DWT->CYCCNT < (uint32_t)(((float)HSI_VALUE / 1000000) * 1500));

        CPOUT_Vout[pll_band_index] = abs((int)ADC0->DR - Trim_Value / 2);
        SET_BIT(ADC0->DISR, BIT(17));
    }

    //Restore PLL0 status
    MODIFY_REG(RCU->PLL0CR, RCU_PLL0CR_EN_Msk, pll0_status);

    //PLL0 VCODET Disable
    CLEAR_BIT(Instance->PLL0CR, BIT(17));

    //Disable DWT
    DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk;
    CoreDebug->DEMCR |= cr_store;

    for (uint8_t pll_band_index = 0; pll_band_index < 4; pll_band_index++) {
        if (CPOUT_Vout[pll_band_index] < CPOUT_Vout[FitBand]) {
            FitBand = pll_band_index;
        }
    }

    //Stop ADC
    SET_BIT(ADC0->CR, 0x01UL);

    //Restore SYSATR Reg
    WRITE_REG(SYSCTRL->SYSATR, sysatr);

    //Restore ATCR Reg
    WRITE_REG(SYSCTRL->ATCR, atcr);

    //RCU/SYSCTRL Reg Lock
    __LL_RCU_RegWrite_Lock(Instance);
    __LL_SYSCTRL_SysRegWrite_Lock(SYSCTRL);
    __LL_SYSCTRL_SpRegWrite_Lock(SYSCTRL);

    return FitBand;
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

