#!/bin/bash

rm -rf ./html

doxygen

pushd html
python3 -m http.server