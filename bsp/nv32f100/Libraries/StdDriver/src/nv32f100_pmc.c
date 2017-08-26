/*****************************************************************************!     
 *     技术讨论：QQ群  123763203
 *     官网    ：www.navota.com
 *
 * @file       pmc.c
 * @brief      电源管理模块（PMC)函数库
 * @author     Navota
 * @date       2017-1-1
 *****************************************************************************/
#include "nv32f100.h"
/*****************************************************************************//*!
*
* @brief  PMC模块初始化函数
* 
* @param[in]   pPMC_Config       PMC 配置结构体.
* @param[in]   pPMC              指向PMC模块.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see PMC_DeInit.
*
*****************************************************************************/
void PMC_Init(PMC_Type *pPMC, PMC_ConfigType *pPMC_Config)
{
    pPMC->SPMSC1 = pPMC_Config->sCtrlstatus.byte;
    pPMC->SPMSC2 = pPMC_Config->sDetectVoltSelect.byte; 
    if(pPMC_Config->sCtrlstatus.bits.bLvwIrqEn)
       NVIC_EnableIRQ(LVD_LVW_IRQn);			
}

/*****************************************************************************//*!
*
* @brief  复位PMC模块.
* 
* @param[in]  pPMC              指向PMC模块.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see PMC_Init.
*
*****************************************************************************/
void PMC_DeInit(PMC_Type *pPMC)
{
    pPMC->SPMSC1 = 0x1C;
    pPMC->SPMSC2 = 0;         
}


/*****************************************************************************//*!
*
* @brief  MCU工作模式选择函数
* 
* @param[in]  u8PmcMode         选择MCU工作模式.
* @param[in]  pPMC              指向PMC模块.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*****************************************************************************/
void PMC_SetMode(PMC_Type *pPMC,uint8_t u8PmcMode)
{
    switch(u8PmcMode & 0x3) 
    {
        case PmcModeRun:    
            break;
        case PmcModeWait:   //等待模式
            wait();
            break;
        case PmcModeStop4:
            /* 停止模式下，使能低压检测*/
            pPMC->SPMSC1 |= (PMC_SPMSC1_LVDE_MASK | PMC_SPMSC1_LVDSE_MASK);	
            stop();   
            break;
        case PmcModeStop3: 
            /* 在停止模式下，禁用低压检测*/
            pPMC->SPMSC1 &= ~(PMC_SPMSC1_LVDE_MASK | PMC_SPMSC1_LVDRE_MASK | PMC_SPMSC1_LVDSE_MASK);	
            stop();  
            break;
        default: 
            break;
    }
 
}



