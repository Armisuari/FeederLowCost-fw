#pragma once


#include <LittleFS.h>
#include <Preferences.h>
#include "AppSettings.h"

class SettingsReader;

extern SettingsReader AppPreference;

class SettingsReader {

public:
    SettingsReader();
    ~SettingsReader() {};
    
    void removeFile(std::string filename);
    bool load(std::string filename);
    bool save(std::string filename);

    AppSettings& current(){
        return currPrefs_;
    } 

protected:
    Preferences *_prefs;
    AppSettings currPrefs_{};
    bool save(AppSettings &settings, std::string filename);
    bool load(AppSettings &settings, std::string filename);
    bool initted_ = false;
private:
    bool isState_ = false;
};