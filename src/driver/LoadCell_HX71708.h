#pragma once

#include <Arduino.h>
#include <interface/LoadCell_Interface.h>

class LoadCell_HX71708 : public LoadCell_Interface
{
public:
    LoadCell_HX71708(int dout = 17, int dsck = 16, float zeroLoad = 563152.69, float loadConstant = -0.0168);
    bool init();
    float readLoad();
    float readRaw();

private:
    bool read(uint32_t delayTime = 100, uint8_t samplingRate = 10);
    float getUncertainty() const;
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