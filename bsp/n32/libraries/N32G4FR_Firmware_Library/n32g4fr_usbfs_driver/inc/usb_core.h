/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file usb_core.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#ifndef __USB_CORE_H__
#define __USB_CORE_H__

#include "n32g4fr.h"

/**
 * @addtogroup N32G4FR_USB_Driver
 * @brief N32G4FR USB low level driver
 * @{
 */

typedef enum _CONTROL_STATE
{
    WaitSetup,      /* 0 */
    SettingUp,      /* 1 */
    InData,         /* 2 */
    OutData,        /* 3 */
    LastInData,     /* 4 */
    LastOutData,    /* 5 */
    WaitStatusIn,   /* 7 */
    WaitStatusOut,  /* 8 */
    Stalled,        /* 9 */
    Pause           /* 10 */
} USB_ControlState; /* The state machine states of a control pipe */

typedef struct OneDescriptor
{
    uint8_t* Descriptor;
    uint16_t Descriptor_Size;
} USB_OneDescriptor, *PONE_DESCRIPTOR;
/* All the request process routines return a value of this type
   If the return value is not SUCCESS or NOT_READY,
   the software will STALL the correspond endpoint */
typedef enum _RESULT
{
    Success = 0, /* Process successfully */
    Error,
    UnSupport,
    Not_Ready /* The process has not been finished, endpoint will be
                     NAK to further request */
} USB_Result;

/*-*-*-*-*-*-*-*-*-*-* Definitions for endpoint level -*-*-*-*-*-*-*-*-*-*-*-*/
typedef struct _ENDPOINT_INFO
{
    /* When send data out of the device,
     CopyData() is used to get data buffer 'Length' bytes data
     if Length is 0,
      CopyData() returns the total length of the data
      if the request is not supported, returns 0
      (NEW Feature )
       if CopyData() returns -1, the calling routine should not proceed
       further and will resume the SETUP process by the class device
     if Length is not 0,
      CopyData() returns a pointer to indicate the data location
     Usb_wLength is the data remain to be sent,
     Usb_wOffset is the Offset of original data
    When receive data from the host,
     CopyData() is used to get user data buffer which is capable
     of Length bytes data to copy data from the endpoint buffer.
     if Length is 0,
      CopyData() returns the available data length,
     if Length is not 0,
      CopyData() returns user buffer address
     Usb_rLength is the data remain to be received,
     Usb_rPointer is the Offset of data buffer
    */
    uint16_t Usb_wLength;
    uint16_t Usb_wOffset;
    uint16_t PacketSize;
    uint8_t* (*CopyData)(uint16_t Length);
} USB_EndpointMess;

/*-*-*-*-*-*-*-*-*-*-*-* Definitions for device level -*-*-*-*-*-*-*-*-*-*-*-*/

typedef struct _DEVICE
{
    uint8_t TotalEndpoint;      /* Number of endpoints that are used */
    uint8_t TotalConfiguration; /* Number of configuration available */
} USB_Device;

typedef union
{
    uint16_t w;
    struct BW
    {
        uint8_t bb1;
        uint8_t bb0;
    } bw;
} uint16_t_uint8_t;

typedef struct _DEVICE_INFO
{
    uint8_t bmRequestType;     /* bmRequestType */
    uint8_t bRequest;          /* bRequest */
    uint16_t_uint8_t wValues;  /* wValue */
    uint16_t_uint8_t wIndexs;  /* wIndex */
    uint16_t_uint8_t wLengths; /* wLength */

    uint8_t CtrlState; /* of type USB_ControlState */
    uint8_t CurrentFeature;
    uint8_t CurrentConfiguration;    /* Selected configuration */
    uint8_t CurrentInterface;        /* Selected interface of current configuration */
    uint8_t CurrentAlternateSetting; /* Selected Alternate Setting of current
                                        interface*/

    USB_EndpointMess Ctrl_Info;
} USB_DeviceMess;

typedef struct _DEVICE_PROP
{
    void (*Init)(void);  /* Initialize the device */
    void (*Reset)(void); /* Reset routine of this device */

    /* Device dependent process after the status stage */
    void (*Process_Status_IN)(void);
    void (*Process_Status_OUT)(void);

    /* Procedure of process on setup stage of a class specified request with data stage */
    /* All class specified requests with data stage are processed in Class_Data_Setup
     Class_Data_Setup()
      responses to check all special requests and fills USB_EndpointMess
      according to the request
      If IN tokens are expected, then wLength & wOffset will be filled
      with the total transferring bytes and the starting position
      If OUT tokens are expected, then rLength & rOffset will be filled
      with the total expected bytes and the starting position in the buffer

      If the request is valid, Class_Data_Setup returns SUCCESS, else UNSUPPORT

     CAUTION:
      Since GET_CONFIGURATION & GET_INTERFACE are highly related to
      the individual classes, they will be checked and processed here.
    */
    USB_Result (*Class_Data_Setup)(uint8_t RequestNo);

    /* Procedure of process on setup stage of a class specified request without data stage */
    /* All class specified requests without data stage are processed in Class_NoData_Setup
     Class_NoData_Setup
      responses to check all special requests and perform the request

     CAUTION:
      Since SET_CONFIGURATION & SET_INTERFACE are highly related to
      the individual classes, they will be checked and processed here.
    */
    USB_Result (*Class_NoData_Setup)(uint8_t RequestNo);

    /*Class_Get_Interface_Setting
     This function is used by the file usb_core.c to test if the selected Interface
     and Alternate Setting (uint8_t Interface, uint8_t AlternateSetting) are supported by
     the application.
     This function is writing by user. It should return "SUCCESS" if the Interface
     and Alternate Setting are supported by the application or "UNSUPPORT" if they
     are not supported. */

    USB_Result (*Class_Get_Interface_Setting)(uint8_t Interface, uint8_t AlternateSetting);

    uint8_t* (*GetDeviceDescriptor)(uint16_t Length);
    uint8_t* (*GetConfigDescriptor)(uint16_t Length);
    uint8_t* (*GetStringDescriptor)(uint16_t Length);

    /* This field is not used in current library version. It is kept only for
     compatibility with previous versions */
    void* RxEP_buffer;

    uint8_t MaxPacketSize;

} DEVICE_PROP;

typedef struct _USER_STANDARD_REQUESTS
{
    void (*User_GetConfiguration)(void);   /* Get Configuration */
    void (*User_SetConfiguration)(void);   /* Set Configuration */
    void (*User_GetInterface)(void);       /* Get Interface */
    void (*User_SetInterface)(void);       /* Set Interface */
    void (*User_GetStatus)(void);          /* Get Status */
    void (*User_ClearFeature)(void);       /* Clear Feature */
    void (*User_SetEndPointFeature)(void); /* Set Endpoint Feature */
    void (*User_SetDeviceFeature)(void);   /* Set Device Feature */
    void (*User_SetDeviceAddress)(void);   /* Set Device Address */
} USER_STANDARD_REQUESTS;

#define Type_Recipient (pInformation->bmRequestType & (REQUEST_TYPE | RECIPIENT))

#define Usb_rLength Usb_wLength
#define Usb_rOffset Usb_wOffset

#define USBwValue   wValues.w
#define USBwValue0  wValues.bw.bb0
#define USBwValue1  wValues.bw.bb1
#define USBwIndex   wIndexs.w
#define USBwIndex0  wIndexs.bw.bb0
#define USBwIndex1  wIndexs.bw.bb1
#define USBwLength  wLengths.w
#define USBwLength0 wLengths.bw.bb0
#define USBwLength1 wLengths.bw.bb1

uint8_t USB_ProcessSetup0(void);
uint8_t USB_ProcessPost0(void);
uint8_t USB_ProcessOut0(void);
uint8_t USB_ProcessIn0(void);

USB_Result Standard_SetEndPointFeature(void);
USB_Result Standard_SetDeviceFeature(void);

uint8_t* Standard_GetConfiguration(uint16_t Length);
USB_Result Standard_SetConfiguration(void);
uint8_t* Standard_GetInterface(uint16_t Length);
USB_Result Standard_SetInterface(void);
uint8_t* Standard_GetDescriptorData(uint16_t Length, PONE_DESCRIPTOR pDesc);

uint8_t* Standard_GetStatus(uint16_t Length);
USB_Result Standard_ClearFeature(void);
void USB_SetDeviceAddress(uint8_t);
void USB_ProcessNop(void);

extern DEVICE_PROP Device_Property;
extern USER_STANDARD_REQUESTS User_Standard_Requests;
extern USB_Device Device_Table;
extern USB_DeviceMess Device_Info;

/* cells saving status during interrupt servicing */
extern __IO uint16_t SaveRState;
extern __IO uint16_t SaveTState;

/**
 * @}
 */

#endif /* __USB_CORE_H__ */
