#!/usr/bin/env python3
# SPDX-License-Identifier: BSD-3-Clause
# PYTHON_ARGCOMPLETE_OK

import sys
import logging
import os
import os.path
import argparse
from collections import OrderedDict
import binascii
from struct import pack, unpack
import lzma
import pprint


PYTHON_MIN_VERSION = (3, 5, 2)  # Ubuntu 16.04 LTS contains Python v3.5.2 by default


if sys.version_info < PYTHON_MIN_VERSION:
    print("Python >= %r is required" % (PYTHON_MIN_VERSION,))
    sys.exit(-1)


try:
    import coloredlogs
except ImportError:
    coloredlogs = None

try:
    import argcomplete
except ImportError:
    argcomplete = None


LOADER_2ND_MAGIC_ORIG = b"BL33"
LOADER_2ND_MAGIC_LZMA = b"B3MA"
LOADER_2ND_MAGIC_LZ4 = b"B3Z4"

LOADER_2ND_MAGIC_LIST = [
    LOADER_2ND_MAGIC_ORIG,
    LOADER_2ND_MAGIC_LZMA,
    LOADER_2ND_MAGIC_LZ4,
]

IMAGE_ALIGN = 512
PARAM1_SIZE = 0x1000
PARAM1_SIZE_WO_SIG = 0x800
PARAM2_SIZE = 0x1000


def round_up(divident, divisor):
    return ((divident + divisor - 1) // divisor) * divisor


def lzma_compress(body):
    z = lzma.LZMACompressor(lzma.FORMAT_ALONE, preset=lzma.PRESET_EXTREME)
    compressed = z.compress(body)
    compressed += z.flush()

    return compressed


def lz4_compress(body):
    try:
        import lz4.frame
    except ImportError:
        logging.error("lz4 is not installed. Run 'pip install lz4'.")
        raise

    compressed = lz4.frame.compress(body)
    return compressed


class Entry:
    __slots__ = "name", "type", "addr", "_content", "entry_size"

    def __init__(self):
        self.addr = None
        self._content = None

    @property
    def end(self):
        return self.addr + self.entry_size

    @property
    def content(self):
        return self._content

    @content.setter
    def content(self, value):
        if type(value) == int:
            value = value.to_bytes(self.entry_size, "little")

        if self.entry_size is not None:
            if len(value) > self.entry_size:
                raise ValueError("%s (%d bytes) must <= %#r" % (self.name, len(value), self.entry_size))
            value = value + b"\0" * (self.entry_size - len(value))

        self._content = value

    @classmethod
    def make(cls, name, entry_size, _type, init=None):
        entry = Entry()
        entry.name = name
        entry.type = _type
        entry.entry_size = entry_size

        if type(init) in (bytes, bytearray):
            entry.content = bytes(init)
        elif entry_size is not None:
            entry.content = b"\0" * entry.entry_size
        else:
            entry.content = b""

        return (name, entry)

    def toint(self):
        if self.type != int:
            raise TypeError("%s is not int type" % self.name)

        return int.from_bytes(self.content, "little")

    def tostr(self):
        v = self.content
        if self.type == int:
            v = "%#08x" % self.toint()
        elif type(self.content) in [bytes, bytearray]:
            v = v.hex()
            if len(v) > 32:
                v = v[:32] + "..."

        return v

    def __str__(self):
        v = self.tostr()
        return "<%s=%s (%dbytes)>" % (self.name, v, self.entry_size)

    def __repr__(self):
        v = self.tostr()
        return "<%s: a=%#x s=%#x c=%s %r>" % (self.name, self.addr, self.entry_size, v, self.type)


class FIP:
    param1 = OrderedDict(
        [
            Entry.make("MAGIC1", 8, int, b"CVBL01\n\0"),
            Entry.make("MAGIC2", 4, int),
            Entry.make("PARAM_CKSUM", 4, int),
            Entry.make("NAND_INFO", 128, int),
            Entry.make("NOR_INFO", 36, int),
            Entry.make("FIP_FLAGS", 8, int),
            Entry.make("CHIP_CONF_SIZE", 4, int),
            Entry.make("BLCP_IMG_CKSUM", 4, int),
            Entry.make("BLCP_IMG_SIZE", 4, int),
            Entry.make("BLCP_IMG_RUNADDR", 4, int),
            Entry.make("BLCP_PARAM_LOADADDR", 4, int),
            Entry.make("BLCP_PARAM_SIZE", 4, int),
            Entry.make("BL2_IMG_CKSUM", 4, int),
            Entry.make("BL2_IMG_SIZE", 4, int),
            Entry.make("BLD_IMG_SIZE", 4, int),
            Entry.make("PARAM2_LOADADDR", 4, int),
            Entry.make("RESERVED1", 4, int),
            Entry.make("CHIP_CONF", 760, bytes),
            Entry.make("BL_EK", 32, bytes),
            Entry.make("ROOT_PK", 512, bytes),
            Entry.make("BL_PK", 512, bytes),
            Entry.make("BL_PK_SIG", 512, bytes),
            Entry.make("CHIP_CONF_SIG", 512, bytes),
            Entry.make("BL2_IMG_SIG", 512, bytes),
            Entry.make("BLCP_IMG_SIG", 512, bytes),
        ]
    )

    body1 = OrderedDict(
        [
            Entry.make("BLCP", None, bytes),
            Entry.make("BL2", None, bytes),
        ]
    )

    param2 = OrderedDict(
        [
            Entry.make("MAGIC1", 8, int, b"CVLD02\n\0"),
            Entry.make("PARAM2_CKSUM", 4, int),
            Entry.make("RESERVED1", 4, bytes),
            # DDR param
            Entry.make("DDR_PARAM_CKSUM", 4, int),
            Entry.make("DDR_PARAM_LOADADDR", 4, int),
            Entry.make("DDR_PARAM_SIZE", 4, int),
            Entry.make("DDR_PARAM_RESERVED", 4, int),
            # BLCP_2ND
            Entry.make("BLCP_2ND_CKSUM", 4, int),
            Entry.make("BLCP_2ND_LOADADDR", 4, int),
            Entry.make("BLCP_2ND_SIZE", 4, int),
            Entry.make("BLCP_2ND_RUNADDR", 4, int),
            # ATF-BL31 or OpenSBI
            Entry.make("MONITOR_CKSUM", 4, int),
            Entry.make("MONITOR_LOADADDR", 4, int),
            Entry.make("MONITOR_SIZE", 4, int),
            Entry.make("MONITOR_RUNADDR", 4, int),
            # u-boot
            Entry.make("LOADER_2ND_RESERVED0", 4, int),
            Entry.make("LOADER_2ND_LOADADDR", 4, int),
            Entry.make("LOADER_2ND_RESERVED1", 4, int),
            Entry.make("LOADER_2ND_RESERVED2", 4, int),
            # Reserved
            Entry.make("RESERVED_LAST", 4096 - 16 * 5, bytes),
        ]
    )

    body2 = OrderedDict(
        [
            Entry.make("DDR_PARAM", None, bytes),
            Entry.make("BLCP_2ND", None, bytes),
            Entry.make("MONITOR", None, bytes),
            Entry.make("LOADER_2ND", None, bytes),
        ]
    )

    ldr_2nd_hdr = OrderedDict(
        [
            Entry.make("JUMP0", 4, int),
            Entry.make("MAGIC", 4, int),
            Entry.make("CKSUM", 4, int),
            Entry.make("SIZE", 4, int),
            Entry.make("RUNADDR", 8, int),
            Entry.make("RESERVED1", 4, int),
            Entry.make("RESERVED2", 4, int),
        ]
    )

    FIP_FLAGS_SCS_MASK = 0x000c
    FIP_FLAGS_ENCRYPTED_MASK = 0x0030

    def _param_size(self, param):
        return max((e.end for e in param.values()))

    def _gen_param(self):
        addr = 0
        for entry in self.param1.values():
            entry.addr = addr
            addr += entry.entry_size

        assert PARAM1_SIZE_WO_SIG == self.param1["BL_PK_SIG"].addr

        addr = 0
        for entry in self.param2.values():
            entry.addr = addr
            addr += entry.entry_size

        assert PARAM2_SIZE == self.param2["RESERVED_LAST"].addr + self.param2["RESERVED_LAST"].entry_size

        addr = 0
        for entry in self.ldr_2nd_hdr.values():
            entry.addr = addr
            addr += entry.entry_size

    def __init__(self):
        self.compress_algo = None
        self._gen_param()

    def image_crc(self, image):
        crc = binascii.crc_hqx(image, 0)
        crc = pack("<H", crc) + b"\xFE\xCA"
        return crc

    def pad(self, data, block_size):
        if type(data) not in [bytearray, bytes]:
            raise TypeError("Need bytearray or bytes")

        r = len(data) % block_size
        if r:
            data += b"\0" * (block_size - r)

        return data

    def _pprint_attr(self, name):
        v = getattr(self, name)

        if type(v) == OrderedDict:
            v = list(v.values())
        logging.info("print(%s):\n" % name + pprint.pformat(v, 4, 140))

    def print_fip_params(self):
        self._pprint_attr("param1")
        self._pprint_attr("param2")
        self._pprint_attr("ldr_2nd_hdr")

    def read_fip(self, path):
        logging.debug("read_fip:")

        with open(path, "rb") as fp:
            fip_bin = fp.read()

        fip_bin = bytearray(fip_bin)

        e = self.param1["MAGIC1"]
        if fip_bin[e.addr : e.end] != e.content:
            raise ValueError("Unknown magic %r" % fip_bin[e.addr : e.end])

        # Read param1 from fip.bin
        for e in self.param1.values():
            e.content = fip_bin[e.addr : e.end]

        self.read_end = PARAM1_SIZE

        # Read BLCP
        e = self.param1["BLCP_IMG_SIZE"]
        blcp_img_size = unpack("<I", fip_bin[e.addr : e.end])[0]
        if blcp_img_size:
            start = self.read_end
            self.read_end = start + blcp_img_size
            self.body1["BLCP"].content = fip_bin[start : self.read_end]

        # Read FSBL as BL2
        e = self.param1["BL2_IMG_SIZE"]
        bl2_img_size = unpack("<I", fip_bin[e.addr : e.end])[0]
        if bl2_img_size:
            start = self.read_end
            self.read_end = start + bl2_img_size
            self.body1["BL2"].content = fip_bin[start : self.read_end]

        logging.info("read_fip end=%#x", self.read_end)
        self.rest_fip = fip_bin[self.read_end :]

        self.read_fip2(fip_bin)

    def read_fip2(self, fip_bin):
        param2_loadaddr = self.param1["PARAM2_LOADADDR"].toint()
        param2_bin = fip_bin[param2_loadaddr : param2_loadaddr + PARAM2_SIZE]

        for e in self.param2.values():
            e.content = param2_bin[e.addr : e.end]

        self.read_end = param2_loadaddr + PARAM2_SIZE

        # Read DDR_PARAM, BLCP_2ND, and MONITOR
        for name in ["DDR_PARAM", "BLCP_2ND", "MONITOR"]:
            size = self.param2[name + "_SIZE"].toint()
            loadaddr = self.param2[name + "_LOADADDR"].toint()
            self.body2[name].content = fip_bin[loadaddr : loadaddr + size]
            self.read_end = loadaddr + size

        # Read LOADER_2ND
        loader_2nd_loadaddr = self.param2["LOADER_2ND_LOADADDR"].toint()
        if loader_2nd_loadaddr:
            self.read_loader_2nd(fip_bin)

        logging.info("read_fip2 end=%#x", self.read_end)
        self.rest_fip = fip_bin[self.read_end :]

    def read_loader_2nd(self, fip_bin):
        loader_2nd_loadaddr = self.param2["LOADER_2ND_LOADADDR"].toint()

        self._parse_ldr_2nd_hdr(fip_bin[loader_2nd_loadaddr:])

        if self.ldr_2nd_hdr["MAGIC"].content not in LOADER_2ND_MAGIC_LIST:
            raise ValueError("%r" % self.ldr_2nd_hdr["MAGIC"].content)

        ldr_2nd_size = self.ldr_2nd_hdr["SIZE"].toint()

        self.body2["LOADER_2ND"].content = fip_bin[loader_2nd_loadaddr : loader_2nd_loadaddr + ldr_2nd_size]

        self.read_end = loader_2nd_loadaddr + ldr_2nd_size
        self.rest_fip = fip_bin[self.read_end :]

    def add_chip_conf(self, args):
        logging.debug("add_chip_conf:")

        with open(args.CHIP_CONF, "rb") as fp:
            image = fp.read()

        if image.startswith(b"APLB"):
            image = image[8:]  # strip old BLP header

        self.param1["CHIP_CONF"].content = image

    def add_blcp(self, args):
        logging.debug("add_blcp:")

        with open(args.BLCP, "rb") as fp:
            image = fp.read()

        image = self.pad(image, IMAGE_ALIGN)

        self.param1["BLCP_IMG_RUNADDR"].content = args.BLCP_IMG_RUNADDR
        self.body1["BLCP"].content = image

    def add_bl2(self, args):
        logging.debug("add_bl2:")

        with open(args.BL2, "rb") as fp:
            image = fp.read()

        bl2_fill = 0
        if args.BL2_FILL:
            bl2_fill = args.BL2_FILL

        image += b"\xA9" * (bl2_fill - len(image))
        image = self.pad(image, IMAGE_ALIGN)

        self.body1["BL2"].content = image

    def add_nor_info(self, args):
        logging.debug("add_nor_info:")
        self.param1["NOR_INFO"].content = args.NOR_INFO

    def add_nand_info(self, args):
        logging.debug("add_nand_info:")
        self.param1["NAND_INFO"].content = args.NAND_INFO

    def update_param1_cksum(self, image):
        image = bytearray(image)
        crc = self.image_crc(image[self.param1["NAND_INFO"].addr : PARAM1_SIZE_WO_SIG])

        param_cksum = self.param1["PARAM_CKSUM"]
        param_cksum.content = crc
        image[param_cksum.addr : param_cksum.end] = crc
        return image

    def make_fip1(self):
        logging.debug("make_fip1:")

        chip_conf = self.param1["CHIP_CONF"].content
        self.param1["CHIP_CONF_SIZE"].content = len(chip_conf)

        blcp = self.body1["BLCP"].content
        self.param1["BLCP_IMG_CKSUM"].content = self.image_crc(blcp)
        self.param1["BLCP_IMG_SIZE"].content = len(blcp)

        bl2 = self.body1["BL2"].content
        self.param1["BL2_IMG_CKSUM"].content = self.image_crc(bl2)
        self.param1["BL2_IMG_SIZE"].content = len(bl2)

        # Pack body1
        body1_bin = b""
        for entry in self.body1.values():
            if len(entry.content) % IMAGE_ALIGN:
                raise ValueError("%s (%d) is not align to %d" % (entry.name, len(entry.content), IMAGE_ALIGN))

            logging.info("add %s (%#x)", entry.name, len(entry.content))
            body1_bin += entry.content

        logging.debug("len(body1_bin) is %d", len(body1_bin))

        # Param1 cksum
        param1_bin = b"".join((entry.content for entry in self.param1.values()))
        param1_bin = self.update_param1_cksum(param1_bin)

        if len(param1_bin) != PARAM1_SIZE:
            raise ValueError("param1_bin is %d bytes" % len(param1_bin))

        fip1_bin = param1_bin + body1_bin
        logging.debug("len(fip1_bin) is %d", len(fip1_bin))

        return fip1_bin

    def add_ddr_param(self, args):
        with open(args.DDR_PARAM, "rb") as fp:
            ddr_param = fp.read()

        logging.debug("ddr_param=%#x bytes", len(ddr_param))
        self.body2["DDR_PARAM"].content = ddr_param

    def add_blcp_2nd(self, args):
        with open(args.BLCP_2ND, "rb") as fp:
            blcp_2nd = fp.read()

        logging.debug("blcp_2nd=%#x bytes", len(blcp_2nd))
        self.body2["BLCP_2ND"].content = blcp_2nd

    def add_monitor(self, args):
        with open(args.MONITOR, "rb") as fp:
            monitor = fp.read()

        logging.debug("monitor=%#x bytes", len(monitor))
        self.body2["MONITOR"].content = monitor

    def add_loader_2nd(self, args):
        with open(args.LOADER_2ND, "rb") as fp:
            loader_2nd = fp.read()

        logging.debug("loader_2nd=%#x bytes", len(loader_2nd))

        e = self.ldr_2nd_hdr["MAGIC"]
        magic = loader_2nd[e.addr : e.end]
        if magic != LOADER_2ND_MAGIC_ORIG:
            raise ValueError("loader_2nd's magic should be %r, but %r" % (LOADER_2ND_MAGIC_ORIG, magic))

        self.compress_algo = args.compress
        self.body2["LOADER_2ND"].content = loader_2nd

    def pack_ddr_param(self, fip_bin):
        if not len(self.body2["DDR_PARAM"].content):
            return

        fip_bin = self.pad(fip_bin, IMAGE_ALIGN)

        # Pack DDR_PARAM to body2
        ddr_param = self.pad(self.body2["DDR_PARAM"].content, IMAGE_ALIGN)

        self.param2["DDR_PARAM_CKSUM"].content = self.image_crc(ddr_param)
        self.param2["DDR_PARAM_SIZE"].content = len(ddr_param)
        self.param2["DDR_PARAM_LOADADDR"].content = len(fip_bin)

        return fip_bin + ddr_param

    def pack_blcp_2nd(self, fip_bin, blcp_2nd_runaddr):
        logging.debug("pack_blcp_2nd:")
        if not len(self.body2["BLCP_2ND"].content):
            return

        runaddr = int(blcp_2nd_runaddr)

        fip_bin = self.pad(fip_bin, IMAGE_ALIGN)

        # Pack MONITOR to body2
        body = self.pad(self.body2["BLCP_2ND"].content, IMAGE_ALIGN)

        self.param2["BLCP_2ND_CKSUM"].content = self.image_crc(body)
        self.param2["BLCP_2ND_SIZE"].content = len(body)
        self.param2["BLCP_2ND_LOADADDR"].content = len(fip_bin)
        self.param2["BLCP_2ND_RUNADDR"].content = runaddr

        return fip_bin + body

    def pack_monitor(self, fip_bin, monitor_runaddr):
        logging.debug("pack_monitor:")
        if not len(self.body2["MONITOR"].content):
            return

        monitor_runaddr = int(monitor_runaddr)

        fip_bin = self.pad(fip_bin, IMAGE_ALIGN)

        # Pack MONITOR to body2
        monitor = self.pad(self.body2["MONITOR"].content, IMAGE_ALIGN)

        self.param2["MONITOR_CKSUM"].content = self.image_crc(monitor)
        self.param2["MONITOR_SIZE"].content = len(monitor)
        self.param2["MONITOR_LOADADDR"].content = len(fip_bin)
        self.param2["MONITOR_RUNADDR"].content = monitor_runaddr

        return fip_bin + monitor

    def _parse_ldr_2nd_hdr(self, image):
        for e in self.ldr_2nd_hdr.values():
            e.content = image[e.addr : e.end]

    def _update_ldr_2nd_hdr(self):
        image = self.body2["LOADER_2ND"].content
        hdr_size = self._param_size(self.ldr_2nd_hdr)
        hdr, body = image[:hdr_size], image[hdr_size:]

        # Update SIZE
        self.ldr_2nd_hdr["SIZE"].content = len(image)

        # Update CKSUM
        hdr = bytearray(b"".join((e.content for e in self.ldr_2nd_hdr.values())))
        # CKSUM is calculated after "CKSUM" field
        hdr_cksum = self.ldr_2nd_hdr["CKSUM"]
        crc = self.image_crc((hdr + body)[hdr_cksum.end :])
        hdr_cksum.content = crc
        hdr = bytearray(b"".join((e.content for e in self.ldr_2nd_hdr.values())))

        self.body2["LOADER_2ND"].content = hdr + body

    def _compress_ldr_2nd(self):
        image = self.body2["LOADER_2ND"].content
        hdr_size = self._param_size(self.ldr_2nd_hdr)
        hdr, body = image[:hdr_size], image[hdr_size:]

        magic = self.ldr_2nd_hdr["MAGIC"].content
        if magic == LOADER_2ND_MAGIC_ORIG:
            # if image is uncompressed, compress it.
            if self.compress_algo is None:
                pass
            elif self.compress_algo == "lzma":
                self.ldr_2nd_hdr["MAGIC"].content = LOADER_2ND_MAGIC_LZMA
                body = lzma_compress(body)
                logging.info("lzma loader_2nd=%#x bytes wo header", len(body))
            elif self.compress_algo == "lz4":
                self.ldr_2nd_hdr["MAGIC"].content = LOADER_2ND_MAGIC_LZ4
                body = lz4_compress(body)
                logging.info("lz4 loader_2nd=%#x bytes wo header", len(body))
            else:
                raise NotImplementedError("'%r' is not supported." % self.compress_algo)
        elif magic in LOADER_2ND_MAGIC_LIST:
            logging.info("loader_2nd is already compressed")
        else:
            raise ValueError("unknown loader_2nd magic (%r)", magic)

        self.body2["LOADER_2ND"].content = self.pad(hdr + body, IMAGE_ALIGN)

    def pack_loader_2nd(self, fip_bin):
        logging.debug("pack_loader_2nd:")
        if not len(self.body2["LOADER_2ND"].content):
            return

        fip_bin = self.pad(fip_bin, IMAGE_ALIGN)
        self.param2["LOADER_2ND_LOADADDR"].content = len(fip_bin)

        self._parse_ldr_2nd_hdr(self.body2["LOADER_2ND"].content)
        self._compress_ldr_2nd()
        self._update_ldr_2nd_hdr()

        # Append LOADER_2ND to body2
        return fip_bin + self.body2["LOADER_2ND"].content

    def insert_param1(self, fip_bin, name, value):
        fip_bin = bytearray(fip_bin)
        e = self.param1[name]
        e.content = value
        fip_bin[e.addr : e.end] = value
        return self.update_param1_cksum(fip_bin)

    def append_fip2(self, fip1_bin, args):
        logging.debug("make_fip2:")
        fip_bin = bytearray(fip1_bin)

        # Update PARAM2_LOADADDR
        param2_loadaddr = len(fip1_bin)
        fip_bin = self.insert_param1(fip_bin, "PARAM2_LOADADDR", pack("<I", param2_loadaddr))

        # Add an empty PARAM2
        fip_bin += b"\0" * PARAM2_SIZE

        # Pack body
        fip_bin = self.pack_ddr_param(fip_bin)

        if len(self.body2["BLCP_2ND"].content):
            runaddr = self.param2["BLCP_2ND_RUNADDR"].toint()
            if not runaddr:
                runaddr = int(args.BLCP_2ND_RUNADDR)
            fip_bin = self.pack_blcp_2nd(fip_bin, runaddr)

        if len(self.body2["MONITOR"].content):
            runaddr = self.param2["MONITOR_RUNADDR"].toint()
            if not runaddr:
                runaddr = int(args.MONITOR_RUNADDR)
            fip_bin = self.pack_monitor(fip_bin, runaddr)

        if len(self.body2["LOADER_2ND"].content):
            fip_bin = self.pack_loader_2nd(fip_bin)

        # Pack param2_bin
        param2_bin = b"".join((entry.content for entry in self.param2.values()))
        self.param2["PARAM2_CKSUM"].content = self.image_crc(param2_bin[self.param2["PARAM2_CKSUM"].end :])
        param2_bin = b"".join((entry.content for entry in self.param2.values()))  # update cksum

        logging.debug("len(param2_bin) is %d", len(param2_bin))
        assert len(param2_bin) == PARAM2_SIZE

        fip_bin[param2_loadaddr : param2_loadaddr + PARAM2_SIZE] = param2_bin

        return fip_bin

    def make(self, args=None):
        fip_bin = self.make_fip1()
        if len(self.body2["DDR_PARAM"].content):
            fip_bin = self.append_fip2(fip_bin, args)

        logging.info("generated fip_bin is %d bytes", len(fip_bin))

        if getattr(self, "rest_fip", None):
            logging.error("the rest of fip is not used: %#x bytes ", len(self.rest_fip))

        return fip_bin


METHODS = {
    "NOR_INFO": FIP.add_nor_info,
    "NAND_INFO": FIP.add_nand_info,
    "CHIP_CONF": FIP.add_chip_conf,
    "BLCP": FIP.add_blcp,
    "BL2": FIP.add_bl2,
    "DDR_PARAM": FIP.add_ddr_param,
    "BLCP_2ND": FIP.add_blcp_2nd,
    "MONITOR": FIP.add_monitor,
    "LOADER_2ND": FIP.add_loader_2nd,
}


def generate_fip(args):
    logging.debug("generate_fip:")
    fip = FIP()

    if args.OLD_FIP:
        fip.read_fip(args.OLD_FIP)

    for m, f in METHODS.items():
        if getattr(args, m):
            f(fip, args)

    fip_bin = fip.make(args)
    fip.print_fip_params()

    if args.output:
        with open(args.output, "wb") as fp:
            fp.write(fip_bin)


def parse_args():
    parser = argparse.ArgumentParser(description="FIP tools")

    parser.add_argument(
        "-v",
        "--verbose",
        help="Increase output verbosity",
        action="store_const",
        const=logging.DEBUG,
        default=logging.INFO,
    )

    subparsers = parser.add_subparsers(dest="subcmd", help="Sub-command help")
    pr_gen = subparsers.add_parser("genfip", help="Generate keys")

    for name in list(METHODS):
        if name in ["NOR_INFO", "NAND_INFO"]:
            pr_gen.add_argument("--" + name, type=bytes.fromhex)
        else:
            pr_gen.add_argument("--" + name, dest=name, type=str, help="Add %s into FIP" % name)

    def auto_int(x):
        return int(x, 0)

    pr_gen.add_argument("--BLCP_IMG_RUNADDR", type=auto_int)
    pr_gen.add_argument("--BLCP_PARAM_LOADADDR", type=auto_int)

    pr_gen.add_argument("--BLCP_2ND_RUNADDR", type=auto_int)

    pr_gen.add_argument("--MONITOR_RUNADDR", type=auto_int)

    pr_gen.add_argument("--compress", choices=["lzma", "lz4", ""])

    pr_gen.add_argument("--OLD_FIP", type=str)
    pr_gen.add_argument("--BLOCK_SIZE", type=auto_int)
    pr_gen.add_argument("--BL2_FILL", type=auto_int)

    pr_gen.add_argument("output", type=str, help="Output filename")

    pr_gen.set_defaults(func=generate_fip)

    if argcomplete:
        argcomplete.autocomplete(parser)

    args = parser.parse_args()
    init_logging(stdout_level=args.verbose)
    logging.info("PROG: %s", parser.prog)

    if not args.subcmd:
        parser.print_help()
        raise SystemExit(1)

    for a, v in sorted(vars(args).items()):
        logging.debug("  %s=%r", a, v)

    return args


def main():
    args = parse_args()
    args.func(args)


def init_logging(log_file=None, file_level="DEBUG", stdout_level="WARNING"):
    root_logger = logging.getLogger()
    root_logger.setLevel(logging.NOTSET)

    fmt = "%(asctime)s %(levelname)8s:%(name)s:%(message)s"

    if log_file is not None:
        file_handler = logging.FileHandler(log_file, encoding="utf-8")
        file_handler.setFormatter(logging.Formatter(fmt))
        file_handler.setLevel(file_level)
        root_logger.addHandler(file_handler)

    if coloredlogs:
        os.environ["COLOREDLOGS_DATE_FORMAT"] = "%H:%M:%S"

        field_styles = {
            "asctime": {"color": "green"},
            "hostname": {"color": "magenta"},
            "levelname": {"color": "black", "bold": True},
            "name": {"color": "blue"},
            "programname": {"color": "cyan"},
        }

        level_styles = coloredlogs.DEFAULT_LEVEL_STYLES
        level_styles["debug"]["color"] = "cyan"

        coloredlogs.install(
            level=stdout_level,
            fmt=fmt,
            field_styles=field_styles,
            level_styles=level_styles,
            milliseconds=True,
        )


if __name__ == "__main__":
    main()
