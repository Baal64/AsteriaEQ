## Pro Micro pin allocation

| Asteria signal | MCU port | Pro Micro pin | Hardware resource |
|---|---|---|---|
| ST4 RA+ | PD2 | D0 / RXI | GPIO input |
| ST4 RA- | PD3 | D1 / TXO | GPIO input |
| MCP23017 SDA | PD1 | D2 | Hardware I2C |
| MCP23017 SCL | PD0 | D3 | Hardware I2C |
| RA DIR | PD4 | D4 / A6 | GPIO output |
| DEC STEP | PC6 | D5 | Timer3 / OC3A |
| DEC DIR | PD7 | D6 / A7 | GPIO output |
| AS5048A RA CS | PE6 | D7 | GPIO output |
| AS5048A DEC CS | PB4 | D8 | GPIO output |
| RA STEP | PB5 | D9 / A8 | Timer1 / OC1A |
| ST4 DEC+ | PB6 | D10 | GPIO input |
| ST4 DEC- | PF7 | A0 | GPIO input |
| Joystick X | PF6 | A1 | ADC6 |
| Joystick Y | PF5 | A2 | ADC5 |
| Reserved | PF4 | A3 | GPIO / ADC4 |
| AS5048A MISO | PB3 | D14 / MISO | Hardware SPI |
| AS5048A SCK | PB1 | D15 / SCK | Hardware SPI |
| AS5048A MOSI | PB2 | D16 / MOSI | Hardware SPI |

## MCP23017 allocation

| MCP23017 pin | Asteria signal |
|---|---|
| GPA0 | RA ENABLE |
| GPA1 | DEC ENABLE |
| GPA2 | Status LED |
| GPA3 | Joystick switch |
| GPA4-GPA7 | Reserved |
| GPB0-GPB7 | Reserved |
