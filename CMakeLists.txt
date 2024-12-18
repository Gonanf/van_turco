cmake_minimum_required(VERSION 3.13)
set(PICO_BOARD "pico_w")

include(pico-sdk/pico_sdk_init.cmake)
project(van_turco)
pico_sdk_init()

add_executable(van_turco ./src/main.cpp)
target_link_libraries(van_turco pico_stdlib pico_cyw43_arch_none )

pico_add_extra_outputs(van_turco)