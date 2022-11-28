/*
*******************************************************************************
*                                              usb host module
*
*                             Copyright(C), 2006-2008, SoftWinners Co., Ltd.
*                                                  All Rights Reserved
*
* File Name :
*
* Author : GLHuang(HoLiGun)
*
* Version : 1.0
*
* Date : 2008.05.xx
*
* Description :
*
* History :
********************************************************************************************************************
*/
//#include "usb_host_config.h"

//#include <usb/usb_os_platform.h>
#include <usb_host_common.h>

//#include "usb_host_base_types.h"
#include <usb_list.h>

#include "usb_core_base.h"
#include "usb_virt_bus.h"
#include "usb_gen_hub.h"
#include "usb_gen_hcd.h"
#include "usb_driver_init.h"

s32 usb_core_init(void)
{
    usb_host_enable();
    usb_virt_bus_init();
    usb_drivers_init();
    usb_gen_hcd_init();
    usb_gen_hub_init();
    return EPDK_OK;
}

s32 usb_core_exit(void)
{
    //  usb_gen_hub_exit();
    usb_gen_hcd_exit();
    usb_drivers_exit();
    usb_virt_bus_exit();
    usb_host_disable();
    return EPDK_OK;
}


