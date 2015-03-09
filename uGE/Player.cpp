#include "Player.hpp"
#include <iostream>

namespace uGE{

    int health = 100;
    int maxHealth = 150;

    Player::Player()
    :GameObject( "Player" )
    {//ctor

    }


    Player::~Player()
    {
        //dtor
    }
//var space

//end of var space


    int Player::getHealth(){
        return health;
    }

    void Player::changeHealth(int _health){
        health += _health;
        if( health > maxHealth ) {
            health = maxHealth;
        }
    }

    void Player::update(){
        GameObject::update();
        if (health <= 0){std::cout<<"HOLY SHIT IT'S 0"<<std::endl;}
    }



    //add stuff below
}
