#ifndef __SWM341_GPIO_H__
#define __SWM341_GPIO_H__


void GPIO_Init(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t dir, uint32_t pull_up, uint32_t pull_down, uint32_t open_drain);  //引脚初始化，包含引脚方向、上拉、下拉、开漏

#define GPIO_INPUT                      ((0 << 0) | (0 << 1) | (0 << 2) | (0 << 3))
#define GPIO_INPUT_PullUp               ((0 << 0) | (1 << 1) | (0 << 2) | (0 << 3))
#define GPIO_INPUT_PullDown             ((0 << 0) | (0 << 1) | (1 << 2) | (0 << 3))
#define GPIO_OUTPUT                     ((1 << 0) | (0 << 1) | (0 << 2) | (0 << 3))
#define GPIO_OUTPUT_OpenDrain           ((1 << 0) | (0 << 1) | (0 << 2) | (1 << 3))
#define GPIO_OUTPUT_OpenDrain_PullUp    ((1 << 0) | (1 << 1) | (0 << 2) | (1 << 3))

#define GPIO_INIT(GPIOx, n, mode)  GPIO_Init(GPIOx, n, (mode & 1) ? 1 : 0, (mode & 2) ? 1 : 0, (mode & 4) ? 1 : 0, (mode & 8) ? 1 : 0)


void GPIO_SetBit(GPIO_TypeDef * GPIOx, uint32_t n);                     //将参数指定的引脚电平置高
void GPIO_ClrBit(GPIO_TypeDef * GPIOx, uint32_t n);                     //将参数指定的引脚电平置低
void GPIO_InvBit(GPIO_TypeDef * GPIOx, uint32_t n);                     //将参数指定的引脚电平反转
uint32_t GPIO_GetBit(GPIO_TypeDef * GPIOx, uint32_t n);                 //读取参数指定的引脚的电平状态
void GPIO_SetBits(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t w);        //将参数指定的从n开始的w位连续引脚的电平置高
void GPIO_ClrBits(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t w);        //将参数指定的从n开始的w位连续引脚的电平置低
void GPIO_InvBits(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t w);        //将参数指定的从n开始的w位连续引脚的电平反转
uint32_t GPIO_GetBits(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t w);    //读取参数指定的从n开始的w位连续引脚的电平状态


void GPIO_AtomicSetBits(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t w);
void GPIO_AtomicClrBits(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t w);
void GPIO_AtomicInvBits(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t w);


// for compatibility
#define GPIO_AtomicSetBit   GPIO_SetBit
#define GPIO_AtomicClrBit   GPIO_ClrBit
#define GPIO_AtomicInvBit   GPIO_InvBit


#endif //__SWM341_GPIO_H__
