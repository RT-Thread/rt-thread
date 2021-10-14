#ifndef __SYS_H
#define __SYS_H
#include "tk499.h"
#include "HAL_conf.h"
//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).M4同M3类似,只是寄存器地址变了.
//IO口操作宏定义
//#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2))
//#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr))
//#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum))

void  RemapVtorTable(void);
void  AI_Responder_enable(void);
void  AI_Responder_disable(void);

void Sys_Soft_Reset(void);                                  //系统软复位
void Sys_Standby(void);                                     //待机模式

void TK499_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel,u8 NVIC_Group);
void Ex_NVIC_Config(u8 GPIOx,u8 BITx,u8 TRIM);              //外部中断配置函数(只对GPIOA~I)

//以下为汇编函数
void WFI_SET(void);     //执行WFI指令
void INTX_DISABLE(void);//关闭所有中断
void INTX_ENABLE(void); //开启所有中断

void TIM3_Config(u16 arr,u16 psc);
#endif











