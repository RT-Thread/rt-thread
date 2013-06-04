/** @file reg_pom.h
*   @brief POM Register Layer Header File
*   @date 29.May.2013
*   @version 03.05.02
*   
*   This file contains:
*   - Definitions
*   - Types
*   - Interface Prototypes
*   .
*   which are relevant for the POM driver.
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

#ifndef __REG_POM_H__
#define __REG_POM_H__

#include "sys_common.h"



/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Pom Register Frame Definition */
/** @struct POMBase
*   @brief POM Register Frame Definition
*
*   This structure is used to access the POM module registers(POM Register Map).
*/
typedef struct
{
  uint32 POMGLBCTRL_UL;   /* 0x00      */
  uint32 POMREV_UL;       /* 0x04      */
  uint32 POMCLKCTRL_UL;   /* 0x08      */
  uint32 POMFLG_UL;       /* 0x0C      */
  struct
  {
    uint32   rsdv1;
  }RESERVED_REG[124U];
  struct                    /* 0x200 ...    */
  {
    uint32 POMPROGSTART_UL; 
    uint32 POMOVLSTART_UL; 
    uint32 POMREGSIZE_UL; 
    uint32   rsdv2; 
  }POMRGNCONF_ST[32U];
}pomBASE_t;


/** @struct POM_CORESIGHT_ST
*   @brief POM_CORESIGHT_ST Register Definition
*
*   This structure is used to access the POM module registers(POM CoreSight Registers ).
*/
typedef struct
{
    uint32 POMITCTRL_UL;                  /* 0xF00            */
    struct                                  /* 0xF04 to 0xF9C   */                     
    {
        uint32 Reserved_Reg_UL;
    }Reserved1_ST[39U];
    uint32 POMCLAIMSET_UL;                /* 0xFA0      */
    uint32 POMCLAIMCLR_UL;                /* 0xFA4      */
    uint32   rsvd1[2U];                    /* 0xFA8      */
    uint32 POMLOCKACCESS_UL;              /* 0xFB0      */
    uint32 POMLOCKSTATUS_UL;              /* 0xFB4      */
    uint32 POMAUTHSTATUS_UL;              /* 0xFB8      */
    uint32   rsvd2[3U];                    /* 0xFBC      */
    uint32 POMDEVID_UL;                   /* 0xFC8      */
    uint32 POMDEVTYPE_UL;                 /* 0xFCC      */
    uint32 POMPERIPHERALID4_UL;           /* 0xFD0      */
    uint32 POMPERIPHERALID5_UL;           /* 0xFD4      */
    uint32 POMPERIPHERALID6_UL;           /* 0xFD8      */
    uint32 POMPERIPHERALID7_UL;           /* 0xFDC      */
    uint32 POMPERIPHERALID0_UL;           /* 0xFE0      */
    uint32 POMPERIPHERALID1_UL;           /* 0xFE4      */
    uint32 POMPERIPHERALID2_UL;           /* 0xFE8      */
    uint32 POMPERIPHERALID3_UL;           /* 0xFEC      */            
    uint32 POMCOMPONENTID0_UL;            /* 0xFF0      */
    uint32 POMCOMPONENTID1_UL;            /* 0xFF4      */
    uint32 POMCOMPONENTID2_UL;            /* 0xFF8      */
    uint32 POMCOMPONENTID3_UL;            /* 0xFFC      */
}POM_CORESIGHT_ST;


#define pomREG ((pomBASE_t *)0xFFA04000U)

/* USER CODE BEGIN (1) */
/* USER CODE END */


#endif
