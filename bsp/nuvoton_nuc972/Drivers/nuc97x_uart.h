/*
 * File      : nuc97x_uart.h
 * This file is part of RT-Thread RTOS
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/05/28     Urey         first implementation
 */

#ifndef _NUC970_UART_H_
#define _NUC970_UART_H_

/*-----------------------------------------*/
/* marco, type and constant definitions    */
/*-----------------------------------------*/
/// @cond HIDDEN_SYMBOLS
#define UART_NUM         11
#define UARTOFFSET       0x100


/** @addtogroup NUC970_UART_EXPORTED_CONSTANTS UART Exported Constants
  @{
*/

#define UARTWRITESIZE    100 /*!< UART max. write size */

#define UARTINTMODE      1   /*!< UART interrupt mode */
#define UARTPOLLMODE     0   /*!< UART polling mode */
#define DISABLEALLIER    0   /*!< Disable all interrupt */


/*---------------------------------------------------------------------------------------------------------*/
/* UA_FCR constants definitions                                                                            */
/*---------------------------------------------------------------------------------------------------------*/

#define UART_FCR_RFITL_1BYTE      (0x0 << UART_FCR_RFITL_Pos)   /*!< UA_FCR setting to set RX FIFO Trigger Level to 1 bit */
#define UART_FCR_RFITL_4BYTES     (0x1 << UART_FCR_RFITL_Pos)   /*!< UA_FCR setting to set RX FIFO Trigger Level to 4 bits */
#define UART_FCR_RFITL_8BYTES     (0x2 << UART_FCR_RFITL_Pos)   /*!< UA_FCR setting to set RX FIFO Trigger Level to 8 bits */
#define UART_FCR_RFITL_14BYTES    (0x3 << UART_FCR_RFITL_Pos)   /*!< UA_FCR setting to set RX FIFO Trigger Level to 14 bits */
#define UART_FCR_RFITL_30BYTES    (0x4 << UART_FCR_RFITL_Pos)   /*!< UA_FCR setting to set RX FIFO Trigger Level to 30 bits */
#define UART_FCR_RFITL_46BYTES    (0x5 << UART_FCR_RFITL_Pos)   /*!< UA_FCR setting to set RX FIFO Trigger Level to 46 bits */
#define UART_FCR_RFITL_62BYTES    (0x6 << UART_FCR_RFITL_Pos)   /*!< UA_FCR setting to set RX FIFO Trigger Level to 62 bits */

#define UART_FCR_RTS_TRI_LEV_1BYTE      (0x0 << UART_FCR_RTS_TRI_LEV_Pos)  /*!< UA_FCR setting to set RTS Trigger Level to 1 bit */
#define UART_FCR_RTS_TRI_LEV_4BYTES     (0x1 << UART_FCR_RTS_TRI_LEV_Pos)  /*!< UA_FCR setting to set RTS Trigger Level to 4 bits */
#define UART_FCR_RTS_TRI_LEV_8BYTES     (0x2 << UART_FCR_RTS_TRI_LEV_Pos)  /*!< UA_FCR setting to set RTS Trigger Level to 8 bits */
#define UART_FCR_RTS_TRI_LEV_14BYTES    (0x3 << UART_FCR_RTS_TRI_LEV_Pos)  /*!< UA_FCR setting to set RTS Trigger Level to 14 bits */
#define UART_FCR_RTS_TRI_LEV_30BYTES    (0x4 << UART_FCR_RTS_TRI_LEV_Pos)  /*!< UA_FCR setting to set RTS Trigger Level to 30 bits */
#define UART_FCR_RTS_TRI_LEV_46BYTES    (0x5 << UART_FCR_RTS_TRI_LEV_Pos)  /*!< UA_FCR setting to set RTS Trigger Level to 46 bits */
#define UART_FCR_RTS_TRI_LEV_62BYTES    (0x6 << UART_FCR_RTS_TRI_LEV_Pos)  /*!< UA_FCR setting to set RTS Trigger Level to 62 bits */

/*---------------------------------------------------------------------------------------------------------*/
/* UA_LCR constants definitions                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define UA_DATA_BITS_5     (0) /*!< UA_LCR setting to set UART word length to 5 bits */
#define UA_DATA_BITS_6     (1) /*!< UA_LCR setting to set UART word length to 6 bits */
#define UA_DATA_BITS_7     (2) /*!< UA_LCR setting to set UART word length to 7 bits */
#define UA_DATA_BITS_8     (3) /*!< UA_LCR setting to set UART word length to 8 bits */

#define UA_PARITY_NONE    (0x0 << UART_LCR_PBE_Pos) /*!< UA_LCR setting to set UART as no parity   */
#define UA_PARITY_ODD     (0x1 << UART_LCR_PBE_Pos) /*!< UA_LCR setting to set UART as odd parity  */
#define UA_PARITY_EVEN    (0x3 << UART_LCR_PBE_Pos) /*!< UA_LCR setting to set UART as even parity */
#define UA_PARITY_STICK    (0x8 << UART_LCR_PBE_Pos) /*!< UA_LCR setting to set UART as stick parity */

#define UA_STOP_BITS_1     (0x0 << UART_LCR_NSB_Pos) /*!< UA_LCR setting for one stop bit  */
#define UA_STOP_BITS_1_5   (0x1 << UART_LCR_NSB_Pos) /*!< UA_LCR setting for 1.5 stop bit when 5-bit word length  */
#define UA_STOP_BITS_2     (0x1 << UART_LCR_NSB_Pos) /*!< UA_LCR setting for two stop bit when 6, 7, 8-bit word length */

/*---------------------------------------------------------------------------------------------------------*/
/* UART RTS LEVEL TRIGGER constants definitions                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define UART_RTS_IS_HIGH_LEV_TRG (0x1 << UART_MCR_LEV_RTS_Pos) /*!< Set RTS is High Level Tigger   */
#define UART_RTS_IS_LOW_LEV_TRG  (0x0 << UART_MCR_LEV_RTS_Pos) /*!< Set RTS is Low Level Tigger    */

/*---------------------------------------------------------------------------------------------------------*/
/* UART CTS LEVEL TRIGGER constants definitions                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define UART_CTS_IS_HIGH_LEV_TRG    (0x1 << UART_MSR_LEV_CTS_Pos) /*!< Set CTS is High Level Trigger   */
#define UART_CTS_IS_LOW_LEV_TRG     (0x0 << UART_MSR_LEV_CTS_Pos) /*!< Set CTS is Low Level Trigger    */

/*---------------------------------------------------------------------------------------------------------*/
/* UA_FUNC_SEL constants definitions                                                                       */
/*---------------------------------------------------------------------------------------------------------*/
#define UART_FUNC_SEL_UART  (0x0 << UART_FUN_SEL_FUN_SEL_Pos) /*!< UA_FUNC_SEL setting to set UART Function  (Default) */
#define UART_FUNC_SEL_LIN   (0x1 << UART_FUN_SEL_FUN_SEL_Pos) /*!< UA_FUNC_SEL setting to set LIN Funciton             */
#define UART_FUNC_SEL_IrDA  (0x2 << UART_FUN_SEL_FUN_SEL_Pos) /*!< UA_FUNC_SEL setting to set IrDA Function            */
#define UART_FUNC_SEL_RS485 (0x3 << UART_FUN_SEL_FUN_SEL_Pos) /*!< UA_FUNC_SEL setting to set RS485 Function           */

/*---------------------------------------------------------------------------------------------------------*/
/* UA_LIN_CTL constants definitions                                                                       */
/*---------------------------------------------------------------------------------------------------------*/
#define UART_LIN_CTL_LINS_EN        (0x1UL << UART_LIN_CTL_LINS_EN_Pos)       /*!< UA_LIN_CTL setting to set LIN Slave Mode Enable */
#define UART_LIN_CTL_LINS_HDET_EN   (0x1UL << UART_LIN_CTL_LINS_HDET_EN_Pos)  /*!< UA_LIN_CTL setting to set LIN Slave Header Detection Enable */
#define UART_LIN_CTL_LINS_ARS_EN    (0x1UL << UART_LIN_CTL_LINS_ARS_EN_Pos)   /*!< UA_LIN_CTL setting to set LIN Slave Automatic Resynchronization Mode Enable */
#define UART_LIN_CTL_LINS_DUM_EN    (0x1UL << UART_LIN_CTL_LINS_DUM_EN_Pos)   /*!< UA_LIN_CTL setting to set LIN Slave Divider Update Method Enable */
#define UART_LIN_CTL_LIN_WAKE_EN    (0x1UL << UART_LIN_CTL_LIN_WAKE_EN_Pos)   /*!< UA_LIN_CTL setting to set LIN Wake-Up Mode Enable */
#define UART_LIN_CTL_LIN_SHD        (0x1UL << UART_LIN_CTL_LIN_SHD_Pos)       /*!< UA_LIN_CTL setting to set LIN TX Send Header Enable */
#define UART_LIN_CTL_LIN_IDPEN      (0x1UL << UART_LIN_CTL_LIN_IDPEN_Pos)     /*!< UA_LIN_CTL setting to set LIN ID Parity Enable */
#define UART_LIN_CTL_LIN_BKDET_ENN  (0x1UL << UART_LIN_CTL_LIN_BKDET_EN_Pos)  /*!< UA_LIN_CTL setting to set LIN Break Detection Enable */
#define UART_LIN_CTL_LIN_RX_DIS     (0x1UL << UART_LIN_CTL_LIN_RX_DIS_Pos)    /*!< UA_LIN_CTL setting to set LIN Receiver Disable */
#define UART_LIN_CTL_BIT_ERR_EN     (0x1UL << UART_LIN_CTL_BIT_ERR_EN_Pos)    /*!< UA_LIN_CTL setting to set Bit Error Detect Enable */
#define UART_LIN_CTL_LIN_BKFL(x)    (((x)-1) << UART_LIN_CTL_LIN_BKFL_Pos)  /*!< UA_LIN_CTL setting to set LIN Break Field Length, x = 10 ~ 15, default value is 12 */
#define UART_LIN_CTL_LIN_BS_LEN(x)  (((x)-1) << UART_LIN_CTL_LIN_BS_LEN_Pos)/*!< UA_LIN_CTL setting to set LIN Break/Sync Delimiter Length, x = 1 ~ 4 */
#define UART_LIN_CTL_LIN_HEAD_SEL_BREAK             (0x0UL << UART_LIN_CTL_LIN_HEAD_SEL_Pos)    /*!< UA_LIN_CTL setting to set LIN Header Select to break field */
#define UART_LIN_CTL_LIN_HEAD_SEL_BREAK_SYNC        (0x1UL << UART_LIN_CTL_LIN_HEAD_SEL_Pos)    /*!< UA_LIN_CTL setting to set LIN Header Select to break field and sync field */
#define UART_LIN_CTL_LIN_HEAD_SEL_BREAK_SYNC_ID     (0x2UL << UART_LIN_CTL_LIN_HEAD_SEL_Pos)    /*!< UA_LIN_CTL setting to set LIN Header Select to break field, sync field and ID field*/
#define UART_LIN_CTL_LIN_LIN_PID(x) ((x) << UART_LIN_CTL_LIN_PID_Pos)       /*!< UA_LIN_CTL setting to set LIN PID value */


/*---------------------------------------------------------------------------------------------------------*/
/* BAUD constants definitions                                                                              */
/*---------------------------------------------------------------------------------------------------------*/
#define UART_BAUD_MODE0        (0)  /*!< Set UART Baudrate Mode is Mode0 */
#define UART_BAUD_MODE2        (UART_BAUD_DIV_X_EN_Msk | UART_BAUD_DIV_X_ONE_Msk)  /*!< Set UART Baudrate Mode is Mode2 */

/* UART THR Bit Field Definitions */
#define UART_THR_THR_Pos         0                                          /*!< UART THR: THR Position  */
#define UART_THR_THR_Msk        (0xFFul << UART_THR_THR_Pos)                 /*!< UART THR: THR Mask      */

/* UART RBR Bit Field Definitions */
#define UART_RBR_RBR_Pos         0                                          /*!< UART RBR: RBR Posistion */
#define UART_RBR_RBR_Msk        (0xFFul << UART_RBR_RBR_Pos)                 /*!< UART RBR: RBR Mask      */

/* UART IER Bit Field Definitions */
#define UART_IER_DMA_RX_EN_Pos      15                                      /*!< UART IER: RX DMA Enable Posistion */
#define UART_IER_DMA_RX_EN_Msk      (1ul << UART_IER_DMA_RX_EN_Pos)         /*!< UART IER: RX DMA Enable Mask      */

#define UART_IER_DMA_TX_EN_Pos      14                                      /*!< UART IER: TX DMA Enable Posistion */
#define UART_IER_DMA_TX_EN_Msk      (1ul << UART_IER_DMA_TX_EN_Pos)         /*!< UART IER: TX DMA Enable Mask      */

#define UART_IER_AUTO_CTS_EN_Pos    13                                      /*!< UART IER: AUTO_CTS_EN Posistion      */
#define UART_IER_AUTO_CTS_EN_Msk    (1ul << UART_IER_AUTO_CTS_EN_Pos)       /*!< UART IER: AUTO_CTS_EN Mask           */

#define UART_IER_AUTO_RTS_EN_Pos    12                                      /*!< UART IER: AUTO_RTS_EN Posistion      */
#define UART_IER_AUTO_RTS_EN_Msk    (1ul << UART_IER_AUTO_RTS_EN_Pos)       /*!< UART IER: AUTO_RTS_EN Mask           */

#define UART_IER_TIME_OUT_EN_Pos    11                                      /*!< UART IER: TIME_OUT_EN Posistion      */
#define UART_IER_TIME_OUT_EN_Msk    (1ul << UART_IER_TIME_OUT_EN_Pos)       /*!< UART IER: TIME_OUT_EN Mask           */

#define UART_IER_LIN_RX_BRK_IEN_Pos 8                                       /*!< UART IER: LIN_RX_BRK_IEN Posistion   */
#define UART_IER_LIN_RX_BRK_IEN_Msk (1ul << UART_IER_LIN_RX_BRK_IEN_Pos)    /*!< UART IER: LIN_RX_BRK_IEN Mask        */

#define UART_IER_WAKE_EN_Pos        6                                       /*!< UART IER: WAKE_EN Posistion          */
#define UART_IER_WAKE_EN_Msk        (1ul << UART_IER_WAKE_EN_Pos)           /*!< UART IER: WAKE_EN Mask               */

#define UART_IER_BUF_ERR_IEN_Pos    5                                       /*!< UART IER: BUF_ERR_IEN Posistion      */
#define UART_IER_BUF_ERR_IEN_Msk    (1ul << UART_IER_BUF_ERR_IEN_Pos)       /*!< UART IER: BUF_ERR_IEN Mask           */

#define UART_IER_RTO_IEN_Pos        4                                       /*!< UART IER: RTO_IEN Posistion          */
#define UART_IER_RTO_IEN_Msk        (1ul << UART_IER_RTO_IEN_Pos)           /*!< UART IER: RTO_IEN Mask               */

#define UART_IER_MODEM_IEN_Pos      3                                       /*!< UART IER: MODEM_IEN Posistion        */
#define UART_IER_MODEM_IEN_Msk      (1ul << UART_IER_MODEM_IEN_Pos)         /*!< UART IER: MODEM_IEN Mask             */

#define UART_IER_RLS_IEN_Pos        2                                       /*!< UART IER: RLS_IEN Posistion          */
#define UART_IER_RLS_IEN_Msk        (1ul << UART_IER_RLS_IEN_Pos)           /*!< UART IER: RLS_IEN Mask               */

#define UART_IER_THRE_IEN_Pos       1                                       /*!< UART IER: THRE_IEN Posistion         */
#define UART_IER_THRE_IEN_Msk       (1ul << UART_IER_THRE_IEN_Pos)          /*!< UART IER: THRE_IEN Mask              */

#define UART_IER_RDA_IEN_Pos        0                                       /*!< UART IER: RDA_IEN Position           */
#define UART_IER_RDA_IEN_Msk        (1ul << UART_IER_RDA_IEN_Pos)           /*!< UART IER: RDA_IEN Mask               */

/* UART FCR Bit Field Definitions */
#define UART_FCR_RTS_TRI_LEV_Pos    16                                      /*!< UART FCR: RTS_TRI_LEV Position       */
#define UART_FCR_RTS_TRI_LEV_Msk    (0xFul << UART_FCR_RTS_TRI_LEV_Pos)     /*!< UART FCR: RTS_TRI_LEV Mask           */

#define UART_FCR_RX_DIS_Pos         8                                       /*!< UART FCR: RX_DIS Position            */
#define UART_FCR_RX_DIS_Msk         (1ul << UART_FCR_RX_DIS_Pos)            /*!< UART FCR: RX_DIS Mask                */

#define UART_FCR_RFITL_Pos          4                                       /*!< UART FCR: RFITL Position             */
#define UART_FCR_RFITL_Msk          (0xFul << UART_FCR_RFITL_Pos)           /*!< UART FCR: RFITL Mask                 */

#define UART_FCR_TFR_Pos            2                                       /*!< UART FCR: TFR Position               */
#define UART_FCR_TFR_Msk            (1ul << UART_FCR_TFR_Pos)               /*!< UART FCR: TFR Mask                   */

#define UART_FCR_RFR_Pos            1                                       /*!< UART FCR: RFR Position               */
#define UART_FCR_RFR_Msk            (1ul << UART_FCR_RFR_Pos)               /*!< UART FCR: RFR Mask                   */

/* UART LCR Bit Field Definitions */
#define UART_LCR_BCB_Pos            6                                       /*!< UART LCR: BCB Position               */
#define UART_LCR_BCB_Msk            (1ul << UART_LCR_BCB_Pos)               /*!< UART LCR: BCB Mask                   */

#define UART_LCR_SPE_Pos            5                                       /*!< UART LCR: SPE Position               */
#define UART_LCR_SPE_Msk            (1ul << UART_LCR_SPE_Pos)               /*!< UART LCR: SPE Mask                   */

#define UART_LCR_EPE_Pos            4                                       /*!< UART LCR: EPE Position               */
#define UART_LCR_EPE_Msk            (1ul << UART_LCR_EPE_Pos)               /*!< UART LCR: EPE Mask                   */

#define UART_LCR_PBE_Pos            3                                       /*!< UART LCR: PBE Position               */
#define UART_LCR_PBE_Msk            (1ul << UART_LCR_PBE_Pos)               /*!< UART LCR: PBE Mask                   */

#define UART_LCR_NSB_Pos            2                                       /*!< UART LCR: NSB Position               */
#define UART_LCR_NSB_Msk            (1ul << UART_LCR_NSB_Pos)               /*!< UART LCR: NSB Mask                   */

#define UART_LCR_WLS_Pos            0                                       /*!< UART LCR: WLS Position               */
#define UART_LCR_WLS_Msk            (0x3ul << UART_LCR_WLS_Pos)             /*!< UART LCR: WLS Mask                   */

/* UART MCR Bit Field Definitions */
#define UART_MCR_RTS_ST_Pos         13                                      /*!< UART MCR: RTS_ST Position            */
#define UART_MCR_RTS_ST_Msk         (1ul << UART_MCR_RTS_ST_Pos)            /*!< UART MCR: RTS_ST Mask                */

#define UART_MCR_LEV_RTS_Pos        9                                       /*!< UART MCR: LEV_RTS Position           */
#define UART_MCR_LEV_RTS_Msk        (1ul << UART_MCR_LEV_RTS_Pos)           /*!< UART MCR: LEV_RTS Mask               */

#define UART_MCR_RTS_Pos            1                                       /*!< UART MCR: RTS Position               */
#define UART_MCR_RTS_Msk            (1ul << UART_MCR_RTS_Pos)               /*!< UART MCR: RTS Mask                   */

/* UART MSR Bit Field Definitions */
#define UART_MSR_LEV_CTS_Pos        8                                       /*!< UART MSR: LEV_CTS Position           */
#define UART_MSR_LEV_CTS_Msk        (1ul << UART_MSR_LEV_CTS_Pos)           /*!< UART MSR: LEV_CTS Mask               */

#define UART_MSR_CTS_ST_Pos         4                                       /*!< UART MSR: CTS_ST Position            */
#define UART_MSR_CTS_ST_Msk         (1ul << UART_MSR_CTS_ST_Pos)            /*!< UART MSR: CTS_ST Mask                */

#define UART_MSR_DCTSF_Pos          0                                       /*!< UART MSR: DCTST Position             */
#define UART_MSR_DCTSF_Msk          (1ul << UART_MSR_DCTSF_Pos)             /*!< UART MSR: DCTST Mask                 */


/* UART FSR Bit Field Definitions */
#define UART_FSR_TE_FLAG_Pos        28                                      /*!< UART FSR: TE_FLAG Position           */
#define UART_FSR_TE_FLAG_Msk        (1ul << UART_FSR_TE_FLAG_Pos)           /*!< UART FSR: TE_FLAG Mask               */

#define UART_FSR_TX_OVER_IF_Pos     24                                      /*!< UART FSR: TX_OVER_IF Position        */
#define UART_FSR_TX_OVER_IF_Msk     (1ul << UART_FSR_TX_OVER_IF_Pos)        /*!< UART FSR: TX_OVER_IF Mask            */

#define UART_FSR_TX_FULL_Pos        23                                      /*!< UART FSR: TX_FULL Position           */
#define UART_FSR_TX_FULL_Msk        (1ul << UART_FSR_TX_FULL_Pos)           /*!< UART FSR: TX_FULL Mask               */

#define UART_FSR_TX_EMPTY_Pos       22                                      /*!< UART FSR: TX_EMPTY Position          */
#define UART_FSR_TX_EMPTY_Msk       (1ul << UART_FSR_TX_EMPTY_Pos)          /*!< UART FSR: TX_EMPTY Mask              */

#define UART_FSR_TX_POINTER_Pos     16                                      /*!< UART FSR: TX_POINTER Position        */
#define UART_FSR_TX_POINTER_Msk     (0x3Ful << UART_FSR_TX_POINTER_Pos)     /*!< UART FSR: TX_POINTER Mask            */

#define UART_FSR_RX_FULL_Pos        15                                      /*!< UART FSR: RX_FULL Position           */
#define UART_FSR_RX_FULL_Msk        (1ul << UART_FSR_RX_FULL_Pos)           /*!< UART FSR: RX_FULL Mask               */

#define UART_FSR_RX_EMPTY_Pos       14                                      /*!< UART FSR: RX_EMPTY Position          */
#define UART_FSR_RX_EMPTY_Msk       (1ul << UART_FSR_RX_EMPTY_Pos)          /*!< UART FSR: RX_EMPTY Mask              */

#define UART_FSR_RX_POINTER_Pos     8                                       /*!< UART FSR: RX_POINTERS Position       */
#define UART_FSR_RX_POINTER_Msk     (0x3Ful << UART_FSR_RX_POINTER_Pos)     /*!< UART FSR: RX_POINTER Mask            */

#define UART_FSR_BIF_Pos            6                                       /*!< UART FSR: BIF Position               */
#define UART_FSR_BIF_Msk            (1ul << UART_FSR_BIF_Pos)               /*!< UART FSR: BIF Mask                   */

#define UART_FSR_FEF_Pos            5                                       /*!< UART FSR: FEF Position               */
#define UART_FSR_FEF_Msk            (1ul << UART_FSR_FEF_Pos)               /*!< UART FSR: FEF Mask                   */

#define UART_FSR_PEF_Pos            4                                       /*!< UART FSR: PEF Position               */
#define UART_FSR_PEF_Msk            (1ul << UART_FSR_PEF_Pos)               /*!< UART FSR: PEF Mask                   */

#define UART_FSR_RS485_ADD_DETF_Pos 3                                       /*!< UART FSR: RS485_ADD_DETF Position    */
#define UART_FSR_RS485_ADD_DETF_Msk (1ul << UART_FSR_RS485_ADD_DETF_Pos)    /*!< UART FSR: RS485_ADD_DETF Mask        */

#define UART_FSR_RX_OVER_IF_Pos     0                                       /*!< UART FSR: RX_OVER_IF Position        */
#define UART_FSR_RX_OVER_IF_Msk     (1ul << UART_FSR_RX_OVER_IF_Pos)        /*!< UART FSR: RX_OVER_IF Mask            */

/* UART ISR Bit Field Definitions */
#define UART_ISR_LIN_RX_BREAK_INT_Pos    15                                      /*!< UART ISR: LIN_RX_BREAK_INT Position       */
#define UART_ISR_LIN_RX_BREAK_INT_Msk    (1ul << UART_ISR_LIN_RX_BREAK_INT_Pos)  /*!< UART ISR: LIN_RX_BREAK_INT Mask           */

#define UART_ISR_BUF_ERR_INT_Pos    13                                      /*!< UART ISR: BUF_ERR_INT Position       */
#define UART_ISR_BUF_ERR_INT_Msk    (1ul << UART_ISR_BUF_ERR_INT_Pos)       /*!< UART ISR: BUF_ERR_INT Mask           */

#define UART_ISR_TOUT_INT_Pos       12                                      /*!< UART ISR: TOUT_INT Position          */
#define UART_ISR_TOUT_INT_Msk       (1ul << UART_ISR_TOUT_INT_Pos)          /*!< UART ISR: TOUT_INT Mask              */

#define UART_ISR_MODEM_INT_Pos      11                                      /*!< UART ISR: MODEM_INT Position         */
#define UART_ISR_MODEM_INT_Msk      (1ul << UART_ISR_MODEM_INT_Pos)         /*!< UART ISR: MODEM_INT Mask             */

#define UART_ISR_RLS_INT_Pos        10                                      /*!< UART ISR: RLS_INT Position           */
#define UART_ISR_RLS_INT_Msk        (1ul << UART_ISR_RLS_INT_Pos)           /*!< UART ISR: RLS_INT Mask               */

#define UART_ISR_THRE_INT_Pos       9                                       /*!< UART ISR: THRE_INT Position          */
#define UART_ISR_THRE_INT_Msk       (1ul << UART_ISR_THRE_INT_Pos)          /*!< UART ISR: THRE_INT Mask              */

#define UART_ISR_RDA_INT_Pos        8                                       /*!< UART ISR: RDA_INT Position           */
#define UART_ISR_RDA_INT_Msk        (1ul << UART_ISR_RDA_INT_Pos)           /*!< UART ISR: RDA_INT Mask               */

#define UART_ISR_LIN_RX_BREAK_IF_Pos 7                                      /*!< UART ISR: LIN RX BREAK IF Position   */
#define UART_ISR_LIN_RX_BREAK_IF_Msk (1ul << UART_ISR_LIN_RX_BREAK_IF_Pos)  /*!< UART ISR: LIN RX BREAK IF Mask       */

#define UART_ISR_BUF_ERR_IF_Pos     5                                       /*!< UART ISR: BUF_ERR_IF Position        */
#define UART_ISR_BUF_ERR_IF_Msk     (1ul << UART_ISR_BUF_ERR_IF_Pos)        /*!< UART ISR: BUF_ERR_IF Mask            */

#define UART_ISR_TOUT_IF_Pos        4                                       /*!< UART ISR: TOUT_IF Position           */
#define UART_ISR_TOUT_IF_Msk        (1ul << UART_ISR_TOUT_IF_Pos)           /*!< UART ISR: TOUT_IF Mask               */

#define UART_ISR_MODEM_IF_Pos       3                                       /*!< UART ISR: MODEM_IF Position          */
#define UART_ISR_MODEM_IF_Msk       (1ul << UART_ISR_MODEM_IF_Pos)          /*!< UART ISR: MODEM_IF Mask              */

#define UART_ISR_RLS_IF_Pos         2                                       /*!< UART ISR: RLS_IF Position            */
#define UART_ISR_RLS_IF_Msk         (1ul << UART_ISR_RLS_IF_Pos)            /*!< UART ISR: RLS_IF Mask                */

#define UART_ISR_THRE_IF_Pos        1                                       /*!< UART ISR: THRE_IF Position           */
#define UART_ISR_THRE_IF_Msk        (1ul << UART_ISR_THRE_IF_Pos)           /*!< UART ISR: THRE_IF Mask               */

#define UART_ISR_RDA_IF_Pos         0                                       /*!< UART ISR: RDA_IF Position            */
#define UART_ISR_RDA_IF_Msk         (1ul << UART_ISR_RDA_IF_Pos)            /*!< UART ISR: RDA_IF Mask                */


/* UART TOR Bit Field Definitions */
#define UART_TOR_DLY_Pos           8                                        /*!< UART TOR: DLY Position               */
#define UART_TOR_DLY_Msk           (0xFFul << UART_TOR_DLY_Pos)             /*!< UART TOR: DLY Mask                   */

#define UART_TOR_TOIC_Pos          0                                        /*!< UART TOR: TOIC Position              */
#define UART_TOR_TOIC_Msk          (0xFFul << UART_TOR_TOIC_Pos)            /*!< UART TOR: TOIC Mask                  */

/* UART BAUD Bit Field Definitions */
#define UART_BAUD_DIV_X_EN_Pos    29                                        /*!< UART BARD: DIV_X_EN Position         */
#define UART_BAUD_DIV_X_EN_Msk    (1ul << UART_BAUD_DIV_X_EN_Pos)           /*!< UART BARD: DIV_X_EN Mask             */

#define UART_BAUD_DIV_X_ONE_Pos   28                                        /*!< UART BARD: DIV_X_ONE Position        */
#define UART_BAUD_DIV_X_ONE_Msk   (1ul << UART_BAUD_DIV_X_ONE_Pos)          /*!< UART BARD: DIV_X_ONE Mask            */

#define UART_BAUD_DIVIDER_X_Pos   24                                        /*!< UART BARD: DIVIDER_X Position        */
#define UART_BAUD_DIVIDER_X_Msk   (0xFul << UART_BAUD_DIVIDER_X_Pos)        /*!< UART BARD: DIVIDER_X Mask            */

#define UART_BAUD_BRD_Pos         0                                         /*!< UART BARD: BRD Position              */
#define UART_BAUD_BRD_Msk         (0xFFFFul << UART_BAUD_BRD_Pos)           /*!< UART BARD: BRD Mask                  */

/* UART IRCR Bit Field Definitions */
#define UART_IRCR_INV_RX_Pos      6                                         /*!< UART IRCR: INV_RX Position           */
#define UART_IRCR_INV_RX_Msk     (1ul << UART_IRCR_INV_RX_Pos)              /*!< UART IRCR: INV_RX Mask               */

#define UART_IRCR_INV_TX_Pos      5                                         /*!< UART IRCR: INV_TX Position           */
#define UART_IRCR_INV_TX_Msk     (1ul << UART_IRCR_INV_TX_Pos)              /*!< UART IRCR: INV_TX Mask               */

#define UART_IRCR_TX_SELECT_Pos   1                                         /*!< UART IRCR: TX_SELECT Position        */
#define UART_IRCR_TX_SELECT_Msk   (1ul << UART_IRCR_TX_SELECT_Pos)          /*!< UART IRCR: TX_SELECT Mask            */

/* UART ALT_CSR Bit Field Definitions */
#define UART_ALT_CSR_ADDR_MATCH_Pos      24                                      /*!< UART ALT_CSR: ADDR_MATCH Position    */
#define UART_ALT_CSR_ADDR_MATCH_Msk     (0xFFul << UART_ALT_CSR_ADDR_MATCH_Pos)  /*!< UART ALT_CSR: ADDR_MATCH Mask        */

#define UART_ALT_CSR_RS485_ADD_EN_Pos   15                                       /*!< UART ALT_CSR: RS485_ADD_EN Position  */
#define UART_ALT_CSR_RS485_ADD_EN_Msk   (1ul << UART_ALT_CSR_RS485_ADD_EN_Pos)   /*!< UART ALT_CSR: RS485_ADD_EN Mask      */

#define UART_ALT_CSR_RS485_AUD_Pos      10                                       /*!< UART ALT_CSR: RS485_AUD Position     */
#define UART_ALT_CSR_RS485_AUD_Msk      (1ul << UART_ALT_CSR_RS485_AUD_Pos)      /*!< UART ALT_CSR: RS485_AUD Mask         */

#define UART_ALT_CSR_RS485_AAD_Pos      9                                        /*!< UART ALT_CSR: RS485_AAD Position     */
#define UART_ALT_CSR_RS485_AAD_Msk      (1ul << UART_ALT_CSR_RS485_AAD_Pos)      /*!< UART ALT_CSR: RS485_AAD Mask         */

#define UART_ALT_CSR_RS485_NMM_Pos      8                                        /*!< UART ALT_CSR: RS485_NMM Position     */
#define UART_ALT_CSR_RS485_NMM_Msk      (1ul << UART_ALT_CSR_RS485_NMM_Pos)      /*!< UART ALT_CSR: RS485_NMM Mask         */

#define UART_ALT_CSR_LIN_TX_EN_Pos      7                                        /*!< UART ALT_CSR: LIN TX Break Mode Enable Position     */
#define UART_ALT_CSR_LIN_TX_EN_Msk      (1ul << UART_ALT_CSR_LIN_TX_EN_Pos)      /*!< UART ALT_CSR: LIN TX Break Mode Enable Mask         */

#define UART_ALT_CSR_LIN_RX_EN_Pos      6                                        /*!< UART ALT_CSR: LIN RX Enable Position     */
#define UART_ALT_CSR_LIN_RX_EN_Msk      (1ul << UART_ALT_CSR_LIN_RX_EN_Pos)      /*!< UART ALT_CSR: LIN RX Enable Mask         */

#define UART_ALT_CSR_UA_LIN_BKFL_Pos    0                                        /*!< UART ALT_CSR: UART LIN Break Field Length Position     */
#define UART_ALT_CSR_UA_LIN_BKFL_Msk    (0xFul << UART_ALT_CSR_UA_LIN_BKFL_Pos)  /*!< UART ALT_CSR: UART LIN Break Field Length Mask         */

/* UART FUN_SEL Bit Field Definitions */
#define UART_FUN_SEL_FUN_SEL_Pos        0                                        /*!< UART FUN_SEL: FUN_SEL Position       */
#define UART_FUN_SEL_FUN_SEL_Msk       (0x3ul << UART_FUN_SEL_FUN_SEL_Pos)       /*!< UART FUN_SEL: FUN_SEL Mask           */

/* UART LIN_CTL Bit Field Definitions */
#define UART_LIN_CTL_LIN_PID_Pos        24                                        /*!< UART LIN_CTL: LIN_PID Position       */
#define UART_LIN_CTL_LIN_PID_Msk        (0xFFul << UART_LIN_CTL_LIN_PID_Pos)      /*!< UART LIN_CTL: LIN_PID Mask           */

#define UART_LIN_CTL_LIN_HEAD_SEL_Pos   22                                        /*!< UART LIN_CTL: LIN_HEAD_SEL Position       */
#define UART_LIN_CTL_LIN_HEAD_SEL_Msk   (0x3ul << UART_LIN_CTL_LIN_HEAD_SEL_Pos)  /*!< UART LIN_CTL: LIN_HEAD_SEL Mask           */

#define UART_LIN_CTL_LIN_BS_LEN_Pos     20                                        /*!< UART LIN_CTL: LIN_BS_LEN Position       */
#define UART_LIN_CTL_LIN_BS_LEN_Msk     (0x3ul << UART_LIN_CTL_LIN_BS_LEN_Pos)    /*!< UART LIN_CTL: LIN_BS_LEN Mask           */

#define UART_LIN_CTL_LIN_BKFL_Pos       16                                        /*!< UART LIN_CTL: LIN_BKFL Position       */
#define UART_LIN_CTL_LIN_BKFL_Msk       (0xFul << UART_LIN_CTL_LIN_BKFL_Pos)      /*!< UART LIN_CTL: LIN_BKFL Mask           */

#define UART_LIN_CTL_BIT_ERR_EN_Pos     12                                        /*!< UART LIN_CTL: BIT_ERR_EN Position       */
#define UART_LIN_CTL_BIT_ERR_EN_Msk     (1ul << UART_LIN_CTL_BIT_ERR_EN_Pos)      /*!< UART LIN_CTL: BIT_ERR_EN Mask           */

#define UART_LIN_CTL_LIN_RX_DIS_Pos     11                                        /*!< UART LIN_CTL: LIN_RX_DIS Position       */
#define UART_LIN_CTL_LIN_RX_DIS_Msk     (1ul << UART_LIN_CTL_LIN_RX_DIS_Pos)      /*!< UART LIN_CTL: LIN_RX_DIS Mask           */

#define UART_LIN_CTL_LIN_BKDET_EN_Pos   10                                        /*!< UART LIN_CTL: LIN_BKDET_EN Position       */
#define UART_LIN_CTL_LIN_BKDET_EN_Msk   (1ul << UART_LIN_CTL_LIN_BKDET_EN_Pos)    /*!< UART LIN_CTL: LIN_BKDET_EN Mask           */

#define UART_LIN_CTL_LIN_IDPEN_Pos      9                                         /*!< UART LIN_CTL: LIN_IDPEN Position       */
#define UART_LIN_CTL_LIN_IDPEN_Msk      (1ul << UART_LIN_CTL_LIN_IDPEN_Pos)       /*!< UART LIN_CTL: LIN_IDPEN Mask           */

#define UART_LIN_CTL_LIN_SHD_Pos        8                                         /*!< UART LIN_CTL: LIN_SHD Position       */
#define UART_LIN_CTL_LIN_SHD_Msk        (1ul << UART_LIN_CTL_LIN_SHD_Pos)         /*!< UART LIN_CTL: LIN_SHD Mask           */

#define UART_LIN_CTL_LIN_WAKE_EN_Pos    4                                          /*!< UART LIN_CTL: LIN_WAKE_EN Position       */
#define UART_LIN_CTL_LIN_WAKE_EN_Msk    (1ul << UART_LIN_CTL_LIN_WAKE_EN_Pos)      /*!< UART LIN_CTL: LIN_WAKE_EN Mask           */

#define UART_LIN_CTL_LINS_DUM_EN_Pos    3                                          /*!< UART LIN_CTL: LINS_DUM_EN Position       */
#define UART_LIN_CTL_LINS_DUM_EN_Msk    (1ul << UART_LIN_CTL_LINS_DUM_EN_Pos)      /*!< UART LIN_CTL: LINS_DUM_EN Mask           */

#define UART_LIN_CTL_LINS_ARS_EN_Pos    2                                          /*!< UART LIN_CTL: LINS_ARS_EN Position       */
#define UART_LIN_CTL_LINS_ARS_EN_Msk    (1ul << UART_LIN_CTL_LINS_ARS_EN_Pos)      /*!< UART LIN_CTL: LINS_ARS_EN Mask           */

#define UART_LIN_CTL_LINS_HDET_EN_Pos   1                                          /*!< UART LIN_CTL: LINS_HDET_EN Position       */
#define UART_LIN_CTL_LINS_HDET_EN_Msk   (1ul << UART_LIN_CTL_LINS_HDET_EN_Pos)     /*!< UART LIN_CTL: LINS_HDET_EN Mask           */

#define UART_LIN_CTL_LINS_EN_Pos        0                                          /*!< UART LIN_CTL: LINS_EN Position       */
#define UART_LIN_CTL_LINS_EN_Msk        (1ul << UART_LIN_CTL_LINS_EN_Pos)          /*!< UART LIN_CTL: LINS_EN Mask           */

/* UART LIN_SR Bit Field Definitions */
#define UART_LIN_SR_LINS_SYNC_F_Pos     3                                           /*!< UART LIN_SR: LINS_SYNC_F Position       */
#define UART_LIN_SR_LINS_SYNC_F_Msk     (1ul << UART_LIN_SR_LINS_SYNC_F_Pos)        /*!< UART LIN_SR: LINS_SYNC_F Mask           */

#define UART_LIN_SR_LINS_IDPERR_F_Pos   2                                           /*!< UART LIN_SR: LINS_IDPERR_F Position       */
#define UART_LIN_SR_LINS_IDPERR_F_Msk   (1ul << UART_LIN_SR_LINS_IDPERR_F_Pos)      /*!< UART LIN_SR: LINS_IDPERR_F Mask           */

#define UART_LIN_SR_LINS_HERR_F_Pos     1                                           /*!< UART LIN_SR: LINS_HERR_F Position       */
#define UART_LIN_SR_LINS_HERR_F_Msk     (1ul << UART_LIN_SR_LINS_HERR_F_Pos)        /*!< UART LIN_SR: LINS_HERR_F Mask           */

#define UART_LIN_SR_LINS_HDET_F_Pos     0                                           /*!< UART LIN_SR: LINS_HDET_F Position       */
#define UART_LIN_SR_LINS_HDET_F_Msk     (1ul << UART_LIN_SR_LINS_HDET_F_Pos)        /*!< UART LIN_SR: LINS_HDET_F Mask           */

/* UART DEBUG Bit Field Definitions */
#define UART_DEBUG_ERR_DIVIA_F_Pos      0                                           /*!< UART DEBUG: ERR_DIVIA_F Position       */
#define UART_DEBUG_ERR_DIVIA_F_Msk      (1ul << UART_DEBUG_ERR_DIVIA_F_Pos)         /*!< UART DEBUG: ERR_DIVIA_F Mask           */

#define UART_DEBUG_ERR_HETIME_OUT_F_Pos 1                                           /*!< UART DEBUG: ERR_HETIME_OUT_F Position  */
#define UART_DEBUG_ERR_HETIME_OUT_F_Msk (1ul << UART_DEBUG_ERR_HETIME_OUT_F_Pos)    /*!< UART DEBUG: ERR_HETIME_OUT_F Mask      */

#define UART_DEBUG_ERR_HEFE_F_Pos       2                                           /*!< UART DEBUG: ERR_HEFE_F Position        */
#define UART_DEBUG_ERR_HEFE_F_Msk       (1ul << UART_DEBUG_ERR_HEFE_F_Pos)          /*!< UART DEBUG: ERR_HEFE_F Mask            */

#define UART_DEBUG_ERR_SYNC_F_Pos       3                                           /*!< UART DEBUG: ERR_SYNC_F Position        */
#define UART_DEBUG_ERR_SYNC_F_Msk       (1ul << UART_DEBUG_ERR_SYNC_F_Pos)          /*!< UART DEBUG: ERR_SYNC_F Mask            */

/* UART SC_CTL Bit Field Definitions */
#define UART_SC_CTL_RX_ERETRY_Pos       0                                           /*!< UART SC_CTL: RX_ERETRY Position        */
#define UART_SC_CTL_RX_ERETRY_Msk       (7ul << UART_SC_CTL_RX_ERETRY_Pos)          /*!< UART SC_CTL: RX_ERETRY Mask            */

#define UART_SC_CTL_RX_ERETRY_EN_Pos    3                                           /*!< UART SC_CTL: RX_ERETRY_EN Position     */
#define UART_SC_CTL_RX_ERETRY_EN_Msk    (1ul << UART_SC_CTL_RX_ERETRY_EN_Pos)       /*!< UART SC_CTL: RX_ERETRY_EN Mask         */

#define UART_SC_CTL_TX_ERETRY_Pos       4                                           /*!< UART SC_CTL: TX_ERETRY Position        */
#define UART_SC_CTL_TX_ERETRY_Msk       (7ul << UART_SC_CTL_TX_ERETRY_Pos)          /*!< UART SC_CTL: TX_ERETRY Mask            */

#define UART_SC_CTL_TX_ERETRY_EN_Pos    7                                           /*!< UART SC_CTL: TX_ERETRY_EN Position     */
#define UART_SC_CTL_TX_ERETRY_EN_Msk    (1ul << UART_SC_CTL_TX_ERETRY_EN_Pos)       /*!< UART SC_CTL: TX_ERETRY_EN Mask         */

/* UART SC_FSR Bit Field Definitions */
#define UART_SC_FSR_RX_OVER_ERETRY_Pos      0                                       /*!< UART SC_FSR: RX_OVER_ERETRY Position   */
#define UART_SC_FSR_RX_OVER_ERETRY_Msk      (1ul << UART_SC_FSR_RX_OVER_ERETRY_Pos) /*!< UART SC_FSR: RX_OVER_ERETRY Mask       */

#define UART_SC_FSR_TX_OVER_ERETRY_Pos      1                                       /*!< UART SC_FSR: TX_OVER_ERETRY Position   */
#define UART_SC_FSR_TX_OVER_ERETRY_Msk      (1ul << UART_SC_FSR_TX_OVER_ERETRY_Pos) /*!< UART SC_FSR: TX_OVER_ERETRY Mask       */

#define UART_SC_FSR_RX_ERETRY_F_Pos         8                                       /*!< UART SC_FSR: RX_ERETRY_F Position      */
#define UART_SC_FSR_RX_ERETRY_F_Msk         (1ul << UART_SC_FSR_RX_ERETRY_F_Pos)    /*!< UART SC_FSR: RX_ERETRY_F Mask          */

#define UART_SC_FSR_TX_ERETRY_F_Pos         9                                       /*!< UART SC_FSR: TX_ERETRY_F Position      */
#define UART_SC_FSR_TX_ERETRY_F_Msk         (1ul << UART_SC_FSR_TX_ERETRY_F_Pos)    /*!< UART SC_FSR: TX_ERETRY_F Mask          */

/*  Enable/Disable IrDA Mode */
#define ENABLEIrDA            1  /*!< Enable IrDA */
#define DISABLEIrDA           0  /*!< Disable IrDA */

/*  define IrDA Direction */
#define IrDA_TX               0   /*!< Set IrDA Tx direction*/
#define IrDA_RX               1   /*!< Set IrDA Rx direction*/

/*  define RTS signal */
#define UART_RTS_HIGH           1  /*!< Set RTS high*/
#define UART_RTS_LOW            0  /*!< Set RTS low*/

/* define IOCTL command of UART operation mode, interrupt or pooling mode */
#define UART_IOC_SETTXMODE               1     /*!< Set Tx Mode */
#define UART_IOC_SETRXMODE               2     /*!< Set Tx Mode */
#define UART_IOC_GETRECCHARINFO          3     /*!< Get receive character */
#define UART_IOC_SETUARTPARAMETER        4     /*!< Config UART */
//#define UART_IOC_PERFORMBLUETOOTH      5
#define UART_IOC_PERFORMIrDA             6     /*!< Config IrDA */
#define UART_IOC_GETUARTREGISTERVALUE    7     /*!< Get UART register value*/
#define UART_IOC_GETERRNO                8     /*!< Get rrror code */
//#define UART_IOC_SETMODEMLOOPBACK      9
//#define UART_IOC_GETDSRSTATE           10
//#define UART_IOC_SETDTRSIGNAL          11
#define UART_IOC_SETINTERRUPT            12    /*!< Set interrupt */
#define UART_IOC_SETBREAKCONTROL         13    /*!< Set break */
#define UART_IOC_GETBIISTATE             14    /*!< Get break status */
#define UART_IOC_GETCTSSTATE             15    /*!< Get CTS status */
#define UART_IOC_SETRTSSIGNAL            16    /*!< Set RTS signal */
#define UART_IOC_SETMODEMINTERRUPT       17    /*!< Set modem interrupt */
#define UART_IOC_ENABLEHWFLOWCONTROL     18    /*!< Enable H/W flow control */
#define UART_IOC_DISABLEHWFLOWCONTROL    19    /*!< Disable H/W flow control */
//#define UART_IOC_ENABLESWFLOWCONTROL   20    /*!< Enable S/W flow control */
//#define UART_IOC_DISABLESWFLOWCONTROL  21    /*!< Disable S/W flow control */
//#define UART_IOC_SETUART1FULLMODEM       22
//#define UART_IOC_SETUART1HIGHSPEED       23

#define UART_IOC_FLUSH_TX_BUFFER         24    /*!< Flush Tx buffer */
#define UART_IOC_FLUSH_RX_BUFFER         25    /*!< Flus Rx buffer */

#define UART_IOC_SET_RS485_MODE          26     /*!< Select RS485 Mode */
#define UART_IOC_SEND_RS485_ADDRESS     27     /*!< Send RS485 Address*/
#define UART_IOC_SET_RS485_RXOFF         28     /*!< Select RS485 Mode */
#define UART_IOC_SET_ALTCTL_REG          29     /*!< Set ALT_CTL register */
#define UART_IOC_GET_ALTCTL_REG          30     /*!< Get ALT_CTL register */

#define UART_IOC_SET_LIN_MODE            31     /*!< Select LIN Mode */


/*  Enable/Disable Modem interrupt */
#define UART_ENABLE_MODEM_INT   0   /*!< Enable Modem interrupt */
#define UART_DISABLE_MODEM_INT  1   /*!< Disable Modem interrupt */

/* These error code can get from UART_IOC_GETERRNO */
#define UART_ERR_PARITY_INVALID          -1   /*!< Parity invalid */
#define UART_ERR_DATA_BITS_INVALID       -2   /*!< Data bits invalid */
#define UART_ERR_STOP_BITS_INVALID       -3   /*!< Stop bit invalid */
#define UART_ERR_TRIGGERLEVEL_INVALID    -4   /*!< Trigger level invalid */
#define UART_ERR_CHANNEL_INVALID         -5   /*!< UART channel invalid */
#define UART_ERR_ALLOC_MEMORY_FAIL       -6   /*!< Allocate memory error */
//#define UART_ERR_CLOCK_SOURCE_INVALID    -7   /*!< Clock Source invalid */
//#define UART_ERR_BAUDRATE_INVALID        -8   /*!< Baudrate invalid */
//#define UART_ERR_CONFIGURE_BT_FAIL       -9
#define UART_ERR_IrDA_COMMAND_INVALID    -10   /*!< IrDA mode invalid */
#define UART_ERR_TX_BUF_NOT_ENOUGH       -11   /*!< Tx buffer not enough */
#define UART_ERR_OPERATE_MODE_INVALID    -12   /*!< Operation mode invalid */
#define UART_ERR_SET_BAUDRATE_FAIL       -13   /*!< Set baudrate fail */

/* These are the error code actually returns to user application */
#define UART_ERR_ID     0xFFFF1700        /*!< UART library ID */
#define UART_ENOTTY    (1 | UART_ERR_ID)  /*!< Command not support           */
#define UART_ENODEV    (2 | UART_ERR_ID)  /*!< Interface number out of range */
#define UART_EIO       (3 | UART_ERR_ID)  /*!< Read/Write error              */


/** \brief  Structure type of UART data
 */
typedef struct
{
    UINT32      uFreq;       /*!< UART clock frequency */
    UINT32      uBaudRate;   /*!< Baudrate */
    UINT8       ucUartNo;    /*!< UART Port */
    UINT8       ucDataBits;  /*!< Select Data length */
    UINT8       ucStopBits;  /*!< Select stop bit length */
    UINT8       ucParity;    /*!< Select Parity */
    UINT8       ucRxTriggerLevel;  /*!< Select Rx FIFO trigger level */
} UART_Param,UART_T;

/*----------------------------------------------------*/
/* Define UART buffer structure                       */
/*----------------------------------------------------*/
typedef struct UART_BUFFER_STRUCT
{
    UINT32 volatile  uUartTxHead, uUartTxTail;
    UINT32 volatile  uUartRxHead, uUartRxTail;

    PUINT8    pucUartTxBuf;
    PUINT8    pucUartRxBuf;
    PVOID     pvUartVector;
    BOOL      bIsUseUARTTxInt;
    BOOL      bIsUseUARTRxInt;
    BOOL      bIsUARTInitial;

    PINT      pucUARTFlag;
    PINT      pucLINFlag;
    UINT32 volatile uRecCnt;
    INT32 volatile nErrno;

} UART_BUFFER_T;


/** \brief  Structure type of UART register
 */
typedef struct UART_REGISTER_STRUCT {
    UINT32 uUartReg[14][2]; /*!< Store UART register value */
} UART_REGISTER_T;


typedef struct
{
    __IO UINT32 RBR_THR;     /*!< Transmit Holding Register */
    __IO UINT32 IER;         /*!< Interrupt Enable Register */
    __IO UINT32 FCR;         /*!< FIFO Control Register */
    __IO UINT32 LCR;         /*!< Line Control Register */
    __IO UINT32 MCR;         /*!< Modem Control Register */
    __IO UINT32 MSR;         /*!< MODEM Status Register */
    __IO UINT32 FSR;         /*!< FIFO Status Register */
    __IO UINT32 ISR;         /*!< Interrupt Status Control Register */
    __IO UINT32 TOR;         /*!< Time-out Register */
    __IO UINT32 BAUD;        /*!< Baud Rate Divider Register */
    __IO UINT32 IRCR;        /*!< IrDA Control Register */
    __IO UINT32 ALT_CSR;     /*!< Alternate Control Register */
    __IO UINT32 FUN_SEL;     /*!< UART Function Select REgister */
    __IO UINT32 LIN_CTL;     /*!< UART LIN Control Register */
    __IO UINT32 LIN_SR;      /*!< LIN Status Register */
} UART_TypeDef;


/*---------------------------------------------------------------------------------------------------------*/
/* UART channel number                                                                                     */
/*---------------------------------------------------------------------------------------------------------*/
#define UART0       ((UART_TypeDef *) UART0_BA)     /*!< UART0  channel  */
#define UART1       ((UART_TypeDef *) UART1_BA)     /*!< UART1  channel  */
#define UART2       ((UART_TypeDef *) UART2_BA)     /*!< UART2  channel  */
#define UART3       ((UART_TypeDef *) UART3_BA)     /*!< UART3  channel  */
#define UART4       ((UART_TypeDef *) UART4_BA)     /*!< UART4  channel  */
#define UART5       ((UART_TypeDef *) UART5_BA)     /*!< UART5  channel  */
#define UART6       ((UART_TypeDef *) UART6_BA)     /*!< UART6  channel  */
#define UART7       ((UART_TypeDef *) UART7_BA)     /*!< UART7  channel  */
#define UART8       ((UART_TypeDef *) UART8_BA)     /*!< UART8  channel  */
#define UART9       ((UART_TypeDef *) UART9_BA)     /*!< UART9  channel  */
#define UARTA       ((UART_TypeDef *) UARTA_BA)     /*!< UARTA  channel  */


#define IS_UART_ALL_PERIPH(PERIPH)  (((PERIPH) == UART1) || \
                                      ((PERIPH) == UART2) || \
                                      ((PERIPH) == UART3) || \
                                      ((PERIPH) == UART4) || \
                                      ((PERIPH) == UART5) || \
                                      ((PERIPH) == UART6) || \
                                      ((PERIPH) == UART7) || \
                                      ((PERIPH) == UART8) || \
                                      ((PERIPH) == UART9) || \
                                      ((PERIPH) == UARTA)    )


/*@}*/ /* end of group NUC970_UART_EXPORTED_STRUCTS */


/** @addtogroup NUC970_UART_EXPORTED_FUNCTIONS UART Exported Functions
  @{
*/

/**
 *    @brief   Calculate UART baudrate mode0 divider
 *
 *    @param[in]   u32SrcFreq      UART clock frequency
 *    @param[in]   u32BaudRate     Baudrate of UART module
 *
 *    @return  UART baudrate mode0 divider
 *  \hideinitializer
 *
 */
#define UART_BAUD_MODE0_DIVIDER(u32SrcFreq, u32BaudRate)    (((u32SrcFreq + (u32BaudRate*8)) / u32BaudRate >> 4)-2)

/**
 *    @brief   Calculate UART baudrate mode2 divider
 *
 *    @param[in]   u32SrcFreq     UART clock frequency
 *    @param[in]   u32BaudRate    Baudrate of UART module
 *
 *    @return  UART baudrate mode2 divider
 * \hideinitializer
 */
#define UART_BAUD_MODE2_DIVIDER(u32SrcFreq, u32BaudRate)    (((u32SrcFreq + (u32BaudRate/2)) / u32BaudRate)-2)


INT UART_Configure(UART_TypeDef *UARTx,UART_Param *pParam);
void UART_EnableInterrupt(UART_TypeDef *UARTx, UINT32 uVal);
void UART_DisableInterrupt(UART_TypeDef *UARTx, UINT32 uVal);


#endif /* _NUC970_UART_H_ */
