/******************************************************************************
*
* @brief  SIM 驱动头文件.  
*
******************************************************************************/
#ifndef SIM_H_
#define SIM_H_

typedef enum {
    ID_TYPE_FAMID,                  /*!< NV32F100x系列   ID */
    ID_TYPE_SUBFAMID,               /*!< NV32F100x子系列 ID */ 
    ID_TYPE_REVID,                  /*!< 器件版本 ID */
    ID_TYPE_PINID                   /*!< 器件引脚 ID */
} IDType;
                                                    				

#if defined(CPU_NV32)
typedef struct{
    struct{
        uint32_t bEnableCLKOUT  : 1;        /*!< 1: 使能 , 0: 禁用 */
        uint32_t bTXDME         : 1;        /*!< 1: 使能 TXDME, 0: 禁用 */
        uint32_t bETMSYNC       : 1;        /*!< 1: 使能 ETM SYNC, 0: 未触发任何同步 */
        uint32_t bRXDFE         : 1;        /*!< 1: 使能 RXD 滤波, 0: 无滤波 */
        uint32_t bRXDCE         : 1;        /*!< 1: 使能 RXD 捕捉, 0: 无捕捉 */
        uint32_t bACIC          : 1;        /*!< 1: ACMP0的输出通道连接到ETM1的输入通道0, 0: 无连接 */
        uint32_t bRTCC          : 1;        /*!< 1: RTC溢出连接到ETM1输入通道1, 0: 无连接 */
        uint32_t u8ADHWT        : 2;        /*!<    选择ADC转换硬件触发源 */
        uint32_t bDisableSWD    : 1;        /*!< 1: 禁用SWD, 0: 使能 */
        uint32_t bDisableRESET  : 1;        /*!< 1: 禁用复位引脚, 0: 使能 */
        uint32_t bDisableNMI    : 1;        /*!< 1: 禁用NMI中断输入引脚, 0:使能 */
        uint32_t bBusDiv        : 1;        /*!<    总线分频系数 */
    } sBits;
    uint8_t     u8Delay;                /*!< ETM触发ADC转换延时值 */
    uint8_t     u8BusRef;               /*!< 总线参考 */
    uint32_t    u32PinSel;              /*!< 引脚选择寄存器的值*/
    uint32_t    u32SCGC;                /*!< 时钟选通寄存器的值 */   
} SIM_ConfigType, *SIM_ConfigPtr; /*!< SIM模块配置结构体类型 */
#endif
                                                 				
  
#if defined(CPU_NV32)
/*****************************************************************************//*!
*
* @brief 设置ETM2触发ADC转换的延时时间
*        
* @param[in]   u8Delay     延时时间模数值，参考时钟采用总线时钟分频
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_DelayETM2Trig2ADC(uint8_t u8Delay)
{
    SIM->SOPT = (SIM->SOPT & ~(SIM_SOPT_DELAY_MASK)) | SIM_SOPT_DELAY(u8Delay);    
}
/*****************************************************************************//*!
*
* @brief 使能总线时钟在PH2上
*
* @param   none
*
* @return none 
*
* @ 参看  SIM_DisableClockOutput
*****************************************************************************/
__STATIC_INLINE void SIM_EnableClockOutput(void)
{
    SIM->SOPT |= (SIM_SOPT_CLKOE_MASK);    
}

/*****************************************************************************//*!
*
* @brief 禁用总线时钟输出在PH2上
*        
* @param   none
*
* @return none
*
* @参看  SIM_EnableClockOutput
*****************************************************************************/
__STATIC_INLINE void SIM_DisableClockOutput(void)
{
    SIM->SOPT &= ~(SIM_SOPT_CLKOE_MASK);    
}
/*****************************************************************************//*!
*
* @brief 设置总线时钟输出分频. 
*        
* @param[in]  u8Divide     分频系数 (3-bits)
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void SIM_SetClockOutputDivide(uint8_t u8Divide)
{
    SIM->SOPT = (SIM->SOPT & ~(SIM_SOPT_BUSREF_MASK)) | SIM_SOPT_BUSREF(u8Divide & 0x07);    
}
/*****************************************************************************//*!
*
* @brief UART0_RX输入信号连接到UART0模块和ETM0通道1
*        
* @param  none       
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void SIM_EnableUART0RXDConnectETMOCH1(void)
{
    SIM->SOPT |= (SIM_SOPT_RXDCE_MASK);    
}
/*****************************************************************************//*!
*
* @brief  UART0_TX输出在映射到引出线前由ETM0通道0调制
*        
* @param  none       
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void SIM_EnableUART0Modulation(void)
{
    SIM->SOPT |= (SIM_SOPT_TXDME_MASK);    
}

/*****************************************************************************//*!
*
* @brief  UART0_TX输出直接连接到引出线上
*        
* @param  none       
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void SIM_DisableUART0Modulation(void)
{
    SIM->SOPT &= ~(SIM_SOPT_TXDME_MASK);    
}
/*****************************************************************************//*!
*
* @brief 生成ETM2模块的PWM同步触发
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_GenerateSoftwareTrig2ETM2(void)
{
    SIM->SOPT |= (SIM_SOPT_ETMSYNC_MASK);    
}
/*****************************************************************************//*!
*
* @brief ETM2_CH3通道映射到PD1上  
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM2CH3Pin(void)
{
    SIM->PINSEL |= SIM_PINSEL_ETM2PS3_MASK;    
}

/*****************************************************************************//*!
*
* @brief  ETM2_CH2通道映射到PD0上
*        
* @param   none
*
* @return  none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM2CH2Pin(void)
{
    SIM->PINSEL |= SIM_PINSEL_ETM2PS2_MASK;    
}
/*****************************************************************************//*!
*
* @brief  ETM0_CH1通道映射到PB3上  
*        
* @param   none
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM0CH1Pin(void)
{
    SIM->PINSEL |= SIM_PINSEL_ETM0PS1_MASK;    
}
/*****************************************************************************//*!
*
* @brief   ETM0_CH0通道映射到PB2上 
*        
* @param   none
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM0CH0Pin(void)
{
    SIM->PINSEL |= SIM_PINSEL_ETM0PS0_MASK;    
}
/*****************************************************************************//*!
*
* @brief  UART0_RX和UART0_TX映射到PA2和PA3上 
*        
* @param   none
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void SIM_RemapUART0Pin(void)
{
    SIM->PINSEL |= SIM_PINSEL_UART0PS_MASK;    
}

/*****************************************************************************//*!
*
* @brief SPI0_SCK SPI0_MOSI SPI0_MISO和SPI0_PCS映射到PE0、PE1、PE2、PE3上 
*        
* @param   none
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void SIM_RemapSPI0Pin(void)
{
    SIM->PINSEL |= SIM_PINSEL_SPI0PS_MASK;    
}

/*****************************************************************************//*!
*
* @brief  I2C0_SCL和I2C_SDA分别映射到PB7、PB6上
*        
* @param   none
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void SIM_RemapI2CPin(void)
{
    SIM->PINSEL |= SIM_PINSEL_IICPS_MASK;    
}
/*****************************************************************************//*!
*
* @brief RXD0输入信号由ACPM0滤波，然后注入UART0 
*        
* @param  none       
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void SIM_EnableUART0Filter(void)
{
    SIM->SOPT |= (SIM_SOPT_RXDFE_MASK);    
}
/******************************************************************************!
*
* @brief RXD0输入信号直接连接到UARTO模块
*        
* @param  none       
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void SIM_DisableUART0Filter(void)
{
    SIM->SOPT &= ~(SIM_SOPT_RXDFE_MASK);    
}
/*****************************************************************************//*!
*
* @brief 选择RTC溢出作为ADC硬件触发源
*        
* @param  none        
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void SIM_TriggerADCByRTC(void)
{
    SIM->SOPT &= ~(SIM_SOPT_ADHWT_MASK);    
}
/*****************************************************************************//*!
*
* @brief 选择PIT溢出作为ADC硬件触发源 
*        
* @param  none       
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void SIM_TriggerADCByPIT(void)
{
    SIM->SOPT = (SIM->SOPT & ~(SIM_SOPT_ADHWT_MASK)) | SIM_SOPT_ADHWT(1);    
}
/*****************************************************************************//*!
*
* @brief 设置ETM2初始化作为ADC硬件触发源.ETM2初始化后经过一段时间延时触发ADC转换
*        
* @param  none      
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void SIM_TriggerADCByETM2Init(void)
{
    SIM->SOPT = (SIM->SOPT & ~(SIM_SOPT_ADHWT_MASK)) | SIM_SOPT_ADHWT(2);    
}

/*****************************************************************************//*!
*
* @brief 设置ETM2匹配作为ADC硬件触发源，ETM2匹配后经过一段时间的延时触发ADC转换
*        
* @param  none       
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void SIM_TriggerADCByETM2Match(void)
{
    SIM->SOPT = (SIM->SOPT & ~(SIM_SOPT_ADHWT_MASK)) | SIM_SOPT_ADHWT(3);    
}
/*****************************************************************************//*!
*
* @brief RTC溢出连接到ETM1输入通道1
*        
* @param  none       
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void SIM_EnableRTCCapture(void)
{
    SIM->SOPT |= (SIM_SOPT_RTCC_MASK);    
}
/*****************************************************************************//*!
*
* @brief RTC溢出未连接到ETM1输入通道1
*        
* @param  none       
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void SIM_DisableRTCCapture(void)
{
    SIM->SOPT &= ~(SIM_SOPT_RTCC_MASK);    
}
/*****************************************************************************//*!
*
* @brief ACMP0输出连接到ETM1输入通道0
*        
* @param  none      
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void SIM_EnableACMP0InputCapture(void)
{
    SIM->SOPT |= (SIM_SOPT_ACIC_MASK);    
}
/*****************************************************************************//*!
*
* @brief ACMP0输出未连接到ETM1输入通道0 
*        
* @param  none      
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void SIM_DisableACMP0InputCapture(void)
{
    SIM->SOPT &= ~(SIM_SOPT_ACIC_MASK);    
}
/*****************************************************************************//*!
*
* @brief RTC0映射到PC5上
*        
* @param   none
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void SIM_RemapRTCPin(void)
{
    SIM->PINSEL |= SIM_PINSEL_RTCPS_MASK;    
}
/*****************************************************************************//*!
*
* @brief 设置总线时钟频率
*        
* @param   none
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void SIM_SetBusDivide(uint8_t u8Divide)
{
    SIM->BUSDIV = u8Divide;    
}
/*****************************************************************************//*!
*
* @brief ETM2_CH1通道映射到PH1上
*        
* @param   none
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM2CH1Pin(void)
{
    SIM->PINSEL |= SIM_PINSEL_ETM2PS1_MASK;    
}

/*****************************************************************************//*!
*
* @brief  ETM2_CH0通道映射到PH0上  
*        
* @param   none
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM2CH0Pin(void)
{
    SIM->PINSEL |= SIM_PINSEL_ETM2PS0_MASK;    
}

/*****************************************************************************//*!
*
* @brief  ETM1_CH1通道映射到PE7上
*        
* @param   none
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM1CH1Pin(void)
{
    SIM->PINSEL |= SIM_PINSEL_ETM1PS1_MASK;    
}

/*****************************************************************************//*!
*
* @brief  ETM1_CH0映射到PH2上
*        
* @param   none
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM1CH0Pin(void)
{
    SIM->PINSEL |= SIM_PINSEL_ETM1PS0_MASK;    
}

#endif

/****************************************************************************/

void SIM_Init(SIM_ConfigType *pConfig);
void SIM_SetClockGating(uint32_t u32PeripheralMask, uint8_t u8GateOn);
uint32_t SIM_GetStatus(uint32_t u32StatusMask);
uint8_t SIM_ReadID(IDType sID);

#endif 


