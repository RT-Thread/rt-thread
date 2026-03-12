/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file n32h76x_78x_xspi.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#ifndef __n32h76x_78x_XSPI_H__
#define __n32h76x_78x_XSPI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h76x_78x.h"
#include <stdbool.h>
#include "n32h76x_78x_rcc.h"
#include "n32h76x_78x_gpio.h"

/** n32h76x_78x_StdPeriph_Driver **/

/**  XSPI driver modules **/

#define XSPI_CTRLRO_SPI_MASK        ((uint32_t)0x00001000)
#define XSPI_CTRLRO_XIP_MASK        
																	  
#define XSPI_WAITCYCLES_MASK        ((uint32_t)~0x0000f800U)
#define XSPI_SPIFRF_MASK            ((uint32_t)~0x00c00000U)
#define XSPI_TRANSTYPE_MASK         ((uint32_t)~0x00000003U)
#define XSPI_DFS_MASK               ((uint32_t)~0x0000001fU)
#define XSPI_ADDRL_MASK             ((uint32_t)~0x0000003cU)
#define XSPI_INST_L_MASK            ((uint32_t)~0x00000300U)
#define XSPI_NDF_MASK               ((uint32_t)~0x0000ffffU)
#define XSPI_TMOD_MASK              ((uint32_t)~0x00000c00U)
#define XSPI_RXFTLR_MASK            ((uint32_t)~0x0000001fU)
#define XSPI_TXFTLR_MASK            ((uint32_t)~0x001f0000U)
#define XSPI_TXFTLITR_MASK          ((uint32_t)~0x0000001fU)																	  
#define XSPI_TXFT_MASK              ((uint32_t)~0x001f001fU)
																	  
#define STANDRD_SPI_FORMAT          XSPI_CTRL0_SPIFRF_STANDARD_FORMAT   //((uint32_t)0x00000000)
#define DUAL_SPI_FORMAT             XSPI_CTRL0_SPIFRF_DUAL_FORMAT       //((uint32_t)0x00400000)
#define QUAD_SPI_FORMAT             XSPI_CTRL0_SPIFRF_QUAD_FORMAT       //((uint32_t)0x00800000)
#define OCTAL_SPI_FORMAT            XSPI_CTRL0_SPIFRF_OCTAL_FORMAT      //((uint32_t)0x00C00000)
#define IS_XSPI_DATA_FORMAT(FORMAT) (((FORMAT) == STANDRD_SPI_FORMAT) || \
                                    ((FORMAT) == DUAL_SPI_FORMAT) || \
                                    ((FORMAT) == QUAD_SPI_FORMAT) || \
                                    ((FORMAT) == OCTAL_SPI_FORMAT))

////////////////////////////////////////////////////////////////////////////////////////////////////
#define XSPI_TIME_OUT_CNT           200

/** XSPI_mode: XSPI_CTRL0 **/
#define XSPI_Mode_Master            XSPI_CTRL0_MST_MASTER  //((uint32_t)0x80000000U)
#define XSPI_Mode_Slave             XSPI_CTRL0_MST_SLAVE   //((uint32_t)0x00000000U)
#define IS_XSPI_MODE(MODE)          (((MODE) == QSPI_Mode_Master) || \
                                    ((MODE) == QSPI_Mode_Slave))
													 

/** @defgroup XSPI_data_direction 
  * @{
  */
  
#define TX_AND_RX                    XSPI_CTRL0_TMOD_TX_AND_RX   // ((uint32_t)0x00000000)
#define TX_ONLY                      XSPI_CTRL0_TMOD_TX_ONLY     // ((uint32_t)0x00000400)
#define RX_ONLY                      XSPI_CTRL0_TMOD_RX_ONLY     // ((uint32_t)0x00000800)
#define EEPROM_READ                  XSPI_CTRL0_TMOD_EEPROM_READ // ((uint32_t)0x00000c00)
#define IS_XSPI_DIRECTION_MODE(MODE) (((MODE) == TX_AND_RX) || \
                                     ((MODE) == TX_ONLY) || \
                                     ((MODE) == RX_ONLY) || \
                                     ((MODE) == EEPROM_READ)) 

/** XSPI_Address_instruction_transfer_format.: XSPI_ENH_CTRL0 **/
#define TRANS_TYPE_STANDRD          XSPI_ENH_CTRL0_TRANSTYPE_STANDARD //((uint32_t)0x00000000)  
#define TRANS_TYPE_STANDRD_FRF      XSPI_ENH_CTRL0_TRANSTYPE_0        //((uint32_t)0x00000001)
#define TRANS_TYPE_FRF              XSPI_ENH_CTRL0_TRANSTYPE_1        //((uint32_t)0x00000002)
#define IS_QSPI_ADDRINSTDFS(SIZE)   (((SIZE) == ENSPI_INST_L_NONE) || \
                                    ((SIZE) == ENSPI_INST_L_04BIT) || \
                                    ((SIZE) == ENSPI_INST_L_08BIT) || \
                                    ((SIZE) == ENSPI_INST_L_16BIT))


/** @defgroup QSPI_Address_length
  * @{
  */
#define ENSPI_ADDR_NONE                  ((uint32_t)0x00000000)
#define ENSPI_ADDR_04BIT                 ((uint32_t)0x00000004)
#define ENSPI_ADDR_08BIT                 ((uint32_t)0x00000008)
#define ENSPI_ADDR_16BIT                 ((uint32_t)0x00000010)
#define ENSPI_ADDR_24BIT                 ((uint32_t)0x00000018)
#define ENSPI_ADDR_28BIT                 ((uint32_t)0x0000001c)
#define ENSPI_ADDR_32BIT                 ((uint32_t)0x00000020)
#define ENSPI_ADDR_40BIT                 ((uint32_t)0x00000028)
#define ENSPI_ADDR_48BIT                 ((uint32_t)0x00000030)
#define ENSPI_ADDR_52BIT                 ((uint32_t)0x00000034)
#define ENSPI_ADDR_56BIT                 ((uint32_t)0x00000038)
#define ENSPI_ADDR_60BIT                 ((uint32_t)0x0000003C)
#define IS_QSPI_ADDRSIZE(SIZE) (((SIZE) == ENSPI_INST_L_NONE) || \
                                   ((SIZE) == ENSPI_INST_L_04BIT) || \
                                   ((SIZE) == ENSPI_INST_L_08BIT) || \
                                   ((SIZE) == ENSPI_INST_L_16BIT))
	

/** @defgroup QSPI_instruction_length
  * @{
  */
#define ENSPI_INST_L_NONE                  ((uint32_t)0x00000000)
#define ENSPI_INST_L_04BIT                 ((uint32_t)0x00000100)
#define ENSPI_INST_L_08BIT                 ((uint32_t)0x00000200)
#define ENSPI_INST_L_16BIT                 ((uint32_t)0x00000300)
#define IS_QSPI_INSTSIZE(SIZE) (((SIZE) == ENSPI_INST_L_NONE) || \
                                   ((SIZE) == ENSPI_INST_L_04BIT) || \
                                   ((SIZE) == ENSPI_INST_L_08BIT) || \
                                   ((SIZE) == ENSPI_INST_L_16BIT))
																	 
/** QSPI_data_size : XSPI_CTRL0:DFS **/
#define DFS_04_BIT                  XSPI_CTRL0_DFS_4_BIT      //((uint32_t)0x00000003U)
#define DFS_08_BIT                  XSPI_CTRL0_DFS_8_BIT      //((uint32_t)0x00000007U)
#define DFS_16_BIT                  XSPI_CTRL0_DFS_16_BIT     //((uint32_t)0x0000000fU)
#define DFS_24_BIT                  XSPI_CTRL0_DFS_24_BIT     //((uint32_t)0x00000017U)
#define DFS_32_BIT                  XSPI_CTRL0_DFS_32_BIT     //((uint32_t)0x0000001fU)
#define IS_XSPI_DATASIZE(DATASIZE)  (((DATASIZE) == DFS_04_BIT) || \
                                    ((DATASIZE) == DFS_08_BIT) || \
                                    ((DATASIZE) == DFS_16_BIT) || \
                                    ((DATASIZE) == DFS_24_BIT) || \
                                    ((DATASIZE) == DFS_32_BIT))


/** @defgroup QSPI_Slave_Select_Toggle_Enable 
  * @{
  */
#define SSTE_BIT1                  XSPI_CTRL0_SSTE_EN       //((uint32_t)0x00004000)
#define SSTE_BIT0                  XSPI_CTRL0_SSTE_DISABLE  //((uint32_t)0x00000000)
#define IS_XSPI_SSTE_BIT(BIT)      (((BIT) == SSTE_BIT1) || \
                                   ((BIT) == SSTE_BIT0))


/** @defgroup QSPI_Clock_Polarity 
  * @{
  */	
#define SCPOL_LOW                  XSPI_CTRL0_SCPOL_LOW   //((uint32_t)0x00000000)
#define SCPOL_HIGH                 XSPI_CTRL0_SCPOL_HIGH  //((uint32_t)0x00000200)
#define IS_XSPI_CPOL(CPOL)         (((CPOL) == SCPOL_LOW) || \
                                   ((CPOL) == SCPOL_HIGH))
													 
/** @defgroup QSPI_Clock_Phase 
  * @{
  */

#define START_BIT                  XSPI_CTRL0_SCPH_FIRST_EDGE   //((uint32_t)0x00000000)
#define MIDDLE_BIT                 XSPI_CTRL0_SCPH_SECOND_EDGE  //((uint32_t)0x00000100)
#define IS_XSPI_CPHA(CPHA)         (((CPHA) == START_BIT) || \
                                   ((CPHA) == MIDDLE_BIT))
			
			
/** @defgroup QSPI_flags_definition 
  * @{
  */

#define XSPI_FLAG_BUSY             ((uint32_t)XSPI_STS_BUSY)    /* Bit[0] BUSY (Transfer Busy Flag) */
#define XSPI_FLAG_TFNF             ((uint32_t)XSPI_STS_TXFNF)   /* Bit[1] TXFNF (Transmit FIFO not Full)*/
#define XSPI_FLAG_TFE              ((uint32_t)XSPI_STS_TXFE)    /* Bit[2] TXFE (Transmit FIFO not Empty)*/
#define XSPI_FLAG_RFNE             ((uint32_t)XSPI_STS_RXFNE)   /* Bit[3] RXFNE (Receive FIFO not Empty)*/
#define XSPI_FLAG_RFF              ((uint32_t)XSPI_STS_RXFF)    /* Bit[4] RXFF (Receive FIFO not Full)*/
#define XSPI_FLAG_TXE              ((uint32_t)XSPI_STS_TXE)     /* Bit[5] TXE (Transmit FIFO error)*/
#define XSPI_FLAG_DCOL             ((uint32_t)XSPI_STS_DCERR)   /* Bit[6] DCERR (Data Conflict Error)*/

#define IS_XSPI_GET_FLAG(FLAG) (((FLAG) == XSPI_FLAG_BUSY) || ((FLAG) == XSPI_FLAG_TFNF) || \
                                   ((FLAG) == XSPI_FLAG_TFE) || ((FLAG) == XSPI_FLAG_RFNE) || \
                                   ((FLAG) == XSPI_FLAG_RFF) || ((FLAG) == XSPI_FLAG_TXE) || \
                                   ((FLAG) == XSPI_FLAG_DCOL))													 


/** @defgroup QSPI_clock_stretching_capability 
  * @{
  */
#define CLK_STRETCH_EN		         ((uint32_t)XSPI_ENH_CTRL0_CLKSTREN)//Enables clock stretching capability in SPI transfers.
#define CLK_STRETCH_DISABLE		     ((uint32_t)0x00000000)//Enables clock stretching capability in SPI transfers.
#define IS_XSPI_CLK_SC(SIZE)       (((SIZE) == CLK_STRETCH_EN) || \
                                   ((SIZE) == CLK_STRETCH_DISABLE))
#define XSPI_DMAReq_Tx             0x02
#define XSPI_DMAReq_Rx             0x01
#define IS_XSPI_DMAREQ(REQ)        (((REQ) == XSPI_DMAReq_Tx) || \
																				 ((REQ) == XSPI_DMAReq_Rx))		


#define XSPI_DMAATW_1BYTE	         ((uint32_t)0x00000000)
#define XSPI_DMAATW_2BYTE	         ((uint32_t)0x00000008)
#define XSPI_DMAATW_4BYTE          ((uint32_t)0x00000010)
#define XSPI_DMAATW_8BYTE	         ((uint32_t)0x00000018)
#define IS_XSPI_DMAATW(ATW)        (((ATW) == XSPI_DMAATW_1BYTE) || ((ATW) == XSPI_DMAATW_2BYTE)\
														       ((ATW) == XSPI_DMAATW_4BYTE) || ((ATW) == XSPI_DMAATW_8BYTE))						
#define DMA_ADDR_INC 			         ((uint32_t)0x00000040)		
#define DMA_ADDR_NINC 			       ((uint32_t)0x00000000)	
															     
#define XSPI_SLV_OUT_DISABLED      ((uint32_t)0x1000)    //Slave Output is disabled 
#define XSPI_SLV_OUT_EN            ((uint32_t)0x0000)    // Slave Output is enabled
													 
/** sets the number of data frames to be continuously received by the XSPI :XSPI_CTRL1**/
#define CTRL1_NDF_CNT 			        1024
#define CTRL1_NDF_0 			          0
#define CTRL1_NDF_1 			          1
#define CTRL1_NDF_8 			          8
#define CTRL1_NDF_16 			          16
#define CTRL1_NDF_63 			          63
#define CTRL1_NDF_127 			        127
#define CTRL1_NDF_255 			        255
#define IS_XSPI_NDF(NDF)            (((NDF) <= 0xFFFF))

/** SPI_BaudRate_Prescaler **/
//Fsclk_out = Fssi_clk/BAUD,BAUD = {SCKDV*2}
#define CLOCK_DIVI_MAX 			         0XFFFE
#define CLOCK_DIVIDER 			         0X1f
#define XSPI_SCLKOUT_DISABLE         ((uint32_t)0x00000000U)

#define XSPI_IT_FLAG_TYPE_M			     ((uint8_t)0x01U)
#define XSPI_IT_FLAG_TYPE_S			     ((uint8_t)0x02U)
#define XSPI_IT_FLAG_TYPE_R			     ((uint8_t)0x03U)

#define XSPI_IT_DONEM                ((uint16_t)0X00B5U)
#define XSPI_IT_SPITEM	             ((uint16_t)0X00A5U)
#define XSPI_IT_AXIEM	               ((uint16_t)0X0085U)
#define XSPI_IT_TXUIM	               ((uint16_t)0X0071U)    
#define XSPI_IT_XRXOIM	             ((uint16_t)0X0066U)    
#define XSPI_IT_MMCIM	               ((uint16_t)0X0054U)    
#define XSPI_IT_RXFFIM	             ((uint16_t)0X0045U)
#define XSPI_IT_RXFOIM	             ((uint16_t)0X0032U)    
#define XSPI_IT_RXFUIM	             ((uint16_t)0X0023U)    
#define XSPI_IT_TXFOIM	             ((uint16_t)0X0011U)    
#define XSPI_IT_TXFEIM	             ((uint16_t)0X0005U)

#define XSPI_DMAREQ_TX               ((uint16_t)0x0002U)    
#define XSPI_DMAREQ_RX               ((uint16_t)0x0001U)    

#define IS_XSPI_CONFIG_CLEAR_IT(IT)  (((IT) == XSPI_IT_DONEM) || ((IT) == XSPI_IT_SPITEM) || \
                                     ((IT) == XSPI_IT_AXIEM) || ((IT) == XSPI_IT_TXUIM || \
                                     ((IT) == XSPI_IT_XRXOIM || ((IT) == XSPI_IT_MSTIM) || \
                                     ((IT) == XSPI_IT_RXFIM || ((IT) == XSPI_IT_RXOIM) || \
                                     ((IT) == XSPI_IT_RXUIM || ((IT) == XSPI_IT_TXOIM) || \
                                     ((IT) == XSPI_IT_TXEIM))


/** @defgroup SPI_wati_cycle
  * @{
  */
#define WAIT_CYCLES(X)                ((uint32_t)X<<11) 
#define ENSPI_WAIT_8CYCLES	          ((uint32_t)0x00004000) //WAIT_CYCLES
#define ENSPI_WAIT_4CYCLES	          ((uint32_t)0x00002000) 
#define ENSPI_WAIT_2CYCLES	          ((uint32_t)0x00001000) 

#define NSS_SLECT                     (0X0F)   //(0X01)//Ƭѡ

/******** Bit definition for XIP_CTRL register  ********/
#define XIPR_PREFETCH_EN              ((uint32_t)0x20000000)
#define CONT_XFER_EN                  ((uint32_t)0x00800000)
#define INST_EN                       ((uint32_t)0x00400000)
#define DFS_HC_ENABLE                 ((uint32_t)0x00040000)
#define DFS_HC_DISABLE                ((uint32_t)0x00000000)
#define MD_BITS_EN                    ((uint32_t)0x00001000)

//xip���ú궨��
#define XIPR_ADDR_24BIT               ((uint32_t)0x00000060)
#define XIPR_ADDR_32BIT               ((uint32_t)0x00000080)
#define XIPR_ADDR_48BIT               ((uint32_t)0x000000c0)

#define XIPR_INST_16BIT               ((uint32_t)0x00000600)
#define XIPR_INST_8BIT                ((uint32_t)0x00000400)
#define XIPR_INST_4BIT                ((uint32_t)0x00000200)
#define XIPR_INST_NONE                ((uint32_t)0x00000000)

#define XIPW_ADDR_24BIT               ((uint32_t)0x00000060)
#define XIPW_ADDR_32BIT               ((uint32_t)0x00000080)
#define XIPW_ADDR_48BIT               ((uint32_t)0x000000c0)

#define XIPW_INST_16BIT               ((uint32_t)0x00000300)
#define XIPW_INST_8BIT                ((uint32_t)0x00000200)
#define XIPW_INST_4BIT                ((uint32_t)0x00000100)
#define XIPW_INST_NONE                ((uint32_t)0x00000000)

#define XIP_WAIT_CYCLES_20            ((uint32_t)0x00028000)
#define XIP_WAIT_CYCLES_8             ((uint32_t)0x00010000)
#define XIP_WAIT_CYCLES_6             ((uint32_t)0x0000c000)

#define XIPR_TRANS_TYPE_STANDRD       ((uint32_t)0x00000000)
#define XIPR_TRANS_TYPE_STANDRD_FRF   ((uint32_t)0x00000004)
#define XIPR_TRANS_TYPE_FRF           ((uint32_t)0x00000008)

#define XIPW_TRANS_TYPE_STANDRD       ((uint32_t)0x00000000)
#define XIPW_TRANS_TYPE_STANDRD_FRF   ((uint32_t)0x00000004)
#define XIPW_TRANS_TYPE_FRF           ((uint32_t)0x00000008)

#define XIPR_DUAL_SPI_FORMAT          ((uint32_t)0x00000001)
#define XIPR_QUAD_SPI_FORMAT          ((uint32_t)0x00000002)
#define XIPR_OCTAL_SPI_FORMAT         ((uint32_t)0x00000003)

#define XIPW_DUAL_SPI_FORMAT          ((uint32_t)0x00000001)
#define XIPW_QUAD_SPI_FORMAT          ((uint32_t)0x00000002)
#define XIPW_OCTAL_SPI_FORMAT         ((uint32_t)0x00000003)

#define XIP_MBL_2                     ((uint32_t)0x00000000)//XIP mode bit width
#define XIP_MBL_4                     ((uint32_t)0x04000000)//XIP mode bit width
#define XIP_MBL_8                     ((uint32_t)0x08000000)//XIP mode bit width
#define XIP_MBL_16                    ((uint32_t)0x0C000000)//XIP mode bit width

typedef enum
{
    XSPI_NULL = 0,
    XSPI_SUCCESS,
} XSPI_STATUS;
////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{		
    /*XSPI_CTRL0*/
	  uint32_t MST;
    uint32_t DFS;
    uint32_t FRF;		      //Frame Format	     Bits[7:6]		
    uint32_t SCPH;
    uint32_t SCPOL;
    uint32_t TMOD;
    uint32_t SSTE;
    uint32_t CFS;
    uint32_t SPIFRF;      //SPI Frame Format   Bits[23:22]
	  uint32_t WAITCYCLES;
    uint32_t INST_L;
    uint32_t ADDR_L;
  
    /*XSPI_CTRL1*/
    uint32_t NDF;

    /*XSPI_MW_CTRL*/
    uint32_t MWMOD;
    uint32_t MCDIR;
    uint32_t MHSEN;
		
    /*XSPI_SLAVE_EN*/
    uint32_t SEN;

    /*XSPI_BAUD*/
    uint32_t CLKDIV;
		 
    /*XSPI_TXFT*/
    //uint32_t TXFT;
		uint32_t TXFTST;
		uint32_t TXFTTEI;
		
    /*XSPI_RXFT*/
    uint32_t RXFT;

    /*XSPI_RS_DELAY*/
    uint32_t SDCN;
    uint32_t SES;

    /*XSPI_ENH_CTRL0*/
    uint32_t ENHANCED_TRANSTYPE;
    uint32_t ENHANCED_ADDR_L;
    uint32_t ENHANCED_INST_L;
    uint32_t ENHANCED_WAITCYCLES;
    uint32_t ENHANCED_WRSPIDDREN;
    uint32_t ENHANCED_WRINDDREN;
    uint32_t ENHANCED_CLKSTREN;
    
    /*XSPI_DDR_TXDE*/
    uint32_t TXDE;

    /*XSPI_XIP_MODE*/
    uint32_t XIPMDBITS;

    /*XSPI_XIP_INCR_TOC*/
    uint32_t ITOC;

    /*XSPI_XIP_WRAP_TOC*/
    uint32_t WTOC;
    
    /*XSPI_XIP_CTRL*/
    uint32_t XIP_FRF;
    uint32_t XIP_TRANSTYPE;
    uint32_t XIP_ADDRL;
    uint32_t XIP_INST_L;
    uint32_t XIPMDBITS_EN;
    uint32_t XIP_WAITCYCLES;
    uint32_t XIPDFSHC;
    uint32_t XIP_DDREN;
    uint32_t XIP_WRINDDREN;
    uint32_t XIPINSTEN;
    uint32_t XIPCTEN;
    uint32_t XIPMBL;
    uint32_t XIPPREEN;

    /*XSPI_XIP_TOUT*/
    uint32_t XTOUT;

} XSPI_InitType;

enum DDR_SET_TYPE
{
	XSPI_INST_DDR_EN =0,//
	XSPI_SPI_DDR_EN =1,
	XSPI_INSTANDSPI_DDR_EN,
	XIP_READ_INST_DDR_EN,
	XIP_READ_IDDR_EN,
	XIP_READ_INSTANDSPI_DDR_EN,
	XIP_WRITE_INST_DDR_EN,
	XIP_WRITE_IDDR_EN,
	XIP_WRITE_INSTANDSPI_DDR_EN,
};


////////////////////////////////////////////////////////////////////////////////////////////////////
void XSPI_DeInit(XSPI_Module* xSPIx);
void XSPI_Init(XSPI_Module* xSPIx, XSPI_InitType* XSPI_InitStruct);
void XSPI_StructInit(XSPI_InitType* XSPI_InitStruct);
void XSPI_Cmd(XSPI_Module* xSPIx, FunctionalState cmd);
void XSPI_XIP_Cmd(XSPI_Module* xSPIx, FunctionalState cmd);
void XSPI_SetTransType(XSPI_Module* xSPIx, uint32_t TransType);
void XSPI_SetWaitCycles(XSPI_Module* xSPIx, uint32_t WAITCYCLES);
void XSPI_SetRXFIFOLevel(XSPI_Module* xSPIx, uint32_t fifo_len);
void XSPI_SetTXFIFOLevel(XSPI_Module* xSPIx, uint32_t fifo_len);
void XSPI_SetTXFIFOStartLevel(XSPI_Module* xSPIx, uint32_t fifo_len);
uint8_t XSPI_GetRXFIFOLevel(XSPI_Module* xSPIx);
uint8_t XSPI_GetTXFIFOLevel(XSPI_Module* xSPIx);
uint32_t XSPI_GetDataPointer(XSPI_Module* xSPIx);
void XSPI_SetTxFifoStartTransferLevel(XSPI_Module* xSPIx,uint16_t Level);
uint32_t XSPI_ReadRxFifoNum(XSPI_Module* xSPIx);
uint32_t XSPI_ReadTxFifoNum(XSPI_Module* xSPIx);
void XSPI_SendData(XSPI_Module* xSPIx, uint32_t SendData);
uint32_t XSPI_ReceiveData(XSPI_Module* xSPIx);
FlagStatus XSPI_GetFlagStatus(XSPI_Module* xSPIx, uint32_t XSPI_FLAG);
uint16_t XSPI_GetINTStatus(XSPI_Module* xSPIx, uint16_t FLAG);
void XSPI_ClearITBit(XSPI_Module* xSPIx, uint16_t XSPI_IT);
void XSPI_ConfigInt(XSPI_Module* xSPIx, uint16_t XSPI_IT, FunctionalState Cmd);
void XSPI_ConfigDMATxLevel(XSPI_Module* xSPIx, uint32_t TxDataLevel);
void XSPI_ConfigDMARxLevel(XSPI_Module* xSPIx, uint32_t RxDataLevel);
void XSPI_EnableDMA(XSPI_Module* xSPIx, uint32_t XSPI_DMAReq, FunctionalState Cmd);
FlagStatus XSPI_GetBusyStatus(XSPI_Module* xSPIx);
FlagStatus XSPI_GetTxDataBusyStatus(XSPI_Module* xSPIx);
FlagStatus XSPI_GetTxDataEmptyStatus(XSPI_Module* xSPIx);
FlagStatus XSPI_GetRxHaveDataStatus(XSPI_Module* xSPIx);
FlagStatus XSPI_GetRxDataFullStatus(XSPI_Module* xSPIx);
FlagStatus XSPI_GetDataConflictErrorStatus(XSPI_Module* xSPIx);
void XSPI_ClrFifo(XSPI_Module* xSPIx);
uint32_t XSPI_GetFifoData(XSPI_Module* xSPIx, uint32_t* pData, uint32_t Len);
void XSPI_SendAndGetWords(XSPI_Module* xSPIx, uint32_t* pSrcData, uint32_t* pDstData, uint32_t cnt);
uint32_t XSPI_SendWordAndGetWords(XSPI_Module* xSPIx, uint32_t WrData, uint32_t* pRdData, uint8_t LastRd);
void XSPI_Slave_Enable(XSPI_Module* xSPIx, uint8_t cmdData);
//================
uint8_t xSPI_Wait_Flag(XSPI_Module* xSPIx,uint32_t flag,uint8_t sta,uint64_t wtime);
uint8_t xSPI_Wait_TransferComplete(XSPI_Module* xSPIx,uint64_t wtime);
void xSPI_TXFifoLevel(XSPI_Module* xSPIx,u16 FifoLevel);
void xSPI_BaudRateSelect(XSPI_Module* xSPIx,uint32_t BAUDR_Value);
void xSPI_RXSampleDelay(XSPI_Module* xSPIx,uint32_t Sampling_Edge,uint32_t SampleDelay);
void SetXspi_InstAddrWaitcycle_phase(XSPI_Module* xSPIx, u32 inst_l, u32 addr_l, u32 wait_cycle);
void SetXspi_TransType(XSPI_Module* xSPIx, u32 type);
void Set_xSPI_DDR(XSPI_Module* xSPIx, u32 set_type);
void xSPI_Clear_RXFIFO(XSPI_Module* xSPIx);
#ifdef __cplusplus
}
#endif

#endif /*__n32h76x_78x_XSPI_H__ */

