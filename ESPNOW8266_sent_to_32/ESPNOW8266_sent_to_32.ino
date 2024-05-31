
#include <ESP8266WiFi.h>
#include <espnow.h>
uint8_t broadcastAddress[] = {0xC8, 0x2E, 0x18, 0x26, 0xB9, 0xF8}; // esp32 MAC address

typedef struct struct_message {
  char a[20];
  int b;
  float c;
  bool d;
} struct_message;

struct_message SentData;
struct_message RecData;

esp_now_peer_info_t peerInfo;

// Callback when data is sent
void DataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

// Callback when data is received
void OnRecData(const esp_now_recv_info_t *info, const uint8_t *incomingData, int len) {
  memcpy(&RecData, incomingData, sizeof(RecData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Char: ");
  Serial.println(RecData.a);
  Serial.print("Int: ");
  Serial.println(RecData.b);
  Serial.print("Float: ");
  Serial.println(RecData.c);
  Serial.print("Bool: ");
  Serial.println(RecData.d);
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_send_cb(DataSent);

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

  esp_now_register_recv_cb(OnRecData);
}

void loop() {
  SendingData();
}

void SendingData() {
  strcpy(SentData.a, "FROM ESP 32");
  SentData.b = random(1, 20);
  SentData.c = 1.2;
  SentData.d = false;

  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&SentData, sizeof(SentData));
  if (result == ESP_OK) {
    Serial.println("Message sent successfully...");
  } else {
    Serial.println("Error sending the data, check your code!!!");
  }
  delay(3000);
}
