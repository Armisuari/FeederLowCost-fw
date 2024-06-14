#pragma once
#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <optional>
#include <ArduinoJson.h>
#include <type_traits>
#include "utils/PSRamAllocator.h"

class JsonUtils // : //public std::runtime_error
{
public:
    virtual void fromJson(const std::string &jsonString) = 0;
    virtual std::string toJson() = 0;
    // JsonUtils(const std::string &message) : std::runtime_error{message} {}
};

template<typename To>
std::optional<To> jsonToOptional(const JsonDocument& data) {
    if(data.isNull()) return std::nullopt;
    return data.as<To>();
}

template<typename From>
JsonDocument optionalToJson(std::optional<From> data) {
    JsonDocument j(&PSRamAllocatorInstance);
    if(data) j.set(data.value());
    return j;
}

template<typename T>
T ArduinoJsonValueOr(const JsonDocument& doc, const std::string_view& key, T defaultValue) {
    if(doc.containsKey(key)) {
        return doc[key];
    }
    return defaultValue;
}

void JsonDocumentMergeImpl(JsonVariant dst, JsonVariantConst src);

template<typename... T>
JsonVariant JsonDocumentMerge(JsonVariant dst, T... src) {
    (JsonDocumentMergeImpl(dst, src), ...);
    return dst;
}

void jsonPrint(JsonVariantConst doc);