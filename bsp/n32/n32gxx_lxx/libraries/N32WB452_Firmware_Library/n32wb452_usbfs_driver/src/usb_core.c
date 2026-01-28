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
 * @file usb_core.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include "usb_lib.h"

#define ValBit(VAR, Place) (VAR & (1 << Place))
#define SetBit(VAR, Place) (VAR |= (1 << Place))
#define ClrBit(VAR, Place) (VAR &= ((1 << Place) ^ 255))

#define Send0LengthData()                                                                                              \
    {                                                                                                                  \
        _SetEPTxCount(ENDP0, 0);                                                                                       \
        vSetEPTxStatus(EP_TX_VALID);                                                                                   \
    }

#define vSetEPRxStatus(st) (SaveRState = st)
#define vSetEPTxStatus(st) (SaveTState = st)

#define USB_StatusIn()  Send0LengthData()
#define USB_StatusOut() vSetEPRxStatus(EP_RX_VALID)

#define StatusInfo0 StatusInfo.bw.bb1 /* Reverse bb0 & bb1 */
#define StatusInfo1 StatusInfo.bw.bb0

uint16_t_uint8_t StatusInfo;

bool Data_Mul_MaxPacketSize = false;

static void DataStageOut(void);
static void DataStageIn(void);
static void NoData_Setup0(void);
static void Data_Setup0(void);

/**
 * @brief Return the current configuration variable address.
 * Input          : Length - How many bytes are needed.
 * @return Return 1 , if the request is invalid when "Length" is 0.
 *                  Return "Buffer" if the "Length" is not 0.
 */
uint8_t* Standard_GetConfiguration(uint16_t Length)
{
    if (Length == 0)
    {
        pInformation->Ctrl_Info.Usb_wLength = sizeof(pInformation->CurrentConfiguration);
        return 0;
    }
    pUser_Standard_Requests->User_GetConfiguration();
    return (uint8_t*)&pInformation->CurrentConfiguration;
}

/**
 * @brief This routine is called to set the configuration value
 *                  Then each class should configure device itself.
 * @return
 * - Success, if the request is performed.
 * - UnSupport, if the request is invalid.
 */
USB_Result Standard_SetConfiguration(void)
{
    if ((pInformation->USBwValue0 <= Device_Table.TotalConfiguration) && (pInformation->USBwValue1 == 0)
        && (pInformation->USBwIndex == 0)) /*call Back usb spec 2.0*/
    {
        pInformation->CurrentConfiguration = pInformation->USBwValue0;
        pUser_Standard_Requests->User_SetConfiguration();
        return Success;
    }
    else
    {
        return UnSupport;
    }
}

/**
 * @brief Return the Alternate Setting of the current interface.
 * Input          : Length - How many bytes are needed.
 * @return
 * - NULL, if the request is invalid when "Length" is 0.
 * - "Buffer" if the "Length" is not 0.
 */
uint8_t* Standard_GetInterface(uint16_t Length)
{
    if (Length == 0)
    {
        pInformation->Ctrl_Info.Usb_wLength = sizeof(pInformation->CurrentAlternateSetting);
        return 0;
    }
    pUser_Standard_Requests->User_GetInterface();
    return (uint8_t*)&pInformation->CurrentAlternateSetting;
}

/**
 * @brief This routine is called to set the interface.
 *                  Then each class should configure the interface them self.
 * @return
 * - Success, if the request is performed.
 * - UnSupport, if the request is invalid.
 */
USB_Result Standard_SetInterface(void)
{
    USB_Result Re;
    /*Test if the specified Interface and Alternate Setting are supported by
      the application Firmware*/
    Re = (*pProperty->Class_Get_Interface_Setting)(pInformation->USBwIndex0, pInformation->USBwValue0);

    if (pInformation->CurrentConfiguration != 0)
    {
        if ((Re != Success) || (pInformation->USBwIndex1 != 0) || (pInformation->USBwValue1 != 0))
        {
            return UnSupport;
        }
        else if (Re == Success)
        {
            pUser_Standard_Requests->User_SetInterface();
            pInformation->CurrentInterface        = pInformation->USBwIndex0;
            pInformation->CurrentAlternateSetting = pInformation->USBwValue0;
            return Success;
        }
    }

    return UnSupport;
}

/**
 * @brief Copy the device request data to "StatusInfo buffer".
 * Input          : - Length - How many bytes are needed.
 * @return Return 0, if the request is at end of data block,
 *                  or is invalid when "Length" is 0.
 */
uint8_t* Standard_GetStatus(uint16_t Length)
{
    if (Length == 0)
    {
        pInformation->Ctrl_Info.Usb_wLength = 2;
        return 0;
    }

    /* Reset Status Information */
    StatusInfo.w = 0;

    if (Type_Recipient == (STANDARD_REQUEST | DEVICE_RECIPIENT))
    {
        /*Get Device Status */
        uint8_t Feature = pInformation->CurrentFeature;

        /* Remote Wakeup enabled */
        if (ValBit(Feature, 5))
        {
            SetBit(StatusInfo0, 1);
        }
        else
        {
            ClrBit(StatusInfo0, 1);
        }

        /* Bus-powered */
        if (ValBit(Feature, 6))
        {
            SetBit(StatusInfo0, 0);
        }
        else /* Self-powered */
        {
            ClrBit(StatusInfo0, 0);
        }
    }
    /*Interface Status*/
    else if (Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT))
    {
        return (uint8_t*)&StatusInfo;
    }
    /*Get EndPoint Status*/
    else if (Type_Recipient == (STANDARD_REQUEST | ENDPOINT_RECIPIENT))
    {
        uint8_t Related_Endpoint;
        uint8_t wIndex0 = pInformation->USBwIndex0;

        Related_Endpoint = (wIndex0 & 0x0f);
        if (ValBit(wIndex0, 7))
        {
            /* IN endpoint */
            if (_GetTxStallStatus(Related_Endpoint))
            {
                SetBit(StatusInfo0, 0); /* IN Endpoint stalled */
            }
        }
        else
        {
            /* OUT endpoint */
            if (_GetRxStallStatus(Related_Endpoint))
            {
                SetBit(StatusInfo0, 0); /* OUT Endpoint stalled */
            }
        }
    }
    else
    {
        return NULL;
    }
    pUser_Standard_Requests->User_GetStatus();
    return (uint8_t*)&StatusInfo;
}

/**
 * @brief Clear or disable a specific feature.
 * @return - Return Success, if the request is performed.
 *                  - Return UnSupport, if the request is invalid.
 */
USB_Result Standard_ClearFeature(void)
{
    uint32_t Type_Rec = Type_Recipient;
    uint32_t Status;

    if (Type_Rec == (STANDARD_REQUEST | DEVICE_RECIPIENT))
    { /*Device Clear Feature*/
        ClrBit(pInformation->CurrentFeature, 5);
        return Success;
    }
    else if (Type_Rec == (STANDARD_REQUEST | ENDPOINT_RECIPIENT))
    { /*EndPoint Clear Feature*/
        USB_Device* pDev;
        uint32_t Related_Endpoint;
        uint32_t wIndex0;
        uint32_t rEP;

        if ((pInformation->USBwValue != ENDPOINT_STALL) || (pInformation->USBwIndex1 != 0))
        {
            return UnSupport;
        }

        pDev             = &Device_Table;
        wIndex0          = pInformation->USBwIndex0;
        rEP              = wIndex0 & ~0x80;
        Related_Endpoint = ENDP0 + rEP;

        if (ValBit(pInformation->USBwIndex0, 7))
        {
            /*Get Status of endpoint & stall the request if the related_ENdpoint
            is Disabled*/
            Status = _GetEPTxStatus(Related_Endpoint);
        }
        else
        {
            Status = _GetEPRxStatus(Related_Endpoint);
        }

        if ((rEP >= pDev->TotalEndpoint) || (Status == 0) || (pInformation->CurrentConfiguration == 0))
        {
            return UnSupport;
        }

        if (wIndex0 & 0x80)
        {
            /* IN endpoint */
            if (_GetTxStallStatus(Related_Endpoint))
            {
                USB_ClrDattogTx(Related_Endpoint);
                SetEPTxStatus(Related_Endpoint, EP_TX_VALID);
            }
        }
        else
        {
            /* OUT endpoint */
            if (_GetRxStallStatus(Related_Endpoint))
            {
                if (Related_Endpoint == ENDP0)
                {
                    /* After clear the STALL, enable the default endpoint receiver */
                    USB_SetEpRxCnt(Related_Endpoint, Device_Property.MaxPacketSize);
                    _SetEPRxStatus(Related_Endpoint, EP_RX_VALID);
                }
                else
                {
                    USB_ClrDattogRx(Related_Endpoint);
                    _SetEPRxStatus(Related_Endpoint, EP_RX_VALID);
                }
            }
        }
        pUser_Standard_Requests->User_ClearFeature();
        return Success;
    }

    return UnSupport;
}

/**
 * @brief Set or enable a specific feature of EndPoint
 * @return - Return Success, if the request is performed.
 *                  - Return UnSupport, if the request is invalid.
 */
USB_Result Standard_SetEndPointFeature(void)
{
    uint32_t wIndex0;
    uint32_t Related_Endpoint;
    uint32_t rEP;
    uint32_t Status;

    wIndex0          = pInformation->USBwIndex0;
    rEP              = wIndex0 & ~0x80;
    Related_Endpoint = ENDP0 + rEP;

    if (ValBit(pInformation->USBwIndex0, 7))
    {
        /* get Status of endpoint & stall the request if the related_ENdpoint
        is Disabled*/
        Status = _GetEPTxStatus(Related_Endpoint);
    }
    else
    {
        Status = _GetEPRxStatus(Related_Endpoint);
    }

    if (Related_Endpoint >= Device_Table.TotalEndpoint || pInformation->USBwValue != 0 || Status == 0
        || pInformation->CurrentConfiguration == 0)
    {
        return UnSupport;
    }
    else
    {
        if (wIndex0 & 0x80)
        {
            /* IN endpoint */
            _SetEPTxStatus(Related_Endpoint, EP_TX_STALL);
        }

        else
        {
            /* OUT endpoint */
            _SetEPRxStatus(Related_Endpoint, EP_RX_STALL);
        }
    }
    pUser_Standard_Requests->User_SetEndPointFeature();
    return Success;
}

/**
 * @brief Set or enable a specific feature of Device.
 * @return - Return Success, if the request is performed.
 *                  - Return UnSupport, if the request is invalid.
 */
USB_Result Standard_SetDeviceFeature(void)
{
    SetBit(pInformation->CurrentFeature, 5);
    pUser_Standard_Requests->User_SetDeviceFeature();
    return Success;
}

/**
 * @brief Standard_GetDescriptorData is used for descriptors transfer.
 *                : This routine is used for the descriptors resident in Flash
 *                  or RAM
 *                  pDesc can be in either Flash or RAM
 *                  The purpose of this routine is to have a versatile way to
 *                  response descriptors request. It allows user to generate
 *                  certain descriptors with software or read descriptors from
 *                  external storage part by part.
 * Input          : - Length - Length of the data in this transfer.
 *                  - pDesc - A pointer points to descriptor struct.
 *                  The structure gives the initial address of the descriptor and
 *                  its original size.
 * @return Address of a part of the descriptor pointed by the Usb_
 *                  wOffset The buffer pointed by this address contains at least
 *                  Length bytes.
 */
uint8_t* Standard_GetDescriptorData(uint16_t Length, USB_OneDescriptor* pDesc)
{
    uint32_t wOffset;

    wOffset = pInformation->Ctrl_Info.Usb_wOffset;
    if (Length == 0)
    {
        pInformation->Ctrl_Info.Usb_wLength = pDesc->Descriptor_Size - wOffset;
        return 0;
    }

    return pDesc->Descriptor + wOffset;
}

/**
 * @brief Data stage of a Control Write Transfer.
 */
void DataStageOut(void)
{
    USB_EndpointMess* pEPinfo = &pInformation->Ctrl_Info;
    uint32_t save_rLength;

    save_rLength = pEPinfo->Usb_rLength;

    if (pEPinfo->CopyData && save_rLength)
    {
        uint8_t* Buffer;
        uint32_t Length;

        Length = pEPinfo->PacketSize;
        if (Length > save_rLength)
        {
            Length = save_rLength;
        }

        Buffer = (*pEPinfo->CopyData)(Length);
        pEPinfo->Usb_rLength -= Length;
        pEPinfo->Usb_rOffset += Length;

        USB_CopyPMAToUserBuf(Buffer, USB_GetEpRxAddr(ENDP0), Length);
    }

    if (pEPinfo->Usb_rLength != 0)
    {
        vSetEPRxStatus(EP_RX_VALID); /* re-enable for next data reception */
        USB_SetEpTxCnt(ENDP0, 0);
        vSetEPTxStatus(EP_TX_VALID); /* Expect the host to abort the data OUT stage */
    }
    /* Set the next State*/
    if (pEPinfo->Usb_rLength >= pEPinfo->PacketSize)
    {
        pInformation->CtrlState = OutData;
    }
    else
    {
        if (pEPinfo->Usb_rLength > 0)
        {
            pInformation->CtrlState = LastOutData;
        }
        else if (pEPinfo->Usb_rLength == 0)
        {
            pInformation->CtrlState = WaitStatusIn;
            USB_StatusIn();
        }
    }
}

/**
 * @brief Data stage of a Control Read Transfer.
 */
void DataStageIn(void)
{
    USB_EndpointMess* pEPinfo = &pInformation->Ctrl_Info;
    uint32_t save_wLength     = pEPinfo->Usb_wLength;
    uint32_t CtrlState        = pInformation->CtrlState;

    uint8_t* DataBuffer;
    uint32_t Length;

    if ((save_wLength == 0) && (CtrlState == LastInData))
    {
        if (Data_Mul_MaxPacketSize == true)
        {
            /* No more data to send and empty packet */
            Send0LengthData();
            CtrlState              = LastInData;
            Data_Mul_MaxPacketSize = false;
        }
        else
        {
            /* No more data to send so STALL the TX Status*/
            CtrlState = WaitStatusOut;
            vSetEPTxStatus(EP_TX_STALL);
        }

        goto Expect_Status_Out;
    }

    Length    = pEPinfo->PacketSize;
    CtrlState = (save_wLength <= Length) ? LastInData : InData;

    if (Length > save_wLength)
    {
        Length = save_wLength;
    }

    DataBuffer = (*pEPinfo->CopyData)(Length);

    USB_CopyUserToPMABuf(DataBuffer, USB_GetEpTxAddr(ENDP0), Length);

    USB_SetEpTxCnt(ENDP0, Length);

    pEPinfo->Usb_wLength -= Length;
    pEPinfo->Usb_wOffset += Length;
    vSetEPTxStatus(EP_TX_VALID);

    USB_StatusOut(); /* Expect the host to abort the data IN stage */

Expect_Status_Out:
    pInformation->CtrlState = CtrlState;
}

/**
 * @brief Proceed the processing of setup request without data stage.
 */
void NoData_Setup0(void)
{
    USB_Result Result  = UnSupport;
    uint32_t RequestNo = pInformation->bRequest;
    uint32_t CtrlState;

    if (Type_Recipient == (STANDARD_REQUEST | DEVICE_RECIPIENT))
    {
        /* Device Request*/
        /* SET_CONFIGURATION*/
        if (RequestNo == SET_CONFIGURATION)
        {
            Result = Standard_SetConfiguration();
        }

        /*SET ADDRESS*/
        else if (RequestNo == SET_ADDRESS)
        {
            if ((pInformation->USBwValue0 > 127) || (pInformation->USBwValue1 != 0) || (pInformation->USBwIndex != 0)
                || (pInformation->CurrentConfiguration != 0))
            /* Device Address should be 127 or less*/
            {
                CtrlState = Stalled;
                goto exit_NoData_Setup0;
            }
            else
            {
                Result = Success;
            }
        }
        /*SET FEATURE for Device*/
        else if (RequestNo == SET_FEATURE)
        {
            if ((pInformation->USBwValue0 == DEVICE_REMOTE_WAKEUP) && (pInformation->USBwIndex == 0))
            {
                Result = Standard_SetDeviceFeature();
            }
            else
            {
                Result = UnSupport;
            }
        }
        /*Clear FEATURE for Device */
        else if (RequestNo == CLR_FEATURE)
        {
            if (pInformation->USBwValue0 == DEVICE_REMOTE_WAKEUP && pInformation->USBwIndex == 0
                && ValBit(pInformation->CurrentFeature, 5))
            {
                Result = Standard_ClearFeature();
            }
            else
            {
                Result = UnSupport;
            }
        }
    }

    /* Interface Request*/
    else if (Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT))
    {
        /*SET INTERFACE*/
        if (RequestNo == SET_INTERFACE)
        {
            Result = Standard_SetInterface();
        }
    }

    /* EndPoint Request*/
    else if (Type_Recipient == (STANDARD_REQUEST | ENDPOINT_RECIPIENT))
    {
        /*CLEAR FEATURE for EndPoint*/
        if (RequestNo == CLR_FEATURE)
        {
            Result = Standard_ClearFeature();
        }
        /* SET FEATURE for EndPoint*/
        else if (RequestNo == SET_FEATURE)
        {
            Result = Standard_SetEndPointFeature();
        }
    }
    else
    {
        Result = UnSupport;
    }

    if (Result != Success)
    {
        Result = (*pProperty->Class_NoData_Setup)(RequestNo);
        if (Result == Not_Ready)
        {
            CtrlState = Pause;
            goto exit_NoData_Setup0;
        }
    }

    if (Result != Success)
    {
        CtrlState = Stalled;
        goto exit_NoData_Setup0;
    }

    CtrlState = WaitStatusIn; /* After no data stage SETUP */

    USB_StatusIn();

exit_NoData_Setup0:
    pInformation->CtrlState = CtrlState;
    return;
}

/**
 * @brief Proceed the processing of setup request with data stage.
 */
void Data_Setup0(void)
{
    uint8_t* (*CopyRoutine)(uint16_t);
    USB_Result Result;
    uint32_t Request_No = pInformation->bRequest;

    uint32_t Related_Endpoint, Reserved;
    uint32_t wOffset, Status;

    CopyRoutine = NULL;
    wOffset     = 0;

    /*GET DESCRIPTOR*/
    if (Request_No == GET_DESCRIPTOR)
    {
        if (Type_Recipient == (STANDARD_REQUEST | DEVICE_RECIPIENT))
        {
            uint8_t wValue1 = pInformation->USBwValue1;
            if (wValue1 == DEVICE_DESCRIPTOR)
            {
                CopyRoutine = pProperty->GetDeviceDescriptor;
            }
            else if (wValue1 == CONFIG_DESCRIPTOR)
            {
                CopyRoutine = pProperty->GetConfigDescriptor;
            }
            else if (wValue1 == STRING_DESCRIPTOR)
            {
                CopyRoutine = pProperty->GetStringDescriptor;
            } /* End of GET_DESCRIPTOR */
        }
    }

    /*GET STATUS*/
    else if ((Request_No == GET_STATUS) && (pInformation->USBwValue == 0) && (pInformation->USBwLength == 0x0002)
             && (pInformation->USBwIndex1 == 0))
    {
        /* GET STATUS for Device*/
        if ((Type_Recipient == (STANDARD_REQUEST | DEVICE_RECIPIENT)) && (pInformation->USBwIndex == 0))
        {
            CopyRoutine = Standard_GetStatus;
        }

        /* GET STATUS for Interface*/
        else if (Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT))
        {
            if (((*pProperty->Class_Get_Interface_Setting)(pInformation->USBwIndex0, 0) == Success)
                && (pInformation->CurrentConfiguration != 0))
            {
                CopyRoutine = Standard_GetStatus;
            }
        }

        /* GET STATUS for EndPoint*/
        else if (Type_Recipient == (STANDARD_REQUEST | ENDPOINT_RECIPIENT))
        {
            Related_Endpoint = (pInformation->USBwIndex0 & 0x0f);
            Reserved         = pInformation->USBwIndex0 & 0x70;

            if (ValBit(pInformation->USBwIndex0, 7))
            {
                /*Get Status of endpoint & stall the request if the related_ENdpoint
                is Disabled*/
                Status = _GetEPTxStatus(Related_Endpoint);
            }
            else
            {
                Status = _GetEPRxStatus(Related_Endpoint);
            }

            if ((Related_Endpoint < Device_Table.TotalEndpoint) && (Reserved == 0) && (Status != 0))
            {
                CopyRoutine = Standard_GetStatus;
            }
        }
    }

    /*GET CONFIGURATION*/
    else if (Request_No == GET_CONFIGURATION)
    {
        if (Type_Recipient == (STANDARD_REQUEST | DEVICE_RECIPIENT))
        {
            CopyRoutine = Standard_GetConfiguration;
        }
    }
    /*GET INTERFACE*/
    else if (Request_No == GET_INTERFACE)
    {
        if ((Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT)) && (pInformation->CurrentConfiguration != 0)
            && (pInformation->USBwValue == 0) && (pInformation->USBwIndex1 == 0) && (pInformation->USBwLength == 0x0001)
            && ((*pProperty->Class_Get_Interface_Setting)(pInformation->USBwIndex0, 0) == Success))
        {
            CopyRoutine = Standard_GetInterface;
        }
    }

    if (CopyRoutine)
    {
        pInformation->Ctrl_Info.Usb_wOffset = wOffset;
        pInformation->Ctrl_Info.CopyData    = CopyRoutine;
        /* sb in the original the cast to word was directly */
        /* now the cast is made step by step */
        (*CopyRoutine)(0);
        Result = Success;
    }
    else
    {
        Result = (*pProperty->Class_Data_Setup)(pInformation->bRequest);
        if (Result == Not_Ready)
        {
            pInformation->CtrlState = Pause;
            return;
        }
    }

    if (pInformation->Ctrl_Info.Usb_wLength == 0xFFFF)
    {
        /* Data is not ready, wait it */
        pInformation->CtrlState = Pause;
        return;
    }
    if ((Result == UnSupport) || (pInformation->Ctrl_Info.Usb_wLength == 0))
    {
        /* Unsupported request */
        pInformation->CtrlState = Stalled;
        return;
    }

    if (ValBit(pInformation->bmRequestType, 7))
    {
        /* Device ==> Host */
        __IO uint32_t wLength = pInformation->USBwLength;

        /* Restrict the data length to be the one host asks for */
        if (pInformation->Ctrl_Info.Usb_wLength > wLength)
        {
            pInformation->Ctrl_Info.Usb_wLength = wLength;
        }

        else if (pInformation->Ctrl_Info.Usb_wLength < pInformation->USBwLength)
        {
            if (pInformation->Ctrl_Info.Usb_wLength < pProperty->MaxPacketSize)
            {
                Data_Mul_MaxPacketSize = false;
            }
            else if ((pInformation->Ctrl_Info.Usb_wLength % pProperty->MaxPacketSize) == 0)
            {
                Data_Mul_MaxPacketSize = true;
            }
        }

        pInformation->Ctrl_Info.PacketSize = pProperty->MaxPacketSize;
        DataStageIn();
    }
    else
    {
        pInformation->CtrlState = OutData;
        vSetEPRxStatus(EP_RX_VALID); /* enable for next data reception */
    }

    return;
}

/**
 * @brief Get the device request data and dispatch to individual process.
 * @return USB_ProcessPost0.
 */
uint8_t USB_ProcessSetup0(void)
{
    union
    {
        uint8_t* b;
        uint16_t* w;
    } pBuf;

    uint16_t offset = 1;

    pBuf.b = PMAAddr + (uint8_t*)(_GetEPRxAddr(ENDP0) * 2); /* *2 for 32 bits addr */

    if (pInformation->CtrlState != Pause)
    {
        pInformation->bmRequestType = *pBuf.b++;           /* bmRequestType */
        pInformation->bRequest      = *pBuf.b++;           /* bRequest */
        pBuf.w += offset;                                  /* word not accessed because of 32 bits addressing */
        pInformation->USBwValue = USB_ByteSwap(*pBuf.w++); /* wValue */
        pBuf.w += offset;                                  /* word not accessed because of 32 bits addressing */
        pInformation->USBwIndex = USB_ByteSwap(*pBuf.w++); /* wIndex */
        pBuf.w += offset;                                  /* word not accessed because of 32 bits addressing */
        pInformation->USBwLength = *pBuf.w;                /* wLength */
    }

    pInformation->CtrlState = SettingUp;
    if (pInformation->USBwLength == 0)
    {
        /* Setup with no data stage */
        NoData_Setup0();
    }
    else
    {
        /* Setup with data stage */
        Data_Setup0();
    }
    return USB_ProcessPost0();
}

/**
 * @brief Process the IN token on all default endpoint.
 * @return USB_ProcessPost0.
 */
uint8_t USB_ProcessIn0(void)
{
    uint32_t CtrlState = pInformation->CtrlState;

    if ((CtrlState == InData) || (CtrlState == LastInData))
    {
        DataStageIn();
        /* CtrlState may be changed outside the function */
        CtrlState = pInformation->CtrlState;
    }

    else if (CtrlState == WaitStatusIn)
    {
        if ((pInformation->bRequest == SET_ADDRESS) && (Type_Recipient == (STANDARD_REQUEST | DEVICE_RECIPIENT)))
        {
            USB_SetDeviceAddress(pInformation->USBwValue0);
            pUser_Standard_Requests->User_SetDeviceAddress();
        }
        (*pProperty->Process_Status_IN)();
        CtrlState = Stalled;
    }

    else
    {
        CtrlState = Stalled;
    }

    pInformation->CtrlState = CtrlState;

    return USB_ProcessPost0();
}

/**
 * @brief Process the OUT token on all default endpoint.
 * @return USB_ProcessPost0.
 */
uint8_t USB_ProcessOut0(void)
{
    uint32_t CtrlState = pInformation->CtrlState;

    if ((CtrlState == InData) || (CtrlState == LastInData))
    {
        /* host aborts the transfer before finish */
        CtrlState = Stalled;
    }
    else if ((CtrlState == OutData) || (CtrlState == LastOutData))
    {
        DataStageOut();
        CtrlState = pInformation->CtrlState; /* may be changed outside the function */
    }

    else if (CtrlState == WaitStatusOut)
    {
        (*pProperty->Process_Status_OUT)();
        CtrlState = Stalled;
    }

    /* Unexpect state, STALL the endpoint */
    else
    {
        CtrlState = Stalled;
    }

    pInformation->CtrlState = CtrlState;

    return USB_ProcessPost0();
}

/**
 * @brief Stall the Endpoint 0 in case of error.
 * @return
 * - 0 if the control State is in Pause
 * - 1 if not.
 */
uint8_t USB_ProcessPost0(void)
{
    USB_SetEpRxCnt(ENDP0, Device_Property.MaxPacketSize);

    if (pInformation->CtrlState == Stalled)
    {
        vSetEPRxStatus(EP_RX_STALL);
        vSetEPTxStatus(EP_TX_STALL);
    }
    return (pInformation->CtrlState == Pause);
}

/**
 * @brief Set the device and all the used Endpoints addresses.
 * @param Val device address.
 */
void USB_SetDeviceAddress(uint8_t Val)
{
    uint32_t i;
    uint32_t nEP = Device_Table.TotalEndpoint;

    /* set address in every used endpoint */
    for (i = 0; i < nEP; i++)
    {
        _SetEPAddress((uint8_t)i, (uint8_t)i);
    }                           /* for */
    _SetDADDR(Val | ADDR_EFUC); /* set device address and enable function */
}

/**
 * @brief No operation function.
 */
void USB_ProcessNop(void)
{
}
