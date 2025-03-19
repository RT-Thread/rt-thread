#!/bin/bash

rm -rf ./html

doxygen
if [ $? -ne 0 ]; then
    echo ""
    echo "OOPS: Something error/warning occurred during Doxygen building, please check it out!"
    echo ""
    exit 1
fi

pushd html
python3 -m http.server