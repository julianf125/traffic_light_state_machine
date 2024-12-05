# Traffic Light State Machine

## Overview
This repository contains a **traffic light state machine** implemented in C.

## Features
- **State Machine**: Manages `RED`, `GREEN`, `YELLOW`, and `FLASH_RED` states with configurable durations.
- **Error Handling**: Enters `FLASH_RED` state for invalid configurations.
- **Test Suite**: Verifies initialization, state transitions, error handling, and display output.

## Build and Run

### Compile and Run the Main Program
```bash
make
./traffic_light
```
By default, the program initializes the traffic light with the default state duration values defined in traffic_light.h. This results in successful initialization and correct routine behavior. To observe the traffic light in the FLASH_RED error state, modidy one or more of the defined values to equal 0.

### Compile and Run the Test Suite
```bash
make test
./test_traffic_light
```

## Repository Structure
```bash
.
├── main.c                 # Main file
├── traffic_light.c        # Traffic light state machine implementation
├── traffic_light.h        # Traffic light state machine header file
├── test_traffic_light.c   # Test suite
├── makefile               # Makefile
└── README.md              # Documentation
```

## Author
Julian Frank

julianfrank125@gmail.com
