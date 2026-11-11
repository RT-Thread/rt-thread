"""
Utils for CMake
Author: https://github.com/klivelinux
"""

import os
import sys
import re
import subprocess
import utils
import rtconfig
from utils import _make_path_relative


def get_zig_version():
    try:
        result = subprocess.run(['zig', 'version'], capture_output=True, text=True)
        version_str = result.stdout.strip()
        parts = version_str.split('.')
        major = int(parts[0])
        minor = int(parts[1]) if len(parts) > 1 else 0
        return (major, minor)
    except Exception:
        return (0, 0)


ZIG_VERSION = get_zig_version()
IS_ZIG_0_14_PLUS = ZIG_VERSION[0] > 0 or (ZIG_VERSION[0] == 0 and ZIG_VERSION[1] >= 14)


def GenerateCFiles(env,project):
    info = utils.ProjectInfo(env)

    ARCH = ".thumb" if rtconfig.CPU in ['cortex-m0', 'cortex-m3', 'cortex-m4', 'cortex-m7','cortex-m23','cortex-m33','cortex-m85'] else ".arm"

    CFLAGS = rtconfig.CFLAGS.replace('\\', "/").replace('\"', "\\\"")
    LFLAGS = rtconfig.LFLAGS.replace('\\', "/").replace('\"', "\\\"")

    zig_file = open('build.zig', 'w')
    if zig_file:
        zig_file.write("const std = @import(\"std\");\n\n")

        if IS_ZIG_0_14_PLUS:
            zig_file.write("const target = std.Target.Query{\n")
            zig_file.write("    .cpu_arch = {},\n".format(ARCH))
            zig_file.write("    .cpu_model = .{{ .explicit = &std.Target.{}.cpu.{} }},\n".format(rtconfig.ARCH, rtconfig.CPU.replace('-', '_')))
            zig_file.write("    .os_tag = .freestanding,\n")
            if ARCH == ".thumb":
                zig_file.write("    .abi = .eabihf,\n")
            else:
                zig_file.write("    .abi = .eabi,\n")
            zig_file.write("};\n\n")
        else:
            zig_file.write("const target = std.zig.CrossTarget{\n")
            zig_file.write("    .cpu_arch = {},\n".format(ARCH))
            zig_file.write("    .cpu_model = .{{ .explicit = &std.Target.{}.cpu.{} }},\n".format(rtconfig.ARCH, rtconfig.CPU.replace('-', '_')))
            zig_file.write("    .os_tag = .freestanding,\n")
            zig_file.write("    .abi = .eabi,\n")
            zig_file.write("};\n\n")

        zig_file.write("const c_includes = [_][]const u8{\n")
        for i in info['CPPPATH']:
            # use relative path
            path = _make_path_relative(os.getcwd(), i)
            zig_file.write("\t\"{}\",\n".format(path.replace("\\", "/")))
        zig_file.write("};\n\n")

        zig_file.write("const c_sources = [_][]const u8{\n")
        for group in project:
            for f in group['src']:
                # use relative path
                path = _make_path_relative(os.getcwd(), os.path.normpath(f.rfile().abspath))
                zig_file.write("\t\"{}\",\n".format(path.replace("\\", "/")))
        zig_file.write("};\n\n")

        zig_file.write("const c_flags = [_][]const u8{\n")
        zig_file.write("\t\"-std=c99\",\n")
        zig_file.write("\t\"-ffunction-sections\",\n")
        zig_file.write("\t\"-fdata-sections\",\n")
        # conver CDefines to CFlags
        for i in info['CPPDEFINES']:
            zig_file.write("\t\"-D{}\",\n".format(i))
        # conver LocalCDefines to CFlags
        for group in project:
            if 'LOCAL_CPPDEFINES' in group and group['LOCAL_CPPDEFINES']:
                for i in group['LOCAL_CPPDEFINES']:
                    zig_file.write("\t\"-D{}\",\n".format(i))        
        zig_file.write("};\n\n")

        zig_file.write("pub fn build(b: *std.Build) void {\n")
        zig_file.write("    const optimize = .ReleaseSmall;\n\n")

        if IS_ZIG_0_14_PLUS:
            zig_file.write("    const root_module = b.createModule(.{\n")
            zig_file.write("        .root_source_file = null,\n")
            zig_file.write("        .target = b.resolveTargetQuery(target),\n")
            zig_file.write("        .optimize = optimize,\n")
            zig_file.write("        .strip = false,\n")
            zig_file.write("    });\n\n")

            zig_file.write("    root_module.addCSourceFiles(.{ .files = &c_sources, .flags = &c_flags });\n")
            zig_file.write("    for (c_includes) |include| {\n")
            zig_file.write("        root_module.addIncludePath(b.path(include));\n")
            zig_file.write("    }\n\n")

            zig_file.write("    const elf = b.addExecutable(.{\n")
            zig_file.write("        .name = \"rtthread.elf\",\n")
            zig_file.write("        .root_module = root_module,\n")
            zig_file.write("    });\n\n")
        else:
            zig_file.write("    const elf = b.addExecutable(.{\n")
            zig_file.write("        .name = \"rtthread.elf\",\n")
            zig_file.write("        .target = b.resolveTargetQuery(target),\n")
            zig_file.write("        .optimize = optimize,\n")
            zig_file.write("        .strip = false,\n")
            zig_file.write("    });\n\n")

        zig_file.write("    elf.entry = .{ .symbol_name = \"Reset_Handler\" };\n\n")

        # find link script in rtconfig.LFLAGS
        LINK_SCRIPT = re.search(r'-T\s*(\S+)', LFLAGS)
        zig_file.write("    elf.setLinkerScript(b.path(\"{}\"));\n".format(LINK_SCRIPT.group(1)))

        zig_file.write("    const copy_elf = b.addInstallArtifact(elf, .{});\n")
        zig_file.write("    b.default_step.dependOn(&copy_elf.step);\n\n")

        zig_file.write("    const bin = b.addObjCopy(elf.getEmittedBin(), .{ .format = .bin });\n")
        zig_file.write("    bin.step.dependOn(&elf.step);\n")

        zig_file.write("    const copy_bin = b.addInstallBinFile(bin.getOutput(), \"rtthread.bin\");\n")
        zig_file.write("    b.default_step.dependOn(&copy_bin.step);\n")
        zig_file.write("}\n")
        zig_file.close()

    return

def ZigBuildProject(env,project):
    version_str = "{}.{}".format(ZIG_VERSION[0], ZIG_VERSION[1])
    print('Detected Zig version: {}'.format(version_str))
    if IS_ZIG_0_14_PLUS:
        print('Using Zig 0.14+ compatible build configuration')
    else:
        print('Using legacy build configuration')
    print('Update setting files for build.zig...')
    GenerateCFiles(env,project)
    print('Done!')

    return
