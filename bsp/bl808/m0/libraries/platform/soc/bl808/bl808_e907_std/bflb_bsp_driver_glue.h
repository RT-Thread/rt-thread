/**
 * *****************************************************************************
 * @file bflb_bsp_driver_glue.h
 * @version 0.1
 * @date 2020-07-08
 * @brief 
 * *****************************************************************************
 * @attention
 * 
 *  <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
 * 
 *  Redistribution and use in source and binary forms, with or without modification,
 *  are permitted provided that the following conditions are met:
 *    1. Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright notice,
 *       this list of conditions and the following disclaimer in the documentation
 *       and/or other materials provided with the distribution.
 *    3. Neither the name of Bouffalo Lab nor the names of its contributors
 *       may be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 * 
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * *****************************************************************************
 */
#ifndef __bBFLB_BSP_DRIVER_GLUE_H__
#define __bBFLB_BSP_DRIVER_GLUE_H__


#include <stdint.h>

#include "bl808_common.h"
#include "bl808_sec_eng.h"
#include "bl808_glb.h"
#include "bl808_dma.h"
#include "bl808_usb.h"
#include "bl808_sdh.h"
#include "bl808_xip_sflash.h"

#define CPU_FLASH_XIP_BASE   BL606P_FLASH_XIP_BASE
#define CPU_FLASH_XIP_END   BL606P_FLASH_XIP_END

#endif
