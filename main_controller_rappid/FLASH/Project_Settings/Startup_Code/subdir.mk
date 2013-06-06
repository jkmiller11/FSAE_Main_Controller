################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Project_Settings/Startup_Code/MPC5604B_Startup.c" \

C_SRCS += \
../Project_Settings/Startup_Code/MPC5604B_Startup.c \

S_SRCS += \
../Project_Settings/Startup_Code/crt0.s \

S_SRCS_QUOTED += \
"../Project_Settings/Startup_Code/crt0.s" \

S_DEPS_QUOTED += \
"./Project_Settings/Startup_Code/crt0_s.d" \

OBJS += \
./Project_Settings/Startup_Code/MPC5604B_Startup_c.obj \
./Project_Settings/Startup_Code/crt0_s.obj \

S_DEPS += \
./Project_Settings/Startup_Code/crt0_s.d \

OBJS_QUOTED += \
"./Project_Settings/Startup_Code/MPC5604B_Startup_c.obj" \
"./Project_Settings/Startup_Code/crt0_s.obj" \

C_DEPS += \
./Project_Settings/Startup_Code/MPC5604B_Startup_c.d \

OBJS_OS_FORMAT += \
./Project_Settings/Startup_Code/MPC5604B_Startup_c.obj \
./Project_Settings/Startup_Code/crt0_s.obj \

C_DEPS_QUOTED += \
"./Project_Settings/Startup_Code/MPC5604B_Startup_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Project_Settings/Startup_Code/MPC5604B_Startup_c.obj: ../Project_Settings/Startup_Code/MPC5604B_Startup.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Project_Settings/Startup_Code/MPC5604B_Startup.args" -o "Project_Settings/Startup_Code/MPC5604B_Startup_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Project_Settings/Startup_Code/%.d: ../Project_Settings/Startup_Code/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Project_Settings/Startup_Code/crt0_s.obj: ../Project_Settings/Startup_Code/crt0.s
	@echo 'Building file: $<'
	@echo 'Executing target #17 $<'
	@echo 'Invoking: PowerPC Assembler'
	"$(PAToolsDirEnv)/mwasmeppc" @@"Project_Settings/Startup_Code/crt0.args" -o "Project_Settings/Startup_Code/crt0_s.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Project_Settings/Startup_Code/%.d: ../Project_Settings/Startup_Code/%.s
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


