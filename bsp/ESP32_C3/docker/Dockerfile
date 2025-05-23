FROM ubuntu:22.04

ARG HTTP_PROXY
ARG HTTPS_PROXY
ENV http_proxy=${HTTP_PROXY}
ENV https_proxy=${HTTPS_PROXY}


# 1. Basic options(with root)
RUN apt update && \
    apt install -y software-properties-common && \
    add-apt-repository universe && \
    apt update && \
    apt install -y --no-install-recommends \
        sudo git wget python3 python3-pip scons vim xz-utils minicom && \
    pip3 install esptool && \
    useradd -m dev && \
    echo "dev ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

# 2. Switch to dev user
USER dev
WORKDIR /home/dev

# 3. Install esp-idf toolchains
RUN wget -q https://github.com/espressif/crosstool-NG/releases/download/esp-2022r1-RC1/riscv32-esp-elf-gcc11_2_0-esp-2022r1-RC1-linux-amd64.tar.xz && \
    sudo tar -xf riscv32-esp-elf-gcc11_2_0-esp-2022r1-RC1-linux-amd64.tar.xz -C /opt

# 4. Clone RT-Thread and switch master
RUN git clone https://github.com/RT-Thread/rt-thread.git && \
    cd rt-thread && \
    git switch master

# 5. Install env tools
WORKDIR /home/dev/rt-thread
RUN wget https://raw.githubusercontent.com/RT-Thread/env/master/install_ubuntu.sh && \
    chmod +x install_ubuntu.sh && \
    ./install_ubuntu.sh

# 6. Modify toolchains path
RUN sed -i "s|^.*EXEC_PATH.*|    EXEC_PATH   = r'/opt/riscv32-esp-elf/bin'|" bsp/ESP32_C3/rtconfig.py

# 7. Set enviroment variables
ENV PATH="/opt/riscv32-esp-elf/bin:/home/dev/.env/tools/scripts:$PATH"

# 8. Update rtthread packages
WORKDIR /home/dev/rt-thread/bsp/ESP32_C3
RUN pkgs --update

