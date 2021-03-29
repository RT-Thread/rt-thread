# @Time : 2020/12/31
# @Author : David Dai
# @File : mkimage.py
#!/usr/bin/python2

import os
import argparse
import struct

parser = argparse.ArgumentParser()

parser.add_argument('-t', '--type')
parser.add_argument('-b', '--bin')
parser.add_argument('-o', '--out', default = "load.bin")
parser.add_argument('-g', '--img', default = "load.img")
parser.add_argument('-a', '--addr', default = "0x00000000")
parser.add_argument('-e', '--ep', default = "0x00000000")

args = parser.parse_args()

args.addr = int(args.addr, 16)
args.ep = int(args.ep, 16)

def stm32image():
    checksum = 0

    with open(args.out, 'wb') as f:
        #write head 'STM32'
        f.write(struct.pack('<B', 0x53))
        f.write(struct.pack('<B', 0x54))
        f.write(struct.pack('<B', 0x4D))
        f.write(struct.pack('<B', 0x32))
        for i in range(16):
            f.write(struct.pack('<I', 0x00000000))

        #write checksum
        with open(args.bin, 'rb') as b:
            while(True):
                raw = b.read(1)
                if len(raw) == 0:
                    b.close()
                    break
                else:
                    checksum = checksum + ord(raw)
        checksum = checksum & 0xffffffff
        f.write(struct.pack('<I', checksum))
        f.write(struct.pack('<I', 0x00010000))

        #write size
        f.write(struct.pack('<I', os.path.getsize(args.bin)))
        #write entry point
        f.write(struct.pack('<I', args.ep))
        f.write(struct.pack('<I', 0x00000000))
        #write image load
        f.write(struct.pack('<I', args.addr))
        f.write(struct.pack('<I', 0x00000000))

        f.write(struct.pack('<I', 0x00000000))
        f.write(struct.pack('<I', 0x00000001))
        f.write(struct.pack('<I', 0x00000001))
        for i in range(37):
            f.write(struct.pack('<I', 0x00000000))

        #write bin data
        with open(args.bin, 'rb') as b:
            while(True):
                raw = b.read(1024)
                if len(raw) == 0:
                    b.close()
                    break
                else:
                    f.write(raw)
        f.close()

    print('Image Type   : STMicroelectronics STM32 Image')
    print('Bin File     : %s' % args.bin)
    print('Out File     : %s' % args.out)
    print('Image Size   : %d bytes' % os.path.getsize(args.bin))
    print('Image Load   : 0x%x' % args.addr)
    print('Entry Point  : 0x%x' % args.ep)
    print('Checksum     : 0x%x' % checksum)

def imx6ullimage():
    dcdConfig = [
        ['0x020c4068', '0xffffffff'],
        ['0x020c406c', '0xffffffff'],
        ['0x020c4070', '0xffffffff'],
        ['0x020c4074', '0xffffffff'],
        ['0x020c4078', '0xffffffff'],
        ['0x020c407c', '0xffffffff'],
        ['0x020c4080', '0xffffffff'],
        ['0x020E04B4', '0x000C0000'],
        ['0x020E04AC', '0x00000000'],
        ['0x020E027C', '0x00000030'],
        ['0x020E0250', '0x00000030'],
        ['0x020E024C', '0x00000030'],
        ['0x020E0490', '0x00000030'],
        ['0x020E0288', '0x000C0030'],
        ['0x020E0270', '0x00000000'],
        ['0x020E0260', '0x00000030'],
        ['0x020E0264', '0x00000030'],
        ['0x020E04A0', '0x00000030'],
        ['0x020E0494', '0x00020000'],
        ['0x020E0280', '0x00000030'],
        ['0x020E0284', '0x00000030'],
        ['0x020E04B0', '0x00020000'],
        ['0x020E0498', '0x00000030'],
        ['0x020E04A4', '0x00000030'],
        ['0x020E0244', '0x00000030'],
        ['0x020E0248', '0x00000030'],
        ['0x021B001C', '0x00008000'],
        ['0x021B0800', '0xA1390003'],
        ['0x021B080C', '0x00000004'],
        ['0x021B083C', '0x41640158'],
        ['0x021B0848', '0x40403237'],
        ['0x021B0850', '0x40403C33'],
        ['0x021B081C', '0x33333333'],
        ['0x021B0820', '0x33333333'],
        ['0x021B082C', '0xf3333333'],
        ['0x021B0830', '0xf3333333'],
        ['0x021B08C0', '0x00944009'],
        ['0x021B08b8', '0x00000800'],
        ['0x021B0004', '0x0002002D'],
        ['0x021B0008', '0x1B333030'],
        ['0x021B000C', '0x676B52F3'],
        ['0x021B0010', '0xB66D0B63'],
        ['0x021B0014', '0x01FF00DB'],
        ['0x021B0018', '0x00201740'],
        ['0x021B001C', '0x00008000'],
        ['0x021B002C', '0x000026D2'],
        ['0x021B0030', '0x006B1023'],
        ['0x021B0040', '0x0000004F'],
        ['0x021B0000', '0x84180000'],
        ['0x021B0890', '0x00400000'],
        ['0x021B001C', '0x02008032'],
        ['0x021B001C', '0x00008033'],
        ['0x021B001C', '0x00048031'],
        ['0x021B001C', '0x15208030'],
        ['0x021B001C', '0x04008040'],
        ['0x021B0020', '0x00000800'],
        ['0x021B0818', '0x00000227'],
        ['0x021B0004', '0x0002552D'],
        ['0x021B0404', '0x00011006'],
        ['0x021B001C', '0x00000000']
        ]

    with open(args.out, 'wb') as f:
        #write ivt
        f.write(struct.pack('<B', 0xD1))
        f.write(struct.pack('>H', 32))
        f.write(struct.pack('<B', 0x40))
        f.write(struct.pack('<I', args.addr))
        f.write(struct.pack('<I', 0x00000000))
        f.write(struct.pack('<I', args.addr - ((len(dcdConfig) + 318) << 3) - 4))
        f.write(struct.pack('<I', args.addr - ((len(dcdConfig) + 318) << 3) - 16))
        f.write(struct.pack('<I', args.addr - ((len(dcdConfig) + 318) << 3) - 48))
        f.write(struct.pack('<I', 0x00000000))
        f.write(struct.pack('<I', 0x00000000))

        #write boot data
        f.write(struct.pack('<I', args.addr - ((len(dcdConfig) + 318) << 3) - 1072))
        f.write(struct.pack('<I', ((os.path.getsize(args.bin) + 0x1000 - 1) & ~(0x1000 - 1)) + 4096))
        f.write(struct.pack('<I', 0x00000000))

        #write DCD
            #dcd header
        f.write(struct.pack('<B', 0xD2))
        f.write(struct.pack('>H', (len(dcdConfig) << 3) + 8))
        f.write(struct.pack('<B', 0x40))
            #dcd wrute header
        f.write(struct.pack('<B', 0xCC))
        f.write(struct.pack('>H', (len(dcdConfig) << 3) + 4))
        f.write(struct.pack('<B', 0x04))
            #dcd wrute data
        for d in dcdConfig:
            f.write(struct.pack('>I', int(d[0], 16)))
            f.write(struct.pack('>I', int(d[1], 16)))

        #padding data
        for i in range(0x27B):
            f.write(struct.pack('<I', 0x00000000))

        #write bin data
        with open(args.bin, 'rb') as b:
            while(True):
                raw = b.read(1024)
                if len(raw) == 0:
                    b.close()
                    break
                else:
                    f.write(raw)

        #padding data
        for i in range(((os.path.getsize(args.bin) + 0x1000 - 1) & ~(0x1000 - 1)) - os.path.getsize(args.bin)):
            f.write(struct.pack('<B', 0x00))
        f.close()

    #build img file
    with open(args.img, 'wb') as g:
        #Header write 1K data
        for i in range(0x100):
            g.write(struct.pack('<I', 0x00000000))

        #write imx data
        with open(args.out, 'rb') as f:
            while(True):
                raw = f.read(1024)
                if len(raw) == 0:
                    f.close()
                    break
                else:
                    g.write(raw)
        g.close()

    print('Image Type   : Freescale i.MX Boot Image')
    print('Bin File     : %s' % args.bin)
    print('IMX File     : %s' % args.out)
    print('IMG File     : %s' % args.img)
    print('Image Size   : %d bytes' % os.path.getsize(args.bin))
    print('Image Load   : 0x%x' % args.addr)

if __name__ == '__main__':
    if args.bin is not None and args.type is not None:
        if not os.path.exists(args.bin):
            print('Bin File : %s is not exist' % args.bin)
            exit()

        if args.type == 'stm32image':
            stm32image()
        elif args.type == "imximage":
            imx6ullimage()
        else:
            print('%s type image no found!' % args.type)
    else:
        print('Help : mkimage.py -b [name.bin] -t [stm32image|imx6ullimage]')