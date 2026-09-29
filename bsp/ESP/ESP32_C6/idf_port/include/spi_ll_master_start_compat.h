#ifndef RT_ESP_IDF_PORT_SPI_LL_MASTER_START_COMPAT_H
#define RT_ESP_IDF_PORT_SPI_LL_MASTER_START_COMPAT_H

#include "hal/spi_ll.h"

/*
 * components/hal/spi_hal_iram.c:188 starts the transaction with
 * spi_ll_master_user_start(hal->hw), a name this package's
 * hal/esp32c6/include/hal/spi_ll.h does not have. C6 splits it in two:
 * spi_ll_apply_config() (spi_ll.h:208, sets cmd.update and waits until the
 * peripheral has taken the configuration) and spi_ll_user_start() (spi_ll.h:231,
 * sets cmd.usr). The six targets whose spi_ll.h does define
 * spi_ll_master_user_start -- esp32, esp32c2, esp32c3, esp32h2, esp32s2,
 * esp32s3 -- all define it as those same two writes, in this order. So this is
 * not a substitute for the C6 sequence, it is the C6 sequence under the name the
 * shared spi_hal_iram.c asks for.
 *
 * Included with -include, for that one source file only (idf_port/SConscript),
 * so no other translation unit sees the name. packages/ is not in the
 * repository, which is why the fix lives here.
 */
#define spi_ll_master_user_start(hw) \
    do                               \
    {                                \
        spi_ll_apply_config(hw);     \
        spi_ll_user_start(hw);       \
    } while (0)

#endif /* RT_ESP_IDF_PORT_SPI_LL_MASTER_START_COMPAT_H */
