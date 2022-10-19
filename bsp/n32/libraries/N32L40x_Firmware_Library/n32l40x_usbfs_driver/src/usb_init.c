/*****************************************************************************
 * Copyright (c) 2022, Nations Technologies Inc.
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
 * @file usb_init.c
 * @author Nations
 * @version v1.2.0
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#include "usb_lib.h"

/*  The number of current endpoint, it will be used to specify an endpoint */
uint8_t EPindex;
/*  The number of current device, it is an index to the Device_Table */
/* uint8_t  Device_no; */
/*  Points to the USB_DeviceMess structure of current device */
/*  The purpose of this register is to speed up the execution */
USB_DeviceMess* pInformation;
/*  Points to the DEVICE_PROP structure of current device */
/*  The purpose of this register is to speed up the execution */
DEVICE_PROP* pProperty;
/*  Temporary save the state of Rx & Tx status. */
/*  Whenever the Rx or Tx state is changed, its value is saved */
/*  in this variable first and will be set to the EPRB or EPRA */
/*  at the end of interrupt process */
uint16_t SaveState;
uint16_t wInterrupt_Mask;
USB_DeviceMess Device_Info;
USER_STANDARD_REQUESTS* pUser_Standard_Requests;

/**
 * @brief USB system initialization
 */
void USB_Init(void)
{
    pInformation            = &Device_Info;
    pInformation->CtrlState = 2;
    pProperty               = &Device_Property;
    pUser_Standard_Requests = &User_Standard_Requests;
    /* Initialize devices one by one */
    pProperty->Init();
    /*Pull up DP*/
//    _ClrDPCtrl();
    _EnPortPullup();
//    printf("DP_CTRL=%x\r\n", (*DP_CTRL));
}
