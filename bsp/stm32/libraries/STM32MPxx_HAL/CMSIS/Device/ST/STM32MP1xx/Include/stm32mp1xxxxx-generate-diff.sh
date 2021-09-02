#!/bin/bash

# Generate all CMSIS files

currdir=${PWD}
export scriptPATH=${PWD}/../../../../../../../__INTERNAL__tools/tools/_CmsisDeviceGenerator

if [ ! -d "${scriptPATH}" ] ; then
  echo Input directory does not exist
  return
fi

cd ${scriptPATH}

perl DeviceGeneration.pl  --target STM32MP1xx -diff

cd ${currdir}
