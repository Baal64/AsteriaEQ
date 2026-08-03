
# Pinout

## 1. Status

> **Status: provisional**
>
> This pinout must not yet be used as the final wiring reference.
>
> STEP pins depend on the final ATmega32U4 hardware-timer allocation.
> Remaining GPIO assignments will be validated only after checking all
> peripheral and interrupt constraints.

---

## 2. Naming conventions

| Name | Meaning |
|---|---|
| RA | Right Ascension |
| DEC | Declination |
| STEP | Step-pulse input of a motor driver |
| DIR | Motor-direction input |
| EN | Motor-driver enable input |
| CS | SPI chip-select |
| HOME | Hall-effect home sensor |
| ST4 | Autoguiding input |
| GPA / GPB | MCP23017 GPIO banks |

---

## 3. Pro Micro allocation

### 3.1 Motor control

| Signal | Pro Micro pin | Direction | Connected device | Status |
|---|---|---|---|---|
| RA STEP | TBD | Output | TMC2209 RA STEP | Timer allocation required |
| RA DIR | TBD | Output | TMC2209 RA DIR | To assign |
| DEC STEP | TBD | Output | TMC2209 DEC STEP | Timer allocation required |
| DEC DIR | TBD | Output | TMC2209 DEC DIR | To assign |

The ENABLE signals are not connected directly to the Pro Micro.

### 3.2 SPI bus

| Signal | Pro Micro pin | Direction | Connected device | Status |
|---|---|---|---|---|
| SPI MOSI | Hardware SPI MOSI | Output | AS5048A RA and DEC | Reserved |
| SPI MISO | Hardware SPI MISO | Input | AS5048A RA and DEC | Reserved |
| SPI SCK | Hardware SPI SCK | Output | AS5048A RA and DEC | Reserved |
| AS5048A CS RA | TBD | Output | AS5048A RA CS | To assign |
| AS5048A CS DEC | TBD | Output | AS5048A DEC CS | To assign |

### 3.3 I²C bus

| Signal | Pro Micro pin | Direction | Connected device | Status |
|---|---|---|---|---|
| SDA | Hardware I²C SDA | Bidirectional | MCP23017 SDA | Reserved |
| SCL | Hardware I²C SCL | Output | MCP23017 SCL | Reserved |

### 3.4 Hall sensors

| Signal | Pro Micro pin | Direction | Connected device | Status |
|---|---|---|---|---|
| HOME RA | TBD | Input | RA Hall sensor | To assign |
| HOME DEC | TBD | Input | DEC Hall sensor | To assign |

### 3.5 ST-4 interface

| Signal | Pro Micro pin | Direction | Active level | Status |
|---|---|---|---|---|
| ST4 RA+ | TBD | Input | Low | To assign |
| ST4 RA− | TBD | Input | Low | To assign |
| ST4 DEC+ | TBD | Input | Low | To assign |
| ST4 DEC− | TBD | Input | Low | To assign |

### 3.6 Joystick

| Signal | Pro Micro pin | Direction | Status |
|---|---|---|---|
| Joystick X | A1 | Analog input | Proposed |
| Joystick Y | A2 | Analog input | Proposed |
| Joystick switch | A3 | Digital input | Proposed |

The previous joystick allocation is retained provisionally because it does not
conflict with the intended SPI or I²C buses. It must still be checked against
the final timer and GPIO allocation.

---

## 4. MCP23017 allocation

### 4.1 I²C address

| Parameter | Value |
|---|---|
| Address | TBD |
| A0 | TBD |
| A1 | TBD |
| A2 | TBD |

The selected address must match the physical A0, A1 and A2 wiring.

### 4.2 Port A

| MCP23017 pin | Function | Direction | Active level | Status |
|---|---|---|---|---|
| GPA0 | RA ENABLE | Output | Low | Proposed |
| GPA1 | DEC ENABLE | Output | Low | Proposed |
| GPA2 | Status LED | Output | High | Proposed |
| GPA3 | Reserved | — | — | Available |
| GPA4 | Reserved | — | — | Available |
| GPA5 | Reserved | — | — | Available |
| GPA6 | Reserved | — | — | Available |
| GPA7 | Reserved | — | — | Available |

### 4.3 Port B

| MCP23017 pin | Function | Direction | Active level | Status |
|---|---|---|---|---|
| GPB0 | Reserved | — | — | Available |
| GPB1 | Reserved | — | — | Available |
| GPB2 | Reserved | — | — | Available |
| GPB3 | Reserved | — | — | Available |
| GPB4 | Reserved | — | — | Available |
| GPB5 | Reserved | — | — | Available |
| GPB6 | Reserved | — | — | Available |
| GPB7 | Reserved | — | — | Available |

---

## 5. TMC2209 connections

### 5.1 Right Ascension driver

| TMC2209 signal | Connected to | Status |
|---|---|---|
| STEP | Pro Micro RA STEP | Pin TBD |
| DIR | Pro Micro RA DIR | Pin TBD |
| EN | MCP23017 GPA0 | Proposed |
| VM | 12 V motor supply | Required |
| GND | Common ground | Required |
| VIO | Logic supply | Voltage to confirm |
| M1A / M1B | Motor coil 1 | Wiring to identify |
| M2A / M2B | Motor coil 2 | Wiring to identify |
| UART / PDN | TBD | Future option |
| MS1 / MS2 | TBD | Microstep configuration |
| CLK | Module-dependent | Verify before wiring |

### 5.2 Declination driver

| TMC2209 signal | Connected to | Status |
|---|---|---|
| STEP | Pro Micro DEC STEP | Pin TBD |
| DIR | Pro Micro DEC DIR | Pin TBD |
| EN | MCP23017 GPA1 | Proposed |
| VM | 12 V motor supply | Required |
| GND | Common ground | Required |
| VIO | Logic supply | Voltage to confirm |
| M1A / M1B | Motor coil 1 | Wiring to identify |
| M2A / M2B | Motor coil 2 | Wiring to identify |
| UART / PDN | TBD | Future option |
| MS1 / MS2 | TBD | Microstep configuration |
| CLK | Module-dependent | Verify before wiring |

---

## 6. AS5048A connections

### 6.1 Shared SPI signals

| AS5048A signal | Connected to |
|---|---|
| MOSI | Pro Micro hardware MOSI |
| MISO | Pro Micro hardware MISO |
| SCK | Pro Micro hardware SCK |
| GND | Common ground |
| Supply | Compatible logic supply, to confirm |

### 6.2 Dedicated chip selects

| Encoder | CS connection |
|---|---|
| RA AS5048A | Pro Micro GPIO, TBD |
| DEC AS5048A | Pro Micro GPIO, TBD |

---

## 7. Hall-sensor connections

| Sensor signal | Connection | Status |
|---|---|---|
| RA Hall output | Pro Micro HOME RA | Pin TBD |
| DEC Hall output | Pro Micro HOME DEC | Pin TBD |
| Sensor supply | Compatible supply | To confirm |
| Sensor ground | Common ground | Required |

The final document must state whether each output is:

- open collector;
- push-pull;
- active high;
- active low.

---

## 8. Status LED

| Signal | Connection | Notes |
|---|---|---|
| LED control | MCP23017 GPA2 | Proposed |
| LED resistor | Series resistor | Approximately 220 ohms |
| LED return | Ground or supply according to wiring | To define |

---

## 9. Power connections

| Rail | Connected devices |
|---|---|
| 12 V | TMC2209 motor supplies |
| 5 V | Pro Micro and compatible logic modules |
| 3.3 V | Only where explicitly required |
| GND | All modules |

Power must remain disconnected while continuity and short-circuit checks are
performed.

---

## 10. Pre-wiring checklist

Before connecting power:

- [ ] Validate the Pro Micro pin map.
- [ ] Validate RA and DEC timer allocation.
- [ ] Confirm every module supply voltage.
- [ ] Identify both coils of each motor with a multimeter.
- [ ] Confirm common-ground continuity.
- [ ] Confirm no short circuit between 12 V, 5 V, 3.3 V and GND.
- [ ] Confirm MCP23017 address wiring.
- [ ] Confirm I²C pull-up resistors.
- [ ] Confirm AS5048A SPI voltage compatibility.
- [ ] Confirm Hall-sensor output type.
- [ ] Confirm TMC2209 EN active level.
- [ ] Confirm TMC2209 microstep configuration.
- [ ] Keep the motors disconnected during initial GPIO tests.
- [ ] Test ENABLE and DIR levels before installing the drivers.