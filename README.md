# STM32 Distance Detection System

Embedded distance measurement and object detection system based on an STM32 microcontroller.

The system allows the user to configure a target distance and tolerance range using a rotary encoder and potentiometer. An HC-SR04 ultrasonic sensor measures the current distance, while an I2C LCD displays the system status.

## Features

- Distance measurement using HC-SR04 ultrasonic sensor
- Timer Input Capture for echo pulse measurement
- Rotary encoder for target distance configuration
- ADC-based tolerance adjustment
- I2C LCD user interface
- Configurable detection range
- Periodic sensor measurements
- Modular firmware architecture
- STM32 HAL-based implementation

## System Architecture
                   ┌──────────────────────┐
                   │      STM32L152       │
                   │    Microcontroller   │
                   │                      │
                   │  Timer Input Capture │
                   │  Timer Encoder       │
                   │  ADC                 │
                   │  I2C                 │
                   │  UART                │
                   └──────────┬───────────┘
                              │
          ┌───────────────────┼───────────────────┐
          │                   │                   │
          ▼                   ▼                   ▼
      HC-SR04            Rotary Encoder      Potentiometer
   Distance Sensor       Target Distance       Tolerance
          │
          │
          └───────────────────┐
                              │
                              ▼
                      Detection Logic
                              │
                              ▼
                          I2C LCD

## How It Works

1. The rotary encoder is used to select the target distance.
2. The potentiometer sets the allowed tolerance.
3. The HC-SR04 periodically measures the distance to an object.
4. The STM32 compares the measured distance with the configured target.
5. If the measured distance is within the allowed tolerance, the system reports object detection.
6. The current measurement and configuration are displayed on the LCD.

## Hardware

- STM32L152 microcontroller
- HC-SR04 ultrasonic distance sensor
- Rotary encoder
- Potentiometer
- I2C LCD display

## Technologies

- C
- STM32
- STM32 HAL
- STM32CubeIDE
- ADC
- Timers
- Timer Input Capture
- Timer Encoder Mode
- GPIO
- I2C
- UART
- Embedded Systems

## Firmware Structure

The firmware is divided into separate modules:

Core/
├── Inc/
│   ├── encoder.h
│   ├── hcsr04.h
│   ├── i2c-lcd.h
│   └── main.h
│
└── Src/
    ├── encoder.c
    ├── hcsr04.c
    ├── i2c-lcd.c
    └── main.c

### HCSR04 Driver

The `hcsr04.c/.h` module handles the ultrasonic sensor.

The implementation uses STM32 Timer Input Capture to measure the duration of the sensor echo pulse and convert it into distance.

### Encoder Driver

The `encoder.c/.h` module handles the rotary encoder using a timer configured in encoder mode.

The module manages:

- Current value
- Minimum and maximum limits
- Pulses per click

### LCD Driver

The `i2c-lcd.c/.h` module provides a simple interface for controlling the HD44780-compatible LCD through an I2C interface.

## Implementation Details

The HC-SR04 driver measures the time between the rising and falling edges of the echo signal.

The encoder is handled using a dedicated timer peripheral.

The application periodically triggers a distance measurement and updates the user interface only when necessary.

## Project Status

Completed and tested.

## What I Learned

This project allowed me to practice:

- STM32 peripheral configuration
- Embedded C programming
- Timer Input Capture
- Timer Encoder Mode
- ADC measurements
- I2C communication
- Hardware abstraction using STM32 HAL
- Modular firmware design
- Integrating sensors and user interfaces

## Possible Improvements

- Add digital filtering for distance measurements
- Replace blocking delays with a fully non-blocking architecture
- Add UART telemetry
- Add configurable measurement frequency
- Add automatic sensor calibration
- Add additional sensors

## Author

**Konrad Misztela**

Intelligent Electronics  
Wrocław University of Science and Technology
