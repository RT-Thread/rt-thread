#!/bin/python
# -*- coding: utf-8 -*-
import os, sys, re, shutil

with open('rtconfig.h', 'r') as file:
	rtconfig_header = file.read()

if os.getenv('RTT_QEMU_ROOT'):
	RTT_QEMU_ROOT = os.getenv('RTT_QEMU_ROOT')
else:
	RTT_QEMU_ROOT = ""

if os.getenv('RTT_ROOT'):
	RTT_ROOT = os.getenv('RTT_ROOT')
else:
	RTT_ROOT = os.path.join(os.getcwd(), '..', '..')

# WSL?
is_windows = sys.platform.startswith('win') or \
	os.popen('which qemu-system-riscv64 | xargs file').read().find('PE') >= 0 or \
	(os.system("readlink `which qemu-system-riscv64` > /dev/null") == 0 and \
	os.popen('readlink `which qemu-system-riscv64` | xargs file').read().find('PE') >= 0)

class QEMU_VERSION:
	def __init__(self):
		cmd = os.popen(RTT_QEMU_ROOT + "qemu-system-riscv64 --version").readlines()[0]
		version = cmd[cmd.find("version ") + 8: -1].split('.')

		self.major = version[0]
		self.minor = version[1]
		self.revision = version[2]
	# ==
	def __eq__(self, version_in):
		version = version_in.split('.')
		return self.major == version[0] and self.minor == version[1] and self.revision == version[2]
	# >=
	def __ge__(self, version_in):
		return self.__gt__(version_in) or self.__eq__(version_in)
	# >
	def __gt__(self, version_in):
		version = version_in.split('.')
		return self.major > version[0] or \
			(self.major == version[0] and self.minor > version[1]) or \
			(self.major == version[0] and self.minor == version[1] and self.revision > version[2])
	# <=
	def __le__(self, version_in):
		return self.__lt__(version_in) or self.__eq__(version_in)
	# <
	def __lt__(self, version_in):
		return not self.__ge__(version_in)
	# !=
	def __ne__(self, version_in):
		return not self.__eq__(version_in)

qemu_version = QEMU_VERSION()

opt = sys.argv

graphic_cfg = """ \
	-device ramfb \
	-device virtio-keyboard-device \
	-device virtio-tablet-device \
"""

cdrom_cfg = ""
virtfs_cfg = ""
ufs_cfg = ""

q_msi = "aia=aplic-imsic"
q_v = ""
q_prefix = "riscv64"
q_dumpdtb = ""
q_smp = int(re.findall(r'#define\s+RT_CPUS_NR\s+(\d+)', rtconfig_header)[0])
q_mem = 128
q_graphic = "-nographic"
q_debug = ""
q_bootargs = "console=ttyS0 earlycon=sbi cma=8M coherent_pool=2M root=vda0 rootfstype=elm rootwait rw"
q_initrd = ""
q_block = "virtio"
q_net = "user"
q_ssh = 12055
q_flash = "flash"
q_sound = "hda"
q_gl = None
q_9p = ""

def is_opt(key, inkey):
	if str("-" + key) == inkey:
		return True
	return False

for i in range(len(opt)):
	if i == 0:
		continue
	inkey = opt[i]

	if is_opt("no-msi", inkey): q_msi = "aia=none"
	if is_opt("v", inkey): q_v = ",v=true,vlen=128,vext_spec=v1.0"
	if is_opt("rv64ilp32", inkey): q_prefix = "rv64ilp32"
	if is_opt("dumpdtb", inkey): q_dumpdtb = str(",dumpdtb=" + opt[i + 1])
	if is_opt("smp", inkey): q_smp = int(opt[i + 1])
	if is_opt("mem", inkey): q_mem = int(opt[i + 1])
	if is_opt("debug", inkey): q_debug = "-S -s"
	if is_opt("bootargs", inkey): q_bootargs = opt[i + 1]
	if is_opt("initrd", inkey): q_initrd = str("-initrd " + opt[i + 1])
	if is_opt("graphic", inkey): q_graphic = graphic_cfg
	if is_opt("virtio-block", inkey): q_block = opt[i + 1]
	if is_opt("tap", inkey): q_net = "tap,ifname=tap0"
	if is_opt("ssh", inkey): q_ssh = int(opt[i + 1])
	if is_opt("flash", inkey): q_flash = opt[i + 1]
	if is_opt("sound", inkey): q_sound = opt[i + 1]
	if is_opt("gl", inkey): q_gl = "-device virtio-gpu-gl-pci -display {},gl=on ".format(opt[i + 1])
	if is_opt("9p", inkey): q_9p = opt[i + 1]

# Display
#	--enable-opengl --enable-virglrenderer
if q_graphic != "-nographic":
	if q_gl:
		q_graphic += q_gl
	else:
		q_graphic += "-device virtio-gpu-device"
elif q_gl != None:
	print("Error: GL should in graphic mode")
	exit(-1)

# Sound
if q_sound == "hda":
	q_sound = "-device intel-hda -device hda-duplex "
elif q_sound == "virtio":
	if qemu_version < '8.2.0':
		print("Error: VirtIO Sound is not in this version: {}".format(qemu_version))
		exit(-1)
	q_sound = "-device virtio-sound-pci,audiodev=vsnd -audiodev alsa,id=vsnd "
else:
	print("Error: Invalid -sound {}".format(q_sound))
	exit(-1)

# Net
#	--enable-slirp
#	Enable TAP in example (not support in Windows, Maybe WSL2):
#		ETH0=`/sbin/route -n | awk '$1 == "0.0.0.0" {print $NF}'`
#		ip link add br0 type bridge
#		ip link set br0 up
#		echo 1 | tee /proc/sys/net/ipv4/ip_forward > /dev/null
#		ip link set ${ETH0} up
#		ip link set ${ETH0} master br0
#		dhclient br0
#		ip tuntap add dev tap0 mode tap
#		ip link set dev tap0 up
#		ip link set tap0 master br0
#
#	Disable TAP in example (not support in Windows, Maybe WSL2):
#		ip link set tap0 down
#		ip tuntap del dev tap0 mod tap
#		echo 0 | tee /proc/sys/net/ipv4/ip_forward > /dev/null
#		ip link set br0 down
#		ip link del br0 type bridge
if q_net.find("user") >= 0:
	q_net += ",hostfwd=tcp::{}-:22".format(q_ssh)
else:
	if not is_windows:
		q_net += ",script=no,downscript=no"
	print("Warning: SSH not set in TAP")

# Storage
#	pflash have pflash0 and pflash1, pflash0 is used for BootROMs such as UEFI
#	if we load file to pflash0, QEMU will boot from it, so we only use pflash1.
#	Well, we can R/W in pflash0 by CFI driver, but the data will lost after QEMU exits.
#
#	partitions (not support in Windows, Maybe WSL2):
#		modprobe nbd max_part=12
#		qemu-nbd --connect=/dev/nbdX ABC.qcow2
#		fdisk /dev/nbdX
#		...
#		qemu-nbd --disconnect /dev/nbdX
disk_list = [q_block, q_flash]

for disk in disk_list:
	size = 64
	if disk == q_flash:
		size = 32
	disk += ".qcow2"
	if not os.path.exists(disk):
		os.system("qemu-img create -f qcow2 {} {}M".format(disk, size))

# Share File System
#	--enable-virtfs
if len(q_9p) > 0:
	p9_tag = "hostshare"
	virtfs_cfg = """ \
		-fsdev local,security_model=passthrough,id=fsdev0,path={} \
			-device virtio-9p-device,fsdev=fsdev0,mount_tag={} \
	""".format(q_9p, p9_tag)
	q_bootargs += " 9p.tag={} 9p.mount=host".format(p9_tag)

# Note
#	Hot-plug / Hot-unplug in QEMU monitor:
#		(qemu) chardev-add socket,host=127.0.0.1,port=4323,server=on,wait=off,telnet=on,id=console2
#		(qemu) device_add virtserialport,chardev=console2,name=org.rt-thread.port,id=port2
#		(qemu) device_del port2
#		(qemu) chardev-remove console2
#
#	VirtIO version disable legacy to set version >= 1.0:
#		-global virtio-mmio.force-legacy=false
#
#	VirtIO used virtqueue packed (version >= 1.0)
#		-device virtio-XYZ-device,packed=on
#
#	VirtIO used PCI/PCIe bus (version >= 1.0)
#		-device virtio-XYZ-pci,disable-legacy=on

os.system("""
{}qemu-system-{} \
	-M virt,acpi=on,aclint=on,{}{}{} \
	-cpu max \
	-smp {} \
	-m {} \
	-kernel rtthread.bin \
	-append "{}" \
	{} \
	-serial mon:stdio \
	{} \
	{} \
	-drive if=none,file={}.qcow2,format=qcow2,id=blk0 \
		-device virtio-blk-device,drive=blk0 \
	-netdev {},id=net0 \
		-device virtio-net-device,netdev=net0,speed=800000 \
	-device virtio-rng-device \
	{} \
	-device virtio-crypto-device,cryptodev=vcrypto0 \
		-object cryptodev-backend-builtin,id=vcrypto0 \
	-device virtio-serial-device \
		-chardev socket,host=127.0.0.1,port=4321,server=on,wait=off,telnet=on,id=console0 \
		-device virtserialport,chardev=console0,name=org.rt-thread.console \
	{} \
	-drive if=pflash,file={}.qcow2,format=qcow2,index=1 \
	-device pci-serial,chardev=console1 \
		-chardev socket,host=127.0.0.1,port=4322,server=on,wait=off,telnet=on,id=console1 \
	-device i6300esb -watchdog-action reset \
	-device edu,dma_mask=0xffffffff
""".format(RTT_QEMU_ROOT, q_prefix, q_msi, q_v, q_dumpdtb, q_smp, q_mem, q_bootargs, q_initrd,
		q_graphic, q_debug, q_block, q_net, virtfs_cfg, q_sound, q_flash))
