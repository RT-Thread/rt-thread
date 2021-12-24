/**
  ******************************************************************************
  * @file    hk32f0xx_divsqrt.h
  * @brief   hk32f0xx divsqrt  file.
  *          The file is the unique include file that the application programmer
	*          is using in the C source code.it is a patch file 
  ******************************************************************************
**/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32F0xx_DIVSQRT_H
#define __HK32F0xx_DIVSQRT_H

#ifdef __cplusplus
 extern "C" {
#endif
 
/* Includes ------------------------------------------------------------------*/
#include "hk32f0xx.h"


#define DVSQ_BUSY_WAIT_EN                           1                                     /* 为1的话在读取DVSQ运算结果寄存器前都会判断并等待DVSQ空闲 */
  
// DVSQ寄存器访问指针
#define DVSQ                                        DIVSQRT   

// DVSQ外设时钟操作
#define RCC_AHBPeriph_DVSQ                          ((uint32_t)0x00000001)
#define RCC_AHBPeriph_DVSQ_CLK_Enable()             RCC->AHBENR2 |= RCC_AHBPeriph_DVSQ     /* 使能DVSQ外设时钟 */
#define RCC_AHBPeriph_DVSQ_CLK_Disable()            RCC->AHBENR2 &= ~RCC_AHBPeriph_DVSQ    /* 关闭DVSQ外设时钟 */

/* DVSQ工作状态定义 */
#define DVSQ_IDLE_NO_OPERATION                      ((uint32_t)0x00000000)                /* 加速器处于空闲状态,并且尚未进行过开方或除法运算 */
#define DVSQ_IDLE_SQRT                              ((uint32_t)0x20000000)                /* 加速器处于空闲状态,并且完成的上一个操作是开方运算 */
#define DVSQ_IDLE_DIV                               ((uint32_t)0x40000000)                /* 加速器处于空闲状诚,并且完成的上一个操作为除法运算 */
#define DVSQ_BUSY_SQRT                              ((uint32_t)0xA0000000)                /* 加速器处于忙状态,并且正在进行开方运算 */
#define DVSQ_BUSY_DIV                               ((uint32_t)0xC0000000)                /* 加速器处于忙状态,并且正在进行除法运算 */

/* 配置DVSQ除法运算的启动方式 */
#define DVSQ_EnableDivFastStart()                   DVSQ->CSR &= ~DIVSQRT_CSR_DFS         /* 使能快速启动除法运算功能 */
#define DVSQ_DisableDivFastStart()                  DVSQ->CSR |= DIVSQRT_CSR_DFS          /* 关闭快速启动除法运算功能 */

/* 配置DVSQ除法是否带符号 */
#define DVSQ_ConfigDivUnsigned()                    DVSQ->CSR |= DIVSQRT_CSR_UNSIGN_DIV   /* 将DVSQ配置为执行无符号除法模式 */
#define DVSQ_ConfigDivSigned()                      DVSQ->CSR &= ~DIVSQRT_CSR_UNSIGN_DIV  /* 将DVSQ配置为执行带符号除法模式 */

/* 配置DVSQ开方运算精度 */
#define DVSQ_ConfigSqrtPresHigh()                   DVSQ->CSR |= DIVSQRT_CSR_HPRESQRT    /* 配置DVSQ为高精度开方运算模式 */
#define DVSQ_ConfigSqrtPresNormal()                 DVSQ->CSR &= ~DIVSQRT_CSR_HPRESQRT    /* 配置DVSQ为普通精度开方运算模式 */

/* 当DVSQ的CSR中DVSQ_CSR_DFS为1时,必须由软件启动除法运算,当该位为0时,往除数寄存器中写入值后硬件自动启动除法运算 */
#define DVSQ_StartDivCalc()                         DVSQ->CSR |= DIVSQRT_CSR_DIV_SRT      /* 开始除法运算 */

/* DVSQ忙状态查询 */
#define DVSQ_IsBusy()                               ((DVSQ->CSR & DIVSQRT_CSR_BUSY)? 1:0) /* 返回'1'表示忙;  返回'0'表示空闲 */

/* DVSQ等待空闲 */
#if (DVSQ_BUSY_WAIT_EN == 1)
#define DVSQ_Wait()                                 while(DVSQ_IsBusy())   
#else
#define DVSQ_Wait()    
#endif



/*DIVSQRT的API函数接口*/
void HK_Dvsq_Init(void);
uint32_t HK_Dvsq_Sqrt(uint32_t u32Radicand, FlagStatus eIsHighPres);
uint32_t HK_Dvsq_Divsion(uint32_t u32Dividend, uint32_t u32Divisor, uint32_t *u32pRemainder, FlagStatus eIsUnsigned, FlagStatus eIsFastStart);
             
#ifdef __cplusplus
}
#endif

#endif
