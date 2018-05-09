/*
 * File      : lan8742a.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-25     LongfeiMa    transplantation driver of lan8742a
 */
#ifndef __LAN8742_H__
#define __LAN8742_H__

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "stm32h7xx_hal.h"

/* Basic Registers */
#define LAN8742_REG_BCR             0           /* Basic Control Register            */
#define LAN8742_REG_BSR             1           /* Basic Status Register             */

/* Extended Registers */
#define LAN8742_REG_PHYIDR1         2           /* PHY Identifier 1                  */
#define LAN8742_REG_PHYIDR2         3           /* PHY Identifier 2                  */
#define LAN8742_REG_ANAR            4           /* Auto-Negotiation Advertisement    */
#define LAN8742_REG_ANLPAR          5           /* Auto-Neg. Link Partner Ability    */
#define LAN8742_REG_ANER            6           /* Auto-Neg. Expansion Register      */
#define LAN8742_REG_ANEG_NP_TX      7           /* Auto-Neg. Next Page Tx            */
#define LAN8742_REG_ANEG_NP_RX      8           /* Auto-Neg. Next Page Rx            */
#define LAN8742_REG_MMD_ACCES_CTRL  13          /* MMD Access Control                */
#define LAN8742_REG_MMD_ACCES_AD    14          /* MMD Access Address/Data           */

/* Vendor-specific Registers */
#define LAN8742_REG_MCSR            17          /* Mode Control/Status Register      */
#define LAN8742_REG_SMR             18          /* Special Modes Register            */
#define LAN8742_REG_TDR_PAT_DEL     24          /* TDR Patterns/Delay Control Reg.   */
#define LAN8742_REG_TDR_CTRL_STAT   25          /* TDR Control/Status Register       */
#define LAN8742_REG_SEC             26          /* System Error Counter Register     */
#define LAN8742_REG_SC_SI           27          /* Specifal Control/Status Indication*/
#define LAN8742_REG_CABLE_LEN       28          /* Cable Length Register             */
#define LAN8742_REG_ISF             29          /* Interrupt Source Flag Register    */
#define LAN8742_REG_IM              30          /* Interrupt Mask Register           */
#define LAN8742_REG_PSCS            31          /* PHY Special Ctrl/Status Register  */

/* Basic Control Register */
#define LAN8742_BCR_RESET           0x8000      /* Software Reset                    */
#define LAN8742_BCR_LOOPBACK        0x4000      /* Loopback mode                     */
#define LAN8742_BCR_SPEED_SEL       0x2000      /* Speed Select (1=100Mb/s)          */
#define LAN8742_BCR_ANEG_EN         0x1000      /* Auto Negotiation Enable           */
#define LAN8742_BCR_POWER_DOWN      0x0800      /* Power Down (1=power down mode)    */
#define LAN8742_BCR_ISOLATE         0x0400      /* Isolate Media interface           */
#define LAN8742_BCR_REST_ANEG       0x0200      /* Restart Auto Negotiation          */
#define LAN8742_BCR_DUPLEX          0x0100      /* Duplex Mode (1=Full duplex)       */
#define LAN8742_BCR_COL_TEST        0x0080      /* Enable Collision Test             */

/* Basic Status Register */
#define LAN8742_BSR_100B_T4         0x8000      /* 100BASE-T4 Capable                */
#define LAN8742_BSR_100B_TX_FD      0x4000      /* 100BASE-TX Full Duplex Capable    */
#define LAN8742_BSR_100B_TX_HD      0x2000      /* 100BASE-TX Half Duplex Capable    */
#define LAN8742_BSR_10B_T_FD        0x1000      /* 10BASE-T Full Duplex Capable      */
#define LAN8742_BSR_10B_T_HD        0x0800      /* 10BASE-T Half Duplex Capable      */
#define LAN8742_BSR_100B_T2_FD      0x0400      /* 1000BASE-T2 Full Duplex Capable   */
#define LAN8742_BSR_100B_T2_HD      0x0200      /* 1000BASE-T2 Half Duplex Capable   */
#define LAN8742_BSR_EXTENDED_STAT   0x0100      /* Extended Status in register 15    */
#define LAN8742_BSR_ANEG_COMPL      0x0020      /* Auto Negotiation Complete         */
#define LAN8742_BSR_REM_FAULT       0x0010      /* Remote Fault                      */
#define LAN8742_BSR_ANEG_ABIL       0x0008      /* Auto Negotiation Ability          */
#define LAN8742_BSR_LINK_STAT       0x0004      /* Link Status (1=link us up)        */
#define LAN8742_BSR_JABBER_DET      0x0002      /* Jabber Detect                     */
#define LAN8742_BSR_EXT_CAPAB       0x0001      /* Extended Capabilities             */

/* PHY Identifier Registers */
#define LAN8742_PHY_ID1             0x0007      /* LAN8742 Device Identifier MSB    */
#define LAN8742_PHY_ID2             0xC130      /* LAN8742 Device Identifier LSB    */

/** @defgroup LAN8742_PHYSCSR_Bit_Definition LAN8742 PHYSCSR Bit Definition
  * @{
  */
#define LAN8742_PHYSCSR_AUTONEGO_DONE   ((uint16_t)0x1000U)
#define LAN8742_PHYSCSR_HCDSPEEDMASK    ((uint16_t)0x001CU)
#define LAN8742_PHYSCSR_10BT_HD         ((uint16_t)0x0004U)
#define LAN8742_PHYSCSR_10BT_FD         ((uint16_t)0x0014U)
#define LAN8742_PHYSCSR_100BTX_HD       ((uint16_t)0x0008U)
#define LAN8742_PHYSCSR_100BTX_FD       ((uint16_t)0x0018U) 



/* PHY Driver State Flags */
#define LAN8742_PHY_INIT              0x01U     /* Driver initialized                */
#define LAN8742_PHY_POWER             0x02U     /* Driver power is on                */


/** @defgroup LAN8742_SMR_Bit_Definition LAN8742 SMR Bit Definition
  * @{
  */
#define LAN8742_SMR_MODE       ((uint16_t)0x00E0U)
#define LAN8742_SMR_PHY_ADDR   ((uint16_t)0x001FU)


/** @defgroup LAN8742_IMR_ISFR_Bit_Definition LAN8742 IMR ISFR Bit Definition
  * @{
  */
#define LAN8742_INT_8       ((uint16_t)0x0100U)
#define LAN8742_INT_7       ((uint16_t)0x0080U)
#define LAN8742_INT_6       ((uint16_t)0x0040U)
#define LAN8742_INT_5       ((uint16_t)0x0020U)
#define LAN8742_INT_4       ((uint16_t)0x0010U)
#define LAN8742_INT_3       ((uint16_t)0x0008U)
#define LAN8742_INT_2       ((uint16_t)0x0004U)
#define LAN8742_INT_1       ((uint16_t)0x0002U)
#define LAN8742_INT_ALL     ((uint16_t)0x01FEU)

/** @defgroup LAN8742_Status LAN8742 Status
  * @{
  */    

#define  LAN8742_STATUS_READ_ERROR            ((int32_t)-5)
#define  LAN8742_STATUS_WRITE_ERROR           ((int32_t)-4)
#define  LAN8742_STATUS_ADDRESS_ERROR         ((int32_t)-3)
#define  LAN8742_STATUS_RESET_TIMEOUT         ((int32_t)-2)
#define  LAN8742_STATUS_ERROR                 ((int32_t)-1)
#define  LAN8742_STATUS_OK                    ((int32_t) 0)
#define  LAN8742_STATUS_LINK_DOWN             ((int32_t) 1)
#define  LAN8742_STATUS_100MBITS_FULLDUPLEX   ((int32_t) 2)
#define  LAN8742_STATUS_100MBITS_HALFDUPLEX   ((int32_t) 3)
#define  LAN8742_STATUS_10MBITS_FULLDUPLEX    ((int32_t) 4)
#define  LAN8742_STATUS_10MBITS_HALFDUPLEX    ((int32_t) 5)
#define  LAN8742_STATUS_AUTONEGO_NOTDONE      ((int32_t) 6)


/* Exported types ------------------------------------------------------------*/ 
/** @defgroup LAN8742_Exported_Types LAN8742 Exported Types
  * @{
  */
typedef int32_t  (*lan8742_Init_Func) (void); 
typedef int32_t  (*lan8742_DeInit_Func) (void);
typedef int32_t  (*lan8742_ReadReg_Func)   (uint32_t, uint32_t, uint32_t *);
typedef int32_t  (*lan8742_WriteReg_Func)  (uint32_t, uint32_t, uint32_t);
typedef int32_t  (*lan8742_GetTick_Func)  (void);

typedef struct 
{                   
  lan8742_Init_Func      Init; 
  lan8742_DeInit_Func    DeInit;
  lan8742_WriteReg_Func  WriteReg;
  lan8742_ReadReg_Func   ReadReg; 
  lan8742_GetTick_Func   GetTick;   
} lan8742_IOCtx_t;  


typedef struct 
{
  uint32_t            DevAddr;
  uint32_t            Is_Initialized;
  lan8742_IOCtx_t     IO;
  void               *pData;
}lan8742_Object_t;


extern ETH_HandleTypeDef EthHandle;

int rt_hw_lan8742a_init(void);

#endif /* __PHY_LAN8742_H */
