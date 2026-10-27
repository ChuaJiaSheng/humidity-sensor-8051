# Humidity Sensor and 8051 Integration

An 8051 humidity/temperature measurement prototype that reads a DHT22 and an analogue humidity-sensor signal, selects a humidity value, and displays humidity and temperature on an LCD.

**Firmware target:** the device registers declared by `SM59R16A5.h`. The source uses 8051 compiler extensions (`sbit`, `interrupt`, and `using`), so it cannot be compiled unchanged as ordinary desktop C.

## Get the project

```sh
git clone https://github.com/ChuaJiaSheng/humidity-sensor-8051.git
cd humidity-sensor-8051
```

## Firmware files

| File | Responsibility |
| --- | --- |
| [src/222257U_main.c](src/222257U_main.c) | Initialisation, measurement loop, humidity selection, and LCD output |
| [src/DHT22_1.c](src/DHT22_1.c) | Timer delays, DHT22 acquisition, ADC reading, and analogue conversion |

The source listings retain their supplied logic. Their presence does not yet constitute a complete buildable firmware project.

## How the program works

1. `setup()` configures the timers, interrupts, and ADC registers.
2. The main program initialises and clears the LCD.
3. Each loop waits using `timer_ms(1000)`, then calls `readht()` and `adcc()`.
4. `readht()` collects five DHT22 bytes on **P3.0** and calculates humidity and temperature values.
5. `adcc()` combines the ADC result registers, calculates voltage/resistance, and applies the polynomial `h = 0.0033*r*r - 0.827*r + 52.493`.
6. The main program attempts to compare the two humidity values: it selects the DHT22 value for a difference of at least 10, otherwise the analogue value.
7. The LCD is written with `RH:`, a percentage, and `Temp:`.

The comparison and scaling need correction or confirmation before the intended selection behaviour can be relied on; see the implementation notes below.

## Dependencies needed to build

| Missing item | Why it is needed |
| --- | --- |
| `dht22_1.h` | Function declarations used by the main program |
| `SM59R16A5.h` | Device-specific register/bit definitions, including timer and ADC registers |
| `IIC LCD.h` and the matching LCD implementation | LCD initialisation, cursor, string, and number functions, including `HIDE_CSR` |
| 8051 compiler/project configuration | Support for the interrupt/bit extensions, device selection, memory model, and clock settings |

Preserve the include spelling: the main program includes `"dht22_1.h"` and `"IIC LCD.h"`. Case and spaces matter when moving the files between systems. A header alone cannot supply the LCD function implementations.

## Build procedure once dependencies are available

1. Install an 8051 toolchain supporting the syntax used by these files.
2. Create/select a project for the exact controller corresponding to `SM59R16A5.h`; a generic 8051 register header is not a substitute for the ADC registers.
3. Add `src/222257U_main.c`, `src/DHT22_1.c`, and the LCD implementation as source files. Add the directories containing the three required headers to the include search path.
4. Set the actual oscillator frequency, timer clock mode, memory model, and programmer settings for the board.
5. Review the implementation notes below, then compile and link. Missing-header errors mean the dependencies are still incomplete; unresolved LCD symbols mean its implementation is missing or not included in the build.
6. After a successful build, program the board using its correct programming interface. Compare physical wiring with the schematic before powering the sensor/display circuit.

**Current reproduction boundary:** the two C listings are available, but the headers, LCD implementation, full project settings, and calibration details are not yet included. An exact successful build command cannot be given until the toolchain/project files are supplied.

## Hardware setup and expected display

- Connect the DHT22 data signal to **P3.0**, as declared by `sbit dht_data = P3^0`.
- Match the analogue input and LCD wiring to the schematic and the missing device/LCD definitions. The ADC pin and LCD bus pins should not be guessed from a generic 8051 pinout.
- Confirm supply/reference voltage, signal levels, sensor resistance units, pull-ups, and the board oscillator before running.
- With working drivers and valid readings, the intended display contains `RH:` with `%` and `Temp:` with `*C`. Exact number formatting depends on `lcd_print_int_2p2()`.

Use a known humidity/temperature reference to check readings. The demo video shows the assembled measurement arrangement, not a calibration guarantee.

## Implementation notes affecting reproduction

| Area | Issue to resolve or verify |
| --- | --- |
| Humidity difference | `error` is `unsigned long`. It cannot be negative, so `if (error < 0)` does not produce an absolute difference and subtraction can wrap. |
| Humidity units | DHT humidity is multiplied by 10, while analogue `h` is multiplied by 1000. Confirm both scales and the LCD formatter before comparing them or interpreting threshold 10. |
| ADC completion | `while (!IRCON && 0x04);` tests logical expressions, not a masked ADC-complete bit. Check the controller's documented flag and clearing behaviour before choosing a replacement. |
| Timing | Timer reloads depend on the board clock. Comments about milliseconds/microseconds are insufficient to establish the actual delay. The start-pulse comment and `timer_ms(5)` call also disagree. |
| Interrupt-shared counters | `x` and `y` change inside ISRs and are polled by foreground code. Review `volatile` and access atomicity for the selected compiler/optimisation level. |
| Sensor communication | Wait loops have no timeouts; an absent or unresponsive sensor can stall execution. The fifth DHT22 byte is collected but no checksum comparison is implemented. |
| Temperature | The conversion masks out the DHT22 sign bit without applying a negative sign. |
| Analogue conversion | Confirm the polynomial's resistance units and calibrated range. The source divides by `5-v`, which becomes zero at full-scale voltage. |

## Circuit and demonstration

| Material | Content |
| --- | --- |
| [8051 schematic](hardware/8051%20Schematic.png) | Sensor, microcontroller, and display wiring drawing |
| [Page 1](hardware/Page%201.png) | Main operational flow |
| [Page 2](hardware/Page%202.png) | DHT22-related flow |
| [Page 3](hardware/Page%203.png) | ADC-related flow |
| [Demonstration video](media/demo.mp4) | Recorded hardware demonstration |
| [QR image](hardware/qrcode.png) | Supporting project QR image |

![8051 hardware schematic](hardware/8051%20Schematic.png)
