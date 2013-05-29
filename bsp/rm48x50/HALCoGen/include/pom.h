/** @file pom.h
*   @brief POM Driver Definition File
*   @date 29.May.2013
*   @version 03.05.02
*   
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

#ifndef __POM_H__
#define __POM_H__

#include "reg_pom.h"



/* USER CODE BEGIN (0) */
/* USER CODE END */


/** @enum pom_region_size
*   @brief Alias names for pom region size
*   This enumeration is used to provide alias names for POM region size:
*/
enum pom_region_size
{
        SIZE_32BYTES    = 0U,
        SIZE_64BYTES    = 1U,
        SIZE_128BYTES   = 2U,
        SIZE_256BYTES   = 3U,
        SIZE_512BYTES   = 4U,
        SIZE_1KB        = 5U,
        SIZE_2KB        = 6U,
        SIZE_4KB        = 7U,
        SIZE_8KB        = 8U,
        SIZE_16KB       = 9U,
        SIZE_32KB       = 10U,
        SIZE_64KB       = 11U,
        SIZE_128KB      = 12U,
        SIZE_256KB      = 13U
};

/** @def INTERNAL_RAM 
*   @brief Alias name for Internal RAM
*/   
#define INTERNAL_RAM    0x08000000U

/** @def SDRAM 
*   @brief Alias name for SD RAM
*/   
#define SDRAM   0x80000000U

/** @def ASYNC_MEMORY 
*   @brief Alias name for Async RAM
*/   
#define ASYNC_MEMORY   0x60000000U


typedef uint32 REGION_t;

/** @struct REGION_CONFIG_ST
*   @brief POM region configuration
*/
typedef struct
{       
        uint32 Prog_Reg_Sta_Addr;
        uint32 Ovly_Reg_Sta_Addr;
        uint32 Reg_Size;
}REGION_CONFIG_t;

/* USER CODE BEGIN (1) */
/* USER CODE END */

/** 
 *  @defgroup POM POM
 *  @brief Parameter Overlay Module.
 *  
 *  The POM provides a mechanism to redirect accesses to non-volatile memory into a volatile memory
 *  internal or external to the device. The data requested by the CPU will be fetched from the overlay memory
 *  instead of the main non-volatile memory.
 *
 *	Related Files
 *   - reg_pom.h
 *   - pom.h
 *   - pom.c
 *  @addtogroup POM
 *  @{
 */
 
/* POM Interface Functions */
void POM_Region_Config(REGION_CONFIG_t *Reg_Config_Ptr,REGION_t Region_Num);
void POM_Reset(void);
void POM_Init(void);
void POM_Disable(void);

/**@}*/
#endif /* __POM_H_*/
