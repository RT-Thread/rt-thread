/*
********************************************************************************
*                                USB UVC Driver
*
*                (c) Copyright 2006-2010, All winners Co,Ld.
*                        All Right Reserved
*
* FileName      :  UVC.c
*
* Author        :  Kingvan
*
* Date          :  2013/03/26
*
* Description   :  USB VIDEO CONTROL Driver中对USB接口设备的处理
*
* Others        :  NULL
*
* History:
*       <time>          <author>     <version >     <desc>
*      2013.03.26       Kingvan         1.0         build this file
*
********************************************************************************
*/
//#include  "usb_host_config.h"
//#include  "usb_host_base_types.h"
#include  "usb_os_platform.h"
#include  "error.h"

#include  "usb_utils_find_zero_bit.h"
#include  "usb_list.h"
#include  "list_head_ext.h"

#include  "usb_host_common.h"
#include  "usb_gen_dev_mod.h"
#include  "urb.h"
#include  "usb.h"
#include  "usb_core_interface.h"
#include  "usb_msg.h"

//#include  "usbh_disk_info.h"
//#include  "usbh_buff_manager.h"
//#include  "usbh_disk_remove_time.h"

#include "video.h"
#include "uvcvideo.h"
#include "uvc_driver.h"


#define  UVC_DRV_NAME       "UVC Class"
#define  UVC_DRV_AUTHOR     "Kingvan.Tong"

//---------------------------------------------------------------
//  宏定义区
//---------------------------------------------------------------

//---------------------------------------------------------------
//  全局变量区
//---------------------------------------------------------------
static struct usb_host_func_drv UVCDrv;
static __u32 UVCDev_id_array;               /* 记录了设备的编号 */
static void* UVCDev_attr;


static unsigned char g_enter_flag = 0;

static struct usb_drv_dev_match_table UVC_match_table[] = {
        /* Genius eFace 2025 */
        { USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_INT_INFO,
          0x0458, 0x706e,0,0,
          0,0,0,
          USB_CLASS_VIDEO,1,0,
          UVC_QUIRK_PROBE_MINMAX },
        /* Microsoft Lifecam NX-6000 */
        { USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_INT_INFO,
          0x045e, 0x00f8,0,0,
          0,0,0,
          USB_CLASS_VIDEO,1,0,
          UVC_QUIRK_PROBE_MINMAX },
        /* Microsoft Lifecam VX-7000 */
        { USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_INT_INFO,
          0x045e, 0x0723,0,0,
          0,0,0,
          USB_CLASS_VIDEO, 1, 0,
          UVC_QUIRK_PROBE_MINMAX },
        /* Logitech Quickcam Fusion */
        { USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_INT_INFO,
          0x046d, 0x08c1,0,0,
          0,0,0,
          USB_CLASS_VENDOR_SPEC, 1, 0,
          0},
        /* Logitech Quickcam Orbit MP */
        { USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_INT_INFO,
          0x046d, 0x08c2,0,0,
          0,0,0,
          USB_CLASS_VENDOR_SPEC, 1, 0,
          0},
        /* Logitech Quickcam Pro for Notebook */
        { USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_INT_INFO,
          0x046d,0x08c3,0,0,
          0,0,0,
          USB_CLASS_VENDOR_SPEC, 1, 0,
          0},
        /* Logitech Quickcam Pro 5000 */
        { USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_INT_INFO,
          0x046d,0x08c5,0,0,
          0,0,0,
          USB_CLASS_VENDOR_SPEC, 1, 0,
         0},
        /* Logitech Quickcam OEM Dell Notebook */
        { USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_INT_INFO,
          0x046d,0x08c6,0,0,
          0,0,0,
          USB_CLASS_VENDOR_SPEC,1,0,
          0},
        /* Logitech Quickcam OEM Cisco VT Camera II */
        { USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_INT_INFO,
          0x046d,0x08c7,0,0,
          0,0,0,
          USB_CLASS_VENDOR_SPEC, 1, 0,
          0},
        /* Chicony CNF7129 (Asus EEE 100HE) */
        { USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_INT_INFO,
          0x04f2, 0xb071,0,0,
          0,0,0,
          USB_CLASS_VIDEO, 1, 0,
          UVC_QUIRK_RESTRICT_FRAME_RATE },
        /* Alcor Micro AU3820 (Future Boy PC USB Webcam) */
        { USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_INT_INFO,
          0x058f, 0x3820,0,0,
          0,0,0,
          USB_CLASS_VIDEO, 1, 0,
          UVC_QUIRK_PROBE_MINMAX },
        /* Apple Built-In iSight */
        { USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_INT_INFO,
          0x05ac,0x8501,0,0,
          0,0,0,
          USB_CLASS_VIDEO,1,0,
          UVC_QUIRK_PROBE_MINMAX | UVC_QUIRK_BUILTIN_ISIGHT },
        /* Genesys Logic USB 2.0 PC Camera */
        { USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_INT_INFO,
          0x05e3,0x0505,0,0,
          0,0,0,
          USB_CLASS_VIDEO, 1, 0,
          UVC_QUIRK_STREAM_NO_FID },
        /* Hercules Classic Silver */
        { USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_INT_INFO,
          0x06f8, 0x300c,0,0,
          0,0,0,
          USB_CLASS_VIDEO, 1, 0,
          UVC_QUIRK_FIX_BANDWIDTH },
        /* ViMicro Vega */
        { USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_INT_INFO,
          0x0ac8, 0x332d,0,0,
          0,0,0,
          USB_CLASS_VIDEO, 1, 0,
          UVC_QUIRK_FIX_BANDWIDTH },
        /* ViMicro - Minoru3D */
        { USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_INT_INFO,
          0x0ac8,0x3410,0,0,
          0,0,0,
          USB_CLASS_VIDEO,1,0,
          UVC_QUIRK_FIX_BANDWIDTH },
        /* ViMicro Venus - Minoru3D */
        { USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_INT_INFO,
          0x0ac8, 0x3420,0,0,
          0,0,0,
          USB_CLASS_VIDEO, 1, 0,
          UVC_QUIRK_FIX_BANDWIDTH },
        /* MT6227 */
        { USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_INT_INFO,
          0x0e8d,0x0004,0,0,
          0,0,0,
          USB_CLASS_VIDEO,1,0,
          UVC_QUIRK_PROBE_MINMAX | UVC_QUIRK_PROBE_DEF },
        /* IMC Networks (Medion Akoya) */
        { USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_INT_INFO,
          0x13d3, 0x5103,0,0,
          0,0,0,
          USB_CLASS_VIDEO, 1, 0,
          UVC_QUIRK_STREAM_NO_FID },
        /* JMicron USB2.0 XGA WebCam */
        { USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_INT_INFO,
          0x152d,0x0310,0,0,
          0,0,0,
          USB_CLASS_VIDEO, 1, 0,
          UVC_QUIRK_PROBE_MINMAX },
        /* Syntek (HP Spartan) */
        { USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_INT_INFO,
          0x174f, 0x5212,0,0,
          0,0,0,
          USB_CLASS_VIDEO, 1, 0,
          UVC_QUIRK_STREAM_NO_FID },
        /* Syntek (Samsung Q310) */
        { USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_INT_INFO,
          0x174f, 0x5931,0,0,
          0,0,0,
          USB_CLASS_VIDEO, 1, 0,
          UVC_QUIRK_STREAM_NO_FID },
        /* Syntek (Packard Bell EasyNote MX52 */
        { USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_INT_INFO,
          0x174f, 0x8a12,0,0,
          0,0,0,
          USB_CLASS_VIDEO, 1, 0,
          UVC_QUIRK_STREAM_NO_FID },
        /* Syntek (Asus F9SG) */
        { USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_INT_INFO,
          0x174f, 0x8a31,0,0,
          0,0,0,
          USB_CLASS_VIDEO, 1, 0,
          UVC_QUIRK_STREAM_NO_FID },
        /* Syntek (Asus U3S) */
        { USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_INT_INFO,
          0x174f, 0x8a33,0,0,
          0,0,0,
          USB_CLASS_VIDEO, 1, 0,
          UVC_QUIRK_STREAM_NO_FID },
        /* Syntek (JAOtech Smart Terminal) */
        { USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_INT_INFO,
          0x174f, 0x8a34,0,0,
          0,0,0,
          USB_CLASS_VIDEO, 1, 0,
          UVC_QUIRK_STREAM_NO_FID },
        /* Miricle 307K */
        { USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_INT_INFO,
          0x17dc,0x0202,0,0,
          0,0,0,
          USB_CLASS_VIDEO,1,0,
          UVC_QUIRK_STREAM_NO_FID },
        /* Lenovo Thinkpad SL400/SL500 */
        { USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_INT_INFO,
          0x17ef,0x480b,0,0,
          0,0,0,
          USB_CLASS_VIDEO,1,0,
          UVC_QUIRK_STREAM_NO_FID },
        /* Aveo Technology USB 2.0 Camera */
        { USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_INT_INFO,
          0x1871,0x0306,0,0,
          0,0,0,
          USB_CLASS_VIDEO, 1, 0,
          UVC_QUIRK_PROBE_MINMAX | UVC_QUIRK_PROBE_EXTRAFIELDS },
        /* Ecamm Pico iMage */
        { USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_INT_INFO,
          0x18cd, 0xcafe,0,0,
          0,0,0,
          USB_CLASS_VIDEO, 1, 0,
          UVC_QUIRK_PROBE_EXTRAFIELDS },
        /* Manta MM-353 Plako */
        { USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_INT_INFO,
          0x18ec,0x3188,0,0,
          0,0,0,
          USB_CLASS_VIDEO,1, 0,
          UVC_QUIRK_PROBE_MINMAX },
        /* FSC WebCam V30S */
        { USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_INT_INFO,
          0x18ec, 0x3288,0,0,
          0,0,0,
          USB_CLASS_VIDEO, 1, 0,
          UVC_QUIRK_PROBE_MINMAX },
        /* Arkmicro unbranded */
        { USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_INT_INFO,
          0x18ec, 0x3290,0,0,
          0,0,0,
          USB_CLASS_VIDEO, 1, 0,
          UVC_QUIRK_PROBE_DEF },
        /* Bodelin ProScopeHR */
        { USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_DEV_HI | USB_DEVICE_ID_MATCH_INT_INFO,
          0x19ab,0x1000,0,0x0126,
          0,0,0,
          USB_CLASS_VIDEO,1,0,
          UVC_QUIRK_STATUS_INTERVAL },
        /* MSI StarCam 370i */
        { USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_INT_INFO,
          0x1b3b, 0x2951,0,0,
          0,0,0,
          USB_CLASS_VIDEO, 1, 0,
          UVC_QUIRK_PROBE_MINMAX },
        /* SiGma Micro USB Web Camera */
        { USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_INT_INFO,
          0x1c4f, 0x3000,0,0,
          0,0,0,
          USB_CLASS_VIDEO, 1, 0,
           UVC_QUIRK_PROBE_MINMAX | UVC_QUIRK_IGNORE_SELECTOR_UNIT },
        /* Generic USB Video Class */
        { USB_DEVICE_ID_MATCH_INT_INFO,
          0,0,0,0,
          0,0,0,
          USB_CLASS_VIDEO, 1, 0,
          0},
        { 0,
          0,0,0,0,
          0,0,0,
          0,0,0,
          0}
};

//---------------------------------------------------------------
//  函数区定义区
//---------------------------------------------------------------

static unsigned int get_UVCDev_id(void)
{
    unsigned int bit = 0;

    bit = find_next_zero_bit((const volatile u32 *)&UVCDev_id_array, (1 * 32), 0);
    if(bit > 32){
        hal_log_err("ERR: find_next_zero_bit failed\n");
        return 31;
    }

    usb_set_bit(bit, (volatile uint32_t *)&UVCDev_id_array);

    return bit;
}

static int free_UVCDev_id(unsigned int bit)
{
    if(usb_test_bit(bit, (volatile uint32_t *)&UVCDev_id_array) == 0){
        hal_log_err("ERR: free_host_id: invalid bit(%d)\n", bit);
        return -1;
    }

    /* 回收该位 */
    usb_clear_bit(bit, (volatile uint32_t *)&UVCDev_id_array);

    return 0;
}

static int UVCDevInit(UVCDev_t *UVCDev, struct usb_interface *intf)
{
    int ret = 0;

    if(UVCDev == NULL || intf == NULL){
        hal_log_err("ERR: UVCDevInit: input error\n");
        return USB_ERR_BAD_ARGUMENTS;
    }

    UVCDev->pusb_dev    = usb_mod_interface_to_usbdev(intf);
    if(UVCDev->pusb_dev == NULL){
        hal_log_err("ERR: UVCDevInit: UVCDev->pusb_dev == NULL\n");
        return USB_ERR_BAD_ARGUMENTS;
    }

    UVCDev->pusb_intf   = intf;
    UVCDev->DevNo       = get_UVCDev_id();

    /* Store our private data in the interface */
    usb_mod_usb_set_intf_priv_data(intf, (void *)UVCDev);


    return USB_ERR_SUCCESS;

}

static int UVCDevFree(UVCDev_t *UVCDev)
{
    unsigned char err = 0;

    if(UVCDev == NULL){
        hal_log_err("ERR: UVC input error\n");
        return USB_ERR_BAD_ARGUMENTS;
    }

    /* Remove our private data from the interface */
    usb_mod_usb_set_intf_priv_data(UVCDev->pusb_intf, NULL);

    free_UVCDev_id(UVCDev->DevNo);

    return 0;
}

static void UVCGetDeviceInfo(UVCDev_t *UVCDev)
{
    struct usb_interface_descriptor *idesc = &(UVCDev->pusb_intf->cur_altsetting->desc);

    UVCDev->InterfaceNo = idesc->bInterfaceNumber;
    UVCDev->SubClass    = idesc->bInterfaceSubClass;
    UVCDev->Protocol    = idesc->bInterfaceProtocol;

    return;
}

void UVCSetDeviceState(UVCDev_t *UVCDev, UVCDev_State_t state)
{
    unsigned int cup_sr = 0;

    ENTER_CRITICAL(cup_sr);
    UVCDev->State = state;
    EXIT_CRITICAL(cup_sr);
}

static int UVCDevScan(UVCDev_t *UVCDev, const struct usb_drv_dev_match_table * table_item)
{
    struct usb_host_virt_interface *cur_alt = NULL;
    int ret = 0;
    unsigned int i = 0;

    if(UVCDev == NULL){
        hal_log_err("ERR: UVCDevScan: input error\n");
        return USB_ERR_BAD_ARGUMENTS;
    }

    /* initalize parameter */
    cur_alt = UVCDev->pusb_intf->cur_altsetting;

    /* get device type */
    UVCDev->DevType = cur_alt->desc.bInterfaceProtocol;

    if (uvc_probe(UVCDev, table_item)) {
        hal_log_err("ERR: uvc_probe failed\n");
        return USB_ERR_DEVICE_PROBE_FAILED;
    }

    if( usbWebcam_probe(UVCDev) != USB_ERR_SUCCESS){
        hal_log_err("ERR: usbWebcamProbe failed\n");
        return USB_ERR_DEVICE_PROBE_FAILED;
    }

    return USB_ERR_SUCCESS;
}

static int UVCDevAdd(UVCDev_t * UVCDev, const struct usb_drv_dev_match_table * table_item)
{
    return UVCDevScan(UVCDev, table_item);
}

static int UVCDevDel(UVCDev_t * UVCDev)
{
    if( usbWebcam_remove(UVCDev) != USB_ERR_SUCCESS){
        hal_log_err("ERR: usbWebcamRemove failed\n");
        return USB_ERR_DEVICE_PROBE_FAILED;
    }
    return USB_ERR_SUCCESS;
}


static int32_t UVCDevProbe(struct usb_interface *intf, const struct usb_drv_dev_match_table * table_item)
{
    UVCDev_t *UVCDev = NULL;
    int ret = 0;
//  unsigned char err  = 0;

    hal_log_info("UVCDevProbe begin\n");

    if( g_enter_flag == 1 )
    {
        hal_log_err("exception: UVCDevProbe\n");
        return -1;
    }

    if(intf == NULL || table_item == NULL){
        hal_log_err("ERR: UVCDevProbe: input error\n");
        return -1;
    }

    //----------------------------------------------------------------
    //   创建UVCDev设备
    //----------------------------------------------------------------
    /* 初始化一个mscDev */
    UVCDev = hal_malloc(sizeof(UVCDev_t));
    if(UVCDev == NULL){
        hal_log_err("ERR: UVCDevProbe malloc failed\n");
        goto error0;
    }

    memset(UVCDev, 0, sizeof(UVCDev_t));

    ret = UVCDevInit(UVCDev, intf);
    if(ret != USB_ERR_SUCCESS){
        hal_log_err("ERR: UVCDevProbe failed\n");
        ret = -1;
        goto error1;
    }

    /* 获得设备信息 */
    UVCGetDeviceInfo(UVCDev);

    UVCSetDeviceState(UVCDev, UVC_DEV_ONLINE);

    //----------------------------------------------------------------
    //   识别UVCDev设备
    //----------------------------------------------------------------
    ret = UVCDevAdd(UVCDev, table_item);
    if(ret != USB_ERR_SUCCESS){
        hal_log_err("ERR: UVCDevScan failed\n");
        ret = -1;
        goto error4;
    }

    g_enter_flag = 1;

    return 0;

error4:
    UVCSetDeviceState(UVCDev, UVC_DEV_OFFLINE);

error3:
error2:
    UVCDevFree(UVCDev);

error1:
    hal_free(UVCDev);

error0:

    return -1;
}

static int32_t UVCDevSuspend(struct usb_interface *intf)
{
    hal_log_info("UVCDevSuspend not support\n");

    return 0;
}

static void UVCDevRemove(struct usb_interface *intf)
{
    UVCDev_t *UVCDev = NULL;

    if( g_enter_flag == 0 )
    {
        hal_log_err("exception: UVCDevRemove\n");
        return;
    }

    if(intf == NULL){
        hal_log_err("ERR: UVCDevRemoves: input error\n");
        return ;
    }

    UVCDev = (UVCDev_t *)usb_mod_usb_get_intf_priv_data(intf);
    if(UVCDev == NULL){
        hal_log_err("ERR: UVCDev = NULL\n");
        return ;
    }

    UVCSetDeviceState(UVCDev, UVC_DEV_OFFLINE);

    UVCDevDel(UVCDev);

    uvc_disconnect(UVCDev);

    UVCDevFree(UVCDev);

    hal_free(UVCDev);

    hal_log_info("UVCDevRemove complete\n");

    g_enter_flag = 0;

    return ;
}

static int UVCDriverInit(struct usb_host_func_drv *drv)
{
    if(drv == NULL){
        hal_log_err("ERR: mscDrv_init: input error\n");
        return -1;
    }

    USB_INIT_LIST_HEAD(&(drv->virt_dev_list));
    drv->func_drv_name      = UVC_DRV_NAME;
    drv->func_drv_auther    = UVC_DRV_AUTHOR;
    drv->probe              = UVCDevProbe;
    drv->disconnect         = UVCDevRemove;
    drv->suspend            = UVCDevSuspend;
    drv->resume             = NULL;
    drv->match_table        = UVC_match_table;

    return 0;
}
int UVCInit(void)
{
    int ret = 0;

    memset(&UVCDrv, 0, sizeof(struct usb_host_func_drv));

    UVCDev_attr = usbWebcam_init();
    if( UVCDev_attr == NULL ){
        hal_log_err("ERR: usbWebcam_init failed\n");
        return -1;
    }

    if(UVCDriverInit(&UVCDrv) != 0){
        hal_log_err("ERR: UVCDriverInit failed\n");
        return -1;
    }

    ret = usb_host_func_drv_reg(&UVCDrv);
    if(ret != 0){
        hal_log_err("ERR: UVCInit: Reg driver %s failed\n", UVCDrv.func_drv_name);
        return -1;
    }

    g_enter_flag = 0;

    return 0;
}

int UVCExit(void)
{
    int ret = 0;

    ret = usb_host_func_drv_unreg(&UVCDrv);
    if(ret != 0){
        hal_log_err("ERR: UVCExit: UnReg driver %s failed\n", UVCDrv.func_drv_name);
        return -1;
    }

    ret = usbWebcam_exit(UVCDev_attr);
    if(ret != 0){
        hal_log_err("ERR: usbWebcam_exit() failed\n");
        return -1;
    }

    memset(&UVCDrv, 0, sizeof(struct usb_host_func_drv));

    return 0;
}










