toolchain("aarch64-smart-musleabi")
    set_kind("standalone")
    
    local exec_path = os.getenv("RTT_EXEC_PATH") or "/opt/aarch64-linux-musleabi/bin/"
    local sdkdir = exec_path .. "/../"
    set_bindir(exec_path)
    set_sdkdir(sdkdir)

    local device = '-march=armv8-a -mtune=cortex-a53 -ftree-vectorize -ffast-math -funwind-tables -fno-strict-aliasing'
    local ldsfile = os.curdir() .. "/los_vdso.lds"
    local incdir = os.curdir() .. "/../include"

    on_load(function(toolchain)
        toolchain:load_cross_toolchain()
        toolchain:add("cxflags", device)
        toolchain:add("cxflags", "-Wall -Wno-cpp -std=gnu99")
        toolchain:add("cxflags", "-fdiagnostics-color=always")
        toolchain:add("cxflags", "-I" .. incdir)
        
        toolchain:add("ldflags", device)
        toolchain:add("ldflags", "-Wl,--gc-sections")
        toolchain:add("ldflags", "-u,system_vectors")
        toolchain:add("ldflags", "-T" .. ldsfile)
        
    end)
toolchain_end()

set_config("plat", "cross")
set_config("target_os", "rt-smart")
set_config("arch", "aarch64")

target("rtos_vdso")
    set_toolchains("aarch64-smart-musleabi")

    set_kind("shared")
    add_files("los_vdso_sys.c")
    set_targetdir("./build")
target_end()