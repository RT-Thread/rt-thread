/*==================================================================================================
* Project : RTD AUTOSAR 4.7
* Platform : CORTEXM
* Peripheral : S32K3XX
* Dependencies : none
*
* Autosar Version : 4.7.0
* Autosar Revision : ASR_REL_4_7_REV_0000
* Autosar Conf.Variant :
* SW Version : 5.0.0
* Build Version : S32K3_RTD_5_0_0_D2408_ASR_REL_4_7_REV_0000_20241002
*
* Copyright 2020 - 2024 NXP
*
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be 
*   used strictly in accordance with the applicable license terms.  By expressly 
*   accepting such terms or by downloading, installing, activating and/or otherwise 
*   using the software, you are agreeing that you have read, and that you agree to 
*   comply with and are bound by, such license terms.  If you do not agree to be 
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/
/**
*   @file    Compiler_Cfg.h
*   @implements     Compiler_Cfg.h_Artifact
*   @version 5.0.0
*
*   @brief   AUTOSAR BaseNXP - Module specific memory and pointer classes
*   @details The file Compiler_Cfg.h contains the module specific parameters (ptrclass and 
*            memclass) that are passed to the macros defined in Compiler.h
*            This file contains sample code only. It is not part of the production code deliverables
*
*   @addtogroup BASENXP_COMPONENT
*   @{
*/
#ifndef COMPILER_CFG_H
#define COMPILER_CFG_H

#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/

/*==================================================================================================
*                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
/** 
@{
* @brief ADC memory and pointer classes.
*/
#define ADC_CODE
#define ADC_CONST
#define ADC_APPL_DATA
#define ADC_APPL_CONST
#define ADC_APPL_CODE
#define ADC_CALLOUT_CODE
#define ADC_VAR_NOINIT
#define ADC_VAR_POWER_ON_INIT
#define ADC_VAR_FAST
#define ADC_VAR
/**@}*/

/** 
@{
* @brief CAN memory and pointer classes.
*/
#define CAN_CODE
#define CAN_CONST
#define CAN_APPL_DATA
#define CAN_APPL_CONST
#define CAN_APPL_CODE
#define CAN_CALLOUT_CODE
#define CAN_VAR_NOINIT
#define CAN_VAR_POWER_ON_INIT
#define CAN_VAR_FAST
#define CAN_VAR
/**@}*/

/** 
@{
* @brief CAN_43_LLCE memory and pointer classes.
*/
#define CAN_43_LLCE_CODE
#define CAN_43_LLCE_CONST
#define CAN_43_LLCE_APPL_DATA
#define CAN_43_LLCE_APPL_CONST
#define CAN_43_LLCE_APPL_CODE
#define CAN_43_LLCE_CALLOUT_CODE
#define CAN_43_LLCE_VAR_NOINIT
#define CAN_43_LLCE_VAR_POWER_ON_INIT
#define CAN_43_LLCE_VAR_FAST
#define CAN_43_LLCE_VAR
/**@}*/

/** 
@{
* @brief CANIF memory and pointer classes.
*/
#define CANIF_CODE
#define CANIF_CONST
#define CANIF_APPL_DATA
#define CANIF_APPL_CONST
#define CANIF_APPL_CODE
#define CANIF_CALLOUT_CODE
#define CANIF_VAR_NOINIT
#define CANIF_VAR_POWER_ON_INIT
#define CANIF_VAR_FAST
#define CANIF_VAR
/**@}*/

/** 
@{
* @brief CRCU memory and pointer classes.
*/
#define CRCU_CODE
#define CRCU_CONST
#define CRCU_APPL_DATA
#define CRCU_APPL_CONST
#define CRCU_APPL_CODE
#define CRCU_CALLOUT_CODE
#define CRCU_VAR_NOINIT
#define CRCU_VAR_POWER_ON_INIT
#define CRCU_VAR_FAST
#define CRCU_VAR
/**@}*/

/** 
@{
* @brief CSEC memory and pointer classes.
*/
#define CSEC_CODE
#define CSEC_CONST
#define CSEC_APPL_DATA
#define CSEC_APPL_CONST
#define CSEC_APPL_CODE
#define CSEC_CALLOUT_CODE
#define CSEC_VAR_NOINIT
#define CSEC_VAR_POWER_ON_INIT
#define CSEC_VAR_FAST
#define CSEC_VAR
/**@}*/

/** 
@{
* @brief DEM memory and pointer classes.
*/
#define DEM_CODE
#define DEM_CONST
#define DEM_APPL_DATA
#define DEM_APPL_CONST
#define DEM_APPL_CODE
#define DEM_CALLOUT_CODE
#define DEM_VAR_NOINIT
#define DEM_VAR_POWER_ON_INIT
#define DEM_VAR_FAST
#define DEM_VAR
/**@}*/

/** 
@{
* @brief DET memory and pointer classes.
*/
#define DET_CODE
#define DET_CONST
#define DET_APPL_DATA
#define DET_APPL_CONST
#define DET_APPL_CODE
#define DET_CALLOUT_CODE
#define DET_VAR_NOINIT
#define DET_VAR_POWER_ON_INIT
#define DET_VAR_FAST
#define DET_VAR
/**@}*/

/** 
@{
* @brief DIO memory and pointer classes.
*/
#define DIO_CODE
#define DIO_CONST
#define DIO_APPL_DATA
#define DIO_APPL_CONST
#define DIO_APPL_CODE
#define DIO_CALLOUT_CODE
#define DIO_VAR_NOINIT
#define DIO_VAR_POWER_ON_INIT
#define DIO_VAR_FAST
#define DIO_VAR
/**@}*/

/** 
@{
* @brief EEP memory and pointer classes.
*/

#define EEP_CODE
#define EEP_CONST
#define EEP_APPL_DATA
#define EEP_APPL_CONST
#define EEP_APPL_CODE
#define EEP_CALLOUT_CODE
#define EEP_VAR_NOINIT
#define EEP_VAR_POWER_ON_INIT
#define EEP_VAR_FAST
#define EEP_VAR
/**@}*/

/**
@{
* @brief ETH memory and pointer classes.
*/

#define ETH_CODE
#define ETH_CONST
#define ETH_APPL_DATA
#define ETH_APPL_CONST
#define ETH_APPL_CODE
#define ETH_CALLOUT_CODE
#define ETH_VAR_NOINIT
#define ETH_VAR_POWER_ON_INIT
#define ETH_VAR_FAST
#define ETH_VAR
/**@}*/

/**
@{
* @brief ETH memory and pointer classes.
*/

#define ETHIF_CODE
#define ETHIF_CONST
#define ETHIF_APPL_DATA
#define ETHIF_APPL_CONST
#define ETHIF_APPL_CODE
#define ETHIF_CALLOUT_CODE
#define ETHIF_VAR_NOINIT
#define ETHIF_VAR_POWER_ON_INIT
#define ETHIF_VAR_FAST
#define ETHIF_VAR
/**@}*/

/**
@{
* @brief ETH memory and pointer classes.
*/

#define ETHTRCV_CODE
#define ETHTRCV_CONST
#define ETHTRCV_APPL_DATA
#define ETHTRCV_APPL_CONST
#define ETHTRCV_APPL_CODE
#define ETHTRCV_CALLOUT_CODE
#define ETHTRCV_VAR_NOINIT
#define ETHTRCV_VAR_POWER_ON_INIT
#define ETHTRCV_VAR_FAST
#define ETHTRCV_VAR
/**@}*/

/** 
@{
* @brief FEE memory and pointer classes.
*/
#define FEE_CODE
#define FEE_CONST
#define FEE_APPL_DATA
#define FEE_APPL_CONST
#define FEE_APPL_CODE
#define FEE_CALLOUT_CODE
#define FEE_VAR_NOINIT
#define FEE_VAR_POWER_ON_INIT
#define FEE_VAR_FAST
#define FEE_VAR
/**@}*/

/** 
@{
* @brief FLS memory and pointer classes.
*/
#define FLS_CODE
#define FLS_CONST
#define FLS_APPL_DATA
#define FLS_APPL_CONST
#define FLS_APPL_CODE
#define FLS_CALLOUT_CODE
#define FLS_VAR_NOINIT
#define FLS_VAR_POWER_ON_INIT
#define FLS_VAR_FAST
#define FLS_VAR
/**@}*/

/** 
@{
* @brief FlexRay memory and pointer classes.
*/
#define FR_CODE
#define FR_CONST
#define FR_APPL_DATA
#define FR_APPL_CONST
#define FR_APPL_CODE
#define FR_CALLOUT_CODE
#define FR_VAR_NOINIT
#define FR_VAR_POWER_ON_INIT
#define FR_VAR_FAST
#define FR_VAR
/**@}*/

/** 
@{
* @brief GPT memory and pointer classes.
*/
#define GPT_CODE
#define GPT_CONST
#define GPT_APPL_DATA
#define GPT_APPL_CONST
#define GPT_APPL_CODE
#define GPT_CALLOUT_CODE
#define GPT_VAR_NOINIT
#define GPT_VAR_POWER_ON_INIT
#define GPT_VAR_FAST
#define GPT_VAR
/**@}*/

/** 
@{
* @brief ICU memory and pointer classes.
*/
#define ICU_CODE
#define ICU_CONST
#define ICU_APPL_DATA
#define ICU_APPL_CONST
#define ICU_APPL_CODE
#define ICU_CALLOUT_CODE
#define ICU_VAR_NOINIT
#define ICU_VAR_POWER_ON_INIT
#define ICU_VAR_FAST
#define ICU_VAR
/**@}*/

/** 
@{
* @brief I2C memory and pointer classes.
*/
#define I2C_CODE
#define I2C_CONST
#define I2C_APPL_DATA
#define I2C_APPL_CONST
#define I2C_APPL_CODE
#define I2C_CALLOUT_CODE
#define I2C_VAR_NOINIT
#define I2C_VAR_POWER_ON_INIT
#define I2C_VAR_FAST
#define I2C_VAR
/**@}*/

/** 
@{
* @brief LIN memory and pointer classes.
*/
#define LIN_CODE
#define LIN_CONST
#define LIN_APPL_DATA
#define LIN_APPL_CONST
#define LIN_APPL_CODE
#define LIN_CALLOUT_CODE
#define LIN_VAR_NOINIT
#define LIN_VAR_POWER_ON_INIT
#define LIN_VAR_FAST
#define LIN_VAR
/**@}*/

/** 
@{
* @brief LIN_43_LLCE memory and pointer classes.
*/
#define LIN_43_LLCE_CODE
#define LIN_43_LLCE_CONST
#define LIN_43_LLCE_APPL_DATA
#define LIN_43_LLCE_APPL_CONST
#define LIN_43_LLCE_APPL_CODE
#define LIN_43_LLCE_CALLOUT_CODE
#define LIN_43_LLCE_VAR_NOINIT
#define LIN_43_LLCE_VAR_POWER_ON_INIT
#define LIN_43_LLCE_VAR_FAST
#define LIN_43_LLCE_VAR
/**@}*/

/** 
@{
* @brief LIN memory and pointer classes.
*/
#define LINIF_CODE
#define LINIF_CONST
#define LINIF_APPL_DATA
#define LINIF_APPL_CONST
#define LINIF_APPL_CODE
#define LINIF_CALLOUT_CODE
#define LINIF_VAR_NOINIT
#define LINIF_VAR_POWER_ON_INIT
#define LINIF_VAR_FAST
#define LINIF_VAR
/**@}*/

/** 
@{
* @brief MCEM memory and pointer classes.
*/
#define MCEM_CODE
#define MCEM_CONST
#define MCEM_APPL_DATA
#define MCEM_APPL_CONST
#define MCEM_APPL_CODE
#define MCEM_CALLOUT_CODE
#define MCEM_VAR_NOINIT
#define MCEM_VAR_POWER_ON_INIT
#define MCEM_VAR_FAST
#define MCEM_VAR
/**@}*/

/** 
@{
* @brief MCL memory and pointer classes.
*/
#define MCL_CODE
#define MCL_CONST
#define MCL_APPL_DATA
#define MCL_APPL_CONST
#define MCL_APPL_CODE
#define MCL_CALLOUT_CODE
#define MCL_VAR_NOINIT
#define MCL_VAR_POWER_ON_INIT
#define MCL_VAR_FAST
#define MCL_VAR
/**@}*/

/** 
@{
* @brief MCU memory and pointer classes.
*/
#define MCU_CODE
#define MCU_CONST
#define MCU_APPL_DATA
#define MCU_APPL_CONST
#define MCU_APPL_CODE
#define MCU_CALLOUT_CODE
#define MCU_VAR_NOINIT
#define MCU_VAR_POWER_ON_INIT
#define MCU_VAR_FAST
#define MCU_VAR
/**@}*/

/** 
@{
* @brief PMIC memory and pointer classes.
*/
#define PMIC_CODE
#define PMIC_CONST
#define PMIC_APPL_DATA
#define PMIC_APPL_CONST
#define PMIC_APPL_CODE
#define PMIC_CALLOUT_CODE
#define PMIC_VAR_NOINIT
#define PMIC_VAR_POWER_ON_INIT
#define PMIC_VAR_FAST
#define PMIC_VAR
/**@}*/

/** 
@{
* @brief PORT memory and pointer classes.
*/
#define PORT_CODE
#define PORT_CONST
#define PORT_APPL_DATA
#define PORT_APPL_CONST
#define PORT_APPL_CODE
#define PORT_CALLOUT_CODE
#define PORT_VAR_NOINIT
#define PORT_VAR_POWER_ON_INIT
#define PORT_VAR_FAST
#define PORT_VAR
/**@}*/

/** 
@{
* @brief PWM memory and pointer classes.
*/
#define PWM_CODE
#define PWM_CONST
#define PWM_APPL_DATA
#define PWM_APPL_CONST
#define PWM_APPL_CODE
#define PWM_CALLOUT_CODE
#define PWM_VAR_NOINIT
#define PWM_VAR_POWER_ON_INIT
#define PWM_VAR_FAST
#define PWM_VAR
/**@}*/


/** 
@{
* @brief RamTST memory and pointer classes.
*/
#define RAMTST_CODE
#define RAMTST_CONST
#define RAMTST_APPL_DATA
#define RAMTST_APPL_CONST
#define RAMTST_APPL_CODE
#define RAMTST_CALLOUT_CODE
#define RAMTST_VAR_NOINIT
#define RAMTST_VAR_POWER_ON_INIT
#define RAMTST_VAR_FAST
#define RAMTST_VAR
/**@}*/

/** 
@{
* @brief SENT memory and pointer classes.
*/
#define SENT_CODE
#define SENT_CONST
#define SENT_APPL_DATA
#define SENT_APPL_CONST
#define SENT_APPL_CODE
#define SENT_CALLOUT_CODE
#define SENT_VAR_NOINIT
#define SENT_VAR_POWER_ON_INIT
#define SENT_VAR_FAST
#define SENT_VAR
/**@}*/

/** 
@{
* @brief SchM memory and pointer classes.
*/
#define SCHM_CODE
#define SCHM_CONST
#define SCHM_APPL_DATA
#define SCHM_APPL_CONST
#define SCHM_APPL_CODE
#define SCHM_CALLOUT_CODE
#define SCHM_VAR_NOINIT
#define SCHM_VAR_POWER_ON_INIT
#define SCHM_VAR_FAST
#define SCHM_VAR
/**@}*/

/** 
@{
* @brief SPI memory and pointer classes.
*/
#define SPI_CODE
#define SPI_CONST
#define SPI_APPL_DATA
#define SPI_APPL_CONST
#define SPI_APPL_CODE
#define SPI_CALLOUT_CODE
#define SPI_VAR_NOINIT
#define SPI_VAR_POWER_ON_INIT
#define SPI_VAR_FAST
#define SPI_VAR
/**@}*/

/** 
@{
* @brief TM memory and pointer classes.
*/
#define TM_CODE
#define TM_CONST
#define TM_APPL_DATA
#define TM_APPL_CONST
#define TM_APPL_CODE
#define TM_CALLOUT_CODE
#define TM_VAR_NOINIT
#define TM_VAR_POWER_ON_INIT
#define TM_VAR_FAST
#define TM_VAR
/**@}*/

/** 
@{
* @brief WDG memory and pointer classes.
*/
#define WDG_CODE
#define WDG_CONST
#define WDG_APPL_DATA
#define WDG_APPL_CONST
#define WDG_APPL_CODE
#define WDG_CALLOUT_CODE
#define WDG_VAR_NOINIT
#define WDG_VAR_POWER_ON_INIT
#define WDG_VAR_FAST
#define WDG_VAR
/**@}*/

/** 
@{
* @brief WDGIF memory and pointer classes.
*/
#define WDGIF_CODE
#define WDGIF_CONST
#define WDGIF_APPL_DATA
#define WDGIF_APPL_CONST
#define WDGIF_APPL_CODE
#define WDGIF_CALLOUT_CODE
#define WDGIF_VAR_NOINIT
#define WDGIF_VAR_POWER_ON_INIT
#define WDGIF_VAR_FAST
#define WDGIF_VAR
/**@}*/

/** 
* @brief Define for ComStack Data.
*/
#define AUTOSAR_COMSTACKDATA

/*==================================================================================================
*                                            ENUMS
==================================================================================================*/

/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* #ifndef COMPILER_CFG_H */

/** @} */
