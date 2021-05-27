/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-04-07 13:24:30
 * @Description:  This files is for gmac config
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "ft_gmac.h"
#include "ft_parameters.h"

FGmac_Config_t Gmac_ConfigTable[FT_GMAC_INSTANCES_NUM] = {
    {FT_GMAC0_ID,
     FT_GMAC_COMMON_ADDR,
     FT_GMAC0_BASEADDR,
     GMAC0_ISRNUM,
     GMAC0_ISRPRIORITY,
     0,
     5,
     GMAC_AUTONEGOTIATION_ENABLE,
     GMAC_SPEED_1000M,
     GMAC_MODE_FULLDUPLEX,
     GMAC_RXINTERRUPT_MODE,
     GMAC_CHECKSUM_BY_SOFTWARE,
     GMAC_MEDIA_INTERFACE_RGMII,
     FT_GMAC0_DEFAULT_ADDR},
    {FT_GMAC1_ID,
     FT_GMAC_COMMON_ADDR,
     FT_GMAC1_BASEADDR,
     GMAC1_ISRNUM,
     GMAC1_ISRPRIORITY,
     0,
     5,
     GMAC_AUTONEGOTIATION_ENABLE,
     GMAC_SPEED_1000M,
     GMAC_MODE_FULLDUPLEX,
     GMAC_RXINTERRUPT_MODE,
     GMAC_CHECKSUM_BY_SOFTWARE,
     GMAC_MEDIA_INTERFACE_RGMII,
     {0}},
};
