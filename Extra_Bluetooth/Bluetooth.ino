#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11);  // RX, TX

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  BTSerial.begin(9600);
  digitalWrite(13, LOW);
}

void loop() {

  while (BTSerial.available() > 0) {

    char receivedChar = BTSerial.read();

    // Ignorar Enter y salto de línea
    if (receivedChar == '\r' || receivedChar == '\n') {
      continue;
    }

    // Mostrar mensaje recibido en el monitor serial
    Serial.print("Mensaje recibido: ");
    Serial.println(receivedChar);

    if (receivedChar == '1') {
      digitalWrite(13, HIGH);
      Serial.println("Comando recibido: 1");
      Serial.println("LED encendido");
      BTSerial.println("LED encendido");
    }

    else if (receivedChar == '0') {
      digitalWrite(13, LOW);
      Serial.println("Comando recibido: 0");
      Serial.println("LED apagado");
      BTSerial.println("LED apagado");
    }

    else {
      Serial.println("Comando no valido");
      BTSerial.println("Comando no valido");
    }
  }
}