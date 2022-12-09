/***************************************************************************//**
* \file cy_pdl.h
* \version 1.10
*
* Include this file in all of your source files that access PDL.
*
********************************************************************************
* \copyright
* Copyright 2018-2019 Cypress Semiconductor Corporation
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#ifndef CY_PDL_H
#define CY_PDL_H

#include "cy_device.h"
#include "cy_device_headers.h"

#include "cy_ble_clk.h"
#include "cy_canfd.h"
#include "cy_crypto.h"
#include "cy_crypto_core.h"
#include "cy_crypto_server.h"
#include "cy_csd.h"
#include "cy_ctb.h"
#include "cy_ctdac.h"
#include "cy_dma.h"
#include "cy_dmac.h"
#include "cy_efuse.h"
#include "cy_flash.h"
#include "cy_gpio.h"
#include "cy_i2s.h"
#include "cy_ipc_drv.h"
#include "cy_ipc_pipe.h"
#include "cy_ipc_sema.h"
#include "cy_lpcomp.h"
#include "cy_lvd.h"
#include "cy_mcwdt.h"
#include "cy_pdm_pcm.h"
#include "cy_pra.h"
#include "cy_pra_cfg.h"
#include "cy_profile.h"
#include "cy_prot.h"
#include "cy_rtc.h"
#include "cy_sar.h"
#include "cy_scb_ezi2c.h"
#include "cy_scb_i2c.h"
#include "cy_scb_spi.h"
#include "cy_scb_uart.h"
#include "cy_sd_host.h"
#include "cy_seglcd.h"
#include "cy_smartio.h"
#include "cy_smif.h"
#include "cy_smif_memslot.h"
#include "cy_sysanalog.h"
#include "cy_sysclk.h"
#include "cy_sysint.h"
#include "cy_syslib.h"
#include "cy_syspm.h"
#include "cy_systick.h"
#include "cy_tcpwm_counter.h"
#include "cy_tcpwm_pwm.h"
#include "cy_tcpwm_quaddec.h"
#include "cy_tcpwm_shiftreg.h"
#include "cy_trigmux.h"
#include "cy_usbfs_dev_drv.h"
#include "cy_wdt.h"


/** Driver Library major version */
#define CY_PDL_VERSION_MAJOR        1

/** Driver Library minor version */
#define CY_PDL_VERSION_MINOR        6

/** Driver Library version */
#define CY_PDL_VERSION              106

#endif /* CY_PDL_H */
