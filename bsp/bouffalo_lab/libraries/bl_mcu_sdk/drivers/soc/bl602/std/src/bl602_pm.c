/**
  ******************************************************************************
  * @file    bl602_pm.c
  * @version V1.0
  * @date
  * @brief   This file is the peripheral case c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
#include "bl602.h"
#include "bl602_aon.h"
#include "bl602_hbn.h"
#include "bl602_glb.h"
#include "bl602_pds.h"
#include "bflb_sf_cfg.h"
#include "bflb_sf_ctrl.h"
#include "bflb_sflash.h"
#include "bflb_spi.h"
#include "bflb_xip_sflash.h"
#include "bl602_common.h"
#include "bflb_sec_trng.h"
/** @addtogroup  BL602_Peripheral_Case
 *  @{
 */

/** @addtogroup  PDS_SETTING
 *  @{
 */

/** @defgroup  PDS_SETTING_Private_Macros
 *  @{
 */

/*@} end of group PDS_SETTING_Private_Macros */

/** @defgroup  PDS_SETTING_Private_Types
 *  @{
 */

/*@} end of group PDS_SETTING_Private_Types */

/** @defgroup  PDS_SETTING_Private_Variables
 *  @{
 */
PDS_DEFAULT_LV_CFG_Type ATTR_TCM_CONST_SECTION pdsCfgLevel0 = {
    .pdsCtl = {
        .pdsStart     =1,
        .sleepForever =0,
        .xtalForceOff =0,
        .saveWiFiState=0,
        .dcdc18Off    =1,
        .bgSysOff     =1,
        .clkOff       =1,
        .memStby      =1,
        .isolation    =1,
        .waitXtalRdy  =0,
        .pdsPwrOff    =1,
        .xtalOff      =0,
        .socEnbForceOn=1,
        .pdsRstSocEn  =0,
        .pdsRC32mOn   =0,
        .pdsLdoVselEn =0,
        .wfiMask      =0,       /* aviod cpu catch wfi signal */
        .ldo11Off     =1,       /* E_ITEM_03 */
        .pdsLdoVol    =0xA,
        .pdsCtlRfSel  =3,
        .pdsCtlPllSel =0,
    },
    .pdsCtl2 = {
        .forceCpuPwrOff   =0,
        .forceWbPwrOff    =0,
        .forceCpuIsoPwrOff=0,
        .forceWbIsoPwrOff =0,
        .forceCpuPdsRst   =0,
        .forceWbPdsRst    =0,
        .forceCpuMemStby  =0,
        .forceWbMemStby   =0,
        .forceCpuGateClk  =0,
        .forceWbGateClk   =0,
    },
    .pdsCtl3 = {
        .forceMiscPwrOff =0,
        .forceMiscIsoEn  =0,
        .forceMiscPdsRst =0,
        .forceMiscMemStby=0,
        .forceMiscGateClk=0,
        .CpuIsoEn        =0,
        .WbIsoEn         =0,
        .MiscIsoEn       =0,
    },
    .pdsCtl4 = {
        .cpuPwrOff  =0,
        .cpuRst     =0,
        .cpuMemStby =1,
        .cpuGateClk =1,
        .WbPwrOff   =0,
        .WbRst      =0,
        .WbMemStby  =1,
        .WbGateClk  =1,
        .MiscPwrOff =0,
        .MiscRst    =0,
        .MiscMemStby=1,
        .MiscGateClk=1,
    }
};
PDS_DEFAULT_LV_CFG_Type ATTR_TCM_CONST_SECTION pdsCfgLevel1 = {
    .pdsCtl = {
        .pdsStart     =1,
        .sleepForever =0,
        .xtalForceOff =0,
        .saveWiFiState=0,
        .dcdc18Off    =1,
        .bgSysOff     =1,
        .clkOff       =1,
        .memStby      =1,
        .isolation    =1,
        .waitXtalRdy  =0,
        .pdsPwrOff    =1,
        .xtalOff      =0,
        .socEnbForceOn=1,
        .pdsRstSocEn  =0,
        .pdsRC32mOn   =0,
        .pdsLdoVselEn =0,
        .wfiMask      =0,       /* aviod cpu catch wfi signal */
        .ldo11Off     =1,       /* E_ITEM_03 */
        .pdsLdoVol    =0xA,
        .pdsCtlRfSel  =2,
        .pdsCtlPllSel =0,
    },
    .pdsCtl2 = {
        .forceCpuPwrOff   =0,
        .forceWbPwrOff    =0,
        .forceCpuIsoPwrOff=0,
        .forceWbIsoPwrOff =0,
        .forceCpuPdsRst   =0,
        .forceWbPdsRst    =0,
        .forceCpuMemStby  =0,
        .forceWbMemStby   =0,
        .forceCpuGateClk  =0,
        .forceWbGateClk   =0,
    },
    .pdsCtl3 = {
        .forceMiscPwrOff =0,
        .forceMiscIsoEn  =0,
        .forceMiscPdsRst =0,
        .forceMiscMemStby=0,
        .forceMiscGateClk=0,
        .CpuIsoEn        =0,
        .WbIsoEn         =1,
        .MiscIsoEn       =0,
    },
    .pdsCtl4 = {
        .cpuPwrOff  =0,
        .cpuRst     =0,
        .cpuMemStby =1,
        .cpuGateClk =1,
        .WbPwrOff   =1,
        .WbRst      =1,
        .WbMemStby  =1,
        .WbGateClk  =1,
        .MiscPwrOff =0,
        .MiscRst    =0,
        .MiscMemStby=1,
        .MiscGateClk=1,
    }
};
PDS_DEFAULT_LV_CFG_Type ATTR_TCM_CONST_SECTION pdsCfgLevel2 = {
    .pdsCtl = {
        .pdsStart     =1,
        .sleepForever =0,
        .xtalForceOff =0,
        .saveWiFiState=0,
        .dcdc18Off    =1,
        .bgSysOff     =1,
        .clkOff       =1,
        .memStby      =1,
        .isolation    =1,
        .waitXtalRdy  =0,
        .pdsPwrOff    =1,
        .xtalOff      =0,
        .socEnbForceOn=1,
        .pdsRstSocEn  =0,
        .pdsRC32mOn   =0,
        .pdsLdoVselEn =0,
        .wfiMask      =0,       /* aviod cpu catch wfi signal */
        .ldo11Off     =1,       /* E_ITEM_03 */
        .pdsLdoVol    =0xA,
        .pdsCtlRfSel  =3,
        .pdsCtlPllSel =0,
    },
    .pdsCtl2 = {
        .forceCpuPwrOff   =0,
        .forceWbPwrOff    =0,
        .forceCpuIsoPwrOff=0,
        .forceWbIsoPwrOff =0,
        .forceCpuPdsRst   =0,
        .forceWbPdsRst    =0,
        .forceCpuMemStby  =0,
        .forceWbMemStby   =0,
        .forceCpuGateClk  =0,
        .forceWbGateClk   =0,
    },
    .pdsCtl3 = {
        .forceMiscPwrOff =0,
        .forceMiscIsoEn  =0,
        .forceMiscPdsRst =0,
        .forceMiscMemStby=0,
        .forceMiscGateClk=0,
        .CpuIsoEn        =1,
        .WbIsoEn         =0,
        .MiscIsoEn       =0,
    },
    .pdsCtl4 = {
        .cpuPwrOff  =1,
        .cpuRst     =1,
        .cpuMemStby =1,
        .cpuGateClk =1,
        .WbPwrOff   =0,
        .WbRst      =0,
        .WbMemStby  =1,
        .WbGateClk  =1,
        .MiscPwrOff =0,
        .MiscRst    =0,
        .MiscMemStby=1,
        .MiscGateClk=1,
    }
};
PDS_DEFAULT_LV_CFG_Type ATTR_TCM_CONST_SECTION pdsCfgLevel3 = {
    .pdsCtl = {
        .pdsStart     =1,
        .sleepForever =0,
        .xtalForceOff =0,
        .saveWiFiState=0,
        .dcdc18Off    =1,
        .bgSysOff     =1,
        .clkOff       =1,
        .memStby      =1,
        .isolation    =1,
        .waitXtalRdy  =0,
        .pdsPwrOff    =1,
        .xtalOff      =1,
        .socEnbForceOn=1,
        .pdsRstSocEn  =0,
        .pdsRC32mOn   =0,
        .pdsLdoVselEn =0,
        .wfiMask      =0,       /* aviod cpu catch wfi signal */
        .ldo11Off     =0,       /* E_ITEM_03 */
        .pdsLdoVol    =0xA,
        .pdsCtlRfSel  =2,
        .pdsCtlPllSel =0,
    },
    .pdsCtl2 = {
        .forceCpuPwrOff   =0,
        .forceWbPwrOff    =0,
        .forceCpuIsoPwrOff=0,
        .forceWbIsoPwrOff =0,
        .forceCpuPdsRst   =0,
        .forceWbPdsRst    =0,
        .forceCpuMemStby  =0,
        .forceWbMemStby   =0,
        .forceCpuGateClk  =0,
        .forceWbGateClk   =0,
    },
    .pdsCtl3 = {
        .forceMiscPwrOff =0,
        .forceMiscIsoEn  =0,
        .forceMiscPdsRst =0,
        .forceMiscMemStby=0,
        .forceMiscGateClk=0,
        .CpuIsoEn        =1,
        .WbIsoEn         =1,
        .MiscIsoEn       =0,
    },
    .pdsCtl4 = {
        .cpuPwrOff  =1,
        .cpuRst     =1,
        .cpuMemStby =1,
        .cpuGateClk =1,
        .WbPwrOff   =1,
        .WbRst      =1,
        .WbMemStby  =1,
        .WbGateClk  =1,
        .MiscPwrOff =0,
        .MiscRst    =0,
        .MiscMemStby=1,
        .MiscGateClk=1,
    }
};
PDS_DEFAULT_LV_CFG_Type ATTR_TCM_CONST_SECTION pdsCfgLevel7 = {
    .pdsCtl = {
        .pdsStart     =1,
        .sleepForever =0,
        .xtalForceOff =0,
        .saveWiFiState=0,
        .dcdc18Off    =1,
        .bgSysOff     =1,
        .clkOff       =1,
        .memStby      =1,
        .isolation    =1,
        .waitXtalRdy  =0,
        .pdsPwrOff    =1,
        .xtalOff      =0,
        .socEnbForceOn=0,
        .pdsRstSocEn  =0,
        .pdsRC32mOn   =0,
        .pdsLdoVselEn =0,
        .wfiMask      =0,       /* aviod cpu catch wfi signal */
        .ldo11Off     =0,       /* E_ITEM_03 */
        .pdsLdoVol    =0xA,
        .pdsCtlRfSel  =2,
        .pdsCtlPllSel =0,
    },
    .pdsCtl2 = {
        .forceCpuPwrOff   =0,
        .forceWbPwrOff    =0,
        .forceCpuIsoPwrOff=0,
        .forceWbIsoPwrOff =0,
        .forceCpuPdsRst   =0,
        .forceWbPdsRst    =0,
        .forceCpuMemStby  =0,
        .forceWbMemStby   =0,
        .forceCpuGateClk  =0,
        .forceWbGateClk   =0,
    },
    .pdsCtl3 = {
        .forceMiscPwrOff =0,
        .forceMiscIsoEn  =0,
        .forceMiscPdsRst =0,
        .forceMiscMemStby=0,
        .forceMiscGateClk=0,
        .CpuIsoEn        =1,
        .WbIsoEn         =1,
        .MiscIsoEn       =1,
    },
    .pdsCtl4 = {
        .cpuPwrOff  =1,
        .cpuRst     =1,
        .cpuMemStby =1,
        .cpuGateClk =1,
        .WbPwrOff   =1,
        .WbRst      =1,
        .WbMemStby  =1,
        .WbGateClk  =1,
        .MiscPwrOff =1,
        .MiscRst    =1,
        .MiscMemStby=1,
        .MiscGateClk=1,
    }
};
PDS_RAM_CFG_Type ATTR_TCM_CONST_SECTION ramCfg = {
    .PDS_RAM_CFG_0KB_16KB_CPU_RAM_RET =1,
    .PDS_RAM_CFG_16KB_32KB_CPU_RAM_RET=1,
    .PDS_RAM_CFG_32KB_48KB_CPU_RAM_RET=1,
    .PDS_RAM_CFG_48KB_64KB_CPU_RAM_RET=1,
    .PDS_RAM_CFG_0KB_16KB_CPU_RAM_SLP =0,
    .PDS_RAM_CFG_16KB_32KB_CPU_RAM_SLP=0,
    .PDS_RAM_CFG_32KB_48KB_CPU_RAM_SLP=0,
    .PDS_RAM_CFG_48KB_64KB_CPU_RAM_SLP=0,
};


/*@} end of group PDS_SETTING_Private_Variables */

/** @defgroup  PDS_SETTING_Global_Variables
 *  @{
 */

/*@} end of group PDS_SETTING_Global_Variables */

/** @defgroup  PDS_SETTING_Private_Fun_Declaration
 *  @{
 */

/*@} end of group PDS_SETTING_Private_Fun_Declaration */

/** @defgroup  PDS_SETTING_Private_Functions
 *  @{
 */

/****************************************************************************//**
 * @brief  PDS update flash_ctrl setting
 *
 * @param  fastClock: fast clock
 *
 * @return None
 *
*******************************************************************************/
void ATTR_TCM_SECTION PDS_Update_Flash_Ctrl_Setting(uint8_t fastClock)
{
    if(fastClock){
        GLB_Set_SF_CLK(1, GLB_SFLASH_CLK_80M, 0);
    }else{
        GLB_Set_SF_CLK(1, GLB_SFLASH_CLK_XTAL, 0);
    }
    bflb_sf_ctrl_set_clock_delay(fastClock);
}

/****************************************************************************//**
 * @brief  PDS power on flash
 *
 * @param  cfg: PDS app config
 *
 * @return None
 *
*******************************************************************************/
void ATTR_TCM_SECTION PDS_Power_On_Flash(PDS_APP_CFG_Type *cfg)
{
    /* Init flash gpio */
    bflb_sf_cfg_init_flash_gpio(0, 1);

    bflb_sf_ctrl_set_owner(SF_CTRL_OWNER_SAHB);

    /* Restore flash */
    bflb_sflash_restore_from_powerdown(cfg->flashCfg, cfg->flashContRead, 0);
}


/****************************************************************************//**
 * @brief  power down sleep mode test function
 *
 * @param  cfg: PDS app config
 *
 * @return None
 *
*******************************************************************************/
void ATTR_TCM_SECTION PDS_Mode_Enter(PDS_APP_CFG_Type *cfg)
{
    PDS_DEFAULT_LV_CFG_Type *pPdsCfg = NULL;

    if(cfg->useXtal32k){
        HBN_32K_Sel(HBN_32K_XTAL);
    }else{
        HBN_32K_Sel(HBN_32K_RC);
        HBN_Power_Off_Xtal_32K();
    }

    /* always disable HBN pin pull up/down for reduce PDS0/1/2/3/7 current, 0x4000F014[16]=0 */
    /* system_init should set reg_en_hw_pu_pd = 0  */
    /* set reg_en_hw_pu_pd = 0, never reg_en_hw_pu_pd = 1 */
    HBN_Hw_Pu_Pd_Cfg(DISABLE);

    /* mask/unmask HBN pin wakeup, 0x4000F014[4:3] */
    HBN_Pin_WakeUp_Mask(~(cfg->pdsAonGpioWakeupSrc));
    if(cfg->pdsAonGpioWakeupSrc!=0){
        HBN_Aon_Pad_IeSmt_Cfg(ENABLE);
        HBN_GPIO_INT_Enable(cfg->pdsAonGpioTrigType);
    }else{
        HBN_Aon_Pad_IeSmt_Cfg(DISABLE);
    }

    /* turn_off_sec_ring */
    // bflb_sec_eng_turn_off_sec_ring();        /* E_ITEM_04 */

    /* disable sec_eng to reduce current which enabled by bflb_platform_init(0) */
    // bflb_sec_eng_trng_disable();

    /* pre callback */
    if(cfg->preCbFun){
        cfg->preCbFun();
    }

    /* To make it simple and safe*/
    __disable_irq();

    uint32_t sf_pin_select = 0;
    if(cfg->powerDownFlash){
        uint32_t tmpVal = 0;

        /* get sw uasge 0 */
        // EF_Ctrl_Read_Sw_Usage(0, (uint32_t *)&tmpVal);
        putreg32(tmpVal, 0x40007000 + 0x10);
        // tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_EF_SW_USAGE_0);
        /* get flash type */
        sf_pin_select = (tmpVal >> 14) & 0x3f;

        HBN_Power_Down_Flash(cfg->flashCfg);
        GLB_Select_External_Flash();
        /* PDS7 and HBN use HBN_Pull up since GPIO/pad turned into HZ */
        if(cfg->pdsLevel==7){
            HBN_Set_Embedded_Flash_Pullup(ENABLE);     /* E_ITEM_06 */
        }
    }

    HBN_Set_Ldo11_All_Vout(cfg->ldoLevel);

    /* if pdsLevel!=2 and pdsLevel!=3, power_down_flash_pin */
    if(cfg->turnOffFlashPad){
        if(cfg->pdsLevel==7){
            /* turn_off_internal_gpio, GPIO23 - GPIO28 */
            /* in PDS7, flash power down, flash GPIO turn to HighZ */
        }else{
            for(uint32_t pin=23;pin<29;pin++){
                GLB_GPIO_Set_PullUp(pin);
            }
        }
    }

    /* power off PLL to reduce current  */
    //if(cfg->turnoffPLL){
        GLB_Set_System_CLK(GLB_PLL_XTAL_NONE,GLB_SYS_CLK_RC32M);
        PDS_Update_Flash_Ctrl_Setting(0);
        PDS_Power_Off_PLL();
        //AON_Power_Off_XTAL();
    //}

    if(cfg->pdsLevel==0){
        pPdsCfg = &pdsCfgLevel0;
    }else if(cfg->pdsLevel==1){
        pPdsCfg = &pdsCfgLevel1;
    }else if(cfg->pdsLevel==2){
        pPdsCfg = &pdsCfgLevel2;
    }else if(cfg->pdsLevel==3){
        pPdsCfg = &pdsCfgLevel3;
    }else if(cfg->pdsLevel==7){
        pPdsCfg = &pdsCfgLevel7;
    }else{
        /* pdsLevel error */
        while(1){
            BL602_Delay_MS(500);
        }
    }

    pPdsCfg->pdsCtl.pdsLdoVol = cfg->ldoLevel;
    pPdsCfg->pdsCtl.pdsLdoVselEn = 1;

    if(!(cfg->turnOffRF)){
        pPdsCfg->pdsCtl.pdsCtlRfSel = 0;
    }

    /* config  ldo11soc_sstart_delay_aon =2 , cr_pds_pd_ldo11=0 to speedup ldo11soc_rdy_aon */
    AON_Set_LDO11_SOC_Sstart_Delay(0x2);

    *((volatile uint32_t *)(GLB_BASE + 0x50)) |= (1 << 8);
    *((volatile uint32_t *)(GLB_BASE + 0x50)) |= (0xF << 0);

    if(cfg->ocramRetetion){
        PDS_Default_Level_Config(pPdsCfg,&ramCfg,cfg->sleepTime);
    }else{
        PDS_Default_Level_Config(pPdsCfg,NULL,cfg->sleepTime);
    }
    __WFI();        /* if(.wfiMask==0){CPU won't power down until PDS module had seen __wfi} */

    /* System will Reset when PDS2\3\7 Entry Fail */
    if (cfg->pdsLevel > 1) {
        GLB_SW_System_Reset();
    }

    /* Wake up from PDS */
    /* post callback, mainly for GPIO or peripherals on/off */
    if(cfg->postCbFun){
        cfg->postCbFun();
    }

    //if(cfg->turnoffPLL){
        GLB_Set_System_CLK(cfg->xtalType,GLB_SYS_CLK_PLL160M);
        PDS_Update_Flash_Ctrl_Setting(1);
    //}

    if(cfg->turnOffFlashPad){
        bflb_sf_cfg_init_flash_gpio((uint8_t)sf_pin_select, 1);
    }

    if(cfg->powerDownFlash){
        HBN_Set_Embedded_Flash_Pullup(DISABLE);     /* E_ITEM_06 */
        PDS_Power_On_Flash(cfg);                    /* call GLB_Select_Internal_Flash() in this API */
    }

    /* always turn_on_sec_ring, may cost more current */
    // SEC_Eng_Turn_On_Sec_Ring();     /* E_ITEM_04 */

    /* always enable sec_eng, may cost more current */
    // Sec_Eng_Trng_Enable();

    HBN_Aon_Pad_IeSmt_Cfg(ENABLE);

    __enable_irq();
}

/*@} end of group PDS_SETTING_Private_Functions */

/*@} end of group PDS_SETTING */

/*@} end of group BL602_Peripheral_Case */