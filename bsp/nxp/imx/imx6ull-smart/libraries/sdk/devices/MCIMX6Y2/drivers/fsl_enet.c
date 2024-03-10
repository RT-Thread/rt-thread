/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-06-16     songchao   support emac driver
 */

#include <rtthread.h>
#include "fsl_enet.h"
#include "fsl_iomuxc.h"
#include "ioremap.h"
#define DBG_TAG "drv.enet"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>
#include "drv_eth.h"

#define ETH_ENABLE (1U)
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief IPv4 PTP message IP version offset. */
#define ENET_PTP1588_IPVERSION_OFFSET 0x0EU
/*! @brief IPv4 PTP message UDP protocol offset. */
#define ENET_PTP1588_IPV4_UDP_PROTOCOL_OFFSET 0x17U
/*! @brief IPv4 PTP message UDP port offset. */
#define ENET_PTP1588_IPV4_UDP_PORT_OFFSET 0x24U
/*! @brief IPv4 PTP message UDP message type offset. */
#define ENET_PTP1588_IPV4_UDP_MSGTYPE_OFFSET 0x2AU
/*! @brief IPv4 PTP message UDP version offset. */
#define ENET_PTP1588_IPV4_UDP_VERSION_OFFSET 0x2BU
/*! @brief IPv4 PTP message UDP clock id offset. */
#define ENET_PTP1588_IPV4_UDP_CLKID_OFFSET 0x3EU
/*! @brief IPv4 PTP message UDP sequence id offset. */
#define ENET_PTP1588_IPV4_UDP_SEQUENCEID_OFFSET 0x48U
/*! @brief IPv4 PTP message UDP control offset. */
#define ENET_PTP1588_IPV4_UDP_CTL_OFFSET 0x4AU
/*! @brief IPv6 PTP message UDP protocol offset. */
#define ENET_PTP1588_IPV6_UDP_PROTOCOL_OFFSET 0x14U
/*! @brief IPv6 PTP message UDP port offset. */
#define ENET_PTP1588_IPV6_UDP_PORT_OFFSET 0x38U
/*! @brief IPv6 PTP message UDP message type offset. */
#define ENET_PTP1588_IPV6_UDP_MSGTYPE_OFFSET 0x3EU
/*! @brief IPv6 PTP message UDP version offset. */
#define ENET_PTP1588_IPV6_UDP_VERSION_OFFSET 0x3FU
/*! @brief IPv6 PTP message UDP clock id offset. */
#define ENET_PTP1588_IPV6_UDP_CLKID_OFFSET 0x52U
/*! @brief IPv6 PTP message UDP sequence id offset. */
#define ENET_PTP1588_IPV6_UDP_SEQUENCEID_OFFSET 0x5CU
/*! @brief IPv6 PTP message UDP control offset. */
#define ENET_PTP1588_IPV6_UDP_CTL_OFFSET 0x5EU
/*! @brief PTPv2 message Ethernet packet type offset. */
#define ENET_PTP1588_ETHL2_PACKETTYPE_OFFSET 0x0CU
/*! @brief PTPv2 message Ethernet message type offset. */
#define ENET_PTP1588_ETHL2_MSGTYPE_OFFSET 0x0EU
/*! @brief PTPv2 message Ethernet version type offset. */
#define ENET_PTP1588_ETHL2_VERSION_OFFSET 0X0FU
/*! @brief PTPv2 message Ethernet clock id offset. */
#define ENET_PTP1588_ETHL2_CLOCKID_OFFSET 0x22
/*! @brief PTPv2 message Ethernet sequence id offset. */
#define ENET_PTP1588_ETHL2_SEQUENCEID_OFFSET 0x2c
/*! @brief Packet type Ethernet IEEE802.3 for PTPv2. */
#define ENET_ETHERNETL2 0x88F7U
/*! @brief Packet type IPv4. */
#define ENET_IPV4 0x0800U
/*! @brief Packet type IPv6. */
#define ENET_IPV6 0x86ddU
/*! @brief Packet type VLAN. */
#define ENET_8021QVLAN 0x8100U
/*! @brief UDP protocol type. */
#define ENET_UDPVERSION 0x0011U
/*! @brief Packet IP version IPv4. */
#define ENET_IPV4VERSION 0x0004U
/*! @brief Packet IP version IPv6. */
#define ENET_IPV6VERSION 0x0006U
/*! @brief Ethernet mac address length. */
#define ENET_FRAME_MACLEN 6U
/*! @brief Ethernet VLAN header length. */
#define ENET_FRAME_VLAN_TAGLEN 4U
/*! @brief MDC frequency. */
#define ENET_MDC_FREQUENCY 2500000U
/*! @brief NanoSecond in one second. */
#define ENET_NANOSECOND_ONE_SECOND 1000000000U
/*! @brief Define a common clock cycle delays used for time stamp capture. */
#define ENET_1588TIME_DELAY_COUNT 10U
/*! @brief Defines the macro for converting constants from host byte order to network byte order. */
#define ENET_HTONS(n) __REV16(n)
#define ENET_HTONL(n) __REV(n)
#define ENET_NTOHS(n) __REV16(n)
#define ENET_NTOHL(n) __REV(n)

/* Typedef for interrupt handler. */
typedef void (*enet_isr_t)(ENET_Type *base, enet_handle_t *handle);
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Get the ENET instance from peripheral base address.
 *
 * @param base ENET peripheral base address.
 * @return ENET instance.
 */
uint32_t ENET_GetInstance(ENET_Type *base);

/*!
 * @brief Set ENET MAC controller with the configuration.
 *
 * @param base ENET peripheral base address.
 * @param config ENET Mac configuration.
 * @param bufferConfig ENET buffer configuration.
 * @param macAddr ENET six-byte mac address.
 * @param srcClock_Hz ENET module clock source, normally it's system clock.
 */
static void ENET_SetMacController(ENET_Type *base,
                                  const enet_config_t *config,
                                  const enet_buffer_config_t *bufferConfig,
                                  uint8_t *macAddr,
                                  uint32_t srcClock_Hz);
/*!
 * @brief Set ENET handler.
 *
 * @param base ENET peripheral base address.
 * @param handle The ENET handle pointer.
 * @param config ENET configuration stucture pointer.
 * @param bufferConfig ENET buffer configuration.
 */
static void ENET_SetHandler(ENET_Type *base,
                            enet_handle_t *handle,
                            const enet_config_t *config,
                            const enet_buffer_config_t *bufferConfig);
/*!
 * @brief Set ENET MAC transmit buffer descriptors.
 *
 * @param txBdStartAlign The aligned start address of ENET transmit buffer descriptors.
 *        is recommended to evenly divisible by 16.
 * @param txBuffStartAlign The aligned start address of ENET transmit buffers, must be evenly divisible by 16.
 * @param txBuffSizeAlign The aligned ENET transmit buffer size, must be evenly divisible by 16.
 * @param txBdNumber The number of ENET transmit buffers.
 */
static void ENET_SetTxBufferDescriptors(volatile enet_tx_bd_struct_t *txBdStartAlign,
                                        uint8_t *txBuffStartAlign,
                                        uint32_t txBuffSizeAlign,
                                        uint32_t txBdNumber);

/*!
 * @brief Set ENET MAC receive buffer descriptors.
 *
 * @param rxBdStartAlign The aligned start address of ENET receive buffer descriptors.
 *        is recommended to evenly divisible by 16.
 * @param rxBuffStartAlign The aligned start address of ENET receive buffers, must be evenly divisible by 16.
 * @param rxBuffSizeAlign The aligned ENET receive buffer size, must be evenly divisible by 16.
 * @param rxBdNumber The number of ENET receive buffers.
 * @param enableInterrupt Enable/disables to generate the receive byte and frame interrupt.
 *        It's used for ENET_ENHANCEDBUFFERDESCRIPTOR_MODE enabled case.
 */
static void ENET_SetRxBufferDescriptors(volatile enet_rx_bd_struct_t *rxBdStartAlign,
                                        uint8_t *rxBuffStartAlign,
                                        uint32_t rxBuffSizeAlign,
                                        uint32_t rxBdNumber,
                                        bool enableInterrupt);

/*!
 * @brief Updates the ENET read buffer descriptors.
 *
 * @param base ENET peripheral base address.
 * @param handle The ENET handle pointer.
 */
static void ENET_UpdateReadBuffers(ENET_Type *base, enet_handle_t *handle);

void rt_hw_cpu_dcache_clean(void *addr, int size);
void rt_hw_cpu_dcache_invalidate(void *addr, int size);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Pointers to enet handles for each instance. */
static enet_handle_t *s_ENETHandle[FSL_FEATURE_SOC_ENET_COUNT] = {NULL,NULL};

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to enet clocks for each instance. */
const clock_ip_name_t s_enetClock[] = ENET_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*! @brief Pointers to enet bases for each instance. */
static ENET_Type *const s_enetBases[] = ENET_BASE_PTRS;

/* ENET ISR for transactional APIs. */
static enet_isr_t s_enetTxIsr = NULL;
static enet_isr_t s_enetRxIsr = NULL;
static enet_isr_t s_enetErrIsr = NULL;
static enet_isr_t s_enetTsIsr = NULL;

/*******************************************************************************
 * Code
 ******************************************************************************/
uint32_t ENET_GetInstance(ENET_Type *base)
{
    uint32_t instance;
    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_enetBases); instance++)
    {
        if (s_enetBases[instance] == base)
        {
            break;
        }
    }
    RT_ASSERT(instance < ARRAY_SIZE(s_enetBases));

    return instance;
}

void ENET_GetDefaultConfig(enet_config_t *config)
{
    /* Checks input parameter. */
    RT_ASSERT(config);

    /* Initializes the MAC configure structure to zero. */
    memset(config, 0, sizeof(enet_config_t));

    /* Sets MII mode, full duplex, 100Mbps for MAC and PHY data interface. */
    config->miiMode = kENET_RmiiMode;
    config->miiSpeed = kENET_MiiSpeed100M;
    config->miiDuplex = kENET_MiiFullDuplex;

    /* Sets the maximum receive frame length. */
    config->rxMaxFrameLen = ENET_FRAME_MAX_FRAMELEN;
}

void ENET_Init(ENET_Type *base,
               enet_handle_t *handle,
               const enet_config_t *config,
               const enet_buffer_config_t *bufferConfig,
               uint8_t *macAddr,
               uint32_t srcClock_Hz)
{
    /* Checks input parameters. */
    RT_ASSERT(handle);
    RT_ASSERT(config);
    RT_ASSERT(bufferConfig);
    RT_ASSERT(bufferConfig->rxBdStartAddrAlign);
    RT_ASSERT(bufferConfig->txBdStartAddrAlign);
    RT_ASSERT(bufferConfig->rxBufferAlign);
    RT_ASSERT(bufferConfig->txBufferAlign);
    RT_ASSERT(macAddr);
    RT_ASSERT(bufferConfig->rxBuffSizeAlign >= ENET_RX_MIN_BUFFERSIZE);
    /* Make sure the buffers should be have the capability of process at least one maximum frame. */
    if (config->macSpecialConfig & kENET_ControlVLANTagEnable)
    {
        RT_ASSERT(bufferConfig->txBuffSizeAlign * bufferConfig->txBdNumber > (ENET_FRAME_MAX_FRAMELEN + ENET_FRAME_VLAN_TAGLEN));
    }
    else
    {
        RT_ASSERT(bufferConfig->txBuffSizeAlign * bufferConfig->txBdNumber > ENET_FRAME_MAX_FRAMELEN);
        RT_ASSERT(bufferConfig->rxBuffSizeAlign * bufferConfig->rxBdNumber > config->rxMaxFrameLen);
    }

    /* Reset ENET module. */
    ENET_Reset(base);
    /* Initializes the ENET transmit buffer descriptors. */
    ENET_SetTxBufferDescriptors(bufferConfig->txBdStartAddrAlign, bufferConfig->txPhyBufferAlign,
                                bufferConfig->txBuffSizeAlign, bufferConfig->txBdNumber);
    /* Initializes the ENET receive buffer descriptors. */


    ENET_SetRxBufferDescriptors(bufferConfig->rxBdStartAddrAlign, bufferConfig->rxPhyBufferAlign,
                                bufferConfig->rxBuffSizeAlign, bufferConfig->rxBdNumber,
                                !!(config->interrupt & (kENET_RxFrameInterrupt | kENET_RxBufferInterrupt)));
    /* Initializes the ENET MAC controller. */
    ENET_SetMacController(base, config, bufferConfig, macAddr, srcClock_Hz);
    /* Set all buffers or data in handler for data transmit/receive process. */
    ENET_SetHandler(base, handle, config, bufferConfig);
}

void ENET_Deinit(ENET_Type *base)
{
    /* Disable interrupt. */
    base->EIMR = 0;

    /* Disable ENET. */
    base->ECR &= ~ENET_ECR_ETHEREN_MASK;

}

void ENET_SetCallback(enet_handle_t *handle, enet_callback_t callback, void *userData)
{
    RT_ASSERT(handle);

    /* Set callback and userData. */
    handle->callback = callback;
    handle->userData = userData;
}

static void ENET_SetHandler(ENET_Type *base,
                            enet_handle_t *handle,
                            const enet_config_t *config,
                            const enet_buffer_config_t *bufferConfig)
{
    struct rt_imx6ul_ethps *imx6ul_device = rt_container_of(config,struct rt_imx6ul_ethps,config);
    uint32_t instance = get_instance_by_base(base);
    memset(handle, 0, sizeof(enet_handle_t));
    handle->rxBdBase = bufferConfig->rxBdStartAddrAlign;
    handle->rxBdCurrent = bufferConfig->rxBdStartAddrAlign;
    handle->txBdBase = bufferConfig->txBdStartAddrAlign;
    handle->txBdCurrent = bufferConfig->txBdStartAddrAlign;
    handle->rxBuffSizeAlign = bufferConfig->rxBuffSizeAlign;
    handle->txBuffSizeAlign = bufferConfig->txBuffSizeAlign;

    /* Save the handle pointer in the global variables. */
    s_ENETHandle[instance] = handle;

    /* Set the IRQ handler when the interrupt is enabled. */
    if (config->interrupt & ENET_TX_INTERRUPT)
    {
        s_enetTxIsr = ENET_TransmitIRQHandler;
        EnableIRQ(imx6ul_device->irq_num);
    }
    if (config->interrupt & ENET_RX_INTERRUPT)
    {
        s_enetRxIsr = ENET_ReceiveIRQHandler;
        EnableIRQ(imx6ul_device->irq_num);
    }
    if (config->interrupt & ENET_ERR_INTERRUPT)
    {
        s_enetErrIsr = ENET_ErrorIRQHandler;
        EnableIRQ(imx6ul_device->irq_num);
    }
}

static void ENET_SetMacController(ENET_Type *base,
                                  const enet_config_t *config,
                                  const enet_buffer_config_t *bufferConfig,
                                  uint8_t *macAddr,
                                  uint32_t srcClock_Hz)
{
    uint32_t rcr = 0;
    uint32_t tcr = 0;
    uint32_t ecr = 0;
    uint32_t macSpecialConfig = config->macSpecialConfig;
    uint32_t maxFrameLen = config->rxMaxFrameLen;

    /* Maximum frame length check. */
    if ((macSpecialConfig & kENET_ControlVLANTagEnable) && (maxFrameLen <= ENET_FRAME_MAX_FRAMELEN))
    {
        maxFrameLen = (ENET_FRAME_MAX_FRAMELEN + ENET_FRAME_VLAN_TAGLEN);
    }

    /* Configures MAC receive controller with user configure structure. */
    rcr = ENET_RCR_NLC(!!(macSpecialConfig & kENET_ControlRxPayloadCheckEnable)) |
          ENET_RCR_CFEN(!!(macSpecialConfig & kENET_ControlFlowControlEnable)) |
          ENET_RCR_FCE(!!(macSpecialConfig & kENET_ControlFlowControlEnable)) |
          ENET_RCR_PADEN(!!(macSpecialConfig & kENET_ControlRxPadRemoveEnable)) |
          ENET_RCR_BC_REJ(!!(macSpecialConfig & kENET_ControlRxBroadCastRejectEnable)) |
          ENET_RCR_PROM(!!(macSpecialConfig & kENET_ControlPromiscuousEnable)) | ENET_RCR_MII_MODE(1) |
          ENET_RCR_RMII_MODE(config->miiMode) | ENET_RCR_RMII_10T(!config->miiSpeed) |
          ENET_RCR_MAX_FL(maxFrameLen) | ENET_RCR_CRCFWD(1);
    /* Receive setting for half duplex. */
    if (config->miiDuplex == kENET_MiiHalfDuplex)
    {
        rcr |= ENET_RCR_DRT_MASK;
    }
    /* Sets internal loop only for MII mode. */
    if ((config->macSpecialConfig & kENET_ControlMIILoopEnable) && (config->miiMode == kENET_MiiMode))
    {
        rcr |= ENET_RCR_LOOP_MASK;
        rcr &= ~ENET_RCR_DRT_MASK;
    }
    base->RCR = rcr;

    /* Configures MAC transmit controller: duplex mode, mac address insertion. */
    tcr = base->TCR & ~(ENET_TCR_FDEN_MASK | ENET_TCR_ADDINS_MASK);
    tcr |= ENET_TCR_FDEN(config->miiDuplex) | ENET_TCR_ADDINS(!!(macSpecialConfig & kENET_ControlMacAddrInsert));
    base->TCR = tcr;

    /* Configures receive and transmit accelerator. */
    base->TACC = config->txAccelerConfig;
    base->RACC = config->rxAccelerConfig;

    /* Sets the pause duration and FIFO threshold for the flow control enabled case. */
    if (macSpecialConfig & kENET_ControlFlowControlEnable)
    {
        uint32_t reemReg;
        base->OPD = config->pauseDuration;
        reemReg = ENET_RSEM_RX_SECTION_EMPTY(config->rxFifoEmptyThreshold);
#if defined (FSL_FEATURE_ENET_HAS_RECEIVE_STATUS_THRESHOLD) && FSL_FEATURE_ENET_HAS_RECEIVE_STATUS_THRESHOLD
        reemReg |= ENET_RSEM_STAT_SECTION_EMPTY(config->rxFifoStatEmptyThreshold);
#endif /* FSL_FEATURE_ENET_HAS_RECEIVE_STATUS_THRESHOLD */
        base->RSEM = reemReg;
    }

    /* FIFO threshold setting for store and forward enable/disable case. */
    if (macSpecialConfig & kENET_ControlStoreAndFwdDisable)
    {
        /* Transmit fifo watermark settings. */
        base->TFWR = config->txFifoWatermark & ENET_TFWR_TFWR_MASK;
        /* Receive fifo full threshold settings. */
        base->RSFL = config->rxFifoFullThreshold & ENET_RSFL_RX_SECTION_FULL_MASK;
    }
    else
    {
        /* Transmit fifo watermark settings. */
        base->TFWR = ENET_TFWR_STRFWD_MASK;
        base->RSFL = 0;
    }

    /* Enable store and forward when accelerator is enabled */
    if (config->txAccelerConfig & (kENET_TxAccelIpCheckEnabled | kENET_TxAccelProtoCheckEnabled))
    {
        base->TFWR = ENET_TFWR_STRFWD_MASK;
    }
    if (config->rxAccelerConfig & (kENET_RxAccelIpCheckEnabled | kENET_RxAccelProtoCheckEnabled))
    {
        base->RSFL = 0;
    }

    /* Initializes transmit buffer descriptor rings start address, two start address should be aligned. */
    base->TDSR = (uint32_t)bufferConfig->txPhyBdStartAddrAlign;
    base->RDSR = (uint32_t)bufferConfig->rxPhyBdStartAddrAlign;

    /* Initializes the maximum buffer size, the buffer size should be aligned. */

    base->MRBR = ENET_MRBR_R_BUF_SIZE(bufferConfig->rxBuffSizeAlign);

    /* Configures the Mac address. */
    ENET_SetMacAddr(base, macAddr);

    /* Initialize the SMI if uninitialized. */
    if (!ENET_GetSMI(base))
    {
        ENET_SetSMI(base, srcClock_Hz, !!(config->macSpecialConfig & kENET_ControlSMIPreambleDisable));
    }

/* Enables Ethernet interrupt and NVIC. */
#if defined(FSL_FEATURE_ENET_HAS_INTERRUPT_COALESCE) && FSL_FEATURE_ENET_HAS_INTERRUPT_COALESCE
    if (config->intCoalesceCfg)
    {
        uint32_t intMask = (ENET_EIMR_TXB_MASK | ENET_EIMR_RXB_MASK);

        /* Clear all buffer interrupts. */
        base->EIMR &= ~intMask;

        /* Set the interrupt coalescence. */
        base->TXIC = ENET_TXIC_ICFT(config->intCoalesceCfg->txCoalesceFrameCount[0]) |
                     config->intCoalesceCfg->txCoalesceTimeCount[0] | ENET_TXIC_ICCS_MASK | ENET_TXIC_ICEN_MASK;
        base->RXIC = ENET_RXIC_ICFT(config->intCoalesceCfg->rxCoalesceFrameCount[0]) |
                     config->intCoalesceCfg->rxCoalesceTimeCount[0] | ENET_RXIC_ICCS_MASK | ENET_RXIC_ICEN_MASK;
    }
#endif /* FSL_FEATURE_ENET_HAS_INTERRUPT_COALESCE */
    ENET_EnableInterrupts(base, config->interrupt);

    /* ENET control register setting. */
    ecr = base->ECR;

    /* Enables Ethernet module after all configuration except the buffer descriptor active. */
    ecr |= ENET_ECR_ETHEREN_MASK | ENET_ECR_DBSWP_MASK;
    base->ECR = ecr;
}

static void ENET_SetTxBufferDescriptors(volatile enet_tx_bd_struct_t *txBdStartAlign,
                                        uint8_t *txBuffStartAlign,
                                        uint32_t txBuffSizeAlign,
                                        uint32_t txBdNumber)
{
    RT_ASSERT(txBdStartAlign);
    RT_ASSERT(txBuffStartAlign);
    uint32_t count;
    volatile enet_tx_bd_struct_t *curBuffDescrip = txBdStartAlign;
    for (count = 0; count < txBdNumber; count++)
    {

        /* Set data buffer address. */
        curBuffDescrip->buffer = (uint8_t *)((uint32_t)&txBuffStartAlign[count * txBuffSizeAlign]);
        /* Initializes data length. */
        curBuffDescrip->length = 0;
        /* Sets the crc. */
        curBuffDescrip->control = (ENET_BUFFDESCRIPTOR_TX_TRANMITCRC_MASK);
        /* Sets the last buffer descriptor with the wrap flag. */
        if (count == txBdNumber - 1)
        {
            curBuffDescrip->control |= ENET_BUFFDESCRIPTOR_TX_WRAP_MASK;
        }

        /* Add cache clean operation. */
        rt_hw_cpu_dcache_clean((void *)curBuffDescrip, sizeof(enet_tx_bd_struct_t));
        /* Increase the index. */
        curBuffDescrip++;
    }
}

static void ENET_SetRxBufferDescriptors(volatile enet_rx_bd_struct_t *rxBdStartAlign,
                                        uint8_t *rxBuffStartAlign,
                                        uint32_t rxBuffSizeAlign,
                                        uint32_t rxBdNumber,
                                        bool enableInterrupt)
{
    RT_ASSERT(rxBdStartAlign);
    RT_ASSERT(rxBuffStartAlign);

    volatile enet_rx_bd_struct_t *curBuffDescrip = rxBdStartAlign;
    uint32_t count = 0;

    /* Initializes receive buffer descriptors. */
    for (count = 0; count < rxBdNumber; count++)
    {
        /* Set data buffer and the length. */
        curBuffDescrip->buffer = (uint8_t *)((void *)&rxBuffStartAlign[count * rxBuffSizeAlign]);
        curBuffDescrip->length = 0;
        /* Initializes the buffer descriptors with empty bit. */
        curBuffDescrip->control = ENET_BUFFDESCRIPTOR_RX_EMPTY_MASK;
        /* Sets the last buffer descriptor with the wrap flag. */
        if (count == rxBdNumber - 1)
        {
            curBuffDescrip->control |= ENET_BUFFDESCRIPTOR_RX_WRAP_MASK;
        }
        /* Add cache clean operation. */
        rt_hw_cpu_dcache_clean((void *)curBuffDescrip, sizeof(enet_rx_bd_struct_t));
        /* Increase the index. */
        curBuffDescrip++;
    }
}

void ENET_SetMII(ENET_Type *base, enet_mii_speed_t speed, enet_mii_duplex_t duplex)
{
    uint32_t rcr = base->RCR;
    uint32_t tcr = base->TCR;
    /* Sets speed mode. */
    if (kENET_MiiSpeed10M == speed)
    {
        rcr |= ENET_RCR_RMII_10T_MASK;
    }
    else
    {
        rcr &= ~ENET_RCR_RMII_10T_MASK;
    }
    /* Set duplex mode. */
    if (duplex == kENET_MiiHalfDuplex)
    {
        rcr |= ENET_RCR_DRT_MASK;
        tcr &= ~ENET_TCR_FDEN_MASK;
    }
    else
    {
        rcr &= ~ENET_RCR_DRT_MASK;
        tcr |= ENET_TCR_FDEN_MASK;
    }

    base->RCR = rcr;
    base->TCR = tcr;
}

void ENET_SetMacAddr(ENET_Type *base, uint8_t *macAddr)
{
    uint32_t address;

    /* Set physical address lower register. */
    address = (uint32_t)(((uint32_t)macAddr[0] << 24U) | ((uint32_t)macAddr[1] << 16U) | ((uint32_t)macAddr[2] << 8U) |
                         (uint32_t)macAddr[3]);
    base->PALR = address;
    /* Set physical address high register. */
    address = (uint32_t)(((uint32_t)macAddr[4] << 8U) | ((uint32_t)macAddr[5]));
    base->PAUR = address << ENET_PAUR_PADDR2_SHIFT;
}

void ENET_GetMacAddr(ENET_Type *base, uint8_t *macAddr)
{
    RT_ASSERT(macAddr);

    uint32_t address;

    /* Get from physical address lower register. */
    address = base->PALR;
    macAddr[0] = 0xFFU & (address >> 24U);
    macAddr[1] = 0xFFU & (address >> 16U);
    macAddr[2] = 0xFFU & (address >> 8U);
    macAddr[3] = 0xFFU & address;

    /* Get from physical address high register. */
    address = (base->PAUR & ENET_PAUR_PADDR2_MASK) >> ENET_PAUR_PADDR2_SHIFT;
    macAddr[4] = 0xFFU & (address >> 8U);
    macAddr[5] = 0xFFU & address;
}

void ENET_SetSMI(ENET_Type *base, uint32_t srcClock_Hz, bool isPreambleDisabled)
{
    RT_ASSERT(srcClock_Hz);

    uint32_t clkCycle = 0;
    uint32_t speed = 0;
    uint32_t mscr = 0;

    /* Calculate the MII speed which controls the frequency of the MDC. */
    speed = srcClock_Hz / (2 * ENET_MDC_FREQUENCY);
    /* Calculate the hold time on the MDIO output. */
    clkCycle = (10 + ENET_NANOSECOND_ONE_SECOND / srcClock_Hz - 1) / (ENET_NANOSECOND_ONE_SECOND / srcClock_Hz) - 1;
    /* Build the configuration for MDC/MDIO control. */
    mscr = ENET_MSCR_MII_SPEED(speed) | ENET_MSCR_DIS_PRE(isPreambleDisabled) | ENET_MSCR_HOLDTIME(clkCycle);
    base->MSCR = mscr;
}

void ENET_StartSMIWrite(ENET_Type *base, uint32_t phyAddr, uint32_t phyReg, enet_mii_write_t operation, uint32_t data)
{
    uint32_t mmfr = 0;

    /* Build MII write command. */
    mmfr = ENET_MMFR_ST(1) | ENET_MMFR_OP(operation) | ENET_MMFR_PA(phyAddr) | ENET_MMFR_RA(phyReg) | ENET_MMFR_TA(2) |
           (data & 0xFFFF);
    base->MMFR = mmfr;
}

void ENET_StartSMIRead(ENET_Type *base, uint32_t phyAddr, uint32_t phyReg, enet_mii_read_t operation)
{
    uint32_t mmfr = 0;

    /* Build MII read command. */
    mmfr = ENET_MMFR_ST(1) | ENET_MMFR_OP(operation) | ENET_MMFR_PA(phyAddr) | ENET_MMFR_RA(phyReg) | ENET_MMFR_TA(2);
    base->MMFR = mmfr;
}

#if defined(FSL_FEATURE_ENET_HAS_EXTEND_MDIO) && FSL_FEATURE_ENET_HAS_EXTEND_MDIO
void ENET_StartExtC45SMIWrite(ENET_Type *base, uint32_t phyAddr, uint32_t phyReg, uint32_t data)
{
    uint32_t mmfr = 0;

    /* Parse the address from the input register. */
    uint16_t devAddr = (phyReg >> ENET_MMFR_TA_SHIFT) & 0x1FU;
    uint16_t regAddr = (uint16_t)(phyReg & 0xFFFFU);

    /* Address write firstly. */
    mmfr = ENET_MMFR_ST(0) | ENET_MMFR_OP(kENET_MiiAddrWrite_C45) | ENET_MMFR_PA(phyAddr) | ENET_MMFR_RA(devAddr) |
           ENET_MMFR_TA(2) | ENET_MMFR_DATA(regAddr);
    base->MMFR = mmfr;

    /* Build MII write command. */
    mmfr = ENET_MMFR_ST(0) | ENET_MMFR_OP(kENET_MiiWriteFrame_C45) | ENET_MMFR_PA(phyAddr) | ENET_MMFR_RA(devAddr) |
           ENET_MMFR_TA(2) | ENET_MMFR_DATA(data);
    base->MMFR = mmfr;
}

void ENET_StartExtC45SMIRead(ENET_Type *base, uint32_t phyAddr, uint32_t phyReg)
{
    uint32_t mmfr = 0;

    /* Parse the address from the input register. */
    uint16_t devAddr = (phyReg >> ENET_MMFR_TA_SHIFT) & 0x1FU;
    uint16_t regAddr = (uint16_t)(phyReg & 0xFFFFU);

    /* Address write firstly. */
    mmfr = ENET_MMFR_ST(0) | ENET_MMFR_OP(kENET_MiiAddrWrite_C45) | ENET_MMFR_PA(phyAddr) | ENET_MMFR_RA(devAddr) |
           ENET_MMFR_TA(2) | ENET_MMFR_DATA(regAddr);
    base->MMFR = mmfr;

    /* Build MII read command. */
    mmfr = ENET_MMFR_ST(0) | ENET_MMFR_OP(kENET_MiiReadFrame_C45) | ENET_MMFR_PA(phyAddr) | ENET_MMFR_RA(devAddr) |
           ENET_MMFR_TA(2);
    base->MMFR = mmfr;
}
#endif /* FSL_FEATURE_ENET_HAS_EXTEND_MDIO */

void ENET_GetRxErrBeforeReadFrame(enet_handle_t *handle, enet_data_error_stats_t *eErrorStatic)
{
    RT_ASSERT(handle);
    RT_ASSERT(handle->rxBdCurrent);
    RT_ASSERT(eErrorStatic);

    uint16_t control = 0;
    volatile enet_rx_bd_struct_t *curBuffDescrip = handle->rxBdCurrent;

    do
    {
        /* Add the cache invalidate maintain. */
        rt_hw_cpu_dcache_invalidate((void *)curBuffDescrip, sizeof(enet_rx_bd_struct_t));

        /* The last buffer descriptor of a frame. */
        if (curBuffDescrip->control & ENET_BUFFDESCRIPTOR_RX_LAST_MASK)
        {
            control = curBuffDescrip->control;
            if (control & ENET_BUFFDESCRIPTOR_RX_TRUNC_MASK)
            {
                /* The receive truncate error. */
                eErrorStatic->statsRxTruncateErr++;
            }
            if (control & ENET_BUFFDESCRIPTOR_RX_OVERRUN_MASK)
            {
                /* The receive over run error. */
                eErrorStatic->statsRxOverRunErr++;
            }
            if (control & ENET_BUFFDESCRIPTOR_RX_LENVLIOLATE_MASK)
            {
                /* The receive length violation error. */
                eErrorStatic->statsRxLenGreaterErr++;
            }
            if (control & ENET_BUFFDESCRIPTOR_RX_NOOCTET_MASK)
            {
                /* The receive alignment error. */
                eErrorStatic->statsRxAlignErr++;
            }
            if (control & ENET_BUFFDESCRIPTOR_RX_CRC_MASK)
            {
                /* The receive CRC error. */
                eErrorStatic->statsRxFcsErr++;
            }
            break;
        }

        /* Increase the buffer descriptor, if it is the last one, increase to first one of the ring buffer. */
        if (curBuffDescrip->control & ENET_BUFFDESCRIPTOR_RX_WRAP_MASK)
        {
            curBuffDescrip = handle->rxBdBase;
        }
        else
        {
            curBuffDescrip++;
        }

    } while (curBuffDescrip != handle->rxBdCurrent);
}

status_t ENET_ReadFrame(ENET_Type *base,enet_handle_t *handle,const enet_config_t *config,uint8_t *data,uint16_t *length)
{
    RT_ASSERT(handle);
    RT_ASSERT(handle->rxBdCurrent);
    RT_ASSERT(length);

    /* Reset the length to zero. */
    *length = 0;

    uint16_t validLastMask = ENET_BUFFDESCRIPTOR_RX_LAST_MASK | ENET_BUFFDESCRIPTOR_RX_EMPTY_MASK;
    volatile enet_rx_bd_struct_t *curBuffDescrip = handle->rxBdCurrent;
    rt_hw_cpu_dcache_invalidate((void *)physical_to_virtual(curBuffDescrip->buffer), handle->rxBuffSizeAlign);

    /* Check the current buffer descriptor's empty flag.  if empty means there is no frame received. */
    if (curBuffDescrip->control & ENET_BUFFDESCRIPTOR_RX_EMPTY_MASK)
    {
        return kStatus_ENET_RxFrameEmpty;
    }
    else
    {
        if ((curBuffDescrip->control & validLastMask) == ENET_BUFFDESCRIPTOR_RX_LAST_MASK)
        {
            if(curBuffDescrip->length <= config->rxMaxFrameLen)
            {
                *length = curBuffDescrip->length;

                rt_memcpy(data, physical_to_virtual(curBuffDescrip->buffer),curBuffDescrip->length);
                /* Updates the receive buffer descriptors. */
                ENET_UpdateReadBuffers(base, handle);
                return kStatus_Success;
            }
            else
            {
                LOG_E("frame error0 curBuffDescrip->control 0x%04x length %d\n",curBuffDescrip->control,curBuffDescrip->length);
                *length = curBuffDescrip->length;
                /* Updates the receive buffer descriptors. */
                ENET_UpdateReadBuffers(base, handle);
                return kStatus_ENET_RxFrameError;
            }
        }
        else
        {
            LOG_E("frame error1 curBuffDescrip->control 0x%04x length %d\n",curBuffDescrip->control,curBuffDescrip->length);
            *length = curBuffDescrip->length;
            ENET_UpdateReadBuffers(base, handle);
            return kStatus_ENET_RxFrameError;
        }
    }
    /* The frame is on processing - set to empty status to make application to receive it next time. */
    return kStatus_ENET_RxFrameEmpty;
}

static void ENET_UpdateReadBuffers(ENET_Type *base, enet_handle_t *handle)
{
    RT_ASSERT(handle);

    /* Clears status. */
    handle->rxBdCurrent->control &= ENET_BUFFDESCRIPTOR_RX_WRAP_MASK;
    /* Sets the receive buffer descriptor with the empty flag. */
    handle->rxBdCurrent->control |= ENET_BUFFDESCRIPTOR_RX_EMPTY_MASK;
    /* Increase current buffer descriptor to the next one. */
    if (handle->rxBdCurrent->control & ENET_BUFFDESCRIPTOR_RX_WRAP_MASK)
    {
        handle->rxBdCurrent = handle->rxBdBase;
    }
    else
    {
        handle->rxBdCurrent++;
    }
    /* Actives the receive buffer descriptor. */
    base->RDAR = ENET_RDAR_RDAR_MASK;
}

status_t ENET_SendFrame(ENET_Type *base, enet_handle_t *handle, const uint8_t *data, uint16_t length,uint32_t last_flag)
{
    RT_ASSERT(handle);
    RT_ASSERT(handle->txBdCurrent);
    RT_ASSERT(data);
    RT_ASSERT(length <= ENET_FRAME_MAX_FRAMELEN);

    volatile enet_tx_bd_struct_t *curBuffDescrip = handle->txBdCurrent;
    /* Check if the transmit buffer is ready. */
    if (curBuffDescrip->control & ENET_BUFFDESCRIPTOR_TX_READY_MASK)
    {
        return kStatus_ENET_TxFrameBusy;
    }
    /* One transmit buffer is enough for one frame. */
    if (handle->txBuffSizeAlign >= length)
    {
        /* Copy data to the buffer for uDMA transfer. */
        rt_memcpy(physical_to_virtual(curBuffDescrip->buffer), data, length);
        /* Set data length. */
        curBuffDescrip->length = length;
        if(last_flag)
        {
            curBuffDescrip->control |= (ENET_BUFFDESCRIPTOR_TX_READY_MASK | ENET_BUFFDESCRIPTOR_TX_LAST_MASK);
        }
        else
        {
            curBuffDescrip->control &= ~ENET_BUFFDESCRIPTOR_TX_LAST_MASK;
            curBuffDescrip->control |= ENET_BUFFDESCRIPTOR_TX_READY_MASK;
        }

        rt_hw_cpu_dcache_clean((void *)physical_to_virtual(curBuffDescrip->buffer),length);
        /* Active the transmit buffer descriptor. */

        base->TDAR = ENET_TDAR_TDAR_MASK;
        /* Increase the buffer descriptor address. */
        while((base->TDAR != 0))
        {
        }
        if (curBuffDescrip->control & ENET_BUFFDESCRIPTOR_TX_WRAP_MASK)
        {
            handle->txBdCurrent = handle->txBdBase;
        }
        else
        {
            handle->txBdCurrent++;
        }
        return kStatus_Success;
    }
    else
    {
        return kStatus_ENET_RxFrameError;
    }
}

void ENET_AddMulticastGroup(ENET_Type *base, uint8_t *address)
{
    RT_ASSERT(address);

    uint32_t crc = 0xFFFFFFFFU;
    uint32_t count1 = 0;
    uint32_t count2 = 0;

    /* Calculates the CRC-32 polynomial on the multicast group address. */
    for (count1 = 0; count1 < ENET_FRAME_MACLEN; count1++)
    {
        uint8_t c = address[count1];
        for (count2 = 0; count2 < 0x08U; count2++)
        {
            if ((c ^ crc) & 1U)
            {
                crc >>= 1U;
                c >>= 1U;
                crc ^= 0xEDB88320U;
            }
            else
            {
                crc >>= 1U;
                c >>= 1U;
            }
        }
    }

    /* Enable a multicast group address. */
    if (!((crc >> 0x1FU) & 1U))
    {
        base->GALR |= 1U << ((crc >> 0x1AU) & 0x1FU);
    }
    else
    {
        base->GAUR |= 1U << ((crc >> 0x1AU) & 0x1FU);
    }
}

void ENET_LeaveMulticastGroup(ENET_Type *base, uint8_t *address)
{
    RT_ASSERT(address);

    uint32_t crc = 0xFFFFFFFFU;
    uint32_t count1 = 0;
    uint32_t count2 = 0;

    /* Calculates the CRC-32 polynomial on the multicast group address. */
    for (count1 = 0; count1 < ENET_FRAME_MACLEN; count1++)
    {
        uint8_t c = address[count1];
        for (count2 = 0; count2 < 0x08U; count2++)
        {
            if ((c ^ crc) & 1U)
            {
                crc >>= 1U;
                c >>= 1U;
                crc ^= 0xEDB88320U;
            }
            else
            {
                crc >>= 1U;
                c >>= 1U;
            }
        }
    }

    /* Set the hash table. */
    if (!((crc >> 0x1FU) & 1U))
    {
        base->GALR &= ~(1U << ((crc >> 0x1AU) & 0x1FU));
    }
    else
    {
        base->GAUR &= ~(1U << ((crc >> 0x1AU) & 0x1FU));
    }
}
void tx_enet_callback(void *base);
void ENET_TransmitIRQHandler(ENET_Type *base, enet_handle_t *handle)
{
    RT_ASSERT(handle);
    /* Check if the transmit interrupt happen. */
    if((kENET_TxBufferInterrupt | kENET_TxFrameInterrupt) & base->EIR)
    {
        /* Clear the transmit interrupt event. */
        base->EIR = kENET_TxFrameInterrupt | kENET_TxBufferInterrupt;
    }
    tx_enet_callback((void *)base);
}
void rx_enet_callback(void *base);
void ENET_ReceiveIRQHandler(ENET_Type *base, enet_handle_t *handle)
{
    RT_ASSERT(handle);

    /* Check if the receive interrupt happen. */
    if((kENET_RxBufferInterrupt | kENET_RxFrameInterrupt) & base->EIR)
    {
        /* Clear the transmit interrupt event. */
        base->EIR = kENET_RxFrameInterrupt | kENET_RxBufferInterrupt;
        rx_enet_callback((void *)base);
    }
}
void ENET_ErrorIRQHandler(ENET_Type *base, enet_handle_t *handle)
{
    RT_ASSERT(handle);

    uint32_t errMask = kENET_BabrInterrupt | kENET_BabtInterrupt | kENET_EBusERInterrupt | kENET_PayloadRxInterrupt |
                       kENET_LateCollisionInterrupt | kENET_RetryLimitInterrupt | kENET_UnderrunInterrupt;
    /* Check if the error interrupt happen. */
    if (kENET_WakeupInterrupt & base->EIR)
    {
        /* Clear the wakeup interrupt. */
        base->EIR = kENET_WakeupInterrupt;
        /* wake up and enter the normal mode. */
        ENET_EnableSleepMode(base, false);
        /* Callback function. */
        if (handle->callback)
        {
            handle->callback(base, handle, kENET_WakeUpEvent, handle->userData);
        }
    }
    else
    {
        /* Clear the error interrupt event status. */
        errMask &= base->EIR;
        base->EIR = errMask;
        /* Callback function. */
        if (handle->callback)
        {
            handle->callback(base, handle, kENET_ErrEvent, handle->userData);
        }
    }
}

void ENET_CommonFrame0IRQHandler(ENET_Type *base)
{
    uint32_t event = base->EIR;
    uint32_t instance = get_instance_by_base(base);

    if(base->EIMR & ENET_TX_INTERRUPT)
    {
        if (event & ENET_TX_INTERRUPT)
        {
            if(s_enetTxIsr)
            {
                s_enetTxIsr(base, s_ENETHandle[instance]);
            }
        }
    }
    if (base->EIMR & ENET_RX_INTERRUPT)
    {
        if (event & ENET_RX_INTERRUPT)
        {
            if(s_enetRxIsr)
            {
                s_enetRxIsr(base, s_ENETHandle[instance]);
            }
        }
    }
    if(base->EIMR & ENET_TS_INTERRUPT)
    {
        if (event & ENET_TS_INTERRUPT)
        {
            if(s_enetTsIsr)
            {
                s_enetTsIsr(base, s_ENETHandle[instance]);
            }
        }
    }
    if(base->EIMR & ENET_ERR_INTERRUPT)
    {
        if (event & ENET_ERR_INTERRUPT)
        {
            if(s_enetErrIsr)
            {
                s_enetErrIsr(base, s_ENETHandle[instance]);
            }
        }
    }
}
void ENET_DriverIRQHandler(int irq, void *base)
{
    ENET_CommonFrame0IRQHandler((ENET_Type *)base);
}
