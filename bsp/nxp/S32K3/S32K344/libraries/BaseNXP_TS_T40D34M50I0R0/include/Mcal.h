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
*   @file           Mcal.h
*   @implements     Mcal.h_Artifact
*   @version 5.0.0
*
*   @brief   AUTOSAR BaseNXP - SWS Compiler abstraction specific for MCAL.
*   @details The file Mcal.h provides MCAL specific macros used for compiler abstraction.
*
*
*   @addtogroup BASENXP_COMPONENT
*   @{
*/


#ifndef MCAL_H
#define MCAL_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
/*
* @file        Mcal.h
* @brief Include compiler abstraction
*/
#include "Compiler.h"
/*
* @file        Mcal.h
* @brief Include standard types
*/
#include "Std_Types.h"

#include "DeviceDefinition.h"

#include "Soc_Ips.h"

#include "Reg_eSys.h"

#include "OsIf_Internal.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define MCAL_VENDOR_ID                    43
#define MCAL_MODULE_ID                    0
#define MCAL_AR_RELEASE_MAJOR_VERSION     4
#define MCAL_AR_RELEASE_MINOR_VERSION     7
#define MCAL_AR_RELEASE_REVISION_VERSION  0
#define MCAL_SW_MAJOR_VERSION             5
#define MCAL_SW_MINOR_VERSION             0
#define MCAL_SW_PATCH_VERSION             0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if source file and Compiler.h header file are of the same Autosar version */
    #if ((MCAL_AR_RELEASE_MAJOR_VERSION != COMPILER_AR_RELEASE_MAJOR_VERSION) || \
         (MCAL_AR_RELEASE_MINOR_VERSION != COMPILER_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of Mcal.h and Compiler.h are different"
    #endif
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if source file and Std_Types.h header file are of the same Autosar version */
    #if ((MCAL_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION) || \
         (MCAL_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of Mcal.h and Std_Types.h are different"
    #endif
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if source file and Reg_eSys.h header file are of the same Autosar version */
    #if ((MCAL_AR_RELEASE_MAJOR_VERSION != REG_ESYS_AR_RELEASE_MAJOR_VERSION) || \
         (MCAL_AR_RELEASE_MINOR_VERSION != REG_ESYS_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of Mcal.h and Reg_eSys.h are different"
    #endif
#endif

/* Check if source file and Soc_Ips.h header file have same versions */
#if (MCAL_VENDOR_ID  != SOC_IPS_VENDOR_ID)
#error "Soc_Ips.h and Mcal.h have different vendor IDs"
#endif

/* Check if source file and Soc_Ips.h header file are of the same Autosar version */
#if ((MCAL_AR_RELEASE_MAJOR_VERSION != SOC_IPS_AR_RELEASE_MAJOR_VERSION) || \
     (MCAL_AR_RELEASE_MINOR_VERSION != SOC_IPS_AR_RELEASE_MINOR_VERSION))
    #error "AutoSar Version Numbers of Mcal.h and Soc_Ips.h are different"
#endif

#if ((MCAL_SW_MAJOR_VERSION != SOC_IPS_SW_MAJOR_VERSION) || \
     (MCAL_SW_MINOR_VERSION != SOC_IPS_SW_MINOR_VERSION) || \
     (MCAL_SW_PATCH_VERSION != SOC_IPS_SW_PATCH_VERSION))
    #error "Software Version Numbers of Soc_Ips.h and Mcal.h are different"
#endif
/*==================================================================================================
*                                         CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/   

/**************************************** Green Hills *********************************************/
#ifdef _GREENHILLS_C_S32K3XX_        
    
    /**
    * @brief Compiler abstraction for the intrinsic wait instruction.
    */
    #define EXECUTE_WAIT()  ASM_KEYWORD("  wfi");
    /**
     * @brief Compiler abstraction for MCAL Fault Injection tests 
    */
    #ifdef MCAL_ENABLE_FAULT_INJECTION

        #define MCAL_PUT_IN_QUOTES(x) #x

        #define MCAL_FAULT_INJECTION_POINT(label) ASM_KEYWORD(MCAL_PUT_IN_QUOTES(label::))
    #else

        #define MCAL_FAULT_INJECTION_POINT(label)
    #endif
        
#endif /* #ifdef _GREENHILLS_C_S32K3XX_ */

/**************************************** Wind River Diab *****************************************/
#ifdef _DIABDATA_C_S32K3XX_ 
    
    /**
    * @brief Compiler abstraction for the intrinsic wait instruction.
    */
    #define EXECUTE_WAIT()  ASM_KEYWORD(" wfi");   
    /**
     * @brief Compiler abstraction for MCAL Fault Injection tests 
    */
    #ifdef MCAL_ENABLE_FAULT_INJECTION

        #define MCAL_PUT_IN_QUOTES(x) #x

        #define MCAL_FAULT_INJECTION_POINT(label) ASM_KEYWORD(MCAL_PUT_IN_QUOTES(label:))
    #else

        #define MCAL_FAULT_INJECTION_POINT(label)
    #endif

#endif /* #ifdef _DIABDATA_C_S32K3XX_ */

/*************************************** CodeWarrior **********************************************/
#ifdef _CODEWARRIOR_C_S32K3XX_
    
    /**
    * @brief Compiler abstraction for the intrinsic wait instruction.
    */
    #define EXECUTE_WAIT()  ASM_KEYWORD (" opword 0x7C00007C");
#endif /* #ifdef _CODEWARRIOR_C_S32K3XX_ */

/*************************************** HighTec **********************************************/
#ifdef _HITECH_C_S32K3XX_
    /**
    * @brief Compiler abstraction for the intrinsic wait instruction.
    */
    #define EXECUTE_WAIT()  ASM_KEYWORD("  wait");
#endif /* #ifdef _HITECH_C_S32K3XX_ */
/**************************************** GCC *********************************************/
#ifdef _GCC_C_S32K3XX_
    /**
    * @brief Compiler abstraction for the intrinsic wait instruction.
    */
    #define EXECUTE_WAIT()  ASM_KEYWORD("  wfi");   
    /**
     * @brief Compiler abstraction for MCAL Fault Injection tests 
    */
    #ifdef MCAL_ENABLE_FAULT_INJECTION

        #define MCAL_PUT_IN_QUOTES(x) #x

        #define MCAL_FAULT_INJECTION_POINT(label) ASM_KEYWORD(MCAL_PUT_IN_QUOTES(label:))
    #else

        #define MCAL_FAULT_INJECTION_POINT(label)
    #endif
  
#endif /* #ifdef _GCC_C_S32K3XX_ */

/**************************************** DS5 *********************************************/
#ifdef _ARM_DS5_C_S32K3XX_
    /**
    * @brief Compiler abstraction for the intrinsic wait instruction.
    */
    #define EXECUTE_WAIT()  ASM_KEYWORD("  wfi"); 
    /**
     * @brief Compiler abstraction for MCAL Fault Injection tests 
    */
    #ifdef MCAL_ENABLE_FAULT_INJECTION

        #define MCAL_PUT_IN_QUOTES(x) #x

        #define MCAL_FAULT_INJECTION_POINT(label) ASM_KEYWORD(MCAL_PUT_IN_QUOTES(label:))
    #else

        #define MCAL_FAULT_INJECTION_POINT(label)
    #endif
    
#endif /* #ifdef _ARM_DS5_C_S32K3XX_ */
/**************************************** IAR *********************************************/
#ifdef _IAR_C_S32K3XX_    
    /**
    * @brief Compiler abstraction for the "Put in Quotes".
    */
    #define MCAL_PUT_IN_QUOTES(x) #x
    /**
    * @brief Compiler abstraction for the "Double Put in Quotes" - Used by VAL_ALIGN.
    */
    #define MCAL_PUT_IN_QUOTES1(x) MCAL_PUT_IN_QUOTES(x) 

    /**
    * @brief Compiler abstraction for the intrinsic wait instruction.
    */
    #define EXECUTE_WAIT()  ASM_KEYWORD("  wfi");    
    /**
     * @brief Compiler abstraction for MCAL Fault Injection tests 
    */
    #ifdef MCAL_ENABLE_FAULT_INJECTION

        #define MCAL_FAULT_INJECTION_POINT(label)   ASM_KEYWORD(MCAL_PUT_IN_QUOTES(label:))
    #else

        #define MCAL_FAULT_INJECTION_POINT(label)
    #endif
        
#endif /* #ifdef _IAR_C_S32K3XX_ */

/* check that the compiler used is supported (otherwise some defines might not exist) */
#ifndef _GREENHILLS_C_S32K3XX_
    #ifndef _DIABDATA_C_S32K3XX_
        #ifndef _CODEWARRIOR_C_S32K3XX_
            #ifndef _HITECH_C_S32K3XX_
                #ifndef _GCC_C_S32K3XX_
                    #ifndef _ARM_DS5_C_S32K3XX_
                        #ifndef _IAR_C_S32K3XX_
                            #error "Unsupported compiler. Compiler abstraction needs to be updated to use this compiler."
                        #endif    
                    #endif
                #endif
            #endif
        #endif
    #endif
#endif
#if (MCAL_PLATFORM_ARM  == MCAL_ARM_AARCH64)
/**
* @brief Data Synchronization Barrier (DSB) completes when all instructions before this instruction complete
*/
#define MCAL_DATA_SYNC_BARRIER()  ASM_KEYWORD("dsb sy":::"memory")
/**
* @brief  flushes the pipeline in the processor, so that all instructions following the ISB are fetched from cache or memory, after the ISB has been completed.
*/
#define MCAL_INSTRUCTION_SYNC_BARRIER()  ASM_KEYWORD("isb":::"memory")
#else
/**
* @brief Data Synchronization Barrier (DSB) completes when all instructions before this instruction complete
*/
#define MCAL_DATA_SYNC_BARRIER()  ASM_KEYWORD(" DSB")

/**
* @brief  flushes the pipeline in the processor, so that all instructions following the ISB are fetched from cache or memory, after the ISB has been completed.
*/
#define MCAL_INSTRUCTION_SYNC_BARRIER()  ASM_KEYWORD(" ISB")
#endif

#if defined(MCAL_PLATFORM_ARM_M4) || defined(MCAL_PLATFORM_ARM_M4F)
    #if !defined(USING_OS_AUTOSAROS)
        #define EXIT_INTERRUPT()  MCAL_DATA_SYNC_BARRIER()   /* DSB sy full system */
    #else
        #define EXIT_INTERRUPT()
    #endif /* !defined(USING_OS_AUTOSAROS) */
#else
    #define EXIT_INTERRUPT()
#endif

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/**
* @brief Typedef for DEM error management implemented by MCAL drivers
*/
typedef struct
{
    uint32 state;   /**< enabling/disabling the DEM error: Active=STD_ON/ Inactive=STD_OFF */
    uint32 id ;     /**< ID of DEM error (0 if STD_OFF)*/
}Mcal_DemErrorType; 
/*==================================================================================================
*                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* #ifndef MCAL_H */

/** @} */
