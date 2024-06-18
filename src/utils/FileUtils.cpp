#include "FileUtils.h"

#define FILE_LOC "/feeder_budget.txt"
FileUtils::FileUtils() {};

static void listDir(FS &fs, const char *dirname, uint8_t levels) {
    Serial.printf("\r\n==== Listing directory: %s ====\r\n", dirname);

    File _root = fs.open(dirname);
    if(!_root){
        Serial.println("- failed to open directory");
        return;
    }
    if(!_root.isDirectory()){
        Serial.println(" - not a directory");
        return;
    }

    File _file = _root.openNextFile();
    while(_file){
        if (_file.isDirectory()){
            time_t t= _file.getLastWrite();
            struct tm * tmstruct = localtime(&t);
            Serial.printf("%d-%02d-%02d %02d:%02d:%02d", 
                          (tmstruct->tm_year)+1900,( tmstruct->tm_mon)+1, tmstruct->tm_mday,tmstruct->tm_hour , tmstruct->tm_min, tmstruct->tm_sec);

            Serial.printf(" \t-- %s --\r\n", _file.name());

            if(levels){
                listDir(fs, _file.name(), levels - 1);
            }
        } else {
            time_t t= _file.getLastWrite();
            struct tm * tmstruct = localtime(&t);
            Serial.printf("%d-%02d-%02d %02d:%02d:%02d",
                          (tmstruct->tm_year)+1900,( tmstruct->tm_mon)+1, tmstruct->tm_mday,tmstruct->tm_hour , tmstruct->tm_min, tmstruct->tm_sec);

            Serial.printf(" \t%d", _file.size());

            Serial.printf(" \t%s\r\n", _file.name());
        }
        _file = _root.openNextFile();
    }

    _root.close();

    Serial.printf("==============================\r\n");
}

bool FileUtils::beginFileSystem()
{
    Serial.println("Starting littlefs");
    if(!LittleFS.begin(1, "/littlefs", 20, "data")){
        Serial.println("Failed mount littlefs");
        return false;
    }
        // List files.
    listDir(LittleFS, "/", 0);

    auto _used = LittleFS.usedBytes(), _total = LittleFS.totalBytes();
    auto _usedPer = (100.0f*(float)_used/(float)_total);
    Serial.printf("LitteFS used: %u bytes of total: %u bytes (used: %.2f%%)\r\n",
                        _used, _total, _usedPer);

    return true;
}