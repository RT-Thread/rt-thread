sudo mount ./boot.fat ./tmp/
sudo rm -rf tmp/kernel/*
sudo cp -rp ../rtthread.bin tmp/kernel/
sudo cp -rp ../rtthread.elf tmp/kernel/
sudo cp -rp ../rtthread.img tmp/kernel/
sudo cp -rp ../rtthread.imx tmp/kernel/
sudo sync
sudo umount ./tmp
sudo cp boot.fat image/input/
cd image
rm -rf tmp
./genimage