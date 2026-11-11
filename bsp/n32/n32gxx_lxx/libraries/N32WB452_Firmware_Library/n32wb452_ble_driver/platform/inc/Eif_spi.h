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
* 文件名：Spi.h
* 功能描述：
* 版本：V 1.0.0
* 作者：
* 日期：
*****************************************************************************/

#ifndef __SPI_H__
#define __SPI_H__
#include "stdint.h"

//------------------------------------------------------------------
//                        Headers
//------------------------------------------------------------------


//------------------------------------------------------------------
//                        Definitions
//------------------------------------------------------------------

#ifdef _SPI_C
void eif_spi_flow_on(void);
bool eif_spi_flow_off(void);
void eif_spi_read(uint8_t *bufptr, uint32_t size, void (*callback) (void*, uint8_t), void* dummy);
void eif_spi_write(uint8_t *bufptr, uint32_t size, void (*callback) (void*, uint8_t), void* dummy);
void eif_spi_recv_bytes(uint8_t *data ,uint16_t length);
int32_t eif_spi_ack_event_check(void);
void eif_spi_send_bytes(uint8_t *src , uint16_t length);
void eif_spi_init(void);
void eif_spi_recv_irq_handler(void);
void eif_spi_recv_irq_enable(uint8_t enable);

#else
extern void eif_spi_flow_on(void);
extern bool eif_spi_flow_off(void);
extern void eif_spi_read(uint8_t *bufptr, uint32_t size, void (*callback) (void*, uint8_t), void* dummy);
extern void eif_spi_write(uint8_t *bufptr, uint32_t size, void (*callback) (void*, uint8_t), void* dummy);
extern int32_t eif_spi_recv_bytes(uint8_t *data ,uint16_t length);
extern int32_t eif_spi_ack_event_check(void);
extern void eif_spi_send_bytes(uint8_t *src , uint16_t length);
extern void eif_spi_init(void);
extern void eif_spi_recv_irq_handler(void);
extern void eif_spi_recv_irq_enable(uint8_t enable);
#endif

#endif    /*__SPIM0DRV_H__*/

