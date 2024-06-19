#pragma once
#include "ArduinoJson.h"
#include "utils/JsonUtils.h"
#include "utils/PSRamAllocator.h"

struct PondDevice_t
{
    std::string pond_id;
    std::string pond_name;

    JsonDocument toJSON() {
        JsonDocument j(&PSRamAllocatorInstance);
        j["pid"] = pond_id;
        j["pname"] = pond_name;
        return j;
    };

    void fromJSON(const JsonDocument& data) {
        pond_id = ArduinoJsonValueOr(data, "pid", "");
        pond_name = ArduinoJsonValueOr(data, "pname", "");
    };
};

struct Schedule_t
{
    std::string schedule_id;

    JsonDocument toJson(){
        JsonDocument j(&PSRamAllocatorInstance);
        j["sid"] = schedule_id;
        return j;
    }

    void fromJson(const JsonDocument& data){
        schedule_id = ArduinoJsonValueOr(data, "sid", "");
    }
};

struct LogsParam_t
{
    int amount;
    int trigger;
    int timestamp;
};

struct Logs_t
{
    bool success;
    int data_count;
    LogsParam_t data;

     JsonDocument toJson(){
        JsonDocument j(&PSRamAllocatorInstance);
        j["success"] = success;
        j["data_count"] = data_count;

        JsonObject dataJson = j.createNestedObject("data");
        dataJson["timestamp"] = data.timestamp;
        dataJson["amount"] = data.amount;
        dataJson["trigger"] = data.trigger;

        return j;
    }

    void fromJson(const JsonDocument& _data){
        success = ArduinoJsonValueOr(_data, "success", 0);
        data_count = ArduinoJsonValueOr(_data, "data_count", 0);
        data.timestamp = ArduinoJsonValueOr(_data, "timestamp", 0);
        data.amount = ArduinoJsonValueOr(_data, "amount", 0);
        data.trigger = ArduinoJsonValueOr(_data, "trigger", 0);
    }
};


struct AppSettings
{
    /* data */
    PondDevice_t pond_device;
    Schedule_t schedule_device;
    Logs_t logs_devicel;

    void parseJSON(const std::string &JsonDocumentPayload);

    JsonDocument toJson(){
        JsonDocument j(&PSRamAllocatorInstance);
        j["feedlogs"] = JsonDocumentMerge(
            pond_device.toJSON(),
            schedule_device.toJson(),
            logs_devicel.toJson()
        );
        return j;
    }

    void fromJson(const JsonDocument& data){
        pond_device.fromJSON(ArduinoJsonValueOr<JsonDocument>(data, "feedlogs", JsonObject()));
        schedule_device.fromJson(ArduinoJsonValueOr<JsonDocument>(data, "feedlogs", JsonObject()));
        logs_devicel.fromJson(ArduinoJsonValueOr<JsonDocument>(data, "feedlogs", JsonObject()));
    }
};
