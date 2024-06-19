#include <string>
#include "FeederApplication.h"
#include "settings/AppSettings.h"
#include "settings/SettingsReader.h"
#include "AppConstant.h"

FeederApplication::FeederApplication(LoadCell_Interface &lc, GateInterface &gate, ThrowerInterface &thrower) : _lc(lc), _gate(gate), _thrower(thrower)
{
}

bool FeederApplication::init()
{
    _lc.init();
    _thrower.init();
    return true;
}

bool FeederApplication::measureLoad()
{
    log_i("Raw load: %f\nLoad (g): %f\n", _lc.readRaw(), _lc.readLoad());
    return true;
}

bool FeederApplication::feed(bool &state, FeedingMode fm)
{
    AppSettings* settings = &AppPreference.current();
    while (state)
    {
        settings->trigger += 1;
        bool success = _act.processCommand(fm);

        Serial.printf("data trigger feed %d\n", settings->trigger);

        // Store results in AppSettings
        settings->success = true;
        settings->dataCount += 1;  
        settings->timestamp = 312321321;   // Get current Unix timestamp
        settings->amount = static_cast<int>(fm); // Convert FeedingMode to int
        
        Serial.printf("data from feed timestamp: %d\n", settings->timestamp);

        // Check for success or trigger limit
        if (success || settings->trigger >= triggOut)
        {
            // Save settings and reset trigger
            AppPreference.save(PREFERENCE_FEEDLOG);  
            settings->trigger = 0;
            state = false; 
        }
    }

    return true;
}

bool FeederApplication::throwerTest(bool state)
{
    // only for testing thrower
    if (state)
    {
        log_i("Thrower on");
        _thrower.run();
    }
    else
    {
        log_i("Thrower off");
        _thrower.stop();
    }
    return true;
}