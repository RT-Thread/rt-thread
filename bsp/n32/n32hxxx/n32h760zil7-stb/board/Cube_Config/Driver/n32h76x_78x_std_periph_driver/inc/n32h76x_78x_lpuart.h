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
 * @file n32h76x_78x_lpuart.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32H76X_LPUART_H__
#define __N32H76X_LPUART_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h76x_78x.h"


/** @addtogroup LPUART
 * @{
 */

/** @addtogroup LPUART_Exported_Types
 * @{
 */

/**
 * @brief  LPUART Init Structure definition
 */

typedef struct
{
    uint32_t BaudRate; /*!< This member configures the LPUART communication baud rate.
                                  The baud rate is computed using the following formula:
                                   - IntegerDivider = ((CLK) / (LPUART_InitStruct->BaudRate)))
                                   - FractionalDivider */

    uint32_t Parity; /*!< Specifies the parity mode.
                                This parameter can be a value of @ref Parity
                                @note When parity is enabled, the computed parity is inserted
                                      at the MSB position of the transmitted data (only support
                                      8 data bits). */ 

    uint32_t Mode; /*!< Specifies wether the Receive or Transmit mode is enabled or disabled.
                              This parameter can be a value of @ref Mode */

    uint32_t RtsThreshold; /* Specifies RTS Threshold.
                                    This parameter can be a value of @ref RtsThreshold */                          

    uint32_t HardwareFlowControl; /*!< Specifies wether the hardware flow control mode is enabled
                                             or disabled.
                                             This parameter can be a value of @ref LPUART_Hardware_Flow_Control */
} LPUART_InitType;

#define LPUART_REG_BIT_MASK        (uint32_t)0x00000000U

#define CTRL_CLR_MASK            ((uint32_t)(~(LPUART_CTRL_RXEN \
                                              |LPUART_CTRL_TXEN \
                                              |LPUART_CTRL_PC \
                                              |LPUART_CTRL_PEN \
											  |LPUART_CTRL_RTST_0 \
											  |LPUART_CTRL_RTST_1\
											  |LPUART_CTRL_CTSEN \
											  |LPUART_CTRL_RTSEN)))  /*!< LPUART CTRL Mask */
											  
											 


/** LPUART parity selection **/

#define LPUART_PE_NO             ((uint32_t)LPUART_CTRL_PC)  /* LPUART parity disable */
#define LPUART_PE_EVEN           ((uint32_t)LPUART_REG_BIT_MASK)/* Even parity */
#define LPUART_PE_ODD            ((uint32_t)LPUART_CTRL_PEN)  /* Odd parity */
#define IS_LPUART_PARITY(PARITY) (((PARITY) == LPUART_PE_NO) || ((PARITY) == LPUART_PE_EVEN) || ((PARITY) == LPUART_PE_ODD))


/** LPUART is configured as RX or TX **/
#define LPUART_MODE_RX       ((uint32_t)LPUART_CTRL_RXEN) /* Transmitter enable */
#define LPUART_MODE_TX       ((uint32_t)LPUART_CTRL_TXEN) /* Receiver enable */
#define IS_LPUART_MODE(MODE) (((MODE) == LPUART_MODE_RX) || ((MODE) == LPUART_MODE_TX))


/** LPUART  RtsThreshold **/
#define LPUART_RTSTH_FIFOHF       ((uint32_t)LPUART_REG_BIT_MASK)
#define LPUART_RTSTH_FIFO3QF      ((uint32_t)LPUART_CTRL_RTST_0)
#define LPUART_RTSTH_FIFOFU       ((uint32_t)LPUART_CTRL_RTST_1)
#define IS_LPUART_RTSTHRESHOLD(RTSTHRESHOLD)                                                                                \
    (((RTSTHRESHOLD) == LPUART_RTSTH_FIFOHF) || ((RTSTHRESHOLD) == LPUART_RTSTH_FIFO3QF) || ((RTSTHRESHOLD) == LPUART_RTSTH_FIFOFU))

 
 /** LPUART Hardware Flow Control **/
#define CTRL_HFCTRL_MASK           ((uint32_t)(~LPUART_HFCTRL_RTS_CTS)) /* LPUART HFCTRL Bit Mask */
#define LPUART_HFCTRL_NONE         ((uint32_t)LPUART_REG_BIT_MASK)
#define LPUART_HFCTRL_CTS          ((uint32_t)LPUART_CTRL_CTSEN)
#define LPUART_HFCTRL_RTS          ((uint32_t)LPUART_CTRL_RTSEN)
#define LPUART_HFCTRL_RTS_CTS      ((uint32_t)(LPUART_CTRL_CTSEN | LPUART_CTRL_RTSEN))
#define IS_LPUART_HARDWARE_FLOW_CONTROL(CONTROL)                                                                        \
    (((CONTROL) == LPUART_HFCTRL_NONE) || ((CONTROL) == LPUART_HFCTRL_RTS) || ((CONTROL) == LPUART_HFCTRL_CTS)          \
     || ((CONTROL) == LPUART_HFCTRL_RTS_CTS))

/** LPUART_Interrupt_definition **/
#define LPUART_INT_MASK           ((uint32_t)0x00007FFFU) /* LPUART Interrupt Mask */
#define LPUART_INT_PE            ((uint32_t)LPUART_INTEN_PCEIEN)
#define LPUART_INT_TXC            ((uint32_t)LPUART_INTEN_TXCIEN)
#define LPUART_INT_RXFIFO_OV      ((uint32_t)LPUART_INTEN_RXFOIEN)
#define LPUART_INT_RXFIFO_FU      ((uint32_t)LPUART_INTEN_RXFFIEN)
#define LPUART_INT_RXFIFO_HF      ((uint32_t)LPUART_INTEN_RXFHFIEN)
#define LPUART_INT_RXFIFO_NE      ((uint32_t)LPUART_INTEN_RXFNEIEN)
#define LPUART_INT_WUF            ((uint32_t)LPUART_INTEN_WUIEN)
#define LPUART_INT_TXFIFO_OV      ((uint32_t)LPUART_INTEN_TXFOIEN)
#define LPUART_INT_TXFIFO_FU      ((uint32_t)LPUART_INTEN_TXFFIEN)
#define LPUART_INT_TXFIFO_QF      ((uint32_t)LPUART_INTEN_TXFQFIEN)
#define LPUART_INT_TXFIFO_HF      ((uint32_t)LPUART_INTEN_TXFHFIEN)
#define LPUART_INT_TXFIFO_NE      ((uint32_t)LPUART_INTEN_TXFNEIEN)

#define LPUART_INT_IDLEF          ((uint32_t)LPUART_INTEN_IDLEFIEN)
#define LPUART_INT_FE             ((uint32_t)LPUART_INTEN_FEIEN)
#define LPUART_INT_TXFIFO_EM      ((uint32_t)LPUART_INTEN_TXFEIEN)


#define IS_LPUART_CFG_INT(IT)                                                                                           \
    (((IT) == LPUART_INT_PE) || ((IT) == LPUART_INT_TXC) || ((IT) == LPUART_INT_RXFIFO_OV) || ((IT) == LPUART_INT_RXFIFO_FU)       \
     || ((IT) == LPUART_INT_RXFIFO_HF) || ((IT) == LPUART_INT_RXFIFO_NE) || ((IT) == LPUART_INT_WUF)||((IT) == LPUART_INT_TXFIFO_OV)    \
	 || ((IT) == LPUART_INT_TXFIFO_FU) || ((IT) == LPUART_INT_TXFIFO_QF) || ((IT) == LPUART_INT_TXFIFO_HF)||((IT) == LPUART_INT_TXFIFO_NE)  \
	 || ((IT) == LPUART_INT_IDLEF) || ((IT) == LPUART_INT_FE) || ((IT) == LPUART_INT_TXFIFO_EM))
	 
#define IS_LPUART_GET_INT(IT)                                                                                           \
    (((IT) == LPUART_INT_PE) || ((IT) == LPUART_INT_TXC) || ((IT) == LPUART_INT_RXFIFO_OV) || ((IT) == LPUART_INT_RXFIFO_FU)       \
     || ((IT) == LPUART_INT_RXFIFO_HF) || ((IT) == LPUART_INT_RXFIFO_NE) || ((IT) == LPUART_INT_WUF)||((IT) == LPUART_INT_TXFIFO_OV)    \
	 || ((IT) == LPUART_INT_TXFIFO_FU) || ((IT) == LPUART_INT_TXFIFO_QF) || ((IT) == LPUART_INT_TXFIFO_HF)||((IT) == LPUART_INT_TXFIFO_NE)  \
	 || ((IT) == LPUART_INT_IDLEF) || ((IT) == LPUART_INT_FE) || ((IT) == LPUART_INT_TXFIFO_EM))
#define IS_LPUART_CLR_INT(IT)                                                                                           \
    (((IT) == LPUART_INT_PE) || ((IT) == LPUART_INT_TXC) || ((IT) == LPUART_INT_RXFIFO_OV) || ((IT) == LPUART_INT_RXFIFO_FU)       \
     || ((IT) == LPUART_INT_RXFIFO_HF) || ((IT) == LPUART_INT_RXFIFO_NE) || ((IT) == LPUART_INT_WUF)||((IT) == LPUART_INT_TXFIFO_OV)    \
	 || ((IT) == LPUART_INT_TXFIFO_FU) || ((IT) == LPUART_INT_TXFIFO_QF) || ((IT) == LPUART_INT_TXFIFO_HF)||((IT) == LPUART_INT_TXFIFO_NE)  \
	 || ((IT) == LPUART_INT_IDLEF) || ((IT) == LPUART_INT_FE) || ((IT) == LPUART_INT_TXFIFO_EM))

/** LPUART_DMA_Requests **/
#define LPUART_DMAREQ_TX         ((uint32_t)LPUART_CTRL_DMATXEN)
#define LPUART_DMAREQ_RX         ((uint32_t)LPUART_CTRL_DMARXEN)

#define IS_LPUART_DMAREQ(DMAREQ) ((((DMAREQ) & (uint32_t)0xFFFFFF9F) == (uint32_t)0x00) && ((DMAREQ) != (uint32_t)0x00))


/** LPUART_WakeUp_methods **/
#define LPUART_WUSTP_ON          ((uint32_t)LPUART_CTRL_WUSTPEN)
#define LPUART_WUSTP_STARTBIT    ((uint32_t)(LPUART_CTRL_WUS_0|LPUART_CTRL_WUS_1|LPUART_CTRL_WUS_3))
#define LPUART_WUSTP_RXNE        ((uint32_t)LPUART_CTRL_WUS_0)
#define LPUART_WUSTP_BYTE        ((uint32_t)LPUART_CTRL_WUS_1)
#define LPUART_WUSTP_FRAME_2     ((uint32_t)(LPUART_CTRL_WUS_1|LPUART_CTRL_WUS_0))
#define LPUART_WUSTP_FRAME_3     ((uint32_t)(LPUART_CTRL_WUS_2)
#define LPUART_WUSTP_FRAME_4     ((uint32_t)(LPUART_CTRL_WUS_2|LPUART_CTRL_WUS_0))
#define LPUART_WUSTP_FRAME_5     ((uint32_t)(LPUART_CTRL_WUS_2|LPUART_CTRL_WUS_1))
#define LPUART_WUSTP_FRAME_6     ((uint32_t)(LPUART_CTRL_WUS_2|LPUART_CTRL_WUS_1|LPUART_CTRL_WUS_0))
#define LPUART_WUSTP_FRAME_7     ((uint32_t)LPUART_CTRL_WUS_3)
#define LPUART_WUSTP_FRAME_8     ((uint32_t)(LPUART_CTRL_WUS_3|LPUART_CTRL_WUS_0))
#define LPUART_WUSTP_FRAME_MANY  ((uint32_t)(LPUART_CTRL_WUS_3|LPUART_CTRL_WUS_1))
#define CTRL_WUSTP_MASK          ((uint32_t)(~(LPUART_CTRL_WUS_0|LPUART_CTRL_WUS_1|LPUART_CTRL_WUS_2|LPUART_CTRL_WUS_3))) /*!< LPUART WakeUp Method Mask */

#define IS_LPUART_WAKEUP(WAKEUP)  \
    (((WAKEUP) == LPUART_WUSTP_STARTBIT) || ((WAKEUP) == LPUART_WUSTP_RXNE) || ((WAKEUP) == LPUART_WUSTP_BYTE) || ((WAKEUP) == LPUART_WUSTP_FRAME_2) \
     ((WAKEUP) == LPUART_WUSTP_FRAME_3) || ((WAKEUP) == LPUART_WUSTP_FRAME_4) || ((WAKEUP) == LPUART_WUSTP_FRAME_5) || ((WAKEUP) == LPUART_WUSTP_FRAME_6) \
	 ((WAKEUP) == LPUART_WUSTP_FRAME_7) || ((WAKEUP) == LPUART_WUSTP_FRAME_8) || ((WAKEUP) == LPUART_WUSTP_FRAME_MANY))

/** LPUART_Sampling_methods **/
#define LPUART_SMPCNT_3B    ((uint32_t)LPUART_REG_BIT_MASK)
#define LPUART_SMPCNT_1B    ((uint32_t)LPUART_CTRL_SSM)
#define CTRL_SMPCNT_MASK 	((uint32_t)(~LPUART_CTRL_SSM))  /*!< LPUART Sampling Method Mask */

/** LPUART_Flush_TXFIFO **/
#define LPUART_FLUSHTXF_ENABLE    ((uint32_t)LPUART_CTRL_FTXF)
#define LPUART_FLUSHTXF_DISABLE   ((uint32_t)(~LPUART_CTRL_FTXF))


/** LPUART_Flush_RXFIFO **/
#define LPUART_FLUSHRXF_ENABLE    ((uint32_t)LPUART_CTRL_FRXF)
#define LPUART_FLUSHRXF_DISABLE   ((uint32_t)(~LPUART_CTRL_FRXF))


/** LPUART_IDLEFRAME_DETECT **/
#define LPUART_IDLEF_ENABLE        ((uint32_t)LPUART_CTRL_IDLEFEN)  /* LPUART Idle frame Enable */
#define LPUART_IDLEF_DISABLE       ((uint32_t)(~LPUART_CTRL_IDLEFEN)) /* LPUART Idle frame Disable */

/** LPUART_LoopBack_Self-Test **/
#define LPUART_LOOPBACK_ENABLE    ((uint32_t)LPUART_CTRL_LB)
#define LPUART_LOOPBACK_DISABLE   ((uint32_t)(~LPUART_CTRL_LB))


/** LPUART_Flags **/

#define LPUART_FLAG_PE           ((uint32_t)LPUART_INTEN_PCEIEN)
#define LPUART_FLAG_TXC          ((uint32_t)LPUART_STS_TXCF)
#define LPUART_FLAG_RXFIFO_OV    ((uint32_t)LPUART_STS_RXFOF)
#define LPUART_FLAG_RXFIFO_FU      ((uint32_t)LPUART_STS_RXFFF)
#define LPUART_FLAG_RXFIFO_HF      ((uint32_t)LPUART_STS_RXFHFF)
#define LPUART_FLAG_RXFIFO_NE      ((uint32_t)LPUART_STS_RXFNEF)
#define LPUART_FLAG_CTS          ((uint32_t)LPUART_STS_CTSF)
#define LPUART_FLAG_WUF          ((uint32_t)LPUART_STS_WUF)
#define LPUART_FLAG_NEF           ((uint32_t)LPUART_STS_NEF)
#define LPUART_FLAG_TXFIFO_OV    ((uint32_t)LPUART_STS_TXFOF)
#define LPUART_FLAG_TXFIFO_FU      ((uint32_t)LPUART_STS_TXFFF)
#define LPUART_FLAG_TXFIFO_QF       ((uint32_t)LPUART_STS_TXFQFF)
#define LPUART_FLAG_TXFIFO_HF      ((uint32_t)LPUART_STS_TXFHFF)
#define LPUART_FLAG_TXFIFO_NE      ((uint32_t)LPUART_STS_TXFNEF)
#define LPUART_FLAG_IDLEF          ((uint32_t)LPUART_STS_IDLEF)
#define LPUART_FLAG_FRAME_ER      ((uint32_t)LPUART_STS_FE)
#define LPUART_FLAG_TXFIFO_EM       ((uint32_t)LPUART_STS_TXFEF)


#define IS_LPUART_FLAG(FLAG)                                                                                            \
    (((FLAG) == LPUART_FLAG_PE) || ((FLAG) == LPUART_FLAG_TXC) || ((FLAG) == LPUART_FLAG_RXFIFO_OV)                           \
     || ((FLAG) == LPUART_FLAG_RXFIFO_FU) || ((FLAG) == LPUART_FLAG_RXFIFO_HF) || ((FLAG) == LPUART_FLAG_RXFIFO_NE)                   \
     || ((FLAG) == LPUART_FLAG_CTS) || ((FLAG) == LPUART_FLAG_WUF) || ((FLAG) == LPUART_FLAG_NEF)     \
     || ((FLAG) == LPUART_FLAG_TXFIFO_OV) || ((FLAG) == LPUART_FLAG_TXFIFO_FU) || ((FLAG) == LPUART_FLAG_TXFIFO_QF) \
	 || ((FLAG) == LPUART_FLAG_TXFIFO_HF) || ((FLAG) == LPUART_FLAG_TXFIFO_NE) || ((FLAG) == LPUART_FLAG_IDLEF)  \
	 || ((FLAG) == LPUART_FLAG_FRAME_ER) || ((FLAG) == LPUART_FLAG_TXFIFO_EM) )

//#define IS_LPUART_CLEAR_FLAG(FLAG) ((((FLAG) & (uint16_t)0xFE40) == 0x00) && ((FLAG) != (uint16_t)0x00))

#define IS_LPUART_BAUDRATE(BAUDRATE) (((BAUDRATE) > 0) && ((BAUDRATE) < 0x010000))

#define IS_LPUART_DATA(DATA)         ((DATA) <= 0xFF)




/**
 * @}
 */

/** @addtogroup LPUART_Exported_Macros
 * @{
 */

/**
 * @}
 */

/** @addtogroup LPUART_Exported_Functions
 * @{
 */





void LPUART_DeInit(LPUART_Module* LPUARTx);
void LPUART_Init(LPUART_Module* LPUARTx, LPUART_InitType* LPUART_InitStruct);
void LPUART_StructInit(LPUART_InitType* LPUART_InitStruct);
void LPUART_FlushRxFifo(LPUART_Module* LPUARTx);
void LPUART_FlushTxFifo(LPUART_Module* LPUARTx);
void LPUART_ConfigInt(LPUART_Module* LPUARTx,uint32_t LPUART_INT, FunctionalState Cmd);
void LPUART_EnableDMA(LPUART_Module* LPUARTx,uint32_t LPUART_DMAReq, FunctionalState Cmd);
void LPUART_ConfigWakeUpMethod(LPUART_Module* LPUARTx,uint32_t LPUART_WakeUpMethod);
void LPUART_EnableWakeUpStop(LPUART_Module* LPUARTx,FunctionalState Cmd);
void LPUART_ConfigSamplingMethod(LPUART_Module* LPUARTx,uint32_t LPUART_SamplingMethod);
void LPUART_EnableLoopBack(LPUART_Module* LPUARTx,FunctionalState Cmd);
void LPUART_SendData(LPUART_Module* LPUARTx,uint8_t Data);
uint8_t LPUART_ReceiveData(LPUART_Module* LPUARTx);
void LPUART_ConfigWakeUpData(LPUART_Module* LPUARTx,uint32_t LPUART_WakeUpData1,uint32_t LPUART_WakeUpData2);
FlagStatus LPUART_GetFlagStatus(LPUART_Module* LPUARTx,uint32_t LPUART_FLAG);
void LPUART_ClrFlag(LPUART_Module* LPUARTx,uint32_t LPUART_FLAG);
INTStatus LPUART_GetIntStatus(LPUART_Module* LPUARTx,uint32_t LPUART_INT);
void LPUART_ClrIntPendingBit(LPUART_Module* LPUARTx,uint32_t LPART_INT);
void LPUART_IdleFrameSet(LPUART_Module* LPUARTx,FunctionalState Cmd);
void LPUART_ConfigRXByte(LPUART_Module* LPUARTx,uint8_t LPUART_RXNUMWU);

#ifdef __cplusplus
}
#endif

#endif /* __N32H76X_78X_LPUART_H__ */

