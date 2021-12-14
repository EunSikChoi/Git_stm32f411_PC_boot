################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/hw/driver/usb/usb_cdc/usb_device.c \
../src/hw/driver/usb/usb_cdc/usbd_cdc.c \
../src/hw/driver/usb/usb_cdc/usbd_cdc_if.c \
../src/hw/driver/usb/usb_cdc/usbd_desc.c 

OBJS += \
./src/hw/driver/usb/usb_cdc/usb_device.o \
./src/hw/driver/usb/usb_cdc/usbd_cdc.o \
./src/hw/driver/usb/usb_cdc/usbd_cdc_if.o \
./src/hw/driver/usb/usb_cdc/usbd_desc.o 

C_DEPS += \
./src/hw/driver/usb/usb_cdc/usb_device.d \
./src/hw/driver/usb/usb_cdc/usbd_cdc.d \
./src/hw/driver/usb/usb_cdc/usbd_cdc_if.d \
./src/hw/driver/usb/usb_cdc/usbd_desc.d 


# Each subdirectory must supply rules for building sources it contributes
src/hw/driver/usb/usb_cdc/usb_device.o: ../src/hw/driver/usb/usb_cdc/usb_device.c src/hw/driver/usb/usb_cdc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F411xE -c -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/common/core" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/ap" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/bsp" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/common" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib/cube_f411/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib/cube_f411/Drivers/CMSIS/Include" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib/cube_f411/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/common/hw/include" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver/usb/core" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver/usb/usb_cdc" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver/usb" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/hw/driver/usb/usb_cdc/usb_device.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/hw/driver/usb/usb_cdc/usbd_cdc.o: ../src/hw/driver/usb/usb_cdc/usbd_cdc.c src/hw/driver/usb/usb_cdc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F411xE -c -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/common/core" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/ap" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/bsp" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/common" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib/cube_f411/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib/cube_f411/Drivers/CMSIS/Include" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib/cube_f411/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/common/hw/include" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver/usb/core" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver/usb/usb_cdc" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver/usb" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/hw/driver/usb/usb_cdc/usbd_cdc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/hw/driver/usb/usb_cdc/usbd_cdc_if.o: ../src/hw/driver/usb/usb_cdc/usbd_cdc_if.c src/hw/driver/usb/usb_cdc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F411xE -c -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/common/core" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/ap" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/bsp" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/common" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib/cube_f411/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib/cube_f411/Drivers/CMSIS/Include" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib/cube_f411/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/common/hw/include" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver/usb/core" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver/usb/usb_cdc" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver/usb" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/hw/driver/usb/usb_cdc/usbd_cdc_if.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/hw/driver/usb/usb_cdc/usbd_desc.o: ../src/hw/driver/usb/usb_cdc/usbd_desc.c src/hw/driver/usb/usb_cdc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F411xE -c -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/common/core" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/ap" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/bsp" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/common" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib/cube_f411/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib/cube_f411/Drivers/CMSIS/Include" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/lib/cube_f411/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/common/hw/include" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver/usb/core" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver/usb/usb_cdc" -I"D:/git/Git_stm32f411_PC_boot/BOOT_PJT/src/hw/driver/usb" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/hw/driver/usb/usb_cdc/usbd_desc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

