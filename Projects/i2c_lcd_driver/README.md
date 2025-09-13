# I²C LCD Driver Project (1602A + PCF8574 + ATmega328P)

## Goal
I hope this project will serve as a **good starting point in embedded systems**, giving me skills that can transfer to **other peripherals, protocols, and microcontrollers** in the future.

The purpose of this project is to **learn I²C intuitively and progressively**, starting from high-level Arduino libraries and moving down to **bare-metal register programming** on the ATmega328P.  

By the end of the week, the aim is to display characters on a **1602A LCD** through its **PCF8574 I²C backpack**, first using `Wire.h` and `LiquidCrystal_I2C`, then by writing a **custom driver**, and finally by controlling the LCD over I²C **without any libraries** (direct TWI register access).

---

## Learning Objectives
- Understand the **I²C protocol** (SDA/SCL, addressing, START/STOP conditions, ACK/NACK).  
- Learn how Arduino’s `Wire` library sends data to I²C devices.  
- Control the **PCF8574 I/O expander** directly over I²C.  
- Map PCF8574 pins to the **HD44780 LCD controller** signals.  
- Implement a **minimal LCD driver** (send commands, print characters, set cursor).  
- Replace the `Wire` library with **bare-metal TWI register code** on ATmega328P.  

---

## Hardware
- Arduino Uno clone (ATmega328P)  
- 1602A LCD with I²C backpack (PCF8574)  

---
