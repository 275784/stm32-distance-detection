# STM32 Distance Detection System

Embedded distance measurement and detection system based on an STM32L152 microcontroller.

The system allows the user to configure a target distance and tolerance range using a rotary encoder and potentiometer. An HC-SR04 ultrasonic sensor measures the current distance, while an I2C LCD displays the system status.

## Features

- Distance measurement using an HC-SR04 ultrasonic sensor
- Configurable target distance and detection tolerance
- Object detection based on the measured distance
- I2C LCD user interface
- Periodic sensor measurements
- Modular embedded C firmware
- STM32 HAL

## System Architecture

The system uses three inputs connected to the STM32L152:

- **HC-SR04** — distance measurement
- **Rotary encoder** — target distance
- **Potentiometer** — detection tolerance

The STM32 processes the input data and determines whether an object is within the configured distance range. The result is displayed on the I2C LCD.

```text
                         ┌──────────────────────┐
                         │      STM32L152       │
                         │     Microcontroller  │
                         ├──────────────────────┤
HC-SR04 ─────────────────► Timer Input Capture  │
                         │                      │
Rotary Encoder ──────────► Timer Encoder Mode   │
                         │                      │
Potentiometer ───────────► ADC                  │
                         │                      │
                         │ I2C ─────────────────┼────► LCD
                         └──────────────────────┘
```

## How It Works

1. The rotary encoder sets the target distance.
2. The potentiometer sets the allowed tolerance.
3. The HC-SR04 periodically measures the distance to an object.
4. The STM32 compares the measured distance with the target.
5. The object is detected when the difference is within the configured tolerance.
6. The current distance, target distance, tolerance and detection status are displayed on the LCD.

## My Contribution

This was an individual project.

I designed and implemented:

- HC-SR04 distance measurement
- rotary encoder handling
- I2C LCD interface
- ADC-based tolerance adjustment
- distance detection logic
- modular firmware structure

## Hardware & Technologies

### Hardware

- STM32L152
- HC-SR04 ultrasonic distance sensor
- Rotary encoder
- Potentiometer
- HD44780-compatible LCD with I2C interface

### Technologies

- C
- Embedded C
- STM32 HAL
- STM32CubeIDE
- ADC
- Timers
- Timer Input Capture
- Timer Encoder Mode
- GPIO
- I2C

## Firmware Structure

The firmware is divided into independent modules:

```text
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
```

### HCSR04 Driver

`hcsr04.c/.h` implements the ultrasonic sensor driver using STM32 Timer Input Capture.

The echo pulse duration is measured and converted into distance.

### Encoder Driver

`encoder.c/.h` handles the rotary encoder using Timer Encoder Mode.

The module manages the current value, configured limits and pulses per click.

### LCD Driver

`i2c-lcd.c/.h` provides the interface for controlling the HD44780-compatible LCD through I2C.

### Application Logic

`main.c` coordinates the individual modules and implements the distance detection logic.

## Implementation Details

### Distance Measurement

The HC-SR04 is triggered periodically. The returning echo pulse is measured using Timer Input Capture, and the pulse duration is converted into distance.

### Detection

The measured distance is compared with the configured target:

```text
|measured distance - target distance| <= tolerance
```

When this condition is met, the system reports object detection.

### User Interface

The LCD displays the current measurement parameters and detection status.

The application also limits unnecessary LCD updates by refreshing the interface only when the displayed state changes.

## Project Status

**Completed and tested.**

## Possible Improvements

- Add digital filtering for distance measurements
- Replace blocking delays with a fully non-blocking architecture
- Add configurable measurement frequency
- Add automatic sensor calibration
- Improve handling of invalid sensor readings
- Add additional sensors

## Author

**Konrad Misztela**

Intelligent Electronics  
Wrocław University of Science and Technology
