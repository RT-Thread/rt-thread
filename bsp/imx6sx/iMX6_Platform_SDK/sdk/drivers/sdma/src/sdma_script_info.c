/*
 * Copyright (c) 2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*!
 * @file sdma_script_info.c
 * @brief a global varialbe to hold the information of the script code.
 */

#include "sdma_script_info.h"

#if defined(CHIP_MX53)
#include "sdma_script_code_mx53.h"
#elif defined (CHIP_MX6DQ)
#include "sdma_script_code_mx6dq.h"
#elif defined (CHIP_MX6SDL) || defined (CHIP_MX6SL)
#include "sdma_script_code_mx6sdl.h"
#endif

#ifdef CHIP_MX53
const sdma_script_info_t script_info = {
    0x00000001,
    0x53,
    {
     {SDMA_AP_2_AP, ap_2_ap_ADDR},
     {SDMA_APP_2_MCU, app_2_mcu_ADDR},
     {SDMA_MCU_2_APP, mcu_2_app_ADDR},
     {SDMA_UART_2_MCU, uart_2_mcu_ADDR},
     {SDMA_SHP_2_MCU, shp_2_mcu_ADDR},
     {SDMA_MCU_2_SHP, mcu_2_shp_ADDR},
     {SDMA_SPDIF_2_MCU, spdif_2_mcu_ADDR},
     {SDMA_MCU_2_SPDIF, mcu_2_spdif_ADDR},
     {SDMA_FIRI_2_MCU, firi_2_mcu_ADDR},
     {SDMA_MCU_2_FIRI, mcu_2_firi_ADDR},
     {SDMA_MCU_2_SSIAPP, mcu_2_ssiapp_ADDR},
     {SDMA_MCU_2_SSISH, mcu_2_ssish_ADDR},
     {SDMA_P_2_P, p_2_p_ADDR},
     {SDMA_SSIAPP_2_MCU, ssiapp_2_mcu_ADDR},
     {SDMA_SSISH_2_MCU, ssish_2_mcu_ADDR},
     {SDMA_NUM_SCRIPTS, 0},
     },
    RAM_CODE_SIZE,
    sdma_code
};
#else
const sdma_script_info_t script_info = {
    0x00000001,
    0x61,
    {
     {SDMA_AP_2_AP, ap_2_ap_ADDR},
     {SDMA_APP_2_MCU, app_2_mcu_ADDR},
     {SDMA_MCU_2_APP, mcu_2_app_ADDR},
     {SDMA_UART_2_MCU, uart_2_mcu_ADDR},
     {SDMA_SHP_2_MCU, shp_2_mcu_ADDR},
     {SDMA_MCU_2_SHP, mcu_2_shp_ADDR},
     {SDMA_SPDIF_2_MCU, spdif_2_mcu_ADDR},
     {SDMA_MCU_2_SPDIF, mcu_2_spdif_ADDR},
     {SDMA_MCU_2_SSIAPP, mcu_2_ssiapp_ADDR},
     {SDMA_MCU_2_SSISH, mcu_2_ssish_ADDR},
     {SDMA_P_2_P, p_2_p_ADDR},
     {SDMA_SSIAPP_2_MCU, ssiapp_2_mcu_ADDR},
     {SDMA_SSISH_2_MCU, ssish_2_mcu_ADDR},
     {SDMA_NUM_SCRIPTS, 0},
     },
    RAM_CODE_SIZE,
    sdma_code
};
#endif
