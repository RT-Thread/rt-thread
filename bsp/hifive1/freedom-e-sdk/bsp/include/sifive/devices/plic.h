// See LICENSE for license details.

#ifndef PLIC_H
#define PLIC_H

#include <sifive/const.h>

// 32 bits per source
#define PLIC_PRIORITY_OFFSET            _AC(0x0000,UL)
#define PLIC_PRIORITY_SHIFT_PER_SOURCE  2
// 1 bit per source (1 address)
#define PLIC_PENDING_OFFSET             _AC(0x1000,UL)
#define PLIC_PENDING_SHIFT_PER_SOURCE   0

//0x80 per target
#define PLIC_ENABLE_OFFSET              _AC(0x2000,UL)
#define PLIC_ENABLE_SHIFT_PER_TARGET    7


#define PLIC_THRESHOLD_OFFSET           _AC(0x200000,UL)
#define PLIC_CLAIM_OFFSET               _AC(0x200004,UL)
#define PLIC_THRESHOLD_SHIFT_PER_TARGET 12
#define PLIC_CLAIM_SHIFT_PER_TARGET     12

#define PLIC_MAX_SOURCE                 1023
#define PLIC_SOURCE_MASK                0x3FF

#define PLIC_MAX_TARGET                 15871
#define PLIC_TARGET_MASK                0x3FFF

#endif /* PLIC_H */
