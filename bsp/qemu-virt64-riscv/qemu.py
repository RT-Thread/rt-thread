#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import argparse
import os
import re
import shlex
import shutil
import subprocess
import sys


def read_default_cpus():
    try:
        with open("rtconfig.h", "r", encoding="utf-8") as f:
            rtconfig = f.read()
    except OSError:
        return 1

    match = re.search(r"#define\s+RT_CPUS_NR\s+(\d+)", rtconfig)
    return int(match.group(1)) if match else 1


def read_riscv_xlen():
    try:
        with open("rtconfig.h", "r", encoding="utf-8") as f:
            rtconfig = f.read()
    except OSError:
        return 64

    return 64 if re.search(r"#define\s+ARCH_RISCV64\b", rtconfig) else 32


def read_vector_vlen():
    try:
        with open("rtconfig.h", "r", encoding="utf-8") as f:
            rtconfig = f.read()
    except OSError:
        return None

    if not re.search(r"#define\s+ARCH_RISCV_VECTOR\b", rtconfig):
        return None

    match = re.search(r"#define\s+ARCH_VECTOR_VLEN_(128|256|512|1024|2048|4096)\b", rtconfig)
    return int(match.group(1)) if match else 128


def using_rt_smart():
    try:
        with open("rtconfig.h", "r", encoding="utf-8") as f:
            rtconfig = f.read()
    except OSError:
        return False

    return re.search(r"#define\s+RT_USING_SMART\b", rtconfig) is not None


def qemu_tool(name):
    root = os.getenv("RTT_QEMU_ROOT", "")
    return os.path.join(root, name) if root else name


def qemu_version(qemu):
    try:
        output = subprocess.check_output(
            [qemu, "--version"],
            stderr=subprocess.STDOUT,
            text=True,
        )
    except (OSError, subprocess.SubprocessError):
        return None

    match = re.search(r"version\s+(\d+)\.(\d+)\.(\d+)", output)
    if not match:
        return None

    return tuple(int(v) for v in match.groups())


def version_to_string(version):
    if version is None:
        return "unknown"
    return ".".join(str(v) for v in version)


def qcow2_image(name):
    return name if name.endswith(".qcow2") else "{}.qcow2".format(name)


def ensure_qcow2(name, size_mb, create=True):
    image = qcow2_image(name)

    if create and not os.path.exists(image):
        subprocess.run(
            [qemu_tool("qemu-img"), "create", "-f", "qcow2", image, "{}M".format(size_mb)],
            check=True,
        )

    return image


def add_cpu_options(cpu, options):
    if not options:
        return cpu
    return "{},{}".format(cpu, ",".join(options))


def virtio_device(name, args, params=""):
    if args.pci:
        device = "virtio-{}-pci,disable-legacy=on".format(name)
    else:
        device = "virtio-{}-device".format(name)

    return "{},{}".format(device, params) if params else device


def dump_dtb_to_dts(dtb):
    dtc = shutil.which("dtc")
    if not dtc:
        print("Warning: dtc not found, skip {} -> dts conversion".format(dtb))
        return

    dts = re.sub(r"\.dtbo?$", ".dts", dtb)
    if dts == dtb:
        dts = "{}.dts".format(dtb)

    subprocess.run([dtc, "-I", "dtb", "-O", "dts", dtb, "-o", dts], check=False)


def parse_args():
    parser = argparse.ArgumentParser(description="Run RT-Thread on QEMU virt RISC-V.")

    parser.add_argument("-smp", type=int, default=read_default_cpus())
    parser.add_argument("-mem", type=int, default=256)
    parser.add_argument("-cpu", default="max")
    parser.add_argument("-kernel", default="rtthread.bin")
    parser.add_argument("-debug", action="store_true", help="Wait for GDB on :1234.")
    parser.add_argument("-dumpdtb", metavar="FILE", help="Dump QEMU generated DTB and exit.")
    parser.add_argument("-dtb", metavar="FILE", help="Use an external DTB.")
    parser.add_argument(
        "-bootargs",
        default="console=ttyS0 earlycon=sbi cma=8M coherent_pool=2M root=vda0 rootfstype=elm rootwait rw",
    )
    parser.add_argument("-initrd", metavar="FILE")

    parser.add_argument("-graphic", action="store_true")
    parser.add_argument("-gl", metavar="BACKEND", help="Enable OpenGL display backend, for example gtk or sdl.")
    parser.add_argument("-sound", choices=["none", "hda", "virtio"], default="none")

    parser.add_argument("-net", dest="net", action="store_true", default=True,
            help="Attach virtio-net using QEMU user networking. This is enabled by default.")
    parser.add_argument("-no-net", dest="net", action="store_false", help="Disable virtio-net.")
    parser.add_argument("-tap", action="store_true", help="Attach virtio-net to tap0.")
    parser.add_argument("-ssh", type=int, default=12055)
    parser.add_argument("-9p", dest="host_9p", metavar="PATH")

    parser.add_argument("-pci", action="store_true", help="Use virtio PCI devices instead of virtio-mmio devices.")
    parser.add_argument("-virtio-console", dest="virtio_console", action="store_true", default=None,
            help="Expose virtio-console on localhost:4321. This is enabled by default for RV64.")
    parser.add_argument("-no-virtio-console", dest="virtio_console", action="store_false", default=None,
            help="Disable virtio-console.")
    parser.add_argument("-pci-serial", dest="pci_serial", action="store_true", default=None,
            help="Expose PCI serial on localhost:4322. This is enabled by default for RV64.")
    parser.add_argument("-no-pci-serial", dest="pci_serial", action="store_false", default=None,
            help="Disable PCI serial.")

    parser.add_argument("-block", "-virtio-block", dest="block", default="virtio")
    parser.add_argument("-nvme", nargs="?", const="nvme", default=argparse.SUPPRESS, metavar="NAME",
            help="Attach an NVMe disk. This is enabled by default for RV64.")
    parser.add_argument("-no-nvme", dest="nvme", action="store_const", const=None,
            default=argparse.SUPPRESS, help="Disable NVMe disk.")
    parser.add_argument("-watchdog", dest="watchdog", action="store_true", default=False,
            help="Attach i6300esb watchdog.")
    parser.add_argument("-no-watchdog", dest="watchdog", action="store_false", help="Disable watchdog.")
    parser.add_argument("-edu", dest="edu", action="store_true", default=False,
            help="Attach QEMU edu PCI test device.")
    parser.add_argument("-no-edu", dest="edu", action="store_false", help="Disable QEMU edu device.")

    parser.add_argument("-rv64ilp32", action="store_true")
    parser.add_argument("-v", action="store_true", help="Enable QEMU vector CPU option even if disabled in rtconfig.h.")
    parser.add_argument("-aia", dest="aia", action="store_true", default=None,
            help="Use AIA APLIC/IMSIC instead of PLIC/ACLINT. This is enabled by default for RV64.")
    parser.add_argument("-no-aia", dest="aia", action="store_false", help="Use PLIC/CLINT instead of AIA.")
    parser.add_argument("-no-msi", action="store_true", help="Compatibility option; same as disabling AIA.")
    parser.add_argument("-dry-run", action="store_true", help="Print QEMU command without running it.")

    return parser.parse_args()


def main():
    args = parse_args()

    configured_cpus = read_default_cpus()
    if args.smp != configured_cpus:
        print(
            "Error: -smp {} does not match RT_CPUS_NR={} in rtconfig.h. "
            "Reconfigure and rebuild the kernel before changing the CPU count.".format(
                args.smp, configured_cpus
            )
        )
        return 1

    xlen = read_riscv_xlen()
    if args.aia is None:
        args.aia = xlen == 64
    if not hasattr(args, "nvme"):
        args.nvme = "nvme" if xlen == 64 and args.aia and not args.no_msi else None
    if args.virtio_console is None:
        args.virtio_console = xlen == 64
    if args.pci_serial is None:
        args.pci_serial = xlen == 64

    qemu = qemu_tool("qemu-system-riscv{}".format(xlen))
    virtio_mmio_legacy = "true" if xlen == 32 else "false"
    if args.rv64ilp32:
        if xlen != 64:
            print("Error: -rv64ilp32 requires an RV64 kernel configuration.")
            return 1
        qemu = qemu_tool("qemu-system-rv64ilp32")

    if args.gl and not args.graphic:
        print("Error: -gl requires -graphic")
        return 1

    if args.tap and not args.net:
        print("Error: -tap conflicts with -no-net")
        return 1

    qemu_ver = qemu_version(qemu)
    if args.sound == "virtio" and qemu_ver is not None and qemu_ver < (8, 2, 0):
        print("Error: virtio sound requires QEMU >= 8.2.0, current {}".format(version_to_string(qemu_ver)))
        return 1

    aia = "aia=aplic-imsic" if args.aia and not args.no_msi else "aia=none"
    machine = "virt,acpi=on,aclint=on,{}".format(aia)

    if args.dumpdtb:
        machine += ",dumpdtb={}".format(args.dumpdtb)

    cpu_options = []
    if using_rt_smart() and args.cpu in ("max", "rv64"):
        cpu_options += ["sv57=off", "sv48=off"]

    vector_vlen = read_vector_vlen()
    if args.v or vector_vlen:
        cpu_options += ["v=true", "vlen={}".format(vector_vlen or 128), "vext_spec=v1.0"]
    cpu = add_cpu_options(args.cpu, cpu_options)

    create_images = not args.dry_run
    block = ensure_qcow2(args.block, 64, create_images)

    if args.tap:
        netdev = "tap,ifname=tap0,script=no,downscript=no,id=net0"
    else:
        netdev = "user,hostfwd=tcp::{}-:22,id=net0".format(args.ssh)

    bootargs = args.bootargs
    if args.host_9p:
        bootargs += " 9p.tag=hostshare 9p.mount=host"

    cmd = [
        qemu,
        "-M", machine,
        "-cpu", cpu,
        "-smp", str(args.smp),
        "-m", str(args.mem),
        "-kernel", args.kernel,
        "-append", bootargs,
        "-serial", "mon:stdio",
        "-global", "virtio-mmio.force-legacy={}".format(virtio_mmio_legacy),
        "-drive", "if=none,file={},format=qcow2,id=blk0".format(block),
        "-device", virtio_device("blk", args, "drive=blk0"),
        "-device", virtio_device("rng", args),
        "-device", virtio_device("crypto", args, "cryptodev=vcrypto0"),
        "-object", "cryptodev-backend-builtin,id=vcrypto0",
    ]

    if args.dtb:
        cmd += ["-dtb", args.dtb]

    if args.net:
        cmd += [
            "-netdev", netdev,
            "-device", virtio_device("net", args, "netdev=net0,speed=800000"),
        ]

    if args.virtio_console:
        cmd += [
            "-device", virtio_device("serial", args),
            "-chardev", "socket,host=127.0.0.1,port=4321,server=on,wait=off,telnet=on,id=console0",
            "-device", "virtserialport,chardev=console0,name=org.rt-thread.console",
        ]

    if args.pci_serial:
        cmd += [
            "-chardev", "socket,host=127.0.0.1,port=4322,server=on,wait=off,telnet=on,id=console1",
            "-device", "pci-serial,chardev=console1",
        ]

    if args.nvme:
        nvme = ensure_qcow2(args.nvme, 64, create_images)
        cmd += [
            "-device", "nvme,id=nvme-ctrl-0,serial=deadbeef",
            "-drive", "if=none,file={},format=qcow2,id=nvme0".format(nvme),
            "-device", "nvme-ns,drive=nvme0",
        ]

    if args.sound == "hda":
        cmd += ["-device", "intel-hda", "-device", "hda-duplex"]
    elif args.sound == "virtio":
        cmd += ["-device", "virtio-sound-pci,audiodev=vsnd", "-audiodev", "alsa,id=vsnd"]

    if args.watchdog:
        cmd += ["-device", "i6300esb", "-watchdog-action", "reset"]

    if args.edu:
        cmd += ["-device", "edu,dma_mask=0xffffffff"]

    if args.initrd:
        cmd += ["-initrd", args.initrd]

    if args.debug:
        cmd += ["-S", "-s"]

    if args.graphic:
        cmd += ["-device", "ramfb"]
        if args.gl:
            cmd += ["-device", "virtio-gpu-gl-pci", "-display", "{},gl=on".format(args.gl)]
        else:
            cmd += ["-device", virtio_device("gpu", args)]
        cmd += [
            "-device", "virtio-keyboard-device",
            "-device", "virtio-tablet-device",
        ]
    else:
        cmd += ["-nographic"]

    if args.host_9p:
        cmd += [
            "-fsdev", "local,security_model=passthrough,id=fsdev0,path={}".format(args.host_9p),
            "-device", virtio_device("9p", args, "fsdev=fsdev0,mount_tag=hostshare"),
        ]

    if args.dry_run:
        print(" ".join(shlex.quote(arg) for arg in cmd))
        return 0

    ret = subprocess.call(cmd)
    if ret == 0 and args.dumpdtb:
        dump_dtb_to_dts(args.dumpdtb)

    return ret


if __name__ == "__main__":
    sys.exit(main())
