#!/bin/bash

RTT_PATH=$(realpath $(dirname $0)/..)
RTT_DOC_PATH=$RTT_PATH/documentation

rm -rf $RTT_DOC_PATH/html

cd $RTT_DOC_PATH
doxygen ./Doxyfile
if [ $? -ne 0 ]; then
    echo ""
    echo "OOPS: Something error/warning occurred during Doxygen building, please check it out!"
    echo ""
    exit 1
fi

pushd $RTT_DOC_PATH/html
python3 -m http.server