/**
 * \file IfxHssl_reg.h
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
 * \defgroup IfxLld_Hssl_Cfg Hssl address
 * \ingroup IfxLld_Hssl
 * 
 * \defgroup IfxLld_Hssl_Cfg_BaseAddress Base address
 * \ingroup IfxLld_Hssl_Cfg
 * 
 * \defgroup IfxLld_Hssl_Cfg_Hssl 2-HSSL
 * \ingroup IfxLld_Hssl_Cfg
 * 
 */
#ifndef IFXHSSL_REG_H
#define IFXHSSL_REG_H 1
/******************************************************************************/
#include "IfxHssl_regdef.h"
/******************************************************************************/
/** \addtogroup IfxLld_Hssl_Cfg_BaseAddress
 * \{  */

/** \brief  HSSL object */
#define MODULE_HSSL /*lint --e(923)*/ (*(Ifx_HSSL*)0xF0080000u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Hssl_Cfg_Hssl
 * \{  */

/** \brief  FC, Access Enable Register 0 */
#define HSSL_ACCEN0 /*lint --e(923)*/ (*(volatile Ifx_HSSL_ACCEN0*)0xF00800FCu)

/** \brief  F8, Access Enable Register 1 */
#define HSSL_ACCEN1 /*lint --e(923)*/ (*(volatile Ifx_HSSL_ACCEN1*)0xF00800F8u)

/** \brief  E0, Access Rules Register */
#define HSSL_AR /*lint --e(923)*/ (*(volatile Ifx_HSSL_AR*)0xF00800E0u)

/** \brief  C4, Access Window End Register */
#define HSSL_AW0_AWEND /*lint --e(923)*/ (*(volatile Ifx_HSSL_AW_AWEND*)0xF00800C4u)

/** Alias (User Manual Name) for HSSL_AW0_AWEND.
* To use register names with standard convension, please use HSSL_AW0_AWEND.
*/
#define	HSSL_AWEND0	(HSSL_AW0_AWEND)

/** \brief  C0, Access Window Start Register */
#define HSSL_AW0_AWSTART /*lint --e(923)*/ (*(volatile Ifx_HSSL_AW_AWSTART*)0xF00800C0u)

/** Alias (User Manual Name) for HSSL_AW0_AWSTART.
* To use register names with standard convension, please use HSSL_AW0_AWSTART.
*/
#define	HSSL_AWSTART0	(HSSL_AW0_AWSTART)

/** \brief  CC, Access Window End Register */
#define HSSL_AW1_AWEND /*lint --e(923)*/ (*(volatile Ifx_HSSL_AW_AWEND*)0xF00800CCu)

/** Alias (User Manual Name) for HSSL_AW1_AWEND.
* To use register names with standard convension, please use HSSL_AW1_AWEND.
*/
#define	HSSL_AWEND1	(HSSL_AW1_AWEND)

/** \brief  C8, Access Window Start Register */
#define HSSL_AW1_AWSTART /*lint --e(923)*/ (*(volatile Ifx_HSSL_AW_AWSTART*)0xF00800C8u)

/** Alias (User Manual Name) for HSSL_AW1_AWSTART.
* To use register names with standard convension, please use HSSL_AW1_AWSTART.
*/
#define	HSSL_AWSTART1	(HSSL_AW1_AWSTART)

/** \brief  D4, Access Window End Register */
#define HSSL_AW2_AWEND /*lint --e(923)*/ (*(volatile Ifx_HSSL_AW_AWEND*)0xF00800D4u)

/** Alias (User Manual Name) for HSSL_AW2_AWEND.
* To use register names with standard convension, please use HSSL_AW2_AWEND.
*/
#define	HSSL_AWEND2	(HSSL_AW2_AWEND)

/** \brief  D0, Access Window Start Register */
#define HSSL_AW2_AWSTART /*lint --e(923)*/ (*(volatile Ifx_HSSL_AW_AWSTART*)0xF00800D0u)

/** Alias (User Manual Name) for HSSL_AW2_AWSTART.
* To use register names with standard convension, please use HSSL_AW2_AWSTART.
*/
#define	HSSL_AWSTART2	(HSSL_AW2_AWSTART)

/** \brief  DC, Access Window End Register */
#define HSSL_AW3_AWEND /*lint --e(923)*/ (*(volatile Ifx_HSSL_AW_AWEND*)0xF00800DCu)

/** Alias (User Manual Name) for HSSL_AW3_AWEND.
* To use register names with standard convension, please use HSSL_AW3_AWEND.
*/
#define	HSSL_AWEND3	(HSSL_AW3_AWEND)

/** \brief  D8, Access Window Start Register */
#define HSSL_AW3_AWSTART /*lint --e(923)*/ (*(volatile Ifx_HSSL_AW_AWSTART*)0xF00800D8u)

/** Alias (User Manual Name) for HSSL_AW3_AWSTART.
* To use register names with standard convension, please use HSSL_AW3_AWSTART.
*/
#define	HSSL_AWSTART3	(HSSL_AW3_AWSTART)

/** \brief  10, Configuration Register */
#define HSSL_CFG /*lint --e(923)*/ (*(volatile Ifx_HSSL_CFG*)0xF0080010u)

/** \brief  0, Clock Control Register */
#define HSSL_CLC /*lint --e(923)*/ (*(volatile Ifx_HSSL_CLC*)0xF0080000u)

/** \brief  C, CRC Control Register */
#define HSSL_CRC /*lint --e(923)*/ (*(volatile Ifx_HSSL_CRC*)0xF008000Cu)

/** \brief  34, Initiator Control Data Register */
#define HSSL_I0_ICON /*lint --e(923)*/ (*(volatile Ifx_HSSL_I_ICON*)0xF0080034u)

/** Alias (User Manual Name) for HSSL_I0_ICON.
* To use register names with standard convension, please use HSSL_I0_ICON.
*/
#define	HSSL_ICON0	(HSSL_I0_ICON)

/** \brief  3C, Initiator Read Data Register */
#define HSSL_I0_IRD /*lint --e(923)*/ (*(volatile Ifx_HSSL_I_IRD*)0xF008003Cu)

/** Alias (User Manual Name) for HSSL_I0_IRD.
* To use register names with standard convension, please use HSSL_I0_IRD.
*/
#define	HSSL_IRD0	(HSSL_I0_IRD)

/** \brief  38, Initiator Read Write Address Register */
#define HSSL_I0_IRWA /*lint --e(923)*/ (*(volatile Ifx_HSSL_I_IRWA*)0xF0080038u)

/** Alias (User Manual Name) for HSSL_I0_IRWA.
* To use register names with standard convension, please use HSSL_I0_IRWA.
*/
#define	HSSL_IRWA0	(HSSL_I0_IRWA)

/** \brief  30, Initiator Write Data Register */
#define HSSL_I0_IWD /*lint --e(923)*/ (*(volatile Ifx_HSSL_I_IWD*)0xF0080030u)

/** Alias (User Manual Name) for HSSL_I0_IWD.
* To use register names with standard convension, please use HSSL_I0_IWD.
*/
#define	HSSL_IWD0	(HSSL_I0_IWD)

/** \brief  44, Initiator Control Data Register */
#define HSSL_I1_ICON /*lint --e(923)*/ (*(volatile Ifx_HSSL_I_ICON*)0xF0080044u)

/** Alias (User Manual Name) for HSSL_I1_ICON.
* To use register names with standard convension, please use HSSL_I1_ICON.
*/
#define	HSSL_ICON1	(HSSL_I1_ICON)

/** \brief  4C, Initiator Read Data Register */
#define HSSL_I1_IRD /*lint --e(923)*/ (*(volatile Ifx_HSSL_I_IRD*)0xF008004Cu)

/** Alias (User Manual Name) for HSSL_I1_IRD.
* To use register names with standard convension, please use HSSL_I1_IRD.
*/
#define	HSSL_IRD1	(HSSL_I1_IRD)

/** \brief  48, Initiator Read Write Address Register */
#define HSSL_I1_IRWA /*lint --e(923)*/ (*(volatile Ifx_HSSL_I_IRWA*)0xF0080048u)

/** Alias (User Manual Name) for HSSL_I1_IRWA.
* To use register names with standard convension, please use HSSL_I1_IRWA.
*/
#define	HSSL_IRWA1	(HSSL_I1_IRWA)

/** \brief  40, Initiator Write Data Register */
#define HSSL_I1_IWD /*lint --e(923)*/ (*(volatile Ifx_HSSL_I_IWD*)0xF0080040u)

/** Alias (User Manual Name) for HSSL_I1_IWD.
* To use register names with standard convension, please use HSSL_I1_IWD.
*/
#define	HSSL_IWD1	(HSSL_I1_IWD)

/** \brief  54, Initiator Control Data Register */
#define HSSL_I2_ICON /*lint --e(923)*/ (*(volatile Ifx_HSSL_I_ICON*)0xF0080054u)

/** Alias (User Manual Name) for HSSL_I2_ICON.
* To use register names with standard convension, please use HSSL_I2_ICON.
*/
#define	HSSL_ICON2	(HSSL_I2_ICON)

/** \brief  5C, Initiator Read Data Register */
#define HSSL_I2_IRD /*lint --e(923)*/ (*(volatile Ifx_HSSL_I_IRD*)0xF008005Cu)

/** Alias (User Manual Name) for HSSL_I2_IRD.
* To use register names with standard convension, please use HSSL_I2_IRD.
*/
#define	HSSL_IRD2	(HSSL_I2_IRD)

/** \brief  58, Initiator Read Write Address Register */
#define HSSL_I2_IRWA /*lint --e(923)*/ (*(volatile Ifx_HSSL_I_IRWA*)0xF0080058u)

/** Alias (User Manual Name) for HSSL_I2_IRWA.
* To use register names with standard convension, please use HSSL_I2_IRWA.
*/
#define	HSSL_IRWA2	(HSSL_I2_IRWA)

/** \brief  50, Initiator Write Data Register */
#define HSSL_I2_IWD /*lint --e(923)*/ (*(volatile Ifx_HSSL_I_IWD*)0xF0080050u)

/** Alias (User Manual Name) for HSSL_I2_IWD.
* To use register names with standard convension, please use HSSL_I2_IWD.
*/
#define	HSSL_IWD2	(HSSL_I2_IWD)

/** \brief  64, Initiator Control Data Register */
#define HSSL_I3_ICON /*lint --e(923)*/ (*(volatile Ifx_HSSL_I_ICON*)0xF0080064u)

/** Alias (User Manual Name) for HSSL_I3_ICON.
* To use register names with standard convension, please use HSSL_I3_ICON.
*/
#define	HSSL_ICON3	(HSSL_I3_ICON)

/** \brief  6C, Initiator Read Data Register */
#define HSSL_I3_IRD /*lint --e(923)*/ (*(volatile Ifx_HSSL_I_IRD*)0xF008006Cu)

/** Alias (User Manual Name) for HSSL_I3_IRD.
* To use register names with standard convension, please use HSSL_I3_IRD.
*/
#define	HSSL_IRD3	(HSSL_I3_IRD)

/** \brief  68, Initiator Read Write Address Register */
#define HSSL_I3_IRWA /*lint --e(923)*/ (*(volatile Ifx_HSSL_I_IRWA*)0xF0080068u)

/** Alias (User Manual Name) for HSSL_I3_IRWA.
* To use register names with standard convension, please use HSSL_I3_IRWA.
*/
#define	HSSL_IRWA3	(HSSL_I3_IRWA)

/** \brief  60, Initiator Write Data Register */
#define HSSL_I3_IWD /*lint --e(923)*/ (*(volatile Ifx_HSSL_I_IWD*)0xF0080060u)

/** Alias (User Manual Name) for HSSL_I3_IWD.
* To use register names with standard convension, please use HSSL_I3_IWD.
*/
#define	HSSL_IWD3	(HSSL_I3_IWD)

/** \brief  8, Module Identification Register */
#define HSSL_ID /*lint --e(923)*/ (*(volatile Ifx_HSSL_ID*)0xF0080008u)

/** \brief  A8, Initiator Stream Current Address Register */
#define HSSL_IS_CA /*lint --e(923)*/ (*(volatile Ifx_HSSL_IS_CA*)0xF00800A8u)

/** Alias (User Manual Name) for HSSL_IS_CA.
* To use register names with standard convension, please use HSSL_IS_CA.
*/
#define	HSSL_ISCA	(HSSL_IS_CA)

/** \brief  AC, Initiator Stream Frame Count Register */
#define HSSL_IS_FC /*lint --e(923)*/ (*(volatile Ifx_HSSL_IS_FC*)0xF00800ACu)

/** Alias (User Manual Name) for HSSL_IS_FC.
* To use register names with standard convension, please use HSSL_IS_FC.
*/
#define	HSSL_ISFC	(HSSL_IS_FC)

/** \brief  A0, Initiator Stream Start Address Register */
#define HSSL_IS_SA0 /*lint --e(923)*/ (*(volatile Ifx_HSSL_ISSA*)0xF00800A0u)

/** Alias (User Manual Name) for HSSL_IS_SA0.
* To use register names with standard convension, please use HSSL_IS_SA0.
*/
#define	HSSL_ISSA0	(HSSL_IS_SA0)

/** \brief  A4, Initiator Stream Start Address Register */
#define HSSL_IS_SA1 /*lint --e(923)*/ (*(volatile Ifx_HSSL_ISSA*)0xF00800A4u)

/** Alias (User Manual Name) for HSSL_IS_SA1.
* To use register names with standard convension, please use HSSL_IS_SA1.
*/
#define	HSSL_ISSA1	(HSSL_IS_SA1)

/** \brief  F4, Kernel Reset Register 0 */
#define HSSL_KRST0 /*lint --e(923)*/ (*(volatile Ifx_HSSL_KRST0*)0xF00800F4u)

/** \brief  F0, Kernel Reset Register 1 */
#define HSSL_KRST1 /*lint --e(923)*/ (*(volatile Ifx_HSSL_KRST1*)0xF00800F0u)

/** \brief  EC, Kernel Reset Status Clear Register */
#define HSSL_KRSTCLR /*lint --e(923)*/ (*(volatile Ifx_HSSL_KRSTCLR*)0xF00800ECu)

/** \brief  18, Miscellaneous Flags Register */
#define HSSL_MFLAGS /*lint --e(923)*/ (*(volatile Ifx_HSSL_MFLAGS*)0xF0080018u)

/** \brief  20, Miscellaneous Flags Clear Register */
#define HSSL_MFLAGSCL /*lint --e(923)*/ (*(volatile Ifx_HSSL_MFLAGSCL*)0xF0080020u)

/** \brief  24, Flags Enable Register */
#define HSSL_MFLAGSEN /*lint --e(923)*/ (*(volatile Ifx_HSSL_MFLAGSEN*)0xF0080024u)

/** \brief  1C, Miscellaneous Flags Set Register */
#define HSSL_MFLAGSSET /*lint --e(923)*/ (*(volatile Ifx_HSSL_MFLAGSSET*)0xF008001Cu)

/** \brief  E8, OCDS Control and Status */
#define HSSL_OCS /*lint --e(923)*/ (*(volatile Ifx_HSSL_OCS*)0xF00800E8u)

/** \brief  14, Request Flags Register */
#define HSSL_QFLAGS /*lint --e(923)*/ (*(volatile Ifx_HSSL_QFLAGS*)0xF0080014u)

/** \brief  28, Stream FIFOs Status Flags Register */
#define HSSL_SFSFLAGS /*lint --e(923)*/ (*(volatile Ifx_HSSL_SFSFLAGS*)0xF0080028u)

/** \brief  74, Target Current Address Register */
#define HSSL_T0_TCA /*lint --e(923)*/ (*(volatile Ifx_HSSL_T_TCA*)0xF0080074u)

/** Alias (User Manual Name) for HSSL_T0_TCA.
* To use register names with standard convension, please use HSSL_T0_TCA.
*/
#define	HSSL_TCA0	(HSSL_T0_TCA)

/** \brief  70, Target Current Data Register */
#define HSSL_T0_TCD /*lint --e(923)*/ (*(volatile Ifx_HSSL_T_TCD*)0xF0080070u)

/** Alias (User Manual Name) for HSSL_T0_TCD.
* To use register names with standard convension, please use HSSL_T0_TCD.
*/
#define	HSSL_TCD0	(HSSL_T0_TCD)

/** \brief  7C, Target Current Address Register */
#define HSSL_T1_TCA /*lint --e(923)*/ (*(volatile Ifx_HSSL_T_TCA*)0xF008007Cu)

/** Alias (User Manual Name) for HSSL_T1_TCA.
* To use register names with standard convension, please use HSSL_T1_TCA.
*/
#define	HSSL_TCA1	(HSSL_T1_TCA)

/** \brief  78, Target Current Data Register */
#define HSSL_T1_TCD /*lint --e(923)*/ (*(volatile Ifx_HSSL_T_TCD*)0xF0080078u)

/** Alias (User Manual Name) for HSSL_T1_TCD.
* To use register names with standard convension, please use HSSL_T1_TCD.
*/
#define	HSSL_TCD1	(HSSL_T1_TCD)

/** \brief  84, Target Current Address Register */
#define HSSL_T2_TCA /*lint --e(923)*/ (*(volatile Ifx_HSSL_T_TCA*)0xF0080084u)

/** Alias (User Manual Name) for HSSL_T2_TCA.
* To use register names with standard convension, please use HSSL_T2_TCA.
*/
#define	HSSL_TCA2	(HSSL_T2_TCA)

/** \brief  80, Target Current Data Register */
#define HSSL_T2_TCD /*lint --e(923)*/ (*(volatile Ifx_HSSL_T_TCD*)0xF0080080u)

/** Alias (User Manual Name) for HSSL_T2_TCD.
* To use register names with standard convension, please use HSSL_T2_TCD.
*/
#define	HSSL_TCD2	(HSSL_T2_TCD)

/** \brief  8C, Target Current Address Register */
#define HSSL_T3_TCA /*lint --e(923)*/ (*(volatile Ifx_HSSL_T_TCA*)0xF008008Cu)

/** Alias (User Manual Name) for HSSL_T3_TCA.
* To use register names with standard convension, please use HSSL_T3_TCA.
*/
#define	HSSL_TCA3	(HSSL_T3_TCA)

/** \brief  88, Target Current Data Register */
#define HSSL_T3_TCD /*lint --e(923)*/ (*(volatile Ifx_HSSL_T_TCD*)0xF0080088u)

/** Alias (User Manual Name) for HSSL_T3_TCD.
* To use register names with standard convension, please use HSSL_T3_TCD.
*/
#define	HSSL_TCD3	(HSSL_T3_TCD)

/** \brief  94, Target ID Address Register */
#define HSSL_TIDADD /*lint --e(923)*/ (*(volatile Ifx_HSSL_TIDADD*)0xF0080094u)

/** \brief  B8, Target Stream Current Address Register */
#define HSSL_TS_CA /*lint --e(923)*/ (*(volatile Ifx_HSSL_TS_CA*)0xF00800B8u)

/** Alias (User Manual Name) for HSSL_TS_CA.
* To use register names with standard convension, please use HSSL_TS_CA.
*/
#define	HSSL_TSCA	(HSSL_TS_CA)

/** \brief  BC, Target Stream Frame Count Register */
#define HSSL_TS_FC /*lint --e(923)*/ (*(volatile Ifx_HSSL_TS_FC*)0xF00800BCu)

/** Alias (User Manual Name) for HSSL_TS_FC.
* To use register names with standard convension, please use HSSL_TS_FC.
*/
#define	HSSL_TSFC	(HSSL_TS_FC)

/** \brief  B0, Target Stream Start Address Register */
#define HSSL_TS_SA0 /*lint --e(923)*/ (*(volatile Ifx_HSSL_TSSA*)0xF00800B0u)

/** Alias (User Manual Name) for HSSL_TS_SA0.
* To use register names with standard convension, please use HSSL_TS_SA0.
*/
#define	HSSL_TSSA0	(HSSL_TS_SA0)

/** \brief  B4, Target Stream Start Address Register */
#define HSSL_TS_SA1 /*lint --e(923)*/ (*(volatile Ifx_HSSL_TSSA*)0xF00800B4u)

/** Alias (User Manual Name) for HSSL_TS_SA1.
* To use register names with standard convension, please use HSSL_TS_SA1.
*/
#define	HSSL_TSSA1	(HSSL_TS_SA1)

/** \brief  90, Target Status Register */
#define HSSL_TSTAT /*lint --e(923)*/ (*(volatile Ifx_HSSL_TSTAT*)0xF0080090u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXHSSL_REG_H */
