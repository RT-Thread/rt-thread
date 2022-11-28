/*
********************************************************************************
*                                USB Hid Driver
*
*                (c) Copyright 2006-2010, All winners Co,Ld.
*                        All Right Reserved
*
* FileName      :  Hid.c
*
* Author        :  Javen
*
* Date          :  2010/06/02
*
* Description   :  Hid Driver中对USB接口设备的处理
*
* Others        :  NULL
*
* History:
*       <time>          <author>     <version >     <desc>
*      2010.06.02       Javen           1.0         build this file
*
********************************************************************************
*/
//#include  "usb_host_config.h"
//#include  "usb_host_base_types.h"
#include  "usb_os_platform.h"
#include  "error.h"

#include  "usb_utils_find_zero_bit.h"
#include  "usb_list.h"
#include  "urb.h"
#include  "list_head_ext.h"
#include  "usb_host_common.h"
#include  "usb_gen_dev_mod.h"
#include  "usb_core_interface.h"
#include  "usb_msg.h"
#include  "HidSpec.h"
#include  "Hid.h"
#include  "Hid_i.h"
#include  "HidTransport.h"
#include  "HidProtocol.h"
#include  "HidFunDrv.h"

#define  HID_DRV_NAME       "HID Class"
#define  HID_DRV_AUTHOR     "Host Driver Author"
#if  0
#define DMSG_HID_TEST   hal_log_info
#else
#define DMSG_HID_TEST(...)
#endif

//---------------------------------------------------------------
//  宏定义区
//---------------------------------------------------------------

//---------------------------------------------------------------
//  全局变量区
//---------------------------------------------------------------
static struct usb_host_func_drv HidDrv;
static u32 HidDev_id_array;             /* 记录了设备的编号 */

static struct usb_drv_dev_match_table Hid_match_table[] = {
    {
        USB_DEVICE_ID_MATCH_INT_CLASS,  //match_flags;

        0,  //idVendor;
        0,  //idProduct;
        0,  //bcdDevice_lo;
        0,  //bcdDevice_hi;

            //Used for device class matches
        0,  //bDeviceClass;
        0,  //bDeviceSubClass;
        0,  //bDeviceProtocol;

            //Used for interface class matches
        USB_CLASS_HID,  //bInterfaceClass;
        0,  //bInterfaceSubClass;
        0,  //bInterfaceProtocol;

            //not matched against
        0,  //driver_info;
    },

    {
        0,  //match_flags;

        0,  //idVendor;
        0,  //idProduct;
        0,  //bcdDevice_lo;
        0,  //bcdDevice_hi;

            //Used for device class matches
        0,  //bDeviceClass;
        0,  //bDeviceSubClass;
        0,  //bDeviceProtocol;

            //Used for interface class matches
        0,  //bInterfaceClass;
        0,  //bInterfaceSubClass;
        0,  //bInterfaceProtocol;

            //not matched against
        0,  //driver_info;
    }/* Terminating entry */
};

//---------------------------------------------------------------
//  函数区定义区
//---------------------------------------------------------------

/*
*******************************************************************************
*                     get_HidDev_id
*
* Description:
*    给新插入的设备分配ID
*
* Parameters:
*    void
*
* Return value:
*    返回分配的ID
*
* note:
*    无
*
*******************************************************************************
*/
static unsigned int get_HidDev_id(void)
{
    unsigned int bit = 0;

    bit = find_next_zero_bit((const volatile u32 *)&HidDev_id_array, (1 * 32), 0);
    if(bit > 32){
        hal_log_err("ERR: find_next_zero_bit failed\n");
        return 31;
    }

    usb_set_bit(bit, (volatile uint32_t *)&HidDev_id_array);

    return bit;
}

/*
*******************************************************************************
*                     free_HidDev_id
*
* Description:
*    释放分配的ID
*
* Parameters:
*    bit : input.  mscDev的ID号
*
* Return value:
*    0  ：成功
*   !0  ：失败
*
* note:
*    无
*
*******************************************************************************
*/
static int free_HidDev_id(unsigned int bit)
{
    if(usb_test_bit(bit, (volatile uint32_t *)&HidDev_id_array) == 0){
        hal_log_err("ERR: free_host_id: invalid bit(%d)\n", bit);
        return -1;
    }

    /* 回收该位 */
    usb_clear_bit(bit, (volatile uint32_t *)&HidDev_id_array);

    return 0;
}

/*
*******************************************************************************
*                     HidDevInit
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*
*
* note:
*    无
*
*******************************************************************************
*/
static int HidDevInit(HidDev_t *HidDev, struct usb_interface *intf)
{
    int ret = 0;

    if(HidDev == NULL || intf == NULL){
        hal_log_err("ERR: HidDevInit: input error\n");
        return USB_ERR_BAD_ARGUMENTS;
    }

    HidDev->pusb_dev    = usb_mod_interface_to_usbdev(intf);
    if(HidDev->pusb_dev == NULL){
        hal_log_err("ERR: HidDevInit: HidDev->pusb_dev == NULL\n");
        return USB_ERR_BAD_ARGUMENTS;
    }

    HidDev->pusb_intf   = intf;
    HidDev->DevNo       = get_HidDev_id();

    /* Store our private data in the interface */
    usb_mod_usb_set_intf_priv_data(intf, (void *)HidDev);

    /* alloc urb */
    HidDev->CurrentUrb = usb_alloc_urb(0);
    if(HidDev->CurrentUrb == NULL){
        hal_log_err("ERR: HidDevInit: usb_alloc_urb failed\n");
        return USB_ERR_ALLOC_URB_FAILED;
    }

    HidDev->CtrlReq = (struct usb_ctrlrequest *)usb_buffer_alloc(HidDev->pusb_dev,
                                                                sizeof(struct usb_ctrlrequest),
                                                                0,
                                                                NULL);
    if(HidDev->CtrlReq == NULL){
        hal_log_err("ERR: usb_buffer_alloc CtrlReq failed\n");
        ret = USB_ERR_MALLOC_FAILED;
        goto error0;
    }

    HidDev->ReportDesc = (unsigned char *)hal_malloc(USB_HID_MAX_DESCRIPTOR_SIZE);
    if(HidDev->ReportDesc == NULL){
        hal_log_err("ERR: hal_malloc failed\n");
        goto error1;
    }

    HidDev->UrbWait = hal_sem_create(0);
    if(HidDev->UrbWait == NULL){
        hal_log_err("ERR: USB_OS_SemCreate UrbWait failed\n");
        ret = USB_ERR_CREATE_SIME_FAILED;
        goto error2;
    }

    return USB_ERR_SUCCESS;

error2:
    hal_free(HidDev->ReportDesc);
    HidDev->ReportDesc = NULL;

error1:
    usb_buffer_free(HidDev->pusb_dev, sizeof(struct usb_ctrlrequest), (void *)(HidDev->CtrlReq), 0);
    HidDev->CtrlReq = NULL;

error0:
    usb_free_urb(HidDev->CurrentUrb);
    HidDev->CurrentUrb = NULL;

    return ret;
}

/*
*******************************************************************************
*                     HidDevFree
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*
*
* note:
*    无
*
*******************************************************************************
*/
static int HidDevFree(HidDev_t *HidDev)
{
    unsigned char err = 0;

    if(HidDev == NULL){
        hal_log_err("ERR: input error\n");
        return USB_ERR_BAD_ARGUMENTS;
    }

    if(HidDev->CurrentUrb){
        usb_free_urb(HidDev->CurrentUrb);
        HidDev->CurrentUrb = NULL;
    }

    if(HidDev->CtrlReq){
        usb_buffer_free(HidDev->pusb_dev, sizeof(struct usb_ctrlrequest), (void *)(HidDev->CtrlReq), 0);
        HidDev->CtrlReq = NULL;
    }

    if(HidDev->ReportDesc){
        hal_free(HidDev->ReportDesc);
    }

    if(HidDev->UrbWait){
        hal_sem_delete(HidDev->UrbWait);
        HidDev->UrbWait = NULL;
    }

    /* Remove our private data from the interface */
    usb_mod_usb_set_intf_priv_data(HidDev->pusb_intf, NULL);

    free_HidDev_id(HidDev->DevNo);

    return 0;
}

/*
*******************************************************************************
*                     HidGetDeviceInfo
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*    无
*
* note:
*    无
*
*******************************************************************************
*/
static void HidGetDeviceInfo(HidDev_t *HidDev, unsigned int index)
{
    struct usb_interface_descriptor *idesc = &(HidDev->pusb_intf->cur_altsetting->desc);

    HidDev->InterfaceNo = idesc->bInterfaceNumber;
    HidDev->SubClass    = idesc->bInterfaceSubClass;
    HidDev->Protocol    = idesc->bInterfaceProtocol;

    return;
}

/*
*******************************************************************************
*                     HidGetTransport
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*
*
* note:
*    无
*
*******************************************************************************
*/
static int HidGetTransport(HidDev_t *HidDev)
{
    HidDev->ResetRecovery = HidResetRecovery;
    HidDev->SoftReset     = HidSoftReset;
    HidDev->Transport     = HidTransport;
    HidDev->StopTransport = HidStopTransport;

    return USB_ERR_SUCCESS;
}

/*
*******************************************************************************
*                     HidCreatePipes
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*
*
* note:
*    无
*
*******************************************************************************
*/
static int HidCreatePipes(HidDev_t *HidDev)
{
    struct usb_host_virt_interface *altsetting = HidDev->pusb_intf->cur_altsetting;
    struct usb_endpoint_descriptor *ep      = NULL;
    struct usb_endpoint_descriptor *ep_int  = NULL;
    int i = 0;

    for (i = 0; i < altsetting->desc.bNumEndpoints; i++) {
        ep = &altsetting->endpoint[i].desc;

        /* Is it an interrupt endpoint? */
        if ((ep->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) == USB_ENDPOINT_XFER_INT) {
            ep_int = ep;
        }
    }

    if(ep_int == NULL){
        hal_log_err("HidCreatePipes: Endpoint sanity check failed! Rejecting dev.\n");
        return USB_ERR_UNKOWN_ERROR;
    }

    /* create ctrl and int pipes */
    HidDev->CtrlOut = usb_sndctrlpipe(HidDev->pusb_dev, 0);
    HidDev->CtrlIn  = usb_rcvctrlpipe(HidDev->pusb_dev, 0);
    HidDev->IntIn   = usb_rcvintpipe(HidDev->pusb_dev,
                                     ep_int->bEndpointAddress & USB_ENDPOINT_NUMBER_MASK);
    HidDev->EpInterval         = ep_int->bInterval;
    HidDev->OnceTransferLength = ep_int->wMaxPacketSize;

    return USB_ERR_SUCCESS;
}

/*
*******************************************************************************
*                     HidSetDeviceState
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*
*
* note:
*    无
*
*******************************************************************************
*/
void HidSetDeviceState(HidDev_t *HidDev, HidDev_State_t state)
{
    unsigned int cup_sr = 0;

    ENTER_CRITICAL(cup_sr);
    HidDev->State = state;
    EXIT_CRITICAL(cup_sr);
}

/*
*******************************************************************************
*                     HidParseReport
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*
*
* note:
*    无
*
*******************************************************************************
*/
int HidGetInputReport(HidDev_t *HidDev,
                        unsigned int Usagepage,
                        unsigned int Usage,
                        unsigned int *BitOffset,
                        unsigned int *BitCount)
{
    usbHidReportEnum_t *InputReport = NULL;
    usbHidReport_t *Report = NULL;
    usbHidField_t *Field = NULL;
    usbHidUsage_t *ReportUsage = NULL;
    unsigned int Offset_ReportId = 0; /* 如果有ReportId, 那么data[0]就不能够算在BitOffset里 */
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int k = 0;

    InputReport = HidDev->HidReportEnum + USB_HID_REPORT_INPUT;
    if(InputReport == NULL){
        hal_log_err("ERR: InputReport is NULL\n");
        return USB_ERR_BAD_ARGUMENTS;
    }

    /* Device uses numbered reports, data[0] is report number */
    if(InputReport->numbered){
        Offset_ReportId = 8;
    }
    hal_log_info("InputReport ReportNum = %d\n", InputReport->ReportNum);

    /* report */
    for(i = 0; i < InputReport->ReportNum; i++){
        Report = InputReport->Report[i];
        if(Report == NULL){
            hal_log_err("ERR: Report is NULL\n");
            continue;
        }

        /* field */
        for(j = 0; j < Report->Maxfield; j++){
            Field = Report->Field[j];
            if(Field == NULL){
                hal_log_err("ERR: Field is NULL\n");
                continue;
            }

            /* Usage */
            for(k = 0; k < Field->maxusage; k++){
                ReportUsage = &Field->usage[k];
                if(ReportUsage == NULL){
                    hal_log_err("ERR: Usage is NULL\n");
                    continue;
                }

                if(Usage == USB_HID_GENERIC_DESKTOP_PAGE_UNDEFINED){
                    if(((ReportUsage->hid >> 16) & 0xffff) == Usagepage){
                        DMSG_HID_TEST("Find Bitmap: Usage(%x), Id = %d, report_offset = %d, report_size = %d\n",
                                   Usagepage, ((Offset_ReportId == 0) ? 0 : 1),
                                   Field->report_offset, (Field->report_size * k));
                        *BitOffset = Offset_ReportId + Field->report_offset + (Field->report_size * k);
                        *BitCount  = Field->report_size * Field->report_count;

                        DMSG_HID_TEST("Usage(%x), BitOffset = %d, BitCount = %d\n",
                                  Usagepage, *BitOffset, *BitCount);

                        return USB_ERR_SUCCESS;
                    }
                }else{
                    if(ReportUsage->hid == ((Usagepage << 16) | Usage)){
                        DMSG_HID_TEST("Find Bitmap: usage(%x, %x), Id = %d, report_offset = %d, report_size = %d\n",
                                   Usagepage, Usage, ((Offset_ReportId == 0) ? 0 : 1),
                                   Field->report_offset, (Field->report_size * k));
                        *BitOffset = Offset_ReportId + Field->report_offset + (Field->report_size * k);
                        *BitCount  = Field->report_size;

                        DMSG_HID_TEST("usage(%x, %x), BitOffset = %d, BitCount = %d\n",
                                  Usagepage, Usage, *BitOffset, *BitCount);

                        return USB_ERR_SUCCESS;
                    }
                }
            }
        }
    }

    return USB_ERR_UNKOWN_ERROR;
}


/*
*******************************************************************************
*                     HidDevScan
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*
*
* note:
*    无
*
*******************************************************************************
*/
static int HidDevScan(HidDev_t *HidDev)
{
    struct usb_host_virt_interface *cur_alt = NULL;
    usbHidDescriptor_t *HidDesc = NULL;
    int ret = 0;
    unsigned int i = 0;

    if(HidDev == NULL){
        hal_log_err("ERR: HidDevScan: input error\n");
        return USB_ERR_BAD_ARGUMENTS;
    }

    /* initalize parameter */
    cur_alt = HidDev->pusb_intf->cur_altsetting;

    /* get device type */
    HidDev->DevType = cur_alt->desc.bInterfaceProtocol;

    /* Get Hid descriptor */
    if (usb_get_extra_descriptor(cur_alt, USB_HID_DT_HID, &HidDesc)
        &&(!cur_alt->desc.bNumEndpoints
           || usb_get_extra_descriptor(&(cur_alt->endpoint[0]), USB_HID_DT_HID, &HidDesc))){
        hal_log_err("ERR: class descriptor not present\n");
        return USB_ERR_UNKOWN_ERROR;
    }

    /* 获得report返回的数据长度 */
    for (i = 0; i < HidDesc->bNumDescriptors; i++){
        if (HidDesc->desc[i].bDescriptorType == USB_HID_DT_REPORT){
            HidDev->ReportSize = le16_to_cpu(HidDesc->desc[i].wDescriptorLength);
            break;
        }
    }

    if (HidDev->ReportSize == 0 || HidDev->ReportSize > USB_HID_MAX_DESCRIPTOR_SIZE) {
        hal_log_err("ERR: weird size of report descriptor (%u)\n", HidDev->ReportSize);
        return USB_ERR_UNKOWN_ERROR;
    }

    /* set idle request, 限制了report的频率 */
    HidSetIlde(HidDev, HidDev->InterfaceNo, 0, 0);

    /* Get Hid Report descriptor */
    ret = HidGetClassDescriptor(HidDev,
                                HidDev->InterfaceNo,
                                USB_HID_DT_REPORT,
                                (void *)HidDev->ReportDesc,
                                HidDev->ReportSize);
    if(ret != USB_ERR_SUCCESS){
        hal_log_err("ERR: HidGetClassDescriptor failed\n");
        return USB_ERR_COMMAND_EXECUTE_FAILED;
    }

    /* parse Hid Report descriptor */
    HidParseReport(HidDev->ReportDesc, HidDev->ReportSize, HidDev);

    /* Client probe */
    switch(HidDev->DevType){
        case USB_HID_PROTOCOL_MOUSE:
            HidDev->ClientProbe  = usbMouseProbe;
            HidDev->ClientRemove = usbMouseRemove;
        break;
/*
        case USB_HID_PROTOCOL_KEYBOARD:
            HidDev->ClientProbe  = usbKeyBoardProbe;
            HidDev->ClientRemove = usbKeyBoardRemove;
        break;
*/
        default:
            hal_log_err("ERR: HidDevScan: unkown hid Device Type(%x)\n", HidDev->DevType);
            HidDev->ClientProbe  = NULL;
            HidDev->ClientRemove = NULL;

            return USB_ERR_UNKOWN_DEVICE;
    }

    if(HidDev->ClientProbe){
        if(HidDev->ClientProbe(HidDev) != USB_ERR_SUCCESS){
            hal_log_err("ERR: ClientProbe faield\n");
            return USB_ERR_DEVICE_PROBE_FAILED;
        }
    }

    return USB_ERR_SUCCESS;
}

/*
*******************************************************************************
*                     HidDevAdd
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*
*
* note:
*    无
*
*******************************************************************************
*/
static int HidDevAdd(HidDev_t * HidDev)
{
    return HidDevScan(HidDev);
}

/*
*******************************************************************************
*                     HidDevDel
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*
*
* note:
*    无
*
*******************************************************************************
*/
static int HidDevDel(HidDev_t * HidDev)
{
    if(HidDev->ClientRemove){
        if(HidDev->ClientRemove(HidDev) != USB_ERR_SUCCESS){
            hal_log_err("ERR: ClientProbe faield\n");
            return USB_ERR_DEVICE_PROBE_FAILED;
        }
    }

    HidFreeReport(HidDev);

    return USB_ERR_SUCCESS;
}


/*
*******************************************************************************
*                     HidSentRequest
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*
*
* note:
*    无
*
*******************************************************************************
*/
int HidSentRequest(HidRequest_t *HidReq)
{
    HidDev_t *HidDev = NULL;
    unsigned int cpu_sr = 0;
    int ret = 0;

    if(HidReq == NULL){
        hal_log_err("ERR: HidSentRequest: input error\n");
        return USB_ERR_BAD_ARGUMENTS;
    }

    HidDev = HidReq->HidDev;
    if(HidDev == NULL){
        hal_log_err("ERR: HidSentRequest: HidDev == NULL\n");
        return USB_ERR_BAD_ARGUMENTS;
    }

    /* Transport */
    ret = HidDev->Transport(HidDev, HidReq);

    ENTER_CRITICAL(cpu_sr);
    HidReq->Result = ret;
    EXIT_CRITICAL(cpu_sr);

    /* HidReq Done */
    HidReq->Done(HidReq);

    return USB_ERR_SUCCESS;
}

/*
*******************************************************************************
*                     HidDevProbe
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*
*
* note:
*    无
*
*******************************************************************************
*/
static int32_t HidDevProbe(struct usb_interface *intf, const struct usb_drv_dev_match_table * table_item)
{
    const s32 match_table_index = table_item - Hid_match_table;
    HidDev_t *HidDev = NULL;
    int ret = 0;
//  unsigned char err  = 0;

    hal_log_info("HidDevProbe begin\n");

    if(intf == NULL || table_item == NULL){
        hal_log_err("ERR: HidDevProbe: input error\n");
        return -1;
    }

    //----------------------------------------------------------------
    //   创建HidDev设备
    //----------------------------------------------------------------
    /* 初始化一个mscDev */
    HidDev = hal_malloc(sizeof(HidDev_t));
    if(HidDev == NULL){
        hal_log_err("ERR: HidDevProbe malloc failed\n");
        goto error0;
    }

    memset(HidDev, 0, sizeof(HidDev_t));

    ret = HidDevInit(HidDev, intf);
    if(ret != USB_ERR_SUCCESS){
        hal_log_err("ERR: HidDevProbe failed\n");
        ret = -1;
        goto error1;
    }

    /* 获得设备信息 */
    HidGetDeviceInfo(HidDev, match_table_index);

    /* 获得Transport */
    ret = HidGetTransport(HidDev);
    if(ret != USB_ERR_SUCCESS){
        hal_log_err("ERR: HidGetTransport failed\n");
        ret = -1;
        goto error2;
    }

    /* 创建传输管道 */
    ret = HidCreatePipes(HidDev);
    if(ret != USB_ERR_SUCCESS){
        hal_log_err("ERR: HidGetTransport failed\n");
        ret = -1;
        goto error3;
    }

    HidSetDeviceState(HidDev, HID_DEV_ONLINE);

    //----------------------------------------------------------------
    //   识别HidDev设备
    //----------------------------------------------------------------
    ret = HidDevAdd(HidDev);
    if(ret != USB_ERR_SUCCESS){
        hal_log_err("ERR: HidDevScan failed\n");
        ret = -1;
        goto error4;
    }

    return 0;

error4:
    HidSetDeviceState(HidDev, HID_DEV_OFFLINE);

error3:
error2:
    HidDevFree(HidDev);

error1:
    hal_free(HidDev);

error0:

    return -1;
}

/*
*******************************************************************************
*                     HidInit
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*    EPDK_OK / EPDK_FAIL
*
* note:
*    无
*
*******************************************************************************
*/
static int32_t HidDevSuspend(struct usb_interface *intf)
{
    hal_log_info("HidDevSuspend not support\n");

    return 0;
}
/*
*******************************************************************************
*                     HidInit
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*    EPDK_OK / EPDK_FAIL
*
* note:
*    无
*
*******************************************************************************
*/
static void HidDevRemove(struct usb_interface *intf)
{
    HidDev_t *HidDev = NULL;

    if(intf == NULL){
        hal_log_err("ERR: HidDevRemoves: input error\n");
        return ;
    }

    HidDev = (HidDev_t *)usb_mod_usb_get_intf_priv_data(intf);
    if(HidDev == NULL){
        hal_log_err("ERR: HidDev = NULL\n");
        return ;
    }

    HidSetDeviceState(HidDev, HID_DEV_OFFLINE);

    HidDevDel(HidDev);

    HidDevFree(HidDev);

    hal_free(HidDev);

    hal_log_info("HidDevRemove complete\n");

    return ;
}

/*
*******************************************************************************
*                     HidInit
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*    EPDK_OK / EPDK_FAIL
*
* note:
*    无
*
*******************************************************************************
*/
static int HidDriverInit(struct usb_host_func_drv *drv)
{
    if(drv == NULL){
        hal_log_err("ERR: mscDrv_init: input error\n");
        return -1;
    }

    USB_INIT_LIST_HEAD(&(drv->virt_dev_list));
    drv->func_drv_name      = HID_DRV_NAME;
    drv->func_drv_auther    = HID_DRV_AUTHOR;
    drv->probe              = HidDevProbe;
    drv->disconnect         = HidDevRemove;
    drv->suspend            = HidDevSuspend;
    drv->resume             = NULL;
    drv->match_table        = Hid_match_table;

    return 0;
}

/*
*******************************************************************************
*                     HidInit
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*    EPDK_OK / EPDK_FAIL
*
* note:
*    无
*
*******************************************************************************
*/
int HidInit(void)
{
    int ret = 0;

    memset(&HidDrv, 0, sizeof(struct usb_host_func_drv));

    if(HidDriverInit(&HidDrv) != 0){
        hal_log_err("ERR: HidDriverInit failed\n");
        return -1;
    }

    ret = usb_host_func_drv_reg(&HidDrv);
    if(ret != 0){
        hal_log_err("ERR: HidInit: Reg driver %s failed\n", HidDrv.func_drv_name);
        return -1;
    }

    return 0;
}

/*
*******************************************************************************
*                     HidExit
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*    EPDK_OK / EPDK_FAIL
*
* note:
*    无
*
*******************************************************************************
*/
int HidExit(void)
{
    int ret = 0;

    ret = usb_host_func_drv_unreg(&HidDrv);
    if(ret != 0){
        hal_log_err("ERR: HidExit: UnReg driver %s failed\n", HidDrv.func_drv_name);
        return -1;
    }

    memset(&HidDrv, 0, sizeof(struct usb_host_func_drv));

    return 0;
}










