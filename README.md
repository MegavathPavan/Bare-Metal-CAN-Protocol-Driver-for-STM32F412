# 🛠️ CAN Protocol Driver (Bare-Metal C) for STM32F4

A **bare-metal** implementation of the **Controller Area Network (CAN)** protocol for STM32F4 microcontrollers, built completely from scratch without using HAL or external libraries. This driver demonstrates register-level control, message-based data handling, and core protocol features like priority-based arbitration and robust error handling.

---

## 📚 About CAN Protocol

The **Controller Area Network (CAN)** protocol is a serial, half-duplex, asynchronous communication protocol originally developed by Bosch for automotive applications. It supports **multi-master** communication without a central controller and ensures **deterministic**, **priority-based**, and **robust** data transfer over a two-wire bus (CANH and CANL).

### 🔑 Key Features:
- **Message-based** communication (not address-based)
- **Non-destructive arbitration** using message IDs
- **Broadcast-type** bus with multi-node support
- **High reliability** in noisy environments
- **Error detection** via CRC, ACK, and bit monitoring

---

## 🔧 CAN Data Transmission Flow

1. **Host** (MCU): Controls what to send/receive
2. **CAN Controller**: Manages protocol-level message handling (initiation, error checking, arbitration)
3. **CAN Transceiver**: Converts logic-level signals to differential voltages for CANH/CANL lines

![Can Network Diagram](https://github.com/MegavathPavan/Bare-Metal-CAN-Protocol-Driver-for-STM32F412/blob/main/CAN%20network%20diagram.png)

---

## 🧩 CAN Frame Structure

![Can Frame Format](https://github.com/MegavathPavan/Bare-Metal-CAN-Protocol-Driver-for-STM32F412/blob/main/CAN%20Frame%20Format.png)

| Field              | Description                                                         |
|-------------------|---------------------------------------------------------------------|
| **SOF**           | Start of Frame (1 bit)                                              |
| **Identifier**    | Message ID (11 or 29 bits) determines priority                      |
| **RTR**           | Remote Transmission Request: 0 = Data Frame, 1 = Remote Frame       |
| **Control Bits**  | Frame info: DLC, IDE, Reserved bits                                 |
| **DLC**           | Data Length Code (0–8)                                              |
| **Data**          | Payload (0 to 8 bytes)                                              |
| **CRC**           | Cyclic Redundancy Check for error detection                        |
| **ACK**           | Acknowledgment bits from receiving nodes                            |
| **EOF**           | End of Frame (7 bits)                                               |

---


## 🧠 Functional Overview

### `can.h`
- `typedef struct CAN_Message`: Encapsulates ID, data, and length
- `CAN_Init()`: Initializes CAN1 peripheral registers
- `CAN_Send(CAN_Message *msg)`: Sends a CAN frame
- `CAN_Receive(CAN_Message *msg)`: Receives a CAN frame from FIFO 0

---

### `can.c`

- **CAN_Init**
  - Enables RCC clock for CAN
  - Configures Time-Triggered Comm, Sleep/Init Modes
  - Sets Bit Timing Register (BTR) for baud rate
  - Enables normal operation mode

- **CAN_Send**
  - Waits for empty mailbox
  - Sets message ID, data length (DLC), and payload
  - Triggers transmission and confirms with debug print

- **CAN_Receive**
  - Waits for RX message in FIFO 0
  - Extracts ID, data, and length
  - Releases FIFO and prints debug info

---

### `main.c`

- Initializes CAN peripheral
- Creates a transmit message (`txMsg`) and a receive buffer (`rxMsg`)
- Sends and receives messages in a loop
- Toggles LED on `GPIOA Pin 5` upon receiving specific message
- Uses UART for debug print statements

---


## ⚙️ Protocol Comparison

| Feature       | CAN                         | UART             | SPI              | I2C                |
|---------------|------------------------------|------------------|------------------|--------------------|
| Bus Type      | Multi-Master (Broadcast)     | Point-to-Point   | Master-Slave     | Master-Slave       |
| Error Handling| Strong (CRC, ACK)            | Minimal          | Minimal          | Moderate           |
| Topology      | Multi-node                   | 1-to-1           | 1-Master N-Slave | 1-Master N-Slave   |
| Distance      | Long (Robust Differential)   | Short            | Short            | Short              |
| Use Case      | Automotive, Industrial, RTOS | Basic Serial I/O | Sensors, Flash   | On-board IC comm.  |

---

## 🌍 Real-World Applications

- 🚗 **Automotive Systems** (Engine control units, ABS, airbags)
- 🏭 **Industrial Automation** (Factory sensors, PLCs)
- ✈️ **Aerospace Systems** (Avionics data buses)
- 🏥 **Medical Devices** (Sensor data in critical systems)
- 🌡️ **Smart Agriculture** (Distributed sensor networks)

---

## 🔗 References

- [STM32 Reference Manual (RM0402) Chapter 28](https://www.st.com/resource/en/reference_manual/rm0402-stm32f412-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)

---

## 🧪 Future Improvements

- ⏱️ Interrupt-based receive handling
- 🔍 CAN message filtering support
- 🧾 Extended Frame ID (29-bit) support
- 🔗 Integration with real CAN tools (e.g., PCAN, CANalyzer)

---

## 📜 License

MIT License – free to use, modify, and share. Credit appreciated 🙌

---

> 🚀 This project demonstrates low-level MCU communication mastery. A solid addition to any embedded systems portfolio!


