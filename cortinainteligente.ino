/*
 * This is a basic example on how to use Espalexa and its device declaration methods.
 */ 
#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>


// prototypes
boolean connectWifi();

//callback functions
void refCortina(uint8_t brightness);


// Change this!!
const char* ssid = "Martins";
const char* password = "matheus2007";

boolean wifiConnected = false;


const int stepsPerRevolution = 800;




Espalexa espalexa;

//Variavel para posição da cortina
double pos = 0;

//Variavel para valor de acrecimo: Tamanho da cortina/Tamanho dos steps = Steps totais, Valor Requerido(0-255 do Espalexa)/Steps totais = Acrecimo final
const double acr = 0.31875;





void setup()
{

  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);

  
  Serial.begin(115200);
  // Initialise wifi connection
  wifiConnected = connectWifi();
  
  if(wifiConnected){
    
    // Define your devices here. 
    espalexa.addDevice("Cortina", refCortina, 0); //simplest definition, default state off
    
    
   


    espalexa.begin();
    
  } else
  {
    while (1) {
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
    }
  }

  
}
 
void loop()
{
   espalexa.loop();
   delay(1);
}

//our callback functions
void refCortina(uint8_t brightness) {

    for(pos > brightness; (pos += acr) < brightness; pos += acr){
      Serial.println("adicionando");
      digitalWrite(D1, LOW);
      digitalWrite(D2, HIGH);
      delay(60);
      digitalWrite(D2, LOW);
       
    }

    for(pos < brightness; (pos -= acr) > brightness; pos -= acr){
      Serial.println("voltando");
      digitalWrite(D1, HIGH);
      digitalWrite(D2, HIGH);
      delay(60);
      digitalWrite(D2, LOW);
      
       
    }
}



// connect to wifi – returns true if successful or false if not
boolean connectWifi(){
  boolean state = true;
  int i = 0;
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20){
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state){
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed.");
  }
  return state;
}
