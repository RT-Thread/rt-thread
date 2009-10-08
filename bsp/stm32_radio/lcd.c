#include "stm32f10x.h"
#include "rtthread.h"
#include "fmt0371/FMT0371.h"

static rt_err_t lcd_init (rt_device_t dev)
{
    ftm0371_port_init();
    ftm0371_init();
    return RT_EOK;
}

static rt_err_t lcd_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t lcd_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t lcd_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
    /* rate control */
    return RT_EOK;
}

static rt_size_t lcd_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    unsigned int i;
    unsigned short *p;
    unsigned int x,y;

    size = size / 2;
    y = (pos/2) / 240;
    x = (pos/2)%240;

    LCD_ADDR = 0x02; // X start point
    LCD_DATA = x;

    LCD_ADDR = 0x03; // Y start point
    LCD_DATA16( y );

    LCD_ADDR = 0x0E; // start write
    p = (unsigned short *) buffer;

    if (size > (240-x))
    {
        for (i=0;i<(240-x);i++)
        {
            LCD_DATA16(*p++);
        }
        LCD_ADDR = 0x02; // X start point
        LCD_DATA = 0;

        LCD_ADDR = 0x03; // Y start point
        LCD_DATA16( y+1 );
        size -= (x+1);

        while (size--)
        {
            LCD_DATA16(*p++);
        }
    }
    else
    {
        for (i=0;i<size;i++)
        {
            LCD_DATA16(*p++);
        }
    }


    return RT_EOK;
}

struct rt_device lcd_device;
rt_err_t lcd_hw_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOF,&GPIO_InitStructure);
    GPIO_SetBits(GPIOF,GPIO_Pin_9);

    ftm0371_port_init();
    ftm0371_init();

    lcd_device.type           = RT_Device_Class_Block;
    lcd_device.rx_indicate 	= RT_NULL;
    lcd_device.tx_complete 	= RT_NULL;
    lcd_device.init           = lcd_init;
    lcd_device.open			= lcd_open;
    lcd_device.close			= lcd_close;
    lcd_device.read 			= RT_NULL;
    lcd_device.write 			= lcd_write;
    lcd_device.control 		= lcd_control;
    lcd_device.private		= RT_NULL;

    return rt_device_register(&lcd_device, "lcd",RT_DEVICE_FLAG_RDWR);
}
