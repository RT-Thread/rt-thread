/**
  **************************************************************************
  * @file     usbh_core.h
  * @brief    usb host core header file
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

/* define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBH_CORE_H
#define __USBH_CORE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "usb_std.h"

/** @addtogroup USBH_drivers_core
  * @{
  */

/** @defgroup USBH_core_exported_types
  * @{
  */

#ifdef USE_OTG_HOST_MODE

/**
  * @brief usb channel flag
  */
typedef enum
{
  HCH_IDLE,           /*!< usb host channel idle */
  HCH_XFRC,           /*!< usb host channel transfer completed */
  HCH_HALTED,         /*!< usb host channel halted */
  HCH_NAK,            /*!< usb host channel nak */
  HCH_NYET,           /*!< usb host channel nyet */
  HCH_STALL,          /*!< usb host channel stall */
  HCH_XACTERR,        /*!< usb host channel transaction error */
  HCH_BBLERR,         /*!< usb host channel babble error */
  HCH_DATATGLERR      /*!< usb host channel data toggle error */
} hch_sts_type;

/**
  * @brief usb channel state
  */
typedef enum
{
  URB_IDLE = 0,    /*!< usb request idle state */
  URB_DONE,        /*!< usb request done state */
  URB_NOTREADY,    /*!< usb request not ready state */
  URB_NYET,        /*!< usb request nyet stat e*/
  URB_ERROR,       /*!< usb request error state */
  URB_STALL        /*!< usb request stall state */
} urb_sts_type;

/**
  * @brief usb control channel flag
  */
typedef enum
{
  CTRL_START = 0,      /*!< usb control request start */
  CTRL_XFERC,          /*!< usb control request completed */
  CTRL_HALTED,         /*!< usb control request halted */
  CTRL_NAK,            /*!< usb control request nak */
  CTRL_STALL,          /*!< usb control request stall */
  CTRL_XACTERR,        /*!< usb control request transaction error */
  CTRL_BBLERR,         /*!< usb control request babble error */
  CTRL_DATATGLERR,     /*!< usb control request data toggle error */
  CTRL_FAIL            /*!< usb control request failed */
} ctrl_sts_type;

/**
  * @brief usb host control state machine
  */
typedef enum
{
  CONTROL_IDLE,              /*!< usb control state idle */
  CONTROL_SETUP,             /*!< usb control state setup */
  CONTROL_SETUP_WAIT,        /*!< usb control state setup wait */
  CONTROL_DATA_IN,           /*!< usb control state data in */
  CONTROL_DATA_IN_WAIT,      /*!< usb control state data in wait */
  CONTROL_DATA_OUT,          /*!< usb control state data out */
  CONTROL_DATA_OUT_WAIT,     /*!< usb control state data out wait */
  CONTROL_STATUS_IN,         /*!< usb control state status in */
  CONTROL_STATUS_IN_WAIT,    /*!< usb control state status in wait */
  CONTROL_STATUS_OUT,        /*!< usb control state out */
  CONTROL_STATUS_OUT_WAIT,   /*!< usb control state out wait */
  CONTROL_ERROR,             /*!< usb control state error */
  CONTROL_STALL,             /*!< usb control state stall */
  CONTROL_COMPLETE           /*!< usb control state complete */
} ctrl_ept0_sts_type;

/**
  * @brief usb host enumration state machine
  */
typedef enum
{
  ENUM_IDLE,                             /*!< usb host enumration state idle */
  ENUM_GET_MIN_DESC,                     /*!< usb host enumration state get descriptor 8 byte*/
  ENUM_GET_FULL_DESC,                    /*!< usb host enumration state get descriptor 18 byte*/
  ENUM_SET_ADDR,                         /*!< usb host enumration state set address */
  ENUM_GET_CFG,                          /*!< usb host enumration state get configuration */
  ENUM_GET_FULL_CFG,                     /*!< usb host enumration state get full configuration  */
  ENUM_GET_MFC_STRING,                   /*!< usb host enumration state get manufacturer string */
  ENUM_GET_PRODUCT_STRING,               /*!< usb host enumration state get product string */
  ENUM_GET_SERIALNUM_STRING,             /*!< usb host enumration state get serial number string */
  ENUM_SET_CONFIG,                       /*!< usb host enumration state set config */
  ENUM_COMPLETE,                         /*!< usb host enumration state complete */
} usbh_enum_sts_type;

/**
  * @brief usb host global state machine
  */
typedef enum
{
  USBH_IDLE,                            /*!< usb host global state idle */
  USBH_PORT_EN,                         /*!< usb host global state port enable */
  USBH_ATTACHED,                        /*!< usb host global state attached */
  USBH_DISCONNECT,                      /*!< usb host global state disconnect */
  USBH_DEV_SPEED,                       /*!< usb host global state device speed */
  USBH_ENUMERATION,                     /*!< usb host global state enumeration */
  USBH_CLASS_REQUEST,                   /*!< usb host global state class request */
  USBH_CLASS,                           /*!< usb host global state class */
  USBH_CTRL_XFER,                       /*!< usb host global state control transfer */
  USBH_USER_HANDLER,                    /*!< usb host global state user handler */
  USBH_SUSPEND,                         /*!< usb host global state suspend */
  USBH_SUSPENDED,                       /*!< usb host have in suspend mode */
  USBH_WAKEUP,                          /*!< usb host global state wakeup */
  USBH_UNSUPPORT,                       /*!< usb host global unsupport device */
  USBH_ERROR_STATE,                     /*!< usb host global state error */
} usbh_gstate_type;

/**
  * @brief usb host transfer state
  */
typedef enum
{
  CMD_IDLE,               /*!< usb host transfer state idle */
  CMD_SEND,               /*!< usb host transfer state send */
  CMD_WAIT                /*!< usb host transfer state wait */
} cmd_sts_type;

/**
  * @brief usb host channel malloc state
  */
#define HCH_OK                           0x0000      /*!< usb channel malloc state ok */
#define HCH_USED                         0x8000      /*!< usb channel had used  */
#define HCH_ERROR                        0xFFFF      /*!< usb channel error */
#define HCH_USED_MASK                    0x7FFF      /*!< usb channel use mask */

/**
  * @brief  channel pid
  */
#define HCH_PID_DATA0                    0           /*!< usb channel pid data 0 */
#define HCH_PID_DATA2                    1           /*!< usb channel pid data 2 */
#define HCH_PID_DATA1                    2           /*!< usb channel pid data 1 */
#define HCH_PID_SETUP                    3           /*!< usb channel pid setup */

/**
  * @brief channel data transfer direction
  */
#define  USB_REQUEST_DIR_MASK            0x80             /*!< usb request direction mask */
#define  USB_DIR_H2D                     USB_REQ_DIR_HTD  /*!< usb request direction host to device */
#define  USB_DIR_D2H                     USB_REQ_DIR_DTH  /*!< usb request direction device to host */

/**
  * @brief request timeout
  */
#define DATA_STAGE_TIMEOUT               5000    /*!< usb data stage timeout */
#define NODATA_STAGE_TIMEOUT             50      /*!< usb no-data stage timeout */

/**
  * @brief max interface and endpoint
  */
#define USBH_MAX_ERROR_COUNT             2   /*!< usb support maximum error */
#define USBH_MAX_INTERFACE               5   /*!< usb support maximum interface */
#define USBH_MAX_ENDPOINT                5   /*!< usb support maximum endpoint */

/**
  * @brief interface descriptor
  */
typedef struct
{
  usb_interface_desc_type                interface;                      /*!< usb device interface descriptor structure */
  usb_endpoint_desc_type                 endpoint[USBH_MAX_ENDPOINT];    /*!< usb device endpoint descriptor structure array */
} usb_itf_desc_type;

/**
  * @brief configure descriptor
  */
typedef struct
{
  usb_configuration_desc_type            cfg;                            /*!< usb device configuration descriptor structure */
  usb_itf_desc_type                      interface[USBH_MAX_INTERFACE];  /*!< usb device interface descriptor structure array*/
} usb_cfg_desc_type;

/**
  * @brief device descriptor
  */
typedef struct
{
  uint8_t                                address;                        /*!< usb device address */
  uint8_t                                speed;                          /*!< usb device speed */
  usb_device_desc_type                   dev_desc;                       /*!< usb device descriptor */
  usb_cfg_desc_type                      cfg_desc;                       /*!< usb device configuration */
} usbh_dev_desc_type;

/**
  * @brief usb host control struct type
  */
typedef struct
{
  uint8_t                                hch_in;                         /*!< in channel number */
  uint8_t                                hch_out;                        /*!< out channel number */
  uint8_t                                ept0_size;                      /*!< endpoint 0 size */
  uint8_t                                *buffer;                        /*!< endpoint 0 transfer buffer */
  usb_setup_type                         setup;                          /*!< control setup type */
  uint16_t                               len;                            /*!< transfer length */
  uint8_t                                err_cnt;                        /*!< error counter */
  uint32_t                               timer;                          /*!< transfer timer */
  ctrl_sts_type                          sts;                            /*!< control transfer status */
  ctrl_ept0_sts_type                     state;                          /*!< endpoint 0 state */
} usbh_ctrl_type;

/**
  * @brief host class handler type
  */
typedef struct
{
  usb_sts_type (*init_handler)(void *uhost);                             /*!< usb host class init handler */
  usb_sts_type (*reset_handler)(void *uhost);                            /*!< usb host class reset handler */
  usb_sts_type (*request_handler)(void *uhost);                          /*!< usb host class request handler */
  usb_sts_type (*process_handler)(void *uhost);                          /*!< usb host class process handler */
  void *pdata;                                                           /*!< usb host class data */
} usbh_class_handler_type;

/**
  * @brief host user handler type
  */
typedef struct
{
  usb_sts_type (*user_init)(void);                                       /*!< usb host user init handler */
  usb_sts_type (*user_reset)(void);                                      /*!< usb host user reset handler */
  usb_sts_type (*user_attached)(void);                                   /*!< usb host user attached handler */
  usb_sts_type (*user_disconnect)(void);                                 /*!< usb host user disconnect handler */
  usb_sts_type (*user_speed)(uint8_t speed);                             /*!< usb host user speed handler */
  usb_sts_type (*user_mfc_string)(void *);                               /*!< usb host user manufacturer string handler */
  usb_sts_type (*user_product_string)(void *);                           /*!< usb host user product string handler */
  usb_sts_type (*user_serial_string)(void *);                            /*!< usb host user serial handler */
  usb_sts_type (*user_enumeration_done)(void);                           /*!< usb host user enumeration done handler */
  usb_sts_type (*user_application)(void);                                /*!< usb host user application handler */
  usb_sts_type (*user_active_vbus)(void *uhost, confirm_state state);    /*!< usb host user active vbus */
  usb_sts_type (*user_not_support)(void);                                /*!< usb host user not support handler */
} usbh_user_handler_type;

/**
  * @brief host host core handler type
  */
typedef struct
{
  usb_reg_type                           *usb_reg;                       /*!< usb register pointer */

  uint8_t                                global_state;                   /*!< usb host global state machine */
  uint8_t                                enum_state;                     /*!< usb host enumeration state machine */
  uint8_t                                req_state;                      /*!< usb host request state machine */

  usbh_dev_desc_type                     dev;                            /*!< usb device descriptor */
  usbh_ctrl_type                         ctrl;                           /*!< usb host control transfer struct */

  usbh_class_handler_type                *class_handler;                 /*!< usb host class handler pointer */
  usbh_user_handler_type                 *user_handler;                  /*!< usb host user handler pointer */

  usb_hch_type                           hch[USB_HOST_CHANNEL_NUM];      /*!< usb host channel array */
  uint8_t                                rx_buffer[USB_MAX_DATA_LENGTH]; /*!< usb host rx buffer */

  uint32_t                               conn_sts;                       /*!< connect status */
  uint32_t                               port_enable;                    /*!< port enable status */
  uint32_t                               timer;                          /*!< sof timer */

  uint32_t                               err_cnt[USB_HOST_CHANNEL_NUM];  /*!< error counter */
  uint32_t                               xfer_cnt[USB_HOST_CHANNEL_NUM]; /*!< xfer counter */
  hch_sts_type                           hch_state[USB_HOST_CHANNEL_NUM];/*!< channel state */
  urb_sts_type                           urb_state[USB_HOST_CHANNEL_NUM];/*!< usb request state */
  uint16_t                               channel[USB_HOST_CHANNEL_NUM];  /*!< channel array */

  void                                   *pdata;
} usbh_core_type;


void usbh_free_channel(usbh_core_type *uhost, uint8_t index);
uint16_t usbh_get_free_channel(usbh_core_type *uhost);
usb_sts_type usbh_set_toggle(usbh_core_type *uhost, uint8_t hc_num, uint8_t toggle);
usb_sts_type usbh_in_out_request(usbh_core_type *uhost, uint8_t hc_num);
usb_sts_type usbh_interrupt_recv(usbh_core_type *uhost, uint8_t hc_num,
                            uint8_t *buffer, uint16_t length);
usb_sts_type usbh_interrupt_send(usbh_core_type *uhost, uint8_t hc_num,
                            uint8_t *buffer, uint16_t length);
usb_sts_type usbh_bulk_recv(usbh_core_type *uhost, uint8_t hc_num,
                            uint8_t *buffer, uint16_t length);
usb_sts_type usbh_bulk_send(usbh_core_type *uhost, uint8_t hc_num,
                            uint8_t *buffer, uint16_t length);
usb_sts_type usbh_isoc_send(usbh_core_type *uhost, uint8_t hc_num,
                            uint8_t *buffer, uint16_t length);
usb_sts_type usbh_isoc_recv(usbh_core_type *uhost, uint8_t hc_num,
                            uint8_t *buffer, uint16_t length);
usb_sts_type usbh_cfg_default_init(usbh_core_type *uhost);
void usbh_enter_suspend(usbh_core_type *uhost);
void usbh_resume(usbh_core_type *uhost);

uint16_t usbh_alloc_channel(usbh_core_type *uhost, uint8_t ept_addr);
urb_sts_type usbh_get_urb_status(usbh_core_type *uhost, uint8_t ch_num);
usb_sts_type usbh_ctrl_result_check(usbh_core_type *uhost,
                                    ctrl_ept0_sts_type next_ctrl_state,
                                    uint8_t next_enum_state);
uint8_t usbh_alloc_address(void);
void usbh_reset_port(usbh_core_type *uhost);
usb_sts_type usbh_loop_handler(usbh_core_type *uhost);
void usbh_ch_disable(usbh_core_type *uhost, uint8_t chn);
void usbh_hc_open(usbh_core_type *uhost,
                   uint8_t chn,
                   uint8_t ept_num,
                   uint8_t dev_address,
                   uint8_t type,
                   uint16_t maxpacket,
                   uint8_t speed);
void usbh_active_vbus(usbh_core_type *uhost, confirm_state state);

usb_sts_type usbh_core_init(usbh_core_type *uhost,
                            usb_reg_type *usb_reg,
                            uint8_t core_id);

hch_sts_type usbh_get_status(usbh_core_type *uhost, uint8_t ch_num);

#endif


/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif
