################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1280/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/NickRethans/Desktop/EmbeddedSystems/Homework3/uartecho_MSP_EXP432E401Y_tirtos_ccs" --include_path="C:/Users/NickRethans/Desktop/EmbeddedSystems/Homework3/uartecho_MSP_EXP432E401Y_tirtos_ccs/Debug" --include_path="C:/ti/simplelink_msp432e4_sdk_4_20_00_12/source" --include_path="C:/ti/simplelink_msp432e4_sdk_4_20_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/simplelink_msp432e4_sdk_4_20_00_12/source/ti/posix/ccs" --include_path="C:/ti/ccs1280/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --advice:power=none -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Users/NickRethans/Desktop/EmbeddedSystems/Homework3/uartecho_MSP_EXP432E401Y_tirtos_ccs/Debug/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-762256271: ../uartecho.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/ccs1280/ccs/utils/sysconfig_1.21.0/sysconfig_cli.bat" --script "C:/Users/NickRethans/Desktop/EmbeddedSystems/Homework3/uartecho_MSP_EXP432E401Y_tirtos_ccs/uartecho.syscfg" -o "syscfg" -s "C:/ti/simplelink_msp432e4_sdk_4_20_00_12/.metadata/product.json" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/ti_drivers_config.c: build-762256271 ../uartecho.syscfg
syscfg/ti_drivers_config.h: build-762256271
syscfg/ti_utils_build_linker.cmd.exp: build-762256271
syscfg/syscfg_c.rov.xs: build-762256271
syscfg: build-762256271

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1280/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/NickRethans/Desktop/EmbeddedSystems/Homework3/uartecho_MSP_EXP432E401Y_tirtos_ccs" --include_path="C:/Users/NickRethans/Desktop/EmbeddedSystems/Homework3/uartecho_MSP_EXP432E401Y_tirtos_ccs/Debug" --include_path="C:/ti/simplelink_msp432e4_sdk_4_20_00_12/source" --include_path="C:/ti/simplelink_msp432e4_sdk_4_20_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/simplelink_msp432e4_sdk_4_20_00_12/source/ti/posix/ccs" --include_path="C:/ti/ccs1280/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --advice:power=none -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="C:/Users/NickRethans/Desktop/EmbeddedSystems/Homework3/uartecho_MSP_EXP432E401Y_tirtos_ccs/Debug/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


