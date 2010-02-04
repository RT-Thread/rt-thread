#include <rtthread.h>
#include <S3C24x0.h>

#include <rtgui/event.h>
#include <rtgui/rtgui_server.h>

/*
key_enter   GPG0
key_down    GPG3
key_up      GPG5
key_right   GPG6
key_left    GPG7
key_power   GPG11
*/
#define key_enter_GETVALUE()  (GPGDAT & (1 << 0))
#define key_down_GETVALUE()   (GPGDAT & (1 << 3))
#define key_up_GETVALUE()     (GPGDAT & (1 << 5))
#define key_right_GETVALUE()  (GPGDAT & (1 << 6))
#define key_left_GETVALUE()   (GPGDAT & (1 << 7))
#define key_power_GETVALUE()  (GPGDAT & (1 << 11))

static void key_thread_entry(void *parameter)
{
	rt_time_t next_delay;
	struct rtgui_event_kbd kbd_event;

	/* init gpio configuration */
	GPGCON = GPGCON & (~((3<<22)|(3<<6)|(3<<0)|(3<<10)|(3<<12)|(3<<14))) |
					((2<<22)|(2<<6)|(2<<0)|(2<<10)|(2<<12)|(2<<14));

	/* init keyboard event */
	RTGUI_EVENT_KBD_INIT(&kbd_event);
	kbd_event.mod  = RTGUI_KMOD_NONE;
	kbd_event.unicode = 0;

	while (1)
	{
		next_delay = 20;
		kbd_event.key = RTGUIK_UNKNOWN;

		kbd_event.type = RTGUI_KEYDOWN;
		if ( key_enter_GETVALUE() == 0 )
		{
			rt_thread_delay(next_delay);
			if (key_enter_GETVALUE() == 0)
			{
				/* HOME key */
				rt_kprintf("key_home\n");
				kbd_event.key  = RTGUIK_HOME;
			}
			else
			{
				rt_kprintf("key_enter\n");
				kbd_event.key  = RTGUIK_RETURN;
			}
		}

		if ( key_down_GETVALUE()  == 0 )
		{
			rt_kprintf("key_down\n");
			kbd_event.key  = RTGUIK_DOWN;
		}

		if ( key_up_GETVALUE()    == 0 )
		{
			rt_kprintf("key_up\n");
			kbd_event.key  = RTGUIK_UP;
		}

		if ( key_right_GETVALUE() == 0 )
		{
			rt_kprintf("key_right\n");
			kbd_event.key  = RTGUIK_RIGHT;
		}

		if ( key_left_GETVALUE()  == 0 )
		{
			rt_kprintf("key_left\n");
			kbd_event.key  = RTGUIK_LEFT;
		}

		if (kbd_event.key != RTGUIK_UNKNOWN)
		{
			/* post down event */
			rtgui_server_post_event(&(kbd_event.parent), sizeof(kbd_event));

			next_delay = 10;
			/* delay to post up event */
			rt_thread_delay(next_delay);

			/* post up event */
			kbd_event.type = RTGUI_KEYUP;
			rtgui_server_post_event(&(kbd_event.parent), sizeof(kbd_event));
		}

		/* wait next key press */
		rt_thread_delay(next_delay);
	}
}

void rt_hw_key_init()
{
	#if 0
	rt_thread_t key_tid;
	key_tid = rt_thread_create("key",
	                           key_thread_entry, RT_NULL,
	                           512, 30, 5);
	if (key_tid != RT_NULL) rt_thread_startup(key_tid);
	#endif
}
