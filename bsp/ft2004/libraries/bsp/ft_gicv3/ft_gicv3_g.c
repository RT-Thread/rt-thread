/*
 * @ : Copyright (c) 2020 Phytium Information Technology, Inc. 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Phytium license agreement.
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-04-29 18:57:47
 * @Description:  This files is for 
 * 
 * @Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "ft_parameters.h"
#include "ft_gicv3.h"

FGicv3_Config_t g_FGicv3_Config_tTable[FT_GICV3_INSTANCES_NUM] = {
    {
        .InstanceId = 0,                                             /* Id of device */
        .Gicv3BaseAddress = FT_GICV3_BASEADDRESS,                    /* gicv3 base Address */
        .Gicv3DistributorAddress = FT_GICV3_DISTRIBUTOR_BASEADDRESS, /* gicv3 Distributor Address */
        .Gicv3RdAddress = FT_GICV3_RD_BASEADDRESS,                   /*  the overall behavior of the Redistributor, for controlling LPIs, and for generating */
        .Gicv3SgiAddress = FT_GICV3_SGI_BASEADDRESS,                 /*  controlling and generating PPIs and SGIs. */
    }};