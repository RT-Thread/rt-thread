add_rules("mode.debug", "mode.release")

toolchain("${toolchain}")
    set_kind("standalone")
    set_sdkdir("${sdkdir}")
toolchain_end()

target("${target}")
    set_kind("binary")
    set_toolchains("${toolchain}")

    add_files(
        ${src_path}
    )

    add_includedirs(
        ${inc_path}
    )

    add_defines(
        ${define}
    )

    add_cflags(
        "${cflags}" ,{force = true}
    )
    add_cxxflags(
        "${cxxflags}" ,{force = true}
    )

    add_asflags(
        "${asflags}" ,{force = true}
    )

    add_ldflags(
        "${ldflags}" ,{force = true}
    )

    set_targetdir("./")
    set_filename("rtthread.elf")

    after_build(function(target)
        os.exec("${toolchain}-objcopy -O ihex rtthread.elf rtthread.hex")
        os.exec("${toolchain}-objcopy -O binary rtthread.elf rtthread.bin")
        os.exec("${toolchain}-size rtthread.elf")
    end)