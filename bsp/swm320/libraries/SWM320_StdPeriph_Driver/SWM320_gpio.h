#ifndef __SWM320_GPIO_H__
#define	__SWM320_GPIO_H__


void GPIO_Init(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t dir, uint32_t pull_up, uint32_t pull_down);	//引脚初始化，包含引脚方向、上拉电阻、下拉电阻

void GPIO_SetBit(GPIO_TypeDef * GPIOx, uint32_t n);						//将参数指定的引脚电平置高
void GPIO_ClrBit(GPIO_TypeDef * GPIOx, uint32_t n);						//将参数指定的引脚电平置低
void GPIO_InvBit(GPIO_TypeDef * GPIOx, uint32_t n);						//将参数指定的引脚电平反转
uint32_t GPIO_GetBit(GPIO_TypeDef * GPIOx, uint32_t n);					//读取参数指定的引脚的电平状态
void GPIO_SetBits(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t w);		//将参数指定的从n开始的w位连续引脚的电平置高
void GPIO_ClrBits(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t w);		//将参数指定的从n开始的w位连续引脚的电平置低
void GPIO_InvBits(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t w);		//将参数指定的从n开始的w位连续引脚的电平反转
uint32_t GPIO_GetBits(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t w);	//读取参数指定的从n开始的w位连续引脚的电平状态

void GPIO_AtomicSetBit(GPIO_TypeDef * GPIOx, uint32_t n);
void GPIO_AtomicClrBit(GPIO_TypeDef * GPIOx, uint32_t n);
void GPIO_AtomicInvBit(GPIO_TypeDef * GPIOx, uint32_t n);
void GPIO_AtomicSetBits(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t w);
void GPIO_AtomicClrBits(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t w);
void GPIO_AtomicInvBits(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t w);


#endif //__SWM320_GPIO_H__
