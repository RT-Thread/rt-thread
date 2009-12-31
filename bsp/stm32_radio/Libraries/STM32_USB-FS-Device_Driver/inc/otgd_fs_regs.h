/******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
* File Name          : otgd_fs_regs.h
* Author             : STMicroelectronics
* Version            : V3.1.0
* Date               : 10/30/2009
* Description        : USB OTG IP hardware registers.
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

#ifndef __USB_OTG_REGS_H__
#define __USB_OTG_REGS_H__

#ifdef STM32F10X_CL

#include "stm32f10x.h"
#include "usb_type.h"

#define USB_OTG_FS1_BASE_ADDR                0x50000000

#define USB_OTG_CORE_GLOBAL_REGS_OFFSET      0x000
#define USB_OTG_DEV_GLOBAL_REG_OFFSET        0x800
#define USB_OTG_DEV_IN_EP_REG_OFFSET         0x900
#define USB_OTG_EP_REG_OFFSET                0x20
#define USB_OTG_DEV_OUT_EP_REG_OFFSET        0xB00
#define USB_OTG_HOST_GLOBAL_REG_OFFSET       0x400
#define USB_OTG_HOST_PORT_REGS_OFFSET        0x440
#define USB_OTG_HOST_CHAN_REGS_OFFSET        0x500
#define USB_OTG_CHAN_REGS_OFFSET             0x20
#define USB_OTG_PCGCCTL_OFFSET               0xE00
#define USB_OTG_DATA_FIFO_OFFSET             0x1000
#define USB_OTG_DATA_FIFO_SIZE               0x1000

#define MAX_PERIO_FIFOS                      8
#define MAX_TX_FIFOS                         4
#define MAX_EPS_CHANNELS                     8

#define DEV_NP_TX_FIFO_SIZE                  160
#define RX_FIFO_SIZE                         160
#define TX_FIFO_SIZE                         160

/*******************************************************************************
 * USB_OTG Core registers .
 * The USB_OTG_core_regs structure defines the size
 * and relative field offsets for the Core Global registers.
 ******************************************************************************/
typedef struct _USB_OTG_common_regs  //000h
{

  __IO uint32_t otg_ctl;      /* USB_OTG Control and Status Register    000h*/
  __IO uint32_t otg_int;      /* USB_OTG Interrupt Register             004h*/
  __IO uint32_t ahb_cfg;      /* Core AHB Configuration Register    008h*/
  __IO uint32_t usb_cfg;      /* Core USB Configuration Register    00Ch*/
  __IO uint32_t rst_ctl;      /* Core Reset Register                010h*/
  __IO uint32_t int_sts;      /* Core Interrupt Register            014h*/
  __IO uint32_t int_msk;      /* Core Interrupt Mask Register       018h*/
  __IO uint32_t rx_stsr;      /* Receive Sts Q Read Register        01Ch*/
  __IO uint32_t rx_stsp;      /* Receive Sts Q Read & POP Register  020h*/
  __IO uint32_t rx_fifo_siz;  /* Receive FIFO Size Register         024h*/
  __IO uint32_t np_tx_fifo_siz;   /* Non Periodic Tx FIFO Size Register 028h*/
  __IO uint32_t np_tx_sts;    /* Non Periodic Tx FIFO/Queue Sts reg 02Ch*/
  __IO uint32_t i2c_ctl;      /* I2C Access Register                030h*/
  __IO uint32_t phy_vnd_ctl;  /* PHY Vendor Control Register        034h*/
  __IO uint32_t gpio;         /* General Purpose IO Register        038h*/
  __IO uint32_t usr_id;       /* User ID Register                   03Ch*/
  __IO uint32_t snps_id;      /* Synopsys ID Register               040h*/
  __IO uint32_t hw_cfg1;      /* User HW Config1 Register (RO)      044h*/
  __IO uint32_t hw_cfg2;      /* User HW Config2 Register (RO)      048h*/
  __IO uint32_t hw_cfg3;      /* User HW Config3 Register (RO)      04Ch*/
  __IO uint32_t hw_cfg4;      /* User HW Config4 Register (RO)      050h*/
  uint32_t  reserved[43];          /* Reserved                      054h-0FFh*/
  __IO uint32_t host_p_tx_fifo_siz; /* Host Periodic Tx FIFO Size Reg     100h*/
  __IO uint32_t dev_p_tx_fsiz_dieptxf[15];/* dev Periodic Transmit FIFO */

}
USB_OTG_common_regs;

/*******************************************************************************
 * dev Registers
 * dev Global Registers : Offsets 800h-BFFh
 * The following structures define the size and relative field offsets
 * for the dev Mode Registers.
 * These registers are visible only in dev mode and must not be
 * accessed in Host mode, as the results are unknown
 ******************************************************************************/
typedef struct _USB_OTG_dev_regs // 800h
{

  __IO uint32_t dev_cfg;         /* dev Configuration Register   800h*/
  __IO uint32_t dev_ctl;         /* dev Control Register         804h*/
  __IO uint32_t dev_sts;         /* dev Status Register (RO)     808h*/
  uint32_t reserved3;         /* Reserved                     80Ch*/
  __IO uint32_t dev_in_ep_msk;   /* dev IN Endpoint Mask         810h*/
  __IO uint32_t dev_out_ep_msk;  /* dev OUT Endpoint Mask        814h*/
  __IO uint32_t dev_all_int;     /* dev All Endpoints Itr Reg    818h*/
  __IO uint32_t dev_all_int_msk; /* dev All Endpoints Itr Mask   81Ch*/
  uint32_t  Reserved8;       /* Reserved                     820h*/
  __IO uint32_t Reserved9;       /* Reserved                     824h*/
  __IO uint32_t dev_vbus_dis;    /* dev VBUS discharge Register  828h*/
  __IO uint32_t dev_vbus_pulse;  /* dev VBUS Pulse Register      82Ch*/
  __IO uint32_t dev_thr_ctl;     /* dev thr                      830h*/
  __IO uint32_t dev_fifo_empty_msk; /* dev empty msk             834h*/

}
USB_OTG_dev_regs;
/*******************************************************************************
 * dev Logical IN Endpoint-Specific Registers: Offsets 900h-AFCh
 * There will be one set of endpoint registers per logical endpointimplemented.
 * These registers are visible only in dev mode and must not be
 * accessed in Host mode, as the results are unknown
*******************************************************************************/
typedef struct _USB_OTG_dev_in_ep_regs
{
  __IO uint32_t dev_in_ep_ctl; /* dev IN Endpoint Control Reg 900h + (ep_num * 20h) + 00h*/
  uint32_t reserved04;             /* Reserved                       900h + (ep_num * 20h) + 04h*/
  __IO uint32_t dev_in_ep_int; /* dev IN Endpoint Itr Reg     900h + (ep_num * 20h) + 08h*/
  uint32_t reserved0C;             /* Reserved                       900h + (ep_num * 20h) + 0Ch*/
  __IO uint32_t dev_in_ep_txfer_siz; /* IN Endpoint Txfer Size   900h + (ep_num * 20h) + 10h*/
  __IO uint32_t dev_in_ep_dma; /* IN Endpoint DMA Address Reg    900h + (ep_num * 20h) + 14h*/
  __IO uint32_t dev_tx_fifo_sts;/*IN Endpoint Tx FIFO Status Reg 900h + (ep_num * 20h) + 18h*/
  uint32_t reserved18;             /* Reserved  900h+(ep_num*20h)+1Ch-900h+ (ep_num * 20h) + 1Ch*/

}
USB_OTG_dev_in_ep_regs;

/*******************************************************************************
 * dev Logical OUT Endpoint-Specific Registers Offsets: B00h-CFCh
 * There will be one set of endpoint registers per logical endpoint
 * implemented.
 * These registers are visible only in dev mode and must not be
 * accessed in Host mode, as the results are unknown
******************************************************************************/
typedef struct _USB_OTG_dev_out_ep_regs
{
  __IO uint32_t dev_out_ep_ctl;       /* dev OUT Endpoint Control Reg  B00h + (ep_num * 20h) + 00h*/
  __IO uint32_t dev_out_ep_frm_nbr;   /* dev OUT Endpoint Frame number B00h + (ep_num * 20h) + 04h*/
  __IO uint32_t dev_out_ep_int;              /* dev OUT Endpoint Itr Reg      B00h + (ep_num * 20h) + 08h*/
  uint32_t reserved0C;                    /* Reserved                         B00h + (ep_num * 20h) + 0Ch*/
  __IO uint32_t dev_out_ep_txfer_siz; /* dev OUT Endpoint Txfer Size   B00h + (ep_num * 20h) + 10h*/
  __IO uint32_t dev_out_ep_dma;              /* dev OUT Endpoint DMA Address  B00h + (ep_num * 20h) + 14h*/
  uint32_t reserved18[2];                 /* Reserved B00h + (ep_num * 20h) + 18h - B00h + (ep_num * 20h) + 1Ch*/

}
USB_OTG_dev_out_ep_regs;
/*******************************************************************************
 * Host Mode Register Structures
 * The Host Global Registers structure defines the size and relative
 * field offsets for the Host Mode Global Registers.
 * Host Global Registers offsets 400h-7FFh.
*******************************************************************************/
typedef struct _USB_OTG_host_regs
{
  __IO uint32_t host_cfg;             /* Host Configuration Register    400h*/
  __IO uint32_t host_frm_intrvl;      /* Host Frame Interval Register   404h*/
  __IO uint32_t host_frm_nbr;         /* Host Frame Nbr/Frame Remaining 408h*/
  uint32_t reserved40C;                   /* Reserved                       40Ch*/
  __IO uint32_t host_p_tx_sts;   /* Host Periodic Tx FIFO/ Queue Status 410h*/
  __IO uint32_t host_all_int;   /* Host All Channels Interrupt Register 414h*/
  __IO uint32_t host_all_int_msk;   /* Host All Channels Interrupt Mask 418h*/

}
USB_OTG_host_regs;

/*******************************************************************************
* Host Channel Specific Registers 500h-5FCh
*******************************************************************************/
typedef struct _USB_OTG_hc_regs
{

  __IO uint32_t hc_char;
  __IO uint32_t hc_split;
  __IO uint32_t hc_int;
  __IO uint32_t hc_int_msk;
  __IO uint32_t hc_txfer_siz;
  __IO uint32_t hc_dma;
  uint32_t reserved[2];

}
USB_OTG_hc_regs;
/*******************************************************************************
 * otg Core registers .
 * The USB_OTG_core_regs structure defines the size
 * and relative field offsets for the Core Global registers.
 ******************************************************************************/
typedef struct USB_OTG_core_regs  //000h
{
  USB_OTG_common_regs         *common_regs;
  USB_OTG_dev_regs            *dev_regs;
  USB_OTG_host_regs           *host_regs;
  USB_OTG_dev_in_ep_regs      *inep_regs[MAX_EPS_CHANNELS];
  USB_OTG_dev_out_ep_regs     *outep_regs[MAX_EPS_CHANNELS];
  USB_OTG_hc_regs             *hc_regs[MAX_EPS_CHANNELS];
  __IO uint32_t                    *hprt0;
  __IO uint32_t                    *data_fifo[MAX_EPS_CHANNELS];
  __IO uint32_t                    *pcgcctl;

}
USB_OTG_CORE_REGS , *pUSB_OTG_CORE_REGS;
/******************************************************************************/

typedef union _USB_OTG_OTG_ctl_data
{
  uint32_t d32;
  struct
  {
uint32_t sesreqscs :
    1;
uint32_t sesreq :
    1;
uint32_t reserved2_7 :
    6;
uint32_t hstnegscs :
    1;
uint32_t hnpreq :
    1;
uint32_t hstsethnpen :
    1;
uint32_t devhnpen :
    1;
uint32_t reserved12_15 :
    4;
uint32_t conidsts :
    1;
uint32_t reserved17 :
    1;
uint32_t asesvld :
    1;
uint32_t bsesvld :
    1;
uint32_t currmod :
    1;
uint32_t reserved21_31 :
    11;
  }
  b;
} USB_OTG_OTG_ctl_data;

/******************************************************************************/

typedef union _USB_OTG_OTG_int_data
{
  uint32_t d32;
  struct
  {
uint32_t reserved0_1 :
    2;
uint32_t sesenddet :
    1;
uint32_t reserved3_7 :
    5;
uint32_t sesreqsucstschng :
    1;
uint32_t hstnegsucstschng :
    1;
uint32_t reserver10_16 :
    7;
uint32_t hstnegdet :
    1;
uint32_t adevtoutchng :
    1;
uint32_t debdone :
    1;
uint32_t reserved31_20 :
    12;
  }
  b;
} USB_OTG_OTG_int_data;


/******************************************************************************/


typedef union _USB_OTG_ahb_cfg_data
{
  uint32_t d32;
  struct
  {
uint32_t glblintrmsk :
    1;
uint32_t hburstlen :
    4;
uint32_t dmaenable :
    1;
uint32_t reserved :
    1;
uint32_t nptxfemplvl_txfemplvl :
    1;
uint32_t ptxfemplvl :
    1;
uint32_t reserved9_31 :
    23;
  }
  b;
} USB_OTG_ahb_cfg_data;

/******************************************************************************/

typedef union _USB_OTG_usb_cfg_data
{
  uint32_t d32;
  struct
  {
uint32_t toutcal :
    3;
uint32_t phyif :
    1;
uint32_t ulpi_utmi_sel :
    1;
uint32_t fsintf :
    1;
uint32_t physel :
    1;
uint32_t ddrsel :
    1;
uint32_t srpcap :
    1;
uint32_t hnpcap :
    1;
uint32_t usbtrdtim :
    4;
uint32_t nptxfrwnden :
    1;
uint32_t phylpwrclksel :
    1;
uint32_t otgutmifssel :
    1;
uint32_t ulpi_fsls :
    1;
uint32_t ulpi_auto_res :
    1;
uint32_t ulpi_clk_sus_m :
    1;
uint32_t ulpi_ext_vbus_drv :
    1;
uint32_t ulpi_int_vbus_indicator :
    1;
uint32_t term_sel_dl_pulse :
    1;
uint32_t reserved :
    6;
uint32_t force_host :
    1;
uint32_t force_dev :
    1;
uint32_t corrupt_tx :
    1;
  }
  b;
} USB_OTG_usb_cfg_data;
/******************************************************************************/

typedef union _USB_OTG_rst_ctl_data
{
  uint32_t d32;
  struct
  {
uint32_t csftrst :
    1;
uint32_t hsftrst :
    1;
uint32_t hstfrm :
    1;
uint32_t intknqflsh :
    1;
uint32_t rxfflsh :
    1;
uint32_t txfflsh :
    1;
uint32_t txfnum :
    5;
uint32_t reserved11_29 :
    19;
uint32_t dmareq :
    1;
uint32_t ahbidle :
    1;
  }
  b;
} USB_OTG_rst_ctl_data;

/******************************************************************************/

typedef union _USB_OTG_int_msk_data
{
  uint32_t d32;
  struct
  {
uint32_t reserved0 :
    1;
uint32_t modemismatch :
    1;
uint32_t otgintr :
    1;
uint32_t sofintr :
    1;
uint32_t rxstsqlvl :
    1;
uint32_t nptxfempty :
    1;
uint32_t ginnakeff :
    1;
uint32_t goutnakeff :
    1;
uint32_t reserved8 :
    1;
uint32_t i2cintr :
    1;
uint32_t erlysuspend :
    1;
uint32_t usbsuspend :
    1;
uint32_t usbreset :
    1;
uint32_t enumdone :
    1;
uint32_t isooutdrop :
    1;
uint32_t eopframe :
    1;
uint32_t reserved16 :
    1;
uint32_t epmismatch :
    1;
uint32_t inepintr :
    1;
uint32_t outepintr :
    1;
uint32_t incomplisoin :
    1;
uint32_t incomplisoout :
    1;
uint32_t reserved22_23 :
    2;
uint32_t portintr :
    1;
uint32_t hcintr :
    1;
uint32_t ptxfempty :
    1;
uint32_t reserved27 :
    1;
uint32_t conidstschng :
    1;
uint32_t disconnect :
    1;
uint32_t sessreqintr :
    1;
uint32_t wkupintr :
    1;
  }
  b;
} USB_OTG_int_msk_data;

/******************************************************************************/


typedef union _USB_OTG_int_sts_data
{
  uint32_t d32;
  struct
  {
uint32_t curmode :
    1;
uint32_t modemismatch :
    1;
uint32_t otgintr :
    1;
uint32_t sofintr :
    1;
uint32_t rxstsqlvl :
    1;
uint32_t nptxfempty :
    1;
uint32_t ginnakeff :
    1;
uint32_t goutnakeff :
    1;
uint32_t reserved8 :
    1;
uint32_t i2cintr :
    1;
uint32_t erlysuspend :
    1;
uint32_t usbsuspend :
    1;
uint32_t usbreset :
    1;
uint32_t enumdone :
    1;
uint32_t isooutdrop :
    1;
uint32_t eopframe :
    1;
uint32_t intokenrx :
    1;
uint32_t epmismatch :
    1;
uint32_t inepint:
    1;
uint32_t outepintr :
    1;
uint32_t incomplisoin :
    1;
uint32_t incomplisoout :
    1;
uint32_t reserved22_23 :
    2;
uint32_t portintr :
    1;
uint32_t hcintr :
    1;
uint32_t ptxfempty :
    1;
uint32_t reserved27 :
    1;
uint32_t conidstschng :
    1;
uint32_t disconnect :
    1;
uint32_t sessreqintr :
    1;
uint32_t wkupintr :
    1;
  }
  b;
} USB_OTG_int_sts_data;

/******************************************************************************/
typedef union _USB_OTG_dev_rx_sts_data
{

  uint32_t d32;
  struct
  {
uint32_t epnum :
    4;
uint32_t bcnt :
    11;
uint32_t dpid :
    2;
uint32_t pktsts :
    4;
uint32_t fn :
    4;
uint32_t reserved :
    7;
  }
  b;
} USB_OTG_dev_rx_sts_data;

/******************************************************************************/
typedef union _USB_OTG_host_rx_sts_data
{

  uint32_t d32;
  struct
  {
uint32_t chnum :
    4;
uint32_t bcnt :
    11;
uint32_t dpid :
    2;
uint32_t pktsts :
    4;
uint32_t reserved :
    11;
  }
  b;
} USB_OTG_host_rx_sts_data;

/******************************************************************************/

typedef union _USB_OTG_fifo_size_data
{
  uint32_t d32;
  struct
  {
uint32_t startaddr :
    16;
uint32_t depth :
    16;
  }
  b;
} USB_OTG_fifo_size_data;

/******************************************************************************/

typedef union _USB_OTG_np_tx_sts_data
{
  uint32_t d32;
  struct
  {
uint32_t nptxfspcavail :
    16;
uint32_t nptxqspcavail :
    8;
uint32_t nptxqtop_terminate :
    1;
uint32_t nptxqtop_token :
    2;
uint32_t nptxqtop_chnep :
    4;
uint32_t reserved :
    1;
  }
  b;
} USB_OTG_np_tx_sts_data;

/******************************************************************************/

typedef union _USB_OTG_dev_tx_fifo_sts_data
{
  uint32_t d32;
  struct
  {
uint32_t txfspcavail :
    16;
uint32_t reserved :
    16;
  }
  b;
} USB_OTG_dev_tx_fifo_sts_data;

/******************************************************************************/
typedef union _USB_OTG_i2c_ctl_data
{

  uint32_t d32;
  struct
  {
uint32_t rwdata :
    8;
uint32_t regaddr :
    8;
uint32_t addr :
    7;
uint32_t i2cen :
    1;
uint32_t ack :
    1;
uint32_t i2csuspctl :
    1;
uint32_t i2cdevaddr :
    2;
uint32_t dat_se0:
    1;
uint32_t reserved :
    1;
uint32_t rw :
    1;
uint32_t bsydne :
    1;
  }
  b;
} USB_OTG_i2c_ctl_data;

/******************************************************************************/

typedef union _USB_OTG_gpio_data
{

  uint32_t d32;
  struct
  {
    /* input */
uint32_t ovrcur :
    1;
uint32_t otgid :
    1;
uint32_t reserved_in :
    14;
    /* Output */
uint32_t pwdn :
    1;
uint32_t i2cifen :
    1;
uint32_t vbussensingA :
    1;
uint32_t vbussensingB :
    1;
uint32_t SOFouten :
    1;
uint32_t reserved_out :
    11;
  }
  b;
} USB_OTG_gpio_data;


/******************************************************************************/

typedef union _USB_OTG_hw_cfg1_data
{

  uint32_t d32;
  struct
  {
uint32_t ep_dir0 :
    2;
uint32_t ep_dir1 :
    2;
uint32_t ep_dir2 :
    2;
uint32_t ep_dir3 :
    2;
uint32_t ep_dir4 :
    2;
uint32_t ep_dir5 :
    2;
uint32_t ep_dir6 :
    2;
uint32_t ep_dir7 :
    2;
uint32_t ep_dir8 :
    2;
uint32_t ep_dir9 :
    2;
uint32_t ep_dir10 :
    2;
uint32_t ep_dir11 :
    2;
uint32_t ep_dir12 :
    2;
uint32_t ep_dir13 :
    2;
uint32_t ep_dir14 :
    2;
uint32_t ep_dir15 :
    2;
  }
  b;
} USB_OTG_hw_cfg1_data;

/******************************************************************************/
typedef union _USB_OTG_hw_cfg2_data
{
  uint32_t d32;
  struct
  {
uint32_t op_mode :
    3;
uint32_t architecture :
    2;
uint32_t point2point :
    1;
uint32_t hs_phy_type :
    2;
uint32_t fs_phy_type :
    2;
uint32_t num_dev_ep :
    4;
uint32_t num_host_chan :
    4;
uint32_t perio_ep_supported :
    1;
uint32_t dynamic_fifo :
    1;
uint32_t rx_status_q_depth :
    2;
uint32_t nonperio_tx_q_depth :
    2;
uint32_t host_perio_tx_q_depth :
    2;
uint32_t dev_token_q_depth :
    5;
uint32_t reserved31 :
    1;
  }
  b;
} USB_OTG_hw_cfg2_data;

/******************************************************************************/

typedef union _USB_OTG_hw_cfg3_data
{

  uint32_t d32;
  struct
  {
uint32_t xfer_size_cntr_width :
    4;
uint32_t packet_size_cntr_width :
    3;
uint32_t otg_func :
    1;
uint32_t i2c :
    1;
uint32_t vendor_ctrl_if :
    1;
uint32_t optional_features :
    1;
uint32_t synch_reset_type :
    1;
uint32_t ahb_phy_clock_synch :
    1;
uint32_t reserved15_13 :
    3;
uint32_t dfifo_depth :
    16;
  }
  b;
} USB_OTG_hw_cfg3_data;

/******************************************************************************/

typedef union _USB_OTG_hw_cfg4_data
{
  uint32_t d32;
  struct
  {
uint32_t num_dev_perio_in_ep :
    4;
uint32_t power_optimiz :
    1;
uint32_t min_ahb_freq :
    9;
uint32_t utmi_phy_data_width :
    2;
uint32_t num_dev_mode_ctrl_ep :
    4;
uint32_t iddig_filt_en :
    1;
uint32_t vbus_valid_filt_en :
    1;
uint32_t a_valid_filt_en :
    1;
uint32_t b_valid_filt_en :
    1;
uint32_t session_end_filt_en :
    1;
uint32_t ded_fifo_en :
    1;
uint32_t num_in_eps :
    4;
uint32_t reserved31_30 :
    2;
  }
  b;
} USB_OTG_hw_cfg4_data;

/******************************************************************************/
typedef union _USB_OTG_dev_cfg_data
{

  uint32_t d32;
  struct
  {
uint32_t devspd :
    2;
uint32_t nzstsouthshk :
    1;
uint32_t reserved3 :
    1;
uint32_t devaddr :
    7;
uint32_t perfrint :
    2;
uint32_t reserved13_17 :
    5;
uint32_t epmscnt :
    4;
  }
  b;
} USB_OTG_dev_cfg_data;

/******************************************************************************/

typedef union _USB_OTG_dev_ctl_data
{

  uint32_t d32;
  struct
  {
uint32_t rmtwkupsig :
    1;
uint32_t sftdiscon :
    1;
uint32_t gnpinnaksts :
    1;
uint32_t goutnaksts :
    1;
uint32_t tstctl :
    3;
uint32_t sgnpinnak :
    1;
uint32_t cgnpinnak :
    1;
uint32_t sgoutnak :
    1;
uint32_t cgoutnak :
    1;
uint32_t reserved :
    21;
  }
  b;
} USB_OTG_dev_ctl_data;

/******************************************************************************/
typedef union _USB_OTG_dev_sts_data
{

  uint32_t d32;
  struct
  {
uint32_t suspsts :
    1;
uint32_t enumspd :
    2;
uint32_t errticerr :
    1;
uint32_t reserved4_7:
    4;
uint32_t soffn :
    14;
uint32_t reserved22_31 :
    10;
  }
  b;
} USB_OTG_dev_sts_data;

/******************************************************************************/

typedef union _USB_OTG_dev_in_ep_int_data
{

  uint32_t d32;
  struct
  {
uint32_t xfercompl :
    1;
uint32_t epdisabled :
    1;
uint32_t ahberr :
    1;
uint32_t timeout :
    1;
uint32_t intktxfemp :
    1;
uint32_t intknepmis :
    1;
uint32_t inepnakeff :
    1;
uint32_t emptyintr :
    1;
uint32_t txfifoundrn :
    1;
uint32_t reserved08_31 :
    23;
  }
  b;
} USB_OTG_dev_in_ep_int_data;

/******************************************************************************/

typedef union _USB_OTG_dev_in_ep_int_data  USB_OTG_dev_in_ep_msk_data;
/******************************************************************************/

typedef union _USB_OTG_dev_out_ep_int_data
{

  uint32_t d32;
  struct
  {
uint32_t xfercompl :
    1;
uint32_t epdisabled :
    1;
uint32_t ahberr :
    1;
uint32_t setup :
    1;
uint32_t reserved04_31 :
    28;
  }
  b;
} USB_OTG_dev_out_ep_int_data;

/******************************************************************************/

typedef union _USB_OTG_dev_out_ep_int_data  USB_OTG_dev_out_ep_msk_data;

/******************************************************************************/
typedef union _USB_OTG_dev_all_int_data
{

  uint32_t d32;
  struct
  {
uint32_t in :
    16;
uint32_t out :
    16;
  }
  ep;
  struct
  {
    /** IN Endpoint bits */
uint32_t inep0  :
    1;
uint32_t inep1  :
    1;
uint32_t inep2  :
    1;
uint32_t inep3  :
    1;
uint32_t inep4  :
    1;
uint32_t inep5  :
    1;
uint32_t inep6  :
    1;
uint32_t inep7  :
    1;
uint32_t inep8  :
    1;
uint32_t inep9  :
    1;
uint32_t inep10 :
    1;
uint32_t inep11 :
    1;
uint32_t inep12 :
    1;
uint32_t inep13 :
    1;
uint32_t inep14 :
    1;
uint32_t inep15 :
    1;
    /** OUT Endpoint bits */
uint32_t outep0  :
    1;
uint32_t outep1  :
    1;
uint32_t outep2  :
    1;
uint32_t outep3  :
    1;
uint32_t outep4  :
    1;
uint32_t outep5  :
    1;
uint32_t outep6  :
    1;
uint32_t outep7  :
    1;
uint32_t outep8  :
    1;
uint32_t outep9  :
    1;
uint32_t outep10 :
    1;
uint32_t outep11 :
    1;
uint32_t outep12 :
    1;
uint32_t outep13 :
    1;
uint32_t outep14 :
    1;
uint32_t outep15 :
    1;
  }
  b;
} USB_OTG_dev_all_int_data;

/******************************************************************************/
typedef union _USB_OTG_token_qr1_data
{

  uint32_t d32;
  struct
  {
uint32_t intknwptr :
    5;
uint32_t reserved05_06 :
    2;
uint32_t wrap_bit :
    1;
uint32_t epnums0_5 :
    24;
  }
  b;
} USB_OTG_token_qr1_data;

/******************************************************************************/

typedef union _USB_OTG_dev_thr_ctl_data
{

  uint32_t d32;
  struct
  {
uint32_t non_iso_thr_en :
    1;
uint32_t iso_thr_en :
    1;
uint32_t tx_thr_len :
    9;
uint32_t reserved11_15 :
    5;
uint32_t rx_thr_en :
    1;
uint32_t rx_thr_len :
    9;
uint32_t reserved26_31 :
    6;
  }
  b;
} USB_OTG_dev_thr_ctl_data;

/******************************************************************************/
typedef union _USB_OTG_dev_ep_ctl_data
{

  uint32_t d32;
  struct
  {
uint32_t mps :
    11;
uint32_t nextep :
    4;
uint32_t usbactep :
    1;
uint32_t dpid :
    1;
uint32_t naksts :
    1;
uint32_t eptype :
    2;
uint32_t snp :
    1;
uint32_t stall :
    1;
uint32_t txfnum :
    4;
uint32_t cnak :
    1;
uint32_t snak :
    1;
uint32_t setd0pid :
    1;
uint32_t setd1pid :
    1;
uint32_t epdis :
    1;
uint32_t epena :
    1;
  }
  b;
} USB_OTG_dev_ep_ctl_data;

/******************************************************************************/

typedef union _USB_OTG_dev_ep_txfer_siz_data
{

  uint32_t d32;
  struct
  {
uint32_t xfersize :
    19;
uint32_t pktcnt :
    10;
uint32_t mc :
    2;
uint32_t reserved :
    1;
  }
  b;
} USB_OTG_dev_ep_txfer_siz_data;

/******************************************************************************/

typedef union _USB_OTG_dev_ep_txfer_size0_data
{

  uint32_t d32;
  struct
  {
uint32_t xfersize :
    7;
uint32_t reserved7_18 :
    12;
uint32_t pktcnt :
    1;
uint32_t reserved20_28 :
    9;
uint32_t supcnt :
    2;
    uint32_t reserved31;
  }
  b;
} USB_OTG_dev_ep_txfer_size0_data;

/******************************************************************************/
typedef union _USB_OTG_host_cfg_data
{

  uint32_t d32;
  struct
  {
uint32_t fslspclksel :
    2;
uint32_t fslssupp :
    1;
  }
  b;
} USB_OTG_host_cfg_data;

/******************************************************************************/

typedef union _USB_OTG_Host_frm_intrvl_data
{
  uint32_t d32;
  struct
  {
uint32_t frint :
    16;
uint32_t reserved :
    16;
  }
  b;
} USB_OTG_Host_frm_intrvl_data;

/******************************************************************************/
#define HFNUM_MAX_FRNUM 0x3FFF
typedef union _USB_OTG_host_frm_nbr_data
{

  uint32_t d32;
  struct
  {
uint32_t frnum :
    16;
uint32_t frrem :
    16;
  }
  b;
} USB_OTG_host_frm_nbr_data;

/******************************************************************************/

typedef union _USB_OTG_host_perio_tx_sts_data
{

  uint32_t d32;
  struct
  {
uint32_t ptxfspcavail :
    16;
uint32_t ptxqspcavail :
    8;
uint32_t ptxqtop_terminate :
    1;
uint32_t ptxqtop_token :
    2;
uint32_t ptxqtop_chnum :
    4;
uint32_t ptxqtop_odd :
    1;
  }
  b;
} USB_OTG_host_perio_tx_sts_data;

/******************************************************************************/
typedef union _USB_OTG_hprt0_data
{
  uint32_t d32;
  struct
  {
uint32_t prtconnsts :
    1;
uint32_t prtconndet :
    1;
uint32_t prtena :
    1;
uint32_t prtenchng :
    1;
uint32_t prtovrcurract :
    1;
uint32_t prtovrcurrchng :
    1;
uint32_t prtres :
    1;
uint32_t prtsusp :
    1;
uint32_t prtrst :
    1;
uint32_t reserved9 :
    1;
uint32_t prtlnsts :
    2;
uint32_t prtpwr :
    1;
uint32_t prttstctl :
    4;
uint32_t prtspd :
    2;
uint32_t reserved19_31 :
    13;
  }
  b;
} USB_OTG_hprt0_data;

/******************************************************************************/

typedef union _USB_OTG_host_all_int_data
{
  uint32_t d32;
  struct
  {
uint32_t ch0 :
    1;
uint32_t ch1 :
    1;
uint32_t ch2 :
    1;
uint32_t ch3 :
    1;
uint32_t ch4 :
    1;
uint32_t ch5 :
    1;
uint32_t ch6 :
    1;
uint32_t ch7 :
    1;
uint32_t ch8 :
    1;
uint32_t ch9 :
    1;
uint32_t ch10 :
    1;
uint32_t ch11 :
    1;
uint32_t ch12 :
    1;
uint32_t ch13 :
    1;
uint32_t ch14 :
    1;
uint32_t ch15 :
    1;
uint32_t reserved :
    16;
  }
  b;

  struct
  {
uint32_t chint :
    16;
uint32_t reserved :
    16;
  }
  b2;
} USB_OTG_host_all_int_data;


/******************************************************************************/

typedef union _USB_OTG_host_all_int_msk_data
{
  uint32_t d32;
  struct
  {
uint32_t ch0 :
    1;
uint32_t ch1 :
    1;
uint32_t ch2 :
    1;
uint32_t ch3 :
    1;
uint32_t ch4 :
    1;
uint32_t ch5 :
    1;
uint32_t ch6 :
    1;
uint32_t ch7 :
    1;
uint32_t ch8 :
    1;
uint32_t ch9 :
    1;
uint32_t ch10 :
    1;
uint32_t ch11 :
    1;
uint32_t ch12 :
    1;
uint32_t ch13 :
    1;
uint32_t ch14 :
    1;
uint32_t ch15 :
    1;
uint32_t reserved :
    16;
  }
  b;

  struct
  {
uint32_t chint :
    16;
uint32_t reserved :
    16;
  }
  b2;
} USB_OTG_host_all_int_msk_data;

/******************************************************************************/

typedef union _USB_OTG_hc_char_data
{

  uint32_t d32;
  struct
  {
uint32_t mps :
    11;
uint32_t epnum :
    4;
uint32_t epdir :
    1;
uint32_t reserved :
    1;
uint32_t lspddev :
    1;
uint32_t eptype :
    2;
uint32_t multicnt :
    2;
uint32_t devaddr :
    7;
uint32_t oddfrm :
    1;
uint32_t chdis :
    1;
uint32_t chen :
    1;
  }
  b;
} USB_OTG_hc_char_data;

/******************************************************************************/
typedef union _USB_OTG_hc_splt_data
{

  uint32_t d32;
  struct
  {
uint32_t prtaddr :
    7;
uint32_t hubaddr :
    7;
uint32_t xactpos :
    2;
uint32_t compsplt :
    1;
uint32_t reserved :
    14;
uint32_t spltena :
    1;
  }
  b;
} USB_OTG_hc_splt_data;

/******************************************************************************/

typedef union _USB_OTG_hc_int_data
{
  uint32_t d32;
  struct
  {
uint32_t xfercomp :
    1;
uint32_t chhltd :
    1;
uint32_t ahberr :
    1;
uint32_t stall :
    1;
uint32_t nak :
    1;
uint32_t ack :
    1;
uint32_t nyet :
    1;
uint32_t xacterr :
    1;
uint32_t bblerr :
    1;
uint32_t frmovrun :
    1;
uint32_t datatglerr :
    1;
uint32_t reserved :
    21;
  }
  b;
} USB_OTG_hc_int_data;

/******************************************************************************/


typedef union _USB_OTG_hc_txfer_siz_data
{

  uint32_t d32;
  struct
  {
uint32_t xfersize :
    19;
uint32_t pktcnt :
    10;
uint32_t pid :
    2;
uint32_t dopng :
    1;
  }
  b;
} USB_OTG_hc_txfer_siz_data;

/******************************************************************************/

typedef union _USB_OTG_hc_int_msk_data
{

  uint32_t d32;
  struct
  {
uint32_t xfercompl :
    1;
uint32_t chhltd :
    1;
uint32_t ahberr :
    1;
uint32_t stall :
    1;
uint32_t nak :
    1;
uint32_t ack :
    1;
uint32_t nyet :
    1;
uint32_t xacterr :
    1;
uint32_t bblerr :
    1;
uint32_t frmovrun :
    1;
uint32_t datatglerr :
    1;
uint32_t reserved :
    21;
  }
  b;
} USB_OTG_hc_int_msk_data;

/******************************************************************************/

typedef union _USB_OTG_host_pcgcctl_data
{
  uint32_t d32;
  struct
  {
uint32_t stoppclk :
    1;
uint32_t gatehclk :
    1;
uint32_t pwrclmp :
    1;
uint32_t rstpdwnmodule :
    1;
uint32_t physuspended :
    1;
uint32_t reserved :
    27;
  }
  b;
} USB_OTG_host_pcgcctl_data;

#endif /* STM32F10X_CL */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/

#endif
