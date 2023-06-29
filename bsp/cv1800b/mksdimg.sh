#/bin/sh
set -e
echo "start compress kernel..."

lzma -c -9 -f -k Image > Image.lzma

./mkimage -f multi.its -r boot.sd