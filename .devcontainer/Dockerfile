FROM ubuntu:20.04

ARG DEST_DIR=/root

WORKDIR ${DEST_DIR}

#system
RUN apt-get update

RUN apt-get upgrade -y

RUN apt-get install -y vim git wget python3 python-is-python3 pip gcc-arm-none-eabi scons libncurses5-dev

RUN DEBIAN_FRONTEND=noninteractive apt-get install -y qemu-system-arm

#env
RUN mkdir /root/.env

RUN mkdir /root/.env/tools

RUN mkdir /root/.env/packages

RUN mkdir /root/.env/packages/packages

RUN mkdir /root/.env/tools/scripts

RUN touch /root/.env/packages/Kconfig

RUN echo 'source "$PKGS_DIR/packages/Kconfig"' > /root/.env/packages/Kconfig

RUN git clone https://github.com/RT-Thread/env.git /root/.env/tools/scripts/

RUN git clone https://github.com/RT-Thread/packages.git /root/.env/packages/packages/

ENV PATH="/root/.env/tools/scripts:$PATH"

RUN pip install requests -qq

ENV RTT_EXEC_PATH=/usr/bin

ENV RTT_CC=gcc

WORKDIR /root



