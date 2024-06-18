#pragma once

class ThrowerInterface
{
    public:
        virtual bool init() = 0;
        virtual bool run() = 0;
        virtual bool stop() = 0;
};