FROM ubuntu:22.04

ARG HTTP_PROXY
ARG HTTPS_PROXY
ENV http_proxy=${HTTP_PROXY}
ENV https_proxy=${HTTPS_PROXY}

RUN apt update && \
    apt install -y --no-install-recommends \
        sudo git wget python3 python3-pip scons xz-utils ca-certificates && \
    pip3 install esptool && \
    useradd -m dev && \
    echo "dev ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

USER dev
WORKDIR /home/dev

RUN wget -q https://github.com/espressif/crosstool-NG/releases/download/esp-2022r1-RC1/riscv32-esp-elf-gcc11_2_0-esp-2022r1-RC1-linux-amd64.tar.xz && \
    sudo tar -xf riscv32-esp-elf-gcc11_2_0-esp-2022r1-RC1-linux-amd64.tar.xz -C /opt && \
    rm riscv32-esp-elf-gcc11_2_0-esp-2022r1-RC1-linux-amd64.tar.xz

ENV PATH="/opt/riscv32-esp-elf/bin:${PATH}"

# 本 BSP 还没进上游。把含有 bsp/ESP/ESP32_C6 的 RT-Thread 树挂到 /home/dev/rt-thread 后再编译。
WORKDIR /home/dev/rt-thread/bsp/ESP/ESP32_C6
CMD ["scons", "--exec-path=/opt/riscv32-esp-elf/bin"]
