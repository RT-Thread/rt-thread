/*
 * File      : touch.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2010, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-10-01     Yi.Qiu      first version
 */

 /* 
  * Warning, this keypad driver can only work on QEMU emulator 
  */
     
#include <rtthread.h>
#include <s3c24x0.h>
#include <rthw.h>

#define KEY_RX_BUFFER_SIZE		32

struct rt_key_device
{
	struct rt_device parent;

	rt_uint32_t  rx_buffer[KEY_RX_BUFFER_SIZE];
	rt_uint32_t read_index, save_index;	
};	
static struct rt_key_device *key_device = RT_NULL;

/* save a char to serial buffer */
static void rt_key_savechar(char ch)
{
	rt_base_t level;
	
	/* disable interrupt */
	level = rt_hw_interrupt_disable();

	key_device->rx_buffer[key_device->save_index] = ch;
	key_device->save_index ++;
	if (key_device->save_index >= KEY_RX_BUFFER_SIZE)
		key_device->save_index = 0;
	
	/* if the next position is read index, discard this 'read char' */
	if (key_device->save_index == key_device->read_index)
	{
		key_device->read_index ++;
		if (key_device->read_index >= KEY_RX_BUFFER_SIZE)
			key_device->read_index = 0;
	}

	/* enable interrupt */
	rt_hw_interrupt_enable(level);
}

/* ISR for serial interrupt */
static void rt_hw_key_isr(void)
{
	/* save on rx buffer */
	rt_key_savechar(URXH1 & 0xff);

	/* invoke callback */
	if (key_device->parent.rx_indicate != RT_NULL)
	{
		rt_size_t rx_length;
		
		/* get rx length */
		rx_length = key_device->read_index > key_device->save_index ?
			KEY_RX_BUFFER_SIZE - key_device->read_index + key_device->save_index :
			key_device->save_index - key_device->read_index;

		key_device->parent.rx_indicate(&key_device->parent, rx_length);
	}	
}

/**
 * This function is only for QEMU emulation
 */
static void rt_key_handler(int vector, void *param)
{
	INTSUBMSK |= (BIT_SUB_RXD1);

	rt_hw_key_isr();
	
	SUBSRCPND |= BIT_SUB_RXD1;
	
	/*Unmask sub interrupt (RXD0)*/
	INTSUBMSK  &=~(BIT_SUB_RXD1);
}

/**
 * This function is only for QEMU emulation
 */
static void key_init(void)
{
	int i = 0;

	GPHCON |= 0xa0;
	/*PULLUP is enable */
	GPHUP  |= 0x0c;  
	
	/* FIFO enable, Tx/Rx FIFO clear */
	UFCON1 = 0x0;
	/* disable the flow control */
	UMCON1= 0x0;
	/* Normal,No parity,1 stop,8 bit */
	ULCON1 = 0x3;
	/*
	 * tx=level,rx=edge,disable timeout int.,enable rx error int.,
	 * normal,interrupt or polling
	 */
	UCON1 = 0x245;

	//UBRD0 = div;
	// UBRD0 = 0x500;	/* baudrate = 19200bps */
	UBRD1 = 0x1a;

	UTXH1 = 0x2;
	URXH1 = 0x1;

	/* output PCLK to UART0/1, PWMTIMER */
	CLKCON |= 0x0D00;

	for (i = 0; i < 100; i++);

	/* install key isr */
	INTSUBMSK &= ~(BIT_SUB_RXD1);

	rt_hw_interrupt_install(INTUART1, rt_key_handler, RT_NULL , "INTUART1");
	rt_hw_interrupt_umask(INTUART1);
}

static rt_err_t rt_key_init(rt_device_t dev)
{		
	if (!(dev->flag & RT_DEVICE_FLAG_ACTIVATED))
	{

		if (dev->flag & RT_DEVICE_FLAG_INT_RX)
		{
			rt_memset(key_device->rx_buffer, 0, 
				sizeof(key_device->rx_buffer));
			key_device->read_index = key_device->save_index = 0;
		}

		dev->flag |= RT_DEVICE_FLAG_ACTIVATED;
	}

	return RT_EOK;
}

static rt_err_t rt_key_open(rt_device_t dev, rt_uint16_t oflag)
{	
	return RT_EOK;
}

static rt_err_t rt_key_close(rt_device_t dev)
{	
	return RT_EOK;
}

static rt_size_t rt_key_read (rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	rt_uint8_t* ptr;
	rt_err_t err_code;
	rt_base_t level;
	
	ptr = buffer;
	err_code = RT_EOK;

	/* interrupt mode Rx */
	while (size)
	{
		if (key_device->read_index != key_device->save_index)
		{
			*ptr++ = key_device->rx_buffer[key_device->read_index];
			size --;

			/* disable interrupt */
			level = rt_hw_interrupt_disable();

			key_device->read_index ++;
			if (key_device->read_index >= KEY_RX_BUFFER_SIZE)
				key_device->read_index = 0;

			/* enable interrupt */
			rt_hw_interrupt_enable(level);
		}
		else
		{
			/* set error code */
			err_code = -RT_EEMPTY;
			break;
		}
	}

	/* set error code */
	rt_set_errno(err_code);
	return (rt_uint32_t)ptr - (rt_uint32_t)buffer;
}

static rt_err_t rt_key_control(rt_device_t dev, int cmd, void *args)
{
	return RT_EOK;
}

#ifdef RT_USING_RTGUI
#include <rtgui/event.h>
#include <rtgui/rtgui_server.h>
#include <rtgui/kbddef.h>

static int s_key_map[0xff] = {0};

static void rt_keymap_init(void)
{
	s_key_map[0x1] = RTGUIK_ESCAPE;
	s_key_map[0xc] = RTGUIK_MINUS;
	s_key_map[0x39] = RTGUIK_SPACE;
	s_key_map[0xd] = RTGUIK_KP_EQUALS;
	s_key_map[0xe] = RTGUIK_BACKSPACE;
	s_key_map[0xf] = RTGUIK_TAB;
	s_key_map[0x1c] = RTGUIK_KP_ENTER;
	s_key_map[0xb] = RTGUIK_0;
	s_key_map[0x2] = RTGUIK_1; 
	s_key_map[0x3] = RTGUIK_2;
	s_key_map[0x4] = RTGUIK_3;
	s_key_map[0x5] = RTGUIK_4;
	s_key_map[0x6] = RTGUIK_5;
	s_key_map[0x7] = RTGUIK_6;
	s_key_map[0x8] = RTGUIK_7;
	s_key_map[0x9] = RTGUIK_8;
	s_key_map[0xa] = RTGUIK_9;
	s_key_map[0x3b] = RTGUIK_F1; 
	s_key_map[0x3c] = RTGUIK_F2;
	s_key_map[0x3d] = RTGUIK_F3;
	s_key_map[0x3e] = RTGUIK_F4;
	s_key_map[0xef] = RTGUIK_F5;
	s_key_map[0x40] = RTGUIK_F6;
	s_key_map[0x41] = RTGUIK_F7;
	s_key_map[0x42] = RTGUIK_F8;
	s_key_map[0x43] = RTGUIK_F9;
	s_key_map[0x1e] = RTGUIK_a;
	s_key_map[0x30] = RTGUIK_b;
	s_key_map[0x2c] = RTGUIK_c;
	s_key_map[0x20] = RTGUIK_d;
	s_key_map[0x12] = RTGUIK_e;
	s_key_map[0x21] = RTGUIK_f;
	s_key_map[0x22] = RTGUIK_g;
	s_key_map[0x23] = RTGUIK_h;
	s_key_map[0x17] = RTGUIK_i;
	s_key_map[0x24] = RTGUIK_j;
	s_key_map[0x25] = RTGUIK_k;
	s_key_map[0x26] = RTGUIK_l;
	s_key_map[0x32] = RTGUIK_m;
	s_key_map[0x31] = RTGUIK_n;
	s_key_map[0x18] = RTGUIK_o;
	s_key_map[0x19] = RTGUIK_p;
	s_key_map[0x10] = RTGUIK_q;
	s_key_map[0x13] = RTGUIK_r;
	s_key_map[0x1f] = RTGUIK_s;
	s_key_map[0x14] = RTGUIK_t;
	s_key_map[0x16] = RTGUIK_u;
	s_key_map[0x2f] = RTGUIK_v;
	s_key_map[0x11] = RTGUIK_w;
	s_key_map[0x2d] = RTGUIK_x;
	s_key_map[0x15] = RTGUIK_y;
	s_key_map[0x2c] = RTGUIK_z;
	s_key_map[0x4b] = RTGUIK_LEFT;
	s_key_map[0x4d] = RTGUIK_RIGHT;
	s_key_map[0x50] = RTGUIK_DOWN;
	s_key_map[0x2e] = RTGUIK_DELETE;
	s_key_map[0x48] = RTGUIK_UP;
}	

static rt_err_t rtgui_key_rx(rt_device_t dev, rt_size_t size)
{
	struct rtgui_event_kbd kbd_event;
	char key_value;

	while(rt_device_read(dev, 0, &key_value, 1) == 1)
	{
		/* init keyboard event */
		RTGUI_EVENT_KBD_INIT(&kbd_event);
		kbd_event.mod  = RTGUI_KMOD_NONE;
		kbd_event.unicode = 0;
		kbd_event.key = RTGUIK_UNKNOWN;

		if(key_value &  0x80)
		{	
			kbd_event.type = RTGUI_KEYUP;
		}	
		else
		{
			kbd_event.type = RTGUI_KEYDOWN;
		}	

		kbd_event.key = s_key_map[key_value & 0x7F];
	}
	if (kbd_event.key != RTGUIK_UNKNOWN)
	{
		/* post down event */
		rtgui_server_post_event(&(kbd_event.parent), sizeof(kbd_event));
	}
	
	return RT_EOK;
}

#endif

/*
 * key driver register
 */
void rt_hw_key_init(void)
{
	/* hardware init */
	key_init();

	key_device = (struct rt_key_device*)rt_malloc (sizeof(struct rt_key_device));
	if (key_device == RT_NULL) return; /* no memory yet */

	/* clear device structure */
	rt_memset(&(key_device->parent), 0, sizeof(struct rt_device));
	
	key_device->parent.type 		= RT_Device_Class_Char;
	key_device->parent.tx_complete = RT_NULL;
	key_device->parent.init 		= rt_key_init;
	key_device->parent.open		= rt_key_open;
	key_device->parent.close		= rt_key_close;
	key_device->parent.read 		= rt_key_read;
	key_device->parent.write 		= RT_NULL;
	key_device->parent.control 	= rt_key_control;
	key_device->parent.user_data   = RT_NULL;

#ifdef RT_USING_RTGUI
	key_device->parent.rx_indicate = rtgui_key_rx;

	/* init keymap */
	rt_keymap_init();
#endif

	/* register key device to RT-Thread */
	rt_device_register(&(key_device->parent), "key", RT_DEVICE_FLAG_RDONLY | RT_DEVICE_FLAG_INT_RX);
}

