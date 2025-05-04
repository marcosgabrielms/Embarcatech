cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PICO_BOARD pico_w CACHE STRING "Board type")

include(pico_sdk_import.cmake)

project(led_control_webserver C CXX ASM)

pico_sdk_init()

add_executable(led_control_webserver
    src/main.c
    src/led_control.c
    src/temperature.c    # Nova modularização para a temperatura
    src/wifi.c
    
)

# Nome e Versão do programa
pico_set_program_name(led_control_webserver "led_control_webserver")
pico_set_program_version(led_control_webserver "0.1")

# Habilitando as saídas para a UART e USB
pico_enable_stdio_uart(led_control_webserver 0)
pico_enable_stdio_usb(led_control_webserver 1)

# Linkagem das bibliotecas necessárias
target_link_libraries(led_control_webserver
    pico_stdlib
    hardware_gpio
    hardware_adc
    pico_cyw43_arch_lwip_threadsafe_background # Biblioteca do Wifi
)

# Definir os diretórios de include

target_include_directories(led_control_webserver PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include() # Diretório dos cabeçalhos(.h)
)

# Geração de saídas extras
pico_add_extra_outputs(led_control_webserver)
