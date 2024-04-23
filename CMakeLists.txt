cmake_minimum_required(VERSION 3.22)

set(DEVICE_FAMILY STM32F40_41xxx)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_TRY_COMPILE_TARGET_TYPE   STATIC_LIBRARY)

project(
        MirkoController
        VERSION 0.1
        LANGUAGES C CXX ASM
)

file(GLOB_RECURSE SRC
        Core/*.c
        Core/*.s
        Core/*.cpp
        Drivers/*.c
        Drivers/*.cpp
        Drivers/*.s
)

add_executable(MirkoController ${SRC})
set_target_properties(MirkoController PROPERTIES OUTPUT_NAME "MirkoController" SUFFIX ".elf")

target_include_directories(MirkoController PRIVATE
        Core/Inc
        Drivers/CMSIS/Device/ST/STM32F0xx/Include
        Drivers/CMSIS/Include
        Drivers/STM32F4xx_HAL_Driver/Inc
        Drivers/STM32F4xx_HAL_Driver/Inc/Legacy
)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)
set(CMAKE_SYSTEM_VERSION 1)

target_compile_definitions(MirkoController PRIVATE USE_HAL_DRIVER STM32F413xx)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_MAKE_PROGRAM makefile )
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CORE_FLAGS "-T${CMAKE_CURRENT_LIST_DIR}/STM32F413RGTX_FLASH.ld -mthumb -fexceptions -mcpu=cortex-m4 -mlittle-endian -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb-interwork --specs=nano.specs --specs=nosys.specs")

set(CMAKE_C_FLAGS "${CORE_FLAGS} -fno-builtin -Wall -std=gnu99 -fdata-sections -ffunction-sections -g3 -gdwarf-2" CACHE INTERNAL "c compiler flags")

set(CMAKE_CXX_FLAGS "${CORE_FLAGS} -fno-rtti -fno-builtin -Wall -std=gnu++17 -fdata-sections -ffunction-sections -g -ggdb3" CACHE INTERNAL "cxx compiler flags")

set(CMAKE_ASM_FLAGS "${CORE_FLAGS} -g -ggdb3 -D__USES_CXX" CACHE INTERNAL "asm compiler flags")