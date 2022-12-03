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

#ifndef __COMMON_TWI_I_H__
#define __COMMON_TWI_I_H__

#ifdef __cplusplus
extern "C" {
#endif

/* TWI Register Offset */
#define TWI_ADDR_REG        (0x00)  /*  31:8bit reserved,7-1bit for slave addr,0 bit for GCE */
#define TWI_XADDR_REG       (0x04)  /*  31:8bit reserved,7-0bit for second addr in 10bit addr */
#define TWI_DATA_REG        (0x08)  /*  31:8bit reserved, 7-0bit send or receive data byte */
#define TWI_CTL_REG         (0x0C)  /*  INT_EN,BUS_EN,M_STA,INT_FLAG,A_ACK */
#define TWI_STAT_REG        (0x10)  /*  28 interrupt types + 0xF8 normal type = 29  */
#define TWI_CLK_REG         (0x14)  /*  31:7bit reserved,6-3bit,CLK_M,2-0bit CLK_N */
#define TWI_SRST_REG        (0x18)  /*  31:1bit reserved;0bit,write 1 to clear 0. */
#define TWI_EFR_REG         (0x1C)  /*  31:2bit reserved,1:0 bit data byte follow read command */
#define TWI_LCR_REG         (0x20)  /*  31:6bits reserved  5:0bit for sda&scl control*/
#define TWI_DVFS_REG        (0x24)  /*  31:3bits reserved  2:0bit for dvfs control. only A10 support. */
#define TWI_DRIVER_CTRL     (0x200)
#define TWI_DRIVER_CFG      (0x204)
#define TWI_DRIVER_SLV      (0x208)
#define TWI_DRIVER_FMT      (0x20C)
#define TWI_DRIVER_BUSC     (0x210)
#define TWI_DRIVER_INTC     (0x214)
#define TWI_DRIVER_DMAC     (0x218)
#define TWI_DRIVER_FIFOC    (0x21C)
#define TWI_DRIVER_SENDF    (0x300)
#define TWI_DRIVER_RECVF    (0x304)

/* TWI address register */
/* general call address enable for slave mode */
#define TWI_GCE_EN      (0x1<<0)
#define TWI_ADDR_MASK       (0x7f<<1)   /* 7:1bits */
/* 31:8bits reserved */


/* TWI extend address register */
/* 7:0bits for extend slave address */
#define TWI_XADDR_MASK      (0xff)
/* 31:8bits reserved */


/* TWI Data register default is 0x0000_0000 */
/* 7:0bits for send or received */
#define TWI_DATA_MASK       (0xff)

/* TWI Control Register Bit Fields & Masks, default value: 0x0000_0000*/
/* 1:0 bits reserved */
/* set 1 to send A_ACK,then low level on SDA */
#define TWI_CTL_ACK     (0x1<<2)
/* INT_FLAG,interrupt status flag: set '1' when interrupt coming */
#define TWI_CTL_INTFLG      (0x1<<3)
#define TWI_CTL_STP     (0x1<<4)    /* M_STP,Automatic clear 0 */
#define TWI_CTL_STA     (0x1<<5)    /* M_STA,atutomatic clear 0 */
/* BUS_EN, master mode should be set 1.*/
#define TWI_CTL_BUSEN       (0x1<<6)
#define TWI_CTL_INTEN       (0x1<<7)    /* INT_EN */
/* 31:8 bit reserved */

/* TWI Clock Register Bit Fields & Masks,default value:0x0000_0000 */
/*
 * Fin is APB CLOCK INPUT;
 * Fsample = F0 = Fin/2^CLK_N;
 *  F1 = F0/(CLK_M+1);
 *
 * Foscl = F1/10 = Fin/(2^CLK_N * (CLK_M+1)*10);
 * Foscl is clock SCL;standard mode:100KHz or fast mode:400KHz
 */
#define TWI_CLK_DUTY        (0x1<<7)    /* 7bit  */
#define TWI_CLK_DIV_M       (0xf<<3)    /* 6:3bit  */
#define TWI_CLK_DIV_N       (0x7<<0)    /* 2:0bit */

/* TWI Soft Reset Register Bit Fields & Masks  */
/* write 1 to clear 0, when complete soft reset clear 0 */
#define TWI_SRST_SRST       (0x1<<0)

/* TWI Enhance Feature Register Bit Fields & Masks  */
/* default -- 0x0 */
/* 00:no,01: 1byte, 10:2 bytes, 11: 3bytes */
#define TWI_EFR_MASK        (0x3<<0)
#define TWI_EFR_WARC_0      (0x0<<0)
#define TWI_EFR_WARC_1      (0x1<<0)
#define TWI_EFR_WARC_2      (0x2<<0)
#define TWI_EFR_WARC_3      (0x3<<0)

/* twi line control register -default value: 0x0000_003a */
/* SDA line state control enable ,1:enable;0:disable */
#define TWI_LCR_SDA_EN      (0x01<<0)
/* SDA line state control bit, 1:high level;0:low level */
#define TWI_LCR_SDA_CTL     (0x01<<1)
/* SCL line state control enable ,1:enable;0:disable */
#define TWI_LCR_SCL_EN      (0x01<<2)
/* SCL line state control bit, 1:high level;0:low level */
#define TWI_LCR_SCL_CTL     (0x01<<3)
/* current state of SDA,readonly bit */
#define TWI_LCR_SDA_STATE_MASK  (0x01<<4)
/* current state of SCL,readonly bit */
#define TWI_LCR_SCL_STATE_MASK  (0x01<<5)
/* 31:6bits reserved */
#define TWI_LCR_IDLE_STATUS (0x3a)
#define TWI_LCR_NORM_STATUS (0x30)      /* normal status */

/* TWI Status Register Bit Fields & Masks  */
#define TWI_STAT_MASK       (0xff)
/* 7:0 bits use only,default is 0xF8 */
#define TWI_STAT_BUS_ERR    (0x00)  /* BUS ERROR */
/* Master mode use only */
#define TWI_STAT_TX_STA     (0x08)  /* START condition transmitted */
/* Repeated START condition transmitted */
#define TWI_STAT_TX_RESTA   (0x10)
/* Address+Write bit transmitted, ACK received */
#define TWI_STAT_TX_AW_ACK  (0x18)
/* Address+Write bit transmitted, ACK not received */
#define TWI_STAT_TX_AW_NAK  (0x20)
/* data byte transmitted in master mode,ack received */
#define TWI_STAT_TXD_ACK    (0x28)
/* data byte transmitted in master mode ,ack not received */
#define TWI_STAT_TXD_NAK    (0x30)
/* arbitration lost in address or data byte */
#define TWI_STAT_ARBLOST    (0x38)
/* Address+Read bit transmitted, ACK received */
#define TWI_STAT_TX_AR_ACK  (0x40)
/* Address+Read bit transmitted, ACK not received */
#define TWI_STAT_TX_AR_NAK  (0x48)
/* data byte received in master mode ,ack transmitted */
#define TWI_STAT_RXD_ACK    (0x50)
/* date byte received in master mode,not ack transmitted */
#define TWI_STAT_RXD_NAK    (0x58)
/* Slave mode use only */
/* Slave address+Write bit received, ACK transmitted */
#define TWI_STAT_RXWS_ACK   (0x60)
#define TWI_STAT_ARBLOST_RXWS_ACK   (0x68)
/* General Call address received, ACK transmitted */
#define TWI_STAT_RXGCAS_ACK     (0x70)
#define TWI_STAT_ARBLOST_RXGCAS_ACK (0x78)
#define TWI_STAT_RXDS_ACK       (0x80)
#define TWI_STAT_RXDS_NAK       (0x88)
#define TWI_STAT_RXDGCAS_ACK        (0x90)
#define TWI_STAT_RXDGCAS_NAK        (0x98)
#define TWI_STAT_RXSTPS_RXRESTAS    (0xA0)
#define TWI_STAT_RXRS_ACK       (0xA8)
#define TWI_STAT_ARBLOST_SLAR_ACK   (0xB0)
/* 10bit Address, second part of address */
/* Second Address byte+Write bit transmitted,ACK received */
#define TWI_STAT_TX_SAW_ACK     (0xD0)
/* Second Address byte+Write bit transmitted,ACK not received */
#define TWI_STAT_TX_SAW_NAK     (0xD8)
/* No relevant status information,INT_FLAG = 0 */
#define TWI_STAT_IDLE           (0xF8)

/* Offset:0x0200. Twi driver control register(Default Value:0x00F8_0000) */
#define TWI_DRV_EN  (0x01<<0)
#define TWI_DRV_RST (0x01<<1)
#define TWI_DRV_STA (0xff<<16)
#define TRAN_RESULT (0x0f<<24)
#define READ_TRAN   (0x01<<28)
#define START_TRAN  (0x01<<31)
#define TRAN_OK     0x00
#define TRAN_FAIL   0x01

/*
 * Offset:0x0204.
 * Twi driver transmission configuration register(Default Value:0x1000_0001)
 */
#define PACKET_MASK (0xffff<<0)
#define INTERVAL_MASK   (0xff<<16)

/* Offset:0x0208. Twi driver slave id register(Default Value:0x0000_0000) */
#define SLV_ID_X    (0xff<<0)
#define SLV_RD_CMD  (0x01<<8)
#define SLV_ID      (0x7f<<9)

/*
 * Offset:0x020C.
 * Twi driver packet format register(Default Value:0x0001_0001)
 */
#define DATA_BYTE   0xffff
#define ADDR_BYTE   (0xff<<16)

/* Offset:0x0210. Twi driver bus control register(Default Value:0x0000_00C0) */
#define TWI_DRV_CLK_DUTY    (0x01<<16)
#define TWI_DRV_CLK_M       (0x0f<<8)
#define TWI_DRV_CLK_N       (0x07<<12)

/*
 * Offset:0x0214.
 * Twi driver interrupt control register(Default Value:0x0000_0000)
 */
#define TRAN_COM_PD (0x1<<0)
#define TRAN_ERR_PD (0x1<<1)
#define TX_REQ_PD   (0x1<<2)
#define RX_REQ_PD   (0x1<<3)
#define TRAN_COM_INT    (0x1<<16)
#define TRAN_ERR_INT    (0x1<<17)
#define TX_REQ_INT  (0x1<<18)
#define RX_REQ_INT  (0x1<<19)
#define TWI_DRV_INT_MASK    (0x0f<<16)
#define TWI_DRV_STAT_MASK   (0x0f<<0)

/*
 * Offset:0x0218.
 * Twi driver DMA configure register(Default Value:0x0010_0010)
 */
#define TRIG_DEFAULT    0x10
#define TRIG_MASK   0x3f
#define DMA_TX      (0x01<<8)
#define DMA_RX      (0x01<<24)
#define TWI_DRQEN_MASK  (DMA_TX | DMA_RX)

/* Offset:0x021C. Twi driver FIFO content register(Default Value:0x0000_0000) */
#define SEND_FIFO_CONT  (0x3f<<0)
#define SEND_FIFO_CLEAR (0x01<<6)
#define RECV_FIFO_CONT  (0x3f<<16)
#define RECV_FIFO_CLEAR (0x01<<22)

/*
 * Offset:0x0300.
 * Twi driver send data FIFO access register(Default Value:0x0000_0000)
 */
#define SEND_DATA_FIFO  (0xff<<0)


/*
 * Offset:0x0304.
 * Twi driver receive data FIFO access register(Default Value:0x0000_0000)
 */
#define RECV_DATA_FIFO  (0xff<<0)

/* TWI driver result */
#define RESULT_COMPLETE 1
#define RESULT_ERR  2

/* TWI mode select */
#define TWI_MASTER_MODE     (1)
#define TWI_SLAVE_MODE      (0) /* seldom use */

#define TWI_SEM_MAX_COUNT 0xFFFFFFFFUL

#define SUNXI_TWI_OK      0
#define SUNXI_TWI_FAIL   -1
#define SUNXI_TWI_RETRY  -2
#define SUNXI_TWI_SFAIL  -3  /* start fail */
#define SUNXI_TWI_TFAIL  -4  /* stop  fail */

#define DMA_THRESHOLD   32
#define MAX_FIFO    32
#define DMA_TIMEOUT 1000

#define TWI_PIN_NUM 2 /*pin num of twi*/

#ifdef __cplusplus
}
#endif
#endif /* __COMMON_TWI_I_H__ */
