/*
 * File      : drv_spi_bus.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2013, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-03-27     Liuguang     the first version.
 */
 
#include "drv_spi_bus.h" 

#include "fsl_common.h" 
#include "fsl_iomuxc.h" 
#include "fsl_lpspi.h" 

#ifdef RT_USING_SPI

#define LPSPI_CLK_SOURCE         (1U)
#define LPSPI_CLK_SOURCE_DIVIDER (7U)

#if defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL
    #error "Please don't define 'FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL'!"
#endif

struct rt1050_spi
{
    LPSPI_Type *base;
    struct rt_spi_configuration *cfg;
};

struct rt1050_hw_spi_cs
{
    rt_uint32_t pin;
};

static uint32_t rt1050_get_lpspi_freq(void)
{
    uint32_t freq = 0;

    /* CLOCK_GetMux(kCLOCK_LpspiMux):
       00b: derive clock from PLL3 PFD1 720M 
       01b: derive clock from PLL3 PFD0 720M 
       10b: derive clock from PLL2      528M 
       11b: derive clock from PLL2 PFD2 396M 
    */
    switch(CLOCK_GetMux(kCLOCK_LpspiMux))
    {
    case 0:
        freq = CLOCK_GetFreq(kCLOCK_Usb1PllPfd1Clk); 
        break; 
        
    case 1:
        freq = CLOCK_GetFreq(kCLOCK_Usb1PllPfd0Clk); 
        break; 
    
    case 2:
        freq = CLOCK_GetFreq(kCLOCK_SysPllClk); 
        break; 
    
    case 3:
        freq = CLOCK_GetFreq(kCLOCK_SysPllPfd2Clk); 
        break; 
    }
    
    freq /= (CLOCK_GetDiv(kCLOCK_LpspiDiv) + 1U); 

    return freq;
}

static rt_err_t rt1050_spi_init(LPSPI_Type *base, struct rt_spi_configuration *cfg)
{
    lpspi_master_config_t masterConfig; 
    
    if(cfg->data_width != 8 && cfg->data_width != 16 && cfg->data_width != 32)
    {
        return RT_EINVAL; 
    }
    
#if defined(RT_USING_SPIBUS1)
    if(base == LPSPI1)
    {
        IOMUXC_SetPinMux   (IOMUXC_GPIO_EMC_27_LPSPI1_SCK, 0U); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_27_LPSPI1_SCK, 0x10B0u); 
        IOMUXC_SetPinMux   (IOMUXC_GPIO_EMC_28_LPSPI1_SDO, 0U); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_28_LPSPI1_SDO, 0x10B0u); 
        IOMUXC_SetPinMux   (IOMUXC_GPIO_EMC_29_LPSPI1_SDI, 0U); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_29_LPSPI1_SDI, 0x10B0u); 
    }
#endif 
    
#if defined(RT_USING_SPIBUS2)
    if(base == LPSPI2)
    {
        IOMUXC_SetPinMux   (IOMUXC_GPIO_SD_B1_07_LPSPI2_SCK, 0U); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_07_LPSPI2_SCK, 0x10B0u); 
        IOMUXC_SetPinMux   (IOMUXC_GPIO_SD_B1_08_LPSPI2_SD0, 0U); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_08_LPSPI2_SD0, 0x10B0u); 
        IOMUXC_SetPinMux   (IOMUXC_GPIO_SD_B1_09_LPSPI2_SDI, 0U); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_09_LPSPI2_SDI, 0x10B0u); 
        
        /* Optional IO config */
        //IOMUXC_SetPinMux   (IOMUXC_GPIO_EMC_00_LPSPI2_SCK, 0U); 
        //IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_00_LPSPI2_SCK, 0x10B0u); 
        //IOMUXC_SetPinMux   (IOMUXC_GPIO_EMC_02_LPSPI2_SDO, 0U); 
        //IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_02_LPSPI2_SDO, 0x10B0u); 
        //IOMUXC_SetPinMux   (IOMUXC_GPIO_EMC_03_LPSPI2_SDI, 0U); 
        //IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_03_LPSPI2_SDI, 0x10B0u); 
    }
#endif 
    
#if defined(RT_USING_SPIBUS3)
    if(base == LPSPI3)
    {
        IOMUXC_SetPinMux   (IOMUXC_GPIO_AD_B1_13_LPSPI3_SDI, 0U); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_13_LPSPI3_SDI, 0x10B0u); 
        IOMUXC_SetPinMux   (IOMUXC_GPIO_AD_B1_14_LPSPI3_SDO, 0U); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_14_LPSPI3_SDO, 0x10B0u); 
        IOMUXC_SetPinMux   (IOMUXC_GPIO_AD_B1_15_LPSPI3_SCK, 0U); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_15_LPSPI3_SCK, 0x10B0u); 
    }
#endif 
    
#if defined(RT_USING_SPIBUS4)
    if(base == LPSPI4)
    {
        IOMUXC_SetPinMux   (IOMUXC_GPIO_B0_01_LPSPI4_SDI, 0U); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_01_LPSPI4_SDI, 0x10B0u); 
        IOMUXC_SetPinMux   (IOMUXC_GPIO_B0_02_LPSPI4_SDO, 0U); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_02_LPSPI4_SDO, 0x10B0u); 
        IOMUXC_SetPinMux   (IOMUXC_GPIO_B0_03_LPSPI4_SCK, 0U); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_03_LPSPI4_SCK, 0x10B0u); 

        /* Optional IO config */
        //IOMUXC_SetPinMux   (IOMUXC_GPIO_B1_07_LPSPI4_SCK, 0U); 
        //IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_07_LPSPI4_SCK, 0x10B0u); 
        //IOMUXC_SetPinMux   (IOMUXC_GPIO_B1_06_LPSPI4_SDO, 0U); 
        //IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_06_LPSPI4_SDO, 0x10B0u); 
        //IOMUXC_SetPinMux   (IOMUXC_GPIO_B1_05_LPSPI4_SDI, 0U); 
        //IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_05_LPSPI4_SDI, 0x10B0u); 
    }
#endif 
    
    LPSPI_MasterGetDefaultConfig(&masterConfig); 
    
    masterConfig.baudRate     = cfg->max_hz; 
    masterConfig.bitsPerFrame = cfg->data_width; 
    
    if(cfg->mode & RT_SPI_MSB)
    {
        masterConfig.direction = kLPSPI_MsbFirst; 
    }
    else
    {
        masterConfig.direction = kLPSPI_LsbFirst; 
    }
    
    if(cfg->mode & RT_SPI_CPHA)
    {
        masterConfig.cpha = kLPSPI_ClockPhaseSecondEdge; 
    }
    else
    {
        masterConfig.cpha = kLPSPI_ClockPhaseFirstEdge; 
    }
    
    if(cfg->mode & RT_SPI_CPOL)
    {
        masterConfig.cpol = kLPSPI_ClockPolarityActiveLow; 
    }
    else
    {
        masterConfig.cpol = kLPSPI_ClockPolarityActiveHigh; 
    }
    
    masterConfig.pinCfg                        = kLPSPI_SdiInSdoOut; 
    masterConfig.dataOutConfig                 = kLpspiDataOutTristate;
    masterConfig.pcsToSckDelayInNanoSec        = 1000000000 / masterConfig.baudRate; 
    masterConfig.lastSckToPcsDelayInNanoSec    = 1000000000 / masterConfig.baudRate; 
    masterConfig.betweenTransferDelayInNanoSec = 1000000000 / masterConfig.baudRate; 
    
    LPSPI_MasterInit(base, &masterConfig, rt1050_get_lpspi_freq()); 
    base->CFGR1 |= LPSPI_CFGR1_PCSCFG_MASK; 
    
    return RT_EOK; 
}

rt_err_t rt1050_spi_bus_attach_device(const char *bus_name, const char *device_name, rt_uint32_t pin)
{
    rt_err_t ret; 
    
    struct rt_spi_device *spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device)); 
    RT_ASSERT(spi_device != RT_NULL); 
    
    struct rt1050_hw_spi_cs *cs_pin = (struct rt1050_hw_spi_cs *)rt_malloc(sizeof(struct rt1050_hw_spi_cs)); 
    RT_ASSERT(cs_pin != RT_NULL);
    
    cs_pin->pin = pin;
    rt_pin_mode(pin, PIN_MODE_OUTPUT); 
    rt_pin_write(pin, PIN_HIGH); 
    
    ret = rt_spi_bus_attach_device(spi_device, device_name, bus_name, (void *)cs_pin); 
    
    return ret; 
}

static rt_err_t spi_configure(struct rt_spi_device *device, struct rt_spi_configuration *cfg)
{
    rt_err_t ret; 
    struct rt1050_spi *spi = RT_NULL; 
    
    RT_ASSERT(cfg != RT_NULL);
    RT_ASSERT(device != RT_NULL);
    
    spi = (struct rt1050_spi *)(device->bus->parent.user_data); 
    spi->cfg = cfg; 
    ret = rt1050_spi_init(spi->base, cfg); 
    
    return ret;
}

static rt_uint32_t spixfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    lpspi_transfer_t transfer; 
    
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(device->bus->parent.user_data != RT_NULL);
    
    struct rt1050_spi *spi = (struct rt1050_spi *)(device->bus->parent.user_data); 
    struct rt1050_hw_spi_cs *cs = device->parent.user_data; 
    
    if(message->cs_take)
    {
        rt_pin_write(cs->pin, PIN_LOW);
    }
    
    transfer.rxData = (uint8_t *)(message->recv_buf); 
    transfer.txData = (uint8_t *)(message->send_buf); 
    transfer.dataSize = message->length; 
    status_t stat = LPSPI_MasterTransferBlocking(spi->base, &transfer); 
    
    if(message->cs_release)
    {
        rt_pin_write(cs->pin, PIN_HIGH);
    }
    
    return message->length; 
}

#if defined(RT_USING_SPIBUS1)
static struct rt1050_spi spi1 = 
{
    .base = LPSPI1
}; 
static struct rt_spi_bus spi1_bus = 
{
    .parent.user_data = &spi1
}; 
#endif

#if defined(RT_USING_SPIBUS2)
static struct rt1050_spi spi2 = 
{
    .base = LPSPI2
}; 
static struct rt_spi_bus spi2_bus = 
{
    .parent.user_data = &spi2
}; 
#endif

#if defined(RT_USING_SPIBUS3)
static struct rt1050_spi spi3 = 
{
    .base = LPSPI3
}; 
static struct rt_spi_bus spi3_bus = 
{
    .parent.user_data = &spi3
}; 
#endif

#if defined(RT_USING_SPIBUS4)
static struct rt1050_spi spi4 = 
{
    .base = LPSPI4
}; 
static struct rt_spi_bus spi4_bus = 
{
    .parent.user_data = &spi4
}; 
#endif

static struct rt_spi_ops rt1050_spi_ops = 
{
    .configure = spi_configure, 
    .xfer      = spixfer
}; 
 
int rt_hw_spi_bus_init(void)
{
#if defined(RT_USING_SPIBUS1) || defined(RT_USING_SPIBUS2) || \
    defined(RT_USING_SPIBUS3) || defined(RT_USING_SPIBUS4)
    
    CLOCK_SetMux(kCLOCK_LpspiMux, LPSPI_CLK_SOURCE);
    CLOCK_SetDiv(kCLOCK_LpspiDiv, LPSPI_CLK_SOURCE_DIVIDER); 
    
    CLOCK_EnableClock(kCLOCK_Iomuxc); 
#endif
    
#if defined(RT_USING_SPIBUS1)
    rt_spi_bus_register(&spi1_bus, "spibus1", &rt1050_spi_ops); 
#endif
    
#if defined(RT_USING_SPIBUS2)
    rt_spi_bus_register(&spi2_bus, "spibus2", &rt1050_spi_ops); 
#endif
    
#if defined(RT_USING_SPIBUS3)
    rt_spi_bus_register(&spi3_bus, "spibus3", &rt1050_spi_ops); 
#endif
    
#if defined(RT_USING_SPIBUS4)
    rt_spi_bus_register(&spi4_bus, "spibus4", &rt1050_spi_ops); 
#endif
    
    return RT_EOK; 
}
INIT_BOARD_EXPORT(rt_hw_spi_bus_init); 

#endif
