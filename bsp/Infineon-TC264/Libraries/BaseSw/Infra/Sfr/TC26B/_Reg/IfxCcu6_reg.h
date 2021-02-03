/**
 * \file IfxCcu6_reg.h
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
 * \defgroup IfxLld_Ccu6_Cfg Ccu6 address
 * \ingroup IfxLld_Ccu6
 * 
 * \defgroup IfxLld_Ccu6_Cfg_BaseAddress Base address
 * \ingroup IfxLld_Ccu6_Cfg
 * 
 * \defgroup IfxLld_Ccu6_Cfg_Ccu60 2-CCU60
 * \ingroup IfxLld_Ccu6_Cfg
 * 
 * \defgroup IfxLld_Ccu6_Cfg_Ccu61 2-CCU61
 * \ingroup IfxLld_Ccu6_Cfg
 * 
 */
#ifndef IFXCCU6_REG_H
#define IFXCCU6_REG_H 1
/******************************************************************************/
#include "IfxCcu6_regdef.h"
/******************************************************************************/
/** \addtogroup IfxLld_Ccu6_Cfg_BaseAddress
 * \{  */

/** \brief  CCU6 object */
#define MODULE_CCU60 /*lint --e(923)*/ (*(Ifx_CCU6*)0xF0002A00u)

/** \brief  CCU6 object */
#define MODULE_CCU61 /*lint --e(923)*/ (*(Ifx_CCU6*)0xF0002B00u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Ccu6_Cfg_Ccu60
 * \{  */

/** \brief  FC, Access Enable Register 0 */
#define CCU60_ACCEN0 /*lint --e(923)*/ (*(volatile Ifx_CCU6_ACCEN0*)0xF0002AFCu)

/** \brief  F8, Access Enable Register 1 */
#define CCU60_ACCEN1 /*lint --e(923)*/ (*(volatile Ifx_CCU6_ACCEN1*)0xF0002AF8u)

/** \brief  30, Capture/Compare Register for Channel CC60 */
#define CCU60_CC60R /*lint --e(923)*/ (*(volatile Ifx_CCU6_CC60R*)0xF0002A30u)

/** \brief  40, Capture/Compare Shadow Reg. for Channel CC60 */
#define CCU60_CC60SR /*lint --e(923)*/ (*(volatile Ifx_CCU6_CC60SR*)0xF0002A40u)

/** \brief  34, Capture/Compare Register for Channel CC61 */
#define CCU60_CC61R /*lint --e(923)*/ (*(volatile Ifx_CCU6_CC61R*)0xF0002A34u)

/** \brief  44, Capture/Compare Shadow Reg. for Channel CC61 */
#define CCU60_CC61SR /*lint --e(923)*/ (*(volatile Ifx_CCU6_CC61SR*)0xF0002A44u)

/** \brief  38, Capture/Compare Register for Channel CC62 */
#define CCU60_CC62R /*lint --e(923)*/ (*(volatile Ifx_CCU6_CC62R*)0xF0002A38u)

/** \brief  48, Capture/Compare Shadow Reg. for Channel CC62 */
#define CCU60_CC62SR /*lint --e(923)*/ (*(volatile Ifx_CCU6_CC62SR*)0xF0002A48u)

/** \brief  58, Compare Register for T13 */
#define CCU60_CC63R /*lint --e(923)*/ (*(volatile Ifx_CCU6_CC63R*)0xF0002A58u)

/** \brief  5C, Compare Shadow Register for T13 */
#define CCU60_CC63SR /*lint --e(923)*/ (*(volatile Ifx_CCU6_CC63SR*)0xF0002A5Cu)

/** \brief  0, Clock Control Register */
#define CCU60_CLC /*lint --e(923)*/ (*(volatile Ifx_CCU6_CLC*)0xF0002A00u)

/** \brief  64, Compare State Modification Register */
#define CCU60_CMPMODIF /*lint --e(923)*/ (*(volatile Ifx_CCU6_CMPMODIF*)0xF0002A64u)

/** \brief  60, Compare State Register */
#define CCU60_CMPSTAT /*lint --e(923)*/ (*(volatile Ifx_CCU6_CMPSTAT*)0xF0002A60u)

/** \brief  8, Module Identification Register */
#define CCU60_ID /*lint --e(923)*/ (*(volatile Ifx_CCU6_ID*)0xF0002A08u)

/** \brief  B0, Interrupt Enable Register */
#define CCU60_IEN /*lint --e(923)*/ (*(volatile Ifx_CCU6_IEN*)0xF0002AB0u)

/** \brief  98, Input Monitoring Register */
#define CCU60_IMON /*lint --e(923)*/ (*(volatile Ifx_CCU6_IMON*)0xF0002A98u)

/** \brief  AC, Interrupt Node Pointer Register */
#define CCU60_INP /*lint --e(923)*/ (*(volatile Ifx_CCU6_INP*)0xF0002AACu)

/** \brief  A0, Interrupt Status Register */
#define CCU60_IS /*lint --e(923)*/ (*(volatile Ifx_CCU6_IS*)0xF0002AA0u)

/** \brief  A8, Interrupt Status Reset Register */
#define CCU60_ISR /*lint --e(923)*/ (*(volatile Ifx_CCU6_ISR*)0xF0002AA8u)

/** \brief  A4, Interrupt Status Set Register */
#define CCU60_ISS /*lint --e(923)*/ (*(volatile Ifx_CCU6_ISS*)0xF0002AA4u)

/** \brief  F4, Kernel Reset Register 0 */
#define CCU60_KRST0 /*lint --e(923)*/ (*(volatile Ifx_CCU6_KRST0*)0xF0002AF4u)

/** \brief  F0, Kernel Reset Register 1 */
#define CCU60_KRST1 /*lint --e(923)*/ (*(volatile Ifx_CCU6_KRST1*)0xF0002AF0u)

/** \brief  EC, Kernel Reset Status Clear Register */
#define CCU60_KRSTCLR /*lint --e(923)*/ (*(volatile Ifx_CCU6_KRSTCLR*)0xF0002AECu)

/** \brief  1C, Kernel State Control Sensitivity Register */
#define CCU60_KSCSR /*lint --e(923)*/ (*(volatile Ifx_CCU6_KSCSR*)0xF0002A1Cu)

/** \brief  9C, Lost Indicator Register */
#define CCU60_LI /*lint --e(923)*/ (*(volatile Ifx_CCU6_LI*)0xF0002A9Cu)

/** \brief  4, Module Configuration Register */
#define CCU60_MCFG /*lint --e(923)*/ (*(volatile Ifx_CCU6_MCFG*)0xF0002A04u)

/** \brief  94, Multi-Channel Mode Control Register */
#define CCU60_MCMCTR /*lint --e(923)*/ (*(volatile Ifx_CCU6_MCMCTR*)0xF0002A94u)

/** \brief  90, Multi-Channel Mode Output Register */
#define CCU60_MCMOUT /*lint --e(923)*/ (*(volatile Ifx_CCU6_MCMOUT*)0xF0002A90u)

/** \brief  8C, Multi-Channel Mode Output Shadow Register */
#define CCU60_MCMOUTS /*lint --e(923)*/ (*(volatile Ifx_CCU6_MCMOUTS*)0xF0002A8Cu)

/** \brief  80, Modulation Control Register */
#define CCU60_MODCTR /*lint --e(923)*/ (*(volatile Ifx_CCU6_MODCTR*)0xF0002A80u)

/** \brief  C, CCU60 Module Output Select Register */
#define CCU60_MOSEL /*lint --e(923)*/ (*(volatile Ifx_CCU6_MOSEL*)0xF0002A0Cu)

/** \brief  E8, OCDS Control and Status Register */
#define CCU60_OCS /*lint --e(923)*/ (*(volatile Ifx_CCU6_OCS*)0xF0002AE8u)

/** \brief  10, Port Input Select Register 0 */
#define CCU60_PISEL0 /*lint --e(923)*/ (*(volatile Ifx_CCU6_PISEL0*)0xF0002A10u)

/** \brief  14, Port Input Select Register 2 */
#define CCU60_PISEL2 /*lint --e(923)*/ (*(volatile Ifx_CCU6_PISEL2*)0xF0002A14u)

/** \brief  88, Passive State Level Register */
#define CCU60_PSLR /*lint --e(923)*/ (*(volatile Ifx_CCU6_PSLR*)0xF0002A88u)

/** \brief  20, Timer T12 Counter Register */
#define CCU60_T12 /*lint --e(923)*/ (*(volatile Ifx_CCU6_T12*)0xF0002A20u)

/** \brief  28, Dead-Time Control Register for Timer12 */
#define CCU60_T12DTC /*lint --e(923)*/ (*(volatile Ifx_CCU6_T12DTC*)0xF0002A28u)

/** \brief  68, T12 Mode Select Register */
#define CCU60_T12MSEL /*lint --e(923)*/ (*(volatile Ifx_CCU6_T12MSEL*)0xF0002A68u)

/** \brief  24, Timer 12 Period Register */
#define CCU60_T12PR /*lint --e(923)*/ (*(volatile Ifx_CCU6_T12PR*)0xF0002A24u)

/** \brief  50, Timer T13 Counter Register */
#define CCU60_T13 /*lint --e(923)*/ (*(volatile Ifx_CCU6_T13*)0xF0002A50u)

/** \brief  54, Timer 13 Period Register */
#define CCU60_T13PR /*lint --e(923)*/ (*(volatile Ifx_CCU6_T13PR*)0xF0002A54u)

/** \brief  70, Timer Control Register 0 */
#define CCU60_TCTR0 /*lint --e(923)*/ (*(volatile Ifx_CCU6_TCTR0*)0xF0002A70u)

/** \brief  74, Timer Control Register 2 */
#define CCU60_TCTR2 /*lint --e(923)*/ (*(volatile Ifx_CCU6_TCTR2*)0xF0002A74u)

/** \brief  78, Timer Control Register 4 */
#define CCU60_TCTR4 /*lint --e(923)*/ (*(volatile Ifx_CCU6_TCTR4*)0xF0002A78u)

/** \brief  84, Trap Control Register */
#define CCU60_TRPCTR /*lint --e(923)*/ (*(volatile Ifx_CCU6_TRPCTR*)0xF0002A84u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Ccu6_Cfg_Ccu61
 * \{  */

/** \brief  FC, Access Enable Register 0 */
#define CCU61_ACCEN0 /*lint --e(923)*/ (*(volatile Ifx_CCU6_ACCEN0*)0xF0002BFCu)

/** \brief  F8, Access Enable Register 1 */
#define CCU61_ACCEN1 /*lint --e(923)*/ (*(volatile Ifx_CCU6_ACCEN1*)0xF0002BF8u)

/** \brief  30, Capture/Compare Register for Channel CC60 */
#define CCU61_CC60R /*lint --e(923)*/ (*(volatile Ifx_CCU6_CC60R*)0xF0002B30u)

/** \brief  40, Capture/Compare Shadow Reg. for Channel CC60 */
#define CCU61_CC60SR /*lint --e(923)*/ (*(volatile Ifx_CCU6_CC60SR*)0xF0002B40u)

/** \brief  34, Capture/Compare Register for Channel CC61 */
#define CCU61_CC61R /*lint --e(923)*/ (*(volatile Ifx_CCU6_CC61R*)0xF0002B34u)

/** \brief  44, Capture/Compare Shadow Reg. for Channel CC61 */
#define CCU61_CC61SR /*lint --e(923)*/ (*(volatile Ifx_CCU6_CC61SR*)0xF0002B44u)

/** \brief  38, Capture/Compare Register for Channel CC62 */
#define CCU61_CC62R /*lint --e(923)*/ (*(volatile Ifx_CCU6_CC62R*)0xF0002B38u)

/** \brief  48, Capture/Compare Shadow Reg. for Channel CC62 */
#define CCU61_CC62SR /*lint --e(923)*/ (*(volatile Ifx_CCU6_CC62SR*)0xF0002B48u)

/** \brief  58, Compare Register for T13 */
#define CCU61_CC63R /*lint --e(923)*/ (*(volatile Ifx_CCU6_CC63R*)0xF0002B58u)

/** \brief  5C, Compare Shadow Register for T13 */
#define CCU61_CC63SR /*lint --e(923)*/ (*(volatile Ifx_CCU6_CC63SR*)0xF0002B5Cu)

/** \brief  0, Clock Control Register */
#define CCU61_CLC /*lint --e(923)*/ (*(volatile Ifx_CCU6_CLC*)0xF0002B00u)

/** \brief  64, Compare State Modification Register */
#define CCU61_CMPMODIF /*lint --e(923)*/ (*(volatile Ifx_CCU6_CMPMODIF*)0xF0002B64u)

/** \brief  60, Compare State Register */
#define CCU61_CMPSTAT /*lint --e(923)*/ (*(volatile Ifx_CCU6_CMPSTAT*)0xF0002B60u)

/** \brief  8, Module Identification Register */
#define CCU61_ID /*lint --e(923)*/ (*(volatile Ifx_CCU6_ID*)0xF0002B08u)

/** \brief  B0, Interrupt Enable Register */
#define CCU61_IEN /*lint --e(923)*/ (*(volatile Ifx_CCU6_IEN*)0xF0002BB0u)

/** \brief  98, Input Monitoring Register */
#define CCU61_IMON /*lint --e(923)*/ (*(volatile Ifx_CCU6_IMON*)0xF0002B98u)

/** \brief  AC, Interrupt Node Pointer Register */
#define CCU61_INP /*lint --e(923)*/ (*(volatile Ifx_CCU6_INP*)0xF0002BACu)

/** \brief  A0, Interrupt Status Register */
#define CCU61_IS /*lint --e(923)*/ (*(volatile Ifx_CCU6_IS*)0xF0002BA0u)

/** \brief  A8, Interrupt Status Reset Register */
#define CCU61_ISR /*lint --e(923)*/ (*(volatile Ifx_CCU6_ISR*)0xF0002BA8u)

/** \brief  A4, Interrupt Status Set Register */
#define CCU61_ISS /*lint --e(923)*/ (*(volatile Ifx_CCU6_ISS*)0xF0002BA4u)

/** \brief  F4, Kernel Reset Register 0 */
#define CCU61_KRST0 /*lint --e(923)*/ (*(volatile Ifx_CCU6_KRST0*)0xF0002BF4u)

/** \brief  F0, Kernel Reset Register 1 */
#define CCU61_KRST1 /*lint --e(923)*/ (*(volatile Ifx_CCU6_KRST1*)0xF0002BF0u)

/** \brief  EC, Kernel Reset Status Clear Register */
#define CCU61_KRSTCLR /*lint --e(923)*/ (*(volatile Ifx_CCU6_KRSTCLR*)0xF0002BECu)

/** \brief  1C, Kernel State Control Sensitivity Register */
#define CCU61_KSCSR /*lint --e(923)*/ (*(volatile Ifx_CCU6_KSCSR*)0xF0002B1Cu)

/** \brief  9C, Lost Indicator Register */
#define CCU61_LI /*lint --e(923)*/ (*(volatile Ifx_CCU6_LI*)0xF0002B9Cu)

/** \brief  4, Module Configuration Register */
#define CCU61_MCFG /*lint --e(923)*/ (*(volatile Ifx_CCU6_MCFG*)0xF0002B04u)

/** \brief  94, Multi-Channel Mode Control Register */
#define CCU61_MCMCTR /*lint --e(923)*/ (*(volatile Ifx_CCU6_MCMCTR*)0xF0002B94u)

/** \brief  90, Multi-Channel Mode Output Register */
#define CCU61_MCMOUT /*lint --e(923)*/ (*(volatile Ifx_CCU6_MCMOUT*)0xF0002B90u)

/** \brief  8C, Multi-Channel Mode Output Shadow Register */
#define CCU61_MCMOUTS /*lint --e(923)*/ (*(volatile Ifx_CCU6_MCMOUTS*)0xF0002B8Cu)

/** \brief  80, Modulation Control Register */
#define CCU61_MODCTR /*lint --e(923)*/ (*(volatile Ifx_CCU6_MODCTR*)0xF0002B80u)

/** \brief  E8, OCDS Control and Status Register */
#define CCU61_OCS /*lint --e(923)*/ (*(volatile Ifx_CCU6_OCS*)0xF0002BE8u)

/** \brief  10, Port Input Select Register 0 */
#define CCU61_PISEL0 /*lint --e(923)*/ (*(volatile Ifx_CCU6_PISEL0*)0xF0002B10u)

/** \brief  14, Port Input Select Register 2 */
#define CCU61_PISEL2 /*lint --e(923)*/ (*(volatile Ifx_CCU6_PISEL2*)0xF0002B14u)

/** \brief  88, Passive State Level Register */
#define CCU61_PSLR /*lint --e(923)*/ (*(volatile Ifx_CCU6_PSLR*)0xF0002B88u)

/** \brief  20, Timer T12 Counter Register */
#define CCU61_T12 /*lint --e(923)*/ (*(volatile Ifx_CCU6_T12*)0xF0002B20u)

/** \brief  28, Dead-Time Control Register for Timer12 */
#define CCU61_T12DTC /*lint --e(923)*/ (*(volatile Ifx_CCU6_T12DTC*)0xF0002B28u)

/** \brief  68, T12 Mode Select Register */
#define CCU61_T12MSEL /*lint --e(923)*/ (*(volatile Ifx_CCU6_T12MSEL*)0xF0002B68u)

/** \brief  24, Timer 12 Period Register */
#define CCU61_T12PR /*lint --e(923)*/ (*(volatile Ifx_CCU6_T12PR*)0xF0002B24u)

/** \brief  50, Timer T13 Counter Register */
#define CCU61_T13 /*lint --e(923)*/ (*(volatile Ifx_CCU6_T13*)0xF0002B50u)

/** \brief  54, Timer 13 Period Register */
#define CCU61_T13PR /*lint --e(923)*/ (*(volatile Ifx_CCU6_T13PR*)0xF0002B54u)

/** \brief  70, Timer Control Register 0 */
#define CCU61_TCTR0 /*lint --e(923)*/ (*(volatile Ifx_CCU6_TCTR0*)0xF0002B70u)

/** \brief  74, Timer Control Register 2 */
#define CCU61_TCTR2 /*lint --e(923)*/ (*(volatile Ifx_CCU6_TCTR2*)0xF0002B74u)

/** \brief  78, Timer Control Register 4 */
#define CCU61_TCTR4 /*lint --e(923)*/ (*(volatile Ifx_CCU6_TCTR4*)0xF0002B78u)

/** \brief  84, Trap Control Register */
#define CCU61_TRPCTR /*lint --e(923)*/ (*(volatile Ifx_CCU6_TRPCTR*)0xF0002B84u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXCCU6_REG_H */
