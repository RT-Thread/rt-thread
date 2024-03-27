#!/usr/bin/env python3

# Copyright (c) 2018-2019, Ulf Magnusson
# SPDX-License-Identifier: ISC

"""
Writes a configuration file where as many symbols as possible are set to 'm'.

The default output filename is '.config'. A different filename can be passed
in the KCONFIG_CONFIG environment variable.

Usage for the Linux kernel:

  $ make [ARCH=<arch>] scriptconfig SCRIPT=Kconfiglib/allmodconfig.py
"""
import kconfiglib


def main():
    kconf = kconfiglib.standard_kconfig(__doc__)

    # See allnoconfig.py
    kconf.warn = False

    for sym in kconf.unique_defined_syms:
        if sym.orig_type == kconfiglib.BOOL:
            # 'bool' choice symbols get their default value, as determined by
            # e.g. 'default's on the choice
            if not sym.choice:
                # All other bool symbols get set to 'y', like for allyesconfig
                sym.set_value(2)
        elif sym.orig_type == kconfiglib.TRISTATE:
            sym.set_value(1)

    for choice in kconf.unique_choices:
        choice.set_value(2 if choice.orig_type == kconfiglib.BOOL else 1)

    kconf.warn = True

    kconf.load_allconfig("allmod.config")

    print(kconf.write_config())


if __name__ == "__main__":
    main()
