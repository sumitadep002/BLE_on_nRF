# BLE on nRF52810

A comprehensive project for developing **BLE Peripheral** firmware on the **nRF52810** SoC using **Zephyr RTOS**, along with a **Python-based Central scanner** using the **Bleak** library.

---

## Key Features

- **Event-Driven Architecture**: Fully utilizes Zephyr RTOS work queues and timers for non-blocking hardware control.
- **Custom Hardware Support**: Integrated definitions for the `CUST_HW_V_2` custom board.
- **Sensor Integration**: Real-time battery voltage monitoring via ADC.
- **Dual-Role Development**: Both Firmware (C) and Central Application (Python) are supported.

---

## Project Status

### Completed
- **#7**: Implement event-driven application using Zephyr RTOS (Closed Jun 29, 2025)
- **#5**: BLE-Peripheral: advertise device voltage (Closed Jun 21, 2025)
- **#4**: ADC: Bring up adc (Closed May 25, 2025)
- **#3**: BLE: implement ble central (Closed May 25, 2025)
- **#2**: BLE: advertise device presence (Closed May 25, 2025)
- **#1**: Define custom board for your hardware (Closed May 11, 2025)

### In Progress / Open
- **#10**: Implement a BLE Central node (Open Sep 27, 2025)
- **#9**: Add Scan Request/Response Support with Feature Flags (Open Jul 1, 2025)
- **#8**: Implement BSP Layer to Abstract Hardware (Open Jun 28, 2025)
- **#6**: Optimise RAM (Open Jun 21, 2025)

---

## Requirements

- **nRF Connect SDK (NCS)**: v2.7.0+
- **Python 3.7+**
- **Bleak**: `pip install bleak`
- **BlueZ**: BLE stack for Linux (`sudo apt install bluez`)

---

## Branching Strategy

- `main`: Project overview and stable releases.
- `nrf-fw-dev`: Active development for the nRF52810 firmware.
- `bleak-dev`: Development of the Python-based BLE central application.

---

## Author

**Sumit** – Embedded Engineer | BLE Enthusiast  
Feel free to reach out with any questions or suggestions.

---

## License

MIT License
