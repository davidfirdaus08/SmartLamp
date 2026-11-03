# 💡 DF Smart Lamp

Wi-Fi smart lamp controller using ESP8266 and a relay, with a neumorphic web interface served directly from the board. No internet required.

![Platform](https://img.shields.io/badge/platform-ESP8266-blue)
![Language](https://img.shields.io/badge/language-C%2B%2B%20%7C%20HTML%20%7C%20CSS%20%7C%20JS-orange)
![Mode](https://img.shields.io/badge/mode-Access%20Point-green)

## ✨ Features

- **Control from any browser**: turn the lamp on/off from your phone or laptop, no app needed
- **No internet or router needed**: the ESP8266 creates its own Wi-Fi network (Access Point mode)
- **Neumorphic UI**: soft-shadow design with an animated glowing lamp icon
- **Instant feedback**: the UI updates immediately when you tap, while the command is sent in the background
- **State sync on reload**: the page always shows the real lamp state from the board
- **Standalone preview page**: includes dark mode toggle and time-based greeting (Pagi, Siang, Sore, Malam) for UI development

## 🏗️ How It Works

```
[Phone / Laptop Browser] <--- Wi-Fi (AP) ---> [ESP8266 Web Server] ---> [Relay] ---> [Lamp]
```

The ESP8266 starts its own Wi-Fi network and runs a small web server. Opening the page serves the control UI. Tapping the button sends a request to `/on` or `/off`, and the board switches the relay accordingly.

| Endpoint | Action |
|----------|--------|
| `/` | Control page |
| `/on` | Turn the lamp on |
| `/off` | Turn the lamp off |

## 🧰 Hardware Requirements

- ESP8266 board (NodeMCU / Wemos D1 Mini)
- 1-channel relay module
- Lamp with fitting and cable
- Jumper wires
- 5V power supply or USB cable

## 🔌 Wiring

| ESP8266 | Relay Module |
|---------|--------------|
| D1 | IN |
| 3V3 / 5V | VCC |
| GND | GND |

The lamp's live wire goes through the relay's **COM** and **NO** terminals.

> ⚠️ **Warning:** This project involves mains voltage (AC). Make sure everything is unplugged while wiring, use proper insulation, and ask someone experienced if you are not confident.

> 📝 The code uses an **active-low** relay (`LOW` = on, `HIGH` = off). If your relay is active-high, swap the two values in `handleOn()` and `handleOff()`.

## 🚀 Getting Started

### 1. Clone the repository

```bash
git clone https://github.com/davidfirdaus08/SmartLamp.git
cd SmartLamp
```

### 2. Prepare Arduino IDE

1. Add the ESP8266 board package via **Boards Manager** (`esp8266` by ESP8266 Community)
2. Select your board (e.g. *NodeMCU 1.0 (ESP-12E Module)*)

### 3. Configure Wi-Fi (optional)

Edit these lines in the sketch:

```cpp
const char* ssid = "DF SmartLamp";
const char* password = "12345678";
```

> 🔒 Change the default password before real use. The password must be at least 8 characters.

### 4. Upload

Connect the board via USB, select the correct port, and click **Upload**.

## 📖 Usage

1. Power on the ESP8266
2. On your phone, connect to the Wi-Fi network **DF SmartLamp**
3. Open **http://192.168.4.1** in your browser
4. Tap **NYALAKAN** to turn on, **MATIKAN** to turn off

## 📁 Project Structure

```
SmartLamp/
├── SmartLamp.ino     # ESP8266 firmware + embedded web UI
├── preview/
│   └── index.html    # Standalone UI preview (dark mode, greeting, social links)
└── README.md
```

## 🗺️ Roadmap

- [ ] Station mode (connect to home Wi-Fi)
- [ ] Auto-off timer
- [ ] Dark mode on the embedded UI
- [ ] Multi-relay support
- [ ] Password-protected control page

## 🎨 UI Preview

Open `preview/index.html` directly in a browser to test the interface without hardware. Commands are simulated in this mode.

## 🤝 Contributing

Suggestions and pull requests are welcome. Fork the repo, create a branch, and open a PR.

## 👤 Author

**David Firdaus**
- GitHub: [@davidfirdaus08](https://github.com/davidfirdaus08)
- Instagram: [@davidfirdaus_08](https://instagram.com/davidfirdaus_08)
- YouTube: [@virlanhakuto](https://youtube.com/@virlanhakuto)
