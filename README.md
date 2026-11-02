# STM32 Automatic Pet Feeder

I wanted to start working on something a little more involved than the smaller projects I've done so far with my embedded learning.

The goal is to build an automatic pet feeder using my STM32 NUCLEO-C031C6. I want it to dispense food at scheduled times, measure how much food has been dispensed using a load cell, and detect when something goes wrong, like a jam or an empty container.

I'm writing the firmware in C using CMSIS and working directly with the STM32 registers rather than relying on HAL. I do, however, plan to use HAL later, and also plan to incorporate FreeRTOS as the project gets more complex.

## Current Progress

The project is still in its early stages. So far, I've set up the basic firmware infrastructure and implemented UART communication for debugging.

Currently implemented:

- Bare-metal STM32 firmware using CMSIS (no HAL)
- USART2 communication at 115200 baud
- Polling-based UART transmission
- SysTick interrupts for millisecond timing
- Non-blocking periodic execution using a tick counter
- Separate modules for UART communication and board initialization
- Makefile-based build using the ARM GNU Toolchain

Right now, the STM32 sends a message over UART every second. It's a simple starting point, but it gives me a way to debug the firmware as I start connecting other hardware.

## Planned Features

- Servo-controlled food dispensing mechanism
- HX711 load cell interface for measuring dispensed food
- DS3231 real-time clock for scheduled feeding
- Portion control based on weight
- Jam detection and error handling
- FreeRTOS for managing concurrent tasks

My plan is to implement and test each component individually before putting everything together.

## Hardware

- STM32 NUCLEO-C031C6
- Servo motor
- HX711 amplifier and load cell (planned)
- DS3231 RTC module (planned)
- External 5V power supply for the servo (planned)
- Breadboard and jumper wires

## Third-Party Code

This project uses STMicroelectronics' CMSIS device headers, startup assembly, system initialization code, and linker configuration.

The original STMicroelectronics copyright notices have been preserved. The UART driver, board support code, and application logic are my own work.

## Status

Work in progress. I'll continue updating this repository as I implement the hardware drivers, feeding logic, and eventually FreeRTOS.
