if [ ! -f "sdroot.bin" ]; then
dd if=/dev/zero of=sdroot.bin bs=1M count=4
fi

mkfs.fat sdroot.bin
mcopy -i sdroot.bin root/bin/* ::

