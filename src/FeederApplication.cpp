#include <string>
#include "FeederApplication.h"
#include "settings/AppSettings.h"
#include "settings/SettingsReader.h"
#include "AppConstant.h"

FeederApplication::FeederApplication(GateInterface &gate, ThrowerInterface &thrower) : _gate(gate), _thrower(thrower)
{ 
}


bool FeederApplication::init()
{
    _loadCell.init();
    _thrower.init();
    return true;
}

bool FeederApplication::measureLoad()
{
    bool readLoad = _loadCell.read();

    if (!readLoad)
    {
        log_e("failed to measure load !");
        return false;
    }

    //need more data, Arief
    // AppPreference.current().logs_devicel.ammount = _loadCell.getLoad();
    log_d("Raw load: %f\nLoad (g): %f\n", _loadCell.getLoadRaw(), _loadCell.getLoad());
    // AppPreference.save(PREFERENCE_FEEDLOG);
    return true;
}

bool FeederApplication::throwerTest(bool state)
{
    //only for testing thrower
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