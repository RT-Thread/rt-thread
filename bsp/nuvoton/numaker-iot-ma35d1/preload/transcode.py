# -*- coding: UTF-8 -*- 

import os

def extract_line(fname, pattern):
    with open(fname, "r") as f:
        lines = f.readlines()
        f.close()
    with open("entry_point.S", "w") as f:
        counter=0
        f.write(".section \".text.entrypoint\"\n")
        f.write(".globl system_vectors\n")
        f.write("\n")
        f.write("ma35d1_start:\n")
        for line in lines:
            if pattern in line:
                new_line = "    .word    0x" + line[6:14] + "\n"
                f.write(new_line)
                counter = counter+1
        f.write("\n")
        f.write(".L__aarch32_code:\n")
        f.write("\n")
        # Append NOP to align vector table.
        counter = (counter+5)*4
        counter_align = (counter+32-1) & ~(32-1)
        nop_num = (counter_align - counter) / 4
        print hex(counter), hex(counter_align), nop_num
        j = 0
        while j < nop_num:
            f.write("    nop\n")
            j += 1
        f.write("    ldr     r0, =ma35d1_start\n")
        f.write("    mov     sp, r0\n")
        f.write("    ldr     pc, =system_vectors\n")
        f.close()

def formatfiles():
    extract_line("preload.txt", ":\t")

if __name__ == '__main__':
    formatfiles()
