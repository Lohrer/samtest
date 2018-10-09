# 3.5.1 in xenial, 3.10.2 in bionic
cmake_minimum_required(VERSION 3.0.2)
project(samtest)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

if(MINGW OR CYGWIN OR WIN32)
    set(UTIL_SEARCH_CMD where)
elseif(UNIX OR APPLE)
    set(UTIL_SEARCH_CMD which)
endif()

set(TOOLCHAIN_PREFIX arm-none-eabi-)

execute_process(
  COMMAND ${UTIL_SEARCH_CMD} ${TOOLCHAIN_PREFIX}gcc
  OUTPUT_VARIABLE BINUTILS_PATH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

get_filename_component(ARM_TOOLCHAIN_DIR ${BINUTILS_PATH} DIRECTORY)

#CMAKE_FORCE_C_COMPILER("arm-none-eabi-gcc" GNU)
set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER})
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++)

# Workaround to remove -rdynamic option
SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")

include_directories(
    xdk-asf
    xdk-asf/include
    xdk-asf/cmsis
)
link_directories(
    xdk-asf
)

add_executable(${PROJECT_NAME}.elf
    samtest.c
    xdk-asf/startup_same70.c
    xdk-asf/system_same70.c
)
target_compile_options(${PROJECT_NAME}.elf PRIVATE -mcpu=cortex-m7 -mthumb -g -D__SAME70Q21B__)
target_link_libraries(${PROJECT_NAME}.elf -Wl,-Map=samtest.map -Tflash.ld -mthumb -mcpu=cortex-m7 -Wl,--gc-sections -Wl,--entry=Reset_Handler)
