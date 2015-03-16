#include <iostream>

#include "FPS.hpp"
#include "Time.hpp"
#include "Logger.h"

namespace uGE {

    float FPS::startTime = 0.0f;
    float FPS::time = 0.0f;
    unsigned int FPS::count = 0;
    unsigned int FPS::fps = 0;

    void FPS::update()
    {
        if( startTime == 0.0f ) {
            startTime = Time::now();
        }

        FPS::time = Time::now();
        FPS::count++;
        if ( FPS::time - FPS::startTime >= 1.0f ) {
            char cFPS[8];
            sprintf( cFPS, "%d", FPS::count );
            Logger::print( Logger::INFO, "FPS " + std::string( cFPS ) );

            FPS::count = 0;
            FPS::startTime = FPS::time;
        }
    }

    unsigned int FPS::getFPS()
    {
        return fps;
    }
}
