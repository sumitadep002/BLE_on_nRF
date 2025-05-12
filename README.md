# nRF52810 BLE Learning – Custom Board with Zephyr

This repository documents my learning journey with **Bluetooth Low Energy (BLE)** development using the **nRF52810** microcontroller and **Zephyr RTOS**.

The project includes:
- Defining and bringing up a **custom board**.
- Validating **LEDs**, **push buttons**, and **serial logging**.
- Implementing **basic BLE functionalities** (advertising, scan response, connection handling).
- Building a **BLE Central application** (Ubuntu-based) using **Bleak**.


## 📌 Target Hardware

- **MCU:** nRF52810  
- **SDK:** nRF Connect SDK v2.7.0  
- **Board:** Custom board (DTS-defined)  
- **Toolchain:** Zephyr-based build system

---

## ✅ Completed Milestones

### 1. Custom Board Bring-up (#1)
- Created custom board definition in `boards/`.
- Brought up serial logging via UART0.
- Added and validated 3 onboard LEDs.
- Added and validated 3 push buttons via DTS and main app.

---

## 🚧 In Progress

### 2. BLE: Basic Functionalities (#2)
- [ ] BLE advertising  
- [ ] Scan response handling  
- [ ] Connection establishment (peripheral role)

### 3. BLE: Central App (Ubuntu-side) (#3)
- [ ] Ubuntu-based BLE Central using **Bleak**
- [ ] Scan, connect, and communicate with peripheral

---

## 📂 Repo Structure (Key Folders)

```

boards/                → Custom board definition
app/src/main.c         → Application logic (LEDs, Buttons, BLE)
app/prj.conf           → Feature flags and configs
CMakeLists.txt         → Build system config

```

---

## 📖 References

- [Zephyr Project Documentation](https://docs.zephyrproject.org/)
- [nRF Connect SDK (v2.7.0)](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/2.7.0/nrf/index.html)
- [Bleak - BLE in Python](https://github.com/hbldh/bleak)

---

## 🔗 Issues Tracker

All work is tracked via GitHub issues and commits referencing:
- `#1` Custom board definition and bring-up
- `#2` BLE peripheral functionalities
- `#3` BLE central-side app using Bleak

---

## ✍️ Author

**Sumit** – Embedded Engineer | IoT Enthusiast  
This repository serves both as a personal learning project and a reference for others working on similar hardware setups.

---