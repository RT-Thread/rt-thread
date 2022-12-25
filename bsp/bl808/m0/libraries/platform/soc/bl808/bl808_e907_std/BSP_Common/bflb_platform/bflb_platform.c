/**
 * *****************************************************************************
 * @file bflb_print.c
 * @version 0.1
 * @date 2020-06-16
 * @brief bflb platform source file
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

#include "hal_uart.h"
#include "stdarg.h"
#include "stdio.h"
#include "launch.h"
#include "string.h"
#include "hw_inc.h"
#include "bflb_platform.h"

#define UART_DEBUG_DEVICE_INDEX 0
#define PLATFORM_INIT_FALSE     (0)
#define PLATFORM_INIT_TRUE      (1)

static uint8_t uart_dbg_disable=0;
static bflb_platform_ring_buffer_load_callback ring_buffer_load_callback;
static uint32_t init_flag = PLATFORM_INIT_FALSE;

UART_Handle uart_dbg_deivce = NULL;

static void uart_read_fxn(UART_Handle handle, void *buf, size_t count){
    UARTBLXXX_Object               *object;
    
    object = handle->object;

    if(object->ringBuffer!= NULL){
        Ring_Buffer_Write(object->ringBuffer,buf,count);
    }

    if(ring_buffer_load_callback != NULL && uart_dbg_deivce != NULL){
        ring_buffer_load_callback(uart_dbg_deivce);
    }
}

void bflb_platform_uart_dbg_init(uint32_t bdrate)
{
    UART_Params uart_params;

    UART_Params_init(&uart_params);
    uart_params.baudRate = bdrate;

    uart_params.readMode = UART_MODE_CALLBACK;
    uart_params.readCallback = uart_read_fxn;

    UART_init();
    if(bdrate == 0){
        uart_dbg_deivce = UART_open(UART_DEBUG_DEVICE_INDEX,NULL);    
    }else{
        uart_dbg_deivce = UART_open(UART_DEBUG_DEVICE_INDEX,&uart_params);            
    }

    UART_read(uart_dbg_deivce,NULL,UART_WAIT_FOREVER);

}

static void bflb_platform_uart_dbg_deinit()
{
    if(uart_dbg_deivce){
        UART_close(uart_dbg_deivce);
    }
}

void bflb_platform_init(uint32_t baudrate)
{
    if(PLATFORM_INIT_FALSE!=init_flag){
        return ;
    }
    init_flag = PLATFORM_INIT_TRUE;

    bflb_platform_init_time();
    Sec_Eng_Trng_Enable();

    if(!uart_dbg_disable){
        bflb_platform_uart_dbg_init(baudrate);
    }
}

void bflb_platform_print_set(uint8_t logDisable)
{
    uart_dbg_disable=logDisable;
}

void bflb_platform_install_callback(bflb_platform_ring_buffer_load_callback fxn)
{
    ring_buffer_load_callback = fxn;
}

void bflb_platform_printf(char *fmt,...)
{
    static char print_buf[128];
    va_list ap;
    if(!uart_dbg_disable){
        va_start(ap, fmt);
        vsnprintf(print_buf, sizeof(print_buf)-1, fmt, ap);
        va_end(ap);
        UART_write(uart_dbg_deivce,(uint8_t*)print_buf,strlen(print_buf));
    }
}

void bflb_platform_prints(char *data)
{
    if(uart_dbg_deivce != NULL){
        UART_write(uart_dbg_deivce,(uint8_t*)data,strlen(data));
    }
}

void bflb_platform_print_hex(uint8_t * buf , uint16_t len)
{
    if(uart_dbg_deivce != NULL){
        UART_write(uart_dbg_deivce,buf,len);
    }
}

void bflb_platform_deinit()
{
    if(!uart_dbg_disable){
        bflb_platform_uart_dbg_deinit();
    }
}

int bflb_platform_get_random(uint8_t *data,uint32_t len)
{
    return BFLB_BSP_Get_Random(data,len);
}

void bflb_platform_init_time()
{
   BFLB_BSP_Init_Time();
}

void bflb_platform_clear_time()
{
    BFLB_BSP_Clear_Time();
}

uint64_t  bflb_platform_get_time_ms()
{
    return BFLB_BSP_Get_Time_Ms();
}

uint64_t bflb_platform_get_time_us()
{
    return BFLB_BSP_Get_Time_Us();
}

void bflb_platform_start_time()
{
    BFLB_BSP_Start_Time();
}

void bflb_platform_stop_time()
{
    BFLB_BSP_Stop_Time();
}

void bflb_platform_set_alarm_time(uint64_t time)
{
    BFLB_BSP_Set_Alarm_Time(time);
}

void bflb_platform_set_alarm_time_callback(void( *interruptFun )( void ))
{
    BFLB_BSP_Set_Alarm_CallBack(interruptFun);
}

void bflb_platform_deinit_time()
{
    BFLB_BSP_Deinit_Time();
}

void bflb_platform_delay_ms(uint32_t time)
{
    BFLB_BSP_Delay_Ms(time);
}

void bflb_platform_delay_us(uint32_t time)
{
    BFLB_BSP_Delay_Us(time);
}