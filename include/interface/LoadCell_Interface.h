#pragma once
class LoadCell_Interface
{
    public:
        virtual bool init() = 0;
        virtual bool read(uint32_t delayTime = 100, uint8_t samplingRate = 10) = 0;
        virtual float getLoad() = 0;
        virtual float getRaw() = 0;
};