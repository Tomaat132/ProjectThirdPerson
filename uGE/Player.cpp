#include "Player.hpp"
#include "Colliders/BoxCollider.hpp"
#include "Utils/glm.hpp"
#include "Time.hpp"

#include <iostream>

namespace uGE
{

    Player::Player()
    :GameObject( "Player" ), _score( 0 ), _shootable( 5 )
    {
        //ctor
    }

    Player::~Player()
    {
        //dtor
    }

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
        if (health <= 0){std::cout<<"Health got below 0"<<std::endl;}
        addCrumbs();

    }
    void Player::addCrumbs(){
    _timeCrumb +=Time::step();
        if(_timeCrumb > 1){//time to update the dropping of crumbs for zombie to follow
        dropCrumbs();//actual dropping of the crumbs
        _timeCrumb = 0;//reset, duh
        }
    }

    void Player::dropCrumbs(){//makes player drop a trail
    glm::vec3 crumb;
    crumb = getPosition();
    crumbs.push_back(crumb);
        for(unsigned int i = 0; i < crumbs.size(); i++){
            if(crumbs.size() > 4){
            crumbs.erase(crumbs.begin());
            }
        }
    }

    std::vector<glm::vec3> Player::getCrumbs(){
        return crumbs;
    }



    //add stuff below
}
