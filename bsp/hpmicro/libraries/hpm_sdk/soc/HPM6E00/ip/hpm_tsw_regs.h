/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_TSW_H
#define HPM_TSW_H

typedef struct {
    __R  uint8_t  RESERVED0[4];                /* 0x0 - 0x3: Reserved */
    __RW uint32_t LU_MAIN_CTRL;                /* 0x4: LU_MAIN control */
    __RW uint32_t LU_MAIN_HITMEM;              /* 0x8: LU_MAIN hit */
    __R  uint32_t LU_MAIN_PARAM;               /* 0xC: LU_MAIN parameter */
    __RW uint32_t LU_MAIN_BYPASS;              /* 0x10: LU_MAIN bypass */
    __RW uint32_t LU_MAIN_PCP_REMAP;           /* 0x14: LU_MAIN PCP remap */
    __R  uint32_t LU_MAIN_VERSION;             /* 0x18: LU_MAIN version */
    __R  uint8_t  RESERVED1[4];                /* 0x1C - 0x1F: Reserved */
    __RW uint32_t LU_MAIN_INTF_ACTION;         /* 0x20: LU_MAIN low word of action data for internal frames */
    __R  uint8_t  RESERVED2[4];                /* 0x24 - 0x27: Reserved */
    __RW uint32_t LU_MAIN_BC_ACTION;           /* 0x28: LU_MAIN low word of action data for broadcast frames */
    __R  uint8_t  RESERVED3[4];                /* 0x2C - 0x2F: Reserved */
    __RW uint32_t LU_MAIN_NN_ACTION;           /* 0x30: LU_MAIN low word of  action data for unknown frames */
    __R  uint8_t  RESERVED4[204];              /* 0x34 - 0xFF: Reserved */
    __R  uint32_t APB2AXIS_CAM_STS;            /* 0x100: status register */
    __R  uint8_t  RESERVED5[12];               /* 0x104 - 0x10F: Reserved */
    __R  uint32_t APB2AXIS_CAM_REQ_CNT;        /* 0x110: request count */
    __R  uint32_t APB2AXIS_CAM_FILLSTS;        /* 0x114: fill status */
    __W  uint32_t APB2AXIS_CAM_RESET;          /* 0x118: reset */
    __R  uint32_t APB2AXIS_CAM_PARAM;          /* 0x11C: parameter */
    __RW uint32_t APB2AXI_CAM_REQDATA_0;       /* 0x120: data0 */
    __RW uint32_t APB2AXI_CAM_REQDATA_1;       /* 0x124: data1 */
    __RW uint32_t APB2AXI_CAM_REQDATA_2;       /* 0x128: data2 */
    __R  uint8_t  RESERVED6[212];              /* 0x12C - 0x1FF: Reserved */
    __R  uint32_t APB2AXIS_ALMEM_STS;          /* 0x200: status register */
    __R  uint8_t  RESERVED7[12];               /* 0x204 - 0x20F: Reserved */
    __R  uint32_t APB2AXIS_ALMEM_REQ_CNT;      /* 0x210: request count */
    __R  uint32_t APB2AXIS_ALMEM_FILLSTS;      /* 0x214: fill status */
    __W  uint32_t APB2AXIS_ALMEM_RESET;        /* 0x218: reset */
    __R  uint32_t APB2AXIS_ALMEM_PARAM;        /* 0x21C: parameter */
    __RW uint32_t APB2AXIS_ALMEM_REQDATA_0;    /* 0x220: data0 */
    __RW uint32_t APB2AXIS_ALMEM_REQDATA_1;    /* 0x224: data1 */
    __R  uint8_t  RESERVED8[88];               /* 0x228 - 0x27F: Reserved */
    __R  uint32_t AXIS2APB_ALMEM_STS;          /* 0x280: status register */
    __R  uint8_t  RESERVED9[12];               /* 0x284 - 0x28F: Reserved */
    __R  uint32_t AXIS2APB_ALMEM_RESP_CNT;     /* 0x290: response count */
    __R  uint32_t AXIS2APB_ALMEM_FILLSTS;      /* 0x294: fill status */
    __RW uint32_t AXIS2APB_ALMEM_RESET;        /* 0x298: reset */
    __R  uint32_t AXIS2APB_ALMEM_PARAM;        /* 0x29C: parameter */
    __RW uint32_t AXIS2APB_ALMEM_RESPDATA_0;   /* 0x2A0: data0 */
    __RW uint32_t AXIS2APB_ALMEM_RESPDATA_1;   /* 0x2A4: data1 */
    __R  uint8_t  RESERVED10[344];             /* 0x2A8 - 0x3FF: Reserved */
    __RW uint32_t HITMEM[4];                   /* 0x400 - 0x40C: hitmem */
    __R  uint8_t  RESERVED11[3056];            /* 0x410 - 0xFFF: Reserved */
    __R  uint32_t APB2AXIS_LOOKUP_STS;         /* 0x1000: status register */
    __R  uint8_t  RESERVED12[12];              /* 0x1004 - 0x100F: Reserved */
    __R  uint32_t APB2AXIS_LOOKUP_REQ_CNT;     /* 0x1010: response count */
    __R  uint32_t APB2AXIS_LOOKUP_FILLSTS;     /* 0x1014: fill status */
    __RW uint32_t APB2AXIS_LOOKUP_RESET;       /* 0x1018: reset */
    __R  uint32_t APB2AXIS_LOOKUP_PARAM;       /* 0x101C: parameter */
    __RW uint32_t APB2AXIS_LOOKUP_REQDATA_0;   /* 0x1020: LOOKUP REQUEST Register REQ_DATA_0 */
    __RW uint32_t APB2AXIS_LOOKUP_REQDATA_1;   /* 0x1024: LOOKUP REQUEST Register REQ_DATA_1 */
    __R  uint8_t  RESERVED13[4];               /* 0x1028 - 0x102B: Reserved */
    __RW uint32_t APB2AXIS_LOOKUP_REQDATA_3;   /* 0x102C: LOOKUP REQUEST Register REQ_DATA_2 */
    __R  uint8_t  RESERVED14[80];              /* 0x1030 - 0x107F: Reserved */
    __R  uint32_t AXIS2APB_LOOKUP_STS;         /* 0x1080: status register */
    __R  uint8_t  RESERVED15[12];              /* 0x1084 - 0x108F: Reserved */
    __R  uint32_t AXIS2APB_LOOKUP_RESP_CNT;    /* 0x1090: response count */
    __R  uint32_t AXIS2APB_LOOKUP_FILLSTS;     /* 0x1094: fill status */
    __RW uint32_t AXIS2APB_LOOKUP_RESET;       /* 0x1098: reset */
    __R  uint32_t AXIS2APB_LOOKUP_PARAM;       /* 0x109C: parameter */
    __RW uint32_t AXIS2APB_LOOKUP_RESPDATA_0;  /* 0x10A0: LOOKUP RESPONSE Data Register */
    __R  uint8_t  RESERVED16[4];               /* 0x10A4 - 0x10A7: Reserved */
    __RW uint32_t AXIS2APB_LOOKUP_RESPDATA_1;  /* 0x10A8: LOOKUP RESPONSE Data Register */
    __R  uint8_t  RESERVED17[3924];            /* 0x10AC - 0x1FFF: Reserved */
    __R  uint32_t CENTRAL_CSR_VERSION;         /* 0x2000: version register */
    __R  uint32_t CENTRAL_CSR_PARAM;           /* 0x2004: Parameter Register */
    __RW uint32_t CENTRAL_CSR_CONFIG;          /* 0x2008: Configuration Register */
    __R  uint32_t CENTRAL_CSR_CB_PARAM;        /* 0x200C: CB Parameter Register */
    __R  uint32_t CENTRAL_CSR_QCI_CTRL_PARAM;  /* 0x2010: QCI Control Parameter Register */
    __R  uint8_t  RESERVED18[240];             /* 0x2014 - 0x2103: Reserved */
    __R  uint32_t CENTRAL_QCI_HWCFG;           /* 0x2104: PSPF General CTRAL */
    __R  uint8_t  RESERVED19[8];               /* 0x2108 - 0x210F: Reserved */
    __RW uint32_t CENTRAL_QCI_FILTERSEL;       /* 0x2110: Filter select index */
    __RW uint32_t CENTRAL_QCI_METERSEL;        /* 0x2114: Flowmeter select index */
    __RW uint32_t CENTRAL_QCI_GATESEL;         /* 0x2118: Gate select index */
    __R  uint8_t  RESERVED20[4];               /* 0x211C - 0x211F: Reserved */
    __RW uint32_t CENTRAL_QCI_FCTRL;           /* 0x2120: FILTER SETTING */
    __RW uint32_t CENTRAL_QCI_FSIZE;           /* 0x2124:  */
    __R  uint8_t  RESERVED21[24];              /* 0x2128 - 0x213F: Reserved */
    __R  uint32_t QCI_CNT[6];                  /* 0x2140 - 0x2154: FILTER COUNTER */
    __R  uint8_t  RESERVED22[8];               /* 0x2158 - 0x215F: Reserved */
    __RW uint32_t CENTRAL_QCI_MCTRL;           /* 0x2160: Flow meter settings */
    __R  uint8_t  RESERVED23[12];              /* 0x2164 - 0x216F: Reserved */
    __RW uint32_t CENTRAL_QCI_CIR;             /* 0x2170:  */
    __RW uint32_t CENTRAL_QCI_CBS;             /* 0x2174:  */
    __RW uint32_t CENTRAL_QCI_EIR;             /* 0x2178:  */
    __RW uint32_t CENTRAL_QCI_EBS;             /* 0x217C:  */
    __RW uint32_t CENTRAL_QCI_GCTRL;           /* 0x2180: Gate settings */
    __RW uint32_t CENTRAL_QCI_GSTATUS;         /* 0x2184:  */
    __RW uint32_t CENTRAL_QCI_GLISTINDEX;      /* 0x2188:  */
    __RW uint32_t CENTRAL_QCI_LISTLEN;         /* 0x218C:  */
    __RW uint32_t CENTRAL_QCI_ACYCLETM;        /* 0x2190:  */
    __RW uint32_t CENTRAL_QCI_ABASETM_L;       /* 0x2194:  */
    __RW uint32_t CENTRAL_QCI_ABASETM_H;       /* 0x2198:  */
    __R  uint8_t  RESERVED24[4];               /* 0x219C - 0x219F: Reserved */
    __RW uint32_t CENTRAL_QCI_AENTRY_CTRL;     /* 0x21A0:  */
    __RW uint32_t CENTRAL_QCI_AENTRY_AENTRY_IVAL; /* 0x21A4:  */
    __R  uint32_t CENTRAL_QCI_AENTRY_OCYCLETM; /* 0x21A8:  */
    __R  uint32_t CENTRAL_QCI_AENTRY_OBASETM_L;/* 0x21AC:  */
    __R  uint32_t CENTRAL_QCI_AENTRY_OBASETM_H;/* 0x21B0:  */
    __R  uint8_t  RESERVED25[7756];            /* 0x21B4 - 0x3FFF: Reserved */
    __RW uint32_t MM2S_DMA_CR;                 /* 0x4000: mm2s control register */
    __RW uint32_t MM2S_DMA_SR;                 /* 0x4004: mm2s status */
    __R  uint32_t MM2S_DMA_FILL;               /* 0x4008: mm2s dma fill status */
    __R  uint8_t  RESERVED26[16];              /* 0x400C - 0x401B: Reserved */
    __R  uint32_t MM2S_DMA_CFG;                /* 0x401C: mm2s dma configure */
    __RW uint32_t MM2S_ADDRLO;                 /* 0x4020: mm2s axi address */
    __R  uint8_t  RESERVED27[4];               /* 0x4024 - 0x4027: Reserved */
    __RW uint32_t MM2S_LENGTH;                 /* 0x4028: mm2s axi length */
    __RW uint32_t MM2S_CTRL;                   /* 0x402C: mm2s command control */
    __R  uint32_t MM2S_RESP;                   /* 0x4030: mm2s response buffer */
    __R  uint8_t  RESERVED28[76];              /* 0x4034 - 0x407F: Reserved */
    __RW uint32_t S2MM_DMA_CR;                 /* 0x4080: s2mm dma control */
    __RW uint32_t S2MM_DMA_SR;                 /* 0x4084: s2mm state */
    __R  uint32_t S2MM_DMA_FILL;               /* 0x4088: s2mm buffer fill status */
    __R  uint8_t  RESERVED29[16];              /* 0x408C - 0x409B: Reserved */
    __R  uint32_t S2MM_DMA_CFG;                /* 0x409C: s2mm dma config status */
    __RW uint32_t S2MM_ADDRLO;                 /* 0x40A0: s2mm axi address */
    __R  uint8_t  RESERVED30[4];               /* 0x40A4 - 0x40A7: Reserved */
    __RW uint32_t S2MM_LENGTH;                 /* 0x40A8: s2mm axi length */
    __RW uint32_t S2MM_CTRL;                   /* 0x40AC: s2mm command control */
    __R  uint32_t S2MM_RESP;                   /* 0x40B0: s2mm response buffer */
    __R  uint8_t  RESERVED31[8012];            /* 0x40B4 - 0x5FFF: Reserved */
    __RW uint32_t PTP_EVT_TS_CTL;              /* 0x6000: timestamp control */
    __R  uint8_t  RESERVED32[4];               /* 0x6004 - 0x6007: Reserved */
    __R  uint32_t PTP_EVT_PPS_TOD_SEC;         /* 0x6008: pps tod seconds */
    __R  uint32_t PTP_EVT_PPS_TOD_NS;          /* 0x600C: pps tod sun seconds */
    __R  uint8_t  RESERVED33[12];              /* 0x6010 - 0x601B: Reserved */
    __RW uint32_t PTP_EVT_SCP_SEC0;            /* 0x601C: target time seconds */
    __RW uint32_t PTP_EVT_SCP_NS0;             /* 0x6020: target time sub seconds */
    __R  uint8_t  RESERVED34[4];               /* 0x6024 - 0x6027: Reserved */
    __R  uint32_t PTP_EVT_TMR_STS;             /* 0x6028: timer status */
    __RW uint32_t PTP_EVT_PPS_CMD;             /* 0x602C: pps command control */
    __R  uint32_t PTP_EVT_ATSLO;               /* 0x6030: auxiliray read data sub seconds */
    __R  uint32_t PTP_EVT_ATSHI;               /* 0x6034: auxiliray read data seconds */
    __R  uint8_t  RESERVED35[40];              /* 0x6038 - 0x605F: Reserved */
    __RW uint32_t PTP_EVT_PPS0_INTERVAL;       /* 0x6060: pps0 interval configure */
    __RW uint32_t PTP_EVT_PPS0_WIDTH;          /* 0x6064: pps0 width configure */
    __R  uint8_t  RESERVED36[24];              /* 0x6068 - 0x607F: Reserved */
    __RW uint32_t PTP_EVT_SCP_SEC1;            /* 0x6080: target time seconds */
    __RW uint32_t PTP_EVT_SCP_NS1;             /* 0x6084: target time sub seconds */
    __RW uint32_t PTP_EVT_PPS1_INTERVAL;       /* 0x6088: pps1 interval configure */
    __RW uint32_t PTP_EVT_PPS1_WIDTH;          /* 0x608C: pps1 width configure */
    __R  uint8_t  RESERVED37[16];              /* 0x6090 - 0x609F: Reserved */
    __RW uint32_t PTP_EVT_SCP_SEC2;            /* 0x60A0: target time seconds */
    __RW uint32_t PTP_EVT_SCP_NS2;             /* 0x60A4: target time sub seconds */
    __RW uint32_t PTP_EVT_PPS2_INTERVAL;       /* 0x60A8: pps2 interval configure */
    __RW uint32_t PTP_EVT_PPS2_WIDTH;          /* 0x60AC: pps2 width configure */
    __R  uint8_t  RESERVED38[16];              /* 0x60B0 - 0x60BF: Reserved */
    __RW uint32_t PTP_EVT_SCP_SEC3;            /* 0x60C0: target time seconds */
    __RW uint32_t PTP_EVT_SCP_NS3;             /* 0x60C4: target time sub seconds */
    __RW uint32_t PTP_EVT_PPS3_INTERVAL;       /* 0x60C8: pps3 interval configure */
    __RW uint32_t PTP_EVT_PPS3_WIDTH;          /* 0x60CC: pps3 width configure */
    __R  uint8_t  RESERVED39[16];              /* 0x60D0 - 0x60DF: Reserved */
    __RW uint32_t PTP_EVT_PPS_CTRL0;           /* 0x60E0: pps control 0 register */
    __RW uint32_t PTP_EVT_PPS_SEL;             /* 0x60E4:  */
    __R  uint8_t  RESERVED40[8];               /* 0x60E8 - 0x60EF: Reserved */
    __RW uint32_t SOFT_RST_CTRL;               /* 0x60F0: softer reset control */
    __R  uint8_t  RESERVED41[40716];           /* 0x60F4 - 0xFFFF: Reserved */
    __RW uint32_t CPU_PORT_PORT_MAIN_TAGGING;  /* 0x10000: PVID Tagging Register */
    __RW uint32_t CPU_PORT_PORT_MAIN_ENNABLE;  /* 0x10004: Port Module Enable Register */
    __R  uint8_t  RESERVED42[10232];           /* 0x10008 - 0x127FF: Reserved */
    __R  uint32_t CPU_PORT_EGRESS_STMID_ESELECT; /* 0x12800: Stream Identification */
    __R  uint8_t  RESERVED43[60];              /* 0x12804 - 0x1283F: Reserved */
    __RW uint32_t CPU_PORT_EGRESS_STMID_CONTROL; /* 0x12840:  */
    __RW uint32_t CPU_PORT_EGRESS_STMID_SEQNO; /* 0x12844:  */
    __RW uint32_t CPU_PORT_EGRESS_STMID_MATCHCNT; /* 0x12848:  */
    __R  uint8_t  RESERVED44[4];               /* 0x1284C - 0x1284F: Reserved */
    __RW uint32_t CPU_PORT_EGRESS_STMID_MACLO; /* 0x12850:  */
    __RW uint32_t CPU_PORT_EGRESS_STMID_MACHI; /* 0x12854:  */
    __R  uint8_t  RESERVED45[4];               /* 0x12858 - 0x1285B: Reserved */
    __RW uint32_t CPU_PORT_EGRESS_STMID_AMACHI;/* 0x1285C:  */
    __R  uint8_t  RESERVED46[416];             /* 0x12860 - 0x129FF: Reserved */
    __RW uint32_t CPU_PORT_EGRESS_FRER_CONTROL;/* 0x12A00: Frame Replication and Elimination */
    __RW uint32_t CPU_PORT_EGRESS_FRER_SIDSEL; /* 0x12A04:  */
    __RW uint32_t CPU_PORT_EGRESS_FRER_IRFUNC; /* 0x12A08:  */
    __RW uint32_t CPU_PORT_EGRESS_FRER_SRFUNC; /* 0x12A0C:  */
    __RW uint32_t CPU_PORT_EGRESS_FRER_FSELECT;/* 0x12A10:  */
    __R  uint8_t  RESERVED47[44];              /* 0x12A14 - 0x12A3F: Reserved */
    __RW uint32_t CPU_PORT_EGRESS_FRER_FCTRL;  /* 0x12A40:  */
    __RW uint32_t CPU_PORT_EGRESS_FRER_RESETMSEC; /* 0x12A44:  */
    __RW uint32_t CPU_PORT_EGRESS_FRER_LATRSPERIOD; /* 0x12A48:  */
    __RW uint32_t CPU_PORT_EGRESS_FRER_LATTESTPERIOD; /* 0x12A4C:  */
    __RW uint32_t CPU_PORT_EGRESS_FRER_LATERRDIFFALW; /* 0x12A50:  */
    __RW uint32_t CPU_PORT_EGRESS_FRER_LATERRCNT; /* 0x12A54:  */
    __R  uint8_t  RESERVED48[8];               /* 0x12A58 - 0x12A5F: Reserved */
    __R  uint32_t EGFRCNT[8];                  /* 0x12A60 - 0x12A7C:  */
    __R  uint8_t  RESERVED49[5504];            /* 0x12A80 - 0x13FFF: Reserved */
    __R  uint32_t CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_CNT_BYTE; /* 0x14000:  */
    __R  uint32_t CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS; /* 0x14004:  */
    __RW uint32_t CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG; /* 0x14008:  */
    __RW uint32_t CPU_PORT_IGRESS_RX_FDFIFO_IE_ERROR_FLAG; /* 0x1400C:  */
    __RW uint32_t CPU_PORT_IGRESS_RX_FDFIFO_IN_CONFIG; /* 0x14010:  */
    __RW uint32_t CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG; /* 0x14014:  */
    __W  uint32_t CPU_PORT_IGRESS_RX_FDFIFO_RESET; /* 0x14018:  */
    __R  uint32_t CPU_PORT_IGRESS_RX_FDFIFO_PARAM; /* 0x1401C:  */
    __RW uint32_t CPU_PORT_IGRESS_RX_FDFIFO_STRFWD; /* 0x14020:  */
    __RW uint32_t CPU_PORT_IGRESS_RX_FDFIFO_PORTMASK; /* 0x14024:  */
    __RW uint32_t CPU_PORT_IGRESS_RX_FDFIFO_MIRROR; /* 0x14028:  */
    __RW uint32_t CPU_PORT_IGRESS_RX_FDFIFO_MIRROR_TX; /* 0x1402C:  */
    __R  uint8_t  RESERVED50[2000];            /* 0x14030 - 0x147FF: Reserved */
    __R  uint32_t CPU_PORT_IGRESS_STMID_ESELECT; /* 0x14800: Stream Identification */
    __R  uint8_t  RESERVED51[60];              /* 0x14804 - 0x1483F: Reserved */
    __RW uint32_t CPU_PORT_IGRESS_STMID_CONTROL; /* 0x14840:  */
    __RW uint32_t CPU_PORT_IGRESS_STMID_SEQNO; /* 0x14844:  */
    __RW uint32_t CPU_PORT_IGRESS_STMID_MATCHCNT; /* 0x14848:  */
    __R  uint8_t  RESERVED52[4];               /* 0x1484C - 0x1484F: Reserved */
    __RW uint32_t CPU_PORT_IGRESS_STMID_MACLO; /* 0x14850:  */
    __RW uint32_t CPU_PORT_IGRESS_STMID_MACHI; /* 0x14854:  */
    __R  uint8_t  RESERVED53[4];               /* 0x14858 - 0x1485B: Reserved */
    __RW uint32_t CPU_PORT_IGRESS_STMID_AMACHI;/* 0x1485C:  */
    __R  uint8_t  RESERVED54[416];             /* 0x14860 - 0x149FF: Reserved */
    __RW uint32_t CPU_PORT_IGRESS_FRER_CONTROL;/* 0x14A00: Frame Replication and Elimination */
    __RW uint32_t CPU_PORT_IGRESS_FRER_SIDSEL; /* 0x14A04:  */
    __RW uint32_t CPU_PORT_IGRESS_FRER_IRFUNC; /* 0x14A08:  */
    __RW uint32_t CPU_PORT_IGRESS_FRER_SRFUNC; /* 0x14A0C:  */
    __RW uint32_t CPU_PORT_IGRESS_FRER_FSELECT;/* 0x14A10:  */
    __R  uint8_t  RESERVED55[44];              /* 0x14A14 - 0x14A3F: Reserved */
    __RW uint32_t CPU_PORT_IGRESS_FRER_FCTRL;  /* 0x14A40:  */
    __RW uint32_t CPU_PORT_IGRESS_FRER_RESETMSEC; /* 0x14A44:  */
    __RW uint32_t CPU_PORT_IGRESS_FRER_LATRSPERIOD; /* 0x14A48:  */
    __RW uint32_t CPU_PORT_IGRESS_FRER_LATTESTPERIOD; /* 0x14A4C:  */
    __RW uint32_t CPU_PORT_IGRESS_FRER_LATERRDIFFALW; /* 0x14A50:  */
    __RW uint32_t CPU_PORT_IGRESS_FRER_LATERRCNT; /* 0x14A54:  */
    __R  uint8_t  RESERVED56[8];               /* 0x14A58 - 0x14A5F: Reserved */
    __R  uint32_t IGFRCNT[8];                  /* 0x14A60 - 0x14A7C:  */
    __R  uint8_t  RESERVED57[13700];           /* 0x14A80 - 0x18003: Reserved */
    __RW uint32_t CPU_PORT_MONITOR_CTRL;       /* 0x18004:  */
    __W  uint32_t CPU_PORT_MONITOR_RESET;      /* 0x18008:  */
    __R  uint32_t CPU_PORT_MONITOR_PARAM;      /* 0x1800C:  */
    __R  uint32_t CPU_PORT_MONITOR_TX_COUNTER_TX_FGOOD; /* 0x18010:  */
    __R  uint8_t  RESERVED58[4];               /* 0x18014 - 0x18017: Reserved */
    __R  uint32_t CPU_PORT_MONITOR_TX_COUNTER_TX_FERROR; /* 0x18018:  */
    __R  uint8_t  RESERVED59[4];               /* 0x1801C - 0x1801F: Reserved */
    __R  uint32_t CPU_PORT_MONITOR_TX_COUNTER_TX_DROP_OVFL; /* 0x18020:  */
    __R  uint8_t  RESERVED60[28];              /* 0x18024 - 0x1803F: Reserved */
    __R  uint32_t CPU_PORT_MONITOR_RX_COUNTER_RX_FGOOD; /* 0x18040:  */
    __R  uint8_t  RESERVED61[4];               /* 0x18044 - 0x18047: Reserved */
    __R  uint32_t CPU_PORT_MONITOR_RX_COUNTER_RX_FERROR; /* 0x18048:  */
    __R  uint8_t  RESERVED62[4];               /* 0x1804C - 0x1804F: Reserved */
    __R  uint32_t CPU_PORT_MONITOR_RX_COUNTER_RX_KNOWN; /* 0x18050:  */
    __R  uint8_t  RESERVED63[4];               /* 0x18054 - 0x18057: Reserved */
    __R  uint32_t CPU_PORT_MONITOR_RX_COUNTER_RX_UNKNOWN; /* 0x18058:  */
    __R  uint8_t  RESERVED64[4];               /* 0x1805C - 0x1805F: Reserved */
    __R  uint32_t CPU_PORT_MONITOR_RX_COUNTER_RX_UC; /* 0x18060:  */
    __R  uint8_t  RESERVED65[4];               /* 0x18064 - 0x18067: Reserved */
    __R  uint32_t CPU_PORT_MONITOR_RX_COUNTER_RX_INTERN; /* 0x18068:  */
    __R  uint8_t  RESERVED66[4];               /* 0x1806C - 0x1806F: Reserved */
    __R  uint32_t CPU_PORT_MONITOR_RX_COUNTER_RX_BC; /* 0x18070:  */
    __R  uint8_t  RESERVED67[4];               /* 0x18074 - 0x18077: Reserved */
    __R  uint32_t CPU_PORT_MONITOR_RX_COUNTER_RX_MULTI; /* 0x18078:  */
    __R  uint8_t  RESERVED68[4];               /* 0x1807C - 0x1807F: Reserved */
    __R  uint32_t CPU_PORT_MONITOR_RX_COUNTER_RX_VLAN; /* 0x18080:  */
    __R  uint8_t  RESERVED69[4];               /* 0x18084 - 0x18087: Reserved */
    __R  uint32_t CPU_PORT_MONITOR_RX_COUNTER_RX_DROP_OVFL; /* 0x18088:  */
    __R  uint8_t  RESERVED70[4];               /* 0x1808C - 0x1808F: Reserved */
    __R  uint32_t CPU_PORT_MONITOR_RX_COUNTER_RX_DROP_LU; /* 0x18090:  */
    __R  uint8_t  RESERVED71[4];               /* 0x18094 - 0x18097: Reserved */
    __R  uint32_t CPU_PORT_MONITOR_RX_COUNTER_RX_DROP_ERR; /* 0x18098:  */
    __R  uint8_t  RESERVED72[4];               /* 0x1809C - 0x1809F: Reserved */
    __R  uint32_t CPU_PORT_MONITOR_RX_COUNTER_RX_DROP_VLAN; /* 0x180A0:  */
    __R  uint8_t  RESERVED73[4];               /* 0x180A4 - 0x180A7: Reserved */
    __R  uint32_t CPU_PORT_MONITOR_RX_COUNTER_RX_FPE_FGOOD; /* 0x180A8:  */
    __R  uint8_t  RESERVED74[32596];           /* 0x180AC - 0x1FFFF: Reserved */
    struct {
        struct {
            __R  uint32_t MAC_VER;             /* 0x20000:  */
            __RW uint32_t MAC_MACADDR_L;       /* 0x20004:  */
            __RW uint32_t MAC_MACADDR_H;       /* 0x20008:  */
            __RW uint32_t MAC_MAC_CTRL;        /* 0x2000C:  */
            __R  uint32_t MAC_TX_FRAMES;       /* 0x20010:  */
            __R  uint32_t MAC_RX_FRAMES;       /* 0x20014:  */
            __R  uint32_t MAC_TX_OCTETS;       /* 0x20018:  */
            __R  uint32_t MAC_RX_OCTETS;       /* 0x2001C:  */
            __RW uint32_t MAC_MDIO_CFG;        /* 0x20020:  */
            __RW uint32_t MAC_MDIO_CTRL;       /* 0x20024:  */
            __R  uint32_t MAC_MDIO_RD_DATA;    /* 0x20028:  */
            __RW uint32_t MAC_MDIO_WR_DATA;    /* 0x2002C:  */
            __RW uint32_t MAC_IRQ_CTRL;        /* 0x20030:  */
            __R  uint8_t  RESERVED0[460];      /* 0x20034 - 0x201FF: Reserved */
        } MAC[2];
        __R  uint8_t  RESERVED0[1024];         /* 0x20400 - 0x207FF: Reserved */
        __RW uint32_t RTC_CR;                  /* 0x20800: ONLY IN PORT1 */
        __RW uint32_t RTC_SR;                  /* 0x20804: ONLY IN PORT1 */
        __R  uint8_t  RESERVED1[8];            /* 0x20808 - 0x2080F: Reserved */
        __RW uint32_t RTC_CT_CURTIME_NS;       /* 0x20810: ONLY IN PORT1 */
        __R  uint32_t RTC_CT_CURTIME_SEC;      /* 0x20814: ONLY IN PORT1 */
        __R  uint8_t  RESERVED2[4];            /* 0x20818 - 0x2081B: Reserved */
        __RW uint32_t RTC_CT_TIMER_INCR;       /* 0x2081C: ONLY IN PORT1 */
        __RW uint32_t RTC_OFS_NS;              /* 0x20820: ONLY IN PORT1 */
        __RW uint32_t RTC_OFS_SL;              /* 0x20824: ONLY IN PORT1 */
        __RW uint32_t RTC_OFS_SH;              /* 0x20828: ONLY IN PORT1 */
        __RW uint32_t RTC_OFS_CH;              /* 0x2082C: ONLY IN PORT1 */
        __RW uint32_t RTC_ALARM_NS;            /* 0x20830: ONLY IN PORT1 */
        __RW uint32_t RTC_ALARM_SL;            /* 0x20834: ONLY IN PORT1 */
        __RW uint32_t RTC_ALARM_SH;            /* 0x20838: ONLY IN PORT1 */
        __R  uint8_t  RESERVED3[4];            /* 0x2083C - 0x2083F: Reserved */
        __RW uint32_t RTC_TIMER_A_PERIOD;      /* 0x20840: ONLY IN PORT1 */
        __R  uint8_t  RESERVED4[1984];         /* 0x20844 - 0x21003: Reserved */
        __RW uint32_t TSYN_CR;                 /* 0x21004:  */
        __RW uint32_t TSYN_SR;                 /* 0x21008:  */
        __R  uint8_t  RESERVED5[4];            /* 0x2100C - 0x2100F: Reserved */
        __R  uint32_t TSYN_PTP_TX_STS;         /* 0x21010:  */
        __RW uint32_t TSYN_PTP_TX_DONE;        /* 0x21014:  */
        __W  uint32_t TSYN_PTP_TX_TRIG;        /* 0x21018:  */
        __RW uint32_t TSYN_PTP_RX_STS;         /* 0x2101C:  */
        __RW uint32_t TSYNTMR[5];              /* 0x21020 - 0x21030:  */
        __R  uint8_t  RESERVED6[8];            /* 0x21034 - 0x2103B: Reserved */
        __RW uint32_t TSYN_HCLKDIV;            /* 0x2103C:  */
        __R  uint8_t  RESERVED7[1472];         /* 0x21040 - 0x215FF: Reserved */
        __R  uint32_t TSYN_RXBUF_RX_FRAME_LENGTH_BYTES; /* 0x21600:  */
        __R  uint8_t  RESERVED8[4];            /* 0x21604 - 0x21607: Reserved */
        __R  uint32_t TSYN_RXBUF_RX_TIME_STAMP_L; /* 0x21608:  */
        __R  uint32_t TSYN_RXBUF_RX_TIME_STAMP_H; /* 0x2160C:  */
        __R  uint32_t RXDATA[60];              /* 0x21610 - 0x216FC:  */
        __R  uint8_t  RESERVED9[256];          /* 0x21700 - 0x217FF: Reserved */
        struct {
            __RW uint32_t TXDATA[60];          /* 0x21800 - 0x218EC:  */
            __RW uint32_t TSYN_TXBUF_BIN0_TQUE_AND_TX_LEN; /* 0x218F0:  */
            __R  uint8_t  RESERVED0[4];        /* 0x218F4 - 0x218F7: Reserved */
            __RW uint32_t TSYN_TXBUF_BIN0_TX_TIMESTAMP_L; /* 0x218F8:  */
            __RW uint32_t TSYN_TXBUF_BIN0_TX_TIMESTAMP_H; /* 0x218FC:  */
        } BIN[8];
        __R  uint8_t  RESERVED10[4];           /* 0x22000 - 0x22003: Reserved */
        __R  uint32_t TSN_SHAPER_HWCFG1;       /* 0x22004:  */
        __R  uint8_t  RESERVED11[4];           /* 0x22008 - 0x2200B: Reserved */
        __RW uint32_t TSN_SHAPER_TQAV;         /* 0x2200C:  */
        __R  uint32_t TSN_SHAPER_TQEM;         /* 0x22010:  */
        __RW uint32_t TSN_SHAPER_FPST;         /* 0x22014:  */
        __RW uint32_t TSN_SHAPER_MMCT;         /* 0x22018:  */
        __RW uint32_t TSN_SHAPER_HOLDADV;      /* 0x2201C:  */
        __R  uint8_t  RESERVED12[224];         /* 0x22020 - 0x220FF: Reserved */
        __RW uint32_t MXSDU[8];                /* 0x22100 - 0x2211C:  */
        __RW uint32_t TXSEL[8];                /* 0x22120 - 0x2213C:  */
        __RW uint32_t IDSEL[8];                /* 0x22140 - 0x2215C:  */
        __R  uint8_t  RESERVED13[1696];        /* 0x22160 - 0x227FF: Reserved */
        __RW uint32_t PORT1_QCH0_CFG;          /* 0x22800: qch channel0 control */
        __RW uint32_t PORT1_QCH1_CFG;          /* 0x22804: qch channel1 control */
        __RW uint32_t PORT1_QCH2_CFG;          /* 0x22808: qch channel2 control */
        __RW uint32_t PORT1_QCH3_CFG;          /* 0x2280C: qch channel3 control */
        __RW uint32_t PORT1_QCH_ERR_CFG;       /* 0x22810: qch clear */
        __R  uint8_t  RESERVED14[2028];        /* 0x22814 - 0x22FFF: Reserved */
        __RW uint32_t TSN_SHAPER_TAS_CRSR;     /* 0x23000:  */
        __RW uint32_t TSN_SHAPER_TAS_ACYCLETM; /* 0x23004:  */
        __RW uint32_t TSN_SHAPER_TAS_ABASETM_L;/* 0x23008:  */
        __RW uint32_t TSN_SHAPER_TAS_ABASETM_H;/* 0x2300C:  */
        __RW uint32_t TSN_SHAPER_TAS_LISTLEN;  /* 0x23010:  */
        __R  uint32_t TSN_SHAPER_TAS_OCYCLETM; /* 0x23014:  */
        __R  uint32_t TSN_SHAPER_TAS_OBASETM_L;/* 0x23018:  */
        __R  uint32_t TSN_SHAPER_TAS_OBASETM_H;/* 0x2301C:  */
        __RW uint32_t MXTK[8];                 /* 0x23020 - 0x2303C:  */
        __RW uint32_t TXOV[8];                 /* 0x23040 - 0x2305C:  */
        __R  uint8_t  RESERVED15[1952];        /* 0x23060 - 0x237FF: Reserved */
        struct {
            __RW uint32_t TSN_SHAPER_ACLIST_ENTRY0_L; /* 0x23800:  */
            __RW uint32_t TSN_SHAPER_ACLIST_ENTRY0_H; /* 0x23804:  */
        } SHACL[256];
        __R  uint8_t  RESERVED16[45056];       /* 0x24000 - 0x2EFFF: Reserved */
        __R  uint32_t TSN_EP_VER;              /* 0x2F000:  */
        __RW uint32_t TSN_EP_CTRL;             /* 0x2F004:  */
        __R  uint8_t  RESERVED17[8];           /* 0x2F008 - 0x2F00F: Reserved */
        __RW uint32_t TSN_EP_TXUF;             /* 0x2F010:  */
        __R  uint32_t TSN_EP_IPCFG;            /* 0x2F014:  */
        __R  uint8_t  RESERVED18[8];           /* 0x2F018 - 0x2F01F: Reserved */
        __R  uint32_t TSN_EP_TSF_D0;           /* 0x2F020:  */
        __R  uint32_t TSN_EP_TSF_D1;           /* 0x2F024:  */
        __R  uint32_t TSN_EP_TSF_D2;           /* 0x2F028:  */
        __RW uint32_t TSN_EP_TSF_SR;           /* 0x2F02C:  */
        __RW uint32_t TSN_EP_MMS_CTRL;         /* 0x2F030:  */
        __R  uint32_t TSN_EP_MMS_STS;          /* 0x2F034:  */
        __RW uint32_t TSN_EP_MMS_VTIME;        /* 0x2F038:  */
        __RW uint32_t TSN_EP_MMS_STAT;         /* 0x2F03C:  */
        __W  uint32_t TSN_EP_PTP_UPTM_NS;      /* 0x2F040:  */
        __W  uint32_t TSN_EP_PTP_UPTM_S;       /* 0x2F044:  */
        __R  uint32_t TSN_EP_PTP_SR;           /* 0x2F048:  */
        __R  uint8_t  RESERVED19[4020];        /* 0x2F04C - 0x2FFFF: Reserved */
        __RW uint32_t SW_CTRL_PORT_MAIN_TAGGING; /* 0x30000: PVID Tagging Register */
        __RW uint32_t SW_CTRL_PORT_MAIN_ENNABLE; /* 0x30004: Port Module Enable Register */
        __R  uint8_t  RESERVED20[8184];        /* 0x30008 - 0x31FFF: Reserved */
        __RW uint32_t SW_CTRL_EGRESS_ECSR_QDROP; /* 0x32000:  */
        __R  uint8_t  RESERVED21[8188];        /* 0x32004 - 0x33FFF: Reserved */
        struct {
            __R  uint32_t SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_CNT_BYTE; /* 0x34000:  */
            __R  uint32_t SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS; /* 0x34004:  */
            __RW uint32_t SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG; /* 0x34008:  */
            __RW uint32_t SW_CTRL_IGRESS_RX_FDFIFO_E_IE_ERROR_FLAG; /* 0x3400C:  */
            __RW uint32_t SW_CTRL_IGRESS_RX_FDFIFO_E_IN_CONFIG; /* 0x34010:  */
            __RW uint32_t SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG; /* 0x34014:  */
            __W  uint32_t SW_CTRL_IGRESS_RX_FDFIFO_E_RESET; /* 0x34018:  */
            __R  uint32_t SW_CTRL_IGRESS_RX_FDFIFO_E_PARAM; /* 0x3401C:  */
            __RW uint32_t SW_CTRL_IGRESS_RX_FDFIFO_E_STRFWD; /* 0x34020:  */
            __RW uint32_t SW_CTRL_IGRESS_RX_FDFIFO_E_PORTMASK; /* 0x34024:  */
            __RW uint32_t SW_CTRL_IGRESS_RX_FDFIFO_E_MIRROR; /* 0x34028:  */
            __RW uint32_t SW_CTRL_IGRESS_RX_FDFIFO_E_MIRROR_TX; /* 0x3402C:  */
            __R  uint8_t  RESERVED0[208];      /* 0x34030 - 0x340FF: Reserved */
        } RXFIFO[2];
        __R  uint8_t  RESERVED22[15876];       /* 0x34200 - 0x38003: Reserved */
        __RW uint32_t SW_CTRL_MONITOR_CTRL;    /* 0x38004:  */
        __W  uint32_t SW_CTRL_MONITOR_RESET;   /* 0x38008:  */
        __R  uint32_t SW_CTRL_MONITOR_PARAM;   /* 0x3800C:  */
        __R  uint32_t MONITOR_TX_COUNTER_TX_FGOOD; /* 0x38010:  */
        __R  uint8_t  RESERVED23[4];           /* 0x38014 - 0x38017: Reserved */
        __R  uint32_t MONITOR_TX_COUNTER_TX_FERROR; /* 0x38018:  */
        __R  uint8_t  RESERVED24[4];           /* 0x3801C - 0x3801F: Reserved */
        __R  uint32_t MONITOR_TX_COUNTER_TX_DROP_OVFL; /* 0x38020:  */
        __R  uint8_t  RESERVED25[28];          /* 0x38024 - 0x3803F: Reserved */
        __R  uint32_t MONITOR_RX_COUNTER_RX_FGOOD; /* 0x38040:  */
        __R  uint8_t  RESERVED26[4];           /* 0x38044 - 0x38047: Reserved */
        __R  uint32_t MONITOR_RX_COUNTER_RX_FERROR; /* 0x38048:  */
        __R  uint8_t  RESERVED27[4];           /* 0x3804C - 0x3804F: Reserved */
        __R  uint32_t MONITOR_RX_COUNTER_RX_KNOWN; /* 0x38050:  */
        __R  uint8_t  RESERVED28[4];           /* 0x38054 - 0x38057: Reserved */
        __R  uint32_t MONITOR_RX_COUNTER_RX_UNKNOWN; /* 0x38058:  */
        __R  uint8_t  RESERVED29[4];           /* 0x3805C - 0x3805F: Reserved */
        __R  uint32_t MONITOR_RX_COUNTER_RX_UC;/* 0x38060:  */
        __R  uint8_t  RESERVED30[4];           /* 0x38064 - 0x38067: Reserved */
        __R  uint32_t MONITOR_RX_COUNTER_RX_INTERN; /* 0x38068:  */
        __R  uint8_t  RESERVED31[4];           /* 0x3806C - 0x3806F: Reserved */
        __R  uint32_t MONITOR_RX_COUNTER_RX_BC;/* 0x38070:  */
        __R  uint8_t  RESERVED32[4];           /* 0x38074 - 0x38077: Reserved */
        __R  uint32_t MONITOR_RX_COUNTER_RX_MULTI; /* 0x38078:  */
        __R  uint8_t  RESERVED33[4];           /* 0x3807C - 0x3807F: Reserved */
        __R  uint32_t MONITOR_RX_COUNTER_RX_VLAN; /* 0x38080:  */
        __R  uint8_t  RESERVED34[4];           /* 0x38084 - 0x38087: Reserved */
        __R  uint32_t MONITOR_RX_COUNTER_RX_DROP_OVFL; /* 0x38088:  */
        __R  uint8_t  RESERVED35[4];           /* 0x3808C - 0x3808F: Reserved */
        __R  uint32_t MONITOR_RX_COUNTER_RX_DROP_LU; /* 0x38090:  */
        __R  uint8_t  RESERVED36[4];           /* 0x38094 - 0x38097: Reserved */
        __R  uint32_t MONITOR_RX_COUNTER_RX_DROP_ERR; /* 0x38098:  */
        __R  uint8_t  RESERVED37[4];           /* 0x3809C - 0x3809F: Reserved */
        __R  uint32_t MONITOR_RX_COUNTER_RX_DROP_VLAN; /* 0x380A0:  */
        __R  uint8_t  RESERVED38[4];           /* 0x380A4 - 0x380A7: Reserved */
        __R  uint32_t MONITOR_RX_COUNTER_RX_FPE_FGOOD; /* 0x380A8:  */
        __R  uint8_t  RESERVED39[16212];       /* 0x380AC - 0x3BFFF: Reserved */
        __RW uint32_t GPR_CTRL0;               /* 0x3C000: control register0 */
        __R  uint8_t  RESERVED40[4];           /* 0x3C004 - 0x3C007: Reserved */
        __RW uint32_t GPR_CTRL2;               /* 0x3C008: control register2 */
        __R  uint8_t  RESERVED41[16372];       /* 0x3C00C - 0x3FFFF: Reserved */
    } TSNPORT[3];
} TSW_Type;


/* Bitfield definition for register: LU_MAIN_CTRL */
/*
 * BYP_EN (R/W)
 *
 * MAC lookup bypass
 */
#define TSW_LU_MAIN_CTRL_BYP_EN_MASK (0x1U)
#define TSW_LU_MAIN_CTRL_BYP_EN_SHIFT (0U)
#define TSW_LU_MAIN_CTRL_BYP_EN_SET(x) (((uint32_t)(x) << TSW_LU_MAIN_CTRL_BYP_EN_SHIFT) & TSW_LU_MAIN_CTRL_BYP_EN_MASK)
#define TSW_LU_MAIN_CTRL_BYP_EN_GET(x) (((uint32_t)(x) & TSW_LU_MAIN_CTRL_BYP_EN_MASK) >> TSW_LU_MAIN_CTRL_BYP_EN_SHIFT)

/* Bitfield definition for register: LU_MAIN_HITMEM */
/*
 * CAMMEMCLR (R/W)
 *
 * clear the cam memory
 */
#define TSW_LU_MAIN_HITMEM_CAMMEMCLR_MASK (0x2U)
#define TSW_LU_MAIN_HITMEM_CAMMEMCLR_SHIFT (1U)
#define TSW_LU_MAIN_HITMEM_CAMMEMCLR_SET(x) (((uint32_t)(x) << TSW_LU_MAIN_HITMEM_CAMMEMCLR_SHIFT) & TSW_LU_MAIN_HITMEM_CAMMEMCLR_MASK)
#define TSW_LU_MAIN_HITMEM_CAMMEMCLR_GET(x) (((uint32_t)(x) & TSW_LU_MAIN_HITMEM_CAMMEMCLR_MASK) >> TSW_LU_MAIN_HITMEM_CAMMEMCLR_SHIFT)

/*
 * HITMEMCLR (R/W)
 *
 * clears the hit memory
 */
#define TSW_LU_MAIN_HITMEM_HITMEMCLR_MASK (0x1U)
#define TSW_LU_MAIN_HITMEM_HITMEMCLR_SHIFT (0U)
#define TSW_LU_MAIN_HITMEM_HITMEMCLR_SET(x) (((uint32_t)(x) << TSW_LU_MAIN_HITMEM_HITMEMCLR_SHIFT) & TSW_LU_MAIN_HITMEM_HITMEMCLR_MASK)
#define TSW_LU_MAIN_HITMEM_HITMEMCLR_GET(x) (((uint32_t)(x) & TSW_LU_MAIN_HITMEM_HITMEMCLR_MASK) >> TSW_LU_MAIN_HITMEM_HITMEMCLR_SHIFT)

/* Bitfield definition for register: LU_MAIN_PARAM */
/*
 * NSTR (RO)
 *
 * number of supported streams
 */
#define TSW_LU_MAIN_PARAM_NSTR_MASK (0xFF00U)
#define TSW_LU_MAIN_PARAM_NSTR_SHIFT (8U)
#define TSW_LU_MAIN_PARAM_NSTR_GET(x) (((uint32_t)(x) & TSW_LU_MAIN_PARAM_NSTR_MASK) >> TSW_LU_MAIN_PARAM_NSTR_SHIFT)

/*
 * ADDRW_ENTRY (RO)
 *
 * bit width of entry address vector
 */
#define TSW_LU_MAIN_PARAM_ADDRW_ENTRY_MASK (0xFFU)
#define TSW_LU_MAIN_PARAM_ADDRW_ENTRY_SHIFT (0U)
#define TSW_LU_MAIN_PARAM_ADDRW_ENTRY_GET(x) (((uint32_t)(x) & TSW_LU_MAIN_PARAM_ADDRW_ENTRY_MASK) >> TSW_LU_MAIN_PARAM_ADDRW_ENTRY_SHIFT)

/* Bitfield definition for register: LU_MAIN_BYPASS */
/*
 * HIT (R/W)
 *
 * set hit bit to frame, only for debugging
 */
#define TSW_LU_MAIN_BYPASS_HIT_MASK (0x1000000UL)
#define TSW_LU_MAIN_BYPASS_HIT_SHIFT (24U)
#define TSW_LU_MAIN_BYPASS_HIT_SET(x) (((uint32_t)(x) << TSW_LU_MAIN_BYPASS_HIT_SHIFT) & TSW_LU_MAIN_BYPASS_HIT_MASK)
#define TSW_LU_MAIN_BYPASS_HIT_GET(x) (((uint32_t)(x) & TSW_LU_MAIN_BYPASS_HIT_MASK) >> TSW_LU_MAIN_BYPASS_HIT_SHIFT)

/*
 * UTAG (R/W)
 *
 * set internal user tag field
 */
#define TSW_LU_MAIN_BYPASS_UTAG_MASK (0xE00000UL)
#define TSW_LU_MAIN_BYPASS_UTAG_SHIFT (21U)
#define TSW_LU_MAIN_BYPASS_UTAG_SET(x) (((uint32_t)(x) << TSW_LU_MAIN_BYPASS_UTAG_SHIFT) & TSW_LU_MAIN_BYPASS_UTAG_MASK)
#define TSW_LU_MAIN_BYPASS_UTAG_GET(x) (((uint32_t)(x) & TSW_LU_MAIN_BYPASS_UTAG_MASK) >> TSW_LU_MAIN_BYPASS_UTAG_SHIFT)

/*
 * HIT_VLAN (R/W)
 *
 * mark frame to be vlan-tagged
 */
#define TSW_LU_MAIN_BYPASS_HIT_VLAN_MASK (0x100000UL)
#define TSW_LU_MAIN_BYPASS_HIT_VLAN_SHIFT (20U)
#define TSW_LU_MAIN_BYPASS_HIT_VLAN_SET(x) (((uint32_t)(x) << TSW_LU_MAIN_BYPASS_HIT_VLAN_SHIFT) & TSW_LU_MAIN_BYPASS_HIT_VLAN_MASK)
#define TSW_LU_MAIN_BYPASS_HIT_VLAN_GET(x) (((uint32_t)(x) & TSW_LU_MAIN_BYPASS_HIT_VLAN_MASK) >> TSW_LU_MAIN_BYPASS_HIT_VLAN_SHIFT)

/*
 * DROP (R/W)
 *
 * mark frame to be dropped
 */
#define TSW_LU_MAIN_BYPASS_DROP_MASK (0x80000UL)
#define TSW_LU_MAIN_BYPASS_DROP_SHIFT (19U)
#define TSW_LU_MAIN_BYPASS_DROP_SET(x) (((uint32_t)(x) << TSW_LU_MAIN_BYPASS_DROP_SHIFT) & TSW_LU_MAIN_BYPASS_DROP_MASK)
#define TSW_LU_MAIN_BYPASS_DROP_GET(x) (((uint32_t)(x) & TSW_LU_MAIN_BYPASS_DROP_MASK) >> TSW_LU_MAIN_BYPASS_DROP_SHIFT)

/*
 * QUEUE (R/W)
 *
 * number of configured buffer depth
 */
#define TSW_LU_MAIN_BYPASS_QUEUE_MASK (0x70000UL)
#define TSW_LU_MAIN_BYPASS_QUEUE_SHIFT (16U)
#define TSW_LU_MAIN_BYPASS_QUEUE_SET(x) (((uint32_t)(x) << TSW_LU_MAIN_BYPASS_QUEUE_SHIFT) & TSW_LU_MAIN_BYPASS_QUEUE_MASK)
#define TSW_LU_MAIN_BYPASS_QUEUE_GET(x) (((uint32_t)(x) & TSW_LU_MAIN_BYPASS_QUEUE_MASK) >> TSW_LU_MAIN_BYPASS_QUEUE_SHIFT)

/*
 * DEST (R/W)
 *
 * target destination ports of frame
 */
#define TSW_LU_MAIN_BYPASS_DEST_MASK (0xFFFFU)
#define TSW_LU_MAIN_BYPASS_DEST_SHIFT (0U)
#define TSW_LU_MAIN_BYPASS_DEST_SET(x) (((uint32_t)(x) << TSW_LU_MAIN_BYPASS_DEST_SHIFT) & TSW_LU_MAIN_BYPASS_DEST_MASK)
#define TSW_LU_MAIN_BYPASS_DEST_GET(x) (((uint32_t)(x) & TSW_LU_MAIN_BYPASS_DEST_MASK) >> TSW_LU_MAIN_BYPASS_DEST_SHIFT)

/* Bitfield definition for register: LU_MAIN_PCP_REMAP */
/*
 * PCP7 (R/W)
 *
 * queue value for PCP=7
 */
#define TSW_LU_MAIN_PCP_REMAP_PCP7_MASK (0xE00000UL)
#define TSW_LU_MAIN_PCP_REMAP_PCP7_SHIFT (21U)
#define TSW_LU_MAIN_PCP_REMAP_PCP7_SET(x) (((uint32_t)(x) << TSW_LU_MAIN_PCP_REMAP_PCP7_SHIFT) & TSW_LU_MAIN_PCP_REMAP_PCP7_MASK)
#define TSW_LU_MAIN_PCP_REMAP_PCP7_GET(x) (((uint32_t)(x) & TSW_LU_MAIN_PCP_REMAP_PCP7_MASK) >> TSW_LU_MAIN_PCP_REMAP_PCP7_SHIFT)

/*
 * PCP6 (R/W)
 *
 * queue value for PCP=6
 */
#define TSW_LU_MAIN_PCP_REMAP_PCP6_MASK (0x1C0000UL)
#define TSW_LU_MAIN_PCP_REMAP_PCP6_SHIFT (18U)
#define TSW_LU_MAIN_PCP_REMAP_PCP6_SET(x) (((uint32_t)(x) << TSW_LU_MAIN_PCP_REMAP_PCP6_SHIFT) & TSW_LU_MAIN_PCP_REMAP_PCP6_MASK)
#define TSW_LU_MAIN_PCP_REMAP_PCP6_GET(x) (((uint32_t)(x) & TSW_LU_MAIN_PCP_REMAP_PCP6_MASK) >> TSW_LU_MAIN_PCP_REMAP_PCP6_SHIFT)

/*
 * PCP5 (R/W)
 *
 * queue value for PCP=5
 */
#define TSW_LU_MAIN_PCP_REMAP_PCP5_MASK (0x38000UL)
#define TSW_LU_MAIN_PCP_REMAP_PCP5_SHIFT (15U)
#define TSW_LU_MAIN_PCP_REMAP_PCP5_SET(x) (((uint32_t)(x) << TSW_LU_MAIN_PCP_REMAP_PCP5_SHIFT) & TSW_LU_MAIN_PCP_REMAP_PCP5_MASK)
#define TSW_LU_MAIN_PCP_REMAP_PCP5_GET(x) (((uint32_t)(x) & TSW_LU_MAIN_PCP_REMAP_PCP5_MASK) >> TSW_LU_MAIN_PCP_REMAP_PCP5_SHIFT)

/*
 * PCP4 (R/W)
 *
 * queue value for PCP=4
 */
#define TSW_LU_MAIN_PCP_REMAP_PCP4_MASK (0x7000U)
#define TSW_LU_MAIN_PCP_REMAP_PCP4_SHIFT (12U)
#define TSW_LU_MAIN_PCP_REMAP_PCP4_SET(x) (((uint32_t)(x) << TSW_LU_MAIN_PCP_REMAP_PCP4_SHIFT) & TSW_LU_MAIN_PCP_REMAP_PCP4_MASK)
#define TSW_LU_MAIN_PCP_REMAP_PCP4_GET(x) (((uint32_t)(x) & TSW_LU_MAIN_PCP_REMAP_PCP4_MASK) >> TSW_LU_MAIN_PCP_REMAP_PCP4_SHIFT)

/*
 * PCP3 (R/W)
 *
 * queue value for PCP=3
 */
#define TSW_LU_MAIN_PCP_REMAP_PCP3_MASK (0xE00U)
#define TSW_LU_MAIN_PCP_REMAP_PCP3_SHIFT (9U)
#define TSW_LU_MAIN_PCP_REMAP_PCP3_SET(x) (((uint32_t)(x) << TSW_LU_MAIN_PCP_REMAP_PCP3_SHIFT) & TSW_LU_MAIN_PCP_REMAP_PCP3_MASK)
#define TSW_LU_MAIN_PCP_REMAP_PCP3_GET(x) (((uint32_t)(x) & TSW_LU_MAIN_PCP_REMAP_PCP3_MASK) >> TSW_LU_MAIN_PCP_REMAP_PCP3_SHIFT)

/*
 * PCP2 (R/W)
 *
 * queue value for PCP=2
 */
#define TSW_LU_MAIN_PCP_REMAP_PCP2_MASK (0x1C0U)
#define TSW_LU_MAIN_PCP_REMAP_PCP2_SHIFT (6U)
#define TSW_LU_MAIN_PCP_REMAP_PCP2_SET(x) (((uint32_t)(x) << TSW_LU_MAIN_PCP_REMAP_PCP2_SHIFT) & TSW_LU_MAIN_PCP_REMAP_PCP2_MASK)
#define TSW_LU_MAIN_PCP_REMAP_PCP2_GET(x) (((uint32_t)(x) & TSW_LU_MAIN_PCP_REMAP_PCP2_MASK) >> TSW_LU_MAIN_PCP_REMAP_PCP2_SHIFT)

/*
 * PCP1 (R/W)
 *
 * queue value for PCP=1
 */
#define TSW_LU_MAIN_PCP_REMAP_PCP1_MASK (0x38U)
#define TSW_LU_MAIN_PCP_REMAP_PCP1_SHIFT (3U)
#define TSW_LU_MAIN_PCP_REMAP_PCP1_SET(x) (((uint32_t)(x) << TSW_LU_MAIN_PCP_REMAP_PCP1_SHIFT) & TSW_LU_MAIN_PCP_REMAP_PCP1_MASK)
#define TSW_LU_MAIN_PCP_REMAP_PCP1_GET(x) (((uint32_t)(x) & TSW_LU_MAIN_PCP_REMAP_PCP1_MASK) >> TSW_LU_MAIN_PCP_REMAP_PCP1_SHIFT)

/*
 * PCP0 (R/W)
 *
 * queue value for PCP=0
 */
#define TSW_LU_MAIN_PCP_REMAP_PCP0_MASK (0x7U)
#define TSW_LU_MAIN_PCP_REMAP_PCP0_SHIFT (0U)
#define TSW_LU_MAIN_PCP_REMAP_PCP0_SET(x) (((uint32_t)(x) << TSW_LU_MAIN_PCP_REMAP_PCP0_SHIFT) & TSW_LU_MAIN_PCP_REMAP_PCP0_MASK)
#define TSW_LU_MAIN_PCP_REMAP_PCP0_GET(x) (((uint32_t)(x) & TSW_LU_MAIN_PCP_REMAP_PCP0_MASK) >> TSW_LU_MAIN_PCP_REMAP_PCP0_SHIFT)

/* Bitfield definition for register: LU_MAIN_VERSION */
/*
 * VER_HI (RO)
 *
 * major version
 */
#define TSW_LU_MAIN_VERSION_VER_HI_MASK (0xFF000000UL)
#define TSW_LU_MAIN_VERSION_VER_HI_SHIFT (24U)
#define TSW_LU_MAIN_VERSION_VER_HI_GET(x) (((uint32_t)(x) & TSW_LU_MAIN_VERSION_VER_HI_MASK) >> TSW_LU_MAIN_VERSION_VER_HI_SHIFT)

/*
 * VER_LO (RO)
 *
 * minor version
 */
#define TSW_LU_MAIN_VERSION_VER_LO_MASK (0xFF0000UL)
#define TSW_LU_MAIN_VERSION_VER_LO_SHIFT (16U)
#define TSW_LU_MAIN_VERSION_VER_LO_GET(x) (((uint32_t)(x) & TSW_LU_MAIN_VERSION_VER_LO_MASK) >> TSW_LU_MAIN_VERSION_VER_LO_SHIFT)

/*
 * VER_REV (RO)
 *
 * revision number
 */
#define TSW_LU_MAIN_VERSION_VER_REV_MASK (0xFFU)
#define TSW_LU_MAIN_VERSION_VER_REV_SHIFT (0U)
#define TSW_LU_MAIN_VERSION_VER_REV_GET(x) (((uint32_t)(x) & TSW_LU_MAIN_VERSION_VER_REV_MASK) >> TSW_LU_MAIN_VERSION_VER_REV_SHIFT)

/* Bitfield definition for register: LU_MAIN_INTF_ACTION */
/*
 * UTAG (R/W)
 *
 * TSN user sideband information from ALMEM
 */
#define TSW_LU_MAIN_INTF_ACTION_UTAG_MASK (0x1C00000UL)
#define TSW_LU_MAIN_INTF_ACTION_UTAG_SHIFT (22U)
#define TSW_LU_MAIN_INTF_ACTION_UTAG_SET(x) (((uint32_t)(x) << TSW_LU_MAIN_INTF_ACTION_UTAG_SHIFT) & TSW_LU_MAIN_INTF_ACTION_UTAG_MASK)
#define TSW_LU_MAIN_INTF_ACTION_UTAG_GET(x) (((uint32_t)(x) & TSW_LU_MAIN_INTF_ACTION_UTAG_MASK) >> TSW_LU_MAIN_INTF_ACTION_UTAG_SHIFT)

/*
 * QSEL (R/W)
 *
 * Define the traffic queue selection:
 * 00 – use PCP field of VLAN, untagged frames use PCP of PVID
 * 01 – use PCP field with global remapping list
 * 10 – reserved
 * 11 – use value QUEUE of Action List
 */
#define TSW_LU_MAIN_INTF_ACTION_QSEL_MASK (0x300000UL)
#define TSW_LU_MAIN_INTF_ACTION_QSEL_SHIFT (20U)
#define TSW_LU_MAIN_INTF_ACTION_QSEL_SET(x) (((uint32_t)(x) << TSW_LU_MAIN_INTF_ACTION_QSEL_SHIFT) & TSW_LU_MAIN_INTF_ACTION_QSEL_MASK)
#define TSW_LU_MAIN_INTF_ACTION_QSEL_GET(x) (((uint32_t)(x) & TSW_LU_MAIN_INTF_ACTION_QSEL_MASK) >> TSW_LU_MAIN_INTF_ACTION_QSEL_SHIFT)

/*
 * DROP (R/W)
 *
 * 1 if frame should be dropped.
 */
#define TSW_LU_MAIN_INTF_ACTION_DROP_MASK (0x80000UL)
#define TSW_LU_MAIN_INTF_ACTION_DROP_SHIFT (19U)
#define TSW_LU_MAIN_INTF_ACTION_DROP_SET(x) (((uint32_t)(x) << TSW_LU_MAIN_INTF_ACTION_DROP_SHIFT) & TSW_LU_MAIN_INTF_ACTION_DROP_MASK)
#define TSW_LU_MAIN_INTF_ACTION_DROP_GET(x) (((uint32_t)(x) & TSW_LU_MAIN_INTF_ACTION_DROP_MASK) >> TSW_LU_MAIN_INTF_ACTION_DROP_SHIFT)

/*
 * QUEUE (R/W)
 *
 * Select the Priority Queue for TSN TX, only used if QSEL=11
 */
#define TSW_LU_MAIN_INTF_ACTION_QUEUE_MASK (0x70000UL)
#define TSW_LU_MAIN_INTF_ACTION_QUEUE_SHIFT (16U)
#define TSW_LU_MAIN_INTF_ACTION_QUEUE_SET(x) (((uint32_t)(x) << TSW_LU_MAIN_INTF_ACTION_QUEUE_SHIFT) & TSW_LU_MAIN_INTF_ACTION_QUEUE_MASK)
#define TSW_LU_MAIN_INTF_ACTION_QUEUE_GET(x) (((uint32_t)(x) & TSW_LU_MAIN_INTF_ACTION_QUEUE_MASK) >> TSW_LU_MAIN_INTF_ACTION_QUEUE_SHIFT)

/*
 * DEST (R/W)
 *
 * Select the destination ports of forwarded frame. It is coded in onehot/select way,
 * where 0 is always route to null. Every bit is mapped to a port.
 * 00000 – to null (frame to clear)
 * 00001 – to port 0 (CPU Port)
 * 00010 – to port 1
 * 00100 – to port 2
 * 01000 – to port 3
 */
#define TSW_LU_MAIN_INTF_ACTION_DEST_MASK (0xFFFFU)
#define TSW_LU_MAIN_INTF_ACTION_DEST_SHIFT (0U)
#define TSW_LU_MAIN_INTF_ACTION_DEST_SET(x) (((uint32_t)(x) << TSW_LU_MAIN_INTF_ACTION_DEST_SHIFT) & TSW_LU_MAIN_INTF_ACTION_DEST_MASK)
#define TSW_LU_MAIN_INTF_ACTION_DEST_GET(x) (((uint32_t)(x) & TSW_LU_MAIN_INTF_ACTION_DEST_MASK) >> TSW_LU_MAIN_INTF_ACTION_DEST_SHIFT)

/* Bitfield definition for register: LU_MAIN_BC_ACTION */
/*
 * UTAG (R/W)
 *
 * TSN user sideband information from ALMEM
 */
#define TSW_LU_MAIN_BC_ACTION_UTAG_MASK (0x1C00000UL)
#define TSW_LU_MAIN_BC_ACTION_UTAG_SHIFT (22U)
#define TSW_LU_MAIN_BC_ACTION_UTAG_SET(x) (((uint32_t)(x) << TSW_LU_MAIN_BC_ACTION_UTAG_SHIFT) & TSW_LU_MAIN_BC_ACTION_UTAG_MASK)
#define TSW_LU_MAIN_BC_ACTION_UTAG_GET(x) (((uint32_t)(x) & TSW_LU_MAIN_BC_ACTION_UTAG_MASK) >> TSW_LU_MAIN_BC_ACTION_UTAG_SHIFT)

/*
 * QSEL (R/W)
 *
 * Define the traffic queue selection:
 * 00 – use PCP field of VLAN, untagged frames use PCP of PVID
 * 01 – use PCP field with global remapping list
 * 10 – reserved
 * 11 – use value QUEUE of Action List
 */
#define TSW_LU_MAIN_BC_ACTION_QSEL_MASK (0x300000UL)
#define TSW_LU_MAIN_BC_ACTION_QSEL_SHIFT (20U)
#define TSW_LU_MAIN_BC_ACTION_QSEL_SET(x) (((uint32_t)(x) << TSW_LU_MAIN_BC_ACTION_QSEL_SHIFT) & TSW_LU_MAIN_BC_ACTION_QSEL_MASK)
#define TSW_LU_MAIN_BC_ACTION_QSEL_GET(x) (((uint32_t)(x) & TSW_LU_MAIN_BC_ACTION_QSEL_MASK) >> TSW_LU_MAIN_BC_ACTION_QSEL_SHIFT)

/*
 * DROP (R/W)
 *
 * 1 if frame should be dropped.
 */
#define TSW_LU_MAIN_BC_ACTION_DROP_MASK (0x80000UL)
#define TSW_LU_MAIN_BC_ACTION_DROP_SHIFT (19U)
#define TSW_LU_MAIN_BC_ACTION_DROP_SET(x) (((uint32_t)(x) << TSW_LU_MAIN_BC_ACTION_DROP_SHIFT) & TSW_LU_MAIN_BC_ACTION_DROP_MASK)
#define TSW_LU_MAIN_BC_ACTION_DROP_GET(x) (((uint32_t)(x) & TSW_LU_MAIN_BC_ACTION_DROP_MASK) >> TSW_LU_MAIN_BC_ACTION_DROP_SHIFT)

/*
 * QUEUE (R/W)
 *
 * Select the Priority Queue for TSN TX, only used if QSEL=11
 */
#define TSW_LU_MAIN_BC_ACTION_QUEUE_MASK (0x70000UL)
#define TSW_LU_MAIN_BC_ACTION_QUEUE_SHIFT (16U)
#define TSW_LU_MAIN_BC_ACTION_QUEUE_SET(x) (((uint32_t)(x) << TSW_LU_MAIN_BC_ACTION_QUEUE_SHIFT) & TSW_LU_MAIN_BC_ACTION_QUEUE_MASK)
#define TSW_LU_MAIN_BC_ACTION_QUEUE_GET(x) (((uint32_t)(x) & TSW_LU_MAIN_BC_ACTION_QUEUE_MASK) >> TSW_LU_MAIN_BC_ACTION_QUEUE_SHIFT)

/*
 * DEST (R/W)
 *
 * Select the destination ports of forwarded frame. It is coded in onehot/select way,
 * where 0 is always route to null. Every bit is mapped to a port.
 * 00000 – to null (frame to clear)
 * 00001 – to port 0 (CPU Port)
 * 00010 – to port 1
 * 00100 – to port 2
 * 01000 – to port 3
 */
#define TSW_LU_MAIN_BC_ACTION_DEST_MASK (0xFFFFU)
#define TSW_LU_MAIN_BC_ACTION_DEST_SHIFT (0U)
#define TSW_LU_MAIN_BC_ACTION_DEST_SET(x) (((uint32_t)(x) << TSW_LU_MAIN_BC_ACTION_DEST_SHIFT) & TSW_LU_MAIN_BC_ACTION_DEST_MASK)
#define TSW_LU_MAIN_BC_ACTION_DEST_GET(x) (((uint32_t)(x) & TSW_LU_MAIN_BC_ACTION_DEST_MASK) >> TSW_LU_MAIN_BC_ACTION_DEST_SHIFT)

/* Bitfield definition for register: LU_MAIN_NN_ACTION */
/*
 * UTAG (R/W)
 *
 * TSN user sideband information from ALMEM
 */
#define TSW_LU_MAIN_NN_ACTION_UTAG_MASK (0x1C00000UL)
#define TSW_LU_MAIN_NN_ACTION_UTAG_SHIFT (22U)
#define TSW_LU_MAIN_NN_ACTION_UTAG_SET(x) (((uint32_t)(x) << TSW_LU_MAIN_NN_ACTION_UTAG_SHIFT) & TSW_LU_MAIN_NN_ACTION_UTAG_MASK)
#define TSW_LU_MAIN_NN_ACTION_UTAG_GET(x) (((uint32_t)(x) & TSW_LU_MAIN_NN_ACTION_UTAG_MASK) >> TSW_LU_MAIN_NN_ACTION_UTAG_SHIFT)

/*
 * QSEL (R/W)
 *
 * Define the traffic queue selection:
 * 00 – use PCP field of VLAN, untagged frames use PCP of PVID
 * 01 – use PCP field with global remapping list
 * 10 – reserved
 * 11 – use value QUEUE of Action List
 */
#define TSW_LU_MAIN_NN_ACTION_QSEL_MASK (0x300000UL)
#define TSW_LU_MAIN_NN_ACTION_QSEL_SHIFT (20U)
#define TSW_LU_MAIN_NN_ACTION_QSEL_SET(x) (((uint32_t)(x) << TSW_LU_MAIN_NN_ACTION_QSEL_SHIFT) & TSW_LU_MAIN_NN_ACTION_QSEL_MASK)
#define TSW_LU_MAIN_NN_ACTION_QSEL_GET(x) (((uint32_t)(x) & TSW_LU_MAIN_NN_ACTION_QSEL_MASK) >> TSW_LU_MAIN_NN_ACTION_QSEL_SHIFT)

/*
 * DROP (R/W)
 *
 * 1 if frame should be dropped.
 */
#define TSW_LU_MAIN_NN_ACTION_DROP_MASK (0x80000UL)
#define TSW_LU_MAIN_NN_ACTION_DROP_SHIFT (19U)
#define TSW_LU_MAIN_NN_ACTION_DROP_SET(x) (((uint32_t)(x) << TSW_LU_MAIN_NN_ACTION_DROP_SHIFT) & TSW_LU_MAIN_NN_ACTION_DROP_MASK)
#define TSW_LU_MAIN_NN_ACTION_DROP_GET(x) (((uint32_t)(x) & TSW_LU_MAIN_NN_ACTION_DROP_MASK) >> TSW_LU_MAIN_NN_ACTION_DROP_SHIFT)

/*
 * QUEUE (R/W)
 *
 * Select the Priority Queue for TSN TX, only used if QSEL=11
 */
#define TSW_LU_MAIN_NN_ACTION_QUEUE_MASK (0x70000UL)
#define TSW_LU_MAIN_NN_ACTION_QUEUE_SHIFT (16U)
#define TSW_LU_MAIN_NN_ACTION_QUEUE_SET(x) (((uint32_t)(x) << TSW_LU_MAIN_NN_ACTION_QUEUE_SHIFT) & TSW_LU_MAIN_NN_ACTION_QUEUE_MASK)
#define TSW_LU_MAIN_NN_ACTION_QUEUE_GET(x) (((uint32_t)(x) & TSW_LU_MAIN_NN_ACTION_QUEUE_MASK) >> TSW_LU_MAIN_NN_ACTION_QUEUE_SHIFT)

/*
 * DEST (R/W)
 *
 * Select the destination ports of forwarded frame. It is coded in onehot/select way,
 * where 0 is always route to null. Every bit is mapped to a port.
 * 00000 – to null (frame to clear)
 * 00001 – to port 0 (CPU Port)
 * 00010 – to port 1
 * 00100 – to port 2
 * 01000 – to port 3
 */
#define TSW_LU_MAIN_NN_ACTION_DEST_MASK (0xFFFFU)
#define TSW_LU_MAIN_NN_ACTION_DEST_SHIFT (0U)
#define TSW_LU_MAIN_NN_ACTION_DEST_SET(x) (((uint32_t)(x) << TSW_LU_MAIN_NN_ACTION_DEST_SHIFT) & TSW_LU_MAIN_NN_ACTION_DEST_MASK)
#define TSW_LU_MAIN_NN_ACTION_DEST_GET(x) (((uint32_t)(x) & TSW_LU_MAIN_NN_ACTION_DEST_MASK) >> TSW_LU_MAIN_NN_ACTION_DEST_SHIFT)

/* Bitfield definition for register: APB2AXIS_CAM_STS */
/*
 * BUSY (RO)
 *
 * the controller is writing data and/or data is pending
 */
#define TSW_APB2AXIS_CAM_STS_BUSY_MASK (0x2U)
#define TSW_APB2AXIS_CAM_STS_BUSY_SHIFT (1U)
#define TSW_APB2AXIS_CAM_STS_BUSY_GET(x) (((uint32_t)(x) & TSW_APB2AXIS_CAM_STS_BUSY_MASK) >> TSW_APB2AXIS_CAM_STS_BUSY_SHIFT)

/*
 * RDY (RO)
 *
 * the new data is written to data register
 */
#define TSW_APB2AXIS_CAM_STS_RDY_MASK (0x1U)
#define TSW_APB2AXIS_CAM_STS_RDY_SHIFT (0U)
#define TSW_APB2AXIS_CAM_STS_RDY_GET(x) (((uint32_t)(x) & TSW_APB2AXIS_CAM_STS_RDY_MASK) >> TSW_APB2AXIS_CAM_STS_RDY_SHIFT)

/* Bitfield definition for register: APB2AXIS_CAM_REQ_CNT */
/*
 * WRCNT (RO)
 *
 * number of streams in queue
 */
#define TSW_APB2AXIS_CAM_REQ_CNT_WRCNT_MASK (0xFFU)
#define TSW_APB2AXIS_CAM_REQ_CNT_WRCNT_SHIFT (0U)
#define TSW_APB2AXIS_CAM_REQ_CNT_WRCNT_GET(x) (((uint32_t)(x) & TSW_APB2AXIS_CAM_REQ_CNT_WRCNT_MASK) >> TSW_APB2AXIS_CAM_REQ_CNT_WRCNT_SHIFT)

/* Bitfield definition for register: APB2AXIS_CAM_FILLSTS */
/*
 * FULL (RO)
 *
 * frame was dropped because the internal descriptor FIFO is full
 */
#define TSW_APB2AXIS_CAM_FILLSTS_FULL_MASK (0x10U)
#define TSW_APB2AXIS_CAM_FILLSTS_FULL_SHIFT (4U)
#define TSW_APB2AXIS_CAM_FILLSTS_FULL_GET(x) (((uint32_t)(x) & TSW_APB2AXIS_CAM_FILLSTS_FULL_MASK) >> TSW_APB2AXIS_CAM_FILLSTS_FULL_SHIFT)

/*
 * EMPTY (RO)
 *
 * FD FIFO failure, internal controller lost synchronization
 */
#define TSW_APB2AXIS_CAM_FILLSTS_EMPTY_MASK (0x1U)
#define TSW_APB2AXIS_CAM_FILLSTS_EMPTY_SHIFT (0U)
#define TSW_APB2AXIS_CAM_FILLSTS_EMPTY_GET(x) (((uint32_t)(x) & TSW_APB2AXIS_CAM_FILLSTS_EMPTY_MASK) >> TSW_APB2AXIS_CAM_FILLSTS_EMPTY_SHIFT)

/* Bitfield definition for register: APB2AXIS_CAM_RESET */
/*
 * RESET (W1C)
 *
 * resets controller and clears all pending stream data
 */
#define TSW_APB2AXIS_CAM_RESET_RESET_MASK (0x1U)
#define TSW_APB2AXIS_CAM_RESET_RESET_SHIFT (0U)
#define TSW_APB2AXIS_CAM_RESET_RESET_SET(x) (((uint32_t)(x) << TSW_APB2AXIS_CAM_RESET_RESET_SHIFT) & TSW_APB2AXIS_CAM_RESET_RESET_MASK)
#define TSW_APB2AXIS_CAM_RESET_RESET_GET(x) (((uint32_t)(x) & TSW_APB2AXIS_CAM_RESET_RESET_MASK) >> TSW_APB2AXIS_CAM_RESET_RESET_SHIFT)

/* Bitfield definition for register: APB2AXIS_CAM_PARAM */
/*
 * DEPTH (RO)
 *
 * number of configured buffer depth
 */
#define TSW_APB2AXIS_CAM_PARAM_DEPTH_MASK (0xFF00U)
#define TSW_APB2AXIS_CAM_PARAM_DEPTH_SHIFT (8U)
#define TSW_APB2AXIS_CAM_PARAM_DEPTH_GET(x) (((uint32_t)(x) & TSW_APB2AXIS_CAM_PARAM_DEPTH_MASK) >> TSW_APB2AXIS_CAM_PARAM_DEPTH_SHIFT)

/*
 * WORDLEN_BYTE (RO)
 *
 * number of configured 32bit words for this controller
 */
#define TSW_APB2AXIS_CAM_PARAM_WORDLEN_BYTE_MASK (0xFFU)
#define TSW_APB2AXIS_CAM_PARAM_WORDLEN_BYTE_SHIFT (0U)
#define TSW_APB2AXIS_CAM_PARAM_WORDLEN_BYTE_GET(x) (((uint32_t)(x) & TSW_APB2AXIS_CAM_PARAM_WORDLEN_BYTE_MASK) >> TSW_APB2AXIS_CAM_PARAM_WORDLEN_BYTE_SHIFT)

/* Bitfield definition for register: APB2AXI_CAM_REQDATA_0 */
/*
 * ENTRY_NUM (R/W)
 *
 * entry number
 */
#define TSW_APB2AXI_CAM_REQDATA_0_ENTRY_NUM_MASK (0xFFFF0000UL)
#define TSW_APB2AXI_CAM_REQDATA_0_ENTRY_NUM_SHIFT (16U)
#define TSW_APB2AXI_CAM_REQDATA_0_ENTRY_NUM_SET(x) (((uint32_t)(x) << TSW_APB2AXI_CAM_REQDATA_0_ENTRY_NUM_SHIFT) & TSW_APB2AXI_CAM_REQDATA_0_ENTRY_NUM_MASK)
#define TSW_APB2AXI_CAM_REQDATA_0_ENTRY_NUM_GET(x) (((uint32_t)(x) & TSW_APB2AXI_CAM_REQDATA_0_ENTRY_NUM_MASK) >> TSW_APB2AXI_CAM_REQDATA_0_ENTRY_NUM_SHIFT)

/*
 * TYPE (R/W)
 *
 * select between set, clear or clear all
 */
#define TSW_APB2AXI_CAM_REQDATA_0_TYPE_MASK (0x300U)
#define TSW_APB2AXI_CAM_REQDATA_0_TYPE_SHIFT (8U)
#define TSW_APB2AXI_CAM_REQDATA_0_TYPE_SET(x) (((uint32_t)(x) << TSW_APB2AXI_CAM_REQDATA_0_TYPE_SHIFT) & TSW_APB2AXI_CAM_REQDATA_0_TYPE_MASK)
#define TSW_APB2AXI_CAM_REQDATA_0_TYPE_GET(x) (((uint32_t)(x) & TSW_APB2AXI_CAM_REQDATA_0_TYPE_MASK) >> TSW_APB2AXI_CAM_REQDATA_0_TYPE_SHIFT)

/*
 * CH (R/W)
 *
 * CAM APB2AXIS channel selection
 */
#define TSW_APB2AXI_CAM_REQDATA_0_CH_MASK (0x1U)
#define TSW_APB2AXI_CAM_REQDATA_0_CH_SHIFT (0U)
#define TSW_APB2AXI_CAM_REQDATA_0_CH_SET(x) (((uint32_t)(x) << TSW_APB2AXI_CAM_REQDATA_0_CH_SHIFT) & TSW_APB2AXI_CAM_REQDATA_0_CH_MASK)
#define TSW_APB2AXI_CAM_REQDATA_0_CH_GET(x) (((uint32_t)(x) & TSW_APB2AXI_CAM_REQDATA_0_CH_MASK) >> TSW_APB2AXI_CAM_REQDATA_0_CH_SHIFT)

/* Bitfield definition for register: APB2AXI_CAM_REQDATA_1 */
/*
 * DESTMAC_LO_PORT_VEC (R/W)
 *
 * dest-mac[31:0] when CH=0；PORT_VEC when CH=1
 */
#define TSW_APB2AXI_CAM_REQDATA_1_DESTMAC_LO_PORT_VEC_MASK (0xFFFFFFFFUL)
#define TSW_APB2AXI_CAM_REQDATA_1_DESTMAC_LO_PORT_VEC_SHIFT (0U)
#define TSW_APB2AXI_CAM_REQDATA_1_DESTMAC_LO_PORT_VEC_SET(x) (((uint32_t)(x) << TSW_APB2AXI_CAM_REQDATA_1_DESTMAC_LO_PORT_VEC_SHIFT) & TSW_APB2AXI_CAM_REQDATA_1_DESTMAC_LO_PORT_VEC_MASK)
#define TSW_APB2AXI_CAM_REQDATA_1_DESTMAC_LO_PORT_VEC_GET(x) (((uint32_t)(x) & TSW_APB2AXI_CAM_REQDATA_1_DESTMAC_LO_PORT_VEC_MASK) >> TSW_APB2AXI_CAM_REQDATA_1_DESTMAC_LO_PORT_VEC_SHIFT)

/* Bitfield definition for register: APB2AXI_CAM_REQDATA_2 */
/*
 * VID (R/W)
 *
 * VLAN-ID value (12 bit) for the VLAN_ID table. Use the fefault VLAN-ID(VID=1), if setup an entry for non-VLAN traffic.
 */
#define TSW_APB2AXI_CAM_REQDATA_2_VID_MASK (0xFFF0000UL)
#define TSW_APB2AXI_CAM_REQDATA_2_VID_SHIFT (16U)
#define TSW_APB2AXI_CAM_REQDATA_2_VID_SET(x) (((uint32_t)(x) << TSW_APB2AXI_CAM_REQDATA_2_VID_SHIFT) & TSW_APB2AXI_CAM_REQDATA_2_VID_MASK)
#define TSW_APB2AXI_CAM_REQDATA_2_VID_GET(x) (((uint32_t)(x) & TSW_APB2AXI_CAM_REQDATA_2_VID_MASK) >> TSW_APB2AXI_CAM_REQDATA_2_VID_SHIFT)

/*
 * DESTMAC_HI (R/W)
 *
 * dest-mac[47:32] when CH=0
 */
#define TSW_APB2AXI_CAM_REQDATA_2_DESTMAC_HI_MASK (0xFFFFU)
#define TSW_APB2AXI_CAM_REQDATA_2_DESTMAC_HI_SHIFT (0U)
#define TSW_APB2AXI_CAM_REQDATA_2_DESTMAC_HI_SET(x) (((uint32_t)(x) << TSW_APB2AXI_CAM_REQDATA_2_DESTMAC_HI_SHIFT) & TSW_APB2AXI_CAM_REQDATA_2_DESTMAC_HI_MASK)
#define TSW_APB2AXI_CAM_REQDATA_2_DESTMAC_HI_GET(x) (((uint32_t)(x) & TSW_APB2AXI_CAM_REQDATA_2_DESTMAC_HI_MASK) >> TSW_APB2AXI_CAM_REQDATA_2_DESTMAC_HI_SHIFT)

/* Bitfield definition for register: APB2AXIS_ALMEM_STS */
/*
 * BUSY (RO)
 *
 * the controller is writing data and/or data is pending
 */
#define TSW_APB2AXIS_ALMEM_STS_BUSY_MASK (0x2U)
#define TSW_APB2AXIS_ALMEM_STS_BUSY_SHIFT (1U)
#define TSW_APB2AXIS_ALMEM_STS_BUSY_GET(x) (((uint32_t)(x) & TSW_APB2AXIS_ALMEM_STS_BUSY_MASK) >> TSW_APB2AXIS_ALMEM_STS_BUSY_SHIFT)

/*
 * RDY (RO)
 *
 * the new data is written to data register
 */
#define TSW_APB2AXIS_ALMEM_STS_RDY_MASK (0x1U)
#define TSW_APB2AXIS_ALMEM_STS_RDY_SHIFT (0U)
#define TSW_APB2AXIS_ALMEM_STS_RDY_GET(x) (((uint32_t)(x) & TSW_APB2AXIS_ALMEM_STS_RDY_MASK) >> TSW_APB2AXIS_ALMEM_STS_RDY_SHIFT)

/* Bitfield definition for register: APB2AXIS_ALMEM_REQ_CNT */
/*
 * WRCNT (RO)
 *
 * number of streams in queue
 */
#define TSW_APB2AXIS_ALMEM_REQ_CNT_WRCNT_MASK (0xFFU)
#define TSW_APB2AXIS_ALMEM_REQ_CNT_WRCNT_SHIFT (0U)
#define TSW_APB2AXIS_ALMEM_REQ_CNT_WRCNT_GET(x) (((uint32_t)(x) & TSW_APB2AXIS_ALMEM_REQ_CNT_WRCNT_MASK) >> TSW_APB2AXIS_ALMEM_REQ_CNT_WRCNT_SHIFT)

/* Bitfield definition for register: APB2AXIS_ALMEM_FILLSTS */
/*
 * FULL (RO)
 *
 * frame was dropped because the internal descriptor FIFO is full
 */
#define TSW_APB2AXIS_ALMEM_FILLSTS_FULL_MASK (0x10U)
#define TSW_APB2AXIS_ALMEM_FILLSTS_FULL_SHIFT (4U)
#define TSW_APB2AXIS_ALMEM_FILLSTS_FULL_GET(x) (((uint32_t)(x) & TSW_APB2AXIS_ALMEM_FILLSTS_FULL_MASK) >> TSW_APB2AXIS_ALMEM_FILLSTS_FULL_SHIFT)

/*
 * EMPTY (RO)
 *
 * FD FIFO failure, internal controller lost synchronization
 */
#define TSW_APB2AXIS_ALMEM_FILLSTS_EMPTY_MASK (0x1U)
#define TSW_APB2AXIS_ALMEM_FILLSTS_EMPTY_SHIFT (0U)
#define TSW_APB2AXIS_ALMEM_FILLSTS_EMPTY_GET(x) (((uint32_t)(x) & TSW_APB2AXIS_ALMEM_FILLSTS_EMPTY_MASK) >> TSW_APB2AXIS_ALMEM_FILLSTS_EMPTY_SHIFT)

/* Bitfield definition for register: APB2AXIS_ALMEM_RESET */
/*
 * RESET (W1C)
 *
 * resets controller and clears all pending stream data
 */
#define TSW_APB2AXIS_ALMEM_RESET_RESET_MASK (0x1U)
#define TSW_APB2AXIS_ALMEM_RESET_RESET_SHIFT (0U)
#define TSW_APB2AXIS_ALMEM_RESET_RESET_SET(x) (((uint32_t)(x) << TSW_APB2AXIS_ALMEM_RESET_RESET_SHIFT) & TSW_APB2AXIS_ALMEM_RESET_RESET_MASK)
#define TSW_APB2AXIS_ALMEM_RESET_RESET_GET(x) (((uint32_t)(x) & TSW_APB2AXIS_ALMEM_RESET_RESET_MASK) >> TSW_APB2AXIS_ALMEM_RESET_RESET_SHIFT)

/* Bitfield definition for register: APB2AXIS_ALMEM_PARAM */
/*
 * DEPTH (RO)
 *
 * number of configured buffer depth
 */
#define TSW_APB2AXIS_ALMEM_PARAM_DEPTH_MASK (0xFF00U)
#define TSW_APB2AXIS_ALMEM_PARAM_DEPTH_SHIFT (8U)
#define TSW_APB2AXIS_ALMEM_PARAM_DEPTH_GET(x) (((uint32_t)(x) & TSW_APB2AXIS_ALMEM_PARAM_DEPTH_MASK) >> TSW_APB2AXIS_ALMEM_PARAM_DEPTH_SHIFT)

/*
 * WORDLEN_BYTE (RO)
 *
 * number of configured 32bit words for this controller
 */
#define TSW_APB2AXIS_ALMEM_PARAM_WORDLEN_BYTE_MASK (0xFFU)
#define TSW_APB2AXIS_ALMEM_PARAM_WORDLEN_BYTE_SHIFT (0U)
#define TSW_APB2AXIS_ALMEM_PARAM_WORDLEN_BYTE_GET(x) (((uint32_t)(x) & TSW_APB2AXIS_ALMEM_PARAM_WORDLEN_BYTE_MASK) >> TSW_APB2AXIS_ALMEM_PARAM_WORDLEN_BYTE_SHIFT)

/* Bitfield definition for register: APB2AXIS_ALMEM_REQDATA_0 */
/*
 * UTAG (R/W)
 *
 * user sideband information
 */
#define TSW_APB2AXIS_ALMEM_REQDATA_0_UTAG_MASK (0x1C00000UL)
#define TSW_APB2AXIS_ALMEM_REQDATA_0_UTAG_SHIFT (22U)
#define TSW_APB2AXIS_ALMEM_REQDATA_0_UTAG_SET(x) (((uint32_t)(x) << TSW_APB2AXIS_ALMEM_REQDATA_0_UTAG_SHIFT) & TSW_APB2AXIS_ALMEM_REQDATA_0_UTAG_MASK)
#define TSW_APB2AXIS_ALMEM_REQDATA_0_UTAG_GET(x) (((uint32_t)(x) & TSW_APB2AXIS_ALMEM_REQDATA_0_UTAG_MASK) >> TSW_APB2AXIS_ALMEM_REQDATA_0_UTAG_SHIFT)

/*
 * QSEL (R/W)
 *
 * define the traffic queue selection
 */
#define TSW_APB2AXIS_ALMEM_REQDATA_0_QSEL_MASK (0x300000UL)
#define TSW_APB2AXIS_ALMEM_REQDATA_0_QSEL_SHIFT (20U)
#define TSW_APB2AXIS_ALMEM_REQDATA_0_QSEL_SET(x) (((uint32_t)(x) << TSW_APB2AXIS_ALMEM_REQDATA_0_QSEL_SHIFT) & TSW_APB2AXIS_ALMEM_REQDATA_0_QSEL_MASK)
#define TSW_APB2AXIS_ALMEM_REQDATA_0_QSEL_GET(x) (((uint32_t)(x) & TSW_APB2AXIS_ALMEM_REQDATA_0_QSEL_MASK) >> TSW_APB2AXIS_ALMEM_REQDATA_0_QSEL_SHIFT)

/*
 * DROP (R/W)
 *
 * frame should dropped
 */
#define TSW_APB2AXIS_ALMEM_REQDATA_0_DROP_MASK (0x80000UL)
#define TSW_APB2AXIS_ALMEM_REQDATA_0_DROP_SHIFT (19U)
#define TSW_APB2AXIS_ALMEM_REQDATA_0_DROP_SET(x) (((uint32_t)(x) << TSW_APB2AXIS_ALMEM_REQDATA_0_DROP_SHIFT) & TSW_APB2AXIS_ALMEM_REQDATA_0_DROP_MASK)
#define TSW_APB2AXIS_ALMEM_REQDATA_0_DROP_GET(x) (((uint32_t)(x) & TSW_APB2AXIS_ALMEM_REQDATA_0_DROP_MASK) >> TSW_APB2AXIS_ALMEM_REQDATA_0_DROP_SHIFT)

/*
 * QUEUE (R/W)
 *
 * select the priority queue if qsel=11
 */
#define TSW_APB2AXIS_ALMEM_REQDATA_0_QUEUE_MASK (0x70000UL)
#define TSW_APB2AXIS_ALMEM_REQDATA_0_QUEUE_SHIFT (16U)
#define TSW_APB2AXIS_ALMEM_REQDATA_0_QUEUE_SET(x) (((uint32_t)(x) << TSW_APB2AXIS_ALMEM_REQDATA_0_QUEUE_SHIFT) & TSW_APB2AXIS_ALMEM_REQDATA_0_QUEUE_MASK)
#define TSW_APB2AXIS_ALMEM_REQDATA_0_QUEUE_GET(x) (((uint32_t)(x) & TSW_APB2AXIS_ALMEM_REQDATA_0_QUEUE_MASK) >> TSW_APB2AXIS_ALMEM_REQDATA_0_QUEUE_SHIFT)

/*
 * DEST (R/W)
 *
 * destination ports
 */
#define TSW_APB2AXIS_ALMEM_REQDATA_0_DEST_MASK (0xFFFFU)
#define TSW_APB2AXIS_ALMEM_REQDATA_0_DEST_SHIFT (0U)
#define TSW_APB2AXIS_ALMEM_REQDATA_0_DEST_SET(x) (((uint32_t)(x) << TSW_APB2AXIS_ALMEM_REQDATA_0_DEST_SHIFT) & TSW_APB2AXIS_ALMEM_REQDATA_0_DEST_MASK)
#define TSW_APB2AXIS_ALMEM_REQDATA_0_DEST_GET(x) (((uint32_t)(x) & TSW_APB2AXIS_ALMEM_REQDATA_0_DEST_MASK) >> TSW_APB2AXIS_ALMEM_REQDATA_0_DEST_SHIFT)

/* Bitfield definition for register: APB2AXIS_ALMEM_REQDATA_1 */
/*
 * WR_NRD (R/W)
 *
 * 1 for write and 0 for read
 */
#define TSW_APB2AXIS_ALMEM_REQDATA_1_WR_NRD_MASK (0x80000000UL)
#define TSW_APB2AXIS_ALMEM_REQDATA_1_WR_NRD_SHIFT (31U)
#define TSW_APB2AXIS_ALMEM_REQDATA_1_WR_NRD_SET(x) (((uint32_t)(x) << TSW_APB2AXIS_ALMEM_REQDATA_1_WR_NRD_SHIFT) & TSW_APB2AXIS_ALMEM_REQDATA_1_WR_NRD_MASK)
#define TSW_APB2AXIS_ALMEM_REQDATA_1_WR_NRD_GET(x) (((uint32_t)(x) & TSW_APB2AXIS_ALMEM_REQDATA_1_WR_NRD_MASK) >> TSW_APB2AXIS_ALMEM_REQDATA_1_WR_NRD_SHIFT)

/*
 * RESP (R/W)
 *
 * write response enable
 */
#define TSW_APB2AXIS_ALMEM_REQDATA_1_RESP_MASK (0x40000000UL)
#define TSW_APB2AXIS_ALMEM_REQDATA_1_RESP_SHIFT (30U)
#define TSW_APB2AXIS_ALMEM_REQDATA_1_RESP_SET(x) (((uint32_t)(x) << TSW_APB2AXIS_ALMEM_REQDATA_1_RESP_SHIFT) & TSW_APB2AXIS_ALMEM_REQDATA_1_RESP_MASK)
#define TSW_APB2AXIS_ALMEM_REQDATA_1_RESP_GET(x) (((uint32_t)(x) & TSW_APB2AXIS_ALMEM_REQDATA_1_RESP_MASK) >> TSW_APB2AXIS_ALMEM_REQDATA_1_RESP_SHIFT)

/*
 * ENTRY_NUM (R/W)
 *
 * define the entry number for reading and writing
 */
#define TSW_APB2AXIS_ALMEM_REQDATA_1_ENTRY_NUM_MASK (0xFFFFU)
#define TSW_APB2AXIS_ALMEM_REQDATA_1_ENTRY_NUM_SHIFT (0U)
#define TSW_APB2AXIS_ALMEM_REQDATA_1_ENTRY_NUM_SET(x) (((uint32_t)(x) << TSW_APB2AXIS_ALMEM_REQDATA_1_ENTRY_NUM_SHIFT) & TSW_APB2AXIS_ALMEM_REQDATA_1_ENTRY_NUM_MASK)
#define TSW_APB2AXIS_ALMEM_REQDATA_1_ENTRY_NUM_GET(x) (((uint32_t)(x) & TSW_APB2AXIS_ALMEM_REQDATA_1_ENTRY_NUM_MASK) >> TSW_APB2AXIS_ALMEM_REQDATA_1_ENTRY_NUM_SHIFT)

/* Bitfield definition for register: AXIS2APB_ALMEM_STS */
/*
 * BUSY (RO)
 *
 * the controller is writing data and/or data is pending
 */
#define TSW_AXIS2APB_ALMEM_STS_BUSY_MASK (0x2U)
#define TSW_AXIS2APB_ALMEM_STS_BUSY_SHIFT (1U)
#define TSW_AXIS2APB_ALMEM_STS_BUSY_GET(x) (((uint32_t)(x) & TSW_AXIS2APB_ALMEM_STS_BUSY_MASK) >> TSW_AXIS2APB_ALMEM_STS_BUSY_SHIFT)

/*
 * RDY (RO)
 *
 * the new data is written to data register
 */
#define TSW_AXIS2APB_ALMEM_STS_RDY_MASK (0x1U)
#define TSW_AXIS2APB_ALMEM_STS_RDY_SHIFT (0U)
#define TSW_AXIS2APB_ALMEM_STS_RDY_GET(x) (((uint32_t)(x) & TSW_AXIS2APB_ALMEM_STS_RDY_MASK) >> TSW_AXIS2APB_ALMEM_STS_RDY_SHIFT)

/* Bitfield definition for register: AXIS2APB_ALMEM_RESP_CNT */
/*
 * RDCNT (RO)
 *
 * number of streams in queue
 */
#define TSW_AXIS2APB_ALMEM_RESP_CNT_RDCNT_MASK (0xFFU)
#define TSW_AXIS2APB_ALMEM_RESP_CNT_RDCNT_SHIFT (0U)
#define TSW_AXIS2APB_ALMEM_RESP_CNT_RDCNT_GET(x) (((uint32_t)(x) & TSW_AXIS2APB_ALMEM_RESP_CNT_RDCNT_MASK) >> TSW_AXIS2APB_ALMEM_RESP_CNT_RDCNT_SHIFT)

/* Bitfield definition for register: AXIS2APB_ALMEM_FILLSTS */
/*
 * FULL (RO)
 *
 * FD FIFO full
 */
#define TSW_AXIS2APB_ALMEM_FILLSTS_FULL_MASK (0x10U)
#define TSW_AXIS2APB_ALMEM_FILLSTS_FULL_SHIFT (4U)
#define TSW_AXIS2APB_ALMEM_FILLSTS_FULL_GET(x) (((uint32_t)(x) & TSW_AXIS2APB_ALMEM_FILLSTS_FULL_MASK) >> TSW_AXIS2APB_ALMEM_FILLSTS_FULL_SHIFT)

/*
 * EMPTY (RO)
 *
 * FD FIFO failure
 */
#define TSW_AXIS2APB_ALMEM_FILLSTS_EMPTY_MASK (0x1U)
#define TSW_AXIS2APB_ALMEM_FILLSTS_EMPTY_SHIFT (0U)
#define TSW_AXIS2APB_ALMEM_FILLSTS_EMPTY_GET(x) (((uint32_t)(x) & TSW_AXIS2APB_ALMEM_FILLSTS_EMPTY_MASK) >> TSW_AXIS2APB_ALMEM_FILLSTS_EMPTY_SHIFT)

/* Bitfield definition for register: AXIS2APB_ALMEM_RESET */
/*
 * RESET (R/W)
 *
 * Resets controller and clears all pending stream data
 */
#define TSW_AXIS2APB_ALMEM_RESET_RESET_MASK (0x1U)
#define TSW_AXIS2APB_ALMEM_RESET_RESET_SHIFT (0U)
#define TSW_AXIS2APB_ALMEM_RESET_RESET_SET(x) (((uint32_t)(x) << TSW_AXIS2APB_ALMEM_RESET_RESET_SHIFT) & TSW_AXIS2APB_ALMEM_RESET_RESET_MASK)
#define TSW_AXIS2APB_ALMEM_RESET_RESET_GET(x) (((uint32_t)(x) & TSW_AXIS2APB_ALMEM_RESET_RESET_MASK) >> TSW_AXIS2APB_ALMEM_RESET_RESET_SHIFT)

/* Bitfield definition for register: AXIS2APB_ALMEM_PARAM */
/*
 * DEPTH (RO)
 *
 * number of configured buffer depth
 */
#define TSW_AXIS2APB_ALMEM_PARAM_DEPTH_MASK (0xFF00U)
#define TSW_AXIS2APB_ALMEM_PARAM_DEPTH_SHIFT (8U)
#define TSW_AXIS2APB_ALMEM_PARAM_DEPTH_GET(x) (((uint32_t)(x) & TSW_AXIS2APB_ALMEM_PARAM_DEPTH_MASK) >> TSW_AXIS2APB_ALMEM_PARAM_DEPTH_SHIFT)

/*
 * WORDLEN_BYTE (RO)
 *
 * number of configured 32bit for this controller
 */
#define TSW_AXIS2APB_ALMEM_PARAM_WORDLEN_BYTE_MASK (0xFFU)
#define TSW_AXIS2APB_ALMEM_PARAM_WORDLEN_BYTE_SHIFT (0U)
#define TSW_AXIS2APB_ALMEM_PARAM_WORDLEN_BYTE_GET(x) (((uint32_t)(x) & TSW_AXIS2APB_ALMEM_PARAM_WORDLEN_BYTE_MASK) >> TSW_AXIS2APB_ALMEM_PARAM_WORDLEN_BYTE_SHIFT)

/* Bitfield definition for register: AXIS2APB_ALMEM_RESPDATA_0 */
/*
 * UTAG (R/W)
 *
 * user sideband information
 */
#define TSW_AXIS2APB_ALMEM_RESPDATA_0_UTAG_MASK (0x1C00000UL)
#define TSW_AXIS2APB_ALMEM_RESPDATA_0_UTAG_SHIFT (22U)
#define TSW_AXIS2APB_ALMEM_RESPDATA_0_UTAG_SET(x) (((uint32_t)(x) << TSW_AXIS2APB_ALMEM_RESPDATA_0_UTAG_SHIFT) & TSW_AXIS2APB_ALMEM_RESPDATA_0_UTAG_MASK)
#define TSW_AXIS2APB_ALMEM_RESPDATA_0_UTAG_GET(x) (((uint32_t)(x) & TSW_AXIS2APB_ALMEM_RESPDATA_0_UTAG_MASK) >> TSW_AXIS2APB_ALMEM_RESPDATA_0_UTAG_SHIFT)

/*
 * QSEL (R/W)
 *
 * define the traffic queue selection
 */
#define TSW_AXIS2APB_ALMEM_RESPDATA_0_QSEL_MASK (0x300000UL)
#define TSW_AXIS2APB_ALMEM_RESPDATA_0_QSEL_SHIFT (20U)
#define TSW_AXIS2APB_ALMEM_RESPDATA_0_QSEL_SET(x) (((uint32_t)(x) << TSW_AXIS2APB_ALMEM_RESPDATA_0_QSEL_SHIFT) & TSW_AXIS2APB_ALMEM_RESPDATA_0_QSEL_MASK)
#define TSW_AXIS2APB_ALMEM_RESPDATA_0_QSEL_GET(x) (((uint32_t)(x) & TSW_AXIS2APB_ALMEM_RESPDATA_0_QSEL_MASK) >> TSW_AXIS2APB_ALMEM_RESPDATA_0_QSEL_SHIFT)

/*
 * DROP (R/W)
 *
 * frame should dropped
 */
#define TSW_AXIS2APB_ALMEM_RESPDATA_0_DROP_MASK (0x80000UL)
#define TSW_AXIS2APB_ALMEM_RESPDATA_0_DROP_SHIFT (19U)
#define TSW_AXIS2APB_ALMEM_RESPDATA_0_DROP_SET(x) (((uint32_t)(x) << TSW_AXIS2APB_ALMEM_RESPDATA_0_DROP_SHIFT) & TSW_AXIS2APB_ALMEM_RESPDATA_0_DROP_MASK)
#define TSW_AXIS2APB_ALMEM_RESPDATA_0_DROP_GET(x) (((uint32_t)(x) & TSW_AXIS2APB_ALMEM_RESPDATA_0_DROP_MASK) >> TSW_AXIS2APB_ALMEM_RESPDATA_0_DROP_SHIFT)

/*
 * QUEUE (R/W)
 *
 * select the priority queue if qsel=11
 */
#define TSW_AXIS2APB_ALMEM_RESPDATA_0_QUEUE_MASK (0x70000UL)
#define TSW_AXIS2APB_ALMEM_RESPDATA_0_QUEUE_SHIFT (16U)
#define TSW_AXIS2APB_ALMEM_RESPDATA_0_QUEUE_SET(x) (((uint32_t)(x) << TSW_AXIS2APB_ALMEM_RESPDATA_0_QUEUE_SHIFT) & TSW_AXIS2APB_ALMEM_RESPDATA_0_QUEUE_MASK)
#define TSW_AXIS2APB_ALMEM_RESPDATA_0_QUEUE_GET(x) (((uint32_t)(x) & TSW_AXIS2APB_ALMEM_RESPDATA_0_QUEUE_MASK) >> TSW_AXIS2APB_ALMEM_RESPDATA_0_QUEUE_SHIFT)

/*
 * DEST (R/W)
 *
 * destination ports
 */
#define TSW_AXIS2APB_ALMEM_RESPDATA_0_DEST_MASK (0xFFFFU)
#define TSW_AXIS2APB_ALMEM_RESPDATA_0_DEST_SHIFT (0U)
#define TSW_AXIS2APB_ALMEM_RESPDATA_0_DEST_SET(x) (((uint32_t)(x) << TSW_AXIS2APB_ALMEM_RESPDATA_0_DEST_SHIFT) & TSW_AXIS2APB_ALMEM_RESPDATA_0_DEST_MASK)
#define TSW_AXIS2APB_ALMEM_RESPDATA_0_DEST_GET(x) (((uint32_t)(x) & TSW_AXIS2APB_ALMEM_RESPDATA_0_DEST_MASK) >> TSW_AXIS2APB_ALMEM_RESPDATA_0_DEST_SHIFT)

/* Bitfield definition for register: AXIS2APB_ALMEM_RESPDATA_1 */
/*
 * WR_NRD (R/W)
 *
 * 1 for write and 0 for read
 */
#define TSW_AXIS2APB_ALMEM_RESPDATA_1_WR_NRD_MASK (0x80000000UL)
#define TSW_AXIS2APB_ALMEM_RESPDATA_1_WR_NRD_SHIFT (31U)
#define TSW_AXIS2APB_ALMEM_RESPDATA_1_WR_NRD_SET(x) (((uint32_t)(x) << TSW_AXIS2APB_ALMEM_RESPDATA_1_WR_NRD_SHIFT) & TSW_AXIS2APB_ALMEM_RESPDATA_1_WR_NRD_MASK)
#define TSW_AXIS2APB_ALMEM_RESPDATA_1_WR_NRD_GET(x) (((uint32_t)(x) & TSW_AXIS2APB_ALMEM_RESPDATA_1_WR_NRD_MASK) >> TSW_AXIS2APB_ALMEM_RESPDATA_1_WR_NRD_SHIFT)

/*
 * RESP (R/W)
 *
 * write response enable
 */
#define TSW_AXIS2APB_ALMEM_RESPDATA_1_RESP_MASK (0x40000000UL)
#define TSW_AXIS2APB_ALMEM_RESPDATA_1_RESP_SHIFT (30U)
#define TSW_AXIS2APB_ALMEM_RESPDATA_1_RESP_SET(x) (((uint32_t)(x) << TSW_AXIS2APB_ALMEM_RESPDATA_1_RESP_SHIFT) & TSW_AXIS2APB_ALMEM_RESPDATA_1_RESP_MASK)
#define TSW_AXIS2APB_ALMEM_RESPDATA_1_RESP_GET(x) (((uint32_t)(x) & TSW_AXIS2APB_ALMEM_RESPDATA_1_RESP_MASK) >> TSW_AXIS2APB_ALMEM_RESPDATA_1_RESP_SHIFT)

/*
 * ENTRY_NUM (R/W)
 *
 * define the entry number for reading and writing
 */
#define TSW_AXIS2APB_ALMEM_RESPDATA_1_ENTRY_NUM_MASK (0xFFFFU)
#define TSW_AXIS2APB_ALMEM_RESPDATA_1_ENTRY_NUM_SHIFT (0U)
#define TSW_AXIS2APB_ALMEM_RESPDATA_1_ENTRY_NUM_SET(x) (((uint32_t)(x) << TSW_AXIS2APB_ALMEM_RESPDATA_1_ENTRY_NUM_SHIFT) & TSW_AXIS2APB_ALMEM_RESPDATA_1_ENTRY_NUM_MASK)
#define TSW_AXIS2APB_ALMEM_RESPDATA_1_ENTRY_NUM_GET(x) (((uint32_t)(x) & TSW_AXIS2APB_ALMEM_RESPDATA_1_ENTRY_NUM_MASK) >> TSW_AXIS2APB_ALMEM_RESPDATA_1_ENTRY_NUM_SHIFT)

/* Bitfield definition for register array: HITMEM */
/*
 * HITMEM_REG (RW)
 *
 * Every bit represents a lookup entry starting with bit 0
 * as entry 0. The memory can be written and cleared by the host system via common memory-mapped
 * bus access.
 */
#define TSW_HITMEM_HITMEM_REG_MASK (0xFFFFFFFFUL)
#define TSW_HITMEM_HITMEM_REG_SHIFT (0U)
#define TSW_HITMEM_HITMEM_REG_SET(x) (((uint32_t)(x) << TSW_HITMEM_HITMEM_REG_SHIFT) & TSW_HITMEM_HITMEM_REG_MASK)
#define TSW_HITMEM_HITMEM_REG_GET(x) (((uint32_t)(x) & TSW_HITMEM_HITMEM_REG_MASK) >> TSW_HITMEM_HITMEM_REG_SHIFT)

/* Bitfield definition for register: APB2AXIS_LOOKUP_STS */
/*
 * BUSY (RO)
 *
 * the controller is writing data and/or data is pending
 */
#define TSW_APB2AXIS_LOOKUP_STS_BUSY_MASK (0x2U)
#define TSW_APB2AXIS_LOOKUP_STS_BUSY_SHIFT (1U)
#define TSW_APB2AXIS_LOOKUP_STS_BUSY_GET(x) (((uint32_t)(x) & TSW_APB2AXIS_LOOKUP_STS_BUSY_MASK) >> TSW_APB2AXIS_LOOKUP_STS_BUSY_SHIFT)

/*
 * RDY (RO)
 *
 * the new data is written to data register
 */
#define TSW_APB2AXIS_LOOKUP_STS_RDY_MASK (0x1U)
#define TSW_APB2AXIS_LOOKUP_STS_RDY_SHIFT (0U)
#define TSW_APB2AXIS_LOOKUP_STS_RDY_GET(x) (((uint32_t)(x) & TSW_APB2AXIS_LOOKUP_STS_RDY_MASK) >> TSW_APB2AXIS_LOOKUP_STS_RDY_SHIFT)

/* Bitfield definition for register: APB2AXIS_LOOKUP_REQ_CNT */
/*
 * WRCNT (RO)
 *
 * number of streams in queue
 */
#define TSW_APB2AXIS_LOOKUP_REQ_CNT_WRCNT_MASK (0xFFU)
#define TSW_APB2AXIS_LOOKUP_REQ_CNT_WRCNT_SHIFT (0U)
#define TSW_APB2AXIS_LOOKUP_REQ_CNT_WRCNT_GET(x) (((uint32_t)(x) & TSW_APB2AXIS_LOOKUP_REQ_CNT_WRCNT_MASK) >> TSW_APB2AXIS_LOOKUP_REQ_CNT_WRCNT_SHIFT)

/* Bitfield definition for register: APB2AXIS_LOOKUP_FILLSTS */
/*
 * FULL (RO)
 *
 * FD FIFO full
 */
#define TSW_APB2AXIS_LOOKUP_FILLSTS_FULL_MASK (0x10U)
#define TSW_APB2AXIS_LOOKUP_FILLSTS_FULL_SHIFT (4U)
#define TSW_APB2AXIS_LOOKUP_FILLSTS_FULL_GET(x) (((uint32_t)(x) & TSW_APB2AXIS_LOOKUP_FILLSTS_FULL_MASK) >> TSW_APB2AXIS_LOOKUP_FILLSTS_FULL_SHIFT)

/*
 * EMPTY (RO)
 *
 * FD FIFO failure
 */
#define TSW_APB2AXIS_LOOKUP_FILLSTS_EMPTY_MASK (0x1U)
#define TSW_APB2AXIS_LOOKUP_FILLSTS_EMPTY_SHIFT (0U)
#define TSW_APB2AXIS_LOOKUP_FILLSTS_EMPTY_GET(x) (((uint32_t)(x) & TSW_APB2AXIS_LOOKUP_FILLSTS_EMPTY_MASK) >> TSW_APB2AXIS_LOOKUP_FILLSTS_EMPTY_SHIFT)

/* Bitfield definition for register: APB2AXIS_LOOKUP_RESET */
/*
 * RESET (R/W)
 *
 * Resets controller and clears all pending stream data
 */
#define TSW_APB2AXIS_LOOKUP_RESET_RESET_MASK (0x1U)
#define TSW_APB2AXIS_LOOKUP_RESET_RESET_SHIFT (0U)
#define TSW_APB2AXIS_LOOKUP_RESET_RESET_SET(x) (((uint32_t)(x) << TSW_APB2AXIS_LOOKUP_RESET_RESET_SHIFT) & TSW_APB2AXIS_LOOKUP_RESET_RESET_MASK)
#define TSW_APB2AXIS_LOOKUP_RESET_RESET_GET(x) (((uint32_t)(x) & TSW_APB2AXIS_LOOKUP_RESET_RESET_MASK) >> TSW_APB2AXIS_LOOKUP_RESET_RESET_SHIFT)

/* Bitfield definition for register: APB2AXIS_LOOKUP_PARAM */
/*
 * DEPTH (RO)
 *
 * number of configured buffer depth
 */
#define TSW_APB2AXIS_LOOKUP_PARAM_DEPTH_MASK (0xFF00U)
#define TSW_APB2AXIS_LOOKUP_PARAM_DEPTH_SHIFT (8U)
#define TSW_APB2AXIS_LOOKUP_PARAM_DEPTH_GET(x) (((uint32_t)(x) & TSW_APB2AXIS_LOOKUP_PARAM_DEPTH_MASK) >> TSW_APB2AXIS_LOOKUP_PARAM_DEPTH_SHIFT)

/*
 * WORDLEN_BYTE (RO)
 *
 * number of configured 32bit for this controller
 */
#define TSW_APB2AXIS_LOOKUP_PARAM_WORDLEN_BYTE_MASK (0xFFU)
#define TSW_APB2AXIS_LOOKUP_PARAM_WORDLEN_BYTE_SHIFT (0U)
#define TSW_APB2AXIS_LOOKUP_PARAM_WORDLEN_BYTE_GET(x) (((uint32_t)(x) & TSW_APB2AXIS_LOOKUP_PARAM_WORDLEN_BYTE_MASK) >> TSW_APB2AXIS_LOOKUP_PARAM_WORDLEN_BYTE_SHIFT)

/* Bitfield definition for register: APB2AXIS_LOOKUP_REQDATA_0 */
/*
 * DESTMAC (RW)
 *
 * Holding the first four bytes of requested MAC address.
 */
#define TSW_APB2AXIS_LOOKUP_REQDATA_0_DESTMAC_MASK (0xFFFFFFFFUL)
#define TSW_APB2AXIS_LOOKUP_REQDATA_0_DESTMAC_SHIFT (0U)
#define TSW_APB2AXIS_LOOKUP_REQDATA_0_DESTMAC_SET(x) (((uint32_t)(x) << TSW_APB2AXIS_LOOKUP_REQDATA_0_DESTMAC_SHIFT) & TSW_APB2AXIS_LOOKUP_REQDATA_0_DESTMAC_MASK)
#define TSW_APB2AXIS_LOOKUP_REQDATA_0_DESTMAC_GET(x) (((uint32_t)(x) & TSW_APB2AXIS_LOOKUP_REQDATA_0_DESTMAC_MASK) >> TSW_APB2AXIS_LOOKUP_REQDATA_0_DESTMAC_SHIFT)

/* Bitfield definition for register: APB2AXIS_LOOKUP_REQDATA_1 */
/*
 * DESTMAC (RW)
 *
 * Holding the last two bytes of requested MAC address.
 */
#define TSW_APB2AXIS_LOOKUP_REQDATA_1_DESTMAC_MASK (0xFFFFU)
#define TSW_APB2AXIS_LOOKUP_REQDATA_1_DESTMAC_SHIFT (0U)
#define TSW_APB2AXIS_LOOKUP_REQDATA_1_DESTMAC_SET(x) (((uint32_t)(x) << TSW_APB2AXIS_LOOKUP_REQDATA_1_DESTMAC_SHIFT) & TSW_APB2AXIS_LOOKUP_REQDATA_1_DESTMAC_MASK)
#define TSW_APB2AXIS_LOOKUP_REQDATA_1_DESTMAC_GET(x) (((uint32_t)(x) & TSW_APB2AXIS_LOOKUP_REQDATA_1_DESTMAC_MASK) >> TSW_APB2AXIS_LOOKUP_REQDATA_1_DESTMAC_SHIFT)

/* Bitfield definition for register: APB2AXIS_LOOKUP_REQDATA_3 */
/*
 * IS_VLAN (RW)
 *
 * Tell the LOOKUP module the requested traffic is VLAN tagged.
 */
#define TSW_APB2AXIS_LOOKUP_REQDATA_3_IS_VLAN_MASK (0x10000UL)
#define TSW_APB2AXIS_LOOKUP_REQDATA_3_IS_VLAN_SHIFT (16U)
#define TSW_APB2AXIS_LOOKUP_REQDATA_3_IS_VLAN_SET(x) (((uint32_t)(x) << TSW_APB2AXIS_LOOKUP_REQDATA_3_IS_VLAN_SHIFT) & TSW_APB2AXIS_LOOKUP_REQDATA_3_IS_VLAN_MASK)
#define TSW_APB2AXIS_LOOKUP_REQDATA_3_IS_VLAN_GET(x) (((uint32_t)(x) & TSW_APB2AXIS_LOOKUP_REQDATA_3_IS_VLAN_MASK) >> TSW_APB2AXIS_LOOKUP_REQDATA_3_IS_VLAN_SHIFT)

/*
 * VLAN_TCI (RW)
 *
 * Set the requested traffic VLAN_TCI, if IS_VLAN=1.
 */
#define TSW_APB2AXIS_LOOKUP_REQDATA_3_VLAN_TCI_MASK (0xFFFFU)
#define TSW_APB2AXIS_LOOKUP_REQDATA_3_VLAN_TCI_SHIFT (0U)
#define TSW_APB2AXIS_LOOKUP_REQDATA_3_VLAN_TCI_SET(x) (((uint32_t)(x) << TSW_APB2AXIS_LOOKUP_REQDATA_3_VLAN_TCI_SHIFT) & TSW_APB2AXIS_LOOKUP_REQDATA_3_VLAN_TCI_MASK)
#define TSW_APB2AXIS_LOOKUP_REQDATA_3_VLAN_TCI_GET(x) (((uint32_t)(x) & TSW_APB2AXIS_LOOKUP_REQDATA_3_VLAN_TCI_MASK) >> TSW_APB2AXIS_LOOKUP_REQDATA_3_VLAN_TCI_SHIFT)

/* Bitfield definition for register: AXIS2APB_LOOKUP_STS */
/*
 * BUSY (RO)
 *
 * the controller is writing data and/or data is pending
 */
#define TSW_AXIS2APB_LOOKUP_STS_BUSY_MASK (0x2U)
#define TSW_AXIS2APB_LOOKUP_STS_BUSY_SHIFT (1U)
#define TSW_AXIS2APB_LOOKUP_STS_BUSY_GET(x) (((uint32_t)(x) & TSW_AXIS2APB_LOOKUP_STS_BUSY_MASK) >> TSW_AXIS2APB_LOOKUP_STS_BUSY_SHIFT)

/*
 * RDY (RO)
 *
 * the new data is written to data register
 */
#define TSW_AXIS2APB_LOOKUP_STS_RDY_MASK (0x1U)
#define TSW_AXIS2APB_LOOKUP_STS_RDY_SHIFT (0U)
#define TSW_AXIS2APB_LOOKUP_STS_RDY_GET(x) (((uint32_t)(x) & TSW_AXIS2APB_LOOKUP_STS_RDY_MASK) >> TSW_AXIS2APB_LOOKUP_STS_RDY_SHIFT)

/* Bitfield definition for register: AXIS2APB_LOOKUP_RESP_CNT */
/*
 * RDCNT (RO)
 *
 * number of streams in queue
 */
#define TSW_AXIS2APB_LOOKUP_RESP_CNT_RDCNT_MASK (0xFFU)
#define TSW_AXIS2APB_LOOKUP_RESP_CNT_RDCNT_SHIFT (0U)
#define TSW_AXIS2APB_LOOKUP_RESP_CNT_RDCNT_GET(x) (((uint32_t)(x) & TSW_AXIS2APB_LOOKUP_RESP_CNT_RDCNT_MASK) >> TSW_AXIS2APB_LOOKUP_RESP_CNT_RDCNT_SHIFT)

/* Bitfield definition for register: AXIS2APB_LOOKUP_FILLSTS */
/*
 * FULL (RO)
 *
 * FD FIFO full
 */
#define TSW_AXIS2APB_LOOKUP_FILLSTS_FULL_MASK (0x10U)
#define TSW_AXIS2APB_LOOKUP_FILLSTS_FULL_SHIFT (4U)
#define TSW_AXIS2APB_LOOKUP_FILLSTS_FULL_GET(x) (((uint32_t)(x) & TSW_AXIS2APB_LOOKUP_FILLSTS_FULL_MASK) >> TSW_AXIS2APB_LOOKUP_FILLSTS_FULL_SHIFT)

/*
 * EMPTY (RO)
 *
 * FD FIFO failure
 */
#define TSW_AXIS2APB_LOOKUP_FILLSTS_EMPTY_MASK (0x1U)
#define TSW_AXIS2APB_LOOKUP_FILLSTS_EMPTY_SHIFT (0U)
#define TSW_AXIS2APB_LOOKUP_FILLSTS_EMPTY_GET(x) (((uint32_t)(x) & TSW_AXIS2APB_LOOKUP_FILLSTS_EMPTY_MASK) >> TSW_AXIS2APB_LOOKUP_FILLSTS_EMPTY_SHIFT)

/* Bitfield definition for register: AXIS2APB_LOOKUP_RESET */
/*
 * RESET (R/W)
 *
 * Resets controller and clears all pending stream data
 */
#define TSW_AXIS2APB_LOOKUP_RESET_RESET_MASK (0x1U)
#define TSW_AXIS2APB_LOOKUP_RESET_RESET_SHIFT (0U)
#define TSW_AXIS2APB_LOOKUP_RESET_RESET_SET(x) (((uint32_t)(x) << TSW_AXIS2APB_LOOKUP_RESET_RESET_SHIFT) & TSW_AXIS2APB_LOOKUP_RESET_RESET_MASK)
#define TSW_AXIS2APB_LOOKUP_RESET_RESET_GET(x) (((uint32_t)(x) & TSW_AXIS2APB_LOOKUP_RESET_RESET_MASK) >> TSW_AXIS2APB_LOOKUP_RESET_RESET_SHIFT)

/* Bitfield definition for register: AXIS2APB_LOOKUP_PARAM */
/*
 * DEPTH (RO)
 *
 * number of configured buffer depth
 */
#define TSW_AXIS2APB_LOOKUP_PARAM_DEPTH_MASK (0xFF00U)
#define TSW_AXIS2APB_LOOKUP_PARAM_DEPTH_SHIFT (8U)
#define TSW_AXIS2APB_LOOKUP_PARAM_DEPTH_GET(x) (((uint32_t)(x) & TSW_AXIS2APB_LOOKUP_PARAM_DEPTH_MASK) >> TSW_AXIS2APB_LOOKUP_PARAM_DEPTH_SHIFT)

/*
 * WORDLEN_BYTE (RO)
 *
 * number of configured 32bit for this controller
 */
#define TSW_AXIS2APB_LOOKUP_PARAM_WORDLEN_BYTE_MASK (0xFFU)
#define TSW_AXIS2APB_LOOKUP_PARAM_WORDLEN_BYTE_SHIFT (0U)
#define TSW_AXIS2APB_LOOKUP_PARAM_WORDLEN_BYTE_GET(x) (((uint32_t)(x) & TSW_AXIS2APB_LOOKUP_PARAM_WORDLEN_BYTE_MASK) >> TSW_AXIS2APB_LOOKUP_PARAM_WORDLEN_BYTE_SHIFT)

/* Bitfield definition for register: AXIS2APB_LOOKUP_RESPDATA_0 */
/*
 * DROP_VLAN (RW)
 *
 * Used for statistics. Shows that drop occurs by VLAN-ID
 */
#define TSW_AXIS2APB_LOOKUP_RESPDATA_0_DROP_VLAN_MASK (0x2000000UL)
#define TSW_AXIS2APB_LOOKUP_RESPDATA_0_DROP_VLAN_SHIFT (25U)
#define TSW_AXIS2APB_LOOKUP_RESPDATA_0_DROP_VLAN_SET(x) (((uint32_t)(x) << TSW_AXIS2APB_LOOKUP_RESPDATA_0_DROP_VLAN_SHIFT) & TSW_AXIS2APB_LOOKUP_RESPDATA_0_DROP_VLAN_MASK)
#define TSW_AXIS2APB_LOOKUP_RESPDATA_0_DROP_VLAN_GET(x) (((uint32_t)(x) & TSW_AXIS2APB_LOOKUP_RESPDATA_0_DROP_VLAN_MASK) >> TSW_AXIS2APB_LOOKUP_RESPDATA_0_DROP_VLAN_SHIFT)

/*
 * HIT (RW)
 *
 * Is 1, if DESTMAC and VID hit an entry.
 */
#define TSW_AXIS2APB_LOOKUP_RESPDATA_0_HIT_MASK (0x1000000UL)
#define TSW_AXIS2APB_LOOKUP_RESPDATA_0_HIT_SHIFT (24U)
#define TSW_AXIS2APB_LOOKUP_RESPDATA_0_HIT_SET(x) (((uint32_t)(x) << TSW_AXIS2APB_LOOKUP_RESPDATA_0_HIT_SHIFT) & TSW_AXIS2APB_LOOKUP_RESPDATA_0_HIT_MASK)
#define TSW_AXIS2APB_LOOKUP_RESPDATA_0_HIT_GET(x) (((uint32_t)(x) & TSW_AXIS2APB_LOOKUP_RESPDATA_0_HIT_MASK) >> TSW_AXIS2APB_LOOKUP_RESPDATA_0_HIT_SHIFT)

/*
 * UTAG (RW)
 *
 * TSN user sideband information from ALMEM.
 */
#define TSW_AXIS2APB_LOOKUP_RESPDATA_0_UTAG_MASK (0xE00000UL)
#define TSW_AXIS2APB_LOOKUP_RESPDATA_0_UTAG_SHIFT (21U)
#define TSW_AXIS2APB_LOOKUP_RESPDATA_0_UTAG_SET(x) (((uint32_t)(x) << TSW_AXIS2APB_LOOKUP_RESPDATA_0_UTAG_SHIFT) & TSW_AXIS2APB_LOOKUP_RESPDATA_0_UTAG_MASK)
#define TSW_AXIS2APB_LOOKUP_RESPDATA_0_UTAG_GET(x) (((uint32_t)(x) & TSW_AXIS2APB_LOOKUP_RESPDATA_0_UTAG_MASK) >> TSW_AXIS2APB_LOOKUP_RESPDATA_0_UTAG_SHIFT)

/*
 * HIT_VLAN (RW)
 *
 * Is 1, if VID hit entry in VLAN_PORT table.
 */
#define TSW_AXIS2APB_LOOKUP_RESPDATA_0_HIT_VLAN_MASK (0x100000UL)
#define TSW_AXIS2APB_LOOKUP_RESPDATA_0_HIT_VLAN_SHIFT (20U)
#define TSW_AXIS2APB_LOOKUP_RESPDATA_0_HIT_VLAN_SET(x) (((uint32_t)(x) << TSW_AXIS2APB_LOOKUP_RESPDATA_0_HIT_VLAN_SHIFT) & TSW_AXIS2APB_LOOKUP_RESPDATA_0_HIT_VLAN_MASK)
#define TSW_AXIS2APB_LOOKUP_RESPDATA_0_HIT_VLAN_GET(x) (((uint32_t)(x) & TSW_AXIS2APB_LOOKUP_RESPDATA_0_HIT_VLAN_MASK) >> TSW_AXIS2APB_LOOKUP_RESPDATA_0_HIT_VLAN_SHIFT)

/*
 * DROP (RW)
 *
 * Indicate that the frame should be dropped.
 */
#define TSW_AXIS2APB_LOOKUP_RESPDATA_0_DROP_MASK (0x80000UL)
#define TSW_AXIS2APB_LOOKUP_RESPDATA_0_DROP_SHIFT (19U)
#define TSW_AXIS2APB_LOOKUP_RESPDATA_0_DROP_SET(x) (((uint32_t)(x) << TSW_AXIS2APB_LOOKUP_RESPDATA_0_DROP_SHIFT) & TSW_AXIS2APB_LOOKUP_RESPDATA_0_DROP_MASK)
#define TSW_AXIS2APB_LOOKUP_RESPDATA_0_DROP_GET(x) (((uint32_t)(x) & TSW_AXIS2APB_LOOKUP_RESPDATA_0_DROP_MASK) >> TSW_AXIS2APB_LOOKUP_RESPDATA_0_DROP_SHIFT)

/*
 * QUEUE (RW)
 *
 * TX traffic queue selection.
 */
#define TSW_AXIS2APB_LOOKUP_RESPDATA_0_QUEUE_MASK (0x70000UL)
#define TSW_AXIS2APB_LOOKUP_RESPDATA_0_QUEUE_SHIFT (16U)
#define TSW_AXIS2APB_LOOKUP_RESPDATA_0_QUEUE_SET(x) (((uint32_t)(x) << TSW_AXIS2APB_LOOKUP_RESPDATA_0_QUEUE_SHIFT) & TSW_AXIS2APB_LOOKUP_RESPDATA_0_QUEUE_MASK)
#define TSW_AXIS2APB_LOOKUP_RESPDATA_0_QUEUE_GET(x) (((uint32_t)(x) & TSW_AXIS2APB_LOOKUP_RESPDATA_0_QUEUE_MASK) >> TSW_AXIS2APB_LOOKUP_RESPDATA_0_QUEUE_SHIFT)

/*
 * DEST (RW)
 *
 * Forwarding ports from 0 to 15, Bit 0 is CPU port.
 */
#define TSW_AXIS2APB_LOOKUP_RESPDATA_0_DEST_MASK (0xFFFFU)
#define TSW_AXIS2APB_LOOKUP_RESPDATA_0_DEST_SHIFT (0U)
#define TSW_AXIS2APB_LOOKUP_RESPDATA_0_DEST_SET(x) (((uint32_t)(x) << TSW_AXIS2APB_LOOKUP_RESPDATA_0_DEST_SHIFT) & TSW_AXIS2APB_LOOKUP_RESPDATA_0_DEST_MASK)
#define TSW_AXIS2APB_LOOKUP_RESPDATA_0_DEST_GET(x) (((uint32_t)(x) & TSW_AXIS2APB_LOOKUP_RESPDATA_0_DEST_MASK) >> TSW_AXIS2APB_LOOKUP_RESPDATA_0_DEST_SHIFT)

/* Bitfield definition for register: AXIS2APB_LOOKUP_RESPDATA_1 */
/*
 * ENTRY_NUM (RW)
 *
 * Entry number of ALMEM.
 */
#define TSW_AXIS2APB_LOOKUP_RESPDATA_1_ENTRY_NUM_MASK (0xFFFFU)
#define TSW_AXIS2APB_LOOKUP_RESPDATA_1_ENTRY_NUM_SHIFT (0U)
#define TSW_AXIS2APB_LOOKUP_RESPDATA_1_ENTRY_NUM_SET(x) (((uint32_t)(x) << TSW_AXIS2APB_LOOKUP_RESPDATA_1_ENTRY_NUM_SHIFT) & TSW_AXIS2APB_LOOKUP_RESPDATA_1_ENTRY_NUM_MASK)
#define TSW_AXIS2APB_LOOKUP_RESPDATA_1_ENTRY_NUM_GET(x) (((uint32_t)(x) & TSW_AXIS2APB_LOOKUP_RESPDATA_1_ENTRY_NUM_MASK) >> TSW_AXIS2APB_LOOKUP_RESPDATA_1_ENTRY_NUM_SHIFT)

/* Bitfield definition for register: CENTRAL_CSR_VERSION */
/*
 * VER_HI (RO)
 *
 * Major Version number of TSN-SW core.
 */
#define TSW_CENTRAL_CSR_VERSION_VER_HI_MASK (0xFF000000UL)
#define TSW_CENTRAL_CSR_VERSION_VER_HI_SHIFT (24U)
#define TSW_CENTRAL_CSR_VERSION_VER_HI_GET(x) (((uint32_t)(x) & TSW_CENTRAL_CSR_VERSION_VER_HI_MASK) >> TSW_CENTRAL_CSR_VERSION_VER_HI_SHIFT)

/*
 * VER_LO (RO)
 *
 * Minor Version number of TSN-SW core.
 */
#define TSW_CENTRAL_CSR_VERSION_VER_LO_MASK (0xFF0000UL)
#define TSW_CENTRAL_CSR_VERSION_VER_LO_SHIFT (16U)
#define TSW_CENTRAL_CSR_VERSION_VER_LO_GET(x) (((uint32_t)(x) & TSW_CENTRAL_CSR_VERSION_VER_LO_MASK) >> TSW_CENTRAL_CSR_VERSION_VER_LO_SHIFT)

/*
 * VER_REV (RO)
 *
 * Reversion number of TSN-SW core.
 */
#define TSW_CENTRAL_CSR_VERSION_VER_REV_MASK (0xFFU)
#define TSW_CENTRAL_CSR_VERSION_VER_REV_SHIFT (0U)
#define TSW_CENTRAL_CSR_VERSION_VER_REV_GET(x) (((uint32_t)(x) & TSW_CENTRAL_CSR_VERSION_VER_REV_MASK) >> TSW_CENTRAL_CSR_VERSION_VER_REV_SHIFT)

/* Bitfield definition for register: CENTRAL_CSR_PARAM */
/*
 * INCL_QCI (RO)
 *
 * Shows if QCI module is present.
 */
#define TSW_CENTRAL_CSR_PARAM_INCL_QCI_MASK (0x40000UL)
#define TSW_CENTRAL_CSR_PARAM_INCL_QCI_SHIFT (18U)
#define TSW_CENTRAL_CSR_PARAM_INCL_QCI_GET(x) (((uint32_t)(x) & TSW_CENTRAL_CSR_PARAM_INCL_QCI_MASK) >> TSW_CENTRAL_CSR_PARAM_INCL_QCI_SHIFT)

/*
 * INCL_CB0 (RO)
 *
 * Shows if IP is configured with “lightweight” 802.1CB at CPU-Port.
 */
#define TSW_CENTRAL_CSR_PARAM_INCL_CB0_MASK (0x20000UL)
#define TSW_CENTRAL_CSR_PARAM_INCL_CB0_SHIFT (17U)
#define TSW_CENTRAL_CSR_PARAM_INCL_CB0_GET(x) (((uint32_t)(x) & TSW_CENTRAL_CSR_PARAM_INCL_CB0_MASK) >> TSW_CENTRAL_CSR_PARAM_INCL_CB0_SHIFT)

/*
 * TESTMODE (RO)
 *
 * Shows if IP is configured in TESTMODE.
 */
#define TSW_CENTRAL_CSR_PARAM_TESTMODE_MASK (0x10000UL)
#define TSW_CENTRAL_CSR_PARAM_TESTMODE_SHIFT (16U)
#define TSW_CENTRAL_CSR_PARAM_TESTMODE_GET(x) (((uint32_t)(x) & TSW_CENTRAL_CSR_PARAM_TESTMODE_MASK) >> TSW_CENTRAL_CSR_PARAM_TESTMODE_SHIFT)

/*
 * TYPE (RO)
 *
 * Specify type of switch core
 */
#define TSW_CENTRAL_CSR_PARAM_TYPE_MASK (0xFF00U)
#define TSW_CENTRAL_CSR_PARAM_TYPE_SHIFT (8U)
#define TSW_CENTRAL_CSR_PARAM_TYPE_GET(x) (((uint32_t)(x) & TSW_CENTRAL_CSR_PARAM_TYPE_MASK) >> TSW_CENTRAL_CSR_PARAM_TYPE_SHIFT)

/*
 * NPORTS (RO)
 *
 * Number of TSN ports without counting internal CPU port. For TSN-SE, it returns always 2
 */
#define TSW_CENTRAL_CSR_PARAM_NPORTS_MASK (0xFFU)
#define TSW_CENTRAL_CSR_PARAM_NPORTS_SHIFT (0U)
#define TSW_CENTRAL_CSR_PARAM_NPORTS_GET(x) (((uint32_t)(x) & TSW_CENTRAL_CSR_PARAM_NPORTS_MASK) >> TSW_CENTRAL_CSR_PARAM_NPORTS_SHIFT)

/* Bitfield definition for register: CENTRAL_CSR_CONFIG */
/*
 * MSEC_CYCLES (R/W)
 *
 * Number of SYS_CLK cycles during 1 ms. It is required to calculate a correct time
 */
#define TSW_CENTRAL_CSR_CONFIG_MSEC_CYCLES_MASK (0xFFFFFFUL)
#define TSW_CENTRAL_CSR_CONFIG_MSEC_CYCLES_SHIFT (0U)
#define TSW_CENTRAL_CSR_CONFIG_MSEC_CYCLES_SET(x) (((uint32_t)(x) << TSW_CENTRAL_CSR_CONFIG_MSEC_CYCLES_SHIFT) & TSW_CENTRAL_CSR_CONFIG_MSEC_CYCLES_MASK)
#define TSW_CENTRAL_CSR_CONFIG_MSEC_CYCLES_GET(x) (((uint32_t)(x) & TSW_CENTRAL_CSR_CONFIG_MSEC_CYCLES_MASK) >> TSW_CENTRAL_CSR_CONFIG_MSEC_CYCLES_SHIFT)

/* Bitfield definition for register: CENTRAL_CSR_CB_PARAM */
/*
 * SID_D (RO)
 *
 * Number of 802.1CB Stream Identification entries. 2^SID_D entries
 */
#define TSW_CENTRAL_CSR_CB_PARAM_SID_D_MASK (0xFF00U)
#define TSW_CENTRAL_CSR_CB_PARAM_SID_D_SHIFT (8U)
#define TSW_CENTRAL_CSR_CB_PARAM_SID_D_GET(x) (((uint32_t)(x) & TSW_CENTRAL_CSR_CB_PARAM_SID_D_MASK) >> TSW_CENTRAL_CSR_CB_PARAM_SID_D_SHIFT)

/*
 * FRER_D (RO)
 *
 * Number of 802.1CB Recovery Function entries. 2^FRER_D entries.
 */
#define TSW_CENTRAL_CSR_CB_PARAM_FRER_D_MASK (0xFFU)
#define TSW_CENTRAL_CSR_CB_PARAM_FRER_D_SHIFT (0U)
#define TSW_CENTRAL_CSR_CB_PARAM_FRER_D_GET(x) (((uint32_t)(x) & TSW_CENTRAL_CSR_CB_PARAM_FRER_D_MASK) >> TSW_CENTRAL_CSR_CB_PARAM_FRER_D_SHIFT)

/* Bitfield definition for register: CENTRAL_CSR_QCI_CTRL_PARAM */
/*
 * QCI_GTD (RO)
 *
 * (Log) gate table depth. 2**GTD entries.
 */
#define TSW_CENTRAL_CSR_QCI_CTRL_PARAM_QCI_GTD_MASK (0xFF0000UL)
#define TSW_CENTRAL_CSR_QCI_CTRL_PARAM_QCI_GTD_SHIFT (16U)
#define TSW_CENTRAL_CSR_QCI_CTRL_PARAM_QCI_GTD_GET(x) (((uint32_t)(x) & TSW_CENTRAL_CSR_QCI_CTRL_PARAM_QCI_GTD_MASK) >> TSW_CENTRAL_CSR_QCI_CTRL_PARAM_QCI_GTD_SHIFT)

/*
 * QCI_FMD (RO)
 *
 * (Log) flow meter depth. 2**FMD entries.
 */
#define TSW_CENTRAL_CSR_QCI_CTRL_PARAM_QCI_FMD_MASK (0xFF00U)
#define TSW_CENTRAL_CSR_QCI_CTRL_PARAM_QCI_FMD_SHIFT (8U)
#define TSW_CENTRAL_CSR_QCI_CTRL_PARAM_QCI_FMD_GET(x) (((uint32_t)(x) & TSW_CENTRAL_CSR_QCI_CTRL_PARAM_QCI_FMD_MASK) >> TSW_CENTRAL_CSR_QCI_CTRL_PARAM_QCI_FMD_SHIFT)

/*
 * QCI_FTD (RO)
 *
 * (Log) filter table depth. 2**FTD entries.
 */
#define TSW_CENTRAL_CSR_QCI_CTRL_PARAM_QCI_FTD_MASK (0xFFU)
#define TSW_CENTRAL_CSR_QCI_CTRL_PARAM_QCI_FTD_SHIFT (0U)
#define TSW_CENTRAL_CSR_QCI_CTRL_PARAM_QCI_FTD_GET(x) (((uint32_t)(x) & TSW_CENTRAL_CSR_QCI_CTRL_PARAM_QCI_FTD_MASK) >> TSW_CENTRAL_CSR_QCI_CTRL_PARAM_QCI_FTD_SHIFT)

/* Bitfield definition for register: CENTRAL_QCI_HWCFG */
/*
 * FMD (RO)
 *
 * FMD – parameter
 */
#define TSW_CENTRAL_QCI_HWCFG_FMD_MASK (0xFF0000UL)
#define TSW_CENTRAL_QCI_HWCFG_FMD_SHIFT (16U)
#define TSW_CENTRAL_QCI_HWCFG_FMD_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_HWCFG_FMD_MASK) >> TSW_CENTRAL_QCI_HWCFG_FMD_SHIFT)

/*
 * GTD (RO)
 *
 * GTD – parameter
 */
#define TSW_CENTRAL_QCI_HWCFG_GTD_MASK (0xFF00U)
#define TSW_CENTRAL_QCI_HWCFG_GTD_SHIFT (8U)
#define TSW_CENTRAL_QCI_HWCFG_GTD_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_HWCFG_GTD_MASK) >> TSW_CENTRAL_QCI_HWCFG_GTD_SHIFT)

/*
 * FTD (RO)
 *
 * FTD – parameter
 */
#define TSW_CENTRAL_QCI_HWCFG_FTD_MASK (0xFFU)
#define TSW_CENTRAL_QCI_HWCFG_FTD_SHIFT (0U)
#define TSW_CENTRAL_QCI_HWCFG_FTD_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_HWCFG_FTD_MASK) >> TSW_CENTRAL_QCI_HWCFG_FTD_SHIFT)

/* Bitfield definition for register: CENTRAL_QCI_FILTERSEL */
/*
 * INDEX (R/W)
 *
 * Filter select index
 * Any written value larger than the maximum index
 * (2**FTD-1) will result in a read-back value of <0>.
 */
#define TSW_CENTRAL_QCI_FILTERSEL_INDEX_MASK (0xFFU)
#define TSW_CENTRAL_QCI_FILTERSEL_INDEX_SHIFT (0U)
#define TSW_CENTRAL_QCI_FILTERSEL_INDEX_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_FILTERSEL_INDEX_SHIFT) & TSW_CENTRAL_QCI_FILTERSEL_INDEX_MASK)
#define TSW_CENTRAL_QCI_FILTERSEL_INDEX_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_FILTERSEL_INDEX_MASK) >> TSW_CENTRAL_QCI_FILTERSEL_INDEX_SHIFT)

/* Bitfield definition for register: CENTRAL_QCI_METERSEL */
/*
 * INDEX (R/W)
 *
 * Flowmeter select index
 * Any written value larger than the maximum index
 * (2**FMD-1) will result in a read-back value of <0>.
 */
#define TSW_CENTRAL_QCI_METERSEL_INDEX_MASK (0xFFU)
#define TSW_CENTRAL_QCI_METERSEL_INDEX_SHIFT (0U)
#define TSW_CENTRAL_QCI_METERSEL_INDEX_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_METERSEL_INDEX_SHIFT) & TSW_CENTRAL_QCI_METERSEL_INDEX_MASK)
#define TSW_CENTRAL_QCI_METERSEL_INDEX_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_METERSEL_INDEX_MASK) >> TSW_CENTRAL_QCI_METERSEL_INDEX_SHIFT)

/* Bitfield definition for register: CENTRAL_QCI_GATESEL */
/*
 * INDEX (R/W)
 *
 * Gate select index
 * Any written value larger than the maximum index
 * (2**GTD-1) will result in a read-back value of <0>.
 */
#define TSW_CENTRAL_QCI_GATESEL_INDEX_MASK (0xFFU)
#define TSW_CENTRAL_QCI_GATESEL_INDEX_SHIFT (0U)
#define TSW_CENTRAL_QCI_GATESEL_INDEX_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_GATESEL_INDEX_SHIFT) & TSW_CENTRAL_QCI_GATESEL_INDEX_MASK)
#define TSW_CENTRAL_QCI_GATESEL_INDEX_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_GATESEL_INDEX_MASK) >> TSW_CENTRAL_QCI_GATESEL_INDEX_SHIFT)

/* Bitfield definition for register: CENTRAL_QCI_FCTRL */
/*
 * ENBLK (R/W)
 *
 * Enable blocking of oversized frames
 * (802.1Qci – 8.6.5.1.1 (g))
 */
#define TSW_CENTRAL_QCI_FCTRL_ENBLK_MASK (0x80000000UL)
#define TSW_CENTRAL_QCI_FCTRL_ENBLK_SHIFT (31U)
#define TSW_CENTRAL_QCI_FCTRL_ENBLK_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_FCTRL_ENBLK_SHIFT) & TSW_CENTRAL_QCI_FCTRL_ENBLK_MASK)
#define TSW_CENTRAL_QCI_FCTRL_ENBLK_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_FCTRL_ENBLK_MASK) >> TSW_CENTRAL_QCI_FCTRL_ENBLK_SHIFT)

/*
 * ENFSZ (R/W)
 *
 * 0: No frame size check
 * 1: Frame size checking, size defined by FSIZE.MXSZ
 * (802.1Qci – 8.6.5.1.1 (e.1))
 */
#define TSW_CENTRAL_QCI_FCTRL_ENFSZ_MASK (0x40000000UL)
#define TSW_CENTRAL_QCI_FCTRL_ENFSZ_SHIFT (30U)
#define TSW_CENTRAL_QCI_FCTRL_ENFSZ_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_FCTRL_ENFSZ_SHIFT) & TSW_CENTRAL_QCI_FCTRL_ENFSZ_MASK)
#define TSW_CENTRAL_QCI_FCTRL_ENFSZ_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_FCTRL_ENFSZ_MASK) >> TSW_CENTRAL_QCI_FCTRL_ENFSZ_SHIFT)

/*
 * ENFID (R/W)
 *
 * 0: No Flow Meter
 * 1: Enable Flow Metering
 * (802.1Qci – 8.6.5.1.1 (e.2))
 */
#define TSW_CENTRAL_QCI_FCTRL_ENFID_MASK (0x20000000UL)
#define TSW_CENTRAL_QCI_FCTRL_ENFID_SHIFT (29U)
#define TSW_CENTRAL_QCI_FCTRL_ENFID_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_FCTRL_ENFID_SHIFT) & TSW_CENTRAL_QCI_FCTRL_ENFID_MASK)
#define TSW_CENTRAL_QCI_FCTRL_ENFID_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_FCTRL_ENFID_MASK) >> TSW_CENTRAL_QCI_FCTRL_ENFID_SHIFT)

/*
 * ENSID (R/W)
 *
 * 0: Filter match any SID value
 * 1: Filter match SID value
 * (802.1Qci – 8.6.5.1.1 (b))
 */
#define TSW_CENTRAL_QCI_FCTRL_ENSID_MASK (0x10000000UL)
#define TSW_CENTRAL_QCI_FCTRL_ENSID_SHIFT (28U)
#define TSW_CENTRAL_QCI_FCTRL_ENSID_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_FCTRL_ENSID_SHIFT) & TSW_CENTRAL_QCI_FCTRL_ENSID_MASK)
#define TSW_CENTRAL_QCI_FCTRL_ENSID_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_FCTRL_ENSID_MASK) >> TSW_CENTRAL_QCI_FCTRL_ENSID_SHIFT)

/*
 * ENPCP (R/W)
 *
 * 0: Filter match any PCP value
 * 1: Filter match PCP value
 * (802.1Qci – 8.6.5.1.1 (c))
 */
#define TSW_CENTRAL_QCI_FCTRL_ENPCP_MASK (0x8000000UL)
#define TSW_CENTRAL_QCI_FCTRL_ENPCP_SHIFT (27U)
#define TSW_CENTRAL_QCI_FCTRL_ENPCP_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_FCTRL_ENPCP_SHIFT) & TSW_CENTRAL_QCI_FCTRL_ENPCP_MASK)
#define TSW_CENTRAL_QCI_FCTRL_ENPCP_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_FCTRL_ENPCP_MASK) >> TSW_CENTRAL_QCI_FCTRL_ENPCP_SHIFT)

/*
 * PCP (R/W)
 *
 * Filter priority code point, if enabled by ENPCP
 */
#define TSW_CENTRAL_QCI_FCTRL_PCP_MASK (0x7000000UL)
#define TSW_CENTRAL_QCI_FCTRL_PCP_SHIFT (24U)
#define TSW_CENTRAL_QCI_FCTRL_PCP_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_FCTRL_PCP_SHIFT) & TSW_CENTRAL_QCI_FCTRL_PCP_MASK)
#define TSW_CENTRAL_QCI_FCTRL_PCP_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_FCTRL_PCP_MASK) >> TSW_CENTRAL_QCI_FCTRL_PCP_SHIFT)

/*
 * FMD (R/W)
 *
 * Associated Flow Meter – if enabled by ENFID
 */
#define TSW_CENTRAL_QCI_FCTRL_FMD_MASK (0xFF0000UL)
#define TSW_CENTRAL_QCI_FCTRL_FMD_SHIFT (16U)
#define TSW_CENTRAL_QCI_FCTRL_FMD_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_FCTRL_FMD_SHIFT) & TSW_CENTRAL_QCI_FCTRL_FMD_MASK)
#define TSW_CENTRAL_QCI_FCTRL_FMD_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_FCTRL_FMD_MASK) >> TSW_CENTRAL_QCI_FCTRL_FMD_SHIFT)

/*
 * GID (R/W)
 *
 * Associated Gate
 */
#define TSW_CENTRAL_QCI_FCTRL_GID_MASK (0xFF00U)
#define TSW_CENTRAL_QCI_FCTRL_GID_SHIFT (8U)
#define TSW_CENTRAL_QCI_FCTRL_GID_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_FCTRL_GID_SHIFT) & TSW_CENTRAL_QCI_FCTRL_GID_MASK)
#define TSW_CENTRAL_QCI_FCTRL_GID_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_FCTRL_GID_MASK) >> TSW_CENTRAL_QCI_FCTRL_GID_SHIFT)

/*
 * SID (R/W)
 *
 * Filter Stream ID – if enabled by ENSID
 */
#define TSW_CENTRAL_QCI_FCTRL_SID_MASK (0xFFU)
#define TSW_CENTRAL_QCI_FCTRL_SID_SHIFT (0U)
#define TSW_CENTRAL_QCI_FCTRL_SID_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_FCTRL_SID_SHIFT) & TSW_CENTRAL_QCI_FCTRL_SID_MASK)
#define TSW_CENTRAL_QCI_FCTRL_SID_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_FCTRL_SID_MASK) >> TSW_CENTRAL_QCI_FCTRL_SID_SHIFT)

/* Bitfield definition for register: CENTRAL_QCI_FSIZE */
/*
 * BLK (R/WC)
 *
 * Stream blocked due to oversize frame.
 * Write <1> to clear.
 * (802.1Qci – 8.6.5.1.1 (h))
 */
#define TSW_CENTRAL_QCI_FSIZE_BLK_MASK (0x80000000UL)
#define TSW_CENTRAL_QCI_FSIZE_BLK_SHIFT (31U)
#define TSW_CENTRAL_QCI_FSIZE_BLK_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_FSIZE_BLK_SHIFT) & TSW_CENTRAL_QCI_FSIZE_BLK_MASK)
#define TSW_CENTRAL_QCI_FSIZE_BLK_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_FSIZE_BLK_MASK) >> TSW_CENTRAL_QCI_FSIZE_BLK_SHIFT)

/*
 * MXSZ (R/W)
 *
 * Maximum-SDU size in octets
 */
#define TSW_CENTRAL_QCI_FSIZE_MXSZ_MASK (0xFFFFU)
#define TSW_CENTRAL_QCI_FSIZE_MXSZ_SHIFT (0U)
#define TSW_CENTRAL_QCI_FSIZE_MXSZ_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_FSIZE_MXSZ_SHIFT) & TSW_CENTRAL_QCI_FSIZE_MXSZ_MASK)
#define TSW_CENTRAL_QCI_FSIZE_MXSZ_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_FSIZE_MXSZ_MASK) >> TSW_CENTRAL_QCI_FSIZE_MXSZ_SHIFT)

/* Bitfield definition for register array: QCI_CNT */
/*
 * VALUE (RO)
 *
 * Filter counter (see 802.1Qci 8.6.5.1.1 f)
 * CNT0: Frames that matched filter
 * CNT1: Frames that passed gate
 * CNT2: Frames that did not pass gate
 * CNT3: Frames that passed Maximum-SDU size check
 * CNT4: Frames that did not pass size check
 * CNT5: Frames discarded by Flow Meter operation
 * Counters starting at value <0> after reset.
 */
#define TSW_QCI_CNT_VALUE_MASK (0xFFFFFFFFUL)
#define TSW_QCI_CNT_VALUE_SHIFT (0U)
#define TSW_QCI_CNT_VALUE_GET(x) (((uint32_t)(x) & TSW_QCI_CNT_VALUE_MASK) >> TSW_QCI_CNT_VALUE_SHIFT)

/* Bitfield definition for register: CENTRAL_QCI_MCTRL */
/*
 * RESET (WO)
 *
 * Flow Meter reset – self-resetting to <0>
 */
#define TSW_CENTRAL_QCI_MCTRL_RESET_MASK (0x80000000UL)
#define TSW_CENTRAL_QCI_MCTRL_RESET_SHIFT (31U)
#define TSW_CENTRAL_QCI_MCTRL_RESET_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_MCTRL_RESET_SHIFT) & TSW_CENTRAL_QCI_MCTRL_RESET_MASK)
#define TSW_CENTRAL_QCI_MCTRL_RESET_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_MCTRL_RESET_MASK) >> TSW_CENTRAL_QCI_MCTRL_RESET_SHIFT)

/*
 * MAFR (RO)
 *
 * MarkAllFramesRed – cleared by RESET
 * (802.1Qci – 8.6.5.1.3 (j))
 */
#define TSW_CENTRAL_QCI_MCTRL_MAFR_MASK (0x10U)
#define TSW_CENTRAL_QCI_MCTRL_MAFR_SHIFT (4U)
#define TSW_CENTRAL_QCI_MCTRL_MAFR_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_MCTRL_MAFR_MASK) >> TSW_CENTRAL_QCI_MCTRL_MAFR_SHIFT)

/*
 * MAFREN (R/W)
 *
 * MarkAllFramesRedEnable
 * (802.1Qci – 8.6.5.1.3 (i))
 */
#define TSW_CENTRAL_QCI_MCTRL_MAFREN_MASK (0x8U)
#define TSW_CENTRAL_QCI_MCTRL_MAFREN_SHIFT (3U)
#define TSW_CENTRAL_QCI_MCTRL_MAFREN_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_MCTRL_MAFREN_SHIFT) & TSW_CENTRAL_QCI_MCTRL_MAFREN_MASK)
#define TSW_CENTRAL_QCI_MCTRL_MAFREN_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_MCTRL_MAFREN_MASK) >> TSW_CENTRAL_QCI_MCTRL_MAFREN_SHIFT)

/*
 * DOY (R/W)
 *
 * DropOnYellow
 * (802.1Qci – 8.6.5.1.3 (h))
 */
#define TSW_CENTRAL_QCI_MCTRL_DOY_MASK (0x4U)
#define TSW_CENTRAL_QCI_MCTRL_DOY_SHIFT (2U)
#define TSW_CENTRAL_QCI_MCTRL_DOY_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_MCTRL_DOY_SHIFT) & TSW_CENTRAL_QCI_MCTRL_DOY_MASK)
#define TSW_CENTRAL_QCI_MCTRL_DOY_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_MCTRL_DOY_MASK) >> TSW_CENTRAL_QCI_MCTRL_DOY_SHIFT)

/*
 * CM (R/W)
 *
 * Color mode – functionally unused
 * (802.1Qci – 8.6.5.1.3 (g))
 */
#define TSW_CENTRAL_QCI_MCTRL_CM_MASK (0x2U)
#define TSW_CENTRAL_QCI_MCTRL_CM_SHIFT (1U)
#define TSW_CENTRAL_QCI_MCTRL_CM_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_MCTRL_CM_SHIFT) & TSW_CENTRAL_QCI_MCTRL_CM_MASK)
#define TSW_CENTRAL_QCI_MCTRL_CM_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_MCTRL_CM_MASK) >> TSW_CENTRAL_QCI_MCTRL_CM_SHIFT)

/*
 * CF (R/W)
 *
 * Coupling flag
 * (802.1Qci – 8.6.5.1.3 (f))
 */
#define TSW_CENTRAL_QCI_MCTRL_CF_MASK (0x1U)
#define TSW_CENTRAL_QCI_MCTRL_CF_SHIFT (0U)
#define TSW_CENTRAL_QCI_MCTRL_CF_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_MCTRL_CF_SHIFT) & TSW_CENTRAL_QCI_MCTRL_CF_MASK)
#define TSW_CENTRAL_QCI_MCTRL_CF_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_MCTRL_CF_MASK) >> TSW_CENTRAL_QCI_MCTRL_CF_SHIFT)

/* Bitfield definition for register: CENTRAL_QCI_CIR */
/*
 * CIR (R/W)
 *
 * Committed information rate – see Chapter 7.5.2.4.
 * (802.1Qci – 8.6.5.1.3 (b))
 */
#define TSW_CENTRAL_QCI_CIR_CIR_MASK (0xFFFFFFUL)
#define TSW_CENTRAL_QCI_CIR_CIR_SHIFT (0U)
#define TSW_CENTRAL_QCI_CIR_CIR_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_CIR_CIR_SHIFT) & TSW_CENTRAL_QCI_CIR_CIR_MASK)
#define TSW_CENTRAL_QCI_CIR_CIR_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_CIR_CIR_MASK) >> TSW_CENTRAL_QCI_CIR_CIR_SHIFT)

/* Bitfield definition for register: CENTRAL_QCI_CBS */
/*
 * CBS (R/W)
 *
 * Committed burst size, in bits (not octets!)
 * (802.1Qci – 8.6.5.1.3 (c))
 */
#define TSW_CENTRAL_QCI_CBS_CBS_MASK (0xFFFFFFFFUL)
#define TSW_CENTRAL_QCI_CBS_CBS_SHIFT (0U)
#define TSW_CENTRAL_QCI_CBS_CBS_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_CBS_CBS_SHIFT) & TSW_CENTRAL_QCI_CBS_CBS_MASK)
#define TSW_CENTRAL_QCI_CBS_CBS_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_CBS_CBS_MASK) >> TSW_CENTRAL_QCI_CBS_CBS_SHIFT)

/* Bitfield definition for register: CENTRAL_QCI_EIR */
/*
 * EIR (R/W)
 *
 * Excess information rate – see Chapter 7.5.2.4.
 * (802.1Qci – 8.6.5.1.3 (d))
 */
#define TSW_CENTRAL_QCI_EIR_EIR_MASK (0xFFFFFFUL)
#define TSW_CENTRAL_QCI_EIR_EIR_SHIFT (0U)
#define TSW_CENTRAL_QCI_EIR_EIR_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_EIR_EIR_SHIFT) & TSW_CENTRAL_QCI_EIR_EIR_MASK)
#define TSW_CENTRAL_QCI_EIR_EIR_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_EIR_EIR_MASK) >> TSW_CENTRAL_QCI_EIR_EIR_SHIFT)

/* Bitfield definition for register: CENTRAL_QCI_EBS */
/*
 * EBS (R/W)
 *
 * Excess burst size, in bits (not octets)
 * (802.1Qci – 8.6.5.1.3 (e))
 */
#define TSW_CENTRAL_QCI_EBS_EBS_MASK (0xFFFFFFFFUL)
#define TSW_CENTRAL_QCI_EBS_EBS_SHIFT (0U)
#define TSW_CENTRAL_QCI_EBS_EBS_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_EBS_EBS_SHIFT) & TSW_CENTRAL_QCI_EBS_EBS_MASK)
#define TSW_CENTRAL_QCI_EBS_EBS_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_EBS_EBS_MASK) >> TSW_CENTRAL_QCI_EBS_EBS_SHIFT)

/* Bitfield definition for register: CENTRAL_QCI_GCTRL */
/*
 * IPV (R/W)
 *
 * Administrative internal priority value specification
 * (802.1Qci – 8.6.5.1.2 (c))
 */
#define TSW_CENTRAL_QCI_GCTRL_IPV_MASK (0xE0U)
#define TSW_CENTRAL_QCI_GCTRL_IPV_SHIFT (5U)
#define TSW_CENTRAL_QCI_GCTRL_IPV_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_GCTRL_IPV_SHIFT) & TSW_CENTRAL_QCI_GCTRL_IPV_MASK)
#define TSW_CENTRAL_QCI_GCTRL_IPV_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_GCTRL_IPV_MASK) >> TSW_CENTRAL_QCI_GCTRL_IPV_SHIFT)

/*
 * STATE (R/W)
 *
 * Administrative stream gate state
 * (802.1Qci – 8.6.5.1.2 (b))
 */
#define TSW_CENTRAL_QCI_GCTRL_STATE_MASK (0x10U)
#define TSW_CENTRAL_QCI_GCTRL_STATE_SHIFT (4U)
#define TSW_CENTRAL_QCI_GCTRL_STATE_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_GCTRL_STATE_SHIFT) & TSW_CENTRAL_QCI_GCTRL_STATE_MASK)
#define TSW_CENTRAL_QCI_GCTRL_STATE_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_GCTRL_STATE_MASK) >> TSW_CENTRAL_QCI_GCTRL_STATE_SHIFT)

/*
 * CDOEE (R/W)
 *
 * Gate – ClosedDueToOctetsExceededEnable
 * (802.1Qci – 8.6.5.1.2 (f))
 */
#define TSW_CENTRAL_QCI_GCTRL_CDOEE_MASK (0x8U)
#define TSW_CENTRAL_QCI_GCTRL_CDOEE_SHIFT (3U)
#define TSW_CENTRAL_QCI_GCTRL_CDOEE_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_GCTRL_CDOEE_SHIFT) & TSW_CENTRAL_QCI_GCTRL_CDOEE_MASK)
#define TSW_CENTRAL_QCI_GCTRL_CDOEE_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_GCTRL_CDOEE_MASK) >> TSW_CENTRAL_QCI_GCTRL_CDOEE_SHIFT)

/*
 * CDIRE (R/W)
 *
 * Gate – ClosedDueToInvalidRxEnable
 * (802.1Qci – 8.6.5.1.2 (d))
 */
#define TSW_CENTRAL_QCI_GCTRL_CDIRE_MASK (0x4U)
#define TSW_CENTRAL_QCI_GCTRL_CDIRE_SHIFT (2U)
#define TSW_CENTRAL_QCI_GCTRL_CDIRE_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_GCTRL_CDIRE_SHIFT) & TSW_CENTRAL_QCI_GCTRL_CDIRE_MASK)
#define TSW_CENTRAL_QCI_GCTRL_CDIRE_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_GCTRL_CDIRE_MASK) >> TSW_CENTRAL_QCI_GCTRL_CDIRE_SHIFT)

/*
 * CFGCH (R/W)
 *
 * Gate – change config (self-resetting to <0>)
 */
#define TSW_CENTRAL_QCI_GCTRL_CFGCH_MASK (0x2U)
#define TSW_CENTRAL_QCI_GCTRL_CFGCH_SHIFT (1U)
#define TSW_CENTRAL_QCI_GCTRL_CFGCH_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_GCTRL_CFGCH_SHIFT) & TSW_CENTRAL_QCI_GCTRL_CFGCH_MASK)
#define TSW_CENTRAL_QCI_GCTRL_CFGCH_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_GCTRL_CFGCH_MASK) >> TSW_CENTRAL_QCI_GCTRL_CFGCH_SHIFT)

/*
 * EN (R/W)
 *
 * Gate control – enable
 */
#define TSW_CENTRAL_QCI_GCTRL_EN_MASK (0x1U)
#define TSW_CENTRAL_QCI_GCTRL_EN_SHIFT (0U)
#define TSW_CENTRAL_QCI_GCTRL_EN_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_GCTRL_EN_SHIFT) & TSW_CENTRAL_QCI_GCTRL_EN_MASK)
#define TSW_CENTRAL_QCI_GCTRL_EN_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_GCTRL_EN_MASK) >> TSW_CENTRAL_QCI_GCTRL_EN_SHIFT)

/* Bitfield definition for register: CENTRAL_QCI_GSTATUS */
/*
 * IPV (RO)
 *
 * Operational internal priority value specification
 * (802.1Qci – 8.6.5.1.2 (c))
 */
#define TSW_CENTRAL_QCI_GSTATUS_IPV_MASK (0xE0U)
#define TSW_CENTRAL_QCI_GSTATUS_IPV_SHIFT (5U)
#define TSW_CENTRAL_QCI_GSTATUS_IPV_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_GSTATUS_IPV_MASK) >> TSW_CENTRAL_QCI_GSTATUS_IPV_SHIFT)

/*
 * STATE (RO)
 *
 * Operational stream gate state
 * (802.1Qci – 8.6.5.1.2 (b))
 */
#define TSW_CENTRAL_QCI_GSTATUS_STATE_MASK (0x10U)
#define TSW_CENTRAL_QCI_GSTATUS_STATE_SHIFT (4U)
#define TSW_CENTRAL_QCI_GSTATUS_STATE_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_GSTATUS_STATE_MASK) >> TSW_CENTRAL_QCI_GSTATUS_STATE_SHIFT)

/*
 * CDOE (WC)
 *
 * Gate – ClosedDueToOctetsExceeded. Write <1> to
 * clear.
 * (802.1Qci – 8.6.5.1.2 (g))
 */
#define TSW_CENTRAL_QCI_GSTATUS_CDOE_MASK (0x8U)
#define TSW_CENTRAL_QCI_GSTATUS_CDOE_SHIFT (3U)
#define TSW_CENTRAL_QCI_GSTATUS_CDOE_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_GSTATUS_CDOE_SHIFT) & TSW_CENTRAL_QCI_GSTATUS_CDOE_MASK)
#define TSW_CENTRAL_QCI_GSTATUS_CDOE_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_GSTATUS_CDOE_MASK) >> TSW_CENTRAL_QCI_GSTATUS_CDOE_SHIFT)

/*
 * CDIR (WC)
 *
 * Gate – ClosedDueToInvalidRx. Write <1> to clear.
 * (802.1Qci – 8.6.5.1.2 (e))
 */
#define TSW_CENTRAL_QCI_GSTATUS_CDIR_MASK (0x4U)
#define TSW_CENTRAL_QCI_GSTATUS_CDIR_SHIFT (2U)
#define TSW_CENTRAL_QCI_GSTATUS_CDIR_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_GSTATUS_CDIR_SHIFT) & TSW_CENTRAL_QCI_GSTATUS_CDIR_MASK)
#define TSW_CENTRAL_QCI_GSTATUS_CDIR_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_GSTATUS_CDIR_MASK) >> TSW_CENTRAL_QCI_GSTATUS_CDIR_SHIFT)

/*
 * CFGP (RO)
 *
 * Configuration change pending
 */
#define TSW_CENTRAL_QCI_GSTATUS_CFGP_MASK (0x2U)
#define TSW_CENTRAL_QCI_GSTATUS_CFGP_SHIFT (1U)
#define TSW_CENTRAL_QCI_GSTATUS_CFGP_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_GSTATUS_CFGP_MASK) >> TSW_CENTRAL_QCI_GSTATUS_CFGP_SHIFT)

/*
 * CFGERR (WC)
 *
 * Configuration change error. Write <1> to clear.
 */
#define TSW_CENTRAL_QCI_GSTATUS_CFGERR_MASK (0x1U)
#define TSW_CENTRAL_QCI_GSTATUS_CFGERR_SHIFT (0U)
#define TSW_CENTRAL_QCI_GSTATUS_CFGERR_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_GSTATUS_CFGERR_SHIFT) & TSW_CENTRAL_QCI_GSTATUS_CFGERR_MASK)
#define TSW_CENTRAL_QCI_GSTATUS_CFGERR_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_GSTATUS_CFGERR_MASK) >> TSW_CENTRAL_QCI_GSTATUS_CFGERR_SHIFT)

/* Bitfield definition for register: CENTRAL_QCI_GLISTINDEX */
/*
 * IDX (R/W)
 *
 * Admin list pointer, select entry 0 – 15.
 */
#define TSW_CENTRAL_QCI_GLISTINDEX_IDX_MASK (0xFU)
#define TSW_CENTRAL_QCI_GLISTINDEX_IDX_SHIFT (0U)
#define TSW_CENTRAL_QCI_GLISTINDEX_IDX_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_GLISTINDEX_IDX_SHIFT) & TSW_CENTRAL_QCI_GLISTINDEX_IDX_MASK)
#define TSW_CENTRAL_QCI_GLISTINDEX_IDX_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_GLISTINDEX_IDX_MASK) >> TSW_CENTRAL_QCI_GLISTINDEX_IDX_SHIFT)

/* Bitfield definition for register: CENTRAL_QCI_LISTLEN */
/*
 * OLEN (RO)
 *
 * Operational list length
 */
#define TSW_CENTRAL_QCI_LISTLEN_OLEN_MASK (0xF0000UL)
#define TSW_CENTRAL_QCI_LISTLEN_OLEN_SHIFT (16U)
#define TSW_CENTRAL_QCI_LISTLEN_OLEN_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_LISTLEN_OLEN_MASK) >> TSW_CENTRAL_QCI_LISTLEN_OLEN_SHIFT)

/*
 * ALEN (R/W)
 *
 * Administrative list length
 */
#define TSW_CENTRAL_QCI_LISTLEN_ALEN_MASK (0xFU)
#define TSW_CENTRAL_QCI_LISTLEN_ALEN_SHIFT (0U)
#define TSW_CENTRAL_QCI_LISTLEN_ALEN_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_LISTLEN_ALEN_SHIFT) & TSW_CENTRAL_QCI_LISTLEN_ALEN_MASK)
#define TSW_CENTRAL_QCI_LISTLEN_ALEN_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_LISTLEN_ALEN_MASK) >> TSW_CENTRAL_QCI_LISTLEN_ALEN_SHIFT)

/* Bitfield definition for register: CENTRAL_QCI_ACYCLETM */
/*
 * ACT (R/W)
 *
 * Administrative cycle time length, nanoseconds.
 */
#define TSW_CENTRAL_QCI_ACYCLETM_ACT_MASK (0x3FFFFFFFUL)
#define TSW_CENTRAL_QCI_ACYCLETM_ACT_SHIFT (0U)
#define TSW_CENTRAL_QCI_ACYCLETM_ACT_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_ACYCLETM_ACT_SHIFT) & TSW_CENTRAL_QCI_ACYCLETM_ACT_MASK)
#define TSW_CENTRAL_QCI_ACYCLETM_ACT_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_ACYCLETM_ACT_MASK) >> TSW_CENTRAL_QCI_ACYCLETM_ACT_SHIFT)

/* Bitfield definition for register: CENTRAL_QCI_ABASETM_L */
/*
 * ABTL (R/W)
 *
 * Administrative base time. Nanoseconds and seconds part. Cycle starts after becoming operational when time is reached by inputs <rtc_sec> and <rtc_ns>.
 */
#define TSW_CENTRAL_QCI_ABASETM_L_ABTL_MASK (0x3FFFFFFFUL)
#define TSW_CENTRAL_QCI_ABASETM_L_ABTL_SHIFT (0U)
#define TSW_CENTRAL_QCI_ABASETM_L_ABTL_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_ABASETM_L_ABTL_SHIFT) & TSW_CENTRAL_QCI_ABASETM_L_ABTL_MASK)
#define TSW_CENTRAL_QCI_ABASETM_L_ABTL_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_ABASETM_L_ABTL_MASK) >> TSW_CENTRAL_QCI_ABASETM_L_ABTL_SHIFT)

/* Bitfield definition for register: CENTRAL_QCI_ABASETM_H */
/*
 * ABTH (R/W)
 *
 */
#define TSW_CENTRAL_QCI_ABASETM_H_ABTH_MASK (0xFFFFFFFFUL)
#define TSW_CENTRAL_QCI_ABASETM_H_ABTH_SHIFT (0U)
#define TSW_CENTRAL_QCI_ABASETM_H_ABTH_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_ABASETM_H_ABTH_SHIFT) & TSW_CENTRAL_QCI_ABASETM_H_ABTH_MASK)
#define TSW_CENTRAL_QCI_ABASETM_H_ABTH_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_ABASETM_H_ABTH_MASK) >> TSW_CENTRAL_QCI_ABASETM_H_ABTH_SHIFT)

/* Bitfield definition for register: CENTRAL_QCI_AENTRY_CTRL */
/*
 * STATE (R/W)
 *
 * AdminList – gate state (1: open)
 */
#define TSW_CENTRAL_QCI_AENTRY_CTRL_STATE_MASK (0x80000000UL)
#define TSW_CENTRAL_QCI_AENTRY_CTRL_STATE_SHIFT (31U)
#define TSW_CENTRAL_QCI_AENTRY_CTRL_STATE_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_AENTRY_CTRL_STATE_SHIFT) & TSW_CENTRAL_QCI_AENTRY_CTRL_STATE_MASK)
#define TSW_CENTRAL_QCI_AENTRY_CTRL_STATE_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_AENTRY_CTRL_STATE_MASK) >> TSW_CENTRAL_QCI_AENTRY_CTRL_STATE_SHIFT)

/*
 * IPV (R/W)
 *
 * AdminList – IPV
 */
#define TSW_CENTRAL_QCI_AENTRY_CTRL_IPV_MASK (0x70000000UL)
#define TSW_CENTRAL_QCI_AENTRY_CTRL_IPV_SHIFT (28U)
#define TSW_CENTRAL_QCI_AENTRY_CTRL_IPV_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_AENTRY_CTRL_IPV_SHIFT) & TSW_CENTRAL_QCI_AENTRY_CTRL_IPV_MASK)
#define TSW_CENTRAL_QCI_AENTRY_CTRL_IPV_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_AENTRY_CTRL_IPV_MASK) >> TSW_CENTRAL_QCI_AENTRY_CTRL_IPV_SHIFT)

/*
 * OCT (R/W)
 *
 * AdminList – maximum octets (0 – disabled)
 */
#define TSW_CENTRAL_QCI_AENTRY_CTRL_OCT_MASK (0xFFFFFFFUL)
#define TSW_CENTRAL_QCI_AENTRY_CTRL_OCT_SHIFT (0U)
#define TSW_CENTRAL_QCI_AENTRY_CTRL_OCT_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_AENTRY_CTRL_OCT_SHIFT) & TSW_CENTRAL_QCI_AENTRY_CTRL_OCT_MASK)
#define TSW_CENTRAL_QCI_AENTRY_CTRL_OCT_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_AENTRY_CTRL_OCT_MASK) >> TSW_CENTRAL_QCI_AENTRY_CTRL_OCT_SHIFT)

/* Bitfield definition for register: CENTRAL_QCI_AENTRY_AENTRY_IVAL */
/*
 * IVAL (R/W)
 *
 * AdminList – time interval in clock ticks
 */
#define TSW_CENTRAL_QCI_AENTRY_AENTRY_IVAL_IVAL_MASK (0xFFFFFFFFUL)
#define TSW_CENTRAL_QCI_AENTRY_AENTRY_IVAL_IVAL_SHIFT (0U)
#define TSW_CENTRAL_QCI_AENTRY_AENTRY_IVAL_IVAL_SET(x) (((uint32_t)(x) << TSW_CENTRAL_QCI_AENTRY_AENTRY_IVAL_IVAL_SHIFT) & TSW_CENTRAL_QCI_AENTRY_AENTRY_IVAL_IVAL_MASK)
#define TSW_CENTRAL_QCI_AENTRY_AENTRY_IVAL_IVAL_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_AENTRY_AENTRY_IVAL_IVAL_MASK) >> TSW_CENTRAL_QCI_AENTRY_AENTRY_IVAL_IVAL_SHIFT)

/* Bitfield definition for register: CENTRAL_QCI_AENTRY_OCYCLETM */
/*
 * OCT (RO)
 *
 * OperCycleTime in nanoseconds
 */
#define TSW_CENTRAL_QCI_AENTRY_OCYCLETM_OCT_MASK (0xFFFFFFFFUL)
#define TSW_CENTRAL_QCI_AENTRY_OCYCLETM_OCT_SHIFT (0U)
#define TSW_CENTRAL_QCI_AENTRY_OCYCLETM_OCT_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_AENTRY_OCYCLETM_OCT_MASK) >> TSW_CENTRAL_QCI_AENTRY_OCYCLETM_OCT_SHIFT)

/* Bitfield definition for register: CENTRAL_QCI_AENTRY_OBASETM_L */
/*
 * OBTL (RO)
 *
 * OperBaseTime – nanoseconds and seconds. Constantly
 * updated – OperBaseTime + N * OperCycleTimt. Might
 * be non-normalized.
 */
#define TSW_CENTRAL_QCI_AENTRY_OBASETM_L_OBTL_MASK (0xFFFFFFFFUL)
#define TSW_CENTRAL_QCI_AENTRY_OBASETM_L_OBTL_SHIFT (0U)
#define TSW_CENTRAL_QCI_AENTRY_OBASETM_L_OBTL_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_AENTRY_OBASETM_L_OBTL_MASK) >> TSW_CENTRAL_QCI_AENTRY_OBASETM_L_OBTL_SHIFT)

/* Bitfield definition for register: CENTRAL_QCI_AENTRY_OBASETM_H */
/*
 * OBTH (RO)
 *
 */
#define TSW_CENTRAL_QCI_AENTRY_OBASETM_H_OBTH_MASK (0xFFFFFFFFUL)
#define TSW_CENTRAL_QCI_AENTRY_OBASETM_H_OBTH_SHIFT (0U)
#define TSW_CENTRAL_QCI_AENTRY_OBASETM_H_OBTH_GET(x) (((uint32_t)(x) & TSW_CENTRAL_QCI_AENTRY_OBASETM_H_OBTH_MASK) >> TSW_CENTRAL_QCI_AENTRY_OBASETM_H_OBTH_SHIFT)

/* Bitfield definition for register: MM2S_DMA_CR */
/*
 * MXLEN (RW)
 *
 * max axi burst size
 */
#define TSW_MM2S_DMA_CR_MXLEN_MASK (0xFF000000UL)
#define TSW_MM2S_DMA_CR_MXLEN_SHIFT (24U)
#define TSW_MM2S_DMA_CR_MXLEN_SET(x) (((uint32_t)(x) << TSW_MM2S_DMA_CR_MXLEN_SHIFT) & TSW_MM2S_DMA_CR_MXLEN_MASK)
#define TSW_MM2S_DMA_CR_MXLEN_GET(x) (((uint32_t)(x) & TSW_MM2S_DMA_CR_MXLEN_MASK) >> TSW_MM2S_DMA_CR_MXLEN_SHIFT)

/*
 * IRQEN (RW)
 *
 * interrupt request enable
 */
#define TSW_MM2S_DMA_CR_IRQEN_MASK (0x8U)
#define TSW_MM2S_DMA_CR_IRQEN_SHIFT (3U)
#define TSW_MM2S_DMA_CR_IRQEN_SET(x) (((uint32_t)(x) << TSW_MM2S_DMA_CR_IRQEN_SHIFT) & TSW_MM2S_DMA_CR_IRQEN_MASK)
#define TSW_MM2S_DMA_CR_IRQEN_GET(x) (((uint32_t)(x) & TSW_MM2S_DMA_CR_IRQEN_MASK) >> TSW_MM2S_DMA_CR_IRQEN_SHIFT)

/*
 * RESET (WO)
 *
 * do reset when active
 */
#define TSW_MM2S_DMA_CR_RESET_MASK (0x4U)
#define TSW_MM2S_DMA_CR_RESET_SHIFT (2U)
#define TSW_MM2S_DMA_CR_RESET_SET(x) (((uint32_t)(x) << TSW_MM2S_DMA_CR_RESET_SHIFT) & TSW_MM2S_DMA_CR_RESET_MASK)
#define TSW_MM2S_DMA_CR_RESET_GET(x) (((uint32_t)(x) & TSW_MM2S_DMA_CR_RESET_MASK) >> TSW_MM2S_DMA_CR_RESET_SHIFT)

/*
 * SOE (RW)
 *
 * stop on error flag
 */
#define TSW_MM2S_DMA_CR_SOE_MASK (0x2U)
#define TSW_MM2S_DMA_CR_SOE_SHIFT (1U)
#define TSW_MM2S_DMA_CR_SOE_SET(x) (((uint32_t)(x) << TSW_MM2S_DMA_CR_SOE_SHIFT) & TSW_MM2S_DMA_CR_SOE_MASK)
#define TSW_MM2S_DMA_CR_SOE_GET(x) (((uint32_t)(x) & TSW_MM2S_DMA_CR_SOE_MASK) >> TSW_MM2S_DMA_CR_SOE_SHIFT)

/*
 * RUN (RW)
 *
 * run command from queue to data mover
 */
#define TSW_MM2S_DMA_CR_RUN_MASK (0x1U)
#define TSW_MM2S_DMA_CR_RUN_SHIFT (0U)
#define TSW_MM2S_DMA_CR_RUN_SET(x) (((uint32_t)(x) << TSW_MM2S_DMA_CR_RUN_SHIFT) & TSW_MM2S_DMA_CR_RUN_MASK)
#define TSW_MM2S_DMA_CR_RUN_GET(x) (((uint32_t)(x) & TSW_MM2S_DMA_CR_RUN_MASK) >> TSW_MM2S_DMA_CR_RUN_SHIFT)

/* Bitfield definition for register: MM2S_DMA_SR */
/*
 * RBUFF (RO)
 *
 * response buffer full
 */
#define TSW_MM2S_DMA_SR_RBUFF_MASK (0x80U)
#define TSW_MM2S_DMA_SR_RBUFF_SHIFT (7U)
#define TSW_MM2S_DMA_SR_RBUFF_GET(x) (((uint32_t)(x) & TSW_MM2S_DMA_SR_RBUFF_MASK) >> TSW_MM2S_DMA_SR_RBUFF_SHIFT)

/*
 * RBUFE (RO)
 *
 * response buffer empty
 */
#define TSW_MM2S_DMA_SR_RBUFE_MASK (0x40U)
#define TSW_MM2S_DMA_SR_RBUFE_SHIFT (6U)
#define TSW_MM2S_DMA_SR_RBUFE_GET(x) (((uint32_t)(x) & TSW_MM2S_DMA_SR_RBUFE_MASK) >> TSW_MM2S_DMA_SR_RBUFE_SHIFT)

/*
 * CBUFF (RO)
 *
 * command buffer full
 */
#define TSW_MM2S_DMA_SR_CBUFF_MASK (0x20U)
#define TSW_MM2S_DMA_SR_CBUFF_SHIFT (5U)
#define TSW_MM2S_DMA_SR_CBUFF_GET(x) (((uint32_t)(x) & TSW_MM2S_DMA_SR_CBUFF_MASK) >> TSW_MM2S_DMA_SR_CBUFF_SHIFT)

/*
 * CBUFE (RO)
 *
 * command buffer empty
 */
#define TSW_MM2S_DMA_SR_CBUFE_MASK (0x10U)
#define TSW_MM2S_DMA_SR_CBUFE_SHIFT (4U)
#define TSW_MM2S_DMA_SR_CBUFE_GET(x) (((uint32_t)(x) & TSW_MM2S_DMA_SR_CBUFE_MASK) >> TSW_MM2S_DMA_SR_CBUFE_SHIFT)

/*
 * IRQ (RWC)
 *
 * interrupt request pending
 */
#define TSW_MM2S_DMA_SR_IRQ_MASK (0x8U)
#define TSW_MM2S_DMA_SR_IRQ_SHIFT (3U)
#define TSW_MM2S_DMA_SR_IRQ_SET(x) (((uint32_t)(x) << TSW_MM2S_DMA_SR_IRQ_SHIFT) & TSW_MM2S_DMA_SR_IRQ_MASK)
#define TSW_MM2S_DMA_SR_IRQ_GET(x) (((uint32_t)(x) & TSW_MM2S_DMA_SR_IRQ_MASK) >> TSW_MM2S_DMA_SR_IRQ_SHIFT)

/*
 * RSET (RO)
 *
 * resetting status
 */
#define TSW_MM2S_DMA_SR_RSET_MASK (0x4U)
#define TSW_MM2S_DMA_SR_RSET_SHIFT (2U)
#define TSW_MM2S_DMA_SR_RSET_GET(x) (((uint32_t)(x) & TSW_MM2S_DMA_SR_RSET_MASK) >> TSW_MM2S_DMA_SR_RSET_SHIFT)

/*
 * BUSY (RO)
 *
 * busy
 */
#define TSW_MM2S_DMA_SR_BUSY_MASK (0x2U)
#define TSW_MM2S_DMA_SR_BUSY_SHIFT (1U)
#define TSW_MM2S_DMA_SR_BUSY_GET(x) (((uint32_t)(x) & TSW_MM2S_DMA_SR_BUSY_MASK) >> TSW_MM2S_DMA_SR_BUSY_SHIFT)

/*
 * STOP (RO)
 *
 * mm2s is stopped
 */
#define TSW_MM2S_DMA_SR_STOP_MASK (0x1U)
#define TSW_MM2S_DMA_SR_STOP_SHIFT (0U)
#define TSW_MM2S_DMA_SR_STOP_GET(x) (((uint32_t)(x) & TSW_MM2S_DMA_SR_STOP_MASK) >> TSW_MM2S_DMA_SR_STOP_SHIFT)

/* Bitfield definition for register: MM2S_DMA_FILL */
/*
 * RFILL (RO)
 *
 * response buffer fill level
 */
#define TSW_MM2S_DMA_FILL_RFILL_MASK (0xFFFF0000UL)
#define TSW_MM2S_DMA_FILL_RFILL_SHIFT (16U)
#define TSW_MM2S_DMA_FILL_RFILL_GET(x) (((uint32_t)(x) & TSW_MM2S_DMA_FILL_RFILL_MASK) >> TSW_MM2S_DMA_FILL_RFILL_SHIFT)

/*
 * CFILL (RO)
 *
 * command buffer fill level
 */
#define TSW_MM2S_DMA_FILL_CFILL_MASK (0xFFFFU)
#define TSW_MM2S_DMA_FILL_CFILL_SHIFT (0U)
#define TSW_MM2S_DMA_FILL_CFILL_GET(x) (((uint32_t)(x) & TSW_MM2S_DMA_FILL_CFILL_MASK) >> TSW_MM2S_DMA_FILL_CFILL_SHIFT)

/* Bitfield definition for register: MM2S_DMA_CFG */
/*
 * DBUFD (RO)
 *
 * data buffer depth
 */
#define TSW_MM2S_DMA_CFG_DBUFD_MASK (0xF000000UL)
#define TSW_MM2S_DMA_CFG_DBUFD_SHIFT (24U)
#define TSW_MM2S_DMA_CFG_DBUFD_GET(x) (((uint32_t)(x) & TSW_MM2S_DMA_CFG_DBUFD_MASK) >> TSW_MM2S_DMA_CFG_DBUFD_SHIFT)

/*
 * CBUFD (RO)
 *
 * command buffer depth
 */
#define TSW_MM2S_DMA_CFG_CBUFD_MASK (0xF00000UL)
#define TSW_MM2S_DMA_CFG_CBUFD_SHIFT (20U)
#define TSW_MM2S_DMA_CFG_CBUFD_GET(x) (((uint32_t)(x) & TSW_MM2S_DMA_CFG_CBUFD_MASK) >> TSW_MM2S_DMA_CFG_CBUFD_SHIFT)

/*
 * ENA64 (RO)
 *
 * enable support for 64 bit addressing
 */
#define TSW_MM2S_DMA_CFG_ENA64_MASK (0x80000UL)
#define TSW_MM2S_DMA_CFG_ENA64_SHIFT (19U)
#define TSW_MM2S_DMA_CFG_ENA64_GET(x) (((uint32_t)(x) & TSW_MM2S_DMA_CFG_ENA64_MASK) >> TSW_MM2S_DMA_CFG_ENA64_SHIFT)

/*
 * ASIZE (RO)
 *
 * axi data bus width
 */
#define TSW_MM2S_DMA_CFG_ASIZE_MASK (0x70000UL)
#define TSW_MM2S_DMA_CFG_ASIZE_SHIFT (16U)
#define TSW_MM2S_DMA_CFG_ASIZE_GET(x) (((uint32_t)(x) & TSW_MM2S_DMA_CFG_ASIZE_MASK) >> TSW_MM2S_DMA_CFG_ASIZE_SHIFT)

/*
 * VER (RO)
 *
 * ip version
 */
#define TSW_MM2S_DMA_CFG_VER_MASK (0xFFFFU)
#define TSW_MM2S_DMA_CFG_VER_SHIFT (0U)
#define TSW_MM2S_DMA_CFG_VER_GET(x) (((uint32_t)(x) & TSW_MM2S_DMA_CFG_VER_MASK) >> TSW_MM2S_DMA_CFG_VER_SHIFT)

/* Bitfield definition for register: MM2S_ADDRLO */
/*
 * ADDRLO (RW)
 *
 * axi address
 */
#define TSW_MM2S_ADDRLO_ADDRLO_MASK (0xFFFFFFFFUL)
#define TSW_MM2S_ADDRLO_ADDRLO_SHIFT (0U)
#define TSW_MM2S_ADDRLO_ADDRLO_SET(x) (((uint32_t)(x) << TSW_MM2S_ADDRLO_ADDRLO_SHIFT) & TSW_MM2S_ADDRLO_ADDRLO_MASK)
#define TSW_MM2S_ADDRLO_ADDRLO_GET(x) (((uint32_t)(x) & TSW_MM2S_ADDRLO_ADDRLO_MASK) >> TSW_MM2S_ADDRLO_ADDRLO_SHIFT)

/* Bitfield definition for register: MM2S_LENGTH */
/*
 * LENGTH (RW)
 *
 * transfer request length in bytes
 */
#define TSW_MM2S_LENGTH_LENGTH_MASK (0xFFFFU)
#define TSW_MM2S_LENGTH_LENGTH_SHIFT (0U)
#define TSW_MM2S_LENGTH_LENGTH_SET(x) (((uint32_t)(x) << TSW_MM2S_LENGTH_LENGTH_SHIFT) & TSW_MM2S_LENGTH_LENGTH_MASK)
#define TSW_MM2S_LENGTH_LENGTH_GET(x) (((uint32_t)(x) & TSW_MM2S_LENGTH_LENGTH_MASK) >> TSW_MM2S_LENGTH_LENGTH_SHIFT)

/* Bitfield definition for register: MM2S_CTRL */
/*
 * GO (WO)
 *
 * commit buffered descriptor to command queue
 */
#define TSW_MM2S_CTRL_GO_MASK (0x80000000UL)
#define TSW_MM2S_CTRL_GO_SHIFT (31U)
#define TSW_MM2S_CTRL_GO_SET(x) (((uint32_t)(x) << TSW_MM2S_CTRL_GO_SHIFT) & TSW_MM2S_CTRL_GO_MASK)
#define TSW_MM2S_CTRL_GO_GET(x) (((uint32_t)(x) & TSW_MM2S_CTRL_GO_MASK) >> TSW_MM2S_CTRL_GO_SHIFT)

/*
 * NGENLAST (RW)
 *
 * no generation of TLAST
 */
#define TSW_MM2S_CTRL_NGENLAST_MASK (0x10U)
#define TSW_MM2S_CTRL_NGENLAST_SHIFT (4U)
#define TSW_MM2S_CTRL_NGENLAST_SET(x) (((uint32_t)(x) << TSW_MM2S_CTRL_NGENLAST_SHIFT) & TSW_MM2S_CTRL_NGENLAST_MASK)
#define TSW_MM2S_CTRL_NGENLAST_GET(x) (((uint32_t)(x) & TSW_MM2S_CTRL_NGENLAST_MASK) >> TSW_MM2S_CTRL_NGENLAST_SHIFT)

/*
 * ID (RW)
 *
 * command id
 */
#define TSW_MM2S_CTRL_ID_MASK (0xFU)
#define TSW_MM2S_CTRL_ID_SHIFT (0U)
#define TSW_MM2S_CTRL_ID_SET(x) (((uint32_t)(x) << TSW_MM2S_CTRL_ID_SHIFT) & TSW_MM2S_CTRL_ID_MASK)
#define TSW_MM2S_CTRL_ID_GET(x) (((uint32_t)(x) & TSW_MM2S_CTRL_ID_MASK) >> TSW_MM2S_CTRL_ID_SHIFT)

/* Bitfield definition for register: MM2S_RESP */
/*
 * LAST (RO)
 *
 * axi-stream with TLAST
 */
#define TSW_MM2S_RESP_LAST_MASK (0x40000000UL)
#define TSW_MM2S_RESP_LAST_SHIFT (30U)
#define TSW_MM2S_RESP_LAST_GET(x) (((uint32_t)(x) & TSW_MM2S_RESP_LAST_MASK) >> TSW_MM2S_RESP_LAST_SHIFT)

/*
 * DECERR (RO)
 *
 * decode error
 */
#define TSW_MM2S_RESP_DECERR_MASK (0x20000000UL)
#define TSW_MM2S_RESP_DECERR_SHIFT (29U)
#define TSW_MM2S_RESP_DECERR_GET(x) (((uint32_t)(x) & TSW_MM2S_RESP_DECERR_MASK) >> TSW_MM2S_RESP_DECERR_SHIFT)

/*
 * SLVERR (RO)
 *
 * slave error
 */
#define TSW_MM2S_RESP_SLVERR_MASK (0x10000000UL)
#define TSW_MM2S_RESP_SLVERR_SHIFT (28U)
#define TSW_MM2S_RESP_SLVERR_GET(x) (((uint32_t)(x) & TSW_MM2S_RESP_SLVERR_MASK) >> TSW_MM2S_RESP_SLVERR_SHIFT)

/*
 * ID (RO)
 *
 * command ID feedback
 */
#define TSW_MM2S_RESP_ID_MASK (0xF000000UL)
#define TSW_MM2S_RESP_ID_SHIFT (24U)
#define TSW_MM2S_RESP_ID_GET(x) (((uint32_t)(x) & TSW_MM2S_RESP_ID_MASK) >> TSW_MM2S_RESP_ID_SHIFT)

/*
 * LENGTH (RO)
 *
 * requested length of tansfer in bytes from command
 */
#define TSW_MM2S_RESP_LENGTH_MASK (0xFFFFU)
#define TSW_MM2S_RESP_LENGTH_SHIFT (0U)
#define TSW_MM2S_RESP_LENGTH_GET(x) (((uint32_t)(x) & TSW_MM2S_RESP_LENGTH_MASK) >> TSW_MM2S_RESP_LENGTH_SHIFT)

/* Bitfield definition for register: S2MM_DMA_CR */
/*
 * MXLEN (RW)
 *
 * max axi burst size
 */
#define TSW_S2MM_DMA_CR_MXLEN_MASK (0xFF000000UL)
#define TSW_S2MM_DMA_CR_MXLEN_SHIFT (24U)
#define TSW_S2MM_DMA_CR_MXLEN_SET(x) (((uint32_t)(x) << TSW_S2MM_DMA_CR_MXLEN_SHIFT) & TSW_S2MM_DMA_CR_MXLEN_MASK)
#define TSW_S2MM_DMA_CR_MXLEN_GET(x) (((uint32_t)(x) & TSW_S2MM_DMA_CR_MXLEN_MASK) >> TSW_S2MM_DMA_CR_MXLEN_SHIFT)

/*
 * IRQEN (RW)
 *
 * interrupt request enable
 */
#define TSW_S2MM_DMA_CR_IRQEN_MASK (0x8U)
#define TSW_S2MM_DMA_CR_IRQEN_SHIFT (3U)
#define TSW_S2MM_DMA_CR_IRQEN_SET(x) (((uint32_t)(x) << TSW_S2MM_DMA_CR_IRQEN_SHIFT) & TSW_S2MM_DMA_CR_IRQEN_MASK)
#define TSW_S2MM_DMA_CR_IRQEN_GET(x) (((uint32_t)(x) & TSW_S2MM_DMA_CR_IRQEN_MASK) >> TSW_S2MM_DMA_CR_IRQEN_SHIFT)

/*
 * RESET (WO)
 *
 * do reset when writing 1
 */
#define TSW_S2MM_DMA_CR_RESET_MASK (0x4U)
#define TSW_S2MM_DMA_CR_RESET_SHIFT (2U)
#define TSW_S2MM_DMA_CR_RESET_SET(x) (((uint32_t)(x) << TSW_S2MM_DMA_CR_RESET_SHIFT) & TSW_S2MM_DMA_CR_RESET_MASK)
#define TSW_S2MM_DMA_CR_RESET_GET(x) (((uint32_t)(x) & TSW_S2MM_DMA_CR_RESET_MASK) >> TSW_S2MM_DMA_CR_RESET_SHIFT)

/*
 * SOE (RW)
 *
 * stop on error flag
 */
#define TSW_S2MM_DMA_CR_SOE_MASK (0x2U)
#define TSW_S2MM_DMA_CR_SOE_SHIFT (1U)
#define TSW_S2MM_DMA_CR_SOE_SET(x) (((uint32_t)(x) << TSW_S2MM_DMA_CR_SOE_SHIFT) & TSW_S2MM_DMA_CR_SOE_MASK)
#define TSW_S2MM_DMA_CR_SOE_GET(x) (((uint32_t)(x) & TSW_S2MM_DMA_CR_SOE_MASK) >> TSW_S2MM_DMA_CR_SOE_SHIFT)

/*
 * RUN (RW)
 *
 * run commands from queue to data mover
 */
#define TSW_S2MM_DMA_CR_RUN_MASK (0x1U)
#define TSW_S2MM_DMA_CR_RUN_SHIFT (0U)
#define TSW_S2MM_DMA_CR_RUN_SET(x) (((uint32_t)(x) << TSW_S2MM_DMA_CR_RUN_SHIFT) & TSW_S2MM_DMA_CR_RUN_MASK)
#define TSW_S2MM_DMA_CR_RUN_GET(x) (((uint32_t)(x) & TSW_S2MM_DMA_CR_RUN_MASK) >> TSW_S2MM_DMA_CR_RUN_SHIFT)

/* Bitfield definition for register: S2MM_DMA_SR */
/*
 * RBUFF (RO)
 *
 * response buffer full
 */
#define TSW_S2MM_DMA_SR_RBUFF_MASK (0x80U)
#define TSW_S2MM_DMA_SR_RBUFF_SHIFT (7U)
#define TSW_S2MM_DMA_SR_RBUFF_GET(x) (((uint32_t)(x) & TSW_S2MM_DMA_SR_RBUFF_MASK) >> TSW_S2MM_DMA_SR_RBUFF_SHIFT)

/*
 * RBUFE (RO)
 *
 * response buffer empty
 */
#define TSW_S2MM_DMA_SR_RBUFE_MASK (0x40U)
#define TSW_S2MM_DMA_SR_RBUFE_SHIFT (6U)
#define TSW_S2MM_DMA_SR_RBUFE_GET(x) (((uint32_t)(x) & TSW_S2MM_DMA_SR_RBUFE_MASK) >> TSW_S2MM_DMA_SR_RBUFE_SHIFT)

/*
 * CBUFF (RO)
 *
 * command buffer full
 */
#define TSW_S2MM_DMA_SR_CBUFF_MASK (0x20U)
#define TSW_S2MM_DMA_SR_CBUFF_SHIFT (5U)
#define TSW_S2MM_DMA_SR_CBUFF_GET(x) (((uint32_t)(x) & TSW_S2MM_DMA_SR_CBUFF_MASK) >> TSW_S2MM_DMA_SR_CBUFF_SHIFT)

/*
 * CBUFE (RO)
 *
 * command buffer empty
 */
#define TSW_S2MM_DMA_SR_CBUFE_MASK (0x10U)
#define TSW_S2MM_DMA_SR_CBUFE_SHIFT (4U)
#define TSW_S2MM_DMA_SR_CBUFE_GET(x) (((uint32_t)(x) & TSW_S2MM_DMA_SR_CBUFE_MASK) >> TSW_S2MM_DMA_SR_CBUFE_SHIFT)

/*
 * IRQ (RWC)
 *
 * interrupt request pending
 */
#define TSW_S2MM_DMA_SR_IRQ_MASK (0x8U)
#define TSW_S2MM_DMA_SR_IRQ_SHIFT (3U)
#define TSW_S2MM_DMA_SR_IRQ_SET(x) (((uint32_t)(x) << TSW_S2MM_DMA_SR_IRQ_SHIFT) & TSW_S2MM_DMA_SR_IRQ_MASK)
#define TSW_S2MM_DMA_SR_IRQ_GET(x) (((uint32_t)(x) & TSW_S2MM_DMA_SR_IRQ_MASK) >> TSW_S2MM_DMA_SR_IRQ_SHIFT)

/*
 * RSET (RO)
 *
 * resetting status
 */
#define TSW_S2MM_DMA_SR_RSET_MASK (0x4U)
#define TSW_S2MM_DMA_SR_RSET_SHIFT (2U)
#define TSW_S2MM_DMA_SR_RSET_GET(x) (((uint32_t)(x) & TSW_S2MM_DMA_SR_RSET_MASK) >> TSW_S2MM_DMA_SR_RSET_SHIFT)

/*
 * BUSY (RO)
 *
 * busy, issued command and outstanding response
 */
#define TSW_S2MM_DMA_SR_BUSY_MASK (0x2U)
#define TSW_S2MM_DMA_SR_BUSY_SHIFT (1U)
#define TSW_S2MM_DMA_SR_BUSY_GET(x) (((uint32_t)(x) & TSW_S2MM_DMA_SR_BUSY_MASK) >> TSW_S2MM_DMA_SR_BUSY_SHIFT)

/*
 * STOP (RO)
 *
 * s2mm is stopped
 */
#define TSW_S2MM_DMA_SR_STOP_MASK (0x1U)
#define TSW_S2MM_DMA_SR_STOP_SHIFT (0U)
#define TSW_S2MM_DMA_SR_STOP_GET(x) (((uint32_t)(x) & TSW_S2MM_DMA_SR_STOP_MASK) >> TSW_S2MM_DMA_SR_STOP_SHIFT)

/* Bitfield definition for register: S2MM_DMA_FILL */
/*
 * RFILL (RO)
 *
 * response buffer fill level
 */
#define TSW_S2MM_DMA_FILL_RFILL_MASK (0xFFFF0000UL)
#define TSW_S2MM_DMA_FILL_RFILL_SHIFT (16U)
#define TSW_S2MM_DMA_FILL_RFILL_GET(x) (((uint32_t)(x) & TSW_S2MM_DMA_FILL_RFILL_MASK) >> TSW_S2MM_DMA_FILL_RFILL_SHIFT)

/*
 * CFILL (RO)
 *
 * command buffer fill level
 */
#define TSW_S2MM_DMA_FILL_CFILL_MASK (0xFFFFU)
#define TSW_S2MM_DMA_FILL_CFILL_SHIFT (0U)
#define TSW_S2MM_DMA_FILL_CFILL_GET(x) (((uint32_t)(x) & TSW_S2MM_DMA_FILL_CFILL_MASK) >> TSW_S2MM_DMA_FILL_CFILL_SHIFT)

/* Bitfield definition for register: S2MM_DMA_CFG */
/*
 * DBUFD (RO)
 *
 * data buffer depth
 */
#define TSW_S2MM_DMA_CFG_DBUFD_MASK (0xF000000UL)
#define TSW_S2MM_DMA_CFG_DBUFD_SHIFT (24U)
#define TSW_S2MM_DMA_CFG_DBUFD_GET(x) (((uint32_t)(x) & TSW_S2MM_DMA_CFG_DBUFD_MASK) >> TSW_S2MM_DMA_CFG_DBUFD_SHIFT)

/*
 * CBUFD (RO)
 *
 * command buffer depth
 */
#define TSW_S2MM_DMA_CFG_CBUFD_MASK (0xF00000UL)
#define TSW_S2MM_DMA_CFG_CBUFD_SHIFT (20U)
#define TSW_S2MM_DMA_CFG_CBUFD_GET(x) (((uint32_t)(x) & TSW_S2MM_DMA_CFG_CBUFD_MASK) >> TSW_S2MM_DMA_CFG_CBUFD_SHIFT)

/*
 * ENA64 (RO)
 *
 * enabled support for 64 bit
 */
#define TSW_S2MM_DMA_CFG_ENA64_MASK (0x80000UL)
#define TSW_S2MM_DMA_CFG_ENA64_SHIFT (19U)
#define TSW_S2MM_DMA_CFG_ENA64_GET(x) (((uint32_t)(x) & TSW_S2MM_DMA_CFG_ENA64_MASK) >> TSW_S2MM_DMA_CFG_ENA64_SHIFT)

/*
 * ASIZE (RO)
 *
 * axi data bus width
 */
#define TSW_S2MM_DMA_CFG_ASIZE_MASK (0x70000UL)
#define TSW_S2MM_DMA_CFG_ASIZE_SHIFT (16U)
#define TSW_S2MM_DMA_CFG_ASIZE_GET(x) (((uint32_t)(x) & TSW_S2MM_DMA_CFG_ASIZE_MASK) >> TSW_S2MM_DMA_CFG_ASIZE_SHIFT)

/*
 * VER (RO)
 *
 * IP version
 */
#define TSW_S2MM_DMA_CFG_VER_MASK (0xFFFFU)
#define TSW_S2MM_DMA_CFG_VER_SHIFT (0U)
#define TSW_S2MM_DMA_CFG_VER_GET(x) (((uint32_t)(x) & TSW_S2MM_DMA_CFG_VER_MASK) >> TSW_S2MM_DMA_CFG_VER_SHIFT)

/* Bitfield definition for register: S2MM_ADDRLO */
/*
 * ADDRLO (RW)
 *
 * axi address
 */
#define TSW_S2MM_ADDRLO_ADDRLO_MASK (0xFFFFFFFFUL)
#define TSW_S2MM_ADDRLO_ADDRLO_SHIFT (0U)
#define TSW_S2MM_ADDRLO_ADDRLO_SET(x) (((uint32_t)(x) << TSW_S2MM_ADDRLO_ADDRLO_SHIFT) & TSW_S2MM_ADDRLO_ADDRLO_MASK)
#define TSW_S2MM_ADDRLO_ADDRLO_GET(x) (((uint32_t)(x) & TSW_S2MM_ADDRLO_ADDRLO_MASK) >> TSW_S2MM_ADDRLO_ADDRLO_SHIFT)

/* Bitfield definition for register: S2MM_LENGTH */
/*
 * LENGTH (RW)
 *
 * transfer request length in bytes
 */
#define TSW_S2MM_LENGTH_LENGTH_MASK (0xFFFFU)
#define TSW_S2MM_LENGTH_LENGTH_SHIFT (0U)
#define TSW_S2MM_LENGTH_LENGTH_SET(x) (((uint32_t)(x) << TSW_S2MM_LENGTH_LENGTH_SHIFT) & TSW_S2MM_LENGTH_LENGTH_MASK)
#define TSW_S2MM_LENGTH_LENGTH_GET(x) (((uint32_t)(x) & TSW_S2MM_LENGTH_LENGTH_MASK) >> TSW_S2MM_LENGTH_LENGTH_SHIFT)

/* Bitfield definition for register: S2MM_CTRL */
/*
 * GO (WO)
 *
 * commit buffered descriptor to command queue
 */
#define TSW_S2MM_CTRL_GO_MASK (0x80000000UL)
#define TSW_S2MM_CTRL_GO_SHIFT (31U)
#define TSW_S2MM_CTRL_GO_SET(x) (((uint32_t)(x) << TSW_S2MM_CTRL_GO_SHIFT) & TSW_S2MM_CTRL_GO_MASK)
#define TSW_S2MM_CTRL_GO_GET(x) (((uint32_t)(x) & TSW_S2MM_CTRL_GO_MASK) >> TSW_S2MM_CTRL_GO_SHIFT)

/*
 * ID (RW)
 *
 * command id
 */
#define TSW_S2MM_CTRL_ID_MASK (0xFU)
#define TSW_S2MM_CTRL_ID_SHIFT (0U)
#define TSW_S2MM_CTRL_ID_SET(x) (((uint32_t)(x) << TSW_S2MM_CTRL_ID_SHIFT) & TSW_S2MM_CTRL_ID_MASK)
#define TSW_S2MM_CTRL_ID_GET(x) (((uint32_t)(x) & TSW_S2MM_CTRL_ID_MASK) >> TSW_S2MM_CTRL_ID_SHIFT)

/* Bitfield definition for register: S2MM_RESP */
/*
 * LAST (RO)
 *
 * axi-stream with last
 */
#define TSW_S2MM_RESP_LAST_MASK (0x40000000UL)
#define TSW_S2MM_RESP_LAST_SHIFT (30U)
#define TSW_S2MM_RESP_LAST_GET(x) (((uint32_t)(x) & TSW_S2MM_RESP_LAST_MASK) >> TSW_S2MM_RESP_LAST_SHIFT)

/*
 * DECERR (RO)
 *
 * decode error
 */
#define TSW_S2MM_RESP_DECERR_MASK (0x20000000UL)
#define TSW_S2MM_RESP_DECERR_SHIFT (29U)
#define TSW_S2MM_RESP_DECERR_GET(x) (((uint32_t)(x) & TSW_S2MM_RESP_DECERR_MASK) >> TSW_S2MM_RESP_DECERR_SHIFT)

/*
 * SLVERR (RO)
 *
 * slave error
 */
#define TSW_S2MM_RESP_SLVERR_MASK (0x10000000UL)
#define TSW_S2MM_RESP_SLVERR_SHIFT (28U)
#define TSW_S2MM_RESP_SLVERR_GET(x) (((uint32_t)(x) & TSW_S2MM_RESP_SLVERR_MASK) >> TSW_S2MM_RESP_SLVERR_SHIFT)

/*
 * ID (RO)
 *
 * command ID feedback
 */
#define TSW_S2MM_RESP_ID_MASK (0xF000000UL)
#define TSW_S2MM_RESP_ID_SHIFT (24U)
#define TSW_S2MM_RESP_ID_GET(x) (((uint32_t)(x) & TSW_S2MM_RESP_ID_MASK) >> TSW_S2MM_RESP_ID_SHIFT)

/*
 * LENGTH (RO)
 *
 * received packet size when terminated by TLAST
 */
#define TSW_S2MM_RESP_LENGTH_MASK (0xFFFFU)
#define TSW_S2MM_RESP_LENGTH_SHIFT (0U)
#define TSW_S2MM_RESP_LENGTH_GET(x) (((uint32_t)(x) & TSW_S2MM_RESP_LENGTH_MASK) >> TSW_S2MM_RESP_LENGTH_SHIFT)

/* Bitfield definition for register: PTP_EVT_TS_CTL */
/*
 * ATSEN (RW)
 *
 * auxiliay snapshot enable
 */
#define TSW_PTP_EVT_TS_CTL_ATSEN_MASK (0x1E000000UL)
#define TSW_PTP_EVT_TS_CTL_ATSEN_SHIFT (25U)
#define TSW_PTP_EVT_TS_CTL_ATSEN_SET(x) (((uint32_t)(x) << TSW_PTP_EVT_TS_CTL_ATSEN_SHIFT) & TSW_PTP_EVT_TS_CTL_ATSEN_MASK)
#define TSW_PTP_EVT_TS_CTL_ATSEN_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_TS_CTL_ATSEN_MASK) >> TSW_PTP_EVT_TS_CTL_ATSEN_SHIFT)

/*
 * ATSFC (W1C)
 *
 * auxiliary snapshot fifo clear
 */
#define TSW_PTP_EVT_TS_CTL_ATSFC_MASK (0x1000000UL)
#define TSW_PTP_EVT_TS_CTL_ATSFC_SHIFT (24U)
#define TSW_PTP_EVT_TS_CTL_ATSFC_SET(x) (((uint32_t)(x) << TSW_PTP_EVT_TS_CTL_ATSFC_SHIFT) & TSW_PTP_EVT_TS_CTL_ATSFC_MASK)
#define TSW_PTP_EVT_TS_CTL_ATSFC_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_TS_CTL_ATSFC_MASK) >> TSW_PTP_EVT_TS_CTL_ATSFC_SHIFT)

/*
 * TSTIG (RW)
 *
 * timestamp interrupt trigger enable
 */
#define TSW_PTP_EVT_TS_CTL_TSTIG_MASK (0x10U)
#define TSW_PTP_EVT_TS_CTL_TSTIG_SHIFT (4U)
#define TSW_PTP_EVT_TS_CTL_TSTIG_SET(x) (((uint32_t)(x) << TSW_PTP_EVT_TS_CTL_TSTIG_SHIFT) & TSW_PTP_EVT_TS_CTL_TSTIG_MASK)
#define TSW_PTP_EVT_TS_CTL_TSTIG_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_TS_CTL_TSTIG_MASK) >> TSW_PTP_EVT_TS_CTL_TSTIG_SHIFT)

/* Bitfield definition for register: PTP_EVT_PPS_TOD_SEC */
/*
 * PPS_TOD_SEC (RO)
 *
 * pps tod seconds
 */
#define TSW_PTP_EVT_PPS_TOD_SEC_PPS_TOD_SEC_MASK (0xFFFFFFFFUL)
#define TSW_PTP_EVT_PPS_TOD_SEC_PPS_TOD_SEC_SHIFT (0U)
#define TSW_PTP_EVT_PPS_TOD_SEC_PPS_TOD_SEC_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_PPS_TOD_SEC_PPS_TOD_SEC_MASK) >> TSW_PTP_EVT_PPS_TOD_SEC_PPS_TOD_SEC_SHIFT)

/* Bitfield definition for register: PTP_EVT_PPS_TOD_NS */
/*
 * PPS_TOD_NS (RO)
 *
 * pps tod sub seconds
 */
#define TSW_PTP_EVT_PPS_TOD_NS_PPS_TOD_NS_MASK (0x3FFFFFFFUL)
#define TSW_PTP_EVT_PPS_TOD_NS_PPS_TOD_NS_SHIFT (0U)
#define TSW_PTP_EVT_PPS_TOD_NS_PPS_TOD_NS_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_PPS_TOD_NS_PPS_TOD_NS_MASK) >> TSW_PTP_EVT_PPS_TOD_NS_PPS_TOD_NS_SHIFT)

/* Bitfield definition for register: PTP_EVT_SCP_SEC0 */
/*
 * SCP_SEC (RW)
 *
 * target time seconds
 */
#define TSW_PTP_EVT_SCP_SEC0_SCP_SEC_MASK (0xFFFFFFFFUL)
#define TSW_PTP_EVT_SCP_SEC0_SCP_SEC_SHIFT (0U)
#define TSW_PTP_EVT_SCP_SEC0_SCP_SEC_SET(x) (((uint32_t)(x) << TSW_PTP_EVT_SCP_SEC0_SCP_SEC_SHIFT) & TSW_PTP_EVT_SCP_SEC0_SCP_SEC_MASK)
#define TSW_PTP_EVT_SCP_SEC0_SCP_SEC_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_SCP_SEC0_SCP_SEC_MASK) >> TSW_PTP_EVT_SCP_SEC0_SCP_SEC_SHIFT)

/* Bitfield definition for register: PTP_EVT_SCP_NS0 */
/*
 * SCP_NS (RW)
 *
 * target time sub seconds
 */
#define TSW_PTP_EVT_SCP_NS0_SCP_NS_MASK (0x3FFFFFFFUL)
#define TSW_PTP_EVT_SCP_NS0_SCP_NS_SHIFT (0U)
#define TSW_PTP_EVT_SCP_NS0_SCP_NS_SET(x) (((uint32_t)(x) << TSW_PTP_EVT_SCP_NS0_SCP_NS_SHIFT) & TSW_PTP_EVT_SCP_NS0_SCP_NS_MASK)
#define TSW_PTP_EVT_SCP_NS0_SCP_NS_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_SCP_NS0_SCP_NS_MASK) >> TSW_PTP_EVT_SCP_NS0_SCP_NS_SHIFT)

/* Bitfield definition for register: PTP_EVT_TMR_STS */
/*
 * RD_CNT (RO)
 *
 * fifo valid count
 */
#define TSW_PTP_EVT_TMR_STS_RD_CNT_MASK (0x3E000000UL)
#define TSW_PTP_EVT_TMR_STS_RD_CNT_SHIFT (25U)
#define TSW_PTP_EVT_TMR_STS_RD_CNT_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_TMR_STS_RD_CNT_MASK) >> TSW_PTP_EVT_TMR_STS_RD_CNT_SHIFT)

/*
 * ATSSTM (RO)
 *
 * auxiliary fifo full error
 */
#define TSW_PTP_EVT_TMR_STS_ATSSTM_MASK (0x1000000UL)
#define TSW_PTP_EVT_TMR_STS_ATSSTM_SHIFT (24U)
#define TSW_PTP_EVT_TMR_STS_ATSSTM_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_TMR_STS_ATSSTM_MASK) >> TSW_PTP_EVT_TMR_STS_ATSSTM_SHIFT)

/*
 * ATPORT (RO)
 *
 * auxiliary port
 */
#define TSW_PTP_EVT_TMR_STS_ATPORT_MASK (0xF0000UL)
#define TSW_PTP_EVT_TMR_STS_ATPORT_SHIFT (16U)
#define TSW_PTP_EVT_TMR_STS_ATPORT_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_TMR_STS_ATPORT_MASK) >> TSW_PTP_EVT_TMR_STS_ATPORT_SHIFT)

/*
 * PPS_TOD_INTR (RC)
 *
 * pps tod intrrupt
 */
#define TSW_PTP_EVT_TMR_STS_PPS_TOD_INTR_MASK (0x400U)
#define TSW_PTP_EVT_TMR_STS_PPS_TOD_INTR_SHIFT (10U)
#define TSW_PTP_EVT_TMR_STS_PPS_TOD_INTR_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_TMR_STS_PPS_TOD_INTR_MASK) >> TSW_PTP_EVT_TMR_STS_PPS_TOD_INTR_SHIFT)

/*
 * TARGET_TIME3_CFG_ERR (RO)
 *
 * target time3 configure error
 */
#define TSW_PTP_EVT_TMR_STS_TARGET_TIME3_CFG_ERR_MASK (0x200U)
#define TSW_PTP_EVT_TMR_STS_TARGET_TIME3_CFG_ERR_SHIFT (9U)
#define TSW_PTP_EVT_TMR_STS_TARGET_TIME3_CFG_ERR_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_TMR_STS_TARGET_TIME3_CFG_ERR_MASK) >> TSW_PTP_EVT_TMR_STS_TARGET_TIME3_CFG_ERR_SHIFT)

/*
 * TARGET_TIME3_REACH_INTR (RC)
 *
 * target time3 reached
 */
#define TSW_PTP_EVT_TMR_STS_TARGET_TIME3_REACH_INTR_MASK (0x100U)
#define TSW_PTP_EVT_TMR_STS_TARGET_TIME3_REACH_INTR_SHIFT (8U)
#define TSW_PTP_EVT_TMR_STS_TARGET_TIME3_REACH_INTR_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_TMR_STS_TARGET_TIME3_REACH_INTR_MASK) >> TSW_PTP_EVT_TMR_STS_TARGET_TIME3_REACH_INTR_SHIFT)

/*
 * TARGET_TIME2_CFG_ERR (RO)
 *
 * target time2 configure error
 */
#define TSW_PTP_EVT_TMR_STS_TARGET_TIME2_CFG_ERR_MASK (0x80U)
#define TSW_PTP_EVT_TMR_STS_TARGET_TIME2_CFG_ERR_SHIFT (7U)
#define TSW_PTP_EVT_TMR_STS_TARGET_TIME2_CFG_ERR_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_TMR_STS_TARGET_TIME2_CFG_ERR_MASK) >> TSW_PTP_EVT_TMR_STS_TARGET_TIME2_CFG_ERR_SHIFT)

/*
 * TARGET_TIME2_REACH_INTR (RC)
 *
 * target time2 reached
 */
#define TSW_PTP_EVT_TMR_STS_TARGET_TIME2_REACH_INTR_MASK (0x40U)
#define TSW_PTP_EVT_TMR_STS_TARGET_TIME2_REACH_INTR_SHIFT (6U)
#define TSW_PTP_EVT_TMR_STS_TARGET_TIME2_REACH_INTR_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_TMR_STS_TARGET_TIME2_REACH_INTR_MASK) >> TSW_PTP_EVT_TMR_STS_TARGET_TIME2_REACH_INTR_SHIFT)

/*
 * TARGET_TIME1_CFG_ERR (RO)
 *
 * target time1 configure error
 */
#define TSW_PTP_EVT_TMR_STS_TARGET_TIME1_CFG_ERR_MASK (0x20U)
#define TSW_PTP_EVT_TMR_STS_TARGET_TIME1_CFG_ERR_SHIFT (5U)
#define TSW_PTP_EVT_TMR_STS_TARGET_TIME1_CFG_ERR_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_TMR_STS_TARGET_TIME1_CFG_ERR_MASK) >> TSW_PTP_EVT_TMR_STS_TARGET_TIME1_CFG_ERR_SHIFT)

/*
 * TARGET_TIME1_REACH_INTR (RC)
 *
 * target time1 reached
 */
#define TSW_PTP_EVT_TMR_STS_TARGET_TIME1_REACH_INTR_MASK (0x10U)
#define TSW_PTP_EVT_TMR_STS_TARGET_TIME1_REACH_INTR_SHIFT (4U)
#define TSW_PTP_EVT_TMR_STS_TARGET_TIME1_REACH_INTR_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_TMR_STS_TARGET_TIME1_REACH_INTR_MASK) >> TSW_PTP_EVT_TMR_STS_TARGET_TIME1_REACH_INTR_SHIFT)

/*
 * TARGET_TIME0_CFG_ERR (RO)
 *
 * target time0 configure error
 */
#define TSW_PTP_EVT_TMR_STS_TARGET_TIME0_CFG_ERR_MASK (0x8U)
#define TSW_PTP_EVT_TMR_STS_TARGET_TIME0_CFG_ERR_SHIFT (3U)
#define TSW_PTP_EVT_TMR_STS_TARGET_TIME0_CFG_ERR_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_TMR_STS_TARGET_TIME0_CFG_ERR_MASK) >> TSW_PTP_EVT_TMR_STS_TARGET_TIME0_CFG_ERR_SHIFT)

/*
 * PTP_FIFO_WR_INTR (RC)
 *
 * auxiliary timestamp trigger snapshot
 */
#define TSW_PTP_EVT_TMR_STS_PTP_FIFO_WR_INTR_MASK (0x4U)
#define TSW_PTP_EVT_TMR_STS_PTP_FIFO_WR_INTR_SHIFT (2U)
#define TSW_PTP_EVT_TMR_STS_PTP_FIFO_WR_INTR_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_TMR_STS_PTP_FIFO_WR_INTR_MASK) >> TSW_PTP_EVT_TMR_STS_PTP_FIFO_WR_INTR_SHIFT)

/*
 * TARGET_TIME0_REACH_INTR (RC)
 *
 * target time0 reached
 */
#define TSW_PTP_EVT_TMR_STS_TARGET_TIME0_REACH_INTR_MASK (0x2U)
#define TSW_PTP_EVT_TMR_STS_TARGET_TIME0_REACH_INTR_SHIFT (1U)
#define TSW_PTP_EVT_TMR_STS_TARGET_TIME0_REACH_INTR_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_TMR_STS_TARGET_TIME0_REACH_INTR_MASK) >> TSW_PTP_EVT_TMR_STS_TARGET_TIME0_REACH_INTR_SHIFT)

/* Bitfield definition for register: PTP_EVT_PPS_CMD */
/*
 * PPS_MODE3 (RW)
 *
 * Target Time Register Mode for PPS3 Output
 */
#define TSW_PTP_EVT_PPS_CMD_PPS_MODE3_MASK (0x60000000UL)
#define TSW_PTP_EVT_PPS_CMD_PPS_MODE3_SHIFT (29U)
#define TSW_PTP_EVT_PPS_CMD_PPS_MODE3_SET(x) (((uint32_t)(x) << TSW_PTP_EVT_PPS_CMD_PPS_MODE3_SHIFT) & TSW_PTP_EVT_PPS_CMD_PPS_MODE3_MASK)
#define TSW_PTP_EVT_PPS_CMD_PPS_MODE3_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_PPS_CMD_PPS_MODE3_MASK) >> TSW_PTP_EVT_PPS_CMD_PPS_MODE3_SHIFT)

/*
 * PPS_CMD3 (RW)
 *
 * pps3 command
 */
#define TSW_PTP_EVT_PPS_CMD_PPS_CMD3_MASK (0x7000000UL)
#define TSW_PTP_EVT_PPS_CMD_PPS_CMD3_SHIFT (24U)
#define TSW_PTP_EVT_PPS_CMD_PPS_CMD3_SET(x) (((uint32_t)(x) << TSW_PTP_EVT_PPS_CMD_PPS_CMD3_SHIFT) & TSW_PTP_EVT_PPS_CMD_PPS_CMD3_MASK)
#define TSW_PTP_EVT_PPS_CMD_PPS_CMD3_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_PPS_CMD_PPS_CMD3_MASK) >> TSW_PTP_EVT_PPS_CMD_PPS_CMD3_SHIFT)

/*
 * PPS_MODE2 (RW)
 *
 * Target Time Register Mode for PPS2 Output
 */
#define TSW_PTP_EVT_PPS_CMD_PPS_MODE2_MASK (0x600000UL)
#define TSW_PTP_EVT_PPS_CMD_PPS_MODE2_SHIFT (21U)
#define TSW_PTP_EVT_PPS_CMD_PPS_MODE2_SET(x) (((uint32_t)(x) << TSW_PTP_EVT_PPS_CMD_PPS_MODE2_SHIFT) & TSW_PTP_EVT_PPS_CMD_PPS_MODE2_MASK)
#define TSW_PTP_EVT_PPS_CMD_PPS_MODE2_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_PPS_CMD_PPS_MODE2_MASK) >> TSW_PTP_EVT_PPS_CMD_PPS_MODE2_SHIFT)

/*
 * PPS_CMD2 (RW)
 *
 * pps2 command
 */
#define TSW_PTP_EVT_PPS_CMD_PPS_CMD2_MASK (0x70000UL)
#define TSW_PTP_EVT_PPS_CMD_PPS_CMD2_SHIFT (16U)
#define TSW_PTP_EVT_PPS_CMD_PPS_CMD2_SET(x) (((uint32_t)(x) << TSW_PTP_EVT_PPS_CMD_PPS_CMD2_SHIFT) & TSW_PTP_EVT_PPS_CMD_PPS_CMD2_MASK)
#define TSW_PTP_EVT_PPS_CMD_PPS_CMD2_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_PPS_CMD_PPS_CMD2_MASK) >> TSW_PTP_EVT_PPS_CMD_PPS_CMD2_SHIFT)

/*
 * PPS_MODE1 (RW)
 *
 * Target Time Register Mode for PPS1 Output
 */
#define TSW_PTP_EVT_PPS_CMD_PPS_MODE1_MASK (0x6000U)
#define TSW_PTP_EVT_PPS_CMD_PPS_MODE1_SHIFT (13U)
#define TSW_PTP_EVT_PPS_CMD_PPS_MODE1_SET(x) (((uint32_t)(x) << TSW_PTP_EVT_PPS_CMD_PPS_MODE1_SHIFT) & TSW_PTP_EVT_PPS_CMD_PPS_MODE1_MASK)
#define TSW_PTP_EVT_PPS_CMD_PPS_MODE1_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_PPS_CMD_PPS_MODE1_MASK) >> TSW_PTP_EVT_PPS_CMD_PPS_MODE1_SHIFT)

/*
 * PPS_CMD1 (RW)
 *
 * pps1 command
 */
#define TSW_PTP_EVT_PPS_CMD_PPS_CMD1_MASK (0x700U)
#define TSW_PTP_EVT_PPS_CMD_PPS_CMD1_SHIFT (8U)
#define TSW_PTP_EVT_PPS_CMD_PPS_CMD1_SET(x) (((uint32_t)(x) << TSW_PTP_EVT_PPS_CMD_PPS_CMD1_SHIFT) & TSW_PTP_EVT_PPS_CMD_PPS_CMD1_MASK)
#define TSW_PTP_EVT_PPS_CMD_PPS_CMD1_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_PPS_CMD_PPS_CMD1_MASK) >> TSW_PTP_EVT_PPS_CMD_PPS_CMD1_SHIFT)

/*
 * PPS_MODE0 (RW)
 *
 * Target Time Register Mode for PPS0 Output
 */
#define TSW_PTP_EVT_PPS_CMD_PPS_MODE0_MASK (0x60U)
#define TSW_PTP_EVT_PPS_CMD_PPS_MODE0_SHIFT (5U)
#define TSW_PTP_EVT_PPS_CMD_PPS_MODE0_SET(x) (((uint32_t)(x) << TSW_PTP_EVT_PPS_CMD_PPS_MODE0_SHIFT) & TSW_PTP_EVT_PPS_CMD_PPS_MODE0_MASK)
#define TSW_PTP_EVT_PPS_CMD_PPS_MODE0_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_PPS_CMD_PPS_MODE0_MASK) >> TSW_PTP_EVT_PPS_CMD_PPS_MODE0_SHIFT)

/*
 * PPS_EN0 (RW)
 *
 * flexible PPS0 output mode enable
 */
#define TSW_PTP_EVT_PPS_CMD_PPS_EN0_MASK (0x10U)
#define TSW_PTP_EVT_PPS_CMD_PPS_EN0_SHIFT (4U)
#define TSW_PTP_EVT_PPS_CMD_PPS_EN0_SET(x) (((uint32_t)(x) << TSW_PTP_EVT_PPS_CMD_PPS_EN0_SHIFT) & TSW_PTP_EVT_PPS_CMD_PPS_EN0_MASK)
#define TSW_PTP_EVT_PPS_CMD_PPS_EN0_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_PPS_CMD_PPS_EN0_MASK) >> TSW_PTP_EVT_PPS_CMD_PPS_EN0_SHIFT)

/*
 * PPS_CMD0 (RW)
 *
 * pps0 command
 */
#define TSW_PTP_EVT_PPS_CMD_PPS_CMD0_MASK (0xFU)
#define TSW_PTP_EVT_PPS_CMD_PPS_CMD0_SHIFT (0U)
#define TSW_PTP_EVT_PPS_CMD_PPS_CMD0_SET(x) (((uint32_t)(x) << TSW_PTP_EVT_PPS_CMD_PPS_CMD0_SHIFT) & TSW_PTP_EVT_PPS_CMD_PPS_CMD0_MASK)
#define TSW_PTP_EVT_PPS_CMD_PPS_CMD0_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_PPS_CMD_PPS_CMD0_MASK) >> TSW_PTP_EVT_PPS_CMD_PPS_CMD0_SHIFT)

/* Bitfield definition for register: PTP_EVT_ATSLO */
/*
 * STSLO (RO)
 *
 * auxiliary fifo read sub seconds info
 */
#define TSW_PTP_EVT_ATSLO_STSLO_MASK (0x7FFFFFFFUL)
#define TSW_PTP_EVT_ATSLO_STSLO_SHIFT (0U)
#define TSW_PTP_EVT_ATSLO_STSLO_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_ATSLO_STSLO_MASK) >> TSW_PTP_EVT_ATSLO_STSLO_SHIFT)

/* Bitfield definition for register: PTP_EVT_ATSHI */
/*
 * STSHI (RO)
 *
 * auxiliary fifo read  seconds info
 */
#define TSW_PTP_EVT_ATSHI_STSHI_MASK (0xFFFFFFFFUL)
#define TSW_PTP_EVT_ATSHI_STSHI_SHIFT (0U)
#define TSW_PTP_EVT_ATSHI_STSHI_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_ATSHI_STSHI_MASK) >> TSW_PTP_EVT_ATSHI_STSHI_SHIFT)

/* Bitfield definition for register: PTP_EVT_PPS0_INTERVAL */
/*
 * PPSINT (RW)
 *
 * PPS0 output signal interval
 */
#define TSW_PTP_EVT_PPS0_INTERVAL_PPSINT_MASK (0xFFFFFFFFUL)
#define TSW_PTP_EVT_PPS0_INTERVAL_PPSINT_SHIFT (0U)
#define TSW_PTP_EVT_PPS0_INTERVAL_PPSINT_SET(x) (((uint32_t)(x) << TSW_PTP_EVT_PPS0_INTERVAL_PPSINT_SHIFT) & TSW_PTP_EVT_PPS0_INTERVAL_PPSINT_MASK)
#define TSW_PTP_EVT_PPS0_INTERVAL_PPSINT_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_PPS0_INTERVAL_PPSINT_MASK) >> TSW_PTP_EVT_PPS0_INTERVAL_PPSINT_SHIFT)

/* Bitfield definition for register: PTP_EVT_PPS0_WIDTH */
/*
 * PPS_WIDTH (RW)
 *
 * pps0 output signal width
 */
#define TSW_PTP_EVT_PPS0_WIDTH_PPS_WIDTH_MASK (0xFFFFFFFFUL)
#define TSW_PTP_EVT_PPS0_WIDTH_PPS_WIDTH_SHIFT (0U)
#define TSW_PTP_EVT_PPS0_WIDTH_PPS_WIDTH_SET(x) (((uint32_t)(x) << TSW_PTP_EVT_PPS0_WIDTH_PPS_WIDTH_SHIFT) & TSW_PTP_EVT_PPS0_WIDTH_PPS_WIDTH_MASK)
#define TSW_PTP_EVT_PPS0_WIDTH_PPS_WIDTH_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_PPS0_WIDTH_PPS_WIDTH_MASK) >> TSW_PTP_EVT_PPS0_WIDTH_PPS_WIDTH_SHIFT)

/* Bitfield definition for register: PTP_EVT_SCP_SEC1 */
/*
 * SCP_SEC (RW)
 *
 * target time seconds
 */
#define TSW_PTP_EVT_SCP_SEC1_SCP_SEC_MASK (0xFFFFFFFFUL)
#define TSW_PTP_EVT_SCP_SEC1_SCP_SEC_SHIFT (0U)
#define TSW_PTP_EVT_SCP_SEC1_SCP_SEC_SET(x) (((uint32_t)(x) << TSW_PTP_EVT_SCP_SEC1_SCP_SEC_SHIFT) & TSW_PTP_EVT_SCP_SEC1_SCP_SEC_MASK)
#define TSW_PTP_EVT_SCP_SEC1_SCP_SEC_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_SCP_SEC1_SCP_SEC_MASK) >> TSW_PTP_EVT_SCP_SEC1_SCP_SEC_SHIFT)

/* Bitfield definition for register: PTP_EVT_SCP_NS1 */
/*
 * SCP_NS (RW)
 *
 * target time sub seconds
 */
#define TSW_PTP_EVT_SCP_NS1_SCP_NS_MASK (0x3FFFFFFFUL)
#define TSW_PTP_EVT_SCP_NS1_SCP_NS_SHIFT (0U)
#define TSW_PTP_EVT_SCP_NS1_SCP_NS_SET(x) (((uint32_t)(x) << TSW_PTP_EVT_SCP_NS1_SCP_NS_SHIFT) & TSW_PTP_EVT_SCP_NS1_SCP_NS_MASK)
#define TSW_PTP_EVT_SCP_NS1_SCP_NS_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_SCP_NS1_SCP_NS_MASK) >> TSW_PTP_EVT_SCP_NS1_SCP_NS_SHIFT)

/* Bitfield definition for register: PTP_EVT_PPS1_INTERVAL */
/*
 * PPSINT (RW)
 *
 * PPS1 output signal interval
 */
#define TSW_PTP_EVT_PPS1_INTERVAL_PPSINT_MASK (0xFFFFFFFFUL)
#define TSW_PTP_EVT_PPS1_INTERVAL_PPSINT_SHIFT (0U)
#define TSW_PTP_EVT_PPS1_INTERVAL_PPSINT_SET(x) (((uint32_t)(x) << TSW_PTP_EVT_PPS1_INTERVAL_PPSINT_SHIFT) & TSW_PTP_EVT_PPS1_INTERVAL_PPSINT_MASK)
#define TSW_PTP_EVT_PPS1_INTERVAL_PPSINT_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_PPS1_INTERVAL_PPSINT_MASK) >> TSW_PTP_EVT_PPS1_INTERVAL_PPSINT_SHIFT)

/* Bitfield definition for register: PTP_EVT_PPS1_WIDTH */
/*
 * PPS_WIDTH (RW)
 *
 * pps1 output signal width
 */
#define TSW_PTP_EVT_PPS1_WIDTH_PPS_WIDTH_MASK (0xFFFFFFFFUL)
#define TSW_PTP_EVT_PPS1_WIDTH_PPS_WIDTH_SHIFT (0U)
#define TSW_PTP_EVT_PPS1_WIDTH_PPS_WIDTH_SET(x) (((uint32_t)(x) << TSW_PTP_EVT_PPS1_WIDTH_PPS_WIDTH_SHIFT) & TSW_PTP_EVT_PPS1_WIDTH_PPS_WIDTH_MASK)
#define TSW_PTP_EVT_PPS1_WIDTH_PPS_WIDTH_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_PPS1_WIDTH_PPS_WIDTH_MASK) >> TSW_PTP_EVT_PPS1_WIDTH_PPS_WIDTH_SHIFT)

/* Bitfield definition for register: PTP_EVT_SCP_SEC2 */
/*
 * SCP_SEC (RW)
 *
 * target time seconds
 */
#define TSW_PTP_EVT_SCP_SEC2_SCP_SEC_MASK (0xFFFFFFFFUL)
#define TSW_PTP_EVT_SCP_SEC2_SCP_SEC_SHIFT (0U)
#define TSW_PTP_EVT_SCP_SEC2_SCP_SEC_SET(x) (((uint32_t)(x) << TSW_PTP_EVT_SCP_SEC2_SCP_SEC_SHIFT) & TSW_PTP_EVT_SCP_SEC2_SCP_SEC_MASK)
#define TSW_PTP_EVT_SCP_SEC2_SCP_SEC_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_SCP_SEC2_SCP_SEC_MASK) >> TSW_PTP_EVT_SCP_SEC2_SCP_SEC_SHIFT)

/* Bitfield definition for register: PTP_EVT_SCP_NS2 */
/*
 * SCP_NS (RW)
 *
 * target time sub seconds
 */
#define TSW_PTP_EVT_SCP_NS2_SCP_NS_MASK (0x3FFFFFFFUL)
#define TSW_PTP_EVT_SCP_NS2_SCP_NS_SHIFT (0U)
#define TSW_PTP_EVT_SCP_NS2_SCP_NS_SET(x) (((uint32_t)(x) << TSW_PTP_EVT_SCP_NS2_SCP_NS_SHIFT) & TSW_PTP_EVT_SCP_NS2_SCP_NS_MASK)
#define TSW_PTP_EVT_SCP_NS2_SCP_NS_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_SCP_NS2_SCP_NS_MASK) >> TSW_PTP_EVT_SCP_NS2_SCP_NS_SHIFT)

/* Bitfield definition for register: PTP_EVT_PPS2_INTERVAL */
/*
 * PPSINT (RW)
 *
 * PPS2 output signal interval
 */
#define TSW_PTP_EVT_PPS2_INTERVAL_PPSINT_MASK (0xFFFFFFFFUL)
#define TSW_PTP_EVT_PPS2_INTERVAL_PPSINT_SHIFT (0U)
#define TSW_PTP_EVT_PPS2_INTERVAL_PPSINT_SET(x) (((uint32_t)(x) << TSW_PTP_EVT_PPS2_INTERVAL_PPSINT_SHIFT) & TSW_PTP_EVT_PPS2_INTERVAL_PPSINT_MASK)
#define TSW_PTP_EVT_PPS2_INTERVAL_PPSINT_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_PPS2_INTERVAL_PPSINT_MASK) >> TSW_PTP_EVT_PPS2_INTERVAL_PPSINT_SHIFT)

/* Bitfield definition for register: PTP_EVT_PPS2_WIDTH */
/*
 * PPS_WIDTH (RW)
 *
 * pps2 output signal width
 */
#define TSW_PTP_EVT_PPS2_WIDTH_PPS_WIDTH_MASK (0xFFFFFFFFUL)
#define TSW_PTP_EVT_PPS2_WIDTH_PPS_WIDTH_SHIFT (0U)
#define TSW_PTP_EVT_PPS2_WIDTH_PPS_WIDTH_SET(x) (((uint32_t)(x) << TSW_PTP_EVT_PPS2_WIDTH_PPS_WIDTH_SHIFT) & TSW_PTP_EVT_PPS2_WIDTH_PPS_WIDTH_MASK)
#define TSW_PTP_EVT_PPS2_WIDTH_PPS_WIDTH_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_PPS2_WIDTH_PPS_WIDTH_MASK) >> TSW_PTP_EVT_PPS2_WIDTH_PPS_WIDTH_SHIFT)

/* Bitfield definition for register: PTP_EVT_SCP_SEC3 */
/*
 * SCP_SEC (RW)
 *
 * target time seconds
 */
#define TSW_PTP_EVT_SCP_SEC3_SCP_SEC_MASK (0xFFFFFFFFUL)
#define TSW_PTP_EVT_SCP_SEC3_SCP_SEC_SHIFT (0U)
#define TSW_PTP_EVT_SCP_SEC3_SCP_SEC_SET(x) (((uint32_t)(x) << TSW_PTP_EVT_SCP_SEC3_SCP_SEC_SHIFT) & TSW_PTP_EVT_SCP_SEC3_SCP_SEC_MASK)
#define TSW_PTP_EVT_SCP_SEC3_SCP_SEC_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_SCP_SEC3_SCP_SEC_MASK) >> TSW_PTP_EVT_SCP_SEC3_SCP_SEC_SHIFT)

/* Bitfield definition for register: PTP_EVT_SCP_NS3 */
/*
 * SCP_NS (RW)
 *
 * target time sub seconds
 */
#define TSW_PTP_EVT_SCP_NS3_SCP_NS_MASK (0x3FFFFFFFUL)
#define TSW_PTP_EVT_SCP_NS3_SCP_NS_SHIFT (0U)
#define TSW_PTP_EVT_SCP_NS3_SCP_NS_SET(x) (((uint32_t)(x) << TSW_PTP_EVT_SCP_NS3_SCP_NS_SHIFT) & TSW_PTP_EVT_SCP_NS3_SCP_NS_MASK)
#define TSW_PTP_EVT_SCP_NS3_SCP_NS_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_SCP_NS3_SCP_NS_MASK) >> TSW_PTP_EVT_SCP_NS3_SCP_NS_SHIFT)

/* Bitfield definition for register: PTP_EVT_PPS3_INTERVAL */
/*
 * PPSINT (RW)
 *
 * PPS3 output signal interval
 */
#define TSW_PTP_EVT_PPS3_INTERVAL_PPSINT_MASK (0xFFFFFFFFUL)
#define TSW_PTP_EVT_PPS3_INTERVAL_PPSINT_SHIFT (0U)
#define TSW_PTP_EVT_PPS3_INTERVAL_PPSINT_SET(x) (((uint32_t)(x) << TSW_PTP_EVT_PPS3_INTERVAL_PPSINT_SHIFT) & TSW_PTP_EVT_PPS3_INTERVAL_PPSINT_MASK)
#define TSW_PTP_EVT_PPS3_INTERVAL_PPSINT_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_PPS3_INTERVAL_PPSINT_MASK) >> TSW_PTP_EVT_PPS3_INTERVAL_PPSINT_SHIFT)

/* Bitfield definition for register: PTP_EVT_PPS3_WIDTH */
/*
 * PPS_WIDTH (RW)
 *
 * pps3 output signal width
 */
#define TSW_PTP_EVT_PPS3_WIDTH_PPS_WIDTH_MASK (0xFFFFFFFFUL)
#define TSW_PTP_EVT_PPS3_WIDTH_PPS_WIDTH_SHIFT (0U)
#define TSW_PTP_EVT_PPS3_WIDTH_PPS_WIDTH_SET(x) (((uint32_t)(x) << TSW_PTP_EVT_PPS3_WIDTH_PPS_WIDTH_SHIFT) & TSW_PTP_EVT_PPS3_WIDTH_PPS_WIDTH_MASK)
#define TSW_PTP_EVT_PPS3_WIDTH_PPS_WIDTH_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_PPS3_WIDTH_PPS_WIDTH_MASK) >> TSW_PTP_EVT_PPS3_WIDTH_PPS_WIDTH_SHIFT)

/* Bitfield definition for register: PTP_EVT_PPS_CTRL0 */
/*
 * PPS_TOD_INTR_MSK (RW)
 *
 * pps tod interrupt enable
 */
#define TSW_PTP_EVT_PPS_CTRL0_PPS_TOD_INTR_MSK_MASK (0x8U)
#define TSW_PTP_EVT_PPS_CTRL0_PPS_TOD_INTR_MSK_SHIFT (3U)
#define TSW_PTP_EVT_PPS_CTRL0_PPS_TOD_INTR_MSK_SET(x) (((uint32_t)(x) << TSW_PTP_EVT_PPS_CTRL0_PPS_TOD_INTR_MSK_SHIFT) & TSW_PTP_EVT_PPS_CTRL0_PPS_TOD_INTR_MSK_MASK)
#define TSW_PTP_EVT_PPS_CTRL0_PPS_TOD_INTR_MSK_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_PPS_CTRL0_PPS_TOD_INTR_MSK_MASK) >> TSW_PTP_EVT_PPS_CTRL0_PPS_TOD_INTR_MSK_SHIFT)

/*
 * TARGET_RAC_INTR_MSK (RW)
 *
 * target timmer interrupt mask
 */
#define TSW_PTP_EVT_PPS_CTRL0_TARGET_RAC_INTR_MSK_MASK (0x4U)
#define TSW_PTP_EVT_PPS_CTRL0_TARGET_RAC_INTR_MSK_SHIFT (2U)
#define TSW_PTP_EVT_PPS_CTRL0_TARGET_RAC_INTR_MSK_SET(x) (((uint32_t)(x) << TSW_PTP_EVT_PPS_CTRL0_TARGET_RAC_INTR_MSK_SHIFT) & TSW_PTP_EVT_PPS_CTRL0_TARGET_RAC_INTR_MSK_MASK)
#define TSW_PTP_EVT_PPS_CTRL0_TARGET_RAC_INTR_MSK_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_PPS_CTRL0_TARGET_RAC_INTR_MSK_MASK) >> TSW_PTP_EVT_PPS_CTRL0_TARGET_RAC_INTR_MSK_SHIFT)

/*
 * FIFO_WR_INTR_MSK (RW)
 *
 * auxiliary snapshot fifo write interrupt enable
 */
#define TSW_PTP_EVT_PPS_CTRL0_FIFO_WR_INTR_MSK_MASK (0x2U)
#define TSW_PTP_EVT_PPS_CTRL0_FIFO_WR_INTR_MSK_SHIFT (1U)
#define TSW_PTP_EVT_PPS_CTRL0_FIFO_WR_INTR_MSK_SET(x) (((uint32_t)(x) << TSW_PTP_EVT_PPS_CTRL0_FIFO_WR_INTR_MSK_SHIFT) & TSW_PTP_EVT_PPS_CTRL0_FIFO_WR_INTR_MSK_MASK)
#define TSW_PTP_EVT_PPS_CTRL0_FIFO_WR_INTR_MSK_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_PPS_CTRL0_FIFO_WR_INTR_MSK_MASK) >> TSW_PTP_EVT_PPS_CTRL0_FIFO_WR_INTR_MSK_SHIFT)

/*
 * TIME_SEL (RW)
 *
 * timer selection
 */
#define TSW_PTP_EVT_PPS_CTRL0_TIME_SEL_MASK (0x1U)
#define TSW_PTP_EVT_PPS_CTRL0_TIME_SEL_SHIFT (0U)
#define TSW_PTP_EVT_PPS_CTRL0_TIME_SEL_SET(x) (((uint32_t)(x) << TSW_PTP_EVT_PPS_CTRL0_TIME_SEL_SHIFT) & TSW_PTP_EVT_PPS_CTRL0_TIME_SEL_MASK)
#define TSW_PTP_EVT_PPS_CTRL0_TIME_SEL_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_PPS_CTRL0_TIME_SEL_MASK) >> TSW_PTP_EVT_PPS_CTRL0_TIME_SEL_SHIFT)

/* Bitfield definition for register: PTP_EVT_PPS_SEL */
/*
 * PPS3_SEL (RW)
 *
 * pps selection for pps3
 */
#define TSW_PTP_EVT_PPS_SEL_PPS3_SEL_MASK (0x1F000000UL)
#define TSW_PTP_EVT_PPS_SEL_PPS3_SEL_SHIFT (24U)
#define TSW_PTP_EVT_PPS_SEL_PPS3_SEL_SET(x) (((uint32_t)(x) << TSW_PTP_EVT_PPS_SEL_PPS3_SEL_SHIFT) & TSW_PTP_EVT_PPS_SEL_PPS3_SEL_MASK)
#define TSW_PTP_EVT_PPS_SEL_PPS3_SEL_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_PPS_SEL_PPS3_SEL_MASK) >> TSW_PTP_EVT_PPS_SEL_PPS3_SEL_SHIFT)

/*
 * PPS2_SEL (RW)
 *
 * pps selection for pps2
 */
#define TSW_PTP_EVT_PPS_SEL_PPS2_SEL_MASK (0x1F0000UL)
#define TSW_PTP_EVT_PPS_SEL_PPS2_SEL_SHIFT (16U)
#define TSW_PTP_EVT_PPS_SEL_PPS2_SEL_SET(x) (((uint32_t)(x) << TSW_PTP_EVT_PPS_SEL_PPS2_SEL_SHIFT) & TSW_PTP_EVT_PPS_SEL_PPS2_SEL_MASK)
#define TSW_PTP_EVT_PPS_SEL_PPS2_SEL_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_PPS_SEL_PPS2_SEL_MASK) >> TSW_PTP_EVT_PPS_SEL_PPS2_SEL_SHIFT)

/*
 * PPS1_SEL (RW)
 *
 * pps selection for pps1
 */
#define TSW_PTP_EVT_PPS_SEL_PPS1_SEL_MASK (0x1F00U)
#define TSW_PTP_EVT_PPS_SEL_PPS1_SEL_SHIFT (8U)
#define TSW_PTP_EVT_PPS_SEL_PPS1_SEL_SET(x) (((uint32_t)(x) << TSW_PTP_EVT_PPS_SEL_PPS1_SEL_SHIFT) & TSW_PTP_EVT_PPS_SEL_PPS1_SEL_MASK)
#define TSW_PTP_EVT_PPS_SEL_PPS1_SEL_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_PPS_SEL_PPS1_SEL_MASK) >> TSW_PTP_EVT_PPS_SEL_PPS1_SEL_SHIFT)

/*
 * PPS0_SEL (RW)
 *
 * pps selection for pps0
 */
#define TSW_PTP_EVT_PPS_SEL_PPS0_SEL_MASK (0x1FU)
#define TSW_PTP_EVT_PPS_SEL_PPS0_SEL_SHIFT (0U)
#define TSW_PTP_EVT_PPS_SEL_PPS0_SEL_SET(x) (((uint32_t)(x) << TSW_PTP_EVT_PPS_SEL_PPS0_SEL_SHIFT) & TSW_PTP_EVT_PPS_SEL_PPS0_SEL_MASK)
#define TSW_PTP_EVT_PPS_SEL_PPS0_SEL_GET(x) (((uint32_t)(x) & TSW_PTP_EVT_PPS_SEL_PPS0_SEL_MASK) >> TSW_PTP_EVT_PPS_SEL_PPS0_SEL_SHIFT)

/* Bitfield definition for register: SOFT_RST_CTRL */
/*
 * TSN_CORE_RST (RW)
 *
 * tsn core reset control
 */
#define TSW_SOFT_RST_CTRL_TSN_CORE_RST_MASK (0x800U)
#define TSW_SOFT_RST_CTRL_TSN_CORE_RST_SHIFT (11U)
#define TSW_SOFT_RST_CTRL_TSN_CORE_RST_SET(x) (((uint32_t)(x) << TSW_SOFT_RST_CTRL_TSN_CORE_RST_SHIFT) & TSW_SOFT_RST_CTRL_TSN_CORE_RST_MASK)
#define TSW_SOFT_RST_CTRL_TSN_CORE_RST_GET(x) (((uint32_t)(x) & TSW_SOFT_RST_CTRL_TSN_CORE_RST_MASK) >> TSW_SOFT_RST_CTRL_TSN_CORE_RST_SHIFT)

/*
 * PTP_EVT_RST (RW)
 *
 * ptp event module reset control
 */
#define TSW_SOFT_RST_CTRL_PTP_EVT_RST_MASK (0x400U)
#define TSW_SOFT_RST_CTRL_PTP_EVT_RST_SHIFT (10U)
#define TSW_SOFT_RST_CTRL_PTP_EVT_RST_SET(x) (((uint32_t)(x) << TSW_SOFT_RST_CTRL_PTP_EVT_RST_SHIFT) & TSW_SOFT_RST_CTRL_PTP_EVT_RST_MASK)
#define TSW_SOFT_RST_CTRL_PTP_EVT_RST_GET(x) (((uint32_t)(x) & TSW_SOFT_RST_CTRL_PTP_EVT_RST_MASK) >> TSW_SOFT_RST_CTRL_PTP_EVT_RST_SHIFT)

/*
 * DMA0_RST (RW)
 *
 * dma0 reset control
 */
#define TSW_SOFT_RST_CTRL_DMA0_RST_MASK (0x100U)
#define TSW_SOFT_RST_CTRL_DMA0_RST_SHIFT (8U)
#define TSW_SOFT_RST_CTRL_DMA0_RST_SET(x) (((uint32_t)(x) << TSW_SOFT_RST_CTRL_DMA0_RST_SHIFT) & TSW_SOFT_RST_CTRL_DMA0_RST_MASK)
#define TSW_SOFT_RST_CTRL_DMA0_RST_GET(x) (((uint32_t)(x) & TSW_SOFT_RST_CTRL_DMA0_RST_MASK) >> TSW_SOFT_RST_CTRL_DMA0_RST_SHIFT)

/*
 * PORT3_RX_RST (RW)
 *
 * port3 rx reset control
 */
#define TSW_SOFT_RST_CTRL_PORT3_RX_RST_MASK (0x20U)
#define TSW_SOFT_RST_CTRL_PORT3_RX_RST_SHIFT (5U)
#define TSW_SOFT_RST_CTRL_PORT3_RX_RST_SET(x) (((uint32_t)(x) << TSW_SOFT_RST_CTRL_PORT3_RX_RST_SHIFT) & TSW_SOFT_RST_CTRL_PORT3_RX_RST_MASK)
#define TSW_SOFT_RST_CTRL_PORT3_RX_RST_GET(x) (((uint32_t)(x) & TSW_SOFT_RST_CTRL_PORT3_RX_RST_MASK) >> TSW_SOFT_RST_CTRL_PORT3_RX_RST_SHIFT)

/*
 * PORT3_TX_RST (RW)
 *
 * port3 tx reset control
 */
#define TSW_SOFT_RST_CTRL_PORT3_TX_RST_MASK (0x10U)
#define TSW_SOFT_RST_CTRL_PORT3_TX_RST_SHIFT (4U)
#define TSW_SOFT_RST_CTRL_PORT3_TX_RST_SET(x) (((uint32_t)(x) << TSW_SOFT_RST_CTRL_PORT3_TX_RST_SHIFT) & TSW_SOFT_RST_CTRL_PORT3_TX_RST_MASK)
#define TSW_SOFT_RST_CTRL_PORT3_TX_RST_GET(x) (((uint32_t)(x) & TSW_SOFT_RST_CTRL_PORT3_TX_RST_MASK) >> TSW_SOFT_RST_CTRL_PORT3_TX_RST_SHIFT)

/*
 * PORT2_RX_RST (RW)
 *
 * port2 rx reset control
 */
#define TSW_SOFT_RST_CTRL_PORT2_RX_RST_MASK (0x8U)
#define TSW_SOFT_RST_CTRL_PORT2_RX_RST_SHIFT (3U)
#define TSW_SOFT_RST_CTRL_PORT2_RX_RST_SET(x) (((uint32_t)(x) << TSW_SOFT_RST_CTRL_PORT2_RX_RST_SHIFT) & TSW_SOFT_RST_CTRL_PORT2_RX_RST_MASK)
#define TSW_SOFT_RST_CTRL_PORT2_RX_RST_GET(x) (((uint32_t)(x) & TSW_SOFT_RST_CTRL_PORT2_RX_RST_MASK) >> TSW_SOFT_RST_CTRL_PORT2_RX_RST_SHIFT)

/*
 * PORT2_TX_RST (RW)
 *
 * port2 tx reset control
 */
#define TSW_SOFT_RST_CTRL_PORT2_TX_RST_MASK (0x4U)
#define TSW_SOFT_RST_CTRL_PORT2_TX_RST_SHIFT (2U)
#define TSW_SOFT_RST_CTRL_PORT2_TX_RST_SET(x) (((uint32_t)(x) << TSW_SOFT_RST_CTRL_PORT2_TX_RST_SHIFT) & TSW_SOFT_RST_CTRL_PORT2_TX_RST_MASK)
#define TSW_SOFT_RST_CTRL_PORT2_TX_RST_GET(x) (((uint32_t)(x) & TSW_SOFT_RST_CTRL_PORT2_TX_RST_MASK) >> TSW_SOFT_RST_CTRL_PORT2_TX_RST_SHIFT)

/*
 * PORT1_RX_RST (RW)
 *
 * port1 rx reset control
 */
#define TSW_SOFT_RST_CTRL_PORT1_RX_RST_MASK (0x2U)
#define TSW_SOFT_RST_CTRL_PORT1_RX_RST_SHIFT (1U)
#define TSW_SOFT_RST_CTRL_PORT1_RX_RST_SET(x) (((uint32_t)(x) << TSW_SOFT_RST_CTRL_PORT1_RX_RST_SHIFT) & TSW_SOFT_RST_CTRL_PORT1_RX_RST_MASK)
#define TSW_SOFT_RST_CTRL_PORT1_RX_RST_GET(x) (((uint32_t)(x) & TSW_SOFT_RST_CTRL_PORT1_RX_RST_MASK) >> TSW_SOFT_RST_CTRL_PORT1_RX_RST_SHIFT)

/*
 * PORT1_TX_RST (RW)
 *
 * port1 tx reset control
 */
#define TSW_SOFT_RST_CTRL_PORT1_TX_RST_MASK (0x1U)
#define TSW_SOFT_RST_CTRL_PORT1_TX_RST_SHIFT (0U)
#define TSW_SOFT_RST_CTRL_PORT1_TX_RST_SET(x) (((uint32_t)(x) << TSW_SOFT_RST_CTRL_PORT1_TX_RST_SHIFT) & TSW_SOFT_RST_CTRL_PORT1_TX_RST_MASK)
#define TSW_SOFT_RST_CTRL_PORT1_TX_RST_GET(x) (((uint32_t)(x) & TSW_SOFT_RST_CTRL_PORT1_TX_RST_MASK) >> TSW_SOFT_RST_CTRL_PORT1_TX_RST_SHIFT)

/* Bitfield definition for register: CPU_PORT_PORT_MAIN_TAGGING */
/*
 * FORCE (R/W)
 *
 * The VLAN-TAG with PVID will be inserted in every frame from Host as their first VLAN-TAG. This can be used for double tagging of tagged/trunk ports
 */
#define TSW_CPU_PORT_PORT_MAIN_TAGGING_FORCE_MASK (0x20000UL)
#define TSW_CPU_PORT_PORT_MAIN_TAGGING_FORCE_SHIFT (17U)
#define TSW_CPU_PORT_PORT_MAIN_TAGGING_FORCE_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_PORT_MAIN_TAGGING_FORCE_SHIFT) & TSW_CPU_PORT_PORT_MAIN_TAGGING_FORCE_MASK)
#define TSW_CPU_PORT_PORT_MAIN_TAGGING_FORCE_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_PORT_MAIN_TAGGING_FORCE_MASK) >> TSW_CPU_PORT_PORT_MAIN_TAGGING_FORCE_SHIFT)

/*
 * ACCESS (R/W)
 *
 * Every tagged frame not matching PVID is filtered out. Every untagged ingress  frame will be tagged with PVID. Every egress frame with PVID will be untagged
 */
#define TSW_CPU_PORT_PORT_MAIN_TAGGING_ACCESS_MASK (0x10000UL)
#define TSW_CPU_PORT_PORT_MAIN_TAGGING_ACCESS_SHIFT (16U)
#define TSW_CPU_PORT_PORT_MAIN_TAGGING_ACCESS_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_PORT_MAIN_TAGGING_ACCESS_SHIFT) & TSW_CPU_PORT_PORT_MAIN_TAGGING_ACCESS_MASK)
#define TSW_CPU_PORT_PORT_MAIN_TAGGING_ACCESS_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_PORT_MAIN_TAGGING_ACCESS_MASK) >> TSW_CPU_PORT_PORT_MAIN_TAGGING_ACCESS_SHIFT)

/*
 * PCP (R/W)
 *
 * VLAN-TCI: Priority Code Point, used when tagged.
 */
#define TSW_CPU_PORT_PORT_MAIN_TAGGING_PCP_MASK (0xE000U)
#define TSW_CPU_PORT_PORT_MAIN_TAGGING_PCP_SHIFT (13U)
#define TSW_CPU_PORT_PORT_MAIN_TAGGING_PCP_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_PORT_MAIN_TAGGING_PCP_SHIFT) & TSW_CPU_PORT_PORT_MAIN_TAGGING_PCP_MASK)
#define TSW_CPU_PORT_PORT_MAIN_TAGGING_PCP_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_PORT_MAIN_TAGGING_PCP_MASK) >> TSW_CPU_PORT_PORT_MAIN_TAGGING_PCP_SHIFT)

/*
 * DEI (R/W)
 *
 * VLAN-TCI: Drop Eligible Indicator, used when tagged.
 */
#define TSW_CPU_PORT_PORT_MAIN_TAGGING_DEI_MASK (0x1000U)
#define TSW_CPU_PORT_PORT_MAIN_TAGGING_DEI_SHIFT (12U)
#define TSW_CPU_PORT_PORT_MAIN_TAGGING_DEI_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_PORT_MAIN_TAGGING_DEI_SHIFT) & TSW_CPU_PORT_PORT_MAIN_TAGGING_DEI_MASK)
#define TSW_CPU_PORT_PORT_MAIN_TAGGING_DEI_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_PORT_MAIN_TAGGING_DEI_MASK) >> TSW_CPU_PORT_PORT_MAIN_TAGGING_DEI_SHIFT)

/*
 * PVID (R/W)
 *
 * Native VLAN of Port. Untagged traffic will be tagged with the native VLAN-ID By default the Port uses VLAN 1.
 */
#define TSW_CPU_PORT_PORT_MAIN_TAGGING_PVID_MASK (0xFFFU)
#define TSW_CPU_PORT_PORT_MAIN_TAGGING_PVID_SHIFT (0U)
#define TSW_CPU_PORT_PORT_MAIN_TAGGING_PVID_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_PORT_MAIN_TAGGING_PVID_SHIFT) & TSW_CPU_PORT_PORT_MAIN_TAGGING_PVID_MASK)
#define TSW_CPU_PORT_PORT_MAIN_TAGGING_PVID_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_PORT_MAIN_TAGGING_PVID_MASK) >> TSW_CPU_PORT_PORT_MAIN_TAGGING_PVID_SHIFT)

/* Bitfield definition for register: CPU_PORT_PORT_MAIN_ENNABLE */
/*
 * EN_SF (R/W)
 *
 * only applicable for CPU-Port at egress: '1' to use S&F FIFO and '0' disable S&F FIFO. Changing during frame operation can lead to frame corruption
 */
#define TSW_CPU_PORT_PORT_MAIN_ENNABLE_EN_SF_MASK (0x2U)
#define TSW_CPU_PORT_PORT_MAIN_ENNABLE_EN_SF_SHIFT (1U)
#define TSW_CPU_PORT_PORT_MAIN_ENNABLE_EN_SF_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_PORT_MAIN_ENNABLE_EN_SF_SHIFT) & TSW_CPU_PORT_PORT_MAIN_ENNABLE_EN_SF_MASK)
#define TSW_CPU_PORT_PORT_MAIN_ENNABLE_EN_SF_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_PORT_MAIN_ENNABLE_EN_SF_MASK) >> TSW_CPU_PORT_PORT_MAIN_ENNABLE_EN_SF_SHIFT)

/*
 * EN_QCI (R/W)
 *
 * if QCI is present at selected egress port, '1' to use QCI and '0' disable QCI. Changing during frame operation can lead to frame corruption.
 */
#define TSW_CPU_PORT_PORT_MAIN_ENNABLE_EN_QCI_MASK (0x1U)
#define TSW_CPU_PORT_PORT_MAIN_ENNABLE_EN_QCI_SHIFT (0U)
#define TSW_CPU_PORT_PORT_MAIN_ENNABLE_EN_QCI_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_PORT_MAIN_ENNABLE_EN_QCI_SHIFT) & TSW_CPU_PORT_PORT_MAIN_ENNABLE_EN_QCI_MASK)
#define TSW_CPU_PORT_PORT_MAIN_ENNABLE_EN_QCI_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_PORT_MAIN_ENNABLE_EN_QCI_MASK) >> TSW_CPU_PORT_PORT_MAIN_ENNABLE_EN_QCI_SHIFT)

/* Bitfield definition for register: CPU_PORT_EGRESS_STMID_ESELECT */
/*
 * ESEL (RO)
 *
 * Select entry. Selected entry mapped to 0x40 – 0x5C.
 */
#define TSW_CPU_PORT_EGRESS_STMID_ESELECT_ESEL_MASK (0xFFU)
#define TSW_CPU_PORT_EGRESS_STMID_ESELECT_ESEL_SHIFT (0U)
#define TSW_CPU_PORT_EGRESS_STMID_ESELECT_ESEL_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_EGRESS_STMID_ESELECT_ESEL_MASK) >> TSW_CPU_PORT_EGRESS_STMID_ESELECT_ESEL_SHIFT)

/* Bitfield definition for register: CPU_PORT_EGRESS_STMID_CONTROL */
/*
 * SID (R/W)
 *
 * Stream ID – inserted to header on match
 */
#define TSW_CPU_PORT_EGRESS_STMID_CONTROL_SID_MASK (0xFF00U)
#define TSW_CPU_PORT_EGRESS_STMID_CONTROL_SID_SHIFT (8U)
#define TSW_CPU_PORT_EGRESS_STMID_CONTROL_SID_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_EGRESS_STMID_CONTROL_SID_SHIFT) & TSW_CPU_PORT_EGRESS_STMID_CONTROL_SID_MASK)
#define TSW_CPU_PORT_EGRESS_STMID_CONTROL_SID_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_EGRESS_STMID_CONTROL_SID_MASK) >> TSW_CPU_PORT_EGRESS_STMID_CONTROL_SID_SHIFT)

/*
 * SEQGEN (R/W)
 *
 * Sequence number generation enable
 */
#define TSW_CPU_PORT_EGRESS_STMID_CONTROL_SEQGEN_MASK (0x80U)
#define TSW_CPU_PORT_EGRESS_STMID_CONTROL_SEQGEN_SHIFT (7U)
#define TSW_CPU_PORT_EGRESS_STMID_CONTROL_SEQGEN_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_EGRESS_STMID_CONTROL_SEQGEN_SHIFT) & TSW_CPU_PORT_EGRESS_STMID_CONTROL_SEQGEN_MASK)
#define TSW_CPU_PORT_EGRESS_STMID_CONTROL_SEQGEN_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_EGRESS_STMID_CONTROL_SEQGEN_MASK) >> TSW_CPU_PORT_EGRESS_STMID_CONTROL_SEQGEN_SHIFT)

/*
 * ACTCTL (R/W)
 *
 * Active Destination MAC – control. See Table 6-6.
 */
#define TSW_CPU_PORT_EGRESS_STMID_CONTROL_ACTCTL_MASK (0x30U)
#define TSW_CPU_PORT_EGRESS_STMID_CONTROL_ACTCTL_SHIFT (4U)
#define TSW_CPU_PORT_EGRESS_STMID_CONTROL_ACTCTL_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_EGRESS_STMID_CONTROL_ACTCTL_SHIFT) & TSW_CPU_PORT_EGRESS_STMID_CONTROL_ACTCTL_MASK)
#define TSW_CPU_PORT_EGRESS_STMID_CONTROL_ACTCTL_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_EGRESS_STMID_CONTROL_ACTCTL_MASK) >> TSW_CPU_PORT_EGRESS_STMID_CONTROL_ACTCTL_SHIFT)

/*
 * SMAC (R/W)
 *
 * 0: Lookup by Destination MAC 1: Lookup by Source MAC
 */
#define TSW_CPU_PORT_EGRESS_STMID_CONTROL_SMAC_MASK (0x8U)
#define TSW_CPU_PORT_EGRESS_STMID_CONTROL_SMAC_SHIFT (3U)
#define TSW_CPU_PORT_EGRESS_STMID_CONTROL_SMAC_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_EGRESS_STMID_CONTROL_SMAC_SHIFT) & TSW_CPU_PORT_EGRESS_STMID_CONTROL_SMAC_MASK)
#define TSW_CPU_PORT_EGRESS_STMID_CONTROL_SMAC_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_EGRESS_STMID_CONTROL_SMAC_MASK) >> TSW_CPU_PORT_EGRESS_STMID_CONTROL_SMAC_SHIFT)

/*
 * MODE (R/W)
 *
 * Lookup mode. 1:Priority – a frame must be untagged or priority tagged ; 2:Tagged – a frame must have a VLAN tag ; 3:All – a frame can be tagged or untagged
 */
#define TSW_CPU_PORT_EGRESS_STMID_CONTROL_MODE_MASK (0x6U)
#define TSW_CPU_PORT_EGRESS_STMID_CONTROL_MODE_SHIFT (1U)
#define TSW_CPU_PORT_EGRESS_STMID_CONTROL_MODE_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_EGRESS_STMID_CONTROL_MODE_SHIFT) & TSW_CPU_PORT_EGRESS_STMID_CONTROL_MODE_MASK)
#define TSW_CPU_PORT_EGRESS_STMID_CONTROL_MODE_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_EGRESS_STMID_CONTROL_MODE_MASK) >> TSW_CPU_PORT_EGRESS_STMID_CONTROL_MODE_SHIFT)

/*
 * EN (R/W)
 *
 * Enable entry
 */
#define TSW_CPU_PORT_EGRESS_STMID_CONTROL_EN_MASK (0x1U)
#define TSW_CPU_PORT_EGRESS_STMID_CONTROL_EN_SHIFT (0U)
#define TSW_CPU_PORT_EGRESS_STMID_CONTROL_EN_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_EGRESS_STMID_CONTROL_EN_SHIFT) & TSW_CPU_PORT_EGRESS_STMID_CONTROL_EN_MASK)
#define TSW_CPU_PORT_EGRESS_STMID_CONTROL_EN_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_EGRESS_STMID_CONTROL_EN_MASK) >> TSW_CPU_PORT_EGRESS_STMID_CONTROL_EN_SHIFT)

/* Bitfield definition for register: CPU_PORT_EGRESS_STMID_SEQNO */
/*
 * SEQNO (R/WC)
 *
 * Sequence number – next number when generating,any write access to clear.
 */
#define TSW_CPU_PORT_EGRESS_STMID_SEQNO_SEQNO_MASK (0xFFFFU)
#define TSW_CPU_PORT_EGRESS_STMID_SEQNO_SEQNO_SHIFT (0U)
#define TSW_CPU_PORT_EGRESS_STMID_SEQNO_SEQNO_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_EGRESS_STMID_SEQNO_SEQNO_SHIFT) & TSW_CPU_PORT_EGRESS_STMID_SEQNO_SEQNO_MASK)
#define TSW_CPU_PORT_EGRESS_STMID_SEQNO_SEQNO_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_EGRESS_STMID_SEQNO_SEQNO_MASK) >> TSW_CPU_PORT_EGRESS_STMID_SEQNO_SEQNO_SHIFT)

/* Bitfield definition for register: CPU_PORT_EGRESS_STMID_MATCHCNT */
/*
 * MATCH (R/WC)
 *
 * Entry match counter – any write access to clear.
 */
#define TSW_CPU_PORT_EGRESS_STMID_MATCHCNT_MATCH_MASK (0xFFFFFFFFUL)
#define TSW_CPU_PORT_EGRESS_STMID_MATCHCNT_MATCH_SHIFT (0U)
#define TSW_CPU_PORT_EGRESS_STMID_MATCHCNT_MATCH_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_EGRESS_STMID_MATCHCNT_MATCH_SHIFT) & TSW_CPU_PORT_EGRESS_STMID_MATCHCNT_MATCH_MASK)
#define TSW_CPU_PORT_EGRESS_STMID_MATCHCNT_MATCH_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_EGRESS_STMID_MATCHCNT_MATCH_MASK) >> TSW_CPU_PORT_EGRESS_STMID_MATCHCNT_MATCH_SHIFT)

/* Bitfield definition for register: CPU_PORT_EGRESS_STMID_MACLO */
/*
 * MACL (R/WC)
 *
 * MAC-Address [31:0] used by lookup.
 */
#define TSW_CPU_PORT_EGRESS_STMID_MACLO_MACL_MASK (0xFFFFFFFFUL)
#define TSW_CPU_PORT_EGRESS_STMID_MACLO_MACL_SHIFT (0U)
#define TSW_CPU_PORT_EGRESS_STMID_MACLO_MACL_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_EGRESS_STMID_MACLO_MACL_SHIFT) & TSW_CPU_PORT_EGRESS_STMID_MACLO_MACL_MASK)
#define TSW_CPU_PORT_EGRESS_STMID_MACLO_MACL_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_EGRESS_STMID_MACLO_MACL_MASK) >> TSW_CPU_PORT_EGRESS_STMID_MACLO_MACL_SHIFT)

/* Bitfield definition for register: CPU_PORT_EGRESS_STMID_MACHI */
/*
 * VID (R/W)
 *
 * VLAN ID used by lookup.
 */
#define TSW_CPU_PORT_EGRESS_STMID_MACHI_VID_MASK (0xFFF0000UL)
#define TSW_CPU_PORT_EGRESS_STMID_MACHI_VID_SHIFT (16U)
#define TSW_CPU_PORT_EGRESS_STMID_MACHI_VID_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_EGRESS_STMID_MACHI_VID_SHIFT) & TSW_CPU_PORT_EGRESS_STMID_MACHI_VID_MASK)
#define TSW_CPU_PORT_EGRESS_STMID_MACHI_VID_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_EGRESS_STMID_MACHI_VID_MASK) >> TSW_CPU_PORT_EGRESS_STMID_MACHI_VID_SHIFT)

/*
 * MATCH (R/W)
 *
 * MAC-Address [47:31] used by lookup.
 */
#define TSW_CPU_PORT_EGRESS_STMID_MACHI_MATCH_MASK (0xFFFFU)
#define TSW_CPU_PORT_EGRESS_STMID_MACHI_MATCH_SHIFT (0U)
#define TSW_CPU_PORT_EGRESS_STMID_MACHI_MATCH_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_EGRESS_STMID_MACHI_MATCH_SHIFT) & TSW_CPU_PORT_EGRESS_STMID_MACHI_MATCH_MASK)
#define TSW_CPU_PORT_EGRESS_STMID_MACHI_MATCH_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_EGRESS_STMID_MACHI_MATCH_MASK) >> TSW_CPU_PORT_EGRESS_STMID_MACHI_MATCH_SHIFT)

/* Bitfield definition for register: CPU_PORT_EGRESS_STMID_AMACHI */
/*
 * APCP (R/W)
 *
 * Active Destination MAC, PCP
 */
#define TSW_CPU_PORT_EGRESS_STMID_AMACHI_APCP_MASK (0xF0000000UL)
#define TSW_CPU_PORT_EGRESS_STMID_AMACHI_APCP_SHIFT (28U)
#define TSW_CPU_PORT_EGRESS_STMID_AMACHI_APCP_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_EGRESS_STMID_AMACHI_APCP_SHIFT) & TSW_CPU_PORT_EGRESS_STMID_AMACHI_APCP_MASK)
#define TSW_CPU_PORT_EGRESS_STMID_AMACHI_APCP_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_EGRESS_STMID_AMACHI_APCP_MASK) >> TSW_CPU_PORT_EGRESS_STMID_AMACHI_APCP_SHIFT)

/*
 * AVID (R/W)
 *
 * Active Destination MAC, VLAN ID
 */
#define TSW_CPU_PORT_EGRESS_STMID_AMACHI_AVID_MASK (0xFFF0000UL)
#define TSW_CPU_PORT_EGRESS_STMID_AMACHI_AVID_SHIFT (16U)
#define TSW_CPU_PORT_EGRESS_STMID_AMACHI_AVID_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_EGRESS_STMID_AMACHI_AVID_SHIFT) & TSW_CPU_PORT_EGRESS_STMID_AMACHI_AVID_MASK)
#define TSW_CPU_PORT_EGRESS_STMID_AMACHI_AVID_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_EGRESS_STMID_AMACHI_AVID_MASK) >> TSW_CPU_PORT_EGRESS_STMID_AMACHI_AVID_SHIFT)

/*
 * AMACH (R/W)
 *
 * Active Destination MAC, MAC-Address [47:32]
 */
#define TSW_CPU_PORT_EGRESS_STMID_AMACHI_AMACH_MASK (0xFFFFU)
#define TSW_CPU_PORT_EGRESS_STMID_AMACHI_AMACH_SHIFT (0U)
#define TSW_CPU_PORT_EGRESS_STMID_AMACHI_AMACH_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_EGRESS_STMID_AMACHI_AMACH_SHIFT) & TSW_CPU_PORT_EGRESS_STMID_AMACHI_AMACH_MASK)
#define TSW_CPU_PORT_EGRESS_STMID_AMACHI_AMACH_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_EGRESS_STMID_AMACHI_AMACH_MASK) >> TSW_CPU_PORT_EGRESS_STMID_AMACHI_AMACH_SHIFT)

/* Bitfield definition for register: CPU_PORT_EGRESS_FRER_CONTROL */
/*
 * LATER (R/WC)
 *
 * Latent error flag – write 1 to clear
 */
#define TSW_CPU_PORT_EGRESS_FRER_CONTROL_LATER_MASK (0x2U)
#define TSW_CPU_PORT_EGRESS_FRER_CONTROL_LATER_SHIFT (1U)
#define TSW_CPU_PORT_EGRESS_FRER_CONTROL_LATER_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_EGRESS_FRER_CONTROL_LATER_SHIFT) & TSW_CPU_PORT_EGRESS_FRER_CONTROL_LATER_MASK)
#define TSW_CPU_PORT_EGRESS_FRER_CONTROL_LATER_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_EGRESS_FRER_CONTROL_LATER_MASK) >> TSW_CPU_PORT_EGRESS_FRER_CONTROL_LATER_SHIFT)

/*
 * RTENC (R/W)
 *
 * R-TAG encoding enable.
 */
#define TSW_CPU_PORT_EGRESS_FRER_CONTROL_RTENC_MASK (0x1U)
#define TSW_CPU_PORT_EGRESS_FRER_CONTROL_RTENC_SHIFT (0U)
#define TSW_CPU_PORT_EGRESS_FRER_CONTROL_RTENC_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_EGRESS_FRER_CONTROL_RTENC_SHIFT) & TSW_CPU_PORT_EGRESS_FRER_CONTROL_RTENC_MASK)
#define TSW_CPU_PORT_EGRESS_FRER_CONTROL_RTENC_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_EGRESS_FRER_CONTROL_RTENC_MASK) >> TSW_CPU_PORT_EGRESS_FRER_CONTROL_RTENC_SHIFT)

/* Bitfield definition for register: CPU_PORT_EGRESS_FRER_SIDSEL */
/*
 * SID (R/W)
 *
 * Stream ID selection for host access to IRFUNC and SRFUNC.
 */
#define TSW_CPU_PORT_EGRESS_FRER_SIDSEL_SID_MASK (0xFFU)
#define TSW_CPU_PORT_EGRESS_FRER_SIDSEL_SID_SHIFT (0U)
#define TSW_CPU_PORT_EGRESS_FRER_SIDSEL_SID_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_EGRESS_FRER_SIDSEL_SID_SHIFT) & TSW_CPU_PORT_EGRESS_FRER_SIDSEL_SID_MASK)
#define TSW_CPU_PORT_EGRESS_FRER_SIDSEL_SID_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_EGRESS_FRER_SIDSEL_SID_MASK) >> TSW_CPU_PORT_EGRESS_FRER_SIDSEL_SID_SHIFT)

/* Bitfield definition for register: CPU_PORT_EGRESS_FRER_IRFUNC */
/*
 * FEN (R/W)
 *
 * Individual recovery function: FEN – enable function for stream SIDSEL.SID. FIDX – function index for stream SIDSEL.SID If function does not exists (FIDX >= 2**FD), FEN will be set to 0.
 */
#define TSW_CPU_PORT_EGRESS_FRER_IRFUNC_FEN_MASK (0x80000000UL)
#define TSW_CPU_PORT_EGRESS_FRER_IRFUNC_FEN_SHIFT (31U)
#define TSW_CPU_PORT_EGRESS_FRER_IRFUNC_FEN_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_EGRESS_FRER_IRFUNC_FEN_SHIFT) & TSW_CPU_PORT_EGRESS_FRER_IRFUNC_FEN_MASK)
#define TSW_CPU_PORT_EGRESS_FRER_IRFUNC_FEN_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_EGRESS_FRER_IRFUNC_FEN_MASK) >> TSW_CPU_PORT_EGRESS_FRER_IRFUNC_FEN_SHIFT)

/*
 * FIDX (R/W)
 *
 */
#define TSW_CPU_PORT_EGRESS_FRER_IRFUNC_FIDX_MASK (0xFFU)
#define TSW_CPU_PORT_EGRESS_FRER_IRFUNC_FIDX_SHIFT (0U)
#define TSW_CPU_PORT_EGRESS_FRER_IRFUNC_FIDX_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_EGRESS_FRER_IRFUNC_FIDX_SHIFT) & TSW_CPU_PORT_EGRESS_FRER_IRFUNC_FIDX_MASK)
#define TSW_CPU_PORT_EGRESS_FRER_IRFUNC_FIDX_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_EGRESS_FRER_IRFUNC_FIDX_MASK) >> TSW_CPU_PORT_EGRESS_FRER_IRFUNC_FIDX_SHIFT)

/* Bitfield definition for register: CPU_PORT_EGRESS_FRER_SRFUNC */
/*
 * FEN (R/W)
 *
 * Sequence recovery function: FEN – enable function for stream SIDSEL.SID. FIDX – function index for stream SIDSEL.SID If function does not exists (FIDX >= 2**FD), FEN will be set to 0.
 */
#define TSW_CPU_PORT_EGRESS_FRER_SRFUNC_FEN_MASK (0x80000000UL)
#define TSW_CPU_PORT_EGRESS_FRER_SRFUNC_FEN_SHIFT (31U)
#define TSW_CPU_PORT_EGRESS_FRER_SRFUNC_FEN_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_EGRESS_FRER_SRFUNC_FEN_SHIFT) & TSW_CPU_PORT_EGRESS_FRER_SRFUNC_FEN_MASK)
#define TSW_CPU_PORT_EGRESS_FRER_SRFUNC_FEN_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_EGRESS_FRER_SRFUNC_FEN_MASK) >> TSW_CPU_PORT_EGRESS_FRER_SRFUNC_FEN_SHIFT)

/*
 * FIDX (R/W)
 *
 */
#define TSW_CPU_PORT_EGRESS_FRER_SRFUNC_FIDX_MASK (0xFFU)
#define TSW_CPU_PORT_EGRESS_FRER_SRFUNC_FIDX_SHIFT (0U)
#define TSW_CPU_PORT_EGRESS_FRER_SRFUNC_FIDX_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_EGRESS_FRER_SRFUNC_FIDX_SHIFT) & TSW_CPU_PORT_EGRESS_FRER_SRFUNC_FIDX_MASK)
#define TSW_CPU_PORT_EGRESS_FRER_SRFUNC_FIDX_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_EGRESS_FRER_SRFUNC_FIDX_MASK) >> TSW_CPU_PORT_EGRESS_FRER_SRFUNC_FIDX_SHIFT)

/* Bitfield definition for register: CPU_PORT_EGRESS_FRER_FSELECT */
/*
 * FIDX (R/W)
 *
 * Recovery function selection for host access at offset 0x140+
 */
#define TSW_CPU_PORT_EGRESS_FRER_FSELECT_FIDX_MASK (0xFFU)
#define TSW_CPU_PORT_EGRESS_FRER_FSELECT_FIDX_SHIFT (0U)
#define TSW_CPU_PORT_EGRESS_FRER_FSELECT_FIDX_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_EGRESS_FRER_FSELECT_FIDX_SHIFT) & TSW_CPU_PORT_EGRESS_FRER_FSELECT_FIDX_MASK)
#define TSW_CPU_PORT_EGRESS_FRER_FSELECT_FIDX_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_EGRESS_FRER_FSELECT_FIDX_MASK) >> TSW_CPU_PORT_EGRESS_FRER_FSELECT_FIDX_SHIFT)

/* Bitfield definition for register: CPU_PORT_EGRESS_FRER_FCTRL */
/*
 * FRSET (WO)
 *
 * Reset recovery function – self-resetting to 0
 */
#define TSW_CPU_PORT_EGRESS_FRER_FCTRL_FRSET_MASK (0x80000000UL)
#define TSW_CPU_PORT_EGRESS_FRER_FCTRL_FRSET_SHIFT (31U)
#define TSW_CPU_PORT_EGRESS_FRER_FCTRL_FRSET_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_EGRESS_FRER_FCTRL_FRSET_SHIFT) & TSW_CPU_PORT_EGRESS_FRER_FCTRL_FRSET_MASK)
#define TSW_CPU_PORT_EGRESS_FRER_FCTRL_FRSET_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_EGRESS_FRER_FCTRL_FRSET_MASK) >> TSW_CPU_PORT_EGRESS_FRER_FCTRL_FRSET_SHIFT)

/*
 * PATHS (R/W)
 *
 * Number of paths (used by latent error detection)
 */
#define TSW_CPU_PORT_EGRESS_FRER_FCTRL_PATHS_MASK (0xFF0000UL)
#define TSW_CPU_PORT_EGRESS_FRER_FCTRL_PATHS_SHIFT (16U)
#define TSW_CPU_PORT_EGRESS_FRER_FCTRL_PATHS_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_EGRESS_FRER_FCTRL_PATHS_SHIFT) & TSW_CPU_PORT_EGRESS_FRER_FCTRL_PATHS_MASK)
#define TSW_CPU_PORT_EGRESS_FRER_FCTRL_PATHS_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_EGRESS_FRER_FCTRL_PATHS_MASK) >> TSW_CPU_PORT_EGRESS_FRER_FCTRL_PATHS_SHIFT)

/*
 * HLEN (R/W)
 *
 * History length (used by Vector recovery algorithm)
 */
#define TSW_CPU_PORT_EGRESS_FRER_FCTRL_HLEN_MASK (0x1F00U)
#define TSW_CPU_PORT_EGRESS_FRER_FCTRL_HLEN_SHIFT (8U)
#define TSW_CPU_PORT_EGRESS_FRER_FCTRL_HLEN_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_EGRESS_FRER_FCTRL_HLEN_SHIFT) & TSW_CPU_PORT_EGRESS_FRER_FCTRL_HLEN_MASK)
#define TSW_CPU_PORT_EGRESS_FRER_FCTRL_HLEN_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_EGRESS_FRER_FCTRL_HLEN_MASK) >> TSW_CPU_PORT_EGRESS_FRER_FCTRL_HLEN_SHIFT)

/*
 * ALGO (R/W)
 *
 * Recovery function algorithm: 0 – Vector recovery algorithm 1 – Match recovery algorithm
 */
#define TSW_CPU_PORT_EGRESS_FRER_FCTRL_ALGO_MASK (0x10U)
#define TSW_CPU_PORT_EGRESS_FRER_FCTRL_ALGO_SHIFT (4U)
#define TSW_CPU_PORT_EGRESS_FRER_FCTRL_ALGO_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_EGRESS_FRER_FCTRL_ALGO_SHIFT) & TSW_CPU_PORT_EGRESS_FRER_FCTRL_ALGO_MASK)
#define TSW_CPU_PORT_EGRESS_FRER_FCTRL_ALGO_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_EGRESS_FRER_FCTRL_ALGO_MASK) >> TSW_CPU_PORT_EGRESS_FRER_FCTRL_ALGO_SHIFT)

/*
 * LATEN (R/W)
 *
 * Latent error detection enable
 */
#define TSW_CPU_PORT_EGRESS_FRER_FCTRL_LATEN_MASK (0x8U)
#define TSW_CPU_PORT_EGRESS_FRER_FCTRL_LATEN_SHIFT (3U)
#define TSW_CPU_PORT_EGRESS_FRER_FCTRL_LATEN_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_EGRESS_FRER_FCTRL_LATEN_SHIFT) & TSW_CPU_PORT_EGRESS_FRER_FCTRL_LATEN_MASK)
#define TSW_CPU_PORT_EGRESS_FRER_FCTRL_LATEN_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_EGRESS_FRER_FCTRL_LATEN_MASK) >> TSW_CPU_PORT_EGRESS_FRER_FCTRL_LATEN_SHIFT)

/*
 * IND (R/W)
 *
 * Individual function (802.1CB 10.4.1.10)
 */
#define TSW_CPU_PORT_EGRESS_FRER_FCTRL_IND_MASK (0x4U)
#define TSW_CPU_PORT_EGRESS_FRER_FCTRL_IND_SHIFT (2U)
#define TSW_CPU_PORT_EGRESS_FRER_FCTRL_IND_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_EGRESS_FRER_FCTRL_IND_SHIFT) & TSW_CPU_PORT_EGRESS_FRER_FCTRL_IND_MASK)
#define TSW_CPU_PORT_EGRESS_FRER_FCTRL_IND_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_EGRESS_FRER_FCTRL_IND_MASK) >> TSW_CPU_PORT_EGRESS_FRER_FCTRL_IND_SHIFT)

/*
 * TNS (R/W)
 *
 * TakeNoSequence (802.1CB 10.4.1.9)
 */
#define TSW_CPU_PORT_EGRESS_FRER_FCTRL_TNS_MASK (0x2U)
#define TSW_CPU_PORT_EGRESS_FRER_FCTRL_TNS_SHIFT (1U)
#define TSW_CPU_PORT_EGRESS_FRER_FCTRL_TNS_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_EGRESS_FRER_FCTRL_TNS_SHIFT) & TSW_CPU_PORT_EGRESS_FRER_FCTRL_TNS_MASK)
#define TSW_CPU_PORT_EGRESS_FRER_FCTRL_TNS_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_EGRESS_FRER_FCTRL_TNS_MASK) >> TSW_CPU_PORT_EGRESS_FRER_FCTRL_TNS_SHIFT)

/* Bitfield definition for register: CPU_PORT_EGRESS_FRER_RESETMSEC */
/*
 * FSRMS (R/W)
 *
 * frerSeqRcvyResetMSec (802.1CB 10.4.1.7)
 */
#define TSW_CPU_PORT_EGRESS_FRER_RESETMSEC_FSRMS_MASK (0xFFFFFFUL)
#define TSW_CPU_PORT_EGRESS_FRER_RESETMSEC_FSRMS_SHIFT (0U)
#define TSW_CPU_PORT_EGRESS_FRER_RESETMSEC_FSRMS_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_EGRESS_FRER_RESETMSEC_FSRMS_SHIFT) & TSW_CPU_PORT_EGRESS_FRER_RESETMSEC_FSRMS_MASK)
#define TSW_CPU_PORT_EGRESS_FRER_RESETMSEC_FSRMS_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_EGRESS_FRER_RESETMSEC_FSRMS_MASK) >> TSW_CPU_PORT_EGRESS_FRER_RESETMSEC_FSRMS_SHIFT)

/* Bitfield definition for register: CPU_PORT_EGRESS_FRER_LATRSPERIOD */
/*
 * FLATR (R/W)
 *
 * frerSeqRcvyLatentResetPeriod (802.1CB 10.4.1.12.4)
 */
#define TSW_CPU_PORT_EGRESS_FRER_LATRSPERIOD_FLATR_MASK (0xFFFFFFUL)
#define TSW_CPU_PORT_EGRESS_FRER_LATRSPERIOD_FLATR_SHIFT (0U)
#define TSW_CPU_PORT_EGRESS_FRER_LATRSPERIOD_FLATR_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_EGRESS_FRER_LATRSPERIOD_FLATR_SHIFT) & TSW_CPU_PORT_EGRESS_FRER_LATRSPERIOD_FLATR_MASK)
#define TSW_CPU_PORT_EGRESS_FRER_LATRSPERIOD_FLATR_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_EGRESS_FRER_LATRSPERIOD_FLATR_MASK) >> TSW_CPU_PORT_EGRESS_FRER_LATRSPERIOD_FLATR_SHIFT)

/* Bitfield definition for register: CPU_PORT_EGRESS_FRER_LATTESTPERIOD */
/*
 * FLATT (R/W)
 *
 * frerSeqRcvyLatentErrorPeriod (802.1CB 10.4.1.12.2)
 */
#define TSW_CPU_PORT_EGRESS_FRER_LATTESTPERIOD_FLATT_MASK (0xFFFFFFUL)
#define TSW_CPU_PORT_EGRESS_FRER_LATTESTPERIOD_FLATT_SHIFT (0U)
#define TSW_CPU_PORT_EGRESS_FRER_LATTESTPERIOD_FLATT_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_EGRESS_FRER_LATTESTPERIOD_FLATT_SHIFT) & TSW_CPU_PORT_EGRESS_FRER_LATTESTPERIOD_FLATT_MASK)
#define TSW_CPU_PORT_EGRESS_FRER_LATTESTPERIOD_FLATT_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_EGRESS_FRER_LATTESTPERIOD_FLATT_MASK) >> TSW_CPU_PORT_EGRESS_FRER_LATTESTPERIOD_FLATT_SHIFT)

/* Bitfield definition for register: CPU_PORT_EGRESS_FRER_LATERRDIFFALW */
/*
 * FDIFF (R/W)
 *
 * frerSeqRcvyLatentErrorDifference (802.1CB 10.4.1.12.1)
 */
#define TSW_CPU_PORT_EGRESS_FRER_LATERRDIFFALW_FDIFF_MASK (0xFFFFFFFFUL)
#define TSW_CPU_PORT_EGRESS_FRER_LATERRDIFFALW_FDIFF_SHIFT (0U)
#define TSW_CPU_PORT_EGRESS_FRER_LATERRDIFFALW_FDIFF_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_EGRESS_FRER_LATERRDIFFALW_FDIFF_SHIFT) & TSW_CPU_PORT_EGRESS_FRER_LATERRDIFFALW_FDIFF_MASK)
#define TSW_CPU_PORT_EGRESS_FRER_LATERRDIFFALW_FDIFF_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_EGRESS_FRER_LATERRDIFFALW_FDIFF_MASK) >> TSW_CPU_PORT_EGRESS_FRER_LATERRDIFFALW_FDIFF_SHIFT)

/* Bitfield definition for register: CPU_PORT_EGRESS_FRER_LATERRCNT */
/*
 * LATERR (R/WC)
 *
 * Counter – latent error detect. Write any value to clear
 */
#define TSW_CPU_PORT_EGRESS_FRER_LATERRCNT_LATERR_MASK (0xFFFFFFFFUL)
#define TSW_CPU_PORT_EGRESS_FRER_LATERRCNT_LATERR_SHIFT (0U)
#define TSW_CPU_PORT_EGRESS_FRER_LATERRCNT_LATERR_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_EGRESS_FRER_LATERRCNT_LATERR_SHIFT) & TSW_CPU_PORT_EGRESS_FRER_LATERRCNT_LATERR_MASK)
#define TSW_CPU_PORT_EGRESS_FRER_LATERRCNT_LATERR_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_EGRESS_FRER_LATERRCNT_LATERR_MASK) >> TSW_CPU_PORT_EGRESS_FRER_LATERRCNT_LATERR_SHIFT)

/* Bitfield definition for register array: EGFRCNT */
/*
 * VALUE (RO)
 *
 * Frame counters
 */
#define TSW_EGFRCNT_VALUE_MASK (0xFFFFFFFFUL)
#define TSW_EGFRCNT_VALUE_SHIFT (0U)
#define TSW_EGFRCNT_VALUE_GET(x) (((uint32_t)(x) & TSW_EGFRCNT_VALUE_MASK) >> TSW_EGFRCNT_VALUE_SHIFT)

/* Bitfield definition for register: CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_CNT_BYTE */
/*
 * FDMEM_CNT_BYTE (RO)
 *
 * Number of bytes stored in frame drop FIFO
 */
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_CNT_BYTE_FDMEM_CNT_BYTE_MASK (0xFFFFFFFFUL)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_CNT_BYTE_FDMEM_CNT_BYTE_SHIFT (0U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_CNT_BYTE_FDMEM_CNT_BYTE_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_CNT_BYTE_FDMEM_CNT_BYTE_MASK) >> TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_CNT_BYTE_FDMEM_CNT_BYTE_SHIFT)

/* Bitfield definition for register: CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS */
/*
 * WAIT_FOR_LU (RO)
 *
 * FD FIFO waits for LookUp information.
 */
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_WAIT_FOR_LU_MASK (0x800U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_WAIT_FOR_LU_SHIFT (11U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_WAIT_FOR_LU_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_WAIT_FOR_LU_MASK) >> TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_WAIT_FOR_LU_SHIFT)

/*
 * WAIT_FOR_FRAME (RO)
 *
 * FD FIFO waits for more frame data.
 */
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_WAIT_FOR_FRAME_MASK (0x400U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_WAIT_FOR_FRAME_SHIFT (10U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_WAIT_FOR_FRAME_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_WAIT_FOR_FRAME_MASK) >> TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_WAIT_FOR_FRAME_SHIFT)

/*
 * BUSY (RO)
 *
 * FD FIFO processes data.
 */
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_BUSY_MASK (0x200U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_BUSY_SHIFT (9U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_BUSY_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_BUSY_MASK) >> TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_BUSY_SHIFT)

/*
 * READY (RO)
 *
 * FD FIFO ready to work or working.
 */
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_READY_MASK (0x100U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_READY_SHIFT (8U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_READY_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_READY_MASK) >> TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_READY_SHIFT)

/*
 * FULL (RO)
 *
 * FD FIFO full
 */
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_FULL_MASK (0x8U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_FULL_SHIFT (3U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_FULL_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_FULL_MASK) >> TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_FULL_SHIFT)

/*
 * AMST_FULL (RO)
 *
 * FD FIFO almost full. Less than 1600 Byte left.
 */
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_AMST_FULL_MASK (0x4U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_AMST_FULL_SHIFT (2U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_AMST_FULL_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_AMST_FULL_MASK) >> TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_AMST_FULL_SHIFT)

/*
 * AMST_EMPTY (RO)
 *
 * FD FIFO almost empty. Few bytes in FIFO.
 */
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_AMST_EMPTY_MASK (0x2U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_AMST_EMPTY_SHIFT (1U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_AMST_EMPTY_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_AMST_EMPTY_MASK) >> TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_AMST_EMPTY_SHIFT)

/*
 * EMPTY (RO)
 *
 * FD FIFO empty
 */
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_EMPTY_MASK (0x1U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_EMPTY_SHIFT (0U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_EMPTY_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_EMPTY_MASK) >> TSW_CPU_PORT_IGRESS_RX_FDFIFO_FDMEM_STS_EMPTY_SHIFT)

/* Bitfield definition for register: CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG */
/*
 * LU_DESC_ERR (R/W1C)
 *
 * LookUp Descriptor lost, because of unknown frame burst by MAC. If there is no  MAC mailfunction then this flag will never be raised. FDFIFO requires reset.
 */
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_LU_DESC_ERR_MASK (0x40U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_LU_DESC_ERR_SHIFT (6U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_LU_DESC_ERR_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_LU_DESC_ERR_SHIFT) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_LU_DESC_ERR_MASK)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_LU_DESC_ERR_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_LU_DESC_ERR_MASK) >> TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_LU_DESC_ERR_SHIFT)

/*
 * WRFAIL_FULL (R/W1C)
 *
 * Set if a frame is partially written into FIFO which had insufficient space. The frame is cut and frame error is set.
 */
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_WRFAIL_FULL_MASK (0x20U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_WRFAIL_FULL_SHIFT (5U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_WRFAIL_FULL_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_WRFAIL_FULL_SHIFT) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_WRFAIL_FULL_MASK)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_WRFAIL_FULL_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_WRFAIL_FULL_MASK) >> TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_WRFAIL_FULL_SHIFT)

/*
 * DROP_NRDY (R/W1C)
 *
 * Frame was dropped because the FIFO was not ready. That can typically happen after a reset of the FIFO
 */
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DROP_NRDY_MASK (0x10U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DROP_NRDY_SHIFT (4U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DROP_NRDY_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DROP_NRDY_SHIFT) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DROP_NRDY_MASK)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DROP_NRDY_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DROP_NRDY_MASK) >> TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DROP_NRDY_SHIFT)

/*
 * DROP_FULL_DESC (R/W1C)
 *
 * Frame was dropped because the internal descriptor FIFO is full. Full by too many frames.
 */
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DROP_FULL_DESC_MASK (0x8U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DROP_FULL_DESC_SHIFT (3U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DROP_FULL_DESC_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DROP_FULL_DESC_SHIFT) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DROP_FULL_DESC_MASK)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DROP_FULL_DESC_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DROP_FULL_DESC_MASK) >> TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DROP_FULL_DESC_SHIFT)

/*
 * DROP_FULL_MEM (R/W1C)
 *
 * Frame was dropped because the FIFO is full. Full by too much data.
 */
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DROP_FULL_MEM_MASK (0x4U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DROP_FULL_MEM_SHIFT (2U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DROP_FULL_MEM_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DROP_FULL_MEM_SHIFT) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DROP_FULL_MEM_MASK)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DROP_FULL_MEM_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DROP_FULL_MEM_MASK) >> TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DROP_FULL_MEM_SHIFT)

/*
 * DESC_NRDY_ERR (R/W1C)
 *
 * FD FIFO failure. Descriptor not received correctly.
 */
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DESC_NRDY_ERR_MASK (0x2U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DESC_NRDY_ERR_SHIFT (1U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DESC_NRDY_ERR_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DESC_NRDY_ERR_SHIFT) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DESC_NRDY_ERR_MASK)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DESC_NRDY_ERR_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DESC_NRDY_ERR_MASK) >> TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DESC_NRDY_ERR_SHIFT)

/*
 * DESC_SEQ_ERR (R/W1C)
 *
 * FD FIFO failure. Internal controller lost synchronization.
 */
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DESC_SEQ_ERR_MASK (0x1U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DESC_SEQ_ERR_SHIFT (0U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DESC_SEQ_ERR_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DESC_SEQ_ERR_SHIFT) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DESC_SEQ_ERR_MASK)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DESC_SEQ_ERR_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DESC_SEQ_ERR_MASK) >> TSW_CPU_PORT_IGRESS_RX_FDFIFO_ERROR_FLAG_DESC_SEQ_ERR_SHIFT)

/* Bitfield definition for register: CPU_PORT_IGRESS_RX_FDFIFO_IE_ERROR_FLAG */
/*
 * IE (R/W)
 *
 * Interrupt enable of ERROR_FLAG.
 */
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_IE_ERROR_FLAG_IE_MASK (0x7FU)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_IE_ERROR_FLAG_IE_SHIFT (0U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_IE_ERROR_FLAG_IE_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_RX_FDFIFO_IE_ERROR_FLAG_IE_SHIFT) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_IE_ERROR_FLAG_IE_MASK)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_IE_ERROR_FLAG_IE_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_IE_ERROR_FLAG_IE_MASK) >> TSW_CPU_PORT_IGRESS_RX_FDFIFO_IE_ERROR_FLAG_IE_SHIFT)

/* Bitfield definition for register: CPU_PORT_IGRESS_RX_FDFIFO_IN_CONFIG */
/*
 * NOCUT_ERROR (R/W)
 *
 * FD_FIFO does not shorten frames which contain an error.
 */
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_IN_CONFIG_NOCUT_ERROR_MASK (0x1U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_IN_CONFIG_NOCUT_ERROR_SHIFT (0U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_IN_CONFIG_NOCUT_ERROR_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_RX_FDFIFO_IN_CONFIG_NOCUT_ERROR_SHIFT) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_IN_CONFIG_NOCUT_ERROR_MASK)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_IN_CONFIG_NOCUT_ERROR_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_IN_CONFIG_NOCUT_ERROR_MASK) >> TSW_CPU_PORT_IGRESS_RX_FDFIFO_IN_CONFIG_NOCUT_ERROR_SHIFT)

/* Bitfield definition for register: CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG */
/*
 * DROP_DEST (R/W)
 *
 * Bit mapped Destination for dropped frames. Typically, frames are cleared at destination 0. Use another value to stream frames for analysis. Supports only max range of port[15:0].
 */
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_DROP_DEST_MASK (0xFFFF0000UL)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_DROP_DEST_SHIFT (16U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_DROP_DEST_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_DROP_DEST_SHIFT) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_DROP_DEST_MASK)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_DROP_DEST_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_DROP_DEST_MASK) >> TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_DROP_DEST_SHIFT)

/*
 * MIRROR_TX_EN (R/W)
 *
 * Incoming frames of this port will be mirrored to the given destination in MIRROR if their destination match with MIRROR_TX.
 */
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_MIRROR_TX_EN_MASK (0x200U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_MIRROR_TX_EN_SHIFT (9U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_MIRROR_TX_EN_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_MIRROR_TX_EN_SHIFT) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_MIRROR_TX_EN_MASK)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_MIRROR_TX_EN_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_MIRROR_TX_EN_MASK) >> TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_MIRROR_TX_EN_SHIFT)

/*
 * MIRROR_RX_EN (R/W)
 *
 * Incoming frames of this port will be mirrored to the given destination in MIRROR_RX.
 */
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_MIRROR_RX_EN_MASK (0x100U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_MIRROR_RX_EN_SHIFT (8U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_MIRROR_RX_EN_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_MIRROR_RX_EN_SHIFT) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_MIRROR_RX_EN_MASK)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_MIRROR_RX_EN_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_MIRROR_RX_EN_MASK) >> TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_MIRROR_RX_EN_SHIFT)

/*
 * CT_FPE_OVRD (R/W)
 *
 * If any Store&Forward option in RX_FDFIFO is set then this flag will still force preemptable traffic to be forwarded in Cut-Through mode. This is a useful option to save latency by double buffering if the used MAC/TSN-EP already does S&F.
 */
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_CT_FPE_OVRD_MASK (0x40U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_CT_FPE_OVRD_SHIFT (6U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_CT_FPE_OVRD_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_CT_FPE_OVRD_SHIFT) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_CT_FPE_OVRD_MASK)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_CT_FPE_OVRD_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_CT_FPE_OVRD_MASK) >> TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_CT_FPE_OVRD_SHIFT)

/*
 * DISABLE (R/W)
 *
 * Disable input of FD FIFO. Take care that also descriptor generation of LookUp is disabled. Remaining frames should be cleared with DROP_ALL.
 */
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_DISABLE_MASK (0x20U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_DISABLE_SHIFT (5U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_DISABLE_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_DISABLE_SHIFT) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_DISABLE_MASK)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_DISABLE_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_DISABLE_MASK) >> TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_DISABLE_SHIFT)

/*
 * DROP_ALL (R/W)
 *
 * Route all frames to DROP_DEST.
 */
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_DROP_ALL_MASK (0x10U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_DROP_ALL_SHIFT (4U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_DROP_ALL_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_DROP_ALL_SHIFT) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_DROP_ALL_MASK)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_DROP_ALL_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_DROP_ALL_MASK) >> TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_DROP_ALL_SHIFT)

/*
 * ERROR_TO_CPU (R/W)
 *
 * Send error frames to CPU.
 */
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_ERROR_TO_CPU_MASK (0x8U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_ERROR_TO_CPU_SHIFT (3U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_ERROR_TO_CPU_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_ERROR_TO_CPU_SHIFT) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_ERROR_TO_CPU_MASK)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_ERROR_TO_CPU_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_ERROR_TO_CPU_MASK) >> TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_ERROR_TO_CPU_SHIFT)

/*
 * MIRROR_TO_CPU (R/W)
 *
 * Duplicate frames to CPU.
 */
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_MIRROR_TO_CPU_MASK (0x4U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_MIRROR_TO_CPU_SHIFT (2U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_MIRROR_TO_CPU_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_MIRROR_TO_CPU_SHIFT) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_MIRROR_TO_CPU_MASK)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_MIRROR_TO_CPU_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_MIRROR_TO_CPU_MASK) >> TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_MIRROR_TO_CPU_SHIFT)

/*
 * NODROP_ERROR (R/W)
 *
 * Do not drop frame errors.
 */
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_NODROP_ERROR_MASK (0x2U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_NODROP_ERROR_SHIFT (1U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_NODROP_ERROR_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_NODROP_ERROR_SHIFT) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_NODROP_ERROR_MASK)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_NODROP_ERROR_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_NODROP_ERROR_MASK) >> TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_NODROP_ERROR_SHIFT)

/*
 * MODE_STORE_FW (R/W)
 *
 * Switch between Cut-Through and Store&Forward mode. 0 - Cut-Through 1 - Store&Forward
 */
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_MODE_STORE_FW_MASK (0x1U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_MODE_STORE_FW_SHIFT (0U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_MODE_STORE_FW_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_MODE_STORE_FW_SHIFT) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_MODE_STORE_FW_MASK)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_MODE_STORE_FW_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_MODE_STORE_FW_MASK) >> TSW_CPU_PORT_IGRESS_RX_FDFIFO_OUT_CONFIG_MODE_STORE_FW_SHIFT)

/* Bitfield definition for register: CPU_PORT_IGRESS_RX_FDFIFO_RESET */
/*
 * SOFTRS (W)
 *
 * Write 1 to reset FD controller and memory pointers. Register Map content remains untouched
 */
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_RESET_SOFTRS_MASK (0x1U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_RESET_SOFTRS_SHIFT (0U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_RESET_SOFTRS_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_RX_FDFIFO_RESET_SOFTRS_SHIFT) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_RESET_SOFTRS_MASK)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_RESET_SOFTRS_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_RESET_SOFTRS_MASK) >> TSW_CPU_PORT_IGRESS_RX_FDFIFO_RESET_SOFTRS_SHIFT)

/* Bitfield definition for register: CPU_PORT_IGRESS_RX_FDFIFO_PARAM */
/*
 * LU_FIFO_DEPTH (RO)
 *
 * Number of MAC lookup descriptors the FIFO can store.
 */
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_PARAM_LU_FIFO_DEPTH_MASK (0xFF000000UL)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_PARAM_LU_FIFO_DEPTH_SHIFT (24U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_PARAM_LU_FIFO_DEPTH_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_PARAM_LU_FIFO_DEPTH_MASK) >> TSW_CPU_PORT_IGRESS_RX_FDFIFO_PARAM_LU_FIFO_DEPTH_SHIFT)

/*
 * FD_DESC_FIFO_DESC (RO)
 *
 * Number of FD descriptors the FIFO can store. Two descriptors need to be stored per frame.
 */
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_PARAM_FD_DESC_FIFO_DESC_MASK (0xFF0000UL)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_PARAM_FD_DESC_FIFO_DESC_SHIFT (16U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_PARAM_FD_DESC_FIFO_DESC_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_PARAM_FD_DESC_FIFO_DESC_MASK) >> TSW_CPU_PORT_IGRESS_RX_FDFIFO_PARAM_FD_DESC_FIFO_DESC_SHIFT)

/*
 * FD_FIFO_DESC (RO)
 *
 * Number of words (4byte) the Frame Drop FIFO can store.
 */
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_PARAM_FD_FIFO_DESC_MASK (0xFFFFU)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_PARAM_FD_FIFO_DESC_SHIFT (0U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_PARAM_FD_FIFO_DESC_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_PARAM_FD_FIFO_DESC_MASK) >> TSW_CPU_PORT_IGRESS_RX_FDFIFO_PARAM_FD_FIFO_DESC_SHIFT)

/* Bitfield definition for register: CPU_PORT_IGRESS_RX_FDFIFO_STRFWD */
/*
 * PORT (R/W)
 *
 * If selected port is set then the frame is transmitted in Store & Forward mode. This is necessary when the ingress rate of this port is slower than the egress rate of the transmitting port. In S&F, the ingress module is able to drop frames with bad CRC.bit 0 - CPU-Port,
 * bit 1 - Port 1, …
 */
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_STRFWD_PORT_MASK (0x1FFFFFFUL)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_STRFWD_PORT_SHIFT (0U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_STRFWD_PORT_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_RX_FDFIFO_STRFWD_PORT_SHIFT) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_STRFWD_PORT_MASK)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_STRFWD_PORT_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_STRFWD_PORT_MASK) >> TSW_CPU_PORT_IGRESS_RX_FDFIFO_STRFWD_PORT_SHIFT)

/* Bitfield definition for register: CPU_PORT_IGRESS_RX_FDFIFO_PORTMASK */
/*
 * PORT (R/W)
 *
 * Port grouping via port mask. If the selected port is not set then the destination will be filtered out. This register allows the realization of port-based-VLAN (no VLAN tags required, only set it by ports).
 * bit 0 - CPU-Port,
 * bit 1 - Port 1, …
 */
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_PORTMASK_PORT_MASK (0x1FFFFFFUL)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_PORTMASK_PORT_SHIFT (0U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_PORTMASK_PORT_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_RX_FDFIFO_PORTMASK_PORT_SHIFT) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_PORTMASK_PORT_MASK)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_PORTMASK_PORT_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_PORTMASK_PORT_MASK) >> TSW_CPU_PORT_IGRESS_RX_FDFIFO_PORTMASK_PORT_SHIFT)

/* Bitfield definition for register: CPU_PORT_IGRESS_RX_FDFIFO_MIRROR */
/*
 * PORT (R/W)
 *
 * Mirror Port. If port mirroring is enabled TX/RX traffic will also be forwarded to this port.
 * bit 0 - CPU-Port,
 * bit 1 - Port 1, …
 */
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_MIRROR_PORT_MASK (0x1FFFFFFUL)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_MIRROR_PORT_SHIFT (0U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_MIRROR_PORT_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_RX_FDFIFO_MIRROR_PORT_SHIFT) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_MIRROR_PORT_MASK)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_MIRROR_PORT_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_MIRROR_PORT_MASK) >> TSW_CPU_PORT_IGRESS_RX_FDFIFO_MIRROR_PORT_SHIFT)

/* Bitfield definition for register: CPU_PORT_IGRESS_RX_FDFIFO_MIRROR_TX */
/*
 * PORT (R/W)
 *
 * Mirror Selection TX. The destination of the frame is compared with this vector. All matching TX probe ports will be mirrored to MIRROR. It is necessary to configure all ingress ports to mirror the complete TX traffic.
 * bit 0 - CPU-Port,
 * bit 1 - Port 1, …
 */
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_MIRROR_TX_PORT_MASK (0x1FFFFFFUL)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_MIRROR_TX_PORT_SHIFT (0U)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_MIRROR_TX_PORT_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_RX_FDFIFO_MIRROR_TX_PORT_SHIFT) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_MIRROR_TX_PORT_MASK)
#define TSW_CPU_PORT_IGRESS_RX_FDFIFO_MIRROR_TX_PORT_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_RX_FDFIFO_MIRROR_TX_PORT_MASK) >> TSW_CPU_PORT_IGRESS_RX_FDFIFO_MIRROR_TX_PORT_SHIFT)

/* Bitfield definition for register: CPU_PORT_IGRESS_STMID_ESELECT */
/*
 * ESEL (RO)
 *
 * Select entry. Selected entry mapped to 0x40 – 0x5C.
 */
#define TSW_CPU_PORT_IGRESS_STMID_ESELECT_ESEL_MASK (0xFFU)
#define TSW_CPU_PORT_IGRESS_STMID_ESELECT_ESEL_SHIFT (0U)
#define TSW_CPU_PORT_IGRESS_STMID_ESELECT_ESEL_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_STMID_ESELECT_ESEL_MASK) >> TSW_CPU_PORT_IGRESS_STMID_ESELECT_ESEL_SHIFT)

/* Bitfield definition for register: CPU_PORT_IGRESS_STMID_CONTROL */
/*
 * SID (RW)
 *
 * Stream ID – inserted to header on match
 */
#define TSW_CPU_PORT_IGRESS_STMID_CONTROL_SID_MASK (0xFF00U)
#define TSW_CPU_PORT_IGRESS_STMID_CONTROL_SID_SHIFT (8U)
#define TSW_CPU_PORT_IGRESS_STMID_CONTROL_SID_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_STMID_CONTROL_SID_SHIFT) & TSW_CPU_PORT_IGRESS_STMID_CONTROL_SID_MASK)
#define TSW_CPU_PORT_IGRESS_STMID_CONTROL_SID_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_STMID_CONTROL_SID_MASK) >> TSW_CPU_PORT_IGRESS_STMID_CONTROL_SID_SHIFT)

/*
 * SEQGEN (RW)
 *
 * Sequence number generation enable
 */
#define TSW_CPU_PORT_IGRESS_STMID_CONTROL_SEQGEN_MASK (0x80U)
#define TSW_CPU_PORT_IGRESS_STMID_CONTROL_SEQGEN_SHIFT (7U)
#define TSW_CPU_PORT_IGRESS_STMID_CONTROL_SEQGEN_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_STMID_CONTROL_SEQGEN_SHIFT) & TSW_CPU_PORT_IGRESS_STMID_CONTROL_SEQGEN_MASK)
#define TSW_CPU_PORT_IGRESS_STMID_CONTROL_SEQGEN_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_STMID_CONTROL_SEQGEN_MASK) >> TSW_CPU_PORT_IGRESS_STMID_CONTROL_SEQGEN_SHIFT)

/*
 * ACTCTL (RW)
 *
 * Active Destination MAC – control. See Table 6-6.
 */
#define TSW_CPU_PORT_IGRESS_STMID_CONTROL_ACTCTL_MASK (0x30U)
#define TSW_CPU_PORT_IGRESS_STMID_CONTROL_ACTCTL_SHIFT (4U)
#define TSW_CPU_PORT_IGRESS_STMID_CONTROL_ACTCTL_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_STMID_CONTROL_ACTCTL_SHIFT) & TSW_CPU_PORT_IGRESS_STMID_CONTROL_ACTCTL_MASK)
#define TSW_CPU_PORT_IGRESS_STMID_CONTROL_ACTCTL_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_STMID_CONTROL_ACTCTL_MASK) >> TSW_CPU_PORT_IGRESS_STMID_CONTROL_ACTCTL_SHIFT)

/*
 * SMAC (RW)
 *
 * 0: Lookup by Destination MAC 1: Lookup by Source MAC
 */
#define TSW_CPU_PORT_IGRESS_STMID_CONTROL_SMAC_MASK (0x8U)
#define TSW_CPU_PORT_IGRESS_STMID_CONTROL_SMAC_SHIFT (3U)
#define TSW_CPU_PORT_IGRESS_STMID_CONTROL_SMAC_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_STMID_CONTROL_SMAC_SHIFT) & TSW_CPU_PORT_IGRESS_STMID_CONTROL_SMAC_MASK)
#define TSW_CPU_PORT_IGRESS_STMID_CONTROL_SMAC_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_STMID_CONTROL_SMAC_MASK) >> TSW_CPU_PORT_IGRESS_STMID_CONTROL_SMAC_SHIFT)

/*
 * MODE (RW)
 *
 * Lookup mode. 1:Priority – a frame must be untagged or priority tagged ; 2:Tagged – a frame must have a VLAN tag ; 3:All – a frame can be tagged or untagged
 */
#define TSW_CPU_PORT_IGRESS_STMID_CONTROL_MODE_MASK (0x6U)
#define TSW_CPU_PORT_IGRESS_STMID_CONTROL_MODE_SHIFT (1U)
#define TSW_CPU_PORT_IGRESS_STMID_CONTROL_MODE_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_STMID_CONTROL_MODE_SHIFT) & TSW_CPU_PORT_IGRESS_STMID_CONTROL_MODE_MASK)
#define TSW_CPU_PORT_IGRESS_STMID_CONTROL_MODE_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_STMID_CONTROL_MODE_MASK) >> TSW_CPU_PORT_IGRESS_STMID_CONTROL_MODE_SHIFT)

/*
 * EN (RW)
 *
 * Enable entry
 */
#define TSW_CPU_PORT_IGRESS_STMID_CONTROL_EN_MASK (0x1U)
#define TSW_CPU_PORT_IGRESS_STMID_CONTROL_EN_SHIFT (0U)
#define TSW_CPU_PORT_IGRESS_STMID_CONTROL_EN_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_STMID_CONTROL_EN_SHIFT) & TSW_CPU_PORT_IGRESS_STMID_CONTROL_EN_MASK)
#define TSW_CPU_PORT_IGRESS_STMID_CONTROL_EN_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_STMID_CONTROL_EN_MASK) >> TSW_CPU_PORT_IGRESS_STMID_CONTROL_EN_SHIFT)

/* Bitfield definition for register: CPU_PORT_IGRESS_STMID_SEQNO */
/*
 * SEQNO (RWC)
 *
 * Sequence number – next number when generating,any write access to clear.
 */
#define TSW_CPU_PORT_IGRESS_STMID_SEQNO_SEQNO_MASK (0xFFFFU)
#define TSW_CPU_PORT_IGRESS_STMID_SEQNO_SEQNO_SHIFT (0U)
#define TSW_CPU_PORT_IGRESS_STMID_SEQNO_SEQNO_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_STMID_SEQNO_SEQNO_SHIFT) & TSW_CPU_PORT_IGRESS_STMID_SEQNO_SEQNO_MASK)
#define TSW_CPU_PORT_IGRESS_STMID_SEQNO_SEQNO_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_STMID_SEQNO_SEQNO_MASK) >> TSW_CPU_PORT_IGRESS_STMID_SEQNO_SEQNO_SHIFT)

/* Bitfield definition for register: CPU_PORT_IGRESS_STMID_MATCHCNT */
/*
 * MATCH (RWC)
 *
 * Entry match counter – any write access to clear.
 */
#define TSW_CPU_PORT_IGRESS_STMID_MATCHCNT_MATCH_MASK (0xFFFFFFFFUL)
#define TSW_CPU_PORT_IGRESS_STMID_MATCHCNT_MATCH_SHIFT (0U)
#define TSW_CPU_PORT_IGRESS_STMID_MATCHCNT_MATCH_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_STMID_MATCHCNT_MATCH_SHIFT) & TSW_CPU_PORT_IGRESS_STMID_MATCHCNT_MATCH_MASK)
#define TSW_CPU_PORT_IGRESS_STMID_MATCHCNT_MATCH_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_STMID_MATCHCNT_MATCH_MASK) >> TSW_CPU_PORT_IGRESS_STMID_MATCHCNT_MATCH_SHIFT)

/* Bitfield definition for register: CPU_PORT_IGRESS_STMID_MACLO */
/*
 * MACL (RWC)
 *
 * MAC-Address [31:0] used by lookup.
 */
#define TSW_CPU_PORT_IGRESS_STMID_MACLO_MACL_MASK (0xFFFFFFFFUL)
#define TSW_CPU_PORT_IGRESS_STMID_MACLO_MACL_SHIFT (0U)
#define TSW_CPU_PORT_IGRESS_STMID_MACLO_MACL_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_STMID_MACLO_MACL_SHIFT) & TSW_CPU_PORT_IGRESS_STMID_MACLO_MACL_MASK)
#define TSW_CPU_PORT_IGRESS_STMID_MACLO_MACL_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_STMID_MACLO_MACL_MASK) >> TSW_CPU_PORT_IGRESS_STMID_MACLO_MACL_SHIFT)

/* Bitfield definition for register: CPU_PORT_IGRESS_STMID_MACHI */
/*
 * VID (RW)
 *
 * VLAN ID used by lookup.
 */
#define TSW_CPU_PORT_IGRESS_STMID_MACHI_VID_MASK (0xFFF0000UL)
#define TSW_CPU_PORT_IGRESS_STMID_MACHI_VID_SHIFT (16U)
#define TSW_CPU_PORT_IGRESS_STMID_MACHI_VID_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_STMID_MACHI_VID_SHIFT) & TSW_CPU_PORT_IGRESS_STMID_MACHI_VID_MASK)
#define TSW_CPU_PORT_IGRESS_STMID_MACHI_VID_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_STMID_MACHI_VID_MASK) >> TSW_CPU_PORT_IGRESS_STMID_MACHI_VID_SHIFT)

/*
 * MATCH (RW)
 *
 * MAC-Address [47:31] used by lookup.
 */
#define TSW_CPU_PORT_IGRESS_STMID_MACHI_MATCH_MASK (0xFFFFU)
#define TSW_CPU_PORT_IGRESS_STMID_MACHI_MATCH_SHIFT (0U)
#define TSW_CPU_PORT_IGRESS_STMID_MACHI_MATCH_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_STMID_MACHI_MATCH_SHIFT) & TSW_CPU_PORT_IGRESS_STMID_MACHI_MATCH_MASK)
#define TSW_CPU_PORT_IGRESS_STMID_MACHI_MATCH_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_STMID_MACHI_MATCH_MASK) >> TSW_CPU_PORT_IGRESS_STMID_MACHI_MATCH_SHIFT)

/* Bitfield definition for register: CPU_PORT_IGRESS_STMID_AMACHI */
/*
 * APCP (RW)
 *
 * Active Destination MAC, PCP
 */
#define TSW_CPU_PORT_IGRESS_STMID_AMACHI_APCP_MASK (0xF0000000UL)
#define TSW_CPU_PORT_IGRESS_STMID_AMACHI_APCP_SHIFT (28U)
#define TSW_CPU_PORT_IGRESS_STMID_AMACHI_APCP_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_STMID_AMACHI_APCP_SHIFT) & TSW_CPU_PORT_IGRESS_STMID_AMACHI_APCP_MASK)
#define TSW_CPU_PORT_IGRESS_STMID_AMACHI_APCP_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_STMID_AMACHI_APCP_MASK) >> TSW_CPU_PORT_IGRESS_STMID_AMACHI_APCP_SHIFT)

/*
 * AVID (RW)
 *
 * Active Destination MAC, VLAN ID
 */
#define TSW_CPU_PORT_IGRESS_STMID_AMACHI_AVID_MASK (0xFFF0000UL)
#define TSW_CPU_PORT_IGRESS_STMID_AMACHI_AVID_SHIFT (16U)
#define TSW_CPU_PORT_IGRESS_STMID_AMACHI_AVID_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_STMID_AMACHI_AVID_SHIFT) & TSW_CPU_PORT_IGRESS_STMID_AMACHI_AVID_MASK)
#define TSW_CPU_PORT_IGRESS_STMID_AMACHI_AVID_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_STMID_AMACHI_AVID_MASK) >> TSW_CPU_PORT_IGRESS_STMID_AMACHI_AVID_SHIFT)

/*
 * AMACH (RW)
 *
 * Active Destination MAC, MAC-Address [47:32]
 */
#define TSW_CPU_PORT_IGRESS_STMID_AMACHI_AMACH_MASK (0xFFFFU)
#define TSW_CPU_PORT_IGRESS_STMID_AMACHI_AMACH_SHIFT (0U)
#define TSW_CPU_PORT_IGRESS_STMID_AMACHI_AMACH_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_STMID_AMACHI_AMACH_SHIFT) & TSW_CPU_PORT_IGRESS_STMID_AMACHI_AMACH_MASK)
#define TSW_CPU_PORT_IGRESS_STMID_AMACHI_AMACH_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_STMID_AMACHI_AMACH_MASK) >> TSW_CPU_PORT_IGRESS_STMID_AMACHI_AMACH_SHIFT)

/* Bitfield definition for register: CPU_PORT_IGRESS_FRER_CONTROL */
/*
 * LATER (RWC)
 *
 * Latent error flag – write 1 to clear
 */
#define TSW_CPU_PORT_IGRESS_FRER_CONTROL_LATER_MASK (0x2U)
#define TSW_CPU_PORT_IGRESS_FRER_CONTROL_LATER_SHIFT (1U)
#define TSW_CPU_PORT_IGRESS_FRER_CONTROL_LATER_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_FRER_CONTROL_LATER_SHIFT) & TSW_CPU_PORT_IGRESS_FRER_CONTROL_LATER_MASK)
#define TSW_CPU_PORT_IGRESS_FRER_CONTROL_LATER_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_FRER_CONTROL_LATER_MASK) >> TSW_CPU_PORT_IGRESS_FRER_CONTROL_LATER_SHIFT)

/*
 * RTENC (RW)
 *
 * R-TAG encoding enable.
 */
#define TSW_CPU_PORT_IGRESS_FRER_CONTROL_RTENC_MASK (0x1U)
#define TSW_CPU_PORT_IGRESS_FRER_CONTROL_RTENC_SHIFT (0U)
#define TSW_CPU_PORT_IGRESS_FRER_CONTROL_RTENC_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_FRER_CONTROL_RTENC_SHIFT) & TSW_CPU_PORT_IGRESS_FRER_CONTROL_RTENC_MASK)
#define TSW_CPU_PORT_IGRESS_FRER_CONTROL_RTENC_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_FRER_CONTROL_RTENC_MASK) >> TSW_CPU_PORT_IGRESS_FRER_CONTROL_RTENC_SHIFT)

/* Bitfield definition for register: CPU_PORT_IGRESS_FRER_SIDSEL */
/*
 * SID (RW)
 *
 * Stream ID selection for host access to IRFUNC and SRFUNC.
 */
#define TSW_CPU_PORT_IGRESS_FRER_SIDSEL_SID_MASK (0xFFU)
#define TSW_CPU_PORT_IGRESS_FRER_SIDSEL_SID_SHIFT (0U)
#define TSW_CPU_PORT_IGRESS_FRER_SIDSEL_SID_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_FRER_SIDSEL_SID_SHIFT) & TSW_CPU_PORT_IGRESS_FRER_SIDSEL_SID_MASK)
#define TSW_CPU_PORT_IGRESS_FRER_SIDSEL_SID_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_FRER_SIDSEL_SID_MASK) >> TSW_CPU_PORT_IGRESS_FRER_SIDSEL_SID_SHIFT)

/* Bitfield definition for register: CPU_PORT_IGRESS_FRER_IRFUNC */
/*
 * FEN (RW)
 *
 * Individual recovery function: FEN – enable function for stream SIDSEL.SID. FIDX – function index for stream SIDSEL.SID If function does not exists (FIDX >= 2**FD), FEN will be set to 0.
 */
#define TSW_CPU_PORT_IGRESS_FRER_IRFUNC_FEN_MASK (0x80000000UL)
#define TSW_CPU_PORT_IGRESS_FRER_IRFUNC_FEN_SHIFT (31U)
#define TSW_CPU_PORT_IGRESS_FRER_IRFUNC_FEN_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_FRER_IRFUNC_FEN_SHIFT) & TSW_CPU_PORT_IGRESS_FRER_IRFUNC_FEN_MASK)
#define TSW_CPU_PORT_IGRESS_FRER_IRFUNC_FEN_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_FRER_IRFUNC_FEN_MASK) >> TSW_CPU_PORT_IGRESS_FRER_IRFUNC_FEN_SHIFT)

/*
 * FIDX (RW)
 *
 */
#define TSW_CPU_PORT_IGRESS_FRER_IRFUNC_FIDX_MASK (0xFFU)
#define TSW_CPU_PORT_IGRESS_FRER_IRFUNC_FIDX_SHIFT (0U)
#define TSW_CPU_PORT_IGRESS_FRER_IRFUNC_FIDX_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_FRER_IRFUNC_FIDX_SHIFT) & TSW_CPU_PORT_IGRESS_FRER_IRFUNC_FIDX_MASK)
#define TSW_CPU_PORT_IGRESS_FRER_IRFUNC_FIDX_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_FRER_IRFUNC_FIDX_MASK) >> TSW_CPU_PORT_IGRESS_FRER_IRFUNC_FIDX_SHIFT)

/* Bitfield definition for register: CPU_PORT_IGRESS_FRER_SRFUNC */
/*
 * FEN (RW)
 *
 * Sequence recovery function: FEN – enable function for stream SIDSEL.SID. FIDX – function index for stream SIDSEL.SID If function does not exists (FIDX >= 2**FD), FEN will be set to 0.
 */
#define TSW_CPU_PORT_IGRESS_FRER_SRFUNC_FEN_MASK (0x80000000UL)
#define TSW_CPU_PORT_IGRESS_FRER_SRFUNC_FEN_SHIFT (31U)
#define TSW_CPU_PORT_IGRESS_FRER_SRFUNC_FEN_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_FRER_SRFUNC_FEN_SHIFT) & TSW_CPU_PORT_IGRESS_FRER_SRFUNC_FEN_MASK)
#define TSW_CPU_PORT_IGRESS_FRER_SRFUNC_FEN_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_FRER_SRFUNC_FEN_MASK) >> TSW_CPU_PORT_IGRESS_FRER_SRFUNC_FEN_SHIFT)

/*
 * FIDX (RW)
 *
 */
#define TSW_CPU_PORT_IGRESS_FRER_SRFUNC_FIDX_MASK (0xFFU)
#define TSW_CPU_PORT_IGRESS_FRER_SRFUNC_FIDX_SHIFT (0U)
#define TSW_CPU_PORT_IGRESS_FRER_SRFUNC_FIDX_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_FRER_SRFUNC_FIDX_SHIFT) & TSW_CPU_PORT_IGRESS_FRER_SRFUNC_FIDX_MASK)
#define TSW_CPU_PORT_IGRESS_FRER_SRFUNC_FIDX_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_FRER_SRFUNC_FIDX_MASK) >> TSW_CPU_PORT_IGRESS_FRER_SRFUNC_FIDX_SHIFT)

/* Bitfield definition for register: CPU_PORT_IGRESS_FRER_FSELECT */
/*
 * FIDX (RW)
 *
 * Recovery function selection for host access at offset 0x140+
 */
#define TSW_CPU_PORT_IGRESS_FRER_FSELECT_FIDX_MASK (0xFFU)
#define TSW_CPU_PORT_IGRESS_FRER_FSELECT_FIDX_SHIFT (0U)
#define TSW_CPU_PORT_IGRESS_FRER_FSELECT_FIDX_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_FRER_FSELECT_FIDX_SHIFT) & TSW_CPU_PORT_IGRESS_FRER_FSELECT_FIDX_MASK)
#define TSW_CPU_PORT_IGRESS_FRER_FSELECT_FIDX_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_FRER_FSELECT_FIDX_MASK) >> TSW_CPU_PORT_IGRESS_FRER_FSELECT_FIDX_SHIFT)

/* Bitfield definition for register: CPU_PORT_IGRESS_FRER_FCTRL */
/*
 * FRSET (WO)
 *
 * Reset recovery function – self-resetting to 0
 */
#define TSW_CPU_PORT_IGRESS_FRER_FCTRL_FRSET_MASK (0x80000000UL)
#define TSW_CPU_PORT_IGRESS_FRER_FCTRL_FRSET_SHIFT (31U)
#define TSW_CPU_PORT_IGRESS_FRER_FCTRL_FRSET_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_FRER_FCTRL_FRSET_SHIFT) & TSW_CPU_PORT_IGRESS_FRER_FCTRL_FRSET_MASK)
#define TSW_CPU_PORT_IGRESS_FRER_FCTRL_FRSET_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_FRER_FCTRL_FRSET_MASK) >> TSW_CPU_PORT_IGRESS_FRER_FCTRL_FRSET_SHIFT)

/*
 * PATHS (RW)
 *
 * Number of paths (used by latent error detection)
 */
#define TSW_CPU_PORT_IGRESS_FRER_FCTRL_PATHS_MASK (0xFF0000UL)
#define TSW_CPU_PORT_IGRESS_FRER_FCTRL_PATHS_SHIFT (16U)
#define TSW_CPU_PORT_IGRESS_FRER_FCTRL_PATHS_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_FRER_FCTRL_PATHS_SHIFT) & TSW_CPU_PORT_IGRESS_FRER_FCTRL_PATHS_MASK)
#define TSW_CPU_PORT_IGRESS_FRER_FCTRL_PATHS_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_FRER_FCTRL_PATHS_MASK) >> TSW_CPU_PORT_IGRESS_FRER_FCTRL_PATHS_SHIFT)

/*
 * HLEN (RW)
 *
 * History length (used by Vector recovery algorithm)
 */
#define TSW_CPU_PORT_IGRESS_FRER_FCTRL_HLEN_MASK (0x1F00U)
#define TSW_CPU_PORT_IGRESS_FRER_FCTRL_HLEN_SHIFT (8U)
#define TSW_CPU_PORT_IGRESS_FRER_FCTRL_HLEN_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_FRER_FCTRL_HLEN_SHIFT) & TSW_CPU_PORT_IGRESS_FRER_FCTRL_HLEN_MASK)
#define TSW_CPU_PORT_IGRESS_FRER_FCTRL_HLEN_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_FRER_FCTRL_HLEN_MASK) >> TSW_CPU_PORT_IGRESS_FRER_FCTRL_HLEN_SHIFT)

/*
 * ALGO (RW)
 *
 * Recovery function algorithm: 0 – Vector recovery algorithm 1 – Match recovery algorithm
 */
#define TSW_CPU_PORT_IGRESS_FRER_FCTRL_ALGO_MASK (0x10U)
#define TSW_CPU_PORT_IGRESS_FRER_FCTRL_ALGO_SHIFT (4U)
#define TSW_CPU_PORT_IGRESS_FRER_FCTRL_ALGO_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_FRER_FCTRL_ALGO_SHIFT) & TSW_CPU_PORT_IGRESS_FRER_FCTRL_ALGO_MASK)
#define TSW_CPU_PORT_IGRESS_FRER_FCTRL_ALGO_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_FRER_FCTRL_ALGO_MASK) >> TSW_CPU_PORT_IGRESS_FRER_FCTRL_ALGO_SHIFT)

/*
 * LATEN (RW)
 *
 * Latent error detection enable
 */
#define TSW_CPU_PORT_IGRESS_FRER_FCTRL_LATEN_MASK (0x8U)
#define TSW_CPU_PORT_IGRESS_FRER_FCTRL_LATEN_SHIFT (3U)
#define TSW_CPU_PORT_IGRESS_FRER_FCTRL_LATEN_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_FRER_FCTRL_LATEN_SHIFT) & TSW_CPU_PORT_IGRESS_FRER_FCTRL_LATEN_MASK)
#define TSW_CPU_PORT_IGRESS_FRER_FCTRL_LATEN_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_FRER_FCTRL_LATEN_MASK) >> TSW_CPU_PORT_IGRESS_FRER_FCTRL_LATEN_SHIFT)

/*
 * IND (RW)
 *
 * Individual function (802.1CB 10.4.1.10)
 */
#define TSW_CPU_PORT_IGRESS_FRER_FCTRL_IND_MASK (0x4U)
#define TSW_CPU_PORT_IGRESS_FRER_FCTRL_IND_SHIFT (2U)
#define TSW_CPU_PORT_IGRESS_FRER_FCTRL_IND_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_FRER_FCTRL_IND_SHIFT) & TSW_CPU_PORT_IGRESS_FRER_FCTRL_IND_MASK)
#define TSW_CPU_PORT_IGRESS_FRER_FCTRL_IND_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_FRER_FCTRL_IND_MASK) >> TSW_CPU_PORT_IGRESS_FRER_FCTRL_IND_SHIFT)

/*
 * TNS (RW)
 *
 * TakeNoSequence (802.1CB 10.4.1.9)
 */
#define TSW_CPU_PORT_IGRESS_FRER_FCTRL_TNS_MASK (0x2U)
#define TSW_CPU_PORT_IGRESS_FRER_FCTRL_TNS_SHIFT (1U)
#define TSW_CPU_PORT_IGRESS_FRER_FCTRL_TNS_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_FRER_FCTRL_TNS_SHIFT) & TSW_CPU_PORT_IGRESS_FRER_FCTRL_TNS_MASK)
#define TSW_CPU_PORT_IGRESS_FRER_FCTRL_TNS_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_FRER_FCTRL_TNS_MASK) >> TSW_CPU_PORT_IGRESS_FRER_FCTRL_TNS_SHIFT)

/* Bitfield definition for register: CPU_PORT_IGRESS_FRER_RESETMSEC */
/*
 * FSRMS (RW)
 *
 * frerSeqRcvyResetMSec (802.1CB 10.4.1.7)
 */
#define TSW_CPU_PORT_IGRESS_FRER_RESETMSEC_FSRMS_MASK (0xFFFFFFUL)
#define TSW_CPU_PORT_IGRESS_FRER_RESETMSEC_FSRMS_SHIFT (0U)
#define TSW_CPU_PORT_IGRESS_FRER_RESETMSEC_FSRMS_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_FRER_RESETMSEC_FSRMS_SHIFT) & TSW_CPU_PORT_IGRESS_FRER_RESETMSEC_FSRMS_MASK)
#define TSW_CPU_PORT_IGRESS_FRER_RESETMSEC_FSRMS_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_FRER_RESETMSEC_FSRMS_MASK) >> TSW_CPU_PORT_IGRESS_FRER_RESETMSEC_FSRMS_SHIFT)

/* Bitfield definition for register: CPU_PORT_IGRESS_FRER_LATRSPERIOD */
/*
 * FLATR (RW)
 *
 * frerSeqRcvyLatentResetPeriod (802.1CB 10.4.1.12.4)
 */
#define TSW_CPU_PORT_IGRESS_FRER_LATRSPERIOD_FLATR_MASK (0xFFFFFFUL)
#define TSW_CPU_PORT_IGRESS_FRER_LATRSPERIOD_FLATR_SHIFT (0U)
#define TSW_CPU_PORT_IGRESS_FRER_LATRSPERIOD_FLATR_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_FRER_LATRSPERIOD_FLATR_SHIFT) & TSW_CPU_PORT_IGRESS_FRER_LATRSPERIOD_FLATR_MASK)
#define TSW_CPU_PORT_IGRESS_FRER_LATRSPERIOD_FLATR_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_FRER_LATRSPERIOD_FLATR_MASK) >> TSW_CPU_PORT_IGRESS_FRER_LATRSPERIOD_FLATR_SHIFT)

/* Bitfield definition for register: CPU_PORT_IGRESS_FRER_LATTESTPERIOD */
/*
 * FLATT (RW)
 *
 * frerSeqRcvyLatentErrorPeriod (802.1CB 10.4.1.12.2)
 */
#define TSW_CPU_PORT_IGRESS_FRER_LATTESTPERIOD_FLATT_MASK (0xFFFFFFUL)
#define TSW_CPU_PORT_IGRESS_FRER_LATTESTPERIOD_FLATT_SHIFT (0U)
#define TSW_CPU_PORT_IGRESS_FRER_LATTESTPERIOD_FLATT_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_FRER_LATTESTPERIOD_FLATT_SHIFT) & TSW_CPU_PORT_IGRESS_FRER_LATTESTPERIOD_FLATT_MASK)
#define TSW_CPU_PORT_IGRESS_FRER_LATTESTPERIOD_FLATT_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_FRER_LATTESTPERIOD_FLATT_MASK) >> TSW_CPU_PORT_IGRESS_FRER_LATTESTPERIOD_FLATT_SHIFT)

/* Bitfield definition for register: CPU_PORT_IGRESS_FRER_LATERRDIFFALW */
/*
 * FDIFF (RW)
 *
 * frerSeqRcvyLatentErrorDifference (802.1CB 10.4.1.12.1)
 */
#define TSW_CPU_PORT_IGRESS_FRER_LATERRDIFFALW_FDIFF_MASK (0xFFFFFFFFUL)
#define TSW_CPU_PORT_IGRESS_FRER_LATERRDIFFALW_FDIFF_SHIFT (0U)
#define TSW_CPU_PORT_IGRESS_FRER_LATERRDIFFALW_FDIFF_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_FRER_LATERRDIFFALW_FDIFF_SHIFT) & TSW_CPU_PORT_IGRESS_FRER_LATERRDIFFALW_FDIFF_MASK)
#define TSW_CPU_PORT_IGRESS_FRER_LATERRDIFFALW_FDIFF_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_FRER_LATERRDIFFALW_FDIFF_MASK) >> TSW_CPU_PORT_IGRESS_FRER_LATERRDIFFALW_FDIFF_SHIFT)

/* Bitfield definition for register: CPU_PORT_IGRESS_FRER_LATERRCNT */
/*
 * LATERR (RWC)
 *
 * Counter – latent error detect. Write any value to clear
 */
#define TSW_CPU_PORT_IGRESS_FRER_LATERRCNT_LATERR_MASK (0xFFFFFFFFUL)
#define TSW_CPU_PORT_IGRESS_FRER_LATERRCNT_LATERR_SHIFT (0U)
#define TSW_CPU_PORT_IGRESS_FRER_LATERRCNT_LATERR_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_IGRESS_FRER_LATERRCNT_LATERR_SHIFT) & TSW_CPU_PORT_IGRESS_FRER_LATERRCNT_LATERR_MASK)
#define TSW_CPU_PORT_IGRESS_FRER_LATERRCNT_LATERR_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_IGRESS_FRER_LATERRCNT_LATERR_MASK) >> TSW_CPU_PORT_IGRESS_FRER_LATERRCNT_LATERR_SHIFT)

/* Bitfield definition for register array: IGFRCNT */
/*
 * VALUE (RO)
 *
 * Frame counters
 */
#define TSW_IGFRCNT_VALUE_MASK (0xFFFFFFFFUL)
#define TSW_IGFRCNT_VALUE_SHIFT (0U)
#define TSW_IGFRCNT_VALUE_GET(x) (((uint32_t)(x) & TSW_IGFRCNT_VALUE_MASK) >> TSW_IGFRCNT_VALUE_SHIFT)

/* Bitfield definition for register: CPU_PORT_MONITOR_CTRL */
/*
 * EN (R/W)
 *
 * Enables counter. If deasserted the counter process stops and the counters hold their value.
 */
#define TSW_CPU_PORT_MONITOR_CTRL_EN_MASK (0x1U)
#define TSW_CPU_PORT_MONITOR_CTRL_EN_SHIFT (0U)
#define TSW_CPU_PORT_MONITOR_CTRL_EN_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_MONITOR_CTRL_EN_SHIFT) & TSW_CPU_PORT_MONITOR_CTRL_EN_MASK)
#define TSW_CPU_PORT_MONITOR_CTRL_EN_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_MONITOR_CTRL_EN_MASK) >> TSW_CPU_PORT_MONITOR_CTRL_EN_SHIFT)

/* Bitfield definition for register: CPU_PORT_MONITOR_RESET */
/*
 * RSRX (WO)
 *
 * Write '1' to reset all RX counters.
 */
#define TSW_CPU_PORT_MONITOR_RESET_RSRX_MASK (0x4U)
#define TSW_CPU_PORT_MONITOR_RESET_RSRX_SHIFT (2U)
#define TSW_CPU_PORT_MONITOR_RESET_RSRX_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_MONITOR_RESET_RSRX_SHIFT) & TSW_CPU_PORT_MONITOR_RESET_RSRX_MASK)
#define TSW_CPU_PORT_MONITOR_RESET_RSRX_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_MONITOR_RESET_RSRX_MASK) >> TSW_CPU_PORT_MONITOR_RESET_RSRX_SHIFT)

/*
 * RSTX (WO)
 *
 * Write '1' to reset all TX counters
 */
#define TSW_CPU_PORT_MONITOR_RESET_RSTX_MASK (0x2U)
#define TSW_CPU_PORT_MONITOR_RESET_RSTX_SHIFT (1U)
#define TSW_CPU_PORT_MONITOR_RESET_RSTX_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_MONITOR_RESET_RSTX_SHIFT) & TSW_CPU_PORT_MONITOR_RESET_RSTX_MASK)
#define TSW_CPU_PORT_MONITOR_RESET_RSTX_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_MONITOR_RESET_RSTX_MASK) >> TSW_CPU_PORT_MONITOR_RESET_RSTX_SHIFT)

/*
 * RSALL (WO)
 *
 * Write '1' to reset all TX&RX counters.
 */
#define TSW_CPU_PORT_MONITOR_RESET_RSALL_MASK (0x1U)
#define TSW_CPU_PORT_MONITOR_RESET_RSALL_SHIFT (0U)
#define TSW_CPU_PORT_MONITOR_RESET_RSALL_SET(x) (((uint32_t)(x) << TSW_CPU_PORT_MONITOR_RESET_RSALL_SHIFT) & TSW_CPU_PORT_MONITOR_RESET_RSALL_MASK)
#define TSW_CPU_PORT_MONITOR_RESET_RSALL_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_MONITOR_RESET_RSALL_MASK) >> TSW_CPU_PORT_MONITOR_RESET_RSALL_SHIFT)

/* Bitfield definition for register: CPU_PORT_MONITOR_PARAM */
/*
 * RX_CNT_EN_VEC (RO)
 *
 * Vector of implemented RX counters. E.g. 0x000F means only the first 4 RX counter are available.
 */
#define TSW_CPU_PORT_MONITOR_PARAM_RX_CNT_EN_VEC_MASK (0xFFFF0000UL)
#define TSW_CPU_PORT_MONITOR_PARAM_RX_CNT_EN_VEC_SHIFT (16U)
#define TSW_CPU_PORT_MONITOR_PARAM_RX_CNT_EN_VEC_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_MONITOR_PARAM_RX_CNT_EN_VEC_MASK) >> TSW_CPU_PORT_MONITOR_PARAM_RX_CNT_EN_VEC_SHIFT)

/*
 * TX_CNT_EN_VEC (RO)
 *
 * Vector of implemented RX counters. E.g. 0x000F means only the first 4 RX counter are available.
 */
#define TSW_CPU_PORT_MONITOR_PARAM_TX_CNT_EN_VEC_MASK (0xFF00U)
#define TSW_CPU_PORT_MONITOR_PARAM_TX_CNT_EN_VEC_SHIFT (8U)
#define TSW_CPU_PORT_MONITOR_PARAM_TX_CNT_EN_VEC_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_MONITOR_PARAM_TX_CNT_EN_VEC_MASK) >> TSW_CPU_PORT_MONITOR_PARAM_TX_CNT_EN_VEC_SHIFT)

/*
 * CNTW (RO)
 *
 * Vector of implemented RX counters. E.g. 0x000F means only the first 4 RX counter
 * are available.
 */
#define TSW_CPU_PORT_MONITOR_PARAM_CNTW_MASK (0x7FU)
#define TSW_CPU_PORT_MONITOR_PARAM_CNTW_SHIFT (0U)
#define TSW_CPU_PORT_MONITOR_PARAM_CNTW_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_MONITOR_PARAM_CNTW_MASK) >> TSW_CPU_PORT_MONITOR_PARAM_CNTW_SHIFT)

/* Bitfield definition for register: CPU_PORT_MONITOR_TX_COUNTER_TX_FGOOD */
/*
 * TX_FGOOD (RO)
 *
 * Good transmitted Frames to TX TSN-EP.
 */
#define TSW_CPU_PORT_MONITOR_TX_COUNTER_TX_FGOOD_TX_FGOOD_MASK (0xFFFFFFFFUL)
#define TSW_CPU_PORT_MONITOR_TX_COUNTER_TX_FGOOD_TX_FGOOD_SHIFT (0U)
#define TSW_CPU_PORT_MONITOR_TX_COUNTER_TX_FGOOD_TX_FGOOD_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_MONITOR_TX_COUNTER_TX_FGOOD_TX_FGOOD_MASK) >> TSW_CPU_PORT_MONITOR_TX_COUNTER_TX_FGOOD_TX_FGOOD_SHIFT)

/* Bitfield definition for register: CPU_PORT_MONITOR_TX_COUNTER_TX_FERROR */
/*
 * TX_FERROR (RO)
 *
 * Transmitted Frames with Error to TX TSN-EP.
 */
#define TSW_CPU_PORT_MONITOR_TX_COUNTER_TX_FERROR_TX_FERROR_MASK (0xFFFFFFFFUL)
#define TSW_CPU_PORT_MONITOR_TX_COUNTER_TX_FERROR_TX_FERROR_SHIFT (0U)
#define TSW_CPU_PORT_MONITOR_TX_COUNTER_TX_FERROR_TX_FERROR_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_MONITOR_TX_COUNTER_TX_FERROR_TX_FERROR_MASK) >> TSW_CPU_PORT_MONITOR_TX_COUNTER_TX_FERROR_TX_FERROR_SHIFT)

/* Bitfield definition for register: CPU_PORT_MONITOR_TX_COUNTER_TX_DROP_OVFL */
/*
 * TX_DROP_OVFL (RO)
 *
 * Dropped frames by full queue of TSN-EP.
 */
#define TSW_CPU_PORT_MONITOR_TX_COUNTER_TX_DROP_OVFL_TX_DROP_OVFL_MASK (0xFFFFFFFFUL)
#define TSW_CPU_PORT_MONITOR_TX_COUNTER_TX_DROP_OVFL_TX_DROP_OVFL_SHIFT (0U)
#define TSW_CPU_PORT_MONITOR_TX_COUNTER_TX_DROP_OVFL_TX_DROP_OVFL_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_MONITOR_TX_COUNTER_TX_DROP_OVFL_TX_DROP_OVFL_MASK) >> TSW_CPU_PORT_MONITOR_TX_COUNTER_TX_DROP_OVFL_TX_DROP_OVFL_SHIFT)

/* Bitfield definition for register: CPU_PORT_MONITOR_RX_COUNTER_RX_FGOOD */
/*
 * RX_FGOOD (RO)
 *
 * Good received frame by ingress buffer.
 */
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_FGOOD_RX_FGOOD_MASK (0xFFFFFFFFUL)
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_FGOOD_RX_FGOOD_SHIFT (0U)
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_FGOOD_RX_FGOOD_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_FGOOD_RX_FGOOD_MASK) >> TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_FGOOD_RX_FGOOD_SHIFT)

/* Bitfield definition for register: CPU_PORT_MONITOR_RX_COUNTER_RX_FERROR */
/*
 * RX_FERROR (RO)
 *
 * Bad received frame by ingress buffer.
 */
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_FERROR_RX_FERROR_MASK (0xFFFFFFFFUL)
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_FERROR_RX_FERROR_SHIFT (0U)
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_FERROR_RX_FERROR_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_FERROR_RX_FERROR_MASK) >> TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_FERROR_RX_FERROR_SHIFT)

/* Bitfield definition for register: CPU_PORT_MONITOR_RX_COUNTER_RX_KNOWN */
/*
 * RX_KNOWN (RO)
 *
 * Number of frames passed ingress with hit by MAC Table. This includes Broadcast and non-relayed frames.
 */
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_KNOWN_RX_KNOWN_MASK (0xFFFFFFFFUL)
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_KNOWN_RX_KNOWN_SHIFT (0U)
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_KNOWN_RX_KNOWN_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_KNOWN_RX_KNOWN_MASK) >> TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_KNOWN_RX_KNOWN_SHIFT)

/* Bitfield definition for register: CPU_PORT_MONITOR_RX_COUNTER_RX_UNKNOWN */
/*
 * RX_UNKNOWN (RO)
 *
 * Number of frames passed ingress without hit by MAC table.
 */
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_UNKNOWN_RX_UNKNOWN_MASK (0xFFFFFFFFUL)
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_UNKNOWN_RX_UNKNOWN_SHIFT (0U)
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_UNKNOWN_RX_UNKNOWN_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_UNKNOWN_RX_UNKNOWN_MASK) >> TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_UNKNOWN_RX_UNKNOWN_SHIFT)

/* Bitfield definition for register: CPU_PORT_MONITOR_RX_COUNTER_RX_UC */
/*
 * RX_UC (RO)
 *
 * Number of unicast frames
 */
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_UC_RX_UC_MASK (0xFFFFFFFFUL)
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_UC_RX_UC_SHIFT (0U)
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_UC_RX_UC_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_UC_RX_UC_MASK) >> TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_UC_RX_UC_SHIFT)

/* Bitfield definition for register: CPU_PORT_MONITOR_RX_COUNTER_RX_INTERN */
/*
 * RX_INTERN (RO)
 *
 * Number of non-relay frames
 */
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_INTERN_RX_INTERN_MASK (0xFFFFFFFFUL)
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_INTERN_RX_INTERN_SHIFT (0U)
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_INTERN_RX_INTERN_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_INTERN_RX_INTERN_MASK) >> TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_INTERN_RX_INTERN_SHIFT)

/* Bitfield definition for register: CPU_PORT_MONITOR_RX_COUNTER_RX_BC */
/*
 * RX_BC (RO)
 *
 * Number of Broadcast frames
 */
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_BC_RX_BC_MASK (0xFFFFFFFFUL)
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_BC_RX_BC_SHIFT (0U)
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_BC_RX_BC_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_BC_RX_BC_MASK) >> TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_BC_RX_BC_SHIFT)

/* Bitfield definition for register: CPU_PORT_MONITOR_RX_COUNTER_RX_MULTI */
/*
 * RX_MULTI (RO)
 *
 * Number of Multicast frames
 */
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_MULTI_RX_MULTI_MASK (0xFFFFFFFFUL)
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_MULTI_RX_MULTI_SHIFT (0U)
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_MULTI_RX_MULTI_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_MULTI_RX_MULTI_MASK) >> TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_MULTI_RX_MULTI_SHIFT)

/* Bitfield definition for register: CPU_PORT_MONITOR_RX_COUNTER_RX_VLAN */
/*
 * RX_VLAN (RO)
 *
 * Number of VLAN tagged frames
 */
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_VLAN_RX_VLAN_MASK (0xFFFFFFFFUL)
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_VLAN_RX_VLAN_SHIFT (0U)
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_VLAN_RX_VLAN_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_VLAN_RX_VLAN_MASK) >> TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_VLAN_RX_VLAN_SHIFT)

/* Bitfield definition for register: CPU_PORT_MONITOR_RX_COUNTER_RX_DROP_OVFL */
/*
 * RX_DROP_OVFL (RO)
 *
 * Dropped frames by ingress overflow.
 */
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_DROP_OVFL_RX_DROP_OVFL_MASK (0xFFFFFFFFUL)
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_DROP_OVFL_RX_DROP_OVFL_SHIFT (0U)
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_DROP_OVFL_RX_DROP_OVFL_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_DROP_OVFL_RX_DROP_OVFL_MASK) >> TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_DROP_OVFL_RX_DROP_OVFL_SHIFT)

/* Bitfield definition for register: CPU_PORT_MONITOR_RX_COUNTER_RX_DROP_LU */
/*
 * RX_DROP_LU (RO)
 *
 * Dropped frames by LookUp decision.
 */
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_DROP_LU_RX_DROP_LU_MASK (0xFFFFFFFFUL)
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_DROP_LU_RX_DROP_LU_SHIFT (0U)
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_DROP_LU_RX_DROP_LU_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_DROP_LU_RX_DROP_LU_MASK) >> TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_DROP_LU_RX_DROP_LU_SHIFT)

/* Bitfield definition for register: CPU_PORT_MONITOR_RX_COUNTER_RX_DROP_ERR */
/*
 * RX_DROP_ERR (RO)
 *
 * Dropped frames with error by ingress. Possible in S&F mode or when frame is queued in ingress.
 */
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_DROP_ERR_RX_DROP_ERR_MASK (0xFFFFFFFFUL)
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_DROP_ERR_RX_DROP_ERR_SHIFT (0U)
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_DROP_ERR_RX_DROP_ERR_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_DROP_ERR_RX_DROP_ERR_MASK) >> TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_DROP_ERR_RX_DROP_ERR_SHIFT)

/* Bitfield definition for register: CPU_PORT_MONITOR_RX_COUNTER_RX_DROP_VLAN */
/*
 * RX_DROP_VLAN (RO)
 *
 * Dropped frames by incompatible VLAN.
 */
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_DROP_VLAN_RX_DROP_VLAN_MASK (0xFFFFFFFFUL)
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_DROP_VLAN_RX_DROP_VLAN_SHIFT (0U)
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_DROP_VLAN_RX_DROP_VLAN_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_DROP_VLAN_RX_DROP_VLAN_MASK) >> TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_DROP_VLAN_RX_DROP_VLAN_SHIFT)

/* Bitfield definition for register: CPU_PORT_MONITOR_RX_COUNTER_RX_FPE_FGOOD */
/*
 * RX_FPE_FGOOD (RO)
 *
 * Number of preemptable frames. Subset of RX_FGOOD
 */
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_FPE_FGOOD_RX_FPE_FGOOD_MASK (0xFFFFFFFFUL)
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_FPE_FGOOD_RX_FPE_FGOOD_SHIFT (0U)
#define TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_FPE_FGOOD_RX_FPE_FGOOD_GET(x) (((uint32_t)(x) & TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_FPE_FGOOD_RX_FPE_FGOOD_MASK) >> TSW_CPU_PORT_MONITOR_RX_COUNTER_RX_FPE_FGOOD_RX_FPE_FGOOD_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: MAC_VER */
/*
 * VER_H (R)
 *
 * Major version number (higher part of the version)
 */
#define TSW_TSNPORT_MAC_MAC_VER_VER_H_MASK (0xFFFF0000UL)
#define TSW_TSNPORT_MAC_MAC_VER_VER_H_SHIFT (16U)
#define TSW_TSNPORT_MAC_MAC_VER_VER_H_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_VER_VER_H_MASK) >> TSW_TSNPORT_MAC_MAC_VER_VER_H_SHIFT)

/*
 * VER_L (R)
 *
 * Minor version number (lower part of the version)
 */
#define TSW_TSNPORT_MAC_MAC_VER_VER_L_MASK (0xFFFFU)
#define TSW_TSNPORT_MAC_MAC_VER_VER_L_SHIFT (0U)
#define TSW_TSNPORT_MAC_MAC_VER_VER_L_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_VER_VER_L_MASK) >> TSW_TSNPORT_MAC_MAC_VER_VER_L_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: MAC_MACADDR_L */
/*
 * MACADDR (R/W)
 *
 * MAC address
 * Lower bits of MAC address (31:0).
 * MACADDR only be modified if TX_EN=0 and RX_EN=0.
 */
#define TSW_TSNPORT_MAC_MAC_MACADDR_L_MACADDR_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_MAC_MAC_MACADDR_L_MACADDR_SHIFT (0U)
#define TSW_TSNPORT_MAC_MAC_MACADDR_L_MACADDR_SET(x) (((uint32_t)(x) << TSW_TSNPORT_MAC_MAC_MACADDR_L_MACADDR_SHIFT) & TSW_TSNPORT_MAC_MAC_MACADDR_L_MACADDR_MASK)
#define TSW_TSNPORT_MAC_MAC_MACADDR_L_MACADDR_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_MACADDR_L_MACADDR_MASK) >> TSW_TSNPORT_MAC_MAC_MACADDR_L_MACADDR_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: MAC_MACADDR_H */
/*
 * PROMISC (R/W)
 *
 * 0 – disabled
 * 1 – enabled
 * If promiscuous mode is enabled, then reception of all frames independent from the
 * Ethernet destination address is enabled.
 * PROMISC can be changed at any time.
 */
#define TSW_TSNPORT_MAC_MAC_MACADDR_H_PROMISC_MASK (0x10000UL)
#define TSW_TSNPORT_MAC_MAC_MACADDR_H_PROMISC_SHIFT (16U)
#define TSW_TSNPORT_MAC_MAC_MACADDR_H_PROMISC_SET(x) (((uint32_t)(x) << TSW_TSNPORT_MAC_MAC_MACADDR_H_PROMISC_SHIFT) & TSW_TSNPORT_MAC_MAC_MACADDR_H_PROMISC_MASK)
#define TSW_TSNPORT_MAC_MAC_MACADDR_H_PROMISC_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_MACADDR_H_PROMISC_MASK) >> TSW_TSNPORT_MAC_MAC_MACADDR_H_PROMISC_SHIFT)

/*
 * MACADDR (R/W)
 *
 * MAC address (see Chapter 4.1)
 * Upper bits of MAC address (47:32).
 * MACADDR can only be modified if TX_EN=0 and RX_EN=0.
 */
#define TSW_TSNPORT_MAC_MAC_MACADDR_H_MACADDR_MASK (0xFFFFU)
#define TSW_TSNPORT_MAC_MAC_MACADDR_H_MACADDR_SHIFT (0U)
#define TSW_TSNPORT_MAC_MAC_MACADDR_H_MACADDR_SET(x) (((uint32_t)(x) << TSW_TSNPORT_MAC_MAC_MACADDR_H_MACADDR_SHIFT) & TSW_TSNPORT_MAC_MAC_MACADDR_H_MACADDR_MASK)
#define TSW_TSNPORT_MAC_MAC_MACADDR_H_MACADDR_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_MACADDR_H_MACADDR_MASK) >> TSW_TSNPORT_MAC_MAC_MACADDR_H_MACADDR_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: MAC_MAC_CTRL */
/*
 * FSTIM (R/W)
 *
 * Fault Stimulation
 * See Chapter 11.3, Table 11-1 for details.
 * FSTIM is write-locked if CSA=1.
 */
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_FSTIM_MASK (0x1F000000UL)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_FSTIM_SHIFT (24U)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_FSTIM_SET(x) (((uint32_t)(x) << TSW_TSNPORT_MAC_MAC_MAC_CTRL_FSTIM_SHIFT) & TSW_TSNPORT_MAC_MAC_MAC_CTRL_FSTIM_MASK)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_FSTIM_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_MAC_CTRL_FSTIM_MASK) >> TSW_TSNPORT_MAC_MAC_MAC_CTRL_FSTIM_SHIFT)

/*
 * RCA (R)
 *
 * <ref_clk> active
 * 0 – not active
 * 1 – active
 * See chapter 11.2.3 for details.
 */
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_RCA_MASK (0x100000UL)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_RCA_SHIFT (20U)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_RCA_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_MAC_CTRL_RCA_MASK) >> TSW_TSNPORT_MAC_MAC_MAC_CTRL_RCA_SHIFT)

/*
 * MCA (R)
 *
 * <mii_clk> active
 * 0 – not active
 * 1 – active
 * See chapter 11.2.3 for details.
 */
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_MCA_MASK (0x80000UL)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_MCA_SHIFT (19U)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_MCA_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_MAC_CTRL_MCA_MASK) >> TSW_TSNPORT_MAC_MAC_MAC_CTRL_MCA_SHIFT)

/*
 * SEN (R/W)
 *
 * Safety Enable
 * 0 – disabled
 * 1 – enabled
 * If enabled, then two instances of the logic core of LLEMAC-1G are compared at
 * runtime to each other.
 * SEN can only be changed if RX_EN and TX_EN can be read as 0. Deactivation delays
 * of RX_EN and TX_EN have to be considered. It is possible to change SEN together
 * with the activation of RX_EN and TX_EN.
 */
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_SEN_MASK (0x10000UL)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_SEN_SHIFT (16U)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_SEN_SET(x) (((uint32_t)(x) << TSW_TSNPORT_MAC_MAC_MAC_CTRL_SEN_SHIFT) & TSW_TSNPORT_MAC_MAC_MAC_CTRL_SEN_MASK)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_SEN_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_MAC_CTRL_SEN_MASK) >> TSW_TSNPORT_MAC_MAC_MAC_CTRL_SEN_SHIFT)

/*
 * CSA (R)
 *
 * Clock switching active (<tx_clk>)
 * 0 – not active
 * 1 – active
 * Switching of <tx_clk> is commanded if CLKSEL or FSTIM (see Table 11-1) are
 * written. Clock switching takes a few clock cycles and this is signaled with CSA=1.
 * When CSA=1 then CLKSEL and FSTIM are write-locked and cannot be changed.
 */
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_CSA_MASK (0x2000U)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_CSA_SHIFT (13U)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_CSA_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_MAC_CTRL_CSA_MASK) >> TSW_TSNPORT_MAC_MAC_MAC_CTRL_CSA_SHIFT)

/*
 * RCE (R/W)
 *
 * <ref_clk> enable
 * 0 – disabled
 * 1 – enabled
 * RCE can only be modified if CLKSEL=111. See Chapter 7.3.3 for further details.
 */
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_RCE_MASK (0x1000U)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_RCE_SHIFT (12U)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_RCE_SET(x) (((uint32_t)(x) << TSW_TSNPORT_MAC_MAC_MAC_CTRL_RCE_SHIFT) & TSW_TSNPORT_MAC_MAC_MAC_CTRL_RCE_MASK)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_RCE_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_MAC_CTRL_RCE_MASK) >> TSW_TSNPORT_MAC_MAC_MAC_CTRL_RCE_SHIFT)

/*
 * MCE (R/W)
 *
 * <mii_clk> enable
 * 0 – disabled
 * 1 – enabled
 * MCE can only be modified if CLKSEL=111. See Chapter 7.3.3 for further details.
 */
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_MCE_MASK (0x800U)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_MCE_SHIFT (11U)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_MCE_SET(x) (((uint32_t)(x) << TSW_TSNPORT_MAC_MAC_MAC_CTRL_MCE_SHIFT) & TSW_TSNPORT_MAC_MAC_MAC_CTRL_MCE_MASK)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_MCE_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_MAC_CTRL_MCE_MASK) >> TSW_TSNPORT_MAC_MAC_MAC_CTRL_MCE_SHIFT)

/*
 * CLKSEL (R/W)
 *
 * TX path clock selector
 * 000 – <mii_clk>
 * 001 – <ref_clk> (recommended setting for this selection)
 * 010 – <ref_clk> divided by 5
 * 011 – <ref_clk> divided by 10
 * 100 – <ref_clk> divided by 50
 * 111 – <ref_clk> and enables modification of RCE and MCE
 * others – <ref_clk>
 * See Chapter 7 for further details.
 * CLKSEL is write-locked if CSA=1.
 */
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_CLKSEL_MASK (0x700U)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_CLKSEL_SHIFT (8U)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_CLKSEL_SET(x) (((uint32_t)(x) << TSW_TSNPORT_MAC_MAC_MAC_CTRL_CLKSEL_SHIFT) & TSW_TSNPORT_MAC_MAC_MAC_CTRL_CLKSEL_MASK)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_CLKSEL_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_MAC_CTRL_CLKSEL_MASK) >> TSW_TSNPORT_MAC_MAC_MAC_CTRL_CLKSEL_SHIFT)

/*
 * PHYSEL (R/W)
 *
 * Selection of the PHY (See Chapter 4.6.)
 * 00 – MII
 * 01 – GMII
 * 10 – RGMII
 * 11 – reserved
 * PHYSEL can only be changed if RX_EN=0 and TX_EN=0. Deactivation delays of
 * RX_EN and TX_EN have to be considered. PHYSEL can only be changed, if these
 * register bits can be read as 0. It is possible to change PHYSEL together with the
 * activation of RX_EN and TX_EN.
 * PHYSEL drives the output <rx_physel>.
 */
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_PHYSEL_MASK (0x60U)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_PHYSEL_SHIFT (5U)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_PHYSEL_SET(x) (((uint32_t)(x) << TSW_TSNPORT_MAC_MAC_MAC_CTRL_PHYSEL_SHIFT) & TSW_TSNPORT_MAC_MAC_MAC_CTRL_PHYSEL_MASK)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_PHYSEL_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_MAC_CTRL_PHYSEL_MASK) >> TSW_TSNPORT_MAC_MAC_MAC_CTRL_PHYSEL_SHIFT)

/*
 * GMIIMODE (R/W)
 *
 * GMII mode / Ethernet speed selection (See Chapter 4.5.)
 * 0 – MII: 10Mbit/s or 100Mbit/s
 * 1 – GMII: 1GBit/s
 * GMIIMODE can only be changed if RX_EN=0 and TX_EN=0. Deactivation delays of
 * RX_EN and TX_EN have to be considered. GMIIMODE can only be changed, if these
 * register bits can be read as 0. It is possible to change GMIIMODE together with the
 * activation of RX_EN and TX_EN.
 * GMIIMODE drives the outputs <tx_gmiimode> and <rx_gmiimode>.
 */
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_GMIIMODE_MASK (0x10U)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_GMIIMODE_SHIFT (4U)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_GMIIMODE_SET(x) (((uint32_t)(x) << TSW_TSNPORT_MAC_MAC_MAC_CTRL_GMIIMODE_SHIFT) & TSW_TSNPORT_MAC_MAC_MAC_CTRL_GMIIMODE_MASK)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_GMIIMODE_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_MAC_CTRL_GMIIMODE_MASK) >> TSW_TSNPORT_MAC_MAC_MAC_CTRL_GMIIMODE_SHIFT)

/*
 * JUMBO (R/W)
 *
 * Jumbo frame support
 * 0 – jumbo frames not supported
 * 1 – jumbo frame supported (not recommended)
 * Jumbo frames are non-standard Ethernet frames with a size bigger than envelope
 * frames (which contain 1982 payload bytes). If jumbo frames are not supported, then
 * LLEMAC-1G generates the appropriate error signals (<tx_gmii_er> for the TX path
 * and <rx_avst_err> for the RX path).
 * Although jumbo frames typically contain up to 9000 bytes, the LLEMAC-1G can handle
 * an infinite frame size. The problem of jumbo frames is the necessary storage space in
 * transmission and reception buffers. LLEMAC-1G does not include storage buffers.
 * JUMBO can be activated or deactivated at any time. The new setting becomes valid
 * immediately after clock domain crossing.
 */
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_JUMBO_MASK (0x8U)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_JUMBO_SHIFT (3U)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_JUMBO_SET(x) (((uint32_t)(x) << TSW_TSNPORT_MAC_MAC_MAC_CTRL_JUMBO_SHIFT) & TSW_TSNPORT_MAC_MAC_MAC_CTRL_JUMBO_MASK)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_JUMBO_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_MAC_CTRL_JUMBO_MASK) >> TSW_TSNPORT_MAC_MAC_MAC_CTRL_JUMBO_SHIFT)

/*
 * TX_EN (R/W)
 *
 * TX path enable
 * 0 – transmission disabled - Avalon-ST READY for the TX path will be set to 0.
 * 1 – transmission enabled
 * TX_EN can be activated or deactivated at any time. Deactivation may take some time.
 * If during deactivation there is a frame in transmission, then this frame will be
 * completed fist. Afterwards bit TX_EN can be read as 0.
 * After the transmission is disabled there may be pending frames left, waiting at the TX
 * stream interface.
 */
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_TX_EN_MASK (0x4U)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_TX_EN_SHIFT (2U)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_TX_EN_SET(x) (((uint32_t)(x) << TSW_TSNPORT_MAC_MAC_MAC_CTRL_TX_EN_SHIFT) & TSW_TSNPORT_MAC_MAC_MAC_CTRL_TX_EN_MASK)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_TX_EN_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_MAC_CTRL_TX_EN_MASK) >> TSW_TSNPORT_MAC_MAC_MAC_CTRL_TX_EN_SHIFT)

/*
 * RX_EN (R/W)
 *
 * RX path enable
 * 0 – reception disabled – no frames fed to Avalon-ST RX path
 * 1 – reception enabled
 * RX_EN can be activated or deactivated at any time. Deactivation may take some time.
 * If during deactivation there is a frame in reception, then this frame will be completed
 * first. Afterwards bit RX_EN can be read as 0.
 */
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_RX_EN_MASK (0x2U)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_RX_EN_SHIFT (1U)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_RX_EN_SET(x) (((uint32_t)(x) << TSW_TSNPORT_MAC_MAC_MAC_CTRL_RX_EN_SHIFT) & TSW_TSNPORT_MAC_MAC_MAC_CTRL_RX_EN_MASK)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_RX_EN_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_MAC_CTRL_RX_EN_MASK) >> TSW_TSNPORT_MAC_MAC_MAC_CTRL_RX_EN_SHIFT)

/*
 * RESSTAT (R/W)
 *
 * Software reset of the statistic counters (see Table 3-8)
 * 0 – no reset
 * 1 – reset active
 * RESSTAT will be automatically set to 0 after the counters have been reset
 */
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_RESSTAT_MASK (0x1U)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_RESSTAT_SHIFT (0U)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_RESSTAT_SET(x) (((uint32_t)(x) << TSW_TSNPORT_MAC_MAC_MAC_CTRL_RESSTAT_SHIFT) & TSW_TSNPORT_MAC_MAC_MAC_CTRL_RESSTAT_MASK)
#define TSW_TSNPORT_MAC_MAC_MAC_CTRL_RESSTAT_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_MAC_CTRL_RESSTAT_MASK) >> TSW_TSNPORT_MAC_MAC_MAC_CTRL_RESSTAT_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: MAC_TX_FRAMES */
/*
 * TX_FRAMES (R)
 *
 * Number of successfully transmitted frames.
 */
#define TSW_TSNPORT_MAC_MAC_TX_FRAMES_TX_FRAMES_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_MAC_MAC_TX_FRAMES_TX_FRAMES_SHIFT (0U)
#define TSW_TSNPORT_MAC_MAC_TX_FRAMES_TX_FRAMES_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_TX_FRAMES_TX_FRAMES_MASK) >> TSW_TSNPORT_MAC_MAC_TX_FRAMES_TX_FRAMES_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: MAC_RX_FRAMES */
/*
 * RX_FRAMES (R)
 *
 * Number of successfully received frames.
 */
#define TSW_TSNPORT_MAC_MAC_RX_FRAMES_RX_FRAMES_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_MAC_MAC_RX_FRAMES_RX_FRAMES_SHIFT (0U)
#define TSW_TSNPORT_MAC_MAC_RX_FRAMES_RX_FRAMES_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_RX_FRAMES_RX_FRAMES_MASK) >> TSW_TSNPORT_MAC_MAC_RX_FRAMES_RX_FRAMES_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: MAC_TX_OCTETS */
/*
 * TX_OCTETS (R)
 *
 * Number of successfully transmitted payload and padding octets.
 */
#define TSW_TSNPORT_MAC_MAC_TX_OCTETS_TX_OCTETS_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_MAC_MAC_TX_OCTETS_TX_OCTETS_SHIFT (0U)
#define TSW_TSNPORT_MAC_MAC_TX_OCTETS_TX_OCTETS_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_TX_OCTETS_TX_OCTETS_MASK) >> TSW_TSNPORT_MAC_MAC_TX_OCTETS_TX_OCTETS_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: MAC_RX_OCTETS */
/*
 * RX_OCTETS (R)
 *
 * Number of successfully received payload and padding octets.
 */
#define TSW_TSNPORT_MAC_MAC_RX_OCTETS_RX_OCTETS_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_MAC_MAC_RX_OCTETS_RX_OCTETS_SHIFT (0U)
#define TSW_TSNPORT_MAC_MAC_RX_OCTETS_RX_OCTETS_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_RX_OCTETS_RX_OCTETS_MASK) >> TSW_TSNPORT_MAC_MAC_RX_OCTETS_RX_OCTETS_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: MAC_MDIO_CFG */
/*
 * NPRE (R/W)
 *
 * No Preamble
 * With NPRE=1 the preamble generation is suppressed and frames are initiated with
 * Start of Frame pattern directly. Suitable in case that all connected PHYs accept
 * management frames without a preamble pattern. Recommended to be used if only
 * one PHY is connected.
 */
#define TSW_TSNPORT_MAC_MAC_MDIO_CFG_NPRE_MASK (0x8000U)
#define TSW_TSNPORT_MAC_MAC_MDIO_CFG_NPRE_SHIFT (15U)
#define TSW_TSNPORT_MAC_MAC_MDIO_CFG_NPRE_SET(x) (((uint32_t)(x) << TSW_TSNPORT_MAC_MAC_MDIO_CFG_NPRE_SHIFT) & TSW_TSNPORT_MAC_MAC_MDIO_CFG_NPRE_MASK)
#define TSW_TSNPORT_MAC_MAC_MDIO_CFG_NPRE_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_MDIO_CFG_NPRE_MASK) >> TSW_TSNPORT_MAC_MAC_MDIO_CFG_NPRE_SHIFT)

/*
 * ENABLE (R/W)
 *
 * Enable the MDIO controller. If the controller is enabled then MDC will be toggled.
 * ENABLE can only be read as 1 if a valid MDC_CLKDIV value is set.
 */
#define TSW_TSNPORT_MAC_MAC_MDIO_CFG_ENABLE_MASK (0x100U)
#define TSW_TSNPORT_MAC_MAC_MDIO_CFG_ENABLE_SHIFT (8U)
#define TSW_TSNPORT_MAC_MAC_MDIO_CFG_ENABLE_SET(x) (((uint32_t)(x) << TSW_TSNPORT_MAC_MAC_MDIO_CFG_ENABLE_SHIFT) & TSW_TSNPORT_MAC_MAC_MDIO_CFG_ENABLE_MASK)
#define TSW_TSNPORT_MAC_MAC_MDIO_CFG_ENABLE_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_MDIO_CFG_ENABLE_MASK) >> TSW_TSNPORT_MAC_MAC_MDIO_CFG_ENABLE_SHIFT)

/*
 * MDC_CLKDIV (R/W)
 *
 * Clock Divider to configure MDC clock frequency. Refer to 10.1 Clock Divider for more
 * details.
 */
#define TSW_TSNPORT_MAC_MAC_MDIO_CFG_MDC_CLKDIV_MASK (0xFFU)
#define TSW_TSNPORT_MAC_MAC_MDIO_CFG_MDC_CLKDIV_SHIFT (0U)
#define TSW_TSNPORT_MAC_MAC_MDIO_CFG_MDC_CLKDIV_SET(x) (((uint32_t)(x) << TSW_TSNPORT_MAC_MAC_MDIO_CFG_MDC_CLKDIV_SHIFT) & TSW_TSNPORT_MAC_MAC_MDIO_CFG_MDC_CLKDIV_MASK)
#define TSW_TSNPORT_MAC_MAC_MDIO_CFG_MDC_CLKDIV_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_MDIO_CFG_MDC_CLKDIV_MASK) >> TSW_TSNPORT_MAC_MAC_MDIO_CFG_MDC_CLKDIV_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: MAC_MDIO_CTRL */
/*
 * OP (R/W)
 *
 * Opcode to determine transfer type
 * 01 – Write Access
 * 10 – Read Access
 */
#define TSW_TSNPORT_MAC_MAC_MDIO_CTRL_OP_MASK (0xC0000000UL)
#define TSW_TSNPORT_MAC_MAC_MDIO_CTRL_OP_SHIFT (30U)
#define TSW_TSNPORT_MAC_MAC_MDIO_CTRL_OP_SET(x) (((uint32_t)(x) << TSW_TSNPORT_MAC_MAC_MDIO_CTRL_OP_SHIFT) & TSW_TSNPORT_MAC_MAC_MDIO_CTRL_OP_MASK)
#define TSW_TSNPORT_MAC_MAC_MDIO_CTRL_OP_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_MDIO_CTRL_OP_MASK) >> TSW_TSNPORT_MAC_MAC_MDIO_CTRL_OP_SHIFT)

/*
 * PHYAD (R/W)
 *
 * Management Frame PHY Address.
 */
#define TSW_TSNPORT_MAC_MAC_MDIO_CTRL_PHYAD_MASK (0x1F000000UL)
#define TSW_TSNPORT_MAC_MAC_MDIO_CTRL_PHYAD_SHIFT (24U)
#define TSW_TSNPORT_MAC_MAC_MDIO_CTRL_PHYAD_SET(x) (((uint32_t)(x) << TSW_TSNPORT_MAC_MAC_MDIO_CTRL_PHYAD_SHIFT) & TSW_TSNPORT_MAC_MAC_MDIO_CTRL_PHYAD_MASK)
#define TSW_TSNPORT_MAC_MAC_MDIO_CTRL_PHYAD_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_MDIO_CTRL_PHYAD_MASK) >> TSW_TSNPORT_MAC_MAC_MDIO_CTRL_PHYAD_SHIFT)

/*
 * REGAD (R/W)
 *
 * Management Frame Register Address.
 */
#define TSW_TSNPORT_MAC_MAC_MDIO_CTRL_REGAD_MASK (0x1F0000UL)
#define TSW_TSNPORT_MAC_MAC_MDIO_CTRL_REGAD_SHIFT (16U)
#define TSW_TSNPORT_MAC_MAC_MDIO_CTRL_REGAD_SET(x) (((uint32_t)(x) << TSW_TSNPORT_MAC_MAC_MDIO_CTRL_REGAD_SHIFT) & TSW_TSNPORT_MAC_MAC_MDIO_CTRL_REGAD_MASK)
#define TSW_TSNPORT_MAC_MAC_MDIO_CTRL_REGAD_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_MDIO_CTRL_REGAD_MASK) >> TSW_TSNPORT_MAC_MAC_MDIO_CTRL_REGAD_SHIFT)

/*
 * INIT (R/W)
 *
 * INIT=1 results in a MDIO write/read transfer if READY=1. If READY=0 while a
 * transfer is already pending or if ENABLE=0 then settings INIT=1 has no effect and
 * the current transaction is withdrawn.
 */
#define TSW_TSNPORT_MAC_MAC_MDIO_CTRL_INIT_MASK (0x100U)
#define TSW_TSNPORT_MAC_MAC_MDIO_CTRL_INIT_SHIFT (8U)
#define TSW_TSNPORT_MAC_MAC_MDIO_CTRL_INIT_SET(x) (((uint32_t)(x) << TSW_TSNPORT_MAC_MAC_MDIO_CTRL_INIT_SHIFT) & TSW_TSNPORT_MAC_MAC_MDIO_CTRL_INIT_MASK)
#define TSW_TSNPORT_MAC_MAC_MDIO_CTRL_INIT_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_MDIO_CTRL_INIT_MASK) >> TSW_TSNPORT_MAC_MAC_MDIO_CTRL_INIT_SHIFT)

/*
 * READY (R)
 *
 * READY=1 indicates a finished transfer and also shows that the controller is ready for a
 * new transfer. READY=1 is only possible if ENABLE=1.
 * If READY=1 is signaled after a read transfer, then RD_DATA is valid until a new
 * transfer is started.
 */
#define TSW_TSNPORT_MAC_MAC_MDIO_CTRL_READY_MASK (0x1U)
#define TSW_TSNPORT_MAC_MAC_MDIO_CTRL_READY_SHIFT (0U)
#define TSW_TSNPORT_MAC_MAC_MDIO_CTRL_READY_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_MDIO_CTRL_READY_MASK) >> TSW_TSNPORT_MAC_MAC_MDIO_CTRL_READY_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: MAC_MDIO_RD_DATA */
/*
 * RD_DATA (R)
 *
 * Read Data is available if READY=1 after a transfer has been started. RD_DATA represents the content of the management data field of the read transfer.
 */
#define TSW_TSNPORT_MAC_MAC_MDIO_RD_DATA_RD_DATA_MASK (0xFFFFU)
#define TSW_TSNPORT_MAC_MAC_MDIO_RD_DATA_RD_DATA_SHIFT (0U)
#define TSW_TSNPORT_MAC_MAC_MDIO_RD_DATA_RD_DATA_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_MDIO_RD_DATA_RD_DATA_MASK) >> TSW_TSNPORT_MAC_MAC_MDIO_RD_DATA_RD_DATA_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: MAC_MDIO_WR_DATA */
/*
 * WR_DATA (R/W)
 *
 * Data is used for the management data field after a write transfer has been started
 */
#define TSW_TSNPORT_MAC_MAC_MDIO_WR_DATA_WR_DATA_MASK (0xFFFFU)
#define TSW_TSNPORT_MAC_MAC_MDIO_WR_DATA_WR_DATA_SHIFT (0U)
#define TSW_TSNPORT_MAC_MAC_MDIO_WR_DATA_WR_DATA_SET(x) (((uint32_t)(x) << TSW_TSNPORT_MAC_MAC_MDIO_WR_DATA_WR_DATA_SHIFT) & TSW_TSNPORT_MAC_MAC_MDIO_WR_DATA_WR_DATA_MASK)
#define TSW_TSNPORT_MAC_MAC_MDIO_WR_DATA_WR_DATA_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_MDIO_WR_DATA_WR_DATA_MASK) >> TSW_TSNPORT_MAC_MAC_MDIO_WR_DATA_WR_DATA_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: MAC_IRQ_CTRL */
/*
 * CAIF (R/W)
 *
 * Clock activity interrupt flag
 * 0 – no interrupt
 * 1 – interrupt pending
 * See Chapter 11.2.3 for details.
 */
#define TSW_TSNPORT_MAC_MAC_IRQ_CTRL_CAIF_MASK (0x800U)
#define TSW_TSNPORT_MAC_MAC_IRQ_CTRL_CAIF_SHIFT (11U)
#define TSW_TSNPORT_MAC_MAC_IRQ_CTRL_CAIF_SET(x) (((uint32_t)(x) << TSW_TSNPORT_MAC_MAC_IRQ_CTRL_CAIF_SHIFT) & TSW_TSNPORT_MAC_MAC_IRQ_CTRL_CAIF_MASK)
#define TSW_TSNPORT_MAC_MAC_IRQ_CTRL_CAIF_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_IRQ_CTRL_CAIF_MASK) >> TSW_TSNPORT_MAC_MAC_IRQ_CTRL_CAIF_SHIFT)

/*
 * SWIF (R/W)
 *
 * Safety warning interrupt flag
 * 0 – no interrupt
 * 1 – interrupt pending
 * See Chapter 11.2.2 for details
 */
#define TSW_TSNPORT_MAC_MAC_IRQ_CTRL_SWIF_MASK (0x400U)
#define TSW_TSNPORT_MAC_MAC_IRQ_CTRL_SWIF_SHIFT (10U)
#define TSW_TSNPORT_MAC_MAC_IRQ_CTRL_SWIF_SET(x) (((uint32_t)(x) << TSW_TSNPORT_MAC_MAC_IRQ_CTRL_SWIF_SHIFT) & TSW_TSNPORT_MAC_MAC_IRQ_CTRL_SWIF_MASK)
#define TSW_TSNPORT_MAC_MAC_IRQ_CTRL_SWIF_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_IRQ_CTRL_SWIF_MASK) >> TSW_TSNPORT_MAC_MAC_IRQ_CTRL_SWIF_SHIFT)

/*
 * SEIF (R/W)
 *
 * Safety Error Interrupt Flag
 * 0 – no interrupt
 * 1 – interrupt pending
 * If SEN=1 and if there is a mismatch between both instances of the logic core of
 * LLEMAC-1G then this results in SEIF=1, TX_EN=0 and RX_EN=0.
 */
#define TSW_TSNPORT_MAC_MAC_IRQ_CTRL_SEIF_MASK (0x200U)
#define TSW_TSNPORT_MAC_MAC_IRQ_CTRL_SEIF_SHIFT (9U)
#define TSW_TSNPORT_MAC_MAC_IRQ_CTRL_SEIF_SET(x) (((uint32_t)(x) << TSW_TSNPORT_MAC_MAC_IRQ_CTRL_SEIF_SHIFT) & TSW_TSNPORT_MAC_MAC_IRQ_CTRL_SEIF_MASK)
#define TSW_TSNPORT_MAC_MAC_IRQ_CTRL_SEIF_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_IRQ_CTRL_SEIF_MASK) >> TSW_TSNPORT_MAC_MAC_IRQ_CTRL_SEIF_SHIFT)

/*
 * MDIF (R/W)
 *
 * MDIO Interrupt Flag
 * 1 – A transfer has been finished
 * 0 – No transfer done
 */
#define TSW_TSNPORT_MAC_MAC_IRQ_CTRL_MDIF_MASK (0x100U)
#define TSW_TSNPORT_MAC_MAC_IRQ_CTRL_MDIF_SHIFT (8U)
#define TSW_TSNPORT_MAC_MAC_IRQ_CTRL_MDIF_SET(x) (((uint32_t)(x) << TSW_TSNPORT_MAC_MAC_IRQ_CTRL_MDIF_SHIFT) & TSW_TSNPORT_MAC_MAC_IRQ_CTRL_MDIF_MASK)
#define TSW_TSNPORT_MAC_MAC_IRQ_CTRL_MDIF_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_IRQ_CTRL_MDIF_MASK) >> TSW_TSNPORT_MAC_MAC_IRQ_CTRL_MDIF_SHIFT)

/*
 * CAIE (R/W)
 *
 * Clock activity interrupt enable
 * 0 – CAIF disabled
 * 1 – CAIF enabled
 */
#define TSW_TSNPORT_MAC_MAC_IRQ_CTRL_CAIE_MASK (0x8U)
#define TSW_TSNPORT_MAC_MAC_IRQ_CTRL_CAIE_SHIFT (3U)
#define TSW_TSNPORT_MAC_MAC_IRQ_CTRL_CAIE_SET(x) (((uint32_t)(x) << TSW_TSNPORT_MAC_MAC_IRQ_CTRL_CAIE_SHIFT) & TSW_TSNPORT_MAC_MAC_IRQ_CTRL_CAIE_MASK)
#define TSW_TSNPORT_MAC_MAC_IRQ_CTRL_CAIE_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_IRQ_CTRL_CAIE_MASK) >> TSW_TSNPORT_MAC_MAC_IRQ_CTRL_CAIE_SHIFT)

/*
 * SWIE (R/W)
 *
 * Safety warning interrupt enable
 * 0 – SWIF disabled
 * 1 – SWIF enabled
 */
#define TSW_TSNPORT_MAC_MAC_IRQ_CTRL_SWIE_MASK (0x4U)
#define TSW_TSNPORT_MAC_MAC_IRQ_CTRL_SWIE_SHIFT (2U)
#define TSW_TSNPORT_MAC_MAC_IRQ_CTRL_SWIE_SET(x) (((uint32_t)(x) << TSW_TSNPORT_MAC_MAC_IRQ_CTRL_SWIE_SHIFT) & TSW_TSNPORT_MAC_MAC_IRQ_CTRL_SWIE_MASK)
#define TSW_TSNPORT_MAC_MAC_IRQ_CTRL_SWIE_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_IRQ_CTRL_SWIE_MASK) >> TSW_TSNPORT_MAC_MAC_IRQ_CTRL_SWIE_SHIFT)

/*
 * MDIE (R/W)
 *
 * MDIO Interrupt Enable
 * 0 – Disabled
 * 1 – Enabled
 */
#define TSW_TSNPORT_MAC_MAC_IRQ_CTRL_MDIE_MASK (0x1U)
#define TSW_TSNPORT_MAC_MAC_IRQ_CTRL_MDIE_SHIFT (0U)
#define TSW_TSNPORT_MAC_MAC_IRQ_CTRL_MDIE_SET(x) (((uint32_t)(x) << TSW_TSNPORT_MAC_MAC_IRQ_CTRL_MDIE_SHIFT) & TSW_TSNPORT_MAC_MAC_IRQ_CTRL_MDIE_MASK)
#define TSW_TSNPORT_MAC_MAC_IRQ_CTRL_MDIE_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MAC_MAC_IRQ_CTRL_MDIE_MASK) >> TSW_TSNPORT_MAC_MAC_IRQ_CTRL_MDIE_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: RTC_CR */
/*
 * TAIE (R/W)
 *
 * Timer A interrupt enable: interrupt enabled when 1
 */
#define TSW_TSNPORT_RTC_CR_TAIE_MASK (0x8U)
#define TSW_TSNPORT_RTC_CR_TAIE_SHIFT (3U)
#define TSW_TSNPORT_RTC_CR_TAIE_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RTC_CR_TAIE_SHIFT) & TSW_TSNPORT_RTC_CR_TAIE_MASK)
#define TSW_TSNPORT_RTC_CR_TAIE_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RTC_CR_TAIE_MASK) >> TSW_TSNPORT_RTC_CR_TAIE_SHIFT)

/*
 * TAEN (R/W)
 *
 * Timer A enable: timer enabled when 1
 */
#define TSW_TSNPORT_RTC_CR_TAEN_MASK (0x4U)
#define TSW_TSNPORT_RTC_CR_TAEN_SHIFT (2U)
#define TSW_TSNPORT_RTC_CR_TAEN_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RTC_CR_TAEN_SHIFT) & TSW_TSNPORT_RTC_CR_TAEN_MASK)
#define TSW_TSNPORT_RTC_CR_TAEN_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RTC_CR_TAEN_MASK) >> TSW_TSNPORT_RTC_CR_TAEN_SHIFT)

/*
 * ALIE (R/W)
 *
 * Alarm interrupt enable: alarm interrupt enabled when 1
 */
#define TSW_TSNPORT_RTC_CR_ALIE_MASK (0x2U)
#define TSW_TSNPORT_RTC_CR_ALIE_SHIFT (1U)
#define TSW_TSNPORT_RTC_CR_ALIE_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RTC_CR_ALIE_SHIFT) & TSW_TSNPORT_RTC_CR_ALIE_MASK)
#define TSW_TSNPORT_RTC_CR_ALIE_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RTC_CR_ALIE_MASK) >> TSW_TSNPORT_RTC_CR_ALIE_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: RTC_SR */
/*
 * TAIS (R/WC)
 *
 * Timer A Interrupt Status: set at rising edge of “timer_clk_a”, write 1 to clear
 */
#define TSW_TSNPORT_RTC_SR_TAIS_MASK (0x8U)
#define TSW_TSNPORT_RTC_SR_TAIS_SHIFT (3U)
#define TSW_TSNPORT_RTC_SR_TAIS_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RTC_SR_TAIS_SHIFT) & TSW_TSNPORT_RTC_SR_TAIS_MASK)
#define TSW_TSNPORT_RTC_SR_TAIS_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RTC_SR_TAIS_MASK) >> TSW_TSNPORT_RTC_SR_TAIS_SHIFT)

/*
 * ALIS (RO)
 *
 * ALIS ro Alarm Interrupt Status: Always set while RTC-Time >= Alarm-Time
 */
#define TSW_TSNPORT_RTC_SR_ALIS_MASK (0x2U)
#define TSW_TSNPORT_RTC_SR_ALIS_SHIFT (1U)
#define TSW_TSNPORT_RTC_SR_ALIS_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RTC_SR_ALIS_MASK) >> TSW_TSNPORT_RTC_SR_ALIS_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: RTC_CT_CURTIME_NS */
/*
 * CT_NS (RO/WU)
 *
 * Local Time (nanosecond part): Update can be triggered by write access to this register. Value range from 0 – 999999999.
 */
#define TSW_TSNPORT_RTC_CT_CURTIME_NS_CT_NS_MASK (0x3FFFFFFFUL)
#define TSW_TSNPORT_RTC_CT_CURTIME_NS_CT_NS_SHIFT (0U)
#define TSW_TSNPORT_RTC_CT_CURTIME_NS_CT_NS_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RTC_CT_CURTIME_NS_CT_NS_SHIFT) & TSW_TSNPORT_RTC_CT_CURTIME_NS_CT_NS_MASK)
#define TSW_TSNPORT_RTC_CT_CURTIME_NS_CT_NS_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RTC_CT_CURTIME_NS_CT_NS_MASK) >> TSW_TSNPORT_RTC_CT_CURTIME_NS_CT_NS_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: RTC_CT_CURTIME_SEC */
/*
 * CT_SEC (RO)
 *
 * Current Time (second part): Update can be triggered by write access to register CURTIME_NS.
 */
#define TSW_TSNPORT_RTC_CT_CURTIME_SEC_CT_SEC_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_RTC_CT_CURTIME_SEC_CT_SEC_SHIFT (0U)
#define TSW_TSNPORT_RTC_CT_CURTIME_SEC_CT_SEC_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RTC_CT_CURTIME_SEC_CT_SEC_MASK) >> TSW_TSNPORT_RTC_CT_CURTIME_SEC_CT_SEC_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: RTC_CT_TIMER_INCR */
/*
 * NS (RW)
 *
 * Local time increment – nanoseconds (integer)
 */
#define TSW_TSNPORT_RTC_CT_TIMER_INCR_NS_MASK (0xFF000000UL)
#define TSW_TSNPORT_RTC_CT_TIMER_INCR_NS_SHIFT (24U)
#define TSW_TSNPORT_RTC_CT_TIMER_INCR_NS_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RTC_CT_TIMER_INCR_NS_SHIFT) & TSW_TSNPORT_RTC_CT_TIMER_INCR_NS_MASK)
#define TSW_TSNPORT_RTC_CT_TIMER_INCR_NS_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RTC_CT_TIMER_INCR_NS_MASK) >> TSW_TSNPORT_RTC_CT_TIMER_INCR_NS_SHIFT)

/*
 * FNS (RW)
 *
 * Local time increment – fractional ns, unsigned, in (1 / 2^24) n
 */
#define TSW_TSNPORT_RTC_CT_TIMER_INCR_FNS_MASK (0xFFFFFFUL)
#define TSW_TSNPORT_RTC_CT_TIMER_INCR_FNS_SHIFT (0U)
#define TSW_TSNPORT_RTC_CT_TIMER_INCR_FNS_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RTC_CT_TIMER_INCR_FNS_SHIFT) & TSW_TSNPORT_RTC_CT_TIMER_INCR_FNS_MASK)
#define TSW_TSNPORT_RTC_CT_TIMER_INCR_FNS_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RTC_CT_TIMER_INCR_FNS_MASK) >> TSW_TSNPORT_RTC_CT_TIMER_INCR_FNS_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: RTC_OFS_NS */
/*
 * OFS_NS (R/W)
 *
 * Real Time Offset (nanoseconds part). Valid value range from 0 – 999999999.
 */
#define TSW_TSNPORT_RTC_OFS_NS_OFS_NS_MASK (0x3FFFFFFFUL)
#define TSW_TSNPORT_RTC_OFS_NS_OFS_NS_SHIFT (0U)
#define TSW_TSNPORT_RTC_OFS_NS_OFS_NS_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RTC_OFS_NS_OFS_NS_SHIFT) & TSW_TSNPORT_RTC_OFS_NS_OFS_NS_MASK)
#define TSW_TSNPORT_RTC_OFS_NS_OFS_NS_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RTC_OFS_NS_OFS_NS_MASK) >> TSW_TSNPORT_RTC_OFS_NS_OFS_NS_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: RTC_OFS_SL */
/*
 * OFS_SL (R/W)
 *
 * 48 Bit Real Time Offset (seconds lo part)
 */
#define TSW_TSNPORT_RTC_OFS_SL_OFS_SL_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_RTC_OFS_SL_OFS_SL_SHIFT (0U)
#define TSW_TSNPORT_RTC_OFS_SL_OFS_SL_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RTC_OFS_SL_OFS_SL_SHIFT) & TSW_TSNPORT_RTC_OFS_SL_OFS_SL_MASK)
#define TSW_TSNPORT_RTC_OFS_SL_OFS_SL_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RTC_OFS_SL_OFS_SL_MASK) >> TSW_TSNPORT_RTC_OFS_SL_OFS_SL_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: RTC_OFS_SH */
/*
 * OFS_SH (R/W)
 *
 * 48 Bit Real Time Offset (seconds hi part)
 */
#define TSW_TSNPORT_RTC_OFS_SH_OFS_SH_MASK (0xFFFFU)
#define TSW_TSNPORT_RTC_OFS_SH_OFS_SH_SHIFT (0U)
#define TSW_TSNPORT_RTC_OFS_SH_OFS_SH_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RTC_OFS_SH_OFS_SH_SHIFT) & TSW_TSNPORT_RTC_OFS_SH_OFS_SH_MASK)
#define TSW_TSNPORT_RTC_OFS_SH_OFS_SH_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RTC_OFS_SH_OFS_SH_MASK) >> TSW_TSNPORT_RTC_OFS_SH_OFS_SH_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: RTC_OFS_CH */
/*
 * SEXT (RO)
 *
 * Real Time Offset Change – sign extension of SFNS (Bit 23)
 */
#define TSW_TSNPORT_RTC_OFS_CH_SEXT_MASK (0xFF000000UL)
#define TSW_TSNPORT_RTC_OFS_CH_SEXT_SHIFT (24U)
#define TSW_TSNPORT_RTC_OFS_CH_SEXT_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RTC_OFS_CH_SEXT_MASK) >> TSW_TSNPORT_RTC_OFS_CH_SEXT_SHIFT)

/*
 * SFNS (R/W)
 *
 * Real Time Offset Change in fractional nanoseconds, signed value; value range from -2^23 / 2^24 to (2^23-1) / 2^24 nanoseconds.
 */
#define TSW_TSNPORT_RTC_OFS_CH_SFNS_MASK (0xFFFFFFUL)
#define TSW_TSNPORT_RTC_OFS_CH_SFNS_SHIFT (0U)
#define TSW_TSNPORT_RTC_OFS_CH_SFNS_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RTC_OFS_CH_SFNS_SHIFT) & TSW_TSNPORT_RTC_OFS_CH_SFNS_MASK)
#define TSW_TSNPORT_RTC_OFS_CH_SFNS_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RTC_OFS_CH_SFNS_MASK) >> TSW_TSNPORT_RTC_OFS_CH_SFNS_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: RTC_ALARM_NS */
/*
 * AL_NS (R/W)
 *
 * Alarm Time (nanoseconds part). Valid value range from 0 – 999999999.
 */
#define TSW_TSNPORT_RTC_ALARM_NS_AL_NS_MASK (0x3FFFFFFFUL)
#define TSW_TSNPORT_RTC_ALARM_NS_AL_NS_SHIFT (0U)
#define TSW_TSNPORT_RTC_ALARM_NS_AL_NS_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RTC_ALARM_NS_AL_NS_SHIFT) & TSW_TSNPORT_RTC_ALARM_NS_AL_NS_MASK)
#define TSW_TSNPORT_RTC_ALARM_NS_AL_NS_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RTC_ALARM_NS_AL_NS_MASK) >> TSW_TSNPORT_RTC_ALARM_NS_AL_NS_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: RTC_ALARM_SL */
/*
 * AL_SL (R/W)
 *
 * Alarm Time (seconds lo part)
 */
#define TSW_TSNPORT_RTC_ALARM_SL_AL_SL_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_RTC_ALARM_SL_AL_SL_SHIFT (0U)
#define TSW_TSNPORT_RTC_ALARM_SL_AL_SL_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RTC_ALARM_SL_AL_SL_SHIFT) & TSW_TSNPORT_RTC_ALARM_SL_AL_SL_MASK)
#define TSW_TSNPORT_RTC_ALARM_SL_AL_SL_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RTC_ALARM_SL_AL_SL_MASK) >> TSW_TSNPORT_RTC_ALARM_SL_AL_SL_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: RTC_ALARM_SH */
/*
 * AL_SH (R/W)
 *
 * Alarm Time (seconds hi part)
 */
#define TSW_TSNPORT_RTC_ALARM_SH_AL_SH_MASK (0xFFFFU)
#define TSW_TSNPORT_RTC_ALARM_SH_AL_SH_SHIFT (0U)
#define TSW_TSNPORT_RTC_ALARM_SH_AL_SH_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RTC_ALARM_SH_AL_SH_SHIFT) & TSW_TSNPORT_RTC_ALARM_SH_AL_SH_MASK)
#define TSW_TSNPORT_RTC_ALARM_SH_AL_SH_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RTC_ALARM_SH_AL_SH_MASK) >> TSW_TSNPORT_RTC_ALARM_SH_AL_SH_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: RTC_TIMER_A_PERIOD */
/*
 * PERIOD_NS (R/W)
 *
 * Timer A Period in ns. This is the period of the timer until the next event, but the half-period of the signal “timer_a_clk”.
 */
#define TSW_TSNPORT_RTC_TIMER_A_PERIOD_PERIOD_NS_MASK (0x1FFFFFFFUL)
#define TSW_TSNPORT_RTC_TIMER_A_PERIOD_PERIOD_NS_SHIFT (0U)
#define TSW_TSNPORT_RTC_TIMER_A_PERIOD_PERIOD_NS_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RTC_TIMER_A_PERIOD_PERIOD_NS_SHIFT) & TSW_TSNPORT_RTC_TIMER_A_PERIOD_PERIOD_NS_MASK)
#define TSW_TSNPORT_RTC_TIMER_A_PERIOD_PERIOD_NS_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RTC_TIMER_A_PERIOD_PERIOD_NS_MASK) >> TSW_TSNPORT_RTC_TIMER_A_PERIOD_PERIOD_NS_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSYN_CR */
/*
 * TMR_ALD (R/W)
 *
 * Timer Auto Load: automatic reloading of timer when reaching 0. Done flag stays set after countdown. Used for periodic events, when following event shall not be delayed by host interaction.
 */
#define TSW_TSNPORT_TSYN_CR_TMR_ALD_MASK (0x1F0000UL)
#define TSW_TSNPORT_TSYN_CR_TMR_ALD_SHIFT (16U)
#define TSW_TSNPORT_TSYN_CR_TMR_ALD_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TSYN_CR_TMR_ALD_SHIFT) & TSW_TSNPORT_TSYN_CR_TMR_ALD_MASK)
#define TSW_TSNPORT_TSYN_CR_TMR_ALD_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSYN_CR_TMR_ALD_MASK) >> TSW_TSNPORT_TSYN_CR_TMR_ALD_SHIFT)

/*
 * TMR_EN (R/W)
 *
 * Timer Enable: every bit corresponds to Timer 0 – 4
 */
#define TSW_TSNPORT_TSYN_CR_TMR_EN_MASK (0x1F00U)
#define TSW_TSNPORT_TSYN_CR_TMR_EN_SHIFT (8U)
#define TSW_TSNPORT_TSYN_CR_TMR_EN_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TSYN_CR_TMR_EN_SHIFT) & TSW_TSNPORT_TSYN_CR_TMR_EN_MASK)
#define TSW_TSNPORT_TSYN_CR_TMR_EN_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSYN_CR_TMR_EN_MASK) >> TSW_TSNPORT_TSYN_CR_TMR_EN_SHIFT)

/*
 * TMRIE (R/W)
 *
 * Timer Interrupt Enable
 */
#define TSW_TSNPORT_TSYN_CR_TMRIE_MASK (0x4U)
#define TSW_TSNPORT_TSYN_CR_TMRIE_SHIFT (2U)
#define TSW_TSNPORT_TSYN_CR_TMRIE_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TSYN_CR_TMRIE_SHIFT) & TSW_TSNPORT_TSYN_CR_TMRIE_MASK)
#define TSW_TSNPORT_TSYN_CR_TMRIE_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSYN_CR_TMRIE_MASK) >> TSW_TSNPORT_TSYN_CR_TMRIE_SHIFT)

/*
 * RXIE (R/W)
 *
 * Rx Interrupt Enable
 */
#define TSW_TSNPORT_TSYN_CR_RXIE_MASK (0x2U)
#define TSW_TSNPORT_TSYN_CR_RXIE_SHIFT (1U)
#define TSW_TSNPORT_TSYN_CR_RXIE_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TSYN_CR_RXIE_SHIFT) & TSW_TSNPORT_TSYN_CR_RXIE_MASK)
#define TSW_TSNPORT_TSYN_CR_RXIE_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSYN_CR_RXIE_MASK) >> TSW_TSNPORT_TSYN_CR_RXIE_SHIFT)

/*
 * TXIE (R/W)
 *
 * Tx Interrupt Enable
 */
#define TSW_TSNPORT_TSYN_CR_TXIE_MASK (0x1U)
#define TSW_TSNPORT_TSYN_CR_TXIE_SHIFT (0U)
#define TSW_TSNPORT_TSYN_CR_TXIE_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TSYN_CR_TXIE_SHIFT) & TSW_TSNPORT_TSYN_CR_TXIE_MASK)
#define TSW_TSNPORT_TSYN_CR_TXIE_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSYN_CR_TXIE_MASK) >> TSW_TSNPORT_TSYN_CR_TXIE_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSYN_SR */
/*
 * TMR_DN (R/WC)
 *
 * Timer Done: 1 when timer reached 0
 */
#define TSW_TSNPORT_TSYN_SR_TMR_DN_MASK (0x1F00U)
#define TSW_TSNPORT_TSYN_SR_TMR_DN_SHIFT (8U)
#define TSW_TSNPORT_TSYN_SR_TMR_DN_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TSYN_SR_TMR_DN_SHIFT) & TSW_TSNPORT_TSYN_SR_TMR_DN_MASK)
#define TSW_TSNPORT_TSYN_SR_TMR_DN_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSYN_SR_TMR_DN_MASK) >> TSW_TSNPORT_TSYN_SR_TMR_DN_SHIFT)

/*
 * TMRIS (RO)
 *
 * Timer Interrupt Status: OR’ed (TMR_DN AND TMR_EN) flags. 1 when timer is enabled and countdown is done
 */
#define TSW_TSNPORT_TSYN_SR_TMRIS_MASK (0x4U)
#define TSW_TSNPORT_TSYN_SR_TMRIS_SHIFT (2U)
#define TSW_TSNPORT_TSYN_SR_TMRIS_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSYN_SR_TMRIS_MASK) >> TSW_TSNPORT_TSYN_SR_TMRIS_SHIFT)

/*
 * RXIS (RO)
 *
 * Rx Interrupt Status, RX buffer data available equal to PTP_RX_STS.AV)
 */
#define TSW_TSNPORT_TSYN_SR_RXIS_MASK (0x2U)
#define TSW_TSNPORT_TSYN_SR_RXIS_SHIFT (1U)
#define TSW_TSNPORT_TSYN_SR_RXIS_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSYN_SR_RXIS_MASK) >> TSW_TSNPORT_TSYN_SR_RXIS_SHIFT)

/*
 * TXIS (RO)
 *
 * Tx Done Interrupt Status: OR’ed PTP_TX_DONE
 */
#define TSW_TSNPORT_TSYN_SR_TXIS_MASK (0x1U)
#define TSW_TSNPORT_TSYN_SR_TXIS_SHIFT (0U)
#define TSW_TSNPORT_TSYN_SR_TXIS_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSYN_SR_TXIS_MASK) >> TSW_TSNPORT_TSYN_SR_TXIS_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSYN_PTP_TX_STS */
/*
 * STS (RO)
 *
 * Transmission status of PTP TX bin n (bit 0 – 7 correspond to tx bin 0 – 7). 1: transmission pending
 */
#define TSW_TSNPORT_TSYN_PTP_TX_STS_STS_MASK (0xFFU)
#define TSW_TSNPORT_TSYN_PTP_TX_STS_STS_SHIFT (0U)
#define TSW_TSNPORT_TSYN_PTP_TX_STS_STS_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSYN_PTP_TX_STS_STS_MASK) >> TSW_TSNPORT_TSYN_PTP_TX_STS_STS_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSYN_PTP_TX_DONE */
/*
 * DONE (R/WC)
 *
 * Transmission done status of PTP TX bin n (bit 0 – 7 correspond to tx bin 0 – 7). 1: transmission done.
 * Writing a ‘1’ clears corresponding bit..
 */
#define TSW_TSNPORT_TSYN_PTP_TX_DONE_DONE_MASK (0xFFU)
#define TSW_TSNPORT_TSYN_PTP_TX_DONE_DONE_SHIFT (0U)
#define TSW_TSNPORT_TSYN_PTP_TX_DONE_DONE_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TSYN_PTP_TX_DONE_DONE_SHIFT) & TSW_TSNPORT_TSYN_PTP_TX_DONE_DONE_MASK)
#define TSW_TSNPORT_TSYN_PTP_TX_DONE_DONE_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSYN_PTP_TX_DONE_DONE_MASK) >> TSW_TSNPORT_TSYN_PTP_TX_DONE_DONE_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSYN_PTP_TX_TRIG */
/*
 * TRIG (WO)
 *
 * Trigger PTP TX bin n (bit 0 – 7 correspond to tx bin 0 –7). Writing ‘1’ will trigger transmission. Corresponding bit PTP_TX_STS.STS(n) will be set immediately.
 */
#define TSW_TSNPORT_TSYN_PTP_TX_TRIG_TRIG_MASK (0xFFU)
#define TSW_TSNPORT_TSYN_PTP_TX_TRIG_TRIG_SHIFT (0U)
#define TSW_TSNPORT_TSYN_PTP_TX_TRIG_TRIG_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TSYN_PTP_TX_TRIG_TRIG_SHIFT) & TSW_TSNPORT_TSYN_PTP_TX_TRIG_TRIG_MASK)
#define TSW_TSNPORT_TSYN_PTP_TX_TRIG_TRIG_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSYN_PTP_TX_TRIG_TRIG_MASK) >> TSW_TSNPORT_TSYN_PTP_TX_TRIG_TRIG_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSYN_PTP_RX_STS */
/*
 * OV (R/WC)
 *
 * FIFO overflow flag. PTP frame has been received and there was no free buffer available. Data has been lost.
 */
#define TSW_TSNPORT_TSYN_PTP_RX_STS_OV_MASK (0x80000000UL)
#define TSW_TSNPORT_TSYN_PTP_RX_STS_OV_SHIFT (31U)
#define TSW_TSNPORT_TSYN_PTP_RX_STS_OV_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TSYN_PTP_RX_STS_OV_SHIFT) & TSW_TSNPORT_TSYN_PTP_RX_STS_OV_MASK)
#define TSW_TSNPORT_TSYN_PTP_RX_STS_OV_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSYN_PTP_RX_STS_OV_MASK) >> TSW_TSNPORT_TSYN_PTP_RX_STS_OV_SHIFT)

/*
 * AV_NXT (R/W)
 *
 * Read access: buffer data available – reading data from RX_BUF is valid.
 * Write access: switch to next RX buffer – shall only be done when buffer not empty (AV=1). Use field RX_SEL as indication when rx buffer switch has been done.
 */
#define TSW_TSNPORT_TSYN_PTP_RX_STS_AV_NXT_MASK (0x40000000UL)
#define TSW_TSNPORT_TSYN_PTP_RX_STS_AV_NXT_SHIFT (30U)
#define TSW_TSNPORT_TSYN_PTP_RX_STS_AV_NXT_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TSYN_PTP_RX_STS_AV_NXT_SHIFT) & TSW_TSNPORT_TSYN_PTP_RX_STS_AV_NXT_MASK)
#define TSW_TSNPORT_TSYN_PTP_RX_STS_AV_NXT_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSYN_PTP_RX_STS_AV_NXT_MASK) >> TSW_TSNPORT_TSYN_PTP_RX_STS_AV_NXT_SHIFT)

/*
 * RX_SEL (RO)
 *
 * Current selected RX buffer for reading (0-7). Can be used to determine when RX buffer has been switched after setting PTP_RX_STS.NXT
 */
#define TSW_TSNPORT_TSYN_PTP_RX_STS_RX_SEL_MASK (0x7U)
#define TSW_TSNPORT_TSYN_PTP_RX_STS_RX_SEL_SHIFT (0U)
#define TSW_TSNPORT_TSYN_PTP_RX_STS_RX_SEL_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSYN_PTP_RX_STS_RX_SEL_MASK) >> TSW_TSNPORT_TSYN_PTP_RX_STS_RX_SEL_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSYN_TMR0 */
/*
 * PERIOD (R/W)
 *
 * Period in ticks, ticks based on register HCLKDIV and host clock <sys_clk>.
 */
#define TSW_TSNPORT_TSYNTMR_PERIOD_MASK (0xFFFFFUL)
#define TSW_TSNPORT_TSYNTMR_PERIOD_SHIFT (0U)
#define TSW_TSNPORT_TSYNTMR_PERIOD_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TSYNTMR_PERIOD_SHIFT) & TSW_TSNPORT_TSYNTMR_PERIOD_MASK)
#define TSW_TSNPORT_TSYNTMR_PERIOD_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSYNTMR_PERIOD_MASK) >> TSW_TSNPORT_TSYNTMR_PERIOD_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSYN_HCLKDIV */
/*
 * PERIOD (R/W)
 *
 * Period in host clocks <sys_clk>. Host clock shall be scaled to ticks of 1/1024th second. Ticks are used by timer TMR0 – TMR4.
 */
#define TSW_TSNPORT_TSYN_HCLKDIV_PERIOD_MASK (0xFFFFFUL)
#define TSW_TSNPORT_TSYN_HCLKDIV_PERIOD_SHIFT (0U)
#define TSW_TSNPORT_TSYN_HCLKDIV_PERIOD_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TSYN_HCLKDIV_PERIOD_SHIFT) & TSW_TSNPORT_TSYN_HCLKDIV_PERIOD_MASK)
#define TSW_TSNPORT_TSYN_HCLKDIV_PERIOD_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSYN_HCLKDIV_PERIOD_MASK) >> TSW_TSNPORT_TSYN_HCLKDIV_PERIOD_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSYN_RXBUF_RX_FRAME_LENGTH_BYTES */
/*
 * RX_FRAME_LENGTH_BYTES (RO)
 *
 * RX frame length bytes [11:0]
 */
#define TSW_TSNPORT_TSYN_RXBUF_RX_FRAME_LENGTH_BYTES_RX_FRAME_LENGTH_BYTES_MASK (0xFFFU)
#define TSW_TSNPORT_TSYN_RXBUF_RX_FRAME_LENGTH_BYTES_RX_FRAME_LENGTH_BYTES_SHIFT (0U)
#define TSW_TSNPORT_TSYN_RXBUF_RX_FRAME_LENGTH_BYTES_RX_FRAME_LENGTH_BYTES_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSYN_RXBUF_RX_FRAME_LENGTH_BYTES_RX_FRAME_LENGTH_BYTES_MASK) >> TSW_TSNPORT_TSYN_RXBUF_RX_FRAME_LENGTH_BYTES_RX_FRAME_LENGTH_BYTES_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSYN_RXBUF_RX_TIME_STAMP_L */
/*
 * RX_TIMESTAMP_LOW (RO)
 *
 * RX Timestamp [31:0]
 */
#define TSW_TSNPORT_TSYN_RXBUF_RX_TIME_STAMP_L_RX_TIMESTAMP_LOW_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_TSYN_RXBUF_RX_TIME_STAMP_L_RX_TIMESTAMP_LOW_SHIFT (0U)
#define TSW_TSNPORT_TSYN_RXBUF_RX_TIME_STAMP_L_RX_TIMESTAMP_LOW_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSYN_RXBUF_RX_TIME_STAMP_L_RX_TIMESTAMP_LOW_MASK) >> TSW_TSNPORT_TSYN_RXBUF_RX_TIME_STAMP_L_RX_TIMESTAMP_LOW_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSYN_RXBUF_RX_TIME_STAMP_H */
/*
 * RX_TIMESTAMP_HIGH (RO)
 *
 * RX Timestamp [63:32]
 */
#define TSW_TSNPORT_TSYN_RXBUF_RX_TIME_STAMP_H_RX_TIMESTAMP_HIGH_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_TSYN_RXBUF_RX_TIME_STAMP_H_RX_TIMESTAMP_HIGH_SHIFT (0U)
#define TSW_TSNPORT_TSYN_RXBUF_RX_TIME_STAMP_H_RX_TIMESTAMP_HIGH_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSYN_RXBUF_RX_TIME_STAMP_H_RX_TIMESTAMP_HIGH_MASK) >> TSW_TSNPORT_TSYN_RXBUF_RX_TIME_STAMP_H_RX_TIMESTAMP_HIGH_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSYN_RXBUF_DATA_WORD0 */
/*
 * RXBUF_DATA_WORD (RO)
 *
 * RXBUF_DATA_WORD
 */
#define TSW_TSNPORT_RXDATA_RXBUF_DATA_WORD_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_RXDATA_RXBUF_DATA_WORD_SHIFT (0U)
#define TSW_TSNPORT_RXDATA_RXBUF_DATA_WORD_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RXDATA_RXBUF_DATA_WORD_MASK) >> TSW_TSNPORT_RXDATA_RXBUF_DATA_WORD_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSYN_TXBUF_BIN0_DATA_WORD0 */
/*
 * TXBUF_BIN0_DATA_WORD0 (WO/RO)
 *
 * TXBUF_BIN0_DATA_WORD0
 */
#define TSW_TSNPORT_BIN_TXDATA_TXBUF_BIN0_DATA_WORD0_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_BIN_TXDATA_TXBUF_BIN0_DATA_WORD0_SHIFT (0U)
#define TSW_TSNPORT_BIN_TXDATA_TXBUF_BIN0_DATA_WORD0_SET(x) (((uint32_t)(x) << TSW_TSNPORT_BIN_TXDATA_TXBUF_BIN0_DATA_WORD0_SHIFT) & TSW_TSNPORT_BIN_TXDATA_TXBUF_BIN0_DATA_WORD0_MASK)
#define TSW_TSNPORT_BIN_TXDATA_TXBUF_BIN0_DATA_WORD0_GET(x) (((uint32_t)(x) & TSW_TSNPORT_BIN_TXDATA_TXBUF_BIN0_DATA_WORD0_MASK) >> TSW_TSNPORT_BIN_TXDATA_TXBUF_BIN0_DATA_WORD0_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSYN_TXBUF_BIN0_TQUE_AND_TX_LEN */
/*
 * TXBUF_BIN0_TQUE (WO/RO)
 *
 * TXBUF_BIN0_TQUE
 */
#define TSW_TSNPORT_BIN_TSYN_TXBUF_BIN0_TQUE_AND_TX_LEN_TXBUF_BIN0_TQUE_MASK (0x7000000UL)
#define TSW_TSNPORT_BIN_TSYN_TXBUF_BIN0_TQUE_AND_TX_LEN_TXBUF_BIN0_TQUE_SHIFT (24U)
#define TSW_TSNPORT_BIN_TSYN_TXBUF_BIN0_TQUE_AND_TX_LEN_TXBUF_BIN0_TQUE_SET(x) (((uint32_t)(x) << TSW_TSNPORT_BIN_TSYN_TXBUF_BIN0_TQUE_AND_TX_LEN_TXBUF_BIN0_TQUE_SHIFT) & TSW_TSNPORT_BIN_TSYN_TXBUF_BIN0_TQUE_AND_TX_LEN_TXBUF_BIN0_TQUE_MASK)
#define TSW_TSNPORT_BIN_TSYN_TXBUF_BIN0_TQUE_AND_TX_LEN_TXBUF_BIN0_TQUE_GET(x) (((uint32_t)(x) & TSW_TSNPORT_BIN_TSYN_TXBUF_BIN0_TQUE_AND_TX_LEN_TXBUF_BIN0_TQUE_MASK) >> TSW_TSNPORT_BIN_TSYN_TXBUF_BIN0_TQUE_AND_TX_LEN_TXBUF_BIN0_TQUE_SHIFT)

/*
 * TXBUF_BIN0_TX_LEN (WO/RO)
 *
 * TXBUF_BIN0_TX_LEN
 */
#define TSW_TSNPORT_BIN_TSYN_TXBUF_BIN0_TQUE_AND_TX_LEN_TXBUF_BIN0_TX_LEN_MASK (0xFFU)
#define TSW_TSNPORT_BIN_TSYN_TXBUF_BIN0_TQUE_AND_TX_LEN_TXBUF_BIN0_TX_LEN_SHIFT (0U)
#define TSW_TSNPORT_BIN_TSYN_TXBUF_BIN0_TQUE_AND_TX_LEN_TXBUF_BIN0_TX_LEN_SET(x) (((uint32_t)(x) << TSW_TSNPORT_BIN_TSYN_TXBUF_BIN0_TQUE_AND_TX_LEN_TXBUF_BIN0_TX_LEN_SHIFT) & TSW_TSNPORT_BIN_TSYN_TXBUF_BIN0_TQUE_AND_TX_LEN_TXBUF_BIN0_TX_LEN_MASK)
#define TSW_TSNPORT_BIN_TSYN_TXBUF_BIN0_TQUE_AND_TX_LEN_TXBUF_BIN0_TX_LEN_GET(x) (((uint32_t)(x) & TSW_TSNPORT_BIN_TSYN_TXBUF_BIN0_TQUE_AND_TX_LEN_TXBUF_BIN0_TX_LEN_MASK) >> TSW_TSNPORT_BIN_TSYN_TXBUF_BIN0_TQUE_AND_TX_LEN_TXBUF_BIN0_TX_LEN_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSYN_TXBUF_BIN0_TX_TIMESTAMP_L */
/*
 * TXBUF_BIN0_TX_TIMESTAMP_L (WO/RO)
 *
 * TXBUF_BIN0_TX_TIMESTAMP_L
 */
#define TSW_TSNPORT_BIN_TSYN_TXBUF_BIN0_TX_TIMESTAMP_L_TXBUF_BIN0_TX_TIMESTAMP_L_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_BIN_TSYN_TXBUF_BIN0_TX_TIMESTAMP_L_TXBUF_BIN0_TX_TIMESTAMP_L_SHIFT (0U)
#define TSW_TSNPORT_BIN_TSYN_TXBUF_BIN0_TX_TIMESTAMP_L_TXBUF_BIN0_TX_TIMESTAMP_L_SET(x) (((uint32_t)(x) << TSW_TSNPORT_BIN_TSYN_TXBUF_BIN0_TX_TIMESTAMP_L_TXBUF_BIN0_TX_TIMESTAMP_L_SHIFT) & TSW_TSNPORT_BIN_TSYN_TXBUF_BIN0_TX_TIMESTAMP_L_TXBUF_BIN0_TX_TIMESTAMP_L_MASK)
#define TSW_TSNPORT_BIN_TSYN_TXBUF_BIN0_TX_TIMESTAMP_L_TXBUF_BIN0_TX_TIMESTAMP_L_GET(x) (((uint32_t)(x) & TSW_TSNPORT_BIN_TSYN_TXBUF_BIN0_TX_TIMESTAMP_L_TXBUF_BIN0_TX_TIMESTAMP_L_MASK) >> TSW_TSNPORT_BIN_TSYN_TXBUF_BIN0_TX_TIMESTAMP_L_TXBUF_BIN0_TX_TIMESTAMP_L_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSYN_TXBUF_BIN0_TX_TIMESTAMP_H */
/*
 * TXBUF_BIN0_TX_TIMESTAMP_H (WO/RO)
 *
 * TXBUF_BIN0TX_TIMESTAMP_H
 */
#define TSW_TSNPORT_BIN_TSYN_TXBUF_BIN0_TX_TIMESTAMP_H_TXBUF_BIN0_TX_TIMESTAMP_H_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_BIN_TSYN_TXBUF_BIN0_TX_TIMESTAMP_H_TXBUF_BIN0_TX_TIMESTAMP_H_SHIFT (0U)
#define TSW_TSNPORT_BIN_TSYN_TXBUF_BIN0_TX_TIMESTAMP_H_TXBUF_BIN0_TX_TIMESTAMP_H_SET(x) (((uint32_t)(x) << TSW_TSNPORT_BIN_TSYN_TXBUF_BIN0_TX_TIMESTAMP_H_TXBUF_BIN0_TX_TIMESTAMP_H_SHIFT) & TSW_TSNPORT_BIN_TSYN_TXBUF_BIN0_TX_TIMESTAMP_H_TXBUF_BIN0_TX_TIMESTAMP_H_MASK)
#define TSW_TSNPORT_BIN_TSYN_TXBUF_BIN0_TX_TIMESTAMP_H_TXBUF_BIN0_TX_TIMESTAMP_H_GET(x) (((uint32_t)(x) & TSW_TSNPORT_BIN_TSYN_TXBUF_BIN0_TX_TIMESTAMP_H_TXBUF_BIN0_TX_TIMESTAMP_H_MASK) >> TSW_TSNPORT_BIN_TSYN_TXBUF_BIN0_TX_TIMESTAMP_H_TXBUF_BIN0_TX_TIMESTAMP_H_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSN_SHAPER_HWCFG1 */
/*
 * LWIDTH (RO)
 *
 * Scheduler list address width (IP core parameter LWIDTH)
 */
#define TSW_TSNPORT_TSN_SHAPER_HWCFG1_LWIDTH_MASK (0xFF000000UL)
#define TSW_TSNPORT_TSN_SHAPER_HWCFG1_LWIDTH_SHIFT (24U)
#define TSW_TSNPORT_TSN_SHAPER_HWCFG1_LWIDTH_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_SHAPER_HWCFG1_LWIDTH_MASK) >> TSW_TSNPORT_TSN_SHAPER_HWCFG1_LWIDTH_SHIFT)

/*
 * TQC (RO)
 *
 * Traffic queue count (IP core parameter TQC)
 */
#define TSW_TSNPORT_TSN_SHAPER_HWCFG1_TQC_MASK (0xFF0000UL)
#define TSW_TSNPORT_TSN_SHAPER_HWCFG1_TQC_SHIFT (16U)
#define TSW_TSNPORT_TSN_SHAPER_HWCFG1_TQC_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_SHAPER_HWCFG1_TQC_MASK) >> TSW_TSNPORT_TSN_SHAPER_HWCFG1_TQC_SHIFT)

/*
 * TQD (RO)
 *
 * Traffic queue depth (IP core parameter TQD)
 */
#define TSW_TSNPORT_TSN_SHAPER_HWCFG1_TQD_MASK (0xFF00U)
#define TSW_TSNPORT_TSN_SHAPER_HWCFG1_TQD_SHIFT (8U)
#define TSW_TSNPORT_TSN_SHAPER_HWCFG1_TQD_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_SHAPER_HWCFG1_TQD_MASK) >> TSW_TSNPORT_TSN_SHAPER_HWCFG1_TQD_SHIFT)

/*
 * DW (RO)
 *
 * Traffic queue data width (Bytes); fixed to value 4 within
 * IP core
 */
#define TSW_TSNPORT_TSN_SHAPER_HWCFG1_DW_MASK (0xFFU)
#define TSW_TSNPORT_TSN_SHAPER_HWCFG1_DW_SHIFT (0U)
#define TSW_TSNPORT_TSN_SHAPER_HWCFG1_DW_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_SHAPER_HWCFG1_DW_MASK) >> TSW_TSNPORT_TSN_SHAPER_HWCFG1_DW_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSN_SHAPER_TQAV */
/*
 * AVIE (R/W)
 *
 * Traffic queue interrupt enable on buffer space available,
 * one bit per traffic queue
 * Bit[i] = 0: no interrupt
 * Bit[i] = 1: interrupt, when AVAIL[i]=1
 */
#define TSW_TSNPORT_TSN_SHAPER_TQAV_AVIE_MASK (0xFF00U)
#define TSW_TSNPORT_TSN_SHAPER_TQAV_AVIE_SHIFT (8U)
#define TSW_TSNPORT_TSN_SHAPER_TQAV_AVIE_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TSN_SHAPER_TQAV_AVIE_SHIFT) & TSW_TSNPORT_TSN_SHAPER_TQAV_AVIE_MASK)
#define TSW_TSNPORT_TSN_SHAPER_TQAV_AVIE_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_SHAPER_TQAV_AVIE_MASK) >> TSW_TSNPORT_TSN_SHAPER_TQAV_AVIE_SHIFT)

/*
 * AVAIL (RO)
 *
 * Traffic queue buffer space available for complete packet of size MaxSDU (register MXSDUi)
 * Bit[i] = 1: space available
 * Bit[i] = 0: no space available or TQ not implemented (I >= TQC)
 */
#define TSW_TSNPORT_TSN_SHAPER_TQAV_AVAIL_MASK (0xFFU)
#define TSW_TSNPORT_TSN_SHAPER_TQAV_AVAIL_SHIFT (0U)
#define TSW_TSNPORT_TSN_SHAPER_TQAV_AVAIL_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_SHAPER_TQAV_AVAIL_MASK) >> TSW_TSNPORT_TSN_SHAPER_TQAV_AVAIL_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSN_SHAPER_TQEM */
/*
 * EMPTY (RO)
 *
 * Traffic queue empty
 * Bit[i] = 1: traffic queue i is empty
 */
#define TSW_TSNPORT_TSN_SHAPER_TQEM_EMPTY_MASK (0xFFU)
#define TSW_TSNPORT_TSN_SHAPER_TQEM_EMPTY_SHIFT (0U)
#define TSW_TSNPORT_TSN_SHAPER_TQEM_EMPTY_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_SHAPER_TQEM_EMPTY_MASK) >> TSW_TSNPORT_TSN_SHAPER_TQEM_EMPTY_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSN_SHAPER_FPST */
/*
 * TABLE (R/W)
 *
 * Frame Preemption Status Table,
 * Bit[i] = 1: Preemptable traffic in TQ[i], otherwise
 * Express traffic (default)
 */
#define TSW_TSNPORT_TSN_SHAPER_FPST_TABLE_MASK (0xFFU)
#define TSW_TSNPORT_TSN_SHAPER_FPST_TABLE_SHIFT (0U)
#define TSW_TSNPORT_TSN_SHAPER_FPST_TABLE_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TSN_SHAPER_FPST_TABLE_SHIFT) & TSW_TSNPORT_TSN_SHAPER_FPST_TABLE_MASK)
#define TSW_TSNPORT_TSN_SHAPER_FPST_TABLE_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_SHAPER_FPST_TABLE_MASK) >> TSW_TSNPORT_TSN_SHAPER_FPST_TABLE_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSN_SHAPER_MMCT */
/*
 * RQREL (R/W)
 *
 * Request HOLD-Signal release operation. Will be automatically set to <0>
 */
#define TSW_TSNPORT_TSN_SHAPER_MMCT_RQREL_MASK (0x2U)
#define TSW_TSNPORT_TSN_SHAPER_MMCT_RQREL_SHIFT (1U)
#define TSW_TSNPORT_TSN_SHAPER_MMCT_RQREL_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TSN_SHAPER_MMCT_RQREL_SHIFT) & TSW_TSNPORT_TSN_SHAPER_MMCT_RQREL_MASK)
#define TSW_TSNPORT_TSN_SHAPER_MMCT_RQREL_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_SHAPER_MMCT_RQREL_MASK) >> TSW_TSNPORT_TSN_SHAPER_MMCT_RQREL_SHIFT)

/*
 * RQHLD (R/W)
 *
 * Request HOLD-Signal hold operation. Will be automatically set to <0>.
 */
#define TSW_TSNPORT_TSN_SHAPER_MMCT_RQHLD_MASK (0x1U)
#define TSW_TSNPORT_TSN_SHAPER_MMCT_RQHLD_SHIFT (0U)
#define TSW_TSNPORT_TSN_SHAPER_MMCT_RQHLD_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TSN_SHAPER_MMCT_RQHLD_SHIFT) & TSW_TSNPORT_TSN_SHAPER_MMCT_RQHLD_MASK)
#define TSW_TSNPORT_TSN_SHAPER_MMCT_RQHLD_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_SHAPER_MMCT_RQHLD_MASK) >> TSW_TSNPORT_TSN_SHAPER_MMCT_RQHLD_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSN_SHAPER_HOLDADV */
/*
 * VALUE (R/W)
 *
 * holdAdvance time for TAS operation Set-And-Hold-MAC in <sys_clk> cycles
 */
#define TSW_TSNPORT_TSN_SHAPER_HOLDADV_VALUE_MASK (0xFFFFU)
#define TSW_TSNPORT_TSN_SHAPER_HOLDADV_VALUE_SHIFT (0U)
#define TSW_TSNPORT_TSN_SHAPER_HOLDADV_VALUE_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TSN_SHAPER_HOLDADV_VALUE_SHIFT) & TSW_TSNPORT_TSN_SHAPER_HOLDADV_VALUE_MASK)
#define TSW_TSNPORT_TSN_SHAPER_HOLDADV_VALUE_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_SHAPER_HOLDADV_VALUE_MASK) >> TSW_TSNPORT_TSN_SHAPER_HOLDADV_VALUE_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSN_SHAPER_MXSDU0 */
/*
 * SDU (R/W)
 *
 * Maximum SDU size for traffic queue n (n = 0 – 7)Returns 0 when n > TQC. Value is size in words (32 bit word size).
 */
#define TSW_TSNPORT_MXSDU_SDU_MASK (0xFFFFU)
#define TSW_TSNPORT_MXSDU_SDU_SHIFT (0U)
#define TSW_TSNPORT_MXSDU_SDU_SET(x) (((uint32_t)(x) << TSW_TSNPORT_MXSDU_SDU_SHIFT) & TSW_TSNPORT_MXSDU_SDU_MASK)
#define TSW_TSNPORT_MXSDU_SDU_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MXSDU_SDU_MASK) >> TSW_TSNPORT_MXSDU_SDU_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSN_SHAPER_TXSEL0 */
/*
 * CBS_EN (R/W)
 *
 * CBS enable traffic queue n (n = 0 – 7). Returns 0 when n > TQC. Must be 0 when changing register IDSLPi.
 */
#define TSW_TSNPORT_TXSEL_CBS_EN_MASK (0xFFFFU)
#define TSW_TSNPORT_TXSEL_CBS_EN_SHIFT (0U)
#define TSW_TSNPORT_TXSEL_CBS_EN_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TXSEL_CBS_EN_SHIFT) & TSW_TSNPORT_TXSEL_CBS_EN_MASK)
#define TSW_TSNPORT_TXSEL_CBS_EN_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TXSEL_CBS_EN_MASK) >> TSW_TSNPORT_TXSEL_CBS_EN_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSN_SHAPER_IDSEL0 */
/*
 * INT (R/W)
 *
 * CBS idle slope for traffic queue n (n = 0 – 7). Returns
 * 0 when n > TQC. The register must only be written
 * when TXSELi.CBE_EN=0.
 * The idle slope value is defined as (INT + FRACT /
 * 65536). The idle slope is set in bits per tick related to
 * <tx_clk>.
 */
#define TSW_TSNPORT_IDSEL_INT_MASK (0xF0000UL)
#define TSW_TSNPORT_IDSEL_INT_SHIFT (16U)
#define TSW_TSNPORT_IDSEL_INT_SET(x) (((uint32_t)(x) << TSW_TSNPORT_IDSEL_INT_SHIFT) & TSW_TSNPORT_IDSEL_INT_MASK)
#define TSW_TSNPORT_IDSEL_INT_GET(x) (((uint32_t)(x) & TSW_TSNPORT_IDSEL_INT_MASK) >> TSW_TSNPORT_IDSEL_INT_SHIFT)

/*
 * FRACT (R/W)
 *
 */
#define TSW_TSNPORT_IDSEL_FRACT_MASK (0xFFFFU)
#define TSW_TSNPORT_IDSEL_FRACT_SHIFT (0U)
#define TSW_TSNPORT_IDSEL_FRACT_SET(x) (((uint32_t)(x) << TSW_TSNPORT_IDSEL_FRACT_SHIFT) & TSW_TSNPORT_IDSEL_FRACT_MASK)
#define TSW_TSNPORT_IDSEL_FRACT_GET(x) (((uint32_t)(x) & TSW_TSNPORT_IDSEL_FRACT_MASK) >> TSW_TSNPORT_IDSEL_FRACT_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: PORT1_QCH0_CFG */
/*
 * CQF_IN_ERR (WC)
 *
 * qch queue in error
 */
#define TSW_TSNPORT_PORT1_QCH0_CFG_CQF_IN_ERR_MASK (0x100000UL)
#define TSW_TSNPORT_PORT1_QCH0_CFG_CQF_IN_ERR_SHIFT (20U)
#define TSW_TSNPORT_PORT1_QCH0_CFG_CQF_IN_ERR_SET(x) (((uint32_t)(x) << TSW_TSNPORT_PORT1_QCH0_CFG_CQF_IN_ERR_SHIFT) & TSW_TSNPORT_PORT1_QCH0_CFG_CQF_IN_ERR_MASK)
#define TSW_TSNPORT_PORT1_QCH0_CFG_CQF_IN_ERR_GET(x) (((uint32_t)(x) & TSW_TSNPORT_PORT1_QCH0_CFG_CQF_IN_ERR_MASK) >> TSW_TSNPORT_PORT1_QCH0_CFG_CQF_IN_ERR_SHIFT)

/*
 * CQF_NUM (R/W)
 *
 * qch queue destination buffer select
 */
#define TSW_TSNPORT_PORT1_QCH0_CFG_CQF_NUM_MASK (0x70000UL)
#define TSW_TSNPORT_PORT1_QCH0_CFG_CQF_NUM_SHIFT (16U)
#define TSW_TSNPORT_PORT1_QCH0_CFG_CQF_NUM_SET(x) (((uint32_t)(x) << TSW_TSNPORT_PORT1_QCH0_CFG_CQF_NUM_SHIFT) & TSW_TSNPORT_PORT1_QCH0_CFG_CQF_NUM_MASK)
#define TSW_TSNPORT_PORT1_QCH0_CFG_CQF_NUM_GET(x) (((uint32_t)(x) & TSW_TSNPORT_PORT1_QCH0_CFG_CQF_NUM_MASK) >> TSW_TSNPORT_PORT1_QCH0_CFG_CQF_NUM_SHIFT)

/*
 * TAS_GPIO_SEL (R/W)
 *
 * tas_gpio select
 */
#define TSW_TSNPORT_PORT1_QCH0_CFG_TAS_GPIO_SEL_MASK (0x7000U)
#define TSW_TSNPORT_PORT1_QCH0_CFG_TAS_GPIO_SEL_SHIFT (12U)
#define TSW_TSNPORT_PORT1_QCH0_CFG_TAS_GPIO_SEL_SET(x) (((uint32_t)(x) << TSW_TSNPORT_PORT1_QCH0_CFG_TAS_GPIO_SEL_SHIFT) & TSW_TSNPORT_PORT1_QCH0_CFG_TAS_GPIO_SEL_MASK)
#define TSW_TSNPORT_PORT1_QCH0_CFG_TAS_GPIO_SEL_GET(x) (((uint32_t)(x) & TSW_TSNPORT_PORT1_QCH0_CFG_TAS_GPIO_SEL_MASK) >> TSW_TSNPORT_PORT1_QCH0_CFG_TAS_GPIO_SEL_SHIFT)

/*
 * AXIS_QCH_EN (R/W)
 *
 * qch queue in select
 */
#define TSW_TSNPORT_PORT1_QCH0_CFG_AXIS_QCH_EN_MASK (0xFF0U)
#define TSW_TSNPORT_PORT1_QCH0_CFG_AXIS_QCH_EN_SHIFT (4U)
#define TSW_TSNPORT_PORT1_QCH0_CFG_AXIS_QCH_EN_SET(x) (((uint32_t)(x) << TSW_TSNPORT_PORT1_QCH0_CFG_AXIS_QCH_EN_SHIFT) & TSW_TSNPORT_PORT1_QCH0_CFG_AXIS_QCH_EN_MASK)
#define TSW_TSNPORT_PORT1_QCH0_CFG_AXIS_QCH_EN_GET(x) (((uint32_t)(x) & TSW_TSNPORT_PORT1_QCH0_CFG_AXIS_QCH_EN_MASK) >> TSW_TSNPORT_PORT1_QCH0_CFG_AXIS_QCH_EN_SHIFT)

/*
 * CQF_EN (R/W)
 *
 * qch enable
 */
#define TSW_TSNPORT_PORT1_QCH0_CFG_CQF_EN_MASK (0x1U)
#define TSW_TSNPORT_PORT1_QCH0_CFG_CQF_EN_SHIFT (0U)
#define TSW_TSNPORT_PORT1_QCH0_CFG_CQF_EN_SET(x) (((uint32_t)(x) << TSW_TSNPORT_PORT1_QCH0_CFG_CQF_EN_SHIFT) & TSW_TSNPORT_PORT1_QCH0_CFG_CQF_EN_MASK)
#define TSW_TSNPORT_PORT1_QCH0_CFG_CQF_EN_GET(x) (((uint32_t)(x) & TSW_TSNPORT_PORT1_QCH0_CFG_CQF_EN_MASK) >> TSW_TSNPORT_PORT1_QCH0_CFG_CQF_EN_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: PORT1_QCH1_CFG */
/*
 * CQF_IN_ERR (WC)
 *
 * qch queue in error
 */
#define TSW_TSNPORT_PORT1_QCH1_CFG_CQF_IN_ERR_MASK (0x100000UL)
#define TSW_TSNPORT_PORT1_QCH1_CFG_CQF_IN_ERR_SHIFT (20U)
#define TSW_TSNPORT_PORT1_QCH1_CFG_CQF_IN_ERR_SET(x) (((uint32_t)(x) << TSW_TSNPORT_PORT1_QCH1_CFG_CQF_IN_ERR_SHIFT) & TSW_TSNPORT_PORT1_QCH1_CFG_CQF_IN_ERR_MASK)
#define TSW_TSNPORT_PORT1_QCH1_CFG_CQF_IN_ERR_GET(x) (((uint32_t)(x) & TSW_TSNPORT_PORT1_QCH1_CFG_CQF_IN_ERR_MASK) >> TSW_TSNPORT_PORT1_QCH1_CFG_CQF_IN_ERR_SHIFT)

/*
 * CQF_NUM (R/W)
 *
 * qch queue destination buffer select
 */
#define TSW_TSNPORT_PORT1_QCH1_CFG_CQF_NUM_MASK (0x70000UL)
#define TSW_TSNPORT_PORT1_QCH1_CFG_CQF_NUM_SHIFT (16U)
#define TSW_TSNPORT_PORT1_QCH1_CFG_CQF_NUM_SET(x) (((uint32_t)(x) << TSW_TSNPORT_PORT1_QCH1_CFG_CQF_NUM_SHIFT) & TSW_TSNPORT_PORT1_QCH1_CFG_CQF_NUM_MASK)
#define TSW_TSNPORT_PORT1_QCH1_CFG_CQF_NUM_GET(x) (((uint32_t)(x) & TSW_TSNPORT_PORT1_QCH1_CFG_CQF_NUM_MASK) >> TSW_TSNPORT_PORT1_QCH1_CFG_CQF_NUM_SHIFT)

/*
 * TAS_GPIO_SEL (R/W)
 *
 * tas_gpio select
 */
#define TSW_TSNPORT_PORT1_QCH1_CFG_TAS_GPIO_SEL_MASK (0x7000U)
#define TSW_TSNPORT_PORT1_QCH1_CFG_TAS_GPIO_SEL_SHIFT (12U)
#define TSW_TSNPORT_PORT1_QCH1_CFG_TAS_GPIO_SEL_SET(x) (((uint32_t)(x) << TSW_TSNPORT_PORT1_QCH1_CFG_TAS_GPIO_SEL_SHIFT) & TSW_TSNPORT_PORT1_QCH1_CFG_TAS_GPIO_SEL_MASK)
#define TSW_TSNPORT_PORT1_QCH1_CFG_TAS_GPIO_SEL_GET(x) (((uint32_t)(x) & TSW_TSNPORT_PORT1_QCH1_CFG_TAS_GPIO_SEL_MASK) >> TSW_TSNPORT_PORT1_QCH1_CFG_TAS_GPIO_SEL_SHIFT)

/*
 * AXIS_QCH_EN (R/W)
 *
 * qch queue in select
 */
#define TSW_TSNPORT_PORT1_QCH1_CFG_AXIS_QCH_EN_MASK (0xFF0U)
#define TSW_TSNPORT_PORT1_QCH1_CFG_AXIS_QCH_EN_SHIFT (4U)
#define TSW_TSNPORT_PORT1_QCH1_CFG_AXIS_QCH_EN_SET(x) (((uint32_t)(x) << TSW_TSNPORT_PORT1_QCH1_CFG_AXIS_QCH_EN_SHIFT) & TSW_TSNPORT_PORT1_QCH1_CFG_AXIS_QCH_EN_MASK)
#define TSW_TSNPORT_PORT1_QCH1_CFG_AXIS_QCH_EN_GET(x) (((uint32_t)(x) & TSW_TSNPORT_PORT1_QCH1_CFG_AXIS_QCH_EN_MASK) >> TSW_TSNPORT_PORT1_QCH1_CFG_AXIS_QCH_EN_SHIFT)

/*
 * CQF_EN (R/W)
 *
 * qch enable
 */
#define TSW_TSNPORT_PORT1_QCH1_CFG_CQF_EN_MASK (0x1U)
#define TSW_TSNPORT_PORT1_QCH1_CFG_CQF_EN_SHIFT (0U)
#define TSW_TSNPORT_PORT1_QCH1_CFG_CQF_EN_SET(x) (((uint32_t)(x) << TSW_TSNPORT_PORT1_QCH1_CFG_CQF_EN_SHIFT) & TSW_TSNPORT_PORT1_QCH1_CFG_CQF_EN_MASK)
#define TSW_TSNPORT_PORT1_QCH1_CFG_CQF_EN_GET(x) (((uint32_t)(x) & TSW_TSNPORT_PORT1_QCH1_CFG_CQF_EN_MASK) >> TSW_TSNPORT_PORT1_QCH1_CFG_CQF_EN_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: PORT1_QCH2_CFG */
/*
 * CQF_IN_ERR (WC)
 *
 * qch queue in error
 */
#define TSW_TSNPORT_PORT1_QCH2_CFG_CQF_IN_ERR_MASK (0x100000UL)
#define TSW_TSNPORT_PORT1_QCH2_CFG_CQF_IN_ERR_SHIFT (20U)
#define TSW_TSNPORT_PORT1_QCH2_CFG_CQF_IN_ERR_SET(x) (((uint32_t)(x) << TSW_TSNPORT_PORT1_QCH2_CFG_CQF_IN_ERR_SHIFT) & TSW_TSNPORT_PORT1_QCH2_CFG_CQF_IN_ERR_MASK)
#define TSW_TSNPORT_PORT1_QCH2_CFG_CQF_IN_ERR_GET(x) (((uint32_t)(x) & TSW_TSNPORT_PORT1_QCH2_CFG_CQF_IN_ERR_MASK) >> TSW_TSNPORT_PORT1_QCH2_CFG_CQF_IN_ERR_SHIFT)

/*
 * CQF_NUM (R/W)
 *
 * qch queue destination buffer select
 */
#define TSW_TSNPORT_PORT1_QCH2_CFG_CQF_NUM_MASK (0x70000UL)
#define TSW_TSNPORT_PORT1_QCH2_CFG_CQF_NUM_SHIFT (16U)
#define TSW_TSNPORT_PORT1_QCH2_CFG_CQF_NUM_SET(x) (((uint32_t)(x) << TSW_TSNPORT_PORT1_QCH2_CFG_CQF_NUM_SHIFT) & TSW_TSNPORT_PORT1_QCH2_CFG_CQF_NUM_MASK)
#define TSW_TSNPORT_PORT1_QCH2_CFG_CQF_NUM_GET(x) (((uint32_t)(x) & TSW_TSNPORT_PORT1_QCH2_CFG_CQF_NUM_MASK) >> TSW_TSNPORT_PORT1_QCH2_CFG_CQF_NUM_SHIFT)

/*
 * TAS_GPIO_SEL (R/W)
 *
 * tas_gpio select
 */
#define TSW_TSNPORT_PORT1_QCH2_CFG_TAS_GPIO_SEL_MASK (0x7000U)
#define TSW_TSNPORT_PORT1_QCH2_CFG_TAS_GPIO_SEL_SHIFT (12U)
#define TSW_TSNPORT_PORT1_QCH2_CFG_TAS_GPIO_SEL_SET(x) (((uint32_t)(x) << TSW_TSNPORT_PORT1_QCH2_CFG_TAS_GPIO_SEL_SHIFT) & TSW_TSNPORT_PORT1_QCH2_CFG_TAS_GPIO_SEL_MASK)
#define TSW_TSNPORT_PORT1_QCH2_CFG_TAS_GPIO_SEL_GET(x) (((uint32_t)(x) & TSW_TSNPORT_PORT1_QCH2_CFG_TAS_GPIO_SEL_MASK) >> TSW_TSNPORT_PORT1_QCH2_CFG_TAS_GPIO_SEL_SHIFT)

/*
 * AXIS_QCH_EN (R/W)
 *
 * qch queue in select
 */
#define TSW_TSNPORT_PORT1_QCH2_CFG_AXIS_QCH_EN_MASK (0xFF0U)
#define TSW_TSNPORT_PORT1_QCH2_CFG_AXIS_QCH_EN_SHIFT (4U)
#define TSW_TSNPORT_PORT1_QCH2_CFG_AXIS_QCH_EN_SET(x) (((uint32_t)(x) << TSW_TSNPORT_PORT1_QCH2_CFG_AXIS_QCH_EN_SHIFT) & TSW_TSNPORT_PORT1_QCH2_CFG_AXIS_QCH_EN_MASK)
#define TSW_TSNPORT_PORT1_QCH2_CFG_AXIS_QCH_EN_GET(x) (((uint32_t)(x) & TSW_TSNPORT_PORT1_QCH2_CFG_AXIS_QCH_EN_MASK) >> TSW_TSNPORT_PORT1_QCH2_CFG_AXIS_QCH_EN_SHIFT)

/*
 * CQF_EN (R/W)
 *
 * qch enable
 */
#define TSW_TSNPORT_PORT1_QCH2_CFG_CQF_EN_MASK (0x1U)
#define TSW_TSNPORT_PORT1_QCH2_CFG_CQF_EN_SHIFT (0U)
#define TSW_TSNPORT_PORT1_QCH2_CFG_CQF_EN_SET(x) (((uint32_t)(x) << TSW_TSNPORT_PORT1_QCH2_CFG_CQF_EN_SHIFT) & TSW_TSNPORT_PORT1_QCH2_CFG_CQF_EN_MASK)
#define TSW_TSNPORT_PORT1_QCH2_CFG_CQF_EN_GET(x) (((uint32_t)(x) & TSW_TSNPORT_PORT1_QCH2_CFG_CQF_EN_MASK) >> TSW_TSNPORT_PORT1_QCH2_CFG_CQF_EN_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: PORT1_QCH3_CFG */
/*
 * CQF_IN_ERR (WC)
 *
 * qch queue in error
 */
#define TSW_TSNPORT_PORT1_QCH3_CFG_CQF_IN_ERR_MASK (0x100000UL)
#define TSW_TSNPORT_PORT1_QCH3_CFG_CQF_IN_ERR_SHIFT (20U)
#define TSW_TSNPORT_PORT1_QCH3_CFG_CQF_IN_ERR_SET(x) (((uint32_t)(x) << TSW_TSNPORT_PORT1_QCH3_CFG_CQF_IN_ERR_SHIFT) & TSW_TSNPORT_PORT1_QCH3_CFG_CQF_IN_ERR_MASK)
#define TSW_TSNPORT_PORT1_QCH3_CFG_CQF_IN_ERR_GET(x) (((uint32_t)(x) & TSW_TSNPORT_PORT1_QCH3_CFG_CQF_IN_ERR_MASK) >> TSW_TSNPORT_PORT1_QCH3_CFG_CQF_IN_ERR_SHIFT)

/*
 * CQF_NUM (R/W)
 *
 * qch queue destination buffer select
 */
#define TSW_TSNPORT_PORT1_QCH3_CFG_CQF_NUM_MASK (0x70000UL)
#define TSW_TSNPORT_PORT1_QCH3_CFG_CQF_NUM_SHIFT (16U)
#define TSW_TSNPORT_PORT1_QCH3_CFG_CQF_NUM_SET(x) (((uint32_t)(x) << TSW_TSNPORT_PORT1_QCH3_CFG_CQF_NUM_SHIFT) & TSW_TSNPORT_PORT1_QCH3_CFG_CQF_NUM_MASK)
#define TSW_TSNPORT_PORT1_QCH3_CFG_CQF_NUM_GET(x) (((uint32_t)(x) & TSW_TSNPORT_PORT1_QCH3_CFG_CQF_NUM_MASK) >> TSW_TSNPORT_PORT1_QCH3_CFG_CQF_NUM_SHIFT)

/*
 * TAS_GPIO_SEL (R/W)
 *
 * tas_gpio select
 */
#define TSW_TSNPORT_PORT1_QCH3_CFG_TAS_GPIO_SEL_MASK (0x7000U)
#define TSW_TSNPORT_PORT1_QCH3_CFG_TAS_GPIO_SEL_SHIFT (12U)
#define TSW_TSNPORT_PORT1_QCH3_CFG_TAS_GPIO_SEL_SET(x) (((uint32_t)(x) << TSW_TSNPORT_PORT1_QCH3_CFG_TAS_GPIO_SEL_SHIFT) & TSW_TSNPORT_PORT1_QCH3_CFG_TAS_GPIO_SEL_MASK)
#define TSW_TSNPORT_PORT1_QCH3_CFG_TAS_GPIO_SEL_GET(x) (((uint32_t)(x) & TSW_TSNPORT_PORT1_QCH3_CFG_TAS_GPIO_SEL_MASK) >> TSW_TSNPORT_PORT1_QCH3_CFG_TAS_GPIO_SEL_SHIFT)

/*
 * AXIS_QCH_EN (R/W)
 *
 * qch queue in select
 */
#define TSW_TSNPORT_PORT1_QCH3_CFG_AXIS_QCH_EN_MASK (0xFF0U)
#define TSW_TSNPORT_PORT1_QCH3_CFG_AXIS_QCH_EN_SHIFT (4U)
#define TSW_TSNPORT_PORT1_QCH3_CFG_AXIS_QCH_EN_SET(x) (((uint32_t)(x) << TSW_TSNPORT_PORT1_QCH3_CFG_AXIS_QCH_EN_SHIFT) & TSW_TSNPORT_PORT1_QCH3_CFG_AXIS_QCH_EN_MASK)
#define TSW_TSNPORT_PORT1_QCH3_CFG_AXIS_QCH_EN_GET(x) (((uint32_t)(x) & TSW_TSNPORT_PORT1_QCH3_CFG_AXIS_QCH_EN_MASK) >> TSW_TSNPORT_PORT1_QCH3_CFG_AXIS_QCH_EN_SHIFT)

/*
 * CQF_EN (R/W)
 *
 * qch enable
 */
#define TSW_TSNPORT_PORT1_QCH3_CFG_CQF_EN_MASK (0x1U)
#define TSW_TSNPORT_PORT1_QCH3_CFG_CQF_EN_SHIFT (0U)
#define TSW_TSNPORT_PORT1_QCH3_CFG_CQF_EN_SET(x) (((uint32_t)(x) << TSW_TSNPORT_PORT1_QCH3_CFG_CQF_EN_SHIFT) & TSW_TSNPORT_PORT1_QCH3_CFG_CQF_EN_MASK)
#define TSW_TSNPORT_PORT1_QCH3_CFG_CQF_EN_GET(x) (((uint32_t)(x) & TSW_TSNPORT_PORT1_QCH3_CFG_CQF_EN_MASK) >> TSW_TSNPORT_PORT1_QCH3_CFG_CQF_EN_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: PORT1_QCH_ERR_CFG */
/*
 * CQF_QUE_ERR (WC)
 *
 * que gate error for each cqf
 */
#define TSW_TSNPORT_PORT1_QCH_ERR_CFG_CQF_QUE_ERR_MASK (0xFF00U)
#define TSW_TSNPORT_PORT1_QCH_ERR_CFG_CQF_QUE_ERR_SHIFT (8U)
#define TSW_TSNPORT_PORT1_QCH_ERR_CFG_CQF_QUE_ERR_SET(x) (((uint32_t)(x) << TSW_TSNPORT_PORT1_QCH_ERR_CFG_CQF_QUE_ERR_SHIFT) & TSW_TSNPORT_PORT1_QCH_ERR_CFG_CQF_QUE_ERR_MASK)
#define TSW_TSNPORT_PORT1_QCH_ERR_CFG_CQF_QUE_ERR_GET(x) (((uint32_t)(x) & TSW_TSNPORT_PORT1_QCH_ERR_CFG_CQF_QUE_ERR_MASK) >> TSW_TSNPORT_PORT1_QCH_ERR_CFG_CQF_QUE_ERR_SHIFT)

/*
 * CQF_NUM_CFG_ERR (RO)
 *
 * cqf_num config error
 */
#define TSW_TSNPORT_PORT1_QCH_ERR_CFG_CQF_NUM_CFG_ERR_MASK (0x4U)
#define TSW_TSNPORT_PORT1_QCH_ERR_CFG_CQF_NUM_CFG_ERR_SHIFT (2U)
#define TSW_TSNPORT_PORT1_QCH_ERR_CFG_CQF_NUM_CFG_ERR_GET(x) (((uint32_t)(x) & TSW_TSNPORT_PORT1_QCH_ERR_CFG_CQF_NUM_CFG_ERR_MASK) >> TSW_TSNPORT_PORT1_QCH_ERR_CFG_CQF_NUM_CFG_ERR_SHIFT)

/*
 * AXIS_QCH_CFG_ERR (RO)
 *
 * axis_qch_en config error
 */
#define TSW_TSNPORT_PORT1_QCH_ERR_CFG_AXIS_QCH_CFG_ERR_MASK (0x2U)
#define TSW_TSNPORT_PORT1_QCH_ERR_CFG_AXIS_QCH_CFG_ERR_SHIFT (1U)
#define TSW_TSNPORT_PORT1_QCH_ERR_CFG_AXIS_QCH_CFG_ERR_GET(x) (((uint32_t)(x) & TSW_TSNPORT_PORT1_QCH_ERR_CFG_AXIS_QCH_CFG_ERR_MASK) >> TSW_TSNPORT_PORT1_QCH_ERR_CFG_AXIS_QCH_CFG_ERR_SHIFT)

/*
 * CQF_CLR_CTRL (R/W)
 *
 * enable cqf buffer auto clear when error
 */
#define TSW_TSNPORT_PORT1_QCH_ERR_CFG_CQF_CLR_CTRL_MASK (0x1U)
#define TSW_TSNPORT_PORT1_QCH_ERR_CFG_CQF_CLR_CTRL_SHIFT (0U)
#define TSW_TSNPORT_PORT1_QCH_ERR_CFG_CQF_CLR_CTRL_SET(x) (((uint32_t)(x) << TSW_TSNPORT_PORT1_QCH_ERR_CFG_CQF_CLR_CTRL_SHIFT) & TSW_TSNPORT_PORT1_QCH_ERR_CFG_CQF_CLR_CTRL_MASK)
#define TSW_TSNPORT_PORT1_QCH_ERR_CFG_CQF_CLR_CTRL_GET(x) (((uint32_t)(x) & TSW_TSNPORT_PORT1_QCH_ERR_CFG_CQF_CLR_CTRL_MASK) >> TSW_TSNPORT_PORT1_QCH_ERR_CFG_CQF_CLR_CTRL_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSN_SHAPER_TAS_CRSR */
/*
 * ADMINGS (RO)
 *
 * Admin gate states, fixed 0xFF. Gate states when TAS is disabled.
 */
#define TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_ADMINGS_MASK (0xFF000000UL)
#define TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_ADMINGS_SHIFT (24U)
#define TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_ADMINGS_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_ADMINGS_MASK) >> TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_ADMINGS_SHIFT)

/*
 * OPERGS (RO)
 *
 * Operational gate states of TQ[i] (i = 0 – TQC-1)
 * Bit[i]=0 – Gate is closed; no start of frame TX possible
 * Bit[i]=1 – Gate is open
 */
#define TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_OPERGS_MASK (0xFF0000UL)
#define TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_OPERGS_SHIFT (16U)
#define TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_OPERGS_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_OPERGS_MASK) >> TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_OPERGS_SHIFT)

/*
 * TAS_GPIO_STA (RO)
 *
 * operational tas gpio gate status of TQ[i]
 */
#define TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_TAS_GPIO_STA_MASK (0xFF00U)
#define TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_TAS_GPIO_STA_SHIFT (8U)
#define TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_TAS_GPIO_STA_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_TAS_GPIO_STA_MASK) >> TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_TAS_GPIO_STA_SHIFT)

/*
 * CFGPEND (RO)
 *
 * Configuration change is pending – Admin basetime not yet reached.
 */
#define TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_CFGPEND_MASK (0x8U)
#define TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_CFGPEND_SHIFT (3U)
#define TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_CFGPEND_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_CFGPEND_MASK) >> TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_CFGPEND_SHIFT)

/*
 * CFGERR (R/WC)
 *
 * Configuration error.
 */
#define TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_CFGERR_MASK (0x4U)
#define TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_CFGERR_SHIFT (2U)
#define TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_CFGERR_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_CFGERR_SHIFT) & TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_CFGERR_MASK)
#define TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_CFGERR_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_CFGERR_MASK) >> TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_CFGERR_SHIFT)

/*
 * CFGCHG (R/W)
 *
 * Switch configuration; Bit is automatically reset to 0;
 * Setting Bit=1 triggers configuration change event.
 */
#define TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_CFGCHG_MASK (0x2U)
#define TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_CFGCHG_SHIFT (1U)
#define TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_CFGCHG_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_CFGCHG_SHIFT) & TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_CFGCHG_MASK)
#define TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_CFGCHG_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_CFGCHG_MASK) >> TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_CFGCHG_SHIFT)

/*
 * EN (R/W)
 *
 * Enable time aware scheduling.
 */
#define TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_EN_MASK (0x1U)
#define TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_EN_SHIFT (0U)
#define TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_EN_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_EN_SHIFT) & TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_EN_MASK)
#define TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_EN_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_EN_MASK) >> TSW_TSNPORT_TSN_SHAPER_TAS_CRSR_EN_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSN_SHAPER_TAS_ACYCLETM */
/*
 * CTIME (R/W)
 *
 * Admin cycletime in nanoseconds.
 */
#define TSW_TSNPORT_TSN_SHAPER_TAS_ACYCLETM_CTIME_MASK (0x3FFFFFFFUL)
#define TSW_TSNPORT_TSN_SHAPER_TAS_ACYCLETM_CTIME_SHIFT (0U)
#define TSW_TSNPORT_TSN_SHAPER_TAS_ACYCLETM_CTIME_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TSN_SHAPER_TAS_ACYCLETM_CTIME_SHIFT) & TSW_TSNPORT_TSN_SHAPER_TAS_ACYCLETM_CTIME_MASK)
#define TSW_TSNPORT_TSN_SHAPER_TAS_ACYCLETM_CTIME_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_SHAPER_TAS_ACYCLETM_CTIME_MASK) >> TSW_TSNPORT_TSN_SHAPER_TAS_ACYCLETM_CTIME_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSN_SHAPER_TAS_ABASETM_L */
/*
 * BASETM_L (R/W)
 *
 * Admin basetime – nanoseconds and seconds part.
 */
#define TSW_TSNPORT_TSN_SHAPER_TAS_ABASETM_L_BASETM_L_MASK (0x3FFFFFFFUL)
#define TSW_TSNPORT_TSN_SHAPER_TAS_ABASETM_L_BASETM_L_SHIFT (0U)
#define TSW_TSNPORT_TSN_SHAPER_TAS_ABASETM_L_BASETM_L_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TSN_SHAPER_TAS_ABASETM_L_BASETM_L_SHIFT) & TSW_TSNPORT_TSN_SHAPER_TAS_ABASETM_L_BASETM_L_MASK)
#define TSW_TSNPORT_TSN_SHAPER_TAS_ABASETM_L_BASETM_L_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_SHAPER_TAS_ABASETM_L_BASETM_L_MASK) >> TSW_TSNPORT_TSN_SHAPER_TAS_ABASETM_L_BASETM_L_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSN_SHAPER_TAS_ABASETM_H */
/*
 * BASETM_H (R/W)
 *
 */
#define TSW_TSNPORT_TSN_SHAPER_TAS_ABASETM_H_BASETM_H_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_TSN_SHAPER_TAS_ABASETM_H_BASETM_H_SHIFT (0U)
#define TSW_TSNPORT_TSN_SHAPER_TAS_ABASETM_H_BASETM_H_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TSN_SHAPER_TAS_ABASETM_H_BASETM_H_SHIFT) & TSW_TSNPORT_TSN_SHAPER_TAS_ABASETM_H_BASETM_H_MASK)
#define TSW_TSNPORT_TSN_SHAPER_TAS_ABASETM_H_BASETM_H_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_SHAPER_TAS_ABASETM_H_BASETM_H_MASK) >> TSW_TSNPORT_TSN_SHAPER_TAS_ABASETM_H_BASETM_H_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSN_SHAPER_TAS_LISTLEN */
/*
 * OLISTLEN (RO)
 *
 * Oper list length.
 */
#define TSW_TSNPORT_TSN_SHAPER_TAS_LISTLEN_OLISTLEN_MASK (0xFF0000UL)
#define TSW_TSNPORT_TSN_SHAPER_TAS_LISTLEN_OLISTLEN_SHIFT (16U)
#define TSW_TSNPORT_TSN_SHAPER_TAS_LISTLEN_OLISTLEN_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_SHAPER_TAS_LISTLEN_OLISTLEN_MASK) >> TSW_TSNPORT_TSN_SHAPER_TAS_LISTLEN_OLISTLEN_SHIFT)

/*
 * ALISTLEN (R/W)
 *
 * Admin list length.
 */
#define TSW_TSNPORT_TSN_SHAPER_TAS_LISTLEN_ALISTLEN_MASK (0xFFU)
#define TSW_TSNPORT_TSN_SHAPER_TAS_LISTLEN_ALISTLEN_SHIFT (0U)
#define TSW_TSNPORT_TSN_SHAPER_TAS_LISTLEN_ALISTLEN_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TSN_SHAPER_TAS_LISTLEN_ALISTLEN_SHIFT) & TSW_TSNPORT_TSN_SHAPER_TAS_LISTLEN_ALISTLEN_MASK)
#define TSW_TSNPORT_TSN_SHAPER_TAS_LISTLEN_ALISTLEN_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_SHAPER_TAS_LISTLEN_ALISTLEN_MASK) >> TSW_TSNPORT_TSN_SHAPER_TAS_LISTLEN_ALISTLEN_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSN_SHAPER_TAS_OCYCLETM */
/*
 * CTIME (RO)
 *
 * Operational cycletime in nanoseconds
 */
#define TSW_TSNPORT_TSN_SHAPER_TAS_OCYCLETM_CTIME_MASK (0x3FFFFFFFUL)
#define TSW_TSNPORT_TSN_SHAPER_TAS_OCYCLETM_CTIME_SHIFT (0U)
#define TSW_TSNPORT_TSN_SHAPER_TAS_OCYCLETM_CTIME_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_SHAPER_TAS_OCYCLETM_CTIME_MASK) >> TSW_TSNPORT_TSN_SHAPER_TAS_OCYCLETM_CTIME_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSN_SHAPER_TAS_OBASETM_L */
/*
 * BASETM_L (RO)
 *
 * Operational basetime – nanoseconds and seconds part. The operational basetime might occasionally have a non-normalized value (ns >= 10^9) for one clock cycle.
 */
#define TSW_TSNPORT_TSN_SHAPER_TAS_OBASETM_L_BASETM_L_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_TSN_SHAPER_TAS_OBASETM_L_BASETM_L_SHIFT (0U)
#define TSW_TSNPORT_TSN_SHAPER_TAS_OBASETM_L_BASETM_L_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_SHAPER_TAS_OBASETM_L_BASETM_L_MASK) >> TSW_TSNPORT_TSN_SHAPER_TAS_OBASETM_L_BASETM_L_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSN_SHAPER_TAS_OBASETM_H */
/*
 * BASETM_H (RO)
 *
 */
#define TSW_TSNPORT_TSN_SHAPER_TAS_OBASETM_H_BASETM_H_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_TSN_SHAPER_TAS_OBASETM_H_BASETM_H_SHIFT (0U)
#define TSW_TSNPORT_TSN_SHAPER_TAS_OBASETM_H_BASETM_H_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_SHAPER_TAS_OBASETM_H_BASETM_H_MASK) >> TSW_TSNPORT_TSN_SHAPER_TAS_OBASETM_H_BASETM_H_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSN_SHAPER_MXTK0 */
/*
 * TICK (R/W)
 *
 * Maximum SDU size in clock ticks. MXTKi is only supported when TQC > i, otherwise read-only with value 0
 */
#define TSW_TSNPORT_MXTK_TICK_MASK (0xFFFFFFUL)
#define TSW_TSNPORT_MXTK_TICK_SHIFT (0U)
#define TSW_TSNPORT_MXTK_TICK_SET(x) (((uint32_t)(x) << TSW_TSNPORT_MXTK_TICK_SHIFT) & TSW_TSNPORT_MXTK_TICK_MASK)
#define TSW_TSNPORT_MXTK_TICK_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MXTK_TICK_MASK) >> TSW_TSNPORT_MXTK_TICK_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSN_SHAPER_TXOV0 */
/*
 * VALUE (R/WC)
 *
 * Transmission overrun counter; increments on transmission when gate is closed; any write access will clear register to 0. TXOVi is only supported when TQC > i.
 */
#define TSW_TSNPORT_TXOV_VALUE_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_TXOV_VALUE_SHIFT (0U)
#define TSW_TSNPORT_TXOV_VALUE_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TXOV_VALUE_SHIFT) & TSW_TSNPORT_TXOV_VALUE_MASK)
#define TSW_TSNPORT_TXOV_VALUE_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TXOV_VALUE_MASK) >> TSW_TSNPORT_TXOV_VALUE_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSN_SHAPER_ACLIST_ENTRY0_L */
/*
 * TAS_GPIO (R/W)
 *
 * gate states for qch and ptp event source
 */
#define TSW_TSNPORT_SHACL_TSN_SHAPER_ACLIST_ENTRY0_L_TAS_GPIO_MASK (0x3FC00UL)
#define TSW_TSNPORT_SHACL_TSN_SHAPER_ACLIST_ENTRY0_L_TAS_GPIO_SHIFT (10U)
#define TSW_TSNPORT_SHACL_TSN_SHAPER_ACLIST_ENTRY0_L_TAS_GPIO_SET(x) (((uint32_t)(x) << TSW_TSNPORT_SHACL_TSN_SHAPER_ACLIST_ENTRY0_L_TAS_GPIO_SHIFT) & TSW_TSNPORT_SHACL_TSN_SHAPER_ACLIST_ENTRY0_L_TAS_GPIO_MASK)
#define TSW_TSNPORT_SHACL_TSN_SHAPER_ACLIST_ENTRY0_L_TAS_GPIO_GET(x) (((uint32_t)(x) & TSW_TSNPORT_SHACL_TSN_SHAPER_ACLIST_ENTRY0_L_TAS_GPIO_MASK) >> TSW_TSNPORT_SHACL_TSN_SHAPER_ACLIST_ENTRY0_L_TAS_GPIO_SHIFT)

/*
 * OP (R/W)
 *
 * gate operation:
 * 0 – SetGateStates
 * 1 – Set-And-Hold-MAC
 * 2 – Set-And-Release-MAC
 * 3 – undefined
 */
#define TSW_TSNPORT_SHACL_TSN_SHAPER_ACLIST_ENTRY0_L_OP_MASK (0x300U)
#define TSW_TSNPORT_SHACL_TSN_SHAPER_ACLIST_ENTRY0_L_OP_SHIFT (8U)
#define TSW_TSNPORT_SHACL_TSN_SHAPER_ACLIST_ENTRY0_L_OP_SET(x) (((uint32_t)(x) << TSW_TSNPORT_SHACL_TSN_SHAPER_ACLIST_ENTRY0_L_OP_SHIFT) & TSW_TSNPORT_SHACL_TSN_SHAPER_ACLIST_ENTRY0_L_OP_MASK)
#define TSW_TSNPORT_SHACL_TSN_SHAPER_ACLIST_ENTRY0_L_OP_GET(x) (((uint32_t)(x) & TSW_TSNPORT_SHACL_TSN_SHAPER_ACLIST_ENTRY0_L_OP_MASK) >> TSW_TSNPORT_SHACL_TSN_SHAPER_ACLIST_ENTRY0_L_OP_SHIFT)

/*
 * STATE (R/W)
 *
 * gate state vector;
 * 1 – Gate is open
 */
#define TSW_TSNPORT_SHACL_TSN_SHAPER_ACLIST_ENTRY0_L_STATE_MASK (0xFFU)
#define TSW_TSNPORT_SHACL_TSN_SHAPER_ACLIST_ENTRY0_L_STATE_SHIFT (0U)
#define TSW_TSNPORT_SHACL_TSN_SHAPER_ACLIST_ENTRY0_L_STATE_SET(x) (((uint32_t)(x) << TSW_TSNPORT_SHACL_TSN_SHAPER_ACLIST_ENTRY0_L_STATE_SHIFT) & TSW_TSNPORT_SHACL_TSN_SHAPER_ACLIST_ENTRY0_L_STATE_MASK)
#define TSW_TSNPORT_SHACL_TSN_SHAPER_ACLIST_ENTRY0_L_STATE_GET(x) (((uint32_t)(x) & TSW_TSNPORT_SHACL_TSN_SHAPER_ACLIST_ENTRY0_L_STATE_MASK) >> TSW_TSNPORT_SHACL_TSN_SHAPER_ACLIST_ENTRY0_L_STATE_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSN_SHAPER_ACLIST_ENTRY0_H */
/*
 * TIME (R/W)
 *
 * Time interval, entry execution in in host clock ticks (<sys_clk>)
 */
#define TSW_TSNPORT_SHACL_TSN_SHAPER_ACLIST_ENTRY0_H_TIME_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_SHACL_TSN_SHAPER_ACLIST_ENTRY0_H_TIME_SHIFT (0U)
#define TSW_TSNPORT_SHACL_TSN_SHAPER_ACLIST_ENTRY0_H_TIME_SET(x) (((uint32_t)(x) << TSW_TSNPORT_SHACL_TSN_SHAPER_ACLIST_ENTRY0_H_TIME_SHIFT) & TSW_TSNPORT_SHACL_TSN_SHAPER_ACLIST_ENTRY0_H_TIME_MASK)
#define TSW_TSNPORT_SHACL_TSN_SHAPER_ACLIST_ENTRY0_H_TIME_GET(x) (((uint32_t)(x) & TSW_TSNPORT_SHACL_TSN_SHAPER_ACLIST_ENTRY0_H_TIME_MASK) >> TSW_TSNPORT_SHACL_TSN_SHAPER_ACLIST_ENTRY0_H_TIME_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSN_EP_VER */
/*
 * VER_HI (RO)
 *
 * major version number
 */
#define TSW_TSNPORT_TSN_EP_VER_VER_HI_MASK (0xFF000000UL)
#define TSW_TSNPORT_TSN_EP_VER_VER_HI_SHIFT (24U)
#define TSW_TSNPORT_TSN_EP_VER_VER_HI_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_EP_VER_VER_HI_MASK) >> TSW_TSNPORT_TSN_EP_VER_VER_HI_SHIFT)

/*
 * VER_LO (RO)
 *
 * minor version number
 */
#define TSW_TSNPORT_TSN_EP_VER_VER_LO_MASK (0xFF0000UL)
#define TSW_TSNPORT_TSN_EP_VER_VER_LO_SHIFT (16U)
#define TSW_TSNPORT_TSN_EP_VER_VER_LO_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_EP_VER_VER_LO_MASK) >> TSW_TSNPORT_TSN_EP_VER_VER_LO_SHIFT)

/*
 * VER_REV (RO)
 *
 * revision number
 */
#define TSW_TSNPORT_TSN_EP_VER_VER_REV_MASK (0xFFU)
#define TSW_TSNPORT_TSN_EP_VER_VER_REV_SHIFT (0U)
#define TSW_TSNPORT_TSN_EP_VER_VER_REV_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_EP_VER_VER_REV_MASK) >> TSW_TSNPORT_TSN_EP_VER_VER_REV_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSN_EP_CTRL */
/*
 * FILTDIS (R/W)
 *
 * Disable filtering of PTP frames (Ethertype = 0x88F7)
 */
#define TSW_TSNPORT_TSN_EP_CTRL_FILTDIS_MASK (0x80000000UL)
#define TSW_TSNPORT_TSN_EP_CTRL_FILTDIS_SHIFT (31U)
#define TSW_TSNPORT_TSN_EP_CTRL_FILTDIS_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TSN_EP_CTRL_FILTDIS_SHIFT) & TSW_TSNPORT_TSN_EP_CTRL_FILTDIS_MASK)
#define TSW_TSNPORT_TSN_EP_CTRL_FILTDIS_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_EP_CTRL_FILTDIS_MASK) >> TSW_TSNPORT_TSN_EP_CTRL_FILTDIS_SHIFT)

/*
 * PTP_1S_EN (R/W)
 *
 * Enable PTPv2 1-step synchronization suppor
 */
#define TSW_TSNPORT_TSN_EP_CTRL_PTP_1S_EN_MASK (0x40000000UL)
#define TSW_TSNPORT_TSN_EP_CTRL_PTP_1S_EN_SHIFT (30U)
#define TSW_TSNPORT_TSN_EP_CTRL_PTP_1S_EN_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TSN_EP_CTRL_PTP_1S_EN_SHIFT) & TSW_TSNPORT_TSN_EP_CTRL_PTP_1S_EN_MASK)
#define TSW_TSNPORT_TSN_EP_CTRL_PTP_1S_EN_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_EP_CTRL_PTP_1S_EN_MASK) >> TSW_TSNPORT_TSN_EP_CTRL_PTP_1S_EN_SHIFT)

/*
 * IE_TSF (R/W)
 *
 * TxTimestampFifo interrupt enable; interrupt will be set when IE_TSF=<1> and TSF_SR.USED>0
 */
#define TSW_TSNPORT_TSN_EP_CTRL_IE_TSF_MASK (0x1U)
#define TSW_TSNPORT_TSN_EP_CTRL_IE_TSF_SHIFT (0U)
#define TSW_TSNPORT_TSN_EP_CTRL_IE_TSF_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TSN_EP_CTRL_IE_TSF_SHIFT) & TSW_TSNPORT_TSN_EP_CTRL_IE_TSF_MASK)
#define TSW_TSNPORT_TSN_EP_CTRL_IE_TSF_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_EP_CTRL_IE_TSF_MASK) >> TSW_TSNPORT_TSN_EP_CTRL_IE_TSF_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSN_EP_TXUF */
/*
 * COUNTER (R/WC)
 *
 * TX buffer underflow counter; incremented when any MAC runs out of data during transmission. The counter is cleared at any write access. The counter is shared by pMAC and eMAC. If underflow event occurs at the same time for pMAC and eMAC, it will be counted as one event.
 */
#define TSW_TSNPORT_TSN_EP_TXUF_COUNTER_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_TSN_EP_TXUF_COUNTER_SHIFT (0U)
#define TSW_TSNPORT_TSN_EP_TXUF_COUNTER_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TSN_EP_TXUF_COUNTER_SHIFT) & TSW_TSNPORT_TSN_EP_TXUF_COUNTER_MASK)
#define TSW_TSNPORT_TSN_EP_TXUF_COUNTER_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_EP_TXUF_COUNTER_MASK) >> TSW_TSNPORT_TSN_EP_TXUF_COUNTER_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSN_EP_IPCFG */
/*
 * INCL_RTC (RO)
 *
 * IP core parameter “INCL_RTC”
 */
#define TSW_TSNPORT_TSN_EP_IPCFG_INCL_RTC_MASK (0x80000000UL)
#define TSW_TSNPORT_TSN_EP_IPCFG_INCL_RTC_SHIFT (31U)
#define TSW_TSNPORT_TSN_EP_IPCFG_INCL_RTC_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_EP_IPCFG_INCL_RTC_MASK) >> TSW_TSNPORT_TSN_EP_IPCFG_INCL_RTC_SHIFT)

/*
 * INCL_SHAP (RO)
 *
 * IP core parameter “INCL_SHAPER”
 */
#define TSW_TSNPORT_TSN_EP_IPCFG_INCL_SHAP_MASK (0x40000000UL)
#define TSW_TSNPORT_TSN_EP_IPCFG_INCL_SHAP_SHIFT (30U)
#define TSW_TSNPORT_TSN_EP_IPCFG_INCL_SHAP_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_EP_IPCFG_INCL_SHAP_MASK) >> TSW_TSNPORT_TSN_EP_IPCFG_INCL_SHAP_SHIFT)

/*
 * INCL_FPE (RO)
 *
 * IP core parameter “INCL_FPE”
 */
#define TSW_TSNPORT_TSN_EP_IPCFG_INCL_FPE_MASK (0x20000000UL)
#define TSW_TSNPORT_TSN_EP_IPCFG_INCL_FPE_SHIFT (29U)
#define TSW_TSNPORT_TSN_EP_IPCFG_INCL_FPE_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_EP_IPCFG_INCL_FPE_MASK) >> TSW_TSNPORT_TSN_EP_IPCFG_INCL_FPE_SHIFT)

/*
 * INCL_TSF (RO)
 *
 * IP core parameter “INCL_TSF”
 */
#define TSW_TSNPORT_TSN_EP_IPCFG_INCL_TSF_MASK (0x10000000UL)
#define TSW_TSNPORT_TSN_EP_IPCFG_INCL_TSF_SHIFT (28U)
#define TSW_TSNPORT_TSN_EP_IPCFG_INCL_TSF_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_EP_IPCFG_INCL_TSF_MASK) >> TSW_TSNPORT_TSN_EP_IPCFG_INCL_TSF_SHIFT)

/*
 * INCL_TSYNC (RO)
 *
 * IP core parameter “INCL_TSYNC”
 */
#define TSW_TSNPORT_TSN_EP_IPCFG_INCL_TSYNC_MASK (0x8000000UL)
#define TSW_TSNPORT_TSN_EP_IPCFG_INCL_TSYNC_SHIFT (27U)
#define TSW_TSNPORT_TSN_EP_IPCFG_INCL_TSYNC_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_EP_IPCFG_INCL_TSYNC_MASK) >> TSW_TSNPORT_TSN_EP_IPCFG_INCL_TSYNC_SHIFT)

/*
 * INCL_1STEP (RO)
 *
 * IP core parameter “INCL_1STEP”
 */
#define TSW_TSNPORT_TSN_EP_IPCFG_INCL_1STEP_MASK (0x4000000UL)
#define TSW_TSNPORT_TSN_EP_IPCFG_INCL_1STEP_SHIFT (26U)
#define TSW_TSNPORT_TSN_EP_IPCFG_INCL_1STEP_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_EP_IPCFG_INCL_1STEP_MASK) >> TSW_TSNPORT_TSN_EP_IPCFG_INCL_1STEP_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSN_EP_TSF_D0 */
/*
 * TSF_NS (RO)
 *
 * Tx-Timestamp-Fifo, lower 32 bit part of local time (<curtime>) at the start of transmission of the packet. Usually nanoseconds part when used with included RTC.
 */
#define TSW_TSNPORT_TSN_EP_TSF_D0_TSF_NS_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_TSN_EP_TSF_D0_TSF_NS_SHIFT (0U)
#define TSW_TSNPORT_TSN_EP_TSF_D0_TSF_NS_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_EP_TSF_D0_TSF_NS_MASK) >> TSW_TSNPORT_TSN_EP_TSF_D0_TSF_NS_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSN_EP_TSF_D1 */
/*
 * TSF_SEC (RO)
 *
 * Tx-Timestamp-Fifo, upper 32 bit part of the local time (<curtime>) at the start of the transmission of the packet. Usually seconds part when used with included RTC.
 */
#define TSW_TSNPORT_TSN_EP_TSF_D1_TSF_SEC_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_TSN_EP_TSF_D1_TSF_SEC_SHIFT (0U)
#define TSW_TSNPORT_TSN_EP_TSF_D1_TSF_SEC_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_EP_TSF_D1_TSF_SEC_MASK) >> TSW_TSNPORT_TSN_EP_TSF_D1_TSF_SEC_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSN_EP_TSF_D2 */
/*
 * TSF_TQ (RO)
 *
 * Tx-Timestamp-Fifo, traffic queue <tx_tqueue> of sent packet
 */
#define TSW_TSNPORT_TSN_EP_TSF_D2_TSF_TQ_MASK (0xE0000000UL)
#define TSW_TSNPORT_TSN_EP_TSF_D2_TSF_TQ_SHIFT (29U)
#define TSW_TSNPORT_TSN_EP_TSF_D2_TSF_TQ_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_EP_TSF_D2_TSF_TQ_MASK) >> TSW_TSNPORT_TSN_EP_TSF_D2_TSF_TQ_SHIFT)

/*
 * TSF_USR (RO)
 *
 * Tx-Timestamp-Fifo, user sideband <tx_tuser> of sent packet; Note: any read to register will remove actual value from FIFO
 */
#define TSW_TSNPORT_TSN_EP_TSF_D2_TSF_USR_MASK (0x7U)
#define TSW_TSNPORT_TSN_EP_TSF_D2_TSF_USR_SHIFT (0U)
#define TSW_TSNPORT_TSN_EP_TSF_D2_TSF_USR_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_EP_TSF_D2_TSF_USR_MASK) >> TSW_TSNPORT_TSN_EP_TSF_D2_TSF_USR_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSN_EP_TSF_SR */
/*
 * TSF_OV (R/WC)
 *
 * Overflow of Tx-Timestamp-Fifo. At least one transmitted packet has been sent and timestamp was not stored; write bit to clear flag
 */
#define TSW_TSNPORT_TSN_EP_TSF_SR_TSF_OV_MASK (0x80000000UL)
#define TSW_TSNPORT_TSN_EP_TSF_SR_TSF_OV_SHIFT (31U)
#define TSW_TSNPORT_TSN_EP_TSF_SR_TSF_OV_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TSN_EP_TSF_SR_TSF_OV_SHIFT) & TSW_TSNPORT_TSN_EP_TSF_SR_TSF_OV_MASK)
#define TSW_TSNPORT_TSN_EP_TSF_SR_TSF_OV_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_EP_TSF_SR_TSF_OV_MASK) >> TSW_TSNPORT_TSN_EP_TSF_SR_TSF_OV_SHIFT)

/*
 * TSF_USED (RO)
 *
 * Tx-Timestamp-Fifo currently used entries counter; reading of TSF_Dx is only valid if field value > 0. Any read from TSF_D2 will decrement counter (unless already 0).
 */
#define TSW_TSNPORT_TSN_EP_TSF_SR_TSF_USED_MASK (0xFFU)
#define TSW_TSNPORT_TSN_EP_TSF_SR_TSF_USED_SHIFT (0U)
#define TSW_TSNPORT_TSN_EP_TSF_SR_TSF_USED_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_EP_TSF_SR_TSF_USED_MASK) >> TSW_TSNPORT_TSN_EP_TSF_SR_TSF_USED_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSN_EP_MMS_CTRL */
/*
 * STATSEL (R/W)
 *
 * MMS statistic counter selection, value can be read in register
 * MMS_STAT
 * <000>: Frame reassembly error counter (802.3br, 30.14.1.8)
 * <001>: Frames rejected due to wrong SMD (802.3br, 30.14.1.9)
 * <010>: Frame assembly ok counter (802.3br, 30.14.1.10)
 * <011>: Fragment rx counter (802.3br, 30.14.1.11)
 * <100>: Fragment tx counter (802.3br, 30.14.1.12)
 * <101>: Hold request counter (802.3br, 30.14.1.13)
 * otherwise: <0>
 */
#define TSW_TSNPORT_TSN_EP_MMS_CTRL_STATSEL_MASK (0xE0U)
#define TSW_TSNPORT_TSN_EP_MMS_CTRL_STATSEL_SHIFT (5U)
#define TSW_TSNPORT_TSN_EP_MMS_CTRL_STATSEL_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TSN_EP_MMS_CTRL_STATSEL_SHIFT) & TSW_TSNPORT_TSN_EP_MMS_CTRL_STATSEL_MASK)
#define TSW_TSNPORT_TSN_EP_MMS_CTRL_STATSEL_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_EP_MMS_CTRL_STATSEL_MASK) >> TSW_TSNPORT_TSN_EP_MMS_CTRL_STATSEL_SHIFT)

/*
 * FRAGSZ (R/W)
 *
 * Minimum non-final fragment size: 64 x (1 + FRAGSZ) – 4 octets
 */
#define TSW_TSNPORT_TSN_EP_MMS_CTRL_FRAGSZ_MASK (0x18U)
#define TSW_TSNPORT_TSN_EP_MMS_CTRL_FRAGSZ_SHIFT (3U)
#define TSW_TSNPORT_TSN_EP_MMS_CTRL_FRAGSZ_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TSN_EP_MMS_CTRL_FRAGSZ_SHIFT) & TSW_TSNPORT_TSN_EP_MMS_CTRL_FRAGSZ_MASK)
#define TSW_TSNPORT_TSN_EP_MMS_CTRL_FRAGSZ_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_EP_MMS_CTRL_FRAGSZ_MASK) >> TSW_TSNPORT_TSN_EP_MMS_CTRL_FRAGSZ_SHIFT)

/*
 * DISV (R/W)
 *
 * Disable verification
 */
#define TSW_TSNPORT_TSN_EP_MMS_CTRL_DISV_MASK (0x4U)
#define TSW_TSNPORT_TSN_EP_MMS_CTRL_DISV_SHIFT (2U)
#define TSW_TSNPORT_TSN_EP_MMS_CTRL_DISV_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TSN_EP_MMS_CTRL_DISV_SHIFT) & TSW_TSNPORT_TSN_EP_MMS_CTRL_DISV_MASK)
#define TSW_TSNPORT_TSN_EP_MMS_CTRL_DISV_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_EP_MMS_CTRL_DISV_MASK) >> TSW_TSNPORT_TSN_EP_MMS_CTRL_DISV_SHIFT)

/*
 * LINK (R/W)
 *
 * Link error
 */
#define TSW_TSNPORT_TSN_EP_MMS_CTRL_LINK_MASK (0x2U)
#define TSW_TSNPORT_TSN_EP_MMS_CTRL_LINK_SHIFT (1U)
#define TSW_TSNPORT_TSN_EP_MMS_CTRL_LINK_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TSN_EP_MMS_CTRL_LINK_SHIFT) & TSW_TSNPORT_TSN_EP_MMS_CTRL_LINK_MASK)
#define TSW_TSNPORT_TSN_EP_MMS_CTRL_LINK_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_EP_MMS_CTRL_LINK_MASK) >> TSW_TSNPORT_TSN_EP_MMS_CTRL_LINK_SHIFT)

/*
 * EN (R/W)
 *
 * Enable preemption
 */
#define TSW_TSNPORT_TSN_EP_MMS_CTRL_EN_MASK (0x1U)
#define TSW_TSNPORT_TSN_EP_MMS_CTRL_EN_SHIFT (0U)
#define TSW_TSNPORT_TSN_EP_MMS_CTRL_EN_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TSN_EP_MMS_CTRL_EN_SHIFT) & TSW_TSNPORT_TSN_EP_MMS_CTRL_EN_MASK)
#define TSW_TSNPORT_TSN_EP_MMS_CTRL_EN_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_EP_MMS_CTRL_EN_MASK) >> TSW_TSNPORT_TSN_EP_MMS_CTRL_EN_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSN_EP_MMS_STS */
/*
 * VFAIL (RO)
 *
 * 802.3br verification state failure; verification is done when any bit VFAIL or VOK is <1>
 */
#define TSW_TSNPORT_TSN_EP_MMS_STS_VFAIL_MASK (0x4U)
#define TSW_TSNPORT_TSN_EP_MMS_STS_VFAIL_SHIFT (2U)
#define TSW_TSNPORT_TSN_EP_MMS_STS_VFAIL_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_EP_MMS_STS_VFAIL_MASK) >> TSW_TSNPORT_TSN_EP_MMS_STS_VFAIL_SHIFT)

/*
 * VOK (RO)
 *
 * 802.3br verification state ok; verification is done when any bit VFAIL or VOK is <1>
 */
#define TSW_TSNPORT_TSN_EP_MMS_STS_VOK_MASK (0x2U)
#define TSW_TSNPORT_TSN_EP_MMS_STS_VOK_SHIFT (1U)
#define TSW_TSNPORT_TSN_EP_MMS_STS_VOK_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_EP_MMS_STS_VOK_MASK) >> TSW_TSNPORT_TSN_EP_MMS_STS_VOK_SHIFT)

/*
 * HLD (RO)
 *
 * HOLD-Signal
 */
#define TSW_TSNPORT_TSN_EP_MMS_STS_HLD_MASK (0x1U)
#define TSW_TSNPORT_TSN_EP_MMS_STS_HLD_SHIFT (0U)
#define TSW_TSNPORT_TSN_EP_MMS_STS_HLD_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_EP_MMS_STS_HLD_MASK) >> TSW_TSNPORT_TSN_EP_MMS_STS_HLD_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSN_EP_MMS_VTIME */
/*
 * VTIME (R/W)
 *
 * 802.3br verification timeout counter in <sys_clk> cycles. Must be set by software in range of 1ms to 128ms.
 */
#define TSW_TSNPORT_TSN_EP_MMS_VTIME_VTIME_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_TSN_EP_MMS_VTIME_VTIME_SHIFT (0U)
#define TSW_TSNPORT_TSN_EP_MMS_VTIME_VTIME_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TSN_EP_MMS_VTIME_VTIME_SHIFT) & TSW_TSNPORT_TSN_EP_MMS_VTIME_VTIME_MASK)
#define TSW_TSNPORT_TSN_EP_MMS_VTIME_VTIME_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_EP_MMS_VTIME_VTIME_MASK) >> TSW_TSNPORT_TSN_EP_MMS_VTIME_VTIME_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSN_EP_MMS_STAT */
/*
 * COUNTER (R/WC)
 *
 * Statistic counter of MMS, selected by MMS_CTRL.STATSEL,any write access will clear selected counter
 */
#define TSW_TSNPORT_TSN_EP_MMS_STAT_COUNTER_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_TSN_EP_MMS_STAT_COUNTER_SHIFT (0U)
#define TSW_TSNPORT_TSN_EP_MMS_STAT_COUNTER_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TSN_EP_MMS_STAT_COUNTER_SHIFT) & TSW_TSNPORT_TSN_EP_MMS_STAT_COUNTER_MASK)
#define TSW_TSNPORT_TSN_EP_MMS_STAT_COUNTER_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_EP_MMS_STAT_COUNTER_MASK) >> TSW_TSNPORT_TSN_EP_MMS_STAT_COUNTER_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSN_EP_PTP_UPTM_NS */
/*
 * UPTM_NS (WO)
 *
 * PTP SYNC frame “upstreamTxTime” in format “seconds.nanoseconds” as potentially received by another TSN-EP port. The correction field of a transmitted PTP SYNC frame is modified by (egressTimestamp –upstreamTxTime), relative to the LocalClock. The “rateRatio” to the Grandmaster Clock is not taken into account.
 */
#define TSW_TSNPORT_TSN_EP_PTP_UPTM_NS_UPTM_NS_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_TSN_EP_PTP_UPTM_NS_UPTM_NS_SHIFT (0U)
#define TSW_TSNPORT_TSN_EP_PTP_UPTM_NS_UPTM_NS_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TSN_EP_PTP_UPTM_NS_UPTM_NS_SHIFT) & TSW_TSNPORT_TSN_EP_PTP_UPTM_NS_UPTM_NS_MASK)
#define TSW_TSNPORT_TSN_EP_PTP_UPTM_NS_UPTM_NS_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_EP_PTP_UPTM_NS_UPTM_NS_MASK) >> TSW_TSNPORT_TSN_EP_PTP_UPTM_NS_UPTM_NS_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSN_EP_PTP_UPTM_S */
/*
 * UPTM_NS (WO)
 *
 */
#define TSW_TSNPORT_TSN_EP_PTP_UPTM_S_UPTM_NS_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_TSN_EP_PTP_UPTM_S_UPTM_NS_SHIFT (0U)
#define TSW_TSNPORT_TSN_EP_PTP_UPTM_S_UPTM_NS_SET(x) (((uint32_t)(x) << TSW_TSNPORT_TSN_EP_PTP_UPTM_S_UPTM_NS_SHIFT) & TSW_TSNPORT_TSN_EP_PTP_UPTM_S_UPTM_NS_MASK)
#define TSW_TSNPORT_TSN_EP_PTP_UPTM_S_UPTM_NS_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_EP_PTP_UPTM_S_UPTM_NS_MASK) >> TSW_TSNPORT_TSN_EP_PTP_UPTM_S_UPTM_NS_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: TSN_EP_PTP_SR */
/*
 * MEAS_NS (RO)
 *
 * Measured value of the deviation of the early timestamping for PTP frames. This value is informational only. The deviation is already included to the corrected “correctionField”.
 */
#define TSW_TSNPORT_TSN_EP_PTP_SR_MEAS_NS_MASK (0xFFFFU)
#define TSW_TSNPORT_TSN_EP_PTP_SR_MEAS_NS_SHIFT (0U)
#define TSW_TSNPORT_TSN_EP_PTP_SR_MEAS_NS_GET(x) (((uint32_t)(x) & TSW_TSNPORT_TSN_EP_PTP_SR_MEAS_NS_MASK) >> TSW_TSNPORT_TSN_EP_PTP_SR_MEAS_NS_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: SW_CTRL_PORT_MAIN_TAGGING */
/*
 * FORCE (R/W)
 *
 * The VLAN-TAG with PVID will be inserted in every frame from Host as their first VLAN-TAG. This can be used for double tagging of tagged/trunk ports
 */
#define TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_FORCE_MASK (0x20000UL)
#define TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_FORCE_SHIFT (17U)
#define TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_FORCE_SET(x) (((uint32_t)(x) << TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_FORCE_SHIFT) & TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_FORCE_MASK)
#define TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_FORCE_GET(x) (((uint32_t)(x) & TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_FORCE_MASK) >> TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_FORCE_SHIFT)

/*
 * ACCESS (R/W)
 *
 * Every tagged frame not matching PVID is filtered out. Every untagged ingress  frame will be tagged with PVID. Every egress frame with PVID will be untagged
 */
#define TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_ACCESS_MASK (0x10000UL)
#define TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_ACCESS_SHIFT (16U)
#define TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_ACCESS_SET(x) (((uint32_t)(x) << TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_ACCESS_SHIFT) & TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_ACCESS_MASK)
#define TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_ACCESS_GET(x) (((uint32_t)(x) & TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_ACCESS_MASK) >> TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_ACCESS_SHIFT)

/*
 * PCP (R/W)
 *
 * VLAN-TCI: Priority Code Point, used when tagged.
 */
#define TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_PCP_MASK (0xE000U)
#define TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_PCP_SHIFT (13U)
#define TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_PCP_SET(x) (((uint32_t)(x) << TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_PCP_SHIFT) & TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_PCP_MASK)
#define TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_PCP_GET(x) (((uint32_t)(x) & TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_PCP_MASK) >> TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_PCP_SHIFT)

/*
 * DEI (R/W)
 *
 * VLAN-TCI: Drop Eligible Indicator, used when tagged.
 */
#define TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_DEI_MASK (0x1000U)
#define TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_DEI_SHIFT (12U)
#define TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_DEI_SET(x) (((uint32_t)(x) << TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_DEI_SHIFT) & TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_DEI_MASK)
#define TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_DEI_GET(x) (((uint32_t)(x) & TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_DEI_MASK) >> TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_DEI_SHIFT)

/*
 * PVID (R/W)
 *
 * Native VLAN of Port. Untagged traffic will be tagged with the native VLAN-ID By default the Port uses VLAN 1.
 */
#define TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_PVID_MASK (0xFFFU)
#define TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_PVID_SHIFT (0U)
#define TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_PVID_SET(x) (((uint32_t)(x) << TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_PVID_SHIFT) & TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_PVID_MASK)
#define TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_PVID_GET(x) (((uint32_t)(x) & TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_PVID_MASK) >> TSW_TSNPORT_SW_CTRL_PORT_MAIN_TAGGING_PVID_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: SW_CTRL_PORT_MAIN_ENNABLE */
/*
 * EN_SF (R/W)
 *
 * only applicable for CPU-Port at egress: '1' to use S&F FIFO and '0' disable S&F FIFO. Changing during frame operation can lead to frame corruption
 */
#define TSW_TSNPORT_SW_CTRL_PORT_MAIN_ENNABLE_EN_SF_MASK (0x2U)
#define TSW_TSNPORT_SW_CTRL_PORT_MAIN_ENNABLE_EN_SF_SHIFT (1U)
#define TSW_TSNPORT_SW_CTRL_PORT_MAIN_ENNABLE_EN_SF_SET(x) (((uint32_t)(x) << TSW_TSNPORT_SW_CTRL_PORT_MAIN_ENNABLE_EN_SF_SHIFT) & TSW_TSNPORT_SW_CTRL_PORT_MAIN_ENNABLE_EN_SF_MASK)
#define TSW_TSNPORT_SW_CTRL_PORT_MAIN_ENNABLE_EN_SF_GET(x) (((uint32_t)(x) & TSW_TSNPORT_SW_CTRL_PORT_MAIN_ENNABLE_EN_SF_MASK) >> TSW_TSNPORT_SW_CTRL_PORT_MAIN_ENNABLE_EN_SF_SHIFT)

/*
 * EN_QCI (R/W)
 *
 * if QCI is present at selected egress port, '1' to use QCI and '0' disable QCI. Changing during frame operation can lead to frame corruption.
 */
#define TSW_TSNPORT_SW_CTRL_PORT_MAIN_ENNABLE_EN_QCI_MASK (0x1U)
#define TSW_TSNPORT_SW_CTRL_PORT_MAIN_ENNABLE_EN_QCI_SHIFT (0U)
#define TSW_TSNPORT_SW_CTRL_PORT_MAIN_ENNABLE_EN_QCI_SET(x) (((uint32_t)(x) << TSW_TSNPORT_SW_CTRL_PORT_MAIN_ENNABLE_EN_QCI_SHIFT) & TSW_TSNPORT_SW_CTRL_PORT_MAIN_ENNABLE_EN_QCI_MASK)
#define TSW_TSNPORT_SW_CTRL_PORT_MAIN_ENNABLE_EN_QCI_GET(x) (((uint32_t)(x) & TSW_TSNPORT_SW_CTRL_PORT_MAIN_ENNABLE_EN_QCI_MASK) >> TSW_TSNPORT_SW_CTRL_PORT_MAIN_ENNABLE_EN_QCI_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: SW_CTRL_EGRESS_ECSR_QDROP */
/*
 * DIS_VEC (R/W)
 *
 * disable drop for each queue when queue not free
 */
#define TSW_TSNPORT_SW_CTRL_EGRESS_ECSR_QDROP_DIS_VEC_MASK (0xFF000000UL)
#define TSW_TSNPORT_SW_CTRL_EGRESS_ECSR_QDROP_DIS_VEC_SHIFT (24U)
#define TSW_TSNPORT_SW_CTRL_EGRESS_ECSR_QDROP_DIS_VEC_SET(x) (((uint32_t)(x) << TSW_TSNPORT_SW_CTRL_EGRESS_ECSR_QDROP_DIS_VEC_SHIFT) & TSW_TSNPORT_SW_CTRL_EGRESS_ECSR_QDROP_DIS_VEC_MASK)
#define TSW_TSNPORT_SW_CTRL_EGRESS_ECSR_QDROP_DIS_VEC_GET(x) (((uint32_t)(x) & TSW_TSNPORT_SW_CTRL_EGRESS_ECSR_QDROP_DIS_VEC_MASK) >> TSW_TSNPORT_SW_CTRL_EGRESS_ECSR_QDROP_DIS_VEC_SHIFT)

/*
 * EN_VEC (R/W)
 *
 * Enable/Disable drop in egress when TSN queue not free.
 * 1 - drop enabled
 * 0 - drop disabled
 * TSN-SW:
 * bit[i] - from Port[i]
 */
#define TSW_TSNPORT_SW_CTRL_EGRESS_ECSR_QDROP_EN_VEC_MASK (0xFFFFFFUL)
#define TSW_TSNPORT_SW_CTRL_EGRESS_ECSR_QDROP_EN_VEC_SHIFT (0U)
#define TSW_TSNPORT_SW_CTRL_EGRESS_ECSR_QDROP_EN_VEC_SET(x) (((uint32_t)(x) << TSW_TSNPORT_SW_CTRL_EGRESS_ECSR_QDROP_EN_VEC_SHIFT) & TSW_TSNPORT_SW_CTRL_EGRESS_ECSR_QDROP_EN_VEC_MASK)
#define TSW_TSNPORT_SW_CTRL_EGRESS_ECSR_QDROP_EN_VEC_GET(x) (((uint32_t)(x) & TSW_TSNPORT_SW_CTRL_EGRESS_ECSR_QDROP_EN_VEC_MASK) >> TSW_TSNPORT_SW_CTRL_EGRESS_ECSR_QDROP_EN_VEC_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_CNT_BYTE */
/*
 * FDMEM_CNT_BYTE (RO)
 *
 * Number of bytes stored in frame drop FIFO
 */
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_CNT_BYTE_FDMEM_CNT_BYTE_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_CNT_BYTE_FDMEM_CNT_BYTE_SHIFT (0U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_CNT_BYTE_FDMEM_CNT_BYTE_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_CNT_BYTE_FDMEM_CNT_BYTE_MASK) >> TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_CNT_BYTE_FDMEM_CNT_BYTE_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS */
/*
 * WAIT_FOR_LU (RO)
 *
 * FD FIFO waits for LookUp information.
 */
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_WAIT_FOR_LU_MASK (0x800U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_WAIT_FOR_LU_SHIFT (11U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_WAIT_FOR_LU_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_WAIT_FOR_LU_MASK) >> TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_WAIT_FOR_LU_SHIFT)

/*
 * WAIT_FOR_FRAME (RO)
 *
 * FD FIFO waits for more frame data.
 */
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_WAIT_FOR_FRAME_MASK (0x400U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_WAIT_FOR_FRAME_SHIFT (10U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_WAIT_FOR_FRAME_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_WAIT_FOR_FRAME_MASK) >> TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_WAIT_FOR_FRAME_SHIFT)

/*
 * BUSY (RO)
 *
 * FD FIFO processes data.
 */
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_BUSY_MASK (0x200U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_BUSY_SHIFT (9U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_BUSY_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_BUSY_MASK) >> TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_BUSY_SHIFT)

/*
 * READY (RO)
 *
 * FD FIFO ready to work or working.
 */
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_READY_MASK (0x100U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_READY_SHIFT (8U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_READY_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_READY_MASK) >> TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_READY_SHIFT)

/*
 * FULL (RO)
 *
 * FD FIFO full
 */
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_FULL_MASK (0x8U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_FULL_SHIFT (3U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_FULL_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_FULL_MASK) >> TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_FULL_SHIFT)

/*
 * AMST_FULL (RO)
 *
 * FD FIFO almost full. Less than 1600 Byte left.
 */
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_AMST_FULL_MASK (0x4U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_AMST_FULL_SHIFT (2U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_AMST_FULL_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_AMST_FULL_MASK) >> TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_AMST_FULL_SHIFT)

/*
 * AMST_EMPTY (RO)
 *
 * FD FIFO almost empty. Few bytes in FIFO.
 */
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_AMST_EMPTY_MASK (0x2U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_AMST_EMPTY_SHIFT (1U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_AMST_EMPTY_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_AMST_EMPTY_MASK) >> TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_AMST_EMPTY_SHIFT)

/*
 * EMPTY (RO)
 *
 * FD FIFO empty
 */
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_EMPTY_MASK (0x1U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_EMPTY_SHIFT (0U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_EMPTY_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_EMPTY_MASK) >> TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_FDMEM_STS_EMPTY_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG */
/*
 * LU_DESC_ERR (R/W1C)
 *
 * LookUp Descriptor lost, because of unknown frame burst by MAC. If there is no  MAC mailfunction then this flag will never be raised. FDFIFO requires reset.
 */
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_LU_DESC_ERR_MASK (0x40U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_LU_DESC_ERR_SHIFT (6U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_LU_DESC_ERR_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_LU_DESC_ERR_SHIFT) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_LU_DESC_ERR_MASK)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_LU_DESC_ERR_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_LU_DESC_ERR_MASK) >> TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_LU_DESC_ERR_SHIFT)

/*
 * WRFAIL_FULL (R/W1C)
 *
 * Set if a frame is partially written into FIFO which had insufficient space. The frame is cut and frame error is set.
 */
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_WRFAIL_FULL_MASK (0x20U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_WRFAIL_FULL_SHIFT (5U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_WRFAIL_FULL_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_WRFAIL_FULL_SHIFT) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_WRFAIL_FULL_MASK)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_WRFAIL_FULL_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_WRFAIL_FULL_MASK) >> TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_WRFAIL_FULL_SHIFT)

/*
 * DROP_NRDY (R/W1C)
 *
 * Frame was dropped because the FIFO was not ready. That can typically happen after a reset of the FIFO
 */
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DROP_NRDY_MASK (0x10U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DROP_NRDY_SHIFT (4U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DROP_NRDY_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DROP_NRDY_SHIFT) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DROP_NRDY_MASK)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DROP_NRDY_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DROP_NRDY_MASK) >> TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DROP_NRDY_SHIFT)

/*
 * DROP_FULL_DESC (R/W1C)
 *
 * Frame was dropped because the internal descriptor FIFO is full. Full by too many frames.
 */
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DROP_FULL_DESC_MASK (0x8U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DROP_FULL_DESC_SHIFT (3U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DROP_FULL_DESC_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DROP_FULL_DESC_SHIFT) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DROP_FULL_DESC_MASK)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DROP_FULL_DESC_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DROP_FULL_DESC_MASK) >> TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DROP_FULL_DESC_SHIFT)

/*
 * DROP_FULL_MEM (R/W1C)
 *
 * Frame was dropped because the FIFO is full. Full by too much data.
 */
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DROP_FULL_MEM_MASK (0x4U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DROP_FULL_MEM_SHIFT (2U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DROP_FULL_MEM_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DROP_FULL_MEM_SHIFT) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DROP_FULL_MEM_MASK)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DROP_FULL_MEM_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DROP_FULL_MEM_MASK) >> TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DROP_FULL_MEM_SHIFT)

/*
 * DESC_NRDY_ERR (R/W1C)
 *
 * FD FIFO failure. Descriptor not received correctly.
 */
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DESC_NRDY_ERR_MASK (0x2U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DESC_NRDY_ERR_SHIFT (1U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DESC_NRDY_ERR_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DESC_NRDY_ERR_SHIFT) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DESC_NRDY_ERR_MASK)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DESC_NRDY_ERR_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DESC_NRDY_ERR_MASK) >> TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DESC_NRDY_ERR_SHIFT)

/*
 * DESC_SEQ_ERR (R/W1C)
 *
 * FD FIFO failure. Internal controller lost synchronization.
 */
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DESC_SEQ_ERR_MASK (0x1U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DESC_SEQ_ERR_SHIFT (0U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DESC_SEQ_ERR_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DESC_SEQ_ERR_SHIFT) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DESC_SEQ_ERR_MASK)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DESC_SEQ_ERR_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DESC_SEQ_ERR_MASK) >> TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_ERROR_FLAG_DESC_SEQ_ERR_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: SW_CTRL_IGRESS_RX_FDFIFO_E_IE_ERROR_FLAG */
/*
 * IE (R/W)
 *
 * Interrupt enable of ERROR_FLAG.
 */
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_IE_ERROR_FLAG_IE_MASK (0x7FU)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_IE_ERROR_FLAG_IE_SHIFT (0U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_IE_ERROR_FLAG_IE_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_IE_ERROR_FLAG_IE_SHIFT) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_IE_ERROR_FLAG_IE_MASK)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_IE_ERROR_FLAG_IE_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_IE_ERROR_FLAG_IE_MASK) >> TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_IE_ERROR_FLAG_IE_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: SW_CTRL_IGRESS_RX_FDFIFO_E_IN_CONFIG */
/*
 * NOCUT_ERROR (R/W)
 *
 * FD_FIFO does not shorten frames which contain an error.
 */
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_IN_CONFIG_NOCUT_ERROR_MASK (0x1U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_IN_CONFIG_NOCUT_ERROR_SHIFT (0U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_IN_CONFIG_NOCUT_ERROR_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_IN_CONFIG_NOCUT_ERROR_SHIFT) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_IN_CONFIG_NOCUT_ERROR_MASK)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_IN_CONFIG_NOCUT_ERROR_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_IN_CONFIG_NOCUT_ERROR_MASK) >> TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_IN_CONFIG_NOCUT_ERROR_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG */
/*
 * DROP_DEST (R/W)
 *
 * Bit mapped Destination for dropped frames. Typically, frames are cleared at destination 0. Use another value to stream frames for analysis. Supports only max range of port[15:0].
 */
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_DROP_DEST_MASK (0xFFFF0000UL)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_DROP_DEST_SHIFT (16U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_DROP_DEST_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_DROP_DEST_SHIFT) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_DROP_DEST_MASK)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_DROP_DEST_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_DROP_DEST_MASK) >> TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_DROP_DEST_SHIFT)

/*
 * MIRROR_TX_EN (R/W)
 *
 * Incoming frames of this port will be mirrored to the given destination in MIRROR if their destination match with MIRROR_TX.
 */
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_MIRROR_TX_EN_MASK (0x200U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_MIRROR_TX_EN_SHIFT (9U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_MIRROR_TX_EN_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_MIRROR_TX_EN_SHIFT) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_MIRROR_TX_EN_MASK)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_MIRROR_TX_EN_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_MIRROR_TX_EN_MASK) >> TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_MIRROR_TX_EN_SHIFT)

/*
 * MIRROR_RX_EN (R/W)
 *
 * Incoming frames of this port will be mirrored to the given destination in MIRROR_RX.
 */
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_MIRROR_RX_EN_MASK (0x100U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_MIRROR_RX_EN_SHIFT (8U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_MIRROR_RX_EN_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_MIRROR_RX_EN_SHIFT) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_MIRROR_RX_EN_MASK)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_MIRROR_RX_EN_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_MIRROR_RX_EN_MASK) >> TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_MIRROR_RX_EN_SHIFT)

/*
 * CT_FPE_OVRD (R/W)
 *
 * If any Store&Forward option in RX_FDFIFO is set then this flag will still force preemptable traffic to be forwarded in Cut-Through mode. This is a useful option to save latency by double buffering if the used MAC/TSN-EP already does S&F.
 */
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_CT_FPE_OVRD_MASK (0x40U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_CT_FPE_OVRD_SHIFT (6U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_CT_FPE_OVRD_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_CT_FPE_OVRD_SHIFT) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_CT_FPE_OVRD_MASK)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_CT_FPE_OVRD_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_CT_FPE_OVRD_MASK) >> TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_CT_FPE_OVRD_SHIFT)

/*
 * DISABLE (R/W)
 *
 * Disable input of FD FIFO. Take care that also descriptor generation of LookUp is disabled. Remaining frames should be cleared with DROP_ALL.
 */
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_DISABLE_MASK (0x20U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_DISABLE_SHIFT (5U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_DISABLE_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_DISABLE_SHIFT) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_DISABLE_MASK)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_DISABLE_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_DISABLE_MASK) >> TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_DISABLE_SHIFT)

/*
 * DROP_ALL (R/W)
 *
 * Route all frames to DROP_DEST.
 */
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_DROP_ALL_MASK (0x10U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_DROP_ALL_SHIFT (4U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_DROP_ALL_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_DROP_ALL_SHIFT) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_DROP_ALL_MASK)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_DROP_ALL_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_DROP_ALL_MASK) >> TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_DROP_ALL_SHIFT)

/*
 * ERROR_TO_CPU (R/W)
 *
 * Send error frames to CPU.
 */
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_ERROR_TO_CPU_MASK (0x8U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_ERROR_TO_CPU_SHIFT (3U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_ERROR_TO_CPU_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_ERROR_TO_CPU_SHIFT) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_ERROR_TO_CPU_MASK)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_ERROR_TO_CPU_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_ERROR_TO_CPU_MASK) >> TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_ERROR_TO_CPU_SHIFT)

/*
 * MIRROR_TO_CPU (R/W)
 *
 * Duplicate frames to CPU.
 */
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_MIRROR_TO_CPU_MASK (0x4U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_MIRROR_TO_CPU_SHIFT (2U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_MIRROR_TO_CPU_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_MIRROR_TO_CPU_SHIFT) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_MIRROR_TO_CPU_MASK)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_MIRROR_TO_CPU_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_MIRROR_TO_CPU_MASK) >> TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_MIRROR_TO_CPU_SHIFT)

/*
 * NODROP_ERROR (R/W)
 *
 * Do not drop frame errors.
 */
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_NODROP_ERROR_MASK (0x2U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_NODROP_ERROR_SHIFT (1U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_NODROP_ERROR_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_NODROP_ERROR_SHIFT) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_NODROP_ERROR_MASK)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_NODROP_ERROR_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_NODROP_ERROR_MASK) >> TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_NODROP_ERROR_SHIFT)

/*
 * MODE_STORE_FW (R/W)
 *
 * Switch between Cut-Through and Store&Forward mode. 0 - Cut-Through 1 - Store&Forward
 */
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_MODE_STORE_FW_MASK (0x1U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_MODE_STORE_FW_SHIFT (0U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_MODE_STORE_FW_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_MODE_STORE_FW_SHIFT) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_MODE_STORE_FW_MASK)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_MODE_STORE_FW_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_MODE_STORE_FW_MASK) >> TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_MODE_STORE_FW_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: SW_CTRL_IGRESS_RX_FDFIFO_E_RESET */
/*
 * SOFTRS (W)
 *
 * Write 1 to reset FD controller and memory pointers. Register Map content remains untouched
 */
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_RESET_SOFTRS_MASK (0x1U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_RESET_SOFTRS_SHIFT (0U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_RESET_SOFTRS_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_RESET_SOFTRS_SHIFT) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_RESET_SOFTRS_MASK)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_RESET_SOFTRS_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_RESET_SOFTRS_MASK) >> TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_RESET_SOFTRS_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: SW_CTRL_IGRESS_RX_FDFIFO_E_PARAM */
/*
 * LU_FIFO_DEPTH (RO)
 *
 * Number of MAC lookup descriptors the FIFO can store.
 */
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_PARAM_LU_FIFO_DEPTH_MASK (0xFF000000UL)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_PARAM_LU_FIFO_DEPTH_SHIFT (24U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_PARAM_LU_FIFO_DEPTH_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_PARAM_LU_FIFO_DEPTH_MASK) >> TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_PARAM_LU_FIFO_DEPTH_SHIFT)

/*
 * FD_DESC_FIFO_DESC (RO)
 *
 * Number of FD descriptors the FIFO can store. Two descriptors need to be stored per frame.
 */
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_PARAM_FD_DESC_FIFO_DESC_MASK (0xFF0000UL)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_PARAM_FD_DESC_FIFO_DESC_SHIFT (16U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_PARAM_FD_DESC_FIFO_DESC_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_PARAM_FD_DESC_FIFO_DESC_MASK) >> TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_PARAM_FD_DESC_FIFO_DESC_SHIFT)

/*
 * FD_FIFO_DESC (RO)
 *
 * Number of words (4byte) the Frame Drop FIFO can store.
 */
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_PARAM_FD_FIFO_DESC_MASK (0xFFFFU)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_PARAM_FD_FIFO_DESC_SHIFT (0U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_PARAM_FD_FIFO_DESC_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_PARAM_FD_FIFO_DESC_MASK) >> TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_PARAM_FD_FIFO_DESC_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: SW_CTRL_IGRESS_RX_FDFIFO_E_STRFWD */
/*
 * PORT (R/W)
 *
 * If selected port is set then the frame is transmitted in Store & Forward mode. This is necessary when the ingress rate of this port is slower than the egress rate of the transmitting port. In S&F, the ingress module is able to drop frames with bad CRC.bit 0 - CPU-Port,
 * bit 1 - Port 1, …
 */
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_STRFWD_PORT_MASK (0x1FFFFFFUL)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_STRFWD_PORT_SHIFT (0U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_STRFWD_PORT_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_STRFWD_PORT_SHIFT) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_STRFWD_PORT_MASK)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_STRFWD_PORT_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_STRFWD_PORT_MASK) >> TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_STRFWD_PORT_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: SW_CTRL_IGRESS_RX_FDFIFO_E_PORTMASK */
/*
 * PORT (R/W)
 *
 * Port grouping via port mask. If the selected port is not set then the destination will be filtered out. This register allows the realization of port-based-VLAN (no VLAN tags required, only set it by ports).
 * bit 0 - CPU-Port,
 * bit 1 - Port 1, …
 */
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_PORTMASK_PORT_MASK (0x1FFFFFFUL)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_PORTMASK_PORT_SHIFT (0U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_PORTMASK_PORT_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_PORTMASK_PORT_SHIFT) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_PORTMASK_PORT_MASK)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_PORTMASK_PORT_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_PORTMASK_PORT_MASK) >> TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_PORTMASK_PORT_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: SW_CTRL_IGRESS_RX_FDFIFO_E_MIRROR */
/*
 * PORT (R/W)
 *
 * Mirror Port. If port mirroring is enabled TX/RX traffic will also be forwarded to this port.
 * bit 0 - CPU-Port,
 * bit 1 - Port 1, …
 */
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_MIRROR_PORT_MASK (0x1FFFFFFUL)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_MIRROR_PORT_SHIFT (0U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_MIRROR_PORT_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_MIRROR_PORT_SHIFT) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_MIRROR_PORT_MASK)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_MIRROR_PORT_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_MIRROR_PORT_MASK) >> TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_MIRROR_PORT_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: SW_CTRL_IGRESS_RX_FDFIFO_E_MIRROR_TX */
/*
 * PORT (R/W)
 *
 * Mirror Selection TX. The destination of the frame is compared with this vector. All matching TX probe ports will be mirrored to MIRROR. It is necessary to configure all ingress ports to mirror the complete TX traffic.
 * bit 0 - CPU-Port,
 * bit 1 - Port 1, …
 */
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_MIRROR_TX_PORT_MASK (0x1FFFFFFUL)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_MIRROR_TX_PORT_SHIFT (0U)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_MIRROR_TX_PORT_SET(x) (((uint32_t)(x) << TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_MIRROR_TX_PORT_SHIFT) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_MIRROR_TX_PORT_MASK)
#define TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_MIRROR_TX_PORT_GET(x) (((uint32_t)(x) & TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_MIRROR_TX_PORT_MASK) >> TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_MIRROR_TX_PORT_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: SW_CTRL_MONITOR_CTRL */
/*
 * EN (R/W)
 *
 * Enables counter. If deasserted the counter process stops and the counters hold their value.
 */
#define TSW_TSNPORT_SW_CTRL_MONITOR_CTRL_EN_MASK (0x1U)
#define TSW_TSNPORT_SW_CTRL_MONITOR_CTRL_EN_SHIFT (0U)
#define TSW_TSNPORT_SW_CTRL_MONITOR_CTRL_EN_SET(x) (((uint32_t)(x) << TSW_TSNPORT_SW_CTRL_MONITOR_CTRL_EN_SHIFT) & TSW_TSNPORT_SW_CTRL_MONITOR_CTRL_EN_MASK)
#define TSW_TSNPORT_SW_CTRL_MONITOR_CTRL_EN_GET(x) (((uint32_t)(x) & TSW_TSNPORT_SW_CTRL_MONITOR_CTRL_EN_MASK) >> TSW_TSNPORT_SW_CTRL_MONITOR_CTRL_EN_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: SW_CTRL_MONITOR_RESET */
/*
 * RSRX (WO)
 *
 * Write '1' to reset all RX counters.
 */
#define TSW_TSNPORT_SW_CTRL_MONITOR_RESET_RSRX_MASK (0x4U)
#define TSW_TSNPORT_SW_CTRL_MONITOR_RESET_RSRX_SHIFT (2U)
#define TSW_TSNPORT_SW_CTRL_MONITOR_RESET_RSRX_SET(x) (((uint32_t)(x) << TSW_TSNPORT_SW_CTRL_MONITOR_RESET_RSRX_SHIFT) & TSW_TSNPORT_SW_CTRL_MONITOR_RESET_RSRX_MASK)
#define TSW_TSNPORT_SW_CTRL_MONITOR_RESET_RSRX_GET(x) (((uint32_t)(x) & TSW_TSNPORT_SW_CTRL_MONITOR_RESET_RSRX_MASK) >> TSW_TSNPORT_SW_CTRL_MONITOR_RESET_RSRX_SHIFT)

/*
 * RSTX (WO)
 *
 * Write '1' to reset all TX counters
 */
#define TSW_TSNPORT_SW_CTRL_MONITOR_RESET_RSTX_MASK (0x2U)
#define TSW_TSNPORT_SW_CTRL_MONITOR_RESET_RSTX_SHIFT (1U)
#define TSW_TSNPORT_SW_CTRL_MONITOR_RESET_RSTX_SET(x) (((uint32_t)(x) << TSW_TSNPORT_SW_CTRL_MONITOR_RESET_RSTX_SHIFT) & TSW_TSNPORT_SW_CTRL_MONITOR_RESET_RSTX_MASK)
#define TSW_TSNPORT_SW_CTRL_MONITOR_RESET_RSTX_GET(x) (((uint32_t)(x) & TSW_TSNPORT_SW_CTRL_MONITOR_RESET_RSTX_MASK) >> TSW_TSNPORT_SW_CTRL_MONITOR_RESET_RSTX_SHIFT)

/*
 * RSALL (WO)
 *
 * Write '1' to reset all TX&RX counters.
 */
#define TSW_TSNPORT_SW_CTRL_MONITOR_RESET_RSALL_MASK (0x1U)
#define TSW_TSNPORT_SW_CTRL_MONITOR_RESET_RSALL_SHIFT (0U)
#define TSW_TSNPORT_SW_CTRL_MONITOR_RESET_RSALL_SET(x) (((uint32_t)(x) << TSW_TSNPORT_SW_CTRL_MONITOR_RESET_RSALL_SHIFT) & TSW_TSNPORT_SW_CTRL_MONITOR_RESET_RSALL_MASK)
#define TSW_TSNPORT_SW_CTRL_MONITOR_RESET_RSALL_GET(x) (((uint32_t)(x) & TSW_TSNPORT_SW_CTRL_MONITOR_RESET_RSALL_MASK) >> TSW_TSNPORT_SW_CTRL_MONITOR_RESET_RSALL_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: SW_CTRL_MONITOR_PARAM */
/*
 * RX_CNT_EN_VEC (RO)
 *
 * Vector of implemented RX counters. E.g. 0x000F means only the first 4 RX counter are available.
 */
#define TSW_TSNPORT_SW_CTRL_MONITOR_PARAM_RX_CNT_EN_VEC_MASK (0xFFFF0000UL)
#define TSW_TSNPORT_SW_CTRL_MONITOR_PARAM_RX_CNT_EN_VEC_SHIFT (16U)
#define TSW_TSNPORT_SW_CTRL_MONITOR_PARAM_RX_CNT_EN_VEC_GET(x) (((uint32_t)(x) & TSW_TSNPORT_SW_CTRL_MONITOR_PARAM_RX_CNT_EN_VEC_MASK) >> TSW_TSNPORT_SW_CTRL_MONITOR_PARAM_RX_CNT_EN_VEC_SHIFT)

/*
 * TX_CNT_EN_VEC (RO)
 *
 * Vector of implemented RX counters. E.g. 0x000F means only the first 4 RX counter are available.
 */
#define TSW_TSNPORT_SW_CTRL_MONITOR_PARAM_TX_CNT_EN_VEC_MASK (0xFF00U)
#define TSW_TSNPORT_SW_CTRL_MONITOR_PARAM_TX_CNT_EN_VEC_SHIFT (8U)
#define TSW_TSNPORT_SW_CTRL_MONITOR_PARAM_TX_CNT_EN_VEC_GET(x) (((uint32_t)(x) & TSW_TSNPORT_SW_CTRL_MONITOR_PARAM_TX_CNT_EN_VEC_MASK) >> TSW_TSNPORT_SW_CTRL_MONITOR_PARAM_TX_CNT_EN_VEC_SHIFT)

/*
 * CNTW (RO)
 *
 * Vector of implemented RX counters. E.g. 0x000F means only the first 4 RX counter
 * are available.
 */
#define TSW_TSNPORT_SW_CTRL_MONITOR_PARAM_CNTW_MASK (0x7FU)
#define TSW_TSNPORT_SW_CTRL_MONITOR_PARAM_CNTW_SHIFT (0U)
#define TSW_TSNPORT_SW_CTRL_MONITOR_PARAM_CNTW_GET(x) (((uint32_t)(x) & TSW_TSNPORT_SW_CTRL_MONITOR_PARAM_CNTW_MASK) >> TSW_TSNPORT_SW_CTRL_MONITOR_PARAM_CNTW_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: MONITOR_TX_COUNTER_TX_FGOOD */
/*
 * TX_FGOOD (RO)
 *
 * Good transmitted Frames to TX TSN-EP.
 */
#define TSW_TSNPORT_MONITOR_TX_COUNTER_TX_FGOOD_TX_FGOOD_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_MONITOR_TX_COUNTER_TX_FGOOD_TX_FGOOD_SHIFT (0U)
#define TSW_TSNPORT_MONITOR_TX_COUNTER_TX_FGOOD_TX_FGOOD_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MONITOR_TX_COUNTER_TX_FGOOD_TX_FGOOD_MASK) >> TSW_TSNPORT_MONITOR_TX_COUNTER_TX_FGOOD_TX_FGOOD_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: MONITOR_TX_COUNTER_TX_FERROR */
/*
 * TX_FERROR (RO)
 *
 * Transmitted Frames with Error to TX TSN-EP.
 */
#define TSW_TSNPORT_MONITOR_TX_COUNTER_TX_FERROR_TX_FERROR_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_MONITOR_TX_COUNTER_TX_FERROR_TX_FERROR_SHIFT (0U)
#define TSW_TSNPORT_MONITOR_TX_COUNTER_TX_FERROR_TX_FERROR_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MONITOR_TX_COUNTER_TX_FERROR_TX_FERROR_MASK) >> TSW_TSNPORT_MONITOR_TX_COUNTER_TX_FERROR_TX_FERROR_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: MONITOR_TX_COUNTER_TX_DROP_OVFL */
/*
 * TX_DROP_OVFL (RO)
 *
 * Dropped frames by full queue of TSN-EP.
 */
#define TSW_TSNPORT_MONITOR_TX_COUNTER_TX_DROP_OVFL_TX_DROP_OVFL_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_MONITOR_TX_COUNTER_TX_DROP_OVFL_TX_DROP_OVFL_SHIFT (0U)
#define TSW_TSNPORT_MONITOR_TX_COUNTER_TX_DROP_OVFL_TX_DROP_OVFL_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MONITOR_TX_COUNTER_TX_DROP_OVFL_TX_DROP_OVFL_MASK) >> TSW_TSNPORT_MONITOR_TX_COUNTER_TX_DROP_OVFL_TX_DROP_OVFL_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: MONITOR_RX_COUNTER_RX_FGOOD */
/*
 * RX_FGOOD (RO)
 *
 * Good received frame by ingress buffer.
 */
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_FGOOD_RX_FGOOD_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_FGOOD_RX_FGOOD_SHIFT (0U)
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_FGOOD_RX_FGOOD_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MONITOR_RX_COUNTER_RX_FGOOD_RX_FGOOD_MASK) >> TSW_TSNPORT_MONITOR_RX_COUNTER_RX_FGOOD_RX_FGOOD_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: MONITOR_RX_COUNTER_RX_FERROR */
/*
 * RX_FERROR (RO)
 *
 * Bad received frame by ingress buffer.
 */
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_FERROR_RX_FERROR_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_FERROR_RX_FERROR_SHIFT (0U)
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_FERROR_RX_FERROR_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MONITOR_RX_COUNTER_RX_FERROR_RX_FERROR_MASK) >> TSW_TSNPORT_MONITOR_RX_COUNTER_RX_FERROR_RX_FERROR_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: MONITOR_RX_COUNTER_RX_KNOWN */
/*
 * RX_KNOWN (RO)
 *
 * Number of frames passed ingress with hit by MAC Table. This includes Broadcast and non-relayed frames.
 */
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_KNOWN_RX_KNOWN_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_KNOWN_RX_KNOWN_SHIFT (0U)
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_KNOWN_RX_KNOWN_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MONITOR_RX_COUNTER_RX_KNOWN_RX_KNOWN_MASK) >> TSW_TSNPORT_MONITOR_RX_COUNTER_RX_KNOWN_RX_KNOWN_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: MONITOR_RX_COUNTER_RX_UNKNOWN */
/*
 * RX_UNKNOWN (RO)
 *
 * Number of frames passed ingress without hit by MAC table.
 */
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_UNKNOWN_RX_UNKNOWN_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_UNKNOWN_RX_UNKNOWN_SHIFT (0U)
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_UNKNOWN_RX_UNKNOWN_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MONITOR_RX_COUNTER_RX_UNKNOWN_RX_UNKNOWN_MASK) >> TSW_TSNPORT_MONITOR_RX_COUNTER_RX_UNKNOWN_RX_UNKNOWN_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: MONITOR_RX_COUNTER_RX_UC */
/*
 * RX_UC (RO)
 *
 * Number of unicast frames
 */
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_UC_RX_UC_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_UC_RX_UC_SHIFT (0U)
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_UC_RX_UC_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MONITOR_RX_COUNTER_RX_UC_RX_UC_MASK) >> TSW_TSNPORT_MONITOR_RX_COUNTER_RX_UC_RX_UC_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: MONITOR_RX_COUNTER_RX_INTERN */
/*
 * RX_INTERN (RO)
 *
 * Number of non-relay frames
 */
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_INTERN_RX_INTERN_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_INTERN_RX_INTERN_SHIFT (0U)
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_INTERN_RX_INTERN_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MONITOR_RX_COUNTER_RX_INTERN_RX_INTERN_MASK) >> TSW_TSNPORT_MONITOR_RX_COUNTER_RX_INTERN_RX_INTERN_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: MONITOR_RX_COUNTER_RX_BC */
/*
 * RX_BC (RO)
 *
 * Number of Broadcast frames
 */
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_BC_RX_BC_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_BC_RX_BC_SHIFT (0U)
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_BC_RX_BC_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MONITOR_RX_COUNTER_RX_BC_RX_BC_MASK) >> TSW_TSNPORT_MONITOR_RX_COUNTER_RX_BC_RX_BC_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: MONITOR_RX_COUNTER_RX_MULTI */
/*
 * RX_MULTI (RO)
 *
 * Number of Multicast frames
 */
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_MULTI_RX_MULTI_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_MULTI_RX_MULTI_SHIFT (0U)
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_MULTI_RX_MULTI_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MONITOR_RX_COUNTER_RX_MULTI_RX_MULTI_MASK) >> TSW_TSNPORT_MONITOR_RX_COUNTER_RX_MULTI_RX_MULTI_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: MONITOR_RX_COUNTER_RX_VLAN */
/*
 * RX_VLAN (RO)
 *
 * Number of VLAN tagged frames
 */
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_VLAN_RX_VLAN_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_VLAN_RX_VLAN_SHIFT (0U)
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_VLAN_RX_VLAN_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MONITOR_RX_COUNTER_RX_VLAN_RX_VLAN_MASK) >> TSW_TSNPORT_MONITOR_RX_COUNTER_RX_VLAN_RX_VLAN_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: MONITOR_RX_COUNTER_RX_DROP_OVFL */
/*
 * RX_DROP_OVFL (RO)
 *
 * Dropped frames by ingress overflow.
 */
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_DROP_OVFL_RX_DROP_OVFL_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_DROP_OVFL_RX_DROP_OVFL_SHIFT (0U)
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_DROP_OVFL_RX_DROP_OVFL_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MONITOR_RX_COUNTER_RX_DROP_OVFL_RX_DROP_OVFL_MASK) >> TSW_TSNPORT_MONITOR_RX_COUNTER_RX_DROP_OVFL_RX_DROP_OVFL_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: MONITOR_RX_COUNTER_RX_DROP_LU */
/*
 * RX_DROP_LU (RO)
 *
 * Dropped frames by LookUp decision.
 */
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_DROP_LU_RX_DROP_LU_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_DROP_LU_RX_DROP_LU_SHIFT (0U)
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_DROP_LU_RX_DROP_LU_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MONITOR_RX_COUNTER_RX_DROP_LU_RX_DROP_LU_MASK) >> TSW_TSNPORT_MONITOR_RX_COUNTER_RX_DROP_LU_RX_DROP_LU_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: MONITOR_RX_COUNTER_RX_DROP_ERR */
/*
 * RX_DROP_ERR (RO)
 *
 * Dropped frames with error by ingress. Possible in S&F mode or when frame is queued in ingress.
 */
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_DROP_ERR_RX_DROP_ERR_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_DROP_ERR_RX_DROP_ERR_SHIFT (0U)
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_DROP_ERR_RX_DROP_ERR_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MONITOR_RX_COUNTER_RX_DROP_ERR_RX_DROP_ERR_MASK) >> TSW_TSNPORT_MONITOR_RX_COUNTER_RX_DROP_ERR_RX_DROP_ERR_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: MONITOR_RX_COUNTER_RX_DROP_VLAN */
/*
 * RX_DROP_VLAN (RO)
 *
 * Dropped frames by incompatible VLAN.
 */
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_DROP_VLAN_RX_DROP_VLAN_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_DROP_VLAN_RX_DROP_VLAN_SHIFT (0U)
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_DROP_VLAN_RX_DROP_VLAN_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MONITOR_RX_COUNTER_RX_DROP_VLAN_RX_DROP_VLAN_MASK) >> TSW_TSNPORT_MONITOR_RX_COUNTER_RX_DROP_VLAN_RX_DROP_VLAN_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: MONITOR_RX_COUNTER_RX_FPE_FGOOD */
/*
 * RX_FPE_FGOOD (RO)
 *
 * Number of preemptable frames. Subset of RX_FGOOD
 */
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_FPE_FGOOD_RX_FPE_FGOOD_MASK (0xFFFFFFFFUL)
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_FPE_FGOOD_RX_FPE_FGOOD_SHIFT (0U)
#define TSW_TSNPORT_MONITOR_RX_COUNTER_RX_FPE_FGOOD_RX_FPE_FGOOD_GET(x) (((uint32_t)(x) & TSW_TSNPORT_MONITOR_RX_COUNTER_RX_FPE_FGOOD_RX_FPE_FGOOD_MASK) >> TSW_TSNPORT_MONITOR_RX_COUNTER_RX_FPE_FGOOD_RX_FPE_FGOOD_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: GPR_CTRL0 */
/*
 * RXCLK_DLY_SEL (RW)
 *
 * delay value of rxclk_delay_chain
 */
#define TSW_TSNPORT_GPR_CTRL0_RXCLK_DLY_SEL_MASK (0x3F00U)
#define TSW_TSNPORT_GPR_CTRL0_RXCLK_DLY_SEL_SHIFT (8U)
#define TSW_TSNPORT_GPR_CTRL0_RXCLK_DLY_SEL_SET(x) (((uint32_t)(x) << TSW_TSNPORT_GPR_CTRL0_RXCLK_DLY_SEL_SHIFT) & TSW_TSNPORT_GPR_CTRL0_RXCLK_DLY_SEL_MASK)
#define TSW_TSNPORT_GPR_CTRL0_RXCLK_DLY_SEL_GET(x) (((uint32_t)(x) & TSW_TSNPORT_GPR_CTRL0_RXCLK_DLY_SEL_MASK) >> TSW_TSNPORT_GPR_CTRL0_RXCLK_DLY_SEL_SHIFT)

/*
 * TXCLK_DLY_SEL (RW)
 *
 * delay value of txclk_delay_chain
 */
#define TSW_TSNPORT_GPR_CTRL0_TXCLK_DLY_SEL_MASK (0x3FU)
#define TSW_TSNPORT_GPR_CTRL0_TXCLK_DLY_SEL_SHIFT (0U)
#define TSW_TSNPORT_GPR_CTRL0_TXCLK_DLY_SEL_SET(x) (((uint32_t)(x) << TSW_TSNPORT_GPR_CTRL0_TXCLK_DLY_SEL_SHIFT) & TSW_TSNPORT_GPR_CTRL0_TXCLK_DLY_SEL_MASK)
#define TSW_TSNPORT_GPR_CTRL0_TXCLK_DLY_SEL_GET(x) (((uint32_t)(x) & TSW_TSNPORT_GPR_CTRL0_TXCLK_DLY_SEL_MASK) >> TSW_TSNPORT_GPR_CTRL0_TXCLK_DLY_SEL_SHIFT)

/* Bitfield definition for register of struct array TSNPORT: GPR_CTRL2 */
/*
 * MAC_SPEED (RW)
 *
 * mac speed
 */
#define TSW_TSNPORT_GPR_CTRL2_MAC_SPEED_MASK (0x300000UL)
#define TSW_TSNPORT_GPR_CTRL2_MAC_SPEED_SHIFT (20U)
#define TSW_TSNPORT_GPR_CTRL2_MAC_SPEED_SET(x) (((uint32_t)(x) << TSW_TSNPORT_GPR_CTRL2_MAC_SPEED_SHIFT) & TSW_TSNPORT_GPR_CTRL2_MAC_SPEED_MASK)
#define TSW_TSNPORT_GPR_CTRL2_MAC_SPEED_GET(x) (((uint32_t)(x) & TSW_TSNPORT_GPR_CTRL2_MAC_SPEED_MASK) >> TSW_TSNPORT_GPR_CTRL2_MAC_SPEED_SHIFT)

/*
 * PAD_OE_ETH_REFCLK (RW)
 *
 * refclock output enable when rmii
 */
#define TSW_TSNPORT_GPR_CTRL2_PAD_OE_ETH_REFCLK_MASK (0x80000UL)
#define TSW_TSNPORT_GPR_CTRL2_PAD_OE_ETH_REFCLK_SHIFT (19U)
#define TSW_TSNPORT_GPR_CTRL2_PAD_OE_ETH_REFCLK_SET(x) (((uint32_t)(x) << TSW_TSNPORT_GPR_CTRL2_PAD_OE_ETH_REFCLK_SHIFT) & TSW_TSNPORT_GPR_CTRL2_PAD_OE_ETH_REFCLK_MASK)
#define TSW_TSNPORT_GPR_CTRL2_PAD_OE_ETH_REFCLK_GET(x) (((uint32_t)(x) & TSW_TSNPORT_GPR_CTRL2_PAD_OE_ETH_REFCLK_MASK) >> TSW_TSNPORT_GPR_CTRL2_PAD_OE_ETH_REFCLK_SHIFT)

/*
 * PHY_INTF_SEL (RW)
 *
 * phy interface select
 */
#define TSW_TSNPORT_GPR_CTRL2_PHY_INTF_SEL_MASK (0xE000U)
#define TSW_TSNPORT_GPR_CTRL2_PHY_INTF_SEL_SHIFT (13U)
#define TSW_TSNPORT_GPR_CTRL2_PHY_INTF_SEL_SET(x) (((uint32_t)(x) << TSW_TSNPORT_GPR_CTRL2_PHY_INTF_SEL_SHIFT) & TSW_TSNPORT_GPR_CTRL2_PHY_INTF_SEL_MASK)
#define TSW_TSNPORT_GPR_CTRL2_PHY_INTF_SEL_GET(x) (((uint32_t)(x) & TSW_TSNPORT_GPR_CTRL2_PHY_INTF_SEL_MASK) >> TSW_TSNPORT_GPR_CTRL2_PHY_INTF_SEL_SHIFT)

/*
 * RMII_TXCLK_SEL (RW)
 *
 * txclk select control for RMII
 */
#define TSW_TSNPORT_GPR_CTRL2_RMII_TXCLK_SEL_MASK (0x400U)
#define TSW_TSNPORT_GPR_CTRL2_RMII_TXCLK_SEL_SHIFT (10U)
#define TSW_TSNPORT_GPR_CTRL2_RMII_TXCLK_SEL_SET(x) (((uint32_t)(x) << TSW_TSNPORT_GPR_CTRL2_RMII_TXCLK_SEL_SHIFT) & TSW_TSNPORT_GPR_CTRL2_RMII_TXCLK_SEL_MASK)
#define TSW_TSNPORT_GPR_CTRL2_RMII_TXCLK_SEL_GET(x) (((uint32_t)(x) & TSW_TSNPORT_GPR_CTRL2_RMII_TXCLK_SEL_MASK) >> TSW_TSNPORT_GPR_CTRL2_RMII_TXCLK_SEL_SHIFT)



/* HITMEM register group index macro definition */
#define TSW_HITMEM_HITMEM_REG_1 (0UL)
#define TSW_HITMEM_HITMEM_REG_2 (1UL)
#define TSW_HITMEM_HITMEM_REG_3 (2UL)
#define TSW_HITMEM_HITMEM_REG_4 (3UL)

/* QCI_CNT register group index macro definition */
#define TSW_QCI_CNT_CENTRAL_QCI_CNT0 (0UL)
#define TSW_QCI_CNT_CENTRAL_QCI_CNT1 (1UL)
#define TSW_QCI_CNT_CENTRAL_QCI_CNT2 (2UL)
#define TSW_QCI_CNT_CENTRAL_QCI_CNT3 (3UL)
#define TSW_QCI_CNT_CENTRAL_QCI_CNT4 (4UL)
#define TSW_QCI_CNT_CENTRAL_QCI_CNT5 (5UL)

/* EGFRCNT register group index macro definition */
#define TSW_EGFRCNT_CPU_PORT_EGRESS_FRER_CNT0 (0UL)
#define TSW_EGFRCNT_CPU_PORT_EGRESS_FRER_CNT1 (1UL)
#define TSW_EGFRCNT_CPU_PORT_EGRESS_FRER_CNT2 (2UL)
#define TSW_EGFRCNT_CPU_PORT_EGRESS_FRER_CNT3 (3UL)
#define TSW_EGFRCNT_CPU_PORT_EGRESS_FRER_CNT4 (4UL)
#define TSW_EGFRCNT_CPU_PORT_EGRESS_FRER_CNT5 (5UL)
#define TSW_EGFRCNT_CPU_PORT_EGRESS_FRER_CNT6 (6UL)
#define TSW_EGFRCNT_CPU_PORT_EGRESS_FRER_CNT7 (7UL)

/* IGFRCNT register group index macro definition */
#define TSW_IGFRCNT_CPU_PORT_IGRESS_FRER_CNT0 (0UL)
#define TSW_IGFRCNT_CPU_PORT_IGRESS_FRER_CNT1 (1UL)
#define TSW_IGFRCNT_CPU_PORT_IGRESS_FRER_CNT2 (2UL)
#define TSW_IGFRCNT_CPU_PORT_IGRESS_FRER_CNT3 (3UL)
#define TSW_IGFRCNT_CPU_PORT_IGRESS_FRER_CNT4 (4UL)
#define TSW_IGFRCNT_CPU_PORT_IGRESS_FRER_CNT5 (5UL)
#define TSW_IGFRCNT_CPU_PORT_IGRESS_FRER_CNT6 (6UL)
#define TSW_IGFRCNT_CPU_PORT_IGRESS_FRER_CNT7 (7UL)

/* MAC register group index macro definition */
#define TSW_MAC_EM1 (0UL)
#define TSW_MAC_PM1 (1UL)

/* TSYNTMR register group index macro definition */
#define TSW_TSNPORT_TSYNTMR_TSYN_TMR0 (0UL)
#define TSW_TSNPORT_TSYNTMR_TSYN_TMR1 (1UL)
#define TSW_TSNPORT_TSYNTMR_TSYN_TMR2 (2UL)
#define TSW_TSNPORT_TSYNTMR_TSYN_TMR3 (3UL)
#define TSW_TSNPORT_TSYNTMR_TSYN_TMR4 (4UL)

/* RXDATA register group index macro definition */
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD0 (0UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD1 (1UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD2 (2UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD3 (3UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD4 (4UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD5 (5UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD6 (6UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD7 (7UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD8 (8UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD9 (9UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD10 (10UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD11 (11UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD12 (12UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD13 (13UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD14 (14UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD15 (15UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD16 (16UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD17 (17UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD18 (18UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD19 (19UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD20 (20UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD21 (21UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD22 (22UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD23 (23UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD24 (24UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD25 (25UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD26 (26UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD27 (27UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD28 (28UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD29 (29UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD30 (30UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD31 (31UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD32 (32UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD33 (33UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD34 (34UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD35 (35UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD36 (36UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD37 (37UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD38 (38UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD39 (39UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD40 (40UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD41 (41UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD42 (42UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD43 (43UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD44 (44UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD45 (45UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD46 (46UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD47 (47UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD48 (48UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD49 (49UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD50 (50UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD51 (51UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD52 (52UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD53 (53UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD54 (54UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD55 (55UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD56 (56UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD57 (57UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD58 (58UL)
#define TSW_TSNPORT_RXDATA_TSYN_RXBUF_DATA_WORD59 (59UL)

/* TXDATA register group index macro definition */
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD0 (0UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD1 (1UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD2 (2UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD3 (3UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD4 (4UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD5 (5UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD6 (6UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD7 (7UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD8 (8UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD9 (9UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD10 (10UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD11 (11UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD12 (12UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD13 (13UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD14 (14UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD15 (15UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD16 (16UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD17 (17UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD18 (18UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD19 (19UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD20 (20UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD21 (21UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD22 (22UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD23 (23UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD24 (24UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD25 (25UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD26 (26UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD27 (27UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD28 (28UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD29 (29UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD30 (30UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD31 (31UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD32 (32UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD33 (33UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD34 (34UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD35 (35UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD36 (36UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD37 (37UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD38 (38UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD39 (39UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD40 (40UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD41 (41UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD42 (42UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD43 (43UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD44 (44UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD45 (45UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD46 (46UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD47 (47UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD48 (48UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD49 (49UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD50 (50UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD51 (51UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD52 (52UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD53 (53UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD54 (54UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD55 (55UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD56 (56UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD57 (57UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD58 (58UL)
#define TSW_TSNPORT_BIN_TXDATA_TSYN_TXBUF_BIN0_DATA_WORD59 (59UL)

/* BIN register group index macro definition */
#define TSW_BIN_TX0 (0UL)
#define TSW_BIN_TX1 (1UL)
#define TSW_BIN_TX2 (2UL)
#define TSW_BIN_TX3 (3UL)
#define TSW_BIN_TX4 (4UL)
#define TSW_BIN_TX5 (5UL)
#define TSW_BIN_TX6 (6UL)
#define TSW_BIN_TX7 (7UL)

/* MXSDU register group index macro definition */
#define TSW_TSNPORT_MXSDU_TSN_SHAPER_MXSDU0 (0UL)
#define TSW_TSNPORT_MXSDU_TSN_SHAPER_MXSDU1 (1UL)
#define TSW_TSNPORT_MXSDU_TSN_SHAPER_MXSDU2 (2UL)
#define TSW_TSNPORT_MXSDU_TSN_SHAPER_MXSDU3 (3UL)
#define TSW_TSNPORT_MXSDU_TSN_SHAPER_MXSDU4 (4UL)
#define TSW_TSNPORT_MXSDU_TSN_SHAPER_MXSDU5 (5UL)
#define TSW_TSNPORT_MXSDU_TSN_SHAPER_MXSDU6 (6UL)
#define TSW_TSNPORT_MXSDU_TSN_SHAPER_MXSDU7 (7UL)

/* TXSEL register group index macro definition */
#define TSW_TSNPORT_TXSEL_TSN_SHAPER_TXSEL0 (0UL)
#define TSW_TSNPORT_TXSEL_TSN_SHAPER_TXSEL1 (1UL)
#define TSW_TSNPORT_TXSEL_TSN_SHAPER_TXSEL2 (2UL)
#define TSW_TSNPORT_TXSEL_TSN_SHAPER_TXSEL3 (3UL)
#define TSW_TSNPORT_TXSEL_TSN_SHAPER_TXSEL4 (4UL)
#define TSW_TSNPORT_TXSEL_TSN_SHAPER_TXSEL5 (5UL)
#define TSW_TSNPORT_TXSEL_TSN_SHAPER_TXSEL6 (6UL)
#define TSW_TSNPORT_TXSEL_TSN_SHAPER_TXSEL7 (7UL)

/* IDSEL register group index macro definition */
#define TSW_TSNPORT_IDSEL_TSN_SHAPER_IDSEL0 (0UL)
#define TSW_TSNPORT_IDSEL_TSN_SHAPER_IDSEL1 (1UL)
#define TSW_TSNPORT_IDSEL_TSN_SHAPER_IDSEL2 (2UL)
#define TSW_TSNPORT_IDSEL_TSN_SHAPER_IDSEL3 (3UL)
#define TSW_TSNPORT_IDSEL_TSN_SHAPER_IDSEL04 (4UL)
#define TSW_TSNPORT_IDSEL_TSN_SHAPER_IDSEL5 (5UL)
#define TSW_TSNPORT_IDSEL_TSN_SHAPER_IDSEL6 (6UL)
#define TSW_TSNPORT_IDSEL_TSN_SHAPER_IDSEL7 (7UL)

/* MXTK register group index macro definition */
#define TSW_TSNPORT_MXTK_TSN_SHAPER_MXTK0 (0UL)
#define TSW_TSNPORT_MXTK_TSN_SHAPER_MXTK1 (1UL)
#define TSW_TSNPORT_MXTK_TSN_SHAPER_MXTK2 (2UL)
#define TSW_TSNPORT_MXTK_TSN_SHAPER_MXTK3 (3UL)
#define TSW_TSNPORT_MXTK_TSN_SHAPER_MXTK4 (4UL)
#define TSW_TSNPORT_MXTK_TSN_SHAPER_MXTK5 (5UL)
#define TSW_TSNPORT_MXTK_TSN_SHAPER_MXTK6 (6UL)
#define TSW_TSNPORT_MXTK_TSN_SHAPER_MXTK7 (7UL)

/* TXOV register group index macro definition */
#define TSW_TSNPORT_TXOV_TSN_SHAPER_TXOV0 (0UL)
#define TSW_TSNPORT_TXOV_TSN_SHAPER_TXOV1 (1UL)
#define TSW_TSNPORT_TXOV_TSN_SHAPER_TXOV2 (2UL)
#define TSW_TSNPORT_TXOV_TSN_SHAPER_TXOV3 (3UL)
#define TSW_TSNPORT_TXOV_TSN_SHAPER_TXOV4 (4UL)
#define TSW_TSNPORT_TXOV_TSN_SHAPER_TXOV5 (5UL)
#define TSW_TSNPORT_TXOV_TSN_SHAPER_TXOV6 (6UL)
#define TSW_TSNPORT_TXOV_TSN_SHAPER_TXOV7 (7UL)

/* SHACL register group index macro definition */
#define TSW_SHACL_ENT0 (0UL)
#define TSW_SHACL_ENT1 (1UL)
#define TSW_SHACL_ENT2 (2UL)
#define TSW_SHACL_ENT3 (3UL)
#define TSW_SHACL_ENT4 (4UL)
#define TSW_SHACL_ENT5 (5UL)
#define TSW_SHACL_ENT6 (6UL)
#define TSW_SHACL_ENT7 (7UL)
#define TSW_SHACL_ENT8 (8UL)
#define TSW_SHACL_ENT9 (9UL)
#define TSW_SHACL_ENT10 (10UL)
#define TSW_SHACL_ENT11 (11UL)
#define TSW_SHACL_ENT12 (12UL)
#define TSW_SHACL_ENT13 (13UL)
#define TSW_SHACL_ENT14 (14UL)
#define TSW_SHACL_ENT15 (15UL)
#define TSW_SHACL_ENT16 (16UL)
#define TSW_SHACL_ENT17 (17UL)
#define TSW_SHACL_ENT18 (18UL)
#define TSW_SHACL_ENT19 (19UL)
#define TSW_SHACL_ENT20 (20UL)
#define TSW_SHACL_ENT21 (21UL)
#define TSW_SHACL_ENT22 (22UL)
#define TSW_SHACL_ENT23 (23UL)
#define TSW_SHACL_ENT24 (24UL)
#define TSW_SHACL_ENT25 (25UL)
#define TSW_SHACL_ENT26 (26UL)
#define TSW_SHACL_ENT27 (27UL)
#define TSW_SHACL_ENT28 (28UL)
#define TSW_SHACL_ENT29 (29UL)
#define TSW_SHACL_ENT30 (30UL)
#define TSW_SHACL_ENT31 (31UL)
#define TSW_SHACL_ENT32 (32UL)
#define TSW_SHACL_ENT33 (33UL)
#define TSW_SHACL_ENT34 (34UL)
#define TSW_SHACL_ENT35 (35UL)
#define TSW_SHACL_ENT36 (36UL)
#define TSW_SHACL_ENT37 (37UL)
#define TSW_SHACL_ENT38 (38UL)
#define TSW_SHACL_ENT39 (39UL)
#define TSW_SHACL_ENT40 (40UL)
#define TSW_SHACL_ENT41 (41UL)
#define TSW_SHACL_ENT42 (42UL)
#define TSW_SHACL_ENT43 (43UL)
#define TSW_SHACL_ENT44 (44UL)
#define TSW_SHACL_ENT45 (45UL)
#define TSW_SHACL_ENT46 (46UL)
#define TSW_SHACL_ENT47 (47UL)
#define TSW_SHACL_ENT48 (48UL)
#define TSW_SHACL_ENT49 (49UL)
#define TSW_SHACL_ENT50 (50UL)
#define TSW_SHACL_ENT51 (51UL)
#define TSW_SHACL_ENT52 (52UL)
#define TSW_SHACL_ENT53 (53UL)
#define TSW_SHACL_ENT54 (54UL)
#define TSW_SHACL_ENT55 (55UL)
#define TSW_SHACL_ENT56 (56UL)
#define TSW_SHACL_ENT57 (57UL)
#define TSW_SHACL_ENT58 (58UL)
#define TSW_SHACL_ENT59 (59UL)
#define TSW_SHACL_ENT60 (60UL)
#define TSW_SHACL_ENT61 (61UL)
#define TSW_SHACL_ENT62 (62UL)
#define TSW_SHACL_ENT63 (63UL)
#define TSW_SHACL_ENT64 (64UL)
#define TSW_SHACL_ENT65 (65UL)
#define TSW_SHACL_ENT66 (66UL)
#define TSW_SHACL_ENT67 (67UL)
#define TSW_SHACL_ENT68 (68UL)
#define TSW_SHACL_ENT69 (69UL)
#define TSW_SHACL_ENT70 (70UL)
#define TSW_SHACL_ENT71 (71UL)
#define TSW_SHACL_ENT72 (72UL)
#define TSW_SHACL_ENT73 (73UL)
#define TSW_SHACL_ENT74 (74UL)
#define TSW_SHACL_ENT75 (75UL)
#define TSW_SHACL_ENT76 (76UL)
#define TSW_SHACL_ENT77 (77UL)
#define TSW_SHACL_ENT78 (78UL)
#define TSW_SHACL_ENT79 (79UL)
#define TSW_SHACL_ENT80 (80UL)
#define TSW_SHACL_ENT81 (81UL)
#define TSW_SHACL_ENT82 (82UL)
#define TSW_SHACL_ENT83 (83UL)
#define TSW_SHACL_ENT84 (84UL)
#define TSW_SHACL_ENT85 (85UL)
#define TSW_SHACL_ENT86 (86UL)
#define TSW_SHACL_ENT87 (87UL)
#define TSW_SHACL_ENT88 (88UL)
#define TSW_SHACL_ENT89 (89UL)
#define TSW_SHACL_ENT90 (90UL)
#define TSW_SHACL_ENT91 (91UL)
#define TSW_SHACL_ENT92 (92UL)
#define TSW_SHACL_ENT93 (93UL)
#define TSW_SHACL_ENT94 (94UL)
#define TSW_SHACL_ENT95 (95UL)
#define TSW_SHACL_ENT96 (96UL)
#define TSW_SHACL_ENT97 (97UL)
#define TSW_SHACL_ENT98 (98UL)
#define TSW_SHACL_ENT99 (99UL)
#define TSW_SHACL_ENT100 (100UL)
#define TSW_SHACL_ENT101 (101UL)
#define TSW_SHACL_ENT102 (102UL)
#define TSW_SHACL_ENT103 (103UL)
#define TSW_SHACL_ENT104 (104UL)
#define TSW_SHACL_ENT105 (105UL)
#define TSW_SHACL_ENT106 (106UL)
#define TSW_SHACL_ENT107 (107UL)
#define TSW_SHACL_ENT108 (108UL)
#define TSW_SHACL_ENT109 (109UL)
#define TSW_SHACL_ENT110 (110UL)
#define TSW_SHACL_ENT111 (111UL)
#define TSW_SHACL_ENT112 (112UL)
#define TSW_SHACL_ENT113 (113UL)
#define TSW_SHACL_ENT114 (114UL)
#define TSW_SHACL_ENT115 (115UL)
#define TSW_SHACL_ENT116 (116UL)
#define TSW_SHACL_ENT117 (117UL)
#define TSW_SHACL_ENT118 (118UL)
#define TSW_SHACL_ENT119 (119UL)
#define TSW_SHACL_ENT120 (120UL)
#define TSW_SHACL_ENT121 (121UL)
#define TSW_SHACL_ENT122 (122UL)
#define TSW_SHACL_ENT123 (123UL)
#define TSW_SHACL_ENT124 (124UL)
#define TSW_SHACL_ENT125 (125UL)
#define TSW_SHACL_ENT126 (126UL)
#define TSW_SHACL_ENT127 (127UL)
#define TSW_SHACL_ENT128 (128UL)
#define TSW_SHACL_ENT129 (129UL)
#define TSW_SHACL_ENT130 (130UL)
#define TSW_SHACL_ENT131 (131UL)
#define TSW_SHACL_ENT132 (132UL)
#define TSW_SHACL_ENT133 (133UL)
#define TSW_SHACL_ENT134 (134UL)
#define TSW_SHACL_ENT135 (135UL)
#define TSW_SHACL_ENT136 (136UL)
#define TSW_SHACL_ENT137 (137UL)
#define TSW_SHACL_ENT138 (138UL)
#define TSW_SHACL_ENT139 (139UL)
#define TSW_SHACL_ENT140 (140UL)
#define TSW_SHACL_ENT141 (141UL)
#define TSW_SHACL_ENT142 (142UL)
#define TSW_SHACL_ENT143 (143UL)
#define TSW_SHACL_ENT144 (144UL)
#define TSW_SHACL_ENT145 (145UL)
#define TSW_SHACL_ENT146 (146UL)
#define TSW_SHACL_ENT147 (147UL)
#define TSW_SHACL_ENT148 (148UL)
#define TSW_SHACL_ENT149 (149UL)
#define TSW_SHACL_ENT150 (150UL)
#define TSW_SHACL_ENT151 (151UL)
#define TSW_SHACL_ENT152 (152UL)
#define TSW_SHACL_ENT153 (153UL)
#define TSW_SHACL_ENT154 (154UL)
#define TSW_SHACL_ENT155 (155UL)
#define TSW_SHACL_ENT156 (156UL)
#define TSW_SHACL_ENT157 (157UL)
#define TSW_SHACL_ENT158 (158UL)
#define TSW_SHACL_ENT159 (159UL)
#define TSW_SHACL_ENT160 (160UL)
#define TSW_SHACL_ENT161 (161UL)
#define TSW_SHACL_ENT162 (162UL)
#define TSW_SHACL_ENT163 (163UL)
#define TSW_SHACL_ENT164 (164UL)
#define TSW_SHACL_ENT165 (165UL)
#define TSW_SHACL_ENT166 (166UL)
#define TSW_SHACL_ENT167 (167UL)
#define TSW_SHACL_ENT168 (168UL)
#define TSW_SHACL_ENT169 (169UL)
#define TSW_SHACL_ENT170 (170UL)
#define TSW_SHACL_ENT171 (171UL)
#define TSW_SHACL_ENT172 (172UL)
#define TSW_SHACL_ENT173 (173UL)
#define TSW_SHACL_ENT174 (174UL)
#define TSW_SHACL_ENT175 (175UL)
#define TSW_SHACL_ENT176 (176UL)
#define TSW_SHACL_ENT177 (177UL)
#define TSW_SHACL_ENT178 (178UL)
#define TSW_SHACL_ENT179 (179UL)
#define TSW_SHACL_ENT180 (180UL)
#define TSW_SHACL_ENT181 (181UL)
#define TSW_SHACL_ENT182 (182UL)
#define TSW_SHACL_ENT183 (183UL)
#define TSW_SHACL_ENT184 (184UL)
#define TSW_SHACL_ENT185 (185UL)
#define TSW_SHACL_ENT186 (186UL)
#define TSW_SHACL_ENT187 (187UL)
#define TSW_SHACL_ENT188 (188UL)
#define TSW_SHACL_ENT189 (189UL)
#define TSW_SHACL_ENT190 (190UL)
#define TSW_SHACL_ENT191 (191UL)
#define TSW_SHACL_ENT192 (192UL)
#define TSW_SHACL_ENT193 (193UL)
#define TSW_SHACL_ENT194 (194UL)
#define TSW_SHACL_ENT195 (195UL)
#define TSW_SHACL_ENT196 (196UL)
#define TSW_SHACL_ENT197 (197UL)
#define TSW_SHACL_ENT198 (198UL)
#define TSW_SHACL_ENT199 (199UL)
#define TSW_SHACL_ENT200 (200UL)
#define TSW_SHACL_ENT201 (201UL)
#define TSW_SHACL_ENT202 (202UL)
#define TSW_SHACL_ENT203 (203UL)
#define TSW_SHACL_ENT204 (204UL)
#define TSW_SHACL_ENT205 (205UL)
#define TSW_SHACL_ENT206 (206UL)
#define TSW_SHACL_ENT207 (207UL)
#define TSW_SHACL_ENT208 (208UL)
#define TSW_SHACL_ENT209 (209UL)
#define TSW_SHACL_ENT210 (210UL)
#define TSW_SHACL_ENT211 (211UL)
#define TSW_SHACL_ENT212 (212UL)
#define TSW_SHACL_ENT213 (213UL)
#define TSW_SHACL_ENT214 (214UL)
#define TSW_SHACL_ENT215 (215UL)
#define TSW_SHACL_ENT216 (216UL)
#define TSW_SHACL_ENT217 (217UL)
#define TSW_SHACL_ENT218 (218UL)
#define TSW_SHACL_ENT219 (219UL)
#define TSW_SHACL_ENT220 (220UL)
#define TSW_SHACL_ENT221 (221UL)
#define TSW_SHACL_ENT222 (222UL)
#define TSW_SHACL_ENT223 (223UL)
#define TSW_SHACL_ENT224 (224UL)
#define TSW_SHACL_ENT225 (225UL)
#define TSW_SHACL_ENT226 (226UL)
#define TSW_SHACL_ENT227 (227UL)
#define TSW_SHACL_ENT228 (228UL)
#define TSW_SHACL_ENT229 (229UL)
#define TSW_SHACL_ENT230 (230UL)
#define TSW_SHACL_ENT231 (231UL)
#define TSW_SHACL_ENT232 (232UL)
#define TSW_SHACL_ENT233 (233UL)
#define TSW_SHACL_ENT234 (234UL)
#define TSW_SHACL_ENT235 (235UL)
#define TSW_SHACL_ENT236 (236UL)
#define TSW_SHACL_ENT237 (237UL)
#define TSW_SHACL_ENT238 (238UL)
#define TSW_SHACL_ENT239 (239UL)
#define TSW_SHACL_ENT240 (240UL)
#define TSW_SHACL_ENT241 (241UL)
#define TSW_SHACL_ENT242 (242UL)
#define TSW_SHACL_ENT243 (243UL)
#define TSW_SHACL_ENT244 (244UL)
#define TSW_SHACL_ENT245 (245UL)
#define TSW_SHACL_ENT246 (246UL)
#define TSW_SHACL_ENT247 (247UL)
#define TSW_SHACL_ENT248 (248UL)
#define TSW_SHACL_ENT249 (249UL)
#define TSW_SHACL_ENT250 (250UL)
#define TSW_SHACL_ENT251 (251UL)
#define TSW_SHACL_ENT252 (252UL)
#define TSW_SHACL_ENT253 (253UL)
#define TSW_SHACL_ENT254 (254UL)
#define TSW_SHACL_ENT255 (255UL)

/* RXFIFO register group index macro definition */
#define TSW_RXFIFO_E1 (0UL)
#define TSW_RXFIFO_P1 (1UL)

/* TSNPORT register group index macro definition */
#define TSW_TSNPORT_PORT1 (0UL)
#define TSW_TSNPORT_PORT2 (1UL)
#define TSW_TSNPORT_PORT3 (2UL)


#endif /* HPM_TSW_H */
