#include "stm32f10x.h"
#include "usb_lib.h"
#include "udisk\disk_istr.h"
#include "hw_config.h"
#include "usb_pwr.h"
//#ifdef UDISK
void udisk_USB_Init(void);
extern void (*USB_Istr)(void);
void nop(void)
{
return ;
}
void udisk_USB_Istr(void);
void udisk_USB_cable(void)
{
    /* usb msc up*/
	  
	  USB_Istr=udisk_USB_Istr;
    Set_System();
		Device_Table.Total_Configuration=3;
    Set_USBClock();
    USB_Interrupts_Config();
	  MAL_Init(0);
    udisk_USB_Init();
}
//#endif