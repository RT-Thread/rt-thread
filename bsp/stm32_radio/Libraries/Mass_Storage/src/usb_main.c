#include "stm32f10x.h"
#include "usb_lib.h"
#include "usb_istr.h"
#include "hw_config.h"
#include "usb_pwr.h"

#include "rtthread.h"

extern uint32_t Mass_Memory_Size[2];
extern uint32_t Mass_Block_Size[2];
extern uint32_t Mass_Block_Count[2];
extern rt_device_t dev_sdio;

#include <finsh.h>
#include "sdcard.h"
void USB_cable(void)
{
    rt_device_t dev = RT_NULL;
    SD_CardInfo * sdio_info = RT_NULL;
    dev = rt_device_find("sd0");
    if(dev != RT_NULL)
    {
        dev_sdio = dev;
        sdio_info = (SD_CardInfo *)dev->private;
        Mass_Memory_Size[0] = sdio_info->CardCapacity;
        Mass_Block_Size[0]  = sdio_info->CardBlockSize;
        Mass_Block_Count[0] = Mass_Memory_Size[0] / Mass_Block_Size[0];

        Set_System();
        Set_USBClock();
        USB_Interrupts_Config();
        USB_Init();
    }
    else
    {
        rt_kprintf("\r\nNo find the device sd0 !!!!");
    }
}
FINSH_FUNCTION_EXPORT(USB_cable, cable_the_usb);
