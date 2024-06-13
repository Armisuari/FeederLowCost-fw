#include <string>
#include "FeederApplication.h"

bool FeederApplication::init()
{
    _loadCell.init();
    return true;
}

bool FeederApplication::measureLoad()
{
    float loadRaw = _loadCell.getLoadRaw();
    float loadGram = _loadCell.getLoad();

    ESP_LOGD(_loadCell.tag, "Raw load: %f\nLoad (g): %f", loadRaw, loadGram);

    return true;
}