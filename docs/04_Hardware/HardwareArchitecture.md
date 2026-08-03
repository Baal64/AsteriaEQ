
# Hardware Architecture

## 1. Purpose

This document describes the hardware architecture of Asteria EQ.

It explains:

- the role of each electronic component;
- the communication buses used by the mount;
- the separation between time-critical and non-time-critical signals;
- the main power-distribution principles;
- the design decisions that constrain the firmware architecture.

The exact electrical connections are documented separately in
[`Pinout.md`](./Pinout.md).

---

## 2. Design principles

The Asteria EQ hardware architecture follows these principles:

1. Time-critical signals are handled directly by the microcontroller.
2. Low-frequency control and status signals may be delegated to an I/O expander.
3. Hardware interrupts must not contain business logic.
4. STEP pulse generation must be deterministic.
5. Communication buses are shared whenever the connected devices support it.
6. Configuration values must remain separate from hardware-control code.
7. Every signal must have a clearly identified owner and timing constraint.
8. A common electrical ground must be shared by all connected modules.

Asteria EQ therefore separates:

- business decisions;
- real-time pulse generation;
- direct GPIO operations;
- expanded GPIO operations;
- sensor communication;
- power distribution.

---

## 3. System overview

The main controller is an ATmega32U4-based Pro Micro running at 5 V and
16 MHz.

It coordinates:

- two TMC2209 stepper drivers;
- two 0.9° NEMA 17 stepper motors;
- two AS5048A absolute magnetic encoders;
- two Hall-effect home sensors;
- an ST-4 autoguiding input;
- an analog joystick with push button;
- one or more status LEDs;
- one MCP23017 I/O expander.

The main communication paths are:

- STEP/DIR signals for motor control;
- SPI for the AS5048A encoders;
- I²C for the MCP23017;
- direct digital inputs for Hall and ST-4 signals;
- analog inputs for the joystick axes.

---

## 4. Processing architecture

### 4.1 Pro Micro

The Pro Micro executes the firmware and hosts the time-critical logic.

It is directly responsible for:

- generating the RA STEP signal;
- generating the DEC STEP signal;
- controlling the RA DIR signal;
- controlling the DEC DIR signal;
- reading both Hall sensors;
- reading the four ST-4 directions;
- reading the joystick analog axes;
- reading the joystick push button;
- communicating with both AS5048A encoders over SPI;
- communicating with the MCP23017 over I²C.

Signals requiring deterministic timing or immediate reaction remain connected
directly to the Pro Micro.

### 4.2 MCP23017

The MCP23017 provides sixteen additional GPIO lines over I²C.

It is used for signals that do not require deterministic or high-frequency
updates.

The initial allocation includes:

- RA driver ENABLE;
- DEC driver ENABLE;
- status LED outputs;
- future low-frequency control or indication signals.

The MCP23017 must not be used to generate STEP pulses.

It should also not be used for safety-critical or latency-sensitive inputs
unless that decision is explicitly reviewed and documented.

---

## 5. Motion-control architecture

### 5.1 Motors

Both axes use 0.9° NEMA 17 stepper motors.

The nominal characteristics are:

| Axis | Full steps per revolution | Step angle |
|---|---:|---:|
| Right Ascension | 400 | 0.9° |
| Declination | 400 | 0.9° |

### 5.2 Mechanical reduction

The current mechanical reductions are:

| Axis | Reduction |
|---|---:|
| Right Ascension | 188:1 |
| Declination | 2:1 |

The reduction value represents the number of motor revolutions required for
one axis revolution.

### 5.3 Microstepping

The initial firmware configuration uses:

```text
16 microsteps per full motor step
```

his value is configurable and may evolve after mechanical and tracking tests.

### 5.4 TMC2209 drivers

Each motor is controlled by one TMC2209 driver.

The mandatory control signals are:

- STEP;
- DIR;
- ENABLE.

STEP and DIR are driven directly by the Pro Micro.

ENABLE is delegated to the MCP23017 because it changes infrequently and has no
strict timing requirement.

UART configuration of the TMC2209 is considered a future extension. The
initial implementation may use hardware-configured operating parameters.

### 5.5 STEP pulse generation

STEP pulses must be generated using hardware timers.

The firmware business layer determines the requested angular velocity.

The motor-driver layer converts that velocity into:

- a direction;
- a positive STEP frequency.

The timer layer produces deterministic pulses at the requested frequency.

Interrupt routines used for STEP generation must remain short and must not
contain:

- tracking logic;
- guiding logic;
- GoTo logic;
- arbitration logic;
- logging;
- blocking operations.

The architectural rule is:

- Software decides. Hardware schedules.

## 6. Position sensing

### 6.1 AS5048A encoders

Each axis uses one AS5048A absolute magnetic encoder.

Both encoders share the hardware SPI bus:

- MOSI;
- MISO;
- SCK.

Each encoder has its own chip-select signal:

- CS RA;
- CS DEC.

Only one chip-select line may be active at a time.

The encoder interface provides absolute angular feedback independently from
the commanded step count.

### 6.2 Hall home sensors

Each axis uses one Hall-effect sensor for homing:

- HOME RA;
- HOME DEC.

The Hall sensors are connected directly to the Pro Micro.

They are not routed through the MCP23017 because homing and limit detection
must remain responsive and independent from I²C availability.

The firmware must define:

the electrical active level;
whether internal pull-up resistors are used;
the expected behavior when a sensor is disconnected;
the safe reaction to an unexpected activation.

## 7. Autoguiding interface

Asteria EQ supports a standard ST-4 guiding input with four active-low
directions:

- RA+;
- RA−;
- DEC+;
- DEC−.

The ST-4 signals are read directly by the Pro Micro.

They must be treated as external digital inputs and electrically protected as
required by the final interface circuit.

The ST-4 interface produces guiding corrections. It must not directly generate
motor pulses.

## 8. User controls

### 8.1 Joystick

The joystick provides:

- one analog RA axis;
- one analog DEC axis;
- one digital push button.

The analog axes are connected directly to ADC-capable Pro Micro pins.

The firmware will apply:

- center calibration;
- dead-zone filtering;
- direction mapping;
- configurable maximum manual speed.

## 8.2 Status LED

Status LEDs are low-frequency outputs and are therefore connected to the
MCP23017.

The initial design uses at least one blue status LED.

Each LED must use an appropriate series resistor. A nominal value around
220 ohms is expected, subject to the selected LED characteristics and supply
voltage.

## 9. Communication buses

### 9.1 SPI

The SPI bus is shared by both AS5048A encoders.

Shared signals:

- MOSI;
- MISO;
- SCK.

Dedicated signals:

- CS RA;
- CS DEC.

The SPI bus remains reserved for devices requiring deterministic and relatively
fast communication.

### 9.2 I²C

The I²C bus connects the Pro Micro to the MCP23017.

Shared signals:

- SDA;
- SCL.

The MCP23017 address must be documented in Pinout.md.

Bus pull-up resistors must be present either on the module or externally. Their
effective combined resistance must be checked if several modules include
on-board pull-ups.

## 10. Power architecture

The system uses separate logical and motor-power domains.

### 10.1 Motor supply

The TMC2209 motor-power inputs are supplied from the 12 V power rail.

The motor supply must include:

- suitable wire gauge;
- reverse-polarity protection if implemented;
- local bulk decoupling near the drivers;
- a common ground with the controller.

### 10.2 Logic supply

The Pro Micro uses 5 V logic.

The logic voltage compatibility of every connected module must be verified
before wiring.

In particular, the following must be confirmed:

- TMC2209 logic-input compatibility;
-MCP23017 supply voltage;
- AS5048A module supply and logic levels;
- Hall-sensor output voltage;
- joystick output range.

### 10.3 Common ground

All modules exchanging digital or analog signals must share a common ground:

- Pro Micro;
- both TMC2209 drivers;
- MCP23017;
- AS5048A encoders;
- Hall sensors;
- joystick;
- ST-4 interface;
- external 5 V and 12 V supplies where applicable.

A missing common ground may produce unreliable signals or damage components.

## 11. Initial responsibility allocation

| Function        | Hardware owner  | Reason                         |
| --------------- | --------------- | ------------------------------ |
| RA STEP         | Pro Micro timer | Deterministic timing           |
| DEC STEP        | Pro Micro timer | Deterministic timing           |
| RA DIR          | Pro Micro GPIO  | Immediate direction control    |
| DEC DIR         | Pro Micro GPIO  | Immediate direction control    |
| RA ENABLE       | MCP23017        | Low-frequency state            |
| DEC ENABLE      | MCP23017        | Low-frequency state            |
| AS5048A SPI     | Pro Micro SPI   | Shared hardware bus            |
| Encoder CS      | Pro Micro GPIO  | Deterministic device selection |
| Hall RA         | Pro Micro GPIO  | Homing and safety              |
| Hall DEC        | Pro Micro GPIO  | Homing and safety              |
| ST-4 inputs     | Pro Micro GPIO  | Responsive guiding inputs      |
| Joystick axes   | Pro Micro ADC   | Analog measurement             |
| Joystick button | Pro Micro GPIO  | User input                     |
| Status LED      | MCP23017        | Low-frequency indication       |

## 12. Design decisions

### 12.1 Why use an MCP23017? 

The Pro Micro does not provide enough convenient GPIO lines for every planned
feature.

The MCP23017 adds sixteen digital lines while consuming only the shared I²C
bus.

### 12.2 Why keep STEP on the Pro Micro? 

STEP requires precise and regular pulse timing.

Generating it through I²C would introduce variable latency and make pulse
frequency dependent on bus traffic.

### 12.3 Why keep Hall sensors on the Pro Micro? 

Home detection must remain responsive and should not depend on successful I²C
communication.

### 12.4 Why share the SPI bus? 

The AS5048A supports independent chip-select inputs. Sharing MOSI, MISO and SCK
reduces GPIO usage while preserving deterministic access to each encoder.

### 12.5 Why place ENABLE on the MCP23017? 

ENABLE changes rarely and does not require deterministic timing.

Moving it to the MCP23017 frees two direct MCU pins without affecting motor
control quality.

## 13. Pending decisions

The following decisions must be completed before final wiring:

- exact Pro Micro pin allocation;
- timer allocation for RA and DEC STEP;
- MCP23017 I²C address;
- final MCP23017 port allocation;
- TMC2209 microstep configuration method;
- TMC2209 UART usage;
- electrical conditioning of ST-4 inputs;
- Hall-sensor active level and pull-up strategy;
- validation of module logic voltages;
- final power-distribution and protection scheme.

These items are tracked in Pinout.md and the relevant ADR documents.
