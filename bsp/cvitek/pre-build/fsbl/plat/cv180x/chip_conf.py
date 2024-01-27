#!/usr/bin/env python3

import logging
import struct
import argparse

CHIP_CONF_CMD_DELAY_MS = 0xFFFFFFFD
CHIP_CONF_CMD_DELAY_US = 0xFFFFFFFE

CHIP_CONF_SCAN_START_1 = 0xFFFFFFA0


def gen_chip_conf(args):
    logging.info("gen_chip_conf")
    regs = [
        (0x0E00000C, 0xA0000001),  # ATF_DBG_REG = 0x0E00000C
        (0x0E00000C, 0xA0000002),
        # (CHIP_CONF_CMD_DELAY_MS, 100),
        # (CHIP_CONF_CMD_DELAY_US, 100),
        (CHIP_CONF_SCAN_START_1, 0xFFFFFFFF),
    ]

    chip_conf = b"".join(struct.pack("<II", a, v) for a, v in regs)
    logging.info("chip_conf=%d bytes", len(chip_conf))

    with open(args.CHIP_CONF, "wb") as fp:
        fp.write(chip_conf)


def main():
    parser = argparse.ArgumentParser(description="generate test cases")
    parser.add_argument("CHIP_CONF", type=str)
    args = parser.parse_args()
    gen_chip_conf(args)


if __name__ == "__main__":
    main()
