# STM32F401CCU6

## System and Memory Architecture
In order to determine which clocks to enable, you must know which periphiral
sits on which bus (AHB1, APB2, etc.).

## Flash Memory Interface
TODO: Understand what this means
Essential for writing Wait States (Latency).

## Reset and Clock Control
The most important part of the manual as nothing will work without a clock.

## General Purpose Input Output
### Flow for understanding the manual
1. Introduction and Main Features - What can the specific pin do?
2. Functional Description - Explains states, data flow, and internal behavior.
3. Register Map - The cheatsheat.
4. Register Descriptions - This is where you'll live. It defines every single bit.
    - Look for "Configuration Procedure" or "Sequence" headings within the
    functional description.

## Key Documents to Keep Open
The Reference Manual isn't enough on its own. You need a "Triple Threat" of PDFs:
1. The Reference Manual (RM0368): How to use the peripherals (The "How").
2. The Datasheet: Pinouts, electrical characteristics, and memory sizes (The "Where" and "How Much").
3. The Programming Manual (PM0214): Covers the actual Cortex-M4 processor core, registers, and instruction set.


### Features
- 16 I/O pins
- Output data from Output Data Register (GPIOx_ODR) 
- Input data to Input Data Register (GPIOx_IDR)
- Bit set and reset register (GPIOx_BSRR) for bitwise write access to (GPIOx_ODR)
- Locking mechanism (GPIOx_LCKR) to freeze the I/O configuration
- Analog function
- Alternate function I/O selection registers (at most 16 AFs per I/O)

