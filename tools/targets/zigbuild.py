"""
Utils for CMake
Author: https://github.com/klivelinux
"""

import os
import sys
import re
import utils
import rtconfig
from utils import _make_path_relative


def GenerateCFiles(env,project):
    info = utils.ProjectInfo(env)

    ARCH = ".thumb" if rtconfig.CPU in ['cortex-m0', 'cortex-m3', 'cortex-m4', 'cortex-m7','cortex-m23','cortex-m33','cortex-m85'] else ".arm"

    CFLAGS = rtconfig.CFLAGS.replace('\\', "/").replace('\"', "\\\"")
    LFLAGS = rtconfig.LFLAGS.replace('\\', "/").replace('\"', "\\\"")

    zig_file = open('build.zig', 'w')
    if zig_file:
        zig_file.write("const std = @import(\"std\");\n\n")

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
        zig_file.write("    const optimize = .ReleaseSafe;\n\n")

        zig_file.write("    const elf = b.addExecutable(.{\n")
        zig_file.write("        .name = \"rtthread.elf\",\n")
        zig_file.write("        .target = b.resolveTargetQuery(target),\n")
        zig_file.write("        .optimize = optimize,\n")
        zig_file.write("        .strip = false,\n")
        zig_file.write("    });\n\n")
        zig_file.write("    elf.entry = .{ .symbol_name = \"Reset_Handler\" };\n\n")

        zig_file.write("    elf.addCSourceFiles(.{ .files = &c_sources, .flags = &c_flags });\n")
        zig_file.write("    for (c_includes) |include| {\n")
        zig_file.write("        elf.addIncludePath(b.path(include));\n")
        zig_file.write("    }\n\n")

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
    print('Update setting files for build.zig...')
    GenerateCFiles(env,project)
    print('Done!')

    return
