#ifndef __RA6W1_FAL_CFG_H__
#define __RA6W1_FAL_CFG_H__

#include <rtconfig.h>
#include "bsp_api.h"
#include "bsp_sflash_map_ra6w1.h"

#define RA6W1_OSPI_FLASH_DEV_NAME "ospi_flash"

#if defined(BSP_USING_OSPI_FLASH)
extern const struct fal_flash_dev ra6w1_ospi_flash;

#define FAL_FLASH_DEV_TABLE       \
{                                 \
    &ra6w1_ospi_flash,           \
}

#ifdef FAL_PART_HAS_TABLE_CFG
#define FAL_PART_TABLE                                                                        \
{                                                                                             \
    {FAL_PART_MAGIC_WORD, "filesystem", RA6W1_OSPI_FLASH_DEV_NAME, SF_USER_AREA, SF_USER_AREA_SIZE, 0}, \
}
#endif /* FAL_PART_HAS_TABLE_CFG */

#endif /* BSP_USING_OSPI_FLASH */

#endif /* __RA6W1_FAL_CFG_H__ */
