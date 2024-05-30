#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

const int receiverPin = 2; // Pin modul KY-022
const int buzzerPin = 33;   // Pin buzzer

IRrecv irrecv(receiverPin);
decode_results results;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  irrecv.enableIRIn(); // Mulai menerima sinyal IR
  Serial.begin(9600);
  pinMode(4,OUTPUT);
  digitalWrite(4, HIGH);
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Menerima sinyal IR berikutnya
    // Jika modul KY-022 mendapatkan input dari KY-008, bunyikan buzzer
    if (results.value == 0xFFA25D) { // Nilai yang diterima dari modul IR tertentu
      digitalWrite(buzzerPin, HIGH);
      delay(1000); // Bunyikan buzzer selama 1 detik
      digitalWrite(buzzerPin, LOW);
    }
  }
}
