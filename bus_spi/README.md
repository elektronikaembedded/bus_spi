# BUS SPI (SPI Bus Abstraction)

A lightweight and portable SPI abstraction layer for embedded systems.

This module provides a clean interface to separate SPI communication from
device drivers like ST7735, W25Qxx, PN532, etc.

---

## ✨ Features

* Works with any MCU or SDK (STM32, ESP-IDF, Nordic, etc.)
* Optional OSAL integration (locking, delays)
* Supports:

  * Blocking SPI
  * DMA / Async (platform dependent)
* Minimal API
* No dynamic memory required
* Fully portable design

---

## 📂 Project Structure

```
bus_spi/
├── include/
│   └── bus_spi.h
├── src/
│   └── bus_spi.c
├── template/
│   └── bus_spi_port.c.example
```

---

## 🚀 Getting Started

### 1. Add module to your project

```
Modules/
└── bus_spi/
```

---

### 2. Create platform implementation

Copy template:

```
cp template/bus_spi_port.c.example port/bus_spi/bus_spi_stm32.c
```

Update it using your platform SDK.

---

### 3. Add to build

Include:

* `include/bus_spi.h`
* `src/bus_spi.c`
* `port/bus_spi/bus_spi_<platform>.c`

---

## 🧩 Usage Example

```c
#include "bus_spi.h"

static bus_spi_t spi_bus;

void app_init(void)
{
    bus_spi_init(&spi_bus, get_bus_spi_ops());

    uint8_t data[] = {0xAA, 0x55};

    spi_bus.ops->write(&spi_bus, data, sizeof(data));
}
```

---

## 🔗 Using with OSAL (Optional)

If you are using OSAL:

```c
spi_bus.osal = &osal;
```

Then the SPI layer can automatically handle:

* Lock / Unlock
* Thread safety
* ISR awareness (if implemented)

If not needed:

```c
spi_bus.osal = NULL;
```

---

## 🧠 API Overview

### Initialize

```
bus_spi_init(&bus, &ops);
```

---

### Write Data

```
bus.ops->write(&bus, tx, len);
```

---

### Transfer (Full Duplex)

```
bus.ops->transfer(&bus, tx, rx, len);
```

---

### Check Busy

```
if (bus.ops->is_busy(&bus))
{
    // SPI busy
}
```

---

## ⚙️ Design Notes

* Uses function pointer table (`bus_spi_ops_t`)
* Platform-specific code stays in `port/`
* Drivers remain completely platform-independent
* OSAL is optional (recommended for RTOS systems)

---

## 🔧 Porting Guide

To support a new platform:

1. Copy template file
2. Implement:

   * init / deinit
   * write / transfer
   * is_busy
3. Return your `bus_spi_ops_t`

---

## 📌 Notes

* Chip Select (CS) is NOT handled by this module
  → Driver must control CS

* `transfer()` is optional

* `is_busy()` can be stubbed if not needed

---

## 📜 License

MIT License
