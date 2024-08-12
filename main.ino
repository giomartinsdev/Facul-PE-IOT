#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

const char* ssid = "SEU_SSID"; //WIFI HOST
const char* password = "SUA_SENHA";  // WIFI PASS

unsigned long myChannelNumber = YOUR_CHANNEL_ID;
const char * myWriteAPIKey = "YOUR_API_KEY";

WiFiClient client;

#define TRIG_PIN D5  
#define ECHO_PIN D6  

void setup() {
  Serial.begin(115200);
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado ao Wi-Fi");
  
  ThingSpeak.begin(client);  
}

void loop() {
  long duration, distance;
  
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  duration = pulseIn(ECHO_PIN, HIGH);
  
  distance = (duration / 2) / 29.1;

  Serial.print("Distância: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // Enviar os dados para o ThingSpeak
  ThingSpeak.setField(1, distance);  // Campo 1 em ThingSpeak
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  
  if(x == 200){
    Serial.println("Dados enviados com sucesso!");
  } else {
    Serial.println("Falha ao enviar dados, código: " + String(x));
  }
  
  delay(20000); 
}
