int trigPin = A0;
int echoPin = A1;
int trigPinL = A2;
int echoPinL = A3;
int trigPinR = A4;
int echoPinR = A5;

int revleft4 = 5;
int fwdleft5 = 4;
int revright6 = 9;
int fwdright7 = 7;

long duration, distance;
long durationL, distanceL;
long durationR, distanceR;
int rotate=0;
int maxleft = 0;
int maxright = 0;
int Insrotate = 0;
 
// FDP_G28

void setup() {
  Serial.begin(9600);
  pinMode(revleft4, OUTPUT);
  pinMode(fwdleft5, OUTPUT);
  pinMode(revright6, OUTPUT);
  pinMode(fwdright7, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPinL, OUTPUT);
  pinMode(echoPinL, INPUT);
  pinMode(trigPinR, OUTPUT);
  pinMode(echoPinR, INPUT);

}

void forward(){
  Serial.println("Forward");
  digitalWrite(fwdright7, HIGH);
  digitalWrite(revright6, LOW);
  digitalWrite(fwdleft5, HIGH);
  digitalWrite(revleft4, LOW);
  delay(100);
}

void left(){
  Serial.println("Left");
  delay(10);
  digitalWrite(fwdright7, LOW);
  digitalWrite(revright6, LOW);
  digitalWrite(fwdleft5, LOW);
  digitalWrite(revleft4, LOW);
  delay(100);

  digitalWrite(fwdright7, HIGH);
  digitalWrite(revright6, LOW);
  digitalWrite(fwdleft5, LOW);
  digitalWrite(revleft4, HIGH);
  delay(465);


  digitalWrite(fwdright7, LOW);
  digitalWrite(revright6, LOW);
  digitalWrite(fwdleft5, LOW);
  digitalWrite(revleft4, LOW);
  delay(20);

  maxleft=0;
  maxright=0;
}

void right(){
  Serial.println("Right");
  delay(10);
  digitalWrite(fwdright7, LOW);
  digitalWrite(revright6, LOW);
  digitalWrite(fwdleft5, LOW);
  digitalWrite(revleft4, LOW);
  delay(100);

  digitalWrite(fwdright7, LOW);
  digitalWrite(revright6, HIGH);
  digitalWrite(fwdleft5, HIGH);
  digitalWrite(revleft4, LOW);
  delay(430);


  digitalWrite(fwdright7, LOW);
  digitalWrite(revright6, LOW);
  digitalWrite(fwdleft5, LOW);
  digitalWrite(revleft4, LOW);
  delay(20);

  maxleft=0;
  maxright=0;
}

void uturn(){
  Serial.println("Uturn");
  digitalWrite(fwdright7, LOW);
  digitalWrite(revright6, LOW);
  digitalWrite(fwdleft5, LOW);
  digitalWrite(revleft4, LOW);
  delay(100);

  digitalWrite(fwdright7, LOW);
  digitalWrite(revright6, HIGH);
  digitalWrite(fwdleft5, HIGH);
  digitalWrite(revleft4, LOW);
  delay(1000);

  maxleft=0;
  maxright=0;
}

void Insleft(){
  digitalWrite(fwdright7, HIGH);
  digitalWrite(revright6, LOW);
  digitalWrite(fwdleft5, LOW);
  digitalWrite(revleft4, HIGH);
  delay(45);
}

void Insright(){
  digitalWrite(fwdright7, LOW);
  digitalWrite(revright6, HIGH);
  digitalWrite(fwdleft5, HIGH);
  digitalWrite(revleft4, LOW);
  delay(45);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin, HIGH); 
  distance = duration*0.017;

  delayMicroseconds(20);
  digitalWrite(trigPinL, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinL, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinL,LOW);
  durationL = pulseIn(echoPinL, HIGH); 
  distanceL = durationL*0.017;

  delayMicroseconds(20);
  digitalWrite(trigPinR, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinR, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinR,LOW);
  durationR = pulseIn(echoPinR, HIGH); 
  distanceR = durationR*0.017;
   Serial.println("Start");
   Serial.println(distance);
   Serial.println(distanceL);
   Serial.println(distanceR);
   Serial.println("Stop");

  digitalWrite(fwdright7, LOW);
  digitalWrite(revright6, LOW);
  digitalWrite(fwdleft5, LOW);
  digitalWrite(revleft4, LOW);
  delay(10);

  if(distanceL>maxleft){
    maxleft=distanceL;
  }

  if(distanceR>maxright){
    maxright=distanceR;
  }

 if(distanceR<18 && distanceL<18 && distance > 30){
   while(distanceR <10 && distanceL<10 && distance > 30){
     if(distanceR<distanceL){
       Insleft();
       forward();
       Insrotate--;
     }
     else if(distanceL<distanceR){
       Insright();
       forward();
       Insrotate++;
     }
   }
   forward();
   delay(1250);
   if(Insrotate<0 && Insrotate >= -18){
     for(int i=-1;i>=Insrotate;i--){
       Insright();
     }
     Insrotate = 0;
   }
   else if(Insrotate>=0 && Insrotate <= 18){
     for(int i=1;i<=Insrotate;i++){
       Insleft();
     }
     Insrotate = 0;
   }
   
   else if(Insrotate>18){
     rotate++;
     Insrotate-=18;
     for(int i=1;i<=Insrotate;i++){
       Insleft();
     }
     Insrotate = 0;
   }
   else if(Insrotate<-18){
     rotate--;
     Insrotate+=18;
     for(int i=-1;i>=Insrotate;i--){
       Insright();
     }
     Insrotate = 0;
   }

 }

  if(distance>30 && (distanceR<9 || distanceL<9)){
    if (distanceR<9){
      left();
      rotate--;
    }
    else if(distanceL<9){
      right();
      rotate++;
    }
  }

  if(rotate<0){
    if(distanceR>=30 && distance>=18){
      forward();
      delay(900);
      
      if (distanceR>=15){
        right();
        rotate++;
      }
    }

    else if(distanceR<30 && distance>18){
      forward();
    }
    else if(distanceR<30 && distance<18){
      uturn();
      rotate+=2;
    }
  }

  else if(rotate>0){
    if(distanceL>=30 && distance>=18){
      forward();
      delay(900);
      if (distanceL>=15){
        left();
        rotate--;
      }
    }

    else if(distanceL<30 && distance>18){
      forward();
    }
    else if(distanceL<30 && distance<18){
      uturn();
      rotate-=2;
    }
  }

  else{
    if(distance>=18){
      forward();
    }
   else if(distance<11 && maxleft<20 && maxright<20){
     uturn();
     if(rotate<0){
       rotate+=2;
     }
     else{
       rotate-=2;
     }
   }

    
    else{
      if(maxleft>maxright){
        left();
        rotate--;
      }
      else if(maxright>=maxleft){
        right();
        rotate++;
      }
    }
  }
}