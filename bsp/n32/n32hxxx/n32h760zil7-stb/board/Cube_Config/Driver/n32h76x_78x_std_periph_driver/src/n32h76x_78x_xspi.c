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
 * @file n32h76x_78x_xspi.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#include "n32h76x_78x_xspi.h"
#include "n32h76x_78x_rcc.h"

/** N32H76X_78X_StdPeriph_Driver **/

/**
*\*\name    XSPI_DeInit.
*\*\fun     Deinitializes the XSPI peripheral registers to its default reset values.
*\*\return  none
**/
void XSPI_DeInit(XSPI_Module* xSPIx)
{
    if(xSPIx == xSPI1)
    {
        RCC_EnableAXIPeriphReset4(RCC_AXI_PERIPHRST_XSPI1);
    }
    else if(xSPIx == xSPI2)
    {
        RCC_EnableAXIPeriphReset4(RCC_AXI_PERIPHRST_XSPI2);
    }
}

/**
*\*\name    XSPIInitConfig.
*\*\fun     Merge configuration from the buffer of XSPI para struct, then write it into related registers.
*\*\param   XSPI_InitStruct :
*\*\          - FRF
*\*\          - SPIFRF
*\*\          - TMOD
*\*\          - SCPOL
*\*\          - SCPH
*\*\          - DFS
*\*\          - SSTE
*\*\          - SEN
*\*\          - CLKDIV
*\*\          - WAITCYCLES
*\*\          - INST_L
*\*\          - ADDRL
*\*\          - NDF
*\*\          - TXFT
*\*\          - RXFT
*\*\          - ENHANCED_WAITCYCLES
*\*\          - ENHANCED_CLKSTREN
*\*\          - ENHANCED_ADDR_L
*\*\          - ENHANCED_INST_L
*\*\          - ENHANCED_TRANSTYPE
*\*\          - ENHANCED_WRSPIDDREN;
*\*\          - ENHANCED_WRINDDREN;
*\*\          - XIP_FRF
*\*\          - XIP_TRANSTYPE
*\*\          - XIP_ADDRL
*\*\          - XIP_INST_L
*\*\          - XIP_WAITCYCLES
*\*\          - XIPDFSHC
*\*\          - XIPINSTEN
*\*\          - XIPCTEN
*\*\          - XIPINSTEN
*\*\          - XIPMBL
*\*\          - XIP_WRINDDREN
*\*\          - XIP_DDREN
*\*\          - XIPDFSHC
*\*\          - XIPMDBITS
*\*\          - ITOC
*\*\          - WTOC
*\*\          - XTOUT
*\*\          - CFS
*\*\          - MWMOD
*\*\          - MCDIR
*\*\          - MHSEN
*\*\          - TXFN
*\*\          - RXFN
*\*\          - SDCN
*\*\          - SES
*\*\          - TXDE
*\*\return  none
**/
void XSPI_Init(XSPI_Module* xSPIx, XSPI_InitType* XSPI_InitStruct)
{
    uint32_t tmpregister = 0;

    if((XSPI_InitStruct->SPIFRF) == XSPI_CTRL0_SPIFRF_STANDARD_FORMAT)
    {
        tmpregister |= (uint32_t)(XSPI_InitStruct->MST | XSPI_InitStruct->FRF | XSPI_InitStruct->SPIFRF | XSPI_InitStruct->SSTE
                                  | XSPI_InitStruct->TMOD | XSPI_InitStruct->SCPOL |  XSPI_InitStruct->SCPH | XSPI_InitStruct->DFS | XSPI_InitStruct->CFS);

        xSPIx->CTRL0 = tmpregister;

        tmpregister = xSPIx->CTRL1;
        tmpregister &= XSPI_NDF_MASK;
        tmpregister |= XSPI_InitStruct->NDF;
        xSPIx->CTRL1 = tmpregister;

        tmpregister = 0;
        tmpregister = (uint32_t)(XSPI_InitStruct->MWMOD | XSPI_InitStruct->MCDIR | XSPI_InitStruct->MHSEN);
        xSPIx->MW_CTRL  = tmpregister;

        xSPIx->BAUD = XSPI_InitStruct->CLKDIV;

        tmpregister = xSPIx->TXFT;
        tmpregister &= XSPI_TXFT_MASK;
        tmpregister = tmpregister | ((XSPI_InitStruct->TXFTST << 16) | XSPI_InitStruct->TXFTTEI);
        xSPIx->TXFT = tmpregister;

        xSPIx->RXFT = XSPI_InitStruct->RXFT;

        xSPIx->DDR_TXDE  = XSPI_InitStruct->TXDE;

        tmpregister = 0;
        tmpregister = (uint32_t)(((XSPI_InitStruct->SES << 16) | XSPI_InitStruct->SDCN) & 0x000100ff);
        xSPIx->RX_DELAY  = tmpregister;

        tmpregister = (uint32_t)(XSPI_InitStruct->ENHANCED_CLKSTREN | XSPI_InitStruct->ENHANCED_INST_L
                                 | XSPI_InitStruct->ENHANCED_ADDR_L | XSPI_InitStruct->ENHANCED_TRANSTYPE | XSPI_InitStruct->ENHANCED_INST_L | XSPI_InitStruct->ENHANCED_WAITCYCLES
                                 | XSPI_InitStruct->ENHANCED_WAITCYCLES | XSPI_InitStruct->ENHANCED_INST_L | XSPI_InitStruct->ENHANCED_ADDR_L);


        xSPIx->ENH_CTRL0 = tmpregister;
    }
    else if((XSPI_InitStruct->SPIFRF) == XSPI_CTRL0_SPIFRF_DUAL_FORMAT)
    {
        tmpregister |= (uint32_t)(XSPI_InitStruct->MST | XSPI_InitStruct->SPIFRF | XSPI_InitStruct->TMOD
                                  | XSPI_InitStruct->SSTE | XSPI_InitStruct->SCPOL |  XSPI_InitStruct->SCPH | XSPI_InitStruct->DFS | XSPI_InitStruct->CFS);

        xSPIx->CTRL0 = tmpregister;

        tmpregister = xSPIx->CTRL1;
        tmpregister &= XSPI_NDF_MASK;
        tmpregister |= XSPI_InitStruct->NDF;
        xSPIx->CTRL1 = tmpregister;

        tmpregister = 0;
        tmpregister = (uint32_t)(XSPI_InitStruct->MWMOD | XSPI_InitStruct->MCDIR | XSPI_InitStruct->MHSEN);
        xSPIx->MW_CTRL  = tmpregister;

        xSPIx->BAUD = XSPI_InitStruct->CLKDIV;

        tmpregister = xSPIx->TXFT;
        tmpregister &= XSPI_TXFT_MASK;
        tmpregister = tmpregister | ((XSPI_InitStruct->TXFTST << 16) | XSPI_InitStruct->TXFTTEI);
        xSPIx->TXFT = tmpregister;

        xSPIx->RXFT = XSPI_InitStruct->RXFT;

        xSPIx->DDR_TXDE  = XSPI_InitStruct->TXDE;

        tmpregister = 0;
        tmpregister = (uint32_t)(((XSPI_InitStruct->SES << 16) | XSPI_InitStruct->SDCN) & 0x000100ff);
        xSPIx->RX_DELAY  = tmpregister;

        tmpregister = 0;
        tmpregister |= (uint32_t)(XSPI_InitStruct->ENHANCED_CLKSTREN | XSPI_InitStruct->ENHANCED_ADDR_L | XSPI_InitStruct->ENHANCED_INST_L
                                  | XSPI_InitStruct->ENHANCED_WAITCYCLES | XSPI_InitStruct->ENHANCED_TRANSTYPE | XSPI_InitStruct->ENHANCED_WRINDDREN
                                  | XSPI_InitStruct->ENHANCED_WRSPIDDREN );
        xSPIx->ENH_CTRL0 = tmpregister;

        tmpregister = 0;
        tmpregister = (uint32_t)(XSPI_InitStruct->XIPMBL | XSPI_InitStruct->XIPCTEN | XSPI_InitStruct->XIPINSTEN | XSPI_InitStruct->XIP_WRINDDREN
                                 | XSPI_InitStruct->XIP_DDREN | XSPI_InitStruct->XIPDFSHC | XSPI_InitStruct->XIP_WAITCYCLES | XSPI_InitStruct->XIPMDBITS_EN
                                 | XSPI_InitStruct->XIP_INST_L | XSPI_InitStruct->XIP_ADDRL | XSPI_InitStruct->XIP_TRANSTYPE | XSPI_InitStruct->XIP_FRF | XSPI_InitStruct->XIPPREEN);
        xSPIx->XIP_CTRL = tmpregister;

        xSPIx->XIP_MODE      = XSPI_InitStruct->XIPMDBITS;
        xSPIx->XIP_INCR_TOC  = XSPI_InitStruct->ITOC;
        xSPIx->XIP_WRAP_TOC  = XSPI_InitStruct->WTOC;
        xSPIx->XIP_TOUT  = XSPI_InitStruct->XTOUT;
    }
    else if((XSPI_InitStruct->SPIFRF) == XSPI_CTRL0_SPIFRF_QUAD_FORMAT || (XSPI_InitStruct->SPIFRF) == XSPI_CTRL0_SPIFRF_OCTAL_FORMAT)
    {
        tmpregister |= (uint32_t)(XSPI_InitStruct->MST | XSPI_InitStruct->SPIFRF | XSPI_InitStruct->SSTE  | XSPI_InitStruct->TMOD
                                  | XSPI_InitStruct->SCPOL |  XSPI_InitStruct->SCPH | XSPI_InitStruct->DFS);

        xSPIx->CTRL0 = tmpregister;

        tmpregister = xSPIx->CTRL1;
        tmpregister &= XSPI_NDF_MASK;
        tmpregister |= XSPI_InitStruct->NDF;
        xSPIx->CTRL1 = tmpregister;

        tmpregister = 0;
        tmpregister = (uint32_t)(XSPI_InitStruct->MWMOD | XSPI_InitStruct->MCDIR | XSPI_InitStruct->MHSEN);
        xSPIx->MW_CTRL  = tmpregister;

        xSPIx->BAUD = XSPI_InitStruct->CLKDIV;

        tmpregister = xSPIx->TXFT;
        tmpregister &= XSPI_TXFT_MASK;
        tmpregister = tmpregister | ((XSPI_InitStruct->TXFTST << 16) | XSPI_InitStruct->TXFTTEI);
        xSPIx->TXFT = tmpregister;

        xSPIx->RXFT = XSPI_InitStruct->RXFT;

        xSPIx->DDR_TXDE  = XSPI_InitStruct->TXDE;

        tmpregister = 0;
        tmpregister = (uint32_t)(((XSPI_InitStruct->SES << 16) | XSPI_InitStruct->SDCN) & 0x000100ff);
        xSPIx->RX_DELAY  = tmpregister;

        tmpregister = 0;
        tmpregister |= (uint32_t)(XSPI_InitStruct->ENHANCED_CLKSTREN | XSPI_InitStruct->ENHANCED_ADDR_L | XSPI_InitStruct->ENHANCED_INST_L
                                  | XSPI_InitStruct->ENHANCED_WAITCYCLES | XSPI_InitStruct->ENHANCED_TRANSTYPE | XSPI_InitStruct->ENHANCED_WRINDDREN
                                  | XSPI_InitStruct->ENHANCED_WRSPIDDREN );
        xSPIx->ENH_CTRL0 = tmpregister;

        tmpregister = 0;
        tmpregister = (uint32_t)(XSPI_InitStruct->XIPMBL | XSPI_InitStruct->XIPCTEN | XSPI_InitStruct->XIPINSTEN | XSPI_InitStruct->XIP_WRINDDREN
                                 | XSPI_InitStruct->XIP_DDREN | XSPI_InitStruct->XIPDFSHC | XSPI_InitStruct->XIP_WAITCYCLES | XSPI_InitStruct->XIPMDBITS_EN
                                 | XSPI_InitStruct->XIP_INST_L | XSPI_InitStruct->XIP_ADDRL | XSPI_InitStruct->XIP_TRANSTYPE | XSPI_InitStruct->XIP_FRF | XSPI_InitStruct->XIPPREEN);
        xSPIx->XIP_CTRL = tmpregister;

        xSPIx->XIP_MODE  = XSPI_InitStruct->XIPMDBITS;
        xSPIx->XIP_INCR_TOC  = XSPI_InitStruct->ITOC;
        xSPIx->XIP_WRAP_TOC  = XSPI_InitStruct->WTOC;
        xSPIx->XIP_TOUT  = XSPI_InitStruct->XTOUT;

    }
    else {}

    xSPIx->SLAVE_EN = XSPI_InitStruct->SEN;
}

/**
*\*\name    XSPI_StructInit.
*\*\fun     Fills each XSPI_InitStruct member with its default value.
*\*\param   XSPI_InitStruct :
*\*\          - FRF
*\*\          - SPIFRF
*\*\          - TMOD
*\*\          - SCPOL
*\*\          - SCPH
*\*\          - DFS
*\*\          - SSTE
*\*\          - SEN
*\*\          - CLKDIV
*\*\          - WAITCYCLES
*\*\          - INST_L
*\*\          - ADDRL
*\*\          - NDF
*\*\          - TXFT
*\*\          - RXFT
*\*\          - ENHANCED_WAITCYCLES
*\*\          - ENHANCED_CLKSTREN
*\*\          - ENHANCED_ADDR_L
*\*\          - ENHANCED_INST_L
*\*\          - ENHANCED_TRANSTYPE
*\*\          - ENHANCED_WRSPIDDREN;
*\*\          - ENHANCED_WRINDDREN;
*\*\          - XIP_FRF
*\*\          - XIP_TRANSTYPE
*\*\          - XIP_ADDRL
*\*\          - XIP_INST_L
*\*\          - XIP_WAITCYCLES
*\*\          - XIPDFSHC
*\*\          - XIPINSTEN
*\*\          - XIPCTEN
*\*\          - XIPINSTEN
*\*\          - XIPMBL
*\*\          - XIP_WRINDDREN
*\*\          - XIP_DDREN
*\*\          - XIPDFSHC
*\*\          - XIPMDBITS
*\*\          - ITOC
*\*\          - WTOC
*\*\          - XTOUT
*\*\          - CFS
*\*\          - MWMOD
*\*\          - MCDIR
*\*\          - MHSEN
*\*\          - TXFN
*\*\          - RXFN
*\*\          - SDCN
*\*\          - SES
*\*\          - TXDE
*\*\return  none
**/
void XSPI_StructInit(XSPI_InitType* XSPI_InitStruct)
{
    XSPI_InitStruct->	FRF	                  = 0;
    XSPI_InitStruct->	SPIFRF	              = 0;
    XSPI_InitStruct->	TMOD	                = 0;
    XSPI_InitStruct->	SCPOL		              = 0;
    XSPI_InitStruct->	SCPH	                = 0;
    XSPI_InitStruct->	DFS	                  = 0;
    XSPI_InitStruct->	SSTE	                = 0;
    XSPI_InitStruct->	SEN		                = 0;
    XSPI_InitStruct->	CLKDIV	              = 0;
    XSPI_InitStruct->	WAITCYCLES	          = 0;
    XSPI_InitStruct->	INST_L	              = 0;
    XSPI_InitStruct->	ADDR_L	              = 0;
    XSPI_InitStruct->	NDF		                = 0;
    XSPI_InitStruct->	TXFTST                = 0;
    XSPI_InitStruct->	TXFTTEI               = 0;
    XSPI_InitStruct->	RXFT	                = 0;
    XSPI_InitStruct->	ENHANCED_WAITCYCLES		= 0;
    XSPI_InitStruct->	ENHANCED_CLKSTREN		  = 0;
    XSPI_InitStruct->	ENHANCED_ADDR_L		    = 0;
    XSPI_InitStruct->	ENHANCED_INST_L	      = 0;
    XSPI_InitStruct->	ENHANCED_TRANSTYPE		= 0;
    XSPI_InitStruct->	ENHANCED_WRSPIDDREN	  = 0;
    XSPI_InitStruct->	ENHANCED_WRINDDREN		= 0;
    XSPI_InitStruct->	XIP_FRF	              = 0;
    XSPI_InitStruct->	XIP_TRANSTYPE	        = 0;
    XSPI_InitStruct->	XIP_ADDRL	            = 0;
    XSPI_InitStruct->	XIP_INST_L		        = 0;
    XSPI_InitStruct->	XIP_WAITCYCLES		    = 0;
    XSPI_InitStruct->	XIPDFSHC	            = 0;
    XSPI_InitStruct->	XIPMBL	              = 0;
    XSPI_InitStruct->	XIPINSTEN		          = 0;
    XSPI_InitStruct->	XIPPREEN	            = 0;
    XSPI_InitStruct->	XIPCTEN	              = 0;
    XSPI_InitStruct->	XIP_WRINDDREN	        = 0;
    XSPI_InitStruct->	XIP_DDREN	            = 0;
    XSPI_InitStruct->	XIPMDBITS_EN	        = 0;
    XSPI_InitStruct->	XIPMDBITS	            = 0;
    XSPI_InitStruct->	ITOC                  = 0;
    XSPI_InitStruct->	WTOC 	                = 0;
    XSPI_InitStruct->	XTOUT                 = 0;
    XSPI_InitStruct->	CFS 	                = 0;
    XSPI_InitStruct->	MWMOD                 = 0;
    XSPI_InitStruct->	MCDIR                 = 0;
    XSPI_InitStruct->	MHSEN                 = 0;
    XSPI_InitStruct->	SDCN                  = 0;
    XSPI_InitStruct->	SES                   = 0;
    XSPI_InitStruct->	TXDE                  = 0;
}

/**
*\*\name    XSPI_Cmd.
*\*\fun     Control XSPI function switch.
*\*\param   cmd
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void XSPI_Cmd(XSPI_Module* xSPIx, FunctionalState cmd)
{
    if (cmd != DISABLE)
    {
        xSPIx->SSIENR |= XSPI_EN_XSPIEN;
    }
    else
    {
        xSPIx->SSIENR &= ~XSPI_EN_XSPIEN;
    }
}

/**
*\*\name    XSPI_XIP_Cmd.
*\*\fun     Control XSPI XIP function switch.
*\*\param   cmd
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void XSPI_XIP_Cmd(XSPI_Module* xSPIx, FunctionalState cmd)
{
    if (cmd != DISABLE)
    {
        xSPIx->XIP_SLAVE_EN |= XSPI_XIP_SLAVE_EN_SEN;
    }
    else
    {
        xSPIx->XIP_SLAVE_EN &= ~XSPI_XIP_SLAVE_EN_SEN;
    }
}


/**
*\*\name    XSPI_Slave_Enable.
*\*\fun     XSPI_Slave_Enable register config.
*\*\param   cmdData: config data
*\*\
*\*\return  none
**/
void XSPI_Slave_Enable(XSPI_Module* xSPIx, uint8_t cmdData)
{
    xSPIx->SLAVE_EN = cmdData;
}

/**
*\*\name    XSPI_SetTransType.
*\*\fun     Set the format of address and instruction sending (1/2/4/8 wire mode)
*\*\param   TransType
*\*\          - XSPI_ENH_CTRL0_TRANSTYPE_STANDARD
*\*\          - XSPI_ENH_CTRL0_TRANSTYPE_ADDRESS_BY_FRF
*\*\          - XSPI_ENH_CTRL0_TRANSTYPE_ALL_BY_FRF
*\*\return  none
**/
void XSPI_SetTransType(XSPI_Module* xSPIx, uint32_t TransType)
{
    xSPIx->ENH_CTRL0 &= XSPI_TRANSTYPE_MASK;
    xSPIx->ENH_CTRL0 |= TransType;
}


/**
*\*\name    XSPI_SetWaitCycles.
*\*\fun     Set the number of empty instruction cycles to wait
*\*\param   WAITCYCLES:
*\*\          - XSPI_ENH_CTRL0_WAIT_1CYCLES
*\*\          - ...
*\*\          - XSPI_ENH_CTRL0_WAIT_31CYCLES
*\*\return  none
**/
void XSPI_SetWaitCycles(XSPI_Module* xSPIx, uint32_t WAITCYCLES)
{
    xSPIx->ENH_CTRL0 &= XSPI_WAITCYCLES_MASK;
    xSPIx->ENH_CTRL0 |= WAITCYCLES;
}

/**
*\*\name    XSPI_SetRXFIFOLevel.
*\*\fun     Set Rx fifo transmission threshold, trigger full interrupt threshold
*\*\param   fifo_len:
*\*\          - 0x0-0xF
*\*\return  none
**/
void XSPI_SetRXFIFOLevel(XSPI_Module* xSPIx, uint32_t fifo_len)
{
    xSPIx->RXFT &= XSPI_RXFTLR_MASK;
    xSPIx->RXFT |= fifo_len;
}

/**
*\*\name    XSPI_SetTXFIFOLevel.
*\*\fun     Set the Tx fifo transmission threshold and trigger the interrupt threshold
*\*\param   fifo_len:
*\*\          - 0x0-0xF
*\*\return  none
**/
void XSPI_SetTXFIFOLevel(XSPI_Module* xSPIx, uint32_t fifo_len)
{
    xSPIx->TXFT &= XSPI_TXFTLITR_MASK;
    xSPIx->TXFT |= fifo_len;
}

/**
*\*\name    XSPI_SetTXFIFOStartLevel.
*\*\fun     Set Tx fifo start transmission threshold
*\*\param   fifo_len:
*\*\          - 0x0-0xF
*\*\return  none
**/
void XSPI_SetTXFIFOStartLevel(XSPI_Module* xSPIx, uint32_t fifo_len)
{
    xSPIx->TXFT &= XSPI_TXFTLR_MASK;
    xSPIx->TXFT |= (fifo_len << 16);
}


/**
*\*\name    XSPI_GetRXFIFOLevel.
*\*\fun     Get the amount of data in the Rx fifo
*\*\return  Amount of data in Rx fifo.
**/
uint8_t XSPI_GetRXFIFOLevel(XSPI_Module* xSPIx)
{
    return xSPIx->RXFT;
}

/**
*\*\name    XSPI_GetTXFIFOLevel.
*\*\fun     Get the amount of data in the Tx fifo
*\*\return  Amount of data in Tx fifo.
**/
uint8_t XSPI_GetTXFIFOLevel(XSPI_Module* xSPIx)
{
    return xSPIx->TXFT;
}

/**
*\*\name    XSPIGetDataPointer.
*\*\fun     Get Pointer of XSPI DAT0 register.
*\*\return  The pointer of XSPI DAT0 register.
**/
uint32_t XSPI_GetDataPointer(XSPI_Module* xSPIx)
{
    return (uint32_t)&xSPIx->DAT0;
}

/**
*\*\name    XSPI_ReadRxFifoNum.
*\*\fun     Read value from XSPI RXFN register which shows the number of the data from receive fifo.
*\*\return  The number of the data from receive fifo.
**/
void XSPI_SetTxFifoStartTransferLevel(XSPI_Module* xSPIx, uint16_t Level)
{
    u32 tmp = xSPIx->TXFT;
    tmp &= ~(0XFFFF0000);
    tmp |= (Level << 16);
    xSPIx->TXFT = tmp;
}
/**
*\*\name    XSPI_ReadRxFifoNum.
*\*\fun     Read value from XSPI RXFN register which shows the number of the data from receive fifo.
*\*\return  The number of the data from receive fifo.
**/
uint32_t XSPI_ReadRxFifoNum(XSPI_Module* xSPIx)
{
    return xSPIx->RXFN;
}

/**
*\*\name    XSPI_ReadTxFifoNum.
*\*\fun     Read value from XSPI TXFN register which shows the number of the data from tx fifo.
*\*\return  The number of the data from tx fifo.
**/
uint32_t XSPI_ReadTxFifoNum(XSPI_Module* xSPIx)
{
    return xSPIx->TXFN;
}

/**
*\*\name    XSPI_SendData.
*\*\fun     Write one data direct to XSPI DAT0 register to send.
*\*\param   SendData:
*\*\          - data to be send
*\*\return  none
**/
void XSPI_SendData(XSPI_Module* xSPIx, uint32_t SendData)
{
    /* Write in the DAT0 register the data to be sent */
    xSPIx->DAT0 = SendData;
}


/**
*\*\name    XSPI_ReceiveData.
*\*\fun     Read one data from XSPI DAT0 register.
*\*\return  The value of XSPI DAT0 register.
**/
uint32_t XSPI_ReceiveData(XSPI_Module* xSPIx)
{
    /* Return the data in the DAT0 register */
    return xSPIx->DAT0;
}


/**
*\*\name    XSPI_GetFlagStatus.
*\*\fun     Checks whether the specified XSPI flag is set or not.
*\*\param   XSPI_FLAG:
*\*\          - XSPI_STS_BUSY
*\*\          - XSPI_STS_TXFNF
*\*\          - XSPI_STS_TXFE
*\*\          - XSPI_STS_RXFNE
*\*\          - XSPI_STS_RXFF
*\*\          - XSPI_STS_TXE
*\*\          - XSPI_STS_DCERR
*\*\return  The new state of XSPI_FLAG (SET or RESET).
**/
FlagStatus XSPI_GetFlagStatus(XSPI_Module* xSPIx, uint32_t XSPI_FLAG)
{
    FlagStatus bitstatus ;

    /* Check the status of the specified XSPI flag */
    if ((xSPIx->STS & XSPI_FLAG) != (uint32_t)RESET)
    {
        /* XSPI_FLAG is set */
        bitstatus = SET;
    }
    else
    {
        /* XSPI_FLAG is reset */
        bitstatus = RESET;
    }

    /* Return the XSPI_FLAG status */
    return  bitstatus;
}


/**
*\*\name    XSPI_GetINTStatus.
*\*\fun     Checks whether the specified XSPI interrupt has occurred or not.
*\*\param   FLAG:
*\*\          - XSPI_ISTS_TXFEIS
*\*\          - XSPI_ISTS_TXFOIS
*\*\          - XSPI_ISTS_RXFUIS
*\*\          - XSPI_ISTS_RXFOIS
*\*\          - XSPI_ISTS_RXFFIS
*\*\          - XSPI_ISTS_MMCIS
*\*\          - XSPI_ISTS_XRXOIS
*\*\          - XSPI_ISTS_TXUIS
*\*\return  The new state of XSPI_IT (SET or RESET).
**/
uint16_t XSPI_GetINTStatus(XSPI_Module* xSPIx, uint16_t FLAG)
{
    uint16_t tmp;
    tmp = xSPIx->ISTS & FLAG;

    if (tmp == 1)
        return 1;
    else
        return 0;
}

/**
*\*\name    XSPI_ClearITBit.
*\*\fun     Checks whether the specified XSPI interrupt has occurred or not.
*\*\param   XSPI_IT:
*\*\          - XSPI_IT_TXUIM
*\*\          - XSPI_IT_XRXOIM
*\*\          - XSPI_IT_MMCIM
*\*\          - XSPI_IT_RXFFIM
*\*\          - XSPI_IT_RXFOIM
*\*\          - XSPI_IT_RXFUIM
*\*\          - XSPI_IT_TXFOIM
*\*\          - XSPI_IT_TXFEIM
*\*\return  none.
**/
void XSPI_ClearITBit(XSPI_Module* xSPIx, uint16_t XSPI_IT)
{
    uint16_t itpos;

    /* Get the SPI IT index */
    itpos = (XSPI_IT & 0x0F);

    /* Clear the selected Error interrupt pending bit */
    if(itpos == 1)
    {
        (void)xSPIx->TXEICR_CLR; //Clear Transmit FIFO Overflow/Underflow Interrupt
    }
    else if(itpos == 2)
    {
        (void)xSPIx->RXFOI_CLR;  //Clear Receive FIFO Overflow Interrupt.
    }
    else if(itpos == 3)
    {
        (void)xSPIx->RXFUI_CLR;  //Clear Receive FIFO Underflow Interrupt.
    }
    else if(itpos == 4)         //Receive FIFO Underflow Interrupt Clear
    {
        (void)xSPIx->MMCI_CLR;   //Clear Multi-Master Contention Interrupt
    }
    else if(itpos == 6)
    {
        (void)xSPIx->XIP_RXFOI_CLR; //Clear XIP Receive FIFO Overflow Interrupt.
    }
    else
    {
        (void)xSPIx->ICLR;
    }
}

/**
*\*\name    XSPI_ConfigInt.
*\*\fun     Enables or disables the specified XSPI interrupts.
*\*\param   XSPI_IT:
*\*\          - XSPI_IT_TXUIM
*\*\          - XSPI_IT_XRXOIM
*\*\          - XSPI_IT_MMCIM
*\*\          - XSPI_IT_RXFFIM
*\*\          - XSPI_IT_RXFOIM
*\*\          - XSPI_IT_RXFUIM
*\*\          - XSPI_IT_TXFOIM
*\*\          - XSPI_IT_TXFEIM
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none.
**/
void XSPI_ConfigInt(XSPI_Module* xSPIx, uint16_t XSPI_IT, FunctionalState Cmd)
{
    uint16_t itpos, itmask;

    /* Get the XSPI IT index */
    itpos = XSPI_IT >> 4;

    /* Set the IT mask */
    itmask = (uint16_t)1 << (uint16_t)itpos;

    if (Cmd != DISABLE)
    {
        /* Enable the selected XSPI interrupt */
        xSPIx->IMASK |= itmask;
    }
    else
    {
        /* Disable the selected XSPI interrupt */
        xSPIx->IMASK &= (uint16_t)~itmask;
    }
}

/**
*\*\name    XSPI_ConfigDMATxLevel.
*\*\fun     Configuration of XSPI DMA Tx Level.
*\*\param   TxDataLevel(transmit data):
*\*\          - 0~0x1F
*\*\return  none.
**/
void XSPI_ConfigDMATxLevel(XSPI_Module* xSPIx, uint32_t TxDataLevel)
{
    xSPIx->DMATDL_CTRL = TxDataLevel;
}


/**
*\*\name    XSPI_ConfigDMARxLevel.
*\*\fun     Configuration of XSPI DMA Rx Level.
*\*\param   RxDataLevel(receive data):
*\*\          - 0~0x1F
*\*\return  none.
**/
void XSPI_ConfigDMARxLevel(XSPI_Module* xSPIx, uint32_t RxDataLevel)
{
    xSPIx->DMARDL_CTRL = RxDataLevel;
}

/**
*\*\name    XSPI_EnableDMA
*\*\fun     Enables or disables the XSPI's DMA interface.
*\*\param   XSPI_DMAReq (The input parameters must be the following values):
*\*\          - XSPI_DMAREQ_TX    XSPI DMA transmit request
*\*\          - XSPI_DMAREQ_RX    XSPI DMA receive request
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
*\*\note  Configured when xSPI_EN.XSPIEN disabled
**/
void XSPI_EnableDMA(XSPI_Module* xSPIx, uint32_t XSPI_DMAReq, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the DMA transfer for selected requests by setting the DMAT and/or
           DADDR bits in the USART CTRL3 register */
        xSPIx->DMA_CTRL |= XSPI_DMAReq;
    }
    else
    {
        /* Disable the DMA transfer for selected requests by clearing the DMAT and/or
           DADDR bits in the USART CTRL3 register */
        xSPIx->DMA_CTRL &= (uint32_t)~XSPI_DMAReq;
    }
}

/**
*\*\name    XSPI_GetBusyStatus.
*\*\fun     Get XSPI status,busy or not.
*\*\return  SET:XSPI busy;
*\*\        RESET:XSPI idle.
**/
FlagStatus XSPI_GetBusyStatus(XSPI_Module* xSPIx)
{
    FlagStatus bitstatus;

    if ((xSPIx->STS & XSPI_STS_BUSY) == XSPI_STS_BUSY)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
*\*\name    XSPI_GetTxDataBusyStatus.
*\*\fun     Check transmit fifo full or not.
*\*\return  SET: Transmit fifo full;
*\*\        RESET: Transmit fifo not full.
**/
FlagStatus XSPI_GetTxDataBusyStatus(XSPI_Module* xSPIx)
{
    FlagStatus bitstatus;

    if ((xSPIx->STS & XSPI_STS_TXFNF) == 0x00)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}


/**
*\*\name    XSPI_GetTxDataEmptyStatus.
*\*\fun     Check transmit fifo empty or not.
*\*\return  SET: Transmit fifo empty;
*\*\        RESET: Transmit fifo not empty.
**/
FlagStatus XSPI_GetTxDataEmptyStatus(XSPI_Module* xSPIx)
{
    FlagStatus bitstatus;

    if ((xSPIx->STS & XSPI_STS_TXFE) == XSPI_STS_TXFE)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
*\*\name    XSPI_GetRxHaveDataStatus.
*\*\fun     Check receive fifo have data or not.
*\*\return  SET:Receive fifo have data;
*\*\        RESET:Receive fifo empty.
**/
FlagStatus XSPI_GetRxHaveDataStatus(XSPI_Module* xSPIx)
{
    FlagStatus bitstatus;

    if ((xSPIx->STS & XSPI_STS_RXFNE) == XSPI_STS_RXFNE)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
*\*\name    XSPI_GetRxDataFullStatus.
*\*\fun     Check receive fifo full or not.
*\*\return  SET: Receive fifo full;
*\*\        RESET: Receive fifo not full.
**/
FlagStatus XSPI_GetRxDataFullStatus(XSPI_Module* xSPIx)
{
    FlagStatus bitstatus;

    if ((xSPIx->STS & XSPI_STS_RXFF) == XSPI_STS_RXFF)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}


/**
*\*\name    XSPI_GetDataConflictErrorStatus.
*\*\fun     Check data conflict error or not.
*\*\return  SET: Data conflict error;
*\*\        RESET: No data conflict error.
**/
FlagStatus XSPI_GetDataConflictErrorStatus(XSPI_Module* xSPIx)
{
    FlagStatus bitstatus;

    if ((xSPIx->STS & XSPI_STS_DCERR) == XSPI_STS_DCERR)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
*\*\name    ClrFifo.
*\*\fun     Read DAT0 register to clear fifo.
*\*\return  none.
**/
void XSPI_ClrFifo(XSPI_Module* xSPIx)
{
    uint32_t timeout = 0;

    while (XSPI_GetRxHaveDataStatus(xSPIx))
    {
        XSPI_ReceiveData(xSPIx);

        if(++timeout >= 200)
        {
            break;
        }
    }
}
/**
*\*\name    GetFifoData
*\*\fun     Get data from fifo.
*\*\param   pData pointer to buffer of getting fifo data.
*\*\param   Len length of getting fifo data.
*\*\return  XSPI_SUCCESS or XSPI_NULL.
**/
uint32_t XSPI_GetFifoData(XSPI_Module* xSPIx, uint32_t* pData, uint32_t Len)
{
    uint32_t cnt;

    for (cnt = 0; cnt < Len; cnt++)
    {
        if (XSPI_GetRxHaveDataStatus(xSPIx))
        {
            *pData++ = XSPI_ReceiveData(xSPIx);
        }
        else
        {
            return XSPI_NULL;
        }
    }

    return XSPI_SUCCESS;
}
/**
*\*\name    XSPISendAndGetWords.
*\*\fun     Send words out from source data buffer and get returned datas into destination data buffer.
*\*\param   pSrcData:
*\*\          - pSrcData pointer to buffer of sending datas.
*\*\param   pDstData:
*\*\          - pDstData pointer to buffer of getting returned datas.
*\*\param   cnt:
*\*\          - cnt number of sending datas.
*\*\return  none.
**/
void XSPI_SendAndGetWords(XSPI_Module* xSPIx, uint32_t* pSrcData, uint32_t* pDstData, uint32_t cnt)
{
    uint32_t num = 0;
    uint32_t timeout = 0;

    while (num < cnt)
    {
        XSPI_SendData(xSPIx, *(pSrcData++));
        num++;
    }

    while (!XSPI_GetRxHaveDataStatus(xSPIx))
    {
        if(++timeout >= XSPI_TIME_OUT_CNT)
        {
            break;
        }
    }

    timeout = 0;

    while (xSPIx->RXFN < cnt)
    {
        if(++timeout >= XSPI_TIME_OUT_CNT)
        {
            break;
        }
    }

    num = 0;

    while (num < cnt)
    {
        *(pDstData++) = XSPI_ReceiveData(xSPIx);
        num++;
    }
}

/**
*\*\name    XSPISendWordAndGetWords.
*\*\fun     Send one word data and get returned words into destination data buffer.
*\*\param   WrData:
*\*\          - WrData one word to be sent.
*\*\param   pRdData:
*\*\          - pRdData pointer to buffer of getting returned datas.
*\*\param   LastRd:
*\*\          - 1:go on to get returned datas.
*\*\          - 0:end to get returned datas.
*\*\return  none.
**/
uint32_t XSPI_SendWordAndGetWords(XSPI_Module* xSPIx, uint32_t WrData, uint32_t* pRdData, uint8_t LastRd)
{
    uint32_t    timeout1 = 0;

    XSPI_SendData(xSPIx, WrData);                   //trammit
    *pRdData = XSPI_ReceiveData(xSPIx);

    if(LastRd != 0)
    {
        while(!XSPI_GetRxHaveDataStatus(xSPIx))   //wait for data
        {
            if(++timeout1 >= XSPI_TIME_OUT_CNT)
            {
                return XSPI_NULL;           //time out
            }
        }

        *pRdData = XSPI_ReceiveData(xSPIx);          //read data
        return XSPI_SUCCESS;
    }

    return XSPI_NULL;
}

/**
*\*\name    xSPI_Wait_Flag.
*\*\fun     xspi Waiting for status register flag.
*\*\param   xSPIx:
*\*\          - xSPI2.
*\*\param   flag:
*\*\          - status register flag to be wait.
*\*\param   sta:
*\*\          - SET or RESET.
*\*\param   wtime:
*\*\          - timeout.
*\*\return  0:ture  1:false
**/
uint8_t xSPI_Wait_Flag(XSPI_Module* xSPIx, uint32_t flag, uint8_t sta, uint64_t wtime)
{
    uint8_t flagsta = 0;

    while(wtime)
    {
        flagsta = (xSPIx->STS & flag) ? 1 : 0;

        if(flagsta == sta)break;

        wtime--;
    }

    if(wtime)return 0;
    else return 1;
}

/**
*\*\name    xSPI_Wait_TransferComplete.
*\*\fun     xspi wait Transfer Complete.
*\*\param   xSPIx:
*\*\          - xSPI2.
*\*\param   wtime:
*\*\          - timeout.
*\*\return  0:ture  1:false
**/
uint8_t xSPI_Wait_TransferComplete(XSPI_Module* xSPIx, uint64_t wtime)
{
    uint8_t ret = 0;
    ret |= xSPI_Wait_Flag(xSPIx, XSPI_STS_TXFE, SET, wtime); //wait for Transmit FIFO is empty:(0x1 EMPTY)
    ret |= xSPI_Wait_Flag(xSPIx, XSPI_STS_BUSY, RESET, wtime); //wait for xSPI is idle or disabled:(0x0 idle)
    return ret;
}

/**
*\*\name    xSPI_TXFifoLevel.
*\*\fun     xspi set tx fifo level.
*\*\param   xSPIx:
*\*\          - xSPI2.
*\*\param   FifoLevel:
*\*\          - tx fifo level to be set.
*\*\return  0:none
**/
void xSPI_TXFifoLevel(XSPI_Module* xSPIx, u16 FifoLevel)
{
    u32 tmp = 0;

    xSPIx->SSIENR = DISABLE; //disable QSPI

    tmp = xSPIx->TXFT;
    //[20:16]	TXFTHR
    tmp &= ~(0x001f0000);
    tmp |= (FifoLevel << 16);
    xSPIx->TXFT = tmp;

    xSPIx->SSIENR = ENABLE;//enable QSPI
}

/**
*\*\name    xSPI_BaudRateSelect.
*\*\fun     xspi set BaudRate.
*\*\param   xSPIx:
*\*\          - xSPI2.
*\*\param   BAUDR_Value:
*\*\          - Baud Rate to be set.
*\*\return  0:none
**/
void xSPI_BaudRateSelect(XSPI_Module* xSPIx, uint32_t BAUDR_Value)
{
    xSPIx->SSIENR = DISABLE; //disable QSPI
    xSPIx->BAUD = BAUDR_Value;
    xSPIx->SSIENR = ENABLE;//enable QSPI
}

void xSPI_RXSampleDelay(XSPI_Module* xSPIx, uint32_t Sampling_Edge, uint32_t SampleDelay)
{
    xSPIx->SSIENR = DISABLE; //disable QSPI
    xSPIx->RX_DELAY = (Sampling_Edge | SampleDelay);
    xSPIx->SSIENR = ENABLE;//enable QSPI
}

/**
*\*\name    SetXspi_InstAddrWaitcycle_phase.
*\*\fun     Set the data length of xSPIx instruction, address stage, and null instruction in each stage.
*\*\param   xSPIx:
*\*\          - xSPI2.
*\*\param   inst_l:
*\*\          - instruction length.
*\*\param   addr_l:
*\*\          - address stage length.
*\*\param   wait_cycle:
*\*\          - wait cycle.
*\*\return  0:none
**/
void SetXspi_InstAddrWaitcycle_phase(XSPI_Module* xSPIx, u32 inst_l, u32 addr_l, u32 wait_cycle)
{
    xSPIx->SSIENR = DISABLE; //disable QSPI

    xSPIx->ENH_CTRL0 &= XSPI_INST_L_MASK;
    xSPIx->ENH_CTRL0 |= inst_l;

    xSPIx->ENH_CTRL0 &= XSPI_ADDRL_MASK;
    xSPIx->ENH_CTRL0 |= addr_l;

    xSPIx->ENH_CTRL0 &= XSPI_WAITCYCLES_MASK;
    xSPIx->ENH_CTRL0 |= wait_cycle;

    xSPIx->SSIENR = ENABLE;//enable QSPI
}

/**
*\*\name    SetXspi_TransType
*\*\fun     Set address and instruction transmission format
*\*\param   xSPIx:
*\*\          - xSPI2.
*\*\param   type:
*\*\          - address and instruction transmission format
*\*\return  0:none
**/
void SetXspi_TransType(XSPI_Module* xSPIx, u32 type)
{
    xSPIx->SSIENR = DISABLE; //disable QSPI

    xSPIx->ENH_CTRL0 &= XSPI_TRANSTYPE_MASK;
    xSPIx->ENH_CTRL0 |= type;
    xSPIx->SSIENR = ENABLE;//enable QSPI
}

/**
*\*\name    Set_xSPI_DDR
*\*\fun     Set DDR Enable:This will enable Dual-data rate transfers in Dual/Quad/Octal frame formats of SPI
*\*\        and Instruction DDR Enable bit.
*\*\param   xSPIx:
*\*\          - xSPI2.
*\*\param   set_type:
*\*\          - DDR enable type
*\*\return  0:none
**/
void Set_xSPI_DDR(XSPI_Module* xSPIx, u32 set_type)
{
    xSPIx->SSIENR = DISABLE; //disable QSPI

    //Send edge settings
    //The maximum value of this register is = (BAUDR/2) -1
    xSPIx->DDR_TXDE = ((xSPIx->BAUD / 2) / 2) > 255 ? 255 : ((xSPIx->BAUD / 2) / 2);

    switch(set_type)
    {
        case XSPI_INST_DDR_EN://Setting the inst ddd separately will not take effect. You must first set the SPI ddd and then set the inst ddd for it to take effect
        {
            xSPIx->ENH_CTRL0 |= (1 << 16); //spi ddr
            xSPIx->ENH_CTRL0 |= (1 << 17); //inst ddr
        }
        break;

        case XSPI_SPI_DDR_EN:
        {
            xSPIx->ENH_CTRL0 |= (1 << 16); //spi ddr
        }
        break;

        case XIP_READ_INST_DDR_EN:
        {
            xSPIx->XIP_CTRL |= (1 << 19); //spi ddr
            xSPIx->XIP_CTRL |= (1 << 20); //inst ddr
        }
        break;

        case XIP_READ_IDDR_EN:
        {
            xSPIx->XIP_CTRL |= (1 << 19); //spi ddr
        }
        break;

        case XIP_WRITE_INST_DDR_EN:
        {
            xSPIx->XIP_WRITE_CTRL |= (1 << 10); //spi ddr
            xSPIx->XIP_WRITE_CTRL |= (1 << 11); //inst ddr
        }
        break;

        case XIP_WRITE_IDDR_EN:
        {
            xSPIx->XIP_WRITE_CTRL |= (1 << 10); //spi ddr
        }
        break;

    }

    xSPIx->SSIENR = ENABLE;//enable QSPI
}

/**
*\*\name    xSPI_Clear_RXFIFO
*\*\fun     clear rx fifo data
*\*\param   xSPIx:
*\*\          - xSPI2.
*\*\return  0:none
**/
void xSPI_Clear_RXFIFO(XSPI_Module* xSPIx)
{
    //clear rx FIFO
    while(xSPIx->STS & XSPI_FLAG_RFNE)// RX FIFO Not Empty flag set
    {
        xSPIx->DAT0;
    }
}
