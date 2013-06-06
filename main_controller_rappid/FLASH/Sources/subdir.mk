################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/adc_init.c" \
"../Sources/adc_trigger_init.c" \
"../Sources/dspi_init.c" \
"../Sources/dspi_var.c" \
"../Sources/flash_init.c" \
"../Sources/flexcan_init.c" \
"../Sources/main.c" \
"../Sources/msr_init.c" \
"../Sources/pcu_init.c" \
"../Sources/rchw_init.c" \
"../Sources/rgm_init.c" \
"../Sources/romcopy.c" \
"../Sources/siu_init.c" \
"../Sources/sys_init.c" \
"../Sources/sysclk_init.c" \

C_SRCS += \
../Sources/adc_init.c \
../Sources/adc_trigger_init.c \
../Sources/dspi_init.c \
../Sources/dspi_var.c \
../Sources/flash_init.c \
../Sources/flexcan_init.c \
../Sources/main.c \
../Sources/msr_init.c \
../Sources/pcu_init.c \
../Sources/rchw_init.c \
../Sources/rgm_init.c \
../Sources/romcopy.c \
../Sources/siu_init.c \
../Sources/sys_init.c \
../Sources/sysclk_init.c \

OBJS += \
./Sources/adc_init_c.obj \
./Sources/adc_trigger_init_c.obj \
./Sources/dspi_init_c.obj \
./Sources/dspi_var_c.obj \
./Sources/flash_init_c.obj \
./Sources/flexcan_init_c.obj \
./Sources/main_c.obj \
./Sources/msr_init_c.obj \
./Sources/pcu_init_c.obj \
./Sources/rchw_init_c.obj \
./Sources/rgm_init_c.obj \
./Sources/romcopy_c.obj \
./Sources/siu_init_c.obj \
./Sources/sys_init_c.obj \
./Sources/sysclk_init_c.obj \

OBJS_QUOTED += \
"./Sources/adc_init_c.obj" \
"./Sources/adc_trigger_init_c.obj" \
"./Sources/dspi_init_c.obj" \
"./Sources/dspi_var_c.obj" \
"./Sources/flash_init_c.obj" \
"./Sources/flexcan_init_c.obj" \
"./Sources/main_c.obj" \
"./Sources/msr_init_c.obj" \
"./Sources/pcu_init_c.obj" \
"./Sources/rchw_init_c.obj" \
"./Sources/rgm_init_c.obj" \
"./Sources/romcopy_c.obj" \
"./Sources/siu_init_c.obj" \
"./Sources/sys_init_c.obj" \
"./Sources/sysclk_init_c.obj" \

C_DEPS += \
./Sources/adc_init_c.d \
./Sources/adc_trigger_init_c.d \
./Sources/dspi_init_c.d \
./Sources/dspi_var_c.d \
./Sources/flash_init_c.d \
./Sources/flexcan_init_c.d \
./Sources/main_c.d \
./Sources/msr_init_c.d \
./Sources/pcu_init_c.d \
./Sources/rchw_init_c.d \
./Sources/rgm_init_c.d \
./Sources/romcopy_c.d \
./Sources/siu_init_c.d \
./Sources/sys_init_c.d \
./Sources/sysclk_init_c.d \

OBJS_OS_FORMAT += \
./Sources/adc_init_c.obj \
./Sources/adc_trigger_init_c.obj \
./Sources/dspi_init_c.obj \
./Sources/dspi_var_c.obj \
./Sources/flash_init_c.obj \
./Sources/flexcan_init_c.obj \
./Sources/main_c.obj \
./Sources/msr_init_c.obj \
./Sources/pcu_init_c.obj \
./Sources/rchw_init_c.obj \
./Sources/rgm_init_c.obj \
./Sources/romcopy_c.obj \
./Sources/siu_init_c.obj \
./Sources/sys_init_c.obj \
./Sources/sysclk_init_c.obj \

C_DEPS_QUOTED += \
"./Sources/adc_init_c.d" \
"./Sources/adc_trigger_init_c.d" \
"./Sources/dspi_init_c.d" \
"./Sources/dspi_var_c.d" \
"./Sources/flash_init_c.d" \
"./Sources/flexcan_init_c.d" \
"./Sources/main_c.d" \
"./Sources/msr_init_c.d" \
"./Sources/pcu_init_c.d" \
"./Sources/rchw_init_c.d" \
"./Sources/rgm_init_c.d" \
"./Sources/romcopy_c.d" \
"./Sources/siu_init_c.d" \
"./Sources/sys_init_c.d" \
"./Sources/sysclk_init_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/adc_init_c.obj: ../Sources/adc_init.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/adc_init.args" -o "Sources/adc_init_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/adc_trigger_init_c.obj: ../Sources/adc_trigger_init.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/adc_trigger_init.args" -o "Sources/adc_trigger_init_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/dspi_init_c.obj: ../Sources/dspi_init.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/dspi_init.args" -o "Sources/dspi_init_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/dspi_var_c.obj: ../Sources/dspi_var.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/dspi_var.args" -o "Sources/dspi_var_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/flash_init_c.obj: ../Sources/flash_init.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/flash_init.args" -o "Sources/flash_init_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/flexcan_init_c.obj: ../Sources/flexcan_init.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/flexcan_init.args" -o "Sources/flexcan_init_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/main_c.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/main.args" -o "Sources/main_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/msr_init_c.obj: ../Sources/msr_init.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/msr_init.args" -o "Sources/msr_init_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/pcu_init_c.obj: ../Sources/pcu_init.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/pcu_init.args" -o "Sources/pcu_init_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/rchw_init_c.obj: ../Sources/rchw_init.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/rchw_init.args" -o "Sources/rchw_init_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/rgm_init_c.obj: ../Sources/rgm_init.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/rgm_init.args" -o "Sources/rgm_init_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/romcopy_c.obj: ../Sources/romcopy.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/romcopy.args" -o "Sources/romcopy_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/siu_init_c.obj: ../Sources/siu_init.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/siu_init.args" -o "Sources/siu_init_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/sys_init_c.obj: ../Sources/sys_init.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/sys_init.args" -o "Sources/sys_init_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/sysclk_init_c.obj: ../Sources/sysclk_init.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/sysclk_init.args" -o "Sources/sysclk_init_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


