#define LASER_PIN 4 // Pin yang terhubung ke output modul KY-008
#define BUZZER_PIN 33 // Pin yang terhubung ke buzzer

void setup() {
  pinMode(LASER_PIN, INPUT); // Set pin laser sebagai input
  pinMode(BUZZER_PIN, OUTPUT); // Set pin buzzer sebagai output
  digitalWrite(LASER_PIN, HIGH);
}

void loop() {
  // Baca status input dari pin laser
  int laserState = digitalRead(LASER_PIN);
  
  // Jika laser terputus (benda melewati)
  if (laserState == LOW) {
    // Nyalakan buzzer
    digitalWrite(BUZZER_PIN, HIGH);
    delay(1000); // Tahan buzzer selama 1 detik
    digitalWrite(BUZZER_PIN, LOW);
  }
}
