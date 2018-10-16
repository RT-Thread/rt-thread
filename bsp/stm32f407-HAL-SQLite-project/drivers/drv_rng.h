#ifndef __DRV_RNG_H__
#define __DRV_RNG_H__

#include <rtthread.h>

int RNG_Init(void);
rt_uint32_t RNG_Get_RandomNum(void);//得到随机数
int RNG_Get_RandomRange(int min,int max);//生成[min,max]范围的随机数

#endif

