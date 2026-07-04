ESP32 + A7670C LTE Module

A complete getting-started guide for interfacing an ESP32 with the SIMCom A7670C LTE module using a proper 1.8V ↔ 3.3V logic level converter.

Features
UART communication
Power supply design
Logic level shifting
Internet connection
Ping test
HTTP
MQTT
GPS
SMS
Voice
Troubleshooting


| Item                | Description |
| ------------------- | ----------- |
| ESP32 DevKit        | ESP32-WROOM |
| LTE Module          | A7670C-LASC |
| Logic Level Shifter | 1.8V ↔ 3.3V |
| Buck Converter      | 4V / 3A     |
| Capacitor           | 2200µF      |
| SIM                 | Airtel 4G   |


ESP32                 Level Shifter              A7670C

GPIO17 (TX2) -------> HV1 -> LV1 ------------> RXD

GPIO16 (RX2) <------- HV2 <- LV2 <------------ TXD

3.3V ----------------> HV

1.8V(VDD_OUT) -------> LV

GND -----------------> GND -------------------> GND

Buck 4V -------------------------------------> VCC


Power Requirements

Explain:

3.4V–4.2V
2A peak current
2200µF capacitor
Common ground

