#!/usr/bin/env python3
# PYTHON_ARGCOMPLETE_OK

import logging
import argparse
from struct import unpack

from Crypto.Cipher import AES
from Crypto.Hash import SHA256
from Crypto.PublicKey import RSA
from Crypto.Signature import pkcs1_15

try:
    import argcomplete
except ImportError:
    argcomplete = None

from fiptool import FIP, IMAGE_ALIGN, init_logging

ENCRYPTION_KEY_SIZE = 16
ENCRYPTION_BLOCK_SIZE = 16
IV_ZERO = b"\0" * ENCRYPTION_BLOCK_SIZE


class SignedFIP(FIP):
    def __init__(self, root_priv_path, bl_priv_path):
        super().__init__()

        with open(root_priv_path, "rb") as fp:
            din = fp.read()
            self.root_priv = RSA.import_key(din)

        with open(bl_priv_path, "rb") as fp:
            din = fp.read()
            self.bl_priv = RSA.import_key(din)

    def read_fip(self, path):
        super().read_fip(path)

        # Verity the reading of fip.bin
        with open(path, "rb") as fp:
            assert fp.read() == self.make()

    def rsa_to_n(self, rsa):
        return rsa.n.to_bytes(rsa.size_in_bytes(), byteorder="big")

    def print_kpub_hash(self, bytes):
        bytes_str = ['{:02x}'.format(int(i)) for i in bytes]
        logging.info("KPUB_HASH:" + "".join(bytes_str))

    def sign_bl_pk(self):
        self.param1["ROOT_PK"].content = self.rsa_to_n(self.root_priv)
        kpub_hash = SHA256.new(self.param1["ROOT_PK"].content[:256])
        self.print_kpub_hash(kpub_hash.digest())

        self.param1["BL_PK"].content = self.rsa_to_n(self.bl_priv)

        digest = SHA256.new(self.rsa_to_n(self.bl_priv))

        sig = pkcs1_15.new(self.root_priv).sign(digest)
        self.param1["BL_PK_SIG"].content = sig

    def sign_by_bl_priv(self, image):
        digest = SHA256.new(image)
        return pkcs1_15.new(self.bl_priv).sign(digest)

    def sign(self):
        logging.info("sign fip.bin")

        self.param1["FIP_FLAGS"].content = self.FIP_FLAGS_SCS_MASK | self.param1["FIP_FLAGS"].toint()

        self.sign_bl_pk()

        cc = self.param1["CHIP_CONF"].content
        cc_size = unpack("<I", self.param1["CHIP_CONF_SIZE"].content)[0]
        logging.debug("CHIP_CONF_SIZE=%#x", cc_size)
        cc = cc[:cc_size]

        self.param1["CHIP_CONF_SIG"].content = self.sign_by_bl_priv(cc)
        self.param1["BL2_IMG_SIG"].content = self.sign_by_bl_priv(self.body1["BL2"].content)

        if self.body1["BLCP"].content:
            logging.debug("sign blcp")
            self.param1["BLCP_IMG_SIG"].content = self.sign_by_bl_priv(self.body1["BLCP"].content)

        self.sign_fip2()

    def sign_fip2(self):
        logging.debug("sign_fip2:")

        sig_size = len(self.rsa_to_n(self.bl_priv))

        for name in ["BLCP_2ND", "MONITOR"]:
            e = self.body2[name]
            if not e.content:
                continue

            logging.info("sign %s: len=%#x", name, len(e.content))

            image = bytearray(self.pad(e.content + b"\xCE" * sig_size, IMAGE_ALIGN))
            sig = self.sign_by_bl_priv(image[:-sig_size])
            assert sig_size == len(sig)
            image[-sig_size:] = sig

            e.content = image

        loader_2nd_loadaddr = self.param2["LOADER_2ND_LOADADDR"].toint()
        if loader_2nd_loadaddr:
            logging.info("sign %s at %#x", "LOADER_2ND_LOADADDR", loader_2nd_loadaddr)

            # Only data after CKSUM field are signed.
            # The value CKSUM include signature and is updated later.
            e = self.body2["LOADER_2ND"]
            e.content = self.pad(e.content + b"\xCE" * sig_size, IMAGE_ALIGN)
            # SIZE is after CKSUM, update it before signing
            self._update_ldr_2nd_hdr()

            image = bytearray(e.content)
            sig = self.sign_by_bl_priv(image[self.ldr_2nd_hdr["CKSUM"].end : -sig_size])
            assert sig_size == len(sig)
            image[-sig_size:] = sig

            e.content = image


class EncryptedFIP(SignedFIP):
    def __init__(self, root_priv_path, bl_priv_path, ldr_ek_path, bl_ek_path):
        super().__init__(root_priv_path, bl_priv_path)

        with open(ldr_ek_path, "rb") as fp:
            self.ldr_ek = fp.read()

        with open(bl_ek_path, "rb") as fp:
            self.bl_ek = fp.read()

    def _aes_encrypt(self, key, plain):
        return AES.new(key, iv=IV_ZERO, mode=AES.MODE_CBC).encrypt(plain)

    def encrypt(self):
        logging.debug("encrypt:")

        self.param1["FIP_FLAGS"].content = self.FIP_FLAGS_ENCRYPTED_MASK | self.param1["FIP_FLAGS"].toint()

        self.param1["BL_EK"].content = self._aes_encrypt(self.ldr_ek, self.bl_ek)
        self.body1["BL2"].content = self._aes_encrypt(self.bl_ek, self.body1["BL2"].content)

        for name in ["BLCP_2ND", "MONITOR"]:
            e = self.body2[name]
            if not e.content:
                continue

            logging.info("encrypt %s: len=%#x", name, len(e.content))
            e.content = self._aes_encrypt(self.bl_ek, e.content)

        loader_2nd_loadaddr = self.param2["LOADER_2ND_LOADADDR"].toint()
        if loader_2nd_loadaddr:
            logging.info("encrypt %s at %#x", "LOADER_2ND_LOADADDR", loader_2nd_loadaddr)

            # Only data after header are encrypted
            e = self.body2["LOADER_2ND"]

            hdr_size = self._param_size(self.ldr_2nd_hdr)
            hdr, body = e.content[:hdr_size], e.content[hdr_size:]

            body = self._aes_encrypt(self.bl_ek, body)
            e.content = hdr + body


def sign_fip(args):
    logging.debug("sign_fip:")

    fip = SignedFIP(args.root_priv, args.bl_priv)
    fip.read_fip(args.SRC_FIP)

    fip.sign()

    fip_bin = fip.make()
    fip.print_fip_params()
    with open(args.DEST_FIP, "wb") as fp:
        fp.write(fip_bin)


def encrypt_fip(args):
    logging.debug("encrypt_fip:")

    fip = EncryptedFIP(args.root_priv, args.bl_priv, args.ldr_ek, args.bl_ek)
    fip.read_fip(args.SRC_FIP)

    fip.sign()
    fip.encrypt()

    fip_bin = fip.make()
    fip.print_fip_params()
    with open(args.DEST_FIP, "wb") as fp:
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

    def auto_int(x):
        return int(x, 0)

    subparsers = parser.add_subparsers(dest="subcmd", help="Sub-command help")

    pr_encrypt = subparsers.add_parser("sign-enc")
    pr_encrypt.set_defaults(func=encrypt_fip)
    pr_encrypt.add_argument("--ldr-ek", type=str)
    pr_encrypt.add_argument("--bl-ek", type=str)

    pr_sign = subparsers.add_parser("sign")
    pr_sign.set_defaults(func=sign_fip)

    for pr in [pr_sign, pr_encrypt]:
        pr.add_argument("--root-priv", type=str)
        pr.add_argument("--bl-priv", type=str)
        pr.add_argument("SRC_FIP", type=str, help="Source fip.bin")
        pr.add_argument("DEST_FIP", type=str, help="Signed fip.bin")

    if argcomplete:
        argcomplete.autocomplete(parser)

    args = parser.parse_args()
    init_logging(stdout_level=args.verbose)
    logging.info("PROG: %s", parser.prog)

    if not args.subcmd:
        parser.print_help()
        raise SystemExit(1)

    for a, v in sorted(vars(args).items()):
        logging.debug("%s=%r", a, v)

    return args


def main():
    args = parse_args()
    args.func(args)


if __name__ == "__main__":
    main()
