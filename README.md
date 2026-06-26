# Robot Sumo STM32

## Gambaran Umum

Program ini merupakan firmware robot sumo berbasis STM32 yang menggunakan arsitektur **State Machine**.

Robot memiliki tiga state utama:

* SEARCH
* ATTACK
* ESCAPE

Perpindahan state dilakukan otomatis berdasarkan data sensor TOF dan sensor garis (IR).

---

# Struktur Project

## config.h

Berisi seluruh konfigurasi robot.

Digunakan untuk menyimpan:

* mapping pin
* alamat TOF
* threshold sensor
* parameter strategi
* timeout
* konfigurasi debugging
* konfigurasi simulasi

Apabila terjadi perubahan hardware, file ini yang pertama kali perlu diubah.

---

## motor.h / motor.cpp

Driver motor TB6612.

Fungsi utama:

* inisialisasi PWM
* mengatur arah putaran
* mengatur kecepatan motor kiri dan kanan

Fungsi yang paling sering digunakan:

```cpp
motor.drive(leftPWM, rightPWM);
```

Nilai:

* positif = maju
* negatif = mundur

---

## tof.h / tof.cpp

Driver seluruh sensor VL53L0X.

Fitur:

* inisialisasi multi sensor menggunakan XSHUT
* penggantian alamat I2C
* pembacaan continuous mode
* median filter
* threshold minimum
* threshold maksimum

Data sensor dapat diperoleh menggunakan

```cpp
tof.getDistance(FRONT1);
tof.getDistance(FRONT2);
tof.getDistance(LEFT);
tof.getDistance(RIGHT);
```

Apabila tidak ada objek maka fungsi mengembalikan nilai 0.

---

## strategy.h / strategy.cpp

Berisi seluruh strategi robot.

Terdapat dua kelompok fungsi.

### Search

Digunakan saat robot belum menemukan lawan.

Contoh:

```cpp
searchBasic()

searchPatrol()

searchSweep()

searchAggressive()
```

---

### Attack

Digunakan saat robot telah menemukan lawan.

Contoh:

```cpp
attackTracking()

attackAggressive()
```

Apabila ingin menambah strategi baru, cukup menambahkan fungsi baru pada file ini lalu memanggilnya dari State Machine.

---

## stateMachine.h / stateMachine.cpp

Merupakan inti seluruh program.

Seluruh keputusan robot dibuat pada file ini.

Fungsi utamanya:

* membaca sensor
* menentukan state
* memanggil strategi
* menghindari garis arena
* mengingat arah lawan terakhir

Hampir seluruh logika robot berada di file ini.

---

# Cara Kerja Robot

Robot selalu berada pada salah satu state berikut.

```
SEARCH
   │
   │ musuh ditemukan
   ▼
ATTACK
   │
   │ musuh hilang
   ▼
SEARCH

Semua state
     │
     │ sensor garis aktif
     ▼
ESCAPE
     │
     ▼
SEARCH
```

Sensor garis memiliki prioritas tertinggi.

---

# Logika SEARCH

Saat tidak ada lawan di depan robot, state akan menjadi SEARCH.

Robot menjalankan salah satu pola pencarian sesuai DIP Switch.

Apabila sebelumnya lawan terlihat kemudian hilang, robot tidak langsung kembali ke pola pencarian.

Robot akan mengingat arah terakhir lawan menggunakan

```
lastSeenDirection
```

selama

```
LAST_SEEN_TIMEOUT
```

Apabila waktu tersebut habis dan lawan masih belum ditemukan maka robot kembali menjalankan pola search normal.

TOF samping digunakan sebagai bantuan pencarian.

Apabila TOF kiri mendeteksi lawan maka robot mengingat bahwa lawan berada di sisi kiri.

Begitu juga sebaliknya.

---

# Logika ATTACK

State ATTACK aktif apabila

```
nearestDistance < ATTACK_DISTANCE
```

Pada state ini:

* TOF depan kiri dan kanan menjadi sensor utama.
* Robot akan terus mengoreksi arah dorongan.

Contoh:

Front Left > Front Right

↓

Robot sedikit membelok ke kiri.

Sebaliknya apabila kanan lebih dekat maka robot membelok ke kanan.

Tujuannya agar dorongan tetap berada di tengah lawan.

---

# Logika ESCAPE

ESCAPE memiliki prioritas paling tinggi.

Urutan kerjanya:

1. sensor garis aktif
2. robot berhenti menyerang
3. robot mundur (atau maju apabila sensor belakang aktif)
4. robot berputar
5. kembali SEARCH

Parameter yang dapat dituning:

```
ESCAPE_BACK_TIME

ESCAPE_TURN_TIME
```

---

# Strategi

## Strategy 1

Basic Search

Robot hanya berputar di tempat hingga menemukan lawan.

Attack menggunakan tracking biasa.

---

## Strategy 2

Patrol Search

Robot bergerak membentuk lengkungan kiri-kanan.

Lebih cepat menemukan lawan dibanding Strategy 1.

Attack menggunakan tracking biasa.

---

## Strategy 3

Sweep Search

Robot bergerak membentuk pola menyerupai huruf S.

TOF samping membantu mengarahkan robot menuju posisi terakhir lawan.

Attack menggunakan tracking biasa.

---

## Strategy 4

Aggressive

Robot lebih sering maju.

Saat menyerang motor luar diberikan PWM maksimum sehingga robot lebih cepat membelok menuju lawan.

---

# Parameter yang Perlu Dituning

Kemungkinan besar parameter berikut perlu disesuaikan saat robot sudah siap digunakan.

```
ATTACK_DISTANCE

SIDE_DETECT_DISTANCE

LAST_SEEN_TIMEOUT

ESCAPE_BACK_TIME

ESCAPE_TURN_TIME
```

Selain itu hampir seluruh nilai PWM pada strategy juga kemungkinan perlu diubah sesuai karakter robot.

---

# Library yang Digunakan

Program menggunakan beberapa library berikut.

* Wire

  * komunikasi I2C

* VL53L0X

  * driver sensor TOF

* Arduino STM32 Core

  * GPIO
  * PWM
  * UART
  * Timer
  * millis()

---

# Cara Menambah Strategi Baru

1. Tambahkan fungsi baru pada `strategy.cpp`.

2. Tambahkan deklarasinya pada `strategy.h`.

3. Tambahkan enum Strategy baru apabila diperlukan.

4. Panggil fungsi tersebut pada

```
Robot::search()

atau

Robot::attack()
```

5. Atur pemilihannya melalui DIP Switch atau manual strategy.

---
