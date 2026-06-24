#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>

void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  uint8_t dataDiterima = incomingData[0];
  
  if (dataDiterima == 1) {
    Serial.print('1'); // Kirim karakter '1' ke STM32 via RX/TX
  } else {
    Serial.print('0'); // Kirim karakter '0' ke STM32 via RX/TX
  }
}
 
void setup() {
  // Baud rate harus disamakan dengan baud rate Serial di STM32 yang membaca ESP
  Serial.begin(115200); 

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {
    return;
  }
  
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {}