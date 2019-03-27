# -*- coding:utf-8 -*-
#
# W600 make img script
# Copyright (c) 2018 Winner Micro Electronic Design Co., Ltd.
# All rights reserved.
#
#                                 image header structure
# --------------------------------------------------------------------------------------------
# | magic number(4B)  | image type(2B)| zip type(2B) | run image addr(4B) | run image len(4B) |
# --------------------------------------------------------------------------------------------
# | run image crc(4B) |  update image addr(4B)  | update image len(4B) | update image crc(4B) |
# ---------------------------------------------------------------------------------------------
# | update no(4B)     |                     ver(16B)                                          |
# ---------------------------------------------------------------------------------------------
# |                                   run code                                                |
# ---------------------------------------------------------------------------------------------
#

import sys
import os
import struct
from zlib import crc32

magic_no = 0xA0FFFF9F

def main(argv):
    if(len(argv) < 8):
        print("param cnt error")
        print("param 0:  .py")
        print("param 1:  input .bin file.(uncompressed file or compressed file)")
        print("param 2:  output file")
        print("param 3:  image type ,0：old param user image,1：reserved,2：secboot,3: new param user image")
        print("param 4:  compressed type,0：uncompressed file,1.compressed file")
        print("param 5:  firmware version file")
        print("param 6： input image storage address")
        print("param 7： input image running address")
        print("param 8： input original image file")
        raise Exception("param cnt error!")

    # version
    try:
        f_ver = open(argv[5], "r+")
    except IOError:
        print("not find %s file" % argv[5])
        raise
    else:
        version = f_ver.readline(20)
        p = version.rfind('.')
        if p == -1:
            version = '1.0.00'
            newversion = '1.0.01'
        else:
            newversion = version[:p+1]
            ver = int(version[p+1:]) + 1
            newversion = newversion + '{:0>2d}'.format(ver)
            #print(newversion)
            if len(newversion) < 16:
                newversion = newversion + '\0' * (16 - len(newversion))
                #print(len(newversion), newversion)
            else:
                newversion = newversion[:15] + '\0'
        f_ver.close()

    # bin file crc
    try:
        f_bin = open(argv[1], mode='rb')
    except IOError:
        print("not find %s file" % argv[1])
        raise
    else:
        bin_data = f_bin.read()
        bin_len = os.path.getsize(argv[1])
        bin_crc = crc32(bin_data) ^ (0xFFFFFFFF)
        # print(hex(bin_crc))

    magic = struct.pack('<I', magic_no)
    img_type = struct.pack('<H', int(argv[3]))
    zip_type = struct.pack('<H', int(argv[4]))
    # print(argv[7], int(argv[7] ,16))
    run_img_addr = struct.pack('<I', int(argv[7], 16))
    upd_img_addr = struct.pack('<I', int(argv[6], 16))
    upd_img_len = struct.pack('<I', bin_len)
    upd_checksum = struct.pack('<I', bin_crc)
    upd_no = struct.pack('<I', 0)
    ver_name = newversion.encode('utf-8')  
    # non-zip image
    if not int(argv[4]):
        run_img_len = struct.pack('<I', bin_len)
        run_org_checksum = struct.pack('<I', bin_crc)
    else:
        # zip image
        try:
            f_src = open(argv[8], 'rb+')
        except IOError:
            f_bin.close()
            print("not find %s file" % argv[8])
            raise
        else:
            src_data = f_src.read()
            src_len = os.path.getsize(argv[8])
            src_crc = crc32(src_data) ^ (0xFFFFFFFF)
            # print(src_data)
            f_src.close()

        run_img_len = struct.pack('<I', src_len)
        run_org_checksum = struct.pack('<I', src_crc)

    #image header crc
    image_header = magic + img_type + zip_type + run_img_addr + run_img_len \
                + run_org_checksum + upd_img_addr + upd_img_len + upd_checksum \
                + upd_no + ver_name

    header_crc = crc32(image_header) ^ (0xFFFFFFFF)

    try:
        f_img = open(argv[2], "wb+")
    except IOError:
        f_bin.close()
        print("create %s file fail" % argv[2])
        raise
    else:
        f_img.write(image_header)
        f_img.write(struct.pack('<I', header_crc))
        f_img.write(bin_data)

        # write dummy data to pad 4byte-aligned
        dummy = len(bin_data) % 4 
        if dummy != 0:
            dummy = 4 - len(bin_data) % 4
            f_img.write(struct.pack('<B', 0) * dummy)

        f_img.close()
        f_bin.close()
        print("image %s create success!" % argv[2])

if __name__ == '__main__':
    main(sys.argv)
