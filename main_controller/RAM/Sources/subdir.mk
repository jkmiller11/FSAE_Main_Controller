################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/ADC.c" \
"../Sources/CAN.c" \
"../Sources/Exceptions.c" \
"../Sources/IntcInterrupts.c" \
"../Sources/ivor_branch_table.c" \
"../Sources/main.c" \
"../Sources/sys_init.c" \

C_SRCS += \
../Sources/ADC.c \
../Sources/CAN.c \
../Sources/Exceptions.c \
../Sources/IntcInterrupts.c \
../Sources/ivor_branch_table.c \
../Sources/main.c \
../Sources/sys_init.c \

OBJS += \
./Sources/ADC_c.obj \
./Sources/CAN_c.obj \
./Sources/Exceptions_c.obj \
./Sources/IntcInterrupts_c.obj \
./Sources/ivor_branch_table_c.obj \
./Sources/main_c.obj \
./Sources/sys_init_c.obj \

OBJS_QUOTED += \
"./Sources/ADC_c.obj" \
"./Sources/CAN_c.obj" \
"./Sources/Exceptions_c.obj" \
"./Sources/IntcInterrupts_c.obj" \
"./Sources/ivor_branch_table_c.obj" \
"./Sources/main_c.obj" \
"./Sources/sys_init_c.obj" \

C_DEPS += \
./Sources/ADC_c.d \
./Sources/CAN_c.d \
./Sources/Exceptions_c.d \
./Sources/IntcInterrupts_c.d \
./Sources/ivor_branch_table_c.d \
./Sources/main_c.d \
./Sources/sys_init_c.d \

OBJS_OS_FORMAT += \
./Sources/ADC_c.obj \
./Sources/CAN_c.obj \
./Sources/Exceptions_c.obj \
./Sources/IntcInterrupts_c.obj \
./Sources/ivor_branch_table_c.obj \
./Sources/main_c.obj \
./Sources/sys_init_c.obj \

C_DEPS_QUOTED += \
"./Sources/ADC_c.d" \
"./Sources/CAN_c.d" \
"./Sources/Exceptions_c.d" \
"./Sources/IntcInterrupts_c.d" \
"./Sources/ivor_branch_table_c.d" \
"./Sources/main_c.d" \
"./Sources/sys_init_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/ADC_c.obj: ../Sources/ADC.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/ADC.args" -o "Sources/ADC_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/CAN_c.obj: ../Sources/CAN.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/CAN.args" -o "Sources/CAN_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/Exceptions_c.obj: ../Sources/Exceptions.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/Exceptions.args" -o "Sources/Exceptions_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/IntcInterrupts_c.obj: ../Sources/IntcInterrupts.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/IntcInterrupts.args" -o "Sources/IntcInterrupts_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/ivor_branch_table_c.obj: ../Sources/ivor_branch_table.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/ivor_branch_table.args" -o "Sources/ivor_branch_table_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/main_c.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/main.args" -o "Sources/main_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/sys_init_c.obj: ../Sources/sys_init.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/sys_init.args" -o "Sources/sys_init_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


