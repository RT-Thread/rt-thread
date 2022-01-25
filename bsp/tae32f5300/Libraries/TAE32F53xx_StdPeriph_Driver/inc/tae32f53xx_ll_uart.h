/**
  ******************************************************************************
  * @file    tae32f53xx_ll_uart.h
  * @author  MCD Application Team
  * @brief   Header file for UART LL module.
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TAE32F53XX_LL_UART_H_
#define _TAE32F53XX_LL_UART_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32f53xx_ll_def.h"
#ifdef LL_DMA_MODULE_ENABLED
#include "tae32f53xx_ll_dma.h"
#endif


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @addtogroup UART_LL
  * @{
  */


/* Exported types ------------------------------------------------------------*/
/** @defgroup UART_LL_Exported_Types UART LL Exported Types
  * @brief    UART LL Exported Types
  * @{
  */

/**
  * @brief UART interrupt ID type definition
  */
typedef enum {
    UART_INT_ID_MODEM_STA       = 0x0,      /*!< modem status               */
    UART_INT_ID_NO_INT_PENDING  = 0x1,      /*!< no interrupt pending       */
    UART_INT_ID_TX_EMPTY        = 0x2,      /*!< THR register empty         */
    UART_INT_ID_RX_AVL          = 0x4,      /*!< received data available    */
    UART_INT_ID_RX_LINE_STA     = 0x6,      /*!< receiver line status       */
    UART_INT_ID_BUSY_DET        = 0x7,      /*!< busy detect                */
    UART_INT_ID_CHAR_TIMEOUT    = 0xc,      /*!< character timeout          */
} UART_IntIdETypeDef;

/**
  * @brief UART data length type definition
  */
typedef enum {
    UART_DAT_LEN_5b = 0,            /*!< Data length 5bits  */
    UART_DAT_LEN_6b = 1,            /*!< Data length 6bits  */
    UART_DAT_LEN_7b = 2,            /*!< Data length 7bits  */
    UART_DAT_LEN_8b = 3,            /*!< Data length 8bits  */
    UART_DAT_LEN_9b = 4,            /*!< Data length 9bits  */
} UART_DatLenETypeDef;

/**
  * @brief UART stop length type definition
  */
typedef enum {
    UART_STOP_LEN_1b,               /*!< Stop length 1bit   */
    UART_STOP_LEN_1b5,              /*!< Stop length 1.5bit */
    UART_STOP_LEN_2b,               /*!< Stop length 2bits  */
} UART_StopLenETypeDef;

/**
  * @brief UART parity type definition
  */
typedef enum {
    UART_PARITY_NO,                 /*!< Parity no          */
    UART_PARITY_ODD,                /*!< Parity odd         */
    UART_PARITY_EVEN,               /*!< Parity even        */
} UART_ParityETypeDef;

/**
  * @brief UART tx empty trigger level type definition
  */
typedef enum {
    UART_TX_EMPTY_TRI_LVL_EMPTY   = UART_TX_FIFO_TRIG_EMPTY,        /*!< tx empty trigger level empty           */
    UART_TX_EMPTY_TRI_LVL_2CAHR   = UART_TX_FIFO_TRIG_2CHAR,        /*!< tx empty trigger level 2char           */
    UART_TX_EMPTY_TRI_LVL_QUARTER = UART_TX_FIFO_TRIG_QUARTER,      /*!< tx empty trigger level quarter         */
    UART_TX_EMPTY_TRI_LVL_HALF    = UART_TX_FIFO_TRIG_HALF,         /*!< tx empty trigger level half            */
} UART_TxEmptyTriLvlETypeDef;

/**
  * @brief UART rx available trigger level type definition
  */
typedef enum {
    UART_RX_AVL_TRI_LVL_1CHAR       = UART_RX_FIFO_TRIG_1CHAR,      /*!< rx available trigger level 1char       */
    UART_RX_AVL_TRI_LVL_QUARTER     = UART_RX_FIFO_TRIG_QUARTER,    /*!< rx available trigger level quarter     */
    UART_RX_AVL_TRI_LVL_HALF        = UART_RX_FIFO_TRIG_HALF,       /*!< rx available trigger level half        */
    UART_RX_AVL_TRI_LVL_FULL_LESS_2 = UART_RX_FIFO_TRIG_2LESS_FULL, /*!< rx available trigger level full less 2 */
} UART_RxAvlTriLvlETypeDef;

/**
  * @brief UART DE polarity type definition
  */
typedef enum {
    UART_DE_POL_ACT_LOW,                    /*!< DE polarity active low                 */
    UART_DE_POL_ACT_HIGH,                   /*!< DE polarity active high                */
} UART_DePolETypeDef;


/**
  * @brief UART Init Structure definition
  */
typedef struct __UART_InitTypeDef {
    uint32_t baudrate;                      /*!< baudrate                               */
    UART_DatLenETypeDef  dat_len;           /*!< data length                            */
    UART_StopLenETypeDef stop_len;          /*!< stop length                            */
    UART_ParityETypeDef  parity;            /*!< parity                                 */
    UART_TxEmptyTriLvlETypeDef tx_tl;       /*!< tx empty trigger level                 */
    UART_RxAvlTriLvlETypeDef   rx_tl;       /*!< rx available trigger level             */
    bool U9BAddrMatchMode_Enable;           /*!< 9_bit addr match enable                */
    uint8_t U9BRxAddress;                   /*!< 9_bit Receive addr                     */
} UART_InitTypeDef;

/**
  * @brief UART RS485 Mode Config Structure definition
  */
typedef struct __UART_Rs485CfgTypeDef {
    bool de_en;                             /*!< DE Singal Enable control               */
    uint8_t de_assert_time;                 /*!< Driver enable assertion time           */
    uint8_t de_deassert_time;               /*!< Driver enable de-assertion time        */
    UART_DePolETypeDef de_polarity;         /*!< DE Singal Polarity                     */
} UART_Rs485CfgTypeDef;

/**
  * @brief UART DMA Status
  */
typedef enum {
    UART_DMA_STATE_RESET = 0,            /*!< DMA State Reset:   not yet initialized or disabled */
    UART_DMA_STATE_READY,                /*!< DMA State Ready:   initialized and ready for use   */
    UART_DMA_STATE_BUSY,                 /*!< DMA State Busy:    process is ongoing              */
    UART_DMA_STATE_ERROR,                /*!< DMA State Error:   process is Error                */
    UART_DMA_STATE_FINISH,               /*!< DMA State Finish:  process has been finished       */
} UART_DMAStatusTypeDef;

/**
  * @brief I2C frame definition
  */
typedef struct __UART_FrameTypeDef {
    UART_TypeDef *Instance;                 /*!< UART Reg base address   */
    uint8_t  *buf;                          /*!< buffer pointer          */
    uint16_t buf_len;                       /*!< buffer length           */
#ifdef LL_DMA_MODULE_ENABLED
    DMA_ChannelETypeDef dma_tx_ch;          /*!< UART Tx DMA Channel     */
    DMA_ChannelETypeDef dma_rx_ch;          /*!< UART Rx DMA Channel     */
#endif
    UART_DMAStatusTypeDef TXdma_status;     /*!< UART DMA status         */
    UART_DMAStatusTypeDef RXdma_status;     /*!< UART DMA status         */
} UART_DMAHandleTypeDef;

/**
  * @}
  */


/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/** @defgroup UART_LL_Exported_Macros UART LL Exported Macros
  * @brief    UART LL Exported Macros
  * @{
  */

/**
  * @brief  RX buffer 8bits read
  * @param  __UART__ Specifies UART peripheral
  * @return 8bits read value
  */
#define __LL_UART_RxBuf8bits_Read(__UART__)         (READ_BIT((__UART__)->RBR, UART_RBR_LSB_8bits_Msk))

/**
  * @brief  RX buffer 9bits read
  * @param  __UART__ Specifies UART peripheral
  * @return 9bits read value
  */
#define __LL_UART_RxBuf9bits_Read(__UART__)         (READ_BIT((__UART__)->RBR, UART_RBR_9bits_Msk))

/**
  * @brief  TX buffer 8bits write
  * @param  __UART__ Specifies UART peripheral
  * @param  val write value
  * @return None
  */
#define __LL_UART_TxBuf8bits_Write(__UART__, val)   \
        MODIFY_REG((__UART__)->THR, UART_THR_LSB_8bits_Msk, (((val) & 0xffUL) << UART_THR_LSB_8bits_Pos))

/**
  * @brief  TX buffer 9bits write
  * @param  __UART__ Specifies UART peripheral
  * @param  val write value
  * @return None
  */
#define __LL_UART_TxBuf9bits_Write(__UART__, val)   \
        MODIFY_REG((__UART__)->THR, UART_THR_9bits_Msk, (((val) & 0x1ffUL) << UART_THR_LSB_8bits_Pos))

/**
  * @brief  divisor latch low wirte
  * @param  __UART__ Specifies UART peripheral
  * @param  val wirte value
  * @return None
  */
#define __LL_UART_DivLatchLow_Write(__UART__, val)  WRITE_REG((__UART__)->DLL, (val & UART_DLL_DLL_Msk))

/**
  * @brief  divisor latch high wirte
  * @param  __UART__ Specifies UART peripheral
  * @param  val wirte value
  * @return None
  */
#define __LL_UART_DivLatchHigh_Write(__UART__, val) WRITE_REG((__UART__)->DLH, (val & UART_DLH_DLH_Msk))

/**
  * @brief  programmable THRE interrupt enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_THRE_INT_En(__UART__)             SET_BIT((__UART__)->IER, UART_IER_PTIME_Msk)

/**
  * @brief  programmable THRE interrupt disable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_THRE_INT_Dis(__UART__)            CLEAR_BIT((__UART__)->IER, UART_IER_PTIME_Msk)

/**
  * @brief  modem status interrupt enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_ModemSta_INT_En(__UART__)         SET_BIT((__UART__)->IER, UART_IER_EDSSI_Msk)

/**
  * @brief  modem status interrupt disable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_ModemSta_INT_Dis(__UART__)        CLEAR_BIT((__UART__)->IER, UART_IER_EDSSI_Msk)

/**
  * @brief  RX line status interrupt enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RxLineSta_INT_En(__UART__)        SET_BIT((__UART__)->IER, UART_IER_ELSI_Msk)

/**
  * @brief  RX line status interrupt disable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RxLineSta_INT_Dis(__UART__)       CLEAR_BIT((__UART__)->IER, UART_IER_ELSI_Msk)

/**
  * @brief  TX holding register empty interrupt enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_TxHoldEmpyt_INT_En(__UART__)      SET_BIT((__UART__)->IER, UART_IER_ETBEI_Msk)

/**
  * @brief  TX holding register empty interrupt disable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_TxHoldEmpyt_INT_Dis(__UART__)     CLEAR_BIT((__UART__)->IER, UART_IER_ETBEI_Msk)

/**
  * @brief  RX data available interrupt enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RxDatAvl_INT_En(__UART__)         SET_BIT((__UART__)->IER, UART_IER_ERBFI_Msk)

/**
  * @brief  RX data available interrupt disable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RxDatAvl_INT_Dis(__UART__)        CLEAR_BIT((__UART__)->IER, UART_IER_ERBFI_Msk)

/**
  * @brief  Judge is FIFOs enable or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 isn't FIFOs enable
  * @retval 3 is FIFOs enable
  */
#define __LL_UART_IsFIFOsEn(__UART__)               (READ_BIT((__UART__)->IIR, UART_IIR_FIFOSE_Msk) >> UART_IIR_FIFOSE_Pos)

/**
  * @brief  Interrupt ID get
  * @param  __UART__ Specifies UART peripheral
  * @return Interrupt ID
  */
#define __LL_UART_INT_ID_Get(__UART__)              (READ_BIT((__UART__)->IIR, UART_IIR_IID_Msk) >> UART_IIR_IID_Pos)

/**
  * @brief  FCR register write
  * @param  __UART__ Specifies UART peripheral
  * @param  val write val
  * @return None
  */
#define __LL_UART_FCR_Write(__UART__, val)          WRITE_REG((__UART__)->FCR, val)

/**
  * @brief  Divisor latch access set
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_DivLatchAccess_Set(__UART__)      SET_BIT((__UART__)->LCR, UART_LCR_DLAB_Msk)

/**
  * @brief  Divisor latch access clear
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_DivLatchAccess_Clr(__UART__)      CLEAR_BIT((__UART__)->LCR, UART_LCR_DLAB_Msk)

/**
  * @brief  Break control set
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_BreakCtrl_Set(__UART__)           SET_BIT((__UART__)->LCR, UART_LCR_BC_Msk)

/**
  * @brief  Break control clear
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_BreakCtrl_Clr(__UART__)           CLEAR_BIT((__UART__)->LCR, UART_LCR_BC_Msk)

/**
  * @brief  Stick parity set
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_StickParity_Set(__UART__)         SET_BIT((__UART__)->LCR, UART_LCR_Stick_Parity_Msk)

/**
  * @brief  Stick parity clear
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_StickParity_Clr(__UART__)         CLEAR_BIT((__UART__)->LCR, UART_LCR_Stick_Parity_Msk)

/**
  * @brief  Even parity set
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_EvenParity_Set(__UART__)          SET_BIT((__UART__)->LCR, UART_LCR_EPS_Msk)

/**
  * @brief  Even parity clear
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_EvenParity_Clr(__UART__)          CLEAR_BIT((__UART__)->LCR, UART_LCR_EPS_Msk)

/**
  * @brief  Parity enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_Parity_En(__UART__)               SET_BIT((__UART__)->LCR, UART_LCR_PEN_Msk)

/**
  * @brief  Parity disable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_Parity_Dis(__UART__)              CLEAR_BIT((__UART__)->LCR, UART_LCR_PEN_Msk)

/**
  * @brief  Judge parity is enable or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 Parity isn't enable
  * @retval 1 Parity is enable
  */
#define __LL_UART_IsParityEn(__UART__)              (READ_BIT((__UART__)->LCR, UART_LCR_PEN_Msk) >> UART_LCR_PEN_Pos)

/**
  * @brief  Stop 1bit set
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_Stop1Bit_Set(__UART__)            CLEAR_BIT((__UART__)->LCR, UART_LCR_STOP_Msk)

/**
  * @brief  Stop 2bits set
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_Stop2bits_Set(__UART__)           SET_BIT((__UART__)->LCR, UART_LCR_STOP_Msk)

/**
  * @brief  Data length select
  * @param  __UART__ Specifies UART peripheral
  * @param  val select value
  * @return None
  */
#define __LL_UART_DatLen_Sel(__UART__, val)         MODIFY_REG((__UART__)->LCR, UART_LCR_DLS_Msk, ((val & 0x3UL) << UART_LCR_DLS_Pos))

/**
  * @brief  Judge is character address or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 isn't character address
  * @retval 1 is character address
  */
#define __LL_UART_IsCharacterAddr(__UART__)         (READ_BIT((__UART__)->LSR, UART_LSR_ADDR_RCVD_Msk) >> UART_LSR_ADDR_RCVD_Pos)

/**
  * @brief  Judge is RX FIFO error or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 isn't RX FIFO error
  * @retval 1 is RX FIFO error
  */
#define __LL_UART_IsRxFIFOErr(__UART__)             (READ_BIT((__UART__)->LSR, UART_LSR_RFE_Msk) >> UART_LSR_RFE_Pos)

/**
  * @brief  Judge is TX empty or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 isn't TX empty
  * @retval 1 is TX empty
  */
#define __LL_UART_IsTxEmpty(__UART__)               (READ_BIT((__UART__)->LSR, UART_LSR_TEMT_Msk) >> UART_LSR_TEMT_Pos)

/**
  * @brief  Judge is TX hold register empty or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 isn't TX hold register empty
  * @retval 1 is TX hold register empty
  */
#define __LL_UART_IsTxHoldRegEmpty(__UART__)        (READ_BIT((__UART__)->LSR, UART_LSR_THRE_Msk) >> UART_LSR_THRE_Pos)

/**
  * @brief  Judge is break interrupt or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 isn't break interrupt
  * @retval 1 is break interrupt
  */
#define __LL_UART_IsBreakInt(__UART__)              (READ_BIT((__UART__)->LSR, UART_LSR_BI_Msk) >> UART_LSR_BI_Pos)

/**
  * @brief  Judge is frame error or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 isn't frame error
  * @retval 1 is frame error
  */
#define __LL_UART_IsFrameErr(__UART__)              (READ_BIT((__UART__)->LSR, UART_LSR_FE_Msk) >> UART_LSR_FE_Pos)

/**
  * @brief  Judge is parity error or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 isn't parity error
  * @retval 1 is parity error
  */
#define __LL_UART_IsParityErr(__UART__)             (READ_BIT((__UART__)->LSR, UART_LSR_PE_Msk) >> UART_LSR_PE_Pos)

/**
  * @brief  Judge is overrun error or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 isn't overrun error
  * @retval 1 is overrun error
  */
#define __LL_UART_IsOverrunErr(__UART__)            (READ_BIT((__UART__)->LSR, UART_LSR_OE_Msk) >> UART_LSR_OE_Pos)

/**
  * @brief  Judge is data ready or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 isn't data ready
  * @retval 1 is data ready
  */
#define __LL_UART_IsDatReady(__UART__)              (READ_BIT((__UART__)->LSR, UART_LSR_DR_Msk) >> UART_LSR_DR_Pos)

/**
  * @brief  Line status get
  * @param  __UART__ Specifies UART peripheral
  * @return Line status
  */
#define __LL_UART_LineSta_Get(__UART__)             READ_BIT((__UART__)->LSR, UART_LSR_ALL_BIT_Msk)

/**
  * @brief  Judge is RXFIFO full or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 isn't RXFIFO full
  * @retval 1 is RXFIFO full
  */
#define __LL_UART_IsRxFIFOFull(__UART__)            (READ_BIT((__UART__)->USR, UART_USR_RFF_Msk) >> UART_USR_RFF_Pos)

/**
  * @brief  Judge is RXFIFO not empty or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 RXFIFO is empty
  * @retval 1 RXFIFO is not empty
  */
#define __LL_UART_IsRxFIFONotEmpty(__UART__)        (READ_BIT((__UART__)->USR, UART_USR_RFNE_Msk) >> UART_USR_RFNE_Pos)

/**
  * @brief  Judge is TXFIFO empty or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 TXFIFO is not empty
  * @retval 1 TXFIFO is empty
  */
#define __LL_UART_IsTxFIFOEmpty(__UART__)           (READ_BIT((__UART__)->USR, UART_USR_TFE_Msk) >> UART_USR_TFE_Pos)

/**
  * @brief  Judge is TXFIFO not full or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 TXFIFO is full
  * @retval 1 TXFIFO is not full
  */
#define __LL_UART_IsTxFIFONotFull(__UART__)         (READ_BIT((__UART__)->USR, UART_USR_TFNF_Msk) >> UART_USR_TFNF_Pos)

/**
  * @brief  TXFIFO level get
  * @param  __UART__ Specifies UART peripheral
  * @return TXFIFO level
  */
#define __LL_UART_TxFIFOLevel_Get(__UART__)         (READ_BIT((__UART__)->TFL, UART_TFL_TFL_Msk) >> UART_TFL_TFL_Pos)

/**
  * @brief  RXFIFO level get
  * @param  __UART__ Specifies UART peripheral
  * @return RXFIFO level
  */
#define __LL_UART_RxFIFOLevel_Get(__UART__)         (READ_BIT((__UART__)->RFL, UART_RFL_RFL_Msk) >> UART_RFL_RFL_Pos)

/**
  * @brief  TX halt enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_TxHalt_En(__UART__)               SET_BIT((__UART__)->HTX, UART_HTX_HTX_Msk)

/**
  * @brief  TX halt disable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_TxHalt_Dis(__UART__)              CLEAR_BIT((__UART__)->HTX, UART_HTX_HTX_Msk)

/**
  * @brief  TX mode set
  * @param  __UART__ Specifies UART peripheral
  * @param  mode tx mode
  * @return None
  */
#define __LL_UART_TxMode_Set(__UART__, mode)        MODIFY_REG((__UART__)->TCR, UART_TCR_XFER_MODE_Msk, mode)

/**
  * @brief  DE signal active high set
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_DE_ActHigh_Set(__UART__)          SET_BIT((__UART__)->TCR, UART_TCR_DE_POL_Msk)

/**
  * @brief  DE signal active low set
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_DE_ActLow_Set(__UART__)           CLEAR_BIT((__UART__)->TCR, UART_TCR_DE_POL_Msk)

/**
  * @brief  RE signal active high set
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RE_ActHigh_Set(__UART__)          SET_BIT((__UART__)->TCR, UART_TCR_RE_POL_Msk)

/**
  * @brief  RE signal active low set
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RE_ActLow_Set(__UART__)           CLEAR_BIT((__UART__)->TCR, UART_TCR_RE_POL_Msk)

/**
  * @brief  RS485 mode enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RS485Mode_En(__UART__)            SET_BIT((__UART__)->TCR, UART_TCR_RS485_EN_Msk)

/**
  * @brief  RS485 mode disable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RS485Mode_Dis(__UART__)           CLEAR_BIT((__UART__)->TCR, UART_TCR_RS485_EN_Msk)

/**
  * @brief  DE enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_DE_En(__UART__)                   SET_BIT((__UART__)->DE_EN, UART_DE_EN_DE_EN_Msk)

/**
  * @brief  DE disable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_DE_Dis(__UART__)                  CLEAR_BIT((__UART__)->DE_EN, UART_DE_EN_DE_EN_Msk)

/**
  * @brief  RE enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RE_En(__UART__)                   SET_BIT((__UART__)->RE_EN, UART_RE_EN_RE_EN_Msk)

/**
  * @brief  DE deassertion time set
  * @param  __UART__ Specifies UART peripheral
  * @param  val set value
  * @return None
  */
#define __LL_UART_DE_DeAssertTime_Set(__UART__, val)        \
        MODIFY_REG((__UART__)->DET, UART_DET_DE_DEASSERT_TIME_Msk, ((val & 0xffUL) << UART_DET_DE_DEASSERT_TIME_Pos))

/**
  * @brief  DE assertion time set
  * @param  __UART__ Specifies UART peripheral
  * @param  val set value
  * @return None
  */
#define __LL_UART_DE_AssertTime_Set(__UART__, val)          \
        MODIFY_REG((__UART__)->DET, UART_DET_DE_ASSERT_TIME_Msk, ((val & 0xffUL) << UART_DET_DE_ASSERT_TIME_Pos))

/**
  * @brief  RE to DE turn around time set
  * @param  __UART__ Specifies UART peripheral
  * @param  val set value
  * @return None
  */
#define __LL_UART_REtoDE_TurnAroundTime_Set(__UART__, val)  \
        MODIFY_REG((__UART__)->TAT, UART_TAT_RE_TO_DE_TIME_Msk, ((val & 0xffffUL) << UART_TAT_RE_TO_DE_TIME_Pos))

/**
  * @brief  DE to RE turn around time set
  * @param  __UART__ Specifies UART peripheral
  * @param  val set value
  * @return None
  */
#define __LL_UART_DEtoRE_TurnAroundTime_Set(__UART__, val)  \
        MODIFY_REG((__UART__)->TAT, UART_TAT_DE_TO_RE_TIME_Msk, ((val & 0xffffUL) << UART_TAT_DE_TO_RE_TIME_Pos))

/**
  * @brief  Divisor latch fraction set
  * @param  __UART__ Specifies UART peripheral
  * @param  val set value
  * @return None
  */
#define __LL_UART_DivLatchFrac_Set(__UART__, val)   MODIFY_REG((__UART__)->DLF, UART_DLF_DLF_Msk, ((val & 0xfUL) << UART_DLF_DLF_Pos))

/**
  * @brief  RAR set
  * @param  __UART__ Specifies UART peripheral
  * @param  addr set address
  * @return None
  */
#define __LL_UART_RAR_Set(__UART__, addr)           MODIFY_REG((__UART__)->RAR, UART_RAR_RAR_Msk, ((addr & 0xffUL) << UART_RAR_RAR_Pos))

/**
  * @brief  TAR set
  * @param  __UART__ Specifies UART peripheral
  * @param  addr set address
  * @return None
  */
#define __LL_UART_TAR_Set(__UART__, addr)           MODIFY_REG((__UART__)->TAR, UART_TAR_TAR_Msk, ((addr & 0xffUL) << UART_TAR_TAR_Pos))

/**
  * @brief  TX mode 9bits set
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_TxMode9bits_Set(__UART__)         SET_BIT((__UART__)->LCR_EXT, UART_LCR_EXT_TRANSMIT_MODE_Msk)

/**
  * @brief  TX mode 8bits set
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_TxMode8bits_Set(__UART__)         CLEAR_BIT((__UART__)->LCR_EXT, UART_LCR_EXT_TRANSMIT_MODE_Msk)

/**
  * @brief  TX mode status get
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 TX mode is 8bits
  * @retval 1 TX mode is 9bits
  */
#define __LL_UART_TxModeSta_Get(__UART__)           \
        (READ_BIT((__UART__)->LCR_EXT, UART_LCR_EXT_TRANSMIT_MODE_Msk) >> UART_LCR_EXT_TRANSMIT_MODE_Pos)

/**
  * @brief  Send address set
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_SendAddr_Start(__UART__)          SET_BIT((__UART__)->LCR_EXT, UART_LCR_EXT_SEND_ADDR_Msk)

/**
  * @brief  Send data set
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_SendDat_Start(__UART__)           CLEAR_BIT((__UART__)->LCR_EXT, UART_LCR_EXT_SEND_ADDR_Msk)

/**
  * @brief  Address match mode enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_AddrMatchMode_En(__UART__)        SET_BIT((__UART__)->LCR_EXT, UART_LCR_EXT_ADDR_MATCH_Msk)

/**
  * @brief  Address match mode disable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_AddrMatchMode_Dis(__UART__)       CLEAR_BIT((__UART__)->LCR_EXT, UART_LCR_EXT_ADDR_MATCH_Msk)

/**
  * @brief  Data length extension 9bits enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_DatLen9bitsExt_En(__UART__)       SET_BIT((__UART__)->LCR_EXT, UART_LCR_EXT_DLS_E_Msk)

/**
  * @brief  Data length extension 9bits disable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_DatLen9bitsExt_Dis(__UART__)      CLEAR_BIT((__UART__)->LCR_EXT, UART_LCR_EXT_DLS_E_Msk)

/**
  * @brief  Judge data length extension 9bits is enable or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 Data length extension 9bits isn't enable
  * @retval 1 Data length extension 9bits is enable
  */
#define __LL_UART_IsDatLen9bitsEn(__UART__)         (READ_BIT((__UART__)->LCR_EXT, UART_LCR_EXT_DLS_E_Msk) >> UART_LCR_EXT_DLS_E_Pos)

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @addtogroup UART_LL_Exported_Functions
  * @{
  */

/** @addtogroup UART_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_UART_Init(UART_TypeDef *Instance, UART_InitTypeDef *Init);
LL_StatusETypeDef LL_UART_DeInit(UART_TypeDef *Instance);
void LL_UART_MspInit(UART_TypeDef *Instance);
void LL_UART_MspDeInit(UART_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup UART_LL_Exported_Functions_Group2
  * @{
  */
LL_StatusETypeDef LL_UART_Transmit_CPU(UART_TypeDef *Instance, uint8_t *pData, uint16_t Size, uint32_t Timeout);
LL_StatusETypeDef LL_UART_Receive_CPU(UART_TypeDef *Instance, uint8_t *pData, uint16_t Size, uint32_t Timeout);

LL_StatusETypeDef LL_UART_Transmit_IT(UART_TypeDef *Instance);
LL_StatusETypeDef LL_UART_Receive_IT(UART_TypeDef *Instance);

#ifdef LL_DMA_MODULE_ENABLED
LL_StatusETypeDef LL_UART_Transmit_DMA(UART_TypeDef *Instance, DMA_UserCfgTypeDef *dma_user_cfg,
                                       UART_DMAHandleTypeDef *huart, uint32_t Timeout);
LL_StatusETypeDef LL_UART_Receive_DMA(UART_TypeDef *Instance, DMA_UserCfgTypeDef *dma_user_cfg,
                                      UART_DMAHandleTypeDef *huart, uint32_t Timeout);
#endif

/**
  * @}
  */


/** @addtogroup UART_LL_Exported_Functions_Group3
  * @{
  */
LL_StatusETypeDef LL_Uart_9bit_SendAddress(UART_TypeDef *Instance, uint8_t TxAddr);
LL_StatusETypeDef LL_UART_RS485Cfg(UART_TypeDef *Instance, UART_Rs485CfgTypeDef *cfg);
uint8_t LL_UART_TxFIFOLVL_GET(UART_TypeDef *Instance);
uint8_t LL_UART_RxFIFOLVL_GET(UART_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup UART_LL_Exported_Functions_Interrupt
  * @{
  */
void LL_UART_IRQHandler(UART_TypeDef *Instance);

void LL_UART_ModemStaCallback(UART_TypeDef *Instance);
void LL_UART_TxEmptyCallback(UART_TypeDef *Instance);
void LL_UART_RxAvailableCallback(UART_TypeDef *Instance);
void LL_UART_RxLineStaCallback(UART_TypeDef *Instance);
void LL_UART_BusyDetCallback(UART_TypeDef *Instance);
void LL_UART_CharTimeOutCallback(UART_TypeDef *Instance);

void LL_UART_BreakErrCallback(UART_TypeDef *Instance);
void LL_UART_FrameErrCallback(UART_TypeDef *Instance);
void LL_UART_ParityErrCallback(UART_TypeDef *Instance);
void LL_UART_RxOverrunErrCallback(UART_TypeDef *Instance);
/**
  * @}
  */

/**
  * @}
  */


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
  * @}
  */

/**
  * @}
  */


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* _TAE32F53XX_LL_UART_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

