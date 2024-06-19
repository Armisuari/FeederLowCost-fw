#include <Arduino.h>
#include "settings/SettingsReader.h"
#include "AppConstant.h"

#include <FeederApplication.h>
#include <driver/LoadCell_HX71708.h>
#include <driver/Gate_servo.h>
#include <driver/Thrower_relay.h>

LoadCell_HX71708 hx71708;
Gate_servo servo;
Thrower_relay relay;

FeederApplication app(hx71708, servo, relay);

void serialCommand();

bool isFeeding = false;
FeedingMode fm;

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