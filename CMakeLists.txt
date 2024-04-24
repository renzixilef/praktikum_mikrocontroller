cmake_minimum_required(VERSION 3.22)

set(DEVICE_FAMILY STM32F40)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(
        MirkoController
        VERSION 0.1
        LANGUAGES C CXX ASM
)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_MAKE_PROGRAM makefile)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)
set(CMAKE_SYSTEM_VERSION 1)

set(CMAKE_TRY_COMPILE_TARGET_TYPE EXECUTABLE)

file(GLOB_RECURSE SRC
        Core/*.c
        Core/*.s
        Core/*.cpp
        Drivers/*.c
        Drivers/*.cpp
        Drivers/*.s
        Startup/*.s
)

add_executable(MirkoController ${SRC})
set_target_properties(MirkoController PROPERTIES OUTPUT_NAME "MirkoController" SUFFIX ".elf")

target_include_directories(MirkoController PRIVATE
        Core/Inc
        Drivers/CMSIS/Device/ST/STM32F0xx/Include
        Drivers/CMSIS/Include
        Drivers/STM32F0xx_HAL_Driver/Inc
        Drivers/STM32F0xx_HAL_Driver/Inc/Legacy
)

target_compile_definitions(MirkoController PRIVATE -DUSE_HAL_DRIVER -DSTM32F051x8)

target_compile_options(MirkoController PRIVATE
        -mcpu=cortex-m0
        -mfloat-abi=soft
        -mthumb
        -ffunction-sections
        -fdata-sections
        -fstack-usage
        -Wall
        -g3
        $<$<CONFIG:Debug>:-Og>
)

target_link_options(MirkoController PRIVATE
        -T${CMAKE_CURRENT_LIST_DIR}/STM32F051R8TX_FLASH.ld
        -specs=nano.specs
        -specs=nosys.specs
        -mcpu=cortex-m0
        -mthumb
        -Wall
        -mfloat-abi=soft
        -Wl,-Map=${PROJECT_NAME}.map,--cref
        -static
        -lc
        -lm
)

add_custom_command(TARGET MirkoController
        POST_BUILD
        COMMAND arm-none-eabi-objcopy -O ihex MirkoController.elf ${PROJECT_NAME}.hex
        COMMAND arm-none-eabi-objcopy -O binary MirkoController.elf ${PROJECT_NAME}.bin)