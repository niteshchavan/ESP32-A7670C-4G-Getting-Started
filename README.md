# ESP32 + A7670C LTE Getting Started

> A complete beginner-to-advanced guide for interfacing an ESP32 with the SIMCom A7670C LTE Cat-1 module.

![Platform](https://img.shields.io/badge/Platform-ESP32-blue)
![Modem](https://img.shields.io/badge/Modem-SIMCom_A7670C-green)
![Arduino](https://img.shields.io/badge/Framework-Arduino-orange)
![License](https://img.shields.io/badge/License-MIT-red)

---

# Features

- ESP32 ↔ A7670C UART Communication
- Proper 1.8V ↔ 3.3V Logic Level Conversion
- Stable Power Supply Design
- LTE Network Registration
- Internet Connectivity
- ICMP Ping Test
- HTTP/HTTPS Examples
- MQTT Examples
- SMS Examples
- GPS (GNSS) Examples
- Voice Call Examples
- Troubleshooting Guide

---

# Hardware Used

| Component | Description |
|------------|------------|
| ESP32 | ESP32 DevKit V1 |
| LTE Module | SIMCom A7670C-LASC |
| Logic Level Shifter | 1.8V ↔ 3.3V |
| Buck Converter | 4V 3A |
| Capacitor | 2200µF Low ESR |
| SIM Card | Airtel 4G |

---

# Hardware Connection

```
                    +----------------------+
                    |       ESP32          |
                    |                      |
GPIO17 (TX2) ------>|                      |
GPIO16 (RX2) <------|                      |
3.3V -------------->|                      |
GND --------------->|                      |
                    +----------+-----------+
                               |
                               |
                               |
                 +-------------+--------------+
                 |   Logic Level Shifter      |
                 |                            |
                 | HV = 3.3V                  |
                 | LV = 1.8V (VDD_OUT)        |
                 | GND                        |
                 +------+--------------+------+
                        |              |
                        |              |
                        |              |
             +----------+--------------+-----------+
             |             A7670C                  |
             |                                     |
             | RXD                                |
             | TXD                                |
             | VCC (4.0V)                         |
             | GND                               |
             | VDD_OUT (1.8V)                    |
             +-----------------------------------+

```

---

# Power Supply

The A7670C requires:

- Voltage : **3.4V ~ 4.2V**
- Recommended : **4.0V**
- Peak Current : **2A to 3A**
- Capacitor : **2200µF**

Do **NOT** power the module directly from the ESP32.

---

# Logic Level Conversion

The UART on the A7670C operates at **1.8V logic**.

Use a proper logic level converter.

| Logic Level Shifter | Voltage |
|---------------------|---------|
| HV | ESP32 3.3V |
| LV | A7670C VDD_OUT (1.8V) |
| GND | Common Ground |

---

# Common Ground

All grounds **must** be connected together.

- ESP32 GND
- A7670C GND
- Buck Converter GND
- Logic Level Shifter GND

---

# UART Pins

| ESP32 | A7670C |
|--------|---------|
| GPIO17 (TX2) | RXD |
| GPIO16 (RX2) | TXD |

Default UART Baud Rate

```
115200
```

---

# First Boot

Wait until the modem finishes booting.

Expected output:

```
PB DONE
```

Only after **PB DONE** should AT commands be sent.

---

# AT Command Test

```
AT
```

Response

```
OK
```

Disable Echo

```
ATE0
```

---

# Check Modem Information

```
ATI
```

Example

```
Manufacturer: INCORPORATED
Model: A7670C-LASC
Revision: A7670M6_V1.11.1
```

---

# Check SIM Status

```
AT+CPIN?
```

Response

```
+CPIN: READY
```

---

# Check Signal Strength

```
AT+CSQ
```

Example

```
+CSQ: 20,99
```

---

# Check Network Registration

```
AT+CREG?
```

Expected

```
+CREG: 0,1
```

LTE Registration

```
AT+CEREG?
```

Expected

```
+CEREG: 0,1
```

---

# Configure Airtel APN

```
AT+CGDCONT=1,"IP","airtelgprs.com"
```

Activate PDP Context

```
AT+CGACT=1,1
```

---

# Check Internet

```
AT+CGATT?
```

Expected

```
+CGATT: 1
```

Get IP Address

```
AT+CGPADDR=1
```

Example

```
+CGPADDR: 10.xxx.xxx.xxx
```

---

# Ping Test

Command

```
AT+CPING="8.8.8.8",1,4,32,3000,10000,64
```

Example

```
+CPING: 1,8.8.8.8,60,130,116
+CPING: 1,8.8.8.8,60,70,116
+CPING: 1,8.8.8.8,60,50,116
+CPING: 1,8.8.8.8,60,450,116

+CPING: 3,4,4,0,50,450,175
```

Meaning

- 4 Packets Sent
- 4 Packets Received
- 0 Packet Loss
- Average Ping ≈ 175 ms

---

# Folder Structure

```
ESP32-A7670C-Getting-Started/
│
├── Arduino/
│   ├── UART_Test/
│   ├── AT_Terminal/
│   ├── Ping_Test/
│   ├── HTTP/
│   ├── HTTPS/
│   ├── MQTT/
│   ├── SMS/
│   ├── GPS/
│   └── Voice/
│
├── docs/
│   ├── Hardware.md
│   ├── Wiring.md
│   ├── Power.md
│   ├── AT_Commands.md
│   └── Troubleshooting.md
│
├── images/
│
├── datasheets/
│
└── README.md
```

---

# Common Problems

## Only "AT" is echoed

Cause

- Echo enabled
- Wrong line ending
- Command sent before boot completed

Solution

```
ATE0
```

Wait until

```
PB DONE
```

---

## No Response

Check

- TX/RX wiring
- Common Ground
- UART Baud Rate
- Power Supply

---

## ERROR on Every Command

Verify

- UART is 115200
- Modem boot completed
- Correct logic level conversion

---

## No IP Address

Check

```
AT+CGATT?
```

Configure APN

```
AT+CGDCONT=1,"IP","airtelgprs.com"
```

Activate PDP

```
AT+CGACT=1,1
```

---

# Future Examples

- HTTP GET
- HTTP POST
- HTTPS
- MQTT
- SSL
- FTP
- TCP Client
- TCP Server
- UDP
- SMS
- Voice Call
- GNSS GPS
- OTA Update
- Speed Test

---

# License

MIT License

---

# Contributions

Pull requests are welcome.

If you find improvements or additional AT command examples, feel free to contribute.
