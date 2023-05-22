#/bin/sh
CHIPNAME=$1
BIN_FILE=$2

set -e

SYSTEM=`uname -s`
echo "system: $SYSTEM"

CONFIG=../config
TOOL_DIR=../../libraries/bl_mcu_sdk/tools/bflb_tools

if [ $SYSTEM = "Darwin" ]
then
    TOOL_NAME=bflb_fw_post_proc-macos
elif [ $SYSTEM = "Linux" ]
then
    TOOL_NAME=bflb_fw_post_proc-ubuntu
else
    TOOL_NAME=bflb_fw_post_proc.exe
fi

if [ -f "$TOOL_DIR/bflb_fw_post_proc/$TOOL_NAME" ]
then
    echo "bflb_fw_post_proc exist"
else
    echo "bflb_fw_post_proc not exist, try download... "
    ./$TOOL_DIR/get_bflb_fw_post_proc.sh
fi

./$TOOL_DIR/bflb_fw_post_proc/$TOOL_NAME --chipname=$CHIPNAME --brdcfgdir=$CONFIG --imgfile=$BIN_FILE