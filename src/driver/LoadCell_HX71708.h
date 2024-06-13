#pragma once
#include <Arduino.h>

class LoadCell_HX71708
{
public:
    LoadCell_HX71708(int dout, int dsck, float zeroLoad = 563152.69, float loadConstant = -0.0168);
    bool init();
    bool read(uint32_t delayTime = 100, uint8_t samplingRate = 10);
    float getLoad();
    float getLoadRaw() const;
    float getUncertainty() const;

    std::string tag = "LOADCELL";
private:
    void calculateUncertainty(const int32_t *samples);
    int32_t readDriver(uint16_t samplingRate);
    int8_t clockCycleReadDout();
    float lsbToGram();

    int _dout, _dsck;
    float _measurementLoad;
    float _zeroLoad;
    float _loadConstant;
    float _measurementUncertainty;
    float _variance;

};