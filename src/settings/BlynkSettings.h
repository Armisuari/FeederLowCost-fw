#pragma once
#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <ArduinoJson.h>

class BlynkSettings;
extern BlynkSettings blynk;

class BlynkSettings {

public:
    BlynkSettings();

    void setup();
    void run();
};