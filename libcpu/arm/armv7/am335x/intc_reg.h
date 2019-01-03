//////////////////////////////////////////////////////////////////////////
/// @file intc_reg.h
//////////////////////////////////////////////////////////////////////////

#ifndef __INTC_REG_H__
#define __INTC_REG_H__

#include <regopr.h>

#define INTC___G___(ofs)                                REG32___G___(0x48200000 + (ofs))
#define INTC_M_G___(ofs, mask)                          REG32_M_G___(0x48200000 + (ofs), mask)
#define INTC_M_S___(ofs, mask, val)                     REG32_M_S___(0x48200000 + (ofs), mask, val)
#define INTC___S___(ofs, val)                           REG32___S___(0x48200000 + (ofs), val)
#define INTC_____WA(ofs, val)                           REG32_____WA(0x48200000 + (ofs), val)
#define INTC_____WZ(ofs)                                REG32_____WZ(0x48200000 + (ofs))
#define INTC_M___WA(ofs, mask, val)                     REG32_M___WA(0x48200000 + (ofs), mask, val)
#define INTC_M___WZ(ofs, mask)                          REG32_M___WZ(0x48200000 + (ofs), mask)
#define INTC_M_S_WA(ofs, mask, val)                     REG32_M_S_WA(0x48200000 + (ofs), mask, val)
#define INTC_M_S_WZ(ofs, mask, val)                     REG32_M_S_WZ(0x48200000 + (ofs), mask, val)
#define INTC_M___W1(ofs, mask)                          REG32_M___W1(0x48200000 + (ofs), mask)
#define INTC_M_S_W1(ofs, mask, val)                     REG32_M_S_W1(0x48200000 + (ofs), mask, val)

#endif // __INTC_REG_H__
