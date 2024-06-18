#include <Arduino.h>
#include "settings/SettingsReader.h"
#include "AppConstant.h"

#include <FeederApplication.h>
#include <driver/Gate_servo.h>
#include <driver/Thrower_relay.h>

Gate_servo servo;
Thrower_relay relay;

FeederApplication app(servo, relay);

void serialCommand();

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  app.init();
}

void loop()
{
  // put your main code here, to run repeatedly:
  serialCommand();

  static uint32_t lastUpadate = 0;
  if (millis() - lastUpadate >= 100U)
  {
    lastUpadate = millis();
    // app.measureLoad();
  }
}

void serialCommand()
{
  int _percent = 0;
  // Check if data is available to read
  if (Serial.available() > 0)
  {
    // Read the incoming data as a string
    String input = Serial.readStringUntil('\n');
    input.trim(); // Remove any leading or trailing whitespace

    // Print the received command
    log_i("Received command: %s", input.c_str());
  }
}