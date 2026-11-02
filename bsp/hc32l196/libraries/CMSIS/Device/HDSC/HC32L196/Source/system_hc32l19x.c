/*******************************************************************************
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
/** \file system_hc32l136.c
 **
 ** System clock initialization.
 ** @link SampleGroup Some description @endlink
 **
 **   - 2019-03-01  1.0  Lux First version.
 **
 ******************************************************************************/

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "base_types.h"
#include "hc32l19x.h"
#include "system_hc32l19x.h"
#include "hc32l196_sysctrl.h"

/**
 ******************************************************************************
 ** System Clock Frequency (Core Clock) Variable according CMSIS
 ******************************************************************************/
uint32_t SystemCoreClock = 4000000;


//add clock source.
void SystemCoreClockUpdate (void) // Update SystemCoreClock variable
{
    SystemCoreClock = Sysctrl_GetHClkFreq();
}

/**
 ******************************************************************************
 ** \brief  对MCU未引出IO端口进行默认配置.
 **
 ** \param  none
 ** \return none
 ******************************************************************************/
static void _InitHidePin(void)
{
    uint32_t tmpReg = M0P_SYSCTRL->PERI_CLKEN0;
	
	M0P_SYSCTRL->PERI_CLKEN0_f.GPIO = 1;
	
#if defined(HC32L19xPxxx)	      //100PIN MCU	  
	M0P_GPIO->PFADS &= 0xFF4F;  ///< PF04/PF05/PF07配置为数字端口    
	
    M0P_GPIO->PFDIR	|= 0x00B0;  ///< PF04/PF05/PF07配置为端口输入	
	  
	M0P_GPIO->PFPU  |= 0x00B0;  ///< PF04/PF05/PF07配置为上拉
	
#elif defined(HC32L19xMxxx)     //80PIN MCU	  
	M0P_GPIO->PDADS &= 0x0F1F;  ///< PD05~07/PD12~15配置为数字端口	  
	M0P_GPIO->PEADS &= 0x783C;  ///< PE00/PE01/PE06~10/PE15配置为数字端口	  
	M0P_GPIO->PFADS &= 0xF9F3;  ///< PF02/PF03/PF09/PF10配置为数字端口	
    
    M0P_GPIO->PDDIR	|= 0xF0E0;  ///< PD05~07/PD12~15配置为端口输入    
	M0P_GPIO->PEDIR	|= 0x87C3;  ///< PE00/PE01/PE06~10/PE15配置为端口输入	  
	M0P_GPIO->PFDIR	|= 0x060C;  ///< PF02/PF03/PF09/PF10配置为数字端口
	
	  
	M0P_GPIO->PDPU  |= 0xF0E0;  ///< PD05~07/PD12~15配置为上拉	  
	M0P_GPIO->PEPU  |= 0x87C3;  ///< PE00/PE01/PE06~10/PE15配置为上拉	  
	M0P_GPIO->PFPU  |= 0x060C;  ///< PF02/PF03/PF09/PF10配置为数字端口
		
#elif defined(HC32L19xKxxx)     //64PIN MCU	  
	M0P_GPIO->PDADS &= 0x0004;  ///< PD00/PD01/PD03~15配置为数字端口	  
	M0P_GPIO->PEADS &= 0x0000;  ///< PE00~15配置为数字端口	  
	M0P_GPIO->PFADS &= 0xF9F3;  ///< PF02/PF03/PF09/PF10配置为数字端口	
    
	M0P_GPIO->PDDIR	|= 0xFFFB;  ///< PD00/PD01/PD03~15配置为端口输入    
	M0P_GPIO->PEDIR	|= 0xFFFF;  ///< PE00~15配置为端口输入	  
	M0P_GPIO->PFDIR	|= 0x060C;  ///< PF02/PF03/PF09/PF10配置为数字端口	
	  
	M0P_GPIO->PDPU  |= 0xFFFB;  ///< PD00/PD01/PD03~15配置为上拉	  
	M0P_GPIO->PEPU  |= 0xFFFF;  ///< PE00~15配置为上拉	  
	M0P_GPIO->PFPU  |= 0x060C;  ///< PF02/PF03/PF09/PF10配置为数字端口
		
#elif defined(HC32L19xJxxx)     //48PIN MCU	  
	M0P_GPIO->PCADS &= 0xE000;  ///< PC00~12配置为数字端口	  
	M0P_GPIO->PDADS &= 0x0000;  ///< PD00~15配置为数字端口	  
	M0P_GPIO->PEADS &= 0x0000;  ///< PE00~15配置为数字端口	  
	M0P_GPIO->PFADS &= 0xF9C3;  ///< PF02~05/PF09/PF10配置为数字端口	
    
	M0P_GPIO->PCDIR	|= 0x1FFF;  ///< PC00~12配置为端口输入    
	M0P_GPIO->PDDIR	|= 0xFFFF;  ///< PD00~15配置为端口输入    
	M0P_GPIO->PEDIR	|= 0xFFFF;  ///< PE00~15配置为端口输入	  
	M0P_GPIO->PFDIR	|= 0x063C;  ///< PF02~05/PF09/PF10配置为数字端口
	
	  
	M0P_GPIO->PCPU  |= 0x1FFF;  ///< PC00~12配置为上拉	  
	M0P_GPIO->PDPU  |= 0xFFFF;  ///< PD00~15配置为上拉	  
    M0P_GPIO->PEPU  |= 0xFFFF;  ///< PE00~15配置为上拉	  
	M0P_GPIO->PFPU  |= 0x063C;  ///< PF02~05/PF09/PF10配置为数字端口
		
#elif defined(HC32L19xFxxx)     //32PIN MCU	  
	M0P_GPIO->PAADS &= 0xFFF4;  ///< PA00/PA01/PA03配置为数字端口	  
	M0P_GPIO->PBADS &= 0x08FB;  ///< PB02/PB08~10/PB12~15配置为数字端口	  
	M0P_GPIO->PCADS &= 0xC000;  ///< PC00~13配置为数字端口	  
	M0P_GPIO->PDADS &= 0x0000;  ///< PD00~15配置为数字端口	  
	M0P_GPIO->PEADS &= 0x0000;  ///< PE00~15配置为数字端口	  
    M0P_GPIO->PFADS &= 0xF903;  ///< PF02~07/PF09/PF10配置为数字端口	
    
	M0P_GPIO->PADIR	|= 0x000B;  ///< PA00/PA01/PA03配置为端口输入    
	M0P_GPIO->PBDIR	|= 0xF704;  ///< PB02/PB08~10/PB12~15配置为端口输入    
	M0P_GPIO->PCDIR	|= 0x3FFF;  ///< PC00~13配置为端口输入    
	M0P_GPIO->PDDIR	|= 0xFFFF;  ///< PD00~15配置为端口输入    
	M0P_GPIO->PEDIR	|= 0xFFFF;  ///< PE00~15配置为端口输入	  
	M0P_GPIO->PFDIR	|= 0x06FC;  ///< PF02~07/PF09/PF10配置为数字端口	
	  
	M0P_GPIO->PAPU  |= 0x000B;  ///< PA00/PA01/PA03配置为上拉	  
	M0P_GPIO->PBPU  |= 0xF704;  ///< PB02/PB08~10/PB12~15配置为上拉	  
	M0P_GPIO->PCPU  |= 0x3FFF;  ///< PC00~13配置为上拉	  
	M0P_GPIO->PDPU  |= 0xFFFF;  ///< PD00~15配置为上拉	  
	M0P_GPIO->PEPU  |= 0xFFFF;  ///< PE00~15配置为上拉	  
	M0P_GPIO->PFPU  |= 0x06FC;  ///< PF02~07/PF09/PF10配置为数字端口
    
#endif
	
	M0P_SYSCTRL->PERI_CLKEN0 = tmpReg;
}

/**
 ******************************************************************************
 ** \brief  Setup the microcontroller system. Initialize the System and update
 ** the SystemCoreClock variable.
 **
 ** \param  none
 ** \return none
 ******************************************************************************/
void SystemInit(void)
{
    M0P_SYSCTRL->RCL_CR_f.TRIM = (*((volatile uint16_t*) (0x00100C22ul)));
    M0P_SYSCTRL->RCH_CR_f.TRIM = (*((volatile uint16_t*) (0x00100C08ul)));
    SystemCoreClockUpdate();
	_InitHidePin();
}

