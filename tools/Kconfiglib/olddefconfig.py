#!/usr/bin/env python3

# Copyright (c) 2018-2019, Ulf Magnusson
# SPDX-License-Identifier: ISC

"""
Updates an old .config file or creates a new one, by filling in default values
for all new symbols. This is the same as picking the default selection for all
symbols in oldconfig, or entering the menuconfig interface and immediately
saving.

The default input/output filename is '.config'. A different filename can be
passed in the KCONFIG_CONFIG environment variable.

When overwriting a configuration file, the old version is saved to
<filename>.old (e.g. .config.old).
"""
import kconfiglib


def main():
    kconf = kconfiglib.standard_kconfig(__doc__)
    print(kconf.load_config())
    print(kconf.write_config())


if __name__ == "__main__":
    main()
