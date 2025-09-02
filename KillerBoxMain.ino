
/*
Código para el robot mini sumo-- KILLERBOX
Robot capaz de detectar obstáculos y reaccionar de acuerdo a la situación
con Sensores de piso para detectar el borde de la arena
y estrategias para empujar al oponente fuera del ring

creado por: Victor Becerra--- github: BecerraSoftware
*/

/*
PINES QUE NO ESTAN FUNCANDO
A4, A6, A7

PINES EN USO
S1=>A0
S2=>A1
S3=>A2
S4=>A3
S8=>A7
*/
//Cuenta con 3 Sensores al frente para detectar 3 posiciones distintas
#define delLeft A2
#define delRigh A5
#define delForWard A3

//Cuenta con 2 Sensores a los costados para detectar si esta de lado o una orientacion
#define sensorRigh 0
#define sensorLeft 0

//Cuenta con dos sensores de piso que detectan el color blanco para no salir del ring
#define floorRigh A7
#define floorLeft A0

//Pines de motores
#define MPos_Left 9
#define MNeg_Left 8
#define PWM_LEFT 10

#define MPos_Righ 6
#define MNeg_Righ 7
#define PWM_RIGH 5


/*
Variables del sistema del robot
BLANCO==> Del sensor de piso que tan intennso detecta el blanco para determinar que movimiento
se efectua
oh si 

*/

//sensores de piso
#define BLANCO 800;// Si el sensor detecta 100 o menos es blanco

const int led= 11;
const int led2=13;


void setup() {
  //SENSORES
  pinMode(delForWard,INPUT);

 // pinMode(/*AQUI PONER EL PIN A EVALUAR*/,INPUT);
  pinMode(floorRigh,INPUT);
  pinMode(floorLeft,INPUT);
  //MOTORES
  pinMode(MPos_Righ, OUTPUT);
  pinMode(MNeg_Righ, OUTPUT);
  pinMode(PWM_RIGH, OUTPUT);

  pinMode(MPos_Left,OUTPUT);
  pinMode(MNeg_Left,OUTPUT);
  pinMode(PWM_LEFT,OUTPUT);

  //varios se puede borrar
  pinMode(led,OUTPUT);
  pinMode(led2,OUTPUT);

  Serial.begin (9600); // Monitor serial
  delay(2000);
}
void loopdev(){
  unsigned int value1 = analogRead(floorRigh);
  unsigned int value2 = analogRead(floorLeft);
  /*
  Serial.print(value1);
  Serial.print(" ");     // Imprime un espacio
  Serial.println(value2); // Imprime value2 y un salto de línea*/

  //Aqui si detecta balnco en los sensores de piso
 
    if(DetectaBlanco(floorRigh) && !DetectaBlanco(floorLeft)){

    }
    if(DetectaBlanco(floorLeft) && !DetectaBlanco(floorRigh)){
      digitalWrite(led2,HIGH);
      delay(50);
      digitalWrite(led2,LOW);
      Serial.println("Detecto Izquierda");
      
    }
     if(DetectaBlanco(floorLeft) && DetectaBlanco(floorRigh)) {
       //Atras(200);
       delay(100);
       stop();
       VueltaRigh(200,200);
      Serial.println("Detecto Los dos");
      
     }
     if(!DetectaBlanco(floorLeft) && !DetectaBlanco(floorRigh)){
      Avanzar(0,100);
      Serial.begin("Detecto Nadota");
    
     }

     Serial.print(value1);
     Serial.print("     ");
     Serial.println(value2);

      
  delay(10);

}
void loop(){
  /*
  unsigned int value1 = analogRead(floorRigh);
  unsigned int value2 = analogRead(floorLeft);

  Serial.print(value1);
  Serial.print(" ");     // Imprime un espacio
  Serial.println(value2); // Imprime value2 y un salto de línea
  */
    if(DetectaBlanco(floorRigh) && DetectaBlanco(floorLeft)){
      
     }

    if(DetectaBlanco(floorLeft) && DetectaBlanco(floorRigh)) {
       Atras(100,2000);
       delay(100);
       //VueltaRigh(200,200);
      Serial.println("Detecto Los dos");
     }

    if(!DetectaBlanco(floorLeft) && !DetectaBlanco(floorRigh)){
      Serial.println("Nadota");
      Avanzar(50,0);
     }
    
  delay(10);
}

void loopSensoresPiso() {

  if(DetectaBlanco(floorLeft) || DetectaBlanco(floorRigh)) {
    stop();
    Serial.println("alto");
  } else {
    Avanzar(10, 0);
    Serial.println("avanzo");
  }
  delay(10);
}
void loopDetectarObstaculos(){
  
  if (DetectarObstaculo(delForWard)) {
    Avanzar(200, 0);   // Opción 0: avanzar recto
  }
  // Si no, si el sensor izquierdo detecta, gira a la derecha (para buscar que el frontal se alinee)
  else if (DetectarObstaculo(delLeft)) {
    Avanzar(150, 2);   // Opción 2: giro a la derecha
  }
  // Si no, si el sensor derecho detecta, gira a la izquierda
  else if (DetectarObstaculo(delRigh)) {
    Avanzar(150, 1);   // Opción 1: giro a la izquierda
  }
  // Si ningún sensor detecta, gira en el sitio lentamente (buscando la señal del frontal)
  else {
    Avanzar(100, 3);   // Opción 3: giro en el sitio
  }

  Serial.println(analogRead(floorRigh));
}
void Atras(float velocidad,int tiempo){
  stop();
  digitalWrite(MPos_Left, LOW);
  digitalWrite(MNeg_Left, HIGH);
  analogWrite(PWM_LEFT, velocidad);
  digitalWrite(MPos_Righ, LOW);
  digitalWrite(MNeg_Righ, HIGH);
  analogWrite(PWM_RIGH, velocidad);
  delay(tiempo);
}

void EncenderLed(int pin){digitalWrite(pin,HIGH);delay(100);digitalWrite(pin,LOW);}                                 
bool DetectaBlanco(int pin){return analogRead(pin)<BLANCO;}
bool DetectarObstaculo(int pin){return digitalRead(pin)==HIGH}
//tiemoo de giro
void VueltaRigh(float velocidad,int turnaroundTime){
  //si detecto uno
        digitalWrite(MPos_Left, LOW);
        digitalWrite(MNeg_Left, HIGH);
        analogWrite(PWM_LEFT, velocidad);
      
        digitalWrite(MPos_Righ, HIGH);
        digitalWrite(MNeg_Righ, LOW);
        analogWrite(PWM_RIGH, 0);
        delay(turnaroundTime);
}
void stop(){
  digitalWrite(MPos_Left,LOW);
  digitalWrite(MNeg_Left,LOW);
  analogWrite(PWM_LEFT,0);

  digitalWrite(MPos_Righ,LOW);
  digitalWrite(MPos_Righ,LOW);
  analogWrite(PWM_RIGH,0);
}
void Avanzar(float velocidad, int opcion){
  /*
 Función Avanzar:
   - velocidad: valor PWM (0 a 255)
   - opcion:
       0 -> ambos motores hacia adelante (avance)
       1 -> giro a la izquierda: motor izquierdo en reversa, motor derecho hacia adelante
       2 -> giro a la derecha: motor izquierdo hacia adelante, motor derecho en reversa
       3 -> giro en el sitio: motores en direcciones opuestas a velocidad moderada
  */
    switch(opcion) {
      case 0: // Avanzar recto
        digitalWrite(MPos_Left, HIGH);
        digitalWrite(MNeg_Left, LOW);
        analogWrite(PWM_LEFT, velocidad);
      
        digitalWrite(MPos_Righ, HIGH);
        digitalWrite(MNeg_Righ, LOW);
        analogWrite(PWM_RIGH, velocidad);
        break;
      
      case 1: // Giro a la izquierda
        digitalWrite(MPos_Left, LOW);
        digitalWrite(MNeg_Left, HIGH);
        analogWrite(PWM_LEFT, velocidad);
      
        digitalWrite(MPos_Righ, HIGH);
        digitalWrite(MNeg_Righ, LOW);
        analogWrite(PWM_RIGH, velocidad);
        break;
      
      case 2: // Giro a la derecha
        digitalWrite(MPos_Left, HIGH);
        digitalWrite(MNeg_Left, LOW);
        analogWrite(PWM_LEFT, velocidad);
      
        digitalWrite(MPos_Righ, LOW);
        digitalWrite(MNeg_Righ, HIGH);
        analogWrite(PWM_RIGH, velocidad);
        break;
      
      case 3: // Giro en el sitio (por ejemplo, giro a la derecha)
        digitalWrite(MPos_Left, HIGH);
        digitalWrite(MNeg_Left, LOW);
        analogWrite(PWM_LEFT, velocidad);
      
        digitalWrite(MPos_Righ, LOW);
        digitalWrite(MNeg_Righ, HIGH);
        analogWrite(PWM_RIGH, velocidad);
        break;
  }
  delay(20);  // Pequeño retardo para estabilidad
}