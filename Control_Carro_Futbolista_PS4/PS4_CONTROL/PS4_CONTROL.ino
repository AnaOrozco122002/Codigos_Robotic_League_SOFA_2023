
#include <PS4Controller.h>
const int Valor_B1 =18 ; //pin
const int Valor_PWB = 5; //pin pwm
const int Valor_B2 = 19;
const int Valor_A1 =22 ; //pin
const int Valor_PWA= 33; //pin pwm
const int Valor_A2= 23;
//int PWM = 255;
const int Frecuencia = 5000;
const int Resolucion = 8;
const int Canal0 = 0;
const int Canal2 = 2;
int Vel=0;
int vel2=0;
int contador_a=0, contador_b=0;
//Disparador
const int Entrada_1=4;
int tiempo_1=6000;
int time_2=0;
float time_a=0;
//Segundo Nucleo    
//TaskHandle_t Task1;


//Turbo
bool Turbo = false, in=true, Co=true,parar=false,a=false,b=false;
int Led=2;

void setup() {

   //xTaskCreatePinnedToCore(loop2,"Task_1",1000,NULL,1,&Task1,0);
  Serial.begin(115200);
  PS4.begin();
  //PS4.begin("78:d8:40:9a:cb:90");
  //PS4.begin("28:C1:3C:45:AD:6B");
  
 

  pinMode(Valor_A1,OUTPUT);
  pinMode(Valor_PWA,OUTPUT);
  pinMode(Valor_A2,OUTPUT);
  pinMode(Valor_B1,OUTPUT);
  pinMode(Valor_PWB,OUTPUT);
  pinMode(Valor_B2,OUTPUT);
  pinMode(Entrada_1,OUTPUT);
  pinMode(Led,OUTPUT);
  CrearPWM();
  digitalWrite(Entrada_1,LOW);
}

/*void loop2(void *parameter){
  for(;;){
    if (PS4.isConnected()) {
      
      }
    }
  }
  vTaskDelay(10);
}
*/


void loop() {
  if((millis() - time_2) >= 300){
      digitalWrite(Entrada_1,LOW);
  }
  if (PS4.isConnected()) {
    if((millis() - time_2) >= 300){
      digitalWrite(Entrada_1,LOW);
    }
    if (PS4.LStickX()>20 && PS4.R2()) {
        Vel = PS4.R2Value()-100;
        vel2 = PS4.R2Value();
        if(Vel<0){
          Vel=0;
        }
        if(vel2 > 70){
          vel2=70;
        }
        ledcWrite(Canal0,Vel);
        digitalWrite(Valor_A1,LOW);
        digitalWrite(Valor_A2,HIGH);
        //Motor B Izquierda
        ledcWrite(Canal2,vel2);
        digitalWrite(Valor_B1,HIGH);
        digitalWrite(Valor_B2,LOW);
        Serial.println("Derecha");
    }
      
    else if(PS4.LStickX()<-20 && PS4.R2()){
      //Gira a la Izquierda
      //Motor A Derecha
      Vel = PS4.R2Value()-100;
        vel2 = PS4.R2Value();
        if(Vel<0){
          Vel=0;
        }
        if(vel2 > 70){
          vel2=70;
        }
      ledcWrite(Canal0,vel2);
      digitalWrite(Valor_A1,HIGH);
      digitalWrite(Valor_A2,LOW);
      //Motor B Izquierda
      ledcWrite(Canal2,Vel);
      digitalWrite(Valor_B1,LOW);
      digitalWrite(Valor_B2,HIGH);
      Serial.println("Izquierda");
      
    }else if(PS4.LStickX()>20 && PS4.L2() ){
      //Gira a la Derecha Atras
        //Motor A Derecha
        Vel = PS4.L2Value()-100;
        vel2 = PS4.L2Value();
        if(Vel<0){
          Vel=0;
        }
        if(vel2 > 70){
          vel2=70;
        }
        ledcWrite(Canal0,Vel);
        digitalWrite(Valor_A1,HIGH);
        digitalWrite(Valor_A2,LOW);
        //Motor B Izquierda
        ledcWrite(Canal2,vel2);
        digitalWrite(Valor_B1,LOW);
        digitalWrite(Valor_B2,HIGH);
        Serial.println("Derecha Atras");
    }else if(PS4.LStickX()<-20 && PS4.L2()){
        //Gira a la Izquierda Atras
      //Motor A Derecha
      Vel = PS4.L2Value()-100;
        vel2 = PS4.L2Value();
        if(Vel<0){
          Vel=0;
        }
        if(vel2 > 70){
          vel2=70;
        }
      ledcWrite(Canal0,vel2);
      digitalWrite(Valor_A1,LOW);
      digitalWrite(Valor_A2,HIGH);
      //Motor B Izquierda
      ledcWrite(Canal2,Vel);
      digitalWrite(Valor_B1,HIGH);
      digitalWrite(Valor_B2,LOW);
      Serial.println("Izquierda Atras");
    }else if(PS4.R2() && !Turbo){
      Vel = PS4.R2Value()-100;
        vel2 = PS4.R2Value();
        if(Vel<0){
          Vel=0;
        }
        if(vel2 > 120){
          vel2=120;
        }
      ledcWrite(Canal0,vel2);
      digitalWrite(Valor_A1,HIGH);
      digitalWrite(Valor_A2,LOW);
      //Motor B Izquierda
      ledcWrite(Canal2,vel2);
      digitalWrite(Valor_B1,HIGH);
      digitalWrite(Valor_B2,LOW);
      Serial.println("Adelante");
    }
    else if(PS4.L2() && !Turbo){
      Vel = PS4.L2Value()-100;
        vel2 = PS4.L2Value();
        if(Vel<0){
          Vel=0;
        }
        if(vel2 > 120){
          vel2=120;
        }
      ledcWrite(Canal0,vel2);
      digitalWrite(Valor_A1,LOW);
      digitalWrite(Valor_A2,HIGH);
      //Motor B Izquierda
      ledcWrite(Canal2,vel2);
      digitalWrite(Valor_B1,LOW);
      digitalWrite(Valor_B2,HIGH);
      Serial.println("Atras");
    }
    /*else if (PS4.LStickX()>20 && PS4.R2()  && Turbo) {
        //Gira a la Derecha
        //Motor A Derecha
        Vel = PS4.R2Value()-100;
        vel2 = PS4.R2Value();
        if(Vel<0){
          Vel=0;
        }
        if(vel2 < 0){
          vel2=0;
        }
        if(vel2 > 10 && vel2<80){
          vel2=vel2 + 80;
        }
        else if(vel2 >= 80){
          vel2=160;
        }
        ledcWrite(Canal0,Vel);
        digitalWrite(Valor_A1,LOW);
        digitalWrite(Valor_A2,HIGH);
        //Motor B Izquierda
        ledcWrite(Canal2,vel2);
        digitalWrite(Valor_B1,HIGH);
        digitalWrite(Valor_B2,LOW);
        Serial.println("Derecha Turbo");
    }
      
    else if(PS4.LStickX()<-20 && PS4.R2() && Turbo){
      //Gira a la Izquierda
      //Motor A Derecha
      Vel = PS4.R2Value()-100;
        vel2 = PS4.R2Value();
        if(Vel<0){
          Vel=0;
        }
        if(vel2 < 0){
          vel2=0;
        }
        if(vel2 > 10 && vel2<80){
          vel2=vel2 + 80;
        }
        else if(vel2 >= 80){
          vel2=160;
        }
      ledcWrite(Canal0,vel2);
      digitalWrite(Valor_A1,HIGH);
      digitalWrite(Valor_A2,LOW);
      //Motor B Izquierda
      ledcWrite(Canal2,Vel);
      digitalWrite(Valor_B1,LOW);
      digitalWrite(Valor_B2,HIGH);
      Serial.println("Izquierda Turbo");
      
    }else if(PS4.LStickX()>20 && PS4.L2() && Turbo){
      //Gira a la Derecha Atras
        //Motor A Derecha
        Vel = PS4.L2Value()-100;
        vel2 = PS4.L2Value();
        if(Vel<0){
          Vel=0;
        }
        if(vel2 < 0){
          vel2=0;
        }
        if(vel2 > 10 && vel2<80){
          vel2=vel2 + 80;
        }
        else if(vel2 >= 80){
          vel2=160;
        }
        ledcWrite(Canal0,Vel);
        digitalWrite(Valor_A1,HIGH);
        digitalWrite(Valor_A2,LOW);
        //Motor B Izquierda
        ledcWrite(Canal2,vel2);
        digitalWrite(Valor_B1,LOW);
        digitalWrite(Valor_B2,HIGH);
        Serial.println("Derecha Atras Turbo");
    }else if(PS4.LStickX()<-20 && PS4.L2() && Turbo){
        //Gira a la Izquierda Atras
      //Motor A Derecha
      Vel = PS4.L2Value()-100;
        vel2 = PS4.L2Value();
        if(Vel<0){
          Vel=0;
        }
        if(vel2 < 0){
          vel2=0;
        }
        if(vel2 > 10 && vel2<80){
          vel2=vel2 + 80;
        }
        else if(vel2 >= 80){
          vel2=160;
        }
      ledcWrite(Canal0,vel2);
      digitalWrite(Valor_A1,LOW);
      digitalWrite(Valor_A2,HIGH);
      //Motor B Izquierda
      ledcWrite(Canal2,Vel);
      digitalWrite(Valor_B1,HIGH);
      digitalWrite(Valor_B2,LOW);
      Serial.println("Izquierda Atras Turbo");
    }*/else if(PS4.R2() && Turbo){
      Vel = PS4.R2Value()-100;
        vel2 = PS4.R2Value();
        if(Vel<0){
          Vel=0;
        }
        if(vel2 < 0){
          vel2=0;
        }
        if(vel2 > 10 && vel2<100){
          vel2=vel2 + 80;
        }
        else if(vel2 >= 100){
          vel2=160;
        }
      ledcWrite(Canal0,vel2+50);
      digitalWrite(Valor_A1,HIGH);
      digitalWrite(Valor_A2,LOW);
      //Motor B Izquierda
      ledcWrite(Canal2,vel2);
      digitalWrite(Valor_B1,HIGH);
      digitalWrite(Valor_B2,LOW);
      Serial.println("Adelante Turbo");
    }
    else if(PS4.L2() && Turbo){
      Vel = PS4.L2Value()-100;
        vel2 = PS4.L2Value();
        if(Vel<0){
          Vel=0;
        }
        if(vel2 < 0){
          vel2=0;
        }
        if(vel2 > 10 && vel2<100){
          vel2=vel2 + 80;
        }
        else if(vel2 >= 100){
          vel2=160;
        }
      ledcWrite(Canal0,vel2);
      digitalWrite(Valor_A1,LOW);
      digitalWrite(Valor_A2,HIGH);
      //Motor B Izquierda
      ledcWrite(Canal2,vel2+50);
      digitalWrite(Valor_B1,LOW);
      digitalWrite(Valor_B2,HIGH);
      Serial.println("Atras Turbo");
    }
    else if(!(PS4.R2() or PS4.L2())){
      
        //ledcWrite(Canal0,0);
        digitalWrite(Valor_A1,LOW);
        digitalWrite(Valor_A2,LOW);
        //Motor B Izquierda
        //ledcWrite(Canal2,0);
        digitalWrite(Valor_B1,LOW);
        digitalWrite(Valor_B2,LOW);
        //Serial.println("Detenido");
      
    }
    if(PS4.R1() && Co){
      Turbo=!Turbo;
      Co=false;
      digitalWrite(Led,HIGH);
      Serial.print("Turbo: ");
      Serial.println(Turbo);
    }
    else if(PS4.L1() && !Co){
        Turbo=!Turbo;
        Co=true;
        digitalWrite(Led,LOW);
        Serial.print("Sin Turbo: ");
        Serial.println(Turbo);
    }
    
    if(PS4.Square()){
        if(in){
          digitalWrite(Entrada_1,HIGH);
          time_2=millis();
          //Delay(300);
          //digitalWrite(Entrada_1,LOW);
          Serial.println("Disparador");
          tiempo_1=millis();
          in=false;
        }
        else if((millis() - tiempo_1) > 1200){
          time_2=millis();
          tiempo_1=millis();
          digitalWrite(Entrada_1,HIGH);
          //Delay(300);
          //digitalWrite(Entrada_1,LOW);
          Serial.println("Disparador");
        }
    }    
  }
}
void CrearPWM(){
  ledcSetup(Canal0,Frecuencia,Resolucion); 
  ledcAttachPin(Valor_PWA,Canal0);
  ledcSetup(Canal2,Frecuencia,Resolucion); 
  ledcAttachPin(Valor_PWB,Canal2);
}


