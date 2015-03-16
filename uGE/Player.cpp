#include "Player.hpp"
#include "Colliders/BoxCollider.hpp"
#include <iostream>
#include "Time.hpp"
namespace uGE{

    int health = 100;
    int maxHealth = 150;

    Player::Player()
    :GameObject( "Player" )
    {//ctor
        _score = 0;
        _shootable = 5;
        _timeLeft = 60.f;
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
    void Player::resetTime(){
        _timeLeft = 60.f;
    }
    int Player::getTimeLeft(){
        return (int)_timeLeft;
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
    bool reset = true;
    //PlayerController* Player::getPlayerController()
    //{
    //    return _controller;
   // }
    void Player::update(){

        GameObject::update();
        if( _timeLeft <= 0.f ) {std::cout<<"TIME IS DEAD"<<std::endl;}
        if (health <= 0){std::cout<<"HOLY SHIT IT'S 0"<<std::endl;}

        _timeLeft -= Time::step();

        if(reset){resetTime(); reset = false;}
    }



    //add stuff below
}
