#pragma once
class LoadCell_Interface
{
    public:
        virtual bool init() = 0;
        virtual float readLoad() = 0;
        virtual float readRaw() = 0;
};