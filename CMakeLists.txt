cmake_minimum_required(VERSION 3.13)
set(PICO_BOARD "pico_w")

IF (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/pico-sdk)
    message(STATUS "Pico SDK found in the source directory")
    IF (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/pico-sdk/lib/cyw43-driver/cyw43.h)
        message(STATUS "Found the submodules in the pico-sdk directory")
    ELSE()
        message(STATUS "No submodules found in the pico-sdk directory, cloning from git") 
        execute_process(COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_CURRENT_SOURCE_DIR}/pico-sdk git submodule update --init)
    ENDIF()
    include(pico-sdk/pico_sdk_init.cmake)

ELSE()
    message(STATUS "Pico SDK not found, cloning from git")
    set(PICO_SDK_FETCH_FROM_GIT on)
    include(pico_sdk_import.cmake)
ENDIF()
project(van_turco)
pico_sdk_init() 


add_executable(van_turco ./src/main.cpp)

pico_generate_pio_header(van_turco ${CMAKE_CURRENT_LIST_DIR}/modules/vga_test/rgb.pio)
pico_generate_pio_header(van_turco ${CMAKE_CURRENT_LIST_DIR}/modules/vga_test/hsync.pio)
pico_generate_pio_header(van_turco ${CMAKE_CURRENT_LIST_DIR}/modules/vga_test/vsync.pio)

target_link_libraries(van_turco pico_stdlib pico_cyw43_arch_none hardware_pio hardware_dma hardware_adc hardware_irq )

pico_add_extra_outputs(van_turco)