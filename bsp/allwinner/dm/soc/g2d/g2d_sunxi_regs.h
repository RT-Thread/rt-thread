/*
 * Copyright (c) 2026 Yuzuki Tsuru
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
 */

/*
 * Register map of the Allwinner G2D.
 *
 * The block is programmed through a register command queue (RCQ): a list of
 * { memory block, register offset, length } entries that the hardware copies
 * into its register file before it runs. Only the control registers at the
 * top are written by the CPU.
 */

#ifndef G2D_SUNXI_REGS_H_
#define G2D_SUNXI_REGS_H_
#include <drivers/misc.h>

/* ---- control registers (CPU) ------------------------------------------ */

#define G2D_RESET                        0x010
#define G2D_RESET_CORE                   RT_BIT(0)
#define G2D_RESET_THREAD(n)              RT_BIT(16 + 4 * (n))
#define G2D_CLK_GATE                     0x014
#define G2D_CLK_GATE_CORE                RT_BIT(0)
#define G2D_CLK_GATE_THREAD(n)           RT_BIT(16 + 4 * (n))
#define G2D_MBUS_GATE                    0x018
#define G2D_MBUS_GATE_CLK                RT_BIT(0)
#define G2D_MBUS_GATE_RESET              RT_BIT(16)
#define G2D_MODE                         0x020
#define G2D_MODE_MASTER                  RT_BIT(0)
#define G2D_CORE_STATUS                  0x028
#define G2D_CORE_STATUS_BUSY             RT_BIT(28)

/* internal cache and bandwidth limiter */
#define G2D_CACHE_CTRL                   0x050
#define G2D_CACHE_CTRL_EN                RT_BIT(16)
#define G2D_CACHE_SIZE0                  0x054
#define G2D_CACHE_SIZE1                  0x058
#define G2D_CACHE_SIZE_MASK              RT_GENMASK(7, 0)
#define G2D_DDR_LIMIT                    0x064
#define G2D_DDR_LIMIT_EN                 RT_BIT(16)
#define G2D_DDR_LIMIT_MASK               RT_GENMASK(8, 0)

/* RCQ thread n */
#define G2D_THREAD(n)                    (0x100 + 0x40 * (n))
#define G2D_THREAD_IRQ_EN                0x00
#define G2D_THREAD_IRQ_STATUS            0x04
#define G2D_THREAD_IRQ_TASK_END          RT_BIT(0)
#define G2D_THREAD_IRQ_RCQ_ACCEPT        RT_BIT(4)
#define G2D_THREAD_IRQ_TIMEOUT           RT_BIT(8)
#define G2D_THREAD_HEAD_LOW              0x10
#define G2D_THREAD_HEAD_HIGH_LEN         0x14
#define G2D_THREAD_HEAD_HIGH_MASK        RT_GENMASK(7, 0)
#define G2D_THREAD_HEAD_LEN_MASK         RT_GENMASK(31, 16)
#define G2D_THREAD_ATTR                  0x18
#define G2D_THREAD_ATTR_CMD_NUM_MASK     RT_GENMASK(11, 0) /* commands - 1 */
#define G2D_THREAD_ATTR_END_IRQ          RT_BIT(16)
#define G2D_THREAD_UPDATE                0x1c

/* ---- register blocks written through the RCQ --------------------------- */

/* engine select: the mixer pipeline or the rotate engine */
#define G2D_CORE_CTRL                    0x300
#define G2D_CORE_CTRL_SIZE               0x04
#define G2D_CORE_CTRL_MIXER              RT_BIT(0)
#define G2D_CORE_CTRL_ROTATE             RT_BIT(4)

/* V0: video overlay (scalable, YUV capable) */
#define G2D_V0                           0x0800
#define G2D_V0_SIZE                      0x40
/* UI overlays */
#define G2D_UI(n)                        (0x1000 + 0x800 * (n))
#define G2D_UI_SIZE                      0x20

/* overlay registers, V0 and UI share the leading ones */
#define G2D_OVL_ATTR                     0x00
#define G2D_OVL_ATTR_EN                  RT_BIT(0)
#define G2D_OVL_ATTR_ALPHA_MODE_MASK     RT_GENMASK(2, 1)
#define G2D_OVL_ATTR_FILL_EN             RT_BIT(4)
#define G2D_OVL_ATTR_FORMAT_MASK         RT_GENMASK(13, 8)
#define G2D_OVL_ATTR_PREMUL              RT_BIT(16)
#define G2D_OVL_ATTR_ALPHA_MASK          RT_GENMASK(31, 24)
#define G2D_OVL_MEM_SIZE                 0x04 /* (h - 1) << 16 | (w - 1) */
#define G2D_OVL_COOR                     0x08
#define G2D_OVL_PITCH0                   0x0c
/* V0 */
#define G2D_V0_PITCH1                    0x10
#define G2D_V0_PITCH2                    0x14
#define G2D_V0_ADDR(p)                   (0x18 + 4 * (p))
#define G2D_V0_FILL                      0x24
#define G2D_V0_ADDR_HIGH                 0x28
#define G2D_V0_WIN_SIZE                  0x2c
#define G2D_V0_HDS0                      0x30 /* coarse down sampling */
#define G2D_V0_HDS1                      0x34
#define G2D_V0_VDS0                      0x38
#define G2D_V0_VDS1                      0x3c
/* UI */
#define G2D_UI_ADDR                      0x10
#define G2D_UI_FILL                      0x14
#define G2D_UI_ADDR_HIGH                 0x18
#define G2D_UI_WIN_SIZE                  0x1c

/* blender */
#define G2D_BLD                          0x0400
#define G2D_BLD_SIZE                     0x1a0
#define G2D_BLD_EN                       0x00
#define G2D_BLD_EN_P0_FILL               RT_BIT(0)
#define G2D_BLD_EN_P1_FILL               RT_BIT(1)
#define G2D_BLD_EN_P0                    RT_BIT(8)
#define G2D_BLD_EN_P1                    RT_BIT(9)
#define G2D_BLD_FILL_COLOR(p)            (0x10 + 4 * (p))
#define G2D_BLD_PIPE_SIZE(p)             (0x20 + 4 * (p))
#define G2D_BLD_PIPE_COOR(p)             (0x30 + 4 * (p))
#define G2D_BLD_PREMUL                   0x40
#define G2D_BLD_BKCOLOR                  0x44
#define G2D_BLD_OUT_SIZE                 0x48
#define G2D_BLD_CTRL                     0x4c
#define G2D_BLD_CK                       0x50
#define G2D_BLD_CK_EN                    RT_BIT(0)
#define G2D_BLD_CK_DIR_MASK              RT_GENMASK(2, 1)
#define G2D_BLD_CK_CFG                   0x54
#define G2D_BLD_CK_MAX                   0x58
#define G2D_BLD_CK_MIN                   0x5c
#define G2D_BLD_OUT_COLOR                0x60
#define G2D_BLD_OUT_PREMUL               RT_BIT(0)
#define G2D_BLD_OUT_YUV                  RT_BIT(1)
#define G2D_BLD_ROP_CTRL                 0x80
#define G2D_BLD_ROP_INDEX0               0x84
#define G2D_BLD_CSC_CTRL                 0x100
#define G2D_BLD_CSC_EN(n)                RT_BIT(n)
#define G2D_BLD_CSC(n)                   (0x110 + 0x30 * (n))

/* write back */
#define G2D_WB                           0x3000
#define G2D_WB_SIZE                      0x2c
#define G2D_WB_ATTR                      0x00
#define G2D_WB_ATTR_FORMAT_MASK          RT_GENMASK(5, 0)
#define G2D_WB_DATA_SIZE                 0x04
#define G2D_WB_PITCH(p)                  (0x08 + 4 * (p))
#define G2D_WB_ADDR(p)                   (0x14 + 8 * (p))
#define G2D_WB_ADDR_HIGH(p)              (0x18 + 8 * (p))

/* video scaler */
#define G2D_VSU                          0x8000
#define G2D_VSU_SIZE                     0x480
#define G2D_VSU_CTRL                     0x00
#define G2D_VSU_CTRL_EN                  RT_BIT(0)
#define G2D_VSU_CTRL_COEF_ACCESS         RT_BIT(8)
#define G2D_VSU_CTRL_FILTER_PLANAR       RT_BIT(16)
#define G2D_VSU_OUT_SIZE                 0x40
#define G2D_VSU_GLB_ALPHA                0x44
#define G2D_VSU_Y_SIZE                   0x80
#define G2D_VSU_Y_HSTEP                  0x88
#define G2D_VSU_Y_VSTEP                  0x8c
#define G2D_VSU_Y_HPHASE                 0x90
#define G2D_VSU_Y_VPHASE                 0x98
#define G2D_VSU_C_SIZE                   0xc0
#define G2D_VSU_C_HSTEP                  0xc8
#define G2D_VSU_C_VSTEP                  0xcc
#define G2D_VSU_C_HPHASE                 0xd0
#define G2D_VSU_C_VPHASE                 0xd8
#define G2D_VSU_Y_HCOEF                  0x200
#define G2D_VSU_Y_VCOEF                  0x300
#define G2D_VSU_C_HCOEF                  0x400

/* rotate engine */
#define G2D_ROT                          0x28000
#define G2D_ROT_SIZE                     0xb8
#define G2D_ROT_CTRL                     0x00
#define G2D_ROT_CTRL_MODE_MASK           RT_GENMASK(1, 0)
#define G2D_ROT_CTRL_DEGREE_MASK         RT_GENMASK(5, 4)
#define G2D_ROT_CTRL_VFLIP               RT_BIT(6)
#define G2D_ROT_CTRL_HFLIP               RT_BIT(7)
#define G2D_ROT_IN_FORMAT                0x20
#define G2D_ROT_IN_SIZE                  0x24
#define G2D_ROT_IN_PITCH(p)              (0x30 + 4 * (p))
#define G2D_ROT_IN_ADDR(p)               (0x40 + 8 * (p))
#define G2D_ROT_IN_ADDR_HIGH(p)          (0x44 + 8 * (p))
#define G2D_ROT_OUT_SIZE                 0x84
#define G2D_ROT_OUT_PITCH(p)             (0x90 + 4 * (p))
#define G2D_ROT_OUT_ADDR(p)              (0xa0 + 8 * (p))
#define G2D_ROT_OUT_ADDR_HIGH(p)         (0xa4 + 8 * (p))

/* width/height field pair shared by the size registers (value = size - 1) */
#define G2D_SIZE(w, h)                   ((((h) - 1) << 16) | ((w) - 1))

#endif /* G2D_SUNXI_REGS_H_ */
