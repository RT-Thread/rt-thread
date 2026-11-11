#!/usr/bin/env python3

"""Generate flash image for EK-RRQ61000 board."""
# See reference implementation in the following legacy SDK files:
# binaries/mkimage/mkimage_new_header.py
# binaries/mkimage/non_secure_cfg.xml.AT25SL641-8MB

import argparse
import binascii
from collections import namedtuple
from rrq61_fw_version import get_fw_version
import os
from os import path
import re


# The following code is taken from mkimage_new_header.py (slightly modified):
def _initial(byte):
    polynomial = 0x1021
    crc = 0
    byte <<= 8
    for _i in range(8):
        if (crc ^ byte) & 0x8000:
            crc = (crc << 1) ^ polynomial
        else:
            crc <<= 1
        byte <<= 1
    return crc


_tab = [_initial(byte) for byte in range(256)]


def _update_crc(crc, byte):
    tmp = (crc >> 8) ^ byte
    crc = (crc << 8) ^ _tab[tmp & 0xFF]
    return crc & 0xFFFF


def crcb(data):
    """Calculate 16-bit long CRC."""
    crc = 0xFFFF  # preset
    for byte in data:
        crc = _update_crc(crc, byte)
    return crc


def to_bytes(value, num_bytes, byteorder='little', signed=False):
    """Convert integer value to specified number of bytes."""
    return value.to_bytes(num_bytes, byteorder, signed=signed)

ProductHeaderValues = namedtuple('ProductHeaderValues', [
    'is_corrupt', 'sram_boot', 'crc_corrupt', 'active_fw_addr',
    'update_fw_addr', 'burstcmda_reg', 'burstcmdb_reg', 'ctrlmode_reg',
    'flash_config'])


def get_product_header(header):
    """Produce product header binary blob."""
    # See calcCRC() in mkimage_new_header.py
    data = bytearray()
    if header.crc_corrupt:
        data.extend(b'\xDE\xAD\xC0\xDE')
    else:
        data.extend(b'\x53\x73' if header.is_corrupt else b'\x50\x70')
        data.extend(to_bytes(header.active_fw_addr, 4))
        data.extend(to_bytes(header.update_fw_addr, 4))
        data.extend(to_bytes(header.burstcmda_reg, 4))
        data.extend(to_bytes(header.burstcmdb_reg, 4))
        data.extend(to_bytes(header.ctrlmode_reg, 4))
        flash_config_id = to_bytes(0x22AA if header.sram_boot else 0x11AA, 2)
        data.extend(flash_config_id)
        flash_config_len = to_bytes(len(header.flash_config), 2)
        data.extend(flash_config_len)
        data.extend(header.flash_config)
    crc = to_bytes(crcb(data), 2)
    data.extend(crc)
    product_header_size = 0x1000  # 4096 bytes
    num_bytes_uninitialized = product_header_size - len(data)
    data.extend(b'\xFF' * num_bytes_uninitialized)
    return data


ImageHeaderValues = namedtuple('ImageHeaderValues', [
    'is_corrupt', 'security', 'version', 'timestamp', 'image_size',
    'image_crc'])


def get_image_header(header):
    """Produce image header binary blob."""
    # See __init__() from ImageHeader class in mkimage_new_header.py
    data = bytearray()
    if header.is_corrupt:
        raise ValueError('image_header_corrupt is not supported')
    if len(header.version) > 64:
        raise ValueError('image header version is longer than 64 bytes')
    data.extend(b'DA16')
    data.extend(to_bytes(header.timestamp, 4))
    data.extend(header.version)
    num_zeros = 64 - len(header.version)
    data.extend(b'\x00' * num_zeros)
    if header.security:
        raise ValueError('security for image header is not supported')
    pointer_to_ivt = 1024
    data.extend(to_bytes(pointer_to_ivt, 4))
    data.extend(to_bytes(header.image_size, 4))
    data.extend(to_bytes(header.image_crc, 4))
    secure_boot_option = 0
    data.extend(to_bytes(secure_boot_option, 4))
    secure_cert_size = 0
    data.extend(to_bytes(secure_cert_size, 4))
    secure_cert_crc = 0
    data.extend(to_bytes(secure_cert_crc, 4))
    crc = binascii.crc32(data)
    data.extend(to_bytes(crc, 4))
    image_header_size = 0x400
    num_bytes_uninitialized = image_header_size - len(data)
    data.extend(b'\xFF' * num_bytes_uninitialized)
    return data


def get_image_header_for_data(in_file_data, header_fw_version):
    """Build the Renesas image header for a raw application binary."""
    ih_values = ImageHeaderValues(
        is_corrupt=False,
        security=False,
        version=header_fw_version.encode(),
        timestamp=0x5939110D,
        image_size=len(in_file_data),
        image_crc=binascii.crc32(in_file_data) & 0xFFFFFFFF,
    )
    return get_image_header(ih_values)

def get_firmware_version_e2s(fw_version_file):
    """
    Reads the firmware version from fw_version.h.
    If not found, defaults to '1.0.0'.
    """
    try:
        with open(fw_version_file, "r") as file:
            content = file.read()
            match = re.search(r'#define FIRMWARE_VERSION\s+"([^"]+)"', content)
            if match:
                return match.group(1)
    except FileNotFoundError:
        print("fw_version.h file not found, using default version.")

    return "1.0.0"  # Default version


def get_header_fw_version(ra6w_grp, out_file_name):
    """Return the firmware version stored in an image header."""
    fw_version = get_fw_version()
    if not fw_version:
        # This condition will be true when we are building project
        # using e2studio and project is prepared outside the repo.
        script_dir = os.path.dirname(os.path.abspath(__file__))
        fw_version_file = os.path.abspath(os.path.join(script_dir, "../ra/fsp/src/rm_wifi/fw_version.h"))
        if not os.path.isfile(fw_version_file):
            fw_version_file = os.path.abspath(os.path.join(script_dir, "../ra/fsp/inc/fw_version.h"))
        fw_version = get_firmware_version_e2s(fw_version_file)
    elif 'rm_wifi_test_app' in out_file_name or 'vndm_wlan' in out_file_name:
        fw_version = fw_version + "-e2studio"
    else:
        fw_version = fw_version + "-cmake"

    return ra6w_grp + '-' + fw_version

def gen_flash_image(in_file, out_file, ra6w_grp):
    """Generate output flash image."""
    in_file_data = in_file.read()
    in_file.close()
    out_file_name = out_file.name

    # From non_secure_cfg.xml.AT25SL641-8MB (product headers 1 and 2):
    ph_values = ProductHeaderValues(
        is_corrupt=False,
        sram_boot=False,
        crc_corrupt=False,
        active_fw_addr=0x00002000,
        update_fw_addr=0x00002000,
        burstcmda_reg=0xa8a500eb,
        burstcmdb_reg=0x00030616,
        ctrlmode_reg=0xF8000532,
        flash_config=b'\x02\x31\x02',
    )

    headers_data = get_product_header(ph_values)  # first product header
    # Second product header is the same as first one according to file
    # non_secure_cfg.xml.AT25SL641-8MB, hence:
    headers_data.extend(headers_data)

    header_fw_version = get_header_fw_version(ra6w_grp, out_file_name)
    fw_version = header_fw_version[len(ra6w_grp) + 1:]
    img_header = get_image_header_for_data(in_file_data, header_fw_version)
    headers_data.extend(img_header)
    out_file.write(headers_data)
    out_file.write(in_file_data)
    out_file.close()

    #gen OTA images for test
    if((os.getcwd().find('rm_wifi') != -1) and out_file_name.find('rm_wifi_typical.img') != -1) :
        gen_ota_flash_images(in_file_data, fw_version, 'rm_wifi_typical_', ra6w_grp)

    elif((os.getcwd().find('rm_wifi') != -1) and out_file_name.find('rm_wifi_ba.img') != -1) :
        gen_ota_flash_images(in_file_data, fw_version, 'rm_wifi_ba_', ra6w_grp)

    elif((os.getcwd().find('rm_matter') != -1) and out_file_name.find('rm_matter_wifi_atcmd_test_app.img') != -1) :
        gen_ota_flash_images(in_file_data, fw_version, 'rm_matter_wifi_atcmd_test_app_', ra6w_grp)

    elif((os.getcwd().find('rm_matter') != -1) and out_file_name.find('rm_matter_wifi_lock_test_app.img') != -1) :
        gen_ota_flash_images(in_file_data, fw_version, 'rm_matter_wifi_lock_test_app_', ra6w_grp)

    elif((os.getcwd().find('vndm_rm_matter') != -1) and out_file_name.find('vndm_rm_matter_wifi_lock_test_app.img') != -1) :
        gen_ota_flash_images(in_file_data, fw_version, 'vndm_rm_matter_wifi_lock_test_app_', ra6w_grp)

    elif((os.getcwd().find('rm_wifi_test_app') != -1) and out_file_name.find('rm_wifi_test_app.img') != -1) :
        gen_ota_flash_images(in_file_data, fw_version, 'rm_wifi_test_app_', ra6w_grp)

    elif((os.getcwd().find('rm_wifi_test_app') != -1) and out_file_name.find('rm_wifi_test_app_at_sdio.img') != -1) :
        gen_ota_flash_images(in_file_data, fw_version, 'rm_wifi_test_app_at_sdio_', ra6w_grp)

    elif((os.getcwd().find('rm_wifi_test_app') != -1) and out_file_name.find('rm_wifi_test_app_at_spi.img') != -1) :
        gen_ota_flash_images(in_file_data, fw_version, 'rm_wifi_test_app_at_spi_', ra6w_grp)

    elif((os.getcwd().find('rm_wifi_test_app') != -1) and out_file_name.find('rm_wifi_test_app_at_uart.img') != -1) :
        gen_ota_flash_images(in_file_data, fw_version, 'rm_wifi_test_app_at_uart_', ra6w_grp)

    elif((os.getcwd().find('red_wifi_test_app') != -1) and out_file_name.find('red_wifi_test_app.img') != -1) :
        gen_ota_flash_images(in_file_data, fw_version, 'red_wifi_test_app_', ra6w_grp)

    elif((os.getcwd().find('vndm_wlan') != -1) and out_file_name.find('vndm_wlan_ble_coex_app.img') != -1) :
        gen_ota_flash_images(in_file_data, fw_version, 'vndm_wlan_ble_coex_app_', ra6w_grp)

    elif((os.getcwd().find('vndm_wlan') != -1) and out_file_name.find('vndm_wlan_ble_coex_app_at_sdio.img') != -1) :
        gen_ota_flash_images(in_file_data, fw_version, 'vndm_wlan_ble_coex_app_at_sdio_', ra6w_grp)

    elif((os.getcwd().find('vndm_wlan') != -1) and out_file_name.find('vndm_wlan_ble_coex_app_at_spi.img') != -1) :
        gen_ota_flash_images(in_file_data, fw_version, 'vndm_wlan_ble_coex_app_at_spi_', ra6w_grp)

    elif((os.getcwd().find('vndm_wlan') != -1) and out_file_name.find('vndm_wlan_ble_coex_app_at_uart.img') != -1) :
        gen_ota_flash_images(in_file_data, fw_version, 'vndm_wlan_ble_coex_app_at_uart_', ra6w_grp)

    elif((os.getcwd().find('vndm_wlan') != -1) and out_file_name.find('vndm_wlan_ble_sps_app.img') != -1) :
        gen_ota_flash_images(in_file_data, fw_version, 'vndm_wlan_ble_sps_app_', ra6w_grp)

    elif((os.getcwd().find('vndm_wlan') != -1) and out_file_name.find('vndm_wlan_ble_codeless_app.img') != -1) :
        gen_ota_flash_images(in_file_data, fw_version, 'vndm_wlan_ble_codeless_app_', ra6w_grp)

    elif((os.getcwd().find('vndm_wlan') != -1) and out_file_name.find('vndm_wlan_ble_coex_provisioning_app') != -1) :
        gen_ota_flash_images(in_file_data, fw_version, 'vndm_wlan_ble_coex_provisioning_app_', ra6w_grp)

    elif((os.getcwd().find('rm_ota_w') != -1) and out_file_name.find('rm_ota_w_typical.img')) :
        # Same version ex) RA6W1-0000000000-00000
        test_fw_version = ra6w_grp + '-' + fw_version
        gen_ota_flash_image(in_file_data, test_fw_version, 'rm_ota_w_ota')
    
    else:
            project_root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
            configuration_file_path = project_root + "/configuration.xml"
            try:
                with open(configuration_file_path, "r", encoding="utf-8") as f:
                    configuration_file_content = f.read()
                    if('<module id="module.middleware.ota_on_ota_w' in configuration_file_content):
                        prefix_file_name = out_file_name.split('.img')[0] + '_'
                        gen_ota_flash_images(in_file_data, fw_version, prefix_file_name, ra6w_grp)
                        
            except FileNotFoundError:
                print("configuration.xml file not found, skipping optional OTA test image generation.")

def gen_ota_flash_image(in_file_data, header_fw_version, ota_file_name):
    """Generate ota flash image."""
    # From non_secure_cfg.xml.AT25SL641-8MB (image header):
    img_header = get_image_header_for_data(in_file_data, header_fw_version)
    headers_data = bytearray()
    headers_data.extend(img_header)
    ota_out_file=open('./'+ota_file_name+'.img', 'wb')
    ota_out_file.write(headers_data)
    ota_out_file.write(in_file_data)
    ota_out_file.close()


def gen_ota_image(in_file, out_file, ra6w_grp):
    """Generate a single OTA image: image header followed by raw firmware."""
    in_file_data = in_file.read()
    in_file.close()

    header_fw_version = get_header_fw_version(ra6w_grp, out_file.name)
    out_file.write(get_image_header_for_data(in_file_data, header_fw_version))
    out_file.write(in_file_data)
    out_file.close()

def gen_ota_flash_images(in_file_data, fw_version, prefix_file_name, ra6w_grp):
    # Same version ex) RA6W1-0000000000-00000
    test_fw_version = ra6w_grp + '-' + fw_version
    gen_ota_flash_image(in_file_data, test_fw_version, prefix_file_name + test_fw_version)

    # Same version ex) _ota.img
    test_fw_version = ra6w_grp + '-' + fw_version
    gen_ota_flash_image(in_file_data, test_fw_version, prefix_file_name + 'ota')

    """Generate output OTA test image."""
    # SDK diff ex) RA6W1-ffffffffff-00000
    test_fw_version = ra6w_grp + '-ffffffffff-' + fw_version[11:]
    gen_ota_flash_image(in_file_data, test_fw_version, prefix_file_name + test_fw_version)

    # Customer diff ex) RA6W1-0000000000-99999
    test_fw_version = ra6w_grp + '-' + fw_version[0:10]+'-99999'
    gen_ota_flash_image(in_file_data, test_fw_version, prefix_file_name + test_fw_version)

    # SDK_Customer diff ex) RA6W1-ffffffffff-99999
    test_fw_version = ra6w_grp + '-ffffffffff-99999'
    gen_ota_flash_image(in_file_data, test_fw_version, prefix_file_name + test_fw_version)

    # Type diff ex) RA6W1-0000000000-00000
    test_fw_version = 'RA6XXX-' + fw_version
    gen_ota_flash_image(in_file_data, test_fw_version, prefix_file_name + test_fw_version)

    # Form diff ex) RA6W1.0000000000.00000
    test_fw_version = ra6w_grp + '.' + fw_version[0:10] + '.' + fw_version[11:]
    gen_ota_flash_image(in_file_data, test_fw_version, prefix_file_name + test_fw_version)

def _main():
    parser = argparse.ArgumentParser(
        description='Generate flash image for EK-RRQ61000 board.')
    parser.add_argument('--ota', '--ota-image', dest='ota_image', action='store_true',
                        help='generate a single OTA image (DA16 image header + raw firmware)')
    parser.add_argument('in_file', metavar='IN', type=argparse.FileType('rb'),
                        help='input file (.bin produced by objcopy)')
    parser.add_argument('out_file', metavar='OUT',
                        type=argparse.FileType('wb'),
                        help='output file (.img flash image)')
    parser.add_argument("ra6w_grp", type=str,
                        choices=["RA6W1-RRQ61001", "RA6W2-RRQ61051"],
                        help="RA6W group (RA6W1-RRQ61001 or RA6W2-RRQ61051)",
                        nargs="?",
                        default="RA6W1-RRQ61001")
    args = parser.parse_args()
    if args.ota_image:
        gen_ota_image(args.in_file, args.out_file, args.ra6w_grp)
    else:
        gen_flash_image(args.in_file, args.out_file, args.ra6w_grp)


if __name__ == '__main__':
    _main()
