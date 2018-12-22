/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2010 Freescale Semiconductor, Inc.
 * ALL RIGHTS RESERVED.
 *
 **************************************************************************//*!
 *
 * @file phdc_app.c
 *
 * @author
 *
 * @version
 *
 * @date May-28-2009
 *
 * @brief When the device is connected using continua manager it comes into
 *        operating state and now we can send measurements by pressing PTG1 key
 *        on the demo board
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "hidef.h"          /* for EnableInterrupts macro */
#include "derivative.h"     /* include peripheral declarations */
#include "types.h"          /* User Defined Data Types */
#include "phdc_app.h"       /* PHDC Application Header File */
#include "phd_com_model.h"  /* IEEE11073 Header File */
#include "realtimercounter.h"

/* skip the inclusion in dependency statge */
#ifndef __NO_SETJMP
   #include <stdio.h>
#endif
#include <stdlib.h>
#include <string.h>			

#if (defined _MCF51MM256_H) || (defined _MCF51JE256_H)
#include "exceptions.h"
#endif

#if (defined __MCF52xxx_H__)||(defined LITTLE_ENDIAN)
/* Put CFV2 hardcoded messages in RAM */
#define USB_CONST
#else
/* Const placement */
#define USB_CONST    const
#endif
/*****************************************************************************
 * Constant and Macro's - None
 *****************************************************************************/
/* association request to send */
uint_8 USB_CONST PHD_WSL_ASSOC_REQ[ASSOC_REQ_SIZE] = {
0xE2, 0x00,                         /* APDU CHOICE Type (AarqApdu) */
0x00, 0x32,                         /* CHOICE.length = 50 */
0x80, 0x00, 0x00, 0x00,             /* assoc-version */
0x00, 0x01, 0x00, 0x2A,             /* data-proto-list.count=1 | length=42*/
0x50, 0x79,                         /* data-proto-id = 20601 */
0x00, 0x26,                         /* data-proto-info length = 38 */
0x80, 0x00, 0x00, 0x00,             /* protocolVersion */
0x80, 0x00,                         /* encoding rules = MDER or PER */
0x80, 0x00, 0x00, 0x00,             /* nomenclatureVersion */
0x00, 0x00, 0x00, 0x00,             /* functionalUnits |
                                      no test association capabilities */
0x00, 0x80, 0x00, 0x00,             /* systemType = sys-type-agent */
0x00, 0x08,                         /* system-id length = 8 and value
    ,                                 (manufacturer- and device- specific) */
0x4C, 0x4E, 0x49, 0x41, 0x47, 0x45, 0x4E, 0x54,
0x40, 0x00,                         /* dev-config-id | extended configuration*/
0x00, 0x01,                         /* data-req-mode-flags */
0x01, 0x00,                         /* data-req-init-agent-count,
                                      data-req-init-manager-count */
0x00, 0x00, 0x00, 0x00              /* Atribute list */
};

/* configuration event report */
uint_8 USB_CONST PHD_WSL_CNFG_EVT_RPT[CNFG_EVT_RPT_SIZE] = {
0xE7, 0x00,                           /* APDU CHOICE Type (PrstApdu) */
0x00, 0xA2,                           /* CHOICE.length = 162 */
0x00, 0xA0,                           /* OCTET STRING.length = 160 */
0x00, 0x02,                           /*  invoke-id = 0x1235 (start of DataApdu
                                          . MDER encoded.) */
0x01, 0x01,                           /*  CHOICE(Remote Operation Invoke |
                                          Confirmed Event Report) */
0x00, 0x9A,                           /*  CHOICE.length = 154 */
0x00, 0x00,                           /*  obj-handle = 0 (MDS object) */
0xFF, 0xFF, 0xFF, 0xFF,               /*  event-time = 0xFFFFFFFF    */
0x0D, 0x1C,                           /*  event-type = MDC_NOTI_CONFIG */
0x00, 0x90,                           /*  event-info.length = 144 (start of
                                          ConfigReport) */
0x05, 0xDC,                           /*  config-report-id */
0x00, 0x03,                           /*  config-obj-list.count = 3 Measurement
                                          objects will be announced */
0x00, 0x8A,                           /*  config-obj-list.length = 138 */
0x00, 0x06,                           /*  obj-class = MDC_MOC_VMO_METRIC_NU */
0x00, 0x01,                           /*  obj-handle = 1 (.. 1st Measurement is
                                          body weight) */
0x00, 0x04,                           /*  attributes.count = 4  */
0x00, 0x24,                           /*  attributes.length = 36  */
0x09, 0x2F,                           /*  attribute-id = MDC_ATTR_ID_TYPE */
0x00, 0x04,                           /*  attribute-value.length = 4      */
0x00, 0x02, 0xE1, 0x40,               /*  0xE1 0x40 MDC_PART_SCADA |
                                          MDC_MASS_BODY_ACTUAL */
0x0A, 0x46,                           /*  attribute-id =
                                          MDC_ATTR_METRIC_SPEC_SMALL      */
0x00, 0x02,                           /*  attribute-value.length = 2  */
0xF0, 0x40,                           /*  intermittent, stored data, upd & msmt
                                          aperiodic, agent init, measured */
0x09, 0x96,                           /*  attribute-id = MDC_ATTR_UNIT_CODE */
0x00, 0x02,                           /*  attribute-value.length = 2 */
0x06, 0xC3,                           /*  MDC_DIM_KILO_G             */
0x0A, 0x55,                           /*  attribute-id =
                                          MDC_ATTR_ATTRIBUTE_VAL_MAP  */
0x00, 0x0C,                           /*  attribute-value.length = 12     */
0x00, 0x02,                           /*  AttrValMap.count = 2         */
0x00, 0x08,                           /*  AttrValMap.length = 8          */
0x0A, 0x56, 0x00, 0x04,               /*  MDC_ATTR_NU_VAL_OBS_SIMP |
                                          value length = 4   */
0x09, 0x90, 0x00, 0x08,               /*  MDC_ATTR_TIME_STAMP_ABS |
                                          value length = 8     */
0x00, 0x06,                           /*  obj-class = MDC_MOC_VMO_METRIC_NU */
0x00, 0x02,                           /*  obj-handle = 2 (..2nd Measurement
                                          is body height) */
0x00, 0x04,                           /*  attributes.count = 4   */
0x00, 0x24,                           /*  attributes.length = 36   */
0x09, 0x2F,                           /*  attribute-id = MDC_ATTR_ID_TYPE */
0x00, 0x04,                           /*  attribute-value.length = 4  */
0x00, 0x02, 0xE1, 0x44,               /*  MDC_PART_SCADA |
                                          MDC_LEN_BODY_ACTUAL */
0x0A, 0x46,                           /*  attribute-id =
                                          MDC_ATTR_METRIC_SPEC_SMALL   */
0x00, 0x02,                           /*  attribute-value.length = 2   */
0xF0, 0x48,                           /*  intermittent, stored data, upd & msmt
                                          aperiodic, agent init, manual */
0x09, 0x96,                           /*  attribute-id = MDC_ATTR_UNIT_CODE*/
0x00, 0x02,                           /*  attribute-value.length = 2*/
0x05, 0x11,                           /*  MDC_DIM_CENTI_M            */
0x0A, 0x55,                           /*  attribute-id =
                                          MDC_ATTR_ATTRIBUTE_VAL_MAP */
0x00, 0x0C,                           /*  attribute-value.length = 12 */
0x00, 0x02,                           /*  AttrValMap.count = 2*/
0x00, 0x08,                           /*  AttrValMap.length = 8*/
0x0A, 0x56, 0x00, 0x04,               /*  MDC_ATTR_NU_VAL_OBS_SIMP, 4 */
0x09, 0x90, 0x00, 0x08,               /*  MDC_ATTR_TIME_STAMP_ABS, 8 */
0x00, 0x06,                           /*  obj-class = MDC_MOC_VMO_METRIC_NU*/
0x00, 0x03,                           /*  obj-handle = 3 (..3rd Measurement
                                          is body mass index) */
0x00, 0x05,                           /*  attributes.count = 5*/
0x00, 0x2A,                           /*  attributes.length = 42*/
0x09, 0x2F,                           /*  attribute-id = MDC_ATTR_ID_TYPE */
0x00, 0x04,                           /*  attribute-value.length = 4 */
0x00, 0x02, 0xE1, 0x50,               /*  MDC_PART_SCADA |
                                          MDC_RATIO_MASS_BODY_LEN_SQ    */
0x0A, 0x46,                           /*  attribute-id =
                                          MDC_ATTR_METRIC_SPEC_SMALL       */
0x00, 0x02,                           /*  attribute-value.length = 2    */
0xF0, 0x42,                           /*  intermittent, stored data, upd &
                                      msmt aperiodic, agent init, calculated */
0x09, 0x96,                           /*  attribute-id = MDC_ATTR_UNIT_CODE*/
0x00, 0x02,                           /*  attribute-value.length = 2       */
0x07, 0xA0,                           /*  MDC_DIM_KG_PER_M_SQ               */
0x0A, 0x47,                           /*  attribute-id =
                                          MDC_ATTR_SOURCE_HANDLE_REF        */
0x00, 0x02,                           /*  attribute-value.length = 2 */
0x00, 0x01,                           /*  reference handle = 1         */
0x0A, 0x55,                           /*  attribute-id =
                                          MDC_ATTR_ATTRIBUTE_VAL_MAP*/
0x00, 0x0C,                           /*  attribute-value.length = 12  */
0x00, 0x02,                           /*  AttrValMap.count = 2          */
0x00, 0x08,                           /*  AttrValMap.length = 8         */
0x0A, 0x56, 0x00, 0x04,               /*  MDC_ATTR_NU_VAL_OBS_SIMP, 4   */
0x09, 0x90, 0x00, 0x08                /*  MDC_ATTR_TIME_STAMP_ABS, 8   */
};

/* release request to send */
uint_8 USB_CONST PHD_WSL_REL_REQ[REL_REQ_SIZE] = {
0xE4, 0x00,                           /* APDU CHOICE Type (RlrqApdu) */
0x00, 0x02,                           /* CHOICE.length = 2 */
0x00, 0x00                            /* reason = normal */
};

/* release response to the host */
uint_8 USB_CONST PHD_WSL_REL_RES[REL_RES_SIZE] = {
0xE5, 0x00,                           /* APDU CHOICE Type (RlrsApdu) */
0x00, 0x02,                           /* CHOICE.length = 2 */
0x00, 0x00                            /* reason = normal */
};


/* abort apdu */
uint_8 USB_CONST PHD_WSL_ABRT[ABRT_SIZE] = {
0xE6, 0x00,                           /* APDU CHOICE Type (RlrsApdu) */
0x00, 0x02,                           /* CHOICE.length = 2 */
0x00, 0x02                            /* reason = normal */
};

/* response to get attributes command */
uint_8 USB_CONST PHD_WSL_DIM_GET_RSP[DIM_GET_RSP_SIZE] = {
0xE7, 0x00,                      /* APDU CHOICE Type (PrstApdu) */
0x00, 0x6E,                      /* CHOICE.length = 110 */
0x00, 0x6C,                      /* OCTET STRING.length = 108 */
0x00, 0x02,                      /* invoke-id =0x0002 (mirrored from request)*/
0x02, 0x03,                      /* CHOICE (Remote Operation Response | Get)*/
0x00, 0x66,                      /* CHOICE.length = 102                     */
0x00, 0x00,                      /* handle = 0 (MDS object)                */
0x00, 0x06,                      /* attribute-list.count = 6               */
0x00, 0x60,                      /* attribute-list.length = 96              */
0x0A, 0x5A,                      /* attribute id=MDC_ATTR_SYS_TYPE_SPEC_LIST */
0x00, 0x08,                      /* attribute-value.length = 8              */
0x00, 0x01,                      /* TypeVerList count = 1                   */
0x00, 0x04,                      /* TypeVerList length = 4                  */
0x10, 0x0F,                      /* type = MDC_DEV_SPEC_PROFILE_SCALE  */
0x00, 0x01,                      /* version=ver 1 of the specialization  */
0x09, 0x28,                      /* attribute-id = MDC_ATTR_ID_MODEL    */
0x00, 0x1A,                      /* attribute-value.length = 26        */
0x00, 0x0A, 0x46, 0x72,          /* string length = 10 | TheCompany  */
0x65, 0x65, 0x73, 0x63,
0x61, 0x6C, 0x65, 0x20,
0x00, 0x0C, 0x4D, 0x65,          /* string length = 12 | TheScaleABC\0    */
0x64, 0x69, 0x63, 0x61,
0x6C, 0x20, 
#ifdef _MCF51JM128_H
0x43, 0x46, 0x56, 0x31,
#endif
#ifdef _MC9S08JM60_H
0x4A, 0x4D, 0x36, 0x30,
#endif
#ifdef _MC9S08JM16_H
0x4A, 0x4D, 0x31, 0x36,
#endif
#ifdef _MC9S08JS16_H
0x4A, 0x53, 0x31, 0x36,
#endif
#ifdef _MC9S08MM128_H
'M', 'M', '1', '2',
#endif
#ifdef _MC9S08JE128_H
'J', 'E', '1', '2',
#endif
#ifdef _MCF51MM256_H
'M', 'M', '2', '5',
#endif
#ifdef _MCF51JE256_H
'J', 'E', '2', '5',
#endif
#ifdef __MCF52xxx_H__
'C', 'F', 'V', '2',
#endif
#if(defined MCU_MK40N512VMD100)
'M', 'k', '4', '0',
#endif
#if(defined MCU_MK53N512CMD100)
'M', 'k', '5', '3',
#endif
#if(defined MCU_MK60N512VMD100)
'M', 'k', '6', '0',
#endif
#if (defined MCU_mcf51jf128)
'J', 'F', '1', '2',
#endif
#if(defined MCU_MK21D5)
'M', 'k', '2', '1',
#endif
#if(defined MCU_MKL25Z4)
'L', '2', 'K', ' ',
#endif
0x09, 0x84,                      /* attribute-id = MDC_ATTR_SYS_ID        */
0x00, 0x0A,                      /* attribute-value.length = 10            */
0x00, 0x08, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88,
                                 /* octet string length = 8 | EUI-64  */
0x0a, 0x44,                      /* attribute-id = MDC_ATTR_DEV_CONFIG_ID   */
0x00, 0x02,                      /* attribute-value.length = 2             */
0x40, 0x00,                      /* dev-config-id = 16384
                                    (extended-config-start)*/
0x09, 0x2D,                      /* attribute-id = MDC_ATTR_ID_PROD_SPECN */
0x00, 0x12,                      /* attribute-value.length = 18           */
0x00, 0x01,                      /* ProductionSpec.count = 1              */
0x00, 0x0E,                      /* ProductionSpec.length = 14             */
0x00, 0x01,                      /* ProdSpecEntry.spec-type=1(serial-number)*/
0x00, 0x00,                      /* ProdSpecEntry.component-id = 0     */
0x00, 0x08, 0x44, 0x45,          /* string length = 8 |
                                    prodSpecEntry.prod-spec = DE124567 */
0x31, 0x32, 0x34, 0x35,
0x36, 0x37,
0x09, 0x87,                      /* attribute-id =MDC_ATTR_TIME_ABS */
0x00, 0x08,                      /* attribute-value.length = 8  */
0x20, 0x09, 0x06, 0x12,          /* Absolute-Time-Stamp=2009-06-12T12:05:0000*/
0x12, 0x05, 0x00, 0x00
};

/* measurements to send */
uint_8  USB_CONST PHD_WSL_DIM_DATA_TX[DIM_DATA_TX_SIZE] = {
0xE7, 0x00, /*APDU CHOICE Type (PrstApdu)*/
0x00, 0x5A, /*CHOICE.length = 90*/
0x00, 0x58, /*OCTET STRING.length = 88*/
0x12, 0x36, /*invoke-id = 0x1236*/
0x01, 0x01, /*CHOICE(Remote Operation Invoke | Confirmed Event Report)*/
0x00, 0x52, /*CHOICE.length = 82*/
0x00, 0x00, /*obj-handle = 0 (MDS object)*/
0x00, 0x00, 0x00, 0x00, /*event-time = 0*/
0x0D, 0x1D, /*event-type = MDC_NOTI_SCAN_REPORT_FIXED*/
0x00, 0x48, /*event-info.length = 72*/
0xF0, 0x00, /*ScanReportInfoFixed.data-req-id = 0xF000*/
0x00, 0x00, /*ScanReportInfoFixed.scan-report-no = 0*/
0x00, 0x04, /*ScanReportInfoFixed.obs-scan-fixed.count = 4*/
0x00, 0x40, /*ScanReportInfoFixed.obs-scan-fixed.length = 64*/
0x00, 0x01, /*ScanReportInfoFixed.obs-scan-fixed.value[0].obj-handle = 1*/
0x00, 0x0C, /*ScanReportInfoFixed.obs-scan-fixed.value[0]. obs-val-data.length
              = 12*/
0xFF, 0x00, 0x02, 0xFA, /*Simple-Nu-Observed-Value = 76.2 (kg)*/
0x20, 0x07, 0x12, 0x06, /*Absolute-Time-Stamp = 2007-12-06T12:10:0000*/
0x12, 0x10, 0x00, 0x00,
0x00, 0x03, /* ScanReportInfoFixed.obs-scan-fixed.value[1].obj-handle = 3*/
0x00, 0x0C, /* ScanReportInfoFixed.obs-scan-fixed.value[1]. obs-val-data.length
               = 12*/
0xFF, 0x00, 0x00, 0xF3, /* Simple-Nu-Observed-Value = 24.3 (kg/m2)*/
0x20, 0x09, 0x06, 0x12, /* Absolute-Time-Stamp=2009-06-12T12:05:0000*/
0x12, 0x10, 0x00, 0x00,
0x00, 0x01, /*ScanReportInfoFixed.obs-scan-fixed.value[0].obj-handle = 1*/
0x00, 0x0C, /*ScanReportInfoFixed.obs-scan-fixed.value[0]. obs-val-data.length
            = 12*/
0xFF, 0x00, 0x02, 0xF8, /*Simple-Nu-Observed-Value = 76.0 (kg)*/
0x20, 0x09, 0x06, 0x12, /* Absolute-Time-Stamp=2009-06-12T12:05:0000*/
0x20, 0x05, 0x00, 0x00,
0x00, 0x03, /*ScanReportInfoFixed.obs-scan-fixed.value[1].obj-handle = 3*/
0x00, 0x0C, /*ScanReportInfoFixed.obs-scan-fixed.value[1]. obs-val-data.length
                = 12*/
0xFF, 0x00, 0x00, 0xF2, /*Simple-Nu-Observed-Value = 24.2 (kg/m2)*/
0x20, 0x09, 0x06, 0x12, /* Absolute-Time-Stamp=2009-06-12T12:05:0000*/
0x20, 0x05, 0x00, 0x00
};
/*****************************************************************************
 * Global Functions Prototypes
 *****************************************************************************/
extern void display_led(uint_8 val);
void TestApp_Init(void);
void PHD_Send_WSL_Measurements_to_Manager (
    uint_8 controller_ID,
    void* buffer_ptr,
    void* size
);
/****************************************************************************
 * Global Variables - None
 ****************************************************************************/
/*****************************************************************************
 * Local Types - None
 *****************************************************************************/
/* structure for the measurements that are changing */
typedef struct _phd_measurement
{
    AbsoluteTime msr_time;
    uint_16 weight[2];
    uint_16 bmi[2];
}PHD_MEASUREMENT, *PHD_MEASUREMENT_PTR;

/*****************************************************************************
 * Local Functions Prototypes
 *****************************************************************************/
static void USB_App_Callback(uint_8 controller_ID, uint_8 event_type);
static void Button_Pressed(void);
static void App_Display(uint_8 val);
#ifdef TIMER_CALLBACK_ARG
static void SelectTimerCallback(void * arg);
#else
static void SelectTimerCallback(void);
#endif
/*****************************************************************************
 * Local Variables
 *****************************************************************************/
#ifdef _MC9S08JS16_H
#pragma DATA_SEG PHD_BUFFER
#endif
static uint_8 event=APP_PHD_UNINITIALISED;

#ifdef _MC9S08JS16_H
#pragma DATA_SEG DEFAULT
#endif
static PHD_MEASUREMENT msr;
static uint_16 scanReportNo;
uint_8 g_app_timer = INVALID_TIMER_VALUE;
/*****************************************************************************
 * Local Functions
 *****************************************************************************/
/******************************************************************************
 *
 *    @name        USB_App_Callback
 *
 *    @brief       This function handles the callback
 *
 *    @param       controller_ID    : Controller ID
 *    @param       event_type       : Value of the event
 *
 *    @return      None
 *
 *****************************************************************************
 * This function is called from the lower layer whenever an event occurs.
 * This sets a variable according to the event_type
 *****************************************************************************/
static void USB_App_Callback(
      uint_8 controller_ID, /* [IN] Controller ID */
      uint_8 event_type     /* [IN] Value of the event */
)
{
    UNUSED (controller_ID)
    /* Remove Timer if any */
    if(g_app_timer != INVALID_TIMER_VALUE)
    {
        (void)RemoveTimerQ(g_app_timer);
        g_app_timer = INVALID_TIMER_VALUE;
    }
    switch(event_type)
    {
        case APP_PHD_UNINITIALISED:
        case APP_PHD_INITIALISED:
        case APP_PHD_CONNECTED_TO_HOST:
        case APP_PHD_ERROR:
            scanReportNo = 0; /* Initialize with 0 each time the Agent is associated to the manager */
            event = event_type;
            break;
        case APP_PHD_MEASUREMENT_SENT:
            event = APP_PHD_CONNECTED_TO_HOST;
            break;
        case APP_PHD_DISCONNECTED_FROM_HOST:
        case APP_PHD_ASSOCIATION_TIMEDOUT:
            event = APP_PHD_INITIALISED;
            break;
        
    }
    return;
}
/******************************************************************************
 *
 *   @name        Button_Pressed
 *
 *   @brief       This funtion checks for any button pressed on the demo board
 *   @param       None
 *
 *   @return      None
 *
 *****************************************************************************
 * This function sends the measurement data or the dissociation request
 * depending on the key pressed
 *****************************************************************************/
 static void Button_Pressed(void)
 {
    if(kbi_stat > 0)
    {
        switch(kbi_stat & KBI_STAT_MASK)
        {
            case SEND_MEASUREMENT_BULK: 
                /* 
                    PTG1 is pressed, used to send
                    measurements 
                */
                if(event == APP_PHD_CONNECTED_TO_HOST)
                {
    		        /* 
    		            Send measurements only when the device is in the 
    		            operating state 
    		        */
    		        event = APP_PHD_MEASUREMENT_SENDING;
                    PHD_Send_Measurements_to_Manager(CONTROLLER_ID , PHDC_BULK_IN_QOS);
                }
                break;
            case SEND_MEASUREMENT_INT:
             #ifndef BUTTON_PRESS_SIMULATION
              #ifndef _MC9S08JS16_H 
                /* 
                    PTG1 is pressed, used to send
                    measurements 
                */
                if(event == APP_PHD_CONNECTED_TO_HOST)
                {
    		        /* 
    		            Send measurements only when the device is in the 
    		            operating state 
    		        */
    		        event = APP_PHD_MEASUREMENT_SENDING;
                    PHD_Send_Measurements_to_Manager(CONTROLLER_ID , PHDC_INT_IN_QOS);
                }
                break;                
              #endif /* _MC9S08JS16_H */
             #endif /* BUTTON_PRESS_SIMULATION */ 
            case DISCONNECT:
              #ifndef BUTTON_PRESS_SIMULATION  
                /* 
                    PTG2 is pressed, to disconnect(dis-associate)
                    from the host 
                */                
                if(event == APP_PHD_CONNECTED_TO_HOST)
                {
                    event = APP_PHD_DISCONNECTING;
                    PHD_Disconnect_from_Manager(CONTROLLER_ID);
                }
                break;
              #endif /* BUTTON_PRESS_SIMULATION */ 
            default:
                break; /* otherwise */
        }
        kbi_stat = 0x00;
    }
 }
/******************************************************************************
 *
 *   @name        TestApp_Init
 *
 *   @brief       This function is the entry for the PHDC Application
 *
 *   @param       None
 *
 *   @return      None
 *
 *****************************************************************************
 * This function starts the PHDC (weighing scale) application
 *****************************************************************************/
void TestApp_Init(void)
{
    uint_8 error;

    /* initialize measurements */
    msr.msr_time.century = 0x20;
    msr.msr_time.year    = 9;
    msr.msr_time.month   = 4;
    msr.msr_time.day     = 9;
    msr.msr_time.hour    = 3;
    msr.msr_time.minute  = 5;
    msr.msr_time.second  = 0;
    msr.msr_time.sec_fractions = 0;

    msr.bmi[0]=  200;
    msr.bmi[1]=  205;
    msr.weight[0]= 95;
    msr.weight[1]= 54;

    DisableInterrupts;
	#if (defined _MCF51MM256_H) || (defined _MCF51JE256_H)
		usb_int_dis();
	#endif	
    /* Initialize the USB interface */
    error = PHD_Transport_Init(CONTROLLER_ID, USB_App_Callback);

    EnableInterrupts;
	#if (defined _MCF51MM256_H) || (defined _MCF51JE256_H)
		usb_int_en();
	#endif		

}

/******************************************************************************
 *
 *   @name        TestApp_Task
 *
 *   @brief       Application task function. It is called from the main loop
 *
 *   @param       None
 *
 *   @return      None
 *
 *****************************************************************************
 * Application task function. It is called from the main loop
 *****************************************************************************/
void TestApp_Task(void)
{       
        /* Check for any button pressed */
        Button_Pressed();
        switch (event)
        {
            case APP_PHD_INITIALISED:
                {
                    /* 
                        Start a timer so that the user has enough time to 
                        select the device specialization 
                    */
                    TIMER_OBJECT TimerObject;
                    TimerObject.msCount = SELECT_TIMEOUT;
                    TimerObject.pfnTimerCallback = SelectTimerCallback;
                 
                    event = APP_PHD_SELECT_TIMER_STARTED;
                    g_app_timer = AddTimerQ(&TimerObject);
                }
                break;
            case APP_PHD_DISCONNECTED_FROM_HOST:
                /* 
                    transition to initialised state so the association 
                    procedure can start again 
                */
                event = APP_PHD_INITIALISED;
                break;

            case APP_PHD_MEASUREMENT_SENT:
                /* 
                    enters here each time we receive a response to the
                    measurements sent 
                */
                event = APP_PHD_CONNECTED_TO_HOST;
                break;
            case APP_PHD_SELECT_TIMER_OFF:
                /* 
                    Start the association procedure once the select timer 
                    fires 
                */
                event = APP_PHD_INITIATED;
                /* connect to the manager */
                PHD_Connect_to_Manager(CONTROLLER_ID);                  
                break;
                  
          default:
              break;
    
        }
}

/******************************************************************************
 *
 *   @name        SelectTimerCallback
 *
 *   @brief       This function is called when the timer used for selecting the
 *                the device specialization fires
 *
 *   @param       arg   : Argument passed by Timer ISR (optional)
 *
 *   @return      None
 *
 *****************************************************************************
 * This function when called initiates the association procedure for the 
 * selected device specialization
 *****************************************************************************/
#ifdef TIMER_CALLBACK_ARG
static void SelectTimerCallback(void * arg)
#else
static void SelectTimerCallback(void)
#endif
{
#ifdef TIMER_CALLBACK_ARG
    UNUSED (arg)
#endif
    g_app_timer = INVALID_TIMER_VALUE;
    event = APP_PHD_SELECT_TIMER_OFF;
}
/******************************************************************************
 *
 *    @name        PHD_Send_WSL_Measurements_to_Manager
 *
 *    @brief       This function sends measurements to the host
 *
 *    @param       controller_ID : Controller ID
 *
 *    @return      None
 *
 *****************************************************************************
 * Called by the application to send the measurement data via event report
 *****************************************************************************/
void PHD_Send_WSL_Measurements_to_Manager (
    uint_8 controller_ID,       /* [IN] Controller ID */    
    void* buffer_ptr,           /* [IN] Measurement buffer */
    void* size                /* [IN] Buffer size */
)
{
        uint_8 i=0;
        uint_8_ptr send_buff = (uint_8_ptr)buffer_ptr;
        
        DATA_apdu *dataApdu = (DATA_apdu *)&(((PRST_apdu *)&((APDU *)send_buff)->u.prst)->value[0]);
        ScanReportInfoFixed *scan_rep = (ScanReportInfoFixed *)&(dataApdu->choice.u.roiv_cmipConfirmedEventReport.event_info.value[0]);
        
        UNUSED(controller_ID)
        *(USB_PACKET_SIZE *)size = DIM_DATA_TX_SIZE;
        /* copy the measurements to send in the phd_buffer */
        (void)memcpy(send_buff, PHD_WSL_DIM_DATA_TX, DIM_DATA_TX_SIZE);        
        /* update the scan report no */
        scan_rep->scan_report_no = scanReportNo++;
        
         /* set measurement  */
         for(i = 0; i < 4; i++)
         {
             msr.msr_time.second++;
             msr.msr_time.second %= 60;
             send_buff[44+i*16] = msr.msr_time.second;
         }

         for(i=0;i<4;i++)
         {
             uint_8 j = (uint_8)(i >> 1);
             if((i & 0x01) == 0)
             {
                msr.weight[j]++;                
                msr.weight[j] %= 1000;
                send_buff[36+i*16] = (uint_8)((msr.weight[j] >> 8) & 0x00FF);
                send_buff[37+i*16] = (uint_8)((msr.weight[j]) & 0x00FF);
             }
             else /* bmi */
             {
                msr.bmi[j]++;                
                msr.bmi[j] %= 500;
                send_buff[36+i*16] = (uint_8)((msr.bmi[j] >> 8) & 0x00FF);
                send_buff[37+i*16] = (uint_8)((msr.bmi[j]) & 0x00FF);
             }
         }
}
