#ifndef BSP_FREEZE_H
#define BSP_FREEZE_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

#if BSP_MCU_GROUP_RA6B1
 #include "../ra6b1/bsp_freeze.h"
#elif BSP_MCU_GROUP_RA6U1
 #include "../ra6u1/bsp_freeze.h"
#elif BSP_MCU_GROUP_RA6W1
 #include "../ra6w1/bsp_freeze.h"
#elif BSP_MCU_GROUP_RA6B2
 #include "../ra6b2/bsp_freeze.h"
#elif BSP_MCU_GROUP_RA6W3
 #include "../ra6w3/bsp_freeze.h"
#endif

#endif
