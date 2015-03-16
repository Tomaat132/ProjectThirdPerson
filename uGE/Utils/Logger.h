// Originally created for use in Project Lycoris (by Karanum)
// Do not use in any other projects without permission.

#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <sstream>

/// Used for outputting text to the OS console/terminal.
/// Should always be used in lieu of the std::cout buffer.

class Logger
{
    public:
        //Logger();
        //virtual ~Logger();

        enum Level { /**< Enumerator of constants defining the urgency level of the logged strings. */
            NORMAL = 0,
            INFO,
            WARNING,
            ERROR
        };

        static void print( Level level, std::string text );
    protected:
    private:
};

template< typename T >
inline std::string to_s( T nonstring ) {
    std::ostringstream ss;
    ss << nonstring;
    return ss.str();
}

#endif // LOGGER_H
