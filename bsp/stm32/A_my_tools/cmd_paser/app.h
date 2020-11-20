/****************************************************************************
 *
 * File Name
 *  app.h
 * Author
 *  wangk
 * Date
 *  2019/08/04
 * Descriptions:
 * app接口定义头文件
 *
 ****************************************************************************/

#ifndef __APP_H__
#define __APP_H__

#include <stdint.h>
#include <stdbool.h>
#include <rtthread.h>

/**---------------------------------------------------------------------------*
**                             Compiler Flag                                  *
**----------------------------------------------------------------------------*/
#ifdef __cplusplus
extern   "C"
{
#endif

/*----------------------------------------------------------------------------*
**                             Mcaro Definitions                              *
**----------------------------------------------------------------------------*/
#define CMD_STR_SIZE 1024
typedef struct __CMD
{
	int rx_count ;
	uint8_t Res ;
	uint8_t BufferReady  : 1 ;
	uint8_t cmd_err_flag : 1 ;
	uint8_t cmd_buffer[CMD_STR_SIZE] ;
	uint8_t cmd_buffer_temp[CMD_STR_SIZE] ;
}CMDSTR_PARSE ;

extern CMDSTR_PARSE  cmd_parse_typedef ; 

	
	
	

/**--------------------------------------------------------------------------*
**                         Compiler Flag                                     *
**---------------------------------------------------------------------------*/
#ifdef   __cplusplus
}
#endif

#endif // __APP_H__
