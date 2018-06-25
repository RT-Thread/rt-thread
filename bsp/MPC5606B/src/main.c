/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "derivative.h" /* include peripheral declarations */

#include "pit.h"
#include "rtthread.h"

extern void xcptn_xmpl(void);
void debugSoftDelay(int x) {
	int i = 0, j = 0;
	for (i = 0; i < x; i++)
		for (j = 0; j < 200; j++)
			;
}
void initModesAndClks(void) {
	SSCM.ERROR.R = 0x3;
	RGM.FES.R = 0xFFFFU;
	RGM.DES.R = 0xFFFFU;
	ME.MER.R = 0x0000001D; /* Enable DRUN, RUN0, SAFE, RESET modes */
	/* Initialize PLL before turning it on: */

	CGM.SC_DC0.R = (0x80 | 1); //设置外设1的时钟分频，CAN0、CAN1，CAN2在 外设1 时钟下。
	CGM.SC_DC1.R = (0x80 | 1); //设置外设2的时钟分频 2分频。
	CGM.SC_DC2.R = (0x80 | 1); //设置外设3的时钟分频，2分频。
	/* Use 1 of the next 2 lines depending on crystal frequency: */
	CGM.FMPLL_CR.R = 0x02400000; /* 8 MHz xtal: Set PLL0 to 64 MHz */

	ME.RUN[0].R = 0x001F0074; /* RUN0 cfg: 16MHzIRCON,OSC0ON,PLL0ON,syclk=PLL */

	ME.RUNPC[1].R = 0x00000010; /* Peri. Cfg. 1 settings: only run in RUN0 mode */

	ME.PCTL[16].R = 0x01; /* MPC56xxB/P/S FlexCAN0: select ME.RUNPC[1] */
	ME.PCTL[17].R = 0x01; /* MPC56xxB/S FlexCAN1:  select ME.RUNPC[1] */
	ME.PCTL[18].R = 0x01; /* MPC56xxB/S FlexCAN2:  select ME.RUNPC[1] */
	ME.PCTL[68].R = 0x01; /* MPC56xxB/S SIUL:  select ME.RUNPC[1] */
	ME.PCTL[92].R = 0x01; /* MPC56xxB/S PIT:  select ME.RUNPC[1] */
	ME.PCTL[33].R = 0x01; /* MPC56xxB/S ADC1:  select ME.RUNPC[1] */

	ME.PCTL[4].R = 0x01; /* MPC56xxB/S DSPI0:  select ME.RUNPC[1] */
	ME.PCTL[5].R = 0x01; /* MPC56xxB/S DSPI1:  select ME.RUNPC[1] */
	ME.PCTL[44].R = 0x01; /* MPC56xxB/S IIC0:  select ME.RUNPC[1] */

	// ME.PCTL[91].R = 0x01;           /* MPC56xxB/S RTC_API:  select ME.RUNPC[1] and ME.LPPC[1]*/

	/* Mode Transition to enter RUN0 mode: */
	ME.MCTL.R = 0x40005AF0; /* Enter RUN0 Mode & Key */
	ME.MCTL.R = 0x4000A50F; /* Enter RUN0 Mode & Inverted Key */
	while (ME.GS.B.S_MTRANS) {
	} /* Wait for mode transition to complete */
	/* Note: could wait here using timer and/or I_TC IRQ */
	while (ME.GS.B.S_CURRENTMODE != 4) {
	} /* Verify RUN0 is the current mode */
}
void disableWatchdog(void) {
	SWT.SR.R = 0x0000c520; /* Write keys to clear soft lock bit */
	SWT.SR.R = 0x0000d928;
	SWT.CR.R = 0x8000010A; /* Clear watchdog enable (WEN) */
}
void SystemCall(void) {
	__asm__("se_sc");
}

extern void PIT_Interrupt10ms(void);
void pit_interrupt(uint8_t chNumber) {
	(void) chNumber;
	rt_interrupt_enter();
	if (chNumber == 0) {
		rt_tick_increase();
	}
	rt_interrupt_leave();

}
struct rt_thread init1;
uint32_t init1_stack[512];
struct rt_thread init2;
uint32_t init2_stack[512];
void T1(void *arg) {
	//int p=(int)arg;
	//CANTxFrame tx0;
	//tx0.IDE=1;
	//tx0.LENGTH=8;
	//tx0.RTR=0;
	//uint32_t sp1=(uint32_t )init1.sp,sp2=(uint32_t )init2.sp;
	for (;;) {

		//tx0.ID=0x123;
		//ComponentMemcpy((void*)tx0.Data,&init1.sp,4);
		//ComponentMemcpy((void*)&(tx0.Data[4]),&init2.sp,4);
		//can_transmit(0,(const CANTxFrame*)&tx0);
		//rt_thread_delay(100);
	}
}
static rt_uint16_t GloalValueTest = 0x12;
rt_sem_t sem;
void rt_init1_thread_entry(void* parameter) {
	(void) parameter;
	//int i=0;
	//rt_uint16_t cfgWord=0x0<<16;
	for (;;) {
		//i++;
		//GloalValueTest++;
		rt_thread_delay(100);
		SIU.GPDO[28].R = ~(SIU.GPDO[28].R);
	}
}
void rt_init2_thread_entry(void* parameter) {
	(void) parameter;
	//int i=0;
	for (;;) {
		//i++;
		//rt_thread_delay(5000);

		//pal_lld_togglepad(PORT_C,PC_LED8);

	}
}
void siu_init(void) {

	SIU.PCR[28].R = 0x0200;        //开发板上的LED灯
}
extern uint32_t __heap_base__, __heap_end__;

int rt_application_init(void) {

	rt_thread_init(&init1, "init", rt_init1_thread_entry,
	RT_NULL, (void*) init1_stack, 512, 5, 10);

	rt_thread_startup(&init1);

	rt_thread_init(&init2, "init2", rt_init2_thread_entry,
	RT_NULL, (void*) init2_stack, 512, 6, 10);

	rt_thread_startup(&init2);

	/*rt_thread_t can= rt_thread_create("can",
	 T1,
	 RT_NULL,
	 512*4,
	 5,
	 10);
	 rt_thread_startup(can);*/

	sem = rt_sem_create("sem", 0, RT_IPC_FLAG_FIFO);
	/*if (init2 != RT_NULL)
	 rt_thread_startup(init2);*/

	return 0;
}
int main(void) {
	disableWatchdog();
	initModesAndClks();
	xcptn_xmpl(); /* Configure and Enable Interrupts */
	irqIsrDisable();
	siu_init();
	pit_init();
	rt_system_heap_init((void*) &__heap_base__, (void*) &__heap_end__);
	rt_system_scheduler_init();

	/* initialize timer */
	rt_system_timer_init();

	/* init timer thread */
	rt_system_timer_thread_init();

	/* init application */
	rt_application_init();

	/* init idle thread */
	rt_thread_idle_init();

	/* start scheduler */
	rt_system_scheduler_start();
	/* Application main loop.*/

	for (;;) {
	}

}

