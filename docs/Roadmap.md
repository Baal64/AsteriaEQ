## Hors périmètre V1

Les fonctionnalités suivantes sont prévues dans l’architecture mais ne seront pas développées en V1 :

- GoTo
- PEC
- UART TMC2209
- compensation du backlash
- communication PC
- Wi-Fi / Bluetooth
- scheduler avancé

## M1 - Development Infrastructure

────────────────────────────────
✅ GitHub
✅ Documentation
✅ CI Documentation
□ PlatformIO
□ CI Build
□ CI Static Analysis

## M2 - Core Architecture

──────────────────────
□ Interfaces Hardware
□ MotionCommand
□ Axis
□ MotionController
□ Mount
□ StateMachine

## M3 - Hardware Layer

───────────────────
□ TMC2209
□ AS5048A
□ MCP23017
□ Joystick
□ LED

## M4 - First Motion

─────────────────
□ Driver Enable
□ STEP Generation
□ RA rotation
□ DEC rotation
□ Speed selection

## M5 - Astronomical Features

──────────────────────────
□ Sidereal
□ Solar
□ Lunar
□ Home
□ Park
□ ST4

## M6 - Validation

────────────────
□ 1 hour tracking
□ Position verification
□ Error logging
