#include <rtthread.h>
#include "board.h"
#include "gicv3.h"

/* MCU1 interrupt numbers extracted from the original SDK configuration. */

#define Os_IntChannel_PDMA0_Ch0Isr          213U
#define Os_IntChannel_Pps_IcuRtcIsr         221U
#define Os_IntChannel_Pps_IcuEthIsr         229U
#define Os_IntChannel_Spi0_Isr              171U
#define Os_IntChannel_Spi1_Isr              172U
#define Os_IntChannel_Spi2_Isr              173U
#define Os_IntChannel_Spi3_Isr              174U
#define Os_IntChannel_Uart4_Isr             45U
#define Os_IntChannel_Uart5_Isr             46U
#define Os_IntChannel_Adc_Ch0WdIsr          48U
#define Os_IntChannel_Adc_Ch1WdIsr          49U
#define Os_IntChannel_Adc_Ch2WdIsr          50U
#define Os_IntChannel_Adc_Ch3WdIsr          51U
#define Os_IntChannel_Adc_Ch4WdIsr          52U
#define Os_IntChannel_Adc_Ch5WdIsr          53U
#define Os_IntChannel_Adc_Ch6WdIsr          54U
#define Os_IntChannel_Adc_Ch7WdIsr          55U
#define Os_IntChannel_Adc_Ch8WdIsr          56U
#define Os_IntChannel_Adc_Ch9WdIsr          57U
#define Os_IntChannel_Adc_Ch10WdIsr         58U
#define Os_IntChannel_Adc_Ch11WdIsr         59U
#define Os_IntChannel_Adc_Ch12WdIsr         60U
#define Os_IntChannel_Adc_Ch13WdIsr         61U
#define Os_IntChannel_Adc_InjIsr            62U
#define Os_IntChannel_Adc_NorIsr            63U
#define Os_IntChannel_I2c0_Isr              64U
#define Os_IntChannel_I2c1_Isr              65U
#define Os_IntChannel_I2c2_Isr              66U
#define Os_IntChannel_I2c3_Isr              67U
#define Os_IntChannel_Gpio_Icu0ExtIsr       68U
#define Os_IntChannel_Gpio_Icu1ExtIsr       69U
#define Os_IntChannel_Gpio_Icu2ExtIsr       70U
#define Os_IntChannel_Mdma1_Ch1Isr          212U
#define Os_IntChannel_Ipc_CpuIpc0Ch0Isr     254U
#define Os_IntChannel_Ipc_CpuIpc0Ch4Isr     258U
#define Os_IntChannel_Ipc_CpuIpc0Ch7Isr     261U
#define Os_IntChannel_Ipc_CpuIpc0Ch10Isr    264U
#define Os_Cross_Core_Ins0_Isr              237U
#define Os_Cross_Core_Ins1_Isr              238U
#define Os_Cross_Core_Ins2_Isr              239U
#define Os_Cross_Core_Ins3_Isr              234U
#define Os_Cross_Core_Ins4_Isr              235U
#define Os_Cross_Core_Ins5_Isr              236U
#define Os_IntChannel_Can5_DataIsr          136U
#define Os_IntChannel_Can6_DataIsr          140U
#define Os_IntChannel_Can7_DataIsr          144U
#define Os_IntChannel_Can8_DataIsr          148U
#define Os_IntChannel_Can9_DataIsr          152U

/*
 * MCU1 interrupt whitelist extracted from the original SDK interrupt map.
 * The current BSP only manages these SPI IDs; everything else is treated as
 * out-of-scope to avoid colliding with resources still owned by MCU0.
 */

const s100_rt_irq_config_t s100_mcu1_rt_irq_configs[] =
{
    {Os_IntChannel_PDMA0_Ch0Isr,      RT_TRUE, "PDMA0_Ch0"},
    {Os_IntChannel_Pps_IcuRtcIsr,     RT_TRUE, "Pps_IcuRtc"},
    {Os_IntChannel_Pps_IcuEthIsr,     RT_TRUE, "Pps_IcuEth"},
    {Os_IntChannel_Spi0_Isr,          RT_TRUE, "Spi0"},
    {Os_IntChannel_Spi1_Isr,          RT_TRUE, "Spi1"},
    {Os_IntChannel_Spi2_Isr,          RT_TRUE, "Spi2"},
    {Os_IntChannel_Spi3_Isr,          RT_TRUE, "Spi3"},
    {Os_IntChannel_Uart4_Isr,         RT_TRUE, "Uart4"},
    {Os_IntChannel_Uart5_Isr,         RT_TRUE, "Uart5"},
    {Os_IntChannel_Adc_Ch0WdIsr,      RT_TRUE, "Adc_Ch0Wd"},
    {Os_IntChannel_Adc_Ch1WdIsr,      RT_TRUE, "Adc_Ch1Wd"},
    {Os_IntChannel_Adc_Ch2WdIsr,      RT_TRUE, "Adc_Ch2Wd"},
    {Os_IntChannel_Adc_Ch3WdIsr,      RT_TRUE, "Adc_Ch3Wd"},
    {Os_IntChannel_Adc_Ch4WdIsr,      RT_TRUE, "Adc_Ch4Wd"},
    {Os_IntChannel_Adc_Ch5WdIsr,      RT_TRUE, "Adc_Ch5Wd"},
    {Os_IntChannel_Adc_Ch6WdIsr,      RT_TRUE, "Adc_Ch6Wd"},
    {Os_IntChannel_Adc_Ch7WdIsr,      RT_TRUE, "Adc_Ch7Wd"},
    {Os_IntChannel_Adc_Ch8WdIsr,      RT_TRUE, "Adc_Ch8Wd"},
    {Os_IntChannel_Adc_Ch9WdIsr,      RT_TRUE, "Adc_Ch9Wd"},
    {Os_IntChannel_Adc_Ch10WdIsr,     RT_TRUE, "Adc_Ch10Wd"},
    {Os_IntChannel_Adc_Ch11WdIsr,     RT_TRUE, "Adc_Ch11Wd"},
    {Os_IntChannel_Adc_Ch12WdIsr,     RT_TRUE, "Adc_Ch12Wd"},
    {Os_IntChannel_Adc_Ch13WdIsr,     RT_TRUE, "Adc_Ch13Wd"},
    {Os_IntChannel_Adc_InjIsr,        RT_TRUE, "Adc_Inj"},
    {Os_IntChannel_Adc_NorIsr,        RT_TRUE, "Adc_Nor"},
    {Os_IntChannel_I2c0_Isr,          RT_TRUE, "I2c0"},
    {Os_IntChannel_I2c1_Isr,          RT_TRUE, "I2c1"},
    {Os_IntChannel_I2c2_Isr,          RT_TRUE, "I2c2"},
    {Os_IntChannel_I2c3_Isr,          RT_TRUE, "I2c3"},
    {Os_IntChannel_Gpio_Icu0ExtIsr,   RT_TRUE, "Gpio_Icu0Ext"},
    {Os_IntChannel_Gpio_Icu1ExtIsr,   RT_TRUE, "Gpio_Icu1Ext"},
    {Os_IntChannel_Gpio_Icu2ExtIsr,   RT_TRUE, "Gpio_Icu2Ext"},
    {Os_IntChannel_Mdma1_Ch1Isr,      RT_TRUE, "Mdma1_Ch1"},
    {Os_IntChannel_Ipc_CpuIpc0Ch0Isr, RT_TRUE, "Ipc_CpuIpc0Ch0"},
    {Os_IntChannel_Ipc_CpuIpc0Ch4Isr, RT_TRUE, "Ipc_CpuIpc0Ch4"},
    {Os_IntChannel_Ipc_CpuIpc0Ch7Isr, RT_TRUE, "Ipc_CpuIpc0Ch7"},
    {Os_IntChannel_Ipc_CpuIpc0Ch10Isr, RT_TRUE, "Ipc_CpuIpc0Ch10"},
    {Os_Cross_Core_Ins0_Isr,          RT_TRUE, "Cross_Core_Ins0"},
    {Os_Cross_Core_Ins1_Isr,          RT_TRUE, "Cross_Core_Ins1"},
    {Os_Cross_Core_Ins2_Isr,          RT_TRUE, "Cross_Core_Ins2"},
    {Os_Cross_Core_Ins3_Isr,          RT_TRUE, "Cross_Core_Ins3"},
    {Os_Cross_Core_Ins4_Isr,          RT_TRUE, "Cross_Core_Ins4"},
    {Os_Cross_Core_Ins5_Isr,          RT_TRUE, "Cross_Core_Ins5"},
    {Os_IntChannel_Can5_DataIsr,      RT_TRUE, "Can5_Data"},
    {Os_IntChannel_Can6_DataIsr,      RT_TRUE, "Can6_Data"},
    {Os_IntChannel_Can7_DataIsr,      RT_TRUE, "Can7_Data"},
    {Os_IntChannel_Can8_DataIsr,      RT_TRUE, "Can8_Data"},
    {Os_IntChannel_Can9_DataIsr,      RT_TRUE, "Can9_Data"},
};

const rt_size_t s100_mcu1_rt_irq_configs_count =
    sizeof(s100_mcu1_rt_irq_configs) / sizeof(s100_mcu1_rt_irq_configs[0]);

rt_bool_t s100_board_irq_is_supported(int irq)
{
    rt_size_t i;

    if ((irq >= 0) && (irq < 32))
    {
        return RT_TRUE;
    }

    for (i = 0; i < s100_mcu1_rt_irq_configs_count; i++)
    {
        if (s100_mcu1_rt_irq_configs[i].irq_number == irq)
        {
            return RT_TRUE;
        }
    }

    return RT_FALSE;
}

