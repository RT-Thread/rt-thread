/**
 * @file    lp.c
 * @brief   Low power functions
 */

/* ****************************************************************************
 * Copyright (C) 2017 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *
 * $Date: 2019-10-07 11:05:30 -0500 (Mon, 07 Oct 2019) $
 * $Revision: 47429 $
 *
 *************************************************************************** */


/***** Includes *****/
#include "lp.h"
#include "pwrseq_regs.h"
#include "mxc_errors.h"
#include "gcr_regs.h"
#include "mxc_config.h"
#include "mxc_sys.h"
#include "flc.h"
#include "tmr_utils.h"

/***** Functions *****/
void LP_ClearWakeStatus(void)
{
    MXC_PWRSEQ->lp_wakefl = 0xFFFFFFFF;

    /* These flags are slow to clear, so block until they do */
    while(MXC_PWRSEQ->lp_wakefl & (MXC_PWRSEQ->lpwk_en));
}

void LP_EnableSRAM3(void)
{
    MXC_PWRSEQ->lpmemsd &= ~MXC_F_PWRSEQ_LPMEMSD_SRAM3_OFF;
}

void LP_DisableSRAM3(void)
{
    MXC_PWRSEQ->lpmemsd |= MXC_F_PWRSEQ_LPMEMSD_SRAM3_OFF;
}

void LP_EnableSRAM2(void)
{
    MXC_PWRSEQ->lpmemsd &= ~MXC_F_PWRSEQ_LPMEMSD_SRAM2_OFF;
}

void LP_DisableSRAM2(void)
{
    MXC_PWRSEQ->lpmemsd |= MXC_F_PWRSEQ_LPMEMSD_SRAM2_OFF;
}

void LP_EnableSRAM1(void)
{
    MXC_PWRSEQ->lpmemsd &= ~MXC_F_PWRSEQ_LPMEMSD_SRAM1_OFF;
}

void LP_DisableSRAM1(void)
{
    MXC_PWRSEQ->lpmemsd |= MXC_F_PWRSEQ_LPMEMSD_SRAM1_OFF;
}

void LP_EnableSRAM0(void)
{
    MXC_PWRSEQ->lpmemsd &= ~MXC_F_PWRSEQ_LPMEMSD_SRAM0_OFF;
}

void LP_DisableSRAM0(void)
{
    MXC_PWRSEQ->lpmemsd |= MXC_F_PWRSEQ_LPMEMSD_SRAM0_OFF;
}

void LP_EnableICacheLightSleep(void)
{
    MXC_GCR->memckcn |= (MXC_F_GCR_MEMCKCN_ICACHELS);
}

void LP_DisableICacheLightSleep(void)
{
    MXC_GCR->memckcn &= ~(MXC_F_GCR_MEMCKCN_ICACHELS);
}

void LP_EnableSysRAM3LightSleep(void)
{
    MXC_GCR->memckcn |= (MXC_F_GCR_MEMCKCN_SYSRAM3LS);
}

void LP_DisableSysRAM3LightSleep(void)
{
    MXC_GCR->memckcn &= ~(MXC_F_GCR_MEMCKCN_SYSRAM3LS);
}

void LP_EnableSysRAM2LightSleep(void)
{
    MXC_GCR->memckcn |= (MXC_F_GCR_MEMCKCN_SYSRAM2LS);
}

void LP_DisableSysRAM2LightSleep(void)
{
    MXC_GCR->memckcn &= ~(MXC_F_GCR_MEMCKCN_SYSRAM2LS);
}

void LP_EnableSysRAM1LightSleep(void)
{
    MXC_GCR->memckcn |= (MXC_F_GCR_MEMCKCN_SYSRAM1LS);
}

void LP_DisableSysRAM1LightSleep(void)
{
    MXC_GCR->memckcn &= ~(MXC_F_GCR_MEMCKCN_SYSRAM1LS);
}

void LP_EnableSysRAM0LightSleep(void)
{
    MXC_GCR->memckcn |= (MXC_F_GCR_MEMCKCN_SYSRAM0LS);
}

void LP_DisableSysRAM0LightSleep(void)
{
    MXC_GCR->memckcn &= ~(MXC_F_GCR_MEMCKCN_SYSRAM0LS);
}

void LP_EnableRTCAlarmWakeup(void)
{
    MXC_GCR->pm |= MXC_F_GCR_PM_RTCWKEN;
}
    
void LP_DisableRTCAlarmWakeup(void)
{
    MXC_GCR->pm &= ~MXC_F_GCR_PM_RTCWKEN;
}

void LP_EnableGPIOWakeup(const gpio_cfg_t *wu_pins)
{
    MXC_GCR->pm |= MXC_F_GCR_PM_GPIOWKEN;
    switch(wu_pins->port)
    {
      case 0: MXC_PWRSEQ->lpwk_en |= wu_pins->mask; break;
    }
}

void LP_DisableGPIOWakeup(const gpio_cfg_t *wu_pins)
{
    switch(wu_pins->port)
    {
      case 0: MXC_PWRSEQ->lpwk_en &= ~wu_pins->mask; break;
    }
    
    if(MXC_PWRSEQ->lpwk_en == 0)
    {
        MXC_GCR->pm &= ~MXC_F_GCR_PM_GPIOWKEN;
    }
}

void LP_EnterSleepMode(void)
{    
    // Clear SLEEPDEEP bit 
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;

    // Go into Sleep mode and wait for an interrupt to wake the processor 
    __WFI();
}

void LP_EnterDeepSleepMode(void)
{    
    // Set SLEEPDEEP bit 
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    // Auto-powerdown 96 MHz oscillator when in deep sleep 
    MXC_GCR->pm |= MXC_F_GCR_PM_HIRCPD;
    // Go into Deepsleep mode and wait for an interrupt to wake the processor 
    __WFI();
}

void LP_EnterBackupMode(void)
{    
    MXC_GCR->pm &= ~MXC_F_GCR_PM_MODE;
    MXC_GCR->pm |= MXC_S_GCR_PM_MODE_BACKUP;
    while(1);
}

void LP_EnterShutdownMode(void)
{
    MXC_GCR->pm &= ~MXC_F_GCR_PM_MODE;
    MXC_GCR->pm |= MXC_S_GCR_PM_MODE_SHUTDOWN;
    while(1);
}
void LP_SetOperatingVoltage(lp_ovr_t ovr)
{
    uint32_t div;

    //Set flash wait state for any clock so its not to low after clock changes.
    MXC_GCR->memckcn = (MXC_GCR->memckcn & ~(MXC_F_GCR_MEMCKCN_FWS)) | (0x5UL << MXC_F_GCR_MEMCKCN_FWS_POS);

    //set the OVR bits
    MXC_PWRSEQ->lp_ctrl &= ~(MXC_F_PWRSEQ_LP_CTRL_OVR);
    MXC_PWRSEQ->lp_ctrl |= ovr;

    //Set LVE bit
    if(ovr == LP_OVR_0_9){
        MXC_FLC->cn |= MXC_F_FLC_CN_LVE;
    }
    else{
        MXC_FLC->cn &= ~(MXC_F_FLC_CN_LVE);
    }

    // Update SystemCoreClock variable
    SystemCoreClockUpdate();

    // Get the clock divider
    div = (MXC_GCR->clkcn & MXC_F_GCR_CLKCN_PSC) >> MXC_F_GCR_CLKCN_PSC_POS;

    //Set Flash Wait States
    if(ovr == LP_OVR_0_9){

        if(div == 0){
            MXC_GCR->memckcn = (MXC_GCR->memckcn & ~(MXC_F_GCR_MEMCKCN_FWS)) | (0x2UL << MXC_F_GCR_MEMCKCN_FWS_POS);

        } else{
            MXC_GCR->memckcn = (MXC_GCR->memckcn & ~(MXC_F_GCR_MEMCKCN_FWS)) | (0x1UL << MXC_F_GCR_MEMCKCN_FWS_POS);

        }

    } else if( ovr == LP_OVR_1_0){  
        if(div == 0){
            MXC_GCR->memckcn = (MXC_GCR->memckcn & ~(MXC_F_GCR_MEMCKCN_FWS)) | (0x2UL << MXC_F_GCR_MEMCKCN_FWS_POS);

        } else{
            MXC_GCR->memckcn = (MXC_GCR->memckcn & ~(MXC_F_GCR_MEMCKCN_FWS)) | (0x1UL << MXC_F_GCR_MEMCKCN_FWS_POS);

        }

    } else {

        if(div == 0){
            MXC_GCR->memckcn = (MXC_GCR->memckcn & ~(MXC_F_GCR_MEMCKCN_FWS)) | (0x4UL << MXC_F_GCR_MEMCKCN_FWS_POS);
        } else if(div == 1){
            MXC_GCR->memckcn = (MXC_GCR->memckcn & ~(MXC_F_GCR_MEMCKCN_FWS)) | (0x2UL << MXC_F_GCR_MEMCKCN_FWS_POS);

        } else{
            MXC_GCR->memckcn = (MXC_GCR->memckcn & ~(MXC_F_GCR_MEMCKCN_FWS)) | (0x1UL << MXC_F_GCR_MEMCKCN_FWS_POS);

        }
    }

}

void LP_EnableSRamRet0(void){
    MXC_PWRSEQ->lp_ctrl |= MXC_F_PWRSEQ_LP_CTRL_RAMRET_SEL0;
}
 
void LP_DisableSRamRet0(void){
    MXC_PWRSEQ->lp_ctrl &= ~MXC_F_PWRSEQ_LP_CTRL_RAMRET_SEL0;
}

void LP_EnableSRamRet1(void){
    MXC_PWRSEQ->lp_ctrl |= MXC_F_PWRSEQ_LP_CTRL_RAMRET_SEL1;
}
 
void LP_DisableSRamRet1(void){
    MXC_PWRSEQ->lp_ctrl &= ~MXC_F_PWRSEQ_LP_CTRL_RAMRET_SEL1;
}

void LP_EnableSRamRet2(void){
    MXC_PWRSEQ->lp_ctrl |= MXC_F_PWRSEQ_LP_CTRL_RAMRET_SEL2;
}
 
void LP_DisableSRamRet2(void){
    MXC_PWRSEQ->lp_ctrl &= ~MXC_F_PWRSEQ_LP_CTRL_RAMRET_SEL2;
}

void LP_EnableSRamRet3(void){
    MXC_PWRSEQ->lp_ctrl |= MXC_F_PWRSEQ_LP_CTRL_RAMRET_SEL3;
}
 
void LP_DisableSRamRet3(void){
    MXC_PWRSEQ->lp_ctrl &= ~MXC_F_PWRSEQ_LP_CTRL_RAMRET_SEL3;
}

void LP_EnableBlockDetect(void){
    MXC_PWRSEQ->lp_ctrl &= ~MXC_F_PWRSEQ_LP_CTRL_VCORE_DET_BYPASS; 
}

void LP_DisableBlockDetect(void){
    MXC_PWRSEQ->lp_ctrl |= MXC_F_PWRSEQ_LP_CTRL_VCORE_DET_BYPASS; 
}

void LP_EnableRamRetReg(void){
    MXC_PWRSEQ->lp_ctrl |= MXC_F_PWRSEQ_LP_CTRL_RETREG_EN;
}

void LP_DisableRamRetReg(void){
    MXC_PWRSEQ->lp_ctrl &= ~MXC_F_PWRSEQ_LP_CTRL_RETREG_EN;
}

void LP_EnableFastWk(void){
    MXC_PWRSEQ->lp_ctrl |= MXC_F_PWRSEQ_LP_CTRL_FAST_WK_EN;
}

void LP_DisableFastWk(void){
    MXC_PWRSEQ->lp_ctrl &= ~MXC_F_PWRSEQ_LP_CTRL_FAST_WK_EN;
}

void LP_EnableBandGap(void){
    MXC_PWRSEQ->lp_ctrl &= ~MXC_F_PWRSEQ_LP_CTRL_BG_OFF;
}

void LP_DisableBandGap(void){
    MXC_PWRSEQ->lp_ctrl |= MXC_F_PWRSEQ_LP_CTRL_BG_OFF;
}

void LP_EnableVCorePORSignal(void){
    MXC_PWRSEQ->lp_ctrl &= ~MXC_F_PWRSEQ_LP_CTRL_VCORE_POR_DIS;
}

void LP_DisableVCorePORSignal(void){
    MXC_PWRSEQ->lp_ctrl |= MXC_F_PWRSEQ_LP_CTRL_VCORE_POR_DIS;
}

void LP_EnableLDO(void){
    MXC_PWRSEQ->lp_ctrl &= ~MXC_F_PWRSEQ_LP_CTRL_LDO_DIS;
}

void LP_DisableLDO(void){
    MXC_PWRSEQ->lp_ctrl |= MXC_F_PWRSEQ_LP_CTRL_LDO_DIS;
}

void LP_EnableVCoreSVM(void){
    MXC_PWRSEQ->lp_ctrl &= ~MXC_F_PWRSEQ_LP_CTRL_VCORE_SVM_DIS;
}

void LP_DisableVCoreSVM(void){
    MXC_PWRSEQ->lp_ctrl |= MXC_F_PWRSEQ_LP_CTRL_VCORE_SVM_DIS;
}

void LP_EnableVDDIOPorMonitoF(void){
    MXC_PWRSEQ->lp_ctrl &= ~MXC_F_PWRSEQ_LP_CTRL_VDDIO_POR_DIS;
}

void LP_DisableVDDIOPorMonitor(void){
    MXC_PWRSEQ->lp_ctrl |= MXC_F_PWRSEQ_LP_CTRL_VDDIO_POR_DIS;
}
