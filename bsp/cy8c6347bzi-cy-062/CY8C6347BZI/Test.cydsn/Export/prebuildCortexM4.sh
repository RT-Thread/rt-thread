#!/bin/sh
# This script allows a 3rd party IDE to use cymcuelftool.exe to perform
# the pre processing that is necessary to extract the bootloader
# data from the *.elf file for use when building the bootloadable
# application.
# NOTE: This script is auto generated. Do not modify.
# 
# Copy cymcuelftool executable from CMSIS-Pack into project
if [ "$2" == "eclipse" ]; then
OSTYPE=
if [ "$3" == "win32" ]; then
    OSTYPE=win
elif [ "$3" == "linux" ]; then
    OSTYPE=linux
else
    OSTYPE=osx
fi

for f in "$1//$OSTYPE/elf"/cymcuelftool*
do
cp -f "$f" .
LAST_EXIT=$?
if [ $LAST_EXIT != 0 ]; then
    exit $LAST_EXIT
fi
done

    exit
fi

