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
// Asumiendo pines 9, 10 y 11 para el lado derecho del L293D
int motorEnb = 9;  // Control de velocidad Derecha (PWM)
int motorIn3 = 12; // Control de dirección Derecha 1
int motorIn4 = 13; // Control de dirección Derecha 2

// Velocidad base de los motores (0 a 255)
int velocidad = 255;

void setup() {
  // Configurar botones
  pinMode(botonIzquierda, INPUT);
  pinMode(botonAtras, INPUT);
  pinMode(botonAdelante, INPUT);
  pinMode(botonDerecha, INPUT);
  
  // Configurar pines del L293D (Izquierda)
  pinMode(motorEna, OUTPUT);
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);

  // Configurar pines del L293D (Derecha)
  pinMode(motorEnb, OUTPUT);
  pinMode(motorIn3, OUTPUT);
  pinMode(motorIn4, OUTPUT);
  
  // Iniciar con todos los motores apagados
  digitalWrite(motorIn1, LOW);
  digitalWrite(motorIn2, LOW);
  analogWrite(motorEna, 0);

  digitalWrite(motorIn3, LOW);
  digitalWrite(motorIn4, LOW);
  analogWrite(motorEnb, 0);
}

void loop() {
  // 1. Leer el estado de los 4 botones
  bool estadoIzquierda = digitalRead(botonIzquierda);
  bool estadoAtras     = digitalRead(botonAtras);
  bool estadoAdelante  = digitalRead(botonAdelante);
  bool estadoDerecha   = digitalRead(botonDerecha);

  // 2. Evaluar qué botón está presionado y mover el carrito
  if (estadoAdelante == HIGH) {
    // Avanzar: Ambos lados giran hacia adelante
    digitalWrite(motorIn1, HIGH);
    digitalWrite(motorIn2, LOW);
    analogWrite(motorEna, velocidad);
    
    digitalWrite(motorIn3, HIGH);
    digitalWrite(motorIn4, LOW);
    analogWrite(motorEnb, velocidad);
  } 
  else if (estadoAtras == HIGH) {
    // Retroceder: Ambos lados giran hacia atrás
    digitalWrite(motorIn1, LOW);
    digitalWrite(motorIn2, HIGH);
    analogWrite(motorEna, velocidad);
    
    digitalWrite(motorIn3, LOW);
    digitalWrite(motorIn4, HIGH);
    analogWrite(motorEnb, velocidad);
  } 
  else if (estadoIzquierda == HIGH) {
    // Girar Izquierda: Lado derecho avanza, lado izquierdo retrocede
    digitalWrite(motorIn1, LOW);
    digitalWrite(motorIn2, HIGH);
    analogWrite(motorEna, velocidad);
    
    digitalWrite(motorIn3, HIGH);
    digitalWrite(motorIn4, LOW);
    analogWrite(motorEnb, velocidad);
  } 
  else if (estadoDerecha == HIGH) {
    // Girar Derecha: Lado izquierdo avanza, lado derecho retrocede
    digitalWrite(motorIn1, HIGH);
    digitalWrite(motorIn2, LOW);
    analogWrite(motorEna, velocidad);
    
    digitalWrite(motorIn3, LOW);
    digitalWrite(motorIn4, HIGH);
    analogWrite(motorEnb, velocidad);
  } 
  else {
    // Si no hay ningún botón presionado, apagar todos los motores
    digitalWrite(motorIn1, LOW);
    digitalWrite(motorIn2, LOW);
    analogWrite(motorEna, 0);
    
    digitalWrite(motorIn3, LOW);
    digitalWrite(motorIn4, LOW);
    analogWrite(motorEnb, 0);
  }
  
  // Pequeña pausa para estabilizar la lectura de los botones
  delay(20);
}