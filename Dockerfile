FROM gcc AS build

RUN apt update
RUN apt install -y cmake python3 build-essential gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib git

RUN git clone https://github.com/Gonanf/van_turco

WORKDIR /van_turco

RUN git clone https://github.com/raspberrypi/pico-sdk

WORKDIR /van_turco/pico-sdk

RUN git submodule update --init 

WORKDIR /van_turco

CMD cmake -B build -DPICO_BOARD=pico_w;cmake --build build
