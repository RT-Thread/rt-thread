#ifndef __USBH_CORE_H__
#define __USBH_CORE_H__

#include <stdint.h>
#include "usbh_conf.h"


typedef enum {
    USBH_OK = 0,
    USBH_BUSY,
    USBH_FAIL,
    USBH_NOT_SUPPORTED,
    USBH_UNRECOVERED_ERROR,
    USBH_APPLY_DEINIT
} USBH_Status;


typedef enum {
    HOST_IDLE = 0,
    HOST_DEV_ATTACHED,
    HOST_PORT_RESETED,
    HOST_PORT_ENABLED,
    HOST_ENUMERATION,
    HOST_CLASS_REQUEST,
    HOST_CLASS,
    HOST_CTRL_XFER,
    HOST_USR_INPUT,
    HOST_SUSPENDED,
    HOST_WAKEUP,
    HOST_DEV_DETACHED,
} HOST_State;


typedef enum {
    ENUM_GET_DEV_DESC = 0,
    ENUM_GET_FULL_DEV_DESC,
    ENUM_SET_ADDR,
    ENUM_GET_CFG_DESC,
    ENUM_GET_FULL_CFG_DESC,
    ENUM_GET_VENDOR_STRING_DESC,
    ENUM_GET_PRODUCT_STRING_DESC,
    ENUM_GET_SERIALNUM_STRING_DESC,
    ENUM_SET_CONFIGURATION,
    ENUM_DEV_CONFIGURED
} ENUM_State;


typedef enum {
    CTRL_IDLE = 0,
    CTRL_SETUP,
    CTRL_SETUP_WAIT,
    CTRL_DATA_IN,
    CTRL_DATA_IN_WAIT,
    CTRL_DATA_OUT,
    CTRL_DATA_OUT_WAIT,
    CTRL_STATUS_IN,
    CTRL_STATUS_IN_WAIT,
    CTRL_STATUS_OUT,
    CTRL_STATUS_OUT_WAIT,
    CTRL_ERROR,
    CTRL_STALLED,
    CTRL_COMPLETE
} CTRL_State;


typedef struct {
    uint8_t            pksz;    // 控制传输包大小
    uint8_t           *buff;    // 控制传输的数据阶段缓冲区
    uint16_t           size;    // 控制传输的数据阶段缓冲区大小
    CTRL_State         state;
    USB_Setup_Packet_t setup;   // Setup 包

    uint8_t        toggle_in;
    uint8_t        toggle_out;
} USBH_CtrlXfer_t;


typedef struct {
    uint8_t        Address;
    uint8_t        Speed;       // 2 低速   3 全速
    USB_DevDesc_t  Dev_Desc;
    USB_CfgDesc_t  Cfg_Desc;
    USB_IntfDesc_t Intf_Desc[USBH_MAX_NUM_INTERFACES];
    USB_EpDesc_t   Ep_Desc[USBH_MAX_NUM_INTERFACES][USBH_MAX_NUM_ENDPOINTS];
    USB_HIDDesc_t  HID_Desc[USBH_MAX_NUM_INTERFACES];
    uint8_t        HIDReport_Desc[USBH_MAX_NUM_INTERFACES][USBH_HID_REPORT_SIZE];
    char strVender[USBH_MAX_STR_SIZE];
    char strProduct[USBH_MAX_STR_SIZE];
    char strSerialNumber[USBH_MAX_STR_SIZE];
} USBH_Device_t;

extern uint8_t  USBH_Cfg_Desc_Buffer[USBH_MAX_CFG_SIZE];
extern uint16_t USBH_Cfg_Desc_Length;

struct USBH_Info_T;
typedef struct {
    USBH_Status (*Init)(struct USBH_Info_T *phost);
    void        (*DeInit)(struct USBH_Info_T *phost);
    USBH_Status (*Request)(struct USBH_Info_T *phost);
    USBH_Status (*Process)(struct USBH_Info_T *phost);
} USBH_Class_cb_t;


typedef struct {
    void (*Init)(void);
    void (*DeInit)(void);
    void (*DeviceAttached)(void);
    void (*ResetDevice)(void);
    void (*DeviceDisconnected)(void);
    void (*OverCurrentDetected)(void);
    void (*DeviceSpeedDetected)(uint8_t DeviceSpeed);
    void (*DeviceDescAvailable)(USB_DevDesc_t *devDesc);
    void (*DeviceAddressAssigned)(void);
    void (*ConfigDescAvailable)(USB_CfgDesc_t *cfgDesc, USB_IntfDesc_t *intfDesc, USB_EpDesc_t *epDesc);
    void (*VendorString)(char *);
    void (*ProductString)(char *);
    void (*SerialNumString)(char *);
    void (*EnumerationDone)(void);
    uint32_t (*UserInput)(void);
    int  (*UserApplication)(void);
    void (*DeviceNotSupported)(void);
    void (*UnrecoveredError)(void);
} USBH_User_cb_t;


typedef struct USBH_Info_T {
    HOST_State       State;             // Host State Machine
    HOST_State       StateBkp;          // State Backup
    ENUM_State       EnumState;         // Enumeration state Machine

    USBH_CtrlXfer_t  Ctrl;
    USBH_Device_t    Device;

    USBH_Class_cb_t *class_cb;
    USBH_User_cb_t  *usr_cb;
} USBH_Info_t;


void USBH_Init(USBH_Class_cb_t *class_cb, USBH_User_cb_t *usr_cb);
void USBH_DeInit(void);

void USBH_Process(void);
USBH_Status USBH_HandleEnum(USBH_Info_t *phost);
void USBH_HandleControl(USBH_Info_t *phost);
USBH_Status USBH_CtrlTransfer(USBH_Info_t *phost, uint8_t *buff, uint16_t size);

void USBH_ErrorHandle(USBH_Info_t *phost, USBH_Status errType);

#endif

