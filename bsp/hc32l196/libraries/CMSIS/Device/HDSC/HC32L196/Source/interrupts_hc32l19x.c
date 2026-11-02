/******************************************************************************
* Copyright (C) 2019, Huada Semiconductor Co.,Ltd All rights reserved.
*
* This software is owned and published by:
* Huada Semiconductor Co.,Ltd ("HDSC").
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with HDSC
* components. This software is licensed by HDSC to be adapted only
* for use in systems utilizing HDSC components. HDSC shall not be
* responsible for misuse or illegal use of this software for devices not
* supported herein. HDSC is providing this software "AS IS" and will
* not be responsible for issues arising from incorrect user implementation
* of the software.
*
* Disclaimer:
* HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
* REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
* ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
* WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
* WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
* WARRANTY OF NONINFRINGEMENT.
* HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
* NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
* LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
* INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
* SAVINGS OR PROFITS,
* EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
* INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
* FROM, THE SOFTWARE.
*
* This software may be replicated in part or whole for the licensed use,
* with the restriction that this Disclaimer and Copyright notice must be
* included with each copy of this software, whether used in part or whole,
* at all times.
*/
/******************************************************************************/
/** \file interrupts_hc32l136.c
 **
 ** Interrupt management
 ** @link Driver Group Some description @endlink
 **
 **   - 2018-04-15  1.0  Lux     First version.
 **
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32l196_ddl.h"
#include "interrupts_hc32l19x.h"

/*******************************************************************************
 *                       IRQ WEAK DEFINE
 ******************************************************************************/
__WEAK void SysTick_IRQHandler(void);

__WEAK void PortA_IRQHandler(void)
{

}

__WEAK void PortB_IRQHandler(void)
{

}

__WEAK void PortC_IRQHandler(void)
{

}

__WEAK void PortD_IRQHandler(void)
{

}

__WEAK void PortE_IRQHandler(void)
{

}

__WEAK void PortF_IRQHandler(void)
{

}

__WEAK void Dmac_IRQHandler(void)
{

}

__WEAK void Tim3_IRQHandler(void)
{

}


__WEAK void Uart0_IRQHandler(void)
{

}

__WEAK void Uart1_IRQHandler(void)
{

}

__WEAK void Uart2_IRQHandler(void)
{

}

__WEAK void Uart3_IRQHandler(void)
{

}

__WEAK void LpUart0_IRQHandler(void)
{

}

__WEAK void LpUart1_IRQHandler(void)
{

}

__WEAK void Spi0_IRQHandler(void)
{

}

__WEAK void Spi1_IRQHandler(void)
{

}

__WEAK void I2c0_IRQHandler(void)
{

}

__WEAK void I2c1_IRQHandler(void)
{

}

__WEAK void Tim0_IRQHandler(void)
{

}

__WEAK void Tim1_IRQHandler(void)
{

}

__WEAK void Tim2_IRQHandler(void)
{

}

__WEAK void LpTim0_IRQHandler(void)
{

}

__WEAK void LpTim1_IRQHandler(void)
{

}

__WEAK void Tim4_IRQHandler(void)
{

}

__WEAK void Tim5_IRQHandler(void)
{

}

__WEAK void Tim6_IRQHandler(void)
{

}

__WEAK void Pca_IRQHandler(void)
{

}

__WEAK void Wdt_IRQHandler(void)
{

}

__WEAK void Rtc_IRQHandler(void)
{

}

__WEAK void Adc_IRQHandler(void)
{

}

__WEAK void Dac_IRQHandler(void)
{

}

__WEAK void Pcnt_IRQHandler(void)
{

}

__WEAK void Vc0_IRQHandler(void)
{

}

__WEAK void Vc1_IRQHandler(void)
{

}

__WEAK void Vc2_IRQHandler(void)
{

}

__WEAK void Lvd_IRQHandler(void)
{

}

__WEAK void Lcd_IRQHandler(void)
{

}

__WEAK void Flash_IRQHandler(void)
{

}

__WEAK void Ram_IRQHandler(void)
{

}

__WEAK void ClkTrim_IRQHandler(void)
{

}


/**
 *******************************************************************************
 ** \brief NVIC 中断使能
 **
 ** \param [in]  enIrq          中断号枚举类型
 ** \param [in]  enLevel        中断优先级枚举类型
 ** \param [in]  bEn            中断开关
 ** \retval    Ok       设置成功
 **            其他值   设置失败
 ******************************************************************************/
void EnableNvic(IRQn_Type enIrq, en_irq_level_t enLevel, boolean_t bEn)
{
    NVIC_ClearPendingIRQ(enIrq);
    NVIC_SetPriority(enIrq, enLevel);
    if (TRUE == bEn)
    {
        NVIC_EnableIRQ(enIrq);
    }
    else
    {
        NVIC_DisableIRQ(enIrq);
    }
}

/**
 *******************************************************************************
 ** \brief NVIC hardware fault 中断实现
 **        
 **
 ** \retval
 ******************************************************************************/
//void HardFault_Handler(void)
//{    
//    volatile int a = 0;

//    while( 0 == a)
//    {
//        ;
//    }
//    
//}


/**
 *******************************************************************************
 ** \brief NVIC SysTick 中断实现
 **
 ** \retval
 ******************************************************************************/
//void SysTick_Handler(void)
//{
//   SysTick_IRQHandler();
//}

/**
 *******************************************************************************
 ** \brief GPIO PortA 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void PORTA_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_PORTA)    
    PortA_IRQHandler();
#endif    
}

/**
 *******************************************************************************
 ** \brief GPIO PortB 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void PORTB_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_PORTB)    
    PortB_IRQHandler();
#endif    
}

/**
 *******************************************************************************
 ** \brief GPIO PortC/E 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void PORTC_E_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_PORTC)    
    PortC_IRQHandler();
#endif
    
#if (INT_CALLBACK_ON == INT_CALLBACK_PORTE)    
    PortE_IRQHandler();
#endif    
}

/**
 *******************************************************************************
 ** \brief GPIO PortD/F 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void PORTD_F_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_PORTD)    
    PortD_IRQHandler();
#endif
    
#if (INT_CALLBACK_ON == INT_CALLBACK_PORTF)    
    PortF_IRQHandler();
#endif    
}

/**
 *******************************************************************************
 ** \brief DMAC  中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void DMAC_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_DMAC)    
    Dmac_IRQHandler();
#endif    
}

/**
 *******************************************************************************
 ** \brief TIM3 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void TIM3_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_TIM3)    
    Tim3_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief UART0/2 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void UART0_2_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_UART0)    
    Uart0_IRQHandler();
#endif 
    
#if (INT_CALLBACK_ON == INT_CALLBACK_UART2)    
    Uart2_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief UART1/3 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void UART1_3_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_UART1)    
    Uart1_IRQHandler();
#endif  
    
#if (INT_CALLBACK_ON == INT_CALLBACK_UART3)    
    Uart3_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief LPUART0 低功耗串口0 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void LPUART0_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_LPUART0)    
    LpUart0_IRQHandler();
#endif    
}

/**
 *******************************************************************************
 ** \brief LPUART1 低功耗串口1 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void LPUART1_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_LPUART1)    
    LpUart1_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief SPI0 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void SPI0_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_SPI0)    
    Spi0_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief SPI1 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void SPI1_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_SPI1)    
    Spi1_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief I2C0 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void I2C0_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_I2C0)    
    I2c0_IRQHandler();
#endif    
}

/**
 *******************************************************************************
 ** \brief I2C1 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void I2C1_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_I2C1)    
    I2c1_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief TIM0 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void TIM0_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_TIM0)    
    Tim0_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief TIM1 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void TIM1_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_TIM1)    
    Tim1_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief TIM2 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void TIM2_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_TIM2)    
    Tim2_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief LPTIM0/1 低功耗时钟 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void LPTIM0_1_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_LPTIM0)
    LpTim0_IRQHandler();
#endif
    
#if (INT_CALLBACK_ON == INT_CALLBACK_LPTIM1)
    LpTim1_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief TIM4 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void TIM4_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_TIM4)    
    Tim4_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief TIM5 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void TIM5_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_TIM5)
    Tim5_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief TIM6 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void TIM6_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_TIM6)
    Tim6_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief PCA 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void PCA_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_PCA)
    Pca_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief WDT 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void WDT_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_WDT)
    Wdt_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief RTC 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void RTC_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_RTC)
    Rtc_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief ADC/DAC 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void ADC_DAC_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_ADC)
    Adc_IRQHandler();
#endif
    
#if (INT_CALLBACK_ON == INT_CALLBACK_DAC)
    Dac_IRQHandler();    
#endif
}

/**
 *******************************************************************************
 ** \brief PCNT 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void PCNT_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_PCNT)
    Pcnt_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief VC0 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void VC0_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_VC0)
    Vc0_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief VC1/2 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void VC1_2_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_VC1)
    Vc1_IRQHandler();
#endif
    
#if (INT_CALLBACK_ON == INT_CALLBACK_VC2)
    Vc2_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief LVD 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void LVD_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_LVD)
    Lvd_IRQHandler();    
#endif
}

/**
 *******************************************************************************
 ** \brief LCD 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void LCD_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_LCD)
    Lcd_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief FLASH/RAM 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void FLASH_RAM_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_FLASH)
    Flash_IRQHandler();
#endif    
    
#if (INT_CALLBACK_ON == INT_CALLBACK_RAM)
    Ram_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief CLKTRIM 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void CLKTRIM_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_CLKTRIM)
    ClkTrim_IRQHandler();
#endif
}

/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/
