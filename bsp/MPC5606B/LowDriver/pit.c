/*
 * pit.c
 *
 *  Created on: 2018年1月2日
 *      Author: Administrator
 */
#include"pit.h"
#include "lowdriver.h"
__weak void pit_interrupt(uint8_t chNumber)
{
	(void)chNumber;
}
static uint32_t osalsystime=0;
volatile struct PIT_tag * debugPIT=&PIT;
void pit0_interrupt(void)
{
	pit_interrupt(0);
	osalsystime++;
	PIT.CH[0].TFLG.R=1;
}
void pit1_interrupt(void)
{
	pit_interrupt(1);
	PIT.CH[1].TFLG.R=1;
}
void pit2_interrupt(void)
{
	pit_interrupt(2);
	PIT.CH[2].TFLG.R=1;
}
void pit3_interrupt(void)
{
	pit_interrupt(3);
	PIT.CH[3].TFLG.R=1;
}
void pit4_interrupt(void)
{
	pit_interrupt(4);
	PIT.CH[4].TFLG.R=1;
}
void pit5_interrupt(void)
{
	pit_interrupt(5);
	PIT.CH[5].TFLG.R=1;
}
void pit6_interrupt(void)
{
	pit_interrupt(6);
	PIT.CH[6].TFLG.R=1;
}
void pit7_interrupt(void)
{
	pit_interrupt(7);
	PIT.CH[7].TFLG.R=1;
}
void pit_init(void)
{
    PIT.PITMCR.R      = 1;        /* PIT clock enabled, stop while debugging. */
    pit_start(0,15,1000);
}
/*
 * chNumber:通道数 0-7
 * pri 0-15 数字越高，优先级越大
 * ticks_per_sec:1秒内的tick数目
 * */
void pit_start(uint8_t chNumber,uint8_t pri,uint16_t ticks_per_sec)
{
	uint16_t psrIndex=0;
	uint32_t reg=0;
	switch(chNumber)
	{
	case 0:
		psrIndex=59;
		break;
	case 1:
		psrIndex=60;
		break;
	case 2:
		psrIndex=61;
		break;
	case 3:
		psrIndex=127;
		break;
	case 4:
		psrIndex=128;
		break;
	case 5:
		psrIndex=129;
		break;
	case 6:
		psrIndex=130;
		break;
	case 7:
		psrIndex=131;
		break;
	}
	INTC.PSR[psrIndex].B.PRI=pri;

	reg = (((uint32_t)SystemTicks) / ticks_per_sec) - 1U;
	PIT.CH[chNumber].LDVAL.R = reg;
	PIT.CH[chNumber].CVAL.R  = reg;
	PIT.CH[chNumber].TFLG.R  = 1;        /* Interrupt flag cleared.                  */
	PIT.CH[chNumber].TCTRL.R = 3;        /* Timer active, interrupt enabled.         */
}
void PITDelay(uint32_t ticks) {

	uint32_t current;

  current = osalsystime;
  while (osalsystime < current + ticks) {
  }

}
