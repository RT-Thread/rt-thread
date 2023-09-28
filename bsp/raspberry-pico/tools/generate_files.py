#! /usr/bin/env python3
import os
import sys
import shutil

# get the path of current file
cmd = os.path.split(os.path.realpath(__file__))[0]

if not os.path.exists(os.path.join(cmd, '../packages/raspberrypi-pico-sdk-latest')):
    print('Error: raspberrypi-pico-sdk not found, please run "pkgs --update" first')
    exit(1)

if os.path.exists(os.path.join(cmd, 'build')):
    shutil.rmtree(os.path.join(cmd, 'build'))


os.mkdir(os.path.join(cmd, 'build'))
os.chdir(os.path.join(cmd, 'build'))

# run cmake
os.system('cmake ' + os.path.join(cmd, '../packages/raspberrypi-pico-sdk-latest'))
os.system('make ELF2UF2Build bs2_default_padded_checksummed_asm')

# copy header files
shutil.copytree(os.path.join(cmd, 'build', 'generated'), os.path.join(cmd, 'generated'), dirs_exist_ok = True)

# copy the generated files to the destination
if "linux" in sys.platform:
    shutil.copyfile(os.path.join(cmd, 'build', 'elf2uf2', 'elf2uf2'), os.path.join(cmd, 'elf2uf2'))
if "win32" in sys.platform:
    shutil.copyfile(os.path.join(cmd, 'build', 'elf2uf2', 'elf2uf2.exe'), os.path.join(cmd, 'elf2uf2.exe'))

# copy bs2_default_padded_checksummed_asm
shutil.copyfile(os.path.join(cmd, 'build', 'src', 'rp2_common', 'boot_stage2', 'bs2_default_padded_checksummed.S'), \
    os.path.join(cmd, 'generated', 'bs2_default_padded_checksummed.S'))

# clean up
shutil.rmtree(os.path.join(cmd, 'build'))
