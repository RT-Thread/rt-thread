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
    TOOL_NAME=bflb_fw_post_proc-macos
    FILE_NAME=bflb_fw_post_proc-macos.tar.gz
elif [ $SYSTEM = "Linux" ]
then
    TOOL_NAME=bflb_fw_post_proc-ubuntu
    FILE_NAME=bflb_fw_post_proc-linux.tar.gz
else
    TOOL_NAME=bflb_fw_post_proc.exe
    FILE_NAME=bflb_fw_post_proc-win.tar.gz
fi

DOWNLOAD_URL=$URL_GITEE
if [ -f "$TOOL_DIR/$TOOL_NAME" ]
then
    echo "bflb_fw_post_proc exist"
else
    echo "bflb_fw_post_proc not exist, try download... "
    echo "url:$DOWNLOAD_URL/$FILE_NAME"

    # 连接超时30s 下载超时120s
    curl -LjO --connect-timeout 30 -m 120 $DOWNLOAD_URL/$FILE_NAME

    mkdir -p $TOOL_DIR/bflb_fw_post_proc
    tar zxvf $FILE_NAME -C $TOOL_DIR/bflb_fw_post_proc
    rm -rf $FILE_NAME
    if [ $SYSTEM = "Darwin" ]; then
        chmod +x $TOOL_DIR/bflb_fw_post_proc/$TOOL_NAME
    elif [ $SYSTEM = "Linux" ]; then
        chmod +x $TOOL_DIR/bflb_fw_post_proc/$TOOL_NAME
    fi
fi
