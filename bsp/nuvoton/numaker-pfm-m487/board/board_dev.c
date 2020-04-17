/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*   1. Redistributions of source code must retain the above copyright notice,
*      this list of conditions and the following disclaimer.
*   2. Redistributions in binary form must reproduce the above copyright notice,
*      this list of conditions and the following disclaimer in the documentation
*      and/or other materials provided with the distribution.
*   3. Neither the name of Nuvoton Technology Corp. nor the names of its contributors
*      may be used to endorse or promote products derived from this software
*      without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* Change Logs:
* Date            Author       Notes
* 2020-1-16       Wayne        First version
*
******************************************************************************/

#include <rtdevice.h>

#if defined(BOARD_USING_STORAGE_SPIFLASH)
#if defined(RT_USING_SFUD)
    static struct rt_spi_device spi_device;
    #include "spi_flash.h"
    #include "spi_flash_sfud.h"
#endif
static int rt_hw_spiflash_init(void)
{
    rt_spi_bus_attach_device(&spi_device, "qspi01", "qspi0", RT_NULL);
#if defined(RT_USING_SFUD)
    if (rt_sfud_flash_probe("flash0", "qspi01") == RT_NULL)
    {
        return -(RT_ERROR);
    }
#endif
    return 0;
}
INIT_COMPONENT_EXPORT(rt_hw_spiflash_init);
#endif /* BOARD_USING_STORAGE_SPIFLASH */

#if defined(BOARD_USING_SRAM0_AS_MEMHEAP)
/*
In Advance board design, SRAM address bus A16/A17/A18 are GPIO-controlled by SW, not EBI.
So we just remap 128KB only to RTT memory heap, due to it is out of controll.
AD0~AD15: 2^16*16bit = 128KB
*/
#include <drv_ebi.h>
#include "NuMicro.h"
static struct rt_memheap system_heap;
int nu_use_exsram_as_heap(void)
{
    rt_err_t ret;

    /* Open ebi bank1 */
    ret = nu_ebi_init(EBI_BANK1, EBI_BUSWIDTH_16BIT, EBI_TIMING_SLOWEST, EBI_OPMODE_NORMAL, EBI_CS_ACTIVE_LOW);
    if (ret != RT_EOK)
        return ret;

    /* Initial sram as heap */
    return rt_memheap_init(&system_heap, "nu_sram_heap", (void *)EBI_BANK1_BASE_ADDR, 128 * 1024);
}
INIT_BOARD_EXPORT(nu_use_exsram_as_heap);
#endif /* BOARD_USING_SRAM0_AS_MEMHEAP */


#if defined(BOARD_USING_MAX31875)
#include <sensor_max31875.h>
int rt_hw_max31875_port(void)
{
    struct rt_sensor_config cfg;

    cfg.intf.dev_name = "i2c1";
    cfg.intf.user_data = (void *)MAX31875_I2C_SLAVE_ADR_R0;
    cfg.irq_pin.pin = RT_PIN_NONE;

    rt_hw_max31875_init("max31875", &cfg);
    return 0;
}
INIT_APP_EXPORT(rt_hw_max31875_port);
#endif /* BOARD_USING_MAX31875 */

#if defined(BOARD_USING_MPU6500)
#include <sensor_inven_mpu6xxx.h>
int rt_hw_mpu6500_port(void)
{
    struct rt_sensor_config cfg;

    cfg.intf.dev_name = "i2c2";
    cfg.intf.user_data = (void *)MPU6XXX_ADDR_DEFAULT;
    cfg.irq_pin.pin = RT_PIN_NONE;

    rt_hw_mpu6xxx_init("mpu",  &cfg);
    return 0;
}
INIT_APP_EXPORT(rt_hw_mpu6500_port);
#endif /* BOARD_USING_MPU6500 */

#if defined(BOARD_USING_LCD_ILI9341) && defined(NU_PKG_USING_ILI9341_EBI)
#include <lcd_ili9341.h>
#if defined(PKG_USING_GUIENGINE)
    #include <rtgui/driver.h>
#endif
int rt_hw_ili9341_port(void)
{
    rt_err_t ret = RT_EOK;

    /* Open ebi BOARD_USING_ILI9341_EBI_PORT */
    ret = nu_ebi_init(BOARD_USING_ILI9341_EBI_PORT, EBI_BUSWIDTH_16BIT, EBI_TIMING_NORMAL, EBI_OPMODE_NORMAL, EBI_CS_ACTIVE_LOW);
    if (ret != RT_EOK)
        return ret;

    switch (BOARD_USING_ILI9341_EBI_PORT)
    {
    case 0:
        EBI->CTL0 |= EBI_CTL0_CACCESS_Msk;
        EBI->TCTL0 |= (EBI_TCTL0_WAHDOFF_Msk | EBI_TCTL0_RAHDOFF_Msk);
        break;
    case 1:
        EBI->CTL1 |= EBI_CTL1_CACCESS_Msk;
        EBI->TCTL1 |= (EBI_TCTL1_WAHDOFF_Msk | EBI_TCTL1_RAHDOFF_Msk);
        break;
    case 2:
        EBI->CTL2 |= EBI_CTL2_CACCESS_Msk;
        EBI->TCTL2 |= (EBI_TCTL2_WAHDOFF_Msk | EBI_TCTL2_RAHDOFF_Msk);
        break;
    }

    if (rt_hw_lcd_ili9341_ebi_init(EBI_BANK0_BASE_ADDR + BOARD_USING_ILI9341_EBI_PORT * EBI_MAX_SIZE) != RT_EOK)
        return -1;

    rt_hw_lcd_ili9341_init();

#if defined(PKG_USING_GUIENGINE)
    rt_device_t lcd_ili9341;
    lcd_ili9341 = rt_device_find("lcd");
    if (lcd_ili9341)
    {
        rtgui_graphic_set_device(lcd_ili9341);
    }
#endif

    return 0;
}
INIT_COMPONENT_EXPORT(rt_hw_ili9341_port);
#endif /* BOARD_USING_LCD_ILI9341 */
