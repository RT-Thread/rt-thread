# -*- coding:utf-8 -*_
#
# W600 make img script
# Copyright (c) 2018 Winner Micro Electronic Design Co., Ltd.
# All rights reserved.
#
#                                   image header structure
# --------------------------------------------------------------------------------------------
# | magic number(4B)  | image type(2B)| zip type(2B) | run image addr(4B) | run image len(4B) |
# --------------------------------------------------------------------------------------------
# | run image crc(4B) |  update image addr(4B)  | update image len(4B) | update image crc(4B) |
# ---------------------------------------------------------------------------------------------
# | update no(4B)     |                     ver(16B)                                          |
# ---------------------------------------------------------------------------------------------
# 
#
#               FLS File structure
#    ----------------------------------------------
#    |      FLS file header (image header)          |
#    ------------------------------------
#    |      secboot header (image header)           |
#    ------------------------------------
#    |      256-sizeof(image header) pad 0xFF       |
#    ------------------------------------
#    |      secboot img area-(56*1024 - 256)        |
#    ------------------------------------
#    |  application image header (image header)     |
#    ------------------------------------
#    |      256-sizeof(image heager)-pad 0xFF       |
#    ------------------------------------
#    |              application image               |
#    ------------------------------------------------
#
#

import sys
import os
import struct
from zlib import crc32

secboot_img_addr = 0x2100
secboot_header_len = 0x100
secboot_header_pos = secboot_img_addr - secboot_header_len
secboot_img_total_len = 56*1024
run_img_header_len = 0x100
magic_no = 0xA0FFFF9F


def main(argv):
    if(len(argv) != 4):
        print("param cnt error")
        print("param 0: .py")
        print("param 1: input \"secboot.img\" file")
        print("param 2: input image file")
        print("param 3: output FLS file")
        raise Exception("param cnt error!")

    # second boot
    try:
        f_sec = open(argv[1], "rb+")
    except IOError:
        print("not find %s file" % argv[1])
        raise
    else:
        magic_word = f_sec.read(4)
        magic, = struct.unpack('<I', magic_word)
        if magic != magic_no:
            f_sec.close()
            raise Exception("input %s file error" % argv[1])

    # app image
    try:
        f_app=open(argv[2], "rb+")
    except IOError:
        f_sec.close()
        print("not find %s file" % argv[2])
        raise
    else:
        magic_word=f_app.read(4)
        magic, = struct.unpack('<I', magic_word)
        if magic != magic_no:
            f_sec.close()
            f_app.close()
            raise Exception("input %s file error" % argv[1])

    appimg_len=os.path.getsize(argv[2])

    # create outfile
    try:
        f_out=open(argv[3], 'wb+')
    except IOError:
        f_app.close()
        f_sec.close()
        print("create %s file error" % argv[3])
        raise
    else:
        final_len=secboot_img_total_len + appimg_len
        data = struct.pack('<B', 0xff) * final_len
        f_out.write(data)

        # Write SECBOOT header to output file
        f_out.seek(56)
        f_sec.seek(0)
        f_out.write(f_sec.read(56))

        # Write SECBOOT image to output file
        f_out.seek(56 + 256)
        f_out.write(f_sec.read())

        # Write run img header to output file
        f_out.seek(56 + secboot_img_total_len)
        f_app.seek(0)
        f_out.write(f_app.read(56))

        # Write run img to output file
        f_out.seek(56 + secboot_img_total_len + run_img_header_len)
        f_out.write(f_app.read())

        # Calculate CRC from secboot header
        f_out.seek(56)
        out_data = f_out.read()
        out_crc = crc32(out_data) ^ (0xFFFFFFFF)
        out_len = len(out_data)
        #print(hex(out_crc))

        magic = struct.pack('<I', magic_no)
        img_type = struct.pack('<H', 0)
        zip_type = struct.pack('<H', 0)
        run_img_addr = struct.pack('<I', secboot_header_pos)
        upd_img_addr = struct.pack('<I', 0)
        upd_img_len = struct.pack('<I', 0)
        upd_checksum = struct.pack('<I', 0)
        upd_no = struct.pack('<I', 0)
        version = '\0' * 16
        ver_name = version.encode('utf-8')  
        run_img_len = struct.pack('<I', out_len)
        run_org_checksum = struct.pack('<I', out_crc)

        # image header crc
        image_header=magic + img_type + zip_type + run_img_addr + run_img_len \
            + run_org_checksum + upd_img_addr + upd_img_len + upd_checksum \
            + upd_no + ver_name

        header_crc=crc32(image_header) ^ (0xFFFFFFFF)

        # Write fls's header to output file
        f_out.seek(0)
        f_out.write(image_header)
        f_out.write(struct.pack('<I', header_crc))

        f_sec.close()
        f_app.close()
        f_out.close()
        print("create %s file success!" % argv[3])
        print("%s size:%dKB. %s size:%dKB" % (argv[2], appimg_len / 1024.0 , argv[3], final_len / 1024.0))


if __name__ == '__main__':
    main(sys.argv)
