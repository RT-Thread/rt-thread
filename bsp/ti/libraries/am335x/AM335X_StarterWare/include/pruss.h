/**
 * \file  pruss_drv.h
 *
 * \brief This file contains the function prototypes for the device
 *        abstraction layer for PRUSS. It also contains some
 *        related macro definitions and some files to be included.
 */


/*
* Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/
*
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


#ifndef __PRUSS_DRV_H__
#define __PRUSS_DRV_H__

#ifdef __cplusplus
extern "C" {
#endif

#define AM33XX

//***********************************************************************
//  PRUSS Register Offsets for AM33X SOC
//***********************************************************************/
#ifdef	AM33XX
#define PRUSS_IRAM_SIZE               8192
#define PRUSS_MMAP_SIZE               0x40000
#define DATARAM0_PHYS_BASE            0x4a300000
#define DATARAM1_PHYS_BASE            0x4a302000
#define INTC_PHYS_BASE                0x4a320000
#define PRU0CONTROL_PHYS_BASE         0x4a322000
#define PRU0DEBUG_PHYS_BASE           0x4a322400
#define PRU1CONTROL_PHYS_BASE         0x4a324000
#define PRU1DEBUG_PHYS_BASE           0x4a324400
#define PRU0IRAM_PHYS_BASE            0x4a334000
#define PRU1IRAM_PHYS_BASE            0x4a338000
#define PRUSS_SHAREDRAM_BASE          0x4a310000
#define	PRUSS_CFG_BASE                0x4a326000
#define	PRUSS_UART_BASE               0x4a328000
#define	PRUSS_IEP_BASE                0x4a32e000
#define	PRUSS_ECAP_BASE               0x4a330000
#define	PRUSS_MIIRT_BASE              0x4a332000
#define	PRUSS_MDIO_BASE               0x4a332400
#else 
//***********************************************************************
//  PRUSS Register Offsets for AM18X SOC
//***********************************************************************/
#define PRUSS_IRAM_SIZE               4096
#define PRUSS_MMAP_SIZE               0x7C00
#define PRUSS_DATARAM_SIZE	          512
#define DATARAM0_PHYS_BASE            0x01C30000
#define DATARAM1_PHYS_BASE            0x01C32000
#define INTC_PHYS_BASE                0x01C34000
#define PRU0CONTROL_PHYS_BASE         0x01C37000
#define PRU0DEBUG_PHYS_BASE           0x01C37400
#define PRU1CONTROL_PHYS_BASE         0x01C37800
#define PRU1DEBUG_PHYS_BASE           0x01C37C00
#define PRU0IRAM_PHYS_BASE            0x01C38000
#define PRU1IRAM_PHYS_BASE            0x01C3C000
#endif

#define PRU_EVTOUT_0            0
#define PRU_EVTOUT_1            1
#define PRU_EVTOUT_2            2
#define PRU_EVTOUT_3            3
#define PRU_EVTOUT_4            4
#define PRU_EVTOUT_5            5
#define PRU_EVTOUT_6            6
#define PRU_EVTOUT_7            7
/* 
 * PRUSS Interrupt Controller (PRUSS INTC) Registers Offsets
 */
 
#define PRU_INTC_REVID_REG  0x000
#define PRU_INTC_CR_REG     0x004
#define PRU_INTC_HCR_REG    0x00C
#define PRU_INTC_GER_REG    0x010
#define PRU_INTC_GNLR_REG   0x01C
#define PRU_INTC_SISR_REG   0x020
#define PRU_INTC_SICR_REG   0x024
#define PRU_INTC_EISR_REG   0x028
#define PRU_INTC_EICR_REG   0x02C
#define PRU_INTC_HIEISR_REG 0x034
#define PRU_INTC_HIDISR_REG 0x038
#define PRU_INTC_GPIR_REG   0x080

#define PRU_INTC_SRSR1_REG  0x200
#define PRU_INTC_SRSR2_REG  0x204

#define PRU_INTC_SECR1_REG  0x280
#define PRU_INTC_SECR2_REG  0x284

#define PRU_INTC_ESR1_REG   0x300
#define PRU_INTC_ESR2_REG   0x304

#define PRU_INTC_ECR1_REG   0x380
#define PRU_INTC_ECR2_REG   0x384

#define PRU_INTC_CMR1_REG   0x400
#define PRU_INTC_CMR2_REG   0x404
#define PRU_INTC_CMR3_REG   0x408
#define PRU_INTC_CMR4_REG   0x40C
#define PRU_INTC_CMR5_REG   0x410
#define PRU_INTC_CMR6_REG   0x414
#define PRU_INTC_CMR7_REG   0x418
#define PRU_INTC_CMR8_REG   0x41C
#define PRU_INTC_CMR9_REG   0x420
#define PRU_INTC_CMR10_REG  0x424
#define PRU_INTC_CMR11_REG  0x428
#define PRU_INTC_CMR12_REG  0x42C
#define PRU_INTC_CMR13_REG  0x430
#define PRU_INTC_CMR14_REG  0x434
#define PRU_INTC_CMR15_REG  0x438
#define PRU_INTC_CMR16_REG  0x43C

#define PRU_INTC_HMR1_REG   0x800
#define PRU_INTC_HMR2_REG   0x804
#define PRU_INTC_HMR3_REG   0x808

#define PRU_INTC_SIPR1_REG  0xD00
#define PRU_INTC_SIPR2_REG  0xD04

#define PRU_INTC_SITR1_REG  0xD80
#define PRU_INTC_SITR2_REG  0xD84

#define PRU_INTC_HIER_REG   0x1500

//***********************************************************************
//  Macros representing PRU Memory locations
//***********************************************************************/
#define PRUSS0_PRU0_DATARAM     0
#define PRUSS0_PRU1_DATARAM     1
#define PRUSS0_PRU0_IRAM        2
#define PRUSS0_PRU1_IRAM        3
#define PRUSS0_SHARED_DATARAM   4
#define	PRUSS0_CFG              5
#define	PRUSS0_UART             6
#define	PRUSS0_IEP              7
#define	PRUSS0_ECAP             8
#define	PRUSS0_MII_RT           9
#define	PRUSS0_MDIO            10
//***********************************************************************
//  Macros representing Interrupt-Channel-Host sizes 
//***********************************************************************/
#define MAX_HOSTS_SUPPORTED	 10
#define NUM_PRU_HOSTS        10
#define NUM_PRU_CHANNELS     10
#define NUM_PRU_SYS_EVTS     64

//***********************************************************************
//  Macros to support dynamic chip detecting feature 
//***********************************************************************/
#define AM18XX_INTC_PHYS_BASE		0x01C34000
#define AM18XX_DATARAM0_PHYS_BASE	0x01C30000
#define AM18XX_PRUSS_INTC_REV		0x4E825900	
#define AM33XX_INTC_PHYS_BASE		0x4a320000
#define AM33XX_DATARAM0_PHYS_BASE	0x4a300000
#define AM33XX_PRUSS_INTC_REV		0x4E82A900
#define PRUSS_V1                    1
#define PRUSS_V2                    2


 typedef struct __sysevt_to_channel_map
 {
     short sysevt;
     short channel;
 }tsysevt_to_channel_map;
 
 typedef struct __channel_to_host_map
 {
     short channel;
     short host;
 }tchannel_to_host_map;
 
 typedef struct __pruss_intc_initdata 
 {
     //Enabled SYSEVTs - Range:0..63
     //{-1} indicates end of list
     char sysevts_enabled[NUM_PRU_SYS_EVTS];
 
     //SysEvt to Channel map. SYSEVTs - Range:0..63 Channels -Range: 0..9
     //{-1, -1} indicates end of list
     tsysevt_to_channel_map sysevt_to_channel_map[NUM_PRU_SYS_EVTS];
     
     //Channel to Host map.Channels -Range: 0..9  HOSTs - Range:0..9 
     //{-1, -1} indicates end of list
     tchannel_to_host_map channel_to_host_map[NUM_PRU_CHANNELS];
 
     //10-bit mask - Enable Host0-Host9 {Host0/1:PRU0/1, Host2..9 : PRUEVT_OUT0..7)
     unsigned int host_enable_bitmask;
 }tpruss_intc_initdata;
 
 //typedef void *(*PRUSSDRV_IRQ_HANDLER) (void *);
 typedef void (*PRUSSDRV_IRQ_HANDLER)(void);


//**********************************************************************
//  API FUNCTION PROTOTYPES
//**********************************************************************/
int PRUSSDRVPruReset(unsigned int pruNum);
int PRUSSDRVPruDisable(unsigned char pruNum);
int PRUSSDRVPruEnable(unsigned char pruNum);
int PRUSSDRVPruWriteMemory(unsigned int pruMem,
                           unsigned int wordoffset,
                           unsigned int *source_mem,
                           unsigned int bytelength);
int PRUSSDRVPruExecProgram(int prunum, char *filename);
int PRUSSDRVPruSendEvent(unsigned int eventnum);
int PRUSSDRVPruClearEvent(unsigned int eventnum);
int PRUSSDRVPruWaitEvent(unsigned int pruEvtoutNum);
int PRUSSDRVPruSendWaitCearEvent(unsigned int sendEventNum, 
								 unsigned int pruEvtoutNum,
								 unsigned int ackEventNum);
int PRUSSDRVRegisterIrqHandler(unsigned int pruEvtoutNum, 
						       unsigned char channel,
						       PRUSSDRV_IRQ_HANDLER irqHandler);
int PRUSSDRVSetPRUBuffer(unsigned int pruNum, 
						 void *buffer,
						 unsigned int numBytes);
 
int PRUSSDRVMapL3Mem(void **address);
int PRUSSDRVMapExtMem(void **address);
int PRUSSDRVMapPruMem(unsigned int pru_ram_id, void **address);
void PRUSSDRVIntcSetCmr(unsigned short sysevt,
                        unsigned short channel);
void PRUSSDRVIntcSetHmr(unsigned short channel,
                        unsigned short host);

void ICSS_Init(void);

// #ifdef  AM33XX
// //int PRUSSDRVMapPeripheralIO(unsigned int per_id, void **address);
// #endif
#ifdef __cplusplus
}
#endif
#endif
