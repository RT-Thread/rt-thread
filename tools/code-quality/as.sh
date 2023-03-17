#!/bin/sh

astyle --style=allman --indent=spaces=4 --pad-oper --pad-header --unpad-paren --suffix=none --align-pointer=name --lineend=linux --convert-tabs --verbose $1
