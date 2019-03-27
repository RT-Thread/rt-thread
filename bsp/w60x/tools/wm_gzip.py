# -*- coding:utf-8 -*-
#
# W600 make gzip file
# Copyright (c) 2018 Winner Micro Electronic Design Co., Ltd.
# All rights reserved.

import sys
import gzip

file_name = sys.argv[1]
file_prefix = file_name + '.gz'
with open(file_name, 'rb') as f_in:
    with gzip.open(file_prefix, 'wb') as f_out:
        f_out.writelines(f_in)
        f_in.close()
        f_out.close()