# NOTE: This script is test under Python 3.x

__copyright__ = "Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved"

import sys
import crcmod


class UnpackImage:

    def __init__(self, pack_file_name, nocrc):
        self.img_list = []
        try:
            with open(pack_file_name, "rb") as pack_file:
                self.pack_data = pack_file.read()
        except (IOError, OSError) as err:
            print(f"Open {pack_file_name} failed")
            sys.exit(err)

        if self.pack_data[0:4] != b'\x20\x54\x56\x4e':
            print(f"{pack_file_name} marker check failed")
            sys.exit(0)

        print("Waiting for unpack Images ...")
        if nocrc == 0:
            print("check pack file crc32 ...")
            crc32_func = crcmod.predefined.mkCrcFun('crc-32')
            checksum = crc32_func(self.pack_data[8:])
            if checksum != int.from_bytes(self.pack_data[4:8], byteorder='little'):
                print(f"{pack_file_name} CRC check failed")
                sys.exit(0)
        self.image_cnt = int.from_bytes(self.pack_data[8:12], byteorder='little')
        # 1st image descriptor begins @ 0x10
        index = 0x10
        for _ in range(self.image_cnt):
            # Put the image length, offset ,attribute in list
            self.img_list.append([int.from_bytes(self.pack_data[index: index + 8], byteorder='little'),
                                  int.from_bytes(self.pack_data[index + 8: index + 16], byteorder='little'),
                                  int.from_bytes(self.pack_data[index + 16: index + 20], byteorder='little'),
                                  index + 24])
            index += int.from_bytes(self.pack_data[index: index + 8], byteorder='little') + 24  # 24 is image header
            if index % 16 != 0:
                index += 16 - (index & 0xF)   # round to 16-byte align

    def img_count(self):
        return self.image_cnt

    def img_attr(self, index):
        if index < self.image_cnt:
            # No need to return the last entry, actual offset in image file.
            # And should return integers instead of list of integer here
            return self.img_list[index][0], self.img_list[index][1], self.img_list[index][2]
        else:
            print("Invalid image index")
            return 0, 0, 0

    def img_content(self, index, offset, size):
        if index >= self.image_cnt:
            print("Invalid image index")
            return ''
        if offset > self.img_list[index][0] or offset + size > self.img_list[index][0]:
            print("Invalid offset")
            return ''

        return self.pack_data[self.img_list[index][3] + offset: self.img_list[index][3] + offset + size]
