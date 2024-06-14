#include <string>
#include "FeederApplication.h"

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
        Serial.println("failed to measure load !");
        return false;
    }

    float loadRaw = _loadCell.getLoadRaw();
    float loadGram = _loadCell.getLoad();
    Serial.printf("Raw load: %f\nLoad (g): %f\n", loadRaw, loadGram);

    return true;
}

bool FeederApplication::feeding(bool state)
{
    //only for testing thrower
    if (state)
    {
        Serial.println("Thrower on");
        _thrower.on();
    }
    else
    {
        Serial.println("Thrower off");
        _thrower.off();
    }
    return true;
}