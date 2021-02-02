#ifndef __SWM320_EXTI_H__
#define	__SWM320_EXTI_H__

void EXTI_Init(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t mode);	//指定引脚外部中断初始化
void EXTI_Open(GPIO_TypeDef * GPIOx, uint32_t n);					//指定引脚外部中断打开（即使能）
void EXTI_Close(GPIO_TypeDef * GPIOx, uint32_t n);					//指定引脚外部中断关闭（即禁能）

uint32_t EXTI_State(GPIO_TypeDef * GPIOx, uint32_t n);				//指定引脚是否触发了中断
uint32_t EXTI_RawState(GPIO_TypeDef * GPIOx, uint32_t n);			//指定引脚是否满足过/了中断触发条件，当此中断关闭时可通过调用此函数以查询的方式检测引脚上是否满足过/了中断触发条件
void EXTI_Clear(GPIO_TypeDef * GPIOx, uint32_t n);					//指定引脚外部中断清除（即清除中断标志，以免再次进入此中断）


#define EXTI_FALL_EDGE	0x00	//下降沿触发中断
#define EXTI_RISE_EDGE	0x01	//上升沿触发中断
#define EXTI_BOTH_EDGE	0x02	//双边沿触发中断
#define EXTI_LOW_LEVEL	0x10	//低电平触发中断
#define EXTI_HIGH_LEVEL	0x11	//高电平触发中断


#endif //__SWM320_EXTI_H__
