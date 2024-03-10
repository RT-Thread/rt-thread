#ifndef _USB_BATT_CHG_H_
#define _USB_BATT_CHG_H_

#include "usbevent.h"

/* Public constants **********************************************************/
/* Debug options */
#define USB_BATT_CHG_DEBUG_ENABLE                           (FALSE)
#ifndef DEBUG_INFO_TRACE
  #define DEBUG_INFO_TRACE(x)                               printf("\n%s", x)
#endif

/* Clock speed value */
#define USB_BATT_CHG_CLOCK_SPEED                            (48)
#define USB_BATT_CHG_CLOCK_UNIT_MHZ                         (1)

/* Timeout definitions in msec. according to Battery charging specification rev 1.1 */
#define T_DCD_DBNC                                          (10)
#define T_VDPSRC_ON                                         (40)
#define T_VDPSRC_CON                                        (40)
//#define T_VDMSRC_EN                                         (20)
//#define T_VDMSRC_DIS                                        (20) 

/* Error status to be returned: invalid parameters */
#define USBERR_INVALID_PARAMETER                            (0x0C)

/* Battery charging states definitions */
#define USB_BATT_CHG_STATE_INIT                             (0x01)
#define USB_BATT_CHG_STATE_VBUS_DETECT                      (0x02)
#define USB_BATT_CHG_STATE_DATA_CONTACT_DETECT              (0x03)
#define USB_BATT_CHG_STATE_CHARGING_PORT_DETECT             (0x04)
#define USB_BATT_CHG_STATE_CHARGER_TYPE_DETECT              (0x05)
#define USB_BATT_CHG_STATE_TIMEOUT                          (0x06)
#define USB_BATT_CHG_STATE_COMPLETE                         (0x07)

/* Event definitions */
#define USB_BATT_CHG_EVENT_NO_EVENT                         (0x00)
#define USB_BATT_CHG_EVENT_PHASE_COMPLETE                   (0x01)
#define USB_BATT_CHG_EVENT_ERROR                            (0x02)
#define USB_BATT_CHG_EVENT_UNPLUGGED 						(0x04)

/* Module sequence states definition */
#define SEQ_STAT_INIT                                       (0)
#define SEQ_STAT_DATA_PIN_CONTACT_DETECTED                  (1)
#define SEQ_STAT_CHARGER_DETECTED                           (2)
#define SEQ_STAT_CHARGER_TYPE_DETECTED                      (3)

#define USBDCD_STATUS_SEQ_STAT_INIT                         (USBDCD_STATUS_SEQ_STAT(SEQ_STAT_INIT))
#define USBDCD_STATUS_SEQ_STAT_DATA_PIN_CONTACT_DETECTED    (USBDCD_STATUS_SEQ_STAT(SEQ_STAT_DATA_PIN_CONTACT_DETECTED))
#define USBDCD_STATUS_SEQ_STAT_CHARGER_DETECTED             (USBDCD_STATUS_SEQ_STAT(SEQ_STAT_CHARGER_DETECTED))
#define USBDCD_STATUS_SEQ_STAT_CHARGER_TYPE_DETECTED        (USBDCD_STATUS_SEQ_STAT(SEQ_STAT_CHARGER_TYPE_DETECTED))

/* USB port type definition */
#define USB_BATT_CHG_PORT_TYPE_NO_PORT 						(0)   /* Charger type: no port */
#define USB_BATT_CHG_PORT_TYPE_SDP                          (1)   /* Charge type: Standard Downstream Port (SDP) */
#define USB_BATT_CHG_PORT_TYPE_CDP                          (2)   /* Charge type: Charging Downstream Port (CDP) */
#define USB_BATT_CHG_PORT_TYPE_DCP                          (3)   /* Charge type: Dedicated Charging Port (DCP)  */

#define SEQ_RES_NO_PORT                                     (0)
#define SEQ_RES_STD_HOST                                    (1)
#define SEQ_RES_CHG_PORT                                    (2)
/* Sequence result after charging type phase */
#define SEQ_RES_CHG_HOST_PORT                               (2)
#define SEQ_RES_DED_CHG_PORT                                (3)

#define USBDCD_STATUS_SEQ_RES_STD_HOST                      (USBDCD_STATUS_SEQ_RES(SEQ_RES_STD_HOST))
#define USBDCD_STATUS_SEQ_RES_CHG_PORT                      (USBDCD_STATUS_SEQ_RES(SEQ_RES_CHG_PORT))
/* Sequence result after charging type phase */
#define USBDCD_STATUS_SEQ_RES_CHG_HOST_PORT                 (USBDCD_STATUS_SEQ_RES(SEQ_RES_CHG_HOST_PORT))
#define USBDCD_STATUS_SEQ_RES_DED_CHG_PORT                  (USBDCD_STATUS_SEQ_RES(SEQ_RES_DED_CHG_PORT))

/* Definitions of typical currents used in Battery Charging specification */
/* Note: except I_SUSP (unit: 100uA) all currents are in mA */
#define I_SUSP        (25)      /* Maximum current provided by a Standard Downstream Port (SDP) in suspend mode (allowed by USB 2.0 spec.) */
#define I_CONFIG      (500)     /* Maximum current provided by a SDP after configuration step (allowed by USB 2.0 spec.) */
#define I_DEV_DCHG    (1800)    /* Maximum output current drawn from a Dedicated Charging Port (DCP) */
#define I_DEV_CPD_LFS (1500)    /* Maximum output current drawn from a Charging Downstream Port (CDP) in low/full speed (LS/FS) */


/* Public types definitions **************************************************/
/* Functions types used to interface with the external battery charger or VBUS detect ICs */
typedef void    (*ext_enable_disable_func)(boolean enable); 
/* Function type definition for the VBUS detection status */
typedef boolean (*ext_vbus_det_get_status)(void);

/* Battery charging specific event type definition */
typedef uint_32   USB_BATT_CHG_EVENT;
 
/* Battery charging timing structure type definition */
typedef struct ubs_batt_chg_timings
{
  uint_16                   time_dcd_dbnc;
  uint_16                   time_vdpsrc_on;
  uint_16                   time_vdpsrc_con;
  uint_16                   time_seq_init; 
  uint_8                    time_check_d_minus;
    
} USB_BATT_CHG_TIMINGS;

/* Battery charging init struct type definitions */
typedef struct usb_batt_chg_init_struct
{
  /* External VBUS Detection IC */
  boolean                   ext_vbus_detect_circuit_use;
#ifdef __GNUC__
  uint_8 					          reserve[3];
#endif
  ext_enable_disable_func   ext_vbus_detect_enable_disable_func;
  ext_vbus_det_get_status   ext_vbus_detect_update_vbus_status_func;
  /* External Battery Charging Monitor IC */                                                                                 
  boolean                   ext_batt_chg_circuit_use;
#ifdef __GNUC__
  uint_8 				            reserve1[3];
#endif
  ext_enable_disable_func   ext_batt_chg_circuit_enable_disable_func;
  
  /* Battery charging timings to be configured */
  /* 
     NOTE: if any of these times is not according to 'Battery Charging Specification' 
     rev. 1.1 it will be ignored and the default HW register value is kept 
  */
  USB_BATT_CHG_TIMINGS      usb_batt_chg_timings_config;

} USB_BATT_CHG_INIT_STRUCT;

/* Battery charging error type enumeration */
typedef enum
{
  no_error                = 0,
  error_seq_timeout,
  error_unknown_port_type
} error_type_t;

/* Battery charging status type definition */
typedef struct usb_batt_chg_status
{
  uint_32         dev_state;
  boolean         vbus_valid;
  uint_32         charger_type;  
  boolean         data_pin_det;
  error_type_t    error_type;  

} USB_BATT_CHG_STATUS;

/* Application callback function type definition */
typedef void (*usb_batt_chg_callback)(USB_BATT_CHG_EVENT event, const USB_BATT_CHG_STATUS* app_bat_chg_status_ptr);

/* Battery charging struct type definition */
typedef struct usb_batt_chg_stuct
{     
  /* Application initalization structure that containing also the external circuit functions */
  USB_BATT_CHG_INIT_STRUCT  usb_batt_chg_init;   
  /* An interrupt from the external VBUS detect circuit */
  uint_8                    pending_vbus_det_ext_isr;  
  /* Battery charger event notification: passed to the application via registered callback */
  USB_EVENT_STRUCT          usb_batt_chg_event; 
  /* Battery charger status structure: used to be passed to the application */
  USB_BATT_CHG_STATUS       usb_batt_chg_status;
  /* Battery charging application callback function */
#ifdef __GNUC__
  uint_8 					reserve[2];
#endif
  usb_batt_chg_callback     app_callback;
    
} USB_BATT_CHG_STRUCT;
 

/* Public functions **********************************************************/
extern uint_32  _usb_batt_chg_init(USB_BATT_CHG_INIT_STRUCT* init_struct); 
extern uint_32  _usb_batt_chg_uinit(void);
extern uint_32  _usb_batt_chg_register_callback(usb_batt_chg_callback callback);
extern void     _usb_batt_chg_ext_isr(void);
extern void     _usb_batt_chg_task(void);
#if (defined __MK_xxx_H__)
	extern void USBDCD_ISR(void);
#elif (defined MCU_mcf51jf128)
	extern void interrupt VectorNumber_Vusbdcd USBDCD_ISR(void);
#endif 
	
#endif /* _USB_BATT_CHG_H_*/
