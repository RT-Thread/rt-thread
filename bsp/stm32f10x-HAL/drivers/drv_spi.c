/*
 * File      : dev_gpio.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author            Notes
 * 2017-10-20     ZYH            the first version
 * 2017-11-35     ZYH            update to 3.0.0
 */

#include <board.h>
#include <drv_spi.h>
#ifdef RT_USING_SPI
#define SPIRXEVENT 0x01
#define SPITXEVENT 0x02
#define SPITIMEOUT 2
#define SPICRCEN 0
struct stm32_hw_spi_cs
{
    rt_uint32_t pin;
};

struct stm32_spi
{
    SPI_TypeDef *Instance;
    struct rt_spi_configuration *cfg;
};

static rt_err_t stm32_spi_init(SPI_TypeDef *spix, struct rt_spi_configuration *cfg)
{
    SPI_HandleTypeDef hspi;
    hspi.Instance = spix;
    if (cfg->mode & RT_SPI_SLAVE)
    {
        hspi.Init.Mode = SPI_MODE_SLAVE;
    }
    else
    {
        hspi.Init.Mode = SPI_MODE_MASTER;
    }
    if (cfg->mode & RT_SPI_3WIRE)
    {
        hspi.Init.Direction = SPI_DIRECTION_1LINE;
    }
    else
    {
        hspi.Init.Direction = SPI_DIRECTION_2LINES;
    }
    if (cfg->data_width == 8)
    {
        hspi.Init.DataSize = SPI_DATASIZE_8BIT;
    }
    else if (cfg->data_width == 16)
    {
        hspi.Init.DataSize = SPI_DATASIZE_16BIT;
    }
    else
    {
        return RT_EIO;
    }
    if (cfg->mode & RT_SPI_CPHA)
    {
        hspi.Init.CLKPhase = SPI_PHASE_2EDGE;
    }
    else
    {
        hspi.Init.CLKPhase = SPI_PHASE_1EDGE;
    }
    if (cfg->mode & RT_SPI_CPOL)
    {
        hspi.Init.CLKPolarity = SPI_POLARITY_HIGH;
    }
    else
    {
        hspi.Init.CLKPolarity = SPI_POLARITY_LOW;
    }
    if (cfg->mode & RT_SPI_NO_CS)
    {
        hspi.Init.NSS = SPI_NSS_SOFT;
    }
    else
    {
        hspi.Init.NSS = SPI_NSS_SOFT;
//        hspi.Init.NSS = SPI_NSS_HARD_OUTPUT;
    }
    if (cfg->max_hz >= HAL_RCC_GetPCLK2Freq() / 2)
    {
        hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
    }
    else if (cfg->max_hz >= HAL_RCC_GetPCLK2Freq() / 4)
    {
        hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
    }
    else if (cfg->max_hz >= HAL_RCC_GetPCLK2Freq() / 8)
    {
        hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
    }
    else if (cfg->max_hz >= HAL_RCC_GetPCLK2Freq() / 16)
    {
        hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
    }
    else if (cfg->max_hz >= HAL_RCC_GetPCLK2Freq() / 32)
    {
        hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
    }
    else if (cfg->max_hz >= HAL_RCC_GetPCLK2Freq() / 64)
    {
        hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
    }
    else if (cfg->max_hz >= HAL_RCC_GetPCLK2Freq() / 128)
    {
        hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
    }
    else
    {
        /*  min prescaler 256 */
        hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
    }
    if (cfg->mode & RT_SPI_MSB)
    {
        hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
    }
    else
    {
        hspi.Init.FirstBit = SPI_FIRSTBIT_LSB;
    }
    hspi.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi.Init.CRCPolynomial = 7;
    hspi.State = HAL_SPI_STATE_RESET;
    if (HAL_SPI_Init(&hspi) != HAL_OK)
    {
        return RT_EIO;
    }
    __HAL_SPI_ENABLE(&hspi);
    return RT_EOK;
}

#define SPISTEP(datalen) (((datalen) == 8) ? 1 : 2)
#define SPISEND_1(reg, ptr, datalen)       \
    do                                     \
    {                                      \
        if (datalen == 8)                  \
        {                                  \
            (reg) = *(rt_uint8_t *)(ptr);  \
        }                                  \
        else                               \
        {                                  \
            (reg) = *(rt_uint16_t *)(ptr); \
        }                                  \
    } while (0)
#define SPIRECV_1(reg, ptr, datalen)      \
    do                                    \
    {                                     \
        if (datalen == 8)                 \
        {                                 \
            *(rt_uint8_t *)(ptr) = (reg); \
        }                                 \
        else                              \
        {                                 \
            *(rt_uint16_t *)(ptr) = reg;  \
        }                                 \
    } while (0)

static rt_err_t spitxrx1b(struct stm32_spi *hspi, void *rcvb, const void *sndb)
{
    rt_uint32_t padrcv = 0;
    rt_uint32_t padsnd = 0xFF;
    if (!rcvb && !sndb)
    {
        return RT_ERROR;
    }
    if (!rcvb)
    {
        rcvb = &padrcv;
    }
    if (!sndb)
    {
        sndb = &padsnd;
    }
    while (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_TXE) == RESET)
        ;
    SPISEND_1(hspi->Instance->DR, sndb, hspi->cfg->data_width);
    while (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_RXNE) == RESET)
        ;
    SPIRECV_1(hspi->Instance->DR, rcvb, hspi->cfg->data_width);
    return RT_EOK;
}

static rt_uint32_t spixfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    rt_err_t res;
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(device->bus->parent.user_data != RT_NULL);
    struct stm32_spi *hspi = (struct stm32_spi *)device->bus->parent.user_data;
    struct stm32_hw_spi_cs *cs = device->parent.user_data;
    if (message->cs_take)
    {
        rt_pin_write(cs->pin, 0);
    }
    const rt_uint8_t *sndb = message->send_buf;
    rt_uint8_t *rcvb = message->recv_buf;
    rt_int32_t length = message->length;
    while (length)
    {
        res = spitxrx1b(hspi, rcvb, sndb);
        if (rcvb)
        {
            rcvb += SPISTEP(hspi->cfg->data_width);
        }
        if (sndb)
        {
            sndb += SPISTEP(hspi->cfg->data_width);
        }
        if (res != RT_EOK)
        {
            break;
        }
        length--;
    }
    /* Wait until Busy flag is reset before disabling SPI */
    while (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_BSY) == SET)
        ;
    if (message->cs_release)
    {
        rt_pin_write(cs->pin, 1);
    }
    return message->length - length;
}

rt_err_t spi_configure(struct rt_spi_device *device,
                       struct rt_spi_configuration *configuration)
{
    struct stm32_spi *hspi = (struct stm32_spi *)device->bus->parent.user_data;
    hspi->cfg = configuration;
    return stm32_spi_init(hspi->Instance, configuration);
}

const struct rt_spi_ops stm_spi_ops =
{
    .configure = spi_configure,
    .xfer = spixfer,
};

struct rt_spi_bus _spi_bus1, _spi_bus2;
struct stm32_spi _spi1, _spi2;
int stm32_spi_register_bus(SPI_TypeDef *SPIx, const char *name)
{
    struct rt_spi_bus *spi_bus;
    struct stm32_spi *spi;
    if (SPIx == SPI1)
    {
        spi_bus = &_spi_bus1;
        spi = &_spi1;
    }
    else if (SPIx == SPI2)
    {
        spi_bus = &_spi_bus2;
        spi = &_spi2;
    }
    else
    {
        return -1;
    }
    spi->Instance = SPIx;
    spi_bus->parent.user_data = spi;
    return rt_spi_bus_register(spi_bus, name, &stm_spi_ops);
}

rt_err_t stm32_spi_bus_attach_device(rt_uint32_t pin, const char *bus_name, const char *device_name)
{
    struct rt_spi_device *spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);
    struct stm32_hw_spi_cs *cs_pin = (struct stm32_hw_spi_cs *)rt_malloc(sizeof(struct stm32_hw_spi_cs));
    RT_ASSERT(cs_pin != RT_NULL);
    cs_pin->pin = pin;
    rt_pin_mode(pin, PIN_MODE_OUTPUT);
    rt_pin_write(pin, 1);
    return rt_spi_bus_attach_device(spi_device, device_name, bus_name, (void *)cs_pin);
}

int stm32_hw_spi_init(void)
{
    int result = 0;
#ifdef RT_USING_SPI1
    result = stm32_spi_register_bus(SPI1, "spi1");
#endif
#ifdef RT_USING_SPI2
    result = stm32_spi_register_bus(SPI2, "spi2");
#endif
    return result;
}
INIT_BOARD_EXPORT(stm32_hw_spi_init);

void HAL_SPI_MspInit(SPI_HandleTypeDef *spiHandle)
{

    GPIO_InitTypeDef GPIO_InitStruct;
    if (spiHandle->Instance == SPI1)
    {
        /* SPI1 clock enable */
        __HAL_RCC_SPI1_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**SPI1 GPIO Configuration
        PA5     ------> SPI1_SCK
        PA6     ------> SPI1_MISO
        PA7     ------> SPI1_MOSI
        */
        GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_7;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_6;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
    else if (spiHandle->Instance == SPI2)
    {
        /* SPI2 clock enable */
        __HAL_RCC_SPI2_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();
        /**SPI2 GPIO Configuration
        PB13     ------> SPI2_SCK
        PB14     ------> SPI2_MISO
        PB15     ------> SPI2_MOSI
        */
        GPIO_InitStruct.Pin = GPIO_PIN_13 | GPIO_PIN_15;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_14;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    }
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef *spiHandle)
{

    if (spiHandle->Instance == SPI1)
    {
        /* Peripheral clock disable */
        __HAL_RCC_SPI1_CLK_DISABLE();

        /**SPI1 GPIO Configuration
        PA5     ------> SPI1_SCK
        PA6     ------> SPI1_MISO
        PA7     ------> SPI1_MOSI
        */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
    }
    else if (spiHandle->Instance == SPI2)
    {
        /* Peripheral clock disable */
        __HAL_RCC_SPI2_CLK_DISABLE();

        /**SPI2 GPIO Configuration
        PB13     ------> SPI2_SCK
        PB14     ------> SPI2_MISO
        PB15     ------> SPI2_MOSI
        */
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
    }
}
#endif /*RT_USING_SPI*/
