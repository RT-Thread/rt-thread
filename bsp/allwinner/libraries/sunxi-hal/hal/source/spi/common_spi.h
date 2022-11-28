/*
* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.
*
* Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
* the the People's Republic of China and other countries.
* All Allwinner Technology Co.,Ltd. trademarks are used with permission.
*
* DISCLAIMER
* THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
* IF YOU NEED TO INTEGRATE THIRD PARTY’S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
* IN ALLWINNERS’SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
* ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
* ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
* COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
* YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PARTY’S TECHNOLOGY.
*
*
* THIS SOFTWARE IS PROVIDED BY ALLWINNER"AS IS" AND TO THE MAXIMUM EXTENT
* PERMITTED BY LAW, ALLWINNER EXPRESSLY DISCLAIMS ALL WARRANTIES OF ANY KIND,
* WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING WITHOUT LIMITATION REGARDING
* THE TITLE, NON-INFRINGEMENT, ACCURACY, CONDITION, COMPLETENESS, PERFORMANCE
* OR MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* IN NO EVENT SHALL ALLWINNER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
* NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS, OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef __COMMON_SPI_I_H__
#define __COMMON_SPI_I_H__

#ifdef __cplusplus
extern "C" {
#endif

#define SUNXI_SPI_REG_SIZE    0x1000 /* controler reg sized */

#define HEXADECIMAL (0x10)
#define REG_INTERVAL (0x04)
#define REG_CL (0x0c)

#define SPI_FIFO_DEPTH (128)
#define MAX_FIFU 64
#define BULK_DATA_BOUNDARY 64       /* can modify to adapt the application */
#define SPI_MAX_FREQUENCY 100000000 /* spi controller just support 100Mhz */
#define SPI_HIGH_FREQUENCY 60000000 /* sample mode threshold frequency  */
#define SPI_LOW_FREQUENCY 24000000  /* sample mode threshold frequency  */
#define SPI_MOD_CLK 50000000    /* sample mode frequency  */

/* SPI Registers offsets from peripheral base address */
#define SPI_VER_REG (0x00)      /* version number register */
#define SPI_GC_REG (0x04)       /* global control register */
#define SPI_TC_REG (0x08)       /* transfer control register */
#define SPI_INT_CTL_REG (0x10)  /* interrupt control register */
#define SPI_INT_STA_REG (0x14)  /* interrupt status register */
#define SPI_FIFO_CTL_REG (0x18) /* fifo control register */
#define SPI_FIFO_STA_REG (0x1C) /* fifo status register */
#define SPI_WAIT_CNT_REG (0x20) /* wait clock counter register */
#define SPI_CLK_CTL_REG                                                        \
    (0x24) /* clock rate control register. better not to use it */
#define SPI_BURST_CNT_REG (0x30)    /* burst counter register */
#define SPI_TRANSMIT_CNT_REG (0x34) /* transmit counter register */
#define SPI_BCC_REG (0x38)    /* burst control counter register */
#define SPI_DMA_CTL_REG (0x88)      /* DMA control register, only for 1639 */
#define SPI_TXDATA_REG (0x200)      /* tx data register */
#define SPI_RXDATA_REG (0x300)      /* rx data register */

/* SPI Global Control Register Bit Fields & Masks,default value:0x0000_0080 */
#define SPI_GC_EN                                                              \
    (0x1                                                                   \
     << 0) /* SPI module enable control 1:enable; 0:disable; default:0 */
#define SPI_GC_MODE                                                            \
    (0x1 << 1) /* SPI function mode select 1:master; 0:slave; default:0 */
#define SPI_GC_TP_EN                                                           \
    (0x1 << 7) /* SPI transmit stop enable 1:stop transmit data when       \
RXFIFO is full; 0:ignore RXFIFO status; default:1 */
#define SPI_GC_SRST                                                            \
    (0x1 << 31) /* soft reset, write 1 will clear SPI control, auto     \
clear to 0 */
/* SPI Transfer Control Register Bit Fields & Masks,default value:0x0000_0087 */
#define SPI_TC_PHA                                                             \
    (0x1 << 0) /* SPI Clock/Data phase control,0: phase0,1:                \
phase1;default:1 */
#define SPI_TC_POL                                                             \
    (0x1 << 1) /* SPI Clock polarity control,0:low level idle,1:high    \
level idle;default:1 */
#define SPI_TC_SPOL                                                            \
    (0x1 << 2) /* SPI Chip select signal polarity control,default: 1,low   \
effective like this:~~|_____~~ */
#define SPI_TC_SSCTL                                                           \
    (0x1                                                                   \
     << 3) /* SPI chip select control,default 0:SPI_SSx remains asserted   \
between SPI bursts,1:negate SPI_SSx between SPI bursts */
#define SPI_TC_SS_MASK                                                         \
    (0x3 << 4) /* SPI chip                                                 \
select:00-SPI_SS0;01-SPI_SS1;10-SPI_SS2;11-SPI_SS3*/
#define SPI_TC_SS_OWNER                                                        \
    (0x1 << 6) /* SS output mode select default is 0:automatic output      \
SS;1:manual output SS */
#define SPI_TC_SS_LEVEL                                                        \
    (0x1 << 7) /* defautl is 1:set SS to high;0:set SS to low */
#define SPI_TC_DHB                                                             \
    (0x1                                                                   \
     << 8) /* Discard Hash Burst,default 0:receiving all spi burst in BC   \
period 1:discard unused,fectch WTC bursts */
#define SPI_TC_DDB                                                             \
    (0x1 << 9) /* Dummy burst Type,default 0: dummy spi burst is           \
zero;1:dummy spi burst is one */
#define SPI_TC_RPSM                                                            \
    (0x1 << 10) /* select mode for high speed write,0:normal write         \
mode,1:rapids write mode,default 0 */
#define SPI_TC_SDM                                                             \
    (0x1 << 13) /* master sample data mode, 1: normal sample            \
mode;0:delay sample mode. */
#define SPI_TC_SDC                                                             \
    (0x1 << 11) /* master sample data control, 1: delay--high speed        \
operation;0:no delay. */
#define SPI_TC_FBS                                                             \
    (0x1 << 12) /* LSB/MSB transfer first select 0:MSB,1:LSB,default    \
0:MSB first */
#define SPI_TC_XCH                                                             \
    (0x1                                                                   \
     << 31) /* Exchange burst default 0:idle,1:start exchange;when BC is   \
zero,this bit cleared by SPI controller*/
#define SPI_TC_SS_BIT_POS (4)

/* SPI Interrupt Control Register Bit Fields & Masks,default value:0x0000_0000
*/
#define SPI_INTEN_RX_RDY                                                       \
    (0x1 << 0) /* rxFIFO Ready Interrupt Enable,---used for immediately    \
received,0:disable;1:enable */
#define SPI_INTEN_RX_EMP                                                       \
    (0x1 << 1) /* rxFIFO Empty Interrupt Enable ---used for IRQ received   \
*/
#define SPI_INTEN_RX_FULL                                                      \
    (0x1 << 2) /* rxFIFO Full Interrupt Enable ---seldom used */
#define SPI_INTEN_TX_ERQ                                                       \
    (0x1 << 4) /* txFIFO Empty Request Interrupt Enable ---seldom used */
#define SPI_INTEN_TX_EMP                                                       \
    (0x1 << 5) /* txFIFO Empty Interrupt Enable ---used  for IRQ tx */
#define SPI_INTEN_TX_FULL                                                      \
    (0x1 << 6) /* txFIFO Full Interrupt Enable ---seldom used */
#define SPI_INTEN_RX_OVF                                                       \
    (0x1                                                                   \
     << 8) /* rxFIFO Overflow Interrupt Enable ---used for error detect */
#define SPI_INTEN_RX_UDR                                                       \
    (0x1                                                                   \
     << 9) /* rxFIFO Underrun Interrupt Enable ---used for error detect */
#define SPI_INTEN_TX_OVF                                                       \
    (0x1 << 10) /* txFIFO Overflow Interrupt Enable ---used for error      \
detect */
#define SPI_INTEN_TX_UDR                                                       \
    (0x1 << 11) /* txFIFO Underrun Interrupt Enable ---not happened */
#define SPI_INTEN_TC                                                           \
    (0x1 << 12) /* Transfer Completed Interrupt Enable  ---used */
#define SPI_INTEN_SSI                                                          \
    (0x1 << 13) /* SSI interrupt Enable,chip select from valid state to    \
invalid state,for slave used only */
#define SPI_INTEN_ERR                                                          \
    (SPI_INTEN_TX_OVF | SPI_INTEN_RX_UDR |                                 \
     SPI_INTEN_RX_OVF) /* NO txFIFO underrun */
#define SPI_INTEN_MASK (0x77 | (0x3f << 8))

/* SPI Interrupt Status Register Bit Fields & Masks,default value:0x0000_0022 */
#define SPI_INT_STA_RX_RDY                                                     \
    (0x1 << 0) /* rxFIFO ready, 0:RX_WL < RX_TRIG_LEVEL,1:RX_WL >=         \
RX_TRIG_LEVEL */
#define SPI_INT_STA_RX_EMP                                                     \
    (0x1 << 1) /* rxFIFO empty, this bit is set when rxFIFO is empty */
#define SPI_INT_STA_RX_FULL                                                    \
    (0x1 << 2) /* rxFIFO full, this bit is set when rxFIFO is full */
#define SPI_INT_STA_TX_RDY                                                     \
    (0x1 << 4) /* txFIFO ready, 0:TX_WL > TX_TRIG_LEVEL,1:TX_WL <=         \
TX_TRIG_LEVEL */
#define SPI_INT_STA_TX_EMP                                                     \
    (0x1 << 5) /* txFIFO empty, this bit is set when txFIFO is empty */
#define SPI_INT_STA_TX_FULL                                                    \
    (0x1 << 6) /* txFIFO full, this bit is set when txFIFO is full */
#define SPI_INT_STA_RX_OVF                                                     \
    (0x1 << 8) /* rxFIFO overflow, when set rxFIFO has overflowed */
#define SPI_INT_STA_RX_UDR                                                     \
    (0x1 << 9) /* rxFIFO underrun, when set rxFIFO has underrun */
#define SPI_INT_STA_TX_OVF                                                     \
    (0x1 << 10) /* txFIFO overflow, when set txFIFO has overflowed */
#define SPI_INT_STA_TX_UDR                                                     \
    (0x1 << 11) /* fxFIFO underrun, when set txFIFO has underrun */
#define SPI_INT_STA_TC (0x1 << 12) /* Transfer Completed */
#define SPI_INT_STA_SSI                                                        \
    (0x1 << 13) /* SS invalid interrupt, when set SS has changed from      \
valid to invalid */
#define SPI_INT_STA_ERR                                                        \
    (SPI_INT_STA_TX_OVF | SPI_INT_STA_RX_UDR |                             \
     SPI_INT_STA_RX_OVF) /* NO txFIFO underrun */
#define SPI_INT_STA_MASK (0x77 | (0x3f << 8))

/* SPI FIFO Control Register Bit Fields & Masks,default value:0x0040_0001 */
#define SPI_FIFO_CTL_RX_LEVEL                                                  \
    (0xFF << 0) /* rxFIFO reday request trigger level,default 0x1 */
#define SPI_FIFO_CTL_RX_DRQEN                                                  \
    (0x1 << 8) /* rxFIFO DMA request enable,1:enable,0:disable */
#define SPI_FIFO_CTL_RX_TESTEN                                                 \
    (0x1 << 14) /* rxFIFO test mode enable,1:enable,0:disable */
#define SPI_FIFO_CTL_RX_RST                                                    \
    (0x1 << 15) /* rxFIFO reset, write 1, auto clear to 0 */
#define SPI_FIFO_CTL_TX_LEVEL                                                  \
    (0xFF << 16) /* txFIFO empty request trigger level,default 0x40 */
#define SPI_FIFO_CTL_TX_DRQEN                                                  \
    (0x1 << 24) /* txFIFO DMA request enable,1:enable,0:disable */
#define SPI_FIFO_CTL_TX_TESTEN                                                 \
    (0x1 << 30) /* txFIFO test mode enable,1:enable,0:disable */
#define SPI_FIFO_CTL_TX_RST                                                    \
    (0x1 << 31) /* txFIFO reset, write 1, auto clear to 0 */
#define SPI_FIFO_CTL_DRQEN_MASK (SPI_FIFO_CTL_TX_DRQEN | SPI_FIFO_CTL_RX_DRQEN)

/* SPI FIFO Status Register Bit Fields & Masks,default value:0x0000_0000 */
#define SPI_FIFO_STA_RX_CNT                                                    \
    (0xFF << 0) /* rxFIFO counter,how many bytes in rxFIFO */
#define SPI_FIFO_STA_RB_CNT                                                    \
    (0x7 << 12) /* rxFIFO read buffer counter,how many bytes in rxFIFO     \
read buffer */
#define SPI_FIFO_STA_RB_WR (0x1 << 15) /* rxFIFO read buffer write enable */
#define SPI_FIFO_STA_TX_CNT                                                    \
    (0xFF << 16) /* txFIFO counter,how many bytes in txFIFO */
#define SPI_FIFO_STA_TB_CNT                                                    \
    (0x7 << 28) /* txFIFO write buffer counter,how many bytes in txFIFO    \
write buffer */
#define SPI_FIFO_STA_TB_WR (0x1 << 31) /* txFIFO write buffer write enable */
#define SPI_RXCNT_BIT_POS (0)
#define SPI_TXCNT_BIT_POS (16)

/* SPI Wait Clock Register Bit Fields & Masks,default value:0x0000_0000 */
#define SPI_WAIT_WCC_MASK                                                      \
    (0xFFFF << 0) /* used only in master mode: Wait Between Transactions   \
*/
#define SPI_WAIT_SWC_MASK                                                      \
    (0xF << 16) /* used only in master mode: Wait before start dual data   \
transfer in dual SPI mode */

/* SPI Clock Control Register Bit Fields & Masks,default:0x0000_0002 */
#define SPI_CLK_CTL_CDR2                                                       \
    (0xFF << 0) /* Clock Divide Rate 2,master mode only : SPI_CLK =        \
AHB_CLK/(2*(n+1)) */
#define SPI_CLK_CTL_CDR1                                                       \
    (0xF << 8) /* Clock Divide Rate 1,master mode only : SPI_CLK =         \
AHB_CLK/2^n */
#define SPI_CLK_CTL_DRS                                                        \
    (0x1 << 12) /* Divide rate select,default,0:rate 1;1:rate 2 */
#define SPI_CLK_SCOPE (SPI_CLK_CTL_CDR2 + 1)

/* SPI Master Burst Counter Register Bit Fields & Masks,default:0x0000_0000 */
/* master mode: when SMC = 1,BC specifies total burst number, Max length is
 * 16Mbytes */
#define SPI_BC_CNT_MASK                                                        \
    (0xFFFFFF << 0) /* Total Burst Counter, tx length + rx length ,SMC=1   \
*/

/* SPI Master Transmit Counter reigster default:0x0000_0000 */
#define SPI_TC_CNT_MASK                                                        \
    (0xFFFFFF                                                              \
     << 0) /* Write Transmit Counter, tx length, NOT rx length!!! */

/* SPI Master Burst Control Counter reigster Bit Fields &
 * Masks,default:0x0000_0000 */
#define SPI_BCC_STC_MASK                                                       \
    (0xFFFFFF << 0)           /* master single mode transmit counter */
#define SPI_BCC_DBC_MASK (0xF << 24)  /* master dummy burst counter */
#define SPI_BCC_DUAL_MODE (0x1 << 28) /* master dual mode RX enable */
#define SPI_BCC_QUAD_MODE (0x1 << 29) /* master quad mode RX enable */

#define SPI_PHA_ACTIVE_ (0x01)
#define SPI_POL_ACTIVE_ (0x02)

#define SPI_MODE_0_ACTIVE_ (0 | 0)
#define SPI_MODE_1_ACTIVE_ (0 | SPI_PHA_ACTIVE_)
#define SPI_MODE_2_ACTIVE_ (SPI_POL_ACTIVE_ | 0)
#define SPI_MODE_3_ACTIVE_ (SPI_POL_ACTIVE_ | SPI_PHA_ACTIVE_)
#define SPI_CS_HIGH_ACTIVE_ (0x04)
#define SPI_LSB_FIRST_ACTIVE_ (0x08)
#define SPI_DUMMY_ONE_ACTIVE_ (0x10)
#define SPI_RECEIVE_ALL_ACTIVE_ (0x20)

#define SUNXI_SPI_DRQ_RX(ch) (DRQSRC_SPI0_RX + ch)
#define SUNXI_SPI_DRQ_TX(ch) (DRQDST_SPI0_TX + ch)

#define SPIM_BUSY (1)
#define SPIM_IDLE (0)

#define spim_set_idle(master_port)                                             \
    do {                                                                   \
        g_spi_master_status[master_port] = SPIM_IDLE;                  \
    } while (0)

#define SPI_MASTER_MB_LSB_FIRST (0x1UL << 3)
#define SPI_MASTER_MB_MSB_FIRST (0x0UL << 3)

#define SPI_MASTER_CPOL_0 (0x0UL << 4)
#define SPI_MASTER_CPOL_1 (0x1UL << 4)

#define SPI_MASTER_CPHA_0 (0x0UL << 5)
#define SPI_MASTER_CPHA_1 (0x1UL << 5)

#define SPI_MASTER_INT_DISABLE (0x0UL << 9)
#define SPI_MASTER_INT_ENABLE (0x1UL << 9)

#define SPI_MASTER_HALF_DUPLEX (0x0UL << 10)
#define SPI_MASTER_FULL_DUPLEX (0x1UL << 10)

#define SPI_MASTER_SLAVE_SEL_0 (0x0UL << 29)
#define SPI_MASTER_SLAVE_SEL_1 (0x1UL << 29)

#ifdef __cplusplus
}
#endif
#endif /* __COMMON_SPI_I_H__ */
