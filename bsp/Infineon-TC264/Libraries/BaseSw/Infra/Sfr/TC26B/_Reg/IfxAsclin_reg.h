/**
 * \file IfxAsclin_reg.h
 * \brief
 * \copyright Copyright (c) 2015 Infineon Technologies AG. All rights reserved.
 *
 * Version: TC26XB_UM_V1.2.R0
 * Specification: tc26xB_um_v1.2_MCSFR.xml (Revision: UM_V1.2)
 * MAY BE CHANGED BY USER [yes/no]: No
 *
 *                                 IMPORTANT NOTICE
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * \defgroup IfxLld_Asclin_Cfg Asclin address
 * \ingroup IfxLld_Asclin
 * 
 * \defgroup IfxLld_Asclin_Cfg_BaseAddress Base address
 * \ingroup IfxLld_Asclin_Cfg
 * 
 * \defgroup IfxLld_Asclin_Cfg_Asclin0 2-ASCLIN0
 * \ingroup IfxLld_Asclin_Cfg
 * 
 * \defgroup IfxLld_Asclin_Cfg_Asclin1 2-ASCLIN1
 * \ingroup IfxLld_Asclin_Cfg
 * 
 * \defgroup IfxLld_Asclin_Cfg_Asclin2 2-ASCLIN2
 * \ingroup IfxLld_Asclin_Cfg
 * 
 * \defgroup IfxLld_Asclin_Cfg_Asclin3 2-ASCLIN3
 * \ingroup IfxLld_Asclin_Cfg
 * 
 */
#ifndef IFXASCLIN_REG_H
#define IFXASCLIN_REG_H 1
/******************************************************************************/
#include "IfxAsclin_regdef.h"
/******************************************************************************/
/** \addtogroup IfxLld_Asclin_Cfg_BaseAddress
 * \{  */

/** \brief  ASCLIN object */
#define MODULE_ASCLIN0 /*lint --e(923)*/ (*(Ifx_ASCLIN*)0xF0000600u)

/** \brief  ASCLIN object */
#define MODULE_ASCLIN1 /*lint --e(923)*/ (*(Ifx_ASCLIN*)0xF0000700u)

/** \brief  ASCLIN object */
#define MODULE_ASCLIN2 /*lint --e(923)*/ (*(Ifx_ASCLIN*)0xF0000800u)

/** \brief  ASCLIN object */
#define MODULE_ASCLIN3 /*lint --e(923)*/ (*(Ifx_ASCLIN*)0xF0000900u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Asclin_Cfg_Asclin0
 * \{  */

/** \brief  FC, Access Enable Register 0 */
#define ASCLIN0_ACCEN0 /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_ACCEN0*)0xF00006FCu)

/** \brief  F8, Access Enable Register 1 */
#define ASCLIN0_ACCEN1 /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_ACCEN1*)0xF00006F8u)

/** \brief  14, Bit Configuration Register */
#define ASCLIN0_BITCON /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_BITCON*)0xF0000614u)

/** \brief  24, Baud Rate Detection Register */
#define ASCLIN0_BRD /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_BRD*)0xF0000624u)

/** \brief  20, Baud Rate Generation Register */
#define ASCLIN0_BRG /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_BRG*)0xF0000620u)

/** \brief  0, Clock Control Register */
#define ASCLIN0_CLC /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_CLC*)0xF0000600u)

/** \brief  4C, Clock Selection Register */
#define ASCLIN0_CSR /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_CSR*)0xF000064Cu)

/** \brief  1C, Data Configuration Register */
#define ASCLIN0_DATCON /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_DATCON*)0xF000061Cu)

/** \brief  34, Flags Register */
#define ASCLIN0_FLAGS /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_FLAGS*)0xF0000634u)

/** \brief  3C, Flags Clear Register */
#define ASCLIN0_FLAGSCLEAR /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_FLAGSCLEAR*)0xF000063Cu)

/** \brief  40, Flags Enable Register */
#define ASCLIN0_FLAGSENABLE /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_FLAGSENABLE*)0xF0000640u)

/** \brief  38, Flags Set Register */
#define ASCLIN0_FLAGSSET /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_FLAGSSET*)0xF0000638u)

/** \brief  18, Frame Control Register */
#define ASCLIN0_FRAMECON /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_FRAMECON*)0xF0000618u)

/** \brief  8, Module Identification Register */
#define ASCLIN0_ID /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_ID*)0xF0000608u)

/** \brief  4, Input and Output Control Register */
#define ASCLIN0_IOCR /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_IOCR*)0xF0000604u)

/** \brief  F4, Kernel Reset Register 0 */
#define ASCLIN0_KRST0 /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_KRST0*)0xF00006F4u)

/** \brief  F0, Kernel Reset Register 1 */
#define ASCLIN0_KRST1 /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_KRST1*)0xF00006F0u)

/** \brief  EC, Kernel Reset Status Clear Register */
#define ASCLIN0_KRSTCLR /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_KRSTCLR*)0xF00006ECu)

/** \brief  2C, LIN Break Timer Register */
#define ASCLIN0_LIN_BTIMER /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_LIN_BTIMER*)0xF000062Cu)

/** Alias (User Manual Name) for ASCLIN0_LIN_BTIMER.
* To use register names with standard convension, please use ASCLIN0_LIN_BTIMER.
*/
#define	ASCLIN0_LINBTIMER	(ASCLIN0_LIN_BTIMER)

/** \brief  28, LIN Control Register */
#define ASCLIN0_LIN_CON /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_LIN_CON*)0xF0000628u)

/** Alias (User Manual Name) for ASCLIN0_LIN_CON.
* To use register names with standard convension, please use ASCLIN0_LIN_CON.
*/
#define	ASCLIN0_LINCON	(ASCLIN0_LIN_CON)

/** \brief  30, LIN Header Timer Register */
#define ASCLIN0_LIN_HTIMER /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_LIN_HTIMER*)0xF0000630u)

/** Alias (User Manual Name) for ASCLIN0_LIN_HTIMER.
* To use register names with standard convension, please use ASCLIN0_LIN_HTIMER.
*/
#define	ASCLIN0_LINHTIMER	(ASCLIN0_LIN_HTIMER)

/** \brief  E8, OCDS Control and Status */
#define ASCLIN0_OCS /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_OCS*)0xF00006E8u)

/** \brief  48, Receive Data Register */
#define ASCLIN0_RXDATA /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_RXDATA*)0xF0000648u)

/** \brief  50, Receive Data Debug Register */
#define ASCLIN0_RXDATAD /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_RXDATAD*)0xF0000650u)

/** \brief  10, RX FIFO Configuration Register */
#define ASCLIN0_RXFIFOCON /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_RXFIFOCON*)0xF0000610u)

/** \brief  44, Transmit Data Register */
#define ASCLIN0_TXDATA /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_TXDATA*)0xF0000644u)

/** \brief  C, TX FIFO Configuration Register */
#define ASCLIN0_TXFIFOCON /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_TXFIFOCON*)0xF000060Cu)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Asclin_Cfg_Asclin1
 * \{  */

/** \brief  FC, Access Enable Register 0 */
#define ASCLIN1_ACCEN0 /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_ACCEN0*)0xF00007FCu)

/** \brief  F8, Access Enable Register 1 */
#define ASCLIN1_ACCEN1 /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_ACCEN1*)0xF00007F8u)

/** \brief  14, Bit Configuration Register */
#define ASCLIN1_BITCON /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_BITCON*)0xF0000714u)

/** \brief  24, Baud Rate Detection Register */
#define ASCLIN1_BRD /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_BRD*)0xF0000724u)

/** \brief  20, Baud Rate Generation Register */
#define ASCLIN1_BRG /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_BRG*)0xF0000720u)

/** \brief  0, Clock Control Register */
#define ASCLIN1_CLC /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_CLC*)0xF0000700u)

/** \brief  4C, Clock Selection Register */
#define ASCLIN1_CSR /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_CSR*)0xF000074Cu)

/** \brief  1C, Data Configuration Register */
#define ASCLIN1_DATCON /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_DATCON*)0xF000071Cu)

/** \brief  34, Flags Register */
#define ASCLIN1_FLAGS /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_FLAGS*)0xF0000734u)

/** \brief  3C, Flags Clear Register */
#define ASCLIN1_FLAGSCLEAR /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_FLAGSCLEAR*)0xF000073Cu)

/** \brief  40, Flags Enable Register */
#define ASCLIN1_FLAGSENABLE /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_FLAGSENABLE*)0xF0000740u)

/** \brief  38, Flags Set Register */
#define ASCLIN1_FLAGSSET /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_FLAGSSET*)0xF0000738u)

/** \brief  18, Frame Control Register */
#define ASCLIN1_FRAMECON /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_FRAMECON*)0xF0000718u)

/** \brief  8, Module Identification Register */
#define ASCLIN1_ID /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_ID*)0xF0000708u)

/** \brief  4, Input and Output Control Register */
#define ASCLIN1_IOCR /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_IOCR*)0xF0000704u)

/** \brief  F4, Kernel Reset Register 0 */
#define ASCLIN1_KRST0 /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_KRST0*)0xF00007F4u)

/** \brief  F0, Kernel Reset Register 1 */
#define ASCLIN1_KRST1 /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_KRST1*)0xF00007F0u)

/** \brief  EC, Kernel Reset Status Clear Register */
#define ASCLIN1_KRSTCLR /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_KRSTCLR*)0xF00007ECu)

/** \brief  2C, LIN Break Timer Register */
#define ASCLIN1_LIN_BTIMER /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_LIN_BTIMER*)0xF000072Cu)

/** Alias (User Manual Name) for ASCLIN1_LIN_BTIMER.
* To use register names with standard convension, please use ASCLIN1_LIN_BTIMER.
*/
#define	ASCLIN1_LINBTIMER	(ASCLIN1_LIN_BTIMER)

/** \brief  28, LIN Control Register */
#define ASCLIN1_LIN_CON /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_LIN_CON*)0xF0000728u)

/** Alias (User Manual Name) for ASCLIN1_LIN_CON.
* To use register names with standard convension, please use ASCLIN1_LIN_CON.
*/
#define	ASCLIN1_LINCON	(ASCLIN1_LIN_CON)

/** \brief  30, LIN Header Timer Register */
#define ASCLIN1_LIN_HTIMER /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_LIN_HTIMER*)0xF0000730u)

/** Alias (User Manual Name) for ASCLIN1_LIN_HTIMER.
* To use register names with standard convension, please use ASCLIN1_LIN_HTIMER.
*/
#define	ASCLIN1_LINHTIMER	(ASCLIN1_LIN_HTIMER)

/** \brief  E8, OCDS Control and Status */
#define ASCLIN1_OCS /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_OCS*)0xF00007E8u)

/** \brief  48, Receive Data Register */
#define ASCLIN1_RXDATA /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_RXDATA*)0xF0000748u)

/** \brief  50, Receive Data Debug Register */
#define ASCLIN1_RXDATAD /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_RXDATAD*)0xF0000750u)

/** \brief  10, RX FIFO Configuration Register */
#define ASCLIN1_RXFIFOCON /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_RXFIFOCON*)0xF0000710u)

/** \brief  44, Transmit Data Register */
#define ASCLIN1_TXDATA /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_TXDATA*)0xF0000744u)

/** \brief  C, TX FIFO Configuration Register */
#define ASCLIN1_TXFIFOCON /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_TXFIFOCON*)0xF000070Cu)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Asclin_Cfg_Asclin2
 * \{  */

/** \brief  FC, Access Enable Register 0 */
#define ASCLIN2_ACCEN0 /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_ACCEN0*)0xF00008FCu)

/** \brief  F8, Access Enable Register 1 */
#define ASCLIN2_ACCEN1 /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_ACCEN1*)0xF00008F8u)

/** \brief  14, Bit Configuration Register */
#define ASCLIN2_BITCON /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_BITCON*)0xF0000814u)

/** \brief  24, Baud Rate Detection Register */
#define ASCLIN2_BRD /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_BRD*)0xF0000824u)

/** \brief  20, Baud Rate Generation Register */
#define ASCLIN2_BRG /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_BRG*)0xF0000820u)

/** \brief  0, Clock Control Register */
#define ASCLIN2_CLC /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_CLC*)0xF0000800u)

/** \brief  4C, Clock Selection Register */
#define ASCLIN2_CSR /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_CSR*)0xF000084Cu)

/** \brief  1C, Data Configuration Register */
#define ASCLIN2_DATCON /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_DATCON*)0xF000081Cu)

/** \brief  34, Flags Register */
#define ASCLIN2_FLAGS /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_FLAGS*)0xF0000834u)

/** \brief  3C, Flags Clear Register */
#define ASCLIN2_FLAGSCLEAR /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_FLAGSCLEAR*)0xF000083Cu)

/** \brief  40, Flags Enable Register */
#define ASCLIN2_FLAGSENABLE /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_FLAGSENABLE*)0xF0000840u)

/** \brief  38, Flags Set Register */
#define ASCLIN2_FLAGSSET /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_FLAGSSET*)0xF0000838u)

/** \brief  18, Frame Control Register */
#define ASCLIN2_FRAMECON /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_FRAMECON*)0xF0000818u)

/** \brief  8, Module Identification Register */
#define ASCLIN2_ID /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_ID*)0xF0000808u)

/** \brief  4, Input and Output Control Register */
#define ASCLIN2_IOCR /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_IOCR*)0xF0000804u)

/** \brief  F4, Kernel Reset Register 0 */
#define ASCLIN2_KRST0 /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_KRST0*)0xF00008F4u)

/** \brief  F0, Kernel Reset Register 1 */
#define ASCLIN2_KRST1 /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_KRST1*)0xF00008F0u)

/** \brief  EC, Kernel Reset Status Clear Register */
#define ASCLIN2_KRSTCLR /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_KRSTCLR*)0xF00008ECu)

/** \brief  2C, LIN Break Timer Register */
#define ASCLIN2_LIN_BTIMER /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_LIN_BTIMER*)0xF000082Cu)

/** Alias (User Manual Name) for ASCLIN2_LIN_BTIMER.
* To use register names with standard convension, please use ASCLIN2_LIN_BTIMER.
*/
#define	ASCLIN2_LINBTIMER	(ASCLIN2_LIN_BTIMER)

/** \brief  28, LIN Control Register */
#define ASCLIN2_LIN_CON /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_LIN_CON*)0xF0000828u)

/** Alias (User Manual Name) for ASCLIN2_LIN_CON.
* To use register names with standard convension, please use ASCLIN2_LIN_CON.
*/
#define	ASCLIN2_LINCON	(ASCLIN2_LIN_CON)

/** \brief  30, LIN Header Timer Register */
#define ASCLIN2_LIN_HTIMER /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_LIN_HTIMER*)0xF0000830u)

/** Alias (User Manual Name) for ASCLIN2_LIN_HTIMER.
* To use register names with standard convension, please use ASCLIN2_LIN_HTIMER.
*/
#define	ASCLIN2_LINHTIMER	(ASCLIN2_LIN_HTIMER)

/** \brief  E8, OCDS Control and Status */
#define ASCLIN2_OCS /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_OCS*)0xF00008E8u)

/** \brief  48, Receive Data Register */
#define ASCLIN2_RXDATA /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_RXDATA*)0xF0000848u)

/** \brief  50, Receive Data Debug Register */
#define ASCLIN2_RXDATAD /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_RXDATAD*)0xF0000850u)

/** \brief  10, RX FIFO Configuration Register */
#define ASCLIN2_RXFIFOCON /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_RXFIFOCON*)0xF0000810u)

/** \brief  44, Transmit Data Register */
#define ASCLIN2_TXDATA /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_TXDATA*)0xF0000844u)

/** \brief  C, TX FIFO Configuration Register */
#define ASCLIN2_TXFIFOCON /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_TXFIFOCON*)0xF000080Cu)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Asclin_Cfg_Asclin3
 * \{  */

/** \brief  FC, Access Enable Register 0 */
#define ASCLIN3_ACCEN0 /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_ACCEN0*)0xF00009FCu)

/** \brief  F8, Access Enable Register 1 */
#define ASCLIN3_ACCEN1 /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_ACCEN1*)0xF00009F8u)

/** \brief  14, Bit Configuration Register */
#define ASCLIN3_BITCON /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_BITCON*)0xF0000914u)

/** \brief  24, Baud Rate Detection Register */
#define ASCLIN3_BRD /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_BRD*)0xF0000924u)

/** \brief  20, Baud Rate Generation Register */
#define ASCLIN3_BRG /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_BRG*)0xF0000920u)

/** \brief  0, Clock Control Register */
#define ASCLIN3_CLC /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_CLC*)0xF0000900u)

/** \brief  4C, Clock Selection Register */
#define ASCLIN3_CSR /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_CSR*)0xF000094Cu)

/** \brief  1C, Data Configuration Register */
#define ASCLIN3_DATCON /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_DATCON*)0xF000091Cu)

/** \brief  34, Flags Register */
#define ASCLIN3_FLAGS /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_FLAGS*)0xF0000934u)

/** \brief  3C, Flags Clear Register */
#define ASCLIN3_FLAGSCLEAR /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_FLAGSCLEAR*)0xF000093Cu)

/** \brief  40, Flags Enable Register */
#define ASCLIN3_FLAGSENABLE /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_FLAGSENABLE*)0xF0000940u)

/** \brief  38, Flags Set Register */
#define ASCLIN3_FLAGSSET /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_FLAGSSET*)0xF0000938u)

/** \brief  18, Frame Control Register */
#define ASCLIN3_FRAMECON /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_FRAMECON*)0xF0000918u)

/** \brief  8, Module Identification Register */
#define ASCLIN3_ID /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_ID*)0xF0000908u)

/** \brief  4, Input and Output Control Register */
#define ASCLIN3_IOCR /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_IOCR*)0xF0000904u)

/** \brief  F4, Kernel Reset Register 0 */
#define ASCLIN3_KRST0 /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_KRST0*)0xF00009F4u)

/** \brief  F0, Kernel Reset Register 1 */
#define ASCLIN3_KRST1 /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_KRST1*)0xF00009F0u)

/** \brief  EC, Kernel Reset Status Clear Register */
#define ASCLIN3_KRSTCLR /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_KRSTCLR*)0xF00009ECu)

/** \brief  2C, LIN Break Timer Register */
#define ASCLIN3_LIN_BTIMER /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_LIN_BTIMER*)0xF000092Cu)

/** Alias (User Manual Name) for ASCLIN3_LIN_BTIMER.
* To use register names with standard convension, please use ASCLIN3_LIN_BTIMER.
*/
#define	ASCLIN3_LINBTIMER	(ASCLIN3_LIN_BTIMER)

/** \brief  28, LIN Control Register */
#define ASCLIN3_LIN_CON /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_LIN_CON*)0xF0000928u)

/** Alias (User Manual Name) for ASCLIN3_LIN_CON.
* To use register names with standard convension, please use ASCLIN3_LIN_CON.
*/
#define	ASCLIN3_LINCON	(ASCLIN3_LIN_CON)

/** \brief  30, LIN Header Timer Register */
#define ASCLIN3_LIN_HTIMER /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_LIN_HTIMER*)0xF0000930u)

/** Alias (User Manual Name) for ASCLIN3_LIN_HTIMER.
* To use register names with standard convension, please use ASCLIN3_LIN_HTIMER.
*/
#define	ASCLIN3_LINHTIMER	(ASCLIN3_LIN_HTIMER)

/** \brief  E8, OCDS Control and Status */
#define ASCLIN3_OCS /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_OCS*)0xF00009E8u)

/** \brief  48, Receive Data Register */
#define ASCLIN3_RXDATA /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_RXDATA*)0xF0000948u)

/** \brief  50, Receive Data Debug Register */
#define ASCLIN3_RXDATAD /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_RXDATAD*)0xF0000950u)

/** \brief  10, RX FIFO Configuration Register */
#define ASCLIN3_RXFIFOCON /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_RXFIFOCON*)0xF0000910u)

/** \brief  44, Transmit Data Register */
#define ASCLIN3_TXDATA /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_TXDATA*)0xF0000944u)

/** \brief  C, TX FIFO Configuration Register */
#define ASCLIN3_TXFIFOCON /*lint --e(923)*/ (*(volatile Ifx_ASCLIN_TXFIFOCON*)0xF000090Cu)
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXASCLIN_REG_H */
