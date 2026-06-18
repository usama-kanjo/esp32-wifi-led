# 🔥 ESP32 LED WiFi Kontrol

ESP32 ile kendi WiFi ağını oluşturup, telefondan LED kontrolü.

## 🚀 Özellikler

- **WiFi Access Point** — Kendi ağını kurar
- **Captive Portal** — Telefona otomatik sayfa açtırır
- **Web Arayüzü** — HTML/CSS ile modern görünüm
- **LED Kontrolü** — Aç/Kapa butonları

## 🛠️ Donanım

| Bileşen | Model |
|---------|-------|
| Mikrodenetleyici | ESP32-DevKit |
| LED | Dahili GPIO2 |

## 📁 Proje Yapısı

src/
├── main.cpp              # Ana program
├── wifi_manager.cpp/h    # WiFi yönetimi
├── web_server.cpp/h      # HTTP sunucusu
├── html_page.cpp/h       # HTML sayfası
├── dns_captive.cpp/h     # DNS portal
└── pin_config.h          # Pin tanımlamaları
plain


## ⚡ Kurulum

### Gereksinimler

- Debian 13 / KDE
- Python 3 + venv
- Neovim (LazyVim) — Opsiyonel

### PlatformIO Kurulumu

```bash
# Sanal ortam
python3 -m venv ~/platformio/venv
source ~/platformio/venv/bin/activate

# PlatformIO
pip install platformio

# Projeyi derle
cd ~/Arduino/platformio
pio run

# ESP32'ye yükle
pio run -t upload

# Seri monitör
pio device monitor

📡 Kullanım

    ESP32'yi USB ile bağla
    pio run -t upload ile yükle
    Telefondan WiFi'ye bağlan:
        SSID: ESP32_WiFi
        Şifre: 12345678
    Tarayıcı otomatik açılır (veya 192.168.4.1 gir)

🖥️ Ekran Görüntüsü
plain

┌─────────────────────────┐
│    🔥 ESP32 LED Kontrol  │
│                         │
│    LED: AÇIK 💡         │
│                         │
│  ┌────────┐ ┌────────┐  │
│  │ LED AÇ │ │LED KAPAT│  │
│  └────────┘ └────────┘  │
└─────────────────────────┘

🔧 Geliştirme
Table
Komut	Açıklama
pio run	Derle
pio run -t upload	Yükle
pio run -t clean	Temizle
pio device monitor	Seri port izle
📝 Notlar

    İlk derleme ~300 MB araç indirir (bir kerelik)
    99-platformio-udev.rules kurulumu için: PlatformIO Docs

📜 Lisans
MIT
EOF
