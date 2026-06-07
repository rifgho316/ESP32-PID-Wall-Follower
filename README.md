# ESP32-PID-Wall-Follower

# Autonomous Wall-Following Robot with PID Control

Proyek ini berisi kode sumber untuk robot beroda penyusur dinding (*wall-follower*) otonom. Robot ini dirancang untuk berjalan lurus di tengah-tengah lorong atau di antara dua dinding menggunakan sistem kontrol **PID (Proportional-Integral-Derivative)** dan dua buah sensor ultrasonik.

## 🌟 Fitur Utama
* **Kontrol PID Cerdas:** Mengkalkulasi error jarak antara dinding kiri dan kanan untuk menghasilkan pergerakan yang mulus (tidak zig-zag patah-patah).
* **Dual Ultrasonic Sensors:** Pembacaan jarak yang di-filter (Low-Pass Filter) dan di-rata-rata agar lebih kebal terhadap *noise* atau pembacaan palsu.
* **Auto-Deceleration:** Kecepatan robot otomatis melambat saat mendeteksi *error* atau ketidakseimbangan posisi yang besar, mencegah tabrakan dengan dinding.
* **Batas Keamanan Sistem:** Dilengkapi fungsi `constrain` pada nilai integral, kontrol, dan PWM motor agar sistem tidak tidak *out of control*.

## 🛠️ Komponen yang Dibutuhkan
1. Mikrokontroler (ESP32/Arduino) - *Pin map diatur untuk ESP32*
2. 2x Sensor Ultrasonik (contoh: HC-SR04)
3. 1x Motor Driver (contoh: L298N)
4. 2x Motor DC beserta Roda
5. Baterai / Power Supply
6. Sasis Robot

## 📌 Konfigurasi Pin (Pin Mapping)

| Komponen | Nama Pin | Pin ESP32 | Keterangan |
| :--- | :--- | :--- | :--- |
| **Sensor Kiri** | TRIG | `13` | Output Trigger |
| | ECHO | `12` | Input Echo |
| **Sensor Kanan**| TRIG | `14` | Output Trigger |
| | ECHO | `27` | Input Echo |
| **Motor Kiri** | ENA | `15` | PWM Speed Control |
| | IN1 | `2` | Direction 1 |
| | IN2 | `4` | Direction 2 |
| **Motor Kanan** | ENB | `5` | PWM Speed Control |
| | IN3 | `16` | Direction 3 |
| | IN4 | `17` | Direction 4 |

## ⚙️ Cara Penyesuaian (Tuning PID)
Jika robot berjalan terlalu bergetar atau responsnya kurang cepat, kamu bisa mengubah nilai variabel berikut pada bagian atas kode:
* `Kp = 3.6;`  (Tingkatkan jika respons belok kurang tajam, turunkan jika robot bergetar/zig-zag keras)
* `Ki = 0.0006;` (Menghilangkan error jangka panjang. Biarkan kecil agar tidak *windup*)
* `Kd = 0.28;` (Tingkatkan untuk meredam guncangan berlebih/mengerem belokan)

## 🚀 Cara Penggunaan
1. Rangkai komponen sesuai dengan tabel Konfigurasi Pin di atas.
2. Buka kode ini menggunakan Arduino IDE.
3. Pastikan *board* ESP32 sudah terinstal dan dipilih di Arduino IDE.
4. *Compile* dan *Upload* kode ke mikrokontroler.
5. Tempatkan robot di antara dua dinding, nyalakan, dan lihat bagaimana robot menyeimbangkan posisinya!
