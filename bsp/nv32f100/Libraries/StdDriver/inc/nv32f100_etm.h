/******************************************************************************
*
* @brief  ETM 驱动头文件.  
*
******************************************************************************/
#ifndef ETM_H_
#define ETM_H_
#ifdef __cplusplus
extern "C" {
#endif
	
#include "common.h"
/******************************************************************************
* ETM 返回值定义
*
*//*! 
* @{
*******************************************************************************/
#define ETM_ERR_SUCCESS         0               /*!< 返回成功 */
#define ETM_ERR_INVALID_PARAM   1               /*!< 返回无效参数 */
/*! @}                                                                        */


/******************************************************************************
* ETM 通道号定义
*
*//*!
* @{
*******************************************************************************/
#define ETM_CHANNEL_CHANNEL0    0               /*!< 通道0 */
#define ETM_CHANNEL_CHANNEL1    1               /*!< 通道1 */
#define ETM_CHANNEL_CHANNEL2    2               /*!< 通道2 */
#define ETM_CHANNEL_CHANNEL3    3               /*!< 通道3 */
#define ETM_CHANNEL_CHANNEL4    4               /*!< 通道4 */
#define ETM_CHANNEL_CHANNEL5    5               /*!< 通道5 */

#define ETM_CHANNELPAIR0        0               /*!< 通道对0:ch0 & ch1 */
#define ETM_CHANNELPAIR1        2               /*!< 通道对1:ch2 & ch3 */
#define ETM_CHANNELPAIR2        4               /*!< 通道对2:ch4 & ch5 */

/*! @}                                                                        */

/******************************************************************************
* ETM PWM模式定义
*
*//*! 
* @{
*******************************************************************************/
#define ETM_PWMMODE_EDGEALLIGNED      1          /*!< 边沿对齐PWM */
#define ETM_PWMMODE_CENTERALLIGNED    2          /*!< 中央对齐PWM */
#define ETM_PWMMODE_COMBINE           3          /*!< 联合PWM     */
/*! @}                                                   */

/******************************************************************************
* ETM 初始化值定义
*
*//*!
* @{
*******************************************************************************/
#define ETM_MOD_INIT	(20000-1)                /*!< MOD 初始化值 */
#define ETM_C0V_INIT	1000                     /*!< C0V 初始化值 */
#define ETM_C1V_INIT	1000                     /*!< C1V 初始化值 */
#define ETM_C2V_INIT	1000                     /*!< C2V 初始化值 */    
#define ETM_C3V_INIT	1000                     /*!< C3V 初始化值 */
#define ETM_C4V_INIT	1000                     /*!< C4V 初始化值 */
#define ETM_C5V_INIT	1000                     /*!< C5V 初始化值 */
/*! @}                                                                        */

/******************************************************************************
* ETM 联合模式位定义
*
*//*!
* @{
*******************************************************************************/
#define ETM_COMBINE_FAULTEN_MASK  0x40       /*!< 故障控制使能 */
#define ETM_COMBINE_SYNCEN_MASK   0x20       /*!< 同步使能 */
#define ETM_COMBINE_DTEN_MASK     0x10       /*!< 死区时间使能 */
#define ETM_COMBINE_DECAP_MASK    0x08       /*!< 双边沿捕获状态位 */
#define ETM_COMBINE_DECAPEN_MASK  0x04       /*!< 双边沿捕获使能位 */
#define ETM_COMBINE_COMP_MASK     0x02       /*!< 通道互补使能 */
#define ETM_COMBINE_COMBINE_MASK  0x01       /*!< 通道组合使能 */
/*! @}                                                                        */

/******************************************************************************
* ETM 时钟源及分频系数定义
*
*//*!
* @{
*******************************************************************************/
#define ETM_CLOCK_NOCLOCK             0                 /*!< 禁用计数器 */
#define ETM_CLOCK_SYSTEMCLOCK         1                 /*!< 系统时钟 */
#define ETM_CLOCK_FIXEDFREQCLOCK      2                 /*!< 固定频率时钟 */
#define ETM_CLOCK_EXTERNALCLOCK       3                 /*!< 外接时钟 */

/* 时钟分频系数 */
#define ETM_CLOCK_PS_DIV1             0                 /*!< 1分频 */
#define ETM_CLOCK_PS_DIV2             1                 /*!< 2分频 */
#define ETM_CLOCK_PS_DIV4             2                 /*!< 4分频 */
#define ETM_CLOCK_PS_DIV8             3                 /*!< 8分频 */
#define ETM_CLOCK_PS_DIV16            4                 /*!< 16分频 */
#define ETM_CLOCK_PS_DIV32            5                 /*!< 32分频 */
#define ETM_CLOCK_PS_DIV64            6                 /*!< 64分频 */
#define ETM_CLOCK_PS_DIV128           7                 /*!< 128分频 */
/*! @}                                                                        */

/******************************************************************************
* ETM 死区时间预分频值
*
*//*! @死区时间预分频值
* @{
*******************************************************************************/
/*  */
#define ETM_DEADETME_DTPS_DIV1        0                 /*!< 1分频 */
#define ETM_DEADETME_DTPS_DIV4        2                 /*!< 4分频 */
#define ETM_DEADETME_DTPS_DIV16       3                 /*!< 16分频 */
/*! @}                                                                        */

/******************************************************************************
* ETM 输出模式定义
*
*//*!
* @{
*******************************************************************************/
/* output mode */
#define ETM_OUTPUT_TOGGLE   1                    /*!< 匹配时切换输出 */
#define ETM_OUTPUT_CLEAR    2                    /*!< 匹配时清零输出 */
#define ETM_OUTPUT_SET      3                    /*!< 匹配时置位输出 */
/*! @}                                                                        */
      
/******************************************************************************
* ETM 输入捕捉边沿定义
*
*//*! 
* @{
*******************************************************************************/

#define ETM_INPUTCAPTURE_RISINGEDGE           1     /*!< 上升沿 */
#define ETM_INPUTCAPTURE_FALLINGEDGE          2     /*!< 下降沿 */
#define ETM_INPUTCAPTURE_BOTHEDGE             3     /*!< 双边沿 */

#define ETM_INPUTCAPTURE_DUALEDGE_NOEDGE      0     /*!< 无 */
#define ETM_INPUTCAPTURE_DUALEDGE_RISINGEDGE  1     /*!< 上升沿 */
#define ETM_INPUTCAPTURE_DUALEDGE_FALLInGEDGE 2     /*!< 下降沿 */
#define ETM_INPUTCAPTURE_DUALEDGE_BOTHEDGE    3     /*!< 双边沿 */
/*! @}                                                                        */

/******************************************************************************
* ETM 双沿捕捉模式定义
*
*//*! 
* @{
*******************************************************************************/
#define ETM_INPUTCAPTURE_DUALEDGE_ONESHOT     4  /*!< 单次捕捉模式 */ 
#define ETM_INPUTCAPTURE_DUALEDGE_CONTINUOUS  5  /*!< 持续捕捉模式 */
/*! @}                                                                        */

/******************************************************************************
* ETM 边沿PWM模式定义
*
*//*! 
* @{
*******************************************************************************/
#define ETM_PWM_HIGHTRUEPULSE        1            /*!< 高真脉冲 */
#define ETM_PWM_LOWTRUEPULSE         2            /*!< 低真脉冲 */
/*! @}                                                                        */

/******************************************************************************
* ETM 同步触发源定义
*
*//*!  
* @{
*******************************************************************************/
#define ETM_SYNC_TRIGGER_SOFTWARE    1        /*!< 软件同步 */
#define ETM_SYNC_TRIGGER_TRIGGER2    2        /*!< 硬件触发2同步, SIM_SOPT[ETMSYNC] */
#define ETM_SYNC_TRIGGER_TRIGGER1    3        /*!< 硬件触发1同步, ETM0CH0 */
#define ETM_SYNC_TRIGGER_TRIGGER0    4        /*!< 硬件触发0同步, ACMP0 */
/*! @}                                                                        */

/******************************************************************************
* ETM 软件输出控制值
*
*//*!  
* @{
*******************************************************************************/ 
#define ETM_SWOCTRL_HIGH    1                /*!< 软件输出高电平 */
#define ETM_SWOCTRL_LOW     0                /*!< 软件输出低电平 */
/*! @}                                                                        */

/******************************************************************************
* ETM  通道极性设置
*
*//*! 
* @{
*******************************************************************************/
#define ETM_POLARITY_HIGHACTIVE     0        /*!< 通道极性高电平有效 */
#define ETM_POLARITY_LOWACTIVE      1        /*!< 通道极性低电平有效 */
/*! @}                                                                        */


/******************************************************************************
******************************************************************************/
/*! @brief ETM_CALLBACK ETM回调类型定义                                */
typedef void (*ETM_CallbackPtr)(void);
/*! @}                                                                        */

/******************************************************************************
* ETM 参数配置结构体.
*
*//*! 
* @{
*******************************************************************************/
/*!
* @brief ETM 参数配置结构体.
*
*/

typedef struct
{
  uint8_t   clk_source;       /*!< 时钟源 */
  uint8_t   prescaler;        /*!< 时钟分频系数 */
  uint8_t   sc;               /*!< 状态和控制 */
  uint16_t  modulo;           /*!< 计数模值 */
  uint16_t  cnt;              /*!< 计数值 */
  uint16_t  cntin;            /*!< 计数初始值 */
  uint8_t   mode;             /*!< 特性模式选择 */
  uint8_t   sync;             /*!< 同步模式 */
  uint8_t   outinit;          /*!< 通道输出初始配置  */
  uint8_t   outmask;          /*!< 输出屏蔽 */
  uint32_t  combine;          /*!< 通道联合 */
  uint16_t  deadETMe;         /*!< 死区时间插入控制 */
  uint8_t   exttrig;          /*!< 外部触发 */
  uint8_t   pol;              /*!< 通道极性 */
  uint16_t  filter;           /*!< 输入滤波控制 */
  uint8_t   fms;              /*!< 故障模式状态 */
  uint16_t  fltctrl;          /*!< 故障控制 */
  uint8_t   fltpol;           /*!< 故障输入极性 */
  uint16_t  conf;             /*!< ETM配置 */
  uint32_t  synconf;          /*!< 同步配置 */
  uint8_t   invctrl;          /*!< 反相控制 */
  uint16_t  swoctrl;          /*!< 软件输出控制 */
  uint16_t  pwmload;          /*!< PWM装载 */
} ETM_ConfigType, *ETM_ConfigPtr;
/*! @}                                                                       */

/******************************************************************************
* ETM 通道配置结构体.
*
*//*!
* @{
*******************************************************************************/
/*!
* @brief ETM 通道配置结构体.
*
*/
typedef struct
{
  uint8_t         u8CnSC;                  /*!< ETM 通道状态和控制 */
  uint16_t        u16CnV;                  /*!< ETM 通道值控制 */
  union
  {
    uint32_t      u32dw;
    struct 
    {
      uint32_t    bMode         : 3;        /*!< ETM模式选择: GPIO, 输入捕获, 输出比较, 边沿PWM, 中央对齐PWM,
                                             * 联合PWM, 双边沿捕获 
                                             */
      uint32_t    bEdge         : 2;        /*!< 边沿选择 */
      uint32_t    bOutCmp       : 2;        /*!< 翻转, 清零, 置位 */
      uint32_t    bPWMPol       : 1;        /*!< 高真脉冲, 低真脉冲 */
      uint32_t    bDualCapMode  : 1;        /*!< 双边沿捕捉模式: 单次, 连续模式 */
      uint32_t    bCHIE         : 1;        /*!< 使能通道中断 */
    }bits;
  }ctrl;                                    /*!< ETM 通道特性控制 */
} ETM_ChParamsType;

/*! @}                                                                        */

/*******************************************************************************/
/*!
 *  内联函数
 */
/*******************************************************************************/

/*****************************************************************************//*!
*
* @brief  使能ETM定时器溢出中断.
*        
* @param[in]    pETM          指向三个ETM定时器其中一个的基址.
*
* @return none.
*
*****************************************************************************/
__STATIC_INLINE void ETM_EnableOverflowInt(ETM_Type *pETM)
{
    if(pETM->SC & ETM_SC_TOF_MASK)
    {
        pETM->SC &= ~ETM_SC_TOF_MASK;
    }
    pETM->SC |= ETM_SC_TOIE_MASK;
}

/*****************************************************************************//*!
*
* @brief  禁用ETM定时器溢出中断.
*        
* @param[in]    pETM    指向三个ETM定时器其中一个的基址.
*
* @return none.
*
*****************************************************************************/
__STATIC_INLINE void ETM_DisableOverflowInt(ETM_Type *pETM)
{
    pETM->SC &= ~ETM_SC_TOIE_MASK;
}

/*****************************************************************************//*!
*
* @brief  使能通道中断.
*        
* @param[in]    pETM            指向三个ETM定时器其中一个的基址.
* @param[in]    u8ETM_Channel   通道号.
*
* @return none.
*
*****************************************************************************/
__STATIC_INLINE void ETM_EnableChannelInt(ETM_Type *pETM, uint8_t u8ETM_Channel)
{
    pETM->CONTROLS[u8ETM_Channel].CnSC |= ETM_CnSC_CHIE_MASK;
}

/*****************************************************************************//*!
*
* @brief  禁止通道中断.
*        
* @param[in]    pETM            指向三个ETM定时器其中一个的基址.
* @param[in]    u8ETM_Channel   通道号.
*
* @return none.
*
*****************************************************************************/
__STATIC_INLINE void ETM_DisableChannelInt(ETM_Type *pETM, uint8_t u8ETM_Channel)
{
    pETM->CONTROLS[u8ETM_Channel].CnSC &= ~ETM_CnSC_CHIE_MASK;
}

/*****************************************************************************//*!
*
* @brief  获取溢出标志位.
*        
* @param[in]    pETM           指向三个ETM定时器其中一个的基址.
*    
* @return none.
*
*****************************************************************************/
__STATIC_INLINE uint8_t ETM_GetOverFlowFlag(ETM_Type *pETM)
{
    return (pETM->SC & ETM_SC_TOF_MASK);
}

/*****************************************************************************//*!
*
* @brief  清除溢出标志位.
*        
* @param[in]    pETM           指向三个ETM定时器其中一个的基址.
*    
* @return none.
*
*****************************************************************************/
__STATIC_INLINE void ETM_ClrOverFlowFlag(ETM_Type *pETM)
{
    if(pETM->SC & ETM_SC_TOF_MASK)
    {
         pETM->SC &= ~ETM_SC_TOF_MASK;
    }
}

/*****************************************************************************//*!
*
* @brief  获取通道事件标志位.
*        
* @param[in]    pETM            指向三个ETM定时器其中一个的基址.
* @param[in]    u8ETM_Channel   通道号.
*
* @return none.
*
*****************************************************************************/
__STATIC_INLINE uint8_t ETM_GetChannelFlag(ETM_Type *pETM, uint8_t u8ETM_Channel)
{
    return (pETM->CONTROLS[u8ETM_Channel].CnSC & ETM_CnSC_CHF_MASK);
}

/*****************************************************************************//*!
*
* @brief  清除通道事件标志位.
*        
* @param[in]    pETM           指向三个ETM定时器其中一个的基址.
*    
* @return none.
*
*****************************************************************************/
__STATIC_INLINE void ETM_ClrChannelFlag(ETM_Type *pETM, uint8_t u8ETM_Channel)
{
    pETM->CONTROLS[u8ETM_Channel].CnSC &= ~ETM_CnSC_CHF_MASK;
}

/*********************************************************************************//*!
*
* @brief 使能写保护功能.被写保护功能位不可写入(ETM2). 
*        
* @param[in]    pETM             ETM2.
*
* @return none.
*
*********************************************************************************/
__STATIC_INLINE void ETM_WriteProtectionEnable(ETM_Type *pETM)
{
    pETM->FMS |= ETM_FMS_WPEN_MASK;
}

/*********************************************************************************//*!
*
* @brief 禁用写保护位.被写保护功能位可写(ETM2). 
*        
* @param[in]    pETM              ETM2.
*
* @return none.
*
*********************************************************************************/
__STATIC_INLINE void ETM_WriteProtectionDisable(ETM_Type *pETM)
{
    if (pETM->FMS & ETM_FMS_WPEN_MASK)
    {
        pETM->MODE |= ETM_MODE_WPDIS_MASK;
    }
}

/*****************************************************************************//*!
*
* @brief  置位 ETMEN 去使能ETM的一些特殊功能寄存器(ETM2).
*        
* @param[in]    pETM             ETM2.
*    
* @return none.
*
*****************************************************************************/
__STATIC_INLINE void ETM_SetETMEnhanced(ETM_Type *pETM)
{
    if(pETM->MODE & ETM_MODE_WPDIS_MASK)   /* 前提是没有进行写保护 */
    {
        pETM->MODE |= ETM_MODE_ETMEN_MASK;
    }
    else
    {
        ETM_WriteProtectionDisable(pETM);
        pETM->MODE |= ETM_MODE_ETMEN_MASK;
        ETM_WriteProtectionEnable(pETM);
    }    
}

/*****************************************************************************//*!
*
* @brief  清除 ETMEN 去禁用一些特殊功能寄存器, 只有一些基础模块可以使用(ETM2).       
* @param[in]    pETM           ETM2.
*    
* @return none.
*
*****************************************************************************/
__STATIC_INLINE void ETM_SetETMBasic(ETM_Type *pETM)
{
    if(pETM->MODE & ETM_MODE_WPDIS_MASK)    /* 前提是要没有进行写保护 */
    {
        pETM->MODE &= ~ETM_MODE_ETMEN_MASK;
    }
    else
    {
        ETM_WriteProtectionDisable(pETM);
        pETM->MODE &= ~ETM_MODE_ETMEN_MASK;
        ETM_WriteProtectionEnable(pETM);
    }  
}

/*****************************************************************************//*!
*
* @brief  设置 ETM 模值(ETM2).
*              
* @param[in]    pETM           (ETM2).
* @param[in]    u16ModValue    需要设置的16位模值.
*
* @return none.
*
*****************************************************************************/
__STATIC_INLINE void ETM_SetModValue(ETM_Type *pETM, uint16_t u16ModValue)
{
    pETM->CNT = 0;
    pETM->MOD = u16ModValue;
    if(ETM2 == pETM)
    {
        if(pETM->MODE & ETM_MODE_ETMEN_MASK)
        {
            pETM->PWMLOAD |= ETM_PWMLOAD_LDOK_MASK;
        }
        else
        {
        }
    }
    else
    {
    }
}

/*****************************************************************************//*!
*
* @brief  设置 ETM 通道值(ETM2).
*                
* @param[in]    pETM               ETM2.
* @param[in]    u16ChannelValue    需要设置的16位通道值.
* @param[in]    u8ETM_Channel      通道号.
*
* @return none.
*
*****************************************************************************/
__STATIC_INLINE void ETM_SetChannelValue(ETM_Type *pETM, uint8_t u8ETM_Channel, uint16_t u16ChannelValue)
{
    pETM->CONTROLS[u8ETM_Channel].CnV = u16ChannelValue;
    if(ETM2 == pETM)
    {
        if(pETM->MODE & ETM_MODE_ETMEN_MASK)
        {
            if(u8ETM_Channel < 2)
            {
                pETM->COMBINE |= ETM_COMBINE_SYNCEN0_MASK; 
            }
            else if (u8ETM_Channel < 4)
            {
                pETM->COMBINE |= ETM_COMBINE_SYNCEN1_MASK;
            }
            else
            {
                pETM->COMBINE |= ETM_COMBINE_SYNCEN2_MASK;
            }
            pETM->PWMLOAD |= ETM_PWMLOAD_LDOK_MASK;  
        }
        else
        {
        }
    }
    else
    {
    }
}

/*****************************************************************************//*!
*
* @brief  设置ETM的计数初始值(ETM2).
*               
* @param[in]    pETM               ETM2.
* @param[in]    u16CounterValue    需要设置的16位计数初始值.
*
* @return none.
*
*****************************************************************************/
__STATIC_INLINE void ETM_SetCounterInitValue(ETM_Type *pETM, uint16_t u16CounterValue)
{
    pETM->CNTIN = u16CounterValue;
    if(pETM->MODE & ETM_MODE_ETMEN_MASK)
    {
        pETM->PWMLOAD |= ETM_PWMLOAD_LDOK_MASK;
    }
    else
    {
    }
}

/*****************************************************************************//*!
*
* @brief  设置输出屏蔽寄存器的值(ETM2).
*               
* @param[in]    pETM            ETM2.
* @param[in]    u16ChMask       屏蔽的通道值（6位，对应ETM2的6个通道）.
*
* @return none.
*
*****************************************************************************/
__STATIC_INLINE void ETM_MaskChannels(ETM_Type *pETM, uint16_t u16ChMask)
{
     pETM->OUTMASK |= u16ChMask;
}

/*****************************************************************************//*!
*
* @brief  清除输出屏蔽寄存器的值(ETM2).
*               
* @param[in]    pETM            ETM2.
* @param[in]    u16ChMask       所要清除屏蔽的通道值（6位，对应ETM2的6个通道）.
*
* @return none.
*
*****************************************************************************/
__STATIC_INLINE void ETM_UnMaskChannels(ETM_Type *pETM, uint16_t u16ChMask)
{
     pETM->OUTMASK &= ~u16ChMask;
}

/*********************************************************************************//*!
*
* @brief 设置 ETM 通道极性(ETM2).
*        
* @param[in]    pETM                 ETM2.
* @param[in]    u8ChsPolValue        所要设置的通道极性值，6位，对应ETM2的6个通道.
*                                    0为高电平有效，1为低电平有效
*
* @return none.
*
*********************************************************************************/
__STATIC_INLINE void ETM_SetChannelsPolarity(ETM_Type *pETM, uint8_t u8ChsPolValue)
{
    pETM->POL = u8ChsPolValue;
}

/*********************************************************************************//*!
*
* @brief 获取 ETM 的通道极性值(ETM2).
*        
* @param[in]    pETM                  ETM2.
*
* @return 通道极性值.
*
*********************************************************************************/
__STATIC_INLINE uint8_t ETM_GetChannelsPolarity(ETM_Type *pETM)
{
    return (pETM->POL);
}

/*********************************************************************************//*!
*
* @brief 设置增强PWM同步(ETM2).
*        
* @param[in]    pETM                 ETM2.
* 
* @return none.
*
*********************************************************************************/
__STATIC_INLINE void ETM_EnableEnhancedSYNCMode(ETM_Type *pETM)
{
    pETM->SYNCONF   |= ETM_SYNCONF_SYNCMODE_MASK;   
}

/*********************************************************************************//*!
*
* @brief 设置传统PWM同步(ETM2).
*        
* @param[in]    pETM              ETM2.
*
* @return none.
*
*********************************************************************************/
__STATIC_INLINE void ETM_DisableEnhancedSYNCMode(ETM_Type *pETM)
{
    pETM->SYNCONF   &= ~ETM_SYNCONF_SYNCMODE_MASK;   
}

/*********************************************************************************//*!
*
* @brief 设置通道外部触发(ETM2).
*        
* @param[in]    pETM               ETM2.
* @param[in]    u8TirggerSource    配置0-5这6个通道的触发
*                                  0：禁止通道触发生产；1：使能通道触发生产
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*********************************************************************************/
__STATIC_INLINE void ETM_SetExternalTrigger(ETM_Type *pETM, uint8_t u8TirggerSource)
{
    pETM->EXTTRIG   = u8TirggerSource;
}

/*********************************************************************************//*!
*
* @brief 获取外部触发标志.
*        
* @param[in]    pETM              ETM2.
*
* @return 通道触发标志.
*
*********************************************************************************/
__STATIC_INLINE uint8_t ETM_GetExternalTriggerFlag(ETM_Type *pETM)
{
    return (pETM->EXTTRIG & ETM_EXTTRIG_TRIGF_MASK);
}

/*********************************************************************************//*!
*
* @brief 设置加载使能位(ETM2).
*        
* @param[in]    pETM              ETM2.
*
* @return none.
*
*********************************************************************************/
__STATIC_INLINE void ETM_SetLoadEnable(ETM_Type *pETM)
{
    pETM->PWMLOAD |= ETM_PWMLOAD_LDOK_MASK;
}

/*********************************************************************************//*!
*
* @brief 设置匹配过程中包括的通道.
*        
* @param[in]    pETM               ETM2.
* @param[in]    u8Matchchannel     匹配过程中所包括的通道.
*
* @return none.
*
*********************************************************************************/
__STATIC_INLINE void ETM_SetLoadMatchChannel(ETM_Type *pETM, uint8_t u8Matchchannel)
{
    pETM->PWMLOAD |= u8Matchchannel;
}

/*********************************************************************************//*!
*
* @brief 禁用通道输入滤波器(ETM2).
*        
* @param[in]    pETM              ETM2.
* @param[in]    u8ETM_Channel     通道号（只有通道0-通道3包含）.
*
* @return none.
*
*********************************************************************************/
__STATIC_INLINE void ETM_InputCaptureFilterClr(ETM_Type *pETM, uint8_t u8ETM_Channel)
{
    pETM->FILTER &= ~(0x000F << (u8ETM_Channel << 2));
}

/*********************************************************************************//*!
*
* @brief 使能通道滤波器(ETM2).
*        
* @param[in]    pETM              ETM2.
* @param[in]    u8ETM_Channel     通道号（只有通道0-通道3包含）.
* @param[in]    u8FilterValue     滤波周期值:1~15, 0: 禁用通道滤波器.
*
* @return none.
*
*********************************************************************************/
__STATIC_INLINE void ETM_InputCaptureFilterSet(ETM_Type *pETM, uint8_t u8ETM_Channel, uint8_t u8FilterValue)
{
    if (u8FilterValue)
    {
        pETM->FILTER |= (u8FilterValue << (u8ETM_Channel << 2));
    }
    else
    {
        ETM_InputCaptureFilterClr(pETM, u8ETM_Channel);
    }
}


/*********************************************************************************//*!
*
* @brief 使能故障输入(ETM2).
*        
* @param[in]    pETM              ETM2.
* @param[in]    u8FaultPin        故障输入通道号: 0~3.
*
* @return none.
*
*********************************************************************************/
__STATIC_INLINE void ETM_FaultPinEnable(ETM_Type *pETM, uint8_t u8FaultPin)
{
    if (pETM->MODE & ETM_MODE_WPDIS_MASK) 
    {
        pETM->FLTCTRL |= (1 << u8FaultPin);
    }
    else                                 
    {
        ETM_WriteProtectionDisable(pETM);
        pETM->FLTCTRL |= (1 << u8FaultPin);
        ETM_WriteProtectionEnable(pETM);
    }
}

/*********************************************************************************//*!
*
* @brief 禁用故障输入(ETM2).
*        
* @param[in]    pETM              ETM2.
* @param[in]    u8FaultPin        故障输入通道号: 0~3.
*
* @return none.
*
*********************************************************************************/
__STATIC_INLINE void ETM_FaultPinDisable(ETM_Type *pETM, uint8_t u8FaultPin)
{
    if (pETM->MODE & ETM_MODE_WPDIS_MASK) 
    {
        pETM->FLTCTRL &= ~(1 << u8FaultPin);
    }
    else                              
    {
        ETM_WriteProtectionDisable(pETM);
        pETM->FLTCTRL &= ~(1 << u8FaultPin);
        ETM_WriteProtectionEnable(pETM);
    }
}

/*********************************************************************************//*!
*
* @brief 使能故障输入滤波器(ETM2).
*        
* @param[in]    pETM              ETM2.
* @param[in]    u8FaultPin        故障输入通道号: 0~3.
*
* @return none.
*
*********************************************************************************/
__STATIC_INLINE void ETM_FaultPinFilterEnable(ETM_Type *pETM, uint8_t u8FaultPin)
{
    if (pETM->MODE & ETM_MODE_WPDIS_MASK) 
    {
        pETM->FLTCTRL |= (0x10 << u8FaultPin);
    }
    else                               
    {
        ETM_WriteProtectionDisable(pETM);
        pETM->FLTCTRL |= (0x10 << u8FaultPin);
        ETM_WriteProtectionEnable(pETM);
    }
}

/*********************************************************************************//*!
*
* @brief 禁用故障输入滤波器(ETM2).
*        
* @param[in]    pETM              ETM2.
* @param[in]    u8FaultPin        故障输入通道号: 0~3.
*
* @return none.
*
*********************************************************************************/
__STATIC_INLINE void ETM_FaultPinFilterDisable(ETM_Type *pETM, uint8_t u8FaultPin)
{
    if (pETM->MODE & ETM_MODE_WPDIS_MASK) 
    {
        pETM->FLTCTRL &= ~(0x10 << u8FaultPin);
    }
    else                           
    {
        ETM_WriteProtectionDisable(pETM);
        pETM->FLTCTRL &= ~(0x10 << u8FaultPin);
        ETM_WriteProtectionEnable(pETM);
    }
}

/*********************************************************************************//*!
*
* @brief 禁用所有的故障输入滤波器(ETM2). 
*        
* @param[in]    pETM              ETM2.
*
* @return none.
*
*********************************************************************************/
__STATIC_INLINE void ETM_FaultPinFilterCDisableAll(ETM_Type *pETM)
{
    pETM->FLTCTRL &= ~ETM_FLTCTRL_FFVAL_MASK;
}

/*********************************************************************************//*!
*
* @brief 设置故障输入滤波器值. 所有的故障通道都为这个值(ETM2).
*        
* @param[in]    pETM              ETM2.
* @param[in]    u8FilterValue     故障输入滤波器值: 1~15, 0 禁用滤波器.
*
* @return none.
*
*********************************************************************************/
__STATIC_INLINE void ETM_FaultPinFilterSet(ETM_Type *pETM, uint8_t u8FilterValue)
{
    if (u8FilterValue)
    {
        pETM->FLTCTRL |= ETM_FLTCTRL_FFVAL(u8FilterValue);
    }
    else
    {
        ETM_FaultPinFilterCDisableAll(pETM);
    }
}

/*********************************************************************************//*!
*
* @brief 获取所有通道故障检测标志(ETM2)
*        
* @param[in]    pETM               ETM2.
*
* @return none.
*
*********************************************************************************/
__STATIC_INLINE uint8_t ETM_GetFaultDetectionLogicORFlag(ETM_Type *pETM)
{
    return (pETM->FMS & ETM_FMS_FAULTF_MASK);
}

/*********************************************************************************//*!
*
* @brief 获取预期通道故障检测标志(ETM2)
*        
* @param[in]    pETM              ETM2.
* @param[in]    u8FaultPin        故障输入通道号: 0~3.
*
* @return none.
*
*********************************************************************************/
__STATIC_INLINE uint8_t ETM_GetFaultDetectionFlag(ETM_Type *pETM, uint8_t u8FaultPin)
{
    return (pETM->FMS & (1 << u8FaultPin));
}

/*********************************************************************************//*!
*
* @brief 获取“或”逻辑的故障输入(ETM2)
*        
* @param[in]    pETM              ETM2.
*
* @return none.
*
*********************************************************************************/
__STATIC_INLINE uint8_t ETM_GetFaultInputsLogicORValue(ETM_Type *pETM)
{
    return (pETM->FMS & ETM_FMS_FAULTIN_MASK);
}

/*! @}                                                                        */

/******************************************************************************
******************************************************************************/

void ETM_ClockSet(ETM_Type *pETM, uint8_t u8ClockSource, uint8_t u8ClockPrescale);
void ETM_PWMInit(ETM_Type *pETM, uint8_t u8PWMModeSelect, uint8_t u8PWMEdgeSelect);
void ETM_InputCaptureInit(ETM_Type *pETM, uint8_t u8ETM_Channel, uint8_t u8CaptureMode);
void ETM_DualEdgeCaptureInit(ETM_Type *pETM, uint8_t u8ChannelPair, uint8_t u8CaptureMode, 
                             uint8_t u8Channel_N_Edge, uint8_t u8Channel_Np1_Edge);
void ETM_OutputCompareInit(ETM_Type *pETM, uint8_t u8ETM_Channel, uint8_t u8CompareMode);
void ETM_SoftwareSync(ETM_Type *pETM);
void ETM_HardwareSync(ETM_Type *pETM, uint8_t u8TriggerN);
void ETM_HardwareSyncCombine(ETM_Type *pETM, uint8_t u8TriggerMask);
void ETM_GenerateTrig2(ETM_Type *pETM);
void ETM_PWMDeadETMeSet(ETM_Type *pETM, uint8_t u8PrescalerValue, uint8_t u8DeadETMeValue);
void ETM_OutputMaskSet(ETM_Type *pETM, uint8_t u8ETM_Channel);
void ETM_SWOutputControlSet(ETM_Type *pETM, uint8_t u8ETM_Channel, uint8_t u8ChannelValue);
void ETM_SetDebugModeBehavior(ETM_Type *pETM, uint8_t u8DebugMode);
void ETM_SetTOFFrequency(ETM_Type *pETM, uint8_t u8TOFNUM);
void ETM_PolaritySet(ETM_Type *pETM, uint8_t u8ETM_Channel, uint8_t u8ActiveValue);
void ETM_InvertChannel(ETM_Type *pETM, uint8_t u8ChannelPair);
void ETM_Init(ETM_Type *pETM, ETM_ConfigType *pConfig);
void ETM_DeInit(ETM_Type *pETM);
void ETM_ChannelInit(ETM_Type *pETM, uint8_t u8ETM_Channel, ETM_ChParamsType *pETM_ChParams);
void ETM_SetDutyCycleCombine(ETM_Type *pETM, uint8_t u8ETM_Channel, uint8_t u8DutyCycle);
void ETM_SetCallback(ETM_Type *pETM, ETM_CallbackPtr pfnCallback);
void  ETM_SyncConfigActivate(ETM_Type *pETM, uint32_t u32ConfigValue);
void ETM_SyncConfigDeactivate(ETM_Type * pETM, uint32_t u32ConfigValue);
uint8_t ETM_GetFaultDetectionLogicORFlag(ETM_Type *pETM);
uint8_t ETM_GetFaultDetectionFlag(ETM_Type *pETM, uint8_t u8FaultPin);
uint8_t ETM_GetFaultInputsLogicORValue(ETM_Type *pETM);
void ETM_WriteProtectionEnable(ETM_Type *pETM);
void ETM_WriteProtectionDisable(ETM_Type *pETM);
void ETM_FaultPinFilterCDisableAll(ETM_Type *pETM);
void ETM_FaultPinFilterSet(ETM_Type *pETM, uint8_t u8FilterValue);
void ETM_FaultPinFilterDisable(ETM_Type *pETM, uint8_t u8FaultPin);
void ETM_FaultPinFilterEnable(ETM_Type *pETM, uint8_t u8FaultPin);
void ETM_FaultPinEnable(ETM_Type *pETM, uint8_t u8FaultPin);
void ETM_FaultPinDisable(ETM_Type *pETM, uint8_t u8FaultPin);
void ETM_InputCaptureFilterClr(ETM_Type *pETM, uint8_t u8ETM_Channel);
void ETM_InputCaptureFilterSet(ETM_Type *pETM, uint8_t u8ETM_Channel, uint8_t u8FilterValue);
void ETM_SetLoadMatchChannel(ETM_Type *pETM, uint8_t u8Matchchannel);
void ETM_SetLoadEnable(ETM_Type *pETM);
uint8_t ETM_GetExternalTriggerFlag(ETM_Type *pETM);
void ETM_DisableEnhancedSYNCMode(ETM_Type *pETM);
void ETM_EnableEnhancedSYNCMode(ETM_Type *pETM);
uint8_t ETM_GetChannelsPolarity(ETM_Type *pETM);
void ETM_SetChannelsPolarity(ETM_Type *pETM, uint8_t u8ChsPolValue);
void ETM_UnMaskChannels(ETM_Type *pETM, uint16_t u16ChMask);
void ETM_MaskChannels(ETM_Type *pETM, uint16_t u16ChMask);
void ETM_SetCounterInitValue(ETM_Type *pETM, uint16_t u16CounterValue);
void ETM_SetChannelValue(ETM_Type *pETM, uint8_t u8ETM_Channel, uint16_t u16ChannelValue);
void ETM_SetModValue(ETM_Type *pETM, uint16_t u16ModValue);
void ETM_SetETMBasic(ETM_Type *pETM);
void ETM_SetETMEnhanced(ETM_Type *pETM);
void ETM_ClrChannelFlag(ETM_Type *pETM, uint8_t u8ETM_Channel);
uint8_t ETM_GetChannelFlag(ETM_Type *pETM, uint8_t u8ETM_Channel);
void ETM_ClrOverFlowFlag(ETM_Type *pETM);
uint8_t ETM_GetOverFlowFlag(ETM_Type *pETM);
void ETM_DisableChannelInt(ETM_Type *pETM, uint8_t u8ETM_Channel);
void ETM_EnableChannelInt(ETM_Type *pETM, uint8_t u8ETM_Channel);
void ETM_DisableOverflowInt(ETM_Type *pETM);
void ETM_EnableOverflowInt(ETM_Type *pETM);
void ETM_disblechannel(ETM_Type *pETM, uint8_t u8ETM_Channel);

#ifdef __cplusplus
}
#endif
#endif /* ETM_H_ */
