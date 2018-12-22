/*
 * Copyright (c) 2010-2012, Freescale Semiconductor, Inc.
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

#ifndef _SPDC_REGS_H_
#define _SPDC_REGS_H_

//*************************************
// Register addresses
//*************************************

/*
 * Register field definitions
 */
#define SPDC_EPD_DISP_TRIGGER		(SPDC_BASE_ADDR + 0x00)
#define SPDC_EPD_UPDATE_X_Y			(SPDC_BASE_ADDR + 0x04)
#define SPDC_EPD_UPDATE_W_H			(SPDC_BASE_ADDR + 0x08)
#define SPDC_EPD_LUT_PARA_UPDATE	(SPDC_BASE_ADDR + 0x0C)
#define SPDC_EPD_OPERATE			(SPDC_BASE_ADDR + 0x10)
#define SPDC_EPD_PANEL_INIT_SET		(SPDC_BASE_ADDR + 0x14)
#define SPDC_EPD_TEMPER_SETTING		(SPDC_BASE_ADDR + 0x18)
#define SPDC_EPD_NEXT_BUF			(SPDC_BASE_ADDR + 0x1C)
#define SPDC_EPD_CURRENT_BUF		(SPDC_BASE_ADDR + 0x20)
#define SPDC_EPD_PREVIOUS_BUF		(SPDC_BASE_ADDR + 0x24)
#define SPDC_EPD_FRM_CNT_BUF		(SPDC_BASE_ADDR + 0x28)
#define SPDC_EPD_LUT_BUF			(SPDC_BASE_ADDR + 0x2C)
#define SPDC_EPD_INT_EN				(SPDC_BASE_ADDR + 0x30)
#define SPDC_EPD_INT_ST_CLR			(SPDC_BASE_ADDR + 0x34)
#define SPDC_EPD_INT_STATUS			(SPDC_BASE_ADDR + 0x38)
#define SPDC_EPD_STATUS				(SPDC_BASE_ADDR + 0x3C)
#define SPDC_EPD_PANEL_TYPE_VER		(SPDC_BASE_ADDR + 0x40)
#define SPDC_EPD_TCON_VER			(SPDC_BASE_ADDR + 0x44)
#define SPDC_EPD_SW_GATE_CLK		(SPDC_BASE_ADDR + 0x48)

#endif // _SPDC_REGS_H_
