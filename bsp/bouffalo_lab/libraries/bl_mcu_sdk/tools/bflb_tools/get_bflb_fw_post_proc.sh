#/bin/bash
CHIPNAME=$1
BIN_FILE=$2

SYSTEM=`uname -s`
echo "system: $SYSTEM"

SHELL_DIR=$(cd "$(dirname "$0")"; pwd)
TOOL_DIR=$SHELL_DIR

URL_GITEE="https://gitee.com/flyingcys/bflb_tools/releases/download/v1.0.4"
URL_GITHUB="https://github.com/flyingcys/bflb_tools/releases/download/v1.0.4"
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

    download_finish=0
    for i in 1 2 3
    do
        timeout=$(expr $i \* 60)
        for url in $URL_GITEE $URL_GITHUB
        do       
            # 连接超时30s 下载超时120s
            curl -C - -LjO --connect-timeout 30 -m $timeout $url/$FILE_NAME
            if [ $? -ne 0 ];then
                echo "download failed, try again..."
            else
                mkdir -p $TOOL_DIR/bflb_fw_post_proc
                tar zxvf $FILE_NAME -C $TOOL_DIR/bflb_fw_post_proc
                rm -rf $FILE_NAME
                if [ $SYSTEM = "Darwin" ]; then
                    chmod +x $TOOL_DIR/bflb_fw_post_proc/$TOOL_NAME
                elif [ $SYSTEM = "Linux" ]; then
                    chmod +x $TOOL_DIR/bflb_fw_post_proc/$TOOL_NAME
                fi

                download_finish=1
                break
            fi
        done

        if [ $download_finish -ne 0 ]; then
            break
        fi
    done
fi
