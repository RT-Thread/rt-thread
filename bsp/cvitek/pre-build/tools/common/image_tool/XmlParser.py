#!/usr/bin/python3
# -*- coding: utf-8 -*-
import logging
import os
import re
import sys
import xml.etree.ElementTree as ET

FORMAT = "%(levelname)s: %(message)s"
logging.basicConfig(level=logging.INFO, format=FORMAT)
Storage_EMMC = 0
Storage_SPINAND = 1
Storage_SPINOR = 2
LBA_SIZE = 512


class XmlParser:
    @staticmethod
    def parse_size(size):
        units = {"B": 1, "K": 2 ** 10, "M": 2 ** 20, "G": 2 ** 30, "T": 2 ** 40}
        size = size.upper()
        logging.debug("parsing size %s" % size)
        if not re.match(r" ", size):
            size = re.sub(r"([BKMGT])", r" \1", size)
            try:
                number, unit = [string.strip() for string in size.split()]
            except ValueError:
                number = size
                unit = "B"

        ret = int(float(number) * units[unit])

        return ret

    def parse(self, install=None):
        try:
            tree = ET.parse(self.xml)
        except Exception:
            logging.error(self.xml + " is not a vaild xml file")
            raise

        root = tree.getroot()
        self.storage = root.attrib["type"]
        install_dir = install
        parts = []
        for part in root:
            p = dict()
            if "size_in_kb" in part.attrib:
                p["part_size"] = int(part.attrib["size_in_kb"]) * 1024
            elif "size_in_b" in part.attrib:
                p["part_size"] = int(part.attrib["size_in_b"])
            else:
                p["part_size"] = sys.maxsize
                # Assign 0 means biggest number

            if part.attrib["file"] and install_dir is not None:
                path = os.path.join(install_dir, part.attrib["file"])
                try:
                    file_size = os.stat(path).st_size
                except Exception:
                    file_size = 0
                if file_size > p["part_size"]:
                    logging.error(
                        "Image: %s(%d) is larger than partition size(%d)"
                        % (part.attrib["file"], file_size, p["part_size"])
                    )
                    raise OverflowError
                p["file_path"] = path
                logging.debug("size of " + path + " : " + str(file_size))
            else:
                file_size = 0

            p["file_size"] = int(file_size)
            p["file_name"] = part.attrib["file"]
            p["label"] = part.attrib["label"]
            p["mountpoint"] = (
                part.attrib["mountpoint"] if "mountpoint" in part.attrib else None
            )
            p["type"] = part.attrib["type"] if "type" in part.attrib else ""
            p["options"] = part.attrib["options"] if "options" in part.attrib else None

            parts.append(p)

        if self.storage == "emmc":
            self.__calEmmcOffset(parts)
        elif self.storage == "spinor":
            self.__calNorOffset(parts)
        elif self.storage == "spinand":
            self.__calNandOffset(parts)
        elif self.storage == "sd":
            self.__calNandOffset(parts)
        elif self.storage == "none":
            self.__calNandOffset(parts)

        else:
            logging.error("Unknown storage type")
            raise ValueError(self.storage)
        for p in parts:
            self.parts[p["label"]] = p
        return parts

    def __calEmmcOffset(self, parts):
        # EMMC will program gpt in the beggining of the emmc, start from 8192
        start = 0
        for p in parts:
            p["offset"] = start
            start += p["part_size"]

    def __calNandOffset(self, parts):
        start = 0
        for p in parts:
            p["offset"] = start
            start += p["part_size"]

    def __calNorOffset(self, parts):
        start = 0
        for p in parts:
            p["offset"] = start
            start += p["part_size"]

    def getStorage(self):
        return self.storage

    def __init__(self, xml):
        self.xml = xml
        self.storage = "emmc"
        self.parts = dict()
