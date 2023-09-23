/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-1-16       Wayne        First version
*
******************************************************************************/

#include <rtdevice.h>
#include <drv_gpio.h>

#if defined(BOARD_USING_STORAGE_SPIFLASH)
#if defined(RT_USING_SFUD)
    #include "spi_flash.h"
    #include "spi_flash_sfud.h"
#endif

#include "drv_qspi.h"

#define W25X_REG_READSTATUS    (0x05)
#define W25X_REG_READSTATUS2   (0x35)
#define W25X_REG_WRITEENABLE   (0x06)
#define W25X_REG_WRITESTATUS   (0x01)
#define W25X_REG_QUADENABLE    (0x02)

static rt_uint8_t SpiFlash_ReadStatusReg(struct rt_qspi_device *qspi_device)
{
    rt_uint8_t u8Val;
    rt_err_t result = RT_EOK;
    rt_uint8_t w25x_txCMD1 = W25X_REG_READSTATUS;

    result = rt_qspi_send_then_recv(qspi_device, &w25x_txCMD1, 1, &u8Val, 1);
    RT_ASSERT(result > 0);

    return u8Val;
}

static rt_uint8_t SpiFlash_ReadStatusReg2(struct rt_qspi_device *qspi_device)
{
    rt_uint8_t u8Val;
    rt_err_t result = RT_EOK;
    rt_uint8_t w25x_txCMD1 = W25X_REG_READSTATUS2;

    result = rt_qspi_send_then_recv(qspi_device, &w25x_txCMD1, 1, &u8Val, 1);
    RT_ASSERT(result > 0);

    return u8Val;
}

static rt_err_t SpiFlash_WriteStatusReg(struct rt_qspi_device *qspi_device, uint8_t u8Value1, uint8_t u8Value2)
{
    rt_uint8_t w25x_txCMD1;
    rt_uint8_t au8Val[2];
    rt_err_t result;
    struct rt_qspi_message qspi_message = {0};

    /* Enable WE */
    w25x_txCMD1 = W25X_REG_WRITEENABLE;
    result = rt_qspi_send(qspi_device, &w25x_txCMD1, sizeof(w25x_txCMD1));
    if (result != sizeof(w25x_txCMD1))
        goto exit_SpiFlash_WriteStatusReg;

    /* Prepare status-1, 2 data */
    au8Val[0] = u8Value1;
    au8Val[1] = u8Value2;

    /* 1-bit mode: Instruction+payload */
    qspi_message.instruction.content = W25X_REG_WRITESTATUS;
    qspi_message.instruction.qspi_lines = 1;

    qspi_message.qspi_data_lines   = 1;
    qspi_message.parent.cs_take    = 1;
    qspi_message.parent.cs_release = 1;
    qspi_message.parent.send_buf   = &au8Val[0];
    qspi_message.parent.length     = sizeof(au8Val);
    qspi_message.parent.next       = RT_NULL;

    if (rt_qspi_transfer_message(qspi_device, &qspi_message) != sizeof(au8Val))
    {
        result = -RT_ERROR;
    }

    result  = RT_EOK;

exit_SpiFlash_WriteStatusReg:

    return result;
}

static void SpiFlash_WaitReady(struct rt_qspi_device *qspi_device)
{
    volatile uint8_t u8ReturnValue;

    do
    {
        u8ReturnValue = SpiFlash_ReadStatusReg(qspi_device);
        u8ReturnValue = u8ReturnValue & 1;
    }
    while (u8ReturnValue != 0);   // check the BUSY bit
}

static void SpiFlash_EnterQspiMode(struct rt_qspi_device *qspi_device)
{
    rt_err_t result = RT_EOK;

    uint8_t u8Status1 = SpiFlash_ReadStatusReg(qspi_device);
    uint8_t u8Status2 = SpiFlash_ReadStatusReg2(qspi_device);

    u8Status2 |= W25X_REG_QUADENABLE;

    result = SpiFlash_WriteStatusReg(qspi_device, u8Status1, u8Status2);
    RT_ASSERT(result == RT_EOK);

    SpiFlash_WaitReady(qspi_device);
}

static void SpiFlash_ExitQspiMode(struct rt_qspi_device *qspi_device)
{
    rt_err_t result = RT_EOK;
    uint8_t u8Status1 = SpiFlash_ReadStatusReg(qspi_device);
    uint8_t u8Status2 = SpiFlash_ReadStatusReg2(qspi_device);

    u8Status2 &= ~W25X_REG_QUADENABLE;

    result = SpiFlash_WriteStatusReg(qspi_device, u8Status1, u8Status2);
    RT_ASSERT(result == RT_EOK);

    SpiFlash_WaitReady(qspi_device);
}

static int rt_hw_spiflash_init(void)
{
    /*
        Don't forget to switch SPIM pins to QSPI0 pins on NuMaker-M467HJ V1.0 board.
        CS:   R12-Open, R13-Close
        CLK:  R14-Open, R15-Close
        MOSI: R16-Open, R17-Close
        MISO: R18-Open, R19-Close
        IO2:  R20-Open, R21-Close
        IO3:  R22-Open, R23-Close
    */
    if (nu_qspi_bus_attach_device("qspi0", "qspi01", 4, SpiFlash_EnterQspiMode, SpiFlash_ExitQspiMode) != RT_EOK)
        return -1;

#if defined(RT_USING_SFUD)
    if (rt_sfud_flash_probe(FAL_USING_NOR_FLASH_DEV_NAME, "qspi01") == RT_NULL)
    {
        return -(RT_ERROR);
    }
#endif

    return 0;
}
INIT_COMPONENT_EXPORT(rt_hw_spiflash_init);
#endif /* BOARD_USING_STORAGE_SPIFLASH */

#if defined(BOARD_USING_NAU8822) && defined(NU_PKG_USING_NAU8822)
#include <acodec_nau8822.h>
S_NU_NAU8822_CONFIG sCodecConfig =
{
    .i2c_bus_name = "i2c2",

    .i2s_bus_name = "sound0",

    .pin_phonejack_en = NU_GET_PININDEX(NU_PD, 3),

    .pin_phonejack_det = NU_GET_PININDEX(NU_PD, 2),
};

int rt_hw_nau8822_port(void)
{
    if (nu_hw_nau8822_init(&sCodecConfig) != RT_EOK)
        return -1;

    return 0;
}
INIT_COMPONENT_EXPORT(rt_hw_nau8822_port);
#endif /* BOARD_USING_NAU8822 */

#if defined(BOARD_USING_LCD_SSD1963) && defined(NU_PKG_USING_SSD1963_EBI)
#include <drv_ebi.h>
#include "NuMicro.h"
#include <lcd_ssd1963.h>
#if defined(PKG_USING_GUIENGINE)
    #include <rtgui/driver.h>
#endif
int rt_hw_ssd1963_port(void)
{
    rt_err_t ret = RT_EOK;

    /* Open ebi BOARD_USING_SSD1963_EBI_PORT */
    ret = nu_ebi_init(BOARD_USING_SSD1963_EBI_PORT, EBI_BUSWIDTH_16BIT, EBI_TIMING_FAST, EBI_OPMODE_NORMAL, EBI_CS_ACTIVE_LOW);
    if (ret != RT_EOK)
        return ret;

    switch (BOARD_USING_SSD1963_EBI_PORT)
    {
    case 0:
        EBI->CTL0 |= EBI_CTL_CACCESS_Msk;
        EBI->TCTL0 |= (EBI_TCTL_WAHDOFF_Msk | EBI_TCTL_RAHDOFF_Msk);
        break;
    case 1:
        EBI->CTL1 |= EBI_CTL_CACCESS_Msk;
        EBI->TCTL1 |= (EBI_TCTL_WAHDOFF_Msk | EBI_TCTL_RAHDOFF_Msk);
        break;
    case 2:
        EBI->CTL2 |= EBI_CTL_CACCESS_Msk;
        EBI->TCTL2 |= (EBI_TCTL_WAHDOFF_Msk | EBI_TCTL_RAHDOFF_Msk);
        break;
    default:
        return -1;
    }

    if (rt_hw_lcd_ssd1963_ebi_init(EBI_BANK0_BASE_ADDR + BOARD_USING_SSD1963_EBI_PORT * EBI_MAX_SIZE) != RT_EOK)
        return -1;

    rt_hw_lcd_ssd1963_init();

#if defined(PKG_USING_GUIENGINE)
    rt_device_t lcd_ssd1963;
    lcd_ssd1963 = rt_device_find("lcd");
    if (lcd_ssd1963)
    {
        rtgui_graphic_set_device(lcd_ssd1963);
    }
#endif

    return 0;
}
INIT_COMPONENT_EXPORT(rt_hw_ssd1963_port);
#endif /* BOARD_USING_LCD_SSD1963 */


#if defined(BOARD_USING_ILI2130) && defined(NU_PKG_USING_TPC_ILI)
#include "ili.h"

#define ILI2130_RST_PIN   NU_GET_PININDEX(NU_PD, 10)
#define ILI2130_IRQ_PIN   NU_GET_PININDEX(NU_PG, 6)

extern int tpc_sample(const char *name);
int rt_hw_ili2130_port(void)
{
    struct rt_touch_config cfg;
    rt_base_t rst_pin = ILI2130_RST_PIN;
    cfg.dev_name = "i2c1";
    cfg.irq_pin.pin = ILI2130_IRQ_PIN;
    cfg.irq_pin.mode = PIN_MODE_INPUT_PULLUP;
    cfg.user_data = &rst_pin;

    rt_hw_ili_tpc_init("ili_tpc", &cfg);
    return tpc_sample("ili_tpc");

}
INIT_ENV_EXPORT(rt_hw_ili2130_port);
#endif /* if defined(BOARD_USING_ILI2130) && defined(NU_PKG_USING_ILI_TPC) */

#if defined(BOARD_USING_LCD_FSA506) && defined(NU_PKG_USING_FSA506_EBI)
#include <drv_ebi.h>
#include "NuMicro.h"
#include <lcd_fsa506.h>
#if defined(PKG_USING_GUIENGINE)
    #include <rtgui/driver.h>
#endif
int rt_hw_fsa506_port(void)
{
    rt_err_t ret = RT_EOK;

    /* Open ebi BOARD_USING_FSA506_EBI_PORT */
    ret = nu_ebi_init(BOARD_USING_FSA506_EBI_PORT, EBI_BUSWIDTH_16BIT, EBI_TIMING_SLOW, EBI_OPMODE_CACCESS, EBI_CS_ACTIVE_LOW);
    if (ret != RT_EOK)
        return ret;

    if (rt_hw_lcd_fsa506_ebi_init(EBI_BANK0_BASE_ADDR + BOARD_USING_FSA506_EBI_PORT * EBI_MAX_SIZE) != RT_EOK)
        return -1;

    rt_hw_lcd_fsa506_init();

#if defined(PKG_USING_GUIENGINE)
    rt_device_t lcd_fsa506 = rt_device_find("lcd");
    if (lcd_fsa506)
    {
        rtgui_graphic_set_device(lcd_fsa506);
    }
#endif

    return 0;
}
INIT_COMPONENT_EXPORT(rt_hw_fsa506_port);
#endif /* BOARD_USING_LCD_FSA506 */



#if defined(BOARD_USING_ST1663I) && defined(NU_PKG_USING_TPC_ST1663I)
#include "st1663i.h"

#define ST1663I_RST_PIN   NU_GET_PININDEX(NU_PD, 10)
#define ST1663I_IRQ_PIN   NU_GET_PININDEX(NU_PG, 6)

extern int tpc_sample(const char *name);
int rt_hw_st1663i_port(void)
{
    struct rt_touch_config cfg;
    rt_base_t rst_pin = ST1663I_RST_PIN;
    cfg.dev_name = "i2c1";
    cfg.irq_pin.pin = ST1663I_IRQ_PIN;
    cfg.irq_pin.mode = PIN_MODE_INPUT_PULLUP;
    cfg.user_data = &rst_pin;

    rt_hw_st1663i_init("st1663i", &cfg);
    return tpc_sample("st1663i");

}
INIT_ENV_EXPORT(rt_hw_st1663i_port);
#endif /* if defined(BOARD_USING_ST1663I) && defined(NU_PKG_USING_TPC_ST1663I) */

#if defined(BOARD_USING_SENSOR0)
#include "ccap_sensor.h"

#define SENSOR0_RST_PIN    NU_GET_PININDEX(NU_PG, 11)
#define SENSOR0_PD_PIN     NU_GET_PININDEX(NU_PD, 12)

ccap_sensor_io sIo_sensor0 =
{
    .RstPin          = SENSOR0_RST_PIN,
    .PwrDwnPin       = SENSOR0_PD_PIN,
    .I2cName         = "i2c0"
};

int rt_hw_sensor0_port(void)
{
    return  nu_ccap_sensor_create(&sIo_sensor0, (ccap_sensor_id)BOARD_USING_SENSON0_ID, "sensor0");
}
INIT_COMPONENT_EXPORT(rt_hw_sensor0_port);

#endif /* BOARD_USING_SENSOR0 */

#if defined(BOARD_USING_NCT7717U)

#include "sensor_nct7717u.h"

int rt_hw_nct7717u_port(void)
{
    struct rt_sensor_config cfg;

    cfg.intf.dev_name = "i2c2";
    cfg.irq_pin.pin = PIN_IRQ_PIN_NONE;

    return rt_hw_nct7717u_init("nct7717u", &cfg);
}
INIT_APP_EXPORT(rt_hw_nct7717u_port);
#endif /* BOARD_USING_NCT7717U */
