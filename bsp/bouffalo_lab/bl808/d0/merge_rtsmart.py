import os
import sys

compress_flag = 0

def create_flash_default_data(length):
    datas = bytearray(length)
    for i in range(length):
        datas[i] = 0xff
    return datas

def gen_flash_bin():
    bootload_file = "./pre_build_bin/spl_bl808_d0.bin"
    dtb_file = "./pre_build_bin/hw.dtb.5M"                  # 64k
    opensbi_file = "./pre_build_bin/opensbi_v0.6.bin"       # 64k
    kernel_file = "./Image.bin"

    kernel_out_img_file = "./whole_img_d0.bin"

    bootload_file_size = os.stat(bootload_file).st_size
    dtb_file_size = os.stat(dtb_file).st_size
    linux_opensbi_file_size = os.stat(opensbi_file).st_size
    kernel_file_size = os.stat(kernel_file).st_size

    whole_img_data = create_flash_default_data(0x10000 + 0x10000 + 0x10000 + kernel_file_size)

    # bootload
    print("bootload size:", bootload_file_size)
    fp = open(bootload_file, 'rb')
    data00 = fp.read() + bytearray(0)
    fp.close()
    whole_img_data[0x0:0x0+len(data00)] = data00  # 0x0~0x10000 64k    

    # dtb
    print("dtb size:", dtb_file_size)
    fp = open(dtb_file, 'rb')
    data0 = fp.read() + bytearray(0)
    fp.close()
    whole_img_data[0x10000:0x10000+len(data0)] = data0  # 0x0~0x10000 64k

    # opensbi
    print("opensbi size:",linux_opensbi_file_size)
    fp = open(opensbi_file, 'rb')
    data1 = fp.read() + bytearray(0)
    fp.close()
    whole_img_data[0x20000:0x20000+len(data1)] = data1  # 0x10000~0x20000 64k

    # linux kernel
    print("kernel img size:",kernel_file_size)

    b0 = (kernel_file_size & 0xff000000) >> 24
    b1 = (kernel_file_size & 0xff0000) >> 16
    b2 = (kernel_file_size & 0xff00) >> 8
    b3 = kernel_file_size & 0xff
    # print(b0)
    # print(b1)
    # print(b2)
    # print(b3)
    header2 = [0x00,0x00,0x00,compress_flag,b3,b2,b1,b0]
    whole_img_data[0x2fff8:0x30000] = bytearray((header2)) # image header
    fp = open(kernel_file, 'rb')
    data2 = fp.read() + bytearray(0)
    fp.close()
    whole_img_data[0x30000:0x30000+len(data2)] = data2 # 4M

    fp = open(kernel_out_img_file, 'wb+')
    fp.write(whole_img_data)
    fp.close()

if __name__ == '__main__':
    if(len(sys.argv) < 2):
        compress_flag = 0
        os.system('cp -rf rtthread_d0.bin Image.bin')
    else:
        if int(sys.argv[1]) == 1:
            print("compress mode...")
            compress_flag = 1
            os.system('lz4 -9 -f rtthread_d0.bin Image.bin')
        else:
            compress_flag = 0
            os.system('cp -rf rtthread_d0.bin Image.bin')

    print("merge bin start...")
    gen_flash_bin()
    print("merge done!")

    os.system('rm -rf Image.bin')
    
