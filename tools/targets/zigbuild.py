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

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import target_utils


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

    CFLAGS = target_utils.escape_quoted_flags(rtconfig.CFLAGS)
    LFLAGS = target_utils.escape_quoted_flags(rtconfig.LFLAGS)

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

        # include dirs: relative, de-duplicated, Zig-quoted list
        inc_dirs = [_make_path_relative(os.getcwd(), i).replace("\\", "/") for i in info['CPPPATH']]
        zig_file.write("const c_includes = [_][]const u8{\n")
        zig_file.write(target_utils.zig_list(target_utils.ordered_unique(inc_dirs)))
        zig_file.write("};\n\n")

        src_files = []
        for group in project:
            for f in group['src']:
                path = _make_path_relative(os.getcwd(), os.path.normpath(f.rfile().abspath))
                src_files.append(path.replace("\\", "/"))
        zig_file.write("const c_sources = [_][]const u8{\n")
        zig_file.write(target_utils.zig_list(target_utils.ordered_unique(src_files)))
        zig_file.write("};\n\n")

        # -D flags: tuple macros fold to FOO=1, global then per-group locals
        flag_defs = ["-D" + d for d in target_utils.normalize_defines(info['CPPDEFINES'])]
        for group in project:
            if 'LOCAL_CPPDEFINES' in group and group['LOCAL_CPPDEFINES']:
                flag_defs += ["-D" + d for d in target_utils.normalize_defines(group['LOCAL_CPPDEFINES'])]
        zig_file.write("const c_flags = [_][]const u8{\n")
        zig_file.write("\t\"-std=c99\",\n")
        zig_file.write("\t\"-ffunction-sections\",\n")
        zig_file.write("\t\"-fdata-sections\",\n")
        zig_file.write(target_utils.zig_list(target_utils.ordered_unique(flag_defs)))
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

        # find the linker script in LFLAGS -- handles -Tfoo, -T foo,
        # -T "dir with space/link.lds" and -Wl,-T,foo without truncating
        link_scripts = target_utils.normalize_link_script_flags(LFLAGS)
        link_script = link_scripts[0].replace("\\", "/") if link_scripts else ""
        zig_file.write("    elf.setLinkerScript(b.path({}));\n".format(
            target_utils.zig_quote(link_script)))

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
