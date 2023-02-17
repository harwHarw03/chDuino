TARGET_EXEC := ./build/chibiTest

#	DIRS : 
BUILD_DIR := ./build
CHIBIOS_DIR := ./chDuino/ChRt
ARDUINO_CORES := ./chDuino/arduino/hardware/arduino/avr/cores/arduino
ARDUINO_VARIANTS := ./chDuino/arduino/hardware/arduino/avr/variants

SERVO_LIB := ./chDuino/arduino/libraries/Servo/src
SOFTWARESERIAL_LIB := ./chDuino/arduino/libraries/SoftwareSerial

#	find C and C++ files
SRCS := $(shell find $(CHIBIOS_DIR) -name '*.cpp' -or -name '*.c' -or -name '*.s')	\
		$(shell find $(ARDUINO_CORES) -name '*.cpp' -or -name '*.c' -or -name '*.s')	\
		$(shell find $(SERVO_LIB) -name '*.cpp' -or -name '*.c' -or -name '*.s')	\
		$(shell find $(SOFTWARESERIAL_LIB) -name '*.cpp' -or -name '*.c' -or -name '*.s')	\
		./main.cpp
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

#	find header files
INC_DIRS := $(shell find $(CHIBIOS_DIR) -type d)	\
			$(shell find $(ARDUINO_CORES) -type d)	\
			$(shell find $(ARDUINO_VARIANTS) -type d)	\
			$(shell find $(SERVO_LIB) -type d)	\
			$(shell find $(SOFTWARESERIAL_LIB) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# The -MMD and -MP flags together generate Makefiles for us!
# These files will have .d instead of .o as the output.
ASSFLAGS := -c -g -x assembler-with-cpp -flto -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10819 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR ${INC_FLAGS}
CFLAGS_FINAL := -Wall -Wextra -Os -g -flto -fuse-linker-plugin -Wl,--gc-sections -mmcu=atmega328p ${INC_FLAGS}
CFLAGS := -c -g -Os -Wall -Wextra -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10819 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR -MMD -MP ${INC_FLAGS}
CPPFLAGS := -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10819 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR -MMD -MP ${INC_FLAGS}

#	compiler options
CC := avr-gcc
CC_AR := avr-gcc-ar
CPP := avr-g++

#	flash
MCU := atmega328p
PROGRAMMER := arduino
PORT := /dev/ttyACM0
AVRDUDE_FLAGS := -p $(MCU) -c $(PROGRAMMER) -P $(PORT)
AVRDUDE := avrdude -v $(AVRDUDE_FLAGS)

#	final build
avr: $(OBJS)
	rm -f core.a
	$(CC_AR) rcs $(BUILD_DIR)/core.a $<
	$(CC) $(CFLAGS_FINAL) -o $(TARGET_EXEC).elf $(OBJS) $(BUILD_DIR)/core.a $(LDFLAGS)
	avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 $(TARGET_EXEC).elf $(TARGET_EXEC).eep
	avr-objcopy -O ihex -R .eeprom $(TARGET_EXEC).elf $(TARGET_EXEC).hex

$(BUILD_DIR)/%.c.o:%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.cpp.o:%.cpp
	mkdir -p $(dir $@)
	$(CPP) $(CPPFLAGS) $< -o $@

$(BUILD_DIR)/%.S.o:%.S
	mkdir -p $(dir $@)
	$(CC) $(ASSFLAGS) $< -o $@

# all:
	# @echo $(SRCS) $(OBJS)

clean:
	rm -r ./build

flash:$(TARGET_EXEC).hex
	$(AVRDUDE) -b 57600 -D -U flash:w:$<
