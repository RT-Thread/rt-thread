#/bin/bash
CHIPNAME=$1
BIN_FILE=$2

set -e

SYSTEM=`uname -s`
echo "system: $SYSTEM"

SHELL_DIR=$(cd "$(dirname "$0")"; pwd)
TOOL_DIR=$SHELL_DIR

URL_GITEE=https://gitee.com/flyingcys/bflb_tools/releases/download/v1.0.4
URL_GITHUB=https://github.com/flyingcys/bflb_tools/releases/download/v1.0.4
if [ $SYSTEM = "Darwin" ]
then
    TOOL_NAME=BLFlashCommand-macos
    FILE_NAME=bouffalo_flash_cube-macos.tar.gz
elif [ $SYSTEM = "Linux" ]
then
    TOOL_NAME=BLFlashCommand-ubuntu
    FILE_NAME=bouffalo_flash_cube-linux.tar.gz
else
    TOOL_NAME=BLFlashCommand.exe
    FILE_NAME=bouffalo_flash_cube-win.tar.gz
fi

DOWNLOAD_URL=$URL_GITEE
if [ -f "$TOOL_DIR/$TOOL_NAME" ]
then
    echo "bouffalo_flash_cube exist"
else
    echo "bouffalo_flash_cube not exist, try download... "
    echo "url:$DOWNLOAD_URL/$FILE_NAME"

    # 连接超时30s 下载超时300s
    curl -LjO --connect-timeout 30 -m 300 $DOWNLOAD_URL/$FILE_NAME

    tar zxvf $FILE_NAME -C $TOOL_DIR
    rm -rf $FILE_NAME
    if [ $SYSTEM = "Darwin" ]; then
        chmod +x $TOOL_DIR/bouffalo_flash_cube/$TOOL_NAME
    elif [ $SYSTEM = "Linux" ]; then
        chmod +x $TOOL_DIR/bouffalo_flash_cube/$TOOL_NAME
    fi
fi
