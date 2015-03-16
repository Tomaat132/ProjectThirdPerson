#include <iostream>
#include <sstream>

#if defined _WIN32
    #include <windef.h>
    #include <wincon.h>
#endif

#include "MyMenu.hpp"
#include "MyGame.hpp"

int main()
{
    #if defined _WIN32
        #ifndef DEBUG
            FreeConsole();
        #endif
    #endif

    MyGame * game = new MyGame();
    game->load();
    game->run();

	return 0;
}
