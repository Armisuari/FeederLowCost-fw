#include <string>
#include "FeederApplication.h"
#include "settings/AppSettings.h"
#include "settings/SettingsReader.h"
#include "AppConstant.h"

bool FeederApplication::init()
{
    _loadCell.init();
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
    //need more data, Arief
    AppPreference.current().logs_devicel.ammount = _loadCell.getLoad();
    Serial.printf("Raw load: %f\nLoad (g): %f\n", loadRaw, loadGram);
    AppPreference.save(PREFERENCE_FEEDLOG);
    return true;
}