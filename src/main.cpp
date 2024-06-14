#include <Arduino.h>
#include <FeederApplication.h>

FeederApplication app;

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
      ESP.restart();
    }
    else if (input == "on") {
      app.feeding(true);
    }
    else if (input == "off") {
      app.feeding(false);
    }
  }
}