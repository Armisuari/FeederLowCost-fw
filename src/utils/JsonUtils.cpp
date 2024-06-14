#include "JsonUtils.h"

void JsonDocumentMergeImpl(JsonVariant dst, JsonVariantConst src)
{
  if (src.is<JsonObjectConst>())
  {
    for (JsonPairConst kvp : src.as<JsonObjectConst>())
    {
      if (dst[kvp.key()]) 
        JsonDocumentMergeImpl(dst[kvp.key()], kvp.value());
      else
        dst[kvp.key()] = kvp.value();
    }
  }
  else
  {
    dst.set(src);
  }
}

void jsonPrint(JsonVariantConst doc) {
  std::string buffer;
  serializeJson(doc, buffer);
  log_e("Json: %s", buffer.c_str());
};