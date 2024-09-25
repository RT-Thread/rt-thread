#/bin/sh

#add_firmHead  xxx.bin  "-n"
#output fn_$1 fa_$1 fs_$1
add_firmHead()
{
	local filename="$1"
	local firmware_gen="tools/firmware_gen.py"

	if [ $# -ge 2 ]; then 
		firmArgs="$2" #add k230 firmware head
		cp ${filename} ${filename}.t; python3  ${firmware_gen} -i ${filename}.t -o f${firmArgs##-}${filename} ${firmArgs};
	else 
		 #add k230 firmware head
		firmArgs="-n"; cp ${filename} ${filename}.t; python3  ${firmware_gen} -i ${filename}.t -o f${firmArgs##-}_${filename} ${firmArgs};
	fi
	rm -rf  ${filename}.t
}

k230_gzip()
{
	local filename="$1"
	local k230_gzip_tool="tools/k230_priv_gzip "

	${k230_gzip_tool} -n8  -f -k ${filename}  ||   ${k230_gzip_tool} -n9 -f -k ${filename} ||  \
	${k230_gzip_tool} -n7 -f -k ${filename}   ||   ${k230_gzip_tool} -n6 -f -k ${filename} || \
	${k230_gzip_tool} -n5 -f -k ${filename}   ||   ${k230_gzip_tool} -n4 -f -k ${filename}

	sed -i -e "1s/\x08/\x09/"  ${filename}.gz
}

bin_gzip_ubootHead_firmHead()
{
    local mkimage="tools/mkimage"
	local file_full_path="$1"
	local filename=$(basename ${file_full_path})
	local mkimgArgs="$2"
	local firmArgs="$3"

	[ "$(dirname ${file_full_path})" == "$(pwd)" ] || cp ${file_full_path} .

    k230_gzip ${filename}

	#add uboot head 
	${mkimage} -A riscv -C gzip  ${mkimgArgs} -d ${filename}.gz  ug_${filename}

	add_firmHead ug_${filename}
	rm -rf ${filename}  ${filename}.gz ug_${filename}
}

gen_rtt_bin()
{
    local filename="fw_payload.bin"
    local CONFIG_MEM_RTT_SYS_BASE="0x200000"

	bin_gzip_ubootHead_firmHead "opensbi/build/platform/kendryte/fpgac908/firmware/${filename}"  \
			 "-O opensbi -T multi  -a ${CONFIG_MEM_RTT_SYS_BASE} -e ${CONFIG_MEM_RTT_SYS_BASE} -n rtt"
    
    mv fn_ug_${filename}  rtt_system.bin
}

build_sbi()
{
    cc=~/.tools/gnu_gcc/riscv64-linux-musleabi_for_x86_64-pc-linux-gnu/bin/riscv64-unknown-linux-musl-

    if [ -n "$1" ]; then
        cc=$1
    fi

    cd opensbi && make FW_PAYLOAD_PATH=../rtthread.bin FW_FDT_PATH=hw.dtb PLATFORM=kendryte/fpgac908 CROSS_COMPILE=$cc

    cd ..
}

build_sbi $1

gen_rtt_bin
