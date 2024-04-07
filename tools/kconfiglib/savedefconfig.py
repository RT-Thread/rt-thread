#!/usr/bin/env python3

# Copyright (c) 2019, Ulf Magnusson
# SPDX-License-Identifier: ISC

"""
Saves a minimal configuration file that only lists symbols that differ in value
from their defaults. Loading such a configuration file is equivalent to loading
the "full" configuration file.

Minimal configuration files are handy to start from when editing configuration
files by hand.

The default input configuration file is '.config'. A different input filename
can be passed in the KCONFIG_CONFIG environment variable.

Note: Minimal configurations can also be generated from within the menuconfig
interface.
"""
import argparse

import kconfiglib


def main():
    parser = argparse.ArgumentParser(
        formatter_class=argparse.RawDescriptionHelpFormatter,
        description=__doc__)

    parser.add_argument(
        "--kconfig",
        default="Kconfig",
        help="Top-level Kconfig file (default: Kconfig)")

    parser.add_argument(
        "--out",
        metavar="MINIMAL_CONFIGURATION",
        default="defconfig",
        help="Output filename for minimal configuration (default: defconfig)")

    args = parser.parse_args()

    kconf = kconfiglib.Kconfig(args.kconfig, suppress_traceback=True)
    print(kconf.load_config())
    print(kconf.write_min_config(args.out))


if __name__ == "__main__":
    main()
