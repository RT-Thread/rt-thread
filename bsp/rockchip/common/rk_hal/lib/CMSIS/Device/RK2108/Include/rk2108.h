/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2020-2021 Rockchip Electronics Co., Ltd.
 */

#ifndef __RK2108_H
#define __RK2108_H
#ifdef __cplusplus
  extern "C" {
#endif
/****************************************************************************************/
/*                                                                                      */
/*                               Module Structure Section                               */
/*                                                                                      */
/****************************************************************************************/
#ifndef __ASSEMBLY__
/* ICACHE Register Structure Define */
struct ICACHE_REG {
    __IO uint32_t CACHE_CTRL;                         /* Address Offset: 0x0000 */
    __IO uint32_t CACHE_MAINTAIN[2];                  /* Address Offset: 0x0004 */
    __IO uint32_t STB_TIMEOUT_CTRL;                   /* Address Offset: 0x000C */
         uint32_t RESERVED0010[4];                    /* Address Offset: 0x0010 */
    __IO uint32_t CACHE_INT_EN;                       /* Address Offset: 0x0020 */
    __IO uint32_t CACHE_INT_ST;                       /* Address Offset: 0x0024 */
    __IO uint32_t CACHE_ERR_HADDR;                    /* Address Offset: 0x0028 */
         uint32_t RESERVED002C;                       /* Address Offset: 0x002C */
    __I  uint32_t CACHE_STATUS;                       /* Address Offset: 0x0030 */
         uint32_t RESERVED0034[3];                    /* Address Offset: 0x0034 */
    __I  uint32_t PMU_RD_NUM_CNT;                     /* Address Offset: 0x0040 */
    __I  uint32_t PMU_WR_NUM_CNT;                     /* Address Offset: 0x0044 */
    __I  uint32_t PMU_SRAM_RD_HIT_CNT;                /* Address Offset: 0x0048 */
    __I  uint32_t PMU_HB_RD_HIT_CNT;                  /* Address Offset: 0x004C */
    __IO uint32_t PMU_STB_RD_HIT_CNT;                 /* Address Offset: 0x0050 */
    __I  uint32_t PMU_RD_HIT_CNT;                     /* Address Offset: 0x0054 */
    __I  uint32_t PMU_WR_HIT_CNT;                     /* Address Offset: 0x0058 */
    __I  uint32_t PMU_RD_MISS_PENALTY_CNT;            /* Address Offset: 0x005C */
    __I  uint32_t PMU_WR_MISS_PENALTY_CNT;            /* Address Offset: 0x0060 */
    __I  uint32_t PMU_RD_LAT_CNT;                     /* Address Offset: 0x0064 */
    __I  uint32_t PMU_WR_LAT_CNT;                     /* Address Offset: 0x0068 */
         uint32_t RESERVED006C[33];                   /* Address Offset: 0x006C */
    __IO uint32_t REVISION;                           /* Address Offset: 0x00F0 */
};
/* DCACHE Register Structure Define */
struct DCACHE_REG {
    __IO uint32_t CACHE_CTRL;                         /* Address Offset: 0x0000 */
    __IO uint32_t CACHE_MAINTAIN[2];                  /* Address Offset: 0x0004 */
    __IO uint32_t STB_TIMEOUT_CTRL;                   /* Address Offset: 0x000C */
         uint32_t RESERVED0010[4];                    /* Address Offset: 0x0010 */
    __IO uint32_t CACHE_INT_EN;                       /* Address Offset: 0x0020 */
    __IO uint32_t CACHE_INT_ST;                       /* Address Offset: 0x0024 */
    __IO uint32_t CACHE_ERR_HADDR;                    /* Address Offset: 0x0028 */
         uint32_t RESERVED002C;                       /* Address Offset: 0x002C */
    __I  uint32_t CACHE_STATUS;                       /* Address Offset: 0x0030 */
         uint32_t RESERVED0034[3];                    /* Address Offset: 0x0034 */
    __I  uint32_t PMU_RD_NUM_CNT;                     /* Address Offset: 0x0040 */
    __I  uint32_t PMU_WR_NUM_CNT;                     /* Address Offset: 0x0044 */
    __I  uint32_t PMU_SRAM_RD_HIT_CNT;                /* Address Offset: 0x0048 */
    __I  uint32_t PMU_HB_RD_HIT_CNT;                  /* Address Offset: 0x004C */
    __IO uint32_t PMU_STB_RD_HIT_CNT;                 /* Address Offset: 0x0050 */
    __I  uint32_t PMU_RD_HIT_CNT;                     /* Address Offset: 0x0054 */
    __I  uint32_t PMU_WR_HIT_CNT;                     /* Address Offset: 0x0058 */
    __I  uint32_t PMU_RD_MISS_PENALTY_CNT;            /* Address Offset: 0x005C */
    __I  uint32_t PMU_WR_MISS_PENALTY_CNT;            /* Address Offset: 0x0060 */
    __I  uint32_t PMU_RD_LAT_CNT;                     /* Address Offset: 0x0064 */
    __I  uint32_t PMU_WR_LAT_CNT;                     /* Address Offset: 0x0068 */
         uint32_t RESERVED006C[33];                   /* Address Offset: 0x006C */
    __IO uint32_t REVISION;                           /* Address Offset: 0x00F0 */
};
/* CRU Register Structure Define */
struct CRU_REG {
    __IO uint32_t GPLL_CON[3];                        /* Address Offset: 0x0000 */
         uint32_t RESERVED000C[5];                    /* Address Offset: 0x000C */
    __IO uint32_t CPLL_CON[5];                        /* Address Offset: 0x0020 */
         uint32_t RESERVED0034[3];                    /* Address Offset: 0x0034 */
    __IO uint32_t SPLL_CON[4];                        /* Address Offset: 0x0040 */
         uint32_t RESERVED0050[4];                    /* Address Offset: 0x0050 */
    __IO uint32_t CRU_MODE_CON00;                     /* Address Offset: 0x0060 */
         uint32_t RESERVED0064[7];                    /* Address Offset: 0x0064 */
    __IO uint32_t CRU_CLKSEL_CON[50];                 /* Address Offset: 0x0080 */
         uint32_t RESERVED0148[14];                   /* Address Offset: 0x0148 */
    __IO uint32_t CRU_CLKGATE_CON[15];                /* Address Offset: 0x0180 */
         uint32_t RESERVED01BC[17];                   /* Address Offset: 0x01BC */
    __IO uint32_t CRU_SOFTRST_CON[16];                /* Address Offset: 0x0200 */
         uint32_t RESERVED0240[48];                   /* Address Offset: 0x0240 */
    __IO uint32_t GLB_CNT_TH;                         /* Address Offset: 0x0300 */
    __IO uint32_t CRU_GLBRST_ST;                      /* Address Offset: 0x0304 */
    __IO uint32_t GLB_SRST_FST_VALUE;                 /* Address Offset: 0x0308 */
    __IO uint32_t GLB_SRST_SND_VALUE;                 /* Address Offset: 0x030C */
    __IO uint32_t GLB_RST_CON;                        /* Address Offset: 0x0310 */
         uint32_t RESERVED0314[3];                    /* Address Offset: 0x0314 */
    __IO uint32_t CRU_SDIO_CON[2];                    /* Address Offset: 0x0320 */
         uint32_t RESERVED0328[2];                    /* Address Offset: 0x0328 */
    __IO uint32_t DCG_CON[2][8];                      /* Address Offset: 0x0330 */
         uint32_t RESERVED0370[36];                   /* Address Offset: 0x0370 */
    __IO uint32_t AS_CON[5][2];                       /* Address Offset: 0x0400 */
};
/* GRF Register Structure Define */
struct GRF_REG {
    __IO uint32_t GPIO0A_IOMUX_L;                     /* Address Offset: 0x0000 */
    __IO uint32_t GPIO0A_IOMUX_H;                     /* Address Offset: 0x0004 */
    __IO uint32_t GPIO0B_IOMUX_L;                     /* Address Offset: 0x0008 */
    __IO uint32_t GPIO0B_IOMUX_H;                     /* Address Offset: 0x000C */
    __IO uint32_t GPIO0C_IOMUX_L;                     /* Address Offset: 0x0010 */
    __IO uint32_t GPIO0C_IOMUX_H;                     /* Address Offset: 0x0014 */
    __IO uint32_t GPIO0D_IOMUX_L;                     /* Address Offset: 0x0018 */
    __IO uint32_t GPIO0D_IOMUX_H;                     /* Address Offset: 0x001C */
    __IO uint32_t GPIO1A_IOMUX_L;                     /* Address Offset: 0x0020 */
    __IO uint32_t GPIO1A_IOMUX_H;                     /* Address Offset: 0x0024 */
    __IO uint32_t GPIO1B_IOMUX_L;                     /* Address Offset: 0x0028 */
    __IO uint32_t GPIO1B_IOMUX_H;                     /* Address Offset: 0x002C */
    __IO uint32_t GPIO1C_IOMUX_L;                     /* Address Offset: 0x0030 */
    __IO uint32_t GPIO1C_IOMUX_H;                     /* Address Offset: 0x0034 */
    __IO uint32_t GPIO1D_IOMUX_L;                     /* Address Offset: 0x0038 */
         uint32_t RESERVED003C;                       /* Address Offset: 0x003C */
    __IO uint32_t GPIO0L_SR;                          /* Address Offset: 0x0040 */
    __IO uint32_t GPIO0H_SR;                          /* Address Offset: 0x0044 */
    __IO uint32_t GPIO1L_SR;                          /* Address Offset: 0x0048 */
    __IO uint32_t GPIO1H_SR;                          /* Address Offset: 0x004C */
         uint32_t RESERVED0050[12];                   /* Address Offset: 0x0050 */
    __IO uint32_t GPIO0A_P;                           /* Address Offset: 0x0080 */
    __IO uint32_t GPIO0B_P;                           /* Address Offset: 0x0084 */
    __IO uint32_t GPIO0C_P;                           /* Address Offset: 0x0088 */
    __IO uint32_t GPIO0D_P;                           /* Address Offset: 0x008C */
    __IO uint32_t GPIO1A_P;                           /* Address Offset: 0x0090 */
    __IO uint32_t GPIO1B_P;                           /* Address Offset: 0x0094 */
    __IO uint32_t GPIO1C_P;                           /* Address Offset: 0x0098 */
    __IO uint32_t GPIO1D_P;                           /* Address Offset: 0x009C */
         uint32_t RESERVED00A0[8];                    /* Address Offset: 0x00A0 */
    __IO uint32_t GPIO0A_E;                           /* Address Offset: 0x00C0 */
    __IO uint32_t GPIO0B_E;                           /* Address Offset: 0x00C4 */
    __IO uint32_t GPIO0C_E;                           /* Address Offset: 0x00C8 */
    __IO uint32_t GPIO0D_E;                           /* Address Offset: 0x00CC */
    __IO uint32_t GPIO1A_E;                           /* Address Offset: 0x00D0 */
    __IO uint32_t GPIO1B_E;                           /* Address Offset: 0x00D4 */
    __IO uint32_t GPIO1C_E;                           /* Address Offset: 0x00D8 */
    __IO uint32_t GPIO1D_E;                           /* Address Offset: 0x00DC */
         uint32_t RESERVED00E0[4];                    /* Address Offset: 0x00E0 */
    __I  uint32_t CHIP_VERSION_ID;                    /* Address Offset: 0x00F0 */
    __I  uint32_t CHIP_IDL;                           /* Address Offset: 0x00F4 */
    __I  uint32_t CHIP_IDH;                           /* Address Offset: 0x00F8 */
         uint32_t RESERVED00FC;                       /* Address Offset: 0x00FC */
    __IO uint32_t SOC_CON0;                           /* Address Offset: 0x0100 */
    __IO uint32_t SOC_CON1;                           /* Address Offset: 0x0104 */
    __IO uint32_t SOC_CON2;                           /* Address Offset: 0x0108 */
    __IO uint32_t SOC_CON3;                           /* Address Offset: 0x010C */
    __IO uint32_t SOC_CON4;                           /* Address Offset: 0x0110 */
    __IO uint32_t SOC_CON5;                           /* Address Offset: 0x0114 */
         uint32_t RESERVED0118[10];                   /* Address Offset: 0x0118 */
    __I  uint32_t SOC_STATUS0;                        /* Address Offset: 0x0140 */
    __I  uint32_t SOC_STATUS1;                        /* Address Offset: 0x0144 */
         uint32_t RESERVED0148[6];                    /* Address Offset: 0x0148 */
    __IO uint32_t DSP_CON0;                           /* Address Offset: 0x0160 */
    __IO uint32_t DSP_CON1;                           /* Address Offset: 0x0164 */
    __IO uint32_t DSP_CON2;                           /* Address Offset: 0x0168 */
         uint32_t RESERVED016C;                       /* Address Offset: 0x016C */
    __I  uint32_t DSP_STAT0;                          /* Address Offset: 0x0170 */
    __I  uint32_t DSP_STAT1;                          /* Address Offset: 0x0174 */
         uint32_t RESERVED0178[2];                    /* Address Offset: 0x0178 */
    __IO uint32_t PVTM_CON0;                          /* Address Offset: 0x0180 */
    __IO uint32_t PVTM_CON1;                          /* Address Offset: 0x0184 */
         uint32_t RESERVED0188[2];                    /* Address Offset: 0x0188 */
    __I  uint32_t PVTM_STATUS0;                       /* Address Offset: 0x0190 */
    __I  uint32_t PVTM_STATUS1;                       /* Address Offset: 0x0194 */
         uint32_t RESERVED0198[10];                   /* Address Offset: 0x0198 */
    __IO uint32_t FW_CON0;                            /* Address Offset: 0x01C0 */
    __IO uint32_t FW_CON1;                            /* Address Offset: 0x01C4 */
    __IO uint32_t FW_CON2;                            /* Address Offset: 0x01C8 */
         uint32_t RESERVED01CC[13];                   /* Address Offset: 0x01CC */
    __IO uint32_t MCU_CON0;                           /* Address Offset: 0x0200 */
    __IO uint32_t MCU_CON1;                           /* Address Offset: 0x0204 */
    __IO uint32_t MCU_CON2;                           /* Address Offset: 0x0208 */
    __IO uint32_t MCU_CON3;                           /* Address Offset: 0x020C */
         uint32_t RESERVED0210[4];                    /* Address Offset: 0x0210 */
    __I  uint32_t MCU_STAT0;                          /* Address Offset: 0x0220 */
         uint32_t RESERVED0224[7];                    /* Address Offset: 0x0224 */
    __IO uint32_t DSI_CON0;                           /* Address Offset: 0x0240 */
    __IO uint32_t DSI_CON1;                           /* Address Offset: 0x0244 */
    __IO uint32_t DSI_CON2;                           /* Address Offset: 0x0248 */
    __IO uint32_t DSI_CON3;                           /* Address Offset: 0x024C */
    __IO uint32_t DSI_CON4;                           /* Address Offset: 0x0250 */
    __IO uint32_t DSI_CON5;                           /* Address Offset: 0x0254 */
    __IO uint32_t DSI_CON6;                           /* Address Offset: 0x0258 */
    __IO uint32_t DSI_CON7;                           /* Address Offset: 0x025C */
    __IO uint32_t DSI_CON8;                           /* Address Offset: 0x0260 */
    __IO uint32_t DSI_CON9;                           /* Address Offset: 0x0264 */
    __IO uint32_t DSI_CON10;                          /* Address Offset: 0x0268 */
    __IO uint32_t DSI_CON11;                          /* Address Offset: 0x026C */
    __IO uint32_t DSI_CON12;                          /* Address Offset: 0x0270 */
    __IO uint32_t DSI_CON13;                          /* Address Offset: 0x0274 */
    __IO uint32_t DSI_CON14;                          /* Address Offset: 0x0278 */
    __IO uint32_t DSI_CON15;                          /* Address Offset: 0x027C */
    __IO uint32_t DSI_CON16;                          /* Address Offset: 0x0280 */
    __IO uint32_t DSI_CON17;                          /* Address Offset: 0x0284 */
    __IO uint32_t DSI_CON18;                          /* Address Offset: 0x0288 */
    __IO uint32_t DSI_CON19;                          /* Address Offset: 0x028C */
    __IO uint32_t DSI_CON20;                          /* Address Offset: 0x0290 */
    __IO uint32_t DSI_CON21;                          /* Address Offset: 0x0294 */
    __IO uint32_t DSI_CON22;                          /* Address Offset: 0x0298 */
    __IO uint32_t DSI_CON23;                          /* Address Offset: 0x029C */
    __IO uint32_t DSI_CON24;                          /* Address Offset: 0x02A0 */
    __IO uint32_t DSI_CON25;                          /* Address Offset: 0x02A4 */
    __IO uint32_t DSI_CON26;                          /* Address Offset: 0x02A8 */
    __IO uint32_t DSI_CON27;                          /* Address Offset: 0x02AC */
    __IO uint32_t DSI_CON28;                          /* Address Offset: 0x02B0 */
    __IO uint32_t DSI_CON29;                          /* Address Offset: 0x02B4 */
         uint32_t RESERVED02B8[2];                    /* Address Offset: 0x02B8 */
    __I  uint32_t DSI_STATUS0;                        /* Address Offset: 0x02C0 */
    __I  uint32_t DSI_STATUS1;                        /* Address Offset: 0x02C4 */
    __I  uint32_t DSI_STATUS2;                        /* Address Offset: 0x02C8 */
    __I  uint32_t DSI_STATUS3;                        /* Address Offset: 0x02CC */
    __I  uint32_t DSI_STATUS4;                        /* Address Offset: 0x02D0 */
    __I  uint32_t DSI_STATUS5;                        /* Address Offset: 0x02D4 */
    __I  uint32_t DSI_STATUS6;                        /* Address Offset: 0x02D8 */
    __I  uint32_t DSI_STATUS7;                        /* Address Offset: 0x02DC */
    __I  uint32_t DSI_STATUS8;                        /* Address Offset: 0x02E0 */
         uint32_t RESERVED02E4[7];                    /* Address Offset: 0x02E4 */
    __IO uint32_t MEM_CON0;                           /* Address Offset: 0x0300 */
    __IO uint32_t MEM_CON1;                           /* Address Offset: 0x0304 */
    __IO uint32_t MEM_CON2;                           /* Address Offset: 0x0308 */
    __IO uint32_t MEM_CON3;                           /* Address Offset: 0x030C */
    __IO uint32_t MEM_CON4;                           /* Address Offset: 0x0310 */
    __IO uint32_t MEM_CON5;                           /* Address Offset: 0x0314 */
    __IO uint32_t MEM_CON6;                           /* Address Offset: 0x0318 */
         uint32_t RESERVED031C[9];                    /* Address Offset: 0x031C */
    __IO uint32_t USBPHY_CON0;                        /* Address Offset: 0x0340 */
    __IO uint32_t USBPHY_CON1;                        /* Address Offset: 0x0344 */
    __IO uint32_t USBPHY_CON2;                        /* Address Offset: 0x0348 */
    __IO uint32_t USBPHY_CON3;                        /* Address Offset: 0x034C */
    __IO uint32_t USBPHY_CON4;                        /* Address Offset: 0x0350 */
    __IO uint32_t USBPHY_CON5;                        /* Address Offset: 0x0354 */
    __IO uint32_t USBPHY_CON6;                        /* Address Offset: 0x0358 */
    __IO uint32_t USBPHY_CON7;                        /* Address Offset: 0x035C */
    __IO uint32_t USBPHY_CON8;                        /* Address Offset: 0x0360 */
         uint32_t RESERVED0364[3];                    /* Address Offset: 0x0364 */
    __I  uint32_t USBPHY_STATUS0;                     /* Address Offset: 0x0370 */
    __IO uint32_t USBPHY_STATUS1;                     /* Address Offset: 0x0374 */
         uint32_t RESERVED0378[5];                    /* Address Offset: 0x0378 */
    __IO uint32_t DMAC_CON3;                          /* Address Offset: 0x038C */
    __IO uint32_t DMAC_CON4;                          /* Address Offset: 0x0390 */
    __IO uint32_t DMAC_CON5;                          /* Address Offset: 0x0394 */
    __IO uint32_t DMAC_CON6;                          /* Address Offset: 0x0398 */
         uint32_t RESERVED039C[9];                    /* Address Offset: 0x039C */
    __IO uint32_t FAST_BOOT_EN;                       /* Address Offset: 0x03C0 */
    __IO uint32_t FAST_BOOT_ADDR;                     /* Address Offset: 0x03C4 */
         uint32_t RESERVED03C8[14];                   /* Address Offset: 0x03C8 */
    __IO uint32_t OS_REG0;                            /* Address Offset: 0x0400 */
    __IO uint32_t OS_REG1;                            /* Address Offset: 0x0404 */
    __IO uint32_t OS_REG2;                            /* Address Offset: 0x0408 */
    __IO uint32_t OS_REG3;                            /* Address Offset: 0x040C */
    __IO uint32_t OS_REG4;                            /* Address Offset: 0x0410 */
    __IO uint32_t OS_REG5;                            /* Address Offset: 0x0414 */
    __IO uint32_t OS_REG6;                            /* Address Offset: 0x0418 */
    __IO uint32_t OS_REG7;                            /* Address Offset: 0x041C */
         uint32_t RESERVED0420[696];                  /* Address Offset: 0x0420 */
    __I  uint32_t CHIP_ID;                            /* Address Offset: 0x0F00 */
};
/* MBOX Register Structure Define */
struct MBOX_CMD_DAT {
    __IO uint32_t CMD;
    __IO uint32_t DATA;
};
struct MBOX_REG {
    __IO uint32_t A2B_INTEN;                          /* Address Offset: 0x0000 */
    __IO uint32_t A2B_STATUS;                         /* Address Offset: 0x0004 */
    struct MBOX_CMD_DAT A2B[4];                       /* Address Offset: 0x0008 */
    __IO uint32_t B2A_INTEN;                          /* Address Offset: 0x0028 */
    __IO uint32_t B2A_STATUS;                         /* Address Offset: 0x002C */
    struct MBOX_CMD_DAT B2A[4];                       /* Address Offset: 0x0030 */
         uint32_t RESERVED0050[44];                   /* Address Offset: 0x0050 */
    __IO uint32_t ATOMIC_LOCK[32];                    /* Address Offset: 0x0100 */
};
/* PMU Register Structure Define */
struct PMU_REG {
    __IO uint32_t WAKEUP_CFG[4];                      /* Address Offset: 0x0000 */
         uint32_t RESERVED0010[2];                    /* Address Offset: 0x0010 */
    __IO uint32_t WAKEUP_CFG6;                        /* Address Offset: 0x0018 */
         uint32_t RESERVED001C[5];                    /* Address Offset: 0x001C */
    __IO uint32_t PWRDN_CON;                          /* Address Offset: 0x0030 */
    __I  uint32_t PWRDN_ST;                           /* Address Offset: 0x0034 */
    __IO uint32_t PLL_CON;                            /* Address Offset: 0x0038 */
    __IO uint32_t PWRMODE_CON;                        /* Address Offset: 0x003C */
    __IO uint32_t SFT_CON;                            /* Address Offset: 0x0040 */
         uint32_t RESERVED0044[3];                    /* Address Offset: 0x0044 */
    __IO uint32_t LDO_CON[3];                         /* Address Offset: 0x0050 */
    __I  uint32_t LDO_STAT;                           /* Address Offset: 0x005C */
    __IO uint32_t INT_CON;                            /* Address Offset: 0x0060 */
    __IO uint32_t INT_ST;                             /* Address Offset: 0x0064 */
    __IO uint32_t PWRMODE_GPIO_POS_INT_CON;           /* Address Offset: 0x0068 */
    __IO uint32_t PWRMODE_GPIO_NEG_INT_CON;           /* Address Offset: 0x006C */
    __IO uint32_t DSP_GPIO_POS_INT_CON;               /* Address Offset: 0x0070 */
    __IO uint32_t DSP_GPIO_NEG_INT_CON;               /* Address Offset: 0x0074 */
    __IO uint32_t PWRMODE_GPIO_POS_INT_ST;            /* Address Offset: 0x0078 */
    __IO uint32_t PWRMODE_GPIO_NEG_INT_ST;            /* Address Offset: 0x007C */
    __IO uint32_t DSP_GPIO_POS_INT_ST;                /* Address Offset: 0x0080 */
    __IO uint32_t DSP_GPIO_NEG_INT_ST;                /* Address Offset: 0x0084 */
    __IO uint32_t PWRDN_INTEN;                        /* Address Offset: 0x0088 */
    __IO uint32_t PWRDN_INT_STATUS;                   /* Address Offset: 0x008C */
    __IO uint32_t WAKEUP_STATUS;                      /* Address Offset: 0x0090 */
         uint32_t RESERVED0094[3];                    /* Address Offset: 0x0094 */
    __IO uint32_t BUS_CLR;                            /* Address Offset: 0x00A0 */
    __IO uint32_t BUS_IDLE_REQ;                       /* Address Offset: 0x00A4 */
    __I  uint32_t BUS_IDLE_ST;                        /* Address Offset: 0x00A8 */
    __I  uint32_t BUS_IDLE_ACK;                       /* Address Offset: 0x00AC */
    __I  uint32_t POWER_ST;                           /* Address Offset: 0x00B0 */
    __I  uint32_t CORE_PWR_ST;                        /* Address Offset: 0x00B4 */
    __IO uint32_t OSC_CNT;                            /* Address Offset: 0x00B8 */
    __IO uint32_t PLLLOCK_CNT;                        /* Address Offset: 0x00BC */
    __IO uint32_t PWRMODE_TIMEOUT_CNT;                /* Address Offset: 0x00C0 */
    __IO uint32_t NOC_AUTO_ENA;                       /* Address Offset: 0x00C4 */
         uint32_t RESERVED00C8[2];                    /* Address Offset: 0x00C8 */
    __IO uint32_t DSPAPM_CON;                         /* Address Offset: 0x00D0 */
         uint32_t RESERVED00D4;                       /* Address Offset: 0x00D4 */
    __IO uint32_t DSP_LDO_ADJ_CNT;                    /* Address Offset: 0x00D8 */
    __IO uint32_t DSP_TIMEOUT_CNT;                    /* Address Offset: 0x00DC */
    __IO uint32_t PWRMODE_LDO_ADJ_CNT;                /* Address Offset: 0x00E0 */
    __IO uint32_t SHRM_CON0;                          /* Address Offset: 0x00E4 */
    __IO uint32_t DSPTCM_CON[2];                      /* Address Offset: 0x00E8 */
    __IO uint32_t SYS_REG[4];                         /* Address Offset: 0x00F0 */
    __IO uint32_t SHRM_CON1;                          /* Address Offset: 0x0100 */
    __IO uint32_t DSPTCM_CON1[2];                     /* Address Offset: 0x0104 */
};
/* DMA Register Structure Define */
struct DMA_CHANNEL_STATUS {
    __I  uint32_t CSR;
    __I  uint32_t CPC;
};
struct DMA_CHANNEL_CONFIG {
    __I  uint32_t SAR;
    __I  uint32_t DAR;
    __I  uint32_t CCR;
    __I  uint32_t LC0;
    __I  uint32_t LC1;
         uint32_t PADDING[3];
};
struct DMA_REG {
    __I  uint32_t DSR;                                /* Address Offset: 0x0000 */
    __I  uint32_t DPC;                                /* Address Offset: 0x0004 */
         uint32_t RESERVED0008[6];                    /* Address Offset: 0x0008 */
    __IO uint32_t INTEN;                              /* Address Offset: 0x0020 */
    __I  uint32_t EVENT_RIS;                          /* Address Offset: 0x0024 */
    __I  uint32_t INTMIS;                             /* Address Offset: 0x0028 */
    __O  uint32_t INTCLR;                             /* Address Offset: 0x002C */
    __I  uint32_t FSRD;                               /* Address Offset: 0x0030 */
    __I  uint32_t FSRC;                               /* Address Offset: 0x0034 */
    __IO uint32_t FTRD;                               /* Address Offset: 0x0038 */
         uint32_t RESERVED003C;                       /* Address Offset: 0x003C */
    __I  uint32_t FTR[6];                             /* Address Offset: 0x0040 */
         uint32_t RESERVED0058[42];                   /* Address Offset: 0x0058 */
    struct DMA_CHANNEL_STATUS CHAN_STS[6];            /* Address Offset: 0x0100 */
         uint32_t RESERVED0130[180];                  /* Address Offset: 0x0130 */
    struct DMA_CHANNEL_CONFIG CHAN_CFG[6];            /* Address Offset: 0x0400 */
         uint32_t RESERVED04C0[528];                  /* Address Offset: 0x04C0 */
    __I  uint32_t DBGSTATUS;                          /* Address Offset: 0x0D00 */
    __O  uint32_t DBGCMD;                             /* Address Offset: 0x0D04 */
    __O  uint32_t DBGINST[2];                         /* Address Offset: 0x0D08 */
         uint32_t RESERVED0D10[60];                   /* Address Offset: 0x0D10 */
    __I  uint32_t CR[5];                              /* Address Offset: 0x0E00 */
    __I  uint32_t CRDN;                               /* Address Offset: 0x0E14 */
         uint32_t RESERVED0E18[26];                   /* Address Offset: 0x0E18 */
    __IO uint32_t WD;                                 /* Address Offset: 0x0E80 */
};
/* ACDCDIG Register Structure Define */
struct ACDCDIG_REG {
    __IO uint32_t VUCTL;                              /* Address Offset: 0x0000 */
    __IO uint32_t VUCTIME;                            /* Address Offset: 0x0004 */
    __IO uint32_t DIGEN;                              /* Address Offset: 0x0008 */
    __IO uint32_t CLKCTRL;                            /* Address Offset: 0x000C */
    __IO uint32_t CLKDIV;                             /* Address Offset: 0x0010 */
    __IO uint32_t REFCFG;                             /* Address Offset: 0x0014 */
    __IO uint32_t ADCCFG0;                            /* Address Offset: 0x0018 */
    __IO uint32_t ADCCFG1;                            /* Address Offset: 0x001C */
    __IO uint32_t ADCCFG2;                            /* Address Offset: 0x0020 */
    __IO uint32_t ADCCFG3;                            /* Address Offset: 0x0024 */
    __IO uint32_t ADCVOLL;                            /* Address Offset: 0x0028 */
    __IO uint32_t ADCVOLR;                            /* Address Offset: 0x002C */
    __IO uint32_t ALC0;                               /* Address Offset: 0x0030 */
    __IO uint32_t ALC1;                               /* Address Offset: 0x0034 */
    __IO uint32_t ALC2;                               /* Address Offset: 0x0038 */
    __IO uint32_t ADCNG;                              /* Address Offset: 0x003C */
    __IO uint32_t HPFCTRL;                            /* Address Offset: 0x0040 */
    __I  uint32_t ADCRVOLL;                           /* Address Offset: 0x0044 */
    __I  uint32_t ADCRVOLR;                           /* Address Offset: 0x0048 */
    __IO uint32_t PGACFG;                             /* Address Offset: 0x004C */
    __IO uint32_t PGAGAINL;                           /* Address Offset: 0x0050 */
    __IO uint32_t PGAGAINR;                           /* Address Offset: 0x0054 */
    __IO uint32_t LILMT1;                             /* Address Offset: 0x0058 */
    __IO uint32_t LILMT2;                             /* Address Offset: 0x005C */
    __IO uint32_t LILMTNG1;                           /* Address Offset: 0x0060 */
    __I  uint32_t LILMTNG2;                           /* Address Offset: 0x0064 */
    __IO uint32_t PDMCTRL;                            /* Address Offset: 0x0068 */
    __IO uint32_t I2SCKM;                             /* Address Offset: 0x006C */
    __IO uint32_t I2SDIV;                             /* Address Offset: 0x0070 */
    __IO uint32_t I2STXCR0;                           /* Address Offset: 0x0074 */
    __IO uint32_t I2STXCR1;                           /* Address Offset: 0x0078 */
    __IO uint32_t I2STXCR2;                           /* Address Offset: 0x007C */
    __IO uint32_t I2STXCMD;                           /* Address Offset: 0x0080 */
    __I  uint32_t VERSION;                            /* Address Offset: 0x0084 */
};
/* UART Register Structure Define */
struct UART_REG {
    union {
        __IO uint32_t RBR;                                /* Address Offset: 0x0000 */
        __IO uint32_t THR;                                /* Address Offset: 0x0000 */
        __IO uint32_t DLL;                                /* Address Offset: 0x0000 */
    };
    union {
        __IO uint32_t DLH;                                /* Address Offset: 0x0004 */
        __IO uint32_t IER;                                /* Address Offset: 0x0004 */
    };
    union {
        __I  uint32_t IIR;                                /* Address Offset: 0x0008 */
        __O  uint32_t FCR;                                /* Address Offset: 0x0008 */
    };
    __IO uint32_t LCR;                                /* Address Offset: 0x000C */
    __IO uint32_t MCR;                                /* Address Offset: 0x0010 */
    __I  uint32_t LSR;                                /* Address Offset: 0x0014 */
    __I  uint32_t MSR;                                /* Address Offset: 0x0018 */
    __IO uint32_t SCR;                                /* Address Offset: 0x001C */
         uint32_t RESERVED0020[4];                    /* Address Offset: 0x0020 */
    union {
        __I  uint32_t SRBR;                               /* Address Offset: 0x0030 */
        __I  uint32_t STHR;                               /* Address Offset: 0x0030 */
    };
         uint32_t RESERVED0034[15];                   /* Address Offset: 0x0034 */
    __IO uint32_t FAR;                                /* Address Offset: 0x0070 */
    __I  uint32_t TFR;                                /* Address Offset: 0x0074 */
    __O  uint32_t RFW;                                /* Address Offset: 0x0078 */
    __I  uint32_t USR;                                /* Address Offset: 0x007C */
    __IO uint32_t TFL;                                /* Address Offset: 0x0080 */
    __I  uint32_t RFL;                                /* Address Offset: 0x0084 */
    __O  uint32_t SRR;                                /* Address Offset: 0x0088 */
    __IO uint32_t SRTS;                               /* Address Offset: 0x008C */
    __IO uint32_t SBCR;                               /* Address Offset: 0x0090 */
    __IO uint32_t SDMAM;                              /* Address Offset: 0x0094 */
    __IO uint32_t SFE;                                /* Address Offset: 0x0098 */
    __IO uint32_t SRT;                                /* Address Offset: 0x009C */
    __IO uint32_t STET;                               /* Address Offset: 0x00A0 */
    __IO uint32_t HTX;                                /* Address Offset: 0x00A4 */
    __O  uint32_t DMASA;                              /* Address Offset: 0x00A8 */
         uint32_t RESERVED00AC[18];                   /* Address Offset: 0x00AC */
    __I  uint32_t CPR;                                /* Address Offset: 0x00F4 */
    __I  uint32_t UCV;                                /* Address Offset: 0x00F8 */
    __I  uint32_t CTR;                                /* Address Offset: 0x00FC */
};
/* PWM Register Structure Define */
struct PWM_CHANNEL {
    __I  uint32_t CNT;
    __IO uint32_t PERIOD_HPR;
    __IO uint32_t DUTY_LPR;
    __IO uint32_t CTRL;
};
struct PWM_REG {
    struct PWM_CHANNEL CHANNELS[4];                   /* Address Offset: 0x0000 */
    __IO uint32_t INTSTS;                             /* Address Offset: 0x0040 */
    __IO uint32_t INT_EN;                             /* Address Offset: 0x0044 */
         uint32_t RESERVED0048[2];                    /* Address Offset: 0x0048 */
    __IO uint32_t FIFO_CTRL;                          /* Address Offset: 0x0050 */
    __IO uint32_t FIFO_INTSTS;                        /* Address Offset: 0x0054 */
    __IO uint32_t FIFO_TOUTTHR;                       /* Address Offset: 0x0058 */
    __IO uint32_t VERSION_ID;                         /* Address Offset: 0x005C */
    __I  uint32_t FIFO;                               /* Address Offset: 0x0060 */
         uint32_t RESERVED0064[7];                    /* Address Offset: 0x0064 */
    __IO uint32_t PWRMATCH_CTRL;                      /* Address Offset: 0x0080 */
    __IO uint32_t PWRMATCH_LPRE;                      /* Address Offset: 0x0084 */
    __IO uint32_t PWRMATCH_HPRE;                      /* Address Offset: 0x0088 */
    __IO uint32_t PWRMATCH_LD;                        /* Address Offset: 0x008C */
    __IO uint32_t PWRMATCH_HD_ZERO;                   /* Address Offset: 0x0090 */
    __IO uint32_t PWRMATCH_HD_ONE;                    /* Address Offset: 0x0094 */
    __IO uint32_t PWRMATCH_VALUE[10];                 /* Address Offset: 0x0098 */
         uint32_t RESERVED00C0[3];                    /* Address Offset: 0x00C0 */
    __I  uint32_t PWM3_PWRCAPTURE_VALUE;              /* Address Offset: 0x00CC */
    __IO uint32_t FILTER_CTRL;                        /* Address Offset: 0x00D0 */
};
/* TIMER Register Structure Define */
struct TIMER_REG {
    __IO uint32_t LOAD_COUNT[2];                      /* Address Offset: 0x0000 */
    __I  uint32_t CURRENT_VALUE[2];                   /* Address Offset: 0x0008 */
    __IO uint32_t CONTROLREG;                         /* Address Offset: 0x0010 */
         uint32_t RESERVED0014;                       /* Address Offset: 0x0014 */
    __IO uint32_t INTSTATUS;                          /* Address Offset: 0x0018 */
};
/* WDT Register Structure Define */
struct WDT_REG {
    __IO uint32_t CR;                             /* Address Offset: 0x0000 */
    __IO uint32_t TORR;                           /* Address Offset: 0x0004 */
    __I  uint32_t CCVR;                           /* Address Offset: 0x0008 */
    __O  uint32_t CRR;                            /* Address Offset: 0x000C */
    __I  uint32_t STAT;                           /* Address Offset: 0x0010 */
    __I  uint32_t EOI;                            /* Address Offset: 0x0014 */
};
/* I2C Register Structure Define */
struct I2C_REG {
    __IO uint32_t CON;                                /* Address Offset: 0x0000 */
    __IO uint32_t CLKDIV;                             /* Address Offset: 0x0004 */
    __IO uint32_t MRXADDR;                            /* Address Offset: 0x0008 */
    __IO uint32_t MRXRADDR;                           /* Address Offset: 0x000C */
    __IO uint32_t MTXCNT;                             /* Address Offset: 0x0010 */
    __IO uint32_t MRXCNT;                             /* Address Offset: 0x0014 */
    __IO uint32_t IEN;                                /* Address Offset: 0x0018 */
    __IO uint32_t IPD;                                /* Address Offset: 0x001C */
    __I  uint32_t FCNT;                               /* Address Offset: 0x0020 */
    __IO uint32_t SCL_OE_DB;                          /* Address Offset: 0x0024 */
         uint32_t RESERVED0028[54];                   /* Address Offset: 0x0028 */
    __IO uint32_t TXDATA[8];                          /* Address Offset: 0x0100 */
         uint32_t RESERVED0120[56];                   /* Address Offset: 0x0120 */
    __I  uint32_t RXDATA[8];                          /* Address Offset: 0x0200 */
    __I  uint32_t ST;                                 /* Address Offset: 0x0220 */
    __IO uint32_t DBGCTRL;                            /* Address Offset: 0x0224 */
};
/* SPI2APB Register Structure Define */
struct SPI2APB_REG {
    __IO uint32_t CTRL0;                              /* Address Offset: 0x0000 */
         uint32_t RESERVED0004[8];                    /* Address Offset: 0x0004 */
    __I  uint32_t SR;                                 /* Address Offset: 0x0024 */
         uint32_t RESERVED0028;                       /* Address Offset: 0x0028 */
    __IO uint32_t IMR;                                /* Address Offset: 0x002C */
         uint32_t RESERVED0030;                       /* Address Offset: 0x0030 */
    __IO uint32_t RISR;                               /* Address Offset: 0x0034 */
    __O  uint32_t ICR;                                /* Address Offset: 0x0038 */
         uint32_t RESERVED003C[3];                    /* Address Offset: 0x003C */
    __IO uint32_t VERSION;                            /* Address Offset: 0x0048 */
         uint32_t RESERVED004C;                       /* Address Offset: 0x004C */
    __IO uint32_t QUICK_REG[3];                       /* Address Offset: 0x0050 */
};
/* SPI Register Structure Define */
struct SPI_REG {
    __IO uint32_t CTRLR[2];                           /* Address Offset: 0x0000 */
    __IO uint32_t ENR;                                /* Address Offset: 0x0008 */
    __IO uint32_t SER;                                /* Address Offset: 0x000C */
    __IO uint32_t BAUDR;                              /* Address Offset: 0x0010 */
    __IO uint32_t TXFTLR;                             /* Address Offset: 0x0014 */
    __IO uint32_t RXFTLR;                             /* Address Offset: 0x0018 */
    __I  uint32_t TXFLR;                              /* Address Offset: 0x001C */
    __I  uint32_t RXFLR;                              /* Address Offset: 0x0020 */
    __IO uint32_t SR;                                 /* Address Offset: 0x0024 */
    __IO uint32_t IPR;                                /* Address Offset: 0x0028 */
    __IO uint32_t IMR;                                /* Address Offset: 0x002C */
    __IO uint32_t ISR;                                /* Address Offset: 0x0030 */
    __IO uint32_t RISR;                               /* Address Offset: 0x0034 */
    __IO uint32_t ICR;                                /* Address Offset: 0x0038 */
    __IO uint32_t DMACR;                              /* Address Offset: 0x003C */
    __IO uint32_t DMATDLR;                            /* Address Offset: 0x0040 */
    __IO uint32_t DMARDLR;                            /* Address Offset: 0x0044 */
         uint32_t RESERVED0048;                       /* Address Offset: 0x0048 */
    __IO uint32_t TIMEOUT;                            /* Address Offset: 0x004C */
    __IO uint32_t BYPASS;                             /* Address Offset: 0x0050 */
         uint32_t RESERVED0054[235];                  /* Address Offset: 0x0054 */
    __O  uint32_t TXDR;                               /* Address Offset: 0x0400 */
         uint32_t RESERVED0404[255];                  /* Address Offset: 0x0404 */
    __IO uint32_t RXDR;                               /* Address Offset: 0x0800 */
};
/* FSPI Register Structure Define */
struct FSPI_REG {
    __IO uint32_t CTRL0;                              /* Address Offset: 0x0000 */
    __IO uint32_t IMR;                                /* Address Offset: 0x0004 */
    __IO uint32_t ICLR;                               /* Address Offset: 0x0008 */
    __IO uint32_t FTLR;                               /* Address Offset: 0x000C */
    __IO uint32_t RCVR;                               /* Address Offset: 0x0010 */
    __IO uint32_t AX0;                                /* Address Offset: 0x0014 */
    __IO uint32_t ABIT0;                              /* Address Offset: 0x0018 */
    __IO uint32_t ISR;                                /* Address Offset: 0x001C */
    __IO uint32_t FSR;                                /* Address Offset: 0x0020 */
    __I  uint32_t SR;                                 /* Address Offset: 0x0024 */
    __I  uint32_t RISR;                               /* Address Offset: 0x0028 */
    __I  uint32_t VER;                                /* Address Offset: 0x002C */
    __IO uint32_t QOP;                                /* Address Offset: 0x0030 */
    __IO uint32_t EXT_CTRL;                           /* Address Offset: 0x0034 */
    __IO uint32_t POLL_CTRL;                          /* Address Offset: 0x0038 */
    __IO uint32_t DLL_CTRL0;                          /* Address Offset: 0x003C */
    __IO uint32_t HRDYMASK;                           /* Address Offset: 0x0040 */
    __IO uint32_t EXT_AX;                             /* Address Offset: 0x0044 */
    __IO uint32_t SCLK_INATM_CNT;                     /* Address Offset: 0x0048 */
    __IO uint32_t AUTO_RF_CNT;                        /* Address Offset: 0x004C */
    __O  uint32_t XMMC_WCMD0;                         /* Address Offset: 0x0050 */
    __O  uint32_t XMMC_RCMD0;                         /* Address Offset: 0x0054 */
    __IO uint32_t XMMC_CTRL;                          /* Address Offset: 0x0058 */
    __IO uint32_t MODE;                               /* Address Offset: 0x005C */
    __IO uint32_t DEVRGN;                             /* Address Offset: 0x0060 */
    __IO uint32_t DEVSIZE0;                           /* Address Offset: 0x0064 */
    __IO uint32_t TME0;                               /* Address Offset: 0x0068 */
    __IO uint32_t POLLDLY_CTRL;                       /* Address Offset: 0x006C */
         uint32_t RESERVED0070[4];                    /* Address Offset: 0x0070 */
    __IO uint32_t DMATR;                              /* Address Offset: 0x0080 */
    __IO uint32_t DMAADDR;                            /* Address Offset: 0x0084 */
         uint32_t RESERVED0088[2];                    /* Address Offset: 0x0088 */
    __I  uint32_t POLL_DATA;                          /* Address Offset: 0x0090 */
    __IO uint32_t XMMCSR;                             /* Address Offset: 0x0094 */
         uint32_t RESERVED0098[26];                   /* Address Offset: 0x0098 */
    __O  uint32_t CMD;                                /* Address Offset: 0x0100 */
    __O  uint32_t ADDR;                               /* Address Offset: 0x0104 */
    __IO uint32_t DATA;                               /* Address Offset: 0x0108 */
         uint32_t RESERVED010C[61];                   /* Address Offset: 0x010C */
    __IO uint32_t CTRL1;                              /* Address Offset: 0x0200 */
         uint32_t RESERVED0204[4];                    /* Address Offset: 0x0204 */
    __IO uint32_t AX1;                                /* Address Offset: 0x0214 */
    __IO uint32_t ABIT1;                              /* Address Offset: 0x0218 */
         uint32_t RESERVED021C[8];                    /* Address Offset: 0x021C */
    __IO uint32_t DLL_CTRL1;                          /* Address Offset: 0x023C */
         uint32_t RESERVED0240[4];                    /* Address Offset: 0x0240 */
    __O  uint32_t XMMC_WCMD1;                         /* Address Offset: 0x0250 */
    __O  uint32_t XMMC_RCMD1;                         /* Address Offset: 0x0254 */
         uint32_t RESERVED0258[3];                    /* Address Offset: 0x0258 */
    __IO uint32_t DEVSIZE1;                           /* Address Offset: 0x0264 */
    __IO uint32_t TME1;                               /* Address Offset: 0x0268 */
};
/* MMC Register Structure Define */
struct MMC_REG {
    __IO uint32_t CTRL;                               /* Address Offset: 0x0000 */
    __IO uint32_t PWREN;                              /* Address Offset: 0x0004 */
    __IO uint32_t CLKDIV;                             /* Address Offset: 0x0008 */
    __IO uint32_t CLKSRC;                             /* Address Offset: 0x000C */
    __IO uint32_t CLKENA;                             /* Address Offset: 0x0010 */
    __IO uint32_t TMOUT;                              /* Address Offset: 0x0014 */
    __IO uint32_t CTYPE;                              /* Address Offset: 0x0018 */
    __IO uint32_t BLKSIZ;                             /* Address Offset: 0x001C */
    __IO uint32_t BYTCNT;                             /* Address Offset: 0x0020 */
    __IO uint32_t INTMASK;                            /* Address Offset: 0x0024 */
    __IO uint32_t CMDARG;                             /* Address Offset: 0x0028 */
    __IO uint32_t CMD;                                /* Address Offset: 0x002C */
    __I  uint32_t RESP[4];                            /* Address Offset: 0x0030 */
    __IO uint32_t MINTSTS;                            /* Address Offset: 0x0040 */
    __IO uint32_t RINTSTS;                            /* Address Offset: 0x0044 */
    __I  uint32_t STATUS;                             /* Address Offset: 0x0048 */
    __IO uint32_t FIFOTH;                             /* Address Offset: 0x004C */
    __I  uint32_t CDETECT;                            /* Address Offset: 0x0050 */
    __IO uint32_t WRTPRT;                             /* Address Offset: 0x0054 */
         uint32_t RESERVED0058;                       /* Address Offset: 0x0058 */
    __I  uint32_t TCBCNT;                             /* Address Offset: 0x005C */
    __I  uint32_t TBBCNT;                             /* Address Offset: 0x0060 */
    __IO uint32_t DEBNCE;                             /* Address Offset: 0x0064 */
    __IO uint32_t USRID;                              /* Address Offset: 0x0068 */
    __I  uint32_t VERID;                              /* Address Offset: 0x006C */
    __I  uint32_t HCON;                               /* Address Offset: 0x0070 */
    __IO uint32_t UHSREG;                             /* Address Offset: 0x0074 */
    __IO uint32_t RSTN;                               /* Address Offset: 0x0078 */
         uint32_t RESERVED007C;                       /* Address Offset: 0x007C */
    __IO uint32_t BMOD;                               /* Address Offset: 0x0080 */
    __O  uint32_t PLDMND;                             /* Address Offset: 0x0084 */
    __IO uint32_t DBADDR;                             /* Address Offset: 0x0088 */
    __IO uint32_t IDSTS;                              /* Address Offset: 0x008C */
    __IO uint32_t IDINTEN;                            /* Address Offset: 0x0090 */
    __IO uint32_t DSCADDR;                            /* Address Offset: 0x0094 */
    __IO uint32_t BUFADDR;                            /* Address Offset: 0x0098 */
         uint32_t RESERVED009C[25];                   /* Address Offset: 0x009C */
    __IO uint32_t CARDTHRCTL;                         /* Address Offset: 0x0100 */
    __IO uint32_t BACKEND_POWER;                      /* Address Offset: 0x0104 */
         uint32_t RESERVED0108;                       /* Address Offset: 0x0108 */
    __IO uint32_t EMMCDDR_REG;                        /* Address Offset: 0x010C */
         uint32_t RESERVED0110[4];                    /* Address Offset: 0x0110 */
    __IO uint32_t RDYINT_GEN;                         /* Address Offset: 0x0120 */
         uint32_t RESERVED0124[55];                   /* Address Offset: 0x0124 */
    __IO uint32_t FIFO_BASE;                          /* Address Offset: 0x0200 */
};
/* GPIO Register Structure Define */
struct GPIO_REG {
    __IO uint32_t SWPORT_DR_L;                        /* Address Offset: 0x0000 */
    __IO uint32_t SWPORT_DR_H;                        /* Address Offset: 0x0004 */
    __IO uint32_t SWPORT_DDR_L;                       /* Address Offset: 0x0008 */
    __IO uint32_t SWPORT_DDR_H;                       /* Address Offset: 0x000C */
    __IO uint32_t INT_EN_L;                           /* Address Offset: 0x0010 */
    __IO uint32_t INT_EN_H;                           /* Address Offset: 0x0014 */
    __IO uint32_t INT_MASK_L;                         /* Address Offset: 0x0018 */
    __IO uint32_t INT_MASK_H;                         /* Address Offset: 0x001C */
    __IO uint32_t INT_TYPE_L;                         /* Address Offset: 0x0020 */
    __IO uint32_t INT_TYPE_H;                         /* Address Offset: 0x0024 */
    __IO uint32_t INT_POLARITY_L;                     /* Address Offset: 0x0028 */
    __IO uint32_t INT_POLARITY_H;                     /* Address Offset: 0x002C */
    __IO uint32_t INT_BOTHEDGE_L;                     /* Address Offset: 0x0030 */
    __IO uint32_t INT_BOTHEDGE_H;                     /* Address Offset: 0x0034 */
    __IO uint32_t DEBOUNCE_L;                         /* Address Offset: 0x0038 */
    __IO uint32_t DEBOUNCE_H;                         /* Address Offset: 0x003C */
    __IO uint32_t DBCLK_DIV_EN_L;                     /* Address Offset: 0x0040 */
    __IO uint32_t DBCLK_DIV_EN_H;                     /* Address Offset: 0x0044 */
    __IO uint32_t DBCLK_DIV_CON;                      /* Address Offset: 0x0048 */
         uint32_t RESERVED004C;                       /* Address Offset: 0x004C */
    __I  uint32_t INT_STATUS;                         /* Address Offset: 0x0050 */
         uint32_t RESERVED0054;                       /* Address Offset: 0x0054 */
    __I  uint32_t INT_RAWSTATUS;                      /* Address Offset: 0x0058 */
         uint32_t RESERVED005C;                       /* Address Offset: 0x005C */
    __IO uint32_t PORT_EOI_L;                         /* Address Offset: 0x0060 */
    __IO uint32_t PORT_EOI_H;                         /* Address Offset: 0x0064 */
         uint32_t RESERVED0068[2];                    /* Address Offset: 0x0068 */
    __I  uint32_t EXT_PORT;                           /* Address Offset: 0x0070 */
         uint32_t RESERVED0074;                       /* Address Offset: 0x0074 */
    __I  uint32_t VER_ID;                             /* Address Offset: 0x0078 */
};
/* KEY_CTRL Register Structure Define */
struct KEY_CTRL_REG {
    __IO uint32_t CON;                                /* Address Offset: 0x0000 */
    __IO uint32_t CAL_TH;                             /* Address Offset: 0x0004 */
    __I  uint32_t DET_REC;                            /* Address Offset: 0x0008 */
    __IO uint32_t INT_CON;                            /* Address Offset: 0x000C */
    __IO uint32_t INT_ST;                             /* Address Offset: 0x0010 */
};
/* PDM Register Structure Define */
struct PDM_REG {
    __IO uint32_t SYSCONFIG;                          /* Address Offset: 0x0000 */
    __IO uint32_t CTRL[2];                            /* Address Offset: 0x0004 */
    __IO uint32_t CLK_CTRL;                           /* Address Offset: 0x000C */
    __IO uint32_t HPF_CTRL;                           /* Address Offset: 0x0010 */
    __IO uint32_t FIFO_CTRL;                          /* Address Offset: 0x0014 */
    __IO uint32_t DMA_CTRL;                           /* Address Offset: 0x0018 */
    __IO uint32_t INT_EN;                             /* Address Offset: 0x001C */
    __IO uint32_t INT_CLR;                            /* Address Offset: 0x0020 */
    __I  uint32_t INT_ST;                             /* Address Offset: 0x0024 */
         uint32_t RESERVED0028[2];                    /* Address Offset: 0x0028 */
    __I  uint32_t RXFIFO_DATA_REG;                    /* Address Offset: 0x0030 */
    __I  uint32_t DATA0R_REG;                         /* Address Offset: 0x0034 */
    __I  uint32_t DATA0L_REG;                         /* Address Offset: 0x0038 */
    __I  uint32_t DATA1R_REG;                         /* Address Offset: 0x003C */
    __I  uint32_t DATA1L_REG;                         /* Address Offset: 0x0040 */
    __I  uint32_t DATA2R_REG;                         /* Address Offset: 0x0044 */
    __I  uint32_t DATA2L_REG;                         /* Address Offset: 0x0048 */
    __I  uint32_t DATA3R_REG;                         /* Address Offset: 0x004C */
    __I  uint32_t DATA3L_REG;                         /* Address Offset: 0x0050 */
    __I  uint32_t DATA_VALID;                         /* Address Offset: 0x0054 */
    __I  uint32_t VERSION;                            /* Address Offset: 0x0058 */
         uint32_t RESERVED005C[233];                  /* Address Offset: 0x005C */
    __I  uint32_t INCR_RXDR;                          /* Address Offset: 0x0400 */
};
/* I2STDM Register Structure Define */
struct I2STDM_REG {
    __IO uint32_t TXCR;                               /* Address Offset: 0x0000 */
    __IO uint32_t RXCR;                               /* Address Offset: 0x0004 */
    __IO uint32_t CKR;                                /* Address Offset: 0x0008 */
    __IO uint32_t TXFIFOLR;                           /* Address Offset: 0x000C */
    __IO uint32_t DMACR;                              /* Address Offset: 0x0010 */
    __IO uint32_t INTCR;                              /* Address Offset: 0x0014 */
    __IO uint32_t INTSR;                              /* Address Offset: 0x0018 */
    __IO uint32_t XFER;                               /* Address Offset: 0x001C */
    __IO uint32_t CLR;                                /* Address Offset: 0x0020 */
    __IO uint32_t TXDR;                               /* Address Offset: 0x0024 */
    __IO uint32_t RXDR;                               /* Address Offset: 0x0028 */
    __IO uint32_t RXFIFOLR;                           /* Address Offset: 0x002C */
    __IO uint32_t TDM_TXCTRL;                         /* Address Offset: 0x0030 */
    __IO uint32_t TDM_RXCTRL;                         /* Address Offset: 0x0034 */
    __IO uint32_t CLKDIV;                             /* Address Offset: 0x0038 */
    __IO uint32_t VERSION;                            /* Address Offset: 0x003C */
};
/* VAD Register Structure Define */
struct VAD_REG {
    __IO uint32_t CONTROL;                            /* Address Offset: 0x0000 */
    __IO uint32_t VS_ADDR;                            /* Address Offset: 0x0004 */
         uint32_t RESERVED0008[17];                   /* Address Offset: 0x0008 */
    __IO uint32_t TIMEOUT;                            /* Address Offset: 0x004C */
    __IO uint32_t RAM_START_ADDR;                     /* Address Offset: 0x0050 */
    __IO uint32_t RAM_END_ADDR;                       /* Address Offset: 0x0054 */
    __IO uint32_t RAM_CUR_ADDR;                       /* Address Offset: 0x0058 */
    __IO uint32_t DET_CON[6];                         /* Address Offset: 0x005C */
    __IO uint32_t INT;                                /* Address Offset: 0x0074 */
    __IO uint32_t AUX_CON0;                           /* Address Offset: 0x0078 */
    __I  uint32_t SAMPLE_CNT;                         /* Address Offset: 0x007C */
    __IO uint32_t RAM_START_ADDR_BUS;                 /* Address Offset: 0x0080 */
    __IO uint32_t RAM_END_ADDR_BUS;                   /* Address Offset: 0x0084 */
    __IO uint32_t RAM_CUR_ADDR_BUS;                   /* Address Offset: 0x0088 */
    __IO uint32_t AUX_CON1;                           /* Address Offset: 0x008C */
         uint32_t RESERVED0090[28];                   /* Address Offset: 0x0090 */
    __IO uint32_t NOISE_FIRST_DATA;                   /* Address Offset: 0x0100 */
         uint32_t RESERVED0104[126];                  /* Address Offset: 0x0104 */
    __IO uint32_t NOISE_LAST_DATA;                    /* Address Offset: 0x02FC */
};
/* VOP Register Structure Define */
struct VOP_REG {
    __IO uint32_t REG_CFG_DONE;                       /* Address Offset: 0x0000 */
    __I  uint32_t VERSION;                            /* Address Offset: 0x0004 */
    __IO uint32_t DSP_BG;                             /* Address Offset: 0x0008 */
    __IO uint32_t MCU;                                /* Address Offset: 0x000C */
    __IO uint32_t SYS_CTRL0;                          /* Address Offset: 0x0010 */
    __IO uint32_t SYS_CTRL1;                          /* Address Offset: 0x0014 */
    __IO uint32_t SYS_CTRL2;                          /* Address Offset: 0x0018 */
         uint32_t RESERVED001C;                       /* Address Offset: 0x001C */
    __IO uint32_t DSP_CTRL0;                          /* Address Offset: 0x0020 */
    __IO uint32_t DSP_CTRL1;                          /* Address Offset: 0x0024 */
    __IO uint32_t DSP_CTRL2;                          /* Address Offset: 0x0028 */
    __IO uint32_t VOP_STATUS;                         /* Address Offset: 0x002C */
    __IO uint32_t LINE_FLAG;                          /* Address Offset: 0x0030 */
    __IO uint32_t INTR_EN;                            /* Address Offset: 0x0034 */
    __IO uint32_t INTR_CLEAR;                         /* Address Offset: 0x0038 */
    __IO uint32_t INTR_STATUS;                        /* Address Offset: 0x003C */
    __IO uint32_t WIN0_CTRL0;                         /* Address Offset: 0x0040 */
    __IO uint32_t WIN0_CTRL1;                         /* Address Offset: 0x0044 */
    __IO uint32_t WIN0_VIR;                           /* Address Offset: 0x0048 */
         uint32_t RESERVED004C;                       /* Address Offset: 0x004C */
    __IO uint32_t WIN0_YRGB_MST;                      /* Address Offset: 0x0050 */
    __IO uint32_t WIN0_DSP_INFO;                      /* Address Offset: 0x0054 */
    __IO uint32_t WIN0_DSP_ST;                        /* Address Offset: 0x0058 */
    __IO uint32_t WIN0_COLOR_KEY;                     /* Address Offset: 0x005C */
         uint32_t RESERVED0060[3];                    /* Address Offset: 0x0060 */
    __IO uint32_t WIN0_ALPHA_CTRL;                    /* Address Offset: 0x006C */
    __IO uint32_t WIN0_CBCR_MST;                      /* Address Offset: 0x0070 */
    __IO uint32_t WIN0_YRGB_MST_RAW;                  /* Address Offset: 0x0074 */
    __IO uint32_t WIN0_CBCR_MST_RAW;                  /* Address Offset: 0x0078 */
    __IO uint32_t WIN0_LOOP_OFFSET;                   /* Address Offset: 0x007C */
    __IO uint32_t WIN1_CTRL0;                         /* Address Offset: 0x0080 */
    __IO uint32_t WIN1_CTRL1;                         /* Address Offset: 0x0084 */
    __IO uint32_t WIN1_VIR;                           /* Address Offset: 0x0088 */
         uint32_t RESERVED008C;                       /* Address Offset: 0x008C */
    __IO uint32_t WIN1_YRGB_MST;                      /* Address Offset: 0x0090 */
    __IO uint32_t WIN1_DSP_INFO;                      /* Address Offset: 0x0094 */
    __IO uint32_t WIN1_DSP_ST;                        /* Address Offset: 0x0098 */
    __IO uint32_t WIN1_COLOR_KEY;                     /* Address Offset: 0x009C */
         uint32_t RESERVED00A0[3];                    /* Address Offset: 0x00A0 */
    __IO uint32_t WIN1_ALPHA_CTRL;                    /* Address Offset: 0x00AC */
    __IO uint32_t WIN1_CBCR_MST;                      /* Address Offset: 0x00B0 */
    __IO uint32_t WIN1_YRGB_MST_RAW;                  /* Address Offset: 0x00B4 */
    __IO uint32_t WIN1_CBCR_MST_RAW;                  /* Address Offset: 0x00B8 */
    __IO uint32_t WIN1_LOOP_OFFSET;                   /* Address Offset: 0x00BC */
    __IO uint32_t WIN2_CTRL0;                         /* Address Offset: 0x00C0 */
    __IO uint32_t WIN2_CTRL1;                         /* Address Offset: 0x00C4 */
    __IO uint32_t WIN2_VIR;                           /* Address Offset: 0x00C8 */
         uint32_t RESERVED00CC;                       /* Address Offset: 0x00CC */
    __IO uint32_t WIN2_YRGB_MST;                      /* Address Offset: 0x00D0 */
    __IO uint32_t WIN2_DSP_INFO;                      /* Address Offset: 0x00D4 */
    __IO uint32_t WIN2_DSP_ST;                        /* Address Offset: 0x00D8 */
    __IO uint32_t WIN2_COLOR_KEY;                     /* Address Offset: 0x00DC */
         uint32_t RESERVED00E0[3];                    /* Address Offset: 0x00E0 */
    __IO uint32_t WIN2_ALPHA_CTRL;                    /* Address Offset: 0x00EC */
    __IO uint32_t WIN2_CBCR_MST;                      /* Address Offset: 0x00F0 */
    __IO uint32_t WIN2_YRGB_MST_RAW;                  /* Address Offset: 0x00F4 */
    __IO uint32_t WIN2_CBCR_MST_RAW;                  /* Address Offset: 0x00F8 */
    __IO uint32_t WIN2_LOOP_OFFSET;                   /* Address Offset: 0x00FC */
    __IO uint32_t DSP_HTOTAL_HS_END;                  /* Address Offset: 0x0100 */
    __IO uint32_t DSP_HACT_ST_END;                    /* Address Offset: 0x0104 */
    __IO uint32_t DSP_VTOTAL_VS_END;                  /* Address Offset: 0x0108 */
    __IO uint32_t DSP_VACT_ST_END;                    /* Address Offset: 0x010C */
    __IO uint32_t DSP_VS_ST_END_F1;                   /* Address Offset: 0x0110 */
    __IO uint32_t DSP_VACT_ST_END_F1;                 /* Address Offset: 0x0114 */
    __IO uint32_t PRE_HTOTAL_HS_END;                  /* Address Offset: 0x0118 */
    __IO uint32_t PRE_HACT_ST_END;                    /* Address Offset: 0x011C */
    __IO uint32_t PRE_VTOTAL_VS_END;                  /* Address Offset: 0x0120 */
    __IO uint32_t PRE_VACT_ST_END;                    /* Address Offset: 0x0124 */
         uint32_t RESERVED0128[14];                   /* Address Offset: 0x0128 */
    __IO uint32_t BCSH_CTRL;                          /* Address Offset: 0x0160 */
    __IO uint32_t BCSH_COL_BAR;                       /* Address Offset: 0x0164 */
    __IO uint32_t BCSH_BCS;                           /* Address Offset: 0x0168 */
    __IO uint32_t BCSH_H;                             /* Address Offset: 0x016C */
    __IO uint32_t GAMMA_COE_WORD0;                    /* Address Offset: 0x0170 */
    __IO uint32_t GAMMA_COE_WORD1;                    /* Address Offset: 0x0174 */
    __IO uint32_t GAMMA_COE_WORD2;                    /* Address Offset: 0x0178 */
    __IO uint32_t GAMMA_COE_WORD3;                    /* Address Offset: 0x017C */
    __IO uint32_t POST_CTRL;                          /* Address Offset: 0x0180 */
    __IO uint32_t COLOR_MATRIX_COE0;                  /* Address Offset: 0x0184 */
    __IO uint32_t COLOR_MATRIX_COE1;                  /* Address Offset: 0x0188 */
    __IO uint32_t COLOR_MATRIX_COE2;                  /* Address Offset: 0x018C */
    __IO uint32_t MCU_WRITE_DATA;                     /* Address Offset: 0x0190 */
         uint32_t RESERVED0194[23];                   /* Address Offset: 0x0194 */
    __I  uint32_t DBG_REG_SCAN_LINE;                  /* Address Offset: 0x01F0 */
    __IO uint32_t BLANKING_VALUE;                     /* Address Offset: 0x01F4 */
    __I  uint32_t FLAG_REG_FRM_VALID;                 /* Address Offset: 0x01F8 */
    __O  uint32_t FLAG_REG;                           /* Address Offset: 0x01FC */
         uint32_t WIN0_BPP_LUT[256];                  /* Address Offset: 0x0200 */
         uint32_t WIN1_BPP_LUT[256];                  /* Address Offset: 0x0600 */
    __IO uint32_t DSC_SYS_CTRL0_IMD;                  /* Address Offset: 0x0A00 */
    __IO uint32_t DSC_SYS_CTRL1;                      /* Address Offset: 0x0A04 */
    __IO uint32_t DSC_SYS_CTRL2;                      /* Address Offset: 0x0A08 */
    __IO uint32_t DSC_SYS_CTRL3;                      /* Address Offset: 0x0A0C */
    __IO uint32_t DSC_CFG[21];                        /* Address Offset: 0x0A10 */
         uint32_t RESERVED0A64[3];                    /* Address Offset: 0x0A64 */
    __IO uint32_t DSC_INT_EN;                         /* Address Offset: 0x0A70 */
    __IO uint32_t DSC_INT_CLR;                        /* Address Offset: 0x0A74 */
    __IO uint32_t DSC_INT_STATUS;                     /* Address Offset: 0x0A78 */
         uint32_t RESERVED0A7C;                       /* Address Offset: 0x0A7C */
    __I  uint32_t DSC_DBG_STATUS0;                    /* Address Offset: 0x0A80 */
    __I  uint32_t DSC_DBG_STATUS1;                    /* Address Offset: 0x0A84 */
    __IO uint32_t DSC_DBG_STATUS2;                    /* Address Offset: 0x0A88 */
};
/* DSI Register Structure Define */
struct DSI_REG {
    __I  uint32_t VERSION;                            /* Address Offset: 0x0000 */
    __IO uint32_t PWR_UP;                             /* Address Offset: 0x0004 */
    __IO uint32_t CLKMGR_CFG;                         /* Address Offset: 0x0008 */
    __IO uint32_t DPI_VCID;                           /* Address Offset: 0x000C */
    __IO uint32_t DPI_COLOR_CODING;                   /* Address Offset: 0x0010 */
    __IO uint32_t DPI_CFG_POL;                        /* Address Offset: 0x0014 */
    __IO uint32_t DPI_LP_CMD_TIM;                     /* Address Offset: 0x0018 */
         uint32_t RESERVED001C[4];                    /* Address Offset: 0x001C */
    __IO uint32_t PCKHDL_CFG;                         /* Address Offset: 0x002C */
    __IO uint32_t GEN_VCID;                           /* Address Offset: 0x0030 */
    __IO uint32_t MODE_CFG;                           /* Address Offset: 0x0034 */
    __IO uint32_t VID_MODE_CFG;                       /* Address Offset: 0x0038 */
    __IO uint32_t VID_PKT_SIZE;                       /* Address Offset: 0x003C */
    __IO uint32_t VID_NUM_CHUNKS;                     /* Address Offset: 0x0040 */
    __IO uint32_t VID_NULL_SIZE;                      /* Address Offset: 0x0044 */
    __IO uint32_t VID_HSA_TIME;                       /* Address Offset: 0x0048 */
    __IO uint32_t VID_HBP_TIME;                       /* Address Offset: 0x004C */
    __IO uint32_t VID_HLINE_TIME;                     /* Address Offset: 0x0050 */
    __IO uint32_t VID_VSA_LINES;                      /* Address Offset: 0x0054 */
    __IO uint32_t VID_VBP_LINES;                      /* Address Offset: 0x0058 */
    __IO uint32_t VID_VFP_LINES;                      /* Address Offset: 0x005C */
    __IO uint32_t VID_VACTIVE_LINES;                  /* Address Offset: 0x0060 */
    __IO uint32_t EDPI_CMD_SIZE;                      /* Address Offset: 0x0064 */
    __IO uint32_t CMD_MODE_CFG;                       /* Address Offset: 0x0068 */
    __IO uint32_t GEN_HDR;                            /* Address Offset: 0x006C */
    __IO uint32_t GEN_PLD_DATA;                       /* Address Offset: 0x0070 */
    __I  uint32_t CMD_PKT_STATUS;                     /* Address Offset: 0x0074 */
    __IO uint32_t TO_CNT_CFG;                         /* Address Offset: 0x0078 */
    __IO uint32_t HS_RD_TO_CNT;                       /* Address Offset: 0x007C */
    __IO uint32_t LP_RD_TO_CNT;                       /* Address Offset: 0x0080 */
    __IO uint32_t HS_WR_TO_CNT;                       /* Address Offset: 0x0084 */
    __IO uint32_t LP_WR_TO_CNT;                       /* Address Offset: 0x0088 */
    __IO uint32_t BTA_TO_CNT;                         /* Address Offset: 0x008C */
    __IO uint32_t SDF_3D;                             /* Address Offset: 0x0090 */
    __IO uint32_t LPCLK_CTRL;                         /* Address Offset: 0x0094 */
    __IO uint32_t PHY_TMR_LPCLK_CFG;                  /* Address Offset: 0x0098 */
    __IO uint32_t PHY_TMR_CFG;                        /* Address Offset: 0x009C */
    __IO uint32_t PHY_RSTZ;                           /* Address Offset: 0x00A0 */
    __IO uint32_t PHY_IF_CFG;                         /* Address Offset: 0x00A4 */
         uint32_t RESERVED00A8[2];                    /* Address Offset: 0x00A8 */
    __I  uint32_t PHY_STATUS;                         /* Address Offset: 0x00B0 */
         uint32_t RESERVED00B4[2];                    /* Address Offset: 0x00B4 */
    __I  uint32_t INT_ST0;                            /* Address Offset: 0x00BC */
    __I  uint32_t INT_ST1;                            /* Address Offset: 0x00C0 */
    __IO uint32_t INT_MSK0;                           /* Address Offset: 0x00C4 */
    __IO uint32_t INT_MSK1;                           /* Address Offset: 0x00C8 */
         uint32_t RESERVED00CC[3];                    /* Address Offset: 0x00CC */
    __O  uint32_t INT_FORCE0;                         /* Address Offset: 0x00D8 */
    __O  uint32_t INT_FORCE1;                         /* Address Offset: 0x00DC */
         uint32_t RESERVED00E0[8];                    /* Address Offset: 0x00E0 */
    __IO uint32_t VID_SHADOW_CTRL;                    /* Address Offset: 0x0100 */
         uint32_t RESERVED0104[2];                    /* Address Offset: 0x0104 */
    __I  uint32_t DPI_VCID_ACT;                       /* Address Offset: 0x010C */
    __I  uint32_t DPI_COLOR_CODING_ACT;               /* Address Offset: 0x0110 */
         uint32_t RESERVED0114;                       /* Address Offset: 0x0114 */
    __I  uint32_t DPI_LP_CMD_TIM_ACT;                 /* Address Offset: 0x0118 */
         uint32_t RESERVED011C[7];                    /* Address Offset: 0x011C */
    __I  uint32_t VID_MODE_CFG_ACT;                   /* Address Offset: 0x0138 */
    __I  uint32_t VID_PKT_SIZE_ACT;                   /* Address Offset: 0x013C */
    __I  uint32_t VID_NUM_CHUNKS_ACT;                 /* Address Offset: 0x0140 */
    __I  uint32_t VID_NULL_SIZE_ACT;                  /* Address Offset: 0x0144 */
    __I  uint32_t VID_HSA_TIME_ACT;                   /* Address Offset: 0x0148 */
    __I  uint32_t VID_HBP_TIME_ACT;                   /* Address Offset: 0x014C */
    __I  uint32_t VID_HLINE_TIME_ACT;                 /* Address Offset: 0x0150 */
    __I  uint32_t VID_VSA_LINES_ACT;                  /* Address Offset: 0x0154 */
    __I  uint32_t VID_VBP_LINES_ACT;                  /* Address Offset: 0x0158 */
    __I  uint32_t VID_VFP_LINES_ACT;                  /* Address Offset: 0x015C */
    __I  uint32_t VID_VACTIVE_LINES_ACT;              /* Address Offset: 0x0160 */
         uint32_t RESERVED0164[11];                   /* Address Offset: 0x0164 */
    __IO uint32_t SDF_3D_ACT;                         /* Address Offset: 0x0190 */
};
/* VICAP Register Structure Define */
struct VICAP_REG {
    __IO uint32_t DVP_CTRL;                           /* Address Offset: 0x0000 */
    __IO uint32_t DVP_INTEN;                          /* Address Offset: 0x0004 */
    __IO uint32_t DVP_INTSTAT;                        /* Address Offset: 0x0008 */
    __IO uint32_t DVP_FOR;                            /* Address Offset: 0x000C */
    __IO uint32_t DVP_DMA_IDLE_REQ;                   /* Address Offset: 0x0010 */
    __IO uint32_t DVP_FRM0_ADDR_Y;                    /* Address Offset: 0x0014 */
    __IO uint32_t DVP_FRM0_ADDR_UV;                   /* Address Offset: 0x0018 */
    __IO uint32_t DVP_FRM1_ADDR_Y;                    /* Address Offset: 0x001C */
    __IO uint32_t DVP_FRM1_ADDR_UV;                   /* Address Offset: 0x0020 */
    __IO uint32_t DVP_VIR_LINE_WIDTH;                 /* Address Offset: 0x0024 */
    __IO uint32_t DVP_SET_SIZE;                       /* Address Offset: 0x0028 */
    __IO uint32_t DVP_BLOCK_LINE_NUM;                 /* Address Offset: 0x002C */
    __IO uint32_t DVP_BLOCK0_ADDR_Y;                  /* Address Offset: 0x0030 */
    __IO uint32_t DVP_BLOCK0_ADDR_UV;                 /* Address Offset: 0x0034 */
    __IO uint32_t DVP_BLOCK1_ADDR_Y;                  /* Address Offset: 0x0038 */
    __IO uint32_t DVP_BLOCK1_ADDR_UV;                 /* Address Offset: 0x003C */
    __IO uint32_t DVP_BLOCK_STATUS;                   /* Address Offset: 0x0040 */
    __IO uint32_t DVP_CROP;                           /* Address Offset: 0x0044 */
    __IO uint32_t DVP_PATH_SEL;                       /* Address Offset: 0x0048 */
    __IO uint32_t DVP_LINE_INT_NUM;                   /* Address Offset: 0x004C */
    __IO uint32_t DVP_WATER_LINE;                     /* Address Offset: 0x0050 */
    __IO uint32_t DVP_FIFO_ENTRY;                     /* Address Offset: 0x0054 */
         uint32_t RESERVED0058[2];                    /* Address Offset: 0x0058 */
    __I  uint32_t DVP_FRAME_STATUS;                   /* Address Offset: 0x0060 */
    __I  uint32_t DVP_CUR_DST;                        /* Address Offset: 0x0064 */
    __IO uint32_t DVP_LAST_LINE;                      /* Address Offset: 0x0068 */
    __IO uint32_t DVP_LAST_PIX;                       /* Address Offset: 0x006C */
};
/* AUDIOPWM Register Structure Define */
struct AUDIOPWM_REG {
    __I  uint32_t VERSION;                            /* Address Offset: 0x0000 */
    __IO uint32_t XFER;                               /* Address Offset: 0x0004 */
    __IO uint32_t SRC_CFG;                            /* Address Offset: 0x0008 */
         uint32_t RESERVED000C;                       /* Address Offset: 0x000C */
    __IO uint32_t PWM_CFG;                            /* Address Offset: 0x0010 */
    __I  uint32_t PWM_ST;                             /* Address Offset: 0x0014 */
    __I  uint32_t PWM_BUF_01;                         /* Address Offset: 0x0018 */
    __I  uint32_t PWM_BUF_23;                         /* Address Offset: 0x001C */
    __IO uint32_t FIFO_CFG;                           /* Address Offset: 0x0020 */
    __I  uint32_t FIFO_LVL;                           /* Address Offset: 0x0024 */
    __IO uint32_t FIFO_INT_EN;                        /* Address Offset: 0x0028 */
    __IO uint32_t FIFO_INT_ST;                        /* Address Offset: 0x002C */
         uint32_t RESERVED0030[20];                   /* Address Offset: 0x0030 */
    __O  uint32_t FIFO_ENTRY;                         /* Address Offset: 0x0080 */
};
#endif /*  __ASSEMBLY__  */
/****************************************************************************************/
/*                                                                                      */
/*                                Module Address Section                                */
/*                                                                                      */
/****************************************************************************************/
/* Memory Base */
#define ICACHE_BASE         0x40000000U /* ICACHE base address */
#define DCACHE_BASE         0x40004000U /* DCACHE base address */
#define CRU_BASE            0x40050000U /* CRU base address */
#define GRF_BASE            0x400B0000U /* GRF base address */
#define MBOX0_BASE          0x40100000U /* MBOX0 base address */
#define MBOX1_BASE          0x40110000U /* MBOX1 base address */
#define MBOX2_BASE          0x40120000U /* MBOX2 base address */
#define PMU_BASE            0x40130000U /* PMU base address */
#define DMA_BASE            0x401C0000U /* DMA base address */
#define ACDCDIG_BASE        0x40300000U /* ACDCDIG base address */
#define UART0_BASE          0x40800000U /* UART0 base address */
#define UART1_BASE          0x40810000U /* UART1 base address */
#define UART2_BASE          0x40820000U /* UART2 base address */
#define PWM0_BASE           0x40880000U /* PWM0 base address */
#define TIMER0_BASE         0x40900000U /* TIMER0 base address */
#define TIMER1_BASE         0x40900020U /* TIMER1 base address */
#define TIMER2_BASE         0x40900040U /* TIMER2 base address */
#define TIMER3_BASE         0x40900060U /* TIMER3 base address */
#define TIMER4_BASE         0x40900080U /* TIMER4 base address */
#define TIMER5_BASE         0x409000A0U /* TIMER5 base address */
#define WDT_BASE            0x40A00000U /* WDT base address */
#define I2C0_BASE           0x40B00000U /* I2C0 base address */
#define I2C1_BASE           0x40B10000U /* I2C1 base address */
#define I2C2_BASE           0x40B20000U /* I2C2 base address */
#define SPI2APB_BASE        0x40C00000U /* SPI2APB base address */
#define SPI1_BASE           0x40C10000U /* SPI1 base address */
#define SPI2_BASE           0x40C20000U /* SPI2 base address */
#define FSPI0_BASE          0x40C80000U /* FSPI0 base address */
#define MMC_BASE            0x40C90000U /* MMC base address */
#define FSPI1_BASE          0x40CA0000U /* FSPI1 base address */
#define GPIO0_BASE          0x40D00000U /* GPIO0 base address */
#define GPIO1_BASE          0x40D10000U /* GPIO1 base address */
#define KEY_CTRL_BASE       0x40E00000U /* KEY_CTRL base address */
#define PDM0_BASE           0x41000000U /* PDM0 base address */
#define I2STDM0_BASE        0x41010000U /* I2STDM0 base address */
#define VAD_BASE            0x41020000U /* VAD base address */
#define I2STDM1_BASE        0x41030000U /* I2STDM1 base address */
#define VOP_BASE            0x41100000U /* VOP base address */
#define DSI_BASE            0x41110000U /* DSI base address */
#define VICAP_BASE          0x41120000U /* VICAP base address */
#define AUDIOPWM_BASE       0x41200000U /* AUDIOPWM base address */
/****************************************************************************************/
/*                                                                                      */
/*                               Module Variable Section                                */
/*                                                                                      */
/****************************************************************************************/
/* Module Variable Define */

#define ICACHE              ((struct ICACHE_REG *) ICACHE_BASE)
#define DCACHE              ((struct DCACHE_REG *) DCACHE_BASE)
#define CRU                 ((struct CRU_REG *) CRU_BASE)
#define GRF                 ((struct GRF_REG *) GRF_BASE)
#define MBOX0               ((struct MBOX_REG *) MBOX0_BASE)
#define MBOX1               ((struct MBOX_REG *) MBOX1_BASE)
#define MBOX2               ((struct MBOX_REG *) MBOX2_BASE)
#define PMU                 ((struct PMU_REG *) PMU_BASE)
#define DMA                 ((struct DMA_REG *) DMA_BASE)
#define ACDCDIG             ((struct ACDCDIG_REG *) ACDCDIG_BASE)
#define UART0               ((struct UART_REG *) UART0_BASE)
#define UART1               ((struct UART_REG *) UART1_BASE)
#define UART2               ((struct UART_REG *) UART2_BASE)
#define PWM0                ((struct PWM_REG *) PWM0_BASE)
#define TIMER0              ((struct TIMER_REG *) TIMER0_BASE)
#define TIMER1              ((struct TIMER_REG *) TIMER1_BASE)
#define TIMER2              ((struct TIMER_REG *) TIMER2_BASE)
#define TIMER3              ((struct TIMER_REG *) TIMER3_BASE)
#define TIMER4              ((struct TIMER_REG *) TIMER4_BASE)
#define TIMER5              ((struct TIMER_REG *) TIMER5_BASE)
#define WDT                 ((struct WDT_REG *) WDT_BASE)
#define I2C0                ((struct I2C_REG *) I2C0_BASE)
#define I2C1                ((struct I2C_REG *) I2C1_BASE)
#define I2C2                ((struct I2C_REG *) I2C2_BASE)
#define SPI2APB             ((struct SPI2APB_REG *) SPI2APB_BASE)
#define SPI1                ((struct SPI_REG *) SPI1_BASE)
#define SPI2                ((struct SPI_REG *) SPI2_BASE)
#define FSPI0               ((struct FSPI_REG *) FSPI0_BASE)
#define MMC                 ((struct MMC_REG *) MMC_BASE)
#define FSPI1               ((struct FSPI_REG *) FSPI1_BASE)
#define GPIO0               ((struct GPIO_REG *) GPIO0_BASE)
#define GPIO1               ((struct GPIO_REG *) GPIO1_BASE)
#define KEY_CTRL            ((struct KEY_CTRL_REG *) KEY_CTRL_BASE)
#define PDM0                ((struct PDM_REG *) PDM0_BASE)
#define I2STDM0             ((struct I2STDM_REG *) I2STDM0_BASE)
#define VAD                 ((struct VAD_REG *) VAD_BASE)
#define I2STDM1             ((struct I2STDM_REG *) I2STDM1_BASE)
#define VOP                 ((struct VOP_REG *) VOP_BASE)
#define DSI                 ((struct DSI_REG *) DSI_BASE)
#define VICAP               ((struct VICAP_REG *) VICAP_BASE)
#define AUDIOPWM            ((struct AUDIOPWM_REG *) AUDIOPWM_BASE)

#define IS_ICACHE_INSTANCE(instance) ((instance) == ICACHE)
#define IS_DCACHE_INSTANCE(instance) ((instance) == DCACHE)
#define IS_CRU_INSTANCE(instance) ((instance) == CRU)
#define IS_GRF_INSTANCE(instance) ((instance) == GRF)
#define IS_PMU_INSTANCE(instance) ((instance) == PMU)
#define IS_DMA_INSTANCE(instance) ((instance) == DMA)
#define IS_ACDCDIG_INSTANCE(instance) ((instance) == ACDCDIG)
#define IS_WDT_INSTANCE(instance) ((instance) == WDT)
#define IS_SPI2APB_INSTANCE(instance) ((instance) == SPI2APB)
#define IS_MMC_INSTANCE(instance) ((instance) == MMC)
#define IS_KEY_CTRL_INSTANCE(instance) ((instance) == KEY_CTRL)
#define IS_VAD_INSTANCE(instance) ((instance) == VAD)
#define IS_VOP_INSTANCE(instance) ((instance) == VOP)
#define IS_DSI_INSTANCE(instance) ((instance) == DSI)
#define IS_VICAP_INSTANCE(instance) ((instance) == VICAP)
#define IS_AUDIOPWM_INSTANCE(instance) ((instance) == AUDIOPWM)
#define IS_MBOX_INSTANCE(instance) (((instance) == MBOX0) || ((instance) == MBOX1) || ((instance) == MBOX2))
#define IS_UART_INSTANCE(instance) (((instance) == UART0) || ((instance) == UART1) || ((instance) == UART2))
#define IS_PWM_INSTANCE(instance) ((instance) == PWM0)
#define IS_TIMER_INSTANCE(instance) (((instance) == TIMER0) || ((instance) == TIMER1) || ((instance) == TIMER2) || ((instance) == TIMER3) || ((instance) == TIMER4) || ((instance) == TIMER5))
#define IS_I2C_INSTANCE(instance) (((instance) == I2C0) || ((instance) == I2C1) || ((instance) == I2C2))
#define IS_SPI_INSTANCE(instance) (((instance) == SPI1) || ((instance) == SPI2))
#define IS_FSPI_INSTANCE(instance) (((instance) == FSPI0) || ((instance) == FSPI1))
#define IS_GPIO_INSTANCE(instance) (((instance) == GPIO0) || ((instance) == GPIO1))
#define IS_PDM_INSTANCE(instance) ((instance) == PDM0)
#define IS_I2STDM_INSTANCE(instance) (((instance) == I2STDM0) || ((instance) == I2STDM1))
/****************************************************************************************/
/*                                                                                      */
/*                               Register Bitmap Section                                */
/*                                                                                      */
/****************************************************************************************/
/*****************************************ICACHE*****************************************/
/* CACHE_CTRL */
#define ICACHE_CACHE_CTRL_OFFSET                           (0x0U)
#define ICACHE_CACHE_CTRL_CACHE_EN_SHIFT                   (0U)
#define ICACHE_CACHE_CTRL_CACHE_EN_MASK                    (0x1U << ICACHE_CACHE_CTRL_CACHE_EN_SHIFT)                   /* 0x00000001 */
#define ICACHE_CACHE_CTRL_CACHE_WT_EN_SHIFT                (1U)
#define ICACHE_CACHE_CTRL_CACHE_WT_EN_MASK                 (0x1U << ICACHE_CACHE_CTRL_CACHE_WT_EN_SHIFT)                /* 0x00000002 */
#define ICACHE_CACHE_CTRL_CACHE_HB_EN_SHIFT                (2U)
#define ICACHE_CACHE_CTRL_CACHE_HB_EN_MASK                 (0x1U << ICACHE_CACHE_CTRL_CACHE_HB_EN_SHIFT)                /* 0x00000004 */
#define ICACHE_CACHE_CTRL_CACHE_STB_EN_SHIFT               (3U)
#define ICACHE_CACHE_CTRL_CACHE_STB_EN_MASK                (0x1U << ICACHE_CACHE_CTRL_CACHE_STB_EN_SHIFT)               /* 0x00000008 */
#define ICACHE_CACHE_CTRL_CACHE_FLUSH_SHIFT                (4U)
#define ICACHE_CACHE_CTRL_CACHE_FLUSH_MASK                 (0x1U << ICACHE_CACHE_CTRL_CACHE_FLUSH_SHIFT)                /* 0x00000010 */
#define ICACHE_CACHE_CTRL_CACHE_PMU_EN_SHIFT               (5U)
#define ICACHE_CACHE_CTRL_CACHE_PMU_EN_MASK                (0x1U << ICACHE_CACHE_CTRL_CACHE_PMU_EN_SHIFT)               /* 0x00000020 */
#define ICACHE_CACHE_CTRL_CACHE_BYPASS_SHIFT               (6U)
#define ICACHE_CACHE_CTRL_CACHE_BYPASS_MASK                (0x1U << ICACHE_CACHE_CTRL_CACHE_BYPASS_SHIFT)               /* 0x00000040 */
#define ICACHE_CACHE_CTRL_STB_TIMEOUT_EN_SHIFT             (7U)
#define ICACHE_CACHE_CTRL_STB_TIMEOUT_EN_MASK              (0x1U << ICACHE_CACHE_CTRL_STB_TIMEOUT_EN_SHIFT)             /* 0x00000080 */
#define ICACHE_CACHE_CTRL_CACHE_ENTRY_THRESH_SHIFT         (8U)
#define ICACHE_CACHE_CTRL_CACHE_ENTRY_THRESH_MASK          (0x7U << ICACHE_CACHE_CTRL_CACHE_ENTRY_THRESH_SHIFT)         /* 0x00000700 */
#define ICACHE_CACHE_CTRL_CACHE_MPU_MODE_SHIFT             (12U)
#define ICACHE_CACHE_CTRL_CACHE_MPU_MODE_MASK              (0x1U << ICACHE_CACHE_CTRL_CACHE_MPU_MODE_SHIFT)             /* 0x00001000 */
#define ICACHE_CACHE_CTRL_CACHE_PF_EN_SHIFT                (13U)
#define ICACHE_CACHE_CTRL_CACHE_PF_EN_MASK                 (0x1U << ICACHE_CACHE_CTRL_CACHE_PF_EN_SHIFT)                /* 0x00002000 */
/* CACHE_MAINTAIN0 */
#define ICACHE_CACHE_MAINTAIN0_OFFSET                      (0x4U)
#define ICACHE_CACHE_MAINTAIN0_CACHE_M_VALID_SHIFT         (0U)
#define ICACHE_CACHE_MAINTAIN0_CACHE_M_VALID_MASK          (0x1U << ICACHE_CACHE_MAINTAIN0_CACHE_M_VALID_SHIFT)         /* 0x00000001 */
#define ICACHE_CACHE_MAINTAIN0_CACHE_M_CMD_SHIFT           (1U)
#define ICACHE_CACHE_MAINTAIN0_CACHE_M_CMD_MASK            (0x3U << ICACHE_CACHE_MAINTAIN0_CACHE_M_CMD_SHIFT)           /* 0x00000006 */
#define ICACHE_CACHE_MAINTAIN0_CACHE_M_ADDR_SHIFT          (5U)
#define ICACHE_CACHE_MAINTAIN0_CACHE_M_ADDR_MASK           (0x7FFFFFFU << ICACHE_CACHE_MAINTAIN0_CACHE_M_ADDR_SHIFT)    /* 0xFFFFFFE0 */
/* CACHE_MAINTAIN1 */
#define ICACHE_CACHE_MAINTAIN1_OFFSET                      (0x8U)
#define ICACHE_CACHE_MAINTAIN1_CACHE_M_OFFSET_SHIFT        (0U)
#define ICACHE_CACHE_MAINTAIN1_CACHE_M_OFFSET_MASK         (0xFFFFU << ICACHE_CACHE_MAINTAIN1_CACHE_M_OFFSET_SHIFT)     /* 0x0000FFFF */
/* STB_TIMEOUT_CTRL */
#define ICACHE_STB_TIMEOUT_CTRL_OFFSET                     (0xCU)
#define ICACHE_STB_TIMEOUT_CTRL_STB_TIMEOUT_VALUE_SHIFT    (0U)
#define ICACHE_STB_TIMEOUT_CTRL_STB_TIMEOUT_VALUE_MASK     (0x7FFFFU << ICACHE_STB_TIMEOUT_CTRL_STB_TIMEOUT_VALUE_SHIFT) /* 0x0007FFFF */
/* CACHE_INT_EN */
#define ICACHE_CACHE_INT_EN_OFFSET                         (0x20U)
#define ICACHE_CACHE_INT_EN_ERR_RECORD_EN_SHIFT            (0U)
#define ICACHE_CACHE_INT_EN_ERR_RECORD_EN_MASK             (0x1U << ICACHE_CACHE_INT_EN_ERR_RECORD_EN_SHIFT)            /* 0x00000001 */
/* CACHE_INT_ST */
#define ICACHE_CACHE_INT_ST_OFFSET                         (0x24U)
#define ICACHE_CACHE_INT_ST_AHB_ERROR_STATUS_SHIFT         (0U)
#define ICACHE_CACHE_INT_ST_AHB_ERROR_STATUS_MASK          (0x1U << ICACHE_CACHE_INT_ST_AHB_ERROR_STATUS_SHIFT)         /* 0x00000001 */
/* CACHE_ERR_HADDR */
#define ICACHE_CACHE_ERR_HADDR_OFFSET                      (0x28U)
#define ICACHE_CACHE_ERR_HADDR_STATUS_HADDR_SHIFT          (0U)
#define ICACHE_CACHE_ERR_HADDR_STATUS_HADDR_MASK           (0x1U << ICACHE_CACHE_ERR_HADDR_STATUS_HADDR_SHIFT)          /* 0x00000001 */
/* CACHE_STATUS */
#define ICACHE_CACHE_STATUS_OFFSET                         (0x30U)
#define ICACHE_CACHE_STATUS                                (0x0U)
#define ICACHE_CACHE_STATUS_CACHE_INIT_FINISH_SHIFT        (0U)
#define ICACHE_CACHE_STATUS_CACHE_INIT_FINISH_MASK         (0x1U << ICACHE_CACHE_STATUS_CACHE_INIT_FINISH_SHIFT)        /* 0x00000001 */
#define ICACHE_CACHE_STATUS_CACHE_M_BUSY_SHIFT             (1U)
#define ICACHE_CACHE_STATUS_CACHE_M_BUSY_MASK              (0x1U << ICACHE_CACHE_STATUS_CACHE_M_BUSY_SHIFT)             /* 0x00000002 */
#define ICACHE_CACHE_STATUS_CACHE_FLUSH_DONE_SHIFT         (2U)
#define ICACHE_CACHE_STATUS_CACHE_FLUSH_DONE_MASK          (0x1U << ICACHE_CACHE_STATUS_CACHE_FLUSH_DONE_SHIFT)         /* 0x00000004 */
/* PMU_RD_NUM_CNT */
#define ICACHE_PMU_RD_NUM_CNT_OFFSET                       (0x40U)
#define ICACHE_PMU_RD_NUM_CNT                              (0x0U)
#define ICACHE_PMU_RD_NUM_CNT_PMU_RD_NUM_CNT_SHIFT         (0U)
#define ICACHE_PMU_RD_NUM_CNT_PMU_RD_NUM_CNT_MASK          (0xFFFFFFFFU << ICACHE_PMU_RD_NUM_CNT_PMU_RD_NUM_CNT_SHIFT)  /* 0xFFFFFFFF */
/* PMU_WR_NUM_CNT */
#define ICACHE_PMU_WR_NUM_CNT_OFFSET                       (0x44U)
#define ICACHE_PMU_WR_NUM_CNT                              (0x0U)
#define ICACHE_PMU_WR_NUM_CNT_PMU_WR_NUM_CNT_SHIFT         (0U)
#define ICACHE_PMU_WR_NUM_CNT_PMU_WR_NUM_CNT_MASK          (0xFFFFFFFFU << ICACHE_PMU_WR_NUM_CNT_PMU_WR_NUM_CNT_SHIFT)  /* 0xFFFFFFFF */
/* PMU_SRAM_RD_HIT_CNT */
#define ICACHE_PMU_SRAM_RD_HIT_CNT_OFFSET                  (0x48U)
#define ICACHE_PMU_SRAM_RD_HIT_CNT                         (0x0U)
#define ICACHE_PMU_SRAM_RD_HIT_CNT_PMU_SRAM_RD_HIT_CNT_SHIFT (0U)
#define ICACHE_PMU_SRAM_RD_HIT_CNT_PMU_SRAM_RD_HIT_CNT_MASK (0xFFFFFFFFU << ICACHE_PMU_SRAM_RD_HIT_CNT_PMU_SRAM_RD_HIT_CNT_SHIFT) /* 0xFFFFFFFF */
/* PMU_HB_RD_HIT_CNT */
#define ICACHE_PMU_HB_RD_HIT_CNT_OFFSET                    (0x4CU)
#define ICACHE_PMU_HB_RD_HIT_CNT                           (0x0U)
#define ICACHE_PMU_HB_RD_HIT_CNT_PMU_HB_RD_HIT_CNT_SHIFT   (0U)
#define ICACHE_PMU_HB_RD_HIT_CNT_PMU_HB_RD_HIT_CNT_MASK    (0xFFFFFFFFU << ICACHE_PMU_HB_RD_HIT_CNT_PMU_HB_RD_HIT_CNT_SHIFT) /* 0xFFFFFFFF */
/* PMU_STB_RD_HIT_CNT */
#define ICACHE_PMU_STB_RD_HIT_CNT_OFFSET                   (0x50U)
#define ICACHE_PMU_STB_RD_HIT_CNT_PMU_STB_RD_HIT_CNT_SHIFT (0U)
#define ICACHE_PMU_STB_RD_HIT_CNT_PMU_STB_RD_HIT_CNT_MASK  (0xFFFFFFFFU << ICACHE_PMU_STB_RD_HIT_CNT_PMU_STB_RD_HIT_CNT_SHIFT) /* 0xFFFFFFFF */
/* PMU_RD_HIT_CNT */
#define ICACHE_PMU_RD_HIT_CNT_OFFSET                       (0x54U)
#define ICACHE_PMU_RD_HIT_CNT                              (0x0U)
#define ICACHE_PMU_RD_HIT_CNT_PMU_RD_HIT_CNT_SHIFT         (0U)
#define ICACHE_PMU_RD_HIT_CNT_PMU_RD_HIT_CNT_MASK          (0xFFFFFFFFU << ICACHE_PMU_RD_HIT_CNT_PMU_RD_HIT_CNT_SHIFT)  /* 0xFFFFFFFF */
/* PMU_WR_HIT_CNT */
#define ICACHE_PMU_WR_HIT_CNT_OFFSET                       (0x58U)
#define ICACHE_PMU_WR_HIT_CNT                              (0x0U)
#define ICACHE_PMU_WR_HIT_CNT_PMU_WR_HIT_CNT_SHIFT         (0U)
#define ICACHE_PMU_WR_HIT_CNT_PMU_WR_HIT_CNT_MASK          (0xFFFFFFFFU << ICACHE_PMU_WR_HIT_CNT_PMU_WR_HIT_CNT_SHIFT)  /* 0xFFFFFFFF */
/* PMU_RD_MISS_PENALTY_CNT */
#define ICACHE_PMU_RD_MISS_PENALTY_CNT_OFFSET              (0x5CU)
#define ICACHE_PMU_RD_MISS_PENALTY_CNT                     (0x0U)
#define ICACHE_PMU_RD_MISS_PENALTY_CNT_PMU_RD_MISS_PENALTY_CNT_SHIFT (0U)
#define ICACHE_PMU_RD_MISS_PENALTY_CNT_PMU_RD_MISS_PENALTY_CNT_MASK (0xFFFFFFFFU << ICACHE_PMU_RD_MISS_PENALTY_CNT_PMU_RD_MISS_PENALTY_CNT_SHIFT) /* 0xFFFFFFFF */
/* PMU_WR_MISS_PENALTY_CNT */
#define ICACHE_PMU_WR_MISS_PENALTY_CNT_OFFSET              (0x60U)
#define ICACHE_PMU_WR_MISS_PENALTY_CNT                     (0x0U)
#define ICACHE_PMU_WR_MISS_PENALTY_CNT_PMU_WR_MISS_PENALTY_CNT_SHIFT (0U)
#define ICACHE_PMU_WR_MISS_PENALTY_CNT_PMU_WR_MISS_PENALTY_CNT_MASK (0xFFFFFFFFU << ICACHE_PMU_WR_MISS_PENALTY_CNT_PMU_WR_MISS_PENALTY_CNT_SHIFT) /* 0xFFFFFFFF */
/* PMU_RD_LAT_CNT */
#define ICACHE_PMU_RD_LAT_CNT_OFFSET                       (0x64U)
#define ICACHE_PMU_RD_LAT_CNT                              (0x0U)
#define ICACHE_PMU_RD_LAT_CNT_PMU_RD_LAT_CNT_SHIFT         (0U)
#define ICACHE_PMU_RD_LAT_CNT_PMU_RD_LAT_CNT_MASK          (0xFFFFFFFFU << ICACHE_PMU_RD_LAT_CNT_PMU_RD_LAT_CNT_SHIFT)  /* 0xFFFFFFFF */
/* PMU_WR_LAT_CNT */
#define ICACHE_PMU_WR_LAT_CNT_OFFSET                       (0x68U)
#define ICACHE_PMU_WR_LAT_CNT                              (0x0U)
#define ICACHE_PMU_WR_LAT_CNT_PMU_RD_LAT_CNT_SHIFT         (0U)
#define ICACHE_PMU_WR_LAT_CNT_PMU_RD_LAT_CNT_MASK          (0xFFFFFFFFU << ICACHE_PMU_WR_LAT_CNT_PMU_RD_LAT_CNT_SHIFT)  /* 0xFFFFFFFF */
/* REVISION */
#define ICACHE_REVISION_OFFSET                             (0xF0U)
#define ICACHE_REVISION_REVISION_SHIFT                     (0U)
#define ICACHE_REVISION_REVISION_MASK                      (0xFFFFFFFFU << ICACHE_REVISION_REVISION_SHIFT)              /* 0xFFFFFFFF */
/*****************************************DCACHE*****************************************/
/* CACHE_CTRL */
#define DCACHE_CACHE_CTRL_OFFSET                           (0x0U)
#define DCACHE_CACHE_CTRL_CACHE_EN_SHIFT                   (0U)
#define DCACHE_CACHE_CTRL_CACHE_EN_MASK                    (0x1U << DCACHE_CACHE_CTRL_CACHE_EN_SHIFT)                   /* 0x00000001 */
#define DCACHE_CACHE_CTRL_CACHE_WT_EN_SHIFT                (1U)
#define DCACHE_CACHE_CTRL_CACHE_WT_EN_MASK                 (0x1U << DCACHE_CACHE_CTRL_CACHE_WT_EN_SHIFT)                /* 0x00000002 */
#define DCACHE_CACHE_CTRL_CACHE_HB_EN_SHIFT                (2U)
#define DCACHE_CACHE_CTRL_CACHE_HB_EN_MASK                 (0x1U << DCACHE_CACHE_CTRL_CACHE_HB_EN_SHIFT)                /* 0x00000004 */
#define DCACHE_CACHE_CTRL_CACHE_STB_EN_SHIFT               (3U)
#define DCACHE_CACHE_CTRL_CACHE_STB_EN_MASK                (0x1U << DCACHE_CACHE_CTRL_CACHE_STB_EN_SHIFT)               /* 0x00000008 */
#define DCACHE_CACHE_CTRL_CACHE_FLUSH_SHIFT                (4U)
#define DCACHE_CACHE_CTRL_CACHE_FLUSH_MASK                 (0x1U << DCACHE_CACHE_CTRL_CACHE_FLUSH_SHIFT)                /* 0x00000010 */
#define DCACHE_CACHE_CTRL_CACHE_PMU_EN_SHIFT               (5U)
#define DCACHE_CACHE_CTRL_CACHE_PMU_EN_MASK                (0x1U << DCACHE_CACHE_CTRL_CACHE_PMU_EN_SHIFT)               /* 0x00000020 */
#define DCACHE_CACHE_CTRL_CACHE_BYPASS_SHIFT               (6U)
#define DCACHE_CACHE_CTRL_CACHE_BYPASS_MASK                (0x1U << DCACHE_CACHE_CTRL_CACHE_BYPASS_SHIFT)               /* 0x00000040 */
#define DCACHE_CACHE_CTRL_STB_TIMEOUT_EN_SHIFT             (7U)
#define DCACHE_CACHE_CTRL_STB_TIMEOUT_EN_MASK              (0x1U << DCACHE_CACHE_CTRL_STB_TIMEOUT_EN_SHIFT)             /* 0x00000080 */
#define DCACHE_CACHE_CTRL_CACHE_ENTRY_THRESH_SHIFT         (8U)
#define DCACHE_CACHE_CTRL_CACHE_ENTRY_THRESH_MASK          (0x7U << DCACHE_CACHE_CTRL_CACHE_ENTRY_THRESH_SHIFT)         /* 0x00000700 */
#define DCACHE_CACHE_CTRL_CACHE_MPU_MODE_SHIFT             (12U)
#define DCACHE_CACHE_CTRL_CACHE_MPU_MODE_MASK              (0x1U << DCACHE_CACHE_CTRL_CACHE_MPU_MODE_SHIFT)             /* 0x00001000 */
#define DCACHE_CACHE_CTRL_CACHE_PF_EN_SHIFT                (13U)
#define DCACHE_CACHE_CTRL_CACHE_PF_EN_MASK                 (0x1U << DCACHE_CACHE_CTRL_CACHE_PF_EN_SHIFT)                /* 0x00002000 */
/* CACHE_MAINTAIN0 */
#define DCACHE_CACHE_MAINTAIN0_OFFSET                      (0x4U)
#define DCACHE_CACHE_MAINTAIN0_CACHE_M_VALID_SHIFT         (0U)
#define DCACHE_CACHE_MAINTAIN0_CACHE_M_VALID_MASK          (0x1U << DCACHE_CACHE_MAINTAIN0_CACHE_M_VALID_SHIFT)         /* 0x00000001 */
#define DCACHE_CACHE_MAINTAIN0_CACHE_M_CMD_SHIFT           (1U)
#define DCACHE_CACHE_MAINTAIN0_CACHE_M_CMD_MASK            (0x3U << DCACHE_CACHE_MAINTAIN0_CACHE_M_CMD_SHIFT)           /* 0x00000006 */
#define DCACHE_CACHE_MAINTAIN0_CACHE_M_ADDR_SHIFT          (5U)
#define DCACHE_CACHE_MAINTAIN0_CACHE_M_ADDR_MASK           (0x7FFFFFFU << DCACHE_CACHE_MAINTAIN0_CACHE_M_ADDR_SHIFT)    /* 0xFFFFFFE0 */
/* CACHE_MAINTAIN1 */
#define DCACHE_CACHE_MAINTAIN1_OFFSET                      (0x8U)
#define DCACHE_CACHE_MAINTAIN1_CACHE_M_OFFSET_SHIFT        (0U)
#define DCACHE_CACHE_MAINTAIN1_CACHE_M_OFFSET_MASK         (0xFFFFU << DCACHE_CACHE_MAINTAIN1_CACHE_M_OFFSET_SHIFT)     /* 0x0000FFFF */
/* STB_TIMEOUT_CTRL */
#define DCACHE_STB_TIMEOUT_CTRL_OFFSET                     (0xCU)
#define DCACHE_STB_TIMEOUT_CTRL_STB_TIMEOUT_VALUE_SHIFT    (0U)
#define DCACHE_STB_TIMEOUT_CTRL_STB_TIMEOUT_VALUE_MASK     (0x7FFFFU << DCACHE_STB_TIMEOUT_CTRL_STB_TIMEOUT_VALUE_SHIFT) /* 0x0007FFFF */
/* CACHE_INT_EN */
#define DCACHE_CACHE_INT_EN_OFFSET                         (0x20U)
#define DCACHE_CACHE_INT_EN_ERR_RECORD_EN_SHIFT            (0U)
#define DCACHE_CACHE_INT_EN_ERR_RECORD_EN_MASK             (0x1U << DCACHE_CACHE_INT_EN_ERR_RECORD_EN_SHIFT)            /* 0x00000001 */
/* CACHE_INT_ST */
#define DCACHE_CACHE_INT_ST_OFFSET                         (0x24U)
#define DCACHE_CACHE_INT_ST_AHB_ERROR_STATUS_SHIFT         (0U)
#define DCACHE_CACHE_INT_ST_AHB_ERROR_STATUS_MASK          (0x1U << DCACHE_CACHE_INT_ST_AHB_ERROR_STATUS_SHIFT)         /* 0x00000001 */
/* CACHE_ERR_HADDR */
#define DCACHE_CACHE_ERR_HADDR_OFFSET                      (0x28U)
#define DCACHE_CACHE_ERR_HADDR_STATUS_HADDR_SHIFT          (0U)
#define DCACHE_CACHE_ERR_HADDR_STATUS_HADDR_MASK           (0x1U << DCACHE_CACHE_ERR_HADDR_STATUS_HADDR_SHIFT)          /* 0x00000001 */
/* CACHE_STATUS */
#define DCACHE_CACHE_STATUS_OFFSET                         (0x30U)
#define DCACHE_CACHE_STATUS                                (0x0U)
#define DCACHE_CACHE_STATUS_CACHE_INIT_FINISH_SHIFT        (0U)
#define DCACHE_CACHE_STATUS_CACHE_INIT_FINISH_MASK         (0x1U << DCACHE_CACHE_STATUS_CACHE_INIT_FINISH_SHIFT)        /* 0x00000001 */
#define DCACHE_CACHE_STATUS_CACHE_M_BUSY_SHIFT             (1U)
#define DCACHE_CACHE_STATUS_CACHE_M_BUSY_MASK              (0x1U << DCACHE_CACHE_STATUS_CACHE_M_BUSY_SHIFT)             /* 0x00000002 */
#define DCACHE_CACHE_STATUS_CACHE_FLUSH_DONE_SHIFT         (2U)
#define DCACHE_CACHE_STATUS_CACHE_FLUSH_DONE_MASK          (0x1U << DCACHE_CACHE_STATUS_CACHE_FLUSH_DONE_SHIFT)         /* 0x00000004 */
/* PMU_RD_NUM_CNT */
#define DCACHE_PMU_RD_NUM_CNT_OFFSET                       (0x40U)
#define DCACHE_PMU_RD_NUM_CNT                              (0x0U)
#define DCACHE_PMU_RD_NUM_CNT_PMU_RD_NUM_CNT_SHIFT         (0U)
#define DCACHE_PMU_RD_NUM_CNT_PMU_RD_NUM_CNT_MASK          (0xFFFFFFFFU << DCACHE_PMU_RD_NUM_CNT_PMU_RD_NUM_CNT_SHIFT)  /* 0xFFFFFFFF */
/* PMU_WR_NUM_CNT */
#define DCACHE_PMU_WR_NUM_CNT_OFFSET                       (0x44U)
#define DCACHE_PMU_WR_NUM_CNT                              (0x0U)
#define DCACHE_PMU_WR_NUM_CNT_PMU_WR_NUM_CNT_SHIFT         (0U)
#define DCACHE_PMU_WR_NUM_CNT_PMU_WR_NUM_CNT_MASK          (0xFFFFFFFFU << DCACHE_PMU_WR_NUM_CNT_PMU_WR_NUM_CNT_SHIFT)  /* 0xFFFFFFFF */
/* PMU_SRAM_RD_HIT_CNT */
#define DCACHE_PMU_SRAM_RD_HIT_CNT_OFFSET                  (0x48U)
#define DCACHE_PMU_SRAM_RD_HIT_CNT                         (0x0U)
#define DCACHE_PMU_SRAM_RD_HIT_CNT_PMU_SRAM_RD_HIT_CNT_SHIFT (0U)
#define DCACHE_PMU_SRAM_RD_HIT_CNT_PMU_SRAM_RD_HIT_CNT_MASK (0xFFFFFFFFU << DCACHE_PMU_SRAM_RD_HIT_CNT_PMU_SRAM_RD_HIT_CNT_SHIFT) /* 0xFFFFFFFF */
/* PMU_HB_RD_HIT_CNT */
#define DCACHE_PMU_HB_RD_HIT_CNT_OFFSET                    (0x4CU)
#define DCACHE_PMU_HB_RD_HIT_CNT                           (0x0U)
#define DCACHE_PMU_HB_RD_HIT_CNT_PMU_HB_RD_HIT_CNT_SHIFT   (0U)
#define DCACHE_PMU_HB_RD_HIT_CNT_PMU_HB_RD_HIT_CNT_MASK    (0xFFFFFFFFU << DCACHE_PMU_HB_RD_HIT_CNT_PMU_HB_RD_HIT_CNT_SHIFT) /* 0xFFFFFFFF */
/* PMU_STB_RD_HIT_CNT */
#define DCACHE_PMU_STB_RD_HIT_CNT_OFFSET                   (0x50U)
#define DCACHE_PMU_STB_RD_HIT_CNT_PMU_STB_RD_HIT_CNT_SHIFT (0U)
#define DCACHE_PMU_STB_RD_HIT_CNT_PMU_STB_RD_HIT_CNT_MASK  (0xFFFFFFFFU << DCACHE_PMU_STB_RD_HIT_CNT_PMU_STB_RD_HIT_CNT_SHIFT) /* 0xFFFFFFFF */
/* PMU_RD_HIT_CNT */
#define DCACHE_PMU_RD_HIT_CNT_OFFSET                       (0x54U)
#define DCACHE_PMU_RD_HIT_CNT                              (0x0U)
#define DCACHE_PMU_RD_HIT_CNT_PMU_RD_HIT_CNT_SHIFT         (0U)
#define DCACHE_PMU_RD_HIT_CNT_PMU_RD_HIT_CNT_MASK          (0xFFFFFFFFU << DCACHE_PMU_RD_HIT_CNT_PMU_RD_HIT_CNT_SHIFT)  /* 0xFFFFFFFF */
/* PMU_WR_HIT_CNT */
#define DCACHE_PMU_WR_HIT_CNT_OFFSET                       (0x58U)
#define DCACHE_PMU_WR_HIT_CNT                              (0x0U)
#define DCACHE_PMU_WR_HIT_CNT_PMU_WR_HIT_CNT_SHIFT         (0U)
#define DCACHE_PMU_WR_HIT_CNT_PMU_WR_HIT_CNT_MASK          (0xFFFFFFFFU << DCACHE_PMU_WR_HIT_CNT_PMU_WR_HIT_CNT_SHIFT)  /* 0xFFFFFFFF */
/* PMU_RD_MISS_PENALTY_CNT */
#define DCACHE_PMU_RD_MISS_PENALTY_CNT_OFFSET              (0x5CU)
#define DCACHE_PMU_RD_MISS_PENALTY_CNT                     (0x0U)
#define DCACHE_PMU_RD_MISS_PENALTY_CNT_PMU_RD_MISS_PENALTY_CNT_SHIFT (0U)
#define DCACHE_PMU_RD_MISS_PENALTY_CNT_PMU_RD_MISS_PENALTY_CNT_MASK (0xFFFFFFFFU << DCACHE_PMU_RD_MISS_PENALTY_CNT_PMU_RD_MISS_PENALTY_CNT_SHIFT) /* 0xFFFFFFFF */
/* PMU_WR_MISS_PENALTY_CNT */
#define DCACHE_PMU_WR_MISS_PENALTY_CNT_OFFSET              (0x60U)
#define DCACHE_PMU_WR_MISS_PENALTY_CNT                     (0x0U)
#define DCACHE_PMU_WR_MISS_PENALTY_CNT_PMU_WR_MISS_PENALTY_CNT_SHIFT (0U)
#define DCACHE_PMU_WR_MISS_PENALTY_CNT_PMU_WR_MISS_PENALTY_CNT_MASK (0xFFFFFFFFU << DCACHE_PMU_WR_MISS_PENALTY_CNT_PMU_WR_MISS_PENALTY_CNT_SHIFT) /* 0xFFFFFFFF */
/* PMU_RD_LAT_CNT */
#define DCACHE_PMU_RD_LAT_CNT_OFFSET                       (0x64U)
#define DCACHE_PMU_RD_LAT_CNT                              (0x0U)
#define DCACHE_PMU_RD_LAT_CNT_PMU_RD_LAT_CNT_SHIFT         (0U)
#define DCACHE_PMU_RD_LAT_CNT_PMU_RD_LAT_CNT_MASK          (0xFFFFFFFFU << DCACHE_PMU_RD_LAT_CNT_PMU_RD_LAT_CNT_SHIFT)  /* 0xFFFFFFFF */
/* PMU_WR_LAT_CNT */
#define DCACHE_PMU_WR_LAT_CNT_OFFSET                       (0x68U)
#define DCACHE_PMU_WR_LAT_CNT                              (0x0U)
#define DCACHE_PMU_WR_LAT_CNT_PMU_RD_LAT_CNT_SHIFT         (0U)
#define DCACHE_PMU_WR_LAT_CNT_PMU_RD_LAT_CNT_MASK          (0xFFFFFFFFU << DCACHE_PMU_WR_LAT_CNT_PMU_RD_LAT_CNT_SHIFT)  /* 0xFFFFFFFF */
/* REVISION */
#define DCACHE_REVISION_OFFSET                             (0xF0U)
#define DCACHE_REVISION_REVISION_SHIFT                     (0U)
#define DCACHE_REVISION_REVISION_MASK                      (0xFFFFFFFFU << DCACHE_REVISION_REVISION_SHIFT)              /* 0xFFFFFFFF */
/******************************************CRU*******************************************/
/* GPLL_CON0 */
#define CRU_GPLL_CON0_OFFSET                               (0x0)
#define CRU_GPLL_CON0_FBDIV_SHIFT                          (0U)
#define CRU_GPLL_CON0_FBDIV_MASK                           (0xFFFU << CRU_GPLL_CON0_FBDIV_SHIFT)                        /* 0x00000FFF */
#define CRU_GPLL_CON0_POSTDIV1_SHIFT                       (12U)
#define CRU_GPLL_CON0_POSTDIV1_MASK                        (0x7U << CRU_GPLL_CON0_POSTDIV1_SHIFT)                       /* 0x00007000 */
#define CRU_GPLL_CON0_BYPASS_SHIFT                         (15U)
#define CRU_GPLL_CON0_BYPASS_MASK                          (0x1U << CRU_GPLL_CON0_BYPASS_SHIFT)                         /* 0x00008000 */
/* GPLL_CON1 */
#define CRU_GPLL_CON1_OFFSET                               (0x4)
#define CRU_GPLL_CON1_REFDIV_SHIFT                         (0U)
#define CRU_GPLL_CON1_REFDIV_MASK                          (0x3FU << CRU_GPLL_CON1_REFDIV_SHIFT)                        /* 0x0000003F */
#define CRU_GPLL_CON1_POSTDIV2_SHIFT                       (6U)
#define CRU_GPLL_CON1_POSTDIV2_MASK                        (0x7U << CRU_GPLL_CON1_POSTDIV2_SHIFT)                       /* 0x000001C0 */
#define CRU_GPLL_CON1_PLL_LOCK_SHIFT                       (10U)
#define CRU_GPLL_CON1_PLL_LOCK_MASK                        (0x1U << CRU_GPLL_CON1_PLL_LOCK_SHIFT)                       /* 0x00000400 */
#define CRU_GPLL_CON1_DSMPD_SHIFT                          (12U)
#define CRU_GPLL_CON1_DSMPD_MASK                           (0x1U << CRU_GPLL_CON1_DSMPD_SHIFT)                          /* 0x00001000 */
#define CRU_GPLL_CON1_PLLPD0_SHIFT                         (13U)
#define CRU_GPLL_CON1_PLLPD0_MASK                          (0x1U << CRU_GPLL_CON1_PLLPD0_SHIFT)                         /* 0x00002000 */
#define CRU_GPLL_CON1_PLLPD1_SHIFT                         (14U)
#define CRU_GPLL_CON1_PLLPD1_MASK                          (0x1U << CRU_GPLL_CON1_PLLPD1_SHIFT)                         /* 0x00004000 */
#define CRU_GPLL_CON1_PLLPDSEL_SHIFT                       (15U)
#define CRU_GPLL_CON1_PLLPDSEL_MASK                        (0x1U << CRU_GPLL_CON1_PLLPDSEL_SHIFT)                       /* 0x00008000 */
/* GPLL_CON2 */
#define CRU_GPLL_CON2_OFFSET                               (0x8)
#define CRU_GPLL_CON2_FRACDIV_SHIFT                        (0U)
#define CRU_GPLL_CON2_FRACDIV_MASK                         (0xFFFFFFU << CRU_GPLL_CON2_FRACDIV_SHIFT)                   /* 0x00FFFFFF */
#define CRU_GPLL_CON2_DACPD_SHIFT                          (24U)
#define CRU_GPLL_CON2_DACPD_MASK                           (0x1U << CRU_GPLL_CON2_DACPD_SHIFT)                          /* 0x01000000 */
#define CRU_GPLL_CON2_FOUTPOSTDIVPD_SHIFT                  (25U)
#define CRU_GPLL_CON2_FOUTPOSTDIVPD_MASK                   (0x1U << CRU_GPLL_CON2_FOUTPOSTDIVPD_SHIFT)                  /* 0x02000000 */
#define CRU_GPLL_CON2_FOUTVCOPD_SHIFT                      (26U)
#define CRU_GPLL_CON2_FOUTVCOPD_MASK                       (0x1U << CRU_GPLL_CON2_FOUTVCOPD_SHIFT)                      /* 0x04000000 */
#define CRU_GPLL_CON2_FOUT4PHASEPD_SHIFT                   (27U)
#define CRU_GPLL_CON2_FOUT4PHASEPD_MASK                    (0x1U << CRU_GPLL_CON2_FOUT4PHASEPD_SHIFT)                   /* 0x08000000 */
/* GPLL_CON3 */
#define CRU_GPLL_CON3_OFFSET                               (0xC)
#define CRU_GPLL_CON3_SSMOD_BP_SHIFT                       (0U)
#define CRU_GPLL_CON3_SSMOD_BP_MASK                        (0x1U << CRU_GPLL_CON3_SSMOD_BP_SHIFT)                       /* 0x00000001 */
#define CRU_GPLL_CON3_SSMOD_DISABLE_SSCG_SHIFT             (1U)
#define CRU_GPLL_CON3_SSMOD_DISABLE_SSCG_MASK              (0x1U << CRU_GPLL_CON3_SSMOD_DISABLE_SSCG_SHIFT)             /* 0x00000002 */
#define CRU_GPLL_CON3_SSMOD_RESET_SHIFT                    (2U)
#define CRU_GPLL_CON3_SSMOD_RESET_MASK                     (0x1U << CRU_GPLL_CON3_SSMOD_RESET_SHIFT)                    /* 0x00000004 */
#define CRU_GPLL_CON3_SSMOD_DOWNSPREAD_SHIFT               (3U)
#define CRU_GPLL_CON3_SSMOD_DOWNSPREAD_MASK                (0x1U << CRU_GPLL_CON3_SSMOD_DOWNSPREAD_SHIFT)               /* 0x00000008 */
#define CRU_GPLL_CON3_SSMOD_DIVVAL_SHIFT                   (4U)
#define CRU_GPLL_CON3_SSMOD_DIVVAL_MASK                    (0xFU << CRU_GPLL_CON3_SSMOD_DIVVAL_SHIFT)                   /* 0x000000F0 */
#define CRU_GPLL_CON3_SSMOD_SPREAD_SHIFT                   (8U)
#define CRU_GPLL_CON3_SSMOD_SPREAD_MASK                    (0x1FU << CRU_GPLL_CON3_SSMOD_SPREAD_SHIFT)                  /* 0x00001F00 */
/* GPLL_CON4 */
#define CRU_GPLL_CON4_OFFSET                               (0x10)
#define CRU_GPLL_CON4_SSMOD_SEL_EXT_WAVE_SHIFT             (0U)
#define CRU_GPLL_CON4_SSMOD_SEL_EXT_WAVE_MASK              (0x1U << CRU_GPLL_CON4_SSMOD_SEL_EXT_WAVE_SHIFT)             /* 0x00000001 */
#define CRU_GPLL_CON4_SSMOD_EXT_MAXADDR_SHIFT              (8U)
#define CRU_GPLL_CON4_SSMOD_EXT_MAXADDR_MASK               (0xFFU << CRU_GPLL_CON4_SSMOD_EXT_MAXADDR_SHIFT)             /* 0x0000FF00 */
/* CPLL_CON0 */
#define CRU_CPLL_CON0_OFFSET                               (0x20)
#define CRU_CPLL_CON0_FBDIV_SHIFT                          (0U)
#define CRU_CPLL_CON0_FBDIV_MASK                           (0xFFFU << CRU_CPLL_CON0_FBDIV_SHIFT)                        /* 0x00000FFF */
#define CRU_CPLL_CON0_POSTDIV1_SHIFT                       (12U)
#define CRU_CPLL_CON0_POSTDIV1_MASK                        (0x7U << CRU_CPLL_CON0_POSTDIV1_SHIFT)                       /* 0x00007000 */
#define CRU_CPLL_CON0_BYPASS_SHIFT                         (15U)
#define CRU_CPLL_CON0_BYPASS_MASK                          (0x1U << CRU_CPLL_CON0_BYPASS_SHIFT)                         /* 0x00008000 */
/* CPLL_CON1 */
#define CRU_CPLL_CON1_OFFSET                               (0x24)
#define CRU_CPLL_CON1_REFDIV_SHIFT                         (0U)
#define CRU_CPLL_CON1_REFDIV_MASK                          (0x3FU << CRU_CPLL_CON1_REFDIV_SHIFT)                        /* 0x0000003F */
#define CRU_CPLL_CON1_POSTDIV2_SHIFT                       (6U)
#define CRU_CPLL_CON1_POSTDIV2_MASK                        (0x7U << CRU_CPLL_CON1_POSTDIV2_SHIFT)                       /* 0x000001C0 */
#define CRU_CPLL_CON1_PLL_LOCK_SHIFT                       (10U)
#define CRU_CPLL_CON1_PLL_LOCK_MASK                        (0x1U << CRU_CPLL_CON1_PLL_LOCK_SHIFT)                       /* 0x00000400 */
#define CRU_CPLL_CON1_DSMPD_SHIFT                          (12U)
#define CRU_CPLL_CON1_DSMPD_MASK                           (0x1U << CRU_CPLL_CON1_DSMPD_SHIFT)                          /* 0x00001000 */
#define CRU_CPLL_CON1_PLLPD0_SHIFT                         (13U)
#define CRU_CPLL_CON1_PLLPD0_MASK                          (0x1U << CRU_CPLL_CON1_PLLPD0_SHIFT)                         /* 0x00002000 */
#define CRU_CPLL_CON1_PLLPD1_SHIFT                         (14U)
#define CRU_CPLL_CON1_PLLPD1_MASK                          (0x1U << CRU_CPLL_CON1_PLLPD1_SHIFT)                         /* 0x00004000 */
#define CRU_CPLL_CON1_PLLPDSEL_SHIFT                       (15U)
#define CRU_CPLL_CON1_PLLPDSEL_MASK                        (0x1U << CRU_CPLL_CON1_PLLPDSEL_SHIFT)                       /* 0x00008000 */
/* CPLL_CON2 */
#define CRU_CPLL_CON2_OFFSET                               (0x28)
#define CRU_CPLL_CON2_FRACDIV_SHIFT                        (0U)
#define CRU_CPLL_CON2_FRACDIV_MASK                         (0xFFFFFFU << CRU_CPLL_CON2_FRACDIV_SHIFT)                   /* 0x00FFFFFF */
#define CRU_CPLL_CON2_DACPD_SHIFT                          (24U)
#define CRU_CPLL_CON2_DACPD_MASK                           (0x1U << CRU_CPLL_CON2_DACPD_SHIFT)                          /* 0x01000000 */
#define CRU_CPLL_CON2_FOUTPOSTDIVPD_SHIFT                  (25U)
#define CRU_CPLL_CON2_FOUTPOSTDIVPD_MASK                   (0x1U << CRU_CPLL_CON2_FOUTPOSTDIVPD_SHIFT)                  /* 0x02000000 */
#define CRU_CPLL_CON2_FOUTVCOPD_SHIFT                      (26U)
#define CRU_CPLL_CON2_FOUTVCOPD_MASK                       (0x1U << CRU_CPLL_CON2_FOUTVCOPD_SHIFT)                      /* 0x04000000 */
#define CRU_CPLL_CON2_FOUT4PHASEPD_SHIFT                   (27U)
#define CRU_CPLL_CON2_FOUT4PHASEPD_MASK                    (0x1U << CRU_CPLL_CON2_FOUT4PHASEPD_SHIFT)                   /* 0x08000000 */
/* SPLL_CON0 */
#define CRU_SPLL_CON0_OFFSET                               (0x40)
#define CRU_SPLL_CON0_CLKOD_SHIFT                          (0U)
#define CRU_SPLL_CON0_CLKOD_MASK                           (0xFU << CRU_SPLL_CON0_CLKOD_SHIFT)                          /* 0x0000000F */
#define CRU_SPLL_CON0_CLKR_SHIFT                           (8U)
#define CRU_SPLL_CON0_CLKR_MASK                            (0x3FU << CRU_SPLL_CON0_CLKR_SHIFT)                          /* 0x00003F00 */
#define CRU_SPLL_CON0_CLKOD_MASK_SHIFT                     (16U)
#define CRU_SPLL_CON0_CLKOD_MASK_MASK                      (0xFU << CRU_SPLL_CON0_CLKOD_MASK_SHIFT)                     /* 0x000F0000 */
#define CRU_SPLL_CON0_CLKR_MASK_SHIFT                      (24U)
#define CRU_SPLL_CON0_CLKR_MASK_MASK                       (0x3FU << CRU_SPLL_CON0_CLKR_MASK_SHIFT)                     /* 0x3F000000 */
/* SPLL_CON1 */
#define CRU_SPLL_CON1_OFFSET                               (0x44)
#define CRU_SPLL_CON1_CLKF_SHIFT                           (0U)
#define CRU_SPLL_CON1_CLKF_MASK                            (0x1FFFU << CRU_SPLL_CON1_CLKF_SHIFT)                        /* 0x00001FFF */
#define CRU_SPLL_CON1_CLKF_MASK_SHIFT                      (16U)
#define CRU_SPLL_CON1_CLKF_MASK_MASK                       (0x1FFFU << CRU_SPLL_CON1_CLKF_MASK_SHIFT)                   /* 0x1FFF0000 */
/* SPLL_CON2 */
#define CRU_SPLL_CON2_OFFSET                               (0x48)
#define CRU_SPLL_CON2_BWADJ_SHIFT                          (0U)
#define CRU_SPLL_CON2_BWADJ_MASK                           (0xFFFU << CRU_SPLL_CON2_BWADJ_SHIFT)                        /* 0x00000FFF */
#define CRU_SPLL_CON2_BWADJ_MASK_SHIFT                     (16U)
#define CRU_SPLL_CON2_BWADJ_MASK_MASK                      (0xFFFU << CRU_SPLL_CON2_BWADJ_MASK_SHIFT)                   /* 0x0FFF0000 */
/* SPLL_CON3 */
#define CRU_SPLL_CON3_OFFSET                               (0x4C)
#define CRU_SPLL_CON3_BYPASS_SHIFT                         (0U)
#define CRU_SPLL_CON3_BYPASS_MASK                          (0x1U << CRU_SPLL_CON3_BYPASS_SHIFT)                         /* 0x00000001 */
#define CRU_SPLL_CON3_POWER_DOWN_SHIFT                     (1U)
#define CRU_SPLL_CON3_POWER_DOWN_MASK                      (0x1U << CRU_SPLL_CON3_POWER_DOWN_SHIFT)                     /* 0x00000002 */
#define CRU_SPLL_CON3_FASTEN_SHIFT                         (2U)
#define CRU_SPLL_CON3_FASTEN_MASK                          (0x1U << CRU_SPLL_CON3_FASTEN_SHIFT)                         /* 0x00000004 */
#define CRU_SPLL_CON3_ENSAT_SHIFT                          (3U)
#define CRU_SPLL_CON3_ENSAT_MASK                           (0x1U << CRU_SPLL_CON3_ENSAT_SHIFT)                          /* 0x00000008 */
#define CRU_SPLL_CON3_TEST_SHIFT                           (4U)
#define CRU_SPLL_CON3_TEST_MASK                            (0x1U << CRU_SPLL_CON3_TEST_SHIFT)                           /* 0x00000010 */
#define CRU_SPLL_CON3_RESET_SHIFT                          (5U)
#define CRU_SPLL_CON3_RESET_MASK                           (0x1U << CRU_SPLL_CON3_RESET_SHIFT)                          /* 0x00000020 */
#define CRU_SPLL_CON3_LOCK_OUT_DISALBE_SHIFT               (6U)
#define CRU_SPLL_CON3_LOCK_OUT_DISALBE_MASK                (0x1U << CRU_SPLL_CON3_LOCK_OUT_DISALBE_SHIFT)               /* 0x00000040 */
#define CRU_SPLL_CON3_BYPASS_MASK_SHIFT                    (16U)
#define CRU_SPLL_CON3_BYPASS_MASK_MASK                     (0x1U << CRU_SPLL_CON3_BYPASS_MASK_SHIFT)                    /* 0x00010000 */
#define CRU_SPLL_CON3_POWER_DOWN_MASK_SHIFT                (17U)
#define CRU_SPLL_CON3_POWER_DOWN_MASK_MASK                 (0x1U << CRU_SPLL_CON3_POWER_DOWN_MASK_SHIFT)                /* 0x00020000 */
#define CRU_SPLL_CON3_FASTEN_MASK_SHIFT                    (18U)
#define CRU_SPLL_CON3_FASTEN_MASK_MASK                     (0x1U << CRU_SPLL_CON3_FASTEN_MASK_SHIFT)                    /* 0x00040000 */
#define CRU_SPLL_CON3_ENSAT_MASK_SHIFT                     (19U)
#define CRU_SPLL_CON3_ENSAT_MASK_MASK                      (0x1U << CRU_SPLL_CON3_ENSAT_MASK_SHIFT)                     /* 0x00080000 */
#define CRU_SPLL_CON3_TEST_MASK_SHIFT                      (20U)
#define CRU_SPLL_CON3_TEST_MASK_MASK                       (0x1U << CRU_SPLL_CON3_TEST_MASK_SHIFT)                      /* 0x00100000 */
#define CRU_SPLL_CON3_RESET_MASK_SHIFT                     (21U)
#define CRU_SPLL_CON3_RESET_MASK_MASK                      (0x1U << CRU_SPLL_CON3_RESET_MASK_SHIFT)                     /* 0x00200000 */
#define CRU_SPLL_CON3_LOCK_OUT_DISABLE_MASK_SHIFT          (22U)
#define CRU_SPLL_CON3_LOCK_OUT_DISABLE_MASK_MASK           (0x1U << CRU_SPLL_CON3_LOCK_OUT_DISABLE_MASK_SHIFT)          /* 0x00400000 */
/* CRU_MODE_CON00 */
#define CRU_CRU_MODE_CON00_OFFSET                          (0x60)
#define CRU_CRU_MODE_CON00_CLK_GPLL_MODE_SHIFT             (0U)
#define CRU_CRU_MODE_CON00_CLK_GPLL_MODE_MASK              (0x3U << CRU_CRU_MODE_CON00_CLK_GPLL_MODE_SHIFT)             /* 0x00000003 */
#define CRU_CRU_MODE_CON00_CLK_CPLL_MODE_SHIFT             (2U)
#define CRU_CRU_MODE_CON00_CLK_CPLL_MODE_MASK              (0x3U << CRU_CRU_MODE_CON00_CLK_CPLL_MODE_SHIFT)             /* 0x0000000C */
/* CRU_CLKSEL_CON00 */
#define CRU_CRU_CLKSEL_CON00_OFFSET                        (0x80)
#define CRU_CRU_CLKSEL_CON00_ACLK_DSP_S_DIV_SHIFT          (0U)
#define CRU_CRU_CLKSEL_CON00_ACLK_DSP_S_DIV_MASK           (0x3FU << CRU_CRU_CLKSEL_CON00_ACLK_DSP_S_DIV_SHIFT)         /* 0x0000003F */
#define CRU_CRU_CLKSEL_CON00_ACLK_DSP_S_SEL_SHIFT          (6U)
#define CRU_CRU_CLKSEL_CON00_ACLK_DSP_S_SEL_MASK           (0x3U << CRU_CRU_CLKSEL_CON00_ACLK_DSP_S_SEL_SHIFT)          /* 0x000000C0 */
#define CRU_CRU_CLKSEL_CON00_PCLK_DSP_DIV_SHIFT            (8U)
#define CRU_CRU_CLKSEL_CON00_PCLK_DSP_DIV_MASK             (0x3FU << CRU_CRU_CLKSEL_CON00_PCLK_DSP_DIV_SHIFT)           /* 0x00003F00 */
/* CRU_CLKSEL_CON02 */
#define CRU_CRU_CLKSEL_CON02_OFFSET                        (0x88)
#define CRU_CRU_CLKSEL_CON02_SCLK_SHRM_DIV_SHIFT           (0U)
#define CRU_CRU_CLKSEL_CON02_SCLK_SHRM_DIV_MASK            (0xFU << CRU_CRU_CLKSEL_CON02_SCLK_SHRM_DIV_SHIFT)           /* 0x0000000F */
#define CRU_CRU_CLKSEL_CON02_SCLK_SHRM_SEL_SHIFT           (4U)
#define CRU_CRU_CLKSEL_CON02_SCLK_SHRM_SEL_MASK            (0x1U << CRU_CRU_CLKSEL_CON02_SCLK_SHRM_SEL_SHIFT)           /* 0x00000010 */
#define CRU_CRU_CLKSEL_CON02_PCLK_SHRM_DIV_SHIFT           (8U)
#define CRU_CRU_CLKSEL_CON02_PCLK_SHRM_DIV_MASK            (0x1FU << CRU_CRU_CLKSEL_CON02_PCLK_SHRM_DIV_SHIFT)          /* 0x00001F00 */
/* CRU_CLKSEL_CON03 */
#define CRU_CRU_CLKSEL_CON03_OFFSET                        (0x8C)
#define CRU_CRU_CLKSEL_CON03_CLK_UART0_SRC_DIV_SHIFT       (0U)
#define CRU_CRU_CLKSEL_CON03_CLK_UART0_SRC_DIV_MASK        (0x1FU << CRU_CRU_CLKSEL_CON03_CLK_UART0_SRC_DIV_SHIFT)      /* 0x0000001F */
#define CRU_CRU_CLKSEL_CON03_CLK_UART0_SRC_SEL_SHIFT       (5U)
#define CRU_CRU_CLKSEL_CON03_CLK_UART0_SRC_SEL_MASK        (0x1U << CRU_CRU_CLKSEL_CON03_CLK_UART0_SRC_SEL_SHIFT)       /* 0x00000020 */
#define CRU_CRU_CLKSEL_CON03_SCLK_UART0_SEL_SHIFT          (6U)
#define CRU_CRU_CLKSEL_CON03_SCLK_UART0_SEL_MASK           (0x3U << CRU_CRU_CLKSEL_CON03_SCLK_UART0_SEL_SHIFT)          /* 0x000000C0 */
/* CRU_CLKSEL_CON04 */
#define CRU_CRU_CLKSEL_CON04_OFFSET                        (0x90)
#define CRU_CRU_CLKSEL_CON04_CLK_UART0_FRAC_DIV_SHIFT      (0U)
#define CRU_CRU_CLKSEL_CON04_CLK_UART0_FRAC_DIV_MASK       (0xFFFFFFFFU << CRU_CRU_CLKSEL_CON04_CLK_UART0_FRAC_DIV_SHIFT) /* 0xFFFFFFFF */
/* CRU_CLKSEL_CON05 */
#define CRU_CRU_CLKSEL_CON05_OFFSET                        (0x94)
#define CRU_CRU_CLKSEL_CON05_CLK_UART1_SRC_DIV_SHIFT       (0U)
#define CRU_CRU_CLKSEL_CON05_CLK_UART1_SRC_DIV_MASK        (0x1FU << CRU_CRU_CLKSEL_CON05_CLK_UART1_SRC_DIV_SHIFT)      /* 0x0000001F */
#define CRU_CRU_CLKSEL_CON05_CLK_UART1_SRC_SEL_SHIFT       (5U)
#define CRU_CRU_CLKSEL_CON05_CLK_UART1_SRC_SEL_MASK        (0x1U << CRU_CRU_CLKSEL_CON05_CLK_UART1_SRC_SEL_SHIFT)       /* 0x00000020 */
#define CRU_CRU_CLKSEL_CON05_SCLK_UART1_SEL_SHIFT          (6U)
#define CRU_CRU_CLKSEL_CON05_SCLK_UART1_SEL_MASK           (0x3U << CRU_CRU_CLKSEL_CON05_SCLK_UART1_SEL_SHIFT)          /* 0x000000C0 */
/* CRU_CLKSEL_CON06 */
#define CRU_CRU_CLKSEL_CON06_OFFSET                        (0x98)
#define CRU_CRU_CLKSEL_CON06_CLK_UART1_FRAC_DIV_SHIFT      (0U)
#define CRU_CRU_CLKSEL_CON06_CLK_UART1_FRAC_DIV_MASK       (0xFFFFFFFFU << CRU_CRU_CLKSEL_CON06_CLK_UART1_FRAC_DIV_SHIFT) /* 0xFFFFFFFF */
/* CRU_CLKSEL_CON07 */
#define CRU_CRU_CLKSEL_CON07_OFFSET                        (0x9C)
#define CRU_CRU_CLKSEL_CON07_CLK_UART2_SRC_DIV_SHIFT       (0U)
#define CRU_CRU_CLKSEL_CON07_CLK_UART2_SRC_DIV_MASK        (0x1FU << CRU_CRU_CLKSEL_CON07_CLK_UART2_SRC_DIV_SHIFT)      /* 0x0000001F */
#define CRU_CRU_CLKSEL_CON07_CLK_UART2_SRC_SEL_SHIFT       (5U)
#define CRU_CRU_CLKSEL_CON07_CLK_UART2_SRC_SEL_MASK        (0x1U << CRU_CRU_CLKSEL_CON07_CLK_UART2_SRC_SEL_SHIFT)       /* 0x00000020 */
#define CRU_CRU_CLKSEL_CON07_SCLK_UART2_SEL_SHIFT          (6U)
#define CRU_CRU_CLKSEL_CON07_SCLK_UART2_SEL_MASK           (0x3U << CRU_CRU_CLKSEL_CON07_SCLK_UART2_SEL_SHIFT)          /* 0x000000C0 */
/* CRU_CLKSEL_CON08 */
#define CRU_CRU_CLKSEL_CON08_OFFSET                        (0xA0)
#define CRU_CRU_CLKSEL_CON08_CLK_UART2_FRAC_DIV_SHIFT      (0U)
#define CRU_CRU_CLKSEL_CON08_CLK_UART2_FRAC_DIV_MASK       (0xFFFFFFFFU << CRU_CRU_CLKSEL_CON08_CLK_UART2_FRAC_DIV_SHIFT) /* 0xFFFFFFFF */
/* CRU_CLKSEL_CON13 */
#define CRU_CRU_CLKSEL_CON13_OFFSET                        (0xB4)
#define CRU_CRU_CLKSEL_CON13_CLK_I2C0_DIV_SHIFT            (0U)
#define CRU_CRU_CLKSEL_CON13_CLK_I2C0_DIV_MASK             (0xFU << CRU_CRU_CLKSEL_CON13_CLK_I2C0_DIV_SHIFT)            /* 0x0000000F */
#define CRU_CRU_CLKSEL_CON13_CLK_I2C1_DIV_SHIFT            (4U)
#define CRU_CRU_CLKSEL_CON13_CLK_I2C1_DIV_MASK             (0xFU << CRU_CRU_CLKSEL_CON13_CLK_I2C1_DIV_SHIFT)            /* 0x000000F0 */
#define CRU_CRU_CLKSEL_CON13_CLK_I2C2_DIV_SHIFT            (8U)
#define CRU_CRU_CLKSEL_CON13_CLK_I2C2_DIV_MASK             (0xFU << CRU_CRU_CLKSEL_CON13_CLK_I2C2_DIV_SHIFT)            /* 0x00000F00 */
/* CRU_CLKSEL_CON14 */
#define CRU_CRU_CLKSEL_CON14_OFFSET                        (0xB8)
#define CRU_CRU_CLKSEL_CON14_MCLK_PDM0_DIV_SHIFT           (0U)
#define CRU_CRU_CLKSEL_CON14_MCLK_PDM0_DIV_MASK            (0x1FU << CRU_CRU_CLKSEL_CON14_MCLK_PDM0_DIV_SHIFT)          /* 0x0000001F */
#define CRU_CRU_CLKSEL_CON14_MCLK_PDM0_SEL_SHIFT           (7U)
#define CRU_CRU_CLKSEL_CON14_MCLK_PDM0_SEL_MASK            (0x1U << CRU_CRU_CLKSEL_CON14_MCLK_PDM0_SEL_SHIFT)           /* 0x00000080 */
#define CRU_CRU_CLKSEL_CON14_HCLK_AUDIO_DIV_SHIFT          (8U)
#define CRU_CRU_CLKSEL_CON14_HCLK_AUDIO_DIV_MASK           (0x1FU << CRU_CRU_CLKSEL_CON14_HCLK_AUDIO_DIV_SHIFT)         /* 0x00001F00 */
#define CRU_CRU_CLKSEL_CON14_HCLK_AUDIO_SEL_SHIFT          (15U)
#define CRU_CRU_CLKSEL_CON14_HCLK_AUDIO_SEL_MASK           (0x1U << CRU_CRU_CLKSEL_CON14_HCLK_AUDIO_SEL_SHIFT)          /* 0x00008000 */
/* CRU_CLKSEL_CON15 */
#define CRU_CRU_CLKSEL_CON15_OFFSET                        (0xBC)
#define CRU_CRU_CLKSEL_CON15_MCLK_PDM0_OUT_DIV_SHIFT       (0U)
#define CRU_CRU_CLKSEL_CON15_MCLK_PDM0_OUT_DIV_MASK        (0xFFFFFFFFU << CRU_CRU_CLKSEL_CON15_MCLK_PDM0_OUT_DIV_SHIFT) /* 0xFFFFFFFF */
/* CRU_CLKSEL_CON16 */
#define CRU_CRU_CLKSEL_CON16_OFFSET                        (0xC0)
#define CRU_CRU_CLKSEL_CON16_CLK_I2S8CH_SRC_DIV_SHIFT      (0U)
#define CRU_CRU_CLKSEL_CON16_CLK_I2S8CH_SRC_DIV_MASK       (0x1FU << CRU_CRU_CLKSEL_CON16_CLK_I2S8CH_SRC_DIV_SHIFT)     /* 0x0000001F */
#define CRU_CRU_CLKSEL_CON16_CLK_I2S8CH_SRC_SEL_SHIFT      (5U)
#define CRU_CRU_CLKSEL_CON16_CLK_I2S8CH_SRC_SEL_MASK       (0x1U << CRU_CRU_CLKSEL_CON16_CLK_I2S8CH_SRC_SEL_SHIFT)      /* 0x00000020 */
#define CRU_CRU_CLKSEL_CON16_MCLK_I2S8CH_SEL_SHIFT         (6U)
#define CRU_CRU_CLKSEL_CON16_MCLK_I2S8CH_SEL_MASK          (0x3U << CRU_CRU_CLKSEL_CON16_MCLK_I2S8CH_SEL_SHIFT)         /* 0x000000C0 */
#define CRU_CRU_CLKSEL_CON16_PCLK_AUDIO_DIV_SHIFT          (8U)
#define CRU_CRU_CLKSEL_CON16_PCLK_AUDIO_DIV_MASK           (0x1FU << CRU_CRU_CLKSEL_CON16_PCLK_AUDIO_DIV_SHIFT)         /* 0x00001F00 */
#define CRU_CRU_CLKSEL_CON16_PCLK_AUDIO_SEL_SHIFT          (14U)
#define CRU_CRU_CLKSEL_CON16_PCLK_AUDIO_SEL_MASK           (0x1U << CRU_CRU_CLKSEL_CON16_PCLK_AUDIO_SEL_SHIFT)          /* 0x00004000 */
#define CRU_CRU_CLKSEL_CON16_I2S_MCLKOUT_SEL_SHIFT         (15U)
#define CRU_CRU_CLKSEL_CON16_I2S_MCLKOUT_SEL_MASK          (0x1U << CRU_CRU_CLKSEL_CON16_I2S_MCLKOUT_SEL_SHIFT)         /* 0x00008000 */
/* CRU_CLKSEL_CON17 */
#define CRU_CRU_CLKSEL_CON17_OFFSET                        (0xC4)
#define CRU_CRU_CLKSEL_CON17_CLK_I2S8CH_FRAC_DIV_SHIFT     (0U)
#define CRU_CRU_CLKSEL_CON17_CLK_I2S8CH_FRAC_DIV_MASK      (0xFFFFFFFFU << CRU_CRU_CLKSEL_CON17_CLK_I2S8CH_FRAC_DIV_SHIFT) /* 0xFFFFFFFF */
/* CRU_CLKSEL_CON18 */
#define CRU_CRU_CLKSEL_CON18_OFFSET                        (0xC8)
#define CRU_CRU_CLKSEL_CON18_ACLK_DMAC_DIV_SHIFT           (0U)
#define CRU_CRU_CLKSEL_CON18_ACLK_DMAC_DIV_MASK            (0x1FU << CRU_CRU_CLKSEL_CON18_ACLK_DMAC_DIV_SHIFT)          /* 0x0000001F */
#define CRU_CRU_CLKSEL_CON18_ACLK_DMAC_SEL_SHIFT           (7U)
#define CRU_CRU_CLKSEL_CON18_ACLK_DMAC_SEL_MASK            (0x1U << CRU_CRU_CLKSEL_CON18_ACLK_DMAC_SEL_SHIFT)           /* 0x00000080 */
/* CRU_CLKSEL_CON19 */
#define CRU_CRU_CLKSEL_CON19_OFFSET                        (0xCC)
#define CRU_CRU_CLKSEL_CON19_ACLK_VOP_DIV_SHIFT            (0U)
#define CRU_CRU_CLKSEL_CON19_ACLK_VOP_DIV_MASK             (0x1FU << CRU_CRU_CLKSEL_CON19_ACLK_VOP_DIV_SHIFT)           /* 0x0000001F */
#define CRU_CRU_CLKSEL_CON19_ACLK_VOP_SEL_SHIFT            (7U)
#define CRU_CRU_CLKSEL_CON19_ACLK_VOP_SEL_MASK             (0x1U << CRU_CRU_CLKSEL_CON19_ACLK_VOP_SEL_SHIFT)            /* 0x00000080 */
/* CRU_CLKSEL_CON20 */
#define CRU_CRU_CLKSEL_CON20_OFFSET                        (0xD0)
#define CRU_CRU_CLKSEL_CON20_DCLK_VOP_S_DIV_SHIFT          (0U)
#define CRU_CRU_CLKSEL_CON20_DCLK_VOP_S_DIV_MASK           (0x1FU << CRU_CRU_CLKSEL_CON20_DCLK_VOP_S_DIV_SHIFT)         /* 0x0000001F */
#define CRU_CRU_CLKSEL_CON20_DCLK_VOP_S_SEL_SHIFT          (7U)
#define CRU_CRU_CLKSEL_CON20_DCLK_VOP_S_SEL_MASK           (0x1U << CRU_CRU_CLKSEL_CON20_DCLK_VOP_S_SEL_SHIFT)          /* 0x00000080 */
/* CRU_CLKSEL_CON22 */
#define CRU_CRU_CLKSEL_CON22_OFFSET                        (0xD8)
#define CRU_CRU_CLKSEL_CON22_OCC_SCAN_CLK_DPHYLANBYTE_SEL_SHIFT (6U)
#define CRU_CRU_CLKSEL_CON22_OCC_SCAN_CLK_DPHYLANBYTE_SEL_MASK (0x3U << CRU_CRU_CLKSEL_CON22_OCC_SCAN_CLK_DPHYLANBYTE_SEL_SHIFT) /* 0x000000C0 */
/* CRU_CLKSEL_CON23 */
#define CRU_CRU_CLKSEL_CON23_OFFSET                        (0xDC)
#define CRU_CRU_CLKSEL_CON23_OCC_SCAN_CLK_DPHYLANBYTE_DIV_SHIFT (0U)
#define CRU_CRU_CLKSEL_CON23_OCC_SCAN_CLK_DPHYLANBYTE_DIV_MASK (0xFFU << CRU_CRU_CLKSEL_CON23_OCC_SCAN_CLK_DPHYLANBYTE_DIV_SHIFT) /* 0x000000FF */
/* CRU_CLKSEL_CON24 */
#define CRU_CRU_CLKSEL_CON24_OFFSET                        (0xE0)
#define CRU_CRU_CLKSEL_CON24_CLK_GPIO_DB0_DIV_SHIFT        (0U)
#define CRU_CRU_CLKSEL_CON24_CLK_GPIO_DB0_DIV_MASK         (0x3FFU << CRU_CRU_CLKSEL_CON24_CLK_GPIO_DB0_DIV_SHIFT)      /* 0x000003FF */
/* CRU_CLKSEL_CON25 */
#define CRU_CRU_CLKSEL_CON25_OFFSET                        (0xE4)
#define CRU_CRU_CLKSEL_CON25_CLK_GPIO_DB1_DIV_SHIFT        (0U)
#define CRU_CRU_CLKSEL_CON25_CLK_GPIO_DB1_DIV_MASK         (0x3FFU << CRU_CRU_CLKSEL_CON25_CLK_GPIO_DB1_DIV_SHIFT)      /* 0x000003FF */
/* CRU_CLKSEL_CON27 */
#define CRU_CRU_CLKSEL_CON27_OFFSET                        (0xEC)
#define CRU_CRU_CLKSEL_CON27_PCLK_ALIVE_DIV_SHIFT          (0U)
#define CRU_CRU_CLKSEL_CON27_PCLK_ALIVE_DIV_MASK           (0x1FU << CRU_CRU_CLKSEL_CON27_PCLK_ALIVE_DIV_SHIFT)         /* 0x0000001F */
/* CRU_CLKSEL_CON28 */
#define CRU_CRU_CLKSEL_CON28_OFFSET                        (0xF0)
#define CRU_CRU_CLKSEL_CON28_HCLK_ALIVE_DIV_SHIFT          (0U)
#define CRU_CRU_CLKSEL_CON28_HCLK_ALIVE_DIV_MASK           (0x1FU << CRU_CRU_CLKSEL_CON28_HCLK_ALIVE_DIV_SHIFT)         /* 0x0000001F */
/* CRU_CLKSEL_CON30 */
#define CRU_CRU_CLKSEL_CON30_OFFSET                        (0xF8)
#define CRU_CRU_CLKSEL_CON30_CLK_TESTOUT_DIV_SHIFT         (0U)
#define CRU_CRU_CLKSEL_CON30_CLK_TESTOUT_DIV_MASK          (0xFFU << CRU_CRU_CLKSEL_CON30_CLK_TESTOUT_DIV_SHIFT)        /* 0x000000FF */
#define CRU_CRU_CLKSEL_CON30_CLK_TESTOUT_SEL_SHIFT         (8U)
#define CRU_CRU_CLKSEL_CON30_CLK_TESTOUT_SEL_MASK          (0xFU << CRU_CRU_CLKSEL_CON30_CLK_TESTOUT_SEL_SHIFT)         /* 0x00000F00 */
/* CRU_CLKSEL_CON31 */
#define CRU_CRU_CLKSEL_CON31_OFFSET                        (0xFC)
#define CRU_CRU_CLKSEL_CON31_CLK_PDM_SAMP_DIV_SHIFT        (0U)
#define CRU_CRU_CLKSEL_CON31_CLK_PDM_SAMP_DIV_MASK         (0x1FU << CRU_CRU_CLKSEL_CON31_CLK_PDM_SAMP_DIV_SHIFT)       /* 0x0000001F */
#define CRU_CRU_CLKSEL_CON31_CLK_PDM_SAMP_SEL_SHIFT        (5U)
#define CRU_CRU_CLKSEL_CON31_CLK_PDM_SAMP_SEL_MASK         (0x1U << CRU_CRU_CLKSEL_CON31_CLK_PDM_SAMP_SEL_SHIFT)        /* 0x00000020 */
/* CRU_CLKSEL_CON33 */
#define CRU_CRU_CLKSEL_CON33_OFFSET                        (0x104)
#define CRU_CRU_CLKSEL_CON33_HCLK_M4_DIV_SHIFT             (0U)
#define CRU_CRU_CLKSEL_CON33_HCLK_M4_DIV_MASK              (0x1FU << CRU_CRU_CLKSEL_CON33_HCLK_M4_DIV_SHIFT)            /* 0x0000001F */
#define CRU_CRU_CLKSEL_CON33_HCLK_M4_SEL_SHIFT             (7U)
#define CRU_CRU_CLKSEL_CON33_HCLK_M4_SEL_MASK              (0x1U << CRU_CRU_CLKSEL_CON33_HCLK_M4_SEL_SHIFT)             /* 0x00000080 */
#define CRU_CRU_CLKSEL_CON33_CLK_SPI1_DIV_SHIFT            (8U)
#define CRU_CRU_CLKSEL_CON33_CLK_SPI1_DIV_MASK             (0x1FU << CRU_CRU_CLKSEL_CON33_CLK_SPI1_DIV_SHIFT)           /* 0x00001F00 */
/* CRU_CLKSEL_CON34 */
#define CRU_CRU_CLKSEL_CON34_OFFSET                        (0x108)
#define CRU_CRU_CLKSEL_CON34_CLK_SPI2_DIV_SHIFT            (8U)
#define CRU_CRU_CLKSEL_CON34_CLK_SPI2_DIV_MASK             (0x1FU << CRU_CRU_CLKSEL_CON34_CLK_SPI2_DIV_SHIFT)           /* 0x00001F00 */
#define CRU_CRU_CLKSEL_CON34_SCLK_SFC_SEL_SHIFT            (14U)
#define CRU_CRU_CLKSEL_CON34_SCLK_SFC_SEL_MASK             (0x1U << CRU_CRU_CLKSEL_CON34_SCLK_SFC_SEL_SHIFT)            /* 0x00004000 */
/* CRU_CLKSEL_CON35 */
#define CRU_CRU_CLKSEL_CON35_OFFSET                        (0x10C)
#define CRU_CRU_CLKSEL_CON35_SCLK_SFC_DIV_SHIFT            (0U)
#define CRU_CRU_CLKSEL_CON35_SCLK_SFC_DIV_MASK             (0xFFU << CRU_CRU_CLKSEL_CON35_SCLK_SFC_DIV_SHIFT)           /* 0x000000FF */
#define CRU_CRU_CLKSEL_CON35_CLK_SDIO_DIV_SHIFT            (8U)
#define CRU_CRU_CLKSEL_CON35_CLK_SDIO_DIV_MASK             (0xFFU << CRU_CRU_CLKSEL_CON35_CLK_SDIO_DIV_SHIFT)           /* 0x0000FF00 */
/* CRU_CLKSEL_CON36 */
#define CRU_CRU_CLKSEL_CON36_OFFSET                        (0x110)
#define CRU_CRU_CLKSEL_CON36_CLK_SDIO_SEL_SHIFT            (8U)
#define CRU_CRU_CLKSEL_CON36_CLK_SDIO_SEL_MASK             (0x3U << CRU_CRU_CLKSEL_CON36_CLK_SDIO_SEL_SHIFT)            /* 0x00000300 */
#define CRU_CRU_CLKSEL_CON36_PCLK_CIF_SRC_SEL_SHIFT        (12U)
#define CRU_CRU_CLKSEL_CON36_PCLK_CIF_SRC_SEL_MASK         (0x1U << CRU_CRU_CLKSEL_CON36_PCLK_CIF_SRC_SEL_SHIFT)        /* 0x00001000 */
/* CRU_CLKSEL_CON37 */
#define CRU_CRU_CLKSEL_CON37_OFFSET                        (0x114)
#define CRU_CRU_CLKSEL_CON37_CLK_AUDPWM_DF_DIV_SHIFT       (0U)
#define CRU_CRU_CLKSEL_CON37_CLK_AUDPWM_DF_DIV_MASK        (0x1FU << CRU_CRU_CLKSEL_CON37_CLK_AUDPWM_DF_DIV_SHIFT)      /* 0x0000001F */
#define CRU_CRU_CLKSEL_CON37_CLK_AUDPWM_SEL_SHIFT          (5U)
#define CRU_CRU_CLKSEL_CON37_CLK_AUDPWM_SEL_MASK           (0x1U << CRU_CRU_CLKSEL_CON37_CLK_AUDPWM_SEL_SHIFT)          /* 0x00000020 */
#define CRU_CRU_CLKSEL_CON37_CLK_AUDPWM_SRC_SEL_SHIFT      (6U)
#define CRU_CRU_CLKSEL_CON37_CLK_AUDPWM_SRC_SEL_MASK       (0x1U << CRU_CRU_CLKSEL_CON37_CLK_AUDPWM_SRC_SEL_SHIFT)      /* 0x00000040 */
#define CRU_CRU_CLKSEL_CON37_I2S1_MCLKOUT_SEL_SHIFT        (7U)
#define CRU_CRU_CLKSEL_CON37_I2S1_MCLKOUT_SEL_MASK         (0x1U << CRU_CRU_CLKSEL_CON37_I2S1_MCLKOUT_SEL_SHIFT)        /* 0x00000080 */
#define CRU_CRU_CLKSEL_CON37_CLK_I2S1_8CH_SRC_DIV_SHIFT    (8U)
#define CRU_CRU_CLKSEL_CON37_CLK_I2S1_8CH_SRC_DIV_MASK     (0x1FU << CRU_CRU_CLKSEL_CON37_CLK_I2S1_8CH_SRC_DIV_SHIFT)   /* 0x00001F00 */
#define CRU_CRU_CLKSEL_CON37_CLK_I2S1_8CH_SRC_SEL_SHIFT    (13U)
#define CRU_CRU_CLKSEL_CON37_CLK_I2S1_8CH_SRC_SEL_MASK     (0x1U << CRU_CRU_CLKSEL_CON37_CLK_I2S1_8CH_SRC_SEL_SHIFT)    /* 0x00002000 */
#define CRU_CRU_CLKSEL_CON37_MCLK_I2S1_8CH_SEL_SHIFT       (14U)
#define CRU_CRU_CLKSEL_CON37_MCLK_I2S1_8CH_SEL_MASK        (0x3U << CRU_CRU_CLKSEL_CON37_MCLK_I2S1_8CH_SEL_SHIFT)       /* 0x0000C000 */
/* CRU_CLKSEL_CON38 */
#define CRU_CRU_CLKSEL_CON38_OFFSET                        (0x118)
#define CRU_CRU_CLKSEL_CON38_CLK_I2S1_8CH_FRAC_DIV_SHIFT   (0U)
#define CRU_CRU_CLKSEL_CON38_CLK_I2S1_8CH_FRAC_DIV_MASK    (0xFFFFFFFFU << CRU_CRU_CLKSEL_CON38_CLK_I2S1_8CH_FRAC_DIV_SHIFT) /* 0xFFFFFFFF */
/* CRU_CLKSEL_CON39 */
#define CRU_CRU_CLKSEL_CON39_OFFSET                        (0x11C)
#define CRU_CRU_CLKSEL_CON39_CLK_PWM_DIV_SHIFT             (0U)
#define CRU_CRU_CLKSEL_CON39_CLK_PWM_DIV_MASK              (0x1FU << CRU_CRU_CLKSEL_CON39_CLK_PWM_DIV_SHIFT)            /* 0x0000001F */
#define CRU_CRU_CLKSEL_CON39_CLK_PWM_SEL_SHIFT             (5U)
#define CRU_CRU_CLKSEL_CON39_CLK_PWM_SEL_MASK              (0x1U << CRU_CRU_CLKSEL_CON39_CLK_PWM_SEL_SHIFT)             /* 0x00000020 */
#define CRU_CRU_CLKSEL_CON39_HCLK_LOGIC_DIV_SHIFT          (8U)
#define CRU_CRU_CLKSEL_CON39_HCLK_LOGIC_DIV_MASK           (0x1FU << CRU_CRU_CLKSEL_CON39_HCLK_LOGIC_DIV_SHIFT)         /* 0x00001F00 */
#define CRU_CRU_CLKSEL_CON39_HCLK_LOGIC_SEL_SHIFT          (15U)
#define CRU_CRU_CLKSEL_CON39_HCLK_LOGIC_SEL_MASK           (0x1U << CRU_CRU_CLKSEL_CON39_HCLK_LOGIC_SEL_SHIFT)          /* 0x00008000 */
/* CRU_CLKSEL_CON40 */
#define CRU_CRU_CLKSEL_CON40_OFFSET                        (0x120)
#define CRU_CRU_CLKSEL_CON40_PCLK_LOGIC_DIV_SHIFT          (0U)
#define CRU_CRU_CLKSEL_CON40_PCLK_LOGIC_DIV_MASK           (0x1FU << CRU_CRU_CLKSEL_CON40_PCLK_LOGIC_DIV_SHIFT)         /* 0x0000001F */
#define CRU_CRU_CLKSEL_CON40_PCLK_LOGIC_SEL_SHIFT          (7U)
#define CRU_CRU_CLKSEL_CON40_PCLK_LOGIC_SEL_MASK           (0x1U << CRU_CRU_CLKSEL_CON40_PCLK_LOGIC_SEL_SHIFT)          /* 0x00000080 */
#define CRU_CRU_CLKSEL_CON40_ACLK_LOGIC_DIV_SHIFT          (8U)
#define CRU_CRU_CLKSEL_CON40_ACLK_LOGIC_DIV_MASK           (0x1FU << CRU_CRU_CLKSEL_CON40_ACLK_LOGIC_DIV_SHIFT)         /* 0x00001F00 */
#define CRU_CRU_CLKSEL_CON40_ACLK_LOGIC_SEL_SHIFT          (15U)
#define CRU_CRU_CLKSEL_CON40_ACLK_LOGIC_SEL_MASK           (0x1U << CRU_CRU_CLKSEL_CON40_ACLK_LOGIC_SEL_SHIFT)          /* 0x00008000 */
/* CRU_CLKSEL_CON41 */
#define CRU_CRU_CLKSEL_CON41_OFFSET                        (0x124)
#define CRU_CRU_CLKSEL_CON41_CLK_CIFOUT_DIV_SHIFT          (0U)
#define CRU_CRU_CLKSEL_CON41_CLK_CIFOUT_DIV_MASK           (0x1FU << CRU_CRU_CLKSEL_CON41_CLK_CIFOUT_DIV_SHIFT)         /* 0x0000001F */
#define CRU_CRU_CLKSEL_CON41_CLK_CIFOUT_SEL_SHIFT          (6U)
#define CRU_CRU_CLKSEL_CON41_CLK_CIFOUT_SEL_MASK           (0x3U << CRU_CRU_CLKSEL_CON41_CLK_CIFOUT_SEL_SHIFT)          /* 0x000000C0 */
#define CRU_CRU_CLKSEL_CON41_CLK_USB2PHY_REF_FRAC_SEL_SHIFT (8U)
#define CRU_CRU_CLKSEL_CON41_CLK_USB2PHY_REF_FRAC_SEL_MASK (0x1U << CRU_CRU_CLKSEL_CON41_CLK_USB2PHY_REF_FRAC_SEL_SHIFT) /* 0x00000100 */
#define CRU_CRU_CLKSEL_CON41_CLK_USB2PHY_REF_SEL_SHIFT     (9U)
#define CRU_CRU_CLKSEL_CON41_CLK_USB2PHY_REF_SEL_MASK      (0x1U << CRU_CRU_CLKSEL_CON41_CLK_USB2PHY_REF_SEL_SHIFT)     /* 0x00000200 */
#define CRU_CRU_CLKSEL_CON41_CLK_DPHY_REF_FRAC_SEL_SHIFT   (10U)
#define CRU_CRU_CLKSEL_CON41_CLK_DPHY_REF_FRAC_SEL_MASK    (0x1U << CRU_CRU_CLKSEL_CON41_CLK_DPHY_REF_FRAC_SEL_SHIFT)   /* 0x00000400 */
#define CRU_CRU_CLKSEL_CON41_CLK_DPHY_REF_SEL_SHIFT        (11U)
#define CRU_CRU_CLKSEL_CON41_CLK_DPHY_REF_SEL_MASK         (0x1U << CRU_CRU_CLKSEL_CON41_CLK_DPHY_REF_SEL_SHIFT)        /* 0x00000800 */
/* CRU_CLKSEL_CON42 */
#define CRU_CRU_CLKSEL_CON42_OFFSET                        (0x128)
#define CRU_CRU_CLKSEL_CON42_CLK_AUDPWM_FRAC_DIV_SHIFT     (0U)
#define CRU_CRU_CLKSEL_CON42_CLK_AUDPWM_FRAC_DIV_MASK      (0xFFFFFFFFU << CRU_CRU_CLKSEL_CON42_CLK_AUDPWM_FRAC_DIV_SHIFT) /* 0xFFFFFFFF */
/* CRU_CLKSEL_CON43 */
#define CRU_CRU_CLKSEL_CON43_OFFSET                        (0x12C)
#define CRU_CRU_CLKSEL_CON43_CLK_USB2PHY_REF_FRAC_DIV_SHIFT (0U)
#define CRU_CRU_CLKSEL_CON43_CLK_USB2PHY_REF_FRAC_DIV_MASK (0xFFFFFFFFU << CRU_CRU_CLKSEL_CON43_CLK_USB2PHY_REF_FRAC_DIV_SHIFT) /* 0xFFFFFFFF */
/* CRU_CLKSEL_CON44 */
#define CRU_CRU_CLKSEL_CON44_OFFSET                        (0x130)
#define CRU_CRU_CLKSEL_CON44_CLK_DPHY_REF_FRAC_DIV_SHIFT   (0U)
#define CRU_CRU_CLKSEL_CON44_CLK_DPHY_REF_FRAC_DIV_MASK    (0xFFFFFFFFU << CRU_CRU_CLKSEL_CON44_CLK_DPHY_REF_FRAC_DIV_SHIFT) /* 0xFFFFFFFF */
/* CRU_CLKSEL_CON46 */
#define CRU_CRU_CLKSEL_CON46_OFFSET                        (0x138)
#define CRU_CRU_CLKSEL_CON46_SCLK_SFC1_SEL_SHIFT           (14U)
#define CRU_CRU_CLKSEL_CON46_SCLK_SFC1_SEL_MASK            (0x1U << CRU_CRU_CLKSEL_CON46_SCLK_SFC1_SEL_SHIFT)           /* 0x00004000 */
/* CRU_CLKSEL_CON47 */
#define CRU_CRU_CLKSEL_CON47_OFFSET                        (0x13C)
#define CRU_CRU_CLKSEL_CON47_SCLK_SFC1_DIV_SHIFT           (0U)
#define CRU_CRU_CLKSEL_CON47_SCLK_SFC1_DIV_MASK            (0xFFU << CRU_CRU_CLKSEL_CON47_SCLK_SFC1_DIV_SHIFT)          /* 0x000000FF */
/* CRU_CLKSEL_CON49 */
#define CRU_CRU_CLKSEL_CON49_OFFSET                        (0x144)
#define CRU_CRU_CLKSEL_CON49_XIN_OSC0_DIV_DIV_SHIFT        (0U)
#define CRU_CRU_CLKSEL_CON49_XIN_OSC0_DIV_DIV_MASK         (0xFFFFFFFFU << CRU_CRU_CLKSEL_CON49_XIN_OSC0_DIV_DIV_SHIFT) /* 0xFFFFFFFF */
/* CRU_GATE_CON00 */
#define CRU_CRU_GATE_CON00_OFFSET                          (0x180)
#define CRU_CRU_GATE_CON00_ACLK_DSP_EN_SHIFT               (0U)
#define CRU_CRU_GATE_CON00_ACLK_DSP_EN_MASK                (0x1U << CRU_CRU_GATE_CON00_ACLK_DSP_EN_SHIFT)               /* 0x00000001 */
#define CRU_CRU_GATE_CON00_ACLK_DSP_NIU_EN_SHIFT           (2U)
#define CRU_CRU_GATE_CON00_ACLK_DSP_NIU_EN_MASK            (0x1U << CRU_CRU_GATE_CON00_ACLK_DSP_NIU_EN_SHIFT)           /* 0x00000004 */
#define CRU_CRU_GATE_CON00_PCLK_DSP_EN_SHIFT               (3U)
#define CRU_CRU_GATE_CON00_PCLK_DSP_EN_MASK                (0x1U << CRU_CRU_GATE_CON00_PCLK_DSP_EN_SHIFT)               /* 0x00000008 */
#define CRU_CRU_GATE_CON00_PCLK_DSP_NIU_EN_SHIFT           (4U)
#define CRU_CRU_GATE_CON00_PCLK_DSP_NIU_EN_MASK            (0x1U << CRU_CRU_GATE_CON00_PCLK_DSP_NIU_EN_SHIFT)           /* 0x00000010 */
#define CRU_CRU_GATE_CON00_PCLK_DSP_GRF_EN_SHIFT           (5U)
#define CRU_CRU_GATE_CON00_PCLK_DSP_GRF_EN_MASK            (0x1U << CRU_CRU_GATE_CON00_PCLK_DSP_GRF_EN_SHIFT)           /* 0x00000020 */
#define CRU_CRU_GATE_CON00_PCLK_WDT1_EN_SHIFT              (6U)
#define CRU_CRU_GATE_CON00_PCLK_WDT1_EN_MASK               (0x1U << CRU_CRU_GATE_CON00_PCLK_WDT1_EN_SHIFT)              /* 0x00000040 */
#define CRU_CRU_GATE_CON00_ACLK_DSP_S_EN_SHIFT             (7U)
#define CRU_CRU_GATE_CON00_ACLK_DSP_S_EN_MASK              (0x1U << CRU_CRU_GATE_CON00_ACLK_DSP_S_EN_SHIFT)             /* 0x00000080 */
/* CRU_GATE_CON01 */
#define CRU_CRU_GATE_CON01_OFFSET                          (0x184)
#define CRU_CRU_GATE_CON01_SCLK_SHRM_EN_SHIFT              (0U)
#define CRU_CRU_GATE_CON01_SCLK_SHRM_EN_MASK               (0x1U << CRU_CRU_GATE_CON01_SCLK_SHRM_EN_SHIFT)              /* 0x00000001 */
#define CRU_CRU_GATE_CON01_ACLK_SHRM_NIU_EN_SHIFT          (1U)
#define CRU_CRU_GATE_CON01_ACLK_SHRM_NIU_EN_MASK           (0x1U << CRU_CRU_GATE_CON01_ACLK_SHRM_NIU_EN_SHIFT)          /* 0x00000002 */
#define CRU_CRU_GATE_CON01_PCLK_SHRM_EN_SHIFT              (2U)
#define CRU_CRU_GATE_CON01_PCLK_SHRM_EN_MASK               (0x1U << CRU_CRU_GATE_CON01_PCLK_SHRM_EN_SHIFT)              /* 0x00000004 */
#define CRU_CRU_GATE_CON01_PCLK_SHRM_NIU_EN_SHIFT          (3U)
#define CRU_CRU_GATE_CON01_PCLK_SHRM_NIU_EN_MASK           (0x1U << CRU_CRU_GATE_CON01_PCLK_SHRM_NIU_EN_SHIFT)          /* 0x00000008 */
/* CRU_GATE_CON02 */
#define CRU_CRU_GATE_CON02_OFFSET                          (0x188)
#define CRU_CRU_GATE_CON02_PCLK_UART0_EN_SHIFT             (0U)
#define CRU_CRU_GATE_CON02_PCLK_UART0_EN_MASK              (0x1U << CRU_CRU_GATE_CON02_PCLK_UART0_EN_SHIFT)             /* 0x00000001 */
#define CRU_CRU_GATE_CON02_PCLK_UART1_EN_SHIFT             (1U)
#define CRU_CRU_GATE_CON02_PCLK_UART1_EN_MASK              (0x1U << CRU_CRU_GATE_CON02_PCLK_UART1_EN_SHIFT)             /* 0x00000002 */
#define CRU_CRU_GATE_CON02_PCLK_UART2_EN_SHIFT             (2U)
#define CRU_CRU_GATE_CON02_PCLK_UART2_EN_MASK              (0x1U << CRU_CRU_GATE_CON02_PCLK_UART2_EN_SHIFT)             /* 0x00000004 */
#define CRU_CRU_GATE_CON02_CLK_UART0_EN_SHIFT              (3U)
#define CRU_CRU_GATE_CON02_CLK_UART0_EN_MASK               (0x1U << CRU_CRU_GATE_CON02_CLK_UART0_EN_SHIFT)              /* 0x00000008 */
#define CRU_CRU_GATE_CON02_CLK_UART0_FRAC_EN_SHIFT         (4U)
#define CRU_CRU_GATE_CON02_CLK_UART0_FRAC_EN_MASK          (0x1U << CRU_CRU_GATE_CON02_CLK_UART0_FRAC_EN_SHIFT)         /* 0x00000010 */
#define CRU_CRU_GATE_CON02_SCLK_UART0_EN_SHIFT             (6U)
#define CRU_CRU_GATE_CON02_SCLK_UART0_EN_MASK              (0x1U << CRU_CRU_GATE_CON02_SCLK_UART0_EN_SHIFT)             /* 0x00000040 */
#define CRU_CRU_GATE_CON02_CLK_UART1_EN_SHIFT              (7U)
#define CRU_CRU_GATE_CON02_CLK_UART1_EN_MASK               (0x1U << CRU_CRU_GATE_CON02_CLK_UART1_EN_SHIFT)              /* 0x00000080 */
#define CRU_CRU_GATE_CON02_CLK_UART1_FRAC_EN_SHIFT         (8U)
#define CRU_CRU_GATE_CON02_CLK_UART1_FRAC_EN_MASK          (0x1U << CRU_CRU_GATE_CON02_CLK_UART1_FRAC_EN_SHIFT)         /* 0x00000100 */
#define CRU_CRU_GATE_CON02_SCLK_UART1_EN_SHIFT             (10U)
#define CRU_CRU_GATE_CON02_SCLK_UART1_EN_MASK              (0x1U << CRU_CRU_GATE_CON02_SCLK_UART1_EN_SHIFT)             /* 0x00000400 */
#define CRU_CRU_GATE_CON02_CLK_UART2_EN_SHIFT              (11U)
#define CRU_CRU_GATE_CON02_CLK_UART2_EN_MASK               (0x1U << CRU_CRU_GATE_CON02_CLK_UART2_EN_SHIFT)              /* 0x00000800 */
#define CRU_CRU_GATE_CON02_CLK_UART2_FRAC_EN_SHIFT         (12U)
#define CRU_CRU_GATE_CON02_CLK_UART2_FRAC_EN_MASK          (0x1U << CRU_CRU_GATE_CON02_CLK_UART2_FRAC_EN_SHIFT)         /* 0x00001000 */
#define CRU_CRU_GATE_CON02_SCLK_UART2_EN_SHIFT             (14U)
#define CRU_CRU_GATE_CON02_SCLK_UART2_EN_MASK              (0x1U << CRU_CRU_GATE_CON02_SCLK_UART2_EN_SHIFT)             /* 0x00004000 */
/* CRU_GATE_CON04 */
#define CRU_CRU_GATE_CON04_OFFSET                          (0x190)
#define CRU_CRU_GATE_CON04_PCLK_TIMER_EN_SHIFT             (0U)
#define CRU_CRU_GATE_CON04_PCLK_TIMER_EN_MASK              (0x1U << CRU_CRU_GATE_CON04_PCLK_TIMER_EN_SHIFT)             /* 0x00000001 */
#define CRU_CRU_GATE_CON04_CLK_TIMER0_EN_SHIFT             (1U)
#define CRU_CRU_GATE_CON04_CLK_TIMER0_EN_MASK              (0x1U << CRU_CRU_GATE_CON04_CLK_TIMER0_EN_SHIFT)             /* 0x00000002 */
#define CRU_CRU_GATE_CON04_CLK_TIMER1_EN_SHIFT             (2U)
#define CRU_CRU_GATE_CON04_CLK_TIMER1_EN_MASK              (0x1U << CRU_CRU_GATE_CON04_CLK_TIMER1_EN_SHIFT)             /* 0x00000004 */
#define CRU_CRU_GATE_CON04_CLK_TIMER2_EN_SHIFT             (3U)
#define CRU_CRU_GATE_CON04_CLK_TIMER2_EN_MASK              (0x1U << CRU_CRU_GATE_CON04_CLK_TIMER2_EN_SHIFT)             /* 0x00000008 */
#define CRU_CRU_GATE_CON04_CLK_TIMER3_EN_SHIFT             (4U)
#define CRU_CRU_GATE_CON04_CLK_TIMER3_EN_MASK              (0x1U << CRU_CRU_GATE_CON04_CLK_TIMER3_EN_SHIFT)             /* 0x00000010 */
#define CRU_CRU_GATE_CON04_CLK_TIMER4_EN_SHIFT             (5U)
#define CRU_CRU_GATE_CON04_CLK_TIMER4_EN_MASK              (0x1U << CRU_CRU_GATE_CON04_CLK_TIMER4_EN_SHIFT)             /* 0x00000020 */
#define CRU_CRU_GATE_CON04_CLK_TIMER5_EN_SHIFT             (6U)
#define CRU_CRU_GATE_CON04_CLK_TIMER5_EN_MASK              (0x1U << CRU_CRU_GATE_CON04_CLK_TIMER5_EN_SHIFT)             /* 0x00000040 */
/* CRU_GATE_CON05 */
#define CRU_CRU_GATE_CON05_OFFSET                          (0x194)
#define CRU_CRU_GATE_CON05_PCLK_I2C2APB_NIU_EN_SHIFT       (0U)
#define CRU_CRU_GATE_CON05_PCLK_I2C2APB_NIU_EN_MASK        (0x1U << CRU_CRU_GATE_CON05_PCLK_I2C2APB_NIU_EN_SHIFT)       /* 0x00000001 */
#define CRU_CRU_GATE_CON05_PCLK_I2C0_EN_SHIFT              (1U)
#define CRU_CRU_GATE_CON05_PCLK_I2C0_EN_MASK               (0x1U << CRU_CRU_GATE_CON05_PCLK_I2C0_EN_SHIFT)              /* 0x00000002 */
#define CRU_CRU_GATE_CON05_PCLK_I2C1_EN_SHIFT              (2U)
#define CRU_CRU_GATE_CON05_PCLK_I2C1_EN_MASK               (0x1U << CRU_CRU_GATE_CON05_PCLK_I2C1_EN_SHIFT)              /* 0x00000004 */
#define CRU_CRU_GATE_CON05_PCLK_I2C2_EN_SHIFT              (3U)
#define CRU_CRU_GATE_CON05_PCLK_I2C2_EN_MASK               (0x1U << CRU_CRU_GATE_CON05_PCLK_I2C2_EN_SHIFT)              /* 0x00000008 */
#define CRU_CRU_GATE_CON05_PCLK_I2C2APB_EN_SHIFT           (4U)
#define CRU_CRU_GATE_CON05_PCLK_I2C2APB_EN_MASK            (0x1U << CRU_CRU_GATE_CON05_PCLK_I2C2APB_EN_SHIFT)           /* 0x00000010 */
#define CRU_CRU_GATE_CON05_CLK_I2C0_EN_SHIFT               (5U)
#define CRU_CRU_GATE_CON05_CLK_I2C0_EN_MASK                (0x1U << CRU_CRU_GATE_CON05_CLK_I2C0_EN_SHIFT)               /* 0x00000020 */
#define CRU_CRU_GATE_CON05_CLK_I2C1_EN_SHIFT               (6U)
#define CRU_CRU_GATE_CON05_CLK_I2C1_EN_MASK                (0x1U << CRU_CRU_GATE_CON05_CLK_I2C1_EN_SHIFT)               /* 0x00000040 */
#define CRU_CRU_GATE_CON05_CLK_I2C2_EN_SHIFT               (7U)
#define CRU_CRU_GATE_CON05_CLK_I2C2_EN_MASK                (0x1U << CRU_CRU_GATE_CON05_CLK_I2C2_EN_SHIFT)               /* 0x00000080 */
#define CRU_CRU_GATE_CON05_PCLK_ACDC_DIG_EN_SHIFT          (14U)
#define CRU_CRU_GATE_CON05_PCLK_ACDC_DIG_EN_MASK           (0x1U << CRU_CRU_GATE_CON05_PCLK_ACDC_DIG_EN_SHIFT)          /* 0x00004000 */
#define CRU_CRU_GATE_CON05_ACLK_DMAC_CORE_EN_SHIFT         (15U)
#define CRU_CRU_GATE_CON05_ACLK_DMAC_CORE_EN_MASK          (0x1U << CRU_CRU_GATE_CON05_ACLK_DMAC_CORE_EN_SHIFT)         /* 0x00008000 */
/* CRU_GATE_CON06 */
#define CRU_CRU_GATE_CON06_OFFSET                          (0x198)
#define CRU_CRU_GATE_CON06_HCLK_PDM0_EN_SHIFT              (0U)
#define CRU_CRU_GATE_CON06_HCLK_PDM0_EN_MASK               (0x1U << CRU_CRU_GATE_CON06_HCLK_PDM0_EN_SHIFT)              /* 0x00000001 */
#define CRU_CRU_GATE_CON06_HCLK_AUDIO_EN_SHIFT             (1U)
#define CRU_CRU_GATE_CON06_HCLK_AUDIO_EN_MASK              (0x1U << CRU_CRU_GATE_CON06_HCLK_AUDIO_EN_SHIFT)             /* 0x00000002 */
#define CRU_CRU_GATE_CON06_HCLK_I2S_8CH_EN_SHIFT           (2U)
#define CRU_CRU_GATE_CON06_HCLK_I2S_8CH_EN_MASK            (0x1U << CRU_CRU_GATE_CON06_HCLK_I2S_8CH_EN_SHIFT)           /* 0x00000004 */
#define CRU_CRU_GATE_CON06_HCLK_VAD_EN_SHIFT               (3U)
#define CRU_CRU_GATE_CON06_HCLK_VAD_EN_MASK                (0x1U << CRU_CRU_GATE_CON06_HCLK_VAD_EN_SHIFT)               /* 0x00000008 */
#define CRU_CRU_GATE_CON06_HCLK_AUDIO_NIU_EN_SHIFT         (4U)
#define CRU_CRU_GATE_CON06_HCLK_AUDIO_NIU_EN_MASK          (0x1U << CRU_CRU_GATE_CON06_HCLK_AUDIO_NIU_EN_SHIFT)         /* 0x00000010 */
#define CRU_CRU_GATE_CON06_HCLK_AUDIO_AHB_ARB_EN_SHIFT     (5U)
#define CRU_CRU_GATE_CON06_HCLK_AUDIO_AHB_ARB_EN_MASK      (0x1U << CRU_CRU_GATE_CON06_HCLK_AUDIO_AHB_ARB_EN_SHIFT)     /* 0x00000020 */
#define CRU_CRU_GATE_CON06_PCLK_AUDIO_NIU_EN_SHIFT         (6U)
#define CRU_CRU_GATE_CON06_PCLK_AUDIO_NIU_EN_MASK          (0x1U << CRU_CRU_GATE_CON06_PCLK_AUDIO_NIU_EN_SHIFT)         /* 0x00000040 */
#define CRU_CRU_GATE_CON06_MCLK_PDM0_EN_SHIFT              (7U)
#define CRU_CRU_GATE_CON06_MCLK_PDM0_EN_MASK               (0x1U << CRU_CRU_GATE_CON06_MCLK_PDM0_EN_SHIFT)              /* 0x00000080 */
#define CRU_CRU_GATE_CON06_MCLK_PDM0_OUT_EN_SHIFT          (8U)
#define CRU_CRU_GATE_CON06_MCLK_PDM0_OUT_EN_MASK           (0x1U << CRU_CRU_GATE_CON06_MCLK_PDM0_OUT_EN_SHIFT)          /* 0x00000100 */
#define CRU_CRU_GATE_CON06_PCLK_AUDIO_EN_SHIFT             (9U)
#define CRU_CRU_GATE_CON06_PCLK_AUDIO_EN_MASK              (0x1U << CRU_CRU_GATE_CON06_PCLK_AUDIO_EN_SHIFT)             /* 0x00000200 */
#define CRU_CRU_GATE_CON06_CLK_I2S8CH_EN_SHIFT             (10U)
#define CRU_CRU_GATE_CON06_CLK_I2S8CH_EN_MASK              (0x1U << CRU_CRU_GATE_CON06_CLK_I2S8CH_EN_SHIFT)             /* 0x00000400 */
#define CRU_CRU_GATE_CON06_CLK_I2S8CH_FRAC_EN_SHIFT        (11U)
#define CRU_CRU_GATE_CON06_CLK_I2S8CH_FRAC_EN_MASK         (0x1U << CRU_CRU_GATE_CON06_CLK_I2S8CH_FRAC_EN_SHIFT)        /* 0x00000800 */
#define CRU_CRU_GATE_CON06_MCLK_I2S8CH_EN_SHIFT            (12U)
#define CRU_CRU_GATE_CON06_MCLK_I2S8CH_EN_MASK             (0x1U << CRU_CRU_GATE_CON06_MCLK_I2S8CH_EN_SHIFT)            /* 0x00001000 */
#define CRU_CRU_GATE_CON06_I2S_MCLKOUT_EN_SHIFT            (13U)
#define CRU_CRU_GATE_CON06_I2S_MCLKOUT_EN_MASK             (0x1U << CRU_CRU_GATE_CON06_I2S_MCLKOUT_EN_SHIFT)            /* 0x00002000 */
#define CRU_CRU_GATE_CON06_ACLK_DMAC_EN_SHIFT              (14U)
#define CRU_CRU_GATE_CON06_ACLK_DMAC_EN_MASK               (0x1U << CRU_CRU_GATE_CON06_ACLK_DMAC_EN_SHIFT)              /* 0x00004000 */
#define CRU_CRU_GATE_CON06_ACLK_DMAC_NIU_EN_SHIFT          (15U)
#define CRU_CRU_GATE_CON06_ACLK_DMAC_NIU_EN_MASK           (0x1U << CRU_CRU_GATE_CON06_ACLK_DMAC_NIU_EN_SHIFT)          /* 0x00008000 */
/* CRU_GATE_CON07 */
#define CRU_CRU_GATE_CON07_OFFSET                          (0x19C)
#define CRU_CRU_GATE_CON07_ACLK_VOP_EN_SHIFT               (0U)
#define CRU_CRU_GATE_CON07_ACLK_VOP_EN_MASK                (0x1U << CRU_CRU_GATE_CON07_ACLK_VOP_EN_SHIFT)               /* 0x00000001 */
#define CRU_CRU_GATE_CON07_DCLK_VOP_S_EN_SHIFT             (2U)
#define CRU_CRU_GATE_CON07_DCLK_VOP_S_EN_MASK              (0x1U << CRU_CRU_GATE_CON07_DCLK_VOP_S_EN_SHIFT)             /* 0x00000004 */
#define CRU_CRU_GATE_CON07_ACLK_VOP_NIU_EN_SHIFT           (3U)
#define CRU_CRU_GATE_CON07_ACLK_VOP_NIU_EN_MASK            (0x1U << CRU_CRU_GATE_CON07_ACLK_VOP_NIU_EN_SHIFT)           /* 0x00000008 */
#define CRU_CRU_GATE_CON07_DCLK_VOP_EN_SHIFT               (4U)
#define CRU_CRU_GATE_CON07_DCLK_VOP_EN_MASK                (0x1U << CRU_CRU_GATE_CON07_DCLK_VOP_EN_SHIFT)               /* 0x00000010 */
#define CRU_CRU_GATE_CON07_DCLK_MIPIDSI_HOST_EN_SHIFT      (5U)
#define CRU_CRU_GATE_CON07_DCLK_MIPIDSI_HOST_EN_MASK       (0x1U << CRU_CRU_GATE_CON07_DCLK_MIPIDSI_HOST_EN_SHIFT)      /* 0x00000020 */
#define CRU_CRU_GATE_CON07_OCC_SCAN_CLK_DPHYLANBYTE_EN_SHIFT (8U)
#define CRU_CRU_GATE_CON07_OCC_SCAN_CLK_DPHYLANBYTE_EN_MASK (0x1U << CRU_CRU_GATE_CON07_OCC_SCAN_CLK_DPHYLANBYTE_EN_SHIFT) /* 0x00000100 */
/* CRU_GATE_CON08 */
#define CRU_CRU_GATE_CON08_OFFSET                          (0x1A0)
#define CRU_CRU_GATE_CON08_PCLK_GPIO0_EN_SHIFT             (0U)
#define CRU_CRU_GATE_CON08_PCLK_GPIO0_EN_MASK              (0x1U << CRU_CRU_GATE_CON08_PCLK_GPIO0_EN_SHIFT)             /* 0x00000001 */
#define CRU_CRU_GATE_CON08_PCLK_GPIO1_EN_SHIFT             (1U)
#define CRU_CRU_GATE_CON08_PCLK_GPIO1_EN_MASK              (0x1U << CRU_CRU_GATE_CON08_PCLK_GPIO1_EN_SHIFT)             /* 0x00000002 */
#define CRU_CRU_GATE_CON08_CLK_GPIO_DB0_EN_SHIFT           (3U)
#define CRU_CRU_GATE_CON08_CLK_GPIO_DB0_EN_MASK            (0x1U << CRU_CRU_GATE_CON08_CLK_GPIO_DB0_EN_SHIFT)           /* 0x00000008 */
#define CRU_CRU_GATE_CON08_CLK_GPIO_DB1_EN_SHIFT           (4U)
#define CRU_CRU_GATE_CON08_CLK_GPIO_DB1_EN_MASK            (0x1U << CRU_CRU_GATE_CON08_CLK_GPIO_DB1_EN_SHIFT)           /* 0x00000010 */
/* CRU_GATE_CON09 */
#define CRU_CRU_GATE_CON09_OFFSET                          (0x1A4)
#define CRU_CRU_GATE_CON09_PCLK_ALIVE_EN_SHIFT             (0U)
#define CRU_CRU_GATE_CON09_PCLK_ALIVE_EN_MASK              (0x1U << CRU_CRU_GATE_CON09_PCLK_ALIVE_EN_SHIFT)             /* 0x00000001 */
#define CRU_CRU_GATE_CON09_HCLK_ALIVE_EN_SHIFT             (1U)
#define CRU_CRU_GATE_CON09_HCLK_ALIVE_EN_MASK              (0x1U << CRU_CRU_GATE_CON09_HCLK_ALIVE_EN_SHIFT)             /* 0x00000002 */
#define CRU_CRU_GATE_CON09_HCLK_ALIVE_NIU_EN_SHIFT         (2U)
#define CRU_CRU_GATE_CON09_HCLK_ALIVE_NIU_EN_MASK          (0x1U << CRU_CRU_GATE_CON09_HCLK_ALIVE_NIU_EN_SHIFT)         /* 0x00000004 */
#define CRU_CRU_GATE_CON09_HCLK_ALIVEAHB_ARB_EN_SHIFT      (3U)
#define CRU_CRU_GATE_CON09_HCLK_ALIVEAHB_ARB_EN_MASK       (0x1U << CRU_CRU_GATE_CON09_HCLK_ALIVEAHB_ARB_EN_SHIFT)      /* 0x00000008 */
#define CRU_CRU_GATE_CON09_HCLK_INTC0_EN_SHIFT             (4U)
#define CRU_CRU_GATE_CON09_HCLK_INTC0_EN_MASK              (0x1U << CRU_CRU_GATE_CON09_HCLK_INTC0_EN_SHIFT)             /* 0x00000010 */
#define CRU_CRU_GATE_CON09_HCLK_INTC1_EN_SHIFT             (5U)
#define CRU_CRU_GATE_CON09_HCLK_INTC1_EN_MASK              (0x1U << CRU_CRU_GATE_CON09_HCLK_INTC1_EN_SHIFT)             /* 0x00000020 */
#define CRU_CRU_GATE_CON09_PCLK_CRU_EN_SHIFT               (8U)
#define CRU_CRU_GATE_CON09_PCLK_CRU_EN_MASK                (0x1U << CRU_CRU_GATE_CON09_PCLK_CRU_EN_SHIFT)               /* 0x00000100 */
#define CRU_CRU_GATE_CON09_PCLK_ALIVE_NIU_EN_SHIFT         (9U)
#define CRU_CRU_GATE_CON09_PCLK_ALIVE_NIU_EN_MASK          (0x1U << CRU_CRU_GATE_CON09_PCLK_ALIVE_NIU_EN_SHIFT)         /* 0x00000200 */
#define CRU_CRU_GATE_CON09_PCLK_PMU_EN_SHIFT               (10U)
#define CRU_CRU_GATE_CON09_PCLK_PMU_EN_MASK                (0x1U << CRU_CRU_GATE_CON09_PCLK_PMU_EN_SHIFT)               /* 0x00000400 */
#define CRU_CRU_GATE_CON09_PCLK_GRF_EN_SHIFT               (11U)
#define CRU_CRU_GATE_CON09_PCLK_GRF_EN_MASK                (0x1U << CRU_CRU_GATE_CON09_PCLK_GRF_EN_SHIFT)               /* 0x00000800 */
#define CRU_CRU_GATE_CON09_CLK_PMU_EN_SHIFT                (12U)
#define CRU_CRU_GATE_CON09_CLK_PMU_EN_MASK                 (0x1U << CRU_CRU_GATE_CON09_CLK_PMU_EN_SHIFT)                /* 0x00001000 */
#define CRU_CRU_GATE_CON09_CLK_TESTOUT_EN_SHIFT            (13U)
#define CRU_CRU_GATE_CON09_CLK_TESTOUT_EN_MASK             (0x1U << CRU_CRU_GATE_CON09_CLK_TESTOUT_EN_SHIFT)            /* 0x00002000 */
#define CRU_CRU_GATE_CON09_CLK_PVTM_EN_SHIFT               (14U)
#define CRU_CRU_GATE_CON09_CLK_PVTM_EN_MASK                (0x1U << CRU_CRU_GATE_CON09_CLK_PVTM_EN_SHIFT)               /* 0x00004000 */
#define CRU_CRU_GATE_CON09_CLK_PDM_SAMP_EN_SHIFT           (15U)
#define CRU_CRU_GATE_CON09_CLK_PDM_SAMP_EN_MASK            (0x1U << CRU_CRU_GATE_CON09_CLK_PDM_SAMP_EN_SHIFT)           /* 0x00008000 */
/* CRU_GATE_CON10 */
#define CRU_CRU_GATE_CON10_OFFSET                          (0x1A8)
#define CRU_CRU_GATE_CON10_CLK_MEMSUBSYS0_EN_SHIFT         (0U)
#define CRU_CRU_GATE_CON10_CLK_MEMSUBSYS0_EN_MASK          (0x1U << CRU_CRU_GATE_CON10_CLK_MEMSUBSYS0_EN_SHIFT)         /* 0x00000001 */
#define CRU_CRU_GATE_CON10_CLK_MEMSUBSYS1_EN_SHIFT         (1U)
#define CRU_CRU_GATE_CON10_CLK_MEMSUBSYS1_EN_MASK          (0x1U << CRU_CRU_GATE_CON10_CLK_MEMSUBSYS1_EN_SHIFT)         /* 0x00000002 */
#define CRU_CRU_GATE_CON10_CLK_MEMSUBSYS2_EN_SHIFT         (2U)
#define CRU_CRU_GATE_CON10_CLK_MEMSUBSYS2_EN_MASK          (0x1U << CRU_CRU_GATE_CON10_CLK_MEMSUBSYS2_EN_SHIFT)         /* 0x00000004 */
#define CRU_CRU_GATE_CON10_CLK_MEMSUBSYS3_EN_SHIFT         (3U)
#define CRU_CRU_GATE_CON10_CLK_MEMSUBSYS3_EN_MASK          (0x1U << CRU_CRU_GATE_CON10_CLK_MEMSUBSYS3_EN_SHIFT)         /* 0x00000008 */
#define CRU_CRU_GATE_CON10_ACLK_MEMSUBSYS_EN_SHIFT         (4U)
#define CRU_CRU_GATE_CON10_ACLK_MEMSUBSYS_EN_MASK          (0x1U << CRU_CRU_GATE_CON10_ACLK_MEMSUBSYS_EN_SHIFT)         /* 0x00000010 */
/* CRU_GATE_CON11 */
#define CRU_CRU_GATE_CON11_OFFSET                          (0x1AC)
#define CRU_CRU_GATE_CON11_ACLK_LOGIC_EN_SHIFT             (0U)
#define CRU_CRU_GATE_CON11_ACLK_LOGIC_EN_MASK              (0x1U << CRU_CRU_GATE_CON11_ACLK_LOGIC_EN_SHIFT)             /* 0x00000001 */
#define CRU_CRU_GATE_CON11_ACLK_LOGIC_NIU_EN_SHIFT         (1U)
#define CRU_CRU_GATE_CON11_ACLK_LOGIC_NIU_EN_MASK          (0x1U << CRU_CRU_GATE_CON11_ACLK_LOGIC_NIU_EN_SHIFT)         /* 0x00000002 */
#define CRU_CRU_GATE_CON11_HCLK_LOGIC_EN_SHIFT             (2U)
#define CRU_CRU_GATE_CON11_HCLK_LOGIC_EN_MASK              (0x1U << CRU_CRU_GATE_CON11_HCLK_LOGIC_EN_SHIFT)             /* 0x00000004 */
#define CRU_CRU_GATE_CON11_PCLK_LOGIC_EN_SHIFT             (3U)
#define CRU_CRU_GATE_CON11_PCLK_LOGIC_EN_MASK              (0x1U << CRU_CRU_GATE_CON11_PCLK_LOGIC_EN_SHIFT)             /* 0x00000008 */
#define CRU_CRU_GATE_CON11_PCLK_SPI2APB_NIU_EN_SHIFT       (4U)
#define CRU_CRU_GATE_CON11_PCLK_SPI2APB_NIU_EN_MASK        (0x1U << CRU_CRU_GATE_CON11_PCLK_SPI2APB_NIU_EN_SHIFT)       /* 0x00000010 */
#define CRU_CRU_GATE_CON11_PCLK_PWM_EN_SHIFT               (5U)
#define CRU_CRU_GATE_CON11_PCLK_PWM_EN_MASK                (0x1U << CRU_CRU_GATE_CON11_PCLK_PWM_EN_SHIFT)               /* 0x00000020 */
#define CRU_CRU_GATE_CON11_PCLK_SPI1_EN_SHIFT              (6U)
#define CRU_CRU_GATE_CON11_PCLK_SPI1_EN_MASK               (0x1U << CRU_CRU_GATE_CON11_PCLK_SPI1_EN_SHIFT)              /* 0x00000040 */
#define CRU_CRU_GATE_CON11_PCLK_SPI2_EN_SHIFT              (7U)
#define CRU_CRU_GATE_CON11_PCLK_SPI2_EN_MASK               (0x1U << CRU_CRU_GATE_CON11_PCLK_SPI2_EN_SHIFT)              /* 0x00000080 */
#define CRU_CRU_GATE_CON11_PCLK_SPI2APB_EN_SHIFT           (8U)
#define CRU_CRU_GATE_CON11_PCLK_SPI2APB_EN_MASK            (0x1U << CRU_CRU_GATE_CON11_PCLK_SPI2APB_EN_SHIFT)           /* 0x00000100 */
#define CRU_CRU_GATE_CON11_PCLK_MAILBOX0_EN_SHIFT          (9U)
#define CRU_CRU_GATE_CON11_PCLK_MAILBOX0_EN_MASK           (0x1U << CRU_CRU_GATE_CON11_PCLK_MAILBOX0_EN_SHIFT)          /* 0x00000200 */
#define CRU_CRU_GATE_CON11_PCLK_MAILBOX1_EN_SHIFT          (10U)
#define CRU_CRU_GATE_CON11_PCLK_MAILBOX1_EN_MASK           (0x1U << CRU_CRU_GATE_CON11_PCLK_MAILBOX1_EN_SHIFT)          /* 0x00000400 */
#define CRU_CRU_GATE_CON11_PCLK_MAILBOX2_EN_SHIFT          (11U)
#define CRU_CRU_GATE_CON11_PCLK_MAILBOX2_EN_MASK           (0x1U << CRU_CRU_GATE_CON11_PCLK_MAILBOX2_EN_SHIFT)          /* 0x00000800 */
#define CRU_CRU_GATE_CON11_PCLK_WDT0_EN_SHIFT              (12U)
#define CRU_CRU_GATE_CON11_PCLK_WDT0_EN_MASK               (0x1U << CRU_CRU_GATE_CON11_PCLK_WDT0_EN_SHIFT)              /* 0x00001000 */
#define CRU_CRU_GATE_CON11_PCLK_MIPIDSI_HOST_EN_SHIFT      (13U)
#define CRU_CRU_GATE_CON11_PCLK_MIPIDSI_HOST_EN_MASK       (0x1U << CRU_CRU_GATE_CON11_PCLK_MIPIDSI_HOST_EN_SHIFT)      /* 0x00002000 */
#define CRU_CRU_GATE_CON11_PCLK_CIF_EN_SHIFT               (14U)
#define CRU_CRU_GATE_CON11_PCLK_CIF_EN_MASK                (0x1U << CRU_CRU_GATE_CON11_PCLK_CIF_EN_SHIFT)               /* 0x00004000 */
#define CRU_CRU_GATE_CON11_PCLK_LOGIC_NIU_EN_SHIFT         (15U)
#define CRU_CRU_GATE_CON11_PCLK_LOGIC_NIU_EN_MASK          (0x1U << CRU_CRU_GATE_CON11_PCLK_LOGIC_NIU_EN_SHIFT)         /* 0x00008000 */
/* CRU_GATE_CON12 */
#define CRU_CRU_GATE_CON12_OFFSET                          (0x1B0)
#define CRU_CRU_GATE_CON12_HCLK_M4_EN_SHIFT                (0U)
#define CRU_CRU_GATE_CON12_HCLK_M4_EN_MASK                 (0x1U << CRU_CRU_GATE_CON12_HCLK_M4_EN_SHIFT)                /* 0x00000001 */
#define CRU_CRU_GATE_CON12_HCLK_USB2CTRL_EN_SHIFT          (1U)
#define CRU_CRU_GATE_CON12_HCLK_USB2CTRL_EN_MASK           (0x1U << CRU_CRU_GATE_CON12_HCLK_USB2CTRL_EN_SHIFT)          /* 0x00000002 */
#define CRU_CRU_GATE_CON12_HCLK_USB2_NIU_EN_SHIFT          (2U)
#define CRU_CRU_GATE_CON12_HCLK_USB2_NIU_EN_MASK           (0x1U << CRU_CRU_GATE_CON12_HCLK_USB2_NIU_EN_SHIFT)          /* 0x00000004 */
#define CRU_CRU_GATE_CON12_HCLK_BOOTROM_EN_SHIFT           (3U)
#define CRU_CRU_GATE_CON12_HCLK_BOOTROM_EN_MASK            (0x1U << CRU_CRU_GATE_CON12_HCLK_BOOTROM_EN_SHIFT)           /* 0x00000008 */
#define CRU_CRU_GATE_CON12_HCLK_VOP_EN_SHIFT               (4U)
#define CRU_CRU_GATE_CON12_HCLK_VOP_EN_MASK                (0x1U << CRU_CRU_GATE_CON12_HCLK_VOP_EN_SHIFT)               /* 0x00000010 */
#define CRU_CRU_GATE_CON12_HCLK_AUDPWM_EN_SHIFT            (5U)
#define CRU_CRU_GATE_CON12_HCLK_AUDPWM_EN_MASK             (0x1U << CRU_CRU_GATE_CON12_HCLK_AUDPWM_EN_SHIFT)            /* 0x00000020 */
#define CRU_CRU_GATE_CON12_HCLK_CIF_EN_SHIFT               (6U)
#define CRU_CRU_GATE_CON12_HCLK_CIF_EN_MASK                (0x1U << CRU_CRU_GATE_CON12_HCLK_CIF_EN_SHIFT)               /* 0x00000040 */
#define CRU_CRU_GATE_CON12_HCLK_LOGIC_NIU_EN_SHIFT         (7U)
#define CRU_CRU_GATE_CON12_HCLK_LOGIC_NIU_EN_MASK          (0x1U << CRU_CRU_GATE_CON12_HCLK_LOGIC_NIU_EN_SHIFT)         /* 0x00000080 */
#define CRU_CRU_GATE_CON12_HCLK_SFC_EN_SHIFT               (8U)
#define CRU_CRU_GATE_CON12_HCLK_SFC_EN_MASK                (0x1U << CRU_CRU_GATE_CON12_HCLK_SFC_EN_SHIFT)               /* 0x00000100 */
#define CRU_CRU_GATE_CON12_HCLK_XIP_SFC_EN_SHIFT           (9U)
#define CRU_CRU_GATE_CON12_HCLK_XIP_SFC_EN_MASK            (0x1U << CRU_CRU_GATE_CON12_HCLK_XIP_SFC_EN_SHIFT)           /* 0x00000200 */
#define CRU_CRU_GATE_CON12_HCLK_SDIO_EN_SHIFT              (10U)
#define CRU_CRU_GATE_CON12_HCLK_SDIO_EN_MASK               (0x1U << CRU_CRU_GATE_CON12_HCLK_SDIO_EN_SHIFT)              /* 0x00000400 */
#define CRU_CRU_GATE_CON12_HCLK_LOGIC_AHB_ARB_EN_SHIFT     (11U)
#define CRU_CRU_GATE_CON12_HCLK_LOGIC_AHB_ARB_EN_MASK      (0x1U << CRU_CRU_GATE_CON12_HCLK_LOGIC_AHB_ARB_EN_SHIFT)     /* 0x00000800 */
#define CRU_CRU_GATE_CON12_HCLK_I2S1_8CH_EN_SHIFT          (12U)
#define CRU_CRU_GATE_CON12_HCLK_I2S1_8CH_EN_MASK           (0x1U << CRU_CRU_GATE_CON12_HCLK_I2S1_8CH_EN_SHIFT)          /* 0x00001000 */
#define CRU_CRU_GATE_CON12_HCLK_CM4_NIU_EN_SHIFT           (13U)
#define CRU_CRU_GATE_CON12_HCLK_CM4_NIU_EN_MASK            (0x1U << CRU_CRU_GATE_CON12_HCLK_CM4_NIU_EN_SHIFT)           /* 0x00002000 */
#define CRU_CRU_GATE_CON12_HCLK_CM4_CORE_EN_SHIFT          (14U)
#define CRU_CRU_GATE_CON12_HCLK_CM4_CORE_EN_MASK           (0x1U << CRU_CRU_GATE_CON12_HCLK_CM4_CORE_EN_SHIFT)          /* 0x00004000 */
#define CRU_CRU_GATE_CON12_CLK_CIFOUT_EN_SHIFT             (15U)
#define CRU_CRU_GATE_CON12_CLK_CIFOUT_EN_MASK              (0x1U << CRU_CRU_GATE_CON12_CLK_CIFOUT_EN_SHIFT)             /* 0x00008000 */
/* CRU_GATE_CON13 */
#define CRU_CRU_GATE_CON13_OFFSET                          (0x1B4)
#define CRU_CRU_GATE_CON13_CLK_SPI1_EN_SHIFT               (0U)
#define CRU_CRU_GATE_CON13_CLK_SPI1_EN_MASK                (0x1U << CRU_CRU_GATE_CON13_CLK_SPI1_EN_SHIFT)               /* 0x00000001 */
#define CRU_CRU_GATE_CON13_CLK_SPI2_EN_SHIFT               (1U)
#define CRU_CRU_GATE_CON13_CLK_SPI2_EN_MASK                (0x1U << CRU_CRU_GATE_CON13_CLK_SPI2_EN_SHIFT)               /* 0x00000002 */
#define CRU_CRU_GATE_CON13_SCLK_SFC_EN_SHIFT               (4U)
#define CRU_CRU_GATE_CON13_SCLK_SFC_EN_MASK                (0x1U << CRU_CRU_GATE_CON13_SCLK_SFC_EN_SHIFT)               /* 0x00000010 */
#define CRU_CRU_GATE_CON13_HCLK_SFC1_EN_SHIFT              (5U)
#define CRU_CRU_GATE_CON13_HCLK_SFC1_EN_MASK               (0x1U << CRU_CRU_GATE_CON13_HCLK_SFC1_EN_SHIFT)              /* 0x00000020 */
#define CRU_CRU_GATE_CON13_HCLK_XIP_SFC1_EN_SHIFT          (6U)
#define CRU_CRU_GATE_CON13_HCLK_XIP_SFC1_EN_MASK           (0x1U << CRU_CRU_GATE_CON13_HCLK_XIP_SFC1_EN_SHIFT)          /* 0x00000040 */
#define CRU_CRU_GATE_CON13_CLK_SDIO_EN_SHIFT               (8U)
#define CRU_CRU_GATE_CON13_CLK_SDIO_EN_MASK                (0x1U << CRU_CRU_GATE_CON13_CLK_SDIO_EN_SHIFT)               /* 0x00000100 */
#define CRU_CRU_GATE_CON13_CLK_I2S1_8CH_EN_SHIFT           (9U)
#define CRU_CRU_GATE_CON13_CLK_I2S1_8CH_EN_MASK            (0x1U << CRU_CRU_GATE_CON13_CLK_I2S1_8CH_EN_SHIFT)           /* 0x00000200 */
#define CRU_CRU_GATE_CON13_CLK_I2S1_8CH_FRAC_EN_SHIFT      (10U)
#define CRU_CRU_GATE_CON13_CLK_I2S1_8CH_FRAC_EN_MASK       (0x1U << CRU_CRU_GATE_CON13_CLK_I2S1_8CH_FRAC_EN_SHIFT)      /* 0x00000400 */
#define CRU_CRU_GATE_CON13_MCLK_I2S1_8CH_EN_SHIFT          (11U)
#define CRU_CRU_GATE_CON13_MCLK_I2S1_8CH_EN_MASK           (0x1U << CRU_CRU_GATE_CON13_MCLK_I2S1_8CH_EN_SHIFT)          /* 0x00000800 */
#define CRU_CRU_GATE_CON13_I2S1_MCLKOUT_EN_SHIFT           (12U)
#define CRU_CRU_GATE_CON13_I2S1_MCLKOUT_EN_MASK            (0x1U << CRU_CRU_GATE_CON13_I2S1_MCLKOUT_EN_SHIFT)           /* 0x00001000 */
#define CRU_CRU_GATE_CON13_CLK_PWM_EN_SHIFT                (13U)
#define CRU_CRU_GATE_CON13_CLK_PWM_EN_MASK                 (0x1U << CRU_CRU_GATE_CON13_CLK_PWM_EN_SHIFT)                /* 0x00002000 */
#define CRU_CRU_GATE_CON13_CLK_AUDPWM_DF_EN_SHIFT          (14U)
#define CRU_CRU_GATE_CON13_CLK_AUDPWM_DF_EN_MASK           (0x1U << CRU_CRU_GATE_CON13_CLK_AUDPWM_DF_EN_SHIFT)          /* 0x00004000 */
#define CRU_CRU_GATE_CON13_ACLK_CIF_EN_SHIFT               (15U)
#define CRU_CRU_GATE_CON13_ACLK_CIF_EN_MASK                (0x1U << CRU_CRU_GATE_CON13_ACLK_CIF_EN_SHIFT)               /* 0x00008000 */
/* CRU_GATE_CON14 */
#define CRU_CRU_GATE_CON14_OFFSET                          (0x1B8)
#define CRU_CRU_GATE_CON14_CLK_AUDPWM_FRAC_EN_SHIFT        (0U)
#define CRU_CRU_GATE_CON14_CLK_AUDPWM_FRAC_EN_MASK         (0x1U << CRU_CRU_GATE_CON14_CLK_AUDPWM_FRAC_EN_SHIFT)        /* 0x00000001 */
#define CRU_CRU_GATE_CON14_ACLK_CIF_NIU_EN_SHIFT           (1U)
#define CRU_CRU_GATE_CON14_ACLK_CIF_NIU_EN_MASK            (0x1U << CRU_CRU_GATE_CON14_ACLK_CIF_NIU_EN_SHIFT)           /* 0x00000002 */
#define CRU_CRU_GATE_CON14_SCLK_SFC1_EN_SHIFT              (4U)
#define CRU_CRU_GATE_CON14_SCLK_SFC1_EN_MASK               (0x1U << CRU_CRU_GATE_CON14_SCLK_SFC1_EN_SHIFT)              /* 0x00000010 */
#define CRU_CRU_GATE_CON14_CLK_USB2_ADP_EN_SHIFT           (5U)
#define CRU_CRU_GATE_CON14_CLK_USB2_ADP_EN_MASK            (0x1U << CRU_CRU_GATE_CON14_CLK_USB2_ADP_EN_SHIFT)           /* 0x00000020 */
#define CRU_CRU_GATE_CON14_CLK_USB2PHY_REF_FRAC_EN_SHIFT   (6U)
#define CRU_CRU_GATE_CON14_CLK_USB2PHY_REF_FRAC_EN_MASK    (0x1U << CRU_CRU_GATE_CON14_CLK_USB2PHY_REF_FRAC_EN_SHIFT)   /* 0x00000040 */
#define CRU_CRU_GATE_CON14_CLK_DPHY_REF_FRAC_EN_SHIFT      (7U)
#define CRU_CRU_GATE_CON14_CLK_DPHY_REF_FRAC_EN_MASK       (0x1U << CRU_CRU_GATE_CON14_CLK_DPHY_REF_FRAC_EN_SHIFT)      /* 0x00000080 */
#define CRU_CRU_GATE_CON14_STCLK_M4_EN_SHIFT               (8U)
#define CRU_CRU_GATE_CON14_STCLK_M4_EN_MASK                (0x1U << CRU_CRU_GATE_CON14_STCLK_M4_EN_SHIFT)               /* 0x00000100 */
#define CRU_CRU_GATE_CON14_CLK_KEY_EN_SHIFT                (9U)
#define CRU_CRU_GATE_CON14_CLK_KEY_EN_MASK                 (0x1U << CRU_CRU_GATE_CON14_CLK_KEY_EN_SHIFT)                /* 0x00000200 */
#define CRU_CRU_GATE_CON14_PCLK_KEY_EN_SHIFT               (10U)
#define CRU_CRU_GATE_CON14_PCLK_KEY_EN_MASK                (0x1U << CRU_CRU_GATE_CON14_PCLK_KEY_EN_SHIFT)               /* 0x00000400 */
#define CRU_CRU_GATE_CON14_CLK_USB2CTRL_EN_SHIFT           (13U)
#define CRU_CRU_GATE_CON14_CLK_USB2CTRL_EN_MASK            (0x1U << CRU_CRU_GATE_CON14_CLK_USB2CTRL_EN_SHIFT)           /* 0x00002000 */
#define CRU_CRU_GATE_CON14_CLK_BT32K_EN_SHIFT              (15U)
#define CRU_CRU_GATE_CON14_CLK_BT32K_EN_MASK               (0x1U << CRU_CRU_GATE_CON14_CLK_BT32K_EN_SHIFT)              /* 0x00008000 */
/* CRU_SOFTRST_CON00 */
#define CRU_CRU_SOFTRST_CON00_OFFSET                       (0x200)
#define CRU_CRU_SOFTRST_CON00_DRESETN_DSP_SHIFT            (0U)
#define CRU_CRU_SOFTRST_CON00_DRESETN_DSP_MASK             (0x1U << CRU_CRU_SOFTRST_CON00_DRESETN_DSP_SHIFT)            /* 0x00000001 */
#define CRU_CRU_SOFTRST_CON00_BRESETN_DSP_SHIFT            (1U)
#define CRU_CRU_SOFTRST_CON00_BRESETN_DSP_MASK             (0x1U << CRU_CRU_SOFTRST_CON00_BRESETN_DSP_SHIFT)            /* 0x00000002 */
#define CRU_CRU_SOFTRST_CON00_ARESETN_DSP_NIU_SHIFT        (2U)
#define CRU_CRU_SOFTRST_CON00_ARESETN_DSP_NIU_MASK         (0x1U << CRU_CRU_SOFTRST_CON00_ARESETN_DSP_NIU_SHIFT)        /* 0x00000004 */
#define CRU_CRU_SOFTRST_CON00_PRESETN_DSP_NIU_SHIFT        (4U)
#define CRU_CRU_SOFTRST_CON00_PRESETN_DSP_NIU_MASK         (0x1U << CRU_CRU_SOFTRST_CON00_PRESETN_DSP_NIU_SHIFT)        /* 0x00000010 */
#define CRU_CRU_SOFTRST_CON00_PRESETN_DSP_GRF_SHIFT        (5U)
#define CRU_CRU_SOFTRST_CON00_PRESETN_DSP_GRF_MASK         (0x1U << CRU_CRU_SOFTRST_CON00_PRESETN_DSP_GRF_SHIFT)        /* 0x00000020 */
#define CRU_CRU_SOFTRST_CON00_PRESETN_WDT1_SHIFT           (6U)
#define CRU_CRU_SOFTRST_CON00_PRESETN_WDT1_MASK            (0x1U << CRU_CRU_SOFTRST_CON00_PRESETN_WDT1_SHIFT)           /* 0x00000040 */
/* CRU_SOFTRST_CON01 */
#define CRU_CRU_SOFTRST_CON01_OFFSET                       (0x204)
#define CRU_CRU_SOFTRST_CON01_SRESETN_SHRM_SHIFT           (0U)
#define CRU_CRU_SOFTRST_CON01_SRESETN_SHRM_MASK            (0x1U << CRU_CRU_SOFTRST_CON01_SRESETN_SHRM_SHIFT)           /* 0x00000001 */
#define CRU_CRU_SOFTRST_CON01_ARESETN_SHRM_NIU_SHIFT       (1U)
#define CRU_CRU_SOFTRST_CON01_ARESETN_SHRM_NIU_MASK        (0x1U << CRU_CRU_SOFTRST_CON01_ARESETN_SHRM_NIU_SHIFT)       /* 0x00000002 */
#define CRU_CRU_SOFTRST_CON01_PRESETN_SHRM_SHIFT           (2U)
#define CRU_CRU_SOFTRST_CON01_PRESETN_SHRM_MASK            (0x1U << CRU_CRU_SOFTRST_CON01_PRESETN_SHRM_SHIFT)           /* 0x00000004 */
#define CRU_CRU_SOFTRST_CON01_PRESETN_SHRM_NIU_SHIFT       (3U)
#define CRU_CRU_SOFTRST_CON01_PRESETN_SHRM_NIU_MASK        (0x1U << CRU_CRU_SOFTRST_CON01_PRESETN_SHRM_NIU_SHIFT)       /* 0x00000008 */
/* CRU_SOFTRST_CON02 */
#define CRU_CRU_SOFTRST_CON02_OFFSET                       (0x208)
#define CRU_CRU_SOFTRST_CON02_PRESETN_UART0_SHIFT          (0U)
#define CRU_CRU_SOFTRST_CON02_PRESETN_UART0_MASK           (0x1U << CRU_CRU_SOFTRST_CON02_PRESETN_UART0_SHIFT)          /* 0x00000001 */
#define CRU_CRU_SOFTRST_CON02_PRESETN_UART1_SHIFT          (1U)
#define CRU_CRU_SOFTRST_CON02_PRESETN_UART1_MASK           (0x1U << CRU_CRU_SOFTRST_CON02_PRESETN_UART1_SHIFT)          /* 0x00000002 */
#define CRU_CRU_SOFTRST_CON02_PRESETN_UART2_SHIFT          (3U)
#define CRU_CRU_SOFTRST_CON02_PRESETN_UART2_MASK           (0x1U << CRU_CRU_SOFTRST_CON02_PRESETN_UART2_SHIFT)          /* 0x00000008 */
#define CRU_CRU_SOFTRST_CON02_SRESETN_UART0_SHIFT          (6U)
#define CRU_CRU_SOFTRST_CON02_SRESETN_UART0_MASK           (0x1U << CRU_CRU_SOFTRST_CON02_SRESETN_UART0_SHIFT)          /* 0x00000040 */
#define CRU_CRU_SOFTRST_CON02_SRESETN_UART1_SHIFT          (9U)
#define CRU_CRU_SOFTRST_CON02_SRESETN_UART1_MASK           (0x1U << CRU_CRU_SOFTRST_CON02_SRESETN_UART1_SHIFT)          /* 0x00000200 */
#define CRU_CRU_SOFTRST_CON02_SRESETN_UART2_SHIFT          (14U)
#define CRU_CRU_SOFTRST_CON02_SRESETN_UART2_MASK           (0x1U << CRU_CRU_SOFTRST_CON02_SRESETN_UART2_SHIFT)          /* 0x00004000 */
/* CRU_SOFTRST_CON04 */
#define CRU_CRU_SOFTRST_CON04_OFFSET                       (0x210)
#define CRU_CRU_SOFTRST_CON04_PRESETN_TIMER_SHIFT          (0U)
#define CRU_CRU_SOFTRST_CON04_PRESETN_TIMER_MASK           (0x1U << CRU_CRU_SOFTRST_CON04_PRESETN_TIMER_SHIFT)          /* 0x00000001 */
#define CRU_CRU_SOFTRST_CON04_RESETN_TIMER0_SHIFT          (1U)
#define CRU_CRU_SOFTRST_CON04_RESETN_TIMER0_MASK           (0x1U << CRU_CRU_SOFTRST_CON04_RESETN_TIMER0_SHIFT)          /* 0x00000002 */
#define CRU_CRU_SOFTRST_CON04_RESETN_TIMER1_SHIFT          (2U)
#define CRU_CRU_SOFTRST_CON04_RESETN_TIMER1_MASK           (0x1U << CRU_CRU_SOFTRST_CON04_RESETN_TIMER1_SHIFT)          /* 0x00000004 */
#define CRU_CRU_SOFTRST_CON04_RESETN_TIMER2_SHIFT          (3U)
#define CRU_CRU_SOFTRST_CON04_RESETN_TIMER2_MASK           (0x1U << CRU_CRU_SOFTRST_CON04_RESETN_TIMER2_SHIFT)          /* 0x00000008 */
#define CRU_CRU_SOFTRST_CON04_RESETN_TIMER3_SHIFT          (4U)
#define CRU_CRU_SOFTRST_CON04_RESETN_TIMER3_MASK           (0x1U << CRU_CRU_SOFTRST_CON04_RESETN_TIMER3_SHIFT)          /* 0x00000010 */
#define CRU_CRU_SOFTRST_CON04_RESETN_TIMER4_SHIFT          (5U)
#define CRU_CRU_SOFTRST_CON04_RESETN_TIMER4_MASK           (0x1U << CRU_CRU_SOFTRST_CON04_RESETN_TIMER4_SHIFT)          /* 0x00000020 */
#define CRU_CRU_SOFTRST_CON04_RESETN_TIMER5_SHIFT          (6U)
#define CRU_CRU_SOFTRST_CON04_RESETN_TIMER5_MASK           (0x1U << CRU_CRU_SOFTRST_CON04_RESETN_TIMER5_SHIFT)          /* 0x00000040 */
/* CRU_SOFTRST_CON05 */
#define CRU_CRU_SOFTRST_CON05_OFFSET                       (0x214)
#define CRU_CRU_SOFTRST_CON05_PRESETN_I2C2APB_NIU_SHIFT    (0U)
#define CRU_CRU_SOFTRST_CON05_PRESETN_I2C2APB_NIU_MASK     (0x1U << CRU_CRU_SOFTRST_CON05_PRESETN_I2C2APB_NIU_SHIFT)    /* 0x00000001 */
#define CRU_CRU_SOFTRST_CON05_PRESETN_I2C0_SHIFT           (1U)
#define CRU_CRU_SOFTRST_CON05_PRESETN_I2C0_MASK            (0x1U << CRU_CRU_SOFTRST_CON05_PRESETN_I2C0_SHIFT)           /* 0x00000002 */
#define CRU_CRU_SOFTRST_CON05_PRESETN_I2C1_SHIFT           (2U)
#define CRU_CRU_SOFTRST_CON05_PRESETN_I2C1_MASK            (0x1U << CRU_CRU_SOFTRST_CON05_PRESETN_I2C1_SHIFT)           /* 0x00000004 */
#define CRU_CRU_SOFTRST_CON05_PRESETN_I2C2_SHIFT           (3U)
#define CRU_CRU_SOFTRST_CON05_PRESETN_I2C2_MASK            (0x1U << CRU_CRU_SOFTRST_CON05_PRESETN_I2C2_SHIFT)           /* 0x00000008 */
#define CRU_CRU_SOFTRST_CON05_PRESETN_I2C2APB_SHIFT        (4U)
#define CRU_CRU_SOFTRST_CON05_PRESETN_I2C2APB_MASK         (0x1U << CRU_CRU_SOFTRST_CON05_PRESETN_I2C2APB_SHIFT)        /* 0x00000010 */
#define CRU_CRU_SOFTRST_CON05_RESETN_I2C0_SHIFT            (5U)
#define CRU_CRU_SOFTRST_CON05_RESETN_I2C0_MASK             (0x1U << CRU_CRU_SOFTRST_CON05_RESETN_I2C0_SHIFT)            /* 0x00000020 */
#define CRU_CRU_SOFTRST_CON05_RESETN_I2C1_SHIFT            (6U)
#define CRU_CRU_SOFTRST_CON05_RESETN_I2C1_MASK             (0x1U << CRU_CRU_SOFTRST_CON05_RESETN_I2C1_SHIFT)            /* 0x00000040 */
#define CRU_CRU_SOFTRST_CON05_RESETN_I2C2_SHIFT            (7U)
#define CRU_CRU_SOFTRST_CON05_RESETN_I2C2_MASK             (0x1U << CRU_CRU_SOFTRST_CON05_RESETN_I2C2_SHIFT)            /* 0x00000080 */
#define CRU_CRU_SOFTRST_CON05_RESETN_CODEC_I2S_OUT_SHIFT   (12U)
#define CRU_CRU_SOFTRST_CON05_RESETN_CODEC_I2S_OUT_MASK    (0x1U << CRU_CRU_SOFTRST_CON05_RESETN_CODEC_I2S_OUT_SHIFT)   /* 0x00001000 */
#define CRU_CRU_SOFTRST_CON05_PRESETN_ACDC_DIG_SHIFT       (14U)
#define CRU_CRU_SOFTRST_CON05_PRESETN_ACDC_DIG_MASK        (0x1U << CRU_CRU_SOFTRST_CON05_PRESETN_ACDC_DIG_SHIFT)       /* 0x00004000 */
#define CRU_CRU_SOFTRST_CON05_ARESETN_DMAC_CORE_SHIFT      (15U)
#define CRU_CRU_SOFTRST_CON05_ARESETN_DMAC_CORE_MASK       (0x1U << CRU_CRU_SOFTRST_CON05_ARESETN_DMAC_CORE_SHIFT)      /* 0x00008000 */
/* CRU_SOFTRST_CON06 */
#define CRU_CRU_SOFTRST_CON06_OFFSET                       (0x218)
#define CRU_CRU_SOFTRST_CON06_HRESETN_PDM0_SHIFT           (0U)
#define CRU_CRU_SOFTRST_CON06_HRESETN_PDM0_MASK            (0x1U << CRU_CRU_SOFTRST_CON06_HRESETN_PDM0_SHIFT)           /* 0x00000001 */
#define CRU_CRU_SOFTRST_CON06_HRESETN_I2S_8CH_SHIFT        (2U)
#define CRU_CRU_SOFTRST_CON06_HRESETN_I2S_8CH_MASK         (0x1U << CRU_CRU_SOFTRST_CON06_HRESETN_I2S_8CH_SHIFT)        /* 0x00000004 */
#define CRU_CRU_SOFTRST_CON06_HRESETN_VAD_SHIFT            (3U)
#define CRU_CRU_SOFTRST_CON06_HRESETN_VAD_MASK             (0x1U << CRU_CRU_SOFTRST_CON06_HRESETN_VAD_SHIFT)            /* 0x00000008 */
#define CRU_CRU_SOFTRST_CON06_HRESETN_AUDIO_NIU_SHIFT      (4U)
#define CRU_CRU_SOFTRST_CON06_HRESETN_AUDIO_NIU_MASK       (0x1U << CRU_CRU_SOFTRST_CON06_HRESETN_AUDIO_NIU_SHIFT)      /* 0x00000010 */
#define CRU_CRU_SOFTRST_CON06_HRESETN_AUDIO_AHB_ARB_SHIFT  (5U)
#define CRU_CRU_SOFTRST_CON06_HRESETN_AUDIO_AHB_ARB_MASK   (0x1U << CRU_CRU_SOFTRST_CON06_HRESETN_AUDIO_AHB_ARB_SHIFT)  /* 0x00000020 */
#define CRU_CRU_SOFTRST_CON06_PRESETN_AUDIO_NIU_SHIFT      (6U)
#define CRU_CRU_SOFTRST_CON06_PRESETN_AUDIO_NIU_MASK       (0x1U << CRU_CRU_SOFTRST_CON06_PRESETN_AUDIO_NIU_SHIFT)      /* 0x00000040 */
#define CRU_CRU_SOFTRST_CON06_MRESETN_PDM0_SHIFT           (7U)
#define CRU_CRU_SOFTRST_CON06_MRESETN_PDM0_MASK            (0x1U << CRU_CRU_SOFTRST_CON06_MRESETN_PDM0_SHIFT)           /* 0x00000080 */
#define CRU_CRU_SOFTRST_CON06_MRESETN_I2S8CH_SHIFT         (12U)
#define CRU_CRU_SOFTRST_CON06_MRESETN_I2S8CH_MASK          (0x1U << CRU_CRU_SOFTRST_CON06_MRESETN_I2S8CH_SHIFT)         /* 0x00001000 */
#define CRU_CRU_SOFTRST_CON06_ARESETN_DMAC_NIU_SHIFT       (15U)
#define CRU_CRU_SOFTRST_CON06_ARESETN_DMAC_NIU_MASK        (0x1U << CRU_CRU_SOFTRST_CON06_ARESETN_DMAC_NIU_SHIFT)       /* 0x00008000 */
/* CRU_SOFTRST_CON07 */
#define CRU_CRU_SOFTRST_CON07_OFFSET                       (0x21C)
#define CRU_CRU_SOFTRST_CON07_ARESETN_VOP_SHIFT            (0U)
#define CRU_CRU_SOFTRST_CON07_ARESETN_VOP_MASK             (0x1U << CRU_CRU_SOFTRST_CON07_ARESETN_VOP_SHIFT)            /* 0x00000001 */
#define CRU_CRU_SOFTRST_CON07_DRESETN_VOP_S_SHIFT          (2U)
#define CRU_CRU_SOFTRST_CON07_DRESETN_VOP_S_MASK           (0x1U << CRU_CRU_SOFTRST_CON07_DRESETN_VOP_S_SHIFT)          /* 0x00000004 */
#define CRU_CRU_SOFTRST_CON07_ARESETN_VOP_NIU_SHIFT        (3U)
#define CRU_CRU_SOFTRST_CON07_ARESETN_VOP_NIU_MASK         (0x1U << CRU_CRU_SOFTRST_CON07_ARESETN_VOP_NIU_SHIFT)        /* 0x00000008 */
/* CRU_SOFTRST_CON08 */
#define CRU_CRU_SOFTRST_CON08_OFFSET                       (0x220)
#define CRU_CRU_SOFTRST_CON08_PRESETN_GPIO0_SHIFT          (0U)
#define CRU_CRU_SOFTRST_CON08_PRESETN_GPIO0_MASK           (0x1U << CRU_CRU_SOFTRST_CON08_PRESETN_GPIO0_SHIFT)          /* 0x00000001 */
#define CRU_CRU_SOFTRST_CON08_PRESETN_GPIO1_SHIFT          (1U)
#define CRU_CRU_SOFTRST_CON08_PRESETN_GPIO1_MASK           (0x1U << CRU_CRU_SOFTRST_CON08_PRESETN_GPIO1_SHIFT)          /* 0x00000002 */
#define CRU_CRU_SOFTRST_CON08_RESETN_GPIO_DB0_SHIFT        (3U)
#define CRU_CRU_SOFTRST_CON08_RESETN_GPIO_DB0_MASK         (0x1U << CRU_CRU_SOFTRST_CON08_RESETN_GPIO_DB0_SHIFT)        /* 0x00000008 */
#define CRU_CRU_SOFTRST_CON08_RESETN_GPIO_DB1_SHIFT        (4U)
#define CRU_CRU_SOFTRST_CON08_RESETN_GPIO_DB1_MASK         (0x1U << CRU_CRU_SOFTRST_CON08_RESETN_GPIO_DB1_SHIFT)        /* 0x00000010 */
/* CRU_SOFTRST_CON09 */
#define CRU_CRU_SOFTRST_CON09_OFFSET                       (0x224)
#define CRU_CRU_SOFTRST_CON09_HRESETN_ALIVE_NIU_SHIFT      (2U)
#define CRU_CRU_SOFTRST_CON09_HRESETN_ALIVE_NIU_MASK       (0x1U << CRU_CRU_SOFTRST_CON09_HRESETN_ALIVE_NIU_SHIFT)      /* 0x00000004 */
#define CRU_CRU_SOFTRST_CON09_HRESETN_ALIVEAHB_ARB_SHIFT   (3U)
#define CRU_CRU_SOFTRST_CON09_HRESETN_ALIVEAHB_ARB_MASK    (0x1U << CRU_CRU_SOFTRST_CON09_HRESETN_ALIVEAHB_ARB_SHIFT)   /* 0x00000008 */
#define CRU_CRU_SOFTRST_CON09_HRESETN_INTC0_SHIFT          (4U)
#define CRU_CRU_SOFTRST_CON09_HRESETN_INTC0_MASK           (0x1U << CRU_CRU_SOFTRST_CON09_HRESETN_INTC0_SHIFT)          /* 0x00000010 */
#define CRU_CRU_SOFTRST_CON09_HRESETN_INTC1_SHIFT          (5U)
#define CRU_CRU_SOFTRST_CON09_HRESETN_INTC1_MASK           (0x1U << CRU_CRU_SOFTRST_CON09_HRESETN_INTC1_SHIFT)          /* 0x00000020 */
#define CRU_CRU_SOFTRST_CON09_PRESETN_CRU_SHIFT            (8U)
#define CRU_CRU_SOFTRST_CON09_PRESETN_CRU_MASK             (0x1U << CRU_CRU_SOFTRST_CON09_PRESETN_CRU_SHIFT)            /* 0x00000100 */
#define CRU_CRU_SOFTRST_CON09_PRESETN_ALIVE_NIU_SHIFT      (9U)
#define CRU_CRU_SOFTRST_CON09_PRESETN_ALIVE_NIU_MASK       (0x1U << CRU_CRU_SOFTRST_CON09_PRESETN_ALIVE_NIU_SHIFT)      /* 0x00000200 */
#define CRU_CRU_SOFTRST_CON09_PRESETN_PMU_SHIFT            (10U)
#define CRU_CRU_SOFTRST_CON09_PRESETN_PMU_MASK             (0x1U << CRU_CRU_SOFTRST_CON09_PRESETN_PMU_SHIFT)            /* 0x00000400 */
#define CRU_CRU_SOFTRST_CON09_PRESETN_GRF_SHIFT            (11U)
#define CRU_CRU_SOFTRST_CON09_PRESETN_GRF_MASK             (0x1U << CRU_CRU_SOFTRST_CON09_PRESETN_GRF_SHIFT)            /* 0x00000800 */
#define CRU_CRU_SOFTRST_CON09_RESETN_PMU_SHIFT             (12U)
#define CRU_CRU_SOFTRST_CON09_RESETN_PMU_MASK              (0x1U << CRU_CRU_SOFTRST_CON09_RESETN_PMU_SHIFT)             /* 0x00001000 */
#define CRU_CRU_SOFTRST_CON09_RESETN_PVTM_SHIFT            (14U)
#define CRU_CRU_SOFTRST_CON09_RESETN_PVTM_MASK             (0x1U << CRU_CRU_SOFTRST_CON09_RESETN_PVTM_SHIFT)            /* 0x00004000 */
#define CRU_CRU_SOFTRST_CON09_RESETN_PDM_SAMP_SHIFT        (15U)
#define CRU_CRU_SOFTRST_CON09_RESETN_PDM_SAMP_MASK         (0x1U << CRU_CRU_SOFTRST_CON09_RESETN_PDM_SAMP_SHIFT)        /* 0x00008000 */
/* CRU_SOFTRST_CON11 */
#define CRU_CRU_SOFTRST_CON11_OFFSET                       (0x22C)
#define CRU_CRU_SOFTRST_CON11_ARESETN_LOGIC_NIU_SHIFT      (1U)
#define CRU_CRU_SOFTRST_CON11_ARESETN_LOGIC_NIU_MASK       (0x1U << CRU_CRU_SOFTRST_CON11_ARESETN_LOGIC_NIU_SHIFT)      /* 0x00000002 */
#define CRU_CRU_SOFTRST_CON11_PRESETN_SPI2APB_NIU_SHIFT    (4U)
#define CRU_CRU_SOFTRST_CON11_PRESETN_SPI2APB_NIU_MASK     (0x1U << CRU_CRU_SOFTRST_CON11_PRESETN_SPI2APB_NIU_SHIFT)    /* 0x00000010 */
#define CRU_CRU_SOFTRST_CON11_PRESETN_PWM_SHIFT            (5U)
#define CRU_CRU_SOFTRST_CON11_PRESETN_PWM_MASK             (0x1U << CRU_CRU_SOFTRST_CON11_PRESETN_PWM_SHIFT)            /* 0x00000020 */
#define CRU_CRU_SOFTRST_CON11_PRESETN_SPI1_SHIFT           (6U)
#define CRU_CRU_SOFTRST_CON11_PRESETN_SPI1_MASK            (0x1U << CRU_CRU_SOFTRST_CON11_PRESETN_SPI1_SHIFT)           /* 0x00000040 */
#define CRU_CRU_SOFTRST_CON11_PRESETN_SPI2_SHIFT           (7U)
#define CRU_CRU_SOFTRST_CON11_PRESETN_SPI2_MASK            (0x1U << CRU_CRU_SOFTRST_CON11_PRESETN_SPI2_SHIFT)           /* 0x00000080 */
#define CRU_CRU_SOFTRST_CON11_PRESETN_SPI2APB_SHIFT        (8U)
#define CRU_CRU_SOFTRST_CON11_PRESETN_SPI2APB_MASK         (0x1U << CRU_CRU_SOFTRST_CON11_PRESETN_SPI2APB_SHIFT)        /* 0x00000100 */
#define CRU_CRU_SOFTRST_CON11_PRESETN_MAILBOX0_SHIFT       (9U)
#define CRU_CRU_SOFTRST_CON11_PRESETN_MAILBOX0_MASK        (0x1U << CRU_CRU_SOFTRST_CON11_PRESETN_MAILBOX0_SHIFT)       /* 0x00000200 */
#define CRU_CRU_SOFTRST_CON11_PRESETN_MAILBOX1_SHIFT       (10U)
#define CRU_CRU_SOFTRST_CON11_PRESETN_MAILBOX1_MASK        (0x1U << CRU_CRU_SOFTRST_CON11_PRESETN_MAILBOX1_SHIFT)       /* 0x00000400 */
#define CRU_CRU_SOFTRST_CON11_PRESETN_MAILBOX2_SHIFT       (11U)
#define CRU_CRU_SOFTRST_CON11_PRESETN_MAILBOX2_MASK        (0x1U << CRU_CRU_SOFTRST_CON11_PRESETN_MAILBOX2_SHIFT)       /* 0x00000800 */
#define CRU_CRU_SOFTRST_CON11_PRESETN_WDT0_SHIFT           (12U)
#define CRU_CRU_SOFTRST_CON11_PRESETN_WDT0_MASK            (0x1U << CRU_CRU_SOFTRST_CON11_PRESETN_WDT0_SHIFT)           /* 0x00001000 */
#define CRU_CRU_SOFTRST_CON11_PRESETN_MIPIDSI_HOST_SHIFT   (13U)
#define CRU_CRU_SOFTRST_CON11_PRESETN_MIPIDSI_HOST_MASK    (0x1U << CRU_CRU_SOFTRST_CON11_PRESETN_MIPIDSI_HOST_SHIFT)   /* 0x00002000 */
#define CRU_CRU_SOFTRST_CON11_PRESETN_CIF_SHIFT            (14U)
#define CRU_CRU_SOFTRST_CON11_PRESETN_CIF_MASK             (0x1U << CRU_CRU_SOFTRST_CON11_PRESETN_CIF_SHIFT)            /* 0x00004000 */
#define CRU_CRU_SOFTRST_CON11_PRESETN_LOGIC_NIU_SHIFT      (15U)
#define CRU_CRU_SOFTRST_CON11_PRESETN_LOGIC_NIU_MASK       (0x1U << CRU_CRU_SOFTRST_CON11_PRESETN_LOGIC_NIU_SHIFT)      /* 0x00008000 */
/* CRU_SOFTRST_CON12 */
#define CRU_CRU_SOFTRST_CON12_OFFSET                       (0x230)
#define CRU_CRU_SOFTRST_CON12_HRESETN_USB2CTRL_SHIFT       (1U)
#define CRU_CRU_SOFTRST_CON12_HRESETN_USB2CTRL_MASK        (0x1U << CRU_CRU_SOFTRST_CON12_HRESETN_USB2CTRL_SHIFT)       /* 0x00000002 */
#define CRU_CRU_SOFTRST_CON12_HRESETN_USB2_NIU_SHIFT       (2U)
#define CRU_CRU_SOFTRST_CON12_HRESETN_USB2_NIU_MASK        (0x1U << CRU_CRU_SOFTRST_CON12_HRESETN_USB2_NIU_SHIFT)       /* 0x00000004 */
#define CRU_CRU_SOFTRST_CON12_HRESETN_BOOTROM_SHIFT        (3U)
#define CRU_CRU_SOFTRST_CON12_HRESETN_BOOTROM_MASK         (0x1U << CRU_CRU_SOFTRST_CON12_HRESETN_BOOTROM_SHIFT)        /* 0x00000008 */
#define CRU_CRU_SOFTRST_CON12_HRESETN_VOP_SHIFT            (4U)
#define CRU_CRU_SOFTRST_CON12_HRESETN_VOP_MASK             (0x1U << CRU_CRU_SOFTRST_CON12_HRESETN_VOP_SHIFT)            /* 0x00000010 */
#define CRU_CRU_SOFTRST_CON12_HRESETN_AUDPWM_SHIFT         (5U)
#define CRU_CRU_SOFTRST_CON12_HRESETN_AUDPWM_MASK          (0x1U << CRU_CRU_SOFTRST_CON12_HRESETN_AUDPWM_SHIFT)         /* 0x00000020 */
#define CRU_CRU_SOFTRST_CON12_HRESETN_CIF_SHIFT            (6U)
#define CRU_CRU_SOFTRST_CON12_HRESETN_CIF_MASK             (0x1U << CRU_CRU_SOFTRST_CON12_HRESETN_CIF_SHIFT)            /* 0x00000040 */
#define CRU_CRU_SOFTRST_CON12_HRESETN_LOGIC_NIU_SHIFT      (7U)
#define CRU_CRU_SOFTRST_CON12_HRESETN_LOGIC_NIU_MASK       (0x1U << CRU_CRU_SOFTRST_CON12_HRESETN_LOGIC_NIU_SHIFT)      /* 0x00000080 */
#define CRU_CRU_SOFTRST_CON12_HRESETN_SFC_SHIFT            (8U)
#define CRU_CRU_SOFTRST_CON12_HRESETN_SFC_MASK             (0x1U << CRU_CRU_SOFTRST_CON12_HRESETN_SFC_SHIFT)            /* 0x00000100 */
#define CRU_CRU_SOFTRST_CON12_HRESETN_XIP_SFC_SHIFT        (9U)
#define CRU_CRU_SOFTRST_CON12_HRESETN_XIP_SFC_MASK         (0x1U << CRU_CRU_SOFTRST_CON12_HRESETN_XIP_SFC_SHIFT)        /* 0x00000200 */
#define CRU_CRU_SOFTRST_CON12_HRESETN_SDIO_SHIFT           (10U)
#define CRU_CRU_SOFTRST_CON12_HRESETN_SDIO_MASK            (0x1U << CRU_CRU_SOFTRST_CON12_HRESETN_SDIO_SHIFT)           /* 0x00000400 */
#define CRU_CRU_SOFTRST_CON12_HRESETN_LOGIC_AHB_ARB_SHIFT  (11U)
#define CRU_CRU_SOFTRST_CON12_HRESETN_LOGIC_AHB_ARB_MASK   (0x1U << CRU_CRU_SOFTRST_CON12_HRESETN_LOGIC_AHB_ARB_SHIFT)  /* 0x00000800 */
#define CRU_CRU_SOFTRST_CON12_HRESETN_I2S1_8CH_SHIFT       (12U)
#define CRU_CRU_SOFTRST_CON12_HRESETN_I2S1_8CH_MASK        (0x1U << CRU_CRU_SOFTRST_CON12_HRESETN_I2S1_8CH_SHIFT)       /* 0x00001000 */
#define CRU_CRU_SOFTRST_CON12_HRESETN_CM4_NIU_SHIFT        (13U)
#define CRU_CRU_SOFTRST_CON12_HRESETN_CM4_NIU_MASK         (0x1U << CRU_CRU_SOFTRST_CON12_HRESETN_CM4_NIU_SHIFT)        /* 0x00002000 */
#define CRU_CRU_SOFTRST_CON12_HRESETN_CM4_CORE_SHIFT       (14U)
#define CRU_CRU_SOFTRST_CON12_HRESETN_CM4_CORE_MASK        (0x1U << CRU_CRU_SOFTRST_CON12_HRESETN_CM4_CORE_SHIFT)       /* 0x00004000 */
/* CRU_SOFTRST_CON13 */
#define CRU_CRU_SOFTRST_CON13_OFFSET                       (0x234)
#define CRU_CRU_SOFTRST_CON13_RESETN_SPI1_SHIFT            (0U)
#define CRU_CRU_SOFTRST_CON13_RESETN_SPI1_MASK             (0x1U << CRU_CRU_SOFTRST_CON13_RESETN_SPI1_SHIFT)            /* 0x00000001 */
#define CRU_CRU_SOFTRST_CON13_RESETN_SPI2_SHIFT            (1U)
#define CRU_CRU_SOFTRST_CON13_RESETN_SPI2_MASK             (0x1U << CRU_CRU_SOFTRST_CON13_RESETN_SPI2_SHIFT)            /* 0x00000002 */
#define CRU_CRU_SOFTRST_CON13_SRESETN_SFC_SHIFT            (4U)
#define CRU_CRU_SOFTRST_CON13_SRESETN_SFC_MASK             (0x1U << CRU_CRU_SOFTRST_CON13_SRESETN_SFC_SHIFT)            /* 0x00000010 */
#define CRU_CRU_SOFTRST_CON13_HRESETN_SFC1_SHIFT           (5U)
#define CRU_CRU_SOFTRST_CON13_HRESETN_SFC1_MASK            (0x1U << CRU_CRU_SOFTRST_CON13_HRESETN_SFC1_SHIFT)           /* 0x00000020 */
#define CRU_CRU_SOFTRST_CON13_HRESETN_XIP_SFC1_SHIFT       (6U)
#define CRU_CRU_SOFTRST_CON13_HRESETN_XIP_SFC1_MASK        (0x1U << CRU_CRU_SOFTRST_CON13_HRESETN_XIP_SFC1_SHIFT)       /* 0x00000040 */
#define CRU_CRU_SOFTRST_CON13_RESETN_SDIO_SHIFT            (8U)
#define CRU_CRU_SOFTRST_CON13_RESETN_SDIO_MASK             (0x1U << CRU_CRU_SOFTRST_CON13_RESETN_SDIO_SHIFT)            /* 0x00000100 */
#define CRU_CRU_SOFTRST_CON13_MRESETN_I2S1_8CH_SHIFT       (11U)
#define CRU_CRU_SOFTRST_CON13_MRESETN_I2S1_8CH_MASK        (0x1U << CRU_CRU_SOFTRST_CON13_MRESETN_I2S1_8CH_SHIFT)       /* 0x00000800 */
#define CRU_CRU_SOFTRST_CON13_RESETN_PWM_SHIFT             (13U)
#define CRU_CRU_SOFTRST_CON13_RESETN_PWM_MASK              (0x1U << CRU_CRU_SOFTRST_CON13_RESETN_PWM_SHIFT)             /* 0x00002000 */
#define CRU_CRU_SOFTRST_CON13_RESETN_AUDPWM_SHIFT          (14U)
#define CRU_CRU_SOFTRST_CON13_RESETN_AUDPWM_MASK           (0x1U << CRU_CRU_SOFTRST_CON13_RESETN_AUDPWM_SHIFT)          /* 0x00004000 */
#define CRU_CRU_SOFTRST_CON13_ARESETN_CIF_SHIFT            (15U)
#define CRU_CRU_SOFTRST_CON13_ARESETN_CIF_MASK             (0x1U << CRU_CRU_SOFTRST_CON13_ARESETN_CIF_SHIFT)            /* 0x00008000 */
/* CRU_SOFTRST_CON14 */
#define CRU_CRU_SOFTRST_CON14_OFFSET                       (0x238)
#define CRU_CRU_SOFTRST_CON14_ARESETN_CIF_NIU_SHIFT        (1U)
#define CRU_CRU_SOFTRST_CON14_ARESETN_CIF_NIU_MASK         (0x1U << CRU_CRU_SOFTRST_CON14_ARESETN_CIF_NIU_SHIFT)        /* 0x00000002 */
#define CRU_CRU_SOFTRST_CON14_SRESETN_SFC1_SHIFT           (4U)
#define CRU_CRU_SOFTRST_CON14_SRESETN_SFC1_MASK            (0x1U << CRU_CRU_SOFTRST_CON14_SRESETN_SFC1_SHIFT)           /* 0x00000010 */
#define CRU_CRU_SOFTRST_CON14_RESETN_USB2_ADP_SHIFT        (5U)
#define CRU_CRU_SOFTRST_CON14_RESETN_USB2_ADP_MASK         (0x1U << CRU_CRU_SOFTRST_CON14_RESETN_USB2_ADP_SHIFT)        /* 0x00000020 */
#define CRU_CRU_SOFTRST_CON14_RESETN_KEY_SHIFT             (9U)
#define CRU_CRU_SOFTRST_CON14_RESETN_KEY_MASK              (0x1U << CRU_CRU_SOFTRST_CON14_RESETN_KEY_SHIFT)             /* 0x00000200 */
#define CRU_CRU_SOFTRST_CON14_PRESETN_KEY_SHIFT            (10U)
#define CRU_CRU_SOFTRST_CON14_PRESETN_KEY_MASK             (0x1U << CRU_CRU_SOFTRST_CON14_PRESETN_KEY_SHIFT)            /* 0x00000400 */
#define CRU_CRU_SOFTRST_CON14_RESETN_USB2PHYUTMI_SHIFT     (12U)
#define CRU_CRU_SOFTRST_CON14_RESETN_USB2PHYUTMI_MASK      (0x1U << CRU_CRU_SOFTRST_CON14_RESETN_USB2PHYUTMI_SHIFT)     /* 0x00001000 */
#define CRU_CRU_SOFTRST_CON14_RESETN_USB2CTRL_SHIFT        (13U)
#define CRU_CRU_SOFTRST_CON14_RESETN_USB2CTRL_MASK         (0x1U << CRU_CRU_SOFTRST_CON14_RESETN_USB2CTRL_SHIFT)        /* 0x00002000 */
#define CRU_CRU_SOFTRST_CON14_RESETN_USB2PHYPO_SHIFT       (14U)
#define CRU_CRU_SOFTRST_CON14_RESETN_USB2PHYPO_MASK        (0x1U << CRU_CRU_SOFTRST_CON14_RESETN_USB2PHYPO_SHIFT)       /* 0x00004000 */
/* GLB_CNT_TH */
#define CRU_GLB_CNT_TH_OFFSET                              (0x300)
#define CRU_GLB_CNT_TH_GLOBAL_RESET_COUNTER_THRESHOLD_SHIFT (0U)
#define CRU_GLB_CNT_TH_GLOBAL_RESET_COUNTER_THRESHOLD_MASK (0xFFFFU << CRU_GLB_CNT_TH_GLOBAL_RESET_COUNTER_THRESHOLD_SHIFT) /* 0x0000FFFF */
/* CRU_GLBRST_ST */
#define CRU_CRU_GLBRST_ST_OFFSET                           (0x304)
#define CRU_CRU_GLBRST_ST_FST_GLB_RST_ST_SHIFT             (0U)
#define CRU_CRU_GLBRST_ST_FST_GLB_RST_ST_MASK              (0x1U << CRU_CRU_GLBRST_ST_FST_GLB_RST_ST_SHIFT)             /* 0x00000001 */
#define CRU_CRU_GLBRST_ST_SND_GLB_RST_ST_SHIFT             (1U)
#define CRU_CRU_GLBRST_ST_SND_GLB_RST_ST_MASK              (0x1U << CRU_CRU_GLBRST_ST_SND_GLB_RST_ST_SHIFT)             /* 0x00000002 */
#define CRU_CRU_GLBRST_ST_FST_GLB_WDT_RST_ST_SHIFT         (4U)
#define CRU_CRU_GLBRST_ST_FST_GLB_WDT_RST_ST_MASK          (0x1U << CRU_CRU_GLBRST_ST_FST_GLB_WDT_RST_ST_SHIFT)         /* 0x00000010 */
#define CRU_CRU_GLBRST_ST_SND_GLB_WDT_RST_ST_SHIFT         (5U)
#define CRU_CRU_GLBRST_ST_SND_GLB_WDT_RST_ST_MASK          (0x1U << CRU_CRU_GLBRST_ST_SND_GLB_WDT_RST_ST_SHIFT)         /* 0x00000020 */
#define CRU_CRU_GLBRST_ST_WDT0_GLBRST_SHIFT                (6U)
#define CRU_CRU_GLBRST_ST_WDT0_GLBRST_MASK                 (0x1U << CRU_CRU_GLBRST_ST_WDT0_GLBRST_SHIFT)                /* 0x00000040 */
#define CRU_CRU_GLBRST_ST_WDT1_GLBRST_SHIFT                (7U)
#define CRU_CRU_GLBRST_ST_WDT1_GLBRST_MASK                 (0x1U << CRU_CRU_GLBRST_ST_WDT1_GLBRST_SHIFT)                /* 0x00000080 */
#define CRU_CRU_GLBRST_ST_WDT2_GLBRST_SHIFT                (8U)
#define CRU_CRU_GLBRST_ST_WDT2_GLBRST_MASK                 (0x1U << CRU_CRU_GLBRST_ST_WDT2_GLBRST_SHIFT)                /* 0x00000100 */
#define CRU_CRU_GLBRST_ST_WDT3_GLBRST_SHIFT                (9U)
#define CRU_CRU_GLBRST_ST_WDT3_GLBRST_MASK                 (0x1U << CRU_CRU_GLBRST_ST_WDT3_GLBRST_SHIFT)                /* 0x00000200 */
/* GLB_SRST_FST_VALUE */
#define CRU_GLB_SRST_FST_VALUE_OFFSET                      (0x308)
#define CRU_GLB_SRST_FST_VALUE_GLB_SRST_FST_SHIFT          (0U)
#define CRU_GLB_SRST_FST_VALUE_GLB_SRST_FST_MASK           (0xFFFFU << CRU_GLB_SRST_FST_VALUE_GLB_SRST_FST_SHIFT)       /* 0x0000FFFF */
/* GLB_SRST_SND_VALUE */
#define CRU_GLB_SRST_SND_VALUE_OFFSET                      (0x30C)
#define CRU_GLB_SRST_SND_VALUE_GLB_SRST_SND_SHIFT          (0U)
#define CRU_GLB_SRST_SND_VALUE_GLB_SRST_SND_MASK           (0xFFFFU << CRU_GLB_SRST_SND_VALUE_GLB_SRST_SND_SHIFT)       /* 0x0000FFFF */
/* GLB_RST_CON */
#define CRU_GLB_RST_CON_OFFSET                             (0x310)
#define CRU_GLB_RST_CON_WDT_RESET_EXT_EN_SHIFT             (7U)
#define CRU_GLB_RST_CON_WDT_RESET_EXT_EN_MASK              (0x1U << CRU_GLB_RST_CON_WDT_RESET_EXT_EN_SHIFT)             /* 0x00000080 */
#define CRU_GLB_RST_CON_WDT0_GLBRST_EN_SHIFT               (8U)
#define CRU_GLB_RST_CON_WDT0_GLBRST_EN_MASK                (0x1U << CRU_GLB_RST_CON_WDT0_GLBRST_EN_SHIFT)               /* 0x00000100 */
#define CRU_GLB_RST_CON_WDT1_GLBRST_EN_SHIFT               (9U)
#define CRU_GLB_RST_CON_WDT1_GLBRST_EN_MASK                (0x1U << CRU_GLB_RST_CON_WDT1_GLBRST_EN_SHIFT)               /* 0x00000200 */
#define CRU_GLB_RST_CON_WDT2_GLBRST_EN_SHIFT               (10U)
#define CRU_GLB_RST_CON_WDT2_GLBRST_EN_MASK                (0x1U << CRU_GLB_RST_CON_WDT2_GLBRST_EN_SHIFT)               /* 0x00000400 */
#define CRU_GLB_RST_CON_WDT3_GLBRST_EN_SHIFT               (11U)
#define CRU_GLB_RST_CON_WDT3_GLBRST_EN_MASK                (0x1U << CRU_GLB_RST_CON_WDT3_GLBRST_EN_SHIFT)               /* 0x00000800 */
#define CRU_GLB_RST_CON_WDT0_FST_GLBRST_EN_SHIFT           (12U)
#define CRU_GLB_RST_CON_WDT0_FST_GLBRST_EN_MASK            (0x1U << CRU_GLB_RST_CON_WDT0_FST_GLBRST_EN_SHIFT)           /* 0x00001000 */
#define CRU_GLB_RST_CON_WDT1_FST_GLBRST_EN_SHIFT           (13U)
#define CRU_GLB_RST_CON_WDT1_FST_GLBRST_EN_MASK            (0x1U << CRU_GLB_RST_CON_WDT1_FST_GLBRST_EN_SHIFT)           /* 0x00002000 */
#define CRU_GLB_RST_CON_WDT2_FST_GLBRST_EN_SHIFT           (14U)
#define CRU_GLB_RST_CON_WDT2_FST_GLBRST_EN_MASK            (0x1U << CRU_GLB_RST_CON_WDT2_FST_GLBRST_EN_SHIFT)           /* 0x00004000 */
#define CRU_GLB_RST_CON_WDT3_FST_GLBRST_EN_SHIFT           (15U)
#define CRU_GLB_RST_CON_WDT3_FST_GLBRST_EN_MASK            (0x1U << CRU_GLB_RST_CON_WDT3_FST_GLBRST_EN_SHIFT)           /* 0x00008000 */
/* CRU_SDIO_CON0 */
#define CRU_CRU_SDIO_CON0_OFFSET                           (0x320)
#define CRU_CRU_SDIO_CON0_SDIO_CON0_SHIFT                  (0U)
#define CRU_CRU_SDIO_CON0_SDIO_CON0_MASK                   (0xFFFFU << CRU_CRU_SDIO_CON0_SDIO_CON0_SHIFT)               /* 0x0000FFFF */
/* CRU_SDIO_CON1 */
#define CRU_CRU_SDIO_CON1_OFFSET                           (0x324)
#define CRU_CRU_SDIO_CON1_SDIO_CON1_SHIFT                  (0U)
#define CRU_CRU_SDIO_CON1_SDIO_CON1_MASK                   (0xFFFFU << CRU_CRU_SDIO_CON1_SDIO_CON1_SHIFT)               /* 0x0000FFFF */
/* DCG0_CON0 */
#define CRU_DCG0_CON0_OFFSET                               (0x330)
#define CRU_DCG0_CON0_CFG_PERIOD_SHIFT                     (0U)
#define CRU_DCG0_CON0_CFG_PERIOD_MASK                      (0xFFFFFFFFU << CRU_DCG0_CON0_CFG_PERIOD_SHIFT)              /* 0xFFFFFFFF */
/* DCG0_CON1 */
#define CRU_DCG0_CON1_OFFSET                               (0x334)
#define CRU_DCG0_CON1_CFG_CNT_SHIFT                        (0U)
#define CRU_DCG0_CON1_CFG_CNT_MASK                         (0xFFFFFFFFU << CRU_DCG0_CON1_CFG_CNT_SHIFT)                 /* 0xFFFFFFFF */
/* DCG0_CON2 */
#define CRU_DCG0_CON2_OFFSET                               (0x338)
#define CRU_DCG0_CON2_CFG_PERIOD_SHIFT                     (0U)
#define CRU_DCG0_CON2_CFG_PERIOD_MASK                      (0xFFFFFFFFU << CRU_DCG0_CON2_CFG_PERIOD_SHIFT)              /* 0xFFFFFFFF */
/* DCG0_CON3 */
#define CRU_DCG0_CON3_OFFSET                               (0x33C)
#define CRU_DCG0_CON3_CFG_CNT_SHIFT                        (0U)
#define CRU_DCG0_CON3_CFG_CNT_MASK                         (0xFFFFFFFFU << CRU_DCG0_CON3_CFG_CNT_SHIFT)                 /* 0xFFFFFFFF */
/* DCG0_CON4 */
#define CRU_DCG0_CON4_OFFSET                               (0x340)
#define CRU_DCG0_CON4_CFG_STEP1_SHIFT                      (0U)
#define CRU_DCG0_CON4_CFG_STEP1_MASK                       (0x7FU << CRU_DCG0_CON4_CFG_STEP1_SHIFT)                     /* 0x0000007F */
#define CRU_DCG0_CON4_CFG_STEP2_SHIFT                      (8U)
#define CRU_DCG0_CON4_CFG_STEP2_MASK                       (0x7FU << CRU_DCG0_CON4_CFG_STEP2_SHIFT)                     /* 0x00007F00 */
#define CRU_DCG0_CON4_CFG_EN_SHIFT                         (15U)
#define CRU_DCG0_CON4_CFG_EN_MASK                          (0x1U << CRU_DCG0_CON4_CFG_EN_SHIFT)                         /* 0x00008000 */
/* DCG0_CON5 */
#define CRU_DCG0_CON5_OFFSET                               (0x344)
#define CRU_DCG0_CON5_CFG_LMT_SHIFT                        (0U)
#define CRU_DCG0_CON5_CFG_LMT_MASK                         (0x7FU << CRU_DCG0_CON5_CFG_LMT_SHIFT)                       /* 0x0000007F */
/* DCG0_CON6 */
#define CRU_DCG0_CON6_OFFSET                               (0x348)
/* DCG0_CON7 */
#define CRU_DCG0_CON7_OFFSET                               (0x34C)
/* DCG1_CON0 */
#define CRU_DCG1_CON0_OFFSET                               (0x350)
#define CRU_DCG1_CON0_CFG_PERIOD_SHIFT                     (0U)
#define CRU_DCG1_CON0_CFG_PERIOD_MASK                      (0xFFFFFFFFU << CRU_DCG1_CON0_CFG_PERIOD_SHIFT)              /* 0xFFFFFFFF */
/* DCG1_CON1 */
#define CRU_DCG1_CON1_OFFSET                               (0x354)
#define CRU_DCG1_CON1_CFG_CNT_SHIFT                        (0U)
#define CRU_DCG1_CON1_CFG_CNT_MASK                         (0xFFFFFFFFU << CRU_DCG1_CON1_CFG_CNT_SHIFT)                 /* 0xFFFFFFFF */
/* DCG1_CON2 */
#define CRU_DCG1_CON2_OFFSET                               (0x358)
#define CRU_DCG1_CON2_CFG_PERIOD_SHIFT                     (0U)
#define CRU_DCG1_CON2_CFG_PERIOD_MASK                      (0xFFFFFFFFU << CRU_DCG1_CON2_CFG_PERIOD_SHIFT)              /* 0xFFFFFFFF */
/* DCG1_CON3 */
#define CRU_DCG1_CON3_OFFSET                               (0x35C)
#define CRU_DCG1_CON3_CFG_CNT_SHIFT                        (0U)
#define CRU_DCG1_CON3_CFG_CNT_MASK                         (0xFFFFFFFFU << CRU_DCG1_CON3_CFG_CNT_SHIFT)                 /* 0xFFFFFFFF */
/* DCG1_CON4 */
#define CRU_DCG1_CON4_OFFSET                               (0x360)
#define CRU_DCG1_CON4_CFG_STEP1_SHIFT                      (0U)
#define CRU_DCG1_CON4_CFG_STEP1_MASK                       (0x7FU << CRU_DCG1_CON4_CFG_STEP1_SHIFT)                     /* 0x0000007F */
#define CRU_DCG1_CON4_CFG_STEP2_SHIFT                      (8U)
#define CRU_DCG1_CON4_CFG_STEP2_MASK                       (0x7FU << CRU_DCG1_CON4_CFG_STEP2_SHIFT)                     /* 0x00007F00 */
#define CRU_DCG1_CON4_CFG_EN_SHIFT                         (15U)
#define CRU_DCG1_CON4_CFG_EN_MASK                          (0x1U << CRU_DCG1_CON4_CFG_EN_SHIFT)                         /* 0x00008000 */
/* DCG1_CON5 */
#define CRU_DCG1_CON5_OFFSET                               (0x364)
#define CRU_DCG1_CON5_CFG_LMT_SHIFT                        (0U)
#define CRU_DCG1_CON5_CFG_LMT_MASK                         (0x7FU << CRU_DCG1_CON5_CFG_LMT_SHIFT)                       /* 0x0000007F */
/* DCG1_CON6 */
#define CRU_DCG1_CON6_OFFSET                               (0x368)
/* DCG1_CON7 */
#define CRU_DCG1_CON7_OFFSET                               (0x36C)
/* AS0_CON0 */
#define CRU_AS0_CON0_OFFSET                                (0x400)
#define CRU_AS0_CON0_CNT_TH_SHIFT                          (0U)
#define CRU_AS0_CON0_CNT_TH_MASK                           (0xFFFFU << CRU_AS0_CON0_CNT_TH_SHIFT)                       /* 0x0000FFFF */
#define CRU_AS0_CON0_WAIT_TH_SHIFT                         (16U)
#define CRU_AS0_CON0_WAIT_TH_MASK                          (0xFFFFU << CRU_AS0_CON0_WAIT_TH_SHIFT)                      /* 0xFFFF0000 */
/* AS0_CON1 */
#define CRU_AS0_CON1_OFFSET                                (0x404)
#define CRU_AS0_CON1_AS_CTRL_SHIFT                         (0U)
#define CRU_AS0_CON1_AS_CTRL_MASK                          (0xFFFU << CRU_AS0_CON1_AS_CTRL_SHIFT)                       /* 0x00000FFF */
#define CRU_AS0_CON1_AS_EN_SHIFT                           (12U)
#define CRU_AS0_CON1_AS_EN_MASK                            (0x1U << CRU_AS0_CON1_AS_EN_SHIFT)                           /* 0x00001000 */
#define CRU_AS0_CON1_ASS_EN_SHIFT                          (13U)
#define CRU_AS0_CON1_ASS_EN_MASK                           (0x1U << CRU_AS0_CON1_ASS_EN_SHIFT)                          /* 0x00002000 */
#define CRU_AS0_CON1_AS_CFG_SHIFT                          (14U)
#define CRU_AS0_CON1_AS_CFG_MASK                           (0x3U << CRU_AS0_CON1_AS_CFG_SHIFT)                          /* 0x0000C000 */
/* AS1_CON0 */
#define CRU_AS1_CON0_OFFSET                                (0x408)
#define CRU_AS1_CON0_CNT_TH_SHIFT                          (0U)
#define CRU_AS1_CON0_CNT_TH_MASK                           (0xFFFFU << CRU_AS1_CON0_CNT_TH_SHIFT)                       /* 0x0000FFFF */
#define CRU_AS1_CON0_WAIT_TH_SHIFT                         (16U)
#define CRU_AS1_CON0_WAIT_TH_MASK                          (0xFFFFU << CRU_AS1_CON0_WAIT_TH_SHIFT)                      /* 0xFFFF0000 */
/* AS1_CON1 */
#define CRU_AS1_CON1_OFFSET                                (0x40C)
#define CRU_AS1_CON1_AS_CTRL_SHIFT                         (0U)
#define CRU_AS1_CON1_AS_CTRL_MASK                          (0xFFFU << CRU_AS1_CON1_AS_CTRL_SHIFT)                       /* 0x00000FFF */
#define CRU_AS1_CON1_AS_EN_SHIFT                           (12U)
#define CRU_AS1_CON1_AS_EN_MASK                            (0x1U << CRU_AS1_CON1_AS_EN_SHIFT)                           /* 0x00001000 */
#define CRU_AS1_CON1_ASS_EN_SHIFT                          (13U)
#define CRU_AS1_CON1_ASS_EN_MASK                           (0x1U << CRU_AS1_CON1_ASS_EN_SHIFT)                          /* 0x00002000 */
#define CRU_AS1_CON1_AS_CFG_SHIFT                          (14U)
#define CRU_AS1_CON1_AS_CFG_MASK                           (0x3U << CRU_AS1_CON1_AS_CFG_SHIFT)                          /* 0x0000C000 */
/* AS2_CON0 */
#define CRU_AS2_CON0_OFFSET                                (0x410)
#define CRU_AS2_CON0_CNT_TH_SHIFT                          (0U)
#define CRU_AS2_CON0_CNT_TH_MASK                           (0xFFFFU << CRU_AS2_CON0_CNT_TH_SHIFT)                       /* 0x0000FFFF */
#define CRU_AS2_CON0_WAIT_TH_SHIFT                         (16U)
#define CRU_AS2_CON0_WAIT_TH_MASK                          (0xFFFFU << CRU_AS2_CON0_WAIT_TH_SHIFT)                      /* 0xFFFF0000 */
/* AS2_CON1 */
#define CRU_AS2_CON1_OFFSET                                (0x414)
#define CRU_AS2_CON1_AS_EN_SHIFT                           (12U)
#define CRU_AS2_CON1_AS_EN_MASK                            (0x1U << CRU_AS2_CON1_AS_EN_SHIFT)                           /* 0x00001000 */
#define CRU_AS2_CON1_ASS_EN_SHIFT                          (13U)
#define CRU_AS2_CON1_ASS_EN_MASK                           (0x1U << CRU_AS2_CON1_ASS_EN_SHIFT)                          /* 0x00002000 */
#define CRU_AS2_CON1_AS_CFG_SHIFT                          (14U)
#define CRU_AS2_CON1_AS_CFG_MASK                           (0x3U << CRU_AS2_CON1_AS_CFG_SHIFT)                          /* 0x0000C000 */
/* AS3_CON0 */
#define CRU_AS3_CON0_OFFSET                                (0x418)
#define CRU_AS3_CON0_CNT_TH_SHIFT                          (0U)
#define CRU_AS3_CON0_CNT_TH_MASK                           (0xFFFFU << CRU_AS3_CON0_CNT_TH_SHIFT)                       /* 0x0000FFFF */
#define CRU_AS3_CON0_WAIT_TH_SHIFT                         (16U)
#define CRU_AS3_CON0_WAIT_TH_MASK                          (0xFFFFU << CRU_AS3_CON0_WAIT_TH_SHIFT)                      /* 0xFFFF0000 */
/* AS3_CON1 */
#define CRU_AS3_CON1_OFFSET                                (0x41C)
#define CRU_AS3_CON1_AS_CTRL_SHIFT                         (0U)
#define CRU_AS3_CON1_AS_CTRL_MASK                          (0xFFFU << CRU_AS3_CON1_AS_CTRL_SHIFT)                       /* 0x00000FFF */
#define CRU_AS3_CON1_AS_EN_SHIFT                           (12U)
#define CRU_AS3_CON1_AS_EN_MASK                            (0x1U << CRU_AS3_CON1_AS_EN_SHIFT)                           /* 0x00001000 */
#define CRU_AS3_CON1_ASS_EN_SHIFT                          (13U)
#define CRU_AS3_CON1_ASS_EN_MASK                           (0x1U << CRU_AS3_CON1_ASS_EN_SHIFT)                          /* 0x00002000 */
#define CRU_AS3_CON1_AS_CFG_SHIFT                          (14U)
#define CRU_AS3_CON1_AS_CFG_MASK                           (0x3U << CRU_AS3_CON1_AS_CFG_SHIFT)                          /* 0x0000C000 */
/* AS4_CON0 */
#define CRU_AS4_CON0_OFFSET                                (0x420)
#define CRU_AS4_CON0_CNT_TH_SHIFT                          (0U)
#define CRU_AS4_CON0_CNT_TH_MASK                           (0xFFFFU << CRU_AS4_CON0_CNT_TH_SHIFT)                       /* 0x0000FFFF */
#define CRU_AS4_CON0_WAIT_TH_SHIFT                         (16U)
#define CRU_AS4_CON0_WAIT_TH_MASK                          (0xFFFFU << CRU_AS4_CON0_WAIT_TH_SHIFT)                      /* 0xFFFF0000 */
/* AS4_CON1 */
#define CRU_AS4_CON1_OFFSET                                (0x424)
#define CRU_AS4_CON1_AS_CTRL_SHIFT                         (0U)
#define CRU_AS4_CON1_AS_CTRL_MASK                          (0xFFFU << CRU_AS4_CON1_AS_CTRL_SHIFT)                       /* 0x00000FFF */
#define CRU_AS4_CON1_AS_EN_SHIFT                           (12U)
#define CRU_AS4_CON1_AS_EN_MASK                            (0x1U << CRU_AS4_CON1_AS_EN_SHIFT)                           /* 0x00001000 */
#define CRU_AS4_CON1_ASS_EN_SHIFT                          (13U)
#define CRU_AS4_CON1_ASS_EN_MASK                           (0x1U << CRU_AS4_CON1_ASS_EN_SHIFT)                          /* 0x00002000 */
#define CRU_AS4_CON1_AS_CFG_SHIFT                          (14U)
#define CRU_AS4_CON1_AS_CFG_MASK                           (0x3U << CRU_AS4_CON1_AS_CFG_SHIFT)                          /* 0x0000C000 */
/******************************************GRF*******************************************/
/* GPIO0A_IOMUX_L */
#define GRF_GPIO0A_IOMUX_L_OFFSET                          (0x0U)
#define GRF_GPIO0A_IOMUX_L_GPIO0A0_SEL_SHIFT               (0U)
#define GRF_GPIO0A_IOMUX_L_GPIO0A0_SEL_MASK                (0xFU << GRF_GPIO0A_IOMUX_L_GPIO0A0_SEL_SHIFT)               /* 0x0000000F */
#define GRF_GPIO0A_IOMUX_L_GPIO0A1_SEL_SHIFT               (4U)
#define GRF_GPIO0A_IOMUX_L_GPIO0A1_SEL_MASK                (0xFU << GRF_GPIO0A_IOMUX_L_GPIO0A1_SEL_SHIFT)               /* 0x000000F0 */
#define GRF_GPIO0A_IOMUX_L_GPIO0A2_SEL_SHIFT               (8U)
#define GRF_GPIO0A_IOMUX_L_GPIO0A2_SEL_MASK                (0xFU << GRF_GPIO0A_IOMUX_L_GPIO0A2_SEL_SHIFT)               /* 0x00000F00 */
#define GRF_GPIO0A_IOMUX_L_GPIO0A3_SEL_SHIFT               (12U)
#define GRF_GPIO0A_IOMUX_L_GPIO0A3_SEL_MASK                (0xFU << GRF_GPIO0A_IOMUX_L_GPIO0A3_SEL_SHIFT)               /* 0x0000F000 */
/* GPIO0A_IOMUX_H */
#define GRF_GPIO0A_IOMUX_H_OFFSET                          (0x4U)
#define GRF_GPIO0A_IOMUX_H_GPIO0A4_SEL_SHIFT               (0U)
#define GRF_GPIO0A_IOMUX_H_GPIO0A4_SEL_MASK                (0xFU << GRF_GPIO0A_IOMUX_H_GPIO0A4_SEL_SHIFT)               /* 0x0000000F */
#define GRF_GPIO0A_IOMUX_H_GPIO0A5_SEL_SHIFT               (4U)
#define GRF_GPIO0A_IOMUX_H_GPIO0A5_SEL_MASK                (0xFU << GRF_GPIO0A_IOMUX_H_GPIO0A5_SEL_SHIFT)               /* 0x000000F0 */
#define GRF_GPIO0A_IOMUX_H_GPIO0A6_SEL_SHIFT               (8U)
#define GRF_GPIO0A_IOMUX_H_GPIO0A6_SEL_MASK                (0xFU << GRF_GPIO0A_IOMUX_H_GPIO0A6_SEL_SHIFT)               /* 0x00000F00 */
#define GRF_GPIO0A_IOMUX_H_GPIO0A7_SEL_SHIFT               (12U)
#define GRF_GPIO0A_IOMUX_H_GPIO0A7_SEL_MASK                (0xFU << GRF_GPIO0A_IOMUX_H_GPIO0A7_SEL_SHIFT)               /* 0x0000F000 */
/* GPIO0B_IOMUX_L */
#define GRF_GPIO0B_IOMUX_L_OFFSET                          (0x8U)
#define GRF_GPIO0B_IOMUX_L_GPIO0B0_SEL_SHIFT               (0U)
#define GRF_GPIO0B_IOMUX_L_GPIO0B0_SEL_MASK                (0xFU << GRF_GPIO0B_IOMUX_L_GPIO0B0_SEL_SHIFT)               /* 0x0000000F */
#define GRF_GPIO0B_IOMUX_L_GPIO0B1_SEL_SHIFT               (4U)
#define GRF_GPIO0B_IOMUX_L_GPIO0B1_SEL_MASK                (0xFU << GRF_GPIO0B_IOMUX_L_GPIO0B1_SEL_SHIFT)               /* 0x000000F0 */
#define GRF_GPIO0B_IOMUX_L_GPIO0B2_SEL_SHIFT               (8U)
#define GRF_GPIO0B_IOMUX_L_GPIO0B2_SEL_MASK                (0xFU << GRF_GPIO0B_IOMUX_L_GPIO0B2_SEL_SHIFT)               /* 0x00000F00 */
#define GRF_GPIO0B_IOMUX_L_GPIO0B3_SEL_SHIFT               (12U)
#define GRF_GPIO0B_IOMUX_L_GPIO0B3_SEL_MASK                (0xFU << GRF_GPIO0B_IOMUX_L_GPIO0B3_SEL_SHIFT)               /* 0x0000F000 */
/* GPIO0B_IOMUX_H */
#define GRF_GPIO0B_IOMUX_H_OFFSET                          (0xCU)
#define GRF_GPIO0B_IOMUX_H_GPIO0B4_SEL_SHIFT               (0U)
#define GRF_GPIO0B_IOMUX_H_GPIO0B4_SEL_MASK                (0xFU << GRF_GPIO0B_IOMUX_H_GPIO0B4_SEL_SHIFT)               /* 0x0000000F */
#define GRF_GPIO0B_IOMUX_H_GPIO0B5_SEL_SHIFT               (4U)
#define GRF_GPIO0B_IOMUX_H_GPIO0B5_SEL_MASK                (0xFU << GRF_GPIO0B_IOMUX_H_GPIO0B5_SEL_SHIFT)               /* 0x000000F0 */
#define GRF_GPIO0B_IOMUX_H_GPIO0B6_SEL_SHIFT               (8U)
#define GRF_GPIO0B_IOMUX_H_GPIO0B6_SEL_MASK                (0xFU << GRF_GPIO0B_IOMUX_H_GPIO0B6_SEL_SHIFT)               /* 0x00000F00 */
#define GRF_GPIO0B_IOMUX_H_GPIO0B7_SEL_SHIFT               (12U)
#define GRF_GPIO0B_IOMUX_H_GPIO0B7_SEL_MASK                (0xFU << GRF_GPIO0B_IOMUX_H_GPIO0B7_SEL_SHIFT)               /* 0x0000F000 */
/* GPIO0C_IOMUX_L */
#define GRF_GPIO0C_IOMUX_L_OFFSET                          (0x10U)
#define GRF_GPIO0C_IOMUX_L_GPIO0C0_SEL_SHIFT               (0U)
#define GRF_GPIO0C_IOMUX_L_GPIO0C0_SEL_MASK                (0xFU << GRF_GPIO0C_IOMUX_L_GPIO0C0_SEL_SHIFT)               /* 0x0000000F */
#define GRF_GPIO0C_IOMUX_L_GPIO0C1_SEL_SHIFT               (4U)
#define GRF_GPIO0C_IOMUX_L_GPIO0C1_SEL_MASK                (0xFU << GRF_GPIO0C_IOMUX_L_GPIO0C1_SEL_SHIFT)               /* 0x000000F0 */
#define GRF_GPIO0C_IOMUX_L_GPIO0C2_SEL_SHIFT               (8U)
#define GRF_GPIO0C_IOMUX_L_GPIO0C2_SEL_MASK                (0xFU << GRF_GPIO0C_IOMUX_L_GPIO0C2_SEL_SHIFT)               /* 0x00000F00 */
#define GRF_GPIO0C_IOMUX_L_GPIO0C3_SEL_SHIFT               (12U)
#define GRF_GPIO0C_IOMUX_L_GPIO0C3_SEL_MASK                (0xFU << GRF_GPIO0C_IOMUX_L_GPIO0C3_SEL_SHIFT)               /* 0x0000F000 */
/* GPIO0C_IOMUX_H */
#define GRF_GPIO0C_IOMUX_H_OFFSET                          (0x14U)
#define GRF_GPIO0C_IOMUX_H_GPIO0C4_SEL_SHIFT               (0U)
#define GRF_GPIO0C_IOMUX_H_GPIO0C4_SEL_MASK                (0xFU << GRF_GPIO0C_IOMUX_H_GPIO0C4_SEL_SHIFT)               /* 0x0000000F */
#define GRF_GPIO0C_IOMUX_H_GPIO0C5_SEL_SHIFT               (4U)
#define GRF_GPIO0C_IOMUX_H_GPIO0C5_SEL_MASK                (0xFU << GRF_GPIO0C_IOMUX_H_GPIO0C5_SEL_SHIFT)               /* 0x000000F0 */
#define GRF_GPIO0C_IOMUX_H_GPIO0C6_SEL_SHIFT               (8U)
#define GRF_GPIO0C_IOMUX_H_GPIO0C6_SEL_MASK                (0xFU << GRF_GPIO0C_IOMUX_H_GPIO0C6_SEL_SHIFT)               /* 0x00000F00 */
#define GRF_GPIO0C_IOMUX_H_GPIO0C7_SEL_SHIFT               (12U)
#define GRF_GPIO0C_IOMUX_H_GPIO0C7_SEL_MASK                (0xFU << GRF_GPIO0C_IOMUX_H_GPIO0C7_SEL_SHIFT)               /* 0x0000F000 */
/* GPIO0D_IOMUX_L */
#define GRF_GPIO0D_IOMUX_L_OFFSET                          (0x18U)
#define GRF_GPIO0D_IOMUX_L_GPIO0D0_SEL_SHIFT               (0U)
#define GRF_GPIO0D_IOMUX_L_GPIO0D0_SEL_MASK                (0xFU << GRF_GPIO0D_IOMUX_L_GPIO0D0_SEL_SHIFT)               /* 0x0000000F */
#define GRF_GPIO0D_IOMUX_L_GPIO0D1_SEL_SHIFT               (4U)
#define GRF_GPIO0D_IOMUX_L_GPIO0D1_SEL_MASK                (0xFU << GRF_GPIO0D_IOMUX_L_GPIO0D1_SEL_SHIFT)               /* 0x000000F0 */
#define GRF_GPIO0D_IOMUX_L_GPIO0D2_SEL_SHIFT               (8U)
#define GRF_GPIO0D_IOMUX_L_GPIO0D2_SEL_MASK                (0xFU << GRF_GPIO0D_IOMUX_L_GPIO0D2_SEL_SHIFT)               /* 0x00000F00 */
#define GRF_GPIO0D_IOMUX_L_GPIO0D3_SEL_SHIFT               (12U)
#define GRF_GPIO0D_IOMUX_L_GPIO0D3_SEL_MASK                (0xFU << GRF_GPIO0D_IOMUX_L_GPIO0D3_SEL_SHIFT)               /* 0x0000F000 */
/* GPIO0D_IOMUX_H */
#define GRF_GPIO0D_IOMUX_H_OFFSET                          (0x1CU)
#define GRF_GPIO0D_IOMUX_H_GPIO0D4_SEL_SHIFT               (0U)
#define GRF_GPIO0D_IOMUX_H_GPIO0D4_SEL_MASK                (0xFU << GRF_GPIO0D_IOMUX_H_GPIO0D4_SEL_SHIFT)               /* 0x0000000F */
#define GRF_GPIO0D_IOMUX_H_GPIO0D5_SEL_SHIFT               (4U)
#define GRF_GPIO0D_IOMUX_H_GPIO0D5_SEL_MASK                (0xFU << GRF_GPIO0D_IOMUX_H_GPIO0D5_SEL_SHIFT)               /* 0x000000F0 */
#define GRF_GPIO0D_IOMUX_H_GPIO0D6_SEL_SHIFT               (8U)
#define GRF_GPIO0D_IOMUX_H_GPIO0D6_SEL_MASK                (0xFU << GRF_GPIO0D_IOMUX_H_GPIO0D6_SEL_SHIFT)               /* 0x00000F00 */
#define GRF_GPIO0D_IOMUX_H_GPIO0D7_SEL_SHIFT               (12U)
#define GRF_GPIO0D_IOMUX_H_GPIO0D7_SEL_MASK                (0xFU << GRF_GPIO0D_IOMUX_H_GPIO0D7_SEL_SHIFT)               /* 0x0000F000 */
/* GPIO1A_IOMUX_L */
#define GRF_GPIO1A_IOMUX_L_OFFSET                          (0x20U)
#define GRF_GPIO1A_IOMUX_L_GPIO1A0_SEL_SHIFT               (0U)
#define GRF_GPIO1A_IOMUX_L_GPIO1A0_SEL_MASK                (0xFU << GRF_GPIO1A_IOMUX_L_GPIO1A0_SEL_SHIFT)               /* 0x0000000F */
#define GRF_GPIO1A_IOMUX_L_GPIO1A1_SEL_SHIFT               (4U)
#define GRF_GPIO1A_IOMUX_L_GPIO1A1_SEL_MASK                (0xFU << GRF_GPIO1A_IOMUX_L_GPIO1A1_SEL_SHIFT)               /* 0x000000F0 */
#define GRF_GPIO1A_IOMUX_L_GPIO1A2_SEL_SHIFT               (8U)
#define GRF_GPIO1A_IOMUX_L_GPIO1A2_SEL_MASK                (0xFU << GRF_GPIO1A_IOMUX_L_GPIO1A2_SEL_SHIFT)               /* 0x00000F00 */
#define GRF_GPIO1A_IOMUX_L_GPIO1A3_SEL_SHIFT               (12U)
#define GRF_GPIO1A_IOMUX_L_GPIO1A3_SEL_MASK                (0xFU << GRF_GPIO1A_IOMUX_L_GPIO1A3_SEL_SHIFT)               /* 0x0000F000 */
/* GPIO1A_IOMUX_H */
#define GRF_GPIO1A_IOMUX_H_OFFSET                          (0x24U)
#define GRF_GPIO1A_IOMUX_H_GPIO1A4_SEL_SHIFT               (0U)
#define GRF_GPIO1A_IOMUX_H_GPIO1A4_SEL_MASK                (0xFU << GRF_GPIO1A_IOMUX_H_GPIO1A4_SEL_SHIFT)               /* 0x0000000F */
#define GRF_GPIO1A_IOMUX_H_GPIO1A5_SEL_SHIFT               (4U)
#define GRF_GPIO1A_IOMUX_H_GPIO1A5_SEL_MASK                (0xFU << GRF_GPIO1A_IOMUX_H_GPIO1A5_SEL_SHIFT)               /* 0x000000F0 */
#define GRF_GPIO1A_IOMUX_H_GPIO1A6_SEL_SHIFT               (8U)
#define GRF_GPIO1A_IOMUX_H_GPIO1A6_SEL_MASK                (0xFU << GRF_GPIO1A_IOMUX_H_GPIO1A6_SEL_SHIFT)               /* 0x00000F00 */
#define GRF_GPIO1A_IOMUX_H_GPIO1A7_SEL_SHIFT               (12U)
#define GRF_GPIO1A_IOMUX_H_GPIO1A7_SEL_MASK                (0xFU << GRF_GPIO1A_IOMUX_H_GPIO1A7_SEL_SHIFT)               /* 0x0000F000 */
/* GPIO1B_IOMUX_L */
#define GRF_GPIO1B_IOMUX_L_OFFSET                          (0x28U)
#define GRF_GPIO1B_IOMUX_L_GPIO1B0_SEL_SHIFT               (0U)
#define GRF_GPIO1B_IOMUX_L_GPIO1B0_SEL_MASK                (0xFU << GRF_GPIO1B_IOMUX_L_GPIO1B0_SEL_SHIFT)               /* 0x0000000F */
#define GRF_GPIO1B_IOMUX_L_GPIO1B1_SEL_SHIFT               (4U)
#define GRF_GPIO1B_IOMUX_L_GPIO1B1_SEL_MASK                (0xFU << GRF_GPIO1B_IOMUX_L_GPIO1B1_SEL_SHIFT)               /* 0x000000F0 */
#define GRF_GPIO1B_IOMUX_L_GPIO1B2_SEL_SHIFT               (8U)
#define GRF_GPIO1B_IOMUX_L_GPIO1B2_SEL_MASK                (0xFU << GRF_GPIO1B_IOMUX_L_GPIO1B2_SEL_SHIFT)               /* 0x00000F00 */
#define GRF_GPIO1B_IOMUX_L_GPIO1B3_SEL_SHIFT               (12U)
#define GRF_GPIO1B_IOMUX_L_GPIO1B3_SEL_MASK                (0xFU << GRF_GPIO1B_IOMUX_L_GPIO1B3_SEL_SHIFT)               /* 0x0000F000 */
/* GPIO1B_IOMUX_H */
#define GRF_GPIO1B_IOMUX_H_OFFSET                          (0x2CU)
#define GRF_GPIO1B_IOMUX_H_GPIO1B4_SEL_SHIFT               (0U)
#define GRF_GPIO1B_IOMUX_H_GPIO1B4_SEL_MASK                (0xFU << GRF_GPIO1B_IOMUX_H_GPIO1B4_SEL_SHIFT)               /* 0x0000000F */
#define GRF_GPIO1B_IOMUX_H_GPIO1B5_SEL_SHIFT               (4U)
#define GRF_GPIO1B_IOMUX_H_GPIO1B5_SEL_MASK                (0xFU << GRF_GPIO1B_IOMUX_H_GPIO1B5_SEL_SHIFT)               /* 0x000000F0 */
#define GRF_GPIO1B_IOMUX_H_GPIO1B6_SEL_SHIFT               (8U)
#define GRF_GPIO1B_IOMUX_H_GPIO1B6_SEL_MASK                (0xFU << GRF_GPIO1B_IOMUX_H_GPIO1B6_SEL_SHIFT)               /* 0x00000F00 */
#define GRF_GPIO1B_IOMUX_H_GPIO1B7_SEL_SHIFT               (12U)
#define GRF_GPIO1B_IOMUX_H_GPIO1B7_SEL_MASK                (0xFU << GRF_GPIO1B_IOMUX_H_GPIO1B7_SEL_SHIFT)               /* 0x0000F000 */
/* GPIO1C_IOMUX_L */
#define GRF_GPIO1C_IOMUX_L_OFFSET                          (0x30U)
#define GRF_GPIO1C_IOMUX_L_GPIO1C0_SEL_SHIFT               (0U)
#define GRF_GPIO1C_IOMUX_L_GPIO1C0_SEL_MASK                (0xFU << GRF_GPIO1C_IOMUX_L_GPIO1C0_SEL_SHIFT)               /* 0x0000000F */
#define GRF_GPIO1C_IOMUX_L_GPIO1C1_SEL_SHIFT               (4U)
#define GRF_GPIO1C_IOMUX_L_GPIO1C1_SEL_MASK                (0xFU << GRF_GPIO1C_IOMUX_L_GPIO1C1_SEL_SHIFT)               /* 0x000000F0 */
#define GRF_GPIO1C_IOMUX_L_GPIO1C2_SEL_SHIFT               (8U)
#define GRF_GPIO1C_IOMUX_L_GPIO1C2_SEL_MASK                (0xFU << GRF_GPIO1C_IOMUX_L_GPIO1C2_SEL_SHIFT)               /* 0x00000F00 */
#define GRF_GPIO1C_IOMUX_L_GPIO1C3_SEL_SHIFT               (12U)
#define GRF_GPIO1C_IOMUX_L_GPIO1C3_SEL_MASK                (0xFU << GRF_GPIO1C_IOMUX_L_GPIO1C3_SEL_SHIFT)               /* 0x0000F000 */
/* GPIO1C_IOMUX_H */
#define GRF_GPIO1C_IOMUX_H_OFFSET                          (0x34U)
#define GRF_GPIO1C_IOMUX_H_GPIO1C4_SEL_SHIFT               (0U)
#define GRF_GPIO1C_IOMUX_H_GPIO1C4_SEL_MASK                (0xFU << GRF_GPIO1C_IOMUX_H_GPIO1C4_SEL_SHIFT)               /* 0x0000000F */
#define GRF_GPIO1C_IOMUX_H_GPIO1C5_SEL_SHIFT               (4U)
#define GRF_GPIO1C_IOMUX_H_GPIO1C5_SEL_MASK                (0xFU << GRF_GPIO1C_IOMUX_H_GPIO1C5_SEL_SHIFT)               /* 0x000000F0 */
#define GRF_GPIO1C_IOMUX_H_GPIO1C6_SEL_SHIFT               (8U)
#define GRF_GPIO1C_IOMUX_H_GPIO1C6_SEL_MASK                (0xFU << GRF_GPIO1C_IOMUX_H_GPIO1C6_SEL_SHIFT)               /* 0x00000F00 */
#define GRF_GPIO1C_IOMUX_H_GPIO1C7_SEL_SHIFT               (12U)
#define GRF_GPIO1C_IOMUX_H_GPIO1C7_SEL_MASK                (0xFU << GRF_GPIO1C_IOMUX_H_GPIO1C7_SEL_SHIFT)               /* 0x0000F000 */
/* GPIO1D_IOMUX_L */
#define GRF_GPIO1D_IOMUX_L_OFFSET                          (0x38U)
#define GRF_GPIO1D_IOMUX_L_GPIO1D0_SEL_SHIFT               (0U)
#define GRF_GPIO1D_IOMUX_L_GPIO1D0_SEL_MASK                (0xFU << GRF_GPIO1D_IOMUX_L_GPIO1D0_SEL_SHIFT)               /* 0x0000000F */
/* GPIO0L_SR */
#define GRF_GPIO0L_SR_OFFSET                               (0x40U)
#define GRF_GPIO0L_SR_GPIO0A_SR_SHIFT                      (0U)
#define GRF_GPIO0L_SR_GPIO0A_SR_MASK                       (0xFFU << GRF_GPIO0L_SR_GPIO0A_SR_SHIFT)                     /* 0x000000FF */
#define GRF_GPIO0L_SR_GPIO0B_SR_SHIFT                      (8U)
#define GRF_GPIO0L_SR_GPIO0B_SR_MASK                       (0xFFU << GRF_GPIO0L_SR_GPIO0B_SR_SHIFT)                     /* 0x0000FF00 */
/* GPIO0H_SR */
#define GRF_GPIO0H_SR_OFFSET                               (0x44U)
#define GRF_GPIO0H_SR_GPIO0C_SR_SHIFT                      (0U)
#define GRF_GPIO0H_SR_GPIO0C_SR_MASK                       (0xFFU << GRF_GPIO0H_SR_GPIO0C_SR_SHIFT)                     /* 0x000000FF */
#define GRF_GPIO0H_SR_GPIO0D_SR_SHIFT                      (8U)
#define GRF_GPIO0H_SR_GPIO0D_SR_MASK                       (0xFFU << GRF_GPIO0H_SR_GPIO0D_SR_SHIFT)                     /* 0x0000FF00 */
/* GPIO1L_SR */
#define GRF_GPIO1L_SR_OFFSET                               (0x48U)
#define GRF_GPIO1L_SR_GPIO1A_SR_SHIFT                      (0U)
#define GRF_GPIO1L_SR_GPIO1A_SR_MASK                       (0xFFU << GRF_GPIO1L_SR_GPIO1A_SR_SHIFT)                     /* 0x000000FF */
#define GRF_GPIO1L_SR_GPIO1B_SR_SHIFT                      (8U)
#define GRF_GPIO1L_SR_GPIO1B_SR_MASK                       (0xFFU << GRF_GPIO1L_SR_GPIO1B_SR_SHIFT)                     /* 0x0000FF00 */
/* GPIO1H_SR */
#define GRF_GPIO1H_SR_OFFSET                               (0x4CU)
#define GRF_GPIO1H_SR_GPIO1C_SR_SHIFT                      (0U)
#define GRF_GPIO1H_SR_GPIO1C_SR_MASK                       (0xFFU << GRF_GPIO1H_SR_GPIO1C_SR_SHIFT)                     /* 0x000000FF */
#define GRF_GPIO1H_SR_GPIO1D_SR_SHIFT                      (8U)
#define GRF_GPIO1H_SR_GPIO1D_SR_MASK                       (0x1U << GRF_GPIO1H_SR_GPIO1D_SR_SHIFT)                      /* 0x00000100 */
/* GPIO0A_P */
#define GRF_GPIO0A_P_OFFSET                                (0x80U)
#define GRF_GPIO0A_P_GPIO0A_P_SHIFT                        (0U)
#define GRF_GPIO0A_P_GPIO0A_P_MASK                         (0xFFFFU << GRF_GPIO0A_P_GPIO0A_P_SHIFT)                     /* 0x0000FFFF */
/* GPIO0B_P */
#define GRF_GPIO0B_P_OFFSET                                (0x84U)
#define GRF_GPIO0B_P_GPIO0B_P_SHIFT                        (0U)
#define GRF_GPIO0B_P_GPIO0B_P_MASK                         (0xFFFFU << GRF_GPIO0B_P_GPIO0B_P_SHIFT)                     /* 0x0000FFFF */
/* GPIO0C_P */
#define GRF_GPIO0C_P_OFFSET                                (0x88U)
#define GRF_GPIO0C_P_GPIO0C_P_SHIFT                        (0U)
#define GRF_GPIO0C_P_GPIO0C_P_MASK                         (0xFFFFU << GRF_GPIO0C_P_GPIO0C_P_SHIFT)                     /* 0x0000FFFF */
/* GPIO0D_P */
#define GRF_GPIO0D_P_OFFSET                                (0x8CU)
#define GRF_GPIO0D_P_GPIO0D_P_SHIFT                        (0U)
#define GRF_GPIO0D_P_GPIO0D_P_MASK                         (0xFFFFU << GRF_GPIO0D_P_GPIO0D_P_SHIFT)                     /* 0x0000FFFF */
/* GPIO1A_P */
#define GRF_GPIO1A_P_OFFSET                                (0x90U)
#define GRF_GPIO1A_P_GPIO1A_P_SHIFT                        (0U)
#define GRF_GPIO1A_P_GPIO1A_P_MASK                         (0xFFFFU << GRF_GPIO1A_P_GPIO1A_P_SHIFT)                     /* 0x0000FFFF */
/* GPIO1B_P */
#define GRF_GPIO1B_P_OFFSET                                (0x94U)
#define GRF_GPIO1B_P_GPIO1B_P_SHIFT                        (0U)
#define GRF_GPIO1B_P_GPIO1B_P_MASK                         (0xFFFFU << GRF_GPIO1B_P_GPIO1B_P_SHIFT)                     /* 0x0000FFFF */
/* GPIO1C_P */
#define GRF_GPIO1C_P_OFFSET                                (0x98U)
#define GRF_GPIO1C_P_GPIO1C_P_SHIFT                        (0U)
#define GRF_GPIO1C_P_GPIO1C_P_MASK                         (0xFFFFU << GRF_GPIO1C_P_GPIO1C_P_SHIFT)                     /* 0x0000FFFF */
/* GPIO1D_P */
#define GRF_GPIO1D_P_OFFSET                                (0x9CU)
#define GRF_GPIO1D_P_GPIO1D_P_SHIFT                        (0U)
#define GRF_GPIO1D_P_GPIO1D_P_MASK                         (0x3U << GRF_GPIO1D_P_GPIO1D_P_SHIFT)                        /* 0x00000003 */
/* GPIO0A_E */
#define GRF_GPIO0A_E_OFFSET                                (0xC0U)
#define GRF_GPIO0A_E_GPIO0A_E_SHIFT                        (0U)
#define GRF_GPIO0A_E_GPIO0A_E_MASK                         (0xFFFFU << GRF_GPIO0A_E_GPIO0A_E_SHIFT)                     /* 0x0000FFFF */
/* GPIO0B_E */
#define GRF_GPIO0B_E_OFFSET                                (0xC4U)
#define GRF_GPIO0B_E_GPIO0B_E_SHIFT                        (0U)
#define GRF_GPIO0B_E_GPIO0B_E_MASK                         (0xFFFFU << GRF_GPIO0B_E_GPIO0B_E_SHIFT)                     /* 0x0000FFFF */
/* GPIO0C_E */
#define GRF_GPIO0C_E_OFFSET                                (0xC8U)
#define GRF_GPIO0C_E_GPIO0C_E_SHIFT                        (0U)
#define GRF_GPIO0C_E_GPIO0C_E_MASK                         (0xFFFFU << GRF_GPIO0C_E_GPIO0C_E_SHIFT)                     /* 0x0000FFFF */
/* GPIO0D_E */
#define GRF_GPIO0D_E_OFFSET                                (0xCCU)
#define GRF_GPIO0D_E_GPIO0D_E_SHIFT                        (0U)
#define GRF_GPIO0D_E_GPIO0D_E_MASK                         (0xFFFFU << GRF_GPIO0D_E_GPIO0D_E_SHIFT)                     /* 0x0000FFFF */
/* GPIO1A_E */
#define GRF_GPIO1A_E_OFFSET                                (0xD0U)
#define GRF_GPIO1A_E_GPIO1A_E_SHIFT                        (0U)
#define GRF_GPIO1A_E_GPIO1A_E_MASK                         (0xFFFFU << GRF_GPIO1A_E_GPIO1A_E_SHIFT)                     /* 0x0000FFFF */
/* GPIO1B_E */
#define GRF_GPIO1B_E_OFFSET                                (0xD4U)
#define GRF_GPIO1B_E_GPIO1B_E_SHIFT                        (0U)
#define GRF_GPIO1B_E_GPIO1B_E_MASK                         (0xFFFFU << GRF_GPIO1B_E_GPIO1B_E_SHIFT)                     /* 0x0000FFFF */
/* GPIO1C_E */
#define GRF_GPIO1C_E_OFFSET                                (0xD8U)
#define GRF_GPIO1C_E_GPIO1C_E_SHIFT                        (0U)
#define GRF_GPIO1C_E_GPIO1C_E_MASK                         (0xFFFFU << GRF_GPIO1C_E_GPIO1C_E_SHIFT)                     /* 0x0000FFFF */
/* GPIO1D_E */
#define GRF_GPIO1D_E_OFFSET                                (0xDCU)
#define GRF_GPIO1D_E_GPIO1D_E_SHIFT                        (0U)
#define GRF_GPIO1D_E_GPIO1D_E_MASK                         (0x3U << GRF_GPIO1D_E_GPIO1D_E_SHIFT)                        /* 0x00000003 */
/* CHIP_VERSION_ID */
#define GRF_CHIP_VERSION_ID_OFFSET                         (0xF0U)
#define GRF_CHIP_VERSION_ID                                (0x0U)
#define GRF_CHIP_VERSION_ID_CHIP_VERSION_ID_SHIFT          (0U)
#define GRF_CHIP_VERSION_ID_CHIP_VERSION_ID_MASK           (0xFFFFFFFFU << GRF_CHIP_VERSION_ID_CHIP_VERSION_ID_SHIFT)   /* 0xFFFFFFFF */
/* CHIP_IDL */
#define GRF_CHIP_IDL_OFFSET                                (0xF4U)
#define GRF_CHIP_IDL                                       (0x4F4C5043U)
#define GRF_CHIP_IDL_CHIP_IDL_SHIFT                        (0U)
#define GRF_CHIP_IDL_CHIP_IDL_MASK                         (0xFFFFFFFFU << GRF_CHIP_IDL_CHIP_IDL_SHIFT)                 /* 0xFFFFFFFF */
/* CHIP_IDH */
#define GRF_CHIP_IDH_OFFSET                                (0xF8U)
#define GRF_CHIP_IDH                                       (0x6F70706FU)
#define GRF_CHIP_IDH_CHIP_IDH_SHIFT                        (0U)
#define GRF_CHIP_IDH_CHIP_IDH_MASK                         (0xFFFFFFFFU << GRF_CHIP_IDH_CHIP_IDH_SHIFT)                 /* 0xFFFFFFFF */
/* SOC_CON0 */
#define GRF_SOC_CON0_OFFSET                                (0x100U)
#define GRF_SOC_CON0_I2C_FLT_F_SHIFT                       (0U)
#define GRF_SOC_CON0_I2C_FLT_F_MASK                        (0xFU << GRF_SOC_CON0_I2C_FLT_F_SHIFT)                       /* 0x0000000F */
#define GRF_SOC_CON0_I2C_FLT_R_SHIFT                       (4U)
#define GRF_SOC_CON0_I2C_FLT_R_MASK                        (0xFU << GRF_SOC_CON0_I2C_FLT_R_SHIFT)                       /* 0x000000F0 */
#define GRF_SOC_CON0_UART0_RTS_SEL_SHIFT                   (8U)
#define GRF_SOC_CON0_UART0_RTS_SEL_MASK                    (0x1U << GRF_SOC_CON0_UART0_RTS_SEL_SHIFT)                   /* 0x00000100 */
#define GRF_SOC_CON0_UART0_CTS_SEL_SHIFT                   (9U)
#define GRF_SOC_CON0_UART0_CTS_SEL_MASK                    (0x1U << GRF_SOC_CON0_UART0_CTS_SEL_SHIFT)                   /* 0x00000200 */
#define GRF_SOC_CON0_UART2_RTS_SEL_SHIFT                   (12U)
#define GRF_SOC_CON0_UART2_RTS_SEL_MASK                    (0x1U << GRF_SOC_CON0_UART2_RTS_SEL_SHIFT)                   /* 0x00001000 */
#define GRF_SOC_CON0_UART2_CTS_SEL_SHIFT                   (13U)
#define GRF_SOC_CON0_UART2_CTS_SEL_MASK                    (0x1U << GRF_SOC_CON0_UART2_CTS_SEL_SHIFT)                   /* 0x00002000 */
#define GRF_SOC_CON0_VOP_TE_SEL_SHIFT                      (14U)
#define GRF_SOC_CON0_VOP_TE_SEL_MASK                       (0x3U << GRF_SOC_CON0_VOP_TE_SEL_SHIFT)                      /* 0x0000C000 */
/* SOC_CON1 */
#define GRF_SOC_CON1_OFFSET                                (0x104U)
#define GRF_SOC_CON1_TOP_FWD_DSP_STALL_SHIFT               (0U)
#define GRF_SOC_CON1_TOP_FWD_DSP_STALL_MASK                (0x1U << GRF_SOC_CON1_TOP_FWD_DSP_STALL_SHIFT)               /* 0x00000001 */
#define GRF_SOC_CON1_DSP_FWD_TOP_STALL_SHIFT               (1U)
#define GRF_SOC_CON1_DSP_FWD_TOP_STALL_MASK                (0x1U << GRF_SOC_CON1_DSP_FWD_TOP_STALL_SHIFT)               /* 0x00000002 */
#define GRF_SOC_CON1_TOP_FWD_SHRM0_STALL_SHIFT             (2U)
#define GRF_SOC_CON1_TOP_FWD_SHRM0_STALL_MASK              (0x1U << GRF_SOC_CON1_TOP_FWD_SHRM0_STALL_SHIFT)             /* 0x00000004 */
#define GRF_SOC_CON1_TOP_FWD_SHRM1_STALL_SHIFT             (3U)
#define GRF_SOC_CON1_TOP_FWD_SHRM1_STALL_MASK              (0x1U << GRF_SOC_CON1_TOP_FWD_SHRM1_STALL_SHIFT)             /* 0x00000008 */
#define GRF_SOC_CON1_TOP_FWD_SHRM2_STALL_SHIFT             (4U)
#define GRF_SOC_CON1_TOP_FWD_SHRM2_STALL_MASK              (0x1U << GRF_SOC_CON1_TOP_FWD_SHRM2_STALL_SHIFT)             /* 0x00000010 */
#define GRF_SOC_CON1_TOP_FWD_AUDIO_STALL_SHIFT             (5U)
#define GRF_SOC_CON1_TOP_FWD_AUDIO_STALL_MASK              (0x1U << GRF_SOC_CON1_TOP_FWD_AUDIO_STALL_SHIFT)             /* 0x00000020 */
#define GRF_SOC_CON1_TOP_FWD_ALIVE_STALL_SHIFT             (6U)
#define GRF_SOC_CON1_TOP_FWD_ALIVE_STALL_MASK              (0x1U << GRF_SOC_CON1_TOP_FWD_ALIVE_STALL_SHIFT)             /* 0x00000040 */
#define GRF_SOC_CON1_AUDIO_FWD_TOP_STALL_SHIFT             (7U)
#define GRF_SOC_CON1_AUDIO_FWD_TOP_STALL_MASK              (0x1U << GRF_SOC_CON1_AUDIO_FWD_TOP_STALL_SHIFT)             /* 0x00000080 */
#define GRF_SOC_CON1_AUDIO_FWD_DSP_STALL_SHIFT             (8U)
#define GRF_SOC_CON1_AUDIO_FWD_DSP_STALL_MASK              (0x1U << GRF_SOC_CON1_AUDIO_FWD_DSP_STALL_SHIFT)             /* 0x00000100 */
#define GRF_SOC_CON1_DSP_FWD_ALIVE_STALL_SHIFT             (9U)
#define GRF_SOC_CON1_DSP_FWD_ALIVE_STALL_MASK              (0x1U << GRF_SOC_CON1_DSP_FWD_ALIVE_STALL_SHIFT)             /* 0x00000200 */
#define GRF_SOC_CON1_DSP_FWD_AUDIO_STALL_SHIFT             (10U)
#define GRF_SOC_CON1_DSP_FWD_AUDIO_STALL_MASK              (0x1U << GRF_SOC_CON1_DSP_FWD_AUDIO_STALL_SHIFT)             /* 0x00000400 */
#define GRF_SOC_CON1_DPISHUTDN_SHIFT                       (12U)
#define GRF_SOC_CON1_DPISHUTDN_MASK                        (0x1U << GRF_SOC_CON1_DPISHUTDN_SHIFT)                       /* 0x00001000 */
#define GRF_SOC_CON1_DPICOLORM_SHIFT                       (13U)
#define GRF_SOC_CON1_DPICOLORM_MASK                        (0x1U << GRF_SOC_CON1_DPICOLORM_SHIFT)                       /* 0x00002000 */
#define GRF_SOC_CON1_DPIUPDATECFG_SHIFT                    (14U)
#define GRF_SOC_CON1_DPIUPDATECFG_MASK                     (0x1U << GRF_SOC_CON1_DPIUPDATECFG_SHIFT)                    /* 0x00004000 */
#define GRF_SOC_CON1_PHYLOCK_SHIFT                         (15U)
#define GRF_SOC_CON1_PHYLOCK_MASK                          (0x1U << GRF_SOC_CON1_PHYLOCK_SHIFT)                         /* 0x00008000 */
/* SOC_CON2 */
#define GRF_SOC_CON2_OFFSET                                (0x108U)
#define GRF_SOC_CON2_GRF_CON_AUDIO_BYPASS_EN_SHIFT         (0U)
#define GRF_SOC_CON2_GRF_CON_AUDIO_BYPASS_EN_MASK          (0x1U << GRF_SOC_CON2_GRF_CON_AUDIO_BYPASS_EN_SHIFT)         /* 0x00000001 */
#define GRF_SOC_CON2_GRF_CON_I2S_BYPASS_MST_SHIFT          (1U)
#define GRF_SOC_CON2_GRF_CON_I2S_BYPASS_MST_MASK           (0x1U << GRF_SOC_CON2_GRF_CON_I2S_BYPASS_MST_SHIFT)          /* 0x00000002 */
#define GRF_SOC_CON2_GRF_CON_CODEC_SEL_SHIFT               (2U)
#define GRF_SOC_CON2_GRF_CON_CODEC_SEL_MASK                (0x1U << GRF_SOC_CON2_GRF_CON_CODEC_SEL_SHIFT)               /* 0x00000004 */
#define GRF_SOC_CON2_GRF_CON_I2S_LRCK_MUX_SHIFT            (3U)
#define GRF_SOC_CON2_GRF_CON_I2S_LRCK_MUX_MASK             (0x1U << GRF_SOC_CON2_GRF_CON_I2S_LRCK_MUX_SHIFT)            /* 0x00000008 */
#define GRF_SOC_CON2_GRF_CON_I2S_SCLK_MUX_SHIFT            (4U)
#define GRF_SOC_CON2_GRF_CON_I2S_SCLK_MUX_MASK             (0x1U << GRF_SOC_CON2_GRF_CON_I2S_SCLK_MUX_SHIFT)            /* 0x00000010 */
#define GRF_SOC_CON2_GRF_CON_I2S_IN_MCLK_SRC_SHIFT         (5U)
#define GRF_SOC_CON2_GRF_CON_I2S_IN_MCLK_SRC_MASK          (0x1U << GRF_SOC_CON2_GRF_CON_I2S_IN_MCLK_SRC_SHIFT)         /* 0x00000020 */
#define GRF_SOC_CON2_GRF_CON_I2S_IN_MCLK_OUT_EN_SHIFT      (6U)
#define GRF_SOC_CON2_GRF_CON_I2S_IN_MCLK_OUT_EN_MASK       (0x1U << GRF_SOC_CON2_GRF_CON_I2S_IN_MCLK_OUT_EN_SHIFT)      /* 0x00000040 */
#define GRF_SOC_CON2_GRF_CON_I2S_OUT_MCLK_OUT_EN_SHIFT     (7U)
#define GRF_SOC_CON2_GRF_CON_I2S_OUT_MCLK_OUT_EN_MASK      (0x1U << GRF_SOC_CON2_GRF_CON_I2S_OUT_MCLK_OUT_EN_SHIFT)     /* 0x00000080 */
#define GRF_SOC_CON2_GRF_CON_PDM_IN_CLK0_BY_CLK_SEL_SHIFT  (8U)
#define GRF_SOC_CON2_GRF_CON_PDM_IN_CLK0_BY_CLK_SEL_MASK   (0x1U << GRF_SOC_CON2_GRF_CON_PDM_IN_CLK0_BY_CLK_SEL_SHIFT)  /* 0x00000100 */
#define GRF_SOC_CON2_GRF_CON_PDM_IN_CLK1_BY_CLK_SEL_SHIFT  (9U)
#define GRF_SOC_CON2_GRF_CON_PDM_IN_CLK1_BY_CLK_SEL_MASK   (0x1U << GRF_SOC_CON2_GRF_CON_PDM_IN_CLK1_BY_CLK_SEL_SHIFT)  /* 0x00000200 */
#define GRF_SOC_CON2_GRF_CON_PDM_IN_CLK_BY_CLK_CRU_SEL_SHIFT (10U)
#define GRF_SOC_CON2_GRF_CON_PDM_IN_CLK_BY_CLK_CRU_SEL_MASK (0x1U << GRF_SOC_CON2_GRF_CON_PDM_IN_CLK_BY_CLK_CRU_SEL_SHIFT) /* 0x00000400 */
#define GRF_SOC_CON2_GRF_CON_PDM_OUT_CLK_OE_SHIFT          (11U)
#define GRF_SOC_CON2_GRF_CON_PDM_OUT_CLK_OE_MASK           (0x1U << GRF_SOC_CON2_GRF_CON_PDM_OUT_CLK_OE_SHIFT)          /* 0x00000800 */
#define GRF_SOC_CON2_GRF_CON_PDM_COMB_EN_SHIFT             (12U)
#define GRF_SOC_CON2_GRF_CON_PDM_COMB_EN_MASK              (0x1U << GRF_SOC_CON2_GRF_CON_PDM_COMB_EN_SHIFT)             /* 0x00001000 */
#define GRF_SOC_CON2_GRF_CON_PDM_COMB_LR_SEL_SHIFT         (13U)
#define GRF_SOC_CON2_GRF_CON_PDM_COMB_LR_SEL_MASK          (0x1U << GRF_SOC_CON2_GRF_CON_PDM_COMB_LR_SEL_SHIFT)         /* 0x00002000 */
#define GRF_SOC_CON2_GRF_CON_PDM_COMB_BY_CLK_SEL_SHIFT     (14U)
#define GRF_SOC_CON2_GRF_CON_PDM_COMB_BY_CLK_SEL_MASK      (0x1U << GRF_SOC_CON2_GRF_CON_PDM_COMB_BY_CLK_SEL_SHIFT)     /* 0x00004000 */
#define GRF_SOC_CON2_GRF_CON_AUDIO_BYPASS_CTRL_SEL_SHIFT   (15U)
#define GRF_SOC_CON2_GRF_CON_AUDIO_BYPASS_CTRL_SEL_MASK    (0x1U << GRF_SOC_CON2_GRF_CON_AUDIO_BYPASS_CTRL_SEL_SHIFT)   /* 0x00008000 */
/* SOC_CON3 */
#define GRF_SOC_CON3_OFFSET                                (0x10CU)
#define GRF_SOC_CON3_GRF_CON_MCLK_DIV2_SEL_SHIFT           (0U)
#define GRF_SOC_CON3_GRF_CON_MCLK_DIV2_SEL_MASK            (0x1U << GRF_SOC_CON3_GRF_CON_MCLK_DIV2_SEL_SHIFT)           /* 0x00000001 */
#define GRF_SOC_CON3_GRF_CON_MAINCLKIN_SMT_SHIFT           (1U)
#define GRF_SOC_CON3_GRF_CON_MAINCLKIN_SMT_MASK            (0x3U << GRF_SOC_CON3_GRF_CON_MAINCLKIN_SMT_SHIFT)           /* 0x00000006 */
#define GRF_SOC_CON3_GRF_CON_OSC_S_SHIFT                   (4U)
#define GRF_SOC_CON3_GRF_CON_OSC_S_MASK                    (0x1FU << GRF_SOC_CON3_GRF_CON_OSC_S_SHIFT)                  /* 0x000001F0 */
#define GRF_SOC_CON3_GRF_CON_OSC_FEB_SHIFT                 (9U)
#define GRF_SOC_CON3_GRF_CON_OSC_FEB_MASK                  (0x1U << GRF_SOC_CON3_GRF_CON_OSC_FEB_SHIFT)                 /* 0x00000200 */
#define GRF_SOC_CON3_GRF_CON_MIPI_SWITCH_EN_PRO_BYP_SHIFT  (12U)
#define GRF_SOC_CON3_GRF_CON_MIPI_SWITCH_EN_PRO_BYP_MASK   (0x1U << GRF_SOC_CON3_GRF_CON_MIPI_SWITCH_EN_PRO_BYP_SHIFT)  /* 0x00001000 */
/* SOC_CON4 */
#define GRF_SOC_CON4_OFFSET                                (0x110U)
#define GRF_SOC_CON4_GRF_CON_MIPI_SWITCH_CTRL_SHIFT        (0U)
#define GRF_SOC_CON4_GRF_CON_MIPI_SWITCH_CTRL_MASK         (0x1U << GRF_SOC_CON4_GRF_CON_MIPI_SWITCH_CTRL_SHIFT)        /* 0x00000001 */
#define GRF_SOC_CON4_GRF_CON_LCD_RESET_TE_BYPASS_SHIFT     (1U)
#define GRF_SOC_CON4_GRF_CON_LCD_RESET_TE_BYPASS_MASK      (0x1U << GRF_SOC_CON4_GRF_CON_LCD_RESET_TE_BYPASS_SHIFT)     /* 0x00000002 */
#define GRF_SOC_CON4_GRF_CON_LCD_RESETN_SHIFT              (2U)
#define GRF_SOC_CON4_GRF_CON_LCD_RESETN_MASK               (0x1U << GRF_SOC_CON4_GRF_CON_LCD_RESETN_SHIFT)              /* 0x00000004 */
#define GRF_SOC_CON4_GRF_CON_LDO_OUT_PWR_EN_SHIFT          (3U)
#define GRF_SOC_CON4_GRF_CON_LDO_OUT_PWR_EN_MASK           (0x1U << GRF_SOC_CON4_GRF_CON_LDO_OUT_PWR_EN_SHIFT)          /* 0x00000008 */
#define GRF_SOC_CON4_GRF_CON_TP_RESETN_SHIFT               (4U)
#define GRF_SOC_CON4_GRF_CON_TP_RESETN_MASK                (0x1U << GRF_SOC_CON4_GRF_CON_TP_RESETN_SHIFT)               /* 0x00000010 */
#define GRF_SOC_CON4_GRF_CON_CLK_OUT_EN_SHIFT              (5U)
#define GRF_SOC_CON4_GRF_CON_CLK_OUT_EN_MASK               (0x1U << GRF_SOC_CON4_GRF_CON_CLK_OUT_EN_SHIFT)              /* 0x00000020 */
#define GRF_SOC_CON4_GRF_CON_MIPI_SWITCH_CTRL_SEL_SHIFT    (6U)
#define GRF_SOC_CON4_GRF_CON_MIPI_SWITCH_CTRL_SEL_MASK     (0x1U << GRF_SOC_CON4_GRF_CON_MIPI_SWITCH_CTRL_SEL_SHIFT)    /* 0x00000040 */
#define GRF_SOC_CON4_GRF_CON_I2S_BYPASS_PROC_EN_SHIFT      (7U)
#define GRF_SOC_CON4_GRF_CON_I2S_BYPASS_PROC_EN_MASK       (0x1U << GRF_SOC_CON4_GRF_CON_I2S_BYPASS_PROC_EN_SHIFT)      /* 0x00000080 */
#define GRF_SOC_CON4_GRF_CON_AUDIO_PRO_APP_PDM_SHIFT       (8U)
#define GRF_SOC_CON4_GRF_CON_AUDIO_PRO_APP_PDM_MASK        (0x1U << GRF_SOC_CON4_GRF_CON_AUDIO_PRO_APP_PDM_SHIFT)       /* 0x00000100 */
#define GRF_SOC_CON4_GRF_CON_AUDIO_PRO_APP_I2S1_SHIFT      (9U)
#define GRF_SOC_CON4_GRF_CON_AUDIO_PRO_APP_I2S1_MASK       (0x1U << GRF_SOC_CON4_GRF_CON_AUDIO_PRO_APP_I2S1_SHIFT)      /* 0x00000200 */
#define GRF_SOC_CON4_GRF_CON_I2S1_SDI2_FROM_IO_SHIFT       (10U)
#define GRF_SOC_CON4_GRF_CON_I2S1_SDI2_FROM_IO_MASK        (0x1U << GRF_SOC_CON4_GRF_CON_I2S1_SDI2_FROM_IO_SHIFT)       /* 0x00000400 */
#define GRF_SOC_CON4_GRF_CON_BT_PCM_I2S0_SHIFT             (11U)
#define GRF_SOC_CON4_GRF_CON_BT_PCM_I2S0_MASK              (0x1U << GRF_SOC_CON4_GRF_CON_BT_PCM_I2S0_SHIFT)             /* 0x00000800 */
#define GRF_SOC_CON4_GRF_CON_USB2_DBNCE_FLTR_BYPASS_SHIFT  (13U)
#define GRF_SOC_CON4_GRF_CON_USB2_DBNCE_FLTR_BYPASS_MASK   (0x1U << GRF_SOC_CON4_GRF_CON_USB2_DBNCE_FLTR_BYPASS_SHIFT)  /* 0x00002000 */
#define GRF_SOC_CON4_GRF_CON_USB2_SCALEDOWN_MODE_SHIFT     (14U)
#define GRF_SOC_CON4_GRF_CON_USB2_SCALEDOWN_MODE_MASK      (0x3U << GRF_SOC_CON4_GRF_CON_USB2_SCALEDOWN_MODE_SHIFT)     /* 0x0000C000 */
/* SOC_CON5 */
#define GRF_SOC_CON5_OFFSET                                (0x114U)
#define GRF_SOC_CON5_GRF_CON_I2C_MST0_IOMUX_SEL_SHIFT      (0U)
#define GRF_SOC_CON5_GRF_CON_I2C_MST0_IOMUX_SEL_MASK       (0x3U << GRF_SOC_CON5_GRF_CON_I2C_MST0_IOMUX_SEL_SHIFT)      /* 0x00000003 */
#define GRF_SOC_CON5_GRF_CON_I2C_MST1_IOMUX_SEL_SHIFT      (2U)
#define GRF_SOC_CON5_GRF_CON_I2C_MST1_IOMUX_SEL_MASK       (0x3U << GRF_SOC_CON5_GRF_CON_I2C_MST1_IOMUX_SEL_SHIFT)      /* 0x0000000C */
#define GRF_SOC_CON5_GRF_CON_I2C_MST2_IOMUX_SEL_SHIFT      (4U)
#define GRF_SOC_CON5_GRF_CON_I2C_MST2_IOMUX_SEL_MASK       (0x3U << GRF_SOC_CON5_GRF_CON_I2C_MST2_IOMUX_SEL_SHIFT)      /* 0x00000030 */
#define GRF_SOC_CON5_GRF_CON_PCM_IOMUX_SEL_SHIFT           (6U)
#define GRF_SOC_CON5_GRF_CON_PCM_IOMUX_SEL_MASK            (0x1U << GRF_SOC_CON5_GRF_CON_PCM_IOMUX_SEL_SHIFT)           /* 0x00000040 */
#define GRF_SOC_CON5_GRF_CON_UART1_IOMUX_SEL_SHIFT         (7U)
#define GRF_SOC_CON5_GRF_CON_UART1_IOMUX_SEL_MASK          (0x3U << GRF_SOC_CON5_GRF_CON_UART1_IOMUX_SEL_SHIFT)         /* 0x00000180 */
#define GRF_SOC_CON5_GRF_CON_SPI_MST1_IOMUX_SEL_SHIFT      (9U)
#define GRF_SOC_CON5_GRF_CON_SPI_MST1_IOMUX_SEL_MASK       (0x1U << GRF_SOC_CON5_GRF_CON_SPI_MST1_IOMUX_SEL_SHIFT)      /* 0x00000200 */
#define GRF_SOC_CON5_GRF_CON_SPI_MST2_IOMUX_SEL_SHIFT      (10U)
#define GRF_SOC_CON5_GRF_CON_SPI_MST2_IOMUX_SEL_MASK       (0x1U << GRF_SOC_CON5_GRF_CON_SPI_MST2_IOMUX_SEL_SHIFT)      /* 0x00000400 */
#define GRF_SOC_CON5_GRF_CON_I2S1_IOMUX_SEL_SHIFT          (11U)
#define GRF_SOC_CON5_GRF_CON_I2S1_IOMUX_SEL_MASK           (0x1U << GRF_SOC_CON5_GRF_CON_I2S1_IOMUX_SEL_SHIFT)          /* 0x00000800 */
#define GRF_SOC_CON5_GRF_CON_PCMCLK_IOMUX_SEL_SHIFT        (12U)
#define GRF_SOC_CON5_GRF_CON_PCMCLK_IOMUX_SEL_MASK         (0x1U << GRF_SOC_CON5_GRF_CON_PCMCLK_IOMUX_SEL_SHIFT)        /* 0x00001000 */
#define GRF_SOC_CON5_GRF_CON_KEY_IOMUX_SEL_SHIFT           (13U)
#define GRF_SOC_CON5_GRF_CON_KEY_IOMUX_SEL_MASK            (0x3U << GRF_SOC_CON5_GRF_CON_KEY_IOMUX_SEL_SHIFT)           /* 0x00006000 */
/* SOC_STATUS0 */
#define GRF_SOC_STATUS0_OFFSET                             (0x140U)
#define GRF_SOC_STATUS0                                    (0x0U)
#define GRF_SOC_STATUS0_DSP_FWD_TOP_PWRACT_SHIFT           (0U)
#define GRF_SOC_STATUS0_DSP_FWD_TOP_PWRACT_MASK            (0x1U << GRF_SOC_STATUS0_DSP_FWD_TOP_PWRACT_SHIFT)           /* 0x00000001 */
#define GRF_SOC_STATUS0_TOP_FWD_DSP_PWRACT_SHIFT           (1U)
#define GRF_SOC_STATUS0_TOP_FWD_DSP_PWRACT_MASK            (0x1U << GRF_SOC_STATUS0_TOP_FWD_DSP_PWRACT_SHIFT)           /* 0x00000002 */
#define GRF_SOC_STATUS0_TOP_FWD_SHRM0_PWRACT_SHIFT         (2U)
#define GRF_SOC_STATUS0_TOP_FWD_SHRM0_PWRACT_MASK          (0x1U << GRF_SOC_STATUS0_TOP_FWD_SHRM0_PWRACT_SHIFT)         /* 0x00000004 */
#define GRF_SOC_STATUS0_TOP_FWD_SHRM1_PWRACT_SHIFT         (3U)
#define GRF_SOC_STATUS0_TOP_FWD_SHRM1_PWRACT_MASK          (0x1U << GRF_SOC_STATUS0_TOP_FWD_SHRM1_PWRACT_SHIFT)         /* 0x00000008 */
#define GRF_SOC_STATUS0_TOP_FWD_SHRM2_PWRACT_SHIFT         (4U)
#define GRF_SOC_STATUS0_TOP_FWD_SHRM2_PWRACT_MASK          (0x1U << GRF_SOC_STATUS0_TOP_FWD_SHRM2_PWRACT_SHIFT)         /* 0x00000010 */
#define GRF_SOC_STATUS0_TOP_FWD_AUDIO_PWRACT_SHIFT         (5U)
#define GRF_SOC_STATUS0_TOP_FWD_AUDIO_PWRACT_MASK          (0x1U << GRF_SOC_STATUS0_TOP_FWD_AUDIO_PWRACT_SHIFT)         /* 0x00000020 */
#define GRF_SOC_STATUS0_TOP_FWD_ALIVE_PWRACT_SHIFT         (6U)
#define GRF_SOC_STATUS0_TOP_FWD_ALIVE_PWRACT_MASK          (0x1U << GRF_SOC_STATUS0_TOP_FWD_ALIVE_PWRACT_SHIFT)         /* 0x00000040 */
#define GRF_SOC_STATUS0_AUDIO_FWD_TOP_PWRACT_SHIFT         (7U)
#define GRF_SOC_STATUS0_AUDIO_FWD_TOP_PWRACT_MASK          (0x1U << GRF_SOC_STATUS0_AUDIO_FWD_TOP_PWRACT_SHIFT)         /* 0x00000080 */
#define GRF_SOC_STATUS0_AUDIO_FWD_DSP_PWRACT_SHIFT         (8U)
#define GRF_SOC_STATUS0_AUDIO_FWD_DSP_PWRACT_MASK          (0x1U << GRF_SOC_STATUS0_AUDIO_FWD_DSP_PWRACT_SHIFT)         /* 0x00000100 */
#define GRF_SOC_STATUS0_DSP_FWD_ALIVE_PWRACT_SHIFT         (9U)
#define GRF_SOC_STATUS0_DSP_FWD_ALIVE_PWRACT_MASK          (0x1U << GRF_SOC_STATUS0_DSP_FWD_ALIVE_PWRACT_SHIFT)         /* 0x00000200 */
#define GRF_SOC_STATUS0_DSP_FWD_AUDIO_PWRACT_SHIFT         (10U)
#define GRF_SOC_STATUS0_DSP_FWD_AUDIO_PWRACT_MASK          (0x1U << GRF_SOC_STATUS0_DSP_FWD_AUDIO_PWRACT_SHIFT)         /* 0x00000400 */
/* SOC_STATUS1 */
#define GRF_SOC_STATUS1_OFFSET                             (0x144U)
#define GRF_SOC_STATUS1                                    (0x0U)
#define GRF_SOC_STATUS1_IO_LCD_IN_TE_SHIFT                 (0U)
#define GRF_SOC_STATUS1_IO_LCD_IN_TE_MASK                  (0x1U << GRF_SOC_STATUS1_IO_LCD_IN_TE_SHIFT)                 /* 0x00000001 */
#define GRF_SOC_STATUS1_IO_LCD_IN_RESETN_SHIFT             (1U)
#define GRF_SOC_STATUS1_IO_LCD_IN_RESETN_MASK              (0x1U << GRF_SOC_STATUS1_IO_LCD_IN_RESETN_SHIFT)             /* 0x00000002 */
#define GRF_SOC_STATUS1_TP_INT_SHIFT                       (2U)
#define GRF_SOC_STATUS1_TP_INT_MASK                        (0x1U << GRF_SOC_STATUS1_TP_INT_SHIFT)                       /* 0x00000004 */
#define GRF_SOC_STATUS1_CLK_SRC_SEL_SHIFT                  (3U)
#define GRF_SOC_STATUS1_CLK_SRC_SEL_MASK                   (0x1U << GRF_SOC_STATUS1_CLK_SRC_SEL_SHIFT)                  /* 0x00000008 */
#define GRF_SOC_STATUS1_OSC_CLKSRC_SEL_SHIFT               (4U)
#define GRF_SOC_STATUS1_OSC_CLKSRC_SEL_MASK                (0x1U << GRF_SOC_STATUS1_OSC_CLKSRC_SEL_SHIFT)               /* 0x00000010 */
#define GRF_SOC_STATUS1_BOOT_SEL_SHIFT                     (5U)
#define GRF_SOC_STATUS1_BOOT_SEL_MASK                      (0x1U << GRF_SOC_STATUS1_BOOT_SEL_SHIFT)                     /* 0x00000020 */
#define GRF_SOC_STATUS1_BOOT_DEVICE_SEL_SHIFT              (6U)
#define GRF_SOC_STATUS1_BOOT_DEVICE_SEL_MASK               (0x1U << GRF_SOC_STATUS1_BOOT_DEVICE_SEL_SHIFT)              /* 0x00000040 */
#define GRF_SOC_STATUS1_AP_WAKEUP_OLPC_SHIFT               (7U)
#define GRF_SOC_STATUS1_AP_WAKEUP_OLPC_MASK                (0x1U << GRF_SOC_STATUS1_AP_WAKEUP_OLPC_SHIFT)               /* 0x00000080 */
#define GRF_SOC_STATUS1_AUDIO_BYPASS_EN_POST_SHIFT         (8U)
#define GRF_SOC_STATUS1_AUDIO_BYPASS_EN_POST_MASK          (0x1U << GRF_SOC_STATUS1_AUDIO_BYPASS_EN_POST_SHIFT)         /* 0x00000100 */
/* DSP_CON0 */
#define GRF_DSP_CON0_OFFSET                                (0x160U)
#define GRF_DSP_CON0_OCDHALTONRESET_SHIFT                  (0U)
#define GRF_DSP_CON0_OCDHALTONRESET_MASK                   (0x1U << GRF_DSP_CON0_OCDHALTONRESET_SHIFT)                  /* 0x00000001 */
#define GRF_DSP_CON0_BREAKIN_SHIFT                         (1U)
#define GRF_DSP_CON0_BREAKIN_MASK                          (0x1U << GRF_DSP_CON0_BREAKIN_SHIFT)                         /* 0x00000002 */
#define GRF_DSP_CON0_BREAKOUTACK_SHIFT                     (2U)
#define GRF_DSP_CON0_BREAKOUTACK_MASK                      (0x1U << GRF_DSP_CON0_BREAKOUTACK_SHIFT)                     /* 0x00000004 */
#define GRF_DSP_CON0_STATVECTORSEL_SHIFT                   (4U)
#define GRF_DSP_CON0_STATVECTORSEL_MASK                    (0x1U << GRF_DSP_CON0_STATVECTORSEL_SHIFT)                   /* 0x00000010 */
#define GRF_DSP_CON0_RUNSTALL_SHIFT                        (5U)
#define GRF_DSP_CON0_RUNSTALL_MASK                         (0x1U << GRF_DSP_CON0_RUNSTALL_SHIFT)                        /* 0x00000020 */
/* DSP_CON1 */
#define GRF_DSP_CON1_OFFSET                                (0x164U)
#define GRF_DSP_CON1_ALTRESETVEC_SHIFT                     (0U)
#define GRF_DSP_CON1_ALTRESETVEC_MASK                      (0xFFFFFFFFU << GRF_DSP_CON1_ALTRESETVEC_SHIFT)              /* 0xFFFFFFFF */
/* DSP_CON2 */
#define GRF_DSP_CON2_OFFSET                                (0x168U)
#define GRF_DSP_CON2_ICACHE_MEM_AUTO_GATING_EN_SHIFT       (0U)
#define GRF_DSP_CON2_ICACHE_MEM_AUTO_GATING_EN_MASK        (0x1U << GRF_DSP_CON2_ICACHE_MEM_AUTO_GATING_EN_SHIFT)       /* 0x00000001 */
#define GRF_DSP_CON2_ITAG_MEM_AUTO_GATING_EN_SHIFT         (1U)
#define GRF_DSP_CON2_ITAG_MEM_AUTO_GATING_EN_MASK          (0x1U << GRF_DSP_CON2_ITAG_MEM_AUTO_GATING_EN_SHIFT)         /* 0x00000002 */
#define GRF_DSP_CON2_DCACHE_MEM_AUTO_GATING_EN_SHIFT       (2U)
#define GRF_DSP_CON2_DCACHE_MEM_AUTO_GATING_EN_MASK        (0x1U << GRF_DSP_CON2_DCACHE_MEM_AUTO_GATING_EN_SHIFT)       /* 0x00000004 */
#define GRF_DSP_CON2_DTAG_MEM_AUTO_GATING_EN_SHIFT         (3U)
#define GRF_DSP_CON2_DTAG_MEM_AUTO_GATING_EN_MASK          (0x1U << GRF_DSP_CON2_DTAG_MEM_AUTO_GATING_EN_SHIFT)         /* 0x00000008 */
#define GRF_DSP_CON2_PREFETCH_RAM_AUTO_GATING_EN_SHIFT     (4U)
#define GRF_DSP_CON2_PREFETCH_RAM_AUTO_GATING_EN_MASK      (0x1U << GRF_DSP_CON2_PREFETCH_RAM_AUTO_GATING_EN_SHIFT)     /* 0x00000010 */
#define GRF_DSP_CON2_DTCM_MEM_AUTO_GATING_EN_SHIFT         (5U)
#define GRF_DSP_CON2_DTCM_MEM_AUTO_GATING_EN_MASK          (0x1U << GRF_DSP_CON2_DTCM_MEM_AUTO_GATING_EN_SHIFT)         /* 0x00000020 */
#define GRF_DSP_CON2_ITCM_MEM_AUTO_GATING_EN_SHIFT         (6U)
#define GRF_DSP_CON2_ITCM_MEM_AUTO_GATING_EN_MASK          (0x1U << GRF_DSP_CON2_ITCM_MEM_AUTO_GATING_EN_SHIFT)         /* 0x00000040 */
#define GRF_DSP_CON2_VAD_DTCM_SPACE_SEL_SHIFT              (8U)
#define GRF_DSP_CON2_VAD_DTCM_SPACE_SEL_MASK               (0x3U << GRF_DSP_CON2_VAD_DTCM_SPACE_SEL_SHIFT)              /* 0x00000300 */
/* DSP_STAT0 */
#define GRF_DSP_STAT0_OFFSET                               (0x170U)
#define GRF_DSP_STAT0                                      (0x0U)
#define GRF_DSP_STAT0_XOCDMODE_SHIFT                       (0U)
#define GRF_DSP_STAT0_XOCDMODE_MASK                        (0x1U << GRF_DSP_STAT0_XOCDMODE_SHIFT)                       /* 0x00000001 */
#define GRF_DSP_STAT0_DEBUGMODE_SHIFT                      (1U)
#define GRF_DSP_STAT0_DEBUGMODE_MASK                       (0x1U << GRF_DSP_STAT0_DEBUGMODE_SHIFT)                      /* 0x00000002 */
#define GRF_DSP_STAT0_BREAKINACK_SHIFT                     (2U)
#define GRF_DSP_STAT0_BREAKINACK_MASK                      (0x1U << GRF_DSP_STAT0_BREAKINACK_SHIFT)                     /* 0x00000004 */
#define GRF_DSP_STAT0_BREAKOUT_SHIFT                       (3U)
#define GRF_DSP_STAT0_BREAKOUT_MASK                        (0x1U << GRF_DSP_STAT0_BREAKOUT_SHIFT)                       /* 0x00000008 */
#define GRF_DSP_STAT0_DOUBLEEXCEPTIONERROR_SHIFT           (4U)
#define GRF_DSP_STAT0_DOUBLEEXCEPTIONERROR_MASK            (0x1U << GRF_DSP_STAT0_DOUBLEEXCEPTIONERROR_SHIFT)           /* 0x00000010 */
#define GRF_DSP_STAT0_PFATALERROR_SHIFT                    (5U)
#define GRF_DSP_STAT0_PFATALERROR_MASK                     (0x1U << GRF_DSP_STAT0_PFATALERROR_SHIFT)                    /* 0x00000020 */
#define GRF_DSP_STAT0_PFAULTINFOVALID_SHIFT                (6U)
#define GRF_DSP_STAT0_PFAULTINFOVALID_MASK                 (0x1U << GRF_DSP_STAT0_PFAULTINFOVALID_SHIFT)                /* 0x00000040 */
#define GRF_DSP_STAT0_PWAITMODE_SHIFT                      (7U)
#define GRF_DSP_STAT0_PWAITMODE_MASK                       (0x1U << GRF_DSP_STAT0_PWAITMODE_SHIFT)                      /* 0x00000080 */
#define GRF_DSP_STAT0_IRAM0LOADSTORE_SHIFT                 (8U)
#define GRF_DSP_STAT0_IRAM0LOADSTORE_MASK                  (0x1U << GRF_DSP_STAT0_IRAM0LOADSTORE_SHIFT)                 /* 0x00000100 */
/* DSP_STAT1 */
#define GRF_DSP_STAT1_OFFSET                               (0x174U)
#define GRF_DSP_STAT1                                      (0x0U)
#define GRF_DSP_STAT1_PFAULTINFO_SHIFT                     (0U)
#define GRF_DSP_STAT1_PFAULTINFO_MASK                      (0xFFFFFFFFU << GRF_DSP_STAT1_PFAULTINFO_SHIFT)              /* 0xFFFFFFFF */
/* PVTM_CON0 */
#define GRF_PVTM_CON0_OFFSET                               (0x180U)
#define GRF_PVTM_CON0_PVTM_START_SHIFT                     (0U)
#define GRF_PVTM_CON0_PVTM_START_MASK                      (0x1U << GRF_PVTM_CON0_PVTM_START_SHIFT)                     /* 0x00000001 */
#define GRF_PVTM_CON0_PVTM_OSC_EN_SHIFT                    (1U)
#define GRF_PVTM_CON0_PVTM_OSC_EN_MASK                     (0x1U << GRF_PVTM_CON0_PVTM_OSC_EN_SHIFT)                    /* 0x00000002 */
#define GRF_PVTM_CON0_PVTM_CLKOUT_DIV_SHIFT                (2U)
#define GRF_PVTM_CON0_PVTM_CLKOUT_DIV_MASK                 (0xFFFU << GRF_PVTM_CON0_PVTM_CLKOUT_DIV_SHIFT)              /* 0x00003FFC */
/* PVTM_CON1 */
#define GRF_PVTM_CON1_OFFSET                               (0x184U)
#define GRF_PVTM_CON1_PVTM_CAL_CNT_SHIFT                   (0U)
#define GRF_PVTM_CON1_PVTM_CAL_CNT_MASK                    (0xFFFFFFFFU << GRF_PVTM_CON1_PVTM_CAL_CNT_SHIFT)            /* 0xFFFFFFFF */
/* PVTM_STATUS0 */
#define GRF_PVTM_STATUS0_OFFSET                            (0x190U)
#define GRF_PVTM_STATUS0                                   (0x0U)
#define GRF_PVTM_STATUS0_PVTM_FREQ_DONE_SHIFT              (0U)
#define GRF_PVTM_STATUS0_PVTM_FREQ_DONE_MASK               (0x1U << GRF_PVTM_STATUS0_PVTM_FREQ_DONE_SHIFT)              /* 0x00000001 */
/* PVTM_STATUS1 */
#define GRF_PVTM_STATUS1_OFFSET                            (0x194U)
#define GRF_PVTM_STATUS1                                   (0x0U)
#define GRF_PVTM_STATUS1_PVTM_FREQ_CNT_SHIFT               (0U)
#define GRF_PVTM_STATUS1_PVTM_FREQ_CNT_MASK                (0xFFFFFFFFU << GRF_PVTM_STATUS1_PVTM_FREQ_CNT_SHIFT)        /* 0xFFFFFFFF */
/* FW_CON0 */
#define GRF_FW_CON0_OFFSET                                 (0x1C0U)
#define GRF_FW_CON0_FWBYPASS_SHIFT                         (0U)
#define GRF_FW_CON0_FWBYPASS_MASK                          (0x1U << GRF_FW_CON0_FWBYPASS_SHIFT)                         /* 0x00000001 */
#define GRF_FW_CON0_MEMEN_SHIFT                            (1U)
#define GRF_FW_CON0_MEMEN_MASK                             (0x1U << GRF_FW_CON0_MEMEN_SHIFT)                            /* 0x00000002 */
#define GRF_FW_CON0_MBOXEN_SHIFT                           (2U)
#define GRF_FW_CON0_MBOXEN_MASK                            (0x1U << GRF_FW_CON0_MBOXEN_SHIFT)                           /* 0x00000004 */
/* FW_CON1 */
#define GRF_FW_CON1_OFFSET                                 (0x1C4U)
#define GRF_FW_CON1_MEM_BASE_ADDRESS_SHIFT                 (0U)
#define GRF_FW_CON1_MEM_BASE_ADDRESS_MASK                  (0xFFFFFFFFU << GRF_FW_CON1_MEM_BASE_ADDRESS_SHIFT)          /* 0xFFFFFFFF */
/* FW_CON2 */
#define GRF_FW_CON2_OFFSET                                 (0x1C8U)
#define GRF_FW_CON2_MEM_TOP_ADDRESS_SHIFT                  (0U)
#define GRF_FW_CON2_MEM_TOP_ADDRESS_MASK                   (0xFFFFFFFFU << GRF_FW_CON2_MEM_TOP_ADDRESS_SHIFT)           /* 0xFFFFFFFF */
/* MCU_CON0 */
#define GRF_MCU_CON0_OFFSET                                (0x200U)
#define GRF_MCU_CON0_M4_RXEV_SHIFT                         (0U)
#define GRF_MCU_CON0_M4_RXEV_MASK                          (0x1U << GRF_MCU_CON0_M4_RXEV_SHIFT)                         /* 0x00000001 */
#define GRF_MCU_CON0_M4_NMI_SHIFT                          (1U)
#define GRF_MCU_CON0_M4_NMI_MASK                           (0x1U << GRF_MCU_CON0_M4_NMI_SHIFT)                          /* 0x00000002 */
#define GRF_MCU_CON0_M4_EDBGRQ_SHIFT                       (2U)
#define GRF_MCU_CON0_M4_EDBGRQ_MASK                        (0x1U << GRF_MCU_CON0_M4_EDBGRQ_SHIFT)                       /* 0x00000004 */
#define GRF_MCU_CON0_M4_DBGRESTART_SHIFT                   (3U)
#define GRF_MCU_CON0_M4_DBGRESTART_MASK                    (0x1U << GRF_MCU_CON0_M4_DBGRESTART_SHIFT)                   /* 0x00000008 */
#define GRF_MCU_CON0_M4_DBGEN_SHIFT                        (4U)
#define GRF_MCU_CON0_M4_DBGEN_MASK                         (0x1U << GRF_MCU_CON0_M4_DBGEN_SHIFT)                        /* 0x00000010 */
#define GRF_MCU_CON0_M4_MPU_DISABLE_SHIFT                  (6U)
#define GRF_MCU_CON0_M4_MPU_DISABLE_MASK                   (0x1U << GRF_MCU_CON0_M4_MPU_DISABLE_SHIFT)                  /* 0x00000040 */
#define GRF_MCU_CON0_M4_FPU_DISABLE_SHIFT                  (7U)
#define GRF_MCU_CON0_M4_FPU_DISABLE_MASK                   (0x1U << GRF_MCU_CON0_M4_FPU_DISABLE_SHIFT)                  /* 0x00000080 */
#define GRF_MCU_CON0_M4_DAP_FIXMASTER_SHIFT                (8U)
#define GRF_MCU_CON0_M4_DAP_FIXMASTER_MASK                 (0x1U << GRF_MCU_CON0_M4_DAP_FIXMASTER_SHIFT)                /* 0x00000100 */
#define GRF_MCU_CON0_M4_DAP_DCACHE_SHIFT                   (9U)
#define GRF_MCU_CON0_M4_DAP_DCACHE_MASK                    (0x1U << GRF_MCU_CON0_M4_DAP_DCACHE_SHIFT)                   /* 0x00000200 */
#define GRF_MCU_CON0_M4_SLEEP_DELAY_SHIFT                  (10U)
#define GRF_MCU_CON0_M4_SLEEP_DELAY_MASK                   (0x1U << GRF_MCU_CON0_M4_SLEEP_DELAY_SHIFT)                  /* 0x00000400 */
/* MCU_CON1 */
#define GRF_MCU_CON1_OFFSET                                (0x204U)
#define GRF_MCU_CON1_M4_TENMS_SHIFT                        (0U)
#define GRF_MCU_CON1_M4_TENMS_MASK                         (0xFFFFFFU << GRF_MCU_CON1_M4_TENMS_SHIFT)                   /* 0x00FFFFFF */
#define GRF_MCU_CON1_M4_SKEW_SHIFT                         (24U)
#define GRF_MCU_CON1_M4_SKEW_MASK                          (0x1U << GRF_MCU_CON1_M4_SKEW_SHIFT)                         /* 0x01000000 */
/* MCU_CON2 */
#define GRF_MCU_CON2_OFFSET                                (0x208U)
#define GRF_MCU_CON2_M4_MEM_OFFSET_SHIFT                   (0U)
#define GRF_MCU_CON2_M4_MEM_OFFSET_MASK                    (0xFFFFFFFFU << GRF_MCU_CON2_M4_MEM_OFFSET_SHIFT)            /* 0xFFFFFFFF */
/* MCU_CON3 */
#define GRF_MCU_CON3_OFFSET                                (0x20CU)
#define GRF_MCU_CON3_M4_FLASH_OFFSET_SHIFT                 (0U)
#define GRF_MCU_CON3_M4_FLASH_OFFSET_MASK                  (0xFFFFFFFFU << GRF_MCU_CON3_M4_FLASH_OFFSET_SHIFT)          /* 0xFFFFFFFF */
/* MCU_STAT0 */
#define GRF_MCU_STAT0_OFFSET                               (0x220U)
#define GRF_MCU_STAT0                                      (0x0U)
#define GRF_MCU_STAT0_M4_SLEEPING_SHIFT                    (0U)
#define GRF_MCU_STAT0_M4_SLEEPING_MASK                     (0x1U << GRF_MCU_STAT0_M4_SLEEPING_SHIFT)                    /* 0x00000001 */
#define GRF_MCU_STAT0_M4_SLEEPDEEP_SHIFT                   (1U)
#define GRF_MCU_STAT0_M4_SLEEPDEEP_MASK                    (0x1U << GRF_MCU_STAT0_M4_SLEEPDEEP_SHIFT)                   /* 0x00000002 */
#define GRF_MCU_STAT0_M4_HALTED_SHIFT                      (2U)
#define GRF_MCU_STAT0_M4_HALTED_MASK                       (0x1U << GRF_MCU_STAT0_M4_HALTED_SHIFT)                      /* 0x00000004 */
#define GRF_MCU_STAT0_M4_DBGRESTARTED_SHIFT                (3U)
#define GRF_MCU_STAT0_M4_DBGRESTARTED_MASK                 (0x1U << GRF_MCU_STAT0_M4_DBGRESTARTED_SHIFT)                /* 0x00000008 */
#define GRF_MCU_STAT0_M4_GATEHCLK_SHIFT                    (4U)
#define GRF_MCU_STAT0_M4_GATEHCLK_MASK                     (0x1U << GRF_MCU_STAT0_M4_GATEHCLK_SHIFT)                    /* 0x00000010 */
#define GRF_MCU_STAT0_M4_LOCKUP_SHIFT                      (5U)
#define GRF_MCU_STAT0_M4_LOCKUP_MASK                       (0x1U << GRF_MCU_STAT0_M4_LOCKUP_SHIFT)                      /* 0x00000020 */
#define GRF_MCU_STAT0_M4_CURRPRI_SHIFT                     (8U)
#define GRF_MCU_STAT0_M4_CURRPRI_MASK                      (0xFFU << GRF_MCU_STAT0_M4_CURRPRI_SHIFT)                    /* 0x0000FF00 */
#define GRF_MCU_STAT0_M4_FPIXC_SHIFT                       (16U)
#define GRF_MCU_STAT0_M4_FPIXC_MASK                        (0x1U << GRF_MCU_STAT0_M4_FPIXC_SHIFT)                       /* 0x00010000 */
#define GRF_MCU_STAT0_M4_FPOFC_SHIFT                       (17U)
#define GRF_MCU_STAT0_M4_FPOFC_MASK                        (0x1U << GRF_MCU_STAT0_M4_FPOFC_SHIFT)                       /* 0x00020000 */
#define GRF_MCU_STAT0_M4_FPUFC_SHIFT                       (18U)
#define GRF_MCU_STAT0_M4_FPUFC_MASK                        (0x1U << GRF_MCU_STAT0_M4_FPUFC_SHIFT)                       /* 0x00040000 */
#define GRF_MCU_STAT0_M4_FPIOC_SHIFT                       (19U)
#define GRF_MCU_STAT0_M4_FPIOC_MASK                        (0x1U << GRF_MCU_STAT0_M4_FPIOC_SHIFT)                       /* 0x00080000 */
#define GRF_MCU_STAT0_M4_FPDZC_SHIFT                       (20U)
#define GRF_MCU_STAT0_M4_FPDZC_MASK                        (0x1U << GRF_MCU_STAT0_M4_FPDZC_SHIFT)                       /* 0x00100000 */
#define GRF_MCU_STAT0_M4_FPIDC_SHIFT                       (21U)
#define GRF_MCU_STAT0_M4_FPIDC_MASK                        (0x1U << GRF_MCU_STAT0_M4_FPIDC_SHIFT)                       /* 0x00200000 */
/* DSI_CON0 */
#define GRF_DSI_CON0_OFFSET                                (0x240U)
#define GRF_DSI_CON0_DPHY_PHYRSTZ_SHIFT                    (0U)
#define GRF_DSI_CON0_DPHY_PHYRSTZ_MASK                     (0x1U << GRF_DSI_CON0_DPHY_PHYRSTZ_SHIFT)                    /* 0x00000001 */
#define GRF_DSI_CON0_DPHY_PLL_CLK_SEL_SHIFT                (2U)
#define GRF_DSI_CON0_DPHY_PLL_CLK_SEL_MASK                 (0x3FFU << GRF_DSI_CON0_DPHY_PLL_CLK_SEL_SHIFT)              /* 0x00000FFC */
#define GRF_DSI_CON0_DPHY_REFCLK_IN_SEL_SHIFT              (12U)
#define GRF_DSI_CON0_DPHY_REFCLK_IN_SEL_MASK               (0x7U << GRF_DSI_CON0_DPHY_REFCLK_IN_SEL_SHIFT)              /* 0x00007000 */
/* DSI_CON1 */
#define GRF_DSI_CON1_OFFSET                                (0x244U)
#define GRF_DSI_CON1_DPHY_TXSKEWCALHS_SHIFT                (0U)
#define GRF_DSI_CON1_DPHY_TXSKEWCALHS_MASK                 (0xFU << GRF_DSI_CON1_DPHY_TXSKEWCALHS_SHIFT)                /* 0x0000000F */
#define GRF_DSI_CON1_DPHY_FORCETXSTOPMODE_SHIFT            (4U)
#define GRF_DSI_CON1_DPHY_FORCETXSTOPMODE_MASK             (0xFU << GRF_DSI_CON1_DPHY_FORCETXSTOPMODE_SHIFT)            /* 0x000000F0 */
#define GRF_DSI_CON1_DPHY_TURNDISABLE0_SHIFT               (8U)
#define GRF_DSI_CON1_DPHY_TURNDISABLE0_MASK                (0x1U << GRF_DSI_CON1_DPHY_TURNDISABLE0_SHIFT)               /* 0x00000100 */
#define GRF_DSI_CON1_DPHY_FORCERXMODE0_SHIFT               (9U)
#define GRF_DSI_CON1_DPHY_FORCERXMODE0_MASK                (0x1U << GRF_DSI_CON1_DPHY_FORCERXMODE0_SHIFT)               /* 0x00000200 */
#define GRF_DSI_CON1_DPHY_TXONLY_SHIFT                     (10U)
#define GRF_DSI_CON1_DPHY_TXONLY_MASK                      (0x1U << GRF_DSI_CON1_DPHY_TXONLY_SHIFT)                     /* 0x00000400 */
#define GRF_DSI_CON1_DPHY_DEBUG_SEL_SHIFT                  (11U)
#define GRF_DSI_CON1_DPHY_DEBUG_SEL_MASK                   (0x1FU << GRF_DSI_CON1_DPHY_DEBUG_SEL_SHIFT)                 /* 0x0000F800 */
/* DSI_CON2 */
#define GRF_DSI_CON2_OFFSET                                (0x248U)
#define GRF_DSI_CON2_DPHY_LANE_SWAP0_SHIFT                 (0U)
#define GRF_DSI_CON2_DPHY_LANE_SWAP0_MASK                  (0x7U << GRF_DSI_CON2_DPHY_LANE_SWAP0_SHIFT)                 /* 0x00000007 */
#define GRF_DSI_CON2_DPHY_LANE_SWAP1_SHIFT                 (3U)
#define GRF_DSI_CON2_DPHY_LANE_SWAP1_MASK                  (0x7U << GRF_DSI_CON2_DPHY_LANE_SWAP1_SHIFT)                 /* 0x00000038 */
#define GRF_DSI_CON2_DPHY_LANE_SWAP2_SHIFT                 (6U)
#define GRF_DSI_CON2_DPHY_LANE_SWAP2_MASK                  (0x7U << GRF_DSI_CON2_DPHY_LANE_SWAP2_SHIFT)                 /* 0x000001C0 */
#define GRF_DSI_CON2_DPHY_LANE_SWAP3_SHIFT                 (9U)
#define GRF_DSI_CON2_DPHY_LANE_SWAP3_MASK                  (0x7U << GRF_DSI_CON2_DPHY_LANE_SWAP3_SHIFT)                 /* 0x00000E00 */
#define GRF_DSI_CON2_DPHY_LANE_SWAP_CLK_SHIFT              (12U)
#define GRF_DSI_CON2_DPHY_LANE_SWAP_CLK_MASK               (0x7U << GRF_DSI_CON2_DPHY_LANE_SWAP_CLK_SHIFT)              /* 0x00007000 */
/* DSI_CON3 */
#define GRF_DSI_CON3_OFFSET                                (0x24CU)
#define GRF_DSI_CON3_DPHY_XCFGI_D0_SHIFT                   (0U)
#define GRF_DSI_CON3_DPHY_XCFGI_D0_MASK                    (0xFFFFFFFFU << GRF_DSI_CON3_DPHY_XCFGI_D0_SHIFT)            /* 0xFFFFFFFF */
/* DSI_CON4 */
#define GRF_DSI_CON4_OFFSET                                (0x250U)
#define GRF_DSI_CON4_DPHY_XCFGI_D0_SHIFT                   (0U)
#define GRF_DSI_CON4_DPHY_XCFGI_D0_MASK                    (0xFFFFFFFFU << GRF_DSI_CON4_DPHY_XCFGI_D0_SHIFT)            /* 0xFFFFFFFF */
/* DSI_CON5 */
#define GRF_DSI_CON5_OFFSET                                (0x254U)
#define GRF_DSI_CON5_DPHY_XCFGI_D0_SHIFT                   (0U)
#define GRF_DSI_CON5_DPHY_XCFGI_D0_MASK                    (0xFFFFFFU << GRF_DSI_CON5_DPHY_XCFGI_D0_SHIFT)              /* 0x00FFFFFF */
/* DSI_CON6 */
#define GRF_DSI_CON6_OFFSET                                (0x258U)
#define GRF_DSI_CON6_DPHY_XCFGI_D1_SHIFT                   (0U)
#define GRF_DSI_CON6_DPHY_XCFGI_D1_MASK                    (0xFFFFFFFFU << GRF_DSI_CON6_DPHY_XCFGI_D1_SHIFT)            /* 0xFFFFFFFF */
/* DSI_CON7 */
#define GRF_DSI_CON7_OFFSET                                (0x25CU)
#define GRF_DSI_CON7_DPHY_XCFGI_D1_SHIFT                   (0U)
#define GRF_DSI_CON7_DPHY_XCFGI_D1_MASK                    (0xFFFFFFFFU << GRF_DSI_CON7_DPHY_XCFGI_D1_SHIFT)            /* 0xFFFFFFFF */
/* DSI_CON8 */
#define GRF_DSI_CON8_OFFSET                                (0x260U)
#define GRF_DSI_CON8_DPHY_XCFGI_D1_SHIFT                   (0U)
#define GRF_DSI_CON8_DPHY_XCFGI_D1_MASK                    (0xFFFFFFU << GRF_DSI_CON8_DPHY_XCFGI_D1_SHIFT)              /* 0x00FFFFFF */
/* DSI_CON9 */
#define GRF_DSI_CON9_OFFSET                                (0x264U)
#define GRF_DSI_CON9_DPHY_XCFGI_D2_SHIFT                   (0U)
#define GRF_DSI_CON9_DPHY_XCFGI_D2_MASK                    (0xFFFFFFFFU << GRF_DSI_CON9_DPHY_XCFGI_D2_SHIFT)            /* 0xFFFFFFFF */
/* DSI_CON10 */
#define GRF_DSI_CON10_OFFSET                               (0x268U)
#define GRF_DSI_CON10_DPHY_XCFGI_D2_SHIFT                  (0U)
#define GRF_DSI_CON10_DPHY_XCFGI_D2_MASK                   (0xFFFFFFFFU << GRF_DSI_CON10_DPHY_XCFGI_D2_SHIFT)           /* 0xFFFFFFFF */
/* DSI_CON11 */
#define GRF_DSI_CON11_OFFSET                               (0x26CU)
#define GRF_DSI_CON11_DPHY_XCFGI_D2_SHIFT                  (0U)
#define GRF_DSI_CON11_DPHY_XCFGI_D2_MASK                   (0xFFFFFFU << GRF_DSI_CON11_DPHY_XCFGI_D2_SHIFT)             /* 0x00FFFFFF */
/* DSI_CON12 */
#define GRF_DSI_CON12_OFFSET                               (0x270U)
#define GRF_DSI_CON12_DPHY_XCFGI_D3_SHIFT                  (0U)
#define GRF_DSI_CON12_DPHY_XCFGI_D3_MASK                   (0xFFFFFFFFU << GRF_DSI_CON12_DPHY_XCFGI_D3_SHIFT)           /* 0xFFFFFFFF */
/* DSI_CON13 */
#define GRF_DSI_CON13_OFFSET                               (0x274U)
#define GRF_DSI_CON13_DPHY_XCFGI_D3_SHIFT                  (0U)
#define GRF_DSI_CON13_DPHY_XCFGI_D3_MASK                   (0xFFFFFFFFU << GRF_DSI_CON13_DPHY_XCFGI_D3_SHIFT)           /* 0xFFFFFFFF */
/* DSI_CON14 */
#define GRF_DSI_CON14_OFFSET                               (0x278U)
#define GRF_DSI_CON14_DPHY_XCFGI_D3_SHIFT                  (0U)
#define GRF_DSI_CON14_DPHY_XCFGI_D3_MASK                   (0xFFFFFFU << GRF_DSI_CON14_DPHY_XCFGI_D3_SHIFT)             /* 0x00FFFFFF */
/* DSI_CON15 */
#define GRF_DSI_CON15_OFFSET                               (0x27CU)
#define GRF_DSI_CON15_DPHY_XCFGI_CLK_SHIFT                 (0U)
#define GRF_DSI_CON15_DPHY_XCFGI_CLK_MASK                  (0xFFFFFFFFU << GRF_DSI_CON15_DPHY_XCFGI_CLK_SHIFT)          /* 0xFFFFFFFF */
/* DSI_CON16 */
#define GRF_DSI_CON16_OFFSET                               (0x280U)
#define GRF_DSI_CON16_DPHY_XCFGI_CLK_SHIFT                 (0U)
#define GRF_DSI_CON16_DPHY_XCFGI_CLK_MASK                  (0xFFFFFFFFU << GRF_DSI_CON16_DPHY_XCFGI_CLK_SHIFT)          /* 0xFFFFFFFF */
/* DSI_CON17 */
#define GRF_DSI_CON17_OFFSET                               (0x284U)
#define GRF_DSI_CON17_DPHY_XCFGI_CLK_SHIFT                 (0U)
#define GRF_DSI_CON17_DPHY_XCFGI_CLK_MASK                  (0xFFFFFFU << GRF_DSI_CON17_DPHY_XCFGI_CLK_SHIFT)            /* 0x00FFFFFF */
/* DSI_CON18 */
#define GRF_DSI_CON18_OFFSET                               (0x288U)
#define GRF_DSI_CON18_DPHY_XCFGI_GLOBAL_SHIFT              (0U)
#define GRF_DSI_CON18_DPHY_XCFGI_GLOBAL_MASK               (0xFFFFFFFFU << GRF_DSI_CON18_DPHY_XCFGI_GLOBAL_SHIFT)       /* 0xFFFFFFFF */
/* DSI_CON19 */
#define GRF_DSI_CON19_OFFSET                               (0x28CU)
#define GRF_DSI_CON19_DPHY_XCFGI_GLOBAL_SHIFT              (0U)
#define GRF_DSI_CON19_DPHY_XCFGI_GLOBAL_MASK               (0xFFFFFFFFU << GRF_DSI_CON19_DPHY_XCFGI_GLOBAL_SHIFT)       /* 0xFFFFFFFF */
/* DSI_CON20 */
#define GRF_DSI_CON20_OFFSET                               (0x290U)
#define GRF_DSI_CON20_DPHY_XCFGI_GLOBAL_SHIFT              (0U)
#define GRF_DSI_CON20_DPHY_XCFGI_GLOBAL_MASK               (0xFFFFFFFFU << GRF_DSI_CON20_DPHY_XCFGI_GLOBAL_SHIFT)       /* 0xFFFFFFFF */
/* DSI_CON21 */
#define GRF_DSI_CON21_OFFSET                               (0x294U)
#define GRF_DSI_CON21_DPHY_XCFGI_GLOBAL_SHIFT              (0U)
#define GRF_DSI_CON21_DPHY_XCFGI_GLOBAL_MASK               (0xFFFFFFFFU << GRF_DSI_CON21_DPHY_XCFGI_GLOBAL_SHIFT)       /* 0xFFFFFFFF */
/* DSI_CON22 */
#define GRF_DSI_CON22_OFFSET                               (0x298U)
#define GRF_DSI_CON22_DPHY_XCFGI_GLOBAL_SHIFT              (0U)
#define GRF_DSI_CON22_DPHY_XCFGI_GLOBAL_MASK               (0xFFFFFFFFU << GRF_DSI_CON22_DPHY_XCFGI_GLOBAL_SHIFT)       /* 0xFFFFFFFF */
/* DSI_CON23 */
#define GRF_DSI_CON23_OFFSET                               (0x29CU)
#define GRF_DSI_CON23_DPHY_XCFGI_GLOBAL_SHIFT              (0U)
#define GRF_DSI_CON23_DPHY_XCFGI_GLOBAL_MASK               (0xFFFFFFFFU << GRF_DSI_CON23_DPHY_XCFGI_GLOBAL_SHIFT)       /* 0xFFFFFFFF */
/* DSI_CON24 */
#define GRF_DSI_CON24_OFFSET                               (0x2A0U)
#define GRF_DSI_CON24_DPHY_XCFGI_GLOBAL_SHIFT              (0U)
#define GRF_DSI_CON24_DPHY_XCFGI_GLOBAL_MASK               (0xFFFFFFFFU << GRF_DSI_CON24_DPHY_XCFGI_GLOBAL_SHIFT)       /* 0xFFFFFFFF */
/* DSI_CON25 */
#define GRF_DSI_CON25_OFFSET                               (0x2A4U)
#define GRF_DSI_CON25_DPHY_XCFGI_GLOBAL_SHIFT              (0U)
#define GRF_DSI_CON25_DPHY_XCFGI_GLOBAL_MASK               (0xFFFFFFU << GRF_DSI_CON25_DPHY_XCFGI_GLOBAL_SHIFT)         /* 0x00FFFFFF */
/* DSI_CON26 */
#define GRF_DSI_CON26_OFFSET                               (0x2A8U)
#define GRF_DSI_CON26_DPHY_FORCE_ODTCAL_SEL_SHIFT          (0U)
#define GRF_DSI_CON26_DPHY_FORCE_ODTCAL_SEL_MASK           (0xFFFU << GRF_DSI_CON26_DPHY_FORCE_ODTCAL_SEL_SHIFT)        /* 0x00000FFF */
/* DSI_CON27 */
#define GRF_DSI_CON27_OFFSET                               (0x2ACU)
#define GRF_DSI_CON27_DPHY_EXT_ODTCAL_SEL_0_SHIFT          (0U)
#define GRF_DSI_CON27_DPHY_EXT_ODTCAL_SEL_0_MASK           (0xFU << GRF_DSI_CON27_DPHY_EXT_ODTCAL_SEL_0_SHIFT)          /* 0x0000000F */
#define GRF_DSI_CON27_DPHY_EXT_ODTCAL_SEL_1_SHIFT          (4U)
#define GRF_DSI_CON27_DPHY_EXT_ODTCAL_SEL_1_MASK           (0xFU << GRF_DSI_CON27_DPHY_EXT_ODTCAL_SEL_1_SHIFT)          /* 0x000000F0 */
#define GRF_DSI_CON27_DPHY_EXT_ODTCAL_SEL_2_SHIFT          (8U)
#define GRF_DSI_CON27_DPHY_EXT_ODTCAL_SEL_2_MASK           (0xFU << GRF_DSI_CON27_DPHY_EXT_ODTCAL_SEL_2_SHIFT)          /* 0x00000F00 */
#define GRF_DSI_CON27_DPHY_EXT_ODTCAL_SEL_3_SHIFT          (12U)
#define GRF_DSI_CON27_DPHY_EXT_ODTCAL_SEL_3_MASK           (0xFU << GRF_DSI_CON27_DPHY_EXT_ODTCAL_SEL_3_SHIFT)          /* 0x0000F000 */
/* DSI_CON28 */
#define GRF_DSI_CON28_OFFSET                               (0x2B0U)
#define GRF_DSI_CON28_DPHY_EXT_ODTCAL_SEL_4_SHIFT          (0U)
#define GRF_DSI_CON28_DPHY_EXT_ODTCAL_SEL_4_MASK           (0xFU << GRF_DSI_CON28_DPHY_EXT_ODTCAL_SEL_4_SHIFT)          /* 0x0000000F */
#define GRF_DSI_CON28_DPHY_EXT_ODTCAL_SEL_5_SHIFT          (4U)
#define GRF_DSI_CON28_DPHY_EXT_ODTCAL_SEL_5_MASK           (0xFU << GRF_DSI_CON28_DPHY_EXT_ODTCAL_SEL_5_SHIFT)          /* 0x000000F0 */
#define GRF_DSI_CON28_DPHY_EXT_ODTCAL_SEL_6_SHIFT          (8U)
#define GRF_DSI_CON28_DPHY_EXT_ODTCAL_SEL_6_MASK           (0xFU << GRF_DSI_CON28_DPHY_EXT_ODTCAL_SEL_6_SHIFT)          /* 0x00000F00 */
#define GRF_DSI_CON28_DPHY_EXT_ODTCAL_SEL_7_SHIFT          (12U)
#define GRF_DSI_CON28_DPHY_EXT_ODTCAL_SEL_7_MASK           (0xFU << GRF_DSI_CON28_DPHY_EXT_ODTCAL_SEL_7_SHIFT)          /* 0x0000F000 */
/* DSI_CON29 */
#define GRF_DSI_CON29_OFFSET                               (0x2B4U)
#define GRF_DSI_CON29_DPHY_EXT_ODTCAL_SEL_8_SHIFT          (0U)
#define GRF_DSI_CON29_DPHY_EXT_ODTCAL_SEL_8_MASK           (0xFU << GRF_DSI_CON29_DPHY_EXT_ODTCAL_SEL_8_SHIFT)          /* 0x0000000F */
#define GRF_DSI_CON29_DPHY_EXT_ODTCAL_SEL_9_SHIFT          (4U)
#define GRF_DSI_CON29_DPHY_EXT_ODTCAL_SEL_9_MASK           (0xFU << GRF_DSI_CON29_DPHY_EXT_ODTCAL_SEL_9_SHIFT)          /* 0x000000F0 */
#define GRF_DSI_CON29_DPHY_EXT_ODTCAL_SEL_10_SHIFT         (8U)
#define GRF_DSI_CON29_DPHY_EXT_ODTCAL_SEL_10_MASK          (0xFU << GRF_DSI_CON29_DPHY_EXT_ODTCAL_SEL_10_SHIFT)         /* 0x00000F00 */
#define GRF_DSI_CON29_DPHY_EXT_ODTCAL_SEL_11_SHIFT         (12U)
#define GRF_DSI_CON29_DPHY_EXT_ODTCAL_SEL_11_MASK          (0xFU << GRF_DSI_CON29_DPHY_EXT_ODTCAL_SEL_11_SHIFT)         /* 0x0000F000 */
/* DSI_STATUS0 */
#define GRF_DSI_STATUS0_OFFSET                             (0x2C0U)
#define GRF_DSI_STATUS0                                    (0x0U)
#define GRF_DSI_STATUS0_DPHY_PHYULPSACTIVENOTCLK_SHIFT     (0U)
#define GRF_DSI_STATUS0_DPHY_PHYULPSACTIVENOTCLK_MASK      (0x1U << GRF_DSI_STATUS0_DPHY_PHYULPSACTIVENOTCLK_SHIFT)     /* 0x00000001 */
#define GRF_DSI_STATUS0_DPHY_PHYSTOPSTATECLKLANE_SHIFT     (1U)
#define GRF_DSI_STATUS0_DPHY_PHYSTOPSTATECLKLANE_MASK      (0x1U << GRF_DSI_STATUS0_DPHY_PHYSTOPSTATECLKLANE_SHIFT)     /* 0x00000002 */
#define GRF_DSI_STATUS0_DPHY_STOPSTATE_SHIFT               (2U)
#define GRF_DSI_STATUS0_DPHY_STOPSTATE_MASK                (0xFU << GRF_DSI_STATUS0_DPHY_STOPSTATE_SHIFT)               /* 0x0000003C */
#define GRF_DSI_STATUS0_DPHY_ULPSACTIVENOT_SHIFT           (6U)
#define GRF_DSI_STATUS0_DPHY_ULPSACTIVENOT_MASK            (0xFU << GRF_DSI_STATUS0_DPHY_ULPSACTIVENOT_SHIFT)           /* 0x000003C0 */
#define GRF_DSI_STATUS0_DPHY_ERRESC_0_SHIFT                (10U)
#define GRF_DSI_STATUS0_DPHY_ERRESC_0_MASK                 (0x1U << GRF_DSI_STATUS0_DPHY_ERRESC_0_SHIFT)                /* 0x00000400 */
#define GRF_DSI_STATUS0_DPHY_ERRSYNCESC_0_SHIFT            (11U)
#define GRF_DSI_STATUS0_DPHY_ERRSYNCESC_0_MASK             (0x1U << GRF_DSI_STATUS0_DPHY_ERRSYNCESC_0_SHIFT)            /* 0x00000800 */
#define GRF_DSI_STATUS0_DPHY_ERRCONTROL_0_SHIFT            (12U)
#define GRF_DSI_STATUS0_DPHY_ERRCONTROL_0_MASK             (0x1U << GRF_DSI_STATUS0_DPHY_ERRCONTROL_0_SHIFT)            /* 0x00001000 */
#define GRF_DSI_STATUS0_DPHY_ERRCONTENTIONLP0_0_SHIFT      (13U)
#define GRF_DSI_STATUS0_DPHY_ERRCONTENTIONLP0_0_MASK       (0x1U << GRF_DSI_STATUS0_DPHY_ERRCONTENTIONLP0_0_SHIFT)      /* 0x00002000 */
#define GRF_DSI_STATUS0_DPHY_ERRCONTENTIONLP1_0_SHIFT      (14U)
#define GRF_DSI_STATUS0_DPHY_ERRCONTENTIONLP1_0_MASK       (0x1U << GRF_DSI_STATUS0_DPHY_ERRCONTENTIONLP1_0_SHIFT)      /* 0x00004000 */
/* DSI_STATUS1 */
#define GRF_DSI_STATUS1_OFFSET                             (0x2C4U)
#define GRF_DSI_STATUS1                                    (0x0U)
#define GRF_DSI_STATUS1_DPHY_DA_ODTCAL_SEL_0_SHIFT         (0U)
#define GRF_DSI_STATUS1_DPHY_DA_ODTCAL_SEL_0_MASK          (0xFU << GRF_DSI_STATUS1_DPHY_DA_ODTCAL_SEL_0_SHIFT)         /* 0x0000000F */
#define GRF_DSI_STATUS1_DPHY_DA_ODTCAL_SEL_1_SHIFT         (4U)
#define GRF_DSI_STATUS1_DPHY_DA_ODTCAL_SEL_1_MASK          (0xFU << GRF_DSI_STATUS1_DPHY_DA_ODTCAL_SEL_1_SHIFT)         /* 0x000000F0 */
#define GRF_DSI_STATUS1_DPHY_DA_ODTCAL_SEL_2_SHIFT         (8U)
#define GRF_DSI_STATUS1_DPHY_DA_ODTCAL_SEL_2_MASK          (0xFU << GRF_DSI_STATUS1_DPHY_DA_ODTCAL_SEL_2_SHIFT)         /* 0x00000F00 */
#define GRF_DSI_STATUS1_DPHY_DA_ODTCAL_SEL_3_SHIFT         (12U)
#define GRF_DSI_STATUS1_DPHY_DA_ODTCAL_SEL_3_MASK          (0xFU << GRF_DSI_STATUS1_DPHY_DA_ODTCAL_SEL_3_SHIFT)         /* 0x0000F000 */
#define GRF_DSI_STATUS1_DPHY_DA_ODTCAL_SEL_4_SHIFT         (16U)
#define GRF_DSI_STATUS1_DPHY_DA_ODTCAL_SEL_4_MASK          (0xFU << GRF_DSI_STATUS1_DPHY_DA_ODTCAL_SEL_4_SHIFT)         /* 0x000F0000 */
#define GRF_DSI_STATUS1_DPHY_DA_ODTCAL_SEL_5_SHIFT         (20U)
#define GRF_DSI_STATUS1_DPHY_DA_ODTCAL_SEL_5_MASK          (0xFU << GRF_DSI_STATUS1_DPHY_DA_ODTCAL_SEL_5_SHIFT)         /* 0x00F00000 */
#define GRF_DSI_STATUS1_DPHY_DA_ODTCAL_SEL_6_SHIFT         (24U)
#define GRF_DSI_STATUS1_DPHY_DA_ODTCAL_SEL_6_MASK          (0xFU << GRF_DSI_STATUS1_DPHY_DA_ODTCAL_SEL_6_SHIFT)         /* 0x0F000000 */
#define GRF_DSI_STATUS1_DPHY_DA_ODTCAL_SEL_7_SHIFT         (28U)
#define GRF_DSI_STATUS1_DPHY_DA_ODTCAL_SEL_7_MASK          (0xFU << GRF_DSI_STATUS1_DPHY_DA_ODTCAL_SEL_7_SHIFT)         /* 0xF0000000 */
/* DSI_STATUS2 */
#define GRF_DSI_STATUS2_OFFSET                             (0x2C8U)
#define GRF_DSI_STATUS2                                    (0x0U)
#define GRF_DSI_STATUS2_DPHY_DA_ODTCAL_SEL_8_SHIFT         (0U)
#define GRF_DSI_STATUS2_DPHY_DA_ODTCAL_SEL_8_MASK          (0xFU << GRF_DSI_STATUS2_DPHY_DA_ODTCAL_SEL_8_SHIFT)         /* 0x0000000F */
#define GRF_DSI_STATUS2_DPHY_DA_ODTCAL_SEL_9_SHIFT         (4U)
#define GRF_DSI_STATUS2_DPHY_DA_ODTCAL_SEL_9_MASK          (0xFU << GRF_DSI_STATUS2_DPHY_DA_ODTCAL_SEL_9_SHIFT)         /* 0x000000F0 */
#define GRF_DSI_STATUS2_DPHY_DA_ODTCAL_SEL_10_SHIFT        (8U)
#define GRF_DSI_STATUS2_DPHY_DA_ODTCAL_SEL_10_MASK         (0xFU << GRF_DSI_STATUS2_DPHY_DA_ODTCAL_SEL_10_SHIFT)        /* 0x00000F00 */
#define GRF_DSI_STATUS2_DPHY_DA_ODTCAL_SEL_11_SHIFT        (12U)
#define GRF_DSI_STATUS2_DPHY_DA_ODTCAL_SEL_11_MASK         (0xFU << GRF_DSI_STATUS2_DPHY_DA_ODTCAL_SEL_11_SHIFT)        /* 0x0000F000 */
/* DSI_STATUS3 */
#define GRF_DSI_STATUS3_OFFSET                             (0x2CCU)
#define GRF_DSI_STATUS3                                    (0x0U)
#define GRF_DSI_STATUS3_DPHY_DEBUG_PORT_SHIFT              (0U)
#define GRF_DSI_STATUS3_DPHY_DEBUG_PORT_MASK               (0xFFFFFFFFU << GRF_DSI_STATUS3_DPHY_DEBUG_PORT_SHIFT)       /* 0xFFFFFFFF */
/* DSI_STATUS4 */
#define GRF_DSI_STATUS4_OFFSET                             (0x2D0U)
#define GRF_DSI_STATUS4                                    (0x0U)
#define GRF_DSI_STATUS4_DPHY_XCFGO_SHIFT                   (0U)
#define GRF_DSI_STATUS4_DPHY_XCFGO_MASK                    (0xFFFFFFFFU << GRF_DSI_STATUS4_DPHY_XCFGO_SHIFT)            /* 0xFFFFFFFF */
/* DSI_STATUS5 */
#define GRF_DSI_STATUS5_OFFSET                             (0x2D4U)
#define GRF_DSI_STATUS5                                    (0x0U)
#define GRF_DSI_STATUS5_DPHY_XCFGO_SHIFT                   (0U)
#define GRF_DSI_STATUS5_DPHY_XCFGO_MASK                    (0xFFFFFFFFU << GRF_DSI_STATUS5_DPHY_XCFGO_SHIFT)            /* 0xFFFFFFFF */
/* DSI_STATUS6 */
#define GRF_DSI_STATUS6_OFFSET                             (0x2D8U)
#define GRF_DSI_STATUS6                                    (0x0U)
#define GRF_DSI_STATUS6_DPHY_XCFGO_SHIFT                   (0U)
#define GRF_DSI_STATUS6_DPHY_XCFGO_MASK                    (0x3FFFU << GRF_DSI_STATUS6_DPHY_XCFGO_SHIFT)                /* 0x00003FFF */
/* DSI_STATUS7 */
#define GRF_DSI_STATUS7_OFFSET                             (0x2DCU)
#define GRF_DSI_STATUS7                                    (0x0U)
#define GRF_DSI_STATUS7_DPHY_MPOSV_SHIFT                   (0U)
#define GRF_DSI_STATUS7_DPHY_MPOSV_MASK                    (0xFFFFFFFFU << GRF_DSI_STATUS7_DPHY_MPOSV_SHIFT)            /* 0xFFFFFFFF */
/* DSI_STATUS8 */
#define GRF_DSI_STATUS8_OFFSET                             (0x2E0U)
#define GRF_DSI_STATUS8                                    (0x0U)
#define GRF_DSI_STATUS8_DPHY_MPOSV_SHIFT                   (0U)
#define GRF_DSI_STATUS8_DPHY_MPOSV_MASK                    (0x3FFU << GRF_DSI_STATUS8_DPHY_MPOSV_SHIFT)                 /* 0x000003FF */
/* MEM_CON0 */
#define GRF_MEM_CON0_OFFSET                                (0x300U)
#define GRF_MEM_CON0_PDM_MEM_EMA_SHIFT                     (0U)
#define GRF_MEM_CON0_PDM_MEM_EMA_MASK                      (0x7U << GRF_MEM_CON0_PDM_MEM_EMA_SHIFT)                     /* 0x00000007 */
#define GRF_MEM_CON0_PDM_MEM_EMAW_SHIFT                    (3U)
#define GRF_MEM_CON0_PDM_MEM_EMAW_MASK                     (0x3U << GRF_MEM_CON0_PDM_MEM_EMAW_SHIFT)                    /* 0x00000018 */
#define GRF_MEM_CON0_M4_MEM_EMA_SHIFT                      (5U)
#define GRF_MEM_CON0_M4_MEM_EMA_MASK                       (0x7U << GRF_MEM_CON0_M4_MEM_EMA_SHIFT)                      /* 0x000000E0 */
#define GRF_MEM_CON0_M4_MEM_EMAW_SHIFT                     (8U)
#define GRF_MEM_CON0_M4_MEM_EMAW_MASK                      (0x3U << GRF_MEM_CON0_M4_MEM_EMAW_SHIFT)                     /* 0x00000300 */
#define GRF_MEM_CON0_SHRM_MEM_EMA_SHIFT                    (10U)
#define GRF_MEM_CON0_SHRM_MEM_EMA_MASK                     (0x7U << GRF_MEM_CON0_SHRM_MEM_EMA_SHIFT)                    /* 0x00001C00 */
#define GRF_MEM_CON0_SHRM_MEM_EMAW_SHIFT                   (13U)
#define GRF_MEM_CON0_SHRM_MEM_EMAW_MASK                    (0x3U << GRF_MEM_CON0_SHRM_MEM_EMAW_SHIFT)                   /* 0x00006000 */
#define GRF_MEM_CON0_SHRM_MEM_EMAS_SHIFT                   (15U)
#define GRF_MEM_CON0_SHRM_MEM_EMAS_MASK                    (0x1U << GRF_MEM_CON0_SHRM_MEM_EMAS_SHIFT)                   /* 0x00008000 */
/* MEM_CON1 */
#define GRF_MEM_CON1_OFFSET                                (0x304U)
#define GRF_MEM_CON1_VOP_DP_EMAA_SHIFT                     (0U)
#define GRF_MEM_CON1_VOP_DP_EMAA_MASK                      (0x7U << GRF_MEM_CON1_VOP_DP_EMAA_SHIFT)                     /* 0x00000007 */
#define GRF_MEM_CON1_VOP_DP_EMASA_SHIFT                    (3U)
#define GRF_MEM_CON1_VOP_DP_EMASA_MASK                     (0x1U << GRF_MEM_CON1_VOP_DP_EMASA_SHIFT)                    /* 0x00000008 */
#define GRF_MEM_CON1_VOP_DP_EMAB_SHIFT                     (4U)
#define GRF_MEM_CON1_VOP_DP_EMAB_MASK                      (0x7U << GRF_MEM_CON1_VOP_DP_EMAB_SHIFT)                     /* 0x00000070 */
#define GRF_MEM_CON1_VOP_SP_EMA_SHIFT                      (7U)
#define GRF_MEM_CON1_VOP_SP_EMA_MASK                       (0x7U << GRF_MEM_CON1_VOP_SP_EMA_SHIFT)                      /* 0x00000380 */
#define GRF_MEM_CON1_VOP_SP_EMAW_SHIFT                     (10U)
#define GRF_MEM_CON1_VOP_SP_EMAW_MASK                      (0x3U << GRF_MEM_CON1_VOP_SP_EMAW_SHIFT)                     /* 0x00000C00 */
#define GRF_MEM_CON1_VOP_SP_EMAS_SHIFT                     (12U)
#define GRF_MEM_CON1_VOP_SP_EMAS_MASK                      (0x1U << GRF_MEM_CON1_VOP_SP_EMAS_SHIFT)                     /* 0x00001000 */
/* MEM_CON2 */
#define GRF_MEM_CON2_OFFSET                                (0x308U)
#define GRF_MEM_CON2_DSIHOST_MEM_EMAA_SHIFT                (0U)
#define GRF_MEM_CON2_DSIHOST_MEM_EMAA_MASK                 (0x7U << GRF_MEM_CON2_DSIHOST_MEM_EMAA_SHIFT)                /* 0x00000007 */
#define GRF_MEM_CON2_DSIHOST_MEM_EMASA_SHIFT               (3U)
#define GRF_MEM_CON2_DSIHOST_MEM_EMASA_MASK                (0x1U << GRF_MEM_CON2_DSIHOST_MEM_EMASA_SHIFT)               /* 0x00000008 */
#define GRF_MEM_CON2_DSIHOST_MEM_EMAB_SHIFT                (4U)
#define GRF_MEM_CON2_DSIHOST_MEM_EMAB_MASK                 (0x7U << GRF_MEM_CON2_DSIHOST_MEM_EMAB_SHIFT)                /* 0x00000070 */
#define GRF_MEM_CON2_VAD_MEM_EMA_SHIFT                     (7U)
#define GRF_MEM_CON2_VAD_MEM_EMA_MASK                      (0x7U << GRF_MEM_CON2_VAD_MEM_EMA_SHIFT)                     /* 0x00000380 */
#define GRF_MEM_CON2_VAD_MEM_EMAW_SHIFT                    (10U)
#define GRF_MEM_CON2_VAD_MEM_EMAW_MASK                     (0x3U << GRF_MEM_CON2_VAD_MEM_EMAW_SHIFT)                    /* 0x00000C00 */
#define GRF_MEM_CON2_ROM_EMA_SHIFT                         (12U)
#define GRF_MEM_CON2_ROM_EMA_MASK                          (0x7U << GRF_MEM_CON2_ROM_EMA_SHIFT)                         /* 0x00007000 */
/* MEM_CON3 */
#define GRF_MEM_CON3_OFFSET                                (0x30CU)
#define GRF_MEM_CON3_SDIO_MEM_EMA_SHIFT                    (0U)
#define GRF_MEM_CON3_SDIO_MEM_EMA_MASK                     (0x7U << GRF_MEM_CON3_SDIO_MEM_EMA_SHIFT)                    /* 0x00000007 */
#define GRF_MEM_CON3_SDIO_MEM_EMAW_SHIFT                   (3U)
#define GRF_MEM_CON3_SDIO_MEM_EMAW_MASK                    (0x3U << GRF_MEM_CON3_SDIO_MEM_EMAW_SHIFT)                   /* 0x00000018 */
#define GRF_MEM_CON3_SDIO_MEM_EMAS_SHIFT                   (5U)
#define GRF_MEM_CON3_SDIO_MEM_EMAS_MASK                    (0x1U << GRF_MEM_CON3_SDIO_MEM_EMAS_SHIFT)                   /* 0x00000020 */
#define GRF_MEM_CON3_DSPTCM_MEM_EMA_SHIFT                  (6U)
#define GRF_MEM_CON3_DSPTCM_MEM_EMA_MASK                   (0x7U << GRF_MEM_CON3_DSPTCM_MEM_EMA_SHIFT)                  /* 0x000001C0 */
#define GRF_MEM_CON3_DSPTCM_MEM_EMAW_SHIFT                 (9U)
#define GRF_MEM_CON3_DSPTCM_MEM_EMAW_MASK                  (0x3U << GRF_MEM_CON3_DSPTCM_MEM_EMAW_SHIFT)                 /* 0x00000600 */
#define GRF_MEM_CON3_DSPCACHE_MEM_EMA_SHIFT                (11U)
#define GRF_MEM_CON3_DSPCACHE_MEM_EMA_MASK                 (0x7U << GRF_MEM_CON3_DSPCACHE_MEM_EMA_SHIFT)                /* 0x00003800 */
#define GRF_MEM_CON3_DSPCACHE_MEM_EMAW_SHIFT               (14U)
#define GRF_MEM_CON3_DSPCACHE_MEM_EMAW_MASK                (0x3U << GRF_MEM_CON3_DSPCACHE_MEM_EMAW_SHIFT)               /* 0x0000C000 */
/* MEM_CON4 */
#define GRF_MEM_CON4_OFFSET                                (0x310U)
#define GRF_MEM_CON4_CIF_DP_EMAA_SHIFT                     (0U)
#define GRF_MEM_CON4_CIF_DP_EMAA_MASK                      (0x7U << GRF_MEM_CON4_CIF_DP_EMAA_SHIFT)                     /* 0x00000007 */
#define GRF_MEM_CON4_CIF_DP_EMASA_SHIFT                    (3U)
#define GRF_MEM_CON4_CIF_DP_EMASA_MASK                     (0x1U << GRF_MEM_CON4_CIF_DP_EMASA_SHIFT)                    /* 0x00000008 */
#define GRF_MEM_CON4_CIF_DP_EMAB_SHIFT                     (4U)
#define GRF_MEM_CON4_CIF_DP_EMAB_MASK                      (0x7U << GRF_MEM_CON4_CIF_DP_EMAB_SHIFT)                     /* 0x00000070 */
#define GRF_MEM_CON4_CIF_SP_EMA_SHIFT                      (7U)
#define GRF_MEM_CON4_CIF_SP_EMA_MASK                       (0x7U << GRF_MEM_CON4_CIF_SP_EMA_SHIFT)                      /* 0x00000380 */
#define GRF_MEM_CON4_CIF_SP_EMAW_SHIFT                     (10U)
#define GRF_MEM_CON4_CIF_SP_EMAW_MASK                      (0x3U << GRF_MEM_CON4_CIF_SP_EMAW_SHIFT)                     /* 0x00000C00 */
/* MEM_CON5 */
#define GRF_MEM_CON5_OFFSET                                (0x314U)
#define GRF_MEM_CON5_USB2_SP_EMA_SHIFT                     (0U)
#define GRF_MEM_CON5_USB2_SP_EMA_MASK                      (0x7U << GRF_MEM_CON5_USB2_SP_EMA_SHIFT)                     /* 0x00000007 */
#define GRF_MEM_CON5_USB2_SP_EMAW_SHIFT                    (3U)
#define GRF_MEM_CON5_USB2_SP_EMAW_MASK                     (0x3U << GRF_MEM_CON5_USB2_SP_EMAW_SHIFT)                    /* 0x00000018 */
#define GRF_MEM_CON5_VOP_DPRA_EMA_SHIFT                    (5U)
#define GRF_MEM_CON5_VOP_DPRA_EMA_MASK                     (0x7U << GRF_MEM_CON5_VOP_DPRA_EMA_SHIFT)                    /* 0x000000E0 */
#define GRF_MEM_CON5_VOP_DPRA_EMAW_SHIFT                   (8U)
#define GRF_MEM_CON5_VOP_DPRA_EMAW_MASK                    (0x3U << GRF_MEM_CON5_VOP_DPRA_EMAW_SHIFT)                   /* 0x00000300 */
#define GRF_MEM_CON5_VOP_DPRA_EMAS_SHIFT                   (10U)
#define GRF_MEM_CON5_VOP_DPRA_EMAS_MASK                    (0x1U << GRF_MEM_CON5_VOP_DPRA_EMAS_SHIFT)                   /* 0x00000400 */
#define GRF_MEM_CON5_VOP_DPRA_EMAP_SHIFT                   (11U)
#define GRF_MEM_CON5_VOP_DPRA_EMAP_MASK                    (0x1U << GRF_MEM_CON5_VOP_DPRA_EMAP_SHIFT)                   /* 0x00000800 */
/* MEM_CON6 */
#define GRF_MEM_CON6_OFFSET                                (0x318U)
#define GRF_MEM_CON6_ACODEC_SP_EMA_SHIFT                   (0U)
#define GRF_MEM_CON6_ACODEC_SP_EMA_MASK                    (0x7U << GRF_MEM_CON6_ACODEC_SP_EMA_SHIFT)                   /* 0x00000007 */
#define GRF_MEM_CON6_ACODEC_SP_EMAW_SHIFT                  (3U)
#define GRF_MEM_CON6_ACODEC_SP_EMAW_MASK                   (0x3U << GRF_MEM_CON6_ACODEC_SP_EMAW_SHIFT)                  /* 0x00000018 */
/* USBPHY_CON0 */
#define GRF_USBPHY_CON0_OFFSET                             (0x340U)
#define GRF_USBPHY_CON0_UTMI_SEL_SHIFT                     (0U)
#define GRF_USBPHY_CON0_UTMI_SEL_MASK                      (0x1U << GRF_USBPHY_CON0_UTMI_SEL_SHIFT)                     /* 0x00000001 */
#define GRF_USBPHY_CON0_UTMI_SUSPEND_N_SHIFT               (1U)
#define GRF_USBPHY_CON0_UTMI_SUSPEND_N_MASK                (0x1U << GRF_USBPHY_CON0_UTMI_SUSPEND_N_SHIFT)               /* 0x00000002 */
#define GRF_USBPHY_CON0_UTMI_OPMODE_SHIFT                  (2U)
#define GRF_USBPHY_CON0_UTMI_OPMODE_MASK                   (0x3U << GRF_USBPHY_CON0_UTMI_OPMODE_SHIFT)                  /* 0x0000000C */
#define GRF_USBPHY_CON0_UTMI_XCVRSELECT_SHIFT              (4U)
#define GRF_USBPHY_CON0_UTMI_XCVRSELECT_MASK               (0x3U << GRF_USBPHY_CON0_UTMI_XCVRSELECT_SHIFT)              /* 0x00000030 */
#define GRF_USBPHY_CON0_UTMI_TERMSELECT_SHIFT              (6U)
#define GRF_USBPHY_CON0_UTMI_TERMSELECT_MASK               (0x1U << GRF_USBPHY_CON0_UTMI_TERMSELECT_SHIFT)              /* 0x00000040 */
#define GRF_USBPHY_CON0_UTMI_DPPULLDOWN_SHIFT              (7U)
#define GRF_USBPHY_CON0_UTMI_DPPULLDOWN_MASK               (0x1U << GRF_USBPHY_CON0_UTMI_DPPULLDOWN_SHIFT)              /* 0x00000080 */
#define GRF_USBPHY_CON0_UTMI_DMPULLDOWN_SHIFT              (8U)
#define GRF_USBPHY_CON0_UTMI_DMPULLDOWN_MASK               (0x1U << GRF_USBPHY_CON0_UTMI_DMPULLDOWN_SHIFT)              /* 0x00000100 */
/* USBPHY_CON1 */
#define GRF_USBPHY_CON1_OFFSET                             (0x344U)
#define GRF_USBPHY_CON1_DATABUS16_SHIFT                    (0U)
#define GRF_USBPHY_CON1_DATABUS16_MASK                     (0x1U << GRF_USBPHY_CON1_DATABUS16_SHIFT)                    /* 0x00000001 */
#define GRF_USBPHY_CON1_TX_ENABLE_N_SHIFT                  (1U)
#define GRF_USBPHY_CON1_TX_ENABLE_N_MASK                   (0x1U << GRF_USBPHY_CON1_TX_ENABLE_N_SHIFT)                  /* 0x00000002 */
#define GRF_USBPHY_CON1_TX_DAT_SHIFT                       (2U)
#define GRF_USBPHY_CON1_TX_DAT_MASK                        (0x1U << GRF_USBPHY_CON1_TX_DAT_SHIFT)                       /* 0x00000004 */
#define GRF_USBPHY_CON1_TX_SE0_SHIFT                       (3U)
#define GRF_USBPHY_CON1_TX_SE0_MASK                        (0x1U << GRF_USBPHY_CON1_TX_SE0_SHIFT)                       /* 0x00000008 */
#define GRF_USBPHY_CON1_VCONTROL_SHIFT                     (4U)
#define GRF_USBPHY_CON1_VCONTROL_MASK                      (0xFU << GRF_USBPHY_CON1_VCONTROL_SHIFT)                     /* 0x000000F0 */
#define GRF_USBPHY_CON1_VCONTROLLOADM_SHIFT                (8U)
#define GRF_USBPHY_CON1_VCONTROLLOADM_MASK                 (0x1U << GRF_USBPHY_CON1_VCONTROLLOADM_SHIFT)                /* 0x00000100 */
#define GRF_USBPHY_CON1_TXBITSTUFFENABLE_SHIFT             (9U)
#define GRF_USBPHY_CON1_TXBITSTUFFENABLE_MASK              (0x1U << GRF_USBPHY_CON1_TXBITSTUFFENABLE_SHIFT)             /* 0x00000200 */
#define GRF_USBPHY_CON1_TXBITSTUFFENABLEH_SHIFT            (10U)
#define GRF_USBPHY_CON1_TXBITSTUFFENABLEH_MASK             (0x1U << GRF_USBPHY_CON1_TXBITSTUFFENABLEH_SHIFT)            /* 0x00000400 */
#define GRF_USBPHY_CON1_FSLSSERIALMODE_SHIFT               (11U)
#define GRF_USBPHY_CON1_FSLSSERIALMODE_MASK                (0x1U << GRF_USBPHY_CON1_FSLSSERIALMODE_SHIFT)               /* 0x00000800 */
#define GRF_USBPHY_CON1_PLL_EN_SHIFT                       (12U)
#define GRF_USBPHY_CON1_PLL_EN_MASK                        (0x1U << GRF_USBPHY_CON1_PLL_EN_SHIFT)                       /* 0x00001000 */
#define GRF_USBPHY_CON1_LPM_ALIVE_SHIFT                    (13U)
#define GRF_USBPHY_CON1_LPM_ALIVE_MASK                     (0x1U << GRF_USBPHY_CON1_LPM_ALIVE_SHIFT)                    /* 0x00002000 */
#define GRF_USBPHY_CON1_XTLSEL_SHIFT                       (14U)
#define GRF_USBPHY_CON1_XTLSEL_MASK                        (0x3U << GRF_USBPHY_CON1_XTLSEL_SHIFT)                       /* 0x0000C000 */
/* USBPHY_CON2 */
#define GRF_USBPHY_CON2_OFFSET                             (0x348U)
#define GRF_USBPHY_CON2_DEBUG_SEL_SHIFT                    (0U)
#define GRF_USBPHY_CON2_DEBUG_SEL_MASK                     (0xFU << GRF_USBPHY_CON2_DEBUG_SEL_SHIFT)                    /* 0x0000000F */
#define GRF_USBPHY_CON2_LS_EN_SHIFT                        (4U)
#define GRF_USBPHY_CON2_LS_EN_MASK                         (0x1U << GRF_USBPHY_CON2_LS_EN_SHIFT)                        /* 0x00000010 */
#define GRF_USBPHY_CON2_HS_BIST_MODE_SHIFT                 (5U)
#define GRF_USBPHY_CON2_HS_BIST_MODE_MASK                  (0x1U << GRF_USBPHY_CON2_HS_BIST_MODE_SHIFT)                 /* 0x00000020 */
#define GRF_USBPHY_CON2_USB_LINESTATE_IRQ_EN_SHIFT         (8U)
#define GRF_USBPHY_CON2_USB_LINESTATE_IRQ_EN_MASK          (0x1U << GRF_USBPHY_CON2_USB_LINESTATE_IRQ_EN_SHIFT)         /* 0x00000100 */
#define GRF_USBPHY_CON2_USB_DISCONNECT_IRQ_EN_SHIFT        (9U)
#define GRF_USBPHY_CON2_USB_DISCONNECT_IRQ_EN_MASK         (0x3U << GRF_USBPHY_CON2_USB_DISCONNECT_IRQ_EN_SHIFT)        /* 0x00000600 */
/* USBPHY_CON3 */
#define GRF_USBPHY_CON3_OFFSET                             (0x34CU)
#define GRF_USBPHY_CON3_XCFG_COARSE_TUNE_NUM_SHIFT         (0U)
#define GRF_USBPHY_CON3_XCFG_COARSE_TUNE_NUM_MASK          (0x7U << GRF_USBPHY_CON3_XCFG_COARSE_TUNE_NUM_SHIFT)         /* 0x00000007 */
#define GRF_USBPHY_CON3_XCFG_FINE_TUNE_NUM_SHIFT           (3U)
#define GRF_USBPHY_CON3_XCFG_FINE_TUNE_NUM_MASK            (0x7U << GRF_USBPHY_CON3_XCFG_FINE_TUNE_NUM_SHIFT)           /* 0x00000038 */
#define GRF_USBPHY_CON3_XCFG_LOCK_RANGE_MAX_SHIFT          (6U)
#define GRF_USBPHY_CON3_XCFG_LOCK_RANGE_MAX_MASK           (0x7U << GRF_USBPHY_CON3_XCFG_LOCK_RANGE_MAX_SHIFT)          /* 0x000001C0 */
#define GRF_USBPHY_CON3_XCFG_LOCK_RANGE_MIN_SHIFT          (9U)
#define GRF_USBPHY_CON3_XCFG_LOCK_RANGE_MIN_MASK           (0x7U << GRF_USBPHY_CON3_XCFG_LOCK_RANGE_MIN_SHIFT)          /* 0x00000E00 */
/* USBPHY_CON4 */
#define GRF_USBPHY_CON4_OFFSET                             (0x350U)
#define GRF_USBPHY_CON4_XCFGI_SHIFT                        (0U)
#define GRF_USBPHY_CON4_XCFGI_MASK                         (0xFFFFFFFFU << GRF_USBPHY_CON4_XCFGI_SHIFT)                 /* 0xFFFFFFFF */
/* USBPHY_CON5 */
#define GRF_USBPHY_CON5_OFFSET                             (0x354U)
#define GRF_USBPHY_CON5_XCFGI_SHIFT                        (0U)
#define GRF_USBPHY_CON5_XCFGI_MASK                         (0xFFFFFFFFU << GRF_USBPHY_CON5_XCFGI_SHIFT)                 /* 0xFFFFFFFF */
/* USBPHY_CON6 */
#define GRF_USBPHY_CON6_OFFSET                             (0x358U)
#define GRF_USBPHY_CON6_XCFGI_SHIFT                        (0U)
#define GRF_USBPHY_CON6_XCFGI_MASK                         (0x3FU << GRF_USBPHY_CON6_XCFGI_SHIFT)                       /* 0x0000003F */
/* USBPHY_CON7 */
#define GRF_USBPHY_CON7_OFFSET                             (0x35CU)
#define GRF_USBPHY_CON7_LINESTATE_DET_CNT_SHIFT            (0U)
#define GRF_USBPHY_CON7_LINESTATE_DET_CNT_MASK             (0xFFFFFU << GRF_USBPHY_CON7_LINESTATE_DET_CNT_SHIFT)        /* 0x000FFFFF */
/* USBPHY_CON8 */
#define GRF_USBPHY_CON8_OFFSET                             (0x360U)
#define GRF_USBPHY_CON8_DISCONNECT_DET_CNT_SHIFT           (0U)
#define GRF_USBPHY_CON8_DISCONNECT_DET_CNT_MASK            (0xFFFFFU << GRF_USBPHY_CON8_DISCONNECT_DET_CNT_SHIFT)       /* 0x000FFFFF */
/* USBPHY_STATUS0 */
#define GRF_USBPHY_STATUS0_OFFSET                          (0x370U)
#define GRF_USBPHY_STATUS0                                 (0x0U)
#define GRF_USBPHY_STATUS0_XCFGO_SHIFT                     (0U)
#define GRF_USBPHY_STATUS0_XCFGO_MASK                      (0xFFU << GRF_USBPHY_STATUS0_XCFGO_SHIFT)                    /* 0x000000FF */
#define GRF_USBPHY_STATUS0_DEBUG_OUT_SHIFT                 (8U)
#define GRF_USBPHY_STATUS0_DEBUG_OUT_MASK                  (0xFFFFU << GRF_USBPHY_STATUS0_DEBUG_OUT_SHIFT)              /* 0x00FFFF00 */
#define GRF_USBPHY_STATUS0_BIST_OK_SHIFT                   (24U)
#define GRF_USBPHY_STATUS0_BIST_OK_MASK                    (0x1U << GRF_USBPHY_STATUS0_BIST_OK_SHIFT)                   /* 0x01000000 */
#define GRF_USBPHY_STATUS0_DATA_OE_SHIFT                   (25U)
#define GRF_USBPHY_STATUS0_DATA_OE_MASK                    (0x1U << GRF_USBPHY_STATUS0_DATA_OE_SHIFT)                   /* 0x02000000 */
#define GRF_USBPHY_STATUS0_UTMI_HOSTDISCONNECT_SHIFT       (26U)
#define GRF_USBPHY_STATUS0_UTMI_HOSTDISCONNECT_MASK        (0x1U << GRF_USBPHY_STATUS0_UTMI_HOSTDISCONNECT_SHIFT)       /* 0x04000000 */
#define GRF_USBPHY_STATUS0_UTMI_LINESTATE_SHIFT            (27U)
#define GRF_USBPHY_STATUS0_UTMI_LINESTATE_MASK             (0x3U << GRF_USBPHY_STATUS0_UTMI_LINESTATE_SHIFT)            /* 0x18000000 */
#define GRF_USBPHY_STATUS0_RX_RCV_SHIFT                    (29U)
#define GRF_USBPHY_STATUS0_RX_RCV_MASK                     (0x1U << GRF_USBPHY_STATUS0_RX_RCV_SHIFT)                    /* 0x20000000 */
#define GRF_USBPHY_STATUS0_RX_DP_SHIFT                     (30U)
#define GRF_USBPHY_STATUS0_RX_DP_MASK                      (0x1U << GRF_USBPHY_STATUS0_RX_DP_SHIFT)                     /* 0x40000000 */
#define GRF_USBPHY_STATUS0_RX_DM_SHIFT                     (31U)
#define GRF_USBPHY_STATUS0_RX_DM_MASK                      (0x1U << GRF_USBPHY_STATUS0_RX_DM_SHIFT)                     /* 0x80000000 */
/* USBPHY_STATUS1 */
#define GRF_USBPHY_STATUS1_OFFSET                          (0x374U)
#define GRF_USBPHY_STATUS1_USB_LINESTATE_IRQ_SHIFT         (8U)
#define GRF_USBPHY_STATUS1_USB_LINESTATE_IRQ_MASK          (0x1U << GRF_USBPHY_STATUS1_USB_LINESTATE_IRQ_SHIFT)         /* 0x00000100 */
#define GRF_USBPHY_STATUS1_USB_DISCONNECT_IRQ_SHIFT        (9U)
#define GRF_USBPHY_STATUS1_USB_DISCONNECT_IRQ_MASK         (0x3U << GRF_USBPHY_STATUS1_USB_DISCONNECT_IRQ_SHIFT)        /* 0x00000600 */
/* DMAC_CON3 */
#define GRF_DMAC_CON3_OFFSET                               (0x38CU)
#define GRF_DMAC_CON3_GRF_DRTYPE_DMAC_AUDIOPWM_SHIFT       (12U)
#define GRF_DMAC_CON3_GRF_DRTYPE_DMAC_AUDIOPWM_MASK        (0x3U << GRF_DMAC_CON3_GRF_DRTYPE_DMAC_AUDIOPWM_SHIFT)       /* 0x00003000 */
#define GRF_DMAC_CON3_GRF_CON_DMAC_REQ_MODIFY_DIS_AUDIOPWM_SHIFT (15U)
#define GRF_DMAC_CON3_GRF_CON_DMAC_REQ_MODIFY_DIS_AUDIOPWM_MASK (0x1U << GRF_DMAC_CON3_GRF_CON_DMAC_REQ_MODIFY_DIS_AUDIOPWM_SHIFT) /* 0x00008000 */
/* DMAC_CON4 */
#define GRF_DMAC_CON4_OFFSET                               (0x390U)
#define GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_UART0TX_SHIFT (0U)
#define GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_UART0TX_MASK (0x1U << GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_UART0TX_SHIFT) /* 0x00000001 */
#define GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_UART0RX_SHIFT (1U)
#define GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_UART0RX_MASK (0x1U << GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_UART0RX_SHIFT) /* 0x00000002 */
#define GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_UART1TX_SHIFT (2U)
#define GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_UART1TX_MASK (0x1U << GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_UART1TX_SHIFT) /* 0x00000004 */
#define GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_UART1RX_SHIFT (3U)
#define GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_UART1RX_MASK (0x1U << GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_UART1RX_SHIFT) /* 0x00000008 */
#define GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_UART2TX_SHIFT (4U)
#define GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_UART2TX_MASK (0x1U << GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_UART2TX_SHIFT) /* 0x00000010 */
#define GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_UART2RX_SHIFT (5U)
#define GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_UART2RX_MASK (0x1U << GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_UART2RX_SHIFT) /* 0x00000020 */
#define GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_I2STX_SHIFT (6U)
#define GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_I2STX_MASK (0x1U << GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_I2STX_SHIFT) /* 0x00000040 */
#define GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_I2SRX_SHIFT (7U)
#define GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_I2SRX_MASK (0x1U << GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_I2SRX_SHIFT) /* 0x00000080 */
#define GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_I2S1TX_SHIFT (8U)
#define GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_I2S1TX_MASK (0x1U << GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_I2S1TX_SHIFT) /* 0x00000100 */
#define GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_I2S1RX_SHIFT (9U)
#define GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_I2S1RX_MASK (0x1U << GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_I2S1RX_SHIFT) /* 0x00000200 */
#define GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_PDM_SHIFT (10U)
#define GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_PDM_MASK (0x1U << GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_PDM_SHIFT) /* 0x00000400 */
#define GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_SPI1TX_SHIFT (11U)
#define GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_SPI1TX_MASK (0x1U << GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_SPI1TX_SHIFT) /* 0x00000800 */
#define GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_SPI1RX_SHIFT (12U)
#define GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_SPI1RX_MASK (0x1U << GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_SPI1RX_SHIFT) /* 0x00001000 */
#define GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_SPI2TX_SHIFT (13U)
#define GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_SPI2TX_MASK (0x1U << GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_SPI2TX_SHIFT) /* 0x00002000 */
#define GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_SPI2RX_SHIFT (14U)
#define GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_SPI2RX_MASK (0x1U << GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_SPI2RX_SHIFT) /* 0x00004000 */
#define GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_PWM_SHIFT (15U)
#define GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_PWM_MASK (0x1U << GRF_DMAC_CON4_GRF_CON_DMAC_REQ_MODIFY_DIS_PWM_SHIFT) /* 0x00008000 */
/* DMAC_CON5 */
#define GRF_DMAC_CON5_OFFSET                               (0x394U)
#define GRF_DMAC_CON5_GRF_DRTYPE_DMAC_UART0_TX_SHIFT       (0U)
#define GRF_DMAC_CON5_GRF_DRTYPE_DMAC_UART0_TX_MASK        (0x3U << GRF_DMAC_CON5_GRF_DRTYPE_DMAC_UART0_TX_SHIFT)       /* 0x00000003 */
#define GRF_DMAC_CON5_GRF_DRTYPE_DMAC_UART0_RX_SHIFT       (2U)
#define GRF_DMAC_CON5_GRF_DRTYPE_DMAC_UART0_RX_MASK        (0x3U << GRF_DMAC_CON5_GRF_DRTYPE_DMAC_UART0_RX_SHIFT)       /* 0x0000000C */
#define GRF_DMAC_CON5_GRF_DRTYPE_DMAC_UART1_TX_SHIFT       (4U)
#define GRF_DMAC_CON5_GRF_DRTYPE_DMAC_UART1_TX_MASK        (0x3U << GRF_DMAC_CON5_GRF_DRTYPE_DMAC_UART1_TX_SHIFT)       /* 0x00000030 */
#define GRF_DMAC_CON5_GRF_DRTYPE_DMAC_UART1_RX_SHIFT       (6U)
#define GRF_DMAC_CON5_GRF_DRTYPE_DMAC_UART1_RX_MASK        (0x3U << GRF_DMAC_CON5_GRF_DRTYPE_DMAC_UART1_RX_SHIFT)       /* 0x000000C0 */
#define GRF_DMAC_CON5_GRF_DRTYPE_DMAC_UART2_TX_SHIFT       (8U)
#define GRF_DMAC_CON5_GRF_DRTYPE_DMAC_UART2_TX_MASK        (0x3U << GRF_DMAC_CON5_GRF_DRTYPE_DMAC_UART2_TX_SHIFT)       /* 0x00000300 */
#define GRF_DMAC_CON5_GRF_DRTYPE_DMAC_UART2_RX_SHIFT       (10U)
#define GRF_DMAC_CON5_GRF_DRTYPE_DMAC_UART2_RX_MASK        (0x3U << GRF_DMAC_CON5_GRF_DRTYPE_DMAC_UART2_RX_SHIFT)       /* 0x00000C00 */
#define GRF_DMAC_CON5_GRF_DRTYPE_DMAC_I2S_TX_SHIFT         (12U)
#define GRF_DMAC_CON5_GRF_DRTYPE_DMAC_I2S_TX_MASK          (0x3U << GRF_DMAC_CON5_GRF_DRTYPE_DMAC_I2S_TX_SHIFT)         /* 0x00003000 */
#define GRF_DMAC_CON5_GRF_DRTYPE_DMAC_I2S_RX_SHIFT         (14U)
#define GRF_DMAC_CON5_GRF_DRTYPE_DMAC_I2S_RX_MASK          (0x3U << GRF_DMAC_CON5_GRF_DRTYPE_DMAC_I2S_RX_SHIFT)         /* 0x0000C000 */
/* DMAC_CON6 */
#define GRF_DMAC_CON6_OFFSET                               (0x398U)
#define GRF_DMAC_CON6_GRF_DRTYPE_DMAC_I2S1_TX_SHIFT        (0U)
#define GRF_DMAC_CON6_GRF_DRTYPE_DMAC_I2S1_TX_MASK         (0x3U << GRF_DMAC_CON6_GRF_DRTYPE_DMAC_I2S1_TX_SHIFT)        /* 0x00000003 */
#define GRF_DMAC_CON6_GRF_DRTYPE_DMAC_I2S1_RX_SHIFT        (2U)
#define GRF_DMAC_CON6_GRF_DRTYPE_DMAC_I2S1_RX_MASK         (0x3U << GRF_DMAC_CON6_GRF_DRTYPE_DMAC_I2S1_RX_SHIFT)        /* 0x0000000C */
#define GRF_DMAC_CON6_GRF_DRTYPE_DMAC_PDM_SHIFT            (4U)
#define GRF_DMAC_CON6_GRF_DRTYPE_DMAC_PDM_MASK             (0x3U << GRF_DMAC_CON6_GRF_DRTYPE_DMAC_PDM_SHIFT)            /* 0x00000030 */
#define GRF_DMAC_CON6_GRF_DRTYPE_DMAC_SPI1_TX_SHIFT        (6U)
#define GRF_DMAC_CON6_GRF_DRTYPE_DMAC_SPI1_TX_MASK         (0x3U << GRF_DMAC_CON6_GRF_DRTYPE_DMAC_SPI1_TX_SHIFT)        /* 0x000000C0 */
#define GRF_DMAC_CON6_GRF_DRTYPE_DMAC_SPI1_RX_SHIFT        (8U)
#define GRF_DMAC_CON6_GRF_DRTYPE_DMAC_SPI1_RX_MASK         (0x3U << GRF_DMAC_CON6_GRF_DRTYPE_DMAC_SPI1_RX_SHIFT)        /* 0x00000300 */
#define GRF_DMAC_CON6_GRF_DRTYPE_DMAC_SPI2_TX_SHIFT        (10U)
#define GRF_DMAC_CON6_GRF_DRTYPE_DMAC_SPI2_TX_MASK         (0x3U << GRF_DMAC_CON6_GRF_DRTYPE_DMAC_SPI2_TX_SHIFT)        /* 0x00000C00 */
#define GRF_DMAC_CON6_GRF_DRTYPE_DMAC_SPI2_RX_SHIFT        (12U)
#define GRF_DMAC_CON6_GRF_DRTYPE_DMAC_SPI2_RX_MASK         (0x3U << GRF_DMAC_CON6_GRF_DRTYPE_DMAC_SPI2_RX_SHIFT)        /* 0x00003000 */
#define GRF_DMAC_CON6_GRF_DRTYPE_DMAC_PWM_SHIFT            (14U)
#define GRF_DMAC_CON6_GRF_DRTYPE_DMAC_PWM_MASK             (0x3U << GRF_DMAC_CON6_GRF_DRTYPE_DMAC_PWM_SHIFT)            /* 0x0000C000 */
/* FAST_BOOT_EN */
#define GRF_FAST_BOOT_EN_OFFSET                            (0x3C0U)
#define GRF_FAST_BOOT_EN_GRF_CON_FAST_BOOT_EN_SHIFT        (0U)
#define GRF_FAST_BOOT_EN_GRF_CON_FAST_BOOT_EN_MASK         (0x1U << GRF_FAST_BOOT_EN_GRF_CON_FAST_BOOT_EN_SHIFT)        /* 0x00000001 */
/* FAST_BOOT_ADDR */
#define GRF_FAST_BOOT_ADDR_OFFSET                          (0x3C4U)
#define GRF_FAST_BOOT_ADDR_GRF_CON_FAST_BOOT_ADDR_SHIFT    (0U)
#define GRF_FAST_BOOT_ADDR_GRF_CON_FAST_BOOT_ADDR_MASK     (0xFFFFFFFFU << GRF_FAST_BOOT_ADDR_GRF_CON_FAST_BOOT_ADDR_SHIFT) /* 0xFFFFFFFF */
/* OS_REG0 */
#define GRF_OS_REG0_OFFSET                                 (0x400U)
#define GRF_OS_REG0_OS_REG_SHIFT                           (0U)
#define GRF_OS_REG0_OS_REG_MASK                            (0xFFFFFFFFU << GRF_OS_REG0_OS_REG_SHIFT)                    /* 0xFFFFFFFF */
/* OS_REG1 */
#define GRF_OS_REG1_OFFSET                                 (0x404U)
#define GRF_OS_REG1_OS_REG_SHIFT                           (0U)
#define GRF_OS_REG1_OS_REG_MASK                            (0xFFFFFFFFU << GRF_OS_REG1_OS_REG_SHIFT)                    /* 0xFFFFFFFF */
/* OS_REG2 */
#define GRF_OS_REG2_OFFSET                                 (0x408U)
#define GRF_OS_REG2_OS_REG_SHIFT                           (0U)
#define GRF_OS_REG2_OS_REG_MASK                            (0xFFFFFFFFU << GRF_OS_REG2_OS_REG_SHIFT)                    /* 0xFFFFFFFF */
/* OS_REG3 */
#define GRF_OS_REG3_OFFSET                                 (0x40CU)
#define GRF_OS_REG3_OS_REG_SHIFT                           (0U)
#define GRF_OS_REG3_OS_REG_MASK                            (0xFFFFFFFFU << GRF_OS_REG3_OS_REG_SHIFT)                    /* 0xFFFFFFFF */
/* OS_REG4 */
#define GRF_OS_REG4_OFFSET                                 (0x410U)
#define GRF_OS_REG4_OS_REG_SHIFT                           (0U)
#define GRF_OS_REG4_OS_REG_MASK                            (0xFFFFFFFFU << GRF_OS_REG4_OS_REG_SHIFT)                    /* 0xFFFFFFFF */
/* OS_REG5 */
#define GRF_OS_REG5_OFFSET                                 (0x414U)
#define GRF_OS_REG5_OS_REG_SHIFT                           (0U)
#define GRF_OS_REG5_OS_REG_MASK                            (0xFFFFFFFFU << GRF_OS_REG5_OS_REG_SHIFT)                    /* 0xFFFFFFFF */
/* OS_REG6 */
#define GRF_OS_REG6_OFFSET                                 (0x418U)
#define GRF_OS_REG6_OS_REG_SHIFT                           (0U)
#define GRF_OS_REG6_OS_REG_MASK                            (0xFFFFFFFFU << GRF_OS_REG6_OS_REG_SHIFT)                    /* 0xFFFFFFFF */
/* OS_REG7 */
#define GRF_OS_REG7_OFFSET                                 (0x41CU)
#define GRF_OS_REG7_OS_REG_SHIFT                           (0U)
#define GRF_OS_REG7_OS_REG_MASK                            (0xFFFFFFFFU << GRF_OS_REG7_OS_REG_SHIFT)                    /* 0xFFFFFFFF */
/* CHIP_ID */
#define GRF_CHIP_ID_OFFSET                                 (0xF00U)
#define GRF_CHIP_ID                                        (0x2108U)
#define GRF_CHIP_ID_CHIP_ID_SHIFT                          (0U)
#define GRF_CHIP_ID_CHIP_ID_MASK                           (0xFFFFFFFFU << GRF_CHIP_ID_CHIP_ID_SHIFT)                   /* 0xFFFFFFFF */
/******************************************MBOX******************************************/
/* A2B_INTEN */
#define MBOX_A2B_INTEN_OFFSET                              (0x0U)
#define MBOX_A2B_INTEN_INT0_SHIFT                          (0U)
#define MBOX_A2B_INTEN_INT0_MASK                           (0x1U << MBOX_A2B_INTEN_INT0_SHIFT)                          /* 0x00000001 */
#define MBOX_A2B_INTEN_INT1_SHIFT                          (1U)
#define MBOX_A2B_INTEN_INT1_MASK                           (0x1U << MBOX_A2B_INTEN_INT1_SHIFT)                          /* 0x00000002 */
#define MBOX_A2B_INTEN_INT2_SHIFT                          (2U)
#define MBOX_A2B_INTEN_INT2_MASK                           (0x1U << MBOX_A2B_INTEN_INT2_SHIFT)                          /* 0x00000004 */
#define MBOX_A2B_INTEN_INT3_SHIFT                          (3U)
#define MBOX_A2B_INTEN_INT3_MASK                           (0x1U << MBOX_A2B_INTEN_INT3_SHIFT)                          /* 0x00000008 */
/* A2B_STATUS */
#define MBOX_A2B_STATUS_OFFSET                             (0x4U)
#define MBOX_A2B_STATUS_INT0_SHIFT                         (0U)
#define MBOX_A2B_STATUS_INT0_MASK                          (0x1U << MBOX_A2B_STATUS_INT0_SHIFT)                         /* 0x00000001 */
#define MBOX_A2B_STATUS_INT1_SHIFT                         (1U)
#define MBOX_A2B_STATUS_INT1_MASK                          (0x1U << MBOX_A2B_STATUS_INT1_SHIFT)                         /* 0x00000002 */
#define MBOX_A2B_STATUS_INT2_SHIFT                         (2U)
#define MBOX_A2B_STATUS_INT2_MASK                          (0x1U << MBOX_A2B_STATUS_INT2_SHIFT)                         /* 0x00000004 */
#define MBOX_A2B_STATUS_INT3_SHIFT                         (3U)
#define MBOX_A2B_STATUS_INT3_MASK                          (0x1U << MBOX_A2B_STATUS_INT3_SHIFT)                         /* 0x00000008 */
/* A2B_CMD_0 */
#define MBOX_A2B_CMD_0_OFFSET                              (0x8U)
#define MBOX_A2B_CMD_0_COMMAND_SHIFT                       (0U)
#define MBOX_A2B_CMD_0_COMMAND_MASK                        (0xFFFFFFFFU << MBOX_A2B_CMD_0_COMMAND_SHIFT)                /* 0xFFFFFFFF */
/* A2B_DAT_0 */
#define MBOX_A2B_DAT_0_OFFSET                              (0xCU)
#define MBOX_A2B_DAT_0_DATA_SHIFT                          (0U)
#define MBOX_A2B_DAT_0_DATA_MASK                           (0xFFFFFFFFU << MBOX_A2B_DAT_0_DATA_SHIFT)                   /* 0xFFFFFFFF */
/* A2B_CMD_1 */
#define MBOX_A2B_CMD_1_OFFSET                              (0x10U)
#define MBOX_A2B_CMD_1_COMMAND_SHIFT                       (0U)
#define MBOX_A2B_CMD_1_COMMAND_MASK                        (0xFFFFFFFFU << MBOX_A2B_CMD_1_COMMAND_SHIFT)                /* 0xFFFFFFFF */
/* A2B_DAT_1 */
#define MBOX_A2B_DAT_1_OFFSET                              (0x14U)
#define MBOX_A2B_DAT_1_DATA_SHIFT                          (0U)
#define MBOX_A2B_DAT_1_DATA_MASK                           (0xFFFFFFFFU << MBOX_A2B_DAT_1_DATA_SHIFT)                   /* 0xFFFFFFFF */
/* A2B_CMD_2 */
#define MBOX_A2B_CMD_2_OFFSET                              (0x18U)
#define MBOX_A2B_CMD_2_COMMAND_SHIFT                       (0U)
#define MBOX_A2B_CMD_2_COMMAND_MASK                        (0xFFFFFFFFU << MBOX_A2B_CMD_2_COMMAND_SHIFT)                /* 0xFFFFFFFF */
/* A2B_DAT_2 */
#define MBOX_A2B_DAT_2_OFFSET                              (0x1CU)
#define MBOX_A2B_DAT_2_DATA_SHIFT                          (0U)
#define MBOX_A2B_DAT_2_DATA_MASK                           (0xFFFFFFFFU << MBOX_A2B_DAT_2_DATA_SHIFT)                   /* 0xFFFFFFFF */
/* A2B_CMD_3 */
#define MBOX_A2B_CMD_3_OFFSET                              (0x20U)
#define MBOX_A2B_CMD_3_COMMAND_SHIFT                       (0U)
#define MBOX_A2B_CMD_3_COMMAND_MASK                        (0xFFFFFFFFU << MBOX_A2B_CMD_3_COMMAND_SHIFT)                /* 0xFFFFFFFF */
/* A2B_DAT_3 */
#define MBOX_A2B_DAT_3_OFFSET                              (0x24U)
#define MBOX_A2B_DAT_3_DATA_SHIFT                          (0U)
#define MBOX_A2B_DAT_3_DATA_MASK                           (0xFFFFFFFFU << MBOX_A2B_DAT_3_DATA_SHIFT)                   /* 0xFFFFFFFF */
/* B2A_INTEN */
#define MBOX_B2A_INTEN_OFFSET                              (0x28U)
#define MBOX_B2A_INTEN_INT0_SHIFT                          (0U)
#define MBOX_B2A_INTEN_INT0_MASK                           (0x1U << MBOX_B2A_INTEN_INT0_SHIFT)                          /* 0x00000001 */
#define MBOX_B2A_INTEN_INT1_SHIFT                          (1U)
#define MBOX_B2A_INTEN_INT1_MASK                           (0x1U << MBOX_B2A_INTEN_INT1_SHIFT)                          /* 0x00000002 */
#define MBOX_B2A_INTEN_INT2_SHIFT                          (2U)
#define MBOX_B2A_INTEN_INT2_MASK                           (0x1U << MBOX_B2A_INTEN_INT2_SHIFT)                          /* 0x00000004 */
#define MBOX_B2A_INTEN_INT3_SHIFT                          (3U)
#define MBOX_B2A_INTEN_INT3_MASK                           (0x1U << MBOX_B2A_INTEN_INT3_SHIFT)                          /* 0x00000008 */
/* B2A_STATUS */
#define MBOX_B2A_STATUS_OFFSET                             (0x2CU)
#define MBOX_B2A_STATUS_INT0_SHIFT                         (0U)
#define MBOX_B2A_STATUS_INT0_MASK                          (0x1U << MBOX_B2A_STATUS_INT0_SHIFT)                         /* 0x00000001 */
#define MBOX_B2A_STATUS_INT1_SHIFT                         (1U)
#define MBOX_B2A_STATUS_INT1_MASK                          (0x1U << MBOX_B2A_STATUS_INT1_SHIFT)                         /* 0x00000002 */
#define MBOX_B2A_STATUS_INT2_SHIFT                         (2U)
#define MBOX_B2A_STATUS_INT2_MASK                          (0x1U << MBOX_B2A_STATUS_INT2_SHIFT)                         /* 0x00000004 */
#define MBOX_B2A_STATUS_INT3_SHIFT                         (3U)
#define MBOX_B2A_STATUS_INT3_MASK                          (0x1U << MBOX_B2A_STATUS_INT3_SHIFT)                         /* 0x00000008 */
/* B2A_CMD_0 */
#define MBOX_B2A_CMD_0_OFFSET                              (0x30U)
#define MBOX_B2A_CMD_0_COMMAND_SHIFT                       (0U)
#define MBOX_B2A_CMD_0_COMMAND_MASK                        (0xFFFFFFFFU << MBOX_B2A_CMD_0_COMMAND_SHIFT)                /* 0xFFFFFFFF */
/* B2A_DAT_0 */
#define MBOX_B2A_DAT_0_OFFSET                              (0x34U)
#define MBOX_B2A_DAT_0_DATA_SHIFT                          (0U)
#define MBOX_B2A_DAT_0_DATA_MASK                           (0xFFFFFFFFU << MBOX_B2A_DAT_0_DATA_SHIFT)                   /* 0xFFFFFFFF */
/* B2A_CMD_1 */
#define MBOX_B2A_CMD_1_OFFSET                              (0x38U)
#define MBOX_B2A_CMD_1_COMMAND_SHIFT                       (0U)
#define MBOX_B2A_CMD_1_COMMAND_MASK                        (0xFFFFFFFFU << MBOX_B2A_CMD_1_COMMAND_SHIFT)                /* 0xFFFFFFFF */
/* B2A_DAT_1 */
#define MBOX_B2A_DAT_1_OFFSET                              (0x3CU)
#define MBOX_B2A_DAT_1_DATA_SHIFT                          (0U)
#define MBOX_B2A_DAT_1_DATA_MASK                           (0xFFFFFFFFU << MBOX_B2A_DAT_1_DATA_SHIFT)                   /* 0xFFFFFFFF */
/* B2A_CMD_2 */
#define MBOX_B2A_CMD_2_OFFSET                              (0x40U)
#define MBOX_B2A_CMD_2_COMMAND_SHIFT                       (0U)
#define MBOX_B2A_CMD_2_COMMAND_MASK                        (0xFFFFFFFFU << MBOX_B2A_CMD_2_COMMAND_SHIFT)                /* 0xFFFFFFFF */
/* B2A_DAT_2 */
#define MBOX_B2A_DAT_2_OFFSET                              (0x44U)
#define MBOX_B2A_DAT_2_DATA_SHIFT                          (0U)
#define MBOX_B2A_DAT_2_DATA_MASK                           (0xFFFFFFFFU << MBOX_B2A_DAT_2_DATA_SHIFT)                   /* 0xFFFFFFFF */
/* B2A_CMD_3 */
#define MBOX_B2A_CMD_3_OFFSET                              (0x48U)
#define MBOX_B2A_CMD_3_COMMAND_SHIFT                       (0U)
#define MBOX_B2A_CMD_3_COMMAND_MASK                        (0xFFFFFFFFU << MBOX_B2A_CMD_3_COMMAND_SHIFT)                /* 0xFFFFFFFF */
/* B2A_DAT_3 */
#define MBOX_B2A_DAT_3_OFFSET                              (0x4CU)
#define MBOX_B2A_DAT_3_DATA_SHIFT                          (0U)
#define MBOX_B2A_DAT_3_DATA_MASK                           (0xFFFFFFFFU << MBOX_B2A_DAT_3_DATA_SHIFT)                   /* 0xFFFFFFFF */
/* ATOMIC_LOCK_00 */
#define MBOX_ATOMIC_LOCK_00_OFFSET                         (0x100U)
#define MBOX_ATOMIC_LOCK_00_ATOMIC_LOCK_00_SHIFT           (0U)
#define MBOX_ATOMIC_LOCK_00_ATOMIC_LOCK_00_MASK            (0x1U << MBOX_ATOMIC_LOCK_00_ATOMIC_LOCK_00_SHIFT)           /* 0x00000001 */
/* ATOMIC_LOCK_01 */
#define MBOX_ATOMIC_LOCK_01_OFFSET                         (0x104U)
#define MBOX_ATOMIC_LOCK_01_ATOMIC_LOCK_01_SHIFT           (0U)
#define MBOX_ATOMIC_LOCK_01_ATOMIC_LOCK_01_MASK            (0x1U << MBOX_ATOMIC_LOCK_01_ATOMIC_LOCK_01_SHIFT)           /* 0x00000001 */
/* ATOMIC_LOCK_02 */
#define MBOX_ATOMIC_LOCK_02_OFFSET                         (0x108U)
#define MBOX_ATOMIC_LOCK_02_ATOMIC_LOCK_02_SHIFT           (0U)
#define MBOX_ATOMIC_LOCK_02_ATOMIC_LOCK_02_MASK            (0x1U << MBOX_ATOMIC_LOCK_02_ATOMIC_LOCK_02_SHIFT)           /* 0x00000001 */
/* ATOMIC_LOCK_03 */
#define MBOX_ATOMIC_LOCK_03_OFFSET                         (0x10CU)
#define MBOX_ATOMIC_LOCK_03_ATOMIC_LOCK_03_SHIFT           (0U)
#define MBOX_ATOMIC_LOCK_03_ATOMIC_LOCK_03_MASK            (0x1U << MBOX_ATOMIC_LOCK_03_ATOMIC_LOCK_03_SHIFT)           /* 0x00000001 */
/* ATOMIC_LOCK_04 */
#define MBOX_ATOMIC_LOCK_04_OFFSET                         (0x110U)
#define MBOX_ATOMIC_LOCK_04_ATOMIC_LOCK_04_SHIFT           (0U)
#define MBOX_ATOMIC_LOCK_04_ATOMIC_LOCK_04_MASK            (0x1U << MBOX_ATOMIC_LOCK_04_ATOMIC_LOCK_04_SHIFT)           /* 0x00000001 */
/* ATOMIC_LOCK_05 */
#define MBOX_ATOMIC_LOCK_05_OFFSET                         (0x114U)
#define MBOX_ATOMIC_LOCK_05_ATOMIC_LOCK_05_SHIFT           (0U)
#define MBOX_ATOMIC_LOCK_05_ATOMIC_LOCK_05_MASK            (0x1U << MBOX_ATOMIC_LOCK_05_ATOMIC_LOCK_05_SHIFT)           /* 0x00000001 */
/* ATOMIC_LOCK_06 */
#define MBOX_ATOMIC_LOCK_06_OFFSET                         (0x118U)
#define MBOX_ATOMIC_LOCK_06_ATOMIC_LOCK_06_SHIFT           (0U)
#define MBOX_ATOMIC_LOCK_06_ATOMIC_LOCK_06_MASK            (0x1U << MBOX_ATOMIC_LOCK_06_ATOMIC_LOCK_06_SHIFT)           /* 0x00000001 */
/* ATOMIC_LOCK_07 */
#define MBOX_ATOMIC_LOCK_07_OFFSET                         (0x11CU)
#define MBOX_ATOMIC_LOCK_07_ATOMIC_LOCK_07_SHIFT           (0U)
#define MBOX_ATOMIC_LOCK_07_ATOMIC_LOCK_07_MASK            (0x1U << MBOX_ATOMIC_LOCK_07_ATOMIC_LOCK_07_SHIFT)           /* 0x00000001 */
/* ATOMIC_LOCK_08 */
#define MBOX_ATOMIC_LOCK_08_OFFSET                         (0x120U)
#define MBOX_ATOMIC_LOCK_08_ATOMIC_LOCK_08_SHIFT           (0U)
#define MBOX_ATOMIC_LOCK_08_ATOMIC_LOCK_08_MASK            (0x1U << MBOX_ATOMIC_LOCK_08_ATOMIC_LOCK_08_SHIFT)           /* 0x00000001 */
/* ATOMIC_LOCK_09 */
#define MBOX_ATOMIC_LOCK_09_OFFSET                         (0x124U)
#define MBOX_ATOMIC_LOCK_09_ATOMIC_LOCK_09_SHIFT           (0U)
#define MBOX_ATOMIC_LOCK_09_ATOMIC_LOCK_09_MASK            (0x1U << MBOX_ATOMIC_LOCK_09_ATOMIC_LOCK_09_SHIFT)           /* 0x00000001 */
/* ATOMIC_LOCK_10 */
#define MBOX_ATOMIC_LOCK_10_OFFSET                         (0x128U)
#define MBOX_ATOMIC_LOCK_10_ATOMIC_LOCK_10_SHIFT           (0U)
#define MBOX_ATOMIC_LOCK_10_ATOMIC_LOCK_10_MASK            (0x1U << MBOX_ATOMIC_LOCK_10_ATOMIC_LOCK_10_SHIFT)           /* 0x00000001 */
/* ATOMIC_LOCK_11 */
#define MBOX_ATOMIC_LOCK_11_OFFSET                         (0x12CU)
#define MBOX_ATOMIC_LOCK_11_ATOMIC_LOCK_11_SHIFT           (0U)
#define MBOX_ATOMIC_LOCK_11_ATOMIC_LOCK_11_MASK            (0x1U << MBOX_ATOMIC_LOCK_11_ATOMIC_LOCK_11_SHIFT)           /* 0x00000001 */
/* ATOMIC_LOCK_12 */
#define MBOX_ATOMIC_LOCK_12_OFFSET                         (0x130U)
#define MBOX_ATOMIC_LOCK_12_ATOMIC_LOCK_12_SHIFT           (0U)
#define MBOX_ATOMIC_LOCK_12_ATOMIC_LOCK_12_MASK            (0x1U << MBOX_ATOMIC_LOCK_12_ATOMIC_LOCK_12_SHIFT)           /* 0x00000001 */
/* ATOMIC_LOCK_13 */
#define MBOX_ATOMIC_LOCK_13_OFFSET                         (0x134U)
#define MBOX_ATOMIC_LOCK_13_ATOMIC_LOCK_13_SHIFT           (0U)
#define MBOX_ATOMIC_LOCK_13_ATOMIC_LOCK_13_MASK            (0x1U << MBOX_ATOMIC_LOCK_13_ATOMIC_LOCK_13_SHIFT)           /* 0x00000001 */
/* ATOMIC_LOCK_14 */
#define MBOX_ATOMIC_LOCK_14_OFFSET                         (0x138U)
#define MBOX_ATOMIC_LOCK_14_ATOMIC_LOCK_14_SHIFT           (0U)
#define MBOX_ATOMIC_LOCK_14_ATOMIC_LOCK_14_MASK            (0x1U << MBOX_ATOMIC_LOCK_14_ATOMIC_LOCK_14_SHIFT)           /* 0x00000001 */
/* ATOMIC_LOCK_15 */
#define MBOX_ATOMIC_LOCK_15_OFFSET                         (0x13CU)
#define MBOX_ATOMIC_LOCK_15_ATOMIC_LOCK_15_SHIFT           (0U)
#define MBOX_ATOMIC_LOCK_15_ATOMIC_LOCK_15_MASK            (0x1U << MBOX_ATOMIC_LOCK_15_ATOMIC_LOCK_15_SHIFT)           /* 0x00000001 */
/* ATOMIC_LOCK_16 */
#define MBOX_ATOMIC_LOCK_16_OFFSET                         (0x140U)
#define MBOX_ATOMIC_LOCK_16_ATOMIC_LOCK_16_SHIFT           (0U)
#define MBOX_ATOMIC_LOCK_16_ATOMIC_LOCK_16_MASK            (0x1U << MBOX_ATOMIC_LOCK_16_ATOMIC_LOCK_16_SHIFT)           /* 0x00000001 */
/* ATOMIC_LOCK_17 */
#define MBOX_ATOMIC_LOCK_17_OFFSET                         (0x144U)
#define MBOX_ATOMIC_LOCK_17_ATOMIC_LOCK_17_SHIFT           (0U)
#define MBOX_ATOMIC_LOCK_17_ATOMIC_LOCK_17_MASK            (0x1U << MBOX_ATOMIC_LOCK_17_ATOMIC_LOCK_17_SHIFT)           /* 0x00000001 */
/* ATOMIC_LOCK_18 */
#define MBOX_ATOMIC_LOCK_18_OFFSET                         (0x148U)
#define MBOX_ATOMIC_LOCK_18_ATOMIC_LOCK_18_SHIFT           (0U)
#define MBOX_ATOMIC_LOCK_18_ATOMIC_LOCK_18_MASK            (0x1U << MBOX_ATOMIC_LOCK_18_ATOMIC_LOCK_18_SHIFT)           /* 0x00000001 */
/* ATOMIC_LOCK_19 */
#define MBOX_ATOMIC_LOCK_19_OFFSET                         (0x14CU)
#define MBOX_ATOMIC_LOCK_19_ATOMIC_LOCK_19_SHIFT           (0U)
#define MBOX_ATOMIC_LOCK_19_ATOMIC_LOCK_19_MASK            (0x1U << MBOX_ATOMIC_LOCK_19_ATOMIC_LOCK_19_SHIFT)           /* 0x00000001 */
/* ATOMIC_LOCK_20 */
#define MBOX_ATOMIC_LOCK_20_OFFSET                         (0x150U)
#define MBOX_ATOMIC_LOCK_20_ATOMIC_LOCK_20_SHIFT           (0U)
#define MBOX_ATOMIC_LOCK_20_ATOMIC_LOCK_20_MASK            (0x1U << MBOX_ATOMIC_LOCK_20_ATOMIC_LOCK_20_SHIFT)           /* 0x00000001 */
/* ATOMIC_LOCK_21 */
#define MBOX_ATOMIC_LOCK_21_OFFSET                         (0x154U)
#define MBOX_ATOMIC_LOCK_21_ATOMIC_LOCK_21_SHIFT           (0U)
#define MBOX_ATOMIC_LOCK_21_ATOMIC_LOCK_21_MASK            (0x1U << MBOX_ATOMIC_LOCK_21_ATOMIC_LOCK_21_SHIFT)           /* 0x00000001 */
/* ATOMIC_LOCK_22 */
#define MBOX_ATOMIC_LOCK_22_OFFSET                         (0x158U)
#define MBOX_ATOMIC_LOCK_22_ATOMIC_LOCK_22_SHIFT           (0U)
#define MBOX_ATOMIC_LOCK_22_ATOMIC_LOCK_22_MASK            (0x1U << MBOX_ATOMIC_LOCK_22_ATOMIC_LOCK_22_SHIFT)           /* 0x00000001 */
/* ATOMIC_LOCK_23 */
#define MBOX_ATOMIC_LOCK_23_OFFSET                         (0x15CU)
#define MBOX_ATOMIC_LOCK_23_ATOMIC_LOCK_23_SHIFT           (0U)
#define MBOX_ATOMIC_LOCK_23_ATOMIC_LOCK_23_MASK            (0x1U << MBOX_ATOMIC_LOCK_23_ATOMIC_LOCK_23_SHIFT)           /* 0x00000001 */
/* ATOMIC_LOCK_24 */
#define MBOX_ATOMIC_LOCK_24_OFFSET                         (0x160U)
#define MBOX_ATOMIC_LOCK_24_ATOMIC_LOCK_24_SHIFT           (0U)
#define MBOX_ATOMIC_LOCK_24_ATOMIC_LOCK_24_MASK            (0x1U << MBOX_ATOMIC_LOCK_24_ATOMIC_LOCK_24_SHIFT)           /* 0x00000001 */
/* ATOMIC_LOCK_25 */
#define MBOX_ATOMIC_LOCK_25_OFFSET                         (0x164U)
#define MBOX_ATOMIC_LOCK_25_ATOMIC_LOCK_25_SHIFT           (0U)
#define MBOX_ATOMIC_LOCK_25_ATOMIC_LOCK_25_MASK            (0x1U << MBOX_ATOMIC_LOCK_25_ATOMIC_LOCK_25_SHIFT)           /* 0x00000001 */
/* ATOMIC_LOCK_26 */
#define MBOX_ATOMIC_LOCK_26_OFFSET                         (0x168U)
#define MBOX_ATOMIC_LOCK_26_ATOMIC_LOCK_26_SHIFT           (0U)
#define MBOX_ATOMIC_LOCK_26_ATOMIC_LOCK_26_MASK            (0x1U << MBOX_ATOMIC_LOCK_26_ATOMIC_LOCK_26_SHIFT)           /* 0x00000001 */
/* ATOMIC_LOCK_27 */
#define MBOX_ATOMIC_LOCK_27_OFFSET                         (0x16CU)
#define MBOX_ATOMIC_LOCK_27_ATOMIC_LOCK_27_SHIFT           (0U)
#define MBOX_ATOMIC_LOCK_27_ATOMIC_LOCK_27_MASK            (0x1U << MBOX_ATOMIC_LOCK_27_ATOMIC_LOCK_27_SHIFT)           /* 0x00000001 */
/* ATOMIC_LOCK_28 */
#define MBOX_ATOMIC_LOCK_28_OFFSET                         (0x170U)
#define MBOX_ATOMIC_LOCK_28_ATOMIC_LOCK_28_SHIFT           (0U)
#define MBOX_ATOMIC_LOCK_28_ATOMIC_LOCK_28_MASK            (0x1U << MBOX_ATOMIC_LOCK_28_ATOMIC_LOCK_28_SHIFT)           /* 0x00000001 */
/* ATOMIC_LOCK_29 */
#define MBOX_ATOMIC_LOCK_29_OFFSET                         (0x174U)
#define MBOX_ATOMIC_LOCK_29_ATOMIC_LOCK_29_SHIFT           (0U)
#define MBOX_ATOMIC_LOCK_29_ATOMIC_LOCK_29_MASK            (0x1U << MBOX_ATOMIC_LOCK_29_ATOMIC_LOCK_29_SHIFT)           /* 0x00000001 */
/* ATOMIC_LOCK_30 */
#define MBOX_ATOMIC_LOCK_30_OFFSET                         (0x178U)
#define MBOX_ATOMIC_LOCK_30_ATOMIC_LOCK_30_SHIFT           (0U)
#define MBOX_ATOMIC_LOCK_30_ATOMIC_LOCK_30_MASK            (0x1U << MBOX_ATOMIC_LOCK_30_ATOMIC_LOCK_30_SHIFT)           /* 0x00000001 */
/* ATOMIC_LOCK_31 */
#define MBOX_ATOMIC_LOCK_31_OFFSET                         (0x17CU)
#define MBOX_ATOMIC_LOCK_31_ATOMIC_LOCK_31_SHIFT           (0U)
#define MBOX_ATOMIC_LOCK_31_ATOMIC_LOCK_31_MASK            (0x1U << MBOX_ATOMIC_LOCK_31_ATOMIC_LOCK_31_SHIFT)           /* 0x00000001 */
/******************************************PMU*******************************************/
/* WAKEUP_CFG0 */
#define PMU_WAKEUP_CFG0_OFFSET                             (0x0U)
#define PMU_WAKEUP_CFG0_GPIO0D_POSEDGE_EN_SHIFT            (0U)
#define PMU_WAKEUP_CFG0_GPIO0D_POSEDGE_EN_MASK             (0xFFU << PMU_WAKEUP_CFG0_GPIO0D_POSEDGE_EN_SHIFT)           /* 0x000000FF */
#define PMU_WAKEUP_CFG0_GPIO1B_POSEDGE_EN_SHIFT            (8U)
#define PMU_WAKEUP_CFG0_GPIO1B_POSEDGE_EN_MASK             (0xFFU << PMU_WAKEUP_CFG0_GPIO1B_POSEDGE_EN_SHIFT)           /* 0x0000FF00 */
/* WAKEUP_CFG1 */
#define PMU_WAKEUP_CFG1_OFFSET                             (0x4U)
#define PMU_WAKEUP_CFG1_GPIO0D_NEGEDGE_EN_SHIFT            (0U)
#define PMU_WAKEUP_CFG1_GPIO0D_NEGEDGE_EN_MASK             (0xFFU << PMU_WAKEUP_CFG1_GPIO0D_NEGEDGE_EN_SHIFT)           /* 0x000000FF */
#define PMU_WAKEUP_CFG1_GPIO1B_NEGEDGE_EN_SHIFT            (8U)
#define PMU_WAKEUP_CFG1_GPIO1B_NEGEDGE_EN_MASK             (0xFFU << PMU_WAKEUP_CFG1_GPIO1B_NEGEDGE_EN_SHIFT)           /* 0x0000FF00 */
/* WAKEUP_CFG2 */
#define PMU_WAKEUP_CFG2_OFFSET                             (0x8U)
#define PMU_WAKEUP_CFG2_GPIO0D_POSEDGE_EN_SHIFT            (0U)
#define PMU_WAKEUP_CFG2_GPIO0D_POSEDGE_EN_MASK             (0xFFU << PMU_WAKEUP_CFG2_GPIO0D_POSEDGE_EN_SHIFT)           /* 0x000000FF */
#define PMU_WAKEUP_CFG2_GPIO1B_POSEDGE_EN_SHIFT            (8U)
#define PMU_WAKEUP_CFG2_GPIO1B_POSEDGE_EN_MASK             (0xFFU << PMU_WAKEUP_CFG2_GPIO1B_POSEDGE_EN_SHIFT)           /* 0x0000FF00 */
/* WAKEUP_CFG3 */
#define PMU_WAKEUP_CFG3_OFFSET                             (0xCU)
#define PMU_WAKEUP_CFG3_GPIO0D_NEGEDGE_EN_SHIFT            (0U)
#define PMU_WAKEUP_CFG3_GPIO0D_NEGEDGE_EN_MASK             (0xFFU << PMU_WAKEUP_CFG3_GPIO0D_NEGEDGE_EN_SHIFT)           /* 0x000000FF */
#define PMU_WAKEUP_CFG3_GPIO1B_NEGEDGE_EN_SHIFT            (8U)
#define PMU_WAKEUP_CFG3_GPIO1B_NEGEDGE_EN_MASK             (0xFFU << PMU_WAKEUP_CFG3_GPIO1B_NEGEDGE_EN_SHIFT)           /* 0x0000FF00 */
/* WAKEUP_CFG6 */
#define PMU_WAKEUP_CFG6_OFFSET                             (0x18U)
#define PMU_WAKEUP_CFG6_PWRMODE_INT_WAKEUP_EN_SHIFT        (0U)
#define PMU_WAKEUP_CFG6_PWRMODE_INT_WAKEUP_EN_MASK         (0x1U << PMU_WAKEUP_CFG6_PWRMODE_INT_WAKEUP_EN_SHIFT)        /* 0x00000001 */
#define PMU_WAKEUP_CFG6_GPIO_INT_EN_SHIFT                  (1U)
#define PMU_WAKEUP_CFG6_GPIO_INT_EN_MASK                   (0x1U << PMU_WAKEUP_CFG6_GPIO_INT_EN_SHIFT)                  /* 0x00000002 */
#define PMU_WAKEUP_CFG6_TIMEOUT_EN_SHIFT                   (2U)
#define PMU_WAKEUP_CFG6_TIMEOUT_EN_MASK                    (0x1U << PMU_WAKEUP_CFG6_TIMEOUT_EN_SHIFT)                   /* 0x00000004 */
#define PMU_WAKEUP_CFG6_TIMER_EN_SHIFT                     (3U)
#define PMU_WAKEUP_CFG6_TIMER_EN_MASK                      (0x1U << PMU_WAKEUP_CFG6_TIMER_EN_SHIFT)                     /* 0x00000008 */
#define PMU_WAKEUP_CFG6_VAD_EN_SHIFT                       (4U)
#define PMU_WAKEUP_CFG6_VAD_EN_MASK                        (0x1U << PMU_WAKEUP_CFG6_VAD_EN_SHIFT)                       /* 0x00000010 */
#define PMU_WAKEUP_CFG6_PWRMODE_WAKEUP_SFT_INT_SHIFT       (5U)
#define PMU_WAKEUP_CFG6_PWRMODE_WAKEUP_SFT_INT_MASK        (0x1U << PMU_WAKEUP_CFG6_PWRMODE_WAKEUP_SFT_INT_SHIFT)       /* 0x00000020 */
/* PWRDN_CON */
#define PMU_PWRDN_CON_OFFSET                               (0x30U)
#define PMU_PWRDN_CON_PD_DSP_PWRDWN_EN_SHIFT               (0U)
#define PMU_PWRDN_CON_PD_DSP_PWRDWN_EN_MASK                (0x1U << PMU_PWRDN_CON_PD_DSP_PWRDWN_EN_SHIFT)               /* 0x00000001 */
#define PMU_PWRDN_CON_PD_LOGIC_PWRDWN_EN_SHIFT             (1U)
#define PMU_PWRDN_CON_PD_LOGIC_PWRDWN_EN_MASK              (0x1U << PMU_PWRDN_CON_PD_LOGIC_PWRDWN_EN_SHIFT)             /* 0x00000002 */
#define PMU_PWRDN_CON_PD_SHRM_PWRDWN_EN_SHIFT              (2U)
#define PMU_PWRDN_CON_PD_SHRM_PWRDWN_EN_MASK               (0x1U << PMU_PWRDN_CON_PD_SHRM_PWRDWN_EN_SHIFT)              /* 0x00000004 */
#define PMU_PWRDN_CON_PD_AUDIO_PWRDWN_EN_SHIFT             (3U)
#define PMU_PWRDN_CON_PD_AUDIO_PWRDWN_EN_MASK              (0x1U << PMU_PWRDN_CON_PD_AUDIO_PWRDWN_EN_SHIFT)             /* 0x00000008 */
/* PWRDN_ST */
#define PMU_PWRDN_ST_OFFSET                                (0x34U)
#define PMU_PWRDN_ST                                       (0x0U)
#define PMU_PWRDN_ST_PD_DSP_PWR_STAT_SHIFT                 (0U)
#define PMU_PWRDN_ST_PD_DSP_PWR_STAT_MASK                  (0x1U << PMU_PWRDN_ST_PD_DSP_PWR_STAT_SHIFT)                 /* 0x00000001 */
#define PMU_PWRDN_ST_PD_LOGIC_PWR_STAT_SHIFT               (1U)
#define PMU_PWRDN_ST_PD_LOGIC_PWR_STAT_MASK                (0x1U << PMU_PWRDN_ST_PD_LOGIC_PWR_STAT_SHIFT)               /* 0x00000002 */
#define PMU_PWRDN_ST_PD_SHRM_PWR_STAT_SHIFT                (2U)
#define PMU_PWRDN_ST_PD_SHRM_PWR_STAT_MASK                 (0x1U << PMU_PWRDN_ST_PD_SHRM_PWR_STAT_SHIFT)                /* 0x00000004 */
#define PMU_PWRDN_ST_PD_AUDIO_PWR_STAT_SHIFT               (3U)
#define PMU_PWRDN_ST_PD_AUDIO_PWR_STAT_MASK                (0x1U << PMU_PWRDN_ST_PD_AUDIO_PWR_STAT_SHIFT)               /* 0x00000008 */
#define PMU_PWRDN_ST_SHAREMEM_PWR_STAT_SHIFT               (4U)
#define PMU_PWRDN_ST_SHAREMEM_PWR_STAT_MASK                (0xFU << PMU_PWRDN_ST_SHAREMEM_PWR_STAT_SHIFT)               /* 0x000000F0 */
/* PLL_CON */
#define PMU_PLL_CON_OFFSET                                 (0x38U)
#define PMU_PLL_CON_PLL_PD_CFG_SHIFT                       (0U)
#define PMU_PLL_CON_PLL_PD_CFG_MASK                        (0x7U << PMU_PLL_CON_PLL_PD_CFG_SHIFT)                       /* 0x00000007 */
#define PMU_PLL_CON_SFT_PLL_PD_SHIFT                       (3U)
#define PMU_PLL_CON_SFT_PLL_PD_MASK                        (0x7U << PMU_PLL_CON_SFT_PLL_PD_SHIFT)                       /* 0x00000038 */
/* PWRMODE_CON */
#define PMU_PWRMODE_CON_OFFSET                             (0x3CU)
#define PMU_PWRMODE_CON_POWER_MODE_EN_SHIFT                (0U)
#define PMU_PWRMODE_CON_POWER_MODE_EN_MASK                 (0x1U << PMU_PWRMODE_CON_POWER_MODE_EN_SHIFT)                /* 0x00000001 */
#define PMU_PWRMODE_CON_OSC_DISABLE_SHIFT                  (1U)
#define PMU_PWRMODE_CON_OSC_DISABLE_MASK                   (0x1U << PMU_PWRMODE_CON_OSC_DISABLE_SHIFT)                  /* 0x00000002 */
#define PMU_PWRMODE_CON_PMU_USE_LF_SHIFT                   (2U)
#define PMU_PWRMODE_CON_PMU_USE_LF_MASK                    (0x1U << PMU_PWRMODE_CON_PMU_USE_LF_SHIFT)                   /* 0x00000004 */
#define PMU_PWRMODE_CON_PLL_PD_EN_SHIFT                    (3U)
#define PMU_PWRMODE_CON_PLL_PD_EN_MASK                     (0x1U << PMU_PWRMODE_CON_PLL_PD_EN_SHIFT)                    /* 0x00000008 */
#define PMU_PWRMODE_CON_LOGIC_PD_EN_SHIFT                  (4U)
#define PMU_PWRMODE_CON_LOGIC_PD_EN_MASK                   (0x1U << PMU_PWRMODE_CON_LOGIC_PD_EN_SHIFT)                  /* 0x00000010 */
#define PMU_PWRMODE_CON_PWRMODE_LDO_ADJ_EN_SHIFT           (5U)
#define PMU_PWRMODE_CON_PWRMODE_LDO_ADJ_EN_MASK            (0x1U << PMU_PWRMODE_CON_PWRMODE_LDO_ADJ_EN_SHIFT)           /* 0x00000020 */
#define PMU_PWRMODE_CON_BYPASS_PLL_LOCK_SHIFT              (6U)
#define PMU_PWRMODE_CON_BYPASS_PLL_LOCK_MASK               (0x1U << PMU_PWRMODE_CON_BYPASS_PLL_LOCK_SHIFT)              /* 0x00000040 */
#define PMU_PWRMODE_CON_BYPASS_HF_EN_SHIFT                 (7U)
#define PMU_PWRMODE_CON_BYPASS_HF_EN_MASK                  (0x1U << PMU_PWRMODE_CON_BYPASS_HF_EN_SHIFT)                 /* 0x00000080 */
#define PMU_PWRMODE_CON_GLOBAL_INT_DISABLE_CFG_SHIFT       (8U)
#define PMU_PWRMODE_CON_GLOBAL_INT_DISABLE_CFG_MASK        (0x1U << PMU_PWRMODE_CON_GLOBAL_INT_DISABLE_CFG_SHIFT)       /* 0x00000100 */
#define PMU_PWRMODE_CON_SHRM_PD_EN_SHIFT                   (9U)
#define PMU_PWRMODE_CON_SHRM_PD_EN_MASK                    (0x1U << PMU_PWRMODE_CON_SHRM_PD_EN_SHIFT)                   /* 0x00000200 */
#define PMU_PWRMODE_CON_SHRM_MEM_RETPD_EN_SHIFT            (10U)
#define PMU_PWRMODE_CON_SHRM_MEM_RETPD_EN_MASK             (0x1U << PMU_PWRMODE_CON_SHRM_MEM_RETPD_EN_SHIFT)            /* 0x00000400 */
#define PMU_PWRMODE_CON_PLLPD_WAIT_EN_SHIFT                (11U)
#define PMU_PWRMODE_CON_PLLPD_WAIT_EN_MASK                 (0x1U << PMU_PWRMODE_CON_PLLPD_WAIT_EN_SHIFT)                /* 0x00000800 */
/* SFT_CON */
#define PMU_SFT_CON_OFFSET                                 (0x40U)
#define PMU_SFT_CON_OSC_DISABLE_CFG_SHIFT                  (0U)
#define PMU_SFT_CON_OSC_DISABLE_CFG_MASK                   (0x1U << PMU_SFT_CON_OSC_DISABLE_CFG_SHIFT)                  /* 0x00000001 */
#define PMU_SFT_CON_PMU_LF_ENA_CFG_SHIFT                   (1U)
#define PMU_SFT_CON_PMU_LF_ENA_CFG_MASK                    (0x1U << PMU_SFT_CON_PMU_LF_ENA_CFG_SHIFT)                   /* 0x00000002 */
#define PMU_SFT_CON_PMU_LF_MODE_CFG_SHIFT                  (2U)
#define PMU_SFT_CON_PMU_LF_MODE_CFG_MASK                   (0x1U << PMU_SFT_CON_PMU_LF_MODE_CFG_SHIFT)                  /* 0x00000004 */
#define PMU_SFT_CON_PWRMODE_EN_SFT_SHIFT                   (3U)
#define PMU_SFT_CON_PWRMODE_EN_SFT_MASK                    (0x1U << PMU_SFT_CON_PWRMODE_EN_SFT_SHIFT)                   /* 0x00000008 */
/* LDO_CON0 */
#define PMU_LDO_CON0_OFFSET                                (0x50U)
#define PMU_LDO_CON0_LDO_MIPI_EN_SHIFT                     (0U)
#define PMU_LDO_CON0_LDO_MIPI_EN_MASK                      (0x1U << PMU_LDO_CON0_LDO_MIPI_EN_SHIFT)                     /* 0x00000001 */
#define PMU_LDO_CON0_LDO_AUDIO_EN_SHIFT                    (1U)
#define PMU_LDO_CON0_LDO_AUDIO_EN_MASK                     (0x1U << PMU_LDO_CON0_LDO_AUDIO_EN_SHIFT)                    /* 0x00000002 */
#define PMU_LDO_CON0_LDO_AUDIO_SFT_SHIFT                   (2U)
#define PMU_LDO_CON0_LDO_AUDIO_SFT_MASK                    (0x3U << PMU_LDO_CON0_LDO_AUDIO_SFT_SHIFT)                   /* 0x0000000C */
#define PMU_LDO_CON0_LDO_BGADJ_SHIFT                       (4U)
#define PMU_LDO_CON0_LDO_BGADJ_MASK                        (0x7U << PMU_LDO_CON0_LDO_BGADJ_SHIFT)                       /* 0x00000070 */
#define PMU_LDO_CON0_LDO_REFADJ_SHIFT                      (8U)
#define PMU_LDO_CON0_LDO_REFADJ_MASK                       (0xFU << PMU_LDO_CON0_LDO_REFADJ_SHIFT)                      /* 0x00000F00 */
/* LDO_CON1 */
#define PMU_LDO_CON1_OFFSET                                (0x54U)
#define PMU_LDO_CON1_MCU_LDOCORE_SFT_SHIFT                 (0U)
#define PMU_LDO_CON1_MCU_LDOCORE_SFT_MASK                  (0x7U << PMU_LDO_CON1_MCU_LDOCORE_SFT_SHIFT)                 /* 0x00000007 */
#define PMU_LDO_CON1_PWRMODE_LDOCORE_ADJ_SHIFT             (4U)
#define PMU_LDO_CON1_PWRMODE_LDOCORE_ADJ_MASK              (0x7U << PMU_LDO_CON1_PWRMODE_LDOCORE_ADJ_SHIFT)             /* 0x00000070 */
#define PMU_LDO_CON1_MCU_LDOMIPI_SFT_SHIFT                 (8U)
#define PMU_LDO_CON1_MCU_LDOMIPI_SFT_MASK                  (0x7U << PMU_LDO_CON1_MCU_LDOMIPI_SFT_SHIFT)                 /* 0x00000700 */
#define PMU_LDO_CON1_PWRMODE_LDOMIPI_ADJ_SHIFT             (12U)
#define PMU_LDO_CON1_PWRMODE_LDOMIPI_ADJ_MASK              (0x7U << PMU_LDO_CON1_PWRMODE_LDOMIPI_ADJ_SHIFT)             /* 0x00007000 */
/* LDO_CON2 */
#define PMU_LDO_CON2_OFFSET                                (0x58U)
#define PMU_LDO_CON2_DSP_LDOCORE_SFT_SHIFT                 (0U)
#define PMU_LDO_CON2_DSP_LDOCORE_SFT_MASK                  (0x7U << PMU_LDO_CON2_DSP_LDOCORE_SFT_SHIFT)                 /* 0x00000007 */
#define PMU_LDO_CON2_DSPAPM_LDOCORE_ADJ_SHIFT              (4U)
#define PMU_LDO_CON2_DSPAPM_LDOCORE_ADJ_MASK               (0x7U << PMU_LDO_CON2_DSPAPM_LDOCORE_ADJ_SHIFT)              /* 0x00000070 */
#define PMU_LDO_CON2_DSP_LDOMIPI_SFT_SHIFT                 (8U)
#define PMU_LDO_CON2_DSP_LDOMIPI_SFT_MASK                  (0x7U << PMU_LDO_CON2_DSP_LDOMIPI_SFT_SHIFT)                 /* 0x00000700 */
#define PMU_LDO_CON2_DSPAPM_LDOMIPI_ADJ_SHIFT              (12U)
#define PMU_LDO_CON2_DSPAPM_LDOMIPI_ADJ_MASK               (0x7U << PMU_LDO_CON2_DSPAPM_LDOMIPI_ADJ_SHIFT)              /* 0x00007000 */
/* LDO_STAT */
#define PMU_LDO_STAT_OFFSET                                (0x5CU)
#define PMU_LDO_STAT                                       (0x0U)
#define PMU_LDO_STAT_LDO_CORE_ADJ_SHIFT                    (0U)
#define PMU_LDO_STAT_LDO_CORE_ADJ_MASK                     (0x7U << PMU_LDO_STAT_LDO_CORE_ADJ_SHIFT)                    /* 0x00000007 */
#define PMU_LDO_STAT_LDO_MIPI_ADJ_SHIFT                    (4U)
#define PMU_LDO_STAT_LDO_MIPI_ADJ_MASK                     (0x7U << PMU_LDO_STAT_LDO_MIPI_ADJ_SHIFT)                    /* 0x00000070 */
/* INT_CON */
#define PMU_INT_CON_OFFSET                                 (0x60U)
#define PMU_INT_CON_PMU_INT_EN_SHIFT                       (0U)
#define PMU_INT_CON_PMU_INT_EN_MASK                        (0x1U << PMU_INT_CON_PMU_INT_EN_SHIFT)                       /* 0x00000001 */
#define PMU_INT_CON_PWRMODE_WAKEUP_INT_EN_SHIFT            (1U)
#define PMU_INT_CON_PWRMODE_WAKEUP_INT_EN_MASK             (0x1U << PMU_INT_CON_PWRMODE_WAKEUP_INT_EN_SHIFT)            /* 0x00000002 */
#define PMU_INT_CON_DSP_WAKEUP_INT_EN_SHIFT                (2U)
#define PMU_INT_CON_DSP_WAKEUP_INT_EN_MASK                 (0x1U << PMU_INT_CON_DSP_WAKEUP_INT_EN_SHIFT)                /* 0x00000004 */
/* INT_ST */
#define PMU_INT_ST_OFFSET                                  (0x64U)
#define PMU_INT_ST_PWRMODE_WAKEUP_STATUS_SHIFT             (0U)
#define PMU_INT_ST_PWRMODE_WAKEUP_STATUS_MASK              (0x1U << PMU_INT_ST_PWRMODE_WAKEUP_STATUS_SHIFT)             /* 0x00000001 */
#define PMU_INT_ST_DSP_WAKEUP_STATUS_SHIFT                 (1U)
#define PMU_INT_ST_DSP_WAKEUP_STATUS_MASK                  (0x1U << PMU_INT_ST_DSP_WAKEUP_STATUS_SHIFT)                 /* 0x00000002 */
#define PMU_INT_ST_PWRMODE_WAKEUP_GPIO_POS_STATUS_SHIFT    (2U)
#define PMU_INT_ST_PWRMODE_WAKEUP_GPIO_POS_STATUS_MASK     (0x1U << PMU_INT_ST_PWRMODE_WAKEUP_GPIO_POS_STATUS_SHIFT)    /* 0x00000004 */
#define PMU_INT_ST_PWRMODE_WAKEUP_GPIO_NEG_STATUS_SHIFT    (3U)
#define PMU_INT_ST_PWRMODE_WAKEUP_GPIO_NEG_STATUS_MASK     (0x1U << PMU_INT_ST_PWRMODE_WAKEUP_GPIO_NEG_STATUS_SHIFT)    /* 0x00000008 */
#define PMU_INT_ST_DSP_WAKEUP_GPIO_POS_STATUS_SHIFT        (4U)
#define PMU_INT_ST_DSP_WAKEUP_GPIO_POS_STATUS_MASK         (0x1U << PMU_INT_ST_DSP_WAKEUP_GPIO_POS_STATUS_SHIFT)        /* 0x00000010 */
#define PMU_INT_ST_DSP_WAKEUP_GPIO_NEG_STATUS_SHIFT        (5U)
#define PMU_INT_ST_DSP_WAKEUP_GPIO_NEG_STATUS_MASK         (0x1U << PMU_INT_ST_DSP_WAKEUP_GPIO_NEG_STATUS_SHIFT)        /* 0x00000020 */
/* PWRMODE_GPIO_POS_INT_CON */
#define PMU_PWRMODE_GPIO_POS_INT_CON_OFFSET                (0x68U)
#define PMU_PWRMODE_GPIO_POS_INT_CON_PWRMODE_GPIO0D_POS_INT_EN_SHIFT (0U)
#define PMU_PWRMODE_GPIO_POS_INT_CON_PWRMODE_GPIO0D_POS_INT_EN_MASK (0xFFU << PMU_PWRMODE_GPIO_POS_INT_CON_PWRMODE_GPIO0D_POS_INT_EN_SHIFT) /* 0x000000FF */
#define PMU_PWRMODE_GPIO_POS_INT_CON_PWRMODE_GPIO1B_POS_INT_EN_SHIFT (8U)
#define PMU_PWRMODE_GPIO_POS_INT_CON_PWRMODE_GPIO1B_POS_INT_EN_MASK (0xFFU << PMU_PWRMODE_GPIO_POS_INT_CON_PWRMODE_GPIO1B_POS_INT_EN_SHIFT) /* 0x0000FF00 */
/* PWRMODE_GPIO_NEG_INT_CON */
#define PMU_PWRMODE_GPIO_NEG_INT_CON_OFFSET                (0x6CU)
#define PMU_PWRMODE_GPIO_NEG_INT_CON_PWRMODE_GPIO0D_NEG_INT_EN_SHIFT (0U)
#define PMU_PWRMODE_GPIO_NEG_INT_CON_PWRMODE_GPIO0D_NEG_INT_EN_MASK (0xFFU << PMU_PWRMODE_GPIO_NEG_INT_CON_PWRMODE_GPIO0D_NEG_INT_EN_SHIFT) /* 0x000000FF */
#define PMU_PWRMODE_GPIO_NEG_INT_CON_PWRMODE_GPIO1B_NEG_INT_EN_SHIFT (8U)
#define PMU_PWRMODE_GPIO_NEG_INT_CON_PWRMODE_GPIO1B_NEG_INT_EN_MASK (0xFFU << PMU_PWRMODE_GPIO_NEG_INT_CON_PWRMODE_GPIO1B_NEG_INT_EN_SHIFT) /* 0x0000FF00 */
/* DSP_GPIO_POS_INT_CON */
#define PMU_DSP_GPIO_POS_INT_CON_OFFSET                    (0x70U)
#define PMU_DSP_GPIO_POS_INT_CON_DSP_GPIO0D_POS_INT_EN_SHIFT (0U)
#define PMU_DSP_GPIO_POS_INT_CON_DSP_GPIO0D_POS_INT_EN_MASK (0xFFU << PMU_DSP_GPIO_POS_INT_CON_DSP_GPIO0D_POS_INT_EN_SHIFT) /* 0x000000FF */
#define PMU_DSP_GPIO_POS_INT_CON_DSP_GPIO1B_POS_INT_EN_SHIFT (8U)
#define PMU_DSP_GPIO_POS_INT_CON_DSP_GPIO1B_POS_INT_EN_MASK (0xFFU << PMU_DSP_GPIO_POS_INT_CON_DSP_GPIO1B_POS_INT_EN_SHIFT) /* 0x0000FF00 */
/* DSP_GPIO_NEG_INT_CON */
#define PMU_DSP_GPIO_NEG_INT_CON_OFFSET                    (0x74U)
#define PMU_DSP_GPIO_NEG_INT_CON_DSP_GPIO0D_NEG_INT_EN_SHIFT (0U)
#define PMU_DSP_GPIO_NEG_INT_CON_DSP_GPIO0D_NEG_INT_EN_MASK (0xFFU << PMU_DSP_GPIO_NEG_INT_CON_DSP_GPIO0D_NEG_INT_EN_SHIFT) /* 0x000000FF */
#define PMU_DSP_GPIO_NEG_INT_CON_DSP_GPIO1B_NEG_INT_EN_SHIFT (8U)
#define PMU_DSP_GPIO_NEG_INT_CON_DSP_GPIO1B_NEG_INT_EN_MASK (0xFFU << PMU_DSP_GPIO_NEG_INT_CON_DSP_GPIO1B_NEG_INT_EN_SHIFT) /* 0x0000FF00 */
/* PWRMODE_GPIO_POS_INT_ST */
#define PMU_PWRMODE_GPIO_POS_INT_ST_OFFSET                 (0x78U)
#define PMU_PWRMODE_GPIO_POS_INT_ST_PWRMODE_GPIO0D_POS_INT_STATUS_SHIFT (0U)
#define PMU_PWRMODE_GPIO_POS_INT_ST_PWRMODE_GPIO0D_POS_INT_STATUS_MASK (0xFFU << PMU_PWRMODE_GPIO_POS_INT_ST_PWRMODE_GPIO0D_POS_INT_STATUS_SHIFT) /* 0x000000FF */
#define PMU_PWRMODE_GPIO_POS_INT_ST_PWRMODE_GPIO1B_POS_INT_STATUS_SHIFT (8U)
#define PMU_PWRMODE_GPIO_POS_INT_ST_PWRMODE_GPIO1B_POS_INT_STATUS_MASK (0xFFU << PMU_PWRMODE_GPIO_POS_INT_ST_PWRMODE_GPIO1B_POS_INT_STATUS_SHIFT) /* 0x0000FF00 */
/* PWRMODE_GPIO_NEG_INT_ST */
#define PMU_PWRMODE_GPIO_NEG_INT_ST_OFFSET                 (0x7CU)
#define PMU_PWRMODE_GPIO_NEG_INT_ST_PWRMODE_GPIO0D_NEG_INT_STATUS_SHIFT (0U)
#define PMU_PWRMODE_GPIO_NEG_INT_ST_PWRMODE_GPIO0D_NEG_INT_STATUS_MASK (0xFFU << PMU_PWRMODE_GPIO_NEG_INT_ST_PWRMODE_GPIO0D_NEG_INT_STATUS_SHIFT) /* 0x000000FF */
#define PMU_PWRMODE_GPIO_NEG_INT_ST_PWRMODE_GPIO1B_NEG_INT_STATUS_SHIFT (8U)
#define PMU_PWRMODE_GPIO_NEG_INT_ST_PWRMODE_GPIO1B_NEG_INT_STATUS_MASK (0xFFU << PMU_PWRMODE_GPIO_NEG_INT_ST_PWRMODE_GPIO1B_NEG_INT_STATUS_SHIFT) /* 0x0000FF00 */
/* DSP_GPIO_POS_INT_ST */
#define PMU_DSP_GPIO_POS_INT_ST_OFFSET                     (0x80U)
#define PMU_DSP_GPIO_POS_INT_ST_DSP_GPIO0D_POS_INT_STATUS_SHIFT (0U)
#define PMU_DSP_GPIO_POS_INT_ST_DSP_GPIO0D_POS_INT_STATUS_MASK (0xFFU << PMU_DSP_GPIO_POS_INT_ST_DSP_GPIO0D_POS_INT_STATUS_SHIFT) /* 0x000000FF */
#define PMU_DSP_GPIO_POS_INT_ST_DSP_GPIO1B_POS_INT_STATUS_SHIFT (8U)
#define PMU_DSP_GPIO_POS_INT_ST_DSP_GPIO1B_POS_INT_STATUS_MASK (0xFFU << PMU_DSP_GPIO_POS_INT_ST_DSP_GPIO1B_POS_INT_STATUS_SHIFT) /* 0x0000FF00 */
/* DSP_GPIO_NEG_INT_ST */
#define PMU_DSP_GPIO_NEG_INT_ST_OFFSET                     (0x84U)
#define PMU_DSP_GPIO_NEG_INT_ST_DSP_GPIO0D_NEG_INT_STATUS_SHIFT (0U)
#define PMU_DSP_GPIO_NEG_INT_ST_DSP_GPIO0D_NEG_INT_STATUS_MASK (0xFFU << PMU_DSP_GPIO_NEG_INT_ST_DSP_GPIO0D_NEG_INT_STATUS_SHIFT) /* 0x000000FF */
#define PMU_DSP_GPIO_NEG_INT_ST_DSP_GPIO1B_NEG_INT_STATUS_SHIFT (8U)
#define PMU_DSP_GPIO_NEG_INT_ST_DSP_GPIO1B_NEG_INT_STATUS_MASK (0xFFU << PMU_DSP_GPIO_NEG_INT_ST_DSP_GPIO1B_NEG_INT_STATUS_SHIFT) /* 0x0000FF00 */
/* PWRDN_INTEN */
#define PMU_PWRDN_INTEN_OFFSET                             (0x88U)
#define PMU_PWRDN_INTEN_PD_DSP_PWR_SWITCH_INT_EN_SHIFT     (0U)
#define PMU_PWRDN_INTEN_PD_DSP_PWR_SWITCH_INT_EN_MASK      (0x1U << PMU_PWRDN_INTEN_PD_DSP_PWR_SWITCH_INT_EN_SHIFT)     /* 0x00000001 */
#define PMU_PWRDN_INTEN_PD_LOGIC_PWR_SWITCH_INT_EN_SHIFT   (1U)
#define PMU_PWRDN_INTEN_PD_LOGIC_PWR_SWITCH_INT_EN_MASK    (0x1U << PMU_PWRDN_INTEN_PD_LOGIC_PWR_SWITCH_INT_EN_SHIFT)   /* 0x00000002 */
#define PMU_PWRDN_INTEN_PD_SHRM_PWR_SWITCH_INT_EN_SHIFT    (2U)
#define PMU_PWRDN_INTEN_PD_SHRM_PWR_SWITCH_INT_EN_MASK     (0x1U << PMU_PWRDN_INTEN_PD_SHRM_PWR_SWITCH_INT_EN_SHIFT)    /* 0x00000004 */
#define PMU_PWRDN_INTEN_PD_AUDIO_PWR_SWITCH_INT_EN_SHIFT   (3U)
#define PMU_PWRDN_INTEN_PD_AUDIO_PWR_SWITCH_INT_EN_MASK    (0x1U << PMU_PWRDN_INTEN_PD_AUDIO_PWR_SWITCH_INT_EN_SHIFT)   /* 0x00000008 */
/* PWRDN_INT_STATUS */
#define PMU_PWRDN_INT_STATUS_OFFSET                        (0x8CU)
#define PMU_PWRDN_INT_STATUS_PD_DSP_PD_SWT_SHIFT           (0U)
#define PMU_PWRDN_INT_STATUS_PD_DSP_PD_SWT_MASK            (0x1U << PMU_PWRDN_INT_STATUS_PD_DSP_PD_SWT_SHIFT)           /* 0x00000001 */
#define PMU_PWRDN_INT_STATUS_PD_LOGIC_PD_SWT_SHIFT         (1U)
#define PMU_PWRDN_INT_STATUS_PD_LOGIC_PD_SWT_MASK          (0x1U << PMU_PWRDN_INT_STATUS_PD_LOGIC_PD_SWT_SHIFT)         /* 0x00000002 */
#define PMU_PWRDN_INT_STATUS_PD_SHRM_PD_SWT_SHIFT          (2U)
#define PMU_PWRDN_INT_STATUS_PD_SHRM_PD_SWT_MASK           (0x1U << PMU_PWRDN_INT_STATUS_PD_SHRM_PD_SWT_SHIFT)          /* 0x00000004 */
#define PMU_PWRDN_INT_STATUS_PD_AUDIO_PD_SWT_SHIFT         (3U)
#define PMU_PWRDN_INT_STATUS_PD_AUDIO_PD_SWT_MASK          (0x1U << PMU_PWRDN_INT_STATUS_PD_AUDIO_PD_SWT_SHIFT)         /* 0x00000008 */
/* WAKEUP_STATUS */
#define PMU_WAKEUP_STATUS_OFFSET                           (0x90U)
#define PMU_WAKEUP_STATUS_WAKEUP_PWRMODE_INT_STATUS_SHIFT  (0U)
#define PMU_WAKEUP_STATUS_WAKEUP_PWRMODE_INT_STATUS_MASK   (0x1U << PMU_WAKEUP_STATUS_WAKEUP_PWRMODE_INT_STATUS_SHIFT)  /* 0x00000001 */
#define PMU_WAKEUP_STATUS_PWRMODE_WAKEUP_GPIO_INT_STATUS_SHIFT (1U)
#define PMU_WAKEUP_STATUS_PWRMODE_WAKEUP_GPIO_INT_STATUS_MASK (0x1U << PMU_WAKEUP_STATUS_PWRMODE_WAKEUP_GPIO_INT_STATUS_SHIFT) /* 0x00000002 */
#define PMU_WAKEUP_STATUS_PWRMODE_WAKEUP_TIMEOUT_STATUS_SHIFT (2U)
#define PMU_WAKEUP_STATUS_PWRMODE_WAKEUP_TIMEOUT_STATUS_MASK (0x1U << PMU_WAKEUP_STATUS_PWRMODE_WAKEUP_TIMEOUT_STATUS_SHIFT) /* 0x00000004 */
#define PMU_WAKEUP_STATUS_PWRMODE_WAKEUP_DSP_SFT_STATUS_SHIFT (3U)
#define PMU_WAKEUP_STATUS_PWRMODE_WAKEUP_DSP_SFT_STATUS_MASK (0x1U << PMU_WAKEUP_STATUS_PWRMODE_WAKEUP_DSP_SFT_STATUS_SHIFT) /* 0x00000008 */
#define PMU_WAKEUP_STATUS_PWRMODE_WAKEUP_TIMER_STATUS_SHIFT (4U)
#define PMU_WAKEUP_STATUS_PWRMODE_WAKEUP_TIMER_STATUS_MASK (0x1U << PMU_WAKEUP_STATUS_PWRMODE_WAKEUP_TIMER_STATUS_SHIFT) /* 0x00000010 */
#define PMU_WAKEUP_STATUS_PWRMODE_WAKEUP_VAD_STATUS_SHIFT  (5U)
#define PMU_WAKEUP_STATUS_PWRMODE_WAKEUP_VAD_STATUS_MASK   (0x1U << PMU_WAKEUP_STATUS_PWRMODE_WAKEUP_VAD_STATUS_SHIFT)  /* 0x00000020 */
#define PMU_WAKEUP_STATUS_WAKEUP_DSP_INT_STATUS_SHIFT      (6U)
#define PMU_WAKEUP_STATUS_WAKEUP_DSP_INT_STATUS_MASK       (0x1U << PMU_WAKEUP_STATUS_WAKEUP_DSP_INT_STATUS_SHIFT)      /* 0x00000040 */
#define PMU_WAKEUP_STATUS_DSP_WAKEUP_GPIO_INT_STATUS_SHIFT (7U)
#define PMU_WAKEUP_STATUS_DSP_WAKEUP_GPIO_INT_STATUS_MASK  (0x1U << PMU_WAKEUP_STATUS_DSP_WAKEUP_GPIO_INT_STATUS_SHIFT) /* 0x00000080 */
#define PMU_WAKEUP_STATUS_DSP_WAKEUP_TIMEOUT_STATUS_SHIFT  (8U)
#define PMU_WAKEUP_STATUS_DSP_WAKEUP_TIMEOUT_STATUS_MASK   (0x1U << PMU_WAKEUP_STATUS_DSP_WAKEUP_TIMEOUT_STATUS_SHIFT)  /* 0x00000100 */
#define PMU_WAKEUP_STATUS_DSP_WAKEUP_SFT_STATUS_SHIFT      (9U)
#define PMU_WAKEUP_STATUS_DSP_WAKEUP_SFT_STATUS_MASK       (0x1U << PMU_WAKEUP_STATUS_DSP_WAKEUP_SFT_STATUS_SHIFT)      /* 0x00000200 */
#define PMU_WAKEUP_STATUS_DSP_WAKEUP_TIMER_STATUS_SHIFT    (10U)
#define PMU_WAKEUP_STATUS_DSP_WAKEUP_TIMER_STATUS_MASK     (0x1U << PMU_WAKEUP_STATUS_DSP_WAKEUP_TIMER_STATUS_SHIFT)    /* 0x00000400 */
#define PMU_WAKEUP_STATUS_DSP_WAKEUP_VAD_STATUS_SHIFT      (11U)
#define PMU_WAKEUP_STATUS_DSP_WAKEUP_VAD_STATUS_MASK       (0x1U << PMU_WAKEUP_STATUS_DSP_WAKEUP_VAD_STATUS_SHIFT)      /* 0x00000800 */
/* BUS_CLR */
#define PMU_BUS_CLR_OFFSET                                 (0xA0U)
#define PMU_BUS_CLR_CLR_DSP_SHIFT                          (0U)
#define PMU_BUS_CLR_CLR_DSP_MASK                           (0x1U << PMU_BUS_CLR_CLR_DSP_SHIFT)                          /* 0x00000001 */
#define PMU_BUS_CLR_CLR_LOGIC_SHIFT                        (1U)
#define PMU_BUS_CLR_CLR_LOGIC_MASK                         (0x1U << PMU_BUS_CLR_CLR_LOGIC_SHIFT)                        /* 0x00000002 */
#define PMU_BUS_CLR_CLR_SHRM_SHIFT                         (2U)
#define PMU_BUS_CLR_CLR_SHRM_MASK                          (0x1U << PMU_BUS_CLR_CLR_SHRM_SHIFT)                         /* 0x00000004 */
#define PMU_BUS_CLR_CLR_AUDIO_SHIFT                        (3U)
#define PMU_BUS_CLR_CLR_AUDIO_MASK                         (0x1U << PMU_BUS_CLR_CLR_AUDIO_SHIFT)                        /* 0x00000008 */
/* BUS_IDLE_REQ */
#define PMU_BUS_IDLE_REQ_OFFSET                            (0xA4U)
#define PMU_BUS_IDLE_REQ_IDLE_REQ_DSP_SHIFT                (0U)
#define PMU_BUS_IDLE_REQ_IDLE_REQ_DSP_MASK                 (0x1U << PMU_BUS_IDLE_REQ_IDLE_REQ_DSP_SHIFT)                /* 0x00000001 */
#define PMU_BUS_IDLE_REQ_IDLE_REQ_LOGIC_SHIFT              (1U)
#define PMU_BUS_IDLE_REQ_IDLE_REQ_LOGIC_MASK               (0x1U << PMU_BUS_IDLE_REQ_IDLE_REQ_LOGIC_SHIFT)              /* 0x00000002 */
#define PMU_BUS_IDLE_REQ_IDLE_REQ_SHRM_SHIFT               (2U)
#define PMU_BUS_IDLE_REQ_IDLE_REQ_SHRM_MASK                (0x1U << PMU_BUS_IDLE_REQ_IDLE_REQ_SHRM_SHIFT)               /* 0x00000004 */
#define PMU_BUS_IDLE_REQ_IDLE_REQ_AUDIO_SHIFT              (3U)
#define PMU_BUS_IDLE_REQ_IDLE_REQ_AUDIO_MASK               (0x1U << PMU_BUS_IDLE_REQ_IDLE_REQ_AUDIO_SHIFT)              /* 0x00000008 */
/* BUS_IDLE_ST */
#define PMU_BUS_IDLE_ST_OFFSET                             (0xA8U)
#define PMU_BUS_IDLE_ST                                    (0x0U)
#define PMU_BUS_IDLE_ST_IDLE_DSP_SHIFT                     (0U)
#define PMU_BUS_IDLE_ST_IDLE_DSP_MASK                      (0x1U << PMU_BUS_IDLE_ST_IDLE_DSP_SHIFT)                     /* 0x00000001 */
#define PMU_BUS_IDLE_ST_IDLE_LOGIC_SHIFT                   (1U)
#define PMU_BUS_IDLE_ST_IDLE_LOGIC_MASK                    (0x1U << PMU_BUS_IDLE_ST_IDLE_LOGIC_SHIFT)                   /* 0x00000002 */
#define PMU_BUS_IDLE_ST_IDLE_SHRM_SHIFT                    (2U)
#define PMU_BUS_IDLE_ST_IDLE_SHRM_MASK                     (0x1U << PMU_BUS_IDLE_ST_IDLE_SHRM_SHIFT)                    /* 0x00000004 */
#define PMU_BUS_IDLE_ST_IDLE_AUDIO_SHIFT                   (3U)
#define PMU_BUS_IDLE_ST_IDLE_AUDIO_MASK                    (0x1U << PMU_BUS_IDLE_ST_IDLE_AUDIO_SHIFT)                   /* 0x00000008 */
/* BUS_IDLE_ACK */
#define PMU_BUS_IDLE_ACK_OFFSET                            (0xACU)
#define PMU_BUS_IDLE_ACK                                   (0x0U)
#define PMU_BUS_IDLE_ACK_IDLE_ACK_DSP_SHIFT                (0U)
#define PMU_BUS_IDLE_ACK_IDLE_ACK_DSP_MASK                 (0x1U << PMU_BUS_IDLE_ACK_IDLE_ACK_DSP_SHIFT)                /* 0x00000001 */
#define PMU_BUS_IDLE_ACK_IDLE_ACK_LOGIC_SHIFT              (1U)
#define PMU_BUS_IDLE_ACK_IDLE_ACK_LOGIC_MASK               (0x1U << PMU_BUS_IDLE_ACK_IDLE_ACK_LOGIC_SHIFT)              /* 0x00000002 */
#define PMU_BUS_IDLE_ACK_IDLE_ACK_SHRM_SHIFT               (2U)
#define PMU_BUS_IDLE_ACK_IDLE_ACK_SHRM_MASK                (0x1U << PMU_BUS_IDLE_ACK_IDLE_ACK_SHRM_SHIFT)               /* 0x00000004 */
#define PMU_BUS_IDLE_ACK_IDLE_ACK_AUDIO_SHIFT              (3U)
#define PMU_BUS_IDLE_ACK_IDLE_ACK_AUDIO_MASK               (0x1U << PMU_BUS_IDLE_ACK_IDLE_ACK_AUDIO_SHIFT)              /* 0x00000008 */
/* POWER_ST */
#define PMU_POWER_ST_OFFSET                                (0xB0U)
#define PMU_POWER_ST                                       (0x0U)
#define PMU_POWER_ST_PWRMODE_POWER_STATE_SHIFT             (0U)
#define PMU_POWER_ST_PWRMODE_POWER_STATE_MASK              (0x1FU << PMU_POWER_ST_PWRMODE_POWER_STATE_SHIFT)            /* 0x0000001F */
#define PMU_POWER_ST_DSP_POWER_STATE_SHIFT                 (5U)
#define PMU_POWER_ST_DSP_POWER_STATE_MASK                  (0xFU << PMU_POWER_ST_DSP_POWER_STATE_SHIFT)                 /* 0x000001E0 */
/* CORE_PWR_ST */
#define PMU_CORE_PWR_ST_OFFSET                             (0xB4U)
#define PMU_CORE_PWR_ST                                    (0x0U)
#define PMU_CORE_PWR_ST_STANDBYWFI_CM4_SHIFT               (0U)
#define PMU_CORE_PWR_ST_STANDBYWFI_CM4_MASK                (0x1U << PMU_CORE_PWR_ST_STANDBYWFI_CM4_SHIFT)               /* 0x00000001 */
#define PMU_CORE_PWR_ST_STANDBYWFI_DSP_SHIFT               (1U)
#define PMU_CORE_PWR_ST_STANDBYWFI_DSP_MASK                (0x1U << PMU_CORE_PWR_ST_STANDBYWFI_DSP_SHIFT)               /* 0x00000002 */
/* OSC_CNT */
#define PMU_OSC_CNT_OFFSET                                 (0xB8U)
#define PMU_OSC_CNT_PMU_OSC_CNT_SHIFT                      (0U)
#define PMU_OSC_CNT_PMU_OSC_CNT_MASK                       (0xFFFFFU << PMU_OSC_CNT_PMU_OSC_CNT_SHIFT)                  /* 0x000FFFFF */
/* PLLLOCK_CNT */
#define PMU_PLLLOCK_CNT_OFFSET                             (0xBCU)
#define PMU_PLLLOCK_CNT_PMU_PLLLOCK_CNT_SHIFT              (0U)
#define PMU_PLLLOCK_CNT_PMU_PLLLOCK_CNT_MASK               (0xFFFFFU << PMU_PLLLOCK_CNT_PMU_PLLLOCK_CNT_SHIFT)          /* 0x000FFFFF */
/* PWRMODE_TIMEOUT_CNT */
#define PMU_PWRMODE_TIMEOUT_CNT_OFFSET                     (0xC0U)
#define PMU_PWRMODE_TIMEOUT_CNT_PWRMODE_TIMEOUT_COUNT_SHIFT (0U)
#define PMU_PWRMODE_TIMEOUT_CNT_PWRMODE_TIMEOUT_COUNT_MASK (0xFFFFFFFFU << PMU_PWRMODE_TIMEOUT_CNT_PWRMODE_TIMEOUT_COUNT_SHIFT) /* 0xFFFFFFFF */
/* NOC_AUTO_ENA */
#define PMU_NOC_AUTO_ENA_OFFSET                            (0xC4U)
#define PMU_NOC_AUTO_ENA_DSP_GATING_DISABLE_SHIFT          (0U)
#define PMU_NOC_AUTO_ENA_DSP_GATING_DISABLE_MASK           (0x1U << PMU_NOC_AUTO_ENA_DSP_GATING_DISABLE_SHIFT)          /* 0x00000001 */
#define PMU_NOC_AUTO_ENA_LOGIC_GATING_DISABLE_SHIFT        (1U)
#define PMU_NOC_AUTO_ENA_LOGIC_GATING_DISABLE_MASK         (0x1U << PMU_NOC_AUTO_ENA_LOGIC_GATING_DISABLE_SHIFT)        /* 0x00000002 */
#define PMU_NOC_AUTO_ENA_SHRM_GATING_DISABLE_SHIFT         (2U)
#define PMU_NOC_AUTO_ENA_SHRM_GATING_DISABLE_MASK          (0x1U << PMU_NOC_AUTO_ENA_SHRM_GATING_DISABLE_SHIFT)         /* 0x00000004 */
#define PMU_NOC_AUTO_ENA_AUDIO_GATING_DISABLE_SHIFT        (3U)
#define PMU_NOC_AUTO_ENA_AUDIO_GATING_DISABLE_MASK         (0x1U << PMU_NOC_AUTO_ENA_AUDIO_GATING_DISABLE_SHIFT)        /* 0x00000008 */
/* DSPAPM_CON */
#define PMU_DSPAPM_CON_OFFSET                              (0xD0U)
#define PMU_DSPAPM_CON_PD_DSP_WFI_PWRDN_EN_SHIFT           (0U)
#define PMU_DSPAPM_CON_PD_DSP_WFI_PWRDN_EN_MASK            (0x1U << PMU_DSPAPM_CON_PD_DSP_WFI_PWRDN_EN_SHIFT)           /* 0x00000001 */
#define PMU_DSPAPM_CON_PD_DSP_IDLE_EN_SHIFT                (1U)
#define PMU_DSPAPM_CON_PD_DSP_IDLE_EN_MASK                 (0x1U << PMU_DSPAPM_CON_PD_DSP_IDLE_EN_SHIFT)                /* 0x00000002 */
#define PMU_DSPAPM_CON_PD_DSP_LDO_ADJ_EN_SHIFT             (2U)
#define PMU_DSPAPM_CON_PD_DSP_LDO_ADJ_EN_MASK              (0x1U << PMU_DSPAPM_CON_PD_DSP_LDO_ADJ_EN_SHIFT)             /* 0x00000004 */
#define PMU_DSPAPM_CON_GLOBAL_INT_DISABLE_DSP_CFG_SHIFT    (3U)
#define PMU_DSPAPM_CON_GLOBAL_INT_DISABLE_DSP_CFG_MASK     (0x1U << PMU_DSPAPM_CON_GLOBAL_INT_DISABLE_DSP_CFG_SHIFT)    /* 0x00000008 */
#define PMU_DSPAPM_CON_PD_DSP_INT_WAKEUP_EN_SHIFT          (4U)
#define PMU_DSPAPM_CON_PD_DSP_INT_WAKEUP_EN_MASK           (0x1U << PMU_DSPAPM_CON_PD_DSP_INT_WAKEUP_EN_SHIFT)          /* 0x00000010 */
#define PMU_DSPAPM_CON_PD_DSP_GPIO_INT_WAKEUP_EN_SHIFT     (5U)
#define PMU_DSPAPM_CON_PD_DSP_GPIO_INT_WAKEUP_EN_MASK      (0x1U << PMU_DSPAPM_CON_PD_DSP_GPIO_INT_WAKEUP_EN_SHIFT)     /* 0x00000020 */
#define PMU_DSPAPM_CON_PD_DSP_TIMEOUT_WAKEUP_EN_SHIFT      (6U)
#define PMU_DSPAPM_CON_PD_DSP_TIMEOUT_WAKEUP_EN_MASK       (0x1U << PMU_DSPAPM_CON_PD_DSP_TIMEOUT_WAKEUP_EN_SHIFT)      /* 0x00000040 */
#define PMU_DSPAPM_CON_PD_DSP_TIMER_WAKEUP_EN_SHIFT        (7U)
#define PMU_DSPAPM_CON_PD_DSP_TIMER_WAKEUP_EN_MASK         (0x1U << PMU_DSPAPM_CON_PD_DSP_TIMER_WAKEUP_EN_SHIFT)        /* 0x00000080 */
#define PMU_DSPAPM_CON_PD_DSP_VAD_WAKEUP_EN_SHIFT          (8U)
#define PMU_DSPAPM_CON_PD_DSP_VAD_WAKEUP_EN_MASK           (0x1U << PMU_DSPAPM_CON_PD_DSP_VAD_WAKEUP_EN_SHIFT)          /* 0x00000100 */
#define PMU_DSPAPM_CON_PD_DSP_SFT_WAKEUP_SHIFT             (9U)
#define PMU_DSPAPM_CON_PD_DSP_SFT_WAKEUP_MASK              (0x1U << PMU_DSPAPM_CON_PD_DSP_SFT_WAKEUP_SHIFT)             /* 0x00000200 */
#define PMU_DSPAPM_CON_PD_DSP_TCM_RETPD_EN_SHIFT           (10U)
#define PMU_DSPAPM_CON_PD_DSP_TCM_RETPD_EN_MASK            (0x1U << PMU_DSPAPM_CON_PD_DSP_TCM_RETPD_EN_SHIFT)           /* 0x00000400 */
/* DSP_LDO_ADJ_CNT */
#define PMU_DSP_LDO_ADJ_CNT_OFFSET                         (0xD8U)
#define PMU_DSP_LDO_ADJ_CNT_DSP_LDO_ADJ_CNT_SHIFT          (0U)
#define PMU_DSP_LDO_ADJ_CNT_DSP_LDO_ADJ_CNT_MASK           (0xFFFFFU << PMU_DSP_LDO_ADJ_CNT_DSP_LDO_ADJ_CNT_SHIFT)      /* 0x000FFFFF */
/* DSP_TIMEOUT_CNT */
#define PMU_DSP_TIMEOUT_CNT_OFFSET                         (0xDCU)
#define PMU_DSP_TIMEOUT_CNT_DSP_TIMEOUT_COUNT_SHIFT        (0U)
#define PMU_DSP_TIMEOUT_CNT_DSP_TIMEOUT_COUNT_MASK         (0xFFFFFFFFU << PMU_DSP_TIMEOUT_CNT_DSP_TIMEOUT_COUNT_SHIFT) /* 0xFFFFFFFF */
/* PWRMODE_LDO_ADJ_CNT */
#define PMU_PWRMODE_LDO_ADJ_CNT_OFFSET                     (0xE0U)
#define PMU_PWRMODE_LDO_ADJ_CNT_PWRMODE_LDO_ADJ_CNT_SHIFT  (0U)
#define PMU_PWRMODE_LDO_ADJ_CNT_PWRMODE_LDO_ADJ_CNT_MASK   (0xFFFFFU << PMU_PWRMODE_LDO_ADJ_CNT_PWRMODE_LDO_ADJ_CNT_SHIFT) /* 0x000FFFFF */
/* SHRM_CON0 */
#define PMU_SHRM_CON0_OFFSET                               (0xE4U)
#define PMU_SHRM_CON0_SHAREMEM_PWRDWN_EN_SFT_SHIFT         (0U)
#define PMU_SHRM_CON0_SHAREMEM_PWRDWN_EN_SFT_MASK          (0xFU << PMU_SHRM_CON0_SHAREMEM_PWRDWN_EN_SFT_SHIFT)         /* 0x0000000F */
#define PMU_SHRM_CON0_SHAREMEM_RET1N_SFT_SHIFT             (4U)
#define PMU_SHRM_CON0_SHAREMEM_RET1N_SFT_MASK              (0xFU << PMU_SHRM_CON0_SHAREMEM_RET1N_SFT_SHIFT)             /* 0x000000F0 */
#define PMU_SHRM_CON0_SHAREMEM_RET2N_SFT_SHIFT             (8U)
#define PMU_SHRM_CON0_SHAREMEM_RET2N_SFT_MASK              (0xFU << PMU_SHRM_CON0_SHAREMEM_RET2N_SFT_SHIFT)             /* 0x00000F00 */
/* DSPTCM_CON0 */
#define PMU_DSPTCM_CON0_OFFSET                             (0xE8U)
#define PMU_DSPTCM_CON0_DSPDTCM_PGEN_SFT_SHIFT             (0U)
#define PMU_DSPTCM_CON0_DSPDTCM_PGEN_SFT_MASK              (0xFFU << PMU_DSPTCM_CON0_DSPDTCM_PGEN_SFT_SHIFT)            /* 0x000000FF */
#define PMU_DSPTCM_CON0_DSPDTCM_RET1N_SFT_SHIFT            (8U)
#define PMU_DSPTCM_CON0_DSPDTCM_RET1N_SFT_MASK             (0xFFU << PMU_DSPTCM_CON0_DSPDTCM_RET1N_SFT_SHIFT)           /* 0x0000FF00 */
/* DSPTCM_CON1 */
#define PMU_DSPTCM_CON1_OFFSET                             (0xECU)
#define PMU_DSPTCM_CON1_DSPDTCM_RET2N_SFT_SHIFT            (0U)
#define PMU_DSPTCM_CON1_DSPDTCM_RET2N_SFT_MASK             (0xFFU << PMU_DSPTCM_CON1_DSPDTCM_RET2N_SFT_SHIFT)           /* 0x000000FF */
#define PMU_DSPTCM_CON1_DSPITCM_PGEN_SFT_SHIFT             (8U)
#define PMU_DSPTCM_CON1_DSPITCM_PGEN_SFT_MASK              (0x1U << PMU_DSPTCM_CON1_DSPITCM_PGEN_SFT_SHIFT)             /* 0x00000100 */
#define PMU_DSPTCM_CON1_DSPITCM_RET1N_SFT_SHIFT            (9U)
#define PMU_DSPTCM_CON1_DSPITCM_RET1N_SFT_MASK             (0x1U << PMU_DSPTCM_CON1_DSPITCM_RET1N_SFT_SHIFT)            /* 0x00000200 */
#define PMU_DSPTCM_CON1_DSPITCM_RET2N_SFT_SHIFT            (10U)
#define PMU_DSPTCM_CON1_DSPITCM_RET2N_SFT_MASK             (0x1U << PMU_DSPTCM_CON1_DSPITCM_RET2N_SFT_SHIFT)            /* 0x00000400 */
/* SYS_REG0 */
#define PMU_SYS_REG0_OFFSET                                (0xF0U)
#define PMU_SYS_REG0_PMU_SYS_REG0_SHIFT                    (0U)
#define PMU_SYS_REG0_PMU_SYS_REG0_MASK                     (0xFFFFFFFFU << PMU_SYS_REG0_PMU_SYS_REG0_SHIFT)             /* 0xFFFFFFFF */
/* SYS_REG1 */
#define PMU_SYS_REG1_OFFSET                                (0xF4U)
#define PMU_SYS_REG1_PMU_SYS_REG1_SHIFT                    (0U)
#define PMU_SYS_REG1_PMU_SYS_REG1_MASK                     (0xFFFFFFFFU << PMU_SYS_REG1_PMU_SYS_REG1_SHIFT)             /* 0xFFFFFFFF */
/* SYS_REG2 */
#define PMU_SYS_REG2_OFFSET                                (0xF8U)
#define PMU_SYS_REG2_PMU_SYS_REG2_SHIFT                    (0U)
#define PMU_SYS_REG2_PMU_SYS_REG2_MASK                     (0xFFFFFFFFU << PMU_SYS_REG2_PMU_SYS_REG2_SHIFT)             /* 0xFFFFFFFF */
/* SYS_REG3 */
#define PMU_SYS_REG3_OFFSET                                (0xFCU)
#define PMU_SYS_REG3_PMU_SYS_REG3_SHIFT                    (0U)
#define PMU_SYS_REG3_PMU_SYS_REG3_MASK                     (0xFFFFFFFFU << PMU_SYS_REG3_PMU_SYS_REG3_SHIFT)             /* 0xFFFFFFFF */
/* SHRM_CON1 */
#define PMU_SHRM_CON1_OFFSET                               (0x100U)
#define PMU_SHRM_CON1_PWRMODE_SHRM_PWRDWN_EN_SHIFT         (0U)
#define PMU_SHRM_CON1_PWRMODE_SHRM_PWRDWN_EN_MASK          (0xFU << PMU_SHRM_CON1_PWRMODE_SHRM_PWRDWN_EN_SHIFT)         /* 0x0000000F */
#define PMU_SHRM_CON1_PWRMODE_SHRM_RET1N_SHIFT             (4U)
#define PMU_SHRM_CON1_PWRMODE_SHRM_RET1N_MASK              (0xFU << PMU_SHRM_CON1_PWRMODE_SHRM_RET1N_SHIFT)             /* 0x000000F0 */
#define PMU_SHRM_CON1_PWRMODE_SHRM_RET2N_SHIFT             (8U)
#define PMU_SHRM_CON1_PWRMODE_SHRM_RET2N_MASK              (0xFU << PMU_SHRM_CON1_PWRMODE_SHRM_RET2N_SHIFT)             /* 0x00000F00 */
/* DSPTCM_CON2 */
#define PMU_DSPTCM_CON2_OFFSET                             (0x104U)
#define PMU_DSPTCM_CON2_DSPAPM_DTCM_PGEN_SHIFT             (0U)
#define PMU_DSPTCM_CON2_DSPAPM_DTCM_PGEN_MASK              (0xFFU << PMU_DSPTCM_CON2_DSPAPM_DTCM_PGEN_SHIFT)            /* 0x000000FF */
#define PMU_DSPTCM_CON2_DSPAPM_DTCM_RET1N_SHIFT            (8U)
#define PMU_DSPTCM_CON2_DSPAPM_DTCM_RET1N_MASK             (0xFFU << PMU_DSPTCM_CON2_DSPAPM_DTCM_RET1N_SHIFT)           /* 0x0000FF00 */
/* DSPTCM_CON3 */
#define PMU_DSPTCM_CON3_OFFSET                             (0x108U)
#define PMU_DSPTCM_CON3_DSPAPM_DTCM_RET2N_SHIFT            (0U)
#define PMU_DSPTCM_CON3_DSPAPM_DTCM_RET2N_MASK             (0xFFU << PMU_DSPTCM_CON3_DSPAPM_DTCM_RET2N_SHIFT)           /* 0x000000FF */
#define PMU_DSPTCM_CON3_DSPAPM_ITCM_PGEN_SHIFT             (8U)
#define PMU_DSPTCM_CON3_DSPAPM_ITCM_PGEN_MASK              (0x1U << PMU_DSPTCM_CON3_DSPAPM_ITCM_PGEN_SHIFT)             /* 0x00000100 */
#define PMU_DSPTCM_CON3_DSPAPM_ITCM_RET1N_SHIFT            (9U)
#define PMU_DSPTCM_CON3_DSPAPM_ITCM_RET1N_MASK             (0x1U << PMU_DSPTCM_CON3_DSPAPM_ITCM_RET1N_SHIFT)            /* 0x00000200 */
#define PMU_DSPTCM_CON3_DSPAPM_ITCM_RET2N_SHIFT            (10U)
#define PMU_DSPTCM_CON3_DSPAPM_ITCM_RET2N_MASK             (0x1U << PMU_DSPTCM_CON3_DSPAPM_ITCM_RET2N_SHIFT)            /* 0x00000400 */
/******************************************DMA*******************************************/
/* DSR */
#define DMA_DSR_OFFSET                                     (0x0U)
#define DMA_DSR                                            (0x0U)
#define DMA_DSR_FIELD0000_SHIFT                            (0U)
#define DMA_DSR_FIELD0000_MASK                             (0xFU << DMA_DSR_FIELD0000_SHIFT)                            /* 0x0000000F */
#define DMA_DSR_FIELD0002_SHIFT                            (4U)
#define DMA_DSR_FIELD0002_MASK                             (0x1FU << DMA_DSR_FIELD0002_SHIFT)                           /* 0x000001F0 */
#define DMA_DSR_FIELD0001_SHIFT                            (9U)
#define DMA_DSR_FIELD0001_MASK                             (0x1U << DMA_DSR_FIELD0001_SHIFT)                            /* 0x00000200 */
/* DPC */
#define DMA_DPC_OFFSET                                     (0x4U)
#define DMA_DPC                                            (0x0U)
#define DMA_DPC_FIELD0000_SHIFT                            (0U)
#define DMA_DPC_FIELD0000_MASK                             (0xFFFFFFFFU << DMA_DPC_FIELD0000_SHIFT)                     /* 0xFFFFFFFF */
/* INTEN */
#define DMA_INTEN_OFFSET                                   (0x20U)
#define DMA_INTEN_FIELD0000_SHIFT                          (0U)
#define DMA_INTEN_FIELD0000_MASK                           (0xFFFFFFFFU << DMA_INTEN_FIELD0000_SHIFT)                   /* 0xFFFFFFFF */
/* EVENT_RIS */
#define DMA_EVENT_RIS_OFFSET                               (0x24U)
#define DMA_EVENT_RIS                                      (0x0U)
#define DMA_EVENT_RIS_FIELD0000_SHIFT                      (0U)
#define DMA_EVENT_RIS_FIELD0000_MASK                       (0xFFFFFFFFU << DMA_EVENT_RIS_FIELD0000_SHIFT)               /* 0xFFFFFFFF */
/* INTMIS */
#define DMA_INTMIS_OFFSET                                  (0x28U)
#define DMA_INTMIS                                         (0x0U)
#define DMA_INTMIS_FIELD0000_SHIFT                         (0U)
#define DMA_INTMIS_FIELD0000_MASK                          (0xFFFFFFFFU << DMA_INTMIS_FIELD0000_SHIFT)                  /* 0xFFFFFFFF */
/* INTCLR */
#define DMA_INTCLR_OFFSET                                  (0x2CU)
#define DMA_INTCLR_FIELD0000_SHIFT                         (0U)
#define DMA_INTCLR_FIELD0000_MASK                          (0xFFFFFFFFU << DMA_INTCLR_FIELD0000_SHIFT)                  /* 0xFFFFFFFF */
/* FSRD */
#define DMA_FSRD_OFFSET                                    (0x30U)
#define DMA_FSRD                                           (0x0U)
#define DMA_FSRD_FIELD0000_SHIFT                           (0U)
#define DMA_FSRD_FIELD0000_MASK                            (0xFFFFFFFFU << DMA_FSRD_FIELD0000_SHIFT)                    /* 0xFFFFFFFF */
/* FSRC */
#define DMA_FSRC_OFFSET                                    (0x34U)
#define DMA_FSRC                                           (0x0U)
#define DMA_FSRC_FIELD0000_SHIFT                           (0U)
#define DMA_FSRC_FIELD0000_MASK                            (0xFFFFFFFFU << DMA_FSRC_FIELD0000_SHIFT)                    /* 0xFFFFFFFF */
/* FTRD */
#define DMA_FTRD_OFFSET                                    (0x38U)
#define DMA_FTRD_FIELD0000_SHIFT                           (0U)
#define DMA_FTRD_FIELD0000_MASK                            (0x1U << DMA_FTRD_FIELD0000_SHIFT)                           /* 0x00000001 */
#define DMA_FTRD_FIELD0005_SHIFT                           (1U)
#define DMA_FTRD_FIELD0005_MASK                            (0x1U << DMA_FTRD_FIELD0005_SHIFT)                           /* 0x00000002 */
#define DMA_FTRD_FIELD0004_SHIFT                           (4U)
#define DMA_FTRD_FIELD0004_MASK                            (0x1U << DMA_FTRD_FIELD0004_SHIFT)                           /* 0x00000010 */
#define DMA_FTRD_FIELD0003_SHIFT                           (5U)
#define DMA_FTRD_FIELD0003_MASK                            (0x1U << DMA_FTRD_FIELD0003_SHIFT)                           /* 0x00000020 */
#define DMA_FTRD_FIELD0002_SHIFT                           (16U)
#define DMA_FTRD_FIELD0002_MASK                            (0x1U << DMA_FTRD_FIELD0002_SHIFT)                           /* 0x00010000 */
#define DMA_FTRD_FIELD0001_SHIFT                           (30U)
#define DMA_FTRD_FIELD0001_MASK                            (0x1U << DMA_FTRD_FIELD0001_SHIFT)                           /* 0x40000000 */
/* FTR0 */
#define DMA_FTR0_OFFSET                                    (0x40U)
#define DMA_FTR0                                           (0x0U)
#define DMA_FTR0_FIELD0000_SHIFT                           (0U)
#define DMA_FTR0_FIELD0000_MASK                            (0x1U << DMA_FTR0_FIELD0000_SHIFT)                           /* 0x00000001 */
#define DMA_FTR0_FIELD0011_SHIFT                           (1U)
#define DMA_FTR0_FIELD0011_MASK                            (0x1U << DMA_FTR0_FIELD0011_SHIFT)                           /* 0x00000002 */
#define DMA_FTR0_FIELD0010_SHIFT                           (5U)
#define DMA_FTR0_FIELD0010_MASK                            (0x1U << DMA_FTR0_FIELD0010_SHIFT)                           /* 0x00000020 */
#define DMA_FTR0_FIELD0009_SHIFT                           (6U)
#define DMA_FTR0_FIELD0009_MASK                            (0x1U << DMA_FTR0_FIELD0009_SHIFT)                           /* 0x00000040 */
#define DMA_FTR0_FIELD0008_SHIFT                           (7U)
#define DMA_FTR0_FIELD0008_MASK                            (0x1U << DMA_FTR0_FIELD0008_SHIFT)                           /* 0x00000080 */
#define DMA_FTR0_FIELD0007_SHIFT                           (12U)
#define DMA_FTR0_FIELD0007_MASK                            (0x1U << DMA_FTR0_FIELD0007_SHIFT)                           /* 0x00001000 */
#define DMA_FTR0_FIELD0006_SHIFT                           (13U)
#define DMA_FTR0_FIELD0006_MASK                            (0x1U << DMA_FTR0_FIELD0006_SHIFT)                           /* 0x00002000 */
#define DMA_FTR0_FIELD0005_SHIFT                           (16U)
#define DMA_FTR0_FIELD0005_MASK                            (0x1U << DMA_FTR0_FIELD0005_SHIFT)                           /* 0x00010000 */
#define DMA_FTR0_FIELD0004_SHIFT                           (17U)
#define DMA_FTR0_FIELD0004_MASK                            (0x1U << DMA_FTR0_FIELD0004_SHIFT)                           /* 0x00020000 */
#define DMA_FTR0_FIELD0003_SHIFT                           (18U)
#define DMA_FTR0_FIELD0003_MASK                            (0x1U << DMA_FTR0_FIELD0003_SHIFT)                           /* 0x00040000 */
#define DMA_FTR0_FIELD0002_SHIFT                           (30U)
#define DMA_FTR0_FIELD0002_MASK                            (0x1U << DMA_FTR0_FIELD0002_SHIFT)                           /* 0x40000000 */
#define DMA_FTR0_FIELD0001_SHIFT                           (31U)
#define DMA_FTR0_FIELD0001_MASK                            (0x1U << DMA_FTR0_FIELD0001_SHIFT)                           /* 0x80000000 */
/* FTR1 */
#define DMA_FTR1_OFFSET                                    (0x44U)
#define DMA_FTR1                                           (0x0U)
#define DMA_FTR1_FIELD0000_SHIFT                           (0U)
#define DMA_FTR1_FIELD0000_MASK                            (0x1U << DMA_FTR1_FIELD0000_SHIFT)                           /* 0x00000001 */
#define DMA_FTR1_FIELD0011_SHIFT                           (1U)
#define DMA_FTR1_FIELD0011_MASK                            (0x1U << DMA_FTR1_FIELD0011_SHIFT)                           /* 0x00000002 */
#define DMA_FTR1_FIELD0010_SHIFT                           (5U)
#define DMA_FTR1_FIELD0010_MASK                            (0x1U << DMA_FTR1_FIELD0010_SHIFT)                           /* 0x00000020 */
#define DMA_FTR1_FIELD0009_SHIFT                           (6U)
#define DMA_FTR1_FIELD0009_MASK                            (0x1U << DMA_FTR1_FIELD0009_SHIFT)                           /* 0x00000040 */
#define DMA_FTR1_FIELD0008_SHIFT                           (7U)
#define DMA_FTR1_FIELD0008_MASK                            (0x1U << DMA_FTR1_FIELD0008_SHIFT)                           /* 0x00000080 */
#define DMA_FTR1_FIELD0007_SHIFT                           (12U)
#define DMA_FTR1_FIELD0007_MASK                            (0x1U << DMA_FTR1_FIELD0007_SHIFT)                           /* 0x00001000 */
#define DMA_FTR1_FIELD0006_SHIFT                           (13U)
#define DMA_FTR1_FIELD0006_MASK                            (0x1U << DMA_FTR1_FIELD0006_SHIFT)                           /* 0x00002000 */
#define DMA_FTR1_FIELD0005_SHIFT                           (16U)
#define DMA_FTR1_FIELD0005_MASK                            (0x1U << DMA_FTR1_FIELD0005_SHIFT)                           /* 0x00010000 */
#define DMA_FTR1_FIELD0004_SHIFT                           (17U)
#define DMA_FTR1_FIELD0004_MASK                            (0x1U << DMA_FTR1_FIELD0004_SHIFT)                           /* 0x00020000 */
#define DMA_FTR1_FIELD0003_SHIFT                           (18U)
#define DMA_FTR1_FIELD0003_MASK                            (0x1U << DMA_FTR1_FIELD0003_SHIFT)                           /* 0x00040000 */
#define DMA_FTR1_FIELD0002_SHIFT                           (30U)
#define DMA_FTR1_FIELD0002_MASK                            (0x1U << DMA_FTR1_FIELD0002_SHIFT)                           /* 0x40000000 */
#define DMA_FTR1_FIELD0001_SHIFT                           (31U)
#define DMA_FTR1_FIELD0001_MASK                            (0x1U << DMA_FTR1_FIELD0001_SHIFT)                           /* 0x80000000 */
/* FTR2 */
#define DMA_FTR2_OFFSET                                    (0x48U)
#define DMA_FTR2                                           (0x0U)
#define DMA_FTR2_FIELD0000_SHIFT                           (0U)
#define DMA_FTR2_FIELD0000_MASK                            (0x1U << DMA_FTR2_FIELD0000_SHIFT)                           /* 0x00000001 */
#define DMA_FTR2_FIELD0011_SHIFT                           (1U)
#define DMA_FTR2_FIELD0011_MASK                            (0x1U << DMA_FTR2_FIELD0011_SHIFT)                           /* 0x00000002 */
#define DMA_FTR2_FIELD0010_SHIFT                           (5U)
#define DMA_FTR2_FIELD0010_MASK                            (0x1U << DMA_FTR2_FIELD0010_SHIFT)                           /* 0x00000020 */
#define DMA_FTR2_FIELD0009_SHIFT                           (6U)
#define DMA_FTR2_FIELD0009_MASK                            (0x1U << DMA_FTR2_FIELD0009_SHIFT)                           /* 0x00000040 */
#define DMA_FTR2_FIELD0008_SHIFT                           (7U)
#define DMA_FTR2_FIELD0008_MASK                            (0x1U << DMA_FTR2_FIELD0008_SHIFT)                           /* 0x00000080 */
#define DMA_FTR2_FIELD0007_SHIFT                           (12U)
#define DMA_FTR2_FIELD0007_MASK                            (0x1U << DMA_FTR2_FIELD0007_SHIFT)                           /* 0x00001000 */
#define DMA_FTR2_FIELD0006_SHIFT                           (13U)
#define DMA_FTR2_FIELD0006_MASK                            (0x1U << DMA_FTR2_FIELD0006_SHIFT)                           /* 0x00002000 */
#define DMA_FTR2_FIELD0005_SHIFT                           (16U)
#define DMA_FTR2_FIELD0005_MASK                            (0x1U << DMA_FTR2_FIELD0005_SHIFT)                           /* 0x00010000 */
#define DMA_FTR2_FIELD0004_SHIFT                           (17U)
#define DMA_FTR2_FIELD0004_MASK                            (0x1U << DMA_FTR2_FIELD0004_SHIFT)                           /* 0x00020000 */
#define DMA_FTR2_FIELD0003_SHIFT                           (18U)
#define DMA_FTR2_FIELD0003_MASK                            (0x1U << DMA_FTR2_FIELD0003_SHIFT)                           /* 0x00040000 */
#define DMA_FTR2_FIELD0002_SHIFT                           (30U)
#define DMA_FTR2_FIELD0002_MASK                            (0x1U << DMA_FTR2_FIELD0002_SHIFT)                           /* 0x40000000 */
#define DMA_FTR2_FIELD0001_SHIFT                           (31U)
#define DMA_FTR2_FIELD0001_MASK                            (0x1U << DMA_FTR2_FIELD0001_SHIFT)                           /* 0x80000000 */
/* FTR3 */
#define DMA_FTR3_OFFSET                                    (0x4CU)
#define DMA_FTR3                                           (0x0U)
#define DMA_FTR3_FIELD0000_SHIFT                           (0U)
#define DMA_FTR3_FIELD0000_MASK                            (0x1U << DMA_FTR3_FIELD0000_SHIFT)                           /* 0x00000001 */
#define DMA_FTR3_FIELD0011_SHIFT                           (1U)
#define DMA_FTR3_FIELD0011_MASK                            (0x1U << DMA_FTR3_FIELD0011_SHIFT)                           /* 0x00000002 */
#define DMA_FTR3_FIELD0010_SHIFT                           (5U)
#define DMA_FTR3_FIELD0010_MASK                            (0x1U << DMA_FTR3_FIELD0010_SHIFT)                           /* 0x00000020 */
#define DMA_FTR3_FIELD0009_SHIFT                           (6U)
#define DMA_FTR3_FIELD0009_MASK                            (0x1U << DMA_FTR3_FIELD0009_SHIFT)                           /* 0x00000040 */
#define DMA_FTR3_FIELD0008_SHIFT                           (7U)
#define DMA_FTR3_FIELD0008_MASK                            (0x1U << DMA_FTR3_FIELD0008_SHIFT)                           /* 0x00000080 */
#define DMA_FTR3_FIELD0007_SHIFT                           (12U)
#define DMA_FTR3_FIELD0007_MASK                            (0x1U << DMA_FTR3_FIELD0007_SHIFT)                           /* 0x00001000 */
#define DMA_FTR3_FIELD0006_SHIFT                           (13U)
#define DMA_FTR3_FIELD0006_MASK                            (0x1U << DMA_FTR3_FIELD0006_SHIFT)                           /* 0x00002000 */
#define DMA_FTR3_FIELD0005_SHIFT                           (16U)
#define DMA_FTR3_FIELD0005_MASK                            (0x1U << DMA_FTR3_FIELD0005_SHIFT)                           /* 0x00010000 */
#define DMA_FTR3_FIELD0004_SHIFT                           (17U)
#define DMA_FTR3_FIELD0004_MASK                            (0x1U << DMA_FTR3_FIELD0004_SHIFT)                           /* 0x00020000 */
#define DMA_FTR3_FIELD0003_SHIFT                           (18U)
#define DMA_FTR3_FIELD0003_MASK                            (0x1U << DMA_FTR3_FIELD0003_SHIFT)                           /* 0x00040000 */
#define DMA_FTR3_FIELD0002_SHIFT                           (30U)
#define DMA_FTR3_FIELD0002_MASK                            (0x1U << DMA_FTR3_FIELD0002_SHIFT)                           /* 0x40000000 */
#define DMA_FTR3_FIELD0001_SHIFT                           (31U)
#define DMA_FTR3_FIELD0001_MASK                            (0x1U << DMA_FTR3_FIELD0001_SHIFT)                           /* 0x80000000 */
/* FTR4 */
#define DMA_FTR4_OFFSET                                    (0x50U)
#define DMA_FTR4                                           (0x0U)
#define DMA_FTR4_FIELD0000_SHIFT                           (0U)
#define DMA_FTR4_FIELD0000_MASK                            (0x1U << DMA_FTR4_FIELD0000_SHIFT)                           /* 0x00000001 */
#define DMA_FTR4_FIELD0011_SHIFT                           (1U)
#define DMA_FTR4_FIELD0011_MASK                            (0x1U << DMA_FTR4_FIELD0011_SHIFT)                           /* 0x00000002 */
#define DMA_FTR4_FIELD0010_SHIFT                           (5U)
#define DMA_FTR4_FIELD0010_MASK                            (0x1U << DMA_FTR4_FIELD0010_SHIFT)                           /* 0x00000020 */
#define DMA_FTR4_FIELD0009_SHIFT                           (6U)
#define DMA_FTR4_FIELD0009_MASK                            (0x1U << DMA_FTR4_FIELD0009_SHIFT)                           /* 0x00000040 */
#define DMA_FTR4_FIELD0008_SHIFT                           (7U)
#define DMA_FTR4_FIELD0008_MASK                            (0x1U << DMA_FTR4_FIELD0008_SHIFT)                           /* 0x00000080 */
#define DMA_FTR4_FIELD0007_SHIFT                           (12U)
#define DMA_FTR4_FIELD0007_MASK                            (0x1U << DMA_FTR4_FIELD0007_SHIFT)                           /* 0x00001000 */
#define DMA_FTR4_FIELD0006_SHIFT                           (13U)
#define DMA_FTR4_FIELD0006_MASK                            (0x1U << DMA_FTR4_FIELD0006_SHIFT)                           /* 0x00002000 */
#define DMA_FTR4_FIELD0005_SHIFT                           (16U)
#define DMA_FTR4_FIELD0005_MASK                            (0x1U << DMA_FTR4_FIELD0005_SHIFT)                           /* 0x00010000 */
#define DMA_FTR4_FIELD0004_SHIFT                           (17U)
#define DMA_FTR4_FIELD0004_MASK                            (0x1U << DMA_FTR4_FIELD0004_SHIFT)                           /* 0x00020000 */
#define DMA_FTR4_FIELD0003_SHIFT                           (18U)
#define DMA_FTR4_FIELD0003_MASK                            (0x1U << DMA_FTR4_FIELD0003_SHIFT)                           /* 0x00040000 */
#define DMA_FTR4_FIELD0002_SHIFT                           (30U)
#define DMA_FTR4_FIELD0002_MASK                            (0x1U << DMA_FTR4_FIELD0002_SHIFT)                           /* 0x40000000 */
#define DMA_FTR4_FIELD0001_SHIFT                           (31U)
#define DMA_FTR4_FIELD0001_MASK                            (0x1U << DMA_FTR4_FIELD0001_SHIFT)                           /* 0x80000000 */
/* FTR5 */
#define DMA_FTR5_OFFSET                                    (0x54U)
#define DMA_FTR5                                           (0x0U)
#define DMA_FTR5_FIELD0000_SHIFT                           (0U)
#define DMA_FTR5_FIELD0000_MASK                            (0x1U << DMA_FTR5_FIELD0000_SHIFT)                           /* 0x00000001 */
#define DMA_FTR5_FIELD0011_SHIFT                           (1U)
#define DMA_FTR5_FIELD0011_MASK                            (0x1U << DMA_FTR5_FIELD0011_SHIFT)                           /* 0x00000002 */
#define DMA_FTR5_FIELD0010_SHIFT                           (5U)
#define DMA_FTR5_FIELD0010_MASK                            (0x1U << DMA_FTR5_FIELD0010_SHIFT)                           /* 0x00000020 */
#define DMA_FTR5_FIELD0009_SHIFT                           (6U)
#define DMA_FTR5_FIELD0009_MASK                            (0x1U << DMA_FTR5_FIELD0009_SHIFT)                           /* 0x00000040 */
#define DMA_FTR5_FIELD0008_SHIFT                           (7U)
#define DMA_FTR5_FIELD0008_MASK                            (0x1U << DMA_FTR5_FIELD0008_SHIFT)                           /* 0x00000080 */
#define DMA_FTR5_FIELD0007_SHIFT                           (12U)
#define DMA_FTR5_FIELD0007_MASK                            (0x1U << DMA_FTR5_FIELD0007_SHIFT)                           /* 0x00001000 */
#define DMA_FTR5_FIELD0006_SHIFT                           (13U)
#define DMA_FTR5_FIELD0006_MASK                            (0x1U << DMA_FTR5_FIELD0006_SHIFT)                           /* 0x00002000 */
#define DMA_FTR5_FIELD0005_SHIFT                           (16U)
#define DMA_FTR5_FIELD0005_MASK                            (0x1U << DMA_FTR5_FIELD0005_SHIFT)                           /* 0x00010000 */
#define DMA_FTR5_FIELD0004_SHIFT                           (17U)
#define DMA_FTR5_FIELD0004_MASK                            (0x1U << DMA_FTR5_FIELD0004_SHIFT)                           /* 0x00020000 */
#define DMA_FTR5_FIELD0003_SHIFT                           (18U)
#define DMA_FTR5_FIELD0003_MASK                            (0x1U << DMA_FTR5_FIELD0003_SHIFT)                           /* 0x00040000 */
#define DMA_FTR5_FIELD0002_SHIFT                           (30U)
#define DMA_FTR5_FIELD0002_MASK                            (0x1U << DMA_FTR5_FIELD0002_SHIFT)                           /* 0x40000000 */
#define DMA_FTR5_FIELD0001_SHIFT                           (31U)
#define DMA_FTR5_FIELD0001_MASK                            (0x1U << DMA_FTR5_FIELD0001_SHIFT)                           /* 0x80000000 */
/* CSR0 */
#define DMA_CSR0_OFFSET                                    (0x100U)
#define DMA_CSR0                                           (0x0U)
#define DMA_CSR0_FIELD0000_SHIFT                           (0U)
#define DMA_CSR0_FIELD0000_MASK                            (0xFU << DMA_CSR0_FIELD0000_SHIFT)                           /* 0x0000000F */
#define DMA_CSR0_FIELD0004_SHIFT                           (4U)
#define DMA_CSR0_FIELD0004_MASK                            (0x1FU << DMA_CSR0_FIELD0004_SHIFT)                          /* 0x000001F0 */
#define DMA_CSR0_FIELD0003_SHIFT                           (14U)
#define DMA_CSR0_FIELD0003_MASK                            (0x1U << DMA_CSR0_FIELD0003_SHIFT)                           /* 0x00004000 */
#define DMA_CSR0_FIELD0002_SHIFT                           (15U)
#define DMA_CSR0_FIELD0002_MASK                            (0x1U << DMA_CSR0_FIELD0002_SHIFT)                           /* 0x00008000 */
#define DMA_CSR0_FIELD0001_SHIFT                           (21U)
#define DMA_CSR0_FIELD0001_MASK                            (0x1U << DMA_CSR0_FIELD0001_SHIFT)                           /* 0x00200000 */
/* CPC0 */
#define DMA_CPC0_OFFSET                                    (0x104U)
#define DMA_CPC0                                           (0x0U)
#define DMA_CPC0_FIELD0000_SHIFT                           (0U)
#define DMA_CPC0_FIELD0000_MASK                            (0xFFFFFFFFU << DMA_CPC0_FIELD0000_SHIFT)                    /* 0xFFFFFFFF */
/* CSR1 */
#define DMA_CSR1_OFFSET                                    (0x108U)
#define DMA_CSR1                                           (0x0U)
#define DMA_CSR1_FIELD0000_SHIFT                           (0U)
#define DMA_CSR1_FIELD0000_MASK                            (0xFU << DMA_CSR1_FIELD0000_SHIFT)                           /* 0x0000000F */
#define DMA_CSR1_FIELD0004_SHIFT                           (4U)
#define DMA_CSR1_FIELD0004_MASK                            (0x1FU << DMA_CSR1_FIELD0004_SHIFT)                          /* 0x000001F0 */
#define DMA_CSR1_FIELD0003_SHIFT                           (14U)
#define DMA_CSR1_FIELD0003_MASK                            (0x1U << DMA_CSR1_FIELD0003_SHIFT)                           /* 0x00004000 */
#define DMA_CSR1_FIELD0002_SHIFT                           (15U)
#define DMA_CSR1_FIELD0002_MASK                            (0x1U << DMA_CSR1_FIELD0002_SHIFT)                           /* 0x00008000 */
#define DMA_CSR1_FIELD0001_SHIFT                           (21U)
#define DMA_CSR1_FIELD0001_MASK                            (0x1U << DMA_CSR1_FIELD0001_SHIFT)                           /* 0x00200000 */
/* CPC1 */
#define DMA_CPC1_OFFSET                                    (0x10CU)
#define DMA_CPC1                                           (0x0U)
#define DMA_CPC1_FIELD0000_SHIFT                           (0U)
#define DMA_CPC1_FIELD0000_MASK                            (0xFFFFFFFFU << DMA_CPC1_FIELD0000_SHIFT)                    /* 0xFFFFFFFF */
/* CSR2 */
#define DMA_CSR2_OFFSET                                    (0x110U)
#define DMA_CSR2                                           (0x0U)
#define DMA_CSR2_FIELD0000_SHIFT                           (0U)
#define DMA_CSR2_FIELD0000_MASK                            (0xFU << DMA_CSR2_FIELD0000_SHIFT)                           /* 0x0000000F */
#define DMA_CSR2_FIELD0004_SHIFT                           (4U)
#define DMA_CSR2_FIELD0004_MASK                            (0x1FU << DMA_CSR2_FIELD0004_SHIFT)                          /* 0x000001F0 */
#define DMA_CSR2_FIELD0003_SHIFT                           (14U)
#define DMA_CSR2_FIELD0003_MASK                            (0x1U << DMA_CSR2_FIELD0003_SHIFT)                           /* 0x00004000 */
#define DMA_CSR2_FIELD0002_SHIFT                           (15U)
#define DMA_CSR2_FIELD0002_MASK                            (0x1U << DMA_CSR2_FIELD0002_SHIFT)                           /* 0x00008000 */
#define DMA_CSR2_FIELD0001_SHIFT                           (21U)
#define DMA_CSR2_FIELD0001_MASK                            (0x1U << DMA_CSR2_FIELD0001_SHIFT)                           /* 0x00200000 */
/* CPC2 */
#define DMA_CPC2_OFFSET                                    (0x114U)
#define DMA_CPC2                                           (0x0U)
#define DMA_CPC2_FIELD0000_SHIFT                           (0U)
#define DMA_CPC2_FIELD0000_MASK                            (0xFFFFFFFFU << DMA_CPC2_FIELD0000_SHIFT)                    /* 0xFFFFFFFF */
/* CSR3 */
#define DMA_CSR3_OFFSET                                    (0x118U)
#define DMA_CSR3                                           (0x0U)
#define DMA_CSR3_FIELD0000_SHIFT                           (0U)
#define DMA_CSR3_FIELD0000_MASK                            (0xFU << DMA_CSR3_FIELD0000_SHIFT)                           /* 0x0000000F */
#define DMA_CSR3_FIELD0004_SHIFT                           (4U)
#define DMA_CSR3_FIELD0004_MASK                            (0x1FU << DMA_CSR3_FIELD0004_SHIFT)                          /* 0x000001F0 */
#define DMA_CSR3_FIELD0003_SHIFT                           (14U)
#define DMA_CSR3_FIELD0003_MASK                            (0x1U << DMA_CSR3_FIELD0003_SHIFT)                           /* 0x00004000 */
#define DMA_CSR3_FIELD0002_SHIFT                           (15U)
#define DMA_CSR3_FIELD0002_MASK                            (0x1U << DMA_CSR3_FIELD0002_SHIFT)                           /* 0x00008000 */
#define DMA_CSR3_FIELD0001_SHIFT                           (21U)
#define DMA_CSR3_FIELD0001_MASK                            (0x1U << DMA_CSR3_FIELD0001_SHIFT)                           /* 0x00200000 */
/* CPC3 */
#define DMA_CPC3_OFFSET                                    (0x11CU)
#define DMA_CPC3                                           (0x0U)
#define DMA_CPC3_FIELD0000_SHIFT                           (0U)
#define DMA_CPC3_FIELD0000_MASK                            (0xFFFFFFFFU << DMA_CPC3_FIELD0000_SHIFT)                    /* 0xFFFFFFFF */
/* CSR4 */
#define DMA_CSR4_OFFSET                                    (0x120U)
#define DMA_CSR4                                           (0x0U)
#define DMA_CSR4_FIELD0000_SHIFT                           (0U)
#define DMA_CSR4_FIELD0000_MASK                            (0xFU << DMA_CSR4_FIELD0000_SHIFT)                           /* 0x0000000F */
#define DMA_CSR4_FIELD0004_SHIFT                           (4U)
#define DMA_CSR4_FIELD0004_MASK                            (0x1FU << DMA_CSR4_FIELD0004_SHIFT)                          /* 0x000001F0 */
#define DMA_CSR4_FIELD0003_SHIFT                           (14U)
#define DMA_CSR4_FIELD0003_MASK                            (0x1U << DMA_CSR4_FIELD0003_SHIFT)                           /* 0x00004000 */
#define DMA_CSR4_FIELD0002_SHIFT                           (15U)
#define DMA_CSR4_FIELD0002_MASK                            (0x1U << DMA_CSR4_FIELD0002_SHIFT)                           /* 0x00008000 */
#define DMA_CSR4_FIELD0001_SHIFT                           (21U)
#define DMA_CSR4_FIELD0001_MASK                            (0x1U << DMA_CSR4_FIELD0001_SHIFT)                           /* 0x00200000 */
/* CPC4 */
#define DMA_CPC4_OFFSET                                    (0x124U)
#define DMA_CPC4                                           (0x0U)
#define DMA_CPC4_FIELD0000_SHIFT                           (0U)
#define DMA_CPC4_FIELD0000_MASK                            (0xFFFFFFFFU << DMA_CPC4_FIELD0000_SHIFT)                    /* 0xFFFFFFFF */
/* CSR5 */
#define DMA_CSR5_OFFSET                                    (0x128U)
#define DMA_CSR5                                           (0x0U)
#define DMA_CSR5_FIELD0000_SHIFT                           (0U)
#define DMA_CSR5_FIELD0000_MASK                            (0xFU << DMA_CSR5_FIELD0000_SHIFT)                           /* 0x0000000F */
#define DMA_CSR5_FIELD0004_SHIFT                           (4U)
#define DMA_CSR5_FIELD0004_MASK                            (0x1FU << DMA_CSR5_FIELD0004_SHIFT)                          /* 0x000001F0 */
#define DMA_CSR5_FIELD0003_SHIFT                           (14U)
#define DMA_CSR5_FIELD0003_MASK                            (0x1U << DMA_CSR5_FIELD0003_SHIFT)                           /* 0x00004000 */
#define DMA_CSR5_FIELD0002_SHIFT                           (15U)
#define DMA_CSR5_FIELD0002_MASK                            (0x1U << DMA_CSR5_FIELD0002_SHIFT)                           /* 0x00008000 */
#define DMA_CSR5_FIELD0001_SHIFT                           (21U)
#define DMA_CSR5_FIELD0001_MASK                            (0x1U << DMA_CSR5_FIELD0001_SHIFT)                           /* 0x00200000 */
/* CPC5 */
#define DMA_CPC5_OFFSET                                    (0x12CU)
#define DMA_CPC5                                           (0x0U)
#define DMA_CPC5_FIELD0000_SHIFT                           (0U)
#define DMA_CPC5_FIELD0000_MASK                            (0xFFFFFFFFU << DMA_CPC5_FIELD0000_SHIFT)                    /* 0xFFFFFFFF */
/* SAR0 */
#define DMA_SAR0_OFFSET                                    (0x400U)
#define DMA_SAR0                                           (0x0U)
#define DMA_SAR0_FIELD0000_SHIFT                           (0U)
#define DMA_SAR0_FIELD0000_MASK                            (0xFFFFFFFFU << DMA_SAR0_FIELD0000_SHIFT)                    /* 0xFFFFFFFF */
/* DAR0 */
#define DMA_DAR0_OFFSET                                    (0x404U)
#define DMA_DAR0                                           (0x0U)
#define DMA_DAR0_FIELD0000_SHIFT                           (0U)
#define DMA_DAR0_FIELD0000_MASK                            (0xFFFFFFFFU << DMA_DAR0_FIELD0000_SHIFT)                    /* 0xFFFFFFFF */
/* CCR0 */
#define DMA_CCR0_OFFSET                                    (0x408U)
#define DMA_CCR0                                           (0x0U)
#define DMA_CCR0_FIELD0000_SHIFT                           (0U)
#define DMA_CCR0_FIELD0000_MASK                            (0x1U << DMA_CCR0_FIELD0000_SHIFT)                           /* 0x00000001 */
#define DMA_CCR0_FIELD0009_SHIFT                           (1U)
#define DMA_CCR0_FIELD0009_MASK                            (0x7U << DMA_CCR0_FIELD0009_SHIFT)                           /* 0x0000000E */
#define DMA_CCR0_FIELD0008_SHIFT                           (4U)
#define DMA_CCR0_FIELD0008_MASK                            (0xFU << DMA_CCR0_FIELD0008_SHIFT)                           /* 0x000000F0 */
#define DMA_CCR0_FIELD0007_SHIFT                           (8U)
#define DMA_CCR0_FIELD0007_MASK                            (0x7U << DMA_CCR0_FIELD0007_SHIFT)                           /* 0x00000700 */
#define DMA_CCR0_FIELD0006_SHIFT                           (11U)
#define DMA_CCR0_FIELD0006_MASK                            (0x7U << DMA_CCR0_FIELD0006_SHIFT)                           /* 0x00003800 */
#define DMA_CCR0_FIELD0005_SHIFT                           (14U)
#define DMA_CCR0_FIELD0005_MASK                            (0x1U << DMA_CCR0_FIELD0005_SHIFT)                           /* 0x00004000 */
#define DMA_CCR0_FIELD0004_SHIFT                           (15U)
#define DMA_CCR0_FIELD0004_MASK                            (0x7U << DMA_CCR0_FIELD0004_SHIFT)                           /* 0x00038000 */
#define DMA_CCR0_FIELD0003_SHIFT                           (18U)
#define DMA_CCR0_FIELD0003_MASK                            (0xFU << DMA_CCR0_FIELD0003_SHIFT)                           /* 0x003C0000 */
#define DMA_CCR0_FIELD0002_SHIFT                           (22U)
#define DMA_CCR0_FIELD0002_MASK                            (0x7U << DMA_CCR0_FIELD0002_SHIFT)                           /* 0x01C00000 */
#define DMA_CCR0_FIELD0001_SHIFT                           (25U)
#define DMA_CCR0_FIELD0001_MASK                            (0x7U << DMA_CCR0_FIELD0001_SHIFT)                           /* 0x0E000000 */
/* LC0_0 */
#define DMA_LC0_0_OFFSET                                   (0x40CU)
#define DMA_LC0_0                                          (0x0U)
#define DMA_LC0_0_FIELD0000_SHIFT                          (0U)
#define DMA_LC0_0_FIELD0000_MASK                           (0xFFU << DMA_LC0_0_FIELD0000_SHIFT)                         /* 0x000000FF */
/* LC1_0 */
#define DMA_LC1_0_OFFSET                                   (0x410U)
#define DMA_LC1_0                                          (0x0U)
#define DMA_LC1_0_FIELD0000_SHIFT                          (0U)
#define DMA_LC1_0_FIELD0000_MASK                           (0xFFU << DMA_LC1_0_FIELD0000_SHIFT)                         /* 0x000000FF */
/* PADDING0 */
#define DMA_PADDING0_OFFSET                                (0x0U)
/* PADDING1 */
#define DMA_PADDING1_OFFSET                                (0x0U)
/* PADDING2 */
#define DMA_PADDING2_OFFSET                                (0x0U)
/* SAR1 */
#define DMA_SAR1_OFFSET                                    (0x420U)
#define DMA_SAR1                                           (0x0U)
#define DMA_SAR1_FIELD0000_SHIFT                           (0U)
#define DMA_SAR1_FIELD0000_MASK                            (0xFFFFFFFFU << DMA_SAR1_FIELD0000_SHIFT)                    /* 0xFFFFFFFF */
/* DAR1 */
#define DMA_DAR1_OFFSET                                    (0x424U)
#define DMA_DAR1                                           (0x0U)
#define DMA_DAR1_FIELD0000_SHIFT                           (0U)
#define DMA_DAR1_FIELD0000_MASK                            (0xFFFFFFFFU << DMA_DAR1_FIELD0000_SHIFT)                    /* 0xFFFFFFFF */
/* CCR1 */
#define DMA_CCR1_OFFSET                                    (0x428U)
#define DMA_CCR1                                           (0x0U)
#define DMA_CCR1_FIELD0000_SHIFT                           (0U)
#define DMA_CCR1_FIELD0000_MASK                            (0x1U << DMA_CCR1_FIELD0000_SHIFT)                           /* 0x00000001 */
#define DMA_CCR1_FIELD0009_SHIFT                           (1U)
#define DMA_CCR1_FIELD0009_MASK                            (0x7U << DMA_CCR1_FIELD0009_SHIFT)                           /* 0x0000000E */
#define DMA_CCR1_FIELD0008_SHIFT                           (4U)
#define DMA_CCR1_FIELD0008_MASK                            (0xFU << DMA_CCR1_FIELD0008_SHIFT)                           /* 0x000000F0 */
#define DMA_CCR1_FIELD0007_SHIFT                           (8U)
#define DMA_CCR1_FIELD0007_MASK                            (0x7U << DMA_CCR1_FIELD0007_SHIFT)                           /* 0x00000700 */
#define DMA_CCR1_FIELD0006_SHIFT                           (11U)
#define DMA_CCR1_FIELD0006_MASK                            (0x7U << DMA_CCR1_FIELD0006_SHIFT)                           /* 0x00003800 */
#define DMA_CCR1_FIELD0005_SHIFT                           (14U)
#define DMA_CCR1_FIELD0005_MASK                            (0x1U << DMA_CCR1_FIELD0005_SHIFT)                           /* 0x00004000 */
#define DMA_CCR1_FIELD0004_SHIFT                           (15U)
#define DMA_CCR1_FIELD0004_MASK                            (0x7U << DMA_CCR1_FIELD0004_SHIFT)                           /* 0x00038000 */
#define DMA_CCR1_FIELD0003_SHIFT                           (18U)
#define DMA_CCR1_FIELD0003_MASK                            (0xFU << DMA_CCR1_FIELD0003_SHIFT)                           /* 0x003C0000 */
#define DMA_CCR1_FIELD0002_SHIFT                           (22U)
#define DMA_CCR1_FIELD0002_MASK                            (0x7U << DMA_CCR1_FIELD0002_SHIFT)                           /* 0x01C00000 */
#define DMA_CCR1_FIELD0001_SHIFT                           (25U)
#define DMA_CCR1_FIELD0001_MASK                            (0x7U << DMA_CCR1_FIELD0001_SHIFT)                           /* 0x0E000000 */
/* LC0_1 */
#define DMA_LC0_1_OFFSET                                   (0x42CU)
#define DMA_LC0_1                                          (0x0U)
#define DMA_LC0_1_FIELD0000_SHIFT                          (0U)
#define DMA_LC0_1_FIELD0000_MASK                           (0xFFU << DMA_LC0_1_FIELD0000_SHIFT)                         /* 0x000000FF */
/* LC1_1 */
#define DMA_LC1_1_OFFSET                                   (0x430U)
#define DMA_LC1_1                                          (0x0U)
#define DMA_LC1_1_FIELD0000_SHIFT                          (0U)
#define DMA_LC1_1_FIELD0000_MASK                           (0xFFU << DMA_LC1_1_FIELD0000_SHIFT)                         /* 0x000000FF */
/* PADDING0 */
#define DMA_PADDING0_OFFSET                                (0x0U)
/* PADDING1 */
#define DMA_PADDING1_OFFSET                                (0x0U)
/* PADDING2 */
#define DMA_PADDING2_OFFSET                                (0x0U)
/* SAR2 */
#define DMA_SAR2_OFFSET                                    (0x440U)
#define DMA_SAR2                                           (0x0U)
#define DMA_SAR2_FIELD0000_SHIFT                           (0U)
#define DMA_SAR2_FIELD0000_MASK                            (0xFFFFFFFFU << DMA_SAR2_FIELD0000_SHIFT)                    /* 0xFFFFFFFF */
/* DAR2 */
#define DMA_DAR2_OFFSET                                    (0x444U)
#define DMA_DAR2                                           (0x0U)
#define DMA_DAR2_FIELD0000_SHIFT                           (0U)
#define DMA_DAR2_FIELD0000_MASK                            (0xFFFFFFFFU << DMA_DAR2_FIELD0000_SHIFT)                    /* 0xFFFFFFFF */
/* CCR2 */
#define DMA_CCR2_OFFSET                                    (0x448U)
#define DMA_CCR2                                           (0x0U)
#define DMA_CCR2_FIELD0000_SHIFT                           (0U)
#define DMA_CCR2_FIELD0000_MASK                            (0x1U << DMA_CCR2_FIELD0000_SHIFT)                           /* 0x00000001 */
#define DMA_CCR2_FIELD0009_SHIFT                           (1U)
#define DMA_CCR2_FIELD0009_MASK                            (0x7U << DMA_CCR2_FIELD0009_SHIFT)                           /* 0x0000000E */
#define DMA_CCR2_FIELD0008_SHIFT                           (4U)
#define DMA_CCR2_FIELD0008_MASK                            (0xFU << DMA_CCR2_FIELD0008_SHIFT)                           /* 0x000000F0 */
#define DMA_CCR2_FIELD0007_SHIFT                           (8U)
#define DMA_CCR2_FIELD0007_MASK                            (0x7U << DMA_CCR2_FIELD0007_SHIFT)                           /* 0x00000700 */
#define DMA_CCR2_FIELD0006_SHIFT                           (11U)
#define DMA_CCR2_FIELD0006_MASK                            (0x7U << DMA_CCR2_FIELD0006_SHIFT)                           /* 0x00003800 */
#define DMA_CCR2_FIELD0005_SHIFT                           (14U)
#define DMA_CCR2_FIELD0005_MASK                            (0x1U << DMA_CCR2_FIELD0005_SHIFT)                           /* 0x00004000 */
#define DMA_CCR2_FIELD0004_SHIFT                           (15U)
#define DMA_CCR2_FIELD0004_MASK                            (0x7U << DMA_CCR2_FIELD0004_SHIFT)                           /* 0x00038000 */
#define DMA_CCR2_FIELD0003_SHIFT                           (18U)
#define DMA_CCR2_FIELD0003_MASK                            (0xFU << DMA_CCR2_FIELD0003_SHIFT)                           /* 0x003C0000 */
#define DMA_CCR2_FIELD0002_SHIFT                           (22U)
#define DMA_CCR2_FIELD0002_MASK                            (0x7U << DMA_CCR2_FIELD0002_SHIFT)                           /* 0x01C00000 */
#define DMA_CCR2_FIELD0001_SHIFT                           (25U)
#define DMA_CCR2_FIELD0001_MASK                            (0x7U << DMA_CCR2_FIELD0001_SHIFT)                           /* 0x0E000000 */
/* LC0_2 */
#define DMA_LC0_2_OFFSET                                   (0x44CU)
#define DMA_LC0_2                                          (0x0U)
#define DMA_LC0_2_FIELD0000_SHIFT                          (0U)
#define DMA_LC0_2_FIELD0000_MASK                           (0xFFU << DMA_LC0_2_FIELD0000_SHIFT)                         /* 0x000000FF */
/* LC1_2 */
#define DMA_LC1_2_OFFSET                                   (0x450U)
#define DMA_LC1_2                                          (0x0U)
#define DMA_LC1_2_FIELD0000_SHIFT                          (0U)
#define DMA_LC1_2_FIELD0000_MASK                           (0xFFU << DMA_LC1_2_FIELD0000_SHIFT)                         /* 0x000000FF */
/* PADDING0 */
#define DMA_PADDING0_OFFSET                                (0x0U)
/* PADDING1 */
#define DMA_PADDING1_OFFSET                                (0x0U)
/* PADDING2 */
#define DMA_PADDING2_OFFSET                                (0x0U)
/* SAR3 */
#define DMA_SAR3_OFFSET                                    (0x460U)
#define DMA_SAR3                                           (0x0U)
#define DMA_SAR3_FIELD0000_SHIFT                           (0U)
#define DMA_SAR3_FIELD0000_MASK                            (0xFFFFFFFFU << DMA_SAR3_FIELD0000_SHIFT)                    /* 0xFFFFFFFF */
/* DAR3 */
#define DMA_DAR3_OFFSET                                    (0x464U)
#define DMA_DAR3                                           (0x0U)
#define DMA_DAR3_FIELD0000_SHIFT                           (0U)
#define DMA_DAR3_FIELD0000_MASK                            (0xFFFFFFFFU << DMA_DAR3_FIELD0000_SHIFT)                    /* 0xFFFFFFFF */
/* CCR3 */
#define DMA_CCR3_OFFSET                                    (0x468U)
#define DMA_CCR3                                           (0x0U)
#define DMA_CCR3_FIELD0000_SHIFT                           (0U)
#define DMA_CCR3_FIELD0000_MASK                            (0x1U << DMA_CCR3_FIELD0000_SHIFT)                           /* 0x00000001 */
#define DMA_CCR3_FIELD0009_SHIFT                           (1U)
#define DMA_CCR3_FIELD0009_MASK                            (0x7U << DMA_CCR3_FIELD0009_SHIFT)                           /* 0x0000000E */
#define DMA_CCR3_FIELD0008_SHIFT                           (4U)
#define DMA_CCR3_FIELD0008_MASK                            (0xFU << DMA_CCR3_FIELD0008_SHIFT)                           /* 0x000000F0 */
#define DMA_CCR3_FIELD0007_SHIFT                           (8U)
#define DMA_CCR3_FIELD0007_MASK                            (0x7U << DMA_CCR3_FIELD0007_SHIFT)                           /* 0x00000700 */
#define DMA_CCR3_FIELD0006_SHIFT                           (11U)
#define DMA_CCR3_FIELD0006_MASK                            (0x7U << DMA_CCR3_FIELD0006_SHIFT)                           /* 0x00003800 */
#define DMA_CCR3_FIELD0005_SHIFT                           (14U)
#define DMA_CCR3_FIELD0005_MASK                            (0x1U << DMA_CCR3_FIELD0005_SHIFT)                           /* 0x00004000 */
#define DMA_CCR3_FIELD0004_SHIFT                           (15U)
#define DMA_CCR3_FIELD0004_MASK                            (0x7U << DMA_CCR3_FIELD0004_SHIFT)                           /* 0x00038000 */
#define DMA_CCR3_FIELD0003_SHIFT                           (18U)
#define DMA_CCR3_FIELD0003_MASK                            (0xFU << DMA_CCR3_FIELD0003_SHIFT)                           /* 0x003C0000 */
#define DMA_CCR3_FIELD0002_SHIFT                           (22U)
#define DMA_CCR3_FIELD0002_MASK                            (0x7U << DMA_CCR3_FIELD0002_SHIFT)                           /* 0x01C00000 */
#define DMA_CCR3_FIELD0001_SHIFT                           (25U)
#define DMA_CCR3_FIELD0001_MASK                            (0x7U << DMA_CCR3_FIELD0001_SHIFT)                           /* 0x0E000000 */
/* LC0_3 */
#define DMA_LC0_3_OFFSET                                   (0x46CU)
#define DMA_LC0_3                                          (0x0U)
#define DMA_LC0_3_FIELD0000_SHIFT                          (0U)
#define DMA_LC0_3_FIELD0000_MASK                           (0xFFU << DMA_LC0_3_FIELD0000_SHIFT)                         /* 0x000000FF */
/* LC1_3 */
#define DMA_LC1_3_OFFSET                                   (0x470U)
#define DMA_LC1_3                                          (0x0U)
#define DMA_LC1_3_FIELD0000_SHIFT                          (0U)
#define DMA_LC1_3_FIELD0000_MASK                           (0xFFU << DMA_LC1_3_FIELD0000_SHIFT)                         /* 0x000000FF */
/* PADDING0 */
#define DMA_PADDING0_OFFSET                                (0x0U)
/* PADDING1 */
#define DMA_PADDING1_OFFSET                                (0x0U)
/* PADDING2 */
#define DMA_PADDING2_OFFSET                                (0x0U)
/* SAR4 */
#define DMA_SAR4_OFFSET                                    (0x480U)
#define DMA_SAR4                                           (0x0U)
#define DMA_SAR4_FIELD0000_SHIFT                           (0U)
#define DMA_SAR4_FIELD0000_MASK                            (0xFFFFFFFFU << DMA_SAR4_FIELD0000_SHIFT)                    /* 0xFFFFFFFF */
/* DAR4 */
#define DMA_DAR4_OFFSET                                    (0x484U)
#define DMA_DAR4                                           (0x0U)
#define DMA_DAR4_FIELD0000_SHIFT                           (0U)
#define DMA_DAR4_FIELD0000_MASK                            (0xFFFFFFFFU << DMA_DAR4_FIELD0000_SHIFT)                    /* 0xFFFFFFFF */
/* CCR4 */
#define DMA_CCR4_OFFSET                                    (0x488U)
#define DMA_CCR4                                           (0x0U)
#define DMA_CCR4_FIELD0000_SHIFT                           (0U)
#define DMA_CCR4_FIELD0000_MASK                            (0x1U << DMA_CCR4_FIELD0000_SHIFT)                           /* 0x00000001 */
#define DMA_CCR4_FIELD0009_SHIFT                           (1U)
#define DMA_CCR4_FIELD0009_MASK                            (0x7U << DMA_CCR4_FIELD0009_SHIFT)                           /* 0x0000000E */
#define DMA_CCR4_FIELD0008_SHIFT                           (4U)
#define DMA_CCR4_FIELD0008_MASK                            (0xFU << DMA_CCR4_FIELD0008_SHIFT)                           /* 0x000000F0 */
#define DMA_CCR4_FIELD0007_SHIFT                           (8U)
#define DMA_CCR4_FIELD0007_MASK                            (0x7U << DMA_CCR4_FIELD0007_SHIFT)                           /* 0x00000700 */
#define DMA_CCR4_FIELD0006_SHIFT                           (11U)
#define DMA_CCR4_FIELD0006_MASK                            (0x7U << DMA_CCR4_FIELD0006_SHIFT)                           /* 0x00003800 */
#define DMA_CCR4_FIELD0005_SHIFT                           (14U)
#define DMA_CCR4_FIELD0005_MASK                            (0x1U << DMA_CCR4_FIELD0005_SHIFT)                           /* 0x00004000 */
#define DMA_CCR4_FIELD0004_SHIFT                           (15U)
#define DMA_CCR4_FIELD0004_MASK                            (0x7U << DMA_CCR4_FIELD0004_SHIFT)                           /* 0x00038000 */
#define DMA_CCR4_FIELD0003_SHIFT                           (18U)
#define DMA_CCR4_FIELD0003_MASK                            (0xFU << DMA_CCR4_FIELD0003_SHIFT)                           /* 0x003C0000 */
#define DMA_CCR4_FIELD0002_SHIFT                           (22U)
#define DMA_CCR4_FIELD0002_MASK                            (0x7U << DMA_CCR4_FIELD0002_SHIFT)                           /* 0x01C00000 */
#define DMA_CCR4_FIELD0001_SHIFT                           (25U)
#define DMA_CCR4_FIELD0001_MASK                            (0x7U << DMA_CCR4_FIELD0001_SHIFT)                           /* 0x0E000000 */
/* LC0_4 */
#define DMA_LC0_4_OFFSET                                   (0x48CU)
#define DMA_LC0_4                                          (0x0U)
#define DMA_LC0_4_FIELD0000_SHIFT                          (0U)
#define DMA_LC0_4_FIELD0000_MASK                           (0xFFU << DMA_LC0_4_FIELD0000_SHIFT)                         /* 0x000000FF */
/* LC1_4 */
#define DMA_LC1_4_OFFSET                                   (0x490U)
#define DMA_LC1_4                                          (0x0U)
#define DMA_LC1_4_FIELD0000_SHIFT                          (0U)
#define DMA_LC1_4_FIELD0000_MASK                           (0xFFU << DMA_LC1_4_FIELD0000_SHIFT)                         /* 0x000000FF */
/* PADDING0 */
#define DMA_PADDING0_OFFSET                                (0x0U)
/* PADDING1 */
#define DMA_PADDING1_OFFSET                                (0x0U)
/* PADDING2 */
#define DMA_PADDING2_OFFSET                                (0x0U)
/* SAR5 */
#define DMA_SAR5_OFFSET                                    (0x4A0U)
#define DMA_SAR5                                           (0x0U)
#define DMA_SAR5_FIELD0000_SHIFT                           (0U)
#define DMA_SAR5_FIELD0000_MASK                            (0xFFFFFFFFU << DMA_SAR5_FIELD0000_SHIFT)                    /* 0xFFFFFFFF */
/* DAR5 */
#define DMA_DAR5_OFFSET                                    (0x4A4U)
#define DMA_DAR5                                           (0x0U)
#define DMA_DAR5_FIELD0000_SHIFT                           (0U)
#define DMA_DAR5_FIELD0000_MASK                            (0xFFFFFFFFU << DMA_DAR5_FIELD0000_SHIFT)                    /* 0xFFFFFFFF */
/* CCR5 */
#define DMA_CCR5_OFFSET                                    (0x4A8U)
#define DMA_CCR5                                           (0x0U)
#define DMA_CCR5_FIELD0000_SHIFT                           (0U)
#define DMA_CCR5_FIELD0000_MASK                            (0x1U << DMA_CCR5_FIELD0000_SHIFT)                           /* 0x00000001 */
#define DMA_CCR5_FIELD0009_SHIFT                           (1U)
#define DMA_CCR5_FIELD0009_MASK                            (0x7U << DMA_CCR5_FIELD0009_SHIFT)                           /* 0x0000000E */
#define DMA_CCR5_FIELD0008_SHIFT                           (4U)
#define DMA_CCR5_FIELD0008_MASK                            (0xFU << DMA_CCR5_FIELD0008_SHIFT)                           /* 0x000000F0 */
#define DMA_CCR5_FIELD0007_SHIFT                           (8U)
#define DMA_CCR5_FIELD0007_MASK                            (0x7U << DMA_CCR5_FIELD0007_SHIFT)                           /* 0x00000700 */
#define DMA_CCR5_FIELD0006_SHIFT                           (11U)
#define DMA_CCR5_FIELD0006_MASK                            (0x7U << DMA_CCR5_FIELD0006_SHIFT)                           /* 0x00003800 */
#define DMA_CCR5_FIELD0005_SHIFT                           (14U)
#define DMA_CCR5_FIELD0005_MASK                            (0x1U << DMA_CCR5_FIELD0005_SHIFT)                           /* 0x00004000 */
#define DMA_CCR5_FIELD0004_SHIFT                           (15U)
#define DMA_CCR5_FIELD0004_MASK                            (0x7U << DMA_CCR5_FIELD0004_SHIFT)                           /* 0x00038000 */
#define DMA_CCR5_FIELD0003_SHIFT                           (18U)
#define DMA_CCR5_FIELD0003_MASK                            (0xFU << DMA_CCR5_FIELD0003_SHIFT)                           /* 0x003C0000 */
#define DMA_CCR5_FIELD0002_SHIFT                           (22U)
#define DMA_CCR5_FIELD0002_MASK                            (0x7U << DMA_CCR5_FIELD0002_SHIFT)                           /* 0x01C00000 */
#define DMA_CCR5_FIELD0001_SHIFT                           (25U)
#define DMA_CCR5_FIELD0001_MASK                            (0x7U << DMA_CCR5_FIELD0001_SHIFT)                           /* 0x0E000000 */
/* LC0_5 */
#define DMA_LC0_5_OFFSET                                   (0x4ACU)
#define DMA_LC0_5                                          (0x0U)
#define DMA_LC0_5_FIELD0000_SHIFT                          (0U)
#define DMA_LC0_5_FIELD0000_MASK                           (0xFFU << DMA_LC0_5_FIELD0000_SHIFT)                         /* 0x000000FF */
/* LC1_5 */
#define DMA_LC1_5_OFFSET                                   (0x4B0U)
#define DMA_LC1_5                                          (0x0U)
#define DMA_LC1_5_FIELD0000_SHIFT                          (0U)
#define DMA_LC1_5_FIELD0000_MASK                           (0xFFU << DMA_LC1_5_FIELD0000_SHIFT)                         /* 0x000000FF */
/* PADDING0 */
#define DMA_PADDING0_OFFSET                                (0x0U)
/* PADDING1 */
#define DMA_PADDING1_OFFSET                                (0x0U)
/* PADDING2 */
#define DMA_PADDING2_OFFSET                                (0x0U)
/* DBGSTATUS */
#define DMA_DBGSTATUS_OFFSET                               (0xD00U)
#define DMA_DBGSTATUS                                      (0x0U)
#define DMA_DBGSTATUS_FIELD0000_SHIFT                      (0U)
#define DMA_DBGSTATUS_FIELD0000_MASK                       (0x3U << DMA_DBGSTATUS_FIELD0000_SHIFT)                      /* 0x00000003 */
/* DBGCMD */
#define DMA_DBGCMD_OFFSET                                  (0xD04U)
#define DMA_DBGCMD_FIELD0000_SHIFT                         (0U)
#define DMA_DBGCMD_FIELD0000_MASK                          (0x3U << DMA_DBGCMD_FIELD0000_SHIFT)                         /* 0x00000003 */
/* DBGINST0 */
#define DMA_DBGINST0_OFFSET                                (0xD08U)
#define DMA_DBGINST0_FIELD0000_SHIFT                       (0U)
#define DMA_DBGINST0_FIELD0000_MASK                        (0x1U << DMA_DBGINST0_FIELD0000_SHIFT)                       /* 0x00000001 */
#define DMA_DBGINST0_FIELD0003_SHIFT                       (8U)
#define DMA_DBGINST0_FIELD0003_MASK                        (0x7U << DMA_DBGINST0_FIELD0003_SHIFT)                       /* 0x00000700 */
#define DMA_DBGINST0_FIELD0002_SHIFT                       (16U)
#define DMA_DBGINST0_FIELD0002_MASK                        (0xFFU << DMA_DBGINST0_FIELD0002_SHIFT)                      /* 0x00FF0000 */
#define DMA_DBGINST0_FIELD0001_SHIFT                       (24U)
#define DMA_DBGINST0_FIELD0001_MASK                        (0xFFU << DMA_DBGINST0_FIELD0001_SHIFT)                      /* 0xFF000000 */
/* DBGINST1 */
#define DMA_DBGINST1_OFFSET                                (0xD0CU)
#define DMA_DBGINST1_FIELD0000_SHIFT                       (0U)
#define DMA_DBGINST1_FIELD0000_MASK                        (0xFFU << DMA_DBGINST1_FIELD0000_SHIFT)                      /* 0x000000FF */
#define DMA_DBGINST1_FIELD0003_SHIFT                       (8U)
#define DMA_DBGINST1_FIELD0003_MASK                        (0xFFU << DMA_DBGINST1_FIELD0003_SHIFT)                      /* 0x0000FF00 */
#define DMA_DBGINST1_FIELD0002_SHIFT                       (16U)
#define DMA_DBGINST1_FIELD0002_MASK                        (0xFFU << DMA_DBGINST1_FIELD0002_SHIFT)                      /* 0x00FF0000 */
#define DMA_DBGINST1_FIELD0001_SHIFT                       (24U)
#define DMA_DBGINST1_FIELD0001_MASK                        (0xFFU << DMA_DBGINST1_FIELD0001_SHIFT)                      /* 0xFF000000 */
/* CR0 */
#define DMA_CR0_OFFSET                                     (0xE00U)
#define DMA_CR0                                            (0x47051U)
#define DMA_CR0_FIELD0000_SHIFT                            (0U)
#define DMA_CR0_FIELD0000_MASK                             (0x1U << DMA_CR0_FIELD0000_SHIFT)                            /* 0x00000001 */
#define DMA_CR0_FIELD0005_SHIFT                            (1U)
#define DMA_CR0_FIELD0005_MASK                             (0x1U << DMA_CR0_FIELD0005_SHIFT)                            /* 0x00000002 */
#define DMA_CR0_FIELD0004_SHIFT                            (2U)
#define DMA_CR0_FIELD0004_MASK                             (0x1U << DMA_CR0_FIELD0004_SHIFT)                            /* 0x00000004 */
#define DMA_CR0_FIELD0003_SHIFT                            (4U)
#define DMA_CR0_FIELD0003_MASK                             (0x7U << DMA_CR0_FIELD0003_SHIFT)                            /* 0x00000070 */
#define DMA_CR0_FIELD0002_SHIFT                            (12U)
#define DMA_CR0_FIELD0002_MASK                             (0x1FU << DMA_CR0_FIELD0002_SHIFT)                           /* 0x0001F000 */
#define DMA_CR0_FIELD0001_SHIFT                            (17U)
#define DMA_CR0_FIELD0001_MASK                             (0x1FU << DMA_CR0_FIELD0001_SHIFT)                           /* 0x003E0000 */
/* CR1 */
#define DMA_CR1_OFFSET                                     (0xE04U)
#define DMA_CR1                                            (0x57U)
#define DMA_CR1_FIELD0000_SHIFT                            (0U)
#define DMA_CR1_FIELD0000_MASK                             (0x7U << DMA_CR1_FIELD0000_SHIFT)                            /* 0x00000007 */
#define DMA_CR1_FIELD0001_SHIFT                            (4U)
#define DMA_CR1_FIELD0001_MASK                             (0xFU << DMA_CR1_FIELD0001_SHIFT)                            /* 0x000000F0 */
/* CR2 */
#define DMA_CR2_OFFSET                                     (0xE08U)
#define DMA_CR2                                            (0x0U)
#define DMA_CR2_FIELD0000_SHIFT                            (0U)
#define DMA_CR2_FIELD0000_MASK                             (0xFFFFFFFFU << DMA_CR2_FIELD0000_SHIFT)                     /* 0xFFFFFFFF */
/* CR3 */
#define DMA_CR3_OFFSET                                     (0xE0CU)
#define DMA_CR3                                            (0x0U)
#define DMA_CR3_FIELD0000_SHIFT                            (0U)
#define DMA_CR3_FIELD0000_MASK                             (0xFFFFFFFFU << DMA_CR3_FIELD0000_SHIFT)                     /* 0xFFFFFFFF */
/* CR4 */
#define DMA_CR4_OFFSET                                     (0xE10U)
#define DMA_CR4                                            (0x6U)
#define DMA_CR4_FIELD0000_SHIFT                            (0U)
#define DMA_CR4_FIELD0000_MASK                             (0xFFFFFFFFU << DMA_CR4_FIELD0000_SHIFT)                     /* 0xFFFFFFFF */
/* CRDN */
#define DMA_CRDN_OFFSET                                    (0xE14U)
#define DMA_CRDN                                           (0x2094733U)
#define DMA_CRDN_FIELD0000_SHIFT                           (0U)
#define DMA_CRDN_FIELD0000_MASK                            (0x7U << DMA_CRDN_FIELD0000_SHIFT)                           /* 0x00000007 */
#define DMA_CRDN_FIELD0005_SHIFT                           (4U)
#define DMA_CRDN_FIELD0005_MASK                            (0x7U << DMA_CRDN_FIELD0005_SHIFT)                           /* 0x00000070 */
#define DMA_CRDN_FIELD0004_SHIFT                           (8U)
#define DMA_CRDN_FIELD0004_MASK                            (0xFU << DMA_CRDN_FIELD0004_SHIFT)                           /* 0x00000F00 */
#define DMA_CRDN_FIELD0003_SHIFT                           (12U)
#define DMA_CRDN_FIELD0003_MASK                            (0x7U << DMA_CRDN_FIELD0003_SHIFT)                           /* 0x00007000 */
#define DMA_CRDN_FIELD0002_SHIFT                           (16U)
#define DMA_CRDN_FIELD0002_MASK                            (0xFU << DMA_CRDN_FIELD0002_SHIFT)                           /* 0x000F0000 */
#define DMA_CRDN_FIELD0001_SHIFT                           (20U)
#define DMA_CRDN_FIELD0001_MASK                            (0x3FFU << DMA_CRDN_FIELD0001_SHIFT)                         /* 0x3FF00000 */
/* WD */
#define DMA_WD_OFFSET                                      (0xE80U)
#define DMA_WD_FIELD0000_SHIFT                             (0U)
#define DMA_WD_FIELD0000_MASK                              (0x1U << DMA_WD_FIELD0000_SHIFT)                             /* 0x00000001 */
/****************************************ACDCDIG*****************************************/
/* VUCTL */
#define ACDCDIG_VUCTL_OFFSET                               (0x0U)
#define ACDCDIG_VUCTL_ADCZDT_SHIFT                         (0U)
#define ACDCDIG_VUCTL_ADCZDT_MASK                          (0x1U << ACDCDIG_VUCTL_ADCZDT_SHIFT)                         /* 0x00000001 */
#define ACDCDIG_VUCTL_ADCFADE_SHIFT                        (1U)
#define ACDCDIG_VUCTL_ADCFADE_MASK                         (0x1U << ACDCDIG_VUCTL_ADCFADE_SHIFT)                        /* 0x00000002 */
#define ACDCDIG_VUCTL_ADC_BYPS_SHIFT                       (2U)
#define ACDCDIG_VUCTL_ADC_BYPS_MASK                        (0x1U << ACDCDIG_VUCTL_ADC_BYPS_SHIFT)                       /* 0x00000004 */
/* VUCTIME */
#define ACDCDIG_VUCTIME_OFFSET                             (0x4U)
#define ACDCDIG_VUCTIME_VUCT_SHIFT                         (0U)
#define ACDCDIG_VUCTIME_VUCT_MASK                          (0xFFU << ACDCDIG_VUCTIME_VUCT_SHIFT)                        /* 0x000000FF */
/* DIGEN */
#define ACDCDIG_DIGEN_OFFSET                               (0x8U)
#define ACDCDIG_DIGEN_I2STX_EN_SHIFT                       (0U)
#define ACDCDIG_DIGEN_I2STX_EN_MASK                        (0x1U << ACDCDIG_DIGEN_I2STX_EN_SHIFT)                       /* 0x00000001 */
#define ACDCDIG_DIGEN_ADC_EN_SHIFT                         (1U)
#define ACDCDIG_DIGEN_ADC_EN_MASK                          (0x1U << ACDCDIG_DIGEN_ADC_EN_SHIFT)                         /* 0x00000002 */
/* CLKCTRL */
#define ACDCDIG_CLKCTRL_OFFSET                             (0xCU)
#define ACDCDIG_CLKCTRL_FILTER_GATE_EN_SHIFT               (2U)
#define ACDCDIG_CLKCTRL_FILTER_GATE_EN_MASK                (0x1U << ACDCDIG_CLKCTRL_FILTER_GATE_EN_SHIFT)               /* 0x00000004 */
#define ACDCDIG_CLKCTRL_CKE_BCLK_SHIFT                     (3U)
#define ACDCDIG_CLKCTRL_CKE_BCLK_MASK                      (0x1U << ACDCDIG_CLKCTRL_CKE_BCLK_SHIFT)                     /* 0x00000008 */
#define ACDCDIG_CLKCTRL_I2STX_CKE_SHIFT                    (4U)
#define ACDCDIG_CLKCTRL_I2STX_CKE_MASK                     (0x1U << ACDCDIG_CLKCTRL_I2STX_CKE_SHIFT)                    /* 0x00000010 */
#define ACDCDIG_CLKCTRL_ADC_CKE_SHIFT                      (5U)
#define ACDCDIG_CLKCTRL_ADC_CKE_MASK                       (0x1U << ACDCDIG_CLKCTRL_ADC_CKE_SHIFT)                      /* 0x00000020 */
#define ACDCDIG_CLKCTRL_CIC_DS_RATIO_SHIFT                 (6U)
#define ACDCDIG_CLKCTRL_CIC_DS_RATIO_MASK                  (0x3U << ACDCDIG_CLKCTRL_CIC_DS_RATIO_SHIFT)                 /* 0x000000C0 */
/* CLKDIV */
#define ACDCDIG_CLKDIV_OFFSET                              (0x10U)
#define ACDCDIG_CLKDIV_INT_DIV_CON_SHIFT                   (0U)
#define ACDCDIG_CLKDIV_INT_DIV_CON_MASK                    (0xFU << ACDCDIG_CLKDIV_INT_DIV_CON_SHIFT)                   /* 0x0000000F */
/* REFCFG */
#define ACDCDIG_REFCFG_OFFSET                              (0x14U)
#define ACDCDIG_REFCFG_REF_TOP_TRIM_SHIFT                  (0U)
#define ACDCDIG_REFCFG_REF_TOP_TRIM_MASK                   (0xFU << ACDCDIG_REFCFG_REF_TOP_TRIM_SHIFT)                  /* 0x0000000F */
#define ACDCDIG_REFCFG_REF_ANA_TRIM_SHIFT                  (4U)
#define ACDCDIG_REFCFG_REF_ANA_TRIM_MASK                   (0x3U << ACDCDIG_REFCFG_REF_ANA_TRIM_SHIFT)                  /* 0x00000030 */
#define ACDCDIG_REFCFG_REF_TOP_PWD_SHIFT                   (6U)
#define ACDCDIG_REFCFG_REF_TOP_PWD_MASK                    (0x1U << ACDCDIG_REFCFG_REF_TOP_PWD_SHIFT)                   /* 0x00000040 */
/* ADCCFG0 */
#define ACDCDIG_ADCCFG0_OFFSET                             (0x18U)
#define ACDCDIG_ADCCFG0_ADC_DITH_SEL_SHIFT                 (0U)
#define ACDCDIG_ADCCFG0_ADC_DITH_SEL_MASK                  (0x7U << ACDCDIG_ADCCFG0_ADC_DITH_SEL_SHIFT)                 /* 0x00000007 */
#define ACDCDIG_ADCCFG0_ADC_DITH_EN_SHIFT                  (3U)
#define ACDCDIG_ADCCFG0_ADC_DITH_EN_MASK                   (0x1U << ACDCDIG_ADCCFG0_ADC_DITH_EN_SHIFT)                  /* 0x00000008 */
#define ACDCDIG_ADCCFG0_ADC_CHOP_CLK_SEL_SHIFT             (4U)
#define ACDCDIG_ADCCFG0_ADC_CHOP_CLK_SEL_MASK              (0x1U << ACDCDIG_ADCCFG0_ADC_CHOP_CLK_SEL_SHIFT)             /* 0x00000010 */
#define ACDCDIG_ADCCFG0_ADC_CHOP_EN_SHIFT                  (5U)
#define ACDCDIG_ADCCFG0_ADC_CHOP_EN_MASK                   (0x1U << ACDCDIG_ADCCFG0_ADC_CHOP_EN_SHIFT)                  /* 0x00000020 */
#define ACDCDIG_ADCCFG0_ADC_PWD_R_SHIFT                    (6U)
#define ACDCDIG_ADCCFG0_ADC_PWD_R_MASK                     (0x1U << ACDCDIG_ADCCFG0_ADC_PWD_R_SHIFT)                    /* 0x00000040 */
#define ACDCDIG_ADCCFG0_ADC_PWD_L_SHIFT                    (7U)
#define ACDCDIG_ADCCFG0_ADC_PWD_L_MASK                     (0x1U << ACDCDIG_ADCCFG0_ADC_PWD_L_SHIFT)                    /* 0x00000080 */
/* ADCCFG1 */
#define ACDCDIG_ADCCFG1_OFFSET                             (0x1CU)
#define ACDCDIG_ADCCFG1_ADC_BOOST_VAGOP_SHIFT              (0U)
#define ACDCDIG_ADCCFG1_ADC_BOOST_VAGOP_MASK               (0x1U << ACDCDIG_ADCCFG1_ADC_BOOST_VAGOP_SHIFT)              /* 0x00000001 */
#define ACDCDIG_ADCCFG1_ADC_BOOST_OPAMP_SHIFT              (1U)
#define ACDCDIG_ADCCFG1_ADC_BOOST_OPAMP_MASK               (0x1U << ACDCDIG_ADCCFG1_ADC_BOOST_OPAMP_SHIFT)              /* 0x00000002 */
#define ACDCDIG_ADCCFG1_ADC_ATTN_OPBIAS_SHIFT              (2U)
#define ACDCDIG_ADCCFG1_ADC_ATTN_OPBIAS_MASK               (0x1U << ACDCDIG_ADCCFG1_ADC_ATTN_OPBIAS_SHIFT)              /* 0x00000004 */
#define ACDCDIG_ADCCFG1_ADC_ATTN_ALLIBIAS_SHIFT            (3U)
#define ACDCDIG_ADCCFG1_ADC_ATTN_ALLIBIAS_MASK             (0x1U << ACDCDIG_ADCCFG1_ADC_ATTN_ALLIBIAS_SHIFT)            /* 0x00000008 */
/* ADCCFG2 */
#define ACDCDIG_ADCCFG2_OFFSET                             (0x20U)
#define ACDCDIG_ADCCFG2_CT_ADC_BOOST_SHIFT                 (0U)
#define ACDCDIG_ADCCFG2_CT_ADC_BOOST_MASK                  (0x1U << ACDCDIG_ADCCFG2_CT_ADC_BOOST_SHIFT)                 /* 0x00000001 */
#define ACDCDIG_ADCCFG2_CT_ADC_ATTN_SHIFT                  (1U)
#define ACDCDIG_ADCCFG2_CT_ADC_ATTN_MASK                   (0x1U << ACDCDIG_ADCCFG2_CT_ADC_ATTN_SHIFT)                  /* 0x00000002 */
#define ACDCDIG_ADCCFG2_CT_ADC_ATTN_OP_SHIFT               (2U)
#define ACDCDIG_ADCCFG2_CT_ADC_ATTN_OP_MASK                (0x1U << ACDCDIG_ADCCFG2_CT_ADC_ATTN_OP_SHIFT)               /* 0x00000004 */
#define ACDCDIG_ADCCFG2_ADC_OUT_SEL_SHIFT                  (3U)
#define ACDCDIG_ADCCFG2_ADC_OUT_SEL_MASK                   (0x1U << ACDCDIG_ADCCFG2_ADC_OUT_SEL_SHIFT)                  /* 0x00000008 */
#define ACDCDIG_ADCCFG2_CT_ADC_ZERO_SHIFT                  (4U)
#define ACDCDIG_ADCCFG2_CT_ADC_ZERO_MASK                   (0x1U << ACDCDIG_ADCCFG2_CT_ADC_ZERO_SHIFT)                  /* 0x00000010 */
#define ACDCDIG_ADCCFG2_CT_ADC_PWD_SHIFT                   (5U)
#define ACDCDIG_ADCCFG2_CT_ADC_PWD_MASK                    (0x1U << ACDCDIG_ADCCFG2_CT_ADC_PWD_SHIFT)                   /* 0x00000020 */
/* ADCCFG3 */
#define ACDCDIG_ADCCFG3_OFFSET                             (0x24U)
#define ACDCDIG_ADCCFG3_FIR_COM_BPS_SHIFT                  (0U)
#define ACDCDIG_ADCCFG3_FIR_COM_BPS_MASK                   (0x1U << ACDCDIG_ADCCFG3_FIR_COM_BPS_SHIFT)                  /* 0x00000001 */
#define ACDCDIG_ADCCFG3_SIG_SCALE_MODE_SHIFT               (1U)
#define ACDCDIG_ADCCFG3_SIG_SCALE_MODE_MASK                (0x1U << ACDCDIG_ADCCFG3_SIG_SCALE_MODE_SHIFT)               /* 0x00000002 */
#define ACDCDIG_ADCCFG3_ADCSRT_SHIFT                       (2U)
#define ACDCDIG_ADCCFG3_ADCSRT_MASK                        (0x7U << ACDCDIG_ADCCFG3_ADCSRT_SHIFT)                       /* 0x0000001C */
/* ADCVOLL */
#define ACDCDIG_ADCVOLL_OFFSET                             (0x28U)
#define ACDCDIG_ADCVOLL_ADCLV_SHIFT                        (0U)
#define ACDCDIG_ADCVOLL_ADCLV_MASK                         (0xFFU << ACDCDIG_ADCVOLL_ADCLV_SHIFT)                       /* 0x000000FF */
/* ADCVOLR */
#define ACDCDIG_ADCVOLR_OFFSET                             (0x2CU)
#define ACDCDIG_ADCVOLR_ADCRV_SHIFT                        (0U)
#define ACDCDIG_ADCVOLR_ADCRV_MASK                         (0xFFU << ACDCDIG_ADCVOLR_ADCRV_SHIFT)                       /* 0x000000FF */
/* ALC0 */
#define ACDCDIG_ALC0_OFFSET                                (0x30U)
#define ACDCDIG_ALC0_ADCRV_GAIN_POL_SHIFT                  (4U)
#define ACDCDIG_ALC0_ADCRV_GAIN_POL_MASK                   (0x1U << ACDCDIG_ALC0_ADCRV_GAIN_POL_SHIFT)                  /* 0x00000010 */
#define ACDCDIG_ALC0_ADCLV_GAIN_POL_SHIFT                  (5U)
#define ACDCDIG_ALC0_ADCLV_GAIN_POL_MASK                   (0x1U << ACDCDIG_ALC0_ADCLV_GAIN_POL_SHIFT)                  /* 0x00000020 */
#define ACDCDIG_ALC0_ALCR_SHIFT                            (6U)
#define ACDCDIG_ALC0_ALCR_MASK                             (0x1U << ACDCDIG_ALC0_ALCR_SHIFT)                            /* 0x00000040 */
#define ACDCDIG_ALC0_ALCL_SHIFT                            (7U)
#define ACDCDIG_ALC0_ALCL_MASK                             (0x1U << ACDCDIG_ALC0_ALCL_SHIFT)                            /* 0x00000080 */
/* ALC1 */
#define ACDCDIG_ALC1_OFFSET                                (0x34U)
#define ACDCDIG_ALC1_ALCRRATE_SHIFT                        (0U)
#define ACDCDIG_ALC1_ALCRRATE_MASK                         (0xFU << ACDCDIG_ALC1_ALCRRATE_SHIFT)                        /* 0x0000000F */
#define ACDCDIG_ALC1_ALCARATE_SHIFT                        (4U)
#define ACDCDIG_ALC1_ALCARATE_MASK                         (0xFU << ACDCDIG_ALC1_ALCARATE_SHIFT)                        /* 0x000000F0 */
/* ALC2 */
#define ACDCDIG_ALC2_OFFSET                                (0x38U)
#define ACDCDIG_ALC2_ALCMIN_SHIFT                          (0U)
#define ACDCDIG_ALC2_ALCMIN_MASK                           (0x7U << ACDCDIG_ALC2_ALCMIN_SHIFT)                          /* 0x00000007 */
#define ACDCDIG_ALC2_ALCMAX_SHIFT                          (4U)
#define ACDCDIG_ALC2_ALCMAX_MASK                           (0x7U << ACDCDIG_ALC2_ALCMAX_SHIFT)                          /* 0x00000070 */
#define ACDCDIG_ALC2_NGVALID_SHIFT                         (7U)
#define ACDCDIG_ALC2_NGVALID_MASK                          (0x1U << ACDCDIG_ALC2_NGVALID_SHIFT)                         /* 0x00000080 */
/* ADCNG */
#define ACDCDIG_ADCNG_OFFSET                               (0x3CU)
#define ACDCDIG_ADCNG_NGDLY_SHIFT                          (0U)
#define ACDCDIG_ADCNG_NGDLY_MASK                           (0x3U << ACDCDIG_ADCNG_NGDLY_SHIFT)                          /* 0x00000003 */
#define ACDCDIG_ADCNG_NGGATE_SHIFT                         (2U)
#define ACDCDIG_ADCNG_NGGATE_MASK                          (0x7U << ACDCDIG_ADCNG_NGGATE_SHIFT)                         /* 0x0000001C */
#define ACDCDIG_ADCNG_NGBOOST_SHIFT                        (5U)
#define ACDCDIG_ADCNG_NGBOOST_MASK                         (0x1U << ACDCDIG_ADCNG_NGBOOST_SHIFT)                        /* 0x00000020 */
#define ACDCDIG_ADCNG_NGEN_SHIFT                           (6U)
#define ACDCDIG_ADCNG_NGEN_MASK                            (0x1U << ACDCDIG_ADCNG_NGEN_SHIFT)                           /* 0x00000040 */
#define ACDCDIG_ADCNG_NGCHL_SHIFT                          (7U)
#define ACDCDIG_ADCNG_NGCHL_MASK                           (0x1U << ACDCDIG_ADCNG_NGCHL_SHIFT)                          /* 0x00000080 */
/* HPFCTRL */
#define ACDCDIG_HPFCTRL_OFFSET                             (0x40U)
#define ACDCDIG_HPFCTRL_HPFCF_SHIFT                        (4U)
#define ACDCDIG_HPFCTRL_HPFCF_MASK                         (0x3U << ACDCDIG_HPFCTRL_HPFCF_SHIFT)                        /* 0x00000030 */
#define ACDCDIG_HPFCTRL_HPFRE_SHIFT                        (6U)
#define ACDCDIG_HPFCTRL_HPFRE_MASK                         (0x1U << ACDCDIG_HPFCTRL_HPFRE_SHIFT)                        /* 0x00000040 */
#define ACDCDIG_HPFCTRL_HPFLE_SHIFT                        (7U)
#define ACDCDIG_HPFCTRL_HPFLE_MASK                         (0x1U << ACDCDIG_HPFCTRL_HPFLE_SHIFT)                        /* 0x00000080 */
/* ADCRVOLL */
#define ACDCDIG_ADCRVOLL_OFFSET                            (0x44U)
#define ACDCDIG_ADCRVOLL                                   (0x0U)
#define ACDCDIG_ADCRVOLL_ADCRLV_SHIFT                      (0U)
#define ACDCDIG_ADCRVOLL_ADCRLV_MASK                       (0x1U << ACDCDIG_ADCRVOLL_ADCRLV_SHIFT)                      /* 0x00000001 */
/* ADCRVOLR */
#define ACDCDIG_ADCRVOLR_OFFSET                            (0x48U)
#define ACDCDIG_ADCRVOLR                                   (0x0U)
#define ACDCDIG_ADCRVOLR_ADCRRV_SHIFT                      (0U)
#define ACDCDIG_ADCRVOLR_ADCRRV_MASK                       (0x1U << ACDCDIG_ADCRVOLR_ADCRRV_SHIFT)                      /* 0x00000001 */
/* PGACFG */
#define ACDCDIG_PGACFG_OFFSET                              (0x4CU)
#define ACDCDIG_PGACFG_PGA_R_DEC_SHIFT                     (0U)
#define ACDCDIG_PGACFG_PGA_R_DEC_MASK                      (0x3U << ACDCDIG_PGACFG_PGA_R_DEC_SHIFT)                     /* 0x00000003 */
#define ACDCDIG_PGACFG_PGA_L_DEC_SHIFT                     (2U)
#define ACDCDIG_PGACFG_PGA_L_DEC_MASK                      (0x3U << ACDCDIG_PGACFG_PGA_L_DEC_SHIFT)                     /* 0x0000000C */
#define ACDCDIG_PGACFG_PGA_R_PD_SHIFT                      (4U)
#define ACDCDIG_PGACFG_PGA_R_PD_MASK                       (0x1U << ACDCDIG_PGACFG_PGA_R_PD_SHIFT)                      /* 0x00000010 */
#define ACDCDIG_PGACFG_PGA_L_PD_SHIFT                      (5U)
#define ACDCDIG_PGACFG_PGA_L_PD_MASK                       (0x1U << ACDCDIG_PGACFG_PGA_L_PD_SHIFT)                      /* 0x00000020 */
#define ACDCDIG_PGACFG_PGA_CHOP_EN_SHIFT                   (6U)
#define ACDCDIG_PGACFG_PGA_CHOP_EN_MASK                    (0x1U << ACDCDIG_PGACFG_PGA_CHOP_EN_SHIFT)                   /* 0x00000040 */
/* PGAGAINL */
#define ACDCDIG_PGAGAINL_OFFSET                            (0x50U)
#define ACDCDIG_PGAGAINL_PGA_GAIN_L_SHIFT                  (0U)
#define ACDCDIG_PGAGAINL_PGA_GAIN_L_MASK                   (0x1FU << ACDCDIG_PGAGAINL_PGA_GAIN_L_SHIFT)                 /* 0x0000001F */
/* PGAGAINR */
#define ACDCDIG_PGAGAINR_OFFSET                            (0x54U)
#define ACDCDIG_PGAGAINR_PGA_GAIN_R_SHIFT                  (0U)
#define ACDCDIG_PGAGAINR_PGA_GAIN_R_MASK                   (0x1FU << ACDCDIG_PGAGAINR_PGA_GAIN_R_SHIFT)                 /* 0x0000001F */
/* LILMT1 */
#define ACDCDIG_LILMT1_OFFSET                              (0x58U)
#define ACDCDIG_LILMT1_MIN_LILMT_SHIFT                     (0U)
#define ACDCDIG_LILMT1_MIN_LILMT_MASK                      (0x7U << ACDCDIG_LILMT1_MIN_LILMT_SHIFT)                     /* 0x00000007 */
#define ACDCDIG_LILMT1_MAX_LILMT_SHIFT                     (4U)
#define ACDCDIG_LILMT1_MAX_LILMT_MASK                      (0x7U << ACDCDIG_LILMT1_MAX_LILMT_SHIFT)                     /* 0x00000070 */
#define ACDCDIG_LILMT1_LMT_EN_SHIFT                        (7U)
#define ACDCDIG_LILMT1_LMT_EN_MASK                         (0x1U << ACDCDIG_LILMT1_LMT_EN_SHIFT)                        /* 0x00000080 */
/* LILMT2 */
#define ACDCDIG_LILMT2_OFFSET                              (0x5CU)
#define ACDCDIG_LILMT2_RLS_RATE_SHIFT                      (0U)
#define ACDCDIG_LILMT2_RLS_RATE_MASK                       (0xFU << ACDCDIG_LILMT2_RLS_RATE_SHIFT)                      /* 0x0000000F */
#define ACDCDIG_LILMT2_ATK_RATE_SHIFT                      (4U)
#define ACDCDIG_LILMT2_ATK_RATE_MASK                       (0xFU << ACDCDIG_LILMT2_ATK_RATE_SHIFT)                      /* 0x000000F0 */
/* LILMTNG1 */
#define ACDCDIG_LILMTNG1_OFFSET                            (0x60U)
#define ACDCDIG_LILMTNG1_NGDLY_LI_SHIFT                    (0U)
#define ACDCDIG_LILMTNG1_NGDLY_LI_MASK                     (0x3U << ACDCDIG_LILMTNG1_NGDLY_LI_SHIFT)                    /* 0x00000003 */
#define ACDCDIG_LILMTNG1_NGGATE_LI_SHIFT                   (2U)
#define ACDCDIG_LILMTNG1_NGGATE_LI_MASK                    (0x7U << ACDCDIG_LILMTNG1_NGGATE_LI_SHIFT)                   /* 0x0000001C */
#define ACDCDIG_LILMTNG1_NGBOOST_LI_SHIFT                  (5U)
#define ACDCDIG_LILMTNG1_NGBOOST_LI_MASK                   (0x1U << ACDCDIG_LILMTNG1_NGBOOST_LI_SHIFT)                  /* 0x00000020 */
#define ACDCDIG_LILMTNG1_NGEN_LI_SHIFT                     (6U)
#define ACDCDIG_LILMTNG1_NGEN_LI_MASK                      (0x1U << ACDCDIG_LILMTNG1_NGEN_LI_SHIFT)                     /* 0x00000040 */
#define ACDCDIG_LILMTNG1_NGCHL_LI_SHIFT                    (7U)
#define ACDCDIG_LILMTNG1_NGCHL_LI_MASK                     (0x1U << ACDCDIG_LILMTNG1_NGCHL_LI_SHIFT)                    /* 0x00000080 */
/* LILMTNG2 */
#define ACDCDIG_LILMTNG2_OFFSET                            (0x64U)
#define ACDCDIG_LILMTNG2                                   (0x0U)
#define ACDCDIG_LILMTNG2_NGVALID_LI_SHIFT                  (0U)
#define ACDCDIG_LILMTNG2_NGVALID_LI_MASK                   (0x1U << ACDCDIG_LILMTNG2_NGVALID_LI_SHIFT)                  /* 0x00000001 */
/* PDMCTRL */
#define ACDCDIG_PDMCTRL_OFFSET                             (0x68U)
#define ACDCDIG_PDMCTRL_PDM_LR_SEL_SHIFT                   (0U)
#define ACDCDIG_PDMCTRL_PDM_LR_SEL_MASK                    (0x1U << ACDCDIG_PDMCTRL_PDM_LR_SEL_SHIFT)                   /* 0x00000001 */
#define ACDCDIG_PDMCTRL_PDM_MODE_SHIFT                     (1U)
#define ACDCDIG_PDMCTRL_PDM_MODE_MASK                      (0x1U << ACDCDIG_PDMCTRL_PDM_MODE_SHIFT)                     /* 0x00000002 */
#define ACDCDIG_PDMCTRL_PDM_EN_SHIFT                       (2U)
#define ACDCDIG_PDMCTRL_PDM_EN_MASK                        (0x1U << ACDCDIG_PDMCTRL_PDM_EN_SHIFT)                       /* 0x00000004 */
/* I2SCKM */
#define ACDCDIG_I2SCKM_OFFSET                              (0x6CU)
#define ACDCDIG_I2SCKM_I2SMST_SHIFT                        (0U)
#define ACDCDIG_I2SCKM_I2SMST_MASK                         (0x1U << ACDCDIG_I2SCKM_I2SMST_SHIFT)                        /* 0x00000001 */
#define ACDCDIG_I2SCKM_SCK_P_SHIFT                         (1U)
#define ACDCDIG_I2SCKM_SCK_P_MASK                          (0x1U << ACDCDIG_I2SCKM_SCK_P_SHIFT)                         /* 0x00000002 */
/* I2SDIV */
#define ACDCDIG_I2SDIV_OFFSET                              (0x70U)
#define ACDCDIG_I2SDIV_SCKDIV_SHIFT                        (0U)
#define ACDCDIG_I2SDIV_SCKDIV_MASK                         (0xFFU << ACDCDIG_I2SDIV_SCKDIV_SHIFT)                       /* 0x000000FF */
/* I2STXCR0 */
#define ACDCDIG_I2STXCR0_OFFSET                            (0x74U)
#define ACDCDIG_I2STXCR0_TXRL_P_SHIFT                      (0U)
#define ACDCDIG_I2STXCR0_TXRL_P_MASK                       (0x1U << ACDCDIG_I2STXCR0_TXRL_P_SHIFT)                      /* 0x00000001 */
#define ACDCDIG_I2STXCR0_SCKDTX_SHIFT                      (1U)
#define ACDCDIG_I2STXCR0_SCKDTX_MASK                       (0x3U << ACDCDIG_I2STXCR0_SCKDTX_SHIFT)                      /* 0x00000006 */
/* I2STXCR1 */
#define ACDCDIG_I2STXCR1_OFFSET                            (0x78U)
#define ACDCDIG_I2STXCR1_LSB_SHIFT                         (0U)
#define ACDCDIG_I2STXCR1_LSB_MASK                          (0x1U << ACDCDIG_I2STXCR1_LSB_SHIFT)                         /* 0x00000001 */
#define ACDCDIG_I2STXCR1_EXRL_SHIFT                        (1U)
#define ACDCDIG_I2STXCR1_EXRL_MASK                         (0x1U << ACDCDIG_I2STXCR1_EXRL_SHIFT)                        /* 0x00000002 */
#define ACDCDIG_I2STXCR1_IBM_SHIFT                         (2U)
#define ACDCDIG_I2STXCR1_IBM_MASK                          (0x3U << ACDCDIG_I2STXCR1_IBM_SHIFT)                         /* 0x0000000C */
#define ACDCDIG_I2STXCR1_PBM_SHIFT                         (4U)
#define ACDCDIG_I2STXCR1_PBM_MASK                          (0x3U << ACDCDIG_I2STXCR1_PBM_SHIFT)                         /* 0x00000030 */
#define ACDCDIG_I2STXCR1_TFS_SHIFT                         (6U)
#define ACDCDIG_I2STXCR1_TFS_MASK                          (0x1U << ACDCDIG_I2STXCR1_TFS_SHIFT)                         /* 0x00000040 */
/* I2STXCR2 */
#define ACDCDIG_I2STXCR2_OFFSET                            (0x7CU)
#define ACDCDIG_I2STXCR2_VDW_SHIFT                         (0U)
#define ACDCDIG_I2STXCR2_VDW_MASK                          (0x1FU << ACDCDIG_I2STXCR2_VDW_SHIFT)                        /* 0x0000001F */
/* I2STXCMD */
#define ACDCDIG_I2STXCMD_OFFSET                            (0x80U)
#define ACDCDIG_I2STXCMD_RCNT_SHIFT                        (0U)
#define ACDCDIG_I2STXCMD_RCNT_MASK                         (0x3FU << ACDCDIG_I2STXCMD_RCNT_SHIFT)                       /* 0x0000003F */
#define ACDCDIG_I2STXCMD_TXC_SHIFT                         (6U)
#define ACDCDIG_I2STXCMD_TXC_MASK                          (0x1U << ACDCDIG_I2STXCMD_TXC_SHIFT)                         /* 0x00000040 */
#define ACDCDIG_I2STXCMD_TXS_SHIFT                         (7U)
#define ACDCDIG_I2STXCMD_TXS_MASK                          (0x1U << ACDCDIG_I2STXCMD_TXS_SHIFT)                         /* 0x00000080 */
/* VERSION */
#define ACDCDIG_VERSION_OFFSET                             (0x84U)
#define ACDCDIG_VERSION                                    (0x1U)
#define ACDCDIG_VERSION_VER_SHIFT                          (0U)
#define ACDCDIG_VERSION_VER_MASK                           (0xFFU << ACDCDIG_VERSION_VER_SHIFT)                         /* 0x000000FF */
/******************************************UART******************************************/
/* RBR */
#define UART_RBR_OFFSET                                    (0x0U)
#define UART_RBR_DATA_INPUT_SHIFT                          (0U)
#define UART_RBR_DATA_INPUT_MASK                           (0xFFU << UART_RBR_DATA_INPUT_SHIFT)                         /* 0x000000FF */
/* THR */
#define UART_THR_OFFSET                                    (0x0U)
#define UART_THR_DATA_OUTPUT_SHIFT                         (0U)
#define UART_THR_DATA_OUTPUT_MASK                          (0xFFU << UART_THR_DATA_OUTPUT_SHIFT)                        /* 0x000000FF */
/* DLL */
#define UART_DLL_OFFSET                                    (0x0U)
#define UART_DLL_BAUD_RATE_DIVISOR_L_SHIFT                 (0U)
#define UART_DLL_BAUD_RATE_DIVISOR_L_MASK                  (0xFFU << UART_DLL_BAUD_RATE_DIVISOR_L_SHIFT)                /* 0x000000FF */
/* DLH */
#define UART_DLH_OFFSET                                    (0x4U)
#define UART_DLH_BAUD_RATE_DIVISOR_H_SHIFT                 (0U)
#define UART_DLH_BAUD_RATE_DIVISOR_H_MASK                  (0xFFU << UART_DLH_BAUD_RATE_DIVISOR_H_SHIFT)                /* 0x000000FF */
/* IER */
#define UART_IER_OFFSET                                    (0x4U)
#define UART_IER_RECEIVE_DATA_AVAILABLE_INT_EN_SHIFT       (0U)
#define UART_IER_RECEIVE_DATA_AVAILABLE_INT_EN_MASK        (0x1U << UART_IER_RECEIVE_DATA_AVAILABLE_INT_EN_SHIFT)       /* 0x00000001 */
#define UART_IER_TRANS_HOLD_EMPTY_INT_EN_SHIFT             (1U)
#define UART_IER_TRANS_HOLD_EMPTY_INT_EN_MASK              (0x1U << UART_IER_TRANS_HOLD_EMPTY_INT_EN_SHIFT)             /* 0x00000002 */
#define UART_IER_RECEIVE_LINE_STATUS_INT_EN_SHIFT          (2U)
#define UART_IER_RECEIVE_LINE_STATUS_INT_EN_MASK           (0x1U << UART_IER_RECEIVE_LINE_STATUS_INT_EN_SHIFT)          /* 0x00000004 */
#define UART_IER_MODEM_STATUS_INT_EN_SHIFT                 (3U)
#define UART_IER_MODEM_STATUS_INT_EN_MASK                  (0x1U << UART_IER_MODEM_STATUS_INT_EN_SHIFT)                 /* 0x00000008 */
#define UART_IER_PROG_THRE_INT_EN_SHIFT                    (7U)
#define UART_IER_PROG_THRE_INT_EN_MASK                     (0x1U << UART_IER_PROG_THRE_INT_EN_SHIFT)                    /* 0x00000080 */
/* IIR */
#define UART_IIR_OFFSET                                    (0x8U)
#define UART_IIR                                           (0x0U)
#define UART_IIR_INT_ID_SHIFT                              (0U)
#define UART_IIR_INT_ID_MASK                               (0xFU << UART_IIR_INT_ID_SHIFT)                              /* 0x0000000F */
#define UART_IIR_FIFOS_EN_SHIFT                            (6U)
#define UART_IIR_FIFOS_EN_MASK                             (0x3U << UART_IIR_FIFOS_EN_SHIFT)                            /* 0x000000C0 */
/* FCR */
#define UART_FCR_OFFSET                                    (0x8U)
#define UART_FCR_FIFO_EN_SHIFT                             (0U)
#define UART_FCR_FIFO_EN_MASK                              (0x1U << UART_FCR_FIFO_EN_SHIFT)                             /* 0x00000001 */
#define UART_FCR_RCVR_FIFO_RESET_SHIFT                     (1U)
#define UART_FCR_RCVR_FIFO_RESET_MASK                      (0x1U << UART_FCR_RCVR_FIFO_RESET_SHIFT)                     /* 0x00000002 */
#define UART_FCR_XMIT_FIFO_RESET_SHIFT                     (2U)
#define UART_FCR_XMIT_FIFO_RESET_MASK                      (0x1U << UART_FCR_XMIT_FIFO_RESET_SHIFT)                     /* 0x00000004 */
#define UART_FCR_DMA_MODE_SHIFT                            (3U)
#define UART_FCR_DMA_MODE_MASK                             (0x1U << UART_FCR_DMA_MODE_SHIFT)                            /* 0x00000008 */
#define UART_FCR_TX_EMPTY_TRIGGER_SHIFT                    (4U)
#define UART_FCR_TX_EMPTY_TRIGGER_MASK                     (0x3U << UART_FCR_TX_EMPTY_TRIGGER_SHIFT)                    /* 0x00000030 */
#define UART_FCR_RCVR_TRIGGER_SHIFT                        (6U)
#define UART_FCR_RCVR_TRIGGER_MASK                         (0x3U << UART_FCR_RCVR_TRIGGER_SHIFT)                        /* 0x000000C0 */
/* LCR */
#define UART_LCR_OFFSET                                    (0xCU)
#define UART_LCR_DATA_LENGTH_SEL_SHIFT                     (0U)
#define UART_LCR_DATA_LENGTH_SEL_MASK                      (0x3U << UART_LCR_DATA_LENGTH_SEL_SHIFT)                     /* 0x00000003 */
#define UART_LCR_STOP_BITS_NUM_SHIFT                       (2U)
#define UART_LCR_STOP_BITS_NUM_MASK                        (0x1U << UART_LCR_STOP_BITS_NUM_SHIFT)                       /* 0x00000004 */
#define UART_LCR_PARITY_EN_SHIFT                           (3U)
#define UART_LCR_PARITY_EN_MASK                            (0x1U << UART_LCR_PARITY_EN_SHIFT)                           /* 0x00000008 */
#define UART_LCR_EVEN_PARITY_SEL_SHIFT                     (4U)
#define UART_LCR_EVEN_PARITY_SEL_MASK                      (0x1U << UART_LCR_EVEN_PARITY_SEL_SHIFT)                     /* 0x00000010 */
#define UART_LCR_BREAK_CTRL_SHIFT                          (6U)
#define UART_LCR_BREAK_CTRL_MASK                           (0x1U << UART_LCR_BREAK_CTRL_SHIFT)                          /* 0x00000040 */
#define UART_LCR_DIV_LAT_ACCESS_SHIFT                      (7U)
#define UART_LCR_DIV_LAT_ACCESS_MASK                       (0x1U << UART_LCR_DIV_LAT_ACCESS_SHIFT)                      /* 0x00000080 */
/* MCR */
#define UART_MCR_OFFSET                                    (0x10U)
#define UART_MCR_DATA_TERMINAL_READY_SHIFT                 (0U)
#define UART_MCR_DATA_TERMINAL_READY_MASK                  (0x1U << UART_MCR_DATA_TERMINAL_READY_SHIFT)                 /* 0x00000001 */
#define UART_MCR_REQ_TO_SEND_SHIFT                         (1U)
#define UART_MCR_REQ_TO_SEND_MASK                          (0x1U << UART_MCR_REQ_TO_SEND_SHIFT)                         /* 0x00000002 */
#define UART_MCR_OUT1_SHIFT                                (2U)
#define UART_MCR_OUT1_MASK                                 (0x1U << UART_MCR_OUT1_SHIFT)                                /* 0x00000004 */
#define UART_MCR_OUT2_SHIFT                                (3U)
#define UART_MCR_OUT2_MASK                                 (0x1U << UART_MCR_OUT2_SHIFT)                                /* 0x00000008 */
#define UART_MCR_LOOPBACK_SHIFT                            (4U)
#define UART_MCR_LOOPBACK_MASK                             (0x1U << UART_MCR_LOOPBACK_SHIFT)                            /* 0x00000010 */
#define UART_MCR_AUTO_FLOW_CTRL_EN_SHIFT                   (5U)
#define UART_MCR_AUTO_FLOW_CTRL_EN_MASK                    (0x1U << UART_MCR_AUTO_FLOW_CTRL_EN_SHIFT)                   /* 0x00000020 */
#define UART_MCR_SIR_MODE_EN_SHIFT                         (6U)
#define UART_MCR_SIR_MODE_EN_MASK                          (0x1U << UART_MCR_SIR_MODE_EN_SHIFT)                         /* 0x00000040 */
/* LSR */
#define UART_LSR_OFFSET                                    (0x14U)
#define UART_LSR                                           (0x0U)
#define UART_LSR_DATA_READY_SHIFT                          (0U)
#define UART_LSR_DATA_READY_MASK                           (0x1U << UART_LSR_DATA_READY_SHIFT)                          /* 0x00000001 */
#define UART_LSR_OVERRUN_ERROR_SHIFT                       (1U)
#define UART_LSR_OVERRUN_ERROR_MASK                        (0x1U << UART_LSR_OVERRUN_ERROR_SHIFT)                       /* 0x00000002 */
#define UART_LSR_PARITY_EROR_SHIFT                         (2U)
#define UART_LSR_PARITY_EROR_MASK                          (0x1U << UART_LSR_PARITY_EROR_SHIFT)                         /* 0x00000004 */
#define UART_LSR_FRAMING_ERROR_SHIFT                       (3U)
#define UART_LSR_FRAMING_ERROR_MASK                        (0x1U << UART_LSR_FRAMING_ERROR_SHIFT)                       /* 0x00000008 */
#define UART_LSR_BREAK_INT_SHIFT                           (4U)
#define UART_LSR_BREAK_INT_MASK                            (0x1U << UART_LSR_BREAK_INT_SHIFT)                           /* 0x00000010 */
#define UART_LSR_TRANS_HOLD_REG_EMPTY_SHIFT                (5U)
#define UART_LSR_TRANS_HOLD_REG_EMPTY_MASK                 (0x1U << UART_LSR_TRANS_HOLD_REG_EMPTY_SHIFT)                /* 0x00000020 */
#define UART_LSR_TRANS_EMPTY_SHIFT                         (6U)
#define UART_LSR_TRANS_EMPTY_MASK                          (0x1U << UART_LSR_TRANS_EMPTY_SHIFT)                         /* 0x00000040 */
#define UART_LSR_RECEIVER_FIFO_ERROR_SHIFT                 (7U)
#define UART_LSR_RECEIVER_FIFO_ERROR_MASK                  (0x1U << UART_LSR_RECEIVER_FIFO_ERROR_SHIFT)                 /* 0x00000080 */
/* MSR */
#define UART_MSR_OFFSET                                    (0x18U)
#define UART_MSR                                           (0x0U)
#define UART_MSR_DELTA_CLEAR_TO_SEND_SHIFT                 (0U)
#define UART_MSR_DELTA_CLEAR_TO_SEND_MASK                  (0x1U << UART_MSR_DELTA_CLEAR_TO_SEND_SHIFT)                 /* 0x00000001 */
#define UART_MSR_DELTA_DATA_SET_READY_SHIFT                (1U)
#define UART_MSR_DELTA_DATA_SET_READY_MASK                 (0x1U << UART_MSR_DELTA_DATA_SET_READY_SHIFT)                /* 0x00000002 */
#define UART_MSR_TRAILING_EDGE_RING_INDICATOR_SHIFT        (2U)
#define UART_MSR_TRAILING_EDGE_RING_INDICATOR_MASK         (0x1U << UART_MSR_TRAILING_EDGE_RING_INDICATOR_SHIFT)        /* 0x00000004 */
#define UART_MSR_DELTA_DATA_CARRIER_DETECT_SHIFT           (3U)
#define UART_MSR_DELTA_DATA_CARRIER_DETECT_MASK            (0x1U << UART_MSR_DELTA_DATA_CARRIER_DETECT_SHIFT)           /* 0x00000008 */
#define UART_MSR_CLEAR_TO_SEND_SHIFT                       (4U)
#define UART_MSR_CLEAR_TO_SEND_MASK                        (0x1U << UART_MSR_CLEAR_TO_SEND_SHIFT)                       /* 0x00000010 */
#define UART_MSR_DATA_SET_READY_SHIFT                      (5U)
#define UART_MSR_DATA_SET_READY_MASK                       (0x1U << UART_MSR_DATA_SET_READY_SHIFT)                      /* 0x00000020 */
#define UART_MSR_RING_INDICATOR_SHIFT                      (6U)
#define UART_MSR_RING_INDICATOR_MASK                       (0x1U << UART_MSR_RING_INDICATOR_SHIFT)                      /* 0x00000040 */
#define UART_MSR_DATA_CARRIOR_DETECT_SHIFT                 (7U)
#define UART_MSR_DATA_CARRIOR_DETECT_MASK                  (0x1U << UART_MSR_DATA_CARRIOR_DETECT_SHIFT)                 /* 0x00000080 */
/* SCR */
#define UART_SCR_OFFSET                                    (0x1CU)
#define UART_SCR_TEMP_STORE_SPACE_SHIFT                    (0U)
#define UART_SCR_TEMP_STORE_SPACE_MASK                     (0xFFU << UART_SCR_TEMP_STORE_SPACE_SHIFT)                   /* 0x000000FF */
/* SRBR */
#define UART_SRBR_OFFSET                                   (0x30U)
#define UART_SRBR                                          (0x0U)
#define UART_SRBR_SHADOW_RBR_SHIFT                         (0U)
#define UART_SRBR_SHADOW_RBR_MASK                          (0xFFU << UART_SRBR_SHADOW_RBR_SHIFT)                        /* 0x000000FF */
/* STHR */
#define UART_STHR_OFFSET                                   (0x30U)
#define UART_STHR                                          (0x0U)
#define UART_STHR_SHADOW_THR_SHIFT                         (0U)
#define UART_STHR_SHADOW_THR_MASK                          (0xFFU << UART_STHR_SHADOW_THR_SHIFT)                        /* 0x000000FF */
/* FAR */
#define UART_FAR_OFFSET                                    (0x70U)
#define UART_FAR_FIFO_ACCESS_TEST_EN_SHIFT                 (0U)
#define UART_FAR_FIFO_ACCESS_TEST_EN_MASK                  (0x1U << UART_FAR_FIFO_ACCESS_TEST_EN_SHIFT)                 /* 0x00000001 */
/* TFR */
#define UART_TFR_OFFSET                                    (0x74U)
#define UART_TFR                                           (0x0U)
#define UART_TFR_TRANS_FIFO_READ_SHIFT                     (0U)
#define UART_TFR_TRANS_FIFO_READ_MASK                      (0xFFU << UART_TFR_TRANS_FIFO_READ_SHIFT)                    /* 0x000000FF */
/* RFW */
#define UART_RFW_OFFSET                                    (0x78U)
#define UART_RFW_RECEIVE_FIFO_WRITE_SHIFT                  (0U)
#define UART_RFW_RECEIVE_FIFO_WRITE_MASK                   (0xFFU << UART_RFW_RECEIVE_FIFO_WRITE_SHIFT)                 /* 0x000000FF */
#define UART_RFW_RECEIVE_FIFO_PARITY_ERROR_SHIFT           (8U)
#define UART_RFW_RECEIVE_FIFO_PARITY_ERROR_MASK            (0x1U << UART_RFW_RECEIVE_FIFO_PARITY_ERROR_SHIFT)           /* 0x00000100 */
#define UART_RFW_RECEIVE_FIFO_FRAMING_ERROR_SHIFT          (9U)
#define UART_RFW_RECEIVE_FIFO_FRAMING_ERROR_MASK           (0x1U << UART_RFW_RECEIVE_FIFO_FRAMING_ERROR_SHIFT)          /* 0x00000200 */
/* USR */
#define UART_USR_OFFSET                                    (0x7CU)
#define UART_USR                                           (0x0U)
#define UART_USR_UART_BUSY_SHIFT                           (0U)
#define UART_USR_UART_BUSY_MASK                            (0x1U << UART_USR_UART_BUSY_SHIFT)                           /* 0x00000001 */
#define UART_USR_TRANS_FIFO_NOT_FULL_SHIFT                 (1U)
#define UART_USR_TRANS_FIFO_NOT_FULL_MASK                  (0x1U << UART_USR_TRANS_FIFO_NOT_FULL_SHIFT)                 /* 0x00000002 */
#define UART_USR_TRASN_FIFO_EMPTY_SHIFT                    (2U)
#define UART_USR_TRASN_FIFO_EMPTY_MASK                     (0x1U << UART_USR_TRASN_FIFO_EMPTY_SHIFT)                    /* 0x00000004 */
#define UART_USR_RECEIVE_FIFO_NOT_EMPTY_SHIFT              (3U)
#define UART_USR_RECEIVE_FIFO_NOT_EMPTY_MASK               (0x1U << UART_USR_RECEIVE_FIFO_NOT_EMPTY_SHIFT)              /* 0x00000008 */
#define UART_USR_RECEIVE_FIFO_FULL_SHIFT                   (4U)
#define UART_USR_RECEIVE_FIFO_FULL_MASK                    (0x1U << UART_USR_RECEIVE_FIFO_FULL_SHIFT)                   /* 0x00000010 */
/* TFL */
#define UART_TFL_OFFSET                                    (0x80U)
#define UART_TFL_TRANS_FIFO_LEVEL_SHIFT                    (0U)
#define UART_TFL_TRANS_FIFO_LEVEL_MASK                     (0x1FU << UART_TFL_TRANS_FIFO_LEVEL_SHIFT)                   /* 0x0000001F */
/* RFL */
#define UART_RFL_OFFSET                                    (0x84U)
#define UART_RFL                                           (0x0U)
#define UART_RFL_RECEIVE_FIFO_LEVEL_SHIFT                  (0U)
#define UART_RFL_RECEIVE_FIFO_LEVEL_MASK                   (0x1FU << UART_RFL_RECEIVE_FIFO_LEVEL_SHIFT)                 /* 0x0000001F */
/* SRR */
#define UART_SRR_OFFSET                                    (0x88U)
#define UART_SRR_UART_RESET_SHIFT                          (0U)
#define UART_SRR_UART_RESET_MASK                           (0x1U << UART_SRR_UART_RESET_SHIFT)                          /* 0x00000001 */
#define UART_SRR_RCVR_FIFO_RESET_SHIFT                     (1U)
#define UART_SRR_RCVR_FIFO_RESET_MASK                      (0x1U << UART_SRR_RCVR_FIFO_RESET_SHIFT)                     /* 0x00000002 */
#define UART_SRR_XMIT_FIFO_RESET_SHIFT                     (2U)
#define UART_SRR_XMIT_FIFO_RESET_MASK                      (0x1U << UART_SRR_XMIT_FIFO_RESET_SHIFT)                     /* 0x00000004 */
/* SRTS */
#define UART_SRTS_OFFSET                                   (0x8CU)
#define UART_SRTS_SHADOW_REQ_TO_SEND_SHIFT                 (0U)
#define UART_SRTS_SHADOW_REQ_TO_SEND_MASK                  (0x1U << UART_SRTS_SHADOW_REQ_TO_SEND_SHIFT)                 /* 0x00000001 */
/* SBCR */
#define UART_SBCR_OFFSET                                   (0x90U)
#define UART_SBCR_SHADOW_BREAK_CTRL_SHIFT                  (0U)
#define UART_SBCR_SHADOW_BREAK_CTRL_MASK                   (0x1U << UART_SBCR_SHADOW_BREAK_CTRL_SHIFT)                  /* 0x00000001 */
/* SDMAM */
#define UART_SDMAM_OFFSET                                  (0x94U)
#define UART_SDMAM_SHADOW_DMA_MODE_SHIFT                   (0U)
#define UART_SDMAM_SHADOW_DMA_MODE_MASK                    (0x1U << UART_SDMAM_SHADOW_DMA_MODE_SHIFT)                   /* 0x00000001 */
/* SFE */
#define UART_SFE_OFFSET                                    (0x98U)
#define UART_SFE_SHADOW_FIFO_EN_SHIFT                      (0U)
#define UART_SFE_SHADOW_FIFO_EN_MASK                       (0x1U << UART_SFE_SHADOW_FIFO_EN_SHIFT)                      /* 0x00000001 */
/* SRT */
#define UART_SRT_OFFSET                                    (0x9CU)
#define UART_SRT_SHADOW_RCVR_TRIGGER_SHIFT                 (0U)
#define UART_SRT_SHADOW_RCVR_TRIGGER_MASK                  (0x1U << UART_SRT_SHADOW_RCVR_TRIGGER_SHIFT)                 /* 0x00000001 */
/* STET */
#define UART_STET_OFFSET                                   (0xA0U)
#define UART_STET_SHADOW_TX_EMPTY_TRIGGER_SHIFT            (0U)
#define UART_STET_SHADOW_TX_EMPTY_TRIGGER_MASK             (0x1U << UART_STET_SHADOW_TX_EMPTY_TRIGGER_SHIFT)            /* 0x00000001 */
/* HTX */
#define UART_HTX_OFFSET                                    (0xA4U)
#define UART_HTX_HALT_TX_EN_SHIFT                          (0U)
#define UART_HTX_HALT_TX_EN_MASK                           (0x1U << UART_HTX_HALT_TX_EN_SHIFT)                          /* 0x00000001 */
/* DMASA */
#define UART_DMASA_OFFSET                                  (0xA8U)
#define UART_DMASA_DMA_SOFTWARE_ACK_SHIFT                  (0U)
#define UART_DMASA_DMA_SOFTWARE_ACK_MASK                   (0x1U << UART_DMASA_DMA_SOFTWARE_ACK_SHIFT)                  /* 0x00000001 */
/* CPR */
#define UART_CPR_OFFSET                                    (0xF4U)
#define UART_CPR                                           (0x0U)
#define UART_CPR_APB_DATA_WIDTH_SHIFT                      (0U)
#define UART_CPR_APB_DATA_WIDTH_MASK                       (0x3U << UART_CPR_APB_DATA_WIDTH_SHIFT)                      /* 0x00000003 */
#define UART_CPR_AFCE_MODE_SHIFT                           (4U)
#define UART_CPR_AFCE_MODE_MASK                            (0x1U << UART_CPR_AFCE_MODE_SHIFT)                           /* 0x00000010 */
#define UART_CPR_THRE_MODE_SHIFT                           (5U)
#define UART_CPR_THRE_MODE_MASK                            (0x1U << UART_CPR_THRE_MODE_SHIFT)                           /* 0x00000020 */
#define UART_CPR_SIR_MODE_SHIFT                            (6U)
#define UART_CPR_SIR_MODE_MASK                             (0x1U << UART_CPR_SIR_MODE_SHIFT)                            /* 0x00000040 */
#define UART_CPR_SIR_LP_MODE_SHIFT                         (7U)
#define UART_CPR_SIR_LP_MODE_MASK                          (0x1U << UART_CPR_SIR_LP_MODE_SHIFT)                         /* 0x00000080 */
#define UART_CPR_NEW_FEAT_SHIFT                            (8U)
#define UART_CPR_NEW_FEAT_MASK                             (0x1U << UART_CPR_NEW_FEAT_SHIFT)                            /* 0x00000100 */
#define UART_CPR_FIFO_ACCESS_SHIFT                         (9U)
#define UART_CPR_FIFO_ACCESS_MASK                          (0x1U << UART_CPR_FIFO_ACCESS_SHIFT)                         /* 0x00000200 */
#define UART_CPR_FIFO_STAT_SHIFT                           (10U)
#define UART_CPR_FIFO_STAT_MASK                            (0x1U << UART_CPR_FIFO_STAT_SHIFT)                           /* 0x00000400 */
#define UART_CPR_SHADOW_SHIFT                              (11U)
#define UART_CPR_SHADOW_MASK                               (0x1U << UART_CPR_SHADOW_SHIFT)                              /* 0x00000800 */
#define UART_CPR_UART_ADD_ENCODED_PARAMS_SHIFT             (12U)
#define UART_CPR_UART_ADD_ENCODED_PARAMS_MASK              (0x1U << UART_CPR_UART_ADD_ENCODED_PARAMS_SHIFT)             /* 0x00001000 */
#define UART_CPR_DMA_EXTRA_SHIFT                           (13U)
#define UART_CPR_DMA_EXTRA_MASK                            (0x1U << UART_CPR_DMA_EXTRA_SHIFT)                           /* 0x00002000 */
#define UART_CPR_FIFO_MODE_SHIFT                           (16U)
#define UART_CPR_FIFO_MODE_MASK                            (0xFFU << UART_CPR_FIFO_MODE_SHIFT)                          /* 0x00FF0000 */
/* UCV */
#define UART_UCV_OFFSET                                    (0xF8U)
#define UART_UCV                                           (0x330372AU)
#define UART_UCV_VER_SHIFT                                 (0U)
#define UART_UCV_VER_MASK                                  (0xFFFFFFFFU << UART_UCV_VER_SHIFT)                          /* 0xFFFFFFFF */
/* CTR */
#define UART_CTR_OFFSET                                    (0xFCU)
#define UART_CTR                                           (0x44570110U)
#define UART_CTR_PERIPHERAL_ID_SHIFT                       (0U)
#define UART_CTR_PERIPHERAL_ID_MASK                        (0xFFFFFFFFU << UART_CTR_PERIPHERAL_ID_SHIFT)                /* 0xFFFFFFFF */
/******************************************PWM*******************************************/
/* PWM0_CNT */
#define PWM_PWM0_CNT_OFFSET                                (0x0U)
#define PWM_PWM0_CNT                                       (0x0U)
#define PWM_PWM0_CNT_CNT_SHIFT                             (0U)
#define PWM_PWM0_CNT_CNT_MASK                              (0xFFFFFFFFU << PWM_PWM0_CNT_CNT_SHIFT)                      /* 0xFFFFFFFF */
/* PWM0_PERIOD_HPR */
#define PWM_PWM0_PERIOD_HPR_OFFSET                         (0x4U)
#define PWM_PWM0_PERIOD_HPR_PERIOD_HPR_SHIFT               (0U)
#define PWM_PWM0_PERIOD_HPR_PERIOD_HPR_MASK                (0xFFFFFFFFU << PWM_PWM0_PERIOD_HPR_PERIOD_HPR_SHIFT)        /* 0xFFFFFFFF */
/* PWM0_DUTY_LPR */
#define PWM_PWM0_DUTY_LPR_OFFSET                           (0x8U)
#define PWM_PWM0_DUTY_LPR_DUTY_LPR_SHIFT                   (0U)
#define PWM_PWM0_DUTY_LPR_DUTY_LPR_MASK                    (0xFFFFFFFFU << PWM_PWM0_DUTY_LPR_DUTY_LPR_SHIFT)            /* 0xFFFFFFFF */
/* PWM0_CTRL */
#define PWM_PWM0_CTRL_OFFSET                               (0xCU)
#define PWM_PWM0_CTRL_PWM_EN_SHIFT                         (0U)
#define PWM_PWM0_CTRL_PWM_EN_MASK                          (0x1U << PWM_PWM0_CTRL_PWM_EN_SHIFT)                         /* 0x00000001 */
#define PWM_PWM0_CTRL_PWM_MODE_SHIFT                       (1U)
#define PWM_PWM0_CTRL_PWM_MODE_MASK                        (0x3U << PWM_PWM0_CTRL_PWM_MODE_SHIFT)                       /* 0x00000006 */
#define PWM_PWM0_CTRL_DUTY_POL_SHIFT                       (3U)
#define PWM_PWM0_CTRL_DUTY_POL_MASK                        (0x1U << PWM_PWM0_CTRL_DUTY_POL_SHIFT)                       /* 0x00000008 */
#define PWM_PWM0_CTRL_INACTIVE_POL_SHIFT                   (4U)
#define PWM_PWM0_CTRL_INACTIVE_POL_MASK                    (0x1U << PWM_PWM0_CTRL_INACTIVE_POL_SHIFT)                   /* 0x00000010 */
#define PWM_PWM0_CTRL_OUTPUT_MODE_SHIFT                    (5U)
#define PWM_PWM0_CTRL_OUTPUT_MODE_MASK                     (0x1U << PWM_PWM0_CTRL_OUTPUT_MODE_SHIFT)                    /* 0x00000020 */
#define PWM_PWM0_CTRL_CONLOCK_SHIFT                        (6U)
#define PWM_PWM0_CTRL_CONLOCK_MASK                         (0x1U << PWM_PWM0_CTRL_CONLOCK_SHIFT)                        /* 0x00000040 */
#define PWM_PWM0_CTRL_CH_CNT_EN_SHIFT                      (7U)
#define PWM_PWM0_CTRL_CH_CNT_EN_MASK                       (0x1U << PWM_PWM0_CTRL_CH_CNT_EN_SHIFT)                      /* 0x00000080 */
#define PWM_PWM0_CTRL_FORCE_CLK_EN_SHIFT                   (8U)
#define PWM_PWM0_CTRL_FORCE_CLK_EN_MASK                    (0x1U << PWM_PWM0_CTRL_FORCE_CLK_EN_SHIFT)                   /* 0x00000100 */
#define PWM_PWM0_CTRL_CLK_SEL_SHIFT                        (9U)
#define PWM_PWM0_CTRL_CLK_SEL_MASK                         (0x1U << PWM_PWM0_CTRL_CLK_SEL_SHIFT)                        /* 0x00000200 */
#define PWM_PWM0_CTRL_PRESCALE_SHIFT                       (12U)
#define PWM_PWM0_CTRL_PRESCALE_MASK                        (0x7U << PWM_PWM0_CTRL_PRESCALE_SHIFT)                       /* 0x00007000 */
#define PWM_PWM0_CTRL_SCALE_SHIFT                          (16U)
#define PWM_PWM0_CTRL_SCALE_MASK                           (0xFFU << PWM_PWM0_CTRL_SCALE_SHIFT)                         /* 0x00FF0000 */
#define PWM_PWM0_CTRL_RPT_SHIFT                            (24U)
#define PWM_PWM0_CTRL_RPT_MASK                             (0xFFU << PWM_PWM0_CTRL_RPT_SHIFT)                           /* 0xFF000000 */
/* PWM1_CNT */
#define PWM_PWM1_CNT_OFFSET                                (0x10U)
#define PWM_PWM1_CNT                                       (0x0U)
#define PWM_PWM1_CNT_CNT_SHIFT                             (0U)
#define PWM_PWM1_CNT_CNT_MASK                              (0xFFFFFFFFU << PWM_PWM1_CNT_CNT_SHIFT)                      /* 0xFFFFFFFF */
/* PWM1_PERIOD_HPR */
#define PWM_PWM1_PERIOD_HPR_OFFSET                         (0x14U)
#define PWM_PWM1_PERIOD_HPR_PERIOD_HPR_SHIFT               (0U)
#define PWM_PWM1_PERIOD_HPR_PERIOD_HPR_MASK                (0xFFFFFFFFU << PWM_PWM1_PERIOD_HPR_PERIOD_HPR_SHIFT)        /* 0xFFFFFFFF */
/* PWM1_DUTY_LPR */
#define PWM_PWM1_DUTY_LPR_OFFSET                           (0x18U)
#define PWM_PWM1_DUTY_LPR_DUTY_LPR_SHIFT                   (0U)
#define PWM_PWM1_DUTY_LPR_DUTY_LPR_MASK                    (0xFFFFFFFFU << PWM_PWM1_DUTY_LPR_DUTY_LPR_SHIFT)            /* 0xFFFFFFFF */
/* PWM1_CTRL */
#define PWM_PWM1_CTRL_OFFSET                               (0x1CU)
#define PWM_PWM1_CTRL_PWM_EN_SHIFT                         (0U)
#define PWM_PWM1_CTRL_PWM_EN_MASK                          (0x1U << PWM_PWM1_CTRL_PWM_EN_SHIFT)                         /* 0x00000001 */
#define PWM_PWM1_CTRL_PWM_MODE_SHIFT                       (1U)
#define PWM_PWM1_CTRL_PWM_MODE_MASK                        (0x3U << PWM_PWM1_CTRL_PWM_MODE_SHIFT)                       /* 0x00000006 */
#define PWM_PWM1_CTRL_DUTY_POL_SHIFT                       (3U)
#define PWM_PWM1_CTRL_DUTY_POL_MASK                        (0x1U << PWM_PWM1_CTRL_DUTY_POL_SHIFT)                       /* 0x00000008 */
#define PWM_PWM1_CTRL_INACTIVE_POL_SHIFT                   (4U)
#define PWM_PWM1_CTRL_INACTIVE_POL_MASK                    (0x1U << PWM_PWM1_CTRL_INACTIVE_POL_SHIFT)                   /* 0x00000010 */
#define PWM_PWM1_CTRL_OUTPUT_MODE_SHIFT                    (5U)
#define PWM_PWM1_CTRL_OUTPUT_MODE_MASK                     (0x1U << PWM_PWM1_CTRL_OUTPUT_MODE_SHIFT)                    /* 0x00000020 */
#define PWM_PWM1_CTRL_CONLOCK_SHIFT                        (6U)
#define PWM_PWM1_CTRL_CONLOCK_MASK                         (0x1U << PWM_PWM1_CTRL_CONLOCK_SHIFT)                        /* 0x00000040 */
#define PWM_PWM1_CTRL_CH_CNT_EN_SHIFT                      (7U)
#define PWM_PWM1_CTRL_CH_CNT_EN_MASK                       (0x1U << PWM_PWM1_CTRL_CH_CNT_EN_SHIFT)                      /* 0x00000080 */
#define PWM_PWM1_CTRL_FORCE_CLK_EN_SHIFT                   (8U)
#define PWM_PWM1_CTRL_FORCE_CLK_EN_MASK                    (0x1U << PWM_PWM1_CTRL_FORCE_CLK_EN_SHIFT)                   /* 0x00000100 */
#define PWM_PWM1_CTRL_CLK_SEL_SHIFT                        (9U)
#define PWM_PWM1_CTRL_CLK_SEL_MASK                         (0x1U << PWM_PWM1_CTRL_CLK_SEL_SHIFT)                        /* 0x00000200 */
#define PWM_PWM1_CTRL_PRESCALE_SHIFT                       (12U)
#define PWM_PWM1_CTRL_PRESCALE_MASK                        (0x7U << PWM_PWM1_CTRL_PRESCALE_SHIFT)                       /* 0x00007000 */
#define PWM_PWM1_CTRL_SCALE_SHIFT                          (16U)
#define PWM_PWM1_CTRL_SCALE_MASK                           (0xFFU << PWM_PWM1_CTRL_SCALE_SHIFT)                         /* 0x00FF0000 */
#define PWM_PWM1_CTRL_RPT_SHIFT                            (24U)
#define PWM_PWM1_CTRL_RPT_MASK                             (0xFFU << PWM_PWM1_CTRL_RPT_SHIFT)                           /* 0xFF000000 */
/* PWM2_CNT */
#define PWM_PWM2_CNT_OFFSET                                (0x20U)
#define PWM_PWM2_CNT                                       (0x0U)
#define PWM_PWM2_CNT_CNT_SHIFT                             (0U)
#define PWM_PWM2_CNT_CNT_MASK                              (0xFFFFFFFFU << PWM_PWM2_CNT_CNT_SHIFT)                      /* 0xFFFFFFFF */
/* PWM2_PERIOD_HPR */
#define PWM_PWM2_PERIOD_HPR_OFFSET                         (0x24U)
#define PWM_PWM2_PERIOD_HPR_PERIOD_HPR_SHIFT               (0U)
#define PWM_PWM2_PERIOD_HPR_PERIOD_HPR_MASK                (0xFFFFFFFFU << PWM_PWM2_PERIOD_HPR_PERIOD_HPR_SHIFT)        /* 0xFFFFFFFF */
/* PWM2_DUTY_LPR */
#define PWM_PWM2_DUTY_LPR_OFFSET                           (0x28U)
#define PWM_PWM2_DUTY_LPR_DUTY_LPR_SHIFT                   (0U)
#define PWM_PWM2_DUTY_LPR_DUTY_LPR_MASK                    (0xFFFFFFFFU << PWM_PWM2_DUTY_LPR_DUTY_LPR_SHIFT)            /* 0xFFFFFFFF */
/* PWM2_CTRL */
#define PWM_PWM2_CTRL_OFFSET                               (0x2CU)
#define PWM_PWM2_CTRL_PWM_EN_SHIFT                         (0U)
#define PWM_PWM2_CTRL_PWM_EN_MASK                          (0x1U << PWM_PWM2_CTRL_PWM_EN_SHIFT)                         /* 0x00000001 */
#define PWM_PWM2_CTRL_PWM_MODE_SHIFT                       (1U)
#define PWM_PWM2_CTRL_PWM_MODE_MASK                        (0x3U << PWM_PWM2_CTRL_PWM_MODE_SHIFT)                       /* 0x00000006 */
#define PWM_PWM2_CTRL_DUTY_POL_SHIFT                       (3U)
#define PWM_PWM2_CTRL_DUTY_POL_MASK                        (0x1U << PWM_PWM2_CTRL_DUTY_POL_SHIFT)                       /* 0x00000008 */
#define PWM_PWM2_CTRL_INACTIVE_POL_SHIFT                   (4U)
#define PWM_PWM2_CTRL_INACTIVE_POL_MASK                    (0x1U << PWM_PWM2_CTRL_INACTIVE_POL_SHIFT)                   /* 0x00000010 */
#define PWM_PWM2_CTRL_OUTPUT_MODE_SHIFT                    (5U)
#define PWM_PWM2_CTRL_OUTPUT_MODE_MASK                     (0x1U << PWM_PWM2_CTRL_OUTPUT_MODE_SHIFT)                    /* 0x00000020 */
#define PWM_PWM2_CTRL_CONLOCK_SHIFT                        (6U)
#define PWM_PWM2_CTRL_CONLOCK_MASK                         (0x1U << PWM_PWM2_CTRL_CONLOCK_SHIFT)                        /* 0x00000040 */
#define PWM_PWM2_CTRL_CH_CNT_EN_SHIFT                      (7U)
#define PWM_PWM2_CTRL_CH_CNT_EN_MASK                       (0x1U << PWM_PWM2_CTRL_CH_CNT_EN_SHIFT)                      /* 0x00000080 */
#define PWM_PWM2_CTRL_FORCE_CLK_EN_SHIFT                   (8U)
#define PWM_PWM2_CTRL_FORCE_CLK_EN_MASK                    (0x1U << PWM_PWM2_CTRL_FORCE_CLK_EN_SHIFT)                   /* 0x00000100 */
#define PWM_PWM2_CTRL_CLK_SEL_SHIFT                        (9U)
#define PWM_PWM2_CTRL_CLK_SEL_MASK                         (0x1U << PWM_PWM2_CTRL_CLK_SEL_SHIFT)                        /* 0x00000200 */
#define PWM_PWM2_CTRL_PRESCALE_SHIFT                       (12U)
#define PWM_PWM2_CTRL_PRESCALE_MASK                        (0x7U << PWM_PWM2_CTRL_PRESCALE_SHIFT)                       /* 0x00007000 */
#define PWM_PWM2_CTRL_SCALE_SHIFT                          (16U)
#define PWM_PWM2_CTRL_SCALE_MASK                           (0xFFU << PWM_PWM2_CTRL_SCALE_SHIFT)                         /* 0x00FF0000 */
#define PWM_PWM2_CTRL_RPT_SHIFT                            (24U)
#define PWM_PWM2_CTRL_RPT_MASK                             (0xFFU << PWM_PWM2_CTRL_RPT_SHIFT)                           /* 0xFF000000 */
/* PWM3_CNT */
#define PWM_PWM3_CNT_OFFSET                                (0x30U)
#define PWM_PWM3_CNT                                       (0x0U)
#define PWM_PWM3_CNT_CNT_SHIFT                             (0U)
#define PWM_PWM3_CNT_CNT_MASK                              (0xFFFFFFFFU << PWM_PWM3_CNT_CNT_SHIFT)                      /* 0xFFFFFFFF */
/* PWM3_PERIOD_HPR */
#define PWM_PWM3_PERIOD_HPR_OFFSET                         (0x34U)
#define PWM_PWM3_PERIOD_HPR_PERIOD_HPR_SHIFT               (0U)
#define PWM_PWM3_PERIOD_HPR_PERIOD_HPR_MASK                (0xFFFFFFFFU << PWM_PWM3_PERIOD_HPR_PERIOD_HPR_SHIFT)        /* 0xFFFFFFFF */
/* PWM3_DUTY_LPR */
#define PWM_PWM3_DUTY_LPR_OFFSET                           (0x38U)
#define PWM_PWM3_DUTY_LPR_DUTY_LPR_SHIFT                   (0U)
#define PWM_PWM3_DUTY_LPR_DUTY_LPR_MASK                    (0xFFFFFFFFU << PWM_PWM3_DUTY_LPR_DUTY_LPR_SHIFT)            /* 0xFFFFFFFF */
/* PWM3_CTRL */
#define PWM_PWM3_CTRL_OFFSET                               (0x3CU)
#define PWM_PWM3_CTRL_PWM_EN_SHIFT                         (0U)
#define PWM_PWM3_CTRL_PWM_EN_MASK                          (0x1U << PWM_PWM3_CTRL_PWM_EN_SHIFT)                         /* 0x00000001 */
#define PWM_PWM3_CTRL_PWM_MODE_SHIFT                       (1U)
#define PWM_PWM3_CTRL_PWM_MODE_MASK                        (0x3U << PWM_PWM3_CTRL_PWM_MODE_SHIFT)                       /* 0x00000006 */
#define PWM_PWM3_CTRL_DUTY_POL_SHIFT                       (3U)
#define PWM_PWM3_CTRL_DUTY_POL_MASK                        (0x1U << PWM_PWM3_CTRL_DUTY_POL_SHIFT)                       /* 0x00000008 */
#define PWM_PWM3_CTRL_INACTIVE_POL_SHIFT                   (4U)
#define PWM_PWM3_CTRL_INACTIVE_POL_MASK                    (0x1U << PWM_PWM3_CTRL_INACTIVE_POL_SHIFT)                   /* 0x00000010 */
#define PWM_PWM3_CTRL_OUTPUT_MODE_SHIFT                    (5U)
#define PWM_PWM3_CTRL_OUTPUT_MODE_MASK                     (0x1U << PWM_PWM3_CTRL_OUTPUT_MODE_SHIFT)                    /* 0x00000020 */
#define PWM_PWM3_CTRL_CONLOCK_SHIFT                        (6U)
#define PWM_PWM3_CTRL_CONLOCK_MASK                         (0x1U << PWM_PWM3_CTRL_CONLOCK_SHIFT)                        /* 0x00000040 */
#define PWM_PWM3_CTRL_CH_CNT_EN_SHIFT                      (7U)
#define PWM_PWM3_CTRL_CH_CNT_EN_MASK                       (0x1U << PWM_PWM3_CTRL_CH_CNT_EN_SHIFT)                      /* 0x00000080 */
#define PWM_PWM3_CTRL_FORCE_CLK_EN_SHIFT                   (8U)
#define PWM_PWM3_CTRL_FORCE_CLK_EN_MASK                    (0x1U << PWM_PWM3_CTRL_FORCE_CLK_EN_SHIFT)                   /* 0x00000100 */
#define PWM_PWM3_CTRL_CLK_SEL_SHIFT                        (9U)
#define PWM_PWM3_CTRL_CLK_SEL_MASK                         (0x1U << PWM_PWM3_CTRL_CLK_SEL_SHIFT)                        /* 0x00000200 */
#define PWM_PWM3_CTRL_PRESCALE_SHIFT                       (12U)
#define PWM_PWM3_CTRL_PRESCALE_MASK                        (0x7U << PWM_PWM3_CTRL_PRESCALE_SHIFT)                       /* 0x00007000 */
#define PWM_PWM3_CTRL_SCALE_SHIFT                          (16U)
#define PWM_PWM3_CTRL_SCALE_MASK                           (0xFFU << PWM_PWM3_CTRL_SCALE_SHIFT)                         /* 0x00FF0000 */
#define PWM_PWM3_CTRL_RPT_SHIFT                            (24U)
#define PWM_PWM3_CTRL_RPT_MASK                             (0xFFU << PWM_PWM3_CTRL_RPT_SHIFT)                           /* 0xFF000000 */
/* INTSTS */
#define PWM_INTSTS_OFFSET                                  (0x40U)
#define PWM_INTSTS_CH0_INTSTS_SHIFT                        (0U)
#define PWM_INTSTS_CH0_INTSTS_MASK                         (0x1U << PWM_INTSTS_CH0_INTSTS_SHIFT)                        /* 0x00000001 */
#define PWM_INTSTS_CH1_INTSTS_SHIFT                        (1U)
#define PWM_INTSTS_CH1_INTSTS_MASK                         (0x1U << PWM_INTSTS_CH1_INTSTS_SHIFT)                        /* 0x00000002 */
#define PWM_INTSTS_CH2_INTSTS_SHIFT                        (2U)
#define PWM_INTSTS_CH2_INTSTS_MASK                         (0x1U << PWM_INTSTS_CH2_INTSTS_SHIFT)                        /* 0x00000004 */
#define PWM_INTSTS_CH3_INTSTS_SHIFT                        (3U)
#define PWM_INTSTS_CH3_INTSTS_MASK                         (0x1U << PWM_INTSTS_CH3_INTSTS_SHIFT)                        /* 0x00000008 */
#define PWM_INTSTS_CH0_PWR_INTSTS_SHIFT                    (4U)
#define PWM_INTSTS_CH0_PWR_INTSTS_MASK                     (0x1U << PWM_INTSTS_CH0_PWR_INTSTS_SHIFT)                    /* 0x00000010 */
#define PWM_INTSTS_CH1_PWR_INTSTS_SHIFT                    (5U)
#define PWM_INTSTS_CH1_PWR_INTSTS_MASK                     (0x1U << PWM_INTSTS_CH1_PWR_INTSTS_SHIFT)                    /* 0x00000020 */
#define PWM_INTSTS_CH2_PWR_INTSTS_SHIFT                    (6U)
#define PWM_INTSTS_CH2_PWR_INTSTS_MASK                     (0x1U << PWM_INTSTS_CH2_PWR_INTSTS_SHIFT)                    /* 0x00000040 */
#define PWM_INTSTS_CH3_PWR_INTSTS_SHIFT                    (7U)
#define PWM_INTSTS_CH3_PWR_INTSTS_MASK                     (0x1U << PWM_INTSTS_CH3_PWR_INTSTS_SHIFT)                    /* 0x00000080 */
#define PWM_INTSTS_CH0_POL_SHIFT                           (8U)
#define PWM_INTSTS_CH0_POL_MASK                            (0x1U << PWM_INTSTS_CH0_POL_SHIFT)                           /* 0x00000100 */
#define PWM_INTSTS_CH1_POL_SHIFT                           (9U)
#define PWM_INTSTS_CH1_POL_MASK                            (0x1U << PWM_INTSTS_CH1_POL_SHIFT)                           /* 0x00000200 */
#define PWM_INTSTS_CH2_POL_SHIFT                           (10U)
#define PWM_INTSTS_CH2_POL_MASK                            (0x1U << PWM_INTSTS_CH2_POL_SHIFT)                           /* 0x00000400 */
#define PWM_INTSTS_CH3_POL_SHIFT                           (11U)
#define PWM_INTSTS_CH3_POL_MASK                            (0x1U << PWM_INTSTS_CH3_POL_SHIFT)                           /* 0x00000800 */
/* INT_EN */
#define PWM_INT_EN_OFFSET                                  (0x44U)
#define PWM_INT_EN_CH0_INT_EN_SHIFT                        (0U)
#define PWM_INT_EN_CH0_INT_EN_MASK                         (0x1U << PWM_INT_EN_CH0_INT_EN_SHIFT)                        /* 0x00000001 */
#define PWM_INT_EN_CH1_INT_EN_SHIFT                        (1U)
#define PWM_INT_EN_CH1_INT_EN_MASK                         (0x1U << PWM_INT_EN_CH1_INT_EN_SHIFT)                        /* 0x00000002 */
#define PWM_INT_EN_CH2_INT_EN_SHIFT                        (2U)
#define PWM_INT_EN_CH2_INT_EN_MASK                         (0x1U << PWM_INT_EN_CH2_INT_EN_SHIFT)                        /* 0x00000004 */
#define PWM_INT_EN_CH3_INT_EN_SHIFT                        (3U)
#define PWM_INT_EN_CH3_INT_EN_MASK                         (0x1U << PWM_INT_EN_CH3_INT_EN_SHIFT)                        /* 0x00000008 */
#define PWM_INT_EN_CH0_PWR_INT_EN_SHIFT                    (4U)
#define PWM_INT_EN_CH0_PWR_INT_EN_MASK                     (0x1U << PWM_INT_EN_CH0_PWR_INT_EN_SHIFT)                    /* 0x00000010 */
#define PWM_INT_EN_CH1_PWR_INT_EN_SHIFT                    (5U)
#define PWM_INT_EN_CH1_PWR_INT_EN_MASK                     (0x1U << PWM_INT_EN_CH1_PWR_INT_EN_SHIFT)                    /* 0x00000020 */
#define PWM_INT_EN_CH2_PWR_INT_EN_SHIFT                    (6U)
#define PWM_INT_EN_CH2_PWR_INT_EN_MASK                     (0x1U << PWM_INT_EN_CH2_PWR_INT_EN_SHIFT)                    /* 0x00000040 */
#define PWM_INT_EN_CH3_PWR_INT_EN_SHIFT                    (7U)
#define PWM_INT_EN_CH3_PWR_INT_EN_MASK                     (0x1U << PWM_INT_EN_CH3_PWR_INT_EN_SHIFT)                    /* 0x00000080 */
/* FIFO_CTRL */
#define PWM_FIFO_CTRL_OFFSET                               (0x50U)
#define PWM_FIFO_CTRL_FIFO_MODE_SEL_SHIFT                  (0U)
#define PWM_FIFO_CTRL_FIFO_MODE_SEL_MASK                   (0x1U << PWM_FIFO_CTRL_FIFO_MODE_SEL_SHIFT)                  /* 0x00000001 */
#define PWM_FIFO_CTRL_FULL_INT_EN_SHIFT                    (1U)
#define PWM_FIFO_CTRL_FULL_INT_EN_MASK                     (0x1U << PWM_FIFO_CTRL_FULL_INT_EN_SHIFT)                    /* 0x00000002 */
#define PWM_FIFO_CTRL_OVERFLOW_INT_EN_SHIFT                (2U)
#define PWM_FIFO_CTRL_OVERFLOW_INT_EN_MASK                 (0x1U << PWM_FIFO_CTRL_OVERFLOW_INT_EN_SHIFT)                /* 0x00000004 */
#define PWM_FIFO_CTRL_WATERMARK_INT_EN_SHIFT               (3U)
#define PWM_FIFO_CTRL_WATERMARK_INT_EN_MASK                (0x1U << PWM_FIFO_CTRL_WATERMARK_INT_EN_SHIFT)               /* 0x00000008 */
#define PWM_FIFO_CTRL_ALMOST_FULL_WATERMARK_SHIFT          (4U)
#define PWM_FIFO_CTRL_ALMOST_FULL_WATERMARK_MASK           (0x7U << PWM_FIFO_CTRL_ALMOST_FULL_WATERMARK_SHIFT)          /* 0x00000070 */
#define PWM_FIFO_CTRL_DMA_MODE_EN_SHIFT                    (8U)
#define PWM_FIFO_CTRL_DMA_MODE_EN_MASK                     (0x1U << PWM_FIFO_CTRL_DMA_MODE_EN_SHIFT)                    /* 0x00000100 */
#define PWM_FIFO_CTRL_TIMEOUT_EN_SHIFT                     (9U)
#define PWM_FIFO_CTRL_TIMEOUT_EN_MASK                      (0x1U << PWM_FIFO_CTRL_TIMEOUT_EN_SHIFT)                     /* 0x00000200 */
#define PWM_FIFO_CTRL_DMA_CH_SEL_EN_SHIFT                  (10U)
#define PWM_FIFO_CTRL_DMA_CH_SEL_EN_MASK                   (0x1U << PWM_FIFO_CTRL_DMA_CH_SEL_EN_SHIFT)                  /* 0x00000400 */
#define PWM_FIFO_CTRL_DMA_CH_SEL_SHIFT                     (12U)
#define PWM_FIFO_CTRL_DMA_CH_SEL_MASK                      (0x3U << PWM_FIFO_CTRL_DMA_CH_SEL_SHIFT)                     /* 0x00003000 */
/* FIFO_INTSTS */
#define PWM_FIFO_INTSTS_OFFSET                             (0x54U)
#define PWM_FIFO_INTSTS_FIFO_FULL_INTSTS_SHIFT             (0U)
#define PWM_FIFO_INTSTS_FIFO_FULL_INTSTS_MASK              (0x1U << PWM_FIFO_INTSTS_FIFO_FULL_INTSTS_SHIFT)             /* 0x00000001 */
#define PWM_FIFO_INTSTS_FIFO_OVERFLOW_INTSTS_SHIFT         (1U)
#define PWM_FIFO_INTSTS_FIFO_OVERFLOW_INTSTS_MASK          (0x1U << PWM_FIFO_INTSTS_FIFO_OVERFLOW_INTSTS_SHIFT)         /* 0x00000002 */
#define PWM_FIFO_INTSTS_FIFO_WATERMARK_FULL_INTSTS_SHIFT   (2U)
#define PWM_FIFO_INTSTS_FIFO_WATERMARK_FULL_INTSTS_MASK    (0x1U << PWM_FIFO_INTSTS_FIFO_WATERMARK_FULL_INTSTS_SHIFT)   /* 0x00000004 */
#define PWM_FIFO_INTSTS_TIMIEOUT_INTSTS_SHIFT              (3U)
#define PWM_FIFO_INTSTS_TIMIEOUT_INTSTS_MASK               (0x1U << PWM_FIFO_INTSTS_TIMIEOUT_INTSTS_SHIFT)              /* 0x00000008 */
#define PWM_FIFO_INTSTS_FIFO_EMPTY_STATUS_SHIFT            (4U)
#define PWM_FIFO_INTSTS_FIFO_EMPTY_STATUS_MASK             (0x1U << PWM_FIFO_INTSTS_FIFO_EMPTY_STATUS_SHIFT)            /* 0x00000010 */
/* FIFO_TOUTTHR */
#define PWM_FIFO_TOUTTHR_OFFSET                            (0x58U)
#define PWM_FIFO_TOUTTHR_TIMEOUT_THRESHOLD_SHIFT           (0U)
#define PWM_FIFO_TOUTTHR_TIMEOUT_THRESHOLD_MASK            (0xFFFFFU << PWM_FIFO_TOUTTHR_TIMEOUT_THRESHOLD_SHIFT)       /* 0x000FFFFF */
/* VERSION_ID */
#define PWM_VERSION_ID_OFFSET                              (0x5CU)
#define PWM_VERSION_ID_SVN_VERSION_SHIFT                   (0U)
#define PWM_VERSION_ID_SVN_VERSION_MASK                    (0xFFFFU << PWM_VERSION_ID_SVN_VERSION_SHIFT)                /* 0x0000FFFF */
#define PWM_VERSION_ID_MINOR_VERSION_SHIFT                 (16U)
#define PWM_VERSION_ID_MINOR_VERSION_MASK                  (0xFFU << PWM_VERSION_ID_MINOR_VERSION_SHIFT)                /* 0x00FF0000 */
#define PWM_VERSION_ID_MAIN_VERSION_SHIFT                  (24U)
#define PWM_VERSION_ID_MAIN_VERSION_MASK                   (0xFFU << PWM_VERSION_ID_MAIN_VERSION_SHIFT)                 /* 0xFF000000 */
/* FIFO */
#define PWM_FIFO_OFFSET                                    (0x60U)
#define PWM_FIFO                                           (0x0U)
#define PWM_FIFO_CYCLE_CNT_SHIFT                           (0U)
#define PWM_FIFO_CYCLE_CNT_MASK                            (0x7FFFFFFFU << PWM_FIFO_CYCLE_CNT_SHIFT)                    /* 0x7FFFFFFF */
#define PWM_FIFO_POL_SHIFT                                 (31U)
#define PWM_FIFO_POL_MASK                                  (0x1U << PWM_FIFO_POL_SHIFT)                                 /* 0x80000000 */
/* PWRMATCH_CTRL */
#define PWM_PWRMATCH_CTRL_OFFSET                           (0x80U)
#define PWM_PWRMATCH_CTRL_CH3_PWRKEY_ENABLE_SHIFT          (3U)
#define PWM_PWRMATCH_CTRL_CH3_PWRKEY_ENABLE_MASK           (0x1U << PWM_PWRMATCH_CTRL_CH3_PWRKEY_ENABLE_SHIFT)          /* 0x00000008 */
#define PWM_PWRMATCH_CTRL_CH3_PWRKEY_POLARITY_SHIFT        (7U)
#define PWM_PWRMATCH_CTRL_CH3_PWRKEY_POLARITY_MASK         (0x1U << PWM_PWRMATCH_CTRL_CH3_PWRKEY_POLARITY_SHIFT)        /* 0x00000080 */
#define PWM_PWRMATCH_CTRL_CH3_PWRKEY_CAPTURE_CTRL_SHIFT    (11U)
#define PWM_PWRMATCH_CTRL_CH3_PWRKEY_CAPTURE_CTRL_MASK     (0x1U << PWM_PWRMATCH_CTRL_CH3_PWRKEY_CAPTURE_CTRL_SHIFT)    /* 0x00000800 */
#define PWM_PWRMATCH_CTRL_CH3_PWRKEY_INT_CTRL_SHIFT        (15U)
#define PWM_PWRMATCH_CTRL_CH3_PWRKEY_INT_CTRL_MASK         (0x1U << PWM_PWRMATCH_CTRL_CH3_PWRKEY_INT_CTRL_SHIFT)        /* 0x00008000 */
/* PWRMATCH_LPRE */
#define PWM_PWRMATCH_LPRE_OFFSET                           (0x84U)
#define PWM_PWRMATCH_LPRE_CNT_MIN_SHIFT                    (0U)
#define PWM_PWRMATCH_LPRE_CNT_MIN_MASK                     (0xFFFFU << PWM_PWRMATCH_LPRE_CNT_MIN_SHIFT)                 /* 0x0000FFFF */
#define PWM_PWRMATCH_LPRE_CNT_MAX_SHIFT                    (16U)
#define PWM_PWRMATCH_LPRE_CNT_MAX_MASK                     (0xFFFFU << PWM_PWRMATCH_LPRE_CNT_MAX_SHIFT)                 /* 0xFFFF0000 */
/* PWRMATCH_HPRE */
#define PWM_PWRMATCH_HPRE_OFFSET                           (0x88U)
#define PWM_PWRMATCH_HPRE_CNT_MIN_SHIFT                    (0U)
#define PWM_PWRMATCH_HPRE_CNT_MIN_MASK                     (0xFFFFU << PWM_PWRMATCH_HPRE_CNT_MIN_SHIFT)                 /* 0x0000FFFF */
#define PWM_PWRMATCH_HPRE_CNT_MAX_SHIFT                    (16U)
#define PWM_PWRMATCH_HPRE_CNT_MAX_MASK                     (0xFFFFU << PWM_PWRMATCH_HPRE_CNT_MAX_SHIFT)                 /* 0xFFFF0000 */
/* PWRMATCH_LD */
#define PWM_PWRMATCH_LD_OFFSET                             (0x8CU)
#define PWM_PWRMATCH_LD_CNT_MIN_SHIFT                      (0U)
#define PWM_PWRMATCH_LD_CNT_MIN_MASK                       (0xFFFFU << PWM_PWRMATCH_LD_CNT_MIN_SHIFT)                   /* 0x0000FFFF */
#define PWM_PWRMATCH_LD_CNT_MAX_SHIFT                      (16U)
#define PWM_PWRMATCH_LD_CNT_MAX_MASK                       (0xFFFFU << PWM_PWRMATCH_LD_CNT_MAX_SHIFT)                   /* 0xFFFF0000 */
/* PWRMATCH_HD_ZERO */
#define PWM_PWRMATCH_HD_ZERO_OFFSET                        (0x90U)
#define PWM_PWRMATCH_HD_ZERO_CNT_MIN_SHIFT                 (0U)
#define PWM_PWRMATCH_HD_ZERO_CNT_MIN_MASK                  (0xFFFFU << PWM_PWRMATCH_HD_ZERO_CNT_MIN_SHIFT)              /* 0x0000FFFF */
#define PWM_PWRMATCH_HD_ZERO_CNT_MAX_SHIFT                 (16U)
#define PWM_PWRMATCH_HD_ZERO_CNT_MAX_MASK                  (0xFFFFU << PWM_PWRMATCH_HD_ZERO_CNT_MAX_SHIFT)              /* 0xFFFF0000 */
/* PWRMATCH_HD_ONE */
#define PWM_PWRMATCH_HD_ONE_OFFSET                         (0x94U)
#define PWM_PWRMATCH_HD_ONE_CNT_MIN_SHIFT                  (0U)
#define PWM_PWRMATCH_HD_ONE_CNT_MIN_MASK                   (0xFFFFU << PWM_PWRMATCH_HD_ONE_CNT_MIN_SHIFT)               /* 0x0000FFFF */
#define PWM_PWRMATCH_HD_ONE_CNT_MAX_SHIFT                  (16U)
#define PWM_PWRMATCH_HD_ONE_CNT_MAX_MASK                   (0xFFFFU << PWM_PWRMATCH_HD_ONE_CNT_MAX_SHIFT)               /* 0xFFFF0000 */
/* PWRMATCH_VALUE0 */
#define PWM_PWRMATCH_VALUE0_OFFSET                         (0x98U)
#define PWM_PWRMATCH_VALUE0_PWRKEY_MATCH_VALUE_SHIFT       (0U)
#define PWM_PWRMATCH_VALUE0_PWRKEY_MATCH_VALUE_MASK        (0xFFFFFFFFU << PWM_PWRMATCH_VALUE0_PWRKEY_MATCH_VALUE_SHIFT) /* 0xFFFFFFFF */
/* PWRMATCH_VALUE1 */
#define PWM_PWRMATCH_VALUE1_OFFSET                         (0x9CU)
#define PWM_PWRMATCH_VALUE1_PWRKEY_MATCH_VALUE_SHIFT       (0U)
#define PWM_PWRMATCH_VALUE1_PWRKEY_MATCH_VALUE_MASK        (0xFFFFFFFFU << PWM_PWRMATCH_VALUE1_PWRKEY_MATCH_VALUE_SHIFT) /* 0xFFFFFFFF */
/* PWRMATCH_VALUE2 */
#define PWM_PWRMATCH_VALUE2_OFFSET                         (0xA0U)
#define PWM_PWRMATCH_VALUE2_PWRKEY_MATCH_VALUE_SHIFT       (0U)
#define PWM_PWRMATCH_VALUE2_PWRKEY_MATCH_VALUE_MASK        (0xFFFFFFFFU << PWM_PWRMATCH_VALUE2_PWRKEY_MATCH_VALUE_SHIFT) /* 0xFFFFFFFF */
/* PWRMATCH_VALUE3 */
#define PWM_PWRMATCH_VALUE3_OFFSET                         (0xA4U)
#define PWM_PWRMATCH_VALUE3_PWRKEY_MATCH_VALUE_SHIFT       (0U)
#define PWM_PWRMATCH_VALUE3_PWRKEY_MATCH_VALUE_MASK        (0xFFFFFFFFU << PWM_PWRMATCH_VALUE3_PWRKEY_MATCH_VALUE_SHIFT) /* 0xFFFFFFFF */
/* PWRMATCH_VALUE4 */
#define PWM_PWRMATCH_VALUE4_OFFSET                         (0xA8U)
#define PWM_PWRMATCH_VALUE4_PWRKEY_MATCH_VALUE_SHIFT       (0U)
#define PWM_PWRMATCH_VALUE4_PWRKEY_MATCH_VALUE_MASK        (0xFFFFFFFFU << PWM_PWRMATCH_VALUE4_PWRKEY_MATCH_VALUE_SHIFT) /* 0xFFFFFFFF */
/* PWRMATCH_VALUE5 */
#define PWM_PWRMATCH_VALUE5_OFFSET                         (0xACU)
#define PWM_PWRMATCH_VALUE5_PWRKEY_MATCH_VALUE_SHIFT       (0U)
#define PWM_PWRMATCH_VALUE5_PWRKEY_MATCH_VALUE_MASK        (0xFFFFFFFFU << PWM_PWRMATCH_VALUE5_PWRKEY_MATCH_VALUE_SHIFT) /* 0xFFFFFFFF */
/* PWRMATCH_VALUE6 */
#define PWM_PWRMATCH_VALUE6_OFFSET                         (0xB0U)
#define PWM_PWRMATCH_VALUE6_PWRKEY_MATCH_VALUE_SHIFT       (0U)
#define PWM_PWRMATCH_VALUE6_PWRKEY_MATCH_VALUE_MASK        (0xFFFFFFFFU << PWM_PWRMATCH_VALUE6_PWRKEY_MATCH_VALUE_SHIFT) /* 0xFFFFFFFF */
/* PWRMATCH_VALUE7 */
#define PWM_PWRMATCH_VALUE7_OFFSET                         (0xB4U)
#define PWM_PWRMATCH_VALUE7_PWRKEY_MATCH_VALUE_SHIFT       (0U)
#define PWM_PWRMATCH_VALUE7_PWRKEY_MATCH_VALUE_MASK        (0xFFFFFFFFU << PWM_PWRMATCH_VALUE7_PWRKEY_MATCH_VALUE_SHIFT) /* 0xFFFFFFFF */
/* PWRMATCH_VALUE8 */
#define PWM_PWRMATCH_VALUE8_OFFSET                         (0xB8U)
#define PWM_PWRMATCH_VALUE8_PWRKEY_MATCH_VALUE_SHIFT       (0U)
#define PWM_PWRMATCH_VALUE8_PWRKEY_MATCH_VALUE_MASK        (0xFFFFFFFFU << PWM_PWRMATCH_VALUE8_PWRKEY_MATCH_VALUE_SHIFT) /* 0xFFFFFFFF */
/* PWRMATCH_VALUE9 */
#define PWM_PWRMATCH_VALUE9_OFFSET                         (0xBCU)
#define PWM_PWRMATCH_VALUE9_PWRKEY_MATCH_VALUE_SHIFT       (0U)
#define PWM_PWRMATCH_VALUE9_PWRKEY_MATCH_VALUE_MASK        (0xFFFFFFFFU << PWM_PWRMATCH_VALUE9_PWRKEY_MATCH_VALUE_SHIFT) /* 0xFFFFFFFF */
/* PWM3_PWRCAPTURE_VALUE */
#define PWM_PWM3_PWRCAPTURE_VALUE_OFFSET                   (0xCCU)
#define PWM_PWM3_PWRCAPTURE_VALUE                          (0x0U)
#define PWM_PWM3_PWRCAPTURE_VALUE_PWRKEY_CAPTURE_VALUE_SHIFT (0U)
#define PWM_PWM3_PWRCAPTURE_VALUE_PWRKEY_CAPTURE_VALUE_MASK (0xFFFFFFFFU << PWM_PWM3_PWRCAPTURE_VALUE_PWRKEY_CAPTURE_VALUE_SHIFT) /* 0xFFFFFFFF */
/* FILTER_CTRL */
#define PWM_FILTER_CTRL_OFFSET                             (0xD0U)
#define PWM_FILTER_CTRL_CH0_INPUT_FILTER_ENABLE_SHIFT      (0U)
#define PWM_FILTER_CTRL_CH0_INPUT_FILTER_ENABLE_MASK       (0x1U << PWM_FILTER_CTRL_CH0_INPUT_FILTER_ENABLE_SHIFT)      /* 0x00000001 */
#define PWM_FILTER_CTRL_CH1_INPUT_FILTER_ENABLE_SHIFT      (1U)
#define PWM_FILTER_CTRL_CH1_INPUT_FILTER_ENABLE_MASK       (0x1U << PWM_FILTER_CTRL_CH1_INPUT_FILTER_ENABLE_SHIFT)      /* 0x00000002 */
#define PWM_FILTER_CTRL_CH2_INPUT_FILTER_ENABLE_SHIFT      (2U)
#define PWM_FILTER_CTRL_CH2_INPUT_FILTER_ENABLE_MASK       (0x1U << PWM_FILTER_CTRL_CH2_INPUT_FILTER_ENABLE_SHIFT)      /* 0x00000004 */
#define PWM_FILTER_CTRL_CH3_INPUT_FILTER_ENABLE_SHIFT      (3U)
#define PWM_FILTER_CTRL_CH3_INPUT_FILTER_ENABLE_MASK       (0x1U << PWM_FILTER_CTRL_CH3_INPUT_FILTER_ENABLE_SHIFT)      /* 0x00000008 */
#define PWM_FILTER_CTRL_FILTER_NUMBER_SHIFT                (4U)
#define PWM_FILTER_CTRL_FILTER_NUMBER_MASK                 (0x1FFU << PWM_FILTER_CTRL_FILTER_NUMBER_SHIFT)              /* 0x00001FF0 */
/*****************************************TIMER******************************************/
/* LOAD_COUNT0 */
#define TIMER_LOAD_COUNT0_OFFSET                           (0x0U)
#define TIMER_LOAD_COUNT0_COUNT0_SHIFT                     (0U)
#define TIMER_LOAD_COUNT0_COUNT0_MASK                      (0xFFFFFFFFU << TIMER_LOAD_COUNT0_COUNT0_SHIFT)              /* 0xFFFFFFFF */
/* LOAD_COUNT1 */
#define TIMER_LOAD_COUNT1_OFFSET                           (0x4U)
#define TIMER_LOAD_COUNT1_COUNT1_SHIFT                     (0U)
#define TIMER_LOAD_COUNT1_COUNT1_MASK                      (0xFFFFFFFFU << TIMER_LOAD_COUNT1_COUNT1_SHIFT)              /* 0xFFFFFFFF */
/* CURRENT_VALUE0 */
#define TIMER_CURRENT_VALUE0_OFFSET                        (0x8U)
#define TIMER_CURRENT_VALUE0                               (0x0U)
#define TIMER_CURRENT_VALUE0_CURRENT_VALUE0_SHIFT          (0U)
#define TIMER_CURRENT_VALUE0_CURRENT_VALUE0_MASK           (0xFFFFFFFFU << TIMER_CURRENT_VALUE0_CURRENT_VALUE0_SHIFT)   /* 0xFFFFFFFF */
/* CURRENT_VALUE1 */
#define TIMER_CURRENT_VALUE1_OFFSET                        (0xCU)
#define TIMER_CURRENT_VALUE1                               (0x0U)
#define TIMER_CURRENT_VALUE1_CURRENT_VALUE1_SHIFT          (0U)
#define TIMER_CURRENT_VALUE1_CURRENT_VALUE1_MASK           (0xFFFFFFFFU << TIMER_CURRENT_VALUE1_CURRENT_VALUE1_SHIFT)   /* 0xFFFFFFFF */
/* CONTROLREG */
#define TIMER_CONTROLREG_OFFSET                            (0x10U)
#define TIMER_CONTROLREG_TIMER_ENABLE_SHIFT                (0U)
#define TIMER_CONTROLREG_TIMER_ENABLE_MASK                 (0x1U << TIMER_CONTROLREG_TIMER_ENABLE_SHIFT)                /* 0x00000001 */
#define TIMER_CONTROLREG_TIMER_MODE_SHIFT                  (1U)
#define TIMER_CONTROLREG_TIMER_MODE_MASK                   (0x1U << TIMER_CONTROLREG_TIMER_MODE_SHIFT)                  /* 0x00000002 */
#define TIMER_CONTROLREG_TIMER_INT_MASK_SHIFT              (2U)
#define TIMER_CONTROLREG_TIMER_INT_MASK_MASK               (0x1U << TIMER_CONTROLREG_TIMER_INT_MASK_SHIFT)              /* 0x00000004 */
/* INTSTATUS */
#define TIMER_INTSTATUS_OFFSET                             (0x18U)
#define TIMER_INTSTATUS_INT_PD_SHIFT                       (0U)
#define TIMER_INTSTATUS_INT_PD_MASK                        (0x1U << TIMER_INTSTATUS_INT_PD_SHIFT)                       /* 0x00000001 */
/******************************************WDT*******************************************/
/* WDT_CR */
#define WDT_CR_OFFSET                                  (0x0)
#define WDT_CR_WDT_EN_SHIFT                            (0U)
#define WDT_CR_WDT_EN_MASK                             (0x1U << WDT_CR_WDT_EN_SHIFT)                            /* 0x00000001 */
#define WDT_CR_RESP_MODE_SHIFT                         (1U)
#define WDT_CR_RESP_MODE_MASK                          (0x1U << WDT_CR_RESP_MODE_SHIFT)                         /* 0x00000002 */
#define WDT_CR_RST_PLUSE_LENTH_SHIFT                   (2U)
#define WDT_CR_RST_PLUSE_LENTH_MASK                    (0x3U << WDT_CR_RST_PLUSE_LENTH_SHIFT)                   /* 0x0000000C */
/* WDT_TORR */
#define WDT_TORR_OFFSET                                (0x4)
#define WDT_TORR_TIMEOUT_PERIOD_SHIFT                  (0U)
#define WDT_TORR_TIMEOUT_PERIOD_MASK                   (0xFU << WDT_TORR_TIMEOUT_PERIOD_SHIFT)                  /* 0x0000000F */
/* WDT_CCVR */
#define WDT_CCVR_OFFSET                                (0x8)
#define WDT_CCVR_CUR_CNT_SHIFT                         (0U)
#define WDT_CCVR_CUR_CNT_MASK                          (0xFFFFFFFFU << WDT_CCVR_CUR_CNT_SHIFT)                  /* 0xFFFFFFFF */
/* WDT_CRR */
#define WDT_CRR_OFFSET                                 (0xC)
#define WDT_CRR_CNT_RESTART_SHIFT                      (0U)
#define WDT_CRR_CNT_RESTART_MASK                       (0xFFU << WDT_CRR_CNT_RESTART_SHIFT)                     /* 0x000000FF */
/* WDT_STAT */
#define WDT_STAT_OFFSET                                (0x10)
#define WDT_STAT_WDT_STATUS_SHIFT                      (0U)
#define WDT_STAT_WDT_STATUS_MASK                       (0x1U << WDT_STAT_WDT_STATUS_SHIFT)                      /* 0x00000001 */
/* WDT_EOI */
#define WDT_EOI_OFFSET                                 (0x14)
#define WDT_EOI_WDT_INT_CLR_SHIFT                      (0U)
#define WDT_EOI_WDT_INT_CLR_MASK                       (0x1U << WDT_EOI_WDT_INT_CLR_SHIFT)                      /* 0x00000001 */
/******************************************I2C*******************************************/
/* CON */
#define I2C_CON_OFFSET                                     (0x0U)
#define I2C_CON_I2C_EN_SHIFT                               (0U)
#define I2C_CON_I2C_EN_MASK                                (0x1U << I2C_CON_I2C_EN_SHIFT)                               /* 0x00000001 */
#define I2C_CON_I2C_MODE_SHIFT                             (1U)
#define I2C_CON_I2C_MODE_MASK                              (0x3U << I2C_CON_I2C_MODE_SHIFT)                             /* 0x00000006 */
#define I2C_CON_START_SHIFT                                (3U)
#define I2C_CON_START_MASK                                 (0x1U << I2C_CON_START_SHIFT)                                /* 0x00000008 */
#define I2C_CON_STOP_SHIFT                                 (4U)
#define I2C_CON_STOP_MASK                                  (0x1U << I2C_CON_STOP_SHIFT)                                 /* 0x00000010 */
#define I2C_CON_ACK_SHIFT                                  (5U)
#define I2C_CON_ACK_MASK                                   (0x1U << I2C_CON_ACK_SHIFT)                                  /* 0x00000020 */
#define I2C_CON_ACT2NAK_SHIFT                              (6U)
#define I2C_CON_ACT2NAK_MASK                               (0x1U << I2C_CON_ACT2NAK_SHIFT)                              /* 0x00000040 */
#define I2C_CON_DATA_UPD_ST_SHIFT                          (8U)
#define I2C_CON_DATA_UPD_ST_MASK                           (0x7U << I2C_CON_DATA_UPD_ST_SHIFT)                          /* 0x00000700 */
#define I2C_CON_START_SETUP_SHIFT                          (12U)
#define I2C_CON_START_SETUP_MASK                           (0x3U << I2C_CON_START_SETUP_SHIFT)                          /* 0x00003000 */
#define I2C_CON_STOP_SETUP_SHIFT                           (14U)
#define I2C_CON_STOP_SETUP_MASK                            (0x3U << I2C_CON_STOP_SETUP_SHIFT)                           /* 0x0000C000 */
#define I2C_CON_VERSION_SHIFT                              (16U)
#define I2C_CON_VERSION_MASK                               (0xFFFFU << I2C_CON_VERSION_SHIFT)                           /* 0xFFFF0000 */
/* CLKDIV */
#define I2C_CLKDIV_OFFSET                                  (0x4U)
#define I2C_CLKDIV_CLKDIVL_SHIFT                           (0U)
#define I2C_CLKDIV_CLKDIVL_MASK                            (0xFFFFU << I2C_CLKDIV_CLKDIVL_SHIFT)                        /* 0x0000FFFF */
#define I2C_CLKDIV_CLKDIVH_SHIFT                           (16U)
#define I2C_CLKDIV_CLKDIVH_MASK                            (0xFFFFU << I2C_CLKDIV_CLKDIVH_SHIFT)                        /* 0xFFFF0000 */
/* MRXADDR */
#define I2C_MRXADDR_OFFSET                                 (0x8U)
#define I2C_MRXADDR_SADDR_SHIFT                            (0U)
#define I2C_MRXADDR_SADDR_MASK                             (0xFFFFFFU << I2C_MRXADDR_SADDR_SHIFT)                       /* 0x00FFFFFF */
#define I2C_MRXADDR_ADDLVLD_SHIFT                          (24U)
#define I2C_MRXADDR_ADDLVLD_MASK                           (0x1U << I2C_MRXADDR_ADDLVLD_SHIFT)                          /* 0x01000000 */
#define I2C_MRXADDR_ADDMVLD_SHIFT                          (25U)
#define I2C_MRXADDR_ADDMVLD_MASK                           (0x1U << I2C_MRXADDR_ADDMVLD_SHIFT)                          /* 0x02000000 */
#define I2C_MRXADDR_ADDHVLD_SHIFT                          (26U)
#define I2C_MRXADDR_ADDHVLD_MASK                           (0x1U << I2C_MRXADDR_ADDHVLD_SHIFT)                          /* 0x04000000 */
/* MRXRADDR */
#define I2C_MRXRADDR_OFFSET                                (0xCU)
#define I2C_MRXRADDR_SRADDR_SHIFT                          (0U)
#define I2C_MRXRADDR_SRADDR_MASK                           (0xFFFFFFU << I2C_MRXRADDR_SRADDR_SHIFT)                     /* 0x00FFFFFF */
#define I2C_MRXRADDR_SRADDLVLD_SHIFT                       (24U)
#define I2C_MRXRADDR_SRADDLVLD_MASK                        (0x1U << I2C_MRXRADDR_SRADDLVLD_SHIFT)                       /* 0x01000000 */
#define I2C_MRXRADDR_SRADDMVLD_SHIFT                       (25U)
#define I2C_MRXRADDR_SRADDMVLD_MASK                        (0x1U << I2C_MRXRADDR_SRADDMVLD_SHIFT)                       /* 0x02000000 */
#define I2C_MRXRADDR_SRADDHVLD_SHIFT                       (26U)
#define I2C_MRXRADDR_SRADDHVLD_MASK                        (0x1U << I2C_MRXRADDR_SRADDHVLD_SHIFT)                       /* 0x04000000 */
/* MTXCNT */
#define I2C_MTXCNT_OFFSET                                  (0x10U)
#define I2C_MTXCNT_MTXCNT_SHIFT                            (0U)
#define I2C_MTXCNT_MTXCNT_MASK                             (0x3FU << I2C_MTXCNT_MTXCNT_SHIFT)                           /* 0x0000003F */
/* MRXCNT */
#define I2C_MRXCNT_OFFSET                                  (0x14U)
#define I2C_MRXCNT_MRXCNT_SHIFT                            (0U)
#define I2C_MRXCNT_MRXCNT_MASK                             (0x3FU << I2C_MRXCNT_MRXCNT_SHIFT)                           /* 0x0000003F */
/* IEN */
#define I2C_IEN_OFFSET                                     (0x18U)
#define I2C_IEN_BTFIEN_SHIFT                               (0U)
#define I2C_IEN_BTFIEN_MASK                                (0x1U << I2C_IEN_BTFIEN_SHIFT)                               /* 0x00000001 */
#define I2C_IEN_BRFIEN_SHIFT                               (1U)
#define I2C_IEN_BRFIEN_MASK                                (0x1U << I2C_IEN_BRFIEN_SHIFT)                               /* 0x00000002 */
#define I2C_IEN_MBTFIEN_SHIFT                              (2U)
#define I2C_IEN_MBTFIEN_MASK                               (0x1U << I2C_IEN_MBTFIEN_SHIFT)                              /* 0x00000004 */
#define I2C_IEN_MBRFIEN_SHIFT                              (3U)
#define I2C_IEN_MBRFIEN_MASK                               (0x1U << I2C_IEN_MBRFIEN_SHIFT)                              /* 0x00000008 */
#define I2C_IEN_STARTIEN_SHIFT                             (4U)
#define I2C_IEN_STARTIEN_MASK                              (0x1U << I2C_IEN_STARTIEN_SHIFT)                             /* 0x00000010 */
#define I2C_IEN_STOPIEN_SHIFT                              (5U)
#define I2C_IEN_STOPIEN_MASK                               (0x1U << I2C_IEN_STOPIEN_SHIFT)                              /* 0x00000020 */
#define I2C_IEN_NAKRCVIEN_SHIFT                            (6U)
#define I2C_IEN_NAKRCVIEN_MASK                             (0x1U << I2C_IEN_NAKRCVIEN_SHIFT)                            /* 0x00000040 */
#define I2C_IEN_SLAVEHDSCLEN_SHIFT                         (7U)
#define I2C_IEN_SLAVEHDSCLEN_MASK                          (0x1U << I2C_IEN_SLAVEHDSCLEN_SHIFT)                         /* 0x00000080 */
/* IPD */
#define I2C_IPD_OFFSET                                     (0x1CU)
#define I2C_IPD_BTFIPD_SHIFT                               (0U)
#define I2C_IPD_BTFIPD_MASK                                (0x1U << I2C_IPD_BTFIPD_SHIFT)                               /* 0x00000001 */
#define I2C_IPD_BRFIPD_SHIFT                               (1U)
#define I2C_IPD_BRFIPD_MASK                                (0x1U << I2C_IPD_BRFIPD_SHIFT)                               /* 0x00000002 */
#define I2C_IPD_MBTFIPD_SHIFT                              (2U)
#define I2C_IPD_MBTFIPD_MASK                               (0x1U << I2C_IPD_MBTFIPD_SHIFT)                              /* 0x00000004 */
#define I2C_IPD_MBRFIPD_SHIFT                              (3U)
#define I2C_IPD_MBRFIPD_MASK                               (0x1U << I2C_IPD_MBRFIPD_SHIFT)                              /* 0x00000008 */
#define I2C_IPD_STARTIPD_SHIFT                             (4U)
#define I2C_IPD_STARTIPD_MASK                              (0x1U << I2C_IPD_STARTIPD_SHIFT)                             /* 0x00000010 */
#define I2C_IPD_STOPIPD_SHIFT                              (5U)
#define I2C_IPD_STOPIPD_MASK                               (0x1U << I2C_IPD_STOPIPD_SHIFT)                              /* 0x00000020 */
#define I2C_IPD_NAKRCVIPD_SHIFT                            (6U)
#define I2C_IPD_NAKRCVIPD_MASK                             (0x1U << I2C_IPD_NAKRCVIPD_SHIFT)                            /* 0x00000040 */
#define I2C_IPD_SLAVEHDSCLIPD_SHIFT                        (7U)
#define I2C_IPD_SLAVEHDSCLIPD_MASK                         (0x1U << I2C_IPD_SLAVEHDSCLIPD_SHIFT)                        /* 0x00000080 */
/* FCNT */
#define I2C_FCNT_OFFSET                                    (0x20U)
#define I2C_FCNT                                           (0x0U)
#define I2C_FCNT_FCNT_SHIFT                                (0U)
#define I2C_FCNT_FCNT_MASK                                 (0x3FU << I2C_FCNT_FCNT_SHIFT)                               /* 0x0000003F */
/* SCL_OE_DB */
#define I2C_SCL_OE_DB_OFFSET                               (0x24U)
#define I2C_SCL_OE_DB_SCL_OE_DB_SHIFT                      (0U)
#define I2C_SCL_OE_DB_SCL_OE_DB_MASK                       (0xFFU << I2C_SCL_OE_DB_SCL_OE_DB_SHIFT)                     /* 0x000000FF */
/* TXDATA0 */
#define I2C_TXDATA0_OFFSET                                 (0x100U)
#define I2C_TXDATA0_TXDATA0_SHIFT                          (0U)
#define I2C_TXDATA0_TXDATA0_MASK                           (0xFFFFFFFFU << I2C_TXDATA0_TXDATA0_SHIFT)                   /* 0xFFFFFFFF */
/* TXDATA1 */
#define I2C_TXDATA1_OFFSET                                 (0x104U)
#define I2C_TXDATA1_TXDATA1_SHIFT                          (0U)
#define I2C_TXDATA1_TXDATA1_MASK                           (0xFFFFFFFFU << I2C_TXDATA1_TXDATA1_SHIFT)                   /* 0xFFFFFFFF */
/* TXDATA2 */
#define I2C_TXDATA2_OFFSET                                 (0x108U)
#define I2C_TXDATA2_TXDATA2_SHIFT                          (0U)
#define I2C_TXDATA2_TXDATA2_MASK                           (0xFFFFFFFFU << I2C_TXDATA2_TXDATA2_SHIFT)                   /* 0xFFFFFFFF */
/* TXDATA3 */
#define I2C_TXDATA3_OFFSET                                 (0x10CU)
#define I2C_TXDATA3_TXDATA3_SHIFT                          (0U)
#define I2C_TXDATA3_TXDATA3_MASK                           (0xFFFFFFFFU << I2C_TXDATA3_TXDATA3_SHIFT)                   /* 0xFFFFFFFF */
/* TXDATA4 */
#define I2C_TXDATA4_OFFSET                                 (0x110U)
#define I2C_TXDATA4_TXDATA4_SHIFT                          (0U)
#define I2C_TXDATA4_TXDATA4_MASK                           (0xFFFFFFFFU << I2C_TXDATA4_TXDATA4_SHIFT)                   /* 0xFFFFFFFF */
/* TXDATA5 */
#define I2C_TXDATA5_OFFSET                                 (0x114U)
#define I2C_TXDATA5_TXDATA5_SHIFT                          (0U)
#define I2C_TXDATA5_TXDATA5_MASK                           (0xFFFFFFFFU << I2C_TXDATA5_TXDATA5_SHIFT)                   /* 0xFFFFFFFF */
/* TXDATA6 */
#define I2C_TXDATA6_OFFSET                                 (0x118U)
#define I2C_TXDATA6_TXDATA6_SHIFT                          (0U)
#define I2C_TXDATA6_TXDATA6_MASK                           (0xFFFFFFFFU << I2C_TXDATA6_TXDATA6_SHIFT)                   /* 0xFFFFFFFF */
/* TXDATA7 */
#define I2C_TXDATA7_OFFSET                                 (0x11CU)
#define I2C_TXDATA7_TXDATA7_SHIFT                          (0U)
#define I2C_TXDATA7_TXDATA7_MASK                           (0xFFFFFFFFU << I2C_TXDATA7_TXDATA7_SHIFT)                   /* 0xFFFFFFFF */
/* RXDATA0 */
#define I2C_RXDATA0_OFFSET                                 (0x200U)
#define I2C_RXDATA0                                        (0x0U)
#define I2C_RXDATA0_RXDATA0_SHIFT                          (0U)
#define I2C_RXDATA0_RXDATA0_MASK                           (0xFFFFFFFFU << I2C_RXDATA0_RXDATA0_SHIFT)                   /* 0xFFFFFFFF */
/* RXDATA1 */
#define I2C_RXDATA1_OFFSET                                 (0x204U)
#define I2C_RXDATA1                                        (0x0U)
#define I2C_RXDATA1_RXDATA1_SHIFT                          (0U)
#define I2C_RXDATA1_RXDATA1_MASK                           (0xFFFFFFFFU << I2C_RXDATA1_RXDATA1_SHIFT)                   /* 0xFFFFFFFF */
/* RXDATA2 */
#define I2C_RXDATA2_OFFSET                                 (0x208U)
#define I2C_RXDATA2                                        (0x0U)
#define I2C_RXDATA2_RXDATA2_SHIFT                          (0U)
#define I2C_RXDATA2_RXDATA2_MASK                           (0xFFFFFFFFU << I2C_RXDATA2_RXDATA2_SHIFT)                   /* 0xFFFFFFFF */
/* RXDATA3 */
#define I2C_RXDATA3_OFFSET                                 (0x20CU)
#define I2C_RXDATA3                                        (0x0U)
#define I2C_RXDATA3_RXDATA3_SHIFT                          (0U)
#define I2C_RXDATA3_RXDATA3_MASK                           (0xFFFFFFFFU << I2C_RXDATA3_RXDATA3_SHIFT)                   /* 0xFFFFFFFF */
/* RXDATA4 */
#define I2C_RXDATA4_OFFSET                                 (0x210U)
#define I2C_RXDATA4                                        (0x0U)
#define I2C_RXDATA4_RXDATA4_SHIFT                          (0U)
#define I2C_RXDATA4_RXDATA4_MASK                           (0xFFFFFFFFU << I2C_RXDATA4_RXDATA4_SHIFT)                   /* 0xFFFFFFFF */
/* RXDATA5 */
#define I2C_RXDATA5_OFFSET                                 (0x214U)
#define I2C_RXDATA5                                        (0x0U)
#define I2C_RXDATA5_RXDATA5_SHIFT                          (0U)
#define I2C_RXDATA5_RXDATA5_MASK                           (0xFFFFFFFFU << I2C_RXDATA5_RXDATA5_SHIFT)                   /* 0xFFFFFFFF */
/* RXDATA6 */
#define I2C_RXDATA6_OFFSET                                 (0x218U)
#define I2C_RXDATA6                                        (0x0U)
#define I2C_RXDATA6_RXDATA6_SHIFT                          (0U)
#define I2C_RXDATA6_RXDATA6_MASK                           (0xFFFFFFFFU << I2C_RXDATA6_RXDATA6_SHIFT)                   /* 0xFFFFFFFF */
/* RXDATA7 */
#define I2C_RXDATA7_OFFSET                                 (0x21CU)
#define I2C_RXDATA7                                        (0x0U)
#define I2C_RXDATA7_RXDATA7_SHIFT                          (0U)
#define I2C_RXDATA7_RXDATA7_MASK                           (0xFFFFFFFFU << I2C_RXDATA7_RXDATA7_SHIFT)                   /* 0xFFFFFFFF */
/* ST */
#define I2C_ST_OFFSET                                      (0x220U)
#define I2C_ST                                             (0x0U)
#define I2C_ST_SDA_ST_SHIFT                                (0U)
#define I2C_ST_SDA_ST_MASK                                 (0x1U << I2C_ST_SDA_ST_SHIFT)                                /* 0x00000001 */
#define I2C_ST_SCL_ST_SHIFT                                (1U)
#define I2C_ST_SCL_ST_MASK                                 (0x1U << I2C_ST_SCL_ST_SHIFT)                                /* 0x00000002 */
/* DBGCTRL */
#define I2C_DBGCTRL_OFFSET                                 (0x224U)
#define I2C_DBGCTRL_FLT_F_SHIFT                            (0U)
#define I2C_DBGCTRL_FLT_F_MASK                             (0xFU << I2C_DBGCTRL_FLT_F_SHIFT)                            /* 0x0000000F */
#define I2C_DBGCTRL_FLT_R_SHIFT                            (4U)
#define I2C_DBGCTRL_FLT_R_MASK                             (0xFU << I2C_DBGCTRL_FLT_R_SHIFT)                            /* 0x000000F0 */
#define I2C_DBGCTRL_SLV_HOLD_SCL_TH_SHIFT                  (8U)
#define I2C_DBGCTRL_SLV_HOLD_SCL_TH_MASK                   (0xFU << I2C_DBGCTRL_SLV_HOLD_SCL_TH_SHIFT)                  /* 0x00000F00 */
#define I2C_DBGCTRL_FLT_EN_SHIFT                           (12U)
#define I2C_DBGCTRL_FLT_EN_MASK                            (0x1U << I2C_DBGCTRL_FLT_EN_SHIFT)                           /* 0x00001000 */
#define I2C_DBGCTRL_NAK_RELEASE_SCL_SHIFT                  (13U)
#define I2C_DBGCTRL_NAK_RELEASE_SCL_MASK                   (0x1U << I2C_DBGCTRL_NAK_RELEASE_SCL_SHIFT)                  /* 0x00002000 */
#define I2C_DBGCTRL_H0_CHECK_SCL_SHIFT                     (14U)
#define I2C_DBGCTRL_H0_CHECK_SCL_MASK                      (0x1U << I2C_DBGCTRL_H0_CHECK_SCL_SHIFT)                     /* 0x00004000 */
/****************************************SPI2APB*****************************************/
/* CTRL0 */
#define SPI2APB_CTRL0_OFFSET                               (0x0U)
#define SPI2APB_CTRL0_FBM_SHIFT                            (0U)
#define SPI2APB_CTRL0_FBM_MASK                             (0x1U << SPI2APB_CTRL0_FBM_SHIFT)                            /* 0x00000001 */
#define SPI2APB_CTRL0_EM_SHIFT                             (1U)
#define SPI2APB_CTRL0_EM_MASK                              (0x1U << SPI2APB_CTRL0_EM_SHIFT)                             /* 0x00000002 */
#define SPI2APB_CTRL0_RXCP_SHIFT                           (2U)
#define SPI2APB_CTRL0_RXCP_MASK                            (0x1U << SPI2APB_CTRL0_RXCP_SHIFT)                           /* 0x00000004 */
#define SPI2APB_CTRL0_TXCP_SHIFT                           (3U)
#define SPI2APB_CTRL0_TXCP_MASK                            (0x1U << SPI2APB_CTRL0_TXCP_SHIFT)                           /* 0x00000008 */
/* SR */
#define SPI2APB_SR_OFFSET                                  (0x24U)
#define SPI2APB_SR                                         (0x0U)
#define SPI2APB_SR_BSF_SHIFT                               (0U)
#define SPI2APB_SR_BSF_MASK                                (0x1U << SPI2APB_SR_BSF_SHIFT)                               /* 0x00000001 */
#define SPI2APB_SR_TFF_SHIFT                               (1U)
#define SPI2APB_SR_TFF_MASK                                (0x1U << SPI2APB_SR_TFF_SHIFT)                               /* 0x00000002 */
#define SPI2APB_SR_TFE_SHIFT                               (2U)
#define SPI2APB_SR_TFE_MASK                                (0x1U << SPI2APB_SR_TFE_SHIFT)                               /* 0x00000004 */
#define SPI2APB_SR_RFF_SHIFT                               (3U)
#define SPI2APB_SR_RFF_MASK                                (0x1U << SPI2APB_SR_RFF_SHIFT)                               /* 0x00000008 */
#define SPI2APB_SR_RFE_SHIFT                               (4U)
#define SPI2APB_SR_RFE_MASK                                (0x1U << SPI2APB_SR_RFE_SHIFT)                               /* 0x00000010 */
/* IMR */
#define SPI2APB_IMR_OFFSET                                 (0x2CU)
#define SPI2APB_IMR_QWIM_SHIFT                             (0U)
#define SPI2APB_IMR_QWIM_MASK                              (0x1U << SPI2APB_IMR_QWIM_SHIFT)                             /* 0x00000001 */
/* RISR */
#define SPI2APB_RISR_OFFSET                                (0x34U)
#define SPI2APB_RISR_QWRIS_SHIFT                           (0U)
#define SPI2APB_RISR_QWRIS_MASK                            (0x1U << SPI2APB_RISR_QWRIS_SHIFT)                           /* 0x00000001 */
/* ICR */
#define SPI2APB_ICR_OFFSET                                 (0x38U)
#define SPI2APB_ICR_CQWI_SHIFT                             (0U)
#define SPI2APB_ICR_CQWI_MASK                              (0x1U << SPI2APB_ICR_CQWI_SHIFT)                             /* 0x00000001 */
/* VERSION */
#define SPI2APB_VERSION_OFFSET                             (0x48U)
#define SPI2APB_VERSION_VERSION_SHIFT                      (0U)
#define SPI2APB_VERSION_VERSION_MASK                       (0xFFFFFFFFU << SPI2APB_VERSION_VERSION_SHIFT)               /* 0xFFFFFFFF */
/* QUICK_REG0 */
#define SPI2APB_QUICK_REG0_OFFSET                          (0x50U)
#define SPI2APB_QUICK_REG0_QWV0_SHIFT                      (0U)
#define SPI2APB_QUICK_REG0_QWV0_MASK                       (0xFFFFFFFFU << SPI2APB_QUICK_REG0_QWV0_SHIFT)               /* 0xFFFFFFFF */
/* QUICK_REG1 */
#define SPI2APB_QUICK_REG1_OFFSET                          (0x54U)
#define SPI2APB_QUICK_REG1_QWV1_SHIFT                      (0U)
#define SPI2APB_QUICK_REG1_QWV1_MASK                       (0xFFFFFFFFU << SPI2APB_QUICK_REG1_QWV1_SHIFT)               /* 0xFFFFFFFF */
/* QUICK_REG2 */
#define SPI2APB_QUICK_REG2_OFFSET                          (0x58U)
#define SPI2APB_QUICK_REG2_QRV_SHIFT                       (0U)
#define SPI2APB_QUICK_REG2_QRV_MASK                        (0xFFFFFFFFU << SPI2APB_QUICK_REG2_QRV_SHIFT)                /* 0xFFFFFFFF */
/******************************************SPI*******************************************/
/* CTRLR0 */
#define SPI_CTRLR0_OFFSET                                  (0x0U)
#define SPI_CTRLR0_DFS_SHIFT                               (0U)
#define SPI_CTRLR0_DFS_MASK                                (0x3U << SPI_CTRLR0_DFS_SHIFT)                               /* 0x00000003 */
#define SPI_CTRLR0_CFS_SHIFT                               (2U)
#define SPI_CTRLR0_CFS_MASK                                (0xFU << SPI_CTRLR0_CFS_SHIFT)                               /* 0x0000003C */
#define SPI_CTRLR0_SCPH_SHIFT                              (6U)
#define SPI_CTRLR0_SCPH_MASK                               (0x1U << SPI_CTRLR0_SCPH_SHIFT)                              /* 0x00000040 */
#define SPI_CTRLR0_SCPOL_SHIFT                             (7U)
#define SPI_CTRLR0_SCPOL_MASK                              (0x1U << SPI_CTRLR0_SCPOL_SHIFT)                             /* 0x00000080 */
#define SPI_CTRLR0_CSM_SHIFT                               (8U)
#define SPI_CTRLR0_CSM_MASK                                (0x3U << SPI_CTRLR0_CSM_SHIFT)                               /* 0x00000300 */
#define SPI_CTRLR0_SSD_SHIFT                               (10U)
#define SPI_CTRLR0_SSD_MASK                                (0x1U << SPI_CTRLR0_SSD_SHIFT)                               /* 0x00000400 */
#define SPI_CTRLR0_EM_SHIFT                                (11U)
#define SPI_CTRLR0_EM_MASK                                 (0x1U << SPI_CTRLR0_EM_SHIFT)                                /* 0x00000800 */
#define SPI_CTRLR0_FBM_SHIFT                               (12U)
#define SPI_CTRLR0_FBM_MASK                                (0x1U << SPI_CTRLR0_FBM_SHIFT)                               /* 0x00001000 */
#define SPI_CTRLR0_BHT_SHIFT                               (13U)
#define SPI_CTRLR0_BHT_MASK                                (0x1U << SPI_CTRLR0_BHT_SHIFT)                               /* 0x00002000 */
#define SPI_CTRLR0_RSD_SHIFT                               (14U)
#define SPI_CTRLR0_RSD_MASK                                (0x3U << SPI_CTRLR0_RSD_SHIFT)                               /* 0x0000C000 */
#define SPI_CTRLR0_FRF_SHIFT                               (16U)
#define SPI_CTRLR0_FRF_MASK                                (0x3U << SPI_CTRLR0_FRF_SHIFT)                               /* 0x00030000 */
#define SPI_CTRLR0_XFM_SHIFT                               (18U)
#define SPI_CTRLR0_XFM_MASK                                (0x3U << SPI_CTRLR0_XFM_SHIFT)                               /* 0x000C0000 */
#define SPI_CTRLR0_OPM_SHIFT                               (20U)
#define SPI_CTRLR0_OPM_MASK                                (0x1U << SPI_CTRLR0_OPM_SHIFT)                               /* 0x00100000 */
#define SPI_CTRLR0_MTM_SHIFT                               (21U)
#define SPI_CTRLR0_MTM_MASK                                (0x1U << SPI_CTRLR0_MTM_SHIFT)                               /* 0x00200000 */
#define SPI_CTRLR0_SOI_SHIFT                               (23U)
#define SPI_CTRLR0_SOI_MASK                                (0x3U << SPI_CTRLR0_SOI_SHIFT)                               /* 0x01800000 */
#define SPI_CTRLR0_LBK_SHIFT                               (25U)
#define SPI_CTRLR0_LBK_MASK                                (0x1U << SPI_CTRLR0_LBK_SHIFT)                               /* 0x02000000 */
/* CTRLR1 */
#define SPI_CTRLR1_OFFSET                                  (0x4U)
#define SPI_CTRLR1_NDM_SHIFT                               (0U)
#define SPI_CTRLR1_NDM_MASK                                (0xFFFFFFFFU << SPI_CTRLR1_NDM_SHIFT)                        /* 0xFFFFFFFF */
/* ENR */
#define SPI_ENR_OFFSET                                     (0x8U)
#define SPI_ENR_ENR_SHIFT                                  (0U)
#define SPI_ENR_ENR_MASK                                   (0x1U << SPI_ENR_ENR_SHIFT)                                  /* 0x00000001 */
/* SER */
#define SPI_SER_OFFSET                                     (0xCU)
#define SPI_SER_SER_SHIFT                                  (0U)
#define SPI_SER_SER_MASK                                   (0x3U << SPI_SER_SER_SHIFT)                                  /* 0x00000003 */
/* BAUDR */
#define SPI_BAUDR_OFFSET                                   (0x10U)
#define SPI_BAUDR_BAUDR_SHIFT                              (0U)
#define SPI_BAUDR_BAUDR_MASK                               (0xFFFFU << SPI_BAUDR_BAUDR_SHIFT)                           /* 0x0000FFFF */
/* TXFTLR */
#define SPI_TXFTLR_OFFSET                                  (0x14U)
#define SPI_TXFTLR_TXFTLR_SHIFT                            (0U)
#define SPI_TXFTLR_TXFTLR_MASK                             (0x3FU << SPI_TXFTLR_TXFTLR_SHIFT)                           /* 0x0000003F */
/* RXFTLR */
#define SPI_RXFTLR_OFFSET                                  (0x18U)
#define SPI_RXFTLR_RXFTLR_SHIFT                            (0U)
#define SPI_RXFTLR_RXFTLR_MASK                             (0x3FU << SPI_RXFTLR_RXFTLR_SHIFT)                           /* 0x0000003F */
/* TXFLR */
#define SPI_TXFLR_OFFSET                                   (0x1CU)
#define SPI_TXFLR                                          (0x0U)
#define SPI_TXFLR_TXFLR_SHIFT                              (0U)
#define SPI_TXFLR_TXFLR_MASK                               (0x7FU << SPI_TXFLR_TXFLR_SHIFT)                             /* 0x0000007F */
/* RXFLR */
#define SPI_RXFLR_OFFSET                                   (0x20U)
#define SPI_RXFLR                                          (0x0U)
#define SPI_RXFLR_RXFLR_SHIFT                              (0U)
#define SPI_RXFLR_RXFLR_MASK                               (0x7FU << SPI_RXFLR_RXFLR_SHIFT)                             /* 0x0000007F */
/* SR */
#define SPI_SR_OFFSET                                      (0x24U)
#define SPI_SR_BSF_SHIFT                                   (0U)
#define SPI_SR_BSF_MASK                                    (0x1U << SPI_SR_BSF_SHIFT)                                   /* 0x00000001 */
#define SPI_SR_TFF_SHIFT                                   (1U)
#define SPI_SR_TFF_MASK                                    (0x1U << SPI_SR_TFF_SHIFT)                                   /* 0x00000002 */
#define SPI_SR_TFE_SHIFT                                   (2U)
#define SPI_SR_TFE_MASK                                    (0x1U << SPI_SR_TFE_SHIFT)                                   /* 0x00000004 */
#define SPI_SR_RFE_SHIFT                                   (3U)
#define SPI_SR_RFE_MASK                                    (0x1U << SPI_SR_RFE_SHIFT)                                   /* 0x00000008 */
#define SPI_SR_RFF_SHIFT                                   (4U)
#define SPI_SR_RFF_MASK                                    (0x1U << SPI_SR_RFF_SHIFT)                                   /* 0x00000010 */
#define SPI_SR_STB_SHIFT                                   (5U)
#define SPI_SR_STB_MASK                                    (0x1U << SPI_SR_STB_SHIFT)                                   /* 0x00000020 */
#define SPI_SR_SSI_SHIFT                                   (6U)
#define SPI_SR_SSI_MASK                                    (0x1U << SPI_SR_SSI_SHIFT)                                   /* 0x00000040 */
/* IPR */
#define SPI_IPR_OFFSET                                     (0x28U)
#define SPI_IPR_IPR_SHIFT                                  (0U)
#define SPI_IPR_IPR_MASK                                   (0x1U << SPI_IPR_IPR_SHIFT)                                  /* 0x00000001 */
/* IMR */
#define SPI_IMR_OFFSET                                     (0x2CU)
#define SPI_IMR_TFEIM_SHIFT                                (0U)
#define SPI_IMR_TFEIM_MASK                                 (0x1U << SPI_IMR_TFEIM_SHIFT)                                /* 0x00000001 */
#define SPI_IMR_TFOIM_SHIFT                                (1U)
#define SPI_IMR_TFOIM_MASK                                 (0x1U << SPI_IMR_TFOIM_SHIFT)                                /* 0x00000002 */
#define SPI_IMR_RFUIM_SHIFT                                (2U)
#define SPI_IMR_RFUIM_MASK                                 (0x1U << SPI_IMR_RFUIM_SHIFT)                                /* 0x00000004 */
#define SPI_IMR_RFOIM_SHIFT                                (3U)
#define SPI_IMR_RFOIM_MASK                                 (0x1U << SPI_IMR_RFOIM_SHIFT)                                /* 0x00000008 */
#define SPI_IMR_RFFIM_SHIFT                                (4U)
#define SPI_IMR_RFFIM_MASK                                 (0x1U << SPI_IMR_RFFIM_SHIFT)                                /* 0x00000010 */
#define SPI_IMR_TOIM_SHIFT                                 (5U)
#define SPI_IMR_TOIM_MASK                                  (0x1U << SPI_IMR_TOIM_SHIFT)                                 /* 0x00000020 */
#define SPI_IMR_SSPIM_SHIFT                                (6U)
#define SPI_IMR_SSPIM_MASK                                 (0x1U << SPI_IMR_SSPIM_SHIFT)                                /* 0x00000040 */
#define SPI_IMR_TXFIM_SHIFT                                (7U)
#define SPI_IMR_TXFIM_MASK                                 (0x1U << SPI_IMR_TXFIM_SHIFT)                                /* 0x00000080 */
/* ISR */
#define SPI_ISR_OFFSET                                     (0x30U)
#define SPI_ISR_TFEIS_SHIFT                                (0U)
#define SPI_ISR_TFEIS_MASK                                 (0x1U << SPI_ISR_TFEIS_SHIFT)                                /* 0x00000001 */
#define SPI_ISR_TFOIS_SHIFT                                (1U)
#define SPI_ISR_TFOIS_MASK                                 (0x1U << SPI_ISR_TFOIS_SHIFT)                                /* 0x00000002 */
#define SPI_ISR_RFUIS_SHIFT                                (2U)
#define SPI_ISR_RFUIS_MASK                                 (0x1U << SPI_ISR_RFUIS_SHIFT)                                /* 0x00000004 */
#define SPI_ISR_RFOIS_SHIFT                                (3U)
#define SPI_ISR_RFOIS_MASK                                 (0x1U << SPI_ISR_RFOIS_SHIFT)                                /* 0x00000008 */
#define SPI_ISR_RFFIS_SHIFT                                (4U)
#define SPI_ISR_RFFIS_MASK                                 (0x1U << SPI_ISR_RFFIS_SHIFT)                                /* 0x00000010 */
#define SPI_ISR_TOIS_SHIFT                                 (5U)
#define SPI_ISR_TOIS_MASK                                  (0x1U << SPI_ISR_TOIS_SHIFT)                                 /* 0x00000020 */
#define SPI_ISR_SSPIS_SHIFT                                (6U)
#define SPI_ISR_SSPIS_MASK                                 (0x1U << SPI_ISR_SSPIS_SHIFT)                                /* 0x00000040 */
#define SPI_ISR_TXFIS_SHIFT                                (7U)
#define SPI_ISR_TXFIS_MASK                                 (0x1U << SPI_ISR_TXFIS_SHIFT)                                /* 0x00000080 */
/* RISR */
#define SPI_RISR_OFFSET                                    (0x34U)
#define SPI_RISR_TFERIS_SHIFT                              (0U)
#define SPI_RISR_TFERIS_MASK                               (0x1U << SPI_RISR_TFERIS_SHIFT)                              /* 0x00000001 */
#define SPI_RISR_TFORIS_SHIFT                              (1U)
#define SPI_RISR_TFORIS_MASK                               (0x1U << SPI_RISR_TFORIS_SHIFT)                              /* 0x00000002 */
#define SPI_RISR_RFURIS_SHIFT                              (2U)
#define SPI_RISR_RFURIS_MASK                               (0x1U << SPI_RISR_RFURIS_SHIFT)                              /* 0x00000004 */
#define SPI_RISR_RFORIS_SHIFT                              (3U)
#define SPI_RISR_RFORIS_MASK                               (0x1U << SPI_RISR_RFORIS_SHIFT)                              /* 0x00000008 */
#define SPI_RISR_RFFRIS_SHIFT                              (4U)
#define SPI_RISR_RFFRIS_MASK                               (0x1U << SPI_RISR_RFFRIS_SHIFT)                              /* 0x00000010 */
#define SPI_RISR_TORIS_SHIFT                               (5U)
#define SPI_RISR_TORIS_MASK                                (0x1U << SPI_RISR_TORIS_SHIFT)                               /* 0x00000020 */
#define SPI_RISR_SSPRIS_SHIFT                              (6U)
#define SPI_RISR_SSPRIS_MASK                               (0x1U << SPI_RISR_SSPRIS_SHIFT)                              /* 0x00000040 */
#define SPI_RISR_TXFRIS_SHIFT                              (7U)
#define SPI_RISR_TXFRIS_MASK                               (0x1U << SPI_RISR_TXFRIS_SHIFT)                              /* 0x00000080 */
/* ICR */
#define SPI_ICR_OFFSET                                     (0x38U)
#define SPI_ICR_CCI_SHIFT                                  (0U)
#define SPI_ICR_CCI_MASK                                   (0x1U << SPI_ICR_CCI_SHIFT)                                  /* 0x00000001 */
#define SPI_ICR_CRFUI_SHIFT                                (1U)
#define SPI_ICR_CRFUI_MASK                                 (0x1U << SPI_ICR_CRFUI_SHIFT)                                /* 0x00000002 */
#define SPI_ICR_CRFOI_SHIFT                                (2U)
#define SPI_ICR_CRFOI_MASK                                 (0x1U << SPI_ICR_CRFOI_SHIFT)                                /* 0x00000004 */
#define SPI_ICR_CTFOI_SHIFT                                (3U)
#define SPI_ICR_CTFOI_MASK                                 (0x1U << SPI_ICR_CTFOI_SHIFT)                                /* 0x00000008 */
#define SPI_ICR_CTOI_SHIFT                                 (4U)
#define SPI_ICR_CTOI_MASK                                  (0x1U << SPI_ICR_CTOI_SHIFT)                                 /* 0x00000010 */
#define SPI_ICR_CSSPI_SHIFT                                (5U)
#define SPI_ICR_CSSPI_MASK                                 (0x1U << SPI_ICR_CSSPI_SHIFT)                                /* 0x00000020 */
#define SPI_ICR_CTXFI_SHIFT                                (6U)
#define SPI_ICR_CTXFI_MASK                                 (0x1U << SPI_ICR_CTXFI_SHIFT)                                /* 0x00000040 */
/* DMACR */
#define SPI_DMACR_OFFSET                                   (0x3CU)
#define SPI_DMACR_RDE_SHIFT                                (0U)
#define SPI_DMACR_RDE_MASK                                 (0x1U << SPI_DMACR_RDE_SHIFT)                                /* 0x00000001 */
#define SPI_DMACR_TDE_SHIFT                                (1U)
#define SPI_DMACR_TDE_MASK                                 (0x1U << SPI_DMACR_TDE_SHIFT)                                /* 0x00000002 */
/* DMATDLR */
#define SPI_DMATDLR_OFFSET                                 (0x40U)
#define SPI_DMATDLR_TDL_SHIFT                              (0U)
#define SPI_DMATDLR_TDL_MASK                               (0x3FU << SPI_DMATDLR_TDL_SHIFT)                             /* 0x0000003F */
/* DMARDLR */
#define SPI_DMARDLR_OFFSET                                 (0x44U)
#define SPI_DMARDLR_RDL_SHIFT                              (0U)
#define SPI_DMARDLR_RDL_MASK                               (0x3FU << SPI_DMARDLR_RDL_SHIFT)                             /* 0x0000003F */
/* TIMEOUT */
#define SPI_TIMEOUT_OFFSET                                 (0x4CU)
#define SPI_TIMEOUT_TOV_SHIFT                              (0U)
#define SPI_TIMEOUT_TOV_MASK                               (0xFFFFU << SPI_TIMEOUT_TOV_SHIFT)                           /* 0x0000FFFF */
#define SPI_TIMEOUT_TOE_SHIFT                              (16U)
#define SPI_TIMEOUT_TOE_MASK                               (0x1U << SPI_TIMEOUT_TOE_SHIFT)                              /* 0x00010000 */
/* BYPASS */
#define SPI_BYPASS_OFFSET                                  (0x50U)
#define SPI_BYPASS_BYEN_SHIFT                              (0U)
#define SPI_BYPASS_BYEN_MASK                               (0x1U << SPI_BYPASS_BYEN_SHIFT)                              /* 0x00000001 */
#define SPI_BYPASS_FBM_SHIFT                               (1U)
#define SPI_BYPASS_FBM_MASK                                (0x1U << SPI_BYPASS_FBM_SHIFT)                               /* 0x00000002 */
#define SPI_BYPASS_END_SHIFT                               (2U)
#define SPI_BYPASS_END_MASK                                (0x1U << SPI_BYPASS_END_SHIFT)                               /* 0x00000004 */
#define SPI_BYPASS_RXCP_SHIFT                              (3U)
#define SPI_BYPASS_RXCP_MASK                               (0x1U << SPI_BYPASS_RXCP_SHIFT)                              /* 0x00000008 */
#define SPI_BYPASS_TXCP_SHIFT                              (4U)
#define SPI_BYPASS_TXCP_MASK                               (0x1U << SPI_BYPASS_TXCP_SHIFT)                              /* 0x00000010 */
/* TXDR */
#define SPI_TXDR_OFFSET                                    (0x400U)
#define SPI_TXDR_TXDR_SHIFT                                (0U)
#define SPI_TXDR_TXDR_MASK                                 (0xFFFFU << SPI_TXDR_TXDR_SHIFT)                             /* 0x0000FFFF */
/* RXDR */
#define SPI_RXDR_OFFSET                                    (0x800U)
#define SPI_RXDR_RXDR_SHIFT                                (0U)
#define SPI_RXDR_RXDR_MASK                                 (0xFFFFU << SPI_RXDR_RXDR_SHIFT)                             /* 0x0000FFFF */
/******************************************FSPI******************************************/
/* CTRL0 */
#define FSPI_CTRL0_OFFSET                                  (0x0U)
#define FSPI_CTRL0_SPIM_SHIFT                              (0U)
#define FSPI_CTRL0_SPIM_MASK                               (0x1U << FSPI_CTRL0_SPIM_SHIFT)                              /* 0x00000001 */
#define FSPI_CTRL0_SHIFTPHASE_SHIFT                        (1U)
#define FSPI_CTRL0_SHIFTPHASE_MASK                         (0x1U << FSPI_CTRL0_SHIFTPHASE_SHIFT)                        /* 0x00000002 */
#define FSPI_CTRL0_IDLE_CYCLE_SHIFT                        (4U)
#define FSPI_CTRL0_IDLE_CYCLE_MASK                         (0xFU << FSPI_CTRL0_IDLE_CYCLE_SHIFT)                        /* 0x000000F0 */
#define FSPI_CTRL0_CMDB_SHIFT                              (8U)
#define FSPI_CTRL0_CMDB_MASK                               (0x3U << FSPI_CTRL0_CMDB_SHIFT)                              /* 0x00000300 */
#define FSPI_CTRL0_ADRB_SHIFT                              (10U)
#define FSPI_CTRL0_ADRB_MASK                               (0x3U << FSPI_CTRL0_ADRB_SHIFT)                              /* 0x00000C00 */
#define FSPI_CTRL0_DATB_SHIFT                              (12U)
#define FSPI_CTRL0_DATB_MASK                               (0x3U << FSPI_CTRL0_DATB_SHIFT)                              /* 0x00003000 */
/* IMR */
#define FSPI_IMR_OFFSET                                    (0x4U)
#define FSPI_IMR_RXFM_SHIFT                                (0U)
#define FSPI_IMR_RXFM_MASK                                 (0x1U << FSPI_IMR_RXFM_SHIFT)                                /* 0x00000001 */
#define FSPI_IMR_RXUM_SHIFT                                (1U)
#define FSPI_IMR_RXUM_MASK                                 (0x1U << FSPI_IMR_RXUM_SHIFT)                                /* 0x00000002 */
#define FSPI_IMR_TXOM_SHIFT                                (2U)
#define FSPI_IMR_TXOM_MASK                                 (0x1U << FSPI_IMR_TXOM_SHIFT)                                /* 0x00000004 */
#define FSPI_IMR_TXEM_SHIFT                                (3U)
#define FSPI_IMR_TXEM_MASK                                 (0x1U << FSPI_IMR_TXEM_SHIFT)                                /* 0x00000008 */
#define FSPI_IMR_TRANSM_SHIFT                              (4U)
#define FSPI_IMR_TRANSM_MASK                               (0x1U << FSPI_IMR_TRANSM_SHIFT)                              /* 0x00000010 */
#define FSPI_IMR_AHBM_SHIFT                                (5U)
#define FSPI_IMR_AHBM_MASK                                 (0x1U << FSPI_IMR_AHBM_SHIFT)                                /* 0x00000020 */
#define FSPI_IMR_NSPIM_SHIFT                               (6U)
#define FSPI_IMR_NSPIM_MASK                                (0x1U << FSPI_IMR_NSPIM_SHIFT)                               /* 0x00000040 */
#define FSPI_IMR_DMAM_SHIFT                                (7U)
#define FSPI_IMR_DMAM_MASK                                 (0x1U << FSPI_IMR_DMAM_SHIFT)                                /* 0x00000080 */
#define FSPI_IMR_STPOLLM_SHIFT                             (8U)
#define FSPI_IMR_STPOLLM_MASK                              (0x1U << FSPI_IMR_STPOLLM_SHIFT)                             /* 0x00000100 */
/* ICLR */
#define FSPI_ICLR_OFFSET                                   (0x8U)
#define FSPI_ICLR_RXFC_SHIFT                               (0U)
#define FSPI_ICLR_RXFC_MASK                                (0x1U << FSPI_ICLR_RXFC_SHIFT)                               /* 0x00000001 */
#define FSPI_ICLR_RXUC_SHIFT                               (1U)
#define FSPI_ICLR_RXUC_MASK                                (0x1U << FSPI_ICLR_RXUC_SHIFT)                               /* 0x00000002 */
#define FSPI_ICLR_TXOC_SHIFT                               (2U)
#define FSPI_ICLR_TXOC_MASK                                (0x1U << FSPI_ICLR_TXOC_SHIFT)                               /* 0x00000004 */
#define FSPI_ICLR_TXEC_SHIFT                               (3U)
#define FSPI_ICLR_TXEC_MASK                                (0x1U << FSPI_ICLR_TXEC_SHIFT)                               /* 0x00000008 */
#define FSPI_ICLR_TRANSC_SHIFT                             (4U)
#define FSPI_ICLR_TRANSC_MASK                              (0x1U << FSPI_ICLR_TRANSC_SHIFT)                             /* 0x00000010 */
#define FSPI_ICLR_AHBC_SHIFT                               (5U)
#define FSPI_ICLR_AHBC_MASK                                (0x1U << FSPI_ICLR_AHBC_SHIFT)                               /* 0x00000020 */
#define FSPI_ICLR_NSPIC_SHIFT                              (6U)
#define FSPI_ICLR_NSPIC_MASK                               (0x1U << FSPI_ICLR_NSPIC_SHIFT)                              /* 0x00000040 */
#define FSPI_ICLR_DMAC_SHIFT                               (7U)
#define FSPI_ICLR_DMAC_MASK                                (0x1U << FSPI_ICLR_DMAC_SHIFT)                               /* 0x00000080 */
#define FSPI_ICLR_STPOLLC_SHIFT                            (8U)
#define FSPI_ICLR_STPOLLC_MASK                             (0x1U << FSPI_ICLR_STPOLLC_SHIFT)                            /* 0x00000100 */
/* FTLR */
#define FSPI_FTLR_OFFSET                                   (0xCU)
#define FSPI_FTLR_TXFTLR_SHIFT                             (0U)
#define FSPI_FTLR_TXFTLR_MASK                              (0xFFU << FSPI_FTLR_TXFTLR_SHIFT)                            /* 0x000000FF */
#define FSPI_FTLR_RXFTLR_SHIFT                             (8U)
#define FSPI_FTLR_RXFTLR_MASK                              (0xFFU << FSPI_FTLR_RXFTLR_SHIFT)                            /* 0x0000FF00 */
/* RCVR */
#define FSPI_RCVR_OFFSET                                   (0x10U)
#define FSPI_RCVR_RCVR_SHIFT                               (0U)
#define FSPI_RCVR_RCVR_MASK                                (0x1U << FSPI_RCVR_RCVR_SHIFT)                               /* 0x00000001 */
/* AX0 */
#define FSPI_AX0_OFFSET                                    (0x14U)
#define FSPI_AX0_AX_SHIFT                                  (0U)
#define FSPI_AX0_AX_MASK                                   (0xFFU << FSPI_AX0_AX_SHIFT)                                 /* 0x000000FF */
/* ABIT0 */
#define FSPI_ABIT0_OFFSET                                  (0x18U)
#define FSPI_ABIT0_ABIT_SHIFT                              (0U)
#define FSPI_ABIT0_ABIT_MASK                               (0x1FU << FSPI_ABIT0_ABIT_SHIFT)                             /* 0x0000001F */
/* ISR */
#define FSPI_ISR_OFFSET                                    (0x1CU)
#define FSPI_ISR_RXFS_SHIFT                                (0U)
#define FSPI_ISR_RXFS_MASK                                 (0x1U << FSPI_ISR_RXFS_SHIFT)                                /* 0x00000001 */
#define FSPI_ISR_RXUS_SHIFT                                (1U)
#define FSPI_ISR_RXUS_MASK                                 (0x1U << FSPI_ISR_RXUS_SHIFT)                                /* 0x00000002 */
#define FSPI_ISR_TXOS_SHIFT                                (2U)
#define FSPI_ISR_TXOS_MASK                                 (0x1U << FSPI_ISR_TXOS_SHIFT)                                /* 0x00000004 */
#define FSPI_ISR_TXES_SHIFT                                (3U)
#define FSPI_ISR_TXES_MASK                                 (0x1U << FSPI_ISR_TXES_SHIFT)                                /* 0x00000008 */
#define FSPI_ISR_TRANSS_SHIFT                              (4U)
#define FSPI_ISR_TRANSS_MASK                               (0x1U << FSPI_ISR_TRANSS_SHIFT)                              /* 0x00000010 */
#define FSPI_ISR_AHBS_SHIFT                                (5U)
#define FSPI_ISR_AHBS_MASK                                 (0x1U << FSPI_ISR_AHBS_SHIFT)                                /* 0x00000020 */
#define FSPI_ISR_NSPIS_SHIFT                               (6U)
#define FSPI_ISR_NSPIS_MASK                                (0x1U << FSPI_ISR_NSPIS_SHIFT)                               /* 0x00000040 */
#define FSPI_ISR_DMAS_SHIFT                                (7U)
#define FSPI_ISR_DMAS_MASK                                 (0x1U << FSPI_ISR_DMAS_SHIFT)                                /* 0x00000080 */
#define FSPI_ISR_STPOLLS_SHIFT                             (8U)
#define FSPI_ISR_STPOLLS_MASK                              (0x1U << FSPI_ISR_STPOLLS_SHIFT)                             /* 0x00000100 */
/* FSR */
#define FSPI_FSR_OFFSET                                    (0x20U)
#define FSPI_FSR_TXFS_SHIFT                                (0U)
#define FSPI_FSR_TXFS_MASK                                 (0x1U << FSPI_FSR_TXFS_SHIFT)                                /* 0x00000001 */
#define FSPI_FSR_TXES_SHIFT                                (1U)
#define FSPI_FSR_TXES_MASK                                 (0x1U << FSPI_FSR_TXES_SHIFT)                                /* 0x00000002 */
#define FSPI_FSR_RXES_SHIFT                                (2U)
#define FSPI_FSR_RXES_MASK                                 (0x1U << FSPI_FSR_RXES_SHIFT)                                /* 0x00000004 */
#define FSPI_FSR_RXFS_SHIFT                                (3U)
#define FSPI_FSR_RXFS_MASK                                 (0x1U << FSPI_FSR_RXFS_SHIFT)                                /* 0x00000008 */
#define FSPI_FSR_TXWLVL_SHIFT                              (8U)
#define FSPI_FSR_TXWLVL_MASK                               (0x1FU << FSPI_FSR_TXWLVL_SHIFT)                             /* 0x00001F00 */
#define FSPI_FSR_RXWLVL_SHIFT                              (16U)
#define FSPI_FSR_RXWLVL_MASK                               (0x1FU << FSPI_FSR_RXWLVL_SHIFT)                             /* 0x001F0000 */
/* SR */
#define FSPI_SR_OFFSET                                     (0x24U)
#define FSPI_SR                                            (0x0U)
#define FSPI_SR_SR_SHIFT                                   (0U)
#define FSPI_SR_SR_MASK                                    (0x1U << FSPI_SR_SR_SHIFT)                                   /* 0x00000001 */
/* RISR */
#define FSPI_RISR_OFFSET                                   (0x28U)
#define FSPI_RISR                                          (0x0U)
#define FSPI_RISR_RXFS_SHIFT                               (0U)
#define FSPI_RISR_RXFS_MASK                                (0x1U << FSPI_RISR_RXFS_SHIFT)                               /* 0x00000001 */
#define FSPI_RISR_RXUS_SHIFT                               (1U)
#define FSPI_RISR_RXUS_MASK                                (0x1U << FSPI_RISR_RXUS_SHIFT)                               /* 0x00000002 */
#define FSPI_RISR_TXOS_SHIFT                               (2U)
#define FSPI_RISR_TXOS_MASK                                (0x1U << FSPI_RISR_TXOS_SHIFT)                               /* 0x00000004 */
#define FSPI_RISR_TXES_SHIFT                               (3U)
#define FSPI_RISR_TXES_MASK                                (0x1U << FSPI_RISR_TXES_SHIFT)                               /* 0x00000008 */
#define FSPI_RISR_TRANSS_SHIFT                             (4U)
#define FSPI_RISR_TRANSS_MASK                              (0x1U << FSPI_RISR_TRANSS_SHIFT)                             /* 0x00000010 */
#define FSPI_RISR_AHBS_SHIFT                               (5U)
#define FSPI_RISR_AHBS_MASK                                (0x1U << FSPI_RISR_AHBS_SHIFT)                               /* 0x00000020 */
#define FSPI_RISR_NSPIS_SHIFT                              (6U)
#define FSPI_RISR_NSPIS_MASK                               (0x1U << FSPI_RISR_NSPIS_SHIFT)                              /* 0x00000040 */
#define FSPI_RISR_DMAS_SHIFT                               (7U)
#define FSPI_RISR_DMAS_MASK                                (0x1U << FSPI_RISR_DMAS_SHIFT)                               /* 0x00000080 */
#define FSPI_RISR_STPOLLS_SHIFT                            (8U)
#define FSPI_RISR_STPOLLS_MASK                             (0x1U << FSPI_RISR_STPOLLS_SHIFT)                            /* 0x00000100 */
/* VER */
#define FSPI_VER_OFFSET                                    (0x2CU)
#define FSPI_VER                                           (0x3U)
#define FSPI_VER_VER_SHIFT                                 (0U)
#define FSPI_VER_VER_MASK                                  (0xFFFFU << FSPI_VER_VER_SHIFT)                              /* 0x0000FFFF */
/* QOP */
#define FSPI_QOP_OFFSET                                    (0x30U)
#define FSPI_QOP_SO123_SHIFT                               (0U)
#define FSPI_QOP_SO123_MASK                                (0x1U << FSPI_QOP_SO123_SHIFT)                               /* 0x00000001 */
#define FSPI_QOP_SO123BP_SHIFT                             (1U)
#define FSPI_QOP_SO123BP_MASK                              (0x1U << FSPI_QOP_SO123BP_SHIFT)                             /* 0x00000002 */
/* EXT_CTRL */
#define FSPI_EXT_CTRL_OFFSET                               (0x34U)
#define FSPI_EXT_CTRL_CS_DESEL_CTRL_SHIFT                  (0U)
#define FSPI_EXT_CTRL_CS_DESEL_CTRL_MASK                   (0xFU << FSPI_EXT_CTRL_CS_DESEL_CTRL_SHIFT)                  /* 0x0000000F */
#define FSPI_EXT_CTRL_SWITCH_IO_DUMM_CNT_SHIFT             (4U)
#define FSPI_EXT_CTRL_SWITCH_IO_DUMM_CNT_MASK              (0xFU << FSPI_EXT_CTRL_SWITCH_IO_DUMM_CNT_SHIFT)             /* 0x000000F0 */
#define FSPI_EXT_CTRL_SWITCH_IO_O2I_CNT_SHIFT              (8U)
#define FSPI_EXT_CTRL_SWITCH_IO_O2I_CNT_MASK               (0xFU << FSPI_EXT_CTRL_SWITCH_IO_O2I_CNT_SHIFT)              /* 0x00000F00 */
#define FSPI_EXT_CTRL_TRANS_INT_MODE_SHIFT                 (13U)
#define FSPI_EXT_CTRL_TRANS_INT_MODE_MASK                  (0x1U << FSPI_EXT_CTRL_TRANS_INT_MODE_SHIFT)                 /* 0x00002000 */
#define FSPI_EXT_CTRL_SR_GEN_MODE_SHIFT                    (14U)
#define FSPI_EXT_CTRL_SR_GEN_MODE_MASK                     (0x1U << FSPI_EXT_CTRL_SR_GEN_MODE_SHIFT)                    /* 0x00004000 */
/* POLL_CTRL */
#define FSPI_POLL_CTRL_OFFSET                              (0x38U)
#define FSPI_POLL_CTRL_ST_POLL_EN_SHIFT                    (0U)
#define FSPI_POLL_CTRL_ST_POLL_EN_MASK                     (0x1U << FSPI_POLL_CTRL_ST_POLL_EN_SHIFT)                    /* 0x00000001 */
#define FSPI_POLL_CTRL_POLL_DLY_EN_SHIFT                   (1U)
#define FSPI_POLL_CTRL_POLL_DLY_EN_MASK                    (0x1U << FSPI_POLL_CTRL_POLL_DLY_EN_SHIFT)                   /* 0x00000002 */
#define FSPI_POLL_CTRL_ST_POLL_CMD_PARA_SHIFT              (8U)
#define FSPI_POLL_CTRL_ST_POLL_CMD_PARA_MASK               (0xFFU << FSPI_POLL_CTRL_ST_POLL_CMD_PARA_SHIFT)             /* 0x0000FF00 */
#define FSPI_POLL_CTRL_ST_POLL_EXPECT_DATA_SHIFT           (16U)
#define FSPI_POLL_CTRL_ST_POLL_EXPECT_DATA_MASK            (0xFFU << FSPI_POLL_CTRL_ST_POLL_EXPECT_DATA_SHIFT)          /* 0x00FF0000 */
#define FSPI_POLL_CTRL_ST_POLL_BIT_COMP_EN_SHIFT           (24U)
#define FSPI_POLL_CTRL_ST_POLL_BIT_COMP_EN_MASK            (0xFFU << FSPI_POLL_CTRL_ST_POLL_BIT_COMP_EN_SHIFT)          /* 0xFF000000 */
/* DLL_CTRL0 */
#define FSPI_DLL_CTRL0_OFFSET                              (0x3CU)
#define FSPI_DLL_CTRL0_SMP_DLL_CFG_SHIFT                   (0U)
#define FSPI_DLL_CTRL0_SMP_DLL_CFG_MASK                    (0xFFU << FSPI_DLL_CTRL0_SMP_DLL_CFG_SHIFT)                  /* 0x000000FF */
#define FSPI_DLL_CTRL0_SCLK_SMP_SEL_SHIFT                  (8U)
#define FSPI_DLL_CTRL0_SCLK_SMP_SEL_MASK                   (0x1U << FSPI_DLL_CTRL0_SCLK_SMP_SEL_SHIFT)                  /* 0x00000100 */
/* HRDYMASK */
#define FSPI_HRDYMASK_OFFSET                               (0x40U)
#define FSPI_HRDYMASK_HRDYMASK_SHIFT                       (0U)
#define FSPI_HRDYMASK_HRDYMASK_MASK                        (0x1U << FSPI_HRDYMASK_HRDYMASK_SHIFT)                       /* 0x00000001 */
/* EXT_AX */
#define FSPI_EXT_AX_OFFSET                                 (0x44U)
#define FSPI_EXT_AX_AX_CANCEL_PAT_SHIFT                    (0U)
#define FSPI_EXT_AX_AX_CANCEL_PAT_MASK                     (0xFFU << FSPI_EXT_AX_AX_CANCEL_PAT_SHIFT)                   /* 0x000000FF */
#define FSPI_EXT_AX_AX_SETUP_PAT_SHIFT                     (8U)
#define FSPI_EXT_AX_AX_SETUP_PAT_MASK                      (0xFFU << FSPI_EXT_AX_AX_SETUP_PAT_SHIFT)                    /* 0x0000FF00 */
/* SCLK_INATM_CNT */
#define FSPI_SCLK_INATM_CNT_OFFSET                         (0x48U)
#define FSPI_SCLK_INATM_CNT_SCLK_INATM_CNT_SHIFT           (0U)
#define FSPI_SCLK_INATM_CNT_SCLK_INATM_CNT_MASK            (0xFFFFFFFFU << FSPI_SCLK_INATM_CNT_SCLK_INATM_CNT_SHIFT)    /* 0xFFFFFFFF */
/* AUTO_RF_CNT */
#define FSPI_AUTO_RF_CNT_OFFSET                            (0x4CU)
#define FSPI_AUTO_RF_CNT_AUTO_RF_CNT_SHIFT                 (0U)
#define FSPI_AUTO_RF_CNT_AUTO_RF_CNT_MASK                  (0xFFFFFFFFU << FSPI_AUTO_RF_CNT_AUTO_RF_CNT_SHIFT)          /* 0xFFFFFFFF */
/* XMMC_WCMD0 */
#define FSPI_XMMC_WCMD0_OFFSET                             (0x50U)
#define FSPI_XMMC_WCMD0_CMD_SHIFT                          (0U)
#define FSPI_XMMC_WCMD0_CMD_MASK                           (0xFFU << FSPI_XMMC_WCMD0_CMD_SHIFT)                         /* 0x000000FF */
#define FSPI_XMMC_WCMD0_DUMM_SHIFT                         (8U)
#define FSPI_XMMC_WCMD0_DUMM_MASK                          (0xFU << FSPI_XMMC_WCMD0_DUMM_SHIFT)                         /* 0x00000F00 */
#define FSPI_XMMC_WCMD0_CONT_SHIFT                         (13U)
#define FSPI_XMMC_WCMD0_CONT_MASK                          (0x1U << FSPI_XMMC_WCMD0_CONT_SHIFT)                         /* 0x00002000 */
#define FSPI_XMMC_WCMD0_ADDRB_SHIFT                        (14U)
#define FSPI_XMMC_WCMD0_ADDRB_MASK                         (0x3U << FSPI_XMMC_WCMD0_ADDRB_SHIFT)                        /* 0x0000C000 */
/* XMMC_RCMD0 */
#define FSPI_XMMC_RCMD0_OFFSET                             (0x54U)
#define FSPI_XMMC_RCMD0_CMD_SHIFT                          (0U)
#define FSPI_XMMC_RCMD0_CMD_MASK                           (0xFFU << FSPI_XMMC_RCMD0_CMD_SHIFT)                         /* 0x000000FF */
#define FSPI_XMMC_RCMD0_DUMM_SHIFT                         (8U)
#define FSPI_XMMC_RCMD0_DUMM_MASK                          (0xFU << FSPI_XMMC_RCMD0_DUMM_SHIFT)                         /* 0x00000F00 */
#define FSPI_XMMC_RCMD0_CONT_SHIFT                         (13U)
#define FSPI_XMMC_RCMD0_CONT_MASK                          (0x1U << FSPI_XMMC_RCMD0_CONT_SHIFT)                         /* 0x00002000 */
#define FSPI_XMMC_RCMD0_ADDRB_SHIFT                        (14U)
#define FSPI_XMMC_RCMD0_ADDRB_MASK                         (0x3U << FSPI_XMMC_RCMD0_ADDRB_SHIFT)                        /* 0x0000C000 */
/* XMMC_CTRL */
#define FSPI_XMMC_CTRL_OFFSET                              (0x58U)
#define FSPI_XMMC_CTRL_DEV_HWEN_SHIFT                      (5U)
#define FSPI_XMMC_CTRL_DEV_HWEN_MASK                       (0x1U << FSPI_XMMC_CTRL_DEV_HWEN_SHIFT)                      /* 0x00000020 */
#define FSPI_XMMC_CTRL_PFT_EN_SHIFT                        (6U)
#define FSPI_XMMC_CTRL_PFT_EN_MASK                         (0x1U << FSPI_XMMC_CTRL_PFT_EN_SHIFT)                        /* 0x00000040 */
/* MODE */
#define FSPI_MODE_OFFSET                                   (0x5CU)
#define FSPI_MODE_XMMC_MODE_EN_SHIFT                       (0U)
#define FSPI_MODE_XMMC_MODE_EN_MASK                        (0x1U << FSPI_MODE_XMMC_MODE_EN_SHIFT)                       /* 0x00000001 */
/* DEVRGN */
#define FSPI_DEVRGN_OFFSET                                 (0x60U)
#define FSPI_DEVRGN_RSIZE_SHIFT                            (0U)
#define FSPI_DEVRGN_RSIZE_MASK                             (0x1FU << FSPI_DEVRGN_RSIZE_SHIFT)                           /* 0x0000001F */
/* DEVSIZE0 */
#define FSPI_DEVSIZE0_OFFSET                               (0x64U)
#define FSPI_DEVSIZE0_DSIZE_SHIFT                          (0U)
#define FSPI_DEVSIZE0_DSIZE_MASK                           (0x1FU << FSPI_DEVSIZE0_DSIZE_SHIFT)                         /* 0x0000001F */
/* TME0 */
#define FSPI_TME0_OFFSET                                   (0x68U)
#define FSPI_TME0_AUTO_RF_EN_SHIFT                         (0U)
#define FSPI_TME0_AUTO_RF_EN_MASK                          (0x1U << FSPI_TME0_AUTO_RF_EN_SHIFT)                         /* 0x00000001 */
#define FSPI_TME0_SCLK_INATM_EN_SHIFT                      (1U)
#define FSPI_TME0_SCLK_INATM_EN_MASK                       (0x1U << FSPI_TME0_SCLK_INATM_EN_SHIFT)                      /* 0x00000002 */
/* POLLDLY_CTRL */
#define FSPI_POLLDLY_CTRL_OFFSET                           (0x6CU)
#define FSPI_POLLDLY_CTRL_CNT_SHIFT                        (0U)
#define FSPI_POLLDLY_CTRL_CNT_MASK                         (0x7FFFFFFFU << FSPI_POLLDLY_CTRL_CNT_SHIFT)                 /* 0x7FFFFFFF */
#define FSPI_POLLDLY_CTRL_POLLDLY_IP_SHIFT                 (31U)
#define FSPI_POLLDLY_CTRL_POLLDLY_IP_MASK                  (0x1U << FSPI_POLLDLY_CTRL_POLLDLY_IP_SHIFT)                 /* 0x80000000 */
/* DMATR */
#define FSPI_DMATR_OFFSET                                  (0x80U)
#define FSPI_DMATR_DMATR_SHIFT                             (0U)
#define FSPI_DMATR_DMATR_MASK                              (0x1U << FSPI_DMATR_DMATR_SHIFT)                             /* 0x00000001 */
/* DMAADDR */
#define FSPI_DMAADDR_OFFSET                                (0x84U)
#define FSPI_DMAADDR_DMAADDR_SHIFT                         (0U)
#define FSPI_DMAADDR_DMAADDR_MASK                          (0xFFFFFFFFU << FSPI_DMAADDR_DMAADDR_SHIFT)                  /* 0xFFFFFFFF */
/* POLL_DATA */
#define FSPI_POLL_DATA_OFFSET                              (0x90U)
#define FSPI_POLL_DATA                                     (0x0U)
#define FSPI_POLL_DATA_POLL_DATA_SHIFT                     (0U)
#define FSPI_POLL_DATA_POLL_DATA_MASK                      (0xFFU << FSPI_POLL_DATA_POLL_DATA_SHIFT)                    /* 0x000000FF */
#define FSPI_POLL_DATA_POLL_STA_SHIFT                      (8U)
#define FSPI_POLL_DATA_POLL_STA_MASK                       (0x1U << FSPI_POLL_DATA_POLL_STA_SHIFT)                      /* 0x00000100 */
/* XMMCSR */
#define FSPI_XMMCSR_OFFSET                                 (0x94U)
#define FSPI_XMMCSR_SLOPOVER0_SHIFT                        (0U)
#define FSPI_XMMCSR_SLOPOVER0_MASK                         (0x1U << FSPI_XMMCSR_SLOPOVER0_SHIFT)                        /* 0x00000001 */
#define FSPI_XMMCSR_SLOPOVER1_SHIFT                        (1U)
#define FSPI_XMMCSR_SLOPOVER1_MASK                         (0x1U << FSPI_XMMCSR_SLOPOVER1_SHIFT)                        /* 0x00000002 */
/* CMD */
#define FSPI_CMD_OFFSET                                    (0x100U)
#define FSPI_CMD_CMD_SHIFT                                 (0U)
#define FSPI_CMD_CMD_MASK                                  (0xFFU << FSPI_CMD_CMD_SHIFT)                                /* 0x000000FF */
#define FSPI_CMD_DUMM_SHIFT                                (8U)
#define FSPI_CMD_DUMM_MASK                                 (0xFU << FSPI_CMD_DUMM_SHIFT)                                /* 0x00000F00 */
#define FSPI_CMD_WR_SHIFT                                  (12U)
#define FSPI_CMD_WR_MASK                                   (0x1U << FSPI_CMD_WR_SHIFT)                                  /* 0x00001000 */
#define FSPI_CMD_CONT_SHIFT                                (13U)
#define FSPI_CMD_CONT_MASK                                 (0x1U << FSPI_CMD_CONT_SHIFT)                                /* 0x00002000 */
#define FSPI_CMD_ADDRB_SHIFT                               (14U)
#define FSPI_CMD_ADDRB_MASK                                (0x3U << FSPI_CMD_ADDRB_SHIFT)                               /* 0x0000C000 */
#define FSPI_CMD_TRB_SHIFT                                 (16U)
#define FSPI_CMD_TRB_MASK                                  (0x3FFFU << FSPI_CMD_TRB_SHIFT)                              /* 0x3FFF0000 */
#define FSPI_CMD_CS_SHIFT                                  (30U)
#define FSPI_CMD_CS_MASK                                   (0x3U << FSPI_CMD_CS_SHIFT)                                  /* 0xC0000000 */
/* ADDR */
#define FSPI_ADDR_OFFSET                                   (0x104U)
#define FSPI_ADDR_ADDR_SHIFT                               (0U)
#define FSPI_ADDR_ADDR_MASK                                (0xFFFFFFFFU << FSPI_ADDR_ADDR_SHIFT)                        /* 0xFFFFFFFF */
/* DATA */
#define FSPI_DATA_OFFSET                                   (0x108U)
#define FSPI_DATA_DATA_SHIFT                               (0U)
#define FSPI_DATA_DATA_MASK                                (0xFFFFFFFFU << FSPI_DATA_DATA_SHIFT)                        /* 0xFFFFFFFF */
/* CTRL1 */
#define FSPI_CTRL1_OFFSET                                  (0x200U)
#define FSPI_CTRL1_SPIM_SHIFT                              (0U)
#define FSPI_CTRL1_SPIM_MASK                               (0x1U << FSPI_CTRL1_SPIM_SHIFT)                              /* 0x00000001 */
#define FSPI_CTRL1_SHIFTPHASE_SHIFT                        (1U)
#define FSPI_CTRL1_SHIFTPHASE_MASK                         (0x1U << FSPI_CTRL1_SHIFTPHASE_SHIFT)                        /* 0x00000002 */
#define FSPI_CTRL1_IDLE_CYCLE_SHIFT                        (4U)
#define FSPI_CTRL1_IDLE_CYCLE_MASK                         (0xFU << FSPI_CTRL1_IDLE_CYCLE_SHIFT)                        /* 0x000000F0 */
#define FSPI_CTRL1_CMDB_SHIFT                              (8U)
#define FSPI_CTRL1_CMDB_MASK                               (0x3U << FSPI_CTRL1_CMDB_SHIFT)                              /* 0x00000300 */
#define FSPI_CTRL1_ADRB_SHIFT                              (10U)
#define FSPI_CTRL1_ADRB_MASK                               (0x3U << FSPI_CTRL1_ADRB_SHIFT)                              /* 0x00000C00 */
#define FSPI_CTRL1_DATB_SHIFT                              (12U)
#define FSPI_CTRL1_DATB_MASK                               (0x3U << FSPI_CTRL1_DATB_SHIFT)                              /* 0x00003000 */
/* AX1 */
#define FSPI_AX1_OFFSET                                    (0x214U)
#define FSPI_AX1_AX_SHIFT                                  (0U)
#define FSPI_AX1_AX_MASK                                   (0xFFU << FSPI_AX1_AX_SHIFT)                                 /* 0x000000FF */
/* ABIT1 */
#define FSPI_ABIT1_OFFSET                                  (0x218U)
#define FSPI_ABIT1_ABIT_SHIFT                              (0U)
#define FSPI_ABIT1_ABIT_MASK                               (0x1FU << FSPI_ABIT1_ABIT_SHIFT)                             /* 0x0000001F */
/* DLL_CTRL1 */
#define FSPI_DLL_CTRL1_OFFSET                              (0x23CU)
#define FSPI_DLL_CTRL1_SMP_DLL_CFG_SHIFT                   (0U)
#define FSPI_DLL_CTRL1_SMP_DLL_CFG_MASK                    (0xFFU << FSPI_DLL_CTRL1_SMP_DLL_CFG_SHIFT)                  /* 0x000000FF */
#define FSPI_DLL_CTRL1_SCLK_SMP_SEL_SHIFT                  (8U)
#define FSPI_DLL_CTRL1_SCLK_SMP_SEL_MASK                   (0x1U << FSPI_DLL_CTRL1_SCLK_SMP_SEL_SHIFT)                  /* 0x00000100 */
/* XMMC_WCMD1 */
#define FSPI_XMMC_WCMD1_OFFSET                             (0x250U)
#define FSPI_XMMC_WCMD1_CMD_SHIFT                          (0U)
#define FSPI_XMMC_WCMD1_CMD_MASK                           (0xFFU << FSPI_XMMC_WCMD1_CMD_SHIFT)                         /* 0x000000FF */
#define FSPI_XMMC_WCMD1_DUMM_SHIFT                         (8U)
#define FSPI_XMMC_WCMD1_DUMM_MASK                          (0xFU << FSPI_XMMC_WCMD1_DUMM_SHIFT)                         /* 0x00000F00 */
#define FSPI_XMMC_WCMD1_CONT_SHIFT                         (13U)
#define FSPI_XMMC_WCMD1_CONT_MASK                          (0x1U << FSPI_XMMC_WCMD1_CONT_SHIFT)                         /* 0x00002000 */
#define FSPI_XMMC_WCMD1_ADDRB_SHIFT                        (14U)
#define FSPI_XMMC_WCMD1_ADDRB_MASK                         (0x3U << FSPI_XMMC_WCMD1_ADDRB_SHIFT)                        /* 0x0000C000 */
/* XMMC_RCMD1 */
#define FSPI_XMMC_RCMD1_OFFSET                             (0x254U)
#define FSPI_XMMC_RCMD1_CMD_SHIFT                          (0U)
#define FSPI_XMMC_RCMD1_CMD_MASK                           (0xFFU << FSPI_XMMC_RCMD1_CMD_SHIFT)                         /* 0x000000FF */
#define FSPI_XMMC_RCMD1_DUMM_SHIFT                         (8U)
#define FSPI_XMMC_RCMD1_DUMM_MASK                          (0xFU << FSPI_XMMC_RCMD1_DUMM_SHIFT)                         /* 0x00000F00 */
#define FSPI_XMMC_RCMD1_CONT_SHIFT                         (13U)
#define FSPI_XMMC_RCMD1_CONT_MASK                          (0x1U << FSPI_XMMC_RCMD1_CONT_SHIFT)                         /* 0x00002000 */
#define FSPI_XMMC_RCMD1_ADDRB_SHIFT                        (14U)
#define FSPI_XMMC_RCMD1_ADDRB_MASK                         (0x3U << FSPI_XMMC_RCMD1_ADDRB_SHIFT)                        /* 0x0000C000 */
/* DEVSIZE1 */
#define FSPI_DEVSIZE1_OFFSET                               (0x264U)
#define FSPI_DEVSIZE1_DSIZE_SHIFT                          (0U)
#define FSPI_DEVSIZE1_DSIZE_MASK                           (0x1FU << FSPI_DEVSIZE1_DSIZE_SHIFT)                         /* 0x0000001F */
/* TME1 */
#define FSPI_TME1_OFFSET                                   (0x268U)
#define FSPI_TME1_AUTO_RF_EN_SHIFT                         (0U)
#define FSPI_TME1_AUTO_RF_EN_MASK                          (0x1U << FSPI_TME1_AUTO_RF_EN_SHIFT)                         /* 0x00000001 */
#define FSPI_TME1_SCLK_INATM_EN_SHIFT                      (1U)
#define FSPI_TME1_SCLK_INATM_EN_MASK                       (0x1U << FSPI_TME1_SCLK_INATM_EN_SHIFT)                      /* 0x00000002 */
/******************************************MMC*******************************************/
/* CTRL */
#define MMC_CTRL_OFFSET                                    (0x0U)
#define MMC_CTRL_CONTROLLER_RESET_SHIFT                    (0U)
#define MMC_CTRL_CONTROLLER_RESET_MASK                     (0x1U << MMC_CTRL_CONTROLLER_RESET_SHIFT)                    /* 0x00000001 */
#define MMC_CTRL_FIFO_RESET_SHIFT                          (1U)
#define MMC_CTRL_FIFO_RESET_MASK                           (0x1U << MMC_CTRL_FIFO_RESET_SHIFT)                          /* 0x00000002 */
#define MMC_CTRL_DMA_RESET_SHIFT                           (2U)
#define MMC_CTRL_DMA_RESET_MASK                            (0x1U << MMC_CTRL_DMA_RESET_SHIFT)                           /* 0x00000004 */
#define MMC_CTRL_INT_ENABLE_SHIFT                          (4U)
#define MMC_CTRL_INT_ENABLE_MASK                           (0x1U << MMC_CTRL_INT_ENABLE_SHIFT)                          /* 0x00000010 */
#define MMC_CTRL_DMA_ENABLE_SHIFT                          (5U)
#define MMC_CTRL_DMA_ENABLE_MASK                           (0x1U << MMC_CTRL_DMA_ENABLE_SHIFT)                          /* 0x00000020 */
#define MMC_CTRL_READ_WAIT_SHIFT                           (6U)
#define MMC_CTRL_READ_WAIT_MASK                            (0x1U << MMC_CTRL_READ_WAIT_SHIFT)                           /* 0x00000040 */
#define MMC_CTRL_SEND_IRQ_RESPONSE_SHIFT                   (7U)
#define MMC_CTRL_SEND_IRQ_RESPONSE_MASK                    (0x1U << MMC_CTRL_SEND_IRQ_RESPONSE_SHIFT)                   /* 0x00000080 */
#define MMC_CTRL_ABORT_READ_DATA_SHIFT                     (8U)
#define MMC_CTRL_ABORT_READ_DATA_MASK                      (0x1U << MMC_CTRL_ABORT_READ_DATA_SHIFT)                     /* 0x00000100 */
#define MMC_CTRL_SEND_CCSD_SHIFT                           (9U)
#define MMC_CTRL_SEND_CCSD_MASK                            (0x1U << MMC_CTRL_SEND_CCSD_SHIFT)                           /* 0x00000200 */
#define MMC_CTRL_SEND_AUTO_STOP_CCSD_SHIFT                 (10U)
#define MMC_CTRL_SEND_AUTO_STOP_CCSD_MASK                  (0x1U << MMC_CTRL_SEND_AUTO_STOP_CCSD_SHIFT)                 /* 0x00000400 */
#define MMC_CTRL_CEATA_DEVICE_INTERRUPT_STATUS_SHIFT       (11U)
#define MMC_CTRL_CEATA_DEVICE_INTERRUPT_STATUS_MASK        (0x1U << MMC_CTRL_CEATA_DEVICE_INTERRUPT_STATUS_SHIFT)       /* 0x00000800 */
#define MMC_CTRL_USE_INTERNAL_DMAC_SHIFT                   (25U)
#define MMC_CTRL_USE_INTERNAL_DMAC_MASK                    (0x1U << MMC_CTRL_USE_INTERNAL_DMAC_SHIFT)                   /* 0x02000000 */
/* PWREN */
#define MMC_PWREN_OFFSET                                   (0x4U)
#define MMC_PWREN_POWER_ENABLE_SHIFT                       (0U)
#define MMC_PWREN_POWER_ENABLE_MASK                        (0x1U << MMC_PWREN_POWER_ENABLE_SHIFT)                       /* 0x00000001 */
/* CLKDIV */
#define MMC_CLKDIV_OFFSET                                  (0x8U)
#define MMC_CLKDIV_CLK_DIVIDER0_SHIFT                      (0U)
#define MMC_CLKDIV_CLK_DIVIDER0_MASK                       (0xFFU << MMC_CLKDIV_CLK_DIVIDER0_SHIFT)                     /* 0x000000FF */
/* CLKSRC */
#define MMC_CLKSRC_OFFSET                                  (0xCU)
#define MMC_CLKSRC_CLK_SOURCE_SHIFT                        (0U)
#define MMC_CLKSRC_CLK_SOURCE_MASK                         (0x3U << MMC_CLKSRC_CLK_SOURCE_SHIFT)                        /* 0x00000003 */
/* CLKENA */
#define MMC_CLKENA_OFFSET                                  (0x10U)
#define MMC_CLKENA_CCLK_ENABLE_SHIFT                       (0U)
#define MMC_CLKENA_CCLK_ENABLE_MASK                        (0x1U << MMC_CLKENA_CCLK_ENABLE_SHIFT)                       /* 0x00000001 */
#define MMC_CLKENA_CCLK_LOW_POWER_SHIFT                    (16U)
#define MMC_CLKENA_CCLK_LOW_POWER_MASK                     (0x1U << MMC_CLKENA_CCLK_LOW_POWER_SHIFT)                    /* 0x00010000 */
/* TMOUT */
#define MMC_TMOUT_OFFSET                                   (0x14U)
#define MMC_TMOUT_RESPONSE_TIMEOUT_SHIFT                   (0U)
#define MMC_TMOUT_RESPONSE_TIMEOUT_MASK                    (0xFFU << MMC_TMOUT_RESPONSE_TIMEOUT_SHIFT)                  /* 0x000000FF */
#define MMC_TMOUT_DATA_TIMEOUT_SHIFT                       (8U)
#define MMC_TMOUT_DATA_TIMEOUT_MASK                        (0xFFFFFFU << MMC_TMOUT_DATA_TIMEOUT_SHIFT)                  /* 0xFFFFFF00 */
/* CTYPE */
#define MMC_CTYPE_OFFSET                                   (0x18U)
#define MMC_CTYPE_CARD_WIDTH_SHIFT                         (0U)
#define MMC_CTYPE_CARD_WIDTH_MASK                          (0x1U << MMC_CTYPE_CARD_WIDTH_SHIFT)                         /* 0x00000001 */
#define MMC_CTYPE_CARD_WIDTH_8_SHIFT                       (16U)
#define MMC_CTYPE_CARD_WIDTH_8_MASK                        (0x1U << MMC_CTYPE_CARD_WIDTH_8_SHIFT)                       /* 0x00010000 */
/* BLKSIZ */
#define MMC_BLKSIZ_OFFSET                                  (0x1CU)
#define MMC_BLKSIZ_BLOCK_SIZE_SHIFT                        (0U)
#define MMC_BLKSIZ_BLOCK_SIZE_MASK                         (0xFFFFU << MMC_BLKSIZ_BLOCK_SIZE_SHIFT)                     /* 0x0000FFFF */
/* BYTCNT */
#define MMC_BYTCNT_OFFSET                                  (0x20U)
#define MMC_BYTCNT_BYTE_COUNT_SHIFT                        (0U)
#define MMC_BYTCNT_BYTE_COUNT_MASK                         (0xFFFFFFFFU << MMC_BYTCNT_BYTE_COUNT_SHIFT)                 /* 0xFFFFFFFF */
/* INTMASK */
#define MMC_INTMASK_OFFSET                                 (0x24U)
#define MMC_INTMASK_INT_MASK_SHIFT                         (0U)
#define MMC_INTMASK_INT_MASK_MASK                          (0xFFFFU << MMC_INTMASK_INT_MASK_SHIFT)                      /* 0x0000FFFF */
#define MMC_INTMASK_DATA_NOBUSY_INT_MASK_SHIFT             (16U)
#define MMC_INTMASK_DATA_NOBUSY_INT_MASK_MASK              (0x1U << MMC_INTMASK_DATA_NOBUSY_INT_MASK_SHIFT)             /* 0x00010000 */
#define MMC_INTMASK_SDIO_INT_MASK_SHIFT                    (24U)
#define MMC_INTMASK_SDIO_INT_MASK_MASK                     (0x1U << MMC_INTMASK_SDIO_INT_MASK_SHIFT)                    /* 0x01000000 */
/* CMDARG */
#define MMC_CMDARG_OFFSET                                  (0x28U)
#define MMC_CMDARG_CMD_ARG_SHIFT                           (0U)
#define MMC_CMDARG_CMD_ARG_MASK                            (0xFFFFFFFFU << MMC_CMDARG_CMD_ARG_SHIFT)                    /* 0xFFFFFFFF */
/* CMD */
#define MMC_CMD_OFFSET                                     (0x2CU)
#define MMC_CMD_CMD_INDEX_SHIFT                            (0U)
#define MMC_CMD_CMD_INDEX_MASK                             (0x3FU << MMC_CMD_CMD_INDEX_SHIFT)                           /* 0x0000003F */
#define MMC_CMD_RESPONSE_EXPECT_SHIFT                      (6U)
#define MMC_CMD_RESPONSE_EXPECT_MASK                       (0x1U << MMC_CMD_RESPONSE_EXPECT_SHIFT)                      /* 0x00000040 */
#define MMC_CMD_RESPONSE_LENGTH_SHIFT                      (7U)
#define MMC_CMD_RESPONSE_LENGTH_MASK                       (0x1U << MMC_CMD_RESPONSE_LENGTH_SHIFT)                      /* 0x00000080 */
#define MMC_CMD_CHECK_RESPONSE_CRC_SHIFT                   (8U)
#define MMC_CMD_CHECK_RESPONSE_CRC_MASK                    (0x1U << MMC_CMD_CHECK_RESPONSE_CRC_SHIFT)                   /* 0x00000100 */
#define MMC_CMD_DATA_EXPECTED_SHIFT                        (9U)
#define MMC_CMD_DATA_EXPECTED_MASK                         (0x1U << MMC_CMD_DATA_EXPECTED_SHIFT)                        /* 0x00000200 */
#define MMC_CMD_WR_SHIFT                                   (10U)
#define MMC_CMD_WR_MASK                                    (0x1U << MMC_CMD_WR_SHIFT)                                   /* 0x00000400 */
#define MMC_CMD_TRANSFER_MODE_SHIFT                        (11U)
#define MMC_CMD_TRANSFER_MODE_MASK                         (0x1U << MMC_CMD_TRANSFER_MODE_SHIFT)                        /* 0x00000800 */
#define MMC_CMD_SEND_AUTO_STOP_SHIFT                       (12U)
#define MMC_CMD_SEND_AUTO_STOP_MASK                        (0x1U << MMC_CMD_SEND_AUTO_STOP_SHIFT)                       /* 0x00001000 */
#define MMC_CMD_WAIT_PRVDATA_COMPLETE_SHIFT                (13U)
#define MMC_CMD_WAIT_PRVDATA_COMPLETE_MASK                 (0x1U << MMC_CMD_WAIT_PRVDATA_COMPLETE_SHIFT)                /* 0x00002000 */
#define MMC_CMD_STOP_ABORT_CMD_SHIFT                       (14U)
#define MMC_CMD_STOP_ABORT_CMD_MASK                        (0x1U << MMC_CMD_STOP_ABORT_CMD_SHIFT)                       /* 0x00004000 */
#define MMC_CMD_SEND_INITIALIZATION_SHIFT                  (15U)
#define MMC_CMD_SEND_INITIALIZATION_MASK                   (0x1U << MMC_CMD_SEND_INITIALIZATION_SHIFT)                  /* 0x00008000 */
#define MMC_CMD_UPDATE_CLOCK_REGS_ONLY_SHIFT               (21U)
#define MMC_CMD_UPDATE_CLOCK_REGS_ONLY_MASK                (0x1U << MMC_CMD_UPDATE_CLOCK_REGS_ONLY_SHIFT)               /* 0x00200000 */
#define MMC_CMD_READ_CEATA_DEVICE_SHIFT                    (22U)
#define MMC_CMD_READ_CEATA_DEVICE_MASK                     (0x1U << MMC_CMD_READ_CEATA_DEVICE_SHIFT)                    /* 0x00400000 */
#define MMC_CMD_CCS_EXPECTED_SHIFT                         (23U)
#define MMC_CMD_CCS_EXPECTED_MASK                          (0x1U << MMC_CMD_CCS_EXPECTED_SHIFT)                         /* 0x00800000 */
#define MMC_CMD_ENABLE_BOOT_SHIFT                          (24U)
#define MMC_CMD_ENABLE_BOOT_MASK                           (0x1U << MMC_CMD_ENABLE_BOOT_SHIFT)                          /* 0x01000000 */
#define MMC_CMD_EXPECT_BOOT_ACK_SHIFT                      (25U)
#define MMC_CMD_EXPECT_BOOT_ACK_MASK                       (0x1U << MMC_CMD_EXPECT_BOOT_ACK_SHIFT)                      /* 0x02000000 */
#define MMC_CMD_DISABLE_BOOT_SHIFT                         (26U)
#define MMC_CMD_DISABLE_BOOT_MASK                          (0x1U << MMC_CMD_DISABLE_BOOT_SHIFT)                         /* 0x04000000 */
#define MMC_CMD_BOOT_MODE_SHIFT                            (27U)
#define MMC_CMD_BOOT_MODE_MASK                             (0x1U << MMC_CMD_BOOT_MODE_SHIFT)                            /* 0x08000000 */
#define MMC_CMD_VOLT_SWITCH_SHIFT                          (28U)
#define MMC_CMD_VOLT_SWITCH_MASK                           (0x1U << MMC_CMD_VOLT_SWITCH_SHIFT)                          /* 0x10000000 */
#define MMC_CMD_USE_HOLD_REG_SHIFT                         (29U)
#define MMC_CMD_USE_HOLD_REG_MASK                          (0x1U << MMC_CMD_USE_HOLD_REG_SHIFT)                         /* 0x20000000 */
#define MMC_CMD_START_CMD_SHIFT                            (31U)
#define MMC_CMD_START_CMD_MASK                             (0x1U << MMC_CMD_START_CMD_SHIFT)                            /* 0x80000000 */
/* RESP0 */
#define MMC_RESP0_OFFSET                                   (0x30U)
#define MMC_RESP0                                          (0x0U)
#define MMC_RESP0_RESPONSE0_SHIFT                          (0U)
#define MMC_RESP0_RESPONSE0_MASK                           (0xFFFFFFFFU << MMC_RESP0_RESPONSE0_SHIFT)                   /* 0xFFFFFFFF */
/* RESP1 */
#define MMC_RESP1_OFFSET                                   (0x34U)
#define MMC_RESP1                                          (0x0U)
#define MMC_RESP1_RESPONSE_SHIFT                           (0U)
#define MMC_RESP1_RESPONSE_MASK                            (0xFFFFFFFFU << MMC_RESP1_RESPONSE_SHIFT)                    /* 0xFFFFFFFF */
/* RESP2 */
#define MMC_RESP2_OFFSET                                   (0x38U)
#define MMC_RESP2                                          (0x0U)
#define MMC_RESP2_RESPONSE2_SHIFT                          (0U)
#define MMC_RESP2_RESPONSE2_MASK                           (0xFFFFFFFFU << MMC_RESP2_RESPONSE2_SHIFT)                   /* 0xFFFFFFFF */
/* RESP3 */
#define MMC_RESP3_OFFSET                                   (0x3CU)
#define MMC_RESP3                                          (0x0U)
#define MMC_RESP3_RESPONSE3_SHIFT                          (0U)
#define MMC_RESP3_RESPONSE3_MASK                           (0xFFFFFFFFU << MMC_RESP3_RESPONSE3_SHIFT)                   /* 0xFFFFFFFF */
/* MINTSTS */
#define MMC_MINTSTS_OFFSET                                 (0x40U)
#define MMC_MINTSTS_INT_STATUS_SHIFT                       (0U)
#define MMC_MINTSTS_INT_STATUS_MASK                        (0xFFFFU << MMC_MINTSTS_INT_STATUS_SHIFT)                    /* 0x0000FFFF */
#define MMC_MINTSTS_DATA_NOBUSY_INT_STATUS_SHIFT           (16U)
#define MMC_MINTSTS_DATA_NOBUSY_INT_STATUS_MASK            (0x1U << MMC_MINTSTS_DATA_NOBUSY_INT_STATUS_SHIFT)           /* 0x00010000 */
#define MMC_MINTSTS_SDIO_INTERRUPT_SHIFT                   (24U)
#define MMC_MINTSTS_SDIO_INTERRUPT_MASK                    (0x1U << MMC_MINTSTS_SDIO_INTERRUPT_SHIFT)                   /* 0x01000000 */
/* RINTSTS */
#define MMC_RINTSTS_OFFSET                                 (0x44U)
#define MMC_RINTSTS_INT_STATUS_SHIFT                       (0U)
#define MMC_RINTSTS_INT_STATUS_MASK                        (0xFFFFU << MMC_RINTSTS_INT_STATUS_SHIFT)                    /* 0x0000FFFF */
#define MMC_RINTSTS_DATA_NOBUSY_INT_STATUS_SHIFT           (16U)
#define MMC_RINTSTS_DATA_NOBUSY_INT_STATUS_MASK            (0x1U << MMC_RINTSTS_DATA_NOBUSY_INT_STATUS_SHIFT)           /* 0x00010000 */
#define MMC_RINTSTS_SDIO_INTERRUPT_SHIFT                   (24U)
#define MMC_RINTSTS_SDIO_INTERRUPT_MASK                    (0x1U << MMC_RINTSTS_SDIO_INTERRUPT_SHIFT)                   /* 0x01000000 */
/* STATUS */
#define MMC_STATUS_OFFSET                                  (0x48U)
#define MMC_STATUS                                         (0x506U)
#define MMC_STATUS_FIFO_RX_WATERMARK_SHIFT                 (0U)
#define MMC_STATUS_FIFO_RX_WATERMARK_MASK                  (0x1U << MMC_STATUS_FIFO_RX_WATERMARK_SHIFT)                 /* 0x00000001 */
#define MMC_STATUS_FIFO_TX_WATERMARK_SHIFT                 (1U)
#define MMC_STATUS_FIFO_TX_WATERMARK_MASK                  (0x1U << MMC_STATUS_FIFO_TX_WATERMARK_SHIFT)                 /* 0x00000002 */
#define MMC_STATUS_FIFO_EMPTY_SHIFT                        (2U)
#define MMC_STATUS_FIFO_EMPTY_MASK                         (0x1U << MMC_STATUS_FIFO_EMPTY_SHIFT)                        /* 0x00000004 */
#define MMC_STATUS_FIFO_FULL_SHIFT                         (3U)
#define MMC_STATUS_FIFO_FULL_MASK                          (0x1U << MMC_STATUS_FIFO_FULL_SHIFT)                         /* 0x00000008 */
#define MMC_STATUS_COMMAND_FSM_STATES_SHIFT                (4U)
#define MMC_STATUS_COMMAND_FSM_STATES_MASK                 (0xFU << MMC_STATUS_COMMAND_FSM_STATES_SHIFT)                /* 0x000000F0 */
#define MMC_STATUS_DATA_3_STATUS_SHIFT                     (8U)
#define MMC_STATUS_DATA_3_STATUS_MASK                      (0x1U << MMC_STATUS_DATA_3_STATUS_SHIFT)                     /* 0x00000100 */
#define MMC_STATUS_DATA_BUSY_SHIFT                         (9U)
#define MMC_STATUS_DATA_BUSY_MASK                          (0x1U << MMC_STATUS_DATA_BUSY_SHIFT)                         /* 0x00000200 */
#define MMC_STATUS_DATA_STATE_MC_BUSY_SHIFT                (10U)
#define MMC_STATUS_DATA_STATE_MC_BUSY_MASK                 (0x1U << MMC_STATUS_DATA_STATE_MC_BUSY_SHIFT)                /* 0x00000400 */
#define MMC_STATUS_RESPONSE_INDEX_SHIFT                    (11U)
#define MMC_STATUS_RESPONSE_INDEX_MASK                     (0x3FU << MMC_STATUS_RESPONSE_INDEX_SHIFT)                   /* 0x0001F800 */
#define MMC_STATUS_FIFO_COUNT_SHIFT                        (17U)
#define MMC_STATUS_FIFO_COUNT_MASK                         (0x1FFFU << MMC_STATUS_FIFO_COUNT_SHIFT)                     /* 0x3FFE0000 */
#define MMC_STATUS_DMA_ACK_SHIFT                           (30U)
#define MMC_STATUS_DMA_ACK_MASK                            (0x1U << MMC_STATUS_DMA_ACK_SHIFT)                           /* 0x40000000 */
#define MMC_STATUS_DMA_REQ_SHIFT                           (31U)
#define MMC_STATUS_DMA_REQ_MASK                            (0x1U << MMC_STATUS_DMA_REQ_SHIFT)                           /* 0x80000000 */
/* FIFOTH */
#define MMC_FIFOTH_OFFSET                                  (0x4CU)
#define MMC_FIFOTH_TX_WMARK_SHIFT                          (0U)
#define MMC_FIFOTH_TX_WMARK_MASK                           (0xFFFU << MMC_FIFOTH_TX_WMARK_SHIFT)                        /* 0x00000FFF */
#define MMC_FIFOTH_RX_WMARK_SHIFT                          (16U)
#define MMC_FIFOTH_RX_WMARK_MASK                           (0xFFFU << MMC_FIFOTH_RX_WMARK_SHIFT)                        /* 0x0FFF0000 */
#define MMC_FIFOTH_DMA_MUTIPLE_TRANSACTION_SIZE_SHIFT      (28U)
#define MMC_FIFOTH_DMA_MUTIPLE_TRANSACTION_SIZE_MASK       (0x7U << MMC_FIFOTH_DMA_MUTIPLE_TRANSACTION_SIZE_SHIFT)      /* 0x70000000 */
/* CDETECT */
#define MMC_CDETECT_OFFSET                                 (0x50U)
#define MMC_CDETECT                                        (0x0U)
#define MMC_CDETECT_CARD_DETECT_N_SHIFT                    (0U)
#define MMC_CDETECT_CARD_DETECT_N_MASK                     (0x1U << MMC_CDETECT_CARD_DETECT_N_SHIFT)                    /* 0x00000001 */
/* WRTPRT */
#define MMC_WRTPRT_OFFSET                                  (0x54U)
#define MMC_WRTPRT_WRITE_PROTECT_SHIFT                     (0U)
#define MMC_WRTPRT_WRITE_PROTECT_MASK                      (0x1U << MMC_WRTPRT_WRITE_PROTECT_SHIFT)                     /* 0x00000001 */
/* TCBCNT */
#define MMC_TCBCNT_OFFSET                                  (0x5CU)
#define MMC_TCBCNT                                         (0x0U)
#define MMC_TCBCNT_TRANS_CARD_BYTE_COUNT_SHIFT             (0U)
#define MMC_TCBCNT_TRANS_CARD_BYTE_COUNT_MASK              (0xFFFFFFFFU << MMC_TCBCNT_TRANS_CARD_BYTE_COUNT_SHIFT)      /* 0xFFFFFFFF */
/* TBBCNT */
#define MMC_TBBCNT_OFFSET                                  (0x60U)
#define MMC_TBBCNT                                         (0x0U)
#define MMC_TBBCNT_TRANS_FIFO_BYTE_COUNT_SHIFT             (0U)
#define MMC_TBBCNT_TRANS_FIFO_BYTE_COUNT_MASK              (0xFFFFFFFFU << MMC_TBBCNT_TRANS_FIFO_BYTE_COUNT_SHIFT)      /* 0xFFFFFFFF */
/* DEBNCE */
#define MMC_DEBNCE_OFFSET                                  (0x64U)
#define MMC_DEBNCE_DEBOUNCE_COUNT_SHIFT                    (0U)
#define MMC_DEBNCE_DEBOUNCE_COUNT_MASK                     (0xFFFFFFU << MMC_DEBNCE_DEBOUNCE_COUNT_SHIFT)               /* 0x00FFFFFF */
/* USRID */
#define MMC_USRID_OFFSET                                   (0x68U)
#define MMC_USRID_USRID_SHIFT                              (0U)
#define MMC_USRID_USRID_MASK                               (0xFFFFFFFFU << MMC_USRID_USRID_SHIFT)                       /* 0xFFFFFFFF */
/* VERID */
#define MMC_VERID_OFFSET                                   (0x6CU)
#define MMC_VERID                                          (0x5342270AU)
#define MMC_VERID_VERID_SHIFT                              (0U)
#define MMC_VERID_VERID_MASK                               (0xFFFFFFFFU << MMC_VERID_VERID_SHIFT)                       /* 0xFFFFFFFF */
/* HCON */
#define MMC_HCON_OFFSET                                    (0x70U)
#define MMC_HCON                                           (0x4C47CC1U)
#define MMC_HCON_CARD_TYPE_SHIFT                           (0U)
#define MMC_HCON_CARD_TYPE_MASK                            (0x1U << MMC_HCON_CARD_TYPE_SHIFT)                           /* 0x00000001 */
#define MMC_HCON_CARD_NUM_SHIFT                            (1U)
#define MMC_HCON_CARD_NUM_MASK                             (0x1FU << MMC_HCON_CARD_NUM_SHIFT)                           /* 0x0000003E */
#define MMC_HCON_H_BUS_TYPE_SHIFT                          (6U)
#define MMC_HCON_H_BUS_TYPE_MASK                           (0x1U << MMC_HCON_H_BUS_TYPE_SHIFT)                          /* 0x00000040 */
#define MMC_HCON_H_DATA_WIDTH_SHIFT                        (7U)
#define MMC_HCON_H_DATA_WIDTH_MASK                         (0x7U << MMC_HCON_H_DATA_WIDTH_SHIFT)                        /* 0x00000380 */
#define MMC_HCON_H_ADDR_WIDTH_SHIFT                        (10U)
#define MMC_HCON_H_ADDR_WIDTH_MASK                         (0x3FU << MMC_HCON_H_ADDR_WIDTH_SHIFT)                       /* 0x0000FC00 */
#define MMC_HCON_DMA_INTERFACE_SHIFT                       (16U)
#define MMC_HCON_DMA_INTERFACE_MASK                        (0x3U << MMC_HCON_DMA_INTERFACE_SHIFT)                       /* 0x00030000 */
#define MMC_HCON_GE_DMA_DATA_WIDTH_SHIFT                   (18U)
#define MMC_HCON_GE_DMA_DATA_WIDTH_MASK                    (0x7U << MMC_HCON_GE_DMA_DATA_WIDTH_SHIFT)                   /* 0x001C0000 */
#define MMC_HCON_FIFO_RAM_INSIDE_SHIFT                     (21U)
#define MMC_HCON_FIFO_RAM_INSIDE_MASK                      (0x1U << MMC_HCON_FIFO_RAM_INSIDE_SHIFT)                     /* 0x00200000 */
#define MMC_HCON_IMPL_HOLD_REG_SHIFT                       (22U)
#define MMC_HCON_IMPL_HOLD_REG_MASK                        (0x1U << MMC_HCON_IMPL_HOLD_REG_SHIFT)                       /* 0x00400000 */
#define MMC_HCON_SET_CLK_FALSE_PATH_SHIFT                  (23U)
#define MMC_HCON_SET_CLK_FALSE_PATH_MASK                   (0x1U << MMC_HCON_SET_CLK_FALSE_PATH_SHIFT)                  /* 0x00800000 */
#define MMC_HCON_NUM_CLK_DIV_SHIFT                         (24U)
#define MMC_HCON_NUM_CLK_DIV_MASK                          (0x3U << MMC_HCON_NUM_CLK_DIV_SHIFT)                         /* 0x03000000 */
#define MMC_HCON_AREA_OPTIMIZED_SHIFT                      (26U)
#define MMC_HCON_AREA_OPTIMIZED_MASK                       (0x1U << MMC_HCON_AREA_OPTIMIZED_SHIFT)                      /* 0x04000000 */
/* UHSREG */
#define MMC_UHSREG_OFFSET                                  (0x74U)
#define MMC_UHSREG_DDR_REG_SHIFT                           (16U)
#define MMC_UHSREG_DDR_REG_MASK                            (0x1U << MMC_UHSREG_DDR_REG_SHIFT)                           /* 0x00010000 */
/* RSTN */
#define MMC_RSTN_OFFSET                                    (0x78U)
#define MMC_RSTN_CARD_RESET_SHIFT                          (0U)
#define MMC_RSTN_CARD_RESET_MASK                           (0x1U << MMC_RSTN_CARD_RESET_SHIFT)                          /* 0x00000001 */
/* BMOD */
#define MMC_BMOD_OFFSET                                    (0x80U)
#define MMC_BMOD_SWR_SHIFT                                 (0U)
#define MMC_BMOD_SWR_MASK                                  (0x1U << MMC_BMOD_SWR_SHIFT)                                 /* 0x00000001 */
#define MMC_BMOD_FB_SHIFT                                  (1U)
#define MMC_BMOD_FB_MASK                                   (0x1U << MMC_BMOD_FB_SHIFT)                                  /* 0x00000002 */
#define MMC_BMOD_DSL_SHIFT                                 (2U)
#define MMC_BMOD_DSL_MASK                                  (0x1FU << MMC_BMOD_DSL_SHIFT)                                /* 0x0000007C */
#define MMC_BMOD_DE_SHIFT                                  (7U)
#define MMC_BMOD_DE_MASK                                   (0x1U << MMC_BMOD_DE_SHIFT)                                  /* 0x00000080 */
#define MMC_BMOD_PBL_SHIFT                                 (8U)
#define MMC_BMOD_PBL_MASK                                  (0x7U << MMC_BMOD_PBL_SHIFT)                                 /* 0x00000700 */
/* PLDMND */
#define MMC_PLDMND_OFFSET                                  (0x84U)
#define MMC_PLDMND_PD_SHIFT                                (0U)
#define MMC_PLDMND_PD_MASK                                 (0xFFFFFFFFU << MMC_PLDMND_PD_SHIFT)                         /* 0xFFFFFFFF */
/* DBADDR */
#define MMC_DBADDR_OFFSET                                  (0x88U)
#define MMC_DBADDR_SBL_SHIFT                               (0U)
#define MMC_DBADDR_SBL_MASK                                (0xFFFFFFFFU << MMC_DBADDR_SBL_SHIFT)                        /* 0xFFFFFFFF */
/* IDSTS */
#define MMC_IDSTS_OFFSET                                   (0x8CU)
#define MMC_IDSTS_TI_SHIFT                                 (0U)
#define MMC_IDSTS_TI_MASK                                  (0x1U << MMC_IDSTS_TI_SHIFT)                                 /* 0x00000001 */
#define MMC_IDSTS_RI_SHIFT                                 (1U)
#define MMC_IDSTS_RI_MASK                                  (0x1U << MMC_IDSTS_RI_SHIFT)                                 /* 0x00000002 */
#define MMC_IDSTS_FBE_SHIFT                                (2U)
#define MMC_IDSTS_FBE_MASK                                 (0x1U << MMC_IDSTS_FBE_SHIFT)                                /* 0x00000004 */
#define MMC_IDSTS_DUI_SHIFT                                (4U)
#define MMC_IDSTS_DUI_MASK                                 (0x1U << MMC_IDSTS_DUI_SHIFT)                                /* 0x00000010 */
#define MMC_IDSTS_CES_SHIFT                                (5U)
#define MMC_IDSTS_CES_MASK                                 (0x1U << MMC_IDSTS_CES_SHIFT)                                /* 0x00000020 */
#define MMC_IDSTS_NIS_SHIFT                                (8U)
#define MMC_IDSTS_NIS_MASK                                 (0x1U << MMC_IDSTS_NIS_SHIFT)                                /* 0x00000100 */
#define MMC_IDSTS_AIS_SHIFT                                (9U)
#define MMC_IDSTS_AIS_MASK                                 (0x1U << MMC_IDSTS_AIS_SHIFT)                                /* 0x00000200 */
#define MMC_IDSTS_EB_SHIFT                                 (10U)
#define MMC_IDSTS_EB_MASK                                  (0x7U << MMC_IDSTS_EB_SHIFT)                                 /* 0x00001C00 */
#define MMC_IDSTS_FSM_SHIFT                                (13U)
#define MMC_IDSTS_FSM_MASK                                 (0xFU << MMC_IDSTS_FSM_SHIFT)                                /* 0x0001E000 */
/* IDINTEN */
#define MMC_IDINTEN_OFFSET                                 (0x90U)
#define MMC_IDINTEN_TI_SHIFT                               (0U)
#define MMC_IDINTEN_TI_MASK                                (0x1U << MMC_IDINTEN_TI_SHIFT)                               /* 0x00000001 */
#define MMC_IDINTEN_RI_SHIFT                               (1U)
#define MMC_IDINTEN_RI_MASK                                (0x1U << MMC_IDINTEN_RI_SHIFT)                               /* 0x00000002 */
#define MMC_IDINTEN_FBE_SHIFT                              (2U)
#define MMC_IDINTEN_FBE_MASK                               (0x1U << MMC_IDINTEN_FBE_SHIFT)                              /* 0x00000004 */
#define MMC_IDINTEN_DU_SHIFT                               (4U)
#define MMC_IDINTEN_DU_MASK                                (0x1U << MMC_IDINTEN_DU_SHIFT)                               /* 0x00000010 */
#define MMC_IDINTEN_CES_SHIFT                              (5U)
#define MMC_IDINTEN_CES_MASK                               (0x1U << MMC_IDINTEN_CES_SHIFT)                              /* 0x00000020 */
#define MMC_IDINTEN_NI_SHIFT                               (8U)
#define MMC_IDINTEN_NI_MASK                                (0x1U << MMC_IDINTEN_NI_SHIFT)                               /* 0x00000100 */
#define MMC_IDINTEN_AI_SHIFT                               (9U)
#define MMC_IDINTEN_AI_MASK                                (0x1U << MMC_IDINTEN_AI_SHIFT)                               /* 0x00000200 */
/* DSCADDR */
#define MMC_DSCADDR_OFFSET                                 (0x94U)
#define MMC_DSCADDR_HDA_SHIFT                              (0U)
#define MMC_DSCADDR_HDA_MASK                               (0xFFFFFFFFU << MMC_DSCADDR_HDA_SHIFT)                       /* 0xFFFFFFFF */
/* BUFADDR */
#define MMC_BUFADDR_OFFSET                                 (0x98U)
#define MMC_BUFADDR_HBA_SHIFT                              (0U)
#define MMC_BUFADDR_HBA_MASK                               (0xFFFFFFFFU << MMC_BUFADDR_HBA_SHIFT)                       /* 0xFFFFFFFF */
/* CARDTHRCTL */
#define MMC_CARDTHRCTL_OFFSET                              (0x100U)
#define MMC_CARDTHRCTL_CARD_RD_THRES_EN_SHIFT              (0U)
#define MMC_CARDTHRCTL_CARD_RD_THRES_EN_MASK               (0x1U << MMC_CARDTHRCTL_CARD_RD_THRES_EN_SHIFT)              /* 0x00000001 */
#define MMC_CARDTHRCTL_BUSY_CLR_INT_EN_SHIFT               (1U)
#define MMC_CARDTHRCTL_BUSY_CLR_INT_EN_MASK                (0x1U << MMC_CARDTHRCTL_BUSY_CLR_INT_EN_SHIFT)               /* 0x00000002 */
#define MMC_CARDTHRCTL_CARD_RD_THRES_SHIFT                 (16U)
#define MMC_CARDTHRCTL_CARD_RD_THRES_MASK                  (0xFFFU << MMC_CARDTHRCTL_CARD_RD_THRES_SHIFT)               /* 0x0FFF0000 */
/* BACKEND_POWER */
#define MMC_BACKEND_POWER_OFFSET                           (0x104U)
#define MMC_BACKEND_POWER_BACK_END_POWER_SHIFT             (0U)
#define MMC_BACKEND_POWER_BACK_END_POWER_MASK              (0x1U << MMC_BACKEND_POWER_BACK_END_POWER_SHIFT)             /* 0x00000001 */
/* EMMCDDR_REG */
#define MMC_EMMCDDR_REG_OFFSET                             (0x10CU)
#define MMC_EMMCDDR_REG_HALF_START_BIT_SHIFT               (0U)
#define MMC_EMMCDDR_REG_HALF_START_BIT_MASK                (0x1U << MMC_EMMCDDR_REG_HALF_START_BIT_SHIFT)               /* 0x00000001 */
/* RDYINT_GEN */
#define MMC_RDYINT_GEN_OFFSET                              (0x120U)
#define MMC_RDYINT_GEN_RDYINT_GEN_MAXVAL_SHIFT             (0U)
#define MMC_RDYINT_GEN_RDYINT_GEN_MAXVAL_MASK              (0xFFU << MMC_RDYINT_GEN_RDYINT_GEN_MAXVAL_SHIFT)            /* 0x000000FF */
#define MMC_RDYINT_GEN_RDYINT_GEN_WORKING_SHIFT            (8U)
#define MMC_RDYINT_GEN_RDYINT_GEN_WORKING_MASK             (0x1U << MMC_RDYINT_GEN_RDYINT_GEN_WORKING_SHIFT)            /* 0x00000100 */
#define MMC_RDYINT_GEN_RDYINT_CNT_STATUS_SHIFT             (16U)
#define MMC_RDYINT_GEN_RDYINT_CNT_STATUS_MASK              (0xFFU << MMC_RDYINT_GEN_RDYINT_CNT_STATUS_SHIFT)            /* 0x00FF0000 */
#define MMC_RDYINT_GEN_RDYINT_CNT_FINISH_SHIFT             (24U)
#define MMC_RDYINT_GEN_RDYINT_CNT_FINISH_MASK              (0x1U << MMC_RDYINT_GEN_RDYINT_CNT_FINISH_SHIFT)             /* 0x01000000 */
/* FIFO_BASE */
#define MMC_FIFO_BASE_OFFSET                               (0x200U)
#define MMC_FIFO_BASE_FIFO_BASE_ADDR_SHIFT                 (0U)
#define MMC_FIFO_BASE_FIFO_BASE_ADDR_MASK                  (0xFFFFFFFFU << MMC_FIFO_BASE_FIFO_BASE_ADDR_SHIFT)          /* 0xFFFFFFFF */
/******************************************GPIO******************************************/
/* SWPORT_DR_L */
#define GPIO_SWPORT_DR_L_OFFSET                            (0x0U)
#define GPIO_SWPORT_DR_L_GPIO_SWPORT_DR_LOW_SHIFT          (0U)
#define GPIO_SWPORT_DR_L_GPIO_SWPORT_DR_LOW_MASK           (0xFFFFU << GPIO_SWPORT_DR_L_GPIO_SWPORT_DR_LOW_SHIFT)       /* 0x0000FFFF */
/* SWPORT_DR_H */
#define GPIO_SWPORT_DR_H_OFFSET                            (0x4U)
#define GPIO_SWPORT_DR_H_GPIO_SWPORT_DR_HIGH_SHIFT         (0U)
#define GPIO_SWPORT_DR_H_GPIO_SWPORT_DR_HIGH_MASK          (0xFFFFU << GPIO_SWPORT_DR_H_GPIO_SWPORT_DR_HIGH_SHIFT)      /* 0x0000FFFF */
/* SWPORT_DDR_L */
#define GPIO_SWPORT_DDR_L_OFFSET                           (0x8U)
#define GPIO_SWPORT_DDR_L_GPIO_SWPORT_DDR_LOW_SHIFT        (0U)
#define GPIO_SWPORT_DDR_L_GPIO_SWPORT_DDR_LOW_MASK         (0xFFFFU << GPIO_SWPORT_DDR_L_GPIO_SWPORT_DDR_LOW_SHIFT)     /* 0x0000FFFF */
/* SWPORT_DDR_H */
#define GPIO_SWPORT_DDR_H_OFFSET                           (0xCU)
#define GPIO_SWPORT_DDR_H_GPIO_SWPORT_DDR_HIGH_SHIFT       (0U)
#define GPIO_SWPORT_DDR_H_GPIO_SWPORT_DDR_HIGH_MASK        (0xFFFFU << GPIO_SWPORT_DDR_H_GPIO_SWPORT_DDR_HIGH_SHIFT)    /* 0x0000FFFF */
/* INT_EN_L */
#define GPIO_INT_EN_L_OFFSET                               (0x10U)
#define GPIO_INT_EN_L_GPIO_INT_EN_LOW_SHIFT                (0U)
#define GPIO_INT_EN_L_GPIO_INT_EN_LOW_MASK                 (0xFFFFU << GPIO_INT_EN_L_GPIO_INT_EN_LOW_SHIFT)             /* 0x0000FFFF */
/* INT_EN_H */
#define GPIO_INT_EN_H_OFFSET                               (0x14U)
#define GPIO_INT_EN_H_GPIO_INT_EN_HIGH_SHIFT               (0U)
#define GPIO_INT_EN_H_GPIO_INT_EN_HIGH_MASK                (0xFFFFU << GPIO_INT_EN_H_GPIO_INT_EN_HIGH_SHIFT)            /* 0x0000FFFF */
/* INT_MASK_L */
#define GPIO_INT_MASK_L_OFFSET                             (0x18U)
#define GPIO_INT_MASK_L_GPIO_INT_MASK_LOW_SHIFT            (0U)
#define GPIO_INT_MASK_L_GPIO_INT_MASK_LOW_MASK             (0xFFFFU << GPIO_INT_MASK_L_GPIO_INT_MASK_LOW_SHIFT)         /* 0x0000FFFF */
/* INT_MASK_H */
#define GPIO_INT_MASK_H_OFFSET                             (0x1CU)
#define GPIO_INT_MASK_H_GPIO_INT_MASK_HIGH_SHIFT           (0U)
#define GPIO_INT_MASK_H_GPIO_INT_MASK_HIGH_MASK            (0xFFFFU << GPIO_INT_MASK_H_GPIO_INT_MASK_HIGH_SHIFT)        /* 0x0000FFFF */
/* INT_TYPE_L */
#define GPIO_INT_TYPE_L_OFFSET                             (0x20U)
#define GPIO_INT_TYPE_L_GPIO_INT_TYPE_LOW_SHIFT            (0U)
#define GPIO_INT_TYPE_L_GPIO_INT_TYPE_LOW_MASK             (0xFFFFU << GPIO_INT_TYPE_L_GPIO_INT_TYPE_LOW_SHIFT)         /* 0x0000FFFF */
/* INT_TYPE_H */
#define GPIO_INT_TYPE_H_OFFSET                             (0x24U)
#define GPIO_INT_TYPE_H_GPIO_INT_TYPE_HIGH_SHIFT           (0U)
#define GPIO_INT_TYPE_H_GPIO_INT_TYPE_HIGH_MASK            (0xFFFFU << GPIO_INT_TYPE_H_GPIO_INT_TYPE_HIGH_SHIFT)        /* 0x0000FFFF */
/* INT_POLARITY_L */
#define GPIO_INT_POLARITY_L_OFFSET                         (0x28U)
#define GPIO_INT_POLARITY_L_GPIO_INT_POLARITY_LOW_SHIFT    (0U)
#define GPIO_INT_POLARITY_L_GPIO_INT_POLARITY_LOW_MASK     (0xFFFFU << GPIO_INT_POLARITY_L_GPIO_INT_POLARITY_LOW_SHIFT) /* 0x0000FFFF */
/* INT_POLARITY_H */
#define GPIO_INT_POLARITY_H_OFFSET                         (0x2CU)
#define GPIO_INT_POLARITY_H_GPIO_INT_POLARITY_HIGH_SHIFT   (0U)
#define GPIO_INT_POLARITY_H_GPIO_INT_POLARITY_HIGH_MASK    (0xFFFFU << GPIO_INT_POLARITY_H_GPIO_INT_POLARITY_HIGH_SHIFT) /* 0x0000FFFF */
/* INT_BOTHEDGE_L */
#define GPIO_INT_BOTHEDGE_L_OFFSET                         (0x30U)
#define GPIO_INT_BOTHEDGE_L_GPIO_INT_BOTHEDGE_LOW_SHIFT    (0U)
#define GPIO_INT_BOTHEDGE_L_GPIO_INT_BOTHEDGE_LOW_MASK     (0xFFFFU << GPIO_INT_BOTHEDGE_L_GPIO_INT_BOTHEDGE_LOW_SHIFT) /* 0x0000FFFF */
/* INT_BOTHEDGE_H */
#define GPIO_INT_BOTHEDGE_H_OFFSET                         (0x34U)
#define GPIO_INT_BOTHEDGE_H_GPIO_INT_BOTHEDGE_HIGH_SHIFT   (0U)
#define GPIO_INT_BOTHEDGE_H_GPIO_INT_BOTHEDGE_HIGH_MASK    (0xFFFFU << GPIO_INT_BOTHEDGE_H_GPIO_INT_BOTHEDGE_HIGH_SHIFT) /* 0x0000FFFF */
/* DEBOUNCE_L */
#define GPIO_DEBOUNCE_L_OFFSET                             (0x38U)
#define GPIO_DEBOUNCE_L_GPIO_DEBOUNCE_LOW_SHIFT            (0U)
#define GPIO_DEBOUNCE_L_GPIO_DEBOUNCE_LOW_MASK             (0xFFFFU << GPIO_DEBOUNCE_L_GPIO_DEBOUNCE_LOW_SHIFT)         /* 0x0000FFFF */
/* DEBOUNCE_H */
#define GPIO_DEBOUNCE_H_OFFSET                             (0x3CU)
#define GPIO_DEBOUNCE_H_GPIO_DEBOUNCE_HIGH_SHIFT           (0U)
#define GPIO_DEBOUNCE_H_GPIO_DEBOUNCE_HIGH_MASK            (0xFFFFU << GPIO_DEBOUNCE_H_GPIO_DEBOUNCE_HIGH_SHIFT)        /* 0x0000FFFF */
/* DBCLK_DIV_EN_L */
#define GPIO_DBCLK_DIV_EN_L_OFFSET                         (0x40U)
#define GPIO_DBCLK_DIV_EN_L_GPIO_DBCLK_DIV_EN_LOW_SHIFT    (0U)
#define GPIO_DBCLK_DIV_EN_L_GPIO_DBCLK_DIV_EN_LOW_MASK     (0xFFFFU << GPIO_DBCLK_DIV_EN_L_GPIO_DBCLK_DIV_EN_LOW_SHIFT) /* 0x0000FFFF */
/* DBCLK_DIV_EN_H */
#define GPIO_DBCLK_DIV_EN_H_OFFSET                         (0x44U)
#define GPIO_DBCLK_DIV_EN_H_GPIO_DBCLK_DIV_EN_HIGH_SHIFT   (0U)
#define GPIO_DBCLK_DIV_EN_H_GPIO_DBCLK_DIV_EN_HIGH_MASK    (0xFFFFU << GPIO_DBCLK_DIV_EN_H_GPIO_DBCLK_DIV_EN_HIGH_SHIFT) /* 0x0000FFFF */
/* DBCLK_DIV_CON */
#define GPIO_DBCLK_DIV_CON_OFFSET                          (0x48U)
#define GPIO_DBCLK_DIV_CON_GPIO_DBCLK_DIV_CON_SHIFT        (0U)
#define GPIO_DBCLK_DIV_CON_GPIO_DBCLK_DIV_CON_MASK         (0xFFFFFFU << GPIO_DBCLK_DIV_CON_GPIO_DBCLK_DIV_CON_SHIFT)   /* 0x00FFFFFF */
/* INT_STATUS */
#define GPIO_INT_STATUS_OFFSET                             (0x50U)
#define GPIO_INT_STATUS                                    (0x0U)
#define GPIO_INT_STATUS_GPIO_INT_STATUS_SHIFT              (0U)
#define GPIO_INT_STATUS_GPIO_INT_STATUS_MASK               (0xFFFFFFFFU << GPIO_INT_STATUS_GPIO_INT_STATUS_SHIFT)       /* 0xFFFFFFFF */
/* INT_RAWSTATUS */
#define GPIO_INT_RAWSTATUS_OFFSET                          (0x58U)
#define GPIO_INT_RAWSTATUS                                 (0x0U)
#define GPIO_INT_RAWSTATUS_GPIO_INT_RAWSTATUS_SHIFT        (0U)
#define GPIO_INT_RAWSTATUS_GPIO_INT_RAWSTATUS_MASK         (0xFFFFFFFFU << GPIO_INT_RAWSTATUS_GPIO_INT_RAWSTATUS_SHIFT) /* 0xFFFFFFFF */
/* PORT_EOI_L */
#define GPIO_PORT_EOI_L_OFFSET                             (0x60U)
#define GPIO_PORT_EOI_L_GPIO_PORT_EOI_LOW_SHIFT            (0U)
#define GPIO_PORT_EOI_L_GPIO_PORT_EOI_LOW_MASK             (0xFFFFU << GPIO_PORT_EOI_L_GPIO_PORT_EOI_LOW_SHIFT)         /* 0x0000FFFF */
/* PORT_EOI_H */
#define GPIO_PORT_EOI_H_OFFSET                             (0x64U)
#define GPIO_PORT_EOI_H_GPIO_PORT_EOI_HIGH_SHIFT           (0U)
#define GPIO_PORT_EOI_H_GPIO_PORT_EOI_HIGH_MASK            (0xFFFFU << GPIO_PORT_EOI_H_GPIO_PORT_EOI_HIGH_SHIFT)        /* 0x0000FFFF */
/* EXT_PORT */
#define GPIO_EXT_PORT_OFFSET                               (0x70U)
#define GPIO_EXT_PORT                                      (0x0U)
#define GPIO_EXT_PORT_GPIO_EXT_PORT_SHIFT                  (0U)
#define GPIO_EXT_PORT_GPIO_EXT_PORT_MASK                   (0xFFFFFFFFU << GPIO_EXT_PORT_GPIO_EXT_PORT_SHIFT)           /* 0xFFFFFFFF */
/* VER_ID */
#define GPIO_VER_ID_OFFSET                                 (0x78U)
#define GPIO_VER_ID                                        (0x1000C2BU)
#define GPIO_VER_ID_GPIO_VER_ID_SHIFT                      (0U)
#define GPIO_VER_ID_GPIO_VER_ID_MASK                       (0xFFFFFFFFU << GPIO_VER_ID_GPIO_VER_ID_SHIFT)               /* 0xFFFFFFFF */
/****************************************KEY_CTRL****************************************/
/* CON */
#define KEY_CTRL_CON_OFFSET                                (0x0U)
#define KEY_CTRL_CON_ENABLE_SHIFT                          (0U)
#define KEY_CTRL_CON_ENABLE_MASK                           (0x1U << KEY_CTRL_CON_ENABLE_SHIFT)                          /* 0x00000001 */
#define KEY_CTRL_CON_KEY_DET_TH_SHIFT                      (4U)
#define KEY_CTRL_CON_KEY_DET_TH_MASK                       (0xFFFFFFFU << KEY_CTRL_CON_KEY_DET_TH_SHIFT)                /* 0xFFFFFFF0 */
/* CAL_TH */
#define KEY_CTRL_CAL_TH_OFFSET                             (0x4U)
#define KEY_CTRL_CAL_TH_KEY_CAL_TH_SHIFT                   (0U)
#define KEY_CTRL_CAL_TH_KEY_CAL_TH_MASK                    (0xFFFFFFFFU << KEY_CTRL_CAL_TH_KEY_CAL_TH_SHIFT)            /* 0xFFFFFFFF */
/* DET_REC */
#define KEY_CTRL_DET_REC_OFFSET                            (0x8U)
#define KEY_CTRL_DET_REC                                   (0x0U)
#define KEY_CTRL_DET_REC_KEY_DET_REC_SHIFT                 (0U)
#define KEY_CTRL_DET_REC_KEY_DET_REC_MASK                  (0xFFFFFFFFU << KEY_CTRL_DET_REC_KEY_DET_REC_SHIFT)          /* 0xFFFFFFFF */
/* INT_CON */
#define KEY_CTRL_INT_CON_OFFSET                            (0xCU)
#define KEY_CTRL_INT_CON_KEY_INT_EN_SHIFT                  (0U)
#define KEY_CTRL_INT_CON_KEY_INT_EN_MASK                   (0x1U << KEY_CTRL_INT_CON_KEY_INT_EN_SHIFT)                  /* 0x00000001 */
#define KEY_CTRL_INT_CON_KEY_INT_MASK_DIS_SHIFT            (1U)
#define KEY_CTRL_INT_CON_KEY_INT_MASK_DIS_MASK             (0x1U << KEY_CTRL_INT_CON_KEY_INT_MASK_DIS_SHIFT)            /* 0x00000002 */
#define KEY_CTRL_INT_CON_KEY_INT_MASK_TH_SHIFT             (16U)
#define KEY_CTRL_INT_CON_KEY_INT_MASK_TH_MASK              (0xFFFFU << KEY_CTRL_INT_CON_KEY_INT_MASK_TH_SHIFT)          /* 0xFFFF0000 */
/* INT_ST */
#define KEY_CTRL_INT_ST_OFFSET                             (0x10U)
#define KEY_CTRL_INT_ST_KEY_INT_ST_SHIFT                   (0U)
#define KEY_CTRL_INT_ST_KEY_INT_ST_MASK                    (0x1U << KEY_CTRL_INT_ST_KEY_INT_ST_SHIFT)                   /* 0x00000001 */
/******************************************PDM*******************************************/
/* SYSCONFIG */
#define PDM_SYSCONFIG_OFFSET                               (0x0U)
#define PDM_SYSCONFIG_RX_CLR_SHIFT                         (0U)
#define PDM_SYSCONFIG_RX_CLR_MASK                          (0x1U << PDM_SYSCONFIG_RX_CLR_SHIFT)                         /* 0x00000001 */
#define PDM_SYSCONFIG_RX_START_SHIFT                       (2U)
#define PDM_SYSCONFIG_RX_START_MASK                        (0x1U << PDM_SYSCONFIG_RX_START_SHIFT)                       /* 0x00000004 */
/* CTRL0 */
#define PDM_CTRL0_OFFSET                                   (0x4U)
#define PDM_CTRL0_DATA_VLD_WIDTH_SHIFT                     (0U)
#define PDM_CTRL0_DATA_VLD_WIDTH_MASK                      (0x1FU << PDM_CTRL0_DATA_VLD_WIDTH_SHIFT)                    /* 0x0000001F */
#define PDM_CTRL0_SAMPLE_RATE_SEL_SHIFT                    (5U)
#define PDM_CTRL0_SAMPLE_RATE_SEL_MASK                     (0x7U << PDM_CTRL0_SAMPLE_RATE_SEL_SHIFT)                    /* 0x000000E0 */
#define PDM_CTRL0_INT_DIV_CON_SHIFT                        (8U)
#define PDM_CTRL0_INT_DIV_CON_MASK                         (0xFFU << PDM_CTRL0_INT_DIV_CON_SHIFT)                       /* 0x0000FF00 */
#define PDM_CTRL0_SIG_SCALE_MODE_SHIFT                     (24U)
#define PDM_CTRL0_SIG_SCALE_MODE_MASK                      (0x1U << PDM_CTRL0_SIG_SCALE_MODE_SHIFT)                     /* 0x01000000 */
#define PDM_CTRL0_FILTER_GATE_EN_SHIFT                     (25U)
#define PDM_CTRL0_FILTER_GATE_EN_MASK                      (0x1U << PDM_CTRL0_FILTER_GATE_EN_SHIFT)                     /* 0x02000000 */
#define PDM_CTRL0_HWT_EN_SHIFT                             (26U)
#define PDM_CTRL0_HWT_EN_MASK                              (0x1U << PDM_CTRL0_HWT_EN_SHIFT)                             /* 0x04000000 */
#define PDM_CTRL0_PATH0_EN_SHIFT                           (27U)
#define PDM_CTRL0_PATH0_EN_MASK                            (0x1U << PDM_CTRL0_PATH0_EN_SHIFT)                           /* 0x08000000 */
#define PDM_CTRL0_PATH1_EN_SHIFT                           (28U)
#define PDM_CTRL0_PATH1_EN_MASK                            (0x1U << PDM_CTRL0_PATH1_EN_SHIFT)                           /* 0x10000000 */
#define PDM_CTRL0_PATH2_EN_SHIFT                           (29U)
#define PDM_CTRL0_PATH2_EN_MASK                            (0x1U << PDM_CTRL0_PATH2_EN_SHIFT)                           /* 0x20000000 */
#define PDM_CTRL0_PATH3_EN_SHIFT                           (30U)
#define PDM_CTRL0_PATH3_EN_MASK                            (0x1U << PDM_CTRL0_PATH3_EN_SHIFT)                           /* 0x40000000 */
#define PDM_CTRL0_SJM_SEL_SHIFT                            (31U)
#define PDM_CTRL0_SJM_SEL_MASK                             (0x1U << PDM_CTRL0_SJM_SEL_SHIFT)                            /* 0x80000000 */
/* CTRL1 */
#define PDM_CTRL1_OFFSET                                   (0x8U)
#define PDM_CTRL1_FRAC_DIV_DENOMONATOR_SHIFT               (0U)
#define PDM_CTRL1_FRAC_DIV_DENOMONATOR_MASK                (0xFFFFU << PDM_CTRL1_FRAC_DIV_DENOMONATOR_SHIFT)            /* 0x0000FFFF */
#define PDM_CTRL1_FRAC_DIV_NUMERATOR_SHIFT                 (16U)
#define PDM_CTRL1_FRAC_DIV_NUMERATOR_MASK                  (0xFFFFU << PDM_CTRL1_FRAC_DIV_NUMERATOR_SHIFT)              /* 0xFFFF0000 */
/* CLK_CTRL */
#define PDM_CLK_CTRL_OFFSET                                (0xCU)
#define PDM_CLK_CTRL_CIC_DS_RATIO_SHIFT                    (0U)
#define PDM_CLK_CTRL_CIC_DS_RATIO_MASK                     (0x3U << PDM_CLK_CTRL_CIC_DS_RATIO_SHIFT)                    /* 0x00000003 */
#define PDM_CLK_CTRL_FIR_COM_BPS_SHIFT                     (2U)
#define PDM_CLK_CTRL_FIR_COM_BPS_MASK                      (0x1U << PDM_CLK_CTRL_FIR_COM_BPS_SHIFT)                     /* 0x00000004 */
#define PDM_CLK_CTRL_LR_CH_EX_SHIFT                        (3U)
#define PDM_CLK_CTRL_LR_CH_EX_MASK                         (0x1U << PDM_CLK_CTRL_LR_CH_EX_SHIFT)                        /* 0x00000008 */
#define PDM_CLK_CTRL_DIV_TYPE_SEL_SHIFT                    (4U)
#define PDM_CLK_CTRL_DIV_TYPE_SEL_MASK                     (0x1U << PDM_CLK_CTRL_DIV_TYPE_SEL_SHIFT)                    /* 0x00000010 */
#define PDM_CLK_CTRL_PDM_CLK_EN_SHIFT                      (5U)
#define PDM_CLK_CTRL_PDM_CLK_EN_MASK                       (0x1U << PDM_CLK_CTRL_PDM_CLK_EN_SHIFT)                      /* 0x00000020 */
/* HPF_CTRL */
#define PDM_HPF_CTRL_OFFSET                                (0x10U)
#define PDM_HPF_CTRL_HPF_CF_SHIFT                          (0U)
#define PDM_HPF_CTRL_HPF_CF_MASK                           (0x3U << PDM_HPF_CTRL_HPF_CF_SHIFT)                          /* 0x00000003 */
#define PDM_HPF_CTRL_HPFRE_SHIFT                           (2U)
#define PDM_HPF_CTRL_HPFRE_MASK                            (0x1U << PDM_HPF_CTRL_HPFRE_SHIFT)                           /* 0x00000004 */
#define PDM_HPF_CTRL_HPFLE_SHIFT                           (3U)
#define PDM_HPF_CTRL_HPFLE_MASK                            (0x1U << PDM_HPF_CTRL_HPFLE_SHIFT)                           /* 0x00000008 */
/* FIFO_CTRL */
#define PDM_FIFO_CTRL_OFFSET                               (0x14U)
#define PDM_FIFO_CTRL_RFL_SHIFT                            (0U)
#define PDM_FIFO_CTRL_RFL_MASK                             (0xFFU << PDM_FIFO_CTRL_RFL_SHIFT)                           /* 0x000000FF */
#define PDM_FIFO_CTRL_RFT_SHIFT                            (8U)
#define PDM_FIFO_CTRL_RFT_MASK                             (0x7FU << PDM_FIFO_CTRL_RFT_SHIFT)                           /* 0x00007F00 */
/* DMA_CTRL */
#define PDM_DMA_CTRL_OFFSET                                (0x18U)
#define PDM_DMA_CTRL_RDL_SHIFT                             (0U)
#define PDM_DMA_CTRL_RDL_MASK                              (0x7FU << PDM_DMA_CTRL_RDL_SHIFT)                            /* 0x0000007F */
#define PDM_DMA_CTRL_RDE_SHIFT                             (8U)
#define PDM_DMA_CTRL_RDE_MASK                              (0x1U << PDM_DMA_CTRL_RDE_SHIFT)                             /* 0x00000100 */
/* INT_EN */
#define PDM_INT_EN_OFFSET                                  (0x1CU)
#define PDM_INT_EN_RXTIE_SHIFT                             (0U)
#define PDM_INT_EN_RXTIE_MASK                              (0x1U << PDM_INT_EN_RXTIE_SHIFT)                             /* 0x00000001 */
#define PDM_INT_EN_RXOIE_SHIFT                             (1U)
#define PDM_INT_EN_RXOIE_MASK                              (0x1U << PDM_INT_EN_RXOIE_SHIFT)                             /* 0x00000002 */
/* INT_CLR */
#define PDM_INT_CLR_OFFSET                                 (0x20U)
#define PDM_INT_CLR_RXOIC_SHIFT                            (1U)
#define PDM_INT_CLR_RXOIC_MASK                             (0x1U << PDM_INT_CLR_RXOIC_SHIFT)                            /* 0x00000002 */
/* INT_ST */
#define PDM_INT_ST_OFFSET                                  (0x24U)
#define PDM_INT_ST                                         (0x0U)
#define PDM_INT_ST_RXFI_SHIFT                              (0U)
#define PDM_INT_ST_RXFI_MASK                               (0x1U << PDM_INT_ST_RXFI_SHIFT)                              /* 0x00000001 */
#define PDM_INT_ST_RXOI_SHIFT                              (1U)
#define PDM_INT_ST_RXOI_MASK                               (0x1U << PDM_INT_ST_RXOI_SHIFT)                              /* 0x00000002 */
/* RXFIFO_DATA_REG */
#define PDM_RXFIFO_DATA_REG_OFFSET                         (0x30U)
#define PDM_RXFIFO_DATA_REG                                (0x0U)
#define PDM_RXFIFO_DATA_REG_RXDR_SHIFT                     (0U)
#define PDM_RXFIFO_DATA_REG_RXDR_MASK                      (0xFFFFFFFFU << PDM_RXFIFO_DATA_REG_RXDR_SHIFT)              /* 0xFFFFFFFF */
/* DATA0R_REG */
#define PDM_DATA0R_REG_OFFSET                              (0x34U)
#define PDM_DATA0R_REG                                     (0x0U)
#define PDM_DATA0R_REG_DATA0R_SHIFT                        (0U)
#define PDM_DATA0R_REG_DATA0R_MASK                         (0xFFFFFFFFU << PDM_DATA0R_REG_DATA0R_SHIFT)                 /* 0xFFFFFFFF */
/* DATA0L_REG */
#define PDM_DATA0L_REG_OFFSET                              (0x38U)
#define PDM_DATA0L_REG                                     (0x0U)
#define PDM_DATA0L_REG_DATA0L_SHIFT                        (0U)
#define PDM_DATA0L_REG_DATA0L_MASK                         (0xFFFFFFFFU << PDM_DATA0L_REG_DATA0L_SHIFT)                 /* 0xFFFFFFFF */
/* DATA1R_REG */
#define PDM_DATA1R_REG_OFFSET                              (0x3CU)
#define PDM_DATA1R_REG                                     (0x0U)
#define PDM_DATA1R_REG_DATA1R_SHIFT                        (0U)
#define PDM_DATA1R_REG_DATA1R_MASK                         (0x1U << PDM_DATA1R_REG_DATA1R_SHIFT)                        /* 0x00000001 */
/* DATA1L_REG */
#define PDM_DATA1L_REG_OFFSET                              (0x40U)
#define PDM_DATA1L_REG                                     (0x0U)
#define PDM_DATA1L_REG_DATA1L_SHIFT                        (0U)
#define PDM_DATA1L_REG_DATA1L_MASK                         (0xFFFFFFFFU << PDM_DATA1L_REG_DATA1L_SHIFT)                 /* 0xFFFFFFFF */
/* DATA2R_REG */
#define PDM_DATA2R_REG_OFFSET                              (0x44U)
#define PDM_DATA2R_REG                                     (0x0U)
#define PDM_DATA2R_REG_DATA2R_SHIFT                        (0U)
#define PDM_DATA2R_REG_DATA2R_MASK                         (0xFFFFFFFFU << PDM_DATA2R_REG_DATA2R_SHIFT)                 /* 0xFFFFFFFF */
/* DATA2L_REG */
#define PDM_DATA2L_REG_OFFSET                              (0x48U)
#define PDM_DATA2L_REG                                     (0x0U)
#define PDM_DATA2L_REG_DATA2L_SHIFT                        (0U)
#define PDM_DATA2L_REG_DATA2L_MASK                         (0xFFFFFFFFU << PDM_DATA2L_REG_DATA2L_SHIFT)                 /* 0xFFFFFFFF */
/* DATA3R_REG */
#define PDM_DATA3R_REG_OFFSET                              (0x4CU)
#define PDM_DATA3R_REG                                     (0x0U)
#define PDM_DATA3R_REG_DATA3R_SHIFT                        (0U)
#define PDM_DATA3R_REG_DATA3R_MASK                         (0xFFFFFFFFU << PDM_DATA3R_REG_DATA3R_SHIFT)                 /* 0xFFFFFFFF */
/* DATA3L_REG */
#define PDM_DATA3L_REG_OFFSET                              (0x50U)
#define PDM_DATA3L_REG                                     (0x0U)
#define PDM_DATA3L_REG_DATA3L_SHIFT                        (0U)
#define PDM_DATA3L_REG_DATA3L_MASK                         (0xFFFFFFFFU << PDM_DATA3L_REG_DATA3L_SHIFT)                 /* 0xFFFFFFFF */
/* DATA_VALID */
#define PDM_DATA_VALID_OFFSET                              (0x54U)
#define PDM_DATA_VALID                                     (0x0U)
#define PDM_DATA_VALID_PATH3_VLD_SHIFT                     (0U)
#define PDM_DATA_VALID_PATH3_VLD_MASK                      (0x1U << PDM_DATA_VALID_PATH3_VLD_SHIFT)                     /* 0x00000001 */
#define PDM_DATA_VALID_PATH2_VLD_SHIFT                     (1U)
#define PDM_DATA_VALID_PATH2_VLD_MASK                      (0x1U << PDM_DATA_VALID_PATH2_VLD_SHIFT)                     /* 0x00000002 */
#define PDM_DATA_VALID_PATH1_VLD_SHIFT                     (2U)
#define PDM_DATA_VALID_PATH1_VLD_MASK                      (0x1U << PDM_DATA_VALID_PATH1_VLD_SHIFT)                     /* 0x00000004 */
#define PDM_DATA_VALID_PATH0_VLD_SHIFT                     (3U)
#define PDM_DATA_VALID_PATH0_VLD_MASK                      (0x1U << PDM_DATA_VALID_PATH0_VLD_SHIFT)                     /* 0x00000008 */
/* VERSION */
#define PDM_VERSION_OFFSET                                 (0x58U)
#define PDM_VERSION                                        (0x59313030U)
#define PDM_VERSION_VERSION_SHIFT                          (0U)
#define PDM_VERSION_VERSION_MASK                           (0xFFFFFFFFU << PDM_VERSION_VERSION_SHIFT)                   /* 0xFFFFFFFF */
/* INCR_RXDR */
#define PDM_INCR_RXDR_OFFSET                               (0x400U)
#define PDM_INCR_RXDR                                      (0x0U)
#define PDM_INCR_RXDR_RECEIVE_FIFO_DATA_SHIFT              (0U)
#define PDM_INCR_RXDR_RECEIVE_FIFO_DATA_MASK               (0xFFFFFFFFU << PDM_INCR_RXDR_RECEIVE_FIFO_DATA_SHIFT)       /* 0xFFFFFFFF */
/*****************************************I2STDM*****************************************/
/* TXCR */
#define I2STDM_TXCR_OFFSET                                 (0x0U)
#define I2STDM_TXCR_VDW_SHIFT                              (0U)
#define I2STDM_TXCR_VDW_MASK                               (0x1FU << I2STDM_TXCR_VDW_SHIFT)                             /* 0x0000001F */
#define I2STDM_TXCR_TFS_SHIFT                              (5U)
#define I2STDM_TXCR_TFS_MASK                               (0x3U << I2STDM_TXCR_TFS_SHIFT)                              /* 0x00000060 */
#define I2STDM_TXCR_PBM_SHIFT                              (7U)
#define I2STDM_TXCR_PBM_MASK                               (0x3U << I2STDM_TXCR_PBM_SHIFT)                              /* 0x00000180 */
#define I2STDM_TXCR_IBM_SHIFT                              (9U)
#define I2STDM_TXCR_IBM_MASK                               (0x3U << I2STDM_TXCR_IBM_SHIFT)                              /* 0x00000600 */
#define I2STDM_TXCR_FBM_SHIFT                              (11U)
#define I2STDM_TXCR_FBM_MASK                               (0x1U << I2STDM_TXCR_FBM_SHIFT)                              /* 0x00000800 */
#define I2STDM_TXCR_SJM_SHIFT                              (12U)
#define I2STDM_TXCR_SJM_MASK                               (0x1U << I2STDM_TXCR_SJM_SHIFT)                              /* 0x00001000 */
#define I2STDM_TXCR_HWT_SHIFT                              (14U)
#define I2STDM_TXCR_HWT_MASK                               (0x1U << I2STDM_TXCR_HWT_SHIFT)                              /* 0x00004000 */
#define I2STDM_TXCR_TCSR_SHIFT                             (15U)
#define I2STDM_TXCR_TCSR_MASK                              (0x3U << I2STDM_TXCR_TCSR_SHIFT)                             /* 0x00018000 */
#define I2STDM_TXCR_RCNT_SHIFT                             (17U)
#define I2STDM_TXCR_RCNT_MASK                              (0x3FU << I2STDM_TXCR_RCNT_SHIFT)                            /* 0x007E0000 */
#define I2STDM_TXCR_TX_PATH_SELECT0_SHIFT                  (23U)
#define I2STDM_TXCR_TX_PATH_SELECT0_MASK                   (0x3U << I2STDM_TXCR_TX_PATH_SELECT0_SHIFT)                  /* 0x01800000 */
#define I2STDM_TXCR_TX_PATH_SELECT1_SHIFT                  (25U)
#define I2STDM_TXCR_TX_PATH_SELECT1_MASK                   (0x3U << I2STDM_TXCR_TX_PATH_SELECT1_SHIFT)                  /* 0x06000000 */
#define I2STDM_TXCR_TX_PATH_SELECT2_SHIFT                  (27U)
#define I2STDM_TXCR_TX_PATH_SELECT2_MASK                   (0x3U << I2STDM_TXCR_TX_PATH_SELECT2_SHIFT)                  /* 0x18000000 */
#define I2STDM_TXCR_TX_PATH_SELECT3_SHIFT                  (29U)
#define I2STDM_TXCR_TX_PATH_SELECT3_MASK                   (0x3U << I2STDM_TXCR_TX_PATH_SELECT3_SHIFT)                  /* 0x60000000 */
/* RXCR */
#define I2STDM_RXCR_OFFSET                                 (0x4U)
#define I2STDM_RXCR_VDW_SHIFT                              (0U)
#define I2STDM_RXCR_VDW_MASK                               (0x1FU << I2STDM_RXCR_VDW_SHIFT)                             /* 0x0000001F */
#define I2STDM_RXCR_TFS_SHIFT                              (5U)
#define I2STDM_RXCR_TFS_MASK                               (0x3U << I2STDM_RXCR_TFS_SHIFT)                              /* 0x00000060 */
#define I2STDM_RXCR_PBM_SHIFT                              (7U)
#define I2STDM_RXCR_PBM_MASK                               (0x3U << I2STDM_RXCR_PBM_SHIFT)                              /* 0x00000180 */
#define I2STDM_RXCR_IBM_SHIFT                              (9U)
#define I2STDM_RXCR_IBM_MASK                               (0x3U << I2STDM_RXCR_IBM_SHIFT)                              /* 0x00000600 */
#define I2STDM_RXCR_FBM_SHIFT                              (11U)
#define I2STDM_RXCR_FBM_MASK                               (0x1U << I2STDM_RXCR_FBM_SHIFT)                              /* 0x00000800 */
#define I2STDM_RXCR_SJM_SHIFT                              (12U)
#define I2STDM_RXCR_SJM_MASK                               (0x1U << I2STDM_RXCR_SJM_SHIFT)                              /* 0x00001000 */
#define I2STDM_RXCR_HWT_SHIFT                              (14U)
#define I2STDM_RXCR_HWT_MASK                               (0x1U << I2STDM_RXCR_HWT_SHIFT)                              /* 0x00004000 */
#define I2STDM_RXCR_RCSR_SHIFT                             (15U)
#define I2STDM_RXCR_RCSR_MASK                              (0x3U << I2STDM_RXCR_RCSR_SHIFT)                             /* 0x00018000 */
#define I2STDM_RXCR_RX_PATH_SELECT0_SHIFT                  (17U)
#define I2STDM_RXCR_RX_PATH_SELECT0_MASK                   (0x3U << I2STDM_RXCR_RX_PATH_SELECT0_SHIFT)                  /* 0x00060000 */
#define I2STDM_RXCR_RX_PATH_SELECT1_SHIFT                  (19U)
#define I2STDM_RXCR_RX_PATH_SELECT1_MASK                   (0x3U << I2STDM_RXCR_RX_PATH_SELECT1_SHIFT)                  /* 0x00180000 */
#define I2STDM_RXCR_RX_PATH_SELECT2_SHIFT                  (21U)
#define I2STDM_RXCR_RX_PATH_SELECT2_MASK                   (0x3U << I2STDM_RXCR_RX_PATH_SELECT2_SHIFT)                  /* 0x00600000 */
#define I2STDM_RXCR_RX_PATH_SELECT3_SHIFT                  (23U)
#define I2STDM_RXCR_RX_PATH_SELECT3_MASK                   (0x3U << I2STDM_RXCR_RX_PATH_SELECT3_SHIFT)                  /* 0x01800000 */
/* CKR */
#define I2STDM_CKR_OFFSET                                  (0x8U)
#define I2STDM_CKR_TSD_SHIFT                               (0U)
#define I2STDM_CKR_TSD_MASK                                (0xFFU << I2STDM_CKR_TSD_SHIFT)                              /* 0x000000FF */
#define I2STDM_CKR_RSD_SHIFT                               (8U)
#define I2STDM_CKR_RSD_MASK                                (0xFFU << I2STDM_CKR_RSD_SHIFT)                              /* 0x0000FF00 */
#define I2STDM_CKR_TLP_SHIFT                               (24U)
#define I2STDM_CKR_TLP_MASK                                (0x1U << I2STDM_CKR_TLP_SHIFT)                               /* 0x01000000 */
#define I2STDM_CKR_RLP_SHIFT                               (25U)
#define I2STDM_CKR_RLP_MASK                                (0x1U << I2STDM_CKR_RLP_SHIFT)                               /* 0x02000000 */
#define I2STDM_CKR_CKP_SHIFT                               (26U)
#define I2STDM_CKR_CKP_MASK                                (0x1U << I2STDM_CKR_CKP_SHIFT)                               /* 0x04000000 */
#define I2STDM_CKR_MSS_SHIFT                               (27U)
#define I2STDM_CKR_MSS_MASK                                (0x1U << I2STDM_CKR_MSS_SHIFT)                               /* 0x08000000 */
#define I2STDM_CKR_LRCK_COMMON_SHIFT                       (28U)
#define I2STDM_CKR_LRCK_COMMON_MASK                        (0x3U << I2STDM_CKR_LRCK_COMMON_SHIFT)                       /* 0x30000000 */
/* TXFIFOLR */
#define I2STDM_TXFIFOLR_OFFSET                             (0xCU)
#define I2STDM_TXFIFOLR_TFL0_SHIFT                         (0U)
#define I2STDM_TXFIFOLR_TFL0_MASK                          (0x3FU << I2STDM_TXFIFOLR_TFL0_SHIFT)                        /* 0x0000003F */
#define I2STDM_TXFIFOLR_TFL1_SHIFT                         (6U)
#define I2STDM_TXFIFOLR_TFL1_MASK                          (0x3FU << I2STDM_TXFIFOLR_TFL1_SHIFT)                        /* 0x00000FC0 */
#define I2STDM_TXFIFOLR_TFL2_SHIFT                         (12U)
#define I2STDM_TXFIFOLR_TFL2_MASK                          (0x3FU << I2STDM_TXFIFOLR_TFL2_SHIFT)                        /* 0x0003F000 */
#define I2STDM_TXFIFOLR_TFL3_SHIFT                         (18U)
#define I2STDM_TXFIFOLR_TFL3_MASK                          (0x3FU << I2STDM_TXFIFOLR_TFL3_SHIFT)                        /* 0x00FC0000 */
/* DMACR */
#define I2STDM_DMACR_OFFSET                                (0x10U)
#define I2STDM_DMACR_TDL_SHIFT                             (0U)
#define I2STDM_DMACR_TDL_MASK                              (0x1FU << I2STDM_DMACR_TDL_SHIFT)                            /* 0x0000001F */
#define I2STDM_DMACR_TDE_SHIFT                             (8U)
#define I2STDM_DMACR_TDE_MASK                              (0x1U << I2STDM_DMACR_TDE_SHIFT)                             /* 0x00000100 */
#define I2STDM_DMACR_RDL_SHIFT                             (16U)
#define I2STDM_DMACR_RDL_MASK                              (0x1FU << I2STDM_DMACR_RDL_SHIFT)                            /* 0x001F0000 */
#define I2STDM_DMACR_RDE_SHIFT                             (24U)
#define I2STDM_DMACR_RDE_MASK                              (0x1U << I2STDM_DMACR_RDE_SHIFT)                             /* 0x01000000 */
/* INTCR */
#define I2STDM_INTCR_OFFSET                                (0x14U)
#define I2STDM_INTCR_TXEIE_SHIFT                           (0U)
#define I2STDM_INTCR_TXEIE_MASK                            (0x1U << I2STDM_INTCR_TXEIE_SHIFT)                           /* 0x00000001 */
#define I2STDM_INTCR_TXUIE_SHIFT                           (1U)
#define I2STDM_INTCR_TXUIE_MASK                            (0x1U << I2STDM_INTCR_TXUIE_SHIFT)                           /* 0x00000002 */
#define I2STDM_INTCR_TXUIC_SHIFT                           (2U)
#define I2STDM_INTCR_TXUIC_MASK                            (0x1U << I2STDM_INTCR_TXUIC_SHIFT)                           /* 0x00000004 */
#define I2STDM_INTCR_TFT_SHIFT                             (4U)
#define I2STDM_INTCR_TFT_MASK                              (0x1FU << I2STDM_INTCR_TFT_SHIFT)                            /* 0x000001F0 */
#define I2STDM_INTCR_RXFIE_SHIFT                           (16U)
#define I2STDM_INTCR_RXFIE_MASK                            (0x1U << I2STDM_INTCR_RXFIE_SHIFT)                           /* 0x00010000 */
#define I2STDM_INTCR_RXOIE_SHIFT                           (17U)
#define I2STDM_INTCR_RXOIE_MASK                            (0x1U << I2STDM_INTCR_RXOIE_SHIFT)                           /* 0x00020000 */
#define I2STDM_INTCR_RXOIC_SHIFT                           (18U)
#define I2STDM_INTCR_RXOIC_MASK                            (0x1U << I2STDM_INTCR_RXOIC_SHIFT)                           /* 0x00040000 */
#define I2STDM_INTCR_RFT_SHIFT                             (20U)
#define I2STDM_INTCR_RFT_MASK                              (0x1FU << I2STDM_INTCR_RFT_SHIFT)                            /* 0x01F00000 */
/* INTSR */
#define I2STDM_INTSR_OFFSET                                (0x18U)
#define I2STDM_INTSR_TXEI_SHIFT                            (0U)
#define I2STDM_INTSR_TXEI_MASK                             (0x1U << I2STDM_INTSR_TXEI_SHIFT)                            /* 0x00000001 */
#define I2STDM_INTSR_TXUI_SHIFT                            (1U)
#define I2STDM_INTSR_TXUI_MASK                             (0x1U << I2STDM_INTSR_TXUI_SHIFT)                            /* 0x00000002 */
#define I2STDM_INTSR_RXFI_SHIFT                            (16U)
#define I2STDM_INTSR_RXFI_MASK                             (0x1U << I2STDM_INTSR_RXFI_SHIFT)                            /* 0x00010000 */
#define I2STDM_INTSR_RXOI_SHIFT                            (17U)
#define I2STDM_INTSR_RXOI_MASK                             (0x1U << I2STDM_INTSR_RXOI_SHIFT)                            /* 0x00020000 */
/* XFER */
#define I2STDM_XFER_OFFSET                                 (0x1CU)
#define I2STDM_XFER_TXS_SHIFT                              (0U)
#define I2STDM_XFER_TXS_MASK                               (0x1U << I2STDM_XFER_TXS_SHIFT)                              /* 0x00000001 */
#define I2STDM_XFER_RXS_SHIFT                              (1U)
#define I2STDM_XFER_RXS_MASK                               (0x1U << I2STDM_XFER_RXS_SHIFT)                              /* 0x00000002 */
/* CLR */
#define I2STDM_CLR_OFFSET                                  (0x20U)
#define I2STDM_CLR_TXC_SHIFT                               (0U)
#define I2STDM_CLR_TXC_MASK                                (0x1U << I2STDM_CLR_TXC_SHIFT)                               /* 0x00000001 */
#define I2STDM_CLR_RXC_SHIFT                               (1U)
#define I2STDM_CLR_RXC_MASK                                (0x1U << I2STDM_CLR_RXC_SHIFT)                               /* 0x00000002 */
/* TXDR */
#define I2STDM_TXDR_OFFSET                                 (0x24U)
#define I2STDM_TXDR_TXDR_SHIFT                             (0U)
#define I2STDM_TXDR_TXDR_MASK                              (0xFFFFFFFFU << I2STDM_TXDR_TXDR_SHIFT)                      /* 0xFFFFFFFF */
/* RXDR */
#define I2STDM_RXDR_OFFSET                                 (0x28U)
#define I2STDM_RXDR_RXDR_SHIFT                             (0U)
#define I2STDM_RXDR_RXDR_MASK                              (0xFFFFFFFFU << I2STDM_RXDR_RXDR_SHIFT)                      /* 0xFFFFFFFF */
/* RXFIFOLR */
#define I2STDM_RXFIFOLR_OFFSET                             (0x2CU)
#define I2STDM_RXFIFOLR_RFL0_SHIFT                         (0U)
#define I2STDM_RXFIFOLR_RFL0_MASK                          (0x3FU << I2STDM_RXFIFOLR_RFL0_SHIFT)                        /* 0x0000003F */
#define I2STDM_RXFIFOLR_RFL1_SHIFT                         (6U)
#define I2STDM_RXFIFOLR_RFL1_MASK                          (0x3FU << I2STDM_RXFIFOLR_RFL1_SHIFT)                        /* 0x00000FC0 */
#define I2STDM_RXFIFOLR_RFL2_SHIFT                         (12U)
#define I2STDM_RXFIFOLR_RFL2_MASK                          (0x3FU << I2STDM_RXFIFOLR_RFL2_SHIFT)                        /* 0x0003F000 */
#define I2STDM_RXFIFOLR_RFL3_SHIFT                         (18U)
#define I2STDM_RXFIFOLR_RFL3_MASK                          (0x3FU << I2STDM_RXFIFOLR_RFL3_SHIFT)                        /* 0x00FC0000 */
/* TDM_TXCTRL */
#define I2STDM_TDM_TXCTRL_OFFSET                           (0x30U)
#define I2STDM_TDM_TXCTRL_TDM_TX_FRAME_WIDTH_SHIFT         (0U)
#define I2STDM_TDM_TXCTRL_TDM_TX_FRAME_WIDTH_MASK          (0x1FFU << I2STDM_TDM_TXCTRL_TDM_TX_FRAME_WIDTH_SHIFT)       /* 0x000001FF */
#define I2STDM_TDM_TXCTRL_TDM_TX_SLOT_BIT_WIDTH_SHIFT      (9U)
#define I2STDM_TDM_TXCTRL_TDM_TX_SLOT_BIT_WIDTH_MASK       (0x1FU << I2STDM_TDM_TXCTRL_TDM_TX_SLOT_BIT_WIDTH_SHIFT)     /* 0x00003E00 */
#define I2STDM_TDM_TXCTRL_TDM_TX_SHIFT_CTRL_SHIFT          (14U)
#define I2STDM_TDM_TXCTRL_TDM_TX_SHIFT_CTRL_MASK           (0x7U << I2STDM_TDM_TXCTRL_TDM_TX_SHIFT_CTRL_SHIFT)          /* 0x0001C000 */
#define I2STDM_TDM_TXCTRL_TX_TDM_FSYNC_WIDTH_SEL0_SHIFT    (17U)
#define I2STDM_TDM_TXCTRL_TX_TDM_FSYNC_WIDTH_SEL0_MASK     (0x1U << I2STDM_TDM_TXCTRL_TX_TDM_FSYNC_WIDTH_SEL0_SHIFT)    /* 0x00020000 */
#define I2STDM_TDM_TXCTRL_TX_TDM_FSYNC_WIDTH_SEL1_SHIFT    (18U)
#define I2STDM_TDM_TXCTRL_TX_TDM_FSYNC_WIDTH_SEL1_MASK     (0x7U << I2STDM_TDM_TXCTRL_TX_TDM_FSYNC_WIDTH_SEL1_SHIFT)    /* 0x001C0000 */
/* TDM_RXCTRL */
#define I2STDM_TDM_RXCTRL_OFFSET                           (0x34U)
#define I2STDM_TDM_RXCTRL_TDM_RX_FRAME_WIDTH_SHIFT         (0U)
#define I2STDM_TDM_RXCTRL_TDM_RX_FRAME_WIDTH_MASK          (0x1FFU << I2STDM_TDM_RXCTRL_TDM_RX_FRAME_WIDTH_SHIFT)       /* 0x000001FF */
#define I2STDM_TDM_RXCTRL_TDM_RX_SLOT_BIT_WIDTH_SHIFT      (9U)
#define I2STDM_TDM_RXCTRL_TDM_RX_SLOT_BIT_WIDTH_MASK       (0x1FU << I2STDM_TDM_RXCTRL_TDM_RX_SLOT_BIT_WIDTH_SHIFT)     /* 0x00003E00 */
#define I2STDM_TDM_RXCTRL_TDM_RX_SHIFT_CTRL_SHIFT          (14U)
#define I2STDM_TDM_RXCTRL_TDM_RX_SHIFT_CTRL_MASK           (0x7U << I2STDM_TDM_RXCTRL_TDM_RX_SHIFT_CTRL_SHIFT)          /* 0x0001C000 */
#define I2STDM_TDM_RXCTRL_RX_TDM_FSYNC_WIDTH_SEL0_SHIFT    (17U)
#define I2STDM_TDM_RXCTRL_RX_TDM_FSYNC_WIDTH_SEL0_MASK     (0x1U << I2STDM_TDM_RXCTRL_RX_TDM_FSYNC_WIDTH_SEL0_SHIFT)    /* 0x00020000 */
#define I2STDM_TDM_RXCTRL_RX_TDM_FSYNC_WIDTH_SEL1_SHIFT    (18U)
#define I2STDM_TDM_RXCTRL_RX_TDM_FSYNC_WIDTH_SEL1_MASK     (0x7U << I2STDM_TDM_RXCTRL_RX_TDM_FSYNC_WIDTH_SEL1_SHIFT)    /* 0x001C0000 */
/* CLKDIV */
#define I2STDM_CLKDIV_OFFSET                               (0x38U)
#define I2STDM_CLKDIV_TX_MDIV_SHIFT                        (0U)
#define I2STDM_CLKDIV_TX_MDIV_MASK                         (0xFFU << I2STDM_CLKDIV_TX_MDIV_SHIFT)                       /* 0x000000FF */
#define I2STDM_CLKDIV_RX_MDIV_SHIFT                        (8U)
#define I2STDM_CLKDIV_RX_MDIV_MASK                         (0xFFU << I2STDM_CLKDIV_RX_MDIV_SHIFT)                       /* 0x0000FF00 */
/* VERSION */
#define I2STDM_VERSION_OFFSET                              (0x3CU)
#define I2STDM_VERSION_I2S_VERSION_SHIFT                   (0U)
#define I2STDM_VERSION_I2S_VERSION_MASK                    (0xFFFFFFFFU << I2STDM_VERSION_I2S_VERSION_SHIFT)            /* 0xFFFFFFFF */
/******************************************VAD*******************************************/
/* CONTROL */
#define VAD_CONTROL_OFFSET                                 (0x0U)
#define VAD_CONTROL_VAD_EN_SHIFT                           (0U)
#define VAD_CONTROL_VAD_EN_MASK                            (0x1U << VAD_CONTROL_VAD_EN_SHIFT)                           /* 0x00000001 */
#define VAD_CONTROL_SOURCE_SELECT_SHIFT                    (1U)
#define VAD_CONTROL_SOURCE_SELECT_MASK                     (0x7U << VAD_CONTROL_SOURCE_SELECT_SHIFT)                    /* 0x0000000E */
#define VAD_CONTROL_SOURCE_BURST_SHIFT                     (4U)
#define VAD_CONTROL_SOURCE_BURST_MASK                      (0x7U << VAD_CONTROL_SOURCE_BURST_SHIFT)                     /* 0x00000070 */
#define VAD_CONTROL_SOURCE_BURST_NUM_SHIFT                 (7U)
#define VAD_CONTROL_SOURCE_BURST_NUM_MASK                  (0x7U << VAD_CONTROL_SOURCE_BURST_NUM_SHIFT)                 /* 0x00000380 */
#define VAD_CONTROL_INCR_LENGTH_SHIFT                      (10U)
#define VAD_CONTROL_INCR_LENGTH_MASK                       (0xFU << VAD_CONTROL_INCR_LENGTH_SHIFT)                      /* 0x00003C00 */
#define VAD_CONTROL_SOURCE_FIXADDR_EN_SHIFT                (14U)
#define VAD_CONTROL_SOURCE_FIXADDR_EN_MASK                 (0x1U << VAD_CONTROL_SOURCE_FIXADDR_EN_SHIFT)                /* 0x00004000 */
#define VAD_CONTROL_VAD_MODE_SHIFT                         (20U)
#define VAD_CONTROL_VAD_MODE_MASK                          (0x3U << VAD_CONTROL_VAD_MODE_SHIFT)                         /* 0x00300000 */
#define VAD_CONTROL_VOICE_CHANNEL_NUM_SHIFT                (23U)
#define VAD_CONTROL_VOICE_CHANNEL_NUM_MASK                 (0x7U << VAD_CONTROL_VOICE_CHANNEL_NUM_SHIFT)                /* 0x03800000 */
#define VAD_CONTROL_VOICE_CHANNEL_BITWIDTH_SHIFT           (26U)
#define VAD_CONTROL_VOICE_CHANNEL_BITWIDTH_MASK            (0x1U << VAD_CONTROL_VOICE_CHANNEL_BITWIDTH_SHIFT)           /* 0x04000000 */
#define VAD_CONTROL_VOICE_24BIT_ALIGN_MODE_SHIFT           (27U)
#define VAD_CONTROL_VOICE_24BIT_ALIGN_MODE_MASK            (0x1U << VAD_CONTROL_VOICE_24BIT_ALIGN_MODE_SHIFT)           /* 0x08000000 */
#define VAD_CONTROL_VOICE_24BIT_SAT_SHIFT                  (28U)
#define VAD_CONTROL_VOICE_24BIT_SAT_MASK                   (0x1U << VAD_CONTROL_VOICE_24BIT_SAT_SHIFT)                  /* 0x10000000 */
#define VAD_CONTROL_VAD_DET_CHANNEL_SHIFT                  (29U)
#define VAD_CONTROL_VAD_DET_CHANNEL_MASK                   (0x7U << VAD_CONTROL_VAD_DET_CHANNEL_SHIFT)                  /* 0xE0000000 */
/* VS_ADDR */
#define VAD_VS_ADDR_OFFSET                                 (0x4U)
#define VAD_VS_ADDR_VS_ADDR_SHIFT                          (0U)
#define VAD_VS_ADDR_VS_ADDR_MASK                           (0xFFFFFFFFU << VAD_VS_ADDR_VS_ADDR_SHIFT)                   /* 0xFFFFFFFF */
/* TIMEOUT */
#define VAD_TIMEOUT_OFFSET                                 (0x4CU)
#define VAD_TIMEOUT_IDLE_TIMEOUT_THD_SHIFT                 (0U)
#define VAD_TIMEOUT_IDLE_TIMEOUT_THD_MASK                  (0xFFFFFU << VAD_TIMEOUT_IDLE_TIMEOUT_THD_SHIFT)             /* 0x000FFFFF */
#define VAD_TIMEOUT_WORK_TIMEOUT_THD_SHIFT                 (20U)
#define VAD_TIMEOUT_WORK_TIMEOUT_THD_MASK                  (0x3FFU << VAD_TIMEOUT_WORK_TIMEOUT_THD_SHIFT)               /* 0x3FF00000 */
#define VAD_TIMEOUT_IDLE_TIMEOUT_EN_SHIFT                  (30U)
#define VAD_TIMEOUT_IDLE_TIMEOUT_EN_MASK                   (0x1U << VAD_TIMEOUT_IDLE_TIMEOUT_EN_SHIFT)                  /* 0x40000000 */
#define VAD_TIMEOUT_WORK_TIMEOUT_EN_SHIFT                  (31U)
#define VAD_TIMEOUT_WORK_TIMEOUT_EN_MASK                   (0x1U << VAD_TIMEOUT_WORK_TIMEOUT_EN_SHIFT)                  /* 0x80000000 */
/* RAM_START_ADDR */
#define VAD_RAM_START_ADDR_OFFSET                          (0x50U)
#define VAD_RAM_START_ADDR_RAM_START_ADDR_SHIFT            (0U)
#define VAD_RAM_START_ADDR_RAM_START_ADDR_MASK             (0xFFFFFFFFU << VAD_RAM_START_ADDR_RAM_START_ADDR_SHIFT)     /* 0xFFFFFFFF */
/* RAM_END_ADDR */
#define VAD_RAM_END_ADDR_OFFSET                            (0x54U)
#define VAD_RAM_END_ADDR_RAM_END_ADDR_SHIFT                (0U)
#define VAD_RAM_END_ADDR_RAM_END_ADDR_MASK                 (0xFFFFFFFFU << VAD_RAM_END_ADDR_RAM_END_ADDR_SHIFT)         /* 0xFFFFFFFF */
/* RAM_CUR_ADDR */
#define VAD_RAM_CUR_ADDR_OFFSET                            (0x58U)
#define VAD_RAM_CUR_ADDR_RAM_CUR_ADDR_SHIFT                (0U)
#define VAD_RAM_CUR_ADDR_RAM_CUR_ADDR_MASK                 (0xFFFFFFFFU << VAD_RAM_CUR_ADDR_RAM_CUR_ADDR_SHIFT)         /* 0xFFFFFFFF */
/* DET_CON0 */
#define VAD_DET_CON0_OFFSET                                (0x5CU)
#define VAD_DET_CON0_GAIN_SHIFT                            (0U)
#define VAD_DET_CON0_GAIN_MASK                             (0xFFFU << VAD_DET_CON0_GAIN_SHIFT)                          /* 0x00000FFF */
#define VAD_DET_CON0_NOISE_LEVEL_SHIFT                     (12U)
#define VAD_DET_CON0_NOISE_LEVEL_MASK                      (0x7U << VAD_DET_CON0_NOISE_LEVEL_SHIFT)                     /* 0x00007000 */
#define VAD_DET_CON0_VAD_CON_THD_SHIFT                     (16U)
#define VAD_DET_CON0_VAD_CON_THD_MASK                      (0xFFU << VAD_DET_CON0_VAD_CON_THD_SHIFT)                    /* 0x00FF0000 */
#define VAD_DET_CON0_DIS_VAD_CON_THD_SHIFT                 (24U)
#define VAD_DET_CON0_DIS_VAD_CON_THD_MASK                  (0xFU << VAD_DET_CON0_DIS_VAD_CON_THD_SHIFT)                 /* 0x0F000000 */
#define VAD_DET_CON0_VAD_THD_MODE_SHIFT                    (28U)
#define VAD_DET_CON0_VAD_THD_MODE_MASK                     (0x3U << VAD_DET_CON0_VAD_THD_MODE_SHIFT)                    /* 0x30000000 */
/* DET_CON1 */
#define VAD_DET_CON1_OFFSET                                (0x60U)
#define VAD_DET_CON1_SOUND_THD_SHIFT                       (0U)
#define VAD_DET_CON1_SOUND_THD_MASK                        (0xFFFFU << VAD_DET_CON1_SOUND_THD_SHIFT)                    /* 0x0000FFFF */
#define VAD_DET_CON1_NOISE_SAMPLE_NUM_SHIFT                (16U)
#define VAD_DET_CON1_NOISE_SAMPLE_NUM_MASK                 (0x3FFU << VAD_DET_CON1_NOISE_SAMPLE_NUM_SHIFT)              /* 0x03FF0000 */
#define VAD_DET_CON1_CLEAN_IIR_EN_SHIFT                    (26U)
#define VAD_DET_CON1_CLEAN_IIR_EN_MASK                     (0x1U << VAD_DET_CON1_CLEAN_IIR_EN_SHIFT)                    /* 0x04000000 */
#define VAD_DET_CON1_FORCE_NOISE_CLK_EN_SHIFT              (28U)
#define VAD_DET_CON1_FORCE_NOISE_CLK_EN_MASK               (0x1U << VAD_DET_CON1_FORCE_NOISE_CLK_EN_SHIFT)              /* 0x10000000 */
#define VAD_DET_CON1_CLEAN_NOISE_AT_BEGIN_SHIFT            (29U)
#define VAD_DET_CON1_CLEAN_NOISE_AT_BEGIN_MASK             (0x1U << VAD_DET_CON1_CLEAN_NOISE_AT_BEGIN_SHIFT)            /* 0x20000000 */
#define VAD_DET_CON1_MIN_NOISE_FIND_MODE_SHIFT             (30U)
#define VAD_DET_CON1_MIN_NOISE_FIND_MODE_MASK              (0x1U << VAD_DET_CON1_MIN_NOISE_FIND_MODE_SHIFT)             /* 0x40000000 */
/* DET_CON2 */
#define VAD_DET_CON2_OFFSET                                (0x64U)
#define VAD_DET_CON2_NOISE_FRM_NUM_SHIFT                   (0U)
#define VAD_DET_CON2_NOISE_FRM_NUM_MASK                    (0x7FU << VAD_DET_CON2_NOISE_FRM_NUM_SHIFT)                  /* 0x0000007F */
#define VAD_DET_CON2_NOISE_ALPHA_SHIFT                     (8U)
#define VAD_DET_CON2_NOISE_ALPHA_MASK                      (0xFFU << VAD_DET_CON2_NOISE_ALPHA_SHIFT)                    /* 0x0000FF00 */
#define VAD_DET_CON2_IIR_ANUM_0_SHIFT                      (16U)
#define VAD_DET_CON2_IIR_ANUM_0_MASK                       (0xFFFFU << VAD_DET_CON2_IIR_ANUM_0_SHIFT)                   /* 0xFFFF0000 */
/* DET_CON3 */
#define VAD_DET_CON3_OFFSET                                (0x68U)
#define VAD_DET_CON3_IIR_ANUM_1_SHIFT                      (0U)
#define VAD_DET_CON3_IIR_ANUM_1_MASK                       (0xFFFFU << VAD_DET_CON3_IIR_ANUM_1_SHIFT)                   /* 0x0000FFFF */
#define VAD_DET_CON3_IIR_ANUM_2_SHIFT                      (16U)
#define VAD_DET_CON3_IIR_ANUM_2_MASK                       (0xFFFFU << VAD_DET_CON3_IIR_ANUM_2_SHIFT)                   /* 0xFFFF0000 */
/* DET_CON4 */
#define VAD_DET_CON4_OFFSET                                (0x6CU)
#define VAD_DET_CON4_IIR_ADEN_1_SHIFT                      (0U)
#define VAD_DET_CON4_IIR_ADEN_1_MASK                       (0xFFFFU << VAD_DET_CON4_IIR_ADEN_1_SHIFT)                   /* 0x0000FFFF */
#define VAD_DET_CON4_IIR_ADEN_2_SHIFT                      (16U)
#define VAD_DET_CON4_IIR_ADEN_2_MASK                       (0xFFFFU << VAD_DET_CON4_IIR_ADEN_2_SHIFT)                   /* 0xFFFF0000 */
/* DET_CON5 */
#define VAD_DET_CON5_OFFSET                                (0x70U)
#define VAD_DET_CON5_NOISE_ABS_SHIFT                       (0U)
#define VAD_DET_CON5_NOISE_ABS_MASK                        (0xFFFFU << VAD_DET_CON5_NOISE_ABS_SHIFT)                    /* 0x0000FFFF */
#define VAD_DET_CON5_IIR_RESULT_SHIFT                      (16U)
#define VAD_DET_CON5_IIR_RESULT_MASK                       (0xFFFFU << VAD_DET_CON5_IIR_RESULT_SHIFT)                   /* 0xFFFF0000 */
/* INT */
#define VAD_INT_OFFSET                                     (0x74U)
#define VAD_INT_VAD_DET_INT_EN_SHIFT                       (0U)
#define VAD_INT_VAD_DET_INT_EN_MASK                        (0x1U << VAD_INT_VAD_DET_INT_EN_SHIFT)                       /* 0x00000001 */
#define VAD_INT_ERROR_INT_EN_SHIFT                         (1U)
#define VAD_INT_ERROR_INT_EN_MASK                          (0x1U << VAD_INT_ERROR_INT_EN_SHIFT)                         /* 0x00000002 */
#define VAD_INT_IDLE_TIMEOUT_INT_EN_SHIFT                  (2U)
#define VAD_INT_IDLE_TIMEOUT_INT_EN_MASK                   (0x1U << VAD_INT_IDLE_TIMEOUT_INT_EN_SHIFT)                  /* 0x00000004 */
#define VAD_INT_WORK_TIMEOUT_INT_EN_SHIFT                  (3U)
#define VAD_INT_WORK_TIMEOUT_INT_EN_MASK                   (0x1U << VAD_INT_WORK_TIMEOUT_INT_EN_SHIFT)                  /* 0x00000008 */
#define VAD_INT_VAD_DET_INT_SHIFT                          (4U)
#define VAD_INT_VAD_DET_INT_MASK                           (0x1U << VAD_INT_VAD_DET_INT_SHIFT)                          /* 0x00000010 */
#define VAD_INT_ERROR_INT_SHIFT                            (5U)
#define VAD_INT_ERROR_INT_MASK                             (0x1U << VAD_INT_ERROR_INT_SHIFT)                            /* 0x00000020 */
#define VAD_INT_IDLE_TIMEOUT_INT_SHIFT                     (6U)
#define VAD_INT_IDLE_TIMEOUT_INT_MASK                      (0x1U << VAD_INT_IDLE_TIMEOUT_INT_SHIFT)                     /* 0x00000040 */
#define VAD_INT_WORK_TIMEOUT_INT_SHIFT                     (7U)
#define VAD_INT_WORK_TIMEOUT_INT_MASK                      (0x1U << VAD_INT_WORK_TIMEOUT_INT_SHIFT)                     /* 0x00000080 */
#define VAD_INT_RAMP_LOOP_FLAG_SHIFT                       (8U)
#define VAD_INT_RAMP_LOOP_FLAG_MASK                        (0x1U << VAD_INT_RAMP_LOOP_FLAG_SHIFT)                       /* 0x00000100 */
#define VAD_INT_VAD_IDLE_SHIFT                             (9U)
#define VAD_INT_VAD_IDLE_MASK                              (0x1U << VAD_INT_VAD_IDLE_SHIFT)                             /* 0x00000200 */
#define VAD_INT_VAD_DATA_TRANS_INT_EN_SHIFT                (10U)
#define VAD_INT_VAD_DATA_TRANS_INT_EN_MASK                 (0x1U << VAD_INT_VAD_DATA_TRANS_INT_EN_SHIFT)                /* 0x00000400 */
#define VAD_INT_VAD_DATA_TRANS_INT_SHIFT                   (11U)
#define VAD_INT_VAD_DATA_TRANS_INT_MASK                    (0x1U << VAD_INT_VAD_DATA_TRANS_INT_SHIFT)                   /* 0x00000800 */
#define VAD_INT_RAMP_LOOP_FLAG_BUS_SHIFT                   (12U)
#define VAD_INT_RAMP_LOOP_FLAG_BUS_MASK                    (0x1U << VAD_INT_RAMP_LOOP_FLAG_BUS_SHIFT)                   /* 0x00001000 */
/* AUX_CON0 */
#define VAD_AUX_CON0_OFFSET                                (0x78U)
#define VAD_AUX_CON0_BUS_WRITE_EN_SHIFT                    (0U)
#define VAD_AUX_CON0_BUS_WRITE_EN_MASK                     (0x1U << VAD_AUX_CON0_BUS_WRITE_EN_SHIFT)                    /* 0x00000001 */
#define VAD_AUX_CON0_DIS_RAM_ITF_SHIFT                     (1U)
#define VAD_AUX_CON0_DIS_RAM_ITF_MASK                      (0x1U << VAD_AUX_CON0_DIS_RAM_ITF_SHIFT)                     /* 0x00000002 */
#define VAD_AUX_CON0_DATA_TRANS_TRIG_INT_EN_SHIFT          (2U)
#define VAD_AUX_CON0_DATA_TRANS_TRIG_INT_EN_MASK           (0x1U << VAD_AUX_CON0_DATA_TRANS_TRIG_INT_EN_SHIFT)          /* 0x00000004 */
#define VAD_AUX_CON0_DATA_TRANS_KBYTE_THD_SHIFT            (4U)
#define VAD_AUX_CON0_DATA_TRANS_KBYTE_THD_MASK             (0xFFU << VAD_AUX_CON0_DATA_TRANS_KBYTE_THD_SHIFT)           /* 0x00000FF0 */
#define VAD_AUX_CON0_BUS_WRITE_ADDR_MODE_SHIFT             (12U)
#define VAD_AUX_CON0_BUS_WRITE_ADDR_MODE_MASK              (0x1U << VAD_AUX_CON0_BUS_WRITE_ADDR_MODE_SHIFT)             /* 0x00001000 */
#define VAD_AUX_CON0_BUS_WRITE_REWORK_ADDR_MODE_SHIFT      (13U)
#define VAD_AUX_CON0_BUS_WRITE_REWORK_ADDR_MODE_MASK       (0x1U << VAD_AUX_CON0_BUS_WRITE_REWORK_ADDR_MODE_SHIFT)      /* 0x00002000 */
#define VAD_AUX_CON0_RAM_WRITE_REWORK_ADDR_MODE_SHIFT      (14U)
#define VAD_AUX_CON0_RAM_WRITE_REWORK_ADDR_MODE_MASK       (0x1U << VAD_AUX_CON0_RAM_WRITE_REWORK_ADDR_MODE_SHIFT)      /* 0x00004000 */
#define VAD_AUX_CON0_INT_TRIG_VALID_THD_SHIFT              (16U)
#define VAD_AUX_CON0_INT_TRIG_VALID_THD_MASK               (0xFFFU << VAD_AUX_CON0_INT_TRIG_VALID_THD_SHIFT)            /* 0x0FFF0000 */
#define VAD_AUX_CON0_INT_TRIG_CTRL_EN_SHIFT                (28U)
#define VAD_AUX_CON0_INT_TRIG_CTRL_EN_MASK                 (0x1U << VAD_AUX_CON0_INT_TRIG_CTRL_EN_SHIFT)                /* 0x10000000 */
#define VAD_AUX_CON0_SAMPLE_CNT_EN_SHIFT                   (29U)
#define VAD_AUX_CON0_SAMPLE_CNT_EN_MASK                    (0x1U << VAD_AUX_CON0_SAMPLE_CNT_EN_SHIFT)                   /* 0x20000000 */
/* SAMPLE_CNT */
#define VAD_SAMPLE_CNT_OFFSET                              (0x7CU)
#define VAD_SAMPLE_CNT                                     (0x0U)
#define VAD_SAMPLE_CNT_SAMPLE_CNT_SHIFT                    (0U)
#define VAD_SAMPLE_CNT_SAMPLE_CNT_MASK                     (0xFFFFFFFFU << VAD_SAMPLE_CNT_SAMPLE_CNT_SHIFT)             /* 0xFFFFFFFF */
/* RAM_START_ADDR_BUS */
#define VAD_RAM_START_ADDR_BUS_OFFSET                      (0x80U)
#define VAD_RAM_START_ADDR_BUS_RAM_START_ADDR_BUS_SHIFT    (0U)
#define VAD_RAM_START_ADDR_BUS_RAM_START_ADDR_BUS_MASK     (0xFFFFFFFFU << VAD_RAM_START_ADDR_BUS_RAM_START_ADDR_BUS_SHIFT) /* 0xFFFFFFFF */
/* RAM_END_ADDR_BUS */
#define VAD_RAM_END_ADDR_BUS_OFFSET                        (0x84U)
#define VAD_RAM_END_ADDR_BUS_RAM_BEGIN_ADDR_BUS_SHIFT      (0U)
#define VAD_RAM_END_ADDR_BUS_RAM_BEGIN_ADDR_BUS_MASK       (0xFFFFFFFFU << VAD_RAM_END_ADDR_BUS_RAM_BEGIN_ADDR_BUS_SHIFT) /* 0xFFFFFFFF */
/* RAM_CUR_ADDR_BUS */
#define VAD_RAM_CUR_ADDR_BUS_OFFSET                        (0x88U)
#define VAD_RAM_CUR_ADDR_BUS_RAM_CUR_ADDR_BUS_SHIFT        (0U)
#define VAD_RAM_CUR_ADDR_BUS_RAM_CUR_ADDR_BUS_MASK         (0xFFFFFFFFU << VAD_RAM_CUR_ADDR_BUS_RAM_CUR_ADDR_BUS_SHIFT) /* 0xFFFFFFFF */
/* AUX_CON1 */
#define VAD_AUX_CON1_OFFSET                                (0x8CU)
#define VAD_AUX_CON1_DATA_TRANS_WORD_THD_SHIFT             (0U)
#define VAD_AUX_CON1_DATA_TRANS_WORD_THD_MASK              (0xFFFFU << VAD_AUX_CON1_DATA_TRANS_WORD_THD_SHIFT)          /* 0x0000FFFF */
#define VAD_AUX_CON1_DATA_TRANS_INT_MODE_SEL_SHIFT         (16U)
#define VAD_AUX_CON1_DATA_TRANS_INT_MODE_SEL_MASK          (0x1U << VAD_AUX_CON1_DATA_TRANS_INT_MODE_SEL_SHIFT)         /* 0x00010000 */
/* NOISE_FIRST_DATA */
#define VAD_NOISE_FIRST_DATA_OFFSET                        (0x100U)
#define VAD_NOISE_FIRST_DATA_NOISE_FIRST_DATA_SHIFT        (0U)
#define VAD_NOISE_FIRST_DATA_NOISE_FIRST_DATA_MASK         (0xFFFFU << VAD_NOISE_FIRST_DATA_NOISE_FIRST_DATA_SHIFT)     /* 0x0000FFFF */
/* NOISE_LAST_DATA */
#define VAD_NOISE_LAST_DATA_OFFSET                         (0x2FCU)
#define VAD_NOISE_LAST_DATA_NOISE_LAST_DATA_SHIFT          (0U)
#define VAD_NOISE_LAST_DATA_NOISE_LAST_DATA_MASK           (0xFFFFU << VAD_NOISE_LAST_DATA_NOISE_LAST_DATA_SHIFT)       /* 0x0000FFFF */
/******************************************VOP*******************************************/
/* REG_CFG_DONE */
#define VOP_REG_CFG_DONE_OFFSET                            (0x0U)
#define VOP_REG_CFG_DONE_REG_LOAD_GLOBAL_EN_SHIFT          (0U)
#define VOP_REG_CFG_DONE_REG_LOAD_GLOBAL_EN_MASK           (0x1U << VOP_REG_CFG_DONE_REG_LOAD_GLOBAL_EN_SHIFT)          /* 0x00000001 */
#define VOP_REG_CFG_DONE_REG_LOAD_WIN0_EN_SHIFT            (1U)
#define VOP_REG_CFG_DONE_REG_LOAD_WIN0_EN_MASK             (0x1U << VOP_REG_CFG_DONE_REG_LOAD_WIN0_EN_SHIFT)            /* 0x00000002 */
#define VOP_REG_CFG_DONE_REG_LOAD_WIN1_EN_SHIFT            (2U)
#define VOP_REG_CFG_DONE_REG_LOAD_WIN1_EN_MASK             (0x1U << VOP_REG_CFG_DONE_REG_LOAD_WIN1_EN_SHIFT)            /* 0x00000004 */
#define VOP_REG_CFG_DONE_REG_LOAD_WIN2_EN_SHIFT            (3U)
#define VOP_REG_CFG_DONE_REG_LOAD_WIN2_EN_MASK             (0x1U << VOP_REG_CFG_DONE_REG_LOAD_WIN2_EN_SHIFT)            /* 0x00000008 */
#define VOP_REG_CFG_DONE_REG_LOAD_WIN3_EN_SHIFT            (4U)
#define VOP_REG_CFG_DONE_REG_LOAD_WIN3_EN_MASK             (0x1U << VOP_REG_CFG_DONE_REG_LOAD_WIN3_EN_SHIFT)            /* 0x00000010 */
#define VOP_REG_CFG_DONE_REG_LOAD_SYS_EN_SHIFT             (5U)
#define VOP_REG_CFG_DONE_REG_LOAD_SYS_EN_MASK              (0x1U << VOP_REG_CFG_DONE_REG_LOAD_SYS_EN_SHIFT)             /* 0x00000020 */
/* VERSION */
#define VOP_VERSION_OFFSET                                 (0x4U)
#define VOP_VERSION                                        (0x0U)
#define VOP_VERSION_BUILD_SHIFT                            (0U)
#define VOP_VERSION_BUILD_MASK                             (0xFFFFU << VOP_VERSION_BUILD_SHIFT)                         /* 0x0000FFFF */
#define VOP_VERSION_MINOR_SHIFT                            (16U)
#define VOP_VERSION_MINOR_MASK                             (0xFFU << VOP_VERSION_MINOR_SHIFT)                           /* 0x00FF0000 */
#define VOP_VERSION_MAJOR_SHIFT                            (24U)
#define VOP_VERSION_MAJOR_MASK                             (0xFFU << VOP_VERSION_MAJOR_SHIFT)                           /* 0xFF000000 */
/* DSP_BG */
#define VOP_DSP_BG_OFFSET                                  (0x8U)
#define VOP_DSP_BG_DSP_BG_BLUE_SHIFT                       (0U)
#define VOP_DSP_BG_DSP_BG_BLUE_MASK                        (0xFFU << VOP_DSP_BG_DSP_BG_BLUE_SHIFT)                      /* 0x000000FF */
#define VOP_DSP_BG_DSP_BG_GREEN_SHIFT                      (8U)
#define VOP_DSP_BG_DSP_BG_GREEN_MASK                       (0xFFU << VOP_DSP_BG_DSP_BG_GREEN_SHIFT)                     /* 0x0000FF00 */
#define VOP_DSP_BG_DSP_BG_RED_SHIFT                        (16U)
#define VOP_DSP_BG_DSP_BG_RED_MASK                         (0xFFU << VOP_DSP_BG_DSP_BG_RED_SHIFT)                       /* 0x00FF0000 */
/* MCU */
#define VOP_MCU_OFFSET                                     (0xCU)
#define VOP_MCU_MCU_PIX_TOTAL_SHIFT                        (0U)
#define VOP_MCU_MCU_PIX_TOTAL_MASK                         (0x3FU << VOP_MCU_MCU_PIX_TOTAL_SHIFT)                       /* 0x0000003F */
#define VOP_MCU_MCU_CS_PST_SHIFT                           (6U)
#define VOP_MCU_MCU_CS_PST_MASK                            (0xFU << VOP_MCU_MCU_CS_PST_SHIFT)                           /* 0x000003C0 */
#define VOP_MCU_MCU_CS_PEND_SHIFT                          (10U)
#define VOP_MCU_MCU_CS_PEND_MASK                           (0x3FU << VOP_MCU_MCU_CS_PEND_SHIFT)                         /* 0x0000FC00 */
#define VOP_MCU_MCU_RW_PST_SHIFT                           (16U)
#define VOP_MCU_MCU_RW_PST_MASK                            (0xFU << VOP_MCU_MCU_RW_PST_SHIFT)                           /* 0x000F0000 */
#define VOP_MCU_MCU_RW_PEND_SHIFT                          (20U)
#define VOP_MCU_MCU_RW_PEND_MASK                           (0x3FU << VOP_MCU_MCU_RW_PEND_SHIFT)                         /* 0x03F00000 */
#define VOP_MCU_MCU_CLK_SEL_SHIFT                          (26U)
#define VOP_MCU_MCU_CLK_SEL_MASK                           (0x1U << VOP_MCU_MCU_CLK_SEL_SHIFT)                          /* 0x04000000 */
#define VOP_MCU_MCU_HOLD_MODE_SHIFT                        (27U)
#define VOP_MCU_MCU_HOLD_MODE_MASK                         (0x1U << VOP_MCU_MCU_HOLD_MODE_SHIFT)                        /* 0x08000000 */
#define VOP_MCU_MCU_FRAME_ST_SHIFT                         (28U)
#define VOP_MCU_MCU_FRAME_ST_MASK                          (0x1U << VOP_MCU_MCU_FRAME_ST_SHIFT)                         /* 0x10000000 */
#define VOP_MCU_MCU_RS_SHIFT                               (29U)
#define VOP_MCU_MCU_RS_MASK                                (0x1U << VOP_MCU_MCU_RS_SHIFT)                               /* 0x20000000 */
#define VOP_MCU_MCU_BYPASS_SHIFT                           (30U)
#define VOP_MCU_MCU_BYPASS_MASK                            (0x1U << VOP_MCU_MCU_BYPASS_SHIFT)                           /* 0x40000000 */
#define VOP_MCU_MCU_TYPE_SHIFT                             (31U)
#define VOP_MCU_MCU_TYPE_MASK                              (0x1U << VOP_MCU_MCU_TYPE_SHIFT)                             /* 0x80000000 */
/* SYS_CTRL0 */
#define VOP_SYS_CTRL0_OFFSET                               (0x10U)
#define VOP_SYS_CTRL0_RESERVED_SHIFT                       (0U)
#define VOP_SYS_CTRL0_RESERVED_MASK                        (0xFFFFFFFFU << VOP_SYS_CTRL0_RESERVED_SHIFT)                /* 0xFFFFFFFF */
/* SYS_CTRL1 */
#define VOP_SYS_CTRL1_OFFSET                               (0x14U)
#define VOP_SYS_CTRL1_SW_NOC_QOS_EN_SHIFT                  (0U)
#define VOP_SYS_CTRL1_SW_NOC_QOS_EN_MASK                   (0x1U << VOP_SYS_CTRL1_SW_NOC_QOS_EN_SHIFT)                  /* 0x00000001 */
#define VOP_SYS_CTRL1_SW_NOC_QOS_VALUE_SHIFT               (1U)
#define VOP_SYS_CTRL1_SW_NOC_QOS_VALUE_MASK                (0x3U << VOP_SYS_CTRL1_SW_NOC_QOS_VALUE_SHIFT)               /* 0x00000006 */
#define VOP_SYS_CTRL1_SW_NOC_HURRY_EN_SHIFT                (4U)
#define VOP_SYS_CTRL1_SW_NOC_HURRY_EN_MASK                 (0x1U << VOP_SYS_CTRL1_SW_NOC_HURRY_EN_SHIFT)                /* 0x00000010 */
#define VOP_SYS_CTRL1_SW_NOC_HURRY_VALUE_SHIFT             (5U)
#define VOP_SYS_CTRL1_SW_NOC_HURRY_VALUE_MASK              (0x3U << VOP_SYS_CTRL1_SW_NOC_HURRY_VALUE_SHIFT)             /* 0x00000060 */
#define VOP_SYS_CTRL1_SW_NOC_HURRY_THRESHOLD_SHIFT         (8U)
#define VOP_SYS_CTRL1_SW_NOC_HURRY_THRESHOLD_MASK          (0xFU << VOP_SYS_CTRL1_SW_NOC_HURRY_THRESHOLD_SHIFT)         /* 0x00000F00 */
#define VOP_SYS_CTRL1_SW_AXI_MAX_OUTSTAND_EN_SHIFT         (12U)
#define VOP_SYS_CTRL1_SW_AXI_MAX_OUTSTAND_EN_MASK          (0x1U << VOP_SYS_CTRL1_SW_AXI_MAX_OUTSTAND_EN_SHIFT)         /* 0x00001000 */
#define VOP_SYS_CTRL1_SW_AXI_MAX_OUTSTAND_NUM_SHIFT        (16U)
#define VOP_SYS_CTRL1_SW_AXI_MAX_OUTSTAND_NUM_MASK         (0x1FU << VOP_SYS_CTRL1_SW_AXI_MAX_OUTSTAND_NUM_SHIFT)       /* 0x001F0000 */
/* SYS_CTRL2 */
#define VOP_SYS_CTRL2_OFFSET                               (0x18U)
#define VOP_SYS_CTRL2_IMD_AUTO_GATING_EN_SHIFT             (0U)
#define VOP_SYS_CTRL2_IMD_AUTO_GATING_EN_MASK              (0x1U << VOP_SYS_CTRL2_IMD_AUTO_GATING_EN_SHIFT)             /* 0x00000001 */
#define VOP_SYS_CTRL2_IMD_VOP_STANDBY_EN_SHIFT             (1U)
#define VOP_SYS_CTRL2_IMD_VOP_STANDBY_EN_MASK              (0x1U << VOP_SYS_CTRL2_IMD_VOP_STANDBY_EN_SHIFT)             /* 0x00000002 */
#define VOP_SYS_CTRL2_IMD_VOP_DMA_STOP_SHIFT               (2U)
#define VOP_SYS_CTRL2_IMD_VOP_DMA_STOP_MASK                (0x1U << VOP_SYS_CTRL2_IMD_VOP_DMA_STOP_SHIFT)               /* 0x00000004 */
#define VOP_SYS_CTRL2_IMD_DSP_OUT_ZERO_SHIFT               (3U)
#define VOP_SYS_CTRL2_IMD_DSP_OUT_ZERO_MASK                (0x1U << VOP_SYS_CTRL2_IMD_DSP_OUT_ZERO_SHIFT)               /* 0x00000008 */
#define VOP_SYS_CTRL2_IMD_YUV_CLIP_SHIFT                   (4U)
#define VOP_SYS_CTRL2_IMD_YUV_CLIP_MASK                    (0x1U << VOP_SYS_CTRL2_IMD_YUV_CLIP_SHIFT)                   /* 0x00000010 */
#define VOP_SYS_CTRL2_IMD_DSP_DATA_OUT_MODE_SHIFT          (6U)
#define VOP_SYS_CTRL2_IMD_DSP_DATA_OUT_MODE_MASK           (0x1U << VOP_SYS_CTRL2_IMD_DSP_DATA_OUT_MODE_SHIFT)          /* 0x00000040 */
#define VOP_SYS_CTRL2_SW_IO_PAD_CLK_SEL_SHIFT              (7U)
#define VOP_SYS_CTRL2_SW_IO_PAD_CLK_SEL_MASK               (0x1U << VOP_SYS_CTRL2_SW_IO_PAD_CLK_SEL_SHIFT)              /* 0x00000080 */
#define VOP_SYS_CTRL2_IMD_EDPI_TE_EN_SHIFT                 (9U)
#define VOP_SYS_CTRL2_IMD_EDPI_TE_EN_MASK                  (0x1U << VOP_SYS_CTRL2_IMD_EDPI_TE_EN_SHIFT)                 /* 0x00000200 */
#define VOP_SYS_CTRL2_IMD_EDPI_CTRL_MODE_SHIFT             (10U)
#define VOP_SYS_CTRL2_IMD_EDPI_CTRL_MODE_MASK              (0x1U << VOP_SYS_CTRL2_IMD_EDPI_CTRL_MODE_SHIFT)             /* 0x00000400 */
#define VOP_SYS_CTRL2_IMD_EDPI_WMS_FS_SHIFT                (11U)
#define VOP_SYS_CTRL2_IMD_EDPI_WMS_FS_MASK                 (0x1U << VOP_SYS_CTRL2_IMD_EDPI_WMS_FS_SHIFT)                /* 0x00000800 */
#define VOP_SYS_CTRL2_IMD_DSP_TIMING_IMD_SHIFT             (12U)
#define VOP_SYS_CTRL2_IMD_DSP_TIMING_IMD_MASK              (0x1U << VOP_SYS_CTRL2_IMD_DSP_TIMING_IMD_SHIFT)             /* 0x00001000 */
#define VOP_SYS_CTRL2_IMD_GLOBAL_REGDONE_EN_SHIFT          (13U)
#define VOP_SYS_CTRL2_IMD_GLOBAL_REGDONE_EN_MASK           (0x1U << VOP_SYS_CTRL2_IMD_GLOBAL_REGDONE_EN_SHIFT)          /* 0x00002000 */
#define VOP_SYS_CTRL2_FS_ADDR_MASK_EN_SHIFT                (14U)
#define VOP_SYS_CTRL2_FS_ADDR_MASK_EN_MASK                 (0x1U << VOP_SYS_CTRL2_FS_ADDR_MASK_EN_SHIFT)                /* 0x00004000 */
#define VOP_SYS_CTRL2_DCF_IDLE_EN_SHIFT                    (15U)
#define VOP_SYS_CTRL2_DCF_IDLE_EN_MASK                     (0x1U << VOP_SYS_CTRL2_DCF_IDLE_EN_SHIFT)                    /* 0x00008000 */
#define VOP_SYS_CTRL2_POST_EMPTY_HOLD_EN_SHIFT             (27U)
#define VOP_SYS_CTRL2_POST_EMPTY_HOLD_EN_MASK              (0x1U << VOP_SYS_CTRL2_POST_EMPTY_HOLD_EN_SHIFT)             /* 0x08000000 */
#define VOP_SYS_CTRL2_DSC_EN_SHIFT                         (28U)
#define VOP_SYS_CTRL2_DSC_EN_MASK                          (0x1U << VOP_SYS_CTRL2_DSC_EN_SHIFT)                         /* 0x10000000 */
#define VOP_SYS_CTRL2_DSC_BYPASS_EN_SHIFT                  (29U)
#define VOP_SYS_CTRL2_DSC_BYPASS_EN_MASK                   (0x1U << VOP_SYS_CTRL2_DSC_BYPASS_EN_SHIFT)                  /* 0x20000000 */
#define VOP_SYS_CTRL2_DPHY_FRM_SWITCH_EN_SHIFT             (30U)
#define VOP_SYS_CTRL2_DPHY_FRM_SWITCH_EN_MASK              (0x1U << VOP_SYS_CTRL2_DPHY_FRM_SWITCH_EN_SHIFT)             /* 0x40000000 */
#define VOP_SYS_CTRL2_IMD_EDPI_WMS_MODE_SHIFT              (31U)
#define VOP_SYS_CTRL2_IMD_EDPI_WMS_MODE_MASK               (0x1U << VOP_SYS_CTRL2_IMD_EDPI_WMS_MODE_SHIFT)              /* 0x80000000 */
/* DSP_CTRL0 */
#define VOP_DSP_CTRL0_OFFSET                               (0x20U)
#define VOP_DSP_CTRL0_RGB_DCLK_EN_SHIFT                    (0U)
#define VOP_DSP_CTRL0_RGB_DCLK_EN_MASK                     (0x1U << VOP_DSP_CTRL0_RGB_DCLK_EN_SHIFT)                    /* 0x00000001 */
#define VOP_DSP_CTRL0_RGB_DCLK_POL_SHIFT                   (1U)
#define VOP_DSP_CTRL0_RGB_DCLK_POL_MASK                    (0x1U << VOP_DSP_CTRL0_RGB_DCLK_POL_SHIFT)                   /* 0x00000002 */
#define VOP_DSP_CTRL0_RGB_HSYNC_POL_SHIFT                  (2U)
#define VOP_DSP_CTRL0_RGB_HSYNC_POL_MASK                   (0x1U << VOP_DSP_CTRL0_RGB_HSYNC_POL_SHIFT)                  /* 0x00000004 */
#define VOP_DSP_CTRL0_RGB_VSYNC_POL_SHIFT                  (3U)
#define VOP_DSP_CTRL0_RGB_VSYNC_POL_MASK                   (0x1U << VOP_DSP_CTRL0_RGB_VSYNC_POL_SHIFT)                  /* 0x00000008 */
#define VOP_DSP_CTRL0_RGB_DEN_POL_SHIFT                    (4U)
#define VOP_DSP_CTRL0_RGB_DEN_POL_MASK                     (0x1U << VOP_DSP_CTRL0_RGB_DEN_POL_SHIFT)                    /* 0x00000010 */
#define VOP_DSP_CTRL0_MIPI_DCLK_EN_SHIFT                   (24U)
#define VOP_DSP_CTRL0_MIPI_DCLK_EN_MASK                    (0x1U << VOP_DSP_CTRL0_MIPI_DCLK_EN_SHIFT)                   /* 0x01000000 */
#define VOP_DSP_CTRL0_MIPI_DCLK_POL_SHIFT                  (25U)
#define VOP_DSP_CTRL0_MIPI_DCLK_POL_MASK                   (0x1U << VOP_DSP_CTRL0_MIPI_DCLK_POL_SHIFT)                  /* 0x02000000 */
#define VOP_DSP_CTRL0_MIPI_HSYNC_POL_SHIFT                 (26U)
#define VOP_DSP_CTRL0_MIPI_HSYNC_POL_MASK                  (0x1U << VOP_DSP_CTRL0_MIPI_HSYNC_POL_SHIFT)                 /* 0x04000000 */
#define VOP_DSP_CTRL0_MIPI_VSYNC_POL_SHIFT                 (27U)
#define VOP_DSP_CTRL0_MIPI_VSYNC_POL_MASK                  (0x1U << VOP_DSP_CTRL0_MIPI_VSYNC_POL_SHIFT)                 /* 0x08000000 */
#define VOP_DSP_CTRL0_MIPI_DEN_POL_SHIFT                   (28U)
#define VOP_DSP_CTRL0_MIPI_DEN_POL_MASK                    (0x1U << VOP_DSP_CTRL0_MIPI_DEN_POL_SHIFT)                   /* 0x10000000 */
/* DSP_CTRL1 */
#define VOP_DSP_CTRL1_OFFSET                               (0x24U)
#define VOP_DSP_CTRL1_RESERVED_SHIFT                       (0U)
#define VOP_DSP_CTRL1_RESERVED_MASK                        (0xFFFFFFFFU << VOP_DSP_CTRL1_RESERVED_SHIFT)                /* 0xFFFFFFFF */
/* DSP_CTRL2 */
#define VOP_DSP_CTRL2_OFFSET                               (0x28U)
#define VOP_DSP_CTRL2_DITHER_UP_SHIFT                      (2U)
#define VOP_DSP_CTRL2_DITHER_UP_MASK                       (0x1U << VOP_DSP_CTRL2_DITHER_UP_SHIFT)                      /* 0x00000004 */
#define VOP_DSP_CTRL2_SW_OVERLAY_MODE_SHIFT                (4U)
#define VOP_DSP_CTRL2_SW_OVERLAY_MODE_MASK                 (0x1U << VOP_DSP_CTRL2_SW_OVERLAY_MODE_SHIFT)                /* 0x00000010 */
#define VOP_DSP_CTRL2_DSP_LUT_EN_SHIFT                     (5U)
#define VOP_DSP_CTRL2_DSP_LUT_EN_MASK                      (0x1U << VOP_DSP_CTRL2_DSP_LUT_EN_SHIFT)                     /* 0x00000020 */
#define VOP_DSP_CTRL2_DITHER_DOWN_MODE_SHIFT               (6U)
#define VOP_DSP_CTRL2_DITHER_DOWN_MODE_MASK                (0x1U << VOP_DSP_CTRL2_DITHER_DOWN_MODE_SHIFT)               /* 0x00000040 */
#define VOP_DSP_CTRL2_DITHER_DOWN_SEL_SHIFT                (7U)
#define VOP_DSP_CTRL2_DITHER_DOWN_SEL_MASK                 (0x1U << VOP_DSP_CTRL2_DITHER_DOWN_SEL_SHIFT)                /* 0x00000080 */
#define VOP_DSP_CTRL2_DITHER_DOWN_SHIFT                    (8U)
#define VOP_DSP_CTRL2_DITHER_DOWN_MASK                     (0x1U << VOP_DSP_CTRL2_DITHER_DOWN_SHIFT)                    /* 0x00000100 */
#define VOP_DSP_CTRL2_DSP_BG_SWAP_SHIFT                    (9U)
#define VOP_DSP_CTRL2_DSP_BG_SWAP_MASK                     (0x1U << VOP_DSP_CTRL2_DSP_BG_SWAP_SHIFT)                    /* 0x00000200 */
#define VOP_DSP_CTRL2_DSP_RB_SWAP_SHIFT                    (11U)
#define VOP_DSP_CTRL2_DSP_RB_SWAP_MASK                     (0x1U << VOP_DSP_CTRL2_DSP_RB_SWAP_SHIFT)                    /* 0x00000800 */
#define VOP_DSP_CTRL2_DSP_RG_SWAP_SHIFT                    (12U)
#define VOP_DSP_CTRL2_DSP_RG_SWAP_MASK                     (0x1U << VOP_DSP_CTRL2_DSP_RG_SWAP_SHIFT)                    /* 0x00001000 */
#define VOP_DSP_CTRL2_DSP_BLANK_EN_SHIFT                   (14U)
#define VOP_DSP_CTRL2_DSP_BLANK_EN_MASK                    (0x1U << VOP_DSP_CTRL2_DSP_BLANK_EN_SHIFT)                   /* 0x00004000 */
#define VOP_DSP_CTRL2_DSP_BLACK_EN_SHIFT                   (15U)
#define VOP_DSP_CTRL2_DSP_BLACK_EN_MASK                    (0x1U << VOP_DSP_CTRL2_DSP_BLACK_EN_SHIFT)                   /* 0x00008000 */
#define VOP_DSP_CTRL2_DSP_OUT_MODE_SHIFT                   (16U)
#define VOP_DSP_CTRL2_DSP_OUT_MODE_MASK                    (0xFU << VOP_DSP_CTRL2_DSP_OUT_MODE_SHIFT)                   /* 0x000F0000 */
#define VOP_DSP_CTRL2_DSP_LAYER1_SEL_SHIFT                 (22U)
#define VOP_DSP_CTRL2_DSP_LAYER1_SEL_MASK                  (0x3U << VOP_DSP_CTRL2_DSP_LAYER1_SEL_SHIFT)                 /* 0x00C00000 */
#define VOP_DSP_CTRL2_DSP_LAYER2_SEL_SHIFT                 (24U)
#define VOP_DSP_CTRL2_DSP_LAYER2_SEL_MASK                  (0x3U << VOP_DSP_CTRL2_DSP_LAYER2_SEL_SHIFT)                 /* 0x03000000 */
#define VOP_DSP_CTRL2_DSP_LAYER3_SEL_SHIFT                 (26U)
#define VOP_DSP_CTRL2_DSP_LAYER3_SEL_MASK                  (0x3U << VOP_DSP_CTRL2_DSP_LAYER3_SEL_SHIFT)                 /* 0x0C000000 */
/* VOP_STATUS */
#define VOP_VOP_STATUS_OFFSET                              (0x2CU)
#define VOP_VOP_STATUS_DSP_BLANKING_EN_ASYNC_AFF2_SHIFT    (0U)
#define VOP_VOP_STATUS_DSP_BLANKING_EN_ASYNC_AFF2_MASK     (0x1U << VOP_VOP_STATUS_DSP_BLANKING_EN_ASYNC_AFF2_SHIFT)    /* 0x00000001 */
#define VOP_VOP_STATUS_DPHY_SWITCH_STATUS_SHIFT            (1U)
#define VOP_VOP_STATUS_DPHY_SWITCH_STATUS_MASK             (0x1U << VOP_VOP_STATUS_DPHY_SWITCH_STATUS_SHIFT)            /* 0x00000002 */
#define VOP_VOP_STATUS_INT_RAW_DMA_FINISH_SHIFT            (2U)
#define VOP_VOP_STATUS_INT_RAW_DMA_FINISH_MASK             (0x1U << VOP_VOP_STATUS_INT_RAW_DMA_FINISH_SHIFT)            /* 0x00000004 */
#define VOP_VOP_STATUS_DMA_STOP_VALID_SHIFT                (4U)
#define VOP_VOP_STATUS_DMA_STOP_VALID_MASK                 (0x1U << VOP_VOP_STATUS_DMA_STOP_VALID_SHIFT)                /* 0x00000010 */
#define VOP_VOP_STATUS_INTR_DMA_FINISH_MUX_SHIFT           (8U)
#define VOP_VOP_STATUS_INTR_DMA_FINISH_MUX_MASK            (0x1U << VOP_VOP_STATUS_INTR_DMA_FINISH_MUX_SHIFT)           /* 0x00000100 */
#define VOP_VOP_STATUS_INTR_LINE_FLAG0_MUX_SHIFT           (9U)
#define VOP_VOP_STATUS_INTR_LINE_FLAG0_MUX_MASK            (0x1U << VOP_VOP_STATUS_INTR_LINE_FLAG0_MUX_SHIFT)           /* 0x00000200 */
#define VOP_VOP_STATUS_INTR_LINE_FLAG1_MUX_SHIFT           (10U)
#define VOP_VOP_STATUS_INTR_LINE_FLAG1_MUX_MASK            (0x1U << VOP_VOP_STATUS_INTR_LINE_FLAG1_MUX_SHIFT)           /* 0x00000400 */
/* LINE_FLAG */
#define VOP_LINE_FLAG_OFFSET                               (0x30U)
#define VOP_LINE_FLAG_DSP_LINE_FLAG0_NUM_SHIFT             (0U)
#define VOP_LINE_FLAG_DSP_LINE_FLAG0_NUM_MASK              (0xFFFU << VOP_LINE_FLAG_DSP_LINE_FLAG0_NUM_SHIFT)           /* 0x00000FFF */
#define VOP_LINE_FLAG_DSP_LINE_FLAG1_NUM_SHIFT             (16U)
#define VOP_LINE_FLAG_DSP_LINE_FLAG1_NUM_MASK              (0xFFFU << VOP_LINE_FLAG_DSP_LINE_FLAG1_NUM_SHIFT)           /* 0x0FFF0000 */
/* INTR_EN */
#define VOP_INTR_EN_OFFSET                                 (0x34U)
#define VOP_INTR_EN_FS0_INTR_EN_SHIFT                      (0U)
#define VOP_INTR_EN_FS0_INTR_EN_MASK                       (0x1U << VOP_INTR_EN_FS0_INTR_EN_SHIFT)                      /* 0x00000001 */
#define VOP_INTR_EN_FS1_INTR_EN_SHIFT                      (1U)
#define VOP_INTR_EN_FS1_INTR_EN_MASK                       (0x1U << VOP_INTR_EN_FS1_INTR_EN_SHIFT)                      /* 0x00000002 */
#define VOP_INTR_EN_ADDR_SAME_INTR_EN_SHIFT                (2U)
#define VOP_INTR_EN_ADDR_SAME_INTR_EN_MASK                 (0x1U << VOP_INTR_EN_ADDR_SAME_INTR_EN_SHIFT)                /* 0x00000004 */
#define VOP_INTR_EN_LINE_FLAG0_INTR_EN_SHIFT               (3U)
#define VOP_INTR_EN_LINE_FLAG0_INTR_EN_MASK                (0x1U << VOP_INTR_EN_LINE_FLAG0_INTR_EN_SHIFT)               /* 0x00000008 */
#define VOP_INTR_EN_LINE_FLAG1_INTR_EN_SHIFT               (4U)
#define VOP_INTR_EN_LINE_FLAG1_INTR_EN_MASK                (0x1U << VOP_INTR_EN_LINE_FLAG1_INTR_EN_SHIFT)               /* 0x00000010 */
#define VOP_INTR_EN_BUS_ERROR_INTR_EN_SHIFT                (5U)
#define VOP_INTR_EN_BUS_ERROR_INTR_EN_MASK                 (0x1U << VOP_INTR_EN_BUS_ERROR_INTR_EN_SHIFT)                /* 0x00000020 */
#define VOP_INTR_EN_WIN0_EMPTY_INTR_EN_SHIFT               (7U)
#define VOP_INTR_EN_WIN0_EMPTY_INTR_EN_MASK                (0x1U << VOP_INTR_EN_WIN0_EMPTY_INTR_EN_SHIFT)               /* 0x00000080 */
#define VOP_INTR_EN_WIN1_EMPTY_INTR_EN_SHIFT               (8U)
#define VOP_INTR_EN_WIN1_EMPTY_INTR_EN_MASK                (0x1U << VOP_INTR_EN_WIN1_EMPTY_INTR_EN_SHIFT)               /* 0x00000100 */
#define VOP_INTR_EN_WIN2_EMPTY_INTR_EN_SHIFT               (9U)
#define VOP_INTR_EN_WIN2_EMPTY_INTR_EN_MASK                (0x1U << VOP_INTR_EN_WIN2_EMPTY_INTR_EN_SHIFT)               /* 0x00000200 */
#define VOP_INTR_EN_DSP_HOLD_VALID_INTR_EN_SHIFT           (10U)
#define VOP_INTR_EN_DSP_HOLD_VALID_INTR_EN_MASK            (0x1U << VOP_INTR_EN_DSP_HOLD_VALID_INTR_EN_SHIFT)           /* 0x00000400 */
#define VOP_INTR_EN_DMA_FRM_FSH_INTR_EN_SHIFT              (11U)
#define VOP_INTR_EN_DMA_FRM_FSH_INTR_EN_MASK               (0x1U << VOP_INTR_EN_DMA_FRM_FSH_INTR_EN_SHIFT)              /* 0x00000800 */
#define VOP_INTR_EN_POST_EMPTY_INTR_EN_SHIFT               (12U)
#define VOP_INTR_EN_POST_EMPTY_INTR_EN_MASK                (0x1U << VOP_INTR_EN_POST_EMPTY_INTR_EN_SHIFT)               /* 0x00001000 */
#define VOP_INTR_EN_POST_LB_ALMOST_FULL_INTR_EN_SHIFT      (13U)
#define VOP_INTR_EN_POST_LB_ALMOST_FULL_INTR_EN_MASK       (0x1U << VOP_INTR_EN_POST_LB_ALMOST_FULL_INTR_EN_SHIFT)      /* 0x00002000 */
#define VOP_INTR_EN_POST_LB_ALMOST_EMPTY_INTR_EN_SHIFT     (14U)
#define VOP_INTR_EN_POST_LB_ALMOST_EMPTY_INTR_EN_MASK      (0x1U << VOP_INTR_EN_POST_LB_ALMOST_EMPTY_INTR_EN_SHIFT)     /* 0x00004000 */
/* INTR_CLEAR */
#define VOP_INTR_CLEAR_OFFSET                              (0x38U)
#define VOP_INTR_CLEAR_FS0_INTR_CLR_SHIFT                  (0U)
#define VOP_INTR_CLEAR_FS0_INTR_CLR_MASK                   (0x1U << VOP_INTR_CLEAR_FS0_INTR_CLR_SHIFT)                  /* 0x00000001 */
#define VOP_INTR_CLEAR_FS1_INTR_CLR_SHIFT                  (1U)
#define VOP_INTR_CLEAR_FS1_INTR_CLR_MASK                   (0x1U << VOP_INTR_CLEAR_FS1_INTR_CLR_SHIFT)                  /* 0x00000002 */
#define VOP_INTR_CLEAR_ADDR_SAME_INTR_CLR_SHIFT            (2U)
#define VOP_INTR_CLEAR_ADDR_SAME_INTR_CLR_MASK             (0x1U << VOP_INTR_CLEAR_ADDR_SAME_INTR_CLR_SHIFT)            /* 0x00000004 */
#define VOP_INTR_CLEAR_LINE_FLAG0_INTR_CLR_SHIFT           (3U)
#define VOP_INTR_CLEAR_LINE_FLAG0_INTR_CLR_MASK            (0x1U << VOP_INTR_CLEAR_LINE_FLAG0_INTR_CLR_SHIFT)           /* 0x00000008 */
#define VOP_INTR_CLEAR_LINE_FLAG1_INTR_CLR_SHIFT           (4U)
#define VOP_INTR_CLEAR_LINE_FLAG1_INTR_CLR_MASK            (0x1U << VOP_INTR_CLEAR_LINE_FLAG1_INTR_CLR_SHIFT)           /* 0x00000010 */
#define VOP_INTR_CLEAR_BUS_ERROR_INTR_CLR_SHIFT            (5U)
#define VOP_INTR_CLEAR_BUS_ERROR_INTR_CLR_MASK             (0x1U << VOP_INTR_CLEAR_BUS_ERROR_INTR_CLR_SHIFT)            /* 0x00000020 */
#define VOP_INTR_CLEAR_WIN0_EMPTY_INTR_CLR_SHIFT           (7U)
#define VOP_INTR_CLEAR_WIN0_EMPTY_INTR_CLR_MASK            (0x1U << VOP_INTR_CLEAR_WIN0_EMPTY_INTR_CLR_SHIFT)           /* 0x00000080 */
#define VOP_INTR_CLEAR_WIN1_EMPTY_INTR_CLR_SHIFT           (8U)
#define VOP_INTR_CLEAR_WIN1_EMPTY_INTR_CLR_MASK            (0x1U << VOP_INTR_CLEAR_WIN1_EMPTY_INTR_CLR_SHIFT)           /* 0x00000100 */
#define VOP_INTR_CLEAR_WIN2_EMPTY_INTR_CLR_SHIFT           (9U)
#define VOP_INTR_CLEAR_WIN2_EMPTY_INTR_CLR_MASK            (0x1U << VOP_INTR_CLEAR_WIN2_EMPTY_INTR_CLR_SHIFT)           /* 0x00000200 */
#define VOP_INTR_CLEAR_DSP_HOLD_VALID_INTR_CLR_SHIFT       (10U)
#define VOP_INTR_CLEAR_DSP_HOLD_VALID_INTR_CLR_MASK        (0x1U << VOP_INTR_CLEAR_DSP_HOLD_VALID_INTR_CLR_SHIFT)       /* 0x00000400 */
#define VOP_INTR_CLEAR_DMA_FRM_FSH_INTR_CLR_SHIFT          (11U)
#define VOP_INTR_CLEAR_DMA_FRM_FSH_INTR_CLR_MASK           (0x1U << VOP_INTR_CLEAR_DMA_FRM_FSH_INTR_CLR_SHIFT)          /* 0x00000800 */
#define VOP_INTR_CLEAR_POST_EMPTY_INTR_CLR_SHIFT           (12U)
#define VOP_INTR_CLEAR_POST_EMPTY_INTR_CLR_MASK            (0x1U << VOP_INTR_CLEAR_POST_EMPTY_INTR_CLR_SHIFT)           /* 0x00001000 */
#define VOP_INTR_CLEAR_POST_LB_ALMOST_FULL_INTR_CLR_SHIFT  (13U)
#define VOP_INTR_CLEAR_POST_LB_ALMOST_FULL_INTR_CLR_MASK   (0x1U << VOP_INTR_CLEAR_POST_LB_ALMOST_FULL_INTR_CLR_SHIFT)  /* 0x00002000 */
#define VOP_INTR_CLEAR_POST_LB_ALMOST_EMPTY_INTR_CLR_SHIFT (14U)
#define VOP_INTR_CLEAR_POST_LB_ALMOST_EMPTY_INTR_CLR_MASK  (0x1U << VOP_INTR_CLEAR_POST_LB_ALMOST_EMPTY_INTR_CLR_SHIFT) /* 0x00004000 */
/* INTR_STATUS */
#define VOP_INTR_STATUS_OFFSET                             (0x3CU)
#define VOP_INTR_STATUS_FS0_INTR_STS_SHIFT                 (0U)
#define VOP_INTR_STATUS_FS0_INTR_STS_MASK                  (0x1U << VOP_INTR_STATUS_FS0_INTR_STS_SHIFT)                 /* 0x00000001 */
#define VOP_INTR_STATUS_FS1_INTR_STS_SHIFT                 (1U)
#define VOP_INTR_STATUS_FS1_INTR_STS_MASK                  (0x1U << VOP_INTR_STATUS_FS1_INTR_STS_SHIFT)                 /* 0x00000002 */
#define VOP_INTR_STATUS_ADDR_SAME_INTR_STS_SHIFT           (2U)
#define VOP_INTR_STATUS_ADDR_SAME_INTR_STS_MASK            (0x1U << VOP_INTR_STATUS_ADDR_SAME_INTR_STS_SHIFT)           /* 0x00000004 */
#define VOP_INTR_STATUS_LINE_FLAG0_INTR_STS_SHIFT          (3U)
#define VOP_INTR_STATUS_LINE_FLAG0_INTR_STS_MASK           (0x1U << VOP_INTR_STATUS_LINE_FLAG0_INTR_STS_SHIFT)          /* 0x00000008 */
#define VOP_INTR_STATUS_LINE_FLAG1_INTR_STS_SHIFT          (4U)
#define VOP_INTR_STATUS_LINE_FLAG1_INTR_STS_MASK           (0x1U << VOP_INTR_STATUS_LINE_FLAG1_INTR_STS_SHIFT)          /* 0x00000010 */
#define VOP_INTR_STATUS_BUS_ERROR_INTR_STS_SHIFT           (5U)
#define VOP_INTR_STATUS_BUS_ERROR_INTR_STS_MASK            (0x1U << VOP_INTR_STATUS_BUS_ERROR_INTR_STS_SHIFT)           /* 0x00000020 */
#define VOP_INTR_STATUS_WIN0_EMPTY_INTR_STS_SHIFT          (7U)
#define VOP_INTR_STATUS_WIN0_EMPTY_INTR_STS_MASK           (0x1U << VOP_INTR_STATUS_WIN0_EMPTY_INTR_STS_SHIFT)          /* 0x00000080 */
#define VOP_INTR_STATUS_WIN1_EMPTY_INTR_STS_SHIFT          (8U)
#define VOP_INTR_STATUS_WIN1_EMPTY_INTR_STS_MASK           (0x1U << VOP_INTR_STATUS_WIN1_EMPTY_INTR_STS_SHIFT)          /* 0x00000100 */
#define VOP_INTR_STATUS_WIN2_EMPTY_INTR_STS_SHIFT          (9U)
#define VOP_INTR_STATUS_WIN2_EMPTY_INTR_STS_MASK           (0x1U << VOP_INTR_STATUS_WIN2_EMPTY_INTR_STS_SHIFT)          /* 0x00000200 */
#define VOP_INTR_STATUS_DSP_HOLD_VALID_INTR_STS_SHIFT      (10U)
#define VOP_INTR_STATUS_DSP_HOLD_VALID_INTR_STS_MASK       (0x1U << VOP_INTR_STATUS_DSP_HOLD_VALID_INTR_STS_SHIFT)      /* 0x00000400 */
#define VOP_INTR_STATUS_DMA_FRM_FSH_INTR_STS_SHIFT         (11U)
#define VOP_INTR_STATUS_DMA_FRM_FSH_INTR_STS_MASK          (0x1U << VOP_INTR_STATUS_DMA_FRM_FSH_INTR_STS_SHIFT)         /* 0x00000800 */
#define VOP_INTR_STATUS_POST_EMPTY_INTR_STS_SHIFT          (12U)
#define VOP_INTR_STATUS_POST_EMPTY_INTR_STS_MASK           (0x1U << VOP_INTR_STATUS_POST_EMPTY_INTR_STS_SHIFT)          /* 0x00001000 */
#define VOP_INTR_STATUS_POST_LB_ALMOST_FULL_INTR_SHIFT     (13U)
#define VOP_INTR_STATUS_POST_LB_ALMOST_FULL_INTR_MASK      (0x1U << VOP_INTR_STATUS_POST_LB_ALMOST_FULL_INTR_SHIFT)     /* 0x00002000 */
#define VOP_INTR_STATUS_POST_LB_ALMOST_EMPTY_INTR_STS_SHIFT (14U)
#define VOP_INTR_STATUS_POST_LB_ALMOST_EMPTY_INTR_STS_MASK (0x1U << VOP_INTR_STATUS_POST_LB_ALMOST_EMPTY_INTR_STS_SHIFT) /* 0x00004000 */
#define VOP_INTR_STATUS_FS0_INTR_RAW_STS_SHIFT             (16U)
#define VOP_INTR_STATUS_FS0_INTR_RAW_STS_MASK              (0x1U << VOP_INTR_STATUS_FS0_INTR_RAW_STS_SHIFT)             /* 0x00010000 */
#define VOP_INTR_STATUS_FS1_INTR_RAW_STS_SHIFT             (17U)
#define VOP_INTR_STATUS_FS1_INTR_RAW_STS_MASK              (0x1U << VOP_INTR_STATUS_FS1_INTR_RAW_STS_SHIFT)             /* 0x00020000 */
#define VOP_INTR_STATUS_ADDR_SAME_INTR_RAW_STS_SHIFT       (18U)
#define VOP_INTR_STATUS_ADDR_SAME_INTR_RAW_STS_MASK        (0x1U << VOP_INTR_STATUS_ADDR_SAME_INTR_RAW_STS_SHIFT)       /* 0x00040000 */
#define VOP_INTR_STATUS_LINE_FLAG0_INTR_RAW_STS_SHIFT      (19U)
#define VOP_INTR_STATUS_LINE_FLAG0_INTR_RAW_STS_MASK       (0x1U << VOP_INTR_STATUS_LINE_FLAG0_INTR_RAW_STS_SHIFT)      /* 0x00080000 */
#define VOP_INTR_STATUS_LINE_FLAG1_INTR_RAW_STS_SHIFT      (20U)
#define VOP_INTR_STATUS_LINE_FLAG1_INTR_RAW_STS_MASK       (0x1U << VOP_INTR_STATUS_LINE_FLAG1_INTR_RAW_STS_SHIFT)      /* 0x00100000 */
#define VOP_INTR_STATUS_BUS_ERROR_INTR_RAW_STS_SHIFT       (21U)
#define VOP_INTR_STATUS_BUS_ERROR_INTR_RAW_STS_MASK        (0x1U << VOP_INTR_STATUS_BUS_ERROR_INTR_RAW_STS_SHIFT)       /* 0x00200000 */
#define VOP_INTR_STATUS_WIN0_EMPTY_INTR_RAW_STS_SHIFT      (23U)
#define VOP_INTR_STATUS_WIN0_EMPTY_INTR_RAW_STS_MASK       (0x1U << VOP_INTR_STATUS_WIN0_EMPTY_INTR_RAW_STS_SHIFT)      /* 0x00800000 */
#define VOP_INTR_STATUS_WIN1_EMPTY_INTR_RAW_STS_SHIFT      (24U)
#define VOP_INTR_STATUS_WIN1_EMPTY_INTR_RAW_STS_MASK       (0x1U << VOP_INTR_STATUS_WIN1_EMPTY_INTR_RAW_STS_SHIFT)      /* 0x01000000 */
#define VOP_INTR_STATUS_WIN2_EMPTY_INTR_RAW_STS_SHIFT      (25U)
#define VOP_INTR_STATUS_WIN2_EMPTY_INTR_RAW_STS_MASK       (0x1U << VOP_INTR_STATUS_WIN2_EMPTY_INTR_RAW_STS_SHIFT)      /* 0x02000000 */
#define VOP_INTR_STATUS_DSP_HOLD_VALID_INTR_RAW_STS_SHIFT  (26U)
#define VOP_INTR_STATUS_DSP_HOLD_VALID_INTR_RAW_STS_MASK   (0x1U << VOP_INTR_STATUS_DSP_HOLD_VALID_INTR_RAW_STS_SHIFT)  /* 0x04000000 */
#define VOP_INTR_STATUS_DMA_FRM_FSH_INTR_RAW_STS_SHIFT     (27U)
#define VOP_INTR_STATUS_DMA_FRM_FSH_INTR_RAW_STS_MASK      (0x1U << VOP_INTR_STATUS_DMA_FRM_FSH_INTR_RAW_STS_SHIFT)     /* 0x08000000 */
#define VOP_INTR_STATUS_POST_EMPTY_INTR_RAW_SHIFT          (28U)
#define VOP_INTR_STATUS_POST_EMPTY_INTR_RAW_MASK           (0x1U << VOP_INTR_STATUS_POST_EMPTY_INTR_RAW_SHIFT)          /* 0x10000000 */
#define VOP_INTR_STATUS_POST_LB_ALMOST_FULL_INTR_RAW_SHIFT (29U)
#define VOP_INTR_STATUS_POST_LB_ALMOST_FULL_INTR_RAW_MASK  (0x1U << VOP_INTR_STATUS_POST_LB_ALMOST_FULL_INTR_RAW_SHIFT) /* 0x20000000 */
#define VOP_INTR_STATUS_POST_LB_ALMOST_EMPTY_INTR_RAW_STS_SHIFT (30U)
#define VOP_INTR_STATUS_POST_LB_ALMOST_EMPTY_INTR_RAW_STS_MASK (0x1U << VOP_INTR_STATUS_POST_LB_ALMOST_EMPTY_INTR_RAW_STS_SHIFT) /* 0x40000000 */
/* WIN0_CTRL0 */
#define VOP_WIN0_CTRL0_OFFSET                              (0x40U)
#define VOP_WIN0_CTRL0_WIN0_EN_SHIFT                       (0U)
#define VOP_WIN0_CTRL0_WIN0_EN_MASK                        (0x1U << VOP_WIN0_CTRL0_WIN0_EN_SHIFT)                       /* 0x00000001 */
#define VOP_WIN0_CTRL0_WIN0_LUT_EN_SHIFT                   (1U)
#define VOP_WIN0_CTRL0_WIN0_LUT_EN_MASK                    (0x1U << VOP_WIN0_CTRL0_WIN0_LUT_EN_SHIFT)                   /* 0x00000002 */
#define VOP_WIN0_CTRL0_WIN0_DATA_FMT_SHIFT                 (4U)
#define VOP_WIN0_CTRL0_WIN0_DATA_FMT_MASK                  (0xFU << VOP_WIN0_CTRL0_WIN0_DATA_FMT_SHIFT)                 /* 0x000000F0 */
#define VOP_WIN0_CTRL0_WIN0_BPP_SWAP_SHIFT                 (8U)
#define VOP_WIN0_CTRL0_WIN0_BPP_SWAP_MASK                  (0x1U << VOP_WIN0_CTRL0_WIN0_BPP_SWAP_SHIFT)                 /* 0x00000100 */
#define VOP_WIN0_CTRL0_WIN0_NO_OUTSTANDING_SHIFT           (9U)
#define VOP_WIN0_CTRL0_WIN0_NO_OUTSTANDING_MASK            (0x1U << VOP_WIN0_CTRL0_WIN0_NO_OUTSTANDING_SHIFT)           /* 0x00000200 */
#define VOP_WIN0_CTRL0_WIN0_YUV_4BIT_EN_SHIFT              (10U)
#define VOP_WIN0_CTRL0_WIN0_YUV_4BIT_EN_MASK               (0x1U << VOP_WIN0_CTRL0_WIN0_YUV_4BIT_EN_SHIFT)              /* 0x00000400 */
#define VOP_WIN0_CTRL0_WIN0_BPP_EN_SHIFT                   (11U)
#define VOP_WIN0_CTRL0_WIN0_BPP_EN_MASK                    (0x1U << VOP_WIN0_CTRL0_WIN0_BPP_EN_SHIFT)                   /* 0x00000800 */
#define VOP_WIN0_CTRL0_WIN0_RB_SWAP_SHIFT                  (12U)
#define VOP_WIN0_CTRL0_WIN0_RB_SWAP_MASK                   (0x1U << VOP_WIN0_CTRL0_WIN0_RB_SWAP_SHIFT)                  /* 0x00001000 */
#define VOP_WIN0_CTRL0_WIN0_ALPHA_SWAP_SHIFT               (13U)
#define VOP_WIN0_CTRL0_WIN0_ALPHA_SWAP_MASK                (0x1U << VOP_WIN0_CTRL0_WIN0_ALPHA_SWAP_SHIFT)               /* 0x00002000 */
#define VOP_WIN0_CTRL0_WIN0_ENDIAN_SWAP_SHIFT              (14U)
#define VOP_WIN0_CTRL0_WIN0_ENDIAN_SWAP_MASK               (0x1U << VOP_WIN0_CTRL0_WIN0_ENDIAN_SWAP_SHIFT)              /* 0x00004000 */
#define VOP_WIN0_CTRL0_WIN0_UV_SWAP_SHIFT                  (15U)
#define VOP_WIN0_CTRL0_WIN0_UV_SWAP_MASK                   (0x1U << VOP_WIN0_CTRL0_WIN0_UV_SWAP_SHIFT)                  /* 0x00008000 */
#define VOP_WIN0_CTRL0_WIN0_R2Y_EN_SHIFT                   (16U)
#define VOP_WIN0_CTRL0_WIN0_R2Y_EN_MASK                    (0x1U << VOP_WIN0_CTRL0_WIN0_R2Y_EN_SHIFT)                   /* 0x00010000 */
#define VOP_WIN0_CTRL0_WIN0_Y2R_EN_SHIFT                   (17U)
#define VOP_WIN0_CTRL0_WIN0_Y2R_EN_MASK                    (0x1U << VOP_WIN0_CTRL0_WIN0_Y2R_EN_SHIFT)                   /* 0x00020000 */
#define VOP_WIN0_CTRL0_WIN0_CSC_MODE_SHIFT                 (18U)
#define VOP_WIN0_CTRL0_WIN0_CSC_MODE_MASK                  (0x3U << VOP_WIN0_CTRL0_WIN0_CSC_MODE_SHIFT)                 /* 0x000C0000 */
/* WIN0_CTRL1 */
#define VOP_WIN0_CTRL1_OFFSET                              (0x44U)
#define VOP_WIN0_CTRL1_WIN0_YRGB_GATHER_EN_SHIFT           (0U)
#define VOP_WIN0_CTRL1_WIN0_YRGB_GATHER_EN_MASK            (0x1U << VOP_WIN0_CTRL1_WIN0_YRGB_GATHER_EN_SHIFT)           /* 0x00000001 */
#define VOP_WIN0_CTRL1_WIN0_CBCR_GATHER_EN_SHIFT           (1U)
#define VOP_WIN0_CTRL1_WIN0_CBCR_GATHER_EN_MASK            (0x1U << VOP_WIN0_CTRL1_WIN0_CBCR_GATHER_EN_SHIFT)           /* 0x00000002 */
#define VOP_WIN0_CTRL1_WIN0_DMA_BURST_LENGTH_SHIFT         (2U)
#define VOP_WIN0_CTRL1_WIN0_DMA_BURST_LENGTH_MASK          (0x3U << VOP_WIN0_CTRL1_WIN0_DMA_BURST_LENGTH_SHIFT)         /* 0x0000000C */
#define VOP_WIN0_CTRL1_WIN0_YRGB_GATHER_NUM_SHIFT          (4U)
#define VOP_WIN0_CTRL1_WIN0_YRGB_GATHER_NUM_MASK           (0x3U << VOP_WIN0_CTRL1_WIN0_YRGB_GATHER_NUM_SHIFT)          /* 0x00000030 */
#define VOP_WIN0_CTRL1_WIN0_CBCR_GATHER_NUM_SHIFT          (6U)
#define VOP_WIN0_CTRL1_WIN0_CBCR_GATHER_NUM_MASK           (0x3U << VOP_WIN0_CTRL1_WIN0_CBCR_GATHER_NUM_SHIFT)          /* 0x000000C0 */
#define VOP_WIN0_CTRL1_SW_WIN0_YRGB_RID_SHIFT              (8U)
#define VOP_WIN0_CTRL1_SW_WIN0_YRGB_RID_MASK               (0xFU << VOP_WIN0_CTRL1_SW_WIN0_YRGB_RID_SHIFT)              /* 0x00000F00 */
#define VOP_WIN0_CTRL1_SW_WIN0_CBCR_RID_SHIFT              (12U)
#define VOP_WIN0_CTRL1_SW_WIN0_CBCR_RID_MASK               (0xFU << VOP_WIN0_CTRL1_SW_WIN0_CBCR_RID_SHIFT)              /* 0x0000F000 */
/* WIN0_VIR */
#define VOP_WIN0_VIR_OFFSET                                (0x48U)
#define VOP_WIN0_VIR_WIN0_YRGB_VIR_STRIDE_SHIFT            (0U)
#define VOP_WIN0_VIR_WIN0_YRGB_VIR_STRIDE_MASK             (0xFFFFU << VOP_WIN0_VIR_WIN0_YRGB_VIR_STRIDE_SHIFT)         /* 0x0000FFFF */
#define VOP_WIN0_VIR_WIN0_CBCR_VIR_STRIDE_SHIFT            (16U)
#define VOP_WIN0_VIR_WIN0_CBCR_VIR_STRIDE_MASK             (0xFFFFU << VOP_WIN0_VIR_WIN0_CBCR_VIR_STRIDE_SHIFT)         /* 0xFFFF0000 */
/* WIN0_YRGB_MST */
#define VOP_WIN0_YRGB_MST_OFFSET                           (0x50U)
#define VOP_WIN0_YRGB_MST_WIN0_YRGB_MST_SHIFT              (0U)
#define VOP_WIN0_YRGB_MST_WIN0_YRGB_MST_MASK               (0xFFFFFFFFU << VOP_WIN0_YRGB_MST_WIN0_YRGB_MST_SHIFT)       /* 0xFFFFFFFF */
/* WIN0_DSP_INFO */
#define VOP_WIN0_DSP_INFO_OFFSET                           (0x54U)
#define VOP_WIN0_DSP_INFO_DSP_WIN0_WIDTH_SHIFT             (0U)
#define VOP_WIN0_DSP_INFO_DSP_WIN0_WIDTH_MASK              (0x1FFFU << VOP_WIN0_DSP_INFO_DSP_WIN0_WIDTH_SHIFT)          /* 0x00001FFF */
#define VOP_WIN0_DSP_INFO_DSP_WIN0_HEIGHT_SHIFT            (16U)
#define VOP_WIN0_DSP_INFO_DSP_WIN0_HEIGHT_MASK             (0x1FFFU << VOP_WIN0_DSP_INFO_DSP_WIN0_HEIGHT_SHIFT)         /* 0x1FFF0000 */
/* WIN0_DSP_ST */
#define VOP_WIN0_DSP_ST_OFFSET                             (0x58U)
#define VOP_WIN0_DSP_ST_DSP_WIN0_XST_SHIFT                 (0U)
#define VOP_WIN0_DSP_ST_DSP_WIN0_XST_MASK                  (0x1FFFU << VOP_WIN0_DSP_ST_DSP_WIN0_XST_SHIFT)              /* 0x00001FFF */
#define VOP_WIN0_DSP_ST_DSP_WIN0_YST_SHIFT                 (16U)
#define VOP_WIN0_DSP_ST_DSP_WIN0_YST_MASK                  (0x1FFFU << VOP_WIN0_DSP_ST_DSP_WIN0_YST_SHIFT)              /* 0x1FFF0000 */
/* WIN0_COLOR_KEY */
#define VOP_WIN0_COLOR_KEY_OFFSET                          (0x5CU)
#define VOP_WIN0_COLOR_KEY_WIN0_KEY_COLOR_SHIFT            (0U)
#define VOP_WIN0_COLOR_KEY_WIN0_KEY_COLOR_MASK             (0xFFFFFFU << VOP_WIN0_COLOR_KEY_WIN0_KEY_COLOR_SHIFT)       /* 0x00FFFFFF */
#define VOP_WIN0_COLOR_KEY_WIN0_KEY_EN_SHIFT               (24U)
#define VOP_WIN0_COLOR_KEY_WIN0_KEY_EN_MASK                (0x1U << VOP_WIN0_COLOR_KEY_WIN0_KEY_EN_SHIFT)               /* 0x01000000 */
/* WIN0_ALPHA_CTRL */
#define VOP_WIN0_ALPHA_CTRL_OFFSET                         (0x6CU)
#define VOP_WIN0_ALPHA_CTRL_WIN0_ALPHA_EN_SHIFT            (0U)
#define VOP_WIN0_ALPHA_CTRL_WIN0_ALPHA_EN_MASK             (0x1U << VOP_WIN0_ALPHA_CTRL_WIN0_ALPHA_EN_SHIFT)            /* 0x00000001 */
#define VOP_WIN0_ALPHA_CTRL_WIN0_ALPHA_MODE_SHIFT          (1U)
#define VOP_WIN0_ALPHA_CTRL_WIN0_ALPHA_MODE_MASK           (0x1U << VOP_WIN0_ALPHA_CTRL_WIN0_ALPHA_MODE_SHIFT)          /* 0x00000002 */
#define VOP_WIN0_ALPHA_CTRL_WIN0_ALPHA_PRE_MUL_SHIFT       (2U)
#define VOP_WIN0_ALPHA_CTRL_WIN0_ALPHA_PRE_MUL_MASK        (0x1U << VOP_WIN0_ALPHA_CTRL_WIN0_ALPHA_PRE_MUL_SHIFT)       /* 0x00000004 */
#define VOP_WIN0_ALPHA_CTRL_WIN0_ALPHA_SAT_MODE_SHIFT      (3U)
#define VOP_WIN0_ALPHA_CTRL_WIN0_ALPHA_SAT_MODE_MASK       (0x1U << VOP_WIN0_ALPHA_CTRL_WIN0_ALPHA_SAT_MODE_SHIFT)      /* 0x00000008 */
#define VOP_WIN0_ALPHA_CTRL_WIN0_ALPHA_VALUE_SHIFT         (4U)
#define VOP_WIN0_ALPHA_CTRL_WIN0_ALPHA_VALUE_MASK          (0xFFU << VOP_WIN0_ALPHA_CTRL_WIN0_ALPHA_VALUE_SHIFT)        /* 0x00000FF0 */
/* WIN0_CBCR_MST */
#define VOP_WIN0_CBCR_MST_OFFSET                           (0x70U)
#define VOP_WIN0_CBCR_MST_WIN0_CBCR_MST_SHIFT              (0U)
#define VOP_WIN0_CBCR_MST_WIN0_CBCR_MST_MASK               (0xFFFFFFFFU << VOP_WIN0_CBCR_MST_WIN0_CBCR_MST_SHIFT)       /* 0xFFFFFFFF */
/* WIN0_YRGB_MST_RAW */
#define VOP_WIN0_YRGB_MST_RAW_OFFSET                       (0x74U)
#define VOP_WIN0_YRGB_MST_RAW_WIN0_YRGB_MST_RAW_SHIFT      (0U)
#define VOP_WIN0_YRGB_MST_RAW_WIN0_YRGB_MST_RAW_MASK       (0xFFFFFFFFU << VOP_WIN0_YRGB_MST_RAW_WIN0_YRGB_MST_RAW_SHIFT) /* 0xFFFFFFFF */
/* WIN0_CBCR_MST_RAW */
#define VOP_WIN0_CBCR_MST_RAW_OFFSET                       (0x78U)
#define VOP_WIN0_CBCR_MST_RAW_WIN0_CBCR_MST_RAW_SHIFT      (0U)
#define VOP_WIN0_CBCR_MST_RAW_WIN0_CBCR_MST_RAW_MASK       (0xFFFFFFFFU << VOP_WIN0_CBCR_MST_RAW_WIN0_CBCR_MST_RAW_SHIFT) /* 0xFFFFFFFF */
/* WIN0_LOOP_OFFSET */
#define VOP_WIN0_LOOP_OFFSET_OFFSET                        (0x7CU)
#define VOP_WIN0_LOOP_OFFSET_WIN0_XLOOP_OFFSET_SHIFT       (0U)
#define VOP_WIN0_LOOP_OFFSET_WIN0_XLOOP_OFFSET_MASK        (0x1FFFU << VOP_WIN0_LOOP_OFFSET_WIN0_XLOOP_OFFSET_SHIFT)    /* 0x00001FFF */
#define VOP_WIN0_LOOP_OFFSET_WIN0_XLOOP_EN_SHIFT           (15U)
#define VOP_WIN0_LOOP_OFFSET_WIN0_XLOOP_EN_MASK            (0x1U << VOP_WIN0_LOOP_OFFSET_WIN0_XLOOP_EN_SHIFT)           /* 0x00008000 */
#define VOP_WIN0_LOOP_OFFSET_WIN0_YLOOP_OFFSET_SHIFT       (16U)
#define VOP_WIN0_LOOP_OFFSET_WIN0_YLOOP_OFFSET_MASK        (0x1FFFU << VOP_WIN0_LOOP_OFFSET_WIN0_YLOOP_OFFSET_SHIFT)    /* 0x1FFF0000 */
#define VOP_WIN0_LOOP_OFFSET_WIN0_YLOOP_EN_SHIFT           (31U)
#define VOP_WIN0_LOOP_OFFSET_WIN0_YLOOP_EN_MASK            (0x1U << VOP_WIN0_LOOP_OFFSET_WIN0_YLOOP_EN_SHIFT)           /* 0x80000000 */
/* WIN1_CTRL0 */
#define VOP_WIN1_CTRL0_OFFSET                              (0x80U)
#define VOP_WIN1_CTRL0_WIN1_EN_SHIFT                       (0U)
#define VOP_WIN1_CTRL0_WIN1_EN_MASK                        (0x1U << VOP_WIN1_CTRL0_WIN1_EN_SHIFT)                       /* 0x00000001 */
#define VOP_WIN1_CTRL0_WIN1_DATA_FMT_SHIFT                 (4U)
#define VOP_WIN1_CTRL0_WIN1_DATA_FMT_MASK                  (0xFU << VOP_WIN1_CTRL0_WIN1_DATA_FMT_SHIFT)                 /* 0x000000F0 */
#define VOP_WIN1_CTRL0_WIN1_BPP_SWAP_SHIFT                 (8U)
#define VOP_WIN1_CTRL0_WIN1_BPP_SWAP_MASK                  (0x1U << VOP_WIN1_CTRL0_WIN1_BPP_SWAP_SHIFT)                 /* 0x00000100 */
#define VOP_WIN1_CTRL0_WIN1_NO_OUTSTANDING_SHIFT           (9U)
#define VOP_WIN1_CTRL0_WIN1_NO_OUTSTANDING_MASK            (0x1U << VOP_WIN1_CTRL0_WIN1_NO_OUTSTANDING_SHIFT)           /* 0x00000200 */
#define VOP_WIN1_CTRL0_WIN1_YUV_4BIT_EN_SHIFT              (10U)
#define VOP_WIN1_CTRL0_WIN1_YUV_4BIT_EN_MASK               (0x1U << VOP_WIN1_CTRL0_WIN1_YUV_4BIT_EN_SHIFT)              /* 0x00000400 */
#define VOP_WIN1_CTRL0_WIN1_BPP_EN_SHIFT                   (11U)
#define VOP_WIN1_CTRL0_WIN1_BPP_EN_MASK                    (0x1U << VOP_WIN1_CTRL0_WIN1_BPP_EN_SHIFT)                   /* 0x00000800 */
#define VOP_WIN1_CTRL0_WIN1_RB_SWAP_SHIFT                  (12U)
#define VOP_WIN1_CTRL0_WIN1_RB_SWAP_MASK                   (0x1U << VOP_WIN1_CTRL0_WIN1_RB_SWAP_SHIFT)                  /* 0x00001000 */
#define VOP_WIN1_CTRL0_WIN1_ALPHA_SWAP_SHIFT               (13U)
#define VOP_WIN1_CTRL0_WIN1_ALPHA_SWAP_MASK                (0x1U << VOP_WIN1_CTRL0_WIN1_ALPHA_SWAP_SHIFT)               /* 0x00002000 */
#define VOP_WIN1_CTRL0_WIN1_ENDIAN_SWAP_SHIFT              (14U)
#define VOP_WIN1_CTRL0_WIN1_ENDIAN_SWAP_MASK               (0x1U << VOP_WIN1_CTRL0_WIN1_ENDIAN_SWAP_SHIFT)              /* 0x00004000 */
#define VOP_WIN1_CTRL0_WIN1_UV_SWAP_SHIFT                  (15U)
#define VOP_WIN1_CTRL0_WIN1_UV_SWAP_MASK                   (0x1U << VOP_WIN1_CTRL0_WIN1_UV_SWAP_SHIFT)                  /* 0x00008000 */
#define VOP_WIN1_CTRL0_WIN1_R2Y_EN_SHIFT                   (16U)
#define VOP_WIN1_CTRL0_WIN1_R2Y_EN_MASK                    (0x1U << VOP_WIN1_CTRL0_WIN1_R2Y_EN_SHIFT)                   /* 0x00010000 */
#define VOP_WIN1_CTRL0_WIN1_Y2R_EN_SHIFT                   (17U)
#define VOP_WIN1_CTRL0_WIN1_Y2R_EN_MASK                    (0x1U << VOP_WIN1_CTRL0_WIN1_Y2R_EN_SHIFT)                   /* 0x00020000 */
#define VOP_WIN1_CTRL0_WIN1_CSC_MODE_SHIFT                 (18U)
#define VOP_WIN1_CTRL0_WIN1_CSC_MODE_MASK                  (0x3U << VOP_WIN1_CTRL0_WIN1_CSC_MODE_SHIFT)                 /* 0x000C0000 */
/* WIN1_CTRL1 */
#define VOP_WIN1_CTRL1_OFFSET                              (0x84U)
#define VOP_WIN1_CTRL1_WIN1_YRGB_GATHER_EN_SHIFT           (0U)
#define VOP_WIN1_CTRL1_WIN1_YRGB_GATHER_EN_MASK            (0x1U << VOP_WIN1_CTRL1_WIN1_YRGB_GATHER_EN_SHIFT)           /* 0x00000001 */
#define VOP_WIN1_CTRL1_WIN1_CBCR_GATHER_EN_SHIFT           (1U)
#define VOP_WIN1_CTRL1_WIN1_CBCR_GATHER_EN_MASK            (0x1U << VOP_WIN1_CTRL1_WIN1_CBCR_GATHER_EN_SHIFT)           /* 0x00000002 */
#define VOP_WIN1_CTRL1_WIN1_DMA_BURST_LENGTH_SHIFT         (2U)
#define VOP_WIN1_CTRL1_WIN1_DMA_BURST_LENGTH_MASK          (0x3U << VOP_WIN1_CTRL1_WIN1_DMA_BURST_LENGTH_SHIFT)         /* 0x0000000C */
#define VOP_WIN1_CTRL1_WIN1_YRGB_GATHER_NUM_SHIFT          (4U)
#define VOP_WIN1_CTRL1_WIN1_YRGB_GATHER_NUM_MASK           (0x3U << VOP_WIN1_CTRL1_WIN1_YRGB_GATHER_NUM_SHIFT)          /* 0x00000030 */
#define VOP_WIN1_CTRL1_WIN1_CBCR_GATHER_NUM_SHIFT          (6U)
#define VOP_WIN1_CTRL1_WIN1_CBCR_GATHER_NUM_MASK           (0x3U << VOP_WIN1_CTRL1_WIN1_CBCR_GATHER_NUM_SHIFT)          /* 0x000000C0 */
#define VOP_WIN1_CTRL1_SW_WIN1_YRGB_RID_SHIFT              (8U)
#define VOP_WIN1_CTRL1_SW_WIN1_YRGB_RID_MASK               (0xFU << VOP_WIN1_CTRL1_SW_WIN1_YRGB_RID_SHIFT)              /* 0x00000F00 */
#define VOP_WIN1_CTRL1_SW_WIN1_CBCR_RID_SHIFT              (12U)
#define VOP_WIN1_CTRL1_SW_WIN1_CBCR_RID_MASK               (0xFU << VOP_WIN1_CTRL1_SW_WIN1_CBCR_RID_SHIFT)              /* 0x0000F000 */
/* WIN1_VIR */
#define VOP_WIN1_VIR_OFFSET                                (0x88U)
#define VOP_WIN1_VIR_WIN1_YRGB_VIR_STRIDE_SHIFT            (0U)
#define VOP_WIN1_VIR_WIN1_YRGB_VIR_STRIDE_MASK             (0xFFFFU << VOP_WIN1_VIR_WIN1_YRGB_VIR_STRIDE_SHIFT)         /* 0x0000FFFF */
#define VOP_WIN1_VIR_WIN1_CBCR_VIR_STRIDE_SHIFT            (16U)
#define VOP_WIN1_VIR_WIN1_CBCR_VIR_STRIDE_MASK             (0xFFFFU << VOP_WIN1_VIR_WIN1_CBCR_VIR_STRIDE_SHIFT)         /* 0xFFFF0000 */
/* WIN1_YRGB_MST */
#define VOP_WIN1_YRGB_MST_OFFSET                           (0x90U)
#define VOP_WIN1_YRGB_MST_WIN1_YRGB_MST_SHIFT              (0U)
#define VOP_WIN1_YRGB_MST_WIN1_YRGB_MST_MASK               (0xFFFFFFFFU << VOP_WIN1_YRGB_MST_WIN1_YRGB_MST_SHIFT)       /* 0xFFFFFFFF */
/* WIN1_DSP_INFO */
#define VOP_WIN1_DSP_INFO_OFFSET                           (0x94U)
#define VOP_WIN1_DSP_INFO_DSP_WIN1_WIDTH_SHIFT             (0U)
#define VOP_WIN1_DSP_INFO_DSP_WIN1_WIDTH_MASK              (0x1FFFU << VOP_WIN1_DSP_INFO_DSP_WIN1_WIDTH_SHIFT)          /* 0x00001FFF */
#define VOP_WIN1_DSP_INFO_DSP_WIN1_HEIGHT_SHIFT            (16U)
#define VOP_WIN1_DSP_INFO_DSP_WIN1_HEIGHT_MASK             (0x1FFFU << VOP_WIN1_DSP_INFO_DSP_WIN1_HEIGHT_SHIFT)         /* 0x1FFF0000 */
/* WIN1_DSP_ST */
#define VOP_WIN1_DSP_ST_OFFSET                             (0x98U)
#define VOP_WIN1_DSP_ST_DSP_WIN1_XST_SHIFT                 (0U)
#define VOP_WIN1_DSP_ST_DSP_WIN1_XST_MASK                  (0x1FFFU << VOP_WIN1_DSP_ST_DSP_WIN1_XST_SHIFT)              /* 0x00001FFF */
#define VOP_WIN1_DSP_ST_DSP_WIN1_YST_SHIFT                 (16U)
#define VOP_WIN1_DSP_ST_DSP_WIN1_YST_MASK                  (0x1FFFU << VOP_WIN1_DSP_ST_DSP_WIN1_YST_SHIFT)              /* 0x1FFF0000 */
/* WIN1_COLOR_KEY */
#define VOP_WIN1_COLOR_KEY_OFFSET                          (0x9CU)
#define VOP_WIN1_COLOR_KEY_WIN1_KEY_COLOR_SHIFT            (0U)
#define VOP_WIN1_COLOR_KEY_WIN1_KEY_COLOR_MASK             (0xFFFFFFU << VOP_WIN1_COLOR_KEY_WIN1_KEY_COLOR_SHIFT)       /* 0x00FFFFFF */
#define VOP_WIN1_COLOR_KEY_WIN1_KEY_EN_SHIFT               (24U)
#define VOP_WIN1_COLOR_KEY_WIN1_KEY_EN_MASK                (0x1U << VOP_WIN1_COLOR_KEY_WIN1_KEY_EN_SHIFT)               /* 0x01000000 */
/* WIN1_ALPHA_CTRL */
#define VOP_WIN1_ALPHA_CTRL_OFFSET                         (0xACU)
#define VOP_WIN1_ALPHA_CTRL_WIN1_ALPHA_EN_SHIFT            (0U)
#define VOP_WIN1_ALPHA_CTRL_WIN1_ALPHA_EN_MASK             (0x1U << VOP_WIN1_ALPHA_CTRL_WIN1_ALPHA_EN_SHIFT)            /* 0x00000001 */
#define VOP_WIN1_ALPHA_CTRL_WIN1_ALPHA_MODE_SHIFT          (1U)
#define VOP_WIN1_ALPHA_CTRL_WIN1_ALPHA_MODE_MASK           (0x1U << VOP_WIN1_ALPHA_CTRL_WIN1_ALPHA_MODE_SHIFT)          /* 0x00000002 */
#define VOP_WIN1_ALPHA_CTRL_WIN1_ALPHA_PRE_MUL_SHIFT       (2U)
#define VOP_WIN1_ALPHA_CTRL_WIN1_ALPHA_PRE_MUL_MASK        (0x1U << VOP_WIN1_ALPHA_CTRL_WIN1_ALPHA_PRE_MUL_SHIFT)       /* 0x00000004 */
#define VOP_WIN1_ALPHA_CTRL_WIN1_ALPHA_SAT_MODE_SHIFT      (3U)
#define VOP_WIN1_ALPHA_CTRL_WIN1_ALPHA_SAT_MODE_MASK       (0x1U << VOP_WIN1_ALPHA_CTRL_WIN1_ALPHA_SAT_MODE_SHIFT)      /* 0x00000008 */
#define VOP_WIN1_ALPHA_CTRL_WIN1_ALPHA_VALUE_SHIFT         (4U)
#define VOP_WIN1_ALPHA_CTRL_WIN1_ALPHA_VALUE_MASK          (0xFFU << VOP_WIN1_ALPHA_CTRL_WIN1_ALPHA_VALUE_SHIFT)        /* 0x00000FF0 */
/* WIN1_CBCR_MST */
#define VOP_WIN1_CBCR_MST_OFFSET                           (0xB0U)
#define VOP_WIN1_CBCR_MST_WIN1_CBCR_MST_SHIFT              (0U)
#define VOP_WIN1_CBCR_MST_WIN1_CBCR_MST_MASK               (0xFFFFFFFFU << VOP_WIN1_CBCR_MST_WIN1_CBCR_MST_SHIFT)       /* 0xFFFFFFFF */
/* WIN1_YRGB_MST_RAW */
#define VOP_WIN1_YRGB_MST_RAW_OFFSET                       (0xB4U)
#define VOP_WIN1_YRGB_MST_RAW_WIN1_YRGB_MST_RAW_SHIFT      (0U)
#define VOP_WIN1_YRGB_MST_RAW_WIN1_YRGB_MST_RAW_MASK       (0xFFFFFFFFU << VOP_WIN1_YRGB_MST_RAW_WIN1_YRGB_MST_RAW_SHIFT) /* 0xFFFFFFFF */
/* WIN1_CBCR_MST_RAW */
#define VOP_WIN1_CBCR_MST_RAW_OFFSET                       (0xB8U)
#define VOP_WIN1_CBCR_MST_RAW_WIN1_CBCR_MST_RAW_SHIFT      (0U)
#define VOP_WIN1_CBCR_MST_RAW_WIN1_CBCR_MST_RAW_MASK       (0xFFFFFFFFU << VOP_WIN1_CBCR_MST_RAW_WIN1_CBCR_MST_RAW_SHIFT) /* 0xFFFFFFFF */
/* WIN1_LOOP_OFFSET */
#define VOP_WIN1_LOOP_OFFSET_OFFSET                        (0xBCU)
#define VOP_WIN1_LOOP_OFFSET_WIN1_XLOOP_OFFSET_SHIFT       (0U)
#define VOP_WIN1_LOOP_OFFSET_WIN1_XLOOP_OFFSET_MASK        (0x1FFFU << VOP_WIN1_LOOP_OFFSET_WIN1_XLOOP_OFFSET_SHIFT)    /* 0x00001FFF */
#define VOP_WIN1_LOOP_OFFSET_WIN1_XLOOP_EN_SHIFT           (15U)
#define VOP_WIN1_LOOP_OFFSET_WIN1_XLOOP_EN_MASK            (0x1U << VOP_WIN1_LOOP_OFFSET_WIN1_XLOOP_EN_SHIFT)           /* 0x00008000 */
#define VOP_WIN1_LOOP_OFFSET_WIN1_YLOOP_OFFSET_SHIFT       (16U)
#define VOP_WIN1_LOOP_OFFSET_WIN1_YLOOP_OFFSET_MASK        (0x1FFFU << VOP_WIN1_LOOP_OFFSET_WIN1_YLOOP_OFFSET_SHIFT)    /* 0x1FFF0000 */
#define VOP_WIN1_LOOP_OFFSET_WIN1_YLOOP_EN_SHIFT           (31U)
#define VOP_WIN1_LOOP_OFFSET_WIN1_YLOOP_EN_MASK            (0x1U << VOP_WIN1_LOOP_OFFSET_WIN1_YLOOP_EN_SHIFT)           /* 0x80000000 */
/* WIN2_CTRL0 */
#define VOP_WIN2_CTRL0_OFFSET                              (0xC0U)
#define VOP_WIN2_CTRL0_WIN2_EN_SHIFT                       (0U)
#define VOP_WIN2_CTRL0_WIN2_EN_MASK                        (0x1U << VOP_WIN2_CTRL0_WIN2_EN_SHIFT)                       /* 0x00000001 */
#define VOP_WIN2_CTRL0_WIN2_DATA_FMT_SHIFT                 (4U)
#define VOP_WIN2_CTRL0_WIN2_DATA_FMT_MASK                  (0xFU << VOP_WIN2_CTRL0_WIN2_DATA_FMT_SHIFT)                 /* 0x000000F0 */
#define VOP_WIN2_CTRL0_WIN2_BPP_SWAP_SHIFT                 (8U)
#define VOP_WIN2_CTRL0_WIN2_BPP_SWAP_MASK                  (0x1U << VOP_WIN2_CTRL0_WIN2_BPP_SWAP_SHIFT)                 /* 0x00000100 */
#define VOP_WIN2_CTRL0_WIN2_NO_OUTSTANDING_SHIFT           (9U)
#define VOP_WIN2_CTRL0_WIN2_NO_OUTSTANDING_MASK            (0x1U << VOP_WIN2_CTRL0_WIN2_NO_OUTSTANDING_SHIFT)           /* 0x00000200 */
#define VOP_WIN2_CTRL0_WIN2_YUV_4BIT_EN_SHIFT              (10U)
#define VOP_WIN2_CTRL0_WIN2_YUV_4BIT_EN_MASK               (0x1U << VOP_WIN2_CTRL0_WIN2_YUV_4BIT_EN_SHIFT)              /* 0x00000400 */
#define VOP_WIN2_CTRL0_WIN2_RB_SWAP_SHIFT                  (12U)
#define VOP_WIN2_CTRL0_WIN2_RB_SWAP_MASK                   (0x1U << VOP_WIN2_CTRL0_WIN2_RB_SWAP_SHIFT)                  /* 0x00001000 */
#define VOP_WIN2_CTRL0_WIN2_ALPHA_SWAP_SHIFT               (13U)
#define VOP_WIN2_CTRL0_WIN2_ALPHA_SWAP_MASK                (0x1U << VOP_WIN2_CTRL0_WIN2_ALPHA_SWAP_SHIFT)               /* 0x00002000 */
#define VOP_WIN2_CTRL0_WIN2_ENDIAN_SWAP_SHIFT              (14U)
#define VOP_WIN2_CTRL0_WIN2_ENDIAN_SWAP_MASK               (0x1U << VOP_WIN2_CTRL0_WIN2_ENDIAN_SWAP_SHIFT)              /* 0x00004000 */
#define VOP_WIN2_CTRL0_WIN2_UV_SWAP_SHIFT                  (15U)
#define VOP_WIN2_CTRL0_WIN2_UV_SWAP_MASK                   (0x1U << VOP_WIN2_CTRL0_WIN2_UV_SWAP_SHIFT)                  /* 0x00008000 */
#define VOP_WIN2_CTRL0_WIN2_R2Y_EN_SHIFT                   (16U)
#define VOP_WIN2_CTRL0_WIN2_R2Y_EN_MASK                    (0x1U << VOP_WIN2_CTRL0_WIN2_R2Y_EN_SHIFT)                   /* 0x00010000 */
#define VOP_WIN2_CTRL0_WIN2_Y2R_EN_SHIFT                   (17U)
#define VOP_WIN2_CTRL0_WIN2_Y2R_EN_MASK                    (0x1U << VOP_WIN2_CTRL0_WIN2_Y2R_EN_SHIFT)                   /* 0x00020000 */
#define VOP_WIN2_CTRL0_WIN2_CSC_MODE_SHIFT                 (18U)
#define VOP_WIN2_CTRL0_WIN2_CSC_MODE_MASK                  (0x3U << VOP_WIN2_CTRL0_WIN2_CSC_MODE_SHIFT)                 /* 0x000C0000 */
/* WIN2_CTRL1 */
#define VOP_WIN2_CTRL1_OFFSET                              (0xC4U)
#define VOP_WIN2_CTRL1_WIN2_YRGB_GATHER_EN_SHIFT           (0U)
#define VOP_WIN2_CTRL1_WIN2_YRGB_GATHER_EN_MASK            (0x1U << VOP_WIN2_CTRL1_WIN2_YRGB_GATHER_EN_SHIFT)           /* 0x00000001 */
#define VOP_WIN2_CTRL1_WIN2_CBCR_GATHER_EN_SHIFT           (1U)
#define VOP_WIN2_CTRL1_WIN2_CBCR_GATHER_EN_MASK            (0x1U << VOP_WIN2_CTRL1_WIN2_CBCR_GATHER_EN_SHIFT)           /* 0x00000002 */
#define VOP_WIN2_CTRL1_WIN2_DMA_BURST_LENGTH_SHIFT         (2U)
#define VOP_WIN2_CTRL1_WIN2_DMA_BURST_LENGTH_MASK          (0x3U << VOP_WIN2_CTRL1_WIN2_DMA_BURST_LENGTH_SHIFT)         /* 0x0000000C */
#define VOP_WIN2_CTRL1_WIN2_YRGB_GATHER_NUM_SHIFT          (4U)
#define VOP_WIN2_CTRL1_WIN2_YRGB_GATHER_NUM_MASK           (0x3U << VOP_WIN2_CTRL1_WIN2_YRGB_GATHER_NUM_SHIFT)          /* 0x00000030 */
#define VOP_WIN2_CTRL1_WIN2_CBCR_GATHER_NUM_SHIFT          (6U)
#define VOP_WIN2_CTRL1_WIN2_CBCR_GATHER_NUM_MASK           (0x3U << VOP_WIN2_CTRL1_WIN2_CBCR_GATHER_NUM_SHIFT)          /* 0x000000C0 */
#define VOP_WIN2_CTRL1_SW_WIN2_YRGB_RID_SHIFT              (8U)
#define VOP_WIN2_CTRL1_SW_WIN2_YRGB_RID_MASK               (0xFU << VOP_WIN2_CTRL1_SW_WIN2_YRGB_RID_SHIFT)              /* 0x00000F00 */
#define VOP_WIN2_CTRL1_SW_WIN2_CBCR_RID_SHIFT              (12U)
#define VOP_WIN2_CTRL1_SW_WIN2_CBCR_RID_MASK               (0xFU << VOP_WIN2_CTRL1_SW_WIN2_CBCR_RID_SHIFT)              /* 0x0000F000 */
/* WIN2_VIR */
#define VOP_WIN2_VIR_OFFSET                                (0xC8U)
#define VOP_WIN2_VIR_WIN2_YRGB_VIR_STRIDE_SHIFT            (0U)
#define VOP_WIN2_VIR_WIN2_YRGB_VIR_STRIDE_MASK             (0xFFFFU << VOP_WIN2_VIR_WIN2_YRGB_VIR_STRIDE_SHIFT)         /* 0x0000FFFF */
#define VOP_WIN2_VIR_WIN2_CBCR_VIR_STRIDE_SHIFT            (16U)
#define VOP_WIN2_VIR_WIN2_CBCR_VIR_STRIDE_MASK             (0xFFFFU << VOP_WIN2_VIR_WIN2_CBCR_VIR_STRIDE_SHIFT)         /* 0xFFFF0000 */
/* WIN2_YRGB_MST */
#define VOP_WIN2_YRGB_MST_OFFSET                           (0xD0U)
#define VOP_WIN2_YRGB_MST_WIN2_YRGB_MST_SHIFT              (0U)
#define VOP_WIN2_YRGB_MST_WIN2_YRGB_MST_MASK               (0xFFFFFFFFU << VOP_WIN2_YRGB_MST_WIN2_YRGB_MST_SHIFT)       /* 0xFFFFFFFF */
/* WIN2_DSP_INFO */
#define VOP_WIN2_DSP_INFO_OFFSET                           (0xD4U)
#define VOP_WIN2_DSP_INFO_DSP_WIN2_WIDTH_SHIFT             (0U)
#define VOP_WIN2_DSP_INFO_DSP_WIN2_WIDTH_MASK              (0x1FFFU << VOP_WIN2_DSP_INFO_DSP_WIN2_WIDTH_SHIFT)          /* 0x00001FFF */
#define VOP_WIN2_DSP_INFO_DSP_WIN2_HEIGHT_SHIFT            (16U)
#define VOP_WIN2_DSP_INFO_DSP_WIN2_HEIGHT_MASK             (0x1FFFU << VOP_WIN2_DSP_INFO_DSP_WIN2_HEIGHT_SHIFT)         /* 0x1FFF0000 */
/* WIN2_DSP_ST */
#define VOP_WIN2_DSP_ST_OFFSET                             (0xD8U)
#define VOP_WIN2_DSP_ST_DSP_WIN2_XST_SHIFT                 (0U)
#define VOP_WIN2_DSP_ST_DSP_WIN2_XST_MASK                  (0x1FFFU << VOP_WIN2_DSP_ST_DSP_WIN2_XST_SHIFT)              /* 0x00001FFF */
#define VOP_WIN2_DSP_ST_DSP_WIN2_YST_SHIFT                 (16U)
#define VOP_WIN2_DSP_ST_DSP_WIN2_YST_MASK                  (0x1FFFU << VOP_WIN2_DSP_ST_DSP_WIN2_YST_SHIFT)              /* 0x1FFF0000 */
/* WIN2_COLOR_KEY */
#define VOP_WIN2_COLOR_KEY_OFFSET                          (0xDCU)
#define VOP_WIN2_COLOR_KEY_WIN2_KEY_COLOR_SHIFT            (0U)
#define VOP_WIN2_COLOR_KEY_WIN2_KEY_COLOR_MASK             (0xFFFFFFU << VOP_WIN2_COLOR_KEY_WIN2_KEY_COLOR_SHIFT)       /* 0x00FFFFFF */
#define VOP_WIN2_COLOR_KEY_WIN2_KEY_EN_SHIFT               (24U)
#define VOP_WIN2_COLOR_KEY_WIN2_KEY_EN_MASK                (0x1U << VOP_WIN2_COLOR_KEY_WIN2_KEY_EN_SHIFT)               /* 0x01000000 */
/* WIN2_ALPHA_CTRL */
#define VOP_WIN2_ALPHA_CTRL_OFFSET                         (0xECU)
#define VOP_WIN2_ALPHA_CTRL_WIN2_ALPHA_EN_SHIFT            (0U)
#define VOP_WIN2_ALPHA_CTRL_WIN2_ALPHA_EN_MASK             (0x1U << VOP_WIN2_ALPHA_CTRL_WIN2_ALPHA_EN_SHIFT)            /* 0x00000001 */
#define VOP_WIN2_ALPHA_CTRL_WIN2_ALPHA_MODE_SHIFT          (1U)
#define VOP_WIN2_ALPHA_CTRL_WIN2_ALPHA_MODE_MASK           (0x1U << VOP_WIN2_ALPHA_CTRL_WIN2_ALPHA_MODE_SHIFT)          /* 0x00000002 */
#define VOP_WIN2_ALPHA_CTRL_WIN2_ALPHA_PRE_MUL_SHIFT       (2U)
#define VOP_WIN2_ALPHA_CTRL_WIN2_ALPHA_PRE_MUL_MASK        (0x1U << VOP_WIN2_ALPHA_CTRL_WIN2_ALPHA_PRE_MUL_SHIFT)       /* 0x00000004 */
#define VOP_WIN2_ALPHA_CTRL_WIN2_ALPHA_SAT_MODE_SHIFT      (3U)
#define VOP_WIN2_ALPHA_CTRL_WIN2_ALPHA_SAT_MODE_MASK       (0x1U << VOP_WIN2_ALPHA_CTRL_WIN2_ALPHA_SAT_MODE_SHIFT)      /* 0x00000008 */
#define VOP_WIN2_ALPHA_CTRL_WIN2_ALPHA_VALUE_SHIFT         (4U)
#define VOP_WIN2_ALPHA_CTRL_WIN2_ALPHA_VALUE_MASK          (0xFFU << VOP_WIN2_ALPHA_CTRL_WIN2_ALPHA_VALUE_SHIFT)        /* 0x00000FF0 */
/* WIN2_CBCR_MST */
#define VOP_WIN2_CBCR_MST_OFFSET                           (0xF0U)
#define VOP_WIN2_CBCR_MST_WIN2_CBCR_MST_SHIFT              (0U)
#define VOP_WIN2_CBCR_MST_WIN2_CBCR_MST_MASK               (0xFFFFFFFFU << VOP_WIN2_CBCR_MST_WIN2_CBCR_MST_SHIFT)       /* 0xFFFFFFFF */
/* WIN2_YRGB_MST_RAW */
#define VOP_WIN2_YRGB_MST_RAW_OFFSET                       (0xF4U)
#define VOP_WIN2_YRGB_MST_RAW_WIN2_YRGB_MST_RAW_SHIFT      (0U)
#define VOP_WIN2_YRGB_MST_RAW_WIN2_YRGB_MST_RAW_MASK       (0xFFFFFFFFU << VOP_WIN2_YRGB_MST_RAW_WIN2_YRGB_MST_RAW_SHIFT) /* 0xFFFFFFFF */
/* WIN2_CBCR_MST_RAW */
#define VOP_WIN2_CBCR_MST_RAW_OFFSET                       (0xF8U)
#define VOP_WIN2_CBCR_MST_RAW_WIN2_CBCR_MST_RAW_SHIFT      (0U)
#define VOP_WIN2_CBCR_MST_RAW_WIN2_CBCR_MST_RAW_MASK       (0xFFFFFFFFU << VOP_WIN2_CBCR_MST_RAW_WIN2_CBCR_MST_RAW_SHIFT) /* 0xFFFFFFFF */
/* WIN2_LOOP_OFFSET */
#define VOP_WIN2_LOOP_OFFSET_OFFSET                        (0xFCU)
#define VOP_WIN2_LOOP_OFFSET_WIN2_XLOOP_OFFSET_SHIFT       (0U)
#define VOP_WIN2_LOOP_OFFSET_WIN2_XLOOP_OFFSET_MASK        (0x1FFFU << VOP_WIN2_LOOP_OFFSET_WIN2_XLOOP_OFFSET_SHIFT)    /* 0x00001FFF */
#define VOP_WIN2_LOOP_OFFSET_WIN2_XLOOP_EN_SHIFT           (15U)
#define VOP_WIN2_LOOP_OFFSET_WIN2_XLOOP_EN_MASK            (0x1U << VOP_WIN2_LOOP_OFFSET_WIN2_XLOOP_EN_SHIFT)           /* 0x00008000 */
#define VOP_WIN2_LOOP_OFFSET_WIN2_YLOOP_OFFSET_SHIFT       (16U)
#define VOP_WIN2_LOOP_OFFSET_WIN2_YLOOP_OFFSET_MASK        (0x1FFFU << VOP_WIN2_LOOP_OFFSET_WIN2_YLOOP_OFFSET_SHIFT)    /* 0x1FFF0000 */
#define VOP_WIN2_LOOP_OFFSET_WIN2_YLOOP_EN_SHIFT           (31U)
#define VOP_WIN2_LOOP_OFFSET_WIN2_YLOOP_EN_MASK            (0x1U << VOP_WIN2_LOOP_OFFSET_WIN2_YLOOP_EN_SHIFT)           /* 0x80000000 */
/* DSP_HTOTAL_HS_END */
#define VOP_DSP_HTOTAL_HS_END_OFFSET                       (0x100U)
#define VOP_DSP_HTOTAL_HS_END_DSP_HS_END_SHIFT             (0U)
#define VOP_DSP_HTOTAL_HS_END_DSP_HS_END_MASK              (0xFFFU << VOP_DSP_HTOTAL_HS_END_DSP_HS_END_SHIFT)           /* 0x00000FFF */
#define VOP_DSP_HTOTAL_HS_END_DSP_HTOTAL_SHIFT             (16U)
#define VOP_DSP_HTOTAL_HS_END_DSP_HTOTAL_MASK              (0xFFFU << VOP_DSP_HTOTAL_HS_END_DSP_HTOTAL_SHIFT)           /* 0x0FFF0000 */
/* DSP_HACT_ST_END */
#define VOP_DSP_HACT_ST_END_OFFSET                         (0x104U)
#define VOP_DSP_HACT_ST_END_DSP_HACT_END_SHIFT             (0U)
#define VOP_DSP_HACT_ST_END_DSP_HACT_END_MASK              (0xFFFU << VOP_DSP_HACT_ST_END_DSP_HACT_END_SHIFT)           /* 0x00000FFF */
#define VOP_DSP_HACT_ST_END_DSP_HACT_ST_SHIFT              (16U)
#define VOP_DSP_HACT_ST_END_DSP_HACT_ST_MASK               (0xFFFU << VOP_DSP_HACT_ST_END_DSP_HACT_ST_SHIFT)            /* 0x0FFF0000 */
/* DSP_VTOTAL_VS_END */
#define VOP_DSP_VTOTAL_VS_END_OFFSET                       (0x108U)
#define VOP_DSP_VTOTAL_VS_END_DSP_VS_END_SHIFT             (0U)
#define VOP_DSP_VTOTAL_VS_END_DSP_VS_END_MASK              (0xFFFU << VOP_DSP_VTOTAL_VS_END_DSP_VS_END_SHIFT)           /* 0x00000FFF */
#define VOP_DSP_VTOTAL_VS_END_DSP_VTOTAL_SHIFT             (16U)
#define VOP_DSP_VTOTAL_VS_END_DSP_VTOTAL_MASK              (0xFFFU << VOP_DSP_VTOTAL_VS_END_DSP_VTOTAL_SHIFT)           /* 0x0FFF0000 */
/* DSP_VACT_ST_END */
#define VOP_DSP_VACT_ST_END_OFFSET                         (0x10CU)
#define VOP_DSP_VACT_ST_END_DSP_VACT_END_SHIFT             (0U)
#define VOP_DSP_VACT_ST_END_DSP_VACT_END_MASK              (0xFFFU << VOP_DSP_VACT_ST_END_DSP_VACT_END_SHIFT)           /* 0x00000FFF */
#define VOP_DSP_VACT_ST_END_DSP_VACT_ST_SHIFT              (16U)
#define VOP_DSP_VACT_ST_END_DSP_VACT_ST_MASK               (0xFFFU << VOP_DSP_VACT_ST_END_DSP_VACT_ST_SHIFT)            /* 0x0FFF0000 */
/* DSP_VS_ST_END_F1 */
#define VOP_DSP_VS_ST_END_F1_OFFSET                        (0x110U)
#define VOP_DSP_VS_ST_END_F1_DSP_VS_END_F1_SHIFT           (0U)
#define VOP_DSP_VS_ST_END_F1_DSP_VS_END_F1_MASK            (0xFFFU << VOP_DSP_VS_ST_END_F1_DSP_VS_END_F1_SHIFT)         /* 0x00000FFF */
#define VOP_DSP_VS_ST_END_F1_DSP_VS_ST_F1_SHIFT            (16U)
#define VOP_DSP_VS_ST_END_F1_DSP_VS_ST_F1_MASK             (0xFFFU << VOP_DSP_VS_ST_END_F1_DSP_VS_ST_F1_SHIFT)          /* 0x0FFF0000 */
/* DSP_VACT_ST_END_F1 */
#define VOP_DSP_VACT_ST_END_F1_OFFSET                      (0x114U)
#define VOP_DSP_VACT_ST_END_F1_DSP_VACT_END_F1_SHIFT       (0U)
#define VOP_DSP_VACT_ST_END_F1_DSP_VACT_END_F1_MASK        (0xFFFU << VOP_DSP_VACT_ST_END_F1_DSP_VACT_END_F1_SHIFT)     /* 0x00000FFF */
#define VOP_DSP_VACT_ST_END_F1_DSP_VACT_ST_F1_SHIFT        (16U)
#define VOP_DSP_VACT_ST_END_F1_DSP_VACT_ST_F1_MASK         (0xFFFU << VOP_DSP_VACT_ST_END_F1_DSP_VACT_ST_F1_SHIFT)      /* 0x0FFF0000 */
/* PRE_HTOTAL_HS_END */
#define VOP_PRE_HTOTAL_HS_END_OFFSET                       (0x118U)
#define VOP_PRE_HTOTAL_HS_END_DSP_HS_END_SHIFT             (0U)
#define VOP_PRE_HTOTAL_HS_END_DSP_HS_END_MASK              (0xFFFU << VOP_PRE_HTOTAL_HS_END_DSP_HS_END_SHIFT)           /* 0x00000FFF */
#define VOP_PRE_HTOTAL_HS_END_DSP_HTOTAL_SHIFT             (16U)
#define VOP_PRE_HTOTAL_HS_END_DSP_HTOTAL_MASK              (0xFFFU << VOP_PRE_HTOTAL_HS_END_DSP_HTOTAL_SHIFT)           /* 0x0FFF0000 */
/* PRE_HACT_ST_END */
#define VOP_PRE_HACT_ST_END_OFFSET                         (0x11CU)
#define VOP_PRE_HACT_ST_END_DSP_HACT_END_SHIFT             (0U)
#define VOP_PRE_HACT_ST_END_DSP_HACT_END_MASK              (0xFFFU << VOP_PRE_HACT_ST_END_DSP_HACT_END_SHIFT)           /* 0x00000FFF */
#define VOP_PRE_HACT_ST_END_DSP_HACT_ST_SHIFT              (16U)
#define VOP_PRE_HACT_ST_END_DSP_HACT_ST_MASK               (0xFFFU << VOP_PRE_HACT_ST_END_DSP_HACT_ST_SHIFT)            /* 0x0FFF0000 */
/* PRE_VTOTAL_VS_END */
#define VOP_PRE_VTOTAL_VS_END_OFFSET                       (0x120U)
#define VOP_PRE_VTOTAL_VS_END_DSP_VS_END_SHIFT             (0U)
#define VOP_PRE_VTOTAL_VS_END_DSP_VS_END_MASK              (0xFFFU << VOP_PRE_VTOTAL_VS_END_DSP_VS_END_SHIFT)           /* 0x00000FFF */
#define VOP_PRE_VTOTAL_VS_END_DSP_VTOTAL_SHIFT             (16U)
#define VOP_PRE_VTOTAL_VS_END_DSP_VTOTAL_MASK              (0xFFFU << VOP_PRE_VTOTAL_VS_END_DSP_VTOTAL_SHIFT)           /* 0x0FFF0000 */
/* PRE_VACT_ST_END */
#define VOP_PRE_VACT_ST_END_OFFSET                         (0x124U)
#define VOP_PRE_VACT_ST_END_DSP_VACT_END_SHIFT             (0U)
#define VOP_PRE_VACT_ST_END_DSP_VACT_END_MASK              (0xFFFU << VOP_PRE_VACT_ST_END_DSP_VACT_END_SHIFT)           /* 0x00000FFF */
#define VOP_PRE_VACT_ST_END_DSP_VACT_ST_SHIFT              (16U)
#define VOP_PRE_VACT_ST_END_DSP_VACT_ST_MASK               (0xFFFU << VOP_PRE_VACT_ST_END_DSP_VACT_ST_SHIFT)            /* 0x0FFF0000 */
/* BCSH_CTRL */
#define VOP_BCSH_CTRL_OFFSET                               (0x160U)
#define VOP_BCSH_CTRL_BCSH_EN_SHIFT                        (0U)
#define VOP_BCSH_CTRL_BCSH_EN_MASK                         (0x1U << VOP_BCSH_CTRL_BCSH_EN_SHIFT)                        /* 0x00000001 */
#define VOP_BCSH_CTRL_SW_BCSH_R2Y_CSC_MODE_SHIFT           (1U)
#define VOP_BCSH_CTRL_SW_BCSH_R2Y_CSC_MODE_MASK            (0x1U << VOP_BCSH_CTRL_SW_BCSH_R2Y_CSC_MODE_SHIFT)           /* 0x00000002 */
#define VOP_BCSH_CTRL_VIDEO_MODE_SHIFT                     (2U)
#define VOP_BCSH_CTRL_VIDEO_MODE_MASK                      (0x3U << VOP_BCSH_CTRL_VIDEO_MODE_SHIFT)                     /* 0x0000000C */
#define VOP_BCSH_CTRL_SW_BCSH_Y2R_CSC_MODE_SHIFT           (4U)
#define VOP_BCSH_CTRL_SW_BCSH_Y2R_CSC_MODE_MASK            (0x3U << VOP_BCSH_CTRL_SW_BCSH_Y2R_CSC_MODE_SHIFT)           /* 0x00000030 */
#define VOP_BCSH_CTRL_SW_BCSH_Y2R_EN_SHIFT                 (6U)
#define VOP_BCSH_CTRL_SW_BCSH_Y2R_EN_MASK                  (0x1U << VOP_BCSH_CTRL_SW_BCSH_Y2R_EN_SHIFT)                 /* 0x00000040 */
#define VOP_BCSH_CTRL_SW_BCSH_R2Y_EN_SHIFT                 (7U)
#define VOP_BCSH_CTRL_SW_BCSH_R2Y_EN_MASK                  (0x1U << VOP_BCSH_CTRL_SW_BCSH_R2Y_EN_SHIFT)                 /* 0x00000080 */
/* BCSH_COL_BAR */
#define VOP_BCSH_COL_BAR_OFFSET                            (0x164U)
#define VOP_BCSH_COL_BAR_COLOR_BAR_Y_SHIFT                 (0U)
#define VOP_BCSH_COL_BAR_COLOR_BAR_Y_MASK                  (0xFFU << VOP_BCSH_COL_BAR_COLOR_BAR_Y_SHIFT)                /* 0x000000FF */
#define VOP_BCSH_COL_BAR_COLOR_BAR_U_SHIFT                 (8U)
#define VOP_BCSH_COL_BAR_COLOR_BAR_U_MASK                  (0xFFU << VOP_BCSH_COL_BAR_COLOR_BAR_U_SHIFT)                /* 0x0000FF00 */
#define VOP_BCSH_COL_BAR_COLOR_BAR_V_SHIFT                 (16U)
#define VOP_BCSH_COL_BAR_COLOR_BAR_V_MASK                  (0xFFU << VOP_BCSH_COL_BAR_COLOR_BAR_V_SHIFT)                /* 0x00FF0000 */
/* BCSH_BCS */
#define VOP_BCSH_BCS_OFFSET                                (0x168U)
#define VOP_BCSH_BCS_BRIGHTNESS_SHIFT                      (0U)
#define VOP_BCSH_BCS_BRIGHTNESS_MASK                       (0x7FU << VOP_BCSH_BCS_BRIGHTNESS_SHIFT)                     /* 0x0000007F */
#define VOP_BCSH_BCS_CONTRAST_SHIFT                        (8U)
#define VOP_BCSH_BCS_CONTRAST_MASK                         (0x1FFU << VOP_BCSH_BCS_CONTRAST_SHIFT)                      /* 0x0001FF00 */
#define VOP_BCSH_BCS_SAT_CON_SHIFT                         (20U)
#define VOP_BCSH_BCS_SAT_CON_MASK                          (0x3FFU << VOP_BCSH_BCS_SAT_CON_SHIFT)                       /* 0x3FF00000 */
/* BCSH_H */
#define VOP_BCSH_H_OFFSET                                  (0x16CU)
#define VOP_BCSH_H_SIN_HUE_SHIFT                           (0U)
#define VOP_BCSH_H_SIN_HUE_MASK                            (0x1FFU << VOP_BCSH_H_SIN_HUE_SHIFT)                         /* 0x000001FF */
#define VOP_BCSH_H_COS_HUE_SHIFT                           (16U)
#define VOP_BCSH_H_COS_HUE_MASK                            (0x1FFU << VOP_BCSH_H_COS_HUE_SHIFT)                         /* 0x01FF0000 */
/* GAMMA_COE_WORD0 */
#define VOP_GAMMA_COE_WORD0_OFFSET                         (0x170U)
#define VOP_GAMMA_COE_WORD0_GAMMA_COE_WORD0_SHIFT          (0U)
#define VOP_GAMMA_COE_WORD0_GAMMA_COE_WORD0_MASK           (0xFFFFFFFFU << VOP_GAMMA_COE_WORD0_GAMMA_COE_WORD0_SHIFT)   /* 0xFFFFFFFF */
/* GAMMA_COE_WORD1 */
#define VOP_GAMMA_COE_WORD1_OFFSET                         (0x174U)
#define VOP_GAMMA_COE_WORD1_GAMMA_COE_WORD1_SHIFT          (0U)
#define VOP_GAMMA_COE_WORD1_GAMMA_COE_WORD1_MASK           (0xFFFFFFFFU << VOP_GAMMA_COE_WORD1_GAMMA_COE_WORD1_SHIFT)   /* 0xFFFFFFFF */
/* GAMMA_COE_WORD2 */
#define VOP_GAMMA_COE_WORD2_OFFSET                         (0x178U)
#define VOP_GAMMA_COE_WORD2_GAMMA_COE_WORD2_SHIFT          (0U)
#define VOP_GAMMA_COE_WORD2_GAMMA_COE_WORD2_MASK           (0xFFFFFFFFU << VOP_GAMMA_COE_WORD2_GAMMA_COE_WORD2_SHIFT)   /* 0xFFFFFFFF */
/* GAMMA_COE_WORD3 */
#define VOP_GAMMA_COE_WORD3_OFFSET                         (0x17CU)
#define VOP_GAMMA_COE_WORD3_GAMMA_COE_WORD3_SHIFT          (0U)
#define VOP_GAMMA_COE_WORD3_GAMMA_COE_WORD3_MASK           (0xFFFFFFFFU << VOP_GAMMA_COE_WORD3_GAMMA_COE_WORD3_SHIFT)   /* 0xFFFFFFFF */
/* POST_CTRL */
#define VOP_POST_CTRL_OFFSET                               (0x180U)
#define VOP_POST_CTRL_Y_GAMMA_EN_SHIFT                     (0U)
#define VOP_POST_CTRL_Y_GAMMA_EN_MASK                      (0x1U << VOP_POST_CTRL_Y_GAMMA_EN_SHIFT)                     /* 0x00000001 */
#define VOP_POST_CTRL_POST_SCL_EN_SHIFT                    (4U)
#define VOP_POST_CTRL_POST_SCL_EN_MASK                     (0x1U << VOP_POST_CTRL_POST_SCL_EN_SHIFT)                    /* 0x00000010 */
#define VOP_POST_CTRL_POST_SCL_HMODE_SHIFT                 (8U)
#define VOP_POST_CTRL_POST_SCL_HMODE_MASK                  (0x3U << VOP_POST_CTRL_POST_SCL_HMODE_SHIFT)                 /* 0x00000300 */
#define VOP_POST_CTRL_POST_SCL_VMODE_SHIFT                 (10U)
#define VOP_POST_CTRL_POST_SCL_VMODE_MASK                  (0x3U << VOP_POST_CTRL_POST_SCL_VMODE_SHIFT)                 /* 0x00000C00 */
#define VOP_POST_CTRL_POST_CSC_EN_SHIFT                    (12U)
#define VOP_POST_CTRL_POST_CSC_EN_MASK                     (0x1U << VOP_POST_CTRL_POST_CSC_EN_SHIFT)                    /* 0x00001000 */
#define VOP_POST_CTRL_POST_CSC_MODE_SHIFT                  (14U)
#define VOP_POST_CTRL_POST_CSC_MODE_MASK                   (0x3U << VOP_POST_CTRL_POST_CSC_MODE_SHIFT)                  /* 0x0000C000 */
#define VOP_POST_CTRL_COLOR_MATRIX_EN_SHIFT                (16U)
#define VOP_POST_CTRL_COLOR_MATRIX_EN_MASK                 (0x1U << VOP_POST_CTRL_COLOR_MATRIX_EN_SHIFT)                /* 0x00010000 */
#define VOP_POST_CTRL_COLOR_MATRIX_COE_MODE_SHIFT          (17U)
#define VOP_POST_CTRL_COLOR_MATRIX_COE_MODE_MASK           (0x1U << VOP_POST_CTRL_COLOR_MATRIX_COE_MODE_SHIFT)          /* 0x00020000 */
#define VOP_POST_CTRL_CLIP_EN_SHIFT                        (20U)
#define VOP_POST_CTRL_CLIP_EN_MASK                         (0x1U << VOP_POST_CTRL_CLIP_EN_SHIFT)                        /* 0x00100000 */
#define VOP_POST_CTRL_Y_THRES_SHIFT                        (24U)
#define VOP_POST_CTRL_Y_THRES_MASK                         (0xFFU << VOP_POST_CTRL_Y_THRES_SHIFT)                       /* 0xFF000000 */
/* COLOR_MATRIX_COE0 */
#define VOP_COLOR_MATRIX_COE0_OFFSET                       (0x184U)
#define VOP_COLOR_MATRIX_COE0_COLOR_MATRIX_COE00_SHIFT     (0U)
#define VOP_COLOR_MATRIX_COE0_COLOR_MATRIX_COE00_MASK      (0xFFU << VOP_COLOR_MATRIX_COE0_COLOR_MATRIX_COE00_SHIFT)    /* 0x000000FF */
#define VOP_COLOR_MATRIX_COE0_COLOR_MATRIX_COE01_SHIFT     (8U)
#define VOP_COLOR_MATRIX_COE0_COLOR_MATRIX_COE01_MASK      (0xFFU << VOP_COLOR_MATRIX_COE0_COLOR_MATRIX_COE01_SHIFT)    /* 0x0000FF00 */
#define VOP_COLOR_MATRIX_COE0_COLOR_MATRIX_COE02_SHIFT     (16U)
#define VOP_COLOR_MATRIX_COE0_COLOR_MATRIX_COE02_MASK      (0xFFU << VOP_COLOR_MATRIX_COE0_COLOR_MATRIX_COE02_SHIFT)    /* 0x00FF0000 */
#define VOP_COLOR_MATRIX_COE0_COLOR_MATRIX_OFFSET0_SHIFT   (24U)
#define VOP_COLOR_MATRIX_COE0_COLOR_MATRIX_OFFSET0_MASK    (0xFFU << VOP_COLOR_MATRIX_COE0_COLOR_MATRIX_OFFSET0_SHIFT)  /* 0xFF000000 */
/* COLOR_MATRIX_COE1 */
#define VOP_COLOR_MATRIX_COE1_OFFSET                       (0x188U)
#define VOP_COLOR_MATRIX_COE1_COLOR_MATRIX_COE10_SHIFT     (0U)
#define VOP_COLOR_MATRIX_COE1_COLOR_MATRIX_COE10_MASK      (0xFFU << VOP_COLOR_MATRIX_COE1_COLOR_MATRIX_COE10_SHIFT)    /* 0x000000FF */
#define VOP_COLOR_MATRIX_COE1_COLOR_MATRIX_COE11_SHIFT     (8U)
#define VOP_COLOR_MATRIX_COE1_COLOR_MATRIX_COE11_MASK      (0xFFU << VOP_COLOR_MATRIX_COE1_COLOR_MATRIX_COE11_SHIFT)    /* 0x0000FF00 */
#define VOP_COLOR_MATRIX_COE1_COLOR_MATRIX_COE12_SHIFT     (16U)
#define VOP_COLOR_MATRIX_COE1_COLOR_MATRIX_COE12_MASK      (0xFFU << VOP_COLOR_MATRIX_COE1_COLOR_MATRIX_COE12_SHIFT)    /* 0x00FF0000 */
#define VOP_COLOR_MATRIX_COE1_COLOR_MATRIX_OFFSET1_SHIFT   (24U)
#define VOP_COLOR_MATRIX_COE1_COLOR_MATRIX_OFFSET1_MASK    (0xFFU << VOP_COLOR_MATRIX_COE1_COLOR_MATRIX_OFFSET1_SHIFT)  /* 0xFF000000 */
/* COLOR_MATRIX_COE2 */
#define VOP_COLOR_MATRIX_COE2_OFFSET                       (0x18CU)
#define VOP_COLOR_MATRIX_COE2_COLOR_MATRIX_COE20_SHIFT     (0U)
#define VOP_COLOR_MATRIX_COE2_COLOR_MATRIX_COE20_MASK      (0xFFU << VOP_COLOR_MATRIX_COE2_COLOR_MATRIX_COE20_SHIFT)    /* 0x000000FF */
#define VOP_COLOR_MATRIX_COE2_COLOR_MATRIX_COE21_SHIFT     (8U)
#define VOP_COLOR_MATRIX_COE2_COLOR_MATRIX_COE21_MASK      (0xFFU << VOP_COLOR_MATRIX_COE2_COLOR_MATRIX_COE21_SHIFT)    /* 0x0000FF00 */
#define VOP_COLOR_MATRIX_COE2_COLOR_MATRIX_COE22_SHIFT     (16U)
#define VOP_COLOR_MATRIX_COE2_COLOR_MATRIX_COE22_MASK      (0xFFU << VOP_COLOR_MATRIX_COE2_COLOR_MATRIX_COE22_SHIFT)    /* 0x00FF0000 */
#define VOP_COLOR_MATRIX_COE2_COLOR_MATRIX_OFFSET2_SHIFT   (24U)
#define VOP_COLOR_MATRIX_COE2_COLOR_MATRIX_OFFSET2_MASK    (0xFFU << VOP_COLOR_MATRIX_COE2_COLOR_MATRIX_OFFSET2_SHIFT)  /* 0xFF000000 */
/* MCU_WRITE_DATA */
#define VOP_MCU_WRITE_DATA_OFFSET                          (0x190U)
#define VOP_MCU_WRITE_DATA_FIELD0000_SHIFT                 (0U)
#define VOP_MCU_WRITE_DATA_FIELD0000_MASK                  (0x1U << VOP_MCU_WRITE_DATA_FIELD0000_SHIFT)                 /* 0x00000001 */
/* DBG_REG_SCAN_LINE */
#define VOP_DBG_REG_SCAN_LINE_OFFSET                       (0x1F0U)
#define VOP_DBG_REG_SCAN_LINE                              (0x0U)
#define VOP_DBG_REG_SCAN_LINE_SCAN_LINE_NUM_SHIFT          (0U)
#define VOP_DBG_REG_SCAN_LINE_SCAN_LINE_NUM_MASK           (0xFFFU << VOP_DBG_REG_SCAN_LINE_SCAN_LINE_NUM_SHIFT)        /* 0x00000FFF */
/* BLANKING_VALUE */
#define VOP_BLANKING_VALUE_OFFSET                          (0x1F4U)
#define VOP_BLANKING_VALUE_SW_BLANKING_VALUE_SHIFT         (0U)
#define VOP_BLANKING_VALUE_SW_BLANKING_VALUE_MASK          (0xFFFFFFU << VOP_BLANKING_VALUE_SW_BLANKING_VALUE_SHIFT)    /* 0x00FFFFFF */
#define VOP_BLANKING_VALUE_BLANKING_VALUE_CONFIG_EN_SHIFT  (24U)
#define VOP_BLANKING_VALUE_BLANKING_VALUE_CONFIG_EN_MASK   (0x1U << VOP_BLANKING_VALUE_BLANKING_VALUE_CONFIG_EN_SHIFT)  /* 0x01000000 */
/* FLAG_REG_FRM_VALID */
#define VOP_FLAG_REG_FRM_VALID_OFFSET                      (0x1F8U)
#define VOP_FLAG_REG_FRM_VALID                             (0x0U)
#define VOP_FLAG_REG_FRM_VALID_FLAG_REG_FRM_VALID_SHIFT    (0U)
#define VOP_FLAG_REG_FRM_VALID_FLAG_REG_FRM_VALID_MASK     (0xFFFFFFFFU << VOP_FLAG_REG_FRM_VALID_FLAG_REG_FRM_VALID_SHIFT) /* 0xFFFFFFFF */
/* FLAG_REG */
#define VOP_FLAG_REG_OFFSET                                (0x1FCU)
#define VOP_FLAG_REG_FLAG_REG_SHIFT                        (0U)
#define VOP_FLAG_REG_FLAG_REG_MASK                         (0xFFFFFFFFU << VOP_FLAG_REG_FLAG_REG_SHIFT)                 /* 0xFFFFFFFF */
/* WIN0_BPP_LUT000 */
#define VOP_WIN0_BPP_LUT000_OFFSET                         (0x200U)
/* WIN0_BPP_LUT001 */
#define VOP_WIN0_BPP_LUT001_OFFSET                         (0x204U)
/* WIN0_BPP_LUT002 */
#define VOP_WIN0_BPP_LUT002_OFFSET                         (0x208U)
/* WIN0_BPP_LUT003 */
#define VOP_WIN0_BPP_LUT003_OFFSET                         (0x20CU)
/* WIN0_BPP_LUT004 */
#define VOP_WIN0_BPP_LUT004_OFFSET                         (0x210U)
/* WIN0_BPP_LUT005 */
#define VOP_WIN0_BPP_LUT005_OFFSET                         (0x214U)
/* WIN0_BPP_LUT006 */
#define VOP_WIN0_BPP_LUT006_OFFSET                         (0x218U)
/* WIN0_BPP_LUT007 */
#define VOP_WIN0_BPP_LUT007_OFFSET                         (0x21CU)
/* WIN0_BPP_LUT008 */
#define VOP_WIN0_BPP_LUT008_OFFSET                         (0x220U)
/* WIN0_BPP_LUT009 */
#define VOP_WIN0_BPP_LUT009_OFFSET                         (0x224U)
/* WIN0_BPP_LUT010 */
#define VOP_WIN0_BPP_LUT010_OFFSET                         (0x228U)
/* WIN0_BPP_LUT011 */
#define VOP_WIN0_BPP_LUT011_OFFSET                         (0x22CU)
/* WIN0_BPP_LUT012 */
#define VOP_WIN0_BPP_LUT012_OFFSET                         (0x230U)
/* WIN0_BPP_LUT013 */
#define VOP_WIN0_BPP_LUT013_OFFSET                         (0x234U)
/* WIN0_BPP_LUT014 */
#define VOP_WIN0_BPP_LUT014_OFFSET                         (0x238U)
/* WIN0_BPP_LUT015 */
#define VOP_WIN0_BPP_LUT015_OFFSET                         (0x23CU)
/* WIN0_BPP_LUT016 */
#define VOP_WIN0_BPP_LUT016_OFFSET                         (0x240U)
/* WIN0_BPP_LUT017 */
#define VOP_WIN0_BPP_LUT017_OFFSET                         (0x244U)
/* WIN0_BPP_LUT018 */
#define VOP_WIN0_BPP_LUT018_OFFSET                         (0x248U)
/* WIN0_BPP_LUT019 */
#define VOP_WIN0_BPP_LUT019_OFFSET                         (0x24CU)
/* WIN0_BPP_LUT020 */
#define VOP_WIN0_BPP_LUT020_OFFSET                         (0x250U)
/* WIN0_BPP_LUT021 */
#define VOP_WIN0_BPP_LUT021_OFFSET                         (0x254U)
/* WIN0_BPP_LUT022 */
#define VOP_WIN0_BPP_LUT022_OFFSET                         (0x258U)
/* WIN0_BPP_LUT023 */
#define VOP_WIN0_BPP_LUT023_OFFSET                         (0x25CU)
/* WIN0_BPP_LUT024 */
#define VOP_WIN0_BPP_LUT024_OFFSET                         (0x260U)
/* WIN0_BPP_LUT025 */
#define VOP_WIN0_BPP_LUT025_OFFSET                         (0x264U)
/* WIN0_BPP_LUT026 */
#define VOP_WIN0_BPP_LUT026_OFFSET                         (0x268U)
/* WIN0_BPP_LUT027 */
#define VOP_WIN0_BPP_LUT027_OFFSET                         (0x26CU)
/* WIN0_BPP_LUT028 */
#define VOP_WIN0_BPP_LUT028_OFFSET                         (0x270U)
/* WIN0_BPP_LUT029 */
#define VOP_WIN0_BPP_LUT029_OFFSET                         (0x274U)
/* WIN0_BPP_LUT030 */
#define VOP_WIN0_BPP_LUT030_OFFSET                         (0x278U)
/* WIN0_BPP_LUT031 */
#define VOP_WIN0_BPP_LUT031_OFFSET                         (0x27CU)
/* WIN0_BPP_LUT032 */
#define VOP_WIN0_BPP_LUT032_OFFSET                         (0x280U)
/* WIN0_BPP_LUT033 */
#define VOP_WIN0_BPP_LUT033_OFFSET                         (0x284U)
/* WIN0_BPP_LUT034 */
#define VOP_WIN0_BPP_LUT034_OFFSET                         (0x288U)
/* WIN0_BPP_LUT035 */
#define VOP_WIN0_BPP_LUT035_OFFSET                         (0x28CU)
/* WIN0_BPP_LUT036 */
#define VOP_WIN0_BPP_LUT036_OFFSET                         (0x290U)
/* WIN0_BPP_LUT037 */
#define VOP_WIN0_BPP_LUT037_OFFSET                         (0x294U)
/* WIN0_BPP_LUT038 */
#define VOP_WIN0_BPP_LUT038_OFFSET                         (0x298U)
/* WIN0_BPP_LUT039 */
#define VOP_WIN0_BPP_LUT039_OFFSET                         (0x29CU)
/* WIN0_BPP_LUT040 */
#define VOP_WIN0_BPP_LUT040_OFFSET                         (0x2A0U)
/* WIN0_BPP_LUT041 */
#define VOP_WIN0_BPP_LUT041_OFFSET                         (0x2A4U)
/* WIN0_BPP_LUT042 */
#define VOP_WIN0_BPP_LUT042_OFFSET                         (0x2A8U)
/* WIN0_BPP_LUT043 */
#define VOP_WIN0_BPP_LUT043_OFFSET                         (0x2ACU)
/* WIN0_BPP_LUT044 */
#define VOP_WIN0_BPP_LUT044_OFFSET                         (0x2B0U)
/* WIN0_BPP_LUT045 */
#define VOP_WIN0_BPP_LUT045_OFFSET                         (0x2B4U)
/* WIN0_BPP_LUT046 */
#define VOP_WIN0_BPP_LUT046_OFFSET                         (0x2B8U)
/* WIN0_BPP_LUT047 */
#define VOP_WIN0_BPP_LUT047_OFFSET                         (0x2BCU)
/* WIN0_BPP_LUT048 */
#define VOP_WIN0_BPP_LUT048_OFFSET                         (0x2C0U)
/* WIN0_BPP_LUT049 */
#define VOP_WIN0_BPP_LUT049_OFFSET                         (0x2C4U)
/* WIN0_BPP_LUT050 */
#define VOP_WIN0_BPP_LUT050_OFFSET                         (0x2C8U)
/* WIN0_BPP_LUT051 */
#define VOP_WIN0_BPP_LUT051_OFFSET                         (0x2CCU)
/* WIN0_BPP_LUT052 */
#define VOP_WIN0_BPP_LUT052_OFFSET                         (0x2D0U)
/* WIN0_BPP_LUT053 */
#define VOP_WIN0_BPP_LUT053_OFFSET                         (0x2D4U)
/* WIN0_BPP_LUT054 */
#define VOP_WIN0_BPP_LUT054_OFFSET                         (0x2D8U)
/* WIN0_BPP_LUT055 */
#define VOP_WIN0_BPP_LUT055_OFFSET                         (0x2DCU)
/* WIN0_BPP_LUT056 */
#define VOP_WIN0_BPP_LUT056_OFFSET                         (0x2E0U)
/* WIN0_BPP_LUT057 */
#define VOP_WIN0_BPP_LUT057_OFFSET                         (0x2E4U)
/* WIN0_BPP_LUT058 */
#define VOP_WIN0_BPP_LUT058_OFFSET                         (0x2E8U)
/* WIN0_BPP_LUT059 */
#define VOP_WIN0_BPP_LUT059_OFFSET                         (0x2ECU)
/* WIN0_BPP_LUT060 */
#define VOP_WIN0_BPP_LUT060_OFFSET                         (0x2F0U)
/* WIN0_BPP_LUT061 */
#define VOP_WIN0_BPP_LUT061_OFFSET                         (0x2F4U)
/* WIN0_BPP_LUT062 */
#define VOP_WIN0_BPP_LUT062_OFFSET                         (0x2F8U)
/* WIN0_BPP_LUT063 */
#define VOP_WIN0_BPP_LUT063_OFFSET                         (0x2FCU)
/* WIN0_BPP_LUT064 */
#define VOP_WIN0_BPP_LUT064_OFFSET                         (0x300U)
/* WIN0_BPP_LUT065 */
#define VOP_WIN0_BPP_LUT065_OFFSET                         (0x304U)
/* WIN0_BPP_LUT066 */
#define VOP_WIN0_BPP_LUT066_OFFSET                         (0x308U)
/* WIN0_BPP_LUT067 */
#define VOP_WIN0_BPP_LUT067_OFFSET                         (0x30CU)
/* WIN0_BPP_LUT068 */
#define VOP_WIN0_BPP_LUT068_OFFSET                         (0x310U)
/* WIN0_BPP_LUT069 */
#define VOP_WIN0_BPP_LUT069_OFFSET                         (0x314U)
/* WIN0_BPP_LUT070 */
#define VOP_WIN0_BPP_LUT070_OFFSET                         (0x318U)
/* WIN0_BPP_LUT071 */
#define VOP_WIN0_BPP_LUT071_OFFSET                         (0x31CU)
/* WIN0_BPP_LUT072 */
#define VOP_WIN0_BPP_LUT072_OFFSET                         (0x320U)
/* WIN0_BPP_LUT073 */
#define VOP_WIN0_BPP_LUT073_OFFSET                         (0x324U)
/* WIN0_BPP_LUT074 */
#define VOP_WIN0_BPP_LUT074_OFFSET                         (0x328U)
/* WIN0_BPP_LUT075 */
#define VOP_WIN0_BPP_LUT075_OFFSET                         (0x32CU)
/* WIN0_BPP_LUT076 */
#define VOP_WIN0_BPP_LUT076_OFFSET                         (0x330U)
/* WIN0_BPP_LUT077 */
#define VOP_WIN0_BPP_LUT077_OFFSET                         (0x334U)
/* WIN0_BPP_LUT078 */
#define VOP_WIN0_BPP_LUT078_OFFSET                         (0x338U)
/* WIN0_BPP_LUT079 */
#define VOP_WIN0_BPP_LUT079_OFFSET                         (0x33CU)
/* WIN0_BPP_LUT080 */
#define VOP_WIN0_BPP_LUT080_OFFSET                         (0x340U)
/* WIN0_BPP_LUT081 */
#define VOP_WIN0_BPP_LUT081_OFFSET                         (0x344U)
/* WIN0_BPP_LUT082 */
#define VOP_WIN0_BPP_LUT082_OFFSET                         (0x348U)
/* WIN0_BPP_LUT083 */
#define VOP_WIN0_BPP_LUT083_OFFSET                         (0x34CU)
/* WIN0_BPP_LUT084 */
#define VOP_WIN0_BPP_LUT084_OFFSET                         (0x350U)
/* WIN0_BPP_LUT085 */
#define VOP_WIN0_BPP_LUT085_OFFSET                         (0x354U)
/* WIN0_BPP_LUT086 */
#define VOP_WIN0_BPP_LUT086_OFFSET                         (0x358U)
/* WIN0_BPP_LUT087 */
#define VOP_WIN0_BPP_LUT087_OFFSET                         (0x35CU)
/* WIN0_BPP_LUT088 */
#define VOP_WIN0_BPP_LUT088_OFFSET                         (0x360U)
/* WIN0_BPP_LUT089 */
#define VOP_WIN0_BPP_LUT089_OFFSET                         (0x364U)
/* WIN0_BPP_LUT090 */
#define VOP_WIN0_BPP_LUT090_OFFSET                         (0x368U)
/* WIN0_BPP_LUT091 */
#define VOP_WIN0_BPP_LUT091_OFFSET                         (0x36CU)
/* WIN0_BPP_LUT092 */
#define VOP_WIN0_BPP_LUT092_OFFSET                         (0x370U)
/* WIN0_BPP_LUT093 */
#define VOP_WIN0_BPP_LUT093_OFFSET                         (0x374U)
/* WIN0_BPP_LUT094 */
#define VOP_WIN0_BPP_LUT094_OFFSET                         (0x378U)
/* WIN0_BPP_LUT095 */
#define VOP_WIN0_BPP_LUT095_OFFSET                         (0x37CU)
/* WIN0_BPP_LUT096 */
#define VOP_WIN0_BPP_LUT096_OFFSET                         (0x380U)
/* WIN0_BPP_LUT097 */
#define VOP_WIN0_BPP_LUT097_OFFSET                         (0x384U)
/* WIN0_BPP_LUT098 */
#define VOP_WIN0_BPP_LUT098_OFFSET                         (0x388U)
/* WIN0_BPP_LUT099 */
#define VOP_WIN0_BPP_LUT099_OFFSET                         (0x38CU)
/* WIN0_BPP_LUT100 */
#define VOP_WIN0_BPP_LUT100_OFFSET                         (0x390U)
/* WIN0_BPP_LUT101 */
#define VOP_WIN0_BPP_LUT101_OFFSET                         (0x394U)
/* WIN0_BPP_LUT102 */
#define VOP_WIN0_BPP_LUT102_OFFSET                         (0x398U)
/* WIN0_BPP_LUT103 */
#define VOP_WIN0_BPP_LUT103_OFFSET                         (0x39CU)
/* WIN0_BPP_LUT104 */
#define VOP_WIN0_BPP_LUT104_OFFSET                         (0x3A0U)
/* WIN0_BPP_LUT105 */
#define VOP_WIN0_BPP_LUT105_OFFSET                         (0x3A4U)
/* WIN0_BPP_LUT106 */
#define VOP_WIN0_BPP_LUT106_OFFSET                         (0x3A8U)
/* WIN0_BPP_LUT107 */
#define VOP_WIN0_BPP_LUT107_OFFSET                         (0x3ACU)
/* WIN0_BPP_LUT108 */
#define VOP_WIN0_BPP_LUT108_OFFSET                         (0x3B0U)
/* WIN0_BPP_LUT109 */
#define VOP_WIN0_BPP_LUT109_OFFSET                         (0x3B4U)
/* WIN0_BPP_LUT110 */
#define VOP_WIN0_BPP_LUT110_OFFSET                         (0x3B8U)
/* WIN0_BPP_LUT111 */
#define VOP_WIN0_BPP_LUT111_OFFSET                         (0x3BCU)
/* WIN0_BPP_LUT112 */
#define VOP_WIN0_BPP_LUT112_OFFSET                         (0x3C0U)
/* WIN0_BPP_LUT113 */
#define VOP_WIN0_BPP_LUT113_OFFSET                         (0x3C4U)
/* WIN0_BPP_LUT114 */
#define VOP_WIN0_BPP_LUT114_OFFSET                         (0x3C8U)
/* WIN0_BPP_LUT115 */
#define VOP_WIN0_BPP_LUT115_OFFSET                         (0x3CCU)
/* WIN0_BPP_LUT116 */
#define VOP_WIN0_BPP_LUT116_OFFSET                         (0x3D0U)
/* WIN0_BPP_LUT117 */
#define VOP_WIN0_BPP_LUT117_OFFSET                         (0x3D4U)
/* WIN0_BPP_LUT118 */
#define VOP_WIN0_BPP_LUT118_OFFSET                         (0x3D8U)
/* WIN0_BPP_LUT119 */
#define VOP_WIN0_BPP_LUT119_OFFSET                         (0x3DCU)
/* WIN0_BPP_LUT120 */
#define VOP_WIN0_BPP_LUT120_OFFSET                         (0x3E0U)
/* WIN0_BPP_LUT121 */
#define VOP_WIN0_BPP_LUT121_OFFSET                         (0x3E4U)
/* WIN0_BPP_LUT122 */
#define VOP_WIN0_BPP_LUT122_OFFSET                         (0x3E8U)
/* WIN0_BPP_LUT123 */
#define VOP_WIN0_BPP_LUT123_OFFSET                         (0x3ECU)
/* WIN0_BPP_LUT124 */
#define VOP_WIN0_BPP_LUT124_OFFSET                         (0x3F0U)
/* WIN0_BPP_LUT125 */
#define VOP_WIN0_BPP_LUT125_OFFSET                         (0x3F4U)
/* WIN0_BPP_LUT126 */
#define VOP_WIN0_BPP_LUT126_OFFSET                         (0x3F8U)
/* WIN0_BPP_LUT127 */
#define VOP_WIN0_BPP_LUT127_OFFSET                         (0x3FCU)
/* WIN0_BPP_LUT128 */
#define VOP_WIN0_BPP_LUT128_OFFSET                         (0x400U)
/* WIN0_BPP_LUT129 */
#define VOP_WIN0_BPP_LUT129_OFFSET                         (0x404U)
/* WIN0_BPP_LUT130 */
#define VOP_WIN0_BPP_LUT130_OFFSET                         (0x408U)
/* WIN0_BPP_LUT131 */
#define VOP_WIN0_BPP_LUT131_OFFSET                         (0x40CU)
/* WIN0_BPP_LUT132 */
#define VOP_WIN0_BPP_LUT132_OFFSET                         (0x410U)
/* WIN0_BPP_LUT133 */
#define VOP_WIN0_BPP_LUT133_OFFSET                         (0x414U)
/* WIN0_BPP_LUT134 */
#define VOP_WIN0_BPP_LUT134_OFFSET                         (0x418U)
/* WIN0_BPP_LUT135 */
#define VOP_WIN0_BPP_LUT135_OFFSET                         (0x41CU)
/* WIN0_BPP_LUT136 */
#define VOP_WIN0_BPP_LUT136_OFFSET                         (0x420U)
/* WIN0_BPP_LUT137 */
#define VOP_WIN0_BPP_LUT137_OFFSET                         (0x424U)
/* WIN0_BPP_LUT138 */
#define VOP_WIN0_BPP_LUT138_OFFSET                         (0x428U)
/* WIN0_BPP_LUT139 */
#define VOP_WIN0_BPP_LUT139_OFFSET                         (0x42CU)
/* WIN0_BPP_LUT140 */
#define VOP_WIN0_BPP_LUT140_OFFSET                         (0x430U)
/* WIN0_BPP_LUT141 */
#define VOP_WIN0_BPP_LUT141_OFFSET                         (0x434U)
/* WIN0_BPP_LUT142 */
#define VOP_WIN0_BPP_LUT142_OFFSET                         (0x438U)
/* WIN0_BPP_LUT143 */
#define VOP_WIN0_BPP_LUT143_OFFSET                         (0x43CU)
/* WIN0_BPP_LUT144 */
#define VOP_WIN0_BPP_LUT144_OFFSET                         (0x440U)
/* WIN0_BPP_LUT145 */
#define VOP_WIN0_BPP_LUT145_OFFSET                         (0x444U)
/* WIN0_BPP_LUT146 */
#define VOP_WIN0_BPP_LUT146_OFFSET                         (0x448U)
/* WIN0_BPP_LUT147 */
#define VOP_WIN0_BPP_LUT147_OFFSET                         (0x44CU)
/* WIN0_BPP_LUT148 */
#define VOP_WIN0_BPP_LUT148_OFFSET                         (0x450U)
/* WIN0_BPP_LUT149 */
#define VOP_WIN0_BPP_LUT149_OFFSET                         (0x454U)
/* WIN0_BPP_LUT150 */
#define VOP_WIN0_BPP_LUT150_OFFSET                         (0x458U)
/* WIN0_BPP_LUT151 */
#define VOP_WIN0_BPP_LUT151_OFFSET                         (0x45CU)
/* WIN0_BPP_LUT152 */
#define VOP_WIN0_BPP_LUT152_OFFSET                         (0x460U)
/* WIN0_BPP_LUT153 */
#define VOP_WIN0_BPP_LUT153_OFFSET                         (0x464U)
/* WIN0_BPP_LUT154 */
#define VOP_WIN0_BPP_LUT154_OFFSET                         (0x468U)
/* WIN0_BPP_LUT155 */
#define VOP_WIN0_BPP_LUT155_OFFSET                         (0x46CU)
/* WIN0_BPP_LUT156 */
#define VOP_WIN0_BPP_LUT156_OFFSET                         (0x470U)
/* WIN0_BPP_LUT157 */
#define VOP_WIN0_BPP_LUT157_OFFSET                         (0x474U)
/* WIN0_BPP_LUT158 */
#define VOP_WIN0_BPP_LUT158_OFFSET                         (0x478U)
/* WIN0_BPP_LUT159 */
#define VOP_WIN0_BPP_LUT159_OFFSET                         (0x47CU)
/* WIN0_BPP_LUT160 */
#define VOP_WIN0_BPP_LUT160_OFFSET                         (0x480U)
/* WIN0_BPP_LUT161 */
#define VOP_WIN0_BPP_LUT161_OFFSET                         (0x484U)
/* WIN0_BPP_LUT162 */
#define VOP_WIN0_BPP_LUT162_OFFSET                         (0x488U)
/* WIN0_BPP_LUT163 */
#define VOP_WIN0_BPP_LUT163_OFFSET                         (0x48CU)
/* WIN0_BPP_LUT164 */
#define VOP_WIN0_BPP_LUT164_OFFSET                         (0x490U)
/* WIN0_BPP_LUT165 */
#define VOP_WIN0_BPP_LUT165_OFFSET                         (0x494U)
/* WIN0_BPP_LUT166 */
#define VOP_WIN0_BPP_LUT166_OFFSET                         (0x498U)
/* WIN0_BPP_LUT167 */
#define VOP_WIN0_BPP_LUT167_OFFSET                         (0x49CU)
/* WIN0_BPP_LUT168 */
#define VOP_WIN0_BPP_LUT168_OFFSET                         (0x4A0U)
/* WIN0_BPP_LUT169 */
#define VOP_WIN0_BPP_LUT169_OFFSET                         (0x4A4U)
/* WIN0_BPP_LUT170 */
#define VOP_WIN0_BPP_LUT170_OFFSET                         (0x4A8U)
/* WIN0_BPP_LUT171 */
#define VOP_WIN0_BPP_LUT171_OFFSET                         (0x4ACU)
/* WIN0_BPP_LUT172 */
#define VOP_WIN0_BPP_LUT172_OFFSET                         (0x4B0U)
/* WIN0_BPP_LUT173 */
#define VOP_WIN0_BPP_LUT173_OFFSET                         (0x4B4U)
/* WIN0_BPP_LUT174 */
#define VOP_WIN0_BPP_LUT174_OFFSET                         (0x4B8U)
/* WIN0_BPP_LUT175 */
#define VOP_WIN0_BPP_LUT175_OFFSET                         (0x4BCU)
/* WIN0_BPP_LUT176 */
#define VOP_WIN0_BPP_LUT176_OFFSET                         (0x4C0U)
/* WIN0_BPP_LUT177 */
#define VOP_WIN0_BPP_LUT177_OFFSET                         (0x4C4U)
/* WIN0_BPP_LUT178 */
#define VOP_WIN0_BPP_LUT178_OFFSET                         (0x4C8U)
/* WIN0_BPP_LUT179 */
#define VOP_WIN0_BPP_LUT179_OFFSET                         (0x4CCU)
/* WIN0_BPP_LUT180 */
#define VOP_WIN0_BPP_LUT180_OFFSET                         (0x4D0U)
/* WIN0_BPP_LUT181 */
#define VOP_WIN0_BPP_LUT181_OFFSET                         (0x4D4U)
/* WIN0_BPP_LUT182 */
#define VOP_WIN0_BPP_LUT182_OFFSET                         (0x4D8U)
/* WIN0_BPP_LUT183 */
#define VOP_WIN0_BPP_LUT183_OFFSET                         (0x4DCU)
/* WIN0_BPP_LUT184 */
#define VOP_WIN0_BPP_LUT184_OFFSET                         (0x4E0U)
/* WIN0_BPP_LUT185 */
#define VOP_WIN0_BPP_LUT185_OFFSET                         (0x4E4U)
/* WIN0_BPP_LUT186 */
#define VOP_WIN0_BPP_LUT186_OFFSET                         (0x4E8U)
/* WIN0_BPP_LUT187 */
#define VOP_WIN0_BPP_LUT187_OFFSET                         (0x4ECU)
/* WIN0_BPP_LUT188 */
#define VOP_WIN0_BPP_LUT188_OFFSET                         (0x4F0U)
/* WIN0_BPP_LUT189 */
#define VOP_WIN0_BPP_LUT189_OFFSET                         (0x4F4U)
/* WIN0_BPP_LUT190 */
#define VOP_WIN0_BPP_LUT190_OFFSET                         (0x4F8U)
/* WIN0_BPP_LUT191 */
#define VOP_WIN0_BPP_LUT191_OFFSET                         (0x4FCU)
/* WIN0_BPP_LUT192 */
#define VOP_WIN0_BPP_LUT192_OFFSET                         (0x500U)
/* WIN0_BPP_LUT193 */
#define VOP_WIN0_BPP_LUT193_OFFSET                         (0x504U)
/* WIN0_BPP_LUT194 */
#define VOP_WIN0_BPP_LUT194_OFFSET                         (0x508U)
/* WIN0_BPP_LUT195 */
#define VOP_WIN0_BPP_LUT195_OFFSET                         (0x50CU)
/* WIN0_BPP_LUT196 */
#define VOP_WIN0_BPP_LUT196_OFFSET                         (0x510U)
/* WIN0_BPP_LUT197 */
#define VOP_WIN0_BPP_LUT197_OFFSET                         (0x514U)
/* WIN0_BPP_LUT198 */
#define VOP_WIN0_BPP_LUT198_OFFSET                         (0x518U)
/* WIN0_BPP_LUT199 */
#define VOP_WIN0_BPP_LUT199_OFFSET                         (0x51CU)
/* WIN0_BPP_LUT200 */
#define VOP_WIN0_BPP_LUT200_OFFSET                         (0x520U)
/* WIN0_BPP_LUT201 */
#define VOP_WIN0_BPP_LUT201_OFFSET                         (0x524U)
/* WIN0_BPP_LUT202 */
#define VOP_WIN0_BPP_LUT202_OFFSET                         (0x528U)
/* WIN0_BPP_LUT203 */
#define VOP_WIN0_BPP_LUT203_OFFSET                         (0x52CU)
/* WIN0_BPP_LUT204 */
#define VOP_WIN0_BPP_LUT204_OFFSET                         (0x530U)
/* WIN0_BPP_LUT205 */
#define VOP_WIN0_BPP_LUT205_OFFSET                         (0x534U)
/* WIN0_BPP_LUT206 */
#define VOP_WIN0_BPP_LUT206_OFFSET                         (0x538U)
/* WIN0_BPP_LUT207 */
#define VOP_WIN0_BPP_LUT207_OFFSET                         (0x53CU)
/* WIN0_BPP_LUT208 */
#define VOP_WIN0_BPP_LUT208_OFFSET                         (0x540U)
/* WIN0_BPP_LUT209 */
#define VOP_WIN0_BPP_LUT209_OFFSET                         (0x544U)
/* WIN0_BPP_LUT210 */
#define VOP_WIN0_BPP_LUT210_OFFSET                         (0x548U)
/* WIN0_BPP_LUT211 */
#define VOP_WIN0_BPP_LUT211_OFFSET                         (0x54CU)
/* WIN0_BPP_LUT212 */
#define VOP_WIN0_BPP_LUT212_OFFSET                         (0x550U)
/* WIN0_BPP_LUT213 */
#define VOP_WIN0_BPP_LUT213_OFFSET                         (0x554U)
/* WIN0_BPP_LUT214 */
#define VOP_WIN0_BPP_LUT214_OFFSET                         (0x558U)
/* WIN0_BPP_LUT215 */
#define VOP_WIN0_BPP_LUT215_OFFSET                         (0x55CU)
/* WIN0_BPP_LUT216 */
#define VOP_WIN0_BPP_LUT216_OFFSET                         (0x560U)
/* WIN0_BPP_LUT217 */
#define VOP_WIN0_BPP_LUT217_OFFSET                         (0x564U)
/* WIN0_BPP_LUT218 */
#define VOP_WIN0_BPP_LUT218_OFFSET                         (0x568U)
/* WIN0_BPP_LUT219 */
#define VOP_WIN0_BPP_LUT219_OFFSET                         (0x56CU)
/* WIN0_BPP_LUT220 */
#define VOP_WIN0_BPP_LUT220_OFFSET                         (0x570U)
/* WIN0_BPP_LUT221 */
#define VOP_WIN0_BPP_LUT221_OFFSET                         (0x574U)
/* WIN0_BPP_LUT222 */
#define VOP_WIN0_BPP_LUT222_OFFSET                         (0x578U)
/* WIN0_BPP_LUT223 */
#define VOP_WIN0_BPP_LUT223_OFFSET                         (0x57CU)
/* WIN0_BPP_LUT224 */
#define VOP_WIN0_BPP_LUT224_OFFSET                         (0x580U)
/* WIN0_BPP_LUT225 */
#define VOP_WIN0_BPP_LUT225_OFFSET                         (0x584U)
/* WIN0_BPP_LUT226 */
#define VOP_WIN0_BPP_LUT226_OFFSET                         (0x588U)
/* WIN0_BPP_LUT227 */
#define VOP_WIN0_BPP_LUT227_OFFSET                         (0x58CU)
/* WIN0_BPP_LUT228 */
#define VOP_WIN0_BPP_LUT228_OFFSET                         (0x590U)
/* WIN0_BPP_LUT229 */
#define VOP_WIN0_BPP_LUT229_OFFSET                         (0x594U)
/* WIN0_BPP_LUT230 */
#define VOP_WIN0_BPP_LUT230_OFFSET                         (0x598U)
/* WIN0_BPP_LUT231 */
#define VOP_WIN0_BPP_LUT231_OFFSET                         (0x59CU)
/* WIN0_BPP_LUT232 */
#define VOP_WIN0_BPP_LUT232_OFFSET                         (0x5A0U)
/* WIN0_BPP_LUT233 */
#define VOP_WIN0_BPP_LUT233_OFFSET                         (0x5A4U)
/* WIN0_BPP_LUT234 */
#define VOP_WIN0_BPP_LUT234_OFFSET                         (0x5A8U)
/* WIN0_BPP_LUT235 */
#define VOP_WIN0_BPP_LUT235_OFFSET                         (0x5ACU)
/* WIN0_BPP_LUT236 */
#define VOP_WIN0_BPP_LUT236_OFFSET                         (0x5B0U)
/* WIN0_BPP_LUT237 */
#define VOP_WIN0_BPP_LUT237_OFFSET                         (0x5B4U)
/* WIN0_BPP_LUT238 */
#define VOP_WIN0_BPP_LUT238_OFFSET                         (0x5B8U)
/* WIN0_BPP_LUT239 */
#define VOP_WIN0_BPP_LUT239_OFFSET                         (0x5BCU)
/* WIN0_BPP_LUT240 */
#define VOP_WIN0_BPP_LUT240_OFFSET                         (0x5C0U)
/* WIN0_BPP_LUT241 */
#define VOP_WIN0_BPP_LUT241_OFFSET                         (0x5C4U)
/* WIN0_BPP_LUT242 */
#define VOP_WIN0_BPP_LUT242_OFFSET                         (0x5C8U)
/* WIN0_BPP_LUT243 */
#define VOP_WIN0_BPP_LUT243_OFFSET                         (0x5CCU)
/* WIN0_BPP_LUT244 */
#define VOP_WIN0_BPP_LUT244_OFFSET                         (0x5D0U)
/* WIN0_BPP_LUT245 */
#define VOP_WIN0_BPP_LUT245_OFFSET                         (0x5D4U)
/* WIN0_BPP_LUT246 */
#define VOP_WIN0_BPP_LUT246_OFFSET                         (0x5D8U)
/* WIN0_BPP_LUT247 */
#define VOP_WIN0_BPP_LUT247_OFFSET                         (0x5DCU)
/* WIN0_BPP_LUT248 */
#define VOP_WIN0_BPP_LUT248_OFFSET                         (0x5E0U)
/* WIN0_BPP_LUT249 */
#define VOP_WIN0_BPP_LUT249_OFFSET                         (0x5E4U)
/* WIN0_BPP_LUT250 */
#define VOP_WIN0_BPP_LUT250_OFFSET                         (0x5E8U)
/* WIN0_BPP_LUT251 */
#define VOP_WIN0_BPP_LUT251_OFFSET                         (0x5ECU)
/* WIN0_BPP_LUT252 */
#define VOP_WIN0_BPP_LUT252_OFFSET                         (0x5F0U)
/* WIN0_BPP_LUT253 */
#define VOP_WIN0_BPP_LUT253_OFFSET                         (0x5F4U)
/* WIN0_BPP_LUT254 */
#define VOP_WIN0_BPP_LUT254_OFFSET                         (0x5F8U)
/* WIN0_BPP_LUT255 */
#define VOP_WIN0_BPP_LUT255_OFFSET                         (0x5FCU)
/* WIN1_BPP_LUT000 */
#define VOP_WIN1_BPP_LUT000_OFFSET                         (0x600U)
/* WIN1_BPP_LUT001 */
#define VOP_WIN1_BPP_LUT001_OFFSET                         (0x604U)
/* WIN1_BPP_LUT002 */
#define VOP_WIN1_BPP_LUT002_OFFSET                         (0x608U)
/* WIN1_BPP_LUT003 */
#define VOP_WIN1_BPP_LUT003_OFFSET                         (0x60CU)
/* WIN1_BPP_LUT004 */
#define VOP_WIN1_BPP_LUT004_OFFSET                         (0x610U)
/* WIN1_BPP_LUT005 */
#define VOP_WIN1_BPP_LUT005_OFFSET                         (0x614U)
/* WIN1_BPP_LUT006 */
#define VOP_WIN1_BPP_LUT006_OFFSET                         (0x618U)
/* WIN1_BPP_LUT007 */
#define VOP_WIN1_BPP_LUT007_OFFSET                         (0x61CU)
/* WIN1_BPP_LUT008 */
#define VOP_WIN1_BPP_LUT008_OFFSET                         (0x620U)
/* WIN1_BPP_LUT009 */
#define VOP_WIN1_BPP_LUT009_OFFSET                         (0x624U)
/* WIN1_BPP_LUT010 */
#define VOP_WIN1_BPP_LUT010_OFFSET                         (0x628U)
/* WIN1_BPP_LUT011 */
#define VOP_WIN1_BPP_LUT011_OFFSET                         (0x62CU)
/* WIN1_BPP_LUT012 */
#define VOP_WIN1_BPP_LUT012_OFFSET                         (0x630U)
/* WIN1_BPP_LUT013 */
#define VOP_WIN1_BPP_LUT013_OFFSET                         (0x634U)
/* WIN1_BPP_LUT014 */
#define VOP_WIN1_BPP_LUT014_OFFSET                         (0x638U)
/* WIN1_BPP_LUT015 */
#define VOP_WIN1_BPP_LUT015_OFFSET                         (0x63CU)
/* WIN1_BPP_LUT016 */
#define VOP_WIN1_BPP_LUT016_OFFSET                         (0x640U)
/* WIN1_BPP_LUT017 */
#define VOP_WIN1_BPP_LUT017_OFFSET                         (0x644U)
/* WIN1_BPP_LUT018 */
#define VOP_WIN1_BPP_LUT018_OFFSET                         (0x648U)
/* WIN1_BPP_LUT019 */
#define VOP_WIN1_BPP_LUT019_OFFSET                         (0x64CU)
/* WIN1_BPP_LUT020 */
#define VOP_WIN1_BPP_LUT020_OFFSET                         (0x650U)
/* WIN1_BPP_LUT021 */
#define VOP_WIN1_BPP_LUT021_OFFSET                         (0x654U)
/* WIN1_BPP_LUT022 */
#define VOP_WIN1_BPP_LUT022_OFFSET                         (0x658U)
/* WIN1_BPP_LUT023 */
#define VOP_WIN1_BPP_LUT023_OFFSET                         (0x65CU)
/* WIN1_BPP_LUT024 */
#define VOP_WIN1_BPP_LUT024_OFFSET                         (0x660U)
/* WIN1_BPP_LUT025 */
#define VOP_WIN1_BPP_LUT025_OFFSET                         (0x664U)
/* WIN1_BPP_LUT026 */
#define VOP_WIN1_BPP_LUT026_OFFSET                         (0x668U)
/* WIN1_BPP_LUT027 */
#define VOP_WIN1_BPP_LUT027_OFFSET                         (0x66CU)
/* WIN1_BPP_LUT028 */
#define VOP_WIN1_BPP_LUT028_OFFSET                         (0x670U)
/* WIN1_BPP_LUT029 */
#define VOP_WIN1_BPP_LUT029_OFFSET                         (0x674U)
/* WIN1_BPP_LUT030 */
#define VOP_WIN1_BPP_LUT030_OFFSET                         (0x678U)
/* WIN1_BPP_LUT031 */
#define VOP_WIN1_BPP_LUT031_OFFSET                         (0x67CU)
/* WIN1_BPP_LUT032 */
#define VOP_WIN1_BPP_LUT032_OFFSET                         (0x680U)
/* WIN1_BPP_LUT033 */
#define VOP_WIN1_BPP_LUT033_OFFSET                         (0x684U)
/* WIN1_BPP_LUT034 */
#define VOP_WIN1_BPP_LUT034_OFFSET                         (0x688U)
/* WIN1_BPP_LUT035 */
#define VOP_WIN1_BPP_LUT035_OFFSET                         (0x68CU)
/* WIN1_BPP_LUT036 */
#define VOP_WIN1_BPP_LUT036_OFFSET                         (0x690U)
/* WIN1_BPP_LUT037 */
#define VOP_WIN1_BPP_LUT037_OFFSET                         (0x694U)
/* WIN1_BPP_LUT038 */
#define VOP_WIN1_BPP_LUT038_OFFSET                         (0x698U)
/* WIN1_BPP_LUT039 */
#define VOP_WIN1_BPP_LUT039_OFFSET                         (0x69CU)
/* WIN1_BPP_LUT040 */
#define VOP_WIN1_BPP_LUT040_OFFSET                         (0x6A0U)
/* WIN1_BPP_LUT041 */
#define VOP_WIN1_BPP_LUT041_OFFSET                         (0x6A4U)
/* WIN1_BPP_LUT042 */
#define VOP_WIN1_BPP_LUT042_OFFSET                         (0x6A8U)
/* WIN1_BPP_LUT043 */
#define VOP_WIN1_BPP_LUT043_OFFSET                         (0x6ACU)
/* WIN1_BPP_LUT044 */
#define VOP_WIN1_BPP_LUT044_OFFSET                         (0x6B0U)
/* WIN1_BPP_LUT045 */
#define VOP_WIN1_BPP_LUT045_OFFSET                         (0x6B4U)
/* WIN1_BPP_LUT046 */
#define VOP_WIN1_BPP_LUT046_OFFSET                         (0x6B8U)
/* WIN1_BPP_LUT047 */
#define VOP_WIN1_BPP_LUT047_OFFSET                         (0x6BCU)
/* WIN1_BPP_LUT048 */
#define VOP_WIN1_BPP_LUT048_OFFSET                         (0x6C0U)
/* WIN1_BPP_LUT049 */
#define VOP_WIN1_BPP_LUT049_OFFSET                         (0x6C4U)
/* WIN1_BPP_LUT050 */
#define VOP_WIN1_BPP_LUT050_OFFSET                         (0x6C8U)
/* WIN1_BPP_LUT051 */
#define VOP_WIN1_BPP_LUT051_OFFSET                         (0x6CCU)
/* WIN1_BPP_LUT052 */
#define VOP_WIN1_BPP_LUT052_OFFSET                         (0x6D0U)
/* WIN1_BPP_LUT053 */
#define VOP_WIN1_BPP_LUT053_OFFSET                         (0x6D4U)
/* WIN1_BPP_LUT054 */
#define VOP_WIN1_BPP_LUT054_OFFSET                         (0x6D8U)
/* WIN1_BPP_LUT055 */
#define VOP_WIN1_BPP_LUT055_OFFSET                         (0x6DCU)
/* WIN1_BPP_LUT056 */
#define VOP_WIN1_BPP_LUT056_OFFSET                         (0x6E0U)
/* WIN1_BPP_LUT057 */
#define VOP_WIN1_BPP_LUT057_OFFSET                         (0x6E4U)
/* WIN1_BPP_LUT058 */
#define VOP_WIN1_BPP_LUT058_OFFSET                         (0x6E8U)
/* WIN1_BPP_LUT059 */
#define VOP_WIN1_BPP_LUT059_OFFSET                         (0x6ECU)
/* WIN1_BPP_LUT060 */
#define VOP_WIN1_BPP_LUT060_OFFSET                         (0x6F0U)
/* WIN1_BPP_LUT061 */
#define VOP_WIN1_BPP_LUT061_OFFSET                         (0x6F4U)
/* WIN1_BPP_LUT062 */
#define VOP_WIN1_BPP_LUT062_OFFSET                         (0x6F8U)
/* WIN1_BPP_LUT063 */
#define VOP_WIN1_BPP_LUT063_OFFSET                         (0x6FCU)
/* WIN1_BPP_LUT064 */
#define VOP_WIN1_BPP_LUT064_OFFSET                         (0x700U)
/* WIN1_BPP_LUT065 */
#define VOP_WIN1_BPP_LUT065_OFFSET                         (0x704U)
/* WIN1_BPP_LUT066 */
#define VOP_WIN1_BPP_LUT066_OFFSET                         (0x708U)
/* WIN1_BPP_LUT067 */
#define VOP_WIN1_BPP_LUT067_OFFSET                         (0x70CU)
/* WIN1_BPP_LUT068 */
#define VOP_WIN1_BPP_LUT068_OFFSET                         (0x710U)
/* WIN1_BPP_LUT069 */
#define VOP_WIN1_BPP_LUT069_OFFSET                         (0x714U)
/* WIN1_BPP_LUT070 */
#define VOP_WIN1_BPP_LUT070_OFFSET                         (0x718U)
/* WIN1_BPP_LUT071 */
#define VOP_WIN1_BPP_LUT071_OFFSET                         (0x71CU)
/* WIN1_BPP_LUT072 */
#define VOP_WIN1_BPP_LUT072_OFFSET                         (0x720U)
/* WIN1_BPP_LUT073 */
#define VOP_WIN1_BPP_LUT073_OFFSET                         (0x724U)
/* WIN1_BPP_LUT074 */
#define VOP_WIN1_BPP_LUT074_OFFSET                         (0x728U)
/* WIN1_BPP_LUT075 */
#define VOP_WIN1_BPP_LUT075_OFFSET                         (0x72CU)
/* WIN1_BPP_LUT076 */
#define VOP_WIN1_BPP_LUT076_OFFSET                         (0x730U)
/* WIN1_BPP_LUT077 */
#define VOP_WIN1_BPP_LUT077_OFFSET                         (0x734U)
/* WIN1_BPP_LUT078 */
#define VOP_WIN1_BPP_LUT078_OFFSET                         (0x738U)
/* WIN1_BPP_LUT079 */
#define VOP_WIN1_BPP_LUT079_OFFSET                         (0x73CU)
/* WIN1_BPP_LUT080 */
#define VOP_WIN1_BPP_LUT080_OFFSET                         (0x740U)
/* WIN1_BPP_LUT081 */
#define VOP_WIN1_BPP_LUT081_OFFSET                         (0x744U)
/* WIN1_BPP_LUT082 */
#define VOP_WIN1_BPP_LUT082_OFFSET                         (0x748U)
/* WIN1_BPP_LUT083 */
#define VOP_WIN1_BPP_LUT083_OFFSET                         (0x74CU)
/* WIN1_BPP_LUT084 */
#define VOP_WIN1_BPP_LUT084_OFFSET                         (0x750U)
/* WIN1_BPP_LUT085 */
#define VOP_WIN1_BPP_LUT085_OFFSET                         (0x754U)
/* WIN1_BPP_LUT086 */
#define VOP_WIN1_BPP_LUT086_OFFSET                         (0x758U)
/* WIN1_BPP_LUT087 */
#define VOP_WIN1_BPP_LUT087_OFFSET                         (0x75CU)
/* WIN1_BPP_LUT088 */
#define VOP_WIN1_BPP_LUT088_OFFSET                         (0x760U)
/* WIN1_BPP_LUT089 */
#define VOP_WIN1_BPP_LUT089_OFFSET                         (0x764U)
/* WIN1_BPP_LUT090 */
#define VOP_WIN1_BPP_LUT090_OFFSET                         (0x768U)
/* WIN1_BPP_LUT091 */
#define VOP_WIN1_BPP_LUT091_OFFSET                         (0x76CU)
/* WIN1_BPP_LUT092 */
#define VOP_WIN1_BPP_LUT092_OFFSET                         (0x770U)
/* WIN1_BPP_LUT093 */
#define VOP_WIN1_BPP_LUT093_OFFSET                         (0x774U)
/* WIN1_BPP_LUT094 */
#define VOP_WIN1_BPP_LUT094_OFFSET                         (0x778U)
/* WIN1_BPP_LUT095 */
#define VOP_WIN1_BPP_LUT095_OFFSET                         (0x77CU)
/* WIN1_BPP_LUT096 */
#define VOP_WIN1_BPP_LUT096_OFFSET                         (0x780U)
/* WIN1_BPP_LUT097 */
#define VOP_WIN1_BPP_LUT097_OFFSET                         (0x784U)
/* WIN1_BPP_LUT098 */
#define VOP_WIN1_BPP_LUT098_OFFSET                         (0x788U)
/* WIN1_BPP_LUT099 */
#define VOP_WIN1_BPP_LUT099_OFFSET                         (0x78CU)
/* WIN1_BPP_LUT100 */
#define VOP_WIN1_BPP_LUT100_OFFSET                         (0x790U)
/* WIN1_BPP_LUT101 */
#define VOP_WIN1_BPP_LUT101_OFFSET                         (0x794U)
/* WIN1_BPP_LUT102 */
#define VOP_WIN1_BPP_LUT102_OFFSET                         (0x798U)
/* WIN1_BPP_LUT103 */
#define VOP_WIN1_BPP_LUT103_OFFSET                         (0x79CU)
/* WIN1_BPP_LUT104 */
#define VOP_WIN1_BPP_LUT104_OFFSET                         (0x7A0U)
/* WIN1_BPP_LUT105 */
#define VOP_WIN1_BPP_LUT105_OFFSET                         (0x7A4U)
/* WIN1_BPP_LUT106 */
#define VOP_WIN1_BPP_LUT106_OFFSET                         (0x7A8U)
/* WIN1_BPP_LUT107 */
#define VOP_WIN1_BPP_LUT107_OFFSET                         (0x7ACU)
/* WIN1_BPP_LUT108 */
#define VOP_WIN1_BPP_LUT108_OFFSET                         (0x7B0U)
/* WIN1_BPP_LUT109 */
#define VOP_WIN1_BPP_LUT109_OFFSET                         (0x7B4U)
/* WIN1_BPP_LUT110 */
#define VOP_WIN1_BPP_LUT110_OFFSET                         (0x7B8U)
/* WIN1_BPP_LUT111 */
#define VOP_WIN1_BPP_LUT111_OFFSET                         (0x7BCU)
/* WIN1_BPP_LUT112 */
#define VOP_WIN1_BPP_LUT112_OFFSET                         (0x7C0U)
/* WIN1_BPP_LUT113 */
#define VOP_WIN1_BPP_LUT113_OFFSET                         (0x7C4U)
/* WIN1_BPP_LUT114 */
#define VOP_WIN1_BPP_LUT114_OFFSET                         (0x7C8U)
/* WIN1_BPP_LUT115 */
#define VOP_WIN1_BPP_LUT115_OFFSET                         (0x7CCU)
/* WIN1_BPP_LUT116 */
#define VOP_WIN1_BPP_LUT116_OFFSET                         (0x7D0U)
/* WIN1_BPP_LUT117 */
#define VOP_WIN1_BPP_LUT117_OFFSET                         (0x7D4U)
/* WIN1_BPP_LUT118 */
#define VOP_WIN1_BPP_LUT118_OFFSET                         (0x7D8U)
/* WIN1_BPP_LUT119 */
#define VOP_WIN1_BPP_LUT119_OFFSET                         (0x7DCU)
/* WIN1_BPP_LUT120 */
#define VOP_WIN1_BPP_LUT120_OFFSET                         (0x7E0U)
/* WIN1_BPP_LUT121 */
#define VOP_WIN1_BPP_LUT121_OFFSET                         (0x7E4U)
/* WIN1_BPP_LUT122 */
#define VOP_WIN1_BPP_LUT122_OFFSET                         (0x7E8U)
/* WIN1_BPP_LUT123 */
#define VOP_WIN1_BPP_LUT123_OFFSET                         (0x7ECU)
/* WIN1_BPP_LUT124 */
#define VOP_WIN1_BPP_LUT124_OFFSET                         (0x7F0U)
/* WIN1_BPP_LUT125 */
#define VOP_WIN1_BPP_LUT125_OFFSET                         (0x7F4U)
/* WIN1_BPP_LUT126 */
#define VOP_WIN1_BPP_LUT126_OFFSET                         (0x7F8U)
/* WIN1_BPP_LUT127 */
#define VOP_WIN1_BPP_LUT127_OFFSET                         (0x7FCU)
/* WIN1_BPP_LUT128 */
#define VOP_WIN1_BPP_LUT128_OFFSET                         (0x800U)
/* WIN1_BPP_LUT129 */
#define VOP_WIN1_BPP_LUT129_OFFSET                         (0x804U)
/* WIN1_BPP_LUT130 */
#define VOP_WIN1_BPP_LUT130_OFFSET                         (0x808U)
/* WIN1_BPP_LUT131 */
#define VOP_WIN1_BPP_LUT131_OFFSET                         (0x80CU)
/* WIN1_BPP_LUT132 */
#define VOP_WIN1_BPP_LUT132_OFFSET                         (0x810U)
/* WIN1_BPP_LUT133 */
#define VOP_WIN1_BPP_LUT133_OFFSET                         (0x814U)
/* WIN1_BPP_LUT134 */
#define VOP_WIN1_BPP_LUT134_OFFSET                         (0x818U)
/* WIN1_BPP_LUT135 */
#define VOP_WIN1_BPP_LUT135_OFFSET                         (0x81CU)
/* WIN1_BPP_LUT136 */
#define VOP_WIN1_BPP_LUT136_OFFSET                         (0x820U)
/* WIN1_BPP_LUT137 */
#define VOP_WIN1_BPP_LUT137_OFFSET                         (0x824U)
/* WIN1_BPP_LUT138 */
#define VOP_WIN1_BPP_LUT138_OFFSET                         (0x828U)
/* WIN1_BPP_LUT139 */
#define VOP_WIN1_BPP_LUT139_OFFSET                         (0x82CU)
/* WIN1_BPP_LUT140 */
#define VOP_WIN1_BPP_LUT140_OFFSET                         (0x830U)
/* WIN1_BPP_LUT141 */
#define VOP_WIN1_BPP_LUT141_OFFSET                         (0x834U)
/* WIN1_BPP_LUT142 */
#define VOP_WIN1_BPP_LUT142_OFFSET                         (0x838U)
/* WIN1_BPP_LUT143 */
#define VOP_WIN1_BPP_LUT143_OFFSET                         (0x83CU)
/* WIN1_BPP_LUT144 */
#define VOP_WIN1_BPP_LUT144_OFFSET                         (0x840U)
/* WIN1_BPP_LUT145 */
#define VOP_WIN1_BPP_LUT145_OFFSET                         (0x844U)
/* WIN1_BPP_LUT146 */
#define VOP_WIN1_BPP_LUT146_OFFSET                         (0x848U)
/* WIN1_BPP_LUT147 */
#define VOP_WIN1_BPP_LUT147_OFFSET                         (0x84CU)
/* WIN1_BPP_LUT148 */
#define VOP_WIN1_BPP_LUT148_OFFSET                         (0x850U)
/* WIN1_BPP_LUT149 */
#define VOP_WIN1_BPP_LUT149_OFFSET                         (0x854U)
/* WIN1_BPP_LUT150 */
#define VOP_WIN1_BPP_LUT150_OFFSET                         (0x858U)
/* WIN1_BPP_LUT151 */
#define VOP_WIN1_BPP_LUT151_OFFSET                         (0x85CU)
/* WIN1_BPP_LUT152 */
#define VOP_WIN1_BPP_LUT152_OFFSET                         (0x860U)
/* WIN1_BPP_LUT153 */
#define VOP_WIN1_BPP_LUT153_OFFSET                         (0x864U)
/* WIN1_BPP_LUT154 */
#define VOP_WIN1_BPP_LUT154_OFFSET                         (0x868U)
/* WIN1_BPP_LUT155 */
#define VOP_WIN1_BPP_LUT155_OFFSET                         (0x86CU)
/* WIN1_BPP_LUT156 */
#define VOP_WIN1_BPP_LUT156_OFFSET                         (0x870U)
/* WIN1_BPP_LUT157 */
#define VOP_WIN1_BPP_LUT157_OFFSET                         (0x874U)
/* WIN1_BPP_LUT158 */
#define VOP_WIN1_BPP_LUT158_OFFSET                         (0x878U)
/* WIN1_BPP_LUT159 */
#define VOP_WIN1_BPP_LUT159_OFFSET                         (0x87CU)
/* WIN1_BPP_LUT160 */
#define VOP_WIN1_BPP_LUT160_OFFSET                         (0x880U)
/* WIN1_BPP_LUT161 */
#define VOP_WIN1_BPP_LUT161_OFFSET                         (0x884U)
/* WIN1_BPP_LUT162 */
#define VOP_WIN1_BPP_LUT162_OFFSET                         (0x888U)
/* WIN1_BPP_LUT163 */
#define VOP_WIN1_BPP_LUT163_OFFSET                         (0x88CU)
/* WIN1_BPP_LUT164 */
#define VOP_WIN1_BPP_LUT164_OFFSET                         (0x890U)
/* WIN1_BPP_LUT165 */
#define VOP_WIN1_BPP_LUT165_OFFSET                         (0x894U)
/* WIN1_BPP_LUT166 */
#define VOP_WIN1_BPP_LUT166_OFFSET                         (0x898U)
/* WIN1_BPP_LUT167 */
#define VOP_WIN1_BPP_LUT167_OFFSET                         (0x89CU)
/* WIN1_BPP_LUT168 */
#define VOP_WIN1_BPP_LUT168_OFFSET                         (0x8A0U)
/* WIN1_BPP_LUT169 */
#define VOP_WIN1_BPP_LUT169_OFFSET                         (0x8A4U)
/* WIN1_BPP_LUT170 */
#define VOP_WIN1_BPP_LUT170_OFFSET                         (0x8A8U)
/* WIN1_BPP_LUT171 */
#define VOP_WIN1_BPP_LUT171_OFFSET                         (0x8ACU)
/* WIN1_BPP_LUT172 */
#define VOP_WIN1_BPP_LUT172_OFFSET                         (0x8B0U)
/* WIN1_BPP_LUT173 */
#define VOP_WIN1_BPP_LUT173_OFFSET                         (0x8B4U)
/* WIN1_BPP_LUT174 */
#define VOP_WIN1_BPP_LUT174_OFFSET                         (0x8B8U)
/* WIN1_BPP_LUT175 */
#define VOP_WIN1_BPP_LUT175_OFFSET                         (0x8BCU)
/* WIN1_BPP_LUT176 */
#define VOP_WIN1_BPP_LUT176_OFFSET                         (0x8C0U)
/* WIN1_BPP_LUT177 */
#define VOP_WIN1_BPP_LUT177_OFFSET                         (0x8C4U)
/* WIN1_BPP_LUT178 */
#define VOP_WIN1_BPP_LUT178_OFFSET                         (0x8C8U)
/* WIN1_BPP_LUT179 */
#define VOP_WIN1_BPP_LUT179_OFFSET                         (0x8CCU)
/* WIN1_BPP_LUT180 */
#define VOP_WIN1_BPP_LUT180_OFFSET                         (0x8D0U)
/* WIN1_BPP_LUT181 */
#define VOP_WIN1_BPP_LUT181_OFFSET                         (0x8D4U)
/* WIN1_BPP_LUT182 */
#define VOP_WIN1_BPP_LUT182_OFFSET                         (0x8D8U)
/* WIN1_BPP_LUT183 */
#define VOP_WIN1_BPP_LUT183_OFFSET                         (0x8DCU)
/* WIN1_BPP_LUT184 */
#define VOP_WIN1_BPP_LUT184_OFFSET                         (0x8E0U)
/* WIN1_BPP_LUT185 */
#define VOP_WIN1_BPP_LUT185_OFFSET                         (0x8E4U)
/* WIN1_BPP_LUT186 */
#define VOP_WIN1_BPP_LUT186_OFFSET                         (0x8E8U)
/* WIN1_BPP_LUT187 */
#define VOP_WIN1_BPP_LUT187_OFFSET                         (0x8ECU)
/* WIN1_BPP_LUT188 */
#define VOP_WIN1_BPP_LUT188_OFFSET                         (0x8F0U)
/* WIN1_BPP_LUT189 */
#define VOP_WIN1_BPP_LUT189_OFFSET                         (0x8F4U)
/* WIN1_BPP_LUT190 */
#define VOP_WIN1_BPP_LUT190_OFFSET                         (0x8F8U)
/* WIN1_BPP_LUT191 */
#define VOP_WIN1_BPP_LUT191_OFFSET                         (0x8FCU)
/* WIN1_BPP_LUT192 */
#define VOP_WIN1_BPP_LUT192_OFFSET                         (0x900U)
/* WIN1_BPP_LUT193 */
#define VOP_WIN1_BPP_LUT193_OFFSET                         (0x904U)
/* WIN1_BPP_LUT194 */
#define VOP_WIN1_BPP_LUT194_OFFSET                         (0x908U)
/* WIN1_BPP_LUT195 */
#define VOP_WIN1_BPP_LUT195_OFFSET                         (0x90CU)
/* WIN1_BPP_LUT196 */
#define VOP_WIN1_BPP_LUT196_OFFSET                         (0x910U)
/* WIN1_BPP_LUT197 */
#define VOP_WIN1_BPP_LUT197_OFFSET                         (0x914U)
/* WIN1_BPP_LUT198 */
#define VOP_WIN1_BPP_LUT198_OFFSET                         (0x918U)
/* WIN1_BPP_LUT199 */
#define VOP_WIN1_BPP_LUT199_OFFSET                         (0x91CU)
/* WIN1_BPP_LUT200 */
#define VOP_WIN1_BPP_LUT200_OFFSET                         (0x920U)
/* WIN1_BPP_LUT201 */
#define VOP_WIN1_BPP_LUT201_OFFSET                         (0x924U)
/* WIN1_BPP_LUT202 */
#define VOP_WIN1_BPP_LUT202_OFFSET                         (0x928U)
/* WIN1_BPP_LUT203 */
#define VOP_WIN1_BPP_LUT203_OFFSET                         (0x92CU)
/* WIN1_BPP_LUT204 */
#define VOP_WIN1_BPP_LUT204_OFFSET                         (0x930U)
/* WIN1_BPP_LUT205 */
#define VOP_WIN1_BPP_LUT205_OFFSET                         (0x934U)
/* WIN1_BPP_LUT206 */
#define VOP_WIN1_BPP_LUT206_OFFSET                         (0x938U)
/* WIN1_BPP_LUT207 */
#define VOP_WIN1_BPP_LUT207_OFFSET                         (0x93CU)
/* WIN1_BPP_LUT208 */
#define VOP_WIN1_BPP_LUT208_OFFSET                         (0x940U)
/* WIN1_BPP_LUT209 */
#define VOP_WIN1_BPP_LUT209_OFFSET                         (0x944U)
/* WIN1_BPP_LUT210 */
#define VOP_WIN1_BPP_LUT210_OFFSET                         (0x948U)
/* WIN1_BPP_LUT211 */
#define VOP_WIN1_BPP_LUT211_OFFSET                         (0x94CU)
/* WIN1_BPP_LUT212 */
#define VOP_WIN1_BPP_LUT212_OFFSET                         (0x950U)
/* WIN1_BPP_LUT213 */
#define VOP_WIN1_BPP_LUT213_OFFSET                         (0x954U)
/* WIN1_BPP_LUT214 */
#define VOP_WIN1_BPP_LUT214_OFFSET                         (0x958U)
/* WIN1_BPP_LUT215 */
#define VOP_WIN1_BPP_LUT215_OFFSET                         (0x95CU)
/* WIN1_BPP_LUT216 */
#define VOP_WIN1_BPP_LUT216_OFFSET                         (0x960U)
/* WIN1_BPP_LUT217 */
#define VOP_WIN1_BPP_LUT217_OFFSET                         (0x964U)
/* WIN1_BPP_LUT218 */
#define VOP_WIN1_BPP_LUT218_OFFSET                         (0x968U)
/* WIN1_BPP_LUT219 */
#define VOP_WIN1_BPP_LUT219_OFFSET                         (0x96CU)
/* WIN1_BPP_LUT220 */
#define VOP_WIN1_BPP_LUT220_OFFSET                         (0x970U)
/* WIN1_BPP_LUT221 */
#define VOP_WIN1_BPP_LUT221_OFFSET                         (0x974U)
/* WIN1_BPP_LUT222 */
#define VOP_WIN1_BPP_LUT222_OFFSET                         (0x978U)
/* WIN1_BPP_LUT223 */
#define VOP_WIN1_BPP_LUT223_OFFSET                         (0x97CU)
/* WIN1_BPP_LUT224 */
#define VOP_WIN1_BPP_LUT224_OFFSET                         (0x980U)
/* WIN1_BPP_LUT225 */
#define VOP_WIN1_BPP_LUT225_OFFSET                         (0x984U)
/* WIN1_BPP_LUT226 */
#define VOP_WIN1_BPP_LUT226_OFFSET                         (0x988U)
/* WIN1_BPP_LUT227 */
#define VOP_WIN1_BPP_LUT227_OFFSET                         (0x98CU)
/* WIN1_BPP_LUT228 */
#define VOP_WIN1_BPP_LUT228_OFFSET                         (0x990U)
/* WIN1_BPP_LUT229 */
#define VOP_WIN1_BPP_LUT229_OFFSET                         (0x994U)
/* WIN1_BPP_LUT230 */
#define VOP_WIN1_BPP_LUT230_OFFSET                         (0x998U)
/* WIN1_BPP_LUT231 */
#define VOP_WIN1_BPP_LUT231_OFFSET                         (0x99CU)
/* WIN1_BPP_LUT232 */
#define VOP_WIN1_BPP_LUT232_OFFSET                         (0x9A0U)
/* WIN1_BPP_LUT233 */
#define VOP_WIN1_BPP_LUT233_OFFSET                         (0x9A4U)
/* WIN1_BPP_LUT234 */
#define VOP_WIN1_BPP_LUT234_OFFSET                         (0x9A8U)
/* WIN1_BPP_LUT235 */
#define VOP_WIN1_BPP_LUT235_OFFSET                         (0x9ACU)
/* WIN1_BPP_LUT236 */
#define VOP_WIN1_BPP_LUT236_OFFSET                         (0x9B0U)
/* WIN1_BPP_LUT237 */
#define VOP_WIN1_BPP_LUT237_OFFSET                         (0x9B4U)
/* WIN1_BPP_LUT238 */
#define VOP_WIN1_BPP_LUT238_OFFSET                         (0x9B8U)
/* WIN1_BPP_LUT239 */
#define VOP_WIN1_BPP_LUT239_OFFSET                         (0x9BCU)
/* WIN1_BPP_LUT240 */
#define VOP_WIN1_BPP_LUT240_OFFSET                         (0x9C0U)
/* WIN1_BPP_LUT241 */
#define VOP_WIN1_BPP_LUT241_OFFSET                         (0x9C4U)
/* WIN1_BPP_LUT242 */
#define VOP_WIN1_BPP_LUT242_OFFSET                         (0x9C8U)
/* WIN1_BPP_LUT243 */
#define VOP_WIN1_BPP_LUT243_OFFSET                         (0x9CCU)
/* WIN1_BPP_LUT244 */
#define VOP_WIN1_BPP_LUT244_OFFSET                         (0x9D0U)
/* WIN1_BPP_LUT245 */
#define VOP_WIN1_BPP_LUT245_OFFSET                         (0x9D4U)
/* WIN1_BPP_LUT246 */
#define VOP_WIN1_BPP_LUT246_OFFSET                         (0x9D8U)
/* WIN1_BPP_LUT247 */
#define VOP_WIN1_BPP_LUT247_OFFSET                         (0x9DCU)
/* WIN1_BPP_LUT248 */
#define VOP_WIN1_BPP_LUT248_OFFSET                         (0x9E0U)
/* WIN1_BPP_LUT249 */
#define VOP_WIN1_BPP_LUT249_OFFSET                         (0x9E4U)
/* WIN1_BPP_LUT250 */
#define VOP_WIN1_BPP_LUT250_OFFSET                         (0x9E8U)
/* WIN1_BPP_LUT251 */
#define VOP_WIN1_BPP_LUT251_OFFSET                         (0x9ECU)
/* WIN1_BPP_LUT252 */
#define VOP_WIN1_BPP_LUT252_OFFSET                         (0x9F0U)
/* WIN1_BPP_LUT253 */
#define VOP_WIN1_BPP_LUT253_OFFSET                         (0x9F4U)
/* WIN1_BPP_LUT254 */
#define VOP_WIN1_BPP_LUT254_OFFSET                         (0x9F8U)
/* WIN1_BPP_LUT255 */
#define VOP_WIN1_BPP_LUT255_OFFSET                         (0x9FCU)
/* DSC_SYS_CTRL0_IMD */
#define VOP_DSC_SYS_CTRL0_IMD_OFFSET                       (0xA00U)
#define VOP_DSC_SYS_CTRL0_IMD_DSC_CONFIG_EN_SHIFT          (0U)
#define VOP_DSC_SYS_CTRL0_IMD_DSC_CONFIG_EN_MASK           (0x1U << VOP_DSC_SYS_CTRL0_IMD_DSC_CONFIG_EN_SHIFT)          /* 0x00000001 */
#define VOP_DSC_SYS_CTRL0_IMD_DSC_IMD_CONFIG_EN_SHIFT      (4U)
#define VOP_DSC_SYS_CTRL0_IMD_DSC_IMD_CONFIG_EN_MASK       (0x1U << VOP_DSC_SYS_CTRL0_IMD_DSC_IMD_CONFIG_EN_SHIFT)      /* 0x00000010 */
#define VOP_DSC_SYS_CTRL0_IMD_DSC_MEM_GATING_EN_SHIFT      (8U)
#define VOP_DSC_SYS_CTRL0_IMD_DSC_MEM_GATING_EN_MASK       (0x1U << VOP_DSC_SYS_CTRL0_IMD_DSC_MEM_GATING_EN_SHIFT)      /* 0x00000100 */
#define VOP_DSC_SYS_CTRL0_IMD_DSC_SOFT_RST_SHIFT           (12U)
#define VOP_DSC_SYS_CTRL0_IMD_DSC_SOFT_RST_MASK            (0x1U << VOP_DSC_SYS_CTRL0_IMD_DSC_SOFT_RST_SHIFT)           /* 0x00001000 */
/* DSC_SYS_CTRL1 */
#define VOP_DSC_SYS_CTRL1_OFFSET                           (0xA04U)
#define VOP_DSC_SYS_CTRL1_DSI_HALT_EN_SHIFT                (0U)
#define VOP_DSC_SYS_CTRL1_DSI_HALT_EN_MASK                 (0x1U << VOP_DSC_SYS_CTRL1_DSI_HALT_EN_SHIFT)                /* 0x00000001 */
#define VOP_DSC_SYS_CTRL1_DSC_REQ_OUT_EN_SHIFT             (1U)
#define VOP_DSC_SYS_CTRL1_DSC_REQ_OUT_EN_MASK              (0x1U << VOP_DSC_SYS_CTRL1_DSC_REQ_OUT_EN_SHIFT)             /* 0x00000002 */
#define VOP_DSC_SYS_CTRL1_DSC_MUTIPLEX_EOC_EN_SHIFT        (2U)
#define VOP_DSC_SYS_CTRL1_DSC_MUTIPLEX_EOC_EN_MASK         (0x1U << VOP_DSC_SYS_CTRL1_DSC_MUTIPLEX_EOC_EN_SHIFT)        /* 0x00000004 */
#define VOP_DSC_SYS_CTRL1_DSC_VIDEO_MODE_SHIFT             (3U)
#define VOP_DSC_SYS_CTRL1_DSC_VIDEO_MODE_MASK              (0x1U << VOP_DSC_SYS_CTRL1_DSC_VIDEO_MODE_SHIFT)             /* 0x00000008 */
#define VOP_DSC_SYS_CTRL1_DSC_ICH_RST_MANUAL_VALUE_SHIFT   (4U)
#define VOP_DSC_SYS_CTRL1_DSC_ICH_RST_MANUAL_VALUE_MASK    (0x1U << VOP_DSC_SYS_CTRL1_DSC_ICH_RST_MANUAL_VALUE_SHIFT)   /* 0x00000010 */
#define VOP_DSC_SYS_CTRL1_DSC_ICH_RST_MANUAL_MODE_SHIFT    (5U)
#define VOP_DSC_SYS_CTRL1_DSC_ICH_RST_MANUAL_MODE_MASK     (0x1U << VOP_DSC_SYS_CTRL1_DSC_ICH_RST_MANUAL_MODE_SHIFT)    /* 0x00000020 */
#define VOP_DSC_SYS_CTRL1_DSC_ICH_DISABLE_SHIFT            (6U)
#define VOP_DSC_SYS_CTRL1_DSC_ICH_DISABLE_MASK             (0x1U << VOP_DSC_SYS_CTRL1_DSC_ICH_DISABLE_SHIFT)            /* 0x00000040 */
#define VOP_DSC_SYS_CTRL1_DSC_FULL_ICH_ERR_PRECISION_SHIFT (7U)
#define VOP_DSC_SYS_CTRL1_DSC_FULL_ICH_ERR_PRECISION_MASK  (0x1U << VOP_DSC_SYS_CTRL1_DSC_FULL_ICH_ERR_PRECISION_SHIFT) /* 0x00000080 */
#define VOP_DSC_SYS_CTRL1_DSC_INT_CLR_TRIG_SHIFT           (8U)
#define VOP_DSC_SYS_CTRL1_DSC_INT_CLR_TRIG_MASK            (0x1U << VOP_DSC_SYS_CTRL1_DSC_INT_CLR_TRIG_SHIFT)           /* 0x00000100 */
#define VOP_DSC_SYS_CTRL1_WORD_SWAP_SHIFT                  (12U)
#define VOP_DSC_SYS_CTRL1_WORD_SWAP_MASK                   (0x1U << VOP_DSC_SYS_CTRL1_WORD_SWAP_SHIFT)                  /* 0x00001000 */
#define VOP_DSC_SYS_CTRL1_HI_LO_BYTE_SWAP_SHIFT            (13U)
#define VOP_DSC_SYS_CTRL1_HI_LO_BYTE_SWAP_MASK             (0x1U << VOP_DSC_SYS_CTRL1_HI_LO_BYTE_SWAP_SHIFT)            /* 0x00002000 */
#define VOP_DSC_SYS_CTRL1_DSC_OUTPUT_DELAY_PERI_SHIFT      (16U)
#define VOP_DSC_SYS_CTRL1_DSC_OUTPUT_DELAY_PERI_MASK       (0xFFFFU << VOP_DSC_SYS_CTRL1_DSC_OUTPUT_DELAY_PERI_SHIFT)   /* 0xFFFF0000 */
/* DSC_SYS_CTRL2 */
#define VOP_DSC_SYS_CTRL2_OFFSET                           (0xA08U)
#define VOP_DSC_SYS_CTRL2_DSC_INITIAL_LINES_SHIFT          (0U)
#define VOP_DSC_SYS_CTRL2_DSC_INITIAL_LINES_MASK           (0xFFU << VOP_DSC_SYS_CTRL2_DSC_INITIAL_LINES_SHIFT)         /* 0x000000FF */
#define VOP_DSC_SYS_CTRL2_DSC_OUTPUT_DELAY_EN_SHIFT        (8U)
#define VOP_DSC_SYS_CTRL2_DSC_OUTPUT_DELAY_EN_MASK         (0x1U << VOP_DSC_SYS_CTRL2_DSC_OUTPUT_DELAY_EN_SHIFT)        /* 0x00000100 */
#define VOP_DSC_SYS_CTRL2_DSC_OUTPUT_DELAY_INIT_SHIFT      (16U)
#define VOP_DSC_SYS_CTRL2_DSC_OUTPUT_DELAY_INIT_MASK       (0xFFFFU << VOP_DSC_SYS_CTRL2_DSC_OUTPUT_DELAY_INIT_SHIFT)   /* 0xFFFF0000 */
/* DSC_SYS_CTRL3 */
#define VOP_DSC_SYS_CTRL3_OFFSET                           (0xA0CU)
#define VOP_DSC_SYS_CTRL3_DSC_OB_MAX_ADDR_SHIFT            (0U)
#define VOP_DSC_SYS_CTRL3_DSC_OB_MAX_ADDR_MASK             (0x3FFFU << VOP_DSC_SYS_CTRL3_DSC_OB_MAX_ADDR_SHIFT)         /* 0x00003FFF */
/* DSC_CFG0 */
#define VOP_DSC_CFG0_OFFSET                                (0xA10U)
#define VOP_DSC_CFG0_RANGE_BPG_OFFSET0_SHIFT               (0U)
#define VOP_DSC_CFG0_RANGE_BPG_OFFSET0_MASK                (0x3FU << VOP_DSC_CFG0_RANGE_BPG_OFFSET0_SHIFT)              /* 0x0000003F */
#define VOP_DSC_CFG0_RANGE_BPG_OFFSET1_SHIFT               (6U)
#define VOP_DSC_CFG0_RANGE_BPG_OFFSET1_MASK                (0x3FU << VOP_DSC_CFG0_RANGE_BPG_OFFSET1_SHIFT)              /* 0x00000FC0 */
#define VOP_DSC_CFG0_RANGE_BPG_OFFSET2_SHIFT               (12U)
#define VOP_DSC_CFG0_RANGE_BPG_OFFSET2_MASK                (0x3FU << VOP_DSC_CFG0_RANGE_BPG_OFFSET2_SHIFT)              /* 0x0003F000 */
#define VOP_DSC_CFG0_RANGE_BPG_OFFSET3_SHIFT               (18U)
#define VOP_DSC_CFG0_RANGE_BPG_OFFSET3_MASK                (0x3FU << VOP_DSC_CFG0_RANGE_BPG_OFFSET3_SHIFT)              /* 0x00FC0000 */
#define VOP_DSC_CFG0_RANGE_BPG_OFFSET4_SHIFT               (24U)
#define VOP_DSC_CFG0_RANGE_BPG_OFFSET4_MASK                (0x3FU << VOP_DSC_CFG0_RANGE_BPG_OFFSET4_SHIFT)              /* 0x3F000000 */
#define VOP_DSC_CFG0_RANGE_BPG_OFFSET5_LO_SHIFT            (30U)
#define VOP_DSC_CFG0_RANGE_BPG_OFFSET5_LO_MASK             (0x3U << VOP_DSC_CFG0_RANGE_BPG_OFFSET5_LO_SHIFT)            /* 0xC0000000 */
/* DSC_CFG1 */
#define VOP_DSC_CFG1_OFFSET                                (0xA14U)
#define VOP_DSC_CFG1_RANGE_BPG_OFFSET5_HI_SHIFT            (0U)
#define VOP_DSC_CFG1_RANGE_BPG_OFFSET5_HI_MASK             (0xFU << VOP_DSC_CFG1_RANGE_BPG_OFFSET5_HI_SHIFT)            /* 0x0000000F */
#define VOP_DSC_CFG1_RANGE_BPG_OFFSET6_SHIFT               (4U)
#define VOP_DSC_CFG1_RANGE_BPG_OFFSET6_MASK                (0x3FU << VOP_DSC_CFG1_RANGE_BPG_OFFSET6_SHIFT)              /* 0x000003F0 */
#define VOP_DSC_CFG1_RANGE_BPG_OFFSET7_SHIFT               (10U)
#define VOP_DSC_CFG1_RANGE_BPG_OFFSET7_MASK                (0x3FU << VOP_DSC_CFG1_RANGE_BPG_OFFSET7_SHIFT)              /* 0x0000FC00 */
#define VOP_DSC_CFG1_RANGE_BPG_OFFSET8_SHIFT               (16U)
#define VOP_DSC_CFG1_RANGE_BPG_OFFSET8_MASK                (0x3FU << VOP_DSC_CFG1_RANGE_BPG_OFFSET8_SHIFT)              /* 0x003F0000 */
#define VOP_DSC_CFG1_RANGE_BPG_OFFSET9_SHIFT               (22U)
#define VOP_DSC_CFG1_RANGE_BPG_OFFSET9_MASK                (0x3FU << VOP_DSC_CFG1_RANGE_BPG_OFFSET9_SHIFT)              /* 0x0FC00000 */
#define VOP_DSC_CFG1_RANGE_BPG_OFFSET10_LO_SHIFT           (28U)
#define VOP_DSC_CFG1_RANGE_BPG_OFFSET10_LO_MASK            (0xFU << VOP_DSC_CFG1_RANGE_BPG_OFFSET10_LO_SHIFT)           /* 0xF0000000 */
/* DSC_CFG2 */
#define VOP_DSC_CFG2_OFFSET                                (0xA18U)
#define VOP_DSC_CFG2_RANGE_BPG_OFFSET10_HI_SHIFT           (0U)
#define VOP_DSC_CFG2_RANGE_BPG_OFFSET10_HI_MASK            (0x3U << VOP_DSC_CFG2_RANGE_BPG_OFFSET10_HI_SHIFT)           /* 0x00000003 */
#define VOP_DSC_CFG2_RANGE_BPG_OFFSET11_SHIFT              (2U)
#define VOP_DSC_CFG2_RANGE_BPG_OFFSET11_MASK               (0x3FU << VOP_DSC_CFG2_RANGE_BPG_OFFSET11_SHIFT)             /* 0x000000FC */
#define VOP_DSC_CFG2_RANGE_BPG_OFFSET12_SHIFT              (8U)
#define VOP_DSC_CFG2_RANGE_BPG_OFFSET12_MASK               (0x3FU << VOP_DSC_CFG2_RANGE_BPG_OFFSET12_SHIFT)             /* 0x00003F00 */
#define VOP_DSC_CFG2_RANGE_BPG_OFFSET13_SHIFT              (14U)
#define VOP_DSC_CFG2_RANGE_BPG_OFFSET13_MASK               (0x3FU << VOP_DSC_CFG2_RANGE_BPG_OFFSET13_SHIFT)             /* 0x000FC000 */
#define VOP_DSC_CFG2_RANGE_BPG_OFFSET14_SHIFT              (20U)
#define VOP_DSC_CFG2_RANGE_BPG_OFFSET14_MASK               (0x3FU << VOP_DSC_CFG2_RANGE_BPG_OFFSET14_SHIFT)             /* 0x03F00000 */
#define VOP_DSC_CFG2_RANGE_MAX_QP0_SHIFT                   (26U)
#define VOP_DSC_CFG2_RANGE_MAX_QP0_MASK                    (0x1FU << VOP_DSC_CFG2_RANGE_MAX_QP0_SHIFT)                  /* 0x7C000000 */
#define VOP_DSC_CFG2_RANGE_MAX_QP1_LO_SHIFT                (31U)
#define VOP_DSC_CFG2_RANGE_MAX_QP1_LO_MASK                 (0x1U << VOP_DSC_CFG2_RANGE_MAX_QP1_LO_SHIFT)                /* 0x80000000 */
/* DSC_CFG3 */
#define VOP_DSC_CFG3_OFFSET                                (0xA1CU)
#define VOP_DSC_CFG3_RANGE_MAX_QP1_HI_SHIFT                (0U)
#define VOP_DSC_CFG3_RANGE_MAX_QP1_HI_MASK                 (0xFU << VOP_DSC_CFG3_RANGE_MAX_QP1_HI_SHIFT)                /* 0x0000000F */
#define VOP_DSC_CFG3_RANGE_MAX_QP2_SHIFT                   (4U)
#define VOP_DSC_CFG3_RANGE_MAX_QP2_MASK                    (0x1FU << VOP_DSC_CFG3_RANGE_MAX_QP2_SHIFT)                  /* 0x000001F0 */
#define VOP_DSC_CFG3_RANGE_MAX_QP3_SHIFT                   (9U)
#define VOP_DSC_CFG3_RANGE_MAX_QP3_MASK                    (0x1FU << VOP_DSC_CFG3_RANGE_MAX_QP3_SHIFT)                  /* 0x00003E00 */
#define VOP_DSC_CFG3_RANGE_MAX_QP4_SHIFT                   (14U)
#define VOP_DSC_CFG3_RANGE_MAX_QP4_MASK                    (0x1FU << VOP_DSC_CFG3_RANGE_MAX_QP4_SHIFT)                  /* 0x0007C000 */
#define VOP_DSC_CFG3_RANGE_MAX_QP5_SHIFT                   (19U)
#define VOP_DSC_CFG3_RANGE_MAX_QP5_MASK                    (0x1FU << VOP_DSC_CFG3_RANGE_MAX_QP5_SHIFT)                  /* 0x00F80000 */
#define VOP_DSC_CFG3_RANGE_MAX_QP6_SHIFT                   (24U)
#define VOP_DSC_CFG3_RANGE_MAX_QP6_MASK                    (0x1FU << VOP_DSC_CFG3_RANGE_MAX_QP6_SHIFT)                  /* 0x1F000000 */
#define VOP_DSC_CFG3_RANGE_MAX_QP7_LO_SHIFT                (29U)
#define VOP_DSC_CFG3_RANGE_MAX_QP7_LO_MASK                 (0x7U << VOP_DSC_CFG3_RANGE_MAX_QP7_LO_SHIFT)                /* 0xE0000000 */
/* DSC_CFG4 */
#define VOP_DSC_CFG4_OFFSET                                (0xA20U)
#define VOP_DSC_CFG4_RANGE_MAX_QP7_HI_SHIFT                (0U)
#define VOP_DSC_CFG4_RANGE_MAX_QP7_HI_MASK                 (0x3U << VOP_DSC_CFG4_RANGE_MAX_QP7_HI_SHIFT)                /* 0x00000003 */
#define VOP_DSC_CFG4_RANGE_MAX_QP8_SHIFT                   (2U)
#define VOP_DSC_CFG4_RANGE_MAX_QP8_MASK                    (0x1FU << VOP_DSC_CFG4_RANGE_MAX_QP8_SHIFT)                  /* 0x0000007C */
#define VOP_DSC_CFG4_RANGE_MAX_QP9_SHIFT                   (7U)
#define VOP_DSC_CFG4_RANGE_MAX_QP9_MASK                    (0x1FU << VOP_DSC_CFG4_RANGE_MAX_QP9_SHIFT)                  /* 0x00000F80 */
#define VOP_DSC_CFG4_RANGE_MAX_QP10_SHIFT                  (12U)
#define VOP_DSC_CFG4_RANGE_MAX_QP10_MASK                   (0x1FU << VOP_DSC_CFG4_RANGE_MAX_QP10_SHIFT)                 /* 0x0001F000 */
#define VOP_DSC_CFG4_RANGE_MAX_QP11_SHIFT                  (17U)
#define VOP_DSC_CFG4_RANGE_MAX_QP11_MASK                   (0x1FU << VOP_DSC_CFG4_RANGE_MAX_QP11_SHIFT)                 /* 0x003E0000 */
#define VOP_DSC_CFG4_RANGE_MAX_QP12_SHIFT                  (22U)
#define VOP_DSC_CFG4_RANGE_MAX_QP12_MASK                   (0x1FU << VOP_DSC_CFG4_RANGE_MAX_QP12_SHIFT)                 /* 0x07C00000 */
#define VOP_DSC_CFG4_RANGE_MAX_QP13_SHIFT                  (27U)
#define VOP_DSC_CFG4_RANGE_MAX_QP13_MASK                   (0x1FU << VOP_DSC_CFG4_RANGE_MAX_QP13_SHIFT)                 /* 0xF8000000 */
/* DSC_CFG5 */
#define VOP_DSC_CFG5_OFFSET                                (0xA24U)
#define VOP_DSC_CFG5_RANGE_MAX_QP14_SHIFT                  (0U)
#define VOP_DSC_CFG5_RANGE_MAX_QP14_MASK                   (0x1FU << VOP_DSC_CFG5_RANGE_MAX_QP14_SHIFT)                 /* 0x0000001F */
#define VOP_DSC_CFG5_RANGE_MIN_QP0_SHIFT                   (5U)
#define VOP_DSC_CFG5_RANGE_MIN_QP0_MASK                    (0x1FU << VOP_DSC_CFG5_RANGE_MIN_QP0_SHIFT)                  /* 0x000003E0 */
#define VOP_DSC_CFG5_RANGE_MIN_QP1_SHIFT                   (10U)
#define VOP_DSC_CFG5_RANGE_MIN_QP1_MASK                    (0x1FU << VOP_DSC_CFG5_RANGE_MIN_QP1_SHIFT)                  /* 0x00007C00 */
#define VOP_DSC_CFG5_RANGE_MIN_QP2_SHIFT                   (15U)
#define VOP_DSC_CFG5_RANGE_MIN_QP2_MASK                    (0x1FU << VOP_DSC_CFG5_RANGE_MIN_QP2_SHIFT)                  /* 0x000F8000 */
#define VOP_DSC_CFG5_RANGE_MIN_QP3_SHIFT                   (20U)
#define VOP_DSC_CFG5_RANGE_MIN_QP3_MASK                    (0x1FU << VOP_DSC_CFG5_RANGE_MIN_QP3_SHIFT)                  /* 0x01F00000 */
#define VOP_DSC_CFG5_RANGE_MIN_QP4_SHIFT                   (25U)
#define VOP_DSC_CFG5_RANGE_MIN_QP4_MASK                    (0x1FU << VOP_DSC_CFG5_RANGE_MIN_QP4_SHIFT)                  /* 0x3E000000 */
#define VOP_DSC_CFG5_RANGE_MIN_QP5_LO_SHIFT                (30U)
#define VOP_DSC_CFG5_RANGE_MIN_QP5_LO_MASK                 (0x3U << VOP_DSC_CFG5_RANGE_MIN_QP5_LO_SHIFT)                /* 0xC0000000 */
/* DSC_CFG6 */
#define VOP_DSC_CFG6_OFFSET                                (0xA28U)
#define VOP_DSC_CFG6_RANGE_MIN_QP5_HI_SHIFT                (0U)
#define VOP_DSC_CFG6_RANGE_MIN_QP5_HI_MASK                 (0x7U << VOP_DSC_CFG6_RANGE_MIN_QP5_HI_SHIFT)                /* 0x00000007 */
#define VOP_DSC_CFG6_RANGE_MIN_QP6_SHIFT                   (3U)
#define VOP_DSC_CFG6_RANGE_MIN_QP6_MASK                    (0x1FU << VOP_DSC_CFG6_RANGE_MIN_QP6_SHIFT)                  /* 0x000000F8 */
#define VOP_DSC_CFG6_RANGE_MIN_QP7_SHIFT                   (8U)
#define VOP_DSC_CFG6_RANGE_MIN_QP7_MASK                    (0x1FU << VOP_DSC_CFG6_RANGE_MIN_QP7_SHIFT)                  /* 0x00001F00 */
#define VOP_DSC_CFG6_RANGE_MIN_QP8_SHIFT                   (13U)
#define VOP_DSC_CFG6_RANGE_MIN_QP8_MASK                    (0x1FU << VOP_DSC_CFG6_RANGE_MIN_QP8_SHIFT)                  /* 0x0003E000 */
#define VOP_DSC_CFG6_RANGE_MIN_QP9_SHIFT                   (18U)
#define VOP_DSC_CFG6_RANGE_MIN_QP9_MASK                    (0x1FU << VOP_DSC_CFG6_RANGE_MIN_QP9_SHIFT)                  /* 0x007C0000 */
#define VOP_DSC_CFG6_RANGE_MIN_QP10_SHIFT                  (23U)
#define VOP_DSC_CFG6_RANGE_MIN_QP10_MASK                   (0x1FU << VOP_DSC_CFG6_RANGE_MIN_QP10_SHIFT)                 /* 0x0F800000 */
#define VOP_DSC_CFG6_RANGE_MIN_QP11_LO_SHIFT               (28U)
#define VOP_DSC_CFG6_RANGE_MIN_QP11_LO_MASK                (0xFU << VOP_DSC_CFG6_RANGE_MIN_QP11_LO_SHIFT)               /* 0xF0000000 */
/* DSC_CFG7 */
#define VOP_DSC_CFG7_OFFSET                                (0xA2CU)
#define VOP_DSC_CFG7_RANGE_MIN_QP11_HI_SHIFT               (0U)
#define VOP_DSC_CFG7_RANGE_MIN_QP11_HI_MASK                (0x1U << VOP_DSC_CFG7_RANGE_MIN_QP11_HI_SHIFT)               /* 0x00000001 */
#define VOP_DSC_CFG7_RANGE_MIN_QP12_SHIFT                  (1U)
#define VOP_DSC_CFG7_RANGE_MIN_QP12_MASK                   (0x1FU << VOP_DSC_CFG7_RANGE_MIN_QP12_SHIFT)                 /* 0x0000003E */
#define VOP_DSC_CFG7_RANGE_MIN_QP13_SHIFT                  (6U)
#define VOP_DSC_CFG7_RANGE_MIN_QP13_MASK                   (0x1FU << VOP_DSC_CFG7_RANGE_MIN_QP13_SHIFT)                 /* 0x000007C0 */
#define VOP_DSC_CFG7_RANGE_MIN_QP14_SHIFT                  (11U)
#define VOP_DSC_CFG7_RANGE_MIN_QP14_MASK                   (0x1FU << VOP_DSC_CFG7_RANGE_MIN_QP14_SHIFT)                 /* 0x0000F800 */
#define VOP_DSC_CFG7_RC_BUF_THRESH0_SHIFT                  (16U)
#define VOP_DSC_CFG7_RC_BUF_THRESH0_MASK                   (0xFFU << VOP_DSC_CFG7_RC_BUF_THRESH0_SHIFT)                 /* 0x00FF0000 */
#define VOP_DSC_CFG7_RC_BUF_THRESH1_SHIFT                  (24U)
#define VOP_DSC_CFG7_RC_BUF_THRESH1_MASK                   (0xFFU << VOP_DSC_CFG7_RC_BUF_THRESH1_SHIFT)                 /* 0xFF000000 */
/* DSC_CFG8 */
#define VOP_DSC_CFG8_OFFSET                                (0xA30U)
#define VOP_DSC_CFG8_RC_BUF_THRESH2_SHIFT                  (0U)
#define VOP_DSC_CFG8_RC_BUF_THRESH2_MASK                   (0xFFU << VOP_DSC_CFG8_RC_BUF_THRESH2_SHIFT)                 /* 0x000000FF */
#define VOP_DSC_CFG8_RC_BUF_THRESH3_SHIFT                  (8U)
#define VOP_DSC_CFG8_RC_BUF_THRESH3_MASK                   (0xFFU << VOP_DSC_CFG8_RC_BUF_THRESH3_SHIFT)                 /* 0x0000FF00 */
#define VOP_DSC_CFG8_RC_BUF_THRESH4_SHIFT                  (16U)
#define VOP_DSC_CFG8_RC_BUF_THRESH4_MASK                   (0xFFU << VOP_DSC_CFG8_RC_BUF_THRESH4_SHIFT)                 /* 0x00FF0000 */
#define VOP_DSC_CFG8_RC_BUF_THRESH5_SHIFT                  (24U)
#define VOP_DSC_CFG8_RC_BUF_THRESH5_MASK                   (0xFFU << VOP_DSC_CFG8_RC_BUF_THRESH5_SHIFT)                 /* 0xFF000000 */
/* DSC_CFG9 */
#define VOP_DSC_CFG9_OFFSET                                (0xA34U)
#define VOP_DSC_CFG9_RC_BUF_THRESH6_SHIFT                  (0U)
#define VOP_DSC_CFG9_RC_BUF_THRESH6_MASK                   (0xFFU << VOP_DSC_CFG9_RC_BUF_THRESH6_SHIFT)                 /* 0x000000FF */
#define VOP_DSC_CFG9_RC_BUF_THRESH7_SHIFT                  (8U)
#define VOP_DSC_CFG9_RC_BUF_THRESH7_MASK                   (0xFFU << VOP_DSC_CFG9_RC_BUF_THRESH7_SHIFT)                 /* 0x0000FF00 */
#define VOP_DSC_CFG9_RC_BUF_THRESH8_SHIFT                  (16U)
#define VOP_DSC_CFG9_RC_BUF_THRESH8_MASK                   (0xFFU << VOP_DSC_CFG9_RC_BUF_THRESH8_SHIFT)                 /* 0x00FF0000 */
#define VOP_DSC_CFG9_RC_BUF_THRESH9_SHIFT                  (24U)
#define VOP_DSC_CFG9_RC_BUF_THRESH9_MASK                   (0xFFU << VOP_DSC_CFG9_RC_BUF_THRESH9_SHIFT)                 /* 0xFF000000 */
/* DSC_CFG10 */
#define VOP_DSC_CFG10_OFFSET                               (0xA38U)
#define VOP_DSC_CFG10_RC_BUF_THRESH10_SHIFT                (0U)
#define VOP_DSC_CFG10_RC_BUF_THRESH10_MASK                 (0xFFU << VOP_DSC_CFG10_RC_BUF_THRESH10_SHIFT)               /* 0x000000FF */
#define VOP_DSC_CFG10_RC_BUF_THRESH11_SHIFT                (8U)
#define VOP_DSC_CFG10_RC_BUF_THRESH11_MASK                 (0xFFU << VOP_DSC_CFG10_RC_BUF_THRESH11_SHIFT)               /* 0x0000FF00 */
#define VOP_DSC_CFG10_RC_BUF_THRESH12_SHIFT                (16U)
#define VOP_DSC_CFG10_RC_BUF_THRESH12_MASK                 (0xFFU << VOP_DSC_CFG10_RC_BUF_THRESH12_SHIFT)               /* 0x00FF0000 */
#define VOP_DSC_CFG10_RC_BUF_THRESH13_SHIFT                (24U)
#define VOP_DSC_CFG10_RC_BUF_THRESH13_MASK                 (0xFFU << VOP_DSC_CFG10_RC_BUF_THRESH13_SHIFT)               /* 0xFF000000 */
/* DSC_CFG11 */
#define VOP_DSC_CFG11_OFFSET                               (0xA3CU)
#define VOP_DSC_CFG11_RC_TGT_OFFSET_LO_SHIFT               (0U)
#define VOP_DSC_CFG11_RC_TGT_OFFSET_LO_MASK                (0xFU << VOP_DSC_CFG11_RC_TGT_OFFSET_LO_SHIFT)               /* 0x0000000F */
#define VOP_DSC_CFG11_RC_TGT_OFFSET_HI_SHIFT               (4U)
#define VOP_DSC_CFG11_RC_TGT_OFFSET_HI_MASK                (0xFU << VOP_DSC_CFG11_RC_TGT_OFFSET_HI_SHIFT)               /* 0x000000F0 */
#define VOP_DSC_CFG11_RC_QUANT_INCR_LIMIT1_SHIFT           (8U)
#define VOP_DSC_CFG11_RC_QUANT_INCR_LIMIT1_MASK            (0x1FU << VOP_DSC_CFG11_RC_QUANT_INCR_LIMIT1_SHIFT)          /* 0x00001F00 */
#define VOP_DSC_CFG11_RC_QUANT_INCR_LIMIT0_SHIFT           (13U)
#define VOP_DSC_CFG11_RC_QUANT_INCR_LIMIT0_MASK            (0x1FU << VOP_DSC_CFG11_RC_QUANT_INCR_LIMIT0_SHIFT)          /* 0x0003E000 */
#define VOP_DSC_CFG11_RC_EDGE_FACTOR_SHIFT                 (18U)
#define VOP_DSC_CFG11_RC_EDGE_FACTOR_MASK                  (0xFU << VOP_DSC_CFG11_RC_EDGE_FACTOR_SHIFT)                 /* 0x003C0000 */
#define VOP_DSC_CFG11_RC_MODEL_SIZE_LO_SHIFT               (22U)
#define VOP_DSC_CFG11_RC_MODEL_SIZE_LO_MASK                (0x3FFU << VOP_DSC_CFG11_RC_MODEL_SIZE_LO_SHIFT)             /* 0xFFC00000 */
/* DSC_CFG12 */
#define VOP_DSC_CFG12_OFFSET                               (0xA40U)
#define VOP_DSC_CFG12_RC_MODEL_SIZE_HI_SHIFT               (0U)
#define VOP_DSC_CFG12_RC_MODEL_SIZE_HI_MASK                (0x3FU << VOP_DSC_CFG12_RC_MODEL_SIZE_HI_SHIFT)              /* 0x0000003F */
#define VOP_DSC_CFG12_FLATNESS_DET_THRESH_SHIFT            (6U)
#define VOP_DSC_CFG12_FLATNESS_DET_THRESH_MASK             (0xFFU << VOP_DSC_CFG12_FLATNESS_DET_THRESH_SHIFT)           /* 0x00003FC0 */
#define VOP_DSC_CFG12_FLATNESS_MAX_QP_SHIFT                (14U)
#define VOP_DSC_CFG12_FLATNESS_MAX_QP_MASK                 (0x1FU << VOP_DSC_CFG12_FLATNESS_MAX_QP_SHIFT)               /* 0x0007C000 */
#define VOP_DSC_CFG12_FLATNESS_MIN_QP_SHIFT                (19U)
#define VOP_DSC_CFG12_FLATNESS_MIN_QP_MASK                 (0x1FU << VOP_DSC_CFG12_FLATNESS_MIN_QP_SHIFT)               /* 0x00F80000 */
#define VOP_DSC_CFG12_FINAL_OFFSET_LO_SHIFT                (24U)
#define VOP_DSC_CFG12_FINAL_OFFSET_LO_MASK                 (0xFFU << VOP_DSC_CFG12_FINAL_OFFSET_LO_SHIFT)               /* 0xFF000000 */
/* DSC_CFG13 */
#define VOP_DSC_CFG13_OFFSET                               (0xA44U)
#define VOP_DSC_CFG13_FINAL_OFFSET_HI_SHIFT                (0U)
#define VOP_DSC_CFG13_FINAL_OFFSET_HI_MASK                 (0xFFU << VOP_DSC_CFG13_FINAL_OFFSET_HI_SHIFT)               /* 0x000000FF */
#define VOP_DSC_CFG13_INITIAL_OFFSET_SHIFT                 (8U)
#define VOP_DSC_CFG13_INITIAL_OFFSET_MASK                  (0xFFFFU << VOP_DSC_CFG13_INITIAL_OFFSET_SHIFT)              /* 0x00FFFF00 */
#define VOP_DSC_CFG13_SLICE_BPG_OFFSET_LO_SHIFT            (24U)
#define VOP_DSC_CFG13_SLICE_BPG_OFFSET_LO_MASK             (0xFFU << VOP_DSC_CFG13_SLICE_BPG_OFFSET_LO_SHIFT)           /* 0xFF000000 */
/* DSC_CFG14 */
#define VOP_DSC_CFG14_OFFSET                               (0xA48U)
#define VOP_DSC_CFG14_SLICE_BPG_OFFSET_HI_SHIFT            (0U)
#define VOP_DSC_CFG14_SLICE_BPG_OFFSET_HI_MASK             (0xFFU << VOP_DSC_CFG14_SLICE_BPG_OFFSET_HI_SHIFT)           /* 0x000000FF */
#define VOP_DSC_CFG14_NFL_BPG_OFFSET_SHIFT                 (8U)
#define VOP_DSC_CFG14_NFL_BPG_OFFSET_MASK                  (0xFFFFU << VOP_DSC_CFG14_NFL_BPG_OFFSET_SHIFT)              /* 0x00FFFF00 */
#define VOP_DSC_CFG14_FIRST_LINE_BPG_OFFSET_SHIFT          (24U)
#define VOP_DSC_CFG14_FIRST_LINE_BPG_OFFSET_MASK           (0x1FU << VOP_DSC_CFG14_FIRST_LINE_BPG_OFFSET_SHIFT)         /* 0x1F000000 */
#define VOP_DSC_CFG14_SCALE_DECREMENT_INTERVAL_LO_SHIFT    (29U)
#define VOP_DSC_CFG14_SCALE_DECREMENT_INTERVAL_LO_MASK     (0x7U << VOP_DSC_CFG14_SCALE_DECREMENT_INTERVAL_LO_SHIFT)    /* 0xE0000000 */
/* DSC_CFG15 */
#define VOP_DSC_CFG15_OFFSET                               (0xA4CU)
#define VOP_DSC_CFG15_SCALE_DECREMENT_INTERVAL_HI_SHIFT    (0U)
#define VOP_DSC_CFG15_SCALE_DECREMENT_INTERVAL_HI_MASK     (0x1FFU << VOP_DSC_CFG15_SCALE_DECREMENT_INTERVAL_HI_SHIFT)  /* 0x000001FF */
#define VOP_DSC_CFG15_SCALE_INCREMENT_INTERVAL_SHIFT       (9U)
#define VOP_DSC_CFG15_SCALE_INCREMENT_INTERVAL_MASK        (0xFFFFU << VOP_DSC_CFG15_SCALE_INCREMENT_INTERVAL_SHIFT)    /* 0x01FFFE00 */
#define VOP_DSC_CFG15_INITIAL_SCALE_VALUE_SHIFT            (25U)
#define VOP_DSC_CFG15_INITIAL_SCALE_VALUE_MASK             (0x3FU << VOP_DSC_CFG15_INITIAL_SCALE_VALUE_SHIFT)           /* 0x7E000000 */
#define VOP_DSC_CFG15_INITIAL_DEC_DELAY_LO_SHIFT           (31U)
#define VOP_DSC_CFG15_INITIAL_DEC_DELAY_LO_MASK            (0x1U << VOP_DSC_CFG15_INITIAL_DEC_DELAY_LO_SHIFT)           /* 0x80000000 */
/* DSC_CFG16 */
#define VOP_DSC_CFG16_OFFSET                               (0xA50U)
#define VOP_DSC_CFG16_INITIAL_DEC_DELAY_HI_SHIFT           (0U)
#define VOP_DSC_CFG16_INITIAL_DEC_DELAY_HI_MASK            (0x7FFFU << VOP_DSC_CFG16_INITIAL_DEC_DELAY_HI_SHIFT)        /* 0x00007FFF */
#define VOP_DSC_CFG16_INITIAL_XMIT_DELAY_SHIFT             (15U)
#define VOP_DSC_CFG16_INITIAL_XMIT_DELAY_MASK              (0x3FFU << VOP_DSC_CFG16_INITIAL_XMIT_DELAY_SHIFT)           /* 0x01FF8000 */
#define VOP_DSC_CFG16_CHUNK_SIZE_LO_SHIFT                  (25U)
#define VOP_DSC_CFG16_CHUNK_SIZE_LO_MASK                   (0x7FU << VOP_DSC_CFG16_CHUNK_SIZE_LO_SHIFT)                 /* 0xFE000000 */
/* DSC_CFG17 */
#define VOP_DSC_CFG17_OFFSET                               (0xA54U)
#define VOP_DSC_CFG17_CHUNK_SIZE_HI_SHIFT                  (0U)
#define VOP_DSC_CFG17_CHUNK_SIZE_HI_MASK                   (0x1FFU << VOP_DSC_CFG17_CHUNK_SIZE_HI_SHIFT)                /* 0x000001FF */
#define VOP_DSC_CFG17_SLICE_HEIGHT_SHIFT                   (9U)
#define VOP_DSC_CFG17_SLICE_HEIGHT_MASK                    (0xFFFFU << VOP_DSC_CFG17_SLICE_HEIGHT_SHIFT)                /* 0x01FFFE00 */
#define VOP_DSC_CFG17_SLICE_WIDTH_LO_SHIFT                 (25U)
#define VOP_DSC_CFG17_SLICE_WIDTH_LO_MASK                  (0x7FU << VOP_DSC_CFG17_SLICE_WIDTH_LO_SHIFT)                /* 0xFE000000 */
/* DSC_CFG18 */
#define VOP_DSC_CFG18_OFFSET                               (0xA58U)
#define VOP_DSC_CFG18_SLICE_WIDTH_HI_SHIFT                 (0U)
#define VOP_DSC_CFG18_SLICE_WIDTH_HI_MASK                  (0x1FFU << VOP_DSC_CFG18_SLICE_WIDTH_HI_SHIFT)               /* 0x000001FF */
#define VOP_DSC_CFG18_PICTURE_HEIGHT_SHIFT                 (9U)
#define VOP_DSC_CFG18_PICTURE_HEIGHT_MASK                  (0xFFFFU << VOP_DSC_CFG18_PICTURE_HEIGHT_SHIFT)              /* 0x01FFFE00 */
#define VOP_DSC_CFG18_PICTURE_WIDTH_LO_SHIFT               (25U)
#define VOP_DSC_CFG18_PICTURE_WIDTH_LO_MASK                (0x7FU << VOP_DSC_CFG18_PICTURE_WIDTH_LO_SHIFT)              /* 0xFE000000 */
/* DSC_CFG19 */
#define VOP_DSC_CFG19_OFFSET                               (0xA5CU)
#define VOP_DSC_CFG19_PICTURE_WIDTH_HI_SHIFT               (0U)
#define VOP_DSC_CFG19_PICTURE_WIDTH_HI_MASK                (0x1FFU << VOP_DSC_CFG19_PICTURE_WIDTH_HI_SHIFT)             /* 0x000001FF */
#define VOP_DSC_CFG19_DSC_VERSION_MINOR_SHIFT              (9U)
#define VOP_DSC_CFG19_DSC_VERSION_MINOR_MASK               (0xFU << VOP_DSC_CFG19_DSC_VERSION_MINOR_SHIFT)              /* 0x00001E00 */
#define VOP_DSC_CFG19_BITS_PER_PIXEL_SHIFT                 (13U)
#define VOP_DSC_CFG19_BITS_PER_PIXEL_MASK                  (0x3FFU << VOP_DSC_CFG19_BITS_PER_PIXEL_SHIFT)               /* 0x007FE000 */
#define VOP_DSC_CFG19_BLOCK_PRED_ENABLE_SHIFT              (23U)
#define VOP_DSC_CFG19_BLOCK_PRED_ENABLE_MASK               (0x1U << VOP_DSC_CFG19_BLOCK_PRED_ENABLE_SHIFT)              /* 0x00800000 */
#define VOP_DSC_CFG19_LINEBUF_DEPTH_SHIFT                  (24U)
#define VOP_DSC_CFG19_LINEBUF_DEPTH_MASK                   (0xFU << VOP_DSC_CFG19_LINEBUF_DEPTH_SHIFT)                  /* 0x0F000000 */
#define VOP_DSC_CFG19_ENABLE_422_SHIFT                     (28U)
#define VOP_DSC_CFG19_ENABLE_422_MASK                      (0x1U << VOP_DSC_CFG19_ENABLE_422_SHIFT)                     /* 0x10000000 */
#define VOP_DSC_CFG19_CONVERT_RGB_SHIFT                    (29U)
#define VOP_DSC_CFG19_CONVERT_RGB_MASK                     (0x1U << VOP_DSC_CFG19_CONVERT_RGB_SHIFT)                    /* 0x20000000 */
#define VOP_DSC_CFG19_BITS_PER_COMPONENT_LO_SHIFT          (30U)
#define VOP_DSC_CFG19_BITS_PER_COMPONENT_LO_MASK           (0x3U << VOP_DSC_CFG19_BITS_PER_COMPONENT_LO_SHIFT)          /* 0xC0000000 */
/* DSC_CFG20 */
#define VOP_DSC_CFG20_OFFSET                               (0xA60U)
#define VOP_DSC_CFG20_BITS_PER_COMPONENT_HI_SHIFT          (0U)
#define VOP_DSC_CFG20_BITS_PER_COMPONENT_HI_MASK           (0x3U << VOP_DSC_CFG20_BITS_PER_COMPONENT_HI_SHIFT)          /* 0x00000003 */
/* DSC_INT_EN */
#define VOP_DSC_INT_EN_OFFSET                              (0xA70U)
#define VOP_DSC_INT_EN_OUT_BUFF_FULL_CONTEXT_1_SHIFT       (0U)
#define VOP_DSC_INT_EN_OUT_BUFF_FULL_CONTEXT_1_MASK        (0x1U << VOP_DSC_INT_EN_OUT_BUFF_FULL_CONTEXT_1_SHIFT)       /* 0x00000001 */
#define VOP_DSC_INT_EN_OUT_BUFF_FULL_CONTEXT_0_SHIFT       (1U)
#define VOP_DSC_INT_EN_OUT_BUFF_FULL_CONTEXT_0_MASK        (0x1U << VOP_DSC_INT_EN_OUT_BUFF_FULL_CONTEXT_0_SHIFT)       /* 0x00000002 */
#define VOP_DSC_INT_EN_OUT_BUFF_EMPTY_CONTEXT_1_SHIFT      (2U)
#define VOP_DSC_INT_EN_OUT_BUFF_EMPTY_CONTEXT_1_MASK       (0x1U << VOP_DSC_INT_EN_OUT_BUFF_EMPTY_CONTEXT_1_SHIFT)      /* 0x00000004 */
#define VOP_DSC_INT_EN_OUT_BUFF_EMPTY_CONTEXT_0_SHIFT      (3U)
#define VOP_DSC_INT_EN_OUT_BUFF_EMPTY_CONTEXT_0_MASK       (0x1U << VOP_DSC_INT_EN_OUT_BUFF_EMPTY_CONTEXT_0_SHIFT)      /* 0x00000008 */
#define VOP_DSC_INT_EN_FRAME_DONE_SHIFT                    (4U)
#define VOP_DSC_INT_EN_FRAME_DONE_MASK                     (0x1U << VOP_DSC_INT_EN_FRAME_DONE_SHIFT)                    /* 0x00000010 */
#define VOP_DSC_INT_EN_FRAME_STARTED_SHIFT                 (5U)
#define VOP_DSC_INT_EN_FRAME_STARTED_MASK                  (0x1U << VOP_DSC_INT_EN_FRAME_STARTED_SHIFT)                 /* 0x00000020 */
#define VOP_DSC_INT_EN_CE_SHIFT                            (6U)
#define VOP_DSC_INT_EN_CE_MASK                             (0x1U << VOP_DSC_INT_EN_CE_SHIFT)                            /* 0x00000040 */
#define VOP_DSC_INT_EN_RC_MODEL_BUFFER_FULLNESS_OVERFLOW_CONTEXT_1_SHIFT (7U)
#define VOP_DSC_INT_EN_RC_MODEL_BUFFER_FULLNESS_OVERFLOW_CONTEXT_1_MASK (0x1U << VOP_DSC_INT_EN_RC_MODEL_BUFFER_FULLNESS_OVERFLOW_CONTEXT_1_SHIFT) /* 0x00000080 */
#define VOP_DSC_INT_EN_RC_MODEL_BUFFER_FULLNESS_OVERFLOW_CONTEXT_0_SHIFT (8U)
#define VOP_DSC_INT_EN_RC_MODEL_BUFFER_FULLNESS_OVERFLOW_CONTEXT_0_MASK (0x1U << VOP_DSC_INT_EN_RC_MODEL_BUFFER_FULLNESS_OVERFLOW_CONTEXT_0_SHIFT) /* 0x00000100 */
#define VOP_DSC_INT_EN_DSC_UNDERFLOW_CONTEX_1_SHIFT        (9U)
#define VOP_DSC_INT_EN_DSC_UNDERFLOW_CONTEX_1_MASK         (0x1U << VOP_DSC_INT_EN_DSC_UNDERFLOW_CONTEX_1_SHIFT)        /* 0x00000200 */
#define VOP_DSC_INT_EN_DSC_UNDERFLOW_CONTEX_0_SHIFT        (10U)
#define VOP_DSC_INT_EN_DSC_UNDERFLOW_CONTEX_0_MASK         (0x1U << VOP_DSC_INT_EN_DSC_UNDERFLOW_CONTEX_0_SHIFT)        /* 0x00000400 */
/* DSC_INT_CLR */
#define VOP_DSC_INT_CLR_OFFSET                             (0xA74U)
#define VOP_DSC_INT_CLR_OUT_BUFF_FULL_CONTEXT_1_SHIFT      (0U)
#define VOP_DSC_INT_CLR_OUT_BUFF_FULL_CONTEXT_1_MASK       (0x1U << VOP_DSC_INT_CLR_OUT_BUFF_FULL_CONTEXT_1_SHIFT)      /* 0x00000001 */
#define VOP_DSC_INT_CLR_OUT_BUFF_FULL_CONTEXT_0_SHIFT      (1U)
#define VOP_DSC_INT_CLR_OUT_BUFF_FULL_CONTEXT_0_MASK       (0x1U << VOP_DSC_INT_CLR_OUT_BUFF_FULL_CONTEXT_0_SHIFT)      /* 0x00000002 */
#define VOP_DSC_INT_CLR_OUT_BUFF_EMPTY_CONTEXT_1_SHIFT     (2U)
#define VOP_DSC_INT_CLR_OUT_BUFF_EMPTY_CONTEXT_1_MASK      (0x1U << VOP_DSC_INT_CLR_OUT_BUFF_EMPTY_CONTEXT_1_SHIFT)     /* 0x00000004 */
#define VOP_DSC_INT_CLR_OUT_BUFF_EMPTY_CONTEXT_0_SHIFT     (3U)
#define VOP_DSC_INT_CLR_OUT_BUFF_EMPTY_CONTEXT_0_MASK      (0x1U << VOP_DSC_INT_CLR_OUT_BUFF_EMPTY_CONTEXT_0_SHIFT)     /* 0x00000008 */
#define VOP_DSC_INT_CLR_FRAME_DONE_SHIFT                   (4U)
#define VOP_DSC_INT_CLR_FRAME_DONE_MASK                    (0x1U << VOP_DSC_INT_CLR_FRAME_DONE_SHIFT)                   /* 0x00000010 */
#define VOP_DSC_INT_CLR_FRAME_STARTED_SHIFT                (5U)
#define VOP_DSC_INT_CLR_FRAME_STARTED_MASK                 (0x1U << VOP_DSC_INT_CLR_FRAME_STARTED_SHIFT)                /* 0x00000020 */
#define VOP_DSC_INT_CLR_CE_SHIFT                           (6U)
#define VOP_DSC_INT_CLR_CE_MASK                            (0x1U << VOP_DSC_INT_CLR_CE_SHIFT)                           /* 0x00000040 */
#define VOP_DSC_INT_CLR_RC_MODEL_BUFFER_FULLNESS_OVERFLOW_CONTEXT_1_SHIFT (7U)
#define VOP_DSC_INT_CLR_RC_MODEL_BUFFER_FULLNESS_OVERFLOW_CONTEXT_1_MASK (0x1U << VOP_DSC_INT_CLR_RC_MODEL_BUFFER_FULLNESS_OVERFLOW_CONTEXT_1_SHIFT) /* 0x00000080 */
#define VOP_DSC_INT_CLR_RC_MODEL_BUFFER_FULLNESS_OVERFLOW_CONTEXT_0_SHIFT (8U)
#define VOP_DSC_INT_CLR_RC_MODEL_BUFFER_FULLNESS_OVERFLOW_CONTEXT_0_MASK (0x1U << VOP_DSC_INT_CLR_RC_MODEL_BUFFER_FULLNESS_OVERFLOW_CONTEXT_0_SHIFT) /* 0x00000100 */
#define VOP_DSC_INT_CLR_DSC_UNDERFLOW_CONTEX_1_SHIFT       (9U)
#define VOP_DSC_INT_CLR_DSC_UNDERFLOW_CONTEX_1_MASK        (0x1U << VOP_DSC_INT_CLR_DSC_UNDERFLOW_CONTEX_1_SHIFT)       /* 0x00000200 */
#define VOP_DSC_INT_CLR_DSC_UNDERFLOW_CONTEX_0_SHIFT       (10U)
#define VOP_DSC_INT_CLR_DSC_UNDERFLOW_CONTEX_0_MASK        (0x1U << VOP_DSC_INT_CLR_DSC_UNDERFLOW_CONTEX_0_SHIFT)       /* 0x00000400 */
/* DSC_INT_STATUS */
#define VOP_DSC_INT_STATUS_OFFSET                          (0xA78U)
#define VOP_DSC_INT_STATUS_OUT_BUFF_FULL_CONTEXT_1_SHIFT   (0U)
#define VOP_DSC_INT_STATUS_OUT_BUFF_FULL_CONTEXT_1_MASK    (0x1U << VOP_DSC_INT_STATUS_OUT_BUFF_FULL_CONTEXT_1_SHIFT)   /* 0x00000001 */
#define VOP_DSC_INT_STATUS_OUT_BUFF_FULL_CONTEXT_0_SHIFT   (1U)
#define VOP_DSC_INT_STATUS_OUT_BUFF_FULL_CONTEXT_0_MASK    (0x1U << VOP_DSC_INT_STATUS_OUT_BUFF_FULL_CONTEXT_0_SHIFT)   /* 0x00000002 */
#define VOP_DSC_INT_STATUS_OUT_BUFF_EMPTY_CONTEXT_1_SHIFT  (2U)
#define VOP_DSC_INT_STATUS_OUT_BUFF_EMPTY_CONTEXT_1_MASK   (0x1U << VOP_DSC_INT_STATUS_OUT_BUFF_EMPTY_CONTEXT_1_SHIFT)  /* 0x00000004 */
#define VOP_DSC_INT_STATUS_OUT_BUFF_EMPTY_CONTEXT_0_SHIFT  (3U)
#define VOP_DSC_INT_STATUS_OUT_BUFF_EMPTY_CONTEXT_0_MASK   (0x1U << VOP_DSC_INT_STATUS_OUT_BUFF_EMPTY_CONTEXT_0_SHIFT)  /* 0x00000008 */
#define VOP_DSC_INT_STATUS_FRAME_DONE_SHIFT                (4U)
#define VOP_DSC_INT_STATUS_FRAME_DONE_MASK                 (0x1U << VOP_DSC_INT_STATUS_FRAME_DONE_SHIFT)                /* 0x00000010 */
#define VOP_DSC_INT_STATUS_FRAME_STARTED_SHIFT             (5U)
#define VOP_DSC_INT_STATUS_FRAME_STARTED_MASK              (0x1U << VOP_DSC_INT_STATUS_FRAME_STARTED_SHIFT)             /* 0x00000020 */
#define VOP_DSC_INT_STATUS_CE_SHIFT                        (6U)
#define VOP_DSC_INT_STATUS_CE_MASK                         (0x1U << VOP_DSC_INT_STATUS_CE_SHIFT)                        /* 0x00000040 */
#define VOP_DSC_INT_STATUS_RC_MODEL_BUFFER_FULLNESS_OVERFLOW_CONTEXT_1_SHIFT (7U)
#define VOP_DSC_INT_STATUS_RC_MODEL_BUFFER_FULLNESS_OVERFLOW_CONTEXT_1_MASK (0x1U << VOP_DSC_INT_STATUS_RC_MODEL_BUFFER_FULLNESS_OVERFLOW_CONTEXT_1_SHIFT) /* 0x00000080 */
#define VOP_DSC_INT_STATUS_RC_MODEL_BUFFER_FULLNESS_OVERFLOW_CONTEXT_0_SHIFT (8U)
#define VOP_DSC_INT_STATUS_RC_MODEL_BUFFER_FULLNESS_OVERFLOW_CONTEXT_0_MASK (0x1U << VOP_DSC_INT_STATUS_RC_MODEL_BUFFER_FULLNESS_OVERFLOW_CONTEXT_0_SHIFT) /* 0x00000100 */
#define VOP_DSC_INT_STATUS_DSC_UNDERFLOW_CONTEX_1_SHIFT    (9U)
#define VOP_DSC_INT_STATUS_DSC_UNDERFLOW_CONTEX_1_MASK     (0x1U << VOP_DSC_INT_STATUS_DSC_UNDERFLOW_CONTEX_1_SHIFT)    /* 0x00000200 */
#define VOP_DSC_INT_STATUS_DSC_UNDERFLOW_CONTEX_0_SHIFT    (10U)
#define VOP_DSC_INT_STATUS_DSC_UNDERFLOW_CONTEX_0_MASK     (0x1U << VOP_DSC_INT_STATUS_DSC_UNDERFLOW_CONTEX_0_SHIFT)    /* 0x00000400 */
/* DSC_DBG_STATUS0 */
#define VOP_DSC_DBG_STATUS0_OFFSET                         (0xA80U)
#define VOP_DSC_DBG_STATUS0                                (0x0U)
#define VOP_DSC_DBG_STATUS0_SLICE_COUNT_OUT_SHIFT          (0U)
#define VOP_DSC_DBG_STATUS0_SLICE_COUNT_OUT_MASK           (0xFFFFU << VOP_DSC_DBG_STATUS0_SLICE_COUNT_OUT_SHIFT)       /* 0x0000FFFF */
#define VOP_DSC_DBG_STATUS0_SLICE_LINE_COUNT_OUT_SHIFT     (16U)
#define VOP_DSC_DBG_STATUS0_SLICE_LINE_COUNT_OUT_MASK      (0xFFFFU << VOP_DSC_DBG_STATUS0_SLICE_LINE_COUNT_OUT_SHIFT)  /* 0xFFFF0000 */
/* DSC_DBG_STATUS1 */
#define VOP_DSC_DBG_STATUS1_OFFSET                         (0xA84U)
#define VOP_DSC_DBG_STATUS1                                (0x0U)
#define VOP_DSC_DBG_STATUS1_SLICE_COUNT_ENCODED_SHIFT      (0U)
#define VOP_DSC_DBG_STATUS1_SLICE_COUNT_ENCODED_MASK       (0xFFFFU << VOP_DSC_DBG_STATUS1_SLICE_COUNT_ENCODED_SHIFT)   /* 0x0000FFFF */
#define VOP_DSC_DBG_STATUS1_SLICE_LINE_COUNT_ENCODED_SHIFT (16U)
#define VOP_DSC_DBG_STATUS1_SLICE_LINE_COUNT_ENCODED_MASK  (0xFFFFU << VOP_DSC_DBG_STATUS1_SLICE_LINE_COUNT_ENCODED_SHIFT) /* 0xFFFF0000 */
/* DSC_DBG_STATUS2 */
#define VOP_DSC_DBG_STATUS2_OFFSET                         (0xA88U)
#define VOP_DSC_DBG_STATUS2_OUT_BUFF_FULL_CONTEXT_1_SHIFT  (0U)
#define VOP_DSC_DBG_STATUS2_OUT_BUFF_FULL_CONTEXT_1_MASK   (0x1U << VOP_DSC_DBG_STATUS2_OUT_BUFF_FULL_CONTEXT_1_SHIFT)  /* 0x00000001 */
#define VOP_DSC_DBG_STATUS2_OUT_BUFF_FULL_CONTEXT_0_SHIFT  (1U)
#define VOP_DSC_DBG_STATUS2_OUT_BUFF_FULL_CONTEXT_0_MASK   (0x1U << VOP_DSC_DBG_STATUS2_OUT_BUFF_FULL_CONTEXT_0_SHIFT)  /* 0x00000002 */
#define VOP_DSC_DBG_STATUS2_OUT_BUFF_EMPTY_CONTEXT_1_SHIFT (2U)
#define VOP_DSC_DBG_STATUS2_OUT_BUFF_EMPTY_CONTEXT_1_MASK  (0x1U << VOP_DSC_DBG_STATUS2_OUT_BUFF_EMPTY_CONTEXT_1_SHIFT) /* 0x00000004 */
#define VOP_DSC_DBG_STATUS2_OUT_BUFF_EMPTY_CONTEXT_0_SHIFT (3U)
#define VOP_DSC_DBG_STATUS2_OUT_BUFF_EMPTY_CONTEXT_0_MASK  (0x1U << VOP_DSC_DBG_STATUS2_OUT_BUFF_EMPTY_CONTEXT_0_SHIFT) /* 0x00000008 */
#define VOP_DSC_DBG_STATUS2_FRAME_DONE_SHIFT               (4U)
#define VOP_DSC_DBG_STATUS2_FRAME_DONE_MASK                (0x1U << VOP_DSC_DBG_STATUS2_FRAME_DONE_SHIFT)               /* 0x00000010 */
#define VOP_DSC_DBG_STATUS2_FRAME_STARTED_SHIFT            (5U)
#define VOP_DSC_DBG_STATUS2_FRAME_STARTED_MASK             (0x1U << VOP_DSC_DBG_STATUS2_FRAME_STARTED_SHIFT)            /* 0x00000020 */
#define VOP_DSC_DBG_STATUS2_CE_SHIFT                       (6U)
#define VOP_DSC_DBG_STATUS2_CE_MASK                        (0x1U << VOP_DSC_DBG_STATUS2_CE_SHIFT)                       /* 0x00000040 */
/******************************************DSI*******************************************/
/* VERSION */
#define DSI_VERSION_OFFSET                                 (0x0U)
#define DSI_VERSION                                        (0x3133302AU)
#define DSI_VERSION_VERSION_SHIFT                          (0U)
#define DSI_VERSION_VERSION_MASK                           (0xFFFFFFFFU << DSI_VERSION_VERSION_SHIFT)                   /* 0xFFFFFFFF */
/* PWR_UP */
#define DSI_PWR_UP_OFFSET                                  (0x4U)
#define DSI_PWR_UP_SHUTDOWNZ_SHIFT                         (0U)
#define DSI_PWR_UP_SHUTDOWNZ_MASK                          (0x1U << DSI_PWR_UP_SHUTDOWNZ_SHIFT)                         /* 0x00000001 */
/* CLKMGR_CFG */
#define DSI_CLKMGR_CFG_OFFSET                              (0x8U)
#define DSI_CLKMGR_CFG_TX_ESC_CLK_DIVISION_SHIFT           (0U)
#define DSI_CLKMGR_CFG_TX_ESC_CLK_DIVISION_MASK            (0xFFU << DSI_CLKMGR_CFG_TX_ESC_CLK_DIVISION_SHIFT)          /* 0x000000FF */
#define DSI_CLKMGR_CFG_TO_CLK_DIVISION_SHIFT               (8U)
#define DSI_CLKMGR_CFG_TO_CLK_DIVISION_MASK                (0xFFU << DSI_CLKMGR_CFG_TO_CLK_DIVISION_SHIFT)              /* 0x0000FF00 */
/* DPI_VCID */
#define DSI_DPI_VCID_OFFSET                                (0xCU)
#define DSI_DPI_VCID_DPI_VCID_SHIFT                        (0U)
#define DSI_DPI_VCID_DPI_VCID_MASK                         (0x3U << DSI_DPI_VCID_DPI_VCID_SHIFT)                        /* 0x00000003 */
/* DPI_COLOR_CODING */
#define DSI_DPI_COLOR_CODING_OFFSET                        (0x10U)
#define DSI_DPI_COLOR_CODING_DPI_COLOR_CODING_SHIFT        (0U)
#define DSI_DPI_COLOR_CODING_DPI_COLOR_CODING_MASK         (0xFU << DSI_DPI_COLOR_CODING_DPI_COLOR_CODING_SHIFT)        /* 0x0000000F */
#define DSI_DPI_COLOR_CODING_LOOSELY18_EN_SHIFT            (8U)
#define DSI_DPI_COLOR_CODING_LOOSELY18_EN_MASK             (0x1U << DSI_DPI_COLOR_CODING_LOOSELY18_EN_SHIFT)            /* 0x00000100 */
/* DPI_CFG_POL */
#define DSI_DPI_CFG_POL_OFFSET                             (0x14U)
#define DSI_DPI_CFG_POL_DATAEN_ACTIVE_LOW_SHIFT            (0U)
#define DSI_DPI_CFG_POL_DATAEN_ACTIVE_LOW_MASK             (0x1U << DSI_DPI_CFG_POL_DATAEN_ACTIVE_LOW_SHIFT)            /* 0x00000001 */
#define DSI_DPI_CFG_POL_VSYNC_ACTIVE_LOW_SHIFT             (1U)
#define DSI_DPI_CFG_POL_VSYNC_ACTIVE_LOW_MASK              (0x1U << DSI_DPI_CFG_POL_VSYNC_ACTIVE_LOW_SHIFT)             /* 0x00000002 */
#define DSI_DPI_CFG_POL_HSYNC_ACTIVE_LOW_SHIFT             (2U)
#define DSI_DPI_CFG_POL_HSYNC_ACTIVE_LOW_MASK              (0x1U << DSI_DPI_CFG_POL_HSYNC_ACTIVE_LOW_SHIFT)             /* 0x00000004 */
#define DSI_DPI_CFG_POL_SHUTD_ACTIVE_LOW_SHIFT             (3U)
#define DSI_DPI_CFG_POL_SHUTD_ACTIVE_LOW_MASK              (0x1U << DSI_DPI_CFG_POL_SHUTD_ACTIVE_LOW_SHIFT)             /* 0x00000008 */
#define DSI_DPI_CFG_POL_COLORM_ACTIVE_LOW_SHIFT            (4U)
#define DSI_DPI_CFG_POL_COLORM_ACTIVE_LOW_MASK             (0x1U << DSI_DPI_CFG_POL_COLORM_ACTIVE_LOW_SHIFT)            /* 0x00000010 */
/* DPI_LP_CMD_TIM */
#define DSI_DPI_LP_CMD_TIM_OFFSET                          (0x18U)
#define DSI_DPI_LP_CMD_TIM_INVACT_LPCMD_TIME_SHIFT         (0U)
#define DSI_DPI_LP_CMD_TIM_INVACT_LPCMD_TIME_MASK          (0xFFU << DSI_DPI_LP_CMD_TIM_INVACT_LPCMD_TIME_SHIFT)        /* 0x000000FF */
#define DSI_DPI_LP_CMD_TIM_OUTVACT_LPCMD_TIME_SHIFT        (16U)
#define DSI_DPI_LP_CMD_TIM_OUTVACT_LPCMD_TIME_MASK         (0xFFU << DSI_DPI_LP_CMD_TIM_OUTVACT_LPCMD_TIME_SHIFT)       /* 0x00FF0000 */
/* PCKHDL_CFG */
#define DSI_PCKHDL_CFG_OFFSET                              (0x2CU)
#define DSI_PCKHDL_CFG_EOTP_TX_EN_SHIFT                    (0U)
#define DSI_PCKHDL_CFG_EOTP_TX_EN_MASK                     (0x1U << DSI_PCKHDL_CFG_EOTP_TX_EN_SHIFT)                    /* 0x00000001 */
#define DSI_PCKHDL_CFG_EOTP_RX_EN_SHIFT                    (1U)
#define DSI_PCKHDL_CFG_EOTP_RX_EN_MASK                     (0x1U << DSI_PCKHDL_CFG_EOTP_RX_EN_SHIFT)                    /* 0x00000002 */
#define DSI_PCKHDL_CFG_BTA_EN_SHIFT                        (2U)
#define DSI_PCKHDL_CFG_BTA_EN_MASK                         (0x1U << DSI_PCKHDL_CFG_BTA_EN_SHIFT)                        /* 0x00000004 */
#define DSI_PCKHDL_CFG_ECC_RX_EN_SHIFT                     (3U)
#define DSI_PCKHDL_CFG_ECC_RX_EN_MASK                      (0x1U << DSI_PCKHDL_CFG_ECC_RX_EN_SHIFT)                     /* 0x00000008 */
#define DSI_PCKHDL_CFG_CRC_RX_EN_SHIFT                     (4U)
#define DSI_PCKHDL_CFG_CRC_RX_EN_MASK                      (0x1U << DSI_PCKHDL_CFG_CRC_RX_EN_SHIFT)                     /* 0x00000010 */
/* GEN_VCID */
#define DSI_GEN_VCID_OFFSET                                (0x30U)
#define DSI_GEN_VCID_GEN_VCID_RX_SHIFT                     (0U)
#define DSI_GEN_VCID_GEN_VCID_RX_MASK                      (0x3U << DSI_GEN_VCID_GEN_VCID_RX_SHIFT)                     /* 0x00000003 */
/* MODE_CFG */
#define DSI_MODE_CFG_OFFSET                                (0x34U)
#define DSI_MODE_CFG_CMD_VIDEO_MODE_SHIFT                  (0U)
#define DSI_MODE_CFG_CMD_VIDEO_MODE_MASK                   (0x1U << DSI_MODE_CFG_CMD_VIDEO_MODE_SHIFT)                  /* 0x00000001 */
/* VID_MODE_CFG */
#define DSI_VID_MODE_CFG_OFFSET                            (0x38U)
#define DSI_VID_MODE_CFG_VID_MODE_TYPE_SHIFT               (0U)
#define DSI_VID_MODE_CFG_VID_MODE_TYPE_MASK                (0x3U << DSI_VID_MODE_CFG_VID_MODE_TYPE_SHIFT)               /* 0x00000003 */
#define DSI_VID_MODE_CFG_LP_VSA_EN_SHIFT                   (8U)
#define DSI_VID_MODE_CFG_LP_VSA_EN_MASK                    (0x1U << DSI_VID_MODE_CFG_LP_VSA_EN_SHIFT)                   /* 0x00000100 */
#define DSI_VID_MODE_CFG_LP_VBP_EN_SHIFT                   (9U)
#define DSI_VID_MODE_CFG_LP_VBP_EN_MASK                    (0x1U << DSI_VID_MODE_CFG_LP_VBP_EN_SHIFT)                   /* 0x00000200 */
#define DSI_VID_MODE_CFG_LP_VFP_EN_SHIFT                   (10U)
#define DSI_VID_MODE_CFG_LP_VFP_EN_MASK                    (0x1U << DSI_VID_MODE_CFG_LP_VFP_EN_SHIFT)                   /* 0x00000400 */
#define DSI_VID_MODE_CFG_LP_VACT_EN_SHIFT                  (11U)
#define DSI_VID_MODE_CFG_LP_VACT_EN_MASK                   (0x1U << DSI_VID_MODE_CFG_LP_VACT_EN_SHIFT)                  /* 0x00000800 */
#define DSI_VID_MODE_CFG_LP_HBP_EN_SHIFT                   (12U)
#define DSI_VID_MODE_CFG_LP_HBP_EN_MASK                    (0x1U << DSI_VID_MODE_CFG_LP_HBP_EN_SHIFT)                   /* 0x00001000 */
#define DSI_VID_MODE_CFG_LP_HFP_EN_SHIFT                   (13U)
#define DSI_VID_MODE_CFG_LP_HFP_EN_MASK                    (0x1U << DSI_VID_MODE_CFG_LP_HFP_EN_SHIFT)                   /* 0x00002000 */
#define DSI_VID_MODE_CFG_FRAME_BTA_ACK_EN_SHIFT            (14U)
#define DSI_VID_MODE_CFG_FRAME_BTA_ACK_EN_MASK             (0x1U << DSI_VID_MODE_CFG_FRAME_BTA_ACK_EN_SHIFT)            /* 0x00004000 */
#define DSI_VID_MODE_CFG_LP_CMD_EN_SHIFT                   (15U)
#define DSI_VID_MODE_CFG_LP_CMD_EN_MASK                    (0x1U << DSI_VID_MODE_CFG_LP_CMD_EN_SHIFT)                   /* 0x00008000 */
#define DSI_VID_MODE_CFG_VGP_EN_SHIFT                      (16U)
#define DSI_VID_MODE_CFG_VGP_EN_MASK                       (0x1U << DSI_VID_MODE_CFG_VGP_EN_SHIFT)                      /* 0x00010000 */
#define DSI_VID_MODE_CFG_VGP_MODE_SHIFT                    (20U)
#define DSI_VID_MODE_CFG_VGP_MODE_MASK                     (0x1U << DSI_VID_MODE_CFG_VGP_MODE_SHIFT)                    /* 0x00100000 */
#define DSI_VID_MODE_CFG_VGP_ORIENTATION_SHIFT             (24U)
#define DSI_VID_MODE_CFG_VGP_ORIENTATION_MASK              (0x1U << DSI_VID_MODE_CFG_VGP_ORIENTATION_SHIFT)             /* 0x01000000 */
/* VID_PKT_SIZE */
#define DSI_VID_PKT_SIZE_OFFSET                            (0x3CU)
#define DSI_VID_PKT_SIZE_VID_PKT_SIZE_SHIFT                (0U)
#define DSI_VID_PKT_SIZE_VID_PKT_SIZE_MASK                 (0x3FFFU << DSI_VID_PKT_SIZE_VID_PKT_SIZE_SHIFT)             /* 0x00003FFF */
/* VID_NUM_CHUNKS */
#define DSI_VID_NUM_CHUNKS_OFFSET                          (0x40U)
#define DSI_VID_NUM_CHUNKS_VID_NUM_CHUNKS_SHIFT            (0U)
#define DSI_VID_NUM_CHUNKS_VID_NUM_CHUNKS_MASK             (0x1FFFU << DSI_VID_NUM_CHUNKS_VID_NUM_CHUNKS_SHIFT)         /* 0x00001FFF */
/* VID_NULL_SIZE */
#define DSI_VID_NULL_SIZE_OFFSET                           (0x44U)
#define DSI_VID_NULL_SIZE_VID_NULL_SIZE_SHIFT              (0U)
#define DSI_VID_NULL_SIZE_VID_NULL_SIZE_MASK               (0x1FFFU << DSI_VID_NULL_SIZE_VID_NULL_SIZE_SHIFT)           /* 0x00001FFF */
/* VID_HSA_TIME */
#define DSI_VID_HSA_TIME_OFFSET                            (0x48U)
#define DSI_VID_HSA_TIME_VID_HSA_TIME_SHIFT                (0U)
#define DSI_VID_HSA_TIME_VID_HSA_TIME_MASK                 (0xFFFU << DSI_VID_HSA_TIME_VID_HSA_TIME_SHIFT)              /* 0x00000FFF */
/* VID_HBP_TIME */
#define DSI_VID_HBP_TIME_OFFSET                            (0x4CU)
#define DSI_VID_HBP_TIME_VID_HBP_TIME_SHIFT                (0U)
#define DSI_VID_HBP_TIME_VID_HBP_TIME_MASK                 (0xFFFU << DSI_VID_HBP_TIME_VID_HBP_TIME_SHIFT)              /* 0x00000FFF */
/* VID_HLINE_TIME */
#define DSI_VID_HLINE_TIME_OFFSET                          (0x50U)
#define DSI_VID_HLINE_TIME_VID_HLINE_TIME_SHIFT            (0U)
#define DSI_VID_HLINE_TIME_VID_HLINE_TIME_MASK             (0x7FFFU << DSI_VID_HLINE_TIME_VID_HLINE_TIME_SHIFT)         /* 0x00007FFF */
/* VID_VSA_LINES */
#define DSI_VID_VSA_LINES_OFFSET                           (0x54U)
#define DSI_VID_VSA_LINES_VSA_LINES_SHIFT                  (0U)
#define DSI_VID_VSA_LINES_VSA_LINES_MASK                   (0x3FFU << DSI_VID_VSA_LINES_VSA_LINES_SHIFT)                /* 0x000003FF */
/* VID_VBP_LINES */
#define DSI_VID_VBP_LINES_OFFSET                           (0x58U)
#define DSI_VID_VBP_LINES_VBP_LINE_SHIFT                   (0U)
#define DSI_VID_VBP_LINES_VBP_LINE_MASK                    (0x3FFU << DSI_VID_VBP_LINES_VBP_LINE_SHIFT)                 /* 0x000003FF */
/* VID_VFP_LINES */
#define DSI_VID_VFP_LINES_OFFSET                           (0x5CU)
#define DSI_VID_VFP_LINES_VFP_LINES_SHIFT                  (0U)
#define DSI_VID_VFP_LINES_VFP_LINES_MASK                   (0x3FFU << DSI_VID_VFP_LINES_VFP_LINES_SHIFT)                /* 0x000003FF */
/* VID_VACTIVE_LINES */
#define DSI_VID_VACTIVE_LINES_OFFSET                       (0x60U)
#define DSI_VID_VACTIVE_LINES_V_ACTIVE_LINES_SHIFT         (0U)
#define DSI_VID_VACTIVE_LINES_V_ACTIVE_LINES_MASK          (0x3FFFU << DSI_VID_VACTIVE_LINES_V_ACTIVE_LINES_SHIFT)      /* 0x00003FFF */
/* EDPI_CMD_SIZE */
#define DSI_EDPI_CMD_SIZE_OFFSET                           (0x64U)
#define DSI_EDPI_CMD_SIZE_EDPI_ALLOWED_CMD_SIZE_SHIFT      (0U)
#define DSI_EDPI_CMD_SIZE_EDPI_ALLOWED_CMD_SIZE_MASK       (0xFFFFU << DSI_EDPI_CMD_SIZE_EDPI_ALLOWED_CMD_SIZE_SHIFT)   /* 0x0000FFFF */
/* CMD_MODE_CFG */
#define DSI_CMD_MODE_CFG_OFFSET                            (0x68U)
#define DSI_CMD_MODE_CFG_TEAR_FX_EN_SHIFT                  (0U)
#define DSI_CMD_MODE_CFG_TEAR_FX_EN_MASK                   (0x1U << DSI_CMD_MODE_CFG_TEAR_FX_EN_SHIFT)                  /* 0x00000001 */
#define DSI_CMD_MODE_CFG_ACK_RQST_EN_SHIFT                 (1U)
#define DSI_CMD_MODE_CFG_ACK_RQST_EN_MASK                  (0x1U << DSI_CMD_MODE_CFG_ACK_RQST_EN_SHIFT)                 /* 0x00000002 */
#define DSI_CMD_MODE_CFG_GEN_SW_0P_TX_SHIFT                (8U)
#define DSI_CMD_MODE_CFG_GEN_SW_0P_TX_MASK                 (0x1U << DSI_CMD_MODE_CFG_GEN_SW_0P_TX_SHIFT)                /* 0x00000100 */
#define DSI_CMD_MODE_CFG_GEN_SW_1P_TX_SHIFT                (9U)
#define DSI_CMD_MODE_CFG_GEN_SW_1P_TX_MASK                 (0x1U << DSI_CMD_MODE_CFG_GEN_SW_1P_TX_SHIFT)                /* 0x00000200 */
#define DSI_CMD_MODE_CFG_GEN_SW_2P_TX_SHIFT                (10U)
#define DSI_CMD_MODE_CFG_GEN_SW_2P_TX_MASK                 (0x1U << DSI_CMD_MODE_CFG_GEN_SW_2P_TX_SHIFT)                /* 0x00000400 */
#define DSI_CMD_MODE_CFG_GEN_SR_0P_TX_SHIFT                (11U)
#define DSI_CMD_MODE_CFG_GEN_SR_0P_TX_MASK                 (0x1U << DSI_CMD_MODE_CFG_GEN_SR_0P_TX_SHIFT)                /* 0x00000800 */
#define DSI_CMD_MODE_CFG_GEN_SR_1P_TX_SHIFT                (12U)
#define DSI_CMD_MODE_CFG_GEN_SR_1P_TX_MASK                 (0x1U << DSI_CMD_MODE_CFG_GEN_SR_1P_TX_SHIFT)                /* 0x00001000 */
#define DSI_CMD_MODE_CFG_GEN_SR_2P_TX_SHIFT                (13U)
#define DSI_CMD_MODE_CFG_GEN_SR_2P_TX_MASK                 (0x1U << DSI_CMD_MODE_CFG_GEN_SR_2P_TX_SHIFT)                /* 0x00002000 */
#define DSI_CMD_MODE_CFG_GEN_LW_TX_SHIFT                   (14U)
#define DSI_CMD_MODE_CFG_GEN_LW_TX_MASK                    (0x1U << DSI_CMD_MODE_CFG_GEN_LW_TX_SHIFT)                   /* 0x00004000 */
#define DSI_CMD_MODE_CFG_DCS_SW_0P_TX_SHIFT                (16U)
#define DSI_CMD_MODE_CFG_DCS_SW_0P_TX_MASK                 (0x1U << DSI_CMD_MODE_CFG_DCS_SW_0P_TX_SHIFT)                /* 0x00010000 */
#define DSI_CMD_MODE_CFG_DCS_SW_1P_TX_SHIFT                (17U)
#define DSI_CMD_MODE_CFG_DCS_SW_1P_TX_MASK                 (0x1U << DSI_CMD_MODE_CFG_DCS_SW_1P_TX_SHIFT)                /* 0x00020000 */
#define DSI_CMD_MODE_CFG_DCS_SR_0P_TX_SHIFT                (18U)
#define DSI_CMD_MODE_CFG_DCS_SR_0P_TX_MASK                 (0x1U << DSI_CMD_MODE_CFG_DCS_SR_0P_TX_SHIFT)                /* 0x00040000 */
#define DSI_CMD_MODE_CFG_DCS_LW_TX_SHIFT                   (19U)
#define DSI_CMD_MODE_CFG_DCS_LW_TX_MASK                    (0x1U << DSI_CMD_MODE_CFG_DCS_LW_TX_SHIFT)                   /* 0x00080000 */
#define DSI_CMD_MODE_CFG_MAX_RD_PKT_SIZE_SHIFT             (24U)
#define DSI_CMD_MODE_CFG_MAX_RD_PKT_SIZE_MASK              (0x1U << DSI_CMD_MODE_CFG_MAX_RD_PKT_SIZE_SHIFT)             /* 0x01000000 */
/* GEN_HDR */
#define DSI_GEN_HDR_OFFSET                                 (0x6CU)
#define DSI_GEN_HDR_GEN_DT_SHIFT                           (0U)
#define DSI_GEN_HDR_GEN_DT_MASK                            (0x3FU << DSI_GEN_HDR_GEN_DT_SHIFT)                          /* 0x0000003F */
#define DSI_GEN_HDR_GEN_VC_SHIFT                           (6U)
#define DSI_GEN_HDR_GEN_VC_MASK                            (0x3U << DSI_GEN_HDR_GEN_VC_SHIFT)                           /* 0x000000C0 */
#define DSI_GEN_HDR_GEN_WC_LSBYTE_SHIFT                    (8U)
#define DSI_GEN_HDR_GEN_WC_LSBYTE_MASK                     (0xFFU << DSI_GEN_HDR_GEN_WC_LSBYTE_SHIFT)                   /* 0x0000FF00 */
#define DSI_GEN_HDR_GEM_WC_MSBYTE_SHIFT                    (16U)
#define DSI_GEN_HDR_GEM_WC_MSBYTE_MASK                     (0xFFU << DSI_GEN_HDR_GEM_WC_MSBYTE_SHIFT)                   /* 0x00FF0000 */
/* GEN_PLD_DATA */
#define DSI_GEN_PLD_DATA_OFFSET                            (0x70U)
#define DSI_GEN_PLD_DATA_GEN_PLD_B1_SHIFT                  (0U)
#define DSI_GEN_PLD_DATA_GEN_PLD_B1_MASK                   (0xFFU << DSI_GEN_PLD_DATA_GEN_PLD_B1_SHIFT)                 /* 0x000000FF */
#define DSI_GEN_PLD_DATA_GEN_PLD_B2_SHIFT                  (8U)
#define DSI_GEN_PLD_DATA_GEN_PLD_B2_MASK                   (0xFFU << DSI_GEN_PLD_DATA_GEN_PLD_B2_SHIFT)                 /* 0x0000FF00 */
#define DSI_GEN_PLD_DATA_GEN_PLD_B3_SHIFT                  (16U)
#define DSI_GEN_PLD_DATA_GEN_PLD_B3_MASK                   (0xFFU << DSI_GEN_PLD_DATA_GEN_PLD_B3_SHIFT)                 /* 0x00FF0000 */
#define DSI_GEN_PLD_DATA_GEN_PLD_B4_SHIFT                  (24U)
#define DSI_GEN_PLD_DATA_GEN_PLD_B4_MASK                   (0xFFU << DSI_GEN_PLD_DATA_GEN_PLD_B4_SHIFT)                 /* 0xFF000000 */
/* CMD_PKT_STATUS */
#define DSI_CMD_PKT_STATUS_OFFSET                          (0x74U)
#define DSI_CMD_PKT_STATUS                                 (0x1515U)
#define DSI_CMD_PKT_STATUS_GEN_CMD_EMPTY_SHIFT             (0U)
#define DSI_CMD_PKT_STATUS_GEN_CMD_EMPTY_MASK              (0x1U << DSI_CMD_PKT_STATUS_GEN_CMD_EMPTY_SHIFT)             /* 0x00000001 */
#define DSI_CMD_PKT_STATUS_GEN_CMD_FULL_SHIFT              (1U)
#define DSI_CMD_PKT_STATUS_GEN_CMD_FULL_MASK               (0x1U << DSI_CMD_PKT_STATUS_GEN_CMD_FULL_SHIFT)              /* 0x00000002 */
#define DSI_CMD_PKT_STATUS_GEN_PLD_W_EMPTY_SHIFT           (2U)
#define DSI_CMD_PKT_STATUS_GEN_PLD_W_EMPTY_MASK            (0x1U << DSI_CMD_PKT_STATUS_GEN_PLD_W_EMPTY_SHIFT)           /* 0x00000004 */
#define DSI_CMD_PKT_STATUS_GEN_PLD_W_FULL_SHIFT            (3U)
#define DSI_CMD_PKT_STATUS_GEN_PLD_W_FULL_MASK             (0x1U << DSI_CMD_PKT_STATUS_GEN_PLD_W_FULL_SHIFT)            /* 0x00000008 */
#define DSI_CMD_PKT_STATUS_GEN_PLD_R_EMPTY_SHIFT           (4U)
#define DSI_CMD_PKT_STATUS_GEN_PLD_R_EMPTY_MASK            (0x1U << DSI_CMD_PKT_STATUS_GEN_PLD_R_EMPTY_SHIFT)           /* 0x00000010 */
#define DSI_CMD_PKT_STATUS_GEN_PLD_R_FULL_SHIFT            (5U)
#define DSI_CMD_PKT_STATUS_GEN_PLD_R_FULL_MASK             (0x1U << DSI_CMD_PKT_STATUS_GEN_PLD_R_FULL_SHIFT)            /* 0x00000020 */
#define DSI_CMD_PKT_STATUS_GEN_RD_CMD_BUSY_SHIFT           (6U)
#define DSI_CMD_PKT_STATUS_GEN_RD_CMD_BUSY_MASK            (0x1U << DSI_CMD_PKT_STATUS_GEN_RD_CMD_BUSY_SHIFT)           /* 0x00000040 */
#define DSI_CMD_PKT_STATUS_DBI_CMD_EMPTY_SHIFT             (8U)
#define DSI_CMD_PKT_STATUS_DBI_CMD_EMPTY_MASK              (0x1U << DSI_CMD_PKT_STATUS_DBI_CMD_EMPTY_SHIFT)             /* 0x00000100 */
#define DSI_CMD_PKT_STATUS_DBI_CMD_FULL_SHIFT              (9U)
#define DSI_CMD_PKT_STATUS_DBI_CMD_FULL_MASK               (0x1U << DSI_CMD_PKT_STATUS_DBI_CMD_FULL_SHIFT)              /* 0x00000200 */
#define DSI_CMD_PKT_STATUS_DBI_PLD_W_EMPTY_SHIFT           (10U)
#define DSI_CMD_PKT_STATUS_DBI_PLD_W_EMPTY_MASK            (0x1U << DSI_CMD_PKT_STATUS_DBI_PLD_W_EMPTY_SHIFT)           /* 0x00000400 */
#define DSI_CMD_PKT_STATUS_DBI_PLD_W_FULL_SHIFT            (11U)
#define DSI_CMD_PKT_STATUS_DBI_PLD_W_FULL_MASK             (0x1U << DSI_CMD_PKT_STATUS_DBI_PLD_W_FULL_SHIFT)            /* 0x00000800 */
#define DSI_CMD_PKT_STATUS_DBI_PLD_R_EMPTY_SHIFT           (12U)
#define DSI_CMD_PKT_STATUS_DBI_PLD_R_EMPTY_MASK            (0x1U << DSI_CMD_PKT_STATUS_DBI_PLD_R_EMPTY_SHIFT)           /* 0x00001000 */
#define DSI_CMD_PKT_STATUS_DBI_PLD_R_FULL_SHIFT            (13U)
#define DSI_CMD_PKT_STATUS_DBI_PLD_R_FULL_MASK             (0x1U << DSI_CMD_PKT_STATUS_DBI_PLD_R_FULL_SHIFT)            /* 0x00002000 */
#define DSI_CMD_PKT_STATUS_DBI_RD_CMD_BUSY_SHIFT           (14U)
#define DSI_CMD_PKT_STATUS_DBI_RD_CMD_BUSY_MASK            (0x1U << DSI_CMD_PKT_STATUS_DBI_RD_CMD_BUSY_SHIFT)           /* 0x00004000 */
/* TO_CNT_CFG */
#define DSI_TO_CNT_CFG_OFFSET                              (0x78U)
#define DSI_TO_CNT_CFG_LPRX_TO_CNT_SHIFT                   (0U)
#define DSI_TO_CNT_CFG_LPRX_TO_CNT_MASK                    (0xFFFFU << DSI_TO_CNT_CFG_LPRX_TO_CNT_SHIFT)                /* 0x0000FFFF */
#define DSI_TO_CNT_CFG_HSTX_TO_CNT_SHIFT                   (16U)
#define DSI_TO_CNT_CFG_HSTX_TO_CNT_MASK                    (0xFFFFU << DSI_TO_CNT_CFG_HSTX_TO_CNT_SHIFT)                /* 0xFFFF0000 */
/* HS_RD_TO_CNT */
#define DSI_HS_RD_TO_CNT_OFFSET                            (0x7CU)
#define DSI_HS_RD_TO_CNT_HS_RD_TO_CNT_SHIFT                (0U)
#define DSI_HS_RD_TO_CNT_HS_RD_TO_CNT_MASK                 (0xFFFFU << DSI_HS_RD_TO_CNT_HS_RD_TO_CNT_SHIFT)             /* 0x0000FFFF */
/* LP_RD_TO_CNT */
#define DSI_LP_RD_TO_CNT_OFFSET                            (0x80U)
#define DSI_LP_RD_TO_CNT_LP_RD_TO_CNT_SHIFT                (0U)
#define DSI_LP_RD_TO_CNT_LP_RD_TO_CNT_MASK                 (0xFFFFU << DSI_LP_RD_TO_CNT_LP_RD_TO_CNT_SHIFT)             /* 0x0000FFFF */
/* HS_WR_TO_CNT */
#define DSI_HS_WR_TO_CNT_OFFSET                            (0x84U)
#define DSI_HS_WR_TO_CNT_HS_WR_TO_CNT_SHIFT                (0U)
#define DSI_HS_WR_TO_CNT_HS_WR_TO_CNT_MASK                 (0xFFFFU << DSI_HS_WR_TO_CNT_HS_WR_TO_CNT_SHIFT)             /* 0x0000FFFF */
#define DSI_HS_WR_TO_CNT_PRESP_TO_MODE_SHIFT               (24U)
#define DSI_HS_WR_TO_CNT_PRESP_TO_MODE_MASK                (0x1U << DSI_HS_WR_TO_CNT_PRESP_TO_MODE_SHIFT)               /* 0x01000000 */
/* LP_WR_TO_CNT */
#define DSI_LP_WR_TO_CNT_OFFSET                            (0x88U)
#define DSI_LP_WR_TO_CNT_LP_WR_TO_CNT_SHIFT                (0U)
#define DSI_LP_WR_TO_CNT_LP_WR_TO_CNT_MASK                 (0xFFFFU << DSI_LP_WR_TO_CNT_LP_WR_TO_CNT_SHIFT)             /* 0x0000FFFF */
/* BTA_TO_CNT */
#define DSI_BTA_TO_CNT_OFFSET                              (0x8CU)
#define DSI_BTA_TO_CNT_BTA_TO_CNT_SHIFT                    (0U)
#define DSI_BTA_TO_CNT_BTA_TO_CNT_MASK                     (0xFFFFU << DSI_BTA_TO_CNT_BTA_TO_CNT_SHIFT)                 /* 0x0000FFFF */
/* SDF_3D */
#define DSI_SDF_3D_OFFSET                                  (0x90U)
#define DSI_SDF_3D_MODE_3D_SHIFT                           (0U)
#define DSI_SDF_3D_MODE_3D_MASK                            (0x3U << DSI_SDF_3D_MODE_3D_SHIFT)                           /* 0x00000003 */
#define DSI_SDF_3D_FORMAT_3D_SHIFT                         (2U)
#define DSI_SDF_3D_FORMAT_3D_MASK                          (0x3U << DSI_SDF_3D_FORMAT_3D_SHIFT)                         /* 0x0000000C */
#define DSI_SDF_3D_SECOND_VSYNC_SHIFT                      (4U)
#define DSI_SDF_3D_SECOND_VSYNC_MASK                       (0x1U << DSI_SDF_3D_SECOND_VSYNC_SHIFT)                      /* 0x00000010 */
#define DSI_SDF_3D_RIGHT_FIRST_SHIFT                       (5U)
#define DSI_SDF_3D_RIGHT_FIRST_MASK                        (0x1U << DSI_SDF_3D_RIGHT_FIRST_SHIFT)                       /* 0x00000020 */
#define DSI_SDF_3D_SEND_3D_CFG_SHIFT                       (16U)
#define DSI_SDF_3D_SEND_3D_CFG_MASK                        (0x1U << DSI_SDF_3D_SEND_3D_CFG_SHIFT)                       /* 0x00010000 */
/* LPCLK_CTRL */
#define DSI_LPCLK_CTRL_OFFSET                              (0x94U)
#define DSI_LPCLK_CTRL_PHY_TXREQUESTCLKHS_SHIFT            (0U)
#define DSI_LPCLK_CTRL_PHY_TXREQUESTCLKHS_MASK             (0x1U << DSI_LPCLK_CTRL_PHY_TXREQUESTCLKHS_SHIFT)            /* 0x00000001 */
#define DSI_LPCLK_CTRL_AUTO_CLKLANE_CTRL_SHIFT             (1U)
#define DSI_LPCLK_CTRL_AUTO_CLKLANE_CTRL_MASK              (0x1U << DSI_LPCLK_CTRL_AUTO_CLKLANE_CTRL_SHIFT)             /* 0x00000002 */
/* PHY_TMR_LPCLK_CFG */
#define DSI_PHY_TMR_LPCLK_CFG_OFFSET                       (0x98U)
#define DSI_PHY_TMR_LPCLK_CFG_PHY_CLKLP2HS_TIME_SHIFT      (0U)
#define DSI_PHY_TMR_LPCLK_CFG_PHY_CLKLP2HS_TIME_MASK       (0x3FFU << DSI_PHY_TMR_LPCLK_CFG_PHY_CLKLP2HS_TIME_SHIFT)    /* 0x000003FF */
#define DSI_PHY_TMR_LPCLK_CFG_PHY_CLKHS2LP_TIME_SHIFT      (16U)
#define DSI_PHY_TMR_LPCLK_CFG_PHY_CLKHS2LP_TIME_MASK       (0x3FFU << DSI_PHY_TMR_LPCLK_CFG_PHY_CLKHS2LP_TIME_SHIFT)    /* 0x03FF0000 */
/* PHY_TMR_CFG */
#define DSI_PHY_TMR_CFG_OFFSET                             (0x9CU)
#define DSI_PHY_TMR_CFG_MAX_RD_TIME_SHIFT                  (0U)
#define DSI_PHY_TMR_CFG_MAX_RD_TIME_MASK                   (0x7FFFU << DSI_PHY_TMR_CFG_MAX_RD_TIME_SHIFT)               /* 0x00007FFF */
#define DSI_PHY_TMR_CFG_PHY_LP2HS_TIME_SHIFT               (16U)
#define DSI_PHY_TMR_CFG_PHY_LP2HS_TIME_MASK                (0xFFU << DSI_PHY_TMR_CFG_PHY_LP2HS_TIME_SHIFT)              /* 0x00FF0000 */
#define DSI_PHY_TMR_CFG_PHY_HS2LP_TIME_SHIFT               (24U)
#define DSI_PHY_TMR_CFG_PHY_HS2LP_TIME_MASK                (0xFFU << DSI_PHY_TMR_CFG_PHY_HS2LP_TIME_SHIFT)              /* 0xFF000000 */
/* PHY_RSTZ */
#define DSI_PHY_RSTZ_OFFSET                                (0xA0U)
#define DSI_PHY_RSTZ_PHY_SHUTDOWNZ_SHIFT                   (0U)
#define DSI_PHY_RSTZ_PHY_SHUTDOWNZ_MASK                    (0x1U << DSI_PHY_RSTZ_PHY_SHUTDOWNZ_SHIFT)                   /* 0x00000001 */
#define DSI_PHY_RSTZ_PHY_RSTZ_SHIFT                        (1U)
#define DSI_PHY_RSTZ_PHY_RSTZ_MASK                         (0x1U << DSI_PHY_RSTZ_PHY_RSTZ_SHIFT)                        /* 0x00000002 */
#define DSI_PHY_RSTZ_PHY_ENABLECLK_SHIFT                   (2U)
#define DSI_PHY_RSTZ_PHY_ENABLECLK_MASK                    (0x1U << DSI_PHY_RSTZ_PHY_ENABLECLK_SHIFT)                   /* 0x00000004 */
#define DSI_PHY_RSTZ_PHY_FORCEPLL_SHIFT                    (3U)
#define DSI_PHY_RSTZ_PHY_FORCEPLL_MASK                     (0x1U << DSI_PHY_RSTZ_PHY_FORCEPLL_SHIFT)                    /* 0x00000008 */
/* PHY_IF_CFG */
#define DSI_PHY_IF_CFG_OFFSET                              (0xA4U)
#define DSI_PHY_IF_CFG_N_LANES_SHIFT                       (0U)
#define DSI_PHY_IF_CFG_N_LANES_MASK                        (0x3U << DSI_PHY_IF_CFG_N_LANES_SHIFT)                       /* 0x00000003 */
#define DSI_PHY_IF_CFG_PHY_STOP_WAIT_TIME_SHIFT            (8U)
#define DSI_PHY_IF_CFG_PHY_STOP_WAIT_TIME_MASK             (0xFFU << DSI_PHY_IF_CFG_PHY_STOP_WAIT_TIME_SHIFT)           /* 0x0000FF00 */
/* PHY_STATUS */
#define DSI_PHY_STATUS_OFFSET                              (0xB0U)
#define DSI_PHY_STATUS                                     (0x1528U)
#define DSI_PHY_STATUS_PHY_LOCK_SHIFT                      (0U)
#define DSI_PHY_STATUS_PHY_LOCK_MASK                       (0x1U << DSI_PHY_STATUS_PHY_LOCK_SHIFT)                      /* 0x00000001 */
#define DSI_PHY_STATUS_PHY_DIRECTION_SHIFT                 (1U)
#define DSI_PHY_STATUS_PHY_DIRECTION_MASK                  (0x1U << DSI_PHY_STATUS_PHY_DIRECTION_SHIFT)                 /* 0x00000002 */
#define DSI_PHY_STATUS_HPY_STOPSTATECLKLANE_SHIFT          (2U)
#define DSI_PHY_STATUS_HPY_STOPSTATECLKLANE_MASK           (0x1U << DSI_PHY_STATUS_HPY_STOPSTATECLKLANE_SHIFT)          /* 0x00000004 */
#define DSI_PHY_STATUS_PHY_ULPSACTIVENOTCLK_SHIFT          (3U)
#define DSI_PHY_STATUS_PHY_ULPSACTIVENOTCLK_MASK           (0x1U << DSI_PHY_STATUS_PHY_ULPSACTIVENOTCLK_SHIFT)          /* 0x00000008 */
#define DSI_PHY_STATUS_PHY_STOPSTATE0LANE_SHIFT            (4U)
#define DSI_PHY_STATUS_PHY_STOPSTATE0LANE_MASK             (0x1U << DSI_PHY_STATUS_PHY_STOPSTATE0LANE_SHIFT)            /* 0x00000010 */
#define DSI_PHY_STATUS_PHY_ULPSACTIVENOT0LANE_SHIFT        (5U)
#define DSI_PHY_STATUS_PHY_ULPSACTIVENOT0LANE_MASK         (0x1U << DSI_PHY_STATUS_PHY_ULPSACTIVENOT0LANE_SHIFT)        /* 0x00000020 */
#define DSI_PHY_STATUS_PHY_RXULPSESC0LANE_SHIFT            (6U)
#define DSI_PHY_STATUS_PHY_RXULPSESC0LANE_MASK             (0x1U << DSI_PHY_STATUS_PHY_RXULPSESC0LANE_SHIFT)            /* 0x00000040 */
#define DSI_PHY_STATUS_PHY_STOPSTATE1LANE_SHIFT            (7U)
#define DSI_PHY_STATUS_PHY_STOPSTATE1LANE_MASK             (0x1U << DSI_PHY_STATUS_PHY_STOPSTATE1LANE_SHIFT)            /* 0x00000080 */
#define DSI_PHY_STATUS_PHY_ULPSACTIVENOT1LANE_SHIFT        (8U)
#define DSI_PHY_STATUS_PHY_ULPSACTIVENOT1LANE_MASK         (0x1U << DSI_PHY_STATUS_PHY_ULPSACTIVENOT1LANE_SHIFT)        /* 0x00000100 */
#define DSI_PHY_STATUS_PHY_STOPSTATE2LANE_SHIFT            (9U)
#define DSI_PHY_STATUS_PHY_STOPSTATE2LANE_MASK             (0x1U << DSI_PHY_STATUS_PHY_STOPSTATE2LANE_SHIFT)            /* 0x00000200 */
#define DSI_PHY_STATUS_PHY_ULPSACTIVENOT2LANE_SHIFT        (10U)
#define DSI_PHY_STATUS_PHY_ULPSACTIVENOT2LANE_MASK         (0x1U << DSI_PHY_STATUS_PHY_ULPSACTIVENOT2LANE_SHIFT)        /* 0x00000400 */
#define DSI_PHY_STATUS_PHY_STOPSTATELANE_SHIFT             (11U)
#define DSI_PHY_STATUS_PHY_STOPSTATELANE_MASK              (0x1U << DSI_PHY_STATUS_PHY_STOPSTATELANE_SHIFT)             /* 0x00000800 */
#define DSI_PHY_STATUS_PHY_ULPSACTIVENOT3LANE_SHIFT        (12U)
#define DSI_PHY_STATUS_PHY_ULPSACTIVENOT3LANE_MASK         (0x1U << DSI_PHY_STATUS_PHY_ULPSACTIVENOT3LANE_SHIFT)        /* 0x00001000 */
/* INT_ST0 */
#define DSI_INT_ST0_OFFSET                                 (0xBCU)
#define DSI_INT_ST0                                        (0x0U)
#define DSI_INT_ST0_ACK_WITH_ERR_0_SHIFT                   (0U)
#define DSI_INT_ST0_ACK_WITH_ERR_0_MASK                    (0x1U << DSI_INT_ST0_ACK_WITH_ERR_0_SHIFT)                   /* 0x00000001 */
#define DSI_INT_ST0_ACK_WITH_ERR_1_SHIFT                   (1U)
#define DSI_INT_ST0_ACK_WITH_ERR_1_MASK                    (0x1U << DSI_INT_ST0_ACK_WITH_ERR_1_SHIFT)                   /* 0x00000002 */
#define DSI_INT_ST0_ACK_WITH_ERR_2_SHIFT                   (2U)
#define DSI_INT_ST0_ACK_WITH_ERR_2_MASK                    (0x1U << DSI_INT_ST0_ACK_WITH_ERR_2_SHIFT)                   /* 0x00000004 */
#define DSI_INT_ST0_ACK_WITH_ERR_3_SHIFT                   (3U)
#define DSI_INT_ST0_ACK_WITH_ERR_3_MASK                    (0x1U << DSI_INT_ST0_ACK_WITH_ERR_3_SHIFT)                   /* 0x00000008 */
#define DSI_INT_ST0_ACK_WITH_ERR_4_SHIFT                   (4U)
#define DSI_INT_ST0_ACK_WITH_ERR_4_MASK                    (0x1U << DSI_INT_ST0_ACK_WITH_ERR_4_SHIFT)                   /* 0x00000010 */
#define DSI_INT_ST0_ACK_WITH_ERR_5_SHIFT                   (5U)
#define DSI_INT_ST0_ACK_WITH_ERR_5_MASK                    (0x1U << DSI_INT_ST0_ACK_WITH_ERR_5_SHIFT)                   /* 0x00000020 */
#define DSI_INT_ST0_ACK_WITH_ERR_6_SHIFT                   (6U)
#define DSI_INT_ST0_ACK_WITH_ERR_6_MASK                    (0x1U << DSI_INT_ST0_ACK_WITH_ERR_6_SHIFT)                   /* 0x00000040 */
#define DSI_INT_ST0_ACK_WITH_ERR_7_SHIFT                   (7U)
#define DSI_INT_ST0_ACK_WITH_ERR_7_MASK                    (0x1U << DSI_INT_ST0_ACK_WITH_ERR_7_SHIFT)                   /* 0x00000080 */
#define DSI_INT_ST0_ACK_WITH_ERR_8_SHIFT                   (8U)
#define DSI_INT_ST0_ACK_WITH_ERR_8_MASK                    (0x1U << DSI_INT_ST0_ACK_WITH_ERR_8_SHIFT)                   /* 0x00000100 */
#define DSI_INT_ST0_ACK_WITH_ERR_9_SHIFT                   (9U)
#define DSI_INT_ST0_ACK_WITH_ERR_9_MASK                    (0x1U << DSI_INT_ST0_ACK_WITH_ERR_9_SHIFT)                   /* 0x00000200 */
#define DSI_INT_ST0_ACK_WITH_ERR_10_SHIFT                  (10U)
#define DSI_INT_ST0_ACK_WITH_ERR_10_MASK                   (0x1U << DSI_INT_ST0_ACK_WITH_ERR_10_SHIFT)                  /* 0x00000400 */
#define DSI_INT_ST0_ACK_WITH_ERR_11_SHIFT                  (11U)
#define DSI_INT_ST0_ACK_WITH_ERR_11_MASK                   (0x1U << DSI_INT_ST0_ACK_WITH_ERR_11_SHIFT)                  /* 0x00000800 */
#define DSI_INT_ST0_ACK_WITH_ERR_12_SHIFT                  (12U)
#define DSI_INT_ST0_ACK_WITH_ERR_12_MASK                   (0x1U << DSI_INT_ST0_ACK_WITH_ERR_12_SHIFT)                  /* 0x00001000 */
#define DSI_INT_ST0_ACK_WITH_ERR_13_SHIFT                  (13U)
#define DSI_INT_ST0_ACK_WITH_ERR_13_MASK                   (0x1U << DSI_INT_ST0_ACK_WITH_ERR_13_SHIFT)                  /* 0x00002000 */
#define DSI_INT_ST0_ACK_WITH_ERR_14_SHIFT                  (14U)
#define DSI_INT_ST0_ACK_WITH_ERR_14_MASK                   (0x1U << DSI_INT_ST0_ACK_WITH_ERR_14_SHIFT)                  /* 0x00004000 */
#define DSI_INT_ST0_ACK_WITH_ERR_15_SHIFT                  (15U)
#define DSI_INT_ST0_ACK_WITH_ERR_15_MASK                   (0x1U << DSI_INT_ST0_ACK_WITH_ERR_15_SHIFT)                  /* 0x00008000 */
#define DSI_INT_ST0_DPHY_ERRORS_0_SHIFT                    (16U)
#define DSI_INT_ST0_DPHY_ERRORS_0_MASK                     (0x1U << DSI_INT_ST0_DPHY_ERRORS_0_SHIFT)                    /* 0x00010000 */
#define DSI_INT_ST0_DPHY_ERRORS_1_SHIFT                    (17U)
#define DSI_INT_ST0_DPHY_ERRORS_1_MASK                     (0x1U << DSI_INT_ST0_DPHY_ERRORS_1_SHIFT)                    /* 0x00020000 */
#define DSI_INT_ST0_DPHY_ERRORS_2_SHIFT                    (18U)
#define DSI_INT_ST0_DPHY_ERRORS_2_MASK                     (0x1U << DSI_INT_ST0_DPHY_ERRORS_2_SHIFT)                    /* 0x00040000 */
#define DSI_INT_ST0_DPHY_ERRORS_3_SHIFT                    (19U)
#define DSI_INT_ST0_DPHY_ERRORS_3_MASK                     (0x1U << DSI_INT_ST0_DPHY_ERRORS_3_SHIFT)                    /* 0x00080000 */
#define DSI_INT_ST0_DPHY_ERRORS_4_SHIFT                    (20U)
#define DSI_INT_ST0_DPHY_ERRORS_4_MASK                     (0x1U << DSI_INT_ST0_DPHY_ERRORS_4_SHIFT)                    /* 0x00100000 */
/* INT_ST1 */
#define DSI_INT_ST1_OFFSET                                 (0xC0U)
#define DSI_INT_ST1                                        (0x0U)
#define DSI_INT_ST1_TO_HS_TX_SHIFT                         (0U)
#define DSI_INT_ST1_TO_HS_TX_MASK                          (0x1U << DSI_INT_ST1_TO_HS_TX_SHIFT)                         /* 0x00000001 */
#define DSI_INT_ST1_TO_LP_RX_SHIFT                         (1U)
#define DSI_INT_ST1_TO_LP_RX_MASK                          (0x1U << DSI_INT_ST1_TO_LP_RX_SHIFT)                         /* 0x00000002 */
#define DSI_INT_ST1_ECC_SINGLE_ERR_SHIFT                   (2U)
#define DSI_INT_ST1_ECC_SINGLE_ERR_MASK                    (0x1U << DSI_INT_ST1_ECC_SINGLE_ERR_SHIFT)                   /* 0x00000004 */
#define DSI_INT_ST1_ECC_MULTI_ERR_SHIFT                    (3U)
#define DSI_INT_ST1_ECC_MULTI_ERR_MASK                     (0x1U << DSI_INT_ST1_ECC_MULTI_ERR_SHIFT)                    /* 0x00000008 */
#define DSI_INT_ST1_CRC_ERR_SHIFT                          (4U)
#define DSI_INT_ST1_CRC_ERR_MASK                           (0x1U << DSI_INT_ST1_CRC_ERR_SHIFT)                          /* 0x00000010 */
#define DSI_INT_ST1_PKT_SIZE_ERR_SHIFT                     (5U)
#define DSI_INT_ST1_PKT_SIZE_ERR_MASK                      (0x1U << DSI_INT_ST1_PKT_SIZE_ERR_SHIFT)                     /* 0x00000020 */
#define DSI_INT_ST1_EOPT_ERR_SHIFT                         (6U)
#define DSI_INT_ST1_EOPT_ERR_MASK                          (0x1U << DSI_INT_ST1_EOPT_ERR_SHIFT)                         /* 0x00000040 */
#define DSI_INT_ST1_DPI_PLD_WR_ERR_SHIFT                   (7U)
#define DSI_INT_ST1_DPI_PLD_WR_ERR_MASK                    (0x1U << DSI_INT_ST1_DPI_PLD_WR_ERR_SHIFT)                   /* 0x00000080 */
#define DSI_INT_ST1_GEN_CMD_WR_ERR_SHIFT                   (8U)
#define DSI_INT_ST1_GEN_CMD_WR_ERR_MASK                    (0x1U << DSI_INT_ST1_GEN_CMD_WR_ERR_SHIFT)                   /* 0x00000100 */
#define DSI_INT_ST1_GEN_PLD_WR_ERR_SHIFT                   (9U)
#define DSI_INT_ST1_GEN_PLD_WR_ERR_MASK                    (0x1U << DSI_INT_ST1_GEN_PLD_WR_ERR_SHIFT)                   /* 0x00000200 */
#define DSI_INT_ST1_GEN_PLD_SEND_ERR_SHIFT                 (10U)
#define DSI_INT_ST1_GEN_PLD_SEND_ERR_MASK                  (0x1U << DSI_INT_ST1_GEN_PLD_SEND_ERR_SHIFT)                 /* 0x00000400 */
#define DSI_INT_ST1_GEN_PLD_RD_ERR_SHIFT                   (11U)
#define DSI_INT_ST1_GEN_PLD_RD_ERR_MASK                    (0x1U << DSI_INT_ST1_GEN_PLD_RD_ERR_SHIFT)                   /* 0x00000800 */
#define DSI_INT_ST1_GEN_PLD_RECEV_ERR_SHIFT                (12U)
#define DSI_INT_ST1_GEN_PLD_RECEV_ERR_MASK                 (0x1U << DSI_INT_ST1_GEN_PLD_RECEV_ERR_SHIFT)                /* 0x00001000 */
#define DSI_INT_ST1_DBI_CMD_WR_ERR_SHIFT                   (13U)
#define DSI_INT_ST1_DBI_CMD_WR_ERR_MASK                    (0x1U << DSI_INT_ST1_DBI_CMD_WR_ERR_SHIFT)                   /* 0x00002000 */
#define DSI_INT_ST1_DBI_PLD_WR_ERR_SHIFT                   (14U)
#define DSI_INT_ST1_DBI_PLD_WR_ERR_MASK                    (0x1U << DSI_INT_ST1_DBI_PLD_WR_ERR_SHIFT)                   /* 0x00004000 */
#define DSI_INT_ST1_DBI_PLD_RD_ERR_SHIFT                   (15U)
#define DSI_INT_ST1_DBI_PLD_RD_ERR_MASK                    (0x1U << DSI_INT_ST1_DBI_PLD_RD_ERR_SHIFT)                   /* 0x00008000 */
#define DSI_INT_ST1_DBI_PLD_RECV_ERR_SHIFT                 (16U)
#define DSI_INT_ST1_DBI_PLD_RECV_ERR_MASK                  (0x1U << DSI_INT_ST1_DBI_PLD_RECV_ERR_SHIFT)                 /* 0x00010000 */
#define DSI_INT_ST1_DBI_ILEGAL_COMM_ERR_SHIFT              (17U)
#define DSI_INT_ST1_DBI_ILEGAL_COMM_ERR_MASK               (0x1U << DSI_INT_ST1_DBI_ILEGAL_COMM_ERR_SHIFT)              /* 0x00020000 */
/* INT_MSK0 */
#define DSI_INT_MSK0_OFFSET                                (0xC4U)
#define DSI_INT_MSK0_ACK_WITH_ERR_0_SHIFT                  (0U)
#define DSI_INT_MSK0_ACK_WITH_ERR_0_MASK                   (0x1U << DSI_INT_MSK0_ACK_WITH_ERR_0_SHIFT)                  /* 0x00000001 */
#define DSI_INT_MSK0_ACK_WITH_ERR_1_SHIFT                  (1U)
#define DSI_INT_MSK0_ACK_WITH_ERR_1_MASK                   (0x1U << DSI_INT_MSK0_ACK_WITH_ERR_1_SHIFT)                  /* 0x00000002 */
#define DSI_INT_MSK0_ACK_WITH_ERR_2_SHIFT                  (2U)
#define DSI_INT_MSK0_ACK_WITH_ERR_2_MASK                   (0x1U << DSI_INT_MSK0_ACK_WITH_ERR_2_SHIFT)                  /* 0x00000004 */
#define DSI_INT_MSK0_ACK_WITH_ERR_3_SHIFT                  (3U)
#define DSI_INT_MSK0_ACK_WITH_ERR_3_MASK                   (0x1U << DSI_INT_MSK0_ACK_WITH_ERR_3_SHIFT)                  /* 0x00000008 */
#define DSI_INT_MSK0_ACK_WITH_ERR_4_SHIFT                  (4U)
#define DSI_INT_MSK0_ACK_WITH_ERR_4_MASK                   (0x1U << DSI_INT_MSK0_ACK_WITH_ERR_4_SHIFT)                  /* 0x00000010 */
#define DSI_INT_MSK0_ACK_WITH_ERR_5_SHIFT                  (5U)
#define DSI_INT_MSK0_ACK_WITH_ERR_5_MASK                   (0x1U << DSI_INT_MSK0_ACK_WITH_ERR_5_SHIFT)                  /* 0x00000020 */
#define DSI_INT_MSK0_ACK_WITH_ERR_6_SHIFT                  (6U)
#define DSI_INT_MSK0_ACK_WITH_ERR_6_MASK                   (0x1U << DSI_INT_MSK0_ACK_WITH_ERR_6_SHIFT)                  /* 0x00000040 */
#define DSI_INT_MSK0_ACK_WITH_ERR_7_SHIFT                  (7U)
#define DSI_INT_MSK0_ACK_WITH_ERR_7_MASK                   (0x1U << DSI_INT_MSK0_ACK_WITH_ERR_7_SHIFT)                  /* 0x00000080 */
#define DSI_INT_MSK0_ACK_WITH_ERR_8_SHIFT                  (8U)
#define DSI_INT_MSK0_ACK_WITH_ERR_8_MASK                   (0x1U << DSI_INT_MSK0_ACK_WITH_ERR_8_SHIFT)                  /* 0x00000100 */
#define DSI_INT_MSK0_ACK_WITH_ERR_9_SHIFT                  (9U)
#define DSI_INT_MSK0_ACK_WITH_ERR_9_MASK                   (0x1U << DSI_INT_MSK0_ACK_WITH_ERR_9_SHIFT)                  /* 0x00000200 */
#define DSI_INT_MSK0_ACK_WITH_ERR_10_SHIFT                 (10U)
#define DSI_INT_MSK0_ACK_WITH_ERR_10_MASK                  (0x1U << DSI_INT_MSK0_ACK_WITH_ERR_10_SHIFT)                 /* 0x00000400 */
#define DSI_INT_MSK0_ACK_WITH_ERR_11_SHIFT                 (11U)
#define DSI_INT_MSK0_ACK_WITH_ERR_11_MASK                  (0x1U << DSI_INT_MSK0_ACK_WITH_ERR_11_SHIFT)                 /* 0x00000800 */
#define DSI_INT_MSK0_ACK_WITH_ERR_12_SHIFT                 (12U)
#define DSI_INT_MSK0_ACK_WITH_ERR_12_MASK                  (0x1U << DSI_INT_MSK0_ACK_WITH_ERR_12_SHIFT)                 /* 0x00001000 */
#define DSI_INT_MSK0_ACK_WITH_ERR_13_SHIFT                 (13U)
#define DSI_INT_MSK0_ACK_WITH_ERR_13_MASK                  (0x1U << DSI_INT_MSK0_ACK_WITH_ERR_13_SHIFT)                 /* 0x00002000 */
#define DSI_INT_MSK0_ACK_WITH_ERR_14_SHIFT                 (14U)
#define DSI_INT_MSK0_ACK_WITH_ERR_14_MASK                  (0x1U << DSI_INT_MSK0_ACK_WITH_ERR_14_SHIFT)                 /* 0x00004000 */
#define DSI_INT_MSK0_ACK_WITH_ERR_15_SHIFT                 (15U)
#define DSI_INT_MSK0_ACK_WITH_ERR_15_MASK                  (0x1U << DSI_INT_MSK0_ACK_WITH_ERR_15_SHIFT)                 /* 0x00008000 */
#define DSI_INT_MSK0_DPHY_ERRORS_0_SHIFT                   (16U)
#define DSI_INT_MSK0_DPHY_ERRORS_0_MASK                    (0x1U << DSI_INT_MSK0_DPHY_ERRORS_0_SHIFT)                   /* 0x00010000 */
#define DSI_INT_MSK0_DPHY_ERRORS_1_SHIFT                   (17U)
#define DSI_INT_MSK0_DPHY_ERRORS_1_MASK                    (0x1U << DSI_INT_MSK0_DPHY_ERRORS_1_SHIFT)                   /* 0x00020000 */
#define DSI_INT_MSK0_DPHY_ERRORS_2_SHIFT                   (18U)
#define DSI_INT_MSK0_DPHY_ERRORS_2_MASK                    (0x1U << DSI_INT_MSK0_DPHY_ERRORS_2_SHIFT)                   /* 0x00040000 */
#define DSI_INT_MSK0_DPHY_ERRORS_3_SHIFT                   (19U)
#define DSI_INT_MSK0_DPHY_ERRORS_3_MASK                    (0x1U << DSI_INT_MSK0_DPHY_ERRORS_3_SHIFT)                   /* 0x00080000 */
#define DSI_INT_MSK0_DPHY_ERRORS_4_SHIFT                   (20U)
#define DSI_INT_MSK0_DPHY_ERRORS_4_MASK                    (0x1U << DSI_INT_MSK0_DPHY_ERRORS_4_SHIFT)                   /* 0x00100000 */
/* INT_MSK1 */
#define DSI_INT_MSK1_OFFSET                                (0xC8U)
#define DSI_INT_MSK1_TO_HS_TX_SHIFT                        (0U)
#define DSI_INT_MSK1_TO_HS_TX_MASK                         (0x1U << DSI_INT_MSK1_TO_HS_TX_SHIFT)                        /* 0x00000001 */
#define DSI_INT_MSK1_TO_LP_RX_SHIFT                        (1U)
#define DSI_INT_MSK1_TO_LP_RX_MASK                         (0x1U << DSI_INT_MSK1_TO_LP_RX_SHIFT)                        /* 0x00000002 */
#define DSI_INT_MSK1_ECC_SINGLE_ERR_SHIFT                  (2U)
#define DSI_INT_MSK1_ECC_SINGLE_ERR_MASK                   (0x1U << DSI_INT_MSK1_ECC_SINGLE_ERR_SHIFT)                  /* 0x00000004 */
#define DSI_INT_MSK1_ECC_MILTI_ERR_SHIFT                   (3U)
#define DSI_INT_MSK1_ECC_MILTI_ERR_MASK                    (0x1U << DSI_INT_MSK1_ECC_MILTI_ERR_SHIFT)                   /* 0x00000008 */
#define DSI_INT_MSK1_CRC_ERR_SHIFT                         (4U)
#define DSI_INT_MSK1_CRC_ERR_MASK                          (0x1U << DSI_INT_MSK1_CRC_ERR_SHIFT)                         /* 0x00000010 */
#define DSI_INT_MSK1_PKT_SIZE_ERR_SHIFT                    (5U)
#define DSI_INT_MSK1_PKT_SIZE_ERR_MASK                     (0x1U << DSI_INT_MSK1_PKT_SIZE_ERR_SHIFT)                    /* 0x00000020 */
#define DSI_INT_MSK1_EOPT_ERR_SHIFT                        (6U)
#define DSI_INT_MSK1_EOPT_ERR_MASK                         (0x1U << DSI_INT_MSK1_EOPT_ERR_SHIFT)                        /* 0x00000040 */
#define DSI_INT_MSK1_DPI_PLD_WR_ERR_SHIFT                  (7U)
#define DSI_INT_MSK1_DPI_PLD_WR_ERR_MASK                   (0x1U << DSI_INT_MSK1_DPI_PLD_WR_ERR_SHIFT)                  /* 0x00000080 */
#define DSI_INT_MSK1_GEN_CMD_WR_ERR_SHIFT                  (8U)
#define DSI_INT_MSK1_GEN_CMD_WR_ERR_MASK                   (0x1U << DSI_INT_MSK1_GEN_CMD_WR_ERR_SHIFT)                  /* 0x00000100 */
#define DSI_INT_MSK1_GEN_PLD_WR_ERR_SHIFT                  (9U)
#define DSI_INT_MSK1_GEN_PLD_WR_ERR_MASK                   (0x1U << DSI_INT_MSK1_GEN_PLD_WR_ERR_SHIFT)                  /* 0x00000200 */
#define DSI_INT_MSK1_GEN_PLD_SEND_ERR_SHIFT                (10U)
#define DSI_INT_MSK1_GEN_PLD_SEND_ERR_MASK                 (0x1U << DSI_INT_MSK1_GEN_PLD_SEND_ERR_SHIFT)                /* 0x00000400 */
#define DSI_INT_MSK1_GEN_PLD_RD_ERR_SHIFT                  (11U)
#define DSI_INT_MSK1_GEN_PLD_RD_ERR_MASK                   (0x1U << DSI_INT_MSK1_GEN_PLD_RD_ERR_SHIFT)                  /* 0x00000800 */
#define DSI_INT_MSK1_GEN_PLD_REVEV_ERR_SHIFT               (12U)
#define DSI_INT_MSK1_GEN_PLD_REVEV_ERR_MASK                (0x1U << DSI_INT_MSK1_GEN_PLD_REVEV_ERR_SHIFT)               /* 0x00001000 */
#define DSI_INT_MSK1_DBI_CMD_WR_ERR_SHIFT                  (13U)
#define DSI_INT_MSK1_DBI_CMD_WR_ERR_MASK                   (0x1U << DSI_INT_MSK1_DBI_CMD_WR_ERR_SHIFT)                  /* 0x00002000 */
#define DSI_INT_MSK1_DBI_PLD_WR_ERR_SHIFT                  (14U)
#define DSI_INT_MSK1_DBI_PLD_WR_ERR_MASK                   (0x1U << DSI_INT_MSK1_DBI_PLD_WR_ERR_SHIFT)                  /* 0x00004000 */
#define DSI_INT_MSK1_DBI_PLD_RD_ERR_SHIFT                  (15U)
#define DSI_INT_MSK1_DBI_PLD_RD_ERR_MASK                   (0x1U << DSI_INT_MSK1_DBI_PLD_RD_ERR_SHIFT)                  /* 0x00008000 */
#define DSI_INT_MSK1_DBI_PLD_RECV_ERR_SHIFT                (16U)
#define DSI_INT_MSK1_DBI_PLD_RECV_ERR_MASK                 (0x1U << DSI_INT_MSK1_DBI_PLD_RECV_ERR_SHIFT)                /* 0x00010000 */
#define DSI_INT_MSK1_DBI_ILEGAL_COMM_ERR_SHIFT             (17U)
#define DSI_INT_MSK1_DBI_ILEGAL_COMM_ERR_MASK              (0x1U << DSI_INT_MSK1_DBI_ILEGAL_COMM_ERR_SHIFT)             /* 0x00020000 */
/* INT_FORCE0 */
#define DSI_INT_FORCE0_OFFSET                              (0xD8U)
#define DSI_INT_FORCE0_ACK_WITH_ERR_0_SHIFT                (0U)
#define DSI_INT_FORCE0_ACK_WITH_ERR_0_MASK                 (0x1U << DSI_INT_FORCE0_ACK_WITH_ERR_0_SHIFT)                /* 0x00000001 */
#define DSI_INT_FORCE0_ACK_WITH_ERR_1_SHIFT                (1U)
#define DSI_INT_FORCE0_ACK_WITH_ERR_1_MASK                 (0x1U << DSI_INT_FORCE0_ACK_WITH_ERR_1_SHIFT)                /* 0x00000002 */
#define DSI_INT_FORCE0_ACK_WITH_ERR_2_SHIFT                (2U)
#define DSI_INT_FORCE0_ACK_WITH_ERR_2_MASK                 (0x1U << DSI_INT_FORCE0_ACK_WITH_ERR_2_SHIFT)                /* 0x00000004 */
#define DSI_INT_FORCE0_ACK_WITH_ERR_3_SHIFT                (3U)
#define DSI_INT_FORCE0_ACK_WITH_ERR_3_MASK                 (0x1U << DSI_INT_FORCE0_ACK_WITH_ERR_3_SHIFT)                /* 0x00000008 */
#define DSI_INT_FORCE0_ACK_WITH_ERR_4_SHIFT                (4U)
#define DSI_INT_FORCE0_ACK_WITH_ERR_4_MASK                 (0x1U << DSI_INT_FORCE0_ACK_WITH_ERR_4_SHIFT)                /* 0x00000010 */
#define DSI_INT_FORCE0_ACK_WITH_ERR_5_SHIFT                (5U)
#define DSI_INT_FORCE0_ACK_WITH_ERR_5_MASK                 (0x1U << DSI_INT_FORCE0_ACK_WITH_ERR_5_SHIFT)                /* 0x00000020 */
#define DSI_INT_FORCE0_ACK_WITH_ERR_6_SHIFT                (6U)
#define DSI_INT_FORCE0_ACK_WITH_ERR_6_MASK                 (0x1U << DSI_INT_FORCE0_ACK_WITH_ERR_6_SHIFT)                /* 0x00000040 */
#define DSI_INT_FORCE0_ACK_WITH_ERR_7_SHIFT                (7U)
#define DSI_INT_FORCE0_ACK_WITH_ERR_7_MASK                 (0x1U << DSI_INT_FORCE0_ACK_WITH_ERR_7_SHIFT)                /* 0x00000080 */
#define DSI_INT_FORCE0_ACK_WITH_ERR_8_SHIFT                (8U)
#define DSI_INT_FORCE0_ACK_WITH_ERR_8_MASK                 (0x1U << DSI_INT_FORCE0_ACK_WITH_ERR_8_SHIFT)                /* 0x00000100 */
#define DSI_INT_FORCE0_ACK_WITH_ERR_9_SHIFT                (9U)
#define DSI_INT_FORCE0_ACK_WITH_ERR_9_MASK                 (0x1U << DSI_INT_FORCE0_ACK_WITH_ERR_9_SHIFT)                /* 0x00000200 */
#define DSI_INT_FORCE0_ACK_WITH_ERR_10_SHIFT               (10U)
#define DSI_INT_FORCE0_ACK_WITH_ERR_10_MASK                (0x1U << DSI_INT_FORCE0_ACK_WITH_ERR_10_SHIFT)               /* 0x00000400 */
#define DSI_INT_FORCE0_ACK_WITH_ERR_11_SHIFT               (11U)
#define DSI_INT_FORCE0_ACK_WITH_ERR_11_MASK                (0x1U << DSI_INT_FORCE0_ACK_WITH_ERR_11_SHIFT)               /* 0x00000800 */
#define DSI_INT_FORCE0_ACK_WITH_ERR_12_SHIFT               (12U)
#define DSI_INT_FORCE0_ACK_WITH_ERR_12_MASK                (0x1U << DSI_INT_FORCE0_ACK_WITH_ERR_12_SHIFT)               /* 0x00001000 */
#define DSI_INT_FORCE0_ACK_WITH_ERR_13_SHIFT               (13U)
#define DSI_INT_FORCE0_ACK_WITH_ERR_13_MASK                (0x1U << DSI_INT_FORCE0_ACK_WITH_ERR_13_SHIFT)               /* 0x00002000 */
#define DSI_INT_FORCE0_ACK_WITH_ERR_14_SHIFT               (14U)
#define DSI_INT_FORCE0_ACK_WITH_ERR_14_MASK                (0x1U << DSI_INT_FORCE0_ACK_WITH_ERR_14_SHIFT)               /* 0x00004000 */
#define DSI_INT_FORCE0_ACK_WITH_ERR_15_SHIFT               (15U)
#define DSI_INT_FORCE0_ACK_WITH_ERR_15_MASK                (0x1U << DSI_INT_FORCE0_ACK_WITH_ERR_15_SHIFT)               /* 0x00008000 */
#define DSI_INT_FORCE0_DPHY_ERRORS_0_SHIFT                 (16U)
#define DSI_INT_FORCE0_DPHY_ERRORS_0_MASK                  (0x1U << DSI_INT_FORCE0_DPHY_ERRORS_0_SHIFT)                 /* 0x00010000 */
#define DSI_INT_FORCE0_DPHY_ERRORS_1_SHIFT                 (17U)
#define DSI_INT_FORCE0_DPHY_ERRORS_1_MASK                  (0x1U << DSI_INT_FORCE0_DPHY_ERRORS_1_SHIFT)                 /* 0x00020000 */
#define DSI_INT_FORCE0_DPHY_ERRORS_2_SHIFT                 (18U)
#define DSI_INT_FORCE0_DPHY_ERRORS_2_MASK                  (0x1U << DSI_INT_FORCE0_DPHY_ERRORS_2_SHIFT)                 /* 0x00040000 */
#define DSI_INT_FORCE0_DPHY_ERRORS_3_SHIFT                 (19U)
#define DSI_INT_FORCE0_DPHY_ERRORS_3_MASK                  (0x1U << DSI_INT_FORCE0_DPHY_ERRORS_3_SHIFT)                 /* 0x00080000 */
#define DSI_INT_FORCE0_DPHY_ERRORS_4_SHIFT                 (20U)
#define DSI_INT_FORCE0_DPHY_ERRORS_4_MASK                  (0x1U << DSI_INT_FORCE0_DPHY_ERRORS_4_SHIFT)                 /* 0x00100000 */
/* INT_FORCE1 */
#define DSI_INT_FORCE1_OFFSET                              (0xDCU)
#define DSI_INT_FORCE1_TO_HS_TX_SHIFT                      (0U)
#define DSI_INT_FORCE1_TO_HS_TX_MASK                       (0x1U << DSI_INT_FORCE1_TO_HS_TX_SHIFT)                      /* 0x00000001 */
#define DSI_INT_FORCE1_TO_LP_RX_SHIFT                      (1U)
#define DSI_INT_FORCE1_TO_LP_RX_MASK                       (0x1U << DSI_INT_FORCE1_TO_LP_RX_SHIFT)                      /* 0x00000002 */
#define DSI_INT_FORCE1_ECC_SINGLE_ERR_SHIFT                (2U)
#define DSI_INT_FORCE1_ECC_SINGLE_ERR_MASK                 (0x1U << DSI_INT_FORCE1_ECC_SINGLE_ERR_SHIFT)                /* 0x00000004 */
#define DSI_INT_FORCE1_ECC_MILTI_ERR_SHIFT                 (3U)
#define DSI_INT_FORCE1_ECC_MILTI_ERR_MASK                  (0x1U << DSI_INT_FORCE1_ECC_MILTI_ERR_SHIFT)                 /* 0x00000008 */
#define DSI_INT_FORCE1_CRC_ERR_OR_RESERVED_SHIFT           (4U)
#define DSI_INT_FORCE1_CRC_ERR_OR_RESERVED_MASK            (0x1U << DSI_INT_FORCE1_CRC_ERR_OR_RESERVED_SHIFT)           /* 0x00000010 */
#define DSI_INT_FORCE1_PKT_SIZE_ERR_SHIFT                  (5U)
#define DSI_INT_FORCE1_PKT_SIZE_ERR_MASK                   (0x1U << DSI_INT_FORCE1_PKT_SIZE_ERR_SHIFT)                  /* 0x00000020 */
#define DSI_INT_FORCE1_EOPT_ERR_SHIFT                      (6U)
#define DSI_INT_FORCE1_EOPT_ERR_MASK                       (0x1U << DSI_INT_FORCE1_EOPT_ERR_SHIFT)                      /* 0x00000040 */
#define DSI_INT_FORCE1_DPI_PLD_WR_ERR_OR_RESERVED_SHIFT    (7U)
#define DSI_INT_FORCE1_DPI_PLD_WR_ERR_OR_RESERVED_MASK     (0x1U << DSI_INT_FORCE1_DPI_PLD_WR_ERR_OR_RESERVED_SHIFT)    /* 0x00000080 */
#define DSI_INT_FORCE1_GEN_CMD_WR_ERR_OR_RESERVED_SHIFT    (8U)
#define DSI_INT_FORCE1_GEN_CMD_WR_ERR_OR_RESERVED_MASK     (0x1U << DSI_INT_FORCE1_GEN_CMD_WR_ERR_OR_RESERVED_SHIFT)    /* 0x00000100 */
#define DSI_INT_FORCE1_GEN_PLD_WR_EN_OR_RESERVED_SHIFT     (9U)
#define DSI_INT_FORCE1_GEN_PLD_WR_EN_OR_RESERVED_MASK      (0x1U << DSI_INT_FORCE1_GEN_PLD_WR_EN_OR_RESERVED_SHIFT)     /* 0x00000200 */
#define DSI_INT_FORCE1_GEN_PLD_SEND_ERR_OR_RESERVE_SHIFT   (10U)
#define DSI_INT_FORCE1_GEN_PLD_SEND_ERR_OR_RESERVE_MASK    (0x1U << DSI_INT_FORCE1_GEN_PLD_SEND_ERR_OR_RESERVE_SHIFT)   /* 0x00000400 */
#define DSI_INT_FORCE1_GEN_PLD_RD_ERR_OR_RESERVED_SHIFT    (11U)
#define DSI_INT_FORCE1_GEN_PLD_RD_ERR_OR_RESERVED_MASK     (0x1U << DSI_INT_FORCE1_GEN_PLD_RD_ERR_OR_RESERVED_SHIFT)    /* 0x00000800 */
#define DSI_INT_FORCE1_GEN_PLD_RECEV_ERR_OR_RESERVED_SHIFT (12U)
#define DSI_INT_FORCE1_GEN_PLD_RECEV_ERR_OR_RESERVED_MASK  (0x1U << DSI_INT_FORCE1_GEN_PLD_RECEV_ERR_OR_RESERVED_SHIFT) /* 0x00001000 */
#define DSI_INT_FORCE1_DBI_CMD_WR_ERR_OR_RESERVED_SHIFT    (13U)
#define DSI_INT_FORCE1_DBI_CMD_WR_ERR_OR_RESERVED_MASK     (0x1U << DSI_INT_FORCE1_DBI_CMD_WR_ERR_OR_RESERVED_SHIFT)    /* 0x00002000 */
#define DSI_INT_FORCE1_DBI_PLD_WR_ERR_OR_RESERVED_SHIFT    (14U)
#define DSI_INT_FORCE1_DBI_PLD_WR_ERR_OR_RESERVED_MASK     (0x1U << DSI_INT_FORCE1_DBI_PLD_WR_ERR_OR_RESERVED_SHIFT)    /* 0x00004000 */
#define DSI_INT_FORCE1_DBI_PLD_RD_ERR_OR_RESERVED_SHIFT    (15U)
#define DSI_INT_FORCE1_DBI_PLD_RD_ERR_OR_RESERVED_MASK     (0x1U << DSI_INT_FORCE1_DBI_PLD_RD_ERR_OR_RESERVED_SHIFT)    /* 0x00008000 */
#define DSI_INT_FORCE1_DBI_PLD_RECV_ERR_OR_RESERVED_SHIFT  (16U)
#define DSI_INT_FORCE1_DBI_PLD_RECV_ERR_OR_RESERVED_MASK   (0x1U << DSI_INT_FORCE1_DBI_PLD_RECV_ERR_OR_RESERVED_SHIFT)  /* 0x00010000 */
#define DSI_INT_FORCE1_DBI_ILEGAL_COMM_ERR_OR_RESERVED_SHIFT (17U)
#define DSI_INT_FORCE1_DBI_ILEGAL_COMM_ERR_OR_RESERVED_MASK (0x1U << DSI_INT_FORCE1_DBI_ILEGAL_COMM_ERR_OR_RESERVED_SHIFT) /* 0x00020000 */
/* VID_SHADOW_CTRL */
#define DSI_VID_SHADOW_CTRL_OFFSET                         (0x100U)
#define DSI_VID_SHADOW_CTRL_VID_SHADOW_EN_SHIFT            (0U)
#define DSI_VID_SHADOW_CTRL_VID_SHADOW_EN_MASK             (0x1U << DSI_VID_SHADOW_CTRL_VID_SHADOW_EN_SHIFT)            /* 0x00000001 */
#define DSI_VID_SHADOW_CTRL_VID_SHADOW_REQ_SHIFT           (8U)
#define DSI_VID_SHADOW_CTRL_VID_SHADOW_REQ_MASK            (0x1U << DSI_VID_SHADOW_CTRL_VID_SHADOW_REQ_SHIFT)           /* 0x00000100 */
#define DSI_VID_SHADOW_CTRL_VID_SHADOW_PIN_REQ_SHIFT       (16U)
#define DSI_VID_SHADOW_CTRL_VID_SHADOW_PIN_REQ_MASK        (0x1U << DSI_VID_SHADOW_CTRL_VID_SHADOW_PIN_REQ_SHIFT)       /* 0x00010000 */
/* DPI_VCID_ACT */
#define DSI_DPI_VCID_ACT_OFFSET                            (0x10CU)
#define DSI_DPI_VCID_ACT                                   (0x0U)
#define DSI_DPI_VCID_ACT_DPI_VCID_SHIFT                    (0U)
#define DSI_DPI_VCID_ACT_DPI_VCID_MASK                     (0x3U << DSI_DPI_VCID_ACT_DPI_VCID_SHIFT)                    /* 0x00000003 */
/* DPI_COLOR_CODING_ACT */
#define DSI_DPI_COLOR_CODING_ACT_OFFSET                    (0x110U)
#define DSI_DPI_COLOR_CODING_ACT                           (0x0U)
#define DSI_DPI_COLOR_CODING_ACT_DPI_COLOR_CODING_SHIFT    (0U)
#define DSI_DPI_COLOR_CODING_ACT_DPI_COLOR_CODING_MASK     (0xFU << DSI_DPI_COLOR_CODING_ACT_DPI_COLOR_CODING_SHIFT)    /* 0x0000000F */
#define DSI_DPI_COLOR_CODING_ACT_LOOSELY18_EN_SHIFT        (8U)
#define DSI_DPI_COLOR_CODING_ACT_LOOSELY18_EN_MASK         (0x1U << DSI_DPI_COLOR_CODING_ACT_LOOSELY18_EN_SHIFT)        /* 0x00000100 */
/* DPI_LP_CMD_TIM_ACT */
#define DSI_DPI_LP_CMD_TIM_ACT_OFFSET                      (0x118U)
#define DSI_DPI_LP_CMD_TIM_ACT                             (0x0U)
#define DSI_DPI_LP_CMD_TIM_ACT_INVACT_LPCMD_TIME_SHIFT     (0U)
#define DSI_DPI_LP_CMD_TIM_ACT_INVACT_LPCMD_TIME_MASK      (0xFFU << DSI_DPI_LP_CMD_TIM_ACT_INVACT_LPCMD_TIME_SHIFT)    /* 0x000000FF */
#define DSI_DPI_LP_CMD_TIM_ACT_OUTVACT_LPCMD_TIME_SHIFT    (16U)
#define DSI_DPI_LP_CMD_TIM_ACT_OUTVACT_LPCMD_TIME_MASK     (0xFFU << DSI_DPI_LP_CMD_TIM_ACT_OUTVACT_LPCMD_TIME_SHIFT)   /* 0x00FF0000 */
/* VID_MODE_CFG_ACT */
#define DSI_VID_MODE_CFG_ACT_OFFSET                        (0x138U)
#define DSI_VID_MODE_CFG_ACT                               (0x0U)
#define DSI_VID_MODE_CFG_ACT_VID_MODE_TYPE_SHIFT           (0U)
#define DSI_VID_MODE_CFG_ACT_VID_MODE_TYPE_MASK            (0x3U << DSI_VID_MODE_CFG_ACT_VID_MODE_TYPE_SHIFT)           /* 0x00000003 */
#define DSI_VID_MODE_CFG_ACT_LP_VSA_EN_SHIFT               (8U)
#define DSI_VID_MODE_CFG_ACT_LP_VSA_EN_MASK                (0x1U << DSI_VID_MODE_CFG_ACT_LP_VSA_EN_SHIFT)               /* 0x00000100 */
#define DSI_VID_MODE_CFG_ACT_LP_VBP_EN_SHIFT               (9U)
#define DSI_VID_MODE_CFG_ACT_LP_VBP_EN_MASK                (0x1U << DSI_VID_MODE_CFG_ACT_LP_VBP_EN_SHIFT)               /* 0x00000200 */
#define DSI_VID_MODE_CFG_ACT_LP_VFP_EN_SHIFT               (10U)
#define DSI_VID_MODE_CFG_ACT_LP_VFP_EN_MASK                (0x1U << DSI_VID_MODE_CFG_ACT_LP_VFP_EN_SHIFT)               /* 0x00000400 */
#define DSI_VID_MODE_CFG_ACT_LP_VACT_EN_SHIFT              (11U)
#define DSI_VID_MODE_CFG_ACT_LP_VACT_EN_MASK               (0x1U << DSI_VID_MODE_CFG_ACT_LP_VACT_EN_SHIFT)              /* 0x00000800 */
#define DSI_VID_MODE_CFG_ACT_LP_HBP_EN_SHIFT               (12U)
#define DSI_VID_MODE_CFG_ACT_LP_HBP_EN_MASK                (0x1U << DSI_VID_MODE_CFG_ACT_LP_HBP_EN_SHIFT)               /* 0x00001000 */
#define DSI_VID_MODE_CFG_ACT_LP_HFP_EN_SHIFT               (13U)
#define DSI_VID_MODE_CFG_ACT_LP_HFP_EN_MASK                (0x1U << DSI_VID_MODE_CFG_ACT_LP_HFP_EN_SHIFT)               /* 0x00002000 */
#define DSI_VID_MODE_CFG_ACT_FRAME_BTA_ACK_EN_SHIFT        (14U)
#define DSI_VID_MODE_CFG_ACT_FRAME_BTA_ACK_EN_MASK         (0x1U << DSI_VID_MODE_CFG_ACT_FRAME_BTA_ACK_EN_SHIFT)        /* 0x00004000 */
#define DSI_VID_MODE_CFG_ACT_LP_CMD_EN_SHIFT               (15U)
#define DSI_VID_MODE_CFG_ACT_LP_CMD_EN_MASK                (0x1U << DSI_VID_MODE_CFG_ACT_LP_CMD_EN_SHIFT)               /* 0x00008000 */
/* VID_PKT_SIZE_ACT */
#define DSI_VID_PKT_SIZE_ACT_OFFSET                        (0x13CU)
#define DSI_VID_PKT_SIZE_ACT                               (0x0U)
#define DSI_VID_PKT_SIZE_ACT_VID_PKT_SIZE_SHIFT            (0U)
#define DSI_VID_PKT_SIZE_ACT_VID_PKT_SIZE_MASK             (0x3FFFU << DSI_VID_PKT_SIZE_ACT_VID_PKT_SIZE_SHIFT)         /* 0x00003FFF */
/* VID_NUM_CHUNKS_ACT */
#define DSI_VID_NUM_CHUNKS_ACT_OFFSET                      (0x140U)
#define DSI_VID_NUM_CHUNKS_ACT                             (0x0U)
#define DSI_VID_NUM_CHUNKS_ACT_VID_NUM_CHUNKS_SHIFT        (0U)
#define DSI_VID_NUM_CHUNKS_ACT_VID_NUM_CHUNKS_MASK         (0x1FFFU << DSI_VID_NUM_CHUNKS_ACT_VID_NUM_CHUNKS_SHIFT)     /* 0x00001FFF */
/* VID_NULL_SIZE_ACT */
#define DSI_VID_NULL_SIZE_ACT_OFFSET                       (0x144U)
#define DSI_VID_NULL_SIZE_ACT                              (0x0U)
#define DSI_VID_NULL_SIZE_ACT_VID_NULL_SIZE_SHIFT          (0U)
#define DSI_VID_NULL_SIZE_ACT_VID_NULL_SIZE_MASK           (0x1FFFU << DSI_VID_NULL_SIZE_ACT_VID_NULL_SIZE_SHIFT)       /* 0x00001FFF */
/* VID_HSA_TIME_ACT */
#define DSI_VID_HSA_TIME_ACT_OFFSET                        (0x148U)
#define DSI_VID_HSA_TIME_ACT                               (0x0U)
#define DSI_VID_HSA_TIME_ACT_VID_HSA_TIME_SHIFT            (0U)
#define DSI_VID_HSA_TIME_ACT_VID_HSA_TIME_MASK             (0xFFFU << DSI_VID_HSA_TIME_ACT_VID_HSA_TIME_SHIFT)          /* 0x00000FFF */
/* VID_HBP_TIME_ACT */
#define DSI_VID_HBP_TIME_ACT_OFFSET                        (0x14CU)
#define DSI_VID_HBP_TIME_ACT                               (0x0U)
#define DSI_VID_HBP_TIME_ACT_VID_HBP_TIME_SHIFT            (0U)
#define DSI_VID_HBP_TIME_ACT_VID_HBP_TIME_MASK             (0xFFFU << DSI_VID_HBP_TIME_ACT_VID_HBP_TIME_SHIFT)          /* 0x00000FFF */
/* VID_HLINE_TIME_ACT */
#define DSI_VID_HLINE_TIME_ACT_OFFSET                      (0x150U)
#define DSI_VID_HLINE_TIME_ACT                             (0x0U)
#define DSI_VID_HLINE_TIME_ACT_VID_HLINE_TIME_SHIFT        (0U)
#define DSI_VID_HLINE_TIME_ACT_VID_HLINE_TIME_MASK         (0x7FFFU << DSI_VID_HLINE_TIME_ACT_VID_HLINE_TIME_SHIFT)     /* 0x00007FFF */
/* VID_VSA_LINES_ACT */
#define DSI_VID_VSA_LINES_ACT_OFFSET                       (0x154U)
#define DSI_VID_VSA_LINES_ACT                              (0x0U)
#define DSI_VID_VSA_LINES_ACT_VSA_LINES_SHIFT              (0U)
#define DSI_VID_VSA_LINES_ACT_VSA_LINES_MASK               (0x3FFU << DSI_VID_VSA_LINES_ACT_VSA_LINES_SHIFT)            /* 0x000003FF */
/* VID_VBP_LINES_ACT */
#define DSI_VID_VBP_LINES_ACT_OFFSET                       (0x158U)
#define DSI_VID_VBP_LINES_ACT                              (0x0U)
#define DSI_VID_VBP_LINES_ACT_VBP_LINES_SHIFT              (0U)
#define DSI_VID_VBP_LINES_ACT_VBP_LINES_MASK               (0x3FFU << DSI_VID_VBP_LINES_ACT_VBP_LINES_SHIFT)            /* 0x000003FF */
/* VID_VFP_LINES_ACT */
#define DSI_VID_VFP_LINES_ACT_OFFSET                       (0x15CU)
#define DSI_VID_VFP_LINES_ACT                              (0x0U)
#define DSI_VID_VFP_LINES_ACT_VFP_LINES_SHIFT              (0U)
#define DSI_VID_VFP_LINES_ACT_VFP_LINES_MASK               (0x3FFU << DSI_VID_VFP_LINES_ACT_VFP_LINES_SHIFT)            /* 0x000003FF */
/* VID_VACTIVE_LINES_ACT */
#define DSI_VID_VACTIVE_LINES_ACT_OFFSET                   (0x160U)
#define DSI_VID_VACTIVE_LINES_ACT                          (0x0U)
#define DSI_VID_VACTIVE_LINES_ACT_V_ACTIVE_LINES_SHIFT     (0U)
#define DSI_VID_VACTIVE_LINES_ACT_V_ACTIVE_LINES_MASK      (0x3FFFU << DSI_VID_VACTIVE_LINES_ACT_V_ACTIVE_LINES_SHIFT)  /* 0x00003FFF */
/* SDF_3D_ACT */
#define DSI_SDF_3D_ACT_OFFSET                              (0x190U)
#define DSI_SDF_3D_ACT_MODE_3D_SHIFT                       (0U)
#define DSI_SDF_3D_ACT_MODE_3D_MASK                        (0x3U << DSI_SDF_3D_ACT_MODE_3D_SHIFT)                       /* 0x00000003 */
#define DSI_SDF_3D_ACT_FORMAT_3D_SHIFT                     (2U)
#define DSI_SDF_3D_ACT_FORMAT_3D_MASK                      (0x3U << DSI_SDF_3D_ACT_FORMAT_3D_SHIFT)                     /* 0x0000000C */
#define DSI_SDF_3D_ACT_SECOND_VSYNC_SHIFT                  (4U)
#define DSI_SDF_3D_ACT_SECOND_VSYNC_MASK                   (0x1U << DSI_SDF_3D_ACT_SECOND_VSYNC_SHIFT)                  /* 0x00000010 */
#define DSI_SDF_3D_ACT_RIGHT_FIRST_SHIFT                   (5U)
#define DSI_SDF_3D_ACT_RIGHT_FIRST_MASK                    (0x1U << DSI_SDF_3D_ACT_RIGHT_FIRST_SHIFT)                   /* 0x00000020 */
#define DSI_SDF_3D_ACT_SEND_3D_CFG_SHIFT                   (16U)
#define DSI_SDF_3D_ACT_SEND_3D_CFG_MASK                    (0x1U << DSI_SDF_3D_ACT_SEND_3D_CFG_SHIFT)                   /* 0x00010000 */
/*****************************************VICAP******************************************/
/* DVP_CTRL */
#define VICAP_DVP_CTRL_OFFSET                              (0x0U)
#define VICAP_DVP_CTRL_CAP_EN_SHIFT                        (0U)
#define VICAP_DVP_CTRL_CAP_EN_MASK                         (0x1U << VICAP_DVP_CTRL_CAP_EN_SHIFT)                        /* 0x00000001 */
#define VICAP_DVP_CTRL_WORK_MODE_SHIFT                     (1U)
#define VICAP_DVP_CTRL_WORK_MODE_MASK                      (0x3U << VICAP_DVP_CTRL_WORK_MODE_SHIFT)                     /* 0x00000006 */
#define VICAP_DVP_CTRL_AXI_BURST_TYPE_SHIFT                (12U)
#define VICAP_DVP_CTRL_AXI_BURST_TYPE_MASK                 (0xFU << VICAP_DVP_CTRL_AXI_BURST_TYPE_SHIFT)                /* 0x0000F000 */
/* DVP_INTEN */
#define VICAP_DVP_INTEN_OFFSET                             (0x4U)
#define VICAP_DVP_INTEN_DMA_FRAME_END_EN_SHIFT             (0U)
#define VICAP_DVP_INTEN_DMA_FRAME_END_EN_MASK              (0x1U << VICAP_DVP_INTEN_DMA_FRAME_END_EN_SHIFT)             /* 0x00000001 */
#define VICAP_DVP_INTEN_LINE_END_EN_SHIFT                  (1U)
#define VICAP_DVP_INTEN_LINE_END_EN_MASK                   (0x1U << VICAP_DVP_INTEN_LINE_END_EN_SHIFT)                  /* 0x00000002 */
#define VICAP_DVP_INTEN_LINE_ERR_EN_SHIFT                  (2U)
#define VICAP_DVP_INTEN_LINE_ERR_EN_MASK                   (0x1U << VICAP_DVP_INTEN_LINE_ERR_EN_SHIFT)                  /* 0x00000004 */
#define VICAP_DVP_INTEN_PIX_ERR_EN_SHIFT                   (3U)
#define VICAP_DVP_INTEN_PIX_ERR_EN_MASK                    (0x1U << VICAP_DVP_INTEN_PIX_ERR_EN_SHIFT)                   /* 0x00000008 */
#define VICAP_DVP_INTEN_IFIFO_OF_EN_SHIFT                  (4U)
#define VICAP_DVP_INTEN_IFIFO_OF_EN_MASK                   (0x1U << VICAP_DVP_INTEN_IFIFO_OF_EN_SHIFT)                  /* 0x00000010 */
#define VICAP_DVP_INTEN_DFIFO_OF_EN_SHIFT                  (5U)
#define VICAP_DVP_INTEN_DFIFO_OF_EN_MASK                   (0x1U << VICAP_DVP_INTEN_DFIFO_OF_EN_SHIFT)                  /* 0x00000020 */
#define VICAP_DVP_INTEN_BUS_ERR_EN_SHIFT                   (6U)
#define VICAP_DVP_INTEN_BUS_ERR_EN_MASK                    (0x1U << VICAP_DVP_INTEN_BUS_ERR_EN_SHIFT)                   /* 0x00000040 */
#define VICAP_DVP_INTEN_FRAME_START_EN_SHIFT               (7U)
#define VICAP_DVP_INTEN_FRAME_START_EN_MASK                (0x1U << VICAP_DVP_INTEN_FRAME_START_EN_SHIFT)               /* 0x00000080 */
#define VICAP_DVP_INTEN_PRE_INF_FRAME_END_EN_SHIFT         (8U)
#define VICAP_DVP_INTEN_PRE_INF_FRAME_END_EN_MASK          (0x1U << VICAP_DVP_INTEN_PRE_INF_FRAME_END_EN_SHIFT)         /* 0x00000100 */
#define VICAP_DVP_INTEN_PST_INF_FRAME_END_EN_SHIFT         (9U)
#define VICAP_DVP_INTEN_PST_INF_FRAME_END_EN_MASK          (0x1U << VICAP_DVP_INTEN_PST_INF_FRAME_END_EN_SHIFT)         /* 0x00000200 */
#define VICAP_DVP_INTEN_BLOCK0_END_EN_SHIFT                (10U)
#define VICAP_DVP_INTEN_BLOCK0_END_EN_MASK                 (0x1U << VICAP_DVP_INTEN_BLOCK0_END_EN_SHIFT)                /* 0x00000400 */
#define VICAP_DVP_INTEN_BLOCK1_END_EN_SHIFT                (11U)
#define VICAP_DVP_INTEN_BLOCK1_END_EN_MASK                 (0x1U << VICAP_DVP_INTEN_BLOCK1_END_EN_SHIFT)                /* 0x00000800 */
#define VICAP_DVP_INTEN_LINE0_END_EN_SHIFT                 (12U)
#define VICAP_DVP_INTEN_LINE0_END_EN_MASK                  (0x1U << VICAP_DVP_INTEN_LINE0_END_EN_SHIFT)                 /* 0x00001000 */
#define VICAP_DVP_INTEN_LINE1_END_EN_SHIFT                 (13U)
#define VICAP_DVP_INTEN_LINE1_END_EN_MASK                  (0x1U << VICAP_DVP_INTEN_LINE1_END_EN_SHIFT)                 /* 0x00002000 */
#define VICAP_DVP_INTEN_BLOCK_ERR_EN_SHIFT                 (14U)
#define VICAP_DVP_INTEN_BLOCK_ERR_EN_MASK                  (0x1U << VICAP_DVP_INTEN_BLOCK_ERR_EN_SHIFT)                 /* 0x00004000 */
/* DVP_INTSTAT */
#define VICAP_DVP_INTSTAT_OFFSET                           (0x8U)
#define VICAP_DVP_INTSTAT_DMA_FRAME_END_SHIFT              (0U)
#define VICAP_DVP_INTSTAT_DMA_FRAME_END_MASK               (0x1U << VICAP_DVP_INTSTAT_DMA_FRAME_END_SHIFT)              /* 0x00000001 */
#define VICAP_DVP_INTSTAT_LINE_END_SHIFT                   (1U)
#define VICAP_DVP_INTSTAT_LINE_END_MASK                    (0x1U << VICAP_DVP_INTSTAT_LINE_END_SHIFT)                   /* 0x00000002 */
#define VICAP_DVP_INTSTAT_LINE_ERR_SHIFT                   (2U)
#define VICAP_DVP_INTSTAT_LINE_ERR_MASK                    (0x1U << VICAP_DVP_INTSTAT_LINE_ERR_SHIFT)                   /* 0x00000004 */
#define VICAP_DVP_INTSTAT_PIX_ERR_SHIFT                    (3U)
#define VICAP_DVP_INTSTAT_PIX_ERR_MASK                     (0x1U << VICAP_DVP_INTSTAT_PIX_ERR_SHIFT)                    /* 0x00000008 */
#define VICAP_DVP_INTSTAT_IFIFO_OF_SHIFT                   (4U)
#define VICAP_DVP_INTSTAT_IFIFO_OF_MASK                    (0x1U << VICAP_DVP_INTSTAT_IFIFO_OF_SHIFT)                   /* 0x00000010 */
#define VICAP_DVP_INTSTAT_DFIFO_OF_SHIFT                   (5U)
#define VICAP_DVP_INTSTAT_DFIFO_OF_MASK                    (0x1U << VICAP_DVP_INTSTAT_DFIFO_OF_SHIFT)                   /* 0x00000020 */
#define VICAP_DVP_INTSTAT_BUS_ERR_SHIFT                    (6U)
#define VICAP_DVP_INTSTAT_BUS_ERR_MASK                     (0x1U << VICAP_DVP_INTSTAT_BUS_ERR_SHIFT)                    /* 0x00000040 */
#define VICAP_DVP_INTSTAT_FRAME_START_SHIFT                (7U)
#define VICAP_DVP_INTSTAT_FRAME_START_MASK                 (0x1U << VICAP_DVP_INTSTAT_FRAME_START_SHIFT)                /* 0x00000080 */
#define VICAP_DVP_INTSTAT_PRE_INF_FRAME_END_SHIFT          (8U)
#define VICAP_DVP_INTSTAT_PRE_INF_FRAME_END_MASK           (0x1U << VICAP_DVP_INTSTAT_PRE_INF_FRAME_END_SHIFT)          /* 0x00000100 */
#define VICAP_DVP_INTSTAT_PST_INF_FRAME_END_SHIFT          (9U)
#define VICAP_DVP_INTSTAT_PST_INF_FRAME_END_MASK           (0x1U << VICAP_DVP_INTSTAT_PST_INF_FRAME_END_SHIFT)          /* 0x00000200 */
#define VICAP_DVP_INTSTAT_BLOCK0_END_SHIFT                 (10U)
#define VICAP_DVP_INTSTAT_BLOCK0_END_MASK                  (0x1U << VICAP_DVP_INTSTAT_BLOCK0_END_SHIFT)                 /* 0x00000400 */
#define VICAP_DVP_INTSTAT_BLOCK1_END_SHIFT                 (11U)
#define VICAP_DVP_INTSTAT_BLOCK1_END_MASK                  (0x1U << VICAP_DVP_INTSTAT_BLOCK1_END_SHIFT)                 /* 0x00000800 */
#define VICAP_DVP_INTSTAT_LINE0_END_SHIFT                  (12U)
#define VICAP_DVP_INTSTAT_LINE0_END_MASK                   (0x1U << VICAP_DVP_INTSTAT_LINE0_END_SHIFT)                  /* 0x00001000 */
#define VICAP_DVP_INTSTAT_LINE1_END_SHIFT                  (13U)
#define VICAP_DVP_INTSTAT_LINE1_END_MASK                   (0x1U << VICAP_DVP_INTSTAT_LINE1_END_SHIFT)                  /* 0x00002000 */
#define VICAP_DVP_INTSTAT_BLOCK_ERR_SHIFT                  (14U)
#define VICAP_DVP_INTSTAT_BLOCK_ERR_MASK                   (0x1U << VICAP_DVP_INTSTAT_BLOCK_ERR_SHIFT)                  /* 0x00004000 */
/* DVP_FOR */
#define VICAP_DVP_FOR_OFFSET                               (0xCU)
#define VICAP_DVP_FOR_VSYNC_POL_SHIFT                      (0U)
#define VICAP_DVP_FOR_VSYNC_POL_MASK                       (0x1U << VICAP_DVP_FOR_VSYNC_POL_SHIFT)                      /* 0x00000001 */
#define VICAP_DVP_FOR_HREF_POL_SHIFT                       (1U)
#define VICAP_DVP_FOR_HREF_POL_MASK                        (0x1U << VICAP_DVP_FOR_HREF_POL_SHIFT)                       /* 0x00000002 */
#define VICAP_DVP_FOR_INPUT_MODE_SHIFT                     (2U)
#define VICAP_DVP_FOR_INPUT_MODE_MASK                      (0x7U << VICAP_DVP_FOR_INPUT_MODE_SHIFT)                     /* 0x0000001C */
#define VICAP_DVP_FOR_YUV_IN_ORDER_SHIFT                   (5U)
#define VICAP_DVP_FOR_YUV_IN_ORDER_MASK                    (0x3U << VICAP_DVP_FOR_YUV_IN_ORDER_SHIFT)                   /* 0x00000060 */
#define VICAP_DVP_FOR_FIELD_ORDER_SHIFT                    (9U)
#define VICAP_DVP_FOR_FIELD_ORDER_MASK                     (0x1U << VICAP_DVP_FOR_FIELD_ORDER_SHIFT)                    /* 0x00000200 */
#define VICAP_DVP_FOR_JPEG_MODE_SHIFT                      (10U)
#define VICAP_DVP_FOR_JPEG_MODE_MASK                       (0x1U << VICAP_DVP_FOR_JPEG_MODE_SHIFT)                      /* 0x00000400 */
#define VICAP_DVP_FOR_RAW_WIDTH_SHIFT                      (11U)
#define VICAP_DVP_FOR_RAW_WIDTH_MASK                       (0x3U << VICAP_DVP_FOR_RAW_WIDTH_SHIFT)                      /* 0x00001800 */
#define VICAP_DVP_FOR_ONLY_Y_MODE_SHIFT                    (15U)
#define VICAP_DVP_FOR_ONLY_Y_MODE_MASK                     (0x1U << VICAP_DVP_FOR_ONLY_Y_MODE_SHIFT)                    /* 0x00008000 */
#define VICAP_DVP_FOR_OUTPUT_420_SHIFT                     (16U)
#define VICAP_DVP_FOR_OUTPUT_420_MASK                      (0x1U << VICAP_DVP_FOR_OUTPUT_420_SHIFT)                     /* 0x00010000 */
#define VICAP_DVP_FOR_OUT_420_ORDER_SHIFT                  (17U)
#define VICAP_DVP_FOR_OUT_420_ORDER_MASK                   (0x1U << VICAP_DVP_FOR_OUT_420_ORDER_SHIFT)                  /* 0x00020000 */
#define VICAP_DVP_FOR_RAW_END_SHIFT                        (18U)
#define VICAP_DVP_FOR_RAW_END_MASK                         (0x1U << VICAP_DVP_FOR_RAW_END_SHIFT)                        /* 0x00040000 */
#define VICAP_DVP_FOR_UV_STORE_ORDER_SHIFT                 (19U)
#define VICAP_DVP_FOR_UV_STORE_ORDER_MASK                  (0x1U << VICAP_DVP_FOR_UV_STORE_ORDER_SHIFT)                 /* 0x00080000 */
#define VICAP_DVP_FOR_HSYNC_MODE_SHIFT                     (20U)
#define VICAP_DVP_FOR_HSYNC_MODE_MASK                      (0x1U << VICAP_DVP_FOR_HSYNC_MODE_SHIFT)                     /* 0x00100000 */
/* DVP_DMA_IDLE_REQ */
#define VICAP_DVP_DMA_IDLE_REQ_OFFSET                      (0x10U)
#define VICAP_DVP_DMA_IDLE_REQ_DMA_IDLE_REQ_SHIFT          (0U)
#define VICAP_DVP_DMA_IDLE_REQ_DMA_IDLE_REQ_MASK           (0x1U << VICAP_DVP_DMA_IDLE_REQ_DMA_IDLE_REQ_SHIFT)          /* 0x00000001 */
/* DVP_FRM0_ADDR_Y */
#define VICAP_DVP_FRM0_ADDR_Y_OFFSET                       (0x14U)
#define VICAP_DVP_FRM0_ADDR_Y_FRM0_ADDR_Y_SHIFT            (0U)
#define VICAP_DVP_FRM0_ADDR_Y_FRM0_ADDR_Y_MASK             (0xFFFFFFFFU << VICAP_DVP_FRM0_ADDR_Y_FRM0_ADDR_Y_SHIFT)     /* 0xFFFFFFFF */
/* DVP_FRM0_ADDR_UV */
#define VICAP_DVP_FRM0_ADDR_UV_OFFSET                      (0x18U)
#define VICAP_DVP_FRM0_ADDR_UV_FRM0_ADDR_UV_SHIFT          (0U)
#define VICAP_DVP_FRM0_ADDR_UV_FRM0_ADDR_UV_MASK           (0xFFFFFFFFU << VICAP_DVP_FRM0_ADDR_UV_FRM0_ADDR_UV_SHIFT)   /* 0xFFFFFFFF */
/* DVP_FRM1_ADDR_Y */
#define VICAP_DVP_FRM1_ADDR_Y_OFFSET                       (0x1CU)
#define VICAP_DVP_FRM1_ADDR_Y_FRM1_ADDR_Y_SHIFT            (0U)
#define VICAP_DVP_FRM1_ADDR_Y_FRM1_ADDR_Y_MASK             (0xFFFFFFFFU << VICAP_DVP_FRM1_ADDR_Y_FRM1_ADDR_Y_SHIFT)     /* 0xFFFFFFFF */
/* DVP_FRM1_ADDR_UV */
#define VICAP_DVP_FRM1_ADDR_UV_OFFSET                      (0x20U)
#define VICAP_DVP_FRM1_ADDR_UV_FRM1_ADDR_UV_SHIFT          (0U)
#define VICAP_DVP_FRM1_ADDR_UV_FRM1_ADDR_UV_MASK           (0xFFFFFFFFU << VICAP_DVP_FRM1_ADDR_UV_FRM1_ADDR_UV_SHIFT)   /* 0xFFFFFFFF */
/* DVP_VIR_LINE_WIDTH */
#define VICAP_DVP_VIR_LINE_WIDTH_OFFSET                    (0x24U)
#define VICAP_DVP_VIR_LINE_WIDTH_VIR_LINE_WIDTH_SHIFT      (0U)
#define VICAP_DVP_VIR_LINE_WIDTH_VIR_LINE_WIDTH_MASK       (0x7FFFU << VICAP_DVP_VIR_LINE_WIDTH_VIR_LINE_WIDTH_SHIFT)   /* 0x00007FFF */
/* DVP_SET_SIZE */
#define VICAP_DVP_SET_SIZE_OFFSET                          (0x28U)
#define VICAP_DVP_SET_SIZE_SET_WIDTH_SHIFT                 (0U)
#define VICAP_DVP_SET_SIZE_SET_WIDTH_MASK                  (0x1FFFU << VICAP_DVP_SET_SIZE_SET_WIDTH_SHIFT)              /* 0x00001FFF */
#define VICAP_DVP_SET_SIZE_SET_HEIGHT_SHIFT                (16U)
#define VICAP_DVP_SET_SIZE_SET_HEIGHT_MASK                 (0x1FFFU << VICAP_DVP_SET_SIZE_SET_HEIGHT_SHIFT)             /* 0x1FFF0000 */
/* DVP_BLOCK_LINE_NUM */
#define VICAP_DVP_BLOCK_LINE_NUM_OFFSET                    (0x2CU)
#define VICAP_DVP_BLOCK_LINE_NUM_BLOCK_LINE_NUM_SHIFT      (0U)
#define VICAP_DVP_BLOCK_LINE_NUM_BLOCK_LINE_NUM_MASK       (0x1FFFU << VICAP_DVP_BLOCK_LINE_NUM_BLOCK_LINE_NUM_SHIFT)   /* 0x00001FFF */
/* DVP_BLOCK0_ADDR_Y */
#define VICAP_DVP_BLOCK0_ADDR_Y_OFFSET                     (0x30U)
#define VICAP_DVP_BLOCK0_ADDR_Y_BLOCK0_ADDR_Y_SHIFT        (0U)
#define VICAP_DVP_BLOCK0_ADDR_Y_BLOCK0_ADDR_Y_MASK         (0xFFFFFFFFU << VICAP_DVP_BLOCK0_ADDR_Y_BLOCK0_ADDR_Y_SHIFT) /* 0xFFFFFFFF */
/* DVP_BLOCK0_ADDR_UV */
#define VICAP_DVP_BLOCK0_ADDR_UV_OFFSET                    (0x34U)
#define VICAP_DVP_BLOCK0_ADDR_UV_BLOCK0_ADDR_UV_SHIFT      (0U)
#define VICAP_DVP_BLOCK0_ADDR_UV_BLOCK0_ADDR_UV_MASK       (0xFFFFFFFFU << VICAP_DVP_BLOCK0_ADDR_UV_BLOCK0_ADDR_UV_SHIFT) /* 0xFFFFFFFF */
/* DVP_BLOCK1_ADDR_Y */
#define VICAP_DVP_BLOCK1_ADDR_Y_OFFSET                     (0x38U)
#define VICAP_DVP_BLOCK1_ADDR_Y_BLOCK1_ADDR_Y_SHIFT        (0U)
#define VICAP_DVP_BLOCK1_ADDR_Y_BLOCK1_ADDR_Y_MASK         (0xFFFFFFFFU << VICAP_DVP_BLOCK1_ADDR_Y_BLOCK1_ADDR_Y_SHIFT) /* 0xFFFFFFFF */
/* DVP_BLOCK1_ADDR_UV */
#define VICAP_DVP_BLOCK1_ADDR_UV_OFFSET                    (0x3CU)
#define VICAP_DVP_BLOCK1_ADDR_UV_BLOCK1_ADDR_UV_SHIFT      (0U)
#define VICAP_DVP_BLOCK1_ADDR_UV_BLOCK1_ADDR_UV_MASK       (0xFFFFFFFFU << VICAP_DVP_BLOCK1_ADDR_UV_BLOCK1_ADDR_UV_SHIFT) /* 0xFFFFFFFF */
/* DVP_BLOCK_STATUS */
#define VICAP_DVP_BLOCK_STATUS_OFFSET                      (0x40U)
#define VICAP_DVP_BLOCK_STATUS_BLK0_STATUS_SHIFT           (0U)
#define VICAP_DVP_BLOCK_STATUS_BLK0_STATUS_MASK            (0x1U << VICAP_DVP_BLOCK_STATUS_BLK0_STATUS_SHIFT)           /* 0x00000001 */
#define VICAP_DVP_BLOCK_STATUS_BLK1_STATUS_SHIFT           (1U)
#define VICAP_DVP_BLOCK_STATUS_BLK1_STATUS_MASK            (0x1U << VICAP_DVP_BLOCK_STATUS_BLK1_STATUS_SHIFT)           /* 0x00000002 */
#define VICAP_DVP_BLOCK_STATUS_BLK_ID_SHIFT                (16U)
#define VICAP_DVP_BLOCK_STATUS_BLK_ID_MASK                 (0xFFU << VICAP_DVP_BLOCK_STATUS_BLK_ID_SHIFT)               /* 0x00FF0000 */
/* DVP_CROP */
#define VICAP_DVP_CROP_OFFSET                              (0x44U)
#define VICAP_DVP_CROP_START_X_SHIFT                       (0U)
#define VICAP_DVP_CROP_START_X_MASK                        (0x1FFFU << VICAP_DVP_CROP_START_X_SHIFT)                    /* 0x00001FFF */
#define VICAP_DVP_CROP_START_Y_SHIFT                       (16U)
#define VICAP_DVP_CROP_START_Y_MASK                        (0x1FFFU << VICAP_DVP_CROP_START_Y_SHIFT)                    /* 0x1FFF0000 */
/* DVP_PATH_SEL */
#define VICAP_DVP_PATH_SEL_OFFSET                          (0x48U)
#define VICAP_DVP_PATH_SEL_YUV_SEL_SHIFT                   (4U)
#define VICAP_DVP_PATH_SEL_YUV_SEL_MASK                    (0x1U << VICAP_DVP_PATH_SEL_YUV_SEL_SHIFT)                   /* 0x00000010 */
#define VICAP_DVP_PATH_SEL_RAW_SEL_SHIFT                   (5U)
#define VICAP_DVP_PATH_SEL_RAW_SEL_MASK                    (0x1U << VICAP_DVP_PATH_SEL_RAW_SEL_SHIFT)                   /* 0x00000020 */
/* DVP_LINE_INT_NUM */
#define VICAP_DVP_LINE_INT_NUM_OFFSET                      (0x4CU)
#define VICAP_DVP_LINE_INT_NUM_LINE0_INT_NUM_SHIFT         (0U)
#define VICAP_DVP_LINE_INT_NUM_LINE0_INT_NUM_MASK          (0x1FFFU << VICAP_DVP_LINE_INT_NUM_LINE0_INT_NUM_SHIFT)      /* 0x00001FFF */
#define VICAP_DVP_LINE_INT_NUM_LINE1_INT_NUM_SHIFT         (16U)
#define VICAP_DVP_LINE_INT_NUM_LINE1_INT_NUM_MASK          (0x1FFFU << VICAP_DVP_LINE_INT_NUM_LINE1_INT_NUM_SHIFT)      /* 0x1FFF0000 */
/* DVP_WATER_LINE */
#define VICAP_DVP_WATER_LINE_OFFSET                        (0x50U)
#define VICAP_DVP_WATER_LINE_HURRY_EN_SHIFT                (0U)
#define VICAP_DVP_WATER_LINE_HURRY_EN_MASK                 (0x1U << VICAP_DVP_WATER_LINE_HURRY_EN_SHIFT)                /* 0x00000001 */
#define VICAP_DVP_WATER_LINE_HURRY_VALUE_SHIFT             (4U)
#define VICAP_DVP_WATER_LINE_HURRY_VALUE_MASK              (0x3U << VICAP_DVP_WATER_LINE_HURRY_VALUE_SHIFT)             /* 0x00000030 */
#define VICAP_DVP_WATER_LINE_WATER_LINE_SHIFT              (8U)
#define VICAP_DVP_WATER_LINE_WATER_LINE_MASK               (0x3U << VICAP_DVP_WATER_LINE_WATER_LINE_SHIFT)              /* 0x00000300 */
/* DVP_FIFO_ENTRY */
#define VICAP_DVP_FIFO_ENTRY_OFFSET                        (0x54U)
#define VICAP_DVP_FIFO_ENTRY_Y_FIFO_ENTRY_SHIFT            (0U)
#define VICAP_DVP_FIFO_ENTRY_Y_FIFO_ENTRY_MASK             (0x1FFU << VICAP_DVP_FIFO_ENTRY_Y_FIFO_ENTRY_SHIFT)          /* 0x000001FF */
#define VICAP_DVP_FIFO_ENTRY_UV_FIFO_ENTRY_SHIFT           (9U)
#define VICAP_DVP_FIFO_ENTRY_UV_FIFO_ENTRY_MASK            (0x1FFU << VICAP_DVP_FIFO_ENTRY_UV_FIFO_ENTRY_SHIFT)         /* 0x0003FE00 */
/* DVP_FRAME_STATUS */
#define VICAP_DVP_FRAME_STATUS_OFFSET                      (0x60U)
#define VICAP_DVP_FRAME_STATUS                             (0x0U)
#define VICAP_DVP_FRAME_STATUS_F0_STS_SHIFT                (0U)
#define VICAP_DVP_FRAME_STATUS_F0_STS_MASK                 (0x1U << VICAP_DVP_FRAME_STATUS_F0_STS_SHIFT)                /* 0x00000001 */
#define VICAP_DVP_FRAME_STATUS_F1_STS_SHIFT                (1U)
#define VICAP_DVP_FRAME_STATUS_F1_STS_MASK                 (0x1U << VICAP_DVP_FRAME_STATUS_F1_STS_SHIFT)                /* 0x00000002 */
#define VICAP_DVP_FRAME_STATUS_IDLE_SHIFT                  (2U)
#define VICAP_DVP_FRAME_STATUS_IDLE_MASK                   (0x1U << VICAP_DVP_FRAME_STATUS_IDLE_SHIFT)                  /* 0x00000004 */
#define VICAP_DVP_FRAME_STATUS_FRAME_NUM_SHIFT             (16U)
#define VICAP_DVP_FRAME_STATUS_FRAME_NUM_MASK              (0xFFFFU << VICAP_DVP_FRAME_STATUS_FRAME_NUM_SHIFT)          /* 0xFFFF0000 */
/* DVP_CUR_DST */
#define VICAP_DVP_CUR_DST_OFFSET                           (0x64U)
#define VICAP_DVP_CUR_DST                                  (0x0U)
#define VICAP_DVP_CUR_DST_CUR_DST_SHIFT                    (0U)
#define VICAP_DVP_CUR_DST_CUR_DST_MASK                     (0xFFFFFFFFU << VICAP_DVP_CUR_DST_CUR_DST_SHIFT)             /* 0xFFFFFFFF */
/* DVP_LAST_LINE */
#define VICAP_DVP_LAST_LINE_OFFSET                         (0x68U)
#define VICAP_DVP_LAST_LINE_LAST_Y_NUM_SHIFT               (0U)
#define VICAP_DVP_LAST_LINE_LAST_Y_NUM_MASK                (0x1FFFU << VICAP_DVP_LAST_LINE_LAST_Y_NUM_SHIFT)            /* 0x00001FFF */
#define VICAP_DVP_LAST_LINE_LAST_UV_NUM_SHIFT              (16U)
#define VICAP_DVP_LAST_LINE_LAST_UV_NUM_MASK               (0x1FFFU << VICAP_DVP_LAST_LINE_LAST_UV_NUM_SHIFT)           /* 0x1FFF0000 */
/* DVP_LAST_PIX */
#define VICAP_DVP_LAST_PIX_OFFSET                          (0x6CU)
#define VICAP_DVP_LAST_PIX_LAST_Y_NUM_SHIFT                (0U)
#define VICAP_DVP_LAST_PIX_LAST_Y_NUM_MASK                 (0x1FFFU << VICAP_DVP_LAST_PIX_LAST_Y_NUM_SHIFT)             /* 0x00001FFF */
#define VICAP_DVP_LAST_PIX_LAST_UV_NUM_SHIFT               (16U)
#define VICAP_DVP_LAST_PIX_LAST_UV_NUM_MASK                (0x1FFFU << VICAP_DVP_LAST_PIX_LAST_UV_NUM_SHIFT)            /* 0x1FFF0000 */
/****************************************AUDIOPWM****************************************/
/* VERSION */
#define AUDIOPWM_VERSION_OFFSET                            (0x0U)
#define AUDIOPWM_VERSION                                   (0x1000000U)
#define AUDIOPWM_VERSION_VERSION_SHIFT                     (0U)
#define AUDIOPWM_VERSION_VERSION_MASK                      (0xFFFFFFFFU << AUDIOPWM_VERSION_VERSION_SHIFT)              /* 0xFFFFFFFF */
/* XFER */
#define AUDIOPWM_XFER_OFFSET                               (0x4U)
#define AUDIOPWM_XFER_START_SHIFT                          (0U)
#define AUDIOPWM_XFER_START_MASK                           (0x1U << AUDIOPWM_XFER_START_SHIFT)                          /* 0x00000001 */
#define AUDIOPWM_XFER_LSTOP_SHIFT                          (1U)
#define AUDIOPWM_XFER_LSTOP_MASK                           (0x1U << AUDIOPWM_XFER_LSTOP_SHIFT)                          /* 0x00000002 */
/* SRC_CFG */
#define AUDIOPWM_SRC_CFG_OFFSET                            (0x8U)
#define AUDIOPWM_SRC_CFG_WIDTH_SHIFT                       (0U)
#define AUDIOPWM_SRC_CFG_WIDTH_MASK                        (0x1FU << AUDIOPWM_SRC_CFG_WIDTH_SHIFT)                      /* 0x0000001F */
#define AUDIOPWM_SRC_CFG_ALIGN_SHIFT                       (5U)
#define AUDIOPWM_SRC_CFG_ALIGN_MASK                        (0x1U << AUDIOPWM_SRC_CFG_ALIGN_SHIFT)                       /* 0x00000020 */
#define AUDIOPWM_SRC_CFG_HALF_EN_SHIFT                     (6U)
#define AUDIOPWM_SRC_CFG_HALF_EN_MASK                      (0x1U << AUDIOPWM_SRC_CFG_HALF_EN_SHIFT)                     /* 0x00000040 */
/* PWM_CFG */
#define AUDIOPWM_PWM_CFG_OFFSET                            (0x10U)
#define AUDIOPWM_PWM_CFG_INTERP_RATE_SHIFT                 (0U)
#define AUDIOPWM_PWM_CFG_INTERP_RATE_MASK                  (0xFU << AUDIOPWM_PWM_CFG_INTERP_RATE_SHIFT)                 /* 0x0000000F */
#define AUDIOPWM_PWM_CFG_LINEAR_INTERP_EN_SHIFT            (4U)
#define AUDIOPWM_PWM_CFG_LINEAR_INTERP_EN_MASK             (0x1U << AUDIOPWM_PWM_CFG_LINEAR_INTERP_EN_SHIFT)            /* 0x00000010 */
#define AUDIOPWM_PWM_CFG_OUT_SWAP_SHIFT                    (5U)
#define AUDIOPWM_PWM_CFG_OUT_SWAP_MASK                     (0x1U << AUDIOPWM_PWM_CFG_OUT_SWAP_SHIFT)                    /* 0x00000020 */
#define AUDIOPWM_PWM_CFG_LEFT_DIS_SHIFT                    (6U)
#define AUDIOPWM_PWM_CFG_LEFT_DIS_MASK                     (0x1U << AUDIOPWM_PWM_CFG_LEFT_DIS_SHIFT)                    /* 0x00000040 */
#define AUDIOPWM_PWM_CFG_RIGHT_DIS_SHIFT                   (7U)
#define AUDIOPWM_PWM_CFG_RIGHT_DIS_MASK                    (0x1U << AUDIOPWM_PWM_CFG_RIGHT_DIS_SHIFT)                   /* 0x00000080 */
#define AUDIOPWM_PWM_CFG_SAMPLE_WIDTH_SHIFT                (8U)
#define AUDIOPWM_PWM_CFG_SAMPLE_WIDTH_MASK                 (0x3U << AUDIOPWM_PWM_CFG_SAMPLE_WIDTH_SHIFT)                /* 0x00000300 */
/* PWM_ST */
#define AUDIOPWM_PWM_ST_OFFSET                             (0x14U)
#define AUDIOPWM_PWM_ST                                    (0x0U)
#define AUDIOPWM_PWM_ST_FIFO_BUSY_SHIFT                    (0U)
#define AUDIOPWM_PWM_ST_FIFO_BUSY_MASK                     (0x1U << AUDIOPWM_PWM_ST_FIFO_BUSY_SHIFT)                    /* 0x00000001 */
#define AUDIOPWM_PWM_ST_PWM_BUSY_SHIFT                     (1U)
#define AUDIOPWM_PWM_ST_PWM_BUSY_MASK                      (0x1U << AUDIOPWM_PWM_ST_PWM_BUSY_SHIFT)                     /* 0x00000002 */
/* PWM_BUF_01 */
#define AUDIOPWM_PWM_BUF_01_OFFSET                         (0x18U)
#define AUDIOPWM_PWM_BUF_01                                (0x0U)
#define AUDIOPWM_PWM_BUF_01_PWM_BUF_0_SHIFT                (0U)
#define AUDIOPWM_PWM_BUF_01_PWM_BUF_0_MASK                 (0x7FFU << AUDIOPWM_PWM_BUF_01_PWM_BUF_0_SHIFT)              /* 0x000007FF */
#define AUDIOPWM_PWM_BUF_01_PWM_BUF_1_SHIFT                (16U)
#define AUDIOPWM_PWM_BUF_01_PWM_BUF_1_MASK                 (0x7FFU << AUDIOPWM_PWM_BUF_01_PWM_BUF_1_SHIFT)              /* 0x07FF0000 */
/* PWM_BUF_23 */
#define AUDIOPWM_PWM_BUF_23_OFFSET                         (0x1CU)
#define AUDIOPWM_PWM_BUF_23                                (0x0U)
#define AUDIOPWM_PWM_BUF_23_PWM_BUF_2_SHIFT                (0U)
#define AUDIOPWM_PWM_BUF_23_PWM_BUF_2_MASK                 (0x7FFU << AUDIOPWM_PWM_BUF_23_PWM_BUF_2_SHIFT)              /* 0x000007FF */
#define AUDIOPWM_PWM_BUF_23_PWM_BUF_3_SHIFT                (16U)
#define AUDIOPWM_PWM_BUF_23_PWM_BUF_3_MASK                 (0x7FFU << AUDIOPWM_PWM_BUF_23_PWM_BUF_3_SHIFT)              /* 0x07FF0000 */
/* FIFO_CFG */
#define AUDIOPWM_FIFO_CFG_OFFSET                           (0x20U)
#define AUDIOPWM_FIFO_CFG_DMA_WATERMARK_SHIFT              (0U)
#define AUDIOPWM_FIFO_CFG_DMA_WATERMARK_MASK               (0x1FU << AUDIOPWM_FIFO_CFG_DMA_WATERMARK_SHIFT)             /* 0x0000001F */
#define AUDIOPWM_FIFO_CFG_DMA_EN_SHIFT                     (7U)
#define AUDIOPWM_FIFO_CFG_DMA_EN_MASK                      (0x1U << AUDIOPWM_FIFO_CFG_DMA_EN_SHIFT)                     /* 0x00000080 */
#define AUDIOPWM_FIFO_CFG_ALMOST_FULL_WATERMARK_SHIFT      (8U)
#define AUDIOPWM_FIFO_CFG_ALMOST_FULL_WATERMARK_MASK       (0x1FU << AUDIOPWM_FIFO_CFG_ALMOST_FULL_WATERMARK_SHIFT)     /* 0x00001F00 */
/* FIFO_LVL */
#define AUDIOPWM_FIFO_LVL_OFFSET                           (0x24U)
#define AUDIOPWM_FIFO_LVL                                  (0x0U)
#define AUDIOPWM_FIFO_LVL_FIFO_SPACE2FULL_SHIFT            (0U)
#define AUDIOPWM_FIFO_LVL_FIFO_SPACE2FULL_MASK             (0x3FU << AUDIOPWM_FIFO_LVL_FIFO_SPACE2FULL_SHIFT)           /* 0x0000003F */
/* FIFO_INT_EN */
#define AUDIOPWM_FIFO_INT_EN_OFFSET                        (0x28U)
#define AUDIOPWM_FIFO_INT_EN_FULL_INT_EN_SHIFT             (0U)
#define AUDIOPWM_FIFO_INT_EN_FULL_INT_EN_MASK              (0x1U << AUDIOPWM_FIFO_INT_EN_FULL_INT_EN_SHIFT)             /* 0x00000001 */
#define AUDIOPWM_FIFO_INT_EN_OVERRUN_INT_EN_SHIFT          (1U)
#define AUDIOPWM_FIFO_INT_EN_OVERRUN_INT_EN_MASK           (0x1U << AUDIOPWM_FIFO_INT_EN_OVERRUN_INT_EN_SHIFT)          /* 0x00000002 */
#define AUDIOPWM_FIFO_INT_EN_EMPTY_INT_EN_SHIFT            (2U)
#define AUDIOPWM_FIFO_INT_EN_EMPTY_INT_EN_MASK             (0x1U << AUDIOPWM_FIFO_INT_EN_EMPTY_INT_EN_SHIFT)            /* 0x00000004 */
/* FIFO_INT_ST */
#define AUDIOPWM_FIFO_INT_ST_OFFSET                        (0x2CU)
#define AUDIOPWM_FIFO_INT_ST_FULL_INT_ST_SHIFT             (0U)
#define AUDIOPWM_FIFO_INT_ST_FULL_INT_ST_MASK              (0x1U << AUDIOPWM_FIFO_INT_ST_FULL_INT_ST_SHIFT)             /* 0x00000001 */
#define AUDIOPWM_FIFO_INT_ST_OVERRUN_INT_ST_SHIFT          (1U)
#define AUDIOPWM_FIFO_INT_ST_OVERRUN_INT_ST_MASK           (0x1U << AUDIOPWM_FIFO_INT_ST_OVERRUN_INT_ST_SHIFT)          /* 0x00000002 */
#define AUDIOPWM_FIFO_INT_ST_EMPTY_INT_ST_SHIFT            (2U)
#define AUDIOPWM_FIFO_INT_ST_EMPTY_INT_ST_MASK             (0x1U << AUDIOPWM_FIFO_INT_ST_EMPTY_INT_ST_SHIFT)            /* 0x00000004 */
/* FIFO_ENTRY */
#define AUDIOPWM_FIFO_ENTRY_OFFSET                         (0x80U)
#define AUDIOPWM_FIFO_ENTRY_FIFO_DATA_ENTRY_SHIFT          (0U)
#define AUDIOPWM_FIFO_ENTRY_FIFO_DATA_ENTRY_MASK           (0xFFFFFFFFU << AUDIOPWM_FIFO_ENTRY_FIFO_DATA_ENTRY_SHIFT)   /* 0xFFFFFFFF */

/****************************************************************************************/
/*                                                                                      */
/*                               Clock Description Section                              */
/*                                                                                      */
/****************************************************************************************/
/********Name=SOFTRST_CON00,Offset=0x200********/
#define SRST_D_DSP     0U
#define SRST_B_DSP     1U
#define SRST_A_DSP_NIU 2U
#define SRST_P_DSP_NIU 4U
#define SRST_P_DSP_GRF 5U
#define SRST_P_WDT1    6U
/********Name=SOFTRST_CON01,Offset=0x204********/
#define SRST_S_SHRM     16U
#define SRST_A_SHRM_NIU 17U
#define SRST_P_SHRM     18U
#define SRST_P_SHRM_NIU 19U
/********Name=SOFTRST_CON02,Offset=0x208********/
#define SRST_P_UART0 32U
#define SRST_P_UART1 33U
#define SRST_P_UART2 35U
#define SRST_S_UART0 38U
#define SRST_S_UART1 41U
#define SRST_S_UART2 46U
/********Name=SOFTRST_CON04,Offset=0x210********/
#define SRST_P_TIMER 64U
#define SRST_TIMER0  65U
#define SRST_TIMER1  66U
#define SRST_TIMER2  67U
#define SRST_TIMER3  68U
#define SRST_TIMER4  69U
#define SRST_TIMER5  70U
/********Name=SOFTRST_CON05,Offset=0x214********/
#define SRST_P_I2C2APB_NIU 80U
#define SRST_P_I2C0        81U
#define SRST_P_I2C1        82U
#define SRST_P_I2C2        83U
#define SRST_P_I2C2APB     84U
#define SRST_I2C0          85U
#define SRST_I2C1          86U
#define SRST_I2C2          87U
#define SRST_CODEC_I2S_OUT 92U
#define SRST_P_ACDC_DIG    94U
#define SRST_A_DMAC_CORE   95U
/********Name=SOFTRST_CON06,Offset=0x218********/
#define SRST_H_PDM0          96U
#define SRST_H_I2S_8CH       98U
#define SRST_H_VAD           99U
#define SRST_H_AUDIO_NIU     100U
#define SRST_H_AUDIO_AHB_ARB 101U
#define SRST_P_AUDIO_NIU     102U
#define SRST_M_PDM0          103U
#define SRST_M_I2S8CH        108U
#define SRST_A_DMAC_NIU      111U
/********Name=SOFTRST_CON07,Offset=0x21C********/
#define SRST_A_VOP     112U
#define SRST_D_VOP_S   114U
#define SRST_A_VOP_NIU 115U
/********Name=SOFTRST_CON08,Offset=0x220********/
#define SRST_P_GPIO0  128U
#define SRST_P_GPIO1  129U
#define SRST_GPIO_DB0 131U
#define SRST_GPIO_DB1 132U
/********Name=SOFTRST_CON09,Offset=0x224********/
#define SRST_H_ALIVE_NIU    146U
#define SRST_H_ALIVEAHB_ARB 147U
#define SRST_H_INTC0        148U
#define SRST_H_INTC1        149U
#define SRST_P_CRU          152U
#define SRST_P_ALIVE_NIU    153U
#define SRST_P_PMU          154U
#define SRST_P_GRF          155U
#define SRST_PMU            156U
#define SRST_PVTM           158U
#define SRST_PDM_SAMP       159U
/********Name=SOFTRST_CON11,Offset=0x22C********/
#define SRST_A_LOGIC_NIU    177U
#define SRST_P_SPI2APB_NIU  180U
#define SRST_P_PWM          181U
#define SRST_P_SPI1         182U
#define SRST_P_SPI2         183U
#define SRST_P_SPI2APB      184U
#define SRST_P_MAILBOX0     185U
#define SRST_P_MAILBOX1     186U
#define SRST_P_MAILBOX2     187U
#define SRST_P_WDT0         188U
#define SRST_P_MIPIDSI_HOST 189U
#define SRST_P_CIF          190U
#define SRST_P_LOGIC_NIU    191U
/********Name=SOFTRST_CON12,Offset=0x230********/
#define SRST_H_USB2CTRL      193U
#define SRST_H_USB2_NIU      194U
#define SRST_H_BOOTROM       195U
#define SRST_H_VOP           196U
#define SRST_H_AUDPWM        197U
#define SRST_H_CIF           198U
#define SRST_H_LOGIC_NIU     199U
#define SRST_H_SFC           200U
#define SRST_H_XIP_SFC       201U
#define SRST_H_SDIO          202U
#define SRST_H_LOGIC_AHB_ARB 203U
#define SRST_H_I2S1_8CH      204U
#define SRST_H_CM4_NIU       205U
#define SRST_H_CM4_CORE      206U
/********Name=SOFTRST_CON13,Offset=0x234********/
#define SRST_SPI1       208U
#define SRST_SPI2       209U
#define SRST_S_SFC      212U
#define SRST_H_SFC1     213U
#define SRST_H_XIP_SFC1 214U
#define SRST_SDIO       216U
#define SRST_M_I2S1_8CH 219U
#define SRST_PWM        221U
#define SRST_AUDPWM     222U
#define SRST_A_CIF      223U
/********Name=SOFTRST_CON14,Offset=0x238********/
#define SRST_A_CIF_NIU   225U
#define SRST_S_SFC1      228U
#define SRST_USB2_ADP    229U
#define SRST_KEY         233U
#define SRST_P_KEY       234U
#define SRST_USB2PHYUTMI 236U
#define SRST_USB2CTRL    237U
#define SRST_USB2PHYPO   238U
/********Name=SOFTRST_CON15,Offset=0x23C********/
#define SRST_H_AC_CM4_CORE 240U
#define SRST_WRITE_ENABLE  256U

/********Name=CLKGATE_CON00,Offset=0x180********/
#define ACLK_DSP_GATE     0U
#define ACLK_DSP_NIU_GATE 2U
#define PCLK_DSP_GATE     3U
#define PCLK_DSP_NIU_GATE 4U
#define PCLK_DSP_GRF_GATE 5U
#define PCLK_WDT1_GATE    6U
#define ACLK_DSP_S_GATE   7U
/********Name=CLKGATE_CON01,Offset=0x184********/
#define SCLK_SHRM_GATE     16U
#define ACLK_SHRM_NIU_GATE 17U
#define PCLK_SHRM_GATE     18U
#define PCLK_SHRM_NIU_GATE 19U
/********Name=CLKGATE_CON02,Offset=0x188********/
#define PCLK_UART0_GATE     32U
#define PCLK_UART1_GATE     33U
#define PCLK_UART2_GATE     34U
#define CLK_UART0_GATE      35U
#define CLK_UART0_FRAC_GATE 36U
#define CLK_UART0_NP5_GATE  37U
#define SCLK_UART0_GATE     38U
#define CLK_UART1_GATE      39U
#define CLK_UART1_FRAC_GATE 40U
#define CLK_UART1_NP5_GATE  41U
#define SCLK_UART1_GATE     42U
#define CLK_UART2_GATE      43U
#define CLK_UART2_FRAC_GATE 44U
#define CLK_UART2_NP5_GATE  45U
#define SCLK_UART2_GATE     46U
/********Name=CLKGATE_CON04,Offset=0x190********/
#define PCLK_TIMER_GATE 64U
#define CLK_TIMER0_GATE 65U
#define CLK_TIMER1_GATE 66U
#define CLK_TIMER2_GATE 67U
#define CLK_TIMER3_GATE 68U
#define CLK_TIMER4_GATE 69U
#define CLK_TIMER5_GATE 70U
/********Name=CLKGATE_CON05,Offset=0x194********/
#define PCLK_I2C2APB_NIU_GATE 80U
#define PCLK_I2C0_GATE        81U
#define PCLK_I2C1_GATE        82U
#define PCLK_I2C2_GATE        83U
#define PCLK_I2C2APB_GATE     84U
#define CLK_I2C0_GATE         85U
#define CLK_I2C1_GATE         86U
#define CLK_I2C2_GATE         87U
#define PCLK_ACDC_DIG_GATE    94U
#define ACLK_DMAC_CORE_GATE   95U
/********Name=CLKGATE_CON06,Offset=0x198********/
#define HCLK_PDM0_GATE          96U
#define HCLK_AUDIO_GATE         97U
#define HCLK_I2S_8CH_GATE       98U
#define HCLK_VAD_GATE           99U
#define HCLK_AUDIO_NIU_GATE     100U
#define HCLK_AUDIO_AHB_ARB_GATE 101U
#define PCLK_AUDIO_NIU_GATE     102U
#define MCLK_PDM0_GATE          103U
#define MCLK_PDM0_OUT_GATE      104U
#define PCLK_AUDIO_GATE         105U
#define CLK_I2S8CH_GATE         106U
#define CLK_I2S8CH_FRAC_GATE    107U
#define MCLK_I2S8CH_GATE        108U
#define I2S_MCLKOUT_GATE        109U
#define ACLK_DMAC_GATE          110U
#define ACLK_DMAC_NIU_GATE      111U
/********Name=CLKGATE_CON07,Offset=0x19C********/
#define ACLK_VOP_GATE                 112U
#define DCLK_VOP_S_GATE               114U
#define ACLK_VOP_NIU_GATE             115U
#define DCLK_VOP_GATE                 116U
#define DCLK_MIPIDSI_HOST_GATE        117U
#define OCC_SCAN_CLK_DPHYLANBYTE_GATE 120U
/********Name=CLKGATE_CON08,Offset=0x1A0********/
#define PCLK_GPIO0_GATE   128U
#define PCLK_GPIO1_GATE   129U
#define CLK_GPIO_DB0_GATE 131U
#define CLK_GPIO_DB1_GATE 132U
/********Name=CLKGATE_CON09,Offset=0x1A4********/
#define PCLK_ALIVE_GATE        144U
#define HCLK_ALIVE_GATE        145U
#define HCLK_ALIVE_NIU_GATE    146U
#define HCLK_ALIVEAHB_ARB_GATE 147U
#define HCLK_INTC0_GATE        148U
#define HCLK_INTC1_GATE        149U
#define PCLK_CRU_GATE          152U
#define PCLK_ALIVE_NIU_GATE    153U
#define PCLK_PMU_GATE          154U
#define PCLK_GRF_GATE          155U
#define CLK_PMU_GATE           156U
#define CLK_TESTOUT_GATE       157U
#define CLK_PVTM_GATE          158U
#define CLK_PDM_SAMP_GATE      159U
/********Name=CLKGATE_CON10,Offset=0x1A8********/
#define CLK_MEMSUBSYS0_GATE 160U
#define CLK_MEMSUBSYS1_GATE 161U
#define CLK_MEMSUBSYS2_GATE 162U
#define CLK_MEMSUBSYS3_GATE 163U
#define ACLK_MEMSUBSYS_GATE 164U
/********Name=CLKGATE_CON11,Offset=0x1AC********/
#define ACLK_LOGIC_GATE        176U
#define ACLK_LOGIC_NIU_GATE    177U
#define HCLK_LOGIC_GATE        178U
#define PCLK_LOGIC_GATE        179U
#define PCLK_SPI2APB_NIU_GATE  180U
#define PCLK_PWM_GATE          181U
#define PCLK_SPI1_GATE         182U
#define PCLK_SPI2_GATE         183U
#define PCLK_SPI2APB_GATE      184U
#define PCLK_MAILBOX0_GATE     185U
#define PCLK_MAILBOX1_GATE     186U
#define PCLK_MAILBOX2_GATE     187U
#define PCLK_WDT0_GATE         188U
#define PCLK_MIPIDSI_HOST_GATE 189U
#define PCLK_CIF_GATE          190U
#define PCLK_LOGIC_NIU_GATE    191U
/********Name=CLKGATE_CON12,Offset=0x1B0********/
#define HCLK_M4_GATE            192U
#define HCLK_USB2CTRL_GATE      193U
#define HCLK_USB2_NIU_GATE      194U
#define HCLK_BOOTROM_GATE       195U
#define HCLK_VOP_GATE           196U
#define HCLK_AUDPWM_GATE        197U
#define HCLK_CIF_GATE           198U
#define HCLK_LOGIC_NIU_GATE     199U
#define HCLK_SFC_GATE           200U
#define HCLK_XIP_SFC_GATE       201U
#define HCLK_SDIO_GATE          202U
#define HCLK_LOGIC_AHB_ARB_GATE 203U
#define HCLK_I2S1_8CH_GATE      204U
#define HCLK_CM4_NIU_GATE       205U
#define HCLK_CM4_CORE_GATE      206U
#define CLK_CIFOUT_GATE         207U
/********Name=CLKGATE_CON13,Offset=0x1B4********/
#define CLK_SPI1_GATE          208U
#define CLK_SPI2_GATE          209U
#define SCLK_SFC_GATE          212U
#define HCLK_SFC1_GATE         213U
#define HCLK_XIP_SFC1_GATE     214U
#define CLK_SDIO_GATE          216U
#define CLK_I2S1_8CH_GATE      217U
#define CLK_I2S1_8CH_FRAC_GATE 218U
#define MCLK_I2S1_8CH_GATE     219U
#define I2S1_MCLKOUT_GATE      220U
#define CLK_PWM_GATE           221U
#define CLK_AUDPWM_DF_GATE     222U
#define ACLK_CIF_GATE          223U
/********Name=CLKGATE_CON14,Offset=0x1B8********/
#define CLK_AUDPWM_FRAC_GATE      224U
#define ACLK_CIF_NIU_GATE         225U
#define SCLK_SFC1_GATE            228U
#define CLK_USB2_ADP_GATE         229U
#define CLK_USB2PHY_REF_FRAC_GATE 230U
#define CLK_DPHY_REF_FRAC_GATE    231U
#define STCLK_M4_GATE             232U
#define CLK_KEY_GATE              233U
#define PCLK_KEY_GATE             234U
#define CLK_USB2CTRL_GATE         237U
#define CLK_BT32K_GATE            239U

/********Name=CLKSEL_CON00,Offset=0x80********/
#define ACLK_DSP_S_DIV 0x06000000U
#define PCLK_DSP_DIV   0x06080000U
/********Name=CLKSEL_CON02,Offset=0x88********/
#define SCLK_SHRM_DIV 0x04000002U
#define PCLK_SHRM_DIV 0x05080002U
/********Name=CLKSEL_CON03,Offset=0x8C********/
#define CLK_UART0_SRC_DIV 0x05000003U
/********Name=CLKSEL_CON04,Offset=0x90********/
#define CLK_UART0_FRAC_DIV 0x20000004U
/********Name=CLKSEL_CON05,Offset=0x94********/
#define CLK_UART1_SRC_DIV 0x05000005U
/********Name=CLKSEL_CON06,Offset=0x98********/
#define CLK_UART1_FRAC_DIV 0x20000006U
/********Name=CLKSEL_CON07,Offset=0x9C********/
#define CLK_UART2_SRC_DIV 0x05000007U
/********Name=CLKSEL_CON08,Offset=0xA0********/
#define CLK_UART2_FRAC_DIV 0x20000008U
/********Name=CLKSEL_CON13,Offset=0xB4********/
#define CLK_I2C0_DIV 0x0400000DU
#define CLK_I2C1_DIV 0x0404000DU
#define CLK_I2C2_DIV 0x0408000DU
/********Name=CLKSEL_CON14,Offset=0xB8********/
#define MCLK_PDM0_DIV  0x0500000EU
#define HCLK_AUDIO_DIV 0x0508000EU
/********Name=CLKSEL_CON15,Offset=0xBC********/
#define MCLK_PDM0_OUT_DIV 0x2000000FU
/********Name=CLKSEL_CON16,Offset=0xC0********/
#define CLK_I2S8CH_SRC_DIV 0x05000010U
#define PCLK_AUDIO_DIV     0x05080010U
/********Name=CLKSEL_CON17,Offset=0xC4********/
#define CLK_I2S8CH_FRAC_DIV 0x20000011U
/********Name=CLKSEL_CON18,Offset=0xC8********/
#define ACLK_DMAC_DIV 0x05000012U
/********Name=CLKSEL_CON19,Offset=0xCC********/
#define ACLK_VOP_DIV 0x05000013U
/********Name=CLKSEL_CON20,Offset=0xD0********/
#define DCLK_VOP_S_DIV 0x05000014U
/********Name=CLKSEL_CON22,Offset=0xD8********/
/********Name=CLKSEL_CON23,Offset=0xDC********/
#define OCC_SCAN_CLK_DPHYLANBYTE_DIV 0x08000017U
/********Name=CLKSEL_CON24,Offset=0xE0********/
#define CLK_GPIO_DB0_DIV 0x0A000018U
/********Name=CLKSEL_CON25,Offset=0xE4********/
#define CLK_GPIO_DB1_DIV 0x0A000019U
/********Name=CLKSEL_CON27,Offset=0xEC********/
#define PCLK_ALIVE_DIV 0x0500001BU
/********Name=CLKSEL_CON28,Offset=0xF0********/
#define HCLK_ALIVE_DIV 0x0500001CU
/********Name=CLKSEL_CON30,Offset=0xF8********/
#define CLK_TESTOUT_DIV 0x0800001EU
/********Name=CLKSEL_CON31,Offset=0xFC********/
#define CLK_PDM_SAMP_DIV 0x0500001FU
/********Name=CLKSEL_CON33,Offset=0x104********/
#define HCLK_M4_DIV  0x05000021U
#define CLK_SPI1_DIV 0x05080021U
/********Name=CLKSEL_CON34,Offset=0x108********/
#define CLK_SPI2_DIV 0x05080022U
/********Name=CLKSEL_CON35,Offset=0x10C********/
#define SCLK_SFC_DIV 0x08000023U
#define CLK_SDIO_DIV 0x08080023U
/********Name=CLKSEL_CON36,Offset=0x110********/
/********Name=CLKSEL_CON37,Offset=0x114********/
#define CLK_AUDPWM_DF_DIV    0x05000025U
#define CLK_I2S1_8CH_SRC_DIV 0x05080025U
/********Name=CLKSEL_CON38,Offset=0x118********/
#define CLK_I2S1_8CH_FRAC_DIV 0x20000026U
/********Name=CLKSEL_CON39,Offset=0x11C********/
#define CLK_PWM_DIV    0x05000027U
#define HCLK_LOGIC_DIV 0x05080027U
/********Name=CLKSEL_CON40,Offset=0x120********/
#define PCLK_LOGIC_DIV 0x05000028U
#define ACLK_LOGIC_DIV 0x05080028U
/********Name=CLKSEL_CON41,Offset=0x124********/
#define CLK_CIFOUT_DIV 0x05000029U
/********Name=CLKSEL_CON42,Offset=0x128********/
#define CLK_AUDPWM_FRAC_DIV 0x2000002AU
/********Name=CLKSEL_CON43,Offset=0x12C********/
#define CLK_USB2PHY_REF_FRAC_DIV 0x2000002BU
/********Name=CLKSEL_CON44,Offset=0x130********/
#define CLK_DPHY_REF_FRAC_DIV 0x2000002CU
/********Name=CLKSEL_CON46,Offset=0x138********/
/********Name=CLKSEL_CON47,Offset=0x13C********/
#define SCLK_SFC1_DIV 0x0800002FU
/********Name=CLKSEL_CON49,Offset=0x144********/
#define XIN_OSC0_DIV 0x20000031U

/********Name=CLKSEL_CON00,Offset=0x80********/
#define ACLK_DSP_S_SEL               0x02060000U
#define ACLK_DSP_S_SEL_CLK_GPLL_MUX  0U
#define ACLK_DSP_S_SEL_CLK_CPLL_MUX  1U
#define ACLK_DSP_S_SEL_XIN_OSC0_FUNC 2U
/********Name=CLKSEL_CON02,Offset=0x88********/
#define SCLK_SHRM_SEL              0x01040002U
#define SCLK_SHRM_SEL_CLK_GPLL_MUX 0U
#define SCLK_SHRM_SEL_CLK_CPLL_MUX 1U
/********Name=CLKSEL_CON03,Offset=0x8C********/
#define CLK_UART0_SRC_SEL              0x01050003U
#define CLK_UART0_SRC_SEL_CLK_GPLL_MUX 0U
#define CLK_UART0_SRC_SEL_CLK_CPLL_MUX 1U
#define SCLK_UART0_SEL                 0x02060003U
#define SCLK_UART0_SEL_CLK_UART0_SRC   0U
#define SCLK_UART0_SEL_CLK_UART0_FRAC  1U
#define SCLK_UART0_SEL_XIN_OSC0_FUNC   2U
/********Name=CLKSEL_CON04,Offset=0x90********/
/********Name=CLKSEL_CON05,Offset=0x94********/
#define CLK_UART1_SRC_SEL              0x01050005U
#define CLK_UART1_SRC_SEL_CLK_GPLL_MUX 0U
#define CLK_UART1_SRC_SEL_CLK_CPLL_MUX 1U
#define SCLK_UART1_SEL                 0x02060005U
#define SCLK_UART1_SEL_CLK_UART1_SRC   0U
#define SCLK_UART1_SEL_CLK_UART1_FRAC  1U
#define SCLK_UART1_SEL_XIN_OSC0_FUNC   2U
/********Name=CLKSEL_CON06,Offset=0x98********/
/********Name=CLKSEL_CON07,Offset=0x9C********/
#define CLK_UART2_SRC_SEL              0x01050007U
#define CLK_UART2_SRC_SEL_CLK_GPLL_MUX 0U
#define CLK_UART2_SRC_SEL_CLK_CPLL_MUX 1U
#define SCLK_UART2_SEL                 0x02060007U
#define SCLK_UART2_SEL_CLK_UART2_SRC   0U
#define SCLK_UART2_SEL_CLK_UART2_FRAC  1U
#define SCLK_UART2_SEL_XIN_OSC0_FUNC   2U
/********Name=CLKSEL_CON08,Offset=0xA0********/
/********Name=CLKSEL_CON13,Offset=0xB4********/
/********Name=CLKSEL_CON14,Offset=0xB8********/
#define MCLK_PDM0_SEL               0x0107000EU
#define MCLK_PDM0_SEL_CLK_GPLL_MUX  0U
#define MCLK_PDM0_SEL_CLK_CPLL_MUX  1U
#define HCLK_AUDIO_SEL              0x010F000EU
#define HCLK_AUDIO_SEL_CLK_GPLL_MUX 0U
#define HCLK_AUDIO_SEL_CLK_CPLL_MUX 1U
/********Name=CLKSEL_CON15,Offset=0xBC********/
/********Name=CLKSEL_CON16,Offset=0xC0********/
#define CLK_I2S8CH_SRC_SEL               0x01050010U
#define CLK_I2S8CH_SRC_SEL_CLK_GPLL_MUX  0U
#define CLK_I2S8CH_SRC_SEL_CLK_CPLL_MUX  1U
#define MCLK_I2S8CH_SEL                  0x02060010U
#define MCLK_I2S8CH_SEL_CLK_I2S8CH_SRC   0U
#define MCLK_I2S8CH_SEL_CLK_I2S8CH_FRAC  1U
#define MCLK_I2S8CH_SEL_I2S_MCLKIN       2U
#define MCLK_I2S8CH_SEL_XIN_OSC0_HALF    3U
#define PCLK_AUDIO_SEL                   0x010E0010U
#define PCLK_AUDIO_SEL_CLK_GPLL_MUX      0U
#define PCLK_AUDIO_SEL_CLK_CPLL_MUX      1U
#define I2S_MCLKOUT_SEL                  0x010F0010U
#define I2S_MCLKOUT_SEL_MCLK_I2S8CH_NDFT 0U
#define I2S_MCLKOUT_SEL_XIN_OSC0_HALF    1U
/********Name=CLKSEL_CON17,Offset=0xC4********/
/********Name=CLKSEL_CON18,Offset=0xC8********/
#define ACLK_DMAC_SEL              0x01070012U
#define ACLK_DMAC_SEL_CLK_GPLL_MUX 0U
#define ACLK_DMAC_SEL_CLK_CPLL_MUX 1U
/********Name=CLKSEL_CON19,Offset=0xCC********/
#define ACLK_VOP_SEL              0x01070013U
#define ACLK_VOP_SEL_CLK_GPLL_MUX 0U
#define ACLK_VOP_SEL_CLK_CPLL_MUX 1U
/********Name=CLKSEL_CON20,Offset=0xD0********/
#define DCLK_VOP_S_SEL              0x01070014U
#define DCLK_VOP_S_SEL_CLK_GPLL_MUX 0U
#define DCLK_VOP_S_SEL_CLK_CPLL_MUX 1U
/********Name=CLKSEL_CON22,Offset=0xD8********/
#define OCC_SCAN_CLK_DPHYLANBYTE_SEL               0x02060016U
#define OCC_SCAN_CLK_DPHYLANBYTE_SEL_CLK_GPLL_MUX  0U
#define OCC_SCAN_CLK_DPHYLANBYTE_SEL_CLK_CPLL_MUX  1U
#define OCC_SCAN_CLK_DPHYLANBYTE_SEL_XIN_OSC0_FUNC 2U
/********Name=CLKSEL_CON23,Offset=0xDC********/
/********Name=CLKSEL_CON24,Offset=0xE0********/
/********Name=CLKSEL_CON25,Offset=0xE4********/
/********Name=CLKSEL_CON27,Offset=0xEC********/
/********Name=CLKSEL_CON28,Offset=0xF0********/
/********Name=CLKSEL_CON30,Offset=0xF8********/
#define CLK_TESTOUT_SEL                     0x0408001EU
#define CLK_TESTOUT_SEL_ACLK_DSP            0U
#define CLK_TESTOUT_SEL_HCLK_M4             1U
#define CLK_TESTOUT_SEL_XIN_OSC0_FUNC       2U
#define CLK_TESTOUT_SEL_CLK_DEEPSLOW        3U
#define CLK_TESTOUT_SEL_PCLK_CIF            4U
#define CLK_TESTOUT_SEL_CLK_USB2PHY_REF     5U
#define CLK_TESTOUT_SEL_CLK_DPHY_REF        6U
#define CLK_TESTOUT_SEL_CLK_MIPIPHY_LANBYTE 7U
#define CLK_TESTOUT_SEL_CLK_USBPHY48M       8U
#define CLK_TESTOUT_SEL_CLK_USBPHY480M      9U
#define CLK_TESTOUT_SEL_ACLK_LOGIC          10U
#define CLK_TESTOUT_SEL_CLK_AUDPWM          11U
#define CLK_TESTOUT_SEL_CLK_SDIO            12U
#define CLK_TESTOUT_SEL_MCLK_I2S8CH         13U
#define CLK_TESTOUT_SEL_DCLK_VOP            14U
#define CLK_TESTOUT_SEL_HCLK_AUDIO          15U
/********Name=CLKSEL_CON31,Offset=0xFC********/
#define CLK_PDM_SAMP_SEL              0x0105001FU
#define CLK_PDM_SAMP_SEL_CLK_GPLL_MUX 0U
#define CLK_PDM_SAMP_SEL_CLK_CPLL_MUX 1U
/********Name=CLKSEL_CON33,Offset=0x104********/
#define HCLK_M4_SEL              0x01070021U
#define HCLK_M4_SEL_CLK_GPLL_MUX 0U
#define HCLK_M4_SEL_CLK_CPLL_MUX 1U
/********Name=CLKSEL_CON34,Offset=0x108********/
#define SCLK_SFC_SEL              0x010E0022U
#define SCLK_SFC_SEL_CLK_GPLL_MUX 0U
#define SCLK_SFC_SEL_CLK_CPLL_MUX 1U
/********Name=CLKSEL_CON35,Offset=0x10C********/
/********Name=CLKSEL_CON36,Offset=0x110********/
#define CLK_SDIO_SEL                     0x02080024U
#define CLK_SDIO_SEL_CLK_GPLL_MUX        0U
#define CLK_SDIO_SEL_CLK_CPLL_MUX        1U
#define CLK_SDIO_SEL_XIN_OSC0_FUNC       2U
#define PCLK_CIF_SRC_SEL                 0x010C0024U
#define PCLK_CIF_SRC_SEL_PCLK_CIF        0U
#define PCLK_CIF_SRC_SEL_PCLK_CIF_INVERT 1U
/********Name=CLKSEL_CON37,Offset=0x114********/
#define CLK_AUDPWM_SEL                      0x01050025U
#define CLK_AUDPWM_SEL_CLK_AUDPWM_DF        0U
#define CLK_AUDPWM_SEL_CLK_AUDPWM_FRAC      1U
#define CLK_AUDPWM_SRC_SEL                  0x01060025U
#define CLK_AUDPWM_SRC_SEL_CLK_GPLL_MUX     0U
#define CLK_AUDPWM_SRC_SEL_CLK_CPLL_MUX     1U
#define I2S1_MCLKOUT_SEL                    0x01070025U
#define I2S1_MCLKOUT_SEL_MCLK_I2S1_8CH_NDFT 0U
#define I2S1_MCLKOUT_SEL_XIN_OSC0_HALF      1U
#define CLK_I2S1_8CH_SRC_SEL                0x010D0025U
#define CLK_I2S1_8CH_SRC_SEL_CLK_GPLL_MUX   0U
#define CLK_I2S1_8CH_SRC_SEL_CLK_CPLL_MUX   1U
#define MCLK_I2S1_8CH_SEL                   0x020E0025U
#define MCLK_I2S1_8CH_SEL_CLK_I2S1_8CH_SRC  0U
#define MCLK_I2S1_8CH_SEL_CLK_I2S1_8CH_FRAC 1U
#define MCLK_I2S1_8CH_SEL_I2S1_MCLKIN       2U
#define MCLK_I2S1_8CH_SEL_XIN_OSC0_HALF     3U
/********Name=CLKSEL_CON38,Offset=0x118********/
/********Name=CLKSEL_CON39,Offset=0x11C********/
#define CLK_PWM_SEL                 0x01050027U
#define CLK_PWM_SEL_CLK_GPLL_MUX    0U
#define CLK_PWM_SEL_XIN_OSC0_FUNC   1U
#define HCLK_LOGIC_SEL              0x010F0027U
#define HCLK_LOGIC_SEL_CLK_GPLL_MUX 0U
#define HCLK_LOGIC_SEL_CLK_CPLL_MUX 1U
/********Name=CLKSEL_CON40,Offset=0x120********/
#define PCLK_LOGIC_SEL              0x01070028U
#define PCLK_LOGIC_SEL_CLK_GPLL_MUX 0U
#define PCLK_LOGIC_SEL_CLK_CPLL_MUX 1U
#define ACLK_LOGIC_SEL              0x010F0028U
#define ACLK_LOGIC_SEL_CLK_GPLL_MUX 0U
#define ACLK_LOGIC_SEL_CLK_CPLL_MUX 1U
/********Name=CLKSEL_CON41,Offset=0x124********/
#define CLK_CIFOUT_SEL                           0x02060029U
#define CLK_CIFOUT_SEL_CLK_GPLL_MUX              0U
#define CLK_CIFOUT_SEL_CLK_CPLL_MUX              1U
#define CLK_CIFOUT_SEL_XIN_OSC0_FUNC             2U
#define CLK_USB2PHY_REF_FRAC_SEL                 0x01080029U
#define CLK_USB2PHY_REF_FRAC_SEL_CLK_GPLL_MUX    0U
#define CLK_USB2PHY_REF_FRAC_SEL_CLK_CPLL_MUX    1U
#define CLK_USB2PHY_REF_SEL                      0x01090029U
#define CLK_USB2PHY_REF_SEL_XIN_OSC0_HALF        0U
#define CLK_USB2PHY_REF_SEL_CLK_USB2PHY_REF_FRAC 1U
#define CLK_DPHY_REF_FRAC_SEL                    0x010A0029U
#define CLK_DPHY_REF_FRAC_SEL_CLK_GPLL_MUX       0U
#define CLK_DPHY_REF_FRAC_SEL_CLK_CPLL_MUX       1U
#define CLK_DPHY_REF_SEL                         0x010B0029U
#define CLK_DPHY_REF_SEL_XIN_OSC0_FUNC           0U
#define CLK_DPHY_REF_SEL_CLK_DPHY_REF_FRAC       1U
/********Name=CLKSEL_CON42,Offset=0x128********/
/********Name=CLKSEL_CON43,Offset=0x12C********/
/********Name=CLKSEL_CON44,Offset=0x130********/
/********Name=CLKSEL_CON46,Offset=0x138********/
#define SCLK_SFC1_SEL              0x010E002EU
#define SCLK_SFC1_SEL_CLK_GPLL_MUX 0U
#define SCLK_SFC1_SEL_CLK_CPLL_MUX 1U
/********Name=CLKSEL_CON47,Offset=0x13C********/
/********Name=CLKSEL_CON49,Offset=0x144********/

#define CLK(mux, div) \
    (((mux) & 0x0F0F00FFU) | (((div) & 0xFFU) << 8) | (((div) & 0x0F0F0000U) << 4))

#ifndef __ASSEMBLY__
typedef enum CLOCK_Name {
    CLK_INVALID = 0U,
    PLL_GPLL,
    PLL_CPLL,
    ACLK_DSP                 = CLK(ACLK_DSP_S_SEL, ACLK_DSP_S_DIV),
    PCLK_DSP                 = CLK(0U, PCLK_DSP_DIV),
    SCLK_SHRM                = CLK(SCLK_SHRM_SEL, SCLK_SHRM_DIV),
    PCLK_SHRM                = CLK(0U, PCLK_SHRM_DIV),
    CLK_UART0_SRC            = CLK(CLK_UART0_SRC_SEL, CLK_UART0_SRC_DIV),
    CLK_UART0_FRAC           = CLK(0U, CLK_UART0_FRAC_DIV),
    CLK_UART0                = CLK(SCLK_UART0_SEL, 0U),
    CLK_UART1_SRC            = CLK(CLK_UART1_SRC_SEL, CLK_UART1_SRC_DIV),
    CLK_UART1_FRAC           = CLK(0U, CLK_UART1_FRAC_DIV),
    CLK_UART1                = CLK(SCLK_UART1_SEL, 0U),
    CLK_UART2_SRC            = CLK(CLK_UART2_SRC_SEL, CLK_UART2_SRC_DIV),
    CLK_UART2_FRAC           = CLK(0U, CLK_UART2_FRAC_DIV),
    CLK_UART2                = CLK(SCLK_UART2_SEL, 0U),
    CLK_I2C0                 = CLK(0U, CLK_I2C0_DIV),
    CLK_I2C1                 = CLK(0U, CLK_I2C1_DIV),
    CLK_I2C2                 = CLK(0U, CLK_I2C2_DIV),
    MCLK_PDM0                = CLK(MCLK_PDM0_SEL, MCLK_PDM0_DIV),
    HCLK_AUDIO               = CLK(HCLK_AUDIO_SEL, HCLK_AUDIO_DIV),
    CLK_I2S8CH_SRC           = CLK(CLK_I2S8CH_SRC_SEL, CLK_I2S8CH_SRC_DIV),
    CLK_I2S8CH_FRAC          = CLK(0U, CLK_I2S8CH_FRAC_DIV),
    MCLK_I2S8CH              = CLK(MCLK_I2S8CH_SEL, 0U),
    I2S_MCLKOUT              = CLK(I2S_MCLKOUT_SEL, 0U),
    ACLK_DMAC                = CLK(ACLK_DMAC_SEL, ACLK_DMAC_DIV),
    PCLK_AUDIO               = CLK(PCLK_AUDIO_SEL, PCLK_AUDIO_DIV),
    ACLK_VOP                 = CLK(ACLK_VOP_SEL, ACLK_VOP_DIV),
    DCLK_VOP_S               = CLK(DCLK_VOP_S_SEL, DCLK_VOP_S_DIV),
    OCC_SCAN_CLK_DPHYLANBYTE = CLK(OCC_SCAN_CLK_DPHYLANBYTE_SEL, OCC_SCAN_CLK_DPHYLANBYTE_DIV),
    CLK_GPIO_DBG0            = CLK(0U, CLK_GPIO_DB0_DIV),
    CLK_GPIO_DBG1            = CLK(0U, CLK_GPIO_DB1_DIV),
    PCLK_ALIVE               = CLK(0U, PCLK_ALIVE_DIV),
    HCLK_ALIVE               = CLK(0U, HCLK_ALIVE_DIV),
    CLK_TESTOUT              = CLK(CLK_TESTOUT_SEL, CLK_TESTOUT_DIV),
    CLK_PDM_SAMP             = CLK(CLK_PDM_SAMP_SEL, CLK_PDM_SAMP_DIV),
    HCLK_M4                  = CLK(HCLK_M4_SEL, HCLK_M4_DIV),
    CLK_SPI1                 = CLK(0U, CLK_SPI1_DIV),
    SCLK_SFC_SRC             = CLK(SCLK_SFC_SEL, SCLK_SFC_DIV),
    CLK_SPI2                 = CLK(0U, CLK_SPI2_DIV),
    CLK_SDIO_SRC             = CLK(CLK_SDIO_SEL, CLK_SDIO_DIV),
    CLK_AUDPWM_SRC           = CLK(CLK_AUDPWM_SRC_SEL, CLK_AUDPWM_DF_DIV),
    CLK_AUDPWM_FRAC          = CLK(0U, CLK_AUDPWM_FRAC_DIV),
    CLK_AUDPWM               = CLK(CLK_AUDPWM_SEL, 0U),
    CLK_I2S1_8CH_SRC         = CLK(CLK_I2S1_8CH_SRC_SEL, CLK_I2S1_8CH_SRC_DIV),
    CLK_I2S1_8CH_FRAC        = CLK(0U, CLK_I2S1_8CH_FRAC_DIV),
    MCLK_I2S1_8CH            = CLK(MCLK_I2S1_8CH_SEL, 0U),
    I2S1_MCLKOUT             = CLK(I2S1_MCLKOUT_SEL, 0U),
    CLK_PWM                  = CLK(CLK_PWM_SEL, CLK_PWM_DIV),
    HCLK_LOGIC               = CLK(HCLK_LOGIC_SEL, HCLK_LOGIC_DIV),
    PCLK_LOGIC               = CLK(PCLK_LOGIC_SEL, PCLK_LOGIC_DIV),
    ACLK_LOGIC               = CLK(ACLK_LOGIC_SEL, ACLK_LOGIC_DIV),
    CLK_CIFOUT               = CLK(CLK_CIFOUT_SEL, CLK_CIFOUT_DIV),
    CLK_USB2PHY_REF_FRAC     = CLK(CLK_USB2PHY_REF_FRAC_SEL, CLK_USB2PHY_REF_FRAC_DIV),
    CLK_USB2PHY_REF          = CLK(CLK_USB2PHY_REF_SEL, 0U),
    CLK_DPHY_REF_FRAC        = CLK(CLK_DPHY_REF_FRAC_SEL, CLK_DPHY_REF_FRAC_DIV),
    CLK_DPHY_REF             = CLK(CLK_DPHY_REF_SEL, 0U),
    SCLK_SFC1_SRC            = CLK(SCLK_SFC1_SEL, SCLK_SFC1_DIV),
    CLK_32K                  = CLK(0U, XIN_OSC0_DIV),
} eCLOCK_Name;
#endif /* __ASSEMBLY__ */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __RK2108_H */
