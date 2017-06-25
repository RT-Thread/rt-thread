/**************************************************************************!     
 *     技术讨论：QQ群  123763203
 *     官网    ：www.navota.com
 *
 * @file       acmp.c
 * @brief      模拟比较器(ACMP)函数库
 * @author     Navota
 * @date       2017-1-1
 ****************************************************************************/
 
#include "nv32f100.h"

/****************************************************************************!
 * @ 存放ACMP回调函数接口
 ****************************************************************************/
ACMP_CallbackPtr ACMP_Callback[2] = {(ACMP_CallbackPtr)NULL};

/**************************************************************************/
void ACMP0_Isr(void);
void ACMP1_Isr(void);

/*****************************************************************************//*!
*
* @brief 初始化ACMP模块
*        
* @param   pACMPx        指向ACMP寄存器基址
* @param   pConfig       控制参数  
*
* @return none.
*
* @see   ACMP_DeInit.  
*
*****************************************************************************/
void ACMP_Init(ACMP_Type *pACMPx, ACMP_ConfigType *pConfig) 
{
    if(ACMP0 == pACMPx)
    {    
        /* 使能ACMP模块的总线时钟 */
        SIM->SCGC |= SIM_SCGC_ACMP0_MASK;
 
        /* 使能ACMP中断 */
        if(pConfig->sCtrlStatus.bits.bIntEn)
            NVIC_EnableIRQ(ACMP0_IRQn);
    }
    else
    {
        SIM->SCGC |= SIM_SCGC_ACMP1_MASK;
        if(pConfig->sCtrlStatus.bits.bIntEn)
            NVIC_EnableIRQ(ACMP1_IRQn);            
    }
    /*选择ACMP正输入和负输入，正输入和负输入引脚不同*/
    pACMPx->C0 = pConfig->sPinSelect.byte;
    ACMP_ConfigDAC(pACMPx, &pConfig->sDacSet );
    //pACMPx->C1 = pConfig->sDacSet.byte;
    pACMPx->C2 = pConfig->sPinEnable.byte;
    pACMPx->CS = pConfig->sCtrlStatus.byte;
}

/*****************************************************************************//*!
*
* @brief 配置ACMP控制寄存器1.
*        
* @param   pACMPx      指向ACMP模块寄存器基地址
* @param   pDACConfig   指向 ACMP DAC 控制结构体.
*
* @return none.
*
*****************************************************************************/
void ACMP_ConfigDAC(ACMP_Type *pACMPx, ACMP_DACType *pDACConfig) 
{
    pACMPx->C1 = pDACConfig->byte;  
}

/*****************************************************************************//*!
*
* @brief  复位ACMP模块.
*        
* @param   pACMPx     指向ACMP模块寄存器基地址
*
* @return none.
*
* @see   ACMP_Init.  
*
*****************************************************************************/
void ACMP_DeInit(ACMP_Type *pACMPx) 
{
    if(ACMP0 == pACMPx)
    {    
        if(pACMPx->CS & ACMP_CS_ACIE_MASK)
            NVIC_DisableIRQ(ACMP0_IRQn);
    }
    else
    {
        if(pACMPx->CS & ACMP_CS_ACIE_MASK)
            NVIC_DisableIRQ(ACMP1_IRQn);            
    }
    
    pACMPx->CS = 0;
    pACMPx->C0 = 0;
    pACMPx->C1 = 0;
    pACMPx->C2 = 0;
    
    if(ACMP0 == pACMPx)
    {    
        SIM->SCGC &= ~SIM_SCGC_ACMP0_MASK;
    }
    else
    {
        SIM->SCGC &= ~SIM_SCGC_ACMP1_MASK;           
    } 
}

/*****************************************************************************//*!
*
* @brief  设置ACMP回调函数，通过中断服务函数调用回调函数.
*        
* @param  pACMPx       指向ACMP模块寄存器基地址. 
* @param   pfnCallback  回调函数.
*
* @return none.
*
*
*****************************************************************************/
void ACMP_SetCallback(ACMP_Type *pACMPx, ACMP_CallbackPtr pfnCallback)
{
    if(ACMP0 == pACMPx)
    {
        ACMP_Callback[0] = pfnCallback;
    }
    else
    {
        ACMP_Callback[1] = pfnCallback;
    }
}

/*****************************************************************************//*!
*
* @brief  ACMP0 中断服务函数.
*        
* @param  none. 
*
* @return none.
*
*****************************************************************************/
void ACMP0_Isr(void)
{
    if(ACMP_Callback[0])
    {
        ACMP_Callback[0]();             /*调用回调函数*/
    }
}

/*****************************************************************************//*!
*
* @brief  ACMP1 中断服务函数
*        
* @param  none. 
*
* @return none.
*
*****************************************************************************/
void ACMP1_Isr(void)
{
    if(ACMP_Callback[1])
    {
        ACMP_Callback[1]();             /* 调用回调函数*/
    }
}
