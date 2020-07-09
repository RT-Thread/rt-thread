/*
 * x1000_dwc.h
 *
 *  Created on: 2017Äê2ÔÂ3ÈÕ
 *      Author: Urey
 */

#ifndef _X1000_DWC_H_
#define _X1000_DWC_H_

#define DWC_FORCE_SPEED_FULL        0

#if DWC_FORCE_SPEED_FULL
#define ENDPOINT_PACKET_SIZE        64
#define CONTROL_MAX_PACKET_SIZE     64
#else
#define ENDPOINT_PACKET_SIZE        512
#define CONTROL_MAX_PACKET_SIZE     64
#endif

#define DWC_EP_IN_OFS   0
#define DWC_EP_OUT_OFS  16

#define DWC_EPNO_MASK   0x7f

typedef struct dwc_ep_t
{
    uint8_t     num;  /* ep number used for register address lookup */
#define EP_IDLE             0
#define EP_TRANSFERED       1
#define EP_TRANSFERING      2

#define EP_SETUP            0
#define EP_DATA             1
#define EP_STATUS           2
#define EP_SETUP_PHASEDONE  3
    uint32_t    ep_state;
    uint32_t    is_in;   /* ep dir 1 = out */

    uint32_t    active; /* ep active */
    uint32_t    type;    /* ep type */
#define DWC_OTG_EP_TYPE_CONTROL 0
#define DWC_OTG_EP_TYPE_ISOC    1
#define DWC_OTG_EP_TYPE_BULK    2
#define DWC_OTG_EP_TYPE_INTR    3

    uint32_t    maxpacket; /* max packet bytes */
//    uint32_t    ctrl_req_addr;
    void*       xfer_buff;   /* pointer to transfer buffer */

    uint32_t    xfer_len;   /* number of bytes to transfer */

    uint32_t    xfer_count; /* number of bytes transfered */

} dwc_ep;

typedef union hwcfg1_data {
    uint32_t d32;

    struct {
        unsigned ep_dir0:2;
        unsigned ep_dir1:2;
        unsigned ep_dir2:2;
        unsigned ep_dir3:2;
        unsigned ep_dir4:2;
        unsigned ep_dir5:2;
        unsigned ep_dir6:2;
        unsigned ep_dir7:2;
        unsigned ep_dir8:2;
        unsigned ep_dir9:2;
        unsigned ep_dir10:2;
        unsigned ep_dir11:2;
        unsigned ep_dir12:2;
        unsigned ep_dir13:2;
        unsigned ep_dir14:2;
        unsigned ep_dir15:2;
    } b;
#define DWC_HWCFG1_DIR_BIDIR    0x0
#define DWC_HWCFG1_DIR_IN       0x1
#define DWC_HWCFG1_DIR_OUT      0x2
} hwcfg1_data_t;

/**
 * This union represents the bit fields in the User HW Config2
 * Register.  Read the register into the <i>d32</i> element then read
 * out the bits using the <i>b</i>it elements.
 */
typedef union hwcfg2_data {
    /** raw register data */
    uint32_t d32;
    /** register bits */
    struct {
        /* GHWCFG2 */
        unsigned op_mode:3;
#define DWC_HWCFG2_OP_MODE_HNP_SRP_CAPABLE_OTG      0
#define DWC_HWCFG2_OP_MODE_SRP_ONLY_CAPABLE_OTG     1
#define DWC_HWCFG2_OP_MODE_NO_HNP_SRP_CAPABLE_OTG   2
#define DWC_HWCFG2_OP_MODE_SRP_CAPABLE_DEVICE       3
#define DWC_HWCFG2_OP_MODE_NO_SRP_CAPABLE_DEVICE    4
#define DWC_HWCFG2_OP_MODE_SRP_CAPABLE_HOST         5
#define DWC_HWCFG2_OP_MODE_NO_SRP_CAPABLE_HOST      6

        unsigned architecture:2;
        unsigned point2point:1;
        unsigned hs_phy_type:2;
#define DWC_HWCFG2_HS_PHY_TYPE_NOT_SUPPORTED 0
#define DWC_HWCFG2_HS_PHY_TYPE_UTMI 1
#define DWC_HWCFG2_HS_PHY_TYPE_ULPI 2
#define DWC_HWCFG2_HS_PHY_TYPE_UTMI_ULPI 3

        unsigned fs_phy_type:2;
        unsigned num_dev_ep:4;
        unsigned num_host_chan:4;
        unsigned perio_ep_supported:1;
        unsigned dynamic_fifo:1;
        unsigned multi_proc_int:1;
        unsigned reserved21:1;
        unsigned nonperio_tx_q_depth:2;
        unsigned host_perio_tx_q_depth:2;
        unsigned dev_token_q_depth:5;
        unsigned otg_enable_ic_usb:1;
    } b;
} hwcfg2_data_t;


/**
 * This union represents the bit fields in the User HW Config3
 * Register.  Read the register into the <i>d32</i> element then read
 * out the bits using the <i>b</i>it elements.
 */
typedef union hwcfg3_data {
    /** raw register data */
    uint32_t d32;
    /** register bits */
    struct {
        /* GHWCFG3 */
        unsigned xfer_size_cntr_width:4;
        unsigned packet_size_cntr_width:3;
        unsigned otg_func:1;
        unsigned i2c:1;
        unsigned vendor_ctrl_if:1;
        unsigned optional_features:1;
        unsigned synch_reset_type:1;
        unsigned adp_supp:1;
        unsigned otg_enable_hsic:1;
        unsigned bc_support:1;
        unsigned otg_lpm_en:1;
        unsigned dfifo_depth:16;
    } b;
} hwcfg3_data_t;


/**
 * This union represents the bit fields in the User HW Config4
 * Register.  Read the register into the <i>d32</i> element then read
 * out the bits using the <i>b</i>it elements.
 */
typedef union hwcfg4_data {
    /** raw register data */
    uint32_t d32;
    /** register bits */
    struct {
        unsigned num_dev_perio_in_ep:4;
        unsigned power_optimiz:1;
        unsigned min_ahb_freq:1;
        unsigned part_power_down:1;
        unsigned reserved:7;
        unsigned utmi_phy_data_width:2;
        unsigned num_dev_mode_ctrl_ep:4;
        unsigned iddig_filt_en:1;
        unsigned vbus_valid_filt_en:1;
        unsigned a_valid_filt_en:1;
        unsigned b_valid_filt_en:1;
        unsigned session_end_filt_en:1;
        unsigned ded_fifo_en:1;
        unsigned num_in_eps:4;
        unsigned desc_dma:1;
        unsigned desc_dma_dyn:1;
    } b;
} hwcfg4_data_t;

typedef union dwc_state {
    uint8_t d8;

    struct {
        unsigned event:1;
#define USB_CABLE_DISCONNECT    0
#define USB_CABLE_CONNECT       1
#define USB_CABLE_SUSPEND       2
#define USB_CONFIGURED          3
        unsigned state:7;
    }b;

} dwc_st;

typedef struct dwc_cfg_if_t
{
    hwcfg1_data_t hwcfg1;
    hwcfg2_data_t hwcfg2;
    hwcfg3_data_t hwcfg3;
    hwcfg4_data_t hwcfg4;
    dwc_st  status;
#define USB_SPEED_HIGH  0
#define USB_SPEED_FULL  1
#define USB_SPEED_LOW   2
    uint8_t speed;
    uint8_t is_dma;
//    uint8_t ep0State;
    dwc_ep *dep[32];

    rt_sem_t    isr_sem;
} dwc_handle;

/**
 * This union represents the bit fields in the Device Control
 * Register.  Read the register into the <i>d32</i> member then
 * set/clear the bits using the <i>b</i>it elements.
 */
typedef union dctl_data {
    /** raw register data */
    uint32_t d32;
    /** register bits */
    struct {
        /** Remote Wakeup */
        unsigned rmtwkupsig:1;
        /** Soft Disconnect */
        unsigned sftdiscon:1;
        /** Global Non-Periodic IN NAK Status */
        unsigned gnpinnaksts:1;
        /** Global OUT NAK Status */
        unsigned goutnaksts:1;
        /** Test Control */
        unsigned tstctl:3;
        /** Set Global Non-Periodic IN NAK */
        unsigned sgnpinnak:1;
        /** Clear Global Non-Periodic IN NAK */
        unsigned cgnpinnak:1;
        /** Set Global OUT NAK */
        unsigned sgoutnak:1;
        /** Clear Global OUT NAK */
        unsigned cgoutnak:1;
        /** Power-On Programming Done */
        unsigned pwronprgdone:1;
        /** Reserved */
        unsigned reserved:1;
        /** Global Multi Count */
        unsigned gmc:2;
        /** Ignore Frame Number for ISOC EPs */
        unsigned ifrmnum:1;
        /** NAK on Babble */
        unsigned nakonbble:1;
        /** Enable Continue on BNA */
        unsigned encontonbna:1;

        unsigned reserved18_31:14;
    } b;
} dctl_data_t;

/**
 * This union represents the bit fields of the Core Interrupt Mask
 * Register (GINTMSK). Set/clear the bits using the bit fields then
 * write the <i>d32</i> value to the register.
 */
typedef union gintmsk_data {
    /** raw register data */
    uint32_t d32;
    /** register bits */
    struct {
        unsigned reserved0:1;
        unsigned modemismatch:1;
        unsigned otgintr:1;
        unsigned sofintr:1;
        unsigned rxstsqlvl:1;
        unsigned nptxfempty:1;
        unsigned ginnakeff:1;
        unsigned goutnakeff:1;
        unsigned ulpickint:1;
        unsigned i2cintr:1;
        unsigned erlysuspend:1;
        unsigned usbsuspend:1;
        unsigned usbreset:1;
        unsigned enumdone:1;
        unsigned isooutdrop:1;
        unsigned eopframe:1;
        unsigned restoredone:1;
        unsigned epmismatch:1;
        unsigned inepintr:1;
        unsigned outepintr:1;
        unsigned incomplisoin:1;
        unsigned incomplisoout:1;
        unsigned fetsusp:1;
        unsigned resetdet:1;
        unsigned portintr:1;
        unsigned hcintr:1;
        unsigned ptxfempty:1;
        unsigned lpmtranrcvd:1;
        unsigned conidstschng:1;
        unsigned disconnect:1;
        unsigned sessreqintr:1;
        unsigned wkupintr:1;
    } b;
} gintmsk_data_t;

/**
 * This union represents the bit fields in the Device EP Control
 * Register.  Read the register into the <i>d32</i> member then
 * set/clear the bits using the <i>b</i>it elements.
 */
typedef union depctl_data {
    /** raw register data */
    uint32_t d32;
    /** register bits */
    struct {
        /** Maximum Packet Size
         * IN/OUT EPn
         * IN/OUT EP0 - 2 bits
         *   2'b00: 64 Bytes
         *   2'b01: 32
         *   2'b10: 16
         *   2'b11: 8 */
        unsigned mps:11;
#define DWC_DEP0CTL_MPS_64   0
#define DWC_DEP0CTL_MPS_32   1
#define DWC_DEP0CTL_MPS_16   2
#define DWC_DEP0CTL_MPS_8    3

        /** Next Endpoint
         * IN EPn/IN EP0
         * OUT EPn/OUT EP0 - reserved */
        unsigned nextep:4;

        /** USB Active Endpoint */
        unsigned usbactep:1;

        /** Endpoint DPID (INTR/Bulk IN and OUT endpoints)
         * This field contains the PID of the packet going to
         * be received or transmitted on this endpoint. The
         * application should program the PID of the first
         * packet going to be received or transmitted on this
         * endpoint , after the endpoint is
         * activated. Application use the SetD1PID and
         * SetD0PID fields of this register to program either
         * D0 or D1 PID.
         *
         * The encoding for this field is
         *   - 0: D0
         *   - 1: D1
         */
        unsigned dpid:1;

        /** NAK Status */
        unsigned naksts:1;

        /** Endpoint Type
         *  2'b00: Control
         *  2'b01: Isochronous
         *  2'b10: Bulk
         *  2'b11: Interrupt */
        unsigned eptype:2;

        /** Snoop Mode
         * OUT EPn/OUT EP0
         * IN EPn/IN EP0 - reserved */
        unsigned snp:1;

        /** Stall Handshake */
        unsigned stall:1;

        /** Tx Fifo Number
         * IN EPn/IN EP0
         * OUT EPn/OUT EP0 - reserved */
        unsigned txfnum:4;

        /** Clear NAK */
        unsigned cnak:1;
        /** Set NAK */
        unsigned snak:1;
        /** Set DATA0 PID (INTR/Bulk IN and OUT endpoints)
         * Writing to this field sets the Endpoint DPID (DPID)
         * field in this register to DATA0. Set Even
         * (micro)frame (SetEvenFr) (ISO IN and OUT Endpoints)
         * Writing to this field sets the Even/Odd
         * (micro)frame (EO_FrNum) field to even (micro)
         * frame.
         */
        unsigned setd0pid:1;
        /** Set DATA1 PID (INTR/Bulk IN and OUT endpoints)
         * Writing to this field sets the Endpoint DPID (DPID)
         * field in this register to DATA1 Set Odd
         * (micro)frame (SetOddFr) (ISO IN and OUT Endpoints)
         * Writing to this field sets the Even/Odd
         * (micro)frame (EO_FrNum) field to odd (micro) frame.
         */
        unsigned setd1pid:1;

        /** Endpoint Disable */
        unsigned epdis:1;
        /** Endpoint Enable */
        unsigned epena:1;
    } b;
} depctl_data_t;

/**
 * This union represents the bit fields in the Device IN EP Interrupt
 * Register and the Device IN EP Common Mask Register.
 *
 * - Read the register into the <i>d32</i> member then set/clear the
 *   bits using the <i>b</i>it elements.
 */
typedef union diepint_data {
    /** raw register data */
    uint32_t d32;
    /** register bits */
    struct {
        /** Transfer complete mask */
        unsigned xfercompl:1;
        /** Endpoint disable mask */
        unsigned epdisabled:1;
        /** AHB Error mask */
        unsigned ahberr:1;
        /** TimeOUT Handshake mask (non-ISOC EPs) */
        unsigned timeout:1;
        /** IN Token received with TxF Empty mask */
        unsigned intktxfemp:1;
        /** IN Token Received with EP mismatch mask */
        unsigned intknepmis:1;
        /** IN Endpoint NAK Effective mask */
        unsigned inepnakeff:1;
        /** Reserved */
        unsigned emptyintr:1;

        unsigned txfifoundrn:1;

        /** BNA Interrupt mask */
        unsigned bna:1;

        unsigned reserved10_12:3;
        /** BNA Interrupt mask */
        unsigned nak:1;

        unsigned reserved14_31:18;
    } b;
} diepint_data_t;

/**
 * This union represents the bit fields in the Device IN EP
 * Common/Dedicated Interrupt Mask Register.
 */
typedef union diepint_data diepmsk_data_t;

/**
 * This union represents the bit fields in the Device OUT EP Interrupt
 * Registerand Device OUT EP Common Interrupt Mask Register.
 *
 * - Read the register into the <i>d32</i> member then set/clear the
 *   bits using the <i>b</i>it elements.
 */
typedef union doepint_data {
    /** raw register data */
    uint32_t d32;
    /** register bits */
    struct {
        /** Transfer complete */
        unsigned xfercompl:1;
        /** Endpoint disable  */
        unsigned epdisabled:1;
        /** AHB Error */
        unsigned ahberr:1;
        /** Setup Phase Done (contorl EPs) */
        unsigned setup:1;
        /** OUT Token Received when Endpoint Disabled */
        unsigned outtknepdis:1;

        unsigned stsphsercvd:1;
        /** Back-to-Back SETUP Packets Received */
        unsigned back2backsetup:1;

        unsigned reserved7:1;
        /** OUT packet Error */
        unsigned outpkterr:1;
        /** BNA Interrupt */
        unsigned bna:1;

        unsigned reserved10:1;
        /** Packet Drop Status */
        unsigned pktdrpsts:1;
        /** Babble Interrupt */
        unsigned babble:1;
        /** NAK Interrupt */
        unsigned nak:1;
        /** NYET Interrupt */
        unsigned nyet:1;

        unsigned reserved15_31:17;
    } b;
} doepint_data_t;

/**
 * This union represents the bit fields in the Device OUT EP
 * Common/Dedicated Interrupt Mask Register.
 */
typedef union doepint_data doepmsk_data_t;

/**
 * This union represents the bit fields in the Device All EP Interrupt
 * and Mask Registers.
 * - Read the register into the <i>d32</i> member then set/clear the
 *   bits using the <i>b</i>it elements.
 */
typedef union daint_data {
    /** raw register data */
    uint32_t d32;
    /** register bits */
    struct {
        /** IN Endpoint bits */
        unsigned in:16;
        /** OUT Endpoint bits */
        unsigned out:16;
    } ep;
    struct {
        /** IN Endpoint bits */
        unsigned inep0:1;
        unsigned inep1:1;
        unsigned inep2:1;
        unsigned inep3:1;
        unsigned inep4:1;
        unsigned inep5:1;
        unsigned inep6:1;
        unsigned inep7:1;
        unsigned inep8:1;
        unsigned inep9:1;
        unsigned inep10:1;
        unsigned inep11:1;
        unsigned inep12:1;
        unsigned inep13:1;
        unsigned inep14:1;
        unsigned inep15:1;
        /** OUT Endpoint bits */
        unsigned outep0:1;
        unsigned outep1:1;
        unsigned outep2:1;
        unsigned outep3:1;
        unsigned outep4:1;
        unsigned outep5:1;
        unsigned outep6:1;
        unsigned outep7:1;
        unsigned outep8:1;
        unsigned outep9:1;
        unsigned outep10:1;
        unsigned outep11:1;
        unsigned outep12:1;
        unsigned outep13:1;
        unsigned outep14:1;
        unsigned outep15:1;
    } b;
} daint_data_t;

/*
 * Functions
 */
/* USB Endpoint Callback Events */
#define USB_EVT_SETUP       1   /* Setup Packet */
#define USB_EVT_OUT         2   /* OUT Packet */
#define USB_EVT_IN          3   /*  IN Packet */
#define USB_EVT_OUT_NAK     4   /* OUT Packet - Not Acknowledged */
#define USB_EVT_IN_NAK      5   /*  IN Packet - Not Acknowledged */
#define USB_EVT_OUT_STALL   6   /* OUT Packet - Stalled */
#define USB_EVT_IN_STALL    7   /*  IN Packet - Stalled */
#define USB_EVT_OUT_DMA_EOT 8   /* DMA OUT EP - End of Transfer */
#define USB_EVT_IN_DMA_EOT  9   /* DMA  IN EP - End of Transfer */
#define USB_EVT_OUT_DMA_NDR 10  /* DMA OUT EP - New Descriptor Request */
#define USB_EVT_IN_DMA_NDR  11  /* DMA  IN EP - New Descriptor Request */
#define USB_EVT_OUT_DMA_ERR 12  /* DMA OUT EP - Error */
#define USB_EVT_IN_DMA_ERR  13  /* DMA  IN EP - Error */
#define USB_EVT_SOF         14

void x1000_usbd_init(dwc_handle *dwc);
void dwc_set_address(dwc_handle *dwc,uint8_t address);
int dwc_ep_disable(dwc_handle *dwc,uint8_t epnum);
int dwc_ep_enable(dwc_handle *dwc,uint8_t epnum);

int dwc_set_ep_stall(dwc_handle *dwc,uint8_t epnum);
int dwc_clr_ep_stall(dwc_handle *dwc,uint8_t epnum);
int dwc_enable_in_ep(dwc_handle *dwc,uint8_t epnum);
int dwc_enable_out_ep(dwc_handle *dwc,uint8_t epnum);
void dwc_ep0_status(dwc_handle *dwc);
void dwc_otg_ep0_out_start(dwc_handle *dwc);

void dwc_handle_ep_data_in_phase(dwc_handle *dwc, uint8_t epnum);
void dwc_handle_ep_status_in_phase(dwc_handle *dwc, uint8_t epnum);
void dwc_handle_ep_data_out_phase(dwc_handle *dwc,uint8_t epnum);

void dwc_ep_out_start(dwc_handle *dwc,uint8_t epnum);
int HW_GetPKT(dwc_handle *dwc, uint8_t epnum, uint8_t *buf,int size);
int HW_SendPKT(dwc_handle *dwc, uint8_t epnum, const uint8_t *buf, int size);

extern void x1000_usbd_event_cb(uint8_t epnum,uint32_t event,void *arg);
#endif /* _X1000_DWC_H_ */
