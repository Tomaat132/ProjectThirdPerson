#include "MenuController.hpp"
#include <iostream>
#include "../MyGame.hpp"

namespace uGE {

    MenuController::MenuController( uGE::GameObject * parent )
    :   Controller( parent )
    {
        //ctor
    }

    MenuController::~MenuController()
    {
        //dtor
    }

    void MenuController::update()
    {
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::P ) )
        {
            //DESTROY MENU
//            delete MyMenu;
            MyGame * game = new MyGame();
            game->load();
            game->run();
        }
    }
}
