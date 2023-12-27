/******************************************************************************************************************************************
* 文件名称: SWM341_iofilt.c
* 功能说明: SWM341单片机的IO滤波器功能模块，对PAD到模块输入间的信号滤波，窄于指定宽度的脉冲视作毛刺，忽略
* 技术支持: http://www.synwit.com.cn/e/tool/gbook/?bid=1
* 注意事项:
* 版本日期: V1.0.0      2016年1月30日
* 升级记录:
*
*
*******************************************************************************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION
* REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, SYNWIT SHALL NOT BE HELD LIABLE
* FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT
* OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONN-
* -ECTION WITH THEIR PRODUCTS.
*
* COPYRIGHT 2012 Synwit Technology
*******************************************************************************************************************************************/
#include "SWM341.h"
#include "SWM341_iofilt.h"


static uint32_t Width[2];


/******************************************************************************************************************************************
* 函数名称: IOFILT_Init()
* 功能说明: IO滤波器初始化
* 输    入: uint32_t IOFILTn  要初始化的滤波器，可取值 0-1
*           uint32_t signal     要对哪个信号进行滤波操作，可取值 IOFILT0_PB5、IOFILT0_PB4、...
*           uint32_t width      被选信号上宽度小于 width 个 HRC 时钟周期的脉冲被视作毛刺，过滤掉，可取值 IOFILT_WIDTH_2、IOFILT_WIDTH_4、...
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void IOFILT_Init(uint32_t IOFILTn, uint32_t signal, uint32_t width)
{
    SYS->CLKSEL &= ~SYS_CLKSEL_IOFILT_Msk;
    SYS->CLKSEL |= (0 << SYS_CLKSEL_IOFILT_Pos);    //滤波器时钟源：HRC

    SYS->CLKEN1 |= (1 << SYS_CLKEN1_IOFILT_Pos);

    *(&SYS->IOFILT0 + IOFILTn) = (signal << SYS_IOFILT_IOSEL_Pos)  |
                                 (0      << SYS_IOFILT_CLKDIV_Pos) |
                                 (width  << SYS_IOFILT_TIM_Pos);

    Width[IOFILTn] = width;
}

/******************************************************************************************************************************************
* 函数名称: IOFILT_Open()
* 功能说明: IO滤波器开启
* 输    入: uint32_t IOFILTn  要初始化的滤波器，可取值 0-1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void IOFILT_Open(uint32_t IOFILTn)
{
    *(&SYS->IOFILT0 + IOFILTn) |= (Width[IOFILTn] << SYS_IOFILT_TIM_Pos);
}

/******************************************************************************************************************************************
* 函数名称: IOFILT_Close()
* 功能说明: IO滤波器关闭，即不滤波，PAD上的信号直接进入模块
* 输    入: uint32_t IOFILTn  要初始化的滤波器，可取值 0-1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void IOFILT_Close(uint32_t IOFILTn)
{
    *(&SYS->IOFILT0 + IOFILTn) &= ~SYS_IOFILT_TIM_Msk;
}
