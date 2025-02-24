#!/bin/bash

#This script can automatically generate doxygen documentation.

# 设置Doxygen配置文件路径（如果有）
DOXYFILE="Doxyfile"
HTML_DIR="./html"

# 清理旧的HTML目录(如果有)
echo "Cleaning up old HTML directory(if exists)..."
if [ -d "$HTML_DIR" ]; then
    rm -rf "$HTML_DIR"
    if [ $? -ne 0 ]; then
        echo "Failed to remove old HTML directory."
        exit 1
    fi
fi

# 运行Doxygen生成新的文档
echo "Generating new documentation with Doxygen..."
doxygen "$DOXYFILE"
if [ $? -ne 0 ]; then
    echo "OOPS: Something error/warning occurred during Doxygen building, please check it out!"
    exit 1
fi

# 启动HTTP服务器来展示生成的文档
echo "Starting HTTP server to serve the generated documentation..."
cd "$HTML_DIR"
if [ $? -ne 0 ]; then
    echo "Failed to change directory to $HTML_DIR"
    exit 1
fi

python3 -m http.server
if [ $? -ne 0 ]; then
    echo "Failed to start the HTTP server."
    exit 1
fi#!/bin/bash

# 设置Doxygen配置文件路径（如果有）
DOXYFILE="Doxyfile"
HTML_DIR="./html"

# 清理旧的HTML目录
echo "Cleaning up old HTML directory..."
if [ -d "$HTML_DIR" ]; then
    rm -rf "$HTML_DIR"
    if [ $? -ne 0 ]; then
        echo "Failed to remove old HTML directory."
        exit 1
    fi
fi

# 运行Doxygen生成新的文档
echo "Generating new documentation with Doxygen..."
doxygen "$DOXYFILE"
if [ $? -ne 0 ]; then
    echo "OOPS: Something error/warning occurred during Doxygen building, please check it out!"
    exit 1
fi

# 启动HTTP服务器来展示生成的文档
echo "Starting HTTP server to serve the generated documentation..."
cd "$HTML_DIR"
if [ $? -ne 0 ]; then
    echo "Failed to change directory to $HTML_DIR"
    exit 1
fi

python3 -m http.server
if [ $? -ne 0 ]; then
    echo "Failed to start the HTTP server."
    exit 1
fi
