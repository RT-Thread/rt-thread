#!/usr/bin/env python3

# Copyright (c) 2018-2019, Ulf Magnusson
# SPDX-License-Identifier: ISC

"""
Writes a configuration file where all symbols are set to their their default
values.

The default output filename is '.config'. A different filename can be passed in
the KCONFIG_CONFIG environment variable.

Usage for the Linux kernel:

  $ make [ARCH=<arch>] scriptconfig SCRIPT=Kconfiglib/alldefconfig.py
"""
import kconfiglib


def main():
    kconf = kconfiglib.standard_kconfig(__doc__)
    kconf.load_allconfig("alldef.config")
    print(kconf.write_config())


if __name__ == "__main__":
    main()
