# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11

# Targets
TARGET = traffic_light
TEST_TARGET = test_traffic_light

# Source files
SOURCES = main.c traffic_light.c
HEADERS = traffic_light.h

# Object files
OBJECTS = $(SOURCES:.c=.o)

# Default rule: build the main program
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Rule for building object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to build and run the test suite
test: $(TEST_TARGET)

$(TEST_TARGET): test_traffic_light.c traffic_light.c traffic_light.h
	$(CC) $(CFLAGS) -o $(TEST_TARGET) test_traffic_light.c traffic_light.c

# Clean up build artifacts
clean:
	rm -f $(TARGET) $(TEST_TARGET) $(OBJECTS)