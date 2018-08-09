#!/bin/bash

# This script will use git (must be in $PATH) and arm-none-eabi tools in combination with GNU Make
# to both fetch and compile all variants of micro-ecc for the nRF5 families

if ! [ -x "$(command -v git)" ]; then
    echo 'git is not installed. Please install and append to PATH.' >&2
    exit
fi

if [ ! -f micro-ecc/uECC.c ]; then
    echo "micro-ecc not found! Let's pull it from HEAD."
    git clone https://github.com/kmackay/micro-ecc.git
fi

make -C nrf51_armgcc/armgcc &&
make -C nrf51_iar/armgcc &&
make -C nrf51_keil/armgcc &&
make -C nrf52hf_armgcc/armgcc &&
make -C nrf52hf_iar/armgcc &&
make -C nrf52hf_keil/armgcc &&
make -C nrf52nf_armgcc/armgcc &&
make -C nrf52nf_iar/armgcc &&
make -C nrf52nf_keil/armgcc
