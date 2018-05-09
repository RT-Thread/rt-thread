/*
 * File      : drv_spi.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2016-09-02     Aubr.Cool      the first version
 */

#include <stm32l0xx.h>
#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#define SPIRXEVENT 0x01
#define SPITXEVENT 0x02

#ifdef RT_USING_SPI

#define SPITIMEOUT 2
#define SPICRCEN 0

struct stm32_hw_spi;

typedef void(*spiirqapi)(struct stm32_hw_spi *hspi);

struct stm32_hw_spi {
    SPI_TypeDef* Instance;
    struct rt_spi_configuration* cfg;
};
struct stm32_spi {
    SPI_TypeDef* spi_device;
    struct stm32_hw_spi *data;
};
struct stm32_hw_spi_cs {
    rt_uint32_t pin;
};
static rt_err_t stml0xx_spi_init(SPI_TypeDef * spix, struct rt_spi_configuration * cfg)
{
  SPI_HandleTypeDef hspi;
  hspi.Instance = spix;

  if(cfg->mode & RT_SPI_SLAVE) {
    hspi.Init.Mode = SPI_MODE_SLAVE;
  } else {
    hspi.Init.Mode = SPI_MODE_MASTER;
  }
  if(cfg->mode & RT_SPI_3WIRE) {
    hspi.Init.Direction = SPI_DIRECTION_1LINE;
  } else {
    hspi.Init.Direction = SPI_DIRECTION_2LINES;
  }
  if(cfg->data_width == 8) {
    hspi.Init.DataSize = SPI_DATASIZE_8BIT;
  } else if(cfg->data_width == 16) {
    hspi.Init.DataSize = SPI_DATASIZE_16BIT;
  } else {
    return RT_EIO;
  }
  if(cfg->mode & RT_SPI_CPHA) {
      hspi.Init.CLKPhase = SPI_PHASE_2EDGE;
  } else {
      hspi.Init.CLKPhase = SPI_PHASE_1EDGE;
  }
  if(cfg->mode & RT_SPI_CPOL) {
      hspi.Init.CLKPolarity = SPI_POLARITY_HIGH;
  } else {
      hspi.Init.CLKPolarity = SPI_POLARITY_LOW;
  }
  if(cfg->mode & RT_SPI_NO_CS) {
      hspi.Init.NSS = SPI_NSS_SOFT;
  } else {
      hspi.Init.NSS = SPI_NSS_HARD_OUTPUT;
  }
  hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  if(cfg->mode & RT_SPI_MSB) {
    hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
  } else {
    hspi.Init.FirstBit = SPI_FIRSTBIT_LSB;
  }
  hspi.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi.Init.CRCPolynomial = 7;
  if (HAL_SPI_Init(&hspi) != HAL_OK)
  {
    return RT_EIO;
  }
  __HAL_SPI_ENABLE(&hspi);
  return RT_EOK;
}
#define SPISTEP(datalen)   (((datalen) == 8) ? 1 : 2)
#define SPISEND_1(reg, ptr, datalen) \
    do {\
        if(datalen == 8) { \
            (reg) = *(rt_uint8_t *)(ptr); \
        } else { \
            (reg) = *(rt_uint16_t *) (ptr); \
        } \
    } while(0)
#define SPIRECV_1(reg, ptr, datalen) \
    do {\
        if(datalen == 8) { \
            *(rt_uint8_t *)(ptr) = (reg); \
        } else { \
            *(rt_uint16_t *) (ptr) = reg; \
        } \
    } while(0)

static rt_err_t spitxrx1b(struct stm32_hw_spi *hspi, void *rcvb, const void *sndb)
{
    rt_uint32_t padrcv = 0;
    rt_uint32_t padsnd = 0xFF;
    if(! rcvb && !sndb) {
        return RT_ERROR;
    }
    if(!rcvb) {
        rcvb = &padrcv;
    }
    if(!sndb) {
        sndb = &padsnd;
    }
    while(__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_TXE) == RESET);
    SPISEND_1(hspi->Instance->DR, sndb, hspi->cfg->data_width);
    while(__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_RXNE) == RESET);
    SPIRECV_1(hspi->Instance->DR, rcvb, hspi->cfg->data_width);
    return RT_EOK;
}
static rt_uint32_t spixfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    rt_err_t res;
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(device->bus->parent.user_data != RT_NULL);
    struct stm32_spi* spix;
    spix = (struct stm32_spi *)device->bus->parent.user_data;
    struct stm32_hw_spi *hspi = spix->data;
    struct stm32_hw_spi_cs * cs = device->parent.user_data;

    if(message->cs_take) {
        rt_pin_write(cs->pin, 0);
    }
    const rt_uint8_t *sndb = message->send_buf;
    rt_uint8_t *rcvb = message->recv_buf;
    rt_int32_t length = message->length;
    while(length) {
        res = spitxrx1b(hspi, rcvb, sndb);
        if(rcvb) {
            rcvb += SPISTEP(hspi->cfg->data_width);
        }
        if(sndb) {
            sndb += SPISTEP(hspi->cfg->data_width);
        }
        if(res != RT_EOK) {
            break;
        }
        length--;
    }
    /* Wait until Busy flag is reset before disabling SPI */
    while(__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_BSY) == SET);
    if(message->cs_release) {
        rt_pin_write(cs->pin, 1);
    }
    return message->length - length;
}
#ifdef RT_USING_SPI1

static struct stm32_hw_spi spi1hwdata = {
    .Instance = SPI1,
};
const static struct stm32_spi spi1 = {
    SPI1,
    &spi1hwdata,
};
const static struct stm32_hw_spi_cs stm32_spi1_cs = {
    SPI1PINNSS,
};
rt_err_t spi1configure(struct rt_spi_device *device,
         struct rt_spi_configuration *configuration)
{
    spi1hwdata.cfg = configuration;
    return stml0xx_spi_init(spi1.spi_device, configuration);
}
const struct rt_spi_ops stm_spi_ops1 =
{
    .configure = spi1configure,
    .xfer = spixfer,
};
static struct rt_spi_bus stm_spi_bus1 = {
    .parent = {
        .user_data = (void *)&spi1,
    },
};

#endif /*RT_USING_SPI1*/
#ifdef RT_USING_SPI2

static struct stm32_hw_spi spi2hwdata = {
    .Instance = SPI2,
};
const struct stm32_spi spi2 = {
    SPI2,
    &spi2hwdata,
};
rt_err_t spi2configure(struct rt_spi_device *device,
         struct rt_spi_configuration *configuration)
{
    spi2hwdata.cfg = configuration;
    return stml0xx_spi_init(spi2.spi_device, configuration);
}
const struct rt_spi_ops stm_spi_ops2 =
{
    .configure = spi2configure,
    .xfer = spixfer,
};
const static struct stm32_hw_spi_cs stm32_spi2_cs = {
    SPI2PINNSS,
};
static struct rt_spi_bus stm_spi_bus2 = {
    .parent = {
        .user_data = (void *)&spi2,
    },
};

#endif /*RT_USING_SPI2*/
static void RCC_Configuration(void)
{
#ifdef RT_USING_SPI1
    __HAL_RCC_SPI1_CLK_ENABLE();
#endif /*RT_USING_SPI1*/
#ifdef RT_USING_SPI2
    __HAL_RCC_SPI2_CLK_ENABLE();
#endif /*RT_USING_SPI2*/
}

static void GPIO_Configuration(void)
{
    #ifdef RT_USING_SPI1
    {
        /**SPI1 GPIO Configuration  **/
        rt_uint32_t mode;
        mode = (GPIO_AF0_SPI1 << 8) | GPIO_MODE_AF_PP;
        stm32_pin_mode_early(SPI1PINSCK, mode);
        stm32_pin_mode_early(SPI1PINMISO, mode);
        stm32_pin_mode_early(SPI1PINMOSI, mode);
    }
    #endif /*RT_USING_SPI1*/
    #ifdef RT_USING_SPI2
    #endif /*RT_USING_SPI1*/
}

int stm32_hw_spi_init(void)
{
    int result1 = RT_EOK, result2 = RT_EOK;
    RCC_Configuration();
    GPIO_Configuration();
    #ifdef RT_USING_SPI1
    {
        result1 = rt_spi_bus_register(&stm_spi_bus1, "spi1", &stm_spi_ops1);
        static struct rt_spi_device spi_device;
        rt_uint32_t mode = GPIO_MODE_OUTPUT_PP;
        stm32_pin_mode_early(SPI1PINNSS, mode);
        stm32_pin_write_early(SPI1PINNSS, 1);
        rt_spi_bus_attach_device(&spi_device, "spi10", "spi1", (void *)&stm32_spi1_cs);
    }
    #endif /*RT_USING_SPI1*/
    #ifdef RT_USING_SPI2
    {
        result2 = rt_spi_bus_register(&stm_spi_bus2, "spi2", &stm_spi_ops1);
        static struct rt_spi_device spi_device;
        rt_uint32_t mode = GPIO_MODE_OUTPUT_PP;
        stm32_pin_mode_early(SPI2PINNSS, mode);
        stm32_pin_write_early(SPI2PINNSS, 1);
        rt_spi_bus_attach_device(&spi_device, "spi20", "spi2", (void *)&stm32_spi2_cs);
    }
    #endif /*RT_USING_SPI2*/
    return result1 | result2;
}
INIT_BOARD_EXPORT(stm32_hw_spi_init);

#endif /*RT_USING_SPI*/
