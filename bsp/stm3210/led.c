#include <rtthread.h>
#include <stm32f10x.h>

#define RCC_APB2Periph_GPIO_LED		RCC_APB2Periph_GPIOF
#define GPIO_LED					GPIOF
#define GPIO_Pin_LED				GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9

static const rt_uint16_t led_map[] = {GPIO_Pin_6, GPIO_Pin_7, GPIO_Pin_8, GPIO_Pin_9};
static rt_uint8_t led_inited = 0;

static void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_LED;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_LED, &GPIO_InitStructure);
}

void LED_Configuration(void)
{
	/* enable led clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO_LED, ENABLE);

	GPIO_Configuration();
}

void rt_hw_led_init()
{
	/* init led configuration if it's not inited. */
	if (!led_inited) 
	{
		LED_Configuration();
		led_inited = 1;
	}
}

void rt_hw_led_on(rt_uint32_t led)
{
	if (led < sizeof(led_map)/sizeof(rt_uint16_t))
		GPIO_SetBits(GPIO_LED, led_map[led]);
}

void rt_hw_led_off(rt_uint32_t led)
{
	if (led < sizeof(led_map)/sizeof(rt_uint16_t))
		GPIO_ResetBits(GPIO_LED, led_map[led]);
}

#ifdef RT_USING_FINSH
#include <finsh.h>
void led(rt_uint32_t led, rt_uint32_t value)
{
	/* init led configuration if it's not inited. */
	if (!led_inited) 
	{
		LED_Configuration();
		led_inited = 1;
	}

	/* set led status */
	if (value)
		rt_hw_led_on(led);
	else
		rt_hw_led_off(led);
}
FINSH_FUNCTION_EXPORT(led, set led[0 - 3] on[1] or off[0].)
#endif

