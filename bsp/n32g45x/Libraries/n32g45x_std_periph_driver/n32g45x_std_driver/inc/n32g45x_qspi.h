/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file n32g45x_qspi.h
 * @author Nations Solution Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32G45X_QSPI_H__
#define __N32G45X_QSPI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g45x.h"
#include <stdbool.h>
/** @addtogroup N32G45X_StdPeriph_Driver
 * @{
 */

/** @addtogroup QSPI
 * @brief QSPI driver modules
 * @{
 */
////////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
    STANDARD_SPI_FORMAT_SEL = 0,
    DUAL_SPI_FORMAT_SEL,
    QUAD_SPI_FORMAT_SEL,
    XIP_SPI_FORMAT_SEL
} QSPI_FORMAT_SEL;

typedef enum
{
    TX_AND_RX = 0,
    TX_ONLY,
    RX_ONLY
} QSPI_DATA_DIR;

typedef enum
{
    QSPI_NSS_PORTA_SEL,
    QSPI_NSS_PORTC_SEL,
    QSPI_NSS_PORTF_SEL
} QSPI_NSS_PORT_SEL;

typedef enum
{
    QSPI_NULL = 0,
    QSPI_SUCCESS,
} QSPI_STATUS;
////////////////////////////////////////////////////////////////////////////////////////////////////
#define QSPI_AFIO_PORT_SEL 							QSPI_NSS_PORTA_SEL

#define ENSPI_WAIT_8CYCLES 							0x4000
#define ENSPI_WAIT_4CYCLES 							0x2000
#define ENSPI_WAIT_2CYCLES 							0x1000
#define ENSPI_INST_L_08BIT 							0x200
#define ENSPI_ADDR_24BIT   							0x18
#define CLOCK_DIVIDER      							12
#define TX_COUNT_EN        							0x01
#define CTRL1_NDF_CNT      							1024

#define XIP_PREFETCH_EN 							1
#define SRAM_CFG_EN     							0

#define DMA_TX 										0x10
#define DMA_RX 										0x01

#define QSPI_DMAReq_TxEN 							0x02
#define QSPI_DMAReq_RxEN 							0x01
////////////////////////////////////////////////////////////////////////////////////////////////////
/* QSPI_CTRL0 */
#define QSPI_CTRL0_DFS_4_BIT               			((uint32_t)0x03)
#define QSPI_CTRL0_DFS_5_BIT               			((uint32_t)0x04)
#define QSPI_CTRL0_DFS_6_BIT               			((uint32_t)0x05)
#define QSPI_CTRL0_DFS_7_BIT               			((uint32_t)0x06)
#define QSPI_CTRL0_DFS_8_BIT               			((uint32_t)0x07)
#define QSPI_CTRL0_DFS_9_BIT               			((uint32_t)0x08)
#define QSPI_CTRL0_DFS_10_BIT              			((uint32_t)0x09)
#define QSPI_CTRL0_DFS_11_BIT              			((uint32_t)0x0A)
#define QSPI_CTRL0_DFS_12_BIT              			((uint32_t)0x0B)
#define QSPI_CTRL0_DFS_13_BIT              			((uint32_t)0x0C)
#define QSPI_CTRL0_DFS_14_BIT              			((uint32_t)0x0D)
#define QSPI_CTRL0_DFS_15_BIT              			((uint32_t)0x0E)
#define QSPI_CTRL0_DFS_16_BIT              			((uint32_t)0x0F)
#define QSPI_CTRL0_DFS_17_BIT              			((uint32_t)0x10)
#define QSPI_CTRL0_DFS_18_BIT              			((uint32_t)0x11)
#define QSPI_CTRL0_DFS_19_BIT              			((uint32_t)0x12)
#define QSPI_CTRL0_DFS_20_BIT              			((uint32_t)0x13)
#define QSPI_CTRL0_DFS_21_BIT              			((uint32_t)0x14)
#define QSPI_CTRL0_DFS_22_BIT              			((uint32_t)0x15)
#define QSPI_CTRL0_DFS_23_BIT              			((uint32_t)0x16)
#define QSPI_CTRL0_DFS_24_BIT              			((uint32_t)0x17)
#define QSPI_CTRL0_DFS_25_BIT              			((uint32_t)0x18)
#define QSPI_CTRL0_DFS_26_BIT              			((uint32_t)0x19)
#define QSPI_CTRL0_DFS_27_BIT              			((uint32_t)0x1A)
#define QSPI_CTRL0_DFS_28_BIT              			((uint32_t)0x1B)
#define QSPI_CTRL0_DFS_29_BIT              			((uint32_t)0x1C)
#define QSPI_CTRL0_DFS_30_BIT              			((uint32_t)0x1D)
#define QSPI_CTRL0_DFS_31_BIT              			((uint32_t)0x1E)
#define QSPI_CTRL0_DFS_32_BIT              			((uint32_t)0x1F)
#define QSPI_CTRL0_FRF_MOTOROLA            			((uint32_t)0x00000000)
#define QSPI_CTRL0_FRF_TI                  			((uint32_t)0x00000040)
#define QSPI_CTRL0_FRF_MICROWIRE           			((uint32_t)0x00000080)
#define QSPI_CTRL0_SCPH_FIRST_EDGE         			((uint32_t)0x00000000)
#define QSPI_CTRL0_SCPH_SECOND_EDGE        			((uint32_t)0x00000100)
#define QSPI_CTRL0_SCPOL_LOW               			((uint32_t)0x00000000)
#define QSPI_CTRL0_SCPOL_HIGH              			((uint32_t)0x00000200)
#define QSPI_CTRL0_TMOD_TX_AND_RX          			((uint32_t)0x00000000)
#define QSPI_CTRL0_TMOD_TX_ONLY            			((uint32_t)0x00000400)
#define QSPI_CTRL0_TMOD_RX_ONLY            			((uint32_t)0x00000800)
#define QSPI_CTRL0_TMOD_EEPROM_READ        			((uint32_t)0x00000C00)
#define QSPI_CTRL0_SRL_EN                			((uint32_t)0x00002000)
#define QSPI_CTRL0_SSTE_EN                   		((uint32_t)0x00004000)
#define QSPI_CTRL0_CFS_1_BIT          	   			((uint32_t)0x00000000)
#define QSPI_CTRL0_CFS_2_BIT          	   			((uint32_t)0x00010000)
#define QSPI_CTRL0_CFS_3_BIT          	   			((uint32_t)0x00020000)
#define QSPI_CTRL0_CFS_4_BIT          	   			((uint32_t)0x00030000)
#define QSPI_CTRL0_CFS_5_BIT          	   			((uint32_t)0x00040000)
#define QSPI_CTRL0_CFS_6_BIT          	   			((uint32_t)0x00050000)
#define QSPI_CTRL0_CFS_7_BIT          	   			((uint32_t)0x00060000)
#define QSPI_CTRL0_CFS_8_BIT          	   			((uint32_t)0x00070000)
#define QSPI_CTRL0_CFS_9_BIT          	   			((uint32_t)0x00080000)
#define QSPI_CTRL0_CFS_10_BIT         	   			((uint32_t)0x00090000)
#define QSPI_CTRL0_CFS_11_BIT         	   			((uint32_t)0x000A0000)
#define QSPI_CTRL0_CFS_12_BIT         	   			((uint32_t)0x000B0000)
#define QSPI_CTRL0_CFS_13_BIT         	   			((uint32_t)0x000C0000)
#define QSPI_CTRL0_CFS_14_BIT         	   			((uint32_t)0x000D0000)
#define QSPI_CTRL0_CFS_15_BIT         	   			((uint32_t)0x000E0000)
#define QSPI_CTRL0_CFS_16_BIT         	   			((uint32_t)0x000F0000)
#define QSPI_CTRL0_SPI_FRF_STANDARD_FORMAT 			((uint32_t)0x00000000)
#define QSPI_CTRL0_SPI_FRF_DUAL_FORMAT     			((uint32_t)0x00400000)
#define QSPI_CTRL0_SPI_FRF_QUAD_FORMAT     			((uint32_t)0x00800000)

/* QSPI_EN */
#define QSPI_EN_QEN 					  			((uint32_t)0x01)
/* QSPI_MW_CTRL */
#define QSPI_MW_CTRL_MWMOD_SEQUENTIAL		  		((uint32_t)0x01)
#define QSPI_MW_CTRL_MC_DIR_TX              		((uint32_t)0x02)
#define QSPI_MW_CTRL_MHS_EN                 		((uint32_t)0x04)

/* QSPI_SLAVE_EN */
#define QSPI_SLAVE_EN_SEN 							((uint32_t)0x01)

/* QSPI_STS */
#define QSPI_STS_BUSY              					((uint32_t)0x01)
#define QSPI_STS_TXFNF_NOT_FULL    					((uint32_t)0x02)
#define QSPI_STS_TXFE_EMPTY        					((uint32_t)0x04)
#define QSPI_STS_RXFNE_NOT_EMPTY   					((uint32_t)0x08)
#define QSPI_STS_RXFF_FULL         					((uint32_t)0x10)
#define QSPI_STS_TX_ERR            					((uint32_t)0x20)
#define QSPI_STS_DC_ERR			   					((uint32_t)0x40)

/* QSPI_IMASK */
#define QSPI_IMASK_TXFEIM    						((uint32_t)0x01)
#define QSPI_IMASK_TXFOIM    						((uint32_t)0x02)
#define QSPI_IMASK_RXFUIM    						((uint32_t)0x04)
#define QSPI_IMASK_RXFOIM    						((uint32_t)0x08)
#define QSPI_IMASK_RXFFIM    						((uint32_t)0x10)
#define QSPI_IMASK_MMCIM     						((uint32_t)0x20)
#define QSPI_IMASK_XRXOIMASK 						((uint32_t)0x40)

/* QSPI_ISTS */
#define QSPI_ISTS_TXFEIS 							((uint32_t)0x01)
#define QSPI_ISTS_TXFOIS 							((uint32_t)0x02)
#define QSPI_ISTS_RXFUIS 							((uint32_t)0x04)
#define QSPI_ISTS_RXFOIS 							((uint32_t)0x08)
#define QSPI_ISTS_RXFFIS 							((uint32_t)0x10)
#define QSPI_ISTS_MMCIS  							((uint32_t)0x20)
#define QSPI_ISTS_XRXOIS 							((uint32_t)0x40)
#define QSPI_ISTS_ICRS   							((uint32_t)0xFF)

/* QSPI_RISTS */
#define QSPI_RISTS_TXFERIS 							((uint32_t)0x01)
#define QSPI_RISTS_TXFORIS 							((uint32_t)0x02)
#define QSPI_RISTS_RXFURIS 							((uint32_t)0x04)
#define QSPI_RISTS_RXFORIS 							((uint32_t)0x08)
#define QSPI_RISTS_RXFFRIS 							((uint32_t)0x10)
#define QSPI_RISTS_MMCRIS  							((uint32_t)0x20)
#define QSPI_RISTS_XRXORIS 							((uint32_t)0x40)

/* QSPI_TXFOI_CLR */
#define QSPI_TXFOI_CLR_TXFOIC 						((uint32_t)0x01)
/* QSPI_RXFOI_CLR */
#define QSPI_RXFOI_CLR_RXFOIC 						((uint32_t)0x01)
/* QSPI_RXFUI_CLR */
#define QSPI_RXFUI_CLR_RXFUIC 						((uint32_t)0x01)
/* QSPI_MMC_CLR */
#define QSPI_MMCI_CLR_MMCIC 						((uint32_t)0x01)
/* QSPI_ICLR */
#define QSPI_ICLR_INTC 								((uint32_t)0x01)
/* QSPI_DMA_CTRL */
#define QSPI_DMA_CTRL_RX_DAM_EN 					((uint32_t)0x01)
#define QSPI_DMA_CTRL_TX_DAM_EN 					((uint32_t)0x02)

/* QSPI_RS_DELAY */
#define QSPI_RS_DELAY_SDCN_0_CYCLES    				((uint32_t)0x00)
#define QSPI_RS_DELAY_SDCN_1_CYCLES    				((uint32_t)0x01)
#define QSPI_RS_DELAY_SDCN_2_CYCLES    				((uint32_t)0x02)
#define QSPI_RS_DELAY_SDCN_3_CYCLES    				((uint32_t)0x03)
#define QSPI_RS_DELAY_SDCN_4_CYCLES    				((uint32_t)0x04)
#define QSPI_RS_DELAY_SDCN_5_CYCLES    				((uint32_t)0x05)
#define QSPI_RS_DELAY_SDCN_6_CYCLES    				((uint32_t)0x06)
#define QSPI_RS_DELAY_SES_RISING_EDGE  				((uint32_t)0x00)
#define QSPI_RS_DELAY_SES_FALLING_EDGE 				((uint32_t)0x01)

/* QSPI_ENH_CTRL0 */
#define QSPI_ENH_CTRL0_TRANS_TYPE_STANDARD       	((uint32_t)0x00000000)
#define QSPI_ENH_CTRL0_TRANS_TYPE_ADDRESS_BY_FRF 	((uint32_t)0x00000001)
#define QSPI_ENH_CTRL0_TRANS_TYPE_ALL_BY_FRF     	((uint32_t)0x00000002)
#define QSPI_ENH_CTRL0_MD_BIT_EN       				((uint32_t)0x00000080)
#define QSPI_ENH_CTRL0_INST_L_0_LINE       			((uint32_t)0x00000000)
#define QSPI_ENH_CTRL0_INST_L_4_LINE       			((uint32_t)0x00000100)
#define QSPI_ENH_CTRL0_INST_L_8_LINE       			((uint32_t)0x00000200)
#define QSPI_ENH_CTRL0_INST_L_16_LINE      			((uint32_t)0x00000300)
#define QSPI_ENH_CTRL0_SPI_DDR_EN          			((uint32_t)0x00010000)
#define QSPI_ENH_CTRL0_INST_DDR_EN         			((uint32_t)0x00020000)
#define QSPI_ENH_CTRL0_XIP_DFS_HC          			((uint32_t)0x00080000)
#define QSPI_ENH_CTRL0_XIP_INST_EN         			((uint32_t)0x00100000)
#define QSPI_ENH_CTRL0_XIP_CT_EN           			((uint32_t)0x00200000)
#define QSPI_ENH_CTRL0_XIP_MBL_2_BIT   				((uint32_t)0x00000000)
#define QSPI_ENH_CTRL0_XIP_MBL_4_BIT   				((uint32_t)0x04000000)
#define QSPI_ENH_CTRL0_XIP_MBL_8_BIT   				((uint32_t)0x08000000)
#define QSPI_ENH_CTRL0_XIP_MBL_16_BIT  				((uint32_t)0x0C000000)
#define QSPI_ENH_CTRL0_CLK_STRETCH_EN      			((uint32_t)0x40000000)

/* XIP_CTRL */
#define XIP_CTRL_FRF_2_LINE           				((uint32_t)0x00000001)
#define XIP_CTRL_FRF_4_LINE           				((uint32_t)0x00000002)
#define XIP_CTRL_FRF_8_LINE           				((uint32_t)0x00000003)
#define XIP_CTRL_TRANS_TYPE_STANDARD_SPI    		((uint32_t)0x00000000)
#define XIP_CTRL_TRANS_TYPE_ADDRESS_BY_XIP_FRF  	((uint32_t)0x00000004)
#define XIP_CTRL_TRANS_TYPE_INSTRUCT_BY_XIP_FRF 	((uint32_t)0x00000008)
#define XIP_CTRL_INST_L_0_LINE        				((uint32_t)0x00000000)
#define XIP_CTRL_INST_L_4_LINE        				((uint32_t)0x00000200)
#define XIP_CTRL_INST_L_8_LINE        				((uint32_t)0x00000400)
#define XIP_CTRL_INST_L_16_LINE       				((uint32_t)0x00000600)
#define XIP_CTRL_MD_BITS_EN           				((uint32_t)0x00001000)
#define XIP_CTRL_DFS_HC           					((uint32_t)0x00040000)
#define XIP_CTRL_DDR_LEN             				((uint32_t)0x00080000)
#define XIP_CTRL_INST_DDR_EN          				((uint32_t)0x00100000)
#define XIP_CTRL_XIP_INST_EN          				((uint32_t)0x00400000)
#define XIP_CTRL_XIP_CT_EN            				((uint32_t)0x00800000)
#define XIP_CTRL_XIP_MBL_LEN_2_BIT    				((uint32_t)0x00000000)
#define XIP_CTRL_XIP_MBL_LEN_4_BIT    				((uint32_t)0x04000000)
#define XIP_CTRL_XIP_MBL_LEN_8_BIT    				((uint32_t)0x08000000)
#define XIP_CTRL_XIP_MBL_LEN_16_BIT   				((uint32_t)0x0C000000)

/* XIP_SLAVE_EN */
#define XIP_SLAVE_EN_SEN 							((uint32_t)0x00000001)
////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
    uint32_t TRANS_TYPE;
    uint32_t SPI_FRF;
    uint32_t TMOD;
    uint32_t SCPOL;
    uint32_t SCPH;
    uint32_t CFS;
    uint32_t DFS;
    uint32_t SSTE;
    uint32_t SEN;
    uint32_t CLK_DIV;
    uint32_t WAIT_CYCLES;
    uint32_t INST_L;
    uint32_t ADDR_LEN;
    uint32_t NDF;
    uint32_t TXFT;
    uint32_t RXFT;

    uint32_t ENHANCED_WAIT_CYCLES;
    uint32_t ENHANCED_CLK_STRETCH_EN;
    uint32_t ENHANCED_ADDR_LEN;
    uint32_t ENHANCED_INST_L;

    uint32_t XIP_FRF;
    uint32_t XIP_TRANS_TYPE;
    uint32_t XIP_ADDR_LEN;
    uint32_t XIP_INST_L;
    uint32_t XIP_WAIT_CYCLES;
    uint32_t XIP_DFS_HC;
    uint32_t XIP_INST_EN;

} QSPI_InitType;
////////////////////////////////////////////////////////////////////////////////////////////////////


void QSPI_Cmd(bool cmd);
void QspiInit(QSPI_FORMAT_SEL qspi_format_sel, QSPI_DATA_DIR data_dir, uint16_t count);
void QSPI_DeInit(void);
uint16_t QSPI_GetITStatus(uint16_t FLAG);
void QSPI_ClearITFLAG(uint16_t FLAG);
void QSPI_DMA_Config(uint32_t PeripheraAddr, uint32_t MemoryAddr, uint16_t Len, uint8_t TxRx);
void QSPI_GPIO(QSPI_NSS_PORT_SEL qspi_nss_port_sel, bool IO1_Input, bool IO3_Output);
//void QSPI_NVIC_Configuration(void);

bool GetQspiBusyStatus(void);
bool GetQspiTxDataBusyStatus(void);
bool GetQspiTxDataEmptyStatus(void);
bool GetQspiRxHaveDataStatus(void);
bool GetQspiRxDataFullStatus(void);
bool GetQspiTransmitErrorStatus(void);
bool GetQspiDataConflictErrorStatus(void);
void QspiSendWord(uint32_t SendData);
uint32_t QspiReadWord(void);
uint32_t QspiGetDataPointer(void);
uint32_t QspiReadRxFifoNum(void);
void QspiSendAndGetWords(uint32_t* pSrcData, uint32_t* pDstData, uint32_t cnt);
uint32_t QspiSendWordAndGetWords(uint32_t WrData, uint32_t* pRdData, uint8_t LastRd);
void ClrFifo(void);
uint32_t GetFifoData(uint32_t* pData, uint32_t Len);

#ifdef __cplusplus
}
#endif

#endif /*__N32G45X_QSPI_H__ */

/**
 * @}
 */

/**
 * @}
 */
