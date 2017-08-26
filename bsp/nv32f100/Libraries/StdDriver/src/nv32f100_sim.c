/*************************************************************************!     
 *     技术讨论：QQ群  123763203
 *     官网    ：www.navota.com
 *
 * @file       sim.c
 * @brief      系统集成模块（SIM)函数库
 * @author     Navota
 * @date       2017-1-1
 *************************************************************************/
#include "nv32f100.h"


#if defined(CPU_NV32)
/*****************************************************************************//*!
   *
   * @ 初始化SIM寄存器.
   * 
   * @ 输入 pConfig   指向SIM配置结构体.  
   *
   * @ 无返回
   * 
   * @ 成功/失败 标准： 无
   *
   * @ 参看  SIM_ConfigType
   *
   *****************************************************************************/
void SIM_Init(SIM_ConfigType *pConfig)
{
    uint32_t    u32Sopt;
    uint32_t    u32PinSel;
    uint32_t    u32Scgc;
    uint32_t    u32BusDiv;
    /*
     * 初始化SIM寄存器
     */
    u32Sopt     = 0x0010000E; /*使能SWD、RESET、NMI引脚 */
    u32PinSel   = 0;
    u32Scgc     = 0x00003000;  /* 使能SWD、FLASH模块的总线时钟 */
    u32BusDiv   = 0;
    u32BusDiv = pConfig->sBits.bBusDiv;    /*总线时钟分频值*/ 
    if(pConfig->sBits.bDisableNMI)     /*禁用NMI引脚*/
    {
        u32Sopt &= ~SIM_SOPT_NMIE_MASK;        
    }
    if(pConfig->sBits.bDisableRESET)    /*禁用RSTPE引脚*/
    {
        u32Sopt &= ~SIM_SOPT_RSTPE_MASK;        
    }   
    if(pConfig->sBits.bDisableSWD)     /*禁用SWDE引脚*/
    {
        u32Sopt &= ~SIM_SOPT_SWDE_MASK;        
    } 
    if(pConfig->sBits.bEnableCLKOUT)  /*使能总线时钟*/
    {
        u32Sopt |= SIM_SOPT_CLKOE_MASK;        
    } 
    if(pConfig->sBits.bETMSYNC)        /*ETM2同步选择*/
    {
        u32Sopt |= SIM_SOPT_ETMSYNC_MASK;  /*生成ETM2模块的PWM同步触发*/   
    }  
    if(pConfig->sBits.bRXDCE)    /*UAT0_RX捕捉选择*/
    {
        u32Sopt |= SIM_SOPT_RXDCE_MASK;  /*UAT0_RX输入信号接到UART0模块和ETM0通道1*/       
    }
    if(pConfig->sBits.bTXDME)   /*URAT0_TX捕捉选择*/
    {
        u32Sopt |= SIM_SOPT_TXDME_MASK;  /*URAT0_TX输出映射到引出线前由ETM0通道调制*/     
    }
    if(pConfig->sBits.bACIC)             /*模拟比较器至输入捕获使能*/
    {
        u32Sopt |= SIM_SOPT_ACIC_MASK;    /* ACMP0输出连接到ETM1输出通道0*/
    }
        if(pConfig->sBits.bRTCC)
    {
        u32Sopt |= SIM_SOPT_RTCC_MASK;    /*RTC溢出连接到ETM1输入通道*/    
    }
        if(pConfig->sBits.bRXDFE)         /*URT0 RxD滤波器选择*/ 
    {
        u32Sopt |= SIM_SOPT_RXDFE_MASK;   /*RXD0输入信号由ACMP0滤波，然后注入UART0*/   
    }
    u32Sopt |= ((pConfig->u8BusRef & 0x07) << 16);  /*总线时钟128分频*/  
    u32Sopt |= ((pConfig->u8Delay) << 24);         /*设置从ETM2初始化/匹配到触发ADC转换的延时时间*/
    u32Sopt |= ((pConfig->sBits.u8ADHWT & 0x03) << 8);/*选择ETM2匹配作为ADC转换的硬件触发源*/
    u32PinSel = pConfig->u32PinSel;
    u32Scgc = pConfig->u32SCGC;   
    
   /*写数据到SIM模块寄存器 */
    SIM->SOPT = u32Sopt;
    SIM->PINSEL = u32PinSel;
    SIM->SCGC = u32Scgc; 
    SIM->BUSDIV = u32BusDiv;
}
#endif

/*****************************************************************************//*!
   *
   * @ 设置SIM时钟选通控制寄存器，使能或者禁用外设总线时钟
   * 
   * @ 输入  u32PeripheralMask    外设时钟掩码
   * @ 输入  u8GateOn             1:开启, 0:关闭.  
   *
   * @ 无返回
   *  
   * @ 成功/失败 标准： 无
   *
   *****************************************************************************/

void SIM_SetClockGating(uint32_t u32PeripheralMask, uint8_t u8GateOn)
{
    uint32_t    u32Scgc;

    /*
     * 
     * 保存初始时时钟控制寄存器的值
     */
    u32Scgc     = SIM->SCGC;
    
    if(u8GateOn)
    {
        u32Scgc |= u32PeripheralMask;
    }
    else
    {
        u32Scgc &= ~u32PeripheralMask;        
    }

    SIM->SCGC = u32Scgc;
}

/*****************************************************************************//*!
   *
   * @ 读取相应的状态标志位.
   * 
   * @ 输入  u32StatusMask    指示要被读取的状态
   *
   * @ 返回状态.
   * 
   * @ 成功/失败 标准： 无
	 *
   *****************************************************************************/

uint32_t SIM_GetStatus(uint32_t u32StatusMask)
{
    uint32_t    u32Status;

    u32Status = SIM->SRSID & u32StatusMask;  //读取状态标志位
    return (u32Status);
}

/*****************************************************************************//*!
   *
   * @ 读相应的ID寄存器.
   * 
   * @ 输入  u8ID    ID的类型. 
   *
   * @ 返回 ID
   *
   * @ 成功/失败 标准： 无
   *
   * 参看 IDType
   *
   *****************************************************************************/
uint8_t SIM_ReadID(IDType sID)
{
    uint32_t    u32ID;
    uint8_t u8IDOffset[4] = 
    { 
        28, 24, 20,16
    };  
    u32ID = (SIM->SRSID >> u8IDOffset[sID]) & 0x0F;   //读取ID
    return (u32ID);
}




