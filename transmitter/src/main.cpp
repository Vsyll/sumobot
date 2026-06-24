#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>

// GANTI DENGAN MAC ADDRESS ESP-01 KAMU NANTI
uint8_t broadcastAddress[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};

const int buttonPin = 4; // Pin D2 di NodeMCU

// Variabel untuk Debounce Non-Blocking (Tanpa Delay)
int buttonState;             
int lastButtonState = HIGH;   
unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 50;    // Jeda debounce 50 ms

bool robotAktif = false;

// Fungsi callback untuk mengetahui status pengiriman data
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Status Pengiriman: ");
  Serial.println(sendStatus == 0 ? "Sukses" : "Gagal");
}
 
void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP); // Mengaktifkan internal pull-up
  
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {
    Serial.println("Gagal inisialisasi ESP-NOW");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}
 
void loop() {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      // Jika tombol ditekan (kondisi LOW)
      if (buttonState == LOW) {
        robotAktif = !robotAktif; // Toggle status aktif (ON/OFF)
        
        uint8_t dataKirim = robotAktif ? 1 : 0;
        esp_now_send(broadcastAddress, &dataKirim, sizeof(dataKirim));
        
        Serial.print("Tombol Ditekan! Sinyal dikirim: ");
        Serial.println(robotAktif ? "START (1)" : "STOP (0)");
      }
    }
  }
  lastButtonState = reading;
}