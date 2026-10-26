// --- PINES DE LOS BOTONES ---
int botonIzquierda = 2;
int botonAtras = 3;
int botonAdelante = 4;
int botonDerecha = 5;

// --- MOTORES LADO IZQUIERDO (Canal 1) ---
int motorEna = 6; // Control de velocidad Izquierda (PWM)
int motorIn1 = 7; // Control de dirección Izquierda 1
int motorIn2 = 8; // Control de dirección Izquierda 2

// --- MOTORES LADO DERECHO (Canal 2) ---
int motorEnb = 9;  // Control de velocidad Derecha (PWM)
int motorIn3 = 12; // Control de dirección Derecha 1
int motorIn4 = 13; // Control de dirección Derecha 2

// --- PINES SENSOR ULTRASÓNICO Y BUZZER ---
const int buzzerPin = 10; // BUZZER 
const int trigPin = A0;   // TRIG
const int echoPin = A1;   // ECHO

// Velocidad base de los motores (0 a 255)
int velocidad = 255;

// Variables para el control del buzzer
unsigned long tiempoAnteriorBuzzer = 0;
bool estadoBuzzer = false;

void setup() {
  pinMode(botonIzquierda, INPUT);
  pinMode(botonAtras, INPUT);
  pinMode(botonAdelante, INPUT);
  pinMode(botonDerecha, INPUT);
  
  pinMode(motorEna, OUTPUT);
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);

  pinMode(motorEnb, OUTPUT);
  pinMode(motorIn3, OUTPUT);
  pinMode(motorIn4, OUTPUT);

  // Configurar pines del Sensor y Buzzer
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  
  // Iniciar con todos los motores y el buzzer apagados
  digitalWrite(motorIn1, LOW);
  digitalWrite(motorIn2, LOW);
  analogWrite(motorEna, 0);

  digitalWrite(motorIn3, LOW);
  digitalWrite(motorIn4, LOW);
  analogWrite(motorEnb, 0);

  noTone(buzzerPin);
}

void loop() {
  
  long duracion;
  int distancia;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duracion = pulseIn(echoPin, HIGH, 30000); 
  
  if (duracion == 0) {
    distancia = 100;
  } else {
    distancia = duracion * 0.034 / 2;
  }

//--------------------------------------------------------------------------
  unsigned long tiempoActual = millis();

  if (distancia > 0 && distancia <= 10) {
    tone(buzzerPin, 1000); 
  } 
  else if (distancia > 10 && distancia <= 50) {
    int intervaloBuzzer = map(distancia, 10, 50, 50, 500); 

    if (tiempoActual - tiempoAnteriorBuzzer >= intervaloBuzzer) {
      tiempoAnteriorBuzzer = tiempoActual;
      estadoBuzzer = !estadoBuzzer; 
      
      if (estadoBuzzer) {
        tone(buzzerPin, 1000);
      } else {
        noTone(buzzerPin);
      }
    }
  } 
  else {
    noTone(buzzerPin);
    estadoBuzzer = false;
  }

// ----------------------------------------------------------------------------
  bool estadoIzquierda = digitalRead(botonIzquierda);
  bool estadoAtras     = digitalRead(botonAtras);
  bool estadoAdelante  = digitalRead(botonAdelante);
  bool estadoDerecha   = digitalRead(botonDerecha);

  if (estadoAdelante == HIGH) {
    digitalWrite(motorIn1, HIGH);
    digitalWrite(motorIn2, LOW);
    analogWrite(motorEna, velocidad);
    
    digitalWrite(motorIn3, HIGH);
    digitalWrite(motorIn4, LOW);
    analogWrite(motorEnb, velocidad);
  } 
  else if (estadoAtras == HIGH) {
    digitalWrite(motorIn1, LOW);
    digitalWrite(motorIn2, HIGH);
    analogWrite(motorEna, velocidad);
    
    digitalWrite(motorIn3, LOW);
    digitalWrite(motorIn4, HIGH);
    analogWrite(motorEnb, velocidad);
  } 
  else if (estadoIzquierda == HIGH) {
    digitalWrite(motorIn1, LOW);
    digitalWrite(motorIn2, HIGH);
    analogWrite(motorEna, velocidad);
    
    digitalWrite(motorIn3, HIGH);
    digitalWrite(motorIn4, LOW);
    analogWrite(motorEnb, velocidad);
  } 
  else if (estadoDerecha == HIGH) {
    digitalWrite(motorIn1, HIGH);
    digitalWrite(motorIn2, LOW);
    analogWrite(motorEna, velocidad);
    
    digitalWrite(motorIn3, LOW);
    digitalWrite(motorIn4, HIGH);
    analogWrite(motorEnb, velocidad);
  } 
  else {
    digitalWrite(motorIn1, LOW);
    digitalWrite(motorIn2, LOW);
    analogWrite(motorEna, 0);
    
    digitalWrite(motorIn3, LOW);
    digitalWrite(motorIn4, LOW);
    analogWrite(motorEnb, 0);
  }
  
  delay(20);
}