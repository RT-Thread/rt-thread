/**************************************************************************//**
 * @file     usbh_lib.h
 * @version  V1.10
 * @brief    USB Host library exported header file.
 *
 * @note
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2019-2020 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef  _USBH_LIB_H_
#define  _USBH_LIB_H_

#include "NuMicro.h"

#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup LIBRARY Library
  @{
*/

/** @addtogroup USBH_Library USB Host Library
  @{
*/

/** @addtogroup USBH_EXPORTED_CONSTANTS USB Host Exported Constants
  @{
*/

#define USBH_OK                     0      /*!< No error.                                       */
#define USBH_ERR_MEMORY_OUT         -10    /*!< Out of memory.                                  */
#define USBH_ERR_IF_ALT_LIMIT       -11    /*!< Number of alternative interface > MAX_ALT_PER_IFACE */
#define USBH_ERR_IF_EP_LIMIT        -15    /*!< Number of endpoints > MAX_EP_PER_IFACE          */
#define USBH_ERR_NOT_SUPPORTED      -101   /*!< Device/Class/Transfer not supported             */
#define USBH_ERR_NOT_MATCHED        -103   /*!< Not macthed                                     */
#define USBH_ERR_NOT_EXPECTED       -104   /*!< Unknown or unexpected                           */
#define USBH_ERR_INVALID_PARAM      -105   /*!< Invalid parameter                               */
#define USBH_ERR_NOT_FOUND          -106   /*!< Device or interface not found                   */
#define USBH_ERR_EP_NOT_FOUND       -107   /*!< Endpoint not found                              */
#define USBH_ERR_DESCRIPTOR         -137   /*!< Failed to parse USB descriptors                 */
#define USBH_ERR_SET_DEV_ADDR       -139   /*!< Failed to set device address                    */
#define USBH_ERR_SET_CONFIG         -151   /*!< Failed to set device configuration              */

#define USBH_ERR_TRANSFER           -201   /*!< USB transfer error                              */
#define USBH_ERR_TIMEOUT            -203   /*!< USB transfer time-out                           */
#define USBH_ERR_ABORT              -205   /*!< USB transfer aborted due to disconnect or reset */
#define USBH_ERR_PORT_RESET         -255   /*!< Hub port reset failed                           */
#define USBH_ERR_SCH_OVERRUN        -257   /*!< USB isochronous schedule overrun                */
#define USBH_ERR_DISCONNECTED       -259   /*!< USB device was disconnected                     */

#define USBH_ERR_TRANSACTION        -271   /*!< USB transaction timeout, CRC, Bad PID, etc.     */
#define USBH_ERR_BABBLE_DETECTED    -272   /*!< A ¡§babble¡¨ is detected during the transaction   */
#define USBH_ERR_DATA_BUFF          -274   /*!< Data buffer overrun or underrun                 */

#define USBH_ERR_CC_NO_ERR          -280   /*!< OHCI CC code - no error                         */
#define USBH_ERR_CRC                -281   /*!< USB trasfer CRC error                           */
#define USBH_ERR_BIT_STUFF          -282   /*!< USB transfer bit stuffing error                 */
#define USBH_ERR_DATA_TOGGLE        -283   /*!< USB trasfer data toggle error                   */
#define USBH_ERR_STALL              -284   /*!< USB trasfer STALL error                         */
#define USBH_ERR_DEV_NO_RESP        -285   /*!< USB trasfer device no response error            */
#define USBH_ERR_PID_CHECK          -286   /*!< USB trasfer PID check failure                   */
#define USBH_ERR_UNEXPECT_PID       -287   /*!< USB trasfer unexpected PID error                */
#define USBH_ERR_DATA_OVERRUN       -288   /*!< USB trasfer data overrun error                  */
#define USBH_ERR_DATA_UNDERRUN      -289   /*!< USB trasfer data underrun error                 */
#define USBH_ERR_BUFF_OVERRUN       -292   /*!< USB trasfer buffer overrun error                */
#define USBH_ERR_BUFF_UNDERRUN      -293   /*!< USB trasfer buffer underrun error               */
#define USBH_ERR_NOT_ACCESS0        -294   /*!< USB trasfer not accessed error                  */
#define USBH_ERR_NOT_ACCESS1        -295   /*!< USB trasfer not accessed error                  */

#define USBH_ERR_OHCI_INIT          -301   /*!< Failed to initialize OHIC controller.           */
#define USBH_ERR_OHCI_EP_BUSY       -303   /*!< The endpoint is under transfer.                 */

#define USBH_ERR_EHCI_INIT          -501   /*!< Failed to initialize EHCI controller.           */
#define USBH_ERR_EHCI_QH_BUSY       -503   /*!< the Queue Head is busy.                         */

#define UMAS_OK                     0      /*!< No error.                                       */
#define UMAS_ERR_NO_DEVICE          -1031  /*!< No Mass Stroage Device found.                   */
#define UMAS_ERR_IO                 -1033  /*!< Device read/write failed.                       */
#define UMAS_ERR_INIT_DEVICE        -1035  /*!< failed to init MSC device                       */
#define UMAS_ERR_CMD_STATUS         -1037  /*!< SCSI command status failed                      */
#define UMAS_ERR_IVALID_PARM        -1038  /*!< Invalid parameter.                              */
#define UMAS_ERR_DRIVE_NOT_FOUND    -1039  /*!< drive not found                                 */

#define HID_RET_OK                  0      /*!< Return with no errors.                          */
#define HID_RET_DEV_NOT_FOUND       -1081  /*!< HID device not found or removed.                */
#define HID_RET_IO_ERR              -1082  /*!< USB transfer failed.                            */
#define HID_RET_INVALID_PARAMETER   -1083  /*!< Invalid parameter.                              */
#define HID_RET_OUT_OF_MEMORY       -1084  /*!< Out of memory.                                  */
#define HID_RET_NOT_SUPPORTED       -1085  /*!< Function not supported.                         */
#define HID_RET_EP_NOT_FOUND        -1086  /*!< Endpoint not found.                             */
#define HID_RET_PARSING             -1087  /*!< Failed to parse HID descriptor                  */
#define HID_RET_XFER_IS_RUNNING     -1089  /*!< The transfer has been enabled.                  */
#define HID_RET_REPORT_NOT_FOUND    -1090  /*!< The transfer has been enabled.                  */

#define UAC_RET_OK                   0     /*!< Return with no errors.                          */
#define UAC_RET_DEV_NOT_FOUND       -2001  /*!< Audio Class device not found or removed.        */
#define UAC_RET_FUNC_NOT_FOUND      -2002  /*!< Audio device has no this function.              */
#define UAC_RET_IO_ERR              -2003  /*!< USB transfer failed.                            */
#define UAC_RET_DATA_LEN            -2004  /*!< Unexpected transfer length                      */
#define UAC_RET_INVALID             -2005  /*!< Invalid parameter or usage.                     */
#define UAC_RET_OUT_OF_MEMORY       -2007  /*!< Out of memory.                                  */
#define UAC_RET_DRV_NOT_SUPPORTED   -2009  /*!< Function not supported by this UAC driver.      */
#define UAC_RET_DEV_NOT_SUPPORTED   -2011  /*!< Function not supported by the UAC device.       */
#define UAC_RET_PARSER              -2013  /*!< Failed to parse UAC descriptor                  */
#define UAC_RET_IS_STREAMING        -2015  /*!< Audio pipe is on streaming.                     */


/*@}*/ /* end of group USBH_EXPORTED_CONSTANTS */


/** @addtogroup USBH_EXPORTED_TYPEDEF USB Host Typedef
  @{
*/
struct udev_t;
typedef void (CONN_FUNC)(struct udev_t *udev, int param);

struct line_coding_t;
struct cdc_dev_t;
typedef void (CDC_CB_FUNC)(struct cdc_dev_t *cdev, uint8_t *rdata, int data_len);

struct usbhid_dev;
typedef void (HID_IR_FUNC)(struct usbhid_dev *hdev, uint16_t ep_addr, int status, uint8_t *rdata, uint32_t data_len);    /*!< interrupt in callback function \hideinitializer */
typedef void (HID_IW_FUNC)(struct usbhid_dev *hdev, uint16_t ep_addr, int status, uint8_t *wbuff, uint32_t *data_len);   /*!< interrupt out callback function \hideinitializer */

struct uac_dev_t;
typedef int (UAC_CB_FUNC)(struct uac_dev_t *dev, uint8_t *data, int len);    /*!< audio in callback function \hideinitializer */

/*@}*/ /* end of group USBH_EXPORTED_STRUCT */



/** @addtogroup USBH_EXPORTED_FUNCTIONS USB Host Exported Functions
  @{
*/

/*------------------------------------------------------------------*/
/*                                                                  */
/*  USB Core Library APIs                                           */
/*                                                                  */
/*------------------------------------------------------------------*/
extern void usbh_core_init(void);
extern int  usbh_polling_root_hubs(void);
extern void usbh_install_conn_callback(CONN_FUNC *conn_func, CONN_FUNC *disconn_func);
extern void usbh_suspend(void);
extern void usbh_resume(void);
extern struct udev_t * usbh_find_device(char *hub_id, int port);
/**
 * @brief  A function return current tick count.
 * @return Current tick.
 * @details User application must provide this function to return current tick.
 *          The tick should increase by 1 for every 10 ms.
 */
extern uint32_t usbh_get_ticks(void);   /* This function must be provided by user application. */
extern uint32_t usbh_tick_from_millisecond(uint32_t msec);   /* This function must be provided by user application. */

/*------------------------------------------------------------------*/
/*                                                                  */
/*  USB Communication Device Class Library APIs                     */
/*                                                                  */
/*------------------------------------------------------------------*/
extern void     usbh_cdc_init(void);
extern struct cdc_dev_t * usbh_cdc_get_device_list(void);
/// @cond HIDDEN_SYMBOLS
extern int32_t  usbh_cdc_get_line_coding(struct cdc_dev_t *cdev, struct line_coding_t *line_code);
extern int32_t  usbh_cdc_set_line_coding(struct cdc_dev_t *cdev, struct line_coding_t *line_code);
/// @endcond HIDDEN_SYMBOLS
extern int32_t  usbh_cdc_set_control_line_state(struct cdc_dev_t *cdev, int active_carrier, int DTE_present);
extern int32_t  usbh_cdc_start_polling_status(struct cdc_dev_t *cdev, CDC_CB_FUNC *func);
extern int32_t  usbh_cdc_start_to_receive_data(struct cdc_dev_t *cdev, CDC_CB_FUNC *func);
extern int32_t  usbh_cdc_send_data(struct cdc_dev_t *cdev, uint8_t *buff, int buff_len);


/*------------------------------------------------------------------*/
/*                                                                  */
/*  USB Human Interface Class Library APIs                          */
/*                                                                  */
/*------------------------------------------------------------------*/
extern void     usbh_hid_init(void);
extern struct usbhid_dev * usbh_hid_get_device_list(void);
extern int32_t  usbh_hid_get_report_descriptor(struct usbhid_dev *hdev, uint8_t *desc_buf, int buf_max_len);
extern int32_t  usbh_hid_get_report(struct usbhid_dev *hdev, int rtp_typ, int rtp_id, uint8_t *data, int len);
extern int32_t  usbh_hid_set_report(struct usbhid_dev *hdev, int rtp_typ, int rtp_id, uint8_t *data, int len);
extern int32_t  usbh_hid_get_idle(struct usbhid_dev *hdev, int rtp_id, uint8_t *idle_rate);
extern int32_t  usbh_hid_set_idle(struct usbhid_dev *hdev, int rtp_id, uint8_t idle_rate);
extern int32_t  usbh_hid_get_protocol(struct usbhid_dev *hdev, uint8_t *protocol);
extern int32_t  usbh_hid_set_protocol(struct usbhid_dev *hdev, uint8_t protocol);
extern int32_t  usbh_hid_start_int_read(struct usbhid_dev *hdev, uint8_t ep_addr, HID_IR_FUNC *func);
extern int32_t  usbh_hid_stop_int_read(struct usbhid_dev *hdev, uint8_t ep_addr);
extern int32_t  usbh_hid_start_int_write(struct usbhid_dev *hdev, uint8_t ep_addr, HID_IW_FUNC *func);
extern int32_t  usbh_hid_stop_int_write(struct usbhid_dev *hdev, uint8_t ep_addr);

/*------------------------------------------------------------------*/
/*                                                                  */
/*  USB Mass Storage Class Library APIs                             */
/*                                                                  */
/*------------------------------------------------------------------*/
extern int  usbh_umas_init(void);
extern int  usbh_umas_disk_status(int drv_no);
extern int  usbh_umas_read(int drv_no, uint32_t sec_no, int sec_cnt, uint8_t *buff);
extern int  usbh_umas_write(int drv_no, uint32_t sec_no, int sec_cnt, uint8_t *buff);
extern int  usbh_umas_ioctl(int drv_no, int cmd, void *buff);
/// @cond HIDDEN_SYMBOLS
extern int  usbh_umas_reset_disk(int drv_no);
/// @endcond HIDDEN_SYMBOLS
/*------------------------------------------------------------------*/
/*                                                                  */
/*  USB Audio Class Library APIs                                    */
/*                                                                  */
/*------------------------------------------------------------------*/
extern void usbh_uac_init(void);
extern int usbh_uac_open(struct uac_dev_t *audev);
extern struct uac_dev_t * usbh_uac_get_device_list(void);
extern int usbh_uac_get_channel_number(struct uac_dev_t *audev, uint8_t target);
extern int usbh_uac_get_bit_resolution(struct uac_dev_t *audev, uint8_t target, uint8_t *byte_cnt);
extern int usbh_uac_get_sampling_rate(struct uac_dev_t *audev, uint8_t target, uint32_t *srate_list, int max_cnt, uint8_t *type);
extern int usbh_uac_sampling_rate_control(struct uac_dev_t *audev, uint8_t target, uint8_t req, uint32_t *srate);
extern int usbh_uac_mute_control(struct uac_dev_t *audev, uint8_t target, uint8_t req, uint16_t chn, uint8_t *mute);
extern int usbh_uac_vol_control(struct uac_dev_t *audev, uint8_t target, uint8_t req, uint16_t chn, uint16_t *volume);
extern int usbh_uac_auto_gain_control(struct uac_dev_t *audev, uint8_t target, uint8_t req, uint16_t chn, uint8_t *bAGC);
extern int usbh_uac_start_audio_in(struct uac_dev_t *uac, UAC_CB_FUNC *func);
extern int usbh_uac_stop_audio_in(struct uac_dev_t *audev);
extern int usbh_uac_start_audio_out(struct uac_dev_t *uac, UAC_CB_FUNC *func);
extern int usbh_uac_stop_audio_out(struct uac_dev_t *audev);


/// @cond HIDDEN_SYMBOLS

extern void dump_ohci_regs(void);
extern void dump_ehci_regs(void);
extern void dump_ohci_ports(void);
extern void dump_ehci_ports(void);
extern uint32_t  usbh_memory_used(void);

/// @endcond HIDDEN_SYMBOLS


/*@}*/ /* end of group USBH_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group USBH_Library */

/*@}*/ /* end of group LIBRARY */

#ifdef __cplusplus
}
#endif

#endif  /* _USBH_LIB_H_ */

/*** (C) COPYRIGHT 2019-2020 Nuvoton Technology Corp. ***/



