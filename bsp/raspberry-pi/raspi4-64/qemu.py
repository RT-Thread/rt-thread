#!/usr/bin/python
# -*- coding: utf-8 -*-
import os, sys, re, shutil

if os.getenv('RTT_QEMU_ROOT'):
	RTT_QEMU_ROOT = os.getenv('RTT_QEMU_ROOT')
else:
	RTT_QEMU_ROOT = ""

if os.getenv('RTT_ROOT'):
	RTT_ROOT = os.getenv('RTT_ROOT')
else:
	RTT_ROOT = os.path.join(os.getcwd(), '..', '..', '..')

sys.path.append(RTT_ROOT + '/tools')

from building import *
import dtc

dts_name = "bcm2711-rpi-4-b"

dtc.dts_to_dtb(RTT_ROOT, ["../dm/dts/" + dts_name + ".dts"], include_paths = [os.getcwd() + '/../dm/include'],
		ignore_warning = ["simple_bus_reg", "unit_address_vs_reg", "clocks_is_cell", "gpios_property"])
try:
	shutil.move("../dm/dts/" + dts_name + ".dtb", dts_name + ".dtb")
except:
	exit(-1)

opt = sys.argv

q_graphic = "-nographic"
q_debug = ""

def is_opt(key, inkey):
	if str("-" + key) == inkey:
		return True
	return False

for i in range(len(opt)):
	if i == 0:
		continue
	inkey = opt[i]

	if is_opt("debug", inkey): q_debug = "-S -s"
	if is_opt("graphic", inkey): q_graphic = "-usb -device usb-mouse -device usb-kbd"

disk = "sd.qcow2"
if not os.path.exists(disk):
	os.system("qemu-img create -f qcow2 {} 64M".format(disk))

flash = "flash.bin"
if not os.path.exists(flash):
	os.system("qemu-img create -f raw {} 1M".format(flash))

os.system("""
{}qemu-system-aarch64 \
	-M raspi4b \
	-m 2G \
	-kernel rtthread.bin \
	-dtb {}.dtb \
	-append "console=ttyAMA0 earlycon=pl011,0xfe201000 cma=8M coherent_pool=2M root=sd0p0 rootfstype=elm rootwait rw" \
	-serial mon:stdio \
	-drive if=sd,file={},format=qcow2 \
	-device ds1338,address=0x68,bus=i2c-bus.0 \
	-device m25p80,write-enable=true,drive=flash0,bus=spi \
		-blockdev node-name=flash0,driver=file,filename={} \
	-device usb-net,netdev=net0 -netdev user,id=net0 \
	{} \
	{}
""".format(RTT_QEMU_ROOT, dts_name, disk, flash, q_graphic, q_debug))
