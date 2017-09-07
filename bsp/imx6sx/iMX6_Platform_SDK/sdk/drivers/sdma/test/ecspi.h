/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
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

#ifndef __ESCPI_H__
#define __ESCPI_H__

typedef struct {
    volatile unsigned int rxdata;
    volatile unsigned int txdata;
    volatile unsigned int conreg;
    volatile unsigned int configreg;
    volatile unsigned int intreg;
    volatile unsigned int dmareg;
    volatile unsigned int statreg;
    volatile unsigned int periodreg;
    volatile unsigned int testreg;
    volatile unsigned int msgdata[16];
} ecspi_reg_t, *ecspi_reg_p;

#define ECSPI_TESTREG_LBC (1<<31)

#define ECSPI_DMA_RXDEN (1<<23)
#define ECSPI_DMA_RXTHR_SHIFT (16)

#define ECSPI_DMA_TXDEN (1<<7)
#define ECSPI_DMA_TXTHR_SHIFT (0)

#define ESCPI_CONREG_BL_ONEWORD (0x1F << 20)
#define ECSPI_CONREG_CHNL0SEL (0<<18)
#define ECSPI_CONREG_CHNL0MD_MASTER (1<<4)
#define ECSPI_CONREG_SMC (1<<3)
#define ECSPI_CONREG_XCH (1<<2)
#define ECSPI_CONREG_EN (1<<0)

#define ECSPI_CONREG_PREDIV (0x3 << 12)
#define ECSPI_CONREG_POSTDIV (0x2 << 8)

#define ECSPI_CONFIG_CHNL0SSCTL (1<<8)

#endif
