#ifndef _GPIO_H_
#define _GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include "stdint.h"
#include "core_cm0plus.h"
#include "nv32f100_bos.h"
/******************************************************************************
 *宏定义，用于生位操作存储加载无符号字段提取(UBFX)硬件编码地址
 *
 *******************************************************************************/
#define GPIO_ALIAS_OFF       0x000F0000L     
#define BOS_BIT_EXTRACT(ADDR,bit,width)        (*(volatile uint32_t *)(((uint32_t) (((uint32_t)&ADDR)-GPIO_ALIAS_OFF))    \
                                  | (BOS_OPCODE_BITFIELD <<26)  \
                                  | ((bit & 0x1F)<<23) | ((width-1) & 0xF)<<19))                       

/******************************************************************************
*
* GPIO位带操作宏定义
*
******************************************************************************/
#define PTA0_OUT_HIGH      BOS_BIT_SET(&GPIOA->PDOR,0)     //PTA0端口数据输出为高
#define PTA0_OUT_LOW       BOS_BIT_CLEAR(&GPIOA->PDOR,0)   //PTA0端口数据输出为低
#define PTA0_OUT_TOGGLE    BOS_BIT_SET(&GPIOA->PTOR,0)     //PTA0端口输出切换

#define PTA1_OUT_HIGH      BOS_BIT_SET(&GPIOA->PDOR,1) 
#define PTA1_OUT_LOW       BOS_BIT_CLEAR(&GPIOA->PDOR,1)	
#define PTA1_OUT_TOGGLE    BOS_BIT_SET(&GPIOA->PTOR,1)

#define PTA2_OUT_HIGH      BOS_BIT_SET(&GPIOA->PDOR,2) 
#define PTA2_OUT_LOW       BOS_BIT_CLEAR(&GPIOA->PDOR,2)
#define PTA2_OUT_TOGGLE    BOS_BIT_SET(&GPIOA->PTOR,2)
	
#define PTA3_OUT_HIGH      BOS_BIT_SET(&GPIOA->PDOR,3) 
#define PTA3_OUT_LOW       BOS_BIT_CLEAR(&GPIOA->PDOR,3)
#define PTA3_OUT_TOGGLE    BOS_BIT_SET(&GPIOA->PTOR,3)

#define PTA4_OUT_HIGH      BOS_BIT_SET(&GPIOA->PDOR,4) 
#define PTA4_OUT_LOW       BOS_BIT_CLEAR(&GPIOA->PDOR,4)
#define PTA4_OUT_TOGGLE    BOS_BIT_SET(&GPIOA->PTOR,4)

#define PTA5_OUT_HIGH      BOS_BIT_SET(&GPIOA->PDOR,5) 
#define PTA5_OUT_LOW       BOS_BIT_CLEAR(&GPIOA->PDOR,5)	
#define PTA5_OUT_TOGGLE    BOS_BIT_SET(&GPIOA->PTOR,5)

#define PTA6_OUT_HIGH      BOS_BIT_SET(&GPIOA->PDOR,6) 
#define PTA6_OUT_LOW       BOS_BIT_CLEAR(&GPIOA->PDOR,6)
#define PTA6_OUT_TOGGLE    BOS_BIT_SET(&GPIOA->PTOR,6)

#define PTA7_OUT_HIGH      BOS_BIT_SET(&GPIOA->PDOR,7) 
#define PTA7_OUT_LOW       BOS_BIT_CLEAR(&GPIOA->PDOR,7)	
#define PTA7_OUT_TOGGLE    BOS_BIT_SET(&GPIOA->PTOR,7)

#define PTB0_OUT_HIGH      BOS_BIT_SET(&GPIOA->PDOR,8)   //PTB0端口数据输出为高
#define PTB0_OUT_LOW       BOS_BIT_CLEAR(&GPIOA->PDOR,8) //PTB0端口数据输出为低
#define PTB0_OUT_TOGGLE    BOS_BIT_SET(&GPIOA->PTOR,8)   //PTB0端口数据输出切换

#define PTB1_OUT_HIGH      BOS_BIT_SET(&GPIOA->PDOR,9) 
#define PTB1_OUT_LOW       BOS_BIT_CLEAR(&GPIOA->PDOR,9)
#define PTB1_OUT_TOGGLE    BOS_BIT_SET(&GPIOA->PTOR,9)
	
#define PTB2_OUT_HIGH      BOS_BIT_SET(&GPIOA->PDOR,10) 
#define PTB2_OUT_LOW       BOS_BIT_CLEAR(&GPIOA->PDOR,10)	
#define PTB2_OUT_TOGGLE    BOS_BIT_SET(&GPIOA->PTOR,10)

#define PTB3_OUT_HIGH      BOS_BIT_SET(&GPIOA->PDOR,11) 
#define PTB3_OUT_LOW       BOS_BIT_CLEAR(&GPIOA->PDOR,11)	
#define PTB3_OUT_TOGGLE    BOS_BIT_SET(&GPIOA->PTOR,11)

#define PTB4_OUT_HIGH      BOS_BIT_SET(&GPIOA->PDOR,12) 
#define PTB4_OUT_LOW       BOS_BIT_CLEAR(&GPIOA->PDOR,12)
#define PTB4_OUT_TOGGLE    BOS_BIT_SET(&GPIOA->PTOR,12)

#define PTB5_OUT_HIGH      BOS_BIT_SET(&GPIOA->PDOR,13) 
#define PTB5_OUT_LOW       BOS_BIT_CLEAR(&GPIOA->PDOR,13)	
#define PTB5_OUT_TOGGLE    BOS_BIT_SET(&GPIOA->PTOR,13)

#define PTB6_OUT_HIGH      BOS_BIT_SET(&GPIOA->PDOR,14) 
#define PTB6_OUT_LOW       BOS_BIT_CLEAR(&GPIOA->PDOR,14)	
#define PTB6_OUT_TOGGLE    BOS_BIT_SET(&GPIOA->PTOR,14)

#define PTB7_OUT_HIGH      BOS_BIT_SET(&GPIOA->PDOR,15) 
#define PTB7_OUT_LOW       BOS_BIT_CLEAR(&GPIOA->PDOR,15)	
#define PTB7_OUT_TOGGLE    BOS_BIT_SET(&GPIOA->PTOR,15)

#define PTC0_OUT_HIGH      BOS_BIT_SET(&GPIOA->PDOR,16)    //PTC0端口数据输出为高
#define PTC0_OUT_LOW       BOS_BIT_CLEAR(&GPIOA->PDOR,16)  //PTC0端口数据输出为低
#define PTC0_OUT_TOGGLE    BOS_BIT_SET(&GPIOA->PTOR,16)    //PTC0端口数据输出切换

#define PTC1_OUT_HIGH      BOS_BIT_SET(&GPIOA->PDOR,17) 
#define PTC1_OUT_LOW       BOS_BIT_CLEAR(&GPIOA->PDOR,17)
#define PTC1_OUT_TOGGLE    BOS_BIT_SET(&GPIOA->PTOR,17)
	
#define PTC2_OUT_HIGH      BOS_BIT_SET(&GPIOA->PDOR,18) 
#define PTC2_OUT_LOW       BOS_BIT_CLEAR(&GPIOA->PDOR,18)	
#define PTC2_OUT_TOGGLE    BOS_BIT_SET(&GPIOA->PTOR,18)

#define PTC3_OUT_HIGH      BOS_BIT_SET(&GPIOA->PDOR,19) 
#define PTC3_OUT_LOW       BOS_BIT_CLEAR(&GPIOA->PDOR,19)	
#define PTC3_OUT_TOGGLE    BOS_BIT_SET(&GPIOA->PTOR,19)

#define PTC4_OUT_HIGH      BOS_BIT_SET(&GPIOA->PDOR,20) 
#define PTC4_OUT_LOW       BOS_BIT_CLEAR(&GPIOA->PDOR,20)
#define PTC4_OUT_TOGGLE    BOS_BIT_SET(&GPIOA->PTOR,20)

#define PTC5_OUT_HIGH      BOS_BIT_SET(&GPIOA->PDOR,21) 
#define PTC5_OUT_LOW       BOS_BIT_CLEAR(&GPIOA->PDOR,21)	
#define PTC5_OUT_TOGGLE    BOS_BIT_SET(&GPIOA->PTOR,21)

#define PTC6_OUT_HIGH      BOS_BIT_SET(&GPIOA->PDOR,22) 
#define PTC6_OUT_LOW       BOS_BIT_CLEAR(&GPIOA->PDOR,22)	
#define PTC6_OUT_TOGGLE    BOS_BIT_SET(&GPIOA->PTOR,22)

#define PTC7_OUT_HIGH      BOS_BIT_SET(&GPIOA->PDOR,23) 
#define PTC7_OUT_LOW       BOS_BIT_CLEAR(&GPIOA->PDOR,23)	
#define PTC7_OUT_TOGGLE    BOS_BIT_SET(&GPIOA->PTOR,23)

#define PTD0_OUT_HIGH      BOS_BIT_SET(&GPIOA->PDOR,24)   //PTD0端口数据输出为高
#define PTD0_OUT_LOW       BOS_BIT_CLEAR(&GPIOA->PDOR,24) //PTD0端口数据输出为低
#define PTD0_OUT_TOGGLE    BOS_BIT_SET(&GPIOA->PTOR,24)   //PTD0端口数据输出切换

#define PTD1_OUT_HIGH      BOS_BIT_SET(&GPIOA->PDOR,25) 
#define PTD1_OUT_LOW       BOS_BIT_CLEAR(&GPIOA->PDOR,25)
#define PTD1_OUT_TOGGLE    BOS_BIT_SET(&GPIOA->PTOR,25)
	
#define PTD2_OUT_HIGH      BOS_BIT_SET(&GPIOA->PDOR,26) 
#define PTD2_OUT_LOW       BOS_BIT_CLEAR(&GPIOA->PDOR,26)	
#define PTD2_OUT_TOGGLE    BOS_BIT_SET(&GPIOA->PTOR,26)

#define PTD3_OUT_HIGH      BOS_BIT_SET(&GPIOA->PDOR,27) 
#define PTD3_OUT_LOW       BOS_BIT_CLEAR(&GPIOA->PDOR,27)	
#define PTD3_OUT_TOGGLE    BOS_BIT_SET(&GPIOA->PTOR,27)

#define PTD4_OUT_HIGH      BOS_BIT_SET(&GPIOA->PDOR,28) 
#define PTD4_OUT_LOW       BOS_BIT_CLEAR(&GPIOA->PDOR,28)
#define PTD4_OUT_TOGGLE    BOS_BIT_SET(&GPIOA->PTOR,28)

#define PTD5_OUT_HIGH      BOS_BIT_SET(&GPIOA->PDOR,29) 
#define PTD5_OUT_LOW       BOS_BIT_CLEAR(&GPIOA->PDOR,29)	
#define PTD5_OUT_TOGGLE    BOS_BIT_SET(&GPIOA->PTOR,29)

#define PTD6_OUT_HIGH      BOS_BIT_SET(&GPIOA->PDOR,30) 
#define PTD6_OUT_LOW       BOS_BIT_CLEAR(&GPIOA->PDOR,30)	
#define PTD6_OUT_TOGGLE    BOS_BIT_SET(&GPIOA->PTOR,30)

#define PTD7_OUT_HIGH      BOS_BIT_SET(&GPIOA->PDOR,31) 
#define PTD7_OUT_LOW       BOS_BIT_CLEAR(&GPIOA->PDOR,31)	
#define PTD7_OUT_TOGGLE    BOS_BIT_SET(&GPIOA->PTOR,31)

#define PTE0_OUT_HIGH      BOS_BIT_SET(&GPIOB->PDOR,0) 
#define PTE0_OUT_LOW       BOS_BIT_CLEAR(&GPIOB->PDOR,0)
#define PTE0_OUT_TOGGLE    BOS_BIT_SET(&GPIOB->PTOR,0)

#define PTE1_OUT_HIGH      BOS_BIT_SET(&GPIOB->PDOR,1)    //PTE0端口数据输出为高
#define PTE1_OUT_LOW       BOS_BIT_CLEAR(&GPIOB->PDOR,1)	//PTE0端口数据输出为低
#define PTE1_OUT_TOGGLE    BOS_BIT_SET(&GPIOB->PTOR,1)    //PTE0端口数据输出切换

#define PTE2_OUT_HIGH      BOS_BIT_SET(&GPIOB->PDOR,2) 
#define PTE2_OUT_LOW       BOS_BIT_CLEAR(&GPIOB->PDOR,2)
#define PTE2_OUT_TOGGLE    BOS_BIT_SET(&GPIOB->PTOR,2)
	
#define PTE3_OUT_HIGH      BOS_BIT_SET(&GPIOB->PDOR,3) 
#define PTE3_OUT_LOW       BOS_BIT_CLEAR(&GPIOB->PDOR,3)
#define PTE3_OUT_TOGGLE    BOS_BIT_SET(&GPIOB->PTOR,3)

#define PTE4_OUT_HIGH      BOS_BIT_SET(&GPIOB->PDOR,4) 
#define PTE4_OUT_LOW       BOS_BIT_CLEAR(&GPIOB->PDOR,4)
#define PTE4_OUT_TOGGLE    BOS_BIT_SET(&GPIOB->PTOR,4)

#define PTE5_OUT_HIGH      BOS_BIT_SET(&GPIOB->PDOR,5) 
#define PTE5_OUT_LOW       BOS_BIT_CLEAR(&GPIOB->PDOR,5)	
#define PTE5_OUT_TOGGLE    BOS_BIT_SET(&GPIOB->PTOR,5)

#define PTE6_OUT_HIGH      BOS_BIT_SET(&GPIOB->PDOR,6) 
#define PTE6_OUT_LOW       BOS_BIT_CLEAR(&GPIOB->PDOR,6)
#define PTE6_OUT_TOGGLE    BOS_BIT_SET(&GPIOB->PTOR,6)

#define PTE7_OUT_HIGH      BOS_BIT_SET(&GPIOB->PDOR,7) 
#define PTE7_OUT_LOW       BOS_BIT_CLEAR(&GPIOB->PDOR,7)	
#define PTE7_OUT_TOGGLE    BOS_BIT_SET(&GPIOB->PTOR,7)

#define PTF0_OUT_HIGH      BOS_BIT_SET(&GPIOB->PDOR,8)    //PTF0端口数据输出为高
#define PTF0_OUT_LOW       BOS_BIT_CLEAR(&GPIOB->PDOR,8)  //PTF0端口数据输出为低
#define PTF0_OUT_TOGGLE    BOS_BIT_SET(&GPIOB->PTOR,8)    //PTF0端口数据输出切换

#define PTF1_OUT_HIGH      BOS_BIT_SET(&GPIOB->PDOR,9) 
#define PTF1_OUT_LOW       BOS_BIT_CLEAR(&GPIOB->PDOR,9)
#define PTF1_OUT_TOGGLE    BOS_BIT_SET(&GPIOB->PTOR,9)
	
#define PTF2_OUT_HIGH      BOS_BIT_SET(&GPIOB->PDOR,10) 
#define PTF2_OUT_LOW       BOS_BIT_CLEAR(&GPIOB->PDOR,10)	
#define PTF2_OUT_TOGGLE    BOS_BIT_SET(&GPIOB->PTOR,10)

#define PTF3_OUT_HIGH      BOS_BIT_SET(&GPIOB->PDOR,11) 
#define PTF3_OUT_LOW       BOS_BIT_CLEAR(&GPIOB->PDOR,11)	
#define PTF3_OUT_TOGGLE    BOS_BIT_SET(&GPIOB->PTOR,11)

#define PTF4_OUT_HIGH      BOS_BIT_SET(&GPIOB->PDOR,12) 
#define PTF4_OUT_LOW       BOS_BIT_CLEAR(&GPIOB->PDOR,12)
#define PTF4_OUT_TOGGLE    BOS_BIT_SET(&GPIOB->PTOR,12)

#define PTF5_OUT_HIGH      BOS_BIT_SET(&GPIOB->PDOR,13) 
#define PTF5_OUT_LOW       BOS_BIT_CLEAR(&GPIOB->PDOR,13)	
#define PTF5_OUT_TOGGLE    BOS_BIT_SET(&GPIOB->PTOR,13)

#define PTF6_OUT_HIGH      BOS_BIT_SET(&GPIOB->PDOR,14) 
#define PTF6_OUT_LOW       BOS_BIT_CLEAR(&GPIOB->PDOR,14)	
#define PTF6_OUT_TOGGLE    BOS_BIT_SET(&GPIOB->PTOR,14)

#define PTF7_OUT_HIGH      BOS_BIT_SET(&GPIOB->PDOR,15) 
#define PTF7_OUT_LOW       BOS_BIT_CLEAR(&GPIOB->PDOR,15)	
#define PTF7_OUT_TOGGLE    BOS_BIT_SET(&GPIOB->PTOR,15)

#define PTG0_OUT_HIGH      BOS_BIT_SET(&GPIOB->PDOR,16)   //PTG0端口数据输出为高
#define PTG0_OUT_LOW       BOS_BIT_CLEAR(&GPIOB->PDOR,16) //PTG0端口数据输出为低
#define PTG0_OUT_TOGGLE    BOS_BIT_SET(&GPIOB->PTOR,16)   //PTG0端口数据输出切换

#define PTG1_OUT_HIGH      BOS_BIT_SET(&GPIOB->PDOR,17) 
#define PTG1_OUT_LOW       BOS_BIT_CLEAR(&GPIOB->PDOR,17)
#define PTG1_OUT_TOGGLE    BOS_BIT_SET(&GPIOB->PTOR,17)
	
#define PTG2_OUT_HIGH      BOS_BIT_SET(&GPIOB->PDOR,18) 
#define PTG2_OUT_LOW       BOS_BIT_CLEAR(&GPIOB->PDOR,18)	
#define PTG2_OUT_TOGGLE    BOS_BIT_SET(&GPIOB->PTOR,18)

#define PTG3_OUT_HIGH      BOS_BIT_SET(&GPIOB->PDOR,19) 
#define PTG3_OUT_LOW       BOS_BIT_CLEAR(&GPIOB->PDOR,19)	
#define PTG3_OUT_TOGGLE    BOS_BIT_SET(&GPIOB->PTOR,19)

#define PTG4_OUT_HIGH      BOS_BIT_SET(&GPIOB->PDOR,20) 
#define PTG4_OUT_LOW       BOS_BIT_CLEAR(&GPIOB->PDOR,20)
#define PTG4_OUT_TOGGLE    BOS_BIT_SET(&GPIOB->PTOR,20)

#define PTG5_OUT_HIGH      BOS_BIT_SET(&GPIOB->PDOR,21) 
#define PTG5_OUT_LOW       BOS_BIT_CLEAR(&GPIOB->PDOR,21)	
#define PTG5_OUT_TOGGLE    BOS_BIT_SET(&GPIOB->PTOR,21)

#define PTG6_OUT_HIGH      BOS_BIT_SET(&GPIOB->PDOR,22) 
#define PTG6_OUT_LOW       BOS_BIT_CLEAR(&GPIOB->PDOR,22)	
#define PTG6_OUT_TOGGLE    BOS_BIT_SET(&GPIOB->PTOR,22)

#define PTG7_OUT_HIGH      BOS_BIT_SET(&GPIOB->PDOR,23) 
#define PTG7_OUT_LOW       BOS_BIT_CLEAR(&GPIOB->PDOR,23)	
#define PTG7_OUT_TOGGLE    BOS_BIT_SET(&GPIOB->PTOR,23)

#define PTH0_OUT_HIGH      BOS_BIT_SET(&GPIOB->PDOR,24)   //PTH0端口数据输出为高
#define PTH0_OUT_LOW       BOS_BIT_CLEAR(&GPIOB->PDOR,24) //PTH0端口数据输出为低
#define PTH0_OUT_TOGGLE    BOS_BIT_SET(&GPIOB->PTOR,24)   //PTH0端口数据输出切换

#define PTH1_OUT_HIGH      BOS_BIT_SET(&GPIOB->PDOR,25) 
#define PTH1_OUT_LOW       BOS_BIT_CLEAR(&GPIOB->PDOR,25)
#define PTH1_OUT_TOGGLE    BOS_BIT_SET(&GPIOB->PTOR,25)
	
#define PTH2_OUT_HIGH      BOS_BIT_SET(&GPIOB->PDOR,26) 
#define PTH2_OUT_LOW       BOS_BIT_CLEAR(&GPIOB->PDOR,26)	
#define PTH2_OUT_TOGGLE    BOS_BIT_SET(&GPIOB->PTOR,26)

#define PTH3_OUT_HIGH      BOS_BIT_SET(&GPIOB->PDOR,27) 
#define PTH3_OUT_LOW       BOS_BIT_CLEAR(&GPIOB->PDOR,27)	
#define PTH3_OUT_TOGGLE    BOS_BIT_SET(&GPIOB->PTOR,27)

#define PTH4_OUT_HIGH      BOS_BIT_SET(&GPIOB->PDOR,28) 
#define PTH4_OUT_LOW       BOS_BIT_CLEAR(&GPIOB->PDOR,28)
#define PTH4_OUT_TOGGLE    BOS_BIT_SET(&GPIOB->PTOR,28)

#define PTH5_OUT_HIGH      BOS_BIT_SET(&GPIOB->PDOR,29) 
#define PTH5_OUT_LOW       BOS_BIT_CLEAR(&GPIOB->PDOR,29)	
#define PTH5_OUT_TOGGLE    BOS_BIT_SET(&GPIOB->PTOR,29)

#define PTH6_OUT_HIGH      BOS_BIT_SET(&GPIOB->PDOR,30) 
#define PTH6_OUT_LOW       BOS_BIT_CLEAR(&GPIOB->PDOR,30)	
#define PTH6_OUT_TOGGLE    BOS_BIT_SET(&GPIOB->PTOR,30)

#define PTH7_OUT_HIGH      BOS_BIT_SET(&GPIOB->PDOR,31) 
#define PTH7_OUT_LOW       BOS_BIT_CLEAR(&GPIOB->PDOR,31)	
#define PTH7_OUT_TOGGLE    BOS_BIT_SET(&GPIOB->PTOR,31)

#define PTA0_IN            BOS_BIT_EXTRACT(GPIOA->PDIR,0,1)  //读取PA0端口输入数据
#define PTA1_IN            BOS_BIT_EXTRACT(GPIOA->PDIR,1,1)
#define PTA2_IN            BOS_BIT_EXTRACT(GPIOA->PDIR,2,1)  
#define PTA3_IN            BOS_BIT_EXTRACT(GPIOA->PDIR,3,1)
#define PTA4_IN            BOS_BIT_EXTRACT(GPIOA->PDIR,4,1)  
#define PTA5_IN            BOS_BIT_EXTRACT(GPIOA->PDIR,5,1)
#define PTA6_IN            BOS_BIT_EXTRACT(GPIOA->PDIR,6,1)  
#define PTA7_IN            BOS_BIT_EXTRACT(GPIOA->PDIR,7,1)

#define PTB0_IN            BOS_BIT_EXTRACT(GPIOA->PDIR,8,1)  //读取PB0端口输入数据
#define PTB1_IN            BOS_BIT_EXTRACT(GPIOA->PDIR,9,1)
#define PTB2_IN            BOS_BIT_EXTRACT(GPIOA->PDIR,10,1)  
#define PTB3_IN            BOS_BIT_EXTRACT(GPIOA->PDIR,11,1)
#define PTB4_IN            BOS_BIT_EXTRACT(GPIOA->PDIR,12,1)  
#define PTB5_IN            BOS_BIT_EXTRACT(GPIOA->PDIR,13,1)
#define PTB6_IN            BOS_BIT_EXTRACT(GPIOA->PDIR,14,1)  
#define PTB7_IN            BOS_BIT_EXTRACT(GPIOA->PDIR,15,1) 

#define PTC0_IN            BOS_BIT_EXTRACT(GPIOA->PDIR,16,1)  //读取PC0端口输入数据
#define PTC1_IN            BOS_BIT_EXTRACT(GPIOA->PDIR,17,1)
#define PTC2_IN            BOS_BIT_EXTRACT(GPIOA->PDIR,18,1)  
#define PTC3_IN            BOS_BIT_EXTRACT(GPIOA->PDIR,19,1)
#define PTC4_IN            BOS_BIT_EXTRACT(GPIOA->PDIR,20,1)  
#define PTC5_IN            BOS_BIT_EXTRACT(GPIOA->PDIR,21,1)
#define PTC6_IN            BOS_BIT_EXTRACT(GPIOA->PDIR,22,1)  
#define PTC7_IN            BOS_BIT_EXTRACT(GPIOA->PDIR,23,1) 

#define PTD0_IN            BOS_BIT_EXTRACT(GPIOA->PDIR,24,1)  //读取PD0端口输入数据
#define PTD1_IN            BOS_BIT_EXTRACT(GPIOA->PDIR,25,1)
#define PTD2_IN            BOS_BIT_EXTRACT(GPIOA->PDIR,26,1)  
#define PTD3_IN            BOS_BIT_EXTRACT(GPIOA->PDIR,27,1)
#define PTD4_IN            BOS_BIT_EXTRACT(GPIOA->PDIR,28,1)  
#define PTD5_IN            BOS_BIT_EXTRACT(GPIOA->PDIR,29,1)
#define PTD6_IN            BOS_BIT_EXTRACT(GPIOA->PDIR,30,1)  
#define PTD7_IN            BOS_BIT_EXTRACT(GPIOA->PDIR,31,1) 

#define PTE0_IN            BOS_BIT_EXTRACT(GPIOB->PDIR,0,1)  //读取PE0端口输入数据
#define PTE1_IN            BOS_BIT_EXTRACT(GPIOB->PDIR,1,1)
#define PTE2_IN            BOS_BIT_EXTRACT(GPIOB->PDIR,2,1)  
#define PTE3_IN            BOS_BIT_EXTRACT(GPIOB->PDIR,3,1)
#define PTE4_IN            BOS_BIT_EXTRACT(GPIOB->PDIR,4,1)  
#define PTE5_IN            BOS_BIT_EXTRACT(GPIOB->PDIR,5,1)
#define PTE6_IN            BOS_BIT_EXTRACT(GPIOB->PDIR,6,1)  
#define PTE7_IN            BOS_BIT_EXTRACT(GPIOB->PDIR,7,1)

#define PTF0_IN            BOS_BIT_EXTRACT(GPIOB->PDIR,8,1)  //读取PF0端口输入数据
#define PTF1_IN            BOS_BIT_EXTRACT(GPIOB->PDIR,9,1)
#define PTF2_IN            BOS_BIT_EXTRACT(GPIOB->PDIR,10,1)  
#define PTF3_IN            BOS_BIT_EXTRACT(GPIOB->PDIR,11,1)
#define PTF4_IN            BOS_BIT_EXTRACT(GPIOB->PDIR,12,1)  
#define PTF5_IN            BOS_BIT_EXTRACT(GPIOB->PDIR,13,1)
#define PTF6_IN            BOS_BIT_EXTRACT(GPIOB->PDIR,14,1)  
#define PTF7_IN            BOS_BIT_EXTRACT(GPIOB->PDIR,15,1) 

#define PTH0_IN            BOS_BIT_EXTRACT(GPIOB->PDIR,16,1)  //读取PH0端口输入数据
#define PTH1_IN            BOS_BIT_EXTRACT(GPIOB->PDIR,17,1)
#define PTH2_IN            BOS_BIT_EXTRACT(GPIOB->PDIR,18,1)  
#define PTH3_IN            BOS_BIT_EXTRACT(GPIOB->PDIR,19,1)
#define PTH4_IN            BOS_BIT_EXTRACT(GPIOB->PDIR,20,1)  
#define PTH5_IN            BOS_BIT_EXTRACT(GPIOB->PDIR,21,1)
#define PTH6_IN            BOS_BIT_EXTRACT(GPIOB->PDIR,22,1)  
#define PTH7_IN            BOS_BIT_EXTRACT(GPIOB->PDIR,23,1) 

#define PTG0_IN            BOS_BIT_EXTRACT(GPIOB->PDIR,24,1)  //读取PG0端口输入数据
#define PTG1_IN            BOS_BIT_EXTRACT(GPIOB->PDIR,25,1)
#define PTG2_IN            BOS_BIT_EXTRACT(GPIOB->PDIR,26,1)  
#define PTG3_IN            BOS_BIT_EXTRACT(GPIOB->PDIR,27,1)
#define PTG4_IN            BOS_BIT_EXTRACT(GPIOB->PDIR,28,1)  
#define PTG5_IN            BOS_BIT_EXTRACT(GPIOB->PDIR,29,1)
#define PTG6_IN            BOS_BIT_EXTRACT(GPIOB->PDIR,30,1)  
#define PTG7_IN            BOS_BIT_EXTRACT(GPIOB->PDIR,31,1) 
/******************************************************************************
*
* 定义GPIO引脚名
*
*******************************************************************************/
typedef enum
{
   /* 用于GPIO */
    GPIO_PTA0 = 0,              /*!< GPIO Pin PTA0 */
    GPIO_PTA1,                  /*!< GPIO Pin PTA1 */
    GPIO_PTA2,                  /*!< GPIO Pin PTA2 */
    GPIO_PTA3,                  /*!< GPIO Pin PTA3 */
    GPIO_PTA4,                  /*!< GPIO Pin PTA4 */
    GPIO_PTA5,                  /*!< GPIO Pin PTA5 */
    GPIO_PTA6,                  /*!< GPIO Pin PTA6 */
    GPIO_PTA7,                  /*!< GPIO Pin PTA7 */
    GPIO_PTB0,                  /*!< GPIO Pin PTB0 */
    GPIO_PTB1,                  /*!< GPIO Pin PTB1 */
    GPIO_PTB2,                  /*!< GPIO Pin PTB2 */
    GPIO_PTB3,                  /*!< GPIO Pin PTB3 */
    GPIO_PTB4,                  /*!< GPIO Pin PTB4 */
    GPIO_PTB5,                  /*!< GPIO Pin PTB5 */
    GPIO_PTB6,                  /*!< GPIO Pin PTB6 */
    GPIO_PTB7,                  /*!< GPIO Pin PTB7 */
    GPIO_PTC0,                  /*!< GPIO Pin PTC0 */
    GPIO_PTC1,                  /*!< GPIO Pin PTC1 */
    GPIO_PTC2,                  /*!< GPIO Pin PTC2 */
    GPIO_PTC3,                  /*!< GPIO Pin PTC3 */
    GPIO_PTC4,                  /*!< GPIO Pin PTC4 */
    GPIO_PTC5,                  /*!< GPIO Pin PTC5 */
    GPIO_PTC6,                  /*!< GPIO Pin PTC6 */
    GPIO_PTC7,                  /*!< GPIO Pin PTC7 */
    GPIO_PTD0,                  /*!< GPIO Pin PTD0 */
    GPIO_PTD1,                  /*!< GPIO Pin PTD1 */
    GPIO_PTD2,                  /*!< GPIO Pin PTD2 */
    GPIO_PTD3,                  /*!< GPIO Pin PTD3 */
    GPIO_PTD4,                  /*!< GPIO Pin PTD4 */
    GPIO_PTD5,                  /*!< GPIO Pin PTD5 */
    GPIO_PTD6,                  /*!< GPIO Pin PTD6 */
    GPIO_PTD7,                  /*!< GPIO Pin PTD7 */
    /* in GPIOB register */
    GPIO_PTE0,                  /*!< GPIO Pin PTE0 */
    GPIO_PTE1,                  /*!< GPIO Pin PTE1 */
    GPIO_PTE2,                  /*!< GPIO Pin PTE2 */
    GPIO_PTE3,                  /*!< GPIO Pin PTE3 */
    GPIO_PTE4,                  /*!< GPIO Pin PTE4 */
    GPIO_PTE5,                  /*!< GPIO Pin PTE5 */
    GPIO_PTE6,                  /*!< GPIO Pin PTE6 */
    GPIO_PTE7,                  /*!< GPIO Pin PTE7 */
    GPIO_PTF0,                  /*!< GPIO Pin PTF0 */
    GPIO_PTF1,                  /*!< GPIO Pin PTF1 */
    GPIO_PTF2,                  /*!< GPIO Pin PTF2 */
    GPIO_PTF3,                  /*!< GPIO Pin PTF3 */
    GPIO_PTF4,                  /*!< GPIO Pin PTF4 */
    GPIO_PTF5,                  /*!< GPIO Pin PTF5 */
    GPIO_PTF6,                  /*!< GPIO Pin PTF6 */
    GPIO_PTF7,                  /*!< GPIO Pin PTF7 */
    GPIO_PTG0,                  /*!< GPIO Pin PTG0 */
    GPIO_PTG1,                  /*!< GPIO Pin PTG1 */
    GPIO_PTG2,                  /*!< GPIO Pin PTG2 */
    GPIO_PTG3,                  /*!< GPIO Pin PTG3 */
    GPIO_PTG4,                  /*!< GPIO Pin PTG4 */
    GPIO_PTG5,                  /*!< GPIO Pin PTG5 */
    GPIO_PTG6,                  /*!< GPIO Pin PTG6 */
    GPIO_PTG7,                  /*!< GPIO Pin PTG7 */
    GPIO_PTH0,                  /*!< GPIO Pin PTH0 */
    GPIO_PTH1,                  /*!< GPIO Pin PTH1 */
    GPIO_PTH2,                  /*!< GPIO Pin PTH2 */
    GPIO_PTH3,                  /*!< GPIO Pin PTH3 */
    GPIO_PTH4,                  /*!< GPIO Pin PTH4 */
    GPIO_PTH5,                  /*!< GPIO Pin PTH5 */
    GPIO_PTH6,                  /*!< GPIO Pin PTH6 */
    GPIO_PTH7,                  /*!< GPIO Pin PTH7 */
    /* the following pins are not in NV322 */
    GPIO_PTI0,                  /*!< GPIO Pin PTI0 */
    GPIO_PTI1,                  /*!< GPIO Pin PTI1 */
    GPIO_PTI2,                  /*!< GPIO Pin PTI2 */
    GPIO_PTI3,                  /*!< GPIO Pin PTI3 */
    GPIO_PTI4,                  /*!< GPIO Pin PTI4 */
    GPIO_PTI5,                  /*!< GPIO Pin PTI5 */
    GPIO_PTI6,                  /*!< GPIO Pin PTI6 */
    GPIO_PTI7,                  /*!< GPIO Pin PTI7 */
    GPIO_PIN_MAX,
} GPIO_PinType;

/******************************************************************************
*
* 定义GPIO引脚掩码
*
*******************************************************************************/
typedef enum
{
    /* in GPIOA register */
    GPIO_PTA0_MASK = (1<<0),    /*!< GPIO Pin PTA0 bit mask */        
    GPIO_PTA1_MASK = (1<<1),    /*!< GPIO Pin PTA1 bit mask */
    GPIO_PTA2_MASK = (1<<2),    /*!< GPIO Pin PTA2 bit mask */
    GPIO_PTA3_MASK = (1<<3),    /*!< GPIO Pin PTA3 bit mask */
    GPIO_PTA4_MASK = (1<<4),    /*!< GPIO Pin PTA4 bit mask */
    GPIO_PTA5_MASK = (1<<5),    /*!< GPIO Pin PTA5 bit mask */
    GPIO_PTA6_MASK = (1<<6),    /*!< GPIO Pin PTA6 bit mask */
    GPIO_PTA7_MASK = (1<<7),    /*!< GPIO Pin PTA7 bit mask */
    GPIO_PTB0_MASK = (1<<8),    /*!< GPIO Pin PTB0 bit mask */
    GPIO_PTB1_MASK = (1<<9),    /*!< GPIO Pin PTB1 bit mask */
    GPIO_PTB2_MASK = (1<<10),   /*!< GPIO Pin PTB2 bit mask */
    GPIO_PTB3_MASK = (1<<11),   /*!< GPIO Pin PTB3 bit mask */
    GPIO_PTB4_MASK = (1<<12),   /*!< GPIO Pin PTB4 bit mask */
    GPIO_PTB5_MASK = (1<<13),   /*!< GPIO Pin PTB5 bit mask */
    GPIO_PTB6_MASK = (1<<14),   /*!< GPIO Pin PTB6 bit mask */
    GPIO_PTB7_MASK = (1<<15),   /*!< GPIO Pin PTB7 bit mask */
    GPIO_PTC0_MASK = (1<<16),   /*!< GPIO Pin PTC0 bit mask */
    GPIO_PTC1_MASK = (1<<17),   /*!< GPIO Pin PTC1 bit mask */
    GPIO_PTC2_MASK = (1<<18),   /*!< GPIO Pin PTC2 bit mask */
    GPIO_PTC3_MASK = (1<<19),   /*!< GPIO Pin PTC3 bit mask */
    GPIO_PTC4_MASK = (1<<20),   /*!< GPIO Pin PTC4 bit mask */
    GPIO_PTC5_MASK = (1<<21),   /*!< GPIO Pin PTC5 bit mask */
    GPIO_PTC6_MASK = (1<<22),   /*!< GPIO Pin PTC6 bit mask */
    GPIO_PTC7_MASK = (1<<23),   /*!< GPIO Pin PTC7 bit mask */
    GPIO_PTD0_MASK = (1<<24),   /*!< GPIO Pin PTD0 bit mask */
    GPIO_PTD1_MASK = (1<<25),   /*!< GPIO Pin PTD1 bit mask */
    GPIO_PTD2_MASK = (1<<26),   /*!< GPIO Pin PTD2 bit mask */
    GPIO_PTD3_MASK = (1<<27),   /*!< GPIO Pin PTD3 bit mask */
    GPIO_PTD4_MASK = (1<<28),   /*!< GPIO Pin PTD4 bit mask */
    GPIO_PTD5_MASK = (1<<29),   /*!< GPIO Pin PTD5 bit mask */
    GPIO_PTD6_MASK = (1<<30),   /*!< GPIO Pin PTD6 bit mask */
	  GPIO_PTD7_MASK = (int)(0x80000000),   /*!< GPIO Pin PTD7 bit mask ** thanks to @homeyou */ 
    /* in GPIOB register */
    GPIO_PTE0_MASK = (1<<0),    /*!< GPIO Pin PTE0 bit mask */
    GPIO_PTE1_MASK = (1<<1),    /*!< GPIO Pin PTE1 bit mask */
    GPIO_PTE2_MASK = (1<<2),    /*!< GPIO Pin PTE2 bit mask */
    GPIO_PTE3_MASK = (1<<3),    /*!< GPIO Pin PTE3 bit mask */
    GPIO_PTE4_MASK = (1<<4),    /*!< GPIO Pin PTE4 bit mask */
    GPIO_PTE5_MASK = (1<<5),    /*!< GPIO Pin PTE5 bit mask */
    GPIO_PTE6_MASK = (1<<6),    /*!< GPIO Pin PTE6 bit mask */
    GPIO_PTE7_MASK = (1<<7),    /*!< GPIO Pin PTE7 bit mask */
    GPIO_PTF0_MASK = (1<<8),    /*!< GPIO Pin PTF0 bit mask */
    GPIO_PTF1_MASK = (1<<9),    /*!< GPIO Pin PTF1 bit mask */
    GPIO_PTF2_MASK = (1<<10),   /*!< GPIO Pin PTF2 bit mask */
    GPIO_PTF3_MASK = (1<<11),   /*!< GPIO Pin PTF3 bit mask */
    GPIO_PTF4_MASK = (1<<12),   /*!< GPIO Pin PTF4 bit mask */
    GPIO_PTF5_MASK = (1<<13),   /*!< GPIO Pin PTF5 bit mask */
    GPIO_PTF6_MASK = (1<<14),   /*!< GPIO Pin PTF6 bit mask */
    GPIO_PTF7_MASK = (1<<15),   /*!< GPIO Pin PTF7 bit mask */
    GPIO_PTG0_MASK = (1<<16),   /*!< GPIO Pin PTG0 bit mask */
    GPIO_PTG1_MASK = (1<<17),   /*!< GPIO Pin PTG1 bit mask */
    GPIO_PTG2_MASK = (1<<18),   /*!< GPIO Pin PTG2 bit mask */
    GPIO_PTG3_MASK = (1<<19),   /*!< GPIO Pin PTG3 bit mask */
    GPIO_PTG4_MASK = (1<<20),   /*!< GPIO Pin PTG4 bit mask */
    GPIO_PTG5_MASK = (1<<21),   /*!< GPIO Pin PTG5 bit mask */
    GPIO_PTG6_MASK = (1<<22),   /*!< GPIO Pin PTG6 bit mask */
    GPIO_PTG7_MASK = (1<<23),   /*!< GPIO Pin PTG7 bit mask */
    GPIO_PTH0_MASK = (1<<24),   /*!< GPIO Pin PTH0 bit mask */
    GPIO_PTH1_MASK = (1<<25),   /*!< GPIO Pin PTH1 bit mask */
    GPIO_PTH2_MASK = (1<<26),   /*!< GPIO Pin PTH2 bit mask */
    GPIO_PTH3_MASK = (1<<27),   /*!< GPIO Pin PTH3 bit mask */
    GPIO_PTH4_MASK = (1<<28),   /*!< GPIO Pin PTH4 bit mask */
    GPIO_PTH5_MASK = (1<<29),   /*!< GPIO Pin PTH5 bit mask */
    GPIO_PTH6_MASK = (1<<30),   /*!< GPIO Pin PTH6 bit mask */
    GPIO_PTH7_MASK = (int)(0x80000000),   /*!< GPIO Pin PTH7 bit mask **  thanks to @homeyou */
    /* in GPIOC register */
    GPIO_PTI0_MASK = (1<<0),    /*!< GPIO Pin PTI0 bit mask */
    GPIO_PTI1_MASK = (1<<1),    /*!< GPIO Pin PTI1 bit mask */
    GPIO_PTI2_MASK = (1<<2),    /*!< GPIO Pin PTI2 bit mask */
    GPIO_PTI3_MASK = (1<<3),    /*!< GPIO Pin PTI3 bit mask */
    GPIO_PTI4_MASK = (1<<4),    /*!< GPIO Pin PTI4 bit mask */
    GPIO_PTI5_MASK = (1<<5),    /*!< GPIO Pin PTI5 bit mask */
    GPIO_PTI6_MASK = (1<<6),    /*!< GPIO Pin PTI6 bit mask */
    GPIO_PTI7_MASK = (1<<7),    /*!< GPIO Pin PTI7 bit mask */
} GPIO_PinMaskType;



/******************************************************************************
*
*定义GPIO引脚配置类型
*
*******************************************************************************/
/*
*   . 如果引脚配置为输入，禁用高电流驱动
*   . 如果引脚配置为输出，禁用内部上拉
*     仅PTH1/0, PTE1/0, PTD1/0, PTB5/4 支持高电流驱动.
*/
typedef enum
{
    GPIO_PinOutput = 0,                 /*!< 设置引脚为输出 */
    GPIO_PinInput,                      /*!< 设置引脚为输出*/
    GPIO_PinInput_InternalPullup,       /*!< 设置引脚为输入且内部上拉 */
    GPIO_PinOutput_HighCurrent,         /*!< 设置引脚为输出，高电流驱动*/
} GPIO_PinConfigType;


/*****************************************************************************//*!
* @brief   切换FGPIO端口数据输出----通过32位掩码确定要切换输出的引脚
*        
* @param[in] pGPIO      指向FGPIO模块,  FGPIOA/FGPIOB.
* @param[in] u32PinMask  32位引脚掩码  ( GPIO_PTA0_MASK, GPIO_PTA1_MASK ............)
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void FGPIO_Toggle(FGPIO_Type *pFGPIO, uint32_t u32PinMask)
{
    pFGPIO->PTOR = u32PinMask;   /* 切换GPIO端口数据输出 */
}

/*****************************************************************************//*!
* @brief 读取FGPIO端口数据输入寄存器
*        
* @param[in] pGPIO       指向FGPIO模块,  FGPIOA/FGPIOB.
*
* @return   FGPIO端口数据输入寄存器32值
*
*****************************************************************************/
 __STATIC_INLINE uint32_t FGPIO_Read(FGPIO_Type *pFGPIO)
{
    return (pFGPIO->PDIR);      /*读端口数据输入寄存器*/
  
}

/*****************************************************************************//*!
* @brief   写数据到FGPIO端口数据输出寄存
*        
* @param[in] pGPIO       指向FGPIO模块, FGPIOA/FGPIOB.
* @param[in] u32Value    写入的数值
*
* @return   none
*
*****************************************************************************/
__STATIC_INLINE void FGPIO_Write(FGPIO_Type *pFGPIO, uint32_t u32Value)
{    
    pFGPIO->PDOR = u32Value;    /*写数据到端口数据输出寄存器*/
}

void GPIO_DeInit(GPIO_Type *pGPIO);
void GPIO_Init(GPIO_Type *pGPIO, uint32_t u32PinMask, GPIO_PinConfigType sGpioType);
void GPIO_Toggle(GPIO_Type *pGPIO, uint32_t u32PinMask);
uint32_t GPIO_Read(GPIO_Type *pGPIO);
void GPIO_Write(GPIO_Type *pGPIO, uint32_t u32Value);
void GPIO_PinInit(GPIO_PinType GPIO_Pin, GPIO_PinConfigType GPIO_PinConfig);
void GPIO_PinToggle(GPIO_PinType GPIO_Pin);
void GPIO_PinSet(GPIO_PinType GPIO_Pin);
void GPIO_PinClear(GPIO_PinType GPIO_Pin);
uint8_t GPIO_BitRead(GPIO_PinType GPIO_Pin);
    


#ifdef __cplusplus
}
#endif
#endif 
