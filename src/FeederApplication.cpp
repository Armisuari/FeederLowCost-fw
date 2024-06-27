#include <string>
#include <memory>
#include "FeederApplication.h"
#include "settings/AppSettings.h"
#include "settings/SettingsReader.h"
#include "AppConstant.h"

FeederApplication::FeederApplication(LoadCell_Interface &lc, GateInterface &gate, ThrowerInterface &thrower)
    : _lc(lc), _gate(gate), _thrower(thrower), _running(true)
{
}

bool FeederApplication::init()
{
    _lc.init();
    _gate.init();
    _thrower.init();

    _gate.open(5);

    _sensorThread = std::thread(&FeederApplication::taskSensor, this);
    return true;
}

bool FeederApplication::measureLoad()
{
    _lc.read();
    log_i("Raw load: %f\tLoad (g): %f\n", _lc.getRaw(), _lc.getLoad());
    return true;
}

bool FeederApplication::feed(bool &state, FeedingMode fm)
{
    AppSettings *settings = &AppPreference.current();

    static bool isProcess;
    static FeedingState fState;

    static uint64_t prevMillis;
    if (millis() - prevMillis > 500U)
    {
        if (state)
        {
            prevMillis = millis();

            if (fState == FAILED)
            {
                settings->trigger += 1;
                log_d("count of triggering feed command %d", settings->trigger);
            }

            _act.processCommand(fm, fState);

            if (fState == SUCCESS)
            {
                log_i("feeding process done");

                // Store results in AppSettings
                settings->success = true;
                settings->dataCount += 1;
                settings->timestamp = 312321321;         // Get current Unix timestamp
                settings->amount = static_cast<int>(fm); // Convert FeedingMode to int
                log_i("data from feed timestamp: %d\n", settings->timestamp);

                // Save settings and reset trigger
                AppPreference.save(PREFERENCE_FEEDLOG);
                settings->trigger = 0;

                state = false;
            }

            // Check for success or trigger limit
            if (fState == FAILED)
            {
                if (settings->trigger >= triggOut)
                {
                    log_e("failed to feed");
                    settings->timestamp = 123123123;

                    // Save settings and reset trigger
                    AppPreference.save(PREFERENCE_FEEDLOG);
                    settings->trigger = 0;
                    state = false;
                }
            }
        }
    }

    return true;
}

void FeederApplication::taskSensor()
{
    while (_running)
    {
        measureLoad();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}
