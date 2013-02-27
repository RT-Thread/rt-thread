#include <rtthread.h>

/* rtgui\common\rtgui_object.c */
_declspec(dllimport) void * _rtgui_object;

/* rtgui\common\color.c */
_declspec(dllimport) rt_uint32_t blue; 
//extern rt_uint32_t * green;

int main(void)
{
	int i;

	//rt_kprintf("green = %x, *green", green, *(rt_uint32_t *)green);
	rt_kprintf("blue = %x\n", blue);
	rt_kprintf("_rtgui_object = %x\n", _rtgui_object);
	
	return 0;
}

