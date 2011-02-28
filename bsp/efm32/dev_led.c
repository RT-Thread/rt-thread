/******************************************************************//**
 * @file 		dev_led.c
 * @brief 	LED driver of RT-Thread RTOS for EFM32
 * 	COPYRIGHT (C) 2011, RT-Thread Development Team
 * @author 	Bernard, onelife
 * @version 	0.4 beta
 **********************************************************************
 * @section License
 * The license and distribution terms for this file may be found in the file LICENSE in this 
 * distribution or at http://www.rt-thread.org/license/LICENSE
 **********************************************************************
 * @section Change Logs
 * Date			Author		Notes
 * 2009-01-05	Bernard		the first version
 * 2010-12-27	onelife		modify for EFM32
 *********************************************************************/

/******************************************************************//**
 * @addtogroup efm32
 * @{
*********************************************************************/

/* Includes -------------------------------------------------------------------*/
#include "board.h"
#include "dev_led.h"

/* Private typedef -------------------------------------------------------------*/
/* Private define --------------------------------------------------------------*/
/* Private macro --------------------------------------------------------------*/
/* Private constants -----------------------------------------------------------*/
static const rt_uint8_t	leds_list[LEDS_MAX_NUMBER][2] = \
{
	{LEDS_PIN_PORT_0, LEDS_PIN_NUMBER_0},
	{LEDS_PIN_PORT_1, LEDS_PIN_NUMBER_1},
	{LEDS_PIN_PORT_2, LEDS_PIN_NUMBER_2},
	{LEDS_PIN_PORT_3, LEDS_PIN_NUMBER_3}
};

/* Private variables ------------------------------------------------------------*/
/* Private function prototypes ---------------------------------------------------*/
/* Private functions ------------------------------------------------------------*/
/******************************************************************//**
 * @brief
 *   Turn on a LED
 *
 * @details
 *
 * @note
 *
 * @param[in] num
 *   LED number
 *
 *********************************************************************/
void rt_hw_led_on(rt_uint8_t num)
{
	RT_ASSERT(num < LEDS_MAX_NUMBER);
	
	GPIO_PinOutSet(leds_list[num][0], leds_list[num][1]);
}

/******************************************************************//**
 * @brief
 *   Turn off a LED
 *
 * @details
 *
 * @note
 *
 * @param[in] num
 *   LED number
 *
 *********************************************************************/
void rt_hw_led_off(rt_uint8_t num)
{
	RT_ASSERT(num < LEDS_MAX_NUMBER);
	
	GPIO_PinOutClear(leds_list[num][0], leds_list[num][1]);
}

/******************************************************************//**
 * @brief
 *   Toggle the state of a LED
 *
 * @details
 *
 * @note
 *
 * @param[in] num
 *   LED number
 *
 *********************************************************************/
void rt_hw_led_toggle(rt_uint8_t num)
{
	RT_ASSERT(num < LEDS_MAX_NUMBER);
	
	GPIO_PinOutToggle(leds_list[num][0], leds_list[num][1]);
}

rt_uint8_t rt_hw_led_state(rt_uint8_t num)
{
	RT_ASSERT(num < LEDS_MAX_NUMBER);
	
	return (rt_uint8_t)GPIO_PinInGet(leds_list[num][0], leds_list[num][1]);
}

/******************************************************************//**
 * @brief
 *   Initialize the LEDs related GPIO
 *
 * @details
 *
 * @note
 *
 * @return
 *	 Error code
 *********************************************************************/
rt_err_t rt_hw_led_init(void)
{
	rt_uint8_t i;
		
	/* Configure GPIO */
	for (i = 0; i < LEDS_MAX_NUMBER; i++)
	{
		GPIO_PinModeSet(
			leds_list[i][0],
			leds_list[i][1],
			gpioModePushPull,
			0);
	}

	return RT_EOK;
}

/*********************************************************************
* 	Export to FINSH
*********************************************************************/
#ifdef RT_USING_FINSH
#include <finsh.h>

void list_leds(void)
{
	rt_uint8_t i;

	rt_kprintf(" led  \t port \t pin  \t state\n");
	rt_kprintf(" -----\t -----\t -----\t -----\n");

    for (i = 0; i < LEDS_MAX_NUMBER; i++)
	{
		rt_kprintf(" %d    \t %x    \t %x    \t %x    \n", 
			i, leds_list[i][0], leds_list[i][1], rt_hw_led_state(i));
	}
}
FINSH_FUNCTION_EXPORT(list_leds, list all the LEDs.)

void set_led(rt_uint32_t led, rt_uint32_t state)
{
	/* set led status */
	switch (state)
	{
	case 0:
		rt_hw_led_off(led);
		break;
	case 1:
		rt_hw_led_on(led);
		break;
	default:
		break;
	}
}
FINSH_FUNCTION_EXPORT(set_led, turn led (0 - 3) on (1) or off (0).)
#endif

/******************************************************************//**
 * @}
*********************************************************************/
