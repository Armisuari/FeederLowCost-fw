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
    Logs_t *log = &AppPreference.current().logs_devicel;
    while (state)
    {
        log->data.trigger += 1;
        bool _res = _act.processCommand(fm);

        if (_res)
        {
            log->success = true;
            log->data_count += 1;
            log->data.timestamp = 3423523; // dummy
            log->data.amount = fm;
        }
        else
        {
            log->success = false;
        }

        if (log->success || log->data.trigger >= triggOut)
        {
            AppPreference.save(PREFERENCE_FEEDLOG);
            log->data.trigger = 0;
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