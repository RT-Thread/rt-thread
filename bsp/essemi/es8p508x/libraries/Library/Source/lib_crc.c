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
#include "lib_crc.h"

 /***************************************************************
  函数名：CRC_getTypeValue
  描  述：配置并返回一个CRC_CON配置参数
  输入值：con_value CRC_CON 数据配置值结构体
  返回值：CRC_CON配置值
 ***************************************************************/
uint32_t CRC_getTypeValue(CRC_CONValueStruType con_value)
{
	uint32_t type =0;
	type = (con_value.xorout | con_value.refout | con_value.refin |\
		con_value.mode|con_value.hs_type|con_value.init_data_type);
	return type;
}

 /***************************************************************
  函数名：CRC_EmptayCheck
  描  述：查空函数
  输入值：address: 查空区域首地址， data_len：查空区域字节长度
  返回值：1：成功，0 ：失败
 ***************************************************************/
uint32_t CRC_EmptayCheck(void* address, uint32_t data_len)
{
    CRC_EM CRC_EmptayCheck = (CRC_EM)(*(uint32_t *)CRC_EmptayCheck_addr);

    uint32_t result;
    __ASM("CPSID i");
    result = (*CRC_EmptayCheck)(address, data_len);
    __ASM("CPSIE i");
    return result;
}

 /***************************************************************
  函数名：CRC_FlashVerify
  描  述：FLASH校验函数
  输入值：address: 校验区域首地址， data_len：校验区域字节长度， type:校验方式配置
  返回值：CRC校验码
 ***************************************************************/
uint32_t CRC_FlashVerify(void* address, uint32_t data_len, uint32_t type)
{
    CRC_FL CRC_FlashVerify = (CRC_FL)(*(uint32_t *)CRC_FlashVerify_addr);

    uint32_t result;
    __ASM("CPSID i");
    result = (*CRC_FlashVerify)(address, data_len, type);
    __ASM("CPSIE i");
    return result;
}

 /***************************************************************
  函数名：CRC_UserCal
  描  述：用户数据校验函数
  输入值：address: 用户校验数据首地址， data_len：校验区域字节长度， type:校验方式配置
  返回值：CRC校验码
 ***************************************************************/
uint32_t CRC_UserCal(void* address, uint32_t data_len, uint32_t type)
{
    CRC_US CRC_UserCal = (CRC_US)(*(uint32_t *)CRC_UserCal_addr);

    uint32_t result;
    __ASM("CPSID i");
    result = (*CRC_UserCal)(address, data_len, type);
    __ASM("CPSIE i");
    return  result;
}

 /***************************************************************
  函数名：CRC_CheckReset
  描  述：CRC复位查询函数
  输入值：无
  返回值：复位标志，1：有复位标志，0：无复位标志
 ***************************************************************/
uint32_t CRC_CheckReset(void)
{
    CRC_CH CRC_CheckReset = (CRC_CH)(*(uint32_t *)CRC_CheckReset_addr);

    uint32_t result;
    __ASM("CPSID i");
    result = (*CRC_CheckReset)();
    __ASM("CPSIE i");
    return result;
}

/************************END OF FILE**************************/

