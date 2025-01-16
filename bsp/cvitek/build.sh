#!/bin/bash

source ./tools.sh

function usage() {
        echo "Usage:"
        echo "  ./build.sh [-h|-l|-b]"
        echo "  -h: display usage"
        echo "  -l: build c906L"
        echo "  -b: build c906B"
}

function build_c906b() {
	echo "build_c906b"

	BOARD_TYPE=`get_board_type $BSP_PATH/cv18xx_risc-v`
	echo "BOARD_TYPE: $BOARD_TYPE"

	DPT_PATH_KERNEL=$BSP_PATH/../../ DPT_BOARD_TYPE=$BOARD_TYPE DPT_PATH_OUTPUT=$BSP_PATH/output ./rttpkgtool/script/mkpkg.sh -b
}

function build_c906l() {
	echo "build_c906l"

	BOARD_TYPE=`get_board_type $BSP_PATH/c906_little`
	echo "BOARD_TYPE: $BOARD_TYPE"

	DPT_PATH_KERNEL=$BSP_PATH/../../ DPT_BOARD_TYPE=$BOARD_TYPE DPT_PATH_OUTPUT=$BSP_PATH/output ./rttpkgtool/script/mkpkg.sh -l
}

while getopts ":hbl" opt
do
        case $opt in
        h)
                O_HELP=y
                ;;
	b)
		O_MAKE_BIG=y
		;;
	l)
		O_MAKE_LITTLE=y
		;;
        ?)
                echo "Unrecognized parameter."
                usage
                exit 1
                ;;
    esac
done

if [ "$O_HELP" = "y" ]; then
	usage
	exit 0
fi

BSP_PATH=$(realpath $(dirname $0))
echo "BSP_PATH: $BSP_PATH"

download_rttpkgtool $BSP_PATH

if [ "$O_MAKE_BIG" = "y" ]; then
	build_c906b
fi

if [ "$O_MAKE_LITTLE" = "y" ]; then
	build_c906l
fi

