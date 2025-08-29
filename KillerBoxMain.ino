/*****************************************************
 *  Código extendido y estructurado para control de robot minisumo
 *  - Sensores frontales, laterales y de piso
 *  - Motores con control PWM
 *  - Sistema DIP switch para modo de prueba
 *  - Rutinas de evasión y ataque
 *  - Control de velocidad y dirección

 BecerraSoftware
 *****************************************************/

// ------------------- Definición de pines -------------------
// Sensores de oponentes

#define SENSOR_DERECHA     5
#define SENSOR_IZQUIERDA   1
#define SENSOR_FRENTE      2

// Sensores de piso (barrera blanca)
#define SENSOR_PISO_DERECHA 4
#define SENSOR_PISO_IZQUIERDA 3

// Motores
#define MOTOR_IZQ_A1 6
#define MOTOR_IZQ_A2 7
#define MOTOR_PWM_A  5

#define MOTOR_DER_B1 9
#define MOTOR_DER_B2 8
#define MOTOR_PWM_B  10

// DIP switch
#define DIP1 11

// LED indicador
#define LED_ESTADO 13

// ------------------- Variables globales -------------------
int lecturaSensorDerecha = 0;
int lecturaSensorIzquierda = 0;
int lecturaSensorFrente = 0;
int lecturaPisoDerecha = 0;
int lecturaPisoIzquierda = 0;

int velocidadBase = 120;   // Velocidad nominal
int velocidadGiro = 150;   // Velocidad para giros
int umbralSensor = 500;    // Valor de referencia de los sensores
bool modoAtaque = false;   // Estado de ataque

// ------------------- Funciones auxiliares -------------------
void parar() {
  analogWrite(MOTOR_PWM_A, 0);
  analogWrite(MOTOR_PWM_B, 0);
  digitalWrite(MOTOR_IZQ_A1, LOW);
  digitalWrite(MOTOR_IZQ_A2, LOW);
  digitalWrite(MOTOR_DER_B1, LOW);
  digitalWrite(MOTOR_DER_B2, LOW);
}

void adelante(int velocidad) {
  digitalWrite(MOTOR_IZQ_A1, HIGH);
  digitalWrite(MOTOR_IZQ_A2, LOW);
  digitalWrite(MOTOR_DER_B1, HIGH);
  digitalWrite(MOTOR_DER_B2, LOW);
  analogWrite(MOTOR_PWM_A, velocidad);
  analogWrite(MOTOR_PWM_B, velocidad);
}

void atras(int velocidad) {
  digitalWrite(MOTOR_IZQ_A1, LOW);
  digitalWrite(MOTOR_IZQ_A2, HIGH);
  digitalWrite(MOTOR_DER_B1, LOW);
  digitalWrite(MOTOR_DER_B2, HIGH);
  analogWrite(MOTOR_PWM_A, velocidad);
  analogWrite(MOTOR_PWM_B, velocidad);
}

void izquierda(int velocidad) {
  digitalWrite(MOTOR_IZQ_A1, LOW);
  digitalWrite(MOTOR_IZQ_A2, HIGH);
  digitalWrite(MOTOR_DER_B1, HIGH);
  digitalWrite(MOTOR_DER_B2, LOW);
  analogWrite(MOTOR_PWM_A, velocidad);
  analogWrite(MOTOR_PWM_B, velocidad);
}

void derecha(int velocidad) {
  digitalWrite(MOTOR_IZQ_A1, HIGH);
  digitalWrite(MOTOR_IZQ_A2, LOW);
  digitalWrite(MOTOR_DER_B1, LOW);
  digitalWrite(MOTOR_DER_B2, HIGH);
  analogWrite(MOTOR_PWM_A, velocidad);
  analogWrite(MOTOR_PWM_B, velocidad);
}

// Rutina de evasión cuando detecta línea blanca
void rutinaEvasion() {
  parar();
  delay(100);
  atras(velocidadBase);
  delay(250);
  derecha(velocidadGiro);
  delay(500);
}

// ------------------- Configuración inicial -------------------
void setup() {
  // Pines de sensores
  pinMode(SENSOR_DERECHA, INPUT);
  pinMode(SENSOR_IZQUIERDA, INPUT);
  pinMode(SENSOR_FRENTE, INPUT);
  pinMode(SENSOR_PISO_DERECHA, INPUT);
  pinMode(SENSOR_PISO_IZQUIERDA, INPUT);

  // Pines de motores
  pinMode(MOTOR_IZQ_A1, OUTPUT);
  pinMode(MOTOR_IZQ_A2, OUTPUT);
  pinMode(MOTOR_PWM_A, OUTPUT);
  pinMode(MOTOR_DER_B1, OUTPUT);
  pinMode(MOTOR_DER_B2, OUTPUT);
  pinMode(MOTOR_PWM_B, OUTPUT);

  // Pines adicionales
  pinMode(DIP1, INPUT);
  pinMode(LED_ESTADO, OUTPUT);

  // Comunicación serial
  Serial.begin(9600);
  Serial.println("===== Robot Minisumo Iniciado =====");
  Serial.println("Esperando activación por DIP switch...");
}

// ------------------- Bucle principal -------------------
void loop() {
  // Espera a que el DIP1 esté en HIGH para activar el robot
  if (digitalRead(DIP1) == HIGH) {
    digitalWrite(LED_ESTADO, HIGH);
    loopVuelta();
  } else {
    parar();
    digitalWrite(LED_ESTADO, LOW);
  }
}

// ------------------- Lógica de movimiento -------------------
void loopVuelta() {
  // Leer sensores
  lecturaSensorDerecha   = analogRead(SENSOR_DERECHA);
  lecturaSensorIzquierda = analogRead(SENSOR_IZQUIERDA);
  lecturaSensorFrente    = analogRead(SENSOR_FRENTE);
  lecturaPisoDerecha     = digitalRead(SENSOR_PISO_DERECHA);
  lecturaPisoIzquierda   = digitalRead(SENSOR_PISO_IZQUIERDA);

  // Imprimir datos de depuración
  Serial.print("Der: "); Serial.print(lecturaSensorDerecha);
  Serial.print(" | Izq: "); Serial.print(lecturaSensorIzquierda);
  Serial.print(" | Frente: "); Serial.print(lecturaSensorFrente);
  Serial.print(" | Piso D: "); Serial.print(lecturaPisoDerecha);
  Serial.print(" | Piso I: "); Serial.println(lecturaPisoIzquierda);

  // Verificación de línea blanca (piso detectado)
  if (lecturaPisoDerecha == HIGH || lecturaPisoIzquierda == HIGH) {
    rutinaEvasion();
  } 
  // Verificación de detección de oponente
  else if (lecturaSensorFrente <= umbralSensor || 
           lecturaSensorDerecha <= umbralSensor || 
           lecturaSensorIzquierda <= umbralSensor) {

    parar();
    delay(100);

    // Ataque frontal
    if (lecturaSensorFrente <= umbralSensor) {
      modoAtaque = true;
      adelante(255);
      digitalWrite(LED_ESTADO, HIGH);
    } 
    // Ataque lateral
    else if (lecturaSensorDerecha <= umbralSensor) {
      derecha(velocidadGiro);
      delay(300);
      adelante(200);
    } 
    else if (lecturaSensorIzquierda <= umbralSensor) {
      izquierda(velocidadGiro);
      delay(300);
      adelante(200);
    }
  } 
  // Si no detecta nada, avanza de manera exploratoria
  else {
    modoAtaque = false;
    adelante(velocidadBase);
    digitalWrite(LED_ESTADO, LOW);
  }
}

