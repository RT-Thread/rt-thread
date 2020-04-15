/***************************************************************
 *Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
 *文件名：  
 *作  者:  AE 
 *版  本:  V1.00
 *日  期:  2017/07/14
 *描  述：  
 *备  注：  适用于 ES8P508芯片
 本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
 ***************************************************************/
#include "lib_aes.h"

/***************************************************************
函数名：AES_Init
描  述：AES功能初始化函数
输入值：AES_InitStruct 初始化结构体
输出值：无
返回值：无
***************************************************************/
void AES_Init(AES_InitStruType * AES_InitStruct)
{


	AES_Reset();

	AES->CON.ENCRYPT = AES_InitStruct->MODE;
	return;
}

/***************************************************************
函数名：AES_WriteKey
描  述：AES写入密钥函数
输入值：AES_KEY 待写入密钥
输出值：无
返回值：无
***************************************************************/
void AES_WriteKey(uint32_t *AES_KEY)
{
	uint32_t *address = AES_KEY;
	
	AES->KEY3.AES_KEY3 = *address;
	address ++;
	AES->KEY2.AES_KEY2 = *address;
	address ++;
	AES->KEY1.AES_KEY1 = *address;
	address ++;
	AES->KEY0.AES_KEY0 = *address;
}

/***************************************************************
函数名：AES_ReadKey
描  述：AES读出密钥函数
输入值：无
输出值：AES_DATA读出密钥存放位置
返回值：无
***************************************************************/
void AES_ReadKey(uint32_t * AES_KEY)
{
	uint32_t *address = AES_KEY;
	
	*address = AES->KEY3.AES_KEY3;
	address ++;
	*address = AES->KEY2.AES_KEY2;
	address ++;
	*address = AES->KEY1.AES_KEY1;
	address ++;
	*address = AES->KEY0.AES_KEY0;
	return;
}

/***************************************************************
函数名：AES_WriteData
描  述：AES写入数据函数
输入值：AES_DATA 待写入数据
输出值：无
返回值：无
***************************************************************/
void AES_WriteData(uint32_t *AES_DATA)
{
	uint32_t *address = AES_DATA;
	
	AES->DATA3.AES_DATA3 = *address;
	address ++;
	AES->DATA2.AES_DATA2 = *address;
	address ++;
	AES->DATA1.AES_DATA1 = *address;
	address ++;
	AES->DATA0.AES_DATA0 = *address;
}

/***************************************************************
函数名：AES_WriteData
描  述：AES读出数据函数
输入值：无
输出值：AES_DATA读出数据存放位置
返回值：无
***************************************************************/
void AES_ReadData(uint32_t * AES_DATA)
{
	uint32_t *address = AES_DATA;
	
	*address = AES->DATA3.AES_DATA3;
	address ++;
	*address = AES->DATA2.AES_DATA2;
	address ++;
	*address = AES->DATA1.AES_DATA1;
	address ++;
	*address = AES->DATA0.AES_DATA0;
	return;
}

/***************************************************************
函数名：AES_ITConfig
描  述：AES中断使能
输入值：AES_IE
	NewState Enable/Disable
输出值：无
返回值：无
***************************************************************/
void AES_ITConfig(AES_TYPE_IT AES_IE, TYPE_FUNCEN NewState)
{
	uint32_t Word = AES->CON.Word&0xffffff8e;
	
	if(AES->CON.GO_DONE == 1)
	{
		return;
	}
	
	if (NewState == ENABLE)
		Word |= (uint32_t)AES_IE;
	else
		
		Word &= ~(uint32_t)AES_IE;

	AES->CON.Word = Word;
	return;

}

/***************************************************************
函数名：AES_GetFlagStatus
描  述：AES获得特定中断标志函数
输入值：IFName 
		AES_IF_IF 加解密完成中断
输出值：无
返回值：中断标志与否
***************************************************************/
FlagStatus AES_GetFlagStatus(AES_TYPE_IF IFName)
{

	if(AES->CON.Word & IFName) {
		return SET;
	}
	return RESET;
}

/***************************************************************
函数名：AES_ClearITPendingBit
描  述：AES清除特定中断标志函数
输入值：IFName 
		AES_IF_DONE 加解密完成中断
输出值：无
返回值：无
***************************************************************/
void AES_ClearITPendingBit(void)
{
	/* 考虑到IF与GO_DONE在同一个word中，对IF赋值可能会存在一些问题 
	 * 例如GO_DONE是1时，取值，随后GO_DONE变成0，而赋值会以原来的1再对其进行赋值
	 * 该部分需要进行测试
	 */
	
	if(AES->CON.GO_DONE == SET)
	{
		return;
	}

	AES->CON.IF = SET;

	return;
}

/***************************************************************
函数名：AES_GetDoneStatus
描  述：AES获得是否加/解密完成
输入值：无
输出值：无
返回值：AES_DONE_NO 加密未完成
	AES_DONE_YES 未加密或者加密已经完成
***************************************************************/
AES_TYPE_DONE AES_GetDoneStatus(void)
{
	if(AES->CON.GO_DONE == 1)
	{
		return AES_DONE_NO;
	}

	return AES_DONE_YES;
}

/***************************************************************
函数名：AES_Reset
描  述：AES复位
输入值：无
输出值：无
返回值：无
***************************************************************/
void AES_Reset(void)
{
	AES->DATA0.Word = 0x00000000;
	AES->DATA1.Word = 0x00000000;
	AES->DATA2.Word = 0x00000000;
	AES->DATA3.Word = 0x00000000;

	AES->KEY0.Word = 0x00000000;
	AES->KEY1.Word = 0x00000000;
	AES->KEY2.Word = 0x00000000;
	AES->KEY3.Word = 0x00000000;

	AES->CON.Word = 0x00000000;
}


