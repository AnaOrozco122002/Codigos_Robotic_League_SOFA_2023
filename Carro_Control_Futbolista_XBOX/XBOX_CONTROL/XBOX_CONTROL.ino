
#include <XboxSeriesXControllerESP32_asukiaaa.hpp>

//XboxSeriesXControllerESP32_asukiaaa::Core xboxController("14:CB:65:F7:18:AC");  //"14:cb:65:f7:18:ac"
//XboxSeriesXControllerESP32_asukiaaa::Core xboxController("14:cb:65:b9:1f:cf"); //felipe
//XboxSeriesXControllerESP32_asukiaaa::Core xboxController("3C:FA:06:48:E3:CB"); //Anaso
XboxSeriesXControllerESP32_asukiaaa::Core xboxController("F4:6A:D7:A6:A8:D9"); //Angieth

int Valor_A1 =18 ; //pin
int Valor_PWA = 5; //pin pwm
int Valor_A2 = 19;
int Valor_B1 =22 ; //pin
int Valor_PWB= 33; //pin pwm
int Valor_B2= 23;
//int PWM = 255;
int Frecuencia = 5000;
int Resolucion = 10;
int Canal0 = 0;
int Canal2 = 2;
int Vel=0;
int vel2 = 0;


//Disparador
const int Entrada_1=4;
int tiempo_1=6000;
int time_2=0;

//Turbo
bool Turbo = false, in=true, Co=true;
int Led=2;

void setup() {
  Serial.begin(115200);
  xboxController.begin();
  

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


  Serial.println("Ready");
}

void loop() {
  xboxController.onLoop();
  if((millis() - time_2) >= 300){
      digitalWrite(Entrada_1,LOW);
  }
  if (xboxController.isConnected()) {
    if (xboxController.isWaitingForFirstNotification()) {
        Serial.println("waiting for first notification");
    } 
    else {
      //Serial.println("Conectado");
      if((millis() - time_2) >= 300){
        digitalWrite(Entrada_1,LOW);
      }
      uint16_t joystickMax = XboxControllerNotificationParser::maxJoy;
      if (((float)xboxController.xboxNotif.joyLHori / joystickMax)>0.6 && ((float)xboxController.xboxNotif.trigRT)>50 && !Turbo) {
        //Gira a la Derecha
        //Motor A Derecha
        Vel = (float)xboxController.xboxNotif.trigRT-700;
        vel2 = (float)xboxController.xboxNotif.trigRT;
        if(Vel<0){
          Vel=0;
        }else if(Vel > 50){
          Vel=50;
        }
        if(vel2 > 210){
          vel2 = 210;
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
      else if(((float)xboxController.xboxNotif.joyLHori / joystickMax)<0.4 && ((float)xboxController.xboxNotif.trigRT)>50 && !Turbo){
        //Gira a la Izquierda
        //Motor A Derecha
         //Motor A Derecha
        Vel = (float)xboxController.xboxNotif.trigRT-200;
        vel2 = (float)xboxController.xboxNotif.trigRT;
        if(Vel<0){
          Vel=0;
        }else if(Vel > 50){
          Vel=50;
        }
        if(vel2 > 220){
          vel2 = 220;
        }
        ledcWrite(Canal0,vel2);
        digitalWrite(Valor_A1,HIGH);
        digitalWrite(Valor_A2,LOW);
        //Motor B Izquierda
        ledcWrite(Canal2,Vel);
        digitalWrite(Valor_B1,LOW);
        digitalWrite(Valor_B2,HIGH);
        Serial.println("Izquierda");
        
      }
      else if(((float)xboxController.xboxNotif.joyLHori / joystickMax)>0.6 && ((float)xboxController.xboxNotif.trigLT)>50 && !Turbo){
        //Gira a la Derecha Atras
          //Motor A Derecha
           //Motor A Derecha
        Vel = (float)xboxController.xboxNotif.trigLT-200;
        vel2 = (float)xboxController.xboxNotif.trigLT;
        if(Vel<0){
          Vel=0;
        }else if(Vel > 50){
          Vel=50;
        }
        if(vel2 > 210){
          vel2 = 210;
        }
          ledcWrite(Canal0,Vel);
          digitalWrite(Valor_A1,HIGH);
          digitalWrite(Valor_A2,LOW);
          //Motor B Izquierda
          ledcWrite(Canal2,vel2);
          digitalWrite(Valor_B1,LOW);
          digitalWrite(Valor_B2,HIGH);
          Serial.println("Derecha Atras");
      }
      else if(((float)xboxController.xboxNotif.joyLHori / joystickMax)<0.4 && ((float)xboxController.xboxNotif.trigLT)>50 && !Turbo){
        //Gira a la Izquierda Atras
        //Motor A Derecha
        Vel = (float)xboxController.xboxNotif.trigLT-200;
        vel2 = (float)xboxController.xboxNotif.trigLT;
        if(Vel<0){
          Vel=0;
        }else if(Vel > 50){
          Vel=50;
        }
        if(vel2 > 220){
          vel2 = 220;
        }
        ledcWrite(Canal0,vel2);
        digitalWrite(Valor_A1,LOW);
        digitalWrite(Valor_A2,HIGH);
        //Motor B Izquierda
        ledcWrite(Canal2,Vel);
        digitalWrite(Valor_B1,HIGH);
        digitalWrite(Valor_B2,LOW);
        Serial.println("Izquierda Atras");
      }
      else if((float)xboxController.xboxNotif.trigRT>50 && !Turbo){
        Vel = (float)xboxController.xboxNotif.trigRT-700;
        vel2 = (float)xboxController.xboxNotif.trigRT;
        if(Vel<0){
          Vel=0;
        }else if(Vel > 100){
          Vel=100;
        }
        if(vel2 > 500){
          vel2 = 500;
        }
        ledcWrite(Canal0,vel2+10);
        digitalWrite(Valor_A1,HIGH);
        digitalWrite(Valor_A2,LOW);
        //Motor B Izquierda
        ledcWrite(Canal2,vel2);
        digitalWrite(Valor_B1,HIGH);
        digitalWrite(Valor_B2,LOW);
        Serial.println("Adelante");
      }
      else if((float)xboxController.xboxNotif.trigLT>50 && !Turbo){
        Vel = (float)xboxController.xboxNotif.trigLT-700;
        vel2 = (float)xboxController.xboxNotif.trigLT;
        if(Vel<0){
          Vel=0;
        }else if(Vel > 100){
          Vel=100;
        }
        if(vel2 > 500){
          vel2 = 500;
        }
        ledcWrite(Canal0,vel2);
        digitalWrite(Valor_A1,LOW);
        digitalWrite(Valor_A2,HIGH);
        //Motor B Izquierda
        ledcWrite(Canal2,vel2+15);
        digitalWrite(Valor_B1,LOW);
        digitalWrite(Valor_B2,HIGH);
        Serial.println("Atras");
      }
      else if (((float)xboxController.xboxNotif.joyLHori / joystickMax)>0.6 && ((float)xboxController.xboxNotif.trigRT)>50 && Turbo) {
        //Gira a la Derecha
        //Motor A Derecha
        Vel = (float)xboxController.xboxNotif.trigRT-700;
        vel2 = (float)xboxController.xboxNotif.trigRT;

         if(Vel<0){
          Vel=0;
        }
        if(vel2 < 0){
          vel2=0;
        }
        if(vel2 > 10 && vel2<100){
          vel2=vel2 + 100;
        }
        else if(vel2 >= 200){
          vel2=200;
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
      else if(((float)xboxController.xboxNotif.joyLHori / joystickMax)<0.4 && ((float)xboxController.xboxNotif.trigRT)>50 && Turbo){
        //Gira a la Izquierda
        //Motor A Derecha
         //Motor A Derecha
        Vel = (float)xboxController.xboxNotif.trigRT-700;
        vel2 = (float)xboxController.xboxNotif.trigRT;
         if(Vel<0){
          Vel=0;
        }
        if(vel2 < 0){
          vel2=0;
        }
        if(vel2 > 10 && vel2<100){
          vel2=vel2 + 100;
        }
        else if(vel2 >= 200){
          vel2=200;
        }
        ledcWrite(Canal0,vel2);
        digitalWrite(Valor_A1,HIGH);
        digitalWrite(Valor_A2,LOW);
        //Motor B Izquierda
        ledcWrite(Canal2,Vel);
        digitalWrite(Valor_B1,LOW);
        digitalWrite(Valor_B2,HIGH);
        Serial.println("Izquierda Turbo");
        
      }
      else if(((float)xboxController.xboxNotif.joyLHori / joystickMax)>0.6 && ((float)xboxController.xboxNotif.trigLT)>50 && Turbo){
        //Gira a la Derecha Atras
          //Motor A Derecha
           //Motor A Derecha
        Vel = (float)xboxController.xboxNotif.trigLT-700;
        vel2 = (float)xboxController.xboxNotif.trigLT;
         if(Vel<0){
          Vel=0;
        }
        if(vel2 < 0){
          vel2=0;
       }
        if(vel2 > 10 && vel2<100){
          vel2=vel2 + 100;
        }
        else if(vel2 >= 200){
          vel2=200;
        }
          ledcWrite(Canal0,Vel);
          digitalWrite(Valor_A1,HIGH);
          digitalWrite(Valor_A2,LOW);
          //Motor B Izquierda
          ledcWrite(Canal2,vel2);
          digitalWrite(Valor_B1,LOW);
          digitalWrite(Valor_B2,HIGH);
          Serial.println("Derecha Atras Turbo");
      }
      else if(((float)xboxController.xboxNotif.joyLHori / joystickMax)<0.4 && ((float)xboxController.xboxNotif.trigLT)>50 && Turbo){
        //Gira a la Izquierda Atras
        //Motor A Derecha
        Vel = (float)xboxController.xboxNotif.trigLT-700;
        vel2 = (float)xboxController.xboxNotif.trigLT;
         if(Vel<0){
          Vel=0;
        }
        if(vel2 < 0){
          vel2=0;
        }
        if(vel2 > 10 && vel2<100){
          vel2=vel2 + 100;
        }
        else if(vel2 >= 200){
          vel2=200;
        }
        ledcWrite(Canal0,vel2);
        digitalWrite(Valor_A1,LOW);
        digitalWrite(Valor_A2,HIGH);
        //Motor B Izquierda
        ledcWrite(Canal2,Vel);
        digitalWrite(Valor_B1,HIGH);
        digitalWrite(Valor_B2,LOW);
        Serial.println("Izquierda Atras Turbo");
      }
      else if((float)xboxController.xboxNotif.trigRT>50 && Turbo){
        Vel = (float)xboxController.xboxNotif.trigRT-700;
        vel2 = (float)xboxController.xboxNotif.trigRT;
         if(Vel<0){
          Vel=0;
        }
        if(vel2 < 0){
          vel2=0;
        }
        if(vel2 > 10 && vel2<350){
          vel2=vel2 + 350;
        }
        else if(vel2 >= 700){
          vel2=700;
        }
        ledcWrite(Canal0,vel2);
        digitalWrite(Valor_A1,HIGH);
        digitalWrite(Valor_A2,LOW);
        //Motor B Izquierda
        ledcWrite(Canal2,vel2);
        digitalWrite(Valor_B1,HIGH);
        digitalWrite(Valor_B2,LOW);
        Serial.println("Adelante Turbo");
        Serial.println(vel2);
      }
      else if((float)xboxController.xboxNotif.trigLT>50 && Turbo){
        Vel = (float)xboxController.xboxNotif.trigLT-700;
        vel2 = (float)xboxController.xboxNotif.trigLT;
         if(Vel<0){
          Vel=0;
        }
        if(vel2 < 0){
          vel2=0;
        }
        if(vel2 > 10 && vel2<350){
          vel2=vel2 + 350;
        }
        else if(vel2 >= 700){
          vel2=750;
        }
        ledcWrite(Canal0,vel2);
        digitalWrite(Valor_A1,LOW);
        digitalWrite(Valor_A2,HIGH);
        //Motor B Izquierda
        ledcWrite(Canal2,vel2);
        digitalWrite(Valor_B1,LOW);
        digitalWrite(Valor_B2,HIGH);
        Serial.println("Atras Turbo");
      }
      else if(!((float)xboxController.xboxNotif.trigRT >50 or (float)xboxController.xboxNotif.trigLT > 50)){
          //ledcWrite(Canal0,0);
          digitalWrite(Valor_A1,LOW);
          digitalWrite(Valor_A2,LOW);
          //Motor B Izquierda
          //ledcWrite(Canal2,0);
          digitalWrite(Valor_B1,LOW);
          digitalWrite(Valor_B2,LOW);
          //Serial.println("Detenido");
      }
      if(xboxController.xboxNotif.btnRB  && Co){
          Turbo=!Turbo;
          Co=false;
          digitalWrite(Led,HIGH);
          Serial.print("Turbo: ");
          Serial.println(Turbo);
      }else if(xboxController.xboxNotif.btnLB && !Co){
          Turbo=!Turbo;
          Co=true;
          digitalWrite(Led,LOW);
          Serial.print("Sin Turbo: ");
          Serial.println(Turbo);
        }
      if(xboxController.xboxNotif.btnX){
        
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
  else {
    Serial.println("not connected");
    if (xboxController.getCountFailedConnection() > 2) {
      ESP.restart();
    }
  }  
}

void CrearPWM(){
  ledcSetup(Canal0,Frecuencia,Resolucion); 
  ledcAttachPin(Valor_PWA,Canal0);
  ledcSetup(Canal2,Frecuencia,Resolucion); 
  ledcAttachPin(Valor_PWB,Canal2);
}

