/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2010 Freescale Semiconductor, Inc.
 * ALL RIGHTS RESERVED.
 *
 **************************************************************************//*!
 *
 * @file phd_device_spec.c
 *
 * @author
 *
 * @version
 *
 * @date June-16-2009

 * @brief This file contains all the data and functions of the various device
 *        specializations supported
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <string.h>				
#include "derivative.h"             /* include peripheral declarations */
#include "types.h"                  /* User Defined Data Types */
#if(defined LITTLE_ENDIAN)
#include "ieee11073_phd_types_kinetis.h"    /* IEEE11073 Data Structures */
#else
#include "ieee11073_phd_types.h"    /* IEEE11073 Data Structures */
#endif
#include "ieee11073_nom_codes.h"    /* IEEE11073 Nomenclature Codes */
#include "phd_com_model.h"
#include "phd_device_spec.h"
#include "user_config.h"

/*****************************************************************************
 * Global Functions Prototypes
 *****************************************************************************/

/****************************************************************************
 * Global Variables
 ****************************************************************************/
/*****************************************************************************
 * Local Types - None
 *****************************************************************************/

/*****************************************************************************
 * Local Functions Prototypes
 *****************************************************************************/
/* Update Weigh Scale measurements */
static void PHD_Send_WSL_Measurements_to_Manager (
    uint_8 controller_ID,
    void* buffer_ptr,
    void* size
);
/* Update Glucose measurements */
static void PHD_Send_GLUCO_Measurements_to_Manager (
    uint_8 controller_ID,
    void* buffer_ptr,
    void* size
);
/* Update Blood Pressure measurements */
static void PHD_Send_BPM_Measurements_to_Manager (
    uint_8 controller_ID,
    void* buffer_ptr,
    void* size
);
/* Update Temperature measurements */
static void PHD_Send_THERMO_Measurements_to_Manager (
    uint_8 controller_ID,
    void* buffer_ptr,
    void* size
);

#if (defined __MCF52xxx_H__)||(defined LITTLE_ENDIAN)
/* Put CFV2 hardcoded messages in RAM */
#define USB_CONST
#else
/* Const placement */
#define USB_CONST		const
#endif

/*****************************************************************************
 * Constant and Macro's
 *****************************************************************************/ 
/* abort apdu */
uint_8 USB_CONST PHD_ABRT[ABRT_SIZE] = {
0xE6, 0x00,                           /* APDU CHOICE Type (RlrsApdu) */
0x00, 0x02,                           /* CHOICE.length = 2 */
0x00, 0x02                            /* reason = normal */
};

/* WEIGH SCALE */

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
0x40, 0x04,                         /* dev-config-id | extended configuration*/ 
0x00, 0x01,                         /* data-req-mode-flags */
0x01, 0x00,                         /* data-req-init-agent-count, 
                                      data-req-init-manager-count */
0x00, 0x00, 0x00, 0x00              /* Atribute list */
};

/* configuration event report */ 
uint_8 USB_CONST PHD_WSL_CNFG_EVT_RPT[PHD_WSL_CNFG_EVT_RPT_SIZE] = {   
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
0x40, 0x04,                           /*  config-report-id */ 
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

/* response to get attributes command */
uint_8 USB_CONST PHD_WSL_DIM_GET_RSP[PHD_WSL_DIM_GET_RSP_SIZE] = {   
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
0x00, 0x0C, 0x4D, 0x65,          /* string length = 12 | WeighScale    */
0x64, 0x69, 0x63, 0x61,
0x6C, 0x20, 
#ifdef _MCF51JM128_H
0x43, 0x46, 0x56, 0x31,
#elif defined _MC9S08JM60_H
0x4A, 0x4D, 0x36, 0x30,
#elif defined _MC9S08JM16_H
0x4A, 0x4D, 0x31, 0x36,
#elif defined _MC9S08JS16_H
0x4A, 0x53, 0x31, 0x36,
#elif defined _MCF51MM256_H
'M', 'M', '2', '5',
#elif defined _MC9S08MM128_H
'M', 'M', '1', '2',
#elif defined _MCF51JE256_H
'J', 'E', '2', '5',
#elif defined _MC9S08JE128_H
'J', 'E', '1', '2',
#elif defined __MCF52xxx_H__
'C', 'F', 'V', '2',
#elif (defined MCU_MK20D5) || (defined MCU_MK20D7)
'M', 'K', '2', '0',
#elif (defined MCU_MK21D5)
'M', 'K', '2', '1',
#elif (defined MCU_MK40N512VMD100) || (defined MCU_MK40D7)
'M', 'K', '4', '0',
#elif defined MCU_MK53N512CMD100
'M', 'K', '5', '3',
#elif defined MCU_MK60N512VMD100
'M', 'K', '6', '0',
#elif defined MCU_MK70F12
'M', 'K', '7', '0',
#elif defined MCU_mcf51jf128
'J', 'F', '1', '2',
#elif defined MCU_MKL25Z4
'L', '2', 'K', ' ',
#else
#error "No device configuration"
#endif
0x09, 0x84,                      /* attribute-id = MDC_ATTR_SYS_ID        */
0x00, 0x0A,                      /* attribute-value.length = 10            */
0x00, 0x08, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 
                                 /* octet string length = 8 | EUI-64  */
0x0a, 0x44,                      /* attribute-id = MDC_ATTR_DEV_CONFIG_ID   */
0x00, 0x02,                      /* attribute-value.length = 2             */
0x40, 0x04,                      /* dev-config-id = 16384 
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
uint_8  USB_CONST PHD_WSL_DIM_DATA_TX[PHD_WSL_DIM_DATA_TX_SIZE] = {   
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
0xFF, 0x00, 0xFF, 0x5F, /*Simple-Nu-Observed-Value = 76.2 (kg)*/
0x20, 0x09, 0x06, 0x12, /*Absolute-Time-Stamp = 2009-06-12T12:10:0000*/
0x0A, 0x05, 0x00, 0x00,
0x00, 0x03, /* ScanReportInfoFixed.obs-scan-fixed.value[1].obj-handle = 3*/
0x00, 0x0C, /* ScanReportInfoFixed.obs-scan-fixed.value[1]. obs-val-data.length
               = 12*/
0xFF, 0x00, 0x00, 0xC8, /* Simple-Nu-Observed-Value = 24.3 (kg/m2)*/
0x20, 0x09, 0x06, 0x12, /*Absolute-Time-Stamp = 2009-06-12T12:10:0000*/
0x0A, 0x05, 0x00, 0x00,
0x00, 0x01, /*ScanReportInfoFixed.obs-scan-fixed.value[0].obj-handle = 1*/
0x00, 0x0C, /*ScanReportInfoFixed.obs-scan-fixed.value[0]. obs-val-data.length 
            = 12*/
0xFF, 0x00, 0x02, 0x36, /*Simple-Nu-Observed-Value = 76.0 (kg)*/
0x20, 0x09, 0x06, 0x12, /*Absolute-Time-Stamp = 2009-06-12T12:10:0000*/
0x0A, 0x05, 0x00, 0x00,
0x00, 0x03, /*ScanReportInfoFixed.obs-scan-fixed.value[1].obj-handle = 3*/
0x00, 0x0C, /*ScanReportInfoFixed.obs-scan-fixed.value[1]. obs-val-data.length 
                = 12*/
0xFF, 0x00, 0x00, 0xCD, /*Simple-Nu-Observed-Value = 24.2 (kg/m2)*/
0x20, 0x09, 0x06, 0x12, /*Absolute-Time-Stamp = 2009-06-12T12:10:0000*/
0x0A, 0x05, 0x00, 0x00
};

/* GLUCOMETER */

/* association request to send */ 
uint_8 USB_CONST PHD_GLUCO_ASSOC_REQ[ASSOC_REQ_SIZE] = {   
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
0x40, 0x05,                         /* dev-config-id | extended configuration*/ 
0x00, 0x01,                         /* data-req-mode-flags */
0x01, 0x00,                         /* data-req-init-agent-count, 
                                      data-req-init-manager-count */
0x00, 0x00, 0x00, 0x00              /* Atribute list */
};

/* configuration event report */ 
uint_8 USB_CONST PHD_GLUCO_CNFG_EVT_RPT[PHD_GLUCO_CNFG_EVT_RPT_SIZE] = {   
0xE7, 0x00,                           /* APDU CHOICE Type (PrstApdu) */
0x00, 0x9A,                           /* CHOICE.length = 154 */
0x00, 0x98,                           /* OCTET STRING.length = 152 */
0x00, 0x02,                           /*  invoke-id = 0x1235 (start of DataApdu
                                          . MDER encoded.) */ 
0x01, 0x01,                           /*  CHOICE(Remote Operation Invoke | 
                                          Confirmed Event Report) */
0x00, 0x92,                           /*  CHOICE.length = 146 */
0x00, 0x00,                           /*  obj-handle = 0 (MDS object) */
0xFF, 0xFF, 0xFF, 0xFF,               /*  event-time = 0xFFFFFFFF    */
0x0D, 0x1C,                           /*  event-type = MDC_NOTI_CONFIG */
0x00, 0x88,                           /*  event-info.length = 136 (start of 
                                          ConfigReport) */
0x40, 0x05,                           /*  config-report-id */ 
0x00, 0x03,                           /*  config-obj-list.count = 3 Measurement
                                          objects will be announced */
0x00, 0x82,                           /*  config-obj-list.length = 130 */
0x00, 0x06,                           /*  obj-class = MDC_MOC_VMO_METRIC_NU */
0x00, 0x01,                           /*  obj-handle = 1 (.. 1st Measurement is
                                          blood glucose) */
0x00, 0x04,                           /*  attributes.count = 4  */
0x00, 0x24,                           /*  attributes.length = 36  */
0x09, 0x2F,                           /*  attribute-id = MDC_ATTR_ID_TYPE */
0x00, 0x04,                           /*  attribute-value.length = 4      */
0x00, 0x02, 0x71, 0xB8,               /*  MDC_PART_SCADA |  
                                          MDC_CONC_GLU_CAPILLARY_WHOLEBLOOD  */ 
0x0A, 0x46,                           /*  attribute-id = 
                                          MDC_ATTR_METRIC_SPEC_SMALL      */
0x00, 0x02,                           /*  attribute-value.length = 2  */
0xF0, 0x40,                           /*  intermittent, stored data, upd & msmt
                                          aperiodic, agent init, measured */
0x09, 0x96,                           /*  attribute-id = MDC_ATTR_UNIT_CODE */
0x00, 0x02,                           /*  attribute-value.length = 2 */
0x12, 0x72,                           /*  MDC_DIM_MILLI_MOLE_PER_L         */
0x0A, 0x55,                           /*  attribute-id = 
                                          MDC_ATTR_ATTRIBUTE_VAL_MAP  */
0x00, 0x0C,                           /*  attribute-value.length = 12     */
0x00, 0x02,                           /*  AttrValMap.count = 2         */
0x00, 0x08,                           /*  AttrValMap.length = 8          */
0x0A, 0x4C, 0x00, 0x02,               /*  MDC_ATTR_NU_VAL_OBS_BASIC | 
                                          value length = 2    */
0x09, 0x90, 0x00, 0x08,               /*  MDC_ATTR_TIME_STAMP_ABS | 
                                          value length = 8     */
0x00, 0x05,                           /*  obj-class = MDC_MOC_VMO_METRIC_ENUM*/
0x00, 0x02,                           /*  obj-handle = 2 (..2nd Measurement 
                                          is context meal) */
0x00, 0x03,                           /*  attributes.count = 3   */
0x00, 0x1E,                           /*  attributes.length = 30   */
0x09, 0x2F,                           /*  attribute-id = MDC_ATTR_ID_TYPE */
0x00, 0x04,                           /*  attribute-value.length = 4  */
0x00, 0x80, 0x72, 0x48,               /*  MDC_PART_PHD_DM | 
                                          MDC_CTXT_GLU_MEAL */
0x0A, 0x46,                           /*  attribute-id = 
                                          MDC_ATTR_METRIC_SPEC_SMALL   */
0x00, 0x02,                           /*  attribute-value.length = 2   */
0xF0, 0x48,                           /*  intermittent, stored data, upd & msmt
                                          aperiodic, agent init, manual */
0x0A, 0x55,                           /*  attribute-id = 
                                          MDC_ATTR_ATTRIBUTE_VAL_MAP */
0x00, 0x0C,                           /*  attribute-value.length = 12 */
0x00, 0x02,                           /*  AttrValMap.count = 2*/
0x00, 0x08,                           /*  AttrValMap.length = 8*/
0x09, 0x90, 0x00, 0x08,               /*  MDC_ATTR_TIME_STAMP_ABS, 8  */
0x0A, 0x49, 0x00, 0x02,               /*  MDC_ATTR_ENUM_OBS_VAL_SIMP_OID, 2 */
0x00, 0x06,                           /*  obj-class = MDC_MOC_VMO_METRIC_NU*/
0x00, 0x03,                           /*  obj-handle = 3 (..3rd Measurement 
                                          is context exercise) */
0x00, 0x04,                           /*  attributes.count = 4*/
0x00, 0x28,                           /*  attributes.length = 40 */
0x09, 0x2F,                           /*  attribute-id = MDC_ATTR_ID_TYPE */
0x00, 0x04,                           /*  attribute-value.length = 4 */
0x00, 0x80, 0x71, 0xE0,               /*  MDC_PART_PHD_DM | 
                                          MDC_CTXT_GLU_EXERCISE    */
0x0A, 0x46,                           /*  attribute-id = 
                                          MDC_ATTR_METRIC_SPEC_SMALL       */
0x00, 0x02,                           /*  attribute-value.length = 2    */
0xF0, 0x48,                           /*  intermittent, stored data, upd & 
                                      msmt aperiodic, agent init, manual */
0x09, 0x96,                           /*  attribute-id = MDC_ATTR_UNIT_CODE*/
0x00, 0x02,                           /*  attribute-value.length = 2       */
0x02, 0x20,                           /*  MDC_DIM_PERCENT               */
0x0A, 0x55,                           /*  attribute-id = 
                                          MDC_ATTR_ATTRIBUTE_VAL_MAP        */
0x00, 0x10,                           /*  attribute-value.length = 16 */
0x00, 0x03,                           /*  AttrValMap.count = 3          */
0x00, 0x0C,                           /*  AttrValMap.length = 12   */
0x09, 0x90, 0x00, 0x08,               /*  MDC_ATTR_TIME_STAMP_ABS, 8 */
0x0A, 0x59, 0x00, 0x04,               /*  MDC_ATTR_TIME_PD_MSMT_ACTIVE, 4 */
0x0A, 0x4C, 0x00, 0x02                /*  MDC_ATTR_NU_VAL_OBS_SIMP, 2 */
};       

/* release request to send */
uint_8 USB_CONST PHD_GLUCO_REL_REQ[REL_REQ_SIZE] = {   
0xE4, 0x00,                           /* APDU CHOICE Type (RlrqApdu) */
0x00, 0x02,                           /* CHOICE.length = 2 */
0x00, 0x00                            /* reason = normal */
};

/* release response to the host */
uint_8 USB_CONST PHD_GLUCO_REL_RES[REL_RES_SIZE] = {   
0xE5, 0x00,                           /* APDU CHOICE Type (RlrsApdu) */
0x00, 0x02,                           /* CHOICE.length = 2 */
0x00, 0x00                            /* reason = normal */
};

/* response to get attributes command */
uint_8 USB_CONST PHD_GLUCO_DIM_GET_RSP[PHD_GLUCO_DIM_GET_RSP_SIZE] = {   
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
0x10, 0x11,                      /* type = MDC_DEV_SPEC_PROFILE_GLUCOSE  */
0x00, 0x01,                      /* version=ver 1 of the specialization  */
0x09, 0x28,                      /* attribute-id = MDC_ATTR_ID_MODEL    */
0x00, 0x1A,                      /* attribute-value.length = 26        */
0x00, 0x0A, 0x46, 0x72,          /* string length = 10 | TheCompany  */
0x65, 0x65, 0x73, 0x63,                                                     
0x61, 0x6C, 0x65, 0x20,
0x00, 0x0C, 0x4D, 0x65,          /* string length = 12 | GlucoseMeter */
0x64, 0x69, 0x63, 0x61,
0x6C, 0x20, 
#ifdef _MCF51JM128_H
0x43, 0x46, 0x56, 0x31,
#elif defined _MC9S08JM60_H
0x4A, 0x4D, 0x36, 0x30,
#elif defined _MC9S08JM16_H
0x4A, 0x4D, 0x31, 0x36,
#elif defined _MC9S08JS16_H
0x4A, 0x53, 0x31, 0x36,
#elif defined _MCF51MM256_H
'M', 'M', '2', '5',
#elif defined _MC9S08MM128_H
'M', 'M', '1', '2',
#elif defined _MCF51JE256_H
'J', 'E', '2', '5',
#elif defined _MC9S08JE128_H
'J', 'E', '1', '2',
#elif defined __MCF52xxx_H__
'C', 'F', 'V', '2',
#elif (defined MCU_MK20D5) || (defined MCU_MK20D7)
'M', 'K', '2', '0',
#elif (defined MCU_MK21D5)
'M', 'K', '2', '1',
#elif (defined MCU_MK40N512VMD100) || (defined MCU_MK40D7)
'M', 'K', '4', '0',
#elif defined MCU_MK53N512CMD100
'M', 'K', '5', '3',
#elif defined MCU_MK60N512VMD100
'M', 'K', '6', '0',
#elif defined MCU_MK70F12
'M', 'K', '7', '0',
#elif defined MCU_mcf51jf128
'J', 'F', '1', '2',
#elif defined MCU_MKL25Z4
'L', '2', 'K', ' ',
#else
#error "No device configuration"
#endif
0x09, 0x84,                      /* attribute-id = MDC_ATTR_SYS_ID        */
0x00, 0x0A,                      /* attribute-value.length = 10            */
0x00, 0x08, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 
                                 /* octet string length = 8 | EUI-64  */
0x0a, 0x44,                      /* attribute-id = MDC_ATTR_DEV_CONFIG_ID   */
0x00, 0x02,                      /* attribute-value.length = 2             */
0x40, 0x05,                      /* dev-config-id = 16384 
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
0x20, 0x09, 0x02, 0x01,          /* Absolute-Time-Stamp=2009-02-01T12:05:0000*/
0x12, 0x05, 0x00, 0x00                                                               
};  

/* measurements to send */
uint_8  USB_CONST PHD_GLUCO_DIM_DATA_TX[PHD_GLUCO_DIM_DATA_TX_SIZE] = {   
0xE7, 0x00, /*APDU CHOICE Type (PrstApdu)*/
0x00, 0x64, /*CHOICE.length = 100*/
0x00, 0x62, /*OCTET STRING.length = 98*/
0x12, 0x36, /*invoke-id = 0x1236*/
0x01, 0x01, /*CHOICE(Remote Operation Invoke | Confirmed Event Report)*/
0x00, 0x5C, /*CHOICE.length = 92*/
0x00, 0x00, /*obj-handle = 0 (MDS object)*/
0x00, 0x00, 0x00, 0x00, /*event-time = 0*/
0x0D, 0x1D, /*event-type = MDC_NOTI_SCAN_REPORT_FIXED*/
0x00, 0x52, /*event-info.length = 82*/
0xF0, 0x00, /*ScanReportInfoFixed.data-req-id = 0xF000*/
0x00, 0x00, /*ScanReportInfoFixed.scan-report-no = 0*/
0x00, 0x05, /*ScanReportInfoFixed.obs-scan-fixed.count = 5*/
0x00, 0x4A, /*ScanReportInfoFixed.obs-scan-fixed.length = 74*/
0x00, 0x01, /*ScanReportInfoFixed.obs-scan-fixed.value[0].obj-handle = 1*/
0x00, 0x0A, /*ScanReportInfoFixed.obs-scan-fixed.value[0]. obs-val-data.length 
              = 10*/
0xF3, 0x52, /*Basic-Nu-Observed-Value = 85.0 (mmol/L) */
0x20, 0x09, 0x06, 0x12, /*Absolute-Time-Stamp = 2009-06-12T12:10:0000*/
0x12, 0x05, 0x00, 0x00,
0x00, 0x01, /* ScanReportInfoFixed.obs-scan-fixed.value[1].obj-handle = 1*/
0x00, 0x0A, /* ScanReportInfoFixed.obs-scan-fixed.value[1]. obs-val-data.length
               = 10*/
0xF4, 0x4C,  /* Basic-Nu-Observed-Value = 110.0 (mmol/L) */
0x20, 0x09, 0x06, 0x12, /*Absolute-Time-Stamp = 2007-06-12T12:10:0000*/
0x12, 0x05, 0x00, 0x00,
0x00, 0x02, /*ScanReportInfoFixed.obs-scan-fixed.value[0].obj-handle = 2*/
0x00, 0x0A, /*ScanReportInfoFixed.obs-scan-fixed.value[0]. obs-val-data.length 
            = 10*/
0x20, 0x09, 0x06, 0x12, /*Absolute-Time-Stamp = 2009-06-12T12:10:0000*/
0x12, 0x05, 0x00, 0x00,
0x72, 0x4C, /*OID=MDC_CTXT_GLU_MEAL_PREPRANDIAL */
0x00, 0x02, /*ScanReportInfoFixed.obs-scan-fixed.value[1].obj-handle = 2*/
0x00, 0x0A,  /*ScanReportInfoFixed.obs-scan-fixed.value[1]. obs-val-data.length 
                = 10*/
0x20, 0x09, 0x06, 0x12, /*Absolute-Time-Stamp = 2009-06-12T12:10:0000*/
0x12, 0x05, 0x00, 0x00,
0x72, 0x50, /*OID= MDC_CTXT_GLU_MEAL_POSTPRANDIAL */
0x00, 0x03, /* ScanReportInfoFixed.obs-scan-fixed.value[1].obj-handle = 3*/
0x00, 0x0E, /* ScanReportInfoFixed.obs-scan-fixed.value[1]. obs-val-data.length
             = 14*/
0x20, 0x09, 0x06, 0x12,  /*Absolute-Time-Stamp = 2009-06-12T12:10:0000*/
0x12, 0x05, 0x00, 0x00,
0x01, 0xB7, 0x74, 0x00,/*Measure-Active-Period=1 hour (28800000 counts of 1/8 
                        milliseconds) */
0xF3, 0x84,        /*Basic-Nu-Observed-Value = 90 (%)*/
};

/* BLOOD PRESSURE MONITOR */

/* association request to send */ 
uint_8 USB_CONST PHD_BPM_ASSOC_REQ[ASSOC_REQ_SIZE] = {   
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
uint_8 USB_CONST PHD_BPM_CNFG_EVT_RPT[PHD_BPM_CNFG_EVT_RPT_SIZE] = {   
0xE7, 0x00,                           /* APDU CHOICE Type (PrstApdu) */
0x00, 0x94,                           /* CHOICE.length = 148 */
0x00, 0x92,                           /* OCTET STRING.length = 146 */
0x00, 0x02,                           /*  invoke-id = 0x1235 (start of DataApdu
                                          . MDER encoded.) */ 
0x01, 0x01,                           /*  CHOICE(Remote Operation Invoke | 
                                          Confirmed Event Report) */
0x00, 0x8C,                           /*  CHOICE.length = 140 */
0x00, 0x00,                           /*  obj-handle = 0 (MDS object) */
0xFF, 0xFF, 0xFF, 0xFF,               /*  event-time = 0xFFFFFFFF    */
0x0D, 0x1C,                           /*  event-type = MDC_NOTI_CONFIG */
0x00, 0x82,                           /*  event-info.length = 130 (start of 
                                          ConfigReport) */
0x02, 0xBC,                           /*  config-report-id */ 
0x00, 0x02,                           /*  config-obj-list.count = 2 Measurement
                                          objects will be announced */
0x00, 0x7C,                           /*  config-obj-list.length = 124 */
0x00, 0x06,                           /*  obj-class = MDC_MOC_VMO_METRIC_NU */
0x00, 0x01,                           /*  obj-handle = 1 (.. 1st Measurement is
                                          systolic, diastolic, MAP) */
0x00, 0x07,                           /*  attributes.count = 7  */
0x00, 0x40,                           /*  attributes.length = 64  */
0x09, 0x2F,                           /*  attribute-id = MDC_ATTR_ID_TYPE */
0x00, 0x04,                           /*  attribute-value.length = 4      */
0x00, 0x02, 0x4A, 0x04,               /*  0xE1 0x40 MDC_PART_SCADA |  
                                          MDC_PRESS_BLD_NONINV */ 
0x0A, 0x46,                           /*  attribute-id = 
                                          MDC_ATTR_METRIC_SPEC_SMALL      */
0x00, 0x02,                           /*  attribute-value.length = 2  */
0xF0, 0x40,                           /*  intermittent, stored data, upd & msmt
                                          aperiodic, agent init, measured */
0x0A, 0x73,                           /*  attribute-id = 
                                          MDC_ATTR_METRIC_STRUCT_SMALL */
0x00, 0x02,                           /*  attribute-value.length = 2 */
0x03, 0x03,                           /*  {ms-struct-compound-fix, 3}  */
0x0A, 0x76,                           /*  attribute-id = 
                                          MDC_ATTR_ID_PHYSIO_LIST  */
0x00, 0x0A,                           /*  attribute-value.length = 10     */
0x00, 0x03,                           /*  AttrValMap.count = 3         */
0x00, 0x06,                           /*  AttrValMap.length = 6          */
0x4A, 0x05, 0x4A, 0x06,               
0x4A, 0x07,                           /*  {MDC_PRESS_BLD_NONINV_SYS,  
                                           MDC_PRESS_BLD_NONINV_DIA,  
                                           MDC_PRESS_BLD_NONINV_MEAN}  */
0x09, 0x96,                           /*  attribute-id = MDC_ATTR_UNIT_CODE */
0x00, 0x02,                           /*  attribute-value.length = 2  */
0x0F, 0x20,                           /*  MDC_DIM_MMHG */
0x09, 0x4A,                           /*  attribute-id = 
                                          MDC_ATTR_NU_ACCUR_MSMT */
0x00, 0x04,                           /*  attribute-value.length = 4    */
0xFA, 0x1E, 0x84, 0x80,               /*  accuracy = 2.0  */
0x0A, 0x55,                           /*  attribute-id = 
                                          MDC_ATTR_ATTRIBUTE_VAL_MAP   */
0x00, 0x0C,                           /*  attribute-value.length = 12   */
0x00, 0x02,                           /*  AttrValMap.count = 2  */
0x00, 0x08,                           /*  AttrValMap.length = 8 */
0x0A, 0x75,0x00, 0x0A,                /*  MDC_ATTR_NU_CMPD_VAL_OBS_BASIC | 
                                          value length = 10 */
0x09, 0x90,0x00, 0x08,                /*  MDC_ATTR_TIME_STAMP_ABS | 
                                          value length = 8  */
0x00, 0x06,                           /*  obj-class = MDC_MOC_VMO_METRIC_NU */
0x00, 0x02,                           /*  obj-handle = 2   (2nd
                                          Measurement is pulse rate)*/
0x00, 0x05,                           /*  attributes.count = 5 */
0x00, 0x2C,                           /*  attributes.length = 44 */
0x09, 0x2F,                           /*  attribute-id = MDC_ATTR_ID_TYPE  */
0x00, 0x04,                           /*  attribute-value.length = 4 */
0x00, 0x02,0x48, 0x2A,                /*  MDC_PART_SCADA | 
                                          MDC_PULS_RATE_NON_INV */
0x0A, 0x46,                           /*  attribute-id = 
                                          MDC_ATTR_METRIC_SPEC_SMALL */
0x00, 0x02,                           /*  attribute-value.length = 2 */
0xF0, 0x40,                           /*  intermittent, stored data, upd & msmt
                                          aperiodic, agent init, measured  */
0x09, 0x96,                           /*  attribute-id = MDC_ATTR_UNIT_CODE */
0x00, 0x02,                           /*  attribute-value.length = 2 */
0x0A, 0xA0,                           /*  MDC_DIM_BEAT_PER_MIN */
0x09, 0x4A,                           /*  attribute-id = 
                                          MDC_ATTR_NU_ACCUR_MSMT */
0x00, 0x04,                           /*  attribute-value.length = 4 */
0xFA, 0x0F,0x42, 0x40,                /*  accuracy = 1.0 */           
0x0A, 0x55,                           /*  attribute-id = 
                                          MDC_ATTR_ATTRIBUTE_VAL_MAP  */
0x00, 0x0C,                           /*  attribute-value.length = 12 */
0x00, 0x02,                           /*  AttrValMap.count = 2 */
0x00, 0x08,                           /*  AttrValMap.length = 8  */
0x0A, 0x4C, 0x00, 0x02,               /*  MDC_ATTR_NU_VAL_OBS_BASIC | 
                                          value length = 2  */
0x09, 0x90, 0x00, 0x08                /*  MDC_ATTR_TIME_STAMP_ABS | 
                                          value length = 8 */
};       

/* release request to send */
uint_8 USB_CONST PHD_BPM_REL_REQ[REL_REQ_SIZE] = {   
0xE4, 0x00,                           /* APDU CHOICE Type (RlrqApdu) */
0x00, 0x02,                           /* CHOICE.length = 2 */
0x00, 0x00                            /* reason = normal */
};

/* release response to the host */
uint_8 USB_CONST PHD_BPM_REL_RES[REL_RES_SIZE] = {   
0xE5, 0x00,                           /* APDU CHOICE Type (RlrsApdu) */
0x00, 0x02,                           /* CHOICE.length = 2 */
0x00, 0x00                            /* reason = normal */
};

/* response to get attributes command */
uint_8 USB_CONST PHD_BPM_DIM_GET_RSP[PHD_BPM_DIM_GET_RSP_SIZE] = {   
0xE7, 0x00,                      /* APDU CHOICE Type (PrstApdu) */
0x00, 0x6E,                      /* CHOICE.length = 110*/
0x00, 0x6C,                      /* OCTET STRING.length = 108 */
0x00, 0x02,                      /* invoke-id =0x0002 (mirrored from request)*/
0x02, 0x03,                      /* CHOICE (Remote Operation Response | Get)*/
0x00, 0x66,                      /* CHOICE.length = 102                     */
0x00, 0x00,                      /* handle = 0 (MDS object)                */
0x00, 0x06,                      /* attribute-list.count = 6               */
0x00, 0x60,                      /* attribute-list.length = 96              */
0x0A, 0x5A,                      /* attribute id=MDC_ATTR_SYS_TYPE_SPEC_LIS */         
0x00, 0x08,                      /* attribute-value.length = 8              */
0x00, 0x01,                      /* TypeVerList count = 1                   */
0x00, 0x04,                      /* TypeVerList length = 4                  */
0x10, 0x07,                      /* type = MDC_DEV_SPEC_PROFILE_BP  */
0x00, 0x01,                      /* version=ver 1 of the specialization  */
0x09, 0x28,                      /* attribute-id = MDC_ATTR_ID_MODEL    */
0x00, 0x1A,                      /* attribute-value.length = 24        */
0x00, 0x0A, 0x46, 0x72,          /* string length = 10 | TheCompany  */
0x65, 0x65, 0x73, 0x63,                                                     
0x61, 0x6C, 0x65, 0x20,
0x00, 0x0C, 0x4D, 0x65,          /* string length = 12 | BPM */
0x64, 0x69, 0x63, 0x61,
0x6C, 0x20, 
#ifdef _MCF51JM128_H
0x43, 0x46, 0x56, 0x31,
#elif defined _MC9S08JM60_H
0x4A, 0x4D, 0x36, 0x30,
#elif defined _MC9S08JM16_H
0x4A, 0x4D, 0x31, 0x36,
#elif defined _MC9S08JS16_H
0x4A, 0x53, 0x31, 0x36,
#elif defined _MCF51MM256_H
'M', 'M', '2', '5',
#elif defined _MC9S08MM128_H
'M', 'M', '1', '2',
#elif defined _MCF51JE256_H
'J', 'E', '2', '5',
#elif defined _MC9S08JE128_H
'J', 'E', '1', '2',
#elif defined __MCF52xxx_H__
'C', 'F', 'V', '2',
#elif (defined MCU_MK20D5) || (defined MCU_MK20D7)
'M', 'K', '2', '0',
#elif (defined MCU_MK21D5)
'M', 'K', '2', '1',
#elif (defined MCU_MK40N512VMD100) || (defined MCU_MK40D7)
'M', 'K', '4', '0',
#elif defined MCU_MK53N512CMD100
'M', 'K', '5', '3',
#elif defined MCU_MK60N512VMD100
'M', 'K', '6', '0',
#elif defined MCU_MK70F12
'M', 'K', '7', '0',
#elif defined MCU_mcf51jf128
'J', 'F', '1', '2',
#elif defined MCU_MKL25Z4
'L', '2', 'K', ' ',
#else
#error "No device configuration"
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
uint_8  USB_CONST PHD_BPM_DIM_DATA_TX[PHD_BPM_DIM_DATA_TX_SIZE] = {   
0xE7, 0x00, /*APDU CHOICE Type (PrstApdu)*/
0x00, 0x3E, /*CHOICE.length = 62*/
0x00, 0x3C, /*OCTET STRING.length = 60 */
0x12, 0x36, /*invoke-id = 0x1236*/
0x01, 0x01, /*CHOICE(Remote Operation Invoke | Confirmed Event Report)*/
0x00, 0x36, /*CHOICE.length = 54*/
0x00, 0x00, /*obj-handle = 0 (MDS object)*/
0x00, 0x00, 0x00, 0x00, /*event-time = 0*/
0x0D, 0x1D, /*event-type = MDC_NOTI_SCAN_REPORT_FIXED*/
0x00, 0x2C, /*event-info.length = 44*/
0xF0, 0x00, /*ScanReportInfoFixed.data-req-id = 0xF000*/
0x00, 0x00, /*ScanReportInfoFixed.scan-report-no = 0*/
0x00, 0x02, /*ScanReportInfoFixed.obs-scan-fixed.count = 2*/
0x00, 0x24, /*ScanReportInfoFixed.obs-scan-fixed.length = 36*/
0x00, 0x01, /*ScanReportInfoFixed.obs-scan-fixed.value[0].obj-handle = 1*/
0x00, 0x12, /*ScanReportInfoFixed.obs-scan-fixed.value[0]. obs-val-data.length 
              = 18*/
0x00, 0x03, /* Compound Object count (3 entries) */
0x00, 0x06, /* Compound Object length (6 bytes)  */
0x00, 0x78, /* Systolic = 120 */
0x00, 0x50, /* Diastolic = 80  */
0x00, 0x64, /* MAP = 100 */
0x20, 0x09, 0x06, 0x12, /*Absolute-Time-Stamp = 2009-06-12T20:05:0000*/
0x12, 0x10, 0x00, 0x00,
0x00, 0x02, /*ScanReportInfoFixed.obs-scan-fixed.value[1].obj-handle = 2*/
0x00, 0x0A, /*ScanReportInfoFixed.obs-scan-fixed.value[1]. obs-val-data.length 
                = 10*/
0xF2, 0x58,  /*Basic-Nu-Observed-Value = 60.0 (BPM) */
0x20, 0x09, 0x06, 0x12, /*Absolute-Time-Stamp = 2009-06-12T20:05:0000*/
0x20, 0x10, 0x00, 0x00
};

/* THERMOMETER */

/* association request to send */ 
uint_8 USB_CONST PHD_THERMO_ASSOC_REQ[ASSOC_REQ_SIZE] = {   
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
uint_8 USB_CONST PHD_THERMO_CNFG_EVT_RPT[PHD_THERMO_CNFG_EVT_RPT_SIZE] = {   
0xE7, 0x00,                           /* APDU CHOICE Type (PrstApdu) */
0x00, 0x44,                           /* CHOICE.length = 68 */
0x00, 0x42,                           /* OCTET STRING.length = 70 */
0x00, 0x03,                           /*  invoke-id = 0x1235 (start of DataApdu
                                          . MDER encoded.) */ 
0x01, 0x01,                           /*  CHOICE(Remote Operation Invoke | 
                                          Confirmed Event Report) */
0x00, 0x3C,                           /*  CHOICE.length = 60 */
0x00, 0x00,                           /*  obj-handle = 0 (MDS object) */
0xFF, 0xFF, 0xFF, 0xFF,               /*  event-time = 0xFFFFFFFF    */
0x0D, 0x1C,                           /*  event-type = MDC_NOTI_CONFIG */
0x00, 0x32,                           /*  event-info.length = 50 (start of 
                                          ConfigReport) */
0x03, 0x20,                           /*  config-report-id */ 
0x00, 0x01,                           /*  config-obj-list.count = 1 Measurement
                                          objects will be announced */
0x00, 0x2C,                           /*  config-obj-list.length = 44 */
0x00, 0x06,                           /*  obj-class = MDC_MOC_VMO_METRIC_NU */
0x00, 0x01,                           /*  obj-handle = 1 (.. 1st Measurement is
                                          temperature) */
0x00, 0x04,                           /*  attributes.count = 4  */
0x00, 0x24,                           /*  attributes.length = 36  */
0x09, 0x2F,                           /*  attribute-id = MDC_ATTR_ID_TYPE */
0x00, 0x04,                           /*  attribute-value.length = 4      */
0x00, 0x02, 0x4B, 0x5C,               /*  MDC_PART_SCADA |  
                                          MDC_TEMP_BODY */ 
0x0A, 0x46,                           /*  attribute-id = 
                                          MDC_ATTR_METRIC_SPEC_SMALL      */
0x00, 0x02,                           /*  attribute-value.length = 2  */
0xF0, 0x40,                           
0x09, 0x96,                           /*  attribute-id = MDC_ATTR_UNIT_CODE */
0x00, 0x02,                           /*  attribute-value.length = 2 */
0x17, 0xA0,                           /*  MDC_DIM_DEGC     */
0x0A, 0x55,                           /*  attribute-id = 
                                          MDC_ATTR_ATTRIBUTE_VAL_MAP  */
0x00, 0x0C,                           /*  attribute-value.length = 16     */
0x00, 0x02,                           /*  AttrValMap.count = 2         */
0x00, 0x08,                           /*  AttrValMap.length = 8          */
0x0A, 0x56, 0x00, 0x04,               /*  MDC_ATTR_NU_VAL_OBS_SIMP, 4   */
0x09, 0x90, 0x00, 0x08                /*  MDC_ATTR_TIME_STAMP_ABS, 8   */
};       

/* release request to send */
uint_8 USB_CONST PHD_THERMO_REL_REQ[REL_REQ_SIZE] = {   
0xE4, 0x00,                           /* APDU CHOICE Type (RlrqApdu) */
0x00, 0x02,                           /* CHOICE.length = 2 */
0x00, 0x00                            /* reason = normal */
};

/* release response to the host */
uint_8 USB_CONST PHD_THERMO_REL_RES[REL_RES_SIZE] = {   
0xE5, 0x00,                           /* APDU CHOICE Type (RlrsApdu) */
0x00, 0x02,                           /* CHOICE.length = 2 */
0x00, 0x00                            /* reason = normal */
};

/* response to get attributes command */
uint_8 USB_CONST PHD_THERMO_DIM_GET_RSP[PHD_THERMO_DIM_GET_RSP_SIZE] = {   
0xE7, 0x00,                      /* APDU CHOICE Type (PrstApdu) */
0x00, 0x58,                      /* CHOICE.length = 88 */
0x00, 0x56,                      /* OCTET STRING.length = 86 */
0x00, 0x02,                      /* invoke-id =0x0002 (mirrored from request)*/
0x02, 0x03,                      /* CHOICE (Remote Operation Response | Get)*/
0x00, 0x50,                      /* CHOICE.length = 80                     */
0x00, 0x00,                      /* handle = 0 (MDS object)                */
0x00, 0x05,                      /* attribute-list.count = 5               */
0x00, 0x4A,                      /* attribute-list.length = 74              */
0x0A, 0x5A,                      /* attribute id=MDC_ATTR_SYS_TYPE_SPEC_LIST */         
0x00, 0x08,                      /* attribute-value.length = 8              */
0x00, 0x01,                      /* TypeVerList count = 1                   */
0x00, 0x04,                      /* TypeVerList length = 4                  */
0x10, 0x08,                      /* type = MDC_DEV_SPEC_PROFILE_TEMP  */
0x00, 0x01,                      /* version=ver 1 of the specialization  */
0x09, 0x28,                      /* attribute-id = MDC_ATTR_ID_MODEL    */
0x00, 0x1A,                      /* attribute-value.length = 26        */
0x00, 0x0A, 0x46, 0x72,          /* string length = 10 | TheCompany  */
0x65, 0x65, 0x73, 0x63,                                                     
0x61, 0x6C, 0x65, 0x20,
0x00, 0x0C, 0x4D, 0x65,          /* string length = 12 | Thermometer\0    */
0x64, 0x69, 0x63, 0x61,
0x6C, 0x20, 
#ifdef _MCF51JM128_H
0x43, 0x46, 0x56, 0x31,
#elif defined _MC9S08JM60_H
0x4A, 0x4D, 0x36, 0x30,
#elif defined _MC9S08JM16_H
0x4A, 0x4D, 0x31, 0x36,
#elif defined _MC9S08JS16_H
0x4A, 0x53, 0x31, 0x36,
#elif defined _MCF51MM256_H
'M', 'M', '2', '5',
#elif defined _MC9S08MM128_H
'M', 'M', '1', '2',
#elif defined _MCF51JE256_H
'J', 'E', '2', '5',
#elif defined _MC9S08JE128_H
'J', 'E', '1', '2',
#elif defined __MCF52xxx_H__
'C', 'F', 'V', '2',
#elif (defined MCU_MK20D5) || (defined MCU_MK20D7)
'M', 'K', '2', '0',
#elif (defined MCU_MK21D5)
'M', 'K', '2', '1',
#elif (defined MCU_MK40N512VMD100) || (defined MCU_MK40D7)
'M', 'K', '4', '0',
#elif defined MCU_MK53N512CMD100
'M', 'K', '5', '3',
#elif defined MCU_MK60N512VMD100
'M', 'K', '6', '0',
#elif defined MCU_MK70F12
'M', 'K', '7', '0',
#elif defined MCU_mcf51jf128
'J', 'F', '1', '2',
#elif defined MCU_MKL25Z4
'L', '2', 'K', ' ',
#else
#error "No device configuration"
#endif
0x09, 0x84,                      /* attribute-id = MDC_ATTR_SYS_ID        */
0x00, 0x0A,                      /* attribute-value.length = 10            */
0x00, 0x08, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 
                                 /* octet string length = 8 | EUI-64  */
0x0a, 0x44,                      /* attribute-id = MDC_ATTR_DEV_CONFIG_ID   */
0x00, 0x02,                      /* attribute-value.length = 2             */
0x40, 0x00,                      /* dev-config-id = 16384 
                                    (extended-config-start)*/
0x09, 0x87,                      /* attribute-id = MDC_ATTR_TIME_ABS */
0x00, 0x08,                      /* attribute-value.length = 8           */
0x20, 0x09, 0x06, 0x12,          /* Absolute-Time-Stamp=2009-06-12T12:05:0000*/
0x08, 0x00, 0x00, 0x00                                                               
};  

/* measurements to send */
uint_8  USB_CONST PHD_THERMO_DIM_DATA_TX[PHD_THERMO_DIM_DATA_TX_SIZE] = {   
0xE7, 0x00, /*APDU CHOICE Type (PrstApdu)*/
0x00, 0x2A, /*CHOICE.length = 42*/
0x00, 0x28, /*OCTET STRING.length = 40*/
0x12, 0x36, /*invoke-id = 0x1236*/
0x01, 0x01, /*CHOICE(Remote Operation Invoke | Confirmed Event Report)*/
0x00, 0x22, /*CHOICE.length = 34*/
0x00, 0x00, /*obj-handle = 0 (MDS object)*/
0x00, 0x00, 0x00, 0x00, /*event-time = 0*/
0x0D, 0x1D, /*event-type = MDC_NOTI_SCAN_REPORT_FIXED*/
0x00, 0x18, /*event-info.length = 24*/
0xF0, 0x00, /*ScanReportInfoFixed.data-req-id = 0xF000*/
0x00, 0x00, /*ScanReportInfoFixed.scan-report-no = 0*/
0x00, 0x01, /*ScanReportInfoFixed.obs-scan-fixed.count = 1*/
0x00, 0x10, /*ScanReportInfoFixed.obs-scan-fixed.length = 16*/
0x00, 0x01, /*ScanReportInfoFixed.obs-scan-fixed.value[0].obj-handle = 1*/
0x00, 0x0C, /*ScanReportInfoFixed.obs-scan-fixed.value[0]. obs-val-data.length 
              = 12*/
0xFB, 0x38, 0x75, 0x20, /*Simple-Nu-Observed-Value = 37.0 (Degrees C) */
0x20, 0x09, 0x06, 0x12, /* Absolute-Time-Stamp=2009-06-12T12:05:0000*/
0x08, 0x30, 0x00, 0x00
};

PHD_CNF_PARAM const g_phd_cnf_param[MAX_DEV_SPEC_SUPPORTED] = 
{
	{
		(uint_8_ptr)PHD_WSL_ASSOC_REQ,
		(uint_8_ptr)PHD_WSL_CNFG_EVT_RPT,
		PHD_WSL_CNFG_EVT_RPT_SIZE,
		(uint_8_ptr)PHD_WSL_REL_REQ,
		(uint_8_ptr)PHD_WSL_REL_RES,
		(uint_8_ptr)PHD_WSL_DIM_GET_RSP,
		PHD_WSL_DIM_GET_RSP_SIZE,
		0x4004,//0x05DC,
		PHD_Send_WSL_Measurements_to_Manager,
	},
	{
		(uint_8_ptr)PHD_GLUCO_ASSOC_REQ,
		(uint_8_ptr)PHD_GLUCO_CNFG_EVT_RPT,
		PHD_GLUCO_CNFG_EVT_RPT_SIZE,
		(uint_8_ptr)PHD_GLUCO_REL_REQ,
		(uint_8_ptr)PHD_GLUCO_REL_RES,
		(uint_8_ptr)PHD_GLUCO_DIM_GET_RSP,
		PHD_GLUCO_DIM_GET_RSP_SIZE,
		0x4005,//0x06A4,
		PHD_Send_GLUCO_Measurements_to_Manager,
	},
	{
		(uint_8_ptr)PHD_BPM_ASSOC_REQ,
		(uint_8_ptr)PHD_BPM_CNFG_EVT_RPT,
		PHD_BPM_CNFG_EVT_RPT_SIZE,
		(uint_8_ptr)PHD_BPM_REL_REQ,
		(uint_8_ptr)PHD_BPM_REL_RES,
		(uint_8_ptr)PHD_BPM_DIM_GET_RSP,
		PHD_BPM_DIM_GET_RSP_SIZE,
		0x02BC,
		PHD_Send_BPM_Measurements_to_Manager,
	},
	{
		(uint_8_ptr)PHD_THERMO_ASSOC_REQ,
		(uint_8_ptr)PHD_THERMO_CNFG_EVT_RPT,
		PHD_THERMO_CNFG_EVT_RPT_SIZE,
		(uint_8_ptr)PHD_THERMO_REL_REQ,
		(uint_8_ptr)PHD_THERMO_REL_RES,
		(uint_8_ptr)PHD_THERMO_DIM_GET_RSP,
		PHD_THERMO_DIM_GET_RSP_SIZE,
		0x0320,
		PHD_Send_THERMO_Measurements_to_Manager,
	},
};

#ifdef _MC9S08JS16_H
#pragma DATA_SEG DEFAULT
#endif
PHD_MEASUREMENT msr;                           

uint_16 scanReportNo;

/******************************************************************************
 *
 *    @name        PHD_Send_WSL_Measurements_to_Manager
 *
 *    @brief       This function is called by the com model when the device 
 *                 specialization selected is Weigh Scale
 *
 *    @param       controller_ID : Controller ID
 *    @param       buffer_ptr    : Measurement buffer
 *    @param       size          : Buffer size
 * 
 *    @return      None
 *
 *****************************************************************************
 * This function when called updates the weigh scale measurements 
 *****************************************************************************/
static void PHD_Send_WSL_Measurements_to_Manager (
    uint_8 controller_ID,       /* [IN] Controller ID */    
    void* buffer_ptr,           /* [IN] Measurement buffer */
    void* size                  /* [IN] Buffer size */
)
{
	uint_8 i=0;
	uint_8_ptr send_buff = (uint_8_ptr)buffer_ptr;

  DATA_apdu *dataApdu = (DATA_apdu *)&(((PRST_apdu *)&((APDU *)send_buff)->u.prst)->value[0]);
  ScanReportInfoFixed *scan_rep = (ScanReportInfoFixed *)&(dataApdu->choice.u.roiv_cmipConfirmedEventReport.event_info.value[0]);	
	
	UNUSED(controller_ID)
	*(USB_PACKET_SIZE *)size = PHD_WSL_DIM_DATA_TX_SIZE;
	/* copy the measurements to send in the phd_buffer */
	(void)memcpy(send_buff, PHD_WSL_DIM_DATA_TX, PHD_WSL_DIM_DATA_TX_SIZE);

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

/******************************************************************************
 *
 *    @name        PHD_Send_GLUCO_Measurements_to_Manager
 *
 *    @brief       This function is called by the com model when the device 
 *                 specialization selected is Glucose Meter
 *
 *    @param       controller_ID : Controller ID
 *    @param       buffer_ptr    : Measurement buffer
 *    @param       size          : Buffer size
 * 
 *    @return      None
 *
 *****************************************************************************
 * This function when called updates the glucose measurements 
 *****************************************************************************/
static void PHD_Send_GLUCO_Measurements_to_Manager (
    uint_8 controller_ID,       /* [IN] Controller ID */    
    void* buffer_ptr,           /* [IN] Measurement buffer */
    void* size                  /* [IN] Buffer size */
)
{
	uint_8 i=0;
	uint_8_ptr send_buff = (uint_8_ptr)buffer_ptr;

  DATA_apdu *dataApdu = (DATA_apdu *)&(((PRST_apdu *)&((APDU *)send_buff)->u.prst)->value[0]);
  ScanReportInfoFixed *scan_rep = (ScanReportInfoFixed *)&(dataApdu->choice.u.roiv_cmipConfirmedEventReport.event_info.value[0]);	
	
    UNUSED(controller_ID)
	
	*(USB_PACKET_SIZE *)size = PHD_GLUCO_DIM_DATA_TX_SIZE;

	(void)memcpy(send_buff, PHD_GLUCO_DIM_DATA_TX, 
		PHD_GLUCO_DIM_DATA_TX_SIZE);

  /* update the scan report no */
  scan_rep->scan_report_no = scanReportNo++;

	/* set measurement  */
	for(i = 0; i < 2; i++)
	{
		msr.msr_time.second++;
		msr.msr_time.second %= 60;
		send_buff[42+i*14] = msr.msr_time.second;
	}
	for(i = 0; i < 3; i++)
	{
		send_buff[68+i*14] = msr.msr_time.second;
	}

	for(i=0;i<2;i++)
	{
		msr.weight[i] += 5;                
		msr.weight[i] %= 1000;
		send_buff[35+i*14] = (uint_8)((msr.weight[i]) & 0x00FF);
	}
}

/******************************************************************************
 *
 *    @name        PHD_Send_BPM_Measurements_to_Manager
 *
 *    @brief       This function is called by the com model when the device 
 *                 specialization selected is Blood Pressure Monitor
 *
 *    @param       controller_ID : Controller ID
 *    @param       buffer_ptr    : Measurement buffer
 *    @param       size          : Buffer size
 * 
 *    @return      None
 *
 *****************************************************************************
 * This function when called updates the blood pressure measurements 
 *****************************************************************************/
static void PHD_Send_BPM_Measurements_to_Manager (
    uint_8 controller_ID,       /* [IN] Controller ID */    
    void* buffer_ptr,           /* [IN] Measurement buffer */
    void* size                  /* [IN] Buffer size */
)
{
	uint_8 i=0;
	uint_8_ptr send_buff = (uint_8_ptr)buffer_ptr;

  DATA_apdu *dataApdu = (DATA_apdu *)&(((PRST_apdu *)&((APDU *)send_buff)->u.prst)->value[0]);
  ScanReportInfoFixed *scan_rep = (ScanReportInfoFixed *)&(dataApdu->choice.u.roiv_cmipConfirmedEventReport.event_info.value[0]);	
	
    UNUSED(controller_ID)        
	*(USB_PACKET_SIZE *)size = PHD_BPM_DIM_DATA_TX_SIZE;
	(void)memcpy(send_buff, PHD_BPM_DIM_DATA_TX, PHD_BPM_DIM_DATA_TX_SIZE);

  /* update the scan report no */
  scan_rep->scan_report_no = scanReportNo++;

	/* set measurement  */
	for(i = 0; i < 2; i++)
	{
		msr.msr_time.second++;
		msr.msr_time.second %= 60;
		send_buff[50+i*14] = msr.msr_time.second;
	}

	for(i=0;i<2;i++)
	{
		msr.weight[i]++;                
		msr.weight[i] %= 250;
		send_buff[38+i*2] = (uint_8)((msr.weight[i] >> 8) & 0x00FF);
		send_buff[39+i*2] = (uint_8)((msr.weight[i]) & 0x00FF);
	}
	send_buff[43] = (uint_8)((send_buff[39] + send_buff[41])/2);
	msr.bmi[0]++;   
	send_buff[57] = (uint_8)((msr.bmi[0]) & 0x00FF);     
}
/******************************************************************************
 *
 *    @name        PHD_Send_THERMO_Measurements_to_Manager
 *
 *    @brief       This function is called by the com model when the device 
 *                 specialization selected is Thermometer
 *
 *    @param       controller_ID : Controller ID
 *    @param       buffer_ptr    : Measurement buffer
 *    @param       size          : Buffer size
 * 
 *    @return      None
 *
 *****************************************************************************
 * This function when called updates the temperature measurements 
 *****************************************************************************/
static void PHD_Send_THERMO_Measurements_to_Manager (
    uint_8 controller_ID,       /* [IN] Controller ID */    
    void* buffer_ptr,           /* [IN] Measurement buffer */
    void* size                  /* [IN] Buffer size */
)
{
	uint_8_ptr send_buff = (uint_8_ptr)buffer_ptr;

  DATA_apdu *dataApdu = (DATA_apdu *)&(((PRST_apdu *)&((APDU *)send_buff)->u.prst)->value[0]);
  ScanReportInfoFixed *scan_rep = (ScanReportInfoFixed *)&(dataApdu->choice.u.roiv_cmipConfirmedEventReport.event_info.value[0]);	

	
	UNUSED(controller_ID)

	*(USB_PACKET_SIZE *)size = PHD_THERMO_DIM_DATA_TX_SIZE;
	(void)memcpy(send_buff, PHD_THERMO_DIM_DATA_TX, 
		PHD_THERMO_DIM_DATA_TX_SIZE);

  /* update the scan report no */
  scan_rep->scan_report_no = scanReportNo++;
  		
	/* set measurement  */
	msr.msr_time.second++;
	msr.msr_time.second %= 60;
	send_buff[44] = msr.msr_time.second;

	msr.weight[0] += 0x0f00;                
	send_buff[36] = (uint_8)((msr.weight[0] >> 8) & 0x00FF);
	send_buff[37] = (uint_8)((msr.weight[0]) & 0x00FF);
}

