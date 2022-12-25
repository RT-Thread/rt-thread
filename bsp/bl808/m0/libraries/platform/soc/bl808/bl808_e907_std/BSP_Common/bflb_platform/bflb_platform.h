#ifndef __BFLB_PLATFORM__H__
#define __BFLB_PLATFORM__H__

#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include <string.h>
#include "launch.h"
#include "bflb_stub.h"
#include "mcu_sdk_version.h"
#include "hal_uart.h"


#define MSG(a,...)              bflb_platform_printf(a,##__VA_ARGS__)
#define MSG_DBG(a,...)          bflb_platform_printf(a,##__VA_ARGS__)
#define MSG_WAR(a,...)          bflb_platform_printf(a,##__VA_ARGS__)
#define MSG_ERR(a,...)          bflb_platform_printf(a,##__VA_ARGS__)
#define BL_CASE_FAIL            {MSG(" Case Fail\r\n");while(1){}}
#define BL_CASE_SUCCESS         {MSG(" Case Success\r\n");while(1){}}


typedef void (*bflb_platform_ring_buffer_load_callback) (UART_Handle handle);


void bflb_platform_print_set(uint8_t logDisable);
void bflb_platform_printf(char *fmt,...);
void bflb_platform_prints(char *data);
void bflb_platform_print_hex(uint8_t * buf , uint16_t len);
void bflb_platform_init(uint32_t baudrate);
void bflb_platform_uart_dbg_init(uint32_t bdrate);

void bflb_platform_deinit(void);
int bflb_platform_get_random(uint8_t *data,uint32_t len);
void bflb_platform_init_time(void);
void bflb_platform_clear_time(void);
uint64_t bflb_platform_get_time_ms(void);
uint64_t bflb_platform_get_time_us(void);
void bflb_platform_start_time(void);
void bflb_platform_stop_time(void);
void bflb_platform_set_alarm_time_callback(void( *interruptFun )( void ));
void bflb_platform_set_alarm_time(uint64_t time);
void bflb_platform_deinit_time(void);
void bflb_platform_delay_ms(uint32_t time);
void bflb_platform_delay_us(uint32_t time);
void bflb_platform_install_callback(bflb_platform_ring_buffer_load_callback fxn);



typedef enum 
{
  BFLB_SUCCESS  = 0, 
  BFLB_ERROR   = 1,
  BFLB_TIMEOUT = 2,
}BFLB_Err_Type;

#endif