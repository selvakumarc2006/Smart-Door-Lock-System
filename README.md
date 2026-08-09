# 🔐 Smart door lock System

A register-level embedded access control system developed using the **Arduino Mega 2560**. The system accepts a 4-digit PIN through a matrix keypad, verifies the PIN, displays the entered digits on a 4-digit 7-segment display, shows access status on a 16×2 LCD, and controls a servo motor for locking and unlocking.

## 🚀 Features

* 4×3 matrix keypad for PIN entry
* 4-digit PIN storage and verification
* `*` key for clearing the entered PIN
* `#` key for confirming the PIN
* 4-digit 7-segment display for PIN entry
* 16×2 LCD for system status
* Servo motor for lock/unlock mechanism
* Timer1 Fast PWM for servo control
* Register-level GPIO configuration
* Register-level Timer1 configuration
* Keypad matrix scanning
* 7-segment multiplexing
* Wokwi simulation

## 🔧 Hardware / Components

* Arduino Mega 2560
* 4×3 Matrix Keypad
* 4-digit 7-segment display
* 16×2 LCD
* Servo motor
* LEDs
* Buzzer
* Jumper wires

## 🧠 Working Principle

The user enters a 4-digit PIN using the matrix keypad.

### Key functions

| Key   | Function          |
| ----- | ----------------- |
| `0–9` | Enter digit       |
| `*`   | Clear entered PIN |
| `#`   | Confirm PIN       |

After entering four digits and pressing `#`, the entered PIN is compared with the predefined password.

### Correct PIN

```text
ACCESS GRANTED
```

The servo motor rotates to the unlock position.

### Incorrect PIN

```text
ACCESS DENIED
```

The servo remains in the locked position.

## ⚙️ Servo PWM

Timer1 of the ATmega2560 is configured in **Fast PWM mode with ICR1 as TOP**.

```text
TOP = 39999
PWM Frequency = 50 Hz
Period = 20 ms
```

The servo position is controlled by changing the OCR1A value.

```text
OCR1A ≈ 2000  → Lock position
OCR1A ≈ 3000  → Approximately 90°
OCR1A ≈ 4000  → Unlock position
```

## 🔌 Register-Level Programming

Instead of relying completely on Arduino functions such as `pinMode()` and `digitalWrite()`, the project directly accesses the ATmega2560 registers using pointers.

Example:

```c
volatile unsigned char *ddrb =
    (volatile unsigned char *)0x24;
```

Timer1 registers are also configured directly:

```c
*tccr1a = (1 << 7) | (1 << 1);

*tccr1b = (1 << 4) |
          (1 << 3) |
          (1 << 1);
```

This helps demonstrate understanding of:

* GPIO registers
* Timer/Counter registers
* PWM generation
* Memory-mapped I/O
* Bit manipulation
* Peripheral interfacing

## 📊 System Flow

```text
             ┌──────────────┐
             │  4×3 Keypad  │
             └──────┬───────┘
                    │
                    ▼
            ┌───────────────┐
            │ Arduino Mega  │
            │  ATmega2560   │
            └───┬───────┬───┘
                │       │
        ┌───────┘       └────────┐
        ▼                        ▼
 ┌─────────────┐          ┌─────────────┐
 │ 7-Segment   │          │    LCD      │
 │ PIN Display │          │   Status    │
 └─────────────┘          └─────────────┘
                │
                ▼
          ┌──────────┐
          │  Servo   │
          │ Lock/    │
          │ Unlock   │
          └──────────┘
```

## 🛠️ Technologies Used

* Embedded C
* Arduino Mega 2560
* ATmega2560
* GPIO
* Timer1
* PWM
* Matrix Keypad
* 7-Segment Display
* 16×2 LCD
* Servo Motor
* Wokwi
* Register-Level Programming

## 🎯 Learning Outcomes

This project provided practical experience in integrating multiple peripherals into a single embedded system. It strengthened my understanding of register-level programming, timer configuration, PWM generation, keypad scanning, display multiplexing, and embedded C programming.


```text
images/circuit.png
images/Access Granted.png
```

## 👨‍💻 Author

**Selvakumar C**

Embedded Systems | Embedded C | Firmware Development

---

⭐ If you find this project useful, feel free to explore the code and simulation.
