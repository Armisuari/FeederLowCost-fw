#include <Arduino.h>
#include "settings/SettingsReader.h"
#include "AppConstant.h"
#include <FeederApplication.h>

FeederApplication app;

void serialCommand();

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
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

void loop()
{
  // put your main code here, to run repeatedly:
  serialCommand();
  // app.feeding(true);

  static uint32_t lastUpadate = 0;
  if (millis() - lastUpadate >= 100U)
  {
    lastUpadate = millis();
    app.measureLoad();
  }
}

void serialCommand() {
  // Check if data is available to read
  if (Serial.available() > 0) {
    // Read the incoming data as a string
    String input = Serial.readStringUntil('\n');
    input.trim();  // Remove any leading or trailing whitespace

    // Print the received command
    Serial.println("Received command: " + input);

    if (input == "r") {
      esp_restart();
    }
  }
}