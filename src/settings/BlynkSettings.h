#pragma once

#include "AppConstant.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <ArduinoJson.h>

class BlynkSettings;
extern BlynkSettings blynk;

class BlynkSettings {

public:
    enum FeedMode { MINIMUM = 1, MEDIUM = 2, MAXIMUM = 3};
    BlynkSettings();

    void setup();
    void run();
    void setMode(FeedMode newMode);

private:
    FeedMode currentMode;
    void changeMode(int mode);
};