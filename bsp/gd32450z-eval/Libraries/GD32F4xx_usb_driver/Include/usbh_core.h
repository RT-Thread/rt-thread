/*!
    \file  usbh_core.h
    \brief header file for usbh_core.c
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-08-15, V1.0.1, firmware for GD32F4xx
*/

#ifndef USBH_CORE_H
#define USBH_CORE_H

#include "usbh_conf.h"
#include "usb_std.h"
#include "usb_core.h"

#define MSC_CLASS                       0x08    /*!< the MSC class define */
#define HID_CLASS                       0x03    /*!< the HID class define */
#define MSC_PROTOCOL                    0x50    /*!< the MSC protocal define */
#define CBI_PROTOCOL                    0x01    /*!< the CBI protocal define */

#define USBH_DEVICE_ADDRESS_DEFAULT     0U      /*!< the default device address define */
#define USBH_DEVICE_ADDRESS             1U      /*!< the device address define */
#define USBH_MAX_ERROR_COUNT            2U      /*!< the max error count define */

#define HOST_USER_SELECT_CONFIGURATION  1U      /*!< the user select configuration define */
#define HOST_USER_CLASS_ACTIVE          2U      /*!< the user class active define */
#define HOST_USER_CLASS_SELECTED        3U      /*!< the user class selected define */
#define HOST_USER_CONNECTION            4U      /*!< the user connecttion define */
#define HOST_USER_DISCONNECTION         5U      /*!< the user disconnection define */
#define HOST_USER_UNRECOVERED_ERROR     6U      /*!< the user unrecovered error define */

#define MAX_USBH_STATE_STACK_DEEP       4       /*!< the max state stack deep define */
#define MAX_USBH_STATE_TABLE_NUM        10U     /*!< the max state table number */

#define HOST_FSM_ID                     0U      /*!< the host state table id */
#define ENUM_FSM_ID                     1U      /*!< the enum state table id */
#define CMD_FSM_ID                      2U      /*!< the cmd state table id */
#define CTRL_FSM_ID                     3U      /*!< the ctrl state table id */
#define CLASS_REQ_FSM_ID                4U      /*!< the class req state table id */
#define CLASS_FSM_ID                    5U      /*!< the class state table id */

#define UP_STATE                        100U    /*!< up state define */
#define GO_TO_UP_STATE_EVENT            100U    /*!< go to up state event define */

#define HOST_HANDLE_TABLE_SIZE          9U      /*!< the host handle table size define */

/* the enum of host state */
typedef enum 
{
    HOST_IDLE = 0,                     /* the host idle state definition */
    HOST_DEV_ATTACHED,                 /* the host device attached state definition */
    HOST_DEV_DETACHED,                 /* the host device detached state definition */
    HOST_DETECT_DEV_SPEED,             /* the host detect device speed state definition */
    HOST_ENUMERATION,                  /* the host enumeration state definition */
    HOST_CLASS_REQUEST,                /* the host class request state definition */
    HOST_CLASS,                        /* the host class state definition */
    HOST_USER_INPUT,                   /* the host user input state definition */
    HOST_SUSPENDED,                    /* the host suspended state definition */
    HOST_ERROR                         /* the host error state definition */
}host_state_enum;

/* the enum of host event */
typedef enum 
{
    HOST_EVENT_ATTACHED = 0,           /* the host attached event */
    HOST_EVENT_ENUM,                   /* the host enum event */
    HOST_EVENT_USER_INPUT,             /* the host user input event */
    HOST_EVENT_CLASS_REQ,              /* the host class request event */
    HOST_EVENT_CLASS,                  /* the host class event */
    HOST_EVENT_ERROR,                  /* the host error event */
    HOST_EVENT_DEV_DETACHED,           /* the host device detached event */
    HOST_EVENT_IDLE                    /* the host idle event */
}host_event_enum;

/* the enum of enum state */
typedef enum
{
    ENUM_IDLE = 0,                     /* the enum idle state definition */
    ENUM_SET_ADDR,                     /* the enum set address state definition */
    ENUM_GET_FULL_DEV_DESC,            /* the enum get full device descripter state definition */
    ENUM_GET_CFG_DESC,                 /* the enum get configuration descripter state definition */
    ENUM_GET_FULL_CFG_DESC,            /* the enum get full configuration descripter state definition */
    ENUM_GET_MFC_STRING_DESC,          /* the enum get MFC string descripter state definition */
    ENUM_GET_PRODUCT_STRING_DESC,      /* the enum get product string descripter state definition */
    ENUM_GET_SERIALNUM_STRING_DESC,    /* the enum get serialnum string descripter state definition */
    ENUM_SET_CONFIGURATION,            /* the enum set congiguration state definition */
    ENUM_DEV_CONFIGURED                /* the enum device configuration state definition */
}enum_state_enum;

/* the enum of ctrl state */
typedef enum 
{
    CTRL_IDLE = 0,                     /* the ctrl idle state definition */
    CTRL_SETUP,                        /* the ctrl setup state definition */
    CTRL_DATA,                         /* the ctrl data state definition */
    CTRL_STATUS,                       /* the ctrl status state definition */
    CTRL_ERROR,                        /* the ctrl error state definition */
    CTRL_STALLED,                      /* the ctrl stalled state definition */
    CTRL_COMPLETE                      /* the ctrl complete state definition */
}ctrl_state_enum;

/* the enum of host status */
typedef enum 
{
    USBH_OK = 0,                       /* the usbh ok status definition */
    USBH_BUSY,                         /* the usbh busy status definition */
    USBH_FAIL,                         /* the usbh fail status definition */
    USBH_NOT_SUPPORTED,                /* the usbh not supported status definition */
    USBH_UNRECOVERED_ERROR,            /* the usbh unrecovered error status definition */
    USBH_SPEED_UNKNOWN_ERROR,          /* the usbh speed unknown error status definition */
    USBH_APPLY_DEINIT                  /* the usbh apply deinit status definition */
}usbh_status_enum;

/* the state of user action */
typedef enum 
{
    USBH_USER_NO_RESP = 0,             /* the user no response */
    USBH_USER_RESP_OK = 1,             /* the user response ok */
}usbh_user_status_enum;

/* control transfer information */
typedef struct
{
    uint8_t               hc_in_num;   /* the host in channel number */
    uint8_t               hc_out_num;  /* the host out channel number */
    uint8_t               ep0_size;    /* the endpoint 0 max packet size */
    uint8_t               error_count; /* the error count */
    uint16_t              length;      /* the length */
    uint16_t              timer;       /* the timer */
    uint8_t              *buff;        /* the buffer */
    usb_setup_union       setup;       /* the setup packet */
}usbh_ctrl_struct;

/* device property */
typedef struct
{
    uint8_t                              address;                                           /* the device address */
    uint8_t                              speed;                                             /* the device speed */
    usb_descriptor_device_struct         dev_desc;                                          /* the device descripter */
    usb_descriptor_configuration_struct  cfg_desc;                                          /* the configuration descripter */
    usb_descriptor_interface_struct      itf_desc[USBH_MAX_INTERFACES_NUM];                 /* the interface descripter */
    usb_descriptor_endpoint_struct       ep_desc[USBH_MAX_INTERFACES_NUM][USBH_MAX_EP_NUM]; /* the endpoint descripter */
}usbh_device_struct;

/* user callbacks */
typedef struct
{
    void (*init)                        (void);                 /* the user callback init function */
    void (*deinit)                      (void);                 /* the user callback deinit function */
    void (*device_connected)            (void);                 /* the user callback device connected function */
    void (*device_reset)                (void);                 /* the user callback device reset function */
    void (*device_disconnected)         (void);                 /* the user callback device disconnected function */
    void (*over_current_detected)       (void);                 /* the user callback over current detected function */
    void (*device_speed_detected)       (uint8_t device_speed);  /* the user callback device speed detected function */
    void (*device_desc_available)       (void *devDesc);        /* the user callback device descrpiter available function */
    void (*device_address_set)          (void);                 /* the user callback set device address function */

    void (*configuration_desc_available)(usb_descriptor_configuration_struct *cfg_desc,
                                         usb_descriptor_interface_struct *itf_desc,
                                         usb_descriptor_endpoint_struct *ep_desc);  
                                                                /* the configuration descripter available function */

    void (*manufacturer_string)         (void *mfc_string);      /* the user callback manufacturer string function */
    void (*product_string)              (void *prod_string);     /* the user callback product string function */
    void (*serial_num_string)           (void *serial_string);   /* the user callback serial number string function */
    void (*enumeration_finish)          (void);                 /* the user callback enumeration finish function */
    usbh_user_status_enum (*user_input) (void);                 /* the user callback user input function */
    int  (*user_application)            (usb_core_handle_struct *pudev, uint8_t id);          
                                                                /* the user callback user appliction function */
    void (*device_not_supported)        (void);                 /* the user callback device not supported function */
    void (*unrecovered_error)           (void);                 /* the user callback unrecovered error function */
}usbh_user_callback_struct;

/* the backup state struct */
typedef struct
{
    host_state_enum                      host_backup_state;     /* the host backup state */
    enum_state_enum                      enum_backup_state;     /* the enum backup state */
    ctrl_state_enum                      ctrl_backup_state;     /* the ctrl backup state */
    uint8_t                              class_req_backup_state;/* the class request backup state */
    uint8_t                              class_backup_state;    /* the class backup state */
} backup_state_struct;

/* host information */
typedef struct
{
    backup_state_struct                  usbh_backup_state;                            /* the usbh backup state variable */
    usbh_ctrl_struct                     control;                                      /* the control struct variable */
    usbh_device_struct                   device;                                       /* the device struct variable */
    usbh_user_callback_struct           *usr_cb;                                       /* the user callback function */
    usbh_status_enum (*class_init)      (usb_core_handle_struct *pudev, void *phost);  /* the class init function */
    void (*class_deinit)                (usb_core_handle_struct *pudev, void *phost);  /* the class deinit function */
}usbh_host_struct;

/* the action function definition */
typedef usbh_status_enum (*ACT_FUN)     (usb_core_handle_struct *pudev, usbh_host_struct *puhost, void* pustate);

/* the state table struct */
typedef struct 
{
    uint8_t                              cur_state;             /* the current state */
    uint8_t                              cur_event;             /* the current event */
    uint8_t                              next_state;            /* the next state */
    ACT_FUN                              event_action_fun;      /* the event action function entry */
} state_table_struct;

/* the state stack struct */
typedef struct
{
    uint8_t                              state;                 /* the state in state stack */
    state_table_struct*                  table;                 /* the table in state stack */
    uint8_t                              table_size;            /* the table size in state stack */
} usbh_state_stack_struct;

/* the state regist table struct */
typedef struct
{
    uint8_t                              id;                    /* the id of the state table */
    state_table_struct*                  table;                 /* the table entry to regist */
    uint8_t                              table_size;            /* the table size to regist */
} usbh_state_regist_table_struct;

/* the state handle struct */
typedef struct 
{
    uint8_t                              usbh_current_state;                                 /* current state */
    uint8_t                              usbh_current_state_table_size;                      /* current state table size */
    state_table_struct*                  usbh_current_state_table;                           /* current state table */
  
    usbh_state_stack_struct              stack[MAX_USBH_STATE_STACK_DEEP];                   /* the stack of state table */
    int8_t                               usbh_current_state_stack_top;                       /* the current state top */
  
    usbh_state_regist_table_struct       usbh_regist_state_table[MAX_USBH_STATE_TABLE_NUM];  /* the array of regist state table */
    uint8_t                              usbh_regist_state_table_num;                        /* the number of regist state table */
} usbh_state_handle_struct;

/* function declarations */
/* the host core driver function */
usbh_status_enum host_state_polling_fun (usb_core_handle_struct *pudev, usbh_host_struct *puhost, void *pustate);
/* initialize the host portion of the driver */
uint32_t  hcd_init (usb_core_handle_struct *pudev, usb_core_id_enum core_id);
/* check if the device is connected */
uint32_t  hcd_is_device_connected (usb_core_handle_struct *pudev);
/* this function returns the last URBstate */
urb_state_enum hcd_urb_state_get (usb_core_handle_struct *pudev, uint8_t channel_num);
/* this function returns the last URBstate */
uint32_t  hcd_xfer_count_get (usb_core_handle_struct *pudev, uint8_t channel_num);
/* de-initialize host */
usbh_status_enum usbh_deinit (usb_core_handle_struct *pudev, 
                              usbh_host_struct *puhost, 
                              usbh_state_handle_struct* pustate);

/* the state core driver function */
/* state core driver init */
void scd_init (usbh_state_handle_struct* pustate);
/* state core driver table regist */
void scd_table_regist (usbh_state_handle_struct* pustate, 
                       state_table_struct* pstate_table,
                       uint8_t table_id,
                       uint8_t current_table_size);
/* state core driver begin */
void scd_begin (usbh_state_handle_struct* pustate, uint8_t table_id);
/* state core driver move state */
void scd_state_move (usbh_state_handle_struct* pustate, uint8_t state);
/* state core driver event handle */
usbh_status_enum scd_event_handle (usb_core_handle_struct *pudev,
                                   usbh_host_struct *puhost,
                                   usbh_state_handle_struct* pustate,
                                   uint8_t event, 
                                   uint8_t state);
/* state core driver table push */
void scd_table_push (usbh_state_handle_struct* pustate);
/* state core driver table pop */
void scd_table_pop (usbh_state_handle_struct* pustate);
/* the function is only used to state move */
usbh_status_enum only_state_move (usb_core_handle_struct *pudev, usbh_host_struct *puhost, void *pustate);
/* the function to the up state */
usbh_status_enum goto_up_state_fun (usb_core_handle_struct *pudev, usbh_host_struct *puhost, void *pustate);

#endif /* USBH_CORE_H */
