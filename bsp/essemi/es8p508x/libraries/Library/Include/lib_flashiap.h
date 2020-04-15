/***************************************************************
 *Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
 *文件名： lib_flashiap.h
 *作 者： Liut
 *版 本： V1.00
 *日 期： 2017/07/14
 *描 述： flash读写库函数头文件
 *备 注： 适用于 ES8P508x芯片
 本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
 ***************************************************************/
#ifndef __LIBIAP_H__
#define __LIBIAP_H__

#include "ES8P508x.h"
#include "type.h"

/*************IAP模块宏定义************/

/* 寄存器解锁 */
#define FlashIAP_RegUnLock() (IAP->UL.UL = 0x49415055)
#define FlashIAP_RegLock()   (IAP->UL.UL = 0x00000000)

/* 使能IAP */
#define FlashIAP_Enable()  (IAP->CON.EN = 0x1)
#define FlashIAP_Disable() (IAP->CON.EN = 0x0)

/* 访问IAP请求 */
#define FlashIAP_REQ() (IAP->CON.FLASH_REQ = 0x1)

/************Flash模块函数声明***********/
ErrorStatus FlashIap_Close_WPROT(uint8_t Page);
ErrorStatus FlashIap_Open_WPROT(uint8_t Page);
ErrorStatus FlashIap_CloseAll_WPROT(void);
ErrorStatus FlashIap_OpenAll_WPROT(void);
ErrorStatus FlashIap_Unlock(void);
ErrorStatus FlashIap_WriteEnd(void);
ErrorStatus FlashIap_ErasePage(uint8_t Page_Addr);
ErrorStatus FlashIap_WriteCont(uint8_t Unit_addr, uint8_t Page_addr, uint32_t Data32);
ErrorStatus FlashIap_WriteWord(uint8_t Unit_addr, uint8_t Page_addr, uint32_t Data32);
ErrorStatus Flash_Read(uint32_t * Ram_Addr, uint32_t Flash_Addr, uint8_t Len);

#endif
/*************************END OF FILE**********************/

