#/bin/sh
CHIPNAME=$1
PORT=$2

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

CONFIG_DIR=./bl60x
if [ $CHIPNAME = 'bl602' ]
then
    CONFIG_DIR=./bl60x
elif [ $CHIPNAME = 'bl616' ]
then
    CONFIG_DIR=./bl61x
elif [ $CHIPNAME = 'bl702' ]
then
    CONFIG_DIR=./bl70x
elif [ $CHIPNAME = 'bl808' ]
then
    CONFIG_DIR=./bl808
else
    echo "chip name error"
fi

TOOL_DIR=./libraries/bl_mcu_sdk/tools/bflb_tools/bouffalo_flash_cube
TOOL_NAME='BLFlashCommand'$TOOL_SUFFIX
CONFIG_FILE=$CONFIG_DIR'/flash_prog_cfg.ini'

./$TOOL_DIR/$TOOL_NAME --interface=uart --baudrate=2000000 --chipname=$CHIPNAME --config=$CONFIG_FILE --port=$PORT
