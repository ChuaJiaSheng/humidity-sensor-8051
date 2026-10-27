# Humidity Sensor and 8051 Integration

Hardware documentation and a demonstration of a humidity-measurement prototype with an 8051-based sensor/display arrangement.

**Repository type:** hardware portfolio and design documentation. A complete standalone firmware build project is not included.

## What this repository provides

Start with the wiring schematic, then read the operational flow diagrams and watch the demonstration. These materials explain the supplied hardware prototype without requiring a software installation. There is no top-level build command because the repository does not contain a complete firmware toolchain project.

## Explore the repository

| Material | What to inspect |
| --- | --- |
| [8051 schematic](hardware/8051%20Schematic.png) | The supplied microcontroller, sensor, and display wiring drawing |
| [Page 1](hardware/Page%201.png) | Main operational flow diagram |
| [Page 2](hardware/Page%202.png) | DHT22-related flow diagram |
| [Page 3](hardware/Page%203.png) | ADC-related flow diagram |
| [Demonstration video](media/demo.mp4) | The assembled measurement hardware and displayed readings |
| [QR image](hardware/qrcode.png) | Supporting project QR image |

![8051 hardware schematic](hardware/8051%20Schematic.png)

Open the images directly in GitHub. The video is available through the file link; download it if GitHub does not play it inline.

## Reading the design

- Use the schematic to trace the connections between the microcontroller, sensor interfaces, and display.
- Follow Page 1 for the overall operating sequence.
- Compare the sensor-reading sequence on Page 2 with the ADC-related sequence on Page 3.
- Use the demo to see the assembled hardware and displayed readings. The video shows a demonstration, not a calibration procedure.

The diagrams are reference material rather than automatically generated documentation from a firmware build. They do not establish the exact compiler settings, driver versions, clock configuration, or calibration values required for another board.

## Reproduction checklist

Before attempting a local reconstruction, identify the exact 8051 variant, supply and signal levels, sensor/display interfaces, pin assignments, clock, programmer, and firmware dependencies. Compare those choices with the schematic and flow diagrams. These items must be verified on the intended hardware; they are not supplied as a tested bill of materials or build configuration here.
