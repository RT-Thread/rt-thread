#if defined(START_FROM_FLASH)
#include "typedefs.h"

#define MPC56xx_ID    0x005A0000  /* RCHW boot ID for MPC56xx devices     */
#define VLE_ENABLE    0x01000000  /* VLE is enabled                       */

extern void _start(void);
#define ENTRY_POINT  _start
#define RCHW_VAL (VLE_ENABLE | MPC56xx_ID)

const uint32_t __attribute__ ((section(".rchw"))) RCHW[] = {RCHW_VAL, (uint32_t)ENTRY_POINT};

#endif /* defined(START_FROM_FLASH) */






