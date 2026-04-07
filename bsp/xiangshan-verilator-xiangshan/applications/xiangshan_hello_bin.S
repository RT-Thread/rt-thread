/*
 * Embed XiangShan guest workload (hello.bin) into the RT-Thread image.
 *
 * This file relies on the NOOP_HOME_PATH macro, which the build system
 * defines as a bare (unquoted) absolute path to the XiangShan root,
 * e.g.  -DNOOP_HOME_PATH=/path/to/XiangShan
 *
 * The preprocessor stringify operator turns the macro-expanded token
 * sequence into a single string literal suitable for .incbin.
 *
 * The two symbols exported here are consumed by
 * xiangshan_rtthread_main.cpp to construct the "wim@addr+size"
 * in-memory image descriptor passed to XiangShan's RAM initialisation.
 */

#ifndef NOOP_HOME_PATH
#error "NOOP_HOME_PATH must be defined to the XiangShan root (bare path, no quotes)"
#endif

#define _STRINGIFY(x) #x
#define STRINGIFY(x)  _STRINGIFY(x)

    .section .rodata
    .balign 8
    .global xiangshan_hello_bin_start
xiangshan_hello_bin_start:
    .incbin STRINGIFY(NOOP_HOME_PATH/ready-to-run/hello.bin)
    .global xiangshan_hello_bin_end
xiangshan_hello_bin_end:
