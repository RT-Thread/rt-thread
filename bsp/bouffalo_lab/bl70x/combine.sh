#/bin/sh
CHIPNAME=$1
BIN_FILE=$2

set -e

SYSTEM=`uname -s`
TOOL_SUFFIX=-ubuntu
echo "system: $SYSTEM"

if [ $SYSTEM = "Darwin" ]
then
    TOOL_SUFFIX=-macos
elif [ $SYSTEM = "Linux" ]
then
    TOOL_SUFFIX=-ubuntu
else
    TOOL_SUFFIX=.exe
fi

TOOL_DIR=../libraries/bl_mcu_sdk/tools/bflb_tools/bflb_fw_post_proc
TOOL_NAME='bflb_fw_post_proc'$TOOL_SUFFIX
CONFIG=./board/config

./$TOOL_DIR/$TOOL_NAME --chipname=$CHIPNAME --brdcfgdir=$CONFIG --imgfile=$BIN_FILE