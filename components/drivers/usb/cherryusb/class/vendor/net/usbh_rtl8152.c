/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbh_core.h"
#include "usbh_rtl8152.h"

#undef USB_DBG_TAG
#define USB_DBG_TAG "rtl8152"
#include "usb_log.h"

#define DEV_FORMAT "/dev/rtl8152"

static USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_rtl8152_rx_buffer[CONFIG_USBHOST_RTL8152_ETH_MAX_RX_SIZE];
static USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_rtl8152_tx_buffer[CONFIG_USBHOST_RTL8152_ETH_MAX_TX_SIZE];
static USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_rtl8152_inttx_buffer[2];
USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_rtl8152_buf[32];

static struct usbh_rtl8152 g_rtl8152_class;

#define RTL8152_REQ_GET_REGS 0x05
#define RTL8152_REQ_SET_REGS 0x05

#define BYTE_EN_DWORD      0xff
#define BYTE_EN_WORD       0x33
#define BYTE_EN_BYTE       0x11
#define BYTE_EN_SIX_BYTES  0x3f
#define BYTE_EN_START_MASK 0x0f
#define BYTE_EN_END_MASK   0xf0

#define MCU_TYPE_PLA 0x0100
#define MCU_TYPE_USB 0x0000

/* Define these values to match your device */
#define VENDOR_ID_REALTEK   0x0bda
#define VENDOR_ID_MICROSOFT 0x045e
#define VENDOR_ID_SAMSUNG   0x04e8
#define VENDOR_ID_LENOVO    0x17ef
#define VENDOR_ID_LINKSYS   0x13b1
#define VENDOR_ID_NVIDIA    0x0955
#define VENDOR_ID_TPLINK    0x2357
#define VENDOR_ID_DLINK     0x2001
#define VENDOR_ID_ASUS      0x0b05

#define R8152_PHY_ID 32

#define PLA_IDR              0xc000
#define PLA_RCR              0xc010
#define PLA_RCR1             0xc012
#define PLA_RMS              0xc016
#define PLA_RXFIFO_CTRL0     0xc0a0
#define PLA_RXFIFO_FULL      0xc0a2
#define PLA_RXFIFO_CTRL1     0xc0a4
#define PLA_RX_FIFO_FULL     0xc0a6
#define PLA_RXFIFO_CTRL2     0xc0a8
#define PLA_RX_FIFO_EMPTY    0xc0aa
#define PLA_DMY_REG0         0xc0b0
#define PLA_FMC              0xc0b4
#define PLA_CFG_WOL          0xc0b6
#define PLA_TEREDO_CFG       0xc0bc
#define PLA_TEREDO_WAKE_BASE 0xc0c4
#define PLA_MAR              0xcd00
#define PLA_BACKUP           0xd000
#define PLA_BDC_CR           0xd1a0
#define PLA_TEREDO_TIMER     0xd2cc
#define PLA_REALWOW_TIMER    0xd2e8
#define PLA_UPHY_TIMER       0xd388
#define PLA_SUSPEND_FLAG     0xd38a
#define PLA_INDICATE_FALG    0xd38c
#define PLA_MACDBG_PRE       0xd38c /* RTL_VER_04 only */
#define PLA_MACDBG_POST      0xd38e /* RTL_VER_04 only */
#define PLA_EXTRA_STATUS     0xd398
#define PLA_GPHY_CTRL        0xd3ae
#define PLA_POL_GPIO_CTRL    0xdc6a
#define PLA_EFUSE_DATA       0xdd00
#define PLA_EFUSE_CMD        0xdd02
#define PLA_LEDSEL           0xdd90
#define PLA_LED_FEATURE      0xdd92
#define PLA_PHYAR            0xde00
#define PLA_BOOT_CTRL        0xe004
#define PLA_LWAKE_CTRL_REG   0xe007
#define PLA_GPHY_INTR_IMR    0xe022
#define PLA_EEE_CR           0xe040
#define PLA_EEE_TXTWSYS      0xe04c
#define PLA_EEE_TXTWSYS_2P5G 0xe058
#define PLA_EEEP_CR          0xe080
#define PLA_MAC_PWR_CTRL     0xe0c0
#define PLA_MAC_PWR_CTRL2    0xe0ca
#define PLA_MAC_PWR_CTRL3    0xe0cc
#define PLA_MAC_PWR_CTRL4    0xe0ce
#define PLA_WDT6_CTRL        0xe428
#define PLA_TCR0             0xe610
#define PLA_TCR1             0xe612
#define PLA_MTPS             0xe615
#define PLA_TXFIFO_CTRL      0xe618
#define PLA_TXFIFO_FULL      0xe61a
#define PLA_RSTTALLY         0xe800
#define PLA_CR               0xe813
#define PLA_CRWECR           0xe81c
#define PLA_CONFIG12         0xe81e /* CONFIG1, CONFIG2 */
#define PLA_CONFIG34         0xe820 /* CONFIG3, CONFIG4 */
#define PLA_CONFIG5          0xe822
#define PLA_PHY_PWR          0xe84c
#define PLA_OOB_CTRL         0xe84f
#define PLA_CPCR             0xe854
#define PLA_MISC_0           0xe858
#define PLA_MISC_1           0xe85a
#define PLA_OCP_GPHY_BASE    0xe86c
#define PLA_TALLYCNT         0xe890
#define PLA_SFF_STS_7        0xe8de
#define PLA_PHYSTATUS        0xe908
#define PLA_CONFIG6          0xe90a /* CONFIG6 */
#define PLA_USB_CFG          0xe952
#define PLA_BP_BA            0xfc26
#define PLA_BP_0             0xfc28
#define PLA_BP_1             0xfc2a
#define PLA_BP_2             0xfc2c
#define PLA_BP_3             0xfc2e
#define PLA_BP_4             0xfc30
#define PLA_BP_5             0xfc32
#define PLA_BP_6             0xfc34
#define PLA_BP_7             0xfc36
#define PLA_BP_EN            0xfc38

#define USB_USB2PHY           0xb41e
#define USB_SSPHYLINK1        0xb426
#define USB_SSPHYLINK2        0xb428
#define USB_L1_CTRL           0xb45e
#define USB_U2P3_CTRL         0xb460
#define USB_CSR_DUMMY1        0xb464
#define USB_CSR_DUMMY2        0xb466
#define USB_DEV_STAT          0xb808
#define USB_CONNECT_TIMER     0xcbf8
#define USB_MSC_TIMER         0xcbfc
#define USB_BURST_SIZE        0xcfc0
#define USB_FW_FIX_EN0        0xcfca
#define USB_FW_FIX_EN1        0xcfcc
#define USB_LPM_CONFIG        0xcfd8
#define USB_ECM_OPTION        0xcfee
#define USB_CSTMR             0xcfef /* RTL8153A */
#define USB_MISC_2            0xcfff
#define USB_ECM_OP            0xd26b
#define USB_GPHY_CTRL         0xd284
#define USB_SPEED_OPTION      0xd32a
#define USB_FW_CTRL           0xd334 /* RTL8153B */
#define USB_FC_TIMER          0xd340
#define USB_USB_CTRL          0xd406
#define USB_PHY_CTRL          0xd408
#define USB_TX_AGG            0xd40a
#define USB_RX_BUF_TH         0xd40c
#define USB_USB_TIMER         0xd428
#define USB_RX_EARLY_TIMEOUT  0xd42c
#define USB_RX_EARLY_SIZE     0xd42e
#define USB_PM_CTRL_STATUS    0xd432 /* RTL8153A */
#define USB_RX_EXTRA_AGGR_TMR 0xd432 /* RTL8153B */
#define USB_TX_DMA            0xd434
#define USB_UPT_RXDMA_OWN     0xd437
#define USB_UPHY3_MDCMDIO     0xd480
#define USB_TOLERANCE         0xd490
#define USB_LPM_CTRL          0xd41a
#define USB_BMU_RESET         0xd4b0
#define USB_BMU_CONFIG        0xd4b4
#define USB_U1U2_TIMER        0xd4da
#define USB_FW_TASK           0xd4e8 /* RTL8153B */
#define USB_RX_AGGR_NUM       0xd4ee
#define USB_UPS_CTRL          0xd800
#define USB_POWER_CUT         0xd80a
#define USB_MISC_0            0xd81a
#define USB_MISC_1            0xd81f
#define USB_AFE_CTRL2         0xd824
#define USB_UPHY_XTAL         0xd826
#define USB_UPS_CFG           0xd842
#define USB_UPS_FLAGS         0xd848
#define USB_WDT1_CTRL         0xe404
#define USB_WDT11_CTRL        0xe43c
#define USB_BP_BA             PLA_BP_BA
#define USB_BP_0              PLA_BP_0
#define USB_BP_1              PLA_BP_1
#define USB_BP_2              PLA_BP_2
#define USB_BP_3              PLA_BP_3
#define USB_BP_4              PLA_BP_4
#define USB_BP_5              PLA_BP_5
#define USB_BP_6              PLA_BP_6
#define USB_BP_7              PLA_BP_7
#define USB_BP_EN             PLA_BP_EN /* RTL8153A */
#define USB_BP_8              0xfc38    /* RTL8153B */
#define USB_BP_9              0xfc3a
#define USB_BP_10             0xfc3c
#define USB_BP_11             0xfc3e
#define USB_BP_12             0xfc40
#define USB_BP_13             0xfc42
#define USB_BP_14             0xfc44
#define USB_BP_15             0xfc46
#define USB_BP2_EN            0xfc48

/* OCP Registers */
#define OCP_ALDPS_CONFIG   0x2010
#define OCP_EEE_CONFIG1    0x2080
#define OCP_EEE_CONFIG2    0x2092
#define OCP_EEE_CONFIG3    0x2094
#define OCP_BASE_MII       0xa400
#define OCP_EEE_AR         0xa41a
#define OCP_EEE_DATA       0xa41c
#define OCP_PHY_STATUS     0xa420
#define OCP_INTR_EN        0xa424
#define OCP_NCTL_CFG       0xa42c
#define OCP_POWER_CFG      0xa430
#define OCP_EEE_CFG        0xa432
#define OCP_SRAM_ADDR      0xa436
#define OCP_SRAM_DATA      0xa438
#define OCP_DOWN_SPEED     0xa442
#define OCP_EEE_ABLE       0xa5c4
#define OCP_EEE_ADV        0xa5d0
#define OCP_EEE_LPABLE     0xa5d2
#define OCP_10GBT_CTRL     0xa5d4
#define OCP_10GBT_STAT     0xa5d6
#define OCP_EEE_ADV2       0xa6d4
#define OCP_PHY_STATE      0xa708 /* nway state for 8153 */
#define OCP_PHY_PATCH_STAT 0xb800
#define OCP_PHY_PATCH_CMD  0xb820
#define OCP_PHY_LOCK       0xb82e
#define OCP_ADC_IOFFSET    0xbcfc
#define OCP_ADC_CFG        0xbc06
#define OCP_SYSCLK_CFG     0xc416

/* SRAM Register */
#define SRAM_GREEN_CFG   0x8011
#define SRAM_LPF_CFG     0x8012
#define SRAM_GPHY_FW_VER 0x801e
#define SRAM_10M_AMP1    0x8080
#define SRAM_10M_AMP2    0x8082
#define SRAM_IMPEDANCE   0x8084
#define SRAM_PHY_LOCK    0xb82e

/* PLA_RCR */
#define RCR_AAP      0x00000001
#define RCR_APM      0x00000002
#define RCR_AM       0x00000004
#define RCR_AB       0x00000008
#define RCR_ACPT_ALL (RCR_AAP | RCR_APM | RCR_AM | RCR_AB)
#define SLOT_EN      BIT(11)

/* PLA_RCR1 */
#define OUTER_VLAN BIT(7)
#define INNER_VLAN BIT(6)

/* PLA_RXFIFO_CTRL0 */
#define RXFIFO_THR1_NORMAL 0x00080002
#define RXFIFO_THR1_OOB    0x01800003

/* PLA_RXFIFO_FULL */
#define RXFIFO_FULL_MASK 0xfff

/* PLA_RXFIFO_CTRL1 */
#define RXFIFO_THR2_FULL   0x00000060
#define RXFIFO_THR2_HIGH   0x00000038
#define RXFIFO_THR2_OOB    0x0000004a
#define RXFIFO_THR2_NORMAL 0x00a0

/* PLA_RXFIFO_CTRL2 */
#define RXFIFO_THR3_FULL   0x00000078
#define RXFIFO_THR3_HIGH   0x00000048
#define RXFIFO_THR3_OOB    0x0000005a
#define RXFIFO_THR3_NORMAL 0x0110

/* PLA_TXFIFO_CTRL */
#define TXFIFO_THR_NORMAL  0x00400008
#define TXFIFO_THR_NORMAL2 0x01000008

/* PLA_DMY_REG0 */
#define ECM_ALDPS 0x0002

/* PLA_FMC */
#define FMC_FCR_MCU_EN 0x0001

/* PLA_EEEP_CR */
#define EEEP_CR_EEEP_TX 0x0002

/* PLA_WDT6_CTRL */
#define WDT6_SET_MODE 0x0010

/* PLA_TCR0 */
#define TCR0_TX_EMPTY  0x0800
#define TCR0_AUTO_FIFO 0x0080

/* PLA_TCR1 */
#define VERSION_MASK 0x7cf0
#define IFG_MASK     (BIT(3) | BIT(9) | BIT(8))
#define IFG_144NS    BIT(9)
#define IFG_96NS     (BIT(9) | BIT(8))

/* PLA_MTPS */
#define MTPS_JUMBO   (12 * 1024 / 64)
#define MTPS_DEFAULT (6 * 1024 / 64)

/* PLA_RSTTALLY */
#define TALLY_RESET 0x0001

/* PLA_CR */
#define CR_RST 0x10
#define CR_RE  0x08
#define CR_TE  0x04

/* PLA_CRWECR */
#define CRWECR_NORAML 0x00
#define CRWECR_CONFIG 0xc0

/* PLA_OOB_CTRL */
#define NOW_IS_OOB      0x80
#define TXFIFO_EMPTY    0x20
#define RXFIFO_EMPTY    0x10
#define LINK_LIST_READY 0x02
#define DIS_MCU_CLROOB  0x01
#define FIFO_EMPTY      (TXFIFO_EMPTY | RXFIFO_EMPTY)

/* PLA_MISC_1 */
#define RXDY_GATED_EN 0x0008

/* PLA_SFF_STS_7 */
#define RE_INIT_LL  0x8000
#define MCU_BORW_EN 0x4000

/* PLA_CPCR */
#define FLOW_CTRL_EN BIT(0)
#define CPCR_RX_VLAN 0x0040

/* PLA_CFG_WOL */
#define MAGIC_EN 0x0001

/* PLA_TEREDO_CFG */
#define TEREDO_SEL           0x8000
#define TEREDO_WAKE_MASK     0x7f00
#define TEREDO_RS_EVENT_MASK 0x00fe
#define OOB_TEREDO_EN        0x0001

/* PLA_BDC_CR */
#define ALDPS_PROXY_MODE 0x0001

/* PLA_EFUSE_CMD */
#define EFUSE_READ_CMD   BIT(15)
#define EFUSE_DATA_BIT16 BIT(7)

/* PLA_CONFIG34 */
#define LINK_ON_WAKE_EN  0x0010
#define LINK_OFF_WAKE_EN 0x0008

/* PLA_CONFIG6 */
#define LANWAKE_CLR_EN BIT(0)

/* PLA_USB_CFG */
#define EN_XG_LIP BIT(1)
#define EN_G_LIP  BIT(2)

/* PLA_CONFIG5 */
#define BWF_EN      0x0040
#define MWF_EN      0x0020
#define UWF_EN      0x0010
#define LAN_WAKE_EN 0x0002

/* PLA_LED_FEATURE */
#define LED_MODE_MASK 0x0700

/* PLA_PHY_PWR */
#define TX_10M_IDLE_EN 0x0080
#define PFM_PWM_SWITCH 0x0040
#define TEST_IO_OFF    BIT(4)

/* PLA_MAC_PWR_CTRL */
#define D3_CLK_GATED_EN    0x00004000
#define MCU_CLK_RATIO      0x07010f07
#define MCU_CLK_RATIO_MASK 0x0f0f0f0f
#define ALDPS_SPDWN_RATIO  0x0f87

/* PLA_MAC_PWR_CTRL2 */
#define EEE_SPDWN_RATIO      0x8007
#define MAC_CLK_SPDWN_EN     BIT(15)
#define EEE_SPDWN_RATIO_MASK 0xff

/* PLA_MAC_PWR_CTRL3 */
#define PLA_MCU_SPDWN_EN   BIT(14)
#define PKT_AVAIL_SPDWN_EN 0x0100
#define SUSPEND_SPDWN_EN   0x0004
#define U1U2_SPDWN_EN      0x0002
#define L1_SPDWN_EN        0x0001

/* PLA_MAC_PWR_CTRL4 */
#define PWRSAVE_SPDWN_EN 0x1000
#define RXDV_SPDWN_EN    0x0800
#define TX10MIDLE_EN     0x0100
#define IDLE_SPDWN_EN    BIT(6)
#define TP100_SPDWN_EN   0x0020
#define TP500_SPDWN_EN   0x0010
#define TP1000_SPDWN_EN  0x0008
#define EEE_SPDWN_EN     0x0001

/* PLA_GPHY_INTR_IMR */
#define GPHY_STS_MSK      0x0001
#define SPEED_DOWN_MSK    0x0002
#define SPDWN_RXDV_MSK    0x0004
#define SPDWN_LINKCHG_MSK 0x0008

/* PLA_PHYAR */
#define PHYAR_FLAG 0x80000000

/* PLA_EEE_CR */
#define EEE_RX_EN 0x0001
#define EEE_TX_EN 0x0002

/* PLA_BOOT_CTRL */
#define AUTOLOAD_DONE 0x0002

/* PLA_LWAKE_CTRL_REG */
#define LANWAKE_PIN BIT(7)

/* PLA_SUSPEND_FLAG */
#define LINK_CHG_EVENT BIT(0)

/* PLA_INDICATE_FALG */
#define UPCOMING_RUNTIME_D3 BIT(0)

/* PLA_MACDBG_PRE and PLA_MACDBG_POST */
#define DEBUG_OE    BIT(0)
#define DEBUG_LTSSM 0x0082

/* PLA_EXTRA_STATUS */
#define CUR_LINK_OK      BIT(15)
#define U3P3_CHECK_EN    BIT(7) /* RTL_VER_05 only */
#define LINK_CHANGE_FLAG BIT(8)
#define POLL_LINK_CHG    BIT(0)

/* PLA_GPHY_CTRL */
#define GPHY_FLASH BIT(1)

/* PLA_POL_GPIO_CTRL */
#define DACK_DET_EN    BIT(15)
#define POL_GPHY_PATCH BIT(4)

/* USB_USB2PHY */
#define USB2PHY_SUSPEND 0x0001
#define USB2PHY_L1      0x0002

/* USB_SSPHYLINK1 */
#define DELAY_PHY_PWR_CHG BIT(1)

/* USB_SSPHYLINK2 */
#define pwd_dn_scale_mask 0x3ffe
#define pwd_dn_scale(x)   ((x) << 1)

/* USB_CSR_DUMMY1 */
#define DYNAMIC_BURST 0x0001

/* USB_CSR_DUMMY2 */
#define EP4_FULL_FC 0x0001

/* USB_DEV_STAT */
#define STAT_SPEED_MASK 0x0006
#define STAT_SPEED_HIGH 0x0000
#define STAT_SPEED_FULL 0x0002

/* USB_FW_FIX_EN0 */
#define FW_FIX_SUSPEND BIT(14)

/* USB_FW_FIX_EN1 */
#define FW_IP_RESET_EN BIT(9)

/* USB_LPM_CONFIG */
#define LPM_U1U2_EN BIT(0)

/* USB_TX_AGG */
#define TX_AGG_MAX_THRESHOLD 0x03

/* USB_RX_BUF_TH */
#define RX_THR_SUPPER 0x0c350180
#define RX_THR_HIGH   0x7a120180
#define RX_THR_SLOW   0xffff0180
#define RX_THR_B      0x00010001

/* USB_TX_DMA */
#define TEST_MODE_DISABLE 0x00000001
#define TX_SIZE_ADJUST1   0x00000100

/* USB_BMU_RESET */
#define BMU_RESET_EP_IN  0x01
#define BMU_RESET_EP_OUT 0x02

/* USB_BMU_CONFIG */
#define ACT_ODMA BIT(1)

/* USB_UPT_RXDMA_OWN */
#define OWN_UPDATE BIT(0)
#define OWN_CLEAR  BIT(1)

/* USB_FW_TASK */
#define FC_PATCH_TASK BIT(1)

/* USB_RX_AGGR_NUM */
#define RX_AGGR_NUM_MASK 0x1ff

/* USB_UPS_CTRL */
#define POWER_CUT 0x0100

/* USB_PM_CTRL_STATUS */
#define RESUME_INDICATE 0x0001

/* USB_ECM_OPTION */
#define BYPASS_MAC_RESET BIT(5)

/* USB_CSTMR */
#define FORCE_SUPER BIT(0)

/* USB_MISC_2 */
#define UPS_FORCE_PWR_DOWN BIT(0)

/* USB_ECM_OP */
#define EN_ALL_SPEED BIT(0)

/* USB_GPHY_CTRL */
#define GPHY_PATCH_DONE BIT(2)
#define BYPASS_FLASH    BIT(5)
#define BACKUP_RESTRORE BIT(6)

/* USB_SPEED_OPTION */
#define RG_PWRDN_EN   BIT(8)
#define ALL_SPEED_OFF BIT(9)

/* USB_FW_CTRL */
#define FLOW_CTRL_PATCH_OPT BIT(1)
#define AUTO_SPEEDUP        BIT(3)
#define FLOW_CTRL_PATCH_2   BIT(8)

/* USB_FC_TIMER */
#define CTRL_TIMER_EN BIT(15)

/* USB_USB_CTRL */
#define CDC_ECM_EN     BIT(3)
#define RX_AGG_DISABLE 0x0010
#define RX_ZERO_EN     0x0080

/* USB_U2P3_CTRL */
#define U2P3_ENABLE 0x0001
#define RX_DETECT8  BIT(3)

/* USB_POWER_CUT */
#define PWR_EN      0x0001
#define PHASE2_EN   0x0008
#define UPS_EN      BIT(4)
#define USP_PREWAKE BIT(5)

/* USB_MISC_0 */
#define PCUT_STATUS 0x0001

/* USB_RX_EARLY_TIMEOUT */
#define COALESCE_SUPER 85000U
#define COALESCE_HIGH  250000U
#define COALESCE_SLOW  524280U

/* USB_WDT1_CTRL */
#define WTD1_EN BIT(0)

/* USB_WDT11_CTRL */
#define TIMER11_EN 0x0001

/* USB_LPM_CTRL */
/* bit 4 ~ 5: fifo empty boundary */
#define FIFO_EMPTY_1FB 0x30 /* 0x1fb * 64 = 32448 bytes */
/* bit 2 ~ 3: LMP timer */
#define LPM_TIMER_MASK  0x0c
#define LPM_TIMER_500MS 0x04 /* 500 ms */
#define LPM_TIMER_500US 0x0c /* 500 us */
#define ROK_EXIT_LPM    0x02

/* USB_AFE_CTRL2 */
#define SEN_VAL_MASK   0xf800
#define SEN_VAL_NORMAL 0xa000
#define SEL_RXIDLE     0x0100

/* USB_UPHY_XTAL */
#define OOBS_POLLING BIT(8)

/* USB_UPS_CFG */
#define SAW_CNT_1MS_MASK 0x0fff
#define MID_REVERSE      BIT(5) /* RTL8156A */

/* USB_UPS_FLAGS */
#define UPS_FLAGS_R_TUNE          BIT(0)
#define UPS_FLAGS_EN_10M_CKDIV    BIT(1)
#define UPS_FLAGS_250M_CKDIV      BIT(2)
#define UPS_FLAGS_EN_ALDPS        BIT(3)
#define UPS_FLAGS_CTAP_SHORT_DIS  BIT(4)
#define UPS_FLAGS_SPEED_MASK      (0xf << 16)
#define ups_flags_speed(x)        ((x) << 16)
#define UPS_FLAGS_EN_EEE          BIT(20)
#define UPS_FLAGS_EN_500M_EEE     BIT(21)
#define UPS_FLAGS_EN_EEE_CKDIV    BIT(22)
#define UPS_FLAGS_EEE_PLLOFF_100  BIT(23)
#define UPS_FLAGS_EEE_PLLOFF_GIGA BIT(24)
#define UPS_FLAGS_EEE_CMOD_LV_EN  BIT(25)
#define UPS_FLAGS_EN_GREEN        BIT(26)
#define UPS_FLAGS_EN_FLOW_CTR     BIT(27)

enum spd_duplex {
    NWAY_10M_HALF,
    NWAY_10M_FULL,
    NWAY_100M_HALF,
    NWAY_100M_FULL,
    NWAY_1000M_FULL,
    FORCE_10M_HALF,
    FORCE_10M_FULL,
    FORCE_100M_HALF,
    FORCE_100M_FULL,
    FORCE_1000M_FULL,
    NWAY_2500M_FULL,
};

/* OCP_ALDPS_CONFIG */
#define ENPWRSAVE  0x8000
#define ENPDNPS    0x0200
#define LINKENA    0x0100
#define DIS_SDSAVE 0x0010

/* OCP_PHY_STATUS */
#define PHY_STAT_MASK     0x0007
#define PHY_STAT_EXT_INIT 2
#define PHY_STAT_LAN_ON   3
#define PHY_STAT_PWRDN    5

/* OCP_INTR_EN */
#define INTR_SPEED_FORCE BIT(3)

/* OCP_NCTL_CFG */
#define PGA_RETURN_EN BIT(1)

/* OCP_POWER_CFG */
#define EEE_CLKDIV_EN 0x8000
#define EN_ALDPS      0x0004
#define EN_10M_PLLOFF 0x0001

/* OCP_EEE_CONFIG1 */
#define RG_TXLPI_MSK_HFDUP 0x8000
#define RG_MATCLR_EN       0x4000
#define EEE_10_CAP         0x2000
#define EEE_NWAY_EN        0x1000
#define TX_QUIET_EN        0x0200
#define RX_QUIET_EN        0x0100
#define sd_rise_time_mask  0x0070
#define sd_rise_time(x)    (MIN(x, 7) << 4) /* bit 4 ~ 6 */
#define RG_RXLPI_MSK_HFDUP 0x0008
#define SDFALLTIME         0x0007 /* bit 0 ~ 2 */

/* OCP_EEE_CONFIG2 */
#define RG_LPIHYS_NUM  0x7000 /* bit 12 ~ 15 */
#define RG_DACQUIET_EN 0x0400
#define RG_LDVQUIET_EN 0x0200
#define RG_CKRSEL      0x0020
#define RG_EEEPRG_EN   0x0010

/* OCP_EEE_CONFIG3 */
#define fast_snr_mask 0xff80
#define fast_snr(x)   (MIN(x, 0x1ff) << 7) /* bit 7 ~ 15 */
#define RG_LFS_SEL    0x0060               /* bit 6 ~ 5 */
#define MSK_PH        0x0006               /* bit 0 ~ 3 */

/* OCP_EEE_AR */
/* bit[15:14] function */
#define FUN_ADDR 0x0000
#define FUN_DATA 0x4000
/* bit[4:0] device addr */

/* OCP_EEE_CFG */
#define CTAP_SHORT_EN 0x0040
#define EEE10_EN      0x0010

/* OCP_DOWN_SPEED */
#define EN_EEE_CMODE  BIT(14)
#define EN_EEE_1000   BIT(13)
#define EN_EEE_100    BIT(12)
#define EN_10M_CLKDIV BIT(11)
#define EN_10M_BGOFF  0x0080

/* OCP_10GBT_CTRL */
#define RTL_ADV2_5G_F_R BIT(5) /* Advertise 2.5GBASE-T fast-retrain */

/* OCP_PHY_STATE */
#define TXDIS_STATE 0x01
#define ABD_STATE   0x02

/* OCP_PHY_PATCH_STAT */
#define PATCH_READY BIT(6)

/* OCP_PHY_PATCH_CMD */
#define PATCH_REQUEST BIT(4)

/* OCP_PHY_LOCK */
#define PATCH_LOCK BIT(0)

/* OCP_ADC_CFG */
#define CKADSEL_L 0x0100
#define ADC_EN    0x0080
#define EN_EMI_L  0x0040

/* OCP_SYSCLK_CFG */
#define sysclk_div_expo(x) (MIN(x, 5) << 8)
#define clk_div_expo(x)    (MIN(x, 5) << 4)

/* SRAM_GREEN_CFG */
#define GREEN_ETH_EN BIT(15)
#define R_TUNE_EN    BIT(11)

/* SRAM_LPF_CFG */
#define LPF_AUTO_TUNE 0x8000

/* SRAM_10M_AMP1 */
#define GDAC_IB_UPALL 0x0008

/* SRAM_10M_AMP2 */
#define AMP_DN 0x0200

/* SRAM_IMPEDANCE */
#define RX_DRIVING_MASK 0x6000

/* SRAM_PHY_LOCK */
#define PHY_PATCH_LOCK 0x0001

/* MAC PASSTHRU */
#define AD_MASK        0xfee0
#define BND_MASK       0x0004
#define BD_MASK        0x0001
#define EFUSE          0xcfdb
#define PASS_THRU_MASK 0x1

#define BP4_SUPER_ONLY 0x1578 /* RTL_VER_04 only */

enum rtl_register_content {
    _2500bps = BIT(10),
    _1250bps = BIT(9),
    _500bps = BIT(8),
    _tx_flow = BIT(6),
    _rx_flow = BIT(5),
    _1000bps = 0x10,
    _100bps = 0x08,
    _10bps = 0x04,
    LINK_STATUS = 0x02,
    FULL_DUP = 0x01,
};

#define is_speed_2500(_speed)   (((_speed) & (_2500bps | LINK_STATUS)) == (_2500bps | LINK_STATUS))
#define is_flow_control(_speed) (((_speed) & (_tx_flow | _rx_flow)) == (_tx_flow | _rx_flow))

#define RTL8152_MAX_TX 4
#define RTL8152_MAX_RX 10
#define INTBUFSIZE     2
#define TX_ALIGN       4
#define RX_ALIGN       8

#define RTL8152_RX_MAX_PENDING 4096
#define RTL8152_RXFG_HEADSZ    256

#define INTR_LINK 0x0004

#define VLAN_ETH_HLEN      18
#define ETH_FCS_LEN        4
#define VLAN_ETH_FRAME_LEN 1514

#define RTL8152_RMS         (VLAN_ETH_FRAME_LEN + ETH_FCS_LEN)
#define RTL8153_RMS         RTL8153_MAX_PACKET
#define mtu_to_size(m)      ((m) + VLAN_ETH_HLEN + ETH_FCS_LEN)
#define size_to_mtu(s)      ((s)-VLAN_ETH_HLEN - ETH_FCS_LEN)
#define rx_reserved_size(x) (mtu_to_size(x) + sizeof(struct rx_desc) + RX_ALIGN)

struct rx_desc {
    uint32_t opts1;
#define RD_CRC      BIT(15)
#define RX_LEN_MASK 0x7fff

    uint32_t opts2;
#define RD_UDP_CS  BIT(23)
#define RD_TCP_CS  BIT(22)
#define RD_IPV6_CS BIT(20)
#define RD_IPV4_CS BIT(19)

    uint32_t opts3;
#define IPF         BIT(23) /* IP checksum fail */
#define UDPF        BIT(22) /* UDP checksum fail */
#define TCPF        BIT(21) /* TCP checksum fail */
#define RX_VLAN_TAG BIT(16)

    uint32_t opts4;
    uint32_t opts5;
    uint32_t opts6;
};

struct tx_desc {
    uint32_t opts1;
#define TX_FS         BIT(31) /* First segment of a packet */
#define TX_LS         BIT(30) /* Final segment of a packet */
#define LGSEND        BIT(29)
#define GTSENDV4      BIT(28)
#define GTSENDV6      BIT(27)
#define GTTCPHO_SHIFT 18
#define GTTCPHO_MAX   0x7fU
#define TX_LEN_MAX    0x3ffffU

    uint32_t opts2;
#define UDP_CS      BIT(31) /* Calculate UDP/IP checksum */
#define TCP_CS      BIT(30) /* Calculate TCP/IP checksum */
#define IPV4_CS     BIT(29) /* Calculate IPv4 checksum */
#define IPV6_CS     BIT(28) /* Calculate IPv6 checksum */
#define MSS_SHIFT   17
#define MSS_MAX     0x7ffU
#define TCPHO_SHIFT 17
#define TCPHO_MAX   0x7ffU
#define TX_VLAN_TAG BIT(16)
};

enum rtl_version {
    RTL_VER_UNKNOWN = 0,
    RTL_VER_01,
    RTL_VER_02,
    RTL_VER_03,
    RTL_VER_04,
    RTL_VER_05,
    RTL_VER_06,
    RTL_VER_07,
    RTL_VER_08,
    RTL_VER_09,

    RTL_TEST_01,
    RTL_VER_10,
    RTL_VER_11,
    RTL_VER_12,
    RTL_VER_13,
    RTL_VER_14,
    RTL_VER_15,

    RTL_VER_MAX
};

/* mii.h */
/* Generic MII registers. */
#define MII_BMCR        0x00 /* Basic mode control register */
#define MII_BMSR        0x01 /* Basic mode status register  */
#define MII_PHYSID1     0x02 /* PHYS ID 1                   */
#define MII_PHYSID2     0x03 /* PHYS ID 2                   */
#define MII_ADVERTISE   0x04 /* Advertisement control reg   */
#define MII_LPA         0x05 /* Link partner ability reg    */
#define MII_EXPANSION   0x06 /* Expansion register          */
#define MII_CTRL1000    0x09 /* 1000BASE-T control          */
#define MII_STAT1000    0x0a /* 1000BASE-T status           */
#define MII_MMD_CTRL    0x0d /* MMD Access Control Register */
#define MII_MMD_DATA    0x0e /* MMD Access Data Register */
#define MII_ESTATUS     0x0f /* Extended Status             */
#define MII_DCOUNTER    0x12 /* Disconnect counter          */
#define MII_FCSCOUNTER  0x13 /* False carrier counter       */
#define MII_NWAYTEST    0x14 /* N-way auto-neg test reg     */
#define MII_RERRCOUNTER 0x15 /* Receive error counter       */
#define MII_SREVISION   0x16 /* Silicon revision            */
#define MII_RESV1       0x17 /* Reserved...                 */
#define MII_LBRERROR    0x18 /* Lpback, rx, bypass error    */
#define MII_PHYADDR     0x19 /* PHY address                 */
#define MII_RESV2       0x1a /* Reserved...                 */
#define MII_TPISTATUS   0x1b /* TPI status for 10mbps       */
#define MII_NCONFIG     0x1c /* Network interface config    */

/* Basic mode control register. */
#define BMCR_RESV      0x003f /* Unused...                   */
#define BMCR_SPEED1000 0x0040 /* MSB of Speed (1000)         */
#define BMCR_CTST      0x0080 /* Collision test              */
#define BMCR_FULLDPLX  0x0100 /* Full duplex                 */
#define BMCR_ANRESTART 0x0200 /* Auto negotiation restart    */
#define BMCR_ISOLATE   0x0400 /* Isolate data paths from MII */
#define BMCR_PDOWN     0x0800 /* Enable low power state      */
#define BMCR_ANENABLE  0x1000 /* Enable auto negotiation     */
#define BMCR_SPEED100  0x2000 /* Select 100Mbps              */
#define BMCR_LOOPBACK  0x4000 /* TXD loopback bits           */
#define BMCR_RESET     0x8000 /* Reset to default state      */
#define BMCR_SPEED10   0x0000 /* Select 10Mbps               */

/* Basic mode status register. */
#define BMSR_ERCAP        0x0001 /* Ext-reg capability          */
#define BMSR_JCD          0x0002 /* Jabber detected             */
#define BMSR_LSTATUS      0x0004 /* Link status                 */
#define BMSR_ANEGCAPABLE  0x0008 /* Able to do auto-negotiation */
#define BMSR_RFAULT       0x0010 /* Remote fault detected       */
#define BMSR_ANEGCOMPLETE 0x0020 /* Auto-negotiation complete   */
#define BMSR_RESV         0x00c0 /* Unused...                   */
#define BMSR_ESTATEN      0x0100 /* Extended Status in R15      */
#define BMSR_100HALF2     0x0200 /* Can do 100BASE-T2 HDX       */
#define BMSR_100FULL2     0x0400 /* Can do 100BASE-T2 FDX       */
#define BMSR_10HALF       0x0800 /* Can do 10mbps, half-duplex  */
#define BMSR_10FULL       0x1000 /* Can do 10mbps, full-duplex  */
#define BMSR_100HALF      0x2000 /* Can do 100mbps, half-duplex */
#define BMSR_100FULL      0x4000 /* Can do 100mbps, full-duplex */
#define BMSR_100BASE4     0x8000 /* Can do 100mbps, 4k packets  */

/* Advertisement control register. */
#define ADVERTISE_SLCT          0x001f /* Selector bits               */
#define ADVERTISE_CSMA          0x0001 /* Only selector supported     */
#define ADVERTISE_10HALF        0x0020 /* Try for 10mbps half-duplex  */
#define ADVERTISE_1000XFULL     0x0020 /* Try for 1000BASE-X full-duplex */
#define ADVERTISE_10FULL        0x0040 /* Try for 10mbps full-duplex  */
#define ADVERTISE_1000XHALF     0x0040 /* Try for 1000BASE-X half-duplex */
#define ADVERTISE_100HALF       0x0080 /* Try for 100mbps half-duplex */
#define ADVERTISE_1000XPAUSE    0x0080 /* Try for 1000BASE-X pause    */
#define ADVERTISE_100FULL       0x0100 /* Try for 100mbps full-duplex */
#define ADVERTISE_1000XPSE_ASYM 0x0100 /* Try for 1000BASE-X asym pause */
#define ADVERTISE_100BASE4      0x0200 /* Try for 100mbps 4k packets  */
#define ADVERTISE_PAUSE_CAP     0x0400 /* Try for pause               */
#define ADVERTISE_PAUSE_ASYM    0x0800 /* Try for asymetric pause     */
#define ADVERTISE_RESV          0x1000 /* Unused...                   */
#define ADVERTISE_RFAULT        0x2000 /* Say we can detect faults    */
#define ADVERTISE_LPACK         0x4000 /* Ack link partners response  */
#define ADVERTISE_NPAGE         0x8000 /* Next page bit               */

#define ADVERTISE_FULL (ADVERTISE_100FULL | ADVERTISE_10FULL | \
                        ADVERTISE_CSMA)
#define ADVERTISE_ALL (ADVERTISE_10HALF | ADVERTISE_10FULL | \
                       ADVERTISE_100HALF | ADVERTISE_100FULL)

/* 1000BASE-T Control register */
#define ADVERTISE_1000FULL    0x0200 /* Advertise 1000BASE-T full duplex */
#define ADVERTISE_1000HALF    0x0100 /* Advertise 1000BASE-T half duplex */
#define CTL1000_AS_MASTER     0x0800
#define CTL1000_ENABLE_MASTER 0x1000

/* ethtool.h */
/* The forced speed, 10Mb, 100Mb, gigabit. */
#define SPEED_10   10
#define SPEED_100  100
#define SPEED_1000 1000

#define SPEED_UNKNOWN -1

/* Duplex, half or full. */
#define DUPLEX_HALF    0x00
#define DUPLEX_FULL    0x01
#define DUPLEX_UNKNOWN 0xff

/* Enable or disable autonegotiation. */
#define AUTONEG_DISABLE 0x00
#define AUTONEG_ENABLE  0x01

static int usbh_rtl8152_read_regs(struct usbh_rtl8152 *rtl8152_class,
                                  uint16_t value,
                                  uint16_t index,
                                  uint16_t size,
                                  void *data)
{
    struct usb_setup_packet *setup;
    int ret;

    if (!rtl8152_class || !rtl8152_class->hport) {
        return -USB_ERR_INVAL;
    }
    setup = rtl8152_class->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_IN | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = RTL8152_REQ_GET_REGS;
    setup->wValue = value;
    setup->wIndex = index;
    setup->wLength = size;

    ret = usbh_control_transfer(rtl8152_class->hport, setup, g_rtl8152_buf);
    if (ret < 0) {
        return ret;
    }
    memcpy(data, g_rtl8152_buf, ret - 8);

    return ret;
}

static int usbh_rtl8152_write_regs(struct usbh_rtl8152 *rtl8152_class,
                                   uint16_t value,
                                   uint16_t index,
                                   uint16_t size,
                                   void *data)
{
    struct usb_setup_packet *setup;

    if (!rtl8152_class || !rtl8152_class->hport) {
        return -USB_ERR_INVAL;
    }
    setup = rtl8152_class->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = RTL8152_REQ_SET_REGS;
    setup->wValue = value;
    setup->wIndex = index;
    setup->wLength = size;

    memcpy(g_rtl8152_buf, data, size);
    return usbh_control_transfer(rtl8152_class->hport, setup, g_rtl8152_buf);
}

static int generic_ocp_read(struct usbh_rtl8152 *tp, uint16_t index, uint16_t size,
                            void *data, uint16_t type)
{
    uint16_t limit = 64;
    int ret = 0;

    /* both size and indix must be 4 bytes align */
    if ((size & 3) || !size || (index & 3) || !data)
        return -USB_ERR_INVAL;

    if ((uint32_t)index + (uint32_t)size > 0xffff)
        return -USB_ERR_INVAL;

    while (size) {
        if (size > limit) {
            ret = usbh_rtl8152_read_regs(tp, index, type, limit, data);
            if (ret < 0)
                break;

            index += limit;
            data += limit;
            size -= limit;
        } else {
            ret = usbh_rtl8152_read_regs(tp, index, type, size, data);
            if (ret < 0)
                break;

            index += size;
            data += size;
            size = 0;
            break;
        }
    }

    return ret;
}

static int generic_ocp_write(struct usbh_rtl8152 *tp, uint16_t index, uint16_t byteen,
                             uint16_t size, void *data, uint16_t type)
{
    int ret;
    uint16_t byteen_start, byteen_end, byen;
    uint16_t limit = 512;

    /* both size and indix must be 4 bytes align */
    if ((size & 3) || !size || (index & 3) || !data)
        return -USB_ERR_INVAL;

    if ((uint32_t)index + (uint32_t)size > 0xffff)
        return -USB_ERR_INVAL;

    byteen_start = byteen & BYTE_EN_START_MASK;
    byteen_end = byteen & BYTE_EN_END_MASK;

    byen = byteen_start | (byteen_start << 4);

    /* Split the first DWORD if the byte_en is not 0xff */
    if (byen != BYTE_EN_DWORD) {
        ret = usbh_rtl8152_write_regs(tp, index, type | byen, 4, data);
        if (ret < 0)
            goto error1;

        index += 4;
        data += 4;
        size -= 4;
    }

    if (size) {
        byen = byteen_end | (byteen_end >> 4);

        /* Split the last DWORD if the byte_en is not 0xff */
        if (byen != BYTE_EN_DWORD)
            size -= 4;

        while (size) {
            if (size > limit) {
                ret = usbh_rtl8152_write_regs(tp, index,
                                              type | BYTE_EN_DWORD,
                                              limit, data);
                if (ret < 0)
                    goto error1;

                index += limit;
                data += limit;
                size -= limit;
            } else {
                ret = usbh_rtl8152_write_regs(tp, index,
                                              type | BYTE_EN_DWORD,
                                              size, data);
                if (ret < 0)
                    goto error1;

                index += size;
                data += size;
                size = 0;
                break;
            }
        }

        /* Set the last DWORD */
        if (byen != BYTE_EN_DWORD)
            ret = usbh_rtl8152_write_regs(tp, index, type | byen, 4, data);
    }

error1:

    return ret;
}

static inline int pla_ocp_read(struct usbh_rtl8152 *tp, uint16_t index, uint16_t size, void *data)
{
    return generic_ocp_read(tp, index, size, data, MCU_TYPE_PLA);
}

static inline int pla_ocp_write(struct usbh_rtl8152 *tp, uint16_t index, uint16_t byteen, uint16_t size, void *data)
{
    return generic_ocp_write(tp, index, byteen, size, data, MCU_TYPE_PLA);
}

static inline int usb_ocp_write(struct usbh_rtl8152 *tp, uint16_t index, uint16_t byteen, uint16_t size, void *data)
{
    return generic_ocp_write(tp, index, byteen, size, data, MCU_TYPE_USB);
}

static uint32_t ocp_read_dword(struct usbh_rtl8152 *tp, uint16_t type, uint16_t index)
{
    uint32_t data;

    generic_ocp_read(tp, index, sizeof(data), &data, type);

    return data;
}

static void ocp_write_dword(struct usbh_rtl8152 *tp, uint16_t type, uint16_t index, uint32_t data)
{
    uint32_t tmp = data;

    generic_ocp_write(tp, index, BYTE_EN_DWORD, sizeof(tmp), &tmp, type);
}

static uint16_t ocp_read_word(struct usbh_rtl8152 *tp, uint16_t type, uint16_t index)
{
    uint32_t data;
    uint32_t tmp;
    uint16_t byen = BYTE_EN_WORD;
    uint8_t shift = index & 2;

    index &= ~3;
    byen <<= shift;

    generic_ocp_read(tp, index, sizeof(tmp), &tmp, type | byen);

    data = tmp;
    data >>= (shift * 8);
    data &= 0xffff;

    return (uint16_t)data;
}

static void ocp_write_word(struct usbh_rtl8152 *tp, uint16_t type, uint16_t index, uint32_t data)
{
    uint32_t mask = 0xffff;
    uint32_t tmp;
    uint16_t byen = BYTE_EN_WORD;
    uint8_t shift = index & 2;

    data &= mask;

    if (index & 2) {
        byen <<= shift;
        mask <<= (shift * 8);
        data <<= (shift * 8);
        index &= ~3;
    }

    tmp = data;

    generic_ocp_write(tp, index, byen, sizeof(tmp), &tmp, type);
}

static uint8_t ocp_read_byte(struct usbh_rtl8152 *tp, uint16_t type, uint16_t index)
{
    uint32_t data;
    uint32_t tmp;
    uint8_t shift = index & 3;

    index &= ~3;

    generic_ocp_read(tp, index, sizeof(tmp), &tmp, type);

    data = tmp;
    data >>= (shift * 8);
    data &= 0xff;

    return (uint8_t)data;
}

static void ocp_write_byte(struct usbh_rtl8152 *tp, uint16_t type, uint16_t index, uint32_t data)
{
    uint32_t mask = 0xff;
    uint32_t tmp;
    uint16_t byen = BYTE_EN_BYTE;
    uint8_t shift = index & 3;

    data &= mask;

    if (index & 3) {
        byen <<= shift;
        mask <<= (shift * 8);
        data <<= (shift * 8);
        index &= ~3;
    }

    tmp = data;

    generic_ocp_write(tp, index, byen, sizeof(tmp), &tmp, type);
}

static uint16_t ocp_reg_read(struct usbh_rtl8152 *tp, uint16_t addr)
{
    uint16_t ocp_base, ocp_index;

    ocp_base = addr & 0xf000;
    if (ocp_base != tp->ocp_base) {
        ocp_write_word(tp, MCU_TYPE_PLA, PLA_OCP_GPHY_BASE, ocp_base);
        tp->ocp_base = ocp_base;
    }

    ocp_index = (addr & 0x0fff) | 0xb000;
    return ocp_read_word(tp, MCU_TYPE_PLA, ocp_index);
}

static void ocp_reg_write(struct usbh_rtl8152 *tp, uint16_t addr, uint16_t data)
{
    uint16_t ocp_base, ocp_index;

    ocp_base = addr & 0xf000;
    if (ocp_base != tp->ocp_base) {
        ocp_write_word(tp, MCU_TYPE_PLA, PLA_OCP_GPHY_BASE, ocp_base);
        tp->ocp_base = ocp_base;
    }

    ocp_index = (addr & 0x0fff) | 0xb000;
    ocp_write_word(tp, MCU_TYPE_PLA, ocp_index, data);
}

static inline void r8152_mdio_write(struct usbh_rtl8152 *tp, uint32_t reg_addr, uint32_t value)
{
    ocp_reg_write(tp, OCP_BASE_MII + reg_addr * 2, value);
}

static inline int r8152_mdio_read(struct usbh_rtl8152 *tp, uint32_t reg_addr)
{
    return ocp_reg_read(tp, OCP_BASE_MII + reg_addr * 2);
}

static uint8_t usbh_rtl8152_get_version(struct usbh_rtl8152 *rtl8152_class)
{
    uint8_t version;
    uint32_t temp;
    uint32_t ocp_data;

    usbh_rtl8152_read_regs(rtl8152_class, PLA_TCR0, MCU_TYPE_PLA, 4, &temp);

    ocp_data = (temp >> 16) & VERSION_MASK;
    switch (ocp_data) {
        case 0x4c00:
            version = RTL_VER_01;
            break;
        case 0x4c10:
            version = RTL_VER_02;
            break;
        case 0x5c00:
            version = RTL_VER_03;
            break;
        case 0x5c10:
            version = RTL_VER_04;
            break;
        case 0x5c20:
            version = RTL_VER_05;
            break;
        case 0x5c30:
            version = RTL_VER_06;
            break;
        case 0x4800:
            version = RTL_VER_07;
            break;
        case 0x6000:
            version = RTL_VER_08;
            break;
        case 0x6010:
            version = RTL_VER_09;
            break;
        case 0x7010:
            version = RTL_TEST_01;
            break;
        case 0x7020:
            version = RTL_VER_10;
            break;
        case 0x7030:
            version = RTL_VER_11;
            break;
        case 0x7400:
            version = RTL_VER_12;
            break;
        case 0x7410:
            version = RTL_VER_13;
            break;
        case 0x6400:
            version = RTL_VER_14;
            break;
        case 0x7420:
            version = RTL_VER_15;
            break;
        default:
            version = RTL_VER_UNKNOWN;
            break;
    }

    return version;
}

#define WAKE_PHY         (1 << 0)
#define WAKE_UCAST       (1 << 1)
#define WAKE_MCAST       (1 << 2)
#define WAKE_BCAST       (1 << 3)
#define WAKE_ARP         (1 << 4)
#define WAKE_MAGIC       (1 << 5)
#define WAKE_MAGICSECURE (1 << 6) /* only meaningful if WAKE_MAGIC */
#define WAKE_FILTER      (1 << 7)

#define WAKE_ANY (WAKE_PHY | WAKE_MAGIC | WAKE_UCAST | WAKE_BCAST | WAKE_MCAST)

static uint32_t __rtl_get_wol(struct usbh_rtl8152 *tp)
{
    uint32_t ocp_data;
    uint32_t wolopts = 0;

    ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_CONFIG34);
    if (ocp_data & LINK_ON_WAKE_EN)
        wolopts |= WAKE_PHY;

    ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_CONFIG5);
    if (ocp_data & UWF_EN)
        wolopts |= WAKE_UCAST;
    if (ocp_data & BWF_EN)
        wolopts |= WAKE_BCAST;
    if (ocp_data & MWF_EN)
        wolopts |= WAKE_MCAST;

    ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_CFG_WOL);
    if (ocp_data & MAGIC_EN)
        wolopts |= WAKE_MAGIC;

    return wolopts;
}

static void r8152_aldps_en(struct usbh_rtl8152 *tp, bool enable)
{
    if (enable) {
        ocp_reg_write(tp, OCP_ALDPS_CONFIG, ENPWRSAVE | ENPDNPS | LINKENA | DIS_SDSAVE);
    } else {
        ocp_reg_write(tp, OCP_ALDPS_CONFIG, ENPDNPS | LINKENA | DIS_SDSAVE);
        usb_osal_msleep(20);
    }
}

static void r8152_power_cut_en(struct usbh_rtl8152 *tp, bool enable)
{
    uint32_t ocp_data;

    ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_UPS_CTRL);
    if (enable)
        ocp_data |= POWER_CUT;
    else
        ocp_data &= ~POWER_CUT;
    ocp_write_word(tp, MCU_TYPE_USB, USB_UPS_CTRL, ocp_data);

    ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_PM_CTRL_STATUS);
    ocp_data &= ~RESUME_INDICATE;
    ocp_write_word(tp, MCU_TYPE_USB, USB_PM_CTRL_STATUS, ocp_data);
}

static void rtl_tally_reset(struct usbh_rtl8152 *tp)
{
    uint32_t ocp_data;

    ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_RSTTALLY);
    ocp_data |= TALLY_RESET;
    ocp_write_word(tp, MCU_TYPE_PLA, PLA_RSTTALLY, ocp_data);
}

static void r8152b_reset_packet_filter(struct usbh_rtl8152 *tp)
{
    uint32_t ocp_data;

    ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_FMC);
    ocp_data &= ~FMC_FCR_MCU_EN;
    ocp_write_word(tp, MCU_TYPE_PLA, PLA_FMC, ocp_data);
    ocp_data |= FMC_FCR_MCU_EN;
    ocp_write_word(tp, MCU_TYPE_PLA, PLA_FMC, ocp_data);
}

static inline void r8153b_rx_agg_chg_indicate(struct usbh_rtl8152 *tp)
{
    ocp_write_byte(tp, MCU_TYPE_USB, USB_UPT_RXDMA_OWN,
                   OWN_UPDATE | OWN_CLEAR);
}

static void rxdy_gated_en(struct usbh_rtl8152 *tp, bool enable)
{
    uint32_t ocp_data;

    ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_MISC_1);
    if (enable)
        ocp_data |= RXDY_GATED_EN;
    else
        ocp_data &= ~RXDY_GATED_EN;
    ocp_write_word(tp, MCU_TYPE_PLA, PLA_MISC_1, ocp_data);
}

static inline uint16_t rtl8152_get_speed(struct usbh_rtl8152 *tp)
{
    return ocp_read_word(tp, MCU_TYPE_PLA, PLA_PHYSTATUS);
}

static void rtl_eee_plus_en(struct usbh_rtl8152 *tp, bool enable)
{
    uint32_t ocp_data;

    ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_EEEP_CR);
    if (enable)
        ocp_data |= EEEP_CR_EEEP_TX;
    else
        ocp_data &= ~EEEP_CR_EEEP_TX;
    ocp_write_word(tp, MCU_TYPE_PLA, PLA_EEEP_CR, ocp_data);
}

static void rtl_set_eee_plus(struct usbh_rtl8152 *tp)
{
    if (rtl8152_get_speed(tp) & _10bps)
        rtl_eee_plus_en(tp, true);
    else
        rtl_eee_plus_en(tp, false);
}

static void rtl8152_nic_reset(struct usbh_rtl8152 *tp)
{
    uint32_t ocp_data;
    int i;

    switch (tp->version) {
        case RTL_TEST_01:
        case RTL_VER_10:
        case RTL_VER_11:
            ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_CR);
            ocp_data &= ~CR_TE;
            ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CR, ocp_data);

            ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_BMU_RESET);
            ocp_data &= ~BMU_RESET_EP_IN;
            ocp_write_word(tp, MCU_TYPE_USB, USB_BMU_RESET, ocp_data);

            ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_USB_CTRL);
            ocp_data |= CDC_ECM_EN;
            ocp_write_word(tp, MCU_TYPE_USB, USB_USB_CTRL, ocp_data);

            ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_CR);
            ocp_data &= ~CR_RE;
            ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CR, ocp_data);

            ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_BMU_RESET);
            ocp_data |= BMU_RESET_EP_IN;
            ocp_write_word(tp, MCU_TYPE_USB, USB_BMU_RESET, ocp_data);

            ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_USB_CTRL);
            ocp_data &= ~CDC_ECM_EN;
            ocp_write_word(tp, MCU_TYPE_USB, USB_USB_CTRL, ocp_data);
            break;

        default:
            ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CR, CR_RST);

            for (i = 0; i < 1000; i++) {
                if (!(ocp_read_byte(tp, MCU_TYPE_PLA, PLA_CR) & CR_RST))
                    break;
                usb_osal_msleep(400);
            }
            break;
    }
}

static void rtl_disable(struct usbh_rtl8152 *tp)
{
    uint32_t ocp_data;
    int i;

    ocp_data = ocp_read_dword(tp, MCU_TYPE_PLA, PLA_RCR);
    ocp_data &= ~RCR_ACPT_ALL;
    ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RCR, ocp_data);

    rxdy_gated_en(tp, true);

    for (i = 0; i < 1000; i++) {
        ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
        if ((ocp_data & FIFO_EMPTY) == FIFO_EMPTY)
            break;
        usb_osal_msleep(1);
    }

    for (i = 0; i < 1000; i++) {
        if (ocp_read_word(tp, MCU_TYPE_PLA, PLA_TCR0) & TCR0_TX_EMPTY)
            break;
        usb_osal_msleep(1);
    }

    rtl8152_nic_reset(tp);
}

static void rtl_rx_vlan_en(struct usbh_rtl8152 *tp, bool enable)
{
    uint32_t ocp_data;

    switch (tp->version) {
        case RTL_VER_01:
        case RTL_VER_02:
        case RTL_VER_03:
        case RTL_VER_04:
        case RTL_VER_05:
        case RTL_VER_06:
        case RTL_VER_07:
        case RTL_VER_08:
        case RTL_VER_09:
        case RTL_VER_14:
            ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_CPCR);
            if (enable)
                ocp_data |= CPCR_RX_VLAN;
            else
                ocp_data &= ~CPCR_RX_VLAN;
            ocp_write_word(tp, MCU_TYPE_PLA, PLA_CPCR, ocp_data);
            break;

        case RTL_TEST_01:
        case RTL_VER_10:
        case RTL_VER_11:
        case RTL_VER_12:
        case RTL_VER_13:
        case RTL_VER_15:
        default:
            ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_RCR1);
            if (enable)
                ocp_data |= OUTER_VLAN | INNER_VLAN;
            else
                ocp_data &= ~(OUTER_VLAN | INNER_VLAN);
            ocp_write_word(tp, MCU_TYPE_PLA, PLA_RCR1, ocp_data);
            break;
    }
}

static void wait_oob_link_list_ready(struct usbh_rtl8152 *tp)
{
    uint32_t ocp_data;
    int i;

    for (i = 0; i < 1000; i++) {
        ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
        if (ocp_data & LINK_LIST_READY)
            break;
        usb_osal_msleep(1);
    }
}

static void r8153_teredo_off(struct usbh_rtl8152 *tp)
{
    uint32_t ocp_data;

    switch (tp->version) {
        case RTL_VER_01:
        case RTL_VER_02:
        case RTL_VER_03:
        case RTL_VER_04:
        case RTL_VER_05:
        case RTL_VER_06:
        case RTL_VER_07:
            ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_TEREDO_CFG);
            ocp_data &= ~(TEREDO_SEL | TEREDO_RS_EVENT_MASK |
                          OOB_TEREDO_EN);
            ocp_write_word(tp, MCU_TYPE_PLA, PLA_TEREDO_CFG, ocp_data);
            break;

        case RTL_VER_08:
        case RTL_VER_09:
        case RTL_TEST_01:
        case RTL_VER_10:
        case RTL_VER_11:
        case RTL_VER_12:
        case RTL_VER_13:
        case RTL_VER_14:
        case RTL_VER_15:
        default:
            /* The bit 0 ~ 7 are relative with teredo settings. They are
		 * W1C (write 1 to clear), so set all 1 to disable it.
		 */
            ocp_write_byte(tp, MCU_TYPE_PLA, PLA_TEREDO_CFG, 0xff);
            break;
    }

    ocp_write_word(tp, MCU_TYPE_PLA, PLA_WDT6_CTRL, WDT6_SET_MODE);
    ocp_write_word(tp, MCU_TYPE_PLA, PLA_REALWOW_TIMER, 0);
    ocp_write_dword(tp, MCU_TYPE_PLA, PLA_TEREDO_TIMER, 0);
}

static void r8152b_exit_oob(struct usbh_rtl8152 *tp)
{
    uint32_t ocp_data;

    ocp_data = ocp_read_dword(tp, MCU_TYPE_PLA, PLA_RCR);
    ocp_data &= ~RCR_ACPT_ALL;
    ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RCR, ocp_data);

    rxdy_gated_en(tp, true);
    r8153_teredo_off(tp);
    ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_NORAML);
    ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CR, 0x00);

    ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
    ocp_data &= ~NOW_IS_OOB;
    ocp_write_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL, ocp_data);

    ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7);
    ocp_data &= ~MCU_BORW_EN;
    ocp_write_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7, ocp_data);

    wait_oob_link_list_ready(tp);

    ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7);
    ocp_data |= RE_INIT_LL;
    ocp_write_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7, ocp_data);

    wait_oob_link_list_ready(tp);

    rtl8152_nic_reset(tp);

    /* rx share fifo credit full threshold */
    ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL0, RXFIFO_THR1_NORMAL);

    if (tp->hport->speed == USB_SPEED_FULL ||
        tp->hport->speed == USB_SPEED_LOW) {
        /* rx share fifo credit near full threshold */
        ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL1,
                        RXFIFO_THR2_FULL);
        ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL2,
                        RXFIFO_THR3_FULL);
    } else {
        /* rx share fifo credit near full threshold */
        ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL1,
                        RXFIFO_THR2_HIGH);
        ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL2,
                        RXFIFO_THR3_HIGH);
    }

    /* TX share fifo free credit full threshold */
    ocp_write_dword(tp, MCU_TYPE_PLA, PLA_TXFIFO_CTRL, TXFIFO_THR_NORMAL2);

    ocp_write_byte(tp, MCU_TYPE_USB, USB_TX_AGG, TX_AGG_MAX_THRESHOLD);
    ocp_write_dword(tp, MCU_TYPE_USB, USB_RX_BUF_TH, RX_THR_HIGH);
    ocp_write_dword(tp, MCU_TYPE_USB, USB_TX_DMA,
                    TEST_MODE_DISABLE | TX_SIZE_ADJUST1);

    rtl_rx_vlan_en(tp, true);

    ocp_write_word(tp, MCU_TYPE_PLA, PLA_RMS, RTL8152_RMS);

    ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_TCR0);
    ocp_data |= TCR0_AUTO_FIFO;
    ocp_write_word(tp, MCU_TYPE_PLA, PLA_TCR0, ocp_data);
}

static void r8152b_enter_oob(struct usbh_rtl8152 *tp)
{
    uint32_t ocp_data;

    ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
    ocp_data &= ~NOW_IS_OOB;
    ocp_write_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL, ocp_data);

    ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL0, RXFIFO_THR1_OOB);
    ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL1, RXFIFO_THR2_OOB);
    ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL2, RXFIFO_THR3_OOB);

    rtl_disable(tp);

    wait_oob_link_list_ready(tp);

    ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7);
    ocp_data |= RE_INIT_LL;
    ocp_write_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7, ocp_data);

    wait_oob_link_list_ready(tp);

    ocp_write_word(tp, MCU_TYPE_PLA, PLA_RMS, RTL8152_RMS);

    rtl_rx_vlan_en(tp, true);

    ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_BDC_CR);
    ocp_data |= ALDPS_PROXY_MODE;
    ocp_write_word(tp, MCU_TYPE_PLA, PLA_BDC_CR, ocp_data);

    ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
    ocp_data |= NOW_IS_OOB | DIS_MCU_CLROOB;
    ocp_write_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL, ocp_data);

    rxdy_gated_en(tp, false);

    ocp_data = ocp_read_dword(tp, MCU_TYPE_PLA, PLA_RCR);
    ocp_data |= RCR_APM | RCR_AM | RCR_AB;
    ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RCR, ocp_data);
}

static void r8152b_init(struct usbh_rtl8152 *tp)
{
    uint32_t ocp_data;
    uint16_t data;

    data = r8152_mdio_read(tp, MII_BMCR);
    if (data & BMCR_PDOWN) {
        data &= ~BMCR_PDOWN;
        r8152_mdio_write(tp, MII_BMCR, data);
    }

    r8152_aldps_en(tp, false);

    if (tp->version == RTL_VER_01) {
        ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_LED_FEATURE);
        ocp_data &= ~LED_MODE_MASK;
        ocp_write_word(tp, MCU_TYPE_PLA, PLA_LED_FEATURE, ocp_data);
    }

    r8152_power_cut_en(tp, false);

    ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_PHY_PWR);
    ocp_data |= TX_10M_IDLE_EN | PFM_PWM_SWITCH;
    ocp_write_word(tp, MCU_TYPE_PLA, PLA_PHY_PWR, ocp_data);
    ocp_data = ocp_read_dword(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL);
    ocp_data &= ~MCU_CLK_RATIO_MASK;
    ocp_data |= MCU_CLK_RATIO | D3_CLK_GATED_EN;
    ocp_write_dword(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL, ocp_data);
    ocp_data = GPHY_STS_MSK | SPEED_DOWN_MSK |
               SPDWN_RXDV_MSK | SPDWN_LINKCHG_MSK;
    ocp_write_word(tp, MCU_TYPE_PLA, PLA_GPHY_INTR_IMR, ocp_data);

    rtl_tally_reset(tp);

    /* enable rx aggregation */
    ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_USB_CTRL);
    ocp_data &= ~(RX_AGG_DISABLE | RX_ZERO_EN);
    ocp_write_word(tp, MCU_TYPE_USB, USB_USB_CTRL, ocp_data);
}

static int rtl_enable(struct usbh_rtl8152 *tp)
{
    uint32_t ocp_data;

    r8152b_reset_packet_filter(tp);

    ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_CR);
    ocp_data |= CR_RE | CR_TE;
    ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CR, ocp_data);

    switch (tp->version) {
        case RTL_VER_01:
        case RTL_VER_02:
        case RTL_VER_03:
        case RTL_VER_04:
        case RTL_VER_05:
        case RTL_VER_06:
        case RTL_VER_07:
            break;
        default:
            r8153b_rx_agg_chg_indicate(tp);
            break;
    }

    rxdy_gated_en(tp, false);

    return 0;
}

static int rtl8152_enable(struct usbh_rtl8152 *tp)
{
    rtl_set_eee_plus(tp);

    return rtl_enable(tp);
}

static void rtl8152_disable(struct usbh_rtl8152 *tp)
{
    r8152_aldps_en(tp, false);
    rtl_disable(tp);
    r8152_aldps_en(tp, true);
}

static void rtl8152_up(struct usbh_rtl8152 *tp)
{
    r8152_aldps_en(tp, false);
    r8152b_exit_oob(tp);
    r8152_aldps_en(tp, true);
}

static void rtl8152_down(struct usbh_rtl8152 *tp)
{
    r8152_power_cut_en(tp, false);
    r8152_aldps_en(tp, false);
    r8152b_enter_oob(tp);
    r8152_aldps_en(tp, true);
}

static int rtl_ops_init(struct usbh_rtl8152 *tp)
{
    struct rtl_ops *ops = &tp->rtl_ops;
    int ret = 0;

    switch (tp->version) {
        case RTL_VER_01:
        case RTL_VER_02:
        case RTL_VER_07:
            ops->init = r8152b_init;
            ops->enable = rtl8152_enable;
            ops->disable = rtl8152_disable;
            ops->up = rtl8152_up;
            ops->down = rtl8152_down;
            // ops->unload = rtl8152_unload;
            // ops->eee_get		= r8152_get_eee;
            // ops->eee_set		= r8152_set_eee;
            // ops->in_nway = rtl8152_in_nway;
            // ops->hw_phy_cfg = r8152b_hw_phy_cfg;
            // ops->autosuspend_en = rtl_runtime_suspend_enable;
            tp->rx_buf_sz = 16 * 1024;
            tp->eee_en = true;
            //tp->eee_adv		= MDIO_EEE_100TX;
            break;

            // case RTL_VER_03:
            // case RTL_VER_04:
            // case RTL_VER_05:
            // case RTL_VER_06:
            //     break;

            // case RTL_VER_08:
            // case RTL_VER_09:
            //     break;

            // case RTL_VER_11:
            // case RTL_VER_10:
            //     break;

            // case RTL_VER_12:
            // case RTL_VER_13:
            // case RTL_VER_15:
            //     break;

            // case RTL_VER_14:
            //     break;

        default:
            ret = -USB_ERR_NODEV;
            USB_LOG_ERR("Unsupport rtl version:%d\r\n", tp->version);
            break;
    }

    return ret;
}

static void rtl8152_set_rx_mode(struct usbh_rtl8152 *tp)
{
    uint32_t ocp_data;
    uint32_t mc_filter[2];

    ocp_data = ocp_read_dword(tp, MCU_TYPE_PLA, PLA_RCR);
    ocp_data &= ~RCR_ACPT_ALL;
    ocp_data |= RCR_AB | RCR_APM;

    ocp_data |= RCR_AM;
    mc_filter[1] = 0xffffffff;
    mc_filter[0] = 0xffffffff;

    pla_ocp_write(tp, PLA_MAR, BYTE_EN_DWORD, sizeof(mc_filter), mc_filter);
    ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RCR, ocp_data);
}

static int rtl8152_set_speed(struct usbh_rtl8152 *tp, uint8_t autoneg, uint16_t speed, uint8_t duplex)
{
    uint16_t bmcr, anar, gbcr;

    anar = r8152_mdio_read(tp, MII_ADVERTISE);
    anar &= ~(ADVERTISE_10HALF | ADVERTISE_10FULL |
              ADVERTISE_100HALF | ADVERTISE_100FULL);
    if (tp->supports_gmii) {
        gbcr = r8152_mdio_read(tp, MII_CTRL1000);
        gbcr &= ~(ADVERTISE_1000FULL | ADVERTISE_1000HALF);
    } else {
        gbcr = 0;
    }

    if (autoneg == AUTONEG_DISABLE) {
        if (speed == SPEED_10) {
            bmcr = 0;
            anar |= ADVERTISE_10HALF | ADVERTISE_10FULL;
        } else if (speed == SPEED_100) {
            bmcr = BMCR_SPEED100;
            anar |= ADVERTISE_100HALF | ADVERTISE_100FULL;
        } else if (speed == SPEED_1000 && tp->supports_gmii) {
            bmcr = BMCR_SPEED1000;
            gbcr |= ADVERTISE_1000FULL | ADVERTISE_1000HALF;
        } else {
            return -USB_ERR_INVAL;
        }

        if (duplex == DUPLEX_FULL)
            bmcr |= BMCR_FULLDPLX;
    } else {
        if (speed == SPEED_10) {
            if (duplex == DUPLEX_FULL)
                anar |= ADVERTISE_10HALF | ADVERTISE_10FULL;
            else
                anar |= ADVERTISE_10HALF;
        } else if (speed == SPEED_100) {
            if (duplex == DUPLEX_FULL) {
                anar |= ADVERTISE_10HALF | ADVERTISE_10FULL;
                anar |= ADVERTISE_100HALF | ADVERTISE_100FULL;
            } else {
                anar |= ADVERTISE_10HALF;
                anar |= ADVERTISE_100HALF;
            }
        } else if (speed == SPEED_1000 && tp->supports_gmii) {
            if (duplex == DUPLEX_FULL) {
                anar |= ADVERTISE_10HALF | ADVERTISE_10FULL;
                anar |= ADVERTISE_100HALF | ADVERTISE_100FULL;
                gbcr |= ADVERTISE_1000FULL | ADVERTISE_1000HALF;
            } else {
                anar |= ADVERTISE_10HALF;
                anar |= ADVERTISE_100HALF;
                gbcr |= ADVERTISE_1000HALF;
            }
        } else {
            return -USB_ERR_INVAL;
        }

        bmcr = BMCR_ANENABLE | BMCR_ANRESTART | BMCR_RESET;
    }

    if (tp->supports_gmii)
        r8152_mdio_write(tp, MII_CTRL1000, gbcr);

    r8152_mdio_write(tp, MII_ADVERTISE, anar);
    r8152_mdio_write(tp, MII_BMCR, bmcr);

    return 0;
}

int r8152_write_hwaddr(struct usbh_rtl8152 *tp, unsigned char *mac)
{
    unsigned char enetaddr[8] = { 0 };
    memcpy(enetaddr, mac, 6);
    ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_CONFIG);
    pla_ocp_write(tp, PLA_IDR, BYTE_EN_SIX_BYTES, 8, enetaddr);
    ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_NORAML);
    return 0;
}

int usbh_rtl8152_get_connect_status(struct usbh_rtl8152 *rtl8152_class)
{
    int ret;

    usbh_int_urb_fill(&rtl8152_class->intin_urb, rtl8152_class->hport, rtl8152_class->intin, g_rtl8152_inttx_buffer, 2, USB_OSAL_WAITING_FOREVER, NULL, NULL);
    ret = usbh_submit_urb(&rtl8152_class->intin_urb);
    if (ret < 0) {
        return ret;
    }

    if (g_rtl8152_inttx_buffer[0] & INTR_LINK) {
        rtl8152_class->connect_status = true;
    } else {
        rtl8152_class->connect_status = false;
    }
    return 0;
}

static int usbh_rtl8152_connect(struct usbh_hubport *hport, uint8_t intf)
{
    struct usb_endpoint_descriptor *ep_desc;
    char mac_buffer[12];
    int ret;

    struct usbh_rtl8152 *rtl8152_class = &g_rtl8152_class;

    memset(rtl8152_class, 0, sizeof(struct usbh_rtl8152));

    rtl8152_class->hport = hport;
    rtl8152_class->intf = intf;

    hport->config.intf[intf].priv = rtl8152_class;

    rtl8152_class->version = usbh_rtl8152_get_version(rtl8152_class);

    if (rtl8152_class->version == RTL_VER_UNKNOWN) {
        USB_LOG_ERR("Unknown version 0x%04x\r\n", rtl8152_class->version);
        return -USB_ERR_NOTSUPP;
    } else {
        USB_LOG_INFO("rtl8152 version 0x%04x\r\n", rtl8152_class->version);
    }

    /* MTU range: 68 - 1500 or 9194 */
    rtl8152_class->min_mtu = 68;
    switch (rtl8152_class->version) {
        case RTL_VER_03:
        case RTL_VER_04:
        case RTL_VER_05:
        case RTL_VER_06:
        case RTL_VER_08:
        case RTL_VER_09:
        case RTL_VER_14:
            rtl8152_class->max_mtu = size_to_mtu(9 * 1024);
            break;
        case RTL_VER_10:
        case RTL_VER_11:
            rtl8152_class->max_mtu = size_to_mtu(15 * 1024);
            break;
        case RTL_VER_12:
        case RTL_VER_13:
        case RTL_VER_15:
            rtl8152_class->max_mtu = size_to_mtu(16 * 1024);
            break;
        case RTL_VER_01:
        case RTL_VER_02:
        case RTL_VER_07:
        default:
            rtl8152_class->max_mtu = 1500;
            break;
    }

    rtl8152_class->saved_wolopts = __rtl_get_wol(rtl8152_class);
    if (rtl_ops_init(rtl8152_class) < 0) {
        return -USB_ERR_NODEV;
    }

    rtl8152_class->rtl_ops.init(rtl8152_class);
    rtl8152_class->rtl_ops.up(rtl8152_class);

    if (rtl8152_class->rx_buf_sz > CONFIG_USBHOST_RTL8152_ETH_MAX_RX_SIZE) {
        USB_LOG_ERR("rx_buf_sz is overflow, default is %d\r\n", CONFIG_USBHOST_RTL8152_ETH_MAX_RX_SIZE);
        return -USB_ERR_NOMEM;
    }

    memset(mac_buffer, 0, 12);
    ret = usbh_get_string_desc(rtl8152_class->hport, 3, (uint8_t *)mac_buffer);
    if (ret < 0) {
        return ret;
    }

    for (int i = 0, j = 0; i < 12; i += 2, j++) {
        char byte_str[3];
        byte_str[0] = mac_buffer[i];
        byte_str[1] = mac_buffer[i + 1];
        byte_str[2] = '\0';

        uint32_t byte = strtoul(byte_str, NULL, 16);
        rtl8152_class->mac[j] = (unsigned char)byte;
    }

    r8152_write_hwaddr(rtl8152_class, rtl8152_class->mac);

    USB_LOG_INFO("RTL8152 MAC address %02x:%02x:%02x:%02x:%02x:%02x\r\n",
                 rtl8152_class->mac[0],
                 rtl8152_class->mac[1],
                 rtl8152_class->mac[2],
                 rtl8152_class->mac[3],
                 rtl8152_class->mac[4],
                 rtl8152_class->mac[5]);

    for (uint8_t i = 0; i < hport->config.intf[intf].altsetting[0].intf_desc.bNumEndpoints; i++) {
        ep_desc = &hport->config.intf[intf].altsetting[0].ep[i].ep_desc;

        if (USB_GET_ENDPOINT_TYPE(ep_desc->bmAttributes) == USB_ENDPOINT_TYPE_INTERRUPT) {
            if (ep_desc->bEndpointAddress & 0x80) {
                USBH_EP_INIT(rtl8152_class->intin, ep_desc);
            } else {
                return -USB_ERR_NOTSUPP;
            }
        } else {
            if (ep_desc->bEndpointAddress & 0x80) {
                USBH_EP_INIT(rtl8152_class->bulkin, ep_desc);
            } else {
                USBH_EP_INIT(rtl8152_class->bulkout, ep_desc);
            }
        }
    }

    strncpy(hport->config.intf[intf].devname, DEV_FORMAT, CONFIG_USBHOST_DEV_NAMELEN);

    USB_LOG_INFO("Register RTL8152 Class:%s\r\n", hport->config.intf[intf].devname);

    usbh_rtl8152_run(rtl8152_class);
    return 0;
}

static int usbh_rtl8152_disconnect(struct usbh_hubport *hport, uint8_t intf)
{
    int ret = 0;

    struct usbh_rtl8152 *rtl8152_class = (struct usbh_rtl8152 *)hport->config.intf[intf].priv;

    if (rtl8152_class) {
        if (rtl8152_class->bulkin) {
            usbh_kill_urb(&rtl8152_class->bulkin_urb);
        }

        if (rtl8152_class->bulkout) {
            usbh_kill_urb(&rtl8152_class->bulkout_urb);
        }

        if (rtl8152_class->intin) {
            usbh_kill_urb(&rtl8152_class->intin_urb);
        }

        if (hport->config.intf[intf].devname[0] != '\0') {
            USB_LOG_INFO("Unregister rtl8152 Class:%s\r\n", hport->config.intf[intf].devname);
            usbh_rtl8152_stop(rtl8152_class);
        }

        memset(rtl8152_class, 0, sizeof(struct usbh_rtl8152));
    }

    return ret;
}

void usbh_rtl8152_rx_thread(void *argument)
{
    uint32_t g_rtl8152_rx_length;
    int ret;
    uint16_t len;
    uint16_t data_offset;
#if CONFIG_USBHOST_RTL8152_ETH_MAX_RX_SIZE <= (16 * 1024)
    uint32_t transfer_size = CONFIG_USBHOST_RTL8152_ETH_MAX_RX_SIZE;
#else
    uint32_t transfer_size = (16 * 1024);
#endif

    (void)argument;
    USB_LOG_INFO("Create rtl8152 rx thread\r\n");
    // clang-format off
find_class:
    // clang-format on
    g_rtl8152_class.connect_status = false;
    if (usbh_find_class_instance("/dev/rtl8152") == NULL) {
        goto delete;
    }

    while (g_rtl8152_class.connect_status == false) {
        ret = usbh_rtl8152_get_connect_status(&g_rtl8152_class);
        if (ret < 0) {
            usb_osal_msleep(100);
            goto find_class;
        }
        usb_osal_msleep(128);
    }

    if (g_rtl8152_class.rtl_ops.enable) {
        g_rtl8152_class.rtl_ops.enable(&g_rtl8152_class);
    } else {
        goto delete;
    }

    rtl8152_set_rx_mode(&g_rtl8152_class);
    rtl8152_set_speed(&g_rtl8152_class, AUTONEG_ENABLE, g_rtl8152_class.supports_gmii ? SPEED_1000 : SPEED_100, DUPLEX_FULL);

    g_rtl8152_rx_length = 0;
    while (1) {
        usbh_bulk_urb_fill(&g_rtl8152_class.bulkin_urb, g_rtl8152_class.hport, g_rtl8152_class.bulkin, &g_rtl8152_rx_buffer[g_rtl8152_rx_length], transfer_size, USB_OSAL_WAITING_FOREVER, NULL, NULL);
        ret = usbh_submit_urb(&g_rtl8152_class.bulkin_urb);
        if (ret < 0) {
            goto find_class;
        }

        g_rtl8152_rx_length += g_rtl8152_class.bulkin_urb.actual_length;

        /* A transfer is complete because last packet is a short packet.
         * Short packet is not zero, match g_rtl8152_rx_length % USB_GET_MAXPACKETSIZE(g_rtl8152_class.bulkin->wMaxPacketSize).
         * Short packet is zero, check if g_rtl8152_class.bulkin_urb.actual_length < transfer_size, for example transfer is complete with size is 1024 < 2048.
        */
        if (g_rtl8152_rx_length % USB_GET_MAXPACKETSIZE(g_rtl8152_class.bulkin->wMaxPacketSize) ||
            (g_rtl8152_class.bulkin_urb.actual_length < transfer_size)) {
            data_offset = 0;

            USB_LOG_DBG("rxlen:%d\r\n", g_rtl8152_rx_length);
            while (g_rtl8152_rx_length > 0) {
                struct rx_desc *rx_desc = (struct rx_desc *)&g_rtl8152_rx_buffer[data_offset];

                len = rx_desc->opts1 & RX_LEN_MASK;

                USB_LOG_DBG("data_offset:%d, eth len:%d\r\n", data_offset, len);

                uint8_t *buf = (uint8_t *)&g_rtl8152_rx_buffer[data_offset + sizeof(struct rx_desc)];
                usbh_rtl8152_eth_input(buf, len);

                data_offset += (len + sizeof(struct rx_desc));
                g_rtl8152_rx_length -= (len + sizeof(struct rx_desc));

                if (len & (RX_ALIGN - 1)) {
                    data_offset += (RX_ALIGN - (len & (RX_ALIGN - 1)));
                    g_rtl8152_rx_length -= (RX_ALIGN - (len & (RX_ALIGN - 1)));
                }
            }
        } else {
#if CONFIG_USBHOST_RTL8152_ETH_MAX_RX_SIZE <= (16 * 1024)
            if (g_rtl8152_rx_length == CONFIG_USBHOST_RTL8152_ETH_MAX_RX_SIZE) {
#else
            if ((g_rtl8152_rx_length + (16 * 1024)) > CONFIG_USBHOST_RTL8152_ETH_MAX_RX_SIZE) {
#endif
                USB_LOG_ERR("Rx packet is overflow, please reduce tcp window size or increase CONFIG_USBHOST_RTL8152_ETH_MAX_RX_SIZE\r\n");
                while (1) {
                }
            }
        }
    }
    // clang-format off
delete:
    USB_LOG_INFO("Delete rtl8152 rx thread\r\n");
    usb_osal_thread_delete(NULL);
    // clang-format on
}

uint8_t *usbh_rtl8152_get_eth_txbuf(void)
{
    return (g_rtl8152_tx_buffer + sizeof(struct tx_desc));
}

int usbh_rtl8152_eth_output(uint32_t buflen)
{
    struct tx_desc *tx_desc;

    if (g_rtl8152_class.connect_status == false) {
        return -USB_ERR_NOTCONN;
    }

    tx_desc = (struct tx_desc *)g_rtl8152_tx_buffer;
    tx_desc->opts1 = buflen | TX_FS | TX_LS;
    tx_desc->opts2 = 0;

    USB_LOG_DBG("txlen:%d\r\n", buflen + sizeof(struct tx_desc));

    usbh_bulk_urb_fill(&g_rtl8152_class.bulkout_urb, g_rtl8152_class.hport, g_rtl8152_class.bulkout, g_rtl8152_tx_buffer, buflen + sizeof(struct tx_desc), USB_OSAL_WAITING_FOREVER, NULL, NULL);
    return usbh_submit_urb(&g_rtl8152_class.bulkout_urb);
}

__WEAK void usbh_rtl8152_run(struct usbh_rtl8152 *rtl8152_class)
{
    (void)rtl8152_class;
}

__WEAK void usbh_rtl8152_stop(struct usbh_rtl8152 *rtl8152_class)
{
    (void)rtl8152_class;
}

static const uint16_t rtl_id_table[][2] = {
    { 0x0BDA, 0x8152 },
    { 0, 0 },
};

static const struct usbh_class_driver rtl8152_class_driver = {
    .driver_name = "rtl8152",
    .connect = usbh_rtl8152_connect,
    .disconnect = usbh_rtl8152_disconnect
};

CLASS_INFO_DEFINE const struct usbh_class_info rtl8152_class_info = {
    .match_flags = USB_CLASS_MATCH_VID_PID | USB_CLASS_MATCH_INTF_CLASS,
    .class = 0xff,
    .subclass = 0x00,
    .protocol = 0x00,
    .id_table = rtl_id_table,
    .class_driver = &rtl8152_class_driver
};
