#/bin/sh
CHIPNAME=$1
BIN_FILE=$2

set -e

SYSTEM=`uname -s`
echo "system: $SYSTEM"

CONFIG=./board/config
TOOL_DIR=../libraries/bl_mcu_sdk/tools/bflb_tools/bflb_fw_post_proc

if [ $SYSTEM = "Darwin" ]
then
    TOOL_NAME=bflb_fw_post_proc-macos
    TOOL_ADDR=https://raw.githubusercontent.com/bouffalolab/bl_mcu_sdk/master/tools/bflb_tools/bflb_fw_post_proc/bflb_fw_post_proc-macos
elif [ $SYSTEM = "Linux" ]
then
    TOOL_NAME=bflb_fw_post_proc-ubuntu
    TOOL_ADDR=https://raw.githubusercontent.com/bouffalolab/bl_mcu_sdk/master/tools/bflb_tools/bflb_fw_post_proc/bflb_fw_post_proc-ubuntu
else
    TOOL_NAME=bflb_fw_post_proc.exe
    TOOL_ADDR=https://raw.githubusercontent.com/bouffalolab/bl_mcu_sdk/master/tools/bflb_tools/bflb_fw_post_proc/bflb_fw_post_proc.exe
fi

if [ -f "$TOOL_DIR/$TOOL_NAME" ]
then
    echo "bflb_fw_post_proc exist"
else
    echo "bflb_fw_post_proc not exist, try download... url:$TOOL_ADDR"
    curl $TOOL_ADDR -o $TOOL_DIR/$TOOL_NAME
    chmod +x $TOOL_DIR/$TOOL_NAME
fi

./$TOOL_DIR/$TOOL_NAME --chipname=$CHIPNAME --brdcfgdir=$CONFIG --imgfile=$BIN_FILE