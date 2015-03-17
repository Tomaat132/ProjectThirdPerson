// Originally created for use in Project Lycoris (by Karanum)
// Do not use in any other projects without permission.
// Thomas has permission for his entire life ^-^

#include "Logger.h"

#include <iostream>
#include <sstream>
#include <string>

#if defined _WIN32
    #include <cstdarg>
    #include <windef.h>
    #include <wincon.h>
    #include <winbase.h>
#endif

/// Logs a string of text to the console. Message color and prefix are determined by the logging level.
void Logger::print( Level level, std::string text )
{
    #if defined DEBUG
        #if defined _WIN32
            HANDLE console = GetStdHandle( STD_OUTPUT_HANDLE );

            std::string printText = text;
            switch( level ) {
                case NORMAL:
                    SetConsoleTextAttribute( console, 0x0F );
                    break;
                case INFO:
                    SetConsoleTextAttribute( console, 0x0B );
                    printText = "[INFO] " + printText;
                    break;
                case WARNING:
                    SetConsoleTextAttribute( console, 0x0E );
                    printText = "[WARN] " + printText;
                    break;
                case ERROR:
                    SetConsoleTextAttribute( console, 0x0C );
                    printText = "[ERROR] " + printText;
                    break;
            }

            std::cout << printText << std::endl;
            SetConsoleTextAttribute( console, 0x0F );
        #endif

        #if defined __linux__
            switch( level ) {
                case NORMAL:
                    printText = "\033[37;1m" + printText + "\033[0m";
                    break;
                case INFO:
                    printText = "[INFO] " + printText;
                    printText = "\033[36;1m" + printText + "\033[0m";
                    break;
                case WARNING:
                    printText = "[WARN] " + printText;
                    printText = "\033[33;1m" + printText + "\033[0m";
                    break;
                case ERROR:
                    printText = "[ERROR] " + printText;
                    printText = "\033[31;1m" + printText + "\033[0m";
                    break;
            }

            std::cout << printText << std::endl;
        #endif

        #if defined TARGET_OS_MAC
            switch( level ) {
                case NORMAL:
                    break;
                case INFO:
                    printText = "[INFO] " + printText;
                    break;
                case WARNING:
                    printText = "[WARN] " + printText;
                    break;
                case ERROR:
                    printText = "[ERROR] " + printText;
                    break;
            }

            std::cout << printText << std::endl;
        #endif
    #endif
}
