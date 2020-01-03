source [find interface/kitprog3.cfg]
source [find target/&&OPENOCDFILE&&]
${TARGET}.cm0 configure -gdb-port disabled
${TARGET}.cm4 configure -rtos auto -rtos-wipe-on-reset-halt 1
