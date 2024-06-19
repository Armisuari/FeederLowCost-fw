#pragma once

#include <ArduinoJson.h>
#include "utils/JsonUtils.h"
#include "utils/PSRamAllocator.h"

// Type Aliases for Clarity
using JsonDoc = JsonDocument&; 

// Pond Device Struct
struct PondDevice {
    std::string pondId;
    std::string pondName;

    // toJSON: Use explicit member names for better readability
    JsonDocument toJson() const { // Make toJson const to indicate it doesn't modify the object
        JsonDocument j(&PSRamAllocatorInstance);
        j["pondId"] = pondId;
        j["pondName"] = pondName;
        return j;
    }

    void fromJSON(const JsonDocument& data) {
        pondId = ArduinoJsonValueOr(data, "pid", "");
        pondName = ArduinoJsonValueOr(data, "pname", "");
    };
};

// Schedule Struct
struct Schedule {
    std::string scheduleId;

    // toJson and fromJson:  Consistent naming with PondDevice
    JsonDocument toJson() const { 
        JsonDocument j(&PSRamAllocatorInstance);
        j["scheduleId"] = scheduleId;
        return j;
    }

    void fromJson(const JsonDocument& data){
        scheduleId = ArduinoJsonValueOr(data, "sid", "");
    }
};

// LogsParam Struct:  No need for methods if it's just data
struct LogsParam {
    int amount = 0; 
    int trigger = 0;
    int timestamp = 0;
};

// Logs Struct:  Improved nesting and clarity
struct Logs {
    bool success = false;
    int dataCount = 0;
    LogsParam data;

    JsonDocument toJson() const {
        JsonDocument j;
        j["success"] = success;
        j["dataCount"] = dataCount;

        JsonObject dataObj = j["data"].to<JsonObject>();
        dataObj["amount"] = data.amount;
        dataObj["trigger"] = data.trigger;
        dataObj["timestamp"] = data.timestamp;
        return j;
    }

    void fromJson(const JsonDocument& _data){
        success = ArduinoJsonValueOr(_data, "success", 0);
        dataCount = ArduinoJsonValueOr(_data, "data_count", 0);
        data.timestamp = ArduinoJsonValueOr(_data, "timestamp", 0);
        data.amount = ArduinoJsonValueOr(_data, "amount", 0);
        data.trigger = ArduinoJsonValueOr(_data, "trigger", 0);
    }
};

// AppSettings Struct:  Clearer member names and parsing logic
struct AppSettings {
    PondDevice pondDevice;
    Schedule schedule;
    bool success = false;
    int dataCount = 0;    
    int amount = 0; 
    int trigger = 0;
    int timestamp = 0;

    void parseJSON(const std::string &JsonDocumentPayload);

    JsonDocument toJson() const { 
        JsonDocument j;
        j["success"] = success;
        j["dataCount"] = dataCount;

        JsonObject dataObj = j["data"].to<JsonObject>();
        dataObj["amount"] = amount;
        dataObj["trigger"] = trigger;
        dataObj["timestamp"] = timestamp;
        return j;
    }

    void fromJson(const JsonDocument& _data){
        success = ArduinoJsonValueOr(_data, "success", 0);
        dataCount = ArduinoJsonValueOr(_data, "data_count", 0);
        timestamp = ArduinoJsonValueOr(_data, "timestamp", 0);
        amount = ArduinoJsonValueOr(_data, "amount", 0);
        trigger = ArduinoJsonValueOr(_data, "trigger", 0);
    }
};
