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
*   @file    RegLockMacros.h
*   
*   @version 5.0.0
*
*   @brief   AUTOSAR BaseNXP - IP module versions.
*   @details Implements macros for soft and hard lock on CORTEXM hardware platform
*	@implements     RegLockMacros.h_Artifact 
*   @addtogroup BASENXP_COMPONENT
*   @{
*/


#ifndef REGLOCKMACROS_H
#define REGLOCKMACROS_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Platform_Types.h"
#include "Soc_Ips.h"

/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define REGLOCKMACROS_VENDOR_ID                    43
#define REGLOCKMACROS_MODULE_ID                    0
#define REGLOCKMACROS_AR_RELEASE_MAJOR_VERSION     4
#define REGLOCKMACROS_AR_RELEASE_MINOR_VERSION     7
#define REGLOCKMACROS_AR_RELEASE_REVISION_VERSION  0
#define REGLOCKMACROS_SW_MAJOR_VERSION             5
#define REGLOCKMACROS_SW_MINOR_VERSION             0
#define REGLOCKMACROS_SW_PATCH_VERSION             0

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if source file and Platform_Types.h header file are of the same Autosar version */
    #if ((REGLOCKMACROS_AR_RELEASE_MAJOR_VERSION != PLATFORM_AR_RELEASE_MAJOR_VERSION) || \
         (REGLOCKMACROS_AR_RELEASE_MINOR_VERSION != PLATFORM_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of RegLockMacros.h and Platform_Types.h are different"
    #endif

    /* Check if source file and Soc_Ips.h header file are of the same Autosar version */
    #if ((REGLOCKMACROS_AR_RELEASE_MAJOR_VERSION != SOC_IPS_AR_RELEASE_MAJOR_VERSION) || \
         (REGLOCKMACROS_AR_RELEASE_MINOR_VERSION != SOC_IPS_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of RegLockMacros.h and Soc_Ips.h are different"
    #endif
#endif

/*==================================================================================================
*                                           CONSTANTS
==================================================================================================*/
/**
* @brief 8 bits memory write macro
*/
#define RLM_REG_WRITE8(address, value)        ((*(volatile uint8*)(address))=  (value))
/**
* @brief 16 bits memory write macro.
*/
#define RLM_REG_WRITE16(address, value)       ((*(volatile uint16*)(address))= (value))
/**
* @brief 32 bits memory write macro.
*/
#define RLM_REG_WRITE32(address, value)       ((*(volatile uint32*)(address))= (value))


/**
* @brief 8 bits memory read macro.
*/
#define RLM_REG_READ8(address)                (*(volatile uint8*)(address))
/**
* @brief 16 bits memory read macro.
*/
#define RLM_REG_READ16(address)               (*(volatile uint16*)(address))
/**
* @brief 32 bits memory read macro.
*/
#define RLM_REG_READ32(address)               (*(volatile uint32*)(address))

/**
* @brief 8 bits bits clearing macro.
*/
#define RLM_REG_BIT_CLEAR8(address, mask)     ((*(volatile uint8*)(address))&= (~(mask)))
/**
* @brief 16 bits bits clearing macro.
*/
#define RLM_REG_BIT_CLEAR16(address, mask)    ((*(volatile uint16*)(address))&= (~(mask)))
/**
* @brief 32 bits bits clearing macro.
*/
#define RLM_REG_BIT_CLEAR32(address, mask)    ((*(volatile uint32*)(address))&= (~(mask)))


/**
* @brief 8 bits bits getting macro.
*/
#define RLM_REG_BIT_GET8(address, mask)       ((*(volatile uint8*)(address))& (mask))
/**
* @brief 16 bits bits getting macro.
*/
#define RLM_REG_BIT_GET16(address, mask)      ((*(volatile uint16*)(address))& (mask))
/**
* @brief 32 bits bits getting macro.
*/
#define RLM_REG_BIT_GET32(address, mask)      ((*(volatile uint32*)(address))& (mask))


/**
* @brief 8 bits bits setting macro.
*/
#define RLM_REG_BIT_SET8(address, mask)       ((*(volatile uint8*)(address))|= (mask))
/**
* @brief 16 bits bits setting macro.
*/
#define RLM_REG_BIT_SET16(address, mask)      ((*(volatile uint16*)(address))|= (mask))
/**
* @brief 32 bits bits setting macro.
*/
#define RLM_REG_BIT_SET32(address, mask)      ((*(volatile uint32*)(address))|= (mask))


/**
* @brief 8 bit clear bits and set with new value
* @note In the current implementation, it is caller's (user's) responsability to make sure that
*       value has only "mask" bits set - (value&~mask)==0
*/
#define RLM_REG_RMW8(address, mask, value)    (RLM_REG_WRITE8((address), ((RLM_REG_READ8(address)& ((uint8)~(mask)))| (value))))
/**
* @brief 16 bit clear bits and set with new value
* @note In the current implementation, it is caller's (user's) responsability to make sure that
*       value has only "mask" bits set - (value&~mask)==0
*/
#define RLM_REG_RMW16(address, mask, value)   (RLM_REG_WRITE16((address), ((RLM_REG_READ16(address)& ((uint16)~(mask)))| (value))))
/**
* @brief 32 bit clear bits and set with new value
* @note In the current implementation, it is caller's (user's) responsability to make sure that
*       value has only "mask" bits set - (value&~mask)==0
*/
#define RLM_REG_RMW32(address, mask, value)   (RLM_REG_WRITE32((address), ((RLM_REG_READ32(address)& ((uint32)~(mask)))| (value))))

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
/* Sanity check on USER_MODE_REG_PROT_ENABLED. This define must exist and has to have one of the 
following 2 values: STD_ON or STD_OFF */
#ifndef USER_MODE_REG_PROT_ENABLED
    #error "USER_MODE_REG_PROT_ENABLED is not defined" 
#endif
#if ((USER_MODE_REG_PROT_ENABLED != STD_ON) && (USER_MODE_REG_PROT_ENABLED != STD_OFF))
    #error "USER_MODE_REG_PROT_ENABLED has a wrong value"
#endif

/**
* @brief Mask for setting SLB bit(s) in a SLBR register (for 8/16/32bit registers)
*/
#define SLBR_SET_BIT_8BIT_REG_MASK_U8     ((uint8)0x88U)
#define SLBR_SET_BIT_16BIT_REG_MASK_U8    ((uint8)0xCCU)
#define SLBR_SET_BIT_32BIT_REG_MASK_U8    ((uint8)0xFFU)

/**
* @brief Mask for clearing WE bit(s) in a SLBR register (for 8/16/32bit registers)
*/
#define SLBR_CLR_BIT_8BIT_REG_MASK_U8     ((uint8)0x80U)
#define SLBR_CLR_BIT_16BIT_REG_MASK_U8    ((uint8)0xC0U)
#define SLBR_CLR_BIT_32BIT_REG_MASK_U8    ((uint8)0xF0U)

/**
* @brief Mask for getting SLB bit(s) in a SLBR register (for 8/16/32bit registers)
*/
#define SLBR_GET_BIT_8BIT_REG_MASK_U8     ((uint8)0x08U)
#define SLBR_GET_BIT_16BIT_REG_MASK_U8    ((uint8)0x0CU)
#define SLBR_GET_BIT_32BIT_REG_MASK_U8    ((uint8)0x0FU)


#if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
    /* This will map the byte number with the offset, as the SLBR bytes are arranged in 3 2 1 0 order. Replaces old expression (x%4 == 1 ? x+1 : (x%4 == 2 ? x-1 : (x%4 == 3 ? x-3 : x+3))) */
    #define ENDIANNESS(x)   ((x) ^ 3UL)

    /**
    * @brief Masks for inverting bit positions in a SLBR register
    */
    #define SLBR_XOR_8BIT_REG_MASK_U8     ((uint8)3U)
    #define SLBR_XOR_16BIT_REG_MASK_U8    ((uint8)2U)
    #define SLBR_XOR_32BIT_REG_MASK_U8    ((uint8)0U)


#else /* BYTE_ORDER = high byte first */
    /* This will map the byte number with the offset, as the SLBR bytes are arranged in 0 1 2 3 order. */
    #define ENDIANNESS(x) (x)

    /**
    * @brief Masks for inverting bit positions in a SLBR register
    */
    #define SLBR_XOR_8BIT_REG_MASK_U8     ((uint8)0U)
    #define SLBR_XOR_16BIT_REG_MASK_U8    ((uint8)0U)
    #define SLBR_XOR_32BIT_REG_MASK_U8    ((uint8)0U)
#endif

/**
* @brief Mask used for getting the alignment of an address
*        inside a 32 bit word
*/
#define MODULO_4_BIT_MASK_U32             ((uint32)0x3UL)

#ifdef IPV_REG_PROT
    #if (IPV_S32K2XX_PLATFORM_U32 == IPV_GET_PLATFORM_U32(IPV_REG_PROT))
        /**
        * @brief Offset to REG_PROT mirrored registers area 
        *        of an IP module
        */
        #define MIRRORED_ADDR_OFFSET_U32          ((uint32)0x400UL)
    #elif (IPV_S32K3XX_PLATFORM_U32 == IPV_GET_PLATFORM_U32(IPV_REG_PROT))
        /**
        * @brief Offset to REG_PROT mirrored registers area 
        *        of an IP module
        */
        #define MIRRORED_ADDR_OFFSET_U32          ((uint32)0x400UL)
    #elif (IPV_S32XX_PLATFORM_U32 == IPV_GET_PLATFORM_U32(IPV_REG_PROT))
        /**
        * @brief Offset to REG_PROT mirrored registers area 
        *        of an IP module
        */
        #define MIRRORED_ADDR_OFFSET_U32          ((uint32)0x400UL)
    #elif (IPV_S32R41_PLATFORM_U32 == IPV_GET_PLATFORM_U32(IPV_REG_PROT))
        /**
        * @brief Offset to REG_PROT mirrored registers area 
        *        of an IP module
        */
        #define MIRRORED_ADDR_OFFSET_U32          ((uint32)0x400UL)
    #else
        /**
        * @brief Offset to REG_PROT mirrored registers area 
        *        of an IP module
        */
        #define MIRRORED_ADDR_OFFSET_U32          ((uint32)0x2000UL)
    #endif
#else
    /**
    * @brief Offset to REG_PROT mirrored registers area 
    *        of an IP module
    */
    #define MIRRORED_ADDR_OFFSET_U32          ((uint32)0x2000UL)
#endif

#ifdef IPV_REG_PROT
    #if (IPV_S32K2XX_PLATFORM_U32 == IPV_GET_PLATFORM_U32(IPV_REG_PROT))
        /**
        * @brief Offset to baseAddress of the SLBR registers area
        *        of an IP module
        */
        #define SLBR_ADDR_OFFSET_U32              ((uint32)0x800UL)
    #elif (IPV_S32K3XX_PLATFORM_U32 == IPV_GET_PLATFORM_U32(IPV_REG_PROT))
        /**
        * @brief Offset to baseAddress of the SLBR registers area
        *        of an IP module
        */
        #define SLBR_ADDR_OFFSET_U32              ((uint32)0x800UL)
    #elif (IPV_S32XX_PLATFORM_U32 == IPV_GET_PLATFORM_U32(IPV_REG_PROT))
        /**
        * @brief Offset to baseAddress of the SLBR registers area
        *        of an IP module
        */
        #define SLBR_ADDR_OFFSET_U32              ((uint32)0x800UL)
    #elif (IPV_S32R41_PLATFORM_U32 == IPV_GET_PLATFORM_U32(IPV_REG_PROT))
        /**
        * @brief Offset to baseAddress of the SLBR registers area
        *        of an IP module
        */
        #define SLBR_ADDR_OFFSET_U32              ((uint32)0x800UL)
    #else
        /**
        * @brief Offset to baseAddress of the REG_PROT GCR register
        *        of an IP module
        */
        #define SLBR_ADDR_OFFSET_U32              ((uint32)0x3800UL)   
    #endif
#else
    /**
    * @brief Offset to baseAddress of the SLBR registers area
    *        of an IP module
    */
    #define SLBR_ADDR_OFFSET_U32              ((uint32)0x3800UL)
#endif

/**
* @brief Macro for getting the address of a lockable
*        register's corresponding SLBR register 
*/
#define SLBR_ADDR32(baseAddr, regAddr, prot_mem)  (((uint32)(baseAddr)) + ((prot_mem) * SLBR_ADDR_OFFSET_U32) +      \
                                                    ENDIANNESS((uint32)((((uint32)(regAddr)) - ((uint32)(baseAddr)))>>0x2U)))

#ifdef IPV_REG_PROT
    #if (IPV_S32K2XX_PLATFORM_U32 == IPV_GET_PLATFORM_U32(IPV_REG_PROT))
        /**
        * @brief Offset to baseAddress of the REG_PROT GCR register
        *        of an IP module
        */
        #define GCR_OFFSET_U32                    ((uint32)0x900UL)
    #elif (IPV_S32K3XX_PLATFORM_U32 == IPV_GET_PLATFORM_U32(IPV_REG_PROT))
        /**
        * @brief Offset to baseAddress of the REG_PROT GCR register
        *        of an IP module
        */
        #define GCR_OFFSET_U32                    ((uint32)0x900UL)
    #elif (IPV_S32S2XX_PLATFORM_U32 == IPV_GET_PLATFORM_U32(IPV_REG_PROT))
        /**
        * @brief Offset to baseAddress of the REG_PROT GCR register
        *        of an IP module
        */
        #define GCR_OFFSET_U32                    ((uint32)0x900UL)

        /**
        * @brief Offset to baseAddress of the REG_PROT_AE GCR register
        *        of an IP module
        */
        #define GCR_AE_OFFSET_U32                 ((uint32)0x3FFCUL)
    #elif (IPV_S32XX_PLATFORM_U32 == IPV_GET_PLATFORM_U32(IPV_REG_PROT))
        /**
        * @brief Offset to baseAddress of the REG_PROT GCR register
        *        of an IP module
        */
        #define GCR_OFFSET_U32                    ((uint32)0x900UL)
    #elif (IPV_S32R41_PLATFORM_U32 == IPV_GET_PLATFORM_U32(IPV_REG_PROT))
        /**
        * @brief Offset to baseAddress of the REG_PROT GCR register
        *        of an IP module
        */
        #define GCR_OFFSET_U32                    ((uint32)0x900UL)
    #else
        /**
        * @brief Offset to baseAddress of the REG_PROT GCR register
        *        of an IP module
        */
        #define GCR_OFFSET_U32                    ((uint32)0x3FFCUL)   
    #endif
#else
    /**
    * @brief Offset to baseAddress of the REG_PROT GCR register
    *        of an IP module
    */
    #define GCR_OFFSET_U32                    ((uint32)0x3FFCUL)
#endif

/**
* @brief REG_PROT GCR bit masks
*/
#define REGPROT_GCR_HLB_MASK_U32          ((uint32)0x80000000UL)
#define REGPROT_GCR_UAA_MASK_U32          ((uint32)0x00800000UL)

/**
* @brief REG_PROT GCR bit positions
*/
#define REGPROT_GCR_HLB_POS_U32           ((uint32)31UL)
#define REGPROT_GCR_UAA_POS_U32           ((uint32)23UL)



/*==================================================================================================
*                     MACROS FOR WORKING WITH SW AND HW LOCK    
==================================================================================================*/


/**
* @brief      Soft locks a register by setting it's corresponding soft lock bit
*
* @details    Based on the address of the register to be soft locked and on the address
*             of the IP where the register belongs to, the corresponding soft lock bit
*             is set    
*
* @param[in]  baseAddr - base address of the IP the register belongs to 
* @param[in]  regAddr  - address of the register to soft lock
* @param[in]  prot_mem - protection size of the IP
*
* @return     void
*/
#if (STD_ON == USER_MODE_REG_PROT_ENABLED)
    #define REG_SET_SOFT_LOCK8(baseAddr, regAddr, prot_mem)                            \
    {                                                                                   \
        RLM_REG_WRITE8(SLBR_ADDR32((baseAddr), (regAddr), (prot_mem)),                  \
        (uint8)(SLBR_SET_BIT_8BIT_REG_MASK_U8 >> ((((regAddr) - (baseAddr)) & MODULO_4_BIT_MASK_U32) ^ SLBR_XOR_8BIT_REG_MASK_U8)));  \
    }
#else
    #define REG_SET_SOFT_LOCK8(baseAddr, regAddr, prot_mem)
#endif /* (STD_ON == USER_MODE_REG_PROT_ENABLED) */

#if (STD_ON == USER_MODE_REG_PROT_ENABLED)
    #define REG_SET_SOFT_LOCK16(baseAddr, regAddr, prot_mem)                            \
    {                                                                                   \
        RLM_REG_WRITE8(SLBR_ADDR32((baseAddr), (regAddr), (prot_mem)),                  \
        (uint8)(SLBR_SET_BIT_16BIT_REG_MASK_U8 >> ((((regAddr) - (baseAddr)) & MODULO_4_BIT_MASK_U32) ^ SLBR_XOR_16BIT_REG_MASK_U8)));  \
    }
#else
    #define REG_SET_SOFT_LOCK16(baseAddr, regAddr, prot_mem)
#endif /* (STD_ON == USER_MODE_REG_PROT_ENABLED) */

#if (STD_ON == USER_MODE_REG_PROT_ENABLED)
    #define REG_SET_SOFT_LOCK32(baseAddr, regAddr, prot_mem)                            \
    {                                                                                   \
        RLM_REG_WRITE8(SLBR_ADDR32((baseAddr), (regAddr), (prot_mem)),                  \
        (uint8)(SLBR_SET_BIT_32BIT_REG_MASK_U8 >> ((((regAddr) - (baseAddr)) & MODULO_4_BIT_MASK_U32) ^ SLBR_XOR_32BIT_REG_MASK_U8)));  \
    }
#else
    #define REG_SET_SOFT_LOCK32(baseAddr, regAddr, prot_mem)
#endif /* (STD_ON == USER_MODE_REG_PROT_ENABLED) */

/**
* @brief      Soft unlocks a register by clearing it's corresponding soft lock bit
*
* @details    Based on the address of the register to be soft unlocked and on the address
*             of the IP where the register belongs to, the corresponding soft lock bit
*             is cleared    
*
* @param[in]  baseAddr - base address of the IP the register belongs to 
* @param[in]  regAddr  - address of the register to soft unlock
* @param[in]  prot_mem - protection size of the IP
*
* @return     void
*/
#if (STD_ON == USER_MODE_REG_PROT_ENABLED)
    #define REG_CLR_SOFT_LOCK8(baseAddr, regAddr, prot_mem)                            \
    {                                                                                   \
        RLM_REG_WRITE8(SLBR_ADDR32((baseAddr), (regAddr), (prot_mem)),                  \
        (uint8)(SLBR_CLR_BIT_8BIT_REG_MASK_U8 >> ((((regAddr) - (baseAddr)) & MODULO_4_BIT_MASK_U32) ^ SLBR_XOR_8BIT_REG_MASK_U8)));  \
    }
#else
    #define REG_CLR_SOFT_LOCK8(baseAddr, regAddr, prot_mem)
#endif /* (STD_ON == USER_MODE_REG_PROT_ENABLED) */

#if (STD_ON == USER_MODE_REG_PROT_ENABLED)
    #define REG_CLR_SOFT_LOCK16(baseAddr, regAddr, prot_mem)                            \
    {                                                                                   \
        RLM_REG_WRITE8(SLBR_ADDR32((baseAddr), (regAddr), (prot_mem)),                  \
        (uint8)(SLBR_CLR_BIT_16BIT_REG_MASK_U8 >> ((((regAddr) - (baseAddr)) & MODULO_4_BIT_MASK_U32) ^ SLBR_XOR_16BIT_REG_MASK_U8)));  \
    }
#else
    #define REG_CLR_SOFT_LOCK16(baseAddr, regAddr, prot_mem)
#endif /* (STD_ON == USER_MODE_REG_PROT_ENABLED) */

#if (STD_ON == USER_MODE_REG_PROT_ENABLED)
    #define REG_CLR_SOFT_LOCK32(baseAddr, regAddr, prot_mem)                            \
    {                                                                                   \
        RLM_REG_WRITE8(SLBR_ADDR32((baseAddr), (regAddr), (prot_mem)),                  \
        (uint8)(SLBR_CLR_BIT_32BIT_REG_MASK_U8 >> ((((regAddr) - (baseAddr)) & MODULO_4_BIT_MASK_U32) ^ SLBR_XOR_32BIT_REG_MASK_U8)));  \
    }
#else
    #define REG_CLR_SOFT_LOCK32(baseAddr, regAddr, prot_mem)
#endif /* (STD_ON == USER_MODE_REG_PROT_ENABLED) */

/**
* @brief      Reads the status of the soft lock bit of a register
*
* @param[in]  baseAddr - base address of the IP the register belongs to 
* @param[in]  regAddr  - address of the register for which to get soft lock bit status
* @param[in]  prot_mem - protection size of the IP
*
* @return     uint8  - 1 if the register's soft lock is enabled
*                    - 0 if the register's soft lock is disabled
*/
#if (STD_ON == USER_MODE_REG_PROT_ENABLED)

    #define REG_GET_SOFT_LOCK8(baseAddr, regAddr, prot_mem)                                                     \
            ((uint8)((RLM_REG_READ8(SLBR_ADDR32((baseAddr), (regAddr), (prot_mem))) &                              \
                    ((uint8)(SLBR_GET_BIT_8BIT_REG_MASK_U8 >> ((((regAddr) - (baseAddr)) & MODULO_4_BIT_MASK_U32) ^ SLBR_XOR_8BIT_REG_MASK_U8)))) != 0 ))
#else

    #define REG_GET_SOFT_LOCK8(baseAddr, regAddr, prot_mem)      ((uint8)0x0UL)
#endif /* (STD_ON == USER_MODE_REG_PROT_ENABLED) */

#if (STD_ON == USER_MODE_REG_PROT_ENABLED)

    #define REG_GET_SOFT_LOCK16(baseAddr, regAddr, prot_mem)                                                     \
            ((uint8)((RLM_REG_READ8(SLBR_ADDR32((baseAddr), (regAddr), (prot_mem))) &                              \
                    ((uint8)(SLBR_GET_BIT_16BIT_REG_MASK_U8 >> ((((regAddr) - (baseAddr)) & MODULO_4_BIT_MASK_U32) ^ SLBR_XOR_16BIT_REG_MASK_U8)))) != 0 ))
#else

    #define REG_GET_SOFT_LOCK16(baseAddr, regAddr, prot_mem)      ((uint8)0x0UL)
#endif /* (STD_ON == USER_MODE_REG_PROT_ENABLED) */

#if (STD_ON == USER_MODE_REG_PROT_ENABLED)

    #define REG_GET_SOFT_LOCK32(baseAddr, regAddr, prot_mem)                                                     \
            ((uint8)((RLM_REG_READ8(SLBR_ADDR32((baseAddr), (regAddr), (prot_mem))) &                              \
                    ((uint8)(SLBR_GET_BIT_32BIT_REG_MASK_U8 >> ((((regAddr) - (baseAddr)) & MODULO_4_BIT_MASK_U32) ^ SLBR_XOR_32BIT_REG_MASK_U8)))) != 0 ))
#else

    #define REG_GET_SOFT_LOCK32(baseAddr, regAddr, prot_mem)      ((uint8)0x0UL)
#endif /* (STD_ON == USER_MODE_REG_PROT_ENABLED) */

/**
* @brief      Sets one bit in a 8 bit register and locks the register automatically 
*
* @details    Clears first the corresponding soft lock bit and writes the REG_PROT mirrored value
*             of the register the bit belongs to, which automatically soft locks the register
*
* @param[in]  baseAddr - base address of the IP the bit belongs to 
* @param[in]  regAddr  - address of the register the bit belongs to
* @param[in]  prot_mem - protection size of the IP
* @param[in]  mask     - 8 bit mask of the bit
*
* @return     void
*/
#if (STD_ON == USER_MODE_REG_PROT_ENABLED)

    #define REG_BIT_SET_LOCK8(baseAddr, regAddr, prot_mem, mask)                        \
        {                                                                               \
            REG_CLR_SOFT_LOCK8((baseAddr), (regAddr), (prot_mem));                       \
            RLM_REG_BIT_SET8((regAddr) + ((prot_mem) * MIRRORED_ADDR_OFFSET_U32),(mask));   \
        }
#else

    #define REG_BIT_SET_LOCK8(baseAddr, regAddr, prot_mem, mask)                        \
        RLM_REG_BIT_SET8((regAddr),(mask))
#endif /* (STD_ON == USER_MODE_REG_PROT_ENABLED) */

/**
* @brief      Sets one bit in a 16 bit register and locks the register automatically 
*
* @details    Clears first the corresponding soft lock bit and writes the REG_PROT mirrored value
*             of the register the bit belongs to, which automatically soft locks the register
*
* @param[in]  baseAddr - base address of the IP the bit belongs to 
* @param[in]  regAddr  - address of the register the bit belongs to
* @param[in]  prot_mem - protection size of the IP
* @param[in]  mask     - 8 bit mask of the bit
*
* @return     void
*/
#if (STD_ON == USER_MODE_REG_PROT_ENABLED)

    #define REG_BIT_SET_LOCK16(baseAddr, regAddr, prot_mem, mask)                         \
        {                                                                                 \
            REG_CLR_SOFT_LOCK16((baseAddr), (regAddr), (prot_mem));                         \
            RLM_REG_BIT_SET16((regAddr) + ((prot_mem) * MIRRORED_ADDR_OFFSET_U32),(mask));    \
        } 
#else

    #define REG_BIT_SET_LOCK16(baseAddr, regAddr, prot_mem, mask)                         \
        RLM_REG_BIT_SET16((regAddr),(mask))
#endif /* (STD_ON == USER_MODE_REG_PROT_ENABLED) */

/**
* @brief      Sets one bit in a 32 bit register and locks the register automatically 
*
* @details    Clears first the corresponding soft lock bit and writes the REG_PROT mirrored value
*             of the register the bit belongs to, which automatically soft locks the register
*
* @param[in]  baseAddr - base address of the IP the bit belongs to 
* @param[in]  regAddr  - address of the register the bit belongs to
* @param[in]  prot_mem - protection size of the IP
* @param[in]  mask     - 8 bit mask of the bit
*
* @return     void
*/
#if (STD_ON == USER_MODE_REG_PROT_ENABLED)

    #define REG_BIT_SET_LOCK32(baseAddr, regAddr, prot_mem, mask)                         \
        {                                                                                 \
            REG_CLR_SOFT_LOCK32((baseAddr), (regAddr), (prot_mem));                         \
            RLM_REG_BIT_SET32((regAddr) + ((prot_mem) * MIRRORED_ADDR_OFFSET_U32),(mask));    \
        }
#else

    #define REG_BIT_SET_LOCK32(baseAddr, regAddr, prot_mem, mask)                         \
        RLM_REG_BIT_SET32((regAddr),(mask))
#endif /* (STD_ON == USER_MODE_REG_PROT_ENABLED) */

/**
* @brief      Clears one bit in a 8 bit register and locks the register automatically 
*
* @details    Clears first the corresponding soft lock bit and writes the REG_PROT mirrored value
*             of the register the bit belongs to, which automatically soft locks the register
*
* @param[in]  baseAddr - base address of the IP the bit belongs to 
* @param[in]  regAddr  - address of the register the bit belongs to
* @param[in]  prot_mem - protection size of the IP
* @param[in]  mask     - 8 bit mask of the bit
*
* @return     void
*/
#if (STD_ON == USER_MODE_REG_PROT_ENABLED)

    #define REG_BIT_CLEAR_LOCK8(baseAddr, regAddr, prot_mem, mask)                                 \
        {                                                                                          \
            REG_CLR_SOFT_LOCK8((baseAddr), (regAddr), (prot_mem));                                  \
            RLM_REG_BIT_CLEAR8((regAddr) + ((prot_mem) * MIRRORED_ADDR_OFFSET_U32),(mask));            \
        }
#else

    #define REG_BIT_CLEAR_LOCK8(baseAddr, regAddr, prot_mem, mask)                                 \
        RLM_REG_BIT_CLEAR8((regAddr),(mask))
#endif /* (STD_ON == USER_MODE_REG_PROT_ENABLED) */

/**
* @brief      Clears one bit in a 16 bit register and locks the register automatically 
*
* @details    Clears first the corresponding soft lock bit and writes the REG_PROT mirrored value
*             of the register the bit belongs to, which automatically soft locks the register
*
* @param[in]  baseAddr - base address of the IP the bit belongs to 
* @param[in]  regAddr  - address of the register the bit belongs to
* @param[in]  prot_mem - protection size of the IP
* @param[in]  mask     - 8 bit mask of the bit
*
* @return     void
*/
#if (STD_ON == USER_MODE_REG_PROT_ENABLED)

    #define REG_BIT_CLEAR_LOCK16(baseAddr, regAddr, prot_mem, mask)                                \
        {                                                                                          \
            REG_CLR_SOFT_LOCK16((baseAddr), (regAddr), (prot_mem));                                  \
            RLM_REG_BIT_CLEAR16((regAddr) + ((prot_mem) * MIRRORED_ADDR_OFFSET_U32),(mask));           \
        }
#else

    #define REG_BIT_CLEAR_LOCK16(baseAddr, regAddr, prot_mem, mask)                                \
        RLM_REG_BIT_CLEAR16((regAddr),(mask))                                  
#endif /* (STD_ON == USER_MODE_REG_PROT_ENABLED) */

/**
* @brief      Clears one bit in a 32 bit register and locks the register automatically 
*
* @details    Clears first the corresponding soft lock bit and writes the REG_PROT mirrored value
*             of the register the bit belongs to, which automatically soft locks the register
*
* @param[in]  baseAddr - base address of the IP the bit belongs to 
* @param[in]  regAddr  - address of the register the bit belongs to
* @param[in]  prot_mem - protection size of the IP
* @param[in]  mask     - 8 bit mask of the bit
*
* @return     void
*/
#if (STD_ON == USER_MODE_REG_PROT_ENABLED)

    #define REG_BIT_CLEAR_LOCK32(baseAddr, regAddr, prot_mem, mask)                                \
        {                                                                                          \
            REG_CLR_SOFT_LOCK32((baseAddr), (regAddr), (prot_mem));                                  \
            RLM_REG_BIT_CLEAR32((regAddr) + ((prot_mem) * MIRRORED_ADDR_OFFSET_U32),(mask));           \
        }
#else

    #define REG_BIT_CLEAR_LOCK32(baseAddr, regAddr, prot_mem, mask)                                \
        RLM_REG_BIT_CLEAR32((regAddr),(mask))
#endif /* (STD_ON == USER_MODE_REG_PROT_ENABLED) */

/**
* @brief      Writes the content of a 8 bit register and locks it automatically 
*
* @details    Clears first the corresponding soft lock bit and writes the REG_PROT mirrored value
*             of the register, which automatically soft locks the register
*
* @param[in]  baseAddr - base address of the IP the register belongs to 
* @param[in]  regAddr  - address of the register to write and soft lock
* @param[in]  prot_mem - protection size of the IP
* @param[in]  value    - 8 bit value the register will be written with 
*
* @return     void
*/
#if (STD_ON == USER_MODE_REG_PROT_ENABLED)

    #define REG_WRITE_LOCK8(baseAddr, regAddr, prot_mem, value)                            \
        {                                                                                  \
            REG_CLR_SOFT_LOCK8((baseAddr), (regAddr), (prot_mem));                          \
            RLM_REG_WRITE8(((regAddr) + ((prot_mem) * MIRRORED_ADDR_OFFSET_U32)), (value));    \
        }
#else

    #define REG_WRITE_LOCK8(baseAddr, regAddr, prot_mem, value)                            \
        RLM_REG_WRITE8((regAddr), (value))
#endif /* (STD_ON == USER_MODE_REG_PROT_ENABLED) */

/**
* @brief      Writes the content of a 16 bit register and locks it automatically 
*
* @details    Clears first the corresponding soft lock bit and writes the REG_PROT mirrored value
*             of the register, which automatically soft locks the register
*
* @param[in]  baseAddr - base address of the IP the register belongs to 
* @param[in]  regAddr  - address of the register to write and soft lock
* @param[in]  prot_mem - protection size of the IP
* @param[in]  value    - 16 bit value the register will be written with 
*
* @return     void
*/
#if (STD_ON == USER_MODE_REG_PROT_ENABLED)

        #define REG_WRITE_LOCK16(baseAddr, regAddr, prot_mem, value)                         \
        {                                                                                    \
            REG_CLR_SOFT_LOCK16((baseAddr), (regAddr), (prot_mem));                            \
            RLM_REG_WRITE16(((regAddr) + ((prot_mem) * MIRRORED_ADDR_OFFSET_U32)), (value));     \
        }
#else

    #define REG_WRITE_LOCK16(baseAddr, regAddr, prot_mem, value)                             \
        RLM_REG_WRITE16((regAddr), (value))
#endif /* (STD_ON == USER_MODE_REG_PROT_ENABLED) */

/**
* @brief      Writes the content of a 32 bit register and locks it automatically 
*
* @details    Clears first the corresponding soft lock bit and writes the REG_PROT mirrored value
*             of the register, which automatically soft locks the register
*
* @param[in]  baseAddr - base address of the IP the register belongs to 
* @param[in]  regAddr  - address of the register to write and soft lock
* @param[in]  prot_mem - protection size of the IP
* @param[in]  value    - 32 bit value the register will be written with 
*
* @return     void
*/
#if (STD_ON == USER_MODE_REG_PROT_ENABLED)

    #define REG_WRITE_LOCK32(baseAddr, regAddr, prot_mem, value)                         \
    {                                                                                    \
        REG_CLR_SOFT_LOCK32((baseAddr), (regAddr), (prot_mem));                            \
        RLM_REG_WRITE32(((regAddr) + ((prot_mem) * MIRRORED_ADDR_OFFSET_U32)), (value));     \
    }
#else

    #define REG_WRITE_LOCK32(baseAddr, regAddr, prot_mem, value)                         \
        RLM_REG_WRITE32((regAddr), (value))
#endif /* (STD_ON == USER_MODE_REG_PROT_ENABLED) */


/**
* @brief      Clears the content of a 8 bit register, writes it with the value in
*             'value' parameter masked with the one in 'mask' parameter and locks 
*             it automatically 
*
* @details    Clears first the corresponding soft lock bit and writes the REG_PROT 
*             mirrored value of the register, which automatically soft locks the register
*
* @param[in]  baseAddr - base address of the IP the register belongs to 
* @param[in]  regAddr  - address of the register to write and soft lock
* @param[in]  prot_mem - protection size of the IP
* @param[in]  mask     - 8 bit mask the register will be written with 
* @param[in]  value    - 8 bit value the register will be written with 
*
* @return     void
*/
#if (STD_ON == USER_MODE_REG_PROT_ENABLED)

    #define REG_RMW_LOCK8(baseAddr, regAddr, prot_mem, mask, value)                          \
    {                                                                                        \
        REG_CLR_SOFT_LOCK8((baseAddr), (regAddr), (prot_mem));                                \
        RLM_REG_RMW8((regAddr) + ((prot_mem) * MIRRORED_ADDR_OFFSET_U32), (mask), (value));      \
    }
#else

    #define REG_RMW_LOCK8(baseAddr, regAddr, prot_mem, mask, value)                          \
        RLM_REG_RMW8((regAddr), (mask), (value))
#endif /* (STD_ON == USER_MODE_REG_PROT_ENABLED) */


/**
* @brief      Clears the content of a 16 bit register, writes it with the value in
*             'value' parameter masked with the one in 'mask' parameter and locks 
*             it automatically 
*
* @details    Clears first the corresponding soft lock bit and writes the REG_PROT 
*             mirrored value of the register, which automatically soft locks the register
*
* @param[in]  baseAddr - base address of the IP the register belongs to 
* @param[in]  regAddr  - address of the register to write and soft lock
* @param[in]  prot_mem - protection size of the IP
* @param[in]  mask     - 16 bit mask the register will be written with 
* @param[in]  value    - 16 bit value the register will be written with 
*
* @return     void
*/

#if (STD_ON == USER_MODE_REG_PROT_ENABLED)
    
    #define REG_RMW_LOCK16(baseAddr, regAddr, prot_mem, mask, value)                         \
    {                                                                                        \
        REG_CLR_SOFT_LOCK16((baseAddr), (regAddr), (prot_mem));                                \
        RLM_REG_RMW16((regAddr) + ((prot_mem) * MIRRORED_ADDR_OFFSET_U32), (mask), (value));     \
    }
#else
    
    #define REG_RMW_LOCK16(baseAddr, regAddr, prot_mem, mask, value)                         \
        RLM_REG_RMW16((regAddr), (mask), (value))
#endif /* (STD_ON == USER_MODE_REG_PROT_ENABLED) */

/**
* @brief      Clears the content of a 32 bit register, writes it with the value in
*             'value' parameter masked with the one in 'mask' parameter and locks 
*             it automatically 
*
* @details    Clears first the corresponding soft lock bit and writes the REG_PROT 
*             mirrored value of the register, which automatically soft locks the register
*
* @param[in]  baseAddr - base address of the IP the register belongs to 
* @param[in]  regAddr  - address of the register to write and soft lock
* @param[in]  prot_mem - protection size of the IP
* @param[in]  mask     - 32 bit mask the register will be written with 
* @param[in]  value    - 32 bit value the register will be written with 
*
* @return     void
*/
#if (STD_ON == USER_MODE_REG_PROT_ENABLED)

    #define REG_RMW_LOCK32(baseAddr, regAddr, prot_mem, mask, value)                         \
    {                                                                                        \
        REG_CLR_SOFT_LOCK32((baseAddr), (regAddr), (prot_mem));                                \
        RLM_REG_RMW32((regAddr) + ((prot_mem) * MIRRORED_ADDR_OFFSET_U32), (mask), (value));     \
    }
#else

    #define REG_RMW_LOCK32(baseAddr, regAddr, prot_mem, mask, value)                         \
        RLM_REG_RMW32((regAddr), (mask), (value))
#endif /* (STD_ON == USER_MODE_REG_PROT_ENABLED) */

/**
* @brief      Sets the hardlock bit of an IP module 
*
* @param[in]  baseAddr - base address of the IP to be hard locked 
* @param[in]  prot_mem - the protection size of the IP
*
* @return     void
*/
#define SET_HARD_LOCK(baseAddr, prot_mem)  \
        RLM_REG_BIT_SET32((baseAddr) + ((prot_mem) * GCR_OFFSET_U32), REGPROT_GCR_HLB_MASK_U32)


/**
* @brief      Reads the Hard Lock bit of an IP module 
*
* @param[in]  baseAddr - base address of the IP for which hard lock status is read 
* @param[in]  prot_mem - the protection size of the IP
*
* @return     uint8  - 1 if hard lock is enabled
*                    - 0 if hard lock is disabled
*/
#define GET_HARD_LOCK(baseAddr, prot_mem)  \
        ((uint8)(RLM_REG_BIT_GET32((baseAddr) + ((prot_mem) * GCR_OFFSET_U32), REGPROT_GCR_HLB_MASK_U32) >> REGPROT_GCR_HLB_POS_U32))

/**
* @brief      Sets the User Access Allowed bit of an IP module 
*
* @param[in]  baseAddr - base address of the IP for which UAA bit is set 
* @param[in]  prot_mem - the protection size of the IP
*
* @return     void
*/
#ifdef IPV_REG_PROT
    #if (IPV_S32S2XX_PLATFORM_U32 == IPV_GET_PLATFORM_U32(IPV_REG_PROT))
    
        #define SET_USER_ACCESS_ALLOWED(baseAddr, prot_mem )  \
                RLM_REG_BIT_SET32((baseAddr) + ((prot_mem) * (((baseAddr) >= 0x55600000UL) ? (GCR_AE_OFFSET_U32) : (GCR_OFFSET_U32))), REGPROT_GCR_UAA_MASK_U32)
    #else
    
        #define SET_USER_ACCESS_ALLOWED(baseAddr, prot_mem )  \
                RLM_REG_BIT_SET32((baseAddr) + ((prot_mem) * GCR_OFFSET_U32), REGPROT_GCR_UAA_MASK_U32)
    #endif
#else

    #define SET_USER_ACCESS_ALLOWED(baseAddr, prot_mem )  \
            RLM_REG_BIT_SET32((baseAddr) + ((prot_mem) * GCR_OFFSET_U32), REGPROT_GCR_UAA_MASK_U32)
#endif

/**
* @brief      Clears the User Access Allowed bit of an IP module 
*
* @param[in]  baseAddr - base address of the IP for which UAA bit is cleared 
* @param[in]  prot_mem - the protection size of the IP
*
* @return     void
*/
#ifdef IPV_REG_PROT

    #if (IPV_S32S2XX_PLATFORM_U32 == IPV_GET_PLATFORM_U32(IPV_REG_PROT))
    
        #define CLR_USER_ACCESS_ALLOWED(baseAddr, prot_mem)  \
                RLM_REG_BIT_CLEAR32((baseAddr) + ((prot_mem) * (((baseAddr) >= 0x55600000UL) ? (GCR_AE_OFFSET_U32) : (GCR_OFFSET_U32))), REGPROT_GCR_UAA_MASK_U32)
    #else
    
        #define CLR_USER_ACCESS_ALLOWED(baseAddr, prot_mem)  \
                RLM_REG_BIT_CLEAR32((baseAddr) + ((prot_mem) * GCR_OFFSET_U32), REGPROT_GCR_UAA_MASK_U32)
    #endif
#else

    #define CLR_USER_ACCESS_ALLOWED(baseAddr, prot_mem)  \
            RLM_REG_BIT_CLEAR32((baseAddr) + ((prot_mem) * GCR_OFFSET_U32), REGPROT_GCR_UAA_MASK_U32)
#endif

/**
* @brief      Reads the User Access Allowed bit of an IP module 
*
* @param[in]  baseAddr - base address of the IP for which UAA is read 
* @param[in]  prot_mem - the protection size of the IP
*
* @return     uint8  - 1 if User Access Allow is enabled
*                    - 0 if User Access Allow is disabled
*/
#ifdef IPV_REG_PROT
    #if (IPV_S32S2XX_PLATFORM_U32 == IPV_GET_PLATFORM_U32(IPV_REG_PROT))
    
        #define GET_USER_ACCESS_ALLOWED(baseAddr, prot_mem)  \
                ((uint8)(RLM_REG_BIT_GET32((baseAddr) + ((prot_mem) * (((baseAddr) >= 0x55600000UL) ? (GCR_AE_OFFSET_U32) : (GCR_OFFSET_U32))), REGPROT_GCR_UAA_MASK_U32) >> REGPROT_GCR_UAA_POS_U32))
    #else
    
        #define GET_USER_ACCESS_ALLOWED(baseAddr, prot_mem)  \
                ((uint8)(RLM_REG_BIT_GET32((baseAddr) + ((prot_mem) * GCR_OFFSET_U32), REGPROT_GCR_UAA_MASK_U32) >> REGPROT_GCR_UAA_POS_U32))
    #endif
#else

    #define GET_USER_ACCESS_ALLOWED(baseAddr, prot_mem)  \
            ((uint8)(RLM_REG_BIT_GET32((baseAddr) + ((prot_mem) * GCR_OFFSET_U32), REGPROT_GCR_UAA_MASK_U32) >> REGPROT_GCR_UAA_POS_U32))
#endif

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

#endif /* #ifndef REGLOCKMACROS_H */

/** @} */
