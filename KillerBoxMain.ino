int s1 = 0; // sensor 1
int s2 = 0; // sensor 1
/*
int f1=0;
int f2=0;
int f3=0;
*/
int sen1 = 2;
int sen2 = 5;




void setup() {
 
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);

  pinMode(5,OUTPUT);//pwma motorderecha
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);//pwmb motorIzquierda

 // pinMode(15,INPUT);
 // pinMode(18,INPUT);
 // pinMode(20,INPUT);//A7

  Serial.begin (9600); // Monitor serial
}

void loop() {
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
       digitalWrite(13,LOW);
     }
    */
    
  }

  


}


  void derecha(int v1){
  analogWrite(5,v1);
  digitalWrite(6,LOW);
  digitalWrite(7,HIGH);

   analogWrite(10,v1);
  digitalWrite(9,LOW);
  digitalWrite(8,HIGH);
  }


    void atras(int v1){
  analogWrite(5,v1);
  digitalWrite(6,HIGH);
  digitalWrite(7,LOW);

   analogWrite(10,v1);
  digitalWrite(9,LOW);
  digitalWrite(8,HIGH);
  }
 
  void izquierda(int v1){
  analogWrite(5,v1);
  digitalWrite(6,HIGH);
  digitalWrite(7,LOW);
  analogWrite(10,v1);
  digitalWrite(9,HIGH);
  digitalWrite(8,LOW);
  }

  void adelante(int v1){
  analogWrite(5,v1);
  digitalWrite(6,LOW);
  digitalWrite(7,HIGH);

   analogWrite(10,v1);
  digitalWrite(9,HIGH);
  digitalWrite(8,LOW);
  }


  
  
  void parar(){
  analogWrite(5,255);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);

  analogWrite(10,255);
  digitalWrite(9,LOW);
  digitalWrite(8,LOW);
  }
