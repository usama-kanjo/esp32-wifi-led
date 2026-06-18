# ESP32 LED WiFi Control

ESP32-based WiFi Access Point with captive portal for LED control from your phone.

## Features

- **WiFi Access Point** — Creates its own network
- **Captive Portal** — Auto-opens page on phone
- **Web Interface** — Modern HTML/CSS UI
- **LED Control** — On/Off buttons

## Hardware

| Component | Model |
|-----------|-------|
| Microcontroller | ESP32-DevKit |
| LED | Built-in GPIO2 |

## Project Structure

src/
├── main.cpp              # Main program
├── wifi_manager.cpp/h    # WiFi management
├── web_server.cpp/h      # HTTP server
├── html_page.cpp/h       # HTML page
├── dns_captive.cpp/h     # DNS portal
└── pin_config.h          # Pin definitions


## Setup

### Requirements

- Debian 13 / KDE
- Python 3 + venv
- Neovim (LazyVim) — Optional

### PlatformIO Installation

```bash
# Virtual environment
python3 -m venv ~/platformio/venv
source ~/platformio/venv/bin/activate

# PlatformIO
pip install platformio

# Build project
cd ~/Arduino/platformio
pio run

# Upload to ESP32
pio run -t upload

# Serial monitor
pio device monitor
```

## Usage

1. Connect ESP32 via USB
2. Upload with `pio run -t upload`
3. Connect your phone to WiFi:
   - SSID: `ESP32_WiFi`
   - Password: `12345678`
4. Browser opens automatically (or go to `192.168.4.1`)

## Screenshot

```
┌─────────────────────────┐
│   🔥 ESP32 LED Control   │
│                         │
│   LED: ON 💡            │
│                         │
│  ┌────────┐ ┌────────┐  │
│  │ LED ON │ │LED OFF │  │
│  └────────┘ └────────┘  │
└─────────────────────────┘
```

## Development

| Command | Description |
|---------|-------------|
| `pio run` | Build |
| `pio run -t upload` | Upload |
| `pio run -t clean` | Clean |
| `pio device monitor` | Serial monitor |

## Notes

- First build downloads ~300 MB of tools (one-time)
- For `99-platformio-udev.rules` setup: PlatformIO Docs

## License

MIT
