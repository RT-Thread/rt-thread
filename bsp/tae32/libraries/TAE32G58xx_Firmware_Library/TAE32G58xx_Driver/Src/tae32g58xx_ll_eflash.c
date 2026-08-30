/**
  ******************************************************************************
  * @file    tae32g58xx_ll_eflash.c
  * @author  MCD Application Team
  * @brief   EFLASH LL module driver
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


#define DBG_TAG             "EFLASH LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae_dbg.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @defgroup EFLASH_LL EFLASH LL
  * @brief    EFLASH LL module driver
  * @{
  */

#ifdef LL_EFLASH_MODULE_ENABLED

/* Private Constants ---------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/* Private Types -------------------------------------------------------------*/
/* Private Variables ---------------------------------------------------------*/
/* Private Function Prototypes -----------------------------------------------*/
/** @defgroup EFLASH_LL_Private_Functions EFLASH LL Private Functions
  * @brief    EFLASH LL Private Functions
  * @{
  */
__STATIC_INLINE bool EFLASH_LastOptSta_Get(EFLASH_TypeDef *Instance, EFLASH_OptETypeDef last_opt);
LL_StatusETypeDef EFLASH_EraseComm(EFLASH_TypeDef *Instance, EFLASH_EraseModeETypeDef erase_mode);
/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup EFLASH_LL_Exported_Functions EFLASH LL Exported Functions
  * @brief    EFLASH LL Exported Functions
  * @{
  */

/** @defgroup EFLASH_LL_Exported_Functions_Group1 EFLASH RW Protection / Optiod Data Config Functions
  * @brief    EFLASH RW Protection / Optiod Data Config Functions
  * @{
  */

/**
  * @brief Read Protect Level Config
  * @param Instance Specifies EFLASH peripheral
  * @param level Read Protect Level
  * @return LL Status
  */
LL_StatusETypeDef LL_EFLASH_ReadProtLvlCfg(EFLASH_TypeDef *Instance, EFLASH_ReadProtLvlETypeDef level)
{
    LL_StatusETypeDef ret;

    //Assert param
    assert_param(IS_EFLASH_ALL_INSTANCE(Instance));

    if (!IS_EFLASH_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //Wait for EFLASH Idle
    ret = LL_EFLASH_WaitForBusyState(Instance, EFLASH_DEFAULT_TIMEOUT);

    if (ret == LL_OK) {
        //Unlock Read/Write Protect Config access
        if (LL_EFLASH_RWProtOptDat_Unlock(Instance) != LL_OK) {
            return LL_FAILED;
        }

        //Set Read Protect Level
        __LL_EFLASH_ReadProtReg_Set(Instance, level);

        //Wait for Operation Complete
        ret = LL_EFLASH_WaitForLastOptCplt(Instance, EFLASH_OPT_RW_PROT, EFLASH_DEFAULT_TIMEOUT);

        //Lanch to reflesh Read Protect config take effect
        __LL_EFLASH_Launch_En(Instance);

        //Lock Read/Write Protect Config access
        LL_EFLASH_RWProtOptDat_Lock(Instance);
    }

    return ret;
}

/**
  * @brief Write Protect Config
  * @param Instance Specifies EFLASH peripheral
  * @param area Write Protect Area
  * @param write_prot_en Write Protect enable
  * @return LL Status
  */
LL_StatusETypeDef LL_EFLASH_WriteProtCfg(EFLASH_TypeDef *Instance, EFLASH_WriteProtAreaETypeDef area, bool write_prot_en)
{
    LL_StatusETypeDef ret;
    uint32_t area_32 = area;
    bool dobule_bank_map1_flag;

    //Assert param
    assert_param(IS_EFLASH_ALL_INSTANCE(Instance));

    if (!IS_EFLASH_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //Check Bank mode and Bank Map Status
    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) {
        dobule_bank_map1_flag = false;
    } else {
        dobule_bank_map1_flag = (bool)((EFLASH_BankModeETypeDef)__LL_EFLASH_BankMode_Get(Instance) == EFLASH_BANK_MODE_DOUBLE &&
                                    (EFLASH_BankAddrMapETypeDef)__LL_EFLASH_BankAddrMap_Get(Instance) == EFLASH_BANK_ADDR_MAP_BANK1);        
    }


    if (dobule_bank_map1_flag) {
        area_32 = (((uint32_t)area & 0xffffUL) << 16) | (((uint32_t)area & 0xffff0000UL) >> 16);
    }

    //Wait for EFLASH Idle
    ret = LL_EFLASH_WaitForBusyState(Instance, EFLASH_DEFAULT_TIMEOUT);

    if (ret == LL_OK) {
        //Unlock Read/Write Protect Config access
        if (LL_EFLASH_RWProtOptDat_Unlock(Instance) != LL_OK) {
            return LL_FAILED;
        }

        ret = LL_EFLASH_WaitForLastOptCplt(Instance, EFLASH_OPT_RW_PROT, EFLASH_DEFAULT_TIMEOUT);
        if (ret != LL_OK) {
            if (LL_EFLASH_RWProtOptDat_Lock(Instance) != LL_OK) {
                return LL_FAILED;
            } else {
                return ret;
            }
        }

        //Write Protect Config
        (void)__LL_EFLASH_WriteProtArea_Read(Instance);
        LL_FUNC_ALTER(write_prot_en, __LL_EFLASH_WriteProtArea_En(Instance, area_32), __LL_EFLASH_WriteProtArea_Dis(Instance, area_32));

        //Wait for Operation Complete
        ret = LL_EFLASH_WaitForLastOptCplt(Instance, EFLASH_OPT_RW_PROT, EFLASH_DEFAULT_TIMEOUT * 3);

        //Lanch to reflesh Write Protect config take effect
        __LL_EFLASH_Launch_En(Instance);

        //Lock Read/Write Protect Config access
        LL_EFLASH_RWProtOptDat_Lock(Instance);
    }

    return ret;
}

/**
  * @brief User Option Data Config
  * @param Instance Specifies EFLASH peripheral
  * @param cfg User Option Data Config pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_EFLASH_OptDatUserCfg(EFLASH_TypeDef *Instance, EFLASH_UserCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_EFLASH_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);

    if (!IS_EFLASH_ALL_INSTANCE(Instance) || cfg == NULL) {
        return LL_INVALID;
    }

    //Wait for EFLASH Idle
    if (LL_EFLASH_WaitForBusyState(Instance, EFLASH_DEFAULT_TIMEOUT) != LL_OK) {
        LOG_E("Wait for Busy state error before operation!\n");
        return LL_ERROR;
    }

    //Unlock Option Data Config access
    if (LL_EFLASH_RWProtOptDat_Unlock(Instance) != LL_OK) {
        return LL_FAILED;
    }

    if (LL_EFLASH_WaitForLastOptCplt(Instance, EFLASH_OPT_OPT_DAT, EFLASH_DEFAULT_TIMEOUT) != LL_OK) {
        goto OPT_DAT_TIMEOUT;
    }

    //Option Data User Config
    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) {
        (void)__LL_EFLASH_OPDR_Read(Instance);
        __LL_EFLASH_BootSel_Set(Instance, cfg->boot_sel);
        while (__LL_EFLASH_BootSel_Read(Instance) != (cfg->boot_sel &  0x7UL));
        if (LL_EFLASH_WaitForLastOptCplt(Instance, EFLASH_OPT_OPT_DAT, EFLASH_DEFAULT_TIMEOUT) != LL_OK) {
            goto OPT_DAT_TIMEOUT;
        }

        (void)__LL_EFLASH_OPDR_Read(Instance);
        __LL_EFLASH_BankAddrMap(Instance, cfg->bank_map);
        while (__LL_EFLASH_BankAddrMap_Get(Instance) != (cfg->bank_map & 0xfUL));
        if (LL_EFLASH_WaitForLastOptCplt(Instance, EFLASH_OPT_OPT_DAT, EFLASH_DEFAULT_TIMEOUT) != LL_OK) {
            goto OPT_DAT_TIMEOUT;
        }

        (void)__LL_EFLASH_OPDR_Read(Instance);
        __LL_EFLASH_BankMode_Cfg(Instance, cfg->bank_mode);
        while (__LL_EFLASH_BankMode_Get(Instance) != (cfg->bank_mode & 0xfUL));
        if (LL_EFLASH_WaitForLastOptCplt(Instance, EFLASH_OPT_OPT_DAT, EFLASH_DEFAULT_TIMEOUT) != LL_OK) {
            goto OPT_DAT_TIMEOUT;
        }

        (void)__LL_EFLASH_OPDR_Read(Instance);
        __LL_EFLASH_BORVolLimit_Cfg(Instance, cfg->bor_vol_lmt);
        while (__LL_EFLASH_BORVolLimit_Read(Instance) != (cfg->bor_vol_lmt  & 0x3UL));
        if (LL_EFLASH_WaitForLastOptCplt(Instance, EFLASH_OPT_OPT_DAT, EFLASH_DEFAULT_TIMEOUT) != LL_OK) {
            goto OPT_DAT_TIMEOUT;
        }

        (void)__LL_EFLASH_OPDR_Read(Instance);
        LL_FUNC_ALTER(cfg->iwdg_en, __LL_EFLASH_IWDG_En(Instance), __LL_EFLASH_IWDG_Dis(Instance));
        while (__LL_EFLASH_Is_IWDGEn(Instance) != cfg->iwdg_en);
        if (LL_EFLASH_WaitForLastOptCplt(Instance, EFLASH_OPT_OPT_DAT, EFLASH_DEFAULT_TIMEOUT) != LL_OK) {
            goto OPT_DAT_TIMEOUT;
        }

        (void)__LL_EFLASH_OPDR_Read(Instance);
        LL_FUNC_ALTER(cfg->wwdg_en, __LL_EFLASH_WWDG_En(Instance), __LL_EFLASH_WWDG_Dis(Instance));
        while (__LL_EFLASH_Is_WWDGEn(Instance) != cfg->wwdg_en);
        if (LL_EFLASH_WaitForLastOptCplt(Instance, EFLASH_OPT_OPT_DAT, EFLASH_DEFAULT_TIMEOUT) != LL_OK) {
            goto OPT_DAT_TIMEOUT;
        }

        (void)__LL_EFLASH_OPDR_Read(Instance);
        LL_FUNC_ALTER(cfg->boot_lock_en, __LL_EFLASH_Boot_Lock(Instance), __LL_EFLASH_Boot_Unlock(Instance));
        while (__LL_EFLASH_Is_BootLock(Instance) != cfg->boot_lock_en);
        if (LL_EFLASH_WaitForLastOptCplt(Instance, EFLASH_OPT_OPT_DAT, EFLASH_DEFAULT_TIMEOUT) != LL_OK) {
            goto OPT_DAT_TIMEOUT;
        }

        (void)__LL_EFLASH_OPDR_Read(Instance);
        LL_FUNC_ALTER(cfg->pwron_ecc_bypass_en, __LL_EFLASH_PowerOnECCBypass_En(Instance), __LL_EFLASH_PowerOnECCBypass_Dis(Instance));
        while (__LL_EFLASH_Is_PowerOnECCBypassEn(Instance) != cfg->pwron_ecc_bypass_en);
        if (LL_EFLASH_WaitForLastOptCplt(Instance, EFLASH_OPT_OPT_DAT, EFLASH_DEFAULT_TIMEOUT) != LL_OK) {
            goto OPT_DAT_TIMEOUT;
        }
    } else {
        __LL_EFLASH_BootSel_Set(Instance, cfg->boot_sel);
        __LL_EFLASH_BankAddrMap(Instance, cfg->bank_map);
        __LL_EFLASH_BankMode_Cfg(Instance, cfg->bank_mode);
        __LL_EFLASH_BORVolLimit_Cfg(Instance, cfg->bor_vol_lmt);

        LL_FUNC_ALTER(cfg->iwdg_en, __LL_EFLASH_IWDG_En(Instance), __LL_EFLASH_IWDG_Dis(Instance));
        LL_FUNC_ALTER(cfg->wwdg_en, __LL_EFLASH_WWDG_En(Instance), __LL_EFLASH_WWDG_Dis(Instance));
        LL_FUNC_ALTER(cfg->boot_lock_en, __LL_EFLASH_Boot_Lock(Instance), __LL_EFLASH_Boot_Unlock(Instance));
        LL_FUNC_ALTER(cfg->pwron_ecc_bypass_en, __LL_EFLASH_PowerOnECCBypass_En(Instance), __LL_EFLASH_PowerOnECCBypass_Dis(Instance));
    }

OPT_DAT_TIMEOUT:
    //Wait for Option Data Operation Complete
    if (LL_EFLASH_WaitForBusyState(Instance, EFLASH_DEFAULT_TIMEOUT) != LL_OK) {
        LOG_E("Wait for Busy state error before Lock!\n");
    }

    //Lock Option Data Config access
    LL_EFLASH_RWProtOptDat_Lock(Instance);

    //Wait for Option Data Operation Complete
    if (LL_EFLASH_WaitForLastOptCplt(Instance, EFLASH_OPT_OPT_DAT, EFLASH_DEFAULT_TIMEOUT) != LL_OK) {
        LOG_E("Option Data user config timeout!!!\n");
        return LL_TIMEOUT;
    }

    return LL_OK;
}

/**
  * @brief EFLASH bank mapping config
  * @param Instance Specifies EFLASH peripheral
  * @param bank_map Bank mapping config
  * @return LL Status
  */
LL_StatusETypeDef LL_EFLASH_BankMapCfg(EFLASH_TypeDef *Instance, EFLASH_BankAddrMapETypeDef bank_map)
{
    //Assert param
    assert_param(IS_EFLASH_ALL_INSTANCE(Instance));

    if (!IS_EFLASH_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //Wait for EFLASH Idle
    if (LL_EFLASH_WaitForBusyState(Instance, EFLASH_DEFAULT_TIMEOUT) != LL_OK) {
        LOG_E("Wait for Busy state error before operation!\n");
        return LL_ERROR;
    }

    //Unlock Option Data Config access
    if (LL_EFLASH_RWProtOptDat_Unlock(Instance) != LL_OK) {
        return LL_FAILED;
    }

    //EFLASH bank mapping config
    (void)__LL_EFLASH_OPDR_Read(Instance);
    __LL_EFLASH_BankAddrMap(Instance, bank_map);
    while (__LL_EFLASH_BankAddrMap_Get(Instance) != (bank_map & 0xfUL));

    //Wait for EFLASH Idle
    if (LL_EFLASH_WaitForBusyState(Instance, EFLASH_DEFAULT_TIMEOUT) != LL_OK) {
        LOG_E("Wait for Busy state error before operation!\n");
    }

    //Lock Option Data Config access
    LL_EFLASH_RWProtOptDat_Lock(Instance);

    //Wait for Option Data Operation Complete
    if (LL_EFLASH_WaitForLastOptCplt(Instance, EFLASH_OPT_OPT_DAT, EFLASH_DEFAULT_TIMEOUT) != LL_OK) {
        LOG_E("Bank mapping config timeout!!!\n");
        return LL_TIMEOUT;
    }

    return LL_OK;
}

/**
  * @brief EFLASH bank mode config
  * @param Instance Specifies EFLASH peripheral
  * @param bank_mode Bank mode config
  * @return LL Status
  */
LL_StatusETypeDef LL_EFLASH_BankModeCfg(EFLASH_TypeDef *Instance, EFLASH_BankModeETypeDef bank_mode)
{
    //Assert param
    assert_param(IS_EFLASH_ALL_INSTANCE(Instance));

    if (!IS_EFLASH_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //Wait for EFLASH Idle
    if (LL_EFLASH_WaitForBusyState(Instance, EFLASH_DEFAULT_TIMEOUT) != LL_OK) {
        LOG_E("Wait for Busy state error before operation!\n");
        return LL_ERROR;
    }

    //Unlock Option Data Config access
    if (LL_EFLASH_RWProtOptDat_Unlock(Instance) != LL_OK) {
        return LL_FAILED;
    }

    //EFLASH bank mode config
    (void)__LL_EFLASH_OPDR_Read(Instance);
    __LL_EFLASH_BankMode_Cfg(Instance, bank_mode);
    while (__LL_EFLASH_BankMode_Get(Instance) != (bank_mode & 0xfUL));

    //Wait for EFLASH Idle
    if (LL_EFLASH_WaitForBusyState(Instance, EFLASH_DEFAULT_TIMEOUT) != LL_OK) {
        LOG_E("Wait for Busy state error before operation!\n");
    }

    //Lock Option Data Config access
    LL_EFLASH_RWProtOptDat_Lock(Instance);

    //Wait for Option Data Operation Complete
    if (LL_EFLASH_WaitForLastOptCplt(Instance, EFLASH_OPT_OPT_DAT, EFLASH_DEFAULT_TIMEOUT) != LL_OK) {
        LOG_E("Bank mode config timeout!!!\n");
        return LL_TIMEOUT;
    }

    return LL_OK;
}

/**
  * @brief EFLASH boot selection config
  * @param Instance Specifies EFLASH peripheral
  * @param boot_sel Boot selection config
  * @return LL Status
  */
LL_StatusETypeDef LL_EFLASH_BootSelCfg(EFLASH_TypeDef *Instance, EFLASH_BootSelETypeDef boot_sel)
{
    //Assert param
    assert_param(IS_EFLASH_ALL_INSTANCE(Instance));

    if (!IS_EFLASH_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //Wait for EFLASH Idle
    if (LL_EFLASH_WaitForBusyState(Instance, EFLASH_DEFAULT_TIMEOUT) != LL_OK) {
        LOG_E("Wait for Busy state error before operation!\n");
        return LL_ERROR;
    }

    //Unlock Option Data Config access
    if (LL_EFLASH_RWProtOptDat_Unlock(Instance) != LL_OK) {
        return LL_FAILED;
    }

    //EFLASH boot selection config
    (void)__LL_EFLASH_OPDR_Read(Instance);
    __LL_EFLASH_BootSel_Set(Instance, boot_sel);
    while (__LL_EFLASH_BootSel_Read(Instance) != (boot_sel &  0x7UL));

    //Wait for EFLASH Idle
    if (LL_EFLASH_WaitForBusyState(Instance, EFLASH_DEFAULT_TIMEOUT) != LL_OK) {
        LOG_E("Wait for Busy state error before operation!\n");
    }

    //Lock Option Data Config access
    LL_EFLASH_RWProtOptDat_Lock(Instance);

    //Wait for Option Data Operation Complete
    if (LL_EFLASH_WaitForLastOptCplt(Instance, EFLASH_OPT_OPT_DAT, EFLASH_DEFAULT_TIMEOUT) != LL_OK) {
        LOG_E("Boot selection config timeout!!!\n");
        return LL_TIMEOUT;
    }

    return LL_OK;
}

/**
  * @brief EFLASH BOR Voltage Limit config
  * @param Instance Specifies EFLASH peripheral
  * @param bor_vol_lmt BOR Voltage Limit config
  * @return LL Status
  */
LL_StatusETypeDef LL_EFLASH_BORVolLimitCfg(EFLASH_TypeDef *Instance, EFLASH_BORVolLimitETypeDef bor_vol_lmt)
{
    //Assert param
    assert_param(IS_EFLASH_ALL_INSTANCE(Instance));

    if (!IS_EFLASH_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //Wait for EFLASH Idle
    if (LL_EFLASH_WaitForBusyState(Instance, EFLASH_DEFAULT_TIMEOUT) != LL_OK) {
        LOG_E("Wait for Busy state error before operation!\n");
        return LL_ERROR;
    }

    //Unlock Option Data Config access
    if (LL_EFLASH_RWProtOptDat_Unlock(Instance) != LL_OK) {
        return LL_FAILED;
    }

    //EFLASH BOR Voltage Limit config
    (void)__LL_EFLASH_OPDR_Read(Instance);
    __LL_EFLASH_BORVolLimit_Cfg(Instance, bor_vol_lmt);
    while (__LL_EFLASH_BORVolLimit_Read(Instance) != (bor_vol_lmt  & 0x3UL));

    //Wait for EFLASH Idle
    if (LL_EFLASH_WaitForBusyState(Instance, EFLASH_DEFAULT_TIMEOUT) != LL_OK) {
        LOG_E("Wait for Busy state error before operation!\n");
    }

    //Lock Option Data Config access
    LL_EFLASH_RWProtOptDat_Lock(Instance);

    //Wait for Option Data Operation Complete
    if (LL_EFLASH_WaitForLastOptCplt(Instance, EFLASH_OPT_OPT_DAT, EFLASH_DEFAULT_TIMEOUT) != LL_OK) {
        LOG_E("BOR voltage limit config timeout!!!\n");
        return LL_TIMEOUT;
    }

    return LL_OK;
}

/**
  * @brief EFLASH User Option config
  * @param Instance Specifies EFLASH peripheral
  * @param user_opt User Option operation type
  * @param opt_param User Option operation param
  *        This parameter can be one of the following values:
  *        1) user_opt = EFLASH_USER_OPT_BOOT_SEL,        opt_param @ref EFLASH_BootSelETypeDef
  *        2) user_opt = EFLASH_USER_OPT_BOR_VOL_LMT_CFG, opt_param @ref EFLASH_BORVolLimitETypeDef
  *        3) user_opt = EFLASH_USER_OPT_BANK_MODE_CFG,   opt_param @ref EFLASH_BankModeETypeDef
  *        4) user_opt = EFLASH_USER_OPT_BANK_MAP_CFG,    opt_param @ref EFLASH_BankAddrMapETypeDef
  *        5) user_opt = Others(except above value),      opt_param @ref bool, which means relative operation Enable/Disable
  * @return LL Status
  */
LL_StatusETypeDef LL_EFLASH_UserOptCfg(EFLASH_TypeDef *Instance, EFLASH_UserOptETypeDef user_opt, uint32_t opt_param)
{
    //Assert param
    assert_param(IS_EFLASH_ALL_INSTANCE(Instance));

    if (!IS_EFLASH_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //Wait for EFLASH Idle
    if (LL_EFLASH_WaitForBusyState(Instance, EFLASH_DEFAULT_TIMEOUT) != LL_OK) {
        LOG_E("Wait for Busy state error before operation!\n");
        return LL_ERROR;
    }

    //Unlock Option Data Config access
    if (LL_EFLASH_RWProtOptDat_Unlock(Instance) != LL_OK) {
        return LL_FAILED;
    }

    if (LL_EFLASH_WaitForLastOptCplt(Instance, EFLASH_OPT_OPT_DAT, EFLASH_DEFAULT_TIMEOUT) != LL_OK) {
        goto invalid;
    }

    switch (user_opt) {
        case EFLASH_USER_OPT_BOOT_LOCK_CFG:
            (void)__LL_EFLASH_OPDR_Read(Instance);
            LL_FUNC_ALTER(opt_param & 0x1UL, __LL_EFLASH_Boot_Lock(Instance), __LL_EFLASH_Boot_Unlock(Instance));
            while (__LL_EFLASH_Is_BootLock(Instance) != (opt_param & 0x1UL));
            break;

        case EFLASH_USER_OPT_BOOT_SEL:
            assert_param(opt_param <= EFLASH_BOOT_SEL_7);

            if (opt_param > EFLASH_BOOT_SEL_7) {
                goto invalid;
            }

            (void)__LL_EFLASH_OPDR_Read(Instance);
            __LL_EFLASH_BootSel_Set(Instance, opt_param);
            while (__LL_EFLASH_BootSel_Read(Instance) != (opt_param &  0x7UL));
            break;

        case EFLASH_USER_OPT_BOR_VOL_LMT_CFG:
            assert_param(opt_param <= EFLASH_BOR_VOL_LIMIT_2V85);

            if (opt_param > EFLASH_BOR_VOL_LIMIT_2V85) {
                goto invalid;
            }

            (void)__LL_EFLASH_OPDR_Read(Instance);
            __LL_EFLASH_BORVolLimit_Cfg(Instance, opt_param);
            while (__LL_EFLASH_BORVolLimit_Read(Instance) != (opt_param  & 0x3UL));
            break;

        case EFLASH_USER_OPT_PWRON_ECC_BYPASS:
            (void)__LL_EFLASH_OPDR_Read(Instance);
            LL_FUNC_ALTER(opt_param & 0x1UL, __LL_EFLASH_PowerOnECCBypass_En(Instance), __LL_EFLASH_PowerOnECCBypass_Dis(Instance));
            while (__LL_EFLASH_Is_PowerOnECCBypassEn(Instance) != (opt_param & 0x1UL));
            break;

        case EFLASH_USER_OPT_IWDG_EN:
            (void)__LL_EFLASH_OPDR_Read(Instance);
            LL_FUNC_ALTER(opt_param & 0x1UL, __LL_EFLASH_IWDG_En(Instance), __LL_EFLASH_IWDG_Dis(Instance));
            while (__LL_EFLASH_Is_IWDGEn(Instance) != (opt_param & 0x1UL));
            break;

        case EFLASH_USER_OPT_WWDG_EN:
            (void)__LL_EFLASH_OPDR_Read(Instance);
            LL_FUNC_ALTER(opt_param & 0x1UL, __LL_EFLASH_WWDG_En(Instance), __LL_EFLASH_WWDG_Dis(Instance));
            while (__LL_EFLASH_Is_WWDGEn(Instance) != (opt_param & 0x1UL));
            break;

        case EFLASH_USER_OPT_BANK_MODE_CFG:
            assert_param(opt_param <= EFLASH_BANK_MODE_SINGLE);

            if (opt_param > EFLASH_BANK_MODE_SINGLE) {
                goto invalid;
            }

            (void)__LL_EFLASH_OPDR_Read(Instance);
            __LL_EFLASH_BankMode_Cfg(Instance, opt_param);
            while (__LL_EFLASH_BankMode_Get(Instance) != (opt_param & 0xfUL));
            break;

        case EFLASH_USER_OPT_BANK_MAP_CFG:
            assert_param(opt_param <= EFLASH_BANK_ADDR_MAP_BANK0);

            if (opt_param > EFLASH_BANK_ADDR_MAP_BANK0) {
                goto invalid;
            }

            (void)__LL_EFLASH_OPDR_Read(Instance);
            __LL_EFLASH_BankAddrMap(Instance, opt_param);
            while (__LL_EFLASH_BankAddrMap_Get(Instance) != (opt_param & 0xfUL));
            break;

        default:
            LOG_E("Invalid user option operation code [%d]!\n", user_opt);
            goto invalid;
    }

    //Wait for EFLASH Idle
    if (LL_EFLASH_WaitForBusyState(Instance, EFLASH_DEFAULT_TIMEOUT) != LL_OK) {
        LOG_E("Wait for Busy state error before operation!\n");
    }

    //Lock Option Data Config access
    if (LL_EFLASH_RWProtOptDat_Lock(Instance) != LL_OK) {
        return LL_FAILED;
    }

    //Wait for Option Data Operation Complete
    if (LL_EFLASH_WaitForLastOptCplt(Instance, EFLASH_OPT_OPT_DAT, EFLASH_DEFAULT_TIMEOUT) != LL_OK) {
        LOG_E("User Option config timeout!!!\n");
        return LL_TIMEOUT;
    }

    return LL_OK;

invalid:
    //Wait for EFLASH Idle
    if (LL_EFLASH_WaitForBusyState(Instance, EFLASH_DEFAULT_TIMEOUT) != LL_OK) {
        LOG_E("Wait for Busy state error before Lock!\n");
        return LL_TIMEOUT;
    }

    //Lock Option Data Config access
    LL_EFLASH_RWProtOptDat_Lock(Instance);

    return LL_INVALID;
}

/**
  * @}
  */


/** @defgroup EFLASH_LL_Exported_Functions_Group2 EFLASH State Functions
  * @brief    EFLASH State Functions
  * @{
  */

/**
  * @brief  EFLASH Wait for busy state
  * @param  Instance Specifies EFLASH peripheral
  * @param  timeout timeout duration
  * @return LL Status
  */
LL_StatusETypeDef LL_EFLASH_WaitForBusyState(EFLASH_TypeDef *Instance, uint32_t timeout)
{
    uint32_t tickstart = LL_GetTick();
    volatile bool oper_done = false;

    //Assert param
    assert_param(IS_EFLASH_ALL_INSTANCE(Instance));

    if (!IS_EFLASH_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) {
        //Wait for All Operation Done
        do {
            oper_done = __LL_EFLASH_IsProgramOptDone(Instance)      & __LL_EFLASH_IsEraseOptDone(Instance)  &
                        __LL_EFLASH_IsStdbyOptDone(Instance)        & __LL_EFLASH_IsWakeupOptDone(Instance) &
                        __LL_EFLASH_IsRwProtOptDatOptDone(Instance) & __LL_EFLASH_IsIdle(Instance);
            if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {
                return LL_TIMEOUT;
            }
        } while (oper_done == false);

        //Check if any errors occurred
        if (__LL_EFLASH_IsAnyError(Instance) || __LL_EFLASH_IsAnyExError(Instance)) {
            __LL_EFLASH_AllErr_Clr(Instance);
            __LL_EFLASH_AllExErr_Clr(Instance);
            return LL_ERROR;
        }

    } else {
        //Wait for All Operation Done
        while (!__LL_EFLASH_IsProgramOptDone(Instance) || !__LL_EFLASH_IsEraseOptDone(Instance) ||
            !__LL_EFLASH_IsStdbyOptDone(Instance) || !__LL_EFLASH_IsWakeupOptDone(Instance) ||
            !__LL_EFLASH_IsRwProtOptDatOptDone(Instance)) {
            if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {
                return LL_TIMEOUT;
            }
        }

        //Check if any errors occurred
        if (__LL_EFLASH_IsAnyError(Instance)) {
            __LL_EFLASH_AllErr_Clr(Instance);
            return LL_ERROR;
        }        
    }

    return LL_OK;
}

/**
  * @brief  EFLASH Wait for last operation complete
  * @param  Instance Specifies EFLASH peripheral
  * @param  last_opt last operation
  * @param  timeout timeout duration
  * @return LL Status
  */
LL_StatusETypeDef LL_EFLASH_WaitForLastOptCplt(EFLASH_TypeDef *Instance, EFLASH_OptETypeDef last_opt, uint32_t timeout)
{
    uint32_t tickstart = LL_GetTick();

    //Assert param
    assert_param(IS_EFLASH_ALL_INSTANCE(Instance));

    if (!IS_EFLASH_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //Wait for Done flag, check any error occurred first, because operation may not start and error occured
    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) {
        do {
            //Check if any errors occurred
            if (__LL_EFLASH_IsAnyError(Instance) || __LL_EFLASH_IsAnyExError(Instance)) {
                __LL_EFLASH_AllErr_Clr(Instance);
                __LL_EFLASH_AllExErr_Clr(Instance);
                return LL_ERROR;
            } 

            if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {
                return LL_TIMEOUT;
            }
        } while (!EFLASH_LastOptSta_Get(Instance, last_opt));        
    } else {
        do {
            //Check if any errors occurred
            if (__LL_EFLASH_IsAnyError(Instance)) {
                __LL_EFLASH_AllErr_Clr(Instance);
                return LL_ERROR;
            }   

            if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {
                return LL_TIMEOUT;
            }
        } while (!EFLASH_LastOptSta_Get(Instance, last_opt));        
    }

    return LL_OK;
}

/**
  * @}
  */


/** @defgroup EFLASH_LL_Exported_Functions_Group3 EFLASH Information Functions
  * @brief    EFLASH Information Functions
  * @{
  */

/**
  * @brief  EFLASH Chip Size get
  * @param  Instance Specifies EFLASH peripheral
  * @return EFLASH Chip Size in Byte unit
  */
uint32_t LL_EFLASH_ChipSize_Get(EFLASH_TypeDef *Instance)
{
    uint32_t sizeKByte;

    //Assert param
    assert_param(IS_EFLASH_ALL_INSTANCE(Instance));

    if (!IS_EFLASH_ALL_INSTANCE(Instance)) {
        return 0;
    }

    sizeKByte = __LL_SYSCTRL_EFlashSize_Get(SYSCTRL);

    if (sizeKByte == 0xffffUL) {
        return 256 * 1024;  //No size information, default 256K
    }

    return sizeKByte * 1024;
}

/**
  * @brief  EFLASH Sector Size get
  * @param  Instance Specifies EFLASH peripheral
  * @return EFLASH Sector Size in Byte unit
  */
uint32_t LL_EFLASH_SectorSize_Get(EFLASH_TypeDef *Instance)
{
    uint32_t chip_size;

    //Assert param
    assert_param(IS_EFLASH_ALL_INSTANCE(Instance));

    if (!IS_EFLASH_ALL_INSTANCE(Instance)) {
        return 0;
    }

    chip_size = LL_EFLASH_ChipSize_Get(Instance);

    if (chip_size == 128 * 1024) {
        return EFLASH_SECTOR_SIZE_128;
    } else if (chip_size == 256 * 1024) {
        if ((EFLASH_BankModeETypeDef)__LL_EFLASH_BankMode_Get(Instance) == EFLASH_BANK_MODE_DOUBLE) {
            return EFLASH_SECTOR_SIZE_256_D;
        } else {
            return EFLASH_SECTOR_SIZE_256_S;
        }
    }

    return 0;
}

/**
  * @brief  EFLASH Sector Numbers get
  * @param  Instance Specifies EFLASH peripheral
  * @return EFLASH Sector Numbers
  */
uint32_t LL_EFLASH_SectorNums_Get(EFLASH_TypeDef *Instance)
{
    uint32_t chip_size;

    //Assert param
    assert_param(IS_EFLASH_ALL_INSTANCE(Instance));

    if (!IS_EFLASH_ALL_INSTANCE(Instance)) {
        return 0;
    }

    chip_size = LL_EFLASH_ChipSize_Get(Instance);

    if (chip_size == 128 * 1024) {
        return EFLASH_SECTOR_NUM_128;
    } else if (chip_size == 256 * 1024) {
        if ((EFLASH_BankModeETypeDef)__LL_EFLASH_BankMode_Get(Instance) == EFLASH_BANK_MODE_DOUBLE) {
            return EFLASH_SECTOR_NUM_256_D;
        } else {
            return EFLASH_SECTOR_NUM_256_S;
        }
    }

    return 0;
}

/**
  * @}
  */


/** @defgroup EFLASH_LL_Exported_Functions_Group4 EFLASH Operation Functions
  * @brief    EFLASH Operation Functions
  * @{
  */

/**
  * @brief  Program an amount of data at a specified address in CPU blocking mode
  * @param  Instance Specifies EFLASH peripheral
  * @param  addr program start relative address which must align to 8 bytes
  * @param  buf  buffer pointer to be programmed
  * @param  size program data size in byte which must be a multiple of 8
  * @return Success program size in byte unit
  */
uint32_t LL_EFLASH_Program(EFLASH_TypeDef *Instance, uint32_t addr, uint8_t *buf, uint32_t size)
{
    bool dobule_bank_map1_flag;
    addr &= EFLASH_PROG_ADDRESS_MASK;
    uint32_t i, *buf_32, cnt = 0, chip_size = LL_EFLASH_ChipSize_Get(Instance);

    //Assert param
    assert_param(IS_EFLASH_ALL_INSTANCE(Instance));
    assert_param(__LL_EFLASH_IsProgAddrOrSizeAlign8Bytes(addr));
    assert_param(__LL_EFLASH_IsProgAddrOrSizeAlign8Bytes(size));
    assert_param(buf != NULL);
    assert_param(addr < chip_size);
    assert_param((addr + size) <= chip_size);

    if (!IS_EFLASH_ALL_INSTANCE(Instance) || !__LL_EFLASH_IsProgAddrOrSizeAlign8Bytes(addr) ||
        !__LL_EFLASH_IsProgAddrOrSizeAlign8Bytes(size) || buf == NULL || addr >= chip_size ||
        (addr + size) > chip_size) {
        return 0;
    }

    //Wait for EFLASH Idle
    if (LL_EFLASH_WaitForBusyState(Instance, EFLASH_DEFAULT_TIMEOUT) != LL_OK) {
        LOG_E("Wait for Busy state error before operation!\n");
        return 0;
    }

    //Check Bank mode and Bank Map Status
    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) {
        dobule_bank_map1_flag = false;
    } else {
        dobule_bank_map1_flag = (bool)((EFLASH_BankModeETypeDef)__LL_EFLASH_BankMode_Get(Instance) == EFLASH_BANK_MODE_DOUBLE &&
                                    (EFLASH_BankAddrMapETypeDef)__LL_EFLASH_BankAddrMap_Get(Instance) == EFLASH_BANK_ADDR_MAP_BANK1);        
    }


    buf_32 = (uint32_t *)buf;

    //Unlock Program/Erase access
    LL_EFLASH_ProgErase_Unlock(Instance);

    for (i = 0; i < size / EFLASH_PROG_SINGLE_SIZE; i++) {
        //Program data Config
        __LL_EFLASH_ProgData0_Set(Instance, *buf_32++);
        __LL_EFLASH_ProgData1_Set(Instance, *buf_32++);

        //Program address Config
        __LL_EFLASH_ProgAddr_Set(Instance, dobule_bank_map1_flag ? addr ^ BIT(17) : addr);

        //Program Start
        __LL_EFLASH_ProgramStart(Instance);

        //Wait for Programming Complete
        if (LL_EFLASH_WaitForLastOptCplt(Instance, EFLASH_OPT_PROG, EFLASH_DEFAULT_TIMEOUT) != LL_OK) {
            LOG_E("Program error at address 0x%08" PRIx32 "!!!\n", addr);
            goto exit;
        }

        addr += EFLASH_PROG_SINGLE_SIZE;
        cnt  += EFLASH_PROG_SINGLE_SIZE;
    }

exit:
    //Lock Program/Erase access
    LL_EFLASH_ProgErase_Lock(Instance);

    return cnt;
}

/**
  * @brief  Erase Multi sectors in CPU blocking mode
  * @param  Instance Specifies EFLASH peripheral
  * @param  sector_start The sector number to be erased start
  * @param  num Erase sector numbers
  * @return Success Erase sector numbers
  */
uint32_t LL_EFLASH_EraseMultiSector(EFLASH_TypeDef *Instance, uint32_t sector_start, uint32_t num)
{
    uint32_t i, sec_nums = LL_EFLASH_SectorNums_Get(Instance);
    bool dobule_bank_map1_flag;

    //Assert param
    assert_param(IS_EFLASH_ALL_INSTANCE(Instance));
    assert_param(sector_start < sec_nums);
    assert_param((sector_start + num - 1) < sec_nums);

    if (!IS_EFLASH_ALL_INSTANCE(Instance) || sector_start >= sec_nums || (sector_start + num - 1) >= sec_nums) {
        return 0;
    }

    //Wait for EFLASH Idle
    if (LL_EFLASH_WaitForBusyState(Instance, EFLASH_DEFAULT_TIMEOUT) != LL_OK) {
        LOG_E("Wait for Busy state error before operation!\n");
        return 0;
    }

    //Check Bank mode and Bank Map Status
    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) {
        dobule_bank_map1_flag = false;
    } else {
        dobule_bank_map1_flag = (bool)((EFLASH_BankModeETypeDef)__LL_EFLASH_BankMode_Get(Instance) == EFLASH_BANK_MODE_DOUBLE &&
                                    (EFLASH_BankAddrMapETypeDef)__LL_EFLASH_BankAddrMap_Get(Instance) == EFLASH_BANK_ADDR_MAP_BANK1);
    }


    //Set to Sector Erase mode
    __LL_EFLASH_EraseMode_Set(Instance, EFLASH_ERASE_MODE_SECTOR);

    //Unlock Program/Erase access
    LL_EFLASH_ProgErase_Unlock(Instance);

    for (i = 0; i < num; i++) {
        //Sector number Config
        __LL_EFLASH_EraseSectorNum_Set(Instance, dobule_bank_map1_flag ? (sector_start + i) ^ BIT(5) : (sector_start + i));

        //Erase Start
        __LL_EFLASH_EraseStart(Instance);

        //Wait for Sector Erase Complete
        if (LL_EFLASH_WaitForLastOptCplt(Instance, EFLASH_OPT_ERASE, EFLASH_DEFAULT_TIMEOUT) != LL_OK) {
            LOG_E("Sector Erase error at Sector number %" PRIu32 "!!!\n", sector_start + i);
            goto exit;
        }
    }

exit:
    //Lock Program/Erase access
    LL_EFLASH_ProgErase_Lock(Instance);

    return i;
}

/**
  * @brief  Erase single sector in CPU blocking mode
  * @param  Instance Specifies EFLASH peripheral
  * @param  sector_num The sector number to be erased [0,255]
  * @return LL Status
  */
LL_StatusETypeDef LL_EFLASH_EraseSector(EFLASH_TypeDef *Instance, uint32_t sector_num)
{
    uint32_t sec_nums = LL_EFLASH_SectorNums_Get(Instance);

    //Assert param
    assert_param(IS_EFLASH_ALL_INSTANCE(Instance));
    assert_param(sector_num < sec_nums);

    if (!IS_EFLASH_ALL_INSTANCE(Instance) || sector_num >= sec_nums) {
        return LL_INVALID;
    }

    //Wait for EFLASH Idle
    if (LL_EFLASH_WaitForBusyState(Instance, EFLASH_DEFAULT_TIMEOUT) != LL_OK) {
        LOG_E("Wait for Busy state error before operation!\n");
        return LL_ERROR;
    }

    if (LL_EFLASH_EraseMultiSector(Instance, sector_num, 1) == 1) {
        return LL_OK;
    } else {
        return LL_ERROR;
    }
}

/**
  * @brief  Erase Chip in CPU blocking mode
  * @param  Instance Specifies EFLASH peripheral
  * @return LL Status
  */
LL_StatusETypeDef LL_EFLASH_EraseChip(EFLASH_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_EFLASH_ALL_INSTANCE(Instance));

    if (!IS_EFLASH_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    return EFLASH_EraseComm(Instance, EFLASH_ERASE_MODE_CHIP);
}

/**
  * @brief  Erase Bank0 in CPU blocking mode
  * @param  Instance Specifies EFLASH peripheral
  * @return LL Status
  */
LL_StatusETypeDef LL_EFLASH_EraseBank0(EFLASH_TypeDef *Instance)
{
    bool dobule_bank_map1_flag;

    //Assert param
    assert_param(IS_EFLASH_ALL_INSTANCE(Instance));

    if (!IS_EFLASH_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //Check Bank mode and Bank Map Status
    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) {
        dobule_bank_map1_flag = false;
    } else {
        dobule_bank_map1_flag = (bool)((EFLASH_BankModeETypeDef)__LL_EFLASH_BankMode_Get(Instance) == EFLASH_BANK_MODE_DOUBLE &&
                                    (EFLASH_BankAddrMapETypeDef)__LL_EFLASH_BankAddrMap_Get(Instance) == EFLASH_BANK_ADDR_MAP_BANK1);
    }

    return EFLASH_EraseComm(Instance, dobule_bank_map1_flag ? EFLASH_ERASE_MODE_BANK1 : EFLASH_ERASE_MODE_BANK0);
}

/**
  * @brief  Erase Bank1 in CPU blocking mode
  * @param  Instance Specifies EFLASH peripheral
  * @return LL Status
  */
LL_StatusETypeDef LL_EFLASH_EraseBank1(EFLASH_TypeDef *Instance)
{
    bool dobule_bank_map1_flag;

    //Assert param
    assert_param(IS_EFLASH_ALL_INSTANCE(Instance));

    if (!IS_EFLASH_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //Check Bank mode and Bank Map Status
    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) {
        dobule_bank_map1_flag = false;
    } else {
        dobule_bank_map1_flag = (bool)((EFLASH_BankModeETypeDef)__LL_EFLASH_BankMode_Get(Instance) == EFLASH_BANK_MODE_DOUBLE &&
                                    (EFLASH_BankAddrMapETypeDef)__LL_EFLASH_BankAddrMap_Get(Instance) == EFLASH_BANK_ADDR_MAP_BANK1);        
    }

    return EFLASH_EraseComm(Instance, dobule_bank_map1_flag ? EFLASH_ERASE_MODE_BANK0 : EFLASH_ERASE_MODE_BANK1);
}

/**
  * @brief  Verify an amount of data at a specified address
  * @param  Instance Specifies EFLASH peripheral
  * @param  addr verify start relative address
  * @param  buf  buffer pointer to be verified
  * @param  size verify data size in byte
  * @return Success verify size in byte unit
  */
uint32_t LL_EFLASH_Verify(EFLASH_TypeDef *Instance, uint32_t addr, uint8_t *buf, uint32_t size)
{
    addr &= EFLASH_PROG_ADDRESS_MASK;
    uint32_t cnt, cmp_addr, chip_size = LL_EFLASH_ChipSize_Get(Instance);

    //Assert param
    assert_param(IS_EFLASH_ALL_INSTANCE(Instance));
    assert_param(buf != NULL);
    assert_param(addr < chip_size);
    assert_param((addr + size) <= chip_size);

    if (!IS_EFLASH_ALL_INSTANCE(Instance) || buf == NULL || addr >= chip_size || (addr + size) > chip_size) {
        return 0;
    }

    //Verify loop
    for (cnt = 0, cmp_addr = addr + EFLASH_MEM_BASE; cnt < size; cnt++, cmp_addr++) {
        if (*((uint8_t *)cmp_addr) != buf[cnt]) {
            break;
        }
    }

    return cnt;
}

/**
  * @}
  */


/** @defgroup EFLASH_LL_Exported_Functions_Lock EFLASH Lock and Unlock Functions
  * @brief    EFLASH Lock and Unlock Functions
  * @{
  */

/**
  * @brief  Unlock EFLASH Program/Erase access
  * @param  Instance Specifies EFLASH peripheral
  * @return LL Status
  */
LL_StatusETypeDef LL_EFLASH_ProgErase_Unlock(EFLASH_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_EFLASH_ALL_INSTANCE(Instance));

    if (!IS_EFLASH_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    if (__LL_EFLASH_IsProgEraseLock(Instance)) {
        //Authorize the FLASH Program/Erase access
        __LL_EFLASH_Key_Set(Instance, EFLASH_PROG_ERASE_KEY1);
        __LL_EFLASH_Key_Set(Instance, EFLASH_PROG_ERASE_KEY2);

        //Verify EFLASH is unlocked
        if (__LL_EFLASH_IsProgEraseLock(Instance)) {
            return LL_ERROR;
        }
    }

    return LL_OK;
}

/**
  * @brief  Lock EFLASH Program/Erase access
  * @param  Instance Specifies EFLASH peripheral
  * @return LL Status
  */
LL_StatusETypeDef LL_EFLASH_ProgErase_Lock(EFLASH_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_EFLASH_ALL_INSTANCE(Instance));

    if (!IS_EFLASH_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    if (!__LL_EFLASH_IsProgEraseLock(Instance)) {
        //Set the LOCK Bit to lock the EFLASH Program/Erase access
        __LL_EFLASH_ProgErase_Lock(Instance);

        //Verify EFLASH is Locked
        if (!__LL_EFLASH_IsProgEraseLock(Instance)) {
            return LL_ERROR;
        }
    }

    return LL_OK;
}

/**
  * @brief  Unlock EFLASH Read/Write Protection / Option Data Operation access
  * @param  Instance Specifies EFLASH peripheral
  * @return LL Status
  */
LL_StatusETypeDef LL_EFLASH_RWProtOptDat_Unlock(EFLASH_TypeDef *Instance)
{
    uint32_t tickstart = LL_GetTick();

    //Assert param
    assert_param(IS_EFLASH_ALL_INSTANCE(Instance));

    if (!IS_EFLASH_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    if (__LL_EFLASH_IsRwProtOptDatLock(Instance)) {
        //Authorize the EFLASH Read/Write Protect access
        __LL_EFLASH_Key_Set(Instance, EFLASH_RW_PROTECT_OPT_DAT_KEY1);
        __LL_EFLASH_Key_Set(Instance, EFLASH_RW_PROTECT_OPT_DAT_KEY2);

        //Verify EFLASH is unlocked
        while (__LL_EFLASH_IsRwProtOptDatLock(Instance)) {
            if ((LL_GetTick() - tickstart) > EFLASH_DEFAULT_TIMEOUT) {
                return LL_ERROR;
            }
        }
    }

    return LL_OK;
}

/**
  * @brief  Lock EFLASH Read/Write Protection / Option Data Operation access
  * @param  Instance Specifies EFLASH peripheral
  * @return LL Status
  */
LL_StatusETypeDef LL_EFLASH_RWProtOptDat_Lock(EFLASH_TypeDef *Instance)
{
    uint32_t tickstart = LL_GetTick();

    //Assert param
    assert_param(IS_EFLASH_ALL_INSTANCE(Instance));

    if (!IS_EFLASH_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    if (!__LL_EFLASH_IsRwProtOptDatLock(Instance)) {
        //Set the LOCK Bit to lock the EFLASH Read/Write Protect access
        __LL_EFLASH_RwProtOptDat_Lock(Instance);

        //Verify EFLASH is Locked
        while (!__LL_EFLASH_IsRwProtOptDatLock(Instance)) {
            if ((LL_GetTick() - tickstart) > EFLASH_DEFAULT_TIMEOUT) {
                return LL_ERROR;
            }
        }
    }

    return LL_OK;
}

/**
  * @brief  Launch Read/Write Protection Feature reloading
  * @param  Instance Specifies EFLASH peripheral
  * @return None
  */
void LL_FLASH_ReadWriteProt_Launch(EFLASH_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_EFLASH_ALL_INSTANCE(Instance));

    if (!IS_EFLASH_ALL_INSTANCE(Instance)) {
        return;
    }

    __LL_EFLASH_Launch_En(Instance);
}

/**
  * @}
  */


/** @defgroup EFLASH_LL_Exported_Functions_Interrupt EFLASH Interrupt Handler and Callback
  * @brief    EFLASH Interrupt Handler and Callback
  * @{
  */

/**
  * @brief  LL EFLASH IRQ Handler
  * @param  Instance Specifies EFLASH peripheral
  * @retval None
  */
void LL_EFLASH_IRQHandler(EFLASH_TypeDef *Instance)
{
    uint32_t int_pending;

    //Assert param
    assert_param(IS_EFLASH_ALL_INSTANCE(Instance));

    if (!IS_EFLASH_ALL_INSTANCE(Instance)) {
        return;
    }

    //Check Error Interrupt Enable or not
    if (!__LL_EFLASH_IsErrIntEn(Instance)) {
        return;
    }

    //All Interrupt Pending Get
    int_pending = __LL_EFLASH_AllIntPnd_Get(Instance);


    //Operation Error Interrupt Handler
    if (int_pending & FLASH_SR_OES_Msk) {
        //Clear Interrupt Pending
        __LL_EFLASH_OptErr_Clr(Instance);

        //Callback
        LL_EFLASH_OptErrCallback(Instance);
    }

    //Write Protect Error Interrupt Handler
    if (int_pending & FLASH_SR_WPS_Msk) {
        //Clear Interrupt Pending
        __LL_EFLASH_WriteProtErr_Clr(Instance);

        //Callback
        LL_EFLASH_WriteProtErrCallback(Instance);
    }

    //Illegal Operation Error Interrupt Handler
    if (int_pending & FLASH_SR_IOS_Msk) {
        //Clear Interrupt Pending
        __LL_EFLASH_IllegalOptErr_Clr(Instance);

        //Callback
        LL_EFLASH_IllegalOptErrCallback(Instance);
    }

    //Single Bit Error Interrupt Handler
    if (int_pending & FLASH_SR_SBC_Msk) {
        //Clear Interrupt Pending
        __LL_EFLASH_SingleBitErrPnd_Clr(Instance);

        //Callback
        LL_EFLASH_SingleBitErrCallback(Instance);
    }



}

/**
  * @brief  EFLASH Operation Error Interrupt Callback
  * @param  Instance Specifies EFLASH peripheral
  * @return None
  */
__WEAK void LL_EFLASH_OptErrCallback(EFLASH_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_EFLASH_OptErrCallback could be implemented in the user file
     */
}

/**
  * @brief  EFLASH Write Protect Error Interrupt Callback
  * @param  Instance Specifies EFLASH peripheral
  * @return None
  */
__WEAK void LL_EFLASH_WriteProtErrCallback(EFLASH_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_EFLASH_WriteProtErrCallback could be implemented in the user file
     */
}

/**
  * @brief  EFLASH Illegal Operation Error Interrupt Callback
  * @param  Instance Specifies EFLASH peripheral
  * @return None
  */
__WEAK void LL_EFLASH_IllegalOptErrCallback(EFLASH_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_EFLASH_IllegalOptErrCallback could be implemented in the user file
     */
}

/**
  * @brief  EFLASH Single Bit Error Interrupt Callback
  * @param  Instance Specifies EFLASH peripheral
  * @return None
  */
__WEAK void LL_EFLASH_SingleBitErrCallback(EFLASH_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_EFLASH_SingleBitErrCallback could be implemented in the user file
     */
}

/**
  * @}
  */

/**
  * @}
  */


/* Private Functions ---------------------------------------------------------*/
/** @addtogroup EFLASH_LL_Private_Functions
  * @{
  */

/**
  * @brief  EFLASH last operation status get
  * @param  Instance Specifies EFLASH peripheral
  * @param  last_opt last operation
  * @retval false last operation isn't Done
  * @retval true  last operation is Done
  */
__STATIC_INLINE bool EFLASH_LastOptSta_Get(EFLASH_TypeDef *Instance, EFLASH_OptETypeDef last_opt)
{
    //Assert param
    assert_param(IS_EFLASH_ALL_INSTANCE(Instance));

    if (!IS_EFLASH_ALL_INSTANCE(Instance)) {
        return true;
    }

    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) {
        if(!__LL_EFLASH_IsIdle(Instance)) {
            return false;
        }
    }

    switch (last_opt) {
        case EFLASH_OPT_PROG:
            return __LL_EFLASH_IsProgramOptDone(Instance);

        case EFLASH_OPT_ERASE:
            return __LL_EFLASH_IsEraseOptDone(Instance);

        case EFLASH_OPT_STDBY:
            return __LL_EFLASH_IsStdbyOptDone(Instance);

        case EFLASH_OPT_WAKEUP:
            return __LL_EFLASH_IsWakeupOptDone(Instance);

        case EFLASH_OPT_RW_PROT:
        case EFLASH_OPT_OPT_DAT:
            return __LL_EFLASH_IsRwProtOptDatOptDone(Instance);                

        default:
            return true;
    }
}

/**
  * @brief  Erase Common (Bank/Chip) in CPU blocking mode
  * @note   This function only support Bank/Chip erase mode
  * @param  Instance Specifies EFLASH peripheral
  * @param  erase_mode Erase mode except EFLASH_ERASE_MODE_SECTOR
  * @return LL Status
  */
LL_StatusETypeDef EFLASH_EraseComm(EFLASH_TypeDef *Instance, EFLASH_EraseModeETypeDef erase_mode)
{
    //Assert param
    assert_param(IS_EFLASH_ALL_INSTANCE(Instance));

    if (!IS_EFLASH_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //Check Erase Mode
    if (erase_mode == EFLASH_ERASE_MODE_SECTOR) {
        LOG_E("%s interface don't support SECTOR erase mode!\n", __FUNCTION__);
        return LL_ERROR;
    }

    //Wait for EFLASH Idle
    if (LL_EFLASH_WaitForBusyState(Instance, EFLASH_DEFAULT_TIMEOUT) != LL_OK) {
        LOG_E("Wait for Busy state error before operation!\n");
        return LL_ERROR;
    }

    //Erase mode Set
    __LL_EFLASH_EraseMode_Set(Instance, erase_mode);

    //Unlock Program/Erase access
    LL_EFLASH_ProgErase_Unlock(Instance);

    //Erase Start
    __LL_EFLASH_EraseStart(Instance);

    //Wait for Erase Complete
    if (LL_EFLASH_WaitForLastOptCplt(Instance, EFLASH_OPT_ERASE, EFLASH_DEFAULT_TIMEOUT) != LL_OK) {
        //Lock Program/Erase access
        LL_EFLASH_ProgErase_Lock(Instance);

        LOG_E("Erase [mode-%d] Error!!!\n", erase_mode);
        return LL_ERROR;
    }

    //Lock Program/Erase access
    LL_EFLASH_ProgErase_Lock(Instance);

    return LL_OK;
}

/**
  * @}
  */


#endif /* LL_EFLASH_MODULE_ENABLED */


/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

