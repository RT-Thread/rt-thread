#!/usr/bin/env python3

# Copyright (c) 2018-2019, Ulf Magnusson
# SPDX-License-Identifier: ISC

"""
Lists all user-modifiable symbols that are not given a value in the
configuration file. Usually, these are new symbols that have been added to the
Kconfig files.

The default configuration filename is '.config'. A different filename can be
passed in the KCONFIG_CONFIG environment variable.
"""
from __future__ import print_function

import argparse
import sys

from kconfiglib import Kconfig, BOOL, TRISTATE, INT, HEX, STRING, TRI_TO_STR


def main():
    parser = argparse.ArgumentParser(
        formatter_class=argparse.RawDescriptionHelpFormatter,
        description=__doc__)

    parser.add_argument(
        "--show-help", "-l",
        action="store_true",
        help="Show any help texts as well")

    parser.add_argument(
        "kconfig",
        metavar="KCONFIG",
        nargs="?",
        default="Kconfig",
        help="Top-level Kconfig file (default: Kconfig)")

    args = parser.parse_args()

    kconf = Kconfig(args.kconfig, suppress_traceback=True)
    # Make it possible to filter this message out
    print(kconf.load_config(), file=sys.stderr)

    for sym in kconf.unique_defined_syms:
        # Only show symbols that can be toggled. Choice symbols are a special
        # case in that sym.assignable will be (2,) (length 1) for visible
        # symbols in choices in y mode, but they can still be toggled by
        # selecting some other symbol.
        if sym.user_value is None and \
           (len(sym.assignable) > 1 or
            (sym.visibility and (sym.orig_type in (INT, HEX, STRING) or
                                 sym.choice))):

            # Don't reuse the 'config_string' format for bool/tristate symbols,
            # to show n-valued symbols as 'CONFIG_FOO=n' instead of
            # '# CONFIG_FOO is not set'. This matches the C tools.
            if sym.orig_type in (BOOL, TRISTATE):
                s = "{}{}={}\n".format(kconf.config_prefix, sym.name,
                                       TRI_TO_STR[sym.tri_value])
            else:
                s = sym.config_string

            print(s, end="")
            if args.show_help:
                for node in sym.nodes:
                    if node.help is not None:
                        # Indent by two spaces. textwrap.indent() is not
                        # available in Python 2 (it's 3.3+).
                        print("\n".join("  " + line
                                        for line in node.help.split("\n")))
                        break


if __name__ == "__main__":
    main()
