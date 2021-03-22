////////////////////////////////////////////////////////////////////////
//
//  ESP32 nodeMCU ESP8266 WIFI control motor access point 
// 
//  code: Control de plataforma movil 
//  botones UP/DOWN/PWM / turnOn/Off 
//
//  Author : Sequeira Andres
//  
////////////////////////////////////////////////////////////////////////

#include <ESP8266WebServer.h> 
#include <ESP8266WiFi.h> 
#include <WiFiClient.h> 

ESP8266WebServer server(80); 
 
// Make a wifi name and password as access points
const char *ssid = "NodeMCU_ESP8266";
const char *password = "qwerty";

// i'm going to use 30 to 40 % of duty cicle 

// define ports to control up,down y pwm for motor dc 

#define MOTOR_UP 14       //  gpio 14 D5
#define MOTOR_DOWN 12     //  gpio 12 D4
#define MOTOR_PWM 13      //  gpio 13 D3 for PWM control
#define RADAR_ON_OFF  15  // gpio 10 for turn on off
#define RADAR_AUX  3      // gpio3 for aux
//#define MOTOR_SPEED 450 
#define DELAY_TIME 1000

int MOTOR_SPEED = 450 ; // INIT MOTOR SPEED 
// MOTOR_PWM from 0 to 1024 
// use 450 
 
//  html code for server
const String HtmlHtml = "<html><head>"
"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" /></head>";
const String HtmlTitle = "<h1>Control MOTOR Using NodeMCU WiFi Access Point</h1><br/>\n";
// const String HtmlLedStateLow = "<big>LED is now <b>OFF</b></big><br/><br/>\n";
// const String HtmlLedStateHigh = "<big>LED is now <b>ON</b></big><br/><br/>\n";
const String HtmlButtons = 
"<a href=\"RADARON\"><button style=\"background-color:green;color:white;width:30%;height:10%;\"> radar ON </button></a>\n"
"<a href=\"RADAROFF\"><button style=\"background-color:red;color:white;width:30%;height:10%;\">radar OFF </button></a><br/>"
"<a href=\"MOTORUP\"><button style=\"background-color:green;color:white;width:30%;height:10%;\">UP</button></a>\n"
"<a href=\"MOTORSTOP\"><button style=\"background-color:red;color:white;width:30%;height:10%;\">STOP </button></a>\n"
"<a href=\"MOTORDOWN\"><button style=\"background-color:blue;color:white;width:30%;height:10%;\">DOWN</button></a><br/>";
const String HtmlHtmlClose = "</html>";
//  

// Function / procedure to handle each client making a request
void response(){
  String htmlRes = HtmlHtml + HtmlTitle;
/*  if(statusLED == LOW){
    htmlRes += HtmlLedStateLow;
  }else{
    htmlRes += HtmlLedStateHigh;
  }  */
 
  htmlRes += HtmlButtons;
  htmlRes += HtmlHtmlClose;
 
  server.send(200, "text/html", htmlRes);
}

void motorUp(){
  digitalWrite(MOTOR_DOWN, LOW);
  delay(100) ;
  analogWrite(MOTOR_PWM,MOTOR_SPEED) ;
  digitalWrite(MOTOR_UP, HIGH);
  Serial.println("Motor up") ;
  response() ;
}

void motorDown(){
  digitalWrite(MOTOR_UP, LOW);
  delay(100) ;
  analogWrite(MOTOR_PWM,MOTOR_SPEED) ;
  digitalWrite(MOTOR_DOWN, HIGH);
  
  Serial.println("Motor Down") ;
  response() ;
 // server.send(200, "text/html", htmlRes);
}

void motorStop(){  // STOP ALL SIGNALS 
  digitalWrite(MOTOR_UP, LOW);
  digitalWrite(MOTOR_DOWN, LOW);
  analogWrite(MOTOR_PWM,0) ;  
  Serial.println("Motor stop") ;
  response() ;
}

// turn on/off the radar 
void radarOn(){
  digitalWrite(RADAR_ON_OFF ,HIGH) ; // turn on the radar
  Serial.println("RADAR ON") ;
  response() ;
}

void radarOff(){
  digitalWrite(RADAR_ON_OFF, LOW) ; // turn off the radar 
  Serial.println("RADAR OFF") ;
  response() ;
}

////// control speed - hardcode ---///////////////////

void motorSpeed30(){
  MOTOR_SPEED = 350 ;
  analogWrite(MOTOR_PWM,MOTOR_SPEED) ; 
  response() ; 
}
void motorSpeed40(){
  MOTOR_SPEED = 400 ;
  analogWrite(MOTOR_PWM,MOTOR_SPEED) ;  
  response() ;
}
void motorSpeed50(){
  MOTOR_SPEED = 500 ;
  analogWrite(MOTOR_PWM,MOTOR_SPEED) ;  
  response() ;
}
void motorSpeed60(){
  MOTOR_SPEED = 600 ;
  analogWrite(MOTOR_PWM,MOTOR_SPEED) ;
  response() ;  
}
void motorSpeed70(){
  MOTOR_SPEED = 700 ;
  analogWrite(MOTOR_PWM,MOTOR_SPEED) ;  
  response() ;
}
void motorSpeed80(){
  MOTOR_SPEED = 800 ;
  analogWrite(MOTOR_PWM,MOTOR_SPEED) ;  
  response() ;
}
void motorSpeed90(){
  MOTOR_SPEED = 900 ;
  analogWrite(MOTOR_PWM,MOTOR_SPEED) ;  
  response() ;
}
void motorSpeed100(){
  MOTOR_SPEED = 1024 ;
  analogWrite(MOTOR_PWM,MOTOR_SPEED) ;  
  response() ;
}
//////////////////////////////////////////////////

// set up esp8266 wifi NodeMCU 
void setup() {
  
    delay(1000); 
    Serial.begin(115200);
    Serial.println();
    WiFi.softAP(ssid, password, 5, 0 );
    //IPAddress apip = WiFi.softAPIP(); // Get the IP server
        // Set your Static IP address
    IPAddress local_IP(192, 168, 1, 100);
    // Set your Gateway IP address
    IPAddress gateway(192, 168, 4, 1);
    // mascara
    IPAddress subnet(255, 255, 0, 0);
    IPAddress primaryDNS(8, 8, 8, 8);   //optional
    IPAddress secondaryDNS(8, 8, 4, 4); //optional

    // Configures static IP address
    if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
      Serial.println("STA Failed to configure");
    }

    Serial.print("Connect your wifi laptop/mobile phone to this NodeMCU Access Point : ");
    Serial.println(ssid);
    Serial.print("Visit this IP : ");
    Serial.println(WiFi.localIP());   // to print ip-addres set before
    Serial.println(" in your browser.");

  // PWM FREQUENCY CONTROL 
    analogWriteFreq(5000) ; // change frequency to 20 khz.
    
    server.on("/", response); 
   // server.on("/LEDOn", handleLedOn);
   //  server.on("/LEDOff", handleLedOff);
    server.on("/MOTORUP", motorUp );
    server.on("/MOTORDOWN", motorDown );
    server.on("/MOTORSTOP", motorStop );
    server.on("/RADARON",radarOn) ;
    server.on("/RADAROFF",radarOff) ;

    //this code is hardcode, then do it better 
 ///////////////////////////////////////////////////////////
    server.on("/MOTORSPEED30",motorSpeed30) ;
    server.on("/MOTORSPEED40",motorSpeed40) ;
    server.on("/MOTORSPEED50",motorSpeed50) ;
    server.on("/MOTORSPEED60",motorSpeed60) ;
    server.on("/MOTORSPEED70",motorSpeed70) ;
    server.on("/MOTORSPEED80",motorSpeed80) ;
    server.on("/MOTORSPEED90",motorSpeed90) ;
    server.on("/MOTORSPEED100",motorSpeed100) ;
  ////////////////////////////////////////////////////
    
    server.begin(); // Start the server
    Serial.println("HTTP server beginned");
   
    // Define GPIO as Output
    pinMode(MOTOR_DOWN, OUTPUT);
    pinMode(MOTOR_UP, OUTPUT);
    pinMode(MOTOR_PWM, OUTPUT);
    pinMode(RADAR_ON_OFF ,OUTPUT) ;
    pinMode(RADAR_AUX,OUTPUT) ;
    
    // Define status
    digitalWrite(MOTOR_DOWN, LOW);
    digitalWrite(MOTOR_UP,LOW);
    digitalWrite(RADAR_ON_OFF ,LOW) ; // for turn ON/OFF the radar 
    digitalWrite(RADAR_AUX, LOW) ; // RADAR PIN AUX ACT 
    
    analogWrite(MOTOR_PWM,0) ;
}
 
void loop() {
    server.handleClient();
}
