/***************************************************************
 *Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
 *文件名：  
 *作  者:  Liut
 *版  本:  V1.00
 *日  期:  2017/07/14
 *描  述：  
 *备  注：  适用于 ES8P508x芯片
 本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
 ***************************************************************/
#ifndef __ES8P508x_IAP_TABLE_H
#define __ES8P508x_IAP_TABLE_H

#include "ES8P508x.h"
#include "type.h"

#ifdef __cplusplus
extern "C" {
#endif

#define IAP_PageProgram_addr    0x10000008
#define IAP_PageErase_addr      0x10000000
#define IAP_WordProgram_addr    0x10000004

typedef ErrorStatus (*IAP_PE)(uint32_t address);
typedef ErrorStatus (*IAP_WP)(uint32_t address, uint32_t data);
typedef ErrorStatus (*IAP_PP)(uint32_t address, uint32_t data[], uint32_t length, uint32_t erase);

ErrorStatus IAP_PageErase(uint32_t address);
ErrorStatus IAP_WordProgram(uint32_t address, uint32_t data);
ErrorStatus IAP_PageProgram(uint32_t address, uint32_t data[], uint32_t length, uint32_t erase);
ErrorStatus IAPRead(uint32_t *Ram_Addr, uint32_t Flash_Addr, uint8_t Len);

#define PageEraseEnable             0x00000001
#define PageEraseDisable            0x00000000

#ifdef __cplusplus
}
#endif

#endif
/*************************END OF FILE**********************/
