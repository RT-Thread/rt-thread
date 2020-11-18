/***************************************************************
 *Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
 *文件名： lib_gpio.h
 *作 者： Liut
 *版 本： V1.00
 *日 期： 2017/07/14
 *描 述： GPIO模块及外部中断、按键中断库函数头文件
 *备 注： 适用于 ES8P508x芯片
 本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
 ***************************************************************/
#ifndef __LIBGPIO_H__
#define __LIBGPIO_H__

#include "ES8P508x.h"
#include "type.h"

/*状态定义*/

/*端口定义*/
typedef enum
{
    GPIOA = 0x0 ,
    GPIOB = 0x1 ,
}GPIO_TYPE;

/*引脚定义*/
typedef enum
{
    GPIO_Pin_0 = 0x00,
    GPIO_Pin_1 = 0x01,
    GPIO_Pin_2 = 0x02,
    GPIO_Pin_3 = 0x03,
    GPIO_Pin_4 = 0x04,
    GPIO_Pin_5 = 0x05,
    GPIO_Pin_6 = 0x06,
    GPIO_Pin_7 = 0x07,
    GPIO_Pin_8 = 0x08,
    GPIO_Pin_9 = 0x09,
    GPIO_Pin_10 = 0x0A,
    GPIO_Pin_11 = 0x0B,
    GPIO_Pin_12 = 0x0C,
    GPIO_Pin_13 = 0x0D,
    GPIO_Pin_14 = 0x0E,
    GPIO_Pin_15 = 0x0F,
    GPIO_Pin_16 = 0x10,
    GPIO_Pin_17 = 0x11,
    GPIO_Pin_18 = 0x12,
    GPIO_Pin_19 = 0x13,
    GPIO_Pin_20 = 0x14,
    GPIO_Pin_21 = 0x15,
    GPIO_Pin_22 = 0x16,
    GPIO_Pin_23 = 0x17,
    GPIO_Pin_24 = 0x18,
    GPIO_Pin_25 = 0x19,
    GPIO_Pin_26 = 0x1A,
    GPIO_Pin_27 = 0x1B,
    GPIO_Pin_28 = 0x1C,
    GPIO_Pin_29 = 0x1D,
    GPIO_Pin_30 = 0x1E,
    GPIO_Pin_31 = 0x1F,
}GPIO_TYPE_PIN;

/* 引脚功能选择 */
typedef enum
{
    GPIO_Func_0 = 0x0 ,
    GPIO_Func_1 = 0x1 ,
    GPIO_Func_2 = 0x2 ,
    GPIO_Func_3 = 0x3 ,
}GPIO_TYPE_FUNC;

/* 引脚方向选择 */
typedef enum
{
    GPIO_Dir_Out = 0x0 ,
    GPIO_Dir_In = 0x1 ,
}GPIO_TYPE_DIR;

/* 引脚输出电流驱动能力选择 */
typedef enum
{
    GPIO_DS_Output_Normal = 0,  // 普通电流输出
    GPIO_DS_Output_Strong = 1,  // 强电流输出
} GPIO_TYPE_DS;

/* 引脚信号类型 */
typedef enum {
	GPIO_Pin_Signal_Digital = 0,	// 数字信号引脚
	GPIO_Pin_Signal_Analog = 1,	  // 模拟信号引脚
} GPIO_Pin_Signal;	

/* 引脚输入弱上拉使能 */
typedef enum {
	GPIO_PUE_Input_Disable = 0,	// 弱上拉禁止
	GPIO_PUE_Input_Enable = 1,	// 弱上拉使能
} GPIO_PUE_Input;

/* 引脚输入弱下拉使能 */
typedef enum {
	GPIO_PDE_Input_Disable = 0,	// 弱下拉禁止
	GPIO_PDE_Input_Enable = 1,	// 弱下拉使能
} GPIO_PDE_Input;


/* 引脚输出开漏使能位 */
typedef enum {
	GPIO_ODE_Output_Disable = 0,	// 开漏禁止
	GPIO_ODE_Output_Enable = 1,	// 开漏使能
} GPIO_ODE_Output;

/* GPIO初始化配置结构体定义 */
typedef struct
{
	  GPIO_Pin_Signal GPIO_Signal;		/* 引脚上的信号类型，只有模拟和数字两种 */
    GPIO_TYPE_FUNC GPIO_Func;       //引脚功能选择
    GPIO_TYPE_DIR GPIO_Direction;   //方向选择
    GPIO_PUE_Input GPIO_PUEN;          //上拉使能
    GPIO_PDE_Input GPIO_PDEN;          //下拉使能
    GPIO_ODE_Output GPIO_OD;            //输出模式开漏使能
    GPIO_TYPE_DS GPIO_DS;           //驱动电流控制
}GPIO_InitStruType;

/* PINT */
typedef enum
{
    PINT0 = 0x0 ,
    PINT1 = 0x1 ,
    PINT2 = 0x2 ,
    PINT3 = 0x3 ,
    PINT4 = 0x4 ,
    PINT5 = 0x5 ,
    PINT6 = 0x6 ,
    PINT7 = 0x7 ,
}PINT_TYPE;

/* PINT SEL */
typedef enum
{
    PINT_SEL0 = 0x0 ,
    PINT_SEL1 = 0x1 ,
    PINT_SEL2 = 0x2 ,
    PINT_SEL3 = 0x3 ,
    PINT_SEL4 = 0x4 ,
    PINT_SEL5 = 0x5 ,
    PINT_SEL6 = 0x6 ,
    PINT_SEL7 = 0x7 ,
}PINT_TYPE_SEL;

/* PINT Trigger */
typedef enum
{
    PINT_Trig_Rise = 0x0 ,
    PINT_Trig_Fall = 0x1 ,
    PINT_Trig_High = 0x2 ,
    PINT_Trig_Low = 0x3 ,
    PINT_Trig_Change = 0x4 ,
}PINT_TYPE_TRIG;


/* PINT中断标志 */
typedef enum
{
    PINT_IT_PINT0 = 0x01 ,
    PINT_IT_PINT1 = 0x02 ,
    PINT_IT_PINT2 = 0x04 ,
    PINT_IT_PINT3 = 0x08 ,
    PINT_IT_PINT4 = 0x10 ,
    PINT_IT_PINT5 = 0x20 ,
    PINT_IT_PINT6 = 0x40 ,
    PINT_IT_PINT7 = 0x80 ,
    PINT_IT_PINTAll = 0xFF ,
}PINT_TYPE_IT;

/* PINT使能控制 */
#define PINT0_Enable() (GPIO->PINTIE.PINTIE |= 0X1)
#define PINT1_Enable() (GPIO->PINTIE.PINTIE |= 0x2)
#define PINT2_Enable() (GPIO->PINTIE.PINTIE |= 0x4)
#define PINT3_Enable() (GPIO->PINTIE.PINTIE |= 0x8)
#define PINT4_Enable() (GPIO->PINTIE.PINTIE |= 0x10)
#define PINT5_Enable() (GPIO->PINTIE.PINTIE |= 0x20)
#define PINT6_Enable() (GPIO->PINTIE.PINTIE |= 0x40)
#define PINT7_Enable() (GPIO->PINTIE.PINTIE |= 0x80)
#define PINT0_Disable() (GPIO->PINTIE.PINTIE &= ~0x01)
#define PINT1_Disable() (GPIO->PINTIE.PINTIE &= ~0x02)
#define PINT2_Disable() (GPIO->PINTIE.PINTIE &= ~0x04)
#define PINT3_Disable() (GPIO->PINTIE.PINTIE &= ~0x08)
#define PINT4_Disable() (GPIO->PINTIE.PINTIE &= ~0x10)
#define PINT5_Disable() (GPIO->PINTIE.PINTIE &= ~0x20)
#define PINT6_Disable() (GPIO->PINTIE.PINTIE &= ~0x40)
#define PINT7_Disable() (GPIO->PINTIE.PINTIE &= ~0x80)

/* PINT屏蔽使能控制 */
#define PINT0_MaskEnable()   (GPIO->PINTIE.PMASK |= 0X01)
#define PINT1_MaskEnable()   (GPIO->PINTIE.PMASK |= 0x02)
#define PINT2_MaskEnable()   (GPIO->PINTIE.PMASK |= 0x04)
#define PINT3_MaskEnable()   (GPIO->PINTIE.PMASK |= 0x08)
#define PINT4_MaskEnable()   (GPIO->PINTIE.PMASK |= 0x10)
#define PINT5_MaskEnable()   (GPIO->PINTIE.PMASK |= 0x20)
#define PINT6_MaskEnable()   (GPIO->PINTIE.PMASK |= 0x40)
#define PINT7_MaskEnable()   (GPIO->PINTIE.PMASK |= 0x80)
#define PINT0_MaskDisable()  (GPIO->PINTIE.PMASK &= ~0x01)
#define PINT1_MaskDisable()  (GPIO->PINTIE.PMASK &= ~0x02)
#define PINT2_MaskDisable()  (GPIO->PINTIE.PMASK &= ~0x04)
#define PINT3_MaskDisable()  (GPIO->PINTIE.PMASK &= ~0x08)
#define PINT4_MaskDisable()  (GPIO->PINTIE.PMASK &= ~0x10)
#define PINT5_MaskDisable()  (GPIO->PINTIE.PMASK &= ~0x20)
#define PINT6_MaskDisable()  (GPIO->PINTIE.PMASK &= ~0x40)
#define PINT7_MaskDisable()  (GPIO->PINTIE.PMASK &= ~0x80)

/* PINT清除所有中断标记 */
#define PINT_ClearAllITPending() (GPIO->PIF.Word = (uint32_t)0xff)

void GPIO_Init(GPIO_TYPE GPIOx,GPIO_TYPE_PIN PINx, GPIO_InitStruType* GPIO_InitStruct);
void GPIO_Write(GPIO_TYPE GPIOx, uint32_t Value);
uint32_t GPIO_Read(GPIO_TYPE GPIOx);
PinStatus GPIO_ReadBit(GPIO_TYPE GPIOx,GPIO_TYPE_PIN PINx);
void GPIOA_SetBit(GPIO_TYPE_PIN PINx);
void GPIOA_ResetBit(GPIO_TYPE_PIN PINx);
void GPIOA_ToggleBit(GPIO_TYPE_PIN PINx);
void GPIOB_SetBit(GPIO_TYPE_PIN PINx);
void GPIOB_ResetBit(GPIO_TYPE_PIN PINx);
void GPIOB_ToggleBit(GPIO_TYPE_PIN PINx);
void GPIOA_SetDirection(GPIO_TYPE_PIN PINx, GPIO_TYPE_DIR Dir_Type);
void GPIOB_SetDirection(GPIO_TYPE_PIN PINx, GPIO_TYPE_DIR Dir_Type);
void PINT_Config(PINT_TYPE PINTx, PINT_TYPE_SEL SELx, PINT_TYPE_TRIG TRIGx);
void GPIO_SetSingalTypeFromPin(GPIO_TYPE GPIOx,GPIO_TYPE_PIN PINx, GPIO_Pin_Signal GPIO_Signal);
void GPIO_SetDirRegFromPin(GPIO_TYPE GPIOx,GPIO_TYPE_PIN PINx, GPIO_TYPE_DIR Dir);
void GPIO_SetODERegFromPin(GPIO_TYPE GPIOx,GPIO_TYPE_PIN PINx, GPIO_ODE_Output ODE);
void GPIO_SetDSRegFromPin(GPIO_TYPE GPIOx,GPIO_TYPE_PIN PINx, GPIO_TYPE_DS DS);
void GPIO_SetPUERegFromPin(GPIO_TYPE GPIOx,GPIO_TYPE_PIN PINx, GPIO_PUE_Input PUE);
void GPIO_SetPDERegFromPin(GPIO_TYPE GPIOx,GPIO_TYPE_PIN PINx, GPIO_PDE_Input PDE);
void GPIO_SetFuncxRegFromPin(GPIO_TYPE GPIOx,GPIO_TYPE_PIN PINx, GPIO_TYPE_FUNC Func);
FlagStatus PINT_GetIFStatus(PINT_TYPE_IT PINT_Flag);
FlagStatus PINT_GetITStatus(PINT_TYPE_IT PINT_Flag);
void PINT_ClearITPendingBit(PINT_TYPE_IT PINT_Flag);

#endif






