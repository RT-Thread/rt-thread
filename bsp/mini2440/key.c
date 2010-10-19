#include <rtthread.h>
#include <s3c24x0.h>

#ifdef RT_USING_RTGUI
#include <rtgui/event.h>
#include <rtgui/rtgui_server.h>
#endif

static void key_handle(int key_value)
{
#ifdef RT_USING_RTGUI
	struct rtgui_event_kbd kbd_event;
	
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
	
	key_value &= 0x7F;
	switch(key_value)
	{
	case 80:	
		kbd_event.key  = RTGUIK_DOWN;
		break;	
	case 72:
		kbd_event.key  = RTGUIK_UP;
		break;
	case 77:
		kbd_event.key  = RTGUIK_RIGHT;
		break;
	case 75:
		kbd_event.key  = RTGUIK_LEFT;
		break;
	case 31:
		kbd_event.key  = 's';
		break;
	case 30:
		kbd_event.key  = 'a';
		break;
	case 44:
		kbd_event.key  = 'z';
		break;
	case 45:
		kbd_event.key  = 'x';
		break;
	case 46:
		kbd_event.key  = 'c';
		break;
	case 16:
		kbd_event.key  = 'q';
		break;
	case 33:
		kbd_event.key  = 'r';
		break;
	case 23:
		kbd_event.key  = 'i';
		break;
	case 50:
		kbd_event.key  = 'm';
		break;
	case 38:
		kbd_event.key  = 'l';
		break;
	case 47:
		kbd_event.key  = 'v';
		break;				
		
	default:
		break;
	}
	
	if (kbd_event.key != RTGUIK_UNKNOWN)
	{
		/* post down event */
		rtgui_server_post_event(&(kbd_event.parent), sizeof(kbd_event));
	}
#endif
}

/**
 * This function is only for QEMU emulation
 */
void rt_virtual_key_isr(int vector)
{
	INTSUBMSK |= (BIT_SUB_RXD1);

	key_handle(URXH1);
	
	SUBSRCPND |= BIT_SUB_RXD1;
	
	/*Unmask sub interrupt (RXD0)*/
	INTSUBMSK  &=~(BIT_SUB_RXD1);
}

/**
 * This function is only for QEMU emulation
 */
void rt_hw_key_init(void)
{
	unsigned long i;

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

	/* install keypad isr */
	INTSUBMSK &= ~(BIT_SUB_RXD1);

	rt_hw_interrupt_install(INTUART1, rt_virtual_key_isr, RT_NULL);
	rt_hw_interrupt_umask(INTUART1);
}

