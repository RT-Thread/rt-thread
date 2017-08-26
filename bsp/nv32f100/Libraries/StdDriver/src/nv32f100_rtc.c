/************************************************************************!     
 *     技术讨论：QQ群  123763203
 *     官网    ：www.navota.com
 *
 * @file       rtc.c
 * @brief      rtc定时器函数库
 * @author     Navota
 * @date       2017-1-1
 ***************************************************************************/
#include "nv32f100.h"

/*!
 * @brief 存放回调入口
 *
 */
RTC_CallbackType RTC_Callback[1] = {(RTC_CallbackType)NULL};  



void RTC_Isr(void);


/******************************************************************************
* 定义RTC的接口函数
*******************************************************************************/

/*****************************************************************************//*!
*
* @brief 初始化RTC模块
*        
* @param[in]   pConfig   配置RTC模块的结构体  
*
* @return none 
*
*****************************************************************************/
void RTC_Init(RTC_ConfigType *pConfig)
{
    uint16_t    u16Clocksource, u16Prescler;
    uint16_t    u16ModVal;
    
    u16Clocksource =0;  
    u16Prescler    =0;
    u16ModVal      =0;

    SIM->SCGC     |= SIM_SCGC_RTC_MASK; 
    
    u16ModVal      = pConfig->u16ModuloValue;
    RTC_SetModulo(u16ModVal); 
    
    if (pConfig->bRTCOut)
    {
    
        RTC->SC= RTC_SC_RTCO_MASK;       
    } 
    
    if (pConfig->bInterruptEn)
    {
         NVIC_EnableIRQ(RTC_IRQn);
         RTC_EnableInt(); 
    }
    else      
    {   
        NVIC_DisableIRQ(RTC_IRQn);
    }
    
    if (pConfig->bFlag)
    {   
        RTC_ClrFlags();         
    }

    u16Clocksource = pConfig->bClockSource; 
    u16Prescler    = pConfig->bClockPresaler;
     
    RTC_SetClock(u16Clocksource,u16Prescler );
}



/*****************************************************************************//*!
*
* @brief 设置RTC模块的中断回调函数
*        
* @param[in]   pfnCallback   回调函数的地址
*
* @return none 
*
*****************************************************************************/
void RTC_SetCallback(RTC_CallbackType pfnCallback)
{
  RTC_Callback[0] = pfnCallback;
}


/*****************************************************************************//*!
*
* @brief 复位RTC模块
*        
* @param none  
*
* @return none 
*
*****************************************************************************/
void RTC_DeInit(void)
{
    NVIC_DisableIRQ(RTC_IRQn);    
    RTC->MOD = 0;
    while(RTC->MOD);
    
    if(RTC_GetFlags())
    {
        RTC_ClrFlags();
    }
    
    RTC->SC = 0;
    while(RTC->SC);
    SIM->SCGC &= ~SIM_SCGC_RTC_MASK;
}



/*****************************************************************************//*!
*
* @brief RTC中断服务函数
*        
* @param none  
*
* @return none 
*
*****************************************************************************/
void RTC_Isr(void) 
{
    RTC_ClrFlags();  //清除中断标志位       
    if (RTC_Callback[0])
    {    
        RTC_Callback[0]();     
    }
}


