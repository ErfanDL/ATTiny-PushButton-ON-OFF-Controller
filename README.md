# ATTiny13/13A/25/45/85 Push Button ON/OFF Controller
Ultra-Low Power Single push button ON/OFF controller based on ATTiny13/13A/25/45/85 for other MicroController and circuits application.

# **Simple mode features:**
- **Ultra-Low Power 000.2uA (200nA)**
- **Supported uControllers: ATTiny13/13A/25/45/85**
- **Single push button ON/OFF**

# **Advanced mode features:**
- **Ultra-Low Power 000.2uA (200nA)**
- **Supported uControllers: ATTiny13/13A/25/45/85**
- **Hold down button to ON/OFF**
- **External Shut down signal from other Micro-controllers or circuits**

# Note
**Please upload the bootloader first, then upload the code.**

# Arduino Chip SETUP

- **Use ATTinyCore for ATTiny25/45/85**: https://github.com/SpenceKonde/ATTinyCore
- **Use MicroCore for ATTiny13/13A**: https://github.com/MCUdude/MicroCore
-----------------------------------
**Arduino setup for ATTiny13/13A**:
- BOD: BOD Disabled
- Bootloader: No bootloader
- Clock: 128 KHz internal osc
- EEPROM: EEPROM not retained
  
![13](https://github.com/ErfanDL/ATTiny13-25-45-85-Push-Button-ON-OFF-Controller/assets/14868771/aa469578-f8b8-413d-8ca0-f5eb798edafd)

-----------------------------------

**Arduino setup for ATTiny25/45/85**:
- Board: "ATtiny25/45/85 (No bootloader)"
- B.O.D. Level (Only set on bootload): "B.O.D. Disabled (saves power)"
- Chip: "ATtiny45"
- Clock Source (Only set on bootload): "128 kHz (internal WDT)"
- Save EEPROM (only set on bootload): "EEPROM not retained"
- LTO (1.6.11+ only): "Disabled"
- millis()/micros(): "Disabled (saves flash)"
- Timer 1 Clock: "CPU (CPU frequency)"

![Screenshot (388)](https://github.com/ErfanDL/ATTiny-PushButton-ON-OFF-Controller/assets/14868771/983342e7-4573-4d75-a0a6-010a4352d4c1)

-----------------------------------

# Simple mode - Wiring and circuit

![butt_bbk](https://github.com/ErfanDL/ATTiny13-25-45-85-Push-Button-ON-OFF-Controller/assets/14868771/9f82f194-fcc3-4068-8632-16992e51a03b)

# Simple mode - Example circuit for Arduino UNO ON/OFF button

![ex](https://github.com/ErfanDL/ATTiny13-25-45-85-Push-Button-ON-OFF-Controller/assets/14868771/c2acebcc-5fa2-4f36-89d9-0771c0f4e2ba)

-----------------------------------

# Advanced mode - Wiring and circuit

![adv1](https://github.com/ErfanDL/ATTiny-PushButton-ON-OFF-Controller/assets/14868771/3933d1f6-1a7d-400c-b7e0-58f698196099)

# Advanced mode - Example circuit for Arduino UNO ON/OFF button

![adv2](https://github.com/ErfanDL/ATTiny-PushButton-ON-OFF-Controller/assets/14868771/97cbc63a-156e-4ba3-a479-e1b94d6d2f2d)

-----------------------------------

# Misc

If you like my work and want to support me, you can send me a donation via crypto:

Ethereum: 0x283D333C14500dDB93aEE219D2AC1ab3a95ADd5E

Tether USDT (TRC20): TPTeQGyVVjK7yk3jXCqXeDZto38jWVU4v8
