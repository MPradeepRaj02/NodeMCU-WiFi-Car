//10 AUGUST 2020
//CRATUS MK10
//FAUCETER WIFI CAR 
//BY PRADEEP RAJ (M.P.R)

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

IPAddress ip(192,143,4,3);
IPAddress netmask(255,255,255,0);
ESP8266WebServer server(8080) ;

const char* ssid = "Fauceter WiFi Car";

//M1-LEFT M2-RIGHT

int M1Forward =4 ;  //D2--IN3
int M2Forward =16 ;  //D0--IN1
int M1Backward =0 ;  //D3--IN4
int M2Backward =5 ; //D1--IN2

int M1ENB = 12; //D6--EB
int M2ENB = 14; //D5--EA

void setup() {
  pinMode(M1Forward, OUTPUT);
  pinMode(M2Forward, OUTPUT);
  pinMode(M1Backward, OUTPUT);
  pinMode(M2Backward, OUTPUT);

  pinMode(M1ENB, OUTPUT);
  pinMode(M2ENB, OUTPUT);

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(ip,ip,netmask);
  WiFi.softAP(ssid);

  server.on("/move",HTTP_GET,Move);
  server.onNotFound(NotConnected);
  Serial.begin(115200);
  server.begin();
}

void loop()  {
  server.handleClient();
  Serial.println(".......");
  Serial.println("WIFI Connected");
  Serial.println("NODE MCU Local IP address ");
  Serial.print(WiFi.localIP());
 
}
  
void Move() {
  if (!server.hasArg("dir"))  {
    server.send(404,"text / plain","Move : Undefined");
    return;
  }
  String direction = server.arg("dir");
  
  if (direction.equals("F")) {
    forward();
    server.send(200,"text / plain","Move : Forward");
  }
  else if (direction.equals("R"))  {
    Right();
    server.send(200,"text / plain","Move : Right");
  }
  else if (direction.equals("L"))  {
    Left();
    server.send(200,"text / plain","Move : Left");
  }
  else if (direction.equals("B"))  {
    backward();
    server.send(200,"text / plain","Move : Backward");
  }
  else {
    stop();
    server.send(200,"text / plain","Move : Stop");
  }
}

void NotConnected() {
  server.send(404, "text / plain", "404 : Devicce Not found");
}


void forward() {
    digitalWrite(M1ENB, HIGH);
    digitalWrite(M2ENB, HIGH); 
    digitalWrite(M1Forward,HIGH);
    digitalWrite(M1Backward,LOW);
    digitalWrite(M2Forward,HIGH);
    digitalWrite(M2Backward,LOW);  
}

void backward(){ 
      digitalWrite(M1ENB, HIGH);
      digitalWrite(M2ENB, HIGH);
    digitalWrite(M1Forward,LOW);
    digitalWrite(M1Backward,HIGH);
    digitalWrite(M2Forward,LOW);
    digitalWrite(M2Backward,HIGH);    }

void Right(){ 
      digitalWrite(M1ENB, HIGH);
      digitalWrite(M2ENB, HIGH);
      digitalWrite(M1Forward,HIGH);
      digitalWrite(M1Backward,LOW);
      digitalWrite(M2Forward,LOW);
      digitalWrite(M2Backward,HIGH);  
  }

void Left(){
      digitalWrite(M1ENB, HIGH);
      digitalWrite(M2ENB, HIGH);
    digitalWrite(M1Forward,LOW);
    digitalWrite(M1Backward,HIGH);
    digitalWrite(M2Forward,HIGH);
    digitalWrite(M2Backward,LOW);  
    }

 void stop(){  
      digitalWrite(M1ENB, LOW);
      digitalWrite(M2ENB, LOW);
    digitalWrite(M1Forward,LOW);
    digitalWrite(M1Backward,LOW);
    digitalWrite(M2Forward,LOW);
    digitalWrite(M2Backward,LOW);  
 }
