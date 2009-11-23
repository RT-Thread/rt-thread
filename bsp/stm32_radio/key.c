#include <rtthread.h>
#include <stm32f10x.h>

#include <rtgui/event.h>
#include <rtgui/rtgui_server.h>

/*
key_enter   PA0
key_down    PA1
key_up      PA2
key_right   PC2
key_left    PC3
*/
#define key_enter_GETVALUE()  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)
#define key_down_GETVALUE()   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)
#define key_up_GETVALUE()     GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)
#define key_right_GETVALUE()  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)
#define key_left_GETVALUE()   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3)

static void key_thread_entry(void *parameter)
{
    rt_time_t next_delay;
    struct rtgui_event_kbd kbd_event;
    GPIO_InitTypeDef GPIO_InitStructure;

    /* init gpio configuration */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC,ENABLE);

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_Init(GPIOC,&GPIO_InitStructure);

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
    rt_thread_t key_tid;
    key_tid = rt_thread_create("key",
                               key_thread_entry, RT_NULL,
                               512, 30, 5);
    if (key_tid != RT_NULL) rt_thread_startup(key_tid);
}
