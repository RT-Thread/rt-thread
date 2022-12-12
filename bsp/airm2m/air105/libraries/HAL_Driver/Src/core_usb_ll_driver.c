/*
 * Copyright (c) 2022 OpenLuat & AirM2M
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "user.h"
#if 0
#define USB_FIFO_MAX    (512)
#define USB_FIFO_DW_DAX (128)

/**
  * 结构说明：调试控制寄存器(USBPHY_CR1)结构
  * 偏移地址：0x0108
  * 初 始 值：0x004921AE
  * 属    性：RW
  * 宽    度：32bit
  */
typedef union _USBPHY_CR1_TypeDef
{
    uint32_t d32;
    struct{
        uint32_t txpreemphasistune          : 1;    /* */
        uint32_t txrisetune                 : 2;    /* */
        uint32_t txvreftune                 : 4;    /* */
        uint32_t txfslstune                 : 4;    /* */
        uint32_t sqrxtune                   : 3;    /* */
        uint32_t compdistune                : 3;    /* */
        uint32_t otgtune                    : 3;    /* */
        uint32_t loopback_enb               : 1;    /* */
        uint32_t otg_disable                : 1;    /* */
        uint32_t commononn                  : 1;    /* */
        uint32_t vatestenb                  : 1;    /* */
        uint32_t lsbist                     : 1;    /* */
        uint32_t fsbist                     : 1;    /* */
        uint32_t hsbist                     : 1;    /* */
        uint32_t bisten                     : 1;    /* */
        uint32_t usb_iddq                   : 1;    /* */
        uint32_t stop_ck_for_suspend        : 1;    /* */
        uint32_t bist_done                  : 1;    /* */
        uint32_t bist_error                 : 1;    /* */
    } b;
} USBPHY_CR1_TypeDef;

/**
  * 结构说明：调试控制寄存器(USBPHY_CR3)结构
  * 偏移地址：0x010C
  * 初 始 值：0x00000000
  * 属    性：RW
  * 宽    度：32bit
  */
typedef union _USBPHY_CR3_TypeDef
{
    uint32_t d32;
    struct{
        uint32_t idpullup                   : 1;    /* 用于操作 USB PHY的idpullup，启动PHY探测ID状态 */
        uint32_t iddig                      : 1;    /* PHY 输出的ID状态信号，用于软件查询 */
        uint32_t reserved2_31               : 29;
    } b;
} USBPHY_CR3_TypeDef;

typedef struct
{
    // Common USB Registers. 0x00 - 0x0F.
    __IO uint8_t FADDR;          // Peripheral Mode Only.
    union
    {
        __IO uint8_t POWER;
        struct
        {
            __IO uint8_t en_suspendM    : 1;
            __IO uint8_t suspend_mode   : 1;
            __IO uint8_t resume         : 1;
            __IO uint8_t reset          : 1;
            __IO uint8_t HS_mode        : 1;    //不支持
            __IO uint8_t HS_enab        : 1;    //不支持
            __IO uint8_t soft_conn      : 1;     /* Periphera mode only */
            __IO uint8_t ISO_update     : 1;     /* Periphera mode only */
        } POWER_b;
    };
    union
    {
        __IO uint16_t INTRTX;
        struct
        {
            __IO uint16_t EP0_intp        : 1;
            __IO uint16_t EP1_tx_intp     : 1;
            __IO uint16_t EP2_tx_intp     : 1;
            __IO uint16_t EP3_tx_intp     : 1;
            __IO uint16_t EP4_tx_intp     : 1;
            __IO uint16_t EP5_tx_intp     : 1;
            __IO uint16_t EP6_tx_intp     : 1;
            __IO uint16_t EP7_tx_intp     : 1;
            __IO uint16_t EP8_tx_intp     : 1;
            __IO uint16_t EP9_tx_intp     : 1;
            __IO uint16_t EP10_tx_intp    : 1;
            __IO uint16_t EP11_tx_intp    : 1;
            __IO uint16_t EP12_tx_intp    : 1;
            __IO uint16_t EP13_tx_intp    : 1;
            __IO uint16_t EP14_tx_intp    : 1;
            __IO uint16_t EP15_tx_intp    : 1;
        } INTRTX_b;
    };
    union
    {
        __IO     uint16_t    INTRRX;
        struct
        {
            uint16_t reserved0               : 1;
            uint16_t EP1_rx_intp             : 1;
            uint16_t EP2_rx_intp             : 1;
            uint16_t EP3_rx_intp             : 1;
            uint16_t EP4_rx_intp             : 1;
            uint16_t EP5_rx_intp             : 1;
            uint16_t EP6_rx_intp             : 1;
            uint16_t EP7_rx_intp             : 1;
            uint16_t EP8_rx_intp             : 1;
            uint16_t EP9_rx_intp             : 1;
            uint16_t EP10_rx_intp            : 1;
            uint16_t EP11_rx_intp            : 1;
            uint16_t EP12_rx_intp            : 1;
            uint16_t EP13_rx_intp            : 1;
            uint16_t EP14_rx_intp            : 1;
            uint16_t EP15_rx_intp            : 1;
        } INTRRX_b;
    };
    union
    {
        __IO    uint16_t    INTRTXE;
        struct
        {
            uint16_t en_EP0_intp        : 1;
            uint16_t en_EP1_tx_intp     : 1;
            uint16_t en_EP2_tx_intp     : 1;
            uint16_t en_EP3_tx_intp     : 1;
            uint16_t en_EP4_tx_intp     : 1;
            uint16_t en_EP5_tx_intp     : 1;
            uint16_t en_EP6_tx_intp     : 1;
            uint16_t en_EP7_tx_intp     : 1;
            uint16_t en_EP8_tx_intp     : 1;
            uint16_t en_EP9_tx_intp     : 1;
            uint16_t en_EP10_tx_intp    : 1;
            uint16_t en_EP11_tx_intp    : 1;
            uint16_t en_EP12_tx_intp    : 1;
            uint16_t en_EP13_tx_intp    : 1;
            uint16_t en_EP14_tx_intp    : 1;
            uint16_t en_EP15_tx_intp    : 1;
        } INTRTXE_b;
    };
    union
    {
        __IO    uint16_t    INTRRXE;
        struct
        {
            uint16_t reserved0                  : 1;
            uint16_t en_EP1_rx_intp             : 1;
            uint16_t en_EP2_rx_intp             : 1;
            uint16_t en_EP3_rx_intp             : 1;
            uint16_t en_EP4_rx_intp             : 1;
            uint16_t en_EP5_rx_intp             : 1;
            uint16_t en_EP6_rx_intp             : 1;
            uint16_t en_EP7_rx_intp             : 1;
            uint16_t en_EP8_rx_intp             : 1;
            uint16_t en_EP9_rx_intp             : 1;
            uint16_t en_EP10_rx_intp            : 1;
            uint16_t en_EP11_rx_intp            : 1;
            uint16_t en_EP12_rx_intp            : 1;
            uint16_t en_EP13_rx_intp            : 1;
            uint16_t en_EP14_rx_intp            : 1;
            uint16_t en_EP15_rx_intp            : 1;
        } INTRRXE_b;
    };
    union
    {
        __IO     uint8_t     INTRUSB;
        struct
        {
            uint8_t suspend         : 1;    /* Set when Suspend signaling is detected on the bus. Only valid in Peripheral mode. */
            uint8_t resume          : 1;    /* Set when Resume signaling is detected on the bus while the MUSBMHDRC is in Suspend mode. */
            uint8_t reset_babble    : 1;    /* Reset: Set in Peripheral mode when Reset signaling is detected on the bus.
                                             * Babble: Set in Host mode when babble is detected. Note: Only active after first SOF has been sent.
                                             */
            uint8_t sof             : 1;    /* Set when a new frame starts.  */
            uint8_t conn            : 1;    /* Set when a device connection is detected. Only valid in Host mode. Valid at all transaction speeds. */
            uint8_t discon          : 1;    /* Set in Host mode when a device disconnect is detected. Set in Peripheral mode when a session ends. Valid at all transaction speeds. */
            uint8_t sess_req        : 1;    /* Set when Session Request signaling has been detected. Only valid when MUSBMHDRC is A device. */
            uint8_t VBus_error      : 1;    /* Set when VBus drops below the VBus Valid threshold during a session. Only valid when MUSBMHDRC is A device. */
        } INTRUSB_b;
    };
    union
    {
        __IO    uint8_t     INTRUSBE;
        struct
        {
            uint8_t en_suspend         : 1;
            uint8_t en_resume          : 1;
            uint8_t en_reset_babble    : 1;
            uint8_t en_sof             : 1;
            uint8_t en_conn            : 1;
            uint8_t en_discon          : 1;
            uint8_t en_sess_req        : 1;
            uint8_t en_VBus_error      : 1;
        } INTRUSBE_b;
    };
    union
    {
        __IO     uint16_t    FRAME;
        struct
        {
            uint16_t frame_number       : 11;
            uint16_t reserved11_15      : 5;    /* Always return 0 */
        } FRAME_b;
    };
    __IO    uint8_t     INDEX;
    __IO    uint8_t     TESTMODE;
    // Indexed CSR. 0x10 - 0x1F.
    union
    {
        __IO    uint16_t    TXMAXP;
        struct
        {
            __IO   uint16_t max_payload_tran           : 11;   /* Bits 10:0 define(in bytes)the maximum payload transmitted in single transaction.
                                                         * The value set can be up to 1024 bytes but is subject to the constraints place by
                                                         * the USB Specification on packet sizes for Bulk,Interrupt and Isochronous transfers
                                                         * in Full-speed and High-speed operations.
                                                         */
            __IO   uint16_t ex_max                     : 5;
        } TXMAXP_b;
    };
    union
    {
        __IO    uint8_t     CSR0L;
        __IO    uint8_t     TXCSRL;
        struct
        {
            __IO   uint8_t rx_pkt_rdy                  : 1;    /* This bit is set when a data packet has been received. An interrupt is
                                                         * generated when this bit is set. The CPU clear this bit by setting the
                                                         * ServicedRxPktRdy bit.
                                                         */
            __IO   uint8_t tx_pkt_rdy                  : 1;    /* The CPU sets this bits after loading a data packet into the FIFO. It is clear
                                                         * automatically when a data packet has been transmitted. An interrupt is also
                                                         * generated at this point(if enabled).
                                                         */
            __IO   uint8_t sent_stall                  : 1;    /* This bit is set when a STALL handshake is transmitted.
                                                         * The CPU should clear this bit.
                                                         */
            __IO   uint8_t data_end                    : 1;    /* The CPU sets this bit:
                                                         * 1. When setting TxPktRdy for the last data packet.
                                                         * 2. When clearing RxPktRdy after unloading the last data packet.
                                                         * 3. When setting TxPktRdy for zero length data packet.
                                                         * It is cleared automatically.
                                                         */
            __IO   uint8_t setup_end                   : 1;    /* This bit will be set when a control transaction ends before the DataEnd
                                                         * bit has been set. An interrupt will be generated and the FIFO flushed at
                                                         * this time.The bit is cleared by the CPU writing a 1 to the ServicedSetupEnd bit.
                                                         */
            __IO   uint8_t send_stall                  : 1;    /* The CPU write a 1 to this bit to terminate the current transaction.
                                                         * The STALL handshake will be transmitted and then this bit will be
                                                         * cleared automatically.
                                                         */
            __IO   uint8_t serviced_rxpktrdy           : 1;    /* The CPU write a 1 to this bit to clear the RxPktRdy bit.
                                                         * It is Cleared automatically.
                                                         */
            __IO   uint8_t serviced_setupend           : 1;    /* The CPU write a 1 to this bit to clear the SetupEnd bit.
                                                         * It is Cleared automatically.
                                                         */
        } CSR0L_DEV_b;
        struct
        {
            __IO   uint8_t rx_pkt_rdy                  : 1;    /* This bit is set when a data packet has been received.An interrupt is generated
                                                         * (If enabled)when this bit set.The CPU should clear this bit when the packet has
                                                         * been read from the FIFO.
                                                         */
            __IO   uint8_t tx_pkt_rdy                  : 1;    /* The CPU sets this bit after loading a data packet into the FIFO.It is cleared
                                                         * automatically when a data packet has been transmitted. An interrupt is also
                                                         * generated at this point(If enabled).
                                                         */
            __IO   uint8_t rx_stall                    : 1;    /* This bit is set when a STALL handshake is received. The CPU should clear this bit. */
            __IO   uint8_t setup_pkt                   : 1;    /* The CPU sets this bit,at the TxPktRdy bit is set,to  send a SETUP token instead
                                                         * of an OUT token for the transaction. Note: Setting this bit also clear the Data
                                                         * Toggle.
                                                         */
            __IO   uint8_t error                       : 1;    /* This bit will be set when three attempts have been made to perform a transaction
                                                         * with no response from the peripheral.The CPU should clear this bit.An interrupt
                                                         * is generated when this bit is set.
                                                         */
            __IO   uint8_t req_pkt                     : 1;    /* The CPU sets this bit to request an IN transaction.
                                                         * It is cleared when RxPktRdy is set.
                                                         */
            __IO   uint8_t status_pkt                  : 1;    /* The CPU sets this bit at the same time as the TxPktRdy or ReqPkt bit is set,
                                                         * to perform a status stage transaction. Setting this bit ensures that the data
                                                         * toggle is set to 1 so that a DATA1 packet is used for the Status Stage transaction.
                                                         */
            __IO   uint8_t nak_timeout                 : 1;    /* This bit will be set when Endpoint 0 is halted following the receipt for longer
                                                         * than the time set by the NAKLimit0 register. The CPU should clear this bit to allow
                                                         * the endpoint to continue.
                                                         */
        } CSR0L_HOST_b;
        struct
        {
            __IO   uint8_t tx_pkt_rdy                  : 1;    /* The CPU sets this bit after loading a data packet into the FIFO. */
            __IO   uint8_t fifo_not_empty              : 1;    /* The USB sets this bit when there is at least 1 packet in the TX FIFO.  */
            __IO   uint8_t under_run                   : 1;    /* The USB sets this bit if an IN token is received when TxPktRdy is not set. The CPU should clear this bit.  */
            __IO   uint8_t flush_fifo                  : 1;    /* The CPU writes a 1 to this bit to flush the latest packet from the endpoint TX FIFO */
            __IO   uint8_t send_stall                  : 1;    /* The CPU writes a 1 to this bit to issue a STALL handshake to an IN token.The CPU
                                                         * clears this bit to terminate the stall condition.
                                                         * Note:This bit has no effect where the endpoint is being used for Isochronous transfers.
                                                         */
            __IO   uint8_t sent_stall                  : 1;    /* This bit is set when a STALL handshake is transmitted.The FIFO is flushed and
                                                         * the TxPktRdy bit is cleared(see below).The CPU should clear this bit.
                                                         */
            __IO   uint8_t clr_data_tog                : 1;    /* The CPU writes a 1 to this bit to reset the endpoint data toggle to 0. */
            __IO   uint8_t incomp_tx                   : 1;    /* When the endpoint is being used for high-bandwidth Isochronous,this bit is set to
                                                         * indicate where a large packet has been split into 2 or 3 packets for transmission
                                                         * but insufficient IN tokens have been received to send all the parts.
                                                         * Note:In anything other than isochronous transfers,this bit will always return 0.
                                                         */
        } TXCSRL_DEV_b;
        struct
        {
            __IO   uint8_t tx_pkt_rdy                  : 1;    /* The CPU sets this bit after loading a data packet into the FIFO. */
            __IO   uint8_t fifo_not_empty              : 1;    /* The USB sets this bit when there is at least 1 packet in the TX FIFO.  */
            __IO   uint8_t error                       : 1;
            __IO   uint8_t flush_fifo                  : 1;    /* The CPU writes a 1 to this bit to flush the latest packet from the endpoint TX FIFO */
            __IO   uint8_t setup_Pkt                   : 1;
            __IO   uint8_t Rx_stall                    : 1;
            __IO   uint8_t clr_data_tog                : 1;    /* The CPU writes a 1 to this bit to reset the endpoint data toggle to 0. */
            __IO   uint8_t NAK_timeout_incompTx        : 1;
        } TXCSRL_HOST_b;

    };
    union
    {
        __IO    uint8_t     CSR0H;
        __IO    uint8_t     TXCSRH;
        struct
        {
            __IO   uint8_t flush_fifo              : 1;    /* The CPU writes a 1 to this bit to flush the next packet to be transmitted/read from
                                                     * the Endpoint 0 FIFO. The FIFO pointer is reset and the TxPktRdy/RxPktRdy bit(below) is
                                                     * cleared. Note:FlushFIFO should only be used when TxPktRdy/RxPktRdy is set.At other
                                                     * times, it may cause data to be corrupted.
                                                     */
            __IO   uint8_t reserved1_7             : 7;    /* Unused. Return 0 when resd. */
        } CSR0H_DEV_b;
        struct
        {
            __IO   uint8_t flush_fifo              : 1;    /* The CPU writes a 1 to this bit to flush the next packet to be transmitted/read from
                                                     * the Endpoint 0 FIFO. The FIFO pointer is reset and the TxPktRdy/RxPktRdy bit(below) is
                                                     * cleared. Note:FlushFIFO should only be used when TxPktRdy/RxPktRdy is set.At other
                                                     * times, it may cause data to be corrupted.
                                                     */
            __IO   uint8_t data_toggle             : 1;    /* When read,this bit indicates the current state of the Endpoint 0 data toggle. If D10
                                                     * is high,this bit may be written with the written with the required setting of the data
                                                     * toggle.If D10 is low,any value written to this bit is ignored.
                                                     */
            __IO   uint8_t data_toggle_wr_en       : 1;    /* The CPU written a 1 to this bit to enable the current state of Endpoint 0 data toggle
                                                     * to be written(see Data Toggle bit,below).This bit is automatically cleared once the new
                                                     * value is written.
                                                     */
            __IO   uint8_t dis_ping                : 1;    /* The CPU writes a 1 to this bit to instruct the core not to issue PING tokens in data
                                                     * and status phases of a high-speed Control transfer(for use with devices that do not
                                                     * respond to PING).
                                                     */
            __IO   uint8_t reserved1_7             : 4;    /* Unused. Return 0 when resd. */
        } CSR0H_HOST_b;
        struct
        {
            __IO   uint8_t reserved0_1                 : 2;
            __IO   uint8_t dma_req_mode                : 1;
            __IO   uint8_t frc_data_tog                : 1;
            __IO   uint8_t dma_req_enab                : 1;
            __IO   uint8_t mode                        : 1;
            __IO   uint8_t iso                         : 1;
            __IO   uint8_t auto_set                    : 1;
        } TXCSRH_DEV_b;
        struct
        {
            __IO   uint8_t data_toggle                 : 1;
            __IO   uint8_t data_toggle_wren            : 1;
            __IO   uint8_t dma_req_mode                : 1;
            __IO   uint8_t frc_data_tog                : 1;
            __IO   uint8_t dma_req_enab                : 1;
            __IO   uint8_t mode                        : 1;
            __IO   uint8_t reserved6                   : 1;
            __IO   uint8_t auto_set                    : 1;
        } TXCSRH_HOST_b;
    };
    union
    {
        __IO    uint16_t    RXMAXP;
        struct
        {
            __IO   uint16_t max_payload_tran               : 11;
            __IO   uint16_t ex_max                         : 5;
        } RXMAXP_b;
    };
    union
    {
        __IO    uint8_t     RXCSRL;
        struct
        {
            __IO   uint8_t rx_pkt_rdy                  : 1;    /* This bit is set when a data packet has been received */
            __IO   uint8_t fifo_full                   : 1;    /* */
            __IO   uint8_t over_run                    : 1;    /* */
            __IO   uint8_t data_error                  : 1;    /* */
            __IO   uint8_t flush_fifo                  : 1;
            __IO   uint8_t send_stall                  : 1;    /* The CPU writes a 1 to this bit to issue a STALL handshake. */
            __IO   uint8_t sent_stall                  : 1;    /* This bit is set when a STALL handshake is transmitted. The CPU should clear this bit.  */
            __IO   uint8_t clr_data_tog                : 1;
        } RXCSRL_DEV_b;
        struct
        {
            __IO   uint8_t rx_pkt_rdy                  : 1;    /* This bit is set when a data packet has been received */
            __IO   uint8_t fifo_full                   : 1;    /* */
            __IO   uint8_t error                       : 1;    /* */
            __IO   uint8_t data_error                  : 1;    /* */
            __IO   uint8_t flush_fifo                  : 1;
            __IO   uint8_t ReqPkt                      : 1;
            __IO   uint8_t RxStall                     : 1;
            __IO   uint8_t clr_data_tog                : 1;
        } RXCSRL_HOST_b;
    };
    union
    {
        __IO    uint8_t     RXCSRH;
        struct
        {
            __IO   uint8_t incomp_rx               : 1;
            __IO   uint8_t reserved1_2             : 2;
            __IO   uint8_t dma_req_mode            : 1;
            __IO   uint8_t dis_nyet_pid_error      : 1;
            __IO   uint8_t dma_req_enab            : 1;
            __IO   uint8_t iso                     : 1;
            __IO   uint8_t auto_clear              : 1;
        } RXCSRH_DEV_b;
        struct
        {
            __IO   uint8_t incomp_rx               : 1;
            __IO   uint8_t data_toggle             : 1;
            __IO   uint8_t data_toggle_wren        : 1;
            __IO   uint8_t dma_req_mode            : 1;
            __IO   uint8_t PID_error               : 1;
            __IO   uint8_t dma_req_enab            : 1;
            __IO   uint8_t auto_req                : 1;
            __IO   uint8_t auto_clear              : 1;
        } RXCSRH_HOST_b;
    };

    union
    {
        __IO     uint8_t     COUNT0;
        __IO     uint16_t    RXCOUNT;
        struct
        {
            __IO     uint8_t ep0_rx_count                    : 7;
            __IO     uint8_t reserved7                       : 1;
        } COUNT0_b;
    };
    union
    {
        __IO    uint8_t     TYPE0;      // Host Mode Only.
        __IO    uint8_t     TXTYPE;     // Host Mode Only.
        struct
        {
            __IO    uint8_t reserved0_5             : 6;    /* Reserved */
            __IO    uint8_t speed                   : 2;    /* Operating speed of the target device :
                                                     *      00:Unused(Note: If selected,the target will be using the same connectionn speed as the core.)
                                                     *      01:High
                                                     *      10:Full
                                                     *      11:Low
                                                     */
        } TYPE0_b;
        struct
        {
            __IO    uint8_t target_EP_number        : 4;    /* Operating speed of the target device when the core is configured with the
                                                     * multipoint option:
                                                     *      00: Unused                  01: High
                                                     *      10: Full                    11: Low
                                                     * When the core is not configured with the multipoint option these bits should
                                                     * not be accessed.
                                                     */
            __IO    uint8_t protocol                : 2;    /* The CPU should set this to select the required protocol for TX endpoint:
                                                     *       00: Control       01: Isochronous
                                                     *       10: Bulk          11: Interrupt
                                                     */
            __IO    uint8_t speed                   : 2;    /* Operating speed of the target device when the core is configured with
                                                     * the multipoint option:
                                                     *      00:Unused        01: High      10: Full      11:Low
                                                     * when the core is not configured with the multipoint option these bits
                                                     * should not be accessed.
                                                     */
        } TXTYPE_b;
    };
    union
    {
        __IO    uint8_t     NAKLIMIT0;  // Host Mode Only.
        __IO    uint8_t     TXINTERVAL; // Host Mode Only.
        struct
        {
            __IO    uint8_t Endpoint0_NAK_Limit         : 5;    /* Endpoint 0 NAK limit (m) */
            __IO    uint8_t reserved5_7                 : 3;    /* Reserve */
        } NAKLIMIT0_b;
        struct
        {
            __IO    uint8_t Tx_polling_interval      :8;
        } TXINTERVAL_b;
    };
    union
    {
        __IO    uint8_t     RXTYPE;         // Host Mode Only.
        struct
        {
            __IO    uint8_t target_EP_number        : 4;    /* Operating speed of the target device when the core is configured with the
                                                     * multipoint option:
                                                     *      00: Unused                  01: High
                                                     *      10: Full                    11: Low
                                                     * When the core is not configured with the multipoint option these bits should
                                                     * not be accessed.
                                                     */
            __IO    uint8_t protocol                : 2;    /* The CPU should set this to select the required protocol for TX endpoint:
                                                     *       00: Control       01: Isochronous
                                                     *       10: Bulk          11: Interrupt
                                                     */
            __IO    uint8_t speed                   : 2;    /* Operating speed of the target device when the core is configured with
                                                     * the multipoint option:
                                                     *      00:Unused        01: High      10: Full      11:Low
                                                     * when the core is not configured with the multipoint option these bits
                                                     * should not be accessed.
                                                     */
        } RXTYPE_b;
    };

    __IO    uint8_t     RXINTERVAL;     // Host Mode Only.
            uint8_t     UNUSED0;
    union
    {
        __IO     uint8_t     CONFIGDATA;
        __IO     uint8_t     FIFOSIZE;
        struct
        {
            __IO     uint8_t utmi_data_width             : 1;    /* Indicates selected UTMI+ data width. Always 0 indicating 8 bits. */
            __IO     uint8_t soft_cone                   : 1;    /* Always "1" . Indicates Soft Connect/Disconnect.  */
            __IO     uint8_t dyn_fifo_sizing             : 1;    /* When set to "1" indicates Dynamic FIFO Sizing option selected.  */
            __IO     uint8_t hb_txe                      : 1;    /* When set to "1" indicates High-bandwidth TX ISO Endpoint Support selected */
            __IO     uint8_t hb_rxe                      : 1;    /* When set to "1" indicates High-bandwidth Rx ISO Endpoint Support selected.  */
            __IO     uint8_t big_endian                  : 1;    /* Always "0". Indicates Little Endian ordering.  */
            __IO     uint8_t mp_txe                      : 1;    /* When set to "1" automatic splitting of bulk packets is selected */
            __IO     uint8_t mp_rxe                      : 1;    /* When set to "1" automatic amalgamation of bulk packets is selected  */
        } CONFIGDATA_b;
        struct
        {
            __IO     uint8_t tx_fifo_size            : 4;
            __IO     uint8_t rx_fifo_size            : 4;
        } b;
    };
    union
    {
        // FIFOS, EP0 - EP15 0x20 - 0x5F.
        __IO    uint8_t     byte;
        __IO    uint16_t    word;
        __IO    uint32_t    dword;
    } FIFOX[16];

    // OTG, DynFIFO + Version. 0x60 - 0x6F.
    union
    {
        __IO    uint8_t     DEVCTL;
        struct
        {
            __IO    uint8_t session             : 1;        /* When operation as an 'A' device,this bit is set or cleared by the CPU to
                                                     * start or end a session. When operating as a 'B' device,this bit is set/cleared
                                                     * by the MUSBMHDRC when a session starts/ends. It is also set by the CPU to initiate
                                                     * the Session Request Protocol.When the MUSBMHDRC is in Suspend mode,the bit may be
                                                     * cleared by the CPU to perform a software disconnect.Note:Clearing this bit when the
                                                     * core is not suspended will result in undefined behavior.
                                                     */
            __IO    uint8_t host_req            : 1;        /* When set,the MUSBMHDRC will initiate the Host Negotiation when Suspend
                                                     * mode is entered.It is cleared when Host Negotiation is completed.
                                                     */
            __IO    uint8_t host_mode           : 1;        /* This Read-only bit is set when the MUSBMHDRC is acting as a Host. */
            __IO    uint8_t VBus                : 2;        /* These Read-only bits encode the current VBus level as follows:
                                                     *            D4      D3       Meaning
                                                     *             0       0       Below SessionEnd
                                                     *             0       1       Above SessionEnd,below AValid
                                                     *             1       0       Above AValid,below VBus Valid
                                                     *             1       1       Above VBus Valid
                                                     */
            __IO    uint8_t LSDev               : 1;        /* This Read-only bit is set when a low-speed device has been detected being
                                                     * connected to the port. Only valid in Host mode.
                                                     */
            __IO    uint8_t FSDev               : 1;        /* This Read-only bit is set when a full-speed or high-speed device has been
                                                     * detected being connected to the port.(High-speed device are distinguished
                                                     * from full-speed by checking for high-speed chirps when the device is reset.)
                                                     * Only valid in Host mode.
                                                     */
            __IO    uint8_t B_Device            : 1;        /* This Read-only bit indicates whether the MUSBMHDRC is operating
                                                     * as the 'A' device or the 'B' device.
                                                     *      0 => 'A' device;         1 => 'B' device.
                                                     * Only valid while a session is in progress. To determine the role
                                                     * when no session is in progress, set the session bit and read this bit.
                                                     * NOTE: If the core is in Force_Host mode(i.e. a session has been started
                                                     * with Testmode.D7 = 1),this bit will indicate the state of the HOSTDISCON
                                                     * input signal from the PHY.
                                                     */
        } DEVCTL_b;
    };
    union
    {
        __IO    uint8_t     MISC;
        struct
        {
            __IO    uint8_t rx_edma             : 1;        /* 1'b0:DMA_REQ signal for all OUT Endpoints will be de-asserted when MAXP
                                                     *      bytes have been read to an endpoint.This is late mode.
                                                     * 1'b1:DMA_REQ signal for all OUT Endpoints will be de-asserted when MAXP-8
                                                     *      bytes have been read to an endpoint.This is early mode.
                                                     */
            __IO    uint8_t tx_edma             : 1;        /* 1'b0:DMA_REQ signal for all IN Endpoints will be de-asserted when MAXP
                                                     *      bytes have been written to an endpoint.This is late mode.
                                                     * 1'b1:DMA_REQ signal for all IN Endpoints will be de-asserted when MAXP-8
                                                     *      bytes have been written to an endpoint.This is early mode.
                                                     */
            __IO    uint8_t reserved2_7         : 6;        /* These bits are reserved. */
        } MISC_b;
    };
    union
    {
        __IO    uint8_t     TXFIFOSZ;
        struct
        {
            __IO    uint8_t size                        : 4;
            __IO    uint8_t double_packet_buffer        : 1;
            __IO    uint8_t reserved5_7                 : 3;
        } TXFIFOSZ_b;
    };
    union
    {
        __IO    uint8_t     RXFIFOSZ;
        struct
        {
            __IO    uint8_t size                        : 4;
            __IO    uint8_t double_packet_buffer        : 1;
            __IO    uint8_t reserved5_7                 : 3;
        } RXFIFOSZ_b;
    };
    __IO    uint16_t    TXFIFOADD;
    __IO    uint16_t    RXFIFOADD;

    union
    {
        __O     uint32_t    VCONTROL;
        __IO     uint32_t    VSTATUS;
    }VCONTROL_VSTATUS;
    union
    {
        __IO     uint16_t    HWVERS;
        struct
        {
            __IO     uint16_t minor_version_number           : 10;
            __IO     uint16_t major_version_number           : 5;
            __IO     uint16_t rc                             : 1;
        } HWVERS_b;
    };

            uint8_t     UNUSED1[2];
    // ULPI & Addnl. Config. registers. 0x70 - 0x7F.
    __IO    uint8_t     ULPIVBUSCONTROL;
    __IO    uint8_t     ULPICARKITCONTROL;
    __IO    uint8_t     ULPIINTMASK;
    __IO     uint8_t     ULPIINTSRC;
    __IO    uint8_t     ULPIREGDATA;
    __IO    uint8_t     ULPIREGADDR;
    __IO    uint8_t     ULPIREGCONTROL;
    __IO     uint8_t     ULPIRAWDATA;
    union
    {
        __IO     uint8_t     EPINFO;
        struct
        {
            __IO     uint8_t tx_endpoint         : 4;
            __IO     uint8_t rx_endpoint         : 4;
        } EPINFO_b;
    };
    union
    {
        __IO     uint8_t     RAMINFO;
        struct
        {
            __IO     uint8_t ram_bits            : 4;
            __IO     uint8_t dma_chans           : 4;
        } RAMINFO_b;
    };
    union
    {
        __IO    uint8_t     LINKINFO;
        struct
        {
            __IO    uint8_t wtid                : 4;
            __IO    uint8_t wtcon               : 4;
        } LINKINFO_b;
    };

    __IO    uint8_t     VPLEN;
    __IO    uint8_t     HS_EOF1;
    __IO    uint8_t     FS_EOF1;
    __IO    uint8_t     LS_EOF1;
    union
    {
        __IO    uint8_t     SOFT_RST;
        struct
        {
            __IO    uint8_t nrst                : 1;
            __IO    uint8_t nrstx               : 1;
            __IO    uint8_t reserved2_7         : 6;
        } SOFT_RST_b;
    };

    struct
    {
        // TADDR Epn (n = 0 - 15). 0x80 - 0xFF.
        __IO    uint8_t     TXFUNCADDR;
                uint8_t     UNUSED0;
        __IO    uint8_t     TXHUBADDR;
        __IO    uint8_t     TXHUBPORT;
        __IO    uint8_t     RXFUNCADDR;
                uint8_t     UNUSED1;
        __IO    uint8_t     RXHUBADDR;
        __IO    uint8_t     RXHUBPORT;
    } AMCS[16];
    struct
    {
        // CSR EPn (n = 0 - 15). 0x100 - 0x1FF;
        union
        {
            __IO    uint16_t    TXMAXP;
            struct
            {
                __IO   uint16_t max_payload_tran           : 11;   /* Bits 10:0 define(in bytes)the maximum payload transmitted in single transaction.
                                                             * The value set can be up to 1024 bytes but is subject to the constraints place by
                                                             * the USB Specification on packet sizes for Bulk,Interrupt and Isochronous transfers
                                                             * in Full-speed and High-speed operations.
                                                             */
                __IO   uint16_t ex_max                     : 5;
            } TXMAXP_b;
        };
        union
        {
            __IO    uint8_t     CSR0L;
            __IO    uint8_t     TXCSRL;
            struct
            {
                __IO   uint8_t rx_pkt_rdy                  : 1;    /* This bit is set when a data packet has been received. An interrupt is
                                                             * generated when this bit is set. The CPU clear this bit by setting the
                                                             * ServicedRxPktRdy bit.
                                                             */
                __IO   uint8_t tx_pkt_rdy                  : 1;    /* The CPU sets this bits after loading a data packet into the FIFO. It is clear
                                                             * automatically when a data packet has been transmitted. An interrupt is also
                                                             * generated at this point(if enabled).
                                                             */
                __IO   uint8_t sent_stall                  : 1;    /* This bit is set when a STALL handshake is transmitted.
                                                             * The CPU should clear this bit.
                                                             */
                __IO   uint8_t data_end                    : 1;    /* The CPU sets this bit:
                                                             * 1. When setting TxPktRdy for the last data packet.
                                                             * 2. When clearing RxPktRdy after unloading the last data packet.
                                                             * 3. When setting TxPktRdy for zero length data packet.
                                                             * It is cleared automatically.
                                                             */
                __IO   uint8_t setup_end                   : 1;    /* This bit will be set when a control transaction ends before the DataEnd
                                                             * bit has been set. An interrupt will be generated and the FIFO flushed at
                                                             * this time.The bit is cleared by the CPU writing a 1 to the ServicedSetupEnd bit.
                                                             */
                __IO   uint8_t send_stall                  : 1;    /* The CPU write a 1 to this bit to terminate the current transaction.
                                                             * The STALL handshake will be transmitted and then this bit will be
                                                             * cleared automatically.
                                                             */
                __IO   uint8_t serviced_rxpktrdy           : 1;    /* The CPU write a 1 to this bit to clear the RxPktRdy bit.
                                                             * It is Cleared automatically.
                                                             */
                __IO   uint8_t serviced_setupend           : 1;    /* The CPU write a 1 to this bit to clear the SetupEnd bit.
                                                             * It is Cleared automatically.
                                                             */
            } CSR0L_DEV_b;
            struct
            {
                __IO   uint8_t rx_pkt_rdy                  : 1;    /* This bit is set when a data packet has been received.An interrupt is generated
                                                             * (If enabled)when this bit set.The CPU should clear this bit when the packet has
                                                             * been read from the FIFO.
                                                             */
                __IO   uint8_t tx_pkt_rdy                  : 1;    /* The CPU sets this bit after loading a data packet into the FIFO.It is cleared
                                                             * automatically when a data packet has been transmitted. An interrupt is also
                                                             * generated at this point(If enabled).
                                                             */
                __IO   uint8_t rx_stall                    : 1;    /* This bit is set when a STALL handshake is received. The CPU should clear this bit. */
                __IO   uint8_t setup_pkt                   : 1;    /* The CPU sets this bit,at the TxPktRdy bit is set,to  send a SETUP token instead
                                                             * of an OUT token for the transaction. Note: Setting this bit also clear the Data
                                                             * Toggle.
                                                             */
                __IO   uint8_t error                       : 1;    /* This bit will be set when three attempts have been made to perform a transaction
                                                             * with no response from the peripheral.The CPU should clear this bit.An interrupt
                                                             * is generated when this bit is set.
                                                             */
                __IO   uint8_t req_pkt                     : 1;    /* The CPU sets this bit to request an IN transaction.
                                                             * It is cleared when RxPktRdy is set.
                                                             */
                __IO   uint8_t status_pkt                  : 1;    /* The CPU sets this bit at the same time as the TxPktRdy or ReqPkt bit is set,
                                                             * to perform a status stage transaction. Setting this bit ensures that the data
                                                             * toggle is set to 1 so that a DATA1 packet is used for the Status Stage transaction.
                                                             */
                __IO   uint8_t nak_timeout                 : 1;    /* This bit will be set when Endpoint 0 is halted following the receipt for longer
                                                             * than the time set by the NAKLimit0 register. The CPU should clear this bit to allow
                                                             * the endpoint to continue.
                                                             */
            } CSR0L_HOST_b;
            struct
            {
                __IO   uint8_t tx_pkt_rdy                  : 1;    /* The CPU sets this bit after loading a data packet into the FIFO. */
                __IO   uint8_t fifo_not_empty              : 1;    /* The USB sets this bit when there is at least 1 packet in the TX FIFO.  */
                __IO   uint8_t under_run                   : 1;    /* The USB sets this bit if an IN token is received when TxPktRdy is not set. The CPU should clear this bit.  */
                __IO   uint8_t flush_fifo                  : 1;    /* The CPU writes a 1 to this bit to flush the latest packet from the endpoint TX FIFO */
                __IO   uint8_t send_stall                  : 1;    /* The CPU writes a 1 to this bit to issue a STALL handshake to an IN token.The CPU
                                                             * clears this bit to terminate the stall condition.
                                                             * Note:This bit has no effect where the endpoint is being used for Isochronous transfers.
                                                             */
                __IO   uint8_t sent_stall                  : 1;    /* This bit is set when a STALL handshake is transmitted.The FIFO is flushed and
                                                             * the TxPktRdy bit is cleared(see below).The CPU should clear this bit.
                                                             */
                __IO   uint8_t clr_data_tog                : 1;    /* The CPU writes a 1 to this bit to reset the endpoint data toggle to 0. */
                __IO   uint8_t incomp_tx                   : 1;    /* When the endpoint is being used for high-bandwidth Isochronous,this bit is set to
                                                             * indicate where a large packet has been split into 2 or 3 packets for transmission
                                                             * but insufficient IN tokens have been received to send all the parts.
                                                             * Note:In anything other than isochronous transfers,this bit will always return 0.
                                                             */
            } TXCSRL_DEV_b;
            struct
            {
                __IO   uint8_t tx_pkt_rdy                  : 1;    /* The CPU sets this bit after loading a data packet into the FIFO. */
                __IO   uint8_t fifo_not_empty              : 1;    /* The USB sets this bit when there is at least 1 packet in the TX FIFO.  */
                __IO   uint8_t error                       : 1;
                __IO   uint8_t flush_fifo                  : 1;    /* The CPU writes a 1 to this bit to flush the latest packet from the endpoint TX FIFO */
                __IO   uint8_t setup_Pkt                   : 1;
                __IO   uint8_t Rx_stall                    : 1;
                __IO   uint8_t clr_data_tog                : 1;    /* The CPU writes a 1 to this bit to reset the endpoint data toggle to 0. */
                __IO   uint8_t NAK_timeout_incompTx        : 1;
            } TXCSRL_HOST_b;

        };
        union
        {
            __IO    uint8_t     CSR0H;
            __IO    uint8_t     TXCSRH;
            struct
            {
                __IO   uint8_t flush_fifo              : 1;    /* The CPU writes a 1 to this bit to flush the next packet to be transmitted/read from
                                                         * the Endpoint 0 FIFO. The FIFO pointer is reset and the TxPktRdy/RxPktRdy bit(below) is
                                                         * cleared. Note:FlushFIFO should only be used when TxPktRdy/RxPktRdy is set.At other
                                                         * times, it may cause data to be corrupted.
                                                         */
                __IO   uint8_t reserved1_7             : 7;    /* Unused. Return 0 when resd. */
            } CSR0H_DEV_b;
            struct
            {
                __IO   uint8_t flush_fifo              : 1;    /* The CPU writes a 1 to this bit to flush the next packet to be transmitted/read from
                                                         * the Endpoint 0 FIFO. The FIFO pointer is reset and the TxPktRdy/RxPktRdy bit(below) is
                                                         * cleared. Note:FlushFIFO should only be used when TxPktRdy/RxPktRdy is set.At other
                                                         * times, it may cause data to be corrupted.
                                                         */
                __IO   uint8_t data_toggle             : 1;    /* When read,this bit indicates the current state of the Endpoint 0 data toggle. If D10
                                                         * is high,this bit may be written with the written with the required setting of the data
                                                         * toggle.If D10 is low,any value written to this bit is ignored.
                                                         */
                __IO   uint8_t data_toggle_wr_en       : 1;    /* The CPU written a 1 to this bit to enable the current state of Endpoint 0 data toggle
                                                         * to be written(see Data Toggle bit,below).This bit is automatically cleared once the new
                                                         * value is written.
                                                         */
                __IO   uint8_t dis_ping                : 1;    /* The CPU writes a 1 to this bit to instruct the core not to issue PING tokens in data
                                                         * and status phases of a high-speed Control transfer(for use with devices that do not
                                                         * respond to PING).
                                                         */
                __IO   uint8_t reserved1_7             : 4;    /* Unused. Return 0 when resd. */
            } CSR0H_HOST_b;
            struct
            {
                __IO   uint8_t reserved0_1                 : 2;
                __IO   uint8_t dma_req_mode                : 1;
                __IO   uint8_t frc_data_tog                : 1;
                __IO   uint8_t dma_req_enab                : 1;
                __IO   uint8_t mode                        : 1;
                __IO   uint8_t iso                         : 1;
                __IO   uint8_t auto_set                    : 1;
            } TXCSRH_DEV_b;
            struct
            {
                __IO   uint8_t data_toggle                 : 1;
                __IO   uint8_t data_toggle_wren            : 1;
                __IO   uint8_t dma_req_mode                : 1;
                __IO   uint8_t frc_data_tog                : 1;
                __IO   uint8_t dma_req_enab                : 1;
                __IO   uint8_t mode                        : 1;
                __IO   uint8_t reserved6                   : 1;
                __IO   uint8_t auto_set                    : 1;
            } TXCSRH_HOST_b;
        };
        union
        {
            __IO    uint16_t    RXMAXP;
            struct
            {
                __IO   uint16_t max_payload_tran               : 11;
                __IO   uint16_t ex_max                         : 5;
            } RXMAXP_b;
        };
        union
        {
            __IO    uint8_t     RXCSRL;
            struct
            {
                __IO   uint8_t rx_pkt_rdy                  : 1;    /* This bit is set when a data packet has been received */
                __IO   uint8_t fifo_full                   : 1;    /* */
                __IO   uint8_t over_run                    : 1;    /* */
                __IO   uint8_t data_error                  : 1;    /* */
                __IO   uint8_t flush_fifo                  : 1;
                __IO   uint8_t send_stall                  : 1;    /* The CPU writes a 1 to this bit to issue a STALL handshake. */
                __IO   uint8_t sent_stall                  : 1;    /* This bit is set when a STALL handshake is transmitted. The CPU should clear this bit.  */
                __IO   uint8_t clr_data_tog                : 1;
            } RXCSRL_DEV_b;
            struct
            {
                __IO   uint8_t rx_pkt_rdy                  : 1;    /* This bit is set when a data packet has been received */
                __IO   uint8_t fifo_full                   : 1;    /* */
                __IO   uint8_t error                       : 1;    /* */
                __IO   uint8_t data_error                  : 1;    /* */
                __IO   uint8_t flush_fifo                  : 1;
                __IO   uint8_t ReqPkt                      : 1;
                __IO   uint8_t RxStall                     : 1;
                __IO   uint8_t clr_data_tog                : 1;
            } RXCSRL_HOST_b;
        };
        union
        {
            __IO    uint8_t     RXCSRH;
            struct
            {
                __IO   uint8_t incomp_rx               : 1;
                __IO   uint8_t reserved1_2             : 2;
                __IO   uint8_t dma_req_mode            : 1;
                __IO   uint8_t dis_nyet_pid_error      : 1;
                __IO   uint8_t dma_req_enab            : 1;
                __IO   uint8_t iso                     : 1;
                __IO   uint8_t auto_clear              : 1;
            } RXCSRH_DEV_b;
            struct
            {
                __IO   uint8_t incomp_rx               : 1;
                __IO   uint8_t data_toggle             : 1;
                __IO   uint8_t data_toggle_wren        : 1;
                __IO   uint8_t dma_req_mode            : 1;
                __IO   uint8_t PID_error               : 1;
                __IO   uint8_t dma_req_enab            : 1;
                __IO   uint8_t auto_req                : 1;
                __IO   uint8_t auto_clear              : 1;
            } RXCSRH_HOST_b;
        };

        union
        {
            __IO     uint16_t    RXCOUNT;
            struct
            {
                __IO     uint16_t ep_rx_count            : 14;
                __IO     uint16_t reserved14_15          : 2;
            } RXCOUNT_b;
        };
        union
        {
            __IO    uint8_t     TYPE0;      // Host Mode Only.
            __IO    uint8_t     TXTYPE;     // Host Mode Only.
            struct
            {
                __IO    uint8_t reserved0_5             : 6;    /* Reserved */
                __IO    uint8_t speed                   : 2;    /* Operating speed of the target device :
                                                         *      00:Unused(Note: If selected,the target will be using the same connectionn speed as the core.)
                                                         *      01:High
                                                         *      10:Full
                                                         *      11:Low
                                                         */
            } TYPE0_b;
            struct
            {
                __IO    uint8_t target_EP_number        : 4;    /* Operating speed of the target device when the core is configured with the
                                                         * multipoint option:
                                                         *      00: Unused                  01: High
                                                         *      10: Full                    11: Low
                                                         * When the core is not configured with the multipoint option these bits should
                                                         * not be accessed.
                                                         */
                __IO    uint8_t protocol                : 2;    /* The CPU should set this to select the required protocol for TX endpoint:
                                                         *       00: Control       01: Isochronous
                                                         *       10: Bulk          11: Interrupt
                                                         */
                __IO    uint8_t speed                   : 2;    /* Operating speed of the target device when the core is configured with
                                                         * the multipoint option:
                                                         *      00:Unused        01: High      10: Full      11:Low
                                                         * when the core is not configured with the multipoint option these bits
                                                         * should not be accessed.
                                                         */
            } TXTYPE_b;
        };
        union
        {
            __IO    uint8_t     NAKLIMIT0;  // Host Mode Only.
            __IO    uint8_t     TXINTERVAL; // Host Mode Only.
            struct
            {
                __IO    uint8_t Endpoint0_NAK_Limit         : 5;    /* Endpoint 0 NAK limit (m) */
                __IO    uint8_t reserved5_7                 : 3;    /* Reserve */
            } NAKLIMIT0_b;
            struct
            {
                __IO    uint8_t Tx_polling_interval      :8;
            } TXINTERVAL_b;
        };
        union
        {
            __IO    uint8_t     RXTYPE;         // Host Mode Only.
            struct
            {
                __IO    uint8_t target_EP_number        : 4;    /* Operating speed of the target device when the core is configured with the
                                                         * multipoint option:
                                                         *      00: Unused                  01: High
                                                         *      10: Full                    11: Low
                                                         * When the core is not configured with the multipoint option these bits should
                                                         * not be accessed.
                                                         */
                __IO    uint8_t protocol                : 2;    /* The CPU should set this to select the required protocol for TX endpoint:
                                                         *       00: Control       01: Isochronous
                                                         *       10: Bulk          11: Interrupt
                                                         */
                __IO    uint8_t speed                   : 2;    /* Operating speed of the target device when the core is configured with
                                                         * the multipoint option:
                                                         *      00:Unused        01: High      10: Full      11:Low
                                                         * when the core is not configured with the multipoint option these bits
                                                         * should not be accessed.
                                                         */
            } RXTYPE_b;
        };
        union
        {
            __IO    uint8_t     RXINTERVAL;     // Host Mode Only.
            struct
            {
                __IO    uint8_t Tx_polling_interval      :8;
            } RXINTERVAL_b;
        };

                uint8_t     UNUSED0;
        union
        {
            __IO     uint8_t     CONFIGDATA;
            __IO     uint8_t     FIFOSIZE;
            struct
            {
                __IO     uint8_t utmi_data_width             : 1;    /* Indicates selected UTMI+ data width. Always 0 indicating 8 bits. */
                __IO     uint8_t soft_cone                   : 1;    /* Always "1" . Indicates Soft Connect/Disconnect.  */
                __IO     uint8_t dyn_fifo_sizing             : 1;    /* When set to "1" indicates Dynamic FIFO Sizing option selected.  */
                __IO     uint8_t hb_txe                      : 1;    /* When set to "1" indicates High-bandwidth TX ISO Endpoint Support selected */
                __IO     uint8_t hb_rxe                      : 1;    /* When set to "1" indicates High-bandwidth Rx ISO Endpoint Support selected.  */
                __IO     uint8_t big_endian                  : 1;    /* Always "0". Indicates Little Endian ordering.  */
                __IO     uint8_t mp_txe                      : 1;    /* When set to "1" automatic splitting of bulk packets is selected */
                __IO     uint8_t mp_rxe                      : 1;    /* When set to "1" automatic amalgamation of bulk packets is selected  */
            } CONFIGDATA_b;
            struct
            {
                __IO     uint8_t tx_fifo_size            : 4;
                __IO     uint8_t rx_fifo_size            : 4;
            } b;
        };
    } CSR[16];
    // Optional DMA Registers. 0x200 - 0x2FF.
    __IO    uint32_t    DMA_INTR;       /* Only one DMA INTR register */
    __IO    uint32_t    DMA_CNTL;
    __IO    uint32_t    DMA_ADDR;
    __IO    uint32_t    DMA_COUNT;
            uint32_t    UNUSED2[60];
    // Extended Registers. 0x300 - 0x35F.
    __IO    uint16_t    RQPKTCOUNT[16]; // Host Mode Only.
            uint16_t    UNUSEDRQPK[16];
    union
    {
        __IO    uint16_t    RXDPKTBUFDIS;   // Rx DPktBufDis.
        struct
        {
            __IO    uint16_t reserved0                  : 1;
            __IO    uint16_t ep1_rx_dis                 : 1;
            __IO    uint16_t ep2_rx_dis                 : 1;
            __IO    uint16_t ep3_rx_dis                 : 1;
            __IO    uint16_t ep4_rx_dis                 : 1;
            __IO    uint16_t ep5_rx_dis                 : 1;
            __IO    uint16_t ep6_rx_dis                 : 1;
            __IO    uint16_t ep7_rx_dis                 : 1;
            __IO    uint16_t ep8_rx_dis                 : 1;
            __IO    uint16_t ep9_rx_dis                 : 1;
            __IO    uint16_t ep10_rx_dis                : 1;
            __IO    uint16_t ep11_rx_dis                : 1;
            __IO    uint16_t ep12_rx_dis                : 1;
            __IO    uint16_t ep13_rx_dis                : 1;
            __IO    uint16_t ep14_rx_dis                : 1;
            __IO    uint16_t ep15_rx_dis                : 1;
        } RXDPKTBUFDIS_b;
    };
    union
    {
        __IO    uint16_t    TXDPKTBUFDIS;   // Tx DPktBufDis.
        struct
        {
            __IO    uint16_t reserved0                  : 1;
            __IO    uint16_t ep1_tx_dis                 : 1;
            __IO    uint16_t ep2_tx_dis                 : 1;
            __IO    uint16_t ep3_tx_dis                 : 1;
            __IO    uint16_t ep4_tx_dis                 : 1;
            __IO    uint16_t ep5_tx_dis                 : 1;
            __IO    uint16_t ep6_tx_dis                 : 1;
            __IO    uint16_t ep7_tx_dis                 : 1;
            __IO    uint16_t ep8_tx_dis                 : 1;
            __IO    uint16_t ep9_tx_dis                 : 1;
            __IO    uint16_t ep10_tx_dis                : 1;
            __IO    uint16_t ep11_tx_dis                : 1;
            __IO    uint16_t ep12_tx_dis                : 1;
            __IO    uint16_t ep13_tx_dis                : 1;
            __IO    uint16_t ep14_tx_dis                : 1;
            __IO    uint16_t ep15_tx_dis                : 1;
        } TXDPKTBUFDIS_b;
    };

    __IO    uint16_t    C_T_UCH;
    __IO    uint16_t    C_T_HSRTN;
    __IO    uint16_t    C_T_HSBT;
            uint16_t    UNUSED3[11];
    // LPM Registers. 0x360 - 0x365.
    union
    {
        __IO     uint16_t    LPM_ATTR;
        struct
        {
            __IO     uint16_t link_state          : 4;   /* This value is provoided by the host to the peripheral to indicate what state the peripheral
                                                 * must transition to after the receipt and acceptance of a LPM transaction.
                                                 * LinkState = 4'h0 - Reserved
                                                 * LinkState = 4'h1 - Slep State(L1)
                                                 * LinkState = 4'h2 - Reserved
                                                 * LinkState = 4'h3 - Reserved
                                                 */
            __IO     uint16_t HIRD                : 4;   /* This is the Host Initiated Resume Duration.This value is the minimum time the host will
                                                 * drive resume on the Bus. The value in this register corresponds to an actual resume time
                                                 * of:
                                                 * Resume Time = 50us + HIRD * 75us.This results a range 50us to 1200us.
                                                 */
            __IO     uint16_t RmtWak              : 1;   /* This bit is the remote wakeup enable bit:
                                                 * RmtWak = 1'b0:Remote wakeup is not enabled.
                                                 * RmtWak = 1'b1:Remote wakeup is enabled.
                                                 * This bit is applied on a temporary basis only and is only applied to the current suspend
                                                 * state.After the current suspend cycle,the remote wakeup capability that was negotiated
                                                 * upon enumeration will apply.
                                                 */
            __IO     uint16_t reserved9_11        : 3;   /* Reserved;Always returns 0 on read */
            __IO     uint16_t EndPoint            : 4;   /* This is the EndPnt that in the Token Packet of the LPM transaction. -*/
        } LPM_ATTR_b;
    };
    union
    {
        __IO    uint8_t     LPM_CNTRL;
        struct
        {
            __IO    uint8_t lpmxmt              : 1;
            __IO    uint8_t lpmres              : 1;
            __IO    uint8_t lpmen               : 2;
            __IO    uint8_t lpmnak              : 1;
            __IO    uint8_t reserved5_7         : 3;
        } LPM_CNTRL_DEV_b;
        struct
        {
            __IO    uint8_t lpmxmt              : 1;
            __IO    uint8_t lpmres              : 1;
            __IO    uint8_t reserved2_7         : 6;
        } LPM_CNTRL_HOST_b;
    };
    union
    {
        __IO    uint8_t     LPM_INTREN;
        struct
        {
            __IO    uint8_t lpmxmt              : 1;
            __IO    uint8_t lpmres              : 1;
            __IO    uint8_t reserved2_7         : 6;
        } LPM_INTREN_b;
    };
    union
    {
        __IO     uint8_t     LPM_INTR;
        struct
        {
            __IO     uint8_t lpmst               : 1;
            __IO     uint8_t lpmny               : 1;
            __IO     uint8_t lpmack              : 1;
            __IO     uint8_t lpmnc               : 1;
            __IO     uint8_t lpmres              : 1;
            __IO     uint8_t lpmerr              : 1;
            __IO     uint8_t reserved6_7         : 2;
        } LPM_INTR_DEV_b;
        struct
        {
            __IO     uint8_t lpmst               : 1;
            __IO     uint8_t lpmny               : 1;
            __IO     uint8_t lpmack              : 1;
            __IO     uint8_t lpmnc               : 1;
            __IO     uint8_t lpmres              : 1;
            __IO     uint8_t reserved5_7         : 3;
        } LPM_INTR_HOST_b;
    };
    union
    {
        __IO    uint8_t     LPM_FADDR;      // Relavant in Host mode only.
        struct
        {
            __IO    uint8_t function_address    : 7;
            __IO    uint8_t reserved7           : 1;
        } LPM_FADDR_b;
    };

}USB_TypeDef;

#define USB_OTG ( (USB_TypeDef *) USB_BASE )
typedef struct
{
    const USB_TypeDef *RegBase;
    const int IrqLine;
    USB_EndpointCtrlStruct EpCtrl[USB_EP_MAX];
    uint32_t RxData[USB_FIFO_DW_DAX];
    PV_Union pRxData;
    uint8_t IsConnect;
    uint8_t IsHost;
    uint8_t NewDeviceAddress;
}USB_HWCtrlStruct;

static USB_HWCtrlStruct prvUSB =
{
        .RegBase = USB_BASE,
        .IrqLine = USB_IRQn,
};

static uint8_t USB_OTG_FifosizeReg(uint16_t fifosiz)
{
    uint8_t register_value = 0;
    switch (fifosiz)
    {
    case 8:
        register_value = 0;
        break;
    case 16:
        register_value = 1;
        break;
    case 32:
        register_value = 2;
        break;
    case 64:
        register_value = 3;
        break;
    case 128:
        register_value = 4;
        break;
    }
    return register_value;
}

static void prvUSB_IrqHandle(int32_t IrqLine, void *pData)
{
    uint32_t USB_ID = (uint32_t)pData;
    uint32_t i;
    uint32_t Count32b;
    uint16_t RxLen;
    uint16_t TxBit = USB_OTG->INTRTX;
    uint16_t RxBit = USB_OTG->INTRRX;
    uint8_t StateBit = USB_OTG->INTRUSB;
    uint8_t EpIndex = 1;
    USB_OTG->INTRUSB = 0;
    USB_OTG->INTRRX = 0;
    USB_OTG->INTRTX = 0;
    if (prvUSB.IsHost || USB_OTG->DEVCTL_b.host_mode)
    {
        ;
    }
    else
    {

        if (StateBit & 0x1)
        {
            USB_StackDeviceBusChange(USB_ID, USBD_BUS_TYPE_SUSPEND);
        }
        if (StateBit & 0x2)
        {
            USB_StackDeviceBusChange(USB_ID, USBD_BUS_TYPE_RESUME);
            USB_OTG->POWER_b.resume = 1;
        }
        if (StateBit & 0x4)
        {
            USB_OTG->FADDR = 0;
            USB_OTG->INDEX = 0;
            USB_FlushFifo(&prvUSB, 0, 0);
            for(i = 1; i < 8; i++)
            {
                USB_FlushFifo(&prvUSB,i, 0);
                USB_FlushFifo(&prvUSB,i, 1);
            }
            USB_SetDeviceEPStatus(&prvUSB, 0, 0, USB_EP_STATE_ACK);
            USB_StackDeviceBusChange(USB_ID, USBD_BUS_TYPE_RESET);
        }
        if (StateBit & 0x8)
        {
            USB_StackDeviceBusChange(USB_ID, USBD_BUS_TYPE_NEW_SOF);
        }
        if (StateBit & 0x20)
        {
            for(i = 0; i < 8; i++)
            {
                memset(&prvUSB.EpCtrl[i].TxBuf, 0, sizeof(Buffer_Struct));
            }
            USB_StackDeviceBusChange(USB_ID, USBD_BUS_TYPE_DISCONNECT);
        }
        if (TxBit & 0x01)
        {
            if (USB_OTG->CSR0L_DEV_b.sent_stall)
            {
                USB_SetDeviceEPStatus(&prvUSB, 0, 0, USB_EP_STATE_ACK);
            }
            if (USB_OTG->CSR0L_DEV_b.setup_end)
            {
                USB_OTG->CSR0L_DEV_b.serviced_setupend = 1;
            }
            if (prvUSB.NewDeviceAddress & 0x80)
            {
                USB_OTG->FADDR = prvUSB.NewDeviceAddress & 0x7f;
                prvUSB.NewDeviceAddress = 0;
            }
            if (USB_OTG->CSR0L_DEV_b.rx_pkt_rdy)
            {
                RxLen = USB_OTG->COUNT0_b.ep0_rx_count;
                if (RxLen)
                {
                    Count32b = RxLen >> 2;
                    for (i = 0; i < Count32b; i++)
                    {
                        prvUSB.RxData[i] = USB_OTG->FIFOX[0].dword;
                    }
                    for (i = Count32b * 4; i < RxLen; i++)
                    {
                        prvUSB.pRxData.pu8[i] = USB_OTG->FIFOX[0].byte;
                    }
                    USB_StackPutRxData(USB_ID, 0, prvUSB.pRxData.pu8, RxLen);
                }
                USB_OTG->CSR0L_DEV_b.serviced_rxpktrdy = 1;
                USB_StackAnalyzeDeviceEpRx(USB_ID, 0);
            }
            else if (!USB_OTG->CSR0L_DEV_b.tx_pkt_rdy)
            {
                USB_DeviceXfer(&prvUSB, 0);
            }

        }
        else if (TxBit)
        {
            TxBit >>= 1;
            EpIndex = 1;
            while(TxBit)
            {
                if (TxBit & 0x01)
                {
                    if (!USB_OTG->CSR[EpIndex].TXCSRL_DEV_b.tx_pkt_rdy)
                    {
                        USB_DeviceXfer(&prvUSB, EpIndex);
                    }
                    USB_OTG->CSR[EpIndex].TXCSRL_DEV_b.sent_stall = prvUSB.EpCtrl[EpIndex].INSTATUS_b.Halt?1:0;
                    USB_OTG->CSR[EpIndex].TXCSRL_DEV_b.send_stall = 0;
                    USB_OTG->CSR[EpIndex].TXCSRL_DEV_b.under_run = 0;
                }
                TxBit >>= 1;
                EpIndex++;
            }
        }
        if (RxBit)
        {
            EpIndex = 1;
            RxBit >>= 1;
            while(RxBit)
            {
                if (RxBit & 0x01)
                {
                    if (USB_OTG->CSR[EpIndex].RXCSRL_DEV_b.rx_pkt_rdy)
                    {
                        RxLen = USB_OTG->CSR[EpIndex].RXCOUNT_b.ep_rx_count;
                        if (RxLen)
                        {
                            Count32b = RxLen >> 2;
                            for (i = 0; i < Count32b; i++)
                            {
                                prvUSB.RxData[i] = USB_OTG->FIFOX[EpIndex].dword;
                            }
                            for (i = Count32b * 4; i < RxLen; i++)
                            {
                                prvUSB.pRxData.pu8[i] = USB_OTG->FIFOX[EpIndex].byte;
                            }
                            USB_StackPutRxData(USB_ID, EpIndex, prvUSB.pRxData.pu8, RxLen);
                        }
                    }
                    USB_OTG->CSR[EpIndex].RXCSRL = 0;
                    USB_OTG->CSR[EpIndex].RXCSRL_DEV_b.sent_stall = prvUSB.EpCtrl[EpIndex].OUTSTATUS_b.Halt?1:0;
                    USB_StackAnalyzeDeviceEpRx(USB_ID, EpIndex);
                }
                RxBit >>= 1;
                EpIndex++;
            }

        }
    }
}

static int prvUSB_SetupEPFifo(HANDLE hUSB)
{
    USB_HWCtrlStruct *hwUSB = (USB_HWCtrlStruct *)hUSB;
    uint8_t i;
    uint8_t Len;
    uint16_t FifoStart = (64 >> 3);
    uint16_t UseFifo = 64;
    //ep0使用默认的64byte

    USB_OTG->INDEX = 0;
    USB_OTG->TXFIFOSZ = 3;
    USB_OTG->RXFIFOSZ = 3;
    USB_OTG->TXFIFOADD = 0;
    USB_OTG->RXFIFOADD = 0;
    USB_OTG->CSR0H_DEV_b.flush_fifo = 1;    //刷新EP0的FIFO
    hwUSB->EpCtrl[0].MaxPacketLen = 64;
    for(i = 1; i < USB_EP_MAX; i++)
    {
        USB_OTG->INDEX = i;
        if (hwUSB->EpCtrl[i].ToDeviceEnable)
        {
            Len = USB_OTG_FifosizeReg(hwUSB->EpCtrl[i].MaxPacketLen);
            USB_OTG->CSR[i].RXMAXP = hwUSB->EpCtrl[i].MaxPacketLen;
            USB_OTG->RXFIFOADD = FifoStart;
            USB_OTG->RXFIFOSZ = Len;
            USB_OTG->CSR[i].RXCSRL = (1 << 4);
            //DBG("%d,%d,%x,%d,%x", i, USB_OTG->CSR[i].RXMAXP, USB_OTG->RXFIFOADD, USB_OTG->RXFIFOSZ, USB_OTG->CSR[i].RXCSRL);
            FifoStart += (hwUSB->EpCtrl[i].MaxPacketLen >> 3);
            UseFifo += hwUSB->EpCtrl[i].MaxPacketLen;
        }
        if (UseFifo > 512)
        {
            return -1;
        }
        if (hwUSB->EpCtrl[i].ToHostEnable)
        {
            USB_OTG->CSR[i].TXMAXP = hwUSB->EpCtrl[i].MaxPacketLen;
            USB_OTG->TXFIFOADD = FifoStart;
            USB_OTG->TXFIFOSZ = Len;
            USB_OTG->CSR[i].TXCSRL = (1 << 3);
            //DBG("%d,%d,%x,%d,%x", i, USB_OTG->CSR[i].TXMAXP, USB_OTG->TXFIFOADD, USB_OTG->TXFIFOSZ, USB_OTG->CSR[i].TXCSRL);
            FifoStart += (hwUSB->EpCtrl[i].MaxPacketLen >> 3);
            UseFifo += hwUSB->EpCtrl[i].MaxPacketLen;
        }
        if (UseFifo > 512)
        {
            return -1;
        }
    }
    USB_OTG->INDEX = 0;
    return 0;
}

void USB_GlobalInit(void)
{
    USB_HWCapsStruct Caps;


    ISR_SetHandler(prvUSB.IrqLine, prvUSB_IrqHandle, USB_ID0);
#ifdef __BUILD_OS__
    ISR_SetPriority(prvUSB.IrqLine, configLIBRARY_LOWEST_INTERRUPT_PRIORITY);
#else
    ISR_SetPriority(prvUSB.IrqLine, 7);
#endif
    prvUSB.IsConnect = 0;
    Caps.EpBufMaxLen = 4096;
    Caps.Feature = 0;
    Caps.FEATURE_b.FullSpeed = 1;
    Caps.CtrlMode = USB_MODE_DUAL;
    USB_StackSetControl(USB_ID0, &prvUSB, prvUSB.EpCtrl, &Caps);
    USB_StackSetDeviceSpeed(USB_ID0, USB_DEVICE_SPEED_FULL_SPEED);
    USB_OTG->INTRRXE = 0;
    USB_OTG->INTRTXE = 0;
    USB_OTG->INTRUSBE = 0;
    prvUSB.pRxData.pu32 = prvUSB.RxData;
    SYSCTRL->CG_CTRL2 &= ~SYSCTRL_AHBPeriph_USB;

}

void USB_PowerOnOff(HANDLE hUSB, uint8_t OnOff)
{
    if (OnOff)
    {
        SYSCTRL->CG_CTRL2 |= SYSCTRL_AHBPeriph_USB;
    }
    else
    {
        SYSCTRL->CG_CTRL2 &= ~SYSCTRL_AHBPeriph_USB;
    }
}

void USB_Stop(HANDLE hUSB)
{
    uint8_t dummy;
    USB_HWCtrlStruct *hwUSB = (USB_HWCtrlStruct *)hUSB;
    ISR_OnOff(hwUSB->IrqLine, 0);
    USB_OTG->POWER = 0;
    USB_OTG->INTRRXE = 0;
    USB_OTG->INTRTXE = 0;
    USB_OTG->INTRUSBE = 0;
    USB_OTG->INTRTX = 0;
    USB_OTG->INTRRX = 0;
    USB_OTG->INTRUSB = 0;
    dummy = USB_OTG->INTRUSB;
}

void USB_ResetStart(HANDLE hUSB)
{
    SYSCTRL->LOCK_R &= ~SYSCTRL_USB_RESET;
    SYSCTRL->SOFT_RST2 |= SYSCTRL_USB_RESET;
    SYSCTRL->LOCK_R |= SYSCTRL_USB_RESET;
}

void USB_ResetEnd(HANDLE hUSB)
{
    SYSCTRL->LOCK_R &= ~SYSCTRL_USB_RESET;
    SYSCTRL->SOFT_RST2 &= ~SYSCTRL_USB_RESET;
    SYSCTRL->LOCK_R |= SYSCTRL_USB_RESET;
}

void USB_SetWorkMode(HANDLE hUSB, uint8_t Mode)
{
    USB_HWCtrlStruct *hwUSB = (USB_HWCtrlStruct *)hUSB;
    USBPHY_CR1_TypeDef CR1;
    USBPHY_CR3_TypeDef CR3;
    CR1.d32 = SYSCTRL->USBPHY_CR1;
    CR1.b.commononn = 0;
    CR1.b.stop_ck_for_suspend = 0;
    SYSCTRL->USBPHY_CR1 = CR1.d32;

    switch (Mode)
    {
    case USB_MODE_HOST:
        USB_OTG->POWER = 1;
        USB_OTG->DEVCTL |= (1 << 0)|(1 << 2);
        CR3.d32 = SYSCTRL->USBPHY_CR3;
        CR3.b.idpullup = 1;
        SYSCTRL->USBPHY_CR3 = CR3.d32;
        hwUSB->IsHost = 1;
        break;
    default:
        USB_OTG->DEVCTL &= ~((1 << 0)|(1 << 2));
        USB_OTG->POWER = 1|(1 << 6);
        CR3.d32 = SYSCTRL->USBPHY_CR3;
        CR3.b.idpullup = 0;
        SYSCTRL->USBPHY_CR3 = CR3.d32;
        hwUSB->IsHost = 0;
        break;
    }
}

void USB_SetDeviceAddress(HANDLE hUSB, uint8_t Address)
{
    prvUSB.NewDeviceAddress = 0x80 | Address;
}

int USB_ReInitEpCfg(HANDLE hUSB)
{
    return -1;
}

int USB_InitEpCfg(HANDLE hUSB)
{
    return prvUSB_SetupEPFifo(hUSB);
}


void USB_Start(HANDLE hUSB)
{
    USB_HWCtrlStruct *hwUSB = (USB_HWCtrlStruct *)hUSB;
    USB_OTG->INTRUSBE = 0xff;
    USB_OTG->INTRUSBE_b.en_sof = 0;
    USB_OTG->INTRTXE = 0xff;
    USB_OTG->INTRRXE = 0xfe;
    ISR_OnOff(hwUSB->IrqLine, 1);
}

void USB_SendZeroPacket(HANDLE hUSB, uint8_t EpIndex)
{
    if (EpIndex)
    {
        USB_OTG->CSR[EpIndex].TXCSRL_DEV_b.tx_pkt_rdy = 1;
    }
    else
    {
        USB_OTG->CSR0L_DEV_b.tx_pkt_rdy = 1;
    }
}

void USB_DeviceXferStop(HANDLE hUSB, uint8_t EpIndex)
{
    USB_HWCtrlStruct *hwUSB = (USB_HWCtrlStruct *)hUSB;
    USB_OTG->INTRTXE &= ~(1 << EpIndex);
    USB_FlushFifo(hUSB, EpIndex, 0);
    USB_OTG->CSR[EpIndex].TXCSRL_DEV_b.send_stall = 0;
    USB_OTG->CSR[EpIndex].TXCSRL_DEV_b.sent_stall = 0;
    USB_OTG->CSR[EpIndex].TXCSRL_DEV_b.under_run = 0;
    USB_OTG->INTRTXE |= (1 << EpIndex);
}

void USB_EpIntOnOff(HANDLE hUSB, uint8_t EpIndex, uint8_t IsToDevice, uint8_t OnOff)
{
    USB_HWCtrlStruct *hwUSB = (USB_HWCtrlStruct *)hUSB;
    if (IsToDevice)
    {
        if (OnOff)
        {
            USB_OTG->INTRRXE |= (1 << EpIndex);
        }
        else
        {
            USB_OTG->INTRRXE &= ~(1 << EpIndex);
        }
    }
    else
    {
        if (OnOff)
        {
            USB_OTG->INTRTXE |= (1 << EpIndex);
        }
        else
        {
            USB_OTG->INTRTXE &= ~(1 << EpIndex);
        }
    }
}

void USB_DeviceXfer(HANDLE hUSB, uint8_t EpIndex)
{
    USB_HWCtrlStruct *hwUSB = (USB_HWCtrlStruct *)hUSB;
    USB_EndpointCtrlStruct *pEpCtrl = &hwUSB->EpCtrl[EpIndex];
    USB_EndpointDataStruct EpData;
    uint16_t TxLen, i;
    EpData.USB_ID = USB_ID0;
    EpData.EpIndex = EpIndex;
    EpData.IsToDevice = 0;
    if (pEpCtrl->TxBuf.Data)
    {
        if (pEpCtrl->TxBuf.Pos >= pEpCtrl->TxBuf.MaxLen)
        {
            if (pEpCtrl->NeedZeroPacket)
            {
//              DBG("Ep%d %d %d %d need send 0 packet", EpIndex,
//                      pEpCtrl->ForceZeroPacket, pEpCtrl->TxBuf.Pos, pEpCtrl->XferMaxLen);
                if (!pEpCtrl->TxZeroPacket)
                {
                    pEpCtrl->TxZeroPacket = 1;
                    if (EpIndex)
                    {
                        USB_OTG->CSR[EpIndex].TXCSRL_DEV_b.tx_pkt_rdy = 1;
                    }
                    else
                    {
                        USB_OTG->CSR0L_DEV_b.tx_pkt_rdy = 1;
                    }
                }
                else
                {
                    DBG("!");
                }

            }
            goto XFER_DONE;
        }
        else
        {
            pEpCtrl->TxZeroPacket = 0;
            if ((pEpCtrl->TxBuf.MaxLen - pEpCtrl->TxBuf.Pos) > pEpCtrl->MaxPacketLen)
            {
                TxLen = pEpCtrl->MaxPacketLen;
            }
            else
            {
                if (pEpCtrl->ForceZeroPacket)
                {
                    pEpCtrl->NeedZeroPacket = 1;
                }
                if ((pEpCtrl->TxBuf.MaxLen - pEpCtrl->TxBuf.Pos) == pEpCtrl->MaxPacketLen)
                {
                    if ( pEpCtrl->TxBuf.MaxLen < pEpCtrl->XferMaxLen )
                    {
                        pEpCtrl->NeedZeroPacket = 1;
                    }
                }
                TxLen = pEpCtrl->TxBuf.MaxLen - pEpCtrl->TxBuf.Pos;
            }


            for(i = pEpCtrl->TxBuf.Pos; i < pEpCtrl->TxBuf.Pos + TxLen; i++)
            {
                USB_OTG->FIFOX[EpIndex].byte = pEpCtrl->TxBuf.Data[i];
            }
            pEpCtrl->TxBuf.Pos += TxLen;
            if (EpIndex)
            {
                USB_OTG->CSR[EpIndex].TXCSRL_DEV_b.tx_pkt_rdy = 1;
            }
            else
            {
                USB_OTG->CSR0L_DEV_b.tx_pkt_rdy = 1;
            }
        }
    }
    return;
XFER_DONE:
    memset(&pEpCtrl->TxBuf, 0, sizeof(Buffer_Struct));
    if (EpIndex)
    {
        pEpCtrl->CB(&EpData, pEpCtrl->pData);
    }
    else
    {
        USB_StackDeviceEp0TxDone(USB_ID0);
    }
}

void USB_SetDeviceNoDataSetup(HANDLE hUSB)
{
    {
        USB_OTG->CSR0L_DEV_b.data_end = 1;
    }
}

void USB_FlushFifo(HANDLE hUSB, uint8_t EpIndex, uint8_t IsToDevice)
{
    if (EpIndex)
    {
        if (IsToDevice)
        {
            USB_OTG->CSR[EpIndex].RXCSRL = (1 << 4);
        }
        else
        {

            USB_OTG->CSR[EpIndex].TXCSRL = (1 << 3);

        }

    }
    else
    {
        if (USB_OTG->CSR0L_DEV_b.rx_pkt_rdy || USB_OTG->CSR0L_DEV_b.tx_pkt_rdy)
        {
            USB_OTG->CSR0H_DEV_b.flush_fifo = 1;
            USB_OTG->CSR0L_DEV_b.serviced_rxpktrdy = 1;
            USB_OTG->CSR0L_DEV_b.tx_pkt_rdy        = 0;
        }
    }
}

/**
* @brief  returns the EP Status
* @param  pdev : Selected device
*         ep : endpoint structure
* @retval : EP status
*/

uint8_t USB_GetDeviceEPStatus(HANDLE hUSB, uint8_t Index, uint8_t IsToDevice)
{
    if (Index)
    {
        if (IsToDevice)
        {

            if (USB_OTG->CSR[Index].RXCSRL_DEV_b.sent_stall)
            {
                return USB_EP_STATE_STALL;
            }
            if (USB_OTG->CSR[Index].RXCSRL_DEV_b.data_error || USB_OTG->CSR[Index].RXCSRL_DEV_b.over_run)
            {
                return USB_EP_STATE_NAK;
            }
            return USB_EP_STATE_ACK;
        }
        else
        {
            if (USB_OTG->CSR[Index].TXCSRL_DEV_b.sent_stall)
            {
                return USB_EP_STATE_STALL;
            }
            if (USB_OTG->CSR[Index].TXCSRL_DEV_b.under_run || USB_OTG->CSR[Index].TXCSRL_DEV_b.tx_pkt_rdy)
            {
                return USB_EP_STATE_NAK;
            }
            return USB_EP_STATE_ACK;
        }
    }
    else
    {
        if (USB_OTG->CSR0L_DEV_b.sent_stall)
        {
            return USB_EP_STATE_STALL;
        }
        return USB_EP_STATE_ACK;
    }
}

/**
* @brief  Set the EP Status
* @param  pdev : Selected device
*         Status : new Status
*         ep : EP structure
* @retval : None
*/
void USB_SetDeviceEPStatus (HANDLE hUSB, uint8_t Index, uint8_t IsToDevice, uint8_t Status)
{
    if (Index)
    {
        if (IsToDevice)
        {
            switch(Status)
            {
            case USB_EP_STATE_DISABLE:
            case USB_EP_STATE_NAK:
            case USB_EP_STATE_NYET:
                break;
            case USB_EP_STATE_STALL:
                DBG("%d", Index);
                USB_OTG->CSR[Index].RXCSRL_DEV_b.send_stall = 1;
                break;
            case USB_EP_STATE_ENABLE:
            case USB_EP_STATE_ACK:
                USB_OTG->CSR[Index].RXCSRL_DEV_b.send_stall = 0;
                USB_OTG->CSR[Index].RXCSRL_DEV_b.sent_stall = 0;
                USB_OTG->CSR[Index].RXCSRL_DEV_b.over_run = 0;
                USB_OTG->CSR[Index].RXCSRL_DEV_b.data_error = 0;
                break;
            }
        }
        else
        {
            switch(Status)
            {
            case USB_EP_STATE_DISABLE:
            case USB_EP_STATE_NAK:
            case USB_EP_STATE_NYET:
                break;
            case USB_EP_STATE_STALL:
                DBG("%d", Index);
                USB_OTG->CSR[Index].TXCSRL_DEV_b.send_stall = 1;
                break;
            case USB_EP_STATE_ENABLE:
            case USB_EP_STATE_ACK:
                USB_OTG->CSR[Index].TXCSRL_DEV_b.send_stall = 0;
                USB_OTG->CSR[Index].TXCSRL_DEV_b.sent_stall = 0;
                USB_OTG->CSR[Index].TXCSRL_DEV_b.under_run = 0;
                break;
            }
        }
    }
    else
    {
        switch(Status)
        {
        case USB_EP_STATE_DISABLE:
        case USB_EP_STATE_NYET:
        case USB_EP_STATE_NAK:
            break;
        case USB_EP_STATE_STALL:
            USB_OTG->CSR0L_DEV_b.send_stall = 1;
            break;
        case USB_EP_STATE_ACK:
        case USB_EP_STATE_ENABLE:
            USB_OTG->CSR0L_DEV_b.send_stall = 0;
            USB_OTG->CSR0L_DEV_b.sent_stall = 0;
            break;
        }
    }
}

void USB_ResumeStart(HANDLE hUSB)
{
    USB_OTG->POWER_b.resume = 1;
}

void USB_ResumeEnd(HANDLE hUSB)
{
    USB_OTG->POWER_b.resume = 0;
}

int32_t USB_SetISOCHDelay(HANDLE hUSB, uint16_t DelayNS)
{
    return -1;
}

int32_t USB_ExitLatency(HANDLE hUSB, uint8_t Config[6])
{
    return -1;
}

#endif
