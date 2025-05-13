# bleak-dev – BLE Central with Bleak (Python)

This repo is a starting point for building a **BLE Central Application** on **Ubuntu** using **Python** and **Bleak**. It will interface with an **nRF52810** running BLE services, allowing us to discover and interact with BLE peripherals.

---

## 🔧 Requirements

- **Python 3.7+**
- **Bleak**: Install via `pip install bleak`
- **Ubuntu** (or any Linux distro with Bluetooth 4.0+ support)
- **BlueZ**: BLE stack for Linux (install with `sudo apt install bluez`)

---

## 🚀 Getting Started

1. **Clone the repo**:
    ```bash
    git clone https://github.com/your-user/bleak-dev.git
    cd bleak-dev
    ```

2. **Install dependencies**:
    ```bash
    pip install bleak
    ```

3. **Run the BLE scan script**:
    ```python
    py_script.py
    ```

    This script will scan for nearby BLE devices and print details about any device named `BLE-BEACON`.

---


## 📖 Reference

- Flash the **nRF52810** with appropriate firmware from the [`nrf-fw-dev`](https://github.com/your-user/nrf-fw-dev) repo.
- See:
  - **#2** – BLE Peripheral functionality on nRF52810
  - **#3** – BLE Central using Bleak on Ubuntu

---

## ✍️ Author

**Sumit** – Embedded Engineer | BLE Enthusiast  
Feel free to reach out with any questions or suggestions.

---

## 📜 License

MIT License
