#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>

const int signalPin = 2; // GPIO2 pada ESP-01 -> Hubungkan ke Pin Input STM32

// Fungsi yang otomatis berjalan saat ESP-01 menerima data dari NodeMCU
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  uint8_t dataDiterima = incomingData[0];
  
  if (dataDiterima == 1) {
    digitalWrite(signalPin, HIGH); // Pin jadi 3.3V (Dibaca HIGH oleh STM32)
    Serial.println("Menerima sinyal START -> Pin HIGH");
  } else {
    digitalWrite(signalPin, LOW);  // Pin jadi 0V (Dibaca LOW oleh STM32)
    Serial.println("Menerima sinyal STOP -> Pin LOW");
  }
}
 
void setup() {
  Serial.begin(115200);
  pinMode(signalPin, OUTPUT);
  digitalWrite(signalPin, LOW); // Set default awal robot mati (LOW)

  WiFi.mode(WIFI_STA);

  // Munculkan MAC Address di Serial Monitor saat pertama dinyalakan
  Serial.println();
  Serial.print("MAC Address ESP-01 Kamu: ");
  Serial.println(WiFi.macAddress());

  if (esp_now_init() != 0) {
    Serial.println("Gagal inisialisasi ESP-NOW");
    return;
  }
  
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
  // Loop sengaja dikosongkan karena logika sakelar digerakkan langsung oleh callback OnDataRecv
}