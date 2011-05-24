#!/bin/bash

if [ -d /mnt/card ] 
then
echo "/mnt/card has been created"
else
sudo mkdir /mnt/card
fi
sudo mount -o loop,offset=32256 SDCARD /mnt/card

