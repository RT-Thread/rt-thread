# NOTE: This script is test under Python 3.x

__copyright__ = "Copyright (C) 2020~2021 Nuvoton Technology Corp. All rights reserved"

import sys
import usb.core
import usb.util
import json
import typing

XFER_LEN_CMD = 0x0012
GET_INFO_CMD = 0x0005


class XUsbCom:

    def __init__(self, _dev):
        self.dev = _dev
        self.write_addr = 0x1
        self.read_addr = 0x81
        self.attach = False
        self.id = 0
        self.info = b''

    def write(self, data) -> None:
        try:
            # Vendor command set transfer length
            self.dev.ctrl_transfer(0x40, 0xA0, wValue=XFER_LEN_CMD, wIndex=len(data), data_or_wLength='')
            # Actual data
            self.dev.write(self.write_addr, data, timeout=1000)
        except usb.core.USBError as err:
            sys.exit(err)

    def read(self, size) -> bytes:
        try:
            buf = self.dev.read(self.read_addr, size, timeout=1000)
        except usb.core.USBError as err:
            sys.exit(err)
        return buf

    def set_media(self, media) -> None:
        try:
            # Vendor command set type
            self.dev.ctrl_transfer(0x40, 0xB0, wValue=media, wIndex=0, data_or_wLength='')
        except usb.core.USBError as err:
            sys.exit(err)
        return

    def get_info(self, data) -> bytes:
        try:
            self.dev.ctrl_transfer(0x40, 0xB0, wValue=GET_INFO_CMD, wIndex=0, data_or_wLength='')
            self.dev.ctrl_transfer(0x40, 0xA0, wValue=XFER_LEN_CMD, wIndex=76, data_or_wLength='')
            self.dev.write(0x01, data, timeout=1000)
            self.info = self.dev.read(0x81, 76, timeout=1000)
            # not used
            self.dev.read(0x81, 4, timeout=5000)

        except usb.core.USBError as err:
            sys.exit(err)
        return self.info

    def set_id(self, i) -> None:
        self.id = i

    def get_id(self) -> int:
        return self.id

    @staticmethod
    def set_align(nand, spinand) -> None:
        # See if we need to overwrite existing json file.
        overwrite = False
        try:
            with open(".config", "r") as json_file:
                cfg = json.load(json_file)
            for key in cfg.keys():
                if key == 'nand_align':
                    if nand != int(cfg['nand_align']):
                        overwrite = True
                elif key == 'spinand_align':
                    if spinand != int(cfg['spinand_align']):
                        overwrite = True
        except (IOError, OSError, json.decoder.JSONDecodeError) as err:
            overwrite = True

        if overwrite is True:
            try:
                with open(".config", "w+") as json_file:
                    new_key = {'nand_align': nand, 'spinand_align': spinand}
                    json.dump(new_key, json_file)
            except (IOError, OSError) as err:
                print("Write .config failed. Please re-attach")
                sys.exit(err)

    @staticmethod
    def get_align() -> typing.Tuple[int, int]:
        try:
            with open(".config", "r") as json_file:
                cfg = json.load(json_file)
        except (IOError, OSError, json.decoder.JSONDecodeError) as err:
            print("Open/parsing .config failed. Please re-attach")
            sys.exit(err)
        nand_align = spinand_align = 0
        for key in cfg.keys():
            if key == 'nand_align':
                nand_align = int(cfg['nand_align'])
            elif key == 'spinand_align':
                spinand_align = int(cfg['spinand_align'])
        return nand_align, spinand_align


class XUsbComList:

    def __init__(self, attach_all=False):
        vid = 0x0416
        pid = 0x5963
        try:
            self.devices = list(usb.core.find(idVendor=vid, idProduct=pid,
                                              find_all=True if attach_all is True else False))
        except TypeError:
            # list will raise exception if there's no device
            self.devices = []
            return
        except usb.core.NoBackendError as err:
            sys.exit(err)

        if len(self.devices) != 0 and attach_all is False:
            # Object type return on attach_all == False is different
            self.devices[0] = self.devices[0].device

        for dev in self.devices:
            try:
                dev.set_configuration()
            except (usb.core.USBError, NotImplementedError) as err:
                sys.exit(err)

        for i in range(0, len(self.devices)):
            self.devices[i] = XUsbCom(self.devices[i])
            self.devices[i].set_id(i)

    def __del__(self):
        if len(self.devices) != 0:
            for dev in self.devices:
                try:
                    usb.util.dispose_resources(dev.dev)
                    # dev.dev.reset()
                    dev = None
                #except (usb.core.USBError, NotImplementedError) as err:
                except usb.core.USBError as err:
                    sys.exit(err)

        self.devices = None

    def get_dev(self):
        return self.devices
