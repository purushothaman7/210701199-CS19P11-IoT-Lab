#define BLYNK_TEMPLATE_ID "TMPL3m24YRVrS"
#define BLYNK_TEMPLATE_NAME "Plant Irrigation"
#define BLYNK_AUTH_TOKEN "ZsCvQkLYtbsT97qpv4UY-vnDoAKsTuy6"

#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define sensor 34
#define motor 5



BlynkTimer timer;

char auth[] = "ZsCvQkLYtbsT97qpv4UY-vnDoAKsTuy6";

char ssid[] = "ramanujancseb";
char pass[] = "12345678";


void setup() {
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  pinMode(motor, OUTPUT);

  pinMode(2, OUTPUT);
  digitalWrite(motor, HIGH);

}

void soilMoisture() {
  int value = analogRead(sensor);
  value = map(value, 0, 4095, 0, 100);
  value = (value - 100) * -1;
  Blynk.virtualWrite(V0, value);
  if (value < 15) {
    Blynk.logEvent("moisture_level_warning","Your Plant is Dying Pour Some Water");
  }
  else if(value >85){
    Blynk.logEvent("moisture_level_warning","Your Plant is Floating Stop Watering");
  }

}


BLYNK_WRITE(V1) {
  bool Relay = param.asInt();
  Serial.print(Relay);
  if (Relay == 1) {
    digitalWrite(motor, LOW);
  } else {
    digitalWrite(motor, HIGH);
  }
}


void loop() {
  soilMoisture();
  Blynk.run();
  
}