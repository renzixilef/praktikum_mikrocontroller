cmake_minimum_required(VERSION 3.22)

set(DEVICE_FAMILY STM32F40)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(
        MirkoController
        VERSION 0.1
        LANGUAGES C CXX ASM
)

set(CMAKE_C_COMPILER /opt/arm-gnu-toolchain/bin/arm-none-eabi-gcc)
set(CMAKE_MAKE_PROGRAM makefile)
set(CMAKE_CXX_COMPILER /opt/arm-gnu-toolchain/bin/arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER /opt/arm-gnu-toolchain/bin/arm-none-eabi-gcc)
set(CMAKE_OBJCOPY /opt/arm-gnu-toolchain/bin/arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP /opt/arm-gnu-toolchain/bin/arm-none-eabi-objdump)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)
set(CMAKE_SYSTEM_VERSION 1)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

file(GLOB_RECURSE SRC
        Core/Src/*.c
        Core/Src/*.s
        Core/Src/*.cpp
        Core/SystemFiles/Src/*.c
        Core/SystemFiles/Src/*.s
        Core/SystemFiles/Src/*.cpp
        Core/SystemFiles/Startup/*.s
        Drivers/*.c
        Drivers/*.cpp
        Drivers/*.s
        Startup/*.s
)

add_executable(MirkoController ${SRC})
set_target_properties(MirkoController PROPERTIES OUTPUT_NAME "MirkoController" SUFFIX ".elf")

target_include_directories(MirkoController PRIVATE
        Core/Inc
        Core/SystemFiles/Inc
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
        $<$<CONFIG:Debug>:-Os>
        -Os
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
        -Os
)

add_custom_command(TARGET MirkoController
        POST_BUILD
        COMMAND /opt/arm-gnu-toolchain/bin/arm-none-eabi-size MirkoController.elf
)

add_custom_command(TARGET MirkoController
        POST_BUILD
        COMMAND /opt/arm-gnu-toolchain/bin/arm-none-eabi-objcopy -O ihex MirkoController.elf ${PROJECT_NAME}.hex
        COMMAND /opt/arm-gnu-toolchain/bin/arm-none-eabi-objcopy -O binary MirkoController.elf ${PROJECT_NAME}.bin
)