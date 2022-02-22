#include "drv_spi.h"
#include "air105_hal.h"
int w5500_spi_device_init(void)
{
    return rt_hw_spi_device_attach(WIZ_SPI_BUS,WIZ_SPI_DEVICE, WIZ_SPI_CS);
}
INIT_DEVICE_EXPORT(w5500_spi_device_init);
