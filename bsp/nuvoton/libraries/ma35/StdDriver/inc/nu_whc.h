/**************************************************************************//**
 * @file     nu_whc.h
 * @brief    WHC driver header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NU_WHC_H__
#define __NU_WHC_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup WHC_Driver WHC Driver
  @{
*/

/** @addtogroup WHC_EXPORTED_CONSTANTS WHC Exported Constants
  @{
*/
#define WHC_CH              4ul /*!<WHC channel number \hideinitializer */
#define WHC_BUFFER_LEN      4ul /*!<WHC buffer size in unsigned int \hideinitializer */

#define WHC_RUN_MODE        0   /*!<Specific core is in normal run mode \hideinitializer */
#define WHC_POFF_MODE       1   /*!<Specific core is in power off mode \hideinitializer */
#define WHC_PD_MODE         2   /*!<Specific core is in power down mode \hideinitializer */

/*@}*/ /* end of group WHC_EXPORTED_CONSTANTS */


/** @addtogroup WHC_EXPORTED_FUNCTIONS WHC Exported Functions
  @{
*/

/**
  * @brief      Recall message
  *
  * @param[in]  whc           The pointer of the specified WHC module.
  * @param[in]  u32Ch         WHC channel, valid channel numbers are 0~3
  * \hideinitializer
  */
#define WHC_RECALL_MSG(whc, u32Ch)          ((whc)->TXCTL |= (1ul << (u32Ch + WHC_TXCTL_CH0RC_Pos)))

/**
  * @brief
  *
  * @param[in]  whc           The pointer of the specified WHC module.
  * @param[in]  u32Ch         WHC channel, valid channel numbers are 0~3
  * \hideinitializer
  */
#define WHC_IS_TX_READY(whc, u32Ch)         ((whc)->TXSTS & (1 << u32Ch))

/**
  * @brief
  *
  * @param[in]  whc           The pointer of the specified WHC module.
  * @param[in]  u32Ch         WHC channel, valid channel numbers are 0~3
  * \hideinitializer
  */
#define WHC_IS_RX_READY(whc, u32Ch)         ((whc)->RXSTS & (1 << u32Ch))

/**
  *    @brief        Enable specified WHC interrupt
  *
  *    @param[in]    whc        The pointer of the specified WHC module
  *    @param[in]    u32IntSel  Interrupt type select
  *                              - \ref WHC_INTEN_RST0IEN_Msk
  *                              - \ref WHC_INTEN_POFF0IEN_Msk
  *                              - \ref WHC_INTEN_PD0IEN_Msk
  *                              - \ref WHC_INTEN_RST1IEN_Msk
  *                              - \ref WHC_INTEN_POFF1IEN_Msk
  *                              - \ref WHC_INTEN_PD1IEN_Msk
  *                              - \ref WHC_INTEN_GI0IEN_Msk
  *                              - \ref WHC_INTEN_GI1IEN_Msk
  *                              - \ref WHC_INTEN_GI2IEN_Msk
  *                              - \ref WHC_INTEN_GI3IEN_Msk
  *                              - \ref WHC_INTEN_TX0IEN_Msk
  *                              - \ref WHC_INTEN_TX1IEN_Msk
  *                              - \ref WHC_INTEN_TX2IEN_Msk
  *                              - \ref WHC_INTEN_TX3IEN_Msk
  *                              - \ref WHC_INTEN_RX0IEN_Msk
  *                              - \ref WHC_INTEN_RX1IEN_Msk
  *                              - \ref WHC_INTEN_RX2IEN_Msk
  *                              - \ref WHC_INTEN_RX3IEN_Msk
  *    \hideinitializer
  */
#define WHC_ENABLE_INT(whc, u32IntSel)    ((whc)->INTEN |= (u32IntSel))


/**
  *    @brief        Disable specified WHC interrupt
  *
  *    @param[in]    whc        The pointer of the specified WHC module
  *    @param[in]    u32IntSel  Interrupt type select
  *                              - \ref WHC_INTEN_RST0IEN_Msk
  *                              - \ref WHC_INTEN_POFF0IEN_Msk
  *                              - \ref WHC_INTEN_PD0IEN_Msk
  *                              - \ref WHC_INTEN_RST1IEN_Msk
  *                              - \ref WHC_INTEN_POFF1IEN_Msk
  *                              - \ref WHC_INTEN_PD1IEN_Msk
  *                              - \ref WHC_INTEN_GI0IEN_Msk
  *                              - \ref WHC_INTEN_GI1IEN_Msk
  *                              - \ref WHC_INTEN_GI2IEN_Msk
  *                              - \ref WHC_INTEN_GI3IEN_Msk
  *                              - \ref WHC_INTEN_TX0IEN_Msk
  *                              - \ref WHC_INTEN_TX1IEN_Msk
  *                              - \ref WHC_INTEN_TX2IEN_Msk
  *                              - \ref WHC_INTEN_TX3IEN_Msk
  *                              - \ref WHC_INTEN_RX0IEN_Msk
  *                              - \ref WHC_INTEN_RX1IEN_Msk
  *                              - \ref WHC_INTEN_RX2IEN_Msk
  *                              - \ref WHC_INTEN_RX3IEN_Msk
  *    \hideinitializer
  */
#define WHC_DISABLE_INT(whc, u32IntSel)    ((whc)->INTEN &= ~(u32IntSel))

/**
  *    @brief        Get specified interrupt flag
  *
  *    @param[in]    whc        The pointer of the specified WHC module
  *    @param[in]    u32IntTypeFlag Interrupt Type Flag, should be
  *                              - \ref WHC_INTSTS_RST0IF_Msk
  *                              - \ref WHC_INTSTS_POFF0IF_Msk
  *                              - \ref WHC_INTSTS_PD0IF_Msk
  *                              - \ref WHC_INTSTS_RST1IF_Msk
  *                              - \ref WHC_INTSTS_POFF1IF_Msk
  *                              - \ref WHC_INTSTS_PD1IF_Msk
  *                              - \ref WHC_INTSTS_GI0IF_Msk
  *                              - \ref WHC_INTSTS_GI1IF_Msk
  *                              - \ref WHC_INTSTS_GI2IF_Msk
  *                              - \ref WHC_INTSTS_GI3IF_Msk
  *                              - \ref WHC_INTSTS_TX0IF_Msk
  *                              - \ref WHC_INTSTS_TX1IF_Msk
  *                              - \ref WHC_INTSTS_TX2IF_Msk
  *                              - \ref WHC_INTSTS_TX3IF_Msk
  *                              - \ref WHC_INTSTS_RX0IF_Msk
  *                              - \ref WHC_INTSTS_RX1IF_Msk
  *                              - \ref WHC_INTSTS_RX2IF_Msk
  *                              - \ref WHC_INTSTS_RX3IF_Msk
  *
  *    @retval       0 The specified interrupt is not happened.
  *                  1 The specified interrupt is happened.
  *    \hideinitializer
  */
#define WHC_GET_INT_FLAG(whc, u32IntTypeFlag)    (((whc)->INTSTS & (u32IntTypeFlag))?1:0)

/**
  *    @brief        Clear specified interrupt flag
  *
  *    @param[in]    whc        The pointer of the specified WHC module
  *    @param[in]    u32IntTypeFlag Interrupt Type Flag, should be
  *                              - \ref WHC_INTSTS_RST0IF_Msk
  *                              - \ref WHC_INTSTS_POFF0IF_Msk
  *                              - \ref WHC_INTSTS_PD0IF_Msk
  *                              - \ref WHC_INTSTS_RST1IF_Msk
  *                              - \ref WHC_INTSTS_POFF1IF_Msk
  *                              - \ref WHC_INTSTS_PD1IF_Msk
  *                              - \ref WHC_INTSTS_GI0IF_Msk
  *                              - \ref WHC_INTSTS_GI1IF_Msk
  *                              - \ref WHC_INTSTS_GI2IF_Msk
  *                              - \ref WHC_INTSTS_GI3IF_Msk
  *                              - \ref WHC_INTSTS_TX0IF_Msk
  *                              - \ref WHC_INTSTS_TX1IF_Msk
  *                              - \ref WHC_INTSTS_TX2IF_Msk
  *                              - \ref WHC_INTSTS_TX3IF_Msk
  *                              - \ref WHC_INTSTS_RX0IF_Msk
  *                              - \ref WHC_INTSTS_RX1IF_Msk
  *                              - \ref WHC_INTSTS_RX2IF_Msk
  *                              - \ref WHC_INTSTS_RX3IF_Msk
  *    \hideinitializer
  */
#define WHC_CLR_INT_FLAG(whc, u32IntTypeFlag)    ((whc)->INTSTS = (u32IntTypeFlag))

/**
  *    @brief        Trigger WHC general event interrupt
  *    @param[in]    whc        The pointer of the specified WHC module
  *    @param[in]    u32IntNum  General event interrupt number, valid number are 0~3
  *
  *    \hideinitializer
  */
#define WHC_TRIGGER_GINT(whc, u32IntNum) ((whc)->GINTTRG = (1ul << u32IntNum))

/**
  *    @brief        Get counter part reset flag
  *    @param[in]    whc        The pointer of the specified WHC module
  *    @retval       The combination of WHC_CPSTS_WDTRF_Msk, WHC_CPSTS_SYSRF_Msk, and WHC_CPSTS_CPURF_Msk
  *
  *    \hideinitializer
  */
#define WHC_GET_RST_FLAG(whc) ((whc)->CPSTS & (WHC_CPSTS_WDTRF_Msk | WHC_CPSTS_SYSRF_Msk | WHC_CPSTS_CPURF_Msk))

/**
  *    @brief        Clear counter part reset flag
  *    @param[in]    whc        The pointer of the specified WHC module
  *
  *    \hideinitializer
  */
#define WHC_CLR_RST_FLAG(whc) ((whc)->CPSTS = (whc)->CPSTS)


/**
  *    @brief        Set wakeup up source
  *
  *    @param[in]    whc        The pointer of the specified WHC module
  *    @param[in]    u32WakeupSrc Wake up source. Should be the combination of:
  *                              - \ref WHC_WKCTL_RST0WKEN_Msk
  *                              - \ref WHC_WKCTL_POFF0WKEN_Msk
  *                              - \ref WHC_WKCTL_PD0WKEN_Msk
  *                              - \ref WHC_WKCTL_RST1WKEN_Msk
  *                              - \ref WHC_WKCTL_POFF1WKEN_Msk
  *                              - \ref WHC_WKCTL_PD1WKEN_Msk
  *                              - \ref WHC_WKCTL_GI0WKEN_Msk
  *                              - \ref WHC_WKCTL_GI1WKEN_Msk
  *                              - \ref WHC_WKCTL_GI2WKEN_Msk
  *                              - \ref WHC_WKCTL_GI3WKEN_Msk
  *                              - \ref WHC_WKCTL_TX0WKEN_Msk
  *                              - \ref WHC_WKCTL_TX1WKEN_Msk
  *                              - \ref WHC_WKCTL_TX2WKEN_Msk
  *                              - \ref WHC_WKCTL_TX3WKEN_Msk
  *                              - \ref WHC_WKCTL_RX0WKEN_Msk
  *                              - \ref WHC_WKCTL_RX1WKEN_Msk
  *                              - \ref WHC_WKCTL_RX2WKEN_Msk
  *                              - \ref WHC_WKCTL_RX3WKEN_Msk
  *    \hideinitializer
  */
#define WHC_SET_WAKEUP_SRC(whc,u32WakeFlag)    ((whc)->WKCTL |= (u32WakeFlag))


/**
  *    @brief        Clear wakeup up source
  *
  *    @param[in]    whc        The pointer of the specified WHC module
  *    @param[in]    u32WakeupSrc Wake up source. Should be the combination of:
  *                              - \ref WHC_WKCTL_RST0WKEN_Msk
  *                              - \ref WHC_WKCTL_POFF0WKEN_Msk
  *                              - \ref WHC_WKCTL_PD0WKEN_Msk
  *                              - \ref WHC_WKCTL_RST1WKEN_Msk
  *                              - \ref WHC_WKCTL_POFF1WKEN_Msk
  *                              - \ref WHC_WKCTL_PD1WKEN_Msk
  *                              - \ref WHC_WKCTL_GI0WKEN_Msk
  *                              - \ref WHC_WKCTL_GI1WKEN_Msk
  *                              - \ref WHC_WKCTL_GI2WKEN_Msk
  *                              - \ref WHC_WKCTL_GI3WKEN_Msk
  *                              - \ref WHC_WKCTL_TX0WKEN_Msk
  *                              - \ref WHC_WKCTL_TX1WKEN_Msk
  *                              - \ref WHC_WKCTL_TX2WKEN_Msk
  *                              - \ref WHC_WKCTL_TX3WKEN_Msk
  *                              - \ref WHC_WKCTL_RX0WKEN_Msk
  *                              - \ref WHC_WKCTL_RX1WKEN_Msk
  *                              - \ref WHC_WKCTL_RX2WKEN_Msk
  *                              - \ref WHC_WKCTL_RX3WKEN_Msk
  *    \hideinitializer
  */
#define WHC_CLR_WAKEUP_SRC(whc,u32WakeFlag)    ((whc)->WKCTL &= ~(u32WakeFlag))

int WHC_Send(WHC_T *whc, uint32_t u32Ch, uint32_t *pu32TxBuf);
int WHC_Recv(WHC_T *whc, uint32_t u32Ch, uint32_t *pu32RxBuf);
int WHC_GetCPSts(WHC_T *whc, uint32_t u32Core);


/*@}*/ /* end of group WHC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group WHC_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif

