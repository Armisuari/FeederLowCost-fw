#include "SettingsReader.h"
#include "ArduinoJson.h"
#include "utils/PSRamAllocator.h"

SettingsReader::SettingsReader()
{
}

bool SettingsReader::load(std::string filename)
{
    bool _ret = load(currPrefs_, filename);
    if (_ret)
    {
    }
    return _ret;
}

bool SettingsReader::load(AppSettings &settings, std::string filename)
{
    auto _file = LittleFS.open(filename.c_str(), "r");

    if (!_file)
    {
        Serial.println("Failed to open file for reading");
        return false;
    }
    try
    {
        if (_file.available())
        {
            String _content = _file.readString();
            Serial.printf("File content: \r\n%s", _content.c_str());
            settings.parseJSON(_content.c_str());
            Serial.println("Settings loaded successfully");
        }
        else
        {
            Serial.println("File is empty");
            Serial.println("Settings loaded with default value");
            settings.parseJSON("{}");
        }
    }
    catch (const std::exception &e)
    {
        Serial.println("Exception occurred while loading settings:");
        Serial.println(e.what());
        _file.close();
        return false;
    }

    _file.close();
    return true;
}

bool SettingsReader::save(std::string filename)
{
    bool _ret = save(currPrefs_, filename);
    return _ret;
}

bool SettingsReader::save(AppSettings &settings, std::string filename)
{
    auto _file = LittleFS.open(filename.c_str(), "w");

    if (!_file)
    {
        Serial.println("Failed to open file for writing");
        return false;
    }

    try
    {
        std::string _out;
        serializeJson(settings.toJson(), _out);
        Serial.println(_out.c_str());
        _file.print(_out.c_str());
        Serial.println("Settings saved to file successfully");
    }
    catch (const std::exception &e)
    {
        Serial.println("Exception occurred while saving settings:");
        Serial.println(e.what());
        _file.close();
        return false;
    }
    _file.close();
    return true;
}
