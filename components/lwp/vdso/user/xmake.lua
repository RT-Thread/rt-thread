/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2024-07-04     rcitach        init ver.
 */
 
toolchain("aarch64-smart-musleabi")
    set_kind("standalone")
    
    local exec_path = os.getenv("RTT_EXEC_PATH") or "/opt/aarch64-linux-musleabi/bin/"
    local sdkdir = exec_path .. "/../"
    local incdir = os.curdir() .. "/../include"
    local device = '-march=armv8-a -mtune=cortex-a53 -ftree-vectorize -ffast-math -funwind-tables -fno-strict-aliasing'
    
    set_bindir(exec_path)
    set_sdkdir(sdkdir)
    
    set_toolset("sh", "aarch64-linux-musleabi-gcc")
    on_load(function(toolchain)
        toolchain:load_cross_toolchain()
        toolchain:add("cxflags", device)
        toolchain:add("cxflags", "-Wall -Wno-cpp -std=gnu99")
        toolchain:add("cxflags", "-fdiagnostics-color=always")
        toolchain:add("cxflags", "-O2")
        toolchain:add("cxflags", "-I" .. incdir)

        toolchain:add("shflags", device)
        toolchain:add("shflags", "-Wl,--gc-sections")
        toolchain:add("shflags", "-u,system_vectors")
        toolchain:add("shflags", "-T vdso.lds")
    end)
toolchain_end()

set_config("plat", "cross")
set_config("target_os", "rt-smart")
set_config("arch", "aarch64")

rule("vdso_lds")
    set_extensions(".lds.S")
    on_buildcmd_file(function (target, batchcmds, sourcefile, opt)
        local incdir = os.curdir() .. "/../include"
        local targetfile = path.basename(sourcefile)
        local prefix = os.getenv("RTT_CC_PREFIX=") or "aarch64-linux-musleabi-"
        batchcmds:vrunv(prefix .. "gcc", {"-E", "-P", sourcefile, "-o", targetfile, "-I", incdir})
    end)

target("rtos_vdso")
    set_toolchains("aarch64-smart-musleabi")
    add_rules("vdso_lds")
    set_kind("shared")
    add_files("vdso.lds.S")
    add_files("vdso_sys.c")
    set_targetdir("build")
target_end()
