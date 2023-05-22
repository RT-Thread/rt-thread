/**
    *****************************************************************************
    * @file     cmem7_eth.c
    *
    * @brief    CMEM7 ethernet source file
    *
    *
    * @version  V2.0
    * @date     3. September 2014
    *
    * @note
    *
    *****************************************************************************
    * @attention
    *
    * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
    * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
    * TIME. AS A RESULT, CAPITAL-MICRO SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
    * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
    * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
    * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
    *
    * <h2><center>&copy; COPYRIGHT 2013 Capital-micro </center></h2>
    *****************************************************************************
    */

#include "cmem7_eth.h"
#include "cmem7_misc.h"

typedef struct {
    union {
    uint32_t  TX0;

        struct {
            uint32_t                                :  1;
            uint32_t UNDERFLOW_ERR  :  1;    /*!< [OUT] Underflow error                                                     */
            uint32_t                                :  1;
            uint32_t COLLISION_CNT  :  4;        /*!< [OUT] Collision count                                       */
            uint32_t                                :  1;
            uint32_t EX_COLLISION   :  1;        /*!< [OUT] Excessive collision error                         */
            uint32_t LATE_COLLISION :  1;        /*!< [OUT] Late collision error                              */
            uint32_t NO_CARRIER     :  1;        /*!< [OUT] No carrier error                                    */
            uint32_t LOSS_CARRIER   :  1;        /*!< [OUT] loss of carrier error                           */
            uint32_t PAYLOAD_ERR        :  1;        /*!< [OUT] IP payload error                                    */
            uint32_t                                :  2;
            uint32_t ERR_SUM                :  1;        /*!< [OUT] Error summary                                           */
            uint32_t HEADER_ERR         :  1;        /*!< [OUT] IP header error                                         */
            uint32_t                                :  3;
            uint32_t TCH                        :  1;        /*!< Second Address Chained                                */
            uint32_t                                :  4;
            uint32_t TTSE           :  1;    /*!< enables IEEE1588 hardware timestamping in first segment */
            uint32_t                              :  2;
            uint32_t FS             :  1;    /*!< first segment flag                                    */
            uint32_t LS             :  1;    /*!< last segment flag                                     */
            uint32_t IC             :  1;    /*!< Interrupt on Completion                               */
            uint32_t OWN            :  1;    /*!< Descriptor is owned by self or hardware               */
        } TX0_b;
    } TX_0;

    union {
    uint32_t  TX1;

        struct {
            uint32_t SIZE                       : 13;    /*!< buffer size                                           */
            uint32_t                : 19;
        } TX1_b;
    } TX_1;

    uint32_t bufAddr;
    uint32_t nextDescAddr;
  uint64_t reserved;
    uint64_t timeStamp;                                  /*!< time stamp in the last segment                         */
} INNER_ETH_TX_DESC;

typedef struct {
    union {
    uint32_t  RX0;

        struct {
            uint32_t                                :  1;
            uint32_t CRC_ERR        :  1;    /*!< [OUT] CRC error while last segment                        */
            uint32_t                                :  5;
            uint32_t TTSE           :  1;    /*!< timestamp available while last segment                */
            uint32_t LS             :  1;    /*!< last segment flag                                     */
            uint32_t FS             :  1;    /*!< first segment flag                                    */
            uint32_t                                :  1;
            uint32_t OVERFLOW_ERR   :  1;    /*!< [OUT] FIFO overflow while last segment                */
            uint32_t LENGTH_ERR     :  1;    /*!< [OUT] length error while last segment                 */
            uint32_t                                :  2;
            uint32_t ERR_SUM        :  1;    /*!< [OUT] Error summary while last segment                */
            uint32_t FL             : 14;    /*!< frame length while last segment                       */
            uint32_t                    :  1;
            uint32_t OWN            :  1;    /*!< Descriptor is owned by self or hardware               */
        } RX0_b;
    } RX_0;

    union {
    uint32_t  RX1;

        struct {
            uint32_t SIZE                       : 13;    /*!< buffer size                                           */
            uint32_t                    :  1;
            uint32_t RCH            :  1;    /*!< Second Address Chained                                */
            uint32_t                    : 16;
            uint32_t DIC              :  1;      /*!< Disable interrupt on Completion                       */
        } RX1_b;
    } RX_1;

    uint32_t bufAddr;
    uint32_t nextDescAddr;
  uint64_t reserved;
    uint64_t timeStamp;                                  /*!< time stamp while the last segment                     */
} INNER_ETH_RX_DESC;


#define PHY_OP_READ                 0x0
#define PHY_OP_WRITE                0x1

#define ETH_BURST_MODE_FIXED        0x0
#define ETH_BURST_MODE_UNDERSIZE    0x1
#define ETH_BURST_MODE_MIXED        0x2

#define ETH_BURST_LENGTH_MIN        1
#define ETH_BURST_LENGTH_MAX        256
#define ETH_BURST_LENGTH_8X_SWITCH  32
#define ETH_BURST_LENGTH_8X_MIN     8

#define ETH_DMA_ARBITRATION_ROUND_ROBIN         0x0
#define ETH_DMA_ARBITRATION_FIXED_PRIORITY  0x1

#define ETH_RX_THRESHOLD_64         0x0
#define ETH_RX_THRESHOLD_32         0x1
#define ETH_RX_THRESHOLD_96         0x2
#define ETH_RX_THRESHOLD_128        0x3

#define ETH_TX_THRESHOLD_64         0x0
#define ETH_TX_THRESHOLD_128        0x1
#define ETH_TX_THRESHOLD_192        0x2
#define ETH_TX_THRESHOLD_256        0x3
#define ETH_TX_THRESHOLD_40         0x4
#define ETH_TX_THRESHOLD_32         0x5
#define ETH_TX_THRESHOLD_24         0x6
#define ETH_TX_THRESHOLD_16         0x7

#define ETH_INT_ABNORMAL_SUMMARY    0x8000
#define ETH_INT_NORMAL_SUMMARY      0x10000

#define IS_ETH_INT_NORMAL(INT)      ((INT & ETH_INT_TX_COMPLETE_FRAME)  || \
                                                                         (INT & ETH_INT_TX_BUF_UNAVAI)          || \
                                                                         (INT & ETH_INT_RX_COMPLETE_FRAME))

#define IS_ETH_INT_ABNORMAL(INT)    ((INT & ETH_INT_TX_STOP)                        || \
                                                                         (INT & ETH_INT_RX_OVERFLOW)        || \
                                                                         (INT & ETH_INT_TX_UNDERFLOW)       || \
                                                                         (INT & ETH_INT_RX_BUF_UNAVAI)          || \
                                                                         (INT & ETH_INT_RX_STOP)                        || \
                                                                         (INT & ETH_INT_BUS_FATAL_ERROR))

#define ETH_PREAMBLE_7_BYTE         0x0
#define ETH_PREAMBLE_5_BYTE         0x1
#define ETH_PREAMBLE_3_BYTE         0x2

#define ETH_LINE_SPEED_1000M_BPS        0x0
#define ETH_LINE_SPEED_10_100M_BPS  0x1

#define ETH_EXACT_SPEED_10M_BPS         0x0
#define ETH_EXACT_SPEED_100M_BPS        0x1

#define ETH_SOURCE_ADDR_REPLACE     0x3

#define ETH_PASS_CTRL_FRAME_ALL     0x0

#define ETH_DESC_OWN_BY_SELF        0x0
#define ETH_DESC_OWN_BY_HW          0x1


static void mac_SwReset(void) {
    ETH->BUS_MODE_b.SWR = 1;
    while (ETH->BUS_MODE_b.SWR) ;
    while (ETH->AHB_STATUS_b.BUSY) ;
}

static void mac_SetConfig(ETH_InitTypeDef *init) {
    ETH->CONFIG_b.PRELEN = ETH_PREAMBLE_7_BYTE;
    ETH->CONFIG_b.RX_EN = init->ETH_RxEn;
    ETH->CONFIG_b.TX_EN = init->ETH_TxEn;
    ETH->CONFIG_b.DC_EN = FALSE;
    ETH->CONFIG_b.ACS = FALSE;
    ETH->CONFIG_b.LUD = init->ETH_LinkUp;
    ETH->CONFIG_b.IPC = init->ETH_ChecksumOffload;
    ETH->CONFIG_b.DM = init->ETH_Duplex;
    ETH->CONFIG_b.LM = FALSE;
    ETH->MMCRIMR = 0xFFFFFFFF;
    ETH->MMCTIMR = 0xFFFFFFFF;
    ETH->MMCIRCOIM = 0xFFFFFFFF;

    if (init->ETH_Speed == ETH_SPEED_10M) {
        ETH->CONFIG_b.FES = ETH_EXACT_SPEED_10M_BPS;
        ETH->CONFIG_b.PS = ETH_LINE_SPEED_10_100M_BPS;
    } else if (init->ETH_Speed == ETH_SPEED_100M) {
        ETH->CONFIG_b.FES = ETH_EXACT_SPEED_100M_BPS;
        ETH->CONFIG_b.PS = ETH_LINE_SPEED_10_100M_BPS;
    } else {
        ETH->CONFIG_b.FES = ETH_EXACT_SPEED_100M_BPS;
        ETH->CONFIG_b.PS = ETH_LINE_SPEED_1000M_BPS;
    }

    ETH->CONFIG_b.JE = init->ETH_JumboFrame;

    ETH->CONFIG_b.JD = TRUE;
    ETH->CONFIG_b.WD = TRUE;
    ETH->CONFIG_b.TC = FALSE;
    ETH->CONFIG_b.CST = TRUE;
    ETH->CONFIG_b.TWOKPE = FALSE;
    ETH->CONFIG_b.SARC = ETH_SOURCE_ADDR_REPLACE;
}

static void mac_SetMacAddr(uint8_t *mac) {
    ETH->ADDR0_HIGH = (mac[5] << 8) | mac[4];
    ETH->ADDR0_LOW = (mac[3] << 24) | (mac[2] << 16) |
          (mac[1] << 8) | mac[0];
}

static void mac_SetBurst(
  uint8_t mode, uint32_t rxBurstLen, uint32_t txBurstLen) {
    ETH->BUS_MODE_b.RIB = FALSE;
    ETH->BUS_MODE_b.AAL = FALSE;

    if (mode == ETH_BURST_MODE_FIXED) {
        ETH->BUS_MODE_b.FB = TRUE;
        ETH->BUS_MODE_b.MB = FALSE;
    } else if (mode == ETH_BURST_MODE_UNDERSIZE) {
        ETH->BUS_MODE_b.FB = FALSE;
        ETH->BUS_MODE_b.MB = FALSE;
    } else {
        ETH->BUS_MODE_b.FB = TRUE;
        ETH->BUS_MODE_b.MB = TRUE;
    }

    rxBurstLen = 1 << rxBurstLen;
    rxBurstLen = (rxBurstLen > ETH_BURST_LENGTH_MAX) ?
      ETH_BURST_LENGTH_MAX : rxBurstLen;

    txBurstLen = 1 << txBurstLen;
    txBurstLen = (txBurstLen > ETH_BURST_LENGTH_MAX) ?
      ETH_BURST_LENGTH_MAX : txBurstLen;

    // Regrading PBLx8 register, if one of PBL and RPBL is more than
    // ETH_BURST_LENGTH_8X_SWITCH, another should be more than
    // ETH_BURST_LENGTH_8X_MIN.
    // If not, the greater level down to ETH_BURST_LENGTH_8X_SWITCH.
    if ((txBurstLen < ETH_BURST_LENGTH_8X_MIN) ||
        (rxBurstLen < ETH_BURST_LENGTH_8X_MIN)) {
        if (rxBurstLen > ETH_BURST_LENGTH_8X_SWITCH) {
            rxBurstLen = ETH_BURST_LENGTH_8X_SWITCH;
        }

        if (txBurstLen > ETH_BURST_LENGTH_8X_SWITCH) {
            txBurstLen = ETH_BURST_LENGTH_8X_SWITCH;
        }
    }

    ETH->BUS_MODE_b.USP = (rxBurstLen == txBurstLen) ? FALSE : TRUE;
  if ((txBurstLen > ETH_BURST_LENGTH_8X_SWITCH) ||
        (rxBurstLen > ETH_BURST_LENGTH_8X_SWITCH)) {
        ETH->BUS_MODE_b.PBLx8 = TRUE;
    } else {
        ETH->BUS_MODE_b.PBLx8 = FALSE;
    }

    if (ETH->BUS_MODE_b.PBLx8) {
        ETH->BUS_MODE_b.RPBL = rxBurstLen >> 3;
        ETH->BUS_MODE_b.PBL = txBurstLen >> 3;
    } else {
        ETH->BUS_MODE_b.RPBL = rxBurstLen;
        ETH->BUS_MODE_b.PBL = txBurstLen;
    }
}

static void mac_SetPriority(BOOL isRxPrior, uint8_t priorityRate) {
  ETH->BUS_MODE_b.PRWG = 0;
    ETH->BUS_MODE_b.DA = ETH_DMA_ARBITRATION_ROUND_ROBIN;

    ETH->BUS_MODE_b.TXPR = isRxPrior ? FALSE : TRUE;
    ETH->BUS_MODE_b.PR = priorityRate;
}

static void mac_SetDescMode(BOOL isAlternate, uint8_t gap) {
  ETH->BUS_MODE_b.ATDS = isAlternate;
    ETH->BUS_MODE_b.DSL = gap;
}

static void mac_SetOpertionMode(void) {
    ETH->OPERATION_b.OSF = FALSE;
    ETH->OPERATION_b.RT = ETH_RX_THRESHOLD_32;
    ETH->OPERATION_b.RSF = FALSE;

    ETH->OPERATION_b.DGF = FALSE;
    ETH->OPERATION_b.FUF = FALSE;
    ETH->OPERATION_b.FEF = FALSE;
    ETH->OPERATION_b.TT = ETH_TX_THRESHOLD_64;
    ETH->OPERATION_b.TSF = FALSE;

    ETH->OPERATION_b.FTF = TRUE;
    ETH->OPERATION_b.DFF = TRUE;
}

static void mac_SetFrameFilter(ETH_FrameFilter *filter) {
    ETH->FF_b.PR = FALSE;
    ETH->FF_b.HUC = FALSE;
    ETH->FF_b.HMC = FALSE;
    ETH->FF_b.DAIF = FALSE;
    ETH->FF_b.PM = FALSE;
    ETH->FF_b.DBF = FALSE;
    ETH->FF_b.PCF = ETH_PASS_CTRL_FRAME_ALL;
    ETH->FF_b.SAIF = FALSE;
    ETH->FF_b.SAF = FALSE;
    ETH->FF_b.HPF = FALSE;
    ETH->FF_b.VTFE = FALSE;
    ETH->FF_b.IPFE = FALSE;
    ETH->FF_b.DNTU = FALSE;
    ETH->FF_b.RA = FALSE;//TRUE

    // receive all
    if (!filter) {
        return ;
    }

    // broadcast
    if (filter->ETH_BroadcastFilterEnable) {
        ETH->FF_b.RA = FALSE;
        ETH->FF_b.DBF = TRUE;
    }

    // DA
    if (filter->ETH_OwnFilterEnable) {
        ETH->FF_b.RA = FALSE;
        ETH->FF_b.DAIF = filter->ETH_SelfDrop;
    }

    // SA
    if (filter->ETH_SourceFilterEnable) {
        uint32_t value;

    ETH->FF_b.RA = FALSE;
        ETH->FF_b.SAF = TRUE;
        ETH->FF_b.SAIF = filter->ETH_SourceDrop;
        ETH->ADDR1_HIGH_b.AE = TRUE;
        ETH->ADDR1_HIGH_b.SA = TRUE;
    ETH->ADDR1_HIGH_b.ADDR =
            (filter->ETH_SourceMacAddr[5] << 8) | filter->ETH_SourceMacAddr[4];


//      value = (filter->ETH_SourceMacAddr[5] << 8) | filter->ETH_SourceMacAddr[4];
//     CMEM7_BFI(&(ETH->ADDR1_HIGH), value, 0, 16);
    ETH->ADDR1_LOW = (filter->ETH_SourceMacAddr[3] << 24) |
            (filter->ETH_SourceMacAddr[2] << 16) |
          (filter->ETH_SourceMacAddr[1] << 8) |
            filter->ETH_SourceMacAddr[0];
    }
}

static void mac_setFlowControl(void) {
  ETH->FC_b.FCB = FALSE;
    ETH->FC_b.TFE = FALSE;//TRUE
    ETH->FC_b.RFE = FALSE;//TRUE
    ETH->FC_b.UP = FALSE;//TRUE
}

uint32_t ETH_PhyRead(uint32_t phyAddr, uint32_t phyReg) {
    ETH->GMII_ADDR_b.PA = phyAddr;
    ETH->GMII_ADDR_b.GR = phyReg;
    ETH->GMII_ADDR_b.GW = PHY_OP_READ;

    ETH->GMII_ADDR_b.BUSY = TRUE;
    while (ETH->GMII_ADDR_b.BUSY) ;

    return ETH->GMII_DATA;
}

void ETH_PhyWrite(uint32_t phyAddr, uint32_t phyReg, uint32_t data) {
    ETH->GMII_ADDR_b.PA = phyAddr;
    ETH->GMII_ADDR_b.GR = phyReg;
    ETH->GMII_ADDR_b.GW = PHY_OP_WRITE;
  ETH->GMII_DATA = data;

    ETH->GMII_ADDR_b.BUSY = TRUE;
    while (ETH->GMII_ADDR_b.BUSY) ;
}

void ETH_StructInit(ETH_InitTypeDef* init)
{
    init->ETH_Speed = ETH_SPEED_10M;
    init->ETH_Duplex = ETH_DUPLEX_FULL;
    init->ETH_JumboFrame = FALSE;
    init->ETH_LinkUp = FALSE;
    init->ETH_RxEn = TRUE;
    init->ETH_TxEn = TRUE;
    init->ETH_ChecksumOffload = FALSE;
    init->ETH_Filter = 0;
    init->ETH_MacAddr[0] = 0;
    init->ETH_MacAddr[1] = 0;
    init->ETH_MacAddr[2] = 0;
    init->ETH_MacAddr[3] = 0;
    init->ETH_MacAddr[4] = 0;
    init->ETH_MacAddr[5] = 0;

}
BOOL ETH_Init(ETH_InitTypeDef *init) {
    assert_param(init);
    assert_param(IS_ETH_SPEED(init->ETH_Speed));
    assert_param(IS_ETH_DUPLEX(init->ETH_Duplex));

    mac_SwReset();
    mac_SetConfig(init);
    mac_SetMacAddr(init->ETH_MacAddr);

    mac_SetBurst(ETH_BURST_MODE_MIXED, 3, 4);
    mac_SetPriority(TRUE, 0);
    mac_SetDescMode(TRUE, 0);
    mac_SetOpertionMode();
    mac_SetFrameFilter(init->ETH_Filter);
    mac_setFlowControl();

    return TRUE;
}

void ETH_ITConfig(uint32_t Int, BOOL enable) {
    assert_param(IS_ETH_INT(Int));

    if (enable) {
        if (IS_ETH_INT_NORMAL(Int)) {
            ETH->INT_EN_b.NIE = TRUE;
        }

        if (IS_ETH_INT_ABNORMAL(Int)) {
            ETH->INT_EN_b.AIE = TRUE;
        }

        ETH->INT_EN |= Int;
    } else {
        ETH->INT_EN &= ~Int;

        if (!IS_ETH_INT_NORMAL(ETH->INT_EN)) {
            ETH->INT_EN_b.NIE = FALSE;
        }

        if (!IS_ETH_INT_ABNORMAL(ETH->INT_EN)) {
            ETH->INT_EN_b.AIE = FALSE;
        }
    }
}
BOOL ETH_GetITStatus(uint32_t Int) {
    assert_param(IS_ETH_INT(Int));

    Int &= ETH->INT_EN;
    if (0 != (ETH->STATUS & Int)) {
        return TRUE;
    }

    return FALSE;
}
void ETH_ClearITPendingBit(uint32_t Int) {
    uint32_t sta;
    assert_param(IS_ETH_INT(Int));

    sta = ETH->STATUS;
    sta &= ETH->INT_EN;
    sta &= ~Int;

    // write 1 clear
    ETH->STATUS = Int;

    if (IS_ETH_INT_NORMAL(Int)) {
        if (!IS_ETH_INT_NORMAL(sta)) {
            // write 1 clear NIS
            ETH->STATUS = ETH_INT_NORMAL_SUMMARY;
        }
    }

    if (IS_ETH_INT_ABNORMAL(Int)) {
        if (!IS_ETH_INT_ABNORMAL(sta)) {
            // write 1 clear AIS
            ETH->STATUS = ETH_INT_ABNORMAL_SUMMARY;
        }
    }
}

void ETH_GetMacAddr(uint8_t *mac) {
  uint32_t tmp;

    if (!mac) {
        return ;
    }

    tmp = ETH->ADDR0_LOW;
    *(mac + 0) = (tmp >> 0) & 0xFF;
    *(mac + 1) = (tmp >> 8) & 0xFF;
    *(mac + 2) = (tmp >> 16) & 0xFF;
    *(mac + 3) = (tmp >> 24) & 0xFF;
    tmp = ETH->ADDR0_HIGH;
    *(mac + 4) = (tmp >> 0) & 0xFF;
    *(mac + 5) = (tmp >> 8) & 0xFF;
}

BOOL ETH_SetTxDescRing(ETH_TX_DESC *ring) {
    ETH_TX_DESC *buf = ring;

    if (!ring) {
        return FALSE;
    }

    if (ETH->OPERATION_b.ST) {
        return FALSE;
    }

  /* If code mapping */
  ring = (ETH_TX_DESC *)GLB_ConvertToMappingFromAddr((uint32_t)ring);
  buf = ring;

    do {
        INNER_ETH_TX_DESC *desc = (INNER_ETH_TX_DESC *)buf;
    uint8_t first = desc->TX_0.TX0_b.FS;
    uint8_t last = desc->TX_0.TX0_b.LS;

    // clear all bits
    desc->TX_0.TX0 = 0;
    desc->TX_0.TX0_b.FS = first;
    desc->TX_0.TX0_b.LS = last;
        desc->TX_0.TX0_b.TCH = TRUE;
        desc->TX_0.TX0_b.IC = TRUE;
        desc->TX_0.TX0_b.OWN = ETH_DESC_OWN_BY_SELF;

    buf->bufAddr = GLB_ConvertToMappingFromAddr(buf->bufAddr);
    buf->nextDescAddr = GLB_ConvertToMappingFromAddr(buf->nextDescAddr);
        buf = (ETH_TX_DESC *)buf->nextDescAddr;
    } while (buf != ring);

    ETH->TDESLA = (uint32_t)ring;

    return TRUE;
}

void ETH_StartTx() {
    ETH->OPERATION_b.ST = TRUE;
}

void ETH_StopTx() {
    ETH->OPERATION_b.ST = FALSE;
}

void ETH_ResumeTx() {
    ETH->TPD = 0;
}

ETH_TX_DESC *ETH_AcquireFreeTxDesc(void) {
    uint32_t cur = ETH->CURTDESAPTR;
    INNER_ETH_TX_DESC *desc = (INNER_ETH_TX_DESC *)cur;

    do {
        if (desc->TX_0.TX0_b.OWN == ETH_DESC_OWN_BY_SELF) {
            return (ETH_TX_DESC *)desc;
        }
        desc = (INNER_ETH_TX_DESC *)desc->nextDescAddr;
    } while ((uint32_t)desc != cur);

  return 0;
}

BOOL ETH_IsFreeTxDesc(ETH_TX_DESC *desc) {
    INNER_ETH_TX_DESC *inner;

    if (!desc) {
        return FALSE;
    }

    inner = (INNER_ETH_TX_DESC *)desc;
    return (inner->TX_0.TX0_b.OWN == ETH_DESC_OWN_BY_SELF) ? TRUE : FALSE;
}

void ETH_ReleaseTxDesc(ETH_TX_DESC *desc) {
    INNER_ETH_TX_DESC *inner;

    if (!desc) {
        return;
    }

    inner = (INNER_ETH_TX_DESC *)desc;
    inner->TX_0.TX0_b.OWN = ETH_DESC_OWN_BY_HW;
}

void ETH_SetTxDescBufAddr(ETH_TX_DESC *desc, uint32_t bufAddr) {
    if (desc) {
        desc->bufAddr = GLB_ConvertToMappingFromAddr(bufAddr);;
    }
}

uint32_t ETH_GetTxDescBufAddr(ETH_TX_DESC *desc) {
  return (desc ? GLB_ConvertToMappingToAddr(desc->bufAddr) : 0);
}

BOOL ETH_SetRxDescRing(ETH_RX_DESC *ring) {
    ETH_RX_DESC *buf = ring;

    if (!ring) {
        return FALSE;
    }

    if (ETH->OPERATION_b.SR) {
        return FALSE;
    }

  /* If code mapping */
  ring = (ETH_RX_DESC *)GLB_ConvertToMappingFromAddr((uint32_t)ring);
  buf = ring;
    do {
        INNER_ETH_RX_DESC *desc = (INNER_ETH_RX_DESC *)buf;
        desc->RX_1.RX1_b.RCH = TRUE;
        desc->RX_1.RX1_b.DIC = FALSE;
        desc->RX_0.RX0_b.OWN = ETH_DESC_OWN_BY_HW;

    buf->bufAddr = GLB_ConvertToMappingFromAddr(buf->bufAddr);
    buf->nextDescAddr = GLB_ConvertToMappingFromAddr(buf->nextDescAddr);
        buf = (ETH_RX_DESC *)buf->nextDescAddr;
    } while (buf != ring);

    ETH->RDESLA = (uint32_t)ring;

    return TRUE;
}

void ETH_StartRx() {
    ETH->OPERATION_b.SR = TRUE;
}

void ETH_StopRx() {
    ETH->OPERATION_b.SR = FALSE;
}

void ETH_ResumeRx() {
    ETH->RPD = 0;
}

ETH_RX_DESC *ETH_AcquireFreeRxDesc(void) {
    uint32_t cur = ETH->CURRDESAPTR;
    INNER_ETH_RX_DESC *desc = (INNER_ETH_RX_DESC *)cur;

    do {
        if (desc->RX_0.RX0_b.OWN == ETH_DESC_OWN_BY_SELF) {
            return (ETH_RX_DESC *)desc;
        }
        desc = (INNER_ETH_RX_DESC *)desc->nextDescAddr;
    } while ((uint32_t)desc != cur);

  return 0;
}

BOOL ETH_IsFreeRxDesc(ETH_RX_DESC *desc) {
    INNER_ETH_RX_DESC *inner;

    if (!desc) {
        return FALSE;
    }

    inner = (INNER_ETH_RX_DESC *)desc;
    return (inner->RX_0.RX0_b.OWN == ETH_DESC_OWN_BY_SELF) ? TRUE : FALSE;
}

void ETH_ReleaseRxDesc(ETH_RX_DESC *desc) {
    INNER_ETH_RX_DESC *inner;

    if (!desc) {
        return;
    }

    inner = (INNER_ETH_RX_DESC *)desc;
    inner->RX_0.RX0_b.OWN = ETH_DESC_OWN_BY_HW;
}


void ETH_SetRxDescBufAddr(ETH_RX_DESC *desc, uint32_t bufAddr) {
    if (desc) {
        desc->bufAddr = GLB_ConvertToMappingFromAddr(bufAddr);;
    }
}

uint32_t ETH_GetRxDescBufAddr(ETH_RX_DESC *desc) {
  return (desc ? GLB_ConvertToMappingToAddr(desc->bufAddr) : 0);
}



