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
 * Date           Author            Notes
 * 2017-11-08     ZYH            the first version
 * 2018-5-30      Slyant         add all spi interface
 */

#include "board.h"
#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
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
//      hspi.Init.NSS = SPI_NSS_HARD_OUTPUT;
    }
    if(cfg->max_hz >= HAL_RCC_GetPCLK2Freq()/2)
    {
        hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
    }
    else if(cfg->max_hz >= HAL_RCC_GetPCLK2Freq()/4)
    {
        hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
    }
    else if(cfg->max_hz >= HAL_RCC_GetPCLK2Freq()/8)
    {
        hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
    }
    else if(cfg->max_hz >= HAL_RCC_GetPCLK2Freq()/16)
    {
        hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
    }
    else if(cfg->max_hz >= HAL_RCC_GetPCLK2Freq()/32)
    {
        hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
    }
    else if(cfg->max_hz >= HAL_RCC_GetPCLK2Freq()/64)
    {
        hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
    }
    else if(cfg->max_hz >= HAL_RCC_GetPCLK2Freq()/128)
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
    struct stm32_spi * hspi = (struct stm32_spi *)device->bus->parent.user_data;
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
    struct stm32_spi * hspi = (struct stm32_spi *)device->bus->parent.user_data;
    hspi->cfg = configuration;
    return stm32_spi_init(hspi->Instance, configuration);
}

const struct rt_spi_ops stm_spi_ops =
{
    .configure = spi_configure,
    .xfer = spixfer,
};

struct rt_spi_bus _spi_bus1,_spi_bus2,_spi_bus3,_spi_bus4,_spi_bus5,_spi_bus6;
struct stm32_spi _spi1,_spi2,_spi3,_spi4,_spi5,_spi6;
int stm32_spi_register_bus(SPI_TypeDef * SPIx,const char * name)
{
    struct rt_spi_bus * spi_bus;
    struct stm32_spi * spi;
    if(SPIx == SPI1)
    {
        spi_bus = &_spi_bus1;
        spi = &_spi1;
    }
#ifdef SPI2	
	else if(SPIx == SPI2)
    {
        spi_bus = &_spi_bus2;
        spi = &_spi2;
    }
#endif
#ifdef SPI3		
    else if(SPIx == SPI3){
        spi_bus = &_spi_bus3;
        spi = &_spi3;
    }
#endif
#ifdef SPI4		
	else if(SPIx == SPI4){
        spi_bus = &_spi_bus4;
        spi = &_spi4;
    }
#endif
#ifdef SPI5		
	else if(SPIx == SPI5){
        spi_bus = &_spi_bus5;
        spi = &_spi5;
    }
#endif
#ifdef SPI6		
	else if(SPIx == SPI6){
        spi_bus = &_spi_bus6;
        spi = &_spi6;
    }
#endif	
	else
    {
        return -1;
    }
    spi->Instance = SPIx;
    spi_bus->parent.user_data = spi;
    return rt_spi_bus_register(spi_bus, name, &stm_spi_ops);
}
//cannot be used before completion init
rt_err_t stm32_spi_bus_attach_device(rt_uint32_t pin,const char * bus_name,const char * device_name)
{
    struct rt_spi_device * spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);
    struct stm32_hw_spi_cs * cs_pin = (struct stm32_hw_spi_cs *)rt_malloc(sizeof(struct stm32_hw_spi_cs));
    RT_ASSERT(cs_pin != RT_NULL);
    cs_pin->pin = pin;
    rt_pin_mode(pin,PIN_MODE_OUTPUT);
    rt_pin_write(pin, 1);
    return rt_spi_bus_attach_device(spi_device, device_name, bus_name, (void *)cs_pin);
}

int stm32_hw_spi_init(void)
{
    int result = 0;
#ifdef RT_USING_SPI1
    result = stm32_spi_register_bus(SPI1,"spi1");
#endif
#ifdef RT_USING_SPI2
    result = stm32_spi_register_bus(SPI2,"spi2");
#endif
#ifdef RT_USING_SPI3
    result = stm32_spi_register_bus(SPI3,"spi3");
#endif
#ifdef RT_USING_SPI4
    result = stm32_spi_register_bus(SPI4,"spi4");
#endif
#ifdef RT_USING_SPI5
    result = stm32_spi_register_bus(SPI5,"spi5");
#endif
#ifdef RT_USING_SPI6
    result = stm32_spi_register_bus(SPI6,"spi6");
#endif	
    return result;
}
INIT_BOARD_EXPORT(stm32_hw_spi_init);

void HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle)
{

    GPIO_InitTypeDef GPIO_InitStruct;
    if(spiHandle->Instance==SPI1)
    {
        /* SPI1 clock enable */
        __HAL_RCC_SPI1_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**SPI1 GPIO Configuration    
        PA5     ------> SPI1_SCK
        PA6     ------> SPI1_MISO
        PA7     ------> SPI1_MOSI 
        */
        GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
#ifdef SPI2		
    else if(spiHandle->Instance==SPI2)
    {
        /* SPI2 clock enable */
        __HAL_RCC_SPI2_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();
        /**SPI2 GPIO Configuration    
        PB13     ------> SPI2_SCK
        PB14     ------> SPI2_MISO
        PB15     ------> SPI2_MOSI 
        */
        GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    }
#endif
#ifdef SPI3		
    else if(spiHandle->Instance==SPI3)
    {
        /* SPI3 clock enable */
        __HAL_RCC_SPI3_CLK_ENABLE();
        __HAL_RCC_GPIOC_CLK_ENABLE();
        /**SPI3 GPIO Configuration    
        PC10     ------> SPI3_SCK
        PC11     ------> SPI3_MISO
        PC12     ------> SPI3_MOSI 
        */
        GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    }
#endif
#ifdef SPI4	
    else if(spiHandle->Instance==SPI4)
    {
        /* SPI4 clock enable */
        __HAL_RCC_SPI4_CLK_ENABLE();
        __HAL_RCC_GPIOE_CLK_ENABLE();
        /**SPI4 GPIO Configuration    
        PE2     ------> SPI4_SCK
        PE5     ------> SPI4_MISO
        PE6     ------> SPI4_MOSI 
        */
        GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_5|GPIO_PIN_6;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF5_SPI4;
        HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
    }
#endif
#ifdef SPI5	
    else if(spiHandle->Instance==SPI5)
    {
        /* SPI5 clock enable */
        __HAL_RCC_SPI5_CLK_ENABLE();
        __HAL_RCC_GPIOF_CLK_ENABLE();
        /**SPI5 GPIO Configuration    
        PF7     ------> SPI5_SCK
        PF8     ------> SPI5_MISO
        PF9     ------> SPI5_MOSI 
        */
        GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF5_SPI5;
        HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
    }	
#endif
#ifdef SPI6	
    else if(spiHandle->Instance==SPI6)
    {
        /* SPI6 clock enable */
        __HAL_RCC_SPI6_CLK_ENABLE();
        __HAL_RCC_GPIOG_CLK_ENABLE();
        /**SPI6 GPIO Configuration    
        PG13     ------> SPI6_SCK
        PG12     ------> SPI6_MISO
        PG14     ------> SPI6_MOSI 
        */
        GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF5_SPI6;
        HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
    }	
#endif	
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{

    if(spiHandle->Instance==SPI1)
    {
        /* Peripheral clock disable */
        __HAL_RCC_SPI1_CLK_DISABLE();

        /**SPI1 GPIO Configuration    
        PA5     ------> SPI1_SCK
        PA6     ------> SPI1_MISO
        PA7     ------> SPI1_MOSI 
        */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
    }
#ifdef SPI2 	
    else if(spiHandle->Instance==SPI2)
    {
        /* Peripheral clock disable */
        __HAL_RCC_SPI2_CLK_DISABLE();

        /**SPI2 GPIO Configuration    
        PB13     ------> SPI2_SCK
        PB14     ------> SPI2_MISO
        PB15     ------> SPI2_MOSI 
        */
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);
    }
#endif
#ifdef SPI3	
    else if(spiHandle->Instance==SPI3)
    {
        /* Peripheral clock disable */
        __HAL_RCC_SPI3_CLK_DISABLE();

        /**SPI3 GPIO Configuration    
        PC10     ------> SPI3_SCK
        PC11     ------> SPI3_MISO
        PC12     ------> SPI3_MOSI 
        */
        HAL_GPIO_DeInit(GPIOC, GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12);
    }
#endif
#ifdef SPI4	
    else if(spiHandle->Instance==SPI4)
    {
        /* Peripheral clock disable */
        __HAL_RCC_SPI4_CLK_DISABLE();

        /**SPI3 GPIO Configuration    
        PE2     ------> SPI3_SCK
        PE5     ------> SPI3_MISO
        PE6     ------> SPI3_MOSI 
        */
        HAL_GPIO_DeInit(GPIOE, GPIO_PIN_2|GPIO_PIN_5|GPIO_PIN_6);
    }
#endif
#ifdef SPI5	
    else if(spiHandle->Instance==SPI5)
    {
        /* Peripheral clock disable */
        __HAL_RCC_SPI5_CLK_DISABLE();

        /**SPI3 GPIO Configuration    
        PF7     ------> SPI3_SCK
        PF8     ------> SPI3_MISO
        PF9     ------> SPI3_MOSI 
        */
        HAL_GPIO_DeInit(GPIOF, GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9);
    }
#endif
#ifdef SPI6	
    else if(spiHandle->Instance==SPI6)
    {
        /* Peripheral clock disable */
        __HAL_RCC_SPI6_CLK_DISABLE();

        /**SPI3 GPIO Configuration    
        PG12     ------> SPI3_SCK
        PG13     ------> SPI3_MISO
        PG14     ------> SPI3_MOSI 
        */
        HAL_GPIO_DeInit(GPIOG, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14);
    }
#endif
} 
#endif /*RT_USING_SPI*/
