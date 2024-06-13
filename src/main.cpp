#include <Arduino.h>
#include <FeederApplication.h>

FeederApplication app;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
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