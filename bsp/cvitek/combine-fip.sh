#!/bin/bash

set -e

LITTLE_BIN=$1

. ./pre-build/fsbl/build/cv1800b_milkv_duo_sd/blmacros.env && \
./pre-build/fsbl/plat/cv180x/fiptool.py -v genfip \
	'fip.bin' \
	--MONITOR_RUNADDR="${MONITOR_RUNADDR}" \
	--BLCP_2ND_RUNADDR="${BLCP_2ND_RUNADDR}" \
	--CHIP_CONF='./pre-build/fsbl/build/cv1800b_milkv_duo_sd/chip_conf.bin' \
	--NOR_INFO='FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF' \
	--NAND_INFO='00000000'\
	--BL2='pre-build/fsbl/build/cv1800b_milkv_duo_sd/bl2.bin' \
	--BLCP_IMG_RUNADDR=0x05200200 \
	--BLCP_PARAM_LOADADDR=0 \
	--BLCP=pre-build/fsbl/test/empty.bin \
	--DDR_PARAM='pre-build/fsbl/test/cv181x/ddr_param.bin' \
	--BLCP_2ND=$LITTLE_BIN \
	--MONITOR='pre-build/fw_dynamic.bin' \
	--LOADER_2ND='pre-build/u-boot-raw.bin' \
	--compress='lzma'