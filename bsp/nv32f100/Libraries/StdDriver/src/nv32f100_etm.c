/*****************************************************************************!     
 *     技术讨论：QQ群  123763203
 *     官网    ：www.navota.com
 *
 * @file       etm.c
 * @brief      etm定时器函数库
 * @author     Navota
 * @date       2017-1-1
 ***************************************************************************/

#include "nv32f100.h"


/*!
 * @brief 存放回调入口
 *
 */
ETM_CallbackPtr ETM_Callback[3] = {(ETM_CallbackPtr)NULL};


/******************************************************************************
* 定义ETM的接口函数
*******************************************************************************/

/*******************************************************************************//*!
*
* @brief 设置ETM模块时钟资源及分频系数.
*        
* @param[in]    pETM                  指向三个ETM定时器其中一个的基址.
* @param[in]    ClockSource           ETM 选择的时钟源 ： 禁用（00）、系统时钟（01）、固定频率时钟（10）、外接时钟（11）.
* @param[in]    ClockPrescale         分频系数.
*
* @return none.
*
*********************************************************************************/
void ETM_ClockSet(ETM_Type *pETM, uint8_t u8ClockSource, uint8_t u8ClockPrescale)
{
    uint8_t   u8Temp;
    u8Temp  = (pETM->SC & 0xE0);//pETM指向的SC寄存器低5位清0，即未选择时钟，时钟输入采取1分频
    u8Temp |= (ETM_SC_CLKS(u8ClockSource & 0x3) | ETM_SC_PS(u8ClockPrescale & 0x7));
    pETM->SC = u8Temp;//配置该ETM的状态与控制寄存器ETMx_SC
}

/*********************************************************************************//*!
*
* @brief  ETM中PWM的初始化函数 
*        
* @param[in]    pETM                  指向三个ETM定时器其中一个的基址.
* @param[in]    PWMModeSelect         居中对齐CPWM（10）、边沿对齐EPWM（01）以及级联模式PWM（11）.
* @param[in]    PWMEdgeSelect         高真脉冲（01）、低真脉冲（10）.
*
* @return none.
*
*********************************************************************************/
void ETM_PWMInit(ETM_Type *pETM, uint8_t u8PWMModeSelect, uint8_t u8PWMEdgeSelect)
{
    uint8_t   channels, i;
    
    ASSERT((ETM0== pETM) || (ETM1== pETM) || (ETM2== pETM));//断言来检测ETM通道是否正确
    
    /* 选用ETM时钟 */
	if (ETM0 == pETM)
    {
        channels = 2;
        SIM->SCGC |= SIM_SCGC_ETM0_MASK; //ETM0共有两个通道
    }
    else if(ETM1 == pETM) 
    {
        channels = 2;
        SIM->SCGC |= SIM_SCGC_ETM1_MASK;  //ETM1共有两个通道
    }        
    else
    {
        channels = 6;
        SIM->SCGC  |= SIM_SCGC_ETM2_MASK; //ETM2共有六个通道
    }
    
    pETM->SC  = 0x0;                                   //关闭计数器
	pETM->MOD = ETM_MOD_INIT; 
    
    if(ETM_PWMMODE_CENTERALLIGNED == u8PWMModeSelect)   //打开CPWM
    {
        pETM->SC |= ETM_SC_CPWMS_MASK; 
    }
    else if(ETM_PWMMODE_COMBINE == u8PWMModeSelect)    
    {
        ASSERT(ETM2 == pETM);
        pETM->MODE    |= ETM_MODE_WPDIS_MASK | ETM_MODE_ETMEN_MASK;
        pETM->COMBINE = ETM_COMBINE_COMBINE0_MASK | ETM_COMBINE_COMP0_MASK | ETM_COMBINE_SYNCEN0_MASK | ETM_COMBINE_DTEN0_MASK |
                        ETM_COMBINE_COMBINE1_MASK | ETM_COMBINE_COMP1_MASK | ETM_COMBINE_SYNCEN1_MASK | ETM_COMBINE_DTEN1_MASK |
                        ETM_COMBINE_COMBINE2_MASK | ETM_COMBINE_COMP2_MASK | ETM_COMBINE_SYNCEN2_MASK | ETM_COMBINE_DTEN2_MASK 
                        ;    // 打开通道级联模式 
        pETM->SC &= ~ETM_SC_CPWMS_MASK; 
    }
    if(ETM_PWM_HIGHTRUEPULSE == u8PWMEdgeSelect)
    {
      /* 配置通道寄存器，设置通道状态及通道计数值 */
        for(i=0; i<channels; i++)
        {
            pETM->CONTROLS[i].CnSC = ETM_CnSC_MSB_MASK | ETM_CnSC_ELSB_MASK;  
            pETM->CONTROLS[i].CnV  = ETM_C0V_INIT + i*100; 
        }
    }
    else if(ETM_PWM_LOWTRUEPULSE == u8PWMEdgeSelect)
    {
        for(i=0; i<channels; i++) 
        {
            pETM->CONTROLS[i].CnSC = ETM_CnSC_MSB_MASK | ETM_CnSC_ELSA_MASK; 
            pETM->CONTROLS[i].CnV  = ETM_C0V_INIT + i*100 ; 
        }
    }  
}

/*********************************************************************************//*!
*
* @brief  禁用ETM的通道功能，用于GPIO或其他功能 
*        
* @param[in]    pETM                  指向三个ETM定时器其中一个的基址.
* @param[in]    u8ETM_Channel         通道号.
*
* @return none.
*
*********************************************************************************/

void ETM_disblechannel(ETM_Type *pETM, uint8_t u8ETM_Channel)
{    
     uint8_t   i;
     i= u8ETM_Channel;
     pETM->CONTROLS[i].CnSC &= ~ (ETM_CnSC_ELSB_MASK| ETM_CnSC_ELSA_MASK); 


}

/*********************************************************************************//*!
*
* @brief 输入捕捉初始化函数.
*        
* @param[in]    pETM                  指向三个ETM定时器其中一个的基址.
* @param[in]    Channel               配置通道号.
* @param[in]    CaptureMode           选择捕捉方式:上升沿, 下降沿或跳变沿.
*
* @return none.
*
*********************************************************************************/
void ETM_InputCaptureInit(ETM_Type *pETM, uint8_t u8ETM_Channel, uint8_t u8CaptureMode)
{ 
    ASSERT(((ETM0 == pETM) && (u8ETM_Channel < 2))   || 
           ((ETM1 == pETM) && (u8ETM_Channel < 2))   || 
           ((ETM2 == pETM) && (u8ETM_Channel < 6))
           );

    
      /* 选用ETM时钟 */
	if ((ETM0 == pETM) && (u8ETM_Channel < 2))
    {
        SIM->SCGC |= SIM_SCGC_ETM0_MASK;
        NVIC_EnableIRQ(ETM0_IRQn);
    }
    else if((ETM1 == pETM)  && (u8ETM_Channel < 2))
    {
        SIM->SCGC |= SIM_SCGC_ETM1_MASK;
        NVIC_EnableIRQ(ETM1_IRQn);
    }        
    else 
    {
        SIM->SCGC |= SIM_SCGC_ETM2_MASK;
        NVIC_EnableIRQ(ETM2_IRQn);
    }
    
    pETM->SC  = 0x0;     //关闭计数器 
    pETM->MOD = 0xFFFF;  
    
    if(ETM_INPUTCAPTURE_RISINGEDGE == u8CaptureMode)        //开启中断，捕获上升沿
    {
        pETM->CONTROLS[u8ETM_Channel].CnSC = ETM_CnSC_CHIE_MASK | ETM_CnSC_ELSA_MASK;
    }
    else if(ETM_INPUTCAPTURE_FALLINGEDGE == u8CaptureMode)  //捕获下降沿
    {
        pETM->CONTROLS[u8ETM_Channel].CnSC = ETM_CnSC_CHIE_MASK | ETM_CnSC_ELSB_MASK;
    }
    else if(ETM_INPUTCAPTURE_BOTHEDGE == u8CaptureMode)     //捕获跳变沿
    {
        pETM->CONTROLS[u8ETM_Channel].CnSC = ETM_CnSC_CHIE_MASK | ETM_CnSC_ELSA_MASK | ETM_CnSC_ELSB_MASK;       
    }
}

/*********************************************************************************//*!
*
* @brief  对ETM配置双边捕获模式来测量一个脉冲的宽度或周期(ETM2).
*        
* @param[in]    pETM                  ETM2.
* @param[in]    ChannelPair           频道配对数的配置为: 0, 2, 4.
* @param[in]    CaptureMode           选择单周期捕捉（4），和连续捕捉方式（5）.
* @param[in]    Channel_N_Edge        频道N边沿检测：无（0），上升沿（1）下降沿（2）双沿（3）. 
* @param[in]    Channel_Np1_Edge      频道N+1边沿检测.
*
* @return none.
*
*********************************************************************************/
void ETM_DualEdgeCaptureInit(ETM_Type *pETM, uint8_t u8ChannelPair, uint8_t u8CaptureMode, 
                                 uint8_t u8Channel_N_Edge, uint8_t u8Channel_Np1_Edge)
{ 
    ASSERT((ETM2 == pETM)  && (u8ChannelPair < 6) && !(u8ChannelPair & 1) );
    
    SIM->SCGC |= SIM_SCGC_ETM2_MASK;
    if((0 == u8ChannelPair) || (2== u8ChannelPair))
    {
                                      
    }
       
    pETM->SC    = 0x0;                  /* 关闭计数器 */ 
    pETM->MOD   = 0xFFFF;
    pETM->MODE |= ETM_MODE_ETMEN_MASK;  /* ETMEN = 1 */  
    
    pETM->COMBINE |=  ((ETM_COMBINE_DECAPEN0_MASK) << (u8ChannelPair * 4)); 
    
    pETM->CONTROLS[u8ChannelPair].CnSC &= ~ETM_CnSC_CHF_MASK;       /* CH(n)F 和 CH(n+1)F 位必须要先清除 */
    pETM->CONTROLS[u8ChannelPair + 1].CnSC &= ~ETM_CnSC_CHF_MASK;
    
    if(ETM_INPUTCAPTURE_DUALEDGE_ONESHOT == u8CaptureMode)          /* 单次模式 */
    {
        pETM->CONTROLS[u8ChannelPair].CnSC &= ~ETM_CnSC_MSA_MASK;
        pETM->CONTROLS[u8ChannelPair+1].CnSC &= ~ETM_CnSC_MSA_MASK;
    }
    else if(ETM_INPUTCAPTURE_DUALEDGE_CONTINUOUS == u8CaptureMode)  /* 连续模式 */
    {
        pETM->CONTROLS[u8ChannelPair].CnSC |= ETM_CnSC_MSA_MASK;
        pETM->CONTROLS[u8ChannelPair+1].CnSC |= ETM_CnSC_MSA_MASK;
    }
    
    pETM->CONTROLS[u8ChannelPair].CnSC |= (u8Channel_N_Edge << 2);   /* 选择检测边沿 */
    pETM->CONTROLS[u8ChannelPair + 1].CnSC |= (u8Channel_Np1_Edge << 2);   
    
    pETM->COMBINE |=  (ETM_COMBINE_DECAP0_MASK << (u8ChannelPair * 4)); 
}

/*********************************************************************************//*!
*
* @brief 输出对比初始化.
*        
* @param[in]    pETM                  指向三个ETM定时器其中一个的基址.
* @param[in]    Channel               配置通道即通道号.
* @param[in]    CompareMode           选择模式：翻转（01）、置位（11）、清0（10）.
*
* @return none.
*
*********************************************************************************/
void ETM_OutputCompareInit(ETM_Type *pETM, uint8_t u8ETM_Channel, uint8_t u8CompareMode)
{
    ASSERT(((ETM0 == pETM) && (u8ETM_Channel < 2))   || 
           ((ETM1 == pETM) && (u8ETM_Channel < 2))   || 
           ((ETM2 == pETM) && (u8ETM_Channel < 6))
           );
    
    /* 选用ETM模块时钟 */
	if(ETM0 == pETM)
    {
        SIM->SCGC |= SIM_SCGC_ETM0_MASK;
    }
    else if(ETM1 == pETM)
    {
        SIM->SCGC |= SIM_SCGC_ETM1_MASK;
    }        
    else
    {
        SIM->SCGC |= SIM_SCGC_ETM2_MASK;
    }
    
    pETM->SC  = 0x0;                                                                    //关闭计数器
    pETM->MOD = ETM_MOD_INIT; 
    pETM->CONTROLS[u8ETM_Channel].CnSC = (ETM_CnSC_MSA_MASK | (u8CompareMode << 2));   
    pETM->CONTROLS[u8ETM_Channel].CnV  = ETM_C0V_INIT;
}

/*********************************************************************************//*!
*
* @brief 实现软件同步触发（ETM2）.
*        
* @param[in]    pETM                  ETM2.
*
* @return none.
*
*********************************************************************************/
void ETM_SoftwareSync(ETM_Type *pETM)
{
    ASSERT(ETM2 == pETM);

    pETM->SYNCONF   |= ETM_SYNCONF_SYNCMODE_MASK;   
    pETM->SYNC      |= ETM_SYNC_SWSYNC_MASK;
}

/*********************************************************************************//*!
*
* @brief ETM中配置ETMx_SYNC 寄存器来选择硬件触发(ETM2).
*        
* @param[in]    pETM                  ETM2.
* @param[in]    u8TriggerN            选择硬件触发资源.
*
* @return none.
*
*********************************************************************************/
void ETM_HardwareSync(ETM_Type *pETM, uint8_t u8TriggerN)
{
    ASSERT(ETM2 == pETM);
    
    pETM->SYNCONF   |= ETM_SYNCONF_SYNCMODE_MASK;  
    
    switch(u8TriggerN)
    {
        case ETM_SYNC_TRIGGER_TRIGGER2: 
                pETM->SYNC |= ETM_SYNC_TRIG2_MASK;
                break;  
        case ETM_SYNC_TRIGGER_TRIGGER1: 
                pETM->SYNC |= ETM_SYNC_TRIG1_MASK;
                break;     /* 需要先配置ETM0CH0 */
        case ETM_SYNC_TRIGGER_TRIGGER0:
                pETM->SYNC |= ETM_SYNC_TRIG0_MASK; 
                break;     /* 需要先配置ACMP0 */
        default: 
                break;
    }
}

/*********************************************************************************//*!
*
* @brief 通过配置ETM保证硬件同步，产生触发（可有多个触发）(ETM2).
*        
* @param[in]    pETM               ETM2.
* @param[in]    u8TriggerMask      硬件触发资源标志号.联合TRIG0~TREG2.(x000xxxx~x111xxxx)
*
* @return none.
*
*********************************************************************************/
void ETM_HardwareSyncCombine(ETM_Type *pETM, uint8_t u8TriggerMask)
{
    ASSERT(ETM2 == pETM);
    
    pETM->SYNCONF   |= ETM_SYNCONF_SYNCMODE_MASK;   
    pETM->SYNC      &= 0x8F;
    pETM->SYNC      |= (u8TriggerMask & 0x70);
}

/*********************************************************************************//*!
*
* @brief 硬件触发2产生ETM2的PWM同步触发(ETM2)
*        
* @param[in]    pETM              ETM2.
*
* @return none.
*
*********************************************************************************/
void ETM_GenerateTrig2(ETM_Type *pETM)
{
    ASSERT(ETM2 == pETM);
    
    if(pETM->SYNC & ETM_SYNC_TRIG2_MASK)
    {
#if defined(CPU_NV32)
        SIM->SOPT  |= SIM_SOPT_ETMSYNC_MASK;
#endif
    }
}


/*********************************************************************************//*!
*
* @brief ETM死区时间设置（ETM2）.
*        
* @param[in]    pETM                  ETM2.
* @param[in]    PrescalerValue        总线时钟分频值, 0 to 3.
* @param[in]    DeadETMeValue         时钟数值插入, 0 to 63.
*
* @return none.
*
*********************************************************************************/
void ETM_PWMDeadETMeSet(ETM_Type *pETM, uint8_t u8PrescalerValue, uint8_t u8DeadETMeValue)
{
    ASSERT(ETM2 == pETM);
    
    pETM->COMBINE |= 0x101010;              /* 使能死区时间插入 */

    if(!(pETM->MODE & ETM_MODE_WPDIS_MASK)) /* 判断是否使能写保护 */
    {
        pETM->MODE |= ETM_MODE_WPDIS_MASK;  /* 禁止写保护 */
        pETM->DEADETME = (ETM_DEADETME_DTVAL(u8DeadETMeValue & 0x3F) | ETM_DEADETME_DTPS(u8PrescalerValue & 0x3));
        pETM->MODE &= ~ETM_MODE_WPDIS_MASK; /* 使能写保护 */       
    }
    else 
    {
        /* 若无写保护 */
        pETM->DEADETME = (ETM_DEADETME_DTVAL(u8DeadETMeValue & 0x3F) | ETM_DEADETME_DTPS(u8PrescalerValue & 0x3));
    }
    pETM->SYNC |= ETM_SYNC_SWSYNC_MASK;     /* 设置软件同步 */
}    

/*********************************************************************************//*!
*
* @brief 设置输出屏蔽（ETM2）.
*        
* @param[in]    pETM                  ETM2.
* @param[in]    Channel               需要屏蔽的通道号.
*
* @return none.
*
*********************************************************************************/
void ETM_OutputMaskSet(ETM_Type *pETM, uint8_t u8ETM_Channel)
{
    ASSERT((ETM2 == pETM) && (u8ETM_Channel < 6));

    pETM->OUTMASK |= (1 << u8ETM_Channel);
    
    if(pETM->SYNC & ETM_SYNC_SYNCHOM_MASK)              /* 通过PWM同步更新 */
    {
        pETM->SYNCONF |= ETM_SYNCONF_SYNCMODE_MASK;   
        if(pETM->SYNCONF & ETM_SYNCONF_SWOM_MASK)       /* 软件触发激活 */
        {
            pETM->SYNC |= ETM_SYNC_SWSYNC_MASK;
        }
        else if(pETM->SYNCONF & ETM_SYNCONF_HWOM_MASK)  /* 硬件触发激活 */
        {
            pETM->SYNC |= ETM_SYNC_TRIG2_MASK;
            
#if defined(CPU_NV32)
            SIM->SOPT  |= SIM_SOPT_ETMSYNC_MASK;         /* 使能硬件同步 */ 
#endif
        }
        else
        {
        }
    }
    else  /* 若无软件同步, 在系统时钟的上升沿对其更新  */
    {
    }
}

/*********************************************************************************//*!
*
* @brief 配置软件输出控制SWOCTRL寄存器的同步是否由软件触发(ETM2).
*        
* @param[in]    pETM                  ETM2.
* @param[in]    Channel               软件触发PWM波的通道选择.
* @param[in]    ChannelValue          0或1,0不触发;1触发.
*
* @return none.
*
*********************************************************************************/
void ETM_SWOutputControlSet(ETM_Type *pETM, uint8_t u8ETM_Channel, uint8_t u8ChannelValue)
{
    ASSERT((ETM2 == pETM) && (u8ETM_Channel < 6));
    
    if(ETM_SWOCTRL_HIGH == u8ChannelValue)
    {
        pETM->SWOCTRL |= (0x0101 << u8ETM_Channel);
    }
    else if(ETM_SWOCTRL_LOW == u8ChannelValue)
    {
        pETM->SWOCTRL |= (1 << u8ETM_Channel);
        pETM->SWOCTRL &= ~(0x100 << u8ETM_Channel);
    }
    if(pETM->SYNCONF & ETM_SYNCONF_SWOC_MASK)               
    {
        pETM->SYNCONF |= ETM_SYNCONF_SYNCMODE_MASK;        
        if(pETM->SYNCONF & ETM_SYNCONF_SWSOC_MASK)        
        {
            pETM->SYNC |= ETM_SYNC_SWSYNC_MASK;            
        }
        else if(pETM->SYNCONF & ETM_SYNCONF_HWSOC_MASK)     
        {
            pETM->SYNC |= ETM_SYNC_TRIG2_MASK;

#if defined(CPU_NV32)
            SIM->SOPT  |= SIM_SOPT_ETMSYNC_MASK;          
#endif
        }
    }
    else 
    {
    }
}

/*********************************************************************************//*!
*
* @brief 设置通道输出极性(ETM2).
*        
* @param[in]    pETM                  ETM2.
* @param[in]    Channel               PWM波的通道选择.
* @param[in]    ActiveValue           极性的选择，0为高电平，1为低电平.
*
* @return none.
*
*********************************************************************************/
void ETM_PolaritySet(ETM_Type *pETM, uint8_t u8ETM_Channel, uint8_t u8ActiveValue)
{
    ASSERT((ETM2 == pETM) && (u8ETM_Channel < 6));
    
    if(ETM_POLARITY_HIGHACTIVE == u8ActiveValue)
    {
        pETM->POL &=  ~(1 << u8ETM_Channel);
    }
    else if(ETM_POLARITY_LOWACTIVE == u8ActiveValue)
    {
        pETM->POL |=  (1 << u8ETM_Channel);
    }
}

/*********************************************************************************//*!
*
* @brief 设置ETM模块在debug模式下的行为(ETM2).
*        
* @param[in]    pETM             ETM2.
* @param[in]    u8DebugMode      debug 的模式从00-11之间选择.
*
* @return none.
*
*********************************************************************************/
void ETM_SetDebugModeBehavior(ETM_Type *pETM, uint8_t u8DebugMode)
{
    ASSERT((ETM2 == pETM));
    pETM->CONF &= ~ETM_CONF_BDMMODE_MASK;
    pETM->CONF |= ETM_CONF_BDMMODE(u8DebugMode);
}

/*********************************************************************************//*!
*
* @brief ETM中TOF频率大小的设置(ETM2).
*        
* @param[in]    pETM             ETM2.
* @param[in]    u8TOFNUM         TOF频率数，大小0和31之间.
*
* @return none.
*
*********************************************************************************/
void ETM_SetTOFFrequency(ETM_Type *pETM, uint8_t u8TOFNUM)
{
    ASSERT((ETM2 == pETM));
    pETM->CONF &= ~ETM_CONF_NUMTOF_MASK;
    pETM->CONF |= ETM_CONF_NUMTOF(u8TOFNUM);
}

/*********************************************************************************//*!
*
* @brief 交换通道CH（n）和通道CH（n+1）的输出结果(ETM2).
*        
* @param[in]    pETM                  ETM2.
* @param[in]    ChannelPair           要被交换的通道数号，即n可为0,1,2.
*    
* @return none.
*
*********************************************************************************/
void ETM_InvertChannel(ETM_Type *pETM, uint8_t u8ChannelPair)
{
    ASSERT((ETM2 == pETM)  && u8ChannelPair <= 2);

    pETM->INVCTRL |= 1<<u8ChannelPair;
    if(pETM->SYNCONF & ETM_SYNCONF_INVC_MASK)       
    {
        pETM->SYNCONF |= ETM_SYNCONF_SYNCMODE_MASK; 
        if(pETM->SYNCONF & ETM_SYNCONF_SWINVC_MASK)
        {
            pETM->SYNC |= ETM_SYNC_SWSYNC_MASK;    
        }
        else if(pETM->SYNCONF & ETM_SYNCONF_HWINVC_MASK)  
        {
            pETM->SYNC |= ETM_SYNC_TRIG2_MASK;

#if defined(CPU_NV32)
            SIM->SOPT  |= SIM_SOPT_ETMSYNC_MASK;           
  
#endif
        }
    }
    else 
    {
    }
}  

/*****************************************************************************//*!
*
* @brief ETM模块初始化函数.
*        
* @param[in]    pETM        指向三个ETM定时器其中一个的基址.
* @param[in]    pConfig     配置ETM模块的结构体.
*
* @return none.
*
*****************************************************************************/
void ETM_Init(ETM_Type *pETM, ETM_ConfigType *pConfig)
{
    ASSERT((ETM0 == pETM) || (ETM1 == pETM) || (ETM2 == pETM));
    if(ETM0 == pETM)
    {
        SIM->SCGC |= SIM_SCGC_ETM0_MASK;
    }
    else if(ETM1 == pETM)
    {
        SIM->SCGC |= SIM_SCGC_ETM1_MASK;
    }
    else
    {
        SIM->SCGC |= SIM_SCGC_ETM2_MASK;
    }
        
    /*关闭计数器*/
    pETM->SC = 0; 
 	pETM->MODE = pConfig->mode;       
	pETM->MOD = pConfig->modulo;
	pETM->CNT = pConfig->cnt;
        
    if( pETM->MODE & ETM_MODE_ETMEN_MASK  ) 
    {
        /* 当 ETMEN = 1时, 下列寄存器可以写入 */
        pETM->COMBINE   = pConfig->combine;      
        pETM->CNTIN     = pConfig->cntin;      
        pETM->SYNC      = pConfig->sync;      
        pETM->OUTINIT   = pConfig->outinit;      
        pETM->OUTMASK   = pConfig->outmask;      
        pETM->DEADETME  = pConfig->deadETMe;      
        pETM->EXTTRIG   = pConfig->exttrig;      
        pETM->POL       = pConfig->pol;      
        pETM->FMS       = pConfig->fms;      
        pETM->FILTER    = pConfig->filter;      
        pETM->FLTCTRL   = pConfig->fltctrl;    
        pETM->FLTPOL    = pConfig->fltpol;      
        pETM->CONF      = pConfig->conf;      
        pETM->SYNCONF   = pConfig->synconf;      
        pETM->SWOCTRL   = pConfig->swoctrl;      
        pETM->PWMLOAD   = pConfig->pwmload;      
    }
    /* 写入状态控制寄存器来使能时钟*/
    pETM->SC = pConfig->sc;
}


/*****************************************************************************//*!
*
* @brief  复位ETM模块.
*        
* @param[in]    pETM          指向三个ETM定时器其中一个的基址.
*
* @return none.
*
*****************************************************************************/
void ETM_DeInit(ETM_Type *pETM)
{
    ASSERT((ETM0 == pETM) || (ETM1 == pETM) || (ETM2 == pETM));
    pETM->SC = 0;       
	pETM->MOD = 0;
	pETM->CNT = 0;
    if(ETM2 == pETM) 
    {
          pETM->MODE = 0x4; 
          pETM->COMBINE = 0;      
          pETM->CNTIN = 0;      
          pETM->SYNC = 0;      
          pETM->OUTINIT = 0;      
          pETM->OUTMASK = 0;      
          pETM->DEADETME = 0;      
          pETM->EXTTRIG = 0;      
          pETM->POL = 0;      
          pETM->FMS = 0;      
          pETM->FILTER = 0;      
          pETM->FLTCTRL = 0;  
          pETM->FLTPOL = 0;      
          pETM->CONF = 0;      
          pETM->SYNCONF = 0;      
          pETM->SWOCTRL = 0;      
          pETM->PWMLOAD = 0;      
    }
    /* 禁止ETM模块的时钟 */
	if (ETM0 == pETM)
    {
        SIM->SCGC &= ~SIM_SCGC_ETM0_MASK;
        NVIC_DisableIRQ(ETM0_IRQn);
    }
    else if(ETM1 == pETM)
    {
        SIM->SCGC &= ~SIM_SCGC_ETM1_MASK;
        NVIC_DisableIRQ(ETM1_IRQn);
    } 
    else if (ETM2 == pETM)
    {
        SIM->SCGC &= ~SIM_SCGC_ETM2_MASK;
        NVIC_DisableIRQ(ETM2_IRQn);
    }
}
    
/*****************************************************************************//*!
*
* @brief 配置ETM通道, 包括通道状态及控制寄存器CnSC和通道计数值寄存器CnV.
*        
* @param[in]    pETM               指向三个ETM定时器其中一个的基址.
* @param[in]    ETM_Channel        ETM的通道号.
* @param[in]    pTETMCH_Params     配置ETM通道参数的结构体.
*
* @return none.
*
*****************************************************************************/
void ETM_ChannelInit(ETM_Type *pETM, uint8_t u8ETM_Channel, ETM_ChParamsType *pTETMCH_Params)
{
    ASSERT((ETM0 == pETM) || (ETM1 == pETM) || (ETM2 == pETM)); //断言检测通道的正确性
    
	if (ETM0 == pETM)
    {
        ASSERT(u8ETM_Channel < 2);
        SIM->SCGC |= SIM_SCGC_ETM0_MASK;
    }
    else if(ETM1 == pETM)
    {
        ASSERT(u8ETM_Channel < 2);
        SIM->SCGC |= SIM_SCGC_ETM1_MASK;
    }        
    else
    {
        ASSERT(u8ETM_Channel < 6);
        SIM->SCGC |= SIM_SCGC_ETM2_MASK;
    }
    
    pETM->CONTROLS[u8ETM_Channel].CnSC = pTETMCH_Params->u8CnSC;
    pETM->CONTROLS[u8ETM_Channel].CnV = pTETMCH_Params->u16CnV; 
    
    return;
}

/*****************************************************************************//*!
*
* @brief 配置级联模式及占空比(ETM2).
*
* @param[in]    pETM            ETM2.
* @param[in]    ETM_Channel     奇通道数：1、3、5.
* @param[in]    dutyCycle       设置占空比，若DutyCycle为10,那么占空比就为10%.
*
* @return none.
*
*****************************************************************************/
void  ETM_SetDutyCycleCombine(ETM_Type *pETM, uint8_t u8ETM_Channel, uint8_t u8DutyCycle)
{
    uint16_t   cnv = pETM->CONTROLS[u8ETM_Channel-1].CnV;
    uint16_t   modulo = pETM->MOD; 
    
    ASSERT((1 == u8ETM_Channel) || (3 == u8ETM_Channel) || (5 == u8ETM_Channel));
    
    cnv += (u8DutyCycle * (modulo+1))  / 100;
    if(cnv > modulo)
    {
        cnv = modulo - 1;
    }
    pETM->CONTROLS[u8ETM_Channel].CnV = cnv ;    
    
    pETM->PWMLOAD |= ETM_PWMLOAD_LDOK_MASK | (1<<u8ETM_Channel);     
}

/*****************************************************************************//*!
*
* @brief 配置寄存器 ETMx_SYNCONF部分位置位,其中里面包含了软件输出的控制是否由硬件触发HW或是否有软件出发SW(ETM2)
*
* @param[in]    pETM             ETM2.
* @param[in]    u32ConfigValue   用来配置SYNCONF寄存器.
*
* @return none.
*
*****************************************************************************/
void  ETM_SyncConfigActivate(ETM_Type *pETM, uint32_t u32ConfigValue)
{
    ASSERT((ETM2 == pETM));
    pETM->SYNCONF |= u32ConfigValue;   
}

/*****************************************************************************//*!
*
* @brief 配置寄存器 ETMx_SYNCONF部分位清除,其中里面包含了软件输出的控制是否由硬件触发HW或是否有软件出发SW(ETM2)
*
* @param[in]    pETM             ETM2.
* @param[in]    u32ConfigValue   用来配置SYNCONF寄存器.
*
* @return none.
*
*****************************************************************************/
void  ETM_SyncConfigDeactivate(ETM_Type *pETM, uint32_t u32ConfigValue)
{
    ASSERT((ETM2 == pETM));
    pETM->SYNCONF &= ~u32ConfigValue;   
}

/*****************************************************************************//*!
*
* @brief 设置回调函数入口.
*
* @param[in]    pETM            指向三个ETM定时器其中一个的基址.
* @param[in]    pfnCallback     回调函数地址.
*
* @return none.
*
*****************************************************************************/
void  ETM_SetCallback(ETM_Type *pETM, ETM_CallbackPtr pfnCallback)
{
   ETM_Callback[((uint32_t)pETM - (uint32_t)ETM0_BASE)>>12] = pfnCallback;
}



/*****************************************************************************//*!
*
* @brief ETM0通道中断服务函数.
*        
* @param none
*
* @return none 
*
*****************************************************************************/
void ETM0_Isr(void)
{
    if(ETM_Callback[0])
    {
        ETM_Callback[0]();
    }
}

/*****************************************************************************//*!
*
* @brief ETM1通道中断服务函数.
*        
* @param none
*
* @return none 
*
*****************************************************************************/
void ETM1_Isr(void)
{
    if(ETM_Callback[1])
    {
        ETM_Callback[1]();
    }
}

/*****************************************************************************//*!
*
* @brief ETM2通道中断服务函数.
*        
* @param none
*
* @return none 
*
*****************************************************************************/
void ETM2_Isr(void)
{
    if(ETM_Callback[2])
    {
        ETM_Callback[2]();
    }
}



