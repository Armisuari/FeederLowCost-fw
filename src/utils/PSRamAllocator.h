#pragma once
#include "Arduino.h"
#include <ArduinoJson.h>

struct PSRamAllocator : ArduinoJson::Allocator {
  void* allocate(size_t size) override {
    return ps_malloc(size);
  }

  void deallocate(void* pointer) override {
    free(pointer);
  }

  void* reallocate(void* ptr, size_t new_size) override {
    return ps_realloc(ptr, new_size);
  }
};

extern PSRamAllocator PSRamAllocatorInstance;