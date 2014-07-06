//usb.c
#include "finsh.h"
#include "ToCOM\usb.h"
#include "stm32f10x.h"
#include "serial.h"
#define   private user_data
rt_sem_t  usb_sem = RT_NULL;
rt_sem_t  usb_sem_rx = RT_NULL;
struct stm32_serial_int_rx  usb_rx;
struct stm32_serial_device usb_serial={RT_NULL,&usb_rx};
struct rt_device  usb_device;
/**
 * @addtogroup STM32
 */
/*@{*/

/* RT-Thread Device Interface */
static rt_err_t rt_usb_init (rt_device_t dev)
{
	struct stm32_serial_device* usb_serial = (struct stm32_serial_device*) dev->private;

	usb_sem = rt_sem_create("sem", 1, RT_IPC_FLAG_FIFO);
  usb_sem_rx = rt_sem_create("sem_rx", 0, RT_IPC_FLAG_PRIO);
	if (!(dev->flag & RT_DEVICE_FLAG_ACTIVATED))
	{
		
		rt_memset(usb_serial->int_rx->rx_buffer, 0,
			sizeof(usb_serial->int_rx->rx_buffer));
		usb_serial->int_rx->read_index = 0;
		usb_serial->int_rx->save_index = 0;
		dev->flag |= RT_DEVICE_FLAG_ACTIVATED;
	}

	return RT_EOK;
}

static rt_err_t rt_usb_open(rt_device_t dev, rt_uint16_t oflag)
{
	//;//上电，到枚举完成说明打开成功
// 	PowerOff();

	  if(oflag==3)
		{
		Set_System();
    Set_USBClock();
    USB_Interrupts_Config();
    TO_COM_USB_Init();
		}
		else if(oflag==1)
		udisk_USB_cable();
	return RT_EOK;
}
extern uint8_t* Data_Buffer;
static rt_err_t rt_usb_close(rt_device_t dev)
{
	//;//掉电
	PowerOff();
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, DISABLE);
	if(Data_Buffer)
	{
	rt_free(Data_Buffer);
	Data_Buffer=0;
	}
	return RT_EOK;
}

static rt_size_t rt_usb_read (rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	rt_uint8_t* ptr;
	rt_err_t err_code;
	struct stm32_serial_device* usb_serial;
	struct stm32_serial_int_rx* usb_rx;

	ptr = buffer;
	err_code = RT_EOK;
	usb_serial = (struct stm32_serial_device*)dev->private;
	usb_rx = usb_serial->int_rx;

	rt_sem_take(usb_sem_rx, 10);

	while(size)
	{
		if (usb_rx->read_index != usb_rx->save_index)
		{
			/* read a character */
			*ptr++ = usb_rx->rx_buffer[usb_rx->read_index];
			size--;
		
			/* move to next position */
			usb_rx->read_index ++;
			if (usb_rx->read_index >= USB_BUFFER_SIZE)
				usb_rx->read_index = 0;
		}
		else
		{
			/* set error code */
			err_code = -RT_EEMPTY;
		
			break;
		}
	}

	//rt_sem_release(usb_sem);

	/* set error code */
	rt_set_errno(err_code);
	return (rt_uint32_t)ptr - (rt_uint32_t)buffer;
}

void USB_SEND_DATA(uint8_t *pbUsrBuf, uint16_t wNBytes);
static rt_size_t rt_usb_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
	rt_uint8_t* ptr;
	rt_uint32_t  times,remainder;
	rt_err_t err_code;

	err_code = RT_EOK;
	ptr = (rt_uint8_t*)buffer;
	if(size==0)
	{
  return 0;
}
	
  	if (dev->flag & RT_DEVICE_FLAG_STREAM)
		{

			if(*(ptr+size-1)=='\n')
			{
				*(ptr+size-1)='\r';
				*(ptr+size++)='\n';	
        *(ptr+size)=0;
			}
			
 }
	times = size/USB_BUFFER_SIZE;
	remainder =  size%USB_BUFFER_SIZE;
	rt_sem_take(usb_sem, RT_WAITING_FOREVER);
	while(times--)
	{
			USB_SEND_DATA(ptr, USB_BUFFER_SIZE);
			ptr = ptr + USB_BUFFER_SIZE;		
	}
  if(remainder)
	USB_SEND_DATA(ptr, remainder);
	
	ptr+=remainder;
	/* set error code */
	rt_set_errno(err_code);
	rt_sem_release(usb_sem);	
	return (rt_uint32_t)ptr - (rt_uint32_t)buffer;
}

static rt_err_t rt_usb_control (rt_device_t dev, rt_uint8_t cmd, void *args)
{
	return RT_EOK;
}
rt_err_t rt_hw_usbhid_register(rt_device_t device, const char* name, rt_uint32_t flag, struct stm32_serial_device *usb)
{
	RT_ASSERT(device != RT_NULL);

	device->type 		= RT_Device_Class_Char;
	device->rx_indicate = RT_NULL;
	device->tx_complete = RT_NULL;
	device->init 		= rt_usb_init;
	device->open		= rt_usb_open;
	device->close		= rt_usb_close;
	device->read 		= rt_usb_read;
	device->write 		= rt_usb_write;
	device->control 	= rt_usb_control;
	device->private		= usb;

	/* register a character device */
	return rt_device_register(device, name, flag);
}

void rt_hw_usb_init(void)
{
// 	  Set_System();
//     Set_USBClock();
//     USB_Interrupts_Config();
//     USB_Init();
//     GPIO_SetBits(GPIOA, GPIO_Pin_12);
	  rt_hw_usbhid_register(&usb_device, "usb",
		RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX ,
		&usb_serial);
}

void SetShell_usb()
{
	
	rt_console_set_device("usb");	
	finsh_set_device("usb");
	
}
FINSH_FUNCTION_EXPORT(SetShell_usb,Setfinsh to virtual_com );