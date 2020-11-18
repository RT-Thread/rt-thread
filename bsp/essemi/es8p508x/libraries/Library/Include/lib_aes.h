/***************************************************************
 *Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
 *文件名：  lib_aes.c
 *作  者：  zoux
 *版  本：  V1.00
 *日  期：  2017/07/14
 *描  述：  AES模块库函数
 *备  注：  适用于 ES8P508x芯片
 本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
 ***************************************************************/
#ifndef __LIBAES_H__
#define __LIBAES_H__

#include "ES8P508x.h"
#include "type.h"

/* 加密解密模式选择位 */
typedef enum {
	AES_MODE_DECRYPT = 0,	/* 解密 */
	AES_MODE_ENCRYPT = 1,	/* 加密 */
}AES_TYPE_MODE;

/* 加密/解密控制位 */
typedef enum {
	AES_DONE_YES = 0,	/* 加密完成 */
	AES_DONE_NO = 1,	/* 正在加密 */
}AES_TYPE_DONE;

/* 加解密数据结构体 */
typedef struct {
	uint32_t DATA[4];
}AES_DATA_TypeDef;

typedef enum {
	AES_IF_IF = 0x80,
}AES_TYPE_IF;

typedef enum {
	AES_IT_IT = 0x40,
}AES_TYPE_IT;

/* 加解密密钥结构体 */
typedef struct {
	uint32_t KEY[4];
}AES_KEY_TypeDef;

/* 加解密初始结构体 */
typedef struct {
	AES_TYPE_MODE MODE;	/* 加密或者解密 */
}AES_InitStruType;

/* 加解密使能，开始加密 */
#define AES_Enable()	(AES->CON.GO_DONE = 1)
/* 加密模块关闭 */
#define AES_Disable()	(AES->CON.GO_DONE = 0)


/********************* ADC模块函数声明 *********************/
void AES_Init(AES_InitStruType * AES_InitStruct);
void AES_WriteKey(uint32_t *AES_KEY);
void AES_ReadKey(uint32_t * AES_KEY);

void AES_WriteData(uint32_t *AES_DATA);
void AES_ReadData(uint32_t * AES_DATA);

void AES_ITConfig(AES_TYPE_IT AES_IE, TYPE_FUNCEN NewState);
void AES_ClearITPendingBit(void);
FlagStatus AES_GetFlagStatus(AES_TYPE_IF Flag);

AES_TYPE_DONE AES_GetDoneStatus(void);
void AES_Reset(void);

#endif

