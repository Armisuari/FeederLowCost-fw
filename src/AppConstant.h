#pragma once

#if __has_include("Arduino.h")
  #include "Arduino.h"
#else
  #define log_w(...)
  #define log_i(...)
  #define log_e(...)
  #define log_d(...)
#endif

// #define 
constexpr auto PREFERENCE_FILENAME = "/preference.json";
constexpr auto PREFERENCE_FEEDLOG = "/feedlog.json";

#define BLYNK_TEMPLATE_ID ""
#define BLYNK_DEVICE_NAME ""
#define BLYNK_AUTH_TOKEN ""
