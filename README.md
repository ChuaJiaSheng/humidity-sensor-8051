# Humidity Sensor and 8051 Integration

Hardware documentation and a demonstration of a humidity-measurement prototype with an 8051-based sensor/display arrangement.

**Repository type:** hardware portfolio and design documentation. A complete standalone firmware build project is not included.

## Obtain and inspect the project

**Prerequisites for inspection:** Git, an image viewer, and an MP4 player. No compiler is required to view the included materials.

```sh
git clone https://github.com/ChuaJiaSheng/humidity-sensor-8051.git
cd humidity-sensor-8051
```

Open the schematic in `hardware/8051 Schematic.png`, then Page 1, Page 2, and Page 3 in order. Play `media/demo.mp4` to compare the assembled measurement arrangement and displayed readings with the diagrams.

**Expected result:** you can view the circuit, operational flow diagrams, and recorded hardware demonstration. There is no runnable application or complete firmware build in this repository.

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

## What is missing for a physical reproduction

This repository alone is insufficient for a complete hardware/firmware reproduction. A reader would additionally need:

- The complete main program, sensor drivers, and LCD drivers in a buildable project.
- The exact 8051 variant, compiler/toolchain, clock, fuse/configuration settings, and programmer.
- A bill of materials with sensor, display, and interface component variants.
- Confirmed supply/signal levels and complete board/pin wiring.
- The fabricated sensor's construction details, calibration data, and conversion parameters where applicable.

Use the schematic and flow diagrams as design references. They cannot replace the missing firmware and calibration information, and the demonstration video does not establish measurement accuracy.
