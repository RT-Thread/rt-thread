/***************************************************************
 *Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
 *文件名： lib_gpio.c
 *作 者： Liut
 *版 本： V1.00
 *日 期： 2017/07/14
 *描 述： flash读写库函数头文件
 *备 注： 适用于 ES8P508x芯片
 本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
 ***************************************************************/
#include "lib_gpio.h"
extern uint32_t SystemCoreClock;
/***************************************************************
  函数名：GPIO_Init
  描  述：GPIO初始化
  输入值：GPIOx：可以是GPIOA/GPIOB 、 PINx：根据芯片选择需要的引脚 、 GPIO_InitStruct：初始化配置结构体地址
  输出值：无
  返回值：无
 ***************************************************************/
void GPIO_Init(GPIO_TYPE GPIOx,GPIO_TYPE_PIN PINx, GPIO_InitStruType* GPIO_InitStruct)
{
	if (GPIO_InitStruct->GPIO_Signal == GPIO_Pin_Signal_Analog) {
		GPIO_SetSingalTypeFromPin(GPIOx, PINx, GPIO_Pin_Signal_Analog);
		GPIO_SetDirRegFromPin(GPIOx, PINx, GPIO_Dir_In);
		GPIO_SetFuncxRegFromPin(GPIOx, PINx, GPIO_Func_0);
	} 
	else {
		GPIO_SetSingalTypeFromPin(GPIOx, PINx, GPIO_Pin_Signal_Digital);
		GPIO_SetDirRegFromPin(GPIOx, PINx, GPIO_InitStruct->GPIO_Direction);
		GPIO_SetFuncxRegFromPin(GPIOx, PINx, GPIO_InitStruct->GPIO_Func);

		if (GPIO_InitStruct->GPIO_Direction == GPIO_Dir_Out) {
			GPIO_SetODERegFromPin(GPIOx, PINx, GPIO_InitStruct->GPIO_OD);
			GPIO_SetDSRegFromPin(GPIOx, PINx, GPIO_InitStruct->GPIO_DS);
		} 
		GPIO_SetPUERegFromPin(GPIOx, PINx, GPIO_InitStruct->GPIO_PUEN);
		GPIO_SetPDERegFromPin(GPIOx, PINx, GPIO_InitStruct->GPIO_PDEN);
	}
}

/***************************************************************
  函数名：GPIO_SetFuncxRegFromPin
  描  述：设置GPIO引脚的功能复用
  输入值：Pin：目的引脚
  Func：功能复用编号
  输出值：无
  返回值：无
 ***************************************************************/
void GPIO_SetFuncxRegFromPin(GPIO_TYPE GPIOx,GPIO_TYPE_PIN PINx, GPIO_TYPE_FUNC Func)
{
	uint32_t value;

	switch (Func) {
		case GPIO_Func_0:
			value = 0;
			break;
		case GPIO_Func_1:
			value = 1;
			break;
		case GPIO_Func_2:
			value = 2;
			break;
		case GPIO_Func_3:
			value = 3;
			break;
		default:
			value = 0;
			break;
	}

	/* 引脚功能设置 */
	if(GPIOx == GPIOB){
	  switch (PINx) {
		  case GPIO_Pin_0:
			  GPIO->PBFUNC0.PB0 = value;
			  break;
		  case GPIO_Pin_1:
			  GPIO->PBFUNC0.PB1 = value;
			  break;
		  case GPIO_Pin_2:
			  GPIO->PBFUNC0.PB2 = value;
			  break;
		  case GPIO_Pin_3:
			  GPIO->PBFUNC0.PB3 = value;
		    break;
	    case GPIO_Pin_4:
		    GPIO->PBFUNC0.PB4 = value;
			  break;
		  case GPIO_Pin_5:
			  GPIO->PBFUNC0.PB5 = value;
			  break;
		  case GPIO_Pin_6:
			  GPIO->PBFUNC0.PB6 = value;
			  break;
		  case GPIO_Pin_7:
			  GPIO->PBFUNC0.PB7 = value;
			  break;
		  case GPIO_Pin_8:
			  GPIO->PBFUNC1.PB8 = value;
			  break;
		  case GPIO_Pin_9:
			  GPIO->PBFUNC1.PB9 = value;
			  break;
		  case GPIO_Pin_10:
			  GPIO->PBFUNC1.PB10 = value;
			  break;
		  case GPIO_Pin_11:
			  GPIO->PBFUNC1.PB11 = value;
			  break;
		  case GPIO_Pin_12:
			  GPIO->PBFUNC1.PB12 = value;
			  break;
		  case GPIO_Pin_13:
			  GPIO->PBFUNC1.PB13 = value;
			  break;
			default:
				break;
		}
	}
		
	else{
		switch (PINx) {
		  case GPIO_Pin_0:
			  GPIO->PAFUNC0.PA0 = value;
			  break;
		  case GPIO_Pin_1:
			  GPIO->PAFUNC0.PA1 = value;
			  break;
		  case GPIO_Pin_2:
			  GPIO->PAFUNC0.PA2 = value;
			  break;
		  case GPIO_Pin_3:
			  GPIO->PAFUNC0.PA3 = value;
			  break;
		  case GPIO_Pin_4:
			  GPIO->PAFUNC0.PA4 = value;
			  break;
		  case GPIO_Pin_5:
			  GPIO->PAFUNC0.PA5 = value;
			  break;
		  case GPIO_Pin_6:
			  GPIO->PAFUNC0.PA6 = value;
			  break;
		  case GPIO_Pin_7:
				GPIO->PAFUNC0.PA7 = value;
				break;
			case GPIO_Pin_8:
				GPIO->PAFUNC1.PA8 = value;
				break;
			case GPIO_Pin_9:
				GPIO->PAFUNC1.PA9 = value;
				break;
			case GPIO_Pin_10:
				GPIO->PAFUNC1.PA10 = value;
				break;
			case GPIO_Pin_11:
				GPIO->PAFUNC1.PA11 = value;
				break;
			case GPIO_Pin_12:
				GPIO->PAFUNC1.PA12 = value;
				break;
			case GPIO_Pin_13:
				GPIO->PAFUNC1.PA13 = value;
				break;
			case GPIO_Pin_14:
				GPIO->PAFUNC1.PA14 = value;
				break;
			case GPIO_Pin_15:
				GPIO->PAFUNC1.PA15 = value;
				break;
			case GPIO_Pin_16:
				GPIO->PAFUNC2.PA16 = value;
				break;
			case GPIO_Pin_17:
				GPIO->PAFUNC2.PA17 = value;
				break;
			case GPIO_Pin_18:
				GPIO->PAFUNC2.PA18 = value;
				break;
			case GPIO_Pin_19:
				GPIO->PAFUNC2.PA19 = value;
				break;
			case GPIO_Pin_20:
				GPIO->PAFUNC2.PA20 = value;
				break;
			case GPIO_Pin_21:
				GPIO->PAFUNC2.PA21 = value;
				break;
			case GPIO_Pin_22:
				GPIO->PAFUNC2.PA22 = value;
				break;
			case GPIO_Pin_23:
				GPIO->PAFUNC2.PA23 = value;
				break;
			case GPIO_Pin_24:
				GPIO->PAFUNC3.PA24 = value;
				break;
			case GPIO_Pin_25:
				GPIO->PAFUNC3.PA25 = value;
				break;
			case GPIO_Pin_26:
				GPIO->PAFUNC3.PA26 = value;
				break;
			case GPIO_Pin_27:
				GPIO->PAFUNC3.PA27 = value;
				break;
			case GPIO_Pin_28:
				GPIO->PAFUNC3.PA28 = value;
				break;
			case GPIO_Pin_29:
				GPIO->PAFUNC3.PA29 = value;
				break;
			case GPIO_Pin_30:
				GPIO->PAFUNC3.PA30 = value;
				break;
			case GPIO_Pin_31:
				GPIO->PAFUNC3.PA31 = value;
				break;
			default:
				break;
		}
	}
	return;
}

/***************************************************************
  函数名：GPIO_SetSingalTypeFromPin
  描  述：设置引脚的信号类型
  输入值：Pin: 目的引脚
  Signal: 引脚的信号类型
  输出值：无
  返回值：无
 ***************************************************************/
void GPIO_SetSingalTypeFromPin(GPIO_TYPE GPIOx,GPIO_TYPE_PIN PINx, GPIO_Pin_Signal GPIO_Signal)
{
	if(GPIOx == GPIOB) {
		if (GPIO_Signal == GPIO_Pin_Signal_Digital)
			GPIO->PBINEB.Word &= (~(1 << PINx));
		else
			GPIO->PBINEB.Word |= (1 << PINx);
	} 
	else{
		if (GPIO_Signal == GPIO_Pin_Signal_Digital)
			GPIO->PAINEB.Word &= (~(1 << PINx));
		else
			GPIO->PAINEB.Word |= (1 << PINx);
	}

	return;
}

/***************************************************************
  函数名：GPIO_SetDirRegFromPin
  描  述：设置引脚的输入或输出方向
  输入值：Pin: 目的引脚
  Dir：引脚方向
  输出值：无
  返回值：无
 ***************************************************************/
void GPIO_SetDirRegFromPin(GPIO_TYPE GPIOx,GPIO_TYPE_PIN PINx, GPIO_TYPE_DIR Dir)
{
	if (GPIOx == GPIOB) {
		if (Dir == GPIO_Dir_In)
			GPIO->PBDIRBSR.Word = (1 << PINx);
		else
			GPIO->PBDIRBCR.Word = (1 << PINx);
	} 
	else {
		if (Dir == GPIO_Dir_In)
			GPIO->PADIRBSR.Word = (1 << PINx);
		else
			GPIO->PADIRBCR.Word = (1 << PINx);
	}

	return;
}

/***************************************************************
  函数名：GPIO_SetODERegFromPin
  描  述：设置引脚的输出开漏方式
  输入值：Pin: 目的引脚
ODE: 输出开漏方式
输出值：无
返回值：无
 ***************************************************************/
void GPIO_SetODERegFromPin(GPIO_TYPE GPIOx,GPIO_TYPE_PIN PINx, GPIO_ODE_Output ODE)
{
	if (GPIOx == GPIOB) {
		if (ODE == GPIO_ODE_Output_Disable)
			GPIO->PBODE.Word &= (~(1 << PINx));
		else
			GPIO->PBODE.Word |= (1 << PINx);
	} 
	else {
		if (ODE == GPIO_ODE_Output_Disable)
			GPIO->PAODE.Word &= (~(1 << PINx));
		else
			GPIO->PAODE.Word |= (1 << PINx);
	}

	return;
}

/***************************************************************
  函数名：GPIO_SetDSRegFromPin
  描  述：设置引脚的输出驱动能力
  输入值：Pin: 目的引脚
DS: 电流驱动方式
输出值：无
返回值：无
 ***************************************************************/
void GPIO_SetDSRegFromPin(GPIO_TYPE GPIOx,GPIO_TYPE_PIN PINx, GPIO_TYPE_DS DS)
{
	if (GPIOx == GPIOB) {
		if (DS == GPIO_DS_Output_Normal)
			GPIO->PBDS.Word &= (~(1 << PINx));
		else
			GPIO->PBDS.Word |= (1 << PINx);
	} 
	else {
		if (DS == GPIO_DS_Output_Normal)
			GPIO->PADS.Word &= (~(1 << PINx));
		else
			GPIO->PADS.Word |= (1 << PINx);
	}

	return;
}

/***************************************************************
  函数名：GPIO_SetPUERegFromPin
  描  述：设置引脚的弱上拉方式
  输入值：Pin: 目的引脚
PUE: 弱上拉方式
输出值：无
返回值：无
 ***************************************************************/
void GPIO_SetPUERegFromPin(GPIO_TYPE GPIOx,GPIO_TYPE_PIN PINx, GPIO_PUE_Input PUE)
{
	if (GPIOx == GPIOB) {
		if (PUE == GPIO_PUE_Input_Disable)
			GPIO->PBPUE.Word &= (~(1 << PINx));
		else
			GPIO->PBPUE.Word |= (1 << PINx);
	} 
	else {
		if (PUE == GPIO_PUE_Input_Disable)
			GPIO->PAPUE.Word &= (~(1 << PINx));
		else
			GPIO->PAPUE.Word |= (1 << PINx);
	}
}

/***************************************************************
  函数名：GPIO_SetPDERegFromPin
  描  述：设置引脚的弱下拉方式
  输入值：Pin: 目的引脚
  PDE：弱下拉方式
  输出值：无
  返回值：无
 ***************************************************************/
void GPIO_SetPDERegFromPin(GPIO_TYPE GPIOx,GPIO_TYPE_PIN PINx, GPIO_PDE_Input PDE)
{
	if (GPIOx == GPIOB) {
		if (PDE == GPIO_PDE_Input_Disable)
			GPIO->PBPDE.Word &= (~(1 << PINx));
		else
			GPIO->PBPDE.Word |= (1 << PINx);
	} 
	else {
		if (PDE == GPIO_PDE_Input_Disable)
			GPIO->PAPDE.Word &= (~(1 << PINx));
		else
			GPIO->PAPDE.Word |= (1 << PINx);
	}

	return;
}

/***************************************************************
  函数名：GPIO_Write
  描  述：GPIO端口写数据
  输入值：GPIOx：可以是GPIOA/GPIOB 、 Value要写的数据——注意：有些不存在的引脚，设置的值相对应的位是无作用的
  输出值：无
  返回值：无
 ***************************************************************/
void GPIO_Write(GPIO_TYPE GPIOx, uint32_t Value)
{
    if(GPIOx == GPIOA)
        GPIO->PADATA.Word = Value;
    else if(GPIOx == GPIOB)
        GPIO->PBDATA.Word = Value;
}

/***************************************************************
  函数名：GPIO_Read
  描  述：GPIO端口读数据
  输入值：GPIOx：可以是GPIOA/GPIOB
  输出值：无
  返回值：读出的数据——注意：有些不存在的引脚，读出的值相对应的位是无效的
 ***************************************************************/
uint32_t GPIO_Read(GPIO_TYPE GPIOx)
{
    if(GPIOx == GPIOA)
        return GPIO->PAPORT.Word;
    else if(GPIOx == GPIOB)
        return GPIO->PBPORT.Word;

    return 0;
}

/***************************************************************
  函数名：GPIO_ReadBit
  描  述：GPIO端口读某位数据
  输入值：GPIOx：可以是GPIOA/GPIOB 、 PINx:GPIO_Pin_0 —— GPIO_Pin_31
  输出值：无
  返回值：读出的数据——注意：有些不存在的引脚，读出的值是无效的
 ***************************************************************/
PinStatus GPIO_ReadBit(GPIO_TYPE GPIOx,GPIO_TYPE_PIN PINx)
{
    PinStatus bitstatus = RESET;

    if(GPIOx == GPIOA)
    {
        if((GPIO->PAPORT.Word&((uint32_t)0x1<<PINx)) != RESET)
            bitstatus = SET;
        else
            bitstatus = RESET;
    }
    else if(GPIOx == GPIOB)
    {
        if((GPIO->PBPORT.Word&((uint32_t)0x1<<PINx)) != RESET)
            bitstatus = SET;
        else
            bitstatus = RESET;
    }

    return bitstatus;
}

/***************************************************************
  函数名：GPIOA_SetBit
  描  述：GPIOA某引脚置1
  输入值：PINx：可以是GPIO_Pin_0 —— GPIO_Pin_31
  输出值：无
  返回值：无
 ***************************************************************/
void GPIOA_SetBit(GPIO_TYPE_PIN PINx)
{
    GPIO->PADATABSR.Word = (uint32_t)0x1<<PINx;
}

/***************************************************************
  函数名：GPIOA_ResetBit
  描  述：GPIOA某引脚清0
  输入值：PINx：可以是GPIO_Pin_0 —— GPIO_Pin_31
  输出值：无
  返回值：无
 ***************************************************************/
void GPIOA_ResetBit(GPIO_TYPE_PIN PINx)
{
    GPIO->PADATABCR.Word = (uint32_t)0x1<<PINx;
}

/***************************************************************
  函数名：GPIOA_ToggleBit
  描  述：GPIOA某引脚输出状态取反
  输入值：PINx：可以是GPIO_Pin_0 —— GPIO_Pin_31
  输出值：无
  返回值：无
 ***************************************************************/
void GPIOA_ToggleBit(GPIO_TYPE_PIN PINx)
{
    GPIO->PADATABRR.Word = (uint32_t)0x1<<PINx;
}

/***************************************************************
  函数名：GPIOB_SetBit
  描  述：GPIOB某引脚置1
  输入值：PINx：可以是GPIO_Pin_0 —— GPIO_Pin_13
  输出值：无
  返回值：无
 ***************************************************************/
void GPIOB_SetBit(GPIO_TYPE_PIN PINx)
{
    GPIO->PBDATABSR.Word = (uint32_t)0x1<<PINx;
}

/***************************************************************
  函数名：GPIOB_ResetBit
  描  述：GPIOB某引脚清0
  输入值：PINx：可以是GPIO_Pin_0 —— GPIO_Pin_13
  输出值：无
  返回值：无
 ***************************************************************/
void GPIOB_ResetBit(GPIO_TYPE_PIN PINx)
{
    GPIO->PBDATABCR.Word = (uint32_t)0x1<<PINx;
}

/***************************************************************
  函数名：GPIOB_ToggleBit
  描  述：GPIOB某引脚输出状态取反
  输入值：PINx：可以是GPIO_Pin_0 —— GPIO_Pin_13
  输出值：无
  返回值：无
 ***************************************************************/
void GPIOB_ToggleBit(GPIO_TYPE_PIN PINx)
{
    GPIO->PBDATABRR.Word = (uint32_t)0x1<<PINx; 
}

/***************************************************************
  函数名：GPIOA_SetDirection
  描  述：GPIOA某引脚设置方向
  输入值：PINx：可以是GPIO_Pin_0 —— GPIO_Pin_31 、 Dir_Type：GPIO_Dir_Out/GPIO_Dir_In
  输出值：无
  返回值：无
 ***************************************************************/
void GPIOA_SetDirection(GPIO_TYPE_PIN PINx, GPIO_TYPE_DIR Dir_Type)
{
    GPIO->PADIR.Word &=~((uint32_t)0x1 << PINx);
    GPIO->PADIR.Word |= ((uint32_t)Dir_Type <<PINx);
}

/***************************************************************
  函数名：GPIOB_SetDirection
  描  述：GPIOB某引脚设置方向
  输入值：PINx：可以是GPIO_Pin_0 —— GPIO_Pin_13 、 Dir_Type：GPIO_Dir_Out/GPIO_Dir_In
  输出值：无
  返回值：无
 ***************************************************************/
void GPIOB_SetDirection(GPIO_TYPE_PIN PINx, GPIO_TYPE_DIR Dir_Type)
{
    GPIO->PBDIR.Word &=~((uint32_t)0x1 << PINx);
    GPIO->PBDIR.Word |= ((uint32_t)Dir_Type <<PINx);
}
/***************************************************************
  函数名：Buzz_Config
  描  述：Buzz配置
  输入值：Buzz_en:Buzz是否使能；freq:频率
  输出值：无
  返回值：无
 ***************************************************************/
void Buzz_Config(TYPE_BUZZEN buzz_en, uint32_t freq)
{
    GPIO->BUZC.BUZ_LOAD = (SystemCoreClock/(freq*2)) - 1;
    GPIO->BUZC.BUZEN = buzz_en;
}
/***************************************************************
  函数名：PINT_Config
  描  述：PINT配置
  输入值：PINTx：可选PINT0 —— PINT7 、 SELx：输入选择 、 TRIGx：触发选择
  输出值：无
  返回值：无
 ***************************************************************/
void PINT_Config(PINT_TYPE PINTx, PINT_TYPE_SEL SELx, PINT_TYPE_TRIG TRIGx)
{
    GPIO->PINTSEL.Word &= ~((uint32_t)0x07<<(PINTx*4));
    GPIO->PINTSEL.Word |=((uint32_t)SELx << (PINTx*4));   //sel选择

    GPIO->PINTCFG.Word &= ~((uint32_t)0x07<<(PINTx*4));
    GPIO->PINTCFG.Word |=((uint32_t)TRIGx << (PINTx*4));  //触发方式选择
}

/***************************************************************
  函数名：PINT_GetIFStatus
  描  述：PINT读取中断标志
  输入值：PINTx：PINT0-PINT7
  输出值：无
  返回值：SET/RESET
 ***************************************************************/
FlagStatus PINT_GetIFStatus(PINT_TYPE_IT PINT_Flag)
{
    FlagStatus bitstatus = RESET;

    if((GPIO->PINTIF.Word & (uint32_t)PINT_Flag) != (uint32_t)RESET)
        bitstatus = SET;
    else   
        bitstatus = RESET;

    return  bitstatus;
}

/***************************************************************
  函数名：PINT_GetITStatus
  描  述：PINT读取中断标志
  输入值：PINTx：PINT0-PINT7
  输出值：无
  返回值：SET/RESET
 ***************************************************************/
FlagStatus PINT_GetITStatus(PINT_TYPE_IT PINT_Flag)
{
    FlagStatus bitstatus = RESET;

    if((GPIO->PINTIF.Word & (uint32_t)PINT_Flag) != (uint32_t)RESET)
        bitstatus = SET;
    else
        bitstatus = RESET;

    return  bitstatus;
}

/***************************************************************
  函数名：PINT_ClearITPendingBit
  描  述：PINT清除中断标志
  输入值：PINT中断类型
  输出值：无
  返回值：无
 ***************************************************************/
void PINT_ClearITPendingBit(PINT_TYPE_IT PINT_Flag)
{
    GPIO->PINTIF.Word = (uint32_t)PINT_Flag;
}

/*************************END OF FILE**********************/



