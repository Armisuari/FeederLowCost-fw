#include <Arduino.h>
#include "settings/SettingsReader.h"
#include "AppConstant.h"
#include <FeederApplication.h>

FeederApplication app;

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
  // setTaskScheduler([]() { return app.measureLoad(); }, 10000U);

  static uint32_t lastUpadate = 0;
  if (millis() - lastUpadate >= 1000U)
  {
    lastUpadate = millis();
    app.measureLoad();
  }
}