# Pemrograman Robotika & IoT Kit iMCLab (ESP32)

Repositori ini berisi kumpulan kode program, eksperimen, dan dokumentasi riset untuk **Kit Robotika iMCLab** berbasis **ESP32**. Proyek ini mencakup kendali tingkat rendah (*low-level*) aktuator motor DC, antarmuka serial Python, hingga integrasi platform **Blynk Cloud** dan **Blynk Air (OTA)**.

---

## 📌 Fitur Utama

- **Kontrol Motor DC & PWM**: Pengaturan arah putar dan kecepatan motor DC menggunakan modul LEDC ESP32 (30 kHz, 8-bit resolution).
- **Integrasi Python**: Komunikasi serial asinkron antara Python Host dan ESP32 untuk pemrosesan tingkat lanjut.
- **Blynk Cloud IoT**: Kontrol sakelar motor, variabel kecepatan (PWM), dan lampu indikator kedip non-blocking secara *real-time* via Web Dashboard & Mobile App.
- **Blynk Air (OTA Update)**: Pembaruan perangkat lunak jarak jauh tanpa kabel (*Over-The-Air*) menggunakan sinkronisasi `BLYNK_FIRMWARE_VERSION`.

---

## 🛠️ Pemetaan Pin (Pinout) ESP32

| Komponen | Pin ESP32 | Tipe Pin | Keterangan |
| :--- | :--- | :--- | :--- |
| **Motor Driver IN1** | `GPIO 27` | Digital Output | Arah Putar Motor |
| **Motor Driver IN2** | `GPIO 26` | Digital Output | Arah Putar Motor |
| **Motor Enable (PWM)** | `GPIO 12` | PWM (LEDC Ch 0) | Pengatur Kecepatan Motor |
| **Blue LED Indicator**| `GPIO 2` | Digital Output | Indikator Kedip Lampu |

---

## 📂 Struktur Modul Eksperimen

- **Modul 1: Pemrograman Basic Robotika**
  - Pengujian logika driver L298N/H-Bridge dan sinyal PWM LEDC ESP32.
- **Modul 2: Pemrograman Robotika Menggunakan Python**
  - Script Python Host (`serial`) untuk mengirimkan instruksi kendali via UART/Serial Terminal.
- **Modul 3: Pemrograman iMCLab Berbasis Blynk**
  - Implementasi `BlynkTimer` untuk eksekusi non-blocking.
  - Konfigurasi Datastream:
    - `V0`: Switch Control (Motor ON/OFF)
    - `V2`: Uptime Telemetry (Detik)
    - `V4`: Speed Control Slider (PWM 0–255)
    - `V5`: Switch Indicator Lamp (LED Blink)
- **Modul 4: Pemrograman Over-The-Air (OTA) Berbasis Blynk Air**
  - Sinkronisasi versi firmware untuk mencegah masalah *Firmware Version Mismatch*.
  - Ekspor compiled binary (`.bin`) dan *shipping* via Blynk.Air Console.

---

## 🚀 Cara Penggunaan

1. **Persiapan Hardware**:
   - Hubungkan ESP32 ke PC melalui kabel USB Data.
   - Pastikan driver motor L298N dan indikator terhubung sesuai tabel pinout.

2. **Setup Arduino IDE**:
   - Install Board Manager **ESP32** by Expressif Systems.
   - Install Library **Blynk** by Volodymyr Shymanskyy.
   - Masukkan kredensial WiFi dan Blynk Auth Token di file `.ino`:
     ```cpp
     #define BLYNK_TEMPLATE_ID   "YOUR_TEMPLATE_ID"
     #define BLYNK_AUTH_TOKEN    "YOUR_AUTH_TOKEN"
     #define BLYNK_FIRMWARE_VERSION "0.0.1"
     ```

3. **Upload & OTA Deployment**:
   - Lakukan upload pertama via Serial Port (USB).
   - Untuk pembaruan versi selanjutnya, lakukan **Export Compiled Binary** (`Ctrl + Alt + S`) di Arduino IDE dan unggah file `.bin` melalui **Blynk Console -> Blynk.Air -> New Shipping**.

---

## 👤 Penulis
**Fauzan Indarwan Zacky**
