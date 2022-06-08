/*
 * MTD device concatenation layer definitions
 *
 * Copyright © 2002      Robert Kaiser <rkaiser@sysgo.de>
 *
 * SPDX-License-Identifier: GPL-2.0+
 *
 */

#ifndef MTD_CONCAT_H
#define MTD_CONCAT_H

struct mtd_info *mtd_concat_create(
    struct mtd_info *subdev[],  /* subdevices to concatenate */
    int num_devs,               /* number of subdevices      */
#ifndef __UBOOT__
    const char *name);          /* name for the new device   */
#else
    char *name);          /* name for the new device   */
#endif

void mtd_concat_destroy(struct mtd_info *mtd);

#endif
