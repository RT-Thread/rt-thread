/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "bl_ipc.h"

//FIXME no BL808/BL606p header file including is Allowed here
#ifdef BL808
#include <bl808_glb.h>
#include <bl808_ipc.h>
#elif defined(BL606P)
#include <bl606p_glb.h>
#include <bl606p_ipc.h>
#else
#error "Use CHIP BL808/BL606P for this module"
#endif


extern void IPC_Common_Interrupt_Handler(uint32_t irqStatus, ipcIntCallback *callBack[GLB_CORE_ID_MAX -1]);
extern ipcIntCallback *m0IpcIntCbfArra[GLB_CORE_ID_MAX - 1];

static void ipc_m0_handler(void)
{
    uint32_t irqStatus;
    irqStatus = IPC_M0_Get_Int_Raw_Status();
    IPC_Common_Interrupt_Handler(irqStatus, m0IpcIntCbfArra);
    IPC_M0_Clear_Int_By_Word(irqStatus);
}
//FIXME no BL808/BL606p header file including is Allowed here
#ifdef BL808
#include <bl808_glb.h>
#elif defined(BL606P)
#include <bl606p_glb.h>
#else
#error "Use CHIP BL808/BL606P for this module"
#endif

void ipc_m0_init(ipcIntCallback *onLPTriggerCallBack,
                 ipcIntCallback *onD0TriggerCallBack)
{
    IPC_M0_Init(onLPTriggerCallBack, onD0TriggerCallBack);

#ifdef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(IPC_M0_IRQn, ipc_m0_handler);
#endif

    System_NVIC_SetPriority(IPC_M0_IRQn, 5, 0);
}
