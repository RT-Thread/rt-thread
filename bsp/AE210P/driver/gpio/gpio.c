#include "gpio.h"
//#include "hal.h"
#include "bsp_hal.h"

struct gpio_dev_t *gpio_p;

//static void _gpio_lisr(int vector)
//{
//	DEBUG(0, 1, "Enter\n");
//	if (vector != IRQ_GPIO_VECTOR)
//		hal_system_error(HAL_ERR_UNHANDLED_INTERRUPT);
//
//	/* Disable GPIO interrupt */
//	uint32_t prv_msk = hal_intc_irq_mask(IRQ_GPIO_VECTOR);
//
//	/* Get int state and then clear it */
//	unsigned int int_sr = IN32(GPIOC_INT_RAW_STATE);
//	gpio_p->int_data = int_sr;
//	OUT32(GPIOC_INT_CLEAR, int_sr);
//
//	/* Clean GPIO pending */
//	hal_intc_irq_clean(IRQ_GPIO_VECTOR);
//
//	/* Enable higher priority interrupt */
//	/* comment it to disable nested interrupt */
//	GIE_ENABLE();
//	hal_raise_bh(&gpio_p->hisr);
//
//	GIE_DISABLE();
//	/* - Enable GPIO interrupt */
//	hal_intc_irq_unmask(prv_msk);
//}

int gpio_init(struct gpio_dev_t *gpio)
{
//	int  status = HAL_SUCCESS;
//	int  core_intl;
//
//	/* initialize global gpio pointer */
//	gpio_p = gpio;
//	core_intl = hal_global_int_ctl(HAL_DISABLE_INTERRUPTS);
//
//	/* INTC */
//	// - Disable GPIO interrupt
//	hal_intc_irq_disable(IRQ_GPIO_VECTOR);
//	// - Clear GPIO interrupt status
//	hal_intc_irq_clean(IRQ_GPIO_VECTOR);
//	// - Setup #PENIRQ trigger mode - edge trigger
//	// - Setup #PENIRQ trigger level - active high
//	hal_intc_irq_config(IRQ_GPIO_VECTOR, IRQ_EDGE_TRIGGER, IRQ_ACTIVE_HIGH);
//
//
//	/* GPIO */
//	/* falling, interrupt when pressed */
//        //OUT32(GPIOC_INT_RISE_NEG, 0xFFFFFFFF);
//	/* rising, interrupt when released */
//        OUT32(GPIOC_INT_RISE_NEG, 0x0);
//	/* enable all gpio interrupt GPIO1-5*/
//        OUT32(GPIOC_INT_ENABLE, 0x3E);
//	/* set the max value to debounce */
//	OUT32(GPIOC_INT_BOUNCE_PRESCALE, 0xFFFF);
//	/* enable debounce */
//	OUT32(GPIOC_INT_BOUNCE_ENABLE, 0x3E);
//
//	status = hal_register_isr(IRQ_GPIO_VECTOR, _gpio_lisr, (void*)0);
//
//	if (status != HAL_SUCCESS){
//		DEBUG(1, 1, "Failed to register GPIO driver LISR!\n");
//		return status;
//	}
//
//	status = hal_create_bh(&gpio->hisr);
//	if (status != HAL_SUCCESS){
//		DEBUG(1, 1, "Failed to create GPIO driver HISR!\n");
//		return status;
//	}
//
//	// - Enable GPIO interrupt
//	hal_intc_irq_enable(IRQ_GPIO_VECTOR);
//
//	/* Restore CPU interrupt controller to previous level */
//	hal_global_int_ctl(core_intl);
//	return status;

	return 0;
}
