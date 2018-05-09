
/******************************************************************************
* @brief providing APIs for configuring ETM. 
*
*******************************************************************************
*
* provide APIs for configuring ETM
******************************************************************************/
#include "common.h"
#include "ETM.h"

/******************************************************************************
* Global variables
******************************************************************************/

/******************************************************************************
* Constants and macros
******************************************************************************/

/******************************************************************************
* Local types
******************************************************************************/

/******************************************************************************
* Local function prototypes
******************************************************************************/

/******************************************************************************
* Local variables
******************************************************************************/

/******************************************************************************
* Local functions
******************************************************************************/

/******************************************************************************
* Global functions
******************************************************************************/
ETM_CallbackPtr ETM_Callback[3] = {(ETM_CallbackPtr)NULL};


/******************************************************************************
* ETM api lists
*
*//*! @addtogroup ETM_api_list
* @{
*******************************************************************************/
/*******************************************************************************//*!
*
* @brief set the ETM moule clock source and prescale.
*        
* @param[in]    pETM                  pointer to one of three ETM base register address.
* @param[in]    ClockSource           ETM clock source.
* @param[in]    ClockPrescale         prescale factor.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*********************************************************************************/
/*******************************************************************************//*!
*
* @设置时钟资源及分频系数    
* @输入     pETM                 指向三个ETM定时器其中一个的基址
* @输入     ClockSource          ETM 时钟资源
* @输入     ClockPrescale        分频系数 
*
* @无返回
*
*********************************************************************************/
void ETM_ClockSet(ETM_Type *pETM, uint8_t u8ClockSource, uint8_t u8ClockPrescale)
{
    uint8_t   u8Temp;
	//pETM指向的SC寄存器低5位清0，即未选择时钟，时钟输入采取1分频
    u8Temp  = (pETM->SC & 0xE0);
	//时钟选择，及预分频因子选择
    u8Temp |= (ETM_SC_CLKS(u8ClockSource & 0x3) | ETM_SC_PS(u8ClockPrescale & 0x7));
	//配置该ETM的状态与控制寄存器ETMx_SC
    pETM->SC = u8Temp;
}

/*********************************************************************************//*!
*
* @brief general configuration to ETM_No to high ture EPWM mode, clock soure is the 
*        system clock, MOD, CnV are the initial value.
*        
* @param[in]    pETM                  pointer to one of three ETM base register address.
* @param[in]    PWMModeSelect         select CPWM , EPWM  or combine pwm mode.
* @param[in]    PWMEdgeSelect         select high true or low true pulse.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*********************************************************************************/
/******************************************************************************************
*
* @ETM中PWM的初始化函数      
* @输入        pETM                 指向三个ETM定时器其中一个的基址
* @输入        PWMModeSelect        居中对齐CPWM（10）、边沿对齐EPWM（01）以及级联模式PWM（11）
* @输入        PWMEdgeSelect        高真脉冲（01）、低真脉冲（10）
*
* @无返回
*
******************************************************************************************/
void ETM_PWMInit(ETM_Type *pETM, uint8_t u8PWMModeSelect, uint8_t u8PWMEdgeSelect)
{
    uint8_t   channels, i;
    
    ASSERT((ETM0== pETM) || (ETM1== pETM) || (ETM2== pETM));//断言检测通道合法性
    
    /* open the clock gate */  
	//使能ETM的时钟
	if (ETM0 == pETM)
    {
        channels = 2;
        SIM->SCGC |= SIM_SCGC_ETM0_MASK;
    }
    else if(ETM1 == pETM)
    {
        channels = 2;
#if !defined(CPU_NV32M3)
        SIM->SCGC |= SIM_SCGC_ETM1_MASK;
#endif
    }        
    else
    {
        channels = 6;
        SIM->SCGC  |= SIM_SCGC_ETM2_MASK;
    }
    
    pETM->SC  = 0x0;     //关闭计数器          /* disable counter */  
	pETM->MOD = ETM_MOD_INIT; 
    
    if(ETM_PWMMODE_CENTERALLIGNED == u8PWMModeSelect) //使能CPWM   /* enable CPWM */
    {
        pETM->SC |= ETM_SC_CPWMS_MASK; 
    }
    else if(ETM_PWMMODE_COMBINE == u8PWMModeSelect) // 打开级联PWM模式    /* enable combine pwm mode */
    {
        ASSERT(ETM2 == pETM);
        pETM->MODE    |= ETM_MODE_WPDIS_MASK | ETM_MODE_ETMEN_MASK;
        pETM->COMBINE = ETM_COMBINE_COMBINE0_MASK | ETM_COMBINE_COMP0_MASK | ETM_COMBINE_SYNCEN0_MASK | ETM_COMBINE_DTEN0_MASK |
                        ETM_COMBINE_COMBINE1_MASK | ETM_COMBINE_COMP1_MASK | ETM_COMBINE_SYNCEN1_MASK | ETM_COMBINE_DTEN1_MASK |
                        ETM_COMBINE_COMBINE2_MASK | ETM_COMBINE_COMP2_MASK | ETM_COMBINE_SYNCEN2_MASK | ETM_COMBINE_DTEN2_MASK 
                        ;     
        pETM->SC &= ~ETM_SC_CPWMS_MASK; 
    }
    if(ETM_PWM_HIGHTRUEPULSE == u8PWMEdgeSelect)
    {
        /* Configure ETMers PWM High True Pulses */
		/* 配置通道寄存器，设置通道状态及通道计数值 */
        for(i=0; i<channels; i++)
        {
            pETM->CONTROLS[i].CnSC = ETM_CnSC_MSB_MASK | ETM_CnSC_ELSB_MASK;  
            pETM->CONTROLS[i].CnV  = ETM_C0V_INIT + i*100; 
        }
    }
    else if(ETM_PWM_LOWTRUEPULSE == u8PWMEdgeSelect)
    {
        /* Configure ETMers for PWM Low True Pulses */
        for(i=0; i<channels; i++) 
        {
            pETM->CONTROLS[i].CnSC = ETM_CnSC_MSB_MASK | ETM_CnSC_ELSA_MASK; 
            pETM->CONTROLS[i].CnV  = ETM_C0V_INIT + i*100 ; 
        }
    }  
}

/*********************************************************************************//*!
*
* @brief general configuration to ETM_No to input capture mode, enable interrupt.
*        
* @param[in]    pETM                  pointer to one of three ETM base register address.
* @param[in]    Channel               channel number to be configured.
* @param[in]    CaptureMode           select capture edge: rising, falling or both.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*********************************************************************************/
/*********************************************************************************
*
* @输入捕捉初始化函数
*        
* @输入        pETM                  指向三个ETM定时器其中一个的基址
* @输入        Channel               配置通道号
* @输入        CaptureMode           选择捕捉方式:上升沿, 下降沿或跳变沿.
*
* @无返回
*
*********************************************************************************/
void ETM_InputCaptureInit(ETM_Type *pETM, uint8_t u8ETM_Channel, uint8_t u8CaptureMode)
{ 
    ASSERT(((ETM0 == pETM) && (u8ETM_Channel < 2))   || 
           ((ETM1 == pETM) && (u8ETM_Channel < 2))   || 
           ((ETM2 == pETM) && (u8ETM_Channel < 6))
           );

    
    /* open the clock gate */
	 /* 使能ETM的时钟 */
	if ((ETM0 == pETM) && (u8ETM_Channel < 2))
    {
        SIM->SCGC |= SIM_SCGC_ETM0_MASK;
        NVIC_EnableIRQ(ETM0_IRQn);
    }
    else if((ETM1 == pETM)  && (u8ETM_Channel < 2))
    {
#if !defined(CPU_NV32M3)
        SIM->SCGC |= SIM_SCGC_ETM1_MASK;
        NVIC_EnableIRQ(ETM1_IRQn);
#endif
    }        
    else 
    {
        SIM->SCGC |= SIM_SCGC_ETM2_MASK;
        NVIC_EnableIRQ(ETM2_IRQn);
    }
    
    pETM->SC  = 0x0;    //关闭计数器     /* diable counter */ 
    pETM->MOD = 0xFFFF;  /* free running */
    
    if(ETM_INPUTCAPTURE_RISINGEDGE == u8CaptureMode) //使能中断，在上升沿捕捉       /* enable interrupt, Capture on rising edge */
    {
        pETM->CONTROLS[u8ETM_Channel].CnSC = ETM_CnSC_CHIE_MASK | ETM_CnSC_ELSA_MASK;
    }
    else if(ETM_INPUTCAPTURE_FALLINGEDGE == u8CaptureMode) //在下降沿捕捉      /* Capture on falling edge */
    {
        pETM->CONTROLS[u8ETM_Channel].CnSC = ETM_CnSC_CHIE_MASK | ETM_CnSC_ELSB_MASK;
    }
    else if(ETM_INPUTCAPTURE_BOTHEDGE == u8CaptureMode) //在上升沿或下降沿捕捉     /* Capture on rising or falling edge */
    {
        pETM->CONTROLS[u8ETM_Channel].CnSC = ETM_CnSC_CHIE_MASK | ETM_CnSC_ELSA_MASK | ETM_CnSC_ELSB_MASK;       
    }
}

/*********************************************************************************//*!
*
* @brief general configuration to ETM_No to Dual Edge Capture mode to measure the
*        width or the period  of a pulse.
*        
* @param[in]    pETM                  pointer to one of three ETM base register address.
* @param[in]    ChannelPair           ChannelPair number to be configured: 0, 2, 4.
* @param[in]    CaptureMode           select capture edge: one shot and continuous mode.
* @param[in]    Channel_N_Edge        channel N detect edge. 
* @param[in]    Channel_Np1_Edge      channel N+1 detect edge.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*********************************************************************************/
/*********************************************************************************//*!
*
* @对ETM配置双边捕获模式来测量一个脉冲的宽度或周期
*        
* @输入        pETM                  指向三个ETM定时器其中一个的基址
* @输入        ChannelPair           频道配对数的配置为: 0, 2, 4.
* @输入        CaptureMode           选择单周期捕捉，和连续捕捉方式
* @输入        Channel_N_Edge        频道N边沿检测 
* @输入        Channel_Np1_Edge      频道N+1边沿检测.
*
* @无返回
*
*********************************************************************************/
void ETM_DualEdgeCaptureInit(ETM_Type *pETM, uint8_t u8ChannelPair, uint8_t u8CaptureMode, 
                                 uint8_t u8Channel_N_Edge, uint8_t u8Channel_Np1_Edge)
{ 
    ASSERT((ETM2 == pETM)  && (u8ChannelPair < 6) && !(u8ChannelPair & 1) );
    
    SIM->SCGC |= SIM_SCGC_ETM2_MASK;
    if((0 == u8ChannelPair) || (2== u8ChannelPair))
    {
                                  //通道滤波      /* channel filter is active */
    }
       
    pETM->SC    = 0x0;         //关闭计数器         /* diable counter */ 
    pETM->MOD   = 0xFFFF;
    pETM->MODE |= ETM_MODE_ETMEN_MASK;  /* ETMEN = 1 */  
    /* DECAPEN = 1,  ChannelPair/2 * 8 */
    pETM->COMBINE |=  ((ETM_COMBINE_DECAPEN0_MASK) << (u8ChannelPair * 4)); 
    
    pETM->CONTROLS[u8ChannelPair].CnSC &= ~ETM_CnSC_CHF_MASK;  //清除相关位     /* CH(n)F and CH(n+1)F bits must be cleared first */
    pETM->CONTROLS[u8ChannelPair + 1].CnSC &= ~ETM_CnSC_CHF_MASK;
    
    if(ETM_INPUTCAPTURE_DUALEDGE_ONESHOT == u8CaptureMode)   //单周期模式     /* oneshot mode */
    {
        pETM->CONTROLS[u8ChannelPair].CnSC &= ~ETM_CnSC_MSA_MASK;
        pETM->CONTROLS[u8ChannelPair+1].CnSC &= ~ETM_CnSC_MSA_MASK;
    }
    else if(ETM_INPUTCAPTURE_DUALEDGE_CONTINUOUS == u8CaptureMode) //连续模式   /* continuouse mode */
    {
        pETM->CONTROLS[u8ChannelPair].CnSC |= ETM_CnSC_MSA_MASK;
        pETM->CONTROLS[u8ChannelPair+1].CnSC |= ETM_CnSC_MSA_MASK;
    }
    
    pETM->CONTROLS[u8ChannelPair].CnSC |= (u8Channel_N_Edge << 2); //选择检测边沿  /* select detec edge */
    pETM->CONTROLS[u8ChannelPair + 1].CnSC |= (u8Channel_Np1_Edge << 2);   
    
    pETM->COMBINE |=  (ETM_COMBINE_DECAP0_MASK << (u8ChannelPair * 4)); 
}

/*********************************************************************************//*!
*
* @brief general configuration to ETM_No to input capture mode.
*        
* @param[in]    pETM                  pointer to one of three ETM base register address.
* @param[in]    Channel               channel number to be configured.
* @param[in]    CompareMode           select compare edge: toggle, set and clear.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*********************************************************************************/
/*********************************************************************************//*!
*
* @输出对比初始化
* 
* @输入     pETM                   指向三个ETM定时器其中一个的基址
* @输入     Channel                必须完成配置通道即通道号
* @输入     CompareMode            选择模式：翻转（01）、置位（11）、清0（10）
*
* @无返回
*
*********************************************************************************/
void ETM_OutputCompareInit(ETM_Type *pETM, uint8_t u8ETM_Channel, uint8_t u8CompareMode)
{
    ASSERT(((ETM0 == pETM) && (u8ETM_Channel < 2))   || 
           ((ETM1 == pETM) && (u8ETM_Channel < 2))   || 
           ((ETM2 == pETM) && (u8ETM_Channel < 6))
           );
    
    /* open the clock gate */
	 /* 使能ETM的时钟 */
	if(ETM0 == pETM)
    {
        SIM->SCGC |= SIM_SCGC_ETM0_MASK;
    }
    else if(ETM1 == pETM)
    {
#if !defined(CPU_NV32M3)
        SIM->SCGC |= SIM_SCGC_ETM1_MASK;
#endif
    }        
    else
    {
        SIM->SCGC |= SIM_SCGC_ETM2_MASK;
    }
    
    pETM->SC  = 0x0;                                                 //关闭计数器                  /* diable counter */
    pETM->MOD = ETM_MOD_INIT; 
    pETM->CONTROLS[u8ETM_Channel].CnSC = (ETM_CnSC_MSA_MASK | (u8CompareMode << 2)); //选择检测边沿   /* select detec edge */
    pETM->CONTROLS[u8ETM_Channel].CnV  = ETM_C0V_INIT;
}

/*********************************************************************************//*!
*
* @brief general configuration to ETM2 to start software synchronization.
*        
* @param[in]    pETM                  pointer to one of three ETM base register address.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*********************************************************************************/
/*********************************************************************************//*!
*
* @运用ETM2来实现软件同步
*        
* @输入       pETM                   指向三个ETM定时器其中一个的基址
*
* @无返回
*
*********************************************************************************/
void ETM_SoftwareSync(ETM_Type *pETM)
{
    ASSERT(ETM2 == pETM);

    pETM->SYNCONF   |= ETM_SYNCONF_SYNCMODE_MASK;   // 选择增强PWM同步  /* recommend enhanced sync mode */
    pETM->SYNC      |= ETM_SYNC_SWSYNC_MASK;
}

/*********************************************************************************//*!
*
* @brief general configuration to ETM to enable hardware synchronization.
*        
* @param[in]    pETM                  pointer to one of three ETM base register address.
* @param[in]    u8TriggerN            select the hardware trigger source.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*********************************************************************************/
/********************************************************************
* @ETM中配置ETMx_SYNC 寄存器来保证软件同步        
* 
* @输入       pETM                    指向三个ETM定时器其中一个的基址
* @输入       u8TriggerN              选择硬件触发资源
*
* @无返回
*
*********************************************************************************/
void ETM_HardwareSync(ETM_Type *pETM, uint8_t u8TriggerN)
{
    ASSERT(ETM2 == pETM);
    
    pETM->SYNCONF   |= ETM_SYNCONF_SYNCMODE_MASK; //选择增强PWM同步 /* recommend enhanced sync mode */
    
    switch(u8TriggerN)
    {
        case ETM_SYNC_TRIGGER_TRIGGER2: 
                pETM->SYNC |= ETM_SYNC_TRIG2_MASK;
                break;  
        case ETM_SYNC_TRIGGER_TRIGGER1: 
                pETM->SYNC |= ETM_SYNC_TRIG1_MASK;
                break;   //首先配置ETM0CH0  /* need configure ETM0CH0 first */
        case ETM_SYNC_TRIGGER_TRIGGER0:
                pETM->SYNC |= ETM_SYNC_TRIG0_MASK; 
                break;   //首先配置CMP0  /* need configure CMP0 first */
        default: 
                break;
    }
}

/*********************************************************************************//*!
*
* @brief general configuration to ETM to enable hardware synchronization, more then 1 trigger.
*        
* @param[in]    pETM               pointer to one of three ETM base register address.
* @param[in]    u8TriggerMask      select the hardware trigger source. combine TRIG0~TREG2.(x000xxxx~x111xxxx)
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*********************************************************************************/
/*********************************************************************************//*!
*
* @通过配置ETM保证硬件同步，产生触发
*        
* @输入   pETM              指向三个ETM定时器其中一个的基址
* @输入   u8TriggerMask     选择硬件触发资源. 
*
* @无返回.
*
*********************************************************************************/
void ETM_HardwareSyncCombine(ETM_Type *pETM, uint8_t u8TriggerMask)
{
    ASSERT(ETM2 == pETM);
    
    pETM->SYNCONF   |= ETM_SYNCONF_SYNCMODE_MASK;  //选择增强PWM同步 /* recommend enhanced sync mode */
    pETM->SYNC      &= 0x8F;
    pETM->SYNC      |= (u8TriggerMask & 0x70);
}

/*********************************************************************************//*!
*
* @brief generate ETM2 hardware trigger 2,Note: please call ETM_HardwareSyncCombine first.
*        
* @param[in]    pETM               pointer to one of three ETM base register address.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*********************************************************************************/
/*********************************************************************************//*!
*
* @产生ETM2硬件触发
*        
* @输入        pETM              指向三个ETM定时器其中一个的基址
*
* @无返回
*
*********************************************************************************/
void ETM_GenerateTrig2(ETM_Type *pETM)
{
    ASSERT(ETM2 == pETM);
    
    if(pETM->SYNC & ETM_SYNC_TRIG2_MASK)
    {
#if defined(CPU_NV32)
        SIM->SOPT  |= SIM_SOPT_ETMSYNC_MASK;
#elif defined(CPU_NV32M3)
        SIM->SOPT  |= SIM_SOPT_ETMSYNC_MASK;
#elif defined(CPU_NV32M4)
        SIM->SOPT0  |= SIM_SOPT0_ETMSYNC_MASK;
#endif
    }
}


/*********************************************************************************//*!
*
* @brief general configuration to ETM_No to start software synchronization.
*        
* @param[in]    pETM                  pointer to one of three ETM base register address.
* @param[in]    PrescalerValue        system clock divide value, 0 to 3.
* @param[in]    DeadETMeValue         n count clock is inserted, 0 to 63.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*********************************************************************************/
/*********************************************************************************//*!
*
* @ETM死区时间插入设置.
*        
* @输入         pETM                  指向三个ETM定时器其中一个的基址
* @输入         PrescalerValue        系统时钟分频值
* @输入         DeadETMeValue         死去插入时间值，0-63可选
*
* @无返回
*
*********************************************************************************/
void ETM_PWMDeadETMeSet(ETM_Type *pETM, uint8_t u8PrescalerValue, uint8_t u8DeadETMeValue)
{
    ASSERT(ETM2 == pETM);
    
    pETM->COMBINE |= 0x101010;     //使能死区时间插入    /* enable dead ETMe insertion */

    if(!(pETM->MODE & ETM_MODE_WPDIS_MASK)) //如果开启了写保护/* if write protection is enabled */
    {
        pETM->MODE |= ETM_MODE_WPDIS_MASK; //禁用写保护 /* disable the write protection */
        pETM->DEADETME = (ETM_DEADETME_DTVAL(u8DeadETMeValue & 0x3F) | ETM_DEADETME_DTPS(u8PrescalerValue & 0x3));
        pETM->MODE &= ~ETM_MODE_WPDIS_MASK;//使能写保护 /* enable the write protection */       
    }
    else 
    {
        //如果没有开启写保护     /* if no protection */
        pETM->DEADETME = (ETM_DEADETME_DTVAL(u8DeadETMeValue & 0x3F) | ETM_DEADETME_DTPS(u8PrescalerValue & 0x3));
    }
    pETM->SYNC |= ETM_SYNC_SWSYNC_MASK;    //软件同步 /* software sync */
}    

/*********************************************************************************//*!
*
* @brief set output mask.
*        
* @param[in]    pETM                  pointer to one of three ETM base register address.
* @param[in]    Channel               pwm channel needed to be masked.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*********************************************************************************/
/*********************************************************************************//*!
*
* @设置输出标志位
*        
* @输入           pETM                  指向三个ETM定时器其中一个的基址
* @输入           Channel               PWM通道位需要被置标志
*
* @无返回
*
*********************************************************************************/
void ETM_OutputMaskSet(ETM_Type *pETM, uint8_t u8ETM_Channel)
{
    ASSERT((ETM2 == pETM) && (u8ETM_Channel < 6));

    pETM->OUTMASK |= (1 << u8ETM_Channel);
    
    if(pETM->SYNC & ETM_SYNC_SYNCHOM_MASK)           //如果需要PWM同步更新   /* if PWM sync is needed */
    {
        pETM->SYNCONF |= ETM_SYNCONF_SYNCMODE_MASK;   //选择增强PWM同步  /* recommend enhanced sync mode */
        if(pETM->SYNCONF & ETM_SYNCONF_SWOM_MASK)    //如果需要软件同步   /* if software sync is needed*/
        {
            pETM->SYNC |= ETM_SYNC_SWSYNC_MASK;
        }
        else if(pETM->SYNCONF & ETM_SYNCONF_HWOM_MASK)//如果需要硬件同步 /* if hardware sync is needed*/
        {
            pETM->SYNC |= ETM_SYNC_TRIG2_MASK;
            
#if defined(CPU_NV32)
            SIM->SOPT  |= SIM_SOPT_ETMSYNC_MASK;      //硬件同步   /* hardware sync */ 
#elif defined(CPU_NV32M3)
            SIM->SOPT  |= SIM_SOPT_ETMSYNC_MASK;         /* hardware sync */ 
#elif defined(CPU_NV32M4)
            SIM->SOPT0  |= SIM_SOPT0_ETMSYNC_MASK;         /* hardware sync */ 
#endif
        }
        else
        {
        }
    }
    else  /* no need to sync, update on the next rising edge of system clock  */
    {
    }
}

/*********************************************************************************//*!
*
* @brief general configuration to ETM_No to start software synchronization.
*        
* @param[in]    pETM                  pointer to one of three ETM base register address.
* @param[in]    Channel               pwm channel needed to be controlled by software.
* @param[in]    ChannelValue          the value to be set,  0 or 1.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*********************************************************************************/
/*********************************************************************************//*!
*
* @配置软件输出控制SWOCTRL寄存器的同步是否由软件触发
*        
* @输入        pETM                  指向三个ETM定时器其中一个的基址
* @输入        Channel               PWM波的通道选择
* @输入        ChannelValue          0或1,0不触发;1触发
*
* @无返回
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
    if(pETM->SYNCONF & ETM_SYNCONF_SWOC_MASK)               /* if PWM sync is needed */
    {
        pETM->SYNCONF |= ETM_SYNCONF_SYNCMODE_MASK;         /* recommend enhanced sync mode */
        if(pETM->SYNCONF & ETM_SYNCONF_SWSOC_MASK)          /* if software sync is needed*/
        {
            pETM->SYNC |= ETM_SYNC_SWSYNC_MASK;             /* software sync */ 
        }
        else if(pETM->SYNCONF & ETM_SYNCONF_HWSOC_MASK)     /* if hardware sync is needed*/
        {
            pETM->SYNC |= ETM_SYNC_TRIG2_MASK;

#if defined(CPU_NV32)
            SIM->SOPT  |= SIM_SOPT_ETMSYNC_MASK;             /* hardware sync */ 
#elif defined(CPU_NV32M3)
            SIM->SOPT  |= SIM_SOPT_ETMSYNC_MASK;             /* hardware sync */ 
#elif defined(CPU_NV32M4)
            SIM->SOPT0  |= SIM_SOPT0_ETMSYNC_MASK;             /* hardware sync */ 
#endif
        }
    }
    else  /* no need to sync, update on the next rising edge of system clock  */
    {
    }
}

/*********************************************************************************//*!
*
* @brief set PWM polarity.
*        
* @param[in]    pETM                  pointer to one of three ETM base register address.
* @param[in]    Channel               pwm channel needed to be controlled by software.
* @param[in]    ActiveValue           the value to be set,  0 or 1.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*********************************************************************************/
/*********************************************************************************
*
* @设置通道输出极性的功能函数
*        
* @输入     pETM                 指向三个ETM定时器其中一个的基址
* @输入     Channel              PWM波的通道选择
* @输入     ActiveValue          极性的选择，0为高电平，1为低电平
*
* @无返回
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
* @brief set ETM behavior in debug mode.
*        
* @param[in]    pETM             pointer to one of three ETM base register address.
* @param[in]    u8DebugMode      debug mode select from 00 to 11.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*********************************************************************************/
/*********************************************************************************
*
* @选择BDM模式下的ETM行为
*        
* @输入   pETM             指向三个ETM定时器其中一个的基址
* @输入   u8DebugMode      debug 的模式从00-11之间选择
*
* @无返回
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
* @brief Selects the ratio between the number of counter overflows to the number of ETMes the TOF bit is set.
*        
* @param[in]    pETM             pointer to one of three ETM base register address.
* @param[in]    u8TOFNUM         TOF numbers before setting TOF bit, 0~31.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*********************************************************************************/
/*********************************************************************************//*!
*
* @ETM中TOF频率大小的设置功能函数
*        
* @输入    pETM              指向三个ETM定时器其中一个的基址
* @输入    u8TOFNUM          TOF频率数，大小0和31之间
* 
* @无返回
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
* @brief swap the output of CH(n) and CH(n+1).
*        
* @param[in]    pETM                  pointer to one of three ETM base register address.
* @param[in]    ChannelPair           the pair to be swapped, 0,1,2.
*    
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*********************************************************************************/
/*********************************************************************************
*
* @交换通道CH（n）和通道CH（n+1）的输出结果   
*    
* @输入  pETM                   其中一个ETM定时器的基址
* @输入  ChannelPair            要被交换的通道数号，即n可为0,1,2,
*
*********************************************************************************/
void ETM_InvertChannel(ETM_Type *pETM, uint8_t u8ChannelPair)
{
    ASSERT((ETM2 == pETM)  && u8ChannelPair <= 2);

    pETM->INVCTRL |= 1<<u8ChannelPair;
    if(pETM->SYNCONF & ETM_SYNCONF_INVC_MASK)     //如果需要PWM同步  /* if PWM sync is needed */
    {
        pETM->SYNCONF |= ETM_SYNCONF_SYNCMODE_MASK; //选择增强PWM同步 /* recommend enhanced sync mode */
        if(pETM->SYNCONF & ETM_SYNCONF_SWINVC_MASK)//如果需要软件同步 /* if software sync is needed*/
        {
            pETM->SYNC |= ETM_SYNC_SWSYNC_MASK; //开启软件同步   /* software sync */ 
        }
        else if(pETM->SYNCONF & ETM_SYNCONF_HWINVC_MASK)   //如果需要硬件同步 /* if hardware sync is needed*/
        {
            pETM->SYNC |= ETM_SYNC_TRIG2_MASK;

#if defined(CPU_NV32)
            SIM->SOPT  |= SIM_SOPT_ETMSYNC_MASK;       //硬件同步      /* hardware sync */ 
#elif defined(CPU_NV32M3)
            SIM->SOPT  |= SIM_SOPT_ETMSYNC_MASK;             /* hardware sync */ 
#elif defined(CPU_NV32M4)
            SIM->SOPT0  |= SIM_SOPT0_ETMSYNC_MASK;             /* hardware sync */ 
#endif
        }
    }
    else  
    {
    }
}  

/*****************************************************************************//*!
*
* @brief configure the ETM as specified control parameters, CnSC and CnV not 
*        included.
*        
* @param[in]    pETM          pointer to one of three ETM base register address.
* @param[in]    pConfig     pointer to ETM general parameters.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*****************************************************************************/
/*****************************************************************************//*!
*
* @ETM初始化函数
*        
* @输入        pETM           指向三个ETM定时器其中一个的基址
* @输入        pConfig        指向ETM的一些基本参数
* @无返回值
*
*****************************************************************************/
void ETM_Init(ETM_Type *pETM, ETM_ConfigType *pConfig)
{
    ASSERT((ETM0 == pETM) || (ETM1 == pETM) || (ETM2 == pETM));
    if(ETM0 == pETM)
    {
        SIM->SCGC |= SIM_SCGC_ETM0_MASK;
    }
#if !defined(CPU_NV32M3)
    else if(ETM1 == pETM)
    {
        SIM->SCGC |= SIM_SCGC_ETM1_MASK;
    }
#endif
    else
    {
        SIM->SCGC |= SIM_SCGC_ETM2_MASK;
    }
        
    /* diable counter */
    pETM->SC = 0; 
 	pETM->MODE = pConfig->mode;       
	pETM->MOD = pConfig->modulo;
	pETM->CNT = pConfig->cnt;
        
    if( pETM->MODE & ETM_MODE_ETMEN_MASK  ) 
    {
        /* when ETMEN = 1, all other registers can be written */
		 /* 当 ETMEN = 1, 所有寄存器都可以被写入 */
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
        pETM->FLTCTRL   = pConfig->fltctrl;    /* fault control */ 
        pETM->FLTPOL    = pConfig->fltpol;      
        pETM->CONF      = pConfig->conf;      
        pETM->SYNCONF   = pConfig->synconf;      
        pETM->SWOCTRL   = pConfig->swoctrl;      
        pETM->PWMLOAD   = pConfig->pwmload;      
    }
    /* write SC to enable clock */
    /*通过写入状态控制寄存器SC来使能ETM时钟 */
    pETM->SC = pConfig->sc;
}


/*****************************************************************************//*!
*
* @brief  close the ETM moudle.
*        
* @param[in]    pETM          pointer to one of three ETM base register address.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*****************************************************************************/
/*****************************************************************************
*
*关闭相应的ETM功能组件函数     
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
    /* close the clock gate */
	/* 禁用时钟 */
	if (ETM0 == pETM)
    {
        SIM->SCGC &= ~SIM_SCGC_ETM0_MASK;
        NVIC_DisableIRQ(ETM0_IRQn);
    }
#if !defined(CPU_NV32M3)    
    else if(ETM1 == pETM)
    {
        SIM->SCGC &= ~SIM_SCGC_ETM1_MASK;
        NVIC_DisableIRQ(ETM1_IRQn);
    } 
#endif
    else if (ETM2 == pETM)
    {
        SIM->SCGC &= ~SIM_SCGC_ETM2_MASK;
        NVIC_DisableIRQ(ETM2_IRQn);
    }
}
    
/*****************************************************************************//*!
*
* @brief configure the ETM  channels, CnSC and CnV are included.
*        
* @param[in]    pETM               pointer to one of three ETM base register address.
* @param[in]    ETM_Channel        ETM channel number.
* @param[in]    pTETMCH_Params     pointer to ETM channel general parameters.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*****************************************************************************/
/*****************************************************************************//*!
*
* @本函数用来配置ETM通道, 包括通道状态及控制寄存器CnSC和通道计数值寄存器CnV      
* @输入     pETM                 指向三个ETM定时器其中一个的基址
* @输入     ETM_Channel          ETM的通道号
* @输入     pTETMCH_Params      指向ETM通道一般参数的指针
*
* @无返回值
*
*****************************************************************************/
void ETM_ChannelInit(ETM_Type *pETM, uint8_t u8ETM_Channel, ETM_ChParamsType *pTETMCH_Params)
{
    ASSERT((ETM0 == pETM) || (ETM1 == pETM) || (ETM2 == pETM));  
    
	if (ETM0 == pETM)
    {
        ASSERT(u8ETM_Channel < 2);
        SIM->SCGC |= SIM_SCGC_ETM0_MASK;
    }
 #if !defined(CPU_NV32M3)
    else if(ETM1 == pETM)
    {
        ASSERT(u8ETM_Channel < 2);
        SIM->SCGC |= SIM_SCGC_ETM1_MASK;
    }        
#endif
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
* @brief set the ETM channel value register per duty cycle and modulo for combine mode
*        odd channel no must be provided and even channel value register is not changed.
*
* @param[in]    pETM            pointer to one of three ETM base register address.
* @param[in]    ETM_Channel     odd channel no:1,3,5.
* @param[in]    dutyCycle       duty cycle in percentage. e.g. 10, means 10%.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*****************************************************************************/
/*****************************************************************************//*!
*
* 必须设置奇数通道数，且偶数通道的值不变
*
* @输入        pETM            指向三个ETM定时器其中一个的基址
* @输入        ETM_Channel     奇通道数：1、3、5
* @输入        dutyCycle       设置占空比，若DutyCycle为10,那么占空比就为10%
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
* @brief configure the ETMx_SYNCONF register including SW and HW Sync selection.
*
* @param[in]    pETM             pointer to one of three ETM base register address.
* @param[in]    u32ConfigValue   ETMx_SYNCONF register config value.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*****************************************************************************/
/*****************************************************************************
*
* @配置寄存器 ETMx_SYNCONF,其中里面包含了软件输出的控制是否由硬件触发HW或是否有软件出发SW
*
* @输入     pETM               指向三个ETM定时器其中一个的基址
* @输入     u32ConfigValue     ETMx_SYNCONF这个寄存器的值 
*
* @无返回
*
*****************************************************************************/
void  ETM_SyncConfigActivate(ETM_Type *pETM, uint32_t u32ConfigValue)
{
    ASSERT((ETM2 == pETM));
    pETM->SYNCONF |= u32ConfigValue;   
}

/*****************************************************************************//*!

*
* @brief configure the ETMx_SYNCONF register including SW and HW Sync selection.
*
* @param[in]    pETM             pointer to one of three ETM base register address.
* @param[in]    u32ConfigValue   ETMx_SYNCONF register config value.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*****************************************************************************/
/*****************************************************************************
*
* @恢复配置寄存器 ETMx_SYNCONF,其中里面包含了软件输出的控制是否由硬件触发HW或是否有软件出发SW
*
* @输入     pETM               指向三个ETM定时器其中一个的基址
* @输入     u32ConfigValue     ETMx_SYNCONF这个寄存器的值 
*
* @无返回
*
*****************************************************************************/
void  ETM_SyncConfigDeactivate(ETM_Type *pETM, uint32_t u32ConfigValue)
{
    ASSERT((ETM2 == pETM));
    pETM->SYNCONF &= ~u32ConfigValue;   
}

/*****************************************************************************//*!
*
* @brief This function sets the callback function.
*
* @param[in]    pETM          pointer to one of three ETM base register address.
* @param[in]    pfnCallback     functon address.
*
* @return none.
*
* @ Pass/ Fail criteria: none
*
*****************************************************************************/
/*****************************************************************************//*!
*
* @设置中断回调函数入口
*
* @输入       pETM            指向三个ETM中其中一个的基址
* @输入       pfnCallback     功能函数的地址
*
* @无返回.
*
*****************************************************************************/
void  ETM_SetCallback(ETM_Type *pETM, ETM_CallbackPtr pfnCallback)
{
   ETM_Callback[((uint32_t)pETM - (uint32_t)ETM0_BASE)>>12] = pfnCallback;
}

/*! @} End of ETM_api_list                                                    */


/*****************************************************************************//*!
*
* @brief  ETM0_Isr interrupt service routine.
*        
* @param  none.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*****************************************************************************/
/*********************************************************************************//*!
*
* @ETM0中断服务函数
* 
* @无输入
*
* @无返回
*
*********************************************************************************/
void ETM0_Isr(void)
{
    if(ETM_Callback[0])
    {
        ETM_Callback[0]();
    }
}

/*****************************************************************************//*!
*
* @brief  ETM1_Isr interrupt service routine.
*        
* @param  none. 
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*****************************************************************************/
/*********************************************************************************//*!
*
* @ETM1中断服务函数
* 
* @无输入
*
* @无返回
*
*********************************************************************************/
void ETM1_Isr(void)
{
    if(ETM_Callback[1])
    {
        ETM_Callback[1]();
    }
}

/*****************************************************************************//*!
*
* @brief  ETM2_Isr interrupt service routine.
*        
* @param  none. 
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*****************************************************************************/
/*********************************************************************************//*!
*
* @ETM2中断服务函数
* 
* @无输入
*
* @无返回
*
*********************************************************************************/
void ETM2_Isr(void)
{
    if(ETM_Callback[2])
    {
        ETM_Callback[2]();
    }
}



