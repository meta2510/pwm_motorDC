int P = 0; //POTENCIOMETRO
int M = 3; //SALIDA DEL MOTOR
int S1 = 2; //POSICION 1 DEL SWITCH
int S2 = 4; //POSICION 2 DEL SWITCH
int Bo1 = 5; //PULSADOR 1 
int Bo2 = 6; //PULSADOR 2
int POR;  // PORCENTAJE ACUTAL DEL PWM 
int IN1 = 7;
int IN2 = 8;

void setup() {
  
  pinMode(M, OUTPUT);
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(Bo1, INPUT);
  pinMode(Bo2, INPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN1,OUTPUT);
  Serial.begin (9600);

}

void loop() {
  
  // SWITCH EN POSICION 1
  while(digitalRead(S1) == HIGH && digitalRead(S2) == LOW){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    if(analogRead(P)<=300 && analogRead(P)>=0){
     //CICLO DE TRABAJO AL 25%
     analogWrite (M, 80);
     Serial.print(25);
     Serial.println("%");
     POR = 1;
     delay(200);
    }
   else if (analogRead(P)<=700 && analogRead(P)>=301){
    //CICLO DE TRABAJO AL 50%
    analogWrite (M, 125);
    Serial.print(50);
    Serial.println("%");
    POR = 2;
    delay(200);
   }
   else if (analogRead(P)<=1023 && analogRead(P)>=701){
    //CICLO DE TRABAJO AL 75%
    analogWrite (M, 187);
    Serial.print(75);
    Serial.println("%");
    POR = 3;
    delay(200);
   }
 }
  
  // SWITCH EN POSICION 2

  while(digitalRead(S2) == HIGH && digitalRead(S1) == LOW){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    delay(750);
    if (POR < 3){
      //CICLO DEL TRABAJO ES MENOR AL 75% SE ENTRA EN ESTE IF
      if (digitalRead(Bo1) == HIGH && POR == 0 && digitalRead(Bo2) == LOW){
        //SI EL CICLO DE TRABAJO ES DE 0% SE AUMENTA AL 25%
        analogWrite(M, 80);
        Serial.print(25);
        Serial.println("%");
        POR = 1;
      }
      else if (digitalRead(Bo1) == HIGH && POR == 1 && digitalRead(Bo2) == LOW){
        //SI EL CICLO DE TRABAJO ES DE 25% SE AUMENTA AL 50%
        analogWrite(M, 125);
        Serial.print(50);
        Serial.println("%");
        POR = 2;
      }
      else if(digitalRead(Bo1) == HIGH && POR == 2 && digitalRead(Bo2) == LOW){
        //SI EL CICLO DE TRABAJO ES DE 50% SE AUMENTA AL 75%
        analogWrite(M, 187);
        Serial.print(75);
        Serial.println("%");
        POR = 3;
      }
    }
    if(POR > 1){
      //CICLO DEL TRABAJO ES MAYOR AL 25% SE ENTRA EN ESTE IF
      if (digitalRead(Bo2) == HIGH && POR == 2 && digitalRead(Bo1) == LOW){
        //SI EL CICLO DE TRABAJO ES DE 50% SE DISMINUYE AL 25%
        analogWrite(M, 80);
        Serial.print(25);
        Serial.println("%");
        POR = 1;
      }
      else if (digitalRead(Bo2) == HIGH && POR == 3 && digitalRead(Bo1) == LOW){
        //SI EL CICLO DE TRABAJO ES DE 75% SE DISMINUYE AL 50%
        analogWrite(M, 125);
        Serial.print(50);
        Serial.println("%");
        POR = 2;
      }
    }
  }
}
