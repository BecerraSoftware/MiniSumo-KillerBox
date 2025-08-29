 


#define sensorDerecha 5
#define sensorIzquierda 1
#define sensorFrente 2


#define SPisoDerecha 4
#define SPisoIzquierda 3

//pines motores 
#define motorIzquierdaA1 6
#define motorIzquierdaA2 7
#define pwdA 5

#define motorDerechaB1 9
#define motorDerechaB2 8
#define pwdB 10







void setup() {
 
  pinMode(sensorDerecha, INPUT);
  pinMode(sensorIzquierda, INPUT);
  pinMode(sensorFrente, INPUT);
  pinMode(SPisoDerecha, INPUT);
  pinMode(SPisoIzquierda, INPUT);

  //Motores
  pinMode(MotorIzquierdaA1, OUTPUT);
  pinMode(MotorIzquierdaA2, OUTPUT);
  pinMode(pwdA, OUTPUT);

  pinMode(MotorDerechaA1, OUTPUT);
  pinMode(MotorDerechaA2, OUTPUT);
  pinMode(pwdB, OUTPUT);




 

  Serial.begin (9600); // Monitor serial
}
void loop(){



}

void l8oop() {
  s1 = analogRead(sen1);
  s2 = analogRead(sen2);
  
  


  if (s1 <= 500 or s2 <= 500) {
    parar();
    delay(100);
    atras(80);
    delay(200);
    derecha(80);
    delay(600);  
  } else {
     //lectura de sensor y
     adelante(80);
/*
     if(digitalRead(18)==1){
       adelante(80);
       digitalWrite(13,HIGH);//ataca
     }else{
       adelante(80); //sigue con tu vida
     }
  }
}

