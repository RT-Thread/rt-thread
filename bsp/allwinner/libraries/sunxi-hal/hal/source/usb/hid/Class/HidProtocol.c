/*
********************************************************************************
*                                USB Hid Driver
*
*                (c) Copyright 2006-2010, All winners Co,Ld.
*                        All Right Reserved
*
* FileName      :  HidProtocol.c
*
* Author        :  Javen
*
* Date          :  2010/06/02
*
* Description   :  Hid 协议
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
#include "usb_os_platform.h"
#include "error.h"

#include "usb_host_common.h"
#include "usb_msg.h"
#include "urb.h"

#include "HidSpec.h"
#include "Hid_i.h"
#include "HidProtocol.h"
#include "HidTransport.h"
#include "sunxi_hal_common.h"
//#define  USBH_HID_PRINT_REPORT

#ifdef USBH_HID_PRINT_REPORT

static void print_field(usbHidField_t *Field)
{
    unsigned int i = 0;

    hal_log_info("\n------------------field---------------\n");
    hal_log_info("Index            = %d\n", Field->Index);
    hal_log_info("HidReport        = %x\n", Field->HidReport);
    hal_log_info("physical         = %x\n", Field->physical);
    hal_log_info("logical          = %x\n", Field->logical);
    hal_log_info("application      = %x\n", Field->application);

    for (i = 0; i < Field->maxusage; i++) {
        hal_log_info("\n");
        hal_log_info("usage[%d].hid              = %x\n", i, Field->usage[i].hid);
        hal_log_info("usage[%d].collection_index = %x\n", i, Field->usage[i].collection_index);
        hal_log_info("usage[%d].code             = %x\n", i, Field->usage[i].code);
        hal_log_info("usage[%d].type             = %x\n", i, Field->usage[i].type);
        hal_log_info("usage[%d].hat_min          = %x\n", i, Field->usage[i].hat_min);
        hal_log_info("usage[%d].hat_max          = %x\n", i, Field->usage[i].hat_max);
        hal_log_info("usage[%d].hat_dir          = %x\n", i, Field->usage[i].hat_dir);
    }

    hal_log_info("usage            = %x\n", Field->usage);
    hal_log_info("maxusage         = %x\n", Field->maxusage);
    hal_log_info("flags            = %x\n", Field->flags);
    hal_log_info("report_offset    = %x\n", Field->report_offset);
    hal_log_info("report_size      = %x\n", Field->report_size);
    hal_log_info("report_count     = %x\n", Field->report_count);
    hal_log_info("report_type      = %x\n", Field->report_type);
    hal_log_info("value            = %x\n", Field->value);
    hal_log_info("logical_maximum  = %x\n", Field->logical_maximum);
    hal_log_info("logical_minimum  = %x\n", Field->logical_minimum);
    hal_log_info("physical_maximum = %x\n", Field->physical_maximum);
    hal_log_info("physical_minimum = %x\n", Field->physical_minimum);
    hal_log_info("unit_exponent    = %x\n", Field->unit_exponent);
    hal_log_info("unit             = %x\n", Field->unit);
    hal_log_info("--------------------------------------\n");
}

static void print_item(usbHidItem_t *item)
{
    hal_log_info("\n------------------item-----------------\n");
    hal_log_info("format = %d\n", item->format);
    hal_log_info("size   = %d\n", item->size);
    hal_log_info("type   = %d\n", item->type);
    hal_log_info("tag    = %d\n", item->tag);
    hal_log_info("data   = %x\n", item->data);
    hal_log_info("--------------------------------------\n");

}

static void print_Report(usbHidReport_t *Report)
{
    unsigned int i = 0;
    unsigned int j = 0;

    if(Report == NULL){
        hal_log_err("Report is NULL\n");
        return;
    }

    hal_log_info("\n");

    hal_log_info("\n Report num  = %d\n", i);
    hal_log_info("Report Id       = %d\n", Report->Id);
    hal_log_info("Report Type     = %d\n", Report->Type);
    hal_log_info("Report Maxfield = %d\n", Report->Maxfield);

    for(j = 0; j < Report->Maxfield; j++){
        hal_log_info("\n field num  = %d\n", j);
        print_field(Report->Field[j]);
    }

    hal_log_info("Report Size = %d\n", Report->Size);
}

static void print_ReportEnum(HidDev_t *HidDev)
{
    unsigned int i = 0;
    unsigned int j = 0;
    usbHidReportEnum_t *ReportEnum = NULL;

    hal_log_info("\n\n-----------print_ReportEnum--------\n");
    for(i = 0; i < USB_HID_REPORT_TYPES; i++){
        ReportEnum = &HidDev->HidReportEnum[i];
        if(ReportEnum == NULL){
            continue;
        }

        hal_log_info("\n ReportEnum num  = %d\n", i);
        hal_log_info("ReportEnum numbered = %d\n", ReportEnum->numbered);
        hal_log_info("ReportEnum ReportNum = %d\n", ReportEnum->ReportNum);

        for(j = 0; j < USB_HID_REPORT_MAX_NUM; j++){
            print_Report(ReportEnum->Report[j]);
        }
    }
    hal_log_info("-----------print_ReportEnum--------\n\n");
}

static void print_global(usbHidGlobalItems_t *Global)
{
    hal_log_info("\n");
    hal_log_info("UsagePage       = %x\n", Global->UsagePage);
    hal_log_info("LogicalMaximum  = %d\n", Global->LogicalMaximum);
    hal_log_info("LogicalMinimum  = %d\n", Global->LogicalMinimum);
    hal_log_info("PhysicalMinimum = %d\n", Global->PhysicalMinimum);
    hal_log_info("PhysicalMaximum = %d\n", Global->PhysicalMaximum);
    hal_log_info("UnitExponent    = %d\n", Global->UnitExponent);
    hal_log_info("Unit            = %d\n", Global->Unit);
    hal_log_info("ReportSize      = %d\n", Global->ReportSize);
    hal_log_info("ReportId        = %d\n", Global->ReportId);
    hal_log_info("ReportCount     = %d\n", Global->ReportCount);
    hal_log_info("Push            = %x\n", Global->Push);
    hal_log_info("Pop             = %x\n", Global->Pop);
}

static void print_local(usbHidLocalItems_t *Local)
{
     unsigned int i = 0;

     if(Local == NULL){
        hal_log_err("Local is NULL\n");
        return;
     }

     for(i = 0; i < Local->usage_index; i++){
        hal_log_info("Local->usage[%d] = %x\n", i, Local->usage[i]);
     }
/*
     for(i = 0; i < USB_HID_MAX_USAGES; i++){
        hal_log_info("Local->collection_index[%d] = %x\n", i, Local->collection_index[i]);
     }
*/
     hal_log_info("Local->usage_index      = %d\n", Local->usage_index);
     hal_log_info("Local->usage_minimum    = %d\n", Local->usage_minimum);
     hal_log_info("Local->delimiter_depth  = %d\n", Local->delimiter_depth);
     hal_log_info("Local->delimiter_branch = %d\n", Local->delimiter_branch);
}

static void print_parser(usbHidParser_t *Parser)
{
    unsigned int i = 0;

    hal_log_info("\n");
    hal_log_info("\n");
    hal_log_info("--------------print_parser-------------\n");
    print_global(&Parser->global);
    for(i = 0; i < USB_HID_GLOBAL_STACK_SIZE; i++){
        print_global(&Parser->global_stack[i]);
    }

    hal_log_info("global_stack_ptr = %d\n", Parser->global_stack_ptr);
    print_local(&Parser->local);

    for(i = 0; i < USB_HID_COLLECTION_STACK_SIZE; i++){
        hal_log_info("collection_stack[%d] = %x\n", i, Parser->collection_stack[i]);
    }

    hal_log_info("global_stack_ptr = %d\n", Parser->collection_stack_ptr);
    hal_log_info("--------------------------------------\n");
    hal_log_info("\n");
}

#else

static void print_field(usbHidField_t *Field)
{

}

static void print_item(usbHidItem_t *item)
{

}

static void print_ReportEnum(HidDev_t *HidDev)
{

}

static void print_local(usbHidLocalItems_t *Local)
{

}

static void print_parser(usbHidParser_t *Parser)
{

}

#endif

/*
*******************************************************************************
*                     HidGetIdle
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
int HidGetClassDescriptor(HidDev_t *HidDev,
                             unsigned int InterfaceNo,
                             unsigned int DescriptorType,
                             void *Buffer,
                             unsigned int TransferLength)
{
    int ret = 0;
    unsigned int retries = 4;  /* retry */

    do {
        ret = usb_control_msg(HidDev->pusb_dev,
                              usb_rcvctrlpipe(HidDev->pusb_dev, 0),
                              USB_REQ_GET_DESCRIPTOR,
                              USB_RECIP_INTERFACE | USB_TYPE_STANDARD | USB_DIR_IN,
                              (DescriptorType << 8),
                              InterfaceNo,
                              Buffer,
                              TransferLength,
                              USB_CTRL_GET_TIMEOUT);
        retries--;
    } while (ret < TransferLength && retries);

    if(ret == TransferLength){
        return USB_ERR_SUCCESS;
    }else{
        return USB_ERR_COMMAND_EXECUTE_FAILED;
    }
}

/*
*******************************************************************************
*                     HidGetIdle
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
int HidGetIdle(HidDev_t *HidDev,
                 unsigned int InterfaceNo,
                 unsigned int ReportId,
                 void *IdleRate)
{
    hal_log_err("ERR: HidGetIdle not support\n");

    return USB_ERR_SUCCESS;
}

/*
*******************************************************************************
*                     HidSetIlde
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
int HidSetIlde(HidDev_t *HidDev,
                 unsigned int InterfaceNo,
                 unsigned int Duration,
                 unsigned int ReportId)
{
    int ret = 0;

    ret = usb_control_msg(HidDev->pusb_dev,
                          usb_sndctrlpipe(HidDev->pusb_dev, 0),
                          USB_HID_REQ_SET_IDLE,
                          USB_DIR_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
                          (Duration << 8) | ReportId,
                          InterfaceNo,
                          NULL,
                          0,
                          USB_CTRL_SET_TIMEOUT);
    if(ret < 0){
        hal_log_err("ERR: HidSetIlde: usb_control_msg failed\n");
        return USB_ERR_COMMAND_EXECUTE_FAILED;
    }

    return USB_ERR_SUCCESS;
}

/*
*******************************************************************************
*                     HidGetReport
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
int HidGetReport(HidDev_t *HidDev,
                   unsigned int InterfaceNo,
                   unsigned int ReportType,
                   unsigned int ReportId,
                   unsigned int ReportLength,
                   void  *ReportData)
{
    int ret = 0;

    ret = usb_control_msg(HidDev->pusb_dev,
                          usb_rcvctrlpipe(HidDev->pusb_dev, 0),
                          USB_HID_HID_REQ_GET_REPORT,
                          USB_RECIP_INTERFACE | USB_TYPE_CLASS | USB_DIR_IN,
                          (ReportType << 8) | ReportId,
                          InterfaceNo,
                          ReportData,
                          ReportLength,
                          USB_CTRL_GET_TIMEOUT);

    if(ret == ReportLength){
        return USB_ERR_SUCCESS;
    }else{
        return USB_ERR_COMMAND_EXECUTE_FAILED;
    }
}

/*
*******************************************************************************
*                     HidSetReport
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
int HidSetReport(HidDev_t *HidDev,
                   unsigned int InterfaceNo,
                   unsigned int ReportType,
                   unsigned int ReportId,
                   unsigned int ReportLength,
                   void *ReportData)
{
    hal_log_err("ERR: HidGetIdle not support\n");

    return USB_ERR_SUCCESS;
}

/*
*******************************************************************************
*                     HidGetProtocol
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
int HidGetProtocol(HidDev_t *HidDev, unsigned int InterfaceNo, void *ProtocolData)
{
    hal_log_err("ERR: HidGetIdle not support\n");

    return USB_ERR_SUCCESS;
}

/*
*******************************************************************************
*                     HidSetProtocol
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
int HidSetProtocol(HidDev_t *HidDev, unsigned int InterfaceNo, unsigned int Protocoltype)
{
    hal_log_err("ERR: HidGetIdle not support\n");

    return USB_ERR_SUCCESS;
}

/*
*******************************************************************************
*                     HidRegisterReport
*
* Description:
*     Register a new report for a device.
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
static usbHidReport_t *HidRegisterReport(HidDev_t *HidDev, unsigned int type, unsigned int id)
{
    usbHidReportEnum_t *ReportEnum = HidDev->HidReportEnum + type;
    usbHidReport_t *Report = NULL;

    if (ReportEnum->Report[id]){
        return ReportEnum->Report[id];
    }

    Report = hal_malloc(sizeof(usbHidReport_t));
    if (Report == NULL){
        hal_log_err("ERR: malloc failed\n");
        return NULL;
    }

    ReportEnum->ReportNum  += 1;

    memset(Report, 0, sizeof(usbHidReport_t));

    if (id != 0){
        ReportEnum->numbered = 1;
    }

    Report->Id              = id;
    Report->Type            = type;
    Report->Size            = 0;
    ReportEnum->Report[id]  = Report;

    return Report;
}

/*
*******************************************************************************
*                     HidRegisterField
*
* Description:
*     Register a new field for this report.
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
static usbHidField_t *HidRegisterField(usbHidReport_t *Report, unsigned int Usages, unsigned int Values)
{
    usbHidField_t *Field = NULL;

    if (Report->Maxfield >= USB_HID_MAX_FIELDS) {
        hal_log_err("ERR: too many fields in report\n");
        return NULL;
    }

    Field = (usbHidField_t *)hal_malloc(sizeof(usbHidField_t));
    if (Field == NULL){
        hal_log_err("ERR: malloc failed\n");
        return NULL;
    }

    memset(Field, 0, sizeof(usbHidField_t));

    Field->usage = (usbHidUsage_t *)hal_malloc(Usages * sizeof(usbHidUsage_t));
    if (Field->usage == NULL){
        hal_log_err("ERR: malloc failed\n");
        goto ERR;
    }
    memset(Field->usage, 0, Usages * sizeof(usbHidUsage_t));

    Field->value = (unsigned int *)hal_malloc(Values * sizeof(unsigned int));
    if (Field->value == NULL){
        hal_log_err("ERR: malloc failed\n");
        goto ERR;
    }
    memset(Field->value, 0, Values * sizeof(unsigned int));

    Field->Index                = Report->Maxfield++;
    Report->Field[Field->Index] = Field;
    Field->HidReport            = Report;

    return Field;

ERR:
    if(Field->usage){
        hal_free(Field->usage);
        Field->usage = NULL;
    }

    hal_free(Field);
    Field = NULL;

    return NULL;
}

/*
*******************************************************************************
*                     open_collection
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
static int open_collection(usbHidParser_t *parser, unsigned type)
{
    usbHidCollectionItems_t *collection = NULL;
    unsigned int usage = 0;

    // 从取出最先进入local的usage
    // 在处理local usage的函数hid_parser_local==>HID_LOCAL_ITEM_TAG_USAGE中
    // data = (parser->global.usage_page local.usage[0];
    // 高16位对应global.usage_page,低16位才对应local的usage
    // 比如报告描述符的前6个字节数据如下：
    // parser->global.usage_page = 0x01;  0x05, 0x01, // USAGE_PAGE (Generic Desktop)
    // parser->local.usage[0] = (0x01 local.usage[0] = (0x01 local.usage[0];
    usage = parser->local.usage[0];

    if (parser->collection_stack_ptr == USB_HID_COLLECTION_STACK_SIZE) {
        hal_log_err("ERR: collection stack overflow\n");
        return -1;
    }

    if (parser->HidDev->maxcollection == parser->HidDev->collection_size) {
        collection = hal_malloc(sizeof(usbHidCollectionItems_t) * parser->HidDev->collection_size * 2);
        if (collection == NULL) {
            hal_log_err("ERR: failed to reallocate collection array\n");
            return -1;
        }

        memset(collection, 0, sizeof(usbHidCollectionItems_t) * parser->HidDev->collection_size * 2);

        memcpy(collection,
                      parser->HidDev->collection,
                      sizeof(usbHidCollectionItems_t) * parser->HidDev->collection_size);
        memset(collection + parser->HidDev->collection_size,
                      0,
                      sizeof(usbHidCollectionItems_t) * parser->HidDev->collection_size);

        hal_free(parser->HidDev->collection);
        parser->HidDev->collection = collection;
        parser->HidDev->collection_size *= 2;
    }

    parser->collection_stack[parser->collection_stack_ptr++] = parser->HidDev->maxcollection;
    collection          = parser->HidDev->collection + parser->HidDev->maxcollection++;
    collection->Type    = type;
    collection->Usage   = usage;
    collection->Level   = parser->collection_stack_ptr - 1;

    if (type == USB_HID_COLLECTION_APPLICATION){
        parser->HidDev->maxapplication++;
    }

    return 0;
}

/*
*******************************************************************************
*                     close_collection
*
* Description:
*     Close a collection.
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
static int close_collection(usbHidParser_t *parser)
{
    if (!parser->collection_stack_ptr) {
        hal_log_err("ERR: collection stack underflow\n");
        return -1;
    }

    parser->collection_stack_ptr--;

    return 0;
}

/*
*******************************************************************************
*                     hid_lookup_collection
*
* Description:
*     Climb up the stack, search for the specified collection type
* and return the usage.
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
static unsigned hid_lookup_collection(usbHidParser_t *parser, unsigned int type)
{
    int n = 0;

    for (n = parser->collection_stack_ptr - 1; n >= 0; n--){
        if (parser->HidDev->collection[parser->collection_stack[n]].Type == type){
            return parser->HidDev->collection[parser->collection_stack[n]].Usage;
        }
    }

    return 0; /* we know nothing about this usage type */
}


/*
*******************************************************************************
*                     HidAddUsage
*
* Description:
*     Add a usage to the temporary parser table.
*
* Parameters:
*     Parser : output.
*     Usage  : input.
*
* Return value:
*
*
* note:
*    无
*
*******************************************************************************
*/
static int HidAddUsage(usbHidParser_t *Parser, unsigned int Usage)
{
    if (Parser->local.usage_index >= USB_HID_MAX_USAGES) {
        hal_log_err("ERR: usage index exceeded\n");
        return USB_ERR_DATA_OVERFLOW;
    }

    Parser->local.usage[Parser->local.usage_index] = Usage;
    Parser->local.collection_index[Parser->local.usage_index] =
        Parser->collection_stack_ptr ?
        Parser->collection_stack[Parser->collection_stack_ptr - 1] : 0;
    Parser->local.usage_index++;

    return 0;
}

/*
*******************************************************************************
*                     HidAddField
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
static int HidAddField(usbHidParser_t *Parser, unsigned int ReportType, unsigned int Flags)
{
    usbHidReport_t *Report = NULL;
    usbHidField_t *Field = NULL;
    int usages = 0;
    unsigned int offset = 0;
    int i = 0;

    Report = HidRegisterReport(Parser->HidDev, ReportType, Parser->global.ReportId);
    if (Report == NULL) {
        hal_log_err("ERR: hid_register_report failed\n");
        return -1;
    }

    if (Parser->global.LogicalMaximum < Parser->global.LogicalMinimum) {
        hal_log_err("ERR: logical range invalid (%d, %d)\n", Parser->global.LogicalMinimum,
                                                            Parser->global.LogicalMaximum);
        return USB_ERR_BAD_ARGUMENTS;
    }

    offset = Report->Size;
    Report->Size += Parser->global.ReportSize * Parser->global.ReportCount;

    if (!Parser->local.usage_index){ /* Ignore padding fields */
        return 0;
    }

    usages = max(Parser->local.usage_index, Parser->global.ReportCount);

    Field = HidRegisterField(Report, usages, Parser->global.ReportCount);
    if (Field == NULL){
        hal_log_err("ERR: HidRegisterField failed\n");
        return 0;
    }

    Field->physical = hid_lookup_collection(Parser, USB_HID_COLLECTION_PHYSICAL);
    Field->logical = hid_lookup_collection(Parser, USB_HID_COLLECTION_LOGICAL);
    Field->application = hid_lookup_collection(Parser, USB_HID_COLLECTION_APPLICATION);

    for (i = 0; i < usages; i++) {
        int j = i;

        /* Duplicate the last usage we parsed if we have excess values */
        if (i >= Parser->local.usage_index){
            j = Parser->local.usage_index - 1;
        }

        Field->usage[i].hid = Parser->local.usage[j];
        Field->usage[i].collection_index = Parser->local.collection_index[j];
    }

    Field->maxusage         = usages;
    Field->flags            = Flags;
    Field->report_offset    = offset;
    Field->report_type      = ReportType;
    Field->report_size      = Parser->global.ReportSize;
    Field->report_count     = Parser->global.ReportCount;
    Field->logical_minimum  = Parser->global.LogicalMinimum;
    Field->logical_maximum  = Parser->global.LogicalMaximum;
    Field->physical_minimum = Parser->global.PhysicalMinimum;
    Field->physical_maximum = Parser->global.PhysicalMaximum;
    Field->unit_exponent    = Parser->global.UnitExponent;
    Field->unit             = Parser->global.Unit;

    print_field(Field);

    return 0;
}

/*
*******************************************************************************
*                     item_udata
*
* Description:
*     Read data value from item.
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
static unsigned int item_udata(usbHidItem_t *Item)
{
    switch (Item->size) {
        case 1:
            return Item->data.Data_u8;
        //break;

        case 2:
            return Item->data.Data_u16;
        //break;

        case 4:
            return Item->data.Data_u32;
        //break;

        default:
            hal_log_err("ERR: unkown item size(%d)\n", Item->size);
    }

    return 0;
}

/*
*******************************************************************************
*                     item_sdata
*
* Description:
*     Read data value from item.
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
static int item_sdata(usbHidItem_t *Item)
{
    switch (Item->size) {
        case 1:
            return Item->data.Data_s8;
        //break;

        case 2:
            return Item->data.Data_s16;
        //break;

        case 4:
            return Item->data.Data_s32;
        //break;

        default:
            hal_log_err("ERR: unkown item size(%d)\n", Item->size);
    }

    return 0;
}

/*
*******************************************************************************
*                     HidParserGlobal
*
* Description:
*     解析全局目录项
*
* Parameters:
*     Parser  :  output. 解析的结果
*     Item    :  input.  待解析的目录项
*
* Return value:
*    成功或者失败
*
* note:
*    无
*
*******************************************************************************
*/
static int HidParserGlobal(usbHidParser_t *Parser, usbHidItem_t *Item)
{
    switch(Item->tag){
        case USB_HID_GLOBAL_ITEM_TAG_PUSH:

            if (Parser->global_stack_ptr == USB_HID_GLOBAL_STACK_SIZE) {
                hal_log_err("ERR: global enviroment stack overflow\n");
                return USB_ERR_DATA_OVERFLOW;
            }

            /* 将parser->global压入堆栈parser->global_stack[global_stack_ptr] */
            memcpy(Parser->global_stack + Parser->global_stack_ptr++,
                          &Parser->global,
                          sizeof(usbHidGlobalItems_t));
            return USB_ERR_SUCCESS;
        //break;

        case USB_HID_GLOBAL_ITEM_TAG_POP:

            if (!Parser->global_stack_ptr) {
                hal_log_err("ERR: global enviroment stack underflow\n");
                return -1;
            }

            /* 将parser->global_stack[--global_stack_ptr]出栈[luther.gliethttp] */
            memcpy(&Parser->global,
                          Parser->global_stack + --Parser->global_stack_ptr,
                          sizeof(usbHidGlobalItems_t));
            return USB_ERR_SUCCESS;
        //break;

        case USB_HID_GLOBAL_ITEM_TAG_USAGE_PAGE:
            /* 全局量global.usage_page, 比如:
               0x05, 0x01, --- USAGE_PAGE (Generic Desktop)
               0x05, 0x09, --- USAGE_PAGE (Button)
             */
            Parser->global.UsagePage = item_udata(Item);
            return USB_ERR_SUCCESS;
        //break;

        case USB_HID_GLOBAL_ITEM_TAG_LOGICAL_MINIMUM:
            Parser->global.LogicalMinimum = item_sdata(Item);
            return USB_ERR_SUCCESS;
        //break;

        case USB_HID_GLOBAL_ITEM_TAG_LOGICAL_MAXIMUM:
            if (Parser->global.LogicalMinimum< 0){
                Parser->global.LogicalMaximum = item_sdata(Item);
            }else{
                Parser->global.LogicalMaximum = item_udata(Item);
            }

            return USB_ERR_SUCCESS;
        //break;

        case USB_HID_GLOBAL_ITEM_TAG_PHYSICAL_MINIMUM:
            Parser->global.PhysicalMinimum = item_sdata(Item);
            return USB_ERR_SUCCESS;
        //break;

        case USB_HID_GLOBAL_ITEM_TAG_PHYSICAL_MAXIMUM:
            if (Parser->global.PhysicalMinimum< 0){
                Parser->global.PhysicalMaximum = item_sdata(Item);
            }else{
                Parser->global.PhysicalMaximum = item_udata(Item);
            }

            return USB_ERR_SUCCESS;
        //break;

        case USB_HID_GLOBAL_ITEM_TAG_UNIT_EXPONENT:
            Parser->global.UnitExponent= item_sdata(Item);
            return USB_ERR_SUCCESS;
        //break;

        case USB_HID_GLOBAL_ITEM_TAG_UNIT:
            Parser->global.Unit = item_udata(Item);
            return USB_ERR_SUCCESS;
        //break;

        case USB_HID_GLOBAL_ITEM_TAG_REPORT_SIZE:
            /* 比如：0x75, 0x01, REPORT_SIZE (1), 表示1个bit */
            if ((Parser->global.ReportSize = item_udata(Item)) > 32) {
                hal_log_err("ERR: invalid report_size %d\n", Parser->global.ReportSize);
                return USB_ERR_UNKOWN_ERROR;
            }
            return USB_ERR_SUCCESS;
        //break;

        case USB_HID_GLOBAL_ITEM_TAG_REPORT_COUNT:
            if ((Parser->global.ReportCount = item_udata(Item)) > USB_HID_MAX_USAGES) {
                hal_log_err("ERR: invalid report_count %d\n", Parser->global.ReportSize);
                return USB_ERR_UNKOWN_ERROR;
            }
            return USB_ERR_SUCCESS;
        //break;

        case USB_HID_GLOBAL_ITEM_TAG_REPORT_ID:
            if ((Parser->global.ReportId = item_udata(Item)) == 0) {
                hal_log_err("ERR: report_id 0 is invalid\n");
                return USB_ERR_UNKOWN_ERROR;
            }
            return USB_ERR_SUCCESS;
        //break;

        default:
            hal_log_err("ERR: unknown global tag 0x%x\n", Item->tag);
            //return USB_ERR_UNKOWN_ERROR;
    }

    return USB_ERR_UNKOWN_ERROR;
}

/*
*******************************************************************************
*                     HidParserGlobal
*
* Description:
*     解析全局目录项
*
* Parameters:
*     Parser  :  output. 解析的结果
*     Item    :  input.  待解析的目录项
*
* Return value:
*    成功或者失败
*
* note:
*    无
*
*******************************************************************************
*/
static int HidParserLocal(usbHidParser_t *Parser, usbHidItem_t *Item)
{
    unsigned int data = 0;
    unsigned int n = 0;

    if (Item->size == 0) {
        hal_log_err("ERR: item data expected for local item\n");
        return -1;
    }

    data = item_udata(Item);

    switch (Item->tag) {
        case USB_HID_LOCAL_ITEM_TAG_DELIMITER:
            if (data) {
                /*
                 * We treat items before the first delimiter
                 * as global to all usage sets (branch 0).
                 * In the moment we process only these global
                 * items and the first delimiter set.
                 */
                if (Parser->local.delimiter_depth != 0) {
                    hal_log_err("ERR: nested delimiters\n");
                    return -1;
                }

                Parser->local.delimiter_depth++;
                Parser->local.delimiter_branch++;
            } else {
                if (Parser->local.delimiter_depth < 1) {
                    hal_log_err("ERR: bogus close delimiter\n");
                    return -1;
                }

                Parser->local.delimiter_depth--;
            }
            return 1;
        //break;

        case USB_HID_LOCAL_ITEM_TAG_USAGE:
            if (Parser->local.delimiter_branch > 1) {
                hal_log_err("ERR: alternative usage ignored\n");
                return 0;
            }

            if (Item->size <= 2){
                data = (Parser->global.UsagePage << 16) + data;
            }

            return HidAddUsage(Parser, data);
        //break;

        case USB_HID_LOCAL_ITEM_TAG_USAGE_MINIMUM:
            if (Parser->local.delimiter_branch > 1) {
                hal_log_err("ERR: alternative usage ignored\n");
                return 0;
            }

            if (Item->size <= 2){
                data = (Parser->global.UsagePage << 16) + data;
            }

            Parser->local.usage_minimum = data;

            return 0;
        //break;

        case USB_HID_LOCAL_ITEM_TAG_USAGE_MAXIMUM:
            if (Parser->local.delimiter_branch > 1) {
                hal_log_err("ERR: alternative usage ignored\n");
                return 0;
            }

            if (Item->size <= 2){
                data = (Parser->global.UsagePage << 16) + data;
            }

            for (n = Parser->local.usage_minimum; n <= data; n++){
                if (HidAddUsage(Parser, n)) {
                    hal_log_err("ERR: hid_add_usage failed\n");
                    return -1;
                }
            }

            return 0;
        //break;

        default:
            hal_log_err("ERR: unknown local item tag 0x%x\n", Item->tag);
            //return 0;
    }

    return 0;
}

/*
*******************************************************************************
*                     hid_parser_main
*
* Description:
*     Process a main item.
*
* Parameters:
*
*
* Return value:
*    成功或者失败
*
* note:
*    无
*
*******************************************************************************
*/
static int HidParserMain(usbHidParser_t *parser, usbHidItem_t *item)
{
    unsigned int data = 0;
    int ret = 0;

    data = item_udata(item);    //返回该Short Item数据,数据有4种,0,1,2,4字节

    switch (item->tag) {
        case USB_HID_MAIN_ITEM_TAG_BEGIN_COLLECTION:
            //Open a collection. 入栈push操作The type/usage is pushed on the stack
            ret = open_collection(parser, data & 0xff);
        break;

        case USB_HID_MAIN_ITEM_TAG_END_COLLECTION:
            // Close a collection.出栈pop操作parser->collection_stack_ptr
            ret = close_collection(parser);
        break;

        case USB_HID_MAIN_ITEM_TAG_INPUT:
            ret = HidAddField(parser, USB_HID_REPORT_INPUT, data);
        break;

        case USB_HID_MAIN_ITEM_TAG_OUTPUT:
            ret = HidAddField(parser, USB_HID_REPORT_OUTPUT, data);
        break;

        case USB_HID_MAIN_ITEM_TAG_FEATURE:
            ret = HidAddField(parser, USB_HID_REPORT_FEATURE, data);
        break;

        default:
            hal_log_err("ERR: unknown main item tag 0x%x\n", item->tag);
            ret = 0;
    }

    // 清0所有parser->local内存数据,local包括:
    // struct hid_local {
    //    unsigned usage[HID_MAX_USAGES];               /* usage array */
    //    unsigned collection_index[HID_MAX_USAGES];    /* collection index array */
    //    unsigned usage_index;
    //    unsigned usage_minimum;
    //    unsigned delimiter_depth;
    //    unsigned delimiter_branch;
    // };
    // 所以parser->local.usage_index在遇到main item时全部清0.
    print_local(&(parser->local));
    memset(&(parser->local), 0, sizeof(parser->local)); /* Reset the local parser environment */

    return ret;
}

/*
*******************************************************************************
*                     hid_parser_main
*
* Description:
*     Process a reserved item..
*
* Parameters:
*
*
* Return value:
*    成功或者失败
*
* note:
*    无
*
*******************************************************************************
*/
static int HidParserReserved(usbHidParser_t *parser, usbHidItem_t *item)
{
    hal_log_err("ERR: reserved item type, tag 0x%x\n", item->tag);

    return 0;
}

/*
 * Free a report and all registered fields. The field->usage and
 * field->value table's are allocated behind the field, so we need
 * only to free(field) itself.
 */

static void hid_free_report(usbHidReport_t *report)
{
    unsigned int n;

    for (n = 0; n < report->Maxfield; n++){
        if(report->Field[n]){
            if(report->Field[n]->usage){
                hal_free(report->Field[n]->usage);
                report->Field[n]->usage = NULL;
            }

            if(report->Field[n]->value){
                hal_free(report->Field[n]->value);
                report->Field[n]->value = NULL;
            }

            hal_free(report->Field[n]);
            report->Field[n] = NULL;
        }
    }

    hal_free(report);

    return;
}

/*
 * Free a device structure, all reports, and all fields.
 */

void hid_free_device(HidDev_t *HidDev)
{
    unsigned int i = 0;
    unsigned int j = 0;

    for (i = 0; i < USB_HID_REPORT_TYPES; i++) {
        usbHidReportEnum_t *report_enum = HidDev->HidReportEnum + i;

        for (j = 0; j < 256; j++) {
            usbHidReport_t *report = report_enum->Report[j];

            if (report){
                report_enum->ReportNum  -= 1;
                hid_free_report(report);
                report_enum->Report[j] = NULL;
            }
        }
    }

    if(HidDev->collection){
        hal_free(HidDev->collection);
        HidDev->collection = NULL;
    }

    return ;
}

/*
*******************************************************************************
*                     HidFetchItem
*
* Description:
*     取出Item，并且解析
*
* Parameters:
*     Start  :  input.  本次带解析的report起始地址
*     End    :  input.  report的结束地址
*     Item   :  output. 解析后的Item
*
* Return value:
*    返回解析后的Item
*
* note:
*    无
*
*******************************************************************************
*/
static __u8 *HidFetchItem(__u8 *Start, __u8 *End, usbHidItem_t *Item)
{
    __u8 b = 0;

    if(Start == NULL || End == NULL || Item == NULL){
        hal_log_err("ERR: input error\n");
        return NULL;
    }

    memset(Item, 0, sizeof(usbHidItem_t));

    if ((End - Start) <= 0){
        hal_log_err("ERR: the item is invalid. Start = %x, End = %x\n", Start, End);
        return NULL;
    }

    b = *Start++;

    Item->type = (b >> 2) & 3;  // 取出类型
    Item->tag  = (b >> 4) & 15; // 取出tag信息

    if (Item->tag == USB_HID_ITEM_TAG_LONG) {
        Item->format = USB_HID_ITEM_FORMAT_LONG;

        if ((End - Start) < 2){
            hal_log_err("ERR: the item is invalid. Start = %x, End = %x\n", Start, End);
            return NULL;
        }

        Item->size = *Start++;
        Item->tag  = *Start++;

        // 保证该Long item拥有所需的足够数据
        if ((End - Start) < Item->size){
            hal_log_err("ERR: the item is invalid. Start = %x, End = %x, Item->size = %x\n",
                       Start, End, Item->size);
            return NULL;
        }

        Item->data.longdata = Start;    // 从第4个字节开始就是数据区
        Start += Item->size;            // start指向下一个item开始处

        return Start;
    }

    Item->format = USB_HID_ITEM_FORMAT_SHORT;
    Item->size = b & 3;  //取出数据大小

    switch(Item->size){
        case 0: // 没有数据区,start指向下一个item开始处
            return Start;

        case 1:
            if ((End - Start) < 1)
                return NULL;
            Item->data.Data_u8 = *Start++;   // 取出1字节数据
            return Start;

        case 2:
            if ((End - Start) < 2)
                return NULL;
            Item->data.Data_u16 = le16_to_cpu(*((__u16 *)Start));
            Start = (__u8 *)((__u16 *)Start + 1);   // start加2
            return Start;

        case 3:
            Item->size++;   // 强制调整到4字节
            if ((End - Start) < 4)
                return NULL;
            Item->data.Data_u32 = le32_to_cpu(*((unsigned int*)Start));
            Start = (__u8 *)((unsigned int *)Start + 1);    // start加4
            return Start;
    }

    return NULL;
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
int HidParseReport(__u8 *ReportData, unsigned int ReportSize, HidDev_t *HidDev)
{
    usbHidParser_t *parser = NULL;  /* 因为usbHidParser_t结构大于16k, 因此使用malloc */
    usbHidItem_t item;
    __u8 *end = NULL;
    int ret = 0;

    parser = (usbHidParser_t *)hal_malloc(sizeof(usbHidParser_t));
    if(parser == NULL){
        hal_log_err("ERR: malloc failed\n");
        ret = USB_ERR_MALLOC_FAILED;

        goto ERR0;
    }
    memset(parser, 0, sizeof(usbHidParser_t));

    HidDev->collection = hal_malloc(sizeof(usbHidCollectionItems_t) *
                                        USB_HID_DEFAULT_NUM_COLLECTIONS);
    if (HidDev->collection == NULL) {
        hal_log_err("ERR: malloc failed\n");
        ret = USB_ERR_MALLOC_FAILED;

        goto ERR1;
    }
    memset(HidDev->collection,
                  0,
                  sizeof(usbHidCollectionItems_t) * USB_HID_DEFAULT_NUM_COLLECTIONS);

    HidDev->collection_size = USB_HID_DEFAULT_NUM_COLLECTIONS;
    parser->HidDev = HidDev;

    // 从设备报告描述符中读取一个item项
    end = ReportData + ReportSize;
    while ((ReportData = HidFetchItem(ReportData, end, &item)) != NULL) {
        print_item(&item);

        /* 现在Long item项还没有使用,所以这里不支持 */
        if (item.format != USB_HID_ITEM_FORMAT_SHORT) {
            hal_log_err("ERR: unexpected long global item\n");
            ret = USB_ERR_UNKOWN_ERROR;
            goto ERR2;
        }

        switch(item.type){
            case USB_HID_ITEM_TYPE_MAIN:
                if (HidParserMain(parser, &item)) {
                    hal_log_err("ERR: item %u %u %u %u parsing failed\n",
                                     item.format,
                                     (unsigned)item.size,
                                     (unsigned)item.type,
                                     (unsigned)item.tag);
                    ret = USB_ERR_UNKOWN_ERROR;
                    goto ERR2;
                }
            break;

            case USB_HID_ITEM_TYPE_GLOBAL:
                if (HidParserGlobal(parser, &item)) {
                    hal_log_err("ERR: item %u %u %u %u parsing failed\n",
                                     item.format,
                                     (unsigned)item.size,
                                     (unsigned)item.type,
                                     (unsigned)item.tag);
                    ret = USB_ERR_UNKOWN_ERROR;
                    goto ERR2;
                }
            break;

            case USB_HID_ITEM_TYPE_LOCAL:
                if (HidParserLocal(parser, &item)) {
                    hal_log_err("ERR: item %u %u %u %u parsing failed\n",
                                     item.format,
                                     (unsigned)item.size,
                                     (unsigned)item.type,
                                     (unsigned)item.tag);
                    ret = USB_ERR_UNKOWN_ERROR;
                    goto ERR2;
                }
            break;

            default:
                if (HidParserReserved(parser, &item)) {
                    hal_log_err("ERR: item %u %u %u %u parsing failed\n",
                                     item.format,
                                     (unsigned)item.size,
                                     (unsigned)item.type,
                                     (unsigned)item.tag);
                    ret = USB_ERR_UNKOWN_ERROR;
                    goto ERR2;
                }
        }

        // 解析完了
        if (ReportData == end) {
            // 入栈操作多于出栈操作,比如COLLECTION (Application)就是入栈, END_COLLECTION对应出栈
            // 目前定义堆栈大小为4个, #define HID_COLLECTION_STACK_SIZE 4
            // 所以报告描述符脚本书写有误,返回NULL,失败
            if (parser->collection_stack_ptr) {
                hal_log_err("ERR: unbalanced collection at end of report description\n");
                ret = USB_ERR_UNKOWN_ERROR;
                goto ERR2;
            }

            // 该变量也是通过入栈,出栈收集的,所以也必须配对
            if (parser->local.delimiter_depth) {
                hal_log_err("ERR: unbalanced delimiter at end of report description\n");
                ret = USB_ERR_UNKOWN_ERROR;
                goto ERR2;
            }

            print_ReportEnum(HidDev);
            print_parser(parser);

            if(parser){
                hal_free(parser);
            }

            //正常解析成功,释放vmalloc到的parser解释器结构体内存.
            return USB_ERR_SUCCESS;
        }
    }

    // 报告描述脚本有误
    hal_log_err("ERR: item fetching failed at offset %d\n", (int)(end - ReportData));

    ret = USB_ERR_UNKOWN_ERROR;

ERR2:
    hid_free_device(HidDev);
    hal_free(HidDev->collection);
    HidDev->collection = NULL;

ERR1:
    hal_free(parser);

ERR0:

    return ret;
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
int HidFreeReport(HidDev_t *HidDev)
{

    hid_free_device(HidDev);

    if(HidDev->collection){
        hal_free(HidDev->collection);
        HidDev->collection = NULL;
    }

    return USB_ERR_SUCCESS;

}

