#include <rtthread.h> 
#include <rtdevice.h> 
#include <multi_button.h>
#ifdef USING_NRF24L01_NODE
#include <nrf_node.h>
#else
#include <nrf_gateway.h>
extern u8 Nodes[MAX_NODE_NUM];
#endif

static struct button btn0, btn1, btn2;

#define BUTTON_0_PIN	(44)
#define BUTTON_1_PIN	(43)
#define BUTTON_2_PIN	(8)

#define LED_0_PIN		(57)
#define LED_1_PIN		(56)

static uint8_t button0_read_pin(void) 
{
    return rt_pin_read(BUTTON_0_PIN); 
}

static uint8_t button1_read_pin(void) 
{
    return rt_pin_read(BUTTON_1_PIN); 
}

static uint8_t button2_read_pin(void) 
{
    return rt_pin_read(BUTTON_2_PIN); 
}

#ifdef USING_NRF24L01_NODE
void button_callback(void *btn)
{
	u8 led_tag;
	u8 data[2];
    uint32_t btn_event_val; 
    
    btn_event_val = get_button_event((struct button *)btn); 
    if(btn==&btn0)
	{
		switch(btn_event_val)
		{
			case PRESS_DOWN:
			{			
				data[0] = led_tag = !rt_pin_read(LED_0_PIN);				
				rt_pin_write(LED_0_PIN, led_tag);
				data[1] = rt_pin_read(LED_1_PIN);
				nrf_send_data(GATEWAY_ADDR, data);
				//rt_kprintf("button press down\n"); 
			}
			break; 
			case PRESS_UP: 
				//rt_kprintf("button press up\n");
			break;
			case PRESS_REPEAT: 
				//rt_kprintf("button press repeat\n");
			break; 
			case SINGLE_CLICK: 
				//rt_kprintf("button single click\n");
			break;
			case DOUBLE_CLICK: 
				//rt_kprintf("button double click\n");
			break;
			case LONG_RRESS_START: 
				nrf_reset();
				//rt_kprintf("button long press start\n");
			break; 
			case LONG_PRESS_HOLD: 
				//rt_kprintf("button long press hold\n");
			break;
		}
	}
	else if(btn==&btn1)
	{
		data[0] = 1;
		switch(btn_event_val)
		{
			case PRESS_DOWN:
			{
				data[0] = rt_pin_read(LED_0_PIN);		
				data[1] = led_tag = !rt_pin_read(LED_1_PIN);				
				rt_pin_write(LED_1_PIN, led_tag);				
				nrf_send_data(GATEWAY_ADDR, data);
				//rt_kprintf("button press down\n"); 
			}
			break; 
			case PRESS_UP: 
				//rt_kprintf("button press up\n");
			break;
			case PRESS_REPEAT: 
				//rt_kprintf("button press repeat\n");
			break; 
			case SINGLE_CLICK: 
				//rt_kprintf("button single click\n");
			break;
			case DOUBLE_CLICK: 
				//rt_kprintf("button double click\n");
			break;
			case LONG_RRESS_START: 
				//rt_kprintf("button long press start\n");
			break; 
			case LONG_PRESS_HOLD: 
				//rt_kprintf("button long press hold\n");
			break;
		}
	}
}
#else
void button_callback(void *btn)
{
	u8 led_tag;
	u8 i, data[2];
    uint32_t btn_event_val; 
    
    btn_event_val = get_button_event((struct button *)btn); 
    if(btn==&btn0)
	{
		switch(btn_event_val)
		{
			case PRESS_DOWN:
			{			
				data[0] = led_tag = !rt_pin_read(LED_0_PIN);
				rt_pin_write(LED_0_PIN, led_tag);
				data[1] = rt_pin_read(LED_1_PIN);
				for(i=ASSIGN_ADDR_START;i<ASSIGN_ADDR_END && Nodes[i];i++)
				{				
					nrf_send_data(i, data);
				}
				//rt_kprintf("button press down\n"); 
			}
			break; 
			case PRESS_UP: 
				//rt_kprintf("button press up\n");
			break;
			case PRESS_REPEAT: 
				//rt_kprintf("button press repeat\n");
			break; 
			case SINGLE_CLICK: 
				//rt_kprintf("button single click\n");
			break;
			case DOUBLE_CLICK: 
				//rt_kprintf("button double click\n");
			break;
			case LONG_RRESS_START: 
				nrf_reset();
				//rt_kprintf("button long press start\n");
			break; 
			case LONG_PRESS_HOLD: 
				//rt_kprintf("button long press hold\n");
			break;
		}
	}
	else if(btn==&btn1)
	{
		data[0] = 1;
		switch(btn_event_val)
		{
			case PRESS_DOWN:
			{		
				data[0] = rt_pin_read(LED_0_PIN);
				data[1] = led_tag = !rt_pin_read(LED_1_PIN);
				rt_pin_write(LED_1_PIN, led_tag);
				
				for(i=ASSIGN_ADDR_START;i<ASSIGN_ADDR_END && Nodes[i];i++)
				{				
					nrf_send_data(i, data);
				}
				//rt_kprintf("button press down\n"); 
			}
			break; 
			case PRESS_UP: 
				//rt_kprintf("button press up\n");
			break;
			case PRESS_REPEAT: 
				//rt_kprintf("button press repeat\n");
			break; 
			case SINGLE_CLICK: 
				//rt_kprintf("button single click\n");
			break;
			case DOUBLE_CLICK: 
				//rt_kprintf("button double click\n");
			break;
			case LONG_RRESS_START: 
				//rt_kprintf("button long press start\n");
			break; 
			case LONG_PRESS_HOLD: 
				//rt_kprintf("button long press hold\n");
			break;
		}
	}
	else if(btn==&btn2)
	{
		switch(btn_event_val)
		{
			case PRESS_DOWN:
			{			
				nrf_assign_addr();
				//rt_kprintf("button press down\n"); 
			}
			break; 
			case PRESS_UP: 
				//rt_kprintf("button press up\n");
			break;
			case PRESS_REPEAT: 
				//rt_kprintf("button press repeat\n");
			break; 
			case SINGLE_CLICK: 
				//rt_kprintf("button single click\n");
			break;
			case DOUBLE_CLICK: 
				//rt_kprintf("button double click\n");
			break;
			case LONG_RRESS_START: 
				//rt_kprintf("button long press start\n");
			break; 
			case LONG_PRESS_HOLD: 
				//rt_kprintf("button long press hold\n");
			break;
		}
	}
}
#endif

void btn_thread_entry(void* p)
{
    while(1)
    {
        /* 5ms */
        rt_thread_delay(RT_TICK_PER_SECOND/200); 
        button_ticks(); 
    }
}

int multi_button(void)
{
    rt_thread_t thread = RT_NULL;
    
    /* Create background ticks thread */
    thread = rt_thread_create("btn", btn_thread_entry, RT_NULL, 1024, 10, 10);
    if(thread == RT_NULL)
    {
        return RT_ERROR; 
    }
    rt_thread_startup(thread);

    /* low level drive */
    rt_pin_mode  (BUTTON_0_PIN, PIN_MODE_INPUT_PULLUP); 
	rt_pin_mode  (BUTTON_1_PIN, PIN_MODE_INPUT_PULLUP); 
	rt_pin_mode  (BUTTON_2_PIN, PIN_MODE_INPUT_PULLUP); 
	
	rt_pin_mode  (LED_0_PIN, PIN_MODE_OUTPUT); 
	rt_pin_write(LED_0_PIN, 0);
	rt_pin_mode  (LED_1_PIN, PIN_MODE_OUTPUT); 
	rt_pin_write(LED_1_PIN, 0);
	
    button_init  (&btn0, button0_read_pin, PIN_LOW);
	button_init  (&btn1, button1_read_pin, PIN_LOW);
	button_init  (&btn2, button2_read_pin, PIN_LOW);
	
    button_attach(&btn0, PRESS_DOWN,       button_callback);
//    button_attach(&btn0, PRESS_UP,         button_callback);
//    button_attach(&btn0, PRESS_REPEAT,     button_callback);
//    button_attach(&btn0, SINGLE_CLICK,     button_callback);
//    button_attach(&btn0, DOUBLE_CLICK,     button_callback);
    button_attach(&btn0, LONG_RRESS_START, button_callback);
//    button_attach(&btn0, LONG_PRESS_HOLD,  button_callback);

    button_attach(&btn1, PRESS_DOWN,       button_callback);
//    button_attach(&btn1, PRESS_UP,         button_callback);
//    button_attach(&btn1, PRESS_REPEAT,     button_callback);
//    button_attach(&btn1, SINGLE_CLICK,     button_callback);
//    button_attach(&btn1, DOUBLE_CLICK,     button_callback);
//    button_attach(&btn1, LONG_RRESS_START, button_callback);
//    button_attach(&btn1, LONG_PRESS_HOLD,  button_callback);

	button_attach(&btn2, PRESS_DOWN,       button_callback);
//    button_attach(&btn1, PRESS_UP,         button_callback);
//    button_attach(&btn1, PRESS_REPEAT,     button_callback);
//    button_attach(&btn1, SINGLE_CLICK,     button_callback);
//    button_attach(&btn1, DOUBLE_CLICK,     button_callback);
//    button_attach(&btn1, LONG_RRESS_START, button_callback);
//    button_attach(&btn1, LONG_PRESS_HOLD,  button_callback);
    button_start (&btn0);
	button_start (&btn1);
	button_start (&btn2);

    return RT_EOK; 
}
INIT_APP_EXPORT(multi_button); 
