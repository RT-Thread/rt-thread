/************************************************************************!     
 *     技术讨论：QQ群  123763203
 *     官网    ：www.navota.com
 *
 * @file       pit.c
 * @brief      pit定时器函数库
 * @author     Navota
 * @date       2017-1-1
 ************************************************************************/

#include "nv32f100.h"

/*!
 * @brief 存放回调入口
 *
 */
PIT_CallbackType PIT_Callback[2] = {(PIT_CallbackType)NULL}; 

void PIT_Ch0Isr(void);
void PIT_Ch1Isr(void);

/******************************************************************************
* 定义PIT的接口函数
*******************************************************************************/

/*****************************************************************************//*!
*
* @brief 初始化PIT模块.
*        
* @param[in]   u8Channel_No   通道号
* @param[in]   pConfig        配置模块的结构体指针
*
* @return none
*
*****************************************************************************/
void PIT_Init(uint8_t u8Channel_No, PIT_ConfigType *pConfig)
{  
    SIM->SCGC |= SIM_SCGC_PIT_MASK;     /*!< 选通PIT模块 */
    
    if (pConfig->bFreeze)            
    {                                               
        PIT_SetDebugFreeze();            
    } 
    
    if (pConfig->bModuleDis == 0) 
    {                                              
        PIT_Enable();       /*!< 标准PIT定时器的时钟使能 */                                                                                
    }  
    
    PIT_SetLoadVal(u8Channel_No, pConfig->u32LoadValue);  //加载对应通道的定时器起始值
    
    if (pConfig->bInterruptEn)            
    {                                   
        if (u8Channel_No)
        {        
             NVIC_EnableIRQ(PIT_CH1_IRQn);  //开启对应通道IRQ中断         
        }
        else
        {                  
            NVIC_EnableIRQ(PIT_CH0_IRQn);
        }
        PIT_ChannelEnableInt(u8Channel_No); //开启对应通道的中断请求
    }                   
    else                                     
    {                     
        NVIC_DisableIRQ(PIT_CH0_IRQn); //禁止通道0的IRQ中断          
    }

    if (pConfig->bChainMode)            
    {                                               
        PIT_ChannelEnableChain(u8Channel_No); //定时器链接到前一定时器            
    }
    
    if (pConfig->bETMerEn)            
    {                                               
        PIT_ChannelEnable(u8Channel_No); //定时器通道使能               
    }             

}


/*****************************************************************************//*!
*
* @brief 装载定时器起始值到加载值寄存器中.
*        
* @param[in]   u8Channel_No   通道号 
* @param[in]   u32loadvalue   所有加载的数值
*
* @return none
*
*****************************************************************************/
void PIT_SetLoadVal(uint8_t u8Channel, uint32_t u32loadvalue)

{
    PIT->CHANNEL[u8Channel].LDVAL = u32loadvalue;   
}


/*****************************************************************************//*!
*
* @brief 设置PIT模块回调函数.
*        
* @param[in]   u8Channel_No   通道号.   
* @param[in]   pfnCallback    指向回调函数.   
*
* @return none
*
*****************************************************************************/
void PIT_SetCallback(uint8_t u8Channel_No, PIT_CallbackType pfnCallback)
{
  PIT_Callback[u8Channel_No] = pfnCallback;
}


/*****************************************************************************//*!
*
* @brief 复位PIT模块
*        
* @param none  
*
* @return none 
*
*****************************************************************************/
void PIT_DeInit(void)
{
    NVIC_DisableIRQ(PIT_CH0_IRQn);
    NVIC_DisableIRQ(PIT_CH1_IRQn);    
    PIT_SetLoadVal(0,0);
    PIT_SetLoadVal(1,0);
    PIT_ChannelDisable(0);
    PIT_ChannelDisable(1);
    PIT_ChannelDisableInt(0);
    PIT_ChannelDisableInt(1);
    PIT_ChannelDisableChain(0);
    PIT_ChannelDisableChain(1);    
    PIT_ChannelClrFlags(0);
    PIT_ChannelClrFlags(1);    
    PIT_SetDebugOn();
    PIT_Disable();
    SIM->SCGC &= ~SIM_SCGC_PIT_MASK;
}


/*****************************************************************************//*!
*
* @brief PIT0通道中断服务函数.
*        
* @param none
*
* @return none 
*
*****************************************************************************/
void PIT_Ch0Isr(void) 
{   
   PIT_ChannelClrFlags(0); //清除中断标志位
    
    if (PIT_Callback[0])
    {    
        PIT_Callback[0]();     
    }
}
    
/*****************************************************************************//*!
*
* @brief PIT0通道中断服务函数.
*        
* @param none
*
* @return none 
*
*****************************************************************************/
void PIT_Ch1Isr(void) 
{   
    PIT_ChannelClrFlags(1); //清除中断标志位
    if (PIT_Callback[1])
    {    
        PIT_Callback[1]();     
    }
}    


