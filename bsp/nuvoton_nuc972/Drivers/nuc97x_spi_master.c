/*
 * File      : nuc97x_spi_master.c
 * This file is part of RT-Thread RTOS
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/05/28     Urey         first implementation
 */
#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "board.h"
#include "nuc97x.h"

static UINT32 SPI_SetSpeed(SPI_TypeDef* SPIx,UINT32 uSpeed)
{
    UINT16 div ;

    div = (UINT16)(SPI_INPUT_CLOCK / (2 * uSpeed)) - 1;
    SPIx->DIVIDER = div;

    return ( SPI_INPUT_CLOCK /  (2*(div+1)));
}

UINT32 SPI_Read(SPI_TypeDef* SPIx,UINT8 buff_id)
{
    UINT32 result = 0;

    assert_param(IS_SPI_ALL_PERIPH(SPIx));

    switch (buff_id)
    {
        case 0:
            result = SPIx->TX0_RX0;
            break;
        case 1:
            result = SPIx->TX1_RX1;
            break;
        case 2:
            result = SPIx->TX2_RX2;
            break;
        case 3:
            result = SPIx->TX3_RX3;
            break;
    }
    return result;
}

VOID SPI_Write(SPI_TypeDef* SPIx,UINT8 buff_id,UINT32 dat)
{
    assert_param(IS_SPI_ALL_PERIPH(SPIx));

    switch (buff_id)
    {
        case 0:
            SPIx->TX0_RX0 = dat;
            break;
        case 1:
            SPIx->TX1_RX1 = dat;
            break;
        case 2:
            SPIx->TX2_RX2 = dat;
            break;
        case 3:
            SPIx->TX3_RX3 = dat;
            break;
    }
}

void SPI_Init(SPI_TypeDef* SPIx)
{
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    if(SPIx == SPI0)
    {
        /* enable clock */
        outpw(REG_CLK_PCLKEN1, inpw(REG_CLK_PCLKEN1) | 0x10);

        /* Configure multi function pins to SPI0: CLK MISO MOSI */
        outpw(REG_SYS_GPB_MFPL, (inpw(REG_SYS_GPB_MFPL) & ~(0x0FL << 28)) | (0x0BL << 28));
        outpw(REG_SYS_GPB_MFPH, (inpw(REG_SYS_GPB_MFPH) & ~(0xFFL <<  0)) | (0xBBL <<  0));
    }
    else if(SPIx == SPI1)
    {
        /* enable clock */
        outpw(REG_CLK_PCLKEN1, inpw(REG_CLK_PCLKEN1) | 0x20);

        /* Configure multi function pins to SPI1 */
#ifdef SPI1_USING_GPIOB
        outpw(REG_SYS_GPB_MFPH, (inpw(REG_SYS_GPB_MFPH) & ~(0xFFF << 20)) | (0xBBB << 20));
#else
        outpw(REG_SYS_GPI_MFPL, (inpw(REG_SYS_GPI_MFPL) & ~(0xFF << 24)) | (0xBB << 24));
        outpw(REG_SYS_GPI_MFPH, (inpw(REG_SYS_GPI_MFPH) & ~(0x0F <<  0)) | (0x0B <<  0));
#endif
    }

}


INT32 SPI_GetBusy(SPI_TypeDef* SPIx)
{
    assert_param(IS_SPI_ALL_PERIPH(SPIx));

    if(SPIx->CNTRL & 0x01)
        return 1;
    else
        return 0;
}


INT32 SPI_Control(SPI_TypeDef* SPIx,UINT32 cmd, UINT32 arg)
{
    assert_param(IS_SPI_ALL_PERIPH(SPIx));

    switch (cmd)
    {
        case SPI_IOC_TRIGGER:
            SPIx->CNTRL = SPIx->CNTRL | 0x01;
            break;

        case SPI_IOC_SET_INTERRUPT:
            if (arg == SPI_ENABLE_INTERRUPT)
                SPIx->CNTRL = SPIx->CNTRL | (0x1 << 17);
            else
                SPIx->CNTRL = SPIx->CNTRL & ~(0x1 << 17);
            break;

        case SPI_IOC_SET_SPEED:
            SPI_SetSpeed(SPIx,arg);
            break;

        case SPI_IOC_SET_DUAL_QUAD_MODE:
            if (arg == SPI_DISABLE_DUAL_QUAD)
            {
                SPIx->CNTRL = SPIx->CNTRL & ~(0x3 << 21);
                break;
            }

            if (arg == SPI_DUAL_MODE)
                SPIx->CNTRL = (SPIx->CNTRL & ~(0x3 << 21)) | (0x1 << 22);
            else
                SPIx->CNTRL = (SPIx->CNTRL & ~(0x3 << 21)) | (0x1 << 21);
            break;
        case SPI_IOC_SET_DUAL_QUAD_DIR:
            if (arg == SPI_DUAL_QUAD_INPUT)

                SPIx->CNTRL = SPIx->CNTRL & ~(0x1 << 20);
            else
                SPIx->CNTRL = SPIx->CNTRL | (0x1 << 20);
            break;

        case SPI_IOC_SET_LSB_MSB:
            if (arg == SPI_MSB)
                SPIx->CNTRL = SPIx->CNTRL & ~(0x1 << 10);
            else
                SPIx->CNTRL = SPIx->CNTRL | (0x1 << 10);
            break;

        case SPI_IOC_SET_TX_NUM:
            if (arg < 4)
                SPIx->CNTRL = (SPIx->CNTRL & ~(0x3 << 8)) | (arg << 8);
            else
                return SPI_ERR_ARG;
            break;

        case SPI_IOC_SET_TX_BITLEN:
            if (arg < 32)
                SPIx->CNTRL = (SPIx->CNTRL & ~(0x1f << 3)) | (arg << 3);
            else
                return SPI_ERR_ARG;
            break;

        case SPI_IOC_SET_MODE:
            if (arg > SPI_MODE_3)
                return SPI_ERR_ARG;

            if (arg == SPI_MODE_0)
                SPIx->CNTRL = (SPIx->CNTRL & ~((0x3 << 1) | (1UL << 31))) | (1 << 2);
            else if (arg == SPI_MODE_1)
                SPIx->CNTRL = (SPIx->CNTRL & ~((0x3 << 1) | (1UL << 31))) | (1 << 1);
            else if (arg == SPI_MODE_2)
                SPIx->CNTRL = (SPIx->CNTRL & ~((0x3 << 1) | (1UL << 31))) | ((1UL << 31) | (1 << 2));
            else
                SPIx->CNTRL = (SPIx->CNTRL & ~((0x3 << 1) | (1UL << 31))) | ((1UL << 31) | (1 << 1));
            break;

        case SPI_IOC_ENABLE_SS:
            if (arg == SPI_SS_SS0)
                SPIx->SSR = (SPIx->SSR & ~(0x3)) | 0x1;
            else if (arg == SPI_SS_SS1)
                SPIx->SSR = (SPIx->SSR & ~(0x3)) | 0x2;
            else if (arg == SPI_SS_BOTH)
                SPIx->SSR = (SPIx->SSR & ~(0x3)) | 0x3;
            else
                return SPI_ERR_ARG;
            break;

        case SPI_IOC_DISABLE_SS:
            if (arg == SPI_SS_SS0)
                SPIx->SSR = SPIx->SSR & ~(0x1);
            else if (arg == SPI_SS_SS1)
                SPIx->SSR = SPIx->SSR & ~(0x2);
            else if (arg == SPI_SS_BOTH)
                SPIx->SSR = SPIx->SSR & ~(0x3);
            else
                return SPI_ERR_ARG;
            break;

        case SPI_IOC_SET_AUTOSS:
            if (arg == SPI_DISABLE_AUTOSS)
                SPIx->SSR = SPIx->SSR & ~(0x1 << 3);
            else
                SPIx->SSR = SPIx->SSR | (0x1 << 3);
            break;

        case SPI_IOC_SET_SS_ACTIVE_LEVEL:
            if (arg == SPI_SS_ACTIVE_LOW)
                SPIx->SSR = SPIx->SSR & ~(0x1 << 2);
            else
                SPIx->SSR = SPIx->SSR | (0x1 << 2);

            break;
        case SPI_IOC_CLR_INTERRUPT:
            SPIx->CNTRL = SPIx->CNTRL | (0x1 << 16);
            break;
        default:
            return SPI_ERR_ARG;
    }

    return SPI_NO_ERR;
}





#define SPI_USE_4REG
//#define SPI_DEBUG

static rt_err_t nuc970_spi_configure(struct rt_spi_device* device, struct rt_spi_configuration* configuration);
static rt_uint32_t nuc970_spi_xfer(struct rt_spi_device* device, struct rt_spi_message* message);

struct nuc970_spi_bus
{
    struct rt_spi_bus parent;
    SPI_TypeDef * SPIx;
    int vector;
    struct rt_completion complete;
};

const struct rt_spi_ops nuc970_spi_ops =
{
    .configure  = nuc970_spi_configure,
    .xfer       = nuc970_spi_xfer,
};

#ifdef BOARD_USING_SPI0
static struct nuc970_spi_bus nuc970_spi0 =
{
    .SPIx = SPI0,
    .vector = SPI0_IRQn,
};
#endif

void nuc970_spi_isr(int vector, void *param)
{
    struct nuc970_spi_bus *spi_bus = (struct nuc970_spi_bus *)param;

    SPI_Control(spi_bus->SPIx, SPI_IOC_CLR_INTERRUPT, 0);

    rt_completion_done(&spi_bus->complete);
}

int rt_hw_spi_bus_init(void)
{
#ifdef BOARD_USING_SPI0
    {
        SPI_Init(nuc970_spi0.SPIx);
        SPI_Control(nuc970_spi0.SPIx, SPI_IOC_SET_INTERRUPT, SPI_ENABLE_INTERRUPT);

        /* USE soft nSS */
        outpw(REG_SYS_GPB_MFPL, (inpw(REG_SYS_GPB_MFPL) & ~(0x0F << 24)) | (0x00 << 24));

        /* Register SPI0 bus */
        rt_spi_bus_register(&nuc970_spi0.parent, "spi0", &nuc970_spi_ops);

        /* Register interrupt */
        rt_hw_interrupt_install(SPI0_IRQn, nuc970_spi_isr, &nuc970_spi0, "spi0ISR");

        /* Set the irq and irq trigger level for SPI0 */
        rt_hw_interrupt_set_priority(SPI0_IRQn, IRQ_LEVEL_2);
        rt_hw_interrupt_set_type(SPI0_IRQn, HIGH_LEVEL_SENSITIVE);

        rt_hw_interrupt_umask(SPI0_IRQn);
    }
#endif
}
INIT_PREV_EXPORT(rt_hw_spi_bus_init);

static rt_err_t nuc970_spi_configure(struct rt_spi_device* device, struct rt_spi_configuration* configuration)
{
    struct nuc970_spi_bus * spi_bus = (struct nuc970_spi_bus *) device->bus;

    /* baudrate */
    SPI_Control(spi_bus->SPIx, SPI_IOC_SET_SPEED, configuration->max_hz);

    /* data_width */
    if (configuration->data_width <= 8)
        SPI_Control(spi_bus->SPIx, SPI_IOC_SET_TX_BITLEN, 8);
    else if (configuration->data_width <= 16)
        SPI_Control(spi_bus->SPIx, SPI_IOC_SET_TX_BITLEN, 16);
    else
        return RT_EIO;

    /* mode */
    switch (configuration->mode & RT_SPI_MODE_3)
    {
        case RT_SPI_MODE_0:
            SPI_Control(spi_bus->SPIx, SPI_IOC_SET_MODE, SPI_MODE_0);
            break;
        case RT_SPI_MODE_1:
            SPI_Control(spi_bus->SPIx, SPI_IOC_SET_MODE, SPI_MODE_1);
            break;
        case RT_SPI_MODE_2:
            SPI_Control(spi_bus->SPIx, SPI_IOC_SET_MODE, SPI_MODE_2);
            break;
        case RT_SPI_MODE_3:
            SPI_Control(spi_bus->SPIx, SPI_IOC_SET_MODE, SPI_MODE_3);
            break;
        default:
            return -RT_EIO;
    }

    /* MSB or LSB */
    if(configuration->mode & RT_SPI_MSB)
        SPI_Control(spi_bus->SPIx,SPI_IOC_SET_LSB_MSB,SPI_MSB);
    else
        SPI_Control(spi_bus->SPIx,SPI_IOC_SET_LSB_MSB,SPI_LSB);

    return RT_EOK;
}

static rt_uint32_t nuc970_spi_xfer(struct rt_spi_device* device, struct rt_spi_message* message)
{
    struct nuc970_spi_bus * spi_bus = (struct nuc970_spi_bus *) device->bus;

    struct nuc970_spi_cs *spi_cs = device->parent.user_data;
    rt_uint32_t size = message->length;
    rt_uint32_t idx = 0;

    /* start trans */
    {
        const rt_uint8_t * send_ptr = message->send_buf;
        rt_uint8_t * recv_ptr = message->recv_buf;

#ifdef SPI_DEBUG
        rt_kprintf("[SPI] send :\n");
        if(send_ptr)
        {
            for (idx = 0; idx < message->length; ++idx) {
                rt_kprintf(" %02x",send_ptr[idx]);
                if((idx % 8 == 0) && (idx != 0))
                    rt_kprintf("\n");
            }
            rt_kprintf("\n");
        }
        else
            rt_kprintf(" NULL :\n");
#endif
        /* take CS */
        if (message->cs_take)
        {
            GPIO_ClrBit((GPIO_PORT) spi_cs->GPIOx, spi_cs->PINx);
        }

        while (idx < size)
        {
#ifdef SPI_USE_4REG
            if(size - idx >= 4)
            {
                SPI_Control(spi_bus->SPIx,SPI_IOC_SET_TX_NUM,3);
                if(send_ptr)
                {
                    SPI_Write(spi_bus->SPIx,0,send_ptr[idx + 0]);
                    SPI_Write(spi_bus->SPIx,1,send_ptr[idx + 1]);
                    SPI_Write(spi_bus->SPIx,2,send_ptr[idx + 2]);
                    SPI_Write(spi_bus->SPIx,3,send_ptr[idx + 3]);
                }
                else
                {
                    SPI_Write(spi_bus->SPIx,0,0xFF);
                    SPI_Write(spi_bus->SPIx,1,0xFF);
                    SPI_Write(spi_bus->SPIx,2,0xFF);
                    SPI_Write(spi_bus->SPIx,3,0xFF);
                }
            }
            else
#endif
            {
                SPI_Control(spi_bus->SPIx,SPI_IOC_SET_TX_NUM,0);
                if(send_ptr)
                    SPI_Write(spi_bus->SPIx,0,send_ptr[idx + 0]);
                else
                    SPI_Write(spi_bus->SPIx,0,0xFF);
            }

            //start...
            rt_completion_init(&spi_bus->complete);
            //wait
            SPI_Control(spi_bus->SPIx,SPI_IOC_TRIGGER,0);
            if(RT_EOK != rt_completion_wait(&spi_bus->complete,RT_WAITING_FOREVER))
                return 0;
//            while(spi_bus->SPIx->CNTRL & 0x01);

#ifdef SPI_USE_4REG
            if(size - idx >= 4)
            {
                if(recv_ptr)
                {
                    recv_ptr[idx + 0] = SPI_Read(spi_bus->SPIx,0);
                    recv_ptr[idx + 1] = SPI_Read(spi_bus->SPIx,1);
                    recv_ptr[idx + 2] = SPI_Read(spi_bus->SPIx,2);
                    recv_ptr[idx + 3] = SPI_Read(spi_bus->SPIx,3);
                }

                idx += 4;
            }
            else
#endif
            {
                if(recv_ptr)
                {
                    recv_ptr[idx + 0] = SPI_Read(spi_bus->SPIx,0);
                }

                idx += 1;
            }
        }

        if(message->cs_release)
        {
            GPIO_SetBit((GPIO_PORT) spi_cs->GPIOx, spi_cs->PINx);
        }

#ifdef SPI_DEBUG
        rt_kprintf("[SPI] recv :\n");
        if(recv_ptr)
        {
            for (idx = 0; idx < message->length; ++idx)
            {
                rt_kprintf(" %02x",recv_ptr[idx]);
                if((idx % 8 == 0) && (idx != 0))
                    rt_kprintf("\n");
            }
            rt_kprintf("\n");
        }
        else
            rt_kprintf(" NULL :\n");
#endif
    }

    return message->length;
}

