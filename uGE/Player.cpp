#include "Player.hpp"
#include "Colliders/BoxCollider.hpp"
#include <iostream>

namespace uGE{

    int health = 100;
    int maxHealth = 150;

    Player::Player()
    :GameObject( "Player" )
    {//ctor
        _score = 0;
        _shootable = 5;
    }


    Player::~Player()
    {
        //dtor
    }
//var space

//end of var space

    void Player::addScore( int value){
        _score += value;
    }
    int Player::getScore(){
        return _score;
    }
    int Player::getHealth(){
        return health;
    }
    int Player::getShootable(){
        return _shootable;
    }
    void Player::changeShootable(int value){
        _shootable += value;
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
