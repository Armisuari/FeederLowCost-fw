#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <ArduinoJson.h>

char ssid[] = "";
char password[] = "";
char auth[] = "";


#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, password);
}

void loop() {
  Blynk.run();
}
