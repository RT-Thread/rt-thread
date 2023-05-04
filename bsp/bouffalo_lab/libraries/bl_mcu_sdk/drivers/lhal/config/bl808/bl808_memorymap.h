#ifndef __BL808_MEMORYMAP_H
#define __BL808_MEMORYMAP_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/
#define BL808_OCRAM_BASE           (0x22020000)
#define BL808_OCRAM_END            (0x22020000 + 64 * 1024)
#define BL808_OCRAM_CACHEABLE_BASE (0x62020000)
#define BL808_OCRAM_CACHEABLE_END  (0x62020000 + 64 * 1024)

#define BL808_WRAM_BASE           (0x22030000)
#define BL808_WRAM_END            (0x22030000 + 160 * 1024)
#define BL808_WRAM_CACHEABLE_BASE (0x62030000)
#define BL808_WRAM_CACHEABLE_END  (0x62030000 + 160 * 1024)

#define BL808_MCU_ALLRAM_BASE           (0x22020000)
#define BL808_MCU_ALLRAM_END            (0x22020000 + 64 * 1024 + 160 * 1024)
#define BL808_MCU_ALLRAM_CACHEABLE_BASE (0x62020000)
#define BL808_MCU_ALLRAM_CACHEABLE_END  (0x62020000 + 64 * 1024 + 160 * 1024)

#define BL808_DRAM_BASE           (0x3EF80000)
#define BL808_DRAM_END            (0x3EF80000 + 512 * 1024)
#define BL808_DRAM_CACHEABLE_BASE (0x7EF80000)
#define BL808_DRAM_CACHEABLE_END  (0x7EF80000 + 512 * 1024)

#define BL808_VRAM_BASE           (0x3F000000)
#define BL808_VRAM_END            (0x3F000000 + 32 * 1024)
#define BL808_VRAM_CACHEABLE_BASE (0x7F000000)
#define BL808_VRAM_CACHEABLE_END  (0x7F000000 + 32 * 1024)

#define BL808_MM_ALLRAM_BASE           (0x3EF80000)
#define BL808_MM_ALLRAM_END            (0x3EF80000 + 512 * 1024 + 32 * 1024)
#define BL808_MM_ALLRAM_CACHEABLE_BASE (0x7EF80000)
#define BL808_MM_ALLRAM_CACHEABLE_END  (0x7EF80000 + 512 * 1024 + 32 * 1024)

#define BL808_FLASH_XIP_BASE         (0x58000000)
#define BL808_FLASH_XIP_END          (0x58000000 + 64 * 1024 * 1024)
#define BL808_FLASH2_XIP_BASE        (0x5C000000)
#define BL808_FLASH2_XIP_END         (0x5C000000 + 64 * 1024 * 1024)
#define BL808_FLASH_XIP_REMAP0_BASE  (0xD8000000)
#define BL808_FLASH_XIP_REMAP0_END   (0xD8000000 + 64 * 1024 * 1024)
#define BL808_FLASH2_XIP_REMAP0_BASE (0xDC000000)
#define BL808_FLASH2_XIP_REMAP0_END  (0xDC000000 + 64 * 1024 * 1024)

#define BL808_MM_WHOLERAM_BASE           (0x3EF80000)
#define BL808_MM_WHOLERAM_END            (0x3EF80000 + 512 * 1024 + 96 * 1024)
#define BL808_MM_WHOLERAM_CACHEABLE_BASE (0x7EF80000)
#define BL808_MM_WHOLERAM_CACHEABLE_END  (0x7EF80000 + 512 * 1024 + 96 * 1024)

/*@} end of group Memory_Map_Section */

/* BL808 peripherals base address */
/* WLSYS */
#define GLB_BASE         ((uint32_t)0x20000000)
#define MIX_BASE         ((uint32_t)0x20001000)
#define GPIP_BASE        ((uint32_t)0x20002000)
#define PHY_BASE         ((uint32_t)0x20002800)
#define AGC_BASE         ((uint32_t)0x20002c00)
#define SEC_DBG_BASE     ((uint32_t)0x20003000)
#define SEC_ENG_BASE     ((uint32_t)0x20004000)
#define TZ1_BASE         ((uint32_t)0x20005000)
#define TZC_SEC_BASE     ((uint32_t)0x20005000)
#define TZ2_BASE         ((uint32_t)0x20006000)
#define TZC_NSEC_BASE    ((uint32_t)0x20006000)
#define EFUSE_BASE       ((uint32_t)0x20056000)
#define EF_DATA_BASE     ((uint32_t)0x20056000)
#define EF_CTRL_BASE     ((uint32_t)0x20056000)
#define CCI_BASE         ((uint32_t)0x20008000)
#define MCU_MISC_BASE    ((uint32_t)0x20009000)
#define L1C_BASE         ((uint32_t)0x20009000)
#define UART0_BASE       ((uint32_t)0x2000a000)
#define UART1_BASE       ((uint32_t)0x2000a100)
#define SPI0_BASE        ((uint32_t)0x2000a200)
#define I2C0_BASE        ((uint32_t)0x2000a300)
#define PWM_BASE         ((uint32_t)0x2000a400)
#define TIMER0_BASE      ((uint32_t)0x2000a500)
#define IR_BASE          ((uint32_t)0x2000a600)
#define CKS_BASE         ((uint32_t)0x2000a700)
#define IPC0_BASE        ((uint32_t)0x2000a800)
#define IPC1_BASE        ((uint32_t)0x2000a840)
#define I2C1_BASE        ((uint32_t)0x2000a900)
#define UART2_BASE       ((uint32_t)0x2000aa00)
#define I2S_BASE         ((uint32_t)0x2000ab00)
#define PDM0_BASE        ((uint32_t)0x2000a000)
#define LZ4D_BASE        ((uint32_t)0x2000ad00)
#define QSPI_BASE        ((uint32_t)0x2000b000)
#define SF_CTRL_BASE     ((uint32_t)0x2000b000)
#define SF_CTRL_BUF_BASE ((uint32_t)0x2000b600)
#define DMA0_BASE        ((uint32_t)0x2000c000)
#define PDS_BASE         ((uint32_t)0x2000e000)
#define HBN_BASE         ((uint32_t)0x2000f000)
#define AON_BASE         ((uint32_t)0x2000f000)
#define EMI_MISC_BASE    ((uint32_t)0x20050000)
#define PSRAM_CTRL_BASE  ((uint32_t)0x20052000)
#define USB_BASE         ((uint32_t)0x20072000)
#define AUDIO_BASE       ((uint32_t)0x20055000)
#define SDH_BASE         ((uint32_t)0x20060000)
#define EMAC_BASE        ((uint32_t)0x20070000)
#define DMA1_BASE        ((uint32_t)0x20071000)

/* MMSYS */
#define MM_MISC_BASE     ((uint32_t)0x30000000)
#define DMA2_BASE        ((uint32_t)0x30001000)
#define UART3_BASE       ((uint32_t)0x30002000)
#define I2C2_BASE        ((uint32_t)0x30003000)
#define I2C3_BASE        ((uint32_t)0x30004000)
#define IPC2_BASE        ((uint32_t)0x30005000)
#define DMA2D_BASE       ((uint32_t)0x30006000)
#define CLKRST_CTRL_BASE ((uint32_t)0x30007000)
#define MM_GLB_BASE      ((uint32_t)0x30007000)
#define SPI1_BASE        ((uint32_t)0x30008000)
#define TIMER1_BASE      ((uint32_t)0x30009000)
#define PSRAM_UHS_BASE   ((uint32_t)0x3000f000)

/* MM_SUBSYS */
#define CAM_FRONT_BASE       ((uint32_t)0x30010000)
#define MM_SUBSYS_BASE       ((uint32_t)0x30011000)
#define DVP0_BASE            ((uint32_t)0x30012000)
#define DVP1_BASE            ((uint32_t)0x30012100)
#define DVP2_BASE            ((uint32_t)0x30012200)
#define DVP3_BASE            ((uint32_t)0x30012300)
#define DVP4_BASE            ((uint32_t)0x30012400)
#define DVP5_BASE            ((uint32_t)0x30012500)
#define DVP6_BASE            ((uint32_t)0x30012600)
#define DVP7_BASE            ((uint32_t)0x30012700)
#define DVP_TSRC0_BASE       ((uint32_t)0x30012800)
#define DVP_TSRC1_BASE       ((uint32_t)0x30012900)
#define AXI_CTRL_NR3D_BASE   ((uint32_t)0x30012a00)
#define OSD_PROBE_BASE       ((uint32_t)0x30012b00)
#define OSD_A_BASE           ((uint32_t)0x30013000)
#define OSD_B_BASE           ((uint32_t)0x30014000)
#define OSD_DP_BASE          ((uint32_t)0x30015000)
#define OSD_BLEND0_OFFSET    (0x000)
#define OSD_BLEND1_OFFSET    (0x100)
#define OSD_BLEND2_OFFSET    (0x200)
#define OSD_BLEND3_OFFSET    (0x300)
#define OSD_DRAW_LOW_OFFSET  (0x400)
#define OSD_DRAW_HIGH_OFFSET (0x504)
#define MIPI_BASE            ((uint32_t)0x3001a000)
#define DBI_BASE             ((uint32_t)0x3001b000)
#define DSI_BASE             ((uint32_t)0x3001a100)
#define CSI_BASE             ((uint32_t)0x3001a000)

/* CODEC_SUBSYS */
#define CODEC_MISC_BASE ((uint32_t)0x30020000)
#define MJPEG_BASE      ((uint32_t)0x30021000)
#define VIDEO_BASE      ((uint32_t)0x30022000)
#define MJPEG_DEC_BASE  ((uint32_t)0x30023000)
#define BL_CNN_BASE     ((uint32_t)0x30024000)

#define HBN_RAM_BASE ((uint32_t)0x20010000)

#define RF_BASE ((uint32_t)0x20001000)

#endif