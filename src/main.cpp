#include <Arduino.h>
#include <FeederApplication.h>

struct TaskUtils
{
  uint16_t interval;   // Time interval in milliseconds
  uint32_t prevMillis; // Last execution time
};

void setTaskScheduler(bool (*func)(), uint16_t interval);

FeederApplication app;

void setup()
{
  // put your setup code here, to run once:
  app.init();
}

void loop()
{
  // put your main code here, to run repeatedly:
  setTaskScheduler([]() { return app.measureLoad(); }, 1000U);
}

void setTaskScheduler(bool (*func)(), uint16_t interval)
{
  TaskUtils _task;
  _task.interval = interval;
  uint32_t currentMillis = millis();
  if (currentMillis - _task.prevMillis >= _task.interval)
  {
    _task.prevMillis = currentMillis;
    func(); // Call the function
  }
}