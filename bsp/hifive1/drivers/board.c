#include <interrupt.h>
#include <rthw.h>
#include <platform.h>
#if 0
static struct mem_desc hw_mem_desc[] =
{
    { 0x00000000, 0xFFFFFFFF, 0x00000000, RW_NCNB },/* None cached for 4G memory */
//  visual start, visual end, phy start , props
    { 0x00000000, 0x000FFFFF, 0x20000000, RW_CB },  /* ISR Vector table */
    { 0x00200000, 0x00001FFF, 0x40000000, RW_CB },  /* 8K cached SRAM 0/1 */
    { 0x20000000, 0x21FFFFFF, 0x20000000, RW_CB },  /* 32M cached SDRAM */
    { 0x90000000, 0x90001FFF, 0x40000000, RW_NCNB },/* 4K SRAM0 + 4k SRAM1 */
    { 0xA0000000, 0xA1FFFFFF, 0x20000000, RW_NCNB },/* 32M none-cached SDRAM */
};
#endif

#include <encoding.h>
static void rt_hw_timer_init(void)
{
	GPIO_REG(GPIO_INPUT_EN)    &= ~((0x1<< RED_LED_OFFSET) | (0x1<< GREEN_LED_OFFSET) | (0x1 << BLUE_LED_OFFSET)) ;
	GPIO_REG(GPIO_OUTPUT_EN)   |=  ((0x1<< RED_LED_OFFSET)| (0x1<< GREEN_LED_OFFSET) | (0x1 << BLUE_LED_OFFSET)) ;
	GPIO_REG(GPIO_OUTPUT_VAL)  |=   (0x1 << BLUE_LED_OFFSET) ;
	GPIO_REG(GPIO_OUTPUT_VAL)  &=  ~((0x1<< RED_LED_OFFSET) | (0x1<< GREEN_LED_OFFSET)) ;
	
/*	enable timer interrupt*/
 	set_csr(mie, MIP_MTIP);	
	volatile uint64_t * mtimecmp    = (uint64_t*) (CLINT_CTRL_ADDR + CLINT_MTIMECMP);
	CLINT_REG(CLINT_MTIME) = 0x0;
/*	CLINT_REG(CLINT_MTIMECMP) = 0x10000;*/
	*mtimecmp = 0x20000;
	return;
}
void rt_hw_board_init(void)
{
	/* initialize mmu */
/*	rt_hw_mmu_init(hw_mem_desc, sizeof(hw_mem_desc)/sizeof(hw_mem_desc[0]));*/
	/* initialize hardware interrupt */
	rt_hw_interrupt_init();

	/* initialize the system clock */
	//rt_hw_clock_init(); //set each pll etc.

	/* initialize uart */
	rt_hw_uart_init();
	rt_console_set_device(RT_CONSOLE_DEVICE_NAME);

	/* initialize timer0 */
	rt_hw_timer_init();

#ifdef RT_USING_COMPONENTS_INIT
	rt_components_board_init();
#endif

	return;
}

