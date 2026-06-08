
#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial vcSerial(2, 3); // RX, TX
Servo myServo;

int light = 7;
int tv = 8;
int fan = 9;

void setup() {
  Serial.begin(9600);
  vcSerial.begin(9600);

  pinMode(light, OUTPUT);
  pinMode(tv, OUTPUT);
  pinMode(fan, OUTPUT);

  myServo.attach(5);

  // OFF state (relay active LOW)
  digitalWrite(light, HIGH);
  digitalWrite(tv, HIGH);
  digitalWrite(fan, HIGH);

  Serial.println("System Ready...");
}

void loop() {
  if (vcSerial.available()) {
    byte data = vcSerial.read();

    Serial.print("Received: ");
    Serial.println(data);

    // LIGHT
    if (data == 63) digitalWrite(light, LOW);
    if (data == 161) digitalWrite(light, HIGH);

    // TV
    if (data == 124) digitalWrite(tv, LOW);
    if (data == 216) digitalWrite(tv, HIGH);

    // FAN
    if (data == 75) digitalWrite(fan, LOW);
    if (data == 226) digitalWrite(fan, HIGH);

    // SERVO (Door)
    if (data == 154) myServo.write(90);  // OPEN
    if (data == 109) myServo.write(0);   // CLOSE
  }
}