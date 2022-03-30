################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../ADC.c \
../A_COMP.c \
../eep_ext.c \
../I2C.c \
../INT_EXT.c \
../IO_PORTs.c \
../LCD_4BIT.c \
../LCD_I2C.c \
../LEDs.c \
../main.c \
../RTC.c \
../RTC_1302.c \
../RTC_LCD.c \
../Servo.c \
../Sleep.c \
../Timers.c \
../USART.c \
../WDT.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
ADC.o \
A_COMP.o \
eep_ext.o \
I2C.o \
INT_EXT.o \
IO_PORTs.o \
LCD_4BIT.o \
LCD_I2C.o \
LEDs.o \
main.o \
RTC.o \
RTC_1302.o \
RTC_LCD.o \
Servo.o \
Sleep.o \
Timers.o \
USART.o \
WDT.o

OBJS_AS_ARGS +=  \
ADC.o \
A_COMP.o \
eep_ext.o \
I2C.o \
INT_EXT.o \
IO_PORTs.o \
LCD_4BIT.o \
LCD_I2C.o \
LEDs.o \
main.o \
RTC.o \
RTC_1302.o \
RTC_LCD.o \
Servo.o \
Sleep.o \
Timers.o \
USART.o \
WDT.o

C_DEPS +=  \
ADC.d \
A_COMP.d \
eep_ext.d \
I2C.d \
INT_EXT.d \
IO_PORTs.d \
LCD_4BIT.d \
LCD_I2C.d \
LEDs.d \
main.d \
RTC.d \
RTC_1302.d \
RTC_LCD.d \
Servo.d \
Sleep.d \
Timers.d \
USART.d \
WDT.d

C_DEPS_AS_ARGS +=  \
ADC.d \
A_COMP.d \
eep_ext.d \
I2C.d \
INT_EXT.d \
IO_PORTs.d \
LCD_4BIT.d \
LCD_I2C.d \
LEDs.d \
main.d \
RTC.d \
RTC_1302.d \
RTC_LCD.d \
Servo.d \
Sleep.d \
Timers.d \
USART.d \
WDT.d

OUTPUT_FILE_PATH +=SDK_Atmega8.elf

OUTPUT_FILE_PATH_AS_ARGS +=SDK_Atmega8.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler





































./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG -DF_CPU=16000000  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.0.90\include"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega8 -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.0.90\gcc\dev\atmega8" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="SDK_Atmega8.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mmcu=atmega8 -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.0.90\gcc\dev\atmega8"  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "SDK_Atmega8.elf" "SDK_Atmega8.hex"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "SDK_Atmega8.elf" "SDK_Atmega8.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "SDK_Atmega8.elf" > "SDK_Atmega8.lss"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "SDK_Atmega8.elf" "SDK_Atmega8.srec"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-size.exe" "SDK_Atmega8.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "SDK_Atmega8.elf" "SDK_Atmega8.a" "SDK_Atmega8.hex" "SDK_Atmega8.lss" "SDK_Atmega8.eep" "SDK_Atmega8.map" "SDK_Atmega8.srec" "SDK_Atmega8.usersignatures"
	