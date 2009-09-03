#include <rtthread.h>
#include "stm32f10x.h"

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures the nested vectored interrupt controller.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{
#ifdef  VECT_TAB_RAM
    /* Set the Vector Table base location at 0x20000000 */
    NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);
#else  /* VECT_TAB_FLASH  */
    /* Set the Vector Table base location at 0x08000000 */
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
#endif
}

/*******************************************************************************
 * Function Name  : SysTick_Configuration
 * Description    : Configures the SysTick for OS tick.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void  SysTick_Configuration(void)
{
    RCC_ClocksTypeDef  rcc_clocks;
    rt_uint32_t         cnts;

    RCC_GetClocksFreq(&rcc_clocks);

    cnts = (rt_uint32_t)rcc_clocks.HCLK_Frequency / RT_TICK_PER_SECOND;

    SysTick_Config(cnts);
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
}

/* init console to support rt_kprintf */
static void rt_hw_console_init()
{
    /* Enable USART1 and GPIOA clocks */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

    /* GPIO configuration */
    {
        GPIO_InitTypeDef GPIO_InitStructure;

        /* Configure USART1 Tx (PA.09) as alternate function push-pull */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        /* Configure USART1 Rx (PA.10) as input floating */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }

    /* USART configuration */
    {
        USART_InitTypeDef USART_InitStructure;

        /* USART1 configured as follow:
        	- BaudRate = 115200 baud
        	- Word Length = 8 Bits
        	- One Stop Bit
        	- No parity
        	- Hardware flow control disabled (RTS and CTS signals)
        	- Receive and transmit enabled
        	- USART Clock disabled
        	- USART CPOL: Clock is active low
        	- USART CPHA: Data is captured on the middle
        	- USART LastBit: The clock pulse of the last data bit is not output to
        	  the SCLK pin
        */
        USART_InitStructure.USART_BaudRate = 115200;
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
        USART_InitStructure.USART_StopBits = USART_StopBits_1;
        USART_InitStructure.USART_Parity = USART_Parity_No;
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
        USART_Init(USART1, &USART_InitStructure);
        /* Enable USART1 */
        USART_Cmd(USART1, ENABLE);
    }
}

/* write one character to serial, must not trigger interrupt */
static void rt_hw_console_putc(const char c)
{
    /*
    	to be polite with serial console add a line feed
    	to the carriage return character
    */
    if (c=='\n')rt_hw_console_putc('\r');

    while (!(USART1->SR & USART_FLAG_TXE));
    USART1->DR = (c & 0x1FF);
}

/**
 * This function is used by rt_kprintf to display a string on console.
 *
 * @param str the displayed string
 */
void rt_hw_console_output(const char* str)
{
    while (*str)
    {
        rt_hw_console_putc (*str++);
    }
}

void board_init(void)
{
    /* NVIC Configuration */
    NVIC_Configuration();

    /* Configure the SysTick */
    SysTick_Configuration();

    rt_hw_console_init();
}

/**
 * This is the timer interrupt service routine.
 *
 */
extern void rt_hw_interrupt_thread_switch(void);
void rt_hw_timer_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
    rt_hw_interrupt_thread_switch();
}
