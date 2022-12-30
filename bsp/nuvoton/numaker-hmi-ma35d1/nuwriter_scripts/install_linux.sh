#!/bin/bash

set -x -e

sudo apt-get install python3 python3-pip

pip3 install -r requirements.txt
