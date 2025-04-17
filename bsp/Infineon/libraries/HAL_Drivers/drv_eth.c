/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-09-23     LZerro       first version
 */

#include <netif/ethernetif.h>
#include <lwipopts.h>
#include "drv_eth.h"
#include "eth_config.h"
#include <rtdbg.h>

#define DBG_TAG               "drv"
#define DBG_LVL               DBG_INFO

#define cy_ecm_log_msg(a,b,c,...) rt_kprintf(c, __VA_ARGS__)

#define cy_rtos_delay_milliseconds rt_thread_mdelay

#define SLEEP_ETHERNET_PHY_STATUS                 (500) /* Sleep time in milliseconds. */

#define Eth_Mempool_Num 40
#define MAX_ADDR_LEN    6

/********************************************************/
/******************EMAC configuration********************/
/********************************************************/
#define EMAC_MII             0
#define EMAC_RMII            1
#define EMAC_GMII            2
#define EMAC_RGMII           3

/********************************************************/
/** PHY Mode Selection       */
#define  EMAC_INTERFACE   EMAC_RGMII

/********************************************************/
/* INTERRUPT */
#define ETH_INTR_SRC         (CY_GIG_ETH_IRQN0)
#define ETH_INTR_SRC_Q1      (CY_GIG_ETH_IRQN1)
#define ETH_INTR_SRC_Q2      (CY_GIG_ETH_IRQN2)

/* TX_DATA_PIN */
#define ETHx_TD0_PORT        CY_GIG_ETH_TD0_PORT
#define ETHx_TD0_PIN         CY_GIG_ETH_TD0_PIN
#define ETHx_TD0_PIN_MUX     CY_GIG_ETH_TD0_PIN_MUX

#define ETHx_TD1_PORT        CY_GIG_ETH_TD1_PORT
#define ETHx_TD1_PIN         CY_GIG_ETH_TD1_PIN
#define ETHx_TD1_PIN_MUX     CY_GIG_ETH_TD1_PIN_MUX

#define ETHx_TD2_PORT        CY_GIG_ETH_TD2_PORT
#define ETHx_TD2_PIN         CY_GIG_ETH_TD2_PIN
#define ETHx_TD2_PIN_MUX     CY_GIG_ETH_TD2_PIN_MUX

#define ETHx_TD3_PORT        CY_GIG_ETH_TD3_PORT
#define ETHx_TD3_PIN         CY_GIG_ETH_TD3_PIN
#define ETHx_TD3_PIN_MUX     CY_GIG_ETH_TD3_PIN_MUX

/* TX_CTRL_PIN */
#define ETHx_TX_CTL_PORT     CY_GIG_ETH_TX_CLK_PORT
#define ETHx_TX_CTL_PIN      CY_GIG_ETH_TX_CTL_PIN
#define ETHx_TX_CTL_PIN_MUX  CY_GIG_ETH_TX_CTL_PIN_MUX

/* RX_DATA_PIN */
#define ETHx_RD0_PORT        CY_GIG_ETH_RD0_PORT
#define ETHx_RD0_PIN         CY_GIG_ETH_RD0_PIN
#define ETHx_RD0_PIN_MUX     CY_GIG_ETH_RD0_PIN_MUX

#define ETHx_RD1_PORT        CY_GIG_ETH_RD1_PORT
#define ETHx_RD1_PIN         CY_GIG_ETH_RD1_PIN
#define ETHx_RD1_PIN_MUX     CY_GIG_ETH_RD1_PIN_MUX

#define ETHx_RD2_PORT        CY_GIG_ETH_RD2_PORT
#define ETHx_RD2_PIN         CY_GIG_ETH_RD2_PIN
#define ETHx_RD2_PIN_MUX     CY_GIG_ETH_RD2_PIN_MUX

#define ETHx_RD3_PORT        CY_GIG_ETH_RD3_PORT
#define ETHx_RD3_PIN         CY_GIG_ETH_RD3_PIN
#define ETHx_RD3_PIN_MUX     CY_GIG_ETH_RD3_PIN_MUX

/* RX_CTRL_PIN */
#define ETHx_RX_CTL_PORT     CY_GIG_ETH_RX_CTL_PORT
#define ETHx_RX_CTL_PIN      CY_GIG_ETH_RX_CTL_PIN
#define ETHx_RX_CTL_PIN_MUX  CY_GIG_ETH_RX_CTL_PIN_MUX

/* CLK_PORT_PIN */
#define ETHx_TX_CLK_PORT     CY_GIG_ETH_TX_CLK_PORT
#define ETHx_TX_CLK_PIN      CY_GIG_ETH_TX_CLK_PIN
#define ETHx_TX_CLK_PIN_MUX  CY_GIG_ETH_TX_CLK_PIN_MUX

#define ETHx_RX_CLK_PORT     CY_GIG_ETH_RX_CLK_PORT
#define ETHx_RX_CLK_PIN      CY_GIG_ETH_RX_CLK_PIN
#define ETHx_RX_CLK_PIN_MUX  CY_GIG_ETH_RX_CLK_PIN_MUX

/* REF_CLK */
#define ETHx_REF_CLK_PORT    CY_GIG_ETH_REF_CLK_PORT
#define ETHx_REF_CLK_PIN     CY_GIG_ETH_REF_CLK_PIN
#define ETHx_REF_CLK_PIN_MUX CY_GIG_ETH_REF_CLK_PIN_MUX

/* Management Data Clock */
#define ETHx_MDC_PORT        CY_GIG_ETH_MDC_PORT
#define ETHx_MDC_PIN         CY_GIG_ETH_MDC_PIN
#define ETHx_MDC_PIN_MUX     CY_GIG_ETH_MDC_PIN_MUX

/* Management Data Input/Output */
#define ETHx_MDIO_PORT       CY_GIG_ETH_MDIO_PORT
#define ETHx_MDIO_PIN        CY_GIG_ETH_MDIO_PIN
#define ETHx_MDIO_PIN_MUX    CY_GIG_ETH_MDIO_PIN_MUX

/* Bits masks to verify auto negotiation configured speed */
#define ANLPAR_10_Msk                           (0x00000020UL)  /**< 10BASE-Te Support */
#define ANLPAR_10_Pos                           (5UL)           /**< 10BASE-Te bit position */
#define ANLPAR_10FD_Msk                         (0x00000040UL)  /**< 10BASE-Te Full Duplex Support */
#define ANLPAR_10FD_Pos                         (6UL)           /**< 10BASE-Te Full Duplex bit position */

#define ANLPAR_TX_Msk                           (0x00000080UL)  /**< 100BASE-TX Support */
#define ANLPAR_TX_Pos                           (7UL)           /**< 100BASE-TX bit position */
#define ANLPAR_TXFD_Msk                         (0x00000100UL)  /**< 100BASE-TX Full Duplex Support */
#define ANLPAR_TXFD_Pos                         (8UL)           /**< 100BASE-TX Full Duplex bit position */
#define ANLPAR_T4_Msk                           (0x00000200UL)  /**< 100BASE-T4 Support */
#define ANLPAR_T4_Pos                           (9UL)           /**< 100BASE-T4 bit position */

#define STS1_1000BASE_T_HALFDUPLEX_Msk          (0x00000400UL)  /**< 1000BASE-T Half-Duplex Capable */
#define STS1_1000BASE_T_HALFDUPLEX_Pos          (10UL)          /**< 1000BASE-T Half-Duplex bit position */
#define STS1_1000BASE_T_FULLDUPLEX_Msk          (0x00000800UL)  /**< 1000BASE-T Full-Duplex Capable */
#define STS1_1000BASE_T_FULLDUPLEX_Pos          (11UL)          /**< 1000BASE-T Full-Duplex bit position */

/********************************************************/

/** PHY related constants    */
#define PHY_ADDR             (0) /* Value depends on PHY and its hardware configurations */
#define PHY_ID_DP83867IR     (0x2000A231) /* PHYIDR1=0x2000 PHYIDR2=0xA231 */

/************************START********************************/

struct rt_ifx_eth
{
    /* inherit from ethernet device */
    struct eth_device parent;
#ifndef PHY_USING_INTERRUPT_MODE
    rt_timer_t poll_link_timer;
#endif

    /* interface address info, hw address */
    rt_uint8_t  dev_addr[MAX_ADDR_LEN];
    /* ETH_Speed */
    rt_uint32_t    ETH_Speed;
    /* ETH_Duplex_Mode */
    rt_uint32_t    ETH_Mode;

    cy_stc_ephy_t                 phy_obj;
    ETH_Type                     *eth_base_type;
};

typedef struct rt_ifx_eth* rt_ifx_eth_t;

static cy_stc_ethif_wrapper_config_t stcWrapperConfig;
uint8_t *pRx_Q_buff_pool[CY_ETH_DEFINE_TOTAL_BD_PER_RXQUEUE];

static struct rt_ifx_eth ifx_eth_device;
static bool is_driver_configured = false;

static rt_uint8_t eth_mempool[Eth_Mempool_Num][CY_ETH_SIZE_MAX_FRAME];
static rt_uint8_t mempool_index = 0;

static rt_mailbox_t recv_frame_buffer_addr_mb = RT_NULL;

/************************END********************************/

/************************START********************************/

static void Cy_Ethx_InterruptHandler (void);
void cy_process_ethernet_data_cb( ETH_Type *eth_type, uint8_t *rx_buffer, uint32_t length );
void cy_notify_ethernet_rx_data_cb(ETH_Type *base, uint8_t **u8RxBuffer, uint32_t *u32Length);
struct pbuf *rt_ifx_eth_rx(rt_device_t dev);
rt_err_t rt_ifx_eth_tx(rt_device_t dev, struct pbuf *p);
static rt_err_t rt_ifx_eth_open(rt_device_t dev, rt_uint16_t oflag);
static rt_err_t rt_ifx_eth_close(rt_device_t dev);
static rt_ssize_t rt_ifx_eth_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size);
static rt_ssize_t rt_ifx_eth_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size);
static rt_err_t rt_ifx_eth_control(rt_device_t dev, int cmd, void *args);
static void phy_monitor_thread_entry(void *parameter);
static cy_en_ethif_speed_sel_t ecm_config_to_speed_sel( cy_ecm_phy_config_t *config);
static void eth_clock_config(cy_en_ethif_speed_sel_t speed_sel, cy_ecm_phy_speed_t phy_speed);
void phyRead(uint32_t phyId, uint32_t regAddress, uint32_t *value);
void phyWrite(uint32_t phyId, uint32_t regAddress, uint32_t value);
static void ethernet_portpins_init (cy_ecm_speed_type_t interface_speed_type);
static void init_phy_DP83867IR (ETH_Type *reg_base, cy_ecm_phy_config_t *ecm_phy_config, cy_stc_ephy_t *phy_obj);
cy_rslt_t cy_eth_driver_initialization(ETH_Type *reg_base, cy_ecm_phy_config_t *ecm_phy_config, cy_stc_ephy_t *phy_obj);
static void enable_phy_DP83867IR_extended_reg(ETH_Type *reg_base, cy_ecm_phy_config_t *ecm_phy_config);
static rt_err_t rt_ifx_eth_init(rt_device_t dev);

/************************END********************************/

/************************START********************************/

/** General Ethernet configuration  */
static cy_stc_ethif_mac_config_t stcENETConfig = {
                .bintrEnable         = 1,                           /** Interrupt enable  */
                .dmaDataBurstLen     = CY_ETHIF_DMA_DBUR_LEN_4,
                .u8dmaCfgFlags       = CY_ETHIF_CFG_DMA_FRCE_TX_BRST,
                .mdcPclkDiv          = CY_ETHIF_MDC_DIV_BY_48,      /** source clock is 80 MHz and MDC must be less than 2.5MHz   */
                .u8rxLenErrDisc      = 0,                           /** Length error frame not discarded  */
                .u8disCopyPause      = 0,
                .u8chkSumOffEn       = 0,                           /** Checksum for both Tx and Rx disabled    */
                .u8rx1536ByteEn      = 1,                           /** Enable receive frame up to 1536    */
                .u8rxJumboFrEn       = 0,
                .u8enRxBadPreamble   = 1,
                .u8ignoreIpgRxEr     = 0,
                .u8storeUdpTcpOffset = 0,
                .u8aw2wMaxPipeline   = 2,                           /** Value must be > 0   */
                .u8ar2rMaxPipeline   = 2,                           /** Value must be > 0   */
                .u8pfcMultiQuantum   = 0,
                .pstcWrapperConfig   = &stcWrapperConfig,
                .pstcTSUConfig       = NULL, //&stcTSUConfig,               /** TSU settings    */
                .btxq0enable         = 1,                           /** Tx Q0 Enabled   */
                .btxq1enable         = 0,                           /** Tx Q1 Disabled  */
                .btxq2enable         = 0,                           /** Tx Q2 Disabled  */
                .brxq0enable         = 1,                           /** Rx Q0 Enabled   */
                .brxq1enable         = 0,                           /** Rx Q1 Disabled  */
                .brxq2enable         = 0,                           /** Rx Q2 Disabled  */
};

/** Interrupt configurations    */
static cy_stc_ethif_intr_config_t stcInterruptConfig = {
                .btsu_time_match        = 0,          /** Timestamp unit time match event */
                .bwol_rx                = 0,          /** Wake-on-LAN event received */
                .blpi_ch_rx             = 0,          /** LPI indication status bit change received */
                .btsu_sec_inc           = 0,          /** TSU seconds register increment */
                .bptp_tx_pdly_rsp       = 0,          /** PTP pdelay_resp frame transmitted */
                .bptp_tx_pdly_req       = 0,          /** PTP pdelay_req frame transmitted */
                .bptp_rx_pdly_rsp       = 0,          /** PTP pdelay_resp frame received */
                .bptp_rx_pdly_req       = 0,          /** PTP pdelay_req frame received */
                .bptp_tx_sync           = 0,          /** PTP sync frame transmitted */
                .bptp_tx_dly_req        = 0,          /** PTP delay_req frame transmitted */
                .bptp_rx_sync           = 0,          /** PTP sync frame received */
                .bptp_rx_dly_req        = 0,          /** PTP delay_req frame received */
                .bext_intr              = 0,          /** External input interrupt detected */
                .bpause_frame_tx        = 0,          /** Pause frame transmitted */
                .bpause_time_zero       = 0,          /** Pause time reaches zero or zero pause frame received */
                .bpause_nz_qu_rx        = 0,          /** Pause frame with non-zero quantum received */
                .bhresp_not_ok          = 0,          /** DMA HRESP not OK */
                .brx_overrun            = 1,          /** Rx overrun error */
                .bpcs_link_change_det   = 0,          /** Link status change detected by PCS */
                .btx_complete           = 1,          /** Frame has been transmitted successfully */
                .btx_fr_corrupt         = 1,          /** Tx frame corrupted */
                .btx_retry_ex_late_coll = 1,          /** Retry limit exceeded or late collision */
                .btx_underrun           = 1,          /** Tx underrun */
                .btx_used_read          = 1,          /** Used bit set has been read in Tx descriptor list */
                .brx_used_read          = 1,          /** Used bit set has been read in Rx descriptor list */
                .brx_complete           = 1,          /** Frame received successfully and stored */
                .bman_frame             = 0,          /** Management frame sent */
};

//回调函数注册
static cy_stc_ethif_cb_t stcInterruptCB = {
    /** Callback functions  */
                .rxframecb  = cy_process_ethernet_data_cb,  //接收处理回调函数
                .txerrorcb  = NULL,             //发送错误回调函数
                .txcompletecb = NULL,          //发送完成回调函数
                .tsuSecondInccb = NULL,                     //TSU 计时器每秒递增时触发的回调
                .rxgetbuff = cy_notify_ethernet_rx_data_cb  //获取空闲缓冲区
};
/************************END********************************/

/************************START********************************/

/**                      PortPinName.outVal||  driveMode               hsiom             ||intEdge||intMask||vtrip||slewRate||driveSel||vregEn||ibufMode||vtripSel||vrefSel||vohSel*/
static cy_stc_gpio_pin_config_t ethx_tx0   = {0x00, CY_GPIO_DM_STRONG_IN_OFF, ETHx_TD0_PIN_MUX,     0,       0,       0,     0,        0,        0,      0,        0,        0,       0};
static cy_stc_gpio_pin_config_t ethx_tx1   = {0x00, CY_GPIO_DM_STRONG_IN_OFF, ETHx_TD1_PIN_MUX,     0,       0,       0,     0,        0,        0,      0,        0,        0,       0};
static cy_stc_gpio_pin_config_t ethx_tx2   = {0x00, CY_GPIO_DM_STRONG_IN_OFF, ETHx_TD2_PIN_MUX,     0,       0,       0,     0,        0,        0,      0,        0,        0,       0};
static cy_stc_gpio_pin_config_t ethx_tx3   = {0x00, CY_GPIO_DM_STRONG_IN_OFF, ETHx_TD3_PIN_MUX,     0,       0,       0,     0,        0,        0,      0,        0,        0,       0};
static cy_stc_gpio_pin_config_t ethx_txctl = {0x00, CY_GPIO_DM_STRONG_IN_OFF, ETHx_TX_CTL_PIN_MUX,  0,       0,       0,     0,        0,        0,      0,        0,        0,       0};
static cy_stc_gpio_pin_config_t ethx_rx0   = {0x00, CY_GPIO_DM_HIGHZ,         ETHx_RD0_PIN_MUX,     0,       0,       0,     0,        0,        0,      0,        0,        0,       0};
static cy_stc_gpio_pin_config_t ethx_rx1   = {0x00, CY_GPIO_DM_HIGHZ,         ETHx_RD1_PIN_MUX,     0,       0,       0,     0,        0,        0,      0,        0,        0,       0};
static cy_stc_gpio_pin_config_t ethx_rx2   = {0x00, CY_GPIO_DM_HIGHZ,         ETHx_RD2_PIN_MUX,     0,       0,       0,     0,        0,        0,      0,        0,        0,       0};
static cy_stc_gpio_pin_config_t ethx_rx3   = {0x00, CY_GPIO_DM_HIGHZ,         ETHx_RD3_PIN_MUX,     0,       0,       0,     0,        0,        0,      0,        0,        0,       0};
static cy_stc_gpio_pin_config_t ethx_rxctl = {0x00, CY_GPIO_DM_HIGHZ,         ETHx_RX_CTL_PIN_MUX,  0,       0,       0,     0,        0,        0,      0,        0,        0,       0};
static cy_stc_gpio_pin_config_t ethx_txclk = {0x00, CY_GPIO_DM_STRONG_IN_OFF, ETHx_TX_CLK_PIN_MUX,  0,       0,       0,     0,        0,        0,      0,        0,        0,       0};
static cy_stc_gpio_pin_config_t ethx_rxclk  = {0x00, CY_GPIO_DM_HIGHZ,       ETHx_RX_CLK_PIN_MUX,  0,       0,       0,     0,        0,        0,      0,        0,        0,       0};
static cy_stc_gpio_pin_config_t ethx_refclk = {0x00, CY_GPIO_DM_HIGHZ,        ETHx_REF_CLK_PIN_MUX, 0,       0,       0,     0,        0,        0,      0,        0,        0,       0};
static cy_stc_gpio_pin_config_t ethx_mdc   = {0x00, CY_GPIO_DM_STRONG_IN_OFF, ETHx_MDC_PIN_MUX,     0,       0,       0,     0,        3,        0,      0,        0,        0,       0};
static cy_stc_gpio_pin_config_t ethx_mdio  = {0x00, CY_GPIO_DM_STRONG,        ETHx_MDIO_PIN_MUX,    0,       0,       0,     0,        3,        0,      0,        0,        0,       0};

/** Enable Ethernet interrupts  */
static const cy_stc_sysint_t irq_cfg_ethx_q0 = {.intrSrc  = ((NvicMux3_IRQn << 16) | ETH_INTR_SRC),    .intrPriority=3UL};
static const cy_stc_sysint_t irq_cfg_ethx_q1 = {.intrSrc  = ((NvicMux3_IRQn << 16) | ETH_INTR_SRC_Q1), .intrPriority=3UL};
static const cy_stc_sysint_t irq_cfg_ethx_q2 = {.intrSrc  = ((NvicMux3_IRQn << 16) | ETH_INTR_SRC_Q2), .intrPriority=3UL};

/************************END********************************/

/** Interrupt handlers for Ethernet 1     */
static void Cy_Ethx_InterruptHandler (void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    Cy_ETHIF_DecodeEvent(ETH_REG_BASE);

    /* leave interrupt */
    rt_interrupt_leave();
}

void cy_process_ethernet_data_cb( ETH_Type *eth_type, uint8_t *rx_buffer, uint32_t length )
{
    rt_err_t result;

    result = rt_mb_send(recv_frame_buffer_addr_mb, (rt_ubase_t)rx_buffer);
    if (result != RT_EOK)
    {
        LOG_I("Send_Recv_Buffer_Adder_MB err = %d", result);
    }

    result = eth_device_ready(&(ifx_eth_device.parent));
    if (result != RT_EOK)
    {
        LOG_I("RxCpltCallback err = %d", result);
    }
}

void cy_notify_ethernet_rx_data_cb(ETH_Type *base, uint8_t **u8RxBuffer, uint32_t *u32Length)
{
        *u8RxBuffer = eth_mempool[mempool_index++];
        if(mempool_index >= Eth_Mempool_Num)
        {
                mempool_index = 0;
        }
    *u32Length = CY_ETH_SIZE_MAX_FRAME;
}

struct pbuf *rt_ifx_eth_rx(rt_device_t dev)
{
    rt_err_t result;
    rt_uint32_t *rx_buffer;
    rt_uint32_t length = CY_ETH_SIZE_MAX_FRAME;
    struct pbuf *recv_frame = RT_NULL;
    struct pbuf *temp = RT_NULL;
    rt_uint32_t bufferoffset = 0;
    rt_uint32_t payloadlength = 0;

    result = rt_mb_recv(recv_frame_buffer_addr_mb, (rt_ubase_t *)&rx_buffer, 1000);
    if(result != RT_EOK)
    {
        LOG_I("Recv_Recv_Buffer_Adder_MB err = %d", result);
    }

    recv_frame = pbuf_alloc(PBUF_RAW, length, PBUF_POOL);
    if(recv_frame != RT_NULL)
    {
        if(rx_buffer != RT_NULL)
                {
                    for(temp = recv_frame; temp != RT_NULL; temp = temp->next)
                    {
                            payloadlength = temp->len;
                            rt_memcpy((uint8_t *)((uint8_t *)temp->payload), (uint8_t *)((uint8_t *)rx_buffer + bufferoffset), (payloadlength < length ? payloadlength : length));
                            bufferoffset = bufferoffset + payloadlength;
                            length = length - payloadlength;
                    }
                }
    }

    return recv_frame;
}

rt_err_t rt_ifx_eth_tx(rt_device_t dev, struct pbuf *p)
{
    struct pbuf *q;
    cy_en_ethif_status_t eth_status;
    rt_uint32_t framelen = 0;
    rt_uint8_t data_buffer[CY_ETH_SIZE_MAX_FRAME];
    rt_ifx_eth_t ifx_device = (rt_ifx_eth_t)dev;

    if (p->tot_len > (u16_t)CY_ETH_SIZE_MAX_FRAME)
    {
        return -RT_ERROR;
    }
    for(q = p; q != NULL; q = q->next)
    {
        rt_memcpy(data_buffer + framelen, q->payload, q->len);
        framelen += (uint32_t)q->len;
    }

    eth_status = Cy_ETHIF_TransmitFrame(ifx_device->eth_base_type, data_buffer, framelen, CY_ETH_QS0_0, true);
    if(eth_status != CY_ETHIF_SUCCESS)
    {
        rt_kprintf("failed to send outgoing packet:[%d]\n", eth_status);
    }
    return RT_EOK;
}

static rt_err_t rt_ifx_eth_open(rt_device_t dev, rt_uint16_t oflag)
{
    LOG_D("emac open");
    return RT_EOK;
}

static rt_err_t rt_ifx_eth_close(rt_device_t dev)
{
    LOG_D("emac close");
    return RT_EOK;
}

static rt_ssize_t rt_ifx_eth_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    LOG_D("emac read");
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_ssize_t rt_ifx_eth_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    LOG_D("emac write");
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_err_t rt_ifx_eth_control(rt_device_t dev, int cmd, void *args)
{
    rt_ifx_eth_t eth_device = (rt_ifx_eth_t)dev;
    switch (cmd)
    {
    case NIOCTL_GADDR:
        /* get mac address */
        if (args)
        {
            SMEMCPY(args, eth_device->dev_addr, 6);
        }
        else
        {
            return -RT_ERROR;
        }
        break;

    default :
        break;
    }

    return RT_EOK;
}

static void phy_monitor_thread_entry(void *parameter)
{
    static rt_uint32_t phy_status = 0;
    rt_uint32_t phy_status_now = 0;

    while (1)
    {
        phy_status_now = Cy_EPHY_GetLinkStatus(&ifx_eth_device.phy_obj);
        if(phy_status_now != phy_status)
        {
            if(phy_status_now == 1UL)
            {
                rt_kprintf("Link Up\n");
                eth_device_linkchange(&ifx_eth_device.parent, RT_TRUE);
            }
            else
            {
                rt_kprintf("Link Dowm\n");
                eth_device_linkchange(&ifx_eth_device.parent, RT_FALSE);
            }
            phy_status = phy_status_now;
        }
        rt_thread_mdelay(1000);
    }
}

static cy_en_ethif_speed_sel_t ecm_config_to_speed_sel( cy_ecm_phy_config_t *config)
{
    cy_en_ethif_speed_sel_t speed_sel;

    if( config->interface_speed_type == CY_ECM_SPEED_TYPE_MII)
    {
        speed_sel = (cy_en_ethif_speed_sel_t)config->phy_speed;
    }
    else if( config->interface_speed_type == CY_ECM_SPEED_TYPE_GMII)
    {
        speed_sel = CY_ETHIF_CTL_GMII_1000;
    }
    else if( config->interface_speed_type == CY_ECM_SPEED_TYPE_RGMII)
    {
        if(config->phy_speed == CY_ECM_PHY_SPEED_10M)
        {
            speed_sel = CY_ETHIF_CTL_RGMII_10;
        }
        else if(config->phy_speed == CY_ECM_PHY_SPEED_100M)
        {
            speed_sel = CY_ETHIF_CTL_RGMII_100;
        }
        else
        {
            speed_sel = CY_ETHIF_CTL_RGMII_1000;
        }
    }
    else
    {
        speed_sel = (config->phy_speed == CY_ECM_PHY_SPEED_10M)?CY_ETHIF_CTL_RMII_10 : CY_ETHIF_CTL_RMII_100;
    }

    return speed_sel;
}

static void eth_clock_config(cy_en_ethif_speed_sel_t speed_sel, cy_ecm_phy_speed_t phy_speed)
{
    if((speed_sel == CY_ETHIF_CTL_MII_10) && (phy_speed == CY_ECM_PHY_SPEED_10M))
        stcWrapperConfig.stcInterfaceSel = CY_ETHIF_CTL_MII_10;       /** 10 Mbps MII */
    else if((speed_sel == CY_ETHIF_CTL_MII_100) && (phy_speed == CY_ECM_PHY_SPEED_100M))
        stcWrapperConfig.stcInterfaceSel = CY_ETHIF_CTL_MII_100;      /** 100 Mbps MII */
    else if((speed_sel == CY_ETHIF_CTL_GMII_1000) && (phy_speed == CY_ECM_PHY_SPEED_1000M))
        stcWrapperConfig.stcInterfaceSel = CY_ETHIF_CTL_GMII_1000;    /** 1000 Mbps GMII */
    else if((speed_sel == CY_ETHIF_CTL_RGMII_10) && (phy_speed == CY_ECM_PHY_SPEED_10M))
        stcWrapperConfig.stcInterfaceSel = CY_ETHIF_CTL_RGMII_10;     /** 10 Mbps RGMII */
    else if((speed_sel == CY_ETHIF_CTL_RGMII_100) && (phy_speed == CY_ECM_PHY_SPEED_100M))
        stcWrapperConfig.stcInterfaceSel = CY_ETHIF_CTL_RGMII_100;    /** 100 Mbps RGMII */
    else if((speed_sel == CY_ETHIF_CTL_RGMII_1000) && (phy_speed == CY_ECM_PHY_SPEED_1000M))
        stcWrapperConfig.stcInterfaceSel = CY_ETHIF_CTL_RGMII_1000;    /** 1000 Mbps RGMII */
    else if((speed_sel == CY_ETHIF_CTL_RMII_10) && (phy_speed == CY_ECM_PHY_SPEED_10M))
        stcWrapperConfig.stcInterfaceSel = CY_ETHIF_CTL_RMII_10;      /** 10 Mbps RMII */
    else if((speed_sel == CY_ETHIF_CTL_RMII_100) && (phy_speed == CY_ECM_PHY_SPEED_100M))
        stcWrapperConfig.stcInterfaceSel = CY_ETHIF_CTL_RMII_100;     /** 100 Mbps RMII */
    else
        stcWrapperConfig.stcInterfaceSel = CY_ETHIF_CTL_RGMII_1000;  /** Error in configuration */

    stcWrapperConfig.bRefClockSource = CY_ETHIF_EXTERNAL_HSIO;     /** Assigning Ref_Clk to HSIO clock; use an external clock from HSIO  */

    if(phy_speed == CY_ECM_PHY_SPEED_10M)
        stcWrapperConfig.u8RefClkDiv = 10;                         /** RefClk: 25 MHz; divide Refclock by 10 to have a 2.5-MHz Tx clock  */
    else if(phy_speed == CY_ECM_PHY_SPEED_100M)
        stcWrapperConfig.u8RefClkDiv = 1;                          /** RefClk: 25 MHz; divide Refclock by 1 to have a 25-MHz Tx clock  */
    else if(phy_speed == CY_ECM_PHY_SPEED_1000M)
        stcWrapperConfig.u8RefClkDiv = 1;                          /** RefClk: 25 MHz; divide Refclock by 1 to have a 25-MHz Tx clock  */
    else /*(phy_speed == CY_ECM_PHY_SPEED_1000M)*/
        stcWrapperConfig.u8RefClkDiv = 1;                          /** RefClk: 125 MHz; divide Refclock by 1 to have a 125-MHz Tx clock || Although only relevant in RGMII/GMII modes */

    return;
}

/* 读取PHY芯片函数 */
void phyRead(uint32_t phyId, uint32_t regAddress, uint32_t *value)
{
    *value = Cy_ETHIF_PhyRegRead(ETH_REG_BASE, regAddress, phyId);
}

/* 写入PHY芯片函数 */
void phyWrite(uint32_t phyId, uint32_t regAddress, uint32_t value)
{
    Cy_ETHIF_PhyRegWrite(ETH_REG_BASE, regAddress, value, phyId);
}

/* GPIO 初始化 */
static void ethernet_portpins_init (cy_ecm_speed_type_t interface_speed_type)
{
    (void)interface_speed_type;
    Cy_GPIO_Pin_Init(ETHx_TD0_PORT, ETHx_TD0_PIN, &ethx_tx0);                       /** TX0 */
    Cy_GPIO_Pin_Init(ETHx_TD1_PORT, ETHx_TD1_PIN, &ethx_tx1);                       /** TX1 */
    Cy_GPIO_Pin_Init(ETHx_TD2_PORT, ETHx_TD2_PIN, &ethx_tx2);                       /** TX2 */
    Cy_GPIO_Pin_Init(ETHx_TD3_PORT, ETHx_TD3_PIN, &ethx_tx3);                       /** TX3 */

    Cy_GPIO_Pin_Init(ETHx_TX_CTL_PORT, ETHx_TX_CTL_PIN, &ethx_txctl);               /** TX_CTL  */

    Cy_GPIO_Pin_Init(ETHx_RD0_PORT, ETHx_RD0_PIN, &ethx_rx0);                       /** RX0 */
    Cy_GPIO_Pin_Init(ETHx_RD1_PORT, ETHx_RD1_PIN, &ethx_rx1);                       /** RX1 */
    Cy_GPIO_Pin_Init(ETHx_RD2_PORT, ETHx_RD2_PIN, &ethx_rx2);                       /** RX2 */
    Cy_GPIO_Pin_Init(ETHx_RD3_PORT, ETHx_RD3_PIN, &ethx_rx3);                       /** RX3 */

    Cy_GPIO_Pin_Init(ETHx_RX_CTL_PORT, ETHx_RX_CTL_PIN, &ethx_rxctl);               /** RX_CTL  */

    Cy_GPIO_Pin_Init(ETHx_REF_CLK_PORT, ETHx_REF_CLK_PIN, &ethx_refclk);            /** REF_CLK */

    Cy_GPIO_Pin_Init(ETHx_TX_CLK_PORT, ETHx_TX_CLK_PIN, &ethx_txclk);               /** TX_CLK  */
    Cy_GPIO_Pin_Init(ETHx_RX_CLK_PORT, ETHx_RX_CLK_PIN, &ethx_rxclk);               /** RX_CLK  */

    Cy_GPIO_Pin_Init(ETHx_MDC_PORT,  ETHx_MDC_PIN, &ethx_mdc);                      /** MDC     */
    Cy_GPIO_Pin_Init(ETHx_MDIO_PORT, ETHx_MDIO_PIN, &ethx_mdio);                    /** MDIO    */
}

/* PHY芯片初始化 */
static void init_phy_DP83867IR (ETH_Type *reg_base, cy_ecm_phy_config_t *ecm_phy_config, cy_stc_ephy_t *phy_obj)
{
    cy_stc_ephy_config_t    phyConfig;
    cy_en_ethif_speed_sel_t speed_sel;
    uint32_t                value = 0;
    uint16_t                configured_hw_speed;
    cy_en_ethif_status_t    eth_status;

    /* Driver configuration is already done */
    if(is_driver_configured == true)
    {
        /* Initialize the PHY */
        Cy_EPHY_Init(phy_obj, phyRead, phyWrite);

        /* If driver already configured and the auto negotiation is enabled, replace the speed and mode by the auto negotiated values decided during driver initialization */
        if(ecm_phy_config->mode == CY_ECM_DUPLEX_AUTO || ecm_phy_config->phy_speed == CY_ECM_PHY_SPEED_AUTO)
        {
            phyRead( 0, REGISTER_ADDRESS_PHY_REG_BMCR, &value );
            cy_ecm_log_msg( CYLF_MIDDLEWARE, CY_LOG_ERR, "REGISTER_ADDRESS_PHY_REG_BMCR = 0x%X\n", (unsigned long)value );
            ecm_phy_config->mode = ((value & (REGISTER_PHY_REG_DUPLEX_MASK)) == 0) ? CY_ECM_DUPLEX_HALF : CY_ECM_DUPLEX_FULL;
            configured_hw_speed = value & (REGISTER_PHY_REG_SPEED_MASK);
            if(configured_hw_speed == REGISTER_PHY_REG_SPEED_MASK_10M)
            {
                ecm_phy_config->phy_speed = CY_ECM_PHY_SPEED_10M;
            }
            else if (configured_hw_speed == REGISTER_PHY_REG_SPEED_MASK_100M)
            {
                ecm_phy_config->phy_speed = CY_ECM_PHY_SPEED_100M;
            }
            else if(configured_hw_speed ==  REGISTER_PHY_REG_SPEED_MASK_1000M)
            {
                ecm_phy_config->phy_speed = CY_ECM_PHY_SPEED_1000M;
            }
        }
    }

    if(!is_driver_configured)
    {
        /* Auto Negotiation enable */
        if(ecm_phy_config->phy_speed == CY_ECM_PHY_SPEED_AUTO || ecm_phy_config->mode == CY_ECM_DUPLEX_AUTO)
        {
            eth_status = Cy_ETHIF_MdioInit(reg_base, &stcENETConfig);
            if (CY_ETHIF_SUCCESS != eth_status)
            {
                cy_ecm_log_msg( CYLF_MIDDLEWARE, CY_LOG_DEBUG, "Ethernet MAC Pre-Init failed with ethStatus=0x%X \n", eth_status );
                return;
            }
            cy_ecm_log_msg( CYLF_MIDDLEWARE, CY_LOG_DEBUG, "Ethernet MAC Pre-Init success \n", 0);

            /* Start auto negotiation */
            phyConfig.speed = (cy_en_ephy_speed_t)CY_ECM_PHY_SPEED_AUTO;
            phyConfig.duplex = (cy_en_ephy_duplex_t)CY_ECM_DUPLEX_AUTO;

            /* Initialize the PHY */
            Cy_EPHY_Init(phy_obj, phyRead, phyWrite);

            Cy_EPHY_Configure( phy_obj, &phyConfig );
            /* Required some delay to get PHY back to Run state */
            cy_rtos_delay_milliseconds(100);

            while (Cy_EPHY_GetAutoNegotiationStatus(phy_obj) != true)
            {
                cy_rtos_delay_milliseconds(100);
            }

            Cy_EPHY_getLinkPartnerCapabilities(phy_obj, &phyConfig);
            ecm_phy_config->phy_speed = (cy_ecm_phy_speed_t)phyConfig.speed;
            ecm_phy_config->mode = (cy_ecm_duplex_t)phyConfig.duplex;
        }

        speed_sel = ecm_config_to_speed_sel(ecm_phy_config);

        /* Update the configuration based on user input */
        eth_clock_config(speed_sel, ecm_phy_config->phy_speed);

        /** Initialize ENET MAC */
        eth_status = Cy_ETHIF_Init(reg_base, &stcENETConfig, &stcInterruptConfig);
        if (CY_ETHIF_SUCCESS != eth_status)
        {
            cy_ecm_log_msg( CYLF_MIDDLEWARE, CY_LOG_DEBUG, "Ethernet MAC Init failed with ethStatus=0x%X \n", eth_status );
            return;
        }
        if(!(ecm_phy_config->phy_speed == CY_ECM_PHY_SPEED_AUTO || ecm_phy_config->mode == CY_ECM_DUPLEX_AUTO))
        {
            /* Initialize the PHY */
            Cy_EPHY_Init(phy_obj, phyRead, phyWrite);
        }
        is_driver_configured = true;
    }
    cy_ecm_log_msg( CYLF_MIDDLEWARE, CY_LOG_DEBUG, "Register driver callbacks  \n", 0);
    stcInterruptCB.rxframecb  = cy_process_ethernet_data_cb;

    /* Reset the PHY */
    Cy_EPHY_Reset(phy_obj);
    Cy_ETHIF_PhyRegWrite(reg_base, 0x1F, 0x8000, PHY_ADDR); /* Ext-Reg CTRl: Perform a full reset, including all registers  */
    cy_rtos_delay_milliseconds(30);    /* Required delay of 30 ms to get PHY back to Run state after reset */

    Cy_EPHY_Discover(phy_obj);

     /* Check for supported PHYs */
    if (PHY_ID_DP83867IR != phy_obj->phyId)
    {
        cy_ecm_log_msg( CYLF_MIDDLEWARE, CY_LOG_DEBUG, "Not supported physical ID \n", 0);
        return;
    }
    phyConfig.duplex = ecm_phy_config->mode;
    phyConfig.speed = ecm_phy_config->phy_speed;

    Cy_EPHY_Configure(phy_obj, &phyConfig);

    /* Enable PHY extended registers */
    enable_phy_DP83867IR_extended_reg(reg_base, ecm_phy_config);

}

cy_rslt_t cy_eth_driver_initialization(ETH_Type *reg_base, cy_ecm_phy_config_t *ecm_phy_config, cy_stc_ephy_t *phy_obj)
{
    cy_rslt_t  result = CY_RSLT_SUCCESS;
    uint32_t   retry_count = 0;

    cy_ecm_log_msg( CYLF_MIDDLEWARE, CY_LOG_DEBUG, "%s(): START \n", __FUNCTION__ );

    /** Configure Ethernet port pins    */
    ethernet_portpins_init(ecm_phy_config->interface_speed_type);

    cy_ecm_log_msg( CYLF_MIDDLEWARE, CY_LOG_DEBUG, "GPIO_INIT_FINISH \n", __FUNCTION__ );

    Cy_SysInt_Init(&irq_cfg_ethx_q0, Cy_Ethx_InterruptHandler);
    Cy_SysInt_Init(&irq_cfg_ethx_q1, Cy_Ethx_InterruptHandler);
    Cy_SysInt_Init(&irq_cfg_ethx_q2, Cy_Ethx_InterruptHandler);

    cy_ecm_log_msg( CYLF_MIDDLEWARE, CY_LOG_DEBUG, "ETH_REG_BASE=[%p] reg_base = [%p] \n", ETH_REG_BASE, reg_base );

    /* rx Q0 buffer pool */
    stcENETConfig.pRxQbuffPool[0] = (cy_ethif_buffpool_t *)&pRx_Q_buff_pool;
    stcENETConfig.pRxQbuffPool[1] = NULL;

    /** Initialize PHY  */
    init_phy_DP83867IR(reg_base, ecm_phy_config, phy_obj);

    NVIC_ClearPendingIRQ(NvicMux3_IRQn);
    NVIC_EnableIRQ(NvicMux3_IRQn);

    Cy_ETHIF_RegisterCallbacks(reg_base, &stcInterruptCB);

    cy_ecm_log_msg( CYLF_MIDDLEWARE, CY_LOG_DEBUG, "%s():retry_count:[%d] END \n", __FUNCTION__, retry_count );

    return result;
}

static void enable_phy_DP83867IR_extended_reg(ETH_Type *reg_base, cy_ecm_phy_config_t *ecm_phy_config)
{
    if(ecm_phy_config->phy_speed == CY_ECM_PHY_SPEED_100M)
    {
        Cy_ETHIF_PhyRegWrite(reg_base, 0x10, 0x5028, PHY_ADDR); /** Disable auto negotiation for MDI/MDI-X **/
    }
    else if(ecm_phy_config->phy_speed == CY_ECM_PHY_SPEED_1000M || ecm_phy_config->phy_speed == CY_ECM_PHY_SPEED_AUTO)
    {
        uint32_t    u32ReadData;
        Cy_ETHIF_PhyRegWrite(reg_base, 0x0D, 0x001F, PHY_ADDR);         /** Begin write access to the extended register     */
        Cy_ETHIF_PhyRegWrite(reg_base, 0x0E, 0x0170, PHY_ADDR);
        Cy_ETHIF_PhyRegWrite(reg_base, 0x0D, 0x401F, PHY_ADDR);
        u32ReadData = Cy_ETHIF_PhyRegRead(reg_base, (uint8_t)0x0E, PHY_ADDR);
        u32ReadData = u32ReadData & 0x0000;                                 /** Change the I/O impedance on the PHY    */
        u32ReadData = u32ReadData | 0x010C;
        Cy_ETHIF_PhyRegWrite(reg_base, 0x0E, u32ReadData, PHY_ADDR);         /** Enable clock from the PHY -> Route it to the MCU    */
        u32ReadData = Cy_ETHIF_PhyRegRead(reg_base, (uint8_t)0x0E, PHY_ADDR);
    }
    else
    {
        /* Do nothing */
    }

    /** Disable RGMII by accessing the extended register set || Please read datasheet section 8.4.2.1 for the procedure in detail */
    Cy_ETHIF_PhyRegWrite(reg_base, 0x0D, 0x001F, PHY_ADDR);                     /** REGCR  */
    Cy_ETHIF_PhyRegWrite(reg_base, 0x0E, 0x0032, PHY_ADDR);                     /** ADDAR, 0x0032 RGMII config register  */
    Cy_ETHIF_PhyRegWrite(reg_base, 0x0D, 0x401F, PHY_ADDR);                     /** REGCR; will force the next write/read access non-incremental  */

    if(ecm_phy_config->interface_speed_type != CY_ECM_SPEED_TYPE_RGMII)
    {
        Cy_ETHIF_PhyRegWrite(reg_base, 0x0E, 0x0000, PHY_ADDR);                     /** Disable RGMII  */
        Cy_ETHIF_PhyRegRead(reg_base, (uint8_t)0x0E, PHY_ADDR);       /** Read RGMII mode status  */
    }
    else
    {
        Cy_ETHIF_PhyRegWrite(reg_base, 0x0E, 0x00D3, PHY_ADDR);                     /** Enable Tx and RX clock delay in the RGMII configuration register  */

        Cy_ETHIF_PhyRegWrite(reg_base, 0x0D, 0x001F, PHY_ADDR);                     /** REGCR  */
        Cy_ETHIF_PhyRegWrite(reg_base, 0x0E, 0x0086, PHY_ADDR);                     /** ADDAR; 0x0086 delay config register  */
        Cy_ETHIF_PhyRegWrite(reg_base, 0x0D, 0x401F, PHY_ADDR);                     /** REGCR; will force the next write/read access non-incremental  */
        Cy_ETHIF_PhyRegWrite(reg_base, 0x0E, 0x0066, PHY_ADDR);                     /** Adjust Tx and Rx clock delays in the PHY  */
    }/* EMAC_INTERFACE != EMAC_RGMII */

    Cy_ETHIF_PhyRegWrite(reg_base, 0x1F, 0x4000, PHY_ADDR);         /** CTRL   */
    cy_rtos_delay_milliseconds(30);/** Some more delay to get the PHY adapted to new interface */
    Cy_ETHIF_PhyRegRead(reg_base, (uint8_t)0x11, PHY_ADDR);
}

static rt_err_t rt_ifx_eth_init(rt_device_t dev)
 {
    rt_err_t state = RT_EOK;
    cy_ecm_phy_config_t           phy_interface_type;

    ifx_eth_device.eth_base_type = ETH_INTERFACE_TYPE;
    cy_ecm_log_msg( CYLF_MIDDLEWARE, CY_LOG_INFO, "Device's eth_base_type is:%d\n", ETH_INTERFACE_TYPE);

    phy_interface_type.interface_speed_type = CY_ECM_SPEED_TYPE_RGMII;
    phy_interface_type.phy_speed = CY_ECM_PHY_SPEED_1000M;
    phy_interface_type.mode = CY_ECM_DUPLEX_FULL;
    cy_ecm_log_msg( CYLF_MIDDLEWARE, CY_LOG_INFO, "Using default phy_interface_type\nType :%d\nSpeed :%d\nMode :%d\n"
                ,phy_interface_type.interface_speed_type
                ,phy_interface_type.phy_speed
                ,phy_interface_type.mode);

    cy_eth_driver_initialization(ifx_eth_device.eth_base_type, &phy_interface_type, &(ifx_eth_device.phy_obj));

    return state;
}

static int rt_hw_ifx_eth_init(void)
{
    rt_err_t result = RT_EOK;

    recv_frame_buffer_addr_mb = rt_mb_create("Eth_rx_mb", Eth_Mempool_Num, RT_IPC_FLAG_PRIO);
    if(recv_frame_buffer_addr_mb == RT_NULL)
    {
        LOG_I("Eth MailBox Init Fail");
    }

    for(rt_uint8_t i = 0; i < CY_ETH_DEFINE_TOTAL_BD_PER_RXQUEUE; i++)
    {
        pRx_Q_buff_pool[i] = rt_malloc(sizeof(uint8) * CY_ETH_SIZE_MAX_FRAME);
    }

    ifx_eth_device.dev_addr[0] = 0x00;
    ifx_eth_device.dev_addr[1] = 0x03;
    ifx_eth_device.dev_addr[2] = 0x19;
    ifx_eth_device.dev_addr[3] = 0x45;
    ifx_eth_device.dev_addr[4] = 0x00;
    ifx_eth_device.dev_addr[5] = 0x00;
    cy_ecm_log_msg( CYLF_MIDDLEWARE, CY_LOG_INFO, "Assigning default MAC address 00-03-19-45-00-00\n", 0);

    ifx_eth_device.parent.parent.init       = rt_ifx_eth_init;
    ifx_eth_device.parent.parent.open       = rt_ifx_eth_open;
    ifx_eth_device.parent.parent.close      = rt_ifx_eth_close;
    ifx_eth_device.parent.parent.read       = rt_ifx_eth_read;
    ifx_eth_device.parent.parent.write      = rt_ifx_eth_write;
    ifx_eth_device.parent.parent.control    = rt_ifx_eth_control;
    ifx_eth_device.parent.parent.user_data  = RT_NULL;

    ifx_eth_device.parent.eth_rx            = rt_ifx_eth_rx;
    ifx_eth_device.parent.eth_tx            = rt_ifx_eth_tx;

    result = eth_device_init(&(ifx_eth_device.parent), "e0");
    if(result != RT_EOK)
    {
        LOG_E("emac device init faild: %d", result);
        result = -RT_ERROR;
        return result;
    }
    else
    {
        LOG_D("emac device init success");
    }

    rt_thread_t tid;
    tid = rt_thread_create("phy",
                           phy_monitor_thread_entry,
                           RT_NULL,
                           1024,
                           RT_THREAD_PRIORITY_MAX - 2,
                           2);
    if (tid != RT_NULL)
    {
        rt_thread_startup(tid);
    }
    else
    {
        LOG_E("phy thread init faild: %d", result);
        result = -RT_ERROR;
        return result;
    }

        return result;
}
INIT_DEVICE_EXPORT(rt_hw_ifx_eth_init);
