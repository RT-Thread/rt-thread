/*****************************************************************************
*         Nations Microcontroller Software Support
* ----------------------------------------------------------------------------
* Copyright (c) 2017, Nations Corporation
*
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* - Redistributions of source code must retain the above copyright notice,
* this list of conditions and the disclaimer below.
*
* Nations's name may not be used to endorse or promote products derived from
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
/*****************************************************************************
* 文件名：ble_monitor.h
* 功能描述：
* 版本：V 1.0.0
* 作者：
* 日期：
*****************************************************************************/

#ifndef __BLE_MONITOR_H__
#define __BLE_MONITOR_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "core_cm4.h"

//------------------------------------------------------------------
//                        Headers
//------------------------------------------------------------------


//------------------------------------------------------------------
//                        Definitions
//------------------------------------------------------------------
extern __IO uint8_t wakeup_flag_5S;
extern __IO uint8_t stop2_flag;
extern __IO uint8_t wakeup_flag;

void ble_status_monitor(void);
void ble_clear_wakeup(void);
void ble_monitor_callback(void);
uint8_t ble_monitor_wait(uint32_t timeout);

#endif    /*__BLE_MONITOR_H__*/

