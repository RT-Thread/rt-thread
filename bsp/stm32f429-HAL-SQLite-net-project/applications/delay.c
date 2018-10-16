#include <rtthread.h>
#include <board.h>

static rt_uint32_t fac_us=0;							//us延时倍乘数
			   
//初始化延迟函数
//当使用ucos的时候,此函数会初始化ucos的时钟节拍
//SYSTICK的时钟固定为AHB时钟
//SYSCLK:系统时钟频率
int delay_init(void)
{
	fac_us=RT_HSE_HCLK/1000000;						//不论是否使用OS,fac_us都需要使用
	return 0;
}
INIT_BOARD_EXPORT(delay_init);

//延时nus
//nus为要延时的us数.	
//nus:0~190887435(最大值即2^32/fac_us@fac_us=22.5)	 
void delay_us(rt_uint32_t nus)
{		
	rt_uint32_t ticks;
	rt_uint32_t told,tnow,tcnt=0;
	rt_uint32_t reload=SysTick->LOAD;				//LOAD的值	    	 
	ticks=nus*fac_us; 						//需要的节拍数 
	told=SysTick->VAL;        				//刚进入时的计数器值
	while(1)
	{
		tnow=SysTick->VAL;	
		if(tnow!=told)
		{	    
			if(tnow<told)tcnt+=told-tnow;	//这里注意一下SYSTICK是一个递减的计数器就可以了.
			else tcnt+=reload-tnow+told;	    
			told=tnow;
			if(tcnt>=ticks)break;			//时间超过/等于要延迟的时间,则退出.
		}  
	};
}
RTM_EXPORT(delay_us);
//延时nms
//nms:要延时的ms数
void delay_ms(rt_uint16_t nms)
{
	rt_uint32_t i;
	for(i=0;i<nms;i++) delay_us(1000);
}
RTM_EXPORT(delay_ms);
