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
    // need more data, Arief
    //  AppPreference.current().logs_devicel.ammount = _loadCell.getLoad();
    log_i("Raw load: %f\nLoad (g): %f\n", _lc.readRaw(), _lc.readLoad());
    // AppPreference.save(PREFERENCE_FEEDLOG);
    return true;
}

bool FeederApplication::feed(bool &state, FeedingMode fm)
{
    static FeedLogsParam log;
    while (state)
    {
        log.data.trigger++;
        bool _res = _act.processCommand(fm);

        if (_res)
        {
            log.succes = true;
            log.data_count += 1;
            log.data.timestamp = 3423523; // dummy
            log.data.amount = fm;
        }
        else
        {
            log.succes = false;
        }

        if (log.succes || log.data.trigger >= triggOut)
        {
            char buffer[256];
            sprintf(buffer,
                    "{"
                    "\"succes\":     %d,"
                    "\"data_count\": %d,"
                    "\"data\":"
                    "["
                    "\"timestamp\": %d,"
                    "\"amount\":    %d,"
                    "\"trigger\":   %d"
                    "]"
                    "}",
                    log.succes, log.data_count,
                    log.data.timestamp, log.data.amount, log.data.trigger);

            Serial.println(buffer);
            log.data.trigger = 0;
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