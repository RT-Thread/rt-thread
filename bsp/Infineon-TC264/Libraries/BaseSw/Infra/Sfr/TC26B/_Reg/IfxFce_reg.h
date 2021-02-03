/**
 * \file IfxFce_reg.h
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
 * \defgroup IfxLld_Fce_Cfg Fce address
 * \ingroup IfxLld_Fce
 * 
 * \defgroup IfxLld_Fce_Cfg_BaseAddress Base address
 * \ingroup IfxLld_Fce_Cfg
 * 
 * \defgroup IfxLld_Fce_Cfg_Fce0 2-FCE0
 * \ingroup IfxLld_Fce_Cfg
 * 
 */
#ifndef IFXFCE_REG_H
#define IFXFCE_REG_H 1
/******************************************************************************/
#include "IfxFce_regdef.h"
/******************************************************************************/
/** \addtogroup IfxLld_Fce_Cfg_BaseAddress
 * \{  */

/** \brief  FCE object */
#define MODULE_FCE0 /*lint --e(923)*/ (*(Ifx_FCE*)0xF0003F00u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Fce_Cfg_Fce0
 * \{  */

/** \brief  FC, Access Enable Register 0 */
#define FCE0_ACCEN0 /*lint --e(923)*/ (*(volatile Ifx_FCE_ACCEN0*)0xF0003FFCu)

/** Alias (User Manual Name) for FCE0_ACCEN0.
* To use register names with standard convension, please use FCE0_ACCEN0.
*/
#define	FCE_ACCEN0	(FCE0_ACCEN0)

/** \brief  F8, Access Enable Register 1 */
#define FCE0_ACCEN1 /*lint --e(923)*/ (*(volatile Ifx_FCE_ACCEN1*)0xF0003FF8u)

/** Alias (User Manual Name) for FCE0_ACCEN1.
* To use register names with standard convension, please use FCE0_ACCEN1.
*/
#define	FCE_ACCEN1	(FCE0_ACCEN1)

/** \brief  0, Clock Control Register */
#define FCE0_CLC /*lint --e(923)*/ (*(volatile Ifx_FCE_CLC*)0xF0003F00u)

/** Alias (User Manual Name) for FCE0_CLC.
* To use register names with standard convension, please use FCE0_CLC.
*/
#define	FCE_CLC	(FCE0_CLC)

/** \brief  8, Module Identification Register */
#define FCE0_ID /*lint --e(923)*/ (*(volatile Ifx_FCE_ID*)0xF0003F08u)

/** Alias (User Manual Name) for FCE0_ID.
* To use register names with standard convension, please use FCE0_ID.
*/
#define	FCE_ID	(FCE0_ID)

/** \brief  28, CRC Configuration Register */
#define FCE0_IN0_CFG /*lint --e(923)*/ (*(volatile Ifx_FCE_CFG*)0xF0003F28u)

/** Alias (User Manual Name) for FCE0_IN0_CFG.
* To use register names with standard convension, please use FCE0_IN0_CFG.
*/
#define	FCE_CFG0	(FCE0_IN0_CFG)

/** \brief  34, CRC Check Register */
#define FCE0_IN0_CHECK /*lint --e(923)*/ (*(volatile Ifx_FCE_IN0_CHECK*)0xF0003F34u)

/** Alias (User Manual Name) for FCE0_IN0_CHECK.
* To use register names with standard convension, please use FCE0_IN0_CHECK.
*/
#define	FCE_CHECK0	(FCE0_IN0_CHECK)

/** \brief  38, CRC Register */
#define FCE0_IN0_CRC /*lint --e(923)*/ (*(volatile Ifx_FCE_IN0_CRC*)0xF0003F38u)

/** Alias (User Manual Name) for FCE0_IN0_CRC.
* To use register names with standard convension, please use FCE0_IN0_CRC.
*/
#define	FCE_CRC0	(FCE0_IN0_CRC)

/** \brief  3C, CRC Test Register */
#define FCE0_IN0_CTR /*lint --e(923)*/ (*(volatile Ifx_FCE_CTR*)0xF0003F3Cu)

/** Alias (User Manual Name) for FCE0_IN0_CTR.
* To use register names with standard convension, please use FCE0_IN0_CTR.
*/
#define	FCE_CTR0	(FCE0_IN0_CTR)

/** \brief  20, Input Register */
#define FCE0_IN0_IR /*lint --e(923)*/ (*(volatile Ifx_FCE_IN0_IR*)0xF0003F20u)

/** Alias (User Manual Name) for FCE0_IN0_IR.
* To use register names with standard convension, please use FCE0_IN0_IR.
*/
#define	FCE_IR0	(FCE0_IN0_IR)

/** \brief  30, CRC Length Register */
#define FCE0_IN0_LENGTH /*lint --e(923)*/ (*(volatile Ifx_FCE_LENGTH*)0xF0003F30u)

/** Alias (User Manual Name) for FCE0_IN0_LENGTH.
* To use register names with standard convension, please use FCE0_IN0_LENGTH.
*/
#define	FCE_LENGTH0	(FCE0_IN0_LENGTH)

/** \brief  24, CRC Result Register */
#define FCE0_IN0_RES /*lint --e(923)*/ (*(volatile Ifx_FCE_IN0_RES*)0xF0003F24u)

/** Alias (User Manual Name) for FCE0_IN0_RES.
* To use register names with standard convension, please use FCE0_IN0_RES.
*/
#define	FCE_RES0	(FCE0_IN0_RES)

/** \brief  2C, CRC Status Register */
#define FCE0_IN0_STS /*lint --e(923)*/ (*(volatile Ifx_FCE_STS*)0xF0003F2Cu)

/** Alias (User Manual Name) for FCE0_IN0_STS.
* To use register names with standard convension, please use FCE0_IN0_STS.
*/
#define	FCE_STS0	(FCE0_IN0_STS)

/** \brief  48, CRC Configuration Register */
#define FCE0_IN1_CFG /*lint --e(923)*/ (*(volatile Ifx_FCE_CFG*)0xF0003F48u)

/** Alias (User Manual Name) for FCE0_IN1_CFG.
* To use register names with standard convension, please use FCE0_IN1_CFG.
*/
#define	FCE_CFG1	(FCE0_IN1_CFG)

/** \brief  54, CRC Check Register */
#define FCE0_IN1_CHECK /*lint --e(923)*/ (*(volatile Ifx_FCE_IN1_CHECK*)0xF0003F54u)

/** Alias (User Manual Name) for FCE0_IN1_CHECK.
* To use register names with standard convension, please use FCE0_IN1_CHECK.
*/
#define	FCE_CHECK1	(FCE0_IN1_CHECK)

/** \brief  58, CRC Register */
#define FCE0_IN1_CRC /*lint --e(923)*/ (*(volatile Ifx_FCE_IN1_CRC*)0xF0003F58u)

/** Alias (User Manual Name) for FCE0_IN1_CRC.
* To use register names with standard convension, please use FCE0_IN1_CRC.
*/
#define	FCE_CRC1	(FCE0_IN1_CRC)

/** \brief  5C, CRC Test Register */
#define FCE0_IN1_CTR /*lint --e(923)*/ (*(volatile Ifx_FCE_CTR*)0xF0003F5Cu)

/** Alias (User Manual Name) for FCE0_IN1_CTR.
* To use register names with standard convension, please use FCE0_IN1_CTR.
*/
#define	FCE_CTR1	(FCE0_IN1_CTR)

/** \brief  40, Input Register */
#define FCE0_IN1_IR /*lint --e(923)*/ (*(volatile Ifx_FCE_IN1_IR*)0xF0003F40u)

/** Alias (User Manual Name) for FCE0_IN1_IR.
* To use register names with standard convension, please use FCE0_IN1_IR.
*/
#define	FCE_IR1	(FCE0_IN1_IR)

/** \brief  50, CRC Length Register */
#define FCE0_IN1_LENGTH /*lint --e(923)*/ (*(volatile Ifx_FCE_LENGTH*)0xF0003F50u)

/** Alias (User Manual Name) for FCE0_IN1_LENGTH.
* To use register names with standard convension, please use FCE0_IN1_LENGTH.
*/
#define	FCE_LENGTH1	(FCE0_IN1_LENGTH)

/** \brief  44, CRC Result Register */
#define FCE0_IN1_RES /*lint --e(923)*/ (*(volatile Ifx_FCE_IN1_RES*)0xF0003F44u)

/** Alias (User Manual Name) for FCE0_IN1_RES.
* To use register names with standard convension, please use FCE0_IN1_RES.
*/
#define	FCE_RES1	(FCE0_IN1_RES)

/** \brief  4C, CRC Status Register */
#define FCE0_IN1_STS /*lint --e(923)*/ (*(volatile Ifx_FCE_STS*)0xF0003F4Cu)

/** Alias (User Manual Name) for FCE0_IN1_STS.
* To use register names with standard convension, please use FCE0_IN1_STS.
*/
#define	FCE_STS1	(FCE0_IN1_STS)

/** \brief  68, CRC Configuration Register */
#define FCE0_IN2_CFG /*lint --e(923)*/ (*(volatile Ifx_FCE_CFG*)0xF0003F68u)

/** Alias (User Manual Name) for FCE0_IN2_CFG.
* To use register names with standard convension, please use FCE0_IN2_CFG.
*/
#define	FCE_CFG2	(FCE0_IN2_CFG)

/** \brief  74, CRC Check Register */
#define FCE0_IN2_CHECK /*lint --e(923)*/ (*(volatile Ifx_FCE_IN2_CHECK*)0xF0003F74u)

/** Alias (User Manual Name) for FCE0_IN2_CHECK.
* To use register names with standard convension, please use FCE0_IN2_CHECK.
*/
#define	FCE_CHECK2	(FCE0_IN2_CHECK)

/** \brief  78, CRC Register */
#define FCE0_IN2_CRC /*lint --e(923)*/ (*(volatile Ifx_FCE_IN2_CRC*)0xF0003F78u)

/** Alias (User Manual Name) for FCE0_IN2_CRC.
* To use register names with standard convension, please use FCE0_IN2_CRC.
*/
#define	FCE_CRC2	(FCE0_IN2_CRC)

/** \brief  7C, CRC Test Register */
#define FCE0_IN2_CTR /*lint --e(923)*/ (*(volatile Ifx_FCE_CTR*)0xF0003F7Cu)

/** Alias (User Manual Name) for FCE0_IN2_CTR.
* To use register names with standard convension, please use FCE0_IN2_CTR.
*/
#define	FCE_CTR2	(FCE0_IN2_CTR)

/** \brief  60, Input Register */
#define FCE0_IN2_IR /*lint --e(923)*/ (*(volatile Ifx_FCE_IN2_IR*)0xF0003F60u)

/** Alias (User Manual Name) for FCE0_IN2_IR.
* To use register names with standard convension, please use FCE0_IN2_IR.
*/
#define	FCE_IR2	(FCE0_IN2_IR)

/** \brief  70, CRC Length Register */
#define FCE0_IN2_LENGTH /*lint --e(923)*/ (*(volatile Ifx_FCE_LENGTH*)0xF0003F70u)

/** Alias (User Manual Name) for FCE0_IN2_LENGTH.
* To use register names with standard convension, please use FCE0_IN2_LENGTH.
*/
#define	FCE_LENGTH2	(FCE0_IN2_LENGTH)

/** \brief  64, CRC Result Register */
#define FCE0_IN2_RES /*lint --e(923)*/ (*(volatile Ifx_FCE_IN2_RES*)0xF0003F64u)

/** Alias (User Manual Name) for FCE0_IN2_RES.
* To use register names with standard convension, please use FCE0_IN2_RES.
*/
#define	FCE_RES2	(FCE0_IN2_RES)

/** \brief  6C, CRC Status Register */
#define FCE0_IN2_STS /*lint --e(923)*/ (*(volatile Ifx_FCE_STS*)0xF0003F6Cu)

/** Alias (User Manual Name) for FCE0_IN2_STS.
* To use register names with standard convension, please use FCE0_IN2_STS.
*/
#define	FCE_STS2	(FCE0_IN2_STS)

/** \brief  88, CRC Configuration Register */
#define FCE0_IN3_CFG /*lint --e(923)*/ (*(volatile Ifx_FCE_CFG*)0xF0003F88u)

/** Alias (User Manual Name) for FCE0_IN3_CFG.
* To use register names with standard convension, please use FCE0_IN3_CFG.
*/
#define	FCE_CFG3	(FCE0_IN3_CFG)

/** \brief  94, CRC Check Register */
#define FCE0_IN3_CHECK /*lint --e(923)*/ (*(volatile Ifx_FCE_IN3_CHECK*)0xF0003F94u)

/** Alias (User Manual Name) for FCE0_IN3_CHECK.
* To use register names with standard convension, please use FCE0_IN3_CHECK.
*/
#define	FCE_CHECK3	(FCE0_IN3_CHECK)

/** \brief  98, CRC Register */
#define FCE0_IN3_CRC /*lint --e(923)*/ (*(volatile Ifx_FCE_IN3_CRC*)0xF0003F98u)

/** Alias (User Manual Name) for FCE0_IN3_CRC.
* To use register names with standard convension, please use FCE0_IN3_CRC.
*/
#define	FCE_CRC3	(FCE0_IN3_CRC)

/** \brief  9C, CRC Test Register */
#define FCE0_IN3_CTR /*lint --e(923)*/ (*(volatile Ifx_FCE_CTR*)0xF0003F9Cu)

/** Alias (User Manual Name) for FCE0_IN3_CTR.
* To use register names with standard convension, please use FCE0_IN3_CTR.
*/
#define	FCE_CTR3	(FCE0_IN3_CTR)

/** \brief  80, Input Register */
#define FCE0_IN3_IR /*lint --e(923)*/ (*(volatile Ifx_FCE_IN3_IR*)0xF0003F80u)

/** Alias (User Manual Name) for FCE0_IN3_IR.
* To use register names with standard convension, please use FCE0_IN3_IR.
*/
#define	FCE_IR3	(FCE0_IN3_IR)

/** \brief  90, CRC Length Register */
#define FCE0_IN3_LENGTH /*lint --e(923)*/ (*(volatile Ifx_FCE_LENGTH*)0xF0003F90u)

/** Alias (User Manual Name) for FCE0_IN3_LENGTH.
* To use register names with standard convension, please use FCE0_IN3_LENGTH.
*/
#define	FCE_LENGTH3	(FCE0_IN3_LENGTH)

/** \brief  84, CRC Result Register */
#define FCE0_IN3_RES /*lint --e(923)*/ (*(volatile Ifx_FCE_IN3_RES*)0xF0003F84u)

/** Alias (User Manual Name) for FCE0_IN3_RES.
* To use register names with standard convension, please use FCE0_IN3_RES.
*/
#define	FCE_RES3	(FCE0_IN3_RES)

/** \brief  8C, CRC Status Register */
#define FCE0_IN3_STS /*lint --e(923)*/ (*(volatile Ifx_FCE_STS*)0xF0003F8Cu)

/** Alias (User Manual Name) for FCE0_IN3_STS.
* To use register names with standard convension, please use FCE0_IN3_STS.
*/
#define	FCE_STS3	(FCE0_IN3_STS)

/** \brief  F4, Kernel Reset Register 0 */
#define FCE0_KRST0 /*lint --e(923)*/ (*(volatile Ifx_FCE_KRST0*)0xF0003FF4u)

/** Alias (User Manual Name) for FCE0_KRST0.
* To use register names with standard convension, please use FCE0_KRST0.
*/
#define	FCE_KRST0	(FCE0_KRST0)

/** \brief  F0, Kernel Reset Register 1 */
#define FCE0_KRST1 /*lint --e(923)*/ (*(volatile Ifx_FCE_KRST1*)0xF0003FF0u)

/** Alias (User Manual Name) for FCE0_KRST1.
* To use register names with standard convension, please use FCE0_KRST1.
*/
#define	FCE_KRST1	(FCE0_KRST1)

/** \brief  EC, Kernel Reset Status Clear Register */
#define FCE0_KRSTCLR /*lint --e(923)*/ (*(volatile Ifx_FCE_KRSTCLR*)0xF0003FECu)

/** Alias (User Manual Name) for FCE0_KRSTCLR.
* To use register names with standard convension, please use FCE0_KRSTCLR.
*/
#define	FCE_KRSTCLR	(FCE0_KRSTCLR)
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXFCE_REG_H */
