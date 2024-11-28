################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../MSP_EXP432E401Y_TIRTOS.cmd 

SYSCFG_SRCS += \
../udpecho.syscfg 

C_SRCS += \
../main_tirtos.c \
../udpEcho.c \
../udpEchoHooks.c \
./syscfg/ti_net_config.c \
./syscfg/ti_ndk_config.c \
./syscfg/ti_drivers_config.c 

GEN_FILES += \
./syscfg/ti_net_config.c \
./syscfg/ti_ndk_config.c \
./syscfg/ti_drivers_config.c 

GEN_MISC_DIRS += \
./syscfg 

C_DEPS += \
./main_tirtos.d \
./udpEcho.d \
./udpEchoHooks.d \
./syscfg/ti_net_config.d \
./syscfg/ti_ndk_config.d \
./syscfg/ti_drivers_config.d 

OBJS += \
./main_tirtos.obj \
./udpEcho.obj \
./udpEchoHooks.obj \
./syscfg/ti_net_config.obj \
./syscfg/ti_ndk_config.obj \
./syscfg/ti_drivers_config.obj 

GEN_MISC_FILES += \
./syscfg/ti_drivers_config.h \
./syscfg/ti_utils_build_linker.cmd.exp \
./syscfg/syscfg_c.rov.xs 

GEN_MISC_DIRS__QUOTED += \
"syscfg" 

OBJS__QUOTED += \
"main_tirtos.obj" \
"udpEcho.obj" \
"udpEchoHooks.obj" \
"syscfg\ti_net_config.obj" \
"syscfg\ti_ndk_config.obj" \
"syscfg\ti_drivers_config.obj" 

GEN_MISC_FILES__QUOTED += \
"syscfg\ti_drivers_config.h" \
"syscfg\ti_utils_build_linker.cmd.exp" \
"syscfg\syscfg_c.rov.xs" 

C_DEPS__QUOTED += \
"main_tirtos.d" \
"udpEcho.d" \
"udpEchoHooks.d" \
"syscfg\ti_net_config.d" \
"syscfg\ti_ndk_config.d" \
"syscfg\ti_drivers_config.d" 

GEN_FILES__QUOTED += \
"syscfg\ti_net_config.c" \
"syscfg\ti_ndk_config.c" \
"syscfg\ti_drivers_config.c" 

C_SRCS__QUOTED += \
"../main_tirtos.c" \
"../udpEcho.c" \
"../udpEchoHooks.c" \
"./syscfg/ti_net_config.c" \
"./syscfg/ti_ndk_config.c" \
"./syscfg/ti_drivers_config.c" 

SYSCFG_SRCS__QUOTED += \
"../udpecho.syscfg" 


