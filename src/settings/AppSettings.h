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

struct Logs_t
{
    float ammount;
    int trigger;

     JsonDocument toJson(){
        JsonDocument j(&PSRamAllocatorInstance);
        j["ammount"] = ammount;
        j["trigger"] = trigger;
        return j;
    }

    void fromJson(const JsonDocument& data){
        ammount = ArduinoJsonValueOr(data, "ammount", 1.0f);
        trigger = ArduinoJsonValueOr(data, "trigger", 0);
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
