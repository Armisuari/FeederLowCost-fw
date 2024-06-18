#pragma once

class GateInterface
{
    public :
        virtual bool init() = 0;
        virtual bool open(int percent) = 0;
};