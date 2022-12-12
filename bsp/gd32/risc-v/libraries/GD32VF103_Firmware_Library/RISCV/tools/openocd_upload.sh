#! /bin/bash -x

work/build/openocd/prefix/bin/openocd -f ${2} \
	-c "flash protect 0 0 last off; program ${1} verify; resume 0x20000000; exit" \
	2>&1 | tee openocd_upload.log
