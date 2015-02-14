################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../dijkstra.cpp \
../exporter.cpp \
../generateCourses.cpp \
../generateFaculty.cpp \
../generateStudent.cpp \
../generatefriends.cpp \
../main.cpp \
../parser.cpp \
../priority_queue.cpp \
../question.cpp \
../sherlock.cpp \
../timekeeper.cpp 

OBJS += \
./dijkstra.o \
./exporter.o \
./generateCourses.o \
./generateFaculty.o \
./generateStudent.o \
./generatefriends.o \
./main.o \
./parser.o \
./priority_queue.o \
./question.o \
./sherlock.o \
./timekeeper.o 

CPP_DEPS += \
./dijkstra.d \
./exporter.d \
./generateCourses.d \
./generateFaculty.d \
./generateStudent.d \
./generatefriends.d \
./main.d \
./parser.d \
./priority_queue.d \
./question.d \
./sherlock.d \
./timekeeper.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


