/***************************************************************
 *Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
 *文件名：  
 *作  者:  Liut
 *版  本:  V1.00
 *日  期:  2017/07/14
 *描  述：  
 *备  注：  适用于 ES8P508芯片
 本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
 ***************************************************************/
#include "lib_iap.h"

/*************************************************
 * @brief  IAP 页擦除编程.回调固化在ROM中的程序
 * @param  address: 页首地址
 * @retval None
 ***********************************************/
ErrorStatus IAP_PageErase(uint32_t address)
{
    IAP_PE IAPPageErase = (IAP_PE)(*(uint32_t *)IAP_PageErase_addr);

    ErrorStatus result;
    __ASM("CPSID i");
    result = (*IAPPageErase)(address);
    __ASM("CPSIE i");
    return  result;
}

/*************************************************
 * @brief  IAP 单字自编程.回调固化在ROM中的程序
 * @param  address: 编程首地址
 * @param  data: 编程数据
 * @retval None
 ************************************************/
ErrorStatus IAP_WordProgram(uint32_t address, uint32_t data)
{
    IAP_WP IAPWordProgram = (IAP_WP)(*(uint32_t *)IAP_WordProgram_addr);

    ErrorStatus result;
    __ASM("CPSID i");
    result = (*IAPWordProgram)( address,  data);
    __ASM("CPSIE i");
    return  result;
}

/************************************************
 * @brief  IAP 多字自编程.回调固化在ROM中的程序
 * @param  address: 编程首地址
 * @param  data[]: 编程数据
 * @param  length: 编程数据长度（字节）
 * @param  address: 编程页是否先擦除
 *     @arg 0: 不擦除
 *     @arg 1: 擦除
 * @retval None
 **********************************************/
ErrorStatus IAP_PageProgram(uint32_t address, uint32_t data[], uint32_t length, uint32_t erase)  //@0x100001c5
{
    IAP_PP IAPPageProgram = (IAP_PP)(*(uint32_t *)IAP_PageProgram_addr);

    ErrorStatus result;
    __ASM("CPSID i");
    result = (*IAPPageProgram)(address,data,length,erase);
    __ASM("CPSIE i");
    return  result;
}
/*************************************
  函数名：IARead
  描  述：Flash读
  输入值：内存地址--读取数据的存放地址
  Flash地址
  读取数据的长度，单位为字（4字节）
  返回值：成功/失败
 **************************************/
ErrorStatus IAPRead(uint32_t *Ram_Addr, uint32_t Flash_Addr, uint8_t Len)
{
    uint8_t i;
    uint32_t *ram_addr;
    const uint32_t *flash_addr;

    ram_addr = Ram_Addr;
    flash_addr = (const uint32_t *)Flash_Addr;

    if (Len == 0)
        return ERROR;

    for (i = 0; i < Len; ++i)
    {
        *ram_addr = *flash_addr;
        ++ram_addr;
        ++flash_addr;
    }

    return SUCCESS;
}

/************************END OF FILE**************************/

