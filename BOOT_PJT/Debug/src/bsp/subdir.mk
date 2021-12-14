################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/bsp/bsp.c \
../src/bsp/stm32f4xx_hal_msp.c \
../src/bsp/stm32f4xx_it.c \
../src/bsp/syscalls.c \
../src/bsp/sysmem.c \
../src/bsp/system_stm32f4xx.c 

OBJS += \
./src/bsp/bsp.o \
./src/bsp/stm32f4xx_hal_msp.o \
./src/bsp/stm32f4xx_it.o \
./src/bsp/syscalls.o \
./src/bsp/sysmem.o \
./src/bsp/system_stm32f4xx.o 

C_DEPS += \
./src/bsp/bsp.d \
./src/bsp/stm32f4xx_hal_msp.d \
./src/bsp/stm32f4xx_it.d \
./src/bsp/syscalls.d \
./src/bsp/sysmem.d \
./src/bsp/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/bsp.o: ../src/bsp/bsp.c src/bsp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F411xE -c -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/common/core" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/ap" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/bsp" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/common" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib/cube_f411/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib/cube_f411/Drivers/CMSIS/Include" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib/cube_f411/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/common/hw/include" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver/usb/core" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver/usb/usb_cdc" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver/usb" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/bsp/bsp.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/bsp/stm32f4xx_hal_msp.o: ../src/bsp/stm32f4xx_hal_msp.c src/bsp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F411xE -c -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/common/core" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/ap" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/bsp" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/common" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib/cube_f411/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib/cube_f411/Drivers/CMSIS/Include" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib/cube_f411/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/common/hw/include" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver/usb/core" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver/usb/usb_cdc" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver/usb" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/bsp/stm32f4xx_hal_msp.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/bsp/stm32f4xx_it.o: ../src/bsp/stm32f4xx_it.c src/bsp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F411xE -c -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/common/core" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/ap" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/bsp" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/common" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib/cube_f411/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib/cube_f411/Drivers/CMSIS/Include" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib/cube_f411/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/common/hw/include" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver/usb/core" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver/usb/usb_cdc" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver/usb" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/bsp/stm32f4xx_it.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/bsp/syscalls.o: ../src/bsp/syscalls.c src/bsp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F411xE -c -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/common/core" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/ap" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/bsp" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/common" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib/cube_f411/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib/cube_f411/Drivers/CMSIS/Include" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib/cube_f411/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/common/hw/include" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver/usb/core" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver/usb/usb_cdc" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver/usb" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/bsp/syscalls.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/bsp/sysmem.o: ../src/bsp/sysmem.c src/bsp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F411xE -c -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/common/core" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/ap" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/bsp" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/common" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib/cube_f411/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib/cube_f411/Drivers/CMSIS/Include" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib/cube_f411/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/common/hw/include" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver/usb/core" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver/usb/usb_cdc" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver/usb" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/bsp/sysmem.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/bsp/system_stm32f4xx.o: ../src/bsp/system_stm32f4xx.c src/bsp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F411xE -c -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/common/core" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/ap" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/bsp" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/common" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib/cube_f411/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib/cube_f411/Drivers/CMSIS/Include" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib/cube_f411/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/common/hw/include" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver/usb/core" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver/usb/usb_cdc" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver/usb" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/bsp/system_stm32f4xx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

