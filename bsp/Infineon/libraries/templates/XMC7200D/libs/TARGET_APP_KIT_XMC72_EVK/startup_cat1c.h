#ifndef __STARTUP_CAT1C_H__
#define __STARTUP_CAT1C_H__

#define FIXED_EXP_NR            (15u)
#define VECTORTABLE_SIZE        (16u + FIXED_EXP_NR + 1u) /* +1 is for Stack pointer */
#define VECTORTABLE_ALIGN       (128) /* alignment for 85 entries (32x4=128) is 2^7=128 bytes */


#endif /* __STARTUP_CAT1C_H__ */
