<<<<<<< HEAD
# CMSIS Build CMakeLists generated on 2024-08-21T15:42:32

cmake_minimum_required(VERSION 3.22)

# Target options

set(TARGET rtos_t1)
set(CPU Cortex-M3)
set(PRJ_DIR "e:/AA_study_resource/Cube_MX/rtos_t1/MDK-ARM")
set(OUT_DIR "E:/AA_study_resource/Cube_MX/rtos_t1/MDK-ARM/out/rtos_t1/rtost1")
set(INT_DIR "E:/AA_study_resource/Cube_MX/rtos_t1/MDK-ARM/tmp/rtos_t1/rtost1")
set(FPU NO_FPU)
set(BYTE_ORDER Little-endian)
set(OPTIMIZE debug)
set(DEBUG on)
set(AS_FLAGS_GLOBAL "-masm=auto")
set(CC_FLAGS_GLOBAL "-std=c99 -fno-rtti -funsigned-char -fshort-enums -fshort-wchar -ffunction-sections -Wno-packed -Wno-missing-variable-declarations -Wno-missing-prototypes -Wno-missing-noreturn -Wno-sign-conversion -Wno-nonportable-include-path -Wno-reserved-id-macro -Wno-unused-macros -Wno-documentation-unknown-command -Wno-documentation -Wno-license-management -Wno-parentheses-equality")
set(CXX_FLAGS_GLOBAL "-xc++ -std=c++11 -fno-rtti -funsigned-char -fshort-enums -fshort-wchar -ffunction-sections -Wno-packed -Wno-missing-variable-declarations -Wno-missing-prototypes -Wno-missing-noreturn -Wno-sign-conversion -Wno-nonportable-include-path -Wno-reserved-id-macro -Wno-unused-macros -Wno-documentation-unknown-command -Wno-documentation -Wno-license-management -Wno-parentheses-equality")
set(LD_FLAGS_GLOBAL "--map --load_addr_map_info --xref --callgraph --symbols --info sizes --info totals --info unused --info veneers --strict --summary_stderr --info summarysizes")
set(LD_SCRIPT "e:/AA_study_resource/Cube_MX/rtos_t1/MDK-ARM/rtos_t1_rtost1.sct")

set(DEFINES
  STM32F10X_MD
  _RTE_
  USE_HAL_DRIVER
  STM32F103xB
)

set(INC_PATHS
  "e:/AA_study_resource/Cube_MX/rtos_t1/Core/Inc"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Drivers/STM32F1xx_HAL_Driver/Inc"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Middlewares/Third_Party/FreeRTOS/Source/include"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Middlewares/Third_Party/FreeRTOS/Source/portable/RVDS/ARM_CM3"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Drivers/CMSIS/Device/ST/STM32F1xx/Include"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Drivers/CMSIS/Include"
  "e:/AA_study_resource/Cube_MX/rtos_t1/MDK-ARM/RTE/_rtost1"
  "C:/Users/18160/AppData/Local/arm/packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include"
  "C:/Users/18160/AppData/Local/arm/packs/Keil/STM32F1xx_DFP/2.4.1/Device/Include"
)

set(AS_ARM_SRC_FILES
  "e:/AA_study_resource/Cube_MX/rtos_t1/MDK-ARM/startup_stm32f103xb.s"
)

set(CC_SRC_FILES
  "e:/AA_study_resource/Cube_MX/rtos_t1/Core/Src/freertos.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Core/Src/gpio.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Core/Src/main.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Core/Src/stm32f1xx_hal_msp.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Core/Src/stm32f1xx_it.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Core/Src/system_stm32f1xx.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Core/Src/usart.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_exti.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Middlewares/Third_Party/FreeRTOS/Source/croutine.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Middlewares/Third_Party/FreeRTOS/Source/event_groups.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Middlewares/Third_Party/FreeRTOS/Source/list.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Middlewares/Third_Party/FreeRTOS/Source/portable/RVDS/ARM_CM3/port.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Middlewares/Third_Party/FreeRTOS/Source/queue.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Middlewares/Third_Party/FreeRTOS/Source/tasks.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Middlewares/Third_Party/FreeRTOS/Source/timers.c"
)

# Toolchain config map

set(REGISTERED_TOOLCHAIN_ROOT "c:/Users/18160/.vcpkg/artifacts/2139c4c6/compilers.arm.armclang/6.22.0/bin")
set(REGISTERED_TOOLCHAIN_VERSION "6.22.0")
set(TOOLCHAIN_VERSION_MIN "6.22.0")
include ("C:/Users/18160/.vcpkg/artifacts/2139c4c6/tools.open.cmsis.pack.cmsis.toolbox/2.4.0/etc/AC6.6.16.2.cmake")
include ("C:/Users/18160/.vcpkg/artifacts/2139c4c6/tools.open.cmsis.pack.cmsis.toolbox/2.4.0/etc/CMSIS-Build-Utils.cmake")

# Setup project

project(${TARGET} LANGUAGES AS_ARM C)

cbuild_get_running_toolchain(TOOLCHAIN_ROOT TOOLCHAIN_VERSION C)

# Global Flags

set(CMAKE_AS_ARM_FLAGS "${AS_ARM_CPU} ${AS_ARM_BYTE_ORDER} ${AS_ARM_DEFINES} ${AS_ARM_OPTIONS_FLAGS} ${AS_ARM_FLAGS} ${AS_FLAGS_GLOBAL}")
cbuild_get_system_includes(CC_SYS_INC_PATHS_LIST CC_SYS_INC_PATHS)
set(CMAKE_C_FLAGS "${CC_CPU} ${CC_BYTE_ORDER} ${CC_DEFINES} ${CC_OPTIONS_FLAGS} ${CC_FLAGS} ${CC_FLAGS_GLOBAL} ${CC_SYS_INC_PATHS}")
set(CMAKE_C_LINK_FLAGS "${LD_CPU} ${_LS}\"${LD_SCRIPT}\" ${LD_FLAGS_GLOBAL} ${LD_OPTIONS_FLAGS} ${LD_FLAGS}")

# Local Flags

foreach(SRC ${AS_ARM_SRC_FILES})
  set_source_files_properties(${SRC} PROPERTIES LANGUAGE AS_ARM)
endforeach()

# Compilation Database

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_custom_target(database COMMAND ${CMAKE_COMMAND} -E copy_if_different "${INT_DIR}/compile_commands.json" "${OUT_DIR}")

# Setup Target

add_executable(${TARGET} ${AS_ARM_SRC_FILES} ${CC_SRC_FILES})
set_target_properties(${TARGET} PROPERTIES PREFIX "" SUFFIX ".axf" OUTPUT_NAME "rtos_t1")
set_target_properties(${TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUT_DIR} LINK_DEPENDS ${LD_SCRIPT})
target_include_directories(${TARGET} PUBLIC ${INC_PATHS})
=======
# CMSIS Build CMakeLists generated on 2024-08-21T15:42:32

cmake_minimum_required(VERSION 3.22)

# Target options

set(TARGET rtos_t1)
set(CPU Cortex-M3)
set(PRJ_DIR "e:/AA_study_resource/Cube_MX/rtos_t1/MDK-ARM")
set(OUT_DIR "E:/AA_study_resource/Cube_MX/rtos_t1/MDK-ARM/out/rtos_t1/rtost1")
set(INT_DIR "E:/AA_study_resource/Cube_MX/rtos_t1/MDK-ARM/tmp/rtos_t1/rtost1")
set(FPU NO_FPU)
set(BYTE_ORDER Little-endian)
set(OPTIMIZE debug)
set(DEBUG on)
set(AS_FLAGS_GLOBAL "-masm=auto")
set(CC_FLAGS_GLOBAL "-std=c99 -fno-rtti -funsigned-char -fshort-enums -fshort-wchar -ffunction-sections -Wno-packed -Wno-missing-variable-declarations -Wno-missing-prototypes -Wno-missing-noreturn -Wno-sign-conversion -Wno-nonportable-include-path -Wno-reserved-id-macro -Wno-unused-macros -Wno-documentation-unknown-command -Wno-documentation -Wno-license-management -Wno-parentheses-equality")
set(CXX_FLAGS_GLOBAL "-xc++ -std=c++11 -fno-rtti -funsigned-char -fshort-enums -fshort-wchar -ffunction-sections -Wno-packed -Wno-missing-variable-declarations -Wno-missing-prototypes -Wno-missing-noreturn -Wno-sign-conversion -Wno-nonportable-include-path -Wno-reserved-id-macro -Wno-unused-macros -Wno-documentation-unknown-command -Wno-documentation -Wno-license-management -Wno-parentheses-equality")
set(LD_FLAGS_GLOBAL "--map --load_addr_map_info --xref --callgraph --symbols --info sizes --info totals --info unused --info veneers --strict --summary_stderr --info summarysizes")
set(LD_SCRIPT "e:/AA_study_resource/Cube_MX/rtos_t1/MDK-ARM/rtos_t1_rtost1.sct")

set(DEFINES
  STM32F10X_MD
  _RTE_
  USE_HAL_DRIVER
  STM32F103xB
)

set(INC_PATHS
  "e:/AA_study_resource/Cube_MX/rtos_t1/Core/Inc"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Drivers/STM32F1xx_HAL_Driver/Inc"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Middlewares/Third_Party/FreeRTOS/Source/include"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Middlewares/Third_Party/FreeRTOS/Source/portable/RVDS/ARM_CM3"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Drivers/CMSIS/Device/ST/STM32F1xx/Include"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Drivers/CMSIS/Include"
  "e:/AA_study_resource/Cube_MX/rtos_t1/MDK-ARM/RTE/_rtost1"
  "C:/Users/18160/AppData/Local/arm/packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include"
  "C:/Users/18160/AppData/Local/arm/packs/Keil/STM32F1xx_DFP/2.4.1/Device/Include"
)

set(AS_ARM_SRC_FILES
  "e:/AA_study_resource/Cube_MX/rtos_t1/MDK-ARM/startup_stm32f103xb.s"
)

set(CC_SRC_FILES
  "e:/AA_study_resource/Cube_MX/rtos_t1/Core/Src/freertos.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Core/Src/gpio.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Core/Src/main.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Core/Src/stm32f1xx_hal_msp.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Core/Src/stm32f1xx_it.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Core/Src/system_stm32f1xx.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Core/Src/usart.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_exti.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Middlewares/Third_Party/FreeRTOS/Source/croutine.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Middlewares/Third_Party/FreeRTOS/Source/event_groups.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Middlewares/Third_Party/FreeRTOS/Source/list.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Middlewares/Third_Party/FreeRTOS/Source/portable/RVDS/ARM_CM3/port.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Middlewares/Third_Party/FreeRTOS/Source/queue.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Middlewares/Third_Party/FreeRTOS/Source/tasks.c"
  "e:/AA_study_resource/Cube_MX/rtos_t1/Middlewares/Third_Party/FreeRTOS/Source/timers.c"
)

# Toolchain config map

set(REGISTERED_TOOLCHAIN_ROOT "c:/Users/18160/.vcpkg/artifacts/2139c4c6/compilers.arm.armclang/6.22.0/bin")
set(REGISTERED_TOOLCHAIN_VERSION "6.22.0")
set(TOOLCHAIN_VERSION_MIN "6.22.0")
include ("C:/Users/18160/.vcpkg/artifacts/2139c4c6/tools.open.cmsis.pack.cmsis.toolbox/2.4.0/etc/AC6.6.16.2.cmake")
include ("C:/Users/18160/.vcpkg/artifacts/2139c4c6/tools.open.cmsis.pack.cmsis.toolbox/2.4.0/etc/CMSIS-Build-Utils.cmake")

# Setup project

project(${TARGET} LANGUAGES AS_ARM C)

cbuild_get_running_toolchain(TOOLCHAIN_ROOT TOOLCHAIN_VERSION C)

# Global Flags

set(CMAKE_AS_ARM_FLAGS "${AS_ARM_CPU} ${AS_ARM_BYTE_ORDER} ${AS_ARM_DEFINES} ${AS_ARM_OPTIONS_FLAGS} ${AS_ARM_FLAGS} ${AS_FLAGS_GLOBAL}")
cbuild_get_system_includes(CC_SYS_INC_PATHS_LIST CC_SYS_INC_PATHS)
set(CMAKE_C_FLAGS "${CC_CPU} ${CC_BYTE_ORDER} ${CC_DEFINES} ${CC_OPTIONS_FLAGS} ${CC_FLAGS} ${CC_FLAGS_GLOBAL} ${CC_SYS_INC_PATHS}")
set(CMAKE_C_LINK_FLAGS "${LD_CPU} ${_LS}\"${LD_SCRIPT}\" ${LD_FLAGS_GLOBAL} ${LD_OPTIONS_FLAGS} ${LD_FLAGS}")

# Local Flags

foreach(SRC ${AS_ARM_SRC_FILES})
  set_source_files_properties(${SRC} PROPERTIES LANGUAGE AS_ARM)
endforeach()

# Compilation Database

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_custom_target(database COMMAND ${CMAKE_COMMAND} -E copy_if_different "${INT_DIR}/compile_commands.json" "${OUT_DIR}")

# Setup Target

add_executable(${TARGET} ${AS_ARM_SRC_FILES} ${CC_SRC_FILES})
set_target_properties(${TARGET} PROPERTIES PREFIX "" SUFFIX ".axf" OUTPUT_NAME "rtos_t1")
set_target_properties(${TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUT_DIR} LINK_DEPENDS ${LD_SCRIPT})
target_include_directories(${TARGET} PUBLIC ${INC_PATHS})
>>>>>>> 00ac74e (9.6)
