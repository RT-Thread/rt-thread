/****************************************************************************************************************************************** 
* 文件名称: SWM320_timr.c
* 功能说明:	SWM320单片机的计数器/定时器功能驱动库
* 技术支持:	http://www.synwit.com.cn/e/tool/gbook/?bid=1
* 注意事项:
* 版本日期:	V1.1.0		2017年10月25日
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
#include "SWM320.h"
#include "SWM320_timr.h"


/****************************************************************************************************************************************** 
* 函数名称: TIMR_Init()
* 功能说明:	TIMR定时器/计数器初始化
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，有效值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4、TIMR5
*			uint32_t mode			TIMR_MODE_TIMER 定时器模式    TIMR_MODE_COUNTER 计数器模式
*			uint32_t period			定时/计数周期
*			uint32_t int_en			中断使能
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_Init(TIMR_TypeDef * TIMRx, uint32_t mode, uint32_t period, uint32_t int_en)
{
	SYS->CLKEN |= (0x01 << SYS_CLKEN_TIMR_Pos);
	
	TIMR_Stop(TIMRx);	//一些关键寄存器只能在定时器停止时设置
	
	TIMRx->CTRL &= ~TIMR_CTRL_CLKSRC_Msk;
	TIMRx->CTRL |= mode << TIMR_CTRL_CLKSRC_Pos;
	
	TIMRx->LDVAL = period;
	
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMRG->IF = (1 << TIMRG_IF_TIMR0_Pos);		//使能中断前清除中断标志
		TIMRG->IE &= ~TIMRG_IE_TIMR0_Msk;
		TIMRG->IE |= (int_en << TIMRG_IE_TIMR0_Pos);
	
		if(int_en) NVIC_EnableIRQ(TIMR0_IRQn);
		break;
	
	case ((uint32_t)TIMR1):
		TIMRG->IF = (1 << TIMRG_IF_TIMR1_Pos);
		TIMRG->IE &= ~TIMRG_IE_TIMR1_Msk;
		TIMRG->IE |= (int_en << TIMRG_IE_TIMR1_Pos);
	
		if(int_en) NVIC_EnableIRQ(TIMR1_IRQn);
		break;
	
	case ((uint32_t)TIMR2):
		TIMRG->IF = (1 << TIMRG_IF_TIMR2_Pos);
		TIMRG->IE &= ~TIMRG_IE_TIMR2_Msk;
		TIMRG->IE |= (int_en << TIMRG_IE_TIMR2_Pos);
	
		if(int_en) NVIC_EnableIRQ(TIMR2_IRQn);
		break;
	
	case ((uint32_t)TIMR3):
		TIMRG->IF = (1 << TIMRG_IF_TIMR3_Pos);
		TIMRG->IE &= ~TIMRG_IE_TIMR3_Msk;
		TIMRG->IE |= (int_en << TIMRG_IE_TIMR3_Pos);
	
		if(int_en) NVIC_EnableIRQ(TIMR3_IRQn);
		break;
	
	case ((uint32_t)TIMR4):
		TIMRG->IF = (1 << TIMRG_IF_TIMR4_Pos);
		TIMRG->IE &= ~TIMRG_IE_TIMR4_Msk;
		TIMRG->IE |= (int_en << TIMRG_IE_TIMR4_Pos);
	
		if(int_en) NVIC_EnableIRQ(TIMR4_IRQn);
		break;
	
	case ((uint32_t)TIMR5):
		TIMRG->IF = (1 << TIMRG_IF_TIMR5_Pos);
		TIMRG->IE &= ~TIMRG_IE_TIMR5_Msk;
		TIMRG->IE |= (int_en << TIMRG_IE_TIMR5_Pos);
	
		if(int_en) NVIC_EnableIRQ(TIMR5_IRQn);
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMR_Start()
* 功能说明:	启动定时器，从初始值开始计时/计数
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4、TIMR5
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_Start(TIMR_TypeDef * TIMRx)
{
	TIMRx->CTRL |= TIMR_CTRL_EN_Msk;
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMR_Stop()
* 功能说明:	停止定时器
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4、TIMR5
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_Stop(TIMR_TypeDef * TIMRx)
{
	TIMRx->CTRL &= ~TIMR_CTRL_EN_Msk;
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMR_Halt()
* 功能说明:	暂停定时器，计数值保持不变
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4、TIMR5
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_Halt(TIMR_TypeDef * TIMRx)
{
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMRG->HALT |= (0x01 << TIMRG_HALT_TIMR0_Pos);
		break;
	
	case ((uint32_t)TIMR1):
		TIMRG->HALT |= (0x01 << TIMRG_HALT_TIMR1_Pos);
		break;
	
	case ((uint32_t)TIMR2):
		TIMRG->HALT |= (0x01 << TIMRG_HALT_TIMR2_Pos);
		break;
	
	case ((uint32_t)TIMR3):
		TIMRG->HALT |= (0x01 << TIMRG_HALT_TIMR3_Pos);
		break;
	
	case ((uint32_t)TIMR4):
		TIMRG->HALT |= (0x01 << TIMRG_HALT_TIMR4_Pos);
		break;
	
	case ((uint32_t)TIMR5):
		TIMRG->HALT |= (0x01 << TIMRG_HALT_TIMR5_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMR_Resume()
* 功能说明:	恢复定时器，从暂停处继续计数
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4、TIMR5
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_Resume(TIMR_TypeDef * TIMRx)
{
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMRG->HALT &= ~(0x01 << TIMRG_HALT_TIMR0_Pos);
		break;
	
	case ((uint32_t)TIMR1):
		TIMRG->HALT &= ~(0x01 << TIMRG_HALT_TIMR1_Pos);
		break;
	
	case ((uint32_t)TIMR2):
		TIMRG->HALT &= ~(0x01 << TIMRG_HALT_TIMR2_Pos);
		break;
	
	case ((uint32_t)TIMR3):
		TIMRG->HALT &= ~(0x01 << TIMRG_HALT_TIMR3_Pos);
		break;
	
	case ((uint32_t)TIMR4):
		TIMRG->HALT &= ~(0x01 << TIMRG_HALT_TIMR4_Pos);
		break;
	
	case ((uint32_t)TIMR5):
		TIMRG->HALT &= ~(0x01 << TIMRG_HALT_TIMR5_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称: TIMR_SetPeriod()
* 功能说明:	设置定时/计数周期
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4、TIMR5
*			uint32_t period			定时/计数周期
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_SetPeriod(TIMR_TypeDef * TIMRx, uint32_t period)
{
	TIMRx->LDVAL = period;
}

/****************************************************************************************************************************************** 
* 函数名称: TIMR_GetPeriod()
* 功能说明:	获取定时/计数周期
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4、TIMR5
* 输    出: uint32_t				当前定时/计数周期
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t TIMR_GetPeriod(TIMR_TypeDef * TIMRx)
{
	return TIMRx->LDVAL; 
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMR_GetCurValue()
* 功能说明:	获取当前计数值
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4、TIMR5
* 输    出: uint32_t				当前计数值
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t TIMR_GetCurValue(TIMR_TypeDef * TIMRx)
{
	return TIMRx->CVAL;
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMR_INTEn()
* 功能说明:	使能中断
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4、TIMR5
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_INTEn(TIMR_TypeDef * TIMRx)
{
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMRG->IE |= (0x01 << TIMRG_IE_TIMR0_Pos);
		NVIC_EnableIRQ(TIMR0_IRQn);
		break;
	
	case ((uint32_t)TIMR1):
		TIMRG->IE |= (0x01 << TIMRG_IE_TIMR1_Pos);
		NVIC_EnableIRQ(TIMR1_IRQn);
		break;
	
	case ((uint32_t)TIMR2):
		TIMRG->IE |= (0x01 << TIMRG_IE_TIMR2_Pos);
		NVIC_EnableIRQ(TIMR2_IRQn);
		break;
	
	case ((uint32_t)TIMR3):
		TIMRG->IE |= (0x01 << TIMRG_IE_TIMR3_Pos);
		NVIC_EnableIRQ(TIMR3_IRQn);
		break;
	
	case ((uint32_t)TIMR4):
		TIMRG->IE |= (0x01 << TIMRG_IE_TIMR4_Pos);
		NVIC_EnableIRQ(TIMR4_IRQn);
		break;
	
	case ((uint32_t)TIMR5):
		TIMRG->IE |= (0x01 << TIMRG_IE_TIMR5_Pos);
		NVIC_EnableIRQ(TIMR5_IRQn);
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称: TIMR_INTDis()
* 功能说明:	禁能中断
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4、TIMR5
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_INTDis(TIMR_TypeDef * TIMRx)
{
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMRG->IE &= ~(0x01 << TIMRG_IE_TIMR0_Pos);
		break;
	
	case ((uint32_t)TIMR1):
		TIMRG->IE &= ~(0x01 << TIMRG_IE_TIMR1_Pos);
		break;
	
	case ((uint32_t)TIMR2):
		TIMRG->IE &= ~(0x01 << TIMRG_IE_TIMR2_Pos);
		break;
	
	case ((uint32_t)TIMR3):
		TIMRG->IE &= ~(0x01 << TIMRG_IE_TIMR3_Pos);
		break;
	
	case ((uint32_t)TIMR4):
		TIMRG->IE &= ~(0x01 << TIMRG_IE_TIMR4_Pos);
		break;
	
	case ((uint32_t)TIMR5):
		TIMRG->IE &= ~(0x01 << TIMRG_IE_TIMR5_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMR_INTClr()
* 功能说明:	清除中断标志
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4、TIMR5
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_INTClr(TIMR_TypeDef * TIMRx)
{
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMRG->IF = (0x01 << TIMRG_IF_TIMR0_Pos);
		break;
	
	case ((uint32_t)TIMR1):
		TIMRG->IF = (0x01 << TIMRG_IF_TIMR1_Pos);
		break;
	
	case ((uint32_t)TIMR2):
		TIMRG->IF = (0x01 << TIMRG_IF_TIMR2_Pos);
		break;
	
	case ((uint32_t)TIMR3):
		TIMRG->IF = (0x01 << TIMRG_IF_TIMR3_Pos);
		break;
	
	case ((uint32_t)TIMR4):
		TIMRG->IF = (0x01 << TIMRG_IF_TIMR4_Pos);
		break;
	
	case ((uint32_t)TIMR5):
		TIMRG->IF = (0x01 << TIMRG_IF_TIMR5_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称: TIMR_INTStat()
* 功能说明:	获取中断状态
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3、TIMR4、TIMR5
* 输    出: uint32_t 				0 TIMRx未产生中断    1 TIMRx产生了中断
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t TIMR_INTStat(TIMR_TypeDef * TIMRx)
{
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		return (TIMRG->IF & TIMRG_IF_TIMR0_Msk) ? 1 : 0;
	
	case ((uint32_t)TIMR1):
		return (TIMRG->IF & TIMRG_IF_TIMR1_Msk) ? 1 : 0;
	
	case ((uint32_t)TIMR2):
		return (TIMRG->IF & TIMRG_IF_TIMR2_Msk) ? 1 : 0;
	
	case ((uint32_t)TIMR3):
		return (TIMRG->IF & TIMRG_IF_TIMR3_Msk) ? 1 : 0;
	
	case ((uint32_t)TIMR4):
		return (TIMRG->IF & TIMRG_IF_TIMR4_Msk) ? 1 : 0;
	
	case ((uint32_t)TIMR5):
		return (TIMRG->IF & TIMRG_IF_TIMR5_Msk) ? 1 : 0;
	}
	
	return 0;
}


/****************************************************************************************************************************************** 
* 函数名称: Pulse_Init()
* 功能说明:	脉宽测量功能初始化
* 输    入: uint32_t pulse			PULSE_LOW 测量低脉冲宽度   PULSE_HIGH 测量高脉冲宽度
*			uint32_t int_en			是否使能脉冲测量完成中断
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void Pulse_Init(uint32_t pulse, uint32_t int_en)
{	
	SYS->CLKEN |= (0x01 << SYS_CLKEN_TIMR_Pos);
	
	TIMRG->PCTRL = (0     << TIMRG_PCTRL_CLKSRC_Pos) |		// 系统时钟作为时钟源
				   (pulse << TIMRG_PCTRL_HIGH_Pos)   |
				   (0     << TIMRG_PCTRL_EN_Pos);
	
	TIMRG->IE |= (1 << TIMRG_IE_PULSE_Pos);		//使能才能查询中断标志
	
	if(int_en)  NVIC_EnableIRQ(PULSE_IRQn);
}

/****************************************************************************************************************************************** 
* 函数名称: Pulse_Start()
* 功能说明:	脉宽测量功能启动，测量到脉宽后会自动关闭测量功能
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void Pulse_Start(void)
{	
	TIMRG->PCTRL |= (1 << TIMRG_PCTRL_EN_Pos);
}

/****************************************************************************************************************************************** 
* 函数名称: Pulse_Done()
* 功能说明:	脉宽测量是否完成
* 输    入: 无
* 输    出: uint32_t				1 测量已完成    0 测量未完成
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t Pulse_Done(void)
{
	if(TIMRG->IF & TIMRG_IF_PULSE_Msk)
	{
		TIMRG->IF = TIMRG_IF_PULSE_Msk;		// 清除中断标志
		
		return 1;
	}
	else
	{
		return 0;
	}
}
