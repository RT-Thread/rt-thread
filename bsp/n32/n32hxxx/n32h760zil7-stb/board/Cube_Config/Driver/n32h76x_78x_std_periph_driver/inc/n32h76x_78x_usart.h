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
 * @file n32h76x_78x_usart.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#ifndef __N32H76X_78X_USART_H__
#define __N32H76X_78X_USART_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h76x_78x.h"

/** USART Init Structure definition **/

typedef struct
{
    uint32_t BaudRate;   /* This member configures the USART communication baud rate.
                                  The baud rate is computed using the following formula:
                                   - IntegerDivider = ((PCLKx) / (16 * (USART_InitStruct->BaudRate)))
                                   - FractionalDivider = ((IntegerDivider - ((u32) IntegerDivider)) * 16) + 0.5 */

    uint32_t WordLength; /* Specifies the number of data bits transmitted or received in a frame. */

    uint32_t StopBits;   /* Specifies the number of stop bits transmitted. */

    uint32_t Parity;     /* Specifies the parity mode. */

    uint32_t Mode;       /* Specifies wether the Receive or Transmit mode is enabled or disabled. */

    uint32_t HardwareFlowControl; /* Specifies wether the hardware flow control mode is enabled or disabled. */
    
    uint32_t OverSampling;        /* Specifies whether USART oversampling mode is 16 or 8. */
} USART_InitType;

/** USART Clock Init Structure definition **/

typedef struct
{
    uint32_t Clock; /* Specifies whether the USART clock is enabled or disabled. */

    uint32_t Polarity; /* Specifies the steady state value of the serial clock. */

    uint32_t Phase; /* Specifies the clock transition on which the bit capture is made. */

    uint32_t LastBit; /* Specifies whether the clock pulse corresponding to the last transmitted
                         data bit (MSB) has to be output on the SCLK pin in synchronous mode. */
} USART_ClockInitType;

/*** USART Structure Definition End ***/

/*** USART Macro Definition Start ***/

#define USART_REG_BIT_MASK        (uint32_t)0x00000000U

/* USART CTRL1 Mask */
#define USART_CTRL1_CLR_MASK           ((uint32_t)(~(USART_CTRL1_RXEN \
                                              |USART_CTRL1_TXEN \
                                              |USART_CTRL1_PSEL \
                                              |USART_CTRL1_PCEN \
                                              |USART_8OVER     \
                                              |USART_CTRL1_WL))) 

/** Configures the word length of USART **/
#define USART_WL_8B               ((uint32_t)USART_REG_BIT_MASK)  /* 8 bits */
#define USART_WL_9B               ((uint32_t)USART_CTRL1_WL)      /* 9 bits */

/** USART STOP bits **/
#define CTRL2_STPB_CLR_MASK      ((uint32_t)(~USART_CTRL2_STPB)) /* USART CTRL2 STOP Bits Mask */
#define USART_STPB_1              ((uint32_t)USART_REG_BIT_MASK)   /* 1 STOP bit */
#define USART_STPB_0_5            ((uint32_t)USART_CTRL2_STPB_0)   /* 0.5 STOP bit */
#define USART_STPB_2              ((uint32_t)USART_CTRL2_STPB_1)   /* 2 STOP bits */
#define USART_STPB_1_5            ((uint32_t)(USART_CTRL2_STPB_1|USART_CTRL2_STPB_0))   /* 1.5 STOP bits */

/** USART parity selection **/
#define USART_PE_NO               (USART_REG_BIT_MASK) /* USART parity disable */
#define USART_PE_EVEN             ((uint32_t)USART_CTRL1_PCEN)   /* Even parity */
#define USART_PE_ODD              ((uint32_t)(USART_CTRL1_PCEN | USART_CTRL1_PSEL))   /* Odd parity */

/** USART is configured as RX or TX **/
#define USART_MODE_RX             ((uint32_t)USART_CTRL1_RXEN)  /* Transmitter enable */
#define USART_MODE_TX             ((uint32_t)USART_CTRL1_TXEN)  /* Receiver enable */

/** USART Hardware Flow Control **/
#define CTRL3_CLR_MASK           ((uint32_t)(~USART_HFCTRL_RTS_CTS)) /* USART CTRL3 Mask */
#define USART_HFCTRL_NONE        ((uint32_t)USART_REG_BIT_MASK)
#define USART_HFCTRL_RTS         ((uint32_t)USART_CTRL3_RTSEN)
#define USART_HFCTRL_CTS         ((uint32_t)USART_CTRL3_CTSEN)
#define USART_HFCTRL_RTS_CTS     ((uint32_t)(USART_CTRL3_RTSEN | USART_CTRL3_CTSEN))

/** USART oversampling configure **/
#define USART_8OVER              ((uint32_t)USART_CTRL1_OSPM)
#define USART_16OVER             ((uint32_t)USART_REG_BIT_MASK)

/* USART CTRL2 Clock Mask */
#define CTRL2_CLOCK_CLR_MASK ((uint32_t)(~(USART_CLK_ENABLE      \
                                           | USART_CTRL2_CLKPOL  \
                                           | USART_CTRL2_CLKPHA  \
                                           | USART_CTRL2_LBCLK))) 
/** Clock **/
#define USART_CLK_DISABLE         ((uint32_t)USART_REG_BIT_MASK)
#define USART_CLK_ENABLE          ((uint32_t)USART_CTRL2_CLKEN)

/** USART_Clock_Polarity **/
#define USART_CLKPOL_LOW          ((uint32_t)USART_REG_BIT_MASK)
#define USART_CLKPOL_HIGH         ((uint32_t)USART_CTRL2_CLKPOL)

/** USART_Clock_Phase **/
#define USART_CLKPHA_1EDGE        ((uint32_t)USART_REG_BIT_MASK)
#define USART_CLKPHA_2EDGE        ((uint32_t)USART_CTRL2_CLKPHA)

/** USART_Last_Bit **/
#define USART_CLKLB_DISABLE       ((uint32_t)USART_REG_BIT_MASK)
#define USART_CLKLB_ENABLE        ((uint32_t)USART_CTRL2_LBCLK)


#define CTRL1_UEN_SET             ((uint32_t)USART_CTRL1_UEN)    /* USART Enable Mask */
#define CTRL1_UEN_RESET           ((uint32_t)(~USART_CTRL1_UEN)) /* USART Disable Mask */

#define CTRL1_IFCEN_ENABLE        ((uint32_t)USART_CTRL1_IFCEN)  /* USART Idle frame Enable */
#define CTRL1_IFCEN_DISABLE       ((uint32_t)(~USART_CTRL1_IFCEN)) /* USART Idle frame Disable */

#define CTRL1_SWAP_ENABLE        ((uint32_t)USART_CTRL1_SWAP)    /* USART Idle frame Enable */
#define CTRL1_SWAP_DISABLE       ((uint32_t)(~USART_CTRL1_SWAP)) /* USART Idle frame Disable */

#define CTRL1_DEP_ENABLE         ((uint32_t)USART_CTRL1_DEP)    /* USART DE signal active high  */
#define CTRL1_DEP_DISABLE        ((uint32_t)(~USART_CTRL1_DEP)) /* USART DE signal active low */

/* USART Driver enable mode  */
#define CTRL1_DEM_ENABLE         ((uint32_t)USART_CTRL1_DEM)  
#define CTRL1_DEM_DISABLE        ((uint32_t)(~USART_CTRL1_DEM))

/* USART FEF Data Discard Enable  */
#define CTRL2_FEFLOSE_ENABLE         ((uint32_t)USART_CTRL2_FEFLOSE)  
#define CTRL2_FEFLOSE_DISABLE        ((uint32_t)(~USART_CTRL2_FEFLOSE))

/* USART NEF Data Discard Enable  */
#define CTRL2_NEFLOSE_ENABLE         ((uint32_t)USART_CTRL2_NEFLOSE)  
#define CTRL2_NEFLOSE_DISABLE        ((uint32_t)(~USART_CTRL2_NEFLOSE))

/* USART PEF Data Discard Enable  */
#define CTRL2_PEFLOSE_ENABLE         ((uint32_t)USART_CTRL2_PEFLOSE)  
#define CTRL2_PEFLOSE_DISABLE        ((uint32_t)(~USART_CTRL2_PEFLOSE))

/* Receiver timeout enable  */
#define CTRL2_RTO_ENABLE         ((uint32_t)USART_CTRL2_RTOEN)  
#define CTRL2_RTO_DISABLE        ((uint32_t)(~USART_CTRL2_RTOEN))


/** USART_Interrupt_definition **/
#define USART_INT_MASK              ((uint32_t)0x0FFFFFFFU) /* USART Interrupt Mask */
#define USART_CTRL1_INTMASK         ((uint32_t)0x10000000U)
#define USART_CTRL2_INTMASK         ((uint32_t)0x20000000U)
#define USART_CTRL3_INTMASK         ((uint32_t)0x40000000U)
#define USART_FIFO_INTMASK          ((uint32_t)0x80000000U)

#define USART_INT_PEF               ((uint32_t)(USART_CTRL1_INTMASK | USART_CTRL1_PEIEN))
#define USART_INT_TXC               ((uint32_t)(USART_CTRL1_INTMASK | USART_CTRL1_TXCIEN))
#define USART_INT_TXDE              ((uint32_t)(USART_CTRL1_INTMASK | USART_CTRL1_TXDEIEN))
#define USART_INT_RXDNE             ((uint32_t)(USART_CTRL1_INTMASK | USART_CTRL1_RXDNEIEN))
#define USART_INT_IDLEF             ((uint32_t)(USART_CTRL1_INTMASK | USART_CTRL1_IDLEIEN))
#define USART_INT_RTOE              ((uint32_t)(USART_CTRL2_INTMASK | USART_CTRL2_RTOIEN))
#define USART_INT_LINBD             ((uint32_t)(USART_CTRL2_INTMASK | USART_CTRL2_LINBDIEN))
#define USART_INT_ERRF              ((uint32_t)(USART_CTRL3_INTMASK | USART_CTRL3_ERRIEN))
#define USART_INT_CTSF              ((uint32_t)(USART_CTRL3_INTMASK | USART_CTRL3_CTSIEN))

#define USART_INT_TXFTE             ((uint32_t)(USART_FIFO_INTMASK | USART_FIFO_TXFTIEN))
#define USART_INT_RXFTE             ((uint32_t)(USART_FIFO_INTMASK | USART_FIFO_RXFTIEN))
#define USART_INT_RXFEE             ((uint32_t)(USART_FIFO_INTMASK | USART_FIFO_RXFEIEN))
#define USART_INT_TXFEE             ((uint32_t)(USART_FIFO_INTMASK | USART_FIFO_TXFEIEN))
#define USART_INT_RXFFE             ((uint32_t)(USART_FIFO_INTMASK | USART_FIFO_RXFFIEN))
#define USART_INT_TXFFE             ((uint32_t)(USART_FIFO_INTMASK | USART_FIFO_TXFFIEN))


#define CTRL2_ADDR_MASK             ((uint32_t)(~USART_CTRL2_ADDR)) 

/** USART_DMA_Requests **/
#define USART_DMAREQ_TX             ((uint32_t)USART_CTRL3_DMATXEN)
#define USART_DMAREQ_RX             ((uint32_t)USART_CTRL3_DMARXEN)

/** USART_WakeUp_methods **/
#define CTRL1_WUM_MASK              ((uint32_t)(~USART_CTRL1_WUM)) 
#define USART_WUM_IDLELINE          ((uint32_t)USART_REG_BIT_MASK)
#define USART_WUM_ADDRMASK          ((uint32_t)USART_CTRL1_WUM)

/* USART mute mode */
#define CTRL1_RCVWU_SET             ((uint32_t)USART_CTRL1_RCVWU) 
#define CTRL1_RCVWU_RESET           ((uint32_t)(~USART_CTRL1_RCVWU))

/** USART_LIN_Break_Detection_Length **/
#define CTRL2_LINBDL_MASK           ((uint32_t)(~USART_CTRL2_LINBDL)) 
#define USART_LINBDL_10B            ((uint32_t)USART_REG_BIT_MASK)
#define USART_LINBDL_11B            ((uint32_t)USART_CTRL2_LINBDL)

/* USART LIN */
#define CTRL2_LINMEN_SET            ((uint32_t)USART_CTRL2_LINMEN) 
#define CTRL2_LINMEN_RESET          ((uint32_t)(~USART_CTRL2_LINMEN))

/* USART Break Character send Mask */
#define CTRL1_SDBRK_SET             ((uint32_t)USART_CTRL1_SDBRK) 

/* Guard Time Register */
#define GTP_LSB_MASK                ((uint32_t)(~USART_GTP_GTV)) 
#define GTP_MSB_MASK                ((uint32_t)(~USART_GTP_PSCV)) 

/* USART SCMEN Mask */
#define CTRL3_SCMEN_SET             ((uint32_t)USART_CTRL3_SCMEN) 
#define CTRL3_SCMEN_RESET           ((uint32_t)(~USART_CTRL3_SCMEN)) 

/* USART SC NACK Mask */
#define CTRL3_SCNACK_SET            ((uint32_t)USART_CTRL3_SCNACK) 
#define CTRL3_SCNACK_RESET          ((uint32_t)(~USART_CTRL3_SCNACK))

/* USART Half-Duplex Mask */
#define CTRL3_HDMEN_SET             ((uint32_t)USART_CTRL3_HDMEN) 
#define CTRL3_HDMEN_RESET           ((uint32_t)(~USART_CTRL3_HDMEN))

/** USART_IrDA_Low_Power **/
#define CTRL3_IRDALP_MASK           ((uint32_t)(~USART_CTRL3_IRDALP)) 
#define USART_IRDAMODE_LOWPPWER     ((uint32_t)USART_CTRL3_IRDALP)
#define USART_IRDAMODE_NORMAL       ((uint32_t)USART_REG_BIT_MASK)

 /* USART IrDA Mask */
#define CTRL3_IRDAMEN_SET           ((uint32_t)USART_CTRL3_IRDAMEN)
#define CTRL3_IRDAMEN_RESET         ((uint32_t)(~USART_CTRL3_IRDAMEN)) 

/** USART_Flags **/
#define USART_FLAG_LOSEMASK         ((uint32_t)USART_STS_FELOSEF | USART_STS_NELOSEF | USART_STS_PELOSEF)
#define USART_FLAG_FELOSE           ((uint32_t)USART_STS_FELOSEF)
#define USART_FLAG_NELOSE           ((uint32_t)USART_STS_NELOSEF)
#define USART_FLAG_PELOSE           ((uint32_t)USART_STS_PELOSEF)
#define USART_FLAG_RTO              ((uint32_t)USART_STS_RTOF)
#define USART_FLAG_FEF              ((uint32_t)USART_STS_FEF)
#define USART_FLAG_NEF              ((uint32_t)USART_STS_NEF)
#define USART_FLAG_OREF             ((uint32_t)USART_STS_OREF)
#define USART_FLAG_PEF              ((uint32_t)USART_STS_PEF)
#define USART_FLAG_LINBD            ((uint32_t)USART_STS_LINBDF)
#define USART_FLAG_CTSF             ((uint32_t)USART_STS_CTSF)
#define USART_FLAG_RXDNE            ((uint32_t)USART_STS_RXDNE)
#define USART_FLAG_TXC              ((uint32_t)USART_STS_TXC)
#define USART_FLAG_TXDE             ((uint32_t)USART_STS_TXDE)
#define USART_FLAG_IDLEF            ((uint32_t)USART_STS_IDLEF)
#define USART_FLAG_TXFT             ((uint32_t)USART_STS_TXFT)
#define USART_FLAG_RXFT             ((uint32_t)USART_STS_RXFT)
#define USART_FLAG_RXFE             ((uint32_t)USART_STS_RXFE)
#define USART_FLAG_TXFE             ((uint32_t)USART_STS_TXFE)
#define USART_FLAG_RXFF             ((uint32_t)USART_STS_RXFF)
#define USART_FLAG_TXFF             ((uint32_t)USART_STS_TXFF)

/* FIFO depth*/
#define USART_FIFO_DEEP1             ((uint32_t)0x00000000U)
#define USART_FIFO_DEEP2             ((uint32_t)0x00000001U)
#define USART_FIFO_DEEP4             ((uint32_t)0x00000002U)
#define USART_FIFO_DEEP6             ((uint32_t)0x00000003U)
#define USART_FIFO_DEEP7             ((uint32_t)0x00000004U)
#define USART_FIFO_DEEP8             ((uint32_t)0x00000005U)

#define USART_CLEAR_FIFO             ((uint32_t)USART_FIFO_CLR)

/* Receiver timeout enable  */
#define USART_FIFO_ENABLE         ((uint32_t)USART_FIFO_EN)  
#define USART_FIFO_DISABLE        ((uint32_t)(~USART_FIFO_EN))


void USART_DeInit(USART_Module* USARTx);
void USART_Init(USART_Module* USARTx, USART_InitType* USART_InitStruct);
void USART_StructInit(USART_InitType* USART_InitStruct);
void USART_ClockInit(USART_Module* USARTx, USART_ClockInitType* USART_ClockInitStruct);
void USART_ClockStructInit(USART_ClockInitType* USART_ClockInitStruct);
void USART_Enable(USART_Module* USARTx, FunctionalState Cmd);
void USART_ConfigInt(USART_Module* USARTx, uint32_t USART_INT, FunctionalState Cmd);
void USART_EnableDMA(USART_Module* USARTx, uint32_t USART_DMAReq, FunctionalState Cmd);
void USART_SetAddr(USART_Module* USARTx, uint8_t USART_Addr);
void USART_ConfigWakeUpMode(USART_Module* USARTx, uint32_t USART_WakeUpMode);
void USART_EnableRcvWakeUp(USART_Module* USARTx, FunctionalState Cmd);
void USART_ConfigLINBreakDetectLength(USART_Module* USARTx, uint32_t USART_LINBreakDetectLength);
void USART_EnableLIN(USART_Module* USARTx, FunctionalState Cmd);
void USART_SendData(USART_Module* USARTx, uint32_t Data);
uint32_t USART_ReceiveData(USART_Module* USARTx);
void USART_SendBreak(USART_Module* USARTx);
void USART_SetGuardTime(USART_Module* USARTx, uint8_t USART_GuardTime);
void USART_SetPrescaler(USART_Module* USARTx, uint8_t USART_Prescaler);
void USART_EnableSmartCard(USART_Module* USARTx, FunctionalState Cmd);
void USART_SetSmartCardNACK(USART_Module* USARTx, FunctionalState Cmd);
void USART_EnableHalfDuplex(USART_Module* USARTx, FunctionalState Cmd);
void USART_ConfigIrDAMode(USART_Module* USARTx, uint32_t USART_IrDAMode);
void USART_EnableIrDA(USART_Module* USARTx, FunctionalState Cmd);
FlagStatus USART_GetFlagStatus(USART_Module* USARTx, uint32_t USART_FLAG);
void USART_ClrFlag(USART_Module* USARTx, uint32_t USART_FLAG);
void USART_ClrRTOFlag(USART_Module* USARTx);
INTStatus USART_GetIntStatus(USART_Module* USARTx, uint32_t USART_INT);
void USART_IdleFrameSet(USART_Module* USARTx,FunctionalState Cmd);
void USART_PinSwapSet(USART_Module* USARTx,FunctionalState Cmd);
void USART_CfgDriverAssertTime(USART_Module* USARTx,uint32_t Time);
void USART_CfgDriverdeassertTime(USART_Module* USARTx,uint32_t Time);
void USART_DriverPolaritySet(USART_Module* USARTx,FunctionalState Cmd);
void USART_DriverModeSet(USART_Module* USARTx,FunctionalState Cmd);
void USART_FEFDiscardSet(USART_Module* USARTx,FunctionalState Cmd);
void USART_NEFDiscardSet(USART_Module* USARTx,FunctionalState Cmd);
void USART_PEFDiscardSet(USART_Module* USARTx,FunctionalState Cmd);
void USART_RTOSet(USART_Module* USARTx,FunctionalState Cmd);
uint32_t USART_GetTxFIFO_Num(USART_Module* USARTx);
uint32_t USART_GetRxFIFO_Num(USART_Module* USARTx);
void USART_CfgRxFIFOThreshold(USART_Module* USARTx,uint32_t threshold);
void USART_CfgTxFIFOThreshold(USART_Module* USARTx,uint32_t threshold);
void USART_ClrFIFO(USART_Module* USARTx);
void USART_FIFOModeSet(USART_Module* USARTx,FunctionalState Cmd);
void USART_IdleFrameWidthSet(USART_Module* USARTx,uint32_t Width);
void USART_CfgRTOWidth(USART_Module* USARTx,uint32_t Width);


#ifdef __cplusplus
}
#endif

#endif /* __N32H76X_USART_H__ */

