################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../FileMerge.cpp \
../FilterNgram.cpp \
../Generalize.cpp \
../Ngram.cpp \
../NkiFile.cpp \
../StringOp.cpp \
../TrainingNGram.cpp \
../WordNGram.cpp \
../main_to3tuple.cpp \
../separateJudger.cpp 

OBJS += \
./FileMerge.o \
./FilterNgram.o \
./Generalize.o \
./Ngram.o \
./NkiFile.o \
./StringOp.o \
./TrainingNGram.o \
./WordNGram.o \
./main_to3tuple.o \
./separateJudger.o 

CPP_DEPS += \
./FileMerge.d \
./FilterNgram.d \
./Generalize.d \
./Ngram.d \
./NkiFile.d \
./StringOp.d \
./TrainingNGram.d \
./WordNGram.d \
./main_to3tuple.d \
./separateJudger.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


