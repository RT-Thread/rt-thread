/***************************************************************************//**
 * @file    drv_ethernet.c
 * @brief   Ethernet driver (SPI mode) of RT-Thread RTOS for using EFM32 USART
 *  module
 *   This driver is tested by using the Microchip ENC28J60 stand-alone Ethernet
 *  controller with SPI interface.
 *  COPYRIGHT (C) 2012, RT-Thread Development Team
 * @author  onelife
 * @version 1.0
 *******************************************************************************
 * @section License
 * The license and distribution terms for this file may be found in the file
 *  LICENSE in this distribution or at http://www.rt-thread.org/license/LICENSE
 *******************************************************************************
 * @section Change Logs
 * Date         Author      Notes
 * 2011-06-22   onelife     Initial creation for using EFM32 USART module
 * 2011-07-25   onelife     Add lock (semaphore) to prevent simultaneously
 *  access
 * 2011-07-28   onelife     Add get_ip() and update_ip() utilities
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup efm32_eth
 * @{
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "board.h"
#include "drv_usart.h"
#include "hdl_interrupt.h"
#include "drv_ethernet.h"

#if defined(EFM32_USING_ETHERNET)
#include <netif/ethernetif.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#ifdef EFM32_ETHERNET_DEBUG
#define eth_debug(format,args...)           rt_kprintf(format, ##args)
#else
#define eth_debug(format,args...)
#endif

/* Private constants ---------------------------------------------------------*/
static const rt_uint8_t     eth_addr[ETH_ADDR_LEN] = ETH_ADDR_DEFAULT;

/* Private variables ---------------------------------------------------------*/
static struct eth_device    eth_dev;
static struct rt_semaphore  ethLock;
static rt_uint8_t           ethBank;
static rt_uint16_t          ethNxtPkt;
static rt_device_t          spi             = RT_NULL;
static rt_bool_t            ethAutoCs       = true;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/***************************************************************************//**
 * @brief
 *   Set/Clear chip select
 *
 * @details
 *
 * @note
 *
 * @param[in] enable
 *  Chip select pin setting
 ******************************************************************************/
static void efm_eth_cs(rt_uint8_t enable)
{
    if (!ethAutoCs)
    {
        if (enable)
        {
            GPIO_PinOutClear(ETH_CS_PORT, ETH_CS_PIN);
        }
        else
        {
            GPIO_PinOutSet(ETH_CS_PORT, ETH_CS_PIN);
        }
    }
}

/***************************************************************************//**
 * @brief
 *  Send command to Ethernet device
 *
 * @details
 *
 * @note
 *
 * @param[in] cmd
 *   Command index
 *
 * @param[in] addr
 *   Register address
 *
 * @param[in/out] data
 *   Pointer to the buffer of register value
 *
 * @return
 *   Error code
 ******************************************************************************/
static rt_err_t efm_eth_cmd(
    rt_uint8_t cmd,
    rt_uint8_t addr,
    rt_uint8_t *data)
{
    RT_ASSERT(spi != RT_NULL);

    rt_uint8_t buf_ins[6], buf_res[2];
    rt_uint8_t len_ins, len_res;

    len_ins = 0;
    do
    {
        /* Build instruction buffer */
        /* Check if need to read back */
        if (cmd == ENC28J60_READ_CTRL_REG)
        {
            buf_ins[len_ins++] = 1;                         /* Instruction length */
        }
        /* Byte 0: Check if no address section */
        if (cmd == ENC28J60_READ_BUF_MEM || cmd == ENC28J60_WRITE_BUF_MEM || \
            cmd == ENC28J60_SOFT_RESET)
        {
            buf_ins[len_ins++] = cmd;
        }
        else
        {
            buf_ins[len_ins++] = cmd | (addr & ADDR_MASK);
        }
        /* Byte 1: Check if data section is present */
        if (cmd == ENC28J60_WRITE_CTRL_REG || cmd == ENC28J60_BIT_FIELD_SET || \
            cmd == ENC28J60_BIT_FIELD_CLR || cmd == ENC28J60_WRITE_BUF_MEM)
        {
            buf_ins[len_ins++] = *data;
        }

        /* Check if reading */
        if (cmd == ENC28J60_READ_CTRL_REG)
        {
            *(rt_uint8_t **)(&buf_ins[len_ins]) = buf_res;  /* Pointer to RX buffer */
            len_ins += 4;

            /* Check if MAC or MII register */
            if (addr & SPRD_MASK)
            {
                len_res = 2;
            }
            else
            {
                len_res = 1;
            }

            /* Send command and get response */
            efm_eth_cs(1);
            if (spi->read(spi, ETH_SPI_RX_SKIP, buf_ins, len_res) == 0)
            {
                break;
            }
            *data = buf_res[len_res - 1];
//          eth_debug("ETH: read RX %x %x (%d)\n", buf_res[0], buf_res[1], len_res);
//          eth_debug("ETH: ** read RX %x %x (%d)\n",
//              buf_res[0], buf_res[1], buf_res[2], buf_res[3], buf_res[4],
//              buf_res[5], buf_res[6], buf_res[7], buf_res[8], buf_res[9],
//              len_res);
        }
        else
        {
//          eth_debug("ETH: ** write TX %x %x %x %x %x %x (%d) \n", buf_ins[0],
//              buf_ins[1], buf_ins[2], buf_ins[3], buf_ins[4], buf_ins[5],
//              len_ins);
            /* Send command and get response */
            efm_eth_cs(1);
            if (spi->write(spi, EFM32_NO_DATA, buf_ins, len_ins) == 0)
            {
                break;
            }
        }

        if (!(cmd == ENC28J60_READ_BUF_MEM || cmd == ENC28J60_WRITE_BUF_MEM))
        {
            efm_eth_cs(0);
        }
        return RT_EOK;
    } while(0);

    eth_debug("ETH: Send command failed!\n");
    efm_eth_cs(0);
    return -RT_ERROR;
}

/***************************************************************************//**
 * @brief
 *  Wrapper function of send command to Ethernet device
 *
 * @details
 *
 * @note
 *
 * @param[in] cmd
 *   Command index
 *
 * @param[in] addr
 *   Register address
 *
 * @param[in/out] data
 *   Pointer to the buffer of register value
 *
 * @return
 *   Error code
 ******************************************************************************/
static rt_err_t efm_eth_sendCmd(
    rt_uint8_t cmd,
    rt_uint8_t addr,
    rt_uint8_t *data)
{
    rt_err_t ret;

    eth_debug("ETH: Send command %x (%x %x)\n", cmd, addr, *data);
    do
    {
        /* Change bank */
        if(((addr & BANK_MASK) != ethBank) && ((addr < EIE) || (addr > ECON1)))
        {
            rt_uint8_t temp;

            if ((ret = efm_eth_cmd(ENC28J60_READ_CTRL_REG, ECON1, &temp)) != RT_EOK)
            {
                break;
            }
            temp &= 0xFC;
            ethBank = (addr & BANK_MASK);
            temp |= ethBank >> BANK_SHIFT;
            if ((ret = efm_eth_cmd(ENC28J60_WRITE_CTRL_REG, ECON1, &temp)) != RT_EOK)
            {
                break;
            }
        }
        /* Send command */
        ret = efm_eth_cmd(cmd, addr, data);
    } while(0);

    return ret;
}

/***************************************************************************//**
 * @brief
 *  Read register of Ethernet device
 *
 * @details
 *
 * @note
 *
 * @param[in] addr
 *   Register address
 *
 * @return
 *   Register value
 ******************************************************************************/
static rt_uint8_t efm_eth_readReg(rt_uint8_t addr)
{
    rt_uint8_t data;

    efm_eth_sendCmd(ENC28J60_READ_CTRL_REG, addr, &data);

    return data;
}

/***************************************************************************//**
 * @brief
 *  Write register of Ethernet device
 *
 * @details
 *
 * @note
 *
 * @param[in] addr
 *   Register address
 *
 * @param[in] data
 *   Register value
 ******************************************************************************/
static void efm_eth_writeReg(rt_uint8_t addr, rt_uint8_t data)
{
    efm_eth_sendCmd(ENC28J60_WRITE_CTRL_REG, addr, &data);
}

/***************************************************************************//**
 * @brief
 *  Read PHY register of Ethernet device
 *
 * @details
 *
 * @note
 *
 * @param[in] addr
 *   Register address
 *
 * @return
 *   Register value
 ******************************************************************************/
static rt_uint16_t efm_eth_readPhy(rt_uint8_t addr)
{
    rt_uint16_t ret;

    eth_debug("ETH: *** read PHY %x\n", addr);

    /* Set PHY register address */
    efm_eth_writeReg(MIREGADR, addr);

    /* Start read operation */
    efm_eth_writeReg(MICMD, MICMD_MIIRD);
    /* Waiting for at least 10.24 uS */
    while(efm_eth_readReg(MISTAT) & MISTAT_BUSY);

    /* Stop read operation */
    efm_eth_writeReg(MICMD, 0x00);

    /* Get the result */
    ret = (rt_uint16_t)efm_eth_readReg(MIRDL);
    ret |= (rt_uint16_t)efm_eth_readReg(MIRDH) << 8;
    return ret;
}

/***************************************************************************//**
 * @brief
 *  Write PHY register of Ethernet device
 *
 * @details
 *
 * @note
 *
 * @param[in] addr
 *   Register address
 *
 * @param[in] data
 *   Register value
 ******************************************************************************/
static void efm_eth_writePhy(rt_uint8_t addr, rt_uint16_t data)
{
    eth_debug("ETH: *** write PHY %x (%x)\n", addr, data);

    /* Set PHY register address */
    efm_eth_writeReg(MIREGADR, addr);

    /* Set data */
    efm_eth_writeReg(MIWRL, data);
    efm_eth_writeReg(MIWRH, data >> 8);
    /* Waiting for at least 10.24 uS */
    while(efm_eth_readReg(MISTAT) & MISTAT_BUSY);
}

/***************************************************************************//**
 * @brief
 *  Interrupt handler of Ethernet device
 *
 * @details
 *
 * @note
 *
 * @param[in] dev
 *  Pointer to device descriptor
 ******************************************************************************/
void efm_eth_isr(rt_device_t dev)
{
    rt_uint8_t reg_eir, data;
    volatile rt_uint8_t cnt;

    /* Disable RX and other interrutps */
    data = EIE_PKTIE | EIE_INTIE;
    efm_eth_sendCmd(ENC28J60_BIT_FIELD_CLR, EIE, &data);

    /* Get interrupt flag */
    efm_eth_sendCmd(ENC28J60_READ_CTRL_REG, EIR, &reg_eir);

    data = 0;
    /* DMA completed */
    if (reg_eir & EIR_DMAIF)
    {
        data |= (rt_uint8_t)EIR_DMAIF;
    }
    /* Link Changed */
    if (reg_eir & EIR_LINKIF)
    {
        /* Read PHIR to clear the flag */
        efm_eth_readPhy(PHIR);
    }
    /* TX done */
    if (reg_eir & EIR_TXIF)
    {
        data |= (rt_uint8_t)EIR_TXIF;
    }
    /* TX error */
    if (reg_eir & EIR_TXERIF)
    {
        data |= (rt_uint8_t)EIR_TXERIF;
    }
    /* RX error */
    if (reg_eir & EIR_RXERIF)
    {
        data |= (rt_uint8_t)EIR_RXERIF;
    }
    /* Clear flags */
    efm_eth_sendCmd(ENC28J60_BIT_FIELD_CLR, EIR, &data);

    /* Get packet counter (Errata 6) */
    efm_eth_sendCmd(ENC28J60_READ_CTRL_REG, EPKTCNT, (rt_uint8_t *)&cnt);
    if (cnt)
    {
        /* Inform Ethernet thread */
        eth_device_ready(&eth_dev);
    }

    /* Enable other interrupts */
    data = EIE_INTIE;
    efm_eth_sendCmd(ENC28J60_BIT_FIELD_SET, EIE, &data);
}

/***************************************************************************//**
 * @brief
 *   Initialize Ethernet device
 *
 * @details
 *
 * @note
 *
 * @param[in] dev
 *   Pointer to device descriptor
 *
 * @return
 *   Error code
 ******************************************************************************/
static rt_err_t efm_eth_init(rt_device_t dev)
{
    rt_uint16_t reg_phy;
    rt_uint8_t data;

    /* Reset chip select */
    efm_eth_cs(0);
    /* Software reset */
    efm_eth_sendCmd(ENC28J60_SOFT_RESET, EFM32_NO_DATA, EFM32_NO_POINTER);
    /* Waiting for at least 1 ms (Errata 2) */
    rt_thread_delay(ETH_PERIOD_WAIT_INIT);
    ethNxtPkt = RXSTART_INIT;
    ethBank = 0;

    /* Init RX buffer */
    efm_eth_writeReg(ERXSTL, RXSTART_INIT & 0xFF);
    efm_eth_writeReg(ERXSTH, RXSTART_INIT >> 8);
    efm_eth_writeReg(ERXNDL, RXSTOP_INIT & 0xFF);
    efm_eth_writeReg(ERXNDH, RXSTOP_INIT >> 8);
    efm_eth_writeReg(ERXRDPTL, RXSTOP_INIT & 0xFF);
    efm_eth_writeReg(ERXRDPTH, RXSTOP_INIT >> 8);

    /* Init TX buffer */
    efm_eth_writeReg(ETXSTL, TXSTART_INIT & 0xFF);
    efm_eth_writeReg(ETXSTH, TXSTART_INIT >> 8);
    efm_eth_writeReg(ETXNDL, TXSTOP_INIT & 0xFF);
    efm_eth_writeReg(ETXNDH, TXSTOP_INIT >> 8);
    efm_eth_writeReg(EWRPTL, TXSTART_INIT & 0xFF);
    efm_eth_writeReg(EWRPTH, TXSTART_INIT >> 8);

    /* Init RX filters */
    /* For broadcast packets we allow only ARP packtets
       All other packets should be unicast only for our mac (MAADR)

       The pattern to match on is therefore
       Type                    ETH.DST
       ARP                     BROADCAST
       06 08 -- -- -- -- -- -- ff ff ff ff ff ff
       These poitions are: 11 0000 0011 1111 in binary and 30 3f in hex
       Checksum for theses bytes is: f7 f9 */
    efm_eth_writeReg(EPMM0, 0x3f);
    efm_eth_writeReg(EPMM1, 0x30);
    efm_eth_writeReg(EPMCSL, 0xf9);
    efm_eth_writeReg(EPMCSH, 0xf7);
    efm_eth_writeReg(ERXFCON, ERXFCON_UCEN | ERXFCON_CRCEN | ERXFCON_PMEN);
    //efm_eth_writeReg(ERXFCON, ERXFCON_UCEN | ERXFCON_CRCEN | ERXFCON_BCEN);
    /* Waiting For OST: The OST does not expire until 7500 OSC1 clock cycles (300 uS)
        pass after Power-on Reset or wake-up from Power-Down mode occurs */

    /* Init MAC */
    /* Enable RX, IEEE defined flow control */
    efm_eth_writeReg(MACON1, MACON1_MARXEN | MACON1_TXPAUS | MACON1_RXPAUS);
    /* Enable padding to 60 bytes, CRC and frame length status reporting */
#if defined(ETH_HALF_DUPLEX)
    efm_eth_writeReg(MACON3, MACON3_PADCFG0 | MACON3_TXCRCEN | MACON3_FRMLNEN);
    efm_eth_writeReg(MACON4, MACON4_DEFER);
#else
    efm_eth_writeReg(MACON3, \
        MACON3_PADCFG0 | MACON3_TXCRCEN | MACON3_FRMLNEN | MACON3_FULDPX);
#endif
    /* Set the maximum packet length */
    efm_eth_writeReg(MAMXFLL, MAX_FRAMELEN & 0xFF);
    efm_eth_writeReg(MAMXFLH, MAX_FRAMELEN >> 8);
    /* Set inter-packet gap (back-to-back). Full-Duplex: 0x15, Half-Duplex: 0x12 */
#if defined(ETH_HALF_DUPLEX)
    efm_eth_writeReg(MABBIPG, 0x12);
#else
    efm_eth_writeReg(MABBIPG, 0x15);
#endif
    /* Set inter-packet gap (non-back-to-back).
        Full-Duplex: 0x0012, Half-Duplex: 0x0C12 */
    efm_eth_writeReg(MAIPGL, 0x12);
#if defined(ETH_HALF_DUPLEX)
    efm_eth_writeReg(MAIPGH, 0x0C);
    /* Set retransmission and collision window */
    efm_eth_writeReg(MACLCON1, 0x0F);
    efm_eth_writeReg(MACLCON2, 0x37);
#endif
    /* Set MAC address
        NOTE: MAC address in ENC28J60 is byte-backward */
    efm_eth_writeReg(MAADR1, eth_addr[0]);
    efm_eth_writeReg(MAADR2, eth_addr[1]);
    efm_eth_writeReg(MAADR3, eth_addr[2]);
    efm_eth_writeReg(MAADR4, eth_addr[3]);
    efm_eth_writeReg(MAADR5, eth_addr[4]);
    efm_eth_writeReg(MAADR6, eth_addr[5]);

    /* Init PHY */
#if defined(ETH_HALF_DUPLEX)
    reg_phy = efm_eth_readPhy(PHCON2);
    efm_eth_writePhy(PHCON2, reg_phy | PHCON2_HDLDIS);
#else
    reg_phy = efm_eth_readPhy(PHCON1);
    efm_eth_writePhy(PHCON1, reg_phy | PHCON1_PDPXMD);
#endif
    /* LEDA: Display link status;
       LEDB: Display transmit and receive activity */
    reg_phy = efm_eth_readPhy(PHLCON);
    efm_eth_writePhy(PHLCON, (reg_phy & 0xF00F) | 0x0470);

    /* Disable clock output */
    efm_eth_writeReg(ECOCON, 0x00);

    /* Clear interrutp flags */
    data = EIR_DMAIF | EIR_TXIF | EIR_TXERIF | EIR_RXERIF;
    efm_eth_sendCmd(ENC28J60_BIT_FIELD_CLR, EIR, &data);
    /* Enable interrutps */
    data = EIE_INTIE | EIE_PKTIE | EIE_TXIE;
    efm_eth_sendCmd(ENC28J60_BIT_FIELD_SET, EIE, &data);
    /* Enable RX */
    data = ECON1_RXEN;
    efm_eth_sendCmd(ENC28J60_BIT_FIELD_SET, ECON1, &data);

    eth_debug("ETH: Init OK\n");
    return RT_EOK;
}

/***************************************************************************//**
 * @brief
 *   Open Ethernet device
 *
 * @details
 *
 * @note
 *
 * @param[in] dev
 *   Pointer to device descriptor
 *
 * @param[in] oflag
 *   Device open flag
 *
 * @return
 *   Error code
 ******************************************************************************/
static rt_err_t efm_eth_open(rt_device_t dev, rt_uint16_t oflag)
{
    eth_debug("ETH: Open, flag %x\n", eth_dev.parent.flag);
    return RT_EOK;
}

/***************************************************************************//**
 * @brief
 *   Close Ethernet device
 *
 * @details
 *
 * @note
 *
 * @param[in] dev
 *   Pointer to device descriptor
 *
 * @return
 *   Error code
 ******************************************************************************/
static rt_err_t efm_eth_close(rt_device_t dev)
{
    eth_debug("ETH: Close, flag %x\n", eth_dev.parent.flag);
    return RT_EOK;
}

/***************************************************************************//**
 * @brief
 *   Read from Ethernet device (Dummy function)
 *
 * @details
 *
 * @note
 *
 * @param[in] dev
 *   Pointer to device descriptor
 *
 * @param[in] pos
 *   Offset
 *
 * @param[in] buffer
 *   Poniter to the buffer
 *
 * @param[in] size
 *   Buffer size in byte
 *
 * @return
 *   Number of read bytes
 ******************************************************************************/
static rt_size_t efm_eth_read(
    rt_device_t     dev,
    rt_off_t        pos,
    void            *buffer,
    rt_size_t       size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

/***************************************************************************//**
 * @brief
 *   Write to Ethernet device (Dummy function)
 *
 * @details
 *
 * @note
 *
 * @param[in] dev
 *   Pointer to device descriptor
 *
 * @param[in] pos
 *   Offset
 *
 * @param[in] buffer
 *   Poniter to the buffer
 *
 * @param[in] size
 *   Buffer size in byte
 *
 * @return
 *   Number of written bytes
 ******************************************************************************/
static rt_size_t efm_eth_write (
    rt_device_t     dev,
    rt_off_t        pos,
    const void      *buffer,
    rt_size_t       size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

/***************************************************************************//**
* @brief
*   Configure Ethernet device
*
* @details
*
* @note
*
* @param[in] dev
*   Pointer to device descriptor
*
* @param[in] cmd
*   Ethernet control command
*
* @param[in] args
*   Arguments
*
* @return
*   Error code
******************************************************************************/
static rt_err_t efm_eth_control (
    rt_device_t     dev,
    rt_uint8_t      cmd,
    void            *args)
{
    rt_err_t ret;

    ret = -RT_ERROR;
    switch(cmd)
    {
    case NIOCTL_GADDR:
        /* Get MAC address */
        if(args)
        {
            rt_memcpy(args, eth_addr, sizeof(eth_addr));
            ret = RT_EOK;
        }
        break;

    default :
        break;
    }

    return RT_EOK;
}

/***************************************************************************//**
* @brief
*   Packet receiving function
*
* @details
*
* @note
*
* @param[in] dev
*   Pointer to device descriptor
*
* @return
*   Pointer to packet buffer
******************************************************************************/
struct pbuf *efm_eth_rx(rt_device_t dev)
{
    rt_uint8_t buf_ins[5], buf_read[6];
    rt_uint8_t data, reg_eie;
    rt_uint16_t len_rx, sta_rx;
    struct pbuf* p;

    /* Lock device */
    rt_sem_take(&ethLock, RT_WAITING_FOREVER);

    /* Disable interrupts */
    data = EIE_INTIE;
    efm_eth_sendCmd(ENC28J60_BIT_FIELD_CLR, EIE, &data);

    p = RT_NULL;
    reg_eie = 0;
    if (efm_eth_readReg(EPKTCNT))
    {
        /* Set read pointer to the start of RX packet */
        efm_eth_writeReg(ERDPTL, ethNxtPkt & 0xFF);
        efm_eth_writeReg(ERDPTH, ethNxtPkt >> 8);

        /* Send read buffer command */
        efm_eth_sendCmd(ENC28J60_READ_BUF_MEM, EFM32_NO_DATA, EFM32_NO_POINTER);
        /* Build instruction buffer */
        buf_ins[0] = 0x00;
        *(rt_uint8_t **)(&buf_ins[1]) = buf_read;
        /* Read packet header */
        if (spi->read(spi, EFM32_NO_DATA, buf_ins, sizeof(buf_read)) == 0)
        {
            eth_debug("ETH: RX header failed!\n");
        }

        ethNxtPkt = buf_read[0] | (buf_read[1] << 8);
        len_rx = buf_read[2] | (buf_read[3] << 8);
        sta_rx = buf_read[4] | (buf_read[5] << 8);
        eth_debug("ETH: RX header ethNxtPkt %x, len_rx %x, sta_rx %x\n",
            ethNxtPkt, len_rx, sta_rx);
        /* Check if OK */
        if (sta_rx & 0x80)
        {
            /* Allocate pbuf */
            p = pbuf_alloc(PBUF_LINK, len_rx - 4, PBUF_RAM);
            if (p != RT_NULL)
            {
                struct pbuf* q;

                for (q = p; q != RT_NULL; q= q->next)
                {
                    /* Build instruction buffer */
                    buf_ins[0] = 0x00;
                    *(rt_uint8_t **)(&buf_ins[1]) = q->payload;
                    /* Read packet header */
                    if (spi->read(spi, EFM32_NO_DATA, buf_ins, q->len) == 0)
                    {
                        eth_debug("ETH: RX payload failed!\n");
                    }
#ifdef EFM32_ETHERNET_DEBUG
                    {
                        rt_uint8_t *temp = (rt_uint8_t *)q->payload;
                        rt_uint32_t i;

                        eth_debug("ETH: ***** read RX (q->len %x) *****\n", q->len);
                        for (i = 0; i < q->len; i += 8)
                        {
                            eth_debug("%02x %02x %02x %02x %02x %02x %02x %02x | %c %c %c %c %c %c %c %c\n",
                                temp[i], temp[i + 1], temp[i + 2], temp[i + 3],
                                temp[i + 4], temp[i + 5], temp[i + 6], temp[i + 7],
                                temp[i], temp[i + 1], temp[i + 2], temp[i + 3],
                                temp[i + 4], temp[i + 5], temp[i + 6], temp[i + 7]);
                        }
                    }
#endif
                }
            }
            else
            {
                eth_debug("ETH: No memory for pbuf!!!\n");
            }
        }
        else
        {
            eth_debug("ETH: Invalid CRC or symbol error occurred!\n");
        }
        efm_eth_cs(0);

        /* Free buffer */
        efm_eth_writeReg(ERXRDPTL, ethNxtPkt & 0xFF);
        efm_eth_writeReg(ERXRDPTH, ethNxtPkt >> 8);

        /* Decrease counter */
        data = ECON2_PKTDEC;
        efm_eth_sendCmd(ENC28J60_BIT_FIELD_SET, ECON2, &data);
    }
    else
    {
        /* Enable RX */
        data = ECON1_RXEN;
        efm_eth_sendCmd(ENC28J60_BIT_FIELD_SET, ECON1, &data);

        reg_eie |= EIE_PKTIE;
        eth_debug("ETH: Enable RX interrupt\n");
    }
    eth_debug("ETH: RX counter %x\n", efm_eth_readReg(EPKTCNT));

    /* Enable interrupts */
    reg_eie |= EIE_INTIE;
    efm_eth_sendCmd(ENC28J60_BIT_FIELD_SET, EIE, &reg_eie);

    /* Unlock device */
    rt_sem_release(&ethLock);

    return p;
}

/***************************************************************************//**
* @brief
*   Packet transmission function
*
* @details
*
* @note
*
* @param[in] dev
*   Pointer to device descriptor
*
* @param[in] p
*   Pointer to packet buffer
*
* @return
*   Error code
******************************************************************************/
rt_err_t efm_eth_tx(rt_device_t dev, struct pbuf* p)
{
    rt_uint8_t data;
    struct pbuf* q;

    /* Lock device */
    rt_sem_take(&ethLock, RT_WAITING_FOREVER);

    /* Disable interrupts */
    data = EIE_INTIE;
    efm_eth_sendCmd(ENC28J60_BIT_FIELD_CLR, EIE, &data);

    /* Set write pointer to the start of TX buffer */
    efm_eth_writeReg(EWRPTL, TXSTART_INIT & 0xFF);
    efm_eth_writeReg(EWRPTH, TXSTART_INIT >> 8);
    /* Set buffer end pointer according to the packet size */
    efm_eth_writeReg(ETXNDL, (TXSTART_INIT + p->tot_len + 1) & 0xFF);
    efm_eth_writeReg(ETXNDH, (TXSTART_INIT + p->tot_len + 1) >> 8);

    /* Send write buffer command */
    data = 0x00;    /* Control byte */
    efm_eth_sendCmd(ENC28J60_WRITE_BUF_MEM, EFM32_NO_DATA, &data);
    /* Send data */
    for (q = p; q != NULL; q = q->next)
    {
        if (spi->write(spi, EFM32_NO_DATA, q->payload, q->len) == 0)
        {
            eth_debug("ETH: TX failed!\n");
            return -RT_ERROR;
        }
#ifdef EFM32_ETHERNET_DEBUG
        {
            rt_uint8_t *temp = (rt_uint8_t *)q->payload;
            rt_uint32_t i;

            eth_debug("ETH: ***** write TX (len %d) *****\n", p->len);
            for (i = 0; i < q->len; i += 8)
            {
                eth_debug("%02x %02x %02x %02x %02x %02x %02x %02x | %c %c %c %c %c %c %c %c\n",
                    temp[i], temp[i + 1], temp[i + 2], temp[i + 3],
                    temp[i + 4], temp[i + 5], temp[i + 6], temp[i + 7],
                    temp[i], temp[i + 1], temp[i + 2], temp[i + 3],
                    temp[i + 4], temp[i + 5], temp[i + 6], temp[i + 7]);
            }
        }
#endif
    }
    efm_eth_cs(0);
    /* Start TX */
    data = ECON1_TXRTS;
    efm_eth_sendCmd(ENC28J60_BIT_FIELD_SET, ECON1, &data);
    /* Errata 12 */
    if (efm_eth_readReg(EIR) & EIR_TXERIF)
    {
        efm_eth_sendCmd(ENC28J60_BIT_FIELD_CLR, ECON1, &data);
        data = EIR_TXERIF;
        efm_eth_sendCmd(ENC28J60_BIT_FIELD_CLR, EIR, &data);
        data = ECON1_TXRTS;
        efm_eth_sendCmd(ENC28J60_BIT_FIELD_SET, ECON1, &data);
    }

    /* Waiting for a while */
    rt_thread_delay(ETH_PERIOD_WAIT_INIT);
    /* Enable interrupts */
    data = EIE_INTIE;
    efm_eth_sendCmd(ENC28J60_BIT_FIELD_SET, EIE, &data);

    /* Unlock device */
    rt_sem_release(&ethLock);

    return RT_EOK;
}

/***************************************************************************//**
* @brief
*   Initialize all Ethernet related hardware and register the device to kernel
*
* @details
*
* @note
*
* @return
*   Error code
******************************************************************************/
rt_err_t efm_hw_eth_init(void)
{
    struct efm32_usart_device_t *usart;
    efm32_irq_hook_init_t       hook;

    do
    {
        /* Find SPI device */
        spi = rt_device_find(ETH_USING_DEVICE_NAME);
        if (spi == RT_NULL)
        {
            eth_debug("ETH: Can't find device %s!\n",
                ETH_USING_DEVICE_NAME);
            break;
        }
        eth_debug("ETH: Find device %s\n", ETH_USING_DEVICE_NAME);

        /* Config chip slect pin */
        usart = (struct efm32_usart_device_t *)(spi->user_data);
        if (!(usart->state & USART_STATE_AUTOCS))
        {
            GPIO_PinModeSet(ETH_CS_PORT, ETH_CS_PIN, gpioModePushPull, 1);
            ethAutoCs = false;
        }
        /* Config reset pin */
        GPIO_PinModeSet(ETH_RESET_PORT, ETH_RESET_PIN, gpioModePushPull, 0);
        /* Config interrupt pin */
        GPIO_PinModeSet(ETH_INT_PORT, ETH_INT_PIN, gpioModeInput, 1);

        /* Config interrupt */
        hook.type       = efm32_irq_type_gpio;
        hook.unit       = ETH_INT_PIN;
        hook.cbFunc     = efm_eth_isr;
        hook.userPtr    = RT_NULL;
        efm32_irq_hook_register(&hook);
        /* Clear pending interrupt */
        BITBAND_Peripheral(&(GPIO->IFC), ETH_INT_PIN, 0x1UL);
        /* Set falling edge interrupt and clear/enable it */
        GPIO_IntConfig(
            ETH_INT_PORT,
            ETH_INT_PIN,
            false,
            true,
            true);
        if ((rt_uint8_t)ETH_INT_PIN % 2)
        {
            NVIC_ClearPendingIRQ(GPIO_ODD_IRQn);
            NVIC_SetPriority(GPIO_ODD_IRQn, EFM32_IRQ_PRI_DEFAULT);
            NVIC_EnableIRQ(GPIO_ODD_IRQn);
        }
        else
        {
            NVIC_ClearPendingIRQ(GPIO_EVEN_IRQn);
            NVIC_SetPriority(GPIO_EVEN_IRQn, EFM32_IRQ_PRI_DEFAULT);
            NVIC_EnableIRQ(GPIO_EVEN_IRQn);
        }

        /* Set SPI speed */
        USART_BaudrateSyncSet(usart->usart_device, 0, ETH_CLK_MAX);

        /* Initialize semaphore */
        rt_sem_init(&ethLock, ETH_DEVICE_NAME, 1, RT_IPC_FLAG_FIFO);

        /* Register Ethernet device */
        eth_dev.parent.init     = efm_eth_init;
        eth_dev.parent.open     = efm_eth_open;
        eth_dev.parent.close    = efm_eth_close;
        eth_dev.parent.read     = efm_eth_read;
        eth_dev.parent.write    = efm_eth_write;
        eth_dev.parent.control  = efm_eth_control;
        eth_dev.eth_rx          = efm_eth_rx;
        eth_dev.eth_tx          = efm_eth_tx;
        eth_device_init(&eth_dev, ETH_DEVICE_NAME);

        /* Start device */
        GPIO_PinOutSet(ETH_RESET_PORT, ETH_RESET_PIN);

        eth_debug("ETH: HW init OK\n");
        return RT_EOK;
    } while (0);

    /* Release buffer */
    rt_kprintf("ETH: HW init failed!\n");
    return -RT_ERROR;
}

/*******************************************************************************
 *  Export to FINSH
 ******************************************************************************/
#if defined(EFM32_USING_ETH_UTILS)
#ifdef RT_USING_FINSH
#include <finsh.h>

void list_eth(void)
{
    rt_uint16_t reg_phy;
    rt_uint8_t data;

    rt_kprintf("    ENC28J60 on %s\n", ETH_USING_DEVICE_NAME);
    rt_kprintf(" ------------------------------\n");
    reg_phy = efm_eth_readPhy(PHSTAT2);
    if (reg_phy & PHSTAT2_PLRITY)
    {
        rt_kprintf(" Cable polarity is reversed\n");
    }
    else
    {
        rt_kprintf(" Cable polarity is correct\n");
    }
    if (reg_phy & PHSTAT2_DPXSTAT)
    {
        rt_kprintf(" Full-duplex mode\n");
    }
    else
    {
        rt_kprintf(" Half-duplex mode\n");
    }
    if (reg_phy & PHSTAT2_LSTAT)
    {
        rt_kprintf(" Link is up\n");
    }
    else
    {
        rt_kprintf(" Link is down\n");
    }
    if (reg_phy & PHSTAT2_COLSTAT)
    {
        rt_kprintf(" Collision is occuring\n");
    }
    else
    {
        rt_kprintf(" No collision\n");
    }
    if (reg_phy & PHSTAT2_RXSTAT)
    {
        rt_kprintf(" RX is busy\n");
    }
    else
    {
        rt_kprintf(" RX is idle\n");
    }
    if (reg_phy & PHSTAT2_TXSTAT)
    {
        rt_kprintf(" TX is busy\n");
    }
    else
    {
        rt_kprintf(" TX is idle\n");
    }
}
FINSH_FUNCTION_EXPORT(list_eth, list the Ethernet device status.)

#include "lwip\api.h"

rt_err_t get_ip(char *ip)
{
    err_t ret;
    struct ip_addr server_ip;
    struct netconn *conn;
    struct netbuf *buf;
    char *rq, *rq2;
    u16_t len;
    const char query[] = "GET / HTTP/1.0\r\nHOST: checkip.dyndns.com\r\n\r\n";
    const char find[] = "body";

    do
    {
#if defined(RT_LWIP_DNS)
        ret = netconn_gethostbyname("checkip.dyndns.com", &server_ip);
        if (ret != ERR_OK)
        {
            break;
        }
#else
        IP4_ADDR(&server_ip, 216,146,38,70);    // IP address of "checkip.dyndns.com"
#endif

        conn = netconn_new(NETCONN_TCP);
        if (conn == NULL)
        {
            break;
        }

        ret = netconn_connect(conn, &server_ip, 80);
        if (ret != ERR_OK)
        {
            break;
        }

        /* Send the query */
        ret = netconn_write(conn, query, sizeof(query) - 1, 0);
        if (ret != ERR_OK)
        {
            break;
        }

        buf = netconn_recv(conn);
        if (buf != NULL)
        {
            /* Get the response */
            ret = netbuf_data(buf, (void **)&rq, &len);
            if (ret != ERR_OK)
            {
                break;
            }

            /* Find the IP address */
            rq = rt_strstr(rq, find);
            if (rq == RT_NULL)
            {
                break;
            }
            rq += 5;
            rq2 = rq;
            rq2 = rt_strstr(rq2, find);
            if (rq2 == RT_NULL)
            {
                break;
            }
            rq2 -= 2;
            *rq2 = 0x0;
//          rt_kprintf("[%s]\n", rq);
        }
        else
        {
            break;
        }

        /* Copy the IP address to buffer */
        if (ip != NULL)
        {
            while(*rq < '0' || *rq > '9')
            {
                rq++;
            }
            rt_memcpy(ip, rq, rq2 - rq + 1);
        }
        netconn_delete(conn);
        netbuf_delete(buf);
        return RT_EOK;
    } while (0);

    netconn_delete(conn);
    netbuf_delete(buf);
    return -RT_ERROR;
}

void list_myip(void)
{
    rt_uint8_t ip[20];

    if (get_ip(ip) != RT_EOK)
    {
        rt_kprintf("Get IP failed!\n");
        return;
    }

    rt_kprintf("Current IP: [%s]\n", ip);
}
FINSH_FUNCTION_EXPORT(list_myip, list the current IP address.)

#if !defined(hostName) || !defined(userPwdB64)
#error "The 'hostName' and 'userPwdB64' must be defined to use update_ip() function"
#endif

rt_err_t update_ip(char *ip)
{
    err_t ret;
    struct ip_addr server_ip;
    struct netconn *conn;
    struct netbuf *buf;
    char *rq;
    u16_t len, len2;
    char query[200] = "GET /nic/update?hostname=";
    const char query2[] = "&myip=";
    const char query3[] = " HTTP/1.0\r\nHost: members.dyndns.org\r\nAuthorization: Basic ";
    const char query4[] = "\r\nUser-Agent: onelife - EFM32 - 0.4\r\n\r\n";
    const char find[] = "good";

    /* Make the query */
    len = rt_strlen(query);
    len2 = sizeof(hostName) - 1;
    rt_memcpy(&query[len], hostName, len2);
    len += len2;

    len2 = sizeof(query2) - 1;
    rt_memcpy(&query[len], query2, len2);
    len += len2;

    len2 = rt_strlen(ip);
    rt_memcpy(&query[len], ip, len2);
    len += len2;

    len2 = sizeof(query3) - 1;
    rt_memcpy(&query[len], query3, len2);
    len += len2;

    len2 = sizeof(userPwdB64) - 1;
    rt_memcpy(&query[len], userPwdB64, len2);
    len += len2;

    len2 = sizeof(query4) - 1;
    rt_memcpy(&query[len], query4, len2);
    len += len2;

    query[len] = 0x0;
//  rt_kprintf("Query: %s\n", &query[100]);

    do
    {
#if defined(RT_LWIP_DNS)
        ret = netconn_gethostbyname("members.dyndns.org", &server_ip);
        if (ret != ERR_OK)
        {
            break;
        }
#else
        IP4_ADDR(&server_ip, 204,13,248,112);   // IP address of "members.dyndns.org"
#endif

        conn = netconn_new(NETCONN_TCP);
        if (conn == NULL)
        {
            break;
        }

        ret = netconn_connect(conn, &server_ip, 80);
        if (ret != ERR_OK)
        {
            break;
        }

        /* Send the query */
        ret = netconn_write(conn, query, len, 0);
        if (ret != ERR_OK)
        {
            break;
        }

        /* Get the response */
        buf = netconn_recv(conn);
        if (buf != NULL)
        {
            ret = netbuf_data(buf, (void **)&rq, &len);
            if (ret != ERR_OK)
            {
                break;
            }

            /* Find the result */
            rq = rt_strstr(rq, find);
            if (rq == RT_NULL)
            {
                break;
            }
//          rt_kprintf("[%s]\n", rq);
        }
        else
        {
            break;
        }

        netconn_delete(conn);
        netbuf_delete(buf);
        return RT_EOK;
    } while (0);

    netconn_delete(conn);
    netbuf_delete(buf);
    return -RT_ERROR;
}

void update_myip(char *ip)
{
    rt_kprintf("Update host, \"%s\", to new IP address %s: ", hostName, ip);

    if (update_ip(ip) != RT_EOK)
    {
        rt_kprintf("failed!\n");
        return;
    }

    rt_kprintf("succeeded.\n", ip);
}
FINSH_FUNCTION_EXPORT(update_myip, update DDNS with specified IP address.)

#endif /* RT_USING_FINSH */
#endif /* defined(EFM32_USING_ETH_UTILS) */

#endif /* defined(EFM32_USING_ETHERNET) */
/******************************************************************//**
 * @}
 ******************************************************************************/
