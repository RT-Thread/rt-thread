/**************************************************************************//**
 * @file     nu_usci_i2c.h
 * @version  V3.0
 * $Revision: 1 $
 * $Date: 16/07/07 7:50p $
 * @brief    M2355 series USCI I2C(UI2C) driver header file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef __NU_USCI_I2C_H__
#define __NU_USCI_I2C_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup USCI_I2C_Driver USCI_I2C Driver
  @{
*/

/** @addtogroup USCI_I2C_EXPORTED_CONSTANTS USCI_I2C Exported Constants
  @{
*/

/*---------------------------------------------------------------------------------------------------------*/
/* USCI_I2C master event definitions                                                                       */
/*---------------------------------------------------------------------------------------------------------*/
enum UI2C_MASTER_EVENT
{
    MASTER_SEND_ADDRESS = 10u,    /*!< Master send address to Slave */
    MASTER_SEND_H_WR_ADDRESS,    /*!< Master send High address to Slave */
    MASTER_SEND_H_RD_ADDRESS,    /*!< Master send address to Slave (Read ADDR) */
    MASTER_SEND_L_ADDRESS,       /*!< Master send Low address to Slave */
    MASTER_SEND_DATA,            /*!< Master Send Data to Slave */
    MASTER_SEND_REPEAT_START,    /*!< Master send repeat start to Slave */
    MASTER_READ_DATA,            /*!< Master Get Data from Slave */
    MASTER_STOP,                 /*!< Master send stop to Slave */
    MASTER_SEND_START            /*!< Master send start to Slave */
};

/*---------------------------------------------------------------------------------------------------------*/
/* USCI_I2C slave event definitions                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
enum UI2C_SLAVE_EVENT
{
    SLAVE_ADDRESS_ACK = 100u,      /*!< Slave send address ACK */
    SLAVE_H_WR_ADDRESS_ACK,       /*!< Slave send High address ACK */
    SLAVE_L_WR_ADDRESS_ACK,       /*!< Slave send Low address ACK */
    SLAVE_GET_DATA,               /*!< Slave Get Data from Master (Write CMD) */
    SLAVE_SEND_DATA,              /*!< Slave Send Data to Master (Read CMD) */
    SLAVE_H_RD_ADDRESS_ACK,       /*!< Slave send High address ACK */
    SLAVE_L_RD_ADDRESS_ACK        /*!< Slave send Low address ACK */
};

/*---------------------------------------------------------------------------------------------------------*/
/*  USCI_CTL constant definitions.                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#define UI2C_CTL_PTRG              (0x20U)    /*!< USCI_CTL setting for I2C control bits. It would set PTRG bit */
#define UI2C_CTL_STA               (0x08U)    /*!< USCI_CTL setting for I2C control bits. It would set STA bit */
#define UI2C_CTL_STO               (0x04U)    /*!< USCI_CTL setting for I2C control bits. It would set STO bit */
#define UI2C_CTL_AA                (0x02U)    /*!< USCI_CTL setting for I2C control bits. It would set AA bit  */

/*---------------------------------------------------------------------------------------------------------*/
/*  USCI_I2C GCMode constant definitions.                                                                  */
/*---------------------------------------------------------------------------------------------------------*/
#define UI2C_GCMODE_ENABLE         (1U)    /*!< Enable  USCI_I2C GC Mode */
#define UI2C_GCMODE_DISABLE        (0U)    /*!< Disable USCI_I2C GC Mode */

/*---------------------------------------------------------------------------------------------------------*/
/*  USCI_I2C Wakeup Mode constant definitions.                                                             */
/*---------------------------------------------------------------------------------------------------------*/
#define UI2C_DATA_TOGGLE_WK        (0x0U << UI2C_WKCTL_WKADDREN_Pos)    /*!< Wakeup according data toggle */
#define UI2C_ADDR_MATCH_WK         (0x1U << UI2C_WKCTL_WKADDREN_Pos)    /*!< Wakeup according address match */

/*---------------------------------------------------------------------------------------------------------*/
/* USCI_I2C interrupt mask definitions                                                                     */
/*---------------------------------------------------------------------------------------------------------*/
#define UI2C_TO_INT_MASK           (0x001U)    /*!< Time-out interrupt mask */
#define UI2C_STAR_INT_MASK         (0x002U)    /*!< Start condition received interrupt mask */
#define UI2C_STOR_INT_MASK         (0x004U)    /*!< Stop condition received interrupt mask */
#define UI2C_NACK_INT_MASK         (0x008U)    /*!< Non-acknowledge interrupt mask */
#define UI2C_ARBLO_INT_MASK        (0x010U)    /*!< Arbitration lost interrupt mask */
#define UI2C_ERR_INT_MASK          (0x020U)    /*!< Error interrupt mask */
#define UI2C_ACK_INT_MASK          (0x040U)    /*!< Acknowledge interrupt mask */

/**@}*/ /* end of group USCI_I2C_EXPORTED_CONSTANTS */


/** @addtogroup USCI_I2C_EXPORTED_FUNCTIONS USCI_I2C Exported Functions
  @{
*/

/**
 *    @brief        This macro sets the USCI_I2C protocol control register at one time
 *
 *    @param[in]    ui2c      The pointer of the specified USCI_I2C module.
 *    @param[in]    u8Ctrl    Set the register value of USCI_I2C control register.
 *
 *    @return       None
 *
 *    @details      Set UI2C_PROTCTL register to control USCI_I2C bus conditions of START, STOP, PTRG, ACK.
 */
#define UI2C_SET_CONTROL_REG(ui2c, u8Ctrl) ((ui2c)->PROTCTL = ((ui2c)->PROTCTL & ~0x2EU) | (u8Ctrl))

/**
 *    @brief        This macro only set START bit to protocol control register of USCI_I2C module.
 *
 *    @param[in]    ui2c      The pointer of the specified USCI_I2C module.
 *
 *    @return       None
 *
 *    @details      Set the USCI_I2C bus START condition in UI2C_PROTCTL register.
 */
#define UI2C_START(ui2c) ((ui2c)->PROTCTL = ((ui2c)->PROTCTL & ~UI2C_PROTCTL_PTRG_Msk) | UI2C_PROTCTL_STA_Msk)

/**
 *    @brief        This macro only set STOP bit to the control register of USCI_I2C module
 *
 *    @param[in]    ui2c      The pointer of the specified USCI_I2C module.
 *
 *    @return       None
 *
 *    @details      Set the USCI_I2C bus STOP condition in UI2C_PROTCTL register.
 */
#define UI2C_STOP(ui2c) ((ui2c)->PROTCTL = ((ui2c)->PROTCTL & ~0x2E) | (UI2C_PROTCTL_PTRG_Msk | UI2C_PROTCTL_STO_Msk))

/**
 *    @brief        This macro returns the data stored in data register of USCI_I2C module
 *
 *    @param[in]    ui2c      The pointer of the specified USCI_I2C module.
 *
 *    @return       Data
 *
 *    @details      Read a byte data value of UI2C_RXDAT register from USCI_I2C bus
 */
#define UI2C_GET_DATA(ui2c) ((ui2c)->RXDAT)

/**
 *    @brief        This macro writes the data to data register of USCI_I2C module
 *
 *    @param[in]    ui2c     The pointer of the specified USCI_I2C module.
 *    @param[in]    u8Data   The data which will be written to data register of USCI_I2C module.
 *
 *    @return       None
 *
 *    @details      Write a byte data value of UI2C_TXDAT register, then sends address or data to USCI I2C bus
 */
#define UI2C_SET_DATA(ui2c, u8Data) ((ui2c)->TXDAT = (u8Data))

/**
 *    @brief        This macro returns time-out flag
 *
 *    @param[in]    ui2c     The pointer of the specified USCI_I2C module.
 *
 *    @retval       0        USCI_I2C bus time-out is not happened
 *    @retval       1        USCI_I2C bus time-out is happened
 *
 *    @details      USCI_I2C bus occurs time-out event, the time-out flag will be set. If not occurs time-out event, this bit is cleared.
 */
#define UI2C_GET_TIMEOUT_FLAG(ui2c) (((ui2c)->PROTSTS & UI2C_PROTSTS_TOIF_Msk) == UI2C_PROTSTS_TOIF_Msk ? 1:0)

/**
 *    @brief        This macro returns wake-up flag
 *
 *    @param[in]    ui2c     The pointer of the specified USCI_I2C module.
 *
 *    @retval       0        Chip is not woken-up from power-down mode
 *    @retval       1        Chip is woken-up from power-down mode
 *
 *    @details      USCI_I2C controller wake-up flag will be set when USCI_I2C bus occurs wake-up from deep-sleep.
 */
#define UI2C_GET_WAKEUP_FLAG(ui2c) (((ui2c)->WKSTS & UI2C_WKSTS_WKF_Msk) == UI2C_WKSTS_WKF_Msk ? 1:0)

/**
 *    @brief        This macro is used to clear USCI_I2C wake-up flag
 *
 *    @param[in]    ui2c     The pointer of the specified USCI_I2C module.
 *
 *    @return       None
 *
 *    @details      If USCI_I2C wake-up flag is set, use this macro to clear it.
 */
#define UI2C_CLR_WAKEUP_FLAG(ui2c)  ((ui2c)->WKSTS = UI2C_WKSTS_WKF_Msk)

/**
 *    @brief        This macro disables the USCI_I2C 10-bit address mode
 *
 *    @param[in]    ui2c     The pointer of the specified USCI_I2C module.
 *
 *    @return       None
 *
 *    @details      The UI2C_I2C is 7-bit address mode, when disable USCI_I2C 10-bit address match function.
 */
#define UI2C_DISABLE_10BIT_ADDR_MODE(ui2c)  ((ui2c)->PROTCTL &= ~(UI2C_PROTCTL_ADDR10EN_Msk))

/**
 *    @brief        This macro enables the 10-bit address mode
 *
 *    @param[in]    ui2c     The pointer of the specified USCI_I2C module.
 *
 *    @return       None
 *
 *    @details      To enable USCI_I2C 10-bit address match function.
 */
#define UI2C_ENABLE_10BIT_ADDR_MODE(ui2c)  ((ui2c)->PROTCTL |= UI2C_PROTCTL_ADDR10EN_Msk)

/**
 *    @brief        This macro gets USCI_I2C protocol interrupt flag or bus status
 *
 *    @param[in]    ui2c     The pointer of the specified USCI_I2C module.
 *
 *    @return       A word data of USCI_I2C_PROTSTS register
 *
 *    @details      Read a word data of USCI_I2C PROTSTS register to get USCI_I2C bus Interrupt flags or status.
 */
#define UI2C_GET_PROT_STATUS(ui2c)    ((ui2c)->PROTSTS)

/**
 *    @brief        This macro clears specified protocol interrupt flag
 *    @param[in]    ui2c     The pointer of the specified USCI_I2C module.
 *    @param[in]    u32IntTypeFlag Interrupt Type Flag, should be
 *                                  - \ref UI2C_PROTSTS_ACKIF_Msk
 *                                  - \ref UI2C_PROTSTS_ERRIF_Msk
 *                                  - \ref UI2C_PROTSTS_ARBLOIF_Msk
 *                                  - \ref UI2C_PROTSTS_NACKIF_Msk
 *                                  - \ref UI2C_PROTSTS_STORIF_Msk
 *                                  - \ref UI2C_PROTSTS_STARIF_Msk
 *                                  - \ref UI2C_PROTSTS_TOIF_Msk
 *    @return None
 *
 *    @details      To clear interrupt flag when USCI_I2C occurs interrupt and set interrupt flag.
 */
#define UI2C_CLR_PROT_INT_FLAG(ui2c,u32IntTypeFlag)    ((ui2c)->PROTSTS = (u32IntTypeFlag))

/**
 *    @brief        This macro enables specified protocol interrupt
 *    @param[in]    ui2c     The pointer of the specified USCI_I2C module.
 *    @param[in]    u32IntSel Interrupt Type, should be
 *                                  - \ref UI2C_PROTIEN_ACKIEN_Msk
 *                                  - \ref UI2C_PROTIEN_ERRIEN_Msk
 *                                  - \ref UI2C_PROTIEN_ARBLOIEN_Msk
 *                                  - \ref UI2C_PROTIEN_NACKIEN_Msk
 *                                  - \ref UI2C_PROTIEN_STORIEN_Msk
 *                                  - \ref UI2C_PROTIEN_STARIEN_Msk
 *                                  - \ref UI2C_PROTIEN_TOIEN_Msk
 *    @return None
 *
 *    @details      Set specified USCI_I2C protocol interrupt bits to enable interrupt function.
 */
#define UI2C_ENABLE_PROT_INT(ui2c, u32IntSel)    ((ui2c)->PROTIEN |= (u32IntSel))

/**
 *    @brief        This macro disables specified protocol interrupt
 *    @param[in]    ui2c     The pointer of the specified USCI_I2C module.
 *    @param[in]    u32IntSel Interrupt Type, should be
 *                                  - \ref UI2C_PROTIEN_ACKIEN_Msk
 *                                  - \ref UI2C_PROTIEN_ERRIEN_Msk
 *                                  - \ref UI2C_PROTIEN_ARBLOIEN_Msk
 *                                  - \ref UI2C_PROTIEN_NACKIEN_Msk
 *                                  - \ref UI2C_PROTIEN_STORIEN_Msk
 *                                  - \ref UI2C_PROTIEN_STARIEN_Msk
 *                                  - \ref UI2C_PROTIEN_TOIEN_Msk
 *    @return None
 *
 *    @details      Clear specified USCI_I2C protocol interrupt bits to disable interrupt funtion.
 */
#define UI2C_DISABLE_PROT_INT(ui2c, u32IntSel)    ((ui2c)->PROTIEN &= ~ (u32IntSel))


uint32_t UI2C_Open(UI2C_T *ui2c, uint32_t u32BusClock);
void UI2C_Close(UI2C_T *ui2c);
void UI2C_ClearTimeoutFlag(UI2C_T *ui2c);
void UI2C_Trigger(UI2C_T *ui2c, uint8_t u8Start, uint8_t u8Stop, uint8_t u8Ptrg, uint8_t u8Ack);
void UI2C_DisableInt(UI2C_T *ui2c, uint32_t u32Mask);
void UI2C_EnableInt(UI2C_T *ui2c, uint32_t u32Mask);
uint32_t UI2C_GetBusClockFreq(UI2C_T *ui2c);
uint32_t UI2C_SetBusClockFreq(UI2C_T *ui2c, uint32_t u32BusClock);
uint32_t UI2C_GetIntFlag(UI2C_T *ui2c, uint32_t u32Mask);
void UI2C_ClearIntFlag(UI2C_T* ui2c, uint32_t u32Mask);
uint32_t UI2C_GetData(UI2C_T *ui2c);
void UI2C_SetData(UI2C_T *ui2c, uint8_t u8Data);
void UI2C_SetSlaveAddr(UI2C_T *ui2c, uint8_t u8SlaveNo, uint16_t u16SlaveAddr, uint8_t u8GCMode);
void UI2C_SetSlaveAddrMask(UI2C_T *ui2c, uint8_t u8SlaveNo, uint16_t u16SlaveAddrMask);
void UI2C_EnableTimeout(UI2C_T *ui2c, uint32_t u32TimeoutCnt);
void UI2C_DisableTimeout(UI2C_T *ui2c);
void UI2C_EnableWakeup(UI2C_T *ui2c, uint8_t u8WakeupMode);
void UI2C_DisableWakeup(UI2C_T *ui2c);
uint8_t UI2C_WriteByte(UI2C_T *ui2c, uint8_t u8SlaveAddr, uint8_t data);
uint32_t UI2C_WriteMultiBytes(UI2C_T *ui2c, uint8_t u8SlaveAddr, uint8_t data[], uint32_t u32wLen);
uint8_t UI2C_WriteByteOneReg(UI2C_T *ui2c, uint8_t u8SlaveAddr, uint8_t u8DataAddr, uint8_t data);
uint32_t UI2C_WriteMultiBytesOneReg(UI2C_T *ui2c, uint8_t u8SlaveAddr, uint8_t u8DataAddr, uint8_t data[], uint32_t u32wLen);
uint8_t UI2C_WriteByteTwoRegs(UI2C_T *ui2c, uint8_t u8SlaveAddr, uint16_t u16DataAddr, uint8_t data);
uint32_t UI2C_WriteMultiBytesTwoRegs(UI2C_T *ui2c, uint8_t u8SlaveAddr, uint16_t u16DataAddr, uint8_t data[], uint32_t u32wLen);
uint8_t UI2C_ReadByte(UI2C_T *ui2c, uint8_t u8SlaveAddr);
uint32_t UI2C_ReadMultiBytes(UI2C_T *ui2c, uint8_t u8SlaveAddr, uint8_t rdata[], uint32_t u32rLen);
uint8_t UI2C_ReadByteOneReg(UI2C_T *ui2c, uint8_t u8SlaveAddr, uint8_t u8DataAddr);
uint32_t UI2C_ReadMultiBytesOneReg(UI2C_T *ui2c, uint8_t u8SlaveAddr, uint8_t u8DataAddr, uint8_t rdata[], uint32_t u32rLen);
uint8_t UI2C_ReadByteTwoRegs(UI2C_T *ui2c, uint8_t u8SlaveAddr, uint16_t u16DataAddr);
uint32_t UI2C_ReadMultiBytesTwoRegs(UI2C_T *ui2c, uint8_t u8SlaveAddr, uint16_t u16DataAddr, uint8_t rdata[], uint32_t u32rLen);
/**@}*/ /* end of group USCI_I2C_EXPORTED_FUNCTIONS */

/**@}*/ /* end of group USCI_I2C_Driver */

/**@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif

