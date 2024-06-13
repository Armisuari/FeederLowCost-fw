#include <array>
#include <variant>

#include "LoadCell_HX71708.h"

LoadCell_HX71708::LoadCell_HX71708(int dout, int dsck, float zeroLoad, float loadConstant) : _dout(dout),
_dsck(dsck), _zeroLoad(zeroLoad), _loadConstant(loadConstant), _measurementLoad(0),
_measurementUncertainty(0), _variance(0)
{
}

bool LoadCell_HX71708::init()
{
    pinMode(_dout, INPUT);
    pinMode(_dsck, OUTPUT);

    return true;
}

bool LoadCell_HX71708::read(uint32_t delayTime, uint8_t samplingRate)
{
    float sumData = 0;
    int32_t adcSamples[7];

    for (int j = 0; j < 7; j++)
    {
        adcSamples[j] = readDriver(samplingRate);
        delay(delayTime);
    }

    // Sort and average samples (excluding outliers)
    std::sort(adcSamples, adcSamples + 7);
    for (int j = 2; j < 5; j++)
    {
        sumData += adcSamples[j];
    }

    _measurementLoad = sumData / 3;
    calculateUncertainty(adcSamples);
    return true;
}

float LoadCell_HX71708::getLoad()
{
    return lsbToGram();
}

float LoadCell_HX71708::getLoadRaw() const
{
    return _measurementLoad;
}

float LoadCell_HX71708::getUncertainty() const
{

    return _measurementUncertainty;
}

void LoadCell_HX71708::calculateUncertainty(const int32_t *samples)
{
    float varianceSum = 0;
    for (int j = 2; j < 5; j++)
    {
        varianceSum += sq(samples[j] - _measurementLoad);
    }
    _variance = varianceSum / 2;
    _measurementUncertainty = _variance;
}

// Function to perform a single clock cycle with DOUT read
int8_t LoadCell_HX71708::clockCycleReadDout()
{
    digitalWrite(_dsck, HIGH);
    delayMicroseconds(10);
    digitalWrite(_dsck, LOW);
    delayMicroseconds(10);
    return digitalRead(_dout);
}

int32_t LoadCell_HX71708::readDriver(uint16_t samplingRate)
{
    int32_t _reading = 0;

    // Use std::array for fixed size data
    std::array<int8_t, 24> data;

    // Loop for _reading data bits
    for (int i = 0; i < 24; ++i)
    {
        data[i] = clockCycleReadDout();
        _reading = (_reading << 1) | data[i];
    }

    // Handle samplingRate specific additional bits using std::variant
    std::variant<int8_t, std::array<int8_t, 3>, std::array<int8_t, 2>> additionalBits;
    if (samplingRate == 320)
    {
        additionalBits = std::array<int8_t, 3>{clockCycleReadDout(), clockCycleReadDout(), clockCycleReadDout()};
    }
    else if (samplingRate == 80)
    {
        additionalBits = std::array<int8_t, 2>{clockCycleReadDout(), clockCycleReadDout()};
    }
    else if (samplingRate == 20)
    {
        additionalBits = clockCycleReadDout();
    }
    else
    {
        // Default 10 Hz - no additional bits
    }

    // Combine data based on framerate variant
    if (std::holds_alternative<std::array<int8_t, 3>>(additionalBits))
    {
        auto extraData = std::get<std::array<int8_t, 3>>(additionalBits);
        _reading |= (extraData[0] << 24) | (extraData[1] << 25) | (extraData[2] << 26);
    }
    else if (std::holds_alternative<std::array<int8_t, 2>>(additionalBits))
    {
        auto extraData = std::get<std::array<int8_t, 2>>(additionalBits);
        _reading |= (extraData[0] << 24) | (extraData[1] << 25);
    }
    else if (std::holds_alternative<int8_t>(additionalBits))
    {
        _reading |= std::get<int8_t>(additionalBits) << 24;
    }

    return _reading;
}

float LoadCell_HX71708::lsbToGram()
{
    float _conversionResult = (float)(_measurementLoad - _zeroLoad) * _loadConstant;
    return _conversionResult;
}