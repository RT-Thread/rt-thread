#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <stdint.h>
#include <stdbool.h>
#include "hw_memmap.h"
#include "sysctl.h"
#include "gpio.h"
#include "pin_map.h"
#include "interrupt.h"
#include "rom_map.h"
#include "drv_gpio.h"


#ifdef RT_USING_PIN

static const struct pin_index pins[] = 
{
    _TM4C_PIN(0 ,F, 0 ),
    _TM4C_PIN(1 ,F, 1 ),
    _TM4C_PIN(2 ,F, 2 ),
    _TM4C_PIN(3 ,F, 3 ),
    _TM4C_PIN(4 ,F, 4 )
};


static struct rt_pin_irq_hdr pin_irq_hdr_tab[] =
{
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL}
};


static uint32_t pin_irq_enable_mask=0;

#define ITEM_NUM(items) sizeof(items) / sizeof(items[0])
	
	
static const struct pin_index *get_pin(uint8_t pin)
{
    const struct pin_index *index;

    if (pin < ITEM_NUM(pins))
    {
        index = &pins[pin];
        if (index->index == -1)
            index = RT_NULL;
    }
    else
    {
        index = RT_NULL;
    }
    return index;
};


static void tm4c123_pin_mode(rt_device_t dev, rt_base_t pin, rt_base_t mode)
{
    const struct pin_index *index;
    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }
				
		if(mode == PIN_MODE_INPUT)
		{
        GPIOPinTypeGPIOInput(index ->gpioBaseAddress, index->pin);
		}
		else if(mode == PIN_MODE_OUTPUT)
		{
			  GPIOPinTypeGPIOOutput(index->gpioBaseAddress, index->pin);
		}
		else if(mode == PIN_MODE_INPUT_PULLUP)
		{
				
    //
    // Make the pin(s) be inputs.
    //
				GPIODirModeSet(index->gpioBaseAddress, index->pin, GPIO_DIR_MODE_IN);
    //
    // Set the pad(s) for standard pullup operation.
    //
				GPIOPadConfigSet(index->gpioBaseAddress, index->pin, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
		}
		else if(mode == PIN_MODE_INPUT_PULLDOWN)
		{		
    //
    // Make the pin(s) be inputs.
    //
				GPIODirModeSet(index->gpioBaseAddress, index->pin, GPIO_DIR_MODE_IN);
    //
    // Set the pad(s) for standard pulldown operation.
    //
				GPIOPadConfigSet(index->gpioBaseAddress, index->pin, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
		}
		else if(mode == PIN_MODE_OUTPUT_OD)
		{
		//
		// Set the pad(s) for standard push-pull operation.
				GPIOPadConfigSet(index->gpioBaseAddress, index->pin, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_OD);
		//
		// Make the pin(s) be outputs.
				GPIODirModeSet(index->gpioBaseAddress, index->pin, GPIO_DIR_MODE_OUT);
		}
		
}

static void tm4c123_pin_write(rt_device_t dev, rt_base_t pin, rt_base_t ui8Val)
{
    const struct pin_index *index;
	  index = get_pin(pin);
	  if( index == RT_NULL)
		{
			    return;
		}
		if(ui8Val)
		{
					GPIOPinWrite(index ->gpioBaseAddress, index->pin, index->pin );
		}
		else
		{
					GPIOPinWrite(index ->gpioBaseAddress, index->pin, 0 );
		}		
}


static int tm4c123_pin_read(rt_device_t dev, rt_base_t pin)
{
    const struct pin_index *index;
		int value = 0;
	  
		index = get_pin(pin);
	  if( index == RT_NULL)
		{
			    return value;
		}
	  value = GPIOPinRead(index ->gpioBaseAddress , index ->pin );
	
    return value;
}

static rt_err_t tm4c123_pin_attach_irq(rt_device_t device, rt_int32_t pin, rt_uint32_t mode, void (*hdr)(void *args), void *args )
{
    //const struct pin_index *index;
	
    return RT_EOK;
}

static rt_err_t tm4c123_pin_dettach_irq(rt_device_t device, rt_int32_t pin)
{
    //const struct pin_index *index;
	
    return RT_EOK;
}


static rt_err_t tm4c123_pin_irq_enable(rt_device_t device, rt_base_t pin,
                                     rt_uint32_t enabled)
{
    //const struct pin_index *index;
    //const struct pin_irq_map *irqmap;
    return RT_EOK;
}


const static struct rt_pin_ops _tm4c123_pin_ops =
{
    tm4c123_pin_mode,
    tm4c123_pin_write,
    tm4c123_pin_read,
    tm4c123_pin_attach_irq,
    tm4c123_pin_dettach_irq,
    tm4c123_pin_irq_enable,
};

int rt_hw_pin_init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    return rt_device_pin_register("pin", &_tm4c123_pin_ops, RT_NULL);
}
INIT_BOARD_EXPORT(rt_hw_pin_init);

#endif   /*RT_USING_PIN*/
