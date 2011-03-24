/*
----------------------------------------------------------------------
File        : GUITOUCH.C
Purpose     : Touch screen manager
----------------------------------------------------------------------
This module handles the touch screen. It is configured in the file
GUITouch.conf.h (Should be located in the Config\ directory).
----------------------------------------------------------------------
*/
#include <rtthread.h>
#include <event.h>
#include <rtgui_server.h>
#include <lcd.h>


#define MOUSE_CLK		(1<<2 ) //GPG2
#define MOUSE_DATA		(1<<11) //GPE11

#define MOUSE_CLK_H()	(GPGDAT |= MOUSE_CLK)	
#define MOUSE_CLK_L()	(GPGDAT &= ~MOUSE_CLK)
#define MOUSE_CLK_OUT()	(GPGCON = GPGCON &(~(0x03<<4)) | (0x01<<4))

#define MOUSE_DATA_H()	(GPEDAT |= MOUSE_DATA)
#define MOUSE_DATA_L()	(GPEDAT &= ~MOUSE_DATA)
#define MOUSE_DATA_IN() (GPECON = GPECON &(~(0x03<<22)))
#define MOUSE_DATA_OUT() (GPECON = GPECON &(~(0x03<<22))|(0x01<<22))
#define MOUSE_DATA_GET() (GPEDAT & MOUSE_DATA)



static rt_int32_t  _ScreenX              = 0;    /* x-pos         */
static rt_int32_t  _ScreenY              = 0;    /* y-pos         */
static rt_int32_t  _NumBytesInBuffer     = 0;    /* bytes in rx buffer */
static rt_uint8_t  _Buttons              = 0;    /* button status */
static rt_uint8_t  _abInBuffer[3];               /* mouse rx buffer */

/*********************************************************************
* PID  (Pointer input device ... mouse/touch) 
**********************************************************************
*/
typedef struct 
{
	struct rt_device parent;
	struct rt_timer* timer;
	int x,y;
	rt_uint8_t Pressed;
} PS2_MOUSE;

static PS2_MOUSE *s_mouse = RT_NULL;

/*********************************************************************
*           _EvaPacket
**********************************************************************
从鼠标接收的数据包队列:
          | D7    D6    D5    D4    D3    D2    D1    D0
---------------------------------------------------------
1st byte  | --    --    Y-    X-     1    --    LB    RB
2nd byte  | X7    X6    X5    X4    X3    X2    X1    X0
3rd byte  | Y7    Y6    Y5    Y4    Y3    Y2    Y1    Y0
*/

static void _EvaPacket(void) 
{
	char a;

	rtgui_event_mouse_t emouse;
	emouse.parent.sender = RT_NULL;
	_Buttons = _abInBuffer[0] & 0x03;

	a = _abInBuffer[1];
	//测试X移动符号
	if(_abInBuffer[0] & 0x10) 
	{
		a = -a;
		_ScreenX  -= a;
	}        /* direction is negative, move left */
	else 
	{
		_ScreenX  += a;
	}

	a = _abInBuffer[2];
	//测试Y移动符号
	if(_abInBuffer[0] & 0x20) 
	{
		a = -a;
		_ScreenY  += a;
	}  /* direction is negative, move down */ 
	else 
	{
		_ScreenY  -= a;
	}

	/* check min/max positions */    
	if(_ScreenX < 0) 
	{
		_ScreenX = 0;
	} 
	else if(_ScreenX > LCD_XSIZE-1) 
	{
		_ScreenX = LCD_XSIZE-1;
	} 
	
	if(_ScreenY < 0) 
	{
		_ScreenY = 0;
	} 
	else if(_ScreenY > LCD_YSIZE-1) 
	{
		_ScreenY = LCD_YSIZE-1;
	}

	/* signal new mouse data */
	emouse.parent.type = RTGUI_EVENT_MOUSE_BUTTON;
	emouse.x       = _ScreenX;
	emouse.y       = _ScreenY;
	emouse.button  = _Buttons;
	//GUI_MOUSE_StoreState(&emouse);
	rtgui_server_post_event((&emouse.parent), sizeof(emouse));
}


/*********************************************************************
  Mouse receive interrupt handler
  The PS2 mouse interrupt gets in three bytes from the mouse, then wakes
  up  the mouse LSR.
**********************************************************************/

void GUI_MOUSE_DRIVER_PS2_OnRx(rt_uint8_t Data) 
{
	if(!_NumBytesInBuffer) 
	{
		/* check for start frame */
		if((Data & 0x0c) == 0x08) 
		{
			_abInBuffer[0] = Data;
			_NumBytesInBuffer++;
		}
	} 
	else 
	{
		_abInBuffer[_NumBytesInBuffer] = Data;
		_NumBytesInBuffer++;
		if(_NumBytesInBuffer >= 3) 
		{
			_EvaPacket();
			_NumBytesInBuffer = 0;
		}
	}
}

/*********************************************************************
*
*       GUI_MOUSE_DRIVER_PS2_Init
*
**********************************************************************
*/

void mouse_PS2_init(void) 
{
	_NumBytesInBuffer = 0; 
}

static void mouse_timer_fire(void* parameter)
{

}

void rtgui_PS2_hw_init(void)
{
	s_mouse = (PS2_MOUSE*)rt_malloc (sizeof(PS2_MOUSE));
	if(s_mouse == RT_NULL) return; /* no memory yet */

	/* clear device structure */
	rt_memset(&(s_mouse->parent), 0, sizeof(struct rt_device));

	/* init device structure */
	s_mouse->parent.type = RT_Device_Class_Unknown;
	s_mouse->parent.init = RT_NULL;//rtgui_mouse_init;
	s_mouse->parent.control = RT_NULL;//rtgui_touch_control;
	s_mouse->parent.private = RT_NULL;

	/* create 1/8 second timer */
	s_mouse->timer = rt_timer_create("mouse", mouse_timer_fire, RT_NULL,
	                                    RT_TICK_PER_SECOND/10, RT_TIMER_FLAG_PERIODIC);

	/* register touch device to RT-Thread */
	rt_device_register(&(s_mouse->parent), "mouse", RT_DEVICE_FLAG_RDWR);

	s_mouse->parent.init(RT_NULL);
}

