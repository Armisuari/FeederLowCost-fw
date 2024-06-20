#include <Arduino.h>
#include "settings/SettingsReader.h"
#include "utils/FileUtils.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include "AppConstant.h"
#include <BlynkSimpleEsp32.h>

#include <FeederApplication.h>
#include <driver/LoadCell_HX71708.h>
#include <driver/Gate_servo.h>
#include <driver/Thrower_relay.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "";
char pass[] = "";

LoadCell_HX71708 hx71708;
Gate_servo servo;
Thrower_relay relay;

FeederApplication app(hx71708, servo, relay);
FileUtils fileUtils;  


void serialCommand();

bool isFeeding = false;
FeedingMode fm;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  fileUtils.beginFileSystem();
  bool loaddedSettings = AppPreference.load(PREFERENCE_FEEDLOG);
  log_i("Settings loaded: %s", loaddedSettings ? "true" : "false");
  if(!loaddedSettings)
  {
    log_e("Feedlogs doesnt exist, create a new one");
    AppPreference.save(PREFERENCE_FEEDLOG);
    esp_restart();
  }
  app.init();
}

BLYNK_WRITE(V0)
{
  int value = param.asInt();
  if(value == 1)
  {
    isFeeding = true;
    fm = MINIMUM;
  }
}

BLYNK_WRITE(V1)
{
  int value = param.asInt();
  if(value == 1)
  {
    isFeeding = true;
    fm = MEDIUM;
  }
}

BLYNK_WRITE(V2)
{
  int value = param.asInt();
  if(value == 1)
  {
    isFeeding = true;
    fm = MAXIMUM;
  }
}

void loop()
{
  Blynk.run();
  // put your main code here, to run repeatedly:
  serialCommand();

  if (isFeeding)
  {
    app.feed(isFeeding, fm);
  }

  static uint32_t lastUpadate = 0;
  if (millis() - lastUpadate >= 1000U)
  {
    lastUpadate = millis();
    app.measureLoad();
  }
}

void serialCommand()
{
  // Check if data is available to read
  if (Serial.available() > 0)
  {
    // Read the incoming data as a string
    String input = Serial.readStringUntil('\n');
    input.trim(); // Remove any leading or trailing whitespace

    // Print the received command
    log_i("Received command: %s", input.c_str());

    if (input == "feed1")
    {
      // feed
      isFeeding = true;
      fm = MINIMUM;
    }
    else if (input == "feed2")
    {
      isFeeding = true;
      fm = MEDIUM;
    }
    else if (input == "feed3")
    {
      isFeeding = true;
      fm = MAXIMUM;
    }
    // else if (input == "feed0")
    // {
    //   // stop
    //   isFeeding = false;
    // }
    else
    {
      log_e("invalid command");
    }
  }
}