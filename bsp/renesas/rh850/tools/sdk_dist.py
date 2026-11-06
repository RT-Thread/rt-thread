#
# Copyright (c) 2026, Linumiz
#
# SPDX-License-Identifier: Apache-2.0
#
# Change Logs:
# Date           Author       Notes
# 2026-11-06     Parthiban    first version
#

import os


def dist_do_building(BSP_ROOT, dist_dir):
    from mkdist import bsp_copy_files

    print('=> copy rh850 libraries')
    bsp_copy_files(os.path.join(os.path.dirname(BSP_ROOT), 'libraries'),
                   os.path.join(dist_dir, 'libraries'))
