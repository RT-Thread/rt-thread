void rt_hw_led_init(void)
{
	return;
}
#include <stdint.h>
#include "platform.h"

void rt_hw_led_on(int led)
{


	uint16_t r=0xFF;
	uint16_t g=0;
	uint16_t b=0;
	char c = 0;

	// Set up RGB PWM

	/* 
	   PWM1_REG(PWM_CFG)   = 0;
	// To balance the power consumption, make one left, one right, and one center aligned.
	PWM1_REG(PWM_CFG)   = (PWM_CFG_ENALWAYS) | (PWM_CFG_CMP2CENTER);
	PWM1_REG(PWM_COUNT) = 0;

	// Period is approximately 244 Hz
	// the LEDs are intentionally left somewhat dim, 
	// as the full brightness can be painful to look at.
	PWM1_REG(PWM_CMP0)  = 0;
	*/
	if(r > 0 && b == 0){
		r--;
		g++;
	}
	if(g > 0 && r == 0){
		g--;
		b++;
	}
	if(b > 0 && g == 0){
		r++;
		b--;
	}

	uint32_t G = g;
	uint32_t R = r;
	uint32_t B = b;

	PWM1_REG(PWM_CMP1)  = G << 4;            // PWM is low on the left, GPIO is low on the left side, LED is ON on the left.
	PWM1_REG(PWM_CMP2)  = (B << 1) << 4;     // PWM is high on the middle, GPIO is low in the middle, LED is ON in the middle.
	PWM1_REG(PWM_CMP3)  = 0xFFFF - (R << 4); // PWM is low on the left, GPIO is low on the right, LED is on on the right.
	return;
}
void rt_hw_led_off(int led)
{
	return;
}
